// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include <stdexcept>
#include "Convertor.h"
#include "UtilTemplate.h"
#include "BoundingBox.h"


namespace Exchanger {


    void broadcastBoundingBox(MPI_Comm comm, int root,
			      BoundingBox* boxes)
    {
	int comm_size, rank;
	MPI_Comm_size(comm, &comm_size);
	MPI_Comm_size(comm, &rank);

	const int size = 2 * DIM * comm_size;
	int result = MPI_Bcast(boxes, size, MPI_DOUBLE,
			       root, comm);
	util::testResult(result, "broadcast BoundingBox error!");
    }


    BoundingBox*  exchangeBoundingBox(MPI_Comm comm, int target,
				      BoundingBox* my_boxes,
				      int my_comm_size)
    {
	// exchange size information
	int tag = 35;
	MPI_Status status;

	int remote_comm_size;
	int result = MPI_Sendrecv(&my_comm_size, 1, MPI_INT,
				  target, tag,
				  &remote_comm_size, 1, MPI_INT,
				  target, tag,
				  comm, &status);

	util::testResult(result, "exchange BoundingBox size error!");
	++tag;

	BoundingBox* remote_boxes = new BoundingBox[remote_comm_size];

        // convert before sending
        Convertor& convertor = Convertor::instance();

	for(int i=0; i<my_comm_size; ++i)
	    convertor.coordinate(my_boxes[i]);

	// exchanging
	const int send_size = 2 * DIM * my_comm_size;
	const int recv_size = 2 * DIM * remote_comm_size;

	result = MPI_Sendrecv(const_cast<BoundingBox*>(my_boxes),
			      send_size, MPI_DOUBLE,
			      target, tag,
			      remote_boxes,
			      recv_size, MPI_DOUBLE,
			      target, tag,
			      comm, &status);

	util::testResult(result, "exchange BoundingBox error!");

        // unconvert after receiving
	for(int i=0; i<remote_comm_size; ++i)
	    convertor.xcoordinate(remote_boxes[i]);

	return remote_boxes;
    }


    BoundingBox* gatherBoundingBox(MPI_Comm comm, int root,
				   const BoundingBox* my_box)
    {
	int comm_size, rank;
	MPI_Comm_size(comm, &comm_size);
	MPI_Comm_size(comm, &rank);

	BoundingBox* boxes = new BoundingBox[comm_size];

	const int size = 2 * DIM;
	int result = MPI_Gather(const_cast<BoundingBox*>(my_box),
				size, MPI_DOUBLE,
				boxes, size, MPI_DOUBLE,
				root, comm);
	util::testResult(result, "gather BoundingBox error!");

	return boxes;
    }


    bool isOverlapped(const BoundingBox& lhs,
                      const BoundingBox& rhs)
    {
        std::vector<double> x(DIM);

        // loop over all vertices of rhs, assuming DIM==3
        for(int i=0; i<2; i++)
            for(int j=0; j<2; j++)
                for(int k=0; k<2; k++) {

                    x[0] = lhs[i][0];
                    x[1] = lhs[j][1];
                    x[2] = lhs[k][2];

                    if(isInside(x, rhs)) return true;
                }

        if( (lhs[0][0] <= rhs[0][0]) && (lhs[1][0] >= rhs[1][0]) &&
	    (lhs[0][1] <= rhs[0][1]) && (lhs[1][1] >= rhs[1][1]) &&
	    (lhs[0][2] <= rhs[0][2]) && (lhs[1][2] >= rhs[1][2]) )
            return true;

        // more general critetion
        if( (lhs[0][0]<=rhs[1][0] && lhs[1][0]>=rhs[0][0]) &&
	    (lhs[0][1]<=rhs[1][1] && lhs[1][1]>=rhs[0][1]) &&
	    (lhs[0][2]<=rhs[1][2] && lhs[1][2]>=rhs[0][2]) )
	    return true;

        return false;
    }


    bool isInside(const std::vector<double>& x,
                  const BoundingBox& box)
    {
        bool inside = true;
        for(int m=0; m<DIM; m++)
            if(x[m] < box[0][m] ||
               x[m] > box[1][m]) {
                inside = false;
                break;
            }

        return inside;
    }


}

// version
// $Id: BoundingBox.cc,v 1.2 2005/03/11 22:42:42 steve Exp $

// End of file
