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


import win32con, win32file, pywintypes


class FileLockingNT(object):


    LOCK_EX = win32com.LOCKFILE_EXCLUSIVE_LOCK
    LOCK_SH = 0
    LOCK_NB = win32con.LOCKFILE_FAIL_IMMEDIATELY

    OVERLAPPED = pywintypes.OVERLAPPED()


    def lock(self, stream, flags):
        handle = win32file._get_osfhandle(file.fileno())
        return win32file.LockFileEx(handle, flags, 0, 0xffff0000, self.OVERLAPPED)


    def unlock(self, stream):
        handle = win32file._get_osfhandle(file.fileno())
        return win32file.UnlockFileEx(handle, 0, 0xffff0000, self.OVERLAPPED)
    

del win32con
del win32file
del pywintypes


# version
__id__ = "$Id: FileLockingNT.py,v 1.1.1.1 2005/03/08 16:13:41 aivazis Exp $"

# End of file 
