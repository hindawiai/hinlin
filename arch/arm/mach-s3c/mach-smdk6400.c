<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach-types.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <mach/irqs.h>
#समावेश "map.h"

#समावेश "devs.h"
#समावेश "cpu.h"
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश "gpio-samsung.h"

#समावेश "s3c64xx.h"

#घोषणा UCON S3C2410_UCON_DEFAULT | S3C2410_UCON_UCLK
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#घोषणा UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg smdk6400_uartcfgs[] __initdata = अणु
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
पूर्ण;

अटल काष्ठा map_desc smdk6400_iodesc[] = अणुपूर्ण;

अटल व्योम __init smdk6400_map_io(व्योम)
अणु
	s3c64xx_init_io(smdk6400_iodesc, ARRAY_SIZE(smdk6400_iodesc));
	s3c64xx_set_xtal_freq(12000000);
	s3c24xx_init_uarts(smdk6400_uartcfgs, ARRAY_SIZE(smdk6400_uartcfgs));
	s3c64xx_set_समयr_source(S3C64XX_PWM3, S3C64XX_PWM4);
पूर्ण

अटल काष्ठा platक्रमm_device *smdk6400_devices[] __initdata = अणु
	&s3c_device_hsmmc1,
	&s3c_device_i2c0,
पूर्ण;

अटल काष्ठा i2c_board_info i2c_devs[] __initdata = अणु
	अणु I2C_BOARD_INFO("wm8753", 0x1A), पूर्ण,
	अणु I2C_BOARD_INFO("24c08", 0x50), पूर्ण,
पूर्ण;

अटल व्योम __init smdk6400_machine_init(व्योम)
अणु
	i2c_रेजिस्टर_board_info(0, i2c_devs, ARRAY_SIZE(i2c_devs));
	platक्रमm_add_devices(smdk6400_devices, ARRAY_SIZE(smdk6400_devices));
पूर्ण

MACHINE_START(SMDK6400, "SMDK6400")
	/* Maपूर्णांकainer: Ben Dooks <ben-linux@fluff.org> */
	.atag_offset	= 0x100,
	.nr_irqs	= S3C64XX_NR_IRQS,
	.init_irq	= s3c6400_init_irq,
	.map_io		= smdk6400_map_io,
	.init_machine	= smdk6400_machine_init,
	.init_समय	= s3c64xx_समयr_init,
MACHINE_END
