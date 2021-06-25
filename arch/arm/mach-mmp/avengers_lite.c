<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/avengers_lite.c
 *
 *  Support क्रम the Marvell PXA168-based Avengers lite Development Platक्रमm.
 *
 *  Copyright (C) 2009-2010 Marvell International Ltd.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/gpio-pxa.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "addr-map.h"
#समावेश "mfp-pxa168.h"
#समावेश "pxa168.h"
#समावेश "irqs.h"


#समावेश "common.h"
#समावेश <linux/delay.h>

/* Avengers lite MFP configurations */
अटल अचिन्हित दीर्घ avengers_lite_pin_config_V16F[] __initdata = अणु
	/* DEBUG_UART */
	GPIO88_UART2_TXD,
	GPIO89_UART2_RXD,
पूर्ण;

अटल काष्ठा pxa_gpio_platक्रमm_data pxa168_gpio_pdata = अणु
	.irq_base	= MMP_GPIO_TO_IRQ(0),
पूर्ण;

अटल व्योम __init avengers_lite_init(व्योम)
अणु
	mfp_config(ARRAY_AND_SIZE(avengers_lite_pin_config_V16F));

	/* on-chip devices */
	pxa168_add_uart(2);
	platक्रमm_device_add_data(&pxa168_device_gpio, &pxa168_gpio_pdata,
				 माप(काष्ठा pxa_gpio_platक्रमm_data));
	platक्रमm_device_रेजिस्टर(&pxa168_device_gpio);
पूर्ण

MACHINE_START(AVENGERS_LITE, "PXA168 Avengers lite Development Platform")
	.map_io		= mmp_map_io,
	.nr_irqs	= MMP_NR_IRQS,
	.init_irq       = pxa168_init_irq,
	.init_समय	= pxa168_समयr_init,
	.init_machine   = avengers_lite_init,
	.restart	= pxa168_restart,
MACHINE_END
