<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * x86 FPU bug checks:
 */
#समावेश <यंत्र/fpu/पूर्णांकernal.h>

/*
 * Boot समय CPU/FPU FDIV bug detection code:
 */

अटल द्विगुन __initdata x = 4195835.0;
अटल द्विगुन __initdata y = 3145727.0;

/*
 * This used to check क्रम exceptions..
 * However, it turns out that to support that,
 * the XMM trap handlers basically had to
 * be buggy. So let's have a correct XMM trap
 * handler, and क्रमget about prपूर्णांकing out
 * some status at boot.
 *
 * We should really only care about bugs here
 * anyway. Not features.
 */
व्योम __init fpu__init_check_bugs(व्योम)
अणु
	s32 fभाग_bug;

	/* kernel_fpu_begin/end() relies on patched alternative inकाष्ठाions. */
	अगर (!boot_cpu_has(X86_FEATURE_FPU))
		वापस;

	kernel_fpu_begin();

	/*
	 * trap_init() enabled FXSR and company _beक्रमe_ testing क्रम FP
	 * problems here.
	 *
	 * Test क्रम the भागl bug: http://en.wikipedia.org/wiki/Fभाग_bug
	 */
	__यंत्र__("fninit\n\t"
		"fldl %1\n\t"
		"fdivl %2\n\t"
		"fmull %2\n\t"
		"fldl %1\n\t"
		"fsubp %%st,%%st(1)\n\t"
		"fistpl %0\n\t"
		"fwait\n\t"
		"fninit"
		: "=m" (*&fभाग_bug)
		: "m" (*&x), "m" (*&y));

	kernel_fpu_end();

	अगर (fभाग_bug) अणु
		set_cpu_bug(&boot_cpu_data, X86_BUG_FDIV);
		pr_warn("Hmm, FPU with FDIV bug\n");
	पूर्ण
पूर्ण
