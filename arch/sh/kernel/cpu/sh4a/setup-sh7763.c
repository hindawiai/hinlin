<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7763 Setup
 *
 *  Copyright (C) 2006  Paul Mundt
 *  Copyright (C) 2007  Yoshihiro Shimoda
 *  Copyright (C) 2008, 2009  Nobuhiro Iwamatsu
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/पन.स>
#समावेश <linux/serial_sci.h>
#समावेश <linux/usb/ohci_pdriver.h>
#समावेश <यंत्र/platक्रमm_early.h>

अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
	.regtype	= SCIx_SH4_SCIF_FIFODATA_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xffe00000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x700)),
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
	.regtype	= SCIx_SH4_SCIF_FIFODATA_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर1_resources[] = अणु
	DEFINE_RES_MEM(0xffe08000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xb80)),
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
	DEFINE_RES_MEM(0xffe10000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xf00)),
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

अटल काष्ठा resource rtc_resources[] = अणु
	[0] = अणु
		.start	= 0xffe80000,
		.end	= 0xffe80000 + 0x58 - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		/* Shared Period/Carry/Alarm IRQ */
		.start  = evt2irq(0x480),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_device = अणु
	.name		= "sh-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(rtc_resources),
	.resource	= rtc_resources,
पूर्ण;

अटल काष्ठा resource usb_ohci_resources[] = अणु
	[0] = अणु
		.start	= 0xffec8000,
		.end	= 0xffec80ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xc60),
		.end	= evt2irq(0xc60),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 usb_ohci_dma_mask = 0xffffffffUL;

अटल काष्ठा usb_ohci_pdata usb_ohci_pdata;

अटल काष्ठा platक्रमm_device usb_ohci_device = अणु
	.name		= "ohci-platform",
	.id		= -1,
	.dev = अणु
		.dma_mask		= &usb_ohci_dma_mask,
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &usb_ohci_pdata,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(usb_ohci_resources),
	.resource	= usb_ohci_resources,
पूर्ण;

अटल काष्ठा resource usbf_resources[] = अणु
	[0] = अणु
		.start	= 0xffec0000,
		.end	= 0xffec00ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xc80),
		.end	= evt2irq(0xc80),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device usbf_device = अणु
	.name		= "sh_udc",
	.id		= -1,
	.dev = अणु
		.dma_mask		= शून्य,
		.coherent_dma_mask	= 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(usbf_resources),
	.resource	= usbf_resources,
पूर्ण;

अटल काष्ठा sh_समयr_config पंचांगu0_platक्रमm_data = अणु
	.channels_mask = 7,
पूर्ण;

अटल काष्ठा resource पंचांगu0_resources[] = अणु
	DEFINE_RES_MEM(0xffd80000, 0x30),
	DEFINE_RES_IRQ(evt2irq(0x580)),
	DEFINE_RES_IRQ(evt2irq(0x5a0)),
	DEFINE_RES_IRQ(evt2irq(0x5c0)),
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
	DEFINE_RES_MEM(0xffd88000, 0x2c),
	DEFINE_RES_IRQ(evt2irq(0xe00)),
	DEFINE_RES_IRQ(evt2irq(0xe20)),
	DEFINE_RES_IRQ(evt2irq(0xe40)),
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

अटल काष्ठा platक्रमm_device *sh7763_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&पंचांगu0_device,
	&पंचांगu1_device,
	&rtc_device,
	&usb_ohci_device,
	&usbf_device,
पूर्ण;

अटल पूर्णांक __init sh7763_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sh7763_devices,
				    ARRAY_SIZE(sh7763_devices));
पूर्ण
arch_initcall(sh7763_devices_setup);

अटल काष्ठा platक्रमm_device *sh7763_early_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&पंचांगu0_device,
	&पंचांगu1_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(sh7763_early_devices,
				   ARRAY_SIZE(sh7763_early_devices));
पूर्ण

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */

	IRL_LLLL, IRL_LLLH, IRL_LLHL, IRL_LLHH,
	IRL_LHLL, IRL_LHLH, IRL_LHHL, IRL_LHHH,
	IRL_HLLL, IRL_HLLH, IRL_HLHL, IRL_HLHH,
	IRL_HHLL, IRL_HHLH, IRL_HHHL,

	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7,
	RTC, WDT, TMU0, TMU1, TMU2, TMU2_TICPI,
	HUDI, LCDC, DMAC, SCIF0, IIC0, IIC1, CMT, GETHER, HAC,
	PCISERR, PCIINTA, PCIINTB, PCIINTC, PCIINTD, PCIC5,
	STIF0, STIF1, SCIF1, SIOF0, SIOF1, SIOF2,
	USBH, USBF, TPU, PCC, MMCIF, SIM,
	TMU3, TMU4, TMU5, ADC, SSI0, SSI1, SSI2, SSI3,
	SCIF2, GPIO,

	/* पूर्णांकerrupt groups */

	TMU012, TMU345,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_VECT(RTC, 0x480), INTC_VECT(RTC, 0x4a0),
	INTC_VECT(RTC, 0x4c0),
	INTC_VECT(WDT, 0x560), INTC_VECT(TMU0, 0x580),
	INTC_VECT(TMU1, 0x5a0), INTC_VECT(TMU2, 0x5c0),
	INTC_VECT(TMU2_TICPI, 0x5e0), INTC_VECT(HUDI, 0x600),
	INTC_VECT(LCDC, 0x620),
	INTC_VECT(DMAC, 0x640), INTC_VECT(DMAC, 0x660),
	INTC_VECT(DMAC, 0x680), INTC_VECT(DMAC, 0x6a0),
	INTC_VECT(DMAC, 0x6c0),
	INTC_VECT(SCIF0, 0x700), INTC_VECT(SCIF0, 0x720),
	INTC_VECT(SCIF0, 0x740), INTC_VECT(SCIF0, 0x760),
	INTC_VECT(DMAC, 0x780), INTC_VECT(DMAC, 0x7a0),
	INTC_VECT(IIC0, 0x8A0), INTC_VECT(IIC1, 0x8C0),
	INTC_VECT(CMT, 0x900), INTC_VECT(GETHER, 0x920),
	INTC_VECT(GETHER, 0x940), INTC_VECT(GETHER, 0x960),
	INTC_VECT(HAC, 0x980),
	INTC_VECT(PCISERR, 0xa00), INTC_VECT(PCIINTA, 0xa20),
	INTC_VECT(PCIINTB, 0xa40), INTC_VECT(PCIINTC, 0xa60),
	INTC_VECT(PCIINTD, 0xa80), INTC_VECT(PCIC5, 0xaa0),
	INTC_VECT(PCIC5, 0xac0), INTC_VECT(PCIC5, 0xae0),
	INTC_VECT(PCIC5, 0xb00), INTC_VECT(PCIC5, 0xb20),
	INTC_VECT(STIF0, 0xb40), INTC_VECT(STIF1, 0xb60),
	INTC_VECT(SCIF1, 0xb80), INTC_VECT(SCIF1, 0xba0),
	INTC_VECT(SCIF1, 0xbc0), INTC_VECT(SCIF1, 0xbe0),
	INTC_VECT(SIOF0, 0xc00), INTC_VECT(SIOF1, 0xc20),
	INTC_VECT(USBH, 0xc60), INTC_VECT(USBF, 0xc80),
	INTC_VECT(USBF, 0xca0),
	INTC_VECT(TPU, 0xcc0), INTC_VECT(PCC, 0xce0),
	INTC_VECT(MMCIF, 0xd00), INTC_VECT(MMCIF, 0xd20),
	INTC_VECT(MMCIF, 0xd40), INTC_VECT(MMCIF, 0xd60),
	INTC_VECT(SIM, 0xd80), INTC_VECT(SIM, 0xda0),
	INTC_VECT(SIM, 0xdc0), INTC_VECT(SIM, 0xde0),
	INTC_VECT(TMU3, 0xe00), INTC_VECT(TMU4, 0xe20),
	INTC_VECT(TMU5, 0xe40), INTC_VECT(ADC, 0xe60),
	INTC_VECT(SSI0, 0xe80), INTC_VECT(SSI1, 0xea0),
	INTC_VECT(SSI2, 0xec0), INTC_VECT(SSI3, 0xee0),
	INTC_VECT(SCIF2, 0xf00), INTC_VECT(SCIF2, 0xf20),
	INTC_VECT(SCIF2, 0xf40), INTC_VECT(SCIF2, 0xf60),
	INTC_VECT(GPIO, 0xf80), INTC_VECT(GPIO, 0xfa0),
	INTC_VECT(GPIO, 0xfc0), INTC_VECT(GPIO, 0xfe0),
पूर्ण;

अटल काष्ठा पूर्णांकc_group groups[] __initdata = अणु
	INTC_GROUP(TMU012, TMU0, TMU1, TMU2, TMU2_TICPI),
	INTC_GROUP(TMU345, TMU3, TMU4, TMU5),
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd40038, 0xffd4003c, 32, /* INT2MSKR / INT2MSKCR */
	  अणु 0, 0, 0, 0, 0, 0, GPIO, 0,
	    SSI0, MMCIF, 0, SIOF0, PCIC5, PCIINTD, PCIINTC, PCIINTB,
	    PCIINTA, PCISERR, HAC, CMT, 0, 0, 0, DMAC,
	    HUDI, 0, WDT, SCIF1, SCIF0, RTC, TMU345, TMU012 पूर्ण पूर्ण,
	अणु 0xffd400d0, 0xffd400d4, 32, /* INT2MSKR1 / INT2MSKCR1 */
	  अणु 0, 0, 0, 0, 0, 0, SCIF2, USBF,
	    0, 0, STIF1, STIF0, 0, 0, USBH, GETHER,
	    PCC, 0, 0, ADC, TPU, SIM, SIOF2, SIOF1,
	    LCDC, 0, IIC1, IIC0, SSI3, SSI2, SSI1, 0 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd40000, 0, 32, 8, /* INT2PRI0 */ अणु TMU0, TMU1,
						 TMU2, TMU2_TICPI पूर्ण पूर्ण,
	अणु 0xffd40004, 0, 32, 8, /* INT2PRI1 */ अणु TMU3, TMU4, TMU5, RTC पूर्ण पूर्ण,
	अणु 0xffd40008, 0, 32, 8, /* INT2PRI2 */ अणु SCIF0, SCIF1, WDT पूर्ण पूर्ण,
	अणु 0xffd4000c, 0, 32, 8, /* INT2PRI3 */ अणु HUDI, DMAC, ADC पूर्ण पूर्ण,
	अणु 0xffd40010, 0, 32, 8, /* INT2PRI4 */ अणु CMT, HAC,
						 PCISERR, PCIINTA पूर्ण पूर्ण,
	अणु 0xffd40014, 0, 32, 8, /* INT2PRI5 */ अणु PCIINTB, PCIINTC,
						 PCIINTD, PCIC5 पूर्ण पूर्ण,
	अणु 0xffd40018, 0, 32, 8, /* INT2PRI6 */ अणु SIOF0, USBF, MMCIF, SSI0 पूर्ण पूर्ण,
	अणु 0xffd4001c, 0, 32, 8, /* INT2PRI7 */ अणु SCIF2, GPIO पूर्ण पूर्ण,
	अणु 0xffd400a0, 0, 32, 8, /* INT2PRI8 */ अणु SSI3, SSI2, SSI1, 0 पूर्ण पूर्ण,
	अणु 0xffd400a4, 0, 32, 8, /* INT2PRI9 */ अणु LCDC, 0, IIC1, IIC0 पूर्ण पूर्ण,
	अणु 0xffd400a8, 0, 32, 8, /* INT2PRI10 */ अणु TPU, SIM, SIOF2, SIOF1 पूर्ण पूर्ण,
	अणु 0xffd400ac, 0, 32, 8, /* INT2PRI11 */ अणु PCC पूर्ण पूर्ण,
	अणु 0xffd400b0, 0, 32, 8, /* INT2PRI12 */ अणु 0, 0, USBH, GETHER पूर्ण पूर्ण,
	अणु 0xffd400b4, 0, 32, 8, /* INT2PRI13 */ अणु 0, 0, STIF1, STIF0 पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh7763", vectors, groups,
			 mask_रेजिस्टरs, prio_रेजिस्टरs, शून्य);

/* Support क्रम बाह्यal पूर्णांकerrupt pins in IRQ mode */
अटल काष्ठा पूर्णांकc_vect irq_vectors[] __initdata = अणु
	INTC_VECT(IRQ0, 0x240), INTC_VECT(IRQ1, 0x280),
	INTC_VECT(IRQ2, 0x2c0), INTC_VECT(IRQ3, 0x300),
	INTC_VECT(IRQ4, 0x340), INTC_VECT(IRQ5, 0x380),
	INTC_VECT(IRQ6, 0x3c0), INTC_VECT(IRQ7, 0x200),
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg irq_mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd00044, 0xffd00064, 32, /* INTMSK0 / INTMSKCLR0 */
	  अणु IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg irq_prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd00010, 0, 32, 4, /* INTPRI */ अणु IRQ0, IRQ1, IRQ2, IRQ3,
					       IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_sense_reg irq_sense_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd0001c, 32, 2, /* ICR1 */   अणु IRQ0, IRQ1, IRQ2, IRQ3,
					    IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg irq_ack_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd00024, 0, 32, /* INTREQ */
	  अणु IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC_ACK(पूर्णांकc_irq_desc, "sh7763-irq", irq_vectors,
			     शून्य, irq_mask_रेजिस्टरs, irq_prio_रेजिस्टरs,
			     irq_sense_रेजिस्टरs, irq_ack_रेजिस्टरs);


/* External पूर्णांकerrupt pins in IRL mode */
अटल काष्ठा पूर्णांकc_vect irl_vectors[] __initdata = अणु
	INTC_VECT(IRL_LLLL, 0x200), INTC_VECT(IRL_LLLH, 0x220),
	INTC_VECT(IRL_LLHL, 0x240), INTC_VECT(IRL_LLHH, 0x260),
	INTC_VECT(IRL_LHLL, 0x280), INTC_VECT(IRL_LHLH, 0x2a0),
	INTC_VECT(IRL_LHHL, 0x2c0), INTC_VECT(IRL_LHHH, 0x2e0),
	INTC_VECT(IRL_HLLL, 0x300), INTC_VECT(IRL_HLLH, 0x320),
	INTC_VECT(IRL_HLHL, 0x340), INTC_VECT(IRL_HLHH, 0x360),
	INTC_VECT(IRL_HHLL, 0x380), INTC_VECT(IRL_HHLH, 0x3a0),
	INTC_VECT(IRL_HHHL, 0x3c0),
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg irl3210_mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd40080, 0xffd40084, 32, /* INTMSK2 / INTMSKCLR2 */
	  अणु IRL_LLLL, IRL_LLLH, IRL_LLHL, IRL_LLHH,
	    IRL_LHLL, IRL_LHLH, IRL_LHHL, IRL_LHHH,
	    IRL_HLLL, IRL_HLLH, IRL_HLHL, IRL_HLHH,
	    IRL_HHLL, IRL_HHLH, IRL_HHHL, पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg irl7654_mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd40080, 0xffd40084, 32, /* INTMSK2 / INTMSKCLR2 */
	  अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	    IRL_LLLL, IRL_LLLH, IRL_LLHL, IRL_LLHH,
	    IRL_LHLL, IRL_LHLH, IRL_LHHL, IRL_LHHH,
	    IRL_HLLL, IRL_HLLH, IRL_HLHL, IRL_HLHH,
	    IRL_HHLL, IRL_HHLH, IRL_HHHL, पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_irl7654_desc, "sh7763-irl7654", irl_vectors,
			शून्य, irl7654_mask_रेजिस्टरs, शून्य, शून्य);

अटल DECLARE_INTC_DESC(पूर्णांकc_irl3210_desc, "sh7763-irl3210", irl_vectors,
			शून्य, irl3210_mask_रेजिस्टरs, शून्य, शून्य);

#घोषणा INTC_ICR0	0xffd00000
#घोषणा INTC_INTMSK0	0xffd00044
#घोषणा INTC_INTMSK1	0xffd00048
#घोषणा INTC_INTMSK2	0xffd40080
#घोषणा INTC_INTMSKCLR1	0xffd00068
#घोषणा INTC_INTMSKCLR2	0xffd40084

व्योम __init plat_irq_setup(व्योम)
अणु
	/* disable IRQ7-0 */
	__raw_ग_लिखोl(0xff000000, INTC_INTMSK0);

	/* disable IRL3-0 + IRL7-4 */
	__raw_ग_लिखोl(0xc0000000, INTC_INTMSK1);
	__raw_ग_लिखोl(0xfffefffe, INTC_INTMSK2);

	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
पूर्ण

व्योम __init plat_irq_setup_pins(पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल IRQ_MODE_IRQ:
		/* select IRQ mode क्रम IRL3-0 + IRL7-4 */
		__raw_ग_लिखोl(__raw_पढ़ोl(INTC_ICR0) | 0x00c00000, INTC_ICR0);
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_irq_desc);
		अवरोध;
	हाल IRQ_MODE_IRL7654:
		/* enable IRL7-4 but करोn't provide any masking */
		__raw_ग_लिखोl(0x40000000, INTC_INTMSKCLR1);
		__raw_ग_लिखोl(0x0000fffe, INTC_INTMSKCLR2);
		अवरोध;
	हाल IRQ_MODE_IRL3210:
		/* enable IRL0-3 but करोn't provide any masking */
		__raw_ग_लिखोl(0x80000000, INTC_INTMSKCLR1);
		__raw_ग_लिखोl(0xfffe0000, INTC_INTMSKCLR2);
		अवरोध;
	हाल IRQ_MODE_IRL7654_MASK:
		/* enable IRL7-4 and mask using cpu पूर्णांकc controller */
		__raw_ग_लिखोl(0x40000000, INTC_INTMSKCLR1);
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_irl7654_desc);
		अवरोध;
	हाल IRQ_MODE_IRL3210_MASK:
		/* enable IRL0-3 and mask using cpu पूर्णांकc controller */
		__raw_ग_लिखोl(0x80000000, INTC_INTMSKCLR1);
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_irl3210_desc);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण
