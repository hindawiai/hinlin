<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2007 TinCanTools
//	David Anders <danders@amltd.com>
//
// @History:
// derived from linux/arch/arm/mach-s3c2410/mach-bast.c, written by
// Ben Dooks <ben@simtec.co.uk>

#समावेश <linux/gpio/machine.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश "devs.h"
#समावेश "cpu.h"

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/physmap.h>

#समावेश "s3c24xx.h"

अटल काष्ठा resource tct_hammer_nor_resource =
			DEFINE_RES_MEM(0x00000000, SZ_16M);

अटल काष्ठा mtd_partition tct_hammer_mtd_partitions[] = अणु
	अणु
		.name		= "System",
		.size		= 0x240000,
		.offset		= 0,
		.mask_flags 	= MTD_WRITEABLE,  /* क्रमce पढ़ो-only */
	पूर्ण, अणु
		.name		= "JFFS2",
		.size		= MTDPART_SIZ_FULL,
		.offset		= MTDPART_OFS_APPEND,
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data tct_hammer_flash_data = अणु
	.width		= 2,
	.parts		= tct_hammer_mtd_partitions,
	.nr_parts	= ARRAY_SIZE(tct_hammer_mtd_partitions),
पूर्ण;

अटल काष्ठा platक्रमm_device tct_hammer_device_nor = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev = अणु
			.platक्रमm_data = &tct_hammer_flash_data,
		पूर्ण,
	.num_resources	= 1,
	.resource	= &tct_hammer_nor_resource,
पूर्ण;

अटल काष्ठा map_desc tct_hammer_iodesc[] __initdata = अणु
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#घोषणा UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg tct_hammer_uartcfgs[] = अणु
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

अटल काष्ठा gpiod_lookup_table tct_hammer_mmc_gpio_table = अणु
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

अटल काष्ठा platक्रमm_device *tct_hammer_devices[] __initdata = अणु
	&s3c_device_adc,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_ohci,
	&s3c_device_rtc,
	&s3c_device_usbgadget,
	&s3c_device_sdi,
	&tct_hammer_device_nor,
पूर्ण;

अटल व्योम __init tct_hammer_map_io(व्योम)
अणु
	s3c24xx_init_io(tct_hammer_iodesc, ARRAY_SIZE(tct_hammer_iodesc));
	s3c24xx_init_uarts(tct_hammer_uartcfgs, ARRAY_SIZE(tct_hammer_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init tct_hammer_init_समय(व्योम)
अणु
	s3c2410_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init tct_hammer_init(व्योम)
अणु
	s3c_i2c0_set_platdata(शून्य);
	gpiod_add_lookup_table(&tct_hammer_mmc_gpio_table);
	platक्रमm_add_devices(tct_hammer_devices, ARRAY_SIZE(tct_hammer_devices));
पूर्ण

MACHINE_START(TCT_HAMMER, "TCT_HAMMER")
	.atag_offset	= 0x100,
	.map_io		= tct_hammer_map_io,
	.init_irq	= s3c2410_init_irq,
	.init_machine	= tct_hammer_init,
	.init_समय	= tct_hammer_init_समय,
MACHINE_END
