<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OMAP3XXX L3 Interconnect Driver header
 *
 * Copyright (C) 2011 Texas Corporation
 *	Felipe Balbi <balbi@ti.com>
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 *	sriअक्षरan <r.sriअक्षरan@ti.com>
 */
#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_L3_INTERCONNECT_3XXX_H
#घोषणा __ARCH_ARM_MACH_OMAP2_L3_INTERCONNECT_3XXX_H

/* Register definitions. All 64-bit wide */
#घोषणा L3_COMPONENT			0x000
#घोषणा L3_CORE				0x018
#घोषणा L3_AGENT_CONTROL		0x020
#घोषणा L3_AGENT_STATUS			0x028
#घोषणा L3_ERROR_LOG			0x058

#घोषणा L3_ERROR_LOG_MULTI		(1 << 31)
#घोषणा L3_ERROR_LOG_SECONDARY		(1 << 30)

#घोषणा L3_ERROR_LOG_ADDR		0x060

/* Register definitions क्रम Sideband Interconnect */
#घोषणा L3_SI_CONTROL			0x020
#घोषणा L3_SI_FLAG_STATUS_0		0x510

अटल स्थिर u64 shअगरt = 1;

#घोषणा L3_STATUS_0_MPUIA_BRST		(shअगरt << 0)
#घोषणा L3_STATUS_0_MPUIA_RSP		(shअगरt << 1)
#घोषणा L3_STATUS_0_MPUIA_INBAND	(shअगरt << 2)
#घोषणा L3_STATUS_0_IVAIA_BRST		(shअगरt << 6)
#घोषणा L3_STATUS_0_IVAIA_RSP		(shअगरt << 7)
#घोषणा L3_STATUS_0_IVAIA_INBAND	(shअगरt << 8)
#घोषणा L3_STATUS_0_SGXIA_BRST		(shअगरt << 9)
#घोषणा L3_STATUS_0_SGXIA_RSP		(shअगरt << 10)
#घोषणा L3_STATUS_0_SGXIA_MERROR	(shअगरt << 11)
#घोषणा L3_STATUS_0_CAMIA_BRST		(shअगरt << 12)
#घोषणा L3_STATUS_0_CAMIA_RSP		(shअगरt << 13)
#घोषणा L3_STATUS_0_CAMIA_INBAND	(shअगरt << 14)
#घोषणा L3_STATUS_0_DISPIA_BRST		(shअगरt << 15)
#घोषणा L3_STATUS_0_DISPIA_RSP		(shअगरt << 16)
#घोषणा L3_STATUS_0_DMARDIA_BRST	(shअगरt << 18)
#घोषणा L3_STATUS_0_DMARDIA_RSP		(shअगरt << 19)
#घोषणा L3_STATUS_0_DMAWRIA_BRST	(shअगरt << 21)
#घोषणा L3_STATUS_0_DMAWRIA_RSP		(shअगरt << 22)
#घोषणा L3_STATUS_0_USBOTGIA_BRST	(shअगरt << 24)
#घोषणा L3_STATUS_0_USBOTGIA_RSP	(shअगरt << 25)
#घोषणा L3_STATUS_0_USBOTGIA_INBAND	(shअगरt << 26)
#घोषणा L3_STATUS_0_USBHOSTIA_BRST	(shअगरt << 27)
#घोषणा L3_STATUS_0_USBHOSTIA_INBAND	(shअगरt << 28)
#घोषणा L3_STATUS_0_SMSTA_REQ		(shअगरt << 48)
#घोषणा L3_STATUS_0_GPMCTA_REQ		(shअगरt << 49)
#घोषणा L3_STATUS_0_OCMRAMTA_REQ	(shअगरt << 50)
#घोषणा L3_STATUS_0_OCMROMTA_REQ	(shअगरt << 51)
#घोषणा L3_STATUS_0_IVATA_REQ		(shअगरt << 54)
#घोषणा L3_STATUS_0_SGXTA_REQ		(shअगरt << 55)
#घोषणा L3_STATUS_0_SGXTA_SERROR	(shअगरt << 56)
#घोषणा L3_STATUS_0_GPMCTA_SERROR	(shअगरt << 57)
#घोषणा L3_STATUS_0_L4CORETA_REQ	(shअगरt << 58)
#घोषणा L3_STATUS_0_L4PERTA_REQ		(shअगरt << 59)
#घोषणा L3_STATUS_0_L4EMUTA_REQ		(shअगरt << 60)
#घोषणा L3_STATUS_0_MAD2DTA_REQ		(shअगरt << 61)

#घोषणा L3_STATUS_0_TIMEOUT_MASK	(L3_STATUS_0_MPUIA_BRST		\
					| L3_STATUS_0_MPUIA_RSP		\
					| L3_STATUS_0_IVAIA_BRST	\
					| L3_STATUS_0_IVAIA_RSP		\
					| L3_STATUS_0_SGXIA_BRST	\
					| L3_STATUS_0_SGXIA_RSP		\
					| L3_STATUS_0_CAMIA_BRST	\
					| L3_STATUS_0_CAMIA_RSP		\
					| L3_STATUS_0_DISPIA_BRST	\
					| L3_STATUS_0_DISPIA_RSP	\
					| L3_STATUS_0_DMARDIA_BRST	\
					| L3_STATUS_0_DMARDIA_RSP	\
					| L3_STATUS_0_DMAWRIA_BRST	\
					| L3_STATUS_0_DMAWRIA_RSP	\
					| L3_STATUS_0_USBOTGIA_BRST	\
					| L3_STATUS_0_USBOTGIA_RSP	\
					| L3_STATUS_0_USBHOSTIA_BRST	\
					| L3_STATUS_0_SMSTA_REQ		\
					| L3_STATUS_0_GPMCTA_REQ	\
					| L3_STATUS_0_OCMRAMTA_REQ	\
					| L3_STATUS_0_OCMROMTA_REQ	\
					| L3_STATUS_0_IVATA_REQ		\
					| L3_STATUS_0_SGXTA_REQ		\
					| L3_STATUS_0_L4CORETA_REQ	\
					| L3_STATUS_0_L4PERTA_REQ	\
					| L3_STATUS_0_L4EMUTA_REQ	\
					| L3_STATUS_0_MAD2DTA_REQ)

#घोषणा L3_SI_FLAG_STATUS_1		0x530

#घोषणा L3_STATUS_1_MPU_DATAIA		(1 << 0)
#घोषणा L3_STATUS_1_DAPIA0		(1 << 3)
#घोषणा L3_STATUS_1_DAPIA1		(1 << 4)
#घोषणा L3_STATUS_1_IVAIA		(1 << 6)

#घोषणा L3_PM_ERROR_LOG			0x020
#घोषणा L3_PM_CONTROL			0x028
#घोषणा L3_PM_ERROR_CLEAR_SINGLE	0x030
#घोषणा L3_PM_ERROR_CLEAR_MULTI		0x038
#घोषणा L3_PM_REQ_INFO_PERMISSION(n)	(0x048 + (0x020 * n))
#घोषणा L3_PM_READ_PERMISSION(n)	(0x050 + (0x020 * n))
#घोषणा L3_PM_WRITE_PERMISSION(n)	(0x058 + (0x020 * n))
#घोषणा L3_PM_ADDR_MATCH(n)		(0x060 + (0x020 * n))

/* L3 error log bit fields. Common क्रम IA and TA */
#घोषणा L3_ERROR_LOG_CODE		24
#घोषणा L3_ERROR_LOG_INITID		8
#घोषणा L3_ERROR_LOG_CMD		0

/* L3 agent status bit fields. */
#घोषणा L3_AGENT_STATUS_CLEAR_IA	0x10000000
#घोषणा L3_AGENT_STATUS_CLEAR_TA	0x01000000

#घोषणा OMAP34xx_IRQ_L3_APP		10
#घोषणा L3_APPLICATION_ERROR		0x0
#घोषणा L3_DEBUG_ERROR			0x1

क्रमागत omap3_l3_initiator_id अणु
	/* LCD has 1 ID */
	OMAP_L3_LCD = 29,
	/* SAD2D has 1 ID */
	OMAP_L3_SAD2D = 28,
	/* MPU has 5 IDs */
	OMAP_L3_IA_MPU_SS_1 = 27,
	OMAP_L3_IA_MPU_SS_2 = 26,
	OMAP_L3_IA_MPU_SS_3 = 25,
	OMAP_L3_IA_MPU_SS_4 = 24,
	OMAP_L3_IA_MPU_SS_5 = 23,
	/* IVA2.2 SS has 3 IDs*/
	OMAP_L3_IA_IVA_SS_1 = 22,
	OMAP_L3_IA_IVA_SS_2 = 21,
	OMAP_L3_IA_IVA_SS_3 = 20,
	/* IVA 2.2 SS DMA has 6 IDS */
	OMAP_L3_IA_IVA_SS_DMA_1 = 19,
	OMAP_L3_IA_IVA_SS_DMA_2 = 18,
	OMAP_L3_IA_IVA_SS_DMA_3 = 17,
	OMAP_L3_IA_IVA_SS_DMA_4 = 16,
	OMAP_L3_IA_IVA_SS_DMA_5 = 15,
	OMAP_L3_IA_IVA_SS_DMA_6 = 14,
	/* SGX has 1 ID */
	OMAP_L3_IA_SGX = 13,
	/* CAM has 3 ID */
	OMAP_L3_IA_CAM_1 = 12,
	OMAP_L3_IA_CAM_2 = 11,
	OMAP_L3_IA_CAM_3 = 10,
	/* DAP has 1 ID */
	OMAP_L3_IA_DAP = 9,
	/* SDMA WR has 2 IDs */
	OMAP_L3_SDMA_WR_1 = 8,
	OMAP_L3_SDMA_WR_2 = 7,
	/* SDMA RD has 4 IDs */
	OMAP_L3_SDMA_RD_1 = 6,
	OMAP_L3_SDMA_RD_2 = 5,
	OMAP_L3_SDMA_RD_3 = 4,
	OMAP_L3_SDMA_RD_4 = 3,
	/* HSUSB OTG has 1 ID */
	OMAP_L3_USBOTG = 2,
	/* HSUSB HOST has 1 ID */
	OMAP_L3_USBHOST = 1,
पूर्ण;

क्रमागत omap3_l3_code अणु
	OMAP_L3_CODE_NOERROR = 0,
	OMAP_L3_CODE_UNSUP_CMD = 1,
	OMAP_L3_CODE_ADDR_HOLE = 2,
	OMAP_L3_CODE_PROTECT_VIOLATION = 3,
	OMAP_L3_CODE_IN_BAND_ERR = 4,
	/* codes 5 and 6 are reserved */
	OMAP_L3_CODE_REQ_TOUT_NOT_ACCEPT = 7,
	OMAP_L3_CODE_REQ_TOUT_NO_RESP = 8,
	/* codes 9 - 15 are also reserved */
पूर्ण;

काष्ठा omap3_l3 अणु
	काष्ठा device *dev;
	काष्ठा clk *ick;

	/* memory base*/
	व्योम __iomem *rt;

	पूर्णांक debug_irq;
	पूर्णांक app_irq;

	/* true when and inband functional error occurs */
	अचिन्हित inband:1;
पूर्ण;

/* offsets क्रम l3 agents in order with the Flag status रेजिस्टर */
अटल अचिन्हित पूर्णांक omap3_l3_app_bases[] = अणु
	/* MPU IA */
	0x1400,
	0x1400,
	0x1400,
	/* RESERVED */
	0,
	0,
	0,
	/* IVA 2.2 IA */
	0x1800,
	0x1800,
	0x1800,
	/* SGX IA */
	0x1c00,
	0x1c00,
	/* RESERVED */
	0,
	/* CAMERA IA */
	0x5800,
	0x5800,
	0x5800,
	/* DISPLAY IA */
	0x5400,
	0x5400,
	/* RESERVED */
	0,
	/*SDMA RD IA */
	0x4c00,
	0x4c00,
	/* RESERVED */
	0,
	/* SDMA WR IA */
	0x5000,
	0x5000,
	/* RESERVED */
	0,
	/* USB OTG IA */
	0x4400,
	0x4400,
	0x4400,
	/* USB HOST IA */
	0x4000,
	0x4000,
	/* RESERVED */
	0,
	0,
	0,
	0,
	/* SAD2D IA */
	0x3000,
	0x3000,
	0x3000,
	/* RESERVED */
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	/* SMA TA */
	0x2000,
	/* GPMC TA */
	0x2400,
	/* OCM RAM TA */
	0x2800,
	/* OCM ROM TA */
	0x2C00,
	/* L4 CORE TA */
	0x6800,
	/* L4 PER TA */
	0x6c00,
	/* IVA 2.2 TA */
	0x6000,
	/* SGX TA */
	0x6400,
	/* L4 EMU TA */
	0x7000,
	/* GPMC TA */
	0x2400,
	/* L4 CORE TA */
	0x6800,
	/* L4 PER TA */
	0x6c00,
	/* L4 EMU TA */
	0x7000,
	/* MAD2D TA */
	0x3400,
	/* RESERVED */
	0,
	0,
पूर्ण;

अटल अचिन्हित पूर्णांक omap3_l3_debug_bases[] = अणु
	/* MPU DATA IA */
	0x1400,
	/* RESERVED */
	0,
	0,
	/* DAP IA */
	0x5c00,
	0x5c00,
	/* RESERVED */
	0,
	/* IVA 2.2 IA */
	0x1800,
	/* REST RESERVED */
पूर्ण;

अटल u32 *omap3_l3_bases[] = अणु
	omap3_l3_app_bases,
	omap3_l3_debug_bases,
पूर्ण;

/*
 * REVISIT define __raw_पढ़ोll/__raw_ग_लिखोll here, but move them to
 * <यंत्र/पन.स> at some poपूर्णांक
 */
#घोषणा __raw_ग_लिखोll(v, a)	(__chk_io_ptr(a), \
				*(अस्थिर u64 __क्रमce *)(a) = (v))
#घोषणा __raw_पढ़ोll(a)		(__chk_io_ptr(a), \
				*(अस्थिर u64 __क्रमce *)(a))

#पूर्ण_अगर
