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

class PythonMill(LineMill):


    names = ["python"]


    def __init__(self):
        LineMill.__init__(self, "#", "#!/usr/bin/env python")
        return


    def _versionId(self):
        format = self._options.versionId

        if format:
            self._rep += [
                '', self.line(" version"), '__id__ = "' + format.strip() + '"'
                ]

        return


# version
__id__ = "$Id: PythonMill.py,v 1.1.1.1 2005/03/08 16:13:47 aivazis Exp $"

#  End of file 
