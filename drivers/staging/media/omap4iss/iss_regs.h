<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * TI OMAP4 ISS V4L2 Driver - Register defines
 *
 * Copyright (C) 2012 Texas Instruments.
 *
 * Author: Sergio Aguirre <sergio.a.aguirre@gmail.com>
 */

#अगर_अघोषित _OMAP4_ISS_REGS_H_
#घोषणा _OMAP4_ISS_REGS_H_

/* ISS */
#घोषणा ISS_HL_REVISION					0x0

#घोषणा ISS_HL_SYSCONFIG				0x10
#घोषणा ISS_HL_SYSCONFIG_IDLEMODE_SHIFT			2
#घोषणा ISS_HL_SYSCONFIG_IDLEMODE_FORCEIDLE		0x0
#घोषणा ISS_HL_SYSCONFIG_IDLEMODE_NOIDLE		0x1
#घोषणा ISS_HL_SYSCONFIG_IDLEMODE_SMARTIDLE		0x2
#घोषणा ISS_HL_SYSCONFIG_SOFTRESET			BIT(0)

#घोषणा ISS_HL_IRQSTATUS_RAW(i)				(0x20 + (0x10 * (i)))
#घोषणा ISS_HL_IRQSTATUS(i)				(0x24 + (0x10 * (i)))
#घोषणा ISS_HL_IRQENABLE_SET(i)				(0x28 + (0x10 * (i)))
#घोषणा ISS_HL_IRQENABLE_CLR(i)				(0x2c + (0x10 * (i)))

#घोषणा ISS_HL_IRQ_HS_VS			BIT(17)
#घोषणा ISS_HL_IRQ_SIMCOP(i)			BIT(12 + (i))
#घोषणा ISS_HL_IRQ_BTE				BIT(11)
#घोषणा ISS_HL_IRQ_CBUFF			BIT(10)
#घोषणा ISS_HL_IRQ_CCP2(i)			BIT((i) > 3 ? 16 : 14 + (i))
#घोषणा ISS_HL_IRQ_CSIB				BIT(5)
#घोषणा ISS_HL_IRQ_CSIA				BIT(4)
#घोषणा ISS_HL_IRQ_ISP(i)			BIT(i)

#घोषणा ISS_CTRL					0x80
#घोषणा ISS_CTRL_CLK_DIV_MASK				(3 << 4)
#घोषणा ISS_CTRL_INPUT_SEL_MASK				(3 << 2)
#घोषणा ISS_CTRL_INPUT_SEL_CSI2A			(0 << 2)
#घोषणा ISS_CTRL_INPUT_SEL_CSI2B			(1 << 2)
#घोषणा ISS_CTRL_SYNC_DETECT_VS_RAISING			(3 << 0)

#घोषणा ISS_CLKCTRL					0x84
#घोषणा ISS_CLKCTRL_VPORT2_CLK				BIT(30)
#घोषणा ISS_CLKCTRL_VPORT1_CLK				BIT(29)
#घोषणा ISS_CLKCTRL_VPORT0_CLK				BIT(28)
#घोषणा ISS_CLKCTRL_CCP2				BIT(4)
#घोषणा ISS_CLKCTRL_CSI2_B				BIT(3)
#घोषणा ISS_CLKCTRL_CSI2_A				BIT(2)
#घोषणा ISS_CLKCTRL_ISP					BIT(1)
#घोषणा ISS_CLKCTRL_SIMCOP				BIT(0)

#घोषणा ISS_CLKSTAT					0x88
#घोषणा ISS_CLKSTAT_VPORT2_CLK				BIT(30)
#घोषणा ISS_CLKSTAT_VPORT1_CLK				BIT(29)
#घोषणा ISS_CLKSTAT_VPORT0_CLK				BIT(28)
#घोषणा ISS_CLKSTAT_CCP2				BIT(4)
#घोषणा ISS_CLKSTAT_CSI2_B				BIT(3)
#घोषणा ISS_CLKSTAT_CSI2_A				BIT(2)
#घोषणा ISS_CLKSTAT_ISP					BIT(1)
#घोषणा ISS_CLKSTAT_SIMCOP				BIT(0)

#घोषणा ISS_PM_STATUS					0x8c
#घोषणा ISS_PM_STATUS_CBUFF_PM_MASK			(3 << 12)
#घोषणा ISS_PM_STATUS_BTE_PM_MASK			(3 << 10)
#घोषणा ISS_PM_STATUS_SIMCOP_PM_MASK			(3 << 8)
#घोषणा ISS_PM_STATUS_ISP_PM_MASK			(3 << 6)
#घोषणा ISS_PM_STATUS_CCP2_PM_MASK			(3 << 4)
#घोषणा ISS_PM_STATUS_CSI2_B_PM_MASK			(3 << 2)
#घोषणा ISS_PM_STATUS_CSI2_A_PM_MASK			(3 << 0)

#घोषणा REGISTER0					0x0
#घोषणा REGISTER0_HSCLOCKCONFIG				BIT(24)
#घोषणा REGISTER0_THS_TERM_MASK				(0xff << 8)
#घोषणा REGISTER0_THS_TERM_SHIFT			8
#घोषणा REGISTER0_THS_SETTLE_MASK			(0xff << 0)
#घोषणा REGISTER0_THS_SETTLE_SHIFT			0

#घोषणा REGISTER1					0x4
#घोषणा REGISTER1_RESET_DONE_CTRLCLK			BIT(29)
#घोषणा REGISTER1_CLOCK_MISS_DETECTOR_STATUS		BIT(25)
#घोषणा REGISTER1_TCLK_TERM_MASK			(0x3f << 18)
#घोषणा REGISTER1_TCLK_TERM_SHIFT			18
#घोषणा REGISTER1_DPHY_HS_SYNC_PATTERN_SHIFT		10
#घोषणा REGISTER1_CTRLCLK_DIV_FACTOR_MASK		(0x3 << 8)
#घोषणा REGISTER1_CTRLCLK_DIV_FACTOR_SHIFT		8
#घोषणा REGISTER1_TCLK_SETTLE_MASK			(0xff << 0)
#घोषणा REGISTER1_TCLK_SETTLE_SHIFT			0

#घोषणा REGISTER2					0x8

#घोषणा CSI2_SYSCONFIG					0x10
#घोषणा CSI2_SYSCONFIG_MSTANDBY_MODE_MASK		(3 << 12)
#घोषणा CSI2_SYSCONFIG_MSTANDBY_MODE_FORCE		(0 << 12)
#घोषणा CSI2_SYSCONFIG_MSTANDBY_MODE_NO			(1 << 12)
#घोषणा CSI2_SYSCONFIG_MSTANDBY_MODE_SMART		(2 << 12)
#घोषणा CSI2_SYSCONFIG_SOFT_RESET			(1 << 1)
#घोषणा CSI2_SYSCONFIG_AUTO_IDLE			(1 << 0)

#घोषणा CSI2_SYSSTATUS					0x14
#घोषणा CSI2_SYSSTATUS_RESET_DONE			BIT(0)

#घोषणा CSI2_IRQSTATUS					0x18
#घोषणा CSI2_IRQENABLE					0x1c

/* Shared bits across CSI2_IRQENABLE and IRQSTATUS */

#घोषणा CSI2_IRQ_OCP_ERR				BIT(14)
#घोषणा CSI2_IRQ_SHORT_PACKET				BIT(13)
#घोषणा CSI2_IRQ_ECC_CORRECTION				BIT(12)
#घोषणा CSI2_IRQ_ECC_NO_CORRECTION			BIT(11)
#घोषणा CSI2_IRQ_COMPLEXIO_ERR				BIT(9)
#घोषणा CSI2_IRQ_FIFO_OVF				BIT(8)
#घोषणा CSI2_IRQ_CONTEXT0				BIT(0)

#घोषणा CSI2_CTRL					0x40
#घोषणा CSI2_CTRL_MFLAG_LEVH_MASK			(7 << 20)
#घोषणा CSI2_CTRL_MFLAG_LEVH_SHIFT			20
#घोषणा CSI2_CTRL_MFLAG_LEVL_MASK			(7 << 17)
#घोषणा CSI2_CTRL_MFLAG_LEVL_SHIFT			17
#घोषणा CSI2_CTRL_BURST_SIZE_EXPAND			(1 << 16)
#घोषणा CSI2_CTRL_VP_CLK_EN				(1 << 15)
#घोषणा CSI2_CTRL_NON_POSTED_WRITE			(1 << 13)
#घोषणा CSI2_CTRL_VP_ONLY_EN				(1 << 11)
#घोषणा CSI2_CTRL_VP_OUT_CTRL_MASK			(3 << 8)
#घोषणा CSI2_CTRL_VP_OUT_CTRL_SHIFT			8
#घोषणा CSI2_CTRL_DBG_EN				(1 << 7)
#घोषणा CSI2_CTRL_BURST_SIZE_MASK			(3 << 5)
#घोषणा CSI2_CTRL_ENDIANNESS				(1 << 4)
#घोषणा CSI2_CTRL_FRAME					(1 << 3)
#घोषणा CSI2_CTRL_ECC_EN				(1 << 2)
#घोषणा CSI2_CTRL_IF_EN					(1 << 0)

#घोषणा CSI2_DBG_H					0x44

#घोषणा CSI2_COMPLEXIO_CFG				0x50
#घोषणा CSI2_COMPLEXIO_CFG_RESET_CTRL			(1 << 30)
#घोषणा CSI2_COMPLEXIO_CFG_RESET_DONE			(1 << 29)
#घोषणा CSI2_COMPLEXIO_CFG_PWD_CMD_MASK			(3 << 27)
#घोषणा CSI2_COMPLEXIO_CFG_PWD_CMD_OFF			(0 << 27)
#घोषणा CSI2_COMPLEXIO_CFG_PWD_CMD_ON			(1 << 27)
#घोषणा CSI2_COMPLEXIO_CFG_PWD_CMD_ULP			(2 << 27)
#घोषणा CSI2_COMPLEXIO_CFG_PWD_STATUS_MASK		(3 << 25)
#घोषणा CSI2_COMPLEXIO_CFG_PWD_STATUS_OFF		(0 << 25)
#घोषणा CSI2_COMPLEXIO_CFG_PWD_STATUS_ON		(1 << 25)
#घोषणा CSI2_COMPLEXIO_CFG_PWD_STATUS_ULP		(2 << 25)
#घोषणा CSI2_COMPLEXIO_CFG_PWR_AUTO			(1 << 24)
#घोषणा CSI2_COMPLEXIO_CFG_DATA_POL(i)			(1 << (((i) * 4) + 3))
#घोषणा CSI2_COMPLEXIO_CFG_DATA_POSITION_MASK(i)	(7 << ((i) * 4))
#घोषणा CSI2_COMPLEXIO_CFG_DATA_POSITION_SHIFT(i)	((i) * 4)
#घोषणा CSI2_COMPLEXIO_CFG_CLOCK_POL			(1 << 3)
#घोषणा CSI2_COMPLEXIO_CFG_CLOCK_POSITION_MASK		(7 << 0)
#घोषणा CSI2_COMPLEXIO_CFG_CLOCK_POSITION_SHIFT		0

#घोषणा CSI2_COMPLEXIO_IRQSTATUS			0x54

#घोषणा CSI2_SHORT_PACKET				0x5c

#घोषणा CSI2_COMPLEXIO_IRQENABLE			0x60

/* Shared bits across CSI2_COMPLEXIO_IRQENABLE and IRQSTATUS */
#घोषणा CSI2_COMPLEXIO_IRQ_STATEALLULPMEXIT		BIT(26)
#घोषणा CSI2_COMPLEXIO_IRQ_STATEALLULPMENTER		BIT(25)
#घोषणा CSI2_COMPLEXIO_IRQ_STATEULPM5			BIT(24)
#घोषणा CSI2_COMPLEXIO_IRQ_STATEULPM4			BIT(23)
#घोषणा CSI2_COMPLEXIO_IRQ_STATEULPM3			BIT(22)
#घोषणा CSI2_COMPLEXIO_IRQ_STATEULPM2			BIT(21)
#घोषणा CSI2_COMPLEXIO_IRQ_STATEULPM1			BIT(20)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRCONTROL5			BIT(19)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRCONTROL4			BIT(18)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRCONTROL3			BIT(17)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRCONTROL2			BIT(16)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRCONTROL1			BIT(15)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRESC5			BIT(14)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRESC4			BIT(13)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRESC3			BIT(12)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRESC2			BIT(11)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRESC1			BIT(10)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRSOTSYNCHS5		BIT(9)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRSOTSYNCHS4		BIT(8)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRSOTSYNCHS3		BIT(7)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRSOTSYNCHS2		BIT(6)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRSOTSYNCHS1		BIT(5)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRSOTHS5			BIT(4)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRSOTHS4			BIT(3)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRSOTHS3			BIT(2)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRSOTHS2			BIT(1)
#घोषणा CSI2_COMPLEXIO_IRQ_ERRSOTHS1			BIT(0)

#घोषणा CSI2_DBG_P					0x68

#घोषणा CSI2_TIMING					0x6c
#घोषणा CSI2_TIMING_FORCE_RX_MODE_IO1			BIT(15)
#घोषणा CSI2_TIMING_STOP_STATE_X16_IO1			BIT(14)
#घोषणा CSI2_TIMING_STOP_STATE_X4_IO1			BIT(13)
#घोषणा CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK		(0x1fff << 0)
#घोषणा CSI2_TIMING_STOP_STATE_COUNTER_IO1_SHIFT	0

#घोषणा CSI2_CTX_CTRL1(i)				(0x70 + (0x20 * (i)))
#घोषणा CSI2_CTX_CTRL1_GENERIC				BIT(30)
#घोषणा CSI2_CTX_CTRL1_TRANSCODE			(0xf << 24)
#घोषणा CSI2_CTX_CTRL1_FEC_NUMBER_MASK			(0xff << 16)
#घोषणा CSI2_CTX_CTRL1_COUNT_MASK			(0xff << 8)
#घोषणा CSI2_CTX_CTRL1_COUNT_SHIFT			8
#घोषणा CSI2_CTX_CTRL1_खातापूर्ण_EN				BIT(7)
#घोषणा CSI2_CTX_CTRL1_EOL_EN				BIT(6)
#घोषणा CSI2_CTX_CTRL1_CS_EN				BIT(5)
#घोषणा CSI2_CTX_CTRL1_COUNT_UNLOCK			BIT(4)
#घोषणा CSI2_CTX_CTRL1_PING_PONG			BIT(3)
#घोषणा CSI2_CTX_CTRL1_CTX_EN				BIT(0)

#घोषणा CSI2_CTX_CTRL2(i)				(0x74 + (0x20 * (i)))
#घोषणा CSI2_CTX_CTRL2_FRAME_MASK			(0xffff << 16)
#घोषणा CSI2_CTX_CTRL2_FRAME_SHIFT			16
#घोषणा CSI2_CTX_CTRL2_USER_DEF_MAP_SHIFT		13
#घोषणा CSI2_CTX_CTRL2_USER_DEF_MAP_MASK		\
		(0x3 << CSI2_CTX_CTRL2_USER_DEF_MAP_SHIFT)
#घोषणा CSI2_CTX_CTRL2_VIRTUAL_ID_MASK			(3 << 11)
#घोषणा CSI2_CTX_CTRL2_VIRTUAL_ID_SHIFT			11
#घोषणा CSI2_CTX_CTRL2_DPCM_PRED			(1 << 10)
#घोषणा CSI2_CTX_CTRL2_FORMAT_MASK			(0x3ff << 0)
#घोषणा CSI2_CTX_CTRL2_FORMAT_SHIFT			0

#घोषणा CSI2_CTX_DAT_OFST(i)				(0x78 + (0x20 * (i)))
#घोषणा CSI2_CTX_DAT_OFST_MASK				(0xfff << 5)

#घोषणा CSI2_CTX_PING_ADDR(i)				(0x7c + (0x20 * (i)))
#घोषणा CSI2_CTX_PING_ADDR_MASK				0xffffffe0

#घोषणा CSI2_CTX_PONG_ADDR(i)				(0x80 + (0x20 * (i)))
#घोषणा CSI2_CTX_PONG_ADDR_MASK				CSI2_CTX_PING_ADDR_MASK

#घोषणा CSI2_CTX_IRQENABLE(i)				(0x84 + (0x20 * (i)))
#घोषणा CSI2_CTX_IRQSTATUS(i)				(0x88 + (0x20 * (i)))

#घोषणा CSI2_CTX_CTRL3(i)				(0x8c + (0x20 * (i)))
#घोषणा CSI2_CTX_CTRL3_ALPHA_SHIFT			5
#घोषणा CSI2_CTX_CTRL3_ALPHA_MASK			\
		(0x3fff << CSI2_CTX_CTRL3_ALPHA_SHIFT)

/* Shared bits across CSI2_CTX_IRQENABLE and IRQSTATUS */
#घोषणा CSI2_CTX_IRQ_ECC_CORRECTION			BIT(8)
#घोषणा CSI2_CTX_IRQ_LINE_NUMBER			BIT(7)
#घोषणा CSI2_CTX_IRQ_FRAME_NUMBER			BIT(6)
#घोषणा CSI2_CTX_IRQ_CS					BIT(5)
#घोषणा CSI2_CTX_IRQ_LE					BIT(3)
#घोषणा CSI2_CTX_IRQ_LS					BIT(2)
#घोषणा CSI2_CTX_IRQ_FE					BIT(1)
#घोषणा CSI2_CTX_IRQ_FS					BIT(0)

/* ISS BTE */
#घोषणा BTE_CTRL					(0x0030)
#घोषणा BTE_CTRL_BW_LIMITER_MASK			(0x3ff << 22)
#घोषणा BTE_CTRL_BW_LIMITER_SHIFT			22

/* ISS ISP_SYS1 */
#घोषणा ISP5_REVISION					(0x0000)
#घोषणा ISP5_SYSCONFIG					(0x0010)
#घोषणा ISP5_SYSCONFIG_STANDBYMODE_MASK			(3 << 4)
#घोषणा ISP5_SYSCONFIG_STANDBYMODE_FORCE		(0 << 4)
#घोषणा ISP5_SYSCONFIG_STANDBYMODE_NO			(1 << 4)
#घोषणा ISP5_SYSCONFIG_STANDBYMODE_SMART		(2 << 4)
#घोषणा ISP5_SYSCONFIG_SOFTRESET			(1 << 1)

#घोषणा ISP5_IRQSTATUS(i)				(0x0028 + (0x10 * (i)))
#घोषणा ISP5_IRQENABLE_SET(i)				(0x002c + (0x10 * (i)))
#घोषणा ISP5_IRQENABLE_CLR(i)				(0x0030 + (0x10 * (i)))

/* Bits shared क्रम ISP5_IRQ* रेजिस्टरs */
#घोषणा ISP5_IRQ_OCP_ERR				BIT(31)
#घोषणा ISP5_IRQ_IPIPE_INT_DPC_RNEW1			BIT(29)
#घोषणा ISP5_IRQ_IPIPE_INT_DPC_RNEW0			BIT(28)
#घोषणा ISP5_IRQ_IPIPE_INT_DPC_INIT			BIT(27)
#घोषणा ISP5_IRQ_IPIPE_INT_खातापूर्ण				BIT(25)
#घोषणा ISP5_IRQ_H3A_INT_खातापूर्ण				BIT(24)
#घोषणा ISP5_IRQ_RSZ_INT_खातापूर्ण1				BIT(23)
#घोषणा ISP5_IRQ_RSZ_INT_खातापूर्ण0				BIT(22)
#घोषणा ISP5_IRQ_RSZ_FIFO_IN_BLK_ERR			BIT(19)
#घोषणा ISP5_IRQ_RSZ_FIFO_OVF				BIT(18)
#घोषणा ISP5_IRQ_RSZ_INT_CYC_RSZB			BIT(17)
#घोषणा ISP5_IRQ_RSZ_INT_CYC_RSZA			BIT(16)
#घोषणा ISP5_IRQ_RSZ_INT_DMA				BIT(15)
#घोषणा ISP5_IRQ_RSZ_INT_LAST_PIX			BIT(14)
#घोषणा ISP5_IRQ_RSZ_INT_REG				BIT(13)
#घोषणा ISP5_IRQ_H3A_INT				BIT(12)
#घोषणा ISP5_IRQ_AF_INT					BIT(11)
#घोषणा ISP5_IRQ_AEW_INT				BIT(10)
#घोषणा ISP5_IRQ_IPIPEIF_IRQ				BIT(9)
#घोषणा ISP5_IRQ_IPIPE_INT_HST				BIT(8)
#घोषणा ISP5_IRQ_IPIPE_INT_BSC				BIT(7)
#घोषणा ISP5_IRQ_IPIPE_INT_DMA				BIT(6)
#घोषणा ISP5_IRQ_IPIPE_INT_LAST_PIX			BIT(5)
#घोषणा ISP5_IRQ_IPIPE_INT_REG				BIT(4)
#घोषणा ISP5_IRQ_ISIF_INT(i)				BIT(i)

#घोषणा ISP5_CTRL					(0x006c)
#घोषणा ISP5_CTRL_MSTANDBY				BIT(24)
#घोषणा ISP5_CTRL_VD_PULSE_EXT				BIT(23)
#घोषणा ISP5_CTRL_MSTANDBY_WAIT				BIT(20)
#घोषणा ISP5_CTRL_BL_CLK_ENABLE				BIT(15)
#घोषणा ISP5_CTRL_ISIF_CLK_ENABLE			BIT(14)
#घोषणा ISP5_CTRL_H3A_CLK_ENABLE			BIT(13)
#घोषणा ISP5_CTRL_RSZ_CLK_ENABLE			BIT(12)
#घोषणा ISP5_CTRL_IPIPE_CLK_ENABLE			BIT(11)
#घोषणा ISP5_CTRL_IPIPEIF_CLK_ENABLE			BIT(10)
#घोषणा ISP5_CTRL_SYNC_ENABLE				BIT(9)
#घोषणा ISP5_CTRL_PSYNC_CLK_SEL				BIT(8)

/* ISS ISP ISIF रेजिस्टर offsets */
#घोषणा ISIF_SYNCEN					(0x0000)
#घोषणा ISIF_SYNCEN_DWEN				BIT(1)
#घोषणा ISIF_SYNCEN_SYEN				BIT(0)

#घोषणा ISIF_MODESET					(0x0004)
#घोषणा ISIF_MODESET_INPMOD_MASK			(3 << 12)
#घोषणा ISIF_MODESET_INPMOD_RAW				(0 << 12)
#घोषणा ISIF_MODESET_INPMOD_YCBCR16			(1 << 12)
#घोषणा ISIF_MODESET_INPMOD_YCBCR8			(2 << 12)
#घोषणा ISIF_MODESET_CCDW_MASK				(7 << 8)
#घोषणा ISIF_MODESET_CCDW_2BIT				(2 << 8)
#घोषणा ISIF_MODESET_CCDMD				(1 << 7)
#घोषणा ISIF_MODESET_SWEN				(1 << 5)
#घोषणा ISIF_MODESET_HDPOL				(1 << 3)
#घोषणा ISIF_MODESET_VDPOL				(1 << 2)

#घोषणा ISIF_SPH					(0x0018)
#घोषणा ISIF_SPH_MASK					(0x7fff)

#घोषणा ISIF_LNH					(0x001c)
#घोषणा ISIF_LNH_MASK					(0x7fff)

#घोषणा ISIF_LNV					(0x0028)
#घोषणा ISIF_LNV_MASK					(0x7fff)

#घोषणा ISIF_HSIZE					(0x0034)
#घोषणा ISIF_HSIZE_ADCR					BIT(12)
#घोषणा ISIF_HSIZE_HSIZE_MASK				(0xfff)

#घोषणा ISIF_CADU					(0x003c)
#घोषणा ISIF_CADU_MASK					(0x7ff)

#घोषणा ISIF_CADL					(0x0040)
#घोषणा ISIF_CADL_MASK					(0xffff)

#घोषणा ISIF_CCOLP					(0x004c)
#घोषणा ISIF_CCOLP_CP0_F0_R				(0 << 6)
#घोषणा ISIF_CCOLP_CP0_F0_GR				(1 << 6)
#घोषणा ISIF_CCOLP_CP0_F0_B				(3 << 6)
#घोषणा ISIF_CCOLP_CP0_F0_GB				(2 << 6)
#घोषणा ISIF_CCOLP_CP1_F0_R				(0 << 4)
#घोषणा ISIF_CCOLP_CP1_F0_GR				(1 << 4)
#घोषणा ISIF_CCOLP_CP1_F0_B				(3 << 4)
#घोषणा ISIF_CCOLP_CP1_F0_GB				(2 << 4)
#घोषणा ISIF_CCOLP_CP2_F0_R				(0 << 2)
#घोषणा ISIF_CCOLP_CP2_F0_GR				(1 << 2)
#घोषणा ISIF_CCOLP_CP2_F0_B				(3 << 2)
#घोषणा ISIF_CCOLP_CP2_F0_GB				(2 << 2)
#घोषणा ISIF_CCOLP_CP3_F0_R				(0 << 0)
#घोषणा ISIF_CCOLP_CP3_F0_GR				(1 << 0)
#घोषणा ISIF_CCOLP_CP3_F0_B				(3 << 0)
#घोषणा ISIF_CCOLP_CP3_F0_GB				(2 << 0)

#घोषणा ISIF_VDINT(i)					(0x0070 + (i) * 4)
#घोषणा ISIF_VDINT_MASK					(0x7fff)

#घोषणा ISIF_CGAMMAWD					(0x0080)
#घोषणा ISIF_CGAMMAWD_GWDI_MASK				(0xf << 1)
#घोषणा ISIF_CGAMMAWD_GWDI(bpp)				((16 - (bpp)) << 1)

#घोषणा ISIF_CCDCFG					(0x0088)
#घोषणा ISIF_CCDCFG_Y8POS				BIT(11)

/* ISS ISP IPIPEIF रेजिस्टर offsets */
#घोषणा IPIPEIF_ENABLE					(0x0000)

#घोषणा IPIPEIF_CFG1					(0x0004)
#घोषणा IPIPEIF_CFG1_INPSRC1_MASK			(3 << 14)
#घोषणा IPIPEIF_CFG1_INPSRC1_VPORT_RAW			(0 << 14)
#घोषणा IPIPEIF_CFG1_INPSRC1_SDRAM_RAW			(1 << 14)
#घोषणा IPIPEIF_CFG1_INPSRC1_ISIF_DARKFM		(2 << 14)
#घोषणा IPIPEIF_CFG1_INPSRC1_SDRAM_YUV			(3 << 14)
#घोषणा IPIPEIF_CFG1_INPSRC2_MASK			(3 << 2)
#घोषणा IPIPEIF_CFG1_INPSRC2_ISIF			(0 << 2)
#घोषणा IPIPEIF_CFG1_INPSRC2_SDRAM_RAW			(1 << 2)
#घोषणा IPIPEIF_CFG1_INPSRC2_ISIF_DARKFM		(2 << 2)
#घोषणा IPIPEIF_CFG1_INPSRC2_SDRAM_YUV			(3 << 2)

#घोषणा IPIPEIF_CFG2					(0x0030)
#घोषणा IPIPEIF_CFG2_YUV8P				BIT(7)
#घोषणा IPIPEIF_CFG2_YUV8				BIT(6)
#घोषणा IPIPEIF_CFG2_YUV16				BIT(3)
#घोषणा IPIPEIF_CFG2_VDPOL				BIT(2)
#घोषणा IPIPEIF_CFG2_HDPOL				BIT(1)
#घोषणा IPIPEIF_CFG2_INTSW				BIT(0)

#घोषणा IPIPEIF_CLKDIV					(0x0040)

/* ISS ISP IPIPE रेजिस्टर offsets */
#घोषणा IPIPE_SRC_EN					(0x0000)
#घोषणा IPIPE_SRC_EN_EN					BIT(0)

#घोषणा IPIPE_SRC_MODE					(0x0004)
#घोषणा IPIPE_SRC_MODE_WRT				BIT(1)
#घोषणा IPIPE_SRC_MODE_OST				BIT(0)

#घोषणा IPIPE_SRC_FMT					(0x0008)
#घोषणा IPIPE_SRC_FMT_RAW2YUV				(0 << 0)
#घोषणा IPIPE_SRC_FMT_RAW2RAW				(1 << 0)
#घोषणा IPIPE_SRC_FMT_RAW2STATS				(2 << 0)
#घोषणा IPIPE_SRC_FMT_YUV2YUV				(3 << 0)

#घोषणा IPIPE_SRC_COL					(0x000c)
#घोषणा IPIPE_SRC_COL_OO_R				(0 << 6)
#घोषणा IPIPE_SRC_COL_OO_GR				(1 << 6)
#घोषणा IPIPE_SRC_COL_OO_B				(3 << 6)
#घोषणा IPIPE_SRC_COL_OO_GB				(2 << 6)
#घोषणा IPIPE_SRC_COL_OE_R				(0 << 4)
#घोषणा IPIPE_SRC_COL_OE_GR				(1 << 4)
#घोषणा IPIPE_SRC_COL_OE_B				(3 << 4)
#घोषणा IPIPE_SRC_COL_OE_GB				(2 << 4)
#घोषणा IPIPE_SRC_COL_EO_R				(0 << 2)
#घोषणा IPIPE_SRC_COL_EO_GR				(1 << 2)
#घोषणा IPIPE_SRC_COL_EO_B				(3 << 2)
#घोषणा IPIPE_SRC_COL_EO_GB				(2 << 2)
#घोषणा IPIPE_SRC_COL_EE_R				(0 << 0)
#घोषणा IPIPE_SRC_COL_EE_GR				(1 << 0)
#घोषणा IPIPE_SRC_COL_EE_B				(3 << 0)
#घोषणा IPIPE_SRC_COL_EE_GB				(2 << 0)

#घोषणा IPIPE_SRC_VPS					(0x0010)
#घोषणा IPIPE_SRC_VPS_MASK				(0xffff)

#घोषणा IPIPE_SRC_VSZ					(0x0014)
#घोषणा IPIPE_SRC_VSZ_MASK				(0x1fff)

#घोषणा IPIPE_SRC_HPS					(0x0018)
#घोषणा IPIPE_SRC_HPS_MASK				(0xffff)

#घोषणा IPIPE_SRC_HSZ					(0x001c)
#घोषणा IPIPE_SRC_HSZ_MASK				(0x1ffe)

#घोषणा IPIPE_SEL_SBU					(0x0020)

#घोषणा IPIPE_SRC_STA					(0x0024)

#घोषणा IPIPE_GCK_MMR					(0x0028)
#घोषणा IPIPE_GCK_MMR_REG				BIT(0)

#घोषणा IPIPE_GCK_PIX					(0x002c)
#घोषणा IPIPE_GCK_PIX_G3				BIT(3)
#घोषणा IPIPE_GCK_PIX_G2				BIT(2)
#घोषणा IPIPE_GCK_PIX_G1				BIT(1)
#घोषणा IPIPE_GCK_PIX_G0				BIT(0)

#घोषणा IPIPE_DPC_LUT_EN				(0x0034)
#घोषणा IPIPE_DPC_LUT_SEL				(0x0038)
#घोषणा IPIPE_DPC_LUT_ADR				(0x003c)
#घोषणा IPIPE_DPC_LUT_SIZ				(0x0040)

#घोषणा IPIPE_DPC_OTF_EN				(0x0044)
#घोषणा IPIPE_DPC_OTF_TYP				(0x0048)
#घोषणा IPIPE_DPC_OTF_2_D_THR_R				(0x004c)
#घोषणा IPIPE_DPC_OTF_2_D_THR_GR			(0x0050)
#घोषणा IPIPE_DPC_OTF_2_D_THR_GB			(0x0054)
#घोषणा IPIPE_DPC_OTF_2_D_THR_B				(0x0058)
#घोषणा IPIPE_DPC_OTF_2_C_THR_R				(0x005c)
#घोषणा IPIPE_DPC_OTF_2_C_THR_GR			(0x0060)
#घोषणा IPIPE_DPC_OTF_2_C_THR_GB			(0x0064)
#घोषणा IPIPE_DPC_OTF_2_C_THR_B				(0x0068)
#घोषणा IPIPE_DPC_OTF_3_SHF				(0x006c)
#घोषणा IPIPE_DPC_OTF_3_D_THR				(0x0070)
#घोषणा IPIPE_DPC_OTF_3_D_SPL				(0x0074)
#घोषणा IPIPE_DPC_OTF_3_D_MIN				(0x0078)
#घोषणा IPIPE_DPC_OTF_3_D_MAX				(0x007c)
#घोषणा IPIPE_DPC_OTF_3_C_THR				(0x0080)
#घोषणा IPIPE_DPC_OTF_3_C_SLP				(0x0084)
#घोषणा IPIPE_DPC_OTF_3_C_MIN				(0x0088)
#घोषणा IPIPE_DPC_OTF_3_C_MAX				(0x008c)

#घोषणा IPIPE_LSC_VOFT					(0x0090)
#घोषणा IPIPE_LSC_VA2					(0x0094)
#घोषणा IPIPE_LSC_VA1					(0x0098)
#घोषणा IPIPE_LSC_VS					(0x009c)
#घोषणा IPIPE_LSC_HOFT					(0x00a0)
#घोषणा IPIPE_LSC_HA2					(0x00a4)
#घोषणा IPIPE_LSC_HA1					(0x00a8)
#घोषणा IPIPE_LSC_HS					(0x00ac)
#घोषणा IPIPE_LSC_GAN_R					(0x00b0)
#घोषणा IPIPE_LSC_GAN_GR				(0x00b4)
#घोषणा IPIPE_LSC_GAN_GB				(0x00b8)
#घोषणा IPIPE_LSC_GAN_B					(0x00bc)
#घोषणा IPIPE_LSC_OFT_R					(0x00c0)
#घोषणा IPIPE_LSC_OFT_GR				(0x00c4)
#घोषणा IPIPE_LSC_OFT_GB				(0x00c8)
#घोषणा IPIPE_LSC_OFT_B					(0x00cc)
#घोषणा IPIPE_LSC_SHF					(0x00d0)
#घोषणा IPIPE_LSC_MAX					(0x00d4)

#घोषणा IPIPE_D2F_1ST_EN				(0x00d8)
#घोषणा IPIPE_D2F_1ST_TYP				(0x00dc)
#घोषणा IPIPE_D2F_1ST_THR_00				(0x00e0)
#घोषणा IPIPE_D2F_1ST_THR_01				(0x00e4)
#घोषणा IPIPE_D2F_1ST_THR_02				(0x00e8)
#घोषणा IPIPE_D2F_1ST_THR_03				(0x00ec)
#घोषणा IPIPE_D2F_1ST_THR_04				(0x00f0)
#घोषणा IPIPE_D2F_1ST_THR_05				(0x00f4)
#घोषणा IPIPE_D2F_1ST_THR_06				(0x00f8)
#घोषणा IPIPE_D2F_1ST_THR_07				(0x00fc)
#घोषणा IPIPE_D2F_1ST_STR_00				(0x0100)
#घोषणा IPIPE_D2F_1ST_STR_01				(0x0104)
#घोषणा IPIPE_D2F_1ST_STR_02				(0x0108)
#घोषणा IPIPE_D2F_1ST_STR_03				(0x010c)
#घोषणा IPIPE_D2F_1ST_STR_04				(0x0110)
#घोषणा IPIPE_D2F_1ST_STR_05				(0x0114)
#घोषणा IPIPE_D2F_1ST_STR_06				(0x0118)
#घोषणा IPIPE_D2F_1ST_STR_07				(0x011c)
#घोषणा IPIPE_D2F_1ST_SPR_00				(0x0120)
#घोषणा IPIPE_D2F_1ST_SPR_01				(0x0124)
#घोषणा IPIPE_D2F_1ST_SPR_02				(0x0128)
#घोषणा IPIPE_D2F_1ST_SPR_03				(0x012c)
#घोषणा IPIPE_D2F_1ST_SPR_04				(0x0130)
#घोषणा IPIPE_D2F_1ST_SPR_05				(0x0134)
#घोषणा IPIPE_D2F_1ST_SPR_06				(0x0138)
#घोषणा IPIPE_D2F_1ST_SPR_07				(0x013c)
#घोषणा IPIPE_D2F_1ST_EDG_MIN				(0x0140)
#घोषणा IPIPE_D2F_1ST_EDG_MAX				(0x0144)
#घोषणा IPIPE_D2F_2ND_EN				(0x0148)
#घोषणा IPIPE_D2F_2ND_TYP				(0x014c)
#घोषणा IPIPE_D2F_2ND_THR00				(0x0150)
#घोषणा IPIPE_D2F_2ND_THR01				(0x0154)
#घोषणा IPIPE_D2F_2ND_THR02				(0x0158)
#घोषणा IPIPE_D2F_2ND_THR03				(0x015c)
#घोषणा IPIPE_D2F_2ND_THR04				(0x0160)
#घोषणा IPIPE_D2F_2ND_THR05				(0x0164)
#घोषणा IPIPE_D2F_2ND_THR06				(0x0168)
#घोषणा IPIPE_D2F_2ND_THR07				(0x016c)
#घोषणा IPIPE_D2F_2ND_STR_00				(0x0170)
#घोषणा IPIPE_D2F_2ND_STR_01				(0x0174)
#घोषणा IPIPE_D2F_2ND_STR_02				(0x0178)
#घोषणा IPIPE_D2F_2ND_STR_03				(0x017c)
#घोषणा IPIPE_D2F_2ND_STR_04				(0x0180)
#घोषणा IPIPE_D2F_2ND_STR_05				(0x0184)
#घोषणा IPIPE_D2F_2ND_STR_06				(0x0188)
#घोषणा IPIPE_D2F_2ND_STR_07				(0x018c)
#घोषणा IPIPE_D2F_2ND_SPR_00				(0x0190)
#घोषणा IPIPE_D2F_2ND_SPR_01				(0x0194)
#घोषणा IPIPE_D2F_2ND_SPR_02				(0x0198)
#घोषणा IPIPE_D2F_2ND_SPR_03				(0x019c)
#घोषणा IPIPE_D2F_2ND_SPR_04				(0x01a0)
#घोषणा IPIPE_D2F_2ND_SPR_05				(0x01a4)
#घोषणा IPIPE_D2F_2ND_SPR_06				(0x01a8)
#घोषणा IPIPE_D2F_2ND_SPR_07				(0x01ac)
#घोषणा IPIPE_D2F_2ND_EDG_MIN				(0x01b0)
#घोषणा IPIPE_D2F_2ND_EDG_MAX				(0x01b4)

#घोषणा IPIPE_GIC_EN					(0x01b8)
#घोषणा IPIPE_GIC_TYP					(0x01bc)
#घोषणा IPIPE_GIC_GAN					(0x01c0)
#घोषणा IPIPE_GIC_NFGAIN				(0x01c4)
#घोषणा IPIPE_GIC_THR					(0x01c8)
#घोषणा IPIPE_GIC_SLP					(0x01cc)

#घोषणा IPIPE_WB2_OFT_R					(0x01d0)
#घोषणा IPIPE_WB2_OFT_GR				(0x01d4)
#घोषणा IPIPE_WB2_OFT_GB				(0x01d8)
#घोषणा IPIPE_WB2_OFT_B					(0x01dc)

#घोषणा IPIPE_WB2_WGN_R					(0x01e0)
#घोषणा IPIPE_WB2_WGN_GR				(0x01e4)
#घोषणा IPIPE_WB2_WGN_GB				(0x01e8)
#घोषणा IPIPE_WB2_WGN_B					(0x01ec)

#घोषणा IPIPE_CFA_MODE					(0x01f0)
#घोषणा IPIPE_CFA_2सूची_HPF_THR				(0x01f4)
#घोषणा IPIPE_CFA_2सूची_HPF_SLP				(0x01f8)
#घोषणा IPIPE_CFA_2सूची_MIX_THR				(0x01fc)
#घोषणा IPIPE_CFA_2सूची_MIX_SLP				(0x0200)
#घोषणा IPIPE_CFA_2सूची_सूची_TRH				(0x0204)
#घोषणा IPIPE_CFA_2सूची_सूची_SLP				(0x0208)
#घोषणा IPIPE_CFA_2सूची_NDWT				(0x020c)
#घोषणा IPIPE_CFA_MONO_HUE_FRA				(0x0210)
#घोषणा IPIPE_CFA_MONO_EDG_THR				(0x0214)
#घोषणा IPIPE_CFA_MONO_THR_MIN				(0x0218)

#घोषणा IPIPE_CFA_MONO_THR_SLP				(0x021c)
#घोषणा IPIPE_CFA_MONO_SLP_MIN				(0x0220)
#घोषणा IPIPE_CFA_MONO_SLP_SLP				(0x0224)
#घोषणा IPIPE_CFA_MONO_LPWT				(0x0228)

#घोषणा IPIPE_RGB1_MUL_RR				(0x022c)
#घोषणा IPIPE_RGB1_MUL_GR				(0x0230)
#घोषणा IPIPE_RGB1_MUL_BR				(0x0234)
#घोषणा IPIPE_RGB1_MUL_RG				(0x0238)
#घोषणा IPIPE_RGB1_MUL_GG				(0x023c)
#घोषणा IPIPE_RGB1_MUL_BG				(0x0240)
#घोषणा IPIPE_RGB1_MUL_RB				(0x0244)
#घोषणा IPIPE_RGB1_MUL_GB				(0x0248)
#घोषणा IPIPE_RGB1_MUL_BB				(0x024c)
#घोषणा IPIPE_RGB1_OFT_OR				(0x0250)
#घोषणा IPIPE_RGB1_OFT_OG				(0x0254)
#घोषणा IPIPE_RGB1_OFT_OB				(0x0258)
#घोषणा IPIPE_GMM_CFG					(0x025c)
#घोषणा IPIPE_RGB2_MUL_RR				(0x0260)
#घोषणा IPIPE_RGB2_MUL_GR				(0x0264)
#घोषणा IPIPE_RGB2_MUL_BR				(0x0268)
#घोषणा IPIPE_RGB2_MUL_RG				(0x026c)
#घोषणा IPIPE_RGB2_MUL_GG				(0x0270)
#घोषणा IPIPE_RGB2_MUL_BG				(0x0274)
#घोषणा IPIPE_RGB2_MUL_RB				(0x0278)
#घोषणा IPIPE_RGB2_MUL_GB				(0x027c)
#घोषणा IPIPE_RGB2_MUL_BB				(0x0280)
#घोषणा IPIPE_RGB2_OFT_OR				(0x0284)
#घोषणा IPIPE_RGB2_OFT_OG				(0x0288)
#घोषणा IPIPE_RGB2_OFT_OB				(0x028c)

#घोषणा IPIPE_YUV_ADJ					(0x0294)
#घोषणा IPIPE_YUV_MUL_RY				(0x0298)
#घोषणा IPIPE_YUV_MUL_GY				(0x029c)
#घोषणा IPIPE_YUV_MUL_BY				(0x02a0)
#घोषणा IPIPE_YUV_MUL_RCB				(0x02a4)
#घोषणा IPIPE_YUV_MUL_GCB				(0x02a8)
#घोषणा IPIPE_YUV_MUL_BCB				(0x02ac)
#घोषणा IPIPE_YUV_MUL_RCR				(0x02b0)
#घोषणा IPIPE_YUV_MUL_GCR				(0x02b4)
#घोषणा IPIPE_YUV_MUL_BCR				(0x02b8)
#घोषणा IPIPE_YUV_OFT_Y					(0x02bc)
#घोषणा IPIPE_YUV_OFT_CB				(0x02c0)
#घोषणा IPIPE_YUV_OFT_CR				(0x02c4)

#घोषणा IPIPE_YUV_PHS					(0x02c8)
#घोषणा IPIPE_YUV_PHS_LPF				BIT(1)
#घोषणा IPIPE_YUV_PHS_POS				BIT(0)

#घोषणा IPIPE_YEE_EN					(0x02d4)
#घोषणा IPIPE_YEE_TYP					(0x02d8)
#घोषणा IPIPE_YEE_SHF					(0x02dc)
#घोषणा IPIPE_YEE_MUL_00				(0x02e0)
#घोषणा IPIPE_YEE_MUL_01				(0x02e4)
#घोषणा IPIPE_YEE_MUL_02				(0x02e8)
#घोषणा IPIPE_YEE_MUL_10				(0x02ec)
#घोषणा IPIPE_YEE_MUL_11				(0x02f0)
#घोषणा IPIPE_YEE_MUL_12				(0x02f4)
#घोषणा IPIPE_YEE_MUL_20				(0x02f8)
#घोषणा IPIPE_YEE_MUL_21				(0x02fc)
#घोषणा IPIPE_YEE_MUL_22				(0x0300)
#घोषणा IPIPE_YEE_THR					(0x0304)
#घोषणा IPIPE_YEE_E_GAN					(0x0308)
#घोषणा IPIPE_YEE_E_THR_1				(0x030c)
#घोषणा IPIPE_YEE_E_THR_2				(0x0310)
#घोषणा IPIPE_YEE_G_GAN					(0x0314)
#घोषणा IPIPE_YEE_G_OFT					(0x0318)

#घोषणा IPIPE_CAR_EN					(0x031c)
#घोषणा IPIPE_CAR_TYP					(0x0320)
#घोषणा IPIPE_CAR_SW					(0x0324)
#घोषणा IPIPE_CAR_HPF_TYP				(0x0328)
#घोषणा IPIPE_CAR_HPF_SHF				(0x032c)
#घोषणा IPIPE_CAR_HPF_THR				(0x0330)
#घोषणा IPIPE_CAR_GN1_GAN				(0x0334)
#घोषणा IPIPE_CAR_GN1_SHF				(0x0338)
#घोषणा IPIPE_CAR_GN1_MIN				(0x033c)
#घोषणा IPIPE_CAR_GN2_GAN				(0x0340)
#घोषणा IPIPE_CAR_GN2_SHF				(0x0344)
#घोषणा IPIPE_CAR_GN2_MIN				(0x0348)
#घोषणा IPIPE_CGS_EN					(0x034c)
#घोषणा IPIPE_CGS_GN1_L_THR				(0x0350)
#घोषणा IPIPE_CGS_GN1_L_GAIN				(0x0354)
#घोषणा IPIPE_CGS_GN1_L_SHF				(0x0358)
#घोषणा IPIPE_CGS_GN1_L_MIN				(0x035c)
#घोषणा IPIPE_CGS_GN1_H_THR				(0x0360)
#घोषणा IPIPE_CGS_GN1_H_GAIN				(0x0364)
#घोषणा IPIPE_CGS_GN1_H_SHF				(0x0368)
#घोषणा IPIPE_CGS_GN1_H_MIN				(0x036c)
#घोषणा IPIPE_CGS_GN2_L_THR				(0x0370)
#घोषणा IPIPE_CGS_GN2_L_GAIN				(0x0374)
#घोषणा IPIPE_CGS_GN2_L_SHF				(0x0378)
#घोषणा IPIPE_CGS_GN2_L_MIN				(0x037c)

#घोषणा IPIPE_BOX_EN					(0x0380)
#घोषणा IPIPE_BOX_MODE					(0x0384)
#घोषणा IPIPE_BOX_TYP					(0x0388)
#घोषणा IPIPE_BOX_SHF					(0x038c)
#घोषणा IPIPE_BOX_SDR_SAD_H				(0x0390)
#घोषणा IPIPE_BOX_SDR_SAD_L				(0x0394)

#घोषणा IPIPE_HST_EN					(0x039c)
#घोषणा IPIPE_HST_MODE					(0x03a0)
#घोषणा IPIPE_HST_SEL					(0x03a4)
#घोषणा IPIPE_HST_PARA					(0x03a8)
#घोषणा IPIPE_HST_0_VPS					(0x03ac)
#घोषणा IPIPE_HST_0_VSZ					(0x03b0)
#घोषणा IPIPE_HST_0_HPS					(0x03b4)
#घोषणा IPIPE_HST_0_HSZ					(0x03b8)
#घोषणा IPIPE_HST_1_VPS					(0x03bc)
#घोषणा IPIPE_HST_1_VSZ					(0x03c0)
#घोषणा IPIPE_HST_1_HPS					(0x03c4)
#घोषणा IPIPE_HST_1_HSZ					(0x03c8)
#घोषणा IPIPE_HST_2_VPS					(0x03cc)
#घोषणा IPIPE_HST_2_VSZ					(0x03d0)
#घोषणा IPIPE_HST_2_HPS					(0x03d4)
#घोषणा IPIPE_HST_2_HSZ					(0x03d8)
#घोषणा IPIPE_HST_3_VPS					(0x03dc)
#घोषणा IPIPE_HST_3_VSZ					(0x03e0)
#घोषणा IPIPE_HST_3_HPS					(0x03e4)
#घोषणा IPIPE_HST_3_HSZ					(0x03e8)
#घोषणा IPIPE_HST_TBL					(0x03ec)
#घोषणा IPIPE_HST_MUL_R					(0x03f0)
#घोषणा IPIPE_HST_MUL_GR				(0x03f4)
#घोषणा IPIPE_HST_MUL_GB				(0x03f8)
#घोषणा IPIPE_HST_MUL_B					(0x03fc)

#घोषणा IPIPE_BSC_EN					(0x0400)
#घोषणा IPIPE_BSC_MODE					(0x0404)
#घोषणा IPIPE_BSC_TYP					(0x0408)
#घोषणा IPIPE_BSC_ROW_VCT				(0x040c)
#घोषणा IPIPE_BSC_ROW_SHF				(0x0410)
#घोषणा IPIPE_BSC_ROW_VPO				(0x0414)
#घोषणा IPIPE_BSC_ROW_VNU				(0x0418)
#घोषणा IPIPE_BSC_ROW_VSKIP				(0x041c)
#घोषणा IPIPE_BSC_ROW_HPO				(0x0420)
#घोषणा IPIPE_BSC_ROW_HNU				(0x0424)
#घोषणा IPIPE_BSC_ROW_HSKIP				(0x0428)
#घोषणा IPIPE_BSC_COL_VCT				(0x042c)
#घोषणा IPIPE_BSC_COL_SHF				(0x0430)
#घोषणा IPIPE_BSC_COL_VPO				(0x0434)
#घोषणा IPIPE_BSC_COL_VNU				(0x0438)
#घोषणा IPIPE_BSC_COL_VSKIP				(0x043c)
#घोषणा IPIPE_BSC_COL_HPO				(0x0440)
#घोषणा IPIPE_BSC_COL_HNU				(0x0444)
#घोषणा IPIPE_BSC_COL_HSKIP				(0x0448)

#घोषणा IPIPE_BSC_EN					(0x0400)

/* ISS ISP Resizer रेजिस्टर offsets */
#घोषणा RSZ_REVISION					(0x0000)
#घोषणा RSZ_SYSCONFIG					(0x0004)
#घोषणा RSZ_SYSCONFIG_RSZB_CLK_EN			BIT(9)
#घोषणा RSZ_SYSCONFIG_RSZA_CLK_EN			BIT(8)

#घोषणा RSZ_IN_FIFO_CTRL				(0x000c)
#घोषणा RSZ_IN_FIFO_CTRL_THRLD_LOW_MASK			(0x1ff << 16)
#घोषणा RSZ_IN_FIFO_CTRL_THRLD_LOW_SHIFT		16
#घोषणा RSZ_IN_FIFO_CTRL_THRLD_HIGH_MASK		(0x1ff << 0)
#घोषणा RSZ_IN_FIFO_CTRL_THRLD_HIGH_SHIFT		0

#घोषणा RSZ_FRACDIV					(0x0008)
#घोषणा RSZ_FRACDIV_MASK				(0xffff)

#घोषणा RSZ_SRC_EN					(0x0020)
#घोषणा RSZ_SRC_EN_SRC_EN				BIT(0)

#घोषणा RSZ_SRC_MODE					(0x0024)
#घोषणा RSZ_SRC_MODE_OST				BIT(0)
#घोषणा RSZ_SRC_MODE_WRT				BIT(1)

#घोषणा RSZ_SRC_FMT0					(0x0028)
#घोषणा RSZ_SRC_FMT0_BYPASS				BIT(1)
#घोषणा RSZ_SRC_FMT0_SEL				BIT(0)

#घोषणा RSZ_SRC_FMT1					(0x002c)
#घोषणा RSZ_SRC_FMT1_IN420				BIT(1)

#घोषणा RSZ_SRC_VPS					(0x0030)
#घोषणा RSZ_SRC_VSZ					(0x0034)
#घोषणा RSZ_SRC_HPS					(0x0038)
#घोषणा RSZ_SRC_HSZ					(0x003c)
#घोषणा RSZ_DMA_RZA					(0x0040)
#घोषणा RSZ_DMA_RZB					(0x0044)
#घोषणा RSZ_DMA_STA					(0x0048)
#घोषणा RSZ_GCK_MMR					(0x004c)
#घोषणा RSZ_GCK_MMR_MMR					BIT(0)

#घोषणा RSZ_GCK_SDR					(0x0054)
#घोषणा RSZ_GCK_SDR_CORE				BIT(0)

#घोषणा RSZ_IRQ_RZA					(0x0058)
#घोषणा RSZ_IRQ_RZA_MASK				(0x1fff)

#घोषणा RSZ_IRQ_RZB					(0x005c)
#घोषणा RSZ_IRQ_RZB_MASK				(0x1fff)

#घोषणा RSZ_YUV_Y_MIN					(0x0060)
#घोषणा RSZ_YUV_Y_MAX					(0x0064)
#घोषणा RSZ_YUV_C_MIN					(0x0068)
#घोषणा RSZ_YUV_C_MAX					(0x006c)

#घोषणा RSZ_SEQ						(0x0074)
#घोषणा RSZ_SEQ_HRVB					BIT(2)
#घोषणा RSZ_SEQ_HRVA					BIT(0)

#घोषणा RZA_EN						(0x0078)
#घोषणा RZA_MODE					(0x007c)
#घोषणा RZA_MODE_ONE_SHOT				BIT(0)

#घोषणा RZA_420						(0x0080)
#घोषणा RZA_I_VPS					(0x0084)
#घोषणा RZA_I_HPS					(0x0088)
#घोषणा RZA_O_VSZ					(0x008c)
#घोषणा RZA_O_HSZ					(0x0090)
#घोषणा RZA_V_PHS_Y					(0x0094)
#घोषणा RZA_V_PHS_C					(0x0098)
#घोषणा RZA_V_DIF					(0x009c)
#घोषणा RZA_V_TYP					(0x00a0)
#घोषणा RZA_V_LPF					(0x00a4)
#घोषणा RZA_H_PHS					(0x00a8)
#घोषणा RZA_H_DIF					(0x00b0)
#घोषणा RZA_H_TYP					(0x00b4)
#घोषणा RZA_H_LPF					(0x00b8)
#घोषणा RZA_DWN_EN					(0x00bc)
#घोषणा RZA_SDR_Y_BAD_H					(0x00d0)
#घोषणा RZA_SDR_Y_BAD_L					(0x00d4)
#घोषणा RZA_SDR_Y_SAD_H					(0x00d8)
#घोषणा RZA_SDR_Y_SAD_L					(0x00dc)
#घोषणा RZA_SDR_Y_OFT					(0x00e0)
#घोषणा RZA_SDR_Y_PTR_S					(0x00e4)
#घोषणा RZA_SDR_Y_PTR_E					(0x00e8)
#घोषणा RZA_SDR_C_BAD_H					(0x00ec)
#घोषणा RZA_SDR_C_BAD_L					(0x00f0)
#घोषणा RZA_SDR_C_SAD_H					(0x00f4)
#घोषणा RZA_SDR_C_SAD_L					(0x00f8)
#घोषणा RZA_SDR_C_OFT					(0x00fc)
#घोषणा RZA_SDR_C_PTR_S					(0x0100)
#घोषणा RZA_SDR_C_PTR_E					(0x0104)

#घोषणा RZB_EN						(0x0108)
#घोषणा RZB_MODE					(0x010c)
#घोषणा RZB_420						(0x0110)
#घोषणा RZB_I_VPS					(0x0114)
#घोषणा RZB_I_HPS					(0x0118)
#घोषणा RZB_O_VSZ					(0x011c)
#घोषणा RZB_O_HSZ					(0x0120)

#घोषणा RZB_V_DIF					(0x012c)
#घोषणा RZB_V_TYP					(0x0130)
#घोषणा RZB_V_LPF					(0x0134)

#घोषणा RZB_H_DIF					(0x0140)
#घोषणा RZB_H_TYP					(0x0144)
#घोषणा RZB_H_LPF					(0x0148)

#घोषणा RZB_SDR_Y_BAD_H					(0x0160)
#घोषणा RZB_SDR_Y_BAD_L					(0x0164)
#घोषणा RZB_SDR_Y_SAD_H					(0x0168)
#घोषणा RZB_SDR_Y_SAD_L					(0x016c)
#घोषणा RZB_SDR_Y_OFT					(0x0170)
#घोषणा RZB_SDR_Y_PTR_S					(0x0174)
#घोषणा RZB_SDR_Y_PTR_E					(0x0178)
#घोषणा RZB_SDR_C_BAD_H					(0x017c)
#घोषणा RZB_SDR_C_BAD_L					(0x0180)
#घोषणा RZB_SDR_C_SAD_H					(0x0184)
#घोषणा RZB_SDR_C_SAD_L					(0x0188)

#घोषणा RZB_SDR_C_PTR_S					(0x0190)
#घोषणा RZB_SDR_C_PTR_E					(0x0194)

/* Shared Biपंचांगasks between RZA & RZB */
#घोषणा RSZ_EN_EN					BIT(0)

#घोषणा RSZ_420_CEN					BIT(1)
#घोषणा RSZ_420_YEN					BIT(0)

#घोषणा RSZ_I_VPS_MASK					(0x1fff)

#घोषणा RSZ_I_HPS_MASK					(0x1fff)

#घोषणा RSZ_O_VSZ_MASK					(0x1fff)

#घोषणा RSZ_O_HSZ_MASK					(0x1ffe)

#घोषणा RSZ_V_PHS_Y_MASK				(0x3fff)

#घोषणा RSZ_V_PHS_C_MASK				(0x3fff)

#घोषणा RSZ_V_DIF_MASK					(0x3fff)

#घोषणा RSZ_V_TYP_C					BIT(1)
#घोषणा RSZ_V_TYP_Y					BIT(0)

#घोषणा RSZ_V_LPF_C_MASK				(0x3f << 6)
#घोषणा RSZ_V_LPF_C_SHIFT				6
#घोषणा RSZ_V_LPF_Y_MASK				(0x3f << 0)
#घोषणा RSZ_V_LPF_Y_SHIFT				0

#घोषणा RSZ_H_PHS_MASK					(0x3fff)

#घोषणा RSZ_H_DIF_MASK					(0x3fff)

#घोषणा RSZ_H_TYP_C					BIT(1)
#घोषणा RSZ_H_TYP_Y					BIT(0)

#घोषणा RSZ_H_LPF_C_MASK				(0x3f << 6)
#घोषणा RSZ_H_LPF_C_SHIFT				6
#घोषणा RSZ_H_LPF_Y_MASK				(0x3f << 0)
#घोषणा RSZ_H_LPF_Y_SHIFT				0

#घोषणा RSZ_DWN_EN_DWN_EN				BIT(0)

#पूर्ण_अगर /* _OMAP4_ISS_REGS_H_ */
