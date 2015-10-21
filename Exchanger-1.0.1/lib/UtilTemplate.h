// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#if !defined(pyExchanger_UtilTemplate_h)
#define pyExchanger_UtilTemplate_h

#include "mpi.h"


namespace Exchanger {


    template <class T, int N> class Array2D;

    namespace util {

	template <class T>
	void broadcast(const MPI_Comm& comm, int broadcaster, T& data);

	template <class T, int N>
	void broadcast(const MPI_Comm& comm, int broadcaster, Array2D<T,N>& data);

	template <class T>
	void exchange(const MPI_Comm& comm, int target, T& data);

	template <class T, int N>
	void exchange(const MPI_Comm& comm, int target, Array2D<T,N>& data);

	template <class T>
	void gatherSum(const MPI_Comm& comm, T& data);

	template <class T>
	inline MPI_Datatype datatype(const T&);

    }
}

#include "UtilTemplate.cc"


#endif

// version
// $Id: UtilTemplate.h,v 1.1 2004/05/08 01:51:14 tan2 Exp $

// End of file
