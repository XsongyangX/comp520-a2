#!/usr/bin/python3

"""
Generate all simple invalid program for type checking.
"""

TYPES = ['int', 'float', 'string', 'boolean']
VALID_ASSIGNMENT = [('int', 'int'), ('float', 'float'), ('float', 'int'),\
('string', 'string'), ('boolean', 'boolean')]
VAR_INITIALIZATION = {'int': 0, 'float': 0.0, 'string': "\"\"", 'boolean': 'false'}
OP_MATH = ['+', '-', '*', '/']
VALID_OP_MATH = [('int', 'int', 'int'), ('float', 'float', 'float'),\
('int', 'float', 'float'), ('float', 'int', 'float'), ('string', 'string', 'string'),\
('int', 'int', 'float')]
OP_BOOL = ['&&', '||']
OP_COMPARE = ['==', '!=', '<', '>', '<=', '>=']
OP_TO_WORDS = {'+': "add", "-": "minus", "*": "times", "/": "divide",\
"&&": "and", "||": "or", "==": "equals", "!=": "not", "<": "lesser", ">": "greater",\
"<=": "leq", ">=": "geq"}
def writeToFile(comment, code, fileName):

	with open(fileName, "w") as file:
		file.write(comment + code)
	
	return

def assignmentTypeConflict(delete=False):
	"""Invalid assignment type """
	
	if delete:
		import os
	
	def invalidCombination(storage, assigned):
	
		if (storage, assigned) not in VALID_ASSIGNMENT:
			return True
	
		return False
	
	
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
				"a = b;"
				
				# generate a meaningful fileName
				target = storage.capitalize() + assigned.capitalize()
				fileNameDirect = "dirAssign" + target + ".min"
				fileNameIndirect = "indirAssign" + target + ".min"
				
				if delete:
					os.remove(fileNameDirect)
					os.remove(fileNameIndirect)
				else:
					writeToFile(comment, directAssignment, fileNameDirect)
					writeToFile(comment, indirectAssignment, fileNameIndirect)
	
	return

def operationsTypeConflict(delete=False):
	"""Invalid operation on certain types """
	
	if delete:
		import os
	
	def invalidCombination(type1, type2, returnType):
		
		if (type1, type2, returnType) not in VALID_OP_MATH:
			return True
		
		return False
	
	# math operations
	for op in OP_MATH:
		combinations = [(type1, type2, returnType) \
		for type1 in TYPES for type2 in TYPES for returnType in TYPES]
		
		for combination in combinations:
			type1, type2, returnType = combination
			if invalidCombination(type1, type2, returnType):
				
				# form the program to print
				comment = "//" + operationsTypeConflict.__doc__ + "\n"
				code = "var a: " + type1 + ";\n"\
				+ "var b: " + type2 + ";\n"\
				+ "var return: " + returnType + " = a " + op + " b;"
				fileName = OP_TO_WORDS[op] + type1.capitalize() + type2.capitalize() \
				+ returnType.capitalize() + ".min"
				
				if delete:
					os.remove(fileName)
				else:
					writeToFile(comment, code, fileName)
				
def main():

	assignmentTypeConflict(delete=False)
	
	operationsTypeConflict(delete=False)
	
	return 
	
# execute only as a script
if __name__ == "__main__":
	main()