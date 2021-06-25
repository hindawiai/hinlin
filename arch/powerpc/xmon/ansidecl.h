<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* ANSI and traditional C compatibility macros
   Copyright 1991, 1992 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

 */

/* ANSI and traditional C compatibility macros

   ANSI C is assumed अगर __STDC__ is #घोषणाd.

   Macro	ANSI C definition	Traditional C definition
   -----	---- - ----------	----------- - ----------
   PTR		`व्योम *'		`char *'
   LONG_DOUBLE	`दीर्घ द्विगुन'		`double'
   VOLATILE	`अस्थिर'		`'
   SIGNED	`चिन्हित'		`'
   PTRCONST	`व्योम *स्थिर'		`char *'
   ANSI_PROTOTYPES  1			not defined

   CONST is also defined, but is obsolete.  Just use स्थिर.

   DEFUN (name, arglist, args)

	Defines function NAME.

	ARGLIST lists the arguments, separated by commas and enबंदd in
	parentheses.  ARGLIST becomes the argument list in traditional C.

	ARGS list the arguments with their types.  It becomes a prototype in
	ANSI C, and the type declarations in traditional C.  Arguments should
	be separated with `AND'.  For functions with a variable number of
	arguments, the last thing listed should be `DOTS'.

   DEFUN_VOID (name)

	Defines a function NAME, which takes no arguments.

   obsolete --     EXFUN (name, (prototype))	-- obsolete.

	Replaced by PARAMS.  Do not use; will disappear someday soon.
	Was used in बाह्यal function declarations.
	In ANSI C it is `NAME PROTOTYPE' (so PROTOTYPE should be enबंदd in
	parentheses).  In traditional C it is `NAME()'.
	For a function that takes no arguments, PROTOTYPE should be `(व्योम)'.

    PARAMS ((args))

	We could use the EXFUN macro to handle prototype declarations, but
	the name is misleading and the result is ugly.  So we just define a
	simple macro to handle the parameter lists, as in:

	      अटल पूर्णांक foo PARAMS ((पूर्णांक, अक्षर));

	This produces:  `अटल पूर्णांक foo();' or `static int foo (int, char);'

	EXFUN would have करोne it like this:

	      अटल पूर्णांक EXFUN (foo, (पूर्णांक, अक्षर));

	but the function is not बाह्यal...and it's hard to visually parse
	the function name out of the mess.   EXFUN should be considered
	obsolete; new code should be written to use PARAMS.

    For example:
	बाह्य पूर्णांक म_लिखो PARAMS ((CONST अक्षर *क्रमmat DOTS));
	पूर्णांक DEFUN(ख_लिखो, (stream, क्रमmat),
		  खाता *stream AND CONST अक्षर *क्रमmat DOTS) अणु ... पूर्ण
	व्योम DEFUN_VOID(पात) अणु ... पूर्ण
*/

#अगर_अघोषित	_ANSIDECL_H

#घोषणा	_ANSIDECL_H	1


/* Every source file includes this file,
   so they will all get the चयन क्रम lपूर्णांक.  */
/* LINTLIBRARY */


#अगर defined (__STDC__) || defined (_AIX) || (defined (__mips) && defined (_SYSTYPE_SVR4)) || defined(WIN32)
/* All known AIX compilers implement these things (but करोn't always
   define __STDC__).  The RISC/OS MIPS compiler defines these things
   in SVR4 mode, but करोes not define __STDC__.  */

#घोषणा	PTR		व्योम *
#घोषणा	PTRCONST	व्योम *CONST
#घोषणा	LONG_DOUBLE	दीर्घ द्विगुन

#घोषणा	AND		,
#घोषणा	NOARGS		व्योम
#घोषणा	CONST		स्थिर
#घोषणा	VOLATILE	अस्थिर
#घोषणा	SIGNED		चिन्हित
#घोषणा	DOTS		, ...

#घोषणा	EXFUN(name, proto)		name proto
#घोषणा	DEFUN(name, arglist, args)	name(args)
#घोषणा	DEFUN_VOID(name)		name(व्योम)

#घोषणा PROTO(type, name, arglist)	type name arglist
#घोषणा PARAMS(paramlist)		paramlist
#घोषणा ANSI_PROTOTYPES			1

#अन्यथा	/* Not ANSI C.  */

#घोषणा	PTR		अक्षर *
#घोषणा	PTRCONST	PTR
#घोषणा	LONG_DOUBLE	द्विगुन

#घोषणा	AND		;
#घोषणा	NOARGS
#घोषणा	CONST
#अगर_अघोषित स्थिर /* some प्रणालीs define it in header files क्रम non-ansi mode */
#घोषणा	स्थिर
#पूर्ण_अगर
#घोषणा	VOLATILE
#घोषणा	SIGNED
#घोषणा	DOTS

#घोषणा	EXFUN(name, proto)		name()
#घोषणा	DEFUN(name, arglist, args)	name arglist args;
#घोषणा	DEFUN_VOID(name)		name()
#घोषणा PROTO(type, name, arglist) type name ()
#घोषणा PARAMS(paramlist)		()

#पूर्ण_अगर	/* ANSI C.  */

#पूर्ण_अगर	/* ansidecl.h	*/
