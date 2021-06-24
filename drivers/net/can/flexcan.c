<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// flexcan.c - FLEXCAN CAN controller driver
//
// Copyright (c) 2005-2006 Varma Electronics Oy
// Copyright (c) 2009 Sascha Hauer, Pengutronix
// Copyright (c) 2010-2017 Pengutronix, Marc Kleine-Budde <kernel@pengutronix.de>
// Copyright (c) 2014 David Jander, Protonic Holland
//
// Based on code originally by Andrey Volkov <avolkov@varma-el.com>

#समावेश <dt-bindings/firmware/imx/rsrc.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/led.h>
#समावेश <linux/can/rx-offload.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware/imx/sci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा DRV_NAME			"flexcan"

/* 8 क्रम RX fअगरo and 2 error handling */
#घोषणा FLEXCAN_NAPI_WEIGHT		(8 + 2)

/* FLEXCAN module configuration रेजिस्टर (CANMCR) bits */
#घोषणा FLEXCAN_MCR_MDIS		BIT(31)
#घोषणा FLEXCAN_MCR_FRZ			BIT(30)
#घोषणा FLEXCAN_MCR_FEN			BIT(29)
#घोषणा FLEXCAN_MCR_HALT		BIT(28)
#घोषणा FLEXCAN_MCR_NOT_RDY		BIT(27)
#घोषणा FLEXCAN_MCR_WAK_MSK		BIT(26)
#घोषणा FLEXCAN_MCR_SOFTRST		BIT(25)
#घोषणा FLEXCAN_MCR_FRZ_ACK		BIT(24)
#घोषणा FLEXCAN_MCR_SUPV		BIT(23)
#घोषणा FLEXCAN_MCR_SLF_WAK		BIT(22)
#घोषणा FLEXCAN_MCR_WRN_EN		BIT(21)
#घोषणा FLEXCAN_MCR_LPM_ACK		BIT(20)
#घोषणा FLEXCAN_MCR_WAK_SRC		BIT(19)
#घोषणा FLEXCAN_MCR_DOZE		BIT(18)
#घोषणा FLEXCAN_MCR_SRX_DIS		BIT(17)
#घोषणा FLEXCAN_MCR_IRMQ		BIT(16)
#घोषणा FLEXCAN_MCR_LPRIO_EN		BIT(13)
#घोषणा FLEXCAN_MCR_AEN			BIT(12)
#घोषणा FLEXCAN_MCR_FDEN		BIT(11)
/* MCR_MAXMB: maximum used MBs is MAXMB + 1 */
#घोषणा FLEXCAN_MCR_MAXMB(x)		((x) & 0x7f)
#घोषणा FLEXCAN_MCR_IDAM_A		(0x0 << 8)
#घोषणा FLEXCAN_MCR_IDAM_B		(0x1 << 8)
#घोषणा FLEXCAN_MCR_IDAM_C		(0x2 << 8)
#घोषणा FLEXCAN_MCR_IDAM_D		(0x3 << 8)

/* FLEXCAN control रेजिस्टर (CANCTRL) bits */
#घोषणा FLEXCAN_CTRL_PRESDIV(x)		(((x) & 0xff) << 24)
#घोषणा FLEXCAN_CTRL_RJW(x)		(((x) & 0x03) << 22)
#घोषणा FLEXCAN_CTRL_PSEG1(x)		(((x) & 0x07) << 19)
#घोषणा FLEXCAN_CTRL_PSEG2(x)		(((x) & 0x07) << 16)
#घोषणा FLEXCAN_CTRL_BOFF_MSK		BIT(15)
#घोषणा FLEXCAN_CTRL_ERR_MSK		BIT(14)
#घोषणा FLEXCAN_CTRL_CLK_SRC		BIT(13)
#घोषणा FLEXCAN_CTRL_LPB		BIT(12)
#घोषणा FLEXCAN_CTRL_TWRN_MSK		BIT(11)
#घोषणा FLEXCAN_CTRL_RWRN_MSK		BIT(10)
#घोषणा FLEXCAN_CTRL_SMP		BIT(7)
#घोषणा FLEXCAN_CTRL_BOFF_REC		BIT(6)
#घोषणा FLEXCAN_CTRL_TSYN		BIT(5)
#घोषणा FLEXCAN_CTRL_LBUF		BIT(4)
#घोषणा FLEXCAN_CTRL_LOM		BIT(3)
#घोषणा FLEXCAN_CTRL_PROPSEG(x)		((x) & 0x07)
#घोषणा FLEXCAN_CTRL_ERR_BUS		(FLEXCAN_CTRL_ERR_MSK)
#घोषणा FLEXCAN_CTRL_ERR_STATE \
	(FLEXCAN_CTRL_TWRN_MSK | FLEXCAN_CTRL_RWRN_MSK | \
	 FLEXCAN_CTRL_BOFF_MSK)
#घोषणा FLEXCAN_CTRL_ERR_ALL \
	(FLEXCAN_CTRL_ERR_BUS | FLEXCAN_CTRL_ERR_STATE)

/* FLEXCAN control रेजिस्टर 2 (CTRL2) bits */
#घोषणा FLEXCAN_CTRL2_ECRWRE		BIT(29)
#घोषणा FLEXCAN_CTRL2_WRMFRZ		BIT(28)
#घोषणा FLEXCAN_CTRL2_RFFN(x)		(((x) & 0x0f) << 24)
#घोषणा FLEXCAN_CTRL2_TASD(x)		(((x) & 0x1f) << 19)
#घोषणा FLEXCAN_CTRL2_MRP		BIT(18)
#घोषणा FLEXCAN_CTRL2_RRS		BIT(17)
#घोषणा FLEXCAN_CTRL2_EACEN		BIT(16)
#घोषणा FLEXCAN_CTRL2_ISOCANFDEN	BIT(12)

/* FLEXCAN memory error control रेजिस्टर (MECR) bits */
#घोषणा FLEXCAN_MECR_ECRWRDIS		BIT(31)
#घोषणा FLEXCAN_MECR_HANCEI_MSK		BIT(19)
#घोषणा FLEXCAN_MECR_FANCEI_MSK		BIT(18)
#घोषणा FLEXCAN_MECR_CEI_MSK		BIT(16)
#घोषणा FLEXCAN_MECR_HAERRIE		BIT(15)
#घोषणा FLEXCAN_MECR_FAERRIE		BIT(14)
#घोषणा FLEXCAN_MECR_EXTERRIE		BIT(13)
#घोषणा FLEXCAN_MECR_RERRDIS		BIT(9)
#घोषणा FLEXCAN_MECR_ECCDIS		BIT(8)
#घोषणा FLEXCAN_MECR_NCEFAFRZ		BIT(7)

/* FLEXCAN error and status रेजिस्टर (ESR) bits */
#घोषणा FLEXCAN_ESR_TWRN_INT		BIT(17)
#घोषणा FLEXCAN_ESR_RWRN_INT		BIT(16)
#घोषणा FLEXCAN_ESR_BIT1_ERR		BIT(15)
#घोषणा FLEXCAN_ESR_BIT0_ERR		BIT(14)
#घोषणा FLEXCAN_ESR_ACK_ERR		BIT(13)
#घोषणा FLEXCAN_ESR_CRC_ERR		BIT(12)
#घोषणा FLEXCAN_ESR_FRM_ERR		BIT(11)
#घोषणा FLEXCAN_ESR_STF_ERR		BIT(10)
#घोषणा FLEXCAN_ESR_TX_WRN		BIT(9)
#घोषणा FLEXCAN_ESR_RX_WRN		BIT(8)
#घोषणा FLEXCAN_ESR_IDLE		BIT(7)
#घोषणा FLEXCAN_ESR_TXRX		BIT(6)
#घोषणा FLEXCAN_EST_FLT_CONF_SHIFT	(4)
#घोषणा FLEXCAN_ESR_FLT_CONF_MASK	(0x3 << FLEXCAN_EST_FLT_CONF_SHIFT)
#घोषणा FLEXCAN_ESR_FLT_CONF_ACTIVE	(0x0 << FLEXCAN_EST_FLT_CONF_SHIFT)
#घोषणा FLEXCAN_ESR_FLT_CONF_PASSIVE	(0x1 << FLEXCAN_EST_FLT_CONF_SHIFT)
#घोषणा FLEXCAN_ESR_BOFF_INT		BIT(2)
#घोषणा FLEXCAN_ESR_ERR_INT		BIT(1)
#घोषणा FLEXCAN_ESR_WAK_INT		BIT(0)
#घोषणा FLEXCAN_ESR_ERR_BUS \
	(FLEXCAN_ESR_BIT1_ERR | FLEXCAN_ESR_BIT0_ERR | \
	 FLEXCAN_ESR_ACK_ERR | FLEXCAN_ESR_CRC_ERR | \
	 FLEXCAN_ESR_FRM_ERR | FLEXCAN_ESR_STF_ERR)
#घोषणा FLEXCAN_ESR_ERR_STATE \
	(FLEXCAN_ESR_TWRN_INT | FLEXCAN_ESR_RWRN_INT | FLEXCAN_ESR_BOFF_INT)
#घोषणा FLEXCAN_ESR_ERR_ALL \
	(FLEXCAN_ESR_ERR_BUS | FLEXCAN_ESR_ERR_STATE)
#घोषणा FLEXCAN_ESR_ALL_INT \
	(FLEXCAN_ESR_TWRN_INT | FLEXCAN_ESR_RWRN_INT | \
	 FLEXCAN_ESR_BOFF_INT | FLEXCAN_ESR_ERR_INT)

/* FLEXCAN Bit Timing रेजिस्टर (CBT) bits */
#घोषणा FLEXCAN_CBT_BTF			BIT(31)
#घोषणा FLEXCAN_CBT_EPRESDIV_MASK	GENMASK(30, 21)
#घोषणा FLEXCAN_CBT_ERJW_MASK		GENMASK(20, 16)
#घोषणा FLEXCAN_CBT_EPROPSEG_MASK	GENMASK(15, 10)
#घोषणा FLEXCAN_CBT_EPSEG1_MASK		GENMASK(9, 5)
#घोषणा FLEXCAN_CBT_EPSEG2_MASK		GENMASK(4, 0)

/* FLEXCAN FD control रेजिस्टर (FDCTRL) bits */
#घोषणा FLEXCAN_FDCTRL_FDRATE		BIT(31)
#घोषणा FLEXCAN_FDCTRL_MBDSR1		GENMASK(20, 19)
#घोषणा FLEXCAN_FDCTRL_MBDSR0		GENMASK(17, 16)
#घोषणा FLEXCAN_FDCTRL_MBDSR_8		0x0
#घोषणा FLEXCAN_FDCTRL_MBDSR_12		0x1
#घोषणा FLEXCAN_FDCTRL_MBDSR_32		0x2
#घोषणा FLEXCAN_FDCTRL_MBDSR_64		0x3
#घोषणा FLEXCAN_FDCTRL_TDCEN		BIT(15)
#घोषणा FLEXCAN_FDCTRL_TDCFAIL		BIT(14)
#घोषणा FLEXCAN_FDCTRL_TDCOFF		GENMASK(12, 8)
#घोषणा FLEXCAN_FDCTRL_TDCVAL		GENMASK(5, 0)

/* FLEXCAN FD Bit Timing रेजिस्टर (FDCBT) bits */
#घोषणा FLEXCAN_FDCBT_FPRESDIV_MASK	GENMASK(29, 20)
#घोषणा FLEXCAN_FDCBT_FRJW_MASK		GENMASK(18, 16)
#घोषणा FLEXCAN_FDCBT_FPROPSEG_MASK	GENMASK(14, 10)
#घोषणा FLEXCAN_FDCBT_FPSEG1_MASK	GENMASK(7, 5)
#घोषणा FLEXCAN_FDCBT_FPSEG2_MASK	GENMASK(2, 0)

/* FLEXCAN पूर्णांकerrupt flag रेजिस्टर (IFLAG) bits */
/* Errata ERR005829 step7: Reserve first valid MB */
#घोषणा FLEXCAN_TX_MB_RESERVED_OFF_FIFO		8
#घोषणा FLEXCAN_TX_MB_RESERVED_OFF_TIMESTAMP	0
#घोषणा FLEXCAN_RX_MB_OFF_TIMESTAMP_FIRST	(FLEXCAN_TX_MB_RESERVED_OFF_TIMESTAMP + 1)
#घोषणा FLEXCAN_IFLAG_MB(x)		BIT_ULL(x)
#घोषणा FLEXCAN_IFLAG_RX_FIFO_OVERFLOW	BIT(7)
#घोषणा FLEXCAN_IFLAG_RX_FIFO_WARN	BIT(6)
#घोषणा FLEXCAN_IFLAG_RX_FIFO_AVAILABLE	BIT(5)

/* FLEXCAN message buffers */
#घोषणा FLEXCAN_MB_CODE_MASK		(0xf << 24)
#घोषणा FLEXCAN_MB_CODE_RX_BUSY_BIT	(0x1 << 24)
#घोषणा FLEXCAN_MB_CODE_RX_INACTIVE	(0x0 << 24)
#घोषणा FLEXCAN_MB_CODE_RX_EMPTY	(0x4 << 24)
#घोषणा FLEXCAN_MB_CODE_RX_FULL		(0x2 << 24)
#घोषणा FLEXCAN_MB_CODE_RX_OVERRUN	(0x6 << 24)
#घोषणा FLEXCAN_MB_CODE_RX_RANSWER	(0xa << 24)

#घोषणा FLEXCAN_MB_CODE_TX_INACTIVE	(0x8 << 24)
#घोषणा FLEXCAN_MB_CODE_TX_ABORT	(0x9 << 24)
#घोषणा FLEXCAN_MB_CODE_TX_DATA		(0xc << 24)
#घोषणा FLEXCAN_MB_CODE_TX_TANSWER	(0xe << 24)

#घोषणा FLEXCAN_MB_CNT_EDL		BIT(31)
#घोषणा FLEXCAN_MB_CNT_BRS		BIT(30)
#घोषणा FLEXCAN_MB_CNT_ESI		BIT(29)
#घोषणा FLEXCAN_MB_CNT_SRR		BIT(22)
#घोषणा FLEXCAN_MB_CNT_IDE		BIT(21)
#घोषणा FLEXCAN_MB_CNT_RTR		BIT(20)
#घोषणा FLEXCAN_MB_CNT_LENGTH(x)	(((x) & 0xf) << 16)
#घोषणा FLEXCAN_MB_CNT_TIMESTAMP(x)	((x) & 0xffff)

#घोषणा FLEXCAN_TIMEOUT_US		(250)

/* FLEXCAN hardware feature flags
 *
 * Below is some version info we got:
 *    SOC   Version   IP-Version  Glitch- [TR]WRN_INT IRQ Err Memory err RTR rece-   FD Mode
 *                                Filter? connected?  Passive detection  ption in MB Supported?
 *   MX25  FlexCAN2  03.00.00.00     no        no        no       no        no           no
 *   MX28  FlexCAN2  03.00.04.00    yes       yes        no       no        no           no
 *   MX35  FlexCAN2  03.00.00.00     no        no        no       no        no           no
 *   MX53  FlexCAN2  03.00.00.00    yes        no        no       no        no           no
 *   MX6s  FlexCAN3  10.00.12.00    yes       yes        no       no       yes           no
 *   MX8QM FlexCAN3  03.00.23.00    yes       yes        no       no       yes          yes
 *   MX8MP FlexCAN3  03.00.17.01    yes       yes        no      yes       yes          yes
 *   VF610 FlexCAN3  ?               no       yes        no      yes       yes?          no
 * LS1021A FlexCAN2  03.00.04.00     no       yes        no       no       yes           no
 * LX2160A FlexCAN3  03.00.23.00     no       yes        no      yes       yes          yes
 *
 * Some SOCs करो not have the RX_WARN & TX_WARN पूर्णांकerrupt line connected.
 */

/* [TR]WRN_INT not connected */
#घोषणा FLEXCAN_QUIRK_BROKEN_WERR_STATE BIT(1)
 /* Disable RX FIFO Global mask */
#घोषणा FLEXCAN_QUIRK_DISABLE_RXFG BIT(2)
/* Enable EACEN and RRS bit in ctrl2 */
#घोषणा FLEXCAN_QUIRK_ENABLE_EACEN_RRS  BIT(3)
/* Disable non-correctable errors पूर्णांकerrupt and मुक्तze mode */
#घोषणा FLEXCAN_QUIRK_DISABLE_MECR BIT(4)
/* Use बारtamp based offloading */
#घोषणा FLEXCAN_QUIRK_USE_OFF_TIMESTAMP BIT(5)
/* No पूर्णांकerrupt क्रम error passive */
#घोषणा FLEXCAN_QUIRK_BROKEN_PERR_STATE BIT(6)
/* शेष to BE रेजिस्टर access */
#घोषणा FLEXCAN_QUIRK_DEFAULT_BIG_ENDIAN BIT(7)
/* Setup stop mode with GPR to support wakeup */
#घोषणा FLEXCAN_QUIRK_SETUP_STOP_MODE_GPR BIT(8)
/* Support CAN-FD mode */
#घोषणा FLEXCAN_QUIRK_SUPPORT_FD BIT(9)
/* support memory detection and correction */
#घोषणा FLEXCAN_QUIRK_SUPPORT_ECC BIT(10)
/* Setup stop mode with SCU firmware to support wakeup */
#घोषणा FLEXCAN_QUIRK_SETUP_STOP_MODE_SCFW BIT(11)

/* Structure of the message buffer */
काष्ठा flexcan_mb अणु
	u32 can_ctrl;
	u32 can_id;
	u32 data[];
पूर्ण;

/* Structure of the hardware रेजिस्टरs */
काष्ठा flexcan_regs अणु
	u32 mcr;		/* 0x00 */
	u32 ctrl;		/* 0x04 - Not affected by Soft Reset */
	u32 समयr;		/* 0x08 */
	u32 tcr;		/* 0x0c */
	u32 rxgmask;		/* 0x10 - Not affected by Soft Reset */
	u32 rx14mask;		/* 0x14 - Not affected by Soft Reset */
	u32 rx15mask;		/* 0x18 - Not affected by Soft Reset */
	u32 ecr;		/* 0x1c */
	u32 esr;		/* 0x20 */
	u32 imask2;		/* 0x24 */
	u32 imask1;		/* 0x28 */
	u32 अगरlag2;		/* 0x2c */
	u32 अगरlag1;		/* 0x30 */
	जोड़ अणु			/* 0x34 */
		u32 gfwr_mx28;	/* MX28, MX53 */
		u32 ctrl2;	/* MX6, VF610 - Not affected by Soft Reset */
	पूर्ण;
	u32 esr2;		/* 0x38 */
	u32 imeur;		/* 0x3c */
	u32 lrfr;		/* 0x40 */
	u32 crcr;		/* 0x44 */
	u32 rxfgmask;		/* 0x48 */
	u32 rxfir;		/* 0x4c - Not affected by Soft Reset */
	u32 cbt;		/* 0x50 - Not affected by Soft Reset */
	u32 _reserved2;		/* 0x54 */
	u32 dbg1;		/* 0x58 */
	u32 dbg2;		/* 0x5c */
	u32 _reserved3[8];	/* 0x60 */
	u8 mb[2][512];		/* 0x80 - Not affected by Soft Reset */
	/* FIFO-mode:
	 *			MB
	 * 0x080...0x08f	0	RX message buffer
	 * 0x090...0x0df	1-5	reserved
	 * 0x0e0...0x0ff	6-7	8 entry ID table
	 *				(mx25, mx28, mx35, mx53)
	 * 0x0e0...0x2df	6-7..37	8..128 entry ID table
	 *				size conf'ed via ctrl2::RFFN
	 *				(mx6, vf610)
	 */
	u32 _reserved4[256];	/* 0x480 */
	u32 rximr[64];		/* 0x880 - Not affected by Soft Reset */
	u32 _reserved5[24];	/* 0x980 */
	u32 gfwr_mx6;		/* 0x9e0 - MX6 */
	u32 _reserved6[39];	/* 0x9e4 */
	u32 _rxfir[6];		/* 0xa80 */
	u32 _reserved8[2];	/* 0xa98 */
	u32 _rxmgmask;		/* 0xaa0 */
	u32 _rxfgmask;		/* 0xaa4 */
	u32 _rx14mask;		/* 0xaa8 */
	u32 _rx15mask;		/* 0xaac */
	u32 tx_smb[4];		/* 0xab0 */
	u32 rx_smb0[4];		/* 0xac0 */
	u32 rx_smb1[4];		/* 0xad0 */
	u32 mecr;		/* 0xae0 */
	u32 erriar;		/* 0xae4 */
	u32 erridpr;		/* 0xae8 */
	u32 errippr;		/* 0xaec */
	u32 rerrar;		/* 0xaf0 */
	u32 rerrdr;		/* 0xaf4 */
	u32 rerrsynr;		/* 0xaf8 */
	u32 errsr;		/* 0xafc */
	u32 _reserved7[64];	/* 0xb00 */
	u32 fdctrl;		/* 0xc00 - Not affected by Soft Reset */
	u32 fdcbt;		/* 0xc04 - Not affected by Soft Reset */
	u32 fdcrc;		/* 0xc08 */
	u32 _reserved9[199];	/* 0xc0c */
	u32 tx_smb_fd[18];	/* 0xf28 */
	u32 rx_smb0_fd[18];	/* 0xf70 */
	u32 rx_smb1_fd[18];	/* 0xfb8 */
पूर्ण;

अटल_निश्चित(माप(काष्ठा flexcan_regs) ==  0x4 * 18 + 0xfb8);

काष्ठा flexcan_devtype_data अणु
	u32 quirks;		/* quirks needed क्रम dअगरferent IP cores */
पूर्ण;

काष्ठा flexcan_stop_mode अणु
	काष्ठा regmap *gpr;
	u8 req_gpr;
	u8 req_bit;
पूर्ण;

काष्ठा flexcan_priv अणु
	काष्ठा can_priv can;
	काष्ठा can_rx_offload offload;
	काष्ठा device *dev;

	काष्ठा flexcan_regs __iomem *regs;
	काष्ठा flexcan_mb __iomem *tx_mb;
	काष्ठा flexcan_mb __iomem *tx_mb_reserved;
	u8 tx_mb_idx;
	u8 mb_count;
	u8 mb_size;
	u8 clk_src;	/* घड़ी source of CAN Protocol Engine */
	u8 scu_idx;

	u64 rx_mask;
	u64 tx_mask;
	u32 reg_ctrl_शेष;

	काष्ठा clk *clk_ipg;
	काष्ठा clk *clk_per;
	स्थिर काष्ठा flexcan_devtype_data *devtype_data;
	काष्ठा regulator *reg_xceiver;
	काष्ठा flexcan_stop_mode sपंचांग;

	/* IPC handle when setup stop mode by System Controller firmware(scfw) */
	काष्ठा imx_sc_ipc *sc_ipc_handle;

	/* Read and Write APIs */
	u32 (*पढ़ो)(व्योम __iomem *addr);
	व्योम (*ग_लिखो)(u32 val, व्योम __iomem *addr);
पूर्ण;

अटल स्थिर काष्ठा flexcan_devtype_data fsl_p1010_devtype_data = अणु
	.quirks = FLEXCAN_QUIRK_BROKEN_WERR_STATE |
		FLEXCAN_QUIRK_BROKEN_PERR_STATE |
		FLEXCAN_QUIRK_DEFAULT_BIG_ENDIAN,
पूर्ण;

अटल स्थिर काष्ठा flexcan_devtype_data fsl_imx25_devtype_data = अणु
	.quirks = FLEXCAN_QUIRK_BROKEN_WERR_STATE |
		FLEXCAN_QUIRK_BROKEN_PERR_STATE,
पूर्ण;

अटल स्थिर काष्ठा flexcan_devtype_data fsl_imx28_devtype_data = अणु
	.quirks = FLEXCAN_QUIRK_BROKEN_PERR_STATE,
पूर्ण;

अटल स्थिर काष्ठा flexcan_devtype_data fsl_imx6q_devtype_data = अणु
	.quirks = FLEXCAN_QUIRK_DISABLE_RXFG | FLEXCAN_QUIRK_ENABLE_EACEN_RRS |
		FLEXCAN_QUIRK_USE_OFF_TIMESTAMP | FLEXCAN_QUIRK_BROKEN_PERR_STATE |
		FLEXCAN_QUIRK_SETUP_STOP_MODE_GPR,
पूर्ण;

अटल स्थिर काष्ठा flexcan_devtype_data fsl_imx8qm_devtype_data = अणु
	.quirks = FLEXCAN_QUIRK_DISABLE_RXFG | FLEXCAN_QUIRK_ENABLE_EACEN_RRS |
		FLEXCAN_QUIRK_USE_OFF_TIMESTAMP | FLEXCAN_QUIRK_BROKEN_PERR_STATE |
		FLEXCAN_QUIRK_SUPPORT_FD | FLEXCAN_QUIRK_SETUP_STOP_MODE_SCFW,
पूर्ण;

अटल काष्ठा flexcan_devtype_data fsl_imx8mp_devtype_data = अणु
	.quirks = FLEXCAN_QUIRK_DISABLE_RXFG | FLEXCAN_QUIRK_ENABLE_EACEN_RRS |
		FLEXCAN_QUIRK_DISABLE_MECR | FLEXCAN_QUIRK_USE_OFF_TIMESTAMP |
		FLEXCAN_QUIRK_BROKEN_PERR_STATE | FLEXCAN_QUIRK_SETUP_STOP_MODE_GPR |
		FLEXCAN_QUIRK_SUPPORT_FD | FLEXCAN_QUIRK_SUPPORT_ECC,
पूर्ण;

अटल स्थिर काष्ठा flexcan_devtype_data fsl_vf610_devtype_data = अणु
	.quirks = FLEXCAN_QUIRK_DISABLE_RXFG | FLEXCAN_QUIRK_ENABLE_EACEN_RRS |
		FLEXCAN_QUIRK_DISABLE_MECR | FLEXCAN_QUIRK_USE_OFF_TIMESTAMP |
		FLEXCAN_QUIRK_BROKEN_PERR_STATE | FLEXCAN_QUIRK_SUPPORT_ECC,
पूर्ण;

अटल स्थिर काष्ठा flexcan_devtype_data fsl_ls1021a_r2_devtype_data = अणु
	.quirks = FLEXCAN_QUIRK_DISABLE_RXFG | FLEXCAN_QUIRK_ENABLE_EACEN_RRS |
		FLEXCAN_QUIRK_BROKEN_PERR_STATE | FLEXCAN_QUIRK_USE_OFF_TIMESTAMP,
पूर्ण;

अटल स्थिर काष्ठा flexcan_devtype_data fsl_lx2160a_r1_devtype_data = अणु
	.quirks = FLEXCAN_QUIRK_DISABLE_RXFG | FLEXCAN_QUIRK_ENABLE_EACEN_RRS |
		FLEXCAN_QUIRK_DISABLE_MECR | FLEXCAN_QUIRK_BROKEN_PERR_STATE |
		FLEXCAN_QUIRK_USE_OFF_TIMESTAMP | FLEXCAN_QUIRK_SUPPORT_FD |
		FLEXCAN_QUIRK_SUPPORT_ECC,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर flexcan_bittiming_स्थिर = अणु
	.name = DRV_NAME,
	.tseg1_min = 4,
	.tseg1_max = 16,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 256,
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर flexcan_fd_bittiming_स्थिर = अणु
	.name = DRV_NAME,
	.tseg1_min = 2,
	.tseg1_max = 96,
	.tseg2_min = 2,
	.tseg2_max = 32,
	.sjw_max = 16,
	.brp_min = 1,
	.brp_max = 1024,
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर flexcan_fd_data_bittiming_स्थिर = अणु
	.name = DRV_NAME,
	.tseg1_min = 2,
	.tseg1_max = 39,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 1024,
	.brp_inc = 1,
पूर्ण;

/* FlexCAN module is essentially modelled as a little-endian IP in most
 * SoCs, i.e the रेजिस्टरs as well as the message buffer areas are
 * implemented in a little-endian fashion.
 *
 * However there are some SoCs (e.g. LS1021A) which implement the FlexCAN
 * module in a big-endian fashion (i.e the रेजिस्टरs as well as the
 * message buffer areas are implemented in a big-endian way).
 *
 * In addition, the FlexCAN module can be found on SoCs having ARM or
 * PPC cores. So, we need to असलtract off the रेजिस्टर पढ़ो/ग_लिखो
 * functions, ensuring that these cater to all the combinations of module
 * endianness and underlying CPU endianness.
 */
अटल अंतरभूत u32 flexcan_पढ़ो_be(व्योम __iomem *addr)
अणु
	वापस ioपढ़ो32be(addr);
पूर्ण

अटल अंतरभूत व्योम flexcan_ग_लिखो_be(u32 val, व्योम __iomem *addr)
अणु
	ioग_लिखो32be(val, addr);
पूर्ण

अटल अंतरभूत u32 flexcan_पढ़ो_le(व्योम __iomem *addr)
अणु
	वापस ioपढ़ो32(addr);
पूर्ण

अटल अंतरभूत व्योम flexcan_ग_लिखो_le(u32 val, व्योम __iomem *addr)
अणु
	ioग_लिखो32(val, addr);
पूर्ण

अटल काष्ठा flexcan_mb __iomem *flexcan_get_mb(स्थिर काष्ठा flexcan_priv *priv,
						 u8 mb_index)
अणु
	u8 bank_size;
	bool bank;

	अगर (WARN_ON(mb_index >= priv->mb_count))
		वापस शून्य;

	bank_size = माप(priv->regs->mb[0]) / priv->mb_size;

	bank = mb_index >= bank_size;
	अगर (bank)
		mb_index -= bank_size;

	वापस (काष्ठा flexcan_mb __iomem *)
		(&priv->regs->mb[bank][priv->mb_size * mb_index]);
पूर्ण

अटल पूर्णांक flexcan_low_घातer_enter_ack(काष्ठा flexcan_priv *priv)
अणु
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	अचिन्हित पूर्णांक समयout = FLEXCAN_TIMEOUT_US / 10;

	जबतक (समयout-- && !(priv->पढ़ो(&regs->mcr) & FLEXCAN_MCR_LPM_ACK))
		udelay(10);

	अगर (!(priv->पढ़ो(&regs->mcr) & FLEXCAN_MCR_LPM_ACK))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक flexcan_low_घातer_निकास_ack(काष्ठा flexcan_priv *priv)
अणु
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	अचिन्हित पूर्णांक समयout = FLEXCAN_TIMEOUT_US / 10;

	जबतक (समयout-- && (priv->पढ़ो(&regs->mcr) & FLEXCAN_MCR_LPM_ACK))
		udelay(10);

	अगर (priv->पढ़ो(&regs->mcr) & FLEXCAN_MCR_LPM_ACK)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम flexcan_enable_wakeup_irq(काष्ठा flexcan_priv *priv, bool enable)
अणु
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u32 reg_mcr;

	reg_mcr = priv->पढ़ो(&regs->mcr);

	अगर (enable)
		reg_mcr |= FLEXCAN_MCR_WAK_MSK;
	अन्यथा
		reg_mcr &= ~FLEXCAN_MCR_WAK_MSK;

	priv->ग_लिखो(reg_mcr, &regs->mcr);
पूर्ण

अटल पूर्णांक flexcan_stop_mode_enable_scfw(काष्ठा flexcan_priv *priv, bool enabled)
अणु
	u8 idx = priv->scu_idx;
	u32 rsrc_id, val;

	rsrc_id = IMX_SC_R_CAN(idx);

	अगर (enabled)
		val = 1;
	अन्यथा
		val = 0;

	/* stop mode request via scu firmware */
	वापस imx_sc_misc_set_control(priv->sc_ipc_handle, rsrc_id,
				       IMX_SC_C_IPG_STOP, val);
पूर्ण

अटल अंतरभूत पूर्णांक flexcan_enter_stop_mode(काष्ठा flexcan_priv *priv)
अणु
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u32 reg_mcr;
	पूर्णांक ret;

	reg_mcr = priv->पढ़ो(&regs->mcr);
	reg_mcr |= FLEXCAN_MCR_SLF_WAK;
	priv->ग_लिखो(reg_mcr, &regs->mcr);

	/* enable stop request */
	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_SETUP_STOP_MODE_SCFW) अणु
		ret = flexcan_stop_mode_enable_scfw(priv, true);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		regmap_update_bits(priv->sपंचांग.gpr, priv->sपंचांग.req_gpr,
				   1 << priv->sपंचांग.req_bit, 1 << priv->sपंचांग.req_bit);
	पूर्ण

	वापस flexcan_low_घातer_enter_ack(priv);
पूर्ण

अटल अंतरभूत पूर्णांक flexcan_निकास_stop_mode(काष्ठा flexcan_priv *priv)
अणु
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u32 reg_mcr;
	पूर्णांक ret;

	/* हटाओ stop request */
	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_SETUP_STOP_MODE_SCFW) अणु
		ret = flexcan_stop_mode_enable_scfw(priv, false);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		regmap_update_bits(priv->sपंचांग.gpr, priv->sपंचांग.req_gpr,
				   1 << priv->sपंचांग.req_bit, 0);
	पूर्ण

	reg_mcr = priv->पढ़ो(&regs->mcr);
	reg_mcr &= ~FLEXCAN_MCR_SLF_WAK;
	priv->ग_लिखो(reg_mcr, &regs->mcr);

	वापस flexcan_low_घातer_निकास_ack(priv);
पूर्ण

अटल अंतरभूत व्योम flexcan_error_irq_enable(स्थिर काष्ठा flexcan_priv *priv)
अणु
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u32 reg_ctrl = (priv->reg_ctrl_शेष | FLEXCAN_CTRL_ERR_MSK);

	priv->ग_लिखो(reg_ctrl, &regs->ctrl);
पूर्ण

अटल अंतरभूत व्योम flexcan_error_irq_disable(स्थिर काष्ठा flexcan_priv *priv)
अणु
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u32 reg_ctrl = (priv->reg_ctrl_शेष & ~FLEXCAN_CTRL_ERR_MSK);

	priv->ग_लिखो(reg_ctrl, &regs->ctrl);
पूर्ण

अटल पूर्णांक flexcan_clks_enable(स्थिर काष्ठा flexcan_priv *priv)
अणु
	पूर्णांक err;

	err = clk_prepare_enable(priv->clk_ipg);
	अगर (err)
		वापस err;

	err = clk_prepare_enable(priv->clk_per);
	अगर (err)
		clk_disable_unprepare(priv->clk_ipg);

	वापस err;
पूर्ण

अटल व्योम flexcan_clks_disable(स्थिर काष्ठा flexcan_priv *priv)
अणु
	clk_disable_unprepare(priv->clk_per);
	clk_disable_unprepare(priv->clk_ipg);
पूर्ण

अटल अंतरभूत पूर्णांक flexcan_transceiver_enable(स्थिर काष्ठा flexcan_priv *priv)
अणु
	अगर (!priv->reg_xceiver)
		वापस 0;

	वापस regulator_enable(priv->reg_xceiver);
पूर्ण

अटल अंतरभूत पूर्णांक flexcan_transceiver_disable(स्थिर काष्ठा flexcan_priv *priv)
अणु
	अगर (!priv->reg_xceiver)
		वापस 0;

	वापस regulator_disable(priv->reg_xceiver);
पूर्ण

अटल पूर्णांक flexcan_chip_enable(काष्ठा flexcan_priv *priv)
अणु
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u32 reg;

	reg = priv->पढ़ो(&regs->mcr);
	reg &= ~FLEXCAN_MCR_MDIS;
	priv->ग_लिखो(reg, &regs->mcr);

	वापस flexcan_low_घातer_निकास_ack(priv);
पूर्ण

अटल पूर्णांक flexcan_chip_disable(काष्ठा flexcan_priv *priv)
अणु
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u32 reg;

	reg = priv->पढ़ो(&regs->mcr);
	reg |= FLEXCAN_MCR_MDIS;
	priv->ग_लिखो(reg, &regs->mcr);

	वापस flexcan_low_घातer_enter_ack(priv);
पूर्ण

अटल पूर्णांक flexcan_chip_मुक्तze(काष्ठा flexcan_priv *priv)
अणु
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	अचिन्हित पूर्णांक समयout;
	u32 bitrate = priv->can.bittiming.bitrate;
	u32 reg;

	अगर (bitrate)
		समयout = 1000 * 1000 * 10 / bitrate;
	अन्यथा
		समयout = FLEXCAN_TIMEOUT_US / 10;

	reg = priv->पढ़ो(&regs->mcr);
	reg |= FLEXCAN_MCR_FRZ | FLEXCAN_MCR_HALT;
	priv->ग_लिखो(reg, &regs->mcr);

	जबतक (समयout-- && !(priv->पढ़ो(&regs->mcr) & FLEXCAN_MCR_FRZ_ACK))
		udelay(100);

	अगर (!(priv->पढ़ो(&regs->mcr) & FLEXCAN_MCR_FRZ_ACK))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक flexcan_chip_unमुक्तze(काष्ठा flexcan_priv *priv)
अणु
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	अचिन्हित पूर्णांक समयout = FLEXCAN_TIMEOUT_US / 10;
	u32 reg;

	reg = priv->पढ़ो(&regs->mcr);
	reg &= ~FLEXCAN_MCR_HALT;
	priv->ग_लिखो(reg, &regs->mcr);

	जबतक (समयout-- && (priv->पढ़ो(&regs->mcr) & FLEXCAN_MCR_FRZ_ACK))
		udelay(10);

	अगर (priv->पढ़ो(&regs->mcr) & FLEXCAN_MCR_FRZ_ACK)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक flexcan_chip_softreset(काष्ठा flexcan_priv *priv)
अणु
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	अचिन्हित पूर्णांक समयout = FLEXCAN_TIMEOUT_US / 10;

	priv->ग_लिखो(FLEXCAN_MCR_SOFTRST, &regs->mcr);
	जबतक (समयout-- && (priv->पढ़ो(&regs->mcr) & FLEXCAN_MCR_SOFTRST))
		udelay(10);

	अगर (priv->पढ़ो(&regs->mcr) & FLEXCAN_MCR_SOFTRST)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक __flexcan_get_berr_counter(स्थिर काष्ठा net_device *dev,
				      काष्ठा can_berr_counter *bec)
अणु
	स्थिर काष्ठा flexcan_priv *priv = netdev_priv(dev);
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u32 reg = priv->पढ़ो(&regs->ecr);

	bec->txerr = (reg >> 0) & 0xff;
	bec->rxerr = (reg >> 8) & 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक flexcan_get_berr_counter(स्थिर काष्ठा net_device *dev,
				    काष्ठा can_berr_counter *bec)
अणु
	स्थिर काष्ठा flexcan_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	err = pm_runसमय_get_sync(priv->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_noidle(priv->dev);
		वापस err;
	पूर्ण

	err = __flexcan_get_berr_counter(dev, bec);

	pm_runसमय_put(priv->dev);

	वापस err;
पूर्ण

अटल netdev_tx_t flexcan_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा flexcan_priv *priv = netdev_priv(dev);
	काष्ठा canfd_frame *cfd = (काष्ठा canfd_frame *)skb->data;
	u32 can_id;
	u32 data;
	u32 ctrl = FLEXCAN_MB_CODE_TX_DATA | ((can_fd_len2dlc(cfd->len)) << 16);
	पूर्णांक i;

	अगर (can_dropped_invalid_skb(dev, skb))
		वापस NETDEV_TX_OK;

	netअगर_stop_queue(dev);

	अगर (cfd->can_id & CAN_EFF_FLAG) अणु
		can_id = cfd->can_id & CAN_EFF_MASK;
		ctrl |= FLEXCAN_MB_CNT_IDE | FLEXCAN_MB_CNT_SRR;
	पूर्ण अन्यथा अणु
		can_id = (cfd->can_id & CAN_SFF_MASK) << 18;
	पूर्ण

	अगर (cfd->can_id & CAN_RTR_FLAG)
		ctrl |= FLEXCAN_MB_CNT_RTR;

	अगर (can_is_canfd_skb(skb)) अणु
		ctrl |= FLEXCAN_MB_CNT_EDL;

		अगर (cfd->flags & CANFD_BRS)
			ctrl |= FLEXCAN_MB_CNT_BRS;
	पूर्ण

	क्रम (i = 0; i < cfd->len; i += माप(u32)) अणु
		data = be32_to_cpup((__be32 *)&cfd->data[i]);
		priv->ग_लिखो(data, &priv->tx_mb->data[i / माप(u32)]);
	पूर्ण

	can_put_echo_skb(skb, dev, 0, 0);

	priv->ग_लिखो(can_id, &priv->tx_mb->can_id);
	priv->ग_लिखो(ctrl, &priv->tx_mb->can_ctrl);

	/* Errata ERR005829 step8:
	 * Write twice INACTIVE(0x8) code to first MB.
	 */
	priv->ग_लिखो(FLEXCAN_MB_CODE_TX_INACTIVE,
		    &priv->tx_mb_reserved->can_ctrl);
	priv->ग_लिखो(FLEXCAN_MB_CODE_TX_INACTIVE,
		    &priv->tx_mb_reserved->can_ctrl);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम flexcan_irq_bus_err(काष्ठा net_device *dev, u32 reg_esr)
अणु
	काष्ठा flexcan_priv *priv = netdev_priv(dev);
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf;
	bool rx_errors = false, tx_errors = false;
	u32 बारtamp;
	पूर्णांक err;

	बारtamp = priv->पढ़ो(&regs->समयr) << 16;

	skb = alloc_can_err_skb(dev, &cf);
	अगर (unlikely(!skb))
		वापस;

	cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;

	अगर (reg_esr & FLEXCAN_ESR_BIT1_ERR) अणु
		netdev_dbg(dev, "BIT1_ERR irq\n");
		cf->data[2] |= CAN_ERR_PROT_BIT1;
		tx_errors = true;
	पूर्ण
	अगर (reg_esr & FLEXCAN_ESR_BIT0_ERR) अणु
		netdev_dbg(dev, "BIT0_ERR irq\n");
		cf->data[2] |= CAN_ERR_PROT_BIT0;
		tx_errors = true;
	पूर्ण
	अगर (reg_esr & FLEXCAN_ESR_ACK_ERR) अणु
		netdev_dbg(dev, "ACK_ERR irq\n");
		cf->can_id |= CAN_ERR_ACK;
		cf->data[3] = CAN_ERR_PROT_LOC_ACK;
		tx_errors = true;
	पूर्ण
	अगर (reg_esr & FLEXCAN_ESR_CRC_ERR) अणु
		netdev_dbg(dev, "CRC_ERR irq\n");
		cf->data[2] |= CAN_ERR_PROT_BIT;
		cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;
		rx_errors = true;
	पूर्ण
	अगर (reg_esr & FLEXCAN_ESR_FRM_ERR) अणु
		netdev_dbg(dev, "FRM_ERR irq\n");
		cf->data[2] |= CAN_ERR_PROT_FORM;
		rx_errors = true;
	पूर्ण
	अगर (reg_esr & FLEXCAN_ESR_STF_ERR) अणु
		netdev_dbg(dev, "STF_ERR irq\n");
		cf->data[2] |= CAN_ERR_PROT_STUFF;
		rx_errors = true;
	पूर्ण

	priv->can.can_stats.bus_error++;
	अगर (rx_errors)
		dev->stats.rx_errors++;
	अगर (tx_errors)
		dev->stats.tx_errors++;

	err = can_rx_offload_queue_sorted(&priv->offload, skb, बारtamp);
	अगर (err)
		dev->stats.rx_fअगरo_errors++;
पूर्ण

अटल व्योम flexcan_irq_state(काष्ठा net_device *dev, u32 reg_esr)
अणु
	काष्ठा flexcan_priv *priv = netdev_priv(dev);
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf;
	क्रमागत can_state new_state, rx_state, tx_state;
	पूर्णांक flt;
	काष्ठा can_berr_counter bec;
	u32 बारtamp;
	पूर्णांक err;

	flt = reg_esr & FLEXCAN_ESR_FLT_CONF_MASK;
	अगर (likely(flt == FLEXCAN_ESR_FLT_CONF_ACTIVE)) अणु
		tx_state = unlikely(reg_esr & FLEXCAN_ESR_TX_WRN) ?
			CAN_STATE_ERROR_WARNING : CAN_STATE_ERROR_ACTIVE;
		rx_state = unlikely(reg_esr & FLEXCAN_ESR_RX_WRN) ?
			CAN_STATE_ERROR_WARNING : CAN_STATE_ERROR_ACTIVE;
		new_state = max(tx_state, rx_state);
	पूर्ण अन्यथा अणु
		__flexcan_get_berr_counter(dev, &bec);
		new_state = flt == FLEXCAN_ESR_FLT_CONF_PASSIVE ?
			CAN_STATE_ERROR_PASSIVE : CAN_STATE_BUS_OFF;
		rx_state = bec.rxerr >= bec.txerr ? new_state : 0;
		tx_state = bec.rxerr <= bec.txerr ? new_state : 0;
	पूर्ण

	/* state hasn't changed */
	अगर (likely(new_state == priv->can.state))
		वापस;

	बारtamp = priv->पढ़ो(&regs->समयr) << 16;

	skb = alloc_can_err_skb(dev, &cf);
	अगर (unlikely(!skb))
		वापस;

	can_change_state(dev, cf, tx_state, rx_state);

	अगर (unlikely(new_state == CAN_STATE_BUS_OFF))
		can_bus_off(dev);

	err = can_rx_offload_queue_sorted(&priv->offload, skb, बारtamp);
	अगर (err)
		dev->stats.rx_fअगरo_errors++;
पूर्ण

अटल अंतरभूत u64 flexcan_पढ़ो64_mask(काष्ठा flexcan_priv *priv, व्योम __iomem *addr, u64 mask)
अणु
	u64 reg = 0;

	अगर (upper_32_bits(mask))
		reg = (u64)priv->पढ़ो(addr - 4) << 32;
	अगर (lower_32_bits(mask))
		reg |= priv->पढ़ो(addr);

	वापस reg & mask;
पूर्ण

अटल अंतरभूत व्योम flexcan_ग_लिखो64(काष्ठा flexcan_priv *priv, u64 val, व्योम __iomem *addr)
अणु
	अगर (upper_32_bits(val))
		priv->ग_लिखो(upper_32_bits(val), addr - 4);
	अगर (lower_32_bits(val))
		priv->ग_लिखो(lower_32_bits(val), addr);
पूर्ण

अटल अंतरभूत u64 flexcan_पढ़ो_reg_अगरlag_rx(काष्ठा flexcan_priv *priv)
अणु
	वापस flexcan_पढ़ो64_mask(priv, &priv->regs->अगरlag1, priv->rx_mask);
पूर्ण

अटल अंतरभूत u64 flexcan_पढ़ो_reg_अगरlag_tx(काष्ठा flexcan_priv *priv)
अणु
	वापस flexcan_पढ़ो64_mask(priv, &priv->regs->अगरlag1, priv->tx_mask);
पूर्ण

अटल अंतरभूत काष्ठा flexcan_priv *rx_offload_to_priv(काष्ठा can_rx_offload *offload)
अणु
	वापस container_of(offload, काष्ठा flexcan_priv, offload);
पूर्ण

अटल काष्ठा sk_buff *flexcan_mailbox_पढ़ो(काष्ठा can_rx_offload *offload,
					    अचिन्हित पूर्णांक n, u32 *बारtamp,
					    bool drop)
अणु
	काष्ठा flexcan_priv *priv = rx_offload_to_priv(offload);
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	काष्ठा flexcan_mb __iomem *mb;
	काष्ठा sk_buff *skb;
	काष्ठा canfd_frame *cfd;
	u32 reg_ctrl, reg_id, reg_अगरlag1;
	पूर्णांक i;

	अगर (unlikely(drop)) अणु
		skb = ERR_PTR(-ENOBUFS);
		जाओ mark_as_पढ़ो;
	पूर्ण

	mb = flexcan_get_mb(priv, n);

	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_USE_OFF_TIMESTAMP) अणु
		u32 code;

		करो अणु
			reg_ctrl = priv->पढ़ो(&mb->can_ctrl);
		पूर्ण जबतक (reg_ctrl & FLEXCAN_MB_CODE_RX_BUSY_BIT);

		/* is this MB empty? */
		code = reg_ctrl & FLEXCAN_MB_CODE_MASK;
		अगर ((code != FLEXCAN_MB_CODE_RX_FULL) &&
		    (code != FLEXCAN_MB_CODE_RX_OVERRUN))
			वापस शून्य;

		अगर (code == FLEXCAN_MB_CODE_RX_OVERRUN) अणु
			/* This MB was overrun, we lost data */
			offload->dev->stats.rx_over_errors++;
			offload->dev->stats.rx_errors++;
		पूर्ण
	पूर्ण अन्यथा अणु
		reg_अगरlag1 = priv->पढ़ो(&regs->अगरlag1);
		अगर (!(reg_अगरlag1 & FLEXCAN_IFLAG_RX_FIFO_AVAILABLE))
			वापस शून्य;

		reg_ctrl = priv->पढ़ो(&mb->can_ctrl);
	पूर्ण

	अगर (reg_ctrl & FLEXCAN_MB_CNT_EDL)
		skb = alloc_canfd_skb(offload->dev, &cfd);
	अन्यथा
		skb = alloc_can_skb(offload->dev, (काष्ठा can_frame **)&cfd);
	अगर (unlikely(!skb)) अणु
		skb = ERR_PTR(-ENOMEM);
		जाओ mark_as_पढ़ो;
	पूर्ण

	/* increase timstamp to full 32 bit */
	*बारtamp = reg_ctrl << 16;

	reg_id = priv->पढ़ो(&mb->can_id);
	अगर (reg_ctrl & FLEXCAN_MB_CNT_IDE)
		cfd->can_id = ((reg_id >> 0) & CAN_EFF_MASK) | CAN_EFF_FLAG;
	अन्यथा
		cfd->can_id = (reg_id >> 18) & CAN_SFF_MASK;

	अगर (reg_ctrl & FLEXCAN_MB_CNT_EDL) अणु
		cfd->len = can_fd_dlc2len((reg_ctrl >> 16) & 0xf);

		अगर (reg_ctrl & FLEXCAN_MB_CNT_BRS)
			cfd->flags |= CANFD_BRS;
	पूर्ण अन्यथा अणु
		cfd->len = can_cc_dlc2len((reg_ctrl >> 16) & 0xf);

		अगर (reg_ctrl & FLEXCAN_MB_CNT_RTR)
			cfd->can_id |= CAN_RTR_FLAG;
	पूर्ण

	अगर (reg_ctrl & FLEXCAN_MB_CNT_ESI)
		cfd->flags |= CANFD_ESI;

	क्रम (i = 0; i < cfd->len; i += माप(u32)) अणु
		__be32 data = cpu_to_be32(priv->पढ़ो(&mb->data[i / माप(u32)]));
		*(__be32 *)(cfd->data + i) = data;
	पूर्ण

 mark_as_पढ़ो:
	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_USE_OFF_TIMESTAMP)
		flexcan_ग_लिखो64(priv, FLEXCAN_IFLAG_MB(n), &regs->अगरlag1);
	अन्यथा
		priv->ग_लिखो(FLEXCAN_IFLAG_RX_FIFO_AVAILABLE, &regs->अगरlag1);

	/* Read the Free Running Timer. It is optional but recommended
	 * to unlock Mailbox as soon as possible and make it available
	 * क्रम reception.
	 */
	priv->पढ़ो(&regs->समयr);

	वापस skb;
पूर्ण

अटल irqवापस_t flexcan_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा flexcan_priv *priv = netdev_priv(dev);
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	irqवापस_t handled = IRQ_NONE;
	u64 reg_अगरlag_tx;
	u32 reg_esr;
	क्रमागत can_state last_state = priv->can.state;

	/* reception पूर्णांकerrupt */
	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_USE_OFF_TIMESTAMP) अणु
		u64 reg_अगरlag_rx;
		पूर्णांक ret;

		जबतक ((reg_अगरlag_rx = flexcan_पढ़ो_reg_अगरlag_rx(priv))) अणु
			handled = IRQ_HANDLED;
			ret = can_rx_offload_irq_offload_बारtamp(&priv->offload,
								   reg_अगरlag_rx);
			अगर (!ret)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		u32 reg_अगरlag1;

		reg_अगरlag1 = priv->पढ़ो(&regs->अगरlag1);
		अगर (reg_अगरlag1 & FLEXCAN_IFLAG_RX_FIFO_AVAILABLE) अणु
			handled = IRQ_HANDLED;
			can_rx_offload_irq_offload_fअगरo(&priv->offload);
		पूर्ण

		/* FIFO overflow पूर्णांकerrupt */
		अगर (reg_अगरlag1 & FLEXCAN_IFLAG_RX_FIFO_OVERFLOW) अणु
			handled = IRQ_HANDLED;
			priv->ग_लिखो(FLEXCAN_IFLAG_RX_FIFO_OVERFLOW,
				    &regs->अगरlag1);
			dev->stats.rx_over_errors++;
			dev->stats.rx_errors++;
		पूर्ण
	पूर्ण

	reg_अगरlag_tx = flexcan_पढ़ो_reg_अगरlag_tx(priv);

	/* transmission complete पूर्णांकerrupt */
	अगर (reg_अगरlag_tx & priv->tx_mask) अणु
		u32 reg_ctrl = priv->पढ़ो(&priv->tx_mb->can_ctrl);

		handled = IRQ_HANDLED;
		stats->tx_bytes +=
			can_rx_offload_get_echo_skb(&priv->offload, 0,
						    reg_ctrl << 16, शून्य);
		stats->tx_packets++;
		can_led_event(dev, CAN_LED_EVENT_TX);

		/* after sending a RTR frame MB is in RX mode */
		priv->ग_लिखो(FLEXCAN_MB_CODE_TX_INACTIVE,
			    &priv->tx_mb->can_ctrl);
		flexcan_ग_लिखो64(priv, priv->tx_mask, &regs->अगरlag1);
		netअगर_wake_queue(dev);
	पूर्ण

	reg_esr = priv->पढ़ो(&regs->esr);

	/* ACK all bus error, state change and wake IRQ sources */
	अगर (reg_esr & (FLEXCAN_ESR_ALL_INT | FLEXCAN_ESR_WAK_INT)) अणु
		handled = IRQ_HANDLED;
		priv->ग_लिखो(reg_esr & (FLEXCAN_ESR_ALL_INT | FLEXCAN_ESR_WAK_INT), &regs->esr);
	पूर्ण

	/* state change पूर्णांकerrupt or broken error state quirk fix is enabled */
	अगर ((reg_esr & FLEXCAN_ESR_ERR_STATE) ||
	    (priv->devtype_data->quirks & (FLEXCAN_QUIRK_BROKEN_WERR_STATE |
					   FLEXCAN_QUIRK_BROKEN_PERR_STATE)))
		flexcan_irq_state(dev, reg_esr);

	/* bus error IRQ - handle अगर bus error reporting is activated */
	अगर ((reg_esr & FLEXCAN_ESR_ERR_BUS) &&
	    (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING))
		flexcan_irq_bus_err(dev, reg_esr);

	/* availability of error पूर्णांकerrupt among state transitions in हाल
	 * bus error reporting is de-activated and
	 * FLEXCAN_QUIRK_BROKEN_PERR_STATE is enabled:
	 *  +--------------------------------------------------------------+
	 *  | +----------------------------------------------+ [stopped /  |
	 *  | |                                              |  sleeping] -+
	 *  +-+-> active <-> warning <-> passive -> bus off -+
	 *        ___________^^^^^^^^^^^^_______________________________
	 *        disabled(1)  enabled             disabled
	 *
	 * (1): enabled अगर FLEXCAN_QUIRK_BROKEN_WERR_STATE is enabled
	 */
	अगर ((last_state != priv->can.state) &&
	    (priv->devtype_data->quirks & FLEXCAN_QUIRK_BROKEN_PERR_STATE) &&
	    !(priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING)) अणु
		चयन (priv->can.state) अणु
		हाल CAN_STATE_ERROR_ACTIVE:
			अगर (priv->devtype_data->quirks &
			    FLEXCAN_QUIRK_BROKEN_WERR_STATE)
				flexcan_error_irq_enable(priv);
			अन्यथा
				flexcan_error_irq_disable(priv);
			अवरोध;

		हाल CAN_STATE_ERROR_WARNING:
			flexcan_error_irq_enable(priv);
			अवरोध;

		हाल CAN_STATE_ERROR_PASSIVE:
		हाल CAN_STATE_BUS_OFF:
			flexcan_error_irq_disable(priv);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस handled;
पूर्ण

अटल व्योम flexcan_set_bittiming_ctrl(स्थिर काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा flexcan_priv *priv = netdev_priv(dev);
	स्थिर काष्ठा can_bittiming *bt = &priv->can.bittiming;
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u32 reg;

	reg = priv->पढ़ो(&regs->ctrl);
	reg &= ~(FLEXCAN_CTRL_PRESDIV(0xff) |
		 FLEXCAN_CTRL_RJW(0x3) |
		 FLEXCAN_CTRL_PSEG1(0x7) |
		 FLEXCAN_CTRL_PSEG2(0x7) |
		 FLEXCAN_CTRL_PROPSEG(0x7));

	reg |= FLEXCAN_CTRL_PRESDIV(bt->brp - 1) |
		FLEXCAN_CTRL_PSEG1(bt->phase_seg1 - 1) |
		FLEXCAN_CTRL_PSEG2(bt->phase_seg2 - 1) |
		FLEXCAN_CTRL_RJW(bt->sjw - 1) |
		FLEXCAN_CTRL_PROPSEG(bt->prop_seg - 1);

	netdev_dbg(dev, "writing ctrl=0x%08x\n", reg);
	priv->ग_लिखो(reg, &regs->ctrl);

	/* prपूर्णांक chip status */
	netdev_dbg(dev, "%s: mcr=0x%08x ctrl=0x%08x\n", __func__,
		   priv->पढ़ो(&regs->mcr), priv->पढ़ो(&regs->ctrl));
पूर्ण

अटल व्योम flexcan_set_bittiming_cbt(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा flexcan_priv *priv = netdev_priv(dev);
	काष्ठा can_bittiming *bt = &priv->can.bittiming;
	काष्ठा can_bittiming *dbt = &priv->can.data_bittiming;
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u32 reg_cbt, reg_fdctrl;

	/* CBT */
	/* CBT[EPSEG1] is 5 bit दीर्घ and CBT[EPROPSEG] is 6 bit
	 * दीर्घ. The can_calc_bittiming() tries to भागide the tseg1
	 * equally between phase_seg1 and prop_seg, which may not fit
	 * in CBT रेजिस्टर. Thereक्रमe, अगर phase_seg1 is more than
	 * possible value, increase prop_seg and decrease phase_seg1.
	 */
	अगर (bt->phase_seg1 > 0x20) अणु
		bt->prop_seg += (bt->phase_seg1 - 0x20);
		bt->phase_seg1 = 0x20;
	पूर्ण

	reg_cbt = FLEXCAN_CBT_BTF |
		FIELD_PREP(FLEXCAN_CBT_EPRESDIV_MASK, bt->brp - 1) |
		FIELD_PREP(FLEXCAN_CBT_ERJW_MASK, bt->sjw - 1) |
		FIELD_PREP(FLEXCAN_CBT_EPROPSEG_MASK, bt->prop_seg - 1) |
		FIELD_PREP(FLEXCAN_CBT_EPSEG1_MASK, bt->phase_seg1 - 1) |
		FIELD_PREP(FLEXCAN_CBT_EPSEG2_MASK, bt->phase_seg2 - 1);

	netdev_dbg(dev, "writing cbt=0x%08x\n", reg_cbt);
	priv->ग_लिखो(reg_cbt, &regs->cbt);

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD) अणु
		u32 reg_fdcbt, reg_ctrl2;

		अगर (bt->brp != dbt->brp)
			netdev_warn(dev, "Data brp=%d and brp=%d don't match, this may result in a phase error. Consider using different bitrate and/or data bitrate.\n",
				    dbt->brp, bt->brp);

		/* FDCBT */
		/* FDCBT[FPSEG1] is 3 bit दीर्घ and FDCBT[FPROPSEG] is
		 * 5 bit दीर्घ. The can_calc_bittiming tries to भागide
		 * the tseg1 equally between phase_seg1 and prop_seg,
		 * which may not fit in FDCBT रेजिस्टर. Thereक्रमe, अगर
		 * phase_seg1 is more than possible value, increase
		 * prop_seg and decrease phase_seg1
		 */
		अगर (dbt->phase_seg1 > 0x8) अणु
			dbt->prop_seg += (dbt->phase_seg1 - 0x8);
			dbt->phase_seg1 = 0x8;
		पूर्ण

		reg_fdcbt = priv->पढ़ो(&regs->fdcbt);
		reg_fdcbt &= ~(FIELD_PREP(FLEXCAN_FDCBT_FPRESDIV_MASK, 0x3ff) |
			       FIELD_PREP(FLEXCAN_FDCBT_FRJW_MASK, 0x7) |
			       FIELD_PREP(FLEXCAN_FDCBT_FPROPSEG_MASK, 0x1f) |
			       FIELD_PREP(FLEXCAN_FDCBT_FPSEG1_MASK, 0x7) |
			       FIELD_PREP(FLEXCAN_FDCBT_FPSEG2_MASK, 0x7));

		reg_fdcbt |= FIELD_PREP(FLEXCAN_FDCBT_FPRESDIV_MASK, dbt->brp - 1) |
			FIELD_PREP(FLEXCAN_FDCBT_FRJW_MASK, dbt->sjw - 1) |
			FIELD_PREP(FLEXCAN_FDCBT_FPROPSEG_MASK, dbt->prop_seg) |
			FIELD_PREP(FLEXCAN_FDCBT_FPSEG1_MASK, dbt->phase_seg1 - 1) |
			FIELD_PREP(FLEXCAN_FDCBT_FPSEG2_MASK, dbt->phase_seg2 - 1);

		netdev_dbg(dev, "writing fdcbt=0x%08x\n", reg_fdcbt);
		priv->ग_लिखो(reg_fdcbt, &regs->fdcbt);

		/* CTRL2 */
		reg_ctrl2 = priv->पढ़ो(&regs->ctrl2);
		reg_ctrl2 &= ~FLEXCAN_CTRL2_ISOCANFDEN;
		अगर (!(priv->can.ctrlmode & CAN_CTRLMODE_FD_NON_ISO))
			reg_ctrl2 |= FLEXCAN_CTRL2_ISOCANFDEN;

		netdev_dbg(dev, "writing ctrl2=0x%08x\n", reg_ctrl2);
		priv->ग_लिखो(reg_ctrl2, &regs->ctrl2);
	पूर्ण

	/* FDCTRL */
	reg_fdctrl = priv->पढ़ो(&regs->fdctrl);
	reg_fdctrl &= ~(FLEXCAN_FDCTRL_FDRATE |
			FIELD_PREP(FLEXCAN_FDCTRL_TDCOFF, 0x1f));

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD) अणु
		reg_fdctrl |= FLEXCAN_FDCTRL_FDRATE;

		अगर (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK) अणु
			/* TDC must be disabled क्रम Loop Back mode */
			reg_fdctrl &= ~FLEXCAN_FDCTRL_TDCEN;
		पूर्ण अन्यथा अणु
			reg_fdctrl |= FLEXCAN_FDCTRL_TDCEN |
				FIELD_PREP(FLEXCAN_FDCTRL_TDCOFF,
					   ((dbt->phase_seg1 - 1) +
					    dbt->prop_seg + 2) *
					   ((dbt->brp - 1 ) + 1));
		पूर्ण
	पूर्ण

	netdev_dbg(dev, "writing fdctrl=0x%08x\n", reg_fdctrl);
	priv->ग_लिखो(reg_fdctrl, &regs->fdctrl);

	netdev_dbg(dev, "%s: mcr=0x%08x ctrl=0x%08x ctrl2=0x%08x fdctrl=0x%08x cbt=0x%08x fdcbt=0x%08x\n",
		   __func__,
		   priv->पढ़ो(&regs->mcr), priv->पढ़ो(&regs->ctrl),
		   priv->पढ़ो(&regs->ctrl2), priv->पढ़ो(&regs->fdctrl),
		   priv->पढ़ो(&regs->cbt), priv->पढ़ो(&regs->fdcbt));
पूर्ण

अटल व्योम flexcan_set_bittiming(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा flexcan_priv *priv = netdev_priv(dev);
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u32 reg;

	reg = priv->पढ़ो(&regs->ctrl);
	reg &= ~(FLEXCAN_CTRL_LPB | FLEXCAN_CTRL_SMP |
		 FLEXCAN_CTRL_LOM);

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		reg |= FLEXCAN_CTRL_LPB;
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		reg |= FLEXCAN_CTRL_LOM;
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		reg |= FLEXCAN_CTRL_SMP;

	netdev_dbg(dev, "writing ctrl=0x%08x\n", reg);
	priv->ग_लिखो(reg, &regs->ctrl);

	अगर (priv->can.ctrlmode_supported & CAN_CTRLMODE_FD)
		वापस flexcan_set_bittiming_cbt(dev);
	अन्यथा
		वापस flexcan_set_bittiming_ctrl(dev);
पूर्ण

अटल व्योम flexcan_ram_init(काष्ठा net_device *dev)
अणु
	काष्ठा flexcan_priv *priv = netdev_priv(dev);
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u32 reg_ctrl2;

	/* 11.8.3.13 Detection and correction of memory errors:
	 * CTRL2[WRMFRZ] grants ग_लिखो access to all memory positions
	 * that require initialization, ranging from 0x080 to 0xADF
	 * and from 0xF28 to 0xFFF when the CAN FD feature is enabled.
	 * The RXMGMASK, RX14MASK, RX15MASK, and RXFGMASK रेजिस्टरs
	 * need to be initialized as well. MCR[RFEN] must not be set
	 * during memory initialization.
	 */
	reg_ctrl2 = priv->पढ़ो(&regs->ctrl2);
	reg_ctrl2 |= FLEXCAN_CTRL2_WRMFRZ;
	priv->ग_लिखो(reg_ctrl2, &regs->ctrl2);

	स_रखो_io(&regs->mb[0][0], 0,
		  दुरत्व(काष्ठा flexcan_regs, rx_smb1[3]) -
		  दुरत्व(काष्ठा flexcan_regs, mb[0][0]) + 0x4);

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD)
		स_रखो_io(&regs->tx_smb_fd[0], 0,
			  दुरत्व(काष्ठा flexcan_regs, rx_smb1_fd[17]) -
			  दुरत्व(काष्ठा flexcan_regs, tx_smb_fd[0]) + 0x4);

	reg_ctrl2 &= ~FLEXCAN_CTRL2_WRMFRZ;
	priv->ग_लिखो(reg_ctrl2, &regs->ctrl2);
पूर्ण

अटल पूर्णांक flexcan_rx_offload_setup(काष्ठा net_device *dev)
अणु
	काष्ठा flexcan_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD)
		priv->mb_size = माप(काष्ठा flexcan_mb) + CANFD_MAX_DLEN;
	अन्यथा
		priv->mb_size = माप(काष्ठा flexcan_mb) + CAN_MAX_DLEN;
	priv->mb_count = (माप(priv->regs->mb[0]) / priv->mb_size) +
			 (माप(priv->regs->mb[1]) / priv->mb_size);

	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_USE_OFF_TIMESTAMP)
		priv->tx_mb_reserved =
			flexcan_get_mb(priv, FLEXCAN_TX_MB_RESERVED_OFF_TIMESTAMP);
	अन्यथा
		priv->tx_mb_reserved =
			flexcan_get_mb(priv, FLEXCAN_TX_MB_RESERVED_OFF_FIFO);
	priv->tx_mb_idx = priv->mb_count - 1;
	priv->tx_mb = flexcan_get_mb(priv, priv->tx_mb_idx);
	priv->tx_mask = FLEXCAN_IFLAG_MB(priv->tx_mb_idx);

	priv->offload.mailbox_पढ़ो = flexcan_mailbox_पढ़ो;

	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_USE_OFF_TIMESTAMP) अणु
		priv->offload.mb_first = FLEXCAN_RX_MB_OFF_TIMESTAMP_FIRST;
		priv->offload.mb_last = priv->mb_count - 2;

		priv->rx_mask = GENMASK_ULL(priv->offload.mb_last,
					    priv->offload.mb_first);
		err = can_rx_offload_add_बारtamp(dev, &priv->offload);
	पूर्ण अन्यथा अणु
		priv->rx_mask = FLEXCAN_IFLAG_RX_FIFO_OVERFLOW |
			FLEXCAN_IFLAG_RX_FIFO_AVAILABLE;
		err = can_rx_offload_add_fअगरo(dev, &priv->offload,
					      FLEXCAN_NAPI_WEIGHT);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम flexcan_chip_पूर्णांकerrupts_enable(स्थिर काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा flexcan_priv *priv = netdev_priv(dev);
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u64 reg_imask;

	disable_irq(dev->irq);
	priv->ग_लिखो(priv->reg_ctrl_शेष, &regs->ctrl);
	reg_imask = priv->rx_mask | priv->tx_mask;
	priv->ग_लिखो(upper_32_bits(reg_imask), &regs->imask2);
	priv->ग_लिखो(lower_32_bits(reg_imask), &regs->imask1);
	enable_irq(dev->irq);
पूर्ण

अटल व्योम flexcan_chip_पूर्णांकerrupts_disable(स्थिर काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा flexcan_priv *priv = netdev_priv(dev);
	काष्ठा flexcan_regs __iomem *regs = priv->regs;

	priv->ग_लिखो(0, &regs->imask2);
	priv->ग_लिखो(0, &regs->imask1);
	priv->ग_लिखो(priv->reg_ctrl_शेष & ~FLEXCAN_CTRL_ERR_ALL,
		    &regs->ctrl);
पूर्ण

/* flexcan_chip_start
 *
 * this functions is entered with घड़ीs enabled
 *
 */
अटल पूर्णांक flexcan_chip_start(काष्ठा net_device *dev)
अणु
	काष्ठा flexcan_priv *priv = netdev_priv(dev);
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u32 reg_mcr, reg_ctrl, reg_ctrl2, reg_mecr;
	पूर्णांक err, i;
	काष्ठा flexcan_mb __iomem *mb;

	/* enable module */
	err = flexcan_chip_enable(priv);
	अगर (err)
		वापस err;

	/* soft reset */
	err = flexcan_chip_softreset(priv);
	अगर (err)
		जाओ out_chip_disable;

	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_SUPPORT_ECC)
		flexcan_ram_init(dev);

	flexcan_set_bittiming(dev);

	/* set मुक्तze, halt */
	err = flexcan_chip_मुक्तze(priv);
	अगर (err)
		जाओ out_chip_disable;

	/* MCR
	 *
	 * only supervisor access
	 * enable warning पूर्णांक
	 * enable inभागidual RX masking
	 * choose क्रमmat C
	 * set max mailbox number
	 */
	reg_mcr = priv->पढ़ो(&regs->mcr);
	reg_mcr &= ~FLEXCAN_MCR_MAXMB(0xff);
	reg_mcr |= FLEXCAN_MCR_SUPV | FLEXCAN_MCR_WRN_EN | FLEXCAN_MCR_IRMQ |
		FLEXCAN_MCR_IDAM_C | FLEXCAN_MCR_MAXMB(priv->tx_mb_idx);

	/* MCR
	 *
	 * FIFO:
	 * - disable क्रम बारtamp mode
	 * - enable क्रम FIFO mode
	 */
	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_USE_OFF_TIMESTAMP)
		reg_mcr &= ~FLEXCAN_MCR_FEN;
	अन्यथा
		reg_mcr |= FLEXCAN_MCR_FEN;

	/* MCR
	 *
	 * NOTE: In loopback mode, the CAN_MCR[SRXDIS] cannot be
	 *       निश्चितed because this will impede the self reception
	 *       of a transmitted message. This is not करोcumented in
	 *       earlier versions of flexcan block guide.
	 *
	 * Self Reception:
	 * - enable Self Reception क्रम loopback mode
	 *   (by clearing "Self Reception Disable" bit)
	 * - disable क्रम normal operation
	 */
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		reg_mcr &= ~FLEXCAN_MCR_SRX_DIS;
	अन्यथा
		reg_mcr |= FLEXCAN_MCR_SRX_DIS;

	/* MCR - CAN-FD */
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD)
		reg_mcr |= FLEXCAN_MCR_FDEN;
	अन्यथा
		reg_mcr &= ~FLEXCAN_MCR_FDEN;

	netdev_dbg(dev, "%s: writing mcr=0x%08x", __func__, reg_mcr);
	priv->ग_लिखो(reg_mcr, &regs->mcr);

	/* CTRL
	 *
	 * disable समयr sync feature
	 *
	 * disable स्वतः busoff recovery
	 * transmit lowest buffer first
	 *
	 * enable tx and rx warning पूर्णांकerrupt
	 * enable bus off पूर्णांकerrupt
	 * (== FLEXCAN_CTRL_ERR_STATE)
	 */
	reg_ctrl = priv->पढ़ो(&regs->ctrl);
	reg_ctrl &= ~FLEXCAN_CTRL_TSYN;
	reg_ctrl |= FLEXCAN_CTRL_BOFF_REC | FLEXCAN_CTRL_LBUF |
		FLEXCAN_CTRL_ERR_STATE;

	/* enable the "error interrupt" (FLEXCAN_CTRL_ERR_MSK),
	 * on most Flexcan cores, too. Otherwise we करोn't get
	 * any error warning or passive पूर्णांकerrupts.
	 */
	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_BROKEN_WERR_STATE ||
	    priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING)
		reg_ctrl |= FLEXCAN_CTRL_ERR_MSK;
	अन्यथा
		reg_ctrl &= ~FLEXCAN_CTRL_ERR_MSK;

	/* save क्रम later use */
	priv->reg_ctrl_शेष = reg_ctrl;
	/* leave पूर्णांकerrupts disabled क्रम now */
	reg_ctrl &= ~FLEXCAN_CTRL_ERR_ALL;
	netdev_dbg(dev, "%s: writing ctrl=0x%08x", __func__, reg_ctrl);
	priv->ग_लिखो(reg_ctrl, &regs->ctrl);

	अगर ((priv->devtype_data->quirks & FLEXCAN_QUIRK_ENABLE_EACEN_RRS)) अणु
		reg_ctrl2 = priv->पढ़ो(&regs->ctrl2);
		reg_ctrl2 |= FLEXCAN_CTRL2_EACEN | FLEXCAN_CTRL2_RRS;
		priv->ग_लिखो(reg_ctrl2, &regs->ctrl2);
	पूर्ण

	अगर (priv->can.ctrlmode_supported & CAN_CTRLMODE_FD) अणु
		u32 reg_fdctrl;

		reg_fdctrl = priv->पढ़ो(&regs->fdctrl);
		reg_fdctrl &= ~(FIELD_PREP(FLEXCAN_FDCTRL_MBDSR1, 0x3) |
				FIELD_PREP(FLEXCAN_FDCTRL_MBDSR0, 0x3));

		अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD) अणु
			reg_fdctrl |=
				FIELD_PREP(FLEXCAN_FDCTRL_MBDSR1,
					   FLEXCAN_FDCTRL_MBDSR_64) |
				FIELD_PREP(FLEXCAN_FDCTRL_MBDSR0,
					   FLEXCAN_FDCTRL_MBDSR_64);
		पूर्ण अन्यथा अणु
			reg_fdctrl |=
				FIELD_PREP(FLEXCAN_FDCTRL_MBDSR1,
					   FLEXCAN_FDCTRL_MBDSR_8) |
				FIELD_PREP(FLEXCAN_FDCTRL_MBDSR0,
					   FLEXCAN_FDCTRL_MBDSR_8);
		पूर्ण

		netdev_dbg(dev, "%s: writing fdctrl=0x%08x",
			   __func__, reg_fdctrl);
		priv->ग_लिखो(reg_fdctrl, &regs->fdctrl);
	पूर्ण

	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_USE_OFF_TIMESTAMP) अणु
		क्रम (i = priv->offload.mb_first; i <= priv->offload.mb_last; i++) अणु
			mb = flexcan_get_mb(priv, i);
			priv->ग_लिखो(FLEXCAN_MB_CODE_RX_EMPTY,
				    &mb->can_ctrl);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* clear and invalidate unused mailboxes first */
		क्रम (i = FLEXCAN_TX_MB_RESERVED_OFF_FIFO; i < priv->mb_count; i++) अणु
			mb = flexcan_get_mb(priv, i);
			priv->ग_लिखो(FLEXCAN_MB_CODE_RX_INACTIVE,
				    &mb->can_ctrl);
		पूर्ण
	पूर्ण

	/* Errata ERR005829: mark first TX mailbox as INACTIVE */
	priv->ग_लिखो(FLEXCAN_MB_CODE_TX_INACTIVE,
		    &priv->tx_mb_reserved->can_ctrl);

	/* mark TX mailbox as INACTIVE */
	priv->ग_लिखो(FLEXCAN_MB_CODE_TX_INACTIVE,
		    &priv->tx_mb->can_ctrl);

	/* acceptance mask/acceptance code (accept everything) */
	priv->ग_लिखो(0x0, &regs->rxgmask);
	priv->ग_लिखो(0x0, &regs->rx14mask);
	priv->ग_लिखो(0x0, &regs->rx15mask);

	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_DISABLE_RXFG)
		priv->ग_लिखो(0x0, &regs->rxfgmask);

	/* clear acceptance filters */
	क्रम (i = 0; i < priv->mb_count; i++)
		priv->ग_लिखो(0, &regs->rximr[i]);

	/* On Vybrid, disable non-correctable errors पूर्णांकerrupt and
	 * मुक्तze mode. It still can correct the correctable errors
	 * when HW supports ECC.
	 *
	 * This also works around errata e5295 which generates false
	 * positive memory errors and put the device in मुक्तze mode.
	 */
	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_DISABLE_MECR) अणु
		/* Follow the protocol as described in "Detection
		 * and Correction of Memory Errors" to ग_लिखो to
		 * MECR रेजिस्टर (step 1 - 5)
		 *
		 * 1. By शेष, CTRL2[ECRWRE] = 0, MECR[ECRWRDIS] = 1
		 * 2. set CTRL2[ECRWRE]
		 */
		reg_ctrl2 = priv->पढ़ो(&regs->ctrl2);
		reg_ctrl2 |= FLEXCAN_CTRL2_ECRWRE;
		priv->ग_लिखो(reg_ctrl2, &regs->ctrl2);

		/* 3. clear MECR[ECRWRDIS] */
		reg_mecr = priv->पढ़ो(&regs->mecr);
		reg_mecr &= ~FLEXCAN_MECR_ECRWRDIS;
		priv->ग_लिखो(reg_mecr, &regs->mecr);

		/* 4. all ग_लिखोs to MECR must keep MECR[ECRWRDIS] cleared */
		reg_mecr &= ~(FLEXCAN_MECR_NCEFAFRZ | FLEXCAN_MECR_HANCEI_MSK |
			      FLEXCAN_MECR_FANCEI_MSK);
		priv->ग_लिखो(reg_mecr, &regs->mecr);

		/* 5. after configuration करोne, lock MECR by either
		 * setting MECR[ECRWRDIS] or clearing CTRL2[ECRWRE]
		 */
		reg_mecr |= FLEXCAN_MECR_ECRWRDIS;
		priv->ग_लिखो(reg_mecr, &regs->mecr);

		reg_ctrl2 &= ~FLEXCAN_CTRL2_ECRWRE;
		priv->ग_लिखो(reg_ctrl2, &regs->ctrl2);
	पूर्ण

	/* synchronize with the can bus */
	err = flexcan_chip_unमुक्तze(priv);
	अगर (err)
		जाओ out_chip_disable;

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	/* prपूर्णांक chip status */
	netdev_dbg(dev, "%s: reading mcr=0x%08x ctrl=0x%08x\n", __func__,
		   priv->पढ़ो(&regs->mcr), priv->पढ़ो(&regs->ctrl));

	वापस 0;

 out_chip_disable:
	flexcan_chip_disable(priv);
	वापस err;
पूर्ण

/* __flexcan_chip_stop
 *
 * this function is entered with घड़ीs enabled
 */
अटल पूर्णांक __flexcan_chip_stop(काष्ठा net_device *dev, bool disable_on_error)
अणु
	काष्ठा flexcan_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	/* मुक्तze + disable module */
	err = flexcan_chip_मुक्तze(priv);
	अगर (err && !disable_on_error)
		वापस err;
	err = flexcan_chip_disable(priv);
	अगर (err && !disable_on_error)
		जाओ out_chip_unमुक्तze;

	priv->can.state = CAN_STATE_STOPPED;

	वापस 0;

 out_chip_unमुक्तze:
	flexcan_chip_unमुक्तze(priv);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक flexcan_chip_stop_disable_on_error(काष्ठा net_device *dev)
अणु
	वापस __flexcan_chip_stop(dev, true);
पूर्ण

अटल अंतरभूत पूर्णांक flexcan_chip_stop(काष्ठा net_device *dev)
अणु
	वापस __flexcan_chip_stop(dev, false);
पूर्ण

अटल पूर्णांक flexcan_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा flexcan_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	अगर ((priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES) &&
	    (priv->can.ctrlmode & CAN_CTRLMODE_FD)) अणु
		netdev_err(dev, "Three Samples mode and CAN-FD mode can't be used together\n");
		वापस -EINVAL;
	पूर्ण

	err = pm_runसमय_get_sync(priv->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_noidle(priv->dev);
		वापस err;
	पूर्ण

	err = खोलो_candev(dev);
	अगर (err)
		जाओ out_runसमय_put;

	err = flexcan_transceiver_enable(priv);
	अगर (err)
		जाओ out_बंद;

	err = flexcan_rx_offload_setup(dev);
	अगर (err)
		जाओ out_transceiver_disable;

	err = flexcan_chip_start(dev);
	अगर (err)
		जाओ out_can_rx_offload_del;

	can_rx_offload_enable(&priv->offload);

	err = request_irq(dev->irq, flexcan_irq, IRQF_SHARED, dev->name, dev);
	अगर (err)
		जाओ out_can_rx_offload_disable;

	flexcan_chip_पूर्णांकerrupts_enable(dev);

	can_led_event(dev, CAN_LED_EVENT_OPEN);

	netअगर_start_queue(dev);

	वापस 0;

 out_can_rx_offload_disable:
	can_rx_offload_disable(&priv->offload);
	flexcan_chip_stop(dev);
 out_can_rx_offload_del:
	can_rx_offload_del(&priv->offload);
 out_transceiver_disable:
	flexcan_transceiver_disable(priv);
 out_बंद:
	बंद_candev(dev);
 out_runसमय_put:
	pm_runसमय_put(priv->dev);

	वापस err;
पूर्ण

अटल पूर्णांक flexcan_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा flexcan_priv *priv = netdev_priv(dev);

	netअगर_stop_queue(dev);
	flexcan_chip_पूर्णांकerrupts_disable(dev);
	मुक्त_irq(dev->irq, dev);
	can_rx_offload_disable(&priv->offload);
	flexcan_chip_stop_disable_on_error(dev);

	can_rx_offload_del(&priv->offload);
	flexcan_transceiver_disable(priv);
	बंद_candev(dev);

	pm_runसमय_put(priv->dev);

	can_led_event(dev, CAN_LED_EVENT_STOP);

	वापस 0;
पूर्ण

अटल पूर्णांक flexcan_set_mode(काष्ठा net_device *dev, क्रमागत can_mode mode)
अणु
	पूर्णांक err;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		err = flexcan_chip_start(dev);
		अगर (err)
			वापस err;

		flexcan_chip_पूर्णांकerrupts_enable(dev);

		netअगर_wake_queue(dev);
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops flexcan_netdev_ops = अणु
	.nकरो_खोलो	= flexcan_खोलो,
	.nकरो_stop	= flexcan_बंद,
	.nकरो_start_xmit	= flexcan_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल पूर्णांक रेजिस्टर_flexcandev(काष्ठा net_device *dev)
अणु
	काष्ठा flexcan_priv *priv = netdev_priv(dev);
	काष्ठा flexcan_regs __iomem *regs = priv->regs;
	u32 reg, err;

	err = flexcan_clks_enable(priv);
	अगर (err)
		वापस err;

	/* select "bus clock", chip must be disabled */
	err = flexcan_chip_disable(priv);
	अगर (err)
		जाओ out_clks_disable;

	reg = priv->पढ़ो(&regs->ctrl);
	अगर (priv->clk_src)
		reg |= FLEXCAN_CTRL_CLK_SRC;
	अन्यथा
		reg &= ~FLEXCAN_CTRL_CLK_SRC;
	priv->ग_लिखो(reg, &regs->ctrl);

	err = flexcan_chip_enable(priv);
	अगर (err)
		जाओ out_chip_disable;

	/* set मुक्तze, halt */
	err = flexcan_chip_मुक्तze(priv);
	अगर (err)
		जाओ out_chip_disable;

	/* activate FIFO, restrict रेजिस्टर access */
	reg = priv->पढ़ो(&regs->mcr);
	reg |=  FLEXCAN_MCR_FEN | FLEXCAN_MCR_SUPV;
	priv->ग_लिखो(reg, &regs->mcr);

	/* Currently we only support newer versions of this core
	 * featuring a RX hardware FIFO (although this driver करोesn't
	 * make use of it on some cores). Older cores, found on some
	 * Coldfire derivates are not tested.
	 */
	reg = priv->पढ़ो(&regs->mcr);
	अगर (!(reg & FLEXCAN_MCR_FEN)) अणु
		netdev_err(dev, "Could not enable RX FIFO, unsupported core\n");
		err = -ENODEV;
		जाओ out_chip_disable;
	पूर्ण

	err = रेजिस्टर_candev(dev);
	अगर (err)
		जाओ out_chip_disable;

	/* Disable core and let pm_runसमय_put() disable the घड़ीs.
	 * If CONFIG_PM is not enabled, the घड़ीs will stay घातered.
	 */
	flexcan_chip_disable(priv);
	pm_runसमय_put(priv->dev);

	वापस 0;

 out_chip_disable:
	flexcan_chip_disable(priv);
 out_clks_disable:
	flexcan_clks_disable(priv);
	वापस err;
पूर्ण

अटल व्योम unरेजिस्टर_flexcandev(काष्ठा net_device *dev)
अणु
	unरेजिस्टर_candev(dev);
पूर्ण

अटल पूर्णांक flexcan_setup_stop_mode_gpr(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *gpr_np;
	काष्ठा flexcan_priv *priv;
	phandle phandle;
	u32 out_val[3];
	पूर्णांक ret;

	अगर (!np)
		वापस -EINVAL;

	/* stop mode property क्रमmat is:
	 * <&gpr req_gpr req_bit>.
	 */
	ret = of_property_पढ़ो_u32_array(np, "fsl,stop-mode", out_val,
					 ARRAY_SIZE(out_val));
	अगर (ret) अणु
		dev_dbg(&pdev->dev, "no stop-mode property\n");
		वापस ret;
	पूर्ण
	phandle = *out_val;

	gpr_np = of_find_node_by_phandle(phandle);
	अगर (!gpr_np) अणु
		dev_dbg(&pdev->dev, "could not find gpr node by phandle\n");
		वापस -ENODEV;
	पूर्ण

	priv = netdev_priv(dev);
	priv->sपंचांग.gpr = syscon_node_to_regmap(gpr_np);
	अगर (IS_ERR(priv->sपंचांग.gpr)) अणु
		dev_dbg(&pdev->dev, "could not find gpr regmap\n");
		ret = PTR_ERR(priv->sपंचांग.gpr);
		जाओ out_put_node;
	पूर्ण

	priv->sपंचांग.req_gpr = out_val[1];
	priv->sपंचांग.req_bit = out_val[2];

	dev_dbg(&pdev->dev,
		"gpr %s req_gpr=0x02%x req_bit=%u\n",
		gpr_np->full_name, priv->sपंचांग.req_gpr, priv->sपंचांग.req_bit);

	वापस 0;

out_put_node:
	of_node_put(gpr_np);
	वापस ret;
पूर्ण

अटल पूर्णांक flexcan_setup_stop_mode_scfw(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा flexcan_priv *priv;
	u8 scu_idx;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u8(pdev->dev.of_node, "fsl,scu-index", &scu_idx);
	अगर (ret < 0) अणु
		dev_dbg(&pdev->dev, "failed to get scu index\n");
		वापस ret;
	पूर्ण

	priv = netdev_priv(dev);
	priv->scu_idx = scu_idx;

	/* this function could be deferred probe, वापस -EPROBE_DEFER */
	वापस imx_scu_get_handle(&priv->sc_ipc_handle);
पूर्ण

/* flexcan_setup_stop_mode - Setup stop mode क्रम wakeup
 *
 * Return: = 0 setup stop mode successfully or करोesn't support this feature
 *         < 0 fail to setup stop mode (could be deferred probe)
 */
अटल पूर्णांक flexcan_setup_stop_mode(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा flexcan_priv *priv;
	पूर्णांक ret;

	priv = netdev_priv(dev);

	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_SETUP_STOP_MODE_SCFW)
		ret = flexcan_setup_stop_mode_scfw(pdev);
	अन्यथा अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_SETUP_STOP_MODE_GPR)
		ret = flexcan_setup_stop_mode_gpr(pdev);
	अन्यथा
		/* वापस 0 directly अगर करोesn't support stop mode feature */
		वापस 0;

	अगर (ret)
		वापस ret;

	device_set_wakeup_capable(&pdev->dev, true);

	अगर (of_property_पढ़ो_bool(pdev->dev.of_node, "wakeup-source"))
		device_set_wakeup_enable(&pdev->dev, true);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id flexcan_of_match[] = अणु
	अणु .compatible = "fsl,imx8qm-flexcan", .data = &fsl_imx8qm_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx8mp-flexcan", .data = &fsl_imx8mp_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx6q-flexcan", .data = &fsl_imx6q_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx28-flexcan", .data = &fsl_imx28_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx53-flexcan", .data = &fsl_imx25_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx35-flexcan", .data = &fsl_imx25_devtype_data, पूर्ण,
	अणु .compatible = "fsl,imx25-flexcan", .data = &fsl_imx25_devtype_data, पूर्ण,
	अणु .compatible = "fsl,p1010-flexcan", .data = &fsl_p1010_devtype_data, पूर्ण,
	अणु .compatible = "fsl,vf610-flexcan", .data = &fsl_vf610_devtype_data, पूर्ण,
	अणु .compatible = "fsl,ls1021ar2-flexcan", .data = &fsl_ls1021a_r2_devtype_data, पूर्ण,
	अणु .compatible = "fsl,lx2160ar1-flexcan", .data = &fsl_lx2160a_r1_devtype_data, पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, flexcan_of_match);

अटल पूर्णांक flexcan_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा flexcan_devtype_data *devtype_data;
	काष्ठा net_device *dev;
	काष्ठा flexcan_priv *priv;
	काष्ठा regulator *reg_xceiver;
	काष्ठा clk *clk_ipg = शून्य, *clk_per = शून्य;
	काष्ठा flexcan_regs __iomem *regs;
	पूर्णांक err, irq;
	u8 clk_src = 1;
	u32 घड़ी_freq = 0;

	reg_xceiver = devm_regulator_get_optional(&pdev->dev, "xceiver");
	अगर (PTR_ERR(reg_xceiver) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अन्यथा अगर (PTR_ERR(reg_xceiver) == -ENODEV)
		reg_xceiver = शून्य;
	अन्यथा अगर (IS_ERR(reg_xceiver))
		वापस PTR_ERR(reg_xceiver);

	अगर (pdev->dev.of_node) अणु
		of_property_पढ़ो_u32(pdev->dev.of_node,
				     "clock-frequency", &घड़ी_freq);
		of_property_पढ़ो_u8(pdev->dev.of_node,
				    "fsl,clk-source", &clk_src);
	पूर्ण

	अगर (!घड़ी_freq) अणु
		clk_ipg = devm_clk_get(&pdev->dev, "ipg");
		अगर (IS_ERR(clk_ipg)) अणु
			dev_err(&pdev->dev, "no ipg clock defined\n");
			वापस PTR_ERR(clk_ipg);
		पूर्ण

		clk_per = devm_clk_get(&pdev->dev, "per");
		अगर (IS_ERR(clk_per)) अणु
			dev_err(&pdev->dev, "no per clock defined\n");
			वापस PTR_ERR(clk_per);
		पूर्ण
		घड़ी_freq = clk_get_rate(clk_per);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस -ENODEV;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	devtype_data = of_device_get_match_data(&pdev->dev);

	अगर ((devtype_data->quirks & FLEXCAN_QUIRK_SUPPORT_FD) &&
	    !(devtype_data->quirks & FLEXCAN_QUIRK_USE_OFF_TIMESTAMP)) अणु
		dev_err(&pdev->dev, "CAN-FD mode doesn't work with FIFO mode!\n");
		वापस -EINVAL;
	पूर्ण

	dev = alloc_candev(माप(काष्ठा flexcan_priv), 1);
	अगर (!dev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	dev->netdev_ops = &flexcan_netdev_ops;
	dev->irq = irq;
	dev->flags |= IFF_ECHO;

	priv = netdev_priv(dev);

	अगर (of_property_पढ़ो_bool(pdev->dev.of_node, "big-endian") ||
	    devtype_data->quirks & FLEXCAN_QUIRK_DEFAULT_BIG_ENDIAN) अणु
		priv->पढ़ो = flexcan_पढ़ो_be;
		priv->ग_लिखो = flexcan_ग_लिखो_be;
	पूर्ण अन्यथा अणु
		priv->पढ़ो = flexcan_पढ़ो_le;
		priv->ग_लिखो = flexcan_ग_लिखो_le;
	पूर्ण

	priv->dev = &pdev->dev;
	priv->can.घड़ी.freq = घड़ी_freq;
	priv->can.करो_set_mode = flexcan_set_mode;
	priv->can.करो_get_berr_counter = flexcan_get_berr_counter;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_LOOPBACK |
		CAN_CTRLMODE_LISTENONLY	| CAN_CTRLMODE_3_SAMPLES |
		CAN_CTRLMODE_BERR_REPORTING;
	priv->regs = regs;
	priv->clk_ipg = clk_ipg;
	priv->clk_per = clk_per;
	priv->clk_src = clk_src;
	priv->devtype_data = devtype_data;
	priv->reg_xceiver = reg_xceiver;

	अगर (priv->devtype_data->quirks & FLEXCAN_QUIRK_SUPPORT_FD) अणु
		priv->can.ctrlmode_supported |= CAN_CTRLMODE_FD |
			CAN_CTRLMODE_FD_NON_ISO;
		priv->can.bittiming_स्थिर = &flexcan_fd_bittiming_स्थिर;
		priv->can.data_bittiming_स्थिर =
			&flexcan_fd_data_bittiming_स्थिर;
	पूर्ण अन्यथा अणु
		priv->can.bittiming_स्थिर = &flexcan_bittiming_स्थिर;
	पूर्ण

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	err = रेजिस्टर_flexcandev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "registering netdev failed\n");
		जाओ failed_रेजिस्टर;
	पूर्ण

	err = flexcan_setup_stop_mode(pdev);
	अगर (err < 0) अणु
		अगर (err != -EPROBE_DEFER)
			dev_err(&pdev->dev, "setup stop mode failed\n");
		जाओ failed_setup_stop_mode;
	पूर्ण

	of_can_transceiver(dev);
	devm_can_led_init(dev);

	वापस 0;

 failed_setup_stop_mode:
	unरेजिस्टर_flexcandev(dev);
 failed_रेजिस्टर:
	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	मुक्त_candev(dev);
	वापस err;
पूर्ण

अटल पूर्णांक flexcan_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);

	device_set_wakeup_enable(&pdev->dev, false);
	device_set_wakeup_capable(&pdev->dev, false);
	unरेजिस्टर_flexcandev(dev);
	pm_runसमय_disable(&pdev->dev);
	मुक्त_candev(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused flexcan_suspend(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा flexcan_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	अगर (netअगर_running(dev)) अणु
		/* अगर wakeup is enabled, enter stop mode
		 * अन्यथा enter disabled mode.
		 */
		अगर (device_may_wakeup(device)) अणु
			enable_irq_wake(dev->irq);
			err = flexcan_enter_stop_mode(priv);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			err = flexcan_chip_stop(dev);
			अगर (err)
				वापस err;

			flexcan_chip_पूर्णांकerrupts_disable(dev);

			err = pinctrl_pm_select_sleep_state(device);
			अगर (err)
				वापस err;
		पूर्ण
		netअगर_stop_queue(dev);
		netअगर_device_detach(dev);
	पूर्ण
	priv->can.state = CAN_STATE_SLEEPING;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused flexcan_resume(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा flexcan_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	priv->can.state = CAN_STATE_ERROR_ACTIVE;
	अगर (netअगर_running(dev)) अणु
		netअगर_device_attach(dev);
		netअगर_start_queue(dev);
		अगर (device_may_wakeup(device)) अणु
			disable_irq_wake(dev->irq);
			err = flexcan_निकास_stop_mode(priv);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			err = pinctrl_pm_select_शेष_state(device);
			अगर (err)
				वापस err;

			err = flexcan_chip_start(dev);
			अगर (err)
				वापस err;

			flexcan_chip_पूर्णांकerrupts_enable(dev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused flexcan_runसमय_suspend(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा flexcan_priv *priv = netdev_priv(dev);

	flexcan_clks_disable(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused flexcan_runसमय_resume(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा flexcan_priv *priv = netdev_priv(dev);

	वापस flexcan_clks_enable(priv);
पूर्ण

अटल पूर्णांक __maybe_unused flexcan_noirq_suspend(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा flexcan_priv *priv = netdev_priv(dev);

	अगर (netअगर_running(dev)) अणु
		पूर्णांक err;

		अगर (device_may_wakeup(device))
			flexcan_enable_wakeup_irq(priv, true);

		err = pm_runसमय_क्रमce_suspend(device);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused flexcan_noirq_resume(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा flexcan_priv *priv = netdev_priv(dev);

	अगर (netअगर_running(dev)) अणु
		पूर्णांक err;

		err = pm_runसमय_क्रमce_resume(device);
		अगर (err)
			वापस err;

		अगर (device_may_wakeup(device))
			flexcan_enable_wakeup_irq(priv, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops flexcan_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(flexcan_suspend, flexcan_resume)
	SET_RUNTIME_PM_OPS(flexcan_runसमय_suspend, flexcan_runसमय_resume, शून्य)
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(flexcan_noirq_suspend, flexcan_noirq_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver flexcan_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &flexcan_pm_ops,
		.of_match_table = flexcan_of_match,
	पूर्ण,
	.probe = flexcan_probe,
	.हटाओ = flexcan_हटाओ,
पूर्ण;

module_platक्रमm_driver(flexcan_driver);

MODULE_AUTHOR("Sascha Hauer <kernel@pengutronix.de>, "
	      "Marc Kleine-Budde <kernel@pengutronix.de>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("CAN port driver for flexcan based chip");
