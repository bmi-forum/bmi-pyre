// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#if !defined(pyExchanger_Inlet_h)
#define pyExchanger_Inlet_h

namespace Exchanger {

    class BoundedMesh;
    class Sink;


    class Inlet {
    protected:
	const BoundedMesh& mesh;
	const Sink& sink;
	double fge_t;
	double cge_t;

    public:
	Inlet(const BoundedMesh& boundedMesh, const Sink& s);
	virtual ~Inlet();

	void storeTimestep(double fge_t, double cge_t);
	virtual void recv() = 0;
	virtual void impose() = 0;

    protected:
	void getTimeFactors(double& N1, double& N2) const;

    private:
	// disable copy c'tor and assignment operator
	Inlet(const Inlet&);
	Inlet& operator=(const Inlet&);

    };


}


#endif

// version
// $Id: Inlet.h,v 1.1 2004/05/08 01:51:14 tan2 Exp $

// End of file
