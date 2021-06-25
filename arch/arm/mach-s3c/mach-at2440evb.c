<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2008 Ramax Lo <ramaxlo@gmail.com>
//      Based on mach-anubis.c by Ben Dooks <ben@simtec.co.uk>
//      and modअगरications by SBZ <sbz@spgui.org> and
//      Weibing <http://weibing.blogbus.com>
//
// For product inक्रमmation, visit http://www.arm.com/

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/dm9000.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <linux/platक्रमm_data/fb-s3c2410.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"
#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/partitions.h>

#समावेश "devs.h"
#समावेश "cpu.h"
#समावेश <linux/platक्रमm_data/mmc-s3cmci.h>

#समावेश "s3c24xx.h"

अटल काष्ठा map_desc at2440evb_iodesc[] __initdata = अणु
	/* Nothing here */
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT
#घोषणा ULCON (S3C2410_LCON_CS8 | S3C2410_LCON_PNONE)
#घोषणा UFCON (S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE)

अटल काष्ठा s3c2410_uartcfg at2440evb_uartcfgs[] __initdata = अणु
	[0] = अणु
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
		.clk_sel	= S3C2410_UCON_CLKSEL1 | S3C2410_UCON_CLKSEL2,
	पूर्ण,
	[1] = अणु
		.hwport	     = 1,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
		.clk_sel	= S3C2410_UCON_CLKSEL1 | S3C2410_UCON_CLKSEL2,
	पूर्ण,
पूर्ण;

/* न_अंकD Flash on AT2440EVB board */

अटल काष्ठा mtd_partition __initdata at2440evb_शेष_nand_part[] = अणु
	[0] = अणु
		.name	= "Boot Agent",
		.size	= SZ_256K,
		.offset	= 0,
	पूर्ण,
	[1] = अणु
		.name	= "Kernel",
		.size	= SZ_2M,
		.offset	= SZ_256K,
	पूर्ण,
	[2] = अणु
		.name	= "Root",
		.offset	= SZ_256K + SZ_2M,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_nand_set __initdata at2440evb_nand_sets[] = अणु
	[0] = अणु
		.name		= "nand",
		.nr_chips	= 1,
		.nr_partitions	= ARRAY_SIZE(at2440evb_शेष_nand_part),
		.partitions	= at2440evb_शेष_nand_part,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_platक्रमm_nand __initdata at2440evb_nand_info = अणु
	.tacls		= 25,
	.twrph0		= 55,
	.twrph1		= 40,
	.nr_sets	= ARRAY_SIZE(at2440evb_nand_sets),
	.sets		= at2440evb_nand_sets,
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_SOFT,
पूर्ण;

/* DM9000AEP 10/100 ethernet controller */

अटल काष्ठा resource at2440evb_dm9k_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_CS3, 4),
	[1] = DEFINE_RES_MEM(S3C2410_CS3 + 4, 4),
	[2] = DEFINE_RES_NAMED(IRQ_EINT7, 1, शून्य, IORESOURCE_IRQ \
					| IORESOURCE_IRQ_HIGHEDGE),
पूर्ण;

अटल काष्ठा dm9000_plat_data at2440evb_dm9k_pdata = अणु
	.flags		= (DM9000_PLATF_16BITONLY | DM9000_PLATF_NO_EEPROM),
पूर्ण;

अटल काष्ठा platक्रमm_device at2440evb_device_eth = अणु
	.name		= "dm9000",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(at2440evb_dm9k_resource),
	.resource	= at2440evb_dm9k_resource,
	.dev		= अणु
		.platक्रमm_data	= &at2440evb_dm9k_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c24xx_mci_pdata at2440evb_mci_pdata __initdata = अणु
	.set_घातer	= s3c24xx_mci_def_set_घातer,
पूर्ण;

अटल काष्ठा gpiod_lookup_table at2440evb_mci_gpio_table = अणु
	.dev_id = "s3c2410-sdi",
	.table = अणु
		/* Card detect S3C2410_GPG(10) */
		GPIO_LOOKUP("GPIOG", 10, "cd", GPIO_ACTIVE_LOW),
		/* bus pins */
		GPIO_LOOKUP_IDX("GPIOE",  5, "bus", 0, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE",  6, "bus", 1, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE",  7, "bus", 2, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE",  8, "bus", 3, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE",  9, "bus", 4, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("GPIOE", 10, "bus", 5, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;


/* 7" LCD panel */

अटल काष्ठा s3c2410fb_display at2440evb_lcd_cfg __initdata = अणु

	.lcdcon5	= S3C2410_LCDCON5_FRM565 |
			  S3C2410_LCDCON5_INVVLINE |
			  S3C2410_LCDCON5_INVVFRAME |
			  S3C2410_LCDCON5_PWREN |
			  S3C2410_LCDCON5_HWSWP,

	.type		= S3C2410_LCDCON1_TFT,

	.width		= 800,
	.height		= 480,

	.pixघड़ी	= 33333, /* HCLK 60 MHz, भागisor 2 */
	.xres		= 800,
	.yres		= 480,
	.bpp		= 16,
	.left_margin	= 88,
	.right_margin	= 40,
	.hsync_len	= 128,
	.upper_margin	= 32,
	.lower_margin	= 11,
	.vsync_len	= 2,
पूर्ण;

अटल काष्ठा s3c2410fb_mach_info at2440evb_fb_info __initdata = अणु
	.displays	= &at2440evb_lcd_cfg,
	.num_displays	= 1,
	.शेष_display = 0,
पूर्ण;

अटल काष्ठा platक्रमm_device *at2440evb_devices[] __initdata = अणु
	&s3c_device_ohci,
	&s3c_device_wdt,
	&s3c_device_adc,
	&s3c_device_i2c0,
	&s3c_device_rtc,
	&s3c_device_nand,
	&s3c_device_sdi,
	&s3c_device_lcd,
	&at2440evb_device_eth,
पूर्ण;

अटल व्योम __init at2440evb_map_io(व्योम)
अणु
	s3c24xx_init_io(at2440evb_iodesc, ARRAY_SIZE(at2440evb_iodesc));
	s3c24xx_init_uarts(at2440evb_uartcfgs, ARRAY_SIZE(at2440evb_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init at2440evb_init_समय(व्योम)
अणु
	s3c2440_init_घड़ीs(16934400);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init at2440evb_init(व्योम)
अणु
	s3c24xx_fb_set_platdata(&at2440evb_fb_info);
	gpiod_add_lookup_table(&at2440evb_mci_gpio_table);
	s3c24xx_mci_set_platdata(&at2440evb_mci_pdata);
	s3c_nand_set_platdata(&at2440evb_nand_info);
	s3c_i2c0_set_platdata(शून्य);

	platक्रमm_add_devices(at2440evb_devices, ARRAY_SIZE(at2440evb_devices));
पूर्ण


MACHINE_START(AT2440EVB, "AT2440EVB")
	.atag_offset	= 0x100,
	.map_io		= at2440evb_map_io,
	.init_machine	= at2440evb_init,
	.init_irq	= s3c2440_init_irq,
	.init_समय	= at2440evb_init_समय,
MACHINE_END
