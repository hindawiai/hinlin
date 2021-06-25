<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7619 Setup
 *
 *  Copyright (C) 2006  Yoshinori Sato
 *  Copyright (C) 2009  Paul Mundt
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/sh_eth.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/platक्रमm_early.h>

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */
	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7,
	WDT, EDMAC, CMT0, CMT1,
	SCIF0, SCIF1, SCIF2,
	HIF_HIFI, HIF_HIFBI,
	DMAC0, DMAC1, DMAC2, DMAC3,
	SIOF,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_IRQ(IRQ0, 64), INTC_IRQ(IRQ1, 65),
	INTC_IRQ(IRQ2, 66), INTC_IRQ(IRQ3, 67),
	INTC_IRQ(IRQ4, 80), INTC_IRQ(IRQ5, 81),
	INTC_IRQ(IRQ6, 82), INTC_IRQ(IRQ7, 83),
	INTC_IRQ(WDT, 84), INTC_IRQ(EDMAC, 85),
	INTC_IRQ(CMT0, 86), INTC_IRQ(CMT1, 87),
	INTC_IRQ(SCIF0, 88), INTC_IRQ(SCIF0, 89),
	INTC_IRQ(SCIF0, 90), INTC_IRQ(SCIF0, 91),
	INTC_IRQ(SCIF1, 92), INTC_IRQ(SCIF1, 93),
	INTC_IRQ(SCIF1, 94), INTC_IRQ(SCIF1, 95),
	INTC_IRQ(SCIF2, 96), INTC_IRQ(SCIF2, 97),
	INTC_IRQ(SCIF2, 98), INTC_IRQ(SCIF2, 99),
	INTC_IRQ(HIF_HIFI, 100), INTC_IRQ(HIF_HIFBI, 101),
	INTC_IRQ(DMAC0, 104), INTC_IRQ(DMAC1, 105),
	INTC_IRQ(DMAC2, 106), INTC_IRQ(DMAC3, 107),
	INTC_IRQ(SIOF, 108),
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xf8140006, 0, 16, 4, /* IPRA */ अणु IRQ0, IRQ1, IRQ2, IRQ3 पूर्ण पूर्ण,
	अणु 0xf8140008, 0, 16, 4, /* IPRB */ अणु IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
	अणु 0xf8080000, 0, 16, 4, /* IPRC */ अणु WDT, EDMAC, CMT0, CMT1 पूर्ण पूर्ण,
	अणु 0xf8080002, 0, 16, 4, /* IPRD */ अणु SCIF0, SCIF1, SCIF2 पूर्ण पूर्ण,
	अणु 0xf8080004, 0, 16, 4, /* IPRE */ अणु HIF_HIFI, HIF_HIFBI पूर्ण पूर्ण,
	अणु 0xf8080006, 0, 16, 4, /* IPRF */ अणु DMAC0, DMAC1, DMAC2, DMAC3 पूर्ण पूर्ण,
	अणु 0xf8080008, 0, 16, 4, /* IPRG */ अणु SIOF पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh7619", vectors, शून्य,
			 शून्य, prio_रेजिस्टरs, शून्य);

अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xf8400000, 0x100),
	DEFINE_RES_IRQ(88),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर0_device = अणु
	.name		= "sh-sci",
	.id		= 0,
	.resource	= scअगर0_resources,
	.num_resources	= ARRAY_SIZE(scअगर0_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर0_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर1_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर1_resources[] = अणु
	DEFINE_RES_MEM(0xf8410000, 0x100),
	DEFINE_RES_IRQ(92),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर1_device = अणु
	.name		= "sh-sci",
	.id		= 1,
	.resource	= scअगर1_resources,
	.num_resources	= ARRAY_SIZE(scअगर1_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर1_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर2_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर2_resources[] = अणु
	DEFINE_RES_MEM(0xf8420000, 0x100),
	DEFINE_RES_IRQ(96),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर2_device = अणु
	.name		= "sh-sci",
	.id		= 2,
	.resource	= scअगर2_resources,
	.num_resources	= ARRAY_SIZE(scअगर2_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर2_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_eth_plat_data eth_platक्रमm_data = अणु
	.phy		= 1,
	.phy_पूर्णांकerface	= PHY_INTERFACE_MODE_MII,
पूर्ण;

अटल काष्ठा resource eth_resources[] = अणु
	[0] = अणु
		.start = 0xfb000000,
		.end = 0xfb0001c7,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start = 85,
		.end = 85,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device eth_device = अणु
	.name = "sh7619-ether",
	.id = -1,
	.dev = अणु
		.platक्रमm_data = &eth_platक्रमm_data,
	पूर्ण,
	.num_resources = ARRAY_SIZE(eth_resources),
	.resource = eth_resources,
पूर्ण;

अटल काष्ठा sh_समयr_config cmt_platक्रमm_data = अणु
	.channels_mask = 3,
पूर्ण;

अटल काष्ठा resource cmt_resources[] = अणु
	DEFINE_RES_MEM(0xf84a0070, 0x10),
	DEFINE_RES_IRQ(86),
	DEFINE_RES_IRQ(87),
पूर्ण;

अटल काष्ठा platक्रमm_device cmt_device = अणु
	.name		= "sh-cmt-16",
	.id		= 0,
	.dev = अणु
		.platक्रमm_data	= &cmt_platक्रमm_data,
	पूर्ण,
	.resource	= cmt_resources,
	.num_resources	= ARRAY_SIZE(cmt_resources),
पूर्ण;

अटल काष्ठा platक्रमm_device *sh7619_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&eth_device,
	&cmt_device,
पूर्ण;

अटल पूर्णांक __init sh7619_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sh7619_devices,
				    ARRAY_SIZE(sh7619_devices));
पूर्ण
arch_initcall(sh7619_devices_setup);

व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
पूर्ण

अटल काष्ठा platक्रमm_device *sh7619_early_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&cmt_device,
पूर्ण;

#घोषणा STBCR3 0xf80a0000

व्योम __init plat_early_device_setup(व्योम)
अणु
	/* enable CMT घड़ी */
	__raw_ग_लिखोb(__raw_पढ़ोb(STBCR3) & ~0x10, STBCR3);

	sh_early_platक्रमm_add_devices(sh7619_early_devices,
				   ARRAY_SIZE(sh7619_early_devices));
पूर्ण
