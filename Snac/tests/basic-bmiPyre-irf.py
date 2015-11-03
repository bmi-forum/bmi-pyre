#!/usr/bin/env mpipython.exe

from bmiPyre import BmiPyreSnac

def test_irf( filename ):
	model = BmiPyreSnac()
	model.initialize( filename )
	model.update()
	model.finalize()

if __name__ == "__main__":
	test_irf( "./basic.xml" )
