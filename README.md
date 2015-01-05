/******************************************************************************************************/
/*** The Python version (a much more efficient one) is under works outside this repo, stay tuned!!! ***/
/******************************************************************************************************/

Initial Release of SHC

Top features:

1. "ShortHand functions" module :
		Functions for matrix and string added. Basic usage of some of the main functions is as follows :-

		1)To input a matrix

		matrixin(&r,&c,mat);

		ARGUMENTS :

		&r	: no of rows
		&c	: no of columns
		mat	: matrix name 

		2)To add two matrices

		matrixadd(&r,&c,&a,&b,mat,matr,sum);

		ARGUMENTS :

		&r	: no of rows of first matrix
		&c	: no of columns of first matrix
		&a	: no of rows of second matrix
		&b	: no of columns of second matrix
		mat	: name of the first matrix
		matr	: name of the second matrix
		sum	: name of the result matrix


		3)To multiply two matrices

		matrixmult(&r,&c,&a,&b,&x,&y,mat,matr,res);

		ARGUMENTS

		&r	: no of rows of first matrix
		&c	: no of columns of first matrix
		&a	: no of rows of second matrix
		&b	: no of columns of second matrix
		&x	: no of rows of result matrix
		&y	: no of columns of result matrix
		mat	: name of the first matrix
		matr	: name of the second matrix
		res	: name of the result matrix


		4)To find the transpose of a matrix

		matrixtrans(&r,&c,mat,tr);

		ARGUMENTS

		&r	: no of rows
		&c	: no of columns
		mat	: matrix name 
		tr	: resultant matrix

		5)To search whether the substring is present or not

		strsearch(s,sr);

		ARGUMENTS

		s	: main string
		sr	: substring

		6)To sort the string given in alphabetical order

		strsort(s);

		ARGUMENTS

		s	: main string

		7)To encrypt and decrypt a particular string

		strencrypt(s);

		ARGUMENTS

		s	: main string

		8)To replace a particular string from the main string

		strreplace(str,str1,str2);


		ARGUMENTS

		s	: main string
		str1	: substring to be replaced
		str2	: replacing string

		9)To copy string from source to destination

		strcopy(source,destination);

		ARGUMENTS

		source	: source string
		destination : destination string

2. Debug, Analyse and Versioning Module:

	Includes shorthands for the respective functions.

3. Graphics Code generation module:

	Includes a WYSIWYG graphics code generator that is capable of generating the code needed for replicating the visuals drawn using mouse.
