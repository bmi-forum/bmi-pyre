// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#if !defined(pyExchanger_Utility_h)
#define pyExchanger_Utility_h

#include <vector>
#include "mpi.h"

namespace Exchanger {

    namespace util {

	MPI_Status waitRequest(const MPI_Request& request);

	std::vector<MPI_Status>
	waitRequest(const std::vector<MPI_Request>& request);

	void testResult(int result, const std::string& errmsg);

    }

}

#endif

// version
// $Id: Utility.h,v 1.1 2004/05/08 01:51:14 tan2 Exp $

// End of file
