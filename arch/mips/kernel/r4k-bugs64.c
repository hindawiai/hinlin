<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2003, 2004, 2007  Maciej W. Rozycki
 */
#समावेश <linux/context_tracking.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/मानकघोष.स>

#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/setup.h>

अटल अक्षर bug64hit[] __initdata =
	"reliable operation impossible!\n%s";
अटल अक्षर nowar[] __initdata =
	"Please report to <linux-mips@vger.kernel.org>.";
अटल अक्षर r4kwar[] __initdata =
	"Enable CPU_R4000_WORKAROUNDS to rectify.";
अटल अक्षर daddiwar[] __initdata =
	"Enable CPU_DADDI_WORKAROUNDS to rectify.";

अटल __always_अंतरभूत __init
व्योम align_mod(स्थिर पूर्णांक align, स्थिर पूर्णांक mod)
अणु
	यंत्र अस्थिर(
		".set	push\n\t"
		".set	noreorder\n\t"
		".balign %0\n\t"
		".rept	%1\n\t"
		"nop\n\t"
		".endr\n\t"
		".set	pop"
		:
		: "n"(align), "n"(mod));
पूर्ण

अटल __always_अंतरभूत __init
व्योम mult_sh_align_mod(दीर्घ *v1, दीर्घ *v2, दीर्घ *w,
		       स्थिर पूर्णांक align, स्थिर पूर्णांक mod)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक m1, m2;
	दीर्घ p, s, lv1, lv2, lw;

	/*
	 * We want the multiply and the shअगरt to be isolated from the
	 * rest of the code to disable gcc optimizations.  Hence the
	 * यंत्र statements that execute nothing, but make gcc not know
	 * what the values of m1, m2 and s are and what lv2 and p are
	 * used क्रम.
	 */

	local_irq_save(flags);
	/*
	 * The following code leads to a wrong result of the first
	 * dsll32 when executed on R4000 rev. 2.2 or 3.0 (PRId
	 * 00000422 or 00000430, respectively).
	 *
	 * See "MIPS R4000PC/SC Errata, Processor Revision 2.2 and
	 * 3.0" by MIPS Technologies, Inc., errata #16 and #28 क्रम
	 * details.  I got no permission to duplicate them here,
	 * sigh... --macro
	 */
	यंत्र अस्थिर(
		""
		: "=r" (m1), "=r" (m2), "=r" (s)
		: "0" (5), "1" (8), "2" (5));
	align_mod(align, mod);
	/*
	 * The trailing nop is needed to fulfill the two-inकाष्ठाion
	 * requirement between पढ़ोing hi/lo and staring a mult/भाग.
	 * Leaving it out may cause gas insert a nop itself अवरोधing
	 * the desired alignment of the next chunk.
	 */
	यंत्र अस्थिर(
		".set	push\n\t"
		".set	noat\n\t"
		".set	noreorder\n\t"
		".set	nomacro\n\t"
		"mult	%2, %3\n\t"
		"dsll32 %0, %4, %5\n\t"
		"mflo	$0\n\t"
		"dsll32 %1, %4, %5\n\t"
		"nop\n\t"
		".set	pop"
		: "=&r" (lv1), "=r" (lw)
		: "r" (m1), "r" (m2), "r" (s), "I" (0)
		: "hi", "lo", "$0");
	/* We have to use single पूर्णांकegers क्रम m1 and m2 and a द्विगुन
	 * one क्रम p to be sure the mulsidi3 gcc's RTL multiplication
	 * inकाष्ठाion has the workaround applied.  Older versions of
	 * gcc have correct umulsi3 and mulsi3, but other
	 * multiplication variants lack the workaround.
	 */
	यंत्र अस्थिर(
		""
		: "=r" (m1), "=r" (m2), "=r" (s)
		: "0" (m1), "1" (m2), "2" (s));
	align_mod(align, mod);
	p = m1 * m2;
	lv2 = s << 32;
	यंत्र अस्थिर(
		""
		: "=r" (lv2)
		: "0" (lv2), "r" (p));
	local_irq_restore(flags);

	*v1 = lv1;
	*v2 = lv2;
	*w = lw;
पूर्ण

अटल __always_अंतरभूत __init व्योम check_mult_sh(व्योम)
अणु
	दीर्घ v1[8], v2[8], w[8];
	पूर्णांक bug, fix, i;

	prपूर्णांकk("Checking for the multiply/shift bug... ");

	/*
	 * Testing discovered false negatives क्रम certain code offsets
	 * पूर्णांकo cache lines.  Hence we test all possible offsets क्रम
	 * the worst assumption of an R4000 I-cache line width of 32
	 * bytes.
	 *
	 * We can't use a loop as alignment directives need to be
	 * immediates.
	 */
	mult_sh_align_mod(&v1[0], &v2[0], &w[0], 32, 0);
	mult_sh_align_mod(&v1[1], &v2[1], &w[1], 32, 1);
	mult_sh_align_mod(&v1[2], &v2[2], &w[2], 32, 2);
	mult_sh_align_mod(&v1[3], &v2[3], &w[3], 32, 3);
	mult_sh_align_mod(&v1[4], &v2[4], &w[4], 32, 4);
	mult_sh_align_mod(&v1[5], &v2[5], &w[5], 32, 5);
	mult_sh_align_mod(&v1[6], &v2[6], &w[6], 32, 6);
	mult_sh_align_mod(&v1[7], &v2[7], &w[7], 32, 7);

	bug = 0;
	क्रम (i = 0; i < 8; i++)
		अगर (v1[i] != w[i])
			bug = 1;

	अगर (bug == 0) अणु
		pr_cont("no.\n");
		वापस;
	पूर्ण

	pr_cont("yes, workaround... ");

	fix = 1;
	क्रम (i = 0; i < 8; i++)
		अगर (v2[i] != w[i])
			fix = 0;

	अगर (fix == 1) अणु
		pr_cont("yes.\n");
		वापस;
	पूर्ण

	pr_cont("no.\n");
	panic(bug64hit, !R4000_WAR ? r4kwar : nowar);
पूर्ण

अटल अस्थिर पूर्णांक daddi_ov;

यंत्रlinkage व्योम __init करो_daddi_ov(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state;

	prev_state = exception_enter();
	daddi_ov = 1;
	regs->cp0_epc += 4;
	exception_निकास(prev_state);
पूर्ण

अटल __init व्योम check_daddi(व्योम)
अणु
	बाह्य यंत्रlinkage व्योम handle_daddi_ov(व्योम);
	अचिन्हित दीर्घ flags;
	व्योम *handler;
	दीर्घ v, पंचांगp;

	prपूर्णांकk("Checking for the daddi bug... ");

	local_irq_save(flags);
	handler = set_except_vector(EXCCODE_OV, handle_daddi_ov);
	/*
	 * The following code fails to trigger an overflow exception
	 * when executed on R4000 rev. 2.2 or 3.0 (PRId 00000422 or
	 * 00000430, respectively).
	 *
	 * See "MIPS R4000PC/SC Errata, Processor Revision 2.2 and
	 * 3.0" by MIPS Technologies, Inc., erratum #23 क्रम details.
	 * I got no permission to duplicate it here, sigh... --macro
	 */
	यंत्र अस्थिर(
		".set	push\n\t"
		".set	noat\n\t"
		".set	noreorder\n\t"
		".set	nomacro\n\t"
		"addiu	%1, $0, %2\n\t"
		"dsrl	%1, %1, 1\n\t"
#अगर_घोषित HAVE_AS_SET_DADDI
		".set	daddi\n\t"
#पूर्ण_अगर
		"daddi	%0, %1, %3\n\t"
		".set	pop"
		: "=r" (v), "=&r" (पंचांगp)
		: "I" (0xffffffffffffdb9aUL), "I" (0x1234));
	set_except_vector(EXCCODE_OV, handler);
	local_irq_restore(flags);

	अगर (daddi_ov) अणु
		pr_cont("no.\n");
		वापस;
	पूर्ण

	pr_cont("yes, workaround... ");

	local_irq_save(flags);
	handler = set_except_vector(EXCCODE_OV, handle_daddi_ov);
	यंत्र अस्थिर(
		"addiu	%1, $0, %2\n\t"
		"dsrl	%1, %1, 1\n\t"
		"daddi	%0, %1, %3"
		: "=r" (v), "=&r" (पंचांगp)
		: "I" (0xffffffffffffdb9aUL), "I" (0x1234));
	set_except_vector(EXCCODE_OV, handler);
	local_irq_restore(flags);

	अगर (daddi_ov) अणु
		pr_cont("yes.\n");
		वापस;
	पूर्ण

	pr_cont("no.\n");
	panic(bug64hit, !DADDI_WAR ? daddiwar : nowar);
पूर्ण

पूर्णांक daddiu_bug	= -1;

अटल __init व्योम check_daddiu(व्योम)
अणु
	दीर्घ v, w, पंचांगp;

	prपूर्णांकk("Checking for the daddiu bug... ");

	/*
	 * The following code leads to a wrong result of daddiu when
	 * executed on R4400 rev. 1.0 (PRId 00000440).
	 *
	 * See "MIPS R4400PC/SC Errata, Processor Revision 1.0" by
	 * MIPS Technologies, Inc., erratum #7 क्रम details.
	 *
	 * According to "MIPS R4000PC/SC Errata, Processor Revision
	 * 2.2 and 3.0" by MIPS Technologies, Inc., erratum #41 this
	 * problem affects R4000 rev. 2.2 and 3.0 (PRId 00000422 and
	 * 00000430, respectively), too.  Testing failed to trigger it
	 * so far.
	 *
	 * I got no permission to duplicate the errata here, sigh...
	 * --macro
	 */
	यंत्र अस्थिर(
		".set	push\n\t"
		".set	noat\n\t"
		".set	noreorder\n\t"
		".set	nomacro\n\t"
		"addiu	%2, $0, %3\n\t"
		"dsrl	%2, %2, 1\n\t"
#अगर_घोषित HAVE_AS_SET_DADDI
		".set	daddi\n\t"
#पूर्ण_अगर
		"daddiu %0, %2, %4\n\t"
		"addiu	%1, $0, %4\n\t"
		"daddu	%1, %2\n\t"
		".set	pop"
		: "=&r" (v), "=&r" (w), "=&r" (पंचांगp)
		: "I" (0xffffffffffffdb9aUL), "I" (0x1234));

	daddiu_bug = v != w;

	अगर (!daddiu_bug) अणु
		pr_cont("no.\n");
		वापस;
	पूर्ण

	pr_cont("yes, workaround... ");

	यंत्र अस्थिर(
		"addiu	%2, $0, %3\n\t"
		"dsrl	%2, %2, 1\n\t"
		"daddiu %0, %2, %4\n\t"
		"addiu	%1, $0, %4\n\t"
		"daddu	%1, %2"
		: "=&r" (v), "=&r" (w), "=&r" (पंचांगp)
		: "I" (0xffffffffffffdb9aUL), "I" (0x1234));

	अगर (v == w) अणु
		pr_cont("yes.\n");
		वापस;
	पूर्ण

	pr_cont("no.\n");
	panic(bug64hit, !DADDI_WAR ? daddiwar : nowar);
पूर्ण

व्योम __init check_bugs64_early(व्योम)
अणु
	check_mult_sh();
	check_daddiu();
पूर्ण

व्योम __init check_bugs64(व्योम)
अणु
	check_daddi();
पूर्ण
