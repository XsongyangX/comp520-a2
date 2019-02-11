# Assignment 2

Song Yang 260744153

Assignment description: https://www.cs.mcgill.ca/~cs520/2019/assignments/Assignment2.pdf

Language specification: https://www.cs.mcgill.ca/~cs520/2019/assignments/Assignment2_Specifications.pdf

Grading rubric: https://www.cs.mcgill.ca/~cs520/2019/assignments/Assignment2_Rubric.pdf

Reference compiler: ssh teaching.cs.mcgill.ca, then run ~cs520/minic

To organize your assignments and project for class, please follow the skeleton provided in this repository.

We provide 3 scripts for convenience and two directories for organization:

* `programs`: Test programs are organized by compilation phase and by expected result. Valid programs should output `OK` and status code `0`, while invalid programs should output `Error: <description>` and status code `1`.
  * `Scan+parse`: Runs both the scanner and parser phases
  * `Typecheck`: Runs until the end of the typechecker phase
  * `Codegen`: Runs until your compiler outputs the target code
* `src`: Source code for your assignment
* `build.sh`: Builds your compiler using `Make` or similar. You should replace the commands here if necessary to build your compiler
* `execute.sh`: Runs the compiled code.
* `run.sh`: Runs your compiler using two arguments (mode - $1 and input file - $2). You should replace the commands here if necessary to invoke your compiler
* `test.sh`: Automatically runs your compiler against test programs in the programs directory and checks the output

Comments found in both files provide more details as to the requirements. Since a large portion of grading is performed automatically, please ensure to follow the input/output specifications **exactly**. You must be able to run the provided scripts on the SOCS Trottier machines.
----------
There are additional scripts (Bash and Python) in this repository.

If there are not around 700 invalid files in the typechecking folder, run `generate.py` with argument `generate`.

* `prettyCheck.sh`: Runs the pretty printer and pretty comparator
* `prettyCompare.py`: Compares the files printed by the pretty printer, called by `prettyCheck.sh`
* `programs`
  * `Typecheck`
    *  `generate.py`: Generates invalid programs for type checking
	*  `invalidate.sh`: Ensures that the programs are indeed invalid by using the reference compiler
