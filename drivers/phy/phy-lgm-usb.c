<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel LGM USB PHY driver
 *
 * Copyright (C) 2020 Intel Corporation.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/usb/phy.h>
#समावेश <linux/workqueue.h>

#घोषणा CTRL1_OFFSET		0x14
#घोषणा SRAM_EXT_LD_DONE	BIT(25)
#घोषणा SRAM_INIT_DONE		BIT(26)

#घोषणा TCPC_OFFSET		0x1014
#घोषणा TCPC_MUX_CTL		GENMASK(1, 0)
#घोषणा MUX_NC			0
#घोषणा MUX_USB			1
#घोषणा MUX_DP			2
#घोषणा MUX_USBDP		3
#घोषणा TCPC_FLIPPED		BIT(2)
#घोषणा TCPC_LOW_POWER_EN	BIT(3)
#घोषणा TCPC_VALID		BIT(4)
#घोषणा TCPC_CONN		\
	(TCPC_VALID | FIELD_PREP(TCPC_MUX_CTL, MUX_USB))
#घोषणा TCPC_DISCONN		\
	(TCPC_VALID | FIELD_PREP(TCPC_MUX_CTL, MUX_NC) | TCPC_LOW_POWER_EN)

अटल स्थिर अक्षर *स्थिर PHY_RESETS[] = अणु "phy31", "phy", पूर्ण;
अटल स्थिर अक्षर *स्थिर CTL_RESETS[] = अणु "apb", "ctrl", पूर्ण;

काष्ठा tca_apb अणु
	काष्ठा reset_control *resets[ARRAY_SIZE(PHY_RESETS)];
	काष्ठा regulator *vbus;
	काष्ठा work_काष्ठा wk;
	काष्ठा usb_phy phy;

	bool regulator_enabled;
	bool phy_initialized;
	bool connected;
पूर्ण;

अटल पूर्णांक get_flipped(काष्ठा tca_apb *ta, bool *flipped)
अणु
	जोड़ extcon_property_value property;
	पूर्णांक ret;

	ret = extcon_get_property(ta->phy.edev, EXTCON_USB_HOST,
				  EXTCON_PROP_USB_TYPEC_POLARITY, &property);
	अगर (ret) अणु
		dev_err(ta->phy.dev, "no polarity property from extcon\n");
		वापस ret;
	पूर्ण

	*flipped = property.पूर्णांकval;

	वापस 0;
पूर्ण

अटल पूर्णांक phy_init(काष्ठा usb_phy *phy)
अणु
	काष्ठा tca_apb *ta = container_of(phy, काष्ठा tca_apb, phy);
	व्योम __iomem *ctrl1 = phy->io_priv + CTRL1_OFFSET;
	पूर्णांक val, ret, i;

	अगर (ta->phy_initialized)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(PHY_RESETS); i++)
		reset_control_deनिश्चित(ta->resets[i]);

	ret = पढ़ोl_poll_समयout(ctrl1, val, val & SRAM_INIT_DONE, 10, 10 * 1000);
	अगर (ret) अणु
		dev_err(ta->phy.dev, "SRAM init failed, 0x%x\n", val);
		वापस ret;
	पूर्ण

	ग_लिखोl(पढ़ोl(ctrl1) | SRAM_EXT_LD_DONE, ctrl1);

	ta->phy_initialized = true;
	अगर (!ta->phy.edev) अणु
		ग_लिखोl(TCPC_CONN, ta->phy.io_priv + TCPC_OFFSET);
		वापस phy->set_vbus(phy, true);
	पूर्ण

	schedule_work(&ta->wk);

	वापस ret;
पूर्ण

अटल व्योम phy_shutकरोwn(काष्ठा usb_phy *phy)
अणु
	काष्ठा tca_apb *ta = container_of(phy, काष्ठा tca_apb, phy);
	पूर्णांक i;

	अगर (!ta->phy_initialized)
		वापस;

	ta->phy_initialized = false;
	flush_work(&ta->wk);
	ta->phy.set_vbus(&ta->phy, false);

	ta->connected = false;
	ग_लिखोl(TCPC_DISCONN, ta->phy.io_priv + TCPC_OFFSET);

	क्रम (i = 0; i < ARRAY_SIZE(PHY_RESETS); i++)
		reset_control_निश्चित(ta->resets[i]);
पूर्ण

अटल पूर्णांक phy_set_vbus(काष्ठा usb_phy *phy, पूर्णांक on)
अणु
	काष्ठा tca_apb *ta = container_of(phy, काष्ठा tca_apb, phy);
	पूर्णांक ret;

	अगर (!!on == ta->regulator_enabled)
		वापस 0;

	अगर (on)
		ret = regulator_enable(ta->vbus);
	अन्यथा
		ret = regulator_disable(ta->vbus);

	अगर (!ret)
		ta->regulator_enabled = on;

	dev_dbg(ta->phy.dev, "set vbus: %d\n", on);
	वापस ret;
पूर्ण

अटल व्योम tca_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tca_apb *ta = container_of(work, काष्ठा tca_apb, wk);
	bool connected;
	bool flipped = false;
	u32 val;
	पूर्णांक ret;

	ret = get_flipped(ta, &flipped);
	अगर (ret)
		वापस;

	connected = extcon_get_state(ta->phy.edev, EXTCON_USB_HOST);
	अगर (connected == ta->connected)
		वापस;

	ta->connected = connected;
	अगर (connected) अणु
		val = TCPC_CONN;
		अगर (flipped)
			val |= TCPC_FLIPPED;
		dev_dbg(ta->phy.dev, "connected%s\n", flipped ? " flipped" : "");
	पूर्ण अन्यथा अणु
		val = TCPC_DISCONN;
		dev_dbg(ta->phy.dev, "disconnected\n");
	पूर्ण

	ग_लिखोl(val, ta->phy.io_priv + TCPC_OFFSET);

	ret = ta->phy.set_vbus(&ta->phy, connected);
	अगर (ret)
		dev_err(ta->phy.dev, "failed to set VBUS\n");
पूर्ण

अटल पूर्णांक id_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा tca_apb *ta = container_of(nb, काष्ठा tca_apb, phy.id_nb);

	अगर (ta->phy_initialized)
		schedule_work(&ta->wk);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक vbus_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ evnt, व्योम *ptr)
अणु
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा reset_control *resets[ARRAY_SIZE(CTL_RESETS)];
	काष्ठा device *dev = &pdev->dev;
	काष्ठा usb_phy *phy;
	काष्ठा tca_apb *ta;
	पूर्णांक i;

	ta = devm_kzalloc(dev, माप(*ta), GFP_KERNEL);
	अगर (!ta)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ta);
	INIT_WORK(&ta->wk, tca_work);

	phy = &ta->phy;
	phy->dev = dev;
	phy->label = dev_name(dev);
	phy->type = USB_PHY_TYPE_USB3;
	phy->init = phy_init;
	phy->shutकरोwn = phy_shutकरोwn;
	phy->set_vbus = phy_set_vbus;
	phy->id_nb.notअगरier_call = id_notअगरier;
	phy->vbus_nb.notअगरier_call = vbus_notअगरier;

	phy->io_priv = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(phy->io_priv))
		वापस PTR_ERR(phy->io_priv);

	ta->vbus = devm_regulator_get(dev, "vbus");
	अगर (IS_ERR(ta->vbus))
		वापस PTR_ERR(ta->vbus);

	क्रम (i = 0; i < ARRAY_SIZE(CTL_RESETS); i++) अणु
		resets[i] = devm_reset_control_get_exclusive(dev, CTL_RESETS[i]);
		अगर (IS_ERR(resets[i])) अणु
			dev_err(dev, "%s reset not found\n", CTL_RESETS[i]);
			वापस PTR_ERR(resets[i]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(PHY_RESETS); i++) अणु
		ta->resets[i] = devm_reset_control_get_exclusive(dev, PHY_RESETS[i]);
		अगर (IS_ERR(ta->resets[i])) अणु
			dev_err(dev, "%s reset not found\n", PHY_RESETS[i]);
			वापस PTR_ERR(ta->resets[i]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(CTL_RESETS); i++)
		reset_control_निश्चित(resets[i]);

	क्रम (i = 0; i < ARRAY_SIZE(PHY_RESETS); i++)
		reset_control_निश्चित(ta->resets[i]);
	/*
	 * Out-of-band reset of the controller after PHY reset will cause
	 * controller malfunctioning, so we should use in-band controller
	 * reset only and leave the controller de-निश्चितed here.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(CTL_RESETS); i++)
		reset_control_deनिश्चित(resets[i]);

	/* Need to रुको at least 20us after de-निश्चित the controller */
	usleep_range(20, 100);

	वापस usb_add_phy_dev(phy);
पूर्ण

अटल पूर्णांक phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tca_apb *ta = platक्रमm_get_drvdata(pdev);

	usb_हटाओ_phy(&ta->phy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id पूर्णांकel_usb_phy_dt_ids[] = अणु
	अणु .compatible = "intel,lgm-usb-phy" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, पूर्णांकel_usb_phy_dt_ids);

अटल काष्ठा platक्रमm_driver lgm_phy_driver = अणु
	.driver = अणु
		.name = "lgm-usb-phy",
		.of_match_table = पूर्णांकel_usb_phy_dt_ids,
	पूर्ण,
	.probe = phy_probe,
	.हटाओ = phy_हटाओ,
पूर्ण;

module_platक्रमm_driver(lgm_phy_driver);

MODULE_DESCRIPTION("Intel LGM USB PHY driver");
MODULE_AUTHOR("Li Yin <yin1.li@intel.com>");
MODULE_AUTHOR("Vadivel Murugan R <vadivel.muruganx.ramuthevar@linux.intel.com>");
MODULE_LICENSE("GPL v2");
