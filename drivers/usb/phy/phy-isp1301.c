<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NXP ISP1301 USB transceiver driver
 *
 * Copyright (C) 2012 Roland Stigge
 *
 * Author: Roland Stigge <stigge@antcom.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/i2c.h>
#समावेश <linux/usb/phy.h>
#समावेश <linux/usb/isp1301.h>

#घोषणा DRV_NAME		"isp1301"

काष्ठा isp1301 अणु
	काष्ठा usb_phy		phy;
	काष्ठा mutex		mutex;

	काष्ठा i2c_client	*client;
पूर्ण;

#घोषणा phy_to_isp(p)		(container_of((p), काष्ठा isp1301, phy))

अटल स्थिर काष्ठा i2c_device_id isp1301_id[] = अणु
	अणु "isp1301", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, isp1301_id);

अटल स्थिर काष्ठा of_device_id isp1301_of_match[] = अणु
	अणु.compatible = "nxp,isp1301" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, isp1301_of_match);

अटल काष्ठा i2c_client *isp1301_i2c_client;

अटल पूर्णांक __isp1301_ग_लिखो(काष्ठा isp1301 *isp, u8 reg, u8 value, u8 clear)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(isp->client, reg | clear, value);
पूर्ण

अटल पूर्णांक isp1301_ग_लिखो(काष्ठा isp1301 *isp, u8 reg, u8 value)
अणु
	वापस __isp1301_ग_लिखो(isp, reg, value, 0);
पूर्ण

अटल पूर्णांक isp1301_clear(काष्ठा isp1301 *isp, u8 reg, u8 value)
अणु
	वापस __isp1301_ग_लिखो(isp, reg, value, ISP1301_I2C_REG_CLEAR_ADDR);
पूर्ण

अटल पूर्णांक isp1301_phy_init(काष्ठा usb_phy *phy)
अणु
	काष्ठा isp1301 *isp = phy_to_isp(phy);

	/* Disable transparent UART mode first */
	isp1301_clear(isp, ISP1301_I2C_MODE_CONTROL_1, MC1_UART_EN);
	isp1301_clear(isp, ISP1301_I2C_MODE_CONTROL_1, ~MC1_SPEED_REG);
	isp1301_ग_लिखो(isp, ISP1301_I2C_MODE_CONTROL_1, MC1_SPEED_REG);
	isp1301_clear(isp, ISP1301_I2C_MODE_CONTROL_2, ~0);
	isp1301_ग_लिखो(isp, ISP1301_I2C_MODE_CONTROL_2, (MC2_BI_DI | MC2_PSW_EN
				| MC2_SPD_SUSP_CTRL));

	isp1301_clear(isp, ISP1301_I2C_OTG_CONTROL_1, ~0);
	isp1301_ग_लिखो(isp, ISP1301_I2C_MODE_CONTROL_1, MC1_DAT_SE0);
	isp1301_ग_लिखो(isp, ISP1301_I2C_OTG_CONTROL_1, (OTG1_DM_PULLDOWN
				| OTG1_DP_PULLDOWN));
	isp1301_clear(isp, ISP1301_I2C_OTG_CONTROL_1, (OTG1_DM_PULLUP
				| OTG1_DP_PULLUP));

	/* mask all पूर्णांकerrupts */
	isp1301_clear(isp, ISP1301_I2C_INTERRUPT_LATCH, ~0);
	isp1301_clear(isp, ISP1301_I2C_INTERRUPT_FALLING, ~0);
	isp1301_clear(isp, ISP1301_I2C_INTERRUPT_RISING, ~0);

	वापस 0;
पूर्ण

अटल पूर्णांक isp1301_phy_set_vbus(काष्ठा usb_phy *phy, पूर्णांक on)
अणु
	काष्ठा isp1301 *isp = phy_to_isp(phy);

	अगर (on)
		isp1301_ग_लिखो(isp, ISP1301_I2C_OTG_CONTROL_1, OTG1_VBUS_DRV);
	अन्यथा
		isp1301_clear(isp, ISP1301_I2C_OTG_CONTROL_1, OTG1_VBUS_DRV);

	वापस 0;
पूर्ण

अटल पूर्णांक isp1301_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	काष्ठा isp1301 *isp;
	काष्ठा usb_phy *phy;

	isp = devm_kzalloc(&client->dev, माप(*isp), GFP_KERNEL);
	अगर (!isp)
		वापस -ENOMEM;

	isp->client = client;
	mutex_init(&isp->mutex);

	phy = &isp->phy;
	phy->dev = &client->dev;
	phy->label = DRV_NAME;
	phy->init = isp1301_phy_init;
	phy->set_vbus = isp1301_phy_set_vbus;
	phy->type = USB_PHY_TYPE_USB2;

	i2c_set_clientdata(client, isp);
	usb_add_phy_dev(phy);

	isp1301_i2c_client = client;

	वापस 0;
पूर्ण

अटल पूर्णांक isp1301_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा isp1301 *isp = i2c_get_clientdata(client);

	usb_हटाओ_phy(&isp->phy);
	isp1301_i2c_client = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver isp1301_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = isp1301_of_match,
	पूर्ण,
	.probe = isp1301_probe,
	.हटाओ = isp1301_हटाओ,
	.id_table = isp1301_id,
पूर्ण;

module_i2c_driver(isp1301_driver);

अटल पूर्णांक match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा device_node *node = (स्थिर काष्ठा device_node *)data;
	वापस (dev->of_node == node) &&
		(dev->driver == &isp1301_driver.driver);
पूर्ण

काष्ठा i2c_client *isp1301_get_client(काष्ठा device_node *node)
अणु
	अगर (node) अणु /* reference of ISP1301 I2C node via DT */
		काष्ठा device *dev = bus_find_device(&i2c_bus_type, शून्य,
						     node, match);
		अगर (!dev)
			वापस शून्य;
		वापस to_i2c_client(dev);
	पूर्ण अन्यथा अणु /* non-DT: only one ISP1301 chip supported */
		वापस isp1301_i2c_client;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(isp1301_get_client);

MODULE_AUTHOR("Roland Stigge <stigge@antcom.de>");
MODULE_DESCRIPTION("NXP ISP1301 USB transceiver driver");
MODULE_LICENSE("GPL");
