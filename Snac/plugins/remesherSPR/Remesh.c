/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**
** Copyright (C), 2003,
**	Pururav Thoutireddy,
**	Californian Institute of Technology, 1200 East California Boulevard, Pasadena, California, 91125, USA.
**	110 Victoria Street, Melbourne, Victoria, 3053, Australia.
**	University of Texas, 1 University Station, Austin, Texas, 78712, USA.
**
** Authors:
**	Pururav Thoutireddy, Staff Scientist, Caltech
**	Stevan M. Quenette, Senior Software Engineer, VPAC. (steve@vpac.org)
**	Stevan M. Quenette, Visitor in Geophysics, Caltech.
**	Luc Lavier, Research Scientist, The University of Texas. (luc@utig.ug.utexas.edu)
**	Luc Lavier, Research Scientist, Caltech.
**
** This program is free software; you can redistribute it and/or modify it
** under the terms of the GNU General Public License as published by the
** Free Software Foundation; either version 2, or (at your option) any
** later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** $Id: Remesh.c 3096 2005-07-13 23:51:01Z EunseoChoi $
**
**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <mpi.h>
#include <StGermain/StGermain.h>
#include <StGermain/FD/FD.h>
#include "Snac/Snac.h"
#include "types.h"
#include "Mesh.h"
#include "Context.h"
#include "Remesh.h"
#include "Register.h"
#include "Utils.h"

#include <string.h>
#include <assert.h>


void _SnacRemesher_Remesh( void* _context, void* data ) {
	Snac_Context*			context = (Snac_Context*)_context;
	SnacRemesher_Context*	contextExt = ExtensionManager_Get(
															  context->extensionMgr,
															  context,
															  SnacRemesher_ContextHandle );
	Mesh*					mesh = context->mesh;
	SnacRemesher_Mesh*		meshExt = ExtensionManager_Get(
														   context->meshExtensionMgr,
														   mesh,
														   SnacRemesher_MeshHandle );
	Bool 					remesh;

	Journal_DPrintf( context->debug, "In: %s\n", __func__ );

	switch( contextExt->condition ) {
		case SnacRemesher_OnTimeStep:
			/* Remeshing on multiples of "OnTimeStep", but don't remesh on loop 0. */
			Journal_Firewall( contextExt->OnTimeStep, context->snacError, 
					  "Invalid remesh timestep criterion." );
			remesh = (context->timeStep <= 1) ? False : 
				(context->timeStep % contextExt->OnTimeStep == 0) ? True : False;
			break;

		case SnacRemesher_OnMinLengthScale:
			remesh = (context->minLengthScale/context->initMinLengthScale < 
				  contextExt->onMinLengthScale) ? True : False;
			break;

		case SnacRemesher_OnBothTimeStepLength:
			Journal_Firewall( contextExt->OnTimeStep, context->snacError, 
					  "Invalid remesh timestep criterion." );
			remesh = (context->timeStep <= 1) ? False : 
			  (context->timeStep % contextExt->OnTimeStep == 0) ? True : False;
			remesh = remesh ? True : (context->minLengthScale/context->initMinLengthScale < 
						  contextExt->onMinLengthScale) ? True : False;
			break;

		case SnacRemesher_Off:
		default:
			remesh = False;
			break;
	}

	if( remesh ) {
		Mesh*				mesh = context->mesh;
		Node_LocalIndex		newNode_i;

		Journal_Printf( context->snacInfo, "Remeshing!\n" );
		
		/*
		** If spherical coordinates are being used, 
		** then we'll need to convert the current mesh's cartesian coordinates 
		** to spherical coordinates first.
		*/
		
		if( meshExt->meshType == SnacRemesher_Spherical ) {
			Node_LocalIndex	lNode_i;
			
			for( lNode_i = 0; lNode_i < mesh->nodeLocalCount; lNode_i++ ) {
				double	x = mesh->nodeCoord[lNode_i][0];
				double	y = mesh->nodeCoord[lNode_i][1];
				double	z = mesh->nodeCoord[lNode_i][2];
				
				mesh->nodeCoord[lNode_i][0] = SnacArcTan( y, x );
				mesh->nodeCoord[lNode_i][1] = sqrt( x * x + y * y + z * z );
				mesh->nodeCoord[lNode_i][2] = acos( z / meshExt->newNodeCoords[lNode_i][1] );
			}
		}
		
		_SnacRemesher_RecoverNodes( context );

		/* Sync the mesh. */
		if( mesh->layout->decomp->procsInUse > 1 ) {
			Mesh_Sync( mesh );
		}
		
		/* Remesh the coordinates. */
		_SnacRemesher_NewCoords( context );

		/* Interpolate current nodal values onto new coordinates. */
		meshExt->newNodes = (Snac_Node*)ExtensionManager_Malloc( mesh->nodeExtensionMgr, mesh->nodeLocalCount );
		_SnacRemesher_InterpolateNodes( context );

		/* Don't forget the residualFr/Ft: 
		   This simple copy works because bottoms nodes are always bottom 
		   and remeshing doesn't change the node number. */
		for( newNode_i = 0; newNode_i < mesh->nodeLocalCount; newNode_i++ ) {
			Snac_Node* dstNode = (Snac_Node*)ExtensionManager_At( context->mesh->nodeExtensionMgr,
																  meshExt->newNodes,
																  newNode_i );

			Snac_Node* srcNode = Snac_Node_At( context, newNode_i );

			dstNode->residualFr = srcNode->residualFr;
			dstNode->residualFt = srcNode->residualFt;
		}
		
		/* Copy accross the new coord */
  		memcpy( mesh->nodeCoord, meshExt->newNodeCoords, mesh->nodeLocalCount * sizeof(Coord) );

		/* Copy node structures to the current array */
		/* The next single line can possibly replace the for loop.
		   memcpy( mesh->node, meshExt->newNodes, mesh->nodeExtensionMgr->finalSize * mesh->nodeLocalCount );  */
		for( newNode_i = 0; newNode_i < mesh->nodeLocalCount; newNode_i++ ) {
			Snac_Node* dstNode = Snac_Node_At( context, newNode_i );
			Snac_Node* srcNode = (Snac_Node*)ExtensionManager_At( context->mesh->nodeExtensionMgr,
																  meshExt->newNodes,
																  newNode_i );
			memcpy( dstNode, srcNode, mesh->nodeExtensionMgr->finalSize );
		}

		/* Simply average the recovered fields at the barycenter of each tet and run updateElements. */
   		_SnacRemesher_InterpolateElements( context );
   		_SnacRemesher_UpdateElements( context );
		
		/* Free some space, as it won't be needed until the next remesh. */
 		ExtensionManager_Free( mesh->nodeExtensionMgr, meshExt->newNodes );
		meshExt->newNodes = NULL;
		
		/*
		** If in spherical mode, convert back to cartesian coordinates.
		*/
		
		if( meshExt->meshType == SnacRemesher_Spherical ) {
			unsigned	lNode_i;
			
			for( lNode_i = 0; lNode_i < mesh->nodeLocalCount; lNode_i++ ) {
				double	theta = mesh->nodeCoord[lNode_i][0];
				double	r = mesh->nodeCoord[lNode_i][1];
				double	phi = mesh->nodeCoord[lNode_i][2];
				
				mesh->nodeCoord[lNode_i][0] = r * sin( phi ) * cos( theta );
				mesh->nodeCoord[lNode_i][1] = r * sin( phi ) * sin( theta );
				mesh->nodeCoord[lNode_i][2] = r * cos( phi );
			}
		}
		
		/* Sync the mesh. */
		if( mesh->layout->decomp->procsInUse > 1 ) {
			Mesh_Sync( mesh );
		}
		
		/* dump info such as remeshing frequency, criterion, and the current time step */
		contextExt->remeshingCount++;
		_SnacRemesher_DumpInfo( context );
	}
}
