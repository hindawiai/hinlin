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

क्रमागत अणु
	CF = 1 << 0,
	PF = 1 << 2,
	ZF = 1 << 6,
	ARITH = CF | PF | ZF,
पूर्ण;

दीर्घ res_fcomi_pi_1;
दीर्घ res_fcomi_1_pi;
दीर्घ res_fcomi_1_1;
दीर्घ res_fcomi_nan_1;
/* sNaN is s|111 1111 1|1xx xxxx xxxx xxxx xxxx xxxx */
/* qNaN is s|111 1111 1|0xx xxxx xxxx xxxx xxxx xxxx (some x must be nonzero) */
पूर्णांक snan = 0x7fc11111;
पूर्णांक qnan = 0x7f811111;
अचिन्हित लघु snan1[5];
/* sNaN80 is s|111 1111 1111 1111 |10xx xx...xx (some x must be nonzero) */
अचिन्हित लघु snan80[5] = अणु 0x1111, 0x1111, 0x1111, 0x8111, 0x7fff पूर्ण;

पूर्णांक test(दीर्घ flags)
अणु
	feclearexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);

	यंत्र ("\n"

	"	push	%0""\n"
	"	popf""\n"
	"	fld1""\n"
	"	fldpi""\n"
	"	fcomi	%%st(1), %%st" "\n"
	"	ffree	%%st(0)" "\n"
	"	ffree	%%st(1)" "\n"
	"	pushf""\n"
	"	pop	res_fcomi_1_pi""\n"

	"	push	%0""\n"
	"	popf""\n"
	"	fldpi""\n"
	"	fld1""\n"
	"	fcomi	%%st(1), %%st" "\n"
	"	ffree	%%st(0)" "\n"
	"	ffree	%%st(1)" "\n"
	"	pushf""\n"
	"	pop	res_fcomi_pi_1""\n"

	"	push	%0""\n"
	"	popf""\n"
	"	fld1""\n"
	"	fld1""\n"
	"	fcomi	%%st(1), %%st" "\n"
	"	ffree	%%st(0)" "\n"
	"	ffree	%%st(1)" "\n"
	"	pushf""\n"
	"	pop	res_fcomi_1_1""\n"
	:
	: "r" (flags)
	);
	अगर ((res_fcomi_1_pi & ARITH) != (0)) अणु
		म_लिखो("[BAD]\tfcomi_1_pi with flags:%lx\n", flags);
		वापस 1;
	पूर्ण
	अगर ((res_fcomi_pi_1 & ARITH) != (CF)) अणु
		म_लिखो("[BAD]\tfcomi_pi_1 with flags:%lx->%lx\n", flags, res_fcomi_pi_1 & ARITH);
		वापस 1;
	पूर्ण
	अगर ((res_fcomi_1_1 & ARITH) != (ZF)) अणु
		म_लिखो("[BAD]\tfcomi_1_1 with flags:%lx\n", flags);
		वापस 1;
	पूर्ण
	अगर (fetestexcept(FE_INVALID) != 0) अणु
		म_लिखो("[BAD]\tFE_INVALID is set in %s\n", __func__);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक test_qnan(दीर्घ flags)
अणु
	feclearexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);

	यंत्र ("\n"
	"	push	%0""\n"
	"	popf""\n"
	"	flds	qnan""\n"
	"	fld1""\n"
	"	fnclex""\n"		// fld of a qnan उठाओd FE_INVALID, clear it
	"	fcomi	%%st(1), %%st" "\n"
	"	ffree	%%st(0)" "\n"
	"	ffree	%%st(1)" "\n"
	"	pushf""\n"
	"	pop	res_fcomi_nan_1""\n"
	:
	: "r" (flags)
	);
	अगर ((res_fcomi_nan_1 & ARITH) != (ZF|CF|PF)) अणु
		म_लिखो("[BAD]\tfcomi_qnan_1 with flags:%lx\n", flags);
		वापस 1;
	पूर्ण
	अगर (fetestexcept(FE_INVALID) != FE_INVALID) अणु
		म_लिखो("[BAD]\tFE_INVALID is not set in %s\n", __func__);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक testu_qnan(दीर्घ flags)
अणु
	feclearexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);

	यंत्र ("\n"
	"	push	%0""\n"
	"	popf""\n"
	"	flds	qnan""\n"
	"	fld1""\n"
	"	fnclex""\n"		// fld of a qnan उठाओd FE_INVALID, clear it
	"	fucomi	%%st(1), %%st" "\n"
	"	ffree	%%st(0)" "\n"
	"	ffree	%%st(1)" "\n"
	"	pushf""\n"
	"	pop	res_fcomi_nan_1""\n"
	:
	: "r" (flags)
	);
	अगर ((res_fcomi_nan_1 & ARITH) != (ZF|CF|PF)) अणु
		म_लिखो("[BAD]\tfcomi_qnan_1 with flags:%lx\n", flags);
		वापस 1;
	पूर्ण
	अगर (fetestexcept(FE_INVALID) != 0) अणु
		म_लिखो("[BAD]\tFE_INVALID is set in %s\n", __func__);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक testu_snan(दीर्घ flags)
अणु
	feclearexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);

	यंत्र ("\n"
	"	push	%0""\n"
	"	popf""\n"
//	"	flds	snan""\n"	// WRONG, this will convert 32-bit fp snan to a *qnan* in 80-bit fp रेजिस्टर!
//	"	fstpt	snan1""\n"	// अगर uncommented, it prपूर्णांकs "snan1:7fff c111 1100 0000 0000" - c111, not 8111!
//	"	fnclex""\n"		// flds of a snan उठाओd FE_INVALID, clear it
	"	fldt	snan80""\n"	// fldt never उठाओ FE_INVALID
	"	fld1""\n"
	"	fucomi	%%st(1), %%st" "\n"
	"	ffree	%%st(0)" "\n"
	"	ffree	%%st(1)" "\n"
	"	pushf""\n"
	"	pop	res_fcomi_nan_1""\n"
	:
	: "r" (flags)
	);
	अगर ((res_fcomi_nan_1 & ARITH) != (ZF|CF|PF)) अणु
		म_लिखो("[BAD]\tfcomi_qnan_1 with flags:%lx\n", flags);
		वापस 1;
	पूर्ण
//	म_लिखो("snan:%x snan1:%04x %04x %04x %04x %04x\n", snan, snan1[4], snan1[3], snan1[2], snan1[1], snan1[0]);
	अगर (fetestexcept(FE_INVALID) != FE_INVALID) अणु
		म_लिखो("[BAD]\tFE_INVALID is not set in %s\n", __func__);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक testp(दीर्घ flags)
अणु
	feclearexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);

	यंत्र ("\n"

	"	push	%0""\n"
	"	popf""\n"
	"	fld1""\n"
	"	fldpi""\n"
	"	fcomip	%%st(1), %%st" "\n"
	"	ffree	%%st(0)" "\n"
	"	pushf""\n"
	"	pop	res_fcomi_1_pi""\n"

	"	push	%0""\n"
	"	popf""\n"
	"	fldpi""\n"
	"	fld1""\n"
	"	fcomip	%%st(1), %%st" "\n"
	"	ffree	%%st(0)" "\n"
	"	pushf""\n"
	"	pop	res_fcomi_pi_1""\n"

	"	push	%0""\n"
	"	popf""\n"
	"	fld1""\n"
	"	fld1""\n"
	"	fcomip	%%st(1), %%st" "\n"
	"	ffree	%%st(0)" "\n"
	"	pushf""\n"
	"	pop	res_fcomi_1_1""\n"
	:
	: "r" (flags)
	);
	अगर ((res_fcomi_1_pi & ARITH) != (0)) अणु
		म_लिखो("[BAD]\tfcomi_1_pi with flags:%lx\n", flags);
		वापस 1;
	पूर्ण
	अगर ((res_fcomi_pi_1 & ARITH) != (CF)) अणु
		म_लिखो("[BAD]\tfcomi_pi_1 with flags:%lx->%lx\n", flags, res_fcomi_pi_1 & ARITH);
		वापस 1;
	पूर्ण
	अगर ((res_fcomi_1_1 & ARITH) != (ZF)) अणु
		म_लिखो("[BAD]\tfcomi_1_1 with flags:%lx\n", flags);
		वापस 1;
	पूर्ण
	अगर (fetestexcept(FE_INVALID) != 0) अणु
		म_लिखो("[BAD]\tFE_INVALID is set in %s\n", __func__);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक testp_qnan(दीर्घ flags)
अणु
	feclearexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);

	यंत्र ("\n"
	"	push	%0""\n"
	"	popf""\n"
	"	flds	qnan""\n"
	"	fld1""\n"
	"	fnclex""\n"		// fld of a qnan उठाओd FE_INVALID, clear it
	"	fcomip	%%st(1), %%st" "\n"
	"	ffree	%%st(0)" "\n"
	"	pushf""\n"
	"	pop	res_fcomi_nan_1""\n"
	:
	: "r" (flags)
	);
	अगर ((res_fcomi_nan_1 & ARITH) != (ZF|CF|PF)) अणु
		म_लिखो("[BAD]\tfcomi_qnan_1 with flags:%lx\n", flags);
		वापस 1;
	पूर्ण
	अगर (fetestexcept(FE_INVALID) != FE_INVALID) अणु
		म_लिखो("[BAD]\tFE_INVALID is not set in %s\n", __func__);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक testup_qnan(दीर्घ flags)
अणु
	feclearexcept(FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW);

	यंत्र ("\n"
	"	push	%0""\n"
	"	popf""\n"
	"	flds	qnan""\n"
	"	fld1""\n"
	"	fnclex""\n"		// fld of a qnan उठाओd FE_INVALID, clear it
	"	fucomip	%%st(1), %%st" "\n"
	"	ffree	%%st(0)" "\n"
	"	pushf""\n"
	"	pop	res_fcomi_nan_1""\n"
	:
	: "r" (flags)
	);
	अगर ((res_fcomi_nan_1 & ARITH) != (ZF|CF|PF)) अणु
		म_लिखो("[BAD]\tfcomi_qnan_1 with flags:%lx\n", flags);
		वापस 1;
	पूर्ण
	अगर (fetestexcept(FE_INVALID) != 0) अणु
		म_लिखो("[BAD]\tFE_INVALID is set in %s\n", __func__);
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

	/* संक_अवैध triggers on 32-bit kernels w/o fcomi emulation
	 * when run with "no387 nofxsr". Other संकेतs are caught
	 * just in हाल.
	 */
	संकेत(संक_अवैध, sighandler);
	संकेत(संक_भ_त्रुटि, sighandler);
	संकेत(संक_अंश, sighandler);

	म_लिखो("[RUN]\tTesting f[u]comi[p] instructions\n");
	err |= test(0);
	err |= test_qnan(0);
	err |= testu_qnan(0);
	err |= testu_snan(0);
	err |= test(CF|ZF|PF);
	err |= test_qnan(CF|ZF|PF);
	err |= testu_qnan(CF|ZF|PF);
	err |= testu_snan(CF|ZF|PF);
	err |= testp(0);
	err |= testp_qnan(0);
	err |= testup_qnan(0);
	err |= testp(CF|ZF|PF);
	err |= testp_qnan(CF|ZF|PF);
	err |= testup_qnan(CF|ZF|PF);
	अगर (!err)
		म_लिखो("[OK]\tf[u]comi[p]\n");
	अन्यथा
		म_लिखो("[FAIL]\tf[u]comi[p] errors: %d\n", err);

	वापस err;
पूर्ण
