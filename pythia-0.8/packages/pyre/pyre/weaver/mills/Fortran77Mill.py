#!/usr/bin/env python
# 
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 
#                               Michael A.G. Aivazis
#                        California Institute of Technology
#                        (C) 1998-2005 All Rights Reserved
# 
#  <LicenseText>
# 
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 


from pyre.weaver.components.LineMill import LineMill

class Fortran77Mill(LineMill):


    names = ["fortran", "fortran77"]


    def __init__(self):
        LineMill.__init__(self, "c", "c -*- Fortran -*-")
        return


# version
__id__ = "$Id: Fortran77Mill.py,v 1.1.1.1 2005/03/08 16:13:47 aivazis Exp $"

#  End of file 
