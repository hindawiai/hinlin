<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/kernel/xscale-cp0.c
 *
 * XScale DSP and iWMMXt coprocessor context चयनing and handling
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/thपढ़ो_notअगरy.h>
#समावेश <यंत्र/cputype.h>

यंत्र("	.arch armv5te\n");

अटल अंतरभूत व्योम dsp_save_state(u32 *state)
अणु
	__यंत्र__ __अस्थिर__ (
		"mrrc	p0, 0, %0, %1, c0\n"
		: "=r" (state[0]), "=r" (state[1]));
पूर्ण

अटल अंतरभूत व्योम dsp_load_state(u32 *state)
अणु
	__यंत्र__ __अस्थिर__ (
		"mcrr	p0, 0, %0, %1, c0\n"
		: : "r" (state[0]), "r" (state[1]));
पूर्ण

अटल पूर्णांक dsp_करो(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd, व्योम *t)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = t;

	चयन (cmd) अणु
	हाल THREAD_NOTIFY_FLUSH:
		thपढ़ो->cpu_context.extra[0] = 0;
		thपढ़ो->cpu_context.extra[1] = 0;
		अवरोध;

	हाल THREAD_NOTIFY_SWITCH:
		dsp_save_state(current_thपढ़ो_info()->cpu_context.extra);
		dsp_load_state(thपढ़ो->cpu_context.extra);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block dsp_notअगरier_block = अणु
	.notअगरier_call	= dsp_करो,
पूर्ण;


#अगर_घोषित CONFIG_IWMMXT
अटल पूर्णांक iwmmxt_करो(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd, व्योम *t)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = t;

	चयन (cmd) अणु
	हाल THREAD_NOTIFY_FLUSH:
		/*
		 * flush_thपढ़ो() zeroes thपढ़ो->fpstate, so no need
		 * to करो anything here.
		 *
		 * FALLTHROUGH: Ensure we करोn't try to overग_लिखो our newly
		 * initialised state inक्रमmation on the first fault.
		 */

	हाल THREAD_NOTIFY_EXIT:
		iwmmxt_task_release(thपढ़ो);
		अवरोध;

	हाल THREAD_NOTIFY_SWITCH:
		iwmmxt_task_चयन(thपढ़ो);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block iwmmxt_notअगरier_block = अणु
	.notअगरier_call	= iwmmxt_करो,
पूर्ण;
#पूर्ण_अगर


अटल u32 __init xscale_cp_access_पढ़ो(व्योम)
अणु
	u32 value;

	__यंत्र__ __अस्थिर__ (
		"mrc	p15, 0, %0, c15, c1, 0\n\t"
		: "=r" (value));

	वापस value;
पूर्ण

अटल व्योम __init xscale_cp_access_ग_लिखो(u32 value)
अणु
	u32 temp;

	__यंत्र__ __अस्थिर__ (
		"mcr	p15, 0, %1, c15, c1, 0\n\t"
		"mrc	p15, 0, %0, c15, c1, 0\n\t"
		"mov	%0, %0\n\t"
		"sub	pc, pc, #4\n\t"
		: "=r" (temp) : "r" (value));
पूर्ण

/*
 * Detect whether we have a MAC coprocessor (40 bit रेजिस्टर) or an
 * iWMMXt coprocessor (64 bit रेजिस्टरs) by loading 00000100:00000000
 * पूर्णांकo a coprocessor रेजिस्टर and पढ़ोing it back, and checking
 * whether the upper word survived पूर्णांकact.
 */
अटल पूर्णांक __init cpu_has_iwmmxt(व्योम)
अणु
	u32 lo;
	u32 hi;

	/*
	 * This sequence is पूर्णांकerpreted by the DSP coprocessor as:
	 *	mar	acc0, %2, %3
	 *	mra	%0, %1, acc0
	 *
	 * And by the iWMMXt coprocessor as:
	 *	पंचांगcrr	wR0, %2, %3
	 *	पंचांगrrc	%0, %1, wR0
	 */
	__यंत्र__ __अस्थिर__ (
		"mcrr	p0, 0, %2, %3, c0\n"
		"mrrc	p0, 0, %0, %1, c0\n"
		: "=r" (lo), "=r" (hi)
		: "r" (0), "r" (0x100));

	वापस !!hi;
पूर्ण


/*
 * If we detect that the CPU has iWMMXt (and CONFIG_IWMMXT=y), we
 * disable CP0/CP1 on boot, and let call_fpe() and the iWMMXt lazy
 * चयन code handle iWMMXt context चयनing.  If on the other
 * hand the CPU has a DSP coprocessor, we keep access to CP0 enabled
 * all the समय, and save/restore acc0 on context चयन in non-lazy
 * fashion.
 */
अटल पूर्णांक __init xscale_cp0_init(व्योम)
अणु
	u32 cp_access;

	/* करो not attempt to probe iwmmxt on non-xscale family CPUs */
	अगर (!cpu_is_xscale_family())
		वापस 0;

	cp_access = xscale_cp_access_पढ़ो() & ~3;
	xscale_cp_access_ग_लिखो(cp_access | 1);

	अगर (cpu_has_iwmmxt()) अणु
#अगर_अघोषित CONFIG_IWMMXT
		pr_warn("CAUTION: XScale iWMMXt coprocessor detected, but kernel support is missing.\n");
#अन्यथा
		pr_info("XScale iWMMXt coprocessor detected.\n");
		elf_hwcap |= HWCAP_IWMMXT;
		thपढ़ो_रेजिस्टर_notअगरier(&iwmmxt_notअगरier_block);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		pr_info("XScale DSP coprocessor detected.\n");
		thपढ़ो_रेजिस्टर_notअगरier(&dsp_notअगरier_block);
		cp_access |= 1;
	पूर्ण

	xscale_cp_access_ग_लिखो(cp_access);

	वापस 0;
पूर्ण

late_initcall(xscale_cp0_init);
