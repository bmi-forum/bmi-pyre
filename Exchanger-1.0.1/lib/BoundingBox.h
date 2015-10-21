// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#if !defined(pyExchanger_BoundingBox_h)
#define pyExchanger_BoundingBox_h


#include <vector>
#include "mpi.h"
#include "DIM.h"


namespace Exchanger {

    typedef double BoundingBox[2][DIM];

    bool isInside(const std::vector<double>& x,
                  const BoundingBox& box);
    bool isOverlapped(const BoundingBox& lhs,
                      const BoundingBox& rhs);

    void broadcastBoundingBox(MPI_Comm comm, int root,
			      BoundingBox* boxes);
    BoundingBox*  exchangeBoundingBox(MPI_Comm comm, int target,
				      BoundingBox* my_boxes,
				      int my_comm_size);
    BoundingBox* gatherBoundingBox(MPI_Comm comm, int root,
				   const BoundingBox* my_box);


}

#endif

// version
// $Id: BoundingBox.h,v 1.1 2004/07/22 04:11:42 tan2 Exp $

// End of file
