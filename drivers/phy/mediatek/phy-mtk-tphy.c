<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015 MediaTek Inc.
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 *
 */

#समावेश <dt-bindings/phy/phy.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

/* version V1 sub-banks offset base address */
/* banks shared by multiple phys */
#घोषणा SSUSB_SIFSLV_V1_SPLLC		0x000	/* shared by u3 phys */
#घोषणा SSUSB_SIFSLV_V1_U2FREQ		0x100	/* shared by u2 phys */
#घोषणा SSUSB_SIFSLV_V1_CHIP		0x300	/* shared by u3 phys */
/* u2 phy bank */
#घोषणा SSUSB_SIFSLV_V1_U2PHY_COM	0x000
/* u3/pcie/sata phy banks */
#घोषणा SSUSB_SIFSLV_V1_U3PHYD		0x000
#घोषणा SSUSB_SIFSLV_V1_U3PHYA		0x200

/* version V2 sub-banks offset base address */
/* u2 phy banks */
#घोषणा SSUSB_SIFSLV_V2_MISC		0x000
#घोषणा SSUSB_SIFSLV_V2_U2FREQ		0x100
#घोषणा SSUSB_SIFSLV_V2_U2PHY_COM	0x300
/* u3/pcie/sata phy banks */
#घोषणा SSUSB_SIFSLV_V2_SPLLC		0x000
#घोषणा SSUSB_SIFSLV_V2_CHIP		0x100
#घोषणा SSUSB_SIFSLV_V2_U3PHYD		0x200
#घोषणा SSUSB_SIFSLV_V2_U3PHYA		0x400

#घोषणा U3P_USBPHYACR0		0x000
#घोषणा PA0_RG_U2PLL_FORCE_ON		BIT(15)
#घोषणा PA0_RG_USB20_INTR_EN		BIT(5)

#घोषणा U3P_USBPHYACR1		0x004
#घोषणा PA1_RG_INTR_CAL		GENMASK(23, 19)
#घोषणा PA1_RG_INTR_CAL_VAL(x)	((0x1f & (x)) << 19)
#घोषणा PA1_RG_VRT_SEL			GENMASK(14, 12)
#घोषणा PA1_RG_VRT_SEL_VAL(x)	((0x7 & (x)) << 12)
#घोषणा PA1_RG_TERM_SEL		GENMASK(10, 8)
#घोषणा PA1_RG_TERM_SEL_VAL(x)	((0x7 & (x)) << 8)

#घोषणा U3P_USBPHYACR2		0x008
#घोषणा PA2_RG_SIF_U2PLL_FORCE_EN	BIT(18)

#घोषणा U3P_USBPHYACR5		0x014
#घोषणा PA5_RG_U2_HSTX_SRCAL_EN	BIT(15)
#घोषणा PA5_RG_U2_HSTX_SRCTRL		GENMASK(14, 12)
#घोषणा PA5_RG_U2_HSTX_SRCTRL_VAL(x)	((0x7 & (x)) << 12)
#घोषणा PA5_RG_U2_HS_100U_U3_EN	BIT(11)

#घोषणा U3P_USBPHYACR6		0x018
#घोषणा PA6_RG_U2_BC11_SW_EN		BIT(23)
#घोषणा PA6_RG_U2_OTG_VBUSCMP_EN	BIT(20)
#घोषणा PA6_RG_U2_DISCTH		GENMASK(7, 4)
#घोषणा PA6_RG_U2_DISCTH_VAL(x)	((0xf & (x)) << 4)
#घोषणा PA6_RG_U2_SQTH		GENMASK(3, 0)
#घोषणा PA6_RG_U2_SQTH_VAL(x)	(0xf & (x))

#घोषणा U3P_U2PHYACR4		0x020
#घोषणा P2C_RG_USB20_GPIO_CTL		BIT(9)
#घोषणा P2C_USB20_GPIO_MODE		BIT(8)
#घोषणा P2C_U2_GPIO_CTR_MSK	(P2C_RG_USB20_GPIO_CTL | P2C_USB20_GPIO_MODE)

#घोषणा U3D_U2PHYDCR0		0x060
#घोषणा P2C_RG_SIF_U2PLL_FORCE_ON	BIT(24)

#घोषणा U3P_U2PHYDTM0		0x068
#घोषणा P2C_FORCE_UART_EN		BIT(26)
#घोषणा P2C_FORCE_DATAIN		BIT(23)
#घोषणा P2C_FORCE_DM_PULLDOWN		BIT(21)
#घोषणा P2C_FORCE_DP_PULLDOWN		BIT(20)
#घोषणा P2C_FORCE_XCVRSEL		BIT(19)
#घोषणा P2C_FORCE_SUSPENDM		BIT(18)
#घोषणा P2C_FORCE_TERMSEL		BIT(17)
#घोषणा P2C_RG_DATAIN			GENMASK(13, 10)
#घोषणा P2C_RG_DATAIN_VAL(x)		((0xf & (x)) << 10)
#घोषणा P2C_RG_DMPULLDOWN		BIT(7)
#घोषणा P2C_RG_DPPULLDOWN		BIT(6)
#घोषणा P2C_RG_XCVRSEL			GENMASK(5, 4)
#घोषणा P2C_RG_XCVRSEL_VAL(x)		((0x3 & (x)) << 4)
#घोषणा P2C_RG_SUSPENDM			BIT(3)
#घोषणा P2C_RG_TERMSEL			BIT(2)
#घोषणा P2C_DTM0_PART_MASK \
		(P2C_FORCE_DATAIN | P2C_FORCE_DM_PULLDOWN | \
		P2C_FORCE_DP_PULLDOWN | P2C_FORCE_XCVRSEL | \
		P2C_FORCE_TERMSEL | P2C_RG_DMPULLDOWN | \
		P2C_RG_DPPULLDOWN | P2C_RG_TERMSEL)

#घोषणा U3P_U2PHYDTM1		0x06C
#घोषणा P2C_RG_UART_EN			BIT(16)
#घोषणा P2C_FORCE_IDDIG		BIT(9)
#घोषणा P2C_RG_VBUSVALID		BIT(5)
#घोषणा P2C_RG_SESSEND			BIT(4)
#घोषणा P2C_RG_AVALID			BIT(2)
#घोषणा P2C_RG_IDDIG			BIT(1)

#घोषणा U3P_U2PHYBC12C		0x080
#घोषणा P2C_RG_CHGDT_EN		BIT(0)

#घोषणा U3P_U3_CHIP_GPIO_CTLD		0x0c
#घोषणा P3C_REG_IP_SW_RST		BIT(31)
#घोषणा P3C_MCU_BUS_CK_GATE_EN		BIT(30)
#घोषणा P3C_FORCE_IP_SW_RST		BIT(29)

#घोषणा U3P_U3_CHIP_GPIO_CTLE		0x10
#घोषणा P3C_RG_SWRST_U3_PHYD		BIT(25)
#घोषणा P3C_RG_SWRST_U3_PHYD_FORCE_EN	BIT(24)

#घोषणा U3P_U3_PHYA_REG0	0x000
#घोषणा P3A_RG_CLKDRV_OFF		GENMASK(3, 2)
#घोषणा P3A_RG_CLKDRV_OFF_VAL(x)	((0x3 & (x)) << 2)

#घोषणा U3P_U3_PHYA_REG1	0x004
#घोषणा P3A_RG_CLKDRV_AMP		GENMASK(31, 29)
#घोषणा P3A_RG_CLKDRV_AMP_VAL(x)	((0x7 & (x)) << 29)

#घोषणा U3P_U3_PHYA_REG6	0x018
#घोषणा P3A_RG_TX_EIDLE_CM		GENMASK(31, 28)
#घोषणा P3A_RG_TX_EIDLE_CM_VAL(x)	((0xf & (x)) << 28)

#घोषणा U3P_U3_PHYA_REG9	0x024
#घोषणा P3A_RG_RX_DAC_MUX		GENMASK(5, 1)
#घोषणा P3A_RG_RX_DAC_MUX_VAL(x)	((0x1f & (x)) << 1)

#घोषणा U3P_U3_PHYA_DA_REG0	0x100
#घोषणा P3A_RG_XTAL_EXT_PE2H		GENMASK(17, 16)
#घोषणा P3A_RG_XTAL_EXT_PE2H_VAL(x)	((0x3 & (x)) << 16)
#घोषणा P3A_RG_XTAL_EXT_PE1H		GENMASK(13, 12)
#घोषणा P3A_RG_XTAL_EXT_PE1H_VAL(x)	((0x3 & (x)) << 12)
#घोषणा P3A_RG_XTAL_EXT_EN_U3		GENMASK(11, 10)
#घोषणा P3A_RG_XTAL_EXT_EN_U3_VAL(x)	((0x3 & (x)) << 10)

#घोषणा U3P_U3_PHYA_DA_REG4	0x108
#घोषणा P3A_RG_PLL_DIVEN_PE2H		GENMASK(21, 19)
#घोषणा P3A_RG_PLL_BC_PE2H		GENMASK(7, 6)
#घोषणा P3A_RG_PLL_BC_PE2H_VAL(x)	((0x3 & (x)) << 6)

#घोषणा U3P_U3_PHYA_DA_REG5	0x10c
#घोषणा P3A_RG_PLL_BR_PE2H		GENMASK(29, 28)
#घोषणा P3A_RG_PLL_BR_PE2H_VAL(x)	((0x3 & (x)) << 28)
#घोषणा P3A_RG_PLL_IC_PE2H		GENMASK(15, 12)
#घोषणा P3A_RG_PLL_IC_PE2H_VAL(x)	((0xf & (x)) << 12)

#घोषणा U3P_U3_PHYA_DA_REG6	0x110
#घोषणा P3A_RG_PLL_IR_PE2H		GENMASK(19, 16)
#घोषणा P3A_RG_PLL_IR_PE2H_VAL(x)	((0xf & (x)) << 16)

#घोषणा U3P_U3_PHYA_DA_REG7	0x114
#घोषणा P3A_RG_PLL_BP_PE2H		GENMASK(19, 16)
#घोषणा P3A_RG_PLL_BP_PE2H_VAL(x)	((0xf & (x)) << 16)

#घोषणा U3P_U3_PHYA_DA_REG20	0x13c
#घोषणा P3A_RG_PLL_DELTA1_PE2H		GENMASK(31, 16)
#घोषणा P3A_RG_PLL_DELTA1_PE2H_VAL(x)	((0xffff & (x)) << 16)

#घोषणा U3P_U3_PHYA_DA_REG25	0x148
#घोषणा P3A_RG_PLL_DELTA_PE2H		GENMASK(15, 0)
#घोषणा P3A_RG_PLL_DELTA_PE2H_VAL(x)	(0xffff & (x))

#घोषणा U3P_U3_PHYD_LFPS1		0x00c
#घोषणा P3D_RG_FWAKE_TH		GENMASK(21, 16)
#घोषणा P3D_RG_FWAKE_TH_VAL(x)	((0x3f & (x)) << 16)

#घोषणा U3P_U3_PHYD_CDR1		0x05c
#घोषणा P3D_RG_CDR_BIR_LTD1		GENMASK(28, 24)
#घोषणा P3D_RG_CDR_BIR_LTD1_VAL(x)	((0x1f & (x)) << 24)
#घोषणा P3D_RG_CDR_BIR_LTD0		GENMASK(12, 8)
#घोषणा P3D_RG_CDR_BIR_LTD0_VAL(x)	((0x1f & (x)) << 8)

#घोषणा U3P_U3_PHYD_RXDET1		0x128
#घोषणा P3D_RG_RXDET_STB2_SET		GENMASK(17, 9)
#घोषणा P3D_RG_RXDET_STB2_SET_VAL(x)	((0x1ff & (x)) << 9)

#घोषणा U3P_U3_PHYD_RXDET2		0x12c
#घोषणा P3D_RG_RXDET_STB2_SET_P3	GENMASK(8, 0)
#घोषणा P3D_RG_RXDET_STB2_SET_P3_VAL(x)	(0x1ff & (x))

#घोषणा U3P_SPLLC_XTALCTL3		0x018
#घोषणा XC3_RG_U3_XTAL_RX_PWD		BIT(9)
#घोषणा XC3_RG_U3_FRC_XTAL_RX_PWD	BIT(8)

#घोषणा U3P_U2FREQ_FMCR0	0x00
#घोषणा P2F_RG_MONCLK_SEL	GENMASK(27, 26)
#घोषणा P2F_RG_MONCLK_SEL_VAL(x)	((0x3 & (x)) << 26)
#घोषणा P2F_RG_FREQDET_EN	BIT(24)
#घोषणा P2F_RG_CYCLECNT		GENMASK(23, 0)
#घोषणा P2F_RG_CYCLECNT_VAL(x)	((P2F_RG_CYCLECNT) & (x))

#घोषणा U3P_U2FREQ_VALUE	0x0c

#घोषणा U3P_U2FREQ_FMMONR1	0x10
#घोषणा P2F_USB_FM_VALID	BIT(0)
#घोषणा P2F_RG_FRCK_EN		BIT(8)

#घोषणा U3P_REF_CLK		26	/* MHZ */
#घोषणा U3P_SLEW_RATE_COEF	28
#घोषणा U3P_SR_COEF_DIVISOR	1000
#घोषणा U3P_FM_DET_CYCLE_CNT	1024

/* SATA रेजिस्टर setting */
#घोषणा PHYD_CTRL_SIGNAL_MODE4		0x1c
/* CDR Charge Pump P-path current adjusपंचांगent */
#घोषणा RG_CDR_BICLTD1_GEN1_MSK		GENMASK(23, 20)
#घोषणा RG_CDR_BICLTD1_GEN1_VAL(x)	((0xf & (x)) << 20)
#घोषणा RG_CDR_BICLTD0_GEN1_MSK		GENMASK(11, 8)
#घोषणा RG_CDR_BICLTD0_GEN1_VAL(x)	((0xf & (x)) << 8)

#घोषणा PHYD_DESIGN_OPTION2		0x24
/* Symbol lock count selection */
#घोषणा RG_LOCK_CNT_SEL_MSK		GENMASK(5, 4)
#घोषणा RG_LOCK_CNT_SEL_VAL(x)		((0x3 & (x)) << 4)

#घोषणा PHYD_DESIGN_OPTION9	0x40
/* COMWAK GAP width winकरोw */
#घोषणा RG_TG_MAX_MSK		GENMASK(20, 16)
#घोषणा RG_TG_MAX_VAL(x)	((0x1f & (x)) << 16)
/* COMINIT GAP width winकरोw */
#घोषणा RG_T2_MAX_MSK		GENMASK(13, 8)
#घोषणा RG_T2_MAX_VAL(x)	((0x3f & (x)) << 8)
/* COMWAK GAP width winकरोw */
#घोषणा RG_TG_MIN_MSK		GENMASK(7, 5)
#घोषणा RG_TG_MIN_VAL(x)	((0x7 & (x)) << 5)
/* COMINIT GAP width winकरोw */
#घोषणा RG_T2_MIN_MSK		GENMASK(4, 0)
#घोषणा RG_T2_MIN_VAL(x)	(0x1f & (x))

#घोषणा ANA_RG_CTRL_SIGNAL1		0x4c
/* TX driver tail current control क्रम 0dB de-empahsis mकरोe क्रम Gen1 speed */
#घोषणा RG_IDRV_0DB_GEN1_MSK		GENMASK(13, 8)
#घोषणा RG_IDRV_0DB_GEN1_VAL(x)		((0x3f & (x)) << 8)

#घोषणा ANA_RG_CTRL_SIGNAL4		0x58
#घोषणा RG_CDR_BICLTR_GEN1_MSK		GENMASK(23, 20)
#घोषणा RG_CDR_BICLTR_GEN1_VAL(x)	((0xf & (x)) << 20)
/* Loop filter R1 resistance adjusपंचांगent क्रम Gen1 speed */
#घोषणा RG_CDR_BR_GEN2_MSK		GENMASK(10, 8)
#घोषणा RG_CDR_BR_GEN2_VAL(x)		((0x7 & (x)) << 8)

#घोषणा ANA_RG_CTRL_SIGNAL6		0x60
/* I-path capacitance adjusपंचांगent क्रम Gen1 */
#घोषणा RG_CDR_BC_GEN1_MSK		GENMASK(28, 24)
#घोषणा RG_CDR_BC_GEN1_VAL(x)		((0x1f & (x)) << 24)
#घोषणा RG_CDR_BIRLTR_GEN1_MSK		GENMASK(4, 0)
#घोषणा RG_CDR_BIRLTR_GEN1_VAL(x)	(0x1f & (x))

#घोषणा ANA_EQ_EYE_CTRL_SIGNAL1		0x6c
/* RX Gen1 LEQ tuning step */
#घोषणा RG_EQ_DLEQ_LFI_GEN1_MSK		GENMASK(11, 8)
#घोषणा RG_EQ_DLEQ_LFI_GEN1_VAL(x)	((0xf & (x)) << 8)

#घोषणा ANA_EQ_EYE_CTRL_SIGNAL4		0xd8
#घोषणा RG_CDR_BIRLTD0_GEN1_MSK		GENMASK(20, 16)
#घोषणा RG_CDR_BIRLTD0_GEN1_VAL(x)	((0x1f & (x)) << 16)

#घोषणा ANA_EQ_EYE_CTRL_SIGNAL5		0xdc
#घोषणा RG_CDR_BIRLTD0_GEN3_MSK		GENMASK(4, 0)
#घोषणा RG_CDR_BIRLTD0_GEN3_VAL(x)	(0x1f & (x))

क्रमागत mtk_phy_version अणु
	MTK_PHY_V1 = 1,
	MTK_PHY_V2,
पूर्ण;

काष्ठा mtk_phy_pdata अणु
	/* aव्योम RX sensitivity level degradation only क्रम mt8173 */
	bool aव्योम_rx_sen_degradation;
	क्रमागत mtk_phy_version version;
पूर्ण;

काष्ठा u2phy_banks अणु
	व्योम __iomem *misc;
	व्योम __iomem *fmreg;
	व्योम __iomem *com;
पूर्ण;

काष्ठा u3phy_banks अणु
	व्योम __iomem *spllc;
	व्योम __iomem *chip;
	व्योम __iomem *phyd; /* include u3phyd_bank2 */
	व्योम __iomem *phya; /* include u3phya_da */
पूर्ण;

काष्ठा mtk_phy_instance अणु
	काष्ठा phy *phy;
	व्योम __iomem *port_base;
	जोड़ अणु
		काष्ठा u2phy_banks u2_banks;
		काष्ठा u3phy_banks u3_banks;
	पूर्ण;
	काष्ठा clk *ref_clk;	/* reference घड़ी of (digital) phy */
	काष्ठा clk *da_ref_clk;	/* reference घड़ी of analog phy */
	u32 index;
	u8 type;
	पूर्णांक eye_src;
	पूर्णांक eye_vrt;
	पूर्णांक eye_term;
	पूर्णांक पूर्णांकr;
	पूर्णांक discth;
	bool bc12_en;
पूर्ण;

काष्ठा mtk_tphy अणु
	काष्ठा device *dev;
	व्योम __iomem *sअगर_base;	/* only shared sअगर */
	स्थिर काष्ठा mtk_phy_pdata *pdata;
	काष्ठा mtk_phy_instance **phys;
	पूर्णांक nphys;
	पूर्णांक src_ref_clk; /* MHZ, reference घड़ी क्रम slew rate calibrate */
	पूर्णांक src_coef; /* coefficient क्रम slew rate calibrate */
पूर्ण;

अटल व्योम hs_slew_rate_calibrate(काष्ठा mtk_tphy *tphy,
	काष्ठा mtk_phy_instance *instance)
अणु
	काष्ठा u2phy_banks *u2_banks = &instance->u2_banks;
	व्योम __iomem *fmreg = u2_banks->fmreg;
	व्योम __iomem *com = u2_banks->com;
	पूर्णांक calibration_val;
	पूर्णांक fm_out;
	u32 पंचांगp;

	/* use क्रमce value */
	अगर (instance->eye_src)
		वापस;

	/* enable USB ring oscillator */
	पंचांगp = पढ़ोl(com + U3P_USBPHYACR5);
	पंचांगp |= PA5_RG_U2_HSTX_SRCAL_EN;
	ग_लिखोl(पंचांगp, com + U3P_USBPHYACR5);
	udelay(1);

	/*enable मुक्त run घड़ी */
	पंचांगp = पढ़ोl(fmreg + U3P_U2FREQ_FMMONR1);
	पंचांगp |= P2F_RG_FRCK_EN;
	ग_लिखोl(पंचांगp, fmreg + U3P_U2FREQ_FMMONR1);

	/* set cycle count as 1024, and select u2 channel */
	पंचांगp = पढ़ोl(fmreg + U3P_U2FREQ_FMCR0);
	पंचांगp &= ~(P2F_RG_CYCLECNT | P2F_RG_MONCLK_SEL);
	पंचांगp |= P2F_RG_CYCLECNT_VAL(U3P_FM_DET_CYCLE_CNT);
	अगर (tphy->pdata->version == MTK_PHY_V1)
		पंचांगp |= P2F_RG_MONCLK_SEL_VAL(instance->index >> 1);

	ग_लिखोl(पंचांगp, fmreg + U3P_U2FREQ_FMCR0);

	/* enable frequency meter */
	पंचांगp = पढ़ोl(fmreg + U3P_U2FREQ_FMCR0);
	पंचांगp |= P2F_RG_FREQDET_EN;
	ग_लिखोl(पंचांगp, fmreg + U3P_U2FREQ_FMCR0);

	/* ignore वापस value */
	पढ़ोl_poll_समयout(fmreg + U3P_U2FREQ_FMMONR1, पंचांगp,
			   (पंचांगp & P2F_USB_FM_VALID), 10, 200);

	fm_out = पढ़ोl(fmreg + U3P_U2FREQ_VALUE);

	/* disable frequency meter */
	पंचांगp = पढ़ोl(fmreg + U3P_U2FREQ_FMCR0);
	पंचांगp &= ~P2F_RG_FREQDET_EN;
	ग_लिखोl(पंचांगp, fmreg + U3P_U2FREQ_FMCR0);

	/*disable मुक्त run घड़ी */
	पंचांगp = पढ़ोl(fmreg + U3P_U2FREQ_FMMONR1);
	पंचांगp &= ~P2F_RG_FRCK_EN;
	ग_लिखोl(पंचांगp, fmreg + U3P_U2FREQ_FMMONR1);

	अगर (fm_out) अणु
		/* ( 1024 / FM_OUT ) x reference घड़ी frequency x coef */
		पंचांगp = tphy->src_ref_clk * tphy->src_coef;
		पंचांगp = (पंचांगp * U3P_FM_DET_CYCLE_CNT) / fm_out;
		calibration_val = DIV_ROUND_CLOSEST(पंचांगp, U3P_SR_COEF_DIVISOR);
	पूर्ण अन्यथा अणु
		/* अगर FM detection fail, set शेष value */
		calibration_val = 4;
	पूर्ण
	dev_dbg(tphy->dev, "phy:%d, fm_out:%d, calib:%d (clk:%d, coef:%d)\n",
		instance->index, fm_out, calibration_val,
		tphy->src_ref_clk, tphy->src_coef);

	/* set HS slew rate */
	पंचांगp = पढ़ोl(com + U3P_USBPHYACR5);
	पंचांगp &= ~PA5_RG_U2_HSTX_SRCTRL;
	पंचांगp |= PA5_RG_U2_HSTX_SRCTRL_VAL(calibration_val);
	ग_लिखोl(पंचांगp, com + U3P_USBPHYACR5);

	/* disable USB ring oscillator */
	पंचांगp = पढ़ोl(com + U3P_USBPHYACR5);
	पंचांगp &= ~PA5_RG_U2_HSTX_SRCAL_EN;
	ग_लिखोl(पंचांगp, com + U3P_USBPHYACR5);
पूर्ण

अटल व्योम u3_phy_instance_init(काष्ठा mtk_tphy *tphy,
	काष्ठा mtk_phy_instance *instance)
अणु
	काष्ठा u3phy_banks *u3_banks = &instance->u3_banks;
	u32 पंचांगp;

	/* gating PCIe Analog XTAL घड़ी */
	पंचांगp = पढ़ोl(u3_banks->spllc + U3P_SPLLC_XTALCTL3);
	पंचांगp |= XC3_RG_U3_XTAL_RX_PWD | XC3_RG_U3_FRC_XTAL_RX_PWD;
	ग_लिखोl(पंचांगp, u3_banks->spllc + U3P_SPLLC_XTALCTL3);

	/* gating XSQ */
	पंचांगp = पढ़ोl(u3_banks->phya + U3P_U3_PHYA_DA_REG0);
	पंचांगp &= ~P3A_RG_XTAL_EXT_EN_U3;
	पंचांगp |= P3A_RG_XTAL_EXT_EN_U3_VAL(2);
	ग_लिखोl(पंचांगp, u3_banks->phya + U3P_U3_PHYA_DA_REG0);

	पंचांगp = पढ़ोl(u3_banks->phya + U3P_U3_PHYA_REG9);
	पंचांगp &= ~P3A_RG_RX_DAC_MUX;
	पंचांगp |= P3A_RG_RX_DAC_MUX_VAL(4);
	ग_लिखोl(पंचांगp, u3_banks->phya + U3P_U3_PHYA_REG9);

	पंचांगp = पढ़ोl(u3_banks->phya + U3P_U3_PHYA_REG6);
	पंचांगp &= ~P3A_RG_TX_EIDLE_CM;
	पंचांगp |= P3A_RG_TX_EIDLE_CM_VAL(0xe);
	ग_लिखोl(पंचांगp, u3_banks->phya + U3P_U3_PHYA_REG6);

	पंचांगp = पढ़ोl(u3_banks->phyd + U3P_U3_PHYD_CDR1);
	पंचांगp &= ~(P3D_RG_CDR_BIR_LTD0 | P3D_RG_CDR_BIR_LTD1);
	पंचांगp |= P3D_RG_CDR_BIR_LTD0_VAL(0xc) | P3D_RG_CDR_BIR_LTD1_VAL(0x3);
	ग_लिखोl(पंचांगp, u3_banks->phyd + U3P_U3_PHYD_CDR1);

	पंचांगp = पढ़ोl(u3_banks->phyd + U3P_U3_PHYD_LFPS1);
	पंचांगp &= ~P3D_RG_FWAKE_TH;
	पंचांगp |= P3D_RG_FWAKE_TH_VAL(0x34);
	ग_लिखोl(पंचांगp, u3_banks->phyd + U3P_U3_PHYD_LFPS1);

	पंचांगp = पढ़ोl(u3_banks->phyd + U3P_U3_PHYD_RXDET1);
	पंचांगp &= ~P3D_RG_RXDET_STB2_SET;
	पंचांगp |= P3D_RG_RXDET_STB2_SET_VAL(0x10);
	ग_लिखोl(पंचांगp, u3_banks->phyd + U3P_U3_PHYD_RXDET1);

	पंचांगp = पढ़ोl(u3_banks->phyd + U3P_U3_PHYD_RXDET2);
	पंचांगp &= ~P3D_RG_RXDET_STB2_SET_P3;
	पंचांगp |= P3D_RG_RXDET_STB2_SET_P3_VAL(0x10);
	ग_लिखोl(पंचांगp, u3_banks->phyd + U3P_U3_PHYD_RXDET2);

	dev_dbg(tphy->dev, "%s(%d)\n", __func__, instance->index);
पूर्ण

अटल व्योम u2_phy_instance_init(काष्ठा mtk_tphy *tphy,
	काष्ठा mtk_phy_instance *instance)
अणु
	काष्ठा u2phy_banks *u2_banks = &instance->u2_banks;
	व्योम __iomem *com = u2_banks->com;
	u32 index = instance->index;
	u32 पंचांगp;

	/* चयन to USB function, and enable usb pll */
	पंचांगp = पढ़ोl(com + U3P_U2PHYDTM0);
	पंचांगp &= ~(P2C_FORCE_UART_EN | P2C_FORCE_SUSPENDM);
	पंचांगp |= P2C_RG_XCVRSEL_VAL(1) | P2C_RG_DATAIN_VAL(0);
	ग_लिखोl(पंचांगp, com + U3P_U2PHYDTM0);

	पंचांगp = पढ़ोl(com + U3P_U2PHYDTM1);
	पंचांगp &= ~P2C_RG_UART_EN;
	ग_लिखोl(पंचांगp, com + U3P_U2PHYDTM1);

	पंचांगp = पढ़ोl(com + U3P_USBPHYACR0);
	पंचांगp |= PA0_RG_USB20_INTR_EN;
	ग_लिखोl(पंचांगp, com + U3P_USBPHYACR0);

	/* disable चयन 100uA current to SSUSB */
	पंचांगp = पढ़ोl(com + U3P_USBPHYACR5);
	पंचांगp &= ~PA5_RG_U2_HS_100U_U3_EN;
	ग_लिखोl(पंचांगp, com + U3P_USBPHYACR5);

	अगर (!index) अणु
		पंचांगp = पढ़ोl(com + U3P_U2PHYACR4);
		पंचांगp &= ~P2C_U2_GPIO_CTR_MSK;
		ग_लिखोl(पंचांगp, com + U3P_U2PHYACR4);
	पूर्ण

	अगर (tphy->pdata->aव्योम_rx_sen_degradation) अणु
		अगर (!index) अणु
			पंचांगp = पढ़ोl(com + U3P_USBPHYACR2);
			पंचांगp |= PA2_RG_SIF_U2PLL_FORCE_EN;
			ग_लिखोl(पंचांगp, com + U3P_USBPHYACR2);

			पंचांगp = पढ़ोl(com + U3D_U2PHYDCR0);
			पंचांगp &= ~P2C_RG_SIF_U2PLL_FORCE_ON;
			ग_लिखोl(पंचांगp, com + U3D_U2PHYDCR0);
		पूर्ण अन्यथा अणु
			पंचांगp = पढ़ोl(com + U3D_U2PHYDCR0);
			पंचांगp |= P2C_RG_SIF_U2PLL_FORCE_ON;
			ग_लिखोl(पंचांगp, com + U3D_U2PHYDCR0);

			पंचांगp = पढ़ोl(com + U3P_U2PHYDTM0);
			पंचांगp |= P2C_RG_SUSPENDM | P2C_FORCE_SUSPENDM;
			ग_लिखोl(पंचांगp, com + U3P_U2PHYDTM0);
		पूर्ण
	पूर्ण

	पंचांगp = पढ़ोl(com + U3P_USBPHYACR6);
	पंचांगp &= ~PA6_RG_U2_BC11_SW_EN;	/* DP/DM BC1.1 path Disable */
	पंचांगp &= ~PA6_RG_U2_SQTH;
	पंचांगp |= PA6_RG_U2_SQTH_VAL(2);
	ग_लिखोl(पंचांगp, com + U3P_USBPHYACR6);

	dev_dbg(tphy->dev, "%s(%d)\n", __func__, index);
पूर्ण

अटल व्योम u2_phy_instance_घातer_on(काष्ठा mtk_tphy *tphy,
	काष्ठा mtk_phy_instance *instance)
अणु
	काष्ठा u2phy_banks *u2_banks = &instance->u2_banks;
	व्योम __iomem *com = u2_banks->com;
	u32 index = instance->index;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(com + U3P_U2PHYDTM0);
	पंचांगp &= ~(P2C_RG_XCVRSEL | P2C_RG_DATAIN | P2C_DTM0_PART_MASK);
	ग_लिखोl(पंचांगp, com + U3P_U2PHYDTM0);

	/* OTG Enable */
	पंचांगp = पढ़ोl(com + U3P_USBPHYACR6);
	पंचांगp |= PA6_RG_U2_OTG_VBUSCMP_EN;
	ग_लिखोl(पंचांगp, com + U3P_USBPHYACR6);

	पंचांगp = पढ़ोl(com + U3P_U2PHYDTM1);
	पंचांगp |= P2C_RG_VBUSVALID | P2C_RG_AVALID;
	पंचांगp &= ~P2C_RG_SESSEND;
	ग_लिखोl(पंचांगp, com + U3P_U2PHYDTM1);

	अगर (tphy->pdata->aव्योम_rx_sen_degradation && index) अणु
		पंचांगp = पढ़ोl(com + U3D_U2PHYDCR0);
		पंचांगp |= P2C_RG_SIF_U2PLL_FORCE_ON;
		ग_लिखोl(पंचांगp, com + U3D_U2PHYDCR0);

		पंचांगp = पढ़ोl(com + U3P_U2PHYDTM0);
		पंचांगp |= P2C_RG_SUSPENDM | P2C_FORCE_SUSPENDM;
		ग_लिखोl(पंचांगp, com + U3P_U2PHYDTM0);
	पूर्ण
	dev_dbg(tphy->dev, "%s(%d)\n", __func__, index);
पूर्ण

अटल व्योम u2_phy_instance_घातer_off(काष्ठा mtk_tphy *tphy,
	काष्ठा mtk_phy_instance *instance)
अणु
	काष्ठा u2phy_banks *u2_banks = &instance->u2_banks;
	व्योम __iomem *com = u2_banks->com;
	u32 index = instance->index;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(com + U3P_U2PHYDTM0);
	पंचांगp &= ~(P2C_RG_XCVRSEL | P2C_RG_DATAIN);
	ग_लिखोl(पंचांगp, com + U3P_U2PHYDTM0);

	/* OTG Disable */
	पंचांगp = पढ़ोl(com + U3P_USBPHYACR6);
	पंचांगp &= ~PA6_RG_U2_OTG_VBUSCMP_EN;
	ग_लिखोl(पंचांगp, com + U3P_USBPHYACR6);

	पंचांगp = पढ़ोl(com + U3P_U2PHYDTM1);
	पंचांगp &= ~(P2C_RG_VBUSVALID | P2C_RG_AVALID);
	पंचांगp |= P2C_RG_SESSEND;
	ग_लिखोl(पंचांगp, com + U3P_U2PHYDTM1);

	अगर (tphy->pdata->aव्योम_rx_sen_degradation && index) अणु
		पंचांगp = पढ़ोl(com + U3P_U2PHYDTM0);
		पंचांगp &= ~(P2C_RG_SUSPENDM | P2C_FORCE_SUSPENDM);
		ग_लिखोl(पंचांगp, com + U3P_U2PHYDTM0);

		पंचांगp = पढ़ोl(com + U3D_U2PHYDCR0);
		पंचांगp &= ~P2C_RG_SIF_U2PLL_FORCE_ON;
		ग_लिखोl(पंचांगp, com + U3D_U2PHYDCR0);
	पूर्ण

	dev_dbg(tphy->dev, "%s(%d)\n", __func__, index);
पूर्ण

अटल व्योम u2_phy_instance_निकास(काष्ठा mtk_tphy *tphy,
	काष्ठा mtk_phy_instance *instance)
अणु
	काष्ठा u2phy_banks *u2_banks = &instance->u2_banks;
	व्योम __iomem *com = u2_banks->com;
	u32 index = instance->index;
	u32 पंचांगp;

	अगर (tphy->pdata->aव्योम_rx_sen_degradation && index) अणु
		पंचांगp = पढ़ोl(com + U3D_U2PHYDCR0);
		पंचांगp &= ~P2C_RG_SIF_U2PLL_FORCE_ON;
		ग_लिखोl(पंचांगp, com + U3D_U2PHYDCR0);

		पंचांगp = पढ़ोl(com + U3P_U2PHYDTM0);
		पंचांगp &= ~P2C_FORCE_SUSPENDM;
		ग_लिखोl(पंचांगp, com + U3P_U2PHYDTM0);
	पूर्ण
पूर्ण

अटल व्योम u2_phy_instance_set_mode(काष्ठा mtk_tphy *tphy,
				     काष्ठा mtk_phy_instance *instance,
				     क्रमागत phy_mode mode)
अणु
	काष्ठा u2phy_banks *u2_banks = &instance->u2_banks;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(u2_banks->com + U3P_U2PHYDTM1);
	चयन (mode) अणु
	हाल PHY_MODE_USB_DEVICE:
		पंचांगp |= P2C_FORCE_IDDIG | P2C_RG_IDDIG;
		अवरोध;
	हाल PHY_MODE_USB_HOST:
		पंचांगp |= P2C_FORCE_IDDIG;
		पंचांगp &= ~P2C_RG_IDDIG;
		अवरोध;
	हाल PHY_MODE_USB_OTG:
		पंचांगp &= ~(P2C_FORCE_IDDIG | P2C_RG_IDDIG);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	ग_लिखोl(पंचांगp, u2_banks->com + U3P_U2PHYDTM1);
पूर्ण

अटल व्योम pcie_phy_instance_init(काष्ठा mtk_tphy *tphy,
	काष्ठा mtk_phy_instance *instance)
अणु
	काष्ठा u3phy_banks *u3_banks = &instance->u3_banks;
	u32 पंचांगp;

	अगर (tphy->pdata->version != MTK_PHY_V1)
		वापस;

	पंचांगp = पढ़ोl(u3_banks->phya + U3P_U3_PHYA_DA_REG0);
	पंचांगp &= ~(P3A_RG_XTAL_EXT_PE1H | P3A_RG_XTAL_EXT_PE2H);
	पंचांगp |= P3A_RG_XTAL_EXT_PE1H_VAL(0x2) | P3A_RG_XTAL_EXT_PE2H_VAL(0x2);
	ग_लिखोl(पंचांगp, u3_banks->phya + U3P_U3_PHYA_DA_REG0);

	/* ref clk drive */
	पंचांगp = पढ़ोl(u3_banks->phya + U3P_U3_PHYA_REG1);
	पंचांगp &= ~P3A_RG_CLKDRV_AMP;
	पंचांगp |= P3A_RG_CLKDRV_AMP_VAL(0x4);
	ग_लिखोl(पंचांगp, u3_banks->phya + U3P_U3_PHYA_REG1);

	पंचांगp = पढ़ोl(u3_banks->phya + U3P_U3_PHYA_REG0);
	पंचांगp &= ~P3A_RG_CLKDRV_OFF;
	पंचांगp |= P3A_RG_CLKDRV_OFF_VAL(0x1);
	ग_लिखोl(पंचांगp, u3_banks->phya + U3P_U3_PHYA_REG0);

	/* SSC delta -5000ppm */
	पंचांगp = पढ़ोl(u3_banks->phya + U3P_U3_PHYA_DA_REG20);
	पंचांगp &= ~P3A_RG_PLL_DELTA1_PE2H;
	पंचांगp |= P3A_RG_PLL_DELTA1_PE2H_VAL(0x3c);
	ग_लिखोl(पंचांगp, u3_banks->phya + U3P_U3_PHYA_DA_REG20);

	पंचांगp = पढ़ोl(u3_banks->phya + U3P_U3_PHYA_DA_REG25);
	पंचांगp &= ~P3A_RG_PLL_DELTA_PE2H;
	पंचांगp |= P3A_RG_PLL_DELTA_PE2H_VAL(0x36);
	ग_लिखोl(पंचांगp, u3_banks->phya + U3P_U3_PHYA_DA_REG25);

	/* change pll BW 0.6M */
	पंचांगp = पढ़ोl(u3_banks->phya + U3P_U3_PHYA_DA_REG5);
	पंचांगp &= ~(P3A_RG_PLL_BR_PE2H | P3A_RG_PLL_IC_PE2H);
	पंचांगp |= P3A_RG_PLL_BR_PE2H_VAL(0x1) | P3A_RG_PLL_IC_PE2H_VAL(0x1);
	ग_लिखोl(पंचांगp, u3_banks->phya + U3P_U3_PHYA_DA_REG5);

	पंचांगp = पढ़ोl(u3_banks->phya + U3P_U3_PHYA_DA_REG4);
	पंचांगp &= ~(P3A_RG_PLL_DIVEN_PE2H | P3A_RG_PLL_BC_PE2H);
	पंचांगp |= P3A_RG_PLL_BC_PE2H_VAL(0x3);
	ग_लिखोl(पंचांगp, u3_banks->phya + U3P_U3_PHYA_DA_REG4);

	पंचांगp = पढ़ोl(u3_banks->phya + U3P_U3_PHYA_DA_REG6);
	पंचांगp &= ~P3A_RG_PLL_IR_PE2H;
	पंचांगp |= P3A_RG_PLL_IR_PE2H_VAL(0x2);
	ग_लिखोl(पंचांगp, u3_banks->phya + U3P_U3_PHYA_DA_REG6);

	पंचांगp = पढ़ोl(u3_banks->phya + U3P_U3_PHYA_DA_REG7);
	पंचांगp &= ~P3A_RG_PLL_BP_PE2H;
	पंचांगp |= P3A_RG_PLL_BP_PE2H_VAL(0xa);
	ग_लिखोl(पंचांगp, u3_banks->phya + U3P_U3_PHYA_DA_REG7);

	/* Tx Detect Rx Timing: 10us -> 5us */
	पंचांगp = पढ़ोl(u3_banks->phyd + U3P_U3_PHYD_RXDET1);
	पंचांगp &= ~P3D_RG_RXDET_STB2_SET;
	पंचांगp |= P3D_RG_RXDET_STB2_SET_VAL(0x10);
	ग_लिखोl(पंचांगp, u3_banks->phyd + U3P_U3_PHYD_RXDET1);

	पंचांगp = पढ़ोl(u3_banks->phyd + U3P_U3_PHYD_RXDET2);
	पंचांगp &= ~P3D_RG_RXDET_STB2_SET_P3;
	पंचांगp |= P3D_RG_RXDET_STB2_SET_P3_VAL(0x10);
	ग_लिखोl(पंचांगp, u3_banks->phyd + U3P_U3_PHYD_RXDET2);

	/* रुको क्रम PCIe subsys रेजिस्टर to active */
	usleep_range(2500, 3000);
	dev_dbg(tphy->dev, "%s(%d)\n", __func__, instance->index);
पूर्ण

अटल व्योम pcie_phy_instance_घातer_on(काष्ठा mtk_tphy *tphy,
	काष्ठा mtk_phy_instance *instance)
अणु
	काष्ठा u3phy_banks *bank = &instance->u3_banks;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(bank->chip + U3P_U3_CHIP_GPIO_CTLD);
	पंचांगp &= ~(P3C_FORCE_IP_SW_RST | P3C_REG_IP_SW_RST);
	ग_लिखोl(पंचांगp, bank->chip + U3P_U3_CHIP_GPIO_CTLD);

	पंचांगp = पढ़ोl(bank->chip + U3P_U3_CHIP_GPIO_CTLE);
	पंचांगp &= ~(P3C_RG_SWRST_U3_PHYD_FORCE_EN | P3C_RG_SWRST_U3_PHYD);
	ग_लिखोl(पंचांगp, bank->chip + U3P_U3_CHIP_GPIO_CTLE);
पूर्ण

अटल व्योम pcie_phy_instance_घातer_off(काष्ठा mtk_tphy *tphy,
	काष्ठा mtk_phy_instance *instance)

अणु
	काष्ठा u3phy_banks *bank = &instance->u3_banks;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(bank->chip + U3P_U3_CHIP_GPIO_CTLD);
	पंचांगp |= P3C_FORCE_IP_SW_RST | P3C_REG_IP_SW_RST;
	ग_लिखोl(पंचांगp, bank->chip + U3P_U3_CHIP_GPIO_CTLD);

	पंचांगp = पढ़ोl(bank->chip + U3P_U3_CHIP_GPIO_CTLE);
	पंचांगp |= P3C_RG_SWRST_U3_PHYD_FORCE_EN | P3C_RG_SWRST_U3_PHYD;
	ग_लिखोl(पंचांगp, bank->chip + U3P_U3_CHIP_GPIO_CTLE);
पूर्ण

अटल व्योम sata_phy_instance_init(काष्ठा mtk_tphy *tphy,
	काष्ठा mtk_phy_instance *instance)
अणु
	काष्ठा u3phy_banks *u3_banks = &instance->u3_banks;
	व्योम __iomem *phyd = u3_banks->phyd;
	u32 पंचांगp;

	/* अक्षरge current adjusपंचांगent */
	पंचांगp = पढ़ोl(phyd + ANA_RG_CTRL_SIGNAL6);
	पंचांगp &= ~(RG_CDR_BIRLTR_GEN1_MSK | RG_CDR_BC_GEN1_MSK);
	पंचांगp |= RG_CDR_BIRLTR_GEN1_VAL(0x6) | RG_CDR_BC_GEN1_VAL(0x1a);
	ग_लिखोl(पंचांगp, phyd + ANA_RG_CTRL_SIGNAL6);

	पंचांगp = पढ़ोl(phyd + ANA_EQ_EYE_CTRL_SIGNAL4);
	पंचांगp &= ~RG_CDR_BIRLTD0_GEN1_MSK;
	पंचांगp |= RG_CDR_BIRLTD0_GEN1_VAL(0x18);
	ग_लिखोl(पंचांगp, phyd + ANA_EQ_EYE_CTRL_SIGNAL4);

	पंचांगp = पढ़ोl(phyd + ANA_EQ_EYE_CTRL_SIGNAL5);
	पंचांगp &= ~RG_CDR_BIRLTD0_GEN3_MSK;
	पंचांगp |= RG_CDR_BIRLTD0_GEN3_VAL(0x06);
	ग_लिखोl(पंचांगp, phyd + ANA_EQ_EYE_CTRL_SIGNAL5);

	पंचांगp = पढ़ोl(phyd + ANA_RG_CTRL_SIGNAL4);
	पंचांगp &= ~(RG_CDR_BICLTR_GEN1_MSK | RG_CDR_BR_GEN2_MSK);
	पंचांगp |= RG_CDR_BICLTR_GEN1_VAL(0x0c) | RG_CDR_BR_GEN2_VAL(0x07);
	ग_लिखोl(पंचांगp, phyd + ANA_RG_CTRL_SIGNAL4);

	पंचांगp = पढ़ोl(phyd + PHYD_CTRL_SIGNAL_MODE4);
	पंचांगp &= ~(RG_CDR_BICLTD0_GEN1_MSK | RG_CDR_BICLTD1_GEN1_MSK);
	पंचांगp |= RG_CDR_BICLTD0_GEN1_VAL(0x08) | RG_CDR_BICLTD1_GEN1_VAL(0x02);
	ग_लिखोl(पंचांगp, phyd + PHYD_CTRL_SIGNAL_MODE4);

	पंचांगp = पढ़ोl(phyd + PHYD_DESIGN_OPTION2);
	पंचांगp &= ~RG_LOCK_CNT_SEL_MSK;
	पंचांगp |= RG_LOCK_CNT_SEL_VAL(0x02);
	ग_लिखोl(पंचांगp, phyd + PHYD_DESIGN_OPTION2);

	पंचांगp = पढ़ोl(phyd + PHYD_DESIGN_OPTION9);
	पंचांगp &= ~(RG_T2_MIN_MSK | RG_TG_MIN_MSK |
		 RG_T2_MAX_MSK | RG_TG_MAX_MSK);
	पंचांगp |= RG_T2_MIN_VAL(0x12) | RG_TG_MIN_VAL(0x04) |
	       RG_T2_MAX_VAL(0x31) | RG_TG_MAX_VAL(0x0e);
	ग_लिखोl(पंचांगp, phyd + PHYD_DESIGN_OPTION9);

	पंचांगp = पढ़ोl(phyd + ANA_RG_CTRL_SIGNAL1);
	पंचांगp &= ~RG_IDRV_0DB_GEN1_MSK;
	पंचांगp |= RG_IDRV_0DB_GEN1_VAL(0x20);
	ग_लिखोl(पंचांगp, phyd + ANA_RG_CTRL_SIGNAL1);

	पंचांगp = पढ़ोl(phyd + ANA_EQ_EYE_CTRL_SIGNAL1);
	पंचांगp &= ~RG_EQ_DLEQ_LFI_GEN1_MSK;
	पंचांगp |= RG_EQ_DLEQ_LFI_GEN1_VAL(0x03);
	ग_लिखोl(पंचांगp, phyd + ANA_EQ_EYE_CTRL_SIGNAL1);

	dev_dbg(tphy->dev, "%s(%d)\n", __func__, instance->index);
पूर्ण

अटल व्योम phy_v1_banks_init(काष्ठा mtk_tphy *tphy,
			      काष्ठा mtk_phy_instance *instance)
अणु
	काष्ठा u2phy_banks *u2_banks = &instance->u2_banks;
	काष्ठा u3phy_banks *u3_banks = &instance->u3_banks;

	चयन (instance->type) अणु
	हाल PHY_TYPE_USB2:
		u2_banks->misc = शून्य;
		u2_banks->fmreg = tphy->sअगर_base + SSUSB_SIFSLV_V1_U2FREQ;
		u2_banks->com = instance->port_base + SSUSB_SIFSLV_V1_U2PHY_COM;
		अवरोध;
	हाल PHY_TYPE_USB3:
	हाल PHY_TYPE_PCIE:
		u3_banks->spllc = tphy->sअगर_base + SSUSB_SIFSLV_V1_SPLLC;
		u3_banks->chip = tphy->sअगर_base + SSUSB_SIFSLV_V1_CHIP;
		u3_banks->phyd = instance->port_base + SSUSB_SIFSLV_V1_U3PHYD;
		u3_banks->phya = instance->port_base + SSUSB_SIFSLV_V1_U3PHYA;
		अवरोध;
	हाल PHY_TYPE_SATA:
		u3_banks->phyd = instance->port_base + SSUSB_SIFSLV_V1_U3PHYD;
		अवरोध;
	शेष:
		dev_err(tphy->dev, "incompatible PHY type\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम phy_v2_banks_init(काष्ठा mtk_tphy *tphy,
			      काष्ठा mtk_phy_instance *instance)
अणु
	काष्ठा u2phy_banks *u2_banks = &instance->u2_banks;
	काष्ठा u3phy_banks *u3_banks = &instance->u3_banks;

	चयन (instance->type) अणु
	हाल PHY_TYPE_USB2:
		u2_banks->misc = instance->port_base + SSUSB_SIFSLV_V2_MISC;
		u2_banks->fmreg = instance->port_base + SSUSB_SIFSLV_V2_U2FREQ;
		u2_banks->com = instance->port_base + SSUSB_SIFSLV_V2_U2PHY_COM;
		अवरोध;
	हाल PHY_TYPE_USB3:
	हाल PHY_TYPE_PCIE:
		u3_banks->spllc = instance->port_base + SSUSB_SIFSLV_V2_SPLLC;
		u3_banks->chip = instance->port_base + SSUSB_SIFSLV_V2_CHIP;
		u3_banks->phyd = instance->port_base + SSUSB_SIFSLV_V2_U3PHYD;
		u3_banks->phya = instance->port_base + SSUSB_SIFSLV_V2_U3PHYA;
		अवरोध;
	शेष:
		dev_err(tphy->dev, "incompatible PHY type\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम phy_parse_property(काष्ठा mtk_tphy *tphy,
				काष्ठा mtk_phy_instance *instance)
अणु
	काष्ठा device *dev = &instance->phy->dev;

	अगर (instance->type != PHY_TYPE_USB2)
		वापस;

	instance->bc12_en = device_property_पढ़ो_bool(dev, "mediatek,bc12");
	device_property_पढ़ो_u32(dev, "mediatek,eye-src",
				 &instance->eye_src);
	device_property_पढ़ो_u32(dev, "mediatek,eye-vrt",
				 &instance->eye_vrt);
	device_property_पढ़ो_u32(dev, "mediatek,eye-term",
				 &instance->eye_term);
	device_property_पढ़ो_u32(dev, "mediatek,intr",
				 &instance->पूर्णांकr);
	device_property_पढ़ो_u32(dev, "mediatek,discth",
				 &instance->discth);
	dev_dbg(dev, "bc12:%d, src:%d, vrt:%d, term:%d, intr:%d, disc:%d\n",
		instance->bc12_en, instance->eye_src,
		instance->eye_vrt, instance->eye_term,
		instance->पूर्णांकr, instance->discth);
पूर्ण

अटल व्योम u2_phy_props_set(काष्ठा mtk_tphy *tphy,
			     काष्ठा mtk_phy_instance *instance)
अणु
	काष्ठा u2phy_banks *u2_banks = &instance->u2_banks;
	व्योम __iomem *com = u2_banks->com;
	u32 पंचांगp;

	अगर (instance->bc12_en) अणु
		पंचांगp = पढ़ोl(com + U3P_U2PHYBC12C);
		पंचांगp |= P2C_RG_CHGDT_EN;	/* BC1.2 path Enable */
		ग_लिखोl(पंचांगp, com + U3P_U2PHYBC12C);
	पूर्ण

	अगर (instance->eye_src) अणु
		पंचांगp = पढ़ोl(com + U3P_USBPHYACR5);
		पंचांगp &= ~PA5_RG_U2_HSTX_SRCTRL;
		पंचांगp |= PA5_RG_U2_HSTX_SRCTRL_VAL(instance->eye_src);
		ग_लिखोl(पंचांगp, com + U3P_USBPHYACR5);
	पूर्ण

	अगर (instance->eye_vrt) अणु
		पंचांगp = पढ़ोl(com + U3P_USBPHYACR1);
		पंचांगp &= ~PA1_RG_VRT_SEL;
		पंचांगp |= PA1_RG_VRT_SEL_VAL(instance->eye_vrt);
		ग_लिखोl(पंचांगp, com + U3P_USBPHYACR1);
	पूर्ण

	अगर (instance->eye_term) अणु
		पंचांगp = पढ़ोl(com + U3P_USBPHYACR1);
		पंचांगp &= ~PA1_RG_TERM_SEL;
		पंचांगp |= PA1_RG_TERM_SEL_VAL(instance->eye_term);
		ग_लिखोl(पंचांगp, com + U3P_USBPHYACR1);
	पूर्ण

	अगर (instance->पूर्णांकr) अणु
		पंचांगp = पढ़ोl(com + U3P_USBPHYACR1);
		पंचांगp &= ~PA1_RG_INTR_CAL;
		पंचांगp |= PA1_RG_INTR_CAL_VAL(instance->पूर्णांकr);
		ग_लिखोl(पंचांगp, com + U3P_USBPHYACR1);
	पूर्ण

	अगर (instance->discth) अणु
		पंचांगp = पढ़ोl(com + U3P_USBPHYACR6);
		पंचांगp &= ~PA6_RG_U2_DISCTH;
		पंचांगp |= PA6_RG_U2_DISCTH_VAL(instance->discth);
		ग_लिखोl(पंचांगp, com + U3P_USBPHYACR6);
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा mtk_phy_instance *instance = phy_get_drvdata(phy);
	काष्ठा mtk_tphy *tphy = dev_get_drvdata(phy->dev.parent);
	पूर्णांक ret;

	ret = clk_prepare_enable(instance->ref_clk);
	अगर (ret) अणु
		dev_err(tphy->dev, "failed to enable ref_clk\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(instance->da_ref_clk);
	अगर (ret) अणु
		dev_err(tphy->dev, "failed to enable da_ref\n");
		clk_disable_unprepare(instance->ref_clk);
		वापस ret;
	पूर्ण

	चयन (instance->type) अणु
	हाल PHY_TYPE_USB2:
		u2_phy_instance_init(tphy, instance);
		u2_phy_props_set(tphy, instance);
		अवरोध;
	हाल PHY_TYPE_USB3:
		u3_phy_instance_init(tphy, instance);
		अवरोध;
	हाल PHY_TYPE_PCIE:
		pcie_phy_instance_init(tphy, instance);
		अवरोध;
	हाल PHY_TYPE_SATA:
		sata_phy_instance_init(tphy, instance);
		अवरोध;
	शेष:
		dev_err(tphy->dev, "incompatible PHY type\n");
		clk_disable_unprepare(instance->ref_clk);
		clk_disable_unprepare(instance->da_ref_clk);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा mtk_phy_instance *instance = phy_get_drvdata(phy);
	काष्ठा mtk_tphy *tphy = dev_get_drvdata(phy->dev.parent);

	अगर (instance->type == PHY_TYPE_USB2) अणु
		u2_phy_instance_घातer_on(tphy, instance);
		hs_slew_rate_calibrate(tphy, instance);
	पूर्ण अन्यथा अगर (instance->type == PHY_TYPE_PCIE) अणु
		pcie_phy_instance_घातer_on(tphy, instance);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा mtk_phy_instance *instance = phy_get_drvdata(phy);
	काष्ठा mtk_tphy *tphy = dev_get_drvdata(phy->dev.parent);

	अगर (instance->type == PHY_TYPE_USB2)
		u2_phy_instance_घातer_off(tphy, instance);
	अन्यथा अगर (instance->type == PHY_TYPE_PCIE)
		pcie_phy_instance_घातer_off(tphy, instance);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा mtk_phy_instance *instance = phy_get_drvdata(phy);
	काष्ठा mtk_tphy *tphy = dev_get_drvdata(phy->dev.parent);

	अगर (instance->type == PHY_TYPE_USB2)
		u2_phy_instance_निकास(tphy, instance);

	clk_disable_unprepare(instance->ref_clk);
	clk_disable_unprepare(instance->da_ref_clk);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_phy_set_mode(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	काष्ठा mtk_phy_instance *instance = phy_get_drvdata(phy);
	काष्ठा mtk_tphy *tphy = dev_get_drvdata(phy->dev.parent);

	अगर (instance->type == PHY_TYPE_USB2)
		u2_phy_instance_set_mode(tphy, instance, mode);

	वापस 0;
पूर्ण

अटल काष्ठा phy *mtk_phy_xlate(काष्ठा device *dev,
					काष्ठा of_phandle_args *args)
अणु
	काष्ठा mtk_tphy *tphy = dev_get_drvdata(dev);
	काष्ठा mtk_phy_instance *instance = शून्य;
	काष्ठा device_node *phy_np = args->np;
	पूर्णांक index;

	अगर (args->args_count != 1) अणु
		dev_err(dev, "invalid number of cells in 'phy' property\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	क्रम (index = 0; index < tphy->nphys; index++)
		अगर (phy_np == tphy->phys[index]->phy->dev.of_node) अणु
			instance = tphy->phys[index];
			अवरोध;
		पूर्ण

	अगर (!instance) अणु
		dev_err(dev, "failed to find appropriate phy\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	instance->type = args->args[0];
	अगर (!(instance->type == PHY_TYPE_USB2 ||
	      instance->type == PHY_TYPE_USB3 ||
	      instance->type == PHY_TYPE_PCIE ||
	      instance->type == PHY_TYPE_SATA)) अणु
		dev_err(dev, "unsupported device type: %d\n", instance->type);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (tphy->pdata->version == MTK_PHY_V1) अणु
		phy_v1_banks_init(tphy, instance);
	पूर्ण अन्यथा अगर (tphy->pdata->version == MTK_PHY_V2) अणु
		phy_v2_banks_init(tphy, instance);
	पूर्ण अन्यथा अणु
		dev_err(dev, "phy version is not supported\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	phy_parse_property(tphy, instance);

	वापस instance->phy;
पूर्ण

अटल स्थिर काष्ठा phy_ops mtk_tphy_ops = अणु
	.init		= mtk_phy_init,
	.निकास		= mtk_phy_निकास,
	.घातer_on	= mtk_phy_घातer_on,
	.घातer_off	= mtk_phy_घातer_off,
	.set_mode	= mtk_phy_set_mode,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा mtk_phy_pdata tphy_v1_pdata = अणु
	.aव्योम_rx_sen_degradation = false,
	.version = MTK_PHY_V1,
पूर्ण;

अटल स्थिर काष्ठा mtk_phy_pdata tphy_v2_pdata = अणु
	.aव्योम_rx_sen_degradation = false,
	.version = MTK_PHY_V2,
पूर्ण;

अटल स्थिर काष्ठा mtk_phy_pdata mt8173_pdata = अणु
	.aव्योम_rx_sen_degradation = true,
	.version = MTK_PHY_V1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_tphy_id_table[] = अणु
	अणु .compatible = "mediatek,mt2701-u3phy", .data = &tphy_v1_pdata पूर्ण,
	अणु .compatible = "mediatek,mt2712-u3phy", .data = &tphy_v2_pdata पूर्ण,
	अणु .compatible = "mediatek,mt8173-u3phy", .data = &mt8173_pdata पूर्ण,
	अणु .compatible = "mediatek,generic-tphy-v1", .data = &tphy_v1_pdata पूर्ण,
	अणु .compatible = "mediatek,generic-tphy-v2", .data = &tphy_v2_pdata पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_tphy_id_table);

अटल पूर्णांक mtk_tphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *child_np;
	काष्ठा phy_provider *provider;
	काष्ठा resource *sअगर_res;
	काष्ठा mtk_tphy *tphy;
	काष्ठा resource res;
	पूर्णांक port, retval;

	tphy = devm_kzalloc(dev, माप(*tphy), GFP_KERNEL);
	अगर (!tphy)
		वापस -ENOMEM;

	tphy->pdata = of_device_get_match_data(dev);
	अगर (!tphy->pdata)
		वापस -EINVAL;

	tphy->nphys = of_get_child_count(np);
	tphy->phys = devm_kसुस्मृति(dev, tphy->nphys,
				       माप(*tphy->phys), GFP_KERNEL);
	अगर (!tphy->phys)
		वापस -ENOMEM;

	tphy->dev = dev;
	platक्रमm_set_drvdata(pdev, tphy);

	sअगर_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	/* SATA phy of V1 needn't it अगर not shared with PCIe or USB */
	अगर (sअगर_res && tphy->pdata->version == MTK_PHY_V1) अणु
		/* get banks shared by multiple phys */
		tphy->sअगर_base = devm_ioremap_resource(dev, sअगर_res);
		अगर (IS_ERR(tphy->sअगर_base)) अणु
			dev_err(dev, "failed to remap sif regs\n");
			वापस PTR_ERR(tphy->sअगर_base);
		पूर्ण
	पूर्ण

	tphy->src_ref_clk = U3P_REF_CLK;
	tphy->src_coef = U3P_SLEW_RATE_COEF;
	/* update parameters of slew rate calibrate अगर exist */
	device_property_पढ़ो_u32(dev, "mediatek,src-ref-clk-mhz",
		&tphy->src_ref_clk);
	device_property_पढ़ो_u32(dev, "mediatek,src-coef", &tphy->src_coef);

	port = 0;
	क्रम_each_child_of_node(np, child_np) अणु
		काष्ठा mtk_phy_instance *instance;
		काष्ठा phy *phy;

		instance = devm_kzalloc(dev, माप(*instance), GFP_KERNEL);
		अगर (!instance) अणु
			retval = -ENOMEM;
			जाओ put_child;
		पूर्ण

		tphy->phys[port] = instance;

		phy = devm_phy_create(dev, child_np, &mtk_tphy_ops);
		अगर (IS_ERR(phy)) अणु
			dev_err(dev, "failed to create phy\n");
			retval = PTR_ERR(phy);
			जाओ put_child;
		पूर्ण

		retval = of_address_to_resource(child_np, 0, &res);
		अगर (retval) अणु
			dev_err(dev, "failed to get address resource(id-%d)\n",
				port);
			जाओ put_child;
		पूर्ण

		instance->port_base = devm_ioremap_resource(&phy->dev, &res);
		अगर (IS_ERR(instance->port_base)) अणु
			dev_err(dev, "failed to remap phy regs\n");
			retval = PTR_ERR(instance->port_base);
			जाओ put_child;
		पूर्ण

		instance->phy = phy;
		instance->index = port;
		phy_set_drvdata(phy, instance);
		port++;

		instance->ref_clk = devm_clk_get_optional(&phy->dev, "ref");
		अगर (IS_ERR(instance->ref_clk)) अणु
			dev_err(dev, "failed to get ref_clk(id-%d)\n", port);
			retval = PTR_ERR(instance->ref_clk);
			जाओ put_child;
		पूर्ण

		instance->da_ref_clk =
			devm_clk_get_optional(&phy->dev, "da_ref");
		अगर (IS_ERR(instance->da_ref_clk)) अणु
			dev_err(dev, "failed to get da_ref_clk(id-%d)\n", port);
			retval = PTR_ERR(instance->da_ref_clk);
			जाओ put_child;
		पूर्ण
	पूर्ण

	provider = devm_of_phy_provider_रेजिस्टर(dev, mtk_phy_xlate);

	वापस PTR_ERR_OR_ZERO(provider);
put_child:
	of_node_put(child_np);
	वापस retval;
पूर्ण

अटल काष्ठा platक्रमm_driver mtk_tphy_driver = अणु
	.probe		= mtk_tphy_probe,
	.driver		= अणु
		.name	= "mtk-tphy",
		.of_match_table = mtk_tphy_id_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_tphy_driver);

MODULE_AUTHOR("Chunfeng Yun <chunfeng.yun@mediatek.com>");
MODULE_DESCRIPTION("MediaTek T-PHY driver");
MODULE_LICENSE("GPL v2");
