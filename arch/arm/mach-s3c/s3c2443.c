<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2007 Simtec Electronics
//   Ben Dooks <ben@simtec.co.uk>
//
// Samsung S3C2443 Mobile CPU support

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
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/reboot.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "map.h"
#समावेश "gpio-samsung.h"
#समावेश <mach/irqs.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "regs-s3c2443-clock.h"
#समावेश "rtc-core-s3c24xx.h"

#समावेश "gpio-core.h"
#समावेश "gpio-cfg.h"
#समावेश "gpio-cfg-helpers.h"
#समावेश "devs.h"
#समावेश "cpu.h"
#समावेश "adc-core.h"

#समावेश "s3c24xx.h"
#समावेश "fb-core-s3c24xx.h"
#समावेश "nand-core-s3c24xx.h"
#समावेश "spi-core-s3c24xx.h"

अटल काष्ठा map_desc s3c2443_iodesc[] __initdata __maybe_unused = अणु
	IODESC_ENT(WATCHDOG),
	IODESC_ENT(CLKPWR),
	IODESC_ENT(TIMER),
पूर्ण;

काष्ठा bus_type s3c2443_subsys = अणु
	.name = "s3c2443-core",
	.dev_name = "s3c2443-core",
पूर्ण;

अटल काष्ठा device s3c2443_dev = अणु
	.bus		= &s3c2443_subsys,
पूर्ण;

पूर्णांक __init s3c2443_init(व्योम)
अणु
	prपूर्णांकk("S3C2443: Initialising architecture\n");

	s3c_nand_setname("s3c2412-nand");
	s3c_fb_setname("s3c2443-fb");

	s3c_adc_setname("s3c2443-adc");
	s3c_rtc_setname("s3c2443-rtc");

	/* change WDT IRQ number */
	s3c_device_wdt.resource[1].start = IRQ_S3C2443_WDT;
	s3c_device_wdt.resource[1].end   = IRQ_S3C2443_WDT;

	वापस device_रेजिस्टर(&s3c2443_dev);
पूर्ण

व्योम __init s3c2443_init_uarts(काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no)
अणु
	s3c24xx_init_uartdevs("s3c2440-uart", s3c2410_uart_resources, cfg, no);
पूर्ण

/* s3c2443_map_io
 *
 * रेजिस्टर the standard cpu IO areas, and any passed in from the
 * machine specअगरic initialisation.
 */

व्योम __init s3c2443_map_io(व्योम)
अणु
	s3c24xx_gpiocfg_शेष.set_pull = s3c2443_gpio_setpull;
	s3c24xx_gpiocfg_शेष.get_pull = s3c2443_gpio_getpull;

	/* initialize device inक्रमmation early */
	s3c24xx_spi_setname("s3c2443-spi");

	iotable_init(s3c2443_iodesc, ARRAY_SIZE(s3c2443_iodesc));
पूर्ण

/* need to रेजिस्टर the subप्रणाली beक्रमe we actually रेजिस्टर the device, and
 * we also need to ensure that it has been initialised beक्रमe any of the
 * drivers even try to use it (even अगर not on an s3c2443 based प्रणाली)
 * as a driver which may support both 2443 and 2440 may try and use it.
*/

अटल पूर्णांक __init s3c2443_core_init(व्योम)
अणु
	वापस subsys_प्रणाली_रेजिस्टर(&s3c2443_subsys, शून्य);
पूर्ण

core_initcall(s3c2443_core_init);
