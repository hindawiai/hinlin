<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016-2019, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>

#समावेश <soc/tegra/fuse.h>

#समावेश "xusb.h"

/* FUSE USB_CALIB रेजिस्टरs */
#घोषणा HS_CURR_LEVEL_PADX_SHIFT(x)	((x) ? (11 + (x - 1) * 6) : 0)
#घोषणा HS_CURR_LEVEL_PAD_MASK		0x3f
#घोषणा HS_TERM_RANGE_ADJ_SHIFT		7
#घोषणा HS_TERM_RANGE_ADJ_MASK		0xf
#घोषणा HS_SQUELCH_SHIFT		29
#घोषणा HS_SQUELCH_MASK			0x7

#घोषणा RPD_CTRL_SHIFT			0
#घोषणा RPD_CTRL_MASK			0x1f

/* XUSB PADCTL रेजिस्टरs */
#घोषणा XUSB_PADCTL_USB2_PAD_MUX	0x4
#घोषणा  USB2_PORT_SHIFT(x)		((x) * 2)
#घोषणा  USB2_PORT_MASK			0x3
#घोषणा   PORT_XUSB			1
#घोषणा  HSIC_PORT_SHIFT(x)		((x) + 20)
#घोषणा  HSIC_PORT_MASK			0x1
#घोषणा   PORT_HSIC			0

#घोषणा XUSB_PADCTL_USB2_PORT_CAP	0x8
#घोषणा XUSB_PADCTL_SS_PORT_CAP		0xc
#घोषणा  PORTX_CAP_SHIFT(x)		((x) * 4)
#घोषणा  PORT_CAP_MASK			0x3
#घोषणा   PORT_CAP_DISABLED		0x0
#घोषणा   PORT_CAP_HOST			0x1
#घोषणा   PORT_CAP_DEVICE		0x2
#घोषणा   PORT_CAP_OTG			0x3

#घोषणा XUSB_PADCTL_ELPG_PROGRAM		0x20
#घोषणा  USB2_PORT_WAKE_INTERRUPT_ENABLE(x)		BIT(x)
#घोषणा  USB2_PORT_WAKEUP_EVENT(x)			BIT((x) +  7)
#घोषणा  SS_PORT_WAKE_INTERRUPT_ENABLE(x)		BIT((x) + 14)
#घोषणा  SS_PORT_WAKEUP_EVENT(x)			BIT((x) + 21)
#घोषणा  USB2_HSIC_PORT_WAKE_INTERRUPT_ENABLE(x)	BIT((x) + 28)
#घोषणा  USB2_HSIC_PORT_WAKEUP_EVENT(x)			BIT((x) + 30)
#घोषणा  ALL_WAKE_EVENTS						\
	(USB2_PORT_WAKEUP_EVENT(0) | USB2_PORT_WAKEUP_EVENT(1) |	\
	USB2_PORT_WAKEUP_EVENT(2) | SS_PORT_WAKEUP_EVENT(0) |		\
	SS_PORT_WAKEUP_EVENT(1) | SS_PORT_WAKEUP_EVENT(2) |		\
	USB2_HSIC_PORT_WAKEUP_EVENT(0))

#घोषणा XUSB_PADCTL_ELPG_PROGRAM_1		0x24
#घोषणा  SSPX_ELPG_CLAMP_EN(x)			BIT(0 + (x) * 3)
#घोषणा  SSPX_ELPG_CLAMP_EN_EARLY(x)		BIT(1 + (x) * 3)
#घोषणा  SSPX_ELPG_VCORE_DOWN(x)		BIT(2 + (x) * 3)
#घोषणा XUSB_PADCTL_SS_PORT_CFG			0x2c
#घोषणा   PORTX_SPEED_SUPPORT_SHIFT(x)		((x) * 4)
#घोषणा   PORTX_SPEED_SUPPORT_MASK		(0x3)
#घोषणा     PORT_SPEED_SUPPORT_GEN1		(0x0)

#घोषणा XUSB_PADCTL_USB2_OTG_PADX_CTL0(x)	(0x88 + (x) * 0x40)
#घोषणा  HS_CURR_LEVEL(x)			((x) & 0x3f)
#घोषणा  TERM_SEL				BIT(25)
#घोषणा  USB2_OTG_PD				BIT(26)
#घोषणा  USB2_OTG_PD2				BIT(27)
#घोषणा  USB2_OTG_PD2_OVRD_EN			BIT(28)
#घोषणा  USB2_OTG_PD_ZI				BIT(29)

#घोषणा XUSB_PADCTL_USB2_OTG_PADX_CTL1(x)	(0x8c + (x) * 0x40)
#घोषणा  USB2_OTG_PD_DR				BIT(2)
#घोषणा  TERM_RANGE_ADJ(x)			(((x) & 0xf) << 3)
#घोषणा  RPD_CTRL(x)				(((x) & 0x1f) << 26)

#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL0		0x284
#घोषणा  BIAS_PAD_PD				BIT(11)
#घोषणा  HS_SQUELCH_LEVEL(x)			(((x) & 0x7) << 0)

#घोषणा XUSB_PADCTL_USB2_BIAS_PAD_CTL1		0x288
#घोषणा  USB2_TRK_START_TIMER(x)		(((x) & 0x7f) << 12)
#घोषणा  USB2_TRK_DONE_RESET_TIMER(x)		(((x) & 0x7f) << 19)
#घोषणा  USB2_PD_TRK				BIT(26)

#घोषणा XUSB_PADCTL_HSIC_PADX_CTL0(x)		(0x300 + (x) * 0x20)
#घोषणा  HSIC_PD_TX_DATA0			BIT(1)
#घोषणा  HSIC_PD_TX_STROBE			BIT(3)
#घोषणा  HSIC_PD_RX_DATA0			BIT(4)
#घोषणा  HSIC_PD_RX_STROBE			BIT(6)
#घोषणा  HSIC_PD_ZI_DATA0			BIT(7)
#घोषणा  HSIC_PD_ZI_STROBE			BIT(9)
#घोषणा  HSIC_RPD_DATA0				BIT(13)
#घोषणा  HSIC_RPD_STROBE			BIT(15)
#घोषणा  HSIC_RPU_DATA0				BIT(16)
#घोषणा  HSIC_RPU_STROBE			BIT(18)

#घोषणा XUSB_PADCTL_HSIC_PAD_TRK_CTL0		0x340
#घोषणा  HSIC_TRK_START_TIMER(x)		(((x) & 0x7f) << 5)
#घोषणा  HSIC_TRK_DONE_RESET_TIMER(x)		(((x) & 0x7f) << 12)
#घोषणा  HSIC_PD_TRK				BIT(19)

#घोषणा USB2_VBUS_ID				0x360
#घोषणा  VBUS_OVERRIDE				BIT(14)
#घोषणा  ID_OVERRIDE(x)				(((x) & 0xf) << 18)
#घोषणा  ID_OVERRIDE_FLOATING			ID_OVERRIDE(8)
#घोषणा  ID_OVERRIDE_GROUNDED			ID_OVERRIDE(0)

#घोषणा TEGRA186_LANE(_name, _offset, _shअगरt, _mask, _type)		\
	अणु								\
		.name = _name,						\
		.offset = _offset,					\
		.shअगरt = _shअगरt,					\
		.mask = _mask,						\
		.num_funcs = ARRAY_SIZE(tegra186_##_type##_functions),	\
		.funcs = tegra186_##_type##_functions,			\
	पूर्ण

काष्ठा tegra_xusb_fuse_calibration अणु
	u32 *hs_curr_level;
	u32 hs_squelch;
	u32 hs_term_range_adj;
	u32 rpd_ctrl;
पूर्ण;

काष्ठा tegra186_xusb_padctl अणु
	काष्ठा tegra_xusb_padctl base;

	काष्ठा tegra_xusb_fuse_calibration calib;

	/* UTMI bias and tracking */
	काष्ठा clk *usb2_trk_clk;
	अचिन्हित पूर्णांक bias_pad_enable;
पूर्ण;

अटल अंतरभूत काष्ठा tegra186_xusb_padctl *
to_tegra186_xusb_padctl(काष्ठा tegra_xusb_padctl *padctl)
अणु
	वापस container_of(padctl, काष्ठा tegra186_xusb_padctl, base);
पूर्ण

/* USB 2.0 UTMI PHY support */
अटल काष्ठा tegra_xusb_lane *
tegra186_usb2_lane_probe(काष्ठा tegra_xusb_pad *pad, काष्ठा device_node *np,
			 अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_usb2_lane *usb2;
	पूर्णांक err;

	usb2 = kzalloc(माप(*usb2), GFP_KERNEL);
	अगर (!usb2)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&usb2->base.list);
	usb2->base.soc = &pad->soc->lanes[index];
	usb2->base.index = index;
	usb2->base.pad = pad;
	usb2->base.np = np;

	err = tegra_xusb_lane_parse_dt(&usb2->base, np);
	अगर (err < 0) अणु
		kमुक्त(usb2);
		वापस ERR_PTR(err);
	पूर्ण

	वापस &usb2->base;
पूर्ण

अटल व्योम tegra186_usb2_lane_हटाओ(काष्ठा tegra_xusb_lane *lane)
अणु
	काष्ठा tegra_xusb_usb2_lane *usb2 = to_usb2_lane(lane);

	kमुक्त(usb2);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_lane_ops tegra186_usb2_lane_ops = अणु
	.probe = tegra186_usb2_lane_probe,
	.हटाओ = tegra186_usb2_lane_हटाओ,
पूर्ण;

अटल व्योम tegra186_uपंचांगi_bias_pad_घातer_on(काष्ठा tegra_xusb_padctl *padctl)
अणु
	काष्ठा tegra186_xusb_padctl *priv = to_tegra186_xusb_padctl(padctl);
	काष्ठा device *dev = padctl->dev;
	u32 value;
	पूर्णांक err;

	mutex_lock(&padctl->lock);

	अगर (priv->bias_pad_enable++ > 0) अणु
		mutex_unlock(&padctl->lock);
		वापस;
	पूर्ण

	err = clk_prepare_enable(priv->usb2_trk_clk);
	अगर (err < 0)
		dev_warn(dev, "failed to enable USB2 trk clock: %d\n", err);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL1);
	value &= ~USB2_TRK_START_TIMER(~0);
	value |= USB2_TRK_START_TIMER(0x1e);
	value &= ~USB2_TRK_DONE_RESET_TIMER(~0);
	value |= USB2_TRK_DONE_RESET_TIMER(0xa);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);
	value &= ~BIAS_PAD_PD;
	value &= ~HS_SQUELCH_LEVEL(~0);
	value |= HS_SQUELCH_LEVEL(priv->calib.hs_squelch);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);

	udelay(1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL1);
	value &= ~USB2_PD_TRK;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL1);

	mutex_unlock(&padctl->lock);
पूर्ण

अटल व्योम tegra186_uपंचांगi_bias_pad_घातer_off(काष्ठा tegra_xusb_padctl *padctl)
अणु
	काष्ठा tegra186_xusb_padctl *priv = to_tegra186_xusb_padctl(padctl);
	u32 value;

	mutex_lock(&padctl->lock);

	अगर (WARN_ON(priv->bias_pad_enable == 0)) अणु
		mutex_unlock(&padctl->lock);
		वापस;
	पूर्ण

	अगर (--priv->bias_pad_enable > 0) अणु
		mutex_unlock(&padctl->lock);
		वापस;
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL1);
	value |= USB2_PD_TRK;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL1);

	clk_disable_unprepare(priv->usb2_trk_clk);

	mutex_unlock(&padctl->lock);
पूर्ण

अटल व्योम tegra_phy_xusb_uपंचांगi_pad_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	काष्ठा tegra_xusb_usb2_port *port;
	काष्ठा device *dev = padctl->dev;
	अचिन्हित पूर्णांक index = lane->index;
	u32 value;

	अगर (!phy)
		वापस;

	port = tegra_xusb_find_usb2_port(padctl, index);
	अगर (!port) अणु
		dev_err(dev, "no port found for USB2 lane %u\n", index);
		वापस;
	पूर्ण

	tegra186_uपंचांगi_bias_pad_घातer_on(padctl);

	udelay(2);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_OTG_PADX_CTL0(index));
	value &= ~USB2_OTG_PD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_OTG_PADX_CTL0(index));

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_OTG_PADX_CTL1(index));
	value &= ~USB2_OTG_PD_DR;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_OTG_PADX_CTL1(index));
पूर्ण

अटल व्योम tegra_phy_xusb_uपंचांगi_pad_घातer_करोwn(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	अचिन्हित पूर्णांक index = lane->index;
	u32 value;

	अगर (!phy)
		वापस;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_OTG_PADX_CTL0(index));
	value |= USB2_OTG_PD;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_OTG_PADX_CTL0(index));

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_OTG_PADX_CTL1(index));
	value |= USB2_OTG_PD_DR;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_OTG_PADX_CTL1(index));

	udelay(2);

	tegra186_uपंचांगi_bias_pad_घातer_off(padctl);
पूर्ण

अटल पूर्णांक tegra186_xusb_padctl_vbus_override(काष्ठा tegra_xusb_padctl *padctl,
					       bool status)
अणु
	u32 value;

	dev_dbg(padctl->dev, "%s vbus override\n", status ? "set" : "clear");

	value = padctl_पढ़ोl(padctl, USB2_VBUS_ID);

	अगर (status) अणु
		value |= VBUS_OVERRIDE;
		value &= ~ID_OVERRIDE(~0);
		value |= ID_OVERRIDE_FLOATING;
	पूर्ण अन्यथा अणु
		value &= ~VBUS_OVERRIDE;
	पूर्ण

	padctl_ग_लिखोl(padctl, value, USB2_VBUS_ID);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_xusb_padctl_id_override(काष्ठा tegra_xusb_padctl *padctl,
					    bool status)
अणु
	u32 value;

	dev_dbg(padctl->dev, "%s id override\n", status ? "set" : "clear");

	value = padctl_पढ़ोl(padctl, USB2_VBUS_ID);

	अगर (status) अणु
		अगर (value & VBUS_OVERRIDE) अणु
			value &= ~VBUS_OVERRIDE;
			padctl_ग_लिखोl(padctl, value, USB2_VBUS_ID);
			usleep_range(1000, 2000);

			value = padctl_पढ़ोl(padctl, USB2_VBUS_ID);
		पूर्ण

		value &= ~ID_OVERRIDE(~0);
		value |= ID_OVERRIDE_GROUNDED;
	पूर्ण अन्यथा अणु
		value &= ~ID_OVERRIDE(~0);
		value |= ID_OVERRIDE_FLOATING;
	पूर्ण

	padctl_ग_लिखोl(padctl, value, USB2_VBUS_ID);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_uपंचांगi_phy_set_mode(काष्ठा phy *phy, क्रमागत phy_mode mode,
				      पूर्णांक submode)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	काष्ठा tegra_xusb_usb2_port *port = tegra_xusb_find_usb2_port(padctl,
								lane->index);
	पूर्णांक err = 0;

	mutex_lock(&padctl->lock);

	dev_dbg(&port->base.dev, "%s: mode %d", __func__, mode);

	अगर (mode == PHY_MODE_USB_OTG) अणु
		अगर (submode == USB_ROLE_HOST) अणु
			tegra186_xusb_padctl_id_override(padctl, true);

			err = regulator_enable(port->supply);
		पूर्ण अन्यथा अगर (submode == USB_ROLE_DEVICE) अणु
			tegra186_xusb_padctl_vbus_override(padctl, true);
		पूर्ण अन्यथा अगर (submode == USB_ROLE_NONE) अणु
			/*
			 * When port is peripheral only or role transitions to
			 * USB_ROLE_NONE from USB_ROLE_DEVICE, regulator is not
			 * enabled.
			 */
			अगर (regulator_is_enabled(port->supply))
				regulator_disable(port->supply);

			tegra186_xusb_padctl_id_override(padctl, false);
			tegra186_xusb_padctl_vbus_override(padctl, false);
		पूर्ण
	पूर्ण

	mutex_unlock(&padctl->lock);

	वापस err;
पूर्ण

अटल पूर्णांक tegra186_uपंचांगi_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_usb2_lane *usb2 = to_usb2_lane(lane);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	काष्ठा tegra186_xusb_padctl *priv = to_tegra186_xusb_padctl(padctl);
	काष्ठा tegra_xusb_usb2_port *port;
	अचिन्हित पूर्णांक index = lane->index;
	काष्ठा device *dev = padctl->dev;
	u32 value;

	port = tegra_xusb_find_usb2_port(padctl, index);
	अगर (!port) अणु
		dev_err(dev, "no port found for USB2 lane %u\n", index);
		वापस -ENODEV;
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_PAD_MUX);
	value &= ~(USB2_PORT_MASK << USB2_PORT_SHIFT(index));
	value |= (PORT_XUSB << USB2_PORT_SHIFT(index));
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_PAD_MUX);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_PORT_CAP);
	value &= ~(PORT_CAP_MASK << PORTX_CAP_SHIFT(index));

	अगर (port->mode == USB_DR_MODE_UNKNOWN)
		value |= (PORT_CAP_DISABLED << PORTX_CAP_SHIFT(index));
	अन्यथा अगर (port->mode == USB_DR_MODE_PERIPHERAL)
		value |= (PORT_CAP_DEVICE << PORTX_CAP_SHIFT(index));
	अन्यथा अगर (port->mode == USB_DR_MODE_HOST)
		value |= (PORT_CAP_HOST << PORTX_CAP_SHIFT(index));
	अन्यथा अगर (port->mode == USB_DR_MODE_OTG)
		value |= (PORT_CAP_OTG << PORTX_CAP_SHIFT(index));

	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_PORT_CAP);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_OTG_PADX_CTL0(index));
	value &= ~USB2_OTG_PD_ZI;
	value |= TERM_SEL;
	value &= ~HS_CURR_LEVEL(~0);

	अगर (usb2->hs_curr_level_offset) अणु
		पूर्णांक hs_current_level;

		hs_current_level = (पूर्णांक)priv->calib.hs_curr_level[index] +
						usb2->hs_curr_level_offset;

		अगर (hs_current_level < 0)
			hs_current_level = 0;
		अगर (hs_current_level > 0x3f)
			hs_current_level = 0x3f;

		value |= HS_CURR_LEVEL(hs_current_level);
	पूर्ण अन्यथा अणु
		value |= HS_CURR_LEVEL(priv->calib.hs_curr_level[index]);
	पूर्ण

	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_OTG_PADX_CTL0(index));

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_USB2_OTG_PADX_CTL1(index));
	value &= ~TERM_RANGE_ADJ(~0);
	value |= TERM_RANGE_ADJ(priv->calib.hs_term_range_adj);
	value &= ~RPD_CTRL(~0);
	value |= RPD_CTRL(priv->calib.rpd_ctrl);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_USB2_OTG_PADX_CTL1(index));

	/* TODO: pad घातer saving */
	tegra_phy_xusb_uपंचांगi_pad_घातer_on(phy);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_uपंचांगi_phy_घातer_off(काष्ठा phy *phy)
अणु
	/* TODO: pad घातer saving */
	tegra_phy_xusb_uपंचांगi_pad_घातer_करोwn(phy);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_uपंचांगi_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	काष्ठा tegra_xusb_usb2_port *port;
	अचिन्हित पूर्णांक index = lane->index;
	काष्ठा device *dev = padctl->dev;
	पूर्णांक err;

	port = tegra_xusb_find_usb2_port(padctl, index);
	अगर (!port) अणु
		dev_err(dev, "no port found for USB2 lane %u\n", index);
		वापस -ENODEV;
	पूर्ण

	अगर (port->supply && port->mode == USB_DR_MODE_HOST) अणु
		err = regulator_enable(port->supply);
		अगर (err) अणु
			dev_err(dev, "failed to enable port %u VBUS: %d\n",
				index, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_uपंचांगi_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	काष्ठा tegra_xusb_usb2_port *port;
	अचिन्हित पूर्णांक index = lane->index;
	काष्ठा device *dev = padctl->dev;
	पूर्णांक err;

	port = tegra_xusb_find_usb2_port(padctl, index);
	अगर (!port) अणु
		dev_err(dev, "no port found for USB2 lane %u\n", index);
		वापस -ENODEV;
	पूर्ण

	अगर (port->supply && port->mode == USB_DR_MODE_HOST) अणु
		err = regulator_disable(port->supply);
		अगर (err) अणु
			dev_err(dev, "failed to disable port %u VBUS: %d\n",
				index, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops uपंचांगi_phy_ops = अणु
	.init = tegra186_uपंचांगi_phy_init,
	.निकास = tegra186_uपंचांगi_phy_निकास,
	.घातer_on = tegra186_uपंचांगi_phy_घातer_on,
	.घातer_off = tegra186_uपंचांगi_phy_घातer_off,
	.set_mode = tegra186_uपंचांगi_phy_set_mode,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा tegra_xusb_pad *
tegra186_usb2_pad_probe(काष्ठा tegra_xusb_padctl *padctl,
			स्थिर काष्ठा tegra_xusb_pad_soc *soc,
			काष्ठा device_node *np)
अणु
	काष्ठा tegra186_xusb_padctl *priv = to_tegra186_xusb_padctl(padctl);
	काष्ठा tegra_xusb_usb2_pad *usb2;
	काष्ठा tegra_xusb_pad *pad;
	पूर्णांक err;

	usb2 = kzalloc(माप(*usb2), GFP_KERNEL);
	अगर (!usb2)
		वापस ERR_PTR(-ENOMEM);

	pad = &usb2->base;
	pad->ops = &tegra186_usb2_lane_ops;
	pad->soc = soc;

	err = tegra_xusb_pad_init(pad, padctl, np);
	अगर (err < 0) अणु
		kमुक्त(usb2);
		जाओ out;
	पूर्ण

	priv->usb2_trk_clk = devm_clk_get(&pad->dev, "trk");
	अगर (IS_ERR(priv->usb2_trk_clk)) अणु
		err = PTR_ERR(priv->usb2_trk_clk);
		dev_dbg(&pad->dev, "failed to get usb2 trk clock: %d\n", err);
		जाओ unरेजिस्टर;
	पूर्ण

	err = tegra_xusb_pad_रेजिस्टर(pad, &uपंचांगi_phy_ops);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	dev_set_drvdata(&pad->dev, pad);

	वापस pad;

unरेजिस्टर:
	device_unरेजिस्टर(&pad->dev);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tegra186_usb2_pad_हटाओ(काष्ठा tegra_xusb_pad *pad)
अणु
	काष्ठा tegra_xusb_usb2_pad *usb2 = to_usb2_pad(pad);

	kमुक्त(usb2);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_pad_ops tegra186_usb2_pad_ops = अणु
	.probe = tegra186_usb2_pad_probe,
	.हटाओ = tegra186_usb2_pad_हटाओ,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra186_usb2_functions[] = अणु
	"xusb",
पूर्ण;

अटल पूर्णांक tegra186_usb2_port_enable(काष्ठा tegra_xusb_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम tegra186_usb2_port_disable(काष्ठा tegra_xusb_port *port)
अणु
पूर्ण

अटल काष्ठा tegra_xusb_lane *
tegra186_usb2_port_map(काष्ठा tegra_xusb_port *port)
अणु
	वापस tegra_xusb_find_lane(port->padctl, "usb2", port->index);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_port_ops tegra186_usb2_port_ops = अणु
	.release = tegra_xusb_usb2_port_release,
	.हटाओ = tegra_xusb_usb2_port_हटाओ,
	.enable = tegra186_usb2_port_enable,
	.disable = tegra186_usb2_port_disable,
	.map = tegra186_usb2_port_map,
पूर्ण;

/* SuperSpeed PHY support */
अटल काष्ठा tegra_xusb_lane *
tegra186_usb3_lane_probe(काष्ठा tegra_xusb_pad *pad, काष्ठा device_node *np,
			 अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_usb3_lane *usb3;
	पूर्णांक err;

	usb3 = kzalloc(माप(*usb3), GFP_KERNEL);
	अगर (!usb3)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&usb3->base.list);
	usb3->base.soc = &pad->soc->lanes[index];
	usb3->base.index = index;
	usb3->base.pad = pad;
	usb3->base.np = np;

	err = tegra_xusb_lane_parse_dt(&usb3->base, np);
	अगर (err < 0) अणु
		kमुक्त(usb3);
		वापस ERR_PTR(err);
	पूर्ण

	वापस &usb3->base;
पूर्ण

अटल व्योम tegra186_usb3_lane_हटाओ(काष्ठा tegra_xusb_lane *lane)
अणु
	काष्ठा tegra_xusb_usb3_lane *usb3 = to_usb3_lane(lane);

	kमुक्त(usb3);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_lane_ops tegra186_usb3_lane_ops = अणु
	.probe = tegra186_usb3_lane_probe,
	.हटाओ = tegra186_usb3_lane_हटाओ,
पूर्ण;
अटल पूर्णांक tegra186_usb3_port_enable(काष्ठा tegra_xusb_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम tegra186_usb3_port_disable(काष्ठा tegra_xusb_port *port)
अणु
पूर्ण

अटल काष्ठा tegra_xusb_lane *
tegra186_usb3_port_map(काष्ठा tegra_xusb_port *port)
अणु
	वापस tegra_xusb_find_lane(port->padctl, "usb3", port->index);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_port_ops tegra186_usb3_port_ops = अणु
	.release = tegra_xusb_usb3_port_release,
	.हटाओ = tegra_xusb_usb3_port_हटाओ,
	.enable = tegra186_usb3_port_enable,
	.disable = tegra186_usb3_port_disable,
	.map = tegra186_usb3_port_map,
पूर्ण;

अटल पूर्णांक tegra186_usb3_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	काष्ठा tegra_xusb_usb3_port *port;
	काष्ठा tegra_xusb_usb2_port *usb2;
	अचिन्हित पूर्णांक index = lane->index;
	काष्ठा device *dev = padctl->dev;
	u32 value;

	port = tegra_xusb_find_usb3_port(padctl, index);
	अगर (!port) अणु
		dev_err(dev, "no port found for USB3 lane %u\n", index);
		वापस -ENODEV;
	पूर्ण

	usb2 = tegra_xusb_find_usb2_port(padctl, port->port);
	अगर (!usb2) अणु
		dev_err(dev, "no companion port found for USB3 lane %u\n",
			index);
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&padctl->lock);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_SS_PORT_CAP);
	value &= ~(PORT_CAP_MASK << PORTX_CAP_SHIFT(index));

	अगर (usb2->mode == USB_DR_MODE_UNKNOWN)
		value |= (PORT_CAP_DISABLED << PORTX_CAP_SHIFT(index));
	अन्यथा अगर (usb2->mode == USB_DR_MODE_PERIPHERAL)
		value |= (PORT_CAP_DEVICE << PORTX_CAP_SHIFT(index));
	अन्यथा अगर (usb2->mode == USB_DR_MODE_HOST)
		value |= (PORT_CAP_HOST << PORTX_CAP_SHIFT(index));
	अन्यथा अगर (usb2->mode == USB_DR_MODE_OTG)
		value |= (PORT_CAP_OTG << PORTX_CAP_SHIFT(index));

	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_SS_PORT_CAP);

	अगर (padctl->soc->supports_gen2 && port->disable_gen2) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_SS_PORT_CFG);
		value &= ~(PORTX_SPEED_SUPPORT_MASK <<
			PORTX_SPEED_SUPPORT_SHIFT(index));
		value |= (PORT_SPEED_SUPPORT_GEN1 <<
			PORTX_SPEED_SUPPORT_SHIFT(index));
		padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_SS_PORT_CFG);
	पूर्ण

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM_1);
	value &= ~SSPX_ELPG_VCORE_DOWN(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM_1);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM_1);
	value &= ~SSPX_ELPG_CLAMP_EN_EARLY(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM_1);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM_1);
	value &= ~SSPX_ELPG_CLAMP_EN(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM_1);

	mutex_unlock(&padctl->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_usb3_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	काष्ठा tegra_xusb_usb3_port *port;
	अचिन्हित पूर्णांक index = lane->index;
	काष्ठा device *dev = padctl->dev;
	u32 value;

	port = tegra_xusb_find_usb3_port(padctl, index);
	अगर (!port) अणु
		dev_err(dev, "no port found for USB3 lane %u\n", index);
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&padctl->lock);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM_1);
	value |= SSPX_ELPG_CLAMP_EN_EARLY(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM_1);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM_1);
	value |= SSPX_ELPG_CLAMP_EN(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM_1);

	usleep_range(250, 350);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM_1);
	value |= SSPX_ELPG_VCORE_DOWN(index);
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM_1);

	mutex_unlock(&padctl->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_usb3_phy_init(काष्ठा phy *phy)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_usb3_phy_निकास(काष्ठा phy *phy)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops usb3_phy_ops = अणु
	.init = tegra186_usb3_phy_init,
	.निकास = tegra186_usb3_phy_निकास,
	.घातer_on = tegra186_usb3_phy_घातer_on,
	.घातer_off = tegra186_usb3_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा tegra_xusb_pad *
tegra186_usb3_pad_probe(काष्ठा tegra_xusb_padctl *padctl,
			स्थिर काष्ठा tegra_xusb_pad_soc *soc,
			काष्ठा device_node *np)
अणु
	काष्ठा tegra_xusb_usb3_pad *usb3;
	काष्ठा tegra_xusb_pad *pad;
	पूर्णांक err;

	usb3 = kzalloc(माप(*usb3), GFP_KERNEL);
	अगर (!usb3)
		वापस ERR_PTR(-ENOMEM);

	pad = &usb3->base;
	pad->ops = &tegra186_usb3_lane_ops;
	pad->soc = soc;

	err = tegra_xusb_pad_init(pad, padctl, np);
	अगर (err < 0) अणु
		kमुक्त(usb3);
		जाओ out;
	पूर्ण

	err = tegra_xusb_pad_रेजिस्टर(pad, &usb3_phy_ops);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	dev_set_drvdata(&pad->dev, pad);

	वापस pad;

unरेजिस्टर:
	device_unरेजिस्टर(&pad->dev);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tegra186_usb3_pad_हटाओ(काष्ठा tegra_xusb_pad *pad)
अणु
	काष्ठा tegra_xusb_usb2_pad *usb2 = to_usb2_pad(pad);

	kमुक्त(usb2);
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_pad_ops tegra186_usb3_pad_ops = अणु
	.probe = tegra186_usb3_pad_probe,
	.हटाओ = tegra186_usb3_pad_हटाओ,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra186_usb3_functions[] = अणु
	"xusb",
पूर्ण;

अटल पूर्णांक
tegra186_xusb_पढ़ो_fuse_calibration(काष्ठा tegra186_xusb_padctl *padctl)
अणु
	काष्ठा device *dev = padctl->base.dev;
	अचिन्हित पूर्णांक i, count;
	u32 value, *level;
	पूर्णांक err;

	count = padctl->base.soc->ports.usb2.count;

	level = devm_kसुस्मृति(dev, count, माप(u32), GFP_KERNEL);
	अगर (!level)
		वापस -ENOMEM;

	err = tegra_fuse_पढ़ोl(TEGRA_FUSE_SKU_CALIB_0, &value);
	अगर (err) अणु
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "failed to read calibration fuse: %d\n",
				err);
		वापस err;
	पूर्ण

	dev_dbg(dev, "FUSE_USB_CALIB_0 %#x\n", value);

	क्रम (i = 0; i < count; i++)
		level[i] = (value >> HS_CURR_LEVEL_PADX_SHIFT(i)) &
				HS_CURR_LEVEL_PAD_MASK;

	padctl->calib.hs_curr_level = level;

	padctl->calib.hs_squelch = (value >> HS_SQUELCH_SHIFT) &
					HS_SQUELCH_MASK;
	padctl->calib.hs_term_range_adj = (value >> HS_TERM_RANGE_ADJ_SHIFT) &
						HS_TERM_RANGE_ADJ_MASK;

	err = tegra_fuse_पढ़ोl(TEGRA_FUSE_USB_CALIB_EXT_0, &value);
	अगर (err) अणु
		dev_err(dev, "failed to read calibration fuse: %d\n", err);
		वापस err;
	पूर्ण

	dev_dbg(dev, "FUSE_USB_CALIB_EXT_0 %#x\n", value);

	padctl->calib.rpd_ctrl = (value >> RPD_CTRL_SHIFT) & RPD_CTRL_MASK;

	वापस 0;
पूर्ण

अटल काष्ठा tegra_xusb_padctl *
tegra186_xusb_padctl_probe(काष्ठा device *dev,
			   स्थिर काष्ठा tegra_xusb_padctl_soc *soc)
अणु
	काष्ठा tegra186_xusb_padctl *priv;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस ERR_PTR(-ENOMEM);

	priv->base.dev = dev;
	priv->base.soc = soc;

	err = tegra186_xusb_पढ़ो_fuse_calibration(priv);
	अगर (err < 0)
		वापस ERR_PTR(err);

	वापस &priv->base;
पूर्ण

अटल व्योम tegra186_xusb_padctl_हटाओ(काष्ठा tegra_xusb_padctl *padctl)
अणु
पूर्ण

अटल स्थिर काष्ठा tegra_xusb_padctl_ops tegra186_xusb_padctl_ops = अणु
	.probe = tegra186_xusb_padctl_probe,
	.हटाओ = tegra186_xusb_padctl_हटाओ,
	.vbus_override = tegra186_xusb_padctl_vbus_override,
पूर्ण;

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_186_SOC)
अटल स्थिर अक्षर * स्थिर tegra186_xusb_padctl_supply_names[] = अणु
	"avdd-pll-erefeut",
	"avdd-usb",
	"vclamp-usb",
	"vddio-hsic",
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_lane_soc tegra186_usb2_lanes[] = अणु
	TEGRA186_LANE("usb2-0", 0,  0, 0, usb2),
	TEGRA186_LANE("usb2-1", 0,  0, 0, usb2),
	TEGRA186_LANE("usb2-2", 0,  0, 0, usb2),
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc tegra186_usb2_pad = अणु
	.name = "usb2",
	.num_lanes = ARRAY_SIZE(tegra186_usb2_lanes),
	.lanes = tegra186_usb2_lanes,
	.ops = &tegra186_usb2_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_lane_soc tegra186_usb3_lanes[] = अणु
	TEGRA186_LANE("usb3-0", 0,  0, 0, usb3),
	TEGRA186_LANE("usb3-1", 0,  0, 0, usb3),
	TEGRA186_LANE("usb3-2", 0,  0, 0, usb3),
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc tegra186_usb3_pad = अणु
	.name = "usb3",
	.num_lanes = ARRAY_SIZE(tegra186_usb3_lanes),
	.lanes = tegra186_usb3_lanes,
	.ops = &tegra186_usb3_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc * स्थिर tegra186_pads[] = अणु
	&tegra186_usb2_pad,
	&tegra186_usb3_pad,
#अगर 0 /* TODO implement */
	&tegra186_hsic_pad,
#पूर्ण_अगर
पूर्ण;

स्थिर काष्ठा tegra_xusb_padctl_soc tegra186_xusb_padctl_soc = अणु
	.num_pads = ARRAY_SIZE(tegra186_pads),
	.pads = tegra186_pads,
	.ports = अणु
		.usb2 = अणु
			.ops = &tegra186_usb2_port_ops,
			.count = 3,
		पूर्ण,
#अगर 0 /* TODO implement */
		.hsic = अणु
			.ops = &tegra186_hsic_port_ops,
			.count = 1,
		पूर्ण,
#पूर्ण_अगर
		.usb3 = अणु
			.ops = &tegra186_usb3_port_ops,
			.count = 3,
		पूर्ण,
	पूर्ण,
	.ops = &tegra186_xusb_padctl_ops,
	.supply_names = tegra186_xusb_padctl_supply_names,
	.num_supplies = ARRAY_SIZE(tegra186_xusb_padctl_supply_names),
पूर्ण;
EXPORT_SYMBOL_GPL(tegra186_xusb_padctl_soc);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_194_SOC)
अटल स्थिर अक्षर * स्थिर tegra194_xusb_padctl_supply_names[] = अणु
	"avdd-usb",
	"vclamp-usb",
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_lane_soc tegra194_usb2_lanes[] = अणु
	TEGRA186_LANE("usb2-0", 0,  0, 0, usb2),
	TEGRA186_LANE("usb2-1", 0,  0, 0, usb2),
	TEGRA186_LANE("usb2-2", 0,  0, 0, usb2),
	TEGRA186_LANE("usb2-3", 0,  0, 0, usb2),
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc tegra194_usb2_pad = अणु
	.name = "usb2",
	.num_lanes = ARRAY_SIZE(tegra194_usb2_lanes),
	.lanes = tegra194_usb2_lanes,
	.ops = &tegra186_usb2_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_lane_soc tegra194_usb3_lanes[] = अणु
	TEGRA186_LANE("usb3-0", 0,  0, 0, usb3),
	TEGRA186_LANE("usb3-1", 0,  0, 0, usb3),
	TEGRA186_LANE("usb3-2", 0,  0, 0, usb3),
	TEGRA186_LANE("usb3-3", 0,  0, 0, usb3),
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc tegra194_usb3_pad = अणु
	.name = "usb3",
	.num_lanes = ARRAY_SIZE(tegra194_usb3_lanes),
	.lanes = tegra194_usb3_lanes,
	.ops = &tegra186_usb3_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_pad_soc * स्थिर tegra194_pads[] = अणु
	&tegra194_usb2_pad,
	&tegra194_usb3_pad,
पूर्ण;

स्थिर काष्ठा tegra_xusb_padctl_soc tegra194_xusb_padctl_soc = अणु
	.num_pads = ARRAY_SIZE(tegra194_pads),
	.pads = tegra194_pads,
	.ports = अणु
		.usb2 = अणु
			.ops = &tegra186_usb2_port_ops,
			.count = 4,
		पूर्ण,
		.usb3 = अणु
			.ops = &tegra186_usb3_port_ops,
			.count = 4,
		पूर्ण,
	पूर्ण,
	.ops = &tegra186_xusb_padctl_ops,
	.supply_names = tegra194_xusb_padctl_supply_names,
	.num_supplies = ARRAY_SIZE(tegra194_xusb_padctl_supply_names),
	.supports_gen2 = true,
पूर्ण;
EXPORT_SYMBOL_GPL(tegra194_xusb_padctl_soc);
#पूर्ण_अगर

MODULE_AUTHOR("JC Kuo <jckuo@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA Tegra186 XUSB Pad Controller driver");
MODULE_LICENSE("GPL v2");
