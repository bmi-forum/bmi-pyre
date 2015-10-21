// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#if !defined(pyExchanger_Outlet_h)
#define pyExchanger_Outlet_h

namespace Exchanger {

    class Source;


    class Outlet {
    protected:
	const Source& source;

    public:
	Outlet(const Source& source);
	virtual ~Outlet();

	virtual void send() = 0;

    private:
	// disable copy c'tor and assignment operator
	Outlet(const Outlet&);
	Outlet& operator=(const Outlet&);

    };


}


#endif

// version
// $Id: Outlet.h,v 1.1 2004/05/08 01:51:14 tan2 Exp $

// End of file
