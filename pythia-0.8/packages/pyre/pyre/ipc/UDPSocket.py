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


from Socket import Socket


class UDPSocket(Socket):


    def __init__(self):
        Socket.__init__(self, type=self.SOCK_DGRAM)
        return


# version
__id__ = "$Id: UDPSocket.py,v 1.1.1.1 2005/03/08 16:13:41 aivazis Exp $"

# End of file 
