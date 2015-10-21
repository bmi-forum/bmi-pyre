// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include "BoundedMesh.h"
#include "Interpolator.h"
#include "Source.h"


namespace Exchanger {

    Source::Source(MPI_Comm c, int sinkrank,
		   BoundedMesh& mesh, const BoundedBox& mybbox) :
	comm(c),
	sinkRank(sinkrank)
    {}


    Source::~Source()
    {
	delete interp;
    }


    // protected functions

    void Source::init(BoundedMesh& mesh, const BoundedBox& mybbox)
    {
        // receive mesh nodes from sink
	recvMesh(mesh, mybbox);

        // using interpolator to find out which nodes are inside this proc
	if(isOverlapped(mesh.bbox(), mybbox)) {
	    createInterpolator(mesh);
	    meshNode_.print("Exchanger-Source-meshNode");
	}

        // report which nodes are inside this proc to sink
	sendMeshNode();

        // keep a copy of the coordinates of mesh nodes
	initX(mesh);
    }


    void Source::recvMesh(BoundedMesh& mesh, const BoundedBox& mybbox)
    {
#if 1
	// assuming sink is broadcasting mesh to every source
	mesh.broadcast(comm, sinkRank);

#else
        // a more efficient approach, but not finished
	BoundedBox bbox = mybbox;
	util::exchange(comm, sinkRank, bbox);

	if(isOverlapped(mybbox, bbox)) {
	    mesh.receive(comm, source[i]);
	    createInterpolator(mesh);
	}

#endif
    }


    void Source::sendMeshNode() const
    {
	meshNode_.sendSize(comm, sinkRank);
	send(meshNode_);
    }


    void Source::initX(const BoundedMesh& mesh)
    {
	X_.resize(meshNode_.size());

	for(int i=0; i<X_.size(); ++i) {
	    int n = meshNode_[0][i];
	    for(int j=0; j<DIM; ++j)
		X_[j][i] = mesh.X(j,n);
	}
    }

}


// version
// $Id: Source.cc,v 1.4 2005/03/11 22:42:43 steve Exp $

// End of file
