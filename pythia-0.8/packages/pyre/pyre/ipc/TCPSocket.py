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


class TCPSocket(Socket):


    def __init__(self):
        Socket.__init__(self, type=self.SOCK_STREAM)
        return


    # constant
    MAX_QUEUE = 10


# version
__id__ = "$Id: TCPSocket.py,v 1.1.1.1 2005/03/08 16:13:41 aivazis Exp $"

# End of file 
