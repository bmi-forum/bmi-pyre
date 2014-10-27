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

struct _BMI_Model {

	Dictionary*        dictionary;
	XML_IO_Handler*    ioHandler;
	Snac_Context*      snacContext;

};

int
BMI_Initialize (const char *config_file, BMI_Model ** handle)
{

    BMI_Model          *self;

	MPI_Comm           CommWorld;
	int                rank;
	int                numProcessors;
	int                procToWatch;
	char*              filename;

    if (!handle)
        return BMI_FAILURE;
    
    self = malloc( sizeof(BMI_Model) );

	/* Initialise MPI, get world info */
	MPI_Init( NULL, NULL ); 	/* MPI_Init( &argc, &argv ); */
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
	self->dictionary = Dictionary_New();
	Dictionary_Add( self->dictionary, "rank", Dictionary_Entry_Value_FromUnsignedInt( 0 ) );
	Dictionary_Add( self->dictionary, "numProcessors", Dictionary_Entry_Value_FromUnsignedInt( 1 ) );
	
	/* Read input */
	self->ioHandler = XML_IO_Handler_New();
    filename = strdup( config_file );
	if ( False == IO_Handler_ReadAllFromFile( self->ioHandler, filename, self->dictionary ) )
        {
            fprintf( stderr, "Error: Snac couldn't find specified input file %s. Exiting.\n", filename );
            exit( EXIT_FAILURE );
        }
	Journal_ReadFromDictionary( self->dictionary );
    free( filename );
    
    /* This is the handle to the SNAC's model data. */
	self->snacContext = Snac_Context_New( 0.0f, 0.0f, sizeof(Snac_Node), sizeof(Snac_Element), CommWorld, self->dictionary );
	if( rank == procToWatch ) Dictionary_PrintConcise( self->dictionary, self->snacContext->verbose );
    
	/* Construction phase -----------------------------------------------------------------------------------------------*/
	Stg_Component_Construct( self->snacContext, 0 /* dummy */, &(self->snacContext), True );
	
	/* Building phase ---------------------------------------------------------------------------------------------------*/
	Stg_Component_Build( self->snacContext, 0 /* dummy */, False );
	
	/* Initialisaton phase ----------------------------------------------------------------------------------------------*/
	Stg_Component_Initialise( self->snacContext, 0 /* dummy */, False );
	if( rank == procToWatch ) Context_PrintConcise( self->snacContext, self->snacContext->verbose );

    /* pass the pointer to Snac_Context to handle */
    *handle = self;
   
    return BMI_SUCCESS;
}


int BMI_Run_model (BMI_Model *self)
{

    
	/* Step the context solver */
	Stg_Component_Execute( self->snacContext, 0 /* dummy */, False );
	
    
    return BMI_SUCCESS;
}
/* End: BMI_Run_model */


int
BMI_Update (BMI_Model *self)
{
    double dt;

    BMI_Get_time_step( self, &dt );

    self->snacContext->currentTime += dt;
    AbstractContext_Step( self->snacContext, dt );
    self->snacContext->timeStep++;

    return BMI_SUCCESS;
}
/* End: BMI_Update */


int
BMI_Update_frac (BMI_Model *self, double f)
{
    if (f>0) {
        double dt;
        
        BMI_Get_time_step (self, &dt);

        self->snacContext->_setDt( self->snacContext, f*dt );

        BMI_Update (self);

        self->snacContext->dt = dt;
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



/*******************************/
/* Model information functions */
/*******************************/
int
BMI_Get_component_name (BMI_Model *self, char * name)
{
    strncpy (name, "SNAC", BMI_MAX_COMPONENT_NAME);
    return BMI_SUCCESS;
}

int
BMI_Get_input_var_name_count (BMI_Model *self, int * count) {

    *count = self->dictionary->count;
    return BMI_SUCCESS;

}

int
BMI_Get_input_var_names (BMI_Model *self, char ** names)
{

  int i;
  /* for (i=0; i<BMI_INPUT_VAR_NAME_COUNT; i++) { */
  /*   strncpy (names[i], input_var_names[i], BMI_MAX_VAR_NAME); */
  /* } */

  printf( "Dictionary:\n" );
  printf( "\tsize: %u\n", self->dictionary->size );
  printf( "\tdelta: %u\n", self->dictionary->delta );
  printf( "\tcount: %u\n", self->dictionary->count );
  printf( "\tentryPtr[0-%u]: {\n", self->dictionary->count );
  for( i = 0; i < self->dictionary->count; i++ ) {
    printf( "\t\t" );
    Dictionary_Entry_Print( self->dictionary->entryPtr[i], stdout ); 
    printf( "\n" );
}
  printf( "\t}\n" );
  
  return BMI_SUCCESS;

}

#if 0

int BMI_Get_output_var_name_count (BMI_Model, int *) {

}

int BMI_Get_output_var_names (BMI_Model *, char **) {

}

/**********************************/
/* Variable information functions */
/**********************************/
int
BMI_Get_var_type (BMI_Model *self, const char *long_var_name, BMI_Var_type * type)
{
  if (strcasecmp (long_var_name, "surface_elevation") == 0) {
    *type = BMI_VAR_TYPE_DOUBLE;
    return BMI_SUCCESS;
  }
  else {
    *type = BMI_VAR_TYPE_UNKNOWN;
    return BMI_FAILURE;
  }
}
/* End: BMI_Get_var_type */

int
BMI_Get_var_units (BMI_Model *self, const char *long_var_name, char * units)
{
  if (strcmp (long_var_name, "surface_elevation") == 0) {
    strncpy (units, "meter", BMI_MAX_UNITS_NAME);
    return BMI_SUCCESS;
  }
  else {
    units[0] = '\0';
    return BMI_FAILURE;
  }
}
/* End: BMI_Get_var_units */

int
BMI_Get_var_rank (BMI_Model *self, const char *long_var_name, int * rank)
{
  if (strcmp (long_var_name, "surface_elevation") == 0) {
    *rank = 2;
    return BMI_SUCCESS;
  }
  else {
    *rank = -1;
    return BMI_FAILURE;
  }
}
/* End: BMI_Get_var_rank */

int
BMI_Get_current_time (BMI_Model *self, double *now) {

    *now = self->snacContext->currentTime;

    return BMI_SUCCESS;
}


int BMI_Get_start_time (BMI_Model *self, double *start_time) {

    *start_time = self->snacContext->currentTime;

    return BMI_SUCCESS;
}

int BMI_Get_end_time (BMI_Model *self, double *end_time) {

    *end_time = self->snacContext->stopTime;

    return BMI_SUCCESS;

}

int BMI_Get_time_units (BMI_Model *, char *) {

}

int
BMI_Get_time_step (BMI_Model *self, double *dt) {

    *dt = AbstractContext_Dt( self->snacContext );
    
    return BMI_SUCCESS;
}


/****************************************/
/* Variable getter and setter functions */
/****************************************/
int BMI_Get_double (BMI_Model *, const char *, double *) {

}

int BMI_Get_double_ptr (BMI_Model *, const char *, double **) {

}

int BMI_Get_double_at_indices (BMI_Model *, const char *, double *, int *, int) {

}

int BMI_Set_double (BMI_Model *, const char *, double *) {

}

int BMI_Set_double_ptr (BMI_Model *, const char *, double **) {

}

int BMI_Set_double_at_indices (BMI_Model *, const char *, int *, int, double *) {

}

/******************************/
/* Grid information functions */
/******************************/
int BMI_Get_grid_shape (BMI_Model *, const char *, int *) {

}

int BMI_Get_grid_spacing (BMI_Model *, const char *, double *) {

}

int BMI_Get_grid_origin (BMI_Model *, const char *, double *) {

}

int BMI_Get_grid_x (BMI_Model *, const char *, double *) {

}

int BMI_Get_grid_y (BMI_Model *, const char *, double *) {

}

int BMI_Get_grid_z (BMI_Model *, const char *, double *) {

}

int BMI_Get_grid_cell_count (BMI_Model *, const char *, int *) {

}

int BMI_Get_grid_point_count (BMI_Model *, const char *, int *) {

}

int BMI_Get_grid_vertex_count (BMI_Model *, const char *, int *) {

}

int BMI_Get_grid_connectivity (BMI_Model *, const char *, int *) {

}

int BMI_Get_grid_offset (BMI_Model *, const char *, int *) {

}

/**************************************************************************/
/* Assumes arrays start at 0, and have contiguous elements (unit stride). */
/**************************************************************************/
double BMI_Get_0d_double (BMI_Model *, const char *);
double *BMI_Get_1d_double (BMI_Model *, const char *, int [1]);
double *BMI_Get_2d_double (BMI_Model *, const char *, int [2]);
double *BMI_Get_3d_double (BMI_Model *, const char *, int [3]);
double *BMI_Get_1d_double_at_indices (BMI_Model *, const char *, int *,
    int , double *);
double *BMI_Get_2d_double_at_indices (BMI_Model *, const char *, int *, int);
// A more general getter
//double *BMI_Get_double (BMI_Model *, const char *, int *, int **);

void BMI_Set_0d_double (BMI_Model *, const char *, double);
void BMI_Set_1d_double (BMI_Model *, const char *, const double *);
void BMI_Set_2d_double (BMI_Model *, const char *, const double *);
void BMI_Set_3d_double (BMI_Model *, const char *, const double *);
void BMI_Set_2d_double_at_indices (BMI_Model *, const char *, int *,
    const double *, int);

int BMI_Get_0d_int (BMI_Model *, const char *);
int *BMI_Get_1d_int (BMI_Model *, const char *, int [1]);
int *BMI_Get_2d_int (BMI_Model *, const char *, int [2]);
int *BMI_Get_3d_int (BMI_Model *, const char *, int [3]);
int *BMI_Get_2d_int_at_indices (BMI_Model *, const char *, int *, int);

void BMI_Set_0d_int (BMI_Model *, const char *, int);
void BMI_Set_1d_int (BMI_Model *, const char *, const int *);
void BMI_Set_2d_int (BMI_Model *, const char *, const int *);
void BMI_Set_3d_int (BMI_Model *, const char *, const int *);
void BMI_Set_2d_int_at_indices (BMI_Model *, const char *, int *,
    const int *, int);

/*
int *BMI_Get_grid_dimen (BMI_Model *, const char *, int *);
double *BMI_Get_grid_res (BMI_Model *, const char *, int *);
double *BMI_Get_grid_corner (BMI_Model *, const char *, int *);
 */

/*
  IElementSet get_Element_Set (BMI_Model *handle);
  IValueSet get_Value_Set (BMI_Model *handle, char *long_var_name, ITimeStamp);
*/

// Since these are just wrappers for other BMI functions, I don't
// think they should be included in the interface definition. They
// could be CMI functions.
int BMI_Is_scalar (BMI_Model *, const char *);
int BMI_Is_vector (BMI_Model *, const char *);
int BMI_Is_grid (BMI_Model *, const char *);
int BMI_Has_var (BMI_Model *, const char *);

// However, something that indicates if the grid is raster, or
// uniform rectilinear would be needed.
int BMI_Is_raster_grid (BMI_Model *, const char *);

#endif
