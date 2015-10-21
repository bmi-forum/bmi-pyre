// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#if !defined(pyExchanger_Convertor_h)
#define pyExchanger_Convertor_h

#include "Array2D.h"
#include "BoundedBox.h"
#include "BoundingBox.h"
#include "DIM.h"


namespace Exchanger {

    class CartesianCoord;
    class SIUnit;

    // singleton class

    class Convertor {
    protected:
	static SIUnit* si;
	static CartesianCoord* cart;
	static bool inited;

    public:
	~Convertor();

	static Convertor& instance();  // the singleton

	// internal representation ==> standard representation
	void coordinate(BoundedBox& bbox) const;
	void coordinate(BoundingBox& bbox) const;
	void coordinate(Array2D<double,DIM>& X) const;
	void temperature(Array2D<double,1>& T) const;
	void time(double& t) const;
	void traction(Array2D<double,DIM>& F,
		      const Array2D<double,DIM>& X) const;
	void stress(Array2D<double,STRESS_DIM>& S,
		      const Array2D<double,DIM>& X) const;
	void velocity(Array2D<double,DIM>& V,
		      const Array2D<double,DIM>& X) const;

	// standard representation ==> internal representation
	void xcoordinate(BoundedBox& bbox) const;
	void xcoordinate(BoundingBox& bbox) const;
	void xcoordinate(Array2D<double,DIM>& X) const;
	void xtemperature(Array2D<double,1>& T) const;
	void xtime(double& t) const;
	void xtraction(Array2D<double,DIM>& F,
		       const Array2D<double,DIM>& X) const;
	void xstress(Array2D<double,STRESS_DIM>& S,
		       const Array2D<double,DIM>& X) const;
	void xvelocity(Array2D<double,DIM>& V,
		       const Array2D<double,DIM>& X) const;

    private:
	Convertor();

	// disable
	Convertor(const Convertor&);
	Convertor& operator=(const Convertor&);

    };


}

#endif

// version
// $Id: Convertor.h,v 1.5 2005/01/29 00:05:43 ces74 Exp $

// End of file
