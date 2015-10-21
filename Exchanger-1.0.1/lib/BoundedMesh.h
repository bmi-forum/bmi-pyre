// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#if !defined(pyExchanger_BoundedMesh_h)
#define pyExchanger_BoundedMesh_h

#include <string>
#include "Array2D.h"
#include "BoundedBox.h"
#include "DIM.h"
#include "mpi.h"


namespace Exchanger {

    class BoundedMesh {
    protected:
	BoundedBox bbox_;         // domain bounds
	Array2D<double,DIM> X_;   // coordinate
	Array2D<int,1> nodeID_;   // node # in Solver data structure

    public:
	BoundedMesh();
	virtual ~BoundedMesh() = 0;

	inline int size() const {return X_.size();}

	inline const BoundedBox& bbox() const {return bbox_;}
	inline double X(int d, int n) const {return X_[d][n];}
	inline int nodeID(int n) const {return nodeID_[0][n];}

	BoundedBox tightBBox() const;
	virtual void broadcast(const MPI_Comm& comm, int broadcaster);
	virtual void broadcast(const MPI_Comm& comm, int broadcaster) const;
	virtual void recv(const MPI_Comm& comm, int sender);
	virtual void send(const MPI_Comm& comm, int receiver) const;

    private:
	BoundedMesh(const BoundedMesh&);
	BoundedMesh& operator=(const BoundedMesh&);

    };

}

#endif

// version
// $Id: BoundedMesh.h,v 1.1 2004/05/08 01:51:14 tan2 Exp $

// End of file
