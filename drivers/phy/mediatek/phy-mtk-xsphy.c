<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MediaTek USB3.1 gen2 xsphy Driver
 *
 * Copyright (c) 2018 MediaTek Inc.
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
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

/* u2 phy banks */
#घोषणा SSUSB_SIFSLV_MISC		0x000
#घोषणा SSUSB_SIFSLV_U2FREQ		0x100
#घोषणा SSUSB_SIFSLV_U2PHY_COM	0x300

/* u3 phy shared banks */
#घोषणा SSPXTP_SIFSLV_DIG_GLB		0x000
#घोषणा SSPXTP_SIFSLV_PHYA_GLB		0x100

/* u3 phy banks */
#घोषणा SSPXTP_SIFSLV_DIG_LN_TOP	0x000
#घोषणा SSPXTP_SIFSLV_DIG_LN_TX0	0x100
#घोषणा SSPXTP_SIFSLV_DIG_LN_RX0	0x200
#घोषणा SSPXTP_SIFSLV_DIG_LN_DAIF	0x300
#घोषणा SSPXTP_SIFSLV_PHYA_LN		0x400

#घोषणा XSP_U2FREQ_FMCR0	((SSUSB_SIFSLV_U2FREQ) + 0x00)
#घोषणा P2F_RG_FREQDET_EN	BIT(24)
#घोषणा P2F_RG_CYCLECNT		GENMASK(23, 0)
#घोषणा P2F_RG_CYCLECNT_VAL(x)	((P2F_RG_CYCLECNT) & (x))

#घोषणा XSP_U2FREQ_MMONR0  ((SSUSB_SIFSLV_U2FREQ) + 0x0c)

#घोषणा XSP_U2FREQ_FMMONR1	((SSUSB_SIFSLV_U2FREQ) + 0x10)
#घोषणा P2F_RG_FRCK_EN		BIT(8)
#घोषणा P2F_USB_FM_VALID	BIT(0)

#घोषणा XSP_USBPHYACR0	((SSUSB_SIFSLV_U2PHY_COM) + 0x00)
#घोषणा P2A0_RG_INTR_EN	BIT(5)

#घोषणा XSP_USBPHYACR1		((SSUSB_SIFSLV_U2PHY_COM) + 0x04)
#घोषणा P2A1_RG_INTR_CAL		GENMASK(23, 19)
#घोषणा P2A1_RG_INTR_CAL_VAL(x)	((0x1f & (x)) << 19)
#घोषणा P2A1_RG_VRT_SEL			GENMASK(14, 12)
#घोषणा P2A1_RG_VRT_SEL_VAL(x)	((0x7 & (x)) << 12)
#घोषणा P2A1_RG_TERM_SEL		GENMASK(10, 8)
#घोषणा P2A1_RG_TERM_SEL_VAL(x)	((0x7 & (x)) << 8)

#घोषणा XSP_USBPHYACR5		((SSUSB_SIFSLV_U2PHY_COM) + 0x014)
#घोषणा P2A5_RG_HSTX_SRCAL_EN	BIT(15)
#घोषणा P2A5_RG_HSTX_SRCTRL		GENMASK(14, 12)
#घोषणा P2A5_RG_HSTX_SRCTRL_VAL(x)	((0x7 & (x)) << 12)

#घोषणा XSP_USBPHYACR6		((SSUSB_SIFSLV_U2PHY_COM) + 0x018)
#घोषणा P2A6_RG_BC11_SW_EN	BIT(23)
#घोषणा P2A6_RG_OTG_VBUSCMP_EN	BIT(20)

#घोषणा XSP_U2PHYDTM1		((SSUSB_SIFSLV_U2PHY_COM) + 0x06C)
#घोषणा P2D_FORCE_IDDIG		BIT(9)
#घोषणा P2D_RG_VBUSVALID	BIT(5)
#घोषणा P2D_RG_SESSEND		BIT(4)
#घोषणा P2D_RG_AVALID		BIT(2)
#घोषणा P2D_RG_IDDIG		BIT(1)

#घोषणा SSPXTP_PHYA_GLB_00		((SSPXTP_SIFSLV_PHYA_GLB) + 0x00)
#घोषणा RG_XTP_GLB_BIAS_INTR_CTRL		GENMASK(21, 16)
#घोषणा RG_XTP_GLB_BIAS_INTR_CTRL_VAL(x)	((0x3f & (x)) << 16)

#घोषणा SSPXTP_PHYA_LN_04	((SSPXTP_SIFSLV_PHYA_LN) + 0x04)
#घोषणा RG_XTP_LN0_TX_IMPSEL		GENMASK(4, 0)
#घोषणा RG_XTP_LN0_TX_IMPSEL_VAL(x)	(0x1f & (x))

#घोषणा SSPXTP_PHYA_LN_14	((SSPXTP_SIFSLV_PHYA_LN) + 0x014)
#घोषणा RG_XTP_LN0_RX_IMPSEL		GENMASK(4, 0)
#घोषणा RG_XTP_LN0_RX_IMPSEL_VAL(x)	(0x1f & (x))

#घोषणा XSP_REF_CLK		26	/* MHZ */
#घोषणा XSP_SLEW_RATE_COEF	17
#घोषणा XSP_SR_COEF_DIVISOR	1000
#घोषणा XSP_FM_DET_CYCLE_CNT	1024

काष्ठा xsphy_instance अणु
	काष्ठा phy *phy;
	व्योम __iomem *port_base;
	काष्ठा clk *ref_clk;	/* reference घड़ी of anolog phy */
	u32 index;
	u32 type;
	/* only क्रम HQA test */
	पूर्णांक efuse_पूर्णांकr;
	पूर्णांक efuse_tx_imp;
	पूर्णांक efuse_rx_imp;
	/* u2 eye diagram */
	पूर्णांक eye_src;
	पूर्णांक eye_vrt;
	पूर्णांक eye_term;
पूर्ण;

काष्ठा mtk_xsphy अणु
	काष्ठा device *dev;
	व्योम __iomem *glb_base;	/* only shared u3 sअगर */
	काष्ठा xsphy_instance **phys;
	पूर्णांक nphys;
	पूर्णांक src_ref_clk; /* MHZ, reference घड़ी क्रम slew rate calibrate */
	पूर्णांक src_coef;    /* coefficient क्रम slew rate calibrate */
पूर्ण;

अटल व्योम u2_phy_slew_rate_calibrate(काष्ठा mtk_xsphy *xsphy,
					काष्ठा xsphy_instance *inst)
अणु
	व्योम __iomem *pbase = inst->port_base;
	पूर्णांक calib_val;
	पूर्णांक fm_out;
	u32 पंचांगp;

	/* use क्रमce value */
	अगर (inst->eye_src)
		वापस;

	/* enable USB ring oscillator */
	पंचांगp = पढ़ोl(pbase + XSP_USBPHYACR5);
	पंचांगp |= P2A5_RG_HSTX_SRCAL_EN;
	ग_लिखोl(पंचांगp, pbase + XSP_USBPHYACR5);
	udelay(1);	/* रुको घड़ी stable */

	/* enable मुक्त run घड़ी */
	पंचांगp = पढ़ोl(pbase + XSP_U2FREQ_FMMONR1);
	पंचांगp |= P2F_RG_FRCK_EN;
	ग_लिखोl(पंचांगp, pbase + XSP_U2FREQ_FMMONR1);

	/* set cycle count as 1024 */
	पंचांगp = पढ़ोl(pbase + XSP_U2FREQ_FMCR0);
	पंचांगp &= ~(P2F_RG_CYCLECNT);
	पंचांगp |= P2F_RG_CYCLECNT_VAL(XSP_FM_DET_CYCLE_CNT);
	ग_लिखोl(पंचांगp, pbase + XSP_U2FREQ_FMCR0);

	/* enable frequency meter */
	पंचांगp = पढ़ोl(pbase + XSP_U2FREQ_FMCR0);
	पंचांगp |= P2F_RG_FREQDET_EN;
	ग_लिखोl(पंचांगp, pbase + XSP_U2FREQ_FMCR0);

	/* ignore वापस value */
	पढ़ोl_poll_समयout(pbase + XSP_U2FREQ_FMMONR1, पंचांगp,
			   (पंचांगp & P2F_USB_FM_VALID), 10, 200);

	fm_out = पढ़ोl(pbase + XSP_U2FREQ_MMONR0);

	/* disable frequency meter */
	पंचांगp = पढ़ोl(pbase + XSP_U2FREQ_FMCR0);
	पंचांगp &= ~P2F_RG_FREQDET_EN;
	ग_लिखोl(पंचांगp, pbase + XSP_U2FREQ_FMCR0);

	/* disable मुक्त run घड़ी */
	पंचांगp = पढ़ोl(pbase + XSP_U2FREQ_FMMONR1);
	पंचांगp &= ~P2F_RG_FRCK_EN;
	ग_लिखोl(पंचांगp, pbase + XSP_U2FREQ_FMMONR1);

	अगर (fm_out) अणु
		/* (1024 / FM_OUT) x reference घड़ी frequency x coefficient */
		पंचांगp = xsphy->src_ref_clk * xsphy->src_coef;
		पंचांगp = (पंचांगp * XSP_FM_DET_CYCLE_CNT) / fm_out;
		calib_val = DIV_ROUND_CLOSEST(पंचांगp, XSP_SR_COEF_DIVISOR);
	पूर्ण अन्यथा अणु
		/* अगर FM detection fail, set शेष value */
		calib_val = 3;
	पूर्ण
	dev_dbg(xsphy->dev, "phy.%d, fm_out:%d, calib:%d (clk:%d, coef:%d)\n",
		inst->index, fm_out, calib_val,
		xsphy->src_ref_clk, xsphy->src_coef);

	/* set HS slew rate */
	पंचांगp = पढ़ोl(pbase + XSP_USBPHYACR5);
	पंचांगp &= ~P2A5_RG_HSTX_SRCTRL;
	पंचांगp |= P2A5_RG_HSTX_SRCTRL_VAL(calib_val);
	ग_लिखोl(पंचांगp, pbase + XSP_USBPHYACR5);

	/* disable USB ring oscillator */
	पंचांगp = पढ़ोl(pbase + XSP_USBPHYACR5);
	पंचांगp &= ~P2A5_RG_HSTX_SRCAL_EN;
	ग_लिखोl(पंचांगp, pbase + XSP_USBPHYACR5);
पूर्ण

अटल व्योम u2_phy_instance_init(काष्ठा mtk_xsphy *xsphy,
				 काष्ठा xsphy_instance *inst)
अणु
	व्योम __iomem *pbase = inst->port_base;
	u32 पंचांगp;

	/* DP/DM BC1.1 path Disable */
	पंचांगp = पढ़ोl(pbase + XSP_USBPHYACR6);
	पंचांगp &= ~P2A6_RG_BC11_SW_EN;
	ग_लिखोl(पंचांगp, pbase + XSP_USBPHYACR6);

	पंचांगp = पढ़ोl(pbase + XSP_USBPHYACR0);
	पंचांगp |= P2A0_RG_INTR_EN;
	ग_लिखोl(पंचांगp, pbase + XSP_USBPHYACR0);
पूर्ण

अटल व्योम u2_phy_instance_घातer_on(काष्ठा mtk_xsphy *xsphy,
				     काष्ठा xsphy_instance *inst)
अणु
	व्योम __iomem *pbase = inst->port_base;
	u32 index = inst->index;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(pbase + XSP_USBPHYACR6);
	पंचांगp |= P2A6_RG_OTG_VBUSCMP_EN;
	ग_लिखोl(पंचांगp, pbase + XSP_USBPHYACR6);

	पंचांगp = पढ़ोl(pbase + XSP_U2PHYDTM1);
	पंचांगp |= P2D_RG_VBUSVALID | P2D_RG_AVALID;
	पंचांगp &= ~P2D_RG_SESSEND;
	ग_लिखोl(पंचांगp, pbase + XSP_U2PHYDTM1);

	dev_dbg(xsphy->dev, "%s(%d)\n", __func__, index);
पूर्ण

अटल व्योम u2_phy_instance_घातer_off(काष्ठा mtk_xsphy *xsphy,
				      काष्ठा xsphy_instance *inst)
अणु
	व्योम __iomem *pbase = inst->port_base;
	u32 index = inst->index;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(pbase + XSP_USBPHYACR6);
	पंचांगp &= ~P2A6_RG_OTG_VBUSCMP_EN;
	ग_लिखोl(पंचांगp, pbase + XSP_USBPHYACR6);

	पंचांगp = पढ़ोl(pbase + XSP_U2PHYDTM1);
	पंचांगp &= ~(P2D_RG_VBUSVALID | P2D_RG_AVALID);
	पंचांगp |= P2D_RG_SESSEND;
	ग_लिखोl(पंचांगp, pbase + XSP_U2PHYDTM1);

	dev_dbg(xsphy->dev, "%s(%d)\n", __func__, index);
पूर्ण

अटल व्योम u2_phy_instance_set_mode(काष्ठा mtk_xsphy *xsphy,
				     काष्ठा xsphy_instance *inst,
				     क्रमागत phy_mode mode)
अणु
	u32 पंचांगp;

	पंचांगp = पढ़ोl(inst->port_base + XSP_U2PHYDTM1);
	चयन (mode) अणु
	हाल PHY_MODE_USB_DEVICE:
		पंचांगp |= P2D_FORCE_IDDIG | P2D_RG_IDDIG;
		अवरोध;
	हाल PHY_MODE_USB_HOST:
		पंचांगp |= P2D_FORCE_IDDIG;
		पंचांगp &= ~P2D_RG_IDDIG;
		अवरोध;
	हाल PHY_MODE_USB_OTG:
		पंचांगp &= ~(P2D_FORCE_IDDIG | P2D_RG_IDDIG);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	ग_लिखोl(पंचांगp, inst->port_base + XSP_U2PHYDTM1);
पूर्ण

अटल व्योम phy_parse_property(काष्ठा mtk_xsphy *xsphy,
				काष्ठा xsphy_instance *inst)
अणु
	काष्ठा device *dev = &inst->phy->dev;

	चयन (inst->type) अणु
	हाल PHY_TYPE_USB2:
		device_property_पढ़ो_u32(dev, "mediatek,efuse-intr",
					 &inst->efuse_पूर्णांकr);
		device_property_पढ़ो_u32(dev, "mediatek,eye-src",
					 &inst->eye_src);
		device_property_पढ़ो_u32(dev, "mediatek,eye-vrt",
					 &inst->eye_vrt);
		device_property_पढ़ो_u32(dev, "mediatek,eye-term",
					 &inst->eye_term);
		dev_dbg(dev, "intr:%d, src:%d, vrt:%d, term:%d\n",
			inst->efuse_पूर्णांकr, inst->eye_src,
			inst->eye_vrt, inst->eye_term);
		अवरोध;
	हाल PHY_TYPE_USB3:
		device_property_पढ़ो_u32(dev, "mediatek,efuse-intr",
					 &inst->efuse_पूर्णांकr);
		device_property_पढ़ो_u32(dev, "mediatek,efuse-tx-imp",
					 &inst->efuse_tx_imp);
		device_property_पढ़ो_u32(dev, "mediatek,efuse-rx-imp",
					 &inst->efuse_rx_imp);
		dev_dbg(dev, "intr:%d, tx-imp:%d, rx-imp:%d\n",
			inst->efuse_पूर्णांकr, inst->efuse_tx_imp,
			inst->efuse_rx_imp);
		अवरोध;
	शेष:
		dev_err(xsphy->dev, "incompatible phy type\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम u2_phy_props_set(काष्ठा mtk_xsphy *xsphy,
			     काष्ठा xsphy_instance *inst)
अणु
	व्योम __iomem *pbase = inst->port_base;
	u32 पंचांगp;

	अगर (inst->efuse_पूर्णांकr) अणु
		पंचांगp = पढ़ोl(pbase + XSP_USBPHYACR1);
		पंचांगp &= ~P2A1_RG_INTR_CAL;
		पंचांगp |= P2A1_RG_INTR_CAL_VAL(inst->efuse_पूर्णांकr);
		ग_लिखोl(पंचांगp, pbase + XSP_USBPHYACR1);
	पूर्ण

	अगर (inst->eye_src) अणु
		पंचांगp = पढ़ोl(pbase + XSP_USBPHYACR5);
		पंचांगp &= ~P2A5_RG_HSTX_SRCTRL;
		पंचांगp |= P2A5_RG_HSTX_SRCTRL_VAL(inst->eye_src);
		ग_लिखोl(पंचांगp, pbase + XSP_USBPHYACR5);
	पूर्ण

	अगर (inst->eye_vrt) अणु
		पंचांगp = पढ़ोl(pbase + XSP_USBPHYACR1);
		पंचांगp &= ~P2A1_RG_VRT_SEL;
		पंचांगp |= P2A1_RG_VRT_SEL_VAL(inst->eye_vrt);
		ग_लिखोl(पंचांगp, pbase + XSP_USBPHYACR1);
	पूर्ण

	अगर (inst->eye_term) अणु
		पंचांगp = पढ़ोl(pbase + XSP_USBPHYACR1);
		पंचांगp &= ~P2A1_RG_TERM_SEL;
		पंचांगp |= P2A1_RG_TERM_SEL_VAL(inst->eye_term);
		ग_लिखोl(पंचांगp, pbase + XSP_USBPHYACR1);
	पूर्ण
पूर्ण

अटल व्योम u3_phy_props_set(काष्ठा mtk_xsphy *xsphy,
			     काष्ठा xsphy_instance *inst)
अणु
	व्योम __iomem *pbase = inst->port_base;
	u32 पंचांगp;

	अगर (inst->efuse_पूर्णांकr) अणु
		पंचांगp = पढ़ोl(xsphy->glb_base + SSPXTP_PHYA_GLB_00);
		पंचांगp &= ~RG_XTP_GLB_BIAS_INTR_CTRL;
		पंचांगp |= RG_XTP_GLB_BIAS_INTR_CTRL_VAL(inst->efuse_पूर्णांकr);
		ग_लिखोl(पंचांगp, xsphy->glb_base + SSPXTP_PHYA_GLB_00);
	पूर्ण

	अगर (inst->efuse_tx_imp) अणु
		पंचांगp = पढ़ोl(pbase + SSPXTP_PHYA_LN_04);
		पंचांगp &= ~RG_XTP_LN0_TX_IMPSEL;
		पंचांगp |= RG_XTP_LN0_TX_IMPSEL_VAL(inst->efuse_tx_imp);
		ग_लिखोl(पंचांगp, pbase + SSPXTP_PHYA_LN_04);
	पूर्ण

	अगर (inst->efuse_rx_imp) अणु
		पंचांगp = पढ़ोl(pbase + SSPXTP_PHYA_LN_14);
		पंचांगp &= ~RG_XTP_LN0_RX_IMPSEL;
		पंचांगp |= RG_XTP_LN0_RX_IMPSEL_VAL(inst->efuse_rx_imp);
		ग_लिखोl(पंचांगp, pbase + SSPXTP_PHYA_LN_14);
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा xsphy_instance *inst = phy_get_drvdata(phy);
	काष्ठा mtk_xsphy *xsphy = dev_get_drvdata(phy->dev.parent);
	पूर्णांक ret;

	ret = clk_prepare_enable(inst->ref_clk);
	अगर (ret) अणु
		dev_err(xsphy->dev, "failed to enable ref_clk\n");
		वापस ret;
	पूर्ण

	चयन (inst->type) अणु
	हाल PHY_TYPE_USB2:
		u2_phy_instance_init(xsphy, inst);
		u2_phy_props_set(xsphy, inst);
		अवरोध;
	हाल PHY_TYPE_USB3:
		u3_phy_props_set(xsphy, inst);
		अवरोध;
	शेष:
		dev_err(xsphy->dev, "incompatible phy type\n");
		clk_disable_unprepare(inst->ref_clk);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा xsphy_instance *inst = phy_get_drvdata(phy);
	काष्ठा mtk_xsphy *xsphy = dev_get_drvdata(phy->dev.parent);

	अगर (inst->type == PHY_TYPE_USB2) अणु
		u2_phy_instance_घातer_on(xsphy, inst);
		u2_phy_slew_rate_calibrate(xsphy, inst);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा xsphy_instance *inst = phy_get_drvdata(phy);
	काष्ठा mtk_xsphy *xsphy = dev_get_drvdata(phy->dev.parent);

	अगर (inst->type == PHY_TYPE_USB2)
		u2_phy_instance_घातer_off(xsphy, inst);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा xsphy_instance *inst = phy_get_drvdata(phy);

	clk_disable_unprepare(inst->ref_clk);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_phy_set_mode(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	काष्ठा xsphy_instance *inst = phy_get_drvdata(phy);
	काष्ठा mtk_xsphy *xsphy = dev_get_drvdata(phy->dev.parent);

	अगर (inst->type == PHY_TYPE_USB2)
		u2_phy_instance_set_mode(xsphy, inst, mode);

	वापस 0;
पूर्ण

अटल काष्ठा phy *mtk_phy_xlate(काष्ठा device *dev,
				 काष्ठा of_phandle_args *args)
अणु
	काष्ठा mtk_xsphy *xsphy = dev_get_drvdata(dev);
	काष्ठा xsphy_instance *inst = शून्य;
	काष्ठा device_node *phy_np = args->np;
	पूर्णांक index;

	अगर (args->args_count != 1) अणु
		dev_err(dev, "invalid number of cells in 'phy' property\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	क्रम (index = 0; index < xsphy->nphys; index++)
		अगर (phy_np == xsphy->phys[index]->phy->dev.of_node) अणु
			inst = xsphy->phys[index];
			अवरोध;
		पूर्ण

	अगर (!inst) अणु
		dev_err(dev, "failed to find appropriate phy\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	inst->type = args->args[0];
	अगर (!(inst->type == PHY_TYPE_USB2 ||
	      inst->type == PHY_TYPE_USB3)) अणु
		dev_err(dev, "unsupported phy type: %d\n", inst->type);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	phy_parse_property(xsphy, inst);

	वापस inst->phy;
पूर्ण

अटल स्थिर काष्ठा phy_ops mtk_xsphy_ops = अणु
	.init		= mtk_phy_init,
	.निकास		= mtk_phy_निकास,
	.घातer_on	= mtk_phy_घातer_on,
	.घातer_off	= mtk_phy_घातer_off,
	.set_mode	= mtk_phy_set_mode,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_xsphy_id_table[] = अणु
	अणु .compatible = "mediatek,xsphy", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_xsphy_id_table);

अटल पूर्णांक mtk_xsphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *child_np;
	काष्ठा phy_provider *provider;
	काष्ठा resource *glb_res;
	काष्ठा mtk_xsphy *xsphy;
	काष्ठा resource res;
	पूर्णांक port, retval;

	xsphy = devm_kzalloc(dev, माप(*xsphy), GFP_KERNEL);
	अगर (!xsphy)
		वापस -ENOMEM;

	xsphy->nphys = of_get_child_count(np);
	xsphy->phys = devm_kसुस्मृति(dev, xsphy->nphys,
				       माप(*xsphy->phys), GFP_KERNEL);
	अगर (!xsphy->phys)
		वापस -ENOMEM;

	xsphy->dev = dev;
	platक्रमm_set_drvdata(pdev, xsphy);

	glb_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	/* optional, may not exist अगर no u3 phys */
	अगर (glb_res) अणु
		/* get banks shared by multiple u3 phys */
		xsphy->glb_base = devm_ioremap_resource(dev, glb_res);
		अगर (IS_ERR(xsphy->glb_base)) अणु
			dev_err(dev, "failed to remap glb regs\n");
			वापस PTR_ERR(xsphy->glb_base);
		पूर्ण
	पूर्ण

	xsphy->src_ref_clk = XSP_REF_CLK;
	xsphy->src_coef = XSP_SLEW_RATE_COEF;
	/* update parameters of slew rate calibrate अगर exist */
	device_property_पढ़ो_u32(dev, "mediatek,src-ref-clk-mhz",
				 &xsphy->src_ref_clk);
	device_property_पढ़ो_u32(dev, "mediatek,src-coef", &xsphy->src_coef);

	port = 0;
	क्रम_each_child_of_node(np, child_np) अणु
		काष्ठा xsphy_instance *inst;
		काष्ठा phy *phy;

		inst = devm_kzalloc(dev, माप(*inst), GFP_KERNEL);
		अगर (!inst) अणु
			retval = -ENOMEM;
			जाओ put_child;
		पूर्ण

		xsphy->phys[port] = inst;

		phy = devm_phy_create(dev, child_np, &mtk_xsphy_ops);
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

		inst->port_base = devm_ioremap_resource(&phy->dev, &res);
		अगर (IS_ERR(inst->port_base)) अणु
			dev_err(dev, "failed to remap phy regs\n");
			retval = PTR_ERR(inst->port_base);
			जाओ put_child;
		पूर्ण

		inst->phy = phy;
		inst->index = port;
		phy_set_drvdata(phy, inst);
		port++;

		inst->ref_clk = devm_clk_get(&phy->dev, "ref");
		अगर (IS_ERR(inst->ref_clk)) अणु
			dev_err(dev, "failed to get ref_clk(id-%d)\n", port);
			retval = PTR_ERR(inst->ref_clk);
			जाओ put_child;
		पूर्ण
	पूर्ण

	provider = devm_of_phy_provider_रेजिस्टर(dev, mtk_phy_xlate);
	वापस PTR_ERR_OR_ZERO(provider);

put_child:
	of_node_put(child_np);
	वापस retval;
पूर्ण

अटल काष्ठा platक्रमm_driver mtk_xsphy_driver = अणु
	.probe		= mtk_xsphy_probe,
	.driver		= अणु
		.name	= "mtk-xsphy",
		.of_match_table = mtk_xsphy_id_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_xsphy_driver);

MODULE_AUTHOR("Chunfeng Yun <chunfeng.yun@mediatek.com>");
MODULE_DESCRIPTION("MediaTek USB XS-PHY driver");
MODULE_LICENSE("GPL v2");
