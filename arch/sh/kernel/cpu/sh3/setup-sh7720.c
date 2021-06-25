<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Setup code क्रम SH7720, SH7721.
 *
 *  Copyright (C) 2007  Markus Brunner, Mark Jonas
 *  Copyright (C) 2009  Paul Mundt
 *
 *  Based on arch/sh/kernel/cpu/sh4/setup-sh7750.c:
 *
 *  Copyright (C) 2006  Paul Mundt
 *  Copyright (C) 2006  Jamie Lenehan
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/पन.स>
#समावेश <linux/serial_sci.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/usb/ohci_pdriver.h>
#समावेश <यंत्र/rtc.h>
#समावेश <यंत्र/platक्रमm_early.h>
#समावेश <cpu/serial.h>

अटल काष्ठा resource rtc_resources[] = अणु
	[0] = अणु
		.start	= 0xa413fec0,
		.end	= 0xa413fec0 + 0x28 - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		/* Shared Period/Carry/Alarm IRQ */
		.start	= evt2irq(0x480),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_rtc_platक्रमm_info rtc_info = अणु
	.capabilities	= RTC_CAP_4_DIGIT_YEAR,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_device = अणु
	.name		= "sh-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(rtc_resources),
	.resource	= rtc_resources,
	.dev		= अणु
		.platक्रमm_data = &rtc_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.type		= PORT_SCIF,
	.ops		= &sh7720_sci_port_ops,
	.regtype	= SCIx_SH7705_SCIF_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xa4430000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xc00)),
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
	.ops		= &sh7720_sci_port_ops,
	.regtype	= SCIx_SH7705_SCIF_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर1_resources[] = अणु
	DEFINE_RES_MEM(0xa4438000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xc20)),
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

अटल काष्ठा resource usb_ohci_resources[] = अणु
	[0] = अणु
		.start	= 0xA4428000,
		.end	= 0xA44280FF,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xa60),
		.end	= evt2irq(0xa60),
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
		.name	= "sh_udc",
		.start	= 0xA4420000,
		.end	= 0xA44200FF,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.name	= "sh_udc",
		.start	= evt2irq(0xa20),
		.end	= evt2irq(0xa20),
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

अटल काष्ठा sh_समयr_config cmt_platक्रमm_data = अणु
	.channels_mask = 0x1f,
पूर्ण;

अटल काष्ठा resource cmt_resources[] = अणु
	DEFINE_RES_MEM(0x044a0000, 0x60),
	DEFINE_RES_IRQ(evt2irq(0xf00)),
पूर्ण;

अटल काष्ठा platक्रमm_device cmt_device = अणु
	.name		= "sh-cmt-32",
	.id		= 0,
	.dev = अणु
		.platक्रमm_data	= &cmt_platक्रमm_data,
	पूर्ण,
	.resource	= cmt_resources,
	.num_resources	= ARRAY_SIZE(cmt_resources),
पूर्ण;

अटल काष्ठा sh_समयr_config पंचांगu0_platक्रमm_data = अणु
	.channels_mask = 7,
पूर्ण;

अटल काष्ठा resource पंचांगu0_resources[] = अणु
	DEFINE_RES_MEM(0xa412fe90, 0x28),
	DEFINE_RES_IRQ(evt2irq(0x400)),
	DEFINE_RES_IRQ(evt2irq(0x420)),
	DEFINE_RES_IRQ(evt2irq(0x440)),
पूर्ण;

अटल काष्ठा platक्रमm_device पंचांगu0_device = अणु
	.name		= "sh-tmu-sh3",
	.id		= 0,
	.dev = अणु
		.platक्रमm_data	= &पंचांगu0_platक्रमm_data,
	पूर्ण,
	.resource	= पंचांगu0_resources,
	.num_resources	= ARRAY_SIZE(पंचांगu0_resources),
पूर्ण;

अटल काष्ठा platक्रमm_device *sh7720_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&cmt_device,
	&पंचांगu0_device,
	&rtc_device,
	&usb_ohci_device,
	&usbf_device,
पूर्ण;

अटल पूर्णांक __init sh7720_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sh7720_devices,
				    ARRAY_SIZE(sh7720_devices));
पूर्ण
arch_initcall(sh7720_devices_setup);

अटल काष्ठा platक्रमm_device *sh7720_early_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&cmt_device,
	&पंचांगu0_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(sh7720_early_devices,
				   ARRAY_SIZE(sh7720_early_devices));
पूर्ण

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */
	TMU0, TMU1, TMU2, RTC,
	WDT, REF_RCMI, SIM,
	IRQ0, IRQ1, IRQ2, IRQ3,
	USBF_SPD, TMU_SUNI, IRQ5, IRQ4,
	DMAC1, LCDC, SSL,
	ADC, DMAC2, USBFI, CMT,
	SCIF0, SCIF1,
	PINT07, PINT815, TPU, IIC,
	SIOF0, SIOF1, MMC, PCC,
	USBHI, AFEIF,
	H_UDI,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	/* IRQ0->5 are handled in setup-sh3.c */
	INTC_VECT(TMU0, 0x400),       INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440),       INTC_VECT(RTC, 0x480),
	INTC_VECT(RTC, 0x4a0),	      INTC_VECT(RTC, 0x4c0),
	INTC_VECT(SIM, 0x4e0),	      INTC_VECT(SIM, 0x500),
	INTC_VECT(SIM, 0x520),	      INTC_VECT(SIM, 0x540),
	INTC_VECT(WDT, 0x560),        INTC_VECT(REF_RCMI, 0x580),
	/* H_UDI cannot be masked */  INTC_VECT(TMU_SUNI, 0x6c0),
	INTC_VECT(USBF_SPD, 0x6e0),   INTC_VECT(DMAC1, 0x800),
	INTC_VECT(DMAC1, 0x820),      INTC_VECT(DMAC1, 0x840),
	INTC_VECT(DMAC1, 0x860),      INTC_VECT(LCDC, 0x900),
#अगर defined(CONFIG_CPU_SUBTYPE_SH7720)
	INTC_VECT(SSL, 0x980),
#पूर्ण_अगर
	INTC_VECT(USBFI, 0xa20),      INTC_VECT(USBFI, 0xa40),
	INTC_VECT(USBHI, 0xa60),
	INTC_VECT(DMAC2, 0xb80),      INTC_VECT(DMAC2, 0xba0),
	INTC_VECT(ADC, 0xbe0),        INTC_VECT(SCIF0, 0xc00),
	INTC_VECT(SCIF1, 0xc20),      INTC_VECT(PINT07, 0xc80),
	INTC_VECT(PINT815, 0xca0),    INTC_VECT(SIOF0, 0xd00),
	INTC_VECT(SIOF1, 0xd20),      INTC_VECT(TPU, 0xd80),
	INTC_VECT(TPU, 0xda0),        INTC_VECT(TPU, 0xdc0),
	INTC_VECT(TPU, 0xde0),        INTC_VECT(IIC, 0xe00),
	INTC_VECT(MMC, 0xe80),        INTC_VECT(MMC, 0xea0),
	INTC_VECT(MMC, 0xec0),        INTC_VECT(MMC, 0xee0),
	INTC_VECT(CMT, 0xf00),        INTC_VECT(PCC, 0xf60),
	INTC_VECT(AFEIF, 0xfe0),
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xA414FEE2UL, 0, 16, 4, /* IPRA */ अणु TMU0, TMU1, TMU2, RTC पूर्ण पूर्ण,
	अणु 0xA414FEE4UL, 0, 16, 4, /* IPRB */ अणु WDT, REF_RCMI, SIM, 0 पूर्ण पूर्ण,
	अणु 0xA4140016UL, 0, 16, 4, /* IPRC */ अणु IRQ3, IRQ2, IRQ1, IRQ0 पूर्ण पूर्ण,
	अणु 0xA4140018UL, 0, 16, 4, /* IPRD */ अणु USBF_SPD, TMU_SUNI, IRQ5, IRQ4 पूर्ण पूर्ण,
	अणु 0xA414001AUL, 0, 16, 4, /* IPRE */ अणु DMAC1, 0, LCDC, SSL पूर्ण पूर्ण,
	अणु 0xA4080000UL, 0, 16, 4, /* IPRF */ अणु ADC, DMAC2, USBFI, CMT पूर्ण पूर्ण,
	अणु 0xA4080002UL, 0, 16, 4, /* IPRG */ अणु SCIF0, SCIF1, 0, 0 पूर्ण पूर्ण,
	अणु 0xA4080004UL, 0, 16, 4, /* IPRH */ अणु PINT07, PINT815, TPU, IIC पूर्ण पूर्ण,
	अणु 0xA4080006UL, 0, 16, 4, /* IPRI */ अणु SIOF0, SIOF1, MMC, PCC पूर्ण पूर्ण,
	अणु 0xA4080008UL, 0, 16, 4, /* IPRJ */ अणु 0, USBHI, 0, AFEIF पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh7720", vectors, शून्य,
		शून्य, prio_रेजिस्टरs, शून्य);

व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
	plat_irq_setup_sh3();
पूर्ण
