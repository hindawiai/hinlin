<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पन.स>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश <mach/regs-ost.h>
#समावेश <mach/reset.h>
#समावेश <mach/smemc.h>

अचिन्हित पूर्णांक reset_status;
EXPORT_SYMBOL(reset_status);

अटल व्योम करो_hw_reset(व्योम);

अटल पूर्णांक reset_gpio = -1;

पूर्णांक init_gpio_reset(पूर्णांक gpio, पूर्णांक output, पूर्णांक level)
अणु
	पूर्णांक rc;

	rc = gpio_request(gpio, "reset generator");
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Can't request reset_gpio\n");
		जाओ out;
	पूर्ण

	अगर (output)
		rc = gpio_direction_output(gpio, level);
	अन्यथा
		rc = gpio_direction_input(gpio);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Can't configure reset_gpio\n");
		gpio_मुक्त(gpio);
		जाओ out;
	पूर्ण

out:
	अगर (!rc)
		reset_gpio = gpio;

	वापस rc;
पूर्ण

/*
 * Trigger GPIO reset.
 * This covers various types of logic connecting gpio pin
 * to RESET pins (nRESET or GPIO_RESET):
 */
अटल व्योम करो_gpio_reset(व्योम)
अणु
	BUG_ON(reset_gpio == -1);

	/* drive it low */
	gpio_direction_output(reset_gpio, 0);
	mdelay(2);
	/* rising edge or drive high */
	gpio_set_value(reset_gpio, 1);
	mdelay(2);
	/* falling edge */
	gpio_set_value(reset_gpio, 0);

	/* give it some समय */
	mdelay(10);

	WARN_ON(1);
	/* fallback */
	करो_hw_reset();
पूर्ण

अटल व्योम करो_hw_reset(व्योम)
अणु
	/* Initialize the watchकरोg and let it fire */
	ग_लिखोl_relaxed(OWER_WME, OWER);
	ग_लिखोl_relaxed(OSSR_M3, OSSR);
	/* ... in 100 ms */
	ग_लिखोl_relaxed(पढ़ोl_relaxed(OSCR) + 368640, OSMR3);
	/*
	 * SDRAM hangs on watchकरोg reset on Marvell PXA270 (erratum 71)
	 * we put SDRAM पूर्णांकo self-refresh to prevent that
	 */
	जबतक (1)
		ग_लिखोl_relaxed(MDREFR_SLFRSH, MDREFR);
पूर्ण

व्योम pxa_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	local_irq_disable();
	local_fiq_disable();

	clear_reset_status(RESET_STATUS_ALL);

	चयन (mode) अणु
	हाल REBOOT_SOFT:
		/* Jump पूर्णांकo ROM at address 0 */
		soft_restart(0);
		अवरोध;
	हाल REBOOT_GPIO:
		करो_gpio_reset();
		अवरोध;
	हाल REBOOT_HARD:
	शेष:
		करो_hw_reset();
		अवरोध;
	पूर्ण
पूर्ण
