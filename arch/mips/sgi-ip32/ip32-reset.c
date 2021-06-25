<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 Keith M Wesolowski
 * Copyright (C) 2001 Paul Mundt
 * Copyright (C) 2003 Guiकरो Guenther <agx@sigxcpu.org>
 */

#समावेश <linux/compiler.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/delay.h>
#समावेश <linux/rtc/ds1685.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/wbflush.h>
#समावेश <यंत्र/ip32/mace.h>
#समावेश <यंत्र/ip32/crime.h>
#समावेश <यंत्र/ip32/ip32_पूर्णांकs.h>

#घोषणा POWERDOWN_TIMEOUT	120
/*
 * Blink frequency during reboot grace period and when panicked.
 */
#घोषणा POWERDOWN_FREQ		(HZ / 4)
#घोषणा PANIC_FREQ		(HZ / 8)

बाह्य काष्ठा platक्रमm_device ip32_rtc_device;

अटल काष्ठा समयr_list घातer_समयr, blink_समयr;
अटल अचिन्हित दीर्घ blink_समयr_समयout;
अटल पूर्णांक has_panicked, shutting_करोwn;

अटल __noवापस व्योम ip32_घातeroff(व्योम *data)
अणु
	व्योम (*घातeroff_func)(काष्ठा platक्रमm_device *) =
		symbol_get(ds1685_rtc_घातeroff);

#अगर_घोषित CONFIG_MODULES
	/* If the first __symbol_get failed, our module wasn't loaded. */
	अगर (!घातeroff_func) अणु
		request_module("rtc-ds1685");
		घातeroff_func = symbol_get(ds1685_rtc_घातeroff);
	पूर्ण
#पूर्ण_अगर

	अगर (!घातeroff_func)
		pr_emerg("RTC not available for power-off.  Spinning forever ...\n");
	अन्यथा अणु
		(*घातeroff_func)((काष्ठा platक्रमm_device *)data);
		symbol_put(ds1685_rtc_घातeroff);
	पूर्ण

	unreachable();
पूर्ण

अटल व्योम ip32_machine_restart(अक्षर *cmd) __noवापस;
अटल व्योम ip32_machine_restart(अक्षर *cmd)
अणु
	msleep(20);
	crime->control = CRIME_CONTROL_HARD_RESET;
	unreachable();
पूर्ण

अटल व्योम blink_समयout(काष्ठा समयr_list *unused)
अणु
	अचिन्हित दीर्घ led = mace->perअगर.ctrl.misc ^ MACEISA_LED_RED;
	mace->perअगर.ctrl.misc = led;
	mod_समयr(&blink_समयr, jअगरfies + blink_समयr_समयout);
पूर्ण

अटल व्योम ip32_machine_halt(व्योम)
अणु
	ip32_घातeroff(&ip32_rtc_device);
पूर्ण

अटल व्योम घातer_समयout(काष्ठा समयr_list *unused)
अणु
	ip32_घातeroff(&ip32_rtc_device);
पूर्ण

व्योम ip32_prepare_घातeroff(व्योम)
अणु
	अगर (has_panicked)
		वापस;

	अगर (shutting_करोwn || समाप्त_cad_pid(संक_विघ्न, 1)) अणु
		/* No init process or button pressed twice.  */
		ip32_घातeroff(&ip32_rtc_device);
	पूर्ण

	shutting_करोwn = 1;
	blink_समयr_समयout = POWERDOWN_FREQ;
	blink_समयout(&blink_समयr);

	समयr_setup(&घातer_समयr, घातer_समयout, 0);
	घातer_समयr.expires = jअगरfies + POWERDOWN_TIMEOUT * HZ;
	add_समयr(&घातer_समयr);
पूर्ण

अटल पूर्णांक panic_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
		       व्योम *ptr)
अणु
	अचिन्हित दीर्घ led;

	अगर (has_panicked)
		वापस NOTIFY_DONE;
	has_panicked = 1;

	/* turn off the green LED */
	led = mace->perअगर.ctrl.misc | MACEISA_LED_GREEN;
	mace->perअगर.ctrl.misc = led;

	blink_समयr_समयout = PANIC_FREQ;
	blink_समयout(&blink_समयr);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block panic_block = अणु
	.notअगरier_call = panic_event,
पूर्ण;

अटल __init पूर्णांक ip32_reboot_setup(व्योम)
अणु
	/* turn on the green led only */
	अचिन्हित दीर्घ led = mace->perअगर.ctrl.misc;
	led |= MACEISA_LED_RED;
	led &= ~MACEISA_LED_GREEN;
	mace->perअगर.ctrl.misc = led;

	_machine_restart = ip32_machine_restart;
	_machine_halt = ip32_machine_halt;
	pm_घातer_off = ip32_machine_halt;

	समयr_setup(&blink_समयr, blink_समयout, 0);
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &panic_block);

	वापस 0;
पूर्ण

subsys_initcall(ip32_reboot_setup);
