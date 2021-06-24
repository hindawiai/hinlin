<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2007 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//
// http://www.fluff.org/ben/smdk2443/
//
// Thanks to Samsung क्रम the loan of an SMDK2443

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

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "regs-gpio.h"

#समावेश <linux/platक्रमm_data/fb-s3c2410.h>
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>

#समावेश "devs.h"
#समावेश "cpu.h"

#समावेश "s3c24xx.h"
#समावेश "common-smdk-s3c24xx.h"

अटल काष्ठा map_desc smdk2443_iodesc[] __initdata = अणु
	/* ISA IO Space map (memory space selected by A24) */

	अणु
		.भव	= (u32)S3C24XX_VA_ISA_WORD,
		.pfn		= __phys_to_pfn(S3C2410_CS2),
		.length		= 0x10000,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (u32)S3C24XX_VA_ISA_WORD + 0x10000,
		.pfn		= __phys_to_pfn(S3C2410_CS2 + (1<<24)),
		.length		= SZ_4M,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (u32)S3C24XX_VA_ISA_BYTE,
		.pfn		= __phys_to_pfn(S3C2410_CS2),
		.length		= 0x10000,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (u32)S3C24XX_VA_ISA_BYTE + 0x10000,
		.pfn		= __phys_to_pfn(S3C2410_CS2 + (1<<24)),
		.length		= SZ_4M,
		.type		= MT_DEVICE,
	पूर्ण
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT | S3C2410_UCON_UCLK
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#घोषणा UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg smdk2443_uartcfgs[] __initdata = अणु
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
	/* IR port */
	[2] = अणु
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = 0x3c5,
		.ulcon	     = 0x43,
		.ufcon	     = 0x51,
	पूर्ण,
	[3] = अणु
		.hwport	     = 3,
		.flags	     = 0,
		.ucon	     = 0x3c5,
		.ulcon	     = 0x03,
		.ufcon	     = 0x51,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device *smdk2443_devices[] __initdata = अणु
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_hsmmc1,
	&s3c2443_device_dma,
पूर्ण;

अटल व्योम __init smdk2443_map_io(व्योम)
अणु
	s3c24xx_init_io(smdk2443_iodesc, ARRAY_SIZE(smdk2443_iodesc));
	s3c24xx_init_uarts(smdk2443_uartcfgs, ARRAY_SIZE(smdk2443_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init smdk2443_init_समय(व्योम)
अणु
	s3c2443_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init smdk2443_machine_init(व्योम)
अणु
	s3c_i2c0_set_platdata(शून्य);
	platक्रमm_add_devices(smdk2443_devices, ARRAY_SIZE(smdk2443_devices));
	smdk_machine_init();
पूर्ण

MACHINE_START(SMDK2443, "SMDK2443")
	/* Maपूर्णांकainer: Ben Dooks <ben-linux@fluff.org> */
	.atag_offset	= 0x100,

	.init_irq	= s3c2443_init_irq,
	.map_io		= smdk2443_map_io,
	.init_machine	= smdk2443_machine_init,
	.init_समय	= smdk2443_init_समय,
MACHINE_END
