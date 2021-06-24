<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7091/SH7750/SH7750S/SH7750R/SH7751/SH7751R Setup
 *
 *  Copyright (C) 2006  Paul Mundt
 *  Copyright (C) 2006  Jamie Lenehan
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/पन.स>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/serial_sci.h>
#समावेश <generated/machtypes.h>
#समावेश <यंत्र/platक्रमm_early.h>

अटल काष्ठा resource rtc_resources[] = अणु
	[0] = अणु
		.start	= 0xffc80000,
		.end	= 0xffc80000 + 0x58 - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		/* Shared Period/Carry/Alarm IRQ */
		.start	= evt2irq(0x480),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_device = अणु
	.name		= "sh-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(rtc_resources),
	.resource	= rtc_resources,
पूर्ण;

अटल काष्ठा plat_sci_port sci_platक्रमm_data = अणु
	.type		= PORT_SCI,
पूर्ण;

अटल काष्ठा resource sci_resources[] = अणु
	DEFINE_RES_MEM(0xffe00000, 0x20),
	DEFINE_RES_IRQ(evt2irq(0x4e0)),
पूर्ण;

अटल काष्ठा platक्रमm_device sci_device = अणु
	.name		= "sh-sci",
	.id		= 0,
	.resource	= sci_resources,
	.num_resources	= ARRAY_SIZE(sci_resources),
	.dev		= अणु
		.platक्रमm_data	= &sci_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर_resources[] = अणु
	DEFINE_RES_MEM(0xffe80000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x700)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर_device = अणु
	.name		= "sh-sci",
	.id		= 1,
	.resource	= scअगर_resources,
	.num_resources	= ARRAY_SIZE(scअगर_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर_platक्रमm_data,
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

/* SH7750R, SH7751 and SH7751R all have two extra समयr channels */
#अगर defined(CONFIG_CPU_SUBTYPE_SH7750R) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751R)

अटल काष्ठा sh_समयr_config पंचांगu1_platक्रमm_data = अणु
	.channels_mask = 3,
पूर्ण;

अटल काष्ठा resource पंचांगu1_resources[] = अणु
	DEFINE_RES_MEM(0xfe100000, 0x20),
	DEFINE_RES_IRQ(evt2irq(0xb00)),
	DEFINE_RES_IRQ(evt2irq(0xb80)),
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

#पूर्ण_अगर

अटल काष्ठा platक्रमm_device *sh7750_devices[] __initdata = अणु
	&rtc_device,
	&पंचांगu0_device,
#अगर defined(CONFIG_CPU_SUBTYPE_SH7750R) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751R)
	&पंचांगu1_device,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init sh7750_devices_setup(व्योम)
अणु
	अगर (mach_is_rts7751r2d()) अणु
		platक्रमm_device_रेजिस्टर(&scअगर_device);
	पूर्ण अन्यथा अणु
		platक्रमm_device_रेजिस्टर(&sci_device);
		platक्रमm_device_रेजिस्टर(&scअगर_device);
	पूर्ण

	वापस platक्रमm_add_devices(sh7750_devices,
				    ARRAY_SIZE(sh7750_devices));
पूर्ण
arch_initcall(sh7750_devices_setup);

अटल काष्ठा platक्रमm_device *sh7750_early_devices[] __initdata = अणु
	&पंचांगu0_device,
#अगर defined(CONFIG_CPU_SUBTYPE_SH7750R) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751R)
	&पंचांगu1_device,
#पूर्ण_अगर
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	काष्ठा platक्रमm_device *dev[1];

	अगर (mach_is_rts7751r2d()) अणु
		scअगर_platक्रमm_data.scscr |= SCSCR_CKE1;
		dev[0] = &scअगर_device;
		sh_early_platक्रमm_add_devices(dev, 1);
	पूर्ण अन्यथा अणु
		dev[0] = &sci_device;
		sh_early_platक्रमm_add_devices(dev, 1);
		dev[0] = &scअगर_device;
		sh_early_platक्रमm_add_devices(dev, 1);
	पूर्ण

	sh_early_platक्रमm_add_devices(sh7750_early_devices,
				   ARRAY_SIZE(sh7750_early_devices));
पूर्ण

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */
	IRL0, IRL1, IRL2, IRL3, /* only IRLM mode supported */
	HUDI, GPIOI, DMAC,
	PCIC0_PCISERR, PCIC1_PCIERR, PCIC1_PCIPWDWN, PCIC1_PCIPWON,
	PCIC1_PCIDMA0, PCIC1_PCIDMA1, PCIC1_PCIDMA2, PCIC1_PCIDMA3,
	TMU3, TMU4, TMU0, TMU1, TMU2, RTC, SCI1, SCIF, WDT, REF,

	/* पूर्णांकerrupt groups */
	PCIC1,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_VECT(HUDI, 0x600), INTC_VECT(GPIOI, 0x620),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(TMU2, 0x460),
	INTC_VECT(RTC, 0x480), INTC_VECT(RTC, 0x4a0),
	INTC_VECT(RTC, 0x4c0),
	INTC_VECT(SCI1, 0x4e0), INTC_VECT(SCI1, 0x500),
	INTC_VECT(SCI1, 0x520), INTC_VECT(SCI1, 0x540),
	INTC_VECT(SCIF, 0x700), INTC_VECT(SCIF, 0x720),
	INTC_VECT(SCIF, 0x740), INTC_VECT(SCIF, 0x760),
	INTC_VECT(WDT, 0x560),
	INTC_VECT(REF, 0x580), INTC_VECT(REF, 0x5a0),
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd00004, 0, 16, 4, /* IPRA */ अणु TMU0, TMU1, TMU2, RTC पूर्ण पूर्ण,
	अणु 0xffd00008, 0, 16, 4, /* IPRB */ अणु WDT, REF, SCI1, 0 पूर्ण पूर्ण,
	अणु 0xffd0000c, 0, 16, 4, /* IPRC */ अणु GPIOI, DMAC, SCIF, HUDI पूर्ण पूर्ण,
	अणु 0xffd00010, 0, 16, 4, /* IPRD */ अणु IRL0, IRL1, IRL2, IRL3 पूर्ण पूर्ण,
	अणु 0xfe080000, 0, 32, 4, /* INTPRI00 */ अणु 0, 0, 0, 0,
						 TMU4, TMU3,
						 PCIC1, PCIC0_PCISERR पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh7750", vectors, शून्य,
			 शून्य, prio_रेजिस्टरs, शून्य);

/* SH7750, SH7750S, SH7751 and SH7091 all have 4-channel DMA controllers */
#अगर defined(CONFIG_CPU_SUBTYPE_SH7750) || \
	defined(CONFIG_CPU_SUBTYPE_SH7750S) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751) || \
	defined(CONFIG_CPU_SUBTYPE_SH7091)
अटल काष्ठा पूर्णांकc_vect vectors_dma4[] __initdata = अणु
	INTC_VECT(DMAC, 0x640), INTC_VECT(DMAC, 0x660),
	INTC_VECT(DMAC, 0x680), INTC_VECT(DMAC, 0x6a0),
	INTC_VECT(DMAC, 0x6c0),
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_dma4, "sh7750_dma4",
			 vectors_dma4, शून्य,
			 शून्य, prio_रेजिस्टरs, शून्य);
#पूर्ण_अगर

/* SH7750R and SH7751R both have 8-channel DMA controllers */
#अगर defined(CONFIG_CPU_SUBTYPE_SH7750R) || defined(CONFIG_CPU_SUBTYPE_SH7751R)
अटल काष्ठा पूर्णांकc_vect vectors_dma8[] __initdata = अणु
	INTC_VECT(DMAC, 0x640), INTC_VECT(DMAC, 0x660),
	INTC_VECT(DMAC, 0x680), INTC_VECT(DMAC, 0x6a0),
	INTC_VECT(DMAC, 0x780), INTC_VECT(DMAC, 0x7a0),
	INTC_VECT(DMAC, 0x7c0), INTC_VECT(DMAC, 0x7e0),
	INTC_VECT(DMAC, 0x6c0),
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_dma8, "sh7750_dma8",
			 vectors_dma8, शून्य,
			 शून्य, prio_रेजिस्टरs, शून्य);
#पूर्ण_अगर

/* SH7750R, SH7751 and SH7751R all have two extra समयr channels */
#अगर defined(CONFIG_CPU_SUBTYPE_SH7750R) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751R)
अटल काष्ठा पूर्णांकc_vect vectors_पंचांगu34[] __initdata = अणु
	INTC_VECT(TMU3, 0xb00), INTC_VECT(TMU4, 0xb80),
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xfe080040, 0xfe080060, 32, /* INTMSK00 / INTMSKCLR00 */
	  अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, TMU4, TMU3,
	    PCIC1_PCIERR, PCIC1_PCIPWDWN, PCIC1_PCIPWON,
	    PCIC1_PCIDMA0, PCIC1_PCIDMA1, PCIC1_PCIDMA2,
	    PCIC1_PCIDMA3, PCIC0_PCISERR पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_पंचांगu34, "sh7750_tmu34",
			 vectors_पंचांगu34, शून्य,
			 mask_रेजिस्टरs, prio_रेजिस्टरs, शून्य);
#पूर्ण_अगर

/* SH7750S, SH7750R, SH7751 and SH7751R all have IRLM priority रेजिस्टरs */
अटल काष्ठा पूर्णांकc_vect vectors_irlm[] __initdata = अणु
	INTC_VECT(IRL0, 0x240), INTC_VECT(IRL1, 0x2a0),
	INTC_VECT(IRL2, 0x300), INTC_VECT(IRL3, 0x360),
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_irlm, "sh7750_irlm", vectors_irlm, शून्य,
			 शून्य, prio_रेजिस्टरs, शून्य);

/* SH7751 and SH7751R both have PCI */
#अगर defined(CONFIG_CPU_SUBTYPE_SH7751) || defined(CONFIG_CPU_SUBTYPE_SH7751R)
अटल काष्ठा पूर्णांकc_vect vectors_pci[] __initdata = अणु
	INTC_VECT(PCIC0_PCISERR, 0xa00), INTC_VECT(PCIC1_PCIERR, 0xae0),
	INTC_VECT(PCIC1_PCIPWDWN, 0xac0), INTC_VECT(PCIC1_PCIPWON, 0xaa0),
	INTC_VECT(PCIC1_PCIDMA0, 0xa80), INTC_VECT(PCIC1_PCIDMA1, 0xa60),
	INTC_VECT(PCIC1_PCIDMA2, 0xa40), INTC_VECT(PCIC1_PCIDMA3, 0xa20),
पूर्ण;

अटल काष्ठा पूर्णांकc_group groups_pci[] __initdata = अणु
	INTC_GROUP(PCIC1, PCIC1_PCIERR, PCIC1_PCIPWDWN, PCIC1_PCIPWON,
		   PCIC1_PCIDMA0, PCIC1_PCIDMA1, PCIC1_PCIDMA2, PCIC1_PCIDMA3),
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_pci, "sh7750_pci", vectors_pci, groups_pci,
			 mask_रेजिस्टरs, prio_रेजिस्टरs, शून्य);
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_SUBTYPE_SH7750) || \
	defined(CONFIG_CPU_SUBTYPE_SH7750S) || \
	defined(CONFIG_CPU_SUBTYPE_SH7091)
व्योम __init plat_irq_setup(व्योम)
अणु
	/*
	 * same vectors क्रम SH7750, SH7750S and SH7091 except क्रम IRLM,
	 * see below..
	 */
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_dma4);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_SUBTYPE_SH7750R)
व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_dma8);
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_पंचांगu34);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_SUBTYPE_SH7751)
व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_dma4);
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_पंचांगu34);
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_pci);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_SUBTYPE_SH7751R)
व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_dma8);
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_पंचांगu34);
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_pci);
पूर्ण
#पूर्ण_अगर

#घोषणा INTC_ICR	0xffd00000UL
#घोषणा INTC_ICR_IRLM   (1<<7)

व्योम __init plat_irq_setup_pins(पूर्णांक mode)
अणु
#अगर defined(CONFIG_CPU_SUBTYPE_SH7750) || defined(CONFIG_CPU_SUBTYPE_SH7091)
	BUG(); /* impossible to mask पूर्णांकerrupts on SH7750 and SH7091 */
	वापस;
#पूर्ण_अगर

	चयन (mode) अणु
	हाल IRQ_MODE_IRQ: /* inभागidual पूर्णांकerrupt mode क्रम IRL3-0 */
		__raw_ग_लिखोw(__raw_पढ़ोw(INTC_ICR) | INTC_ICR_IRLM, INTC_ICR);
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_irlm);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण
