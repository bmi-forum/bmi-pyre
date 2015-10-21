// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#if !defined(pyExchanger_CartesianCoord_h)
#define pyExchanger_CartesianCoord_h

#include "Array2D.h"
#include "BoundedBox.h"
#include "BoundingBox.h"
#include "DIM.h"

namespace Exchanger {

    class BoundedMesh;


    class CartesianCoord {

    public:
	CartesianCoord() {};
	virtual ~CartesianCoord() {};

	// Transform to cartesian coordinate system from spherical system
	virtual void coordinate(BoundedBox& bbox) const = 0;
	virtual void coordinate(BoundingBox& bbox) const = 0;
	virtual void coordinate(Array2D<double,DIM>& X) const = 0;
	virtual void vector(Array2D<double,DIM>& V,
			    const Array2D<double,DIM>& X) const = 0;
	virtual void tensor_rank2(Array2D<double,STRESS_DIM>& S,
			    const Array2D<double,DIM>& X) const = 0;

	// Transform to spherical coordinate system from cartesian system
	virtual void xcoordinate(BoundedBox& bbox) const = 0;
	virtual void xcoordinate(BoundingBox& bbox) const = 0;
	virtual void xcoordinate(Array2D<double,DIM>& X) const = 0;
	virtual void xvector(Array2D<double,DIM>& V,
			     const Array2D<double,DIM>& X) const = 0;
	virtual void xtensor_rank2(Array2D<double,STRESS_DIM>& S,
			     const Array2D<double,DIM>& X) const = 0;

    private:
	// disable
	CartesianCoord(const CartesianCoord&);
	CartesianCoord& operator=(const CartesianCoord&);

    };


}


#endif

// version
// $Id: CartesianCoord.h,v 1.4 2005/01/29 00:05:43 ces74 Exp $

// End of file
