<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7203 and SH7263 Setup
 *
 *  Copyright (C) 2007 - 2009  Paul Mundt
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
	DMAC0, DMAC1, DMAC2, DMAC3, DMAC4, DMAC5, DMAC6, DMAC7,
	USB, LCDC, CMT0, CMT1, BSC, WDT,

	MTU0_ABCD, MTU0_VEF, MTU1_AB, MTU1_VU, MTU2_AB, MTU2_VU,
	MTU3_ABCD, MTU4_ABCD, MTU2_TCI3V, MTU2_TCI4V,

	ADC_ADI,

	IIC30, IIC31, IIC32, IIC33,
	SCIF0, SCIF1, SCIF2, SCIF3,

	SSU0, SSU1,

	SSI0_SSII, SSI1_SSII, SSI2_SSII, SSI3_SSII,

	/* ROM-DEC, SDHI, SRC, and IEB are SH7263 specअगरic */
	ROMDEC, FLCTL, SDHI, RTC, RCAN0, RCAN1,
	SRC, IEBI,

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
	INTC_IRQ(DMAC0, 108), INTC_IRQ(DMAC0, 109),
	INTC_IRQ(DMAC1, 112), INTC_IRQ(DMAC1, 113),
	INTC_IRQ(DMAC2, 116), INTC_IRQ(DMAC2, 117),
	INTC_IRQ(DMAC3, 120), INTC_IRQ(DMAC3, 121),
	INTC_IRQ(DMAC4, 124), INTC_IRQ(DMAC4, 125),
	INTC_IRQ(DMAC5, 128), INTC_IRQ(DMAC5, 129),
	INTC_IRQ(DMAC6, 132), INTC_IRQ(DMAC6, 133),
	INTC_IRQ(DMAC7, 136), INTC_IRQ(DMAC7, 137),
	INTC_IRQ(USB, 140), INTC_IRQ(LCDC, 141),
	INTC_IRQ(CMT0, 142), INTC_IRQ(CMT1, 143),
	INTC_IRQ(BSC, 144), INTC_IRQ(WDT, 145),
	INTC_IRQ(MTU0_ABCD, 146), INTC_IRQ(MTU0_ABCD, 147),
	INTC_IRQ(MTU0_ABCD, 148), INTC_IRQ(MTU0_ABCD, 149),
	INTC_IRQ(MTU0_VEF, 150),
	INTC_IRQ(MTU0_VEF, 151), INTC_IRQ(MTU0_VEF, 152),
	INTC_IRQ(MTU1_AB, 153), INTC_IRQ(MTU1_AB, 154),
	INTC_IRQ(MTU1_VU, 155), INTC_IRQ(MTU1_VU, 156),
	INTC_IRQ(MTU2_AB, 157), INTC_IRQ(MTU2_AB, 158),
	INTC_IRQ(MTU2_VU, 159), INTC_IRQ(MTU2_VU, 160),
	INTC_IRQ(MTU3_ABCD, 161), INTC_IRQ(MTU3_ABCD, 162),
	INTC_IRQ(MTU3_ABCD, 163), INTC_IRQ(MTU3_ABCD, 164),
	INTC_IRQ(MTU2_TCI3V, 165),
	INTC_IRQ(MTU4_ABCD, 166), INTC_IRQ(MTU4_ABCD, 167),
	INTC_IRQ(MTU4_ABCD, 168), INTC_IRQ(MTU4_ABCD, 169),
	INTC_IRQ(MTU2_TCI4V, 170),
	INTC_IRQ(ADC_ADI, 171),
	INTC_IRQ(IIC30, 172), INTC_IRQ(IIC30, 173),
	INTC_IRQ(IIC30, 174), INTC_IRQ(IIC30, 175),
	INTC_IRQ(IIC30, 176),
	INTC_IRQ(IIC31, 177), INTC_IRQ(IIC31, 178),
	INTC_IRQ(IIC31, 179), INTC_IRQ(IIC31, 180),
	INTC_IRQ(IIC31, 181),
	INTC_IRQ(IIC32, 182), INTC_IRQ(IIC32, 183),
	INTC_IRQ(IIC32, 184), INTC_IRQ(IIC32, 185),
	INTC_IRQ(IIC32, 186),
	INTC_IRQ(IIC33, 187), INTC_IRQ(IIC33, 188),
	INTC_IRQ(IIC33, 189), INTC_IRQ(IIC33, 190),
	INTC_IRQ(IIC33, 191),
	INTC_IRQ(SCIF0, 192), INTC_IRQ(SCIF0, 193),
	INTC_IRQ(SCIF0, 194), INTC_IRQ(SCIF0, 195),
	INTC_IRQ(SCIF1, 196), INTC_IRQ(SCIF1, 197),
	INTC_IRQ(SCIF1, 198), INTC_IRQ(SCIF1, 199),
	INTC_IRQ(SCIF2, 200), INTC_IRQ(SCIF2, 201),
	INTC_IRQ(SCIF2, 202), INTC_IRQ(SCIF2, 203),
	INTC_IRQ(SCIF3, 204), INTC_IRQ(SCIF3, 205),
	INTC_IRQ(SCIF3, 206), INTC_IRQ(SCIF3, 207),
	INTC_IRQ(SSU0, 208), INTC_IRQ(SSU0, 209),
	INTC_IRQ(SSU0, 210),
	INTC_IRQ(SSU1, 211), INTC_IRQ(SSU1, 212),
	INTC_IRQ(SSU1, 213),
	INTC_IRQ(SSI0_SSII, 214), INTC_IRQ(SSI1_SSII, 215),
	INTC_IRQ(SSI2_SSII, 216), INTC_IRQ(SSI3_SSII, 217),
	INTC_IRQ(FLCTL, 224), INTC_IRQ(FLCTL, 225),
	INTC_IRQ(FLCTL, 226), INTC_IRQ(FLCTL, 227),
	INTC_IRQ(RTC, 231), INTC_IRQ(RTC, 232),
	INTC_IRQ(RTC, 233),
	INTC_IRQ(RCAN0, 234), INTC_IRQ(RCAN0, 235),
	INTC_IRQ(RCAN0, 236), INTC_IRQ(RCAN0, 237),
	INTC_IRQ(RCAN0, 238),
	INTC_IRQ(RCAN1, 239), INTC_IRQ(RCAN1, 240),
	INTC_IRQ(RCAN1, 241), INTC_IRQ(RCAN1, 242),
	INTC_IRQ(RCAN1, 243),

	/* SH7263-specअगरic trash */
#अगर_घोषित CONFIG_CPU_SUBTYPE_SH7263
	INTC_IRQ(ROMDEC, 218), INTC_IRQ(ROMDEC, 219),
	INTC_IRQ(ROMDEC, 220), INTC_IRQ(ROMDEC, 221),
	INTC_IRQ(ROMDEC, 222), INTC_IRQ(ROMDEC, 223),

	INTC_IRQ(SDHI, 228), INTC_IRQ(SDHI, 229),
	INTC_IRQ(SDHI, 230),

	INTC_IRQ(SRC, 244), INTC_IRQ(SRC, 245),
	INTC_IRQ(SRC, 246),

	INTC_IRQ(IEBI, 247),
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा पूर्णांकc_group groups[] __initdata = अणु
	INTC_GROUP(PINT, PINT0, PINT1, PINT2, PINT3,
		   PINT4, PINT5, PINT6, PINT7),
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xfffe0818, 0, 16, 4, /* IPR01 */ अणु IRQ0, IRQ1, IRQ2, IRQ3 पूर्ण पूर्ण,
	अणु 0xfffe081a, 0, 16, 4, /* IPR02 */ अणु IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
	अणु 0xfffe0820, 0, 16, 4, /* IPR05 */ अणु PINT, 0, 0, 0 पूर्ण पूर्ण,
	अणु 0xfffe0c00, 0, 16, 4, /* IPR06 */ अणु DMAC0, DMAC1, DMAC2, DMAC3 पूर्ण पूर्ण,
	अणु 0xfffe0c02, 0, 16, 4, /* IPR07 */ अणु DMAC4, DMAC5, DMAC6, DMAC7 पूर्ण पूर्ण,
	अणु 0xfffe0c04, 0, 16, 4, /* IPR08 */ अणु USB, LCDC, CMT0, CMT1 पूर्ण पूर्ण,
	अणु 0xfffe0c06, 0, 16, 4, /* IPR09 */ अणु BSC, WDT, MTU0_ABCD, MTU0_VEF पूर्ण पूर्ण,
	अणु 0xfffe0c08, 0, 16, 4, /* IPR10 */ अणु MTU1_AB, MTU1_VU, MTU2_AB,
					      MTU2_VU पूर्ण पूर्ण,
	अणु 0xfffe0c0a, 0, 16, 4, /* IPR11 */ अणु MTU3_ABCD, MTU2_TCI3V, MTU4_ABCD,
					      MTU2_TCI4V पूर्ण पूर्ण,
	अणु 0xfffe0c0c, 0, 16, 4, /* IPR12 */ अणु ADC_ADI, IIC30, IIC31, IIC32 पूर्ण पूर्ण,
	अणु 0xfffe0c0e, 0, 16, 4, /* IPR13 */ अणु IIC33, SCIF0, SCIF1, SCIF2 पूर्ण पूर्ण,
	अणु 0xfffe0c10, 0, 16, 4, /* IPR14 */ अणु SCIF3, SSU0, SSU1, SSI0_SSII पूर्ण पूर्ण,
#अगर_घोषित CONFIG_CPU_SUBTYPE_SH7203
	अणु 0xfffe0c12, 0, 16, 4, /* IPR15 */ अणु SSI1_SSII, SSI2_SSII,
					      SSI3_SSII, 0 पूर्ण पूर्ण,
	अणु 0xfffe0c14, 0, 16, 4, /* IPR16 */ अणु FLCTL, 0, RTC, RCAN0 पूर्ण पूर्ण,
	अणु 0xfffe0c16, 0, 16, 4, /* IPR17 */ अणु RCAN1, 0, 0, 0 पूर्ण पूर्ण,
#अन्यथा
	अणु 0xfffe0c12, 0, 16, 4, /* IPR15 */ अणु SSI1_SSII, SSI2_SSII,
					      SSI3_SSII, ROMDEC पूर्ण पूर्ण,
	अणु 0xfffe0c14, 0, 16, 4, /* IPR16 */ अणु FLCTL, SDHI, RTC, RCAN0 पूर्ण पूर्ण,
	अणु 0xfffe0c16, 0, 16, 4, /* IPR17 */ अणु RCAN1, SRC, IEBI, 0 पूर्ण पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xfffe0808, 0, 16, /* PINTER */
	  अणु 0, 0, 0, 0, 0, 0, 0, 0,
	    PINT7, PINT6, PINT5, PINT4, PINT3, PINT2, PINT1, PINT0 पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh7203", vectors, groups,
			 mask_रेजिस्टरs, prio_रेजिस्टरs, शून्य);

अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
	.regtype	= SCIx_SH2_SCIF_FIFODATA_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xfffe8000, 0x100),
	DEFINE_RES_IRQ(192),
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
	.regtype	= SCIx_SH2_SCIF_FIFODATA_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर1_resources[] = अणु
	DEFINE_RES_MEM(0xfffe8800, 0x100),
	DEFINE_RES_IRQ(196),
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
	.regtype	= SCIx_SH2_SCIF_FIFODATA_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर2_resources[] = अणु
	DEFINE_RES_MEM(0xfffe9000, 0x100),
	DEFINE_RES_IRQ(200),
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
	.regtype	= SCIx_SH2_SCIF_FIFODATA_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर3_resources[] = अणु
	DEFINE_RES_MEM(0xfffe9800, 0x100),
	DEFINE_RES_IRQ(204),
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

अटल काष्ठा sh_समयr_config cmt_platक्रमm_data = अणु
	.channels_mask = 3,
पूर्ण;

अटल काष्ठा resource cmt_resources[] = अणु
	DEFINE_RES_MEM(0xfffec000, 0x10),
	DEFINE_RES_IRQ(142),
	DEFINE_RES_IRQ(143),
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

अटल काष्ठा resource mtu2_resources[] = अणु
	DEFINE_RES_MEM(0xfffe4000, 0x400),
	DEFINE_RES_IRQ_NAMED(146, "tgi0a"),
	DEFINE_RES_IRQ_NAMED(153, "tgi1a"),
पूर्ण;

अटल काष्ठा platक्रमm_device mtu2_device = अणु
	.name		= "sh-mtu2",
	.id		= -1,
	.resource	= mtu2_resources,
	.num_resources	= ARRAY_SIZE(mtu2_resources),
पूर्ण;

अटल काष्ठा resource rtc_resources[] = अणु
	[0] = अणु
		.start	= 0xffff2000,
		.end	= 0xffff2000 + 0x58 - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		/* Shared Period/Carry/Alarm IRQ */
		.start	= 231,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_device = अणु
	.name		= "sh-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(rtc_resources),
	.resource	= rtc_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *sh7203_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&scअगर3_device,
	&cmt_device,
	&mtu2_device,
	&rtc_device,
पूर्ण;

अटल पूर्णांक __init sh7203_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sh7203_devices,
				    ARRAY_SIZE(sh7203_devices));
पूर्ण
arch_initcall(sh7203_devices_setup);

व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
पूर्ण

अटल काष्ठा platक्रमm_device *sh7203_early_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&scअगर3_device,
	&cmt_device,
	&mtu2_device,
पूर्ण;

#घोषणा STBCR3 0xfffe0408
#घोषणा STBCR4 0xfffe040c

व्योम __init plat_early_device_setup(व्योम)
अणु
	/* enable CMT घड़ी */
	__raw_ग_लिखोb(__raw_पढ़ोb(STBCR4) & ~0x04, STBCR4);

	/* enable MTU2 घड़ी */
	__raw_ग_लिखोb(__raw_पढ़ोb(STBCR3) & ~0x20, STBCR3);

	sh_early_platक्रमm_add_devices(sh7203_early_devices,
				   ARRAY_SIZE(sh7203_early_devices));
पूर्ण
