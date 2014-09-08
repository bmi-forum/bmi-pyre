/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**
** Copyright (C), 2003, 
**	Steve Quenette, 110 Victoria Street, Melbourne, Victoria, 3053, Australia.
**	Californian Institute of Technology, 1200 East California Boulevard, Pasadena, California, 91125, USA.
**	University of Texas, 1 University Station, Austin, Texas, 78712, USA.
**
** Authors:
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
** Role:
**	Instantiates the Snac solver/modeller.
**
** Assumptions:
**
** Comments:
**	Snac is an evolution of the FLAC methodology and code.
**	Snac is 3D.
**
** $Id: main.c 3243 2006-10-12 09:04:00Z SteveQuenette $
**
**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <mpi.h>
#include "StGermain/StGermain.h"
#include "StGermain/FD/FD.h"
#include "Snac/Snac.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bmi.h>

/* We are not extending on Snac at all, so just let the compiler know that a node, element and particle are the Snac equivalent. */
struct _Node {
	struct { __Snac_Node };
};

struct _Element {
	struct { __Snac_Element };
};

/*struct __BMI_Model { __Snac_Context };*/
struct _BMI_Model {

	Dictionary*        dictionary;
	XML_IO_Handler*    ioHandler;
	Snac_Context*      snacContext;

};

int
BMI_Initialize (const char *config_file, BMI_Model ** handle)
{

    BMI_Model          self;

	MPI_Comm           CommWorld;
	int                rank;
	int                numProcessors;
	int                procToWatch;
	char*              filename;

    if (!handle)
        return BMI_FAILURE;
    
	/* Initialise MPI, get world info */
	/* MPI_Init( &argc, &argv ); */
	MPI_Init( NULL, NULL );
	MPI_Comm_dup( MPI_COMM_WORLD, &CommWorld );
	MPI_Comm_size( CommWorld, &numProcessors );
	MPI_Comm_rank( CommWorld, &rank );
    
    /* Hardwire the process to watch to 0. 
       Note that it doesn't have to be 0 when multiple processrs are used. */ 
    procToWatch = 0;
#if 0
	if( argc >= 3 ) {
		procToWatch = atoi( argv[2] );
	}
	else {
		procToWatch = 0;
	}
#endif
	if( rank == procToWatch ) printf( "Watching rank: %i\n", rank );
	
	/* if (!Snac_Init( &argc, &argv )) { */
	if (!Snac_Init( NULL, NULL )) {
		fprintf(stderr, "Error initialising StGermain, exiting.\n" );
		exit(EXIT_FAILURE);
	}
	
	/* Snac's init message */
    {
        int tmp	= Stream_GetPrintingRank( Journal_Register( InfoStream_Type, "Context" ) );
        Stream_SetPrintingRank( Journal_Register( InfoStream_Type, "Context" ), 0 );
        Journal_Printf( /* DO NOT CHANGE OR REMOVE */
                       Journal_Register( InfoStream_Type, "Context" ), 
                       "Snac. Copyright (C) 2003-2005 Caltech, VPAC & University of Texas.\n" );
        Stream_Flush( Journal_Register( InfoStream_Type, "Context" ) );
        Stream_SetPrintingRank( Journal_Register( InfoStream_Type, "Context" ), tmp );
    }

    /* Ensures copyright info always come first in output */
	MPI_Barrier( CommWorld );
    
	
	/* Create the dictionary, and some fixed values */
    /* Hardwirred to the one-processor scenario for now. */
	self.dictionary = Dictionary_New();
	Dictionary_Add( self.dictionary, "rank", Dictionary_Entry_Value_FromUnsignedInt( 0 ) );
	Dictionary_Add( self.dictionary, "numProcessors", Dictionary_Entry_Value_FromUnsignedInt( 1 ) );
	
	/* Read input */
	self.ioHandler = XML_IO_Handler_New();
    filename = strdup( config_file );
	if ( False == IO_Handler_ReadAllFromFile( self.ioHandler, filename, self.dictionary ) )
        {
            fprintf( stderr, "Error: Snac couldn't find specified input file %s. Exiting.\n", filename );
            exit( EXIT_FAILURE );
        }
	Journal_ReadFromDictionary( self.dictionary );
    free( filename );
    
    /* This is the handle to the SNAC's model data. */
	self.snacContext = Snac_Context_New( 0.0f, 0.0f, sizeof(Snac_Node), sizeof(Snac_Element), CommWorld, self.dictionary );
	if( rank == procToWatch ) Dictionary_PrintConcise( self.dictionary, self.snacContext->verbose );
    
	/* Construction phase -----------------------------------------------------------------------------------------------*/
	Stg_Component_Construct( self.snacContext, 0 /* dummy */, &(self.snacContext), True );
	
	/* Building phase ---------------------------------------------------------------------------------------------------*/
	Stg_Component_Build( self.snacContext, 0 /* dummy */, False );
	
	/* Initialisaton phase ----------------------------------------------------------------------------------------------*/
	Stg_Component_Initialise( self.snacContext, 0 /* dummy */, False );
	if( rank == procToWatch ) Context_PrintConcise( self.snacContext, self.snacContext->verbose );


    /* pass the pointer to Snac_Context to handle */
    *handle = &self;
    
    return BMI_SUCCESS;
}


int BMI_Update (BMI_Model *self)
{

    
	/* Step the context solver */
	Stg_Component_Execute( self->snacContext, 0 /* dummy */, False );
	
    
    return BMI_SUCCESS;
}
/* End: BMI_Update */

#if 0
int
BMI_Update_frac (BMI_Model *self, double f)
{
  if (f>0) {
    double dt;

    BMI_Get_time_step (self, &dt);

    self->dt = f * dt;

    BMI_Update (self);

    self->dt = dt;
  }

  return BMI_SUCCESS;
}
/* End: BMI_Update_frac */

int
BMI_Update_until (BMI_Model *self, double t)
{
  {
    double dt;
    double now;

    BMI_Get_time_step (self, &dt);
    BMI_Get_current_time (self, &now);

    {
      int n;
      const double n_steps = (t - now) / dt;
      for (n=0; n<(int)n_steps; n++) {
        BMI_Update (self);
      }

      BMI_Update_frac (self, n_steps - (int)n_steps);
    }
  }

  return BMI_SUCCESS;
}
/* End: BMI_Update_until */
#endif

int
BMI_Finalize (BMI_Model *self)
{
    if (self)
        {
            /* Stg_Class_Delete stuff */
            Stg_Component_Destroy( self->snacContext, 0 /* dummy */, False );
            Stg_Class_Delete( self->snacContext );
            Stg_Class_Delete( self->ioHandler );
            Stg_Class_Delete( self->dictionary );
            
            /* Close off frameworks */
            Snac_Finalise();
            MPI_Finalize();
        }
    
    return BMI_SUCCESS;
}
/* End: BMI_Finalize */


int
BMI_Get_component_name (BMI_Model *self, char * name)
{
  strncpy (name, "Snac model as a BMI component", BMI_MAX_COMPONENT_NAME);
  return BMI_SUCCESS;
}
/* End: BMI_Get_component_name */
