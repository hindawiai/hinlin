<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-spear13xx/hotplug.c
 *
 * Copyright (C) 2012 ST Microelectronics Ltd.
 * Deepak Sikri <deepak.sikri@st.com>
 *
 * based upon linux/arch/arm/mach-realview/hotplug.c
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/smp.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/smp_plat.h>

#समावेश "generic.h"

अटल अंतरभूत व्योम cpu_enter_lowघातer(व्योम)
अणु
	अचिन्हित पूर्णांक v;

	यंत्र अस्थिर(
	"	mcr	p15, 0, %1, c7, c5, 0\n"
	"	dsb\n"
	/*
	 * Turn off coherency
	 */
	"	mrc	p15, 0, %0, c1, c0, 1\n"
	"	bic	%0, %0, #0x20\n"
	"	mcr	p15, 0, %0, c1, c0, 1\n"
	"	mrc	p15, 0, %0, c1, c0, 0\n"
	"	bic	%0, %0, %2\n"
	"	mcr	p15, 0, %0, c1, c0, 0\n"
	: "=&r" (v)
	: "r" (0), "Ir" (CR_C)
	: "cc", "memory");
पूर्ण

अटल अंतरभूत व्योम cpu_leave_lowघातer(व्योम)
अणु
	अचिन्हित पूर्णांक v;

	यंत्र अस्थिर("mrc	p15, 0, %0, c1, c0, 0\n"
	"	orr	%0, %0, %1\n"
	"	mcr	p15, 0, %0, c1, c0, 0\n"
	"	mrc	p15, 0, %0, c1, c0, 1\n"
	"	orr	%0, %0, #0x20\n"
	"	mcr	p15, 0, %0, c1, c0, 1\n"
	: "=&r" (v)
	: "Ir" (CR_C)
	: "cc");
पूर्ण

अटल अंतरभूत व्योम spear13xx_करो_lowघातer(अचिन्हित पूर्णांक cpu, पूर्णांक *spurious)
अणु
	क्रम (;;) अणु
		wfi();

		अगर (spear_pen_release == cpu) अणु
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
 * platक्रमm-specअगरic code to shutकरोwn a CPU
 *
 * Called with IRQs disabled
 */
व्योम spear13xx_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक spurious = 0;

	/*
	 * we're पढ़ोy क्रम shutकरोwn now, so करो it
	 */
	cpu_enter_lowघातer();
	spear13xx_करो_lowघातer(cpu, &spurious);

	/*
	 * bring this CPU back पूर्णांकo the world of cache
	 * coherency, and then restore पूर्णांकerrupts
	 */
	cpu_leave_lowघातer();

	अगर (spurious)
		pr_warn("CPU%u: %u spurious wakeup calls\n", cpu, spurious);
पूर्ण
