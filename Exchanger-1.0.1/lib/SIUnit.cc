// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include <stdexcept>
#include "SIUnit.h"


namespace Exchanger {


    SIUnit::SIUnit()
    {}


    SIUnit::~SIUnit()
    {}


    void SIUnit::coordinate(BoundedBox& bbox) const
    {
	for(int i=0; i<2; ++i)
	    bbox[i][DIM-1] *= length_factor;
    }


    void SIUnit::coordinate(BoundingBox& bbox) const
    {
	for(int i=0; i<2; ++i)
	    bbox[i][DIM-1] *= length_factor;
    }


    void SIUnit::coordinate(Array2D<double,DIM>& X) const
    {
	for(int i=0; i<X.size(); ++i)
	    X[DIM-1][i] *= length_factor;
    }


    void SIUnit::temperature(Array2D<double,1>& T) const
    {
	for(int i=0; i<T.size(); ++i) {
	    T[0][i] *= temperature_factor;
	    T[0][i] += temperature_offset;
	}
    }


    void SIUnit::time(double& t) const
    {
	t *= time_factor;
    }


    void SIUnit::traction(Array2D<double,DIM>& F) const
    {
	for(int i=0; i<F.size(); ++i)
	    for(int d=0; d<DIM; ++d)
		F[d][i] *= traction_factor;
    }


    void SIUnit::stress(Array2D<double,STRESS_DIM>& S) const
    {
	for(int i=0; i<S.size(); ++i)
	    for(int d=0; d<STRESS_DIM; ++d)
		S[d][i] *= stress_factor;
    }


    void SIUnit::velocity(Array2D<double,DIM>& V) const
    {
	for(int i=0; i<V.size(); ++i)
	    for(int d=0; d<DIM; ++d)
		V[d][i] *= velocity_factor;
    }


    void SIUnit::xcoordinate(BoundedBox& bbox) const
    {
	for(int i=0; i<2; ++i)
	    bbox[i][DIM-1] /= length_factor;
    }


    void SIUnit::xcoordinate(BoundingBox& bbox) const
    {
	for(int i=0; i<2; ++i)
	    bbox[i][DIM-1] /= length_factor;
    }


    void SIUnit::xcoordinate(Array2D<double,DIM>& X) const
    {
	for(int i=0; i<X.size(); ++i)
	    X[DIM-1][i] /= length_factor;
    }


    void SIUnit::xtemperature(Array2D<double,1>& T) const
    {
	for(int i=0; i<T.size(); ++i) {
	    T[0][i] -= temperature_offset;
	    T[0][i] /= temperature_factor;
	}
    }


    void SIUnit::xtime(double& t) const
    {
	t /= time_factor;
    }


    void SIUnit::xtraction(Array2D<double,DIM>& F) const
    {
	for(int i=0; i<F.size(); ++i)
	    for(int d=0; d<DIM; ++d)
		F[d][i] /= traction_factor;
    }


    void SIUnit::xstress(Array2D<double,STRESS_DIM>& S) const
    {
	for(int i=0; i<S.size(); ++i)
	    for(int d=0; d<STRESS_DIM; ++d)
			S[d][i] /= stress_factor;
    }


    void SIUnit::xvelocity(Array2D<double,DIM>& V) const
    {
	for(int i=0; i<V.size(); ++i)
	    for(int d=0; d<DIM; ++d)
		V[d][i] /= velocity_factor;
    }


}


// version
// $Id: SIUnit.cc,v 1.4 2005/03/11 22:42:43 steve Exp $

// End of file
