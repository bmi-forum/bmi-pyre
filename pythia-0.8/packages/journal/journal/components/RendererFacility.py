#!/usr/bin/env python
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                             Michael A.G. Aivazis
#                      California Institute of Technology
#                      (C) 1998-2005  All Rights Reserved
#
# <LicenseText>
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#

from pyre.inventory.Facility import Facility


class RendererFacility(Facility):


    def __init__(self, factory=None, args=[]):

        if factory is None:
            args = []
            from Renderer import Renderer as factory
            
        Facility.__init__(self, name="renderer", factory=factory, args=args)
        return


# version
__id__ = "$Id: RendererFacility.py,v 1.1.1.1 2005/03/08 16:13:53 aivazis Exp $"

# End of file 
