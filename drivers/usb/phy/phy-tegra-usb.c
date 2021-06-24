<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010 Google, Inc.
 * Copyright (C) 2013 NVIDIA Corporation
 *
 * Author:
 *	Erik Gilling <konkers@google.com>
 *	Benoit Goby <benoit@android.com>
 *	Venu Byravarasu <vbyravarasu@nvidia.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/resource.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश <linux/regulator/consumer.h>

#समावेश <linux/usb/ehci_def.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/usb/tegra_usb_phy.h>
#समावेश <linux/usb/ulpi.h>

#घोषणा ULPI_VIEWPORT				0x170

/* PORTSC PTS/PHCD bits, Tegra20 only */
#घोषणा TEGRA_USB_PORTSC1			0x184
#घोषणा TEGRA_USB_PORTSC1_PTS(x)		(((x) & 0x3) << 30)
#घोषणा TEGRA_USB_PORTSC1_PHCD			BIT(23)

/* HOSTPC1 PTS/PHCD bits, Tegra30 and above */
#घोषणा TEGRA_USB_HOSTPC1_DEVLC			0x1b4
#घोषणा TEGRA_USB_HOSTPC1_DEVLC_PTS(x)		(((x) & 0x7) << 29)
#घोषणा TEGRA_USB_HOSTPC1_DEVLC_PHCD		BIT(22)

/* Bits of PORTSC1, which will get cleared by writing 1 पूर्णांकo them */
#घोषणा TEGRA_PORTSC1_RWC_BITS	(PORT_CSC | PORT_PEC | PORT_OCC)

#घोषणा USB_SUSP_CTRL				0x400
#घोषणा   USB_WAKE_ON_RESUME_EN			BIT(2)
#घोषणा   USB_WAKE_ON_CNNT_EN_DEV		BIT(3)
#घोषणा   USB_WAKE_ON_DISCON_EN_DEV		BIT(4)
#घोषणा   USB_SUSP_CLR				BIT(5)
#घोषणा   USB_PHY_CLK_VALID			BIT(7)
#घोषणा   UTMIP_RESET				BIT(11)
#घोषणा   UHSIC_RESET				BIT(11)
#घोषणा   UTMIP_PHY_ENABLE			BIT(12)
#घोषणा   ULPI_PHY_ENABLE			BIT(13)
#घोषणा   USB_SUSP_SET				BIT(14)
#घोषणा   USB_WAKEUP_DEBOUNCE_COUNT(x)		(((x) & 0x7) << 16)

#घोषणा USB_PHY_VBUS_SENSORS			0x404
#घोषणा   B_SESS_VLD_WAKEUP_EN			BIT(6)
#घोषणा   B_VBUS_VLD_WAKEUP_EN			BIT(14)
#घोषणा   A_SESS_VLD_WAKEUP_EN			BIT(22)
#घोषणा   A_VBUS_VLD_WAKEUP_EN			BIT(30)

#घोषणा USB_PHY_VBUS_WAKEUP_ID			0x408
#घोषणा   VBUS_WAKEUP_WAKEUP_EN			BIT(30)

#घोषणा USB1_LEGACY_CTRL			0x410
#घोषणा   USB1_NO_LEGACY_MODE			BIT(0)
#घोषणा   USB1_VBUS_SENSE_CTL_MASK		(3 << 1)
#घोषणा   USB1_VBUS_SENSE_CTL_VBUS_WAKEUP	(0 << 1)
#घोषणा   USB1_VBUS_SENSE_CTL_AB_SESS_VLD_OR_VBUS_WAKEUP \
						(1 << 1)
#घोषणा   USB1_VBUS_SENSE_CTL_AB_SESS_VLD	(2 << 1)
#घोषणा   USB1_VBUS_SENSE_CTL_A_SESS_VLD	(3 << 1)

#घोषणा ULPI_TIMING_CTRL_0			0x424
#घोषणा   ULPI_OUTPUT_PINMUX_BYP		BIT(10)
#घोषणा   ULPI_CLKOUT_PINMUX_BYP		BIT(11)

#घोषणा ULPI_TIMING_CTRL_1			0x428
#घोषणा   ULPI_DATA_TRIMMER_LOAD		BIT(0)
#घोषणा   ULPI_DATA_TRIMMER_SEL(x)		(((x) & 0x7) << 1)
#घोषणा   ULPI_STPसूचीNXT_TRIMMER_LOAD		BIT(16)
#घोषणा   ULPI_STPसूचीNXT_TRIMMER_SEL(x)		(((x) & 0x7) << 17)
#घोषणा   ULPI_सूची_TRIMMER_LOAD			BIT(24)
#घोषणा   ULPI_सूची_TRIMMER_SEL(x)		(((x) & 0x7) << 25)

#घोषणा UTMIP_PLL_CFG1				0x804
#घोषणा   UTMIP_XTAL_FREQ_COUNT(x)		(((x) & 0xfff) << 0)
#घोषणा   UTMIP_PLLU_ENABLE_DLY_COUNT(x)	(((x) & 0x1f) << 27)

#घोषणा UTMIP_XCVR_CFG0				0x808
#घोषणा   UTMIP_XCVR_SETUP(x)			(((x) & 0xf) << 0)
#घोषणा   UTMIP_XCVR_SETUP_MSB(x)		((((x) & 0x70) >> 4) << 22)
#घोषणा   UTMIP_XCVR_LSRSLEW(x)			(((x) & 0x3) << 8)
#घोषणा   UTMIP_XCVR_LSFSLEW(x)			(((x) & 0x3) << 10)
#घोषणा   UTMIP_FORCE_PD_POWERDOWN		BIT(14)
#घोषणा   UTMIP_FORCE_PD2_POWERDOWN		BIT(16)
#घोषणा   UTMIP_FORCE_PDZI_POWERDOWN		BIT(18)
#घोषणा   UTMIP_XCVR_LSBIAS_SEL			BIT(21)
#घोषणा   UTMIP_XCVR_HSSLEW(x)			(((x) & 0x3) << 4)
#घोषणा   UTMIP_XCVR_HSSLEW_MSB(x)		((((x) & 0x1fc) >> 2) << 25)

#घोषणा UTMIP_BIAS_CFG0				0x80c
#घोषणा   UTMIP_OTGPD				BIT(11)
#घोषणा   UTMIP_BIASPD				BIT(10)
#घोषणा   UTMIP_HSSQUELCH_LEVEL(x)		(((x) & 0x3) << 0)
#घोषणा   UTMIP_HSDISCON_LEVEL(x)		(((x) & 0x3) << 2)
#घोषणा   UTMIP_HSDISCON_LEVEL_MSB(x)		((((x) & 0x4) >> 2) << 24)

#घोषणा UTMIP_HSRX_CFG0				0x810
#घोषणा   UTMIP_ELASTIC_LIMIT(x)		(((x) & 0x1f) << 10)
#घोषणा   UTMIP_IDLE_WAIT(x)			(((x) & 0x1f) << 15)

#घोषणा UTMIP_HSRX_CFG1				0x814
#घोषणा   UTMIP_HS_SYNC_START_DLY(x)		(((x) & 0x1f) << 1)

#घोषणा UTMIP_TX_CFG0				0x820
#घोषणा   UTMIP_FS_PREABMLE_J			BIT(19)
#घोषणा   UTMIP_HS_DISCON_DISABLE		BIT(8)

#घोषणा UTMIP_MISC_CFG0				0x824
#घोषणा   UTMIP_DPDM_OBSERVE			BIT(26)
#घोषणा   UTMIP_DPDM_OBSERVE_SEL(x)		(((x) & 0xf) << 27)
#घोषणा   UTMIP_DPDM_OBSERVE_SEL_FS_J		UTMIP_DPDM_OBSERVE_SEL(0xf)
#घोषणा   UTMIP_DPDM_OBSERVE_SEL_FS_K		UTMIP_DPDM_OBSERVE_SEL(0xe)
#घोषणा   UTMIP_DPDM_OBSERVE_SEL_FS_SE1		UTMIP_DPDM_OBSERVE_SEL(0xd)
#घोषणा   UTMIP_DPDM_OBSERVE_SEL_FS_SE0		UTMIP_DPDM_OBSERVE_SEL(0xc)
#घोषणा   UTMIP_SUSPEND_EXIT_ON_EDGE		BIT(22)

#घोषणा UTMIP_MISC_CFG1				0x828
#घोषणा   UTMIP_PLL_ACTIVE_DLY_COUNT(x)		(((x) & 0x1f) << 18)
#घोषणा   UTMIP_PLLU_STABLE_COUNT(x)		(((x) & 0xfff) << 6)

#घोषणा UTMIP_DEBOUNCE_CFG0			0x82c
#घोषणा   UTMIP_BIAS_DEBOUNCE_A(x)		(((x) & 0xffff) << 0)

#घोषणा UTMIP_BAT_CHRG_CFG0			0x830
#घोषणा   UTMIP_PD_CHRG				BIT(0)

#घोषणा UTMIP_SPARE_CFG0			0x834
#घोषणा   FUSE_SETUP_SEL			BIT(3)

#घोषणा UTMIP_XCVR_CFG1				0x838
#घोषणा   UTMIP_FORCE_PDDISC_POWERDOWN		BIT(0)
#घोषणा   UTMIP_FORCE_PDCHRP_POWERDOWN		BIT(2)
#घोषणा   UTMIP_FORCE_PDDR_POWERDOWN		BIT(4)
#घोषणा   UTMIP_XCVR_TERM_RANGE_ADJ(x)		(((x) & 0xf) << 18)

#घोषणा UTMIP_BIAS_CFG1				0x83c
#घोषणा   UTMIP_BIAS_PDTRK_COUNT(x)		(((x) & 0x1f) << 3)

/* For Tegra30 and above only, the address is dअगरferent in Tegra20 */
#घोषणा USB_USBMODE				0x1f8
#घोषणा   USB_USBMODE_MASK			(3 << 0)
#घोषणा   USB_USBMODE_HOST			(3 << 0)
#घोषणा   USB_USBMODE_DEVICE			(2 << 0)

अटल DEFINE_SPINLOCK(uपंचांगip_pad_lock);
अटल अचिन्हित पूर्णांक uपंचांगip_pad_count;

काष्ठा tegra_xtal_freq अणु
	अचिन्हित पूर्णांक freq;
	u8 enable_delay;
	u8 stable_count;
	u8 active_delay;
	u8 xtal_freq_count;
	u16 debounce;
पूर्ण;

अटल स्थिर काष्ठा tegra_xtal_freq tegra_freq_table[] = अणु
	अणु
		.freq = 12000000,
		.enable_delay = 0x02,
		.stable_count = 0x2F,
		.active_delay = 0x04,
		.xtal_freq_count = 0x76,
		.debounce = 0x7530,
	पूर्ण,
	अणु
		.freq = 13000000,
		.enable_delay = 0x02,
		.stable_count = 0x33,
		.active_delay = 0x05,
		.xtal_freq_count = 0x7F,
		.debounce = 0x7EF4,
	पूर्ण,
	अणु
		.freq = 19200000,
		.enable_delay = 0x03,
		.stable_count = 0x4B,
		.active_delay = 0x06,
		.xtal_freq_count = 0xBB,
		.debounce = 0xBB80,
	पूर्ण,
	अणु
		.freq = 26000000,
		.enable_delay = 0x04,
		.stable_count = 0x66,
		.active_delay = 0x09,
		.xtal_freq_count = 0xFE,
		.debounce = 0xFDE8,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा tegra_usb_phy *to_tegra_usb_phy(काष्ठा usb_phy *u_phy)
अणु
	वापस container_of(u_phy, काष्ठा tegra_usb_phy, u_phy);
पूर्ण

अटल व्योम set_pts(काष्ठा tegra_usb_phy *phy, u8 pts_val)
अणु
	व्योम __iomem *base = phy->regs;
	u32 val;

	अगर (phy->soc_config->has_hostpc) अणु
		val = पढ़ोl_relaxed(base + TEGRA_USB_HOSTPC1_DEVLC);
		val &= ~TEGRA_USB_HOSTPC1_DEVLC_PTS(~0);
		val |= TEGRA_USB_HOSTPC1_DEVLC_PTS(pts_val);
		ग_लिखोl_relaxed(val, base + TEGRA_USB_HOSTPC1_DEVLC);
	पूर्ण अन्यथा अणु
		val = पढ़ोl_relaxed(base + TEGRA_USB_PORTSC1);
		val &= ~TEGRA_PORTSC1_RWC_BITS;
		val &= ~TEGRA_USB_PORTSC1_PTS(~0);
		val |= TEGRA_USB_PORTSC1_PTS(pts_val);
		ग_लिखोl_relaxed(val, base + TEGRA_USB_PORTSC1);
	पूर्ण
पूर्ण

अटल व्योम set_phcd(काष्ठा tegra_usb_phy *phy, bool enable)
अणु
	व्योम __iomem *base = phy->regs;
	u32 val;

	अगर (phy->soc_config->has_hostpc) अणु
		val = पढ़ोl_relaxed(base + TEGRA_USB_HOSTPC1_DEVLC);
		अगर (enable)
			val |= TEGRA_USB_HOSTPC1_DEVLC_PHCD;
		अन्यथा
			val &= ~TEGRA_USB_HOSTPC1_DEVLC_PHCD;
		ग_लिखोl_relaxed(val, base + TEGRA_USB_HOSTPC1_DEVLC);
	पूर्ण अन्यथा अणु
		val = पढ़ोl_relaxed(base + TEGRA_USB_PORTSC1) & ~PORT_RWC_BITS;
		अगर (enable)
			val |= TEGRA_USB_PORTSC1_PHCD;
		अन्यथा
			val &= ~TEGRA_USB_PORTSC1_PHCD;
		ग_लिखोl_relaxed(val, base + TEGRA_USB_PORTSC1);
	पूर्ण
पूर्ण

अटल पूर्णांक uपंचांगip_pad_खोलो(काष्ठा tegra_usb_phy *phy)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(phy->pad_clk);
	अगर (ret) अणु
		dev_err(phy->u_phy.dev,
			"Failed to enable UTMI-pads clock: %d\n", ret);
		वापस ret;
	पूर्ण

	spin_lock(&uपंचांगip_pad_lock);

	ret = reset_control_deनिश्चित(phy->pad_rst);
	अगर (ret) अणु
		dev_err(phy->u_phy.dev,
			"Failed to initialize UTMI-pads reset: %d\n", ret);
		जाओ unlock;
	पूर्ण

	ret = reset_control_निश्चित(phy->pad_rst);
	अगर (ret) अणु
		dev_err(phy->u_phy.dev,
			"Failed to assert UTMI-pads reset: %d\n", ret);
		जाओ unlock;
	पूर्ण

	udelay(1);

	ret = reset_control_deनिश्चित(phy->pad_rst);
	अगर (ret)
		dev_err(phy->u_phy.dev,
			"Failed to deassert UTMI-pads reset: %d\n", ret);
unlock:
	spin_unlock(&uपंचांगip_pad_lock);

	clk_disable_unprepare(phy->pad_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक uपंचांगip_pad_बंद(काष्ठा tegra_usb_phy *phy)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(phy->pad_clk);
	अगर (ret) अणु
		dev_err(phy->u_phy.dev,
			"Failed to enable UTMI-pads clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = reset_control_निश्चित(phy->pad_rst);
	अगर (ret)
		dev_err(phy->u_phy.dev,
			"Failed to assert UTMI-pads reset: %d\n", ret);

	udelay(1);

	clk_disable_unprepare(phy->pad_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक uपंचांगip_pad_घातer_on(काष्ठा tegra_usb_phy *phy)
अणु
	काष्ठा tegra_uपंचांगip_config *config = phy->config;
	व्योम __iomem *base = phy->pad_regs;
	u32 val;
	पूर्णांक err;

	err = clk_prepare_enable(phy->pad_clk);
	अगर (err)
		वापस err;

	spin_lock(&uपंचांगip_pad_lock);

	अगर (uपंचांगip_pad_count++ == 0) अणु
		val = पढ़ोl_relaxed(base + UTMIP_BIAS_CFG0);
		val &= ~(UTMIP_OTGPD | UTMIP_BIASPD);

		अगर (phy->soc_config->requires_extra_tuning_parameters) अणु
			val &= ~(UTMIP_HSSQUELCH_LEVEL(~0) |
				UTMIP_HSDISCON_LEVEL(~0) |
				UTMIP_HSDISCON_LEVEL_MSB(~0));

			val |= UTMIP_HSSQUELCH_LEVEL(config->hssquelch_level);
			val |= UTMIP_HSDISCON_LEVEL(config->hsdiscon_level);
			val |= UTMIP_HSDISCON_LEVEL_MSB(config->hsdiscon_level);
		पूर्ण
		ग_लिखोl_relaxed(val, base + UTMIP_BIAS_CFG0);
	पूर्ण

	अगर (phy->pad_wakeup) अणु
		phy->pad_wakeup = false;
		uपंचांगip_pad_count--;
	पूर्ण

	spin_unlock(&uपंचांगip_pad_lock);

	clk_disable_unprepare(phy->pad_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक uपंचांगip_pad_घातer_off(काष्ठा tegra_usb_phy *phy)
अणु
	व्योम __iomem *base = phy->pad_regs;
	u32 val;
	पूर्णांक ret;

	ret = clk_prepare_enable(phy->pad_clk);
	अगर (ret)
		वापस ret;

	spin_lock(&uपंचांगip_pad_lock);

	अगर (!uपंचांगip_pad_count) अणु
		dev_err(phy->u_phy.dev, "UTMIP pad already powered off\n");
		ret = -EINVAL;
		जाओ ulock;
	पूर्ण

	/*
	 * In accordance to TRM, OTG and Bias pad circuits could be turned off
	 * to save घातer अगर wake is enabled, but the VBUS-change detection
	 * method is board-specअगरic and these circuits may need to be enabled
	 * to generate wakeup event, hence we will just keep them both enabled.
	 */
	अगर (phy->wakeup_enabled) अणु
		phy->pad_wakeup = true;
		uपंचांगip_pad_count++;
	पूर्ण

	अगर (--uपंचांगip_pad_count == 0) अणु
		val = पढ़ोl_relaxed(base + UTMIP_BIAS_CFG0);
		val |= UTMIP_OTGPD | UTMIP_BIASPD;
		ग_लिखोl_relaxed(val, base + UTMIP_BIAS_CFG0);
	पूर्ण
ulock:
	spin_unlock(&uपंचांगip_pad_lock);

	clk_disable_unprepare(phy->pad_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक uपंचांगi_रुको_रेजिस्टर(व्योम __iomem *reg, u32 mask, u32 result)
अणु
	u32 पंचांगp;

	वापस पढ़ोl_relaxed_poll_समयout(reg, पंचांगp, (पंचांगp & mask) == result,
					  2000, 6000);
पूर्ण

अटल व्योम uपंचांगi_phy_clk_disable(काष्ठा tegra_usb_phy *phy)
अणु
	व्योम __iomem *base = phy->regs;
	u32 val;

	/*
	 * The USB driver may have alपढ़ोy initiated the phy घड़ी
	 * disable so रुको to see अगर the घड़ी turns off and अगर not
	 * then proceed with gating the घड़ी.
	 */
	अगर (uपंचांगi_रुको_रेजिस्टर(base + USB_SUSP_CTRL, USB_PHY_CLK_VALID, 0) == 0)
		वापस;

	अगर (phy->is_legacy_phy) अणु
		val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
		val |= USB_SUSP_SET;
		ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);

		usleep_range(10, 100);

		val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
		val &= ~USB_SUSP_SET;
		ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);
	पूर्ण अन्यथा अणु
		set_phcd(phy, true);
	पूर्ण

	अगर (uपंचांगi_रुको_रेजिस्टर(base + USB_SUSP_CTRL, USB_PHY_CLK_VALID, 0))
		dev_err(phy->u_phy.dev,
			"Timeout waiting for PHY to stabilize on disable\n");
पूर्ण

अटल व्योम uपंचांगi_phy_clk_enable(काष्ठा tegra_usb_phy *phy)
अणु
	व्योम __iomem *base = phy->regs;
	u32 val;

	/*
	 * The USB driver may have alपढ़ोy initiated the phy घड़ी
	 * enable so रुको to see अगर the घड़ी turns on and अगर not
	 * then proceed with ungating the घड़ी.
	 */
	अगर (uपंचांगi_रुको_रेजिस्टर(base + USB_SUSP_CTRL, USB_PHY_CLK_VALID,
			       USB_PHY_CLK_VALID) == 0)
		वापस;

	अगर (phy->is_legacy_phy) अणु
		val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
		val |= USB_SUSP_CLR;
		ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);

		usleep_range(10, 100);

		val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
		val &= ~USB_SUSP_CLR;
		ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);
	पूर्ण अन्यथा अणु
		set_phcd(phy, false);
	पूर्ण

	अगर (uपंचांगi_रुको_रेजिस्टर(base + USB_SUSP_CTRL, USB_PHY_CLK_VALID,
			       USB_PHY_CLK_VALID))
		dev_err(phy->u_phy.dev,
			"Timeout waiting for PHY to stabilize on enable\n");
पूर्ण

अटल पूर्णांक uपंचांगi_phy_घातer_on(काष्ठा tegra_usb_phy *phy)
अणु
	काष्ठा tegra_uपंचांगip_config *config = phy->config;
	व्योम __iomem *base = phy->regs;
	u32 val;
	पूर्णांक err;

	val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
	val |= UTMIP_RESET;
	ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);

	अगर (phy->is_legacy_phy) अणु
		val = पढ़ोl_relaxed(base + USB1_LEGACY_CTRL);
		val |= USB1_NO_LEGACY_MODE;
		ग_लिखोl_relaxed(val, base + USB1_LEGACY_CTRL);
	पूर्ण

	val = पढ़ोl_relaxed(base + UTMIP_TX_CFG0);
	val |= UTMIP_FS_PREABMLE_J;
	ग_लिखोl_relaxed(val, base + UTMIP_TX_CFG0);

	val = पढ़ोl_relaxed(base + UTMIP_HSRX_CFG0);
	val &= ~(UTMIP_IDLE_WAIT(~0) | UTMIP_ELASTIC_LIMIT(~0));
	val |= UTMIP_IDLE_WAIT(config->idle_रुको_delay);
	val |= UTMIP_ELASTIC_LIMIT(config->elastic_limit);
	ग_लिखोl_relaxed(val, base + UTMIP_HSRX_CFG0);

	val = पढ़ोl_relaxed(base + UTMIP_HSRX_CFG1);
	val &= ~UTMIP_HS_SYNC_START_DLY(~0);
	val |= UTMIP_HS_SYNC_START_DLY(config->hssync_start_delay);
	ग_लिखोl_relaxed(val, base + UTMIP_HSRX_CFG1);

	val = पढ़ोl_relaxed(base + UTMIP_DEBOUNCE_CFG0);
	val &= ~UTMIP_BIAS_DEBOUNCE_A(~0);
	val |= UTMIP_BIAS_DEBOUNCE_A(phy->freq->debounce);
	ग_लिखोl_relaxed(val, base + UTMIP_DEBOUNCE_CFG0);

	val = पढ़ोl_relaxed(base + UTMIP_MISC_CFG0);
	val &= ~UTMIP_SUSPEND_EXIT_ON_EDGE;
	ग_लिखोl_relaxed(val, base + UTMIP_MISC_CFG0);

	अगर (!phy->soc_config->uपंचांगi_pll_config_in_car_module) अणु
		val = पढ़ोl_relaxed(base + UTMIP_MISC_CFG1);
		val &= ~(UTMIP_PLL_ACTIVE_DLY_COUNT(~0) |
			UTMIP_PLLU_STABLE_COUNT(~0));
		val |= UTMIP_PLL_ACTIVE_DLY_COUNT(phy->freq->active_delay) |
			UTMIP_PLLU_STABLE_COUNT(phy->freq->stable_count);
		ग_लिखोl_relaxed(val, base + UTMIP_MISC_CFG1);

		val = पढ़ोl_relaxed(base + UTMIP_PLL_CFG1);
		val &= ~(UTMIP_XTAL_FREQ_COUNT(~0) |
			UTMIP_PLLU_ENABLE_DLY_COUNT(~0));
		val |= UTMIP_XTAL_FREQ_COUNT(phy->freq->xtal_freq_count) |
			UTMIP_PLLU_ENABLE_DLY_COUNT(phy->freq->enable_delay);
		ग_लिखोl_relaxed(val, base + UTMIP_PLL_CFG1);
	पूर्ण

	val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
	val &= ~USB_WAKE_ON_RESUME_EN;
	ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);

	अगर (phy->mode == USB_DR_MODE_PERIPHERAL) अणु
		val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
		val &= ~(USB_WAKE_ON_CNNT_EN_DEV | USB_WAKE_ON_DISCON_EN_DEV);
		ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);

		val = पढ़ोl_relaxed(base + USB_PHY_VBUS_WAKEUP_ID);
		val &= ~VBUS_WAKEUP_WAKEUP_EN;
		ग_लिखोl_relaxed(val, base + USB_PHY_VBUS_WAKEUP_ID);

		val = पढ़ोl_relaxed(base + USB_PHY_VBUS_SENSORS);
		val &= ~(A_VBUS_VLD_WAKEUP_EN | A_SESS_VLD_WAKEUP_EN);
		val &= ~(B_VBUS_VLD_WAKEUP_EN | B_SESS_VLD_WAKEUP_EN);
		ग_लिखोl_relaxed(val, base + USB_PHY_VBUS_SENSORS);

		val = पढ़ोl_relaxed(base + UTMIP_BAT_CHRG_CFG0);
		val &= ~UTMIP_PD_CHRG;
		ग_लिखोl_relaxed(val, base + UTMIP_BAT_CHRG_CFG0);
	पूर्ण अन्यथा अणु
		val = पढ़ोl_relaxed(base + UTMIP_BAT_CHRG_CFG0);
		val |= UTMIP_PD_CHRG;
		ग_लिखोl_relaxed(val, base + UTMIP_BAT_CHRG_CFG0);
	पूर्ण

	err = uपंचांगip_pad_घातer_on(phy);
	अगर (err)
		वापस err;

	val = पढ़ोl_relaxed(base + UTMIP_XCVR_CFG0);
	val &= ~(UTMIP_FORCE_PD_POWERDOWN | UTMIP_FORCE_PD2_POWERDOWN |
		 UTMIP_FORCE_PDZI_POWERDOWN | UTMIP_XCVR_LSBIAS_SEL |
		 UTMIP_XCVR_SETUP(~0) | UTMIP_XCVR_SETUP_MSB(~0) |
		 UTMIP_XCVR_LSFSLEW(~0) | UTMIP_XCVR_LSRSLEW(~0));

	अगर (!config->xcvr_setup_use_fuses) अणु
		val |= UTMIP_XCVR_SETUP(config->xcvr_setup);
		val |= UTMIP_XCVR_SETUP_MSB(config->xcvr_setup);
	पूर्ण
	val |= UTMIP_XCVR_LSFSLEW(config->xcvr_lsfslew);
	val |= UTMIP_XCVR_LSRSLEW(config->xcvr_lsrslew);

	अगर (phy->soc_config->requires_extra_tuning_parameters) अणु
		val &= ~(UTMIP_XCVR_HSSLEW(~0) | UTMIP_XCVR_HSSLEW_MSB(~0));
		val |= UTMIP_XCVR_HSSLEW(config->xcvr_hsslew);
		val |= UTMIP_XCVR_HSSLEW_MSB(config->xcvr_hsslew);
	पूर्ण
	ग_लिखोl_relaxed(val, base + UTMIP_XCVR_CFG0);

	val = पढ़ोl_relaxed(base + UTMIP_XCVR_CFG1);
	val &= ~(UTMIP_FORCE_PDDISC_POWERDOWN | UTMIP_FORCE_PDCHRP_POWERDOWN |
		 UTMIP_FORCE_PDDR_POWERDOWN | UTMIP_XCVR_TERM_RANGE_ADJ(~0));
	val |= UTMIP_XCVR_TERM_RANGE_ADJ(config->term_range_adj);
	ग_लिखोl_relaxed(val, base + UTMIP_XCVR_CFG1);

	val = पढ़ोl_relaxed(base + UTMIP_BIAS_CFG1);
	val &= ~UTMIP_BIAS_PDTRK_COUNT(~0);
	val |= UTMIP_BIAS_PDTRK_COUNT(0x5);
	ग_लिखोl_relaxed(val, base + UTMIP_BIAS_CFG1);

	val = पढ़ोl_relaxed(base + UTMIP_SPARE_CFG0);
	अगर (config->xcvr_setup_use_fuses)
		val |= FUSE_SETUP_SEL;
	अन्यथा
		val &= ~FUSE_SETUP_SEL;
	ग_लिखोl_relaxed(val, base + UTMIP_SPARE_CFG0);

	अगर (!phy->is_legacy_phy) अणु
		val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
		val |= UTMIP_PHY_ENABLE;
		ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);
	पूर्ण

	val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
	val &= ~UTMIP_RESET;
	ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);

	अगर (phy->is_legacy_phy) अणु
		val = पढ़ोl_relaxed(base + USB1_LEGACY_CTRL);
		val &= ~USB1_VBUS_SENSE_CTL_MASK;
		val |= USB1_VBUS_SENSE_CTL_A_SESS_VLD;
		ग_लिखोl_relaxed(val, base + USB1_LEGACY_CTRL);

		val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
		val &= ~USB_SUSP_SET;
		ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);
	पूर्ण

	uपंचांगi_phy_clk_enable(phy);

	अगर (phy->soc_config->requires_usbmode_setup) अणु
		val = पढ़ोl_relaxed(base + USB_USBMODE);
		val &= ~USB_USBMODE_MASK;
		अगर (phy->mode == USB_DR_MODE_HOST)
			val |= USB_USBMODE_HOST;
		अन्यथा
			val |= USB_USBMODE_DEVICE;
		ग_लिखोl_relaxed(val, base + USB_USBMODE);
	पूर्ण

	अगर (!phy->is_legacy_phy)
		set_pts(phy, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक uपंचांगi_phy_घातer_off(काष्ठा tegra_usb_phy *phy)
अणु
	व्योम __iomem *base = phy->regs;
	u32 val;

	uपंचांगi_phy_clk_disable(phy);

	/* PHY won't resume अगर reset is निश्चितed */
	अगर (!phy->wakeup_enabled) अणु
		val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
		val |= UTMIP_RESET;
		ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);
	पूर्ण

	val = पढ़ोl_relaxed(base + UTMIP_BAT_CHRG_CFG0);
	val |= UTMIP_PD_CHRG;
	ग_लिखोl_relaxed(val, base + UTMIP_BAT_CHRG_CFG0);

	अगर (!phy->wakeup_enabled) अणु
		val = पढ़ोl_relaxed(base + UTMIP_XCVR_CFG0);
		val |= UTMIP_FORCE_PD_POWERDOWN | UTMIP_FORCE_PD2_POWERDOWN |
		       UTMIP_FORCE_PDZI_POWERDOWN;
		ग_लिखोl_relaxed(val, base + UTMIP_XCVR_CFG0);
	पूर्ण

	val = पढ़ोl_relaxed(base + UTMIP_XCVR_CFG1);
	val |= UTMIP_FORCE_PDDISC_POWERDOWN | UTMIP_FORCE_PDCHRP_POWERDOWN |
	       UTMIP_FORCE_PDDR_POWERDOWN;
	ग_लिखोl_relaxed(val, base + UTMIP_XCVR_CFG1);

	अगर (phy->wakeup_enabled) अणु
		val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
		val &= ~USB_WAKEUP_DEBOUNCE_COUNT(~0);
		val |= USB_WAKEUP_DEBOUNCE_COUNT(5);
		val |= USB_WAKE_ON_RESUME_EN;
		ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);

		/*
		 * Ask VBUS sensor to generate wake event once cable is
		 * connected.
		 */
		अगर (phy->mode == USB_DR_MODE_PERIPHERAL) अणु
			val = पढ़ोl_relaxed(base + USB_PHY_VBUS_WAKEUP_ID);
			val |= VBUS_WAKEUP_WAKEUP_EN;
			ग_लिखोl_relaxed(val, base + USB_PHY_VBUS_WAKEUP_ID);

			val = पढ़ोl_relaxed(base + USB_PHY_VBUS_SENSORS);
			val |= A_VBUS_VLD_WAKEUP_EN;
			ग_लिखोl_relaxed(val, base + USB_PHY_VBUS_SENSORS);
		पूर्ण
	पूर्ण

	वापस uपंचांगip_pad_घातer_off(phy);
पूर्ण

अटल व्योम uपंचांगi_phy_preresume(काष्ठा tegra_usb_phy *phy)
अणु
	व्योम __iomem *base = phy->regs;
	u32 val;

	val = पढ़ोl_relaxed(base + UTMIP_TX_CFG0);
	val |= UTMIP_HS_DISCON_DISABLE;
	ग_लिखोl_relaxed(val, base + UTMIP_TX_CFG0);
पूर्ण

अटल व्योम uपंचांगi_phy_postresume(काष्ठा tegra_usb_phy *phy)
अणु
	व्योम __iomem *base = phy->regs;
	u32 val;

	val = पढ़ोl_relaxed(base + UTMIP_TX_CFG0);
	val &= ~UTMIP_HS_DISCON_DISABLE;
	ग_लिखोl_relaxed(val, base + UTMIP_TX_CFG0);
पूर्ण

अटल व्योम uपंचांगi_phy_restore_start(काष्ठा tegra_usb_phy *phy,
				   क्रमागत tegra_usb_phy_port_speed port_speed)
अणु
	व्योम __iomem *base = phy->regs;
	u32 val;

	val = पढ़ोl_relaxed(base + UTMIP_MISC_CFG0);
	val &= ~UTMIP_DPDM_OBSERVE_SEL(~0);
	अगर (port_speed == TEGRA_USB_PHY_PORT_SPEED_LOW)
		val |= UTMIP_DPDM_OBSERVE_SEL_FS_K;
	अन्यथा
		val |= UTMIP_DPDM_OBSERVE_SEL_FS_J;
	ग_लिखोl_relaxed(val, base + UTMIP_MISC_CFG0);
	usleep_range(1, 10);

	val = पढ़ोl_relaxed(base + UTMIP_MISC_CFG0);
	val |= UTMIP_DPDM_OBSERVE;
	ग_लिखोl_relaxed(val, base + UTMIP_MISC_CFG0);
	usleep_range(10, 100);
पूर्ण

अटल व्योम uपंचांगi_phy_restore_end(काष्ठा tegra_usb_phy *phy)
अणु
	व्योम __iomem *base = phy->regs;
	u32 val;

	val = पढ़ोl_relaxed(base + UTMIP_MISC_CFG0);
	val &= ~UTMIP_DPDM_OBSERVE;
	ग_लिखोl_relaxed(val, base + UTMIP_MISC_CFG0);
	usleep_range(10, 100);
पूर्ण

अटल पूर्णांक ulpi_phy_घातer_on(काष्ठा tegra_usb_phy *phy)
अणु
	व्योम __iomem *base = phy->regs;
	u32 val;
	पूर्णांक err;

	gpiod_set_value_cansleep(phy->reset_gpio, 1);

	err = clk_prepare_enable(phy->clk);
	अगर (err)
		वापस err;

	usleep_range(5000, 6000);

	gpiod_set_value_cansleep(phy->reset_gpio, 0);

	usleep_range(1000, 2000);

	val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
	val |= UHSIC_RESET;
	ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);

	val = पढ़ोl_relaxed(base + ULPI_TIMING_CTRL_0);
	val |= ULPI_OUTPUT_PINMUX_BYP | ULPI_CLKOUT_PINMUX_BYP;
	ग_लिखोl_relaxed(val, base + ULPI_TIMING_CTRL_0);

	val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
	val |= ULPI_PHY_ENABLE;
	ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);

	val = 0;
	ग_लिखोl_relaxed(val, base + ULPI_TIMING_CTRL_1);

	val |= ULPI_DATA_TRIMMER_SEL(4);
	val |= ULPI_STPसूचीNXT_TRIMMER_SEL(4);
	val |= ULPI_सूची_TRIMMER_SEL(4);
	ग_लिखोl_relaxed(val, base + ULPI_TIMING_CTRL_1);
	usleep_range(10, 100);

	val |= ULPI_DATA_TRIMMER_LOAD;
	val |= ULPI_STPसूचीNXT_TRIMMER_LOAD;
	val |= ULPI_सूची_TRIMMER_LOAD;
	ग_लिखोl_relaxed(val, base + ULPI_TIMING_CTRL_1);

	/* Fix VbusInvalid due to भग्नing VBUS */
	err = usb_phy_io_ग_लिखो(phy->ulpi, 0x40, 0x08);
	अगर (err) अणु
		dev_err(phy->u_phy.dev, "ULPI write failed: %d\n", err);
		जाओ disable_clk;
	पूर्ण

	err = usb_phy_io_ग_लिखो(phy->ulpi, 0x80, 0x0B);
	अगर (err) अणु
		dev_err(phy->u_phy.dev, "ULPI write failed: %d\n", err);
		जाओ disable_clk;
	पूर्ण

	val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
	val |= USB_SUSP_CLR;
	ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);
	usleep_range(100, 1000);

	val = पढ़ोl_relaxed(base + USB_SUSP_CTRL);
	val &= ~USB_SUSP_CLR;
	ग_लिखोl_relaxed(val, base + USB_SUSP_CTRL);

	वापस 0;

disable_clk:
	clk_disable_unprepare(phy->clk);

	वापस err;
पूर्ण

अटल पूर्णांक ulpi_phy_घातer_off(काष्ठा tegra_usb_phy *phy)
अणु
	gpiod_set_value_cansleep(phy->reset_gpio, 1);
	usleep_range(5000, 6000);
	clk_disable_unprepare(phy->clk);

	/*
	 * Wakeup currently unimplemented क्रम ULPI, thus PHY needs to be
	 * क्रमce-resumed.
	 */
	अगर (WARN_ON_ONCE(phy->wakeup_enabled)) अणु
		ulpi_phy_घातer_on(phy);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_usb_phy_घातer_on(काष्ठा tegra_usb_phy *phy)
अणु
	पूर्णांक err;

	अगर (phy->घातered_on)
		वापस 0;

	अगर (phy->is_ulpi_phy)
		err = ulpi_phy_घातer_on(phy);
	अन्यथा
		err = uपंचांगi_phy_घातer_on(phy);
	अगर (err)
		वापस err;

	phy->घातered_on = true;

	/* Let PHY settle करोwn */
	usleep_range(2000, 2500);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_usb_phy_घातer_off(काष्ठा tegra_usb_phy *phy)
अणु
	पूर्णांक err;

	अगर (!phy->घातered_on)
		वापस 0;

	अगर (phy->is_ulpi_phy)
		err = ulpi_phy_घातer_off(phy);
	अन्यथा
		err = uपंचांगi_phy_घातer_off(phy);
	अगर (err)
		वापस err;

	phy->घातered_on = false;

	वापस 0;
पूर्ण

अटल व्योम tegra_usb_phy_shutकरोwn(काष्ठा usb_phy *u_phy)
अणु
	काष्ठा tegra_usb_phy *phy = to_tegra_usb_phy(u_phy);

	अगर (WARN_ON(!phy->freq))
		वापस;

	tegra_usb_phy_घातer_off(phy);

	अगर (!phy->is_ulpi_phy)
		uपंचांगip_pad_बंद(phy);

	regulator_disable(phy->vbus);
	clk_disable_unprepare(phy->pll_u);

	phy->freq = शून्य;
पूर्ण

अटल पूर्णांक tegra_usb_phy_set_wakeup(काष्ठा usb_phy *u_phy, bool enable)
अणु
	काष्ठा tegra_usb_phy *phy = to_tegra_usb_phy(u_phy);

	phy->wakeup_enabled = enable;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_usb_phy_set_suspend(काष्ठा usb_phy *u_phy, पूर्णांक suspend)
अणु
	काष्ठा tegra_usb_phy *phy = to_tegra_usb_phy(u_phy);

	अगर (WARN_ON(!phy->freq))
		वापस -EINVAL;

	अगर (suspend)
		वापस tegra_usb_phy_घातer_off(phy);
	अन्यथा
		वापस tegra_usb_phy_घातer_on(phy);
पूर्ण

अटल पूर्णांक tegra_usb_phy_init(काष्ठा usb_phy *u_phy)
अणु
	काष्ठा tegra_usb_phy *phy = to_tegra_usb_phy(u_phy);
	अचिन्हित दीर्घ parent_rate;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (WARN_ON(phy->freq))
		वापस 0;

	err = clk_prepare_enable(phy->pll_u);
	अगर (err)
		वापस err;

	parent_rate = clk_get_rate(clk_get_parent(phy->pll_u));
	क्रम (i = 0; i < ARRAY_SIZE(tegra_freq_table); i++) अणु
		अगर (tegra_freq_table[i].freq == parent_rate) अणु
			phy->freq = &tegra_freq_table[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!phy->freq) अणु
		dev_err(phy->u_phy.dev, "Invalid pll_u parent rate %ld\n",
			parent_rate);
		err = -EINVAL;
		जाओ disable_clk;
	पूर्ण

	err = regulator_enable(phy->vbus);
	अगर (err) अणु
		dev_err(phy->u_phy.dev,
			"Failed to enable USB VBUS regulator: %d\n", err);
		जाओ disable_clk;
	पूर्ण

	अगर (!phy->is_ulpi_phy) अणु
		err = uपंचांगip_pad_खोलो(phy);
		अगर (err)
			जाओ disable_vbus;
	पूर्ण

	err = tegra_usb_phy_घातer_on(phy);
	अगर (err)
		जाओ बंद_phy;

	वापस 0;

बंद_phy:
	अगर (!phy->is_ulpi_phy)
		uपंचांगip_pad_बंद(phy);

disable_vbus:
	regulator_disable(phy->vbus);

disable_clk:
	clk_disable_unprepare(phy->pll_u);

	phy->freq = शून्य;

	वापस err;
पूर्ण

व्योम tegra_usb_phy_preresume(काष्ठा usb_phy *u_phy)
अणु
	काष्ठा tegra_usb_phy *phy = to_tegra_usb_phy(u_phy);

	अगर (!phy->is_ulpi_phy)
		uपंचांगi_phy_preresume(phy);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_usb_phy_preresume);

व्योम tegra_usb_phy_postresume(काष्ठा usb_phy *u_phy)
अणु
	काष्ठा tegra_usb_phy *phy = to_tegra_usb_phy(u_phy);

	अगर (!phy->is_ulpi_phy)
		uपंचांगi_phy_postresume(phy);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_usb_phy_postresume);

व्योम tegra_ehci_phy_restore_start(काष्ठा usb_phy *u_phy,
				  क्रमागत tegra_usb_phy_port_speed port_speed)
अणु
	काष्ठा tegra_usb_phy *phy = to_tegra_usb_phy(u_phy);

	अगर (!phy->is_ulpi_phy)
		uपंचांगi_phy_restore_start(phy, port_speed);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_ehci_phy_restore_start);

व्योम tegra_ehci_phy_restore_end(काष्ठा usb_phy *u_phy)
अणु
	काष्ठा tegra_usb_phy *phy = to_tegra_usb_phy(u_phy);

	अगर (!phy->is_ulpi_phy)
		uपंचांगi_phy_restore_end(phy);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_ehci_phy_restore_end);

अटल पूर्णांक पढ़ो_uपंचांगi_param(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *param,
			   u8 *dest)
अणु
	u32 value;
	पूर्णांक err;

	err = of_property_पढ़ो_u32(pdev->dev.of_node, param, &value);
	अगर (err)
		dev_err(&pdev->dev,
			"Failed to read USB UTMI parameter %s: %d\n",
			param, err);
	अन्यथा
		*dest = value;

	वापस err;
पूर्ण

अटल पूर्णांक uपंचांगi_phy_probe(काष्ठा tegra_usb_phy *tegra_phy,
			  काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_uपंचांगip_config *config;
	काष्ठा resource *res;
	पूर्णांक err;

	tegra_phy->is_ulpi_phy = false;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Failed to get UTMI pad regs\n");
		वापस  -ENXIO;
	पूर्ण

	/*
	 * Note that UTMI pad रेजिस्टरs are shared by all PHYs, thereक्रमe
	 * devm_platक्रमm_ioremap_resource() can't be used here.
	 */
	tegra_phy->pad_regs = devm_ioremap(&pdev->dev, res->start,
					   resource_size(res));
	अगर (!tegra_phy->pad_regs) अणु
		dev_err(&pdev->dev, "Failed to remap UTMI pad regs\n");
		वापस -ENOMEM;
	पूर्ण

	tegra_phy->config = devm_kzalloc(&pdev->dev, माप(*config),
					 GFP_KERNEL);
	अगर (!tegra_phy->config)
		वापस -ENOMEM;

	config = tegra_phy->config;

	err = पढ़ो_uपंचांगi_param(pdev, "nvidia,hssync-start-delay",
			      &config->hssync_start_delay);
	अगर (err)
		वापस err;

	err = पढ़ो_uपंचांगi_param(pdev, "nvidia,elastic-limit",
			      &config->elastic_limit);
	अगर (err)
		वापस err;

	err = पढ़ो_uपंचांगi_param(pdev, "nvidia,idle-wait-delay",
			      &config->idle_रुको_delay);
	अगर (err)
		वापस err;

	err = पढ़ो_uपंचांगi_param(pdev, "nvidia,term-range-adj",
			      &config->term_range_adj);
	अगर (err)
		वापस err;

	err = पढ़ो_uपंचांगi_param(pdev, "nvidia,xcvr-lsfslew",
			      &config->xcvr_lsfslew);
	अगर (err)
		वापस err;

	err = पढ़ो_uपंचांगi_param(pdev, "nvidia,xcvr-lsrslew",
			      &config->xcvr_lsrslew);
	अगर (err)
		वापस err;

	अगर (tegra_phy->soc_config->requires_extra_tuning_parameters) अणु
		err = पढ़ो_uपंचांगi_param(pdev, "nvidia,xcvr-hsslew",
				      &config->xcvr_hsslew);
		अगर (err)
			वापस err;

		err = पढ़ो_uपंचांगi_param(pdev, "nvidia,hssquelch-level",
				      &config->hssquelch_level);
		अगर (err)
			वापस err;

		err = पढ़ो_uपंचांगi_param(pdev, "nvidia,hsdiscon-level",
				      &config->hsdiscon_level);
		अगर (err)
			वापस err;
	पूर्ण

	config->xcvr_setup_use_fuses = of_property_पढ़ो_bool(
		pdev->dev.of_node, "nvidia,xcvr-setup-use-fuses");

	अगर (!config->xcvr_setup_use_fuses) अणु
		err = पढ़ो_uपंचांगi_param(pdev, "nvidia,xcvr-setup",
				      &config->xcvr_setup);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tegra_phy_soc_config tegra20_soc_config = अणु
	.uपंचांगi_pll_config_in_car_module = false,
	.has_hostpc = false,
	.requires_usbmode_setup = false,
	.requires_extra_tuning_parameters = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_phy_soc_config tegra30_soc_config = अणु
	.uपंचांगi_pll_config_in_car_module = true,
	.has_hostpc = true,
	.requires_usbmode_setup = true,
	.requires_extra_tuning_parameters = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_usb_phy_id_table[] = अणु
	अणु .compatible = "nvidia,tegra30-usb-phy", .data = &tegra30_soc_config पूर्ण,
	अणु .compatible = "nvidia,tegra20-usb-phy", .data = &tegra20_soc_config पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_usb_phy_id_table);

अटल पूर्णांक tegra_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा tegra_usb_phy *tegra_phy;
	क्रमागत usb_phy_पूर्णांकerface phy_type;
	काष्ठा reset_control *reset;
	काष्ठा gpio_desc *gpiod;
	काष्ठा resource *res;
	काष्ठा usb_phy *phy;
	पूर्णांक err;

	tegra_phy = devm_kzalloc(&pdev->dev, माप(*tegra_phy), GFP_KERNEL);
	अगर (!tegra_phy)
		वापस -ENOMEM;

	tegra_phy->soc_config = of_device_get_match_data(&pdev->dev);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Failed to get I/O memory\n");
		वापस  -ENXIO;
	पूर्ण

	/*
	 * Note that PHY and USB controller are using shared रेजिस्टरs,
	 * thereक्रमe devm_platक्रमm_ioremap_resource() can't be used here.
	 */
	tegra_phy->regs = devm_ioremap(&pdev->dev, res->start,
				       resource_size(res));
	अगर (!tegra_phy->regs) अणु
		dev_err(&pdev->dev, "Failed to remap I/O memory\n");
		वापस -ENOMEM;
	पूर्ण

	tegra_phy->is_legacy_phy =
		of_property_पढ़ो_bool(np, "nvidia,has-legacy-mode");

	अगर (of_find_property(np, "dr_mode", शून्य))
		tegra_phy->mode = usb_get_dr_mode(&pdev->dev);
	अन्यथा
		tegra_phy->mode = USB_DR_MODE_HOST;

	अगर (tegra_phy->mode == USB_DR_MODE_UNKNOWN) अणु
		dev_err(&pdev->dev, "dr_mode is invalid\n");
		वापस -EINVAL;
	पूर्ण

	/* On some boards, the VBUS regulator करोesn't need to be controlled */
	tegra_phy->vbus = devm_regulator_get(&pdev->dev, "vbus");
	अगर (IS_ERR(tegra_phy->vbus))
		वापस PTR_ERR(tegra_phy->vbus);

	tegra_phy->pll_u = devm_clk_get(&pdev->dev, "pll_u");
	err = PTR_ERR_OR_ZERO(tegra_phy->pll_u);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to get pll_u clock: %d\n", err);
		वापस err;
	पूर्ण

	phy_type = of_usb_get_phy_mode(np);
	चयन (phy_type) अणु
	हाल USBPHY_INTERFACE_MODE_UTMI:
		err = uपंचांगi_phy_probe(tegra_phy, pdev);
		अगर (err)
			वापस err;

		tegra_phy->pad_clk = devm_clk_get(&pdev->dev, "utmi-pads");
		err = PTR_ERR_OR_ZERO(tegra_phy->pad_clk);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Failed to get UTMIP pad clock: %d\n", err);
			वापस err;
		पूर्ण

		reset = devm_reset_control_get_optional_shared(&pdev->dev,
							       "utmi-pads");
		err = PTR_ERR_OR_ZERO(reset);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Failed to get UTMI-pads reset: %d\n", err);
			वापस err;
		पूर्ण
		tegra_phy->pad_rst = reset;
		अवरोध;

	हाल USBPHY_INTERFACE_MODE_ULPI:
		tegra_phy->is_ulpi_phy = true;

		tegra_phy->clk = devm_clk_get(&pdev->dev, "ulpi-link");
		err = PTR_ERR_OR_ZERO(tegra_phy->clk);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Failed to get ULPI clock: %d\n", err);
			वापस err;
		पूर्ण

		gpiod = devm_gpiod_get_from_of_node(&pdev->dev, np,
						    "nvidia,phy-reset-gpio",
						    0, GPIOD_OUT_HIGH,
						    "ulpi_phy_reset_b");
		err = PTR_ERR_OR_ZERO(gpiod);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Request failed for reset GPIO: %d\n", err);
			वापस err;
		पूर्ण
		tegra_phy->reset_gpio = gpiod;

		phy = devm_otg_ulpi_create(&pdev->dev,
					   &ulpi_viewport_access_ops, 0);
		अगर (!phy) अणु
			dev_err(&pdev->dev, "Failed to create ULPI OTG\n");
			वापस -ENOMEM;
		पूर्ण

		tegra_phy->ulpi = phy;
		tegra_phy->ulpi->io_priv = tegra_phy->regs + ULPI_VIEWPORT;
		अवरोध;

	शेष:
		dev_err(&pdev->dev, "phy_type %u is invalid or unsupported\n",
			phy_type);
		वापस -EINVAL;
	पूर्ण

	tegra_phy->u_phy.dev = &pdev->dev;
	tegra_phy->u_phy.init = tegra_usb_phy_init;
	tegra_phy->u_phy.shutकरोwn = tegra_usb_phy_shutकरोwn;
	tegra_phy->u_phy.set_wakeup = tegra_usb_phy_set_wakeup;
	tegra_phy->u_phy.set_suspend = tegra_usb_phy_set_suspend;

	platक्रमm_set_drvdata(pdev, tegra_phy);

	वापस usb_add_phy_dev(&tegra_phy->u_phy);
पूर्ण

अटल पूर्णांक tegra_usb_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_usb_phy *tegra_phy = platक्रमm_get_drvdata(pdev);

	usb_हटाओ_phy(&tegra_phy->u_phy);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tegra_usb_phy_driver = अणु
	.probe		= tegra_usb_phy_probe,
	.हटाओ		= tegra_usb_phy_हटाओ,
	.driver		= अणु
		.name	= "tegra-phy",
		.of_match_table = tegra_usb_phy_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_usb_phy_driver);

MODULE_DESCRIPTION("Tegra USB PHY driver");
MODULE_LICENSE("GPL v2");
