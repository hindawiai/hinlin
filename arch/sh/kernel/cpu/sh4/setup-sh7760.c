<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7760 Setup
 *
 *  Copyright (C) 2006  Paul Mundt
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/platक्रमm_early.h>

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */
	IRL0, IRL1, IRL2, IRL3,
	HUDI, GPIOI, DMAC,
	IRQ4, IRQ5, IRQ6, IRQ7,
	HCAN20, HCAN21,
	SSI0, SSI1,
	HAC0, HAC1,
	I2C0, I2C1,
	USB, LCDC,
	DMABRG0, DMABRG1, DMABRG2,
	SCIF0_ERI, SCIF0_RXI, SCIF0_BRI, SCIF0_TXI,
	SCIF1_ERI, SCIF1_RXI, SCIF1_BRI, SCIF1_TXI,
	SCIF2_ERI, SCIF2_RXI, SCIF2_BRI, SCIF2_TXI,
	SIM_ERI, SIM_RXI, SIM_TXI, SIM_TEI,
	HSPI,
	MMCIF0, MMCIF1, MMCIF2, MMCIF3,
	MFI, ADC, CMT,
	TMU0, TMU1, TMU2,
	WDT, REF,

	/* पूर्णांकerrupt groups */
	DMABRG, SCIF0, SCIF1, SCIF2, SIM, MMCIF,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_VECT(HUDI, 0x600), INTC_VECT(GPIOI, 0x620),
	INTC_VECT(DMAC, 0x640), INTC_VECT(DMAC, 0x660),
	INTC_VECT(DMAC, 0x680), INTC_VECT(DMAC, 0x6a0),
	INTC_VECT(DMAC, 0x780), INTC_VECT(DMAC, 0x7a0),
	INTC_VECT(DMAC, 0x7c0), INTC_VECT(DMAC, 0x7e0),
	INTC_VECT(DMAC, 0x6c0),
	INTC_VECT(IRQ4, 0x800), INTC_VECT(IRQ5, 0x820),
	INTC_VECT(IRQ6, 0x840), INTC_VECT(IRQ6, 0x860),
	INTC_VECT(HCAN20, 0x900), INTC_VECT(HCAN21, 0x920),
	INTC_VECT(SSI0, 0x940), INTC_VECT(SSI1, 0x960),
	INTC_VECT(HAC0, 0x980), INTC_VECT(HAC1, 0x9a0),
	INTC_VECT(I2C0, 0x9c0), INTC_VECT(I2C1, 0x9e0),
	INTC_VECT(USB, 0xa00), INTC_VECT(LCDC, 0xa20),
	INTC_VECT(DMABRG0, 0xa80), INTC_VECT(DMABRG1, 0xaa0),
	INTC_VECT(DMABRG2, 0xac0),
	INTC_VECT(SCIF0_ERI, 0x880), INTC_VECT(SCIF0_RXI, 0x8a0),
	INTC_VECT(SCIF0_BRI, 0x8c0), INTC_VECT(SCIF0_TXI, 0x8e0),
	INTC_VECT(SCIF1_ERI, 0xb00), INTC_VECT(SCIF1_RXI, 0xb20),
	INTC_VECT(SCIF1_BRI, 0xb40), INTC_VECT(SCIF1_TXI, 0xb60),
	INTC_VECT(SCIF2_ERI, 0xb80), INTC_VECT(SCIF2_RXI, 0xba0),
	INTC_VECT(SCIF2_BRI, 0xbc0), INTC_VECT(SCIF2_TXI, 0xbe0),
	INTC_VECT(SIM_ERI, 0xc00), INTC_VECT(SIM_RXI, 0xc20),
	INTC_VECT(SIM_TXI, 0xc40), INTC_VECT(SIM_TEI, 0xc60),
	INTC_VECT(HSPI, 0xc80),
	INTC_VECT(MMCIF0, 0xd00), INTC_VECT(MMCIF1, 0xd20),
	INTC_VECT(MMCIF2, 0xd40), INTC_VECT(MMCIF3, 0xd60),
	INTC_VECT(MFI, 0xe80), /* 0xf80 according to data sheet */
	INTC_VECT(ADC, 0xf80), INTC_VECT(CMT, 0xfa0),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(TMU2, 0x460),
	INTC_VECT(WDT, 0x560),
	INTC_VECT(REF, 0x580), INTC_VECT(REF, 0x5a0),
पूर्ण;

अटल काष्ठा पूर्णांकc_group groups[] __initdata = अणु
	INTC_GROUP(DMABRG, DMABRG0, DMABRG1, DMABRG2),
	INTC_GROUP(SCIF0, SCIF0_ERI, SCIF0_RXI, SCIF0_BRI, SCIF0_TXI),
	INTC_GROUP(SCIF1, SCIF1_ERI, SCIF1_RXI, SCIF1_BRI, SCIF1_TXI),
	INTC_GROUP(SCIF2, SCIF2_ERI, SCIF2_RXI, SCIF2_BRI, SCIF2_TXI),
	INTC_GROUP(SIM, SIM_ERI, SIM_RXI, SIM_TXI, SIM_TEI),
	INTC_GROUP(MMCIF, MMCIF0, MMCIF1, MMCIF2, MMCIF3),
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xfe080040, 0xfe080060, 32, /* INTMSK00 / INTMSKCLR00 */
	  अणु IRQ4, IRQ5, IRQ6, IRQ7, 0, 0, HCAN20, HCAN21,
	    SSI0, SSI1, HAC0, HAC1, I2C0, I2C1, USB, LCDC,
	    0, DMABRG0, DMABRG1, DMABRG2,
	    SCIF0_ERI, SCIF0_RXI, SCIF0_BRI, SCIF0_TXI,
	    SCIF1_ERI, SCIF1_RXI, SCIF1_BRI, SCIF1_TXI,
	    SCIF2_ERI, SCIF2_RXI, SCIF2_BRI, SCIF2_TXI, पूर्ण पूर्ण,
	अणु 0xfe080044, 0xfe080064, 32, /* INTMSK04 / INTMSKCLR04 */
	  अणु 0, 0, 0, 0, 0, 0, 0, 0,
	    SIM_ERI, SIM_RXI, SIM_TXI, SIM_TEI,
	    HSPI, MMCIF0, MMCIF1, MMCIF2,
	    MMCIF3, 0, 0, 0, 0, 0, 0, 0,
	    0, MFI, 0, 0, 0, 0, ADC, CMT, पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd00004, 0, 16, 4, /* IPRA */ अणु TMU0, TMU1, TMU2 पूर्ण पूर्ण,
	अणु 0xffd00008, 0, 16, 4, /* IPRB */ अणु WDT, REF, 0, 0 पूर्ण पूर्ण,
	अणु 0xffd0000c, 0, 16, 4, /* IPRC */ अणु GPIOI, DMAC, 0, HUDI पूर्ण पूर्ण,
	अणु 0xffd00010, 0, 16, 4, /* IPRD */ अणु IRL0, IRL1, IRL2, IRL3 पूर्ण पूर्ण,
	अणु 0xfe080000, 0, 32, 4, /* INTPRI00 */ अणु IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
	अणु 0xfe080004, 0, 32, 4, /* INTPRI04 */ अणु HCAN20, HCAN21, SSI0, SSI1,
						 HAC0, HAC1, I2C0, I2C1 पूर्ण पूर्ण,
	अणु 0xfe080008, 0, 32, 4, /* INTPRI08 */ अणु USB, LCDC, DMABRG, SCIF0,
						 SCIF1, SCIF2, SIM, HSPI पूर्ण पूर्ण,
	अणु 0xfe08000c, 0, 32, 4, /* INTPRI0C */ अणु 0, 0, MMCIF, 0,
						 MFI, 0, ADC, CMT पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh7760", vectors, groups,
			 mask_रेजिस्टरs, prio_रेजिस्टरs, शून्य);

अटल काष्ठा पूर्णांकc_vect vectors_irq[] __initdata = अणु
	INTC_VECT(IRL0, 0x240), INTC_VECT(IRL1, 0x2a0),
	INTC_VECT(IRL2, 0x300), INTC_VECT(IRL3, 0x360),
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_irq, "sh7760-irq", vectors_irq, groups,
			 mask_रेजिस्टरs, prio_रेजिस्टरs, शून्य);

अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
	.regtype	= SCIx_SH4_SCIF_FIFODATA_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xfe600000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x880)),
	DEFINE_RES_IRQ(evt2irq(0x8a0)),
	DEFINE_RES_IRQ(evt2irq(0x8e0)),
	DEFINE_RES_IRQ(evt2irq(0x8c0)),
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
	.type		= PORT_SCIF,
	.scscr		= SCSCR_REIE,
	.regtype	= SCIx_SH4_SCIF_FIFODATA_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर1_resources[] = अणु
	DEFINE_RES_MEM(0xfe610000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xb00)),
	DEFINE_RES_IRQ(evt2irq(0xb20)),
	DEFINE_RES_IRQ(evt2irq(0xb60)),
	DEFINE_RES_IRQ(evt2irq(0xb40)),
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
	.regtype	= SCIx_SH4_SCIF_FIFODATA_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर2_resources[] = अणु
	DEFINE_RES_MEM(0xfe620000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xb80)),
	DEFINE_RES_IRQ(evt2irq(0xba0)),
	DEFINE_RES_IRQ(evt2irq(0xbe0)),
	DEFINE_RES_IRQ(evt2irq(0xbc0)),
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

अटल काष्ठा plat_sci_port scअगर3_platक्रमm_data = अणु
	/*
	 * This is actually a SIM card module serial port, based on an SCI with
	 * additional रेजिस्टरs. The sh-sci driver करोesn't support the SIM port
	 * type, declare it as a SCI. Don't declare the additional रेजिस्टरs in
	 * the memory resource or the driver will compute an incorrect regshअगरt
	 * value.
	 */
	.type		= PORT_SCI,
पूर्ण;

अटल काष्ठा resource scअगर3_resources[] = अणु
	DEFINE_RES_MEM(0xfe480000, 0x10),
	DEFINE_RES_IRQ(evt2irq(0xc00)),
	DEFINE_RES_IRQ(evt2irq(0xc20)),
	DEFINE_RES_IRQ(evt2irq(0xc40)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर3_device = अणु
	.name		= "sh-sci",
	.id		= 3,
	.resource	= scअगर3_resources,
	.num_resources	= ARRAY_SIZE(scअगर3_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर3_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_समयr_config पंचांगu0_platक्रमm_data = अणु
	.channels_mask = 7,
पूर्ण;

अटल काष्ठा resource पंचांगu0_resources[] = अणु
	DEFINE_RES_MEM(0xffd80000, 0x30),
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


अटल काष्ठा platक्रमm_device *sh7760_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&scअगर3_device,
	&पंचांगu0_device,
पूर्ण;

अटल पूर्णांक __init sh7760_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sh7760_devices,
				    ARRAY_SIZE(sh7760_devices));
पूर्ण
arch_initcall(sh7760_devices_setup);

अटल काष्ठा platक्रमm_device *sh7760_early_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&scअगर3_device,
	&पंचांगu0_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(sh7760_early_devices,
				   ARRAY_SIZE(sh7760_early_devices));
पूर्ण

#घोषणा INTC_ICR	0xffd00000UL
#घोषणा INTC_ICR_IRLM	(1 << 7)

व्योम __init plat_irq_setup_pins(पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल IRQ_MODE_IRQ:
		__raw_ग_लिखोw(__raw_पढ़ोw(INTC_ICR) | INTC_ICR_IRLM, INTC_ICR);
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_irq);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
पूर्ण
