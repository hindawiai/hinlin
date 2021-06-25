<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Microchip USB251xB USB 2.0 Hi-Speed Hub Controller
 * Configuration via SMBus.
 *
 * Copyright (c) 2017 SKIDATA AG
 *
 * This work is based on the USB3503 driver by Dongjin Kim and
 * a not-accepted patch by Fabien Lahoudere, see:
 * https://patchwork.kernel.org/patch/9257715/
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/nls.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

/* Internal Register Set Addresses & Default Values acc. to DS00001692C */
#घोषणा USB251XB_ADDR_VENDOR_ID_LSB	0x00
#घोषणा USB251XB_ADDR_VENDOR_ID_MSB	0x01
#घोषणा USB251XB_DEF_VENDOR_ID		0x0424

#घोषणा USB251XB_ADDR_PRODUCT_ID_LSB	0x02
#घोषणा USB251XB_ADDR_PRODUCT_ID_MSB	0x03

#घोषणा USB251XB_ADDR_DEVICE_ID_LSB	0x04
#घोषणा USB251XB_ADDR_DEVICE_ID_MSB	0x05
#घोषणा USB251XB_DEF_DEVICE_ID		0x0BB3

#घोषणा USB251XB_ADDR_CONFIG_DATA_1	0x06
#घोषणा USB251XB_DEF_CONFIG_DATA_1	0x9B
#घोषणा USB251XB_ADDR_CONFIG_DATA_2	0x07
#घोषणा USB251XB_DEF_CONFIG_DATA_2	0x20
#घोषणा USB251XB_ADDR_CONFIG_DATA_3	0x08
#घोषणा USB251XB_DEF_CONFIG_DATA_3	0x02

#घोषणा USB251XB_ADDR_NON_REMOVABLE_DEVICES	0x09
#घोषणा USB251XB_DEF_NON_REMOVABLE_DEVICES	0x00

#घोषणा USB251XB_ADDR_PORT_DISABLE_SELF	0x0A
#घोषणा USB251XB_DEF_PORT_DISABLE_SELF	0x00
#घोषणा USB251XB_ADDR_PORT_DISABLE_BUS	0x0B
#घोषणा USB251XB_DEF_PORT_DISABLE_BUS	0x00

#घोषणा USB251XB_ADDR_MAX_POWER_SELF	0x0C
#घोषणा USB251XB_DEF_MAX_POWER_SELF	0x01
#घोषणा USB251XB_ADDR_MAX_POWER_BUS	0x0D
#घोषणा USB251XB_DEF_MAX_POWER_BUS	0x32

#घोषणा USB251XB_ADDR_MAX_CURRENT_SELF	0x0E
#घोषणा USB251XB_DEF_MAX_CURRENT_SELF	0x01
#घोषणा USB251XB_ADDR_MAX_CURRENT_BUS	0x0F
#घोषणा USB251XB_DEF_MAX_CURRENT_BUS	0x32

#घोषणा USB251XB_ADDR_POWER_ON_TIME	0x10
#घोषणा USB251XB_DEF_POWER_ON_TIME	0x32

#घोषणा USB251XB_ADDR_LANGUAGE_ID_HIGH	0x11
#घोषणा USB251XB_ADDR_LANGUAGE_ID_LOW	0x12
#घोषणा USB251XB_DEF_LANGUAGE_ID	0x0000

#घोषणा USB251XB_STRING_बफ_मानE			62
#घोषणा USB251XB_ADDR_MANUFACTURER_STRING_LEN	0x13
#घोषणा USB251XB_ADDR_MANUFACTURER_STRING	0x16
#घोषणा USB251XB_DEF_MANUFACTURER_STRING	"Microchip"

#घोषणा USB251XB_ADDR_PRODUCT_STRING_LEN	0x14
#घोषणा USB251XB_ADDR_PRODUCT_STRING		0x54

#घोषणा USB251XB_ADDR_SERIAL_STRING_LEN		0x15
#घोषणा USB251XB_ADDR_SERIAL_STRING		0x92
#घोषणा USB251XB_DEF_SERIAL_STRING		""

#घोषणा USB251XB_ADDR_BATTERY_CHARGING_ENABLE	0xD0
#घोषणा USB251XB_DEF_BATTERY_CHARGING_ENABLE	0x00

#घोषणा USB251XB_ADDR_BOOST_UP	0xF6
#घोषणा USB251XB_DEF_BOOST_UP	0x00
#घोषणा USB251XB_ADDR_BOOST_57	0xF7
#घोषणा USB251XB_DEF_BOOST_57	0x00
#घोषणा USB251XB_ADDR_BOOST_14	0xF8
#घोषणा USB251XB_DEF_BOOST_14	0x00

#घोषणा USB251XB_ADDR_PORT_SWAP	0xFA
#घोषणा USB251XB_DEF_PORT_SWAP	0x00

#घोषणा USB251XB_ADDR_PORT_MAP_12	0xFB
#घोषणा USB251XB_DEF_PORT_MAP_12	0x00
#घोषणा USB251XB_ADDR_PORT_MAP_34	0xFC
#घोषणा USB251XB_DEF_PORT_MAP_34	0x00 /* USB251अणु3B/i,4B/i,7/iपूर्ण only */
#घोषणा USB251XB_ADDR_PORT_MAP_56	0xFD
#घोषणा USB251XB_DEF_PORT_MAP_56	0x00 /* USB2517/i only */
#घोषणा USB251XB_ADDR_PORT_MAP_7	0xFE
#घोषणा USB251XB_DEF_PORT_MAP_7		0x00 /* USB2517/i only */

#घोषणा USB251XB_ADDR_STATUS_COMMAND		0xFF
#घोषणा USB251XB_STATUS_COMMAND_SMBUS_DOWN	0x04
#घोषणा USB251XB_STATUS_COMMAND_RESET		0x02
#घोषणा USB251XB_STATUS_COMMAND_ATTACH		0x01

#घोषणा USB251XB_I2C_REG_SZ	0x100
#घोषणा USB251XB_I2C_WRITE_SZ	0x10

#घोषणा DRIVER_NAME	"usb251xb"
#घोषणा DRIVER_DESC	"Microchip USB 2.0 Hi-Speed Hub Controller"

काष्ठा usb251xb अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *i2c;
	काष्ठा regulator *vdd;
	u8 skip_config;
	काष्ठा gpio_desc *gpio_reset;
	u16 venकरोr_id;
	u16 product_id;
	u16 device_id;
	u8  conf_data1;
	u8  conf_data2;
	u8  conf_data3;
	u8  non_rem_dev;
	u8  port_disable_sp;
	u8  port_disable_bp;
	u8  max_घातer_sp;
	u8  max_घातer_bp;
	u8  max_current_sp;
	u8  max_current_bp;
	u8  घातer_on_समय;
	u16 lang_id;
	u8 manufacturer_len;
	u8 product_len;
	u8 serial_len;
	अक्षर manufacturer[USB251XB_STRING_बफ_मानE];
	अक्षर product[USB251XB_STRING_बफ_मानE];
	अक्षर serial[USB251XB_STRING_बफ_मानE];
	u8  bat_अक्षरge_en;
	u8  boost_up;
	u8  boost_57;
	u8  boost_14;
	u8  port_swap;
	u8  port_map12;
	u8  port_map34;
	u8  port_map56;
	u8  port_map7;
	u8  status;
पूर्ण;

काष्ठा usb251xb_data अणु
	u16 product_id;
	u8 port_cnt;
	bool led_support;
	bool bat_support;
	अक्षर product_str[USB251XB_STRING_बफ_मानE / 2]; /* ASCII string */
पूर्ण;

अटल स्थिर काष्ठा usb251xb_data usb2422_data = अणु
	.product_id = 0x2422,
	.port_cnt = 2,
	.led_support = false,
	.bat_support = true,
	.product_str = "USB2422",
पूर्ण;

अटल स्थिर काष्ठा usb251xb_data usb2512b_data = अणु
	.product_id = 0x2512,
	.port_cnt = 2,
	.led_support = false,
	.bat_support = true,
	.product_str = "USB2512B",
पूर्ण;

अटल स्थिर काष्ठा usb251xb_data usb2512bi_data = अणु
	.product_id = 0x2512,
	.port_cnt = 2,
	.led_support = false,
	.bat_support = true,
	.product_str = "USB2512Bi",
पूर्ण;

अटल स्थिर काष्ठा usb251xb_data usb2513b_data = अणु
	.product_id = 0x2513,
	.port_cnt = 3,
	.led_support = false,
	.bat_support = true,
	.product_str = "USB2513B",
पूर्ण;

अटल स्थिर काष्ठा usb251xb_data usb2513bi_data = अणु
	.product_id = 0x2513,
	.port_cnt = 3,
	.led_support = false,
	.bat_support = true,
	.product_str = "USB2513Bi",
पूर्ण;

अटल स्थिर काष्ठा usb251xb_data usb2514b_data = अणु
	.product_id = 0x2514,
	.port_cnt = 4,
	.led_support = false,
	.bat_support = true,
	.product_str = "USB2514B",
पूर्ण;

अटल स्थिर काष्ठा usb251xb_data usb2514bi_data = अणु
	.product_id = 0x2514,
	.port_cnt = 4,
	.led_support = false,
	.bat_support = true,
	.product_str = "USB2514Bi",
पूर्ण;

अटल स्थिर काष्ठा usb251xb_data usb2517_data = अणु
	.product_id = 0x2517,
	.port_cnt = 7,
	.led_support = true,
	.bat_support = false,
	.product_str = "USB2517",
पूर्ण;

अटल स्थिर काष्ठा usb251xb_data usb2517i_data = अणु
	.product_id = 0x2517,
	.port_cnt = 7,
	.led_support = true,
	.bat_support = false,
	.product_str = "USB2517i",
पूर्ण;

#अगर_घोषित CONFIG_GPIOLIB
अटल पूर्णांक usb251xb_check_dev_children(काष्ठा device *dev, व्योम *child)
अणु
	अगर (dev->type == &i2c_adapter_type) अणु
		वापस device_क्रम_each_child(dev, child,
					     usb251xb_check_dev_children);
	पूर्ण

	वापस (dev == child);
पूर्ण

अटल पूर्णांक usb251x_check_gpio_chip(काष्ठा usb251xb *hub)
अणु
	काष्ठा gpio_chip *gc = gpiod_to_chip(hub->gpio_reset);
	काष्ठा i2c_adapter *adap = hub->i2c->adapter;
	पूर्णांक ret;

	अगर (!hub->gpio_reset)
		वापस 0;

	अगर (!gc)
		वापस -EINVAL;

	ret = usb251xb_check_dev_children(&adap->dev, gc->parent);
	अगर (ret) अणु
		dev_err(hub->dev, "Reset GPIO chip is at the same i2c-bus\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक usb251x_check_gpio_chip(काष्ठा usb251xb *hub)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम usb251xb_reset(काष्ठा usb251xb *hub)
अणु
	अगर (!hub->gpio_reset)
		वापस;

	i2c_lock_bus(hub->i2c->adapter, I2C_LOCK_SEGMENT);

	gpiod_set_value_cansleep(hub->gpio_reset, 1);
	usleep_range(1, 10);	/* >=1us RESET_N निश्चितed */
	gpiod_set_value_cansleep(hub->gpio_reset, 0);

	/* रुको क्रम hub recovery/stabilization */
	usleep_range(500, 750);	/* >=500us after RESET_N deनिश्चितed */

	i2c_unlock_bus(hub->i2c->adapter, I2C_LOCK_SEGMENT);
पूर्ण

अटल पूर्णांक usb251xb_connect(काष्ठा usb251xb *hub)
अणु
	काष्ठा device *dev = hub->dev;
	पूर्णांक err, i;
	अक्षर i2c_wb[USB251XB_I2C_REG_SZ];

	स_रखो(i2c_wb, 0, USB251XB_I2C_REG_SZ);

	अगर (hub->skip_config) अणु
		dev_info(dev, "Skip hub configuration, only attach.\n");
		i2c_wb[0] = 0x01;
		i2c_wb[1] = USB251XB_STATUS_COMMAND_ATTACH;

		usb251xb_reset(hub);

		err = i2c_smbus_ग_लिखो_i2c_block_data(hub->i2c,
				USB251XB_ADDR_STATUS_COMMAND, 2, i2c_wb);
		अगर (err) अणु
			dev_err(dev, "attaching hub failed: %d\n", err);
			वापस err;
		पूर्ण
		वापस 0;
	पूर्ण

	i2c_wb[USB251XB_ADDR_VENDOR_ID_MSB]     = (hub->venकरोr_id >> 8) & 0xFF;
	i2c_wb[USB251XB_ADDR_VENDOR_ID_LSB]     = hub->venकरोr_id & 0xFF;
	i2c_wb[USB251XB_ADDR_PRODUCT_ID_MSB]    = (hub->product_id >> 8) & 0xFF;
	i2c_wb[USB251XB_ADDR_PRODUCT_ID_LSB]    = hub->product_id & 0xFF;
	i2c_wb[USB251XB_ADDR_DEVICE_ID_MSB]     = (hub->device_id >> 8) & 0xFF;
	i2c_wb[USB251XB_ADDR_DEVICE_ID_LSB]     = hub->device_id & 0xFF;
	i2c_wb[USB251XB_ADDR_CONFIG_DATA_1]     = hub->conf_data1;
	i2c_wb[USB251XB_ADDR_CONFIG_DATA_2]     = hub->conf_data2;
	i2c_wb[USB251XB_ADDR_CONFIG_DATA_3]     = hub->conf_data3;
	i2c_wb[USB251XB_ADDR_NON_REMOVABLE_DEVICES] = hub->non_rem_dev;
	i2c_wb[USB251XB_ADDR_PORT_DISABLE_SELF] = hub->port_disable_sp;
	i2c_wb[USB251XB_ADDR_PORT_DISABLE_BUS]  = hub->port_disable_bp;
	i2c_wb[USB251XB_ADDR_MAX_POWER_SELF]    = hub->max_घातer_sp;
	i2c_wb[USB251XB_ADDR_MAX_POWER_BUS]     = hub->max_घातer_bp;
	i2c_wb[USB251XB_ADDR_MAX_CURRENT_SELF]  = hub->max_current_sp;
	i2c_wb[USB251XB_ADDR_MAX_CURRENT_BUS]   = hub->max_current_bp;
	i2c_wb[USB251XB_ADDR_POWER_ON_TIME]     = hub->घातer_on_समय;
	i2c_wb[USB251XB_ADDR_LANGUAGE_ID_HIGH]  = (hub->lang_id >> 8) & 0xFF;
	i2c_wb[USB251XB_ADDR_LANGUAGE_ID_LOW]   = hub->lang_id & 0xFF;
	i2c_wb[USB251XB_ADDR_MANUFACTURER_STRING_LEN] = hub->manufacturer_len;
	i2c_wb[USB251XB_ADDR_PRODUCT_STRING_LEN]      = hub->product_len;
	i2c_wb[USB251XB_ADDR_SERIAL_STRING_LEN]       = hub->serial_len;
	स_नकल(&i2c_wb[USB251XB_ADDR_MANUFACTURER_STRING], hub->manufacturer,
	       USB251XB_STRING_बफ_मानE);
	स_नकल(&i2c_wb[USB251XB_ADDR_SERIAL_STRING], hub->serial,
	       USB251XB_STRING_बफ_मानE);
	स_नकल(&i2c_wb[USB251XB_ADDR_PRODUCT_STRING], hub->product,
	       USB251XB_STRING_बफ_मानE);
	i2c_wb[USB251XB_ADDR_BATTERY_CHARGING_ENABLE] = hub->bat_अक्षरge_en;
	i2c_wb[USB251XB_ADDR_BOOST_UP]          = hub->boost_up;
	i2c_wb[USB251XB_ADDR_BOOST_57]          = hub->boost_57;
	i2c_wb[USB251XB_ADDR_BOOST_14]          = hub->boost_14;
	i2c_wb[USB251XB_ADDR_PORT_SWAP]         = hub->port_swap;
	i2c_wb[USB251XB_ADDR_PORT_MAP_12]       = hub->port_map12;
	i2c_wb[USB251XB_ADDR_PORT_MAP_34]       = hub->port_map34;
	i2c_wb[USB251XB_ADDR_PORT_MAP_56]       = hub->port_map56;
	i2c_wb[USB251XB_ADDR_PORT_MAP_7]        = hub->port_map7;
	i2c_wb[USB251XB_ADDR_STATUS_COMMAND] = USB251XB_STATUS_COMMAND_ATTACH;

	usb251xb_reset(hub);

	/* ग_लिखो रेजिस्टरs */
	क्रम (i = 0; i < (USB251XB_I2C_REG_SZ / USB251XB_I2C_WRITE_SZ); i++) अणु
		पूर्णांक offset = i * USB251XB_I2C_WRITE_SZ;
		अक्षर wbuf[USB251XB_I2C_WRITE_SZ + 1];

		/* The first data byte transferred tells the hub how many data
		 * bytes will follow (byte count).
		 */
		wbuf[0] = USB251XB_I2C_WRITE_SZ;
		स_नकल(&wbuf[1], &i2c_wb[offset], USB251XB_I2C_WRITE_SZ);

		dev_dbg(dev, "writing %d byte block %d to 0x%02X\n",
			USB251XB_I2C_WRITE_SZ, i, offset);

		err = i2c_smbus_ग_लिखो_i2c_block_data(hub->i2c, offset,
						     USB251XB_I2C_WRITE_SZ + 1,
						     wbuf);
		अगर (err)
			जाओ out_err;
	पूर्ण

	dev_info(dev, "Hub configuration was successful.\n");
	वापस 0;

out_err:
	dev_err(dev, "configuring block %d failed: %d\n", i, err);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल व्योम usb251xb_get_ports_field(काष्ठा usb251xb *hub,
				    स्थिर अक्षर *prop_name, u8 port_cnt,
				    bool ds_only, u8 *fld)
अणु
	काष्ठा device *dev = hub->dev;
	काष्ठा property *prop;
	स्थिर __be32 *p;
	u32 port;

	of_property_क्रम_each_u32(dev->of_node, prop_name, prop, p, port) अणु
		अगर ((port >= ds_only ? 1 : 0) && (port <= port_cnt))
			*fld |= BIT(port);
		अन्यथा
			dev_warn(dev, "port %u doesn't exist\n", port);
	पूर्ण
पूर्ण

अटल पूर्णांक usb251xb_get_ofdata(काष्ठा usb251xb *hub,
			       स्थिर काष्ठा usb251xb_data *data)
अणु
	काष्ठा device *dev = hub->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक len, err;
	u32 property_u32 = 0;
	स्थिर अक्षर *cproperty_अक्षर;
	अक्षर str[USB251XB_STRING_बफ_मानE / 2];

	अगर (!np) अणु
		dev_err(dev, "failed to get ofdata\n");
		वापस -ENODEV;
	पूर्ण

	अगर (of_get_property(np, "skip-config", शून्य))
		hub->skip_config = 1;
	अन्यथा
		hub->skip_config = 0;

	hub->gpio_reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	अगर (PTR_ERR(hub->gpio_reset) == -EPROBE_DEFER) अणु
		वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अगर (IS_ERR(hub->gpio_reset)) अणु
		err = PTR_ERR(hub->gpio_reset);
		dev_err(dev, "unable to request GPIO reset pin (%d)\n", err);
		वापस err;
	पूर्ण

	अगर (of_property_पढ़ो_u16_array(np, "vendor-id", &hub->venकरोr_id, 1))
		hub->venकरोr_id = USB251XB_DEF_VENDOR_ID;

	अगर (of_property_पढ़ो_u16_array(np, "product-id",
				       &hub->product_id, 1))
		hub->product_id = data->product_id;

	अगर (of_property_पढ़ो_u16_array(np, "device-id", &hub->device_id, 1))
		hub->device_id = USB251XB_DEF_DEVICE_ID;

	hub->conf_data1 = USB251XB_DEF_CONFIG_DATA_1;
	अगर (of_get_property(np, "self-powered", शून्य)) अणु
		hub->conf_data1 |= BIT(7);

		/* Configure Over-Current sens when self-घातered */
		hub->conf_data1 &= ~BIT(2);
		अगर (of_get_property(np, "ganged-sensing", शून्य))
			hub->conf_data1 &= ~BIT(1);
		अन्यथा अगर (of_get_property(np, "individual-sensing", शून्य))
			hub->conf_data1 |= BIT(1);
	पूर्ण अन्यथा अगर (of_get_property(np, "bus-powered", शून्य)) अणु
		hub->conf_data1 &= ~BIT(7);

		/* Disable Over-Current sense when bus-घातered */
		hub->conf_data1 |= BIT(2);
	पूर्ण

	अगर (of_get_property(np, "disable-hi-speed", शून्य))
		hub->conf_data1 |= BIT(5);

	अगर (of_get_property(np, "multi-tt", शून्य))
		hub->conf_data1 |= BIT(4);
	अन्यथा अगर (of_get_property(np, "single-tt", शून्य))
		hub->conf_data1 &= ~BIT(4);

	अगर (of_get_property(np, "disable-eop", शून्य))
		hub->conf_data1 |= BIT(3);

	अगर (of_get_property(np, "individual-port-switching", शून्य))
		hub->conf_data1 |= BIT(0);
	अन्यथा अगर (of_get_property(np, "ganged-port-switching", शून्य))
		hub->conf_data1 &= ~BIT(0);

	hub->conf_data2 = USB251XB_DEF_CONFIG_DATA_2;
	अगर (of_get_property(np, "dynamic-power-switching", शून्य))
		hub->conf_data2 |= BIT(7);

	अगर (!of_property_पढ़ो_u32(np, "oc-delay-us", &property_u32)) अणु
		अगर (property_u32 == 100) अणु
			/* 100 us*/
			hub->conf_data2 &= ~BIT(5);
			hub->conf_data2 &= ~BIT(4);
		पूर्ण अन्यथा अगर (property_u32 == 4000) अणु
			/* 4 ms */
			hub->conf_data2 &= ~BIT(5);
			hub->conf_data2 |= BIT(4);
		पूर्ण अन्यथा अगर (property_u32 == 16000) अणु
			/* 16 ms */
			hub->conf_data2 |= BIT(5);
			hub->conf_data2 |= BIT(4);
		पूर्ण अन्यथा अणु
			/* 8 ms (DEFAULT) */
			hub->conf_data2 |= BIT(5);
			hub->conf_data2 &= ~BIT(4);
		पूर्ण
	पूर्ण

	अगर (of_get_property(np, "compound-device", शून्य))
		hub->conf_data2 |= BIT(3);

	hub->conf_data3 = USB251XB_DEF_CONFIG_DATA_3;
	अगर (of_get_property(np, "port-mapping-mode", शून्य))
		hub->conf_data3 |= BIT(3);

	अगर (data->led_support && of_get_property(np, "led-usb-mode", शून्य))
		hub->conf_data3 &= ~BIT(1);

	अगर (of_get_property(np, "string-support", शून्य))
		hub->conf_data3 |= BIT(0);

	hub->non_rem_dev = USB251XB_DEF_NON_REMOVABLE_DEVICES;
	usb251xb_get_ports_field(hub, "non-removable-ports", data->port_cnt,
				 true, &hub->non_rem_dev);

	hub->port_disable_sp = USB251XB_DEF_PORT_DISABLE_SELF;
	usb251xb_get_ports_field(hub, "sp-disabled-ports", data->port_cnt,
				 true, &hub->port_disable_sp);

	hub->port_disable_bp = USB251XB_DEF_PORT_DISABLE_BUS;
	usb251xb_get_ports_field(hub, "bp-disabled-ports", data->port_cnt,
				 true, &hub->port_disable_bp);

	hub->max_घातer_sp = USB251XB_DEF_MAX_POWER_SELF;
	अगर (!of_property_पढ़ो_u32(np, "sp-max-total-current-microamp",
	    &property_u32))
		hub->max_घातer_sp = min_t(u8, property_u32 / 2000, 50);

	hub->max_घातer_bp = USB251XB_DEF_MAX_POWER_BUS;
	अगर (!of_property_पढ़ो_u32(np, "bp-max-total-current-microamp",
	    &property_u32))
		hub->max_घातer_bp = min_t(u8, property_u32 / 2000, 255);

	hub->max_current_sp = USB251XB_DEF_MAX_CURRENT_SELF;
	अगर (!of_property_पढ़ो_u32(np, "sp-max-removable-current-microamp",
	    &property_u32))
		hub->max_current_sp = min_t(u8, property_u32 / 2000, 50);

	hub->max_current_bp = USB251XB_DEF_MAX_CURRENT_BUS;
	अगर (!of_property_पढ़ो_u32(np, "bp-max-removable-current-microamp",
	    &property_u32))
		hub->max_current_bp = min_t(u8, property_u32 / 2000, 255);

	hub->घातer_on_समय = USB251XB_DEF_POWER_ON_TIME;
	अगर (!of_property_पढ़ो_u32(np, "power-on-time-ms", &property_u32))
		hub->घातer_on_समय = min_t(u8, property_u32 / 2, 255);

	अगर (of_property_पढ़ो_u16_array(np, "language-id", &hub->lang_id, 1))
		hub->lang_id = USB251XB_DEF_LANGUAGE_ID;

	cproperty_अक्षर = of_get_property(np, "manufacturer", शून्य);
	strlcpy(str, cproperty_अक्षर ? : USB251XB_DEF_MANUFACTURER_STRING,
		माप(str));
	hub->manufacturer_len = म_माप(str) & 0xFF;
	स_रखो(hub->manufacturer, 0, USB251XB_STRING_बफ_मानE);
	len = min_t(माप_प्रकार, USB251XB_STRING_बफ_मानE / 2, म_माप(str));
	len = utf8s_to_utf16s(str, len, UTF16_LITTLE_ENDIAN,
			      (ब_अक्षर_प्रकार *)hub->manufacturer,
			      USB251XB_STRING_बफ_मानE);

	cproperty_अक्षर = of_get_property(np, "product", शून्य);
	strlcpy(str, cproperty_अक्षर ? : data->product_str, माप(str));
	hub->product_len = म_माप(str) & 0xFF;
	स_रखो(hub->product, 0, USB251XB_STRING_बफ_मानE);
	len = min_t(माप_प्रकार, USB251XB_STRING_बफ_मानE / 2, म_माप(str));
	len = utf8s_to_utf16s(str, len, UTF16_LITTLE_ENDIAN,
			      (ब_अक्षर_प्रकार *)hub->product,
			      USB251XB_STRING_बफ_मानE);

	cproperty_अक्षर = of_get_property(np, "serial", शून्य);
	strlcpy(str, cproperty_अक्षर ? : USB251XB_DEF_SERIAL_STRING,
		माप(str));
	hub->serial_len = म_माप(str) & 0xFF;
	स_रखो(hub->serial, 0, USB251XB_STRING_बफ_मानE);
	len = min_t(माप_प्रकार, USB251XB_STRING_बफ_मानE / 2, म_माप(str));
	len = utf8s_to_utf16s(str, len, UTF16_LITTLE_ENDIAN,
			      (ब_अक्षर_प्रकार *)hub->serial,
			      USB251XB_STRING_बफ_मानE);

	/*
	 * The datasheet करोcuments the रेजिस्टर as 'Port Swap' but in real the
	 * रेजिस्टर controls the USB DP/DM संकेत swapping क्रम each port.
	 */
	hub->port_swap = USB251XB_DEF_PORT_SWAP;
	usb251xb_get_ports_field(hub, "swap-dx-lanes", data->port_cnt,
				 false, &hub->port_swap);

	/* The following parameters are currently not exposed to devicetree, but
	 * may be as soon as needed.
	 */
	hub->bat_अक्षरge_en = USB251XB_DEF_BATTERY_CHARGING_ENABLE;
	hub->boost_up = USB251XB_DEF_BOOST_UP;
	hub->boost_57 = USB251XB_DEF_BOOST_57;
	hub->boost_14 = USB251XB_DEF_BOOST_14;
	hub->port_map12 = USB251XB_DEF_PORT_MAP_12;
	hub->port_map34 = USB251XB_DEF_PORT_MAP_34;
	hub->port_map56 = USB251XB_DEF_PORT_MAP_56;
	hub->port_map7  = USB251XB_DEF_PORT_MAP_7;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id usb251xb_of_match[] = अणु
	अणु
		.compatible = "microchip,usb2422",
		.data = &usb2422_data,
	पूर्ण, अणु
		.compatible = "microchip,usb2512b",
		.data = &usb2512b_data,
	पूर्ण, अणु
		.compatible = "microchip,usb2512bi",
		.data = &usb2512bi_data,
	पूर्ण, अणु
		.compatible = "microchip,usb2513b",
		.data = &usb2513b_data,
	पूर्ण, अणु
		.compatible = "microchip,usb2513bi",
		.data = &usb2513bi_data,
	पूर्ण, अणु
		.compatible = "microchip,usb2514b",
		.data = &usb2514b_data,
	पूर्ण, अणु
		.compatible = "microchip,usb2514bi",
		.data = &usb2514bi_data,
	पूर्ण, अणु
		.compatible = "microchip,usb2517",
		.data = &usb2517_data,
	पूर्ण, अणु
		.compatible = "microchip,usb2517i",
		.data = &usb2517i_data,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, usb251xb_of_match);
#अन्यथा /* CONFIG_OF */
अटल पूर्णांक usb251xb_get_ofdata(काष्ठा usb251xb *hub,
			       स्थिर काष्ठा usb251xb_data *data)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल व्योम usb251xb_regulator_disable_action(व्योम *data)
अणु
	काष्ठा usb251xb *hub = data;

	regulator_disable(hub->vdd);
पूर्ण

अटल पूर्णांक usb251xb_probe(काष्ठा usb251xb *hub)
अणु
	काष्ठा device *dev = hub->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा usb251xb_data *usb_data = of_device_get_match_data(dev);
	पूर्णांक err;

	अगर (np && usb_data) अणु
		err = usb251xb_get_ofdata(hub, usb_data);
		अगर (err) अणु
			dev_err(dev, "failed to get ofdata: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	/*
	 * usb251x SMBus-slave SCL lane is muxed with CFG_SEL0 pin. So अगर anyone
	 * tries to work with the bus at the moment the hub reset is released,
	 * it may cause an invalid config being latched by usb251x. Particularly
	 * one of the config modes makes the hub loading a शेष रेजिस्टरs
	 * value without SMBus-slave पूर्णांकerface activation. If the hub
	 * accidentally माला_लो this mode, this will cause the driver SMBus-
	 * functions failure. Normally we could just lock the SMBus-segment the
	 * hub i2c-पूर्णांकerface resides क्रम the device-specअगरic reset timing. But
	 * the GPIO controller, which is used to handle the hub reset, might be
	 * placed at the same i2c-bus segment. In this हाल an error should be
	 * वापसed since we can't safely use the GPIO controller to clear the
	 * reset state (it may affect the hub configuration) and we can't lock
	 * the i2c-bus segment (it will cause a deadlock).
	 */
	err = usb251x_check_gpio_chip(hub);
	अगर (err)
		वापस err;

	hub->vdd = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(hub->vdd))
		वापस PTR_ERR(hub->vdd);

	err = regulator_enable(hub->vdd);
	अगर (err)
		वापस err;

	err = devm_add_action_or_reset(dev,
				       usb251xb_regulator_disable_action, hub);
	अगर (err)
		वापस err;

	err = usb251xb_connect(hub);
	अगर (err) अणु
		dev_err(dev, "Failed to connect hub (%d)\n", err);
		वापस err;
	पूर्ण

	dev_info(dev, "Hub probed successfully\n");

	वापस 0;
पूर्ण

अटल पूर्णांक usb251xb_i2c_probe(काष्ठा i2c_client *i2c,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा usb251xb *hub;

	hub = devm_kzalloc(&i2c->dev, माप(काष्ठा usb251xb), GFP_KERNEL);
	अगर (!hub)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, hub);
	hub->dev = &i2c->dev;
	hub->i2c = i2c;

	वापस usb251xb_probe(hub);
पूर्ण

अटल पूर्णांक __maybe_unused usb251xb_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा usb251xb *hub = i2c_get_clientdata(client);

	वापस regulator_disable(hub->vdd);
पूर्ण

अटल पूर्णांक __maybe_unused usb251xb_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा usb251xb *hub = i2c_get_clientdata(client);
	पूर्णांक err;

	err = regulator_enable(hub->vdd);
	अगर (err)
		वापस err;

	वापस usb251xb_connect(hub);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(usb251xb_pm_ops, usb251xb_suspend, usb251xb_resume);

अटल स्थिर काष्ठा i2c_device_id usb251xb_id[] = अणु
	अणु "usb2422", 0 पूर्ण,
	अणु "usb2512b", 0 पूर्ण,
	अणु "usb2512bi", 0 पूर्ण,
	अणु "usb2513b", 0 पूर्ण,
	अणु "usb2513bi", 0 पूर्ण,
	अणु "usb2514b", 0 पूर्ण,
	अणु "usb2514bi", 0 पूर्ण,
	अणु "usb2517", 0 पूर्ण,
	अणु "usb2517i", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, usb251xb_id);

अटल काष्ठा i2c_driver usb251xb_i2c_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = of_match_ptr(usb251xb_of_match),
		.pm = &usb251xb_pm_ops,
	पूर्ण,
	.probe    = usb251xb_i2c_probe,
	.id_table = usb251xb_id,
पूर्ण;

module_i2c_driver(usb251xb_i2c_driver);

MODULE_AUTHOR("Richard Leitner <richard.leitner@skidata.com>");
MODULE_DESCRIPTION("USB251x/xBi USB 2.0 Hub Controller Driver");
MODULE_LICENSE("GPL");
