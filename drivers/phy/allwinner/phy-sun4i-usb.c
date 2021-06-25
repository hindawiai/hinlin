<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Allwinner sun4i USB phy driver
 *
 * Copyright (C) 2014-2015 Hans de Goede <hdegoede@redhat.com>
 *
 * Based on code from
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 *
 * Modelled after: Samsung S5P/Exynos SoC series MIPI CSIS/DSIM DPHY driver
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/phy-sun4i-usb.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/workqueue.h>

#घोषणा REG_ISCR			0x00
#घोषणा REG_PHYCTL_A10			0x04
#घोषणा REG_PHYBIST			0x08
#घोषणा REG_PHYTUNE			0x0c
#घोषणा REG_PHYCTL_A33			0x10
#घोषणा REG_PHY_OTGCTL			0x20

#घोषणा REG_PMU_UNK1			0x10

#घोषणा PHYCTL_DATA			BIT(7)

#घोषणा OTGCTL_ROUTE_MUSB		BIT(0)

#घोषणा SUNXI_AHB_ICHR8_EN		BIT(10)
#घोषणा SUNXI_AHB_INCR4_BURST_EN	BIT(9)
#घोषणा SUNXI_AHB_INCRX_ALIGN_EN	BIT(8)
#घोषणा SUNXI_ULPI_BYPASS_EN		BIT(0)

/* ISCR, Interface Status and Control bits */
#घोषणा ISCR_ID_PULLUP_EN		(1 << 17)
#घोषणा ISCR_DPDM_PULLUP_EN	(1 << 16)
/* sunxi has the phy id/vbus pins not connected, so we use the क्रमce bits */
#घोषणा ISCR_FORCE_ID_MASK	(3 << 14)
#घोषणा ISCR_FORCE_ID_LOW		(2 << 14)
#घोषणा ISCR_FORCE_ID_HIGH	(3 << 14)
#घोषणा ISCR_FORCE_VBUS_MASK	(3 << 12)
#घोषणा ISCR_FORCE_VBUS_LOW	(2 << 12)
#घोषणा ISCR_FORCE_VBUS_HIGH	(3 << 12)

/* Common Control Bits क्रम Both PHYs */
#घोषणा PHY_PLL_BW			0x03
#घोषणा PHY_RES45_CAL_EN		0x0c

/* Private Control Bits क्रम Each PHY */
#घोषणा PHY_TX_AMPLITUDE_TUNE		0x20
#घोषणा PHY_TX_SLEWRATE_TUNE		0x22
#घोषणा PHY_VBUSVALID_TH_SEL		0x25
#घोषणा PHY_PULLUP_RES_SEL		0x27
#घोषणा PHY_OTG_FUNC_EN			0x28
#घोषणा PHY_VBUS_DET_EN			0x29
#घोषणा PHY_DISCON_TH_SEL		0x2a
#घोषणा PHY_SQUELCH_DETECT		0x3c

/* A83T specअगरic control bits क्रम PHY0 */
#घोषणा PHY_CTL_VBUSVLDEXT		BIT(5)
#घोषणा PHY_CTL_SIDDQ			BIT(3)

/* A83T specअगरic control bits क्रम PHY2 HSIC */
#घोषणा SUNXI_EHCI_HS_FORCE		BIT(20)
#घोषणा SUNXI_HSIC_CONNECT_DET		BIT(17)
#घोषणा SUNXI_HSIC_CONNECT_INT		BIT(16)
#घोषणा SUNXI_HSIC			BIT(1)

#घोषणा MAX_PHYS			4

/*
 * Note करो not उठाओ the debounce समय, we must report Vusb high within 100ms
 * otherwise we get Vbus errors
 */
#घोषणा DEBOUNCE_TIME			msecs_to_jअगरfies(50)
#घोषणा POLL_TIME			msecs_to_jअगरfies(250)

क्रमागत sun4i_usb_phy_type अणु
	sun4i_a10_phy,
	sun6i_a31_phy,
	sun8i_a33_phy,
	sun8i_a83t_phy,
	sun8i_h3_phy,
	sun8i_r40_phy,
	sun8i_v3s_phy,
	sun50i_a64_phy,
	sun50i_h6_phy,
पूर्ण;

काष्ठा sun4i_usb_phy_cfg अणु
	पूर्णांक num_phys;
	पूर्णांक hsic_index;
	क्रमागत sun4i_usb_phy_type type;
	u32 disc_thresh;
	u8 phyctl_offset;
	bool dedicated_घड़ीs;
	bool enable_pmu_unk1;
	bool phy0_dual_route;
	पूर्णांक missing_phys;
पूर्ण;

काष्ठा sun4i_usb_phy_data अणु
	व्योम __iomem *base;
	स्थिर काष्ठा sun4i_usb_phy_cfg *cfg;
	क्रमागत usb_dr_mode dr_mode;
	spinlock_t reg_lock; /* guard access to phyctl reg */
	काष्ठा sun4i_usb_phy अणु
		काष्ठा phy *phy;
		व्योम __iomem *pmu;
		काष्ठा regulator *vbus;
		काष्ठा reset_control *reset;
		काष्ठा clk *clk;
		काष्ठा clk *clk2;
		bool regulator_on;
		पूर्णांक index;
	पूर्ण phys[MAX_PHYS];
	/* phy0 / otg related variables */
	काष्ठा extcon_dev *extcon;
	bool phy0_init;
	काष्ठा gpio_desc *id_det_gpio;
	काष्ठा gpio_desc *vbus_det_gpio;
	काष्ठा घातer_supply *vbus_घातer_supply;
	काष्ठा notअगरier_block vbus_घातer_nb;
	bool vbus_घातer_nb_रेजिस्टरed;
	bool क्रमce_session_end;
	पूर्णांक id_det_irq;
	पूर्णांक vbus_det_irq;
	पूर्णांक id_det;
	पूर्णांक vbus_det;
	काष्ठा delayed_work detect;
पूर्ण;

#घोषणा to_sun4i_usb_phy_data(phy) \
	container_of((phy), काष्ठा sun4i_usb_phy_data, phys[(phy)->index])

अटल व्योम sun4i_usb_phy0_update_iscr(काष्ठा phy *_phy, u32 clr, u32 set)
अणु
	काष्ठा sun4i_usb_phy *phy = phy_get_drvdata(_phy);
	काष्ठा sun4i_usb_phy_data *data = to_sun4i_usb_phy_data(phy);
	u32 iscr;

	iscr = पढ़ोl(data->base + REG_ISCR);
	iscr &= ~clr;
	iscr |= set;
	ग_लिखोl(iscr, data->base + REG_ISCR);
पूर्ण

अटल व्योम sun4i_usb_phy0_set_id_detect(काष्ठा phy *phy, u32 val)
अणु
	अगर (val)
		val = ISCR_FORCE_ID_HIGH;
	अन्यथा
		val = ISCR_FORCE_ID_LOW;

	sun4i_usb_phy0_update_iscr(phy, ISCR_FORCE_ID_MASK, val);
पूर्ण

अटल व्योम sun4i_usb_phy0_set_vbus_detect(काष्ठा phy *phy, u32 val)
अणु
	अगर (val)
		val = ISCR_FORCE_VBUS_HIGH;
	अन्यथा
		val = ISCR_FORCE_VBUS_LOW;

	sun4i_usb_phy0_update_iscr(phy, ISCR_FORCE_VBUS_MASK, val);
पूर्ण

अटल व्योम sun4i_usb_phy_ग_लिखो(काष्ठा sun4i_usb_phy *phy, u32 addr, u32 data,
				पूर्णांक len)
अणु
	काष्ठा sun4i_usb_phy_data *phy_data = to_sun4i_usb_phy_data(phy);
	u32 temp, usbc_bit = BIT(phy->index * 2);
	व्योम __iomem *phyctl = phy_data->base + phy_data->cfg->phyctl_offset;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&phy_data->reg_lock, flags);

	अगर (phy_data->cfg->phyctl_offset == REG_PHYCTL_A33) अणु
		/* SoCs newer than A33 need us to set phyctl to 0 explicitly */
		ग_लिखोl(0, phyctl);
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		temp = पढ़ोl(phyctl);

		/* clear the address portion */
		temp &= ~(0xff << 8);

		/* set the address */
		temp |= ((addr + i) << 8);
		ग_लिखोl(temp, phyctl);

		/* set the data bit and clear usbc bit*/
		temp = पढ़ोb(phyctl);
		अगर (data & 0x1)
			temp |= PHYCTL_DATA;
		अन्यथा
			temp &= ~PHYCTL_DATA;
		temp &= ~usbc_bit;
		ग_लिखोb(temp, phyctl);

		/* pulse usbc_bit */
		temp = पढ़ोb(phyctl);
		temp |= usbc_bit;
		ग_लिखोb(temp, phyctl);

		temp = पढ़ोb(phyctl);
		temp &= ~usbc_bit;
		ग_लिखोb(temp, phyctl);

		data >>= 1;
	पूर्ण

	spin_unlock_irqrestore(&phy_data->reg_lock, flags);
पूर्ण

अटल व्योम sun4i_usb_phy_passby(काष्ठा sun4i_usb_phy *phy, पूर्णांक enable)
अणु
	काष्ठा sun4i_usb_phy_data *phy_data = to_sun4i_usb_phy_data(phy);
	u32 bits, reg_value;

	अगर (!phy->pmu)
		वापस;

	bits = SUNXI_AHB_ICHR8_EN | SUNXI_AHB_INCR4_BURST_EN |
		SUNXI_AHB_INCRX_ALIGN_EN | SUNXI_ULPI_BYPASS_EN;

	/* A83T USB2 is HSIC */
	अगर (phy_data->cfg->type == sun8i_a83t_phy && phy->index == 2)
		bits |= SUNXI_EHCI_HS_FORCE | SUNXI_HSIC_CONNECT_INT |
			SUNXI_HSIC;

	reg_value = पढ़ोl(phy->pmu);

	अगर (enable)
		reg_value |= bits;
	अन्यथा
		reg_value &= ~bits;

	ग_लिखोl(reg_value, phy->pmu);
पूर्ण

अटल पूर्णांक sun4i_usb_phy_init(काष्ठा phy *_phy)
अणु
	काष्ठा sun4i_usb_phy *phy = phy_get_drvdata(_phy);
	काष्ठा sun4i_usb_phy_data *data = to_sun4i_usb_phy_data(phy);
	पूर्णांक ret;
	u32 val;

	ret = clk_prepare_enable(phy->clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(phy->clk2);
	अगर (ret) अणु
		clk_disable_unprepare(phy->clk);
		वापस ret;
	पूर्ण

	ret = reset_control_deनिश्चित(phy->reset);
	अगर (ret) अणु
		clk_disable_unprepare(phy->clk2);
		clk_disable_unprepare(phy->clk);
		वापस ret;
	पूर्ण

	अगर (data->cfg->type == sun8i_a83t_phy ||
	    data->cfg->type == sun50i_h6_phy) अणु
		अगर (phy->index == 0) अणु
			val = पढ़ोl(data->base + data->cfg->phyctl_offset);
			val |= PHY_CTL_VBUSVLDEXT;
			val &= ~PHY_CTL_SIDDQ;
			ग_लिखोl(val, data->base + data->cfg->phyctl_offset);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (phy->pmu && data->cfg->enable_pmu_unk1) अणु
			val = पढ़ोl(phy->pmu + REG_PMU_UNK1);
			ग_लिखोl(val & ~2, phy->pmu + REG_PMU_UNK1);
		पूर्ण

		/* Enable USB 45 Ohm resistor calibration */
		अगर (phy->index == 0)
			sun4i_usb_phy_ग_लिखो(phy, PHY_RES45_CAL_EN, 0x01, 1);

		/* Adjust PHY's magnitude and rate */
		sun4i_usb_phy_ग_लिखो(phy, PHY_TX_AMPLITUDE_TUNE, 0x14, 5);

		/* Disconnect threshold adjusपंचांगent */
		sun4i_usb_phy_ग_लिखो(phy, PHY_DISCON_TH_SEL,
				    data->cfg->disc_thresh, 2);
	पूर्ण

	sun4i_usb_phy_passby(phy, 1);

	अगर (phy->index == 0) अणु
		data->phy0_init = true;

		/* Enable pull-ups */
		sun4i_usb_phy0_update_iscr(_phy, 0, ISCR_DPDM_PULLUP_EN);
		sun4i_usb_phy0_update_iscr(_phy, 0, ISCR_ID_PULLUP_EN);

		/* Force ISCR and cable state updates */
		data->id_det = -1;
		data->vbus_det = -1;
		queue_delayed_work(प्रणाली_wq, &data->detect, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_usb_phy_निकास(काष्ठा phy *_phy)
अणु
	काष्ठा sun4i_usb_phy *phy = phy_get_drvdata(_phy);
	काष्ठा sun4i_usb_phy_data *data = to_sun4i_usb_phy_data(phy);

	अगर (phy->index == 0) अणु
		अगर (data->cfg->type == sun8i_a83t_phy ||
		    data->cfg->type == sun50i_h6_phy) अणु
			व्योम __iomem *phyctl = data->base +
				data->cfg->phyctl_offset;

			ग_लिखोl(पढ़ोl(phyctl) | PHY_CTL_SIDDQ, phyctl);
		पूर्ण

		/* Disable pull-ups */
		sun4i_usb_phy0_update_iscr(_phy, ISCR_DPDM_PULLUP_EN, 0);
		sun4i_usb_phy0_update_iscr(_phy, ISCR_ID_PULLUP_EN, 0);
		data->phy0_init = false;
	पूर्ण

	sun4i_usb_phy_passby(phy, 0);
	reset_control_निश्चित(phy->reset);
	clk_disable_unprepare(phy->clk2);
	clk_disable_unprepare(phy->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_usb_phy0_get_id_det(काष्ठा sun4i_usb_phy_data *data)
अणु
	चयन (data->dr_mode) अणु
	हाल USB_DR_MODE_OTG:
		अगर (data->id_det_gpio)
			वापस gpiod_get_value_cansleep(data->id_det_gpio);
		अन्यथा
			वापस 1; /* Fallback to peripheral mode */
	हाल USB_DR_MODE_HOST:
		वापस 0;
	हाल USB_DR_MODE_PERIPHERAL:
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक sun4i_usb_phy0_get_vbus_det(काष्ठा sun4i_usb_phy_data *data)
अणु
	अगर (data->vbus_det_gpio)
		वापस gpiod_get_value_cansleep(data->vbus_det_gpio);

	अगर (data->vbus_घातer_supply) अणु
		जोड़ घातer_supply_propval val;
		पूर्णांक r;

		r = घातer_supply_get_property(data->vbus_घातer_supply,
					      POWER_SUPPLY_PROP_PRESENT, &val);
		अगर (r == 0)
			वापस val.पूर्णांकval;
	पूर्ण

	/* Fallback: report vbus as high */
	वापस 1;
पूर्ण

अटल bool sun4i_usb_phy0_have_vbus_det(काष्ठा sun4i_usb_phy_data *data)
अणु
	वापस data->vbus_det_gpio || data->vbus_घातer_supply;
पूर्ण

अटल bool sun4i_usb_phy0_poll(काष्ठा sun4i_usb_phy_data *data)
अणु
	अगर ((data->id_det_gpio && data->id_det_irq <= 0) ||
	    (data->vbus_det_gpio && data->vbus_det_irq <= 0))
		वापस true;

	/*
	 * The A31/A23/A33 companion pmics (AXP221/AXP223) करो not
	 * generate vbus change पूर्णांकerrupts when the board is driving
	 * vbus using the N_VBUSEN pin on the pmic, so we must poll
	 * when using the pmic क्रम vbus-det _and_ we're driving vbus.
	 */
	अगर ((data->cfg->type == sun6i_a31_phy ||
	     data->cfg->type == sun8i_a33_phy) &&
	    data->vbus_घातer_supply && data->phys[0].regulator_on)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक sun4i_usb_phy_घातer_on(काष्ठा phy *_phy)
अणु
	काष्ठा sun4i_usb_phy *phy = phy_get_drvdata(_phy);
	काष्ठा sun4i_usb_phy_data *data = to_sun4i_usb_phy_data(phy);
	पूर्णांक ret;

	अगर (!phy->vbus || phy->regulator_on)
		वापस 0;

	/* For phy0 only turn on Vbus अगर we करोn't have an ext. Vbus */
	अगर (phy->index == 0 && sun4i_usb_phy0_have_vbus_det(data) &&
				data->vbus_det) अणु
		dev_warn(&_phy->dev, "External vbus detected, not enabling our own vbus\n");
		वापस 0;
	पूर्ण

	ret = regulator_enable(phy->vbus);
	अगर (ret)
		वापस ret;

	phy->regulator_on = true;

	/* We must report Vbus high within OTG_TIME_A_WAIT_VRISE msec. */
	अगर (phy->index == 0 && sun4i_usb_phy0_poll(data))
		mod_delayed_work(प्रणाली_wq, &data->detect, DEBOUNCE_TIME);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_usb_phy_घातer_off(काष्ठा phy *_phy)
अणु
	काष्ठा sun4i_usb_phy *phy = phy_get_drvdata(_phy);
	काष्ठा sun4i_usb_phy_data *data = to_sun4i_usb_phy_data(phy);

	अगर (!phy->vbus || !phy->regulator_on)
		वापस 0;

	regulator_disable(phy->vbus);
	phy->regulator_on = false;

	/*
	 * phy0 vbus typically slowly disअक्षरges, someबार this causes the
	 * Vbus gpio to not trigger an edge irq on Vbus off, so क्रमce a rescan.
	 */
	अगर (phy->index == 0 && !sun4i_usb_phy0_poll(data))
		mod_delayed_work(प्रणाली_wq, &data->detect, POLL_TIME);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_usb_phy_set_mode(काष्ठा phy *_phy,
				  क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	काष्ठा sun4i_usb_phy *phy = phy_get_drvdata(_phy);
	काष्ठा sun4i_usb_phy_data *data = to_sun4i_usb_phy_data(phy);
	पूर्णांक new_mode;

	अगर (phy->index != 0) अणु
		अगर (mode == PHY_MODE_USB_HOST)
			वापस 0;
		वापस -EINVAL;
	पूर्ण

	चयन (mode) अणु
	हाल PHY_MODE_USB_HOST:
		new_mode = USB_DR_MODE_HOST;
		अवरोध;
	हाल PHY_MODE_USB_DEVICE:
		new_mode = USB_DR_MODE_PERIPHERAL;
		अवरोध;
	हाल PHY_MODE_USB_OTG:
		new_mode = USB_DR_MODE_OTG;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (new_mode != data->dr_mode) अणु
		dev_info(&_phy->dev, "Changing dr_mode to %d\n", new_mode);
		data->dr_mode = new_mode;
	पूर्ण

	data->id_det = -1; /* Force reprocessing of id */
	data->क्रमce_session_end = true;
	queue_delayed_work(प्रणाली_wq, &data->detect, 0);

	वापस 0;
पूर्ण

व्योम sun4i_usb_phy_set_squelch_detect(काष्ठा phy *_phy, bool enabled)
अणु
	काष्ठा sun4i_usb_phy *phy = phy_get_drvdata(_phy);

	sun4i_usb_phy_ग_लिखो(phy, PHY_SQUELCH_DETECT, enabled ? 0 : 2, 2);
पूर्ण
EXPORT_SYMBOL_GPL(sun4i_usb_phy_set_squelch_detect);

अटल स्थिर काष्ठा phy_ops sun4i_usb_phy_ops = अणु
	.init		= sun4i_usb_phy_init,
	.निकास		= sun4i_usb_phy_निकास,
	.घातer_on	= sun4i_usb_phy_घातer_on,
	.घातer_off	= sun4i_usb_phy_घातer_off,
	.set_mode	= sun4i_usb_phy_set_mode,
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम sun4i_usb_phy0_reroute(काष्ठा sun4i_usb_phy_data *data, पूर्णांक id_det)
अणु
	u32 regval;

	regval = पढ़ोl(data->base + REG_PHY_OTGCTL);
	अगर (id_det == 0) अणु
		/* Host mode. Route phy0 to EHCI/OHCI */
		regval &= ~OTGCTL_ROUTE_MUSB;
	पूर्ण अन्यथा अणु
		/* Peripheral mode. Route phy0 to MUSB */
		regval |= OTGCTL_ROUTE_MUSB;
	पूर्ण
	ग_लिखोl(regval, data->base + REG_PHY_OTGCTL);
पूर्ण

अटल व्योम sun4i_usb_phy0_id_vbus_det_scan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sun4i_usb_phy_data *data =
		container_of(work, काष्ठा sun4i_usb_phy_data, detect.work);
	काष्ठा phy *phy0 = data->phys[0].phy;
	काष्ठा sun4i_usb_phy *phy;
	bool क्रमce_session_end, id_notअगरy = false, vbus_notअगरy = false;
	पूर्णांक id_det, vbus_det;

	अगर (!phy0)
		वापस;

	phy = phy_get_drvdata(phy0);
	id_det = sun4i_usb_phy0_get_id_det(data);
	vbus_det = sun4i_usb_phy0_get_vbus_det(data);

	mutex_lock(&phy0->mutex);

	अगर (!data->phy0_init) अणु
		mutex_unlock(&phy0->mutex);
		वापस;
	पूर्ण

	क्रमce_session_end = data->क्रमce_session_end;
	data->क्रमce_session_end = false;

	अगर (id_det != data->id_det) अणु
		/* id-change, क्रमce session end अगर we've no vbus detection */
		अगर (data->dr_mode == USB_DR_MODE_OTG &&
		    !sun4i_usb_phy0_have_vbus_det(data))
			क्रमce_session_end = true;

		/* When entering host mode (id = 0) क्रमce end the session now */
		अगर (क्रमce_session_end && id_det == 0) अणु
			sun4i_usb_phy0_set_vbus_detect(phy0, 0);
			msleep(200);
			sun4i_usb_phy0_set_vbus_detect(phy0, 1);
		पूर्ण
		sun4i_usb_phy0_set_id_detect(phy0, id_det);
		data->id_det = id_det;
		id_notअगरy = true;
	पूर्ण

	अगर (vbus_det != data->vbus_det) अणु
		sun4i_usb_phy0_set_vbus_detect(phy0, vbus_det);
		data->vbus_det = vbus_det;
		vbus_notअगरy = true;
	पूर्ण

	mutex_unlock(&phy0->mutex);

	अगर (id_notअगरy) अणु
		extcon_set_state_sync(data->extcon, EXTCON_USB_HOST,
					!id_det);
		/* When leaving host mode क्रमce end the session here */
		अगर (क्रमce_session_end && id_det == 1) अणु
			mutex_lock(&phy0->mutex);
			sun4i_usb_phy0_set_vbus_detect(phy0, 0);
			msleep(1000);
			sun4i_usb_phy0_set_vbus_detect(phy0, 1);
			mutex_unlock(&phy0->mutex);
		पूर्ण

		/* Enable PHY0 passby क्रम host mode only. */
		sun4i_usb_phy_passby(phy, !id_det);

		/* Re-route PHY0 अगर necessary */
		अगर (data->cfg->phy0_dual_route)
			sun4i_usb_phy0_reroute(data, id_det);
	पूर्ण

	अगर (vbus_notअगरy)
		extcon_set_state_sync(data->extcon, EXTCON_USB, vbus_det);

	अगर (sun4i_usb_phy0_poll(data))
		queue_delayed_work(प्रणाली_wq, &data->detect, POLL_TIME);
पूर्ण

अटल irqवापस_t sun4i_usb_phy0_id_vbus_det_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sun4i_usb_phy_data *data = dev_id;

	/* vbus or id changed, let the pins settle and then scan them */
	mod_delayed_work(प्रणाली_wq, &data->detect, DEBOUNCE_TIME);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sun4i_usb_phy0_vbus_notअगरy(काष्ठा notअगरier_block *nb,
				      अचिन्हित दीर्घ val, व्योम *v)
अणु
	काष्ठा sun4i_usb_phy_data *data =
		container_of(nb, काष्ठा sun4i_usb_phy_data, vbus_घातer_nb);
	काष्ठा घातer_supply *psy = v;

	/* Properties on the vbus_घातer_supply changed, scan vbus_det */
	अगर (val == PSY_EVENT_PROP_CHANGED && psy == data->vbus_घातer_supply)
		mod_delayed_work(प्रणाली_wq, &data->detect, DEBOUNCE_TIME);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा phy *sun4i_usb_phy_xlate(काष्ठा device *dev,
					काष्ठा of_phandle_args *args)
अणु
	काष्ठा sun4i_usb_phy_data *data = dev_get_drvdata(dev);

	अगर (args->args[0] >= data->cfg->num_phys)
		वापस ERR_PTR(-ENODEV);

	अगर (data->cfg->missing_phys & BIT(args->args[0]))
		वापस ERR_PTR(-ENODEV);

	वापस data->phys[args->args[0]].phy;
पूर्ण

अटल पूर्णांक sun4i_usb_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sun4i_usb_phy_data *data = dev_get_drvdata(dev);

	अगर (data->vbus_घातer_nb_रेजिस्टरed)
		घातer_supply_unreg_notअगरier(&data->vbus_घातer_nb);
	अगर (data->id_det_irq > 0)
		devm_मुक्त_irq(dev, data->id_det_irq, data);
	अगर (data->vbus_det_irq > 0)
		devm_मुक्त_irq(dev, data->vbus_det_irq, data);

	cancel_delayed_work_sync(&data->detect);

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक sun4i_usb_phy0_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
पूर्ण;

अटल पूर्णांक sun4i_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_usb_phy_data *data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा phy_provider *phy_provider;
	पूर्णांक i, ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	spin_lock_init(&data->reg_lock);
	INIT_DELAYED_WORK(&data->detect, sun4i_usb_phy0_id_vbus_det_scan);
	dev_set_drvdata(dev, data);
	data->cfg = of_device_get_match_data(dev);
	अगर (!data->cfg)
		वापस -EINVAL;

	data->base = devm_platक्रमm_ioremap_resource_byname(pdev, "phy_ctrl");
	अगर (IS_ERR(data->base))
		वापस PTR_ERR(data->base);

	data->id_det_gpio = devm_gpiod_get_optional(dev, "usb0_id_det",
						    GPIOD_IN);
	अगर (IS_ERR(data->id_det_gpio)) अणु
		dev_err(dev, "Couldn't request ID GPIO\n");
		वापस PTR_ERR(data->id_det_gpio);
	पूर्ण

	data->vbus_det_gpio = devm_gpiod_get_optional(dev, "usb0_vbus_det",
						      GPIOD_IN);
	अगर (IS_ERR(data->vbus_det_gpio)) अणु
		dev_err(dev, "Couldn't request VBUS detect GPIO\n");
		वापस PTR_ERR(data->vbus_det_gpio);
	पूर्ण

	अगर (of_find_property(np, "usb0_vbus_power-supply", शून्य)) अणु
		data->vbus_घातer_supply = devm_घातer_supply_get_by_phandle(dev,
						     "usb0_vbus_power-supply");
		अगर (IS_ERR(data->vbus_घातer_supply)) अणु
			dev_err(dev, "Couldn't get the VBUS power supply\n");
			वापस PTR_ERR(data->vbus_घातer_supply);
		पूर्ण

		अगर (!data->vbus_घातer_supply)
			वापस -EPROBE_DEFER;
	पूर्ण

	data->dr_mode = of_usb_get_dr_mode_by_phy(np, 0);

	data->extcon = devm_extcon_dev_allocate(dev, sun4i_usb_phy0_cable);
	अगर (IS_ERR(data->extcon)) अणु
		dev_err(dev, "Couldn't allocate our extcon device\n");
		वापस PTR_ERR(data->extcon);
	पूर्ण

	ret = devm_extcon_dev_रेजिस्टर(dev, data->extcon);
	अगर (ret) अणु
		dev_err(dev, "failed to register extcon: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < data->cfg->num_phys; i++) अणु
		काष्ठा sun4i_usb_phy *phy = data->phys + i;
		अक्षर name[16];

		अगर (data->cfg->missing_phys & BIT(i))
			जारी;

		snम_लिखो(name, माप(name), "usb%d_vbus", i);
		phy->vbus = devm_regulator_get_optional(dev, name);
		अगर (IS_ERR(phy->vbus)) अणु
			अगर (PTR_ERR(phy->vbus) == -EPROBE_DEFER) अणु
				dev_err(dev,
					"Couldn't get regulator %s... Deferring probe\n",
					name);
				वापस -EPROBE_DEFER;
			पूर्ण

			phy->vbus = शून्य;
		पूर्ण

		अगर (data->cfg->dedicated_घड़ीs)
			snम_लिखो(name, माप(name), "usb%d_phy", i);
		अन्यथा
			strlcpy(name, "usb_phy", माप(name));

		phy->clk = devm_clk_get(dev, name);
		अगर (IS_ERR(phy->clk)) अणु
			dev_err(dev, "failed to get clock %s\n", name);
			वापस PTR_ERR(phy->clk);
		पूर्ण

		/* The first PHY is always tied to OTG, and never HSIC */
		अगर (data->cfg->hsic_index && i == data->cfg->hsic_index) अणु
			/* HSIC needs secondary घड़ी */
			snम_लिखो(name, माप(name), "usb%d_hsic_12M", i);
			phy->clk2 = devm_clk_get(dev, name);
			अगर (IS_ERR(phy->clk2)) अणु
				dev_err(dev, "failed to get clock %s\n", name);
				वापस PTR_ERR(phy->clk2);
			पूर्ण
		पूर्ण

		snम_लिखो(name, माप(name), "usb%d_reset", i);
		phy->reset = devm_reset_control_get(dev, name);
		अगर (IS_ERR(phy->reset)) अणु
			dev_err(dev, "failed to get reset %s\n", name);
			वापस PTR_ERR(phy->reset);
		पूर्ण

		अगर (i || data->cfg->phy0_dual_route) अणु /* No pmu क्रम musb */
			snम_लिखो(name, माप(name), "pmu%d", i);
			phy->pmu = devm_platक्रमm_ioremap_resource_byname(pdev, name);
			अगर (IS_ERR(phy->pmu))
				वापस PTR_ERR(phy->pmu);
		पूर्ण

		phy->phy = devm_phy_create(dev, शून्य, &sun4i_usb_phy_ops);
		अगर (IS_ERR(phy->phy)) अणु
			dev_err(dev, "failed to create PHY %d\n", i);
			वापस PTR_ERR(phy->phy);
		पूर्ण

		phy->index = i;
		phy_set_drvdata(phy->phy, &data->phys[i]);
	पूर्ण

	data->id_det_irq = gpiod_to_irq(data->id_det_gpio);
	अगर (data->id_det_irq > 0) अणु
		ret = devm_request_irq(dev, data->id_det_irq,
				sun4i_usb_phy0_id_vbus_det_irq,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				"usb0-id-det", data);
		अगर (ret) अणु
			dev_err(dev, "Err requesting id-det-irq: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	data->vbus_det_irq = gpiod_to_irq(data->vbus_det_gpio);
	अगर (data->vbus_det_irq > 0) अणु
		ret = devm_request_irq(dev, data->vbus_det_irq,
				sun4i_usb_phy0_id_vbus_det_irq,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				"usb0-vbus-det", data);
		अगर (ret) अणु
			dev_err(dev, "Err requesting vbus-det-irq: %d\n", ret);
			data->vbus_det_irq = -1;
			sun4i_usb_phy_हटाओ(pdev); /* Stop detect work */
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (data->vbus_घातer_supply) अणु
		data->vbus_घातer_nb.notअगरier_call = sun4i_usb_phy0_vbus_notअगरy;
		data->vbus_घातer_nb.priority = 0;
		ret = घातer_supply_reg_notअगरier(&data->vbus_घातer_nb);
		अगर (ret) अणु
			sun4i_usb_phy_हटाओ(pdev); /* Stop detect work */
			वापस ret;
		पूर्ण
		data->vbus_घातer_nb_रेजिस्टरed = true;
	पूर्ण

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, sun4i_usb_phy_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		sun4i_usb_phy_हटाओ(pdev); /* Stop detect work */
		वापस PTR_ERR(phy_provider);
	पूर्ण

	dev_dbg(dev, "successfully loaded\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sun4i_usb_phy_cfg sun4i_a10_cfg = अणु
	.num_phys = 3,
	.type = sun4i_a10_phy,
	.disc_thresh = 3,
	.phyctl_offset = REG_PHYCTL_A10,
	.dedicated_घड़ीs = false,
	.enable_pmu_unk1 = false,
पूर्ण;

अटल स्थिर काष्ठा sun4i_usb_phy_cfg sun5i_a13_cfg = अणु
	.num_phys = 2,
	.type = sun4i_a10_phy,
	.disc_thresh = 2,
	.phyctl_offset = REG_PHYCTL_A10,
	.dedicated_घड़ीs = false,
	.enable_pmu_unk1 = false,
पूर्ण;

अटल स्थिर काष्ठा sun4i_usb_phy_cfg sun6i_a31_cfg = अणु
	.num_phys = 3,
	.type = sun6i_a31_phy,
	.disc_thresh = 3,
	.phyctl_offset = REG_PHYCTL_A10,
	.dedicated_घड़ीs = true,
	.enable_pmu_unk1 = false,
पूर्ण;

अटल स्थिर काष्ठा sun4i_usb_phy_cfg sun7i_a20_cfg = अणु
	.num_phys = 3,
	.type = sun4i_a10_phy,
	.disc_thresh = 2,
	.phyctl_offset = REG_PHYCTL_A10,
	.dedicated_घड़ीs = false,
	.enable_pmu_unk1 = false,
पूर्ण;

अटल स्थिर काष्ठा sun4i_usb_phy_cfg sun8i_a23_cfg = अणु
	.num_phys = 2,
	.type = sun6i_a31_phy,
	.disc_thresh = 3,
	.phyctl_offset = REG_PHYCTL_A10,
	.dedicated_घड़ीs = true,
	.enable_pmu_unk1 = false,
पूर्ण;

अटल स्थिर काष्ठा sun4i_usb_phy_cfg sun8i_a33_cfg = अणु
	.num_phys = 2,
	.type = sun8i_a33_phy,
	.disc_thresh = 3,
	.phyctl_offset = REG_PHYCTL_A33,
	.dedicated_घड़ीs = true,
	.enable_pmu_unk1 = false,
पूर्ण;

अटल स्थिर काष्ठा sun4i_usb_phy_cfg sun8i_a83t_cfg = अणु
	.num_phys = 3,
	.hsic_index = 2,
	.type = sun8i_a83t_phy,
	.phyctl_offset = REG_PHYCTL_A33,
	.dedicated_घड़ीs = true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_usb_phy_cfg sun8i_h3_cfg = अणु
	.num_phys = 4,
	.type = sun8i_h3_phy,
	.disc_thresh = 3,
	.phyctl_offset = REG_PHYCTL_A33,
	.dedicated_घड़ीs = true,
	.enable_pmu_unk1 = true,
	.phy0_dual_route = true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_usb_phy_cfg sun8i_r40_cfg = अणु
	.num_phys = 3,
	.type = sun8i_r40_phy,
	.disc_thresh = 3,
	.phyctl_offset = REG_PHYCTL_A33,
	.dedicated_घड़ीs = true,
	.enable_pmu_unk1 = true,
	.phy0_dual_route = true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_usb_phy_cfg sun8i_v3s_cfg = अणु
	.num_phys = 1,
	.type = sun8i_v3s_phy,
	.disc_thresh = 3,
	.phyctl_offset = REG_PHYCTL_A33,
	.dedicated_घड़ीs = true,
	.enable_pmu_unk1 = true,
	.phy0_dual_route = true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_usb_phy_cfg sun50i_a64_cfg = अणु
	.num_phys = 2,
	.type = sun50i_a64_phy,
	.disc_thresh = 3,
	.phyctl_offset = REG_PHYCTL_A33,
	.dedicated_घड़ीs = true,
	.enable_pmu_unk1 = true,
	.phy0_dual_route = true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_usb_phy_cfg sun50i_h6_cfg = अणु
	.num_phys = 4,
	.type = sun50i_h6_phy,
	.disc_thresh = 3,
	.phyctl_offset = REG_PHYCTL_A33,
	.dedicated_घड़ीs = true,
	.phy0_dual_route = true,
	.missing_phys = BIT(1) | BIT(2),
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun4i_usb_phy_of_match[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-usb-phy", .data = &sun4i_a10_cfg पूर्ण,
	अणु .compatible = "allwinner,sun5i-a13-usb-phy", .data = &sun5i_a13_cfg पूर्ण,
	अणु .compatible = "allwinner,sun6i-a31-usb-phy", .data = &sun6i_a31_cfg पूर्ण,
	अणु .compatible = "allwinner,sun7i-a20-usb-phy", .data = &sun7i_a20_cfg पूर्ण,
	अणु .compatible = "allwinner,sun8i-a23-usb-phy", .data = &sun8i_a23_cfg पूर्ण,
	अणु .compatible = "allwinner,sun8i-a33-usb-phy", .data = &sun8i_a33_cfg पूर्ण,
	अणु .compatible = "allwinner,sun8i-a83t-usb-phy", .data = &sun8i_a83t_cfg पूर्ण,
	अणु .compatible = "allwinner,sun8i-h3-usb-phy", .data = &sun8i_h3_cfg पूर्ण,
	अणु .compatible = "allwinner,sun8i-r40-usb-phy", .data = &sun8i_r40_cfg पूर्ण,
	अणु .compatible = "allwinner,sun8i-v3s-usb-phy", .data = &sun8i_v3s_cfg पूर्ण,
	अणु .compatible = "allwinner,sun50i-a64-usb-phy",
	  .data = &sun50i_a64_cfgपूर्ण,
	अणु .compatible = "allwinner,sun50i-h6-usb-phy", .data = &sun50i_h6_cfg पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_usb_phy_of_match);

अटल काष्ठा platक्रमm_driver sun4i_usb_phy_driver = अणु
	.probe	= sun4i_usb_phy_probe,
	.हटाओ	= sun4i_usb_phy_हटाओ,
	.driver = अणु
		.of_match_table	= sun4i_usb_phy_of_match,
		.name  = "sun4i-usb-phy",
	पूर्ण
पूर्ण;
module_platक्रमm_driver(sun4i_usb_phy_driver);

MODULE_DESCRIPTION("Allwinner sun4i USB phy driver");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL v2");
