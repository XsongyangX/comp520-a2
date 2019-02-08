#!/usr/bin/python3

"""
assumes that the program to check are in the folders
created by prettyCheck.sh
"""

import sys
import os

# get argument to decide to remove the directories or not
if len(sys.argv) != 2:
	raise Exception("Needs exactly 1 argument: destroy | keep")
	
# compare files
for folder in os.listdir("pretty"):

	for subfolder in os.listdir(os.path.join("pretty/", folder)):
		print("in" + str(subfolder))
