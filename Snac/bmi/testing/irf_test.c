#include <mpi.h>
#include "StGermain/StGermain.h"
#include "StGermain/FD/FD.h"
#include "Snac/Snac.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bmi.h>


int
main (void)
{
    BMI_Model *self = NULL;
    int err = BMI_SUCCESS;
    char name[BMI_MAX_COMPONENT_NAME];
    
    /***********************/
    /* Initialization      */
    /***********************/
    fprintf (stdout, "Initializing... ");
    
    err = BMI_Initialize ("./bmi_test.xml", &self);
    if (err || !self)
        return EXIT_FAILURE;
    
    fprintf (stdout, "PASS\n");

    /***********************/
    /* Get component name  */
    /***********************/

    BMI_Get_component_name (self, name);
    fprintf (stdout, "%s\n", name);

    /***********************/
    /* Update              */
    /***********************/
    BMI_Update (self);

#if 0
    {
        int i;
        const int n_steps = 10;
        double time;
        
        for (i = 0; i < n_steps; i++)
            {
                fprintf (stdout, "Running until t = %d... ", i+1);
                if (BMI_Update (self)==0 && BMI_Get_current_time (self, &time)==0) {
                    if (fabs (time-(i+1)) < 1e-6)
                        fprintf (stdout, "PASS\n");
                    else {
                        return EXIT_FAILURE;
                    }
                }
                else
                    return EXIT_FAILURE;
            }
        
        fprintf (stdout, "Running until t = %f... ", 1000.5);
        if (BMI_Update_until (self, 1000.5)==0 && BMI_Get_current_time (self, &time)==0) {
            if (fabs (time-1000.5) < 1e-6)
                fprintf (stdout, "PASS\n");
            else {
                fprintf (stdout, "%f\n", time);
                return EXIT_FAILURE;
            }
        }
        else
            return EXIT_FAILURE;
    }
#endif
    
    /***********************/
    /* Finalization        */
    /***********************/
    fprintf (stdout, "Finalizing... ");
    err = BMI_Finalize (self);
    
    if (err)
        return EXIT_FAILURE;
    fprintf (stdout, "PASS\n");
    
    return EXIT_SUCCESS;
}
