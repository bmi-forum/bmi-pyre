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


def dbm():
    from dbm.CodecDBM import CodecDBM
    return CodecDBM()


def odb(name='odb', extension=None):
    from fs.CodecODB import CodecODB
    return CodecODB(name, extension)

# version
__id__ = "$Id: __init__.py,v 1.1.1.1 2005/03/08 16:13:41 aivazis Exp $"

# End of file 
