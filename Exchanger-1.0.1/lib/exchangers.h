// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#if !defined(PyExchanger_exchangers_h)
#define PyExchanger_exchangers_h


extern char PyExchanger_exchangeBoundedBox__name__[];
extern char PyExchanger_exchangeBoundedBox__doc__[];
extern "C"
PyObject * PyExchanger_exchangeBoundedBox(PyObject *, PyObject *);


extern char PyExchanger_exchangeBoundingBox__name__[];
extern char PyExchanger_exchangeBoundingBox__doc__[];
extern "C"
PyObject * PyExchanger_exchangeBoundingBox(PyObject *, PyObject *);


extern char PyExchanger_exchangeSignal__name__[];
extern char PyExchanger_exchangeSignal__doc__[];
extern "C"
PyObject * PyExchanger_exchangeSignal(PyObject *, PyObject *);


extern char PyExchanger_exchangeTimestep__name__[];
extern char PyExchanger_exchangeTimestep__doc__[];
extern "C"
PyObject * PyExchanger_exchangeTimestep(PyObject *, PyObject *);


extern char PyExchanger_Inlet_impose__name__[];
extern char PyExchanger_Inlet_impose__doc__[];
extern "C"
PyObject * PyExchanger_Inlet_impose(PyObject *, PyObject *);


extern char PyExchanger_Inlet_recv__name__[];
extern char PyExchanger_Inlet_recv__doc__[];
extern "C"
PyObject * PyExchanger_Inlet_recv(PyObject *, PyObject *);


extern char PyExchanger_Inlet_storeTimestep__name__[];
extern char PyExchanger_Inlet_storeTimestep__doc__[];
extern "C"
PyObject * PyExchanger_Inlet_storeTimestep(PyObject *, PyObject *);


extern char PyExchanger_Outlet_send__name__[];
extern char PyExchanger_Outlet_send__doc__[];
extern "C"
PyObject * PyExchanger_Outlet_send(PyObject *, PyObject *);


extern char PyExchanger_Sink_create__name__[];
extern char PyExchanger_Sink_create__doc__[];
extern "C"
PyObject * PyExchanger_Sink_create(PyObject *, PyObject *);


#endif

// version
// $Id: exchangers.h,v 1.2 2004/07/22 04:11:42 tan2 Exp $

// End of file
