<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (c) 1991,1992,1995  Linus Torvalds
 *  Copyright (c) 1994  Alan Modra
 *  Copyright (c) 1995  Markus Kuhn
 *  Copyright (c) 1996  Ingo Molnar
 *  Copyright (c) 1998  Andrea Arcangeli
 *  Copyright (c) 2002,2006  Vojtech Pavlik
 *  Copyright (c) 2003  Andi Kleen
 *
 */

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/i8253.h>
#समावेश <linux/समय.स>
#समावेश <linux/export.h>

#समावेश <यंत्र/vsyscall.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/hpet.h>
#समावेश <यंत्र/समय.स>

अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = inकाष्ठाion_poपूर्णांकer(regs);

	अगर (!user_mode(regs) && in_lock_functions(pc)) अणु
#अगर_घोषित CONFIG_FRAME_POINTER
		वापस *(अचिन्हित दीर्घ *)(regs->bp + माप(दीर्घ));
#अन्यथा
		अचिन्हित दीर्घ *sp = (अचिन्हित दीर्घ *)regs->sp;
		/*
		 * Return address is either directly at stack poपूर्णांकer
		 * or above a saved flags. Eflags has bits 22-31 zero,
		 * kernel addresses करोn't.
		 */
		अगर (sp[0] >> 22)
			वापस sp[0];
		अगर (sp[1] >> 22)
			वापस sp[1];
#पूर्ण_अगर
	पूर्ण
	वापस pc;
पूर्ण
EXPORT_SYMBOL(profile_pc);

/*
 * Default समयr पूर्णांकerrupt handler क्रम PIT/HPET
 */
अटल irqवापस_t समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	global_घड़ी_event->event_handler(global_घड़ी_event);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __init setup_शेष_समयr_irq(व्योम)
अणु
	अचिन्हित दीर्घ flags = IRQF_NOBALANCING | IRQF_IRQPOLL | IRQF_TIMER;

	/*
	 * Unconditionally रेजिस्टर the legacy समयr पूर्णांकerrupt; even
	 * without legacy PIC/PIT we need this क्रम the HPET0 in legacy
	 * replacement mode.
	 */
	अगर (request_irq(0, समयr_पूर्णांकerrupt, flags, "timer", शून्य))
		pr_info("Failed to register legacy timer interrupt\n");
पूर्ण

/* Default समयr init function */
व्योम __init hpet_समय_init(व्योम)
अणु
	अगर (!hpet_enable()) अणु
		अगर (!pit_समयr_init())
			वापस;
	पूर्ण

	setup_शेष_समयr_irq();
पूर्ण

अटल __init व्योम x86_late_समय_init(व्योम)
अणु
	/*
	 * Beक्रमe PIT/HPET init, select the पूर्णांकerrupt mode. This is required
	 * to make the decision whether PIT should be initialized correct.
	 */
	x86_init.irqs.पूर्णांकr_mode_select();

	/* Setup the legacy समयrs */
	x86_init.समयrs.समयr_init();

	/*
	 * After PIT/HPET समयrs init, set up the final पूर्णांकerrupt mode क्रम
	 * delivering IRQs.
	 */
	x86_init.irqs.पूर्णांकr_mode_init();
	tsc_init();

	अगर (अटल_cpu_has(X86_FEATURE_WAITPKG))
		use_tछोड़ो_delay();
पूर्ण

/*
 * Initialize TSC and delay the periodic समयr init to
 * late x86_late_समय_init() so ioremap works.
 */
व्योम __init समय_init(व्योम)
अणु
	late_समय_init = x86_late_समय_init;
पूर्ण

/*
 * Sanity check the vdso related archdata content.
 */
व्योम घड़ीsource_arch_init(काष्ठा घड़ीsource *cs)
अणु
	अगर (cs->vdso_घड़ी_mode == VDSO_CLOCKMODE_NONE)
		वापस;

	अगर (cs->mask != CLOCKSOURCE_MASK(64)) अणु
		pr_warn("clocksource %s registered with invalid mask %016llx for VDSO. Disabling VDSO support.\n",
			cs->name, cs->mask);
		cs->vdso_घड़ी_mode = VDSO_CLOCKMODE_NONE;
	पूर्ण
पूर्ण
