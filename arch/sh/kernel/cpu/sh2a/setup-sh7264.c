<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7264 Setup
 *
 * Copyright (C) 2012  Renesas Electronics Europe Ltd
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/usb/r8a66597.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/platक्रमm_early.h>

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */
	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7,
	PINT0, PINT1, PINT2, PINT3, PINT4, PINT5, PINT6, PINT7,

	DMAC0, DMAC1, DMAC2, DMAC3, DMAC4, DMAC5, DMAC6, DMAC7,
	DMAC8, DMAC9, DMAC10, DMAC11, DMAC12, DMAC13, DMAC14, DMAC15,
	USB, VDC3, CMT0, CMT1, BSC, WDT,
	MTU0_ABCD, MTU0_VEF, MTU1_AB, MTU1_VU, MTU2_AB, MTU2_VU,
	MTU3_ABCD, MTU3_TCI3V, MTU4_ABCD, MTU4_TCI4V,
	PWMT1, PWMT2, ADC_ADI,
	SSIF0, SSII1, SSII2, SSII3,
	RSPDIF,
	IIC30, IIC31, IIC32, IIC33,
	SCIF0_BRI, SCIF0_ERI, SCIF0_RXI, SCIF0_TXI,
	SCIF1_BRI, SCIF1_ERI, SCIF1_RXI, SCIF1_TXI,
	SCIF2_BRI, SCIF2_ERI, SCIF2_RXI, SCIF2_TXI,
	SCIF3_BRI, SCIF3_ERI, SCIF3_RXI, SCIF3_TXI,
	SCIF4_BRI, SCIF4_ERI, SCIF4_RXI, SCIF4_TXI,
	SCIF5_BRI, SCIF5_ERI, SCIF5_RXI, SCIF5_TXI,
	SCIF6_BRI, SCIF6_ERI, SCIF6_RXI, SCIF6_TXI,
	SCIF7_BRI, SCIF7_ERI, SCIF7_RXI, SCIF7_TXI,
	SIO_FIFO, RSPIC0, RSPIC1,
	RCAN0, RCAN1, IEBC, CD_ROMD,
	NFMC, SDHI, RTC,
	SRCC0, SRCC1, DCOMU, OFFI, IFEI,

	/* पूर्णांकerrupt groups */
	PINT, SCIF0, SCIF1, SCIF2, SCIF3, SCIF4, SCIF5, SCIF6, SCIF7,
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
	INTC_IRQ(DMAC8, 140), INTC_IRQ(DMAC8, 141),
	INTC_IRQ(DMAC9, 144), INTC_IRQ(DMAC9, 145),
	INTC_IRQ(DMAC10, 148), INTC_IRQ(DMAC10, 149),
	INTC_IRQ(DMAC11, 152), INTC_IRQ(DMAC11, 153),
	INTC_IRQ(DMAC12, 156), INTC_IRQ(DMAC12, 157),
	INTC_IRQ(DMAC13, 160), INTC_IRQ(DMAC13, 161),
	INTC_IRQ(DMAC14, 164), INTC_IRQ(DMAC14, 165),
	INTC_IRQ(DMAC15, 168), INTC_IRQ(DMAC15, 169),

	INTC_IRQ(USB, 170),
	INTC_IRQ(VDC3, 171), INTC_IRQ(VDC3, 172),
	INTC_IRQ(VDC3, 173), INTC_IRQ(VDC3, 174),
	INTC_IRQ(CMT0, 175), INTC_IRQ(CMT1, 176),
	INTC_IRQ(BSC, 177), INTC_IRQ(WDT, 178),

	INTC_IRQ(MTU0_ABCD, 179), INTC_IRQ(MTU0_ABCD, 180),
	INTC_IRQ(MTU0_ABCD, 181), INTC_IRQ(MTU0_ABCD, 182),
	INTC_IRQ(MTU0_VEF, 183),
	INTC_IRQ(MTU0_VEF, 184), INTC_IRQ(MTU0_VEF, 185),
	INTC_IRQ(MTU1_AB, 186), INTC_IRQ(MTU1_AB, 187),
	INTC_IRQ(MTU1_VU, 188), INTC_IRQ(MTU1_VU, 189),
	INTC_IRQ(MTU2_AB, 190), INTC_IRQ(MTU2_AB, 191),
	INTC_IRQ(MTU2_VU, 192), INTC_IRQ(MTU2_VU, 193),
	INTC_IRQ(MTU3_ABCD, 194), INTC_IRQ(MTU3_ABCD, 195),
	INTC_IRQ(MTU3_ABCD, 196), INTC_IRQ(MTU3_ABCD, 197),
	INTC_IRQ(MTU3_TCI3V, 198),
	INTC_IRQ(MTU4_ABCD, 199), INTC_IRQ(MTU4_ABCD, 200),
	INTC_IRQ(MTU4_ABCD, 201), INTC_IRQ(MTU4_ABCD, 202),
	INTC_IRQ(MTU4_TCI4V, 203),

	INTC_IRQ(PWMT1, 204), INTC_IRQ(PWMT2, 205),

	INTC_IRQ(ADC_ADI, 206),

	INTC_IRQ(SSIF0, 207), INTC_IRQ(SSIF0, 208),
	INTC_IRQ(SSIF0, 209),
	INTC_IRQ(SSII1, 210), INTC_IRQ(SSII1, 211),
	INTC_IRQ(SSII2, 212), INTC_IRQ(SSII2, 213),
	INTC_IRQ(SSII3, 214), INTC_IRQ(SSII3, 215),

	INTC_IRQ(RSPDIF, 216),

	INTC_IRQ(IIC30, 217), INTC_IRQ(IIC30, 218),
	INTC_IRQ(IIC30, 219), INTC_IRQ(IIC30, 220),
	INTC_IRQ(IIC30, 221),
	INTC_IRQ(IIC31, 222), INTC_IRQ(IIC31, 223),
	INTC_IRQ(IIC31, 224), INTC_IRQ(IIC31, 225),
	INTC_IRQ(IIC31, 226),
	INTC_IRQ(IIC32, 227), INTC_IRQ(IIC32, 228),
	INTC_IRQ(IIC32, 229), INTC_IRQ(IIC32, 230),
	INTC_IRQ(IIC32, 231),

	INTC_IRQ(SCIF0_BRI, 232), INTC_IRQ(SCIF0_ERI, 233),
	INTC_IRQ(SCIF0_RXI, 234), INTC_IRQ(SCIF0_TXI, 235),
	INTC_IRQ(SCIF1_BRI, 236), INTC_IRQ(SCIF1_ERI, 237),
	INTC_IRQ(SCIF1_RXI, 238), INTC_IRQ(SCIF1_TXI, 239),
	INTC_IRQ(SCIF2_BRI, 240), INTC_IRQ(SCIF2_ERI, 241),
	INTC_IRQ(SCIF2_RXI, 242), INTC_IRQ(SCIF2_TXI, 243),
	INTC_IRQ(SCIF3_BRI, 244), INTC_IRQ(SCIF3_ERI, 245),
	INTC_IRQ(SCIF3_RXI, 246), INTC_IRQ(SCIF3_TXI, 247),
	INTC_IRQ(SCIF4_BRI, 248), INTC_IRQ(SCIF4_ERI, 249),
	INTC_IRQ(SCIF4_RXI, 250), INTC_IRQ(SCIF4_TXI, 251),
	INTC_IRQ(SCIF5_BRI, 252), INTC_IRQ(SCIF5_ERI, 253),
	INTC_IRQ(SCIF5_RXI, 254), INTC_IRQ(SCIF5_TXI, 255),
	INTC_IRQ(SCIF6_BRI, 256), INTC_IRQ(SCIF6_ERI, 257),
	INTC_IRQ(SCIF6_RXI, 258), INTC_IRQ(SCIF6_TXI, 259),
	INTC_IRQ(SCIF7_BRI, 260), INTC_IRQ(SCIF7_ERI, 261),
	INTC_IRQ(SCIF7_RXI, 262), INTC_IRQ(SCIF7_TXI, 263),

	INTC_IRQ(SIO_FIFO, 264),

	INTC_IRQ(RSPIC0, 265), INTC_IRQ(RSPIC0, 266),
	INTC_IRQ(RSPIC0, 267),
	INTC_IRQ(RSPIC1, 268), INTC_IRQ(RSPIC1, 269),
	INTC_IRQ(RSPIC1, 270),

	INTC_IRQ(RCAN0, 271), INTC_IRQ(RCAN0, 272),
	INTC_IRQ(RCAN0, 273), INTC_IRQ(RCAN0, 274),
	INTC_IRQ(RCAN0, 275),
	INTC_IRQ(RCAN1, 276), INTC_IRQ(RCAN1, 277),
	INTC_IRQ(RCAN1, 278), INTC_IRQ(RCAN1, 279),
	INTC_IRQ(RCAN1, 280),

	INTC_IRQ(IEBC, 281),

	INTC_IRQ(CD_ROMD, 282), INTC_IRQ(CD_ROMD, 283),
	INTC_IRQ(CD_ROMD, 284), INTC_IRQ(CD_ROMD, 285),
	INTC_IRQ(CD_ROMD, 286), INTC_IRQ(CD_ROMD, 287),

	INTC_IRQ(NFMC, 288), INTC_IRQ(NFMC, 289),
	INTC_IRQ(NFMC, 290), INTC_IRQ(NFMC, 291),

	INTC_IRQ(SDHI, 292), INTC_IRQ(SDHI, 293),
	INTC_IRQ(SDHI, 294),

	INTC_IRQ(RTC, 296), INTC_IRQ(RTC, 297),
	INTC_IRQ(RTC, 298),

	INTC_IRQ(SRCC0, 299), INTC_IRQ(SRCC0, 300),
	INTC_IRQ(SRCC0, 301), INTC_IRQ(SRCC0, 302),
	INTC_IRQ(SRCC0, 303),
	INTC_IRQ(SRCC1, 304), INTC_IRQ(SRCC1, 305),
	INTC_IRQ(SRCC1, 306), INTC_IRQ(SRCC1, 307),
	INTC_IRQ(SRCC1, 308),

	INTC_IRQ(DCOMU, 310), INTC_IRQ(DCOMU, 311),
	INTC_IRQ(DCOMU, 312),
पूर्ण;

अटल काष्ठा पूर्णांकc_group groups[] __initdata = अणु
	INTC_GROUP(PINT, PINT0, PINT1, PINT2, PINT3,
		   PINT4, PINT5, PINT6, PINT7),
	INTC_GROUP(SCIF0, SCIF0_BRI, SCIF0_ERI, SCIF0_RXI, SCIF0_TXI),
	INTC_GROUP(SCIF1, SCIF1_BRI, SCIF1_ERI, SCIF1_RXI, SCIF1_TXI),
	INTC_GROUP(SCIF2, SCIF2_BRI, SCIF2_ERI, SCIF2_RXI, SCIF2_TXI),
	INTC_GROUP(SCIF3, SCIF3_BRI, SCIF3_ERI, SCIF3_RXI, SCIF3_TXI),
	INTC_GROUP(SCIF4, SCIF4_BRI, SCIF4_ERI, SCIF4_RXI, SCIF4_TXI),
	INTC_GROUP(SCIF5, SCIF5_BRI, SCIF5_ERI, SCIF5_RXI, SCIF5_TXI),
	INTC_GROUP(SCIF6, SCIF6_BRI, SCIF6_ERI, SCIF6_RXI, SCIF6_TXI),
	INTC_GROUP(SCIF7, SCIF7_BRI, SCIF7_ERI, SCIF7_RXI, SCIF7_TXI),
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xfffe0818, 0, 16, 4, /* IPR01 */ अणु IRQ0, IRQ1, IRQ2, IRQ3 पूर्ण पूर्ण,
	अणु 0xfffe081a, 0, 16, 4, /* IPR02 */ अणु IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
	अणु 0xfffe0820, 0, 16, 4, /* IPR05 */ अणु PINT, 0, 0, 0 पूर्ण पूर्ण,
	अणु 0xfffe0c00, 0, 16, 4, /* IPR06 */ अणु DMAC0,  DMAC1,  DMAC2,  DMAC3 पूर्ण पूर्ण,
	अणु 0xfffe0c02, 0, 16, 4, /* IPR07 */ अणु DMAC4,  DMAC5,  DMAC6,  DMAC7 पूर्ण पूर्ण,
	अणु 0xfffe0c04, 0, 16, 4, /* IPR08 */ अणु DMAC8,  DMAC9,
					      DMAC10, DMAC11 पूर्ण पूर्ण,
	अणु 0xfffe0c06, 0, 16, 4, /* IPR09 */ अणु DMAC12, DMAC13,
					      DMAC14, DMAC15 पूर्ण पूर्ण,
	अणु 0xfffe0c08, 0, 16, 4, /* IPR10 */ अणु USB, VDC3, CMT0, CMT1 पूर्ण पूर्ण,
	अणु 0xfffe0c0a, 0, 16, 4, /* IPR11 */ अणु BSC, WDT, MTU0_ABCD, MTU0_VEF पूर्ण पूर्ण,
	अणु 0xfffe0c0c, 0, 16, 4, /* IPR12 */ अणु MTU1_AB, MTU1_VU,
					      MTU2_AB, MTU2_VU पूर्ण पूर्ण,
	अणु 0xfffe0c0e, 0, 16, 4, /* IPR13 */ अणु MTU3_ABCD, MTU3_TCI3V,
					      MTU4_ABCD, MTU4_TCI4V पूर्ण पूर्ण,
	अणु 0xfffe0c10, 0, 16, 4, /* IPR14 */ अणु PWMT1, PWMT2, ADC_ADI, 0 पूर्ण पूर्ण,
	अणु 0xfffe0c12, 0, 16, 4, /* IPR15 */ अणु SSIF0, SSII1, SSII2, SSII3 पूर्ण पूर्ण,
	अणु 0xfffe0c14, 0, 16, 4, /* IPR16 */ अणु RSPDIF, IIC30, IIC31, IIC32 पूर्ण पूर्ण,
	अणु 0xfffe0c16, 0, 16, 4, /* IPR17 */ अणु SCIF0, SCIF1, SCIF2, SCIF3 पूर्ण पूर्ण,
	अणु 0xfffe0c18, 0, 16, 4, /* IPR18 */ अणु SCIF4, SCIF5, SCIF6, SCIF7 पूर्ण पूर्ण,
	अणु 0xfffe0c1a, 0, 16, 4, /* IPR19 */ अणु SIO_FIFO, 0, RSPIC0, RSPIC1, पूर्ण पूर्ण,
	अणु 0xfffe0c1c, 0, 16, 4, /* IPR20 */ अणु RCAN0, RCAN1, IEBC, CD_ROMD पूर्ण पूर्ण,
	अणु 0xfffe0c1e, 0, 16, 4, /* IPR21 */ अणु NFMC, SDHI, RTC, 0 पूर्ण पूर्ण,
	अणु 0xfffe0c20, 0, 16, 4, /* IPR22 */ अणु SRCC0, SRCC1, 0, DCOMU पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xfffe0808, 0, 16, /* PINTER */
	  अणु 0, 0, 0, 0, 0, 0, 0, 0,
	    PINT7, PINT6, PINT5, PINT4, PINT3, PINT2, PINT1, PINT0 पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh7264", vectors, groups,
			 mask_रेजिस्टरs, prio_रेजिस्टरs, शून्य);

अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
	.regtype	= SCIx_SH2_SCIF_FIFODATA_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xfffe8000, 0x100),
	DEFINE_RES_IRQ(233),
	DEFINE_RES_IRQ(234),
	DEFINE_RES_IRQ(235),
	DEFINE_RES_IRQ(232),
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
	DEFINE_RES_IRQ(237),
	DEFINE_RES_IRQ(238),
	DEFINE_RES_IRQ(239),
	DEFINE_RES_IRQ(236),
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
	DEFINE_RES_IRQ(241),
	DEFINE_RES_IRQ(242),
	DEFINE_RES_IRQ(243),
	DEFINE_RES_IRQ(240),
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
	DEFINE_RES_IRQ(245),
	DEFINE_RES_IRQ(246),
	DEFINE_RES_IRQ(247),
	DEFINE_RES_IRQ(244),
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
	.regtype	= SCIx_SH2_SCIF_FIFODATA_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर4_resources[] = अणु
	DEFINE_RES_MEM(0xfffea000, 0x100),
	DEFINE_RES_IRQ(249),
	DEFINE_RES_IRQ(250),
	DEFINE_RES_IRQ(251),
	DEFINE_RES_IRQ(248),
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
	.regtype	= SCIx_SH2_SCIF_FIFODATA_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर5_resources[] = अणु
	DEFINE_RES_MEM(0xfffea800, 0x100),
	DEFINE_RES_IRQ(253),
	DEFINE_RES_IRQ(254),
	DEFINE_RES_IRQ(255),
	DEFINE_RES_IRQ(252),
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
	.regtype	= SCIx_SH2_SCIF_FIFODATA_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर6_resources[] = अणु
	DEFINE_RES_MEM(0xfffeb000, 0x100),
	DEFINE_RES_IRQ(257),
	DEFINE_RES_IRQ(258),
	DEFINE_RES_IRQ(259),
	DEFINE_RES_IRQ(256),
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
	.regtype	= SCIx_SH2_SCIF_FIFODATA_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर7_resources[] = अणु
	DEFINE_RES_MEM(0xfffeb800, 0x100),
	DEFINE_RES_IRQ(261),
	DEFINE_RES_IRQ(262),
	DEFINE_RES_IRQ(263),
	DEFINE_RES_IRQ(260),
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

अटल काष्ठा sh_समयr_config cmt_platक्रमm_data = अणु
	.channels_mask = 3,
पूर्ण;

अटल काष्ठा resource cmt_resources[] = अणु
	DEFINE_RES_MEM(0xfffec000, 0x10),
	DEFINE_RES_IRQ(175),
	DEFINE_RES_IRQ(176),
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
	DEFINE_RES_IRQ_NAMED(179, "tgi0a"),
	DEFINE_RES_IRQ_NAMED(186, "tgi1a"),
पूर्ण;

अटल काष्ठा platक्रमm_device mtu2_device = अणु
	.name		= "sh-mtu2",
	.id		= -1,
	.resource	= mtu2_resources,
	.num_resources	= ARRAY_SIZE(mtu2_resources),
पूर्ण;

अटल काष्ठा resource rtc_resources[] = अणु
	[0] = अणु
		.start	= 0xfffe6000,
		.end	= 0xfffe6000 + 0x30 - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		/* Shared Period/Carry/Alarm IRQ */
		.start	= 296,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_device = अणु
	.name		= "sh-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(rtc_resources),
	.resource	= rtc_resources,
पूर्ण;

/* USB Host */
अटल व्योम usb_port_घातer(पूर्णांक port, पूर्णांक घातer)
अणु
	__raw_ग_लिखोw(0x200 , 0xffffc0c2) ; /* Initialise UACS25 */
पूर्ण

अटल काष्ठा r8a66597_platdata r8a66597_data = अणु
	.on_chip = 1,
	.endian = 1,
	.port_घातer = usb_port_घातer,
पूर्ण;

अटल काष्ठा resource r8a66597_usb_host_resources[] = अणु
	[0] = अणु
		.start	= 0xffffc000,
		.end	= 0xffffc0e4,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= 170,
		.end	= 170,
		.flags	= IORESOURCE_IRQ | IRQF_TRIGGER_LOW,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device r8a66597_usb_host_device = अणु
	.name		= "r8a66597_hcd",
	.id		= 0,
	.dev = अणु
		.dma_mask		= शून्य,         /*  not use dma */
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &r8a66597_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(r8a66597_usb_host_resources),
	.resource	= r8a66597_usb_host_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *sh7264_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&scअगर3_device,
	&scअगर4_device,
	&scअगर5_device,
	&scअगर6_device,
	&scअगर7_device,
	&cmt_device,
	&mtu2_device,
	&rtc_device,
	&r8a66597_usb_host_device,
पूर्ण;

अटल पूर्णांक __init sh7264_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sh7264_devices,
				    ARRAY_SIZE(sh7264_devices));
पूर्ण
arch_initcall(sh7264_devices_setup);

व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
पूर्ण

अटल काष्ठा platक्रमm_device *sh7264_early_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&scअगर3_device,
	&scअगर4_device,
	&scअगर5_device,
	&scअगर6_device,
	&scअगर7_device,
	&cmt_device,
	&mtu2_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(sh7264_early_devices,
				   ARRAY_SIZE(sh7264_early_devices));
पूर्ण
