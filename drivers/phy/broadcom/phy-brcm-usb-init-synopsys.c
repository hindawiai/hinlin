<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Broadcom */

/*
 * This module contains USB PHY initialization क्रम घातer up and S3 resume
 * क्रम newer Synopsys based USB hardware first used on the bcm7216.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>

#समावेश <linux/soc/brcmstb/brcmstb.h>
#समावेश "phy-brcm-usb-init.h"

#घोषणा PHY_LOCK_TIMEOUT_MS 200

/* Register definitions क्रम syscon piarbctl रेजिस्टरs */
#घोषणा PIARBCTL_CAM			0x00
#घोषणा PIARBCTL_SPLITTER		0x04
#घोषणा PIARBCTL_MISC			0x08
#घोषणा   PIARBCTL_MISC_SECURE_MASK			0x80000000
#घोषणा   PIARBCTL_MISC_USB_SELECT_MASK			0x40000000
#घोषणा   PIARBCTL_MISC_USB_4G_SDRAM_MASK		0x20000000
#घोषणा   PIARBCTL_MISC_USB_PRIORITY_MASK		0x000f0000
#घोषणा   PIARBCTL_MISC_USB_MEM_PAGE_MASK		0x0000f000
#घोषणा   PIARBCTL_MISC_CAM1_MEM_PAGE_MASK		0x00000f00
#घोषणा   PIARBCTL_MISC_CAM0_MEM_PAGE_MASK		0x000000f0
#घोषणा   PIARBCTL_MISC_SATA_PRIORITY_MASK		0x0000000f

#घोषणा PIARBCTL_MISC_USB_ONLY_MASK		\
	(PIARBCTL_MISC_USB_SELECT_MASK |	\
	 PIARBCTL_MISC_USB_4G_SDRAM_MASK |	\
	 PIARBCTL_MISC_USB_PRIORITY_MASK |	\
	 PIARBCTL_MISC_USB_MEM_PAGE_MASK)

/* Register definitions क्रम the USB CTRL block */
#घोषणा USB_CTRL_SETUP			0x00
#घोषणा   USB_CTRL_SETUP_STRAP_IPP_SEL_MASK		0x02000000
#घोषणा   USB_CTRL_SETUP_SCB2_EN_MASK			0x00008000
#घोषणा   USB_CTRL_SETUP_tca_drv_sel_MASK		0x01000000
#घोषणा   USB_CTRL_SETUP_SCB1_EN_MASK			0x00004000
#घोषणा   USB_CTRL_SETUP_SOFT_SHUTDOWN_MASK		0x00000200
#घोषणा   USB_CTRL_SETUP_IPP_MASK			0x00000020
#घोषणा   USB_CTRL_SETUP_IOC_MASK			0x00000010
#घोषणा USB_CTRL_USB_PM			0x04
#घोषणा   USB_CTRL_USB_PM_USB_PWRDN_MASK		0x80000000
#घोषणा   USB_CTRL_USB_PM_SOFT_RESET_MASK		0x40000000
#घोषणा   USB_CTRL_USB_PM_BDC_SOFT_RESETB_MASK		0x00800000
#घोषणा   USB_CTRL_USB_PM_XHC_SOFT_RESETB_MASK		0x00400000
#घोषणा USB_CTRL_USB_PM_STATUS		0x08
#घोषणा USB_CTRL_USB_DEVICE_CTL1	0x10
#घोषणा   USB_CTRL_USB_DEVICE_CTL1_PORT_MODE_MASK	0x00000003
#घोषणा USB_CTRL_TEST_PORT_CTL		0x30
#घोषणा   USB_CTRL_TEST_PORT_CTL_TPOUT_SEL_MASK	0x000000ff
#घोषणा   USB_CTRL_TEST_PORT_CTL_TPOUT_SEL_PME_GEN_MASK	0x0000002e
#घोषणा USB_CTRL_TP_DIAG1		0x34
#घोषणा   USB_CTLR_TP_DIAG1_wake_MASK	0x00000002
#घोषणा USB_CTRL_CTLR_CSHCR		0x50
#घोषणा   USB_CTRL_CTLR_CSHCR_ctl_pme_en_MASK	0x00040000

/* Register definitions क्रम the USB_PHY block in 7211b0 */
#घोषणा USB_PHY_PLL_CTL			0x00
#घोषणा   USB_PHY_PLL_CTL_PLL_RESETB_MASK		0x40000000
#घोषणा USB_PHY_PLL_LDO_CTL		0x08
#घोषणा   USB_PHY_PLL_LDO_CTL_AFE_CORERDY_MASK		0x00000004
#घोषणा   USB_PHY_PLL_LDO_CTL_AFE_LDO_PWRDWNB_MASK	0x00000002
#घोषणा   USB_PHY_PLL_LDO_CTL_AFE_BG_PWRDWNB_MASK	0x00000001
#घोषणा USB_PHY_UTMI_CTL_1		0x04
#घोषणा   USB_PHY_UTMI_CTL_1_POWER_UP_FSM_EN_MASK	0x00000800
#घोषणा   USB_PHY_UTMI_CTL_1_PHY_MODE_MASK		0x0000000c
#घोषणा   USB_PHY_UTMI_CTL_1_PHY_MODE_SHIFT		2
#घोषणा USB_PHY_IDDQ			0x1c
#घोषणा   USB_PHY_IDDQ_phy_iddq_MASK			0x00000001
#घोषणा USB_PHY_STATUS			0x20
#घोषणा   USB_PHY_STATUS_pll_lock_MASK			0x00000001

/* Register definitions क्रम the MDIO रेजिस्टरs in the DWC2 block of
 * the 7211b0.
 * NOTE: The PHY's MDIO रेजिस्टरs are only accessible through the
 * legacy DesignWare USB controller even though it's not being used.
 */
#घोषणा USB_GMDIOCSR	0
#घोषणा USB_GMDIOGEN	4

/* Register definitions क्रम the BDC EC block in 7211b0 */
#घोषणा BDC_EC_AXIRDA			0x0c
#घोषणा   BDC_EC_AXIRDA_RTS_MASK			0xf0000000
#घोषणा   BDC_EC_AXIRDA_RTS_SHIFT			28


अटल व्योम usb_mdio_ग_लिखो_7211b0(काष्ठा brcm_usb_init_params *params,
				  uपूर्णांक8_t addr, uपूर्णांक16_t data)
अणु
	व्योम __iomem *usb_mdio = params->regs[BRCM_REGS_USB_MDIO];

	addr &= 0x1f; /* 5-bit address */
	brcm_usb_ग_लिखोl(0xffffffff, usb_mdio + USB_GMDIOGEN);
	जबतक (brcm_usb_पढ़ोl(usb_mdio + USB_GMDIOCSR) & (1<<31))
		;
	brcm_usb_ग_लिखोl(0x59020000 | (addr << 18) | data,
			usb_mdio + USB_GMDIOGEN);
	जबतक (brcm_usb_पढ़ोl(usb_mdio + USB_GMDIOCSR) & (1<<31))
		;
	brcm_usb_ग_लिखोl(0x00000000, usb_mdio + USB_GMDIOGEN);
	जबतक (brcm_usb_पढ़ोl(usb_mdio + USB_GMDIOCSR) & (1<<31))
		;
पूर्ण

अटल uपूर्णांक16_t __maybe_unused usb_mdio_पढ़ो_7211b0(
	काष्ठा brcm_usb_init_params *params, uपूर्णांक8_t addr)
अणु
	व्योम __iomem *usb_mdio = params->regs[BRCM_REGS_USB_MDIO];

	addr &= 0x1f; /* 5-bit address */
	brcm_usb_ग_लिखोl(0xffffffff, usb_mdio + USB_GMDIOGEN);
	जबतक (brcm_usb_पढ़ोl(usb_mdio + USB_GMDIOCSR) & (1<<31))
		;
	brcm_usb_ग_लिखोl(0x69020000 | (addr << 18), usb_mdio + USB_GMDIOGEN);
	जबतक (brcm_usb_पढ़ोl(usb_mdio + USB_GMDIOCSR) & (1<<31))
		;
	brcm_usb_ग_लिखोl(0x00000000, usb_mdio + USB_GMDIOGEN);
	जबतक (brcm_usb_पढ़ोl(usb_mdio + USB_GMDIOCSR) & (1<<31))
		;
	वापस brcm_usb_पढ़ोl(usb_mdio + USB_GMDIOCSR) & 0xffff;
पूर्ण

अटल व्योम usb2_eye_fix_7211b0(काष्ठा brcm_usb_init_params *params)
अणु
	/* select bank */
	usb_mdio_ग_लिखो_7211b0(params, 0x1f, 0x80a0);

	/* Set the eye */
	usb_mdio_ग_लिखो_7211b0(params, 0x0a, 0xc6a0);
पूर्ण

अटल व्योम xhci_soft_reset(काष्ठा brcm_usb_init_params *params,
			पूर्णांक on_off)
अणु
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];

	/* Assert reset */
	अगर (on_off)
		USB_CTRL_UNSET(ctrl, USB_PM, XHC_SOFT_RESETB);
	/* De-निश्चित reset */
	अन्यथा
		USB_CTRL_SET(ctrl, USB_PM, XHC_SOFT_RESETB);
पूर्ण

अटल व्योम usb_init_ipp(काष्ठा brcm_usb_init_params *params)
अणु
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];
	u32 reg;
	u32 orig_reg;

	pr_debug("%s\n", __func__);

	orig_reg = reg = brcm_usb_पढ़ोl(USB_CTRL_REG(ctrl, SETUP));
	अगर (params->ipp != 2)
		/* override ipp strap pin (अगर it निकासs) */
		reg &= ~(USB_CTRL_MASK(SETUP, STRAP_IPP_SEL));

	/* Override the शेष OC and PP polarity */
	reg &= ~(USB_CTRL_MASK(SETUP, IPP) | USB_CTRL_MASK(SETUP, IOC));
	अगर (params->ioc)
		reg |= USB_CTRL_MASK(SETUP, IOC);
	अगर (params->ipp == 1)
		reg |= USB_CTRL_MASK(SETUP, IPP);
	brcm_usb_ग_लिखोl(reg, USB_CTRL_REG(ctrl, SETUP));

	/*
	 * If we're changing IPP, make sure घातer is off दीर्घ enough
	 * to turn off any connected devices.
	 */
	अगर ((reg ^ orig_reg) & USB_CTRL_MASK(SETUP, IPP))
		msleep(50);
पूर्ण

अटल व्योम syscon_piarbctl_init(काष्ठा regmap *rmap)
अणु
	/* Switch from legacy USB OTG controller to new STB USB controller */
	regmap_update_bits(rmap, PIARBCTL_MISC, PIARBCTL_MISC_USB_ONLY_MASK,
			   PIARBCTL_MISC_USB_SELECT_MASK |
			   PIARBCTL_MISC_USB_4G_SDRAM_MASK);
पूर्ण

अटल व्योम usb_init_common(काष्ठा brcm_usb_init_params *params)
अणु
	u32 reg;
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];

	pr_debug("%s\n", __func__);

	USB_CTRL_UNSET(ctrl, USB_PM, USB_PWRDN);
	/* 1 millisecond - क्रम USB घड़ीs to settle करोwn */
	usleep_range(1000, 2000);

	अगर (USB_CTRL_MASK(USB_DEVICE_CTL1, PORT_MODE)) अणु
		reg = brcm_usb_पढ़ोl(USB_CTRL_REG(ctrl, USB_DEVICE_CTL1));
		reg &= ~USB_CTRL_MASK(USB_DEVICE_CTL1, PORT_MODE);
		reg |= params->mode;
		brcm_usb_ग_लिखोl(reg, USB_CTRL_REG(ctrl, USB_DEVICE_CTL1));
	पूर्ण
	चयन (params->mode) अणु
	हाल USB_CTLR_MODE_HOST:
		USB_CTRL_UNSET(ctrl, USB_PM, BDC_SOFT_RESETB);
		अवरोध;
	शेष:
		USB_CTRL_UNSET(ctrl, USB_PM, BDC_SOFT_RESETB);
		USB_CTRL_SET(ctrl, USB_PM, BDC_SOFT_RESETB);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम usb_wake_enable_7211b0(काष्ठा brcm_usb_init_params *params,
				   bool enable)
अणु
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];

	अगर (enable)
		USB_CTRL_SET(ctrl, CTLR_CSHCR, ctl_pme_en);
	अन्यथा
		USB_CTRL_UNSET(ctrl, CTLR_CSHCR, ctl_pme_en);
पूर्ण

अटल व्योम usb_init_common_7211b0(काष्ठा brcm_usb_init_params *params)
अणु
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];
	व्योम __iomem *usb_phy = params->regs[BRCM_REGS_USB_PHY];
	व्योम __iomem *bdc_ec = params->regs[BRCM_REGS_BDC_EC];
	पूर्णांक समयout_ms = PHY_LOCK_TIMEOUT_MS;
	u32 reg;

	अगर (params->syscon_piarbctl)
		syscon_piarbctl_init(params->syscon_piarbctl);

	USB_CTRL_UNSET(ctrl, USB_PM, USB_PWRDN);

	usb_wake_enable_7211b0(params, false);
	अगर (!params->wake_enabled) अणु

		/* unकरो possible suspend settings */
		brcm_usb_ग_लिखोl(0, usb_phy + USB_PHY_IDDQ);
		reg = brcm_usb_पढ़ोl(usb_phy + USB_PHY_PLL_CTL);
		reg |= USB_PHY_PLL_CTL_PLL_RESETB_MASK;
		brcm_usb_ग_लिखोl(reg, usb_phy + USB_PHY_PLL_CTL);

		/* temporarily enable FSM so PHY comes up properly */
		reg = brcm_usb_पढ़ोl(usb_phy + USB_PHY_UTMI_CTL_1);
		reg |= USB_PHY_UTMI_CTL_1_POWER_UP_FSM_EN_MASK;
		brcm_usb_ग_लिखोl(reg, usb_phy + USB_PHY_UTMI_CTL_1);
	पूर्ण

	/* Init the PHY */
	reg = USB_PHY_PLL_LDO_CTL_AFE_CORERDY_MASK |
		USB_PHY_PLL_LDO_CTL_AFE_LDO_PWRDWNB_MASK |
		USB_PHY_PLL_LDO_CTL_AFE_BG_PWRDWNB_MASK;
	brcm_usb_ग_लिखोl(reg, usb_phy + USB_PHY_PLL_LDO_CTL);

	/* रुको क्रम lock */
	जबतक (समयout_ms-- > 0) अणु
		reg = brcm_usb_पढ़ोl(usb_phy + USB_PHY_STATUS);
		अगर (reg & USB_PHY_STATUS_pll_lock_MASK)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण

	/* Set the PHY_MODE */
	reg = brcm_usb_पढ़ोl(usb_phy + USB_PHY_UTMI_CTL_1);
	reg &= ~USB_PHY_UTMI_CTL_1_PHY_MODE_MASK;
	reg |= params->mode << USB_PHY_UTMI_CTL_1_PHY_MODE_SHIFT;
	brcm_usb_ग_लिखोl(reg, usb_phy + USB_PHY_UTMI_CTL_1);

	usb_init_common(params);

	/*
	 * The BDC controller will get occasional failures with
	 * the शेष "Read Transaction Size" of 6 (1024 bytes).
	 * Set it to 4 (256 bytes).
	 */
	अगर ((params->mode != USB_CTLR_MODE_HOST) && bdc_ec) अणु
		reg = brcm_usb_पढ़ोl(bdc_ec + BDC_EC_AXIRDA);
		reg &= ~BDC_EC_AXIRDA_RTS_MASK;
		reg |= (0x4 << BDC_EC_AXIRDA_RTS_SHIFT);
		brcm_usb_ग_लिखोl(reg, bdc_ec + BDC_EC_AXIRDA);
	पूर्ण

	/*
	 * Disable FSM, otherwise the PHY will स्वतः suspend when no
	 * device is connected and will be reset on resume.
	 */
	reg = brcm_usb_पढ़ोl(usb_phy + USB_PHY_UTMI_CTL_1);
	reg &= ~USB_PHY_UTMI_CTL_1_POWER_UP_FSM_EN_MASK;
	brcm_usb_ग_लिखोl(reg, usb_phy + USB_PHY_UTMI_CTL_1);

	usb2_eye_fix_7211b0(params);
पूर्ण

अटल व्योम usb_init_xhci(काष्ठा brcm_usb_init_params *params)
अणु
	pr_debug("%s\n", __func__);

	xhci_soft_reset(params, 0);
पूर्ण

अटल व्योम usb_uninit_common(काष्ठा brcm_usb_init_params *params)
अणु
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];

	pr_debug("%s\n", __func__);

	USB_CTRL_SET(ctrl, USB_PM, USB_PWRDN);

पूर्ण

अटल व्योम usb_uninit_common_7211b0(काष्ठा brcm_usb_init_params *params)
अणु
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];
	व्योम __iomem *usb_phy = params->regs[BRCM_REGS_USB_PHY];
	u32 reg;

	pr_debug("%s\n", __func__);

	अगर (params->wake_enabled) अणु
		USB_CTRL_SET(ctrl, TEST_PORT_CTL, TPOUT_SEL_PME_GEN);
		usb_wake_enable_7211b0(params, true);
	पूर्ण अन्यथा अणु
		USB_CTRL_SET(ctrl, USB_PM, USB_PWRDN);
		brcm_usb_ग_लिखोl(0, usb_phy + USB_PHY_PLL_LDO_CTL);
		reg = brcm_usb_पढ़ोl(usb_phy + USB_PHY_PLL_CTL);
		reg &= ~USB_PHY_PLL_CTL_PLL_RESETB_MASK;
		brcm_usb_ग_लिखोl(reg, usb_phy + USB_PHY_PLL_CTL);
		brcm_usb_ग_लिखोl(USB_PHY_IDDQ_phy_iddq_MASK,
				usb_phy + USB_PHY_IDDQ);
	पूर्ण

पूर्ण

अटल व्योम usb_uninit_xhci(काष्ठा brcm_usb_init_params *params)
अणु

	pr_debug("%s\n", __func__);

	अगर (!params->wake_enabled)
		xhci_soft_reset(params, 1);
पूर्ण

अटल पूर्णांक usb_get_dual_select(काष्ठा brcm_usb_init_params *params)
अणु
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];
	u32 reg = 0;

	pr_debug("%s\n", __func__);

	reg = brcm_usb_पढ़ोl(USB_CTRL_REG(ctrl, USB_DEVICE_CTL1));
	reg &= USB_CTRL_MASK(USB_DEVICE_CTL1, PORT_MODE);
	वापस reg;
पूर्ण

अटल व्योम usb_set_dual_select(काष्ठा brcm_usb_init_params *params, पूर्णांक mode)
अणु
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];
	u32 reg;

	pr_debug("%s\n", __func__);

	reg = brcm_usb_पढ़ोl(USB_CTRL_REG(ctrl, USB_DEVICE_CTL1));
	reg &= ~USB_CTRL_MASK(USB_DEVICE_CTL1, PORT_MODE);
	reg |= mode;
	brcm_usb_ग_लिखोl(reg, USB_CTRL_REG(ctrl, USB_DEVICE_CTL1));
पूर्ण

अटल स्थिर काष्ठा brcm_usb_init_ops bcm7216_ops = अणु
	.init_ipp = usb_init_ipp,
	.init_common = usb_init_common,
	.init_xhci = usb_init_xhci,
	.uninit_common = usb_uninit_common,
	.uninit_xhci = usb_uninit_xhci,
	.get_dual_select = usb_get_dual_select,
	.set_dual_select = usb_set_dual_select,
पूर्ण;

अटल स्थिर काष्ठा brcm_usb_init_ops bcm7211b0_ops = अणु
	.init_ipp = usb_init_ipp,
	.init_common = usb_init_common_7211b0,
	.init_xhci = usb_init_xhci,
	.uninit_common = usb_uninit_common_7211b0,
	.uninit_xhci = usb_uninit_xhci,
	.get_dual_select = usb_get_dual_select,
	.set_dual_select = usb_set_dual_select,
पूर्ण;

व्योम brcm_usb_dvr_init_7216(काष्ठा brcm_usb_init_params *params)
अणु

	pr_debug("%s\n", __func__);

	params->family_name = "7216";
	params->ops = &bcm7216_ops;
पूर्ण

व्योम brcm_usb_dvr_init_7211b0(काष्ठा brcm_usb_init_params *params)
अणु

	pr_debug("%s\n", __func__);

	params->family_name = "7211";
	params->ops = &bcm7211b0_ops;
	params->suspend_with_घड़ीs = true;
पूर्ण
