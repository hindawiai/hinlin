<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh4a/setup-sh7734.c
 *
 * SH7734 Setup
 *
 * Copyright (C) 2011,2012 Nobuhiro Iwamatsu <nobuhiro.iwamatsu.yj@renesas.com>
 * Copyright (C) 2011,2012 Renesas Solutions Corp.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/platक्रमm_early.h>
#समावेश <cpu/sh7734.h>

/* SCIF */
अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr          = SCSCR_REIE,
	.type           = PORT_SCIF,
	.regtype        = SCIx_SH4_SCIF_BRG_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xffe40000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x8c0)),
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
	.scscr          = SCSCR_REIE,
	.type           = PORT_SCIF,
	.regtype        = SCIx_SH4_SCIF_BRG_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर1_resources[] = अणु
	DEFINE_RES_MEM(0xffe41000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x8e0)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर1_device = अणु
	.name		= "sh-sci",
	.id		= 1,
	.resource	= scअगर1_resources,
	.num_resources	= ARRAY_SIZE(scअगर1_resources),
	.dev		= अणु
		.platक्रमm_data = &scअगर1_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर2_platक्रमm_data = अणु
	.scscr          = SCSCR_REIE,
	.type           = PORT_SCIF,
	.regtype        = SCIx_SH4_SCIF_BRG_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर2_resources[] = अणु
	DEFINE_RES_MEM(0xffe42000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x900)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर2_device = अणु
	.name		= "sh-sci",
	.id		= 2,
	.resource	= scअगर2_resources,
	.num_resources	= ARRAY_SIZE(scअगर2_resources),
	.dev		= अणु
		.platक्रमm_data = &scअगर2_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर3_platक्रमm_data = अणु
	.scscr          = SCSCR_REIE | SCSCR_TOIE,
	.type           = PORT_SCIF,
	.regtype        = SCIx_SH4_SCIF_BRG_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर3_resources[] = अणु
	DEFINE_RES_MEM(0xffe43000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x920)),
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
	.scscr          = SCSCR_REIE,
	.type           = PORT_SCIF,
	.regtype        = SCIx_SH4_SCIF_BRG_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर4_resources[] = अणु
	DEFINE_RES_MEM(0xffe44000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x940)),
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
	.scscr          = SCSCR_REIE,
	.type           = PORT_SCIF,
	.regtype	= SCIx_SH4_SCIF_BRG_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर5_resources[] = अणु
	DEFINE_RES_MEM(0xffe43000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x960)),
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

/* RTC */
अटल काष्ठा resource rtc_resources[] = अणु
	[0] = अणु
		.name	= "rtc",
		.start	= 0xFFFC5000,
		.end	= 0xFFFC5000 + 0x26 - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xC00),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_device = अणु
	.name		= "sh-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(rtc_resources),
	.resource	= rtc_resources,
पूर्ण;

/* I2C 0 */
अटल काष्ठा resource i2c0_resources[] = अणु
	[0] = अणु
		.name	= "IIC0",
		.start  = 0xFFC70000,
		.end    = 0xFFC7000A - 1,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0x860),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device i2c0_device = अणु
	.name           = "i2c-sh7734",
	.id             = 0,
	.num_resources  = ARRAY_SIZE(i2c0_resources),
	.resource       = i2c0_resources,
पूर्ण;

/* TMU */
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
	DEFINE_RES_IRQ(evt2irq(0x480)),
	DEFINE_RES_IRQ(evt2irq(0x4a0)),
	DEFINE_RES_IRQ(evt2irq(0x4c0)),
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
	DEFINE_RES_MEM(0xffd82000, 0x30),
	DEFINE_RES_IRQ(evt2irq(0x500)),
	DEFINE_RES_IRQ(evt2irq(0x520)),
	DEFINE_RES_IRQ(evt2irq(0x540)),
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

अटल काष्ठा platक्रमm_device *sh7734_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&scअगर3_device,
	&scअगर4_device,
	&scअगर5_device,
	&पंचांगu0_device,
	&पंचांगu1_device,
	&पंचांगu2_device,
	&rtc_device,
पूर्ण;

अटल काष्ठा platक्रमm_device *sh7734_early_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&scअगर3_device,
	&scअगर4_device,
	&scअगर5_device,
	&पंचांगu0_device,
	&पंचांगu1_device,
	&पंचांगu2_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(sh7734_early_devices,
		ARRAY_SIZE(sh7734_early_devices));
पूर्ण

#घोषणा GROUP 0
क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */

	IRL0_LLLL, IRL0_LLLH, IRL0_LLHL, IRL0_LLHH,
	IRL0_LHLL, IRL0_LHLH, IRL0_LHHL, IRL0_LHHH,
	IRL0_HLLL, IRL0_HLLH, IRL0_HLHL, IRL0_HLHH,
	IRL0_HHLL, IRL0_HHLH, IRL0_HHHL,

	IRQ0, IRQ1, IRQ2, IRQ3,
	DU,
	TMU00, TMU10, TMU20, TMU21,
	TMU30, TMU40, TMU50, TMU51,
	TMU60, TMU70, TMU80,
	RESET_WDT,
	USB,
	HUDI,
	SHDMAC,
	SSI0, SSI1,	SSI2, SSI3,
	VIN0,
	RGPVG,
	_2DG,
	MMC,
	HSPI,
	LBSCATA,
	I2C0,
	RCAN0,
	MIMLB,
	SCIF0, SCIF1, SCIF2, SCIF3, SCIF4, SCIF5,
	LBSCDMAC0, LBSCDMAC1, LBSCDMAC2,
	RCAN1,
	SDHI0, SDHI1,
	IEBUS,
	HPBDMAC0_3, HPBDMAC4_10, HPBDMAC11_18, HPBDMAC19_22, HPBDMAC23_25_27_28,
	RTC,
	VIN1,
	LCDC,
	SRC0, SRC1,
	GETHER,
	SDHI2,
	GPIO0_3, GPIO4_5,
	STIF0, STIF1,
	ADMAC,
	HIF,
	FLCTL,
	ADC,
	MTU2,
	RSPI,
	QSPI,
	HSCIF,
	VEU3F_VE3,

	/* Group */
	/* Mask */
	STIF_M,
	GPIO_M,
	HPBDMAC_M,
	LBSCDMAC_M,
	RCAN_M,
	SRC_M,
	SCIF_M,
	LCDC_M,
	_2DG_M,
	VIN_M,
	TMU_3_M,
	TMU_0_M,

	/* Priority */
	RCAN_P,
	LBSCDMAC_P,

	/* Common */
	SDHI,
	SSI,
	SPI,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_VECT(DU, 0x3E0),
	INTC_VECT(TMU00, 0x400),
	INTC_VECT(TMU10, 0x420),
	INTC_VECT(TMU20, 0x440),
	INTC_VECT(TMU30, 0x480),
	INTC_VECT(TMU40, 0x4A0),
	INTC_VECT(TMU50, 0x4C0),
	INTC_VECT(TMU51, 0x4E0),
	INTC_VECT(TMU60, 0x500),
	INTC_VECT(TMU70, 0x520),
	INTC_VECT(TMU80, 0x540),
	INTC_VECT(RESET_WDT, 0x560),
	INTC_VECT(USB, 0x580),
	INTC_VECT(HUDI, 0x600),
	INTC_VECT(SHDMAC, 0x620),
	INTC_VECT(SSI0, 0x6C0),
	INTC_VECT(SSI1, 0x6E0),
	INTC_VECT(SSI2, 0x700),
	INTC_VECT(SSI3, 0x720),
	INTC_VECT(VIN0, 0x740),
	INTC_VECT(RGPVG, 0x760),
	INTC_VECT(_2DG, 0x780),
	INTC_VECT(MMC, 0x7A0),
	INTC_VECT(HSPI, 0x7E0),
	INTC_VECT(LBSCATA, 0x840),
	INTC_VECT(I2C0, 0x860),
	INTC_VECT(RCAN0, 0x880),
	INTC_VECT(SCIF0, 0x8A0),
	INTC_VECT(SCIF1, 0x8C0),
	INTC_VECT(SCIF2, 0x900),
	INTC_VECT(SCIF3, 0x920),
	INTC_VECT(SCIF4, 0x940),
	INTC_VECT(SCIF5, 0x960),
	INTC_VECT(LBSCDMAC0, 0x9E0),
	INTC_VECT(LBSCDMAC1, 0xA00),
	INTC_VECT(LBSCDMAC2, 0xA20),
	INTC_VECT(RCAN1, 0xA60),
	INTC_VECT(SDHI0, 0xAE0),
	INTC_VECT(SDHI1, 0xB00),
	INTC_VECT(IEBUS, 0xB20),
	INTC_VECT(HPBDMAC0_3, 0xB60),
	INTC_VECT(HPBDMAC4_10, 0xB80),
	INTC_VECT(HPBDMAC11_18, 0xBA0),
	INTC_VECT(HPBDMAC19_22, 0xBC0),
	INTC_VECT(HPBDMAC23_25_27_28, 0xBE0),
	INTC_VECT(RTC, 0xC00),
	INTC_VECT(VIN1, 0xC20),
	INTC_VECT(LCDC, 0xC40),
	INTC_VECT(SRC0, 0xC60),
	INTC_VECT(SRC1, 0xC80),
	INTC_VECT(GETHER, 0xCA0),
	INTC_VECT(SDHI2, 0xCC0),
	INTC_VECT(GPIO0_3, 0xCE0),
	INTC_VECT(GPIO4_5, 0xD00),
	INTC_VECT(STIF0, 0xD20),
	INTC_VECT(STIF1, 0xD40),
	INTC_VECT(ADMAC, 0xDA0),
	INTC_VECT(HIF, 0xDC0),
	INTC_VECT(FLCTL, 0xDE0),
	INTC_VECT(ADC, 0xE00),
	INTC_VECT(MTU2, 0xE20),
	INTC_VECT(RSPI, 0xE40),
	INTC_VECT(QSPI, 0xE60),
	INTC_VECT(HSCIF, 0xFC0),
	INTC_VECT(VEU3F_VE3, 0xF40),
पूर्ण;

अटल काष्ठा पूर्णांकc_group groups[] __initdata = अणु
	/* Common */
	INTC_GROUP(SDHI, SDHI0, SDHI1, SDHI2),
	INTC_GROUP(SPI, HSPI, RSPI, QSPI),
	INTC_GROUP(SSI, SSI0, SSI1, SSI2, SSI3),

	/* Mask group */
	INTC_GROUP(STIF_M, STIF0, STIF1), /* 22 */
	INTC_GROUP(GPIO_M, GPIO0_3, GPIO4_5), /* 21 */
	INTC_GROUP(HPBDMAC_M, HPBDMAC0_3, HPBDMAC4_10, HPBDMAC11_18,
			HPBDMAC19_22, HPBDMAC23_25_27_28), /* 19 */
	INTC_GROUP(LBSCDMAC_M, LBSCDMAC0, LBSCDMAC1, LBSCDMAC2), /* 18 */
	INTC_GROUP(RCAN_M, RCAN0, RCAN1, IEBUS), /* 17 */
	INTC_GROUP(SRC_M, SRC0, SRC1), /* 16 */
	INTC_GROUP(SCIF_M, SCIF0, SCIF1, SCIF2, SCIF3, SCIF4, SCIF5,
			HSCIF), /* 14 */
	INTC_GROUP(LCDC_M, LCDC, MIMLB), /* 13 */
	INTC_GROUP(_2DG_M, _2DG, RGPVG), /* 12 */
	INTC_GROUP(VIN_M, VIN0, VIN1), /* 10 */
	INTC_GROUP(TMU_3_M, TMU30, TMU40, TMU50, TMU51,
			TMU60, TMU60, TMU70, TMU80), /* 2 */
	INTC_GROUP(TMU_0_M, TMU00, TMU10, TMU20, TMU21), /* 1 */

	/* Priority group*/
	INTC_GROUP(RCAN_P, RCAN0, RCAN1), /* INT2PRI5 */
	INTC_GROUP(LBSCDMAC_P, LBSCDMAC0, LBSCDMAC1), /* INT2PRI5 */
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xFF804040, 0xFF804044, 32, /* INT2MSKRG / INT2MSKCR */
	  अणु 0,
		VEU3F_VE3,
		SDHI, /* SDHI 0-2 */
		ADMAC,
		FLCTL,
		RESET_WDT,
		HIF,
		ADC,
		MTU2,
		STIF_M, /* STIF 0,1 */
		GPIO_M, /* GPIO 0-5*/
		GETHER,
		HPBDMAC_M, /* HPBDMAC 0_3 - 23_25_27_28 */
		LBSCDMAC_M, /* LBSCDMAC 0 - 2 */
		RCAN_M, /* RCAN, IEBUS */
		SRC_M,	/* SRC 0,1 */
		LBSCATA,
		SCIF_M, /* SCIF 0-5, HSCIF */
		LCDC_M, /* LCDC, MIMLB */
		_2DG_M,	/* 2DG, RGPVG */
		SPI, /* HSPI, RSPI, QSPI */
		VIN_M,	/* VIN0, 1 */
		SSI,	/* SSI 0-3 */
		USB,
		SHDMAC,
		HUDI,
		MMC,
		RTC,
		I2C0, /* I2C */ /* I2C 0, 1*/
		TMU_3_M, /* TMU30 - TMU80 */
		TMU_0_M, /* TMU00 - TMU21 */
		DU पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xFF804000, 0, 32, 8, /* INT2PRI0 */
		अणु DU, TMU00, TMU10, TMU20 पूर्ण पूर्ण,
	अणु 0xFF804004, 0, 32, 8, /* INT2PRI1 */
		अणु TMU30, TMU60, RTC, SDHI पूर्ण पूर्ण,
	अणु 0xFF804008, 0, 32, 8, /* INT2PRI2 */
		अणु HUDI, SHDMAC, USB, SSI पूर्ण पूर्ण,
	अणु 0xFF80400C, 0, 32, 8, /* INT2PRI3 */
		अणु VIN0, SPI, _2DG, LBSCATA पूर्ण पूर्ण,
	अणु 0xFF804010, 0, 32, 8, /* INT2PRI4 */
		अणु SCIF0, SCIF3, HSCIF, LCDC पूर्ण पूर्ण,
	अणु 0xFF804014, 0, 32, 8, /* INT2PRI5 */
		अणु RCAN_P, LBSCDMAC_P, LBSCDMAC2, MMC पूर्ण पूर्ण,
	अणु 0xFF804018, 0, 32, 8, /* INT2PRI6 */
		अणु HPBDMAC0_3, HPBDMAC4_10, HPBDMAC11_18, HPBDMAC19_22 पूर्ण पूर्ण,
	अणु 0xFF80401C, 0, 32, 8, /* INT2PRI7 */
		अणु HPBDMAC23_25_27_28, I2C0, SRC0, SRC1 पूर्ण पूर्ण,
	अणु 0xFF804020, 0, 32, 8, /* INT2PRI8 */
		अणु 0 /* ADIF */, VIN1, RESET_WDT, HIF पूर्ण पूर्ण,
	अणु 0xFF804024, 0, 32, 8, /* INT2PRI9 */
		अणु ADMAC, FLCTL, GPIO0_3, GPIO4_5 पूर्ण पूर्ण,
	अणु 0xFF804028, 0, 32, 8, /* INT2PRI10 */
		अणु STIF0, STIF1, VEU3F_VE3, GETHER पूर्ण पूर्ण,
	अणु 0xFF80402C, 0, 32, 8, /* INT2PRI11 */
		अणु MTU2, RGPVG, MIMLB, IEBUS पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh7734", vectors, groups,
	mask_रेजिस्टरs, prio_रेजिस्टरs, शून्य);

/* Support क्रम बाह्यal पूर्णांकerrupt pins in IRQ mode */

अटल काष्ठा पूर्णांकc_vect irq3210_vectors[] __initdata = अणु
	INTC_VECT(IRQ0, 0x240), INTC_VECT(IRQ1, 0x280),
	INTC_VECT(IRQ2, 0x2C0), INTC_VECT(IRQ3, 0x300),
पूर्ण;

अटल काष्ठा पूर्णांकc_sense_reg irq3210_sense_रेजिस्टरs[] __initdata = अणु
	अणु 0xFF80201C, 32, 2, /* ICR1 */
	अणु IRQ0, IRQ1, IRQ2, IRQ3, पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg irq3210_ack_रेजिस्टरs[] __initdata = अणु
	अणु 0xFF802024, 0, 32, /* INTREQ */
	अणु IRQ0, IRQ1, IRQ2, IRQ3, पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg irq3210_mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xFF802044, 0xFF802064, 32, /* INTMSK0 / INTMSKCLR0 */
	अणु IRQ0, IRQ1, IRQ2, IRQ3, पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg irq3210_prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xFF802010, 0, 32, 4, /* INTPRI */
	अणु IRQ0, IRQ1, IRQ2, IRQ3, पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC_ACK(पूर्णांकc_desc_irq3210, "sh7734-irq3210",
	irq3210_vectors, शून्य,
	irq3210_mask_रेजिस्टरs, irq3210_prio_रेजिस्टरs,
	irq3210_sense_रेजिस्टरs, irq3210_ack_रेजिस्टरs);

/* External पूर्णांकerrupt pins in IRL mode */

अटल काष्ठा पूर्णांकc_vect vectors_irl3210[] __initdata = अणु
	INTC_VECT(IRL0_LLLL, 0x200), INTC_VECT(IRL0_LLLH, 0x220),
	INTC_VECT(IRL0_LLHL, 0x240), INTC_VECT(IRL0_LLHH, 0x260),
	INTC_VECT(IRL0_LHLL, 0x280), INTC_VECT(IRL0_LHLH, 0x2a0),
	INTC_VECT(IRL0_LHHL, 0x2c0), INTC_VECT(IRL0_LHHH, 0x2e0),
	INTC_VECT(IRL0_HLLL, 0x300), INTC_VECT(IRL0_HLLH, 0x320),
	INTC_VECT(IRL0_HLHL, 0x340), INTC_VECT(IRL0_HLHH, 0x360),
	INTC_VECT(IRL0_HHLL, 0x380), INTC_VECT(IRL0_HHLH, 0x3a0),
	INTC_VECT(IRL0_HHHL, 0x3c0),
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_irl3210, "sh7734-irl3210",
	vectors_irl3210, शून्य, mask_रेजिस्टरs, शून्य, शून्य);

#घोषणा INTC_ICR0		0xFF802000
#घोषणा INTC_INTMSK0    0xFF802044
#घोषणा INTC_INTMSK1    0xFF802048
#घोषणा INTC_INTMSKCLR0 0xFF802064
#घोषणा INTC_INTMSKCLR1 0xFF802068

व्योम __init plat_irq_setup(व्योम)
अणु
	/* disable IRQ3-0 */
	__raw_ग_लिखोl(0xF0000000, INTC_INTMSK0);

	/* disable IRL3-0 */
	__raw_ग_लिखोl(0x80000000, INTC_INTMSK1);

	/* select IRL mode क्रम IRL3-0 */
	__raw_ग_लिखोl(__raw_पढ़ोl(INTC_ICR0) & ~0x00800000, INTC_ICR0);

	/* disable holding function, ie enable "SH-4 Mode (LVLMODE)" */
	__raw_ग_लिखोl(__raw_पढ़ोl(INTC_ICR0) | 0x00200000, INTC_ICR0);

	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
पूर्ण

व्योम __init plat_irq_setup_pins(पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल IRQ_MODE_IRQ3210:
		/* select IRQ mode क्रम IRL3-0 */
		__raw_ग_लिखोl(__raw_पढ़ोl(INTC_ICR0) | 0x00800000, INTC_ICR0);
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_irq3210);
		अवरोध;
	हाल IRQ_MODE_IRL3210:
		/* enable IRL0-3 but करोn't provide any masking */
		__raw_ग_लिखोl(0x80000000, INTC_INTMSKCLR1);
		__raw_ग_लिखोl(0xf0000000, INTC_INTMSKCLR0);
		अवरोध;
	हाल IRQ_MODE_IRL3210_MASK:
		/* enable IRL0-3 and mask using cpu पूर्णांकc controller */
		__raw_ग_लिखोl(0x80000000, INTC_INTMSKCLR0);
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_irl3210);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण
