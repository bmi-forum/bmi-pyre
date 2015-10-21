// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include <typeinfo>
#include "journal/diagnostics.h"
#include "Array2D.h"
#include "Utility.h"

namespace Exchanger {

    namespace util {

	template <class T>
	void broadcast(const MPI_Comm& comm, int broadcaster, T& data)
	{
	    int size;
	    MPI_Comm_size(comm, &size);
	    if(size == 1) return;

	    int result = MPI_Bcast(&data, 1, datatype(data), broadcaster, comm);
	    testResult(result, "broadcast error!");
	}


	template <class T, int N>
	void broadcast(const MPI_Comm& comm, int broadcaster, Array2D<T,N>& data)
	{
	    int size;
	    MPI_Comm_size(comm, &size);
	    if(size == 1) return;

	    data.broadcast(comm, broadcaster);
	}


	template <class T>
	void exchange(const MPI_Comm& comm, int target, T& data)
	{
	    const int tag = 352;
	    MPI_Status status;

	    int result = MPI_Sendrecv_replace(&data, 1, datatype(data),
					      target, tag,
					      target, tag,
					      comm, &status);
	    testResult(result, "exchange error!");
	}


	template <class T, int N>
	void exchange(const MPI_Comm& comm, int target, Array2D<T,N>& data)
	{
	    // non-blocking send
	    MPI_Request request;
	    Array2D<T,N> data2(data);
	    data2.send(comm, target, request);

	    // blocking receive
	    data.recv(comm, target);

	    waitRequest(request);
	}


	template <class T>
	void gatherSum(const MPI_Comm& comm, T& data)
	{
	    int size;
	    MPI_Comm_size(comm, &size);
	    if(size == 1) return;

	    const int root = 0;
	    T tmp(data);
	    int result = MPI_Reduce(&tmp, &data, 1, datatype(data),
				    MPI_SUM, root, comm);
	    testResult(result, "gatherSum error!");

	    broadcast(comm, root, data);
	}


	template <class T>
	MPI_Datatype datatype(const T&)
	{
	    if (typeid(T) == typeid(double))
		return MPI_DOUBLE;

	    if (typeid(T) == typeid(float))
		return MPI_FLOAT;

	    if (typeid(T) == typeid(int))
		return MPI_INT;

	    if (typeid(T) == typeid(char))
		return MPI_CHAR;

	    journal::firewall_t firewall("UtilTemplate");
	    firewall << journal::at(__HERE__)
		     << "unexpected datatype" << journal::endl;
	    throw std::domain_error("unexpected datatype");
	}

    }
}

// version
// $Id: UtilTemplate.cc,v 1.3 2005/06/03 21:51:47 leif Exp $

// End of file
