<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// (C) 2006 Thomas Gleixner <tglx@linutronix.de>
//
// Derived from mach-smdk2413.c - (C) 2006 Simtec Electronics

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"
#समावेश "gpio-cfg.h"

#समावेश <linux/platक्रमm_data/fb-s3c2410.h>

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>

#समावेश "devs.h"
#समावेश "cpu.h"

#समावेश "s3c24xx.h"

अटल काष्ठा map_desc vsपंचांगs_iodesc[] __initdata = अणु
पूर्ण;

अटल काष्ठा s3c2410_uartcfg vsपंचांगs_uartcfgs[] __initdata = अणु
	[0] = अणु
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = 0x3c5,
		.ulcon	     = 0x03,
		.ufcon	     = 0x51,
	पूर्ण,
	[1] = अणु
		.hwport	     = 1,
		.flags	     = 0,
		.ucon	     = 0x3c5,
		.ulcon	     = 0x03,
		.ufcon	     = 0x51,
	पूर्ण,
	[2] = अणु
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = 0x3c5,
		.ulcon	     = 0x03,
		.ufcon	     = 0x51,
	पूर्ण
पूर्ण;

अटल काष्ठा mtd_partition __initdata vsपंचांगs_nand_part[] = अणु
	[0] = अणु
		.name	= "Boot Agent",
		.size	= 0x7C000,
		.offset	= 0,
	पूर्ण,
	[1] = अणु
		.name	= "UBoot Config",
		.offset = 0x7C000,
		.size	= 0x4000,
	पूर्ण,
	[2] = अणु
		.name	= "Kernel",
		.offset = 0x80000,
		.size	= 0x200000,
	पूर्ण,
	[3] = अणु
		.name	= "RFS",
		.offset	= 0x280000,
		.size	= 0x3d80000,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_nand_set __initdata vsपंचांगs_nand_sets[] = अणु
	[0] = अणु
		.name		= "NAND",
		.nr_chips	= 1,
		.nr_partitions	= ARRAY_SIZE(vsपंचांगs_nand_part),
		.partitions	= vsपंचांगs_nand_part,
	पूर्ण,
पूर्ण;

/* choose a set of timings which should suit most 512Mbit
 * chips and beyond.
*/

अटल काष्ठा s3c2410_platक्रमm_nand __initdata vsपंचांगs_nand_info = अणु
	.tacls		= 20,
	.twrph0		= 60,
	.twrph1		= 20,
	.nr_sets	= ARRAY_SIZE(vsपंचांगs_nand_sets),
	.sets		= vsपंचांगs_nand_sets,
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_SOFT,
पूर्ण;

अटल काष्ठा platक्रमm_device *vsपंचांगs_devices[] __initdata = अणु
	&s3c_device_ohci,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_iis,
	&s3c_device_rtc,
	&s3c_device_nand,
	&s3c2412_device_dma,
पूर्ण;

अटल व्योम __init vsपंचांगs_fixup(काष्ठा tag *tags, अक्षर **cmdline)
अणु
	अगर (tags != phys_to_virt(S3C2410_SDRAM_PA + 0x100)) अणु
		memblock_add(0x30000000, SZ_64M);
	पूर्ण
पूर्ण

अटल व्योम __init vsपंचांगs_map_io(व्योम)
अणु
	s3c24xx_init_io(vsपंचांगs_iodesc, ARRAY_SIZE(vsपंचांगs_iodesc));
	s3c24xx_init_uarts(vsपंचांगs_uartcfgs, ARRAY_SIZE(vsपंचांगs_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init vsपंचांगs_init_समय(व्योम)
अणु
	s3c2412_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init vsपंचांगs_init(व्योम)
अणु
	s3c_i2c0_set_platdata(शून्य);
	s3c_nand_set_platdata(&vsपंचांगs_nand_info);
	/* Configure the I2S pins (GPE0...GPE4) in correct mode */
	s3c_gpio_cfgall_range(S3C2410_GPE(0), 5, S3C_GPIO_SFN(2),
			      S3C_GPIO_PULL_NONE);
	platक्रमm_add_devices(vsपंचांगs_devices, ARRAY_SIZE(vsपंचांगs_devices));
पूर्ण

MACHINE_START(VSTMS, "VSTMS")
	.atag_offset	= 0x100,

	.fixup		= vsपंचांगs_fixup,
	.init_irq	= s3c2412_init_irq,
	.init_machine	= vsपंचांगs_init,
	.map_io		= vsपंचांगs_map_io,
	.init_समय	= vsपंचांगs_init_समय,
MACHINE_END
