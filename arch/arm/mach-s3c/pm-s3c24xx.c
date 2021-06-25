<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2004-2006 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//
// S3C24XX Power Manager (Suspend-To-RAM) support
//
// See Documentation/arm/samsung-s3c24xx/suspend.rst क्रम more inक्रमmation
//
// Parts based on arch/arm/mach-pxa/pm.c
//
// Thanks to Dimitry Andric क्रम debugging

#समावेश <linux/init.h>
#समावेश <linux/suspend.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समय.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/पन.स>

#समावेश "regs-clock.h"
#समावेश "regs-gpio.h"
#समावेश "regs-irq.h"
#समावेश "gpio-samsung.h"

#समावेश <यंत्र/mach/समय.स>

#समावेश "gpio-cfg.h"
#समावेश "pm.h"

#समावेश "regs-mem-s3c24xx.h"

#घोषणा PFX "s3c24xx-pm: "

#अगर_घोषित CONFIG_PM_SLEEP
अटल काष्ठा sleep_save core_save[] = अणु
	/* we restore the timings here, with the proviso that the board
	 * brings the प्रणाली up in an slower, or equal frequency setting
	 * to the original प्रणाली.
	 *
	 * अगर we cannot guarantee this, then things are going to go very
	 * wrong here, as we modअगरy the refresh and both pll settings.
	 */

	SAVE_ITEM(S3C2410_BWSCON),
	SAVE_ITEM(S3C2410_BANKCON0),
	SAVE_ITEM(S3C2410_BANKCON1),
	SAVE_ITEM(S3C2410_BANKCON2),
	SAVE_ITEM(S3C2410_BANKCON3),
	SAVE_ITEM(S3C2410_BANKCON4),
	SAVE_ITEM(S3C2410_BANKCON5),
पूर्ण;
#पूर्ण_अगर

/* s3c_pm_check_resume_pin
 *
 * check to see अगर the pin is configured correctly क्रम sleep mode, and
 * make any necessary adjusपंचांगents अगर it is not
*/

अटल व्योम s3c_pm_check_resume_pin(अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक irqoffs)
अणु
	अचिन्हित दीर्घ irqstate;
	अचिन्हित दीर्घ pinstate;
	पूर्णांक irq = gpio_to_irq(pin);

	अगर (irqoffs < 4)
		irqstate = s3c_irqwake_पूर्णांकmask & (1L<<irqoffs);
	अन्यथा
		irqstate = s3c_irqwake_eपूर्णांकmask & (1L<<irqoffs);

	pinstate = s3c_gpio_अ_लोfg(pin);

	अगर (!irqstate) अणु
		अगर (pinstate == S3C2410_GPIO_IRQ)
			S3C_PMDBG("Leaving IRQ %d (pin %d) as is\n", irq, pin);
	पूर्ण अन्यथा अणु
		अगर (pinstate == S3C2410_GPIO_IRQ) अणु
			S3C_PMDBG("Disabling IRQ %d (pin %d)\n", irq, pin);
			s3c_gpio_cfgpin(pin, S3C2410_GPIO_INPUT);
		पूर्ण
	पूर्ण
पूर्ण

/* s3c_pm_configure_extपूर्णांक
 *
 * configure all बाह्यal पूर्णांकerrupt pins
*/

व्योम s3c_pm_configure_extपूर्णांक(व्योम)
अणु
	पूर्णांक pin;

	/* क्रम each of the बाह्यal पूर्णांकerrupts (EINT0..EINT15) we
	 * need to check whether it is an बाह्यal पूर्णांकerrupt source,
	 * and then configure it as an input अगर it is not
	*/

	क्रम (pin = S3C2410_GPF(0); pin <= S3C2410_GPF(7); pin++) अणु
		s3c_pm_check_resume_pin(pin, pin - S3C2410_GPF(0));
	पूर्ण

	क्रम (pin = S3C2410_GPG(0); pin <= S3C2410_GPG(7); pin++) अणु
		s3c_pm_check_resume_pin(pin, (pin - S3C2410_GPG(0))+8);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
व्योम s3c_pm_restore_core(व्योम)
अणु
	s3c_pm_करो_restore_core(core_save, ARRAY_SIZE(core_save));
पूर्ण

व्योम s3c_pm_save_core(व्योम)
अणु
	s3c_pm_करो_save(core_save, ARRAY_SIZE(core_save));
पूर्ण
#पूर्ण_अगर
