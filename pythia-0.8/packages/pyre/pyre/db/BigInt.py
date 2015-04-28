#!/usr/bin/env python
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                             Michael A.G. Aivazis
#                      California Institute of Technology
#                      (C) 1998-2005  All Rights Reserved
#
# {LicenseText}
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#


from Column import Column


class BigInt(Column):


    def type(self):
        return "bigint"


    def __init__(self, **kwds):
        Column.__init__(self, **kwds)
        return


# version
__id__ = "$Id: BigInt.py,v 1.1 2005/04/06 20:46:30 aivazis Exp $"

# End of file 
