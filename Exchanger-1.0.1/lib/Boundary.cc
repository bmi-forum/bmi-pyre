// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include <vector>
#include "Boundary.h"


namespace Exchanger {

    Boundary::Boundary() :
	BoundedMesh()
    {}


    Boundary::~Boundary()
    {}


    void Boundary::broadcast(const MPI_Comm& comm, int broadcaster)
    {
	BoundedMesh::broadcast(comm, broadcaster);

	normal_.broadcast(comm, broadcaster);
	normal_.print("Exchanger-Boundary-normal_recv");
    }


    void Boundary::broadcast(const MPI_Comm& comm, int broadcaster) const
    {
	BoundedMesh::broadcast(comm, broadcaster);

	normal_.broadcast(comm, broadcaster);
    }


    void Boundary::recv(const MPI_Comm& comm, int sender)
    {
	BoundedMesh::recv(comm, sender);

	normal_.recv(comm, sender);
    }


    void Boundary::send(const MPI_Comm& comm, int receiver) const
    {
	BoundedMesh::send(comm, receiver);

	normal_.send(comm, receiver);
    }


    // private functions


}


// version
// $Id: Boundary.cc,v 1.4 2005/03/11 22:42:42 steve Exp $

// End of file
