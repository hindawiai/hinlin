<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * TI HD3SS3220 Type-C DRP Port Controller Driver
 *
 * Copyright (C) 2019 Renesas Electronics Corp.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/usb/role.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/typec.h>
#समावेश <linux/delay.h>

#घोषणा HD3SS3220_REG_CN_STAT_CTRL	0x09
#घोषणा HD3SS3220_REG_GEN_CTRL		0x0A
#घोषणा HD3SS3220_REG_DEV_REV		0xA0

/* Register HD3SS3220_REG_CN_STAT_CTRL*/
#घोषणा HD3SS3220_REG_CN_STAT_CTRL_ATTACHED_STATE_MASK	(BIT(7) | BIT(6))
#घोषणा HD3SS3220_REG_CN_STAT_CTRL_AS_DFP		BIT(6)
#घोषणा HD3SS3220_REG_CN_STAT_CTRL_AS_UFP		BIT(7)
#घोषणा HD3SS3220_REG_CN_STAT_CTRL_TO_ACCESSORY		(BIT(7) | BIT(6))
#घोषणा HD3SS3220_REG_CN_STAT_CTRL_INT_STATUS		BIT(4)

/* Register HD3SS3220_REG_GEN_CTRL*/
#घोषणा HD3SS3220_REG_GEN_CTRL_SRC_PREF_MASK		(BIT(2) | BIT(1))
#घोषणा HD3SS3220_REG_GEN_CTRL_SRC_PREF_DRP_DEFAULT	0x00
#घोषणा HD3SS3220_REG_GEN_CTRL_SRC_PREF_DRP_TRY_SNK	BIT(1)
#घोषणा HD3SS3220_REG_GEN_CTRL_SRC_PREF_DRP_TRY_SRC	(BIT(2) | BIT(1))

काष्ठा hd3ss3220 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा usb_role_चयन	*role_sw;
	काष्ठा typec_port *port;
पूर्ण;

अटल पूर्णांक hd3ss3220_set_source_pref(काष्ठा hd3ss3220 *hd3ss3220, पूर्णांक src_pref)
अणु
	वापस regmap_update_bits(hd3ss3220->regmap, HD3SS3220_REG_GEN_CTRL,
				  HD3SS3220_REG_GEN_CTRL_SRC_PREF_MASK,
				  src_pref);
पूर्ण

अटल क्रमागत usb_role hd3ss3220_get_attached_state(काष्ठा hd3ss3220 *hd3ss3220)
अणु
	अचिन्हित पूर्णांक reg_val;
	क्रमागत usb_role attached_state;
	पूर्णांक ret;

	ret = regmap_पढ़ो(hd3ss3220->regmap, HD3SS3220_REG_CN_STAT_CTRL,
			  &reg_val);
	अगर (ret < 0)
		वापस ret;

	चयन (reg_val & HD3SS3220_REG_CN_STAT_CTRL_ATTACHED_STATE_MASK) अणु
	हाल HD3SS3220_REG_CN_STAT_CTRL_AS_DFP:
		attached_state = USB_ROLE_HOST;
		अवरोध;
	हाल HD3SS3220_REG_CN_STAT_CTRL_AS_UFP:
		attached_state = USB_ROLE_DEVICE;
		अवरोध;
	शेष:
		attached_state = USB_ROLE_NONE;
		अवरोध;
	पूर्ण

	वापस attached_state;
पूर्ण

अटल पूर्णांक hd3ss3220_dr_set(काष्ठा typec_port *port, क्रमागत typec_data_role role)
अणु
	काष्ठा hd3ss3220 *hd3ss3220 = typec_get_drvdata(port);
	क्रमागत usb_role role_val;
	पूर्णांक pref, ret = 0;

	अगर (role == TYPEC_HOST) अणु
		role_val = USB_ROLE_HOST;
		pref = HD3SS3220_REG_GEN_CTRL_SRC_PREF_DRP_TRY_SRC;
	पूर्ण अन्यथा अणु
		role_val = USB_ROLE_DEVICE;
		pref = HD3SS3220_REG_GEN_CTRL_SRC_PREF_DRP_TRY_SNK;
	पूर्ण

	ret = hd3ss3220_set_source_pref(hd3ss3220, pref);
	usleep_range(10, 100);

	usb_role_चयन_set_role(hd3ss3220->role_sw, role_val);
	typec_set_data_role(hd3ss3220->port, role);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा typec_operations hd3ss3220_ops = अणु
	.dr_set = hd3ss3220_dr_set
पूर्ण;

अटल व्योम hd3ss3220_set_role(काष्ठा hd3ss3220 *hd3ss3220)
अणु
	क्रमागत usb_role role_state = hd3ss3220_get_attached_state(hd3ss3220);

	usb_role_चयन_set_role(hd3ss3220->role_sw, role_state);
	अगर (role_state == USB_ROLE_NONE)
		hd3ss3220_set_source_pref(hd3ss3220,
				HD3SS3220_REG_GEN_CTRL_SRC_PREF_DRP_DEFAULT);

	चयन (role_state) अणु
	हाल USB_ROLE_HOST:
		typec_set_data_role(hd3ss3220->port, TYPEC_HOST);
		अवरोध;
	हाल USB_ROLE_DEVICE:
		typec_set_data_role(hd3ss3220->port, TYPEC_DEVICE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t hd3ss3220_irq(काष्ठा hd3ss3220 *hd3ss3220)
अणु
	पूर्णांक err;

	hd3ss3220_set_role(hd3ss3220);
	err = regmap_update_bits_base(hd3ss3220->regmap,
				      HD3SS3220_REG_CN_STAT_CTRL,
				      HD3SS3220_REG_CN_STAT_CTRL_INT_STATUS,
				      HD3SS3220_REG_CN_STAT_CTRL_INT_STATUS,
				      शून्य, false, true);
	अगर (err < 0)
		वापस IRQ_NONE;

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t hd3ss3220_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा i2c_client *client = to_i2c_client(data);
	काष्ठा hd3ss3220 *hd3ss3220 = i2c_get_clientdata(client);

	वापस hd3ss3220_irq(hd3ss3220);
पूर्ण

अटल स्थिर काष्ठा regmap_config config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x0A,
पूर्ण;

अटल पूर्णांक hd3ss3220_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा typec_capability typec_cap = अणु पूर्ण;
	काष्ठा hd3ss3220 *hd3ss3220;
	काष्ठा fwnode_handle *connector, *ep;
	पूर्णांक ret;
	अचिन्हित पूर्णांक data;

	hd3ss3220 = devm_kzalloc(&client->dev, माप(काष्ठा hd3ss3220),
				 GFP_KERNEL);
	अगर (!hd3ss3220)
		वापस -ENOMEM;

	i2c_set_clientdata(client, hd3ss3220);

	hd3ss3220->dev = &client->dev;
	hd3ss3220->regmap = devm_regmap_init_i2c(client, &config);
	अगर (IS_ERR(hd3ss3220->regmap))
		वापस PTR_ERR(hd3ss3220->regmap);

	hd3ss3220_set_source_pref(hd3ss3220,
				  HD3SS3220_REG_GEN_CTRL_SRC_PREF_DRP_DEFAULT);
	/* For backward compatibility check the connector child node first */
	connector = device_get_named_child_node(hd3ss3220->dev, "connector");
	अगर (connector) अणु
		hd3ss3220->role_sw = fwnode_usb_role_चयन_get(connector);
	पूर्ण अन्यथा अणु
		ep = fwnode_graph_get_next_endpoपूर्णांक(dev_fwnode(hd3ss3220->dev), शून्य);
		अगर (!ep)
			वापस -ENODEV;
		connector = fwnode_graph_get_remote_port_parent(ep);
		fwnode_handle_put(ep);
		अगर (!connector)
			वापस -ENODEV;
		hd3ss3220->role_sw = usb_role_चयन_get(hd3ss3220->dev);
	पूर्ण

	अगर (IS_ERR(hd3ss3220->role_sw)) अणु
		ret = PTR_ERR(hd3ss3220->role_sw);
		जाओ err_put_fwnode;
	पूर्ण

	typec_cap.prefer_role = TYPEC_NO_PREFERRED_ROLE;
	typec_cap.driver_data = hd3ss3220;
	typec_cap.type = TYPEC_PORT_DRP;
	typec_cap.data = TYPEC_PORT_DRD;
	typec_cap.ops = &hd3ss3220_ops;
	typec_cap.fwnode = connector;

	hd3ss3220->port = typec_रेजिस्टर_port(&client->dev, &typec_cap);
	अगर (IS_ERR(hd3ss3220->port)) अणु
		ret = PTR_ERR(hd3ss3220->port);
		जाओ err_put_role;
	पूर्ण

	hd3ss3220_set_role(hd3ss3220);
	ret = regmap_पढ़ो(hd3ss3220->regmap, HD3SS3220_REG_CN_STAT_CTRL, &data);
	अगर (ret < 0)
		जाओ err_unreg_port;

	अगर (data & HD3SS3220_REG_CN_STAT_CTRL_INT_STATUS) अणु
		ret = regmap_ग_लिखो(hd3ss3220->regmap,
				HD3SS3220_REG_CN_STAT_CTRL,
				data | HD3SS3220_REG_CN_STAT_CTRL_INT_STATUS);
		अगर (ret < 0)
			जाओ err_unreg_port;
	पूर्ण

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
					hd3ss3220_irq_handler,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					"hd3ss3220", &client->dev);
		अगर (ret)
			जाओ err_unreg_port;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(client, HD3SS3220_REG_DEV_REV);
	अगर (ret < 0)
		जाओ err_unreg_port;

	fwnode_handle_put(connector);

	dev_info(&client->dev, "probed revision=0x%x\n", ret);

	वापस 0;
err_unreg_port:
	typec_unरेजिस्टर_port(hd3ss3220->port);
err_put_role:
	usb_role_चयन_put(hd3ss3220->role_sw);
err_put_fwnode:
	fwnode_handle_put(connector);

	वापस ret;
पूर्ण

अटल पूर्णांक hd3ss3220_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा hd3ss3220 *hd3ss3220 = i2c_get_clientdata(client);

	typec_unरेजिस्टर_port(hd3ss3220->port);
	usb_role_चयन_put(hd3ss3220->role_sw);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dev_ids[] = अणु
	अणु .compatible = "ti,hd3ss3220"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dev_ids);

अटल काष्ठा i2c_driver hd3ss3220_driver = अणु
	.driver = अणु
		.name = "hd3ss3220",
		.of_match_table = of_match_ptr(dev_ids),
	पूर्ण,
	.probe = hd3ss3220_probe,
	.हटाओ =  hd3ss3220_हटाओ,
पूर्ण;

module_i2c_driver(hd3ss3220_driver);

MODULE_AUTHOR("Biju Das <biju.das@bp.renesas.com>");
MODULE_DESCRIPTION("TI HD3SS3220 DRP Port Controller Driver");
MODULE_LICENSE("GPL");
