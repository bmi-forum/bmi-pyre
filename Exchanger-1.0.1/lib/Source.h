// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#if !defined(pyExchanger_Source_h)
#define pyExchanger_Source_h

#include <vector>
#include "journal/diagnostics.h"
#include "mpi.h"
#include "Array2D.h"
#include "BoundedBox.h"
#include "DIM.h"
#include "Utility.h"


namespace Exchanger {

    class BoundedMesh;
    class Interpolator;

    class Source {
    protected:
	MPI_Comm comm;
	const int sinkRank;
	Array2D<int,1> meshNode_;
	Array2D<double,DIM> X_;
	Interpolator* interp;

    public:
	Source(MPI_Comm c, int sinkrank,
	       BoundedMesh& mesh, const BoundedBox& mybbox);
	virtual ~Source();

	inline int size() const {return meshNode_.size();}
	inline const Array2D<double,DIM>& getX() const {return X_;}

	virtual void interpolateDisplacement(Array2D<double,DIM>& D) const = 0;
	virtual void interpolateForce(Array2D<double,DIM>& F) const = 0;
	virtual void interpolateHeatflux(Array2D<double,DIM>& H) const = 0;
	virtual void interpolatePressure(Array2D<double,1>& P) const = 0;
	virtual void interpolateStress(Array2D<double,STRESS_DIM>& S) const = 0;
	virtual void interpolateTemperature(Array2D<double,1>& T) const = 0;
	virtual void interpolateTraction(Array2D<double,DIM>& F) const = 0;
	virtual void interpolateVelocity(Array2D<double,DIM>& V) const = 0;

	template <class T, int N>
	void send(const Array2D<T,N>& array) const;

	template <class T1, int N1, class T2, int N2>
	void send(const Array2D<T1,N1>& array1,
		  const Array2D<T2,N2>& array2) const;

    protected:
	void init(BoundedMesh& mesh, const BoundedBox& mybbox);
	virtual void createInterpolator(const BoundedMesh& mesh) = 0;

    private:
	void recvMesh(BoundedMesh& mesh, const BoundedBox& mybbox);
	void sendMeshNode() const;
	void initX(const BoundedMesh& mesh);

	// disable copy c'tor and assignment operator
	Source(const Source&);
	Source& operator=(const Source&);

    };


    template <class T, int N>
    void Source::send(const Array2D<T,N>& array) const
    {
#ifdef DEBUG
	if(size() != array.size()) {
 	    journal::firewall_t firewall("Exchanger-Source");
 	    firewall << journal::at(__HERE__)
 		     << "Source: inconsistenet array size" << journal::endl;
	    throw std::out_of_range("Source");
	}
#endif

	if(size()) {
	    MPI_Request request;
	    array.send(comm, sinkRank, 0, array.size(), request);
	    util::waitRequest(request);
	}
    }


    template <class T1, int N1, class T2, int N2>
    void Source::send(const Array2D<T1,N1>& array1,
		      const Array2D<T2,N2>& array2) const
    {
#ifdef DEBUG
	if(size() != array1.size() || size() != array2.size()) {
 	    journal::firewall_t firewall("Exchanger-Source");
 	    firewall << journal::at(__HERE__)
 		     << "Source: inconsistenet array size" << journal::endl;
	    throw std::out_of_range("Source");
	}
#endif

	if(size()) {
	    std::vector<MPI_Request> request;
	    request.reserve(2);

	    request.push_back(MPI_Request());
	    array1.send(comm, sinkRank, 0, array1.size(), request.back());

	    request.push_back(MPI_Request());
	    array2.send(comm, sinkRank, 0, array2.size(), request.back());

	    util::waitRequest(request);
	}
    }

}
#endif

// version
// $Id: Source.h,v 1.3 2005/06/03 21:51:47 leif Exp $

// End of file
