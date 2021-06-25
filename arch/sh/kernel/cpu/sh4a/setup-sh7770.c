<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7770 Setup
 *
 *  Copyright (C) 2006 - 2008  Paul Mundt
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/platक्रमm_early.h>

अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE | SCSCR_TOIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xff923000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x9a0)),
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
	.scscr		= SCSCR_REIE | SCSCR_TOIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर1_resources[] = अणु
	DEFINE_RES_MEM(0xff924000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x9c0)),
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
	.scscr		= SCSCR_REIE | SCSCR_TOIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर2_resources[] = अणु
	DEFINE_RES_MEM(0xff925000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x9e0)),
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
	.scscr		= SCSCR_REIE | SCSCR_TOIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर3_resources[] = अणु
	DEFINE_RES_MEM(0xff926000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xa00)),
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
	.scscr		= SCSCR_REIE | SCSCR_TOIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर4_resources[] = अणु
	DEFINE_RES_MEM(0xff927000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xa20)),
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
	.scscr		= SCSCR_REIE | SCSCR_TOIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर5_resources[] = अणु
	DEFINE_RES_MEM(0xff928000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xa40)),
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
	.scscr		= SCSCR_REIE | SCSCR_TOIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर6_resources[] = अणु
	DEFINE_RES_MEM(0xff929000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xa60)),
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
	.scscr		= SCSCR_REIE | SCSCR_TOIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर7_resources[] = अणु
	DEFINE_RES_MEM(0xff92a000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xa80)),
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

अटल काष्ठा plat_sci_port scअगर8_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE | SCSCR_TOIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर8_resources[] = अणु
	DEFINE_RES_MEM(0xff92b000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xaa0)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर8_device = अणु
	.name		= "sh-sci",
	.id		= 8,
	.resource	= scअगर8_resources,
	.num_resources	= ARRAY_SIZE(scअगर8_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर8_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर9_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE | SCSCR_TOIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर9_resources[] = अणु
	DEFINE_RES_MEM(0xff92c000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xac0)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर9_device = अणु
	.name		= "sh-sci",
	.id		= 9,
	.resource	= scअगर9_resources,
	.num_resources	= ARRAY_SIZE(scअगर9_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर9_platक्रमm_data,
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

अटल काष्ठा sh_समयr_config पंचांगu1_platक्रमm_data = अणु
	.channels_mask = 7,
पूर्ण;

अटल काष्ठा resource पंचांगu1_resources[] = अणु
	DEFINE_RES_MEM(0xffd81000, 0x30),
	DEFINE_RES_IRQ(evt2irq(0x460)),
	DEFINE_RES_IRQ(evt2irq(0x480)),
	DEFINE_RES_IRQ(evt2irq(0x4a0)),
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

अटल काष्ठा sh_समयr_config पंचांगu2_platक्रमm_data = अणु
	.channels_mask = 7,
पूर्ण;

अटल काष्ठा resource पंचांगu2_resources[] = अणु
	DEFINE_RES_MEM(0xffd82000, 0x2c),
	DEFINE_RES_IRQ(evt2irq(0x4c0)),
	DEFINE_RES_IRQ(evt2irq(0x4e0)),
	DEFINE_RES_IRQ(evt2irq(0x500)),
पूर्ण;

अटल काष्ठा platक्रमm_device पंचांगu2_device = अणु
	.name		= "sh-tmu",
	.id		= 2,
	.dev = अणु
		.platक्रमm_data	= &पंचांगu2_platक्रमm_data,
	पूर्ण,
	.resource	= पंचांगu2_resources,
	.num_resources	= ARRAY_SIZE(पंचांगu2_resources),
पूर्ण;

अटल काष्ठा platक्रमm_device *sh7770_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&scअगर3_device,
	&scअगर4_device,
	&scअगर5_device,
	&scअगर6_device,
	&scअगर7_device,
	&scअगर8_device,
	&scअगर9_device,
	&पंचांगu0_device,
	&पंचांगu1_device,
	&पंचांगu2_device,
पूर्ण;

अटल पूर्णांक __init sh7770_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sh7770_devices,
				    ARRAY_SIZE(sh7770_devices));
पूर्ण
arch_initcall(sh7770_devices_setup);

अटल काष्ठा platक्रमm_device *sh7770_early_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&scअगर3_device,
	&scअगर4_device,
	&scअगर5_device,
	&scअगर6_device,
	&scअगर7_device,
	&scअगर8_device,
	&scअगर9_device,
	&पंचांगu0_device,
	&पंचांगu1_device,
	&पंचांगu2_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(sh7770_early_devices,
				   ARRAY_SIZE(sh7770_early_devices));
पूर्ण

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */
	IRL_LLLL, IRL_LLLH, IRL_LLHL, IRL_LLHH,
	IRL_LHLL, IRL_LHLH, IRL_LHHL, IRL_LHHH,
	IRL_HLLL, IRL_HLLH, IRL_HLHL, IRL_HLHH,
	IRL_HHLL, IRL_HHLH, IRL_HHHL,

	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5,

	GPIO,
	TMU0, TMU1, TMU2, TMU2_TICPI,
	TMU3, TMU4, TMU5, TMU5_TICPI,
	TMU6, TMU7, TMU8,
	HAC, IPI, SPDIF, HUDI, I2C,
	DMAC0_DMINT0, DMAC0_DMINT1, DMAC0_DMINT2,
	I2S0, I2S1, I2S2, I2S3,
	SRC_RX, SRC_TX, SRC_SPDIF,
	DU, VIDEO_IN, REMOTE, YUV, USB, ATAPI, CAN, GPS, GFX2D,
	GFX3D_MBX, GFX3D_DMAC,
	EXBUS_ATA,
	SPI0, SPI1,
	SCIF089, SCIF1234, SCIF567,
	ADC,
	BBDMAC_0_3, BBDMAC_4_7, BBDMAC_8_10, BBDMAC_11_14,
	BBDMAC_15_18, BBDMAC_19_22, BBDMAC_23_26, BBDMAC_27,
	BBDMAC_28, BBDMAC_29, BBDMAC_30, BBDMAC_31,

	/* पूर्णांकerrupt groups */
	TMU, DMAC, I2S, SRC, GFX3D, SPI, SCIF, BBDMAC,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_VECT(GPIO, 0x3e0),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(TMU2_TICPI, 0x460),
	INTC_VECT(TMU3, 0x480), INTC_VECT(TMU4, 0x4a0),
	INTC_VECT(TMU5, 0x4c0), INTC_VECT(TMU5_TICPI, 0x4e0),
	INTC_VECT(TMU6, 0x500), INTC_VECT(TMU7, 0x520),
	INTC_VECT(TMU8, 0x540),
	INTC_VECT(HAC, 0x580), INTC_VECT(IPI, 0x5c0),
	INTC_VECT(SPDIF, 0x5e0),
	INTC_VECT(HUDI, 0x600), INTC_VECT(I2C, 0x620),
	INTC_VECT(DMAC0_DMINT0, 0x640), INTC_VECT(DMAC0_DMINT1, 0x660),
	INTC_VECT(DMAC0_DMINT2, 0x680),
	INTC_VECT(I2S0, 0x6a0), INTC_VECT(I2S1, 0x6c0),
	INTC_VECT(I2S2, 0x6e0), INTC_VECT(I2S3, 0x700),
	INTC_VECT(SRC_RX, 0x720), INTC_VECT(SRC_TX, 0x740),
	INTC_VECT(SRC_SPDIF, 0x760),
	INTC_VECT(DU, 0x780), INTC_VECT(VIDEO_IN, 0x7a0),
	INTC_VECT(REMOTE, 0x7c0), INTC_VECT(YUV, 0x7e0),
	INTC_VECT(USB, 0x840), INTC_VECT(ATAPI, 0x860),
	INTC_VECT(CAN, 0x880), INTC_VECT(GPS, 0x8a0),
	INTC_VECT(GFX2D, 0x8c0),
	INTC_VECT(GFX3D_MBX, 0x900), INTC_VECT(GFX3D_DMAC, 0x920),
	INTC_VECT(EXBUS_ATA, 0x940),
	INTC_VECT(SPI0, 0x960), INTC_VECT(SPI1, 0x980),
	INTC_VECT(SCIF089, 0x9a0), INTC_VECT(SCIF1234, 0x9c0),
	INTC_VECT(SCIF1234, 0x9e0), INTC_VECT(SCIF1234, 0xa00),
	INTC_VECT(SCIF1234, 0xa20), INTC_VECT(SCIF567, 0xa40),
	INTC_VECT(SCIF567, 0xa60), INTC_VECT(SCIF567, 0xa80),
	INTC_VECT(SCIF089, 0xaa0), INTC_VECT(SCIF089, 0xac0),
	INTC_VECT(ADC, 0xb20),
	INTC_VECT(BBDMAC_0_3, 0xba0), INTC_VECT(BBDMAC_0_3, 0xbc0),
	INTC_VECT(BBDMAC_0_3, 0xbe0), INTC_VECT(BBDMAC_0_3, 0xc00),
	INTC_VECT(BBDMAC_4_7, 0xc20), INTC_VECT(BBDMAC_4_7, 0xc40),
	INTC_VECT(BBDMAC_4_7, 0xc60), INTC_VECT(BBDMAC_4_7, 0xc80),
	INTC_VECT(BBDMAC_8_10, 0xca0), INTC_VECT(BBDMAC_8_10, 0xcc0),
	INTC_VECT(BBDMAC_8_10, 0xce0), INTC_VECT(BBDMAC_11_14, 0xd00),
	INTC_VECT(BBDMAC_11_14, 0xd20), INTC_VECT(BBDMAC_11_14, 0xd40),
	INTC_VECT(BBDMAC_11_14, 0xd60), INTC_VECT(BBDMAC_15_18, 0xd80),
	INTC_VECT(BBDMAC_15_18, 0xda0), INTC_VECT(BBDMAC_15_18, 0xdc0),
	INTC_VECT(BBDMAC_15_18, 0xde0), INTC_VECT(BBDMAC_19_22, 0xe00),
	INTC_VECT(BBDMAC_19_22, 0xe20), INTC_VECT(BBDMAC_19_22, 0xe40),
	INTC_VECT(BBDMAC_19_22, 0xe60), INTC_VECT(BBDMAC_23_26, 0xe80),
	INTC_VECT(BBDMAC_23_26, 0xea0), INTC_VECT(BBDMAC_23_26, 0xec0),
	INTC_VECT(BBDMAC_23_26, 0xee0), INTC_VECT(BBDMAC_27, 0xf00),
	INTC_VECT(BBDMAC_28, 0xf20), INTC_VECT(BBDMAC_29, 0xf40),
	INTC_VECT(BBDMAC_30, 0xf60), INTC_VECT(BBDMAC_31, 0xf80),
पूर्ण;

अटल काष्ठा पूर्णांकc_group groups[] __initdata = अणु
	INTC_GROUP(TMU, TMU0, TMU1, TMU2, TMU2_TICPI, TMU3, TMU4, TMU5,
		   TMU5_TICPI, TMU6, TMU7, TMU8),
	INTC_GROUP(DMAC, DMAC0_DMINT0, DMAC0_DMINT1, DMAC0_DMINT2),
	INTC_GROUP(I2S, I2S0, I2S1, I2S2, I2S3),
	INTC_GROUP(SRC, SRC_RX, SRC_TX, SRC_SPDIF),
	INTC_GROUP(GFX3D, GFX3D_MBX, GFX3D_DMAC),
	INTC_GROUP(SPI, SPI0, SPI1),
	INTC_GROUP(SCIF, SCIF089, SCIF1234, SCIF567),
	INTC_GROUP(BBDMAC,
		   BBDMAC_0_3, BBDMAC_4_7, BBDMAC_8_10, BBDMAC_11_14,
		   BBDMAC_15_18, BBDMAC_19_22, BBDMAC_23_26, BBDMAC_27,
		   BBDMAC_28, BBDMAC_29, BBDMAC_30, BBDMAC_31),
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xffe00040, 0xffe00044, 32, /* INT2MSKR / INT2MSKCR */
	  अणु 0, BBDMAC, ADC, SCIF, SPI, EXBUS_ATA, GFX3D, GFX2D,
	    GPS, CAN, ATAPI, USB, YUV, REMOTE, VIDEO_IN, DU, SRC, I2S,
	    DMAC, I2C, HUDI, SPDIF, IPI, HAC, TMU, GPIO पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xffe00000, 0, 32, 8, /* INT2PRI0 */ अणु GPIO, TMU0, 0, HAC पूर्ण पूर्ण,
	अणु 0xffe00004, 0, 32, 8, /* INT2PRI1 */ अणु IPI, SPDIF, HUDI, I2C पूर्ण पूर्ण,
	अणु 0xffe00008, 0, 32, 8, /* INT2PRI2 */ अणु DMAC, I2S, SRC, DU पूर्ण पूर्ण,
	अणु 0xffe0000c, 0, 32, 8, /* INT2PRI3 */ अणु VIDEO_IN, REMOTE, YUV, USB पूर्ण पूर्ण,
	अणु 0xffe00010, 0, 32, 8, /* INT2PRI4 */ अणु ATAPI, CAN, GPS, GFX2D पूर्ण पूर्ण,
	अणु 0xffe00014, 0, 32, 8, /* INT2PRI5 */ अणु 0, GFX3D, EXBUS_ATA, SPI पूर्ण पूर्ण,
	अणु 0xffe00018, 0, 32, 8, /* INT2PRI6 */ अणु SCIF1234, SCIF567, SCIF089 पूर्ण पूर्ण,
	अणु 0xffe0001c, 0, 32, 8, /* INT2PRI7 */ अणु ADC, 0, 0, BBDMAC_0_3 पूर्ण पूर्ण,
	अणु 0xffe00020, 0, 32, 8, /* INT2PRI8 */
	  अणु BBDMAC_4_7, BBDMAC_8_10, BBDMAC_11_14, BBDMAC_15_18 पूर्ण पूर्ण,
	अणु 0xffe00024, 0, 32, 8, /* INT2PRI9 */
	  अणु BBDMAC_19_22, BBDMAC_23_26, BBDMAC_27, BBDMAC_28 पूर्ण पूर्ण,
	अणु 0xffe00028, 0, 32, 8, /* INT2PRI10 */
	  अणु BBDMAC_29, BBDMAC_30, BBDMAC_31 पूर्ण पूर्ण,
	अणु 0xffe0002c, 0, 32, 8, /* INT2PRI11 */
	  अणु TMU1, TMU2, TMU2_TICPI, TMU3 पूर्ण पूर्ण,
	अणु 0xffe00030, 0, 32, 8, /* INT2PRI12 */
	  अणु TMU4, TMU5, TMU5_TICPI, TMU6 पूर्ण पूर्ण,
	अणु 0xffe00034, 0, 32, 8, /* INT2PRI13 */
	  अणु TMU7, TMU8 पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh7770", vectors, groups,
			 mask_रेजिस्टरs, prio_रेजिस्टरs, शून्य);

/* Support क्रम बाह्यal पूर्णांकerrupt pins in IRQ mode */
अटल काष्ठा पूर्णांकc_vect irq_vectors[] __initdata = अणु
	INTC_VECT(IRQ0, 0x240), INTC_VECT(IRQ1, 0x280),
	INTC_VECT(IRQ2, 0x2c0), INTC_VECT(IRQ3, 0x300),
	INTC_VECT(IRQ4, 0x340), INTC_VECT(IRQ5, 0x380),
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg irq_mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd00044, 0xffd00064, 32, /* INTMSK0 / INTMSKCLR0 */
	  अणु IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg irq_prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd00010, 0, 32, 4, /* INTPRI */ अणु IRQ0, IRQ1, IRQ2, IRQ3,
					       IRQ4, IRQ5, पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_sense_reg irq_sense_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd0001c, 32, 2, /* ICR1 */   अणु IRQ0, IRQ1, IRQ2, IRQ3,
					    IRQ4, IRQ5, पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_irq_desc, "sh7770-irq", irq_vectors,
			 शून्य, irq_mask_रेजिस्टरs, irq_prio_रेजिस्टरs,
			 irq_sense_रेजिस्टरs);

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

अटल DECLARE_INTC_DESC(पूर्णांकc_irl7654_desc, "sh7780-irl7654", irl_vectors,
			 शून्य, irl7654_mask_रेजिस्टरs, शून्य, शून्य);

अटल DECLARE_INTC_DESC(पूर्णांकc_irl3210_desc, "sh7780-irl3210", irl_vectors,
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

	/* select IRL mode क्रम IRL3-0 + IRL7-4 */
	__raw_ग_लिखोl(__raw_पढ़ोl(INTC_ICR0) & ~0x00c00000, INTC_ICR0);

	/* disable holding function, ie enable "SH-4 Mode" */
	__raw_ग_लिखोl(__raw_पढ़ोl(INTC_ICR0) | 0x00200000, INTC_ICR0);

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
