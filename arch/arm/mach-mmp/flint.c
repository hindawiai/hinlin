<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/flपूर्णांक.c
 *
 *  Support क्रम the Marvell Flपूर्णांक Development Platक्रमm.
 *
 *  Copyright (C) 2009 Marvell International Ltd.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio-pxa.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "addr-map.h"
#समावेश "mfp-mmp2.h"
#समावेश "mmp2.h"
#समावेश "irqs.h"

#समावेश "common.h"

#घोषणा FLINT_NR_IRQS	(MMP_NR_IRQS + 48)

अटल अचिन्हित दीर्घ flपूर्णांक_pin_config[] __initdata = अणु
	/* UART1 */
	GPIO45_UART1_RXD,
	GPIO46_UART1_TXD,

	/* UART2 */
	GPIO47_UART2_RXD,
	GPIO48_UART2_TXD,

	/* SMC */
	GPIO151_SMC_SCLK,
	GPIO145_SMC_nCS0,
	GPIO146_SMC_nCS1,
	GPIO152_SMC_BE0,
	GPIO153_SMC_BE1,
	GPIO154_SMC_IRQ,
	GPIO113_SMC_RDY,

	/*Ethernet*/
	GPIO155_GPIO,

	/* DFI */
	GPIO168_DFI_D0,
	GPIO167_DFI_D1,
	GPIO166_DFI_D2,
	GPIO165_DFI_D3,
	GPIO107_DFI_D4,
	GPIO106_DFI_D5,
	GPIO105_DFI_D6,
	GPIO104_DFI_D7,
	GPIO111_DFI_D8,
	GPIO164_DFI_D9,
	GPIO163_DFI_D10,
	GPIO162_DFI_D11,
	GPIO161_DFI_D12,
	GPIO110_DFI_D13,
	GPIO109_DFI_D14,
	GPIO108_DFI_D15,
	GPIO143_ND_nCS0,
	GPIO144_ND_nCS1,
	GPIO147_ND_nWE,
	GPIO148_ND_nRE,
	GPIO150_ND_ALE,
	GPIO149_ND_CLE,
	GPIO112_ND_RDY0,
	GPIO160_ND_RDY1,
पूर्ण;

अटल काष्ठा pxa_gpio_platक्रमm_data mmp2_gpio_pdata = अणु
	.irq_base	= MMP_GPIO_TO_IRQ(0),
पूर्ण;

अटल काष्ठा smc91x_platdata flपूर्णांक_smc91x_info = अणु
	.flags  = SMC91X_USE_16BIT | SMC91X_NOWAIT,
पूर्ण;

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.start  = SMC_CS1_PHYS_BASE + 0x300,
		.end    = SMC_CS1_PHYS_BASE + 0xfffff,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = MMP_GPIO_TO_IRQ(155),
		.end    = MMP_GPIO_TO_IRQ(155),
		.flags  = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name           = "smc91x",
	.id             = 0,
	.dev            = अणु
		.platक्रमm_data = &flपूर्णांक_smc91x_info,
	पूर्ण,
	.num_resources  = ARRAY_SIZE(smc91x_resources),
	.resource       = smc91x_resources,
पूर्ण;

अटल व्योम __init flपूर्णांक_init(व्योम)
अणु
	mfp_config(ARRAY_AND_SIZE(flपूर्णांक_pin_config));

	/* on-chip devices */
	mmp2_add_uart(1);
	mmp2_add_uart(2);
	platक्रमm_device_add_data(&mmp2_device_gpio, &mmp2_gpio_pdata,
				 माप(काष्ठा pxa_gpio_platक्रमm_data));
	platक्रमm_device_रेजिस्टर(&mmp2_device_gpio);

	/* off-chip devices */
	platक्रमm_device_रेजिस्टर(&smc91x_device);
पूर्ण

MACHINE_START(FLINT, "Flint Development Platform")
	.map_io		= mmp_map_io,
	.nr_irqs	= FLINT_NR_IRQS,
	.init_irq       = mmp2_init_irq,
	.init_समय	= mmp2_समयr_init,
	.init_machine   = flपूर्णांक_init,
	.restart	= mmp_restart,
MACHINE_END
