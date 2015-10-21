// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include <vector>
#include "BoundedBox.h"


namespace Exchanger {

    bool isOverlapped(const BoundedBox& lhs,
		      const BoundedBox& rhs)
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

	if((lhs[0][0] <= rhs[0][0])&& (lhs[1][0] >= rhs[1][0])&&
	   (lhs[0][1] <= rhs[0][1])&& (lhs[1][1] >= rhs[1][1])&&
	   (lhs[0][2] <= rhs[0][2])&& (lhs[1][2] >= rhs[1][2]))
	    return true;
	// more general critetion
	else if( (lhs[0][0]<=rhs[1][0] && lhs[1][0]>=rhs[0][0]) &&
		 (lhs[0][1]<=rhs[1][1] && lhs[1][1]>=rhs[0][1]) &&
		 (lhs[0][2]<=rhs[1][2] && lhs[1][2]>=rhs[0][2]) )
		return true;

	return false;
    }


    bool isInside(const std::vector<double>& x,
		  const BoundedBox& bbox)
    {
	bool inside = true;
	for(int m=0; m<DIM; m++)
	    if(x[m] < bbox[0][m] ||
	       x[m] > bbox[1][m]) {
		inside = false;
		break;
	    }

	return inside;
    }


}

// version
// $Id: BoundedBox.cc,v 1.3 2005/03/11 22:42:42 steve Exp $

// End of file
