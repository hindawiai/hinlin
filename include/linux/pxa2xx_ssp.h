<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2003 Russell King, All Rights Reserved.
 *
 * This driver supports the following PXA CPU/SSP ports:-
 *
 *       PXA250     SSP
 *       PXA255     SSP, NSSP
 *       PXA26x     SSP, NSSP, ASSP
 *       PXA27x     SSP1, SSP2, SSP3
 *       PXA3xx     SSP1, SSP2, SSP3, SSP4
 */

#अगर_अघोषित __LINUX_SSP_H
#घोषणा __LINUX_SSP_H

#समावेश <linux/bits.h>
#समावेश <linux/compiler_types.h>
#समावेश <linux/पन.स>
#समावेश <linux/kconfig.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>

काष्ठा clk;
काष्ठा device;
काष्ठा device_node;

/*
 * SSP Serial Port Registers
 * PXA250, PXA255, PXA26x and PXA27x SSP controllers are all slightly dअगरferent.
 * PXA255, PXA26x and PXA27x have extra ports, रेजिस्टरs and bits.
 */

#घोषणा SSCR0		(0x00)  /* SSP Control Register 0 */
#घोषणा SSCR1		(0x04)  /* SSP Control Register 1 */
#घोषणा SSSR		(0x08)  /* SSP Status Register */
#घोषणा SSITR		(0x0C)  /* SSP Interrupt Test Register */
#घोषणा SSDR		(0x10)  /* SSP Data Write/Data Read Register */

#घोषणा SSTO		(0x28)  /* SSP Time Out Register */
#घोषणा DDS_RATE	(0x28)  /* SSP DDS Clock Rate Register (Intel Quark) */
#घोषणा SSPSP		(0x2C)  /* SSP Programmable Serial Protocol */
#घोषणा SSTSA		(0x30)  /* SSP Tx Timeslot Active */
#घोषणा SSRSA		(0x34)  /* SSP Rx Timeslot Active */
#घोषणा SSTSS		(0x38)  /* SSP Timeslot Status */
#घोषणा SSACD		(0x3C)  /* SSP Audio Clock Divider */
#घोषणा SSACDD		(0x40)	/* SSP Audio Clock Dither Divider */

/* Common PXA2xx bits first */
#घोषणा SSCR0_DSS	GENMASK(3, 0)	/* Data Size Select (mask) */
#घोषणा SSCR0_DataSize(x)  ((x) - 1)	/* Data Size Select [4..16] */
#घोषणा SSCR0_FRF	GENMASK(5, 4)	/* FRame Format (mask) */
#घोषणा SSCR0_Motorola	(0x0 << 4)	/* Motorola's Serial Peripheral Interface (SPI) */
#घोषणा SSCR0_TI	(0x1 << 4)	/* Texas Instruments' Synchronous Serial Protocol (SSP) */
#घोषणा SSCR0_National	(0x2 << 4)	/* National Microwire */
#घोषणा SSCR0_ECS	BIT(6)		/* External घड़ी select */
#घोषणा SSCR0_SSE	BIT(7)		/* Synchronous Serial Port Enable */
#घोषणा SSCR0_SCR(x)	((x) << 8)	/* Serial Clock Rate (mask) */

/* PXA27x, PXA3xx */
#घोषणा SSCR0_EDSS	BIT(20)		/* Extended data size select */
#घोषणा SSCR0_NCS	BIT(21)		/* Network घड़ी select */
#घोषणा SSCR0_RIM	BIT(22)		/* Receive FIFO overrrun पूर्णांकerrupt mask */
#घोषणा SSCR0_TUM	BIT(23)		/* Transmit FIFO underrun पूर्णांकerrupt mask */
#घोषणा SSCR0_FRDC	GENMASK(26, 24)	/* Frame rate भागider control (mask) */
#घोषणा SSCR0_SlotsPerFrm(x) (((x) - 1) << 24)	/* Time slots per frame [1..8] */
#घोषणा SSCR0_FPCKE	BIT(29)		/* FIFO packing enable */
#घोषणा SSCR0_ACS	BIT(30)		/* Audio घड़ी select */
#घोषणा SSCR0_MOD	BIT(31)		/* Mode (normal or network) */

#घोषणा SSCR1_RIE	BIT(0)		/* Receive FIFO Interrupt Enable */
#घोषणा SSCR1_TIE	BIT(1)		/* Transmit FIFO Interrupt Enable */
#घोषणा SSCR1_LBM	BIT(2)		/* Loop-Back Mode */
#घोषणा SSCR1_SPO	BIT(3)		/* Motorola SPI SSPSCLK polarity setting */
#घोषणा SSCR1_SPH	BIT(4)		/* Motorola SPI SSPSCLK phase setting */
#घोषणा SSCR1_MWDS	BIT(5)		/* Microwire Transmit Data Size */

#घोषणा SSSR_ALT_FRM_MASK	GENMASK(1, 0)	/* Masks the SFRM संकेत number */
#घोषणा SSSR_TNF		BIT(2)		/* Transmit FIFO Not Full */
#घोषणा SSSR_RNE		BIT(3)		/* Receive FIFO Not Empty */
#घोषणा SSSR_BSY		BIT(4)		/* SSP Busy */
#घोषणा SSSR_TFS		BIT(5)		/* Transmit FIFO Service Request */
#घोषणा SSSR_RFS		BIT(6)		/* Receive FIFO Service Request */
#घोषणा SSSR_ROR		BIT(7)		/* Receive FIFO Overrun */

#घोषणा RX_THRESH_DFLT	8
#घोषणा TX_THRESH_DFLT	8

#घोषणा SSSR_TFL_MASK	GENMASK(11, 8)	/* Transmit FIFO Level mask */
#घोषणा SSSR_RFL_MASK	GENMASK(15, 12)	/* Receive FIFO Level mask */

#घोषणा SSCR1_TFT	GENMASK(9, 6)	/* Transmit FIFO Threshold (mask) */
#घोषणा SSCR1_TxTresh(x) (((x) - 1) << 6)	/* level [1..16] */
#घोषणा SSCR1_RFT	GENMASK(13, 10)	/* Receive FIFO Threshold (mask) */
#घोषणा SSCR1_RxTresh(x) (((x) - 1) << 10)	/* level [1..16] */

#घोषणा RX_THRESH_CE4100_DFLT	2
#घोषणा TX_THRESH_CE4100_DFLT	2

#घोषणा CE4100_SSSR_TFL_MASK	GENMASK(9, 8)	/* Transmit FIFO Level mask */
#घोषणा CE4100_SSSR_RFL_MASK	GENMASK(13, 12)	/* Receive FIFO Level mask */

#घोषणा CE4100_SSCR1_TFT	GENMASK(7, 6)	/* Transmit FIFO Threshold (mask) */
#घोषणा CE4100_SSCR1_TxTresh(x) (((x) - 1) << 6)	/* level [1..4] */
#घोषणा CE4100_SSCR1_RFT	GENMASK(11, 10)	/* Receive FIFO Threshold (mask) */
#घोषणा CE4100_SSCR1_RxTresh(x) (((x) - 1) << 10)	/* level [1..4] */

/* QUARK_X1000 SSCR0 bit definition */
#घोषणा QUARK_X1000_SSCR0_DSS		GENMASK(4, 0)	/* Data Size Select (mask) */
#घोषणा QUARK_X1000_SSCR0_DataSize(x)	((x) - 1)	/* Data Size Select [4..32] */
#घोषणा QUARK_X1000_SSCR0_FRF		GENMASK(6, 5)	/* FRame Format (mask) */
#घोषणा QUARK_X1000_SSCR0_Motorola	(0x0 << 5)	/* Motorola's Serial Peripheral Interface (SPI) */

#घोषणा RX_THRESH_QUARK_X1000_DFLT	1
#घोषणा TX_THRESH_QUARK_X1000_DFLT	16

#घोषणा QUARK_X1000_SSSR_TFL_MASK	GENMASK(12, 8)	/* Transmit FIFO Level mask */
#घोषणा QUARK_X1000_SSSR_RFL_MASK	GENMASK(17, 13)	/* Receive FIFO Level mask */

#घोषणा QUARK_X1000_SSCR1_TFT	GENMASK(10, 6)	/* Transmit FIFO Threshold (mask) */
#घोषणा QUARK_X1000_SSCR1_TxTresh(x) (((x) - 1) << 6)	/* level [1..32] */
#घोषणा QUARK_X1000_SSCR1_RFT	GENMASK(15, 11)	/* Receive FIFO Threshold (mask) */
#घोषणा QUARK_X1000_SSCR1_RxTresh(x) (((x) - 1) << 11)	/* level [1..32] */
#घोषणा QUARK_X1000_SSCR1_EFWR	BIT(16)		/* Enable FIFO Write/Read */
#घोषणा QUARK_X1000_SSCR1_STRF	BIT(17)		/* Select FIFO or EFWR */

/* extra bits in PXA255, PXA26x and PXA27x SSP ports */
#घोषणा SSCR0_TISSP		(1 << 4)	/* TI Sync Serial Protocol */
#घोषणा SSCR0_PSP		(3 << 4)	/* PSP - Programmable Serial Protocol */

#घोषणा SSCR1_EFWR		BIT(14)		/* Enable FIFO Write/Read */
#घोषणा SSCR1_STRF		BIT(15)		/* Select FIFO or EFWR */
#घोषणा SSCR1_IFS		BIT(16)		/* Invert Frame Signal */
#घोषणा SSCR1_PINTE		BIT(18)		/* Peripheral Trailing Byte Interrupt Enable */
#घोषणा SSCR1_TINTE		BIT(19)		/* Receiver Time-out Interrupt enable */
#घोषणा SSCR1_RSRE		BIT(20)		/* Receive Service Request Enable */
#घोषणा SSCR1_TSRE		BIT(21)		/* Transmit Service Request Enable */
#घोषणा SSCR1_TRAIL		BIT(22)		/* Trailing Byte */
#घोषणा SSCR1_RWOT		BIT(23)		/* Receive Without Transmit */
#घोषणा SSCR1_SFRMसूची		BIT(24)		/* Frame Direction */
#घोषणा SSCR1_SCLKसूची		BIT(25)		/* Serial Bit Rate Clock Direction */
#घोषणा SSCR1_ECRB		BIT(26)		/* Enable Clock request B */
#घोषणा SSCR1_ECRA		BIT(27)		/* Enable Clock Request A */
#घोषणा SSCR1_SCFR		BIT(28)		/* Slave Clock मुक्त Running */
#घोषणा SSCR1_EBCEI		BIT(29)		/* Enable Bit Count Error पूर्णांकerrupt */
#घोषणा SSCR1_TTE		BIT(30)		/* TXD Tristate Enable */
#घोषणा SSCR1_TTELP		BIT(31)		/* TXD Tristate Enable Last Phase */

#घोषणा SSSR_PINT		BIT(18)		/* Peripheral Trailing Byte Interrupt */
#घोषणा SSSR_TINT		BIT(19)		/* Receiver Time-out Interrupt */
#घोषणा SSSR_EOC		BIT(20)		/* End Of Chain */
#घोषणा SSSR_TUR		BIT(21)		/* Transmit FIFO Under Run */
#घोषणा SSSR_CSS		BIT(22)		/* Clock Synchronisation Status */
#घोषणा SSSR_BCE		BIT(23)		/* Bit Count Error */

#घोषणा SSPSP_SCMODE(x)		((x) << 0)	/* Serial Bit Rate Clock Mode */
#घोषणा SSPSP_SFRMP		BIT(2)		/* Serial Frame Polarity */
#घोषणा SSPSP_ETDS		BIT(3)		/* End of Transfer data State */
#घोषणा SSPSP_STRTDLY(x)	((x) << 4)	/* Start Delay */
#घोषणा SSPSP_DMYSTRT(x)	((x) << 7)	/* Dummy Start */
#घोषणा SSPSP_SFRMDLY(x)	((x) << 9)	/* Serial Frame Delay */
#घोषणा SSPSP_SFRMWDTH(x)	((x) << 16)	/* Serial Frame Width */
#घोषणा SSPSP_DMYSTOP(x)	((x) << 23)	/* Dummy Stop */
#घोषणा SSPSP_FSRT		BIT(25)		/* Frame Sync Relative Timing */

/* PXA3xx */
#घोषणा SSPSP_EDMYSTRT(x)	((x) << 26)     /* Extended Dummy Start */
#घोषणा SSPSP_EDMYSTOP(x)	((x) << 28)     /* Extended Dummy Stop */
#घोषणा SSPSP_TIMING_MASK	(0x7f8001f0)

#घोषणा SSACD_ACDS(x)		((x) << 0)	/* Audio घड़ी भागider select */
#घोषणा SSACD_ACDS_1		(0)
#घोषणा SSACD_ACDS_2		(1)
#घोषणा SSACD_ACDS_4		(2)
#घोषणा SSACD_ACDS_8		(3)
#घोषणा SSACD_ACDS_16		(4)
#घोषणा SSACD_ACDS_32		(5)
#घोषणा SSACD_SCDB		BIT(3)		/* SSPSYSCLK Divider Bypass */
#घोषणा SSACD_SCDB_4X		(0)
#घोषणा SSACD_SCDB_1X		(1)
#घोषणा SSACD_ACPS(x)		((x) << 4)	/* Audio घड़ी PLL select */
#घोषणा SSACD_SCDX8		BIT(7)		/* SYSCLK भागision ratio select */

/* LPSS SSP */
#घोषणा SSITF			0x44		/* TX FIFO trigger level */
#घोषणा SSITF_TxHiThresh(x)	(((x) - 1) << 0)
#घोषणा SSITF_TxLoThresh(x)	(((x) - 1) << 8)

#घोषणा SSIRF			0x48		/* RX FIFO trigger level */
#घोषणा SSIRF_RxThresh(x)	((x) - 1)

/* LPT/WPT SSP */
#घोषणा SSCR2		(0x40)	/* SSP Command / Status 2 */
#घोषणा SSPSP2		(0x44)	/* SSP Programmable Serial Protocol 2 */

क्रमागत pxa_ssp_type अणु
	SSP_UNDEFINED = 0,
	PXA25x_SSP,  /* pxa 210, 250, 255, 26x */
	PXA25x_NSSP, /* pxa 255, 26x (including ASSP) */
	PXA27x_SSP,
	PXA3xx_SSP,
	PXA168_SSP,
	MMP2_SSP,
	PXA910_SSP,
	CE4100_SSP,
	QUARK_X1000_SSP,
	LPSS_LPT_SSP, /* Keep LPSS types sorted with lpss_platक्रमms[] */
	LPSS_BYT_SSP,
	LPSS_BSW_SSP,
	LPSS_SPT_SSP,
	LPSS_BXT_SSP,
	LPSS_CNL_SSP,
पूर्ण;

काष्ठा ssp_device अणु
	काष्ठा device	*dev;
	काष्ठा list_head	node;

	काष्ठा clk	*clk;
	व्योम __iomem	*mmio_base;
	अचिन्हित दीर्घ	phys_base;

	स्थिर अक्षर	*label;
	पूर्णांक		port_id;
	क्रमागत pxa_ssp_type type;
	पूर्णांक		use_count;
	पूर्णांक		irq;

	काष्ठा device_node	*of_node;
पूर्ण;

/**
 * pxa_ssp_ग_लिखो_reg - Write to a SSP रेजिस्टर
 *
 * @dev: SSP device to access
 * @reg: Register to ग_लिखो to
 * @val: Value to be written.
 */
अटल अंतरभूत व्योम pxa_ssp_ग_लिखो_reg(काष्ठा ssp_device *dev, u32 reg, u32 val)
अणु
	__raw_ग_लिखोl(val, dev->mmio_base + reg);
पूर्ण

/**
 * pxa_ssp_पढ़ो_reg - Read from a SSP रेजिस्टर
 *
 * @dev: SSP device to access
 * @reg: Register to पढ़ो from
 */
अटल अंतरभूत u32 pxa_ssp_पढ़ो_reg(काष्ठा ssp_device *dev, u32 reg)
अणु
	वापस __raw_पढ़ोl(dev->mmio_base + reg);
पूर्ण

#अगर IS_ENABLED(CONFIG_PXA_SSP)
काष्ठा ssp_device *pxa_ssp_request(पूर्णांक port, स्थिर अक्षर *label);
व्योम pxa_ssp_मुक्त(काष्ठा ssp_device *);
काष्ठा ssp_device *pxa_ssp_request_of(स्थिर काष्ठा device_node *of_node,
				      स्थिर अक्षर *label);
#अन्यथा
अटल अंतरभूत काष्ठा ssp_device *pxa_ssp_request(पूर्णांक port, स्थिर अक्षर *label)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा ssp_device *pxa_ssp_request_of(स्थिर काष्ठा device_node *n,
						    स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम pxa_ssp_मुक्त(काष्ठा ssp_device *ssp) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
