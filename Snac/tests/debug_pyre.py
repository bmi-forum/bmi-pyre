import StGermain
StGermain.initialise()
import Snac.pyre.Application
a = Snac.pyre.Application.Application()
a.inventory.inputFilename="./basic.xml"
a._dictionary.LoadFromFile( a.inventory.inputFilename )
a.inventory.layout.initialize( a )
a.comm = a.inventory.layout.comm
a.rank = a.inventory.layout.rank
a.nodes = a.inventory.layout.nodes
a.findLayout( a.inventory.layout )

import StGermain.pyre.Bindings.pyre
import Snac.Context
a._stgCommunicator = StGermain.pyre.Bindings.pyre.ConvertFromPyreComm( a.solverCommunicator )

import Snac.Bindings.SnacContext as bindings
bindings.New(a._dictionary._handle, a._stgCommunicator)