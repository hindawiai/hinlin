<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH-X3 Prototype Setup
 *
 *  Copyright (C) 2007 - 2010  Paul Mundt
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <cpu/shx3.h>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/platक्रमm_early.h>

/*
 * This पूर्णांकentionally only रेजिस्टरs SCIF ports 0, 1, and 3. SCIF 2
 * INTEVT values overlap with the FPU EXPEVT ones, requiring special
 * demuxing in the exception dispatch path.
 *
 * As this overlap is something that never should have made it in to
 * silicon in the first place, we just refuse to deal with the port at
 * all rather than adding infraकाष्ठाure to hack around it.
 */
अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xffc30000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x700)),
	DEFINE_RES_IRQ(evt2irq(0x720)),
	DEFINE_RES_IRQ(evt2irq(0x760)),
	DEFINE_RES_IRQ(evt2irq(0x740)),
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
	DEFINE_RES_MEM(0xffc40000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x780)),
	DEFINE_RES_IRQ(evt2irq(0x7a0)),
	DEFINE_RES_IRQ(evt2irq(0x7e0)),
	DEFINE_RES_IRQ(evt2irq(0x7c0)),
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
	DEFINE_RES_MEM(0xffc60000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x880)),
	DEFINE_RES_IRQ(evt2irq(0x8a0)),
	DEFINE_RES_IRQ(evt2irq(0x8e0)),
	DEFINE_RES_IRQ(evt2irq(0x8c0)),
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

अटल काष्ठा sh_समयr_config पंचांगu0_platक्रमm_data = अणु
	.channels_mask = 7,
पूर्ण;

अटल काष्ठा resource पंचांगu0_resources[] = अणु
	DEFINE_RES_MEM(0xffc10000, 0x30),
	DEFINE_RES_IRQ(evt2irq(0x400)),
	DEFINE_RES_IRQ(evt2irq(0x420)),
	DEFINE_RES_IRQ(evt2irq(0x440)),
पूर्ण;

अटल काष्ठा platक्रमm_device पंचांगu0_device = अणु
	.name		= "sh-tmu",
	.id		= 0,
	.dev = अणु
		.platक्रमm_data	= &पंचांगu0_platक्रमm_data,
	पूर्ण,
	.resource	= पंचांगu0_resources,
	.num_resources	= ARRAY_SIZE(पंचांगu0_resources),
पूर्ण;

अटल काष्ठा sh_समयr_config पंचांगu1_platक्रमm_data = अणु
	.channels_mask = 7,
पूर्ण;

अटल काष्ठा resource पंचांगu1_resources[] = अणु
	DEFINE_RES_MEM(0xffc20000, 0x2c),
	DEFINE_RES_IRQ(evt2irq(0x460)),
	DEFINE_RES_IRQ(evt2irq(0x480)),
	DEFINE_RES_IRQ(evt2irq(0x4a0)),
पूर्ण;

अटल काष्ठा platक्रमm_device पंचांगu1_device = अणु
	.name		= "sh-tmu",
	.id		= 1,
	.dev = अणु
		.platक्रमm_data	= &पंचांगu1_platक्रमm_data,
	पूर्ण,
	.resource	= पंचांगu1_resources,
	.num_resources	= ARRAY_SIZE(पंचांगu1_resources),
पूर्ण;

अटल काष्ठा platक्रमm_device *shx3_early_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&पंचांगu0_device,
	&पंचांगu1_device,
पूर्ण;

अटल पूर्णांक __init shx3_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(shx3_early_devices,
				   ARRAY_SIZE(shx3_early_devices));
पूर्ण
arch_initcall(shx3_devices_setup);

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(shx3_early_devices,
				   ARRAY_SIZE(shx3_early_devices));
पूर्ण

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */
	IRL_LLLL, IRL_LLLH, IRL_LLHL, IRL_LLHH,
	IRL_LHLL, IRL_LHLH, IRL_LHHL, IRL_LHHH,
	IRL_HLLL, IRL_HLLH, IRL_HLHL, IRL_HLHH,
	IRL_HHLL, IRL_HHLH, IRL_HHHL,
	IRQ0, IRQ1, IRQ2, IRQ3,
	HUDII,
	TMU0, TMU1, TMU2, TMU3, TMU4, TMU5,
	PCII0, PCII1, PCII2, PCII3, PCII4,
	PCII5, PCII6, PCII7, PCII8, PCII9,
	SCIF0_ERI, SCIF0_RXI, SCIF0_BRI, SCIF0_TXI,
	SCIF1_ERI, SCIF1_RXI, SCIF1_BRI, SCIF1_TXI,
	SCIF2_ERI, SCIF2_RXI, SCIF2_BRI, SCIF2_TXI,
	SCIF3_ERI, SCIF3_RXI, SCIF3_BRI, SCIF3_TXI,
	DMAC0_DMINT0, DMAC0_DMINT1, DMAC0_DMINT2, DMAC0_DMINT3,
	DMAC0_DMINT4, DMAC0_DMINT5, DMAC0_DMAE,
	DU,
	DMAC1_DMINT6, DMAC1_DMINT7, DMAC1_DMINT8, DMAC1_DMINT9,
	DMAC1_DMINT10, DMAC1_DMINT11, DMAC1_DMAE,
	IIC, VIN0, VIN1, VCORE0, ATAPI,
	DTU0, DTU1, DTU2, DTU3,
	FE0, FE1,
	GPIO0, GPIO1, GPIO2, GPIO3,
	PAM, IRM,
	INTICI0, INTICI1, INTICI2, INTICI3,
	INTICI4, INTICI5, INTICI6, INTICI7,

	/* पूर्णांकerrupt groups */
	IRL, PCII56789, SCIF0, SCIF1, SCIF2, SCIF3,
	DMAC0, DMAC1,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_VECT(HUDII, 0x3e0),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(TMU3, 0x460),
	INTC_VECT(TMU4, 0x480), INTC_VECT(TMU5, 0x4a0),
	INTC_VECT(PCII0, 0x500), INTC_VECT(PCII1, 0x520),
	INTC_VECT(PCII2, 0x540), INTC_VECT(PCII3, 0x560),
	INTC_VECT(PCII4, 0x580), INTC_VECT(PCII5, 0x5a0),
	INTC_VECT(PCII6, 0x5c0), INTC_VECT(PCII7, 0x5e0),
	INTC_VECT(PCII8, 0x600), INTC_VECT(PCII9, 0x620),
	INTC_VECT(SCIF0_ERI, 0x700), INTC_VECT(SCIF0_RXI, 0x720),
	INTC_VECT(SCIF0_BRI, 0x740), INTC_VECT(SCIF0_TXI, 0x760),
	INTC_VECT(SCIF1_ERI, 0x780), INTC_VECT(SCIF1_RXI, 0x7a0),
	INTC_VECT(SCIF1_BRI, 0x7c0), INTC_VECT(SCIF1_TXI, 0x7e0),
	INTC_VECT(SCIF3_ERI, 0x880), INTC_VECT(SCIF3_RXI, 0x8a0),
	INTC_VECT(SCIF3_BRI, 0x8c0), INTC_VECT(SCIF3_TXI, 0x8e0),
	INTC_VECT(DMAC0_DMINT0, 0x900), INTC_VECT(DMAC0_DMINT1, 0x920),
	INTC_VECT(DMAC0_DMINT2, 0x940), INTC_VECT(DMAC0_DMINT3, 0x960),
	INTC_VECT(DMAC0_DMINT4, 0x980), INTC_VECT(DMAC0_DMINT5, 0x9a0),
	INTC_VECT(DMAC0_DMAE, 0x9c0),
	INTC_VECT(DU, 0x9e0),
	INTC_VECT(DMAC1_DMINT6, 0xa00), INTC_VECT(DMAC1_DMINT7, 0xa20),
	INTC_VECT(DMAC1_DMINT8, 0xa40), INTC_VECT(DMAC1_DMINT9, 0xa60),
	INTC_VECT(DMAC1_DMINT10, 0xa80), INTC_VECT(DMAC1_DMINT11, 0xaa0),
	INTC_VECT(DMAC1_DMAE, 0xac0),
	INTC_VECT(IIC, 0xae0),
	INTC_VECT(VIN0, 0xb00), INTC_VECT(VIN1, 0xb20),
	INTC_VECT(VCORE0, 0xb00), INTC_VECT(ATAPI, 0xb60),
	INTC_VECT(DTU0, 0xc00), INTC_VECT(DTU0, 0xc20),
	INTC_VECT(DTU0, 0xc40),
	INTC_VECT(DTU1, 0xc60), INTC_VECT(DTU1, 0xc80),
	INTC_VECT(DTU1, 0xca0),
	INTC_VECT(DTU2, 0xcc0), INTC_VECT(DTU2, 0xce0),
	INTC_VECT(DTU2, 0xd00),
	INTC_VECT(DTU3, 0xd20), INTC_VECT(DTU3, 0xd40),
	INTC_VECT(DTU3, 0xd60),
	INTC_VECT(FE0, 0xe00), INTC_VECT(FE1, 0xe20),
	INTC_VECT(GPIO0, 0xe40), INTC_VECT(GPIO1, 0xe60),
	INTC_VECT(GPIO2, 0xe80), INTC_VECT(GPIO3, 0xea0),
	INTC_VECT(PAM, 0xec0), INTC_VECT(IRM, 0xee0),
	INTC_VECT(INTICI0, 0xf00), INTC_VECT(INTICI1, 0xf20),
	INTC_VECT(INTICI2, 0xf40), INTC_VECT(INTICI3, 0xf60),
	INTC_VECT(INTICI4, 0xf80), INTC_VECT(INTICI5, 0xfa0),
	INTC_VECT(INTICI6, 0xfc0), INTC_VECT(INTICI7, 0xfe0),
पूर्ण;

अटल काष्ठा पूर्णांकc_group groups[] __initdata = अणु
	INTC_GROUP(IRL, IRL_LLLL, IRL_LLLH, IRL_LLHL, IRL_LLHH,
		   IRL_LHLL, IRL_LHLH, IRL_LHHL, IRL_LHHH,
		   IRL_HLLL, IRL_HLLH, IRL_HLHL, IRL_HLHH,
		   IRL_HHLL, IRL_HHLH, IRL_HHHL),
	INTC_GROUP(PCII56789, PCII5, PCII6, PCII7, PCII8, PCII9),
	INTC_GROUP(SCIF0, SCIF0_ERI, SCIF0_RXI, SCIF0_BRI, SCIF0_TXI),
	INTC_GROUP(SCIF1, SCIF1_ERI, SCIF1_RXI, SCIF1_BRI, SCIF1_TXI),
	INTC_GROUP(SCIF3, SCIF3_ERI, SCIF3_RXI, SCIF3_BRI, SCIF3_TXI),
	INTC_GROUP(DMAC0, DMAC0_DMINT0, DMAC0_DMINT1, DMAC0_DMINT2,
		   DMAC0_DMINT3, DMAC0_DMINT4, DMAC0_DMINT5, DMAC0_DMAE),
	INTC_GROUP(DMAC1, DMAC1_DMINT6, DMAC1_DMINT7, DMAC1_DMINT8,
		   DMAC1_DMINT9, DMAC1_DMINT10, DMAC1_DMINT11),
पूर्ण;

#घोषणा INT2DISTCR0	0xfe4108a0
#घोषणा INT2DISTCR1	0xfe4108a4
#घोषणा INT2DISTCR2	0xfe4108a8

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xfe410030, 0xfe410050, 32, /* CnINTMSK0 / CnINTMSKCLR0 */
	  अणु IRQ0, IRQ1, IRQ2, IRQ3 पूर्ण पूर्ण,
	अणु 0xfe410040, 0xfe410060, 32, /* CnINTMSK1 / CnINTMSKCLR1 */
	  अणु IRL पूर्ण पूर्ण,
	अणु 0xfe410820, 0xfe410850, 32, /* CnINT2MSK0 / CnINT2MSKCLR0 */
	  अणु FE1, FE0, 0, ATAPI, VCORE0, VIN1, VIN0, IIC,
	    DU, GPIO3, GPIO2, GPIO1, GPIO0, PAM, 0, 0,
	    0, 0, 0, 0, 0, 0, 0, 0, /* HUDI bits ignored */
	    0, TMU5, TMU4, TMU3, TMU2, TMU1, TMU0, 0, पूर्ण,
	    INTC_SMP_BALANCING(INT2DISTCR0) पूर्ण,
	अणु 0xfe410830, 0xfe410860, 32, /* CnINT2MSK1 / CnINT2MSKCLR1 */
	  अणु 0, 0, 0, 0, DTU3, DTU2, DTU1, DTU0, /* IRM bits ignored */
	    PCII9, PCII8, PCII7, PCII6, PCII5, PCII4, PCII3, PCII2,
	    PCII1, PCII0, DMAC1_DMAE, DMAC1_DMINT11,
	    DMAC1_DMINT10, DMAC1_DMINT9, DMAC1_DMINT8, DMAC1_DMINT7,
	    DMAC1_DMINT6, DMAC0_DMAE, DMAC0_DMINT5, DMAC0_DMINT4,
	    DMAC0_DMINT3, DMAC0_DMINT2, DMAC0_DMINT1, DMAC0_DMINT0 पूर्ण,
	    INTC_SMP_BALANCING(INT2DISTCR1) पूर्ण,
	अणु 0xfe410840, 0xfe410870, 32, /* CnINT2MSK2 / CnINT2MSKCLR2 */
	  अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	    SCIF3_TXI, SCIF3_BRI, SCIF3_RXI, SCIF3_ERI,
	    SCIF2_TXI, SCIF2_BRI, SCIF2_RXI, SCIF2_ERI,
	    SCIF1_TXI, SCIF1_BRI, SCIF1_RXI, SCIF1_ERI,
	    SCIF0_TXI, SCIF0_BRI, SCIF0_RXI, SCIF0_ERI पूर्ण,
	    INTC_SMP_BALANCING(INT2DISTCR2) पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xfe410010, 0, 32, 4, /* INTPRI */ अणु IRQ0, IRQ1, IRQ2, IRQ3 पूर्ण पूर्ण,

	अणु 0xfe410800, 0, 32, 4, /* INT2PRI0 */ अणु 0, HUDII, TMU5, TMU4,
						 TMU3, TMU2, TMU1, TMU0 पूर्ण पूर्ण,
	अणु 0xfe410804, 0, 32, 4, /* INT2PRI1 */ अणु DTU3, DTU2, DTU1, DTU0,
						 SCIF3, SCIF2,
						 SCIF1, SCIF0 पूर्ण पूर्ण,
	अणु 0xfe410808, 0, 32, 4, /* INT2PRI2 */ अणु DMAC1, DMAC0,
						 PCII56789, PCII4,
						 PCII3, PCII2,
						 PCII1, PCII0 पूर्ण पूर्ण,
	अणु 0xfe41080c, 0, 32, 4, /* INT2PRI3 */ अणु FE1, FE0, ATAPI, VCORE0,
						 VIN1, VIN0, IIC, DUपूर्ण पूर्ण,
	अणु 0xfe410810, 0, 32, 4, /* INT2PRI4 */ अणु 0, 0, PAM, GPIO3,
						 GPIO2, GPIO1, GPIO0, IRM पूर्ण पूर्ण,
	अणु 0xfe410090, 0xfe4100a0, 32, 4, /* CnICIPRI / CnICIPRICLR */
	  अणु INTICI7, INTICI6, INTICI5, INTICI4,
	    INTICI3, INTICI2, INTICI1, INTICI0 पूर्ण, INTC_SMP(4, 4) पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "shx3", vectors, groups,
			 mask_रेजिस्टरs, prio_रेजिस्टरs, शून्य);

/* Support क्रम बाह्यal पूर्णांकerrupt pins in IRQ mode */
अटल काष्ठा पूर्णांकc_vect vectors_irq[] __initdata = अणु
	INTC_VECT(IRQ0, 0x240), INTC_VECT(IRQ1, 0x280),
	INTC_VECT(IRQ2, 0x2c0), INTC_VECT(IRQ3, 0x300),
पूर्ण;

अटल काष्ठा पूर्णांकc_sense_reg sense_रेजिस्टरs[] __initdata = अणु
	अणु 0xfe41001c, 32, 2, /* ICR1 */   अणु IRQ0, IRQ1, IRQ2, IRQ3 पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_irq, "shx3-irq", vectors_irq, groups,
			 mask_रेजिस्टरs, prio_रेजिस्टरs, sense_रेजिस्टरs);

/* External पूर्णांकerrupt pins in IRL mode */
अटल काष्ठा पूर्णांकc_vect vectors_irl[] __initdata = अणु
	INTC_VECT(IRL_LLLL, 0x200), INTC_VECT(IRL_LLLH, 0x220),
	INTC_VECT(IRL_LLHL, 0x240), INTC_VECT(IRL_LLHH, 0x260),
	INTC_VECT(IRL_LHLL, 0x280), INTC_VECT(IRL_LHLH, 0x2a0),
	INTC_VECT(IRL_LHHL, 0x2c0), INTC_VECT(IRL_LHHH, 0x2e0),
	INTC_VECT(IRL_HLLL, 0x300), INTC_VECT(IRL_HLLH, 0x320),
	INTC_VECT(IRL_HLHL, 0x340), INTC_VECT(IRL_HLHH, 0x360),
	INTC_VECT(IRL_HHLL, 0x380), INTC_VECT(IRL_HHLH, 0x3a0),
	INTC_VECT(IRL_HHHL, 0x3c0),
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_irl, "shx3-irl", vectors_irl, groups,
			 mask_रेजिस्टरs, prio_रेजिस्टरs, शून्य);

व्योम __init plat_irq_setup_pins(पूर्णांक mode)
अणु
	पूर्णांक ret = 0;

	चयन (mode) अणु
	हाल IRQ_MODE_IRQ:
		ret |= gpio_request(GPIO_FN_IRQ3, पूर्णांकc_desc_irq.name);
		ret |= gpio_request(GPIO_FN_IRQ2, पूर्णांकc_desc_irq.name);
		ret |= gpio_request(GPIO_FN_IRQ1, पूर्णांकc_desc_irq.name);
		ret |= gpio_request(GPIO_FN_IRQ0, पूर्णांकc_desc_irq.name);

		अगर (unlikely(ret)) अणु
			pr_err("Failed to set IRQ mode\n");
			वापस;
		पूर्ण

		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_irq);
		अवरोध;
	हाल IRQ_MODE_IRL3210:
		ret |= gpio_request(GPIO_FN_IRL3, पूर्णांकc_desc_irl.name);
		ret |= gpio_request(GPIO_FN_IRL2, पूर्णांकc_desc_irl.name);
		ret |= gpio_request(GPIO_FN_IRL1, पूर्णांकc_desc_irl.name);
		ret |= gpio_request(GPIO_FN_IRL0, पूर्णांकc_desc_irl.name);

		अगर (unlikely(ret)) अणु
			pr_err("Failed to set IRL mode\n");
			वापस;
		पूर्ण

		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_irl);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	अचिन्हित पूर्णांक nid = 1;

	/* Register CPU#0 URAM space as Node 1 */
	setup_booपंचांगem_node(nid++, 0x145f0000, 0x14610000);	/* CPU0 */

#अगर 0
	/* XXX: Not yet.. */
	setup_booपंचांगem_node(nid++, 0x14df0000, 0x14e10000);	/* CPU1 */
	setup_booपंचांगem_node(nid++, 0x155f0000, 0x15610000);	/* CPU2 */
	setup_booपंचांगem_node(nid++, 0x15df0000, 0x15e10000);	/* CPU3 */
#पूर्ण_अगर

	setup_booपंचांगem_node(nid++, 0x16000000, 0x16020000);	/* CSM */
पूर्ण
