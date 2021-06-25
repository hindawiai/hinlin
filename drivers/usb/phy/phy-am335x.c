<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/usb_phy_generic.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/usb/of.h>

#समावेश "phy-am335x-control.h"
#समावेश "phy-generic.h"

काष्ठा am335x_phy अणु
	काष्ठा usb_phy_generic usb_phy_gen;
	काष्ठा phy_control *phy_ctrl;
	पूर्णांक id;
	क्रमागत usb_dr_mode dr_mode;
पूर्ण;

अटल पूर्णांक am335x_init(काष्ठा usb_phy *phy)
अणु
	काष्ठा am335x_phy *am_phy = dev_get_drvdata(phy->dev);

	phy_ctrl_घातer(am_phy->phy_ctrl, am_phy->id, am_phy->dr_mode, true);
	वापस 0;
पूर्ण

अटल व्योम am335x_shutकरोwn(काष्ठा usb_phy *phy)
अणु
	काष्ठा am335x_phy *am_phy = dev_get_drvdata(phy->dev);

	phy_ctrl_घातer(am_phy->phy_ctrl, am_phy->id, am_phy->dr_mode, false);
पूर्ण

अटल पूर्णांक am335x_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा am335x_phy *am_phy;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	am_phy = devm_kzalloc(dev, माप(*am_phy), GFP_KERNEL);
	अगर (!am_phy)
		वापस -ENOMEM;

	am_phy->phy_ctrl = am335x_get_phy_control(dev);
	अगर (!am_phy->phy_ctrl)
		वापस -EPROBE_DEFER;

	am_phy->id = of_alias_get_id(pdev->dev.of_node, "phy");
	अगर (am_phy->id < 0) अणु
		dev_err(&pdev->dev, "Missing PHY id: %d\n", am_phy->id);
		वापस am_phy->id;
	पूर्ण

	am_phy->dr_mode = of_usb_get_dr_mode_by_phy(pdev->dev.of_node, -1);

	ret = usb_phy_gen_create_phy(dev, &am_phy->usb_phy_gen);
	अगर (ret)
		वापस ret;

	am_phy->usb_phy_gen.phy.init = am335x_init;
	am_phy->usb_phy_gen.phy.shutकरोwn = am335x_shutकरोwn;

	platक्रमm_set_drvdata(pdev, am_phy);
	device_init_wakeup(dev, true);

	/*
	 * If we leave PHY wakeup enabled then AM33XX wakes up
	 * immediately from DS0. To aव्योम this we mark dev->घातer.can_wakeup
	 * to false. The same is checked in suspend routine to decide
	 * on whether to enable PHY wakeup or not.
	 * PHY wakeup works fine in standby mode, there by allowing us to
	 * handle remote wakeup, wakeup on disconnect and connect.
	 */

	device_set_wakeup_enable(dev, false);
	phy_ctrl_घातer(am_phy->phy_ctrl, am_phy->id, am_phy->dr_mode, false);

	वापस usb_add_phy_dev(&am_phy->usb_phy_gen.phy);
पूर्ण

अटल पूर्णांक am335x_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा am335x_phy *am_phy = platक्रमm_get_drvdata(pdev);

	usb_हटाओ_phy(&am_phy->usb_phy_gen.phy);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक am335x_phy_suspend(काष्ठा device *dev)
अणु
	काष्ठा am335x_phy *am_phy = dev_get_drvdata(dev);

	/*
	 * Enable phy wakeup only अगर dev->घातer.can_wakeup is true.
	 * Make sure to enable wakeup to support remote wakeup	in
	 * standby mode ( same is not supported in OFF(DS0) mode).
	 * Enable it by करोing
	 * echo enabled > /sys/bus/platक्रमm/devices/<usb-phy-id>/घातer/wakeup
	 */

	अगर (device_may_wakeup(dev))
		phy_ctrl_wkup(am_phy->phy_ctrl, am_phy->id, true);

	phy_ctrl_घातer(am_phy->phy_ctrl, am_phy->id, am_phy->dr_mode, false);

	वापस 0;
पूर्ण

अटल पूर्णांक am335x_phy_resume(काष्ठा device *dev)
अणु
	काष्ठा am335x_phy	*am_phy = dev_get_drvdata(dev);

	phy_ctrl_घातer(am_phy->phy_ctrl, am_phy->id, am_phy->dr_mode, true);

	अगर (device_may_wakeup(dev))
		phy_ctrl_wkup(am_phy->phy_ctrl, am_phy->id, false);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(am335x_pm_ops, am335x_phy_suspend, am335x_phy_resume);

अटल स्थिर काष्ठा of_device_id am335x_phy_ids[] = अणु
	अणु .compatible = "ti,am335x-usb-phy" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, am335x_phy_ids);

अटल काष्ठा platक्रमm_driver am335x_phy_driver = अणु
	.probe          = am335x_phy_probe,
	.हटाओ         = am335x_phy_हटाओ,
	.driver         = अणु
		.name   = "am335x-phy-driver",
		.pm = &am335x_pm_ops,
		.of_match_table = am335x_phy_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(am335x_phy_driver);
MODULE_LICENSE("GPL v2");
