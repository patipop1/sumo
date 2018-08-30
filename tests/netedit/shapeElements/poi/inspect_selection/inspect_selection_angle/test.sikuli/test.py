#!/usr/bin/env python
# Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
# Copyright (C) 2009-2018 German Aerospace Center (DLR) and others.
# This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v2.0
# which accompanies this distribution, and is available at
# http://www.eclipse.org/legal/epl-v20.html
# SPDX-License-Identifier: EPL-2.0

# @file    test.py
# @author  Pablo Alvarez Lopez
# @date    2016-11-25
# @version $Id$

# import common functions for netedit tests
import os
import sys

testRoot = os.path.join(os.environ.get('SUMO_HOME', '.'), 'tests')
neteditTestRoot = os.path.join(
    os.environ.get('TEXTTEST_HOME', testRoot), 'netedit')
sys.path.append(neteditTestRoot)
import neteditTestFunctions as netedit  # noqa

# Open netedit
neteditProcess, match = netedit.setupAndStart(neteditTestRoot, ['--gui-testing-debug-gl'])

# go to select mode
netedit.selectMode()

# select first POI
netedit.leftClick(match, 100, 50)

# select second POI
netedit.leftClick(match, 150, 50)

# go to inspect mode
netedit.inspectMode()

# inspect first POI
netedit.leftClick(match, 100, 50)

# Change parameter 10 with a non valid value (dummy)
netedit.modifyAttribute(10, "dummyAngle")

# Change parameter 10 with a valid value (negative)
netedit.modifyAttribute(10, "-12")

# Change parameter 10 with a valid value (> 360)
netedit.modifyAttribute(10, "500")

# Change parameter 10 with a valid value
netedit.modifyAttribute(10, "30")

# Check undos and redos
netedit.undo(match, 4)
netedit.redo(match, 4)

# save shapes
netedit.saveShapes()

# save network
netedit.saveNetwork()

# quit netedit
netedit.quit(neteditProcess)
