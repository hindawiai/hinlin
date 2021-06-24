<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/usb/otg.h>

#समावेश "ci_hdrc_imx.h"

#घोषणा MX25_USB_PHY_CTRL_OFFSET	0x08
#घोषणा MX25_BM_EXTERNAL_VBUS_DIVIDER	BIT(23)

#घोषणा MX25_EHCI_INTERFACE_SINGLE_UNI	(2 << 0)
#घोषणा MX25_EHCI_INTERFACE_DIFF_UNI	(0 << 0)
#घोषणा MX25_EHCI_INTERFACE_MASK	(0xf)

#घोषणा MX25_OTG_SIC_SHIFT		29
#घोषणा MX25_OTG_SIC_MASK		(0x3 << MX25_OTG_SIC_SHIFT)
#घोषणा MX25_OTG_PM_BIT			BIT(24)
#घोषणा MX25_OTG_PP_BIT			BIT(11)
#घोषणा MX25_OTG_OCPOL_BIT		BIT(3)

#घोषणा MX25_H1_SIC_SHIFT		21
#घोषणा MX25_H1_SIC_MASK		(0x3 << MX25_H1_SIC_SHIFT)
#घोषणा MX25_H1_PP_BIT			BIT(18)
#घोषणा MX25_H1_PM_BIT			BIT(16)
#घोषणा MX25_H1_IPPUE_UP_BIT		BIT(7)
#घोषणा MX25_H1_IPPUE_DOWN_BIT		BIT(6)
#घोषणा MX25_H1_TLL_BIT			BIT(5)
#घोषणा MX25_H1_USBTE_BIT		BIT(4)
#घोषणा MX25_H1_OCPOL_BIT		BIT(2)

#घोषणा MX27_H1_PM_BIT			BIT(8)
#घोषणा MX27_H2_PM_BIT			BIT(16)
#घोषणा MX27_OTG_PM_BIT			BIT(24)

#घोषणा MX53_USB_OTG_PHY_CTRL_0_OFFSET	0x08
#घोषणा MX53_USB_OTG_PHY_CTRL_1_OFFSET	0x0c
#घोषणा MX53_USB_CTRL_1_OFFSET	        0x10
#घोषणा MX53_USB_CTRL_1_H2_XCVR_CLK_SEL_MASK (0x11 << 2)
#घोषणा MX53_USB_CTRL_1_H2_XCVR_CLK_SEL_ULPI BIT(2)
#घोषणा MX53_USB_CTRL_1_H3_XCVR_CLK_SEL_MASK (0x11 << 6)
#घोषणा MX53_USB_CTRL_1_H3_XCVR_CLK_SEL_ULPI BIT(6)
#घोषणा MX53_USB_UH2_CTRL_OFFSET	0x14
#घोषणा MX53_USB_UH3_CTRL_OFFSET	0x18
#घोषणा MX53_USB_CLKONOFF_CTRL_OFFSET	0x24
#घोषणा MX53_USB_CLKONOFF_CTRL_H2_INT60CKOFF BIT(21)
#घोषणा MX53_USB_CLKONOFF_CTRL_H3_INT60CKOFF BIT(22)
#घोषणा MX53_BM_OVER_CUR_DIS_H1		BIT(5)
#घोषणा MX53_BM_OVER_CUR_DIS_OTG	BIT(8)
#घोषणा MX53_BM_OVER_CUR_DIS_UHx	BIT(30)
#घोषणा MX53_USB_CTRL_1_UH2_ULPI_EN	BIT(26)
#घोषणा MX53_USB_CTRL_1_UH3_ULPI_EN	BIT(27)
#घोषणा MX53_USB_UHx_CTRL_WAKE_UP_EN	BIT(7)
#घोषणा MX53_USB_UHx_CTRL_ULPI_INT_EN	BIT(8)
#घोषणा MX53_USB_PHYCTRL1_PLLDIV_MASK	0x3
#घोषणा MX53_USB_PLL_DIV_24_MHZ		0x01

#घोषणा MX6_BM_NON_BURST_SETTING	BIT(1)
#घोषणा MX6_BM_OVER_CUR_DIS		BIT(7)
#घोषणा MX6_BM_OVER_CUR_POLARITY	BIT(8)
#घोषणा MX6_BM_PWR_POLARITY		BIT(9)
#घोषणा MX6_BM_WAKEUP_ENABLE		BIT(10)
#घोषणा MX6_BM_UTMI_ON_CLOCK		BIT(13)
#घोषणा MX6_BM_ID_WAKEUP		BIT(16)
#घोषणा MX6_BM_VBUS_WAKEUP		BIT(17)
#घोषणा MX6SX_BM_DPDM_WAKEUP_EN		BIT(29)
#घोषणा MX6_BM_WAKEUP_INTR		BIT(31)

#घोषणा MX6_USB_HSIC_CTRL_OFFSET	0x10
/* Send resume संकेत without 480Mhz PHY घड़ी */
#घोषणा MX6SX_BM_HSIC_AUTO_RESUME	BIT(23)
/* set beक्रमe portsc.suspendM = 1 */
#घोषणा MX6_BM_HSIC_DEV_CONN		BIT(21)
/* HSIC enable */
#घोषणा MX6_BM_HSIC_EN			BIT(12)
/* Force HSIC module 480M घड़ी on, even when in Host is in suspend mode */
#घोषणा MX6_BM_HSIC_CLK_ON		BIT(11)

#घोषणा MX6_USB_OTG1_PHY_CTRL		0x18
/* For imx6dql, it is host-only controller, क्रम later imx6, it is otg's */
#घोषणा MX6_USB_OTG2_PHY_CTRL		0x1c
#घोषणा MX6SX_USB_VBUS_WAKEUP_SOURCE(v)	(v << 8)
#घोषणा MX6SX_USB_VBUS_WAKEUP_SOURCE_VBUS	MX6SX_USB_VBUS_WAKEUP_SOURCE(0)
#घोषणा MX6SX_USB_VBUS_WAKEUP_SOURCE_AVALID	MX6SX_USB_VBUS_WAKEUP_SOURCE(1)
#घोषणा MX6SX_USB_VBUS_WAKEUP_SOURCE_BVALID	MX6SX_USB_VBUS_WAKEUP_SOURCE(2)
#घोषणा MX6SX_USB_VBUS_WAKEUP_SOURCE_SESS_END	MX6SX_USB_VBUS_WAKEUP_SOURCE(3)

#घोषणा VF610_OVER_CUR_DIS		BIT(7)

#घोषणा MX7D_USBNC_USB_CTRL2		0x4
#घोषणा MX7D_USB_VBUS_WAKEUP_SOURCE_MASK	0x3
#घोषणा MX7D_USB_VBUS_WAKEUP_SOURCE(v)		(v << 0)
#घोषणा MX7D_USB_VBUS_WAKEUP_SOURCE_VBUS	MX7D_USB_VBUS_WAKEUP_SOURCE(0)
#घोषणा MX7D_USB_VBUS_WAKEUP_SOURCE_AVALID	MX7D_USB_VBUS_WAKEUP_SOURCE(1)
#घोषणा MX7D_USB_VBUS_WAKEUP_SOURCE_BVALID	MX7D_USB_VBUS_WAKEUP_SOURCE(2)
#घोषणा MX7D_USB_VBUS_WAKEUP_SOURCE_SESS_END	MX7D_USB_VBUS_WAKEUP_SOURCE(3)
#घोषणा MX7D_USBNC_AUTO_RESUME				BIT(2)
/* The शेष DM/DP value is pull-करोwn */
#घोषणा MX7D_USBNC_USB_CTRL2_OPMODE(v)			(v << 6)
#घोषणा MX7D_USBNC_USB_CTRL2_OPMODE_NON_DRIVING	MX7D_USBNC_USB_CTRL2_OPMODE(1)
#घोषणा MX7D_USBNC_USB_CTRL2_OPMODE_OVERRIDE_MASK	(BIT(7) | BIT(6))
#घोषणा MX7D_USBNC_USB_CTRL2_OPMODE_OVERRIDE_EN		BIT(8)
#घोषणा MX7D_USBNC_USB_CTRL2_DP_OVERRIDE_VAL		BIT(12)
#घोषणा MX7D_USBNC_USB_CTRL2_DP_OVERRIDE_EN		BIT(13)
#घोषणा MX7D_USBNC_USB_CTRL2_DM_OVERRIDE_VAL		BIT(14)
#घोषणा MX7D_USBNC_USB_CTRL2_DM_OVERRIDE_EN		BIT(15)
#घोषणा MX7D_USBNC_USB_CTRL2_DP_DM_MASK			(BIT(12) | BIT(13) | \
							BIT(14) | BIT(15))

#घोषणा MX7D_USB_OTG_PHY_CFG1		0x30
#घोषणा MX7D_USB_OTG_PHY_CFG2_CHRG_CHRGSEL	BIT(0)
#घोषणा MX7D_USB_OTG_PHY_CFG2_CHRG_VDATDETENB0	BIT(1)
#घोषणा MX7D_USB_OTG_PHY_CFG2_CHRG_VDATSRCENB0	BIT(2)
#घोषणा MX7D_USB_OTG_PHY_CFG2_CHRG_DCDENB	BIT(3)
#घोषणा MX7D_USB_OTG_PHY_CFG2_DRVVBUS0		BIT(16)

#घोषणा MX7D_USB_OTG_PHY_CFG2		0x34

#घोषणा MX7D_USB_OTG_PHY_STATUS		0x3c
#घोषणा MX7D_USB_OTG_PHY_STATUS_LINE_STATE0	BIT(0)
#घोषणा MX7D_USB_OTG_PHY_STATUS_LINE_STATE1	BIT(1)
#घोषणा MX7D_USB_OTG_PHY_STATUS_VBUS_VLD	BIT(3)
#घोषणा MX7D_USB_OTG_PHY_STATUS_CHRGDET		BIT(29)

#घोषणा MX7D_USB_OTG_PHY_CFG1		0x30
#घोषणा TXPREEMPAMPTUNE0_BIT		28
#घोषणा TXPREEMPAMPTUNE0_MASK		(3 << 28)
#घोषणा TXVREFTUNE0_BIT			20
#घोषणा TXVREFTUNE0_MASK		(0xf << 20)

#घोषणा MX6_USB_OTG_WAKEUP_BITS (MX6_BM_WAKEUP_ENABLE | MX6_BM_VBUS_WAKEUP | \
				 MX6_BM_ID_WAKEUP)

काष्ठा usbmisc_ops अणु
	/* It's called once when probe a usb device */
	पूर्णांक (*init)(काष्ठा imx_usbmisc_data *data);
	/* It's called once after adding a usb device */
	पूर्णांक (*post)(काष्ठा imx_usbmisc_data *data);
	/* It's called when we need to enable/disable usb wakeup */
	पूर्णांक (*set_wakeup)(काष्ठा imx_usbmisc_data *data, bool enabled);
	/* It's called beक्रमe setting portsc.suspendM */
	पूर्णांक (*hsic_set_connect)(काष्ठा imx_usbmisc_data *data);
	/* It's called during suspend/resume */
	पूर्णांक (*hsic_set_clk)(काष्ठा imx_usbmisc_data *data, bool enabled);
	/* usb अक्षरger detection */
	पूर्णांक (*अक्षरger_detection)(काष्ठा imx_usbmisc_data *data);
पूर्ण;

काष्ठा imx_usbmisc अणु
	व्योम __iomem *base;
	spinlock_t lock;
	स्थिर काष्ठा usbmisc_ops *ops;
पूर्ण;

अटल अंतरभूत bool is_imx53_usbmisc(काष्ठा imx_usbmisc_data *data);

अटल पूर्णांक usbmisc_imx25_init(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	अचिन्हित दीर्घ flags;
	u32 val = 0;

	अगर (data->index > 1)
		वापस -EINVAL;

	spin_lock_irqsave(&usbmisc->lock, flags);
	चयन (data->index) अणु
	हाल 0:
		val = पढ़ोl(usbmisc->base);
		val &= ~(MX25_OTG_SIC_MASK | MX25_OTG_PP_BIT);
		val |= (MX25_EHCI_INTERFACE_DIFF_UNI & MX25_EHCI_INTERFACE_MASK) << MX25_OTG_SIC_SHIFT;
		val |= (MX25_OTG_PM_BIT | MX25_OTG_OCPOL_BIT);

		/*
		 * If the polarity is not configured assume active high क्रम
		 * historical reasons.
		 */
		अगर (data->oc_pol_configured && data->oc_pol_active_low)
			val &= ~MX25_OTG_OCPOL_BIT;

		ग_लिखोl(val, usbmisc->base);
		अवरोध;
	हाल 1:
		val = पढ़ोl(usbmisc->base);
		val &= ~(MX25_H1_SIC_MASK | MX25_H1_PP_BIT |  MX25_H1_IPPUE_UP_BIT);
		val |= (MX25_EHCI_INTERFACE_SINGLE_UNI & MX25_EHCI_INTERFACE_MASK) << MX25_H1_SIC_SHIFT;
		val |= (MX25_H1_PM_BIT | MX25_H1_OCPOL_BIT | MX25_H1_TLL_BIT |
			MX25_H1_USBTE_BIT | MX25_H1_IPPUE_DOWN_BIT);

		/*
		 * If the polarity is not configured assume active high क्रम
		 * historical reasons.
		 */
		अगर (data->oc_pol_configured && data->oc_pol_active_low)
			val &= ~MX25_H1_OCPOL_BIT;

		ग_लिखोl(val, usbmisc->base);

		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&usbmisc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक usbmisc_imx25_post(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	व्योम __iomem *reg;
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (data->index > 2)
		वापस -EINVAL;

	अगर (data->index)
		वापस 0;

	spin_lock_irqsave(&usbmisc->lock, flags);
	reg = usbmisc->base + MX25_USB_PHY_CTRL_OFFSET;
	val = पढ़ोl(reg);

	अगर (data->evकरो)
		val |= MX25_BM_EXTERNAL_VBUS_DIVIDER;
	अन्यथा
		val &= ~MX25_BM_EXTERNAL_VBUS_DIVIDER;

	ग_लिखोl(val, reg);
	spin_unlock_irqrestore(&usbmisc->lock, flags);
	usleep_range(5000, 10000); /* needed to stabilize voltage */

	वापस 0;
पूर्ण

अटल पूर्णांक usbmisc_imx27_init(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	अचिन्हित दीर्घ flags;
	u32 val;

	चयन (data->index) अणु
	हाल 0:
		val = MX27_OTG_PM_BIT;
		अवरोध;
	हाल 1:
		val = MX27_H1_PM_BIT;
		अवरोध;
	हाल 2:
		val = MX27_H2_PM_BIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&usbmisc->lock, flags);
	अगर (data->disable_oc)
		val = पढ़ोl(usbmisc->base) | val;
	अन्यथा
		val = पढ़ोl(usbmisc->base) & ~val;
	ग_लिखोl(val, usbmisc->base);
	spin_unlock_irqrestore(&usbmisc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक usbmisc_imx53_init(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	व्योम __iomem *reg = शून्य;
	अचिन्हित दीर्घ flags;
	u32 val = 0;

	अगर (data->index > 3)
		वापस -EINVAL;

	/* Select a 24 MHz reference घड़ी क्रम the PHY  */
	val = पढ़ोl(usbmisc->base + MX53_USB_OTG_PHY_CTRL_1_OFFSET);
	val &= ~MX53_USB_PHYCTRL1_PLLDIV_MASK;
	val |= MX53_USB_PLL_DIV_24_MHZ;
	ग_लिखोl(val, usbmisc->base + MX53_USB_OTG_PHY_CTRL_1_OFFSET);

	spin_lock_irqsave(&usbmisc->lock, flags);

	चयन (data->index) अणु
	हाल 0:
		अगर (data->disable_oc) अणु
			reg = usbmisc->base + MX53_USB_OTG_PHY_CTRL_0_OFFSET;
			val = पढ़ोl(reg) | MX53_BM_OVER_CUR_DIS_OTG;
			ग_लिखोl(val, reg);
		पूर्ण
		अवरोध;
	हाल 1:
		अगर (data->disable_oc) अणु
			reg = usbmisc->base + MX53_USB_OTG_PHY_CTRL_0_OFFSET;
			val = पढ़ोl(reg) | MX53_BM_OVER_CUR_DIS_H1;
			ग_लिखोl(val, reg);
		पूर्ण
		अवरोध;
	हाल 2:
		अगर (data->ulpi) अणु
			/* set USBH2 पूर्णांकo ULPI-mode. */
			reg = usbmisc->base + MX53_USB_CTRL_1_OFFSET;
			val = पढ़ोl(reg) | MX53_USB_CTRL_1_UH2_ULPI_EN;
			/* select ULPI घड़ी */
			val &= ~MX53_USB_CTRL_1_H2_XCVR_CLK_SEL_MASK;
			val |= MX53_USB_CTRL_1_H2_XCVR_CLK_SEL_ULPI;
			ग_लिखोl(val, reg);
			/* Set पूर्णांकerrupt wake up enable */
			reg = usbmisc->base + MX53_USB_UH2_CTRL_OFFSET;
			val = पढ़ोl(reg) | MX53_USB_UHx_CTRL_WAKE_UP_EN
				| MX53_USB_UHx_CTRL_ULPI_INT_EN;
			ग_लिखोl(val, reg);
			अगर (is_imx53_usbmisc(data)) अणु
				/* Disable पूर्णांकernal 60Mhz घड़ी */
				reg = usbmisc->base +
					MX53_USB_CLKONOFF_CTRL_OFFSET;
				val = पढ़ोl(reg) |
					MX53_USB_CLKONOFF_CTRL_H2_INT60CKOFF;
				ग_लिखोl(val, reg);
			पूर्ण

		पूर्ण
		अगर (data->disable_oc) अणु
			reg = usbmisc->base + MX53_USB_UH2_CTRL_OFFSET;
			val = पढ़ोl(reg) | MX53_BM_OVER_CUR_DIS_UHx;
			ग_लिखोl(val, reg);
		पूर्ण
		अवरोध;
	हाल 3:
		अगर (data->ulpi) अणु
			/* set USBH3 पूर्णांकo ULPI-mode. */
			reg = usbmisc->base + MX53_USB_CTRL_1_OFFSET;
			val = पढ़ोl(reg) | MX53_USB_CTRL_1_UH3_ULPI_EN;
			/* select ULPI घड़ी */
			val &= ~MX53_USB_CTRL_1_H3_XCVR_CLK_SEL_MASK;
			val |= MX53_USB_CTRL_1_H3_XCVR_CLK_SEL_ULPI;
			ग_लिखोl(val, reg);
			/* Set पूर्णांकerrupt wake up enable */
			reg = usbmisc->base + MX53_USB_UH3_CTRL_OFFSET;
			val = पढ़ोl(reg) | MX53_USB_UHx_CTRL_WAKE_UP_EN
				| MX53_USB_UHx_CTRL_ULPI_INT_EN;
			ग_लिखोl(val, reg);

			अगर (is_imx53_usbmisc(data)) अणु
				/* Disable पूर्णांकernal 60Mhz घड़ी */
				reg = usbmisc->base +
					MX53_USB_CLKONOFF_CTRL_OFFSET;
				val = पढ़ोl(reg) |
					MX53_USB_CLKONOFF_CTRL_H3_INT60CKOFF;
				ग_लिखोl(val, reg);
			पूर्ण
		पूर्ण
		अगर (data->disable_oc) अणु
			reg = usbmisc->base + MX53_USB_UH3_CTRL_OFFSET;
			val = पढ़ोl(reg) | MX53_BM_OVER_CUR_DIS_UHx;
			ग_लिखोl(val, reg);
		पूर्ण
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&usbmisc->lock, flags);

	वापस 0;
पूर्ण

अटल u32 usbmisc_wakeup_setting(काष्ठा imx_usbmisc_data *data)
अणु
	u32 wakeup_setting = MX6_USB_OTG_WAKEUP_BITS;

	अगर (data->ext_id || data->available_role != USB_DR_MODE_OTG)
		wakeup_setting &= ~MX6_BM_ID_WAKEUP;

	अगर (data->ext_vbus || data->available_role == USB_DR_MODE_HOST)
		wakeup_setting &= ~MX6_BM_VBUS_WAKEUP;

	वापस wakeup_setting;
पूर्ण

अटल पूर्णांक usbmisc_imx6q_set_wakeup
	(काष्ठा imx_usbmisc_data *data, bool enabled)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक ret = 0;

	अगर (data->index > 3)
		वापस -EINVAL;

	spin_lock_irqsave(&usbmisc->lock, flags);
	val = पढ़ोl(usbmisc->base + data->index * 4);
	अगर (enabled) अणु
		val &= ~MX6_USB_OTG_WAKEUP_BITS;
		val |= usbmisc_wakeup_setting(data);
	पूर्ण अन्यथा अणु
		अगर (val & MX6_BM_WAKEUP_INTR)
			pr_debug("wakeup int at ci_hdrc.%d\n", data->index);
		val &= ~MX6_USB_OTG_WAKEUP_BITS;
	पूर्ण
	ग_लिखोl(val, usbmisc->base + data->index * 4);
	spin_unlock_irqrestore(&usbmisc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक usbmisc_imx6q_init(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (data->index > 3)
		वापस -EINVAL;

	spin_lock_irqsave(&usbmisc->lock, flags);

	reg = पढ़ोl(usbmisc->base + data->index * 4);
	अगर (data->disable_oc) अणु
		reg |= MX6_BM_OVER_CUR_DIS;
	पूर्ण अन्यथा अणु
		reg &= ~MX6_BM_OVER_CUR_DIS;

		/*
		 * If the polarity is not configured keep it as setup by the
		 * bootloader.
		 */
		अगर (data->oc_pol_configured && data->oc_pol_active_low)
			reg |= MX6_BM_OVER_CUR_POLARITY;
		अन्यथा अगर (data->oc_pol_configured)
			reg &= ~MX6_BM_OVER_CUR_POLARITY;
	पूर्ण
	/* If the polarity is not set keep it as setup by the bootlader */
	अगर (data->pwr_pol == 1)
		reg |= MX6_BM_PWR_POLARITY;
	ग_लिखोl(reg, usbmisc->base + data->index * 4);

	/* SoC non-burst setting */
	reg = पढ़ोl(usbmisc->base + data->index * 4);
	ग_लिखोl(reg | MX6_BM_NON_BURST_SETTING,
			usbmisc->base + data->index * 4);

	/* For HSIC controller */
	अगर (data->hsic) अणु
		reg = पढ़ोl(usbmisc->base + data->index * 4);
		ग_लिखोl(reg | MX6_BM_UTMI_ON_CLOCK,
			usbmisc->base + data->index * 4);
		reg = पढ़ोl(usbmisc->base + MX6_USB_HSIC_CTRL_OFFSET
			+ (data->index - 2) * 4);
		reg |= MX6_BM_HSIC_EN | MX6_BM_HSIC_CLK_ON;
		ग_लिखोl(reg, usbmisc->base + MX6_USB_HSIC_CTRL_OFFSET
			+ (data->index - 2) * 4);
	पूर्ण

	spin_unlock_irqrestore(&usbmisc->lock, flags);

	usbmisc_imx6q_set_wakeup(data, false);

	वापस 0;
पूर्ण

अटल पूर्णांक usbmisc_imx6_hsic_get_reg_offset(काष्ठा imx_usbmisc_data *data)
अणु
	पूर्णांक offset, ret = 0;

	अगर (data->index == 2 || data->index == 3) अणु
		offset = (data->index - 2) * 4;
	पूर्ण अन्यथा अगर (data->index == 0) अणु
		/*
		 * For SoCs like i.MX7D and later, each USB controller has
		 * its own non-core रेजिस्टर region. For SoCs beक्रमe i.MX7D,
		 * the first two USB controllers are non-HSIC controllers.
		 */
		offset = 0;
	पूर्ण अन्यथा अणु
		dev_err(data->dev, "index is error for usbmisc\n");
		ret = -EINVAL;
	पूर्ण

	वापस ret ? ret : offset;
पूर्ण

अटल पूर्णांक usbmisc_imx6_hsic_set_connect(काष्ठा imx_usbmisc_data *data)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	पूर्णांक offset;

	spin_lock_irqsave(&usbmisc->lock, flags);
	offset = usbmisc_imx6_hsic_get_reg_offset(data);
	अगर (offset < 0) अणु
		spin_unlock_irqrestore(&usbmisc->lock, flags);
		वापस offset;
	पूर्ण

	val = पढ़ोl(usbmisc->base + MX6_USB_HSIC_CTRL_OFFSET + offset);
	अगर (!(val & MX6_BM_HSIC_DEV_CONN))
		ग_लिखोl(val | MX6_BM_HSIC_DEV_CONN,
			usbmisc->base + MX6_USB_HSIC_CTRL_OFFSET + offset);

	spin_unlock_irqrestore(&usbmisc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक usbmisc_imx6_hsic_set_clk(काष्ठा imx_usbmisc_data *data, bool on)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	पूर्णांक offset;

	spin_lock_irqsave(&usbmisc->lock, flags);
	offset = usbmisc_imx6_hsic_get_reg_offset(data);
	अगर (offset < 0) अणु
		spin_unlock_irqrestore(&usbmisc->lock, flags);
		वापस offset;
	पूर्ण

	val = पढ़ोl(usbmisc->base + MX6_USB_HSIC_CTRL_OFFSET + offset);
	val |= MX6_BM_HSIC_EN | MX6_BM_HSIC_CLK_ON;
	अगर (on)
		val |= MX6_BM_HSIC_CLK_ON;
	अन्यथा
		val &= ~MX6_BM_HSIC_CLK_ON;

	ग_लिखोl(val, usbmisc->base + MX6_USB_HSIC_CTRL_OFFSET + offset);
	spin_unlock_irqrestore(&usbmisc->lock, flags);

	वापस 0;
पूर्ण


अटल पूर्णांक usbmisc_imx6sx_init(काष्ठा imx_usbmisc_data *data)
अणु
	व्योम __iomem *reg = शून्य;
	अचिन्हित दीर्घ flags;
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	u32 val;

	usbmisc_imx6q_init(data);

	अगर (data->index == 0 || data->index == 1) अणु
		reg = usbmisc->base + MX6_USB_OTG1_PHY_CTRL + data->index * 4;
		spin_lock_irqsave(&usbmisc->lock, flags);
		/* Set vbus wakeup source as bvalid */
		val = पढ़ोl(reg);
		ग_लिखोl(val | MX6SX_USB_VBUS_WAKEUP_SOURCE_BVALID, reg);
		/*
		 * Disable dp/dm wakeup in device mode when vbus is
		 * not there.
		 */
		val = पढ़ोl(usbmisc->base + data->index * 4);
		ग_लिखोl(val & ~MX6SX_BM_DPDM_WAKEUP_EN,
			usbmisc->base + data->index * 4);
		spin_unlock_irqrestore(&usbmisc->lock, flags);
	पूर्ण

	/* For HSIC controller */
	अगर (data->hsic) अणु
		val = पढ़ोl(usbmisc->base + MX6_USB_HSIC_CTRL_OFFSET);
		val |= MX6SX_BM_HSIC_AUTO_RESUME;
		ग_लिखोl(val, usbmisc->base + MX6_USB_HSIC_CTRL_OFFSET);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usbmisc_vf610_init(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	u32 reg;

	/*
	 * Vybrid only has one misc रेजिस्टर set, but in two dअगरferent
	 * areas. These is reflected in two instances of this driver.
	 */
	अगर (data->index >= 1)
		वापस -EINVAL;

	अगर (data->disable_oc) अणु
		reg = पढ़ोl(usbmisc->base);
		ग_लिखोl(reg | VF610_OVER_CUR_DIS, usbmisc->base);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usbmisc_imx7d_set_wakeup
	(काष्ठा imx_usbmisc_data *data, bool enabled)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&usbmisc->lock, flags);
	val = पढ़ोl(usbmisc->base);
	अगर (enabled) अणु
		val &= ~MX6_USB_OTG_WAKEUP_BITS;
		val |= usbmisc_wakeup_setting(data);
		ग_लिखोl(val, usbmisc->base);
	पूर्ण अन्यथा अणु
		अगर (val & MX6_BM_WAKEUP_INTR)
			dev_dbg(data->dev, "wakeup int\n");
		ग_लिखोl(val & ~MX6_USB_OTG_WAKEUP_BITS, usbmisc->base);
	पूर्ण
	spin_unlock_irqrestore(&usbmisc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक usbmisc_imx7d_init(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (data->index >= 1)
		वापस -EINVAL;

	spin_lock_irqsave(&usbmisc->lock, flags);
	reg = पढ़ोl(usbmisc->base);
	अगर (data->disable_oc) अणु
		reg |= MX6_BM_OVER_CUR_DIS;
	पूर्ण अन्यथा अणु
		reg &= ~MX6_BM_OVER_CUR_DIS;

		/*
		 * If the polarity is not configured keep it as setup by the
		 * bootloader.
		 */
		अगर (data->oc_pol_configured && data->oc_pol_active_low)
			reg |= MX6_BM_OVER_CUR_POLARITY;
		अन्यथा अगर (data->oc_pol_configured)
			reg &= ~MX6_BM_OVER_CUR_POLARITY;
	पूर्ण
	/* If the polarity is not set keep it as setup by the bootlader */
	अगर (data->pwr_pol == 1)
		reg |= MX6_BM_PWR_POLARITY;
	ग_लिखोl(reg, usbmisc->base);

	/* SoC non-burst setting */
	reg = पढ़ोl(usbmisc->base);
	ग_लिखोl(reg | MX6_BM_NON_BURST_SETTING, usbmisc->base);

	अगर (!data->hsic) अणु
		reg = पढ़ोl(usbmisc->base + MX7D_USBNC_USB_CTRL2);
		reg &= ~MX7D_USB_VBUS_WAKEUP_SOURCE_MASK;
		ग_लिखोl(reg | MX7D_USB_VBUS_WAKEUP_SOURCE_BVALID
			| MX7D_USBNC_AUTO_RESUME,
			usbmisc->base + MX7D_USBNC_USB_CTRL2);
		/* PHY tuning क्रम संकेत quality */
		reg = पढ़ोl(usbmisc->base + MX7D_USB_OTG_PHY_CFG1);
		अगर (data->emp_curr_control && data->emp_curr_control <=
			(TXPREEMPAMPTUNE0_MASK >> TXPREEMPAMPTUNE0_BIT)) अणु
			reg &= ~TXPREEMPAMPTUNE0_MASK;
			reg |= (data->emp_curr_control << TXPREEMPAMPTUNE0_BIT);
		पूर्ण

		अगर (data->dc_vol_level_adjust && data->dc_vol_level_adjust <=
			(TXVREFTUNE0_MASK >> TXVREFTUNE0_BIT)) अणु
			reg &= ~TXVREFTUNE0_MASK;
			reg |= (data->dc_vol_level_adjust << TXVREFTUNE0_BIT);
		पूर्ण

		ग_लिखोl(reg, usbmisc->base + MX7D_USB_OTG_PHY_CFG1);
	पूर्ण

	spin_unlock_irqrestore(&usbmisc->lock, flags);

	usbmisc_imx7d_set_wakeup(data, false);

	वापस 0;
पूर्ण

अटल पूर्णांक imx7d_अक्षरger_secondary_detection(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	काष्ठा usb_phy *usb_phy = data->usb_phy;
	पूर्णांक val;
	अचिन्हित दीर्घ flags;

	/* Clear VDATSRCENB0 to disable VDP_SRC and IDM_SNK required by BC 1.2 spec */
	spin_lock_irqsave(&usbmisc->lock, flags);
	val = पढ़ोl(usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	val &= ~MX7D_USB_OTG_PHY_CFG2_CHRG_VDATSRCENB0;
	ग_लिखोl(val, usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	spin_unlock_irqrestore(&usbmisc->lock, flags);

	/* TVDMSRC_DIS */
	msleep(20);

	/* VDM_SRC is connected to D- and IDP_SINK is connected to D+ */
	spin_lock_irqsave(&usbmisc->lock, flags);
	val = पढ़ोl(usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	ग_लिखोl(val | MX7D_USB_OTG_PHY_CFG2_CHRG_VDATSRCENB0 |
			MX7D_USB_OTG_PHY_CFG2_CHRG_VDATDETENB0 |
			MX7D_USB_OTG_PHY_CFG2_CHRG_CHRGSEL,
				usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	spin_unlock_irqrestore(&usbmisc->lock, flags);

	/* TVDMSRC_ON */
	msleep(40);

	/*
	 * Per BC 1.2, check voltage of D+:
	 * DCP: अगर greater than VDAT_REF;
	 * CDP: अगर less than VDAT_REF.
	 */
	val = पढ़ोl(usbmisc->base + MX7D_USB_OTG_PHY_STATUS);
	अगर (val & MX7D_USB_OTG_PHY_STATUS_CHRGDET) अणु
		dev_dbg(data->dev, "It is a dedicate charging port\n");
		usb_phy->chg_type = DCP_TYPE;
	पूर्ण अन्यथा अणु
		dev_dbg(data->dev, "It is a charging downstream port\n");
		usb_phy->chg_type = CDP_TYPE;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम imx7_disable_अक्षरger_detector(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&usbmisc->lock, flags);
	val = पढ़ोl(usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	val &= ~(MX7D_USB_OTG_PHY_CFG2_CHRG_DCDENB |
			MX7D_USB_OTG_PHY_CFG2_CHRG_VDATSRCENB0 |
			MX7D_USB_OTG_PHY_CFG2_CHRG_VDATDETENB0 |
			MX7D_USB_OTG_PHY_CFG2_CHRG_CHRGSEL);
	ग_लिखोl(val, usbmisc->base + MX7D_USB_OTG_PHY_CFG2);

	/* Set OPMODE to be 2'b00 and disable its override */
	val = पढ़ोl(usbmisc->base + MX7D_USBNC_USB_CTRL2);
	val &= ~MX7D_USBNC_USB_CTRL2_OPMODE_OVERRIDE_MASK;
	ग_लिखोl(val, usbmisc->base + MX7D_USBNC_USB_CTRL2);

	val = पढ़ोl(usbmisc->base + MX7D_USBNC_USB_CTRL2);
	ग_लिखोl(val & ~MX7D_USBNC_USB_CTRL2_OPMODE_OVERRIDE_EN,
			usbmisc->base + MX7D_USBNC_USB_CTRL2);
	spin_unlock_irqrestore(&usbmisc->lock, flags);
पूर्ण

अटल पूर्णांक imx7d_अक्षरger_data_contact_detect(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक i, data_pin_contact_count = 0;

	/* Enable Data Contact Detect (DCD) per the USB BC 1.2 */
	spin_lock_irqsave(&usbmisc->lock, flags);
	val = पढ़ोl(usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	ग_लिखोl(val | MX7D_USB_OTG_PHY_CFG2_CHRG_DCDENB,
			usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	spin_unlock_irqrestore(&usbmisc->lock, flags);

	क्रम (i = 0; i < 100; i = i + 1) अणु
		val = पढ़ोl(usbmisc->base + MX7D_USB_OTG_PHY_STATUS);
		अगर (!(val & MX7D_USB_OTG_PHY_STATUS_LINE_STATE0)) अणु
			अगर (data_pin_contact_count++ > 5)
				/* Data pin makes contact */
				अवरोध;
			usleep_range(5000, 10000);
		पूर्ण अन्यथा अणु
			data_pin_contact_count = 0;
			usleep_range(5000, 6000);
		पूर्ण
	पूर्ण

	/* Disable DCD after finished data contact check */
	spin_lock_irqsave(&usbmisc->lock, flags);
	val = पढ़ोl(usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	ग_लिखोl(val & ~MX7D_USB_OTG_PHY_CFG2_CHRG_DCDENB,
			usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	spin_unlock_irqrestore(&usbmisc->lock, flags);

	अगर (i == 100) अणु
		dev_err(data->dev,
			"VBUS is coming from a dedicated power supply.\n");
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx7d_अक्षरger_primary_detection(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	काष्ठा usb_phy *usb_phy = data->usb_phy;
	अचिन्हित दीर्घ flags;
	u32 val;

	/* VDP_SRC is connected to D+ and IDM_SINK is connected to D- */
	spin_lock_irqsave(&usbmisc->lock, flags);
	val = पढ़ोl(usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	val &= ~MX7D_USB_OTG_PHY_CFG2_CHRG_CHRGSEL;
	ग_लिखोl(val | MX7D_USB_OTG_PHY_CFG2_CHRG_VDATSRCENB0 |
			MX7D_USB_OTG_PHY_CFG2_CHRG_VDATDETENB0,
				usbmisc->base + MX7D_USB_OTG_PHY_CFG2);
	spin_unlock_irqrestore(&usbmisc->lock, flags);

	/* TVDPSRC_ON */
	msleep(40);

	/* Check अगर D- is less than VDAT_REF to determine an SDP per BC 1.2 */
	val = पढ़ोl(usbmisc->base + MX7D_USB_OTG_PHY_STATUS);
	अगर (!(val & MX7D_USB_OTG_PHY_STATUS_CHRGDET)) अणु
		dev_dbg(data->dev, "It is a standard downstream port\n");
		usb_phy->chg_type = SDP_TYPE;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Whole अक्षरger detection process:
 * 1. OPMODE override to be non-driving
 * 2. Data contact check
 * 3. Primary detection
 * 4. Secondary detection
 * 5. Disable अक्षरger detection
 */
अटल पूर्णांक imx7d_अक्षरger_detection(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	काष्ठा usb_phy *usb_phy = data->usb_phy;
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक ret;

	/* Check अगर vbus is valid */
	val = पढ़ोl(usbmisc->base + MX7D_USB_OTG_PHY_STATUS);
	अगर (!(val & MX7D_USB_OTG_PHY_STATUS_VBUS_VLD)) अणु
		dev_err(data->dev, "vbus is error\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Keep OPMODE to be non-driving mode during the whole
	 * अक्षरger detection process.
	 */
	spin_lock_irqsave(&usbmisc->lock, flags);
	val = पढ़ोl(usbmisc->base + MX7D_USBNC_USB_CTRL2);
	val &= ~MX7D_USBNC_USB_CTRL2_OPMODE_OVERRIDE_MASK;
	val |= MX7D_USBNC_USB_CTRL2_OPMODE_NON_DRIVING;
	ग_लिखोl(val, usbmisc->base + MX7D_USBNC_USB_CTRL2);

	val = पढ़ोl(usbmisc->base + MX7D_USBNC_USB_CTRL2);
	ग_लिखोl(val | MX7D_USBNC_USB_CTRL2_OPMODE_OVERRIDE_EN,
			usbmisc->base + MX7D_USBNC_USB_CTRL2);
	spin_unlock_irqrestore(&usbmisc->lock, flags);

	ret = imx7d_अक्षरger_data_contact_detect(data);
	अगर (ret)
		वापस ret;

	ret = imx7d_अक्षरger_primary_detection(data);
	अगर (!ret && usb_phy->chg_type != SDP_TYPE)
		ret = imx7d_अक्षरger_secondary_detection(data);

	imx7_disable_अक्षरger_detector(data);

	वापस ret;
पूर्ण

अटल पूर्णांक usbmisc_imx7ulp_init(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (data->index >= 1)
		वापस -EINVAL;

	spin_lock_irqsave(&usbmisc->lock, flags);
	reg = पढ़ोl(usbmisc->base);
	अगर (data->disable_oc) अणु
		reg |= MX6_BM_OVER_CUR_DIS;
	पूर्ण अन्यथा अणु
		reg &= ~MX6_BM_OVER_CUR_DIS;

		/*
		 * If the polarity is not configured keep it as setup by the
		 * bootloader.
		 */
		अगर (data->oc_pol_configured && data->oc_pol_active_low)
			reg |= MX6_BM_OVER_CUR_POLARITY;
		अन्यथा अगर (data->oc_pol_configured)
			reg &= ~MX6_BM_OVER_CUR_POLARITY;
	पूर्ण
	/* If the polarity is not set keep it as setup by the bootlader */
	अगर (data->pwr_pol == 1)
		reg |= MX6_BM_PWR_POLARITY;

	ग_लिखोl(reg, usbmisc->base);

	/* SoC non-burst setting */
	reg = पढ़ोl(usbmisc->base);
	ग_लिखोl(reg | MX6_BM_NON_BURST_SETTING, usbmisc->base);

	अगर (data->hsic) अणु
		reg = पढ़ोl(usbmisc->base);
		ग_लिखोl(reg | MX6_BM_UTMI_ON_CLOCK, usbmisc->base);

		reg = पढ़ोl(usbmisc->base + MX6_USB_HSIC_CTRL_OFFSET);
		reg |= MX6_BM_HSIC_EN | MX6_BM_HSIC_CLK_ON;
		ग_लिखोl(reg, usbmisc->base + MX6_USB_HSIC_CTRL_OFFSET);

		/*
		 * For non-HSIC controller, the स्वतःresume is enabled
		 * at MXS PHY driver (usbphy_ctrl bit18).
		 */
		reg = पढ़ोl(usbmisc->base + MX7D_USBNC_USB_CTRL2);
		ग_लिखोl(reg | MX7D_USBNC_AUTO_RESUME,
			usbmisc->base + MX7D_USBNC_USB_CTRL2);
	पूर्ण अन्यथा अणु
		reg = पढ़ोl(usbmisc->base + MX7D_USBNC_USB_CTRL2);
		reg &= ~MX7D_USB_VBUS_WAKEUP_SOURCE_MASK;
		ग_लिखोl(reg | MX7D_USB_VBUS_WAKEUP_SOURCE_BVALID,
			 usbmisc->base + MX7D_USBNC_USB_CTRL2);
	पूर्ण

	spin_unlock_irqrestore(&usbmisc->lock, flags);

	usbmisc_imx7d_set_wakeup(data, false);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usbmisc_ops imx25_usbmisc_ops = अणु
	.init = usbmisc_imx25_init,
	.post = usbmisc_imx25_post,
पूर्ण;

अटल स्थिर काष्ठा usbmisc_ops imx27_usbmisc_ops = अणु
	.init = usbmisc_imx27_init,
पूर्ण;

अटल स्थिर काष्ठा usbmisc_ops imx51_usbmisc_ops = अणु
	.init = usbmisc_imx53_init,
पूर्ण;

अटल स्थिर काष्ठा usbmisc_ops imx53_usbmisc_ops = अणु
	.init = usbmisc_imx53_init,
पूर्ण;

अटल स्थिर काष्ठा usbmisc_ops imx6q_usbmisc_ops = अणु
	.set_wakeup = usbmisc_imx6q_set_wakeup,
	.init = usbmisc_imx6q_init,
	.hsic_set_connect = usbmisc_imx6_hsic_set_connect,
	.hsic_set_clk   = usbmisc_imx6_hsic_set_clk,
पूर्ण;

अटल स्थिर काष्ठा usbmisc_ops vf610_usbmisc_ops = अणु
	.init = usbmisc_vf610_init,
पूर्ण;

अटल स्थिर काष्ठा usbmisc_ops imx6sx_usbmisc_ops = अणु
	.set_wakeup = usbmisc_imx6q_set_wakeup,
	.init = usbmisc_imx6sx_init,
	.hsic_set_connect = usbmisc_imx6_hsic_set_connect,
	.hsic_set_clk = usbmisc_imx6_hsic_set_clk,
पूर्ण;

अटल स्थिर काष्ठा usbmisc_ops imx7d_usbmisc_ops = अणु
	.init = usbmisc_imx7d_init,
	.set_wakeup = usbmisc_imx7d_set_wakeup,
	.अक्षरger_detection = imx7d_अक्षरger_detection,
पूर्ण;

अटल स्थिर काष्ठा usbmisc_ops imx7ulp_usbmisc_ops = अणु
	.init = usbmisc_imx7ulp_init,
	.set_wakeup = usbmisc_imx7d_set_wakeup,
	.hsic_set_connect = usbmisc_imx6_hsic_set_connect,
	.hsic_set_clk = usbmisc_imx6_hsic_set_clk,
पूर्ण;

अटल अंतरभूत bool is_imx53_usbmisc(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);

	वापस usbmisc->ops == &imx53_usbmisc_ops;
पूर्ण

पूर्णांक imx_usbmisc_init(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc;

	अगर (!data)
		वापस 0;

	usbmisc = dev_get_drvdata(data->dev);
	अगर (!usbmisc->ops->init)
		वापस 0;
	वापस usbmisc->ops->init(data);
पूर्ण
EXPORT_SYMBOL_GPL(imx_usbmisc_init);

पूर्णांक imx_usbmisc_init_post(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc;

	अगर (!data)
		वापस 0;

	usbmisc = dev_get_drvdata(data->dev);
	अगर (!usbmisc->ops->post)
		वापस 0;
	वापस usbmisc->ops->post(data);
पूर्ण
EXPORT_SYMBOL_GPL(imx_usbmisc_init_post);

पूर्णांक imx_usbmisc_set_wakeup(काष्ठा imx_usbmisc_data *data, bool enabled)
अणु
	काष्ठा imx_usbmisc *usbmisc;

	अगर (!data)
		वापस 0;

	usbmisc = dev_get_drvdata(data->dev);
	अगर (!usbmisc->ops->set_wakeup)
		वापस 0;
	वापस usbmisc->ops->set_wakeup(data, enabled);
पूर्ण
EXPORT_SYMBOL_GPL(imx_usbmisc_set_wakeup);

पूर्णांक imx_usbmisc_hsic_set_connect(काष्ठा imx_usbmisc_data *data)
अणु
	काष्ठा imx_usbmisc *usbmisc;

	अगर (!data)
		वापस 0;

	usbmisc = dev_get_drvdata(data->dev);
	अगर (!usbmisc->ops->hsic_set_connect || !data->hsic)
		वापस 0;
	वापस usbmisc->ops->hsic_set_connect(data);
पूर्ण
EXPORT_SYMBOL_GPL(imx_usbmisc_hsic_set_connect);

पूर्णांक imx_usbmisc_hsic_set_clk(काष्ठा imx_usbmisc_data *data, bool on)
अणु
	काष्ठा imx_usbmisc *usbmisc;

	अगर (!data)
		वापस 0;

	usbmisc = dev_get_drvdata(data->dev);
	अगर (!usbmisc->ops->hsic_set_clk || !data->hsic)
		वापस 0;
	वापस usbmisc->ops->hsic_set_clk(data, on);
पूर्ण
EXPORT_SYMBOL_GPL(imx_usbmisc_hsic_set_clk);

पूर्णांक imx_usbmisc_अक्षरger_detection(काष्ठा imx_usbmisc_data *data, bool connect)
अणु
	काष्ठा imx_usbmisc *usbmisc;
	काष्ठा usb_phy *usb_phy;
	पूर्णांक ret = 0;

	अगर (!data)
		वापस -EINVAL;

	usbmisc = dev_get_drvdata(data->dev);
	usb_phy = data->usb_phy;
	अगर (!usbmisc->ops->अक्षरger_detection)
		वापस -ENOTSUPP;

	अगर (connect) अणु
		ret = usbmisc->ops->अक्षरger_detection(data);
		अगर (ret) अणु
			dev_err(data->dev,
					"Error occurs during detection: %d\n",
					ret);
			usb_phy->chg_state = USB_CHARGER_ABSENT;
		पूर्ण अन्यथा अणु
			usb_phy->chg_state = USB_CHARGER_PRESENT;
		पूर्ण
	पूर्ण अन्यथा अणु
		usb_phy->chg_state = USB_CHARGER_ABSENT;
		usb_phy->chg_type = UNKNOWN_TYPE;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(imx_usbmisc_अक्षरger_detection);

अटल स्थिर काष्ठा of_device_id usbmisc_imx_dt_ids[] = अणु
	अणु
		.compatible = "fsl,imx25-usbmisc",
		.data = &imx25_usbmisc_ops,
	पूर्ण,
	अणु
		.compatible = "fsl,imx35-usbmisc",
		.data = &imx25_usbmisc_ops,
	पूर्ण,
	अणु
		.compatible = "fsl,imx27-usbmisc",
		.data = &imx27_usbmisc_ops,
	पूर्ण,
	अणु
		.compatible = "fsl,imx51-usbmisc",
		.data = &imx51_usbmisc_ops,
	पूर्ण,
	अणु
		.compatible = "fsl,imx53-usbmisc",
		.data = &imx53_usbmisc_ops,
	पूर्ण,
	अणु
		.compatible = "fsl,imx6q-usbmisc",
		.data = &imx6q_usbmisc_ops,
	पूर्ण,
	अणु
		.compatible = "fsl,vf610-usbmisc",
		.data = &vf610_usbmisc_ops,
	पूर्ण,
	अणु
		.compatible = "fsl,imx6sx-usbmisc",
		.data = &imx6sx_usbmisc_ops,
	पूर्ण,
	अणु
		.compatible = "fsl,imx6ul-usbmisc",
		.data = &imx6sx_usbmisc_ops,
	पूर्ण,
	अणु
		.compatible = "fsl,imx7d-usbmisc",
		.data = &imx7d_usbmisc_ops,
	पूर्ण,
	अणु
		.compatible = "fsl,imx7ulp-usbmisc",
		.data = &imx7ulp_usbmisc_ops,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, usbmisc_imx_dt_ids);

अटल पूर्णांक usbmisc_imx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_usbmisc *data;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	spin_lock_init(&data->lock);

	data->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->base))
		वापस PTR_ERR(data->base);

	data->ops = of_device_get_match_data(&pdev->dev);
	platक्रमm_set_drvdata(pdev, data);

	वापस 0;
पूर्ण

अटल पूर्णांक usbmisc_imx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver usbmisc_imx_driver = अणु
	.probe = usbmisc_imx_probe,
	.हटाओ = usbmisc_imx_हटाओ,
	.driver = अणु
		.name = "usbmisc_imx",
		.of_match_table = usbmisc_imx_dt_ids,
	 पूर्ण,
पूर्ण;

module_platक्रमm_driver(usbmisc_imx_driver);

MODULE_ALIAS("platform:usbmisc-imx");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("driver for imx usb non-core registers");
MODULE_AUTHOR("Richard Zhao <richard.zhao@freescale.com>");
