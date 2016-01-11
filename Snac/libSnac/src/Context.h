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
*/
/** \file
** Role:
**	This is the Snac Context... the Snac modeller/solver.
**
** Assumptions:
**
** Comments:
**
** $Id: Context.h 3274 2007-03-27 20:25:29Z EunseoChoi $
**
**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef __Snac_Context_h__
#define __Snac_Context_h__

	/* Textual name of this class */
	extern const Type Snac_Context_Type;

	/* Snac_Context entry point names */
	extern const Name Snac_EP_LoopNodesEnergy;
	extern const Name Snac_EP_LoopElementsEnergy;
	extern const Name Snac_EP_CalcStresses;
	extern const Name Snac_EP_StrainRate;
	extern const Name Snac_EP_Stress;
	extern const Name Snac_EP_Constitutive;
	extern const Name Snac_EP_LoopNodesMomentum;
	extern const Name Snac_EP_Force;
	extern const Name Snac_EP_ForceBC;
	extern const Name Snac_EP_UpdateNodeMomentum;
	extern const Name Snac_EP_LoopElementsMomentum;
	extern const Name Snac_EP_UpdateElementMomentum;
	extern const Name Snac_EP_RheologyUpdate;

	/* Snac_Context dt type names */
	extern const Name Snac_DtType_Constant;
	extern const Name Snac_DtType_Dynamic;
	extern const Name Snac_DtType_Wave;

	/* Snac_Context info */
	#define __Snac_Context \
		/* General info */ \
		__MeshContext \
		\
		/* Virtual info */ \
		\
		/* Snac_Context info */ \
		Bool                spherical; \
		Bool                computeThermalStress; \
		\
		\
		double				topo_kappa; \
		double				topoGradMax; \
		double				topoGradCriterion; \
		\
		Snac_Material*		materialProperty; \
		double				dt; \
		Type				dtType; \
		double				strain_inert; \
		double				speedOfSound; \
		double				minLengthScale; \
		double				initMinLengthScale; \
		\
		double				pisos; \
		double				gravity; \
		double				demf; \
		\
		CompositeVC*		nodeICs; \
		CompositeVC*		elementICs; \
		CompositeVC*		velocityBCs; \
		\
		/* TODO... we want journal or the like to look after this in the end */ \
		FILE*				simInfo; \
		FILE*				timeStepInfo; \
		FILE*				stressTensorOut; \
		Stream*				phaseIndexOut; \
		Stream*				strainRateOut; \
		Stream*				hydroPressureOut; \
		Stream*				stressOut; \
		Stream*				coordOut; \
		Stream*				velOut; \
		Stream*				forceOut; \
		\
		FILE*				checkpointTimeStepInfo; \
		FILE*				stressTensorCheckpoint; \
		Stream*				phaseIndexCheckpoint; \
		Stream*				coordCheckpoint; \
		Stream*				velCheckpoint; \
		\
		Stream*				snacInfo; \
		Stream*				snacDebug; \
		Stream*				snacVerbose; \
		Stream*				snacError; \
		\
		/* Calculation order of Snac's force per node summation */ \
		Snac_ForceCalcType		forceCalcType; \
		Index				decomposedAxis; \
		\
		/* Parallisation information */ \
		Snac_Parallel*			parallel; \
		\
		/* Snac_Context specific entry point keys */ \
		EntryPoint_Index		calcStressesK; \
		EntryPoint_Index		strainRateK; \
		EntryPoint_Index		stressK; \
		EntryPoint_Index		constitutiveK; \
		EntryPoint_Index		loopNodesMomentumK; \
		EntryPoint_Index		updateNodeK; \
		EntryPoint_Index		forceK; \
		EntryPoint_Index		loopElementsMomentumK;\
		EntryPoint_Index		updateElementK; \
		EntryPoint_Index		loopNodesEnergyK; \
		EntryPoint_Index		loopElementsEnergyK; \
		/* Should this type by Index? */ \
		Index				numProcX; \
		Index				numProcY; \
		Index				numProcZ; \
		/* pointer to the array of surface node coordinates */
		double***			surfNodes;


	struct _Snac_Context { __Snac_Context };


	/* Create a new Snac_Context and initialise */
	Snac_Context* Snac_Context_New(
		double					start,
		double					stop,
		SizeT					nodeSize,
		SizeT					elementSize,
		MPI_Comm				communicator,
		Dictionary*				dictionary );

	/* Initialise a Snac_Context */
	void Snac_Context_Init(
		Snac_Context*				self,
		double					start,
		double					stop,
		SizeT					nodeSize,
		SizeT					elementSize,
		MPI_Comm				communicator,
		Dictionary*				dictionary );

	/* Creation implementation / Virtual constructor */
	Snac_Context* _Snac_Context_New(
		SizeT					_sizeOfSelf,
		Type					type,
		Stg_Class_DeleteFunction*			_delete,
		Stg_Class_PrintFunction*			_print,
		Stg_Class_CopyFunction*			_copy,
		AbstractContext_SetDt*			_setDt,
		double					start,
		double					stop,
		SizeT					nodeSize,
		SizeT					elementSize,
		MPI_Comm				communicator,
		Dictionary*				dictionary );

	/* Initialisation implementation */
	void _Snac_Context_Init( Snac_Context* self );


	/* Stg_Class_Delete implementation */
	void _Snac_Context_Delete( void* context );

	/* Print implementation */
	void _Snac_Context_Print( void* context, Stream* stream );


	/* Build the Snac implementation */
	void _Snac_Context_Build( void* context );

	/* Initialise the Snac implementation */
	void _Snac_Context_InitialConditions( void* context );

	/* Initialise the Snac material properties */
	void _Snac_Context_InitializeMaterialProperties( void* context );

	/* Obtain the Dt for the Snac implementation */
	double _Snac_Context_Dt( void* context );

	/* Set the Dt */
	void _Snac_Context_SetDt( void* context, double dt );

	/* Set the boundary conditions of the Snac implementation */
	void _Snac_Context_BoundaryConditions( void* context );

	/* Do the zeroth time step */
	void Snac_Context_TimeStepZero( void* context );

	/* Solve for the Snac implementation */
	void _Snac_Context_Solve( void* context );

	/* Solve strain-rate, strain and stress for each element */
	void _Snac_Context_CalcStresses( void* context );

	/* Solve force, velocities and coordinates for each node */
	void _Snac_Context_LoopNodes( void* context );

	/* Solve volumes, normals, etc for each element */
	void _Snac_Context_LoopElements( void* context );
	void _Snac_Context_LoopElements_Restart( void* context );

	/* Sync for the Snac implementation */
	void _Snac_Context_Sync( void* context );

	/* Some output dumping helpers */
	Bool isTimeToDump( void* context );
	Bool isTimeToCheckpoint( void* context );

	void _Snac_Context_WriteLoopInfo( void* context );
	void _Snac_Context_DumpLoopInfo( void* context );
	void _Snac_Context_CheckpointLoopInfo( void* context );
	void _Snac_Context_InitOutput( void* context );
	void _Snac_Context_InitDump( void* context );
	void _Snac_Context_InitCheckpoint( void* context );
	void _Snac_Context_WriteOutput( void* context );
	void _Snac_Context_Dump( void* context );
	void _Snac_Context_Checkpoint( void* context );
	void _Snac_Context_DumpStressTensor( void* context );
	void _Snac_Context_CheckpointStressTensor( void* context );

#endif /* __Snac_Context_h__ */
