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


class ServiceRequest(object):


    def __init__(self, command, args=None):
        self.command = command

        if args is None:
            args = ()
        self.args = args

        return


# version
__id__ = "$Id: ServiceRequest.py,v 1.1.1.1 2005/03/08 16:13:48 aivazis Exp $"

# End of file 
