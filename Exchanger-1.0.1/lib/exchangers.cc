// -*- C++ -*-
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  <LicenseText>
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

#include <Python.h>
#include "mpi.h"
#include "mpi/pympi.h"
#include "BoundedBox.h"
#include "BoundingBox.h"
#include "Convertor.h"
#include "DIM.h"
#include "Inlet.h"
#include "Sink.h"
#include "Outlet.h"
#include "UtilTemplate.h"
#include "Utility.h"
#include "exchangers.h"

namespace Exchanger {

    void deleteBoundedBox(void* p);
    void deleteBoundingBoxes(void* p);
    void deleteSink(void*);

}

using namespace Exchanger;


char PyExchanger_exchangeBoundedBox__doc__[] = "";
char PyExchanger_exchangeBoundedBox__name__[] = "exchangeBoundedBox";

PyObject * PyExchanger_exchangeBoundedBox(PyObject *, PyObject *args)
{
    PyObject *obj0, *obj1, *obj2;
    int target;

    if (!PyArg_ParseTuple(args, "OOOi:exchangeBoundedBox",
                          &obj0, &obj1, &obj2, &target))
        return NULL;

    BoundedBox* bbox = static_cast<BoundedBox*>(PyCObject_AsVoidPtr(obj0));

    PyMPICommObject *temp1 = (PyMPICommObject*)obj1;
    MPI_Comm mycomm = temp1->comm;

    const int leader = 0;
    int rank;
    MPI_Comm_rank(mycomm, &rank);

    // copy contents of bbox to newbbox
    BoundedBox* newbbox = new BoundedBox(*bbox);

    if(rank == leader) {
        PyMPICommObject* temp2 = (PyMPICommObject*)obj2;
        MPI_Comm intercomm = temp2->comm;

        // convert before sending
        Convertor& convertor = Convertor::instance();
        convertor.coordinate(*newbbox);

        util::exchange(intercomm, target, *newbbox);

        // unconvert after receiving
        convertor.xcoordinate(*newbbox);
    }

    util::broadcast(mycomm, leader, *newbbox);
    newbbox->print("Exchanger-exchangers-RemoteBBox");

    PyObject *cobj = PyCObject_FromVoidPtr(newbbox, deleteBoundedBox);
    return Py_BuildValue("N", cobj);
}


char PyExchanger_exchangeBoundingBox__doc__[] = "";
char PyExchanger_exchangeBoundingBox__name__[] = "exchangeBoundingBox";

PyObject * PyExchanger_exchangeBoundingBox(PyObject *, PyObject *args)
{
    PyObject *obj0, *obj1, *obj2;
    int target;

    if (!PyArg_ParseTuple(args, "OOOi:exchangeBoundingBox",
                          &obj0, &obj1, &obj2, &target))
        return NULL;

    BoundingBox* box = static_cast<BoundingBox*>(PyCObject_AsVoidPtr(obj0));

    PyMPICommObject* temp1 = (PyMPICommObject*)obj1;
    MPI_Comm mycomm = temp1->comm;

    const int leader = 0;
    int rank;
    MPI_Comm_rank(mycomm, &rank);

    BoundingBox* my_boxes = gatherBoundingBox(mycomm, leader, box);
    BoundingBox* remote_boxes;

    if(rank == leader) {
        PyMPICommObject* temp2 = (PyMPICommObject*)obj2;
        MPI_Comm intercomm = temp2->comm;

	int my_comm_size;
	MPI_Comm_size(mycomm, &my_comm_size);

	remote_boxes = exchangeBoundingBox(intercomm, target,
					   my_boxes, my_comm_size);
    }

    broadcastBoundingBox(mycomm, leader, remote_boxes);

    PyObject *cobj = PyCObject_FromVoidPtr(remote_boxes, deleteBoundingBoxes);
    return Py_BuildValue("N", cobj);
}


char PyExchanger_exchangeSignal__doc__[] = "";
char PyExchanger_exchangeSignal__name__[] = "exchangeSignal";

PyObject * PyExchanger_exchangeSignal(PyObject *, PyObject *args)
{
    int signal;
    PyObject *obj1, *obj2;
    int target;

    if (!PyArg_ParseTuple(args, "iOOi:exchangeTimestep",
                          &signal, &obj1, &obj2, &target))
        return NULL;

    PyMPICommObject* temp1 = (PyMPICommObject*)obj1;
    MPI_Comm mycomm = temp1->comm;

    const int leader = 0;
    int rank;
    MPI_Comm_rank(mycomm, &rank);

    if(rank == leader) {
        PyMPICommObject* temp2 = (PyMPICommObject*)obj2;
        MPI_Comm intercomm = temp2->comm;

        util::exchange(intercomm, target, signal);
    }

    util::broadcast(mycomm, leader, signal);

    return Py_BuildValue("i", signal);
}


char PyExchanger_exchangeTimestep__doc__[] = "";
char PyExchanger_exchangeTimestep__name__[] = "exchangeTimestep";

PyObject * PyExchanger_exchangeTimestep(PyObject *, PyObject *args)
{
    double dt;
    PyObject *obj1, *obj2;
    int target;

    if (!PyArg_ParseTuple(args, "dOOi:exchangeTimestep",
                          &dt, &obj1, &obj2, &target))
        return NULL;

    PyMPICommObject* temp1 = (PyMPICommObject*)obj1;
    MPI_Comm mycomm = temp1->comm;

    const int leader = 0;
    int rank;
    MPI_Comm_rank(mycomm, &rank);

    if(rank == leader) {
        PyMPICommObject* temp2 = (PyMPICommObject*)obj2;
        MPI_Comm intercomm = temp2->comm;

        Convertor& convertor = Convertor::instance();
        convertor.time(dt);

        util::exchange(intercomm, target, dt);

        convertor.xtime(dt);
    }

    util::broadcast(mycomm, leader, dt);

    return Py_BuildValue("d", dt);
}


char PyExchanger_Inlet_impose__doc__[] = "";
char PyExchanger_Inlet_impose__name__[] = "Inlet_impose";

PyObject * PyExchanger_Inlet_impose(PyObject *, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O:Inlet_impose", &obj))
        return NULL;

    Inlet* inlet = static_cast<Inlet*>(PyCObject_AsVoidPtr(obj));

    inlet->impose();

    Py_INCREF(Py_None);
    return Py_None;
}


char PyExchanger_Inlet_recv__doc__[] = "";
char PyExchanger_Inlet_recv__name__[] = "Inlet_recv";

PyObject * PyExchanger_Inlet_recv(PyObject *, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O:Inlet_recv", &obj))
        return NULL;

    Inlet* inlet = static_cast<Inlet*>(PyCObject_AsVoidPtr(obj));

    inlet->recv();

    Py_INCREF(Py_None);
    return Py_None;
}


char PyExchanger_Inlet_storeTimestep__doc__[] = "";
char PyExchanger_Inlet_storeTimestep__name__[] = "Inlet_storeTimestep";

PyObject * PyExchanger_Inlet_storeTimestep(PyObject *self, PyObject *args)
{
    PyObject *obj;
    double fge_t, cge_t;

    if (!PyArg_ParseTuple(args, "Odd:Inlet_storeTimestep",
                          &obj, &fge_t, &cge_t))
        return NULL;

    Inlet* inlet = static_cast<Inlet*>(PyCObject_AsVoidPtr(obj));

    inlet->storeTimestep(fge_t, cge_t);

    Py_INCREF(Py_None);
    return Py_None;
}


char PyExchanger_Outlet_send__doc__[] = "";
char PyExchanger_Outlet_send__name__[] = "Outlet_send";

PyObject * PyExchanger_Outlet_send(PyObject *, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O:Outlet_send", &obj))
        return NULL;

    Outlet* outlet = static_cast<Outlet*>(PyCObject_AsVoidPtr(obj));

    outlet->send();

    Py_INCREF(Py_None);
    return Py_None;
}


char PyExchanger_Sink_create__doc__[] = "";
char PyExchanger_Sink_create__name__[] = "Sink_create";

PyObject * PyExchanger_Sink_create(PyObject *self, PyObject *args)
{
    PyObject *obj1, *obj2;
    int numSrc;

    if (!PyArg_ParseTuple(args, "OiO:Sink_create",
                          &obj1, &numSrc, &obj2))
        return NULL;

    PyMPICommObject* temp = (PyMPICommObject*)obj1;
    MPI_Comm comm = temp->comm;

    BoundedMesh* b = static_cast<BoundedMesh*>(PyCObject_AsVoidPtr(obj2));

    Sink* sink = new Sink(comm, numSrc, *b);

    PyObject *cobj = PyCObject_FromVoidPtr(sink, deleteSink);
    return Py_BuildValue("O", cobj);
}


// helper functions

namespace Exchanger {

    void deleteBoundedBox(void* p)
    {
	delete static_cast<BoundedBox*>(p);
    }


    void deleteBoundingBoxes(void* p)
    {
	delete [] static_cast<BoundingBox*>(p);
    }


    void deleteSink(void* p)
    {
	delete static_cast<Sink*>(p);
    }

}

// version
// $Id: exchangers.cc,v 1.3 2005/03/11 22:42:43 steve Exp $

// End of file
