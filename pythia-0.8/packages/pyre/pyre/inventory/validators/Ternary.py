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


from Validator import Validator


class Ternary(Validator):


    def __init__(self, v1, v2):
        self.v1 = v1
        self.v2 = v2
        return


# version
__id__ = "$Id: Ternary.py,v 1.1.1.1 2005/03/08 16:13:44 aivazis Exp $"

# End of file 
