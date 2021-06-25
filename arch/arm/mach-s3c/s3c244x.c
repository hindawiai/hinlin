<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2004-2006 Simtec Electronics
//   Ben Dooks <ben@simtec.co.uk>
//
// Samsung S3C2440 and S3C2442 Mobile CPU support (not S3C2443)

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "map.h"
#समावेश <यंत्र/irq.h>

#समावेश "regs-clock.h"
#समावेश "regs-gpio.h"

#समावेश "devs.h"
#समावेश "cpu.h"
#समावेश "pm.h"

#समावेश "s3c24xx.h"
#समावेश "nand-core-s3c24xx.h"
#समावेश "regs-dsc-s3c24xx.h"

अटल काष्ठा map_desc s3c244x_iodesc[] __initdata __maybe_unused = अणु
	IODESC_ENT(CLKPWR),
	IODESC_ENT(TIMER),
	IODESC_ENT(WATCHDOG),
पूर्ण;

/* uart initialisation */

व्योम __init s3c244x_init_uarts(काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no)
अणु
	s3c24xx_init_uartdevs("s3c2440-uart", s3c2410_uart_resources, cfg, no);
पूर्ण

व्योम __init s3c244x_map_io(व्योम)
अणु
	/* रेजिस्टर our io-tables */

	iotable_init(s3c244x_iodesc, ARRAY_SIZE(s3c244x_iodesc));

	/* नाम any peripherals used dअगरfering from the s3c2410 */

	s3c_device_sdi.name  = "s3c2440-sdi";
	s3c_device_i2c0.name  = "s3c2440-i2c";
	s3c_nand_setname("s3c2440-nand");
	s3c_device_ts.name = "s3c2440-ts";
	s3c_device_usbgadget.name = "s3c2440-usbgadget";
	s3c2410_device_dclk.name = "s3c2440-dclk";
पूर्ण

/* Since the S3C2442 and S3C2440 share items, put both subप्रणालीs here */

काष्ठा bus_type s3c2440_subsys = अणु
	.name		= "s3c2440-core",
	.dev_name	= "s3c2440-core",
पूर्ण;

काष्ठा bus_type s3c2442_subsys = अणु
	.name		= "s3c2442-core",
	.dev_name	= "s3c2442-core",
पूर्ण;

/* need to रेजिस्टर the subप्रणाली beक्रमe we actually रेजिस्टर the device, and
 * we also need to ensure that it has been initialised beक्रमe any of the
 * drivers even try to use it (even अगर not on an s3c2440 based प्रणाली)
 * as a driver which may support both 2410 and 2440 may try and use it.
*/

अटल पूर्णांक __init s3c2440_core_init(व्योम)
अणु
	वापस subsys_प्रणाली_रेजिस्टर(&s3c2440_subsys, शून्य);
पूर्ण

core_initcall(s3c2440_core_init);

अटल पूर्णांक __init s3c2442_core_init(व्योम)
अणु
	वापस subsys_प्रणाली_रेजिस्टर(&s3c2442_subsys, शून्य);
पूर्ण

core_initcall(s3c2442_core_init);


#अगर_घोषित CONFIG_PM_SLEEP
अटल काष्ठा sleep_save s3c244x_sleep[] = अणु
	SAVE_ITEM(S3C2440_DSC0),
	SAVE_ITEM(S3C2440_DSC1),
	SAVE_ITEM(S3C2440_GPJDAT),
	SAVE_ITEM(S3C2440_GPJCON),
	SAVE_ITEM(S3C2440_GPJUP)
पूर्ण;

अटल पूर्णांक s3c244x_suspend(व्योम)
अणु
	s3c_pm_करो_save(s3c244x_sleep, ARRAY_SIZE(s3c244x_sleep));
	वापस 0;
पूर्ण

अटल व्योम s3c244x_resume(व्योम)
अणु
	s3c_pm_करो_restore(s3c244x_sleep, ARRAY_SIZE(s3c244x_sleep));
पूर्ण

काष्ठा syscore_ops s3c244x_pm_syscore_ops = अणु
	.suspend	= s3c244x_suspend,
	.resume		= s3c244x_resume,
पूर्ण;
#पूर्ण_अगर
