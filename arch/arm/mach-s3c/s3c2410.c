<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2003-2005 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//
// http://www.simtec.co.uk/products/EB2410ITX/

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "map.h"
#समावेश "gpio-samsung.h"
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/प्रणाली_misc.h>


#समावेश "regs-clock.h"

#समावेश "cpu.h"
#समावेश "devs.h"
#समावेश "pm.h"

#समावेश "gpio-core.h"
#समावेश "gpio-cfg.h"
#समावेश "gpio-cfg-helpers.h"

#समावेश "s3c24xx.h"

/* Initial IO mappings */

अटल काष्ठा map_desc s3c2410_iodesc[] __initdata __maybe_unused = अणु
	IODESC_ENT(CLKPWR),
	IODESC_ENT(TIMER),
	IODESC_ENT(WATCHDOG),
पूर्ण;

/* our uart devices */

/* uart registration process */

व्योम __init s3c2410_init_uarts(काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no)
अणु
	s3c24xx_init_uartdevs("s3c2410-uart", s3c2410_uart_resources, cfg, no);
पूर्ण

/* s3c2410_map_io
 *
 * रेजिस्टर the standard cpu IO areas, and any passed in from the
 * machine specअगरic initialisation.
*/

व्योम __init s3c2410_map_io(व्योम)
अणु
	s3c24xx_gpiocfg_शेष.set_pull = s3c24xx_gpio_setpull_1up;
	s3c24xx_gpiocfg_शेष.get_pull = s3c24xx_gpio_getpull_1up;

	iotable_init(s3c2410_iodesc, ARRAY_SIZE(s3c2410_iodesc));
पूर्ण

काष्ठा bus_type s3c2410_subsys = अणु
	.name = "s3c2410-core",
	.dev_name = "s3c2410-core",
पूर्ण;

/* Note, we would have liked to name this s3c2410-core, but we cannot
 * रेजिस्टर two subप्रणालीs with the same name.
 */
काष्ठा bus_type s3c2410a_subsys = अणु
	.name = "s3c2410a-core",
	.dev_name = "s3c2410a-core",
पूर्ण;

अटल काष्ठा device s3c2410_dev = अणु
	.bus		= &s3c2410_subsys,
पूर्ण;

/* need to रेजिस्टर the subप्रणाली beक्रमe we actually रेजिस्टर the device, and
 * we also need to ensure that it has been initialised beक्रमe any of the
 * drivers even try to use it (even अगर not on an s3c2410 based प्रणाली)
 * as a driver which may support both 2410 and 2440 may try and use it.
*/

अटल पूर्णांक __init s3c2410_core_init(व्योम)
अणु
	वापस subsys_प्रणाली_रेजिस्टर(&s3c2410_subsys, शून्य);
पूर्ण

core_initcall(s3c2410_core_init);

अटल पूर्णांक __init s3c2410a_core_init(व्योम)
अणु
	वापस subsys_प्रणाली_रेजिस्टर(&s3c2410a_subsys, शून्य);
पूर्ण

core_initcall(s3c2410a_core_init);

पूर्णांक __init s3c2410_init(व्योम)
अणु
	prपूर्णांकk("S3C2410: Initialising architecture\n");

#अगर_घोषित CONFIG_PM_SLEEP
	रेजिस्टर_syscore_ops(&s3c2410_pm_syscore_ops);
	रेजिस्टर_syscore_ops(&s3c24xx_irq_syscore_ops);
#पूर्ण_अगर

	वापस device_रेजिस्टर(&s3c2410_dev);
पूर्ण

पूर्णांक __init s3c2410a_init(व्योम)
अणु
	s3c2410_dev.bus = &s3c2410a_subsys;
	वापस s3c2410_init();
पूर्ण
