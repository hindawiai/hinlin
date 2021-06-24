<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * drivers/extcon/extcon-tusb320.c - TUSB320 extcon driver
 *
 * Copyright (C) 2020 National Instruments Corporation
 * Author: Michael Auchter <michael.auchter@ni.com>
 */

#समावेश <linux/extcon-provider.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#घोषणा TUSB320_REG9				0x9
#घोषणा TUSB320_REG9_ATTACHED_STATE_SHIFT	6
#घोषणा TUSB320_REG9_ATTACHED_STATE_MASK	0x3
#घोषणा TUSB320_REG9_CABLE_सूचीECTION		BIT(5)
#घोषणा TUSB320_REG9_INTERRUPT_STATUS		BIT(4)
#घोषणा TUSB320_ATTACHED_STATE_NONE		0x0
#घोषणा TUSB320_ATTACHED_STATE_DFP		0x1
#घोषणा TUSB320_ATTACHED_STATE_UFP		0x2
#घोषणा TUSB320_ATTACHED_STATE_ACC		0x3

काष्ठा tusb320_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा extcon_dev *edev;
पूर्ण;

अटल स्थिर अक्षर * स्थिर tusb_attached_states[] = अणु
	[TUSB320_ATTACHED_STATE_NONE] = "not attached",
	[TUSB320_ATTACHED_STATE_DFP]  = "downstream facing port",
	[TUSB320_ATTACHED_STATE_UFP]  = "upstream facing port",
	[TUSB320_ATTACHED_STATE_ACC]  = "accessory",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tusb320_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
पूर्ण;

अटल पूर्णांक tusb320_check_signature(काष्ठा tusb320_priv *priv)
अणु
	अटल स्थिर अक्षर sig[] = अणु '\0', 'T', 'U', 'S', 'B', '3', '2', '0' पूर्ण;
	अचिन्हित val;
	पूर्णांक i, ret;

	क्रम (i = 0; i < माप(sig); i++) अणु
		ret = regmap_पढ़ो(priv->regmap, माप(sig) - 1 - i, &val);
		अगर (ret < 0)
			वापस ret;
		अगर (val != sig[i]) अणु
			dev_err(priv->dev, "signature mismatch!\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t tusb320_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tusb320_priv *priv = dev_id;
	पूर्णांक state, polarity;
	अचिन्हित reg;

	अगर (regmap_पढ़ो(priv->regmap, TUSB320_REG9, &reg)) अणु
		dev_err(priv->dev, "error during i2c read!\n");
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(reg & TUSB320_REG9_INTERRUPT_STATUS))
		वापस IRQ_NONE;

	state = (reg >> TUSB320_REG9_ATTACHED_STATE_SHIFT) &
		TUSB320_REG9_ATTACHED_STATE_MASK;
	polarity = !!(reg & TUSB320_REG9_CABLE_सूचीECTION);

	dev_dbg(priv->dev, "attached state: %s, polarity: %d\n",
		tusb_attached_states[state], polarity);

	extcon_set_state(priv->edev, EXTCON_USB,
			 state == TUSB320_ATTACHED_STATE_UFP);
	extcon_set_state(priv->edev, EXTCON_USB_HOST,
			 state == TUSB320_ATTACHED_STATE_DFP);
	extcon_set_property(priv->edev, EXTCON_USB,
			    EXTCON_PROP_USB_TYPEC_POLARITY,
			    (जोड़ extcon_property_value)polarity);
	extcon_set_property(priv->edev, EXTCON_USB_HOST,
			    EXTCON_PROP_USB_TYPEC_POLARITY,
			    (जोड़ extcon_property_value)polarity);
	extcon_sync(priv->edev, EXTCON_USB);
	extcon_sync(priv->edev, EXTCON_USB_HOST);

	regmap_ग_लिखो(priv->regmap, TUSB320_REG9, reg);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा regmap_config tusb320_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक tusb320_extcon_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tusb320_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	priv->dev = &client->dev;

	priv->regmap = devm_regmap_init_i2c(client, &tusb320_regmap_config);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	ret = tusb320_check_signature(priv);
	अगर (ret)
		वापस ret;

	priv->edev = devm_extcon_dev_allocate(priv->dev, tusb320_extcon_cable);
	अगर (IS_ERR(priv->edev)) अणु
		dev_err(priv->dev, "failed to allocate extcon device\n");
		वापस PTR_ERR(priv->edev);
	पूर्ण

	ret = devm_extcon_dev_रेजिस्टर(priv->dev, priv->edev);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "failed to register extcon device\n");
		वापस ret;
	पूर्ण

	extcon_set_property_capability(priv->edev, EXTCON_USB,
				       EXTCON_PROP_USB_TYPEC_POLARITY);
	extcon_set_property_capability(priv->edev, EXTCON_USB_HOST,
				       EXTCON_PROP_USB_TYPEC_POLARITY);

	/* update initial state */
	tusb320_irq_handler(client->irq, priv);

	ret = devm_request_thपढ़ोed_irq(priv->dev, client->irq, शून्य,
					tusb320_irq_handler,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					client->name, priv);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id tusb320_extcon_dt_match[] = अणु
	अणु .compatible = "ti,tusb320", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tusb320_extcon_dt_match);

अटल काष्ठा i2c_driver tusb320_extcon_driver = अणु
	.probe		= tusb320_extcon_probe,
	.driver		= अणु
		.name	= "extcon-tusb320",
		.of_match_table = tusb320_extcon_dt_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init tusb320_init(व्योम)
अणु
	वापस i2c_add_driver(&tusb320_extcon_driver);
पूर्ण
subsys_initcall(tusb320_init);

अटल व्योम __निकास tusb320_निकास(व्योम)
अणु
	i2c_del_driver(&tusb320_extcon_driver);
पूर्ण
module_निकास(tusb320_निकास);

MODULE_AUTHOR("Michael Auchter <michael.auchter@ni.com>");
MODULE_DESCRIPTION("TI TUSB320 extcon driver");
MODULE_LICENSE("GPL v2");
