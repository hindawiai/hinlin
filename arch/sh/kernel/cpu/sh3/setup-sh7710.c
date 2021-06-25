<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH3 Setup code क्रम SH7710, SH7712
 *
 *  Copyright (C) 2006 - 2009  Paul Mundt
 *  Copyright (C) 2007  Nobuhiro Iwamatsu
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <यंत्र/rtc.h>
#समावेश <यंत्र/platक्रमm_early.h>

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */
	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5,
	DMAC1, SCIF0, SCIF1, DMAC2, IPSEC,
	EDMAC0, EDMAC1, EDMAC2,
	SIOF0, SIOF1,

	TMU0, TMU1, TMU2,
	RTC, WDT, REF,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	/* IRQ0->5 are handled in setup-sh3.c */
	INTC_VECT(DMAC1, 0x800), INTC_VECT(DMAC1, 0x820),
	INTC_VECT(DMAC1, 0x840), INTC_VECT(DMAC1, 0x860),
	INTC_VECT(SCIF0, 0x880), INTC_VECT(SCIF0, 0x8a0),
	INTC_VECT(SCIF0, 0x8c0), INTC_VECT(SCIF0, 0x8e0),
	INTC_VECT(SCIF1, 0x900), INTC_VECT(SCIF1, 0x920),
	INTC_VECT(SCIF1, 0x940), INTC_VECT(SCIF1, 0x960),
	INTC_VECT(DMAC2, 0xb80), INTC_VECT(DMAC2, 0xba0),
#अगर_घोषित CONFIG_CPU_SUBTYPE_SH7710
	INTC_VECT(IPSEC, 0xbe0),
#पूर्ण_अगर
	INTC_VECT(EDMAC0, 0xc00), INTC_VECT(EDMAC1, 0xc20),
	INTC_VECT(EDMAC2, 0xc40),
	INTC_VECT(SIOF0, 0xe00), INTC_VECT(SIOF0, 0xe20),
	INTC_VECT(SIOF0, 0xe40), INTC_VECT(SIOF0, 0xe60),
	INTC_VECT(SIOF1, 0xe80), INTC_VECT(SIOF1, 0xea0),
	INTC_VECT(SIOF1, 0xec0), INTC_VECT(SIOF1, 0xee0),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440),
	INTC_VECT(RTC, 0x480), INTC_VECT(RTC, 0x4a0),
	INTC_VECT(RTC, 0x4c0),
	INTC_VECT(WDT, 0x560),
	INTC_VECT(REF, 0x580),
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xfffffee2, 0, 16, 4, /* IPRA */ अणु TMU0, TMU1, TMU2, RTC पूर्ण पूर्ण,
	अणु 0xfffffee4, 0, 16, 4, /* IPRB */ अणु WDT, REF, 0, 0 पूर्ण पूर्ण,
	अणु 0xa4000016, 0, 16, 4, /* IPRC */ अणु IRQ3, IRQ2, IRQ1, IRQ0 पूर्ण पूर्ण,
	अणु 0xa4000018, 0, 16, 4, /* IPRD */ अणु 0, 0, IRQ5, IRQ4 पूर्ण पूर्ण,
	अणु 0xa400001a, 0, 16, 4, /* IPRE */ अणु DMAC1, SCIF0, SCIF1 पूर्ण पूर्ण,
	अणु 0xa4080000, 0, 16, 4, /* IPRF */ अणु IPSEC, DMAC2 पूर्ण पूर्ण,
	अणु 0xa4080002, 0, 16, 4, /* IPRG */ अणु EDMAC0, EDMAC1, EDMAC2 पूर्ण पूर्ण,
	अणु 0xa4080004, 0, 16, 4, /* IPRH */ अणु 0, 0, 0, SIOF0 पूर्ण पूर्ण,
	अणु 0xa4080006, 0, 16, 4, /* IPRI */ अणु 0, 0, SIOF1 पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh7710", vectors, शून्य,
			 शून्य, prio_रेजिस्टरs, शून्य);

अटल काष्ठा resource rtc_resources[] = अणु
	[0] =	अणु
		.start	= 0xa413fec0,
		.end	= 0xa413fec0 + 0x1e,
		.flags  = IORESOURCE_IO,
	पूर्ण,
	[1] =	अणु
		.start  = evt2irq(0x480),
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
	.scscr		= SCSCR_REIE | SCSCR_CKE1,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xa4400000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x880)),
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
	.scscr		= SCSCR_REIE | SCSCR_CKE1,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर1_resources[] = अणु
	DEFINE_RES_MEM(0xa4410000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x900)),
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

अटल काष्ठा platक्रमm_device *sh7710_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&पंचांगu0_device,
	&rtc_device,
पूर्ण;

अटल पूर्णांक __init sh7710_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sh7710_devices,
				    ARRAY_SIZE(sh7710_devices));
पूर्ण
arch_initcall(sh7710_devices_setup);

अटल काष्ठा platक्रमm_device *sh7710_early_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&पंचांगu0_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(sh7710_early_devices,
				   ARRAY_SIZE(sh7710_early_devices));
पूर्ण

व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
	plat_irq_setup_sh3();
पूर्ण
