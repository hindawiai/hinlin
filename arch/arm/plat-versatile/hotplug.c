<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *
 * This hotplug implementation is _specअगरic_ to the situation found on
 * ARM development platक्रमms where there is _no_ possibility of actually
 * taking a CPU offline, resetting it, or otherwise.  Real platक्रमms must
 * NOT copy this code.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/smp.h>

#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/cp15.h>

#समावेश <plat/platsmp.h>

अटल अंतरभूत व्योम versatile_immitation_enter_lowघातer(अचिन्हित पूर्णांक actrl_mask)
अणु
	अचिन्हित पूर्णांक v;

	यंत्र अस्थिर(
		"mcr	p15, 0, %1, c7, c5, 0\n"
	"	mcr	p15, 0, %1, c7, c10, 4\n"
	/*
	 * Turn off coherency
	 */
	"	mrc	p15, 0, %0, c1, c0, 1\n"
	"	bic	%0, %0, %3\n"
	"	mcr	p15, 0, %0, c1, c0, 1\n"
	"	mrc	p15, 0, %0, c1, c0, 0\n"
	"	bic	%0, %0, %2\n"
	"	mcr	p15, 0, %0, c1, c0, 0\n"
	  : "=&r" (v)
	  : "r" (0), "Ir" (CR_C), "Ir" (actrl_mask)
	  : "cc");
पूर्ण

अटल अंतरभूत व्योम versatile_immitation_leave_lowघातer(अचिन्हित पूर्णांक actrl_mask)
अणु
	अचिन्हित पूर्णांक v;

	यंत्र अस्थिर(
		"mrc	p15, 0, %0, c1, c0, 0\n"
	"	orr	%0, %0, %1\n"
	"	mcr	p15, 0, %0, c1, c0, 0\n"
	"	mrc	p15, 0, %0, c1, c0, 1\n"
	"	orr	%0, %0, %2\n"
	"	mcr	p15, 0, %0, c1, c0, 1\n"
	  : "=&r" (v)
	  : "Ir" (CR_C), "Ir" (actrl_mask)
	  : "cc");
पूर्ण

अटल अंतरभूत व्योम versatile_immitation_करो_lowघातer(अचिन्हित पूर्णांक cpu, पूर्णांक *spurious)
अणु
	/*
	 * there is no घातer-control hardware on this platक्रमm, so all
	 * we can करो is put the core पूर्णांकo WFI; this is safe as the calling
	 * code will have alपढ़ोy disabled पूर्णांकerrupts.
	 *
	 * This code should not be used outside Versatile platक्रमms.
	 */
	क्रम (;;) अणु
		wfi();

		अगर (versatile_cpu_release == cpu_logical_map(cpu)) अणु
			/*
			 * OK, proper wakeup, we're करोne
			 */
			अवरोध;
		पूर्ण

		/*
		 * Getting here, means that we have come out of WFI without
		 * having been woken up - this shouldn't happen
		 *
		 * Just note it happening - when we're woken, we can report
		 * its occurrence.
		 */
		(*spurious)++;
	पूर्ण
पूर्ण

/*
 * platक्रमm-specअगरic code to shutकरोwn a CPU.
 * This code supports immitation-style CPU hotplug क्रम Versatile/Realview/
 * Versatile Express platक्रमms that are unable to करो real CPU hotplug.
 */
व्योम versatile_immitation_cpu_die(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक actrl_mask)
अणु
	पूर्णांक spurious = 0;

	versatile_immitation_enter_lowघातer(actrl_mask);
	versatile_immitation_करो_lowघातer(cpu, &spurious);
	versatile_immitation_leave_lowघातer(actrl_mask);

	अगर (spurious)
		pr_warn("CPU%u: %u spurious wakeup calls\n", cpu, spurious);
पूर्ण
