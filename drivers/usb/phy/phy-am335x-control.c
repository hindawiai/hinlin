<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/usb/otg.h>
#समावेश "phy-am335x-control.h"

काष्ठा am335x_control_usb अणु
	काष्ठा device *dev;
	व्योम __iomem *phy_reg;
	व्योम __iomem *wkup;
	spinlock_t lock;
	काष्ठा phy_control phy_ctrl;
पूर्ण;

#घोषणा AM335X_USB0_CTRL		0x0
#घोषणा AM335X_USB1_CTRL		0x8
#घोषणा AM335x_USB_WKUP			0x0

#घोषणा USBPHY_CM_PWRDN		(1 << 0)
#घोषणा USBPHY_OTG_PWRDN	(1 << 1)
#घोषणा USBPHY_OTGVDET_EN	(1 << 19)
#घोषणा USBPHY_OTGSESSEND_EN	(1 << 20)

#घोषणा AM335X_PHY0_WK_EN	(1 << 0)
#घोषणा AM335X_PHY1_WK_EN	(1 << 8)

अटल व्योम am335x_phy_wkup(काष्ठा  phy_control *phy_ctrl, u32 id, bool on)
अणु
	काष्ठा am335x_control_usb *usb_ctrl;
	u32 val;
	u32 reg;

	usb_ctrl = container_of(phy_ctrl, काष्ठा am335x_control_usb, phy_ctrl);

	चयन (id) अणु
	हाल 0:
		reg = AM335X_PHY0_WK_EN;
		अवरोध;
	हाल 1:
		reg = AM335X_PHY1_WK_EN;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	spin_lock(&usb_ctrl->lock);
	val = पढ़ोl(usb_ctrl->wkup);

	अगर (on)
		val |= reg;
	अन्यथा
		val &= ~reg;

	ग_लिखोl(val, usb_ctrl->wkup);
	spin_unlock(&usb_ctrl->lock);
पूर्ण

अटल व्योम am335x_phy_घातer(काष्ठा phy_control *phy_ctrl, u32 id,
				क्रमागत usb_dr_mode dr_mode, bool on)
अणु
	काष्ठा am335x_control_usb *usb_ctrl;
	u32 val;
	u32 reg;

	usb_ctrl = container_of(phy_ctrl, काष्ठा am335x_control_usb, phy_ctrl);

	चयन (id) अणु
	हाल 0:
		reg = AM335X_USB0_CTRL;
		अवरोध;
	हाल 1:
		reg = AM335X_USB1_CTRL;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	val = पढ़ोl(usb_ctrl->phy_reg + reg);
	अगर (on) अणु
		अगर (dr_mode == USB_DR_MODE_HOST) अणु
			val &= ~(USBPHY_CM_PWRDN | USBPHY_OTG_PWRDN |
					USBPHY_OTGVDET_EN);
			val |= USBPHY_OTGSESSEND_EN;
		पूर्ण अन्यथा अणु
			val &= ~(USBPHY_CM_PWRDN | USBPHY_OTG_PWRDN);
			val |= USBPHY_OTGVDET_EN | USBPHY_OTGSESSEND_EN;
		पूर्ण
	पूर्ण अन्यथा अणु
		val |= USBPHY_CM_PWRDN | USBPHY_OTG_PWRDN;
	पूर्ण

	ग_लिखोl(val, usb_ctrl->phy_reg + reg);

	/*
	 * Give the PHY ~1ms to complete the घातer up operation.
	 * Tests have shown unstable behaviour अगर other USB PHY related
	 * रेजिस्टरs are written too लघुly after such a transition.
	 */
	अगर (on)
		mdelay(1);
पूर्ण

अटल स्थिर काष्ठा phy_control ctrl_am335x = अणु
	.phy_घातer = am335x_phy_घातer,
	.phy_wkup = am335x_phy_wkup,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_control_usb_id_table[] = अणु
	अणु .compatible = "ti,am335x-usb-ctrl-module", .data = &ctrl_am335x पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_control_usb_id_table);

अटल काष्ठा platक्रमm_driver am335x_control_driver;
अटल पूर्णांक match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा device_node *node = (स्थिर काष्ठा device_node *)data;
	वापस dev->of_node == node &&
		dev->driver == &am335x_control_driver.driver;
पूर्ण

काष्ठा phy_control *am335x_get_phy_control(काष्ठा device *dev)
अणु
	काष्ठा device_node *node;
	काष्ठा am335x_control_usb *ctrl_usb;

	node = of_parse_phandle(dev->of_node, "ti,ctrl_mod", 0);
	अगर (!node)
		वापस शून्य;

	dev = bus_find_device(&platक्रमm_bus_type, शून्य, node, match);
	of_node_put(node);
	अगर (!dev)
		वापस शून्य;

	ctrl_usb = dev_get_drvdata(dev);
	put_device(dev);
	अगर (!ctrl_usb)
		वापस शून्य;
	वापस &ctrl_usb->phy_ctrl;
पूर्ण
EXPORT_SYMBOL_GPL(am335x_get_phy_control);

अटल पूर्णांक am335x_control_usb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा am335x_control_usb *ctrl_usb;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा phy_control *phy_ctrl;

	of_id = of_match_node(omap_control_usb_id_table, pdev->dev.of_node);
	अगर (!of_id)
		वापस -EINVAL;

	phy_ctrl = of_id->data;

	ctrl_usb = devm_kzalloc(&pdev->dev, माप(*ctrl_usb), GFP_KERNEL);
	अगर (!ctrl_usb)
		वापस -ENOMEM;

	ctrl_usb->dev = &pdev->dev;

	ctrl_usb->phy_reg = devm_platक्रमm_ioremap_resource_byname(pdev, "phy_ctrl");
	अगर (IS_ERR(ctrl_usb->phy_reg))
		वापस PTR_ERR(ctrl_usb->phy_reg);

	ctrl_usb->wkup = devm_platक्रमm_ioremap_resource_byname(pdev, "wakeup");
	अगर (IS_ERR(ctrl_usb->wkup))
		वापस PTR_ERR(ctrl_usb->wkup);

	spin_lock_init(&ctrl_usb->lock);
	ctrl_usb->phy_ctrl = *phy_ctrl;

	dev_set_drvdata(ctrl_usb->dev, ctrl_usb);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver am335x_control_driver = अणु
	.probe		= am335x_control_usb_probe,
	.driver		= अणु
		.name	= "am335x-control-usb",
		.of_match_table = omap_control_usb_id_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(am335x_control_driver);
MODULE_LICENSE("GPL v2");
