// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#if !defined(pyExchanger_BoundedBox_h)
#define pyExchanger_BoundedBox_h

#include "Array2D.h"
#include "DIM.h"


namespace Exchanger {

    typedef Array2D<double,2> BoundedBox;

    bool isOverlapped(const BoundedBox& lhs,
		      const BoundedBox& rhs);

    bool isInside(const std::vector<double>& x,
		  const BoundedBox& bbox);

}

#endif

// version
// $Id: BoundedBox.h,v 1.1 2004/05/08 01:51:14 tan2 Exp $

// End of file
