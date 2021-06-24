<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अघोषित _GNU_SOURCE
#घोषणा _GNU_SOURCE 1
#अघोषित __USE_GNU
#घोषणा __USE_GNU 1
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <संकेत.स>
#समावेश <sys/types.h>
#समावेश <sys/select.h>
#समावेश <sys/समय.स>
#समावेश <sys/रुको.h>
#समावेश <fenv.h>

अचिन्हित दीर्घ दीर्घ res64 = -1;
अचिन्हित पूर्णांक res32 = -1;
अचिन्हित लघु res16 = -1;

पूर्णांक test(व्योम)
अणु
	पूर्णांक ex;

	feclearexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);
	यंत्र अस्थिर ("\n"
	"	fld1""\n"
	"	fisttp	res16""\n"
	"	fld1""\n"
	"	fisttpl	res32""\n"
	"	fld1""\n"
	"	fisttpll res64""\n"
	: : : "memory"
	);
	अगर (res16 != 1 || res32 != 1 || res64 != 1) अणु
		म_लिखो("[BAD]\tfisttp 1\n");
		वापस 1;
	पूर्ण
	ex = fetestexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);
	अगर (ex != 0) अणु
		म_लिखो("[BAD]\tfisttp 1: wrong exception state\n");
		वापस 1;
	पूर्ण

	feclearexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);
	यंत्र अस्थिर ("\n"
	"	fldpi""\n"
	"	fisttp	res16""\n"
	"	fldpi""\n"
	"	fisttpl	res32""\n"
	"	fldpi""\n"
	"	fisttpll res64""\n"
	: : : "memory"
	);
	अगर (res16 != 3 || res32 != 3 || res64 != 3) अणु
		म_लिखो("[BAD]\tfisttp pi\n");
		वापस 1;
	पूर्ण
	ex = fetestexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);
	अगर (ex != FE_INEXACT) अणु
		म_लिखो("[BAD]\tfisttp pi: wrong exception state\n");
		वापस 1;
	पूर्ण

	feclearexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);
	यंत्र अस्थिर ("\n"
	"	fldpi""\n"
	"	fchs""\n"
	"	fisttp	res16""\n"
	"	fldpi""\n"
	"	fchs""\n"
	"	fisttpl	res32""\n"
	"	fldpi""\n"
	"	fchs""\n"
	"	fisttpll res64""\n"
	: : : "memory"
	);
	अगर (res16 != 0xfffd || res32 != 0xfffffffd || res64 != 0xfffffffffffffffdULL) अणु
		म_लिखो("[BAD]\tfisttp -pi\n");
		वापस 1;
	पूर्ण
	ex = fetestexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);
	अगर (ex != FE_INEXACT) अणु
		म_लिखो("[BAD]\tfisttp -pi: wrong exception state\n");
		वापस 1;
	पूर्ण

	feclearexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);
	यंत्र अस्थिर ("\n"
	"	fldln2""\n"
	"	fisttp	res16""\n"
	"	fldln2""\n"
	"	fisttpl	res32""\n"
	"	fldln2""\n"
	"	fisttpll res64""\n"
	: : : "memory"
	);
	/* Test truncation to zero (round-to-nearest would give 1 here) */
	अगर (res16 != 0 || res32 != 0 || res64 != 0) अणु
		म_लिखो("[BAD]\tfisttp ln2\n");
		वापस 1;
	पूर्ण
	ex = fetestexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);
	अगर (ex != FE_INEXACT) अणु
		म_लिखो("[BAD]\tfisttp ln2: wrong exception state\n");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम sighandler(पूर्णांक sig)
अणु
	म_लिखो("[FAIL]\tGot signal %d, exiting\n", sig);
	निकास(1);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv, अक्षर **envp)
अणु
	पूर्णांक err = 0;

	/* संक_अवैध triggers on 32-bit kernels w/o fisttp emulation
	 * when run with "no387 nofxsr". Other संकेतs are caught
	 * just in हाल.
	 */
	संकेत(संक_अवैध, sighandler);
	संकेत(संक_भ_त्रुटि, sighandler);
	संकेत(संक_अंश, sighandler);

	म_लिखो("[RUN]\tTesting fisttp instructions\n");
	err |= test();
	अगर (!err)
		म_लिखो("[OK]\tfisttp\n");
	अन्यथा
		म_लिखो("[FAIL]\tfisttp errors: %d\n", err);

	वापस err;
पूर्ण
