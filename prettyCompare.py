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

	print("in " + str(folder))
	
	for sourceFile in os.listdir(os.path.join("pretty/", folder)):
		
		with open(os.path.join("pretty/", folder, sourceFile), "r") as prettyPrint:
		
			with open(os.path.join("pretty/", folder, "compare", sourceFile as \
			prettyPrint2:
				
				# pretty print identity does not hold
				if (str(prettyPrint) != str(prettyPrint2)):
				
					print("identity violated :" + str(sourceFile))

# destroy pretty folder if wanted
if (sys.argv[1] == "destroy"):
	os.removedirs("pretty")
