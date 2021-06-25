<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2006 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//
// http://armlinux.simtec.co.uk/.

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/reboot.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "map.h"
#समावेश "regs-clock.h"
#समावेश "regs-gpio.h"

#समावेश "cpu.h"
#समावेश "devs.h"
#समावेश "pm.h"

#समावेश "s3c24xx.h"
#समावेश "nand-core-s3c24xx.h"
#समावेश "regs-dsc-s3c24xx.h"
#समावेश "s3c2412-power.h"

#अगर_अघोषित CONFIG_CPU_S3C2412_ONLY
व्योम __iomem *s3c24xx_va_gpio2 = S3C24XX_VA_GPIO;

अटल अंतरभूत व्योम s3c2412_init_gpio2(व्योम)
अणु
	s3c24xx_va_gpio2 = S3C24XX_VA_GPIO + 0x10;
पूर्ण
#अन्यथा
#घोषणा s3c2412_init_gpio2() करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

/* Initial IO mappings */

अटल काष्ठा map_desc s3c2412_iodesc[] __initdata __maybe_unused = अणु
	IODESC_ENT(CLKPWR),
	IODESC_ENT(TIMER),
	IODESC_ENT(WATCHDOG),
	अणु
		.भव = (अचिन्हित दीर्घ)S3C2412_VA_SSMC,
		.pfn	 = __phys_to_pfn(S3C2412_PA_SSMC),
		.length	 = SZ_1M,
		.type	 = MT_DEVICE,
	पूर्ण,
	अणु
		.भव = (अचिन्हित दीर्घ)S3C2412_VA_EBI,
		.pfn	 = __phys_to_pfn(S3C2412_PA_EBI),
		.length	 = SZ_1M,
		.type	 = MT_DEVICE,
	पूर्ण,
पूर्ण;

/* uart registration process */

व्योम __init s3c2412_init_uarts(काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no)
अणु
	s3c24xx_init_uartdevs("s3c2412-uart", s3c2410_uart_resources, cfg, no);

	/* नाम devices that are s3c2412/s3c2413 specअगरic */
	s3c_device_sdi.name  = "s3c2412-sdi";
	s3c_device_lcd.name  = "s3c2412-lcd";
	s3c_nand_setname("s3c2412-nand");

	/* alter IRQ of SDI controller */

	s3c_device_sdi.resource[1].start = IRQ_S3C2412_SDI;
	s3c_device_sdi.resource[1].end   = IRQ_S3C2412_SDI;

	/* spi channel related changes, s3c2412/13 specअगरic */
	s3c_device_spi0.name = "s3c2412-spi";
	s3c_device_spi0.resource[0].end = S3C24XX_PA_SPI + 0x24;
	s3c_device_spi1.name = "s3c2412-spi";
	s3c_device_spi1.resource[0].start = S3C24XX_PA_SPI + S3C2412_SPI1;
	s3c_device_spi1.resource[0].end = S3C24XX_PA_SPI + S3C2412_SPI1 + 0x24;

पूर्ण

/* s3c2412_idle
 *
 * use the standard idle call by ensuring the idle mode
 * in घातer config, then issuing the idle co-processor
 * inकाष्ठाion
*/

अटल व्योम s3c2412_idle(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;

	/* ensure our idle mode is to go to idle */

	पंचांगp = __raw_पढ़ोl(S3C2412_PWRCFG);
	पंचांगp &= ~S3C2412_PWRCFG_STANDBYWFI_MASK;
	पंचांगp |= S3C2412_PWRCFG_STANDBYWFI_IDLE;
	__raw_ग_लिखोl(पंचांगp, S3C2412_PWRCFG);

	cpu_करो_idle();
पूर्ण

/* s3c2412_map_io
 *
 * रेजिस्टर the standard cpu IO areas, and any passed in from the
 * machine specअगरic initialisation.
*/

व्योम __init s3c2412_map_io(व्योम)
अणु
	/* move base of IO */

	s3c2412_init_gpio2();

	/* set our idle function */

	arm_pm_idle = s3c2412_idle;

	/* रेजिस्टर our io-tables */

	iotable_init(s3c2412_iodesc, ARRAY_SIZE(s3c2412_iodesc));
पूर्ण

/* need to रेजिस्टर the subप्रणाली beक्रमe we actually रेजिस्टर the device, and
 * we also need to ensure that it has been initialised beक्रमe any of the
 * drivers even try to use it (even अगर not on an s3c2412 based प्रणाली)
 * as a driver which may support both 2410 and 2440 may try and use it.
*/

काष्ठा bus_type s3c2412_subsys = अणु
	.name = "s3c2412-core",
	.dev_name = "s3c2412-core",
पूर्ण;

अटल पूर्णांक __init s3c2412_core_init(व्योम)
अणु
	वापस subsys_प्रणाली_रेजिस्टर(&s3c2412_subsys, शून्य);
पूर्ण

core_initcall(s3c2412_core_init);

अटल काष्ठा device s3c2412_dev = अणु
	.bus		= &s3c2412_subsys,
पूर्ण;

पूर्णांक __init s3c2412_init(व्योम)
अणु
	prपूर्णांकk("S3C2412: Initialising architecture\n");

#अगर_घोषित CONFIG_PM_SLEEP
	रेजिस्टर_syscore_ops(&s3c2412_pm_syscore_ops);
	रेजिस्टर_syscore_ops(&s3c24xx_irq_syscore_ops);
#पूर्ण_अगर

	वापस device_रेजिस्टर(&s3c2412_dev);
पूर्ण
