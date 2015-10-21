// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
// Purpose:
// convert/unconvert quantities exchanged to SI unit
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#if !defined(pyExchanger_SIUnit_h)
#define pyExchanger_SIUnit_h

#include "Array2D.h"
#include "BoundedBox.h"
#include "BoundingBox.h"
#include "DIM.h"


namespace Exchanger {

    // singleton class

    class SIUnit {
    protected:
	double length_factor;
	double velocity_factor;
	double temperature_factor;
	double temperature_offset;
	double time_factor;
	double traction_factor;
	double stress_factor;

    public:
	SIUnit();
	virtual ~SIUnit() = 0;

	// dimensionalize
	void coordinate(BoundedBox& bbox) const;
	void coordinate(BoundingBox& bbox) const;
	void coordinate(Array2D<double,DIM>& X) const;
	void temperature(Array2D<double,1>& T) const;
	void time(double& t) const;
	void traction(Array2D<double,DIM>& F) const;
	void stress(Array2D<double,STRESS_DIM>& S) const;
	void velocity(Array2D<double,DIM>& V) const;

	// non-dimensionalize
	void xcoordinate(BoundedBox& bbox) const;
	void xcoordinate(BoundingBox& bbox) const;
	void xcoordinate(Array2D<double,DIM>& X) const;
	void xtemperature(Array2D<double,1>& T) const;
	void xtime(double& t) const;
	void xtraction(Array2D<double,DIM>& F) const;
	void xstress(Array2D<double,STRESS_DIM>& S) const;
	void xvelocity(Array2D<double,DIM>& V) const;

    private:
	// disable
	SIUnit(const SIUnit&);
	SIUnit& operator=(const SIUnit&);

    };


}


#endif

// version
// $Id: SIUnit.h,v 1.4 2005/01/29 00:05:43 ces74 Exp $

// End of file
