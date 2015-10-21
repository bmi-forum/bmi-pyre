#!/usr/bin/env python
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
# <LicenseText>
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#

from mpi.Application import Application
import journal


class CoupledApp(Application):


    def __init__(self, name="coupled-application"):
        Application.__init__(self, name)

        self.solver = None
        self.solverCommunicator = None
        self.myPlus = []
        self.remotePlus = []

        self.comm = None
        self.rank = 0
        self.nodes = 0

        self._info = journal.debug(name)
        return



    def main(self, *args, **kwds):
        self.initialize()
        self.reportConfiguration()
        self.launch()
        return



    def initialize(self):
        layout = self.inventory.layout
        layout.initialize(self)

        self.findLayout(layout)

        controller = self.inventory.controller
        controller.initialize(self)

        return



    def findLayout(self, layout):

        if layout.coarse:
            self.solver = self.inventory.coarse
            self.exchanger = self.inventory.cge
            self.solverCommunicator = layout.coarse
            self.myPlus = layout.coarsePlus
            self.remotePlus = layout.finePlus
        elif layout.fine:
            self.solver = self.inventory.fine
            self.exchanger = self.inventory.fge
            self.solverCommunicator = layout.fine
            self.myPlus = layout.finePlus
            self.remotePlus = layout.coarsePlus
        else:
            import journal
            journal.warning(self.name).log("node '%d' is an orphan"
                                           % layout.rank)
        return



    def reportConfiguration(self):

        import mpi
        rank = mpi.world().rank

        if rank != 0:
            return

        self._info.line("configuration:")
        self._info.line("  properties:")
        self._info.line("    name: %r" % self.name)
        self._info.line("    steps: %d" % self.inventory.steps)

        self._info.line("  facilities:")
        self._info.line("    journal: %r" % self.inventory.journal.name)
        self._info.line("    launcher: %r" % self.inventory.launcher.name)
        self._info.line("    layout: %r" % self.inventory.layout.name)
        self._info.line("    controller: %r" % self.inventory.controller.name)
        self._info.line("    coupler: %r" % self.inventory.coupler.name)
        self._info.line("    coarse: %r" % self.inventory.coarse.name)
        self._info.line("    fine: %r" % self.inventory.fine.name)
        self._info.line("    cge: %r" % self.inventory.cge.name)
        self._info.line("    fge: %r" % self.inventory.fge.name)

        return



    def launch(self):
        controller = self.inventory.controller
        controller.launch(self)

        controller.march(steps=self.inventory.steps)
        return



    class Inventory(Application.Inventory):

        import pyre.inventory
        import pyre.simulations.SimulationController as Controller
        import pyre.simulations.Solver as Solver

        import Coupler
        import Layout
        import Exchanger


        controller = pyre.inventory.facility("controller", factory=Controller.controller)
        coupler = pyre.inventory.facility("coupler", factory=Coupler.coupler)
        layout = pyre.inventory.facility("layout", factory=Layout.layout)

        coarse = pyre.inventory.facility("coarse", factory=Solver)
        fine = pyre.inventory.facility("fine", factory=Solver)
        cge = pyre.inventory.facility("cge", factory=Exchanger.coarsegridexchanger)
        fge = pyre.inventory.facility("fge", factory=Exchanger.finegridexchanger)

        steps = pyre.inventory.int("steps", default=1)




# main
if __name__ == "__main__":

    app = CoupledApp()
    app.run()



# version
__id__ = "$Id: CoupledApp.py,v 1.3 2005/06/08 01:55:34 leif Exp $"

# End of file
