<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/leds/leds-as3645a.c - AS3645A and LM3555 flash controllers driver
 *
 * Copyright (C) 2008-2011 Nokia Corporation
 * Copyright (c) 2011, 2017 Intel Corporation.
 *
 * Based on drivers/media/i2c/as3645a.c.
 *
 * Contact: Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/led-class-flash.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-flash-led-class.h>

#घोषणा AS_TIMER_US_TO_CODE(t)			(((t) / 1000 - 100) / 50)
#घोषणा AS_TIMER_CODE_TO_US(c)			((50 * (c) + 100) * 1000)

/* Register definitions */

/* Read-only Design info रेजिस्टर: Reset state: xxxx 0001 */
#घोषणा AS_DESIGN_INFO_REG			0x00
#घोषणा AS_DESIGN_INFO_FACTORY(x)		(((x) >> 4))
#घोषणा AS_DESIGN_INFO_MODEL(x)			((x) & 0x0f)

/* Read-only Version control रेजिस्टर: Reset state: 0000 0000
 * क्रम first engineering samples
 */
#घोषणा AS_VERSION_CONTROL_REG			0x01
#घोषणा AS_VERSION_CONTROL_RFU(x)		(((x) >> 4))
#घोषणा AS_VERSION_CONTROL_VERSION(x)		((x) & 0x0f)

/* Read / Write	(Indicator and समयr रेजिस्टर): Reset state: 0000 1111 */
#घोषणा AS_INDICATOR_AND_TIMER_REG		0x02
#घोषणा AS_INDICATOR_AND_TIMER_TIMEOUT_SHIFT	0
#घोषणा AS_INDICATOR_AND_TIMER_VREF_SHIFT	4
#घोषणा AS_INDICATOR_AND_TIMER_INDICATOR_SHIFT	6

/* Read / Write	(Current set रेजिस्टर): Reset state: 0110 1001 */
#घोषणा AS_CURRENT_SET_REG			0x03
#घोषणा AS_CURRENT_ASSIST_LIGHT_SHIFT		0
#घोषणा AS_CURRENT_LED_DET_ON			(1 << 3)
#घोषणा AS_CURRENT_FLASH_CURRENT_SHIFT		4

/* Read / Write	(Control रेजिस्टर): Reset state: 1011 0100 */
#घोषणा AS_CONTROL_REG				0x04
#घोषणा AS_CONTROL_MODE_SETTING_SHIFT		0
#घोषणा AS_CONTROL_STROBE_ON			(1 << 2)
#घोषणा AS_CONTROL_OUT_ON			(1 << 3)
#घोषणा AS_CONTROL_EXT_TORCH_ON			(1 << 4)
#घोषणा AS_CONTROL_STROBE_TYPE_EDGE		(0 << 5)
#घोषणा AS_CONTROL_STROBE_TYPE_LEVEL		(1 << 5)
#घोषणा AS_CONTROL_COIL_PEAK_SHIFT		6

/* Read only (D3 is पढ़ो / ग_लिखो) (Fault and info): Reset state: 0000 x000 */
#घोषणा AS_FAULT_INFO_REG			0x05
#घोषणा AS_FAULT_INFO_INDUCTOR_PEAK_LIMIT	(1 << 1)
#घोषणा AS_FAULT_INFO_INDICATOR_LED		(1 << 2)
#घोषणा AS_FAULT_INFO_LED_AMOUNT		(1 << 3)
#घोषणा AS_FAULT_INFO_TIMEOUT			(1 << 4)
#घोषणा AS_FAULT_INFO_OVER_TEMPERATURE		(1 << 5)
#घोषणा AS_FAULT_INFO_SHORT_CIRCUIT		(1 << 6)
#घोषणा AS_FAULT_INFO_OVER_VOLTAGE		(1 << 7)

/* Boost रेजिस्टर */
#घोषणा AS_BOOST_REG				0x0d
#घोषणा AS_BOOST_CURRENT_DISABLE		(0 << 0)
#घोषणा AS_BOOST_CURRENT_ENABLE			(1 << 0)

/* Password रेजिस्टर is used to unlock boost रेजिस्टर writing */
#घोषणा AS_PASSWORD_REG				0x0f
#घोषणा AS_PASSWORD_UNLOCK_VALUE		0x55

#घोषणा AS_NAME					"as3645a"
#घोषणा AS_I2C_ADDR				(0x60 >> 1) /* W:0x60, R:0x61 */

#घोषणा AS_FLASH_TIMEOUT_MIN			100000	/* us */
#घोषणा AS_FLASH_TIMEOUT_MAX			850000
#घोषणा AS_FLASH_TIMEOUT_STEP			50000

#घोषणा AS_FLASH_INTENSITY_MIN			200000	/* uA */
#घोषणा AS_FLASH_INTENSITY_MAX_1LED		500000
#घोषणा AS_FLASH_INTENSITY_MAX_2LEDS		400000
#घोषणा AS_FLASH_INTENSITY_STEP			20000

#घोषणा AS_TORCH_INTENSITY_MIN			20000	/* uA */
#घोषणा AS_TORCH_INTENSITY_MAX			160000
#घोषणा AS_TORCH_INTENSITY_STEP			20000

#घोषणा AS_INDICATOR_INTENSITY_MIN		0	/* uA */
#घोषणा AS_INDICATOR_INTENSITY_MAX		10000
#घोषणा AS_INDICATOR_INTENSITY_STEP		2500

#घोषणा AS_PEAK_mA_MAX				2000
#घोषणा AS_PEAK_mA_TO_REG(a) \
	((min_t(u32, AS_PEAK_mA_MAX, a) - 1250) / 250)

/* LED numbers क्रम Devicetree */
#घोषणा AS_LED_FLASH				0
#घोषणा AS_LED_INDICATOR			1

क्रमागत as_mode अणु
	AS_MODE_EXT_TORCH = 0 << AS_CONTROL_MODE_SETTING_SHIFT,
	AS_MODE_INDICATOR = 1 << AS_CONTROL_MODE_SETTING_SHIFT,
	AS_MODE_ASSIST = 2 << AS_CONTROL_MODE_SETTING_SHIFT,
	AS_MODE_FLASH = 3 << AS_CONTROL_MODE_SETTING_SHIFT,
पूर्ण;

काष्ठा as3645a_config अणु
	u32 flash_समयout_us;
	u32 flash_max_ua;
	u32 assist_max_ua;
	u32 indicator_max_ua;
	u32 voltage_reference;
	u32 peak;
पूर्ण;

काष्ठा as3645a अणु
	काष्ठा i2c_client *client;

	काष्ठा mutex mutex;

	काष्ठा led_classdev_flash fled;
	काष्ठा led_classdev iled_cdev;

	काष्ठा v4l2_flash *vf;
	काष्ठा v4l2_flash *vfind;

	काष्ठा fwnode_handle *flash_node;
	काष्ठा fwnode_handle *indicator_node;

	काष्ठा as3645a_config cfg;

	क्रमागत as_mode mode;
	अचिन्हित पूर्णांक समयout;
	अचिन्हित पूर्णांक flash_current;
	अचिन्हित पूर्णांक assist_current;
	अचिन्हित पूर्णांक indicator_current;
	क्रमागत v4l2_flash_strobe_source strobe_source;
पूर्ण;

#घोषणा fled_to_as3645a(__fled) container_of(__fled, काष्ठा as3645a, fled)
#घोषणा iled_cdev_to_as3645a(__iled_cdev) \
	container_of(__iled_cdev, काष्ठा as3645a, iled_cdev)

/* Return negative त्रुटि_सं अन्यथा zero on success */
अटल पूर्णांक as3645a_ग_लिखो(काष्ठा as3645a *flash, u8 addr, u8 val)
अणु
	काष्ठा i2c_client *client = flash->client;
	पूर्णांक rval;

	rval = i2c_smbus_ग_लिखो_byte_data(client, addr, val);

	dev_dbg(&client->dev, "Write Addr:%02X Val:%02X %s\n", addr, val,
		rval < 0 ? "fail" : "ok");

	वापस rval;
पूर्ण

/* Return negative त्रुटि_सं अन्यथा a data byte received from the device. */
अटल पूर्णांक as3645a_पढ़ो(काष्ठा as3645a *flash, u8 addr)
अणु
	काष्ठा i2c_client *client = flash->client;
	पूर्णांक rval;

	rval = i2c_smbus_पढ़ो_byte_data(client, addr);

	dev_dbg(&client->dev, "Read Addr:%02X Val:%02X %s\n", addr, rval,
		rval < 0 ? "fail" : "ok");

	वापस rval;
पूर्ण

/* -----------------------------------------------------------------------------
 * Hardware configuration and trigger
 */

/**
 * as3645a_set_config - Set flash configuration रेजिस्टरs
 * @flash: The flash
 *
 * Configure the hardware with flash, assist and indicator currents, as well as
 * flash समयout.
 *
 * Return 0 on success, or a negative error code अगर an I2C communication error
 * occurred.
 */
अटल पूर्णांक as3645a_set_current(काष्ठा as3645a *flash)
अणु
	u8 val;

	val = (flash->flash_current << AS_CURRENT_FLASH_CURRENT_SHIFT)
	    | (flash->assist_current << AS_CURRENT_ASSIST_LIGHT_SHIFT)
	    | AS_CURRENT_LED_DET_ON;

	वापस as3645a_ग_लिखो(flash, AS_CURRENT_SET_REG, val);
पूर्ण

अटल पूर्णांक as3645a_set_समयout(काष्ठा as3645a *flash)
अणु
	u8 val;

	val = flash->समयout << AS_INDICATOR_AND_TIMER_TIMEOUT_SHIFT;

	val |= (flash->cfg.voltage_reference
		<< AS_INDICATOR_AND_TIMER_VREF_SHIFT)
	    |  ((flash->indicator_current ? flash->indicator_current - 1 : 0)
		 << AS_INDICATOR_AND_TIMER_INDICATOR_SHIFT);

	वापस as3645a_ग_लिखो(flash, AS_INDICATOR_AND_TIMER_REG, val);
पूर्ण

/**
 * as3645a_set_control - Set flash control रेजिस्टर
 * @flash: The flash
 * @mode: Desired output mode
 * @on: Desired output state
 *
 * Configure the hardware with output mode and state.
 *
 * Return 0 on success, or a negative error code अगर an I2C communication error
 * occurred.
 */
अटल पूर्णांक
as3645a_set_control(काष्ठा as3645a *flash, क्रमागत as_mode mode, bool on)
अणु
	u8 reg;

	/* Configure output parameters and operation mode. */
	reg = (flash->cfg.peak << AS_CONTROL_COIL_PEAK_SHIFT)
	    | (on ? AS_CONTROL_OUT_ON : 0)
	    | mode;

	अगर (mode == AS_MODE_FLASH &&
	    flash->strobe_source == V4L2_FLASH_STROBE_SOURCE_EXTERNAL)
		reg |= AS_CONTROL_STROBE_TYPE_LEVEL
		    |  AS_CONTROL_STROBE_ON;

	वापस as3645a_ग_लिखो(flash, AS_CONTROL_REG, reg);
पूर्ण

अटल पूर्णांक as3645a_get_fault(काष्ठा led_classdev_flash *fled, u32 *fault)
अणु
	काष्ठा as3645a *flash = fled_to_as3645a(fled);
	पूर्णांक rval;

	/* NOTE: पढ़ोing रेजिस्टर clears fault status */
	rval = as3645a_पढ़ो(flash, AS_FAULT_INFO_REG);
	अगर (rval < 0)
		वापस rval;

	अगर (rval & AS_FAULT_INFO_INDUCTOR_PEAK_LIMIT)
		*fault |= LED_FAULT_OVER_CURRENT;

	अगर (rval & AS_FAULT_INFO_INDICATOR_LED)
		*fault |= LED_FAULT_INDICATOR;

	dev_dbg(&flash->client->dev, "%u connected LEDs\n",
		rval & AS_FAULT_INFO_LED_AMOUNT ? 2 : 1);

	अगर (rval & AS_FAULT_INFO_TIMEOUT)
		*fault |= LED_FAULT_TIMEOUT;

	अगर (rval & AS_FAULT_INFO_OVER_TEMPERATURE)
		*fault |= LED_FAULT_OVER_TEMPERATURE;

	अगर (rval & AS_FAULT_INFO_SHORT_CIRCUIT)
		*fault |= LED_FAULT_OVER_CURRENT;

	अगर (rval & AS_FAULT_INFO_OVER_VOLTAGE)
		*fault |= LED_FAULT_INPUT_VOLTAGE;

	वापस rval;
पूर्ण

अटल अचिन्हित पूर्णांक __as3645a_current_to_reg(अचिन्हित पूर्णांक min, अचिन्हित पूर्णांक max,
					     अचिन्हित पूर्णांक step,
					     अचिन्हित पूर्णांक val)
अणु
	अगर (val < min)
		val = min;

	अगर (val > max)
		val = max;

	वापस (val - min) / step;
पूर्ण

अटल अचिन्हित पूर्णांक as3645a_current_to_reg(काष्ठा as3645a *flash, bool is_flash,
					   अचिन्हित पूर्णांक ua)
अणु
	अगर (is_flash)
		वापस __as3645a_current_to_reg(AS_TORCH_INTENSITY_MIN,
						flash->cfg.assist_max_ua,
						AS_TORCH_INTENSITY_STEP, ua);
	अन्यथा
		वापस __as3645a_current_to_reg(AS_FLASH_INTENSITY_MIN,
						flash->cfg.flash_max_ua,
						AS_FLASH_INTENSITY_STEP, ua);
पूर्ण

अटल पूर्णांक as3645a_set_indicator_brightness(काष्ठा led_classdev *iled_cdev,
					    क्रमागत led_brightness brightness)
अणु
	काष्ठा as3645a *flash = iled_cdev_to_as3645a(iled_cdev);
	पूर्णांक rval;

	flash->indicator_current = brightness;

	rval = as3645a_set_समयout(flash);
	अगर (rval)
		वापस rval;

	वापस as3645a_set_control(flash, AS_MODE_INDICATOR, brightness);
पूर्ण

अटल पूर्णांक as3645a_set_assist_brightness(काष्ठा led_classdev *fled_cdev,
					 क्रमागत led_brightness brightness)
अणु
	काष्ठा led_classdev_flash *fled = lcdev_to_flcdev(fled_cdev);
	काष्ठा as3645a *flash = fled_to_as3645a(fled);
	पूर्णांक rval;

	अगर (brightness) अणु
		/* Register value 0 is 20 mA. */
		flash->assist_current = brightness - 1;

		rval = as3645a_set_current(flash);
		अगर (rval)
			वापस rval;
	पूर्ण

	वापस as3645a_set_control(flash, AS_MODE_ASSIST, brightness);
पूर्ण

अटल पूर्णांक as3645a_set_flash_brightness(काष्ठा led_classdev_flash *fled,
					u32 brightness_ua)
अणु
	काष्ठा as3645a *flash = fled_to_as3645a(fled);

	flash->flash_current = as3645a_current_to_reg(flash, true,
						      brightness_ua);

	वापस as3645a_set_current(flash);
पूर्ण

अटल पूर्णांक as3645a_set_flash_समयout(काष्ठा led_classdev_flash *fled,
				     u32 समयout_us)
अणु
	काष्ठा as3645a *flash = fled_to_as3645a(fled);

	flash->समयout = AS_TIMER_US_TO_CODE(समयout_us);

	वापस as3645a_set_समयout(flash);
पूर्ण

अटल पूर्णांक as3645a_set_strobe(काष्ठा led_classdev_flash *fled, bool state)
अणु
	काष्ठा as3645a *flash = fled_to_as3645a(fled);

	वापस as3645a_set_control(flash, AS_MODE_FLASH, state);
पूर्ण

अटल स्थिर काष्ठा led_flash_ops as3645a_led_flash_ops = अणु
	.flash_brightness_set = as3645a_set_flash_brightness,
	.समयout_set = as3645a_set_flash_समयout,
	.strobe_set = as3645a_set_strobe,
	.fault_get = as3645a_get_fault,
पूर्ण;

अटल पूर्णांक as3645a_setup(काष्ठा as3645a *flash)
अणु
	काष्ठा device *dev = &flash->client->dev;
	u32 fault = 0;
	पूर्णांक rval;

	/* clear errors */
	rval = as3645a_पढ़ो(flash, AS_FAULT_INFO_REG);
	अगर (rval < 0)
		वापस rval;

	dev_dbg(dev, "Fault info: %02x\n", rval);

	rval = as3645a_set_current(flash);
	अगर (rval < 0)
		वापस rval;

	rval = as3645a_set_समयout(flash);
	अगर (rval < 0)
		वापस rval;

	rval = as3645a_set_control(flash, AS_MODE_INDICATOR, false);
	अगर (rval < 0)
		वापस rval;

	/* पढ़ो status */
	rval = as3645a_get_fault(&flash->fled, &fault);
	अगर (rval < 0)
		वापस rval;

	dev_dbg(dev, "AS_INDICATOR_AND_TIMER_REG: %02x\n",
		as3645a_पढ़ो(flash, AS_INDICATOR_AND_TIMER_REG));
	dev_dbg(dev, "AS_CURRENT_SET_REG: %02x\n",
		as3645a_पढ़ो(flash, AS_CURRENT_SET_REG));
	dev_dbg(dev, "AS_CONTROL_REG: %02x\n",
		as3645a_पढ़ो(flash, AS_CONTROL_REG));

	वापस rval & ~AS_FAULT_INFO_LED_AMOUNT ? -EIO : 0;
पूर्ण

अटल पूर्णांक as3645a_detect(काष्ठा as3645a *flash)
अणु
	काष्ठा device *dev = &flash->client->dev;
	पूर्णांक rval, man, model, rfu, version;
	स्थिर अक्षर *venकरोr;

	rval = as3645a_पढ़ो(flash, AS_DESIGN_INFO_REG);
	अगर (rval < 0) अणु
		dev_err(dev, "can't read design info reg\n");
		वापस rval;
	पूर्ण

	man = AS_DESIGN_INFO_FACTORY(rval);
	model = AS_DESIGN_INFO_MODEL(rval);

	rval = as3645a_पढ़ो(flash, AS_VERSION_CONTROL_REG);
	अगर (rval < 0) अणु
		dev_err(dev, "can't read version control reg\n");
		वापस rval;
	पूर्ण

	rfu = AS_VERSION_CONTROL_RFU(rval);
	version = AS_VERSION_CONTROL_VERSION(rval);

	/* Verअगरy the chip model and version. */
	अगर (model != 0x01 || rfu != 0x00) अणु
		dev_err(dev, "AS3645A not detected (model %d rfu %d)\n",
			model, rfu);
		वापस -ENODEV;
	पूर्ण

	चयन (man) अणु
	हाल 1:
		venकरोr = "AMS, Austria Micro Systems";
		अवरोध;
	हाल 2:
		venकरोr = "ADI, Analog Devices Inc.";
		अवरोध;
	हाल 3:
		venकरोr = "NSC, National Semiconductor";
		अवरोध;
	हाल 4:
		venकरोr = "NXP";
		अवरोध;
	हाल 5:
		venकरोr = "TI, Texas Instrument";
		अवरोध;
	शेष:
		venकरोr = "Unknown";
	पूर्ण

	dev_info(dev, "Chip vendor: %s (%d) Version: %d\n", venकरोr,
		 man, version);

	rval = as3645a_ग_लिखो(flash, AS_PASSWORD_REG, AS_PASSWORD_UNLOCK_VALUE);
	अगर (rval < 0)
		वापस rval;

	वापस as3645a_ग_लिखो(flash, AS_BOOST_REG, AS_BOOST_CURRENT_DISABLE);
पूर्ण

अटल पूर्णांक as3645a_parse_node(काष्ठा as3645a *flash,
			      काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा as3645a_config *cfg = &flash->cfg;
	काष्ठा fwnode_handle *child;
	पूर्णांक rval;

	fwnode_क्रम_each_child_node(fwnode, child) अणु
		u32 id = 0;

		fwnode_property_पढ़ो_u32(child, "reg", &id);

		चयन (id) अणु
		हाल AS_LED_FLASH:
			flash->flash_node = child;
			fwnode_handle_get(child);
			अवरोध;
		हाल AS_LED_INDICATOR:
			flash->indicator_node = child;
			fwnode_handle_get(child);
			अवरोध;
		शेष:
			dev_warn(&flash->client->dev,
				 "unknown LED %u encountered, ignoring\n", id);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!flash->flash_node) अणु
		dev_err(&flash->client->dev, "can't find flash node\n");
		वापस -ENODEV;
	पूर्ण

	rval = fwnode_property_पढ़ो_u32(flash->flash_node, "flash-timeout-us",
					&cfg->flash_समयout_us);
	अगर (rval < 0) अणु
		dev_err(&flash->client->dev,
			"can't read flash-timeout-us property for flash\n");
		जाओ out_err;
	पूर्ण

	rval = fwnode_property_पढ़ो_u32(flash->flash_node, "flash-max-microamp",
					&cfg->flash_max_ua);
	अगर (rval < 0) अणु
		dev_err(&flash->client->dev,
			"can't read flash-max-microamp property for flash\n");
		जाओ out_err;
	पूर्ण

	rval = fwnode_property_पढ़ो_u32(flash->flash_node, "led-max-microamp",
					&cfg->assist_max_ua);
	अगर (rval < 0) अणु
		dev_err(&flash->client->dev,
			"can't read led-max-microamp property for flash\n");
		जाओ out_err;
	पूर्ण

	fwnode_property_पढ़ो_u32(flash->flash_node, "voltage-reference",
				 &cfg->voltage_reference);

	fwnode_property_पढ़ो_u32(flash->flash_node, "ams,input-max-microamp",
				 &cfg->peak);
	cfg->peak = AS_PEAK_mA_TO_REG(cfg->peak);

	अगर (!flash->indicator_node) अणु
		dev_warn(&flash->client->dev,
			 "can't find indicator node\n");
		जाओ out_err;
	पूर्ण


	rval = fwnode_property_पढ़ो_u32(flash->indicator_node,
					"led-max-microamp",
					&cfg->indicator_max_ua);
	अगर (rval < 0) अणु
		dev_err(&flash->client->dev,
			"can't read led-max-microamp property for indicator\n");
		जाओ out_err;
	पूर्ण

	वापस 0;

out_err:
	fwnode_handle_put(flash->flash_node);
	fwnode_handle_put(flash->indicator_node);

	वापस rval;
पूर्ण

अटल पूर्णांक as3645a_led_class_setup(काष्ठा as3645a *flash)
अणु
	काष्ठा led_classdev *fled_cdev = &flash->fled.led_cdev;
	काष्ठा led_classdev *iled_cdev = &flash->iled_cdev;
	काष्ठा led_init_data init_data = अणुपूर्ण;
	काष्ठा led_flash_setting *cfg;
	पूर्णांक rval;

	iled_cdev->brightness_set_blocking = as3645a_set_indicator_brightness;
	iled_cdev->max_brightness =
		flash->cfg.indicator_max_ua / AS_INDICATOR_INTENSITY_STEP;
	iled_cdev->flags = LED_CORE_SUSPENDRESUME;

	init_data.fwnode = flash->indicator_node;
	init_data.devicename = AS_NAME;
	init_data.शेष_label = "indicator";

	rval = led_classdev_रेजिस्टर_ext(&flash->client->dev, iled_cdev,
					 &init_data);
	अगर (rval < 0)
		वापस rval;

	cfg = &flash->fled.brightness;
	cfg->min = AS_FLASH_INTENSITY_MIN;
	cfg->max = flash->cfg.flash_max_ua;
	cfg->step = AS_FLASH_INTENSITY_STEP;
	cfg->val = flash->cfg.flash_max_ua;

	cfg = &flash->fled.समयout;
	cfg->min = AS_FLASH_TIMEOUT_MIN;
	cfg->max = flash->cfg.flash_समयout_us;
	cfg->step = AS_FLASH_TIMEOUT_STEP;
	cfg->val = flash->cfg.flash_समयout_us;

	flash->fled.ops = &as3645a_led_flash_ops;

	fled_cdev->brightness_set_blocking = as3645a_set_assist_brightness;
	/* Value 0 is off in LED class. */
	fled_cdev->max_brightness =
		as3645a_current_to_reg(flash, false,
				       flash->cfg.assist_max_ua) + 1;
	fled_cdev->flags = LED_DEV_CAP_FLASH | LED_CORE_SUSPENDRESUME;

	init_data.fwnode = flash->flash_node;
	init_data.devicename = AS_NAME;
	init_data.शेष_label = "flash";

	rval = led_classdev_flash_रेजिस्टर_ext(&flash->client->dev,
					       &flash->fled, &init_data);
	अगर (rval)
		जाओ out_err;

	वापस rval;

out_err:
	led_classdev_unरेजिस्टर(iled_cdev);
	dev_err(&flash->client->dev,
		"led_classdev_flash_register() failed, error %d\n",
		rval);
	वापस rval;
पूर्ण

अटल पूर्णांक as3645a_v4l2_setup(काष्ठा as3645a *flash)
अणु
	काष्ठा led_classdev_flash *fled = &flash->fled;
	काष्ठा led_classdev *led = &fled->led_cdev;
	काष्ठा v4l2_flash_config cfg = अणु
		.पूर्णांकensity = अणु
			.min = AS_TORCH_INTENSITY_MIN,
			.max = flash->cfg.assist_max_ua,
			.step = AS_TORCH_INTENSITY_STEP,
			.val = flash->cfg.assist_max_ua,
		पूर्ण,
	पूर्ण;
	काष्ठा v4l2_flash_config cfgind = अणु
		.पूर्णांकensity = अणु
			.min = AS_INDICATOR_INTENSITY_MIN,
			.max = flash->cfg.indicator_max_ua,
			.step = AS_INDICATOR_INTENSITY_STEP,
			.val = flash->cfg.indicator_max_ua,
		पूर्ण,
	पूर्ण;

	strlcpy(cfg.dev_name, led->dev->kobj.name, माप(cfg.dev_name));
	strlcpy(cfgind.dev_name, flash->iled_cdev.dev->kobj.name,
		माप(cfgind.dev_name));

	flash->vf = v4l2_flash_init(
		&flash->client->dev, flash->flash_node, &flash->fled, शून्य,
		&cfg);
	अगर (IS_ERR(flash->vf))
		वापस PTR_ERR(flash->vf);

	flash->vfind = v4l2_flash_indicator_init(
		&flash->client->dev, flash->indicator_node, &flash->iled_cdev,
		&cfgind);
	अगर (IS_ERR(flash->vfind)) अणु
		v4l2_flash_release(flash->vf);
		वापस PTR_ERR(flash->vfind);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक as3645a_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा as3645a *flash;
	पूर्णांक rval;

	अगर (!dev_fwnode(&client->dev))
		वापस -ENODEV;

	flash = devm_kzalloc(&client->dev, माप(*flash), GFP_KERNEL);
	अगर (flash == शून्य)
		वापस -ENOMEM;

	flash->client = client;

	rval = as3645a_parse_node(flash, dev_fwnode(&client->dev));
	अगर (rval < 0)
		वापस rval;

	rval = as3645a_detect(flash);
	अगर (rval < 0)
		जाओ out_put_nodes;

	mutex_init(&flash->mutex);
	i2c_set_clientdata(client, flash);

	rval = as3645a_setup(flash);
	अगर (rval)
		जाओ out_mutex_destroy;

	rval = as3645a_led_class_setup(flash);
	अगर (rval)
		जाओ out_mutex_destroy;

	rval = as3645a_v4l2_setup(flash);
	अगर (rval)
		जाओ out_led_classdev_flash_unरेजिस्टर;

	वापस 0;

out_led_classdev_flash_unरेजिस्टर:
	led_classdev_flash_unरेजिस्टर(&flash->fled);

out_mutex_destroy:
	mutex_destroy(&flash->mutex);

out_put_nodes:
	fwnode_handle_put(flash->flash_node);
	fwnode_handle_put(flash->indicator_node);

	वापस rval;
पूर्ण

अटल पूर्णांक as3645a_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा as3645a *flash = i2c_get_clientdata(client);

	as3645a_set_control(flash, AS_MODE_EXT_TORCH, false);

	v4l2_flash_release(flash->vf);
	v4l2_flash_release(flash->vfind);

	led_classdev_flash_unरेजिस्टर(&flash->fled);
	led_classdev_unरेजिस्टर(&flash->iled_cdev);

	mutex_destroy(&flash->mutex);

	fwnode_handle_put(flash->flash_node);
	fwnode_handle_put(flash->indicator_node);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id as3645a_id_table[] = अणु
	अणु AS_NAME, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, as3645a_id_table);

अटल स्थिर काष्ठा of_device_id as3645a_of_table[] = अणु
	अणु .compatible = "ams,as3645a" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, as3645a_of_table);

अटल काष्ठा i2c_driver as3645a_i2c_driver = अणु
	.driver	= अणु
		.of_match_table = as3645a_of_table,
		.name = AS_NAME,
	पूर्ण,
	.probe_new	= as3645a_probe,
	.हटाओ	= as3645a_हटाओ,
	.id_table = as3645a_id_table,
पूर्ण;

module_i2c_driver(as3645a_i2c_driver);

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_AUTHOR("Sakari Ailus <sakari.ailus@iki.fi>");
MODULE_DESCRIPTION("LED flash driver for AS3645A, LM3555 and their clones");
MODULE_LICENSE("GPL v2");
