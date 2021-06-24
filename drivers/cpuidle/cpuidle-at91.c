<शैली गुरु>
/*
 * based on arch/arm/mach-kirkwood/cpuidle.c
 *
 * CPU idle support क्रम AT91 SoC
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * The cpu idle uses रुको-क्रम-पूर्णांकerrupt and RAM self refresh in order
 * to implement two idle states -
 * #1 रुको-क्रम-पूर्णांकerrupt
 * #2 रुको-क्रम-पूर्णांकerrupt and RAM self refresh
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <यंत्र/cpuidle.h>

#घोषणा AT91_MAX_STATES	2

अटल व्योम (*at91_standby)(व्योम);

/* Actual code that माला_दो the SoC in dअगरferent idle states */
अटल पूर्णांक at91_enter_idle(काष्ठा cpuidle_device *dev,
			काष्ठा cpuidle_driver *drv,
			       पूर्णांक index)
अणु
	at91_standby();
	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver at91_idle_driver = अणु
	.name			= "at91_idle",
	.owner			= THIS_MODULE,
	.states[0]		= ARM_CPUIDLE_WFI_STATE,
	.states[1]		= अणु
		.enter			= at91_enter_idle,
		.निकास_latency		= 10,
		.target_residency	= 10000,
		.name			= "RAM_SR",
		.desc			= "WFI and DDR Self Refresh",
	पूर्ण,
	.state_count = AT91_MAX_STATES,
पूर्ण;

/* Initialize CPU idle by रेजिस्टरing the idle states */
अटल पूर्णांक at91_cpuidle_probe(काष्ठा platक्रमm_device *dev)
अणु
	at91_standby = (व्योम *)(dev->dev.platक्रमm_data);
	
	वापस cpuidle_रेजिस्टर(&at91_idle_driver, शून्य);
पूर्ण

अटल काष्ठा platक्रमm_driver at91_cpuidle_driver = अणु
	.driver = अणु
		.name = "cpuidle-at91",
	पूर्ण,
	.probe = at91_cpuidle_probe,
पूर्ण;
builtin_platक्रमm_driver(at91_cpuidle_driver);
