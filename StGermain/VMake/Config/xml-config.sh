#!/bin/sh

##  Copyright (C) 2005 Victorian Partnership for Advanced Computing (VPAC) Ltd
##  110 Victoria Street, Melbourne, 3053, Australia.
##
##  This library is free software; you can redistribute it and/or
##  modify it under the terms of the GNU Lesser General Public
##  License as published by the Free Software Foundation; either
##  version 2.1 of the License, or (at your option) any later version.
##
##  This library is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
##  Lesser General Public License for more details.
##
##  You should have received a copy of the GNU Lesser General Public
##  License along with this library; if not, write to the Free Software
##  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

parsePackageConfigOptions $@

# Obtain libxml information
if test "${XML2_CONFIG_DEFAULT}x" = "x" ; then
	XML2_CONFIG_DEFAULT=`${WHICH} xml2-config 2> /dev/null`
	if whichFailed "${XML2_CONFIG_DEFAULT}"; then
		XML2_CONFIG_DEFAULT="/usr/bin/xml2-config"
	fi
fi
setValueWithDefault XML2_CONFIG "${XML2_CONFIG_DEFAULT}"
assertValidExecutable "${XML2_CONFIG}" xml2-config

XML_DIR_DEFAULT=`$XML2_CONFIG --prefix`
setValueWithDefault XML_DIR "${XML_DIR_DEFAULT}"

XML_CFLAGS_DEFAULT=`$XML2_CONFIG --cflags`
setValueWithDefault XML_CFLAGS "${XML_CFLAGS_DEFAULT}"

XML_INCLUDES_DEFAULT=`$XML2_CONFIG --cflags`
setValueWithDefault XML_INCLUDES "${XML_CFLAGS_DEFAULT}"

XML_LIBS_DEFAULT=`$XML2_CONFIG --libs`
setValueWithDefault XML_LIBS "${XML_LIBS_DEFAULT}"
