// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include <algorithm>
#include <limits>
#include "Convertor.h"
#include "BoundedMesh.h"


namespace Exchanger {


    BoundedMesh::BoundedMesh() :
	bbox_(DIM)
    {}


    BoundedMesh::~BoundedMesh()
    {}


    BoundedBox BoundedMesh::tightBBox() const
    {
	BoundedBox tbbox(DIM);

	for(int d=0; d<DIM; ++d) {
	    tbbox[0][d] = std::numeric_limits<double>::max();
	    tbbox[1][d] = std::numeric_limits<double>::min();
	}

	for(int n=0; n<size(); ++n)
	    for(int d=0; d<DIM; ++d) {
		tbbox[0][d] = std::min(tbbox[0][d], X_[d][n]);
		tbbox[1][d] = std::max(tbbox[1][d], X_[d][n]);
	    }

	return tbbox;
    }


    void BoundedMesh::broadcast(const MPI_Comm& comm, int broadcaster)
    {
	bbox_.broadcast(comm, broadcaster);
	bbox_.print("Exchanger-BoundedMesh-BBox_recv");
	X_.broadcast(comm, broadcaster);
	X_.print("Exchanger-BoundedMesh-X_recv");

	Convertor& convertor = Convertor::instance();
	convertor.xcoordinate(bbox_);
	convertor.xcoordinate(X_);
    }


    void BoundedMesh::broadcast(const MPI_Comm& comm, int broadcaster) const
    {
	BoundedBox bbox(bbox_);
	Array2D<double,DIM> X(X_);

	Convertor& convertor = Convertor::instance();
	convertor.coordinate(bbox);
	convertor.coordinate(X);

	bbox.broadcast(comm, broadcaster);
	X.broadcast(comm, broadcaster);
    }


    void BoundedMesh::recv(const MPI_Comm& comm, int sender)
    {
	bbox_.recv(comm, sender);
	bbox_.print("Exchanger-BoundedMesh-BBox_recv");
	X_.recv(comm, sender);
	X_.print("Exchanger-BoundedMesh-X_recv");

	Convertor& convertor = Convertor::instance();
	convertor.xcoordinate(bbox_);
	convertor.xcoordinate(X_);
    }


    void BoundedMesh::send(const MPI_Comm& comm, int receiver) const
    {
	BoundedBox bbox(bbox_);
	Array2D<double,DIM> X(X_);

	Convertor& convertor = Convertor::instance();
	convertor.coordinate(bbox);
	convertor.coordinate(X);

	bbox.send(comm, receiver);
	X.send(comm, receiver);
    }

}


// version
// $Id: BoundedMesh.cc,v 1.2 2005/03/11 22:42:42 steve Exp $

// End of file
