<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/tavorevb.c
 *
 *  Support क्रम the Marvell PXA910-based TavorEVB Development Platक्रमm.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio-pxa.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/smc91x.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "addr-map.h"
#समावेश "mfp-pxa910.h"
#समावेश "pxa910.h"
#समावेश "irqs.h"

#समावेश "common.h"

अटल अचिन्हित दीर्घ tavorevb_pin_config[] __initdata = अणु
	/* UART2 */
	GPIO47_UART2_RXD,
	GPIO48_UART2_TXD,

	/* SMC */
	SM_nCS0_nCS0,
	SM_ADV_SM_ADV,
	SM_SCLK_SM_SCLK,
	SM_SCLK_SM_SCLK,
	SM_BE0_SM_BE0,
	SM_BE1_SM_BE1,

	/* DFI */
	DF_IO0_ND_IO0,
	DF_IO1_ND_IO1,
	DF_IO2_ND_IO2,
	DF_IO3_ND_IO3,
	DF_IO4_ND_IO4,
	DF_IO5_ND_IO5,
	DF_IO6_ND_IO6,
	DF_IO7_ND_IO7,
	DF_IO8_ND_IO8,
	DF_IO9_ND_IO9,
	DF_IO10_ND_IO10,
	DF_IO11_ND_IO11,
	DF_IO12_ND_IO12,
	DF_IO13_ND_IO13,
	DF_IO14_ND_IO14,
	DF_IO15_ND_IO15,
	DF_nCS0_SM_nCS2_nCS0,
	DF_ALE_SM_WEn_ND_ALE,
	DF_CLE_SM_OEn_ND_CLE,
	DF_WEn_DF_WEn,
	DF_REn_DF_REn,
	DF_RDY0_DF_RDY0,
पूर्ण;

अटल काष्ठा pxa_gpio_platक्रमm_data pxa910_gpio_pdata = अणु
	.irq_base	= MMP_GPIO_TO_IRQ(0),
पूर्ण;

अटल काष्ठा smc91x_platdata tavorevb_smc91x_info = अणु
	.flags	= SMC91X_USE_16BIT | SMC91X_NOWAIT,
पूर्ण;

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.start	= SMC_CS1_PHYS_BASE + 0x300,
		.end	= SMC_CS1_PHYS_BASE + 0xfffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= MMP_GPIO_TO_IRQ(80),
		.end	= MMP_GPIO_TO_IRQ(80),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data = &tavorevb_smc91x_info,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
पूर्ण;

अटल व्योम __init tavorevb_init(व्योम)
अणु
	mfp_config(ARRAY_AND_SIZE(tavorevb_pin_config));

	/* on-chip devices */
	pxa910_add_uart(1);
	platक्रमm_device_add_data(&pxa910_device_gpio, &pxa910_gpio_pdata,
				 माप(काष्ठा pxa_gpio_platक्रमm_data));
	platक्रमm_device_रेजिस्टर(&pxa910_device_gpio);

	/* off-chip devices */
	platक्रमm_device_रेजिस्टर(&smc91x_device);
पूर्ण

MACHINE_START(TAVOREVB, "PXA910 Evaluation Board (aka TavorEVB)")
	.map_io		= mmp_map_io,
	.nr_irqs	= MMP_NR_IRQS,
	.init_irq       = pxa910_init_irq,
	.init_समय	= pxa910_समयr_init,
	.init_machine   = tavorevb_init,
	.restart	= mmp_restart,
MACHINE_END
