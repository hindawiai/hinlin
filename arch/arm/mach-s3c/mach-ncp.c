<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2008-2009 Samsung Electronics

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
#समावेश <linux/i2c.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>

#समावेश <video/platक्रमm_lcd.h>
#समावेश <video/samsung_fimd.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <mach/irqs.h>
#समावेश "map.h"

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश "fb.h"

#समावेश "devs.h"
#समावेश "cpu.h"

#समावेश "s3c64xx.h"

#घोषणा UCON S3C2410_UCON_DEFAULT
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE
#घोषणा UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg ncp_uartcfgs[] __initdata = अणु
	/* REVISIT: NCP uses only serial 1, 2 */
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
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *ncp_devices[] __initdata = अणु
	&s3c_device_hsmmc1,
	&s3c_device_i2c0,
पूर्ण;

अटल काष्ठा map_desc ncp_iodesc[] __initdata = अणुपूर्ण;

अटल व्योम __init ncp_map_io(व्योम)
अणु
	s3c64xx_init_io(ncp_iodesc, ARRAY_SIZE(ncp_iodesc));
	s3c64xx_set_xtal_freq(12000000);
	s3c24xx_init_uarts(ncp_uartcfgs, ARRAY_SIZE(ncp_uartcfgs));
	s3c64xx_set_समयr_source(S3C64XX_PWM3, S3C64XX_PWM4);
पूर्ण

अटल व्योम __init ncp_machine_init(व्योम)
अणु
	s3c_i2c0_set_platdata(शून्य);

	platक्रमm_add_devices(ncp_devices, ARRAY_SIZE(ncp_devices));
पूर्ण

MACHINE_START(NCP, "NCP")
	/* Maपूर्णांकainer: Samsung Electronics */
	.atag_offset	= 0x100,
	.nr_irqs	= S3C64XX_NR_IRQS,
	.init_irq	= s3c6410_init_irq,
	.map_io		= ncp_map_io,
	.init_machine	= ncp_machine_init,
	.init_समय	= s3c64xx_समयr_init,
MACHINE_END
