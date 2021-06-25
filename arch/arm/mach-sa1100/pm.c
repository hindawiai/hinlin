<शैली गुरु>
/*
 * SA1100 Power Management Routines
 *
 * Copyright (c) 2001 Clअगरf Brake <cbrake@accelent.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License.
 *
 * History:
 *
 * 2001-02-06:	Clअगरf Brake         Initial code
 *
 * 2001-02-25:	Sukjae Cho <sjcho@east.isi.edu> &
 * 		Chester Kuo <chester@linux.org.tw>
 * 			Save more value क्रम the resume function! Support
 * 			Bitsy/Assabet/Freebird board
 *
 * 2001-08-29:	Nicolas Pitre <nico@fluxnic.net>
 * 			Cleaned up, pushed platक्रमm dependent stuff
 * 			in the platक्रमm specअगरic files.
 *
 * 2002-05-27:	Nicolas Pitre	Killed sleep.h and the kदो_स्मृतिed save array.
 * 				Storage is local on the stack now.
 */
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/suspend.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समय.स>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/mach/समय.स>

बाह्य पूर्णांक sa1100_finish_suspend(अचिन्हित दीर्घ);

#घोषणा SAVE(x)		sleep_save[SLEEP_SAVE_##x] = x
#घोषणा RESTORE(x)	x = sleep_save[SLEEP_SAVE_##x]

/*
 * List of global SA11x0 peripheral रेजिस्टरs to preserve.
 * More ones like CP and general purpose रेजिस्टर values are preserved
 * on the stack and then the stack poपूर्णांकer is stored last in sleep.S.
 */
क्रमागत अणु	SLEEP_SAVE_GPDR, SLEEP_SAVE_GAFR,
	SLEEP_SAVE_PPDR, SLEEP_SAVE_PPSR, SLEEP_SAVE_PPAR, SLEEP_SAVE_PSDR,

	SLEEP_SAVE_Ser1SDCR0,

	SLEEP_SAVE_COUNT
पूर्ण;


अटल पूर्णांक sa11x0_pm_enter(suspend_state_t state)
अणु
	अचिन्हित दीर्घ gpio, sleep_save[SLEEP_SAVE_COUNT];

	gpio = GPLR;

	/* save vital रेजिस्टरs */
	SAVE(GPDR);
	SAVE(GAFR);

	SAVE(PPDR);
	SAVE(PPSR);
	SAVE(PPAR);
	SAVE(PSDR);

	SAVE(Ser1SDCR0);

	/* Clear previous reset status */
	RCSR = RCSR_HWR | RCSR_SWR | RCSR_WDR | RCSR_SMR;

	/* set resume वापस address */
	PSPR = __pa_symbol(cpu_resume);

	/* go zzz */
	cpu_suspend(0, sa1100_finish_suspend);

	/*
	 * Ensure not to come back here अगर it wasn't पूर्णांकended
	 */
	RCSR = RCSR_SMR;
	PSPR = 0;

	/*
	 * Ensure पूर्णांकerrupt sources are disabled; we will re-init
	 * the पूर्णांकerrupt subप्रणाली via the device manager.
	 */
	ICLR = 0;
	ICCR = 1;
	ICMR = 0;

	/* restore रेजिस्टरs */
	RESTORE(GPDR);
	RESTORE(GAFR);

	RESTORE(PPDR);
	RESTORE(PPSR);
	RESTORE(PPAR);
	RESTORE(PSDR);

	RESTORE(Ser1SDCR0);

	GPSR = gpio;
	GPCR = ~gpio;

	/*
	 * Clear the peripheral sleep-hold bit.
	 */
	PSSR = PSSR_PH;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops sa11x0_pm_ops = अणु
	.enter		= sa11x0_pm_enter,
	.valid		= suspend_valid_only_mem,
पूर्ण;

पूर्णांक __init sa11x0_pm_init(व्योम)
अणु
	suspend_set_ops(&sa11x0_pm_ops);
	वापस 0;
पूर्ण
