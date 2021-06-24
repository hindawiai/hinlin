<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7705 Setup
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
#समावेश <cpu/serial.h>
#समावेश <यंत्र/platक्रमm_early.h>

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */
	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5,
	PINT07, PINT815,

	DMAC, SCIF0, SCIF2, ADC_ADI, USB,

	TPU0, TPU1, TPU2, TPU3,
	TMU0, TMU1, TMU2,

	RTC, WDT, REF_RCMI,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	/* IRQ0->5 are handled in setup-sh3.c */
	INTC_VECT(PINT07, 0x700), INTC_VECT(PINT815, 0x720),
	INTC_VECT(DMAC, 0x800), INTC_VECT(DMAC, 0x820),
	INTC_VECT(DMAC, 0x840), INTC_VECT(DMAC, 0x860),
	INTC_VECT(SCIF0, 0x880), INTC_VECT(SCIF0, 0x8a0),
	INTC_VECT(SCIF0, 0x8e0),
	INTC_VECT(SCIF2, 0x900), INTC_VECT(SCIF2, 0x920),
	INTC_VECT(SCIF2, 0x960),
	INTC_VECT(ADC_ADI, 0x980),
	INTC_VECT(USB, 0xa20), INTC_VECT(USB, 0xa40),
	INTC_VECT(TPU0, 0xc00), INTC_VECT(TPU1, 0xc20),
	INTC_VECT(TPU2, 0xc80), INTC_VECT(TPU3, 0xca0),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(TMU2, 0x460),
	INTC_VECT(RTC, 0x480), INTC_VECT(RTC, 0x4a0),
	INTC_VECT(RTC, 0x4c0),
	INTC_VECT(WDT, 0x560),
	INTC_VECT(REF_RCMI, 0x580),
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xfffffee2, 0, 16, 4, /* IPRA */ अणु TMU0, TMU1, TMU2, RTC पूर्ण पूर्ण,
	अणु 0xfffffee4, 0, 16, 4, /* IPRB */ अणु WDT, REF_RCMI, 0, 0 पूर्ण पूर्ण,
	अणु 0xa4000016, 0, 16, 4, /* IPRC */ अणु IRQ3, IRQ2, IRQ1, IRQ0 पूर्ण पूर्ण,
	अणु 0xa4000018, 0, 16, 4, /* IPRD */ अणु PINT07, PINT815, IRQ5, IRQ4 पूर्ण पूर्ण,
	अणु 0xa400001a, 0, 16, 4, /* IPRE */ अणु DMAC, SCIF0, SCIF2, ADC_ADI पूर्ण पूर्ण,
	अणु 0xa4080000, 0, 16, 4, /* IPRF */ अणु 0, 0, USB पूर्ण पूर्ण,
	अणु 0xa4080002, 0, 16, 4, /* IPRG */ अणु TPU0, TPU1 पूर्ण पूर्ण,
	अणु 0xa4080004, 0, 16, 4, /* IPRH */ अणु TPU2, TPU3 पूर्ण पूर्ण,

पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh7705", vectors, शून्य,
			 शून्य, prio_रेजिस्टरs, शून्य);

अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr		= SCSCR_CKE1,
	.type		= PORT_SCIF,
	.ops		= &sh770x_sci_port_ops,
	.regtype	= SCIx_SH7705_SCIF_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xa4410000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x900)),
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
	.ops		= &sh770x_sci_port_ops,
	.regtype	= SCIx_SH7705_SCIF_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर1_resources[] = अणु
	DEFINE_RES_MEM(0xa4400000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x880)),
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

अटल काष्ठा resource rtc_resources[] = अणु
	[0] =	अणु
		.start	= 0xfffffec0,
		.end	= 0xfffffec0 + 0x1e,
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

अटल काष्ठा sh_समयr_config पंचांगu0_platक्रमm_data = अणु
	.channels_mask = 7,
पूर्ण;

अटल काष्ठा resource पंचांगu0_resources[] = अणु
	DEFINE_RES_MEM(0xfffffe90, 0x2c),
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

अटल काष्ठा platक्रमm_device *sh7705_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&पंचांगu0_device,
	&rtc_device,
पूर्ण;

अटल पूर्णांक __init sh7705_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sh7705_devices,
				    ARRAY_SIZE(sh7705_devices));
पूर्ण
arch_initcall(sh7705_devices_setup);

अटल काष्ठा platक्रमm_device *sh7705_early_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&पंचांगu0_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(sh7705_early_devices,
				   ARRAY_SIZE(sh7705_early_devices));
पूर्ण

व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
	plat_irq_setup_sh3();
पूर्ण
