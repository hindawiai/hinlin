<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH3 Setup code क्रम SH7706, SH7707, SH7708, SH7709
 *
 *  Copyright (C) 2007  Magnus Damm
 *  Copyright (C) 2009  Paul Mundt
 *
 * Based on setup-sh7709.c
 *
 *  Copyright (C) 2006  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <cpu/serial.h>
#समावेश <यंत्र/platक्रमm_early.h>

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */
	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5,
	PINT07, PINT815,
	DMAC, SCIF0, SCIF2, SCI, ADC_ADI,
	LCDC, PCC0, PCC1,
	TMU0, TMU1, TMU2,
	RTC, WDT, REF,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(TMU2, 0x460),
	INTC_VECT(RTC, 0x480), INTC_VECT(RTC, 0x4a0),
	INTC_VECT(RTC, 0x4c0),
	INTC_VECT(SCI, 0x4e0), INTC_VECT(SCI, 0x500),
	INTC_VECT(SCI, 0x520), INTC_VECT(SCI, 0x540),
	INTC_VECT(WDT, 0x560),
	INTC_VECT(REF, 0x580),
	INTC_VECT(REF, 0x5a0),
#अगर defined(CONFIG_CPU_SUBTYPE_SH7706) || \
    defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	/* IRQ0->5 are handled in setup-sh3.c */
	INTC_VECT(DMAC, 0x800), INTC_VECT(DMAC, 0x820),
	INTC_VECT(DMAC, 0x840), INTC_VECT(DMAC, 0x860),
	INTC_VECT(ADC_ADI, 0x980),
	INTC_VECT(SCIF2, 0x900), INTC_VECT(SCIF2, 0x920),
	INTC_VECT(SCIF2, 0x940), INTC_VECT(SCIF2, 0x960),
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	INTC_VECT(PINT07, 0x700), INTC_VECT(PINT815, 0x720),
	INTC_VECT(SCIF0, 0x880), INTC_VECT(SCIF0, 0x8a0),
	INTC_VECT(SCIF0, 0x8c0), INTC_VECT(SCIF0, 0x8e0),
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_SUBTYPE_SH7707)
	INTC_VECT(LCDC, 0x9a0),
	INTC_VECT(PCC0, 0x9c0), INTC_VECT(PCC1, 0x9e0),
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xfffffee2, 0, 16, 4, /* IPRA */ अणु TMU0, TMU1, TMU2, RTC पूर्ण पूर्ण,
	अणु 0xfffffee4, 0, 16, 4, /* IPRB */ अणु WDT, REF, SCI, 0 पूर्ण पूर्ण,
#अगर defined(CONFIG_CPU_SUBTYPE_SH7706) || \
    defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	अणु 0xa4000016, 0, 16, 4, /* IPRC */ अणु IRQ3, IRQ2, IRQ1, IRQ0 पूर्ण पूर्ण,
	अणु 0xa4000018, 0, 16, 4, /* IPRD */ अणु 0, 0, IRQ5, IRQ4 पूर्ण पूर्ण,
	अणु 0xa400001a, 0, 16, 4, /* IPRE */ अणु DMAC, 0, SCIF2, ADC_ADI पूर्ण पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	अणु 0xa4000018, 0, 16, 4, /* IPRD */ अणु PINT07, PINT815, पूर्ण पूर्ण,
	अणु 0xa400001a, 0, 16, 4, /* IPRE */ अणु 0, SCIF0 पूर्ण पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_SUBTYPE_SH7707)
	अणु 0xa400001c, 0, 16, 4, /* IPRF */ अणु 0, LCDC, PCC0, PCC1, पूर्ण पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh770x", vectors, शून्य,
			 शून्य, prio_रेजिस्टरs, शून्य);

अटल काष्ठा resource rtc_resources[] = अणु
	[0] =	अणु
		.start	= 0xfffffec0,
		.end	= 0xfffffec0 + 0x1e,
		.flags  = IORESOURCE_IO,
	पूर्ण,
	[1] =	अणु
		.start	= evt2irq(0x480),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_device = अणु
	.name		= "sh-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(rtc_resources),
	.resource	= rtc_resources,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.type		= PORT_SCI,
	.ops		= &sh770x_sci_port_ops,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xfffffe80, 0x10),
	DEFINE_RES_IRQ(evt2irq(0x4e0)),
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
#अगर defined(CONFIG_CPU_SUBTYPE_SH7706) || \
    defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
अटल काष्ठा plat_sci_port scअगर1_platक्रमm_data = अणु
	.type		= PORT_SCIF,
	.ops		= &sh770x_sci_port_ops,
	.regtype	= SCIx_SH3_SCIF_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर1_resources[] = अणु
	DEFINE_RES_MEM(0xa4000150, 0x10),
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
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
अटल काष्ठा plat_sci_port scअगर2_platक्रमm_data = अणु
	.type		= PORT_IRDA,
	.ops		= &sh770x_sci_port_ops,
पूर्ण;

अटल काष्ठा resource scअगर2_resources[] = अणु
	DEFINE_RES_MEM(0xa4000140, 0x10),
	DEFINE_RES_IRQ(evt2irq(0x880)),
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
#पूर्ण_अगर

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

अटल काष्ठा platक्रमm_device *sh770x_devices[] __initdata = अणु
	&scअगर0_device,
#अगर defined(CONFIG_CPU_SUBTYPE_SH7706) || \
    defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	&scअगर1_device,
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	&scअगर2_device,
#पूर्ण_अगर
	&पंचांगu0_device,
	&rtc_device,
पूर्ण;

अटल पूर्णांक __init sh770x_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sh770x_devices,
		ARRAY_SIZE(sh770x_devices));
पूर्ण
arch_initcall(sh770x_devices_setup);

अटल काष्ठा platक्रमm_device *sh770x_early_devices[] __initdata = अणु
	&scअगर0_device,
#अगर defined(CONFIG_CPU_SUBTYPE_SH7706) || \
    defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	&scअगर1_device,
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	&scअगर2_device,
#पूर्ण_अगर
	&पंचांगu0_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(sh770x_early_devices,
				   ARRAY_SIZE(sh770x_early_devices));
पूर्ण

व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
#अगर defined(CONFIG_CPU_SUBTYPE_SH7706) || \
    defined(CONFIG_CPU_SUBTYPE_SH7707) || \
    defined(CONFIG_CPU_SUBTYPE_SH7709)
	plat_irq_setup_sh3();
#पूर्ण_अगर
पूर्ण
