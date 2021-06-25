<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2006 American Microप्रणालीs Limited
//	David Anders <danders@amltd.com>
//
// @History:
// derived from linux/arch/arm/mach-s3c2410/mach-bast.c, written by
// Ben Dooks <ben@simtec.co.uk>

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <linux/platक्रमm_data/fb-s3c2410.h>

#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश "devs.h"
#समावेश "cpu.h"
#समावेश "gpio-cfg.h"

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/physmap.h>

#समावेश "s3c24xx.h"

अटल काष्ठा resource amlm5900_nor_resource =
			DEFINE_RES_MEM(0x00000000, SZ_16M);

अटल काष्ठा mtd_partition amlm5900_mtd_partitions[] = अणु
	अणु
		.name		= "System",
		.size		= 0x240000,
		.offset		= 0,
		.mask_flags 	= MTD_WRITEABLE,  /* क्रमce पढ़ो-only */
	पूर्ण, अणु
		.name		= "Kernel",
		.size		= 0x100000,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण, अणु
		.name		= "Ramdisk",
		.size		= 0x300000,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण, अणु
		.name		= "JFFS2",
		.size		= 0x9A0000,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण, अणु
		.name		= "Settings",
		.size		= MTDPART_SIZ_FULL,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data amlm5900_flash_data = अणु
	.width		= 2,
	.parts		= amlm5900_mtd_partitions,
	.nr_parts	= ARRAY_SIZE(amlm5900_mtd_partitions),
पूर्ण;

अटल काष्ठा platक्रमm_device amlm5900_device_nor = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev = अणु
			.platक्रमm_data = &amlm5900_flash_data,
		पूर्ण,
	.num_resources	= 1,
	.resource	= &amlm5900_nor_resource,
पूर्ण;

अटल काष्ठा map_desc amlm5900_iodesc[] __initdata = अणु
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#घोषणा UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg amlm5900_uartcfgs[] = अणु
	[0] = अणु
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण,
	[1] = अणु
		.hwport	     = 1,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण,
	[2] = अणु
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण
पूर्ण;

अटल काष्ठा gpiod_lookup_table amlm5900_mmc_gpio_table = अणु
	.dev_id = "s3c2410-sdi",
	.table = अणु
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

अटल काष्ठा platक्रमm_device *amlm5900_devices[] __initdata = अणु
#अगर_घोषित CONFIG_FB_S3C2410
	&s3c_device_lcd,
#पूर्ण_अगर
	&s3c_device_adc,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_ohci,
 	&s3c_device_rtc,
	&s3c_device_usbgadget,
        &s3c_device_sdi,
	&amlm5900_device_nor,
पूर्ण;

अटल व्योम __init amlm5900_map_io(व्योम)
अणु
	s3c24xx_init_io(amlm5900_iodesc, ARRAY_SIZE(amlm5900_iodesc));
	s3c24xx_init_uarts(amlm5900_uartcfgs, ARRAY_SIZE(amlm5900_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init amlm5900_init_समय(व्योम)
अणु
	s3c2410_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

#अगर_घोषित CONFIG_FB_S3C2410
अटल काष्ठा s3c2410fb_display __initdata amlm5900_lcd_info = अणु
	.width		= 160,
	.height		= 160,

	.type		= S3C2410_LCDCON1_STN4,

	.pixघड़ी	= 680000, /* HCLK = 100MHz */
	.xres		= 160,
	.yres		= 160,
	.bpp		= 4,
	.left_margin	= 1 << (4 + 3),
	.right_margin	= 8 << 3,
	.hsync_len	= 48,
	.upper_margin	= 0,
	.lower_margin	= 0,

	.lcdcon5	= 0x00000001,
पूर्ण;

अटल काष्ठा s3c2410fb_mach_info __initdata amlm5900_fb_info = अणु

	.displays = &amlm5900_lcd_info,
	.num_displays = 1,
	.शेष_display = 0,

	.gpccon =	0xaaaaaaaa,
	.gpccon_mask =	0xffffffff,
	.gpccon_reg =	S3C2410_GPCCON,
	.gpcup =	0x0000ffff,
	.gpcup_mask =	0xffffffff,
	.gpcup_reg =	S3C2410_GPCUP,

	.gpdcon =	0xaaaaaaaa,
	.gpdcon_mask =	0xffffffff,
	.gpdcon_reg =	S3C2410_GPDCON,
	.gpdup =	0x0000ffff,
	.gpdup_mask =	0xffffffff,
	.gpdup_reg =	S3C2410_GPDUP,
पूर्ण;
#पूर्ण_अगर

अटल irqवापस_t
amlm5900_wake_पूर्णांकerrupt(पूर्णांक irq, व्योम *ignored)
अणु
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम amlm5900_init_pm(व्योम)
अणु
	पूर्णांक ret = 0;

	ret = request_irq(IRQ_EINT9, &amlm5900_wake_पूर्णांकerrupt,
				IRQF_TRIGGER_RISING | IRQF_SHARED,
				"amlm5900_wakeup", &amlm5900_wake_पूर्णांकerrupt);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "AML-M5900: no wakeup irq, %d?\n", ret);
	पूर्ण अन्यथा अणु
		enable_irq_wake(IRQ_EINT9);
		/* configure the suspend/resume status pin */
		s3c_gpio_cfgpin(S3C2410_GPF(2), S3C2410_GPIO_OUTPUT);
		s3c_gpio_setpull(S3C2410_GPF(2), S3C_GPIO_PULL_UP);
	पूर्ण
पूर्ण
अटल व्योम __init amlm5900_init(व्योम)
अणु
	amlm5900_init_pm();
#अगर_घोषित CONFIG_FB_S3C2410
	s3c24xx_fb_set_platdata(&amlm5900_fb_info);
#पूर्ण_अगर
	s3c_i2c0_set_platdata(शून्य);
	gpiod_add_lookup_table(&amlm5900_mmc_gpio_table);
	platक्रमm_add_devices(amlm5900_devices, ARRAY_SIZE(amlm5900_devices));
पूर्ण

MACHINE_START(AML_M5900, "AML_M5900")
	.atag_offset	= 0x100,
	.map_io		= amlm5900_map_io,
	.init_irq	= s3c2410_init_irq,
	.init_machine	= amlm5900_init,
	.init_समय	= amlm5900_init_समय,
MACHINE_END
