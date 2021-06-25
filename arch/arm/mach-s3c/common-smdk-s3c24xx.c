<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2006 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//
// Common code क्रम SMDK2410 and SMDK2440 boards
//
// http://www.fluff.org/ben/smdk2440/

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/irq.h>

#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"
#समावेश <linux/platक्रमm_data/leds-s3c24xx.h>
#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>

#समावेश "gpio-cfg.h"
#समावेश "devs.h"
#समावेश "pm.h"

#समावेश "common-smdk-s3c24xx.h"

/* LED devices */

अटल काष्ठा gpiod_lookup_table smdk_led4_gpio_table = अणु
	.dev_id = "s3c24xx_led.0",
	.table = अणु
		GPIO_LOOKUP("GPF", 4, शून्य, GPIO_ACTIVE_LOW | GPIO_OPEN_DRAIN),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table smdk_led5_gpio_table = अणु
	.dev_id = "s3c24xx_led.1",
	.table = अणु
		GPIO_LOOKUP("GPF", 5, शून्य, GPIO_ACTIVE_LOW | GPIO_OPEN_DRAIN),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table smdk_led6_gpio_table = अणु
	.dev_id = "s3c24xx_led.2",
	.table = अणु
		GPIO_LOOKUP("GPF", 6, शून्य, GPIO_ACTIVE_LOW | GPIO_OPEN_DRAIN),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table smdk_led7_gpio_table = अणु
	.dev_id = "s3c24xx_led.3",
	.table = अणु
		GPIO_LOOKUP("GPF", 7, शून्य, GPIO_ACTIVE_LOW | GPIO_OPEN_DRAIN),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata smdk_pdata_led4 = अणु
	.name		= "led4",
	.def_trigger	= "timer",
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata smdk_pdata_led5 = अणु
	.name		= "led5",
	.def_trigger	= "nand-disk",
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata smdk_pdata_led6 = अणु
	.name		= "led6",
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata smdk_pdata_led7 = अणु
	.name		= "led7",
पूर्ण;

अटल काष्ठा platक्रमm_device smdk_led4 = अणु
	.name		= "s3c24xx_led",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data = &smdk_pdata_led4,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device smdk_led5 = अणु
	.name		= "s3c24xx_led",
	.id		= 1,
	.dev		= अणु
		.platक्रमm_data = &smdk_pdata_led5,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device smdk_led6 = अणु
	.name		= "s3c24xx_led",
	.id		= 2,
	.dev		= अणु
		.platक्रमm_data = &smdk_pdata_led6,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device smdk_led7 = अणु
	.name		= "s3c24xx_led",
	.id		= 3,
	.dev		= अणु
		.platक्रमm_data = &smdk_pdata_led7,
	पूर्ण,
पूर्ण;

/* न_अंकD parititon from 2.4.18-swl5 */

अटल काष्ठा mtd_partition smdk_शेष_nand_part[] = अणु
	[0] = अणु
		.name	= "Boot Agent",
		.size	= SZ_16K,
		.offset	= 0,
	पूर्ण,
	[1] = अणु
		.name	= "S3C2410 flash partition 1",
		.offset = 0,
		.size	= SZ_2M,
	पूर्ण,
	[2] = अणु
		.name	= "S3C2410 flash partition 2",
		.offset = SZ_4M,
		.size	= SZ_4M,
	पूर्ण,
	[3] = अणु
		.name	= "S3C2410 flash partition 3",
		.offset	= SZ_8M,
		.size	= SZ_2M,
	पूर्ण,
	[4] = अणु
		.name	= "S3C2410 flash partition 4",
		.offset = SZ_1M * 10,
		.size	= SZ_4M,
	पूर्ण,
	[5] = अणु
		.name	= "S3C2410 flash partition 5",
		.offset	= SZ_1M * 14,
		.size	= SZ_1M * 10,
	पूर्ण,
	[6] = अणु
		.name	= "S3C2410 flash partition 6",
		.offset	= SZ_1M * 24,
		.size	= SZ_1M * 24,
	पूर्ण,
	[7] = अणु
		.name	= "S3C2410 flash partition 7",
		.offset = SZ_1M * 48,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

अटल काष्ठा s3c2410_nand_set smdk_nand_sets[] = अणु
	[0] = अणु
		.name		= "NAND",
		.nr_chips	= 1,
		.nr_partitions	= ARRAY_SIZE(smdk_शेष_nand_part),
		.partitions	= smdk_शेष_nand_part,
	पूर्ण,
पूर्ण;

/* choose a set of timings which should suit most 512Mbit
 * chips and beyond.
*/

अटल काष्ठा s3c2410_platक्रमm_nand smdk_nand_info = अणु
	.tacls		= 20,
	.twrph0		= 60,
	.twrph1		= 20,
	.nr_sets	= ARRAY_SIZE(smdk_nand_sets),
	.sets		= smdk_nand_sets,
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_SOFT,
पूर्ण;

/* devices we initialise */

अटल काष्ठा platक्रमm_device __initdata *smdk_devs[] = अणु
	&s3c_device_nand,
	&smdk_led4,
	&smdk_led5,
	&smdk_led6,
	&smdk_led7,
पूर्ण;

व्योम __init smdk_machine_init(व्योम)
अणु
	अगर (machine_is_smdk2443())
		smdk_nand_info.twrph0 = 50;

	s3c_nand_set_platdata(&smdk_nand_info);

	/* Disable pull-up on the LED lines */
	s3c_gpio_setpull(S3C2410_GPF(4), S3C_GPIO_PULL_NONE);
	s3c_gpio_setpull(S3C2410_GPF(5), S3C_GPIO_PULL_NONE);
	s3c_gpio_setpull(S3C2410_GPF(6), S3C_GPIO_PULL_NONE);
	s3c_gpio_setpull(S3C2410_GPF(7), S3C_GPIO_PULL_NONE);

	/* Add lookups क्रम the lines */
	gpiod_add_lookup_table(&smdk_led4_gpio_table);
	gpiod_add_lookup_table(&smdk_led5_gpio_table);
	gpiod_add_lookup_table(&smdk_led6_gpio_table);
	gpiod_add_lookup_table(&smdk_led7_gpio_table);

	platक्रमm_add_devices(smdk_devs, ARRAY_SIZE(smdk_devs));

	s3c_pm_init();
पूर्ण
