#!/usr/bin/env python
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
# <LicenseText>
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#


# factory
def coupler(name="coupler", facility="coupler"):
    return Coupler(name, facility)


from pyre.components.Component import Component



class Coupler(Component):


    def __init__(self, name, facility):
        Component.__init__(self, name, facility)

        self.exchanger = None
        return



    def initialize(self, solver):
        self.exchanger = solver.exchanger
        self.exchanger.initialize(solver)
        return



    def launch(self, solver):
        self.exchanger.launch(solver)
        return



    def initTemperature(self):
        self.exchanger.initTemperature()
        return



    def newStep(self):
        self.exchanger.NewStep()
        return



    def applyBoundaryConditions(self):
        self.exchanger.applyBoundaryConditions()
        return



    def stableTimestep(self, dt):
        dt = self.exchanger.stableTimestep(dt)
        return dt



    def endTimestep(self, done):
        done = self.exchanger.endTimestep(done)
        return done



# version
__id__ = "$Id: Coupler.py,v 1.1 2004/05/18 23:12:26 tan2 Exp $"

# End of file
