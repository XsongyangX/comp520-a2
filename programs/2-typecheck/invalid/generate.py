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
"&&": "and", "||": "or", "==": "equals", "!=": "neq", "<": "lesser", ">": "greater",\
"<=": "leq", ">=": "geq", "!": "not"}
OP_UNARY = ['-', '!']
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
	
	def invalidCombination(type1, type2, returnType, validSet):
		
		if (type1, type2, returnType) not in validSet:
			return True
		
		return False
	
	def invalidUnary(unary, returnType, validSet):
		if (unary, returnType) not in validSet:
			return True
		return False
	
	combinations = [(type1, type2, returnType) \
	for type1 in TYPES for type2 in TYPES for returnType in TYPES]
	unaryCombinations = [(unary, returnType) for unary in TYPES\
	for returnType in TYPES]
	
	# math operations
	for op in OP_MATH:
		for combination in combinations:
			type1, type2, returnType = combination
			if invalidCombination(type1, type2, returnType, VALID_OP_MATH):
				
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
				
	# boolean operations
	for op in OP_BOOL:
		for combination in combinations:
			type1, type2, returnType = combination
			if invalidCombination(type1, type2, \
			returnType, [('boolean', 'boolean', 'boolean')]):
				
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
	
	# compare operations
	for op in OP_COMPARE:
		for combination in combinations:
			type1, type2, returnType = combination
			if invalidCombination(type1, type2, \
			returnType, [('boolean', 'boolean', 'boolean'),\
			('int', 'int', 'boolean'), ('float', 'float', 'boolean'),\
			('string', 'string', 'boolean')]):
				
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

	# unary operations
	# unary minus
	op = '-'
	for combination in unaryCombinations:
		unary, returnType = combination
		if invalidUnary(unary, returnType, \
		[('int', 'boolean'), ('float', 'boolean')]):
				
			# form the program to print
			comment = "//" + operationsTypeConflict.__doc__ + "\n"
			code = "var a: " + unary + ";\n"\
			+ "var return: " + returnType + " = " + op + "a;"
			fileName = "uminus" + unary.capitalize() + returnType.capitalize() + ".min"
			
			if delete:
				try:
					os.remove(fileName)
				except FileNotFoundError as e:
					print(str(e))
					continue
			else:
				writeToFile(comment, code, fileName)
				
	# unary not
	op = '!'
	for combination in unaryCombinations:
		unary, returnType = combination
		if invalidUnary(unary, returnType,\
		[('boolean', 'boolean')]):
				
			# form the program to print
			comment = "//" + operationsTypeConflict.__doc__ + "\n"
			code = "var a: " + unary + ";\n"\
			+ "var return: " + returnType + " = " + op + "a;"
			fileName = OP_TO_WORDS[op] + unary.capitalize() + returnType.capitalize() + ".min"
			
			if delete:
				try:
					os.remove(fileName)
				except FileNotFoundError as e:
					print(str(e))
					continue
			else:
				writeToFile(comment, code, fileName)
def main():

	assignmentTypeConflict(delete=True)
	
	operationsTypeConflict(delete=True)
	
	return 
	
# execute only as a script
if __name__ == "__main__":
	main()