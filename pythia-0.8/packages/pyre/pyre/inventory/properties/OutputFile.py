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


from pyre.inventory.Property import Property


class OutputFile(Property):


    def __init__(self, name, default=None, meta=None, validator=None):
        if default is None:
            import sys
            default = sys.stdout
            
        Property.__init__(self, name, "file", default, meta, validator)

        return


    def _cast(self, value):
        if isinstance(value, basestring):
            if value == "stdout":
                import sys
                value = sys.stdout
            elif value == "stderr":
                import sys
                value = sys.stderr
            else:
                value = file(value, "w")
        
        return value


# version
__id__ = "$Id: OutputFile.py,v 1.2 2005/03/11 06:09:39 aivazis Exp $"

# End of file 
