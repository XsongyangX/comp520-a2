#!/usr/bin/python3

"""
Generate all simple invalid program for type checking.
"""

TYPES = ['int', 'float', 'string', 'boolean']
VALID_ASSIGNMENT = [('int', 'int'), ('float', 'float'), ('float', 'int'),\
('string', 'string'), ('boolean', 'boolean')]
VAR_INITIALIZATION = {'int': 0, 'float': 0.0, 'string': "\"\"", 'boolean': 'false'}

def assignmentTypeConflict():
	"""Invalid assignment type """
	
	def invalidCombination(storage, assigned):
	
		if (storage, assigned) not in VALID_ASSIGNMENT:
			return True
	
		return False
	
	def writeToFile(comment, code, fileName):
	
		with open(fileName, "w") as file:
			file.write(comment + code)
		
		return
	
	for storage in TYPES:
		for assigned in TYPES:
		
			if invalidCombination(storage, assigned):
				
				# form the code
				
				# introductory comment
				comment = "//" + assignmentTypeConflict.__doc__\
				+ storage + ":=" + assigned + "\n"
				
				# direct assignment with the default initialization
				directAssignment = "var a: " + storage + " = "\
				+ str(VAR_INITIALIZATION[assigned]) + ";"
				
				# indirect assignment with declared (but uninitialized) var
				indirectAssignment = "var a: " + storage + ";\n"
				indirectAssignment = indirectAssignment +\
				"var b: " + assigned + ";\n" +\
				"a = b";
				
				# generate a meaningful fileName
				target = storage.capitalize() + assigned.capitalize()
				fileNameDirect = "dirAssign" + target + ".min"
				fileNameIndirect = "indirAssign" + target + ".min"
				
				writeToFile(comment, directAssignment, fileNameDirect)
				writeToFile(comment, indirectAssignment, fileNameIndirect)
	
	return

def main():

	assignmentTypeConflict()
	

	return 
	
# execute only as a script
if __name__ == "__main__":
	main()