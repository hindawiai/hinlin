<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  SH7201 setup
 *
 *  Copyright (C) 2008  Peter Grअगरfin pgrअगरfin@mpc-data.co.uk
 *  Copyright (C) 2009  Paul Mundt
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/platक्रमm_early.h>

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */
	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7,
	PINT0, PINT1, PINT2, PINT3, PINT4, PINT5, PINT6, PINT7,

	ADC_ADI,

	MTU20_ABCD, MTU20_VEF, MTU21_AB, MTU21_VU, MTU22_AB, MTU22_VU,
	MTU23_ABCD, MTU24_ABCD, MTU25_UVW, MTU2_TCI3V, MTU2_TCI4V,

	RTC, WDT,

	IIC30, IIC31, IIC32,

	DMAC0_DMINT0, DMAC1_DMINT1,
	DMAC2_DMINT2, DMAC3_DMINT3,

	SCIF0, SCIF1, SCIF2, SCIF3, SCIF4, SCIF5, SCIF6, SCIF7,

	DMAC0_DMINTA, DMAC4_DMINT4, DMAC5_DMINT5, DMAC6_DMINT6,
	DMAC7_DMINT7,

	RCAN0, RCAN1,

	SSI0_SSII, SSI1_SSII,

	TMR0, TMR1,

	/* पूर्णांकerrupt groups */
	PINT,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_IRQ(IRQ0, 64), INTC_IRQ(IRQ1, 65),
	INTC_IRQ(IRQ2, 66), INTC_IRQ(IRQ3, 67),
	INTC_IRQ(IRQ4, 68), INTC_IRQ(IRQ5, 69),
	INTC_IRQ(IRQ6, 70), INTC_IRQ(IRQ7, 71),

	INTC_IRQ(PINT0, 80), INTC_IRQ(PINT1, 81),
	INTC_IRQ(PINT2, 82), INTC_IRQ(PINT3, 83),
	INTC_IRQ(PINT4, 84), INTC_IRQ(PINT5, 85),
	INTC_IRQ(PINT6, 86), INTC_IRQ(PINT7, 87),

	INTC_IRQ(ADC_ADI, 92),

	INTC_IRQ(MTU20_ABCD, 108), INTC_IRQ(MTU20_ABCD, 109),
	INTC_IRQ(MTU20_ABCD, 110), INTC_IRQ(MTU20_ABCD, 111),

	INTC_IRQ(MTU20_VEF, 112), INTC_IRQ(MTU20_VEF, 113),
	INTC_IRQ(MTU20_VEF, 114),

	INTC_IRQ(MTU21_AB, 116), INTC_IRQ(MTU21_AB, 117),
	INTC_IRQ(MTU21_VU, 120), INTC_IRQ(MTU21_VU, 121),

	INTC_IRQ(MTU22_AB, 124), INTC_IRQ(MTU22_AB, 125),
	INTC_IRQ(MTU22_VU, 128), INTC_IRQ(MTU22_VU, 129),

	INTC_IRQ(MTU23_ABCD, 132), INTC_IRQ(MTU23_ABCD, 133),
	INTC_IRQ(MTU23_ABCD, 134), INTC_IRQ(MTU23_ABCD, 135),

	INTC_IRQ(MTU2_TCI3V, 136),

	INTC_IRQ(MTU24_ABCD, 140), INTC_IRQ(MTU24_ABCD, 141),
	INTC_IRQ(MTU24_ABCD, 142), INTC_IRQ(MTU24_ABCD, 143),

	INTC_IRQ(MTU2_TCI4V, 144),

	INTC_IRQ(MTU25_UVW, 148), INTC_IRQ(MTU25_UVW, 149),
	INTC_IRQ(MTU25_UVW, 150),

	INTC_IRQ(RTC, 152), INTC_IRQ(RTC, 153),
	INTC_IRQ(RTC, 154),

	INTC_IRQ(WDT, 156),

	INTC_IRQ(IIC30, 157), INTC_IRQ(IIC30, 158),
	INTC_IRQ(IIC30, 159), INTC_IRQ(IIC30, 160),
	INTC_IRQ(IIC30, 161),

	INTC_IRQ(IIC31, 164), INTC_IRQ(IIC31, 165),
	INTC_IRQ(IIC31, 166), INTC_IRQ(IIC31, 167),
	INTC_IRQ(IIC31, 168),

	INTC_IRQ(IIC32, 170), INTC_IRQ(IIC32, 171),
	INTC_IRQ(IIC32, 172), INTC_IRQ(IIC32, 173),
	INTC_IRQ(IIC32, 174),

	INTC_IRQ(DMAC0_DMINT0, 176), INTC_IRQ(DMAC1_DMINT1, 177),
	INTC_IRQ(DMAC2_DMINT2, 178), INTC_IRQ(DMAC3_DMINT3, 179),

	INTC_IRQ(SCIF0, 180), INTC_IRQ(SCIF0, 181),
	INTC_IRQ(SCIF0, 182), INTC_IRQ(SCIF0, 183),
	INTC_IRQ(SCIF1, 184), INTC_IRQ(SCIF1, 185),
	INTC_IRQ(SCIF1, 186), INTC_IRQ(SCIF1, 187),
	INTC_IRQ(SCIF2, 188), INTC_IRQ(SCIF2, 189),
	INTC_IRQ(SCIF2, 190), INTC_IRQ(SCIF2, 191),
	INTC_IRQ(SCIF3, 192), INTC_IRQ(SCIF3, 193),
	INTC_IRQ(SCIF3, 194), INTC_IRQ(SCIF3, 195),
	INTC_IRQ(SCIF4, 196), INTC_IRQ(SCIF4, 197),
	INTC_IRQ(SCIF4, 198), INTC_IRQ(SCIF4, 199),
	INTC_IRQ(SCIF5, 200), INTC_IRQ(SCIF5, 201),
	INTC_IRQ(SCIF5, 202), INTC_IRQ(SCIF5, 203),
	INTC_IRQ(SCIF6, 204), INTC_IRQ(SCIF6, 205),
	INTC_IRQ(SCIF6, 206), INTC_IRQ(SCIF6, 207),
	INTC_IRQ(SCIF7, 208), INTC_IRQ(SCIF7, 209),
	INTC_IRQ(SCIF7, 210), INTC_IRQ(SCIF7, 211),

	INTC_IRQ(DMAC0_DMINTA, 212), INTC_IRQ(DMAC4_DMINT4, 216),
	INTC_IRQ(DMAC5_DMINT5, 217), INTC_IRQ(DMAC6_DMINT6, 218),
	INTC_IRQ(DMAC7_DMINT7, 219),

	INTC_IRQ(RCAN0, 228), INTC_IRQ(RCAN0, 229),
	INTC_IRQ(RCAN0, 230),
	INTC_IRQ(RCAN0, 231), INTC_IRQ(RCAN0, 232),

	INTC_IRQ(RCAN1, 234), INTC_IRQ(RCAN1, 235),
	INTC_IRQ(RCAN1, 236),
	INTC_IRQ(RCAN1, 237), INTC_IRQ(RCAN1, 238),

	INTC_IRQ(SSI0_SSII, 244), INTC_IRQ(SSI1_SSII, 245),

	INTC_IRQ(TMR0, 246), INTC_IRQ(TMR0, 247),
	INTC_IRQ(TMR0, 248),

	INTC_IRQ(TMR1, 252), INTC_IRQ(TMR1, 253),
	INTC_IRQ(TMR1, 254),
पूर्ण;

अटल काष्ठा पूर्णांकc_group groups[] __initdata = अणु
	INTC_GROUP(PINT, PINT0, PINT1, PINT2, PINT3,
		   PINT4, PINT5, PINT6, PINT7),
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xfffe9418, 0, 16, 4, /* IPR01 */ अणु IRQ0, IRQ1, IRQ2, IRQ3 पूर्ण पूर्ण,
	अणु 0xfffe941a, 0, 16, 4, /* IPR02 */ अणु IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
	अणु 0xfffe9420, 0, 16, 4, /* IPR05 */ अणु PINT, 0, ADC_ADI, 0 पूर्ण पूर्ण,
	अणु 0xfffe9800, 0, 16, 4, /* IPR06 */ अणु 0, MTU20_ABCD, MTU20_VEF, MTU21_AB पूर्ण पूर्ण,
	अणु 0xfffe9802, 0, 16, 4, /* IPR07 */ अणु MTU21_VU, MTU22_AB, MTU22_VU,  MTU23_ABCD पूर्ण पूर्ण,
	अणु 0xfffe9804, 0, 16, 4, /* IPR08 */ अणु MTU2_TCI3V, MTU24_ABCD, MTU2_TCI4V, MTU25_UVW पूर्ण पूर्ण,

	अणु 0xfffe9806, 0, 16, 4, /* IPR09 */ अणु RTC, WDT, IIC30, 0 पूर्ण पूर्ण,
	अणु 0xfffe9808, 0, 16, 4, /* IPR10 */ अणु IIC31, IIC32, DMAC0_DMINT0, DMAC1_DMINT1 पूर्ण पूर्ण,
	अणु 0xfffe980a, 0, 16, 4, /* IPR11 */ अणु DMAC2_DMINT2, DMAC3_DMINT3, SCIF0, SCIF1 पूर्ण पूर्ण,
	अणु 0xfffe980c, 0, 16, 4, /* IPR12 */ अणु SCIF2, SCIF3, SCIF4, SCIF5 पूर्ण पूर्ण,
	अणु 0xfffe980e, 0, 16, 4, /* IPR13 */ अणु SCIF6, SCIF7, DMAC0_DMINTA, DMAC4_DMINT4  पूर्ण पूर्ण,
	अणु 0xfffe9810, 0, 16, 4, /* IPR14 */ अणु DMAC5_DMINT5, DMAC6_DMINT6, DMAC7_DMINT7, 0 पूर्ण पूर्ण,
	अणु 0xfffe9812, 0, 16, 4, /* IPR15 */ अणु 0, RCAN0, RCAN1, 0 पूर्ण पूर्ण,
	अणु 0xfffe9814, 0, 16, 4, /* IPR16 */ अणु SSI0_SSII, SSI1_SSII, TMR0, TMR1 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xfffe9408, 0, 16, /* PINTER */
	  अणु 0, 0, 0, 0, 0, 0, 0, 0,
	    PINT7, PINT6, PINT5, PINT4, PINT3, PINT2, PINT1, PINT0 पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh7201", vectors, groups,
			 mask_रेजिस्टरs, prio_रेजिस्टरs, शून्य);

अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xfffe8000, 0x100),
	DEFINE_RES_IRQ(180),
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
	DEFINE_RES_MEM(0xfffe8800, 0x100),
	DEFINE_RES_IRQ(184),
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
	DEFINE_RES_MEM(0xfffe9000, 0x100),
	DEFINE_RES_IRQ(188),
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
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर3_resources[] = अणु
	DEFINE_RES_MEM(0xfffe9800, 0x100),
	DEFINE_RES_IRQ(192),
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

अटल काष्ठा plat_sci_port scअगर4_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर4_resources[] = अणु
	DEFINE_RES_MEM(0xfffea000, 0x100),
	DEFINE_RES_IRQ(196),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर4_device = अणु
	.name		= "sh-sci",
	.id		= 4,
	.resource	= scअगर4_resources,
	.num_resources	= ARRAY_SIZE(scअगर4_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर4_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर5_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर5_resources[] = अणु
	DEFINE_RES_MEM(0xfffea800, 0x100),
	DEFINE_RES_IRQ(200),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर5_device = अणु
	.name		= "sh-sci",
	.id		= 5,
	.resource	= scअगर5_resources,
	.num_resources	= ARRAY_SIZE(scअगर5_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर5_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर6_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर6_resources[] = अणु
	DEFINE_RES_MEM(0xfffeb000, 0x100),
	DEFINE_RES_IRQ(204),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर6_device = अणु
	.name		= "sh-sci",
	.id		= 6,
	.resource	= scअगर6_resources,
	.num_resources	= ARRAY_SIZE(scअगर6_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर6_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर7_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर7_resources[] = अणु
	DEFINE_RES_MEM(0xfffeb800, 0x100),
	DEFINE_RES_IRQ(208),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर7_device = अणु
	.name		= "sh-sci",
	.id		= 7,
	.resource	= scअगर7_resources,
	.num_resources	= ARRAY_SIZE(scअगर7_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर7_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource rtc_resources[] = अणु
	[0] = अणु
		.start	= 0xffff0800,
		.end	= 0xffff2000 + 0x58 - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		/* Shared Period/Carry/Alarm IRQ */
		.start	= 152,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_device = अणु
	.name		= "sh-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(rtc_resources),
	.resource	= rtc_resources,
पूर्ण;

अटल काष्ठा resource mtu2_resources[] = अणु
	DEFINE_RES_MEM(0xfffe4000, 0x400),
	DEFINE_RES_IRQ_NAMED(108, "tgi0a"),
	DEFINE_RES_IRQ_NAMED(116, "tgi1a"),
	DEFINE_RES_IRQ_NAMED(124, "tgi1b"),
पूर्ण;

अटल काष्ठा platक्रमm_device mtu2_device = अणु
	.name		= "sh-mtu2",
	.id		= -1,
	.resource	= mtu2_resources,
	.num_resources	= ARRAY_SIZE(mtu2_resources),
पूर्ण;

अटल काष्ठा platक्रमm_device *sh7201_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&scअगर3_device,
	&scअगर4_device,
	&scअगर5_device,
	&scअगर6_device,
	&scअगर7_device,
	&rtc_device,
	&mtu2_device,
पूर्ण;

अटल पूर्णांक __init sh7201_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sh7201_devices,
				    ARRAY_SIZE(sh7201_devices));
पूर्ण
arch_initcall(sh7201_devices_setup);

व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
पूर्ण

अटल काष्ठा platक्रमm_device *sh7201_early_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&scअगर3_device,
	&scअगर4_device,
	&scअगर5_device,
	&scअगर6_device,
	&scअगर7_device,
	&mtu2_device,
पूर्ण;

#घोषणा STBCR3 0xfffe0408

व्योम __init plat_early_device_setup(व्योम)
अणु
	/* enable MTU2 घड़ी */
	__raw_ग_लिखोb(__raw_पढ़ोb(STBCR3) & ~0x20, STBCR3);

	sh_early_platक्रमm_add_devices(sh7201_early_devices,
				   ARRAY_SIZE(sh7201_early_devices));
पूर्ण
