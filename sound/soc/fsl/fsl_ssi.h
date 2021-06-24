<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fsl_ssi.h - ALSA SSI पूर्णांकerface क्रम the Freescale MPC8610 and i.MX SoC
 *
 * Author: Timur Tabi <timur@मुक्तscale.com>
 *
 * Copyright 2007-2008 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित _MPC8610_I2S_H
#घोषणा _MPC8610_I2S_H

/* -- SSI Register Map -- */

/* SSI Transmit Data Register 0 */
#घोषणा REG_SSI_STX0			0x00
/* SSI Transmit Data Register 1 */
#घोषणा REG_SSI_STX1			0x04
/* SSI Receive Data Register 0 */
#घोषणा REG_SSI_SRX0			0x08
/* SSI Receive Data Register 1 */
#घोषणा REG_SSI_SRX1			0x0c
/* SSI Control Register */
#घोषणा REG_SSI_SCR			0x10
/* SSI Interrupt Status Register */
#घोषणा REG_SSI_SISR			0x14
/* SSI Interrupt Enable Register */
#घोषणा REG_SSI_SIER			0x18
/* SSI Transmit Configuration Register */
#घोषणा REG_SSI_STCR			0x1c
/* SSI Receive Configuration Register */
#घोषणा REG_SSI_SRCR			0x20
#घोषणा REG_SSI_SxCR(tx)		((tx) ? REG_SSI_STCR : REG_SSI_SRCR)
/* SSI Transmit Clock Control Register */
#घोषणा REG_SSI_STCCR			0x24
/* SSI Receive Clock Control Register */
#घोषणा REG_SSI_SRCCR			0x28
#घोषणा REG_SSI_SxCCR(tx)		((tx) ? REG_SSI_STCCR : REG_SSI_SRCCR)
/* SSI FIFO Control/Status Register */
#घोषणा REG_SSI_SFCSR			0x2c
/*
 * SSI Test Register (Intended क्रम debugging purposes only)
 *
 * Note: STR is not करोcumented in recent IMX datasheet, but
 * is described in IMX51 reference manual at section 56.3.3.14
 */
#घोषणा REG_SSI_STR			0x30
/*
 * SSI Option Register (Intended क्रम पूर्णांकernal use only)
 *
 * Note: SOR is not करोcumented in recent IMX datasheet, but
 * is described in IMX51 reference manual at section 56.3.3.15
 */
#घोषणा REG_SSI_SOR			0x34
/* SSI AC97 Control Register */
#घोषणा REG_SSI_SACNT			0x38
/* SSI AC97 Command Address Register */
#घोषणा REG_SSI_SACADD			0x3c
/* SSI AC97 Command Data Register */
#घोषणा REG_SSI_SACDAT			0x40
/* SSI AC97 Tag Register */
#घोषणा REG_SSI_SATAG			0x44
/* SSI Transmit Time Slot Mask Register */
#घोषणा REG_SSI_STMSK			0x48
/* SSI  Receive Time Slot Mask Register */
#घोषणा REG_SSI_SRMSK			0x4c
#घोषणा REG_SSI_SxMSK(tx)		((tx) ? REG_SSI_STMSK : REG_SSI_SRMSK)
/*
 * SSI AC97 Channel Status Register
 *
 * The status could be changed by:
 * 1) Writing a '1' bit at some position in SACCEN sets relevant bit in SACCST
 * 2) Writing a '1' bit at some position in SACCDIS unsets the relevant bit
 * 3) Receivng a '1' in SLOTREQ bit from बाह्यal CODEC via AC Link
 */
#घोषणा REG_SSI_SACCST			0x50
/* SSI AC97 Channel Enable Register -- Set bits in SACCST */
#घोषणा REG_SSI_SACCEN			0x54
/* SSI AC97 Channel Disable Register -- Clear bits in SACCST */
#घोषणा REG_SSI_SACCDIS			0x58

/* -- SSI Register Field Maps -- */

/* SSI Control Register -- REG_SSI_SCR 0x10 */
#घोषणा SSI_SCR_SYNC_TX_FS		0x00001000
#घोषणा SSI_SCR_RFR_CLK_DIS		0x00000800
#घोषणा SSI_SCR_TFR_CLK_DIS		0x00000400
#घोषणा SSI_SCR_TCH_EN			0x00000100
#घोषणा SSI_SCR_SYS_CLK_EN		0x00000080
#घोषणा SSI_SCR_I2S_MODE_MASK		0x00000060
#घोषणा SSI_SCR_I2S_MODE_NORMAL		0x00000000
#घोषणा SSI_SCR_I2S_MODE_MASTER		0x00000020
#घोषणा SSI_SCR_I2S_MODE_SLAVE		0x00000040
#घोषणा SSI_SCR_SYN			0x00000010
#घोषणा SSI_SCR_NET			0x00000008
#घोषणा SSI_SCR_I2S_NET_MASK		(SSI_SCR_NET | SSI_SCR_I2S_MODE_MASK)
#घोषणा SSI_SCR_RE			0x00000004
#घोषणा SSI_SCR_TE			0x00000002
#घोषणा SSI_SCR_SSIEN			0x00000001

/* SSI Interrupt Status Register -- REG_SSI_SISR 0x14 */
#घोषणा SSI_SISR_RFRC			0x01000000
#घोषणा SSI_SISR_TFRC			0x00800000
#घोषणा SSI_SISR_CMDAU			0x00040000
#घोषणा SSI_SISR_CMDDU			0x00020000
#घोषणा SSI_SISR_RXT			0x00010000
#घोषणा SSI_SISR_RDR1			0x00008000
#घोषणा SSI_SISR_RDR0			0x00004000
#घोषणा SSI_SISR_TDE1			0x00002000
#घोषणा SSI_SISR_TDE0			0x00001000
#घोषणा SSI_SISR_ROE1			0x00000800
#घोषणा SSI_SISR_ROE0			0x00000400
#घोषणा SSI_SISR_TUE1			0x00000200
#घोषणा SSI_SISR_TUE0			0x00000100
#घोषणा SSI_SISR_TFS			0x00000080
#घोषणा SSI_SISR_RFS			0x00000040
#घोषणा SSI_SISR_TLS			0x00000020
#घोषणा SSI_SISR_RLS			0x00000010
#घोषणा SSI_SISR_RFF1			0x00000008
#घोषणा SSI_SISR_RFF0			0x00000004
#घोषणा SSI_SISR_TFE1			0x00000002
#घोषणा SSI_SISR_TFE0			0x00000001

/* SSI Interrupt Enable Register -- REG_SSI_SIER 0x18 */
#घोषणा SSI_SIER_RFRC_EN		0x01000000
#घोषणा SSI_SIER_TFRC_EN		0x00800000
#घोषणा SSI_SIER_RDMAE			0x00400000
#घोषणा SSI_SIER_RIE			0x00200000
#घोषणा SSI_SIER_TDMAE			0x00100000
#घोषणा SSI_SIER_TIE			0x00080000
#घोषणा SSI_SIER_CMDAU_EN		0x00040000
#घोषणा SSI_SIER_CMDDU_EN		0x00020000
#घोषणा SSI_SIER_RXT_EN			0x00010000
#घोषणा SSI_SIER_RDR1_EN		0x00008000
#घोषणा SSI_SIER_RDR0_EN		0x00004000
#घोषणा SSI_SIER_TDE1_EN		0x00002000
#घोषणा SSI_SIER_TDE0_EN		0x00001000
#घोषणा SSI_SIER_ROE1_EN		0x00000800
#घोषणा SSI_SIER_ROE0_EN		0x00000400
#घोषणा SSI_SIER_TUE1_EN		0x00000200
#घोषणा SSI_SIER_TUE0_EN		0x00000100
#घोषणा SSI_SIER_TFS_EN			0x00000080
#घोषणा SSI_SIER_RFS_EN			0x00000040
#घोषणा SSI_SIER_TLS_EN			0x00000020
#घोषणा SSI_SIER_RLS_EN			0x00000010
#घोषणा SSI_SIER_RFF1_EN		0x00000008
#घोषणा SSI_SIER_RFF0_EN		0x00000004
#घोषणा SSI_SIER_TFE1_EN		0x00000002
#घोषणा SSI_SIER_TFE0_EN		0x00000001

/* SSI Transmit Configuration Register -- REG_SSI_STCR 0x1C */
#घोषणा SSI_STCR_TXBIT0			0x00000200
#घोषणा SSI_STCR_TFEN1			0x00000100
#घोषणा SSI_STCR_TFEN0			0x00000080
#घोषणा SSI_STCR_TFसूची			0x00000040
#घोषणा SSI_STCR_TXसूची			0x00000020
#घोषणा SSI_STCR_TSHFD			0x00000010
#घोषणा SSI_STCR_TSCKP			0x00000008
#घोषणा SSI_STCR_TFSI			0x00000004
#घोषणा SSI_STCR_TFSL			0x00000002
#घोषणा SSI_STCR_TEFS			0x00000001

/* SSI Receive Configuration Register -- REG_SSI_SRCR 0x20 */
#घोषणा SSI_SRCR_RXEXT			0x00000400
#घोषणा SSI_SRCR_RXBIT0			0x00000200
#घोषणा SSI_SRCR_RFEN1			0x00000100
#घोषणा SSI_SRCR_RFEN0			0x00000080
#घोषणा SSI_SRCR_RFसूची			0x00000040
#घोषणा SSI_SRCR_RXसूची			0x00000020
#घोषणा SSI_SRCR_RSHFD			0x00000010
#घोषणा SSI_SRCR_RSCKP			0x00000008
#घोषणा SSI_SRCR_RFSI			0x00000004
#घोषणा SSI_SRCR_RFSL			0x00000002
#घोषणा SSI_SRCR_REFS			0x00000001

/*
 * SSI Transmit Clock Control Register -- REG_SSI_STCCR 0x24
 * SSI Receive Clock Control Register -- REG_SSI_SRCCR 0x28
 */
#घोषणा SSI_SxCCR_DIV2_SHIFT		18
#घोषणा SSI_SxCCR_DIV2			0x00040000
#घोषणा SSI_SxCCR_PSR_SHIFT		17
#घोषणा SSI_SxCCR_PSR			0x00020000
#घोषणा SSI_SxCCR_WL_SHIFT		13
#घोषणा SSI_SxCCR_WL_MASK		0x0001E000
#घोषणा SSI_SxCCR_WL(x) \
	(((((x) / 2) - 1) << SSI_SxCCR_WL_SHIFT) & SSI_SxCCR_WL_MASK)
#घोषणा SSI_SxCCR_DC_SHIFT		8
#घोषणा SSI_SxCCR_DC_MASK		0x00001F00
#घोषणा SSI_SxCCR_DC(x) \
	((((x) - 1) << SSI_SxCCR_DC_SHIFT) & SSI_SxCCR_DC_MASK)
#घोषणा SSI_SxCCR_PM_SHIFT		0
#घोषणा SSI_SxCCR_PM_MASK		0x000000FF
#घोषणा SSI_SxCCR_PM(x) \
	((((x) - 1) << SSI_SxCCR_PM_SHIFT) & SSI_SxCCR_PM_MASK)

/*
 * SSI FIFO Control/Status Register -- REG_SSI_SFCSR 0x2c
 *
 * Tx or Rx FIFO Counter -- SSI_SFCSR_xFCNTy Read-Only
 * Tx or Rx FIFO Watermarks -- SSI_SFCSR_xFWMy Read/Write
 */
#घोषणा SSI_SFCSR_RFCNT1_SHIFT		28
#घोषणा SSI_SFCSR_RFCNT1_MASK		0xF0000000
#घोषणा SSI_SFCSR_RFCNT1(x) \
	(((x) & SSI_SFCSR_RFCNT1_MASK) >> SSI_SFCSR_RFCNT1_SHIFT)
#घोषणा SSI_SFCSR_TFCNT1_SHIFT		24
#घोषणा SSI_SFCSR_TFCNT1_MASK		0x0F000000
#घोषणा SSI_SFCSR_TFCNT1(x) \
	(((x) & SSI_SFCSR_TFCNT1_MASK) >> SSI_SFCSR_TFCNT1_SHIFT)
#घोषणा SSI_SFCSR_RFWM1_SHIFT		20
#घोषणा SSI_SFCSR_RFWM1_MASK		0x00F00000
#घोषणा SSI_SFCSR_RFWM1(x)	\
	(((x) << SSI_SFCSR_RFWM1_SHIFT) & SSI_SFCSR_RFWM1_MASK)
#घोषणा SSI_SFCSR_TFWM1_SHIFT		16
#घोषणा SSI_SFCSR_TFWM1_MASK		0x000F0000
#घोषणा SSI_SFCSR_TFWM1(x)	\
	(((x) << SSI_SFCSR_TFWM1_SHIFT) & SSI_SFCSR_TFWM1_MASK)
#घोषणा SSI_SFCSR_RFCNT0_SHIFT		12
#घोषणा SSI_SFCSR_RFCNT0_MASK		0x0000F000
#घोषणा SSI_SFCSR_RFCNT0(x) \
	(((x) & SSI_SFCSR_RFCNT0_MASK) >> SSI_SFCSR_RFCNT0_SHIFT)
#घोषणा SSI_SFCSR_TFCNT0_SHIFT		8
#घोषणा SSI_SFCSR_TFCNT0_MASK		0x00000F00
#घोषणा SSI_SFCSR_TFCNT0(x) \
	(((x) & SSI_SFCSR_TFCNT0_MASK) >> SSI_SFCSR_TFCNT0_SHIFT)
#घोषणा SSI_SFCSR_RFWM0_SHIFT		4
#घोषणा SSI_SFCSR_RFWM0_MASK		0x000000F0
#घोषणा SSI_SFCSR_RFWM0(x)	\
	(((x) << SSI_SFCSR_RFWM0_SHIFT) & SSI_SFCSR_RFWM0_MASK)
#घोषणा SSI_SFCSR_TFWM0_SHIFT		0
#घोषणा SSI_SFCSR_TFWM0_MASK		0x0000000F
#घोषणा SSI_SFCSR_TFWM0(x)	\
	(((x) << SSI_SFCSR_TFWM0_SHIFT) & SSI_SFCSR_TFWM0_MASK)

/* SSI Test Register -- REG_SSI_STR 0x30 */
#घोषणा SSI_STR_TEST			0x00008000
#घोषणा SSI_STR_RCK2TCK			0x00004000
#घोषणा SSI_STR_RFS2TFS			0x00002000
#घोषणा SSI_STR_RXSTATE(x)		(((x) >> 8) & 0x1F)
#घोषणा SSI_STR_TXD2RXD			0x00000080
#घोषणा SSI_STR_TCK2RCK			0x00000040
#घोषणा SSI_STR_TFS2RFS			0x00000020
#घोषणा SSI_STR_TXSTATE(x)		((x) & 0x1F)

/* SSI Option Register -- REG_SSI_SOR 0x34 */
#घोषणा SSI_SOR_CLKOFF			0x00000040
#घोषणा SSI_SOR_RX_CLR			0x00000020
#घोषणा SSI_SOR_TX_CLR			0x00000010
#घोषणा SSI_SOR_xX_CLR(tx)		((tx) ? SSI_SOR_TX_CLR : SSI_SOR_RX_CLR)
#घोषणा SSI_SOR_INIT			0x00000008
#घोषणा SSI_SOR_WAIT_SHIFT		1
#घोषणा SSI_SOR_WAIT_MASK		0x00000006
#घोषणा SSI_SOR_WAIT(x)			(((x) & 3) << SSI_SOR_WAIT_SHIFT)
#घोषणा SSI_SOR_SYNRST			0x00000001

/* SSI AC97 Control Register -- REG_SSI_SACNT 0x38 */
#घोषणा SSI_SACNT_FRDIV(x)		(((x) & 0x3f) << 5)
#घोषणा SSI_SACNT_WR			0x00000010
#घोषणा SSI_SACNT_RD			0x00000008
#घोषणा SSI_SACNT_RDWR_MASK		0x00000018
#घोषणा SSI_SACNT_TIF			0x00000004
#घोषणा SSI_SACNT_FV			0x00000002
#घोषणा SSI_SACNT_AC97EN		0x00000001


काष्ठा device;

#अगर IS_ENABLED(CONFIG_DEBUG_FS)

काष्ठा fsl_ssi_dbg अणु
	काष्ठा dentry *dbg_dir;

	काष्ठा अणु
		अचिन्हित पूर्णांक rfrc;
		अचिन्हित पूर्णांक tfrc;
		अचिन्हित पूर्णांक cmdau;
		अचिन्हित पूर्णांक cmddu;
		अचिन्हित पूर्णांक rxt;
		अचिन्हित पूर्णांक rdr1;
		अचिन्हित पूर्णांक rdr0;
		अचिन्हित पूर्णांक tde1;
		अचिन्हित पूर्णांक tde0;
		अचिन्हित पूर्णांक roe1;
		अचिन्हित पूर्णांक roe0;
		अचिन्हित पूर्णांक tue1;
		अचिन्हित पूर्णांक tue0;
		अचिन्हित पूर्णांक tfs;
		अचिन्हित पूर्णांक rfs;
		अचिन्हित पूर्णांक tls;
		अचिन्हित पूर्णांक rls;
		अचिन्हित पूर्णांक rff1;
		अचिन्हित पूर्णांक rff0;
		अचिन्हित पूर्णांक tfe1;
		अचिन्हित पूर्णांक tfe0;
	पूर्ण stats;
पूर्ण;

व्योम fsl_ssi_dbg_isr(काष्ठा fsl_ssi_dbg *ssi_dbg, u32 sisr);

व्योम fsl_ssi_debugfs_create(काष्ठा fsl_ssi_dbg *ssi_dbg, काष्ठा device *dev);

व्योम fsl_ssi_debugfs_हटाओ(काष्ठा fsl_ssi_dbg *ssi_dbg);

#अन्यथा

काष्ठा fsl_ssi_dbg अणु
पूर्ण;

अटल अंतरभूत व्योम fsl_ssi_dbg_isr(काष्ठा fsl_ssi_dbg *stats, u32 sisr)
अणु
पूर्ण

अटल अंतरभूत व्योम fsl_ssi_debugfs_create(काष्ठा fsl_ssi_dbg *ssi_dbg,
					  काष्ठा device *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम fsl_ssi_debugfs_हटाओ(काष्ठा fsl_ssi_dbg *ssi_dbg)
अणु
पूर्ण
#पूर्ण_अगर  /* ! IS_ENABLED(CONFIG_DEBUG_FS) */

#पूर्ण_अगर
