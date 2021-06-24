<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2009 Yauhen Kharuzhy <jekhor@gmail.com>,
//	as part of OpenInkpot project
// Copyright (c) 2009 Promwad Innovation Company
//	Yauhen Kharuzhy <yauhen.kharuzhy@promwad.com>
//
// Samsung S3C2416 Mobile CPU support

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/reboot.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "map.h"
#समावेश "gpio-samsung.h"
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "regs-s3c2443-clock.h"
#समावेश "rtc-core-s3c24xx.h"

#समावेश "gpio-core.h"
#समावेश "gpio-cfg.h"
#समावेश "gpio-cfg-helpers.h"
#समावेश "devs.h"
#समावेश "cpu.h"
#समावेश "sdhci.h"
#समावेश "pm.h"

#समावेश "iic-core.h"
#समावेश "adc-core.h"

#समावेश "s3c24xx.h"
#समावेश "fb-core-s3c24xx.h"
#समावेश "nand-core-s3c24xx.h"
#समावेश "spi-core-s3c24xx.h"

अटल काष्ठा map_desc s3c2416_iodesc[] __initdata __maybe_unused = अणु
	IODESC_ENT(WATCHDOG),
	IODESC_ENT(CLKPWR),
	IODESC_ENT(TIMER),
पूर्ण;

काष्ठा bus_type s3c2416_subsys = अणु
	.name = "s3c2416-core",
	.dev_name = "s3c2416-core",
पूर्ण;

अटल काष्ठा device s3c2416_dev = अणु
	.bus		= &s3c2416_subsys,
पूर्ण;

पूर्णांक __init s3c2416_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "S3C2416: Initializing architecture\n");

	/* change WDT IRQ number */
	s3c_device_wdt.resource[1].start = IRQ_S3C2443_WDT;
	s3c_device_wdt.resource[1].end   = IRQ_S3C2443_WDT;

	/* the i2c devices are directly compatible with s3c2440 */
	s3c_i2c0_setname("s3c2440-i2c");
	s3c_i2c1_setname("s3c2440-i2c");

	s3c_fb_setname("s3c2443-fb");

	s3c_adc_setname("s3c2416-adc");
	s3c_rtc_setname("s3c2416-rtc");

#अगर_घोषित CONFIG_PM_SLEEP
	रेजिस्टर_syscore_ops(&s3c2416_pm_syscore_ops);
	रेजिस्टर_syscore_ops(&s3c24xx_irq_syscore_ops);
	रेजिस्टर_syscore_ops(&s3c2416_irq_syscore_ops);
#पूर्ण_अगर

	वापस device_रेजिस्टर(&s3c2416_dev);
पूर्ण

व्योम __init s3c2416_init_uarts(काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no)
अणु
	s3c24xx_init_uartdevs("s3c2440-uart", s3c2410_uart_resources, cfg, no);

	s3c_nand_setname("s3c2412-nand");
पूर्ण

/* s3c2416_map_io
 *
 * रेजिस्टर the standard cpu IO areas, and any passed in from the
 * machine specअगरic initialisation.
 */

व्योम __init s3c2416_map_io(व्योम)
अणु
	s3c24xx_gpiocfg_शेष.set_pull = samsung_gpio_setpull_upकरोwn;
	s3c24xx_gpiocfg_शेष.get_pull = samsung_gpio_getpull_upकरोwn;

	/* initialize device inक्रमmation early */
	s3c2416_शेष_sdhci0();
	s3c2416_शेष_sdhci1();
	s3c24xx_spi_setname("s3c2443-spi");

	iotable_init(s3c2416_iodesc, ARRAY_SIZE(s3c2416_iodesc));
पूर्ण

/* need to रेजिस्टर the subप्रणाली beक्रमe we actually रेजिस्टर the device, and
 * we also need to ensure that it has been initialised beक्रमe any of the
 * drivers even try to use it (even अगर not on an s3c2416 based प्रणाली)
 * as a driver which may support both 2443 and 2440 may try and use it.
*/

अटल पूर्णांक __init s3c2416_core_init(व्योम)
अणु
	वापस subsys_प्रणाली_रेजिस्टर(&s3c2416_subsys, शून्य);
पूर्ण

core_initcall(s3c2416_core_init);
