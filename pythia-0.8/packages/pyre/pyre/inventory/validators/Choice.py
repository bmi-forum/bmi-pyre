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


class Choice(Binary):


    def __call__(self, candidate):
        if candidate in self.value:
            return candidate

        raise ValueError("%r is not %s" % (candidate, self))


    def __str__(self):
        return "(in %r)" % (self.value)


# version
__id__ = "$Id: Choice.py,v 1.2 2005/03/10 04:03:19 aivazis Exp $"

# End of file 
