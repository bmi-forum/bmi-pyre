// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include "journal/diagnostics.h"
#include "Utility.h"

namespace Exchanger {

    namespace util {

	MPI_Status waitRequest(const MPI_Request& request)
	{
	    MPI_Status status;
	    int result = MPI_Wait(const_cast<MPI_Request*>(&request), &status);
	    testResult(result, "wait error!");

	    return status;
	}


	std::vector<MPI_Status>
	waitRequest(const std::vector<MPI_Request>& request)
	{
	    std::vector<MPI_Status> status(request.size());
	    int result = MPI_Waitall(request.size(),
				     const_cast<MPI_Request*>(&request[0]), &status[0]);
	    testResult(result, "wait error!");

	    return status;
	}


	void testResult(int result, const std::string& errmsg)
	{
	    if (result != MPI_SUCCESS) {
		journal::error_t error("Exchanger-Utility");
		error << journal::at(__HERE__) << errmsg << journal::endl;
		throw result;
	    }
	}


    }
}

// version
// $Id: Utility.cc,v 1.3 2005/06/03 21:51:47 leif Exp $

// End of file
