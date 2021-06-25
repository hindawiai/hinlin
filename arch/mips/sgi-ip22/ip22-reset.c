<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1997, 1998, 2001, 03, 05, 06 by Ralf Baechle
 */
#समावेश <linux/linkage.h>
#समावेश <linux/init.h>
#समावेश <linux/rtc/ds1286.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/pm.h>
#समावेश <linux/समयr.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/sgi/ioc.h>
#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/mc.h>
#समावेश <यंत्र/sgi/ip22.h>

/*
 * Just घातerकरोwn अगर init hasn't करोne after POWERDOWN_TIMEOUT seconds.
 * I'm not sure if this feature is a good idea, for now it's here just to
 * make the घातer button make behave just like under IRIX.
 */
#घोषणा POWERDOWN_TIMEOUT	120

/*
 * Blink frequency during reboot grace period and when panicked.
 */
#घोषणा POWERDOWN_FREQ		(HZ / 4)
#घोषणा PANIC_FREQ		(HZ / 8)

अटल काष्ठा समयr_list घातer_समयr, blink_समयr, debounce_समयr;
अटल अचिन्हित दीर्घ blink_समयr_समयout;

#घोषणा MACHINE_PANICED		1
#घोषणा MACHINE_SHUTTING_DOWN	2

अटल पूर्णांक machine_state;

अटल व्योम __noवापस sgi_machine_घातer_off(व्योम)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	local_irq_disable();

	/* Disable watchकरोg */
	पंचांगp = hpc3c0->rtcregs[RTC_CMD] & 0xff;
	hpc3c0->rtcregs[RTC_CMD] = पंचांगp | RTC_WAM;
	hpc3c0->rtcregs[RTC_WSEC] = 0;
	hpc3c0->rtcregs[RTC_WHSEC] = 0;

	जबतक (1) अणु
		sgioc->panel = ~SGIOC_PANEL_POWERON;
		/* Good bye cruel world ...  */

		/* If we're still running, we probably got sent an alarm
		   पूर्णांकerrupt.  Read the flag to clear it.  */
		पंचांगp = hpc3c0->rtcregs[RTC_HOURS_ALARM];
	पूर्ण
पूर्ण

अटल व्योम __noवापस sgi_machine_restart(अक्षर *command)
अणु
	अगर (machine_state & MACHINE_SHUTTING_DOWN)
		sgi_machine_घातer_off();
	sgimc->cpuctrl0 |= SGIMC_CCTRL0_SYSINIT;
	जबतक (1);
पूर्ण

अटल व्योम __noवापस sgi_machine_halt(व्योम)
अणु
	अगर (machine_state & MACHINE_SHUTTING_DOWN)
		sgi_machine_घातer_off();
	ArcEnterInteractiveMode();
पूर्ण

अटल व्योम घातer_समयout(काष्ठा समयr_list *unused)
अणु
	sgi_machine_घातer_off();
पूर्ण

अटल व्योम blink_समयout(काष्ठा समयr_list *unused)
अणु
	/* XXX fix this क्रम fullhouse  */
	sgi_ioc_reset ^= (SGIOC_RESET_LC0OFF|SGIOC_RESET_LC1OFF);
	sgioc->reset = sgi_ioc_reset;

	mod_समयr(&blink_समयr, jअगरfies + blink_समयr_समयout);
पूर्ण

अटल व्योम debounce(काष्ठा समयr_list *unused)
अणु
	del_समयr(&debounce_समयr);
	अगर (sgपूर्णांक->istat1 & SGINT_ISTAT1_PWR) अणु
		/* Interrupt still being sent. */
		debounce_समयr.expires = jअगरfies + (HZ / 20); /* 0.05s	*/
		add_समयr(&debounce_समयr);

		sgioc->panel = SGIOC_PANEL_POWERON | SGIOC_PANEL_POWERINTR |
			       SGIOC_PANEL_VOLDNINTR | SGIOC_PANEL_VOLDNHOLD |
			       SGIOC_PANEL_VOLUPINTR | SGIOC_PANEL_VOLUPHOLD;

		वापस;
	पूर्ण

	अगर (machine_state & MACHINE_PANICED)
		sgimc->cpuctrl0 |= SGIMC_CCTRL0_SYSINIT;

	enable_irq(SGI_PANEL_IRQ);
पूर्ण

अटल अंतरभूत व्योम घातer_button(व्योम)
अणु
	अगर (machine_state & MACHINE_PANICED)
		वापस;

	अगर ((machine_state & MACHINE_SHUTTING_DOWN) ||
			समाप्त_cad_pid(संक_विघ्न, 1)) अणु
		/* No init process or button pressed twice.  */
		sgi_machine_घातer_off();
	पूर्ण

	machine_state |= MACHINE_SHUTTING_DOWN;
	blink_समयr_समयout = POWERDOWN_FREQ;
	blink_समयout(&blink_समयr);

	समयr_setup(&घातer_समयr, घातer_समयout, 0);
	घातer_समयr.expires = jअगरfies + POWERDOWN_TIMEOUT * HZ;
	add_समयr(&घातer_समयr);
पूर्ण

अटल irqवापस_t panel_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक buttons;

	buttons = sgioc->panel;
	sgioc->panel = SGIOC_PANEL_POWERON | SGIOC_PANEL_POWERINTR;

	अगर (sgपूर्णांक->istat1 & SGINT_ISTAT1_PWR) अणु
		/* Wait until पूर्णांकerrupt goes away */
		disable_irq_nosync(SGI_PANEL_IRQ);
		समयr_setup(&debounce_समयr, debounce, 0);
		debounce_समयr.expires = jअगरfies + 5;
		add_समयr(&debounce_समयr);
	पूर्ण

	/* Power button was pressed
	 * ioc.ps page 22: "The Panel Register is called Power Control by Full
	 * House. Only lowest 2 bits are used. Guiness uses upper four bits
	 * क्रम volume control". This is not true, all bits are pulled high
	 * on fullhouse */
	अगर (!(buttons & SGIOC_PANEL_POWERINTR))
		घातer_button();

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक panic_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
		      व्योम *ptr)
अणु
	अगर (machine_state & MACHINE_PANICED)
		वापस NOTIFY_DONE;
	machine_state |= MACHINE_PANICED;

	blink_समयr_समयout = PANIC_FREQ;
	blink_समयout(&blink_समयr);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block panic_block = अणु
	.notअगरier_call	= panic_event,
पूर्ण;

अटल पूर्णांक __init reboot_setup(व्योम)
अणु
	पूर्णांक res;

	_machine_restart = sgi_machine_restart;
	_machine_halt = sgi_machine_halt;
	pm_घातer_off = sgi_machine_घातer_off;

	res = request_irq(SGI_PANEL_IRQ, panel_पूर्णांक, 0, "Front Panel", शून्य);
	अगर (res) अणु
		prपूर्णांकk(KERN_ERR "Allocation of front panel IRQ failed\n");
		वापस res;
	पूर्ण

	समयr_setup(&blink_समयr, blink_समयout, 0);
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &panic_block);

	वापस 0;
पूर्ण

subsys_initcall(reboot_setup);
