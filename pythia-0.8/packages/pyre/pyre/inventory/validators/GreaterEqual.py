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


from Binary import Binary


class GreaterEqual(Binary):


    def __call__(self, candidate):
        if candidate >= self.value:
            return candidate

        raise ValueError("%s is not %s" % (candidate, self))


    def __str__(self):
        return "(greater than or equal to %s)" % (self.value)


# version
__id__ = "$Id: GreaterEqual.py,v 1.2 2005/03/10 04:03:20 aivazis Exp $"

# End of file 
