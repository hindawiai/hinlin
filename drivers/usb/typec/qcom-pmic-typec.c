<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/role.h>
#समावेश <linux/usb/typec_mux.h>

#घोषणा TYPEC_MISC_STATUS		0xb
#घोषणा CC_ATTACHED			BIT(0)
#घोषणा CC_ORIENTATION			BIT(1)
#घोषणा SNK_SRC_MODE			BIT(6)
#घोषणा TYPEC_MODE_CFG			0x44
#घोषणा TYPEC_DISABLE_CMD		BIT(0)
#घोषणा EN_SNK_ONLY			BIT(1)
#घोषणा EN_SRC_ONLY			BIT(2)
#घोषणा TYPEC_VCONN_CONTROL		0x46
#घोषणा VCONN_EN_SRC			BIT(0)
#घोषणा VCONN_EN_VAL			BIT(1)
#घोषणा TYPEC_EXIT_STATE_CFG		0x50
#घोषणा SEL_SRC_UPPER_REF		BIT(2)
#घोषणा TYPEC_INTR_EN_CFG_1		0x5e
#घोषणा TYPEC_INTR_EN_CFG_1_MASK	GENMASK(7, 0)

काष्ठा qcom_pmic_typec अणु
	काष्ठा device		*dev;
	काष्ठा regmap		*regmap;
	u32			base;

	काष्ठा typec_port	*port;
	काष्ठा usb_role_चयन *role_sw;

	काष्ठा regulator	*vbus_reg;
	bool			vbus_enabled;
पूर्ण;

अटल व्योम qcom_pmic_typec_enable_vbus_regulator(काष्ठा qcom_pmic_typec
							*qcom_usb, bool enable)
अणु
	पूर्णांक ret;

	अगर (enable == qcom_usb->vbus_enabled)
		वापस;

	अगर (enable) अणु
		ret = regulator_enable(qcom_usb->vbus_reg);
		अगर (ret)
			वापस;
	पूर्ण अन्यथा अणु
		ret = regulator_disable(qcom_usb->vbus_reg);
		अगर (ret)
			वापस;
	पूर्ण
	qcom_usb->vbus_enabled = enable;
पूर्ण

अटल व्योम qcom_pmic_typec_check_connection(काष्ठा qcom_pmic_typec *qcom_usb)
अणु
	क्रमागत typec_orientation orientation;
	क्रमागत usb_role role;
	अचिन्हित पूर्णांक stat;
	bool enable_vbus;

	regmap_पढ़ो(qcom_usb->regmap, qcom_usb->base + TYPEC_MISC_STATUS,
		    &stat);

	अगर (stat & CC_ATTACHED) अणु
		orientation = (stat & CC_ORIENTATION) ?
				TYPEC_ORIENTATION_REVERSE :
				TYPEC_ORIENTATION_NORMAL;
		typec_set_orientation(qcom_usb->port, orientation);

		role = (stat & SNK_SRC_MODE) ? USB_ROLE_HOST : USB_ROLE_DEVICE;
		अगर (role == USB_ROLE_HOST)
			enable_vbus = true;
		अन्यथा
			enable_vbus = false;
	पूर्ण अन्यथा अणु
		role = USB_ROLE_NONE;
		enable_vbus = false;
	पूर्ण

	qcom_pmic_typec_enable_vbus_regulator(qcom_usb, enable_vbus);
	usb_role_चयन_set_role(qcom_usb->role_sw, role);
पूर्ण

अटल irqवापस_t qcom_pmic_typec_पूर्णांकerrupt(पूर्णांक irq, व्योम *_qcom_usb)
अणु
	काष्ठा qcom_pmic_typec *qcom_usb = _qcom_usb;

	qcom_pmic_typec_check_connection(qcom_usb);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम qcom_pmic_typec_typec_hw_init(काष्ठा qcom_pmic_typec *qcom_usb,
					  क्रमागत typec_port_type type)
अणु
	u8 mode = 0;

	regmap_update_bits(qcom_usb->regmap,
			   qcom_usb->base + TYPEC_INTR_EN_CFG_1,
			   TYPEC_INTR_EN_CFG_1_MASK, 0);

	अगर (type == TYPEC_PORT_SRC)
		mode = EN_SRC_ONLY;
	अन्यथा अगर (type == TYPEC_PORT_SNK)
		mode = EN_SNK_ONLY;

	regmap_update_bits(qcom_usb->regmap, qcom_usb->base + TYPEC_MODE_CFG,
			   EN_SNK_ONLY | EN_SRC_ONLY, mode);

	regmap_update_bits(qcom_usb->regmap,
			   qcom_usb->base + TYPEC_VCONN_CONTROL,
			   VCONN_EN_SRC | VCONN_EN_VAL, VCONN_EN_SRC);
	regmap_update_bits(qcom_usb->regmap,
			   qcom_usb->base + TYPEC_EXIT_STATE_CFG,
			   SEL_SRC_UPPER_REF, SEL_SRC_UPPER_REF);
पूर्ण

अटल पूर्णांक qcom_pmic_typec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_pmic_typec *qcom_usb;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा typec_capability cap;
	स्थिर अक्षर *buf;
	पूर्णांक ret, irq, role;
	u32 reg;

	ret = device_property_पढ़ो_u32(dev, "reg", &reg);
	अगर (ret < 0) अणु
		dev_err(dev, "missing base address\n");
		वापस ret;
	पूर्ण

	qcom_usb = devm_kzalloc(dev, माप(*qcom_usb), GFP_KERNEL);
	अगर (!qcom_usb)
		वापस -ENOMEM;

	qcom_usb->dev = dev;
	qcom_usb->base = reg;

	qcom_usb->regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!qcom_usb->regmap) अणु
		dev_err(dev, "Failed to get regmap\n");
		वापस -EINVAL;
	पूर्ण

	qcom_usb->vbus_reg = devm_regulator_get(qcom_usb->dev, "usb_vbus");
	अगर (IS_ERR(qcom_usb->vbus_reg))
		वापस PTR_ERR(qcom_usb->vbus_reg);

	fwnode = device_get_named_child_node(dev, "connector");
	अगर (!fwnode)
		वापस -EINVAL;

	ret = fwnode_property_पढ़ो_string(fwnode, "power-role", &buf);
	अगर (!ret) अणु
		role = typec_find_port_घातer_role(buf);
		अगर (role < 0)
			role = TYPEC_PORT_SNK;
	पूर्ण अन्यथा अणु
		role = TYPEC_PORT_SNK;
	पूर्ण
	cap.type = role;

	ret = fwnode_property_पढ़ो_string(fwnode, "data-role", &buf);
	अगर (!ret) अणु
		role = typec_find_port_data_role(buf);
		अगर (role < 0)
			role = TYPEC_PORT_UFP;
	पूर्ण अन्यथा अणु
		role = TYPEC_PORT_UFP;
	पूर्ण
	cap.data = role;

	cap.prefer_role = TYPEC_NO_PREFERRED_ROLE;
	cap.fwnode = fwnode;
	qcom_usb->port = typec_रेजिस्टर_port(dev, &cap);
	अगर (IS_ERR(qcom_usb->port)) अणु
		ret = PTR_ERR(qcom_usb->port);
		dev_err(dev, "Failed to register type c port %d\n", ret);
		जाओ err_put_node;
	पूर्ण
	fwnode_handle_put(fwnode);

	qcom_usb->role_sw = fwnode_usb_role_चयन_get(dev_fwnode(qcom_usb->dev));
	अगर (IS_ERR(qcom_usb->role_sw)) अणु
		अगर (PTR_ERR(qcom_usb->role_sw) != -EPROBE_DEFER)
			dev_err(dev, "failed to get role switch\n");
		ret = PTR_ERR(qcom_usb->role_sw);
		जाओ err_typec_port;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		जाओ err_usb_role_sw;

	ret = devm_request_thपढ़ोed_irq(qcom_usb->dev, irq, शून्य,
					qcom_pmic_typec_पूर्णांकerrupt, IRQF_ONESHOT,
					"qcom-pmic-typec", qcom_usb);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not request IRQ\n");
		जाओ err_usb_role_sw;
	पूर्ण

	platक्रमm_set_drvdata(pdev, qcom_usb);
	qcom_pmic_typec_typec_hw_init(qcom_usb, cap.type);
	qcom_pmic_typec_check_connection(qcom_usb);

	वापस 0;

err_usb_role_sw:
	usb_role_चयन_put(qcom_usb->role_sw);
err_typec_port:
	typec_unरेजिस्टर_port(qcom_usb->port);
err_put_node:
	fwnode_handle_put(fwnode);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_pmic_typec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_pmic_typec *qcom_usb = platक्रमm_get_drvdata(pdev);

	usb_role_चयन_set_role(qcom_usb->role_sw, USB_ROLE_NONE);
	qcom_pmic_typec_enable_vbus_regulator(qcom_usb, 0);

	typec_unरेजिस्टर_port(qcom_usb->port);
	usb_role_चयन_put(qcom_usb->role_sw);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_pmic_typec_table[] = अणु
	अणु .compatible = "qcom,pm8150b-usb-typec" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_pmic_typec_table);

अटल काष्ठा platक्रमm_driver qcom_pmic_typec = अणु
	.driver = अणु
		.name = "qcom,pmic-typec",
		.of_match_table = qcom_pmic_typec_table,
	पूर्ण,
	.probe = qcom_pmic_typec_probe,
	.हटाओ = qcom_pmic_typec_हटाओ,
पूर्ण;
module_platक्रमm_driver(qcom_pmic_typec);

MODULE_DESCRIPTION("QCOM PMIC USB type C driver");
MODULE_LICENSE("GPL v2");
