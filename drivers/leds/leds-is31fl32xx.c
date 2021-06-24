<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम ISSI IS31FL32xx family of I2C LED controllers
 *
 * Copyright 2015 Allworx Corp.
 *
 * Datasheets:
 *   http://www.issi.com/US/product-analog-fxled-driver.shपंचांगl
 *   http://www.si-en.com/product.asp?parentid=890
 */

#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

/* Used to indicate a device has no such रेजिस्टर */
#घोषणा IS31FL32XX_REG_NONE 0xFF

/* Software Shutकरोwn bit in Shutकरोwn Register */
#घोषणा IS31FL32XX_SHUTDOWN_SSD_ENABLE  0
#घोषणा IS31FL32XX_SHUTDOWN_SSD_DISABLE BIT(0)

/* IS31FL3216 has a number of unique रेजिस्टरs */
#घोषणा IS31FL3216_CONFIG_REG 0x00
#घोषणा IS31FL3216_LIGHTING_EFFECT_REG 0x03
#घोषणा IS31FL3216_CHANNEL_CONFIG_REG 0x04

/* Software Shutकरोwn bit in 3216 Config Register */
#घोषणा IS31FL3216_CONFIG_SSD_ENABLE  BIT(7)
#घोषणा IS31FL3216_CONFIG_SSD_DISABLE 0

काष्ठा is31fl32xx_priv;
काष्ठा is31fl32xx_led_data अणु
	काष्ठा led_classdev cdev;
	u8 channel; /* 1-based, max priv->cdef->channels */
	काष्ठा is31fl32xx_priv *priv;
पूर्ण;

काष्ठा is31fl32xx_priv अणु
	स्थिर काष्ठा is31fl32xx_chipdef *cdef;
	काष्ठा i2c_client *client;
	अचिन्हित पूर्णांक num_leds;
	काष्ठा is31fl32xx_led_data leds[];
पूर्ण;

/**
 * काष्ठा is31fl32xx_chipdef - chip-specअगरic attributes
 * @channels            : Number of LED channels
 * @shutकरोwn_reg        : address of Shutकरोwn रेजिस्टर (optional)
 * @pwm_update_reg      : address of PWM Update रेजिस्टर
 * @global_control_reg  : address of Global Control रेजिस्टर (optional)
 * @reset_reg           : address of Reset रेजिस्टर (optional)
 * @pwm_रेजिस्टर_base   : address of first PWM रेजिस्टर
 * @pwm_रेजिस्टरs_reversed: : true अगर PWM रेजिस्टरs count करोwn instead of up
 * @led_control_रेजिस्टर_base : address of first LED control रेजिस्टर (optional)
 * @enable_bits_per_led_control_रेजिस्टर: number of LEDs enable bits in each
 * @reset_func:         : poपूर्णांकer to reset function
 *
 * For all optional रेजिस्टर addresses, the sentinel value %IS31FL32XX_REG_NONE
 * indicates that this chip has no such रेजिस्टर.
 *
 * If non-शून्य, @reset_func will be called during probing to set all
 * necessary रेजिस्टरs to a known initialization state. This is needed
 * क्रम chips that करो not have a @reset_reg.
 *
 * @enable_bits_per_led_control_रेजिस्टर must be >=1 अगर
 * @led_control_रेजिस्टर_base != %IS31FL32XX_REG_NONE.
 */
काष्ठा is31fl32xx_chipdef अणु
	u8	channels;
	u8	shutकरोwn_reg;
	u8	pwm_update_reg;
	u8	global_control_reg;
	u8	reset_reg;
	u8	pwm_रेजिस्टर_base;
	bool	pwm_रेजिस्टरs_reversed;
	u8	led_control_रेजिस्टर_base;
	u8	enable_bits_per_led_control_रेजिस्टर;
	पूर्णांक (*reset_func)(काष्ठा is31fl32xx_priv *priv);
	पूर्णांक (*sw_shutकरोwn_func)(काष्ठा is31fl32xx_priv *priv, bool enable);
पूर्ण;

अटल स्थिर काष्ठा is31fl32xx_chipdef is31fl3236_cdef = अणु
	.channels				= 36,
	.shutकरोwn_reg				= 0x00,
	.pwm_update_reg				= 0x25,
	.global_control_reg			= 0x4a,
	.reset_reg				= 0x4f,
	.pwm_रेजिस्टर_base			= 0x01,
	.led_control_रेजिस्टर_base		= 0x26,
	.enable_bits_per_led_control_रेजिस्टर	= 1,
पूर्ण;

अटल स्थिर काष्ठा is31fl32xx_chipdef is31fl3235_cdef = अणु
	.channels				= 28,
	.shutकरोwn_reg				= 0x00,
	.pwm_update_reg				= 0x25,
	.global_control_reg			= 0x4a,
	.reset_reg				= 0x4f,
	.pwm_रेजिस्टर_base			= 0x05,
	.led_control_रेजिस्टर_base		= 0x2a,
	.enable_bits_per_led_control_रेजिस्टर	= 1,
पूर्ण;

अटल स्थिर काष्ठा is31fl32xx_chipdef is31fl3218_cdef = अणु
	.channels				= 18,
	.shutकरोwn_reg				= 0x00,
	.pwm_update_reg				= 0x16,
	.global_control_reg			= IS31FL32XX_REG_NONE,
	.reset_reg				= 0x17,
	.pwm_रेजिस्टर_base			= 0x01,
	.led_control_रेजिस्टर_base		= 0x13,
	.enable_bits_per_led_control_रेजिस्टर	= 6,
पूर्ण;

अटल पूर्णांक is31fl3216_reset(काष्ठा is31fl32xx_priv *priv);
अटल पूर्णांक is31fl3216_software_shutकरोwn(काष्ठा is31fl32xx_priv *priv,
					bool enable);
अटल स्थिर काष्ठा is31fl32xx_chipdef is31fl3216_cdef = अणु
	.channels				= 16,
	.shutकरोwn_reg				= IS31FL32XX_REG_NONE,
	.pwm_update_reg				= 0xB0,
	.global_control_reg			= IS31FL32XX_REG_NONE,
	.reset_reg				= IS31FL32XX_REG_NONE,
	.pwm_रेजिस्टर_base			= 0x10,
	.pwm_रेजिस्टरs_reversed			= true,
	.led_control_रेजिस्टर_base		= 0x01,
	.enable_bits_per_led_control_रेजिस्टर	= 8,
	.reset_func				= is31fl3216_reset,
	.sw_shutकरोwn_func			= is31fl3216_software_shutकरोwn,
पूर्ण;

अटल पूर्णांक is31fl32xx_ग_लिखो(काष्ठा is31fl32xx_priv *priv, u8 reg, u8 val)
अणु
	पूर्णांक ret;

	dev_dbg(&priv->client->dev, "writing register 0x%02X=0x%02X", reg, val);

	ret =  i2c_smbus_ग_लिखो_byte_data(priv->client, reg, val);
	अगर (ret) अणु
		dev_err(&priv->client->dev,
			"register write to 0x%02X failed (error %d)",
			reg, ret);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Custom reset function क्रम IS31FL3216 because it करोes not have a RESET
 * रेजिस्टर the way that the other IS31FL32xx chips करो. We करोn't bother
 * writing the GPIO and animation रेजिस्टरs, because the रेजिस्टरs we
 * करो ग_लिखो ensure those will have no effect.
 */
अटल पूर्णांक is31fl3216_reset(काष्ठा is31fl32xx_priv *priv)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = is31fl32xx_ग_लिखो(priv, IS31FL3216_CONFIG_REG,
			       IS31FL3216_CONFIG_SSD_ENABLE);
	अगर (ret)
		वापस ret;
	क्रम (i = 0; i < priv->cdef->channels; i++) अणु
		ret = is31fl32xx_ग_लिखो(priv, priv->cdef->pwm_रेजिस्टर_base+i,
				       0x00);
		अगर (ret)
			वापस ret;
	पूर्ण
	ret = is31fl32xx_ग_लिखो(priv, priv->cdef->pwm_update_reg, 0);
	अगर (ret)
		वापस ret;
	ret = is31fl32xx_ग_लिखो(priv, IS31FL3216_LIGHTING_EFFECT_REG, 0x00);
	अगर (ret)
		वापस ret;
	ret = is31fl32xx_ग_लिखो(priv, IS31FL3216_CHANNEL_CONFIG_REG, 0x00);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * Custom Software-Shutकरोwn function क्रम IS31FL3216 because it करोes not have
 * a SHUTDOWN रेजिस्टर the way that the other IS31FL32xx chips करो.
 * We करोn't bother करोing a पढ़ो/modअगरy/ग_लिखो on the CONFIG रेजिस्टर because
 * we only ever use a value of '0' क्रम the other fields in that रेजिस्टर.
 */
अटल पूर्णांक is31fl3216_software_shutकरोwn(काष्ठा is31fl32xx_priv *priv,
					bool enable)
अणु
	u8 value = enable ? IS31FL3216_CONFIG_SSD_ENABLE :
			    IS31FL3216_CONFIG_SSD_DISABLE;

	वापस is31fl32xx_ग_लिखो(priv, IS31FL3216_CONFIG_REG, value);
पूर्ण

/*
 * NOTE: A mutex is not needed in this function because:
 * - All referenced data is पढ़ो-only after probe()
 * - The I2C core has a mutex on to protect the bus
 * - There are no पढ़ो/modअगरy/ग_लिखो operations
 * - Intervening operations between the ग_लिखो of the PWM रेजिस्टर
 *   and the Update रेजिस्टर are harmless.
 *
 * Example:
 *	PWM_REG_1 ग_लिखो 16
 *	UPDATE_REG ग_लिखो 0
 *	PWM_REG_2 ग_लिखो 128
 *	UPDATE_REG ग_लिखो 0
 *   vs:
 *	PWM_REG_1 ग_लिखो 16
 *	PWM_REG_2 ग_लिखो 128
 *	UPDATE_REG ग_लिखो 0
 *	UPDATE_REG ग_लिखो 0
 * are equivalent. Poking the Update रेजिस्टर merely applies all PWM
 * रेजिस्टर ग_लिखोs up to that poपूर्णांक.
 */
अटल पूर्णांक is31fl32xx_brightness_set(काष्ठा led_classdev *led_cdev,
				     क्रमागत led_brightness brightness)
अणु
	स्थिर काष्ठा is31fl32xx_led_data *led_data =
		container_of(led_cdev, काष्ठा is31fl32xx_led_data, cdev);
	स्थिर काष्ठा is31fl32xx_chipdef *cdef = led_data->priv->cdef;
	u8 pwm_रेजिस्टर_offset;
	पूर्णांक ret;

	dev_dbg(led_cdev->dev, "%s: %d\n", __func__, brightness);

	/* NOTE: led_data->channel is 1-based */
	अगर (cdef->pwm_रेजिस्टरs_reversed)
		pwm_रेजिस्टर_offset = cdef->channels - led_data->channel;
	अन्यथा
		pwm_रेजिस्टर_offset = led_data->channel - 1;

	ret = is31fl32xx_ग_लिखो(led_data->priv,
			       cdef->pwm_रेजिस्टर_base + pwm_रेजिस्टर_offset,
			       brightness);
	अगर (ret)
		वापस ret;

	वापस is31fl32xx_ग_लिखो(led_data->priv, cdef->pwm_update_reg, 0);
पूर्ण

अटल पूर्णांक is31fl32xx_reset_regs(काष्ठा is31fl32xx_priv *priv)
अणु
	स्थिर काष्ठा is31fl32xx_chipdef *cdef = priv->cdef;
	पूर्णांक ret;

	अगर (cdef->reset_reg != IS31FL32XX_REG_NONE) अणु
		ret = is31fl32xx_ग_लिखो(priv, cdef->reset_reg, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (cdef->reset_func)
		वापस cdef->reset_func(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक is31fl32xx_software_shutकरोwn(काष्ठा is31fl32xx_priv *priv,
					bool enable)
अणु
	स्थिर काष्ठा is31fl32xx_chipdef *cdef = priv->cdef;
	पूर्णांक ret;

	अगर (cdef->shutकरोwn_reg != IS31FL32XX_REG_NONE) अणु
		u8 value = enable ? IS31FL32XX_SHUTDOWN_SSD_ENABLE :
				    IS31FL32XX_SHUTDOWN_SSD_DISABLE;
		ret = is31fl32xx_ग_लिखो(priv, cdef->shutकरोwn_reg, value);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (cdef->sw_shutकरोwn_func)
		वापस cdef->sw_shutकरोwn_func(priv, enable);

	वापस 0;
पूर्ण

अटल पूर्णांक is31fl32xx_init_regs(काष्ठा is31fl32xx_priv *priv)
अणु
	स्थिर काष्ठा is31fl32xx_chipdef *cdef = priv->cdef;
	पूर्णांक ret;

	ret = is31fl32xx_reset_regs(priv);
	अगर (ret)
		वापस ret;

	/*
	 * Set enable bit क्रम all channels.
	 * We will control state with PWM रेजिस्टरs alone.
	 */
	अगर (cdef->led_control_रेजिस्टर_base != IS31FL32XX_REG_NONE) अणु
		u8 value =
		    GENMASK(cdef->enable_bits_per_led_control_रेजिस्टर-1, 0);
		u8 num_regs = cdef->channels /
				cdef->enable_bits_per_led_control_रेजिस्टर;
		पूर्णांक i;

		क्रम (i = 0; i < num_regs; i++) अणु
			ret = is31fl32xx_ग_लिखो(priv,
					       cdef->led_control_रेजिस्टर_base+i,
					       value);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	ret = is31fl32xx_software_shutकरोwn(priv, false);
	अगर (ret)
		वापस ret;

	अगर (cdef->global_control_reg != IS31FL32XX_REG_NONE) अणु
		ret = is31fl32xx_ग_लिखो(priv, cdef->global_control_reg, 0x00);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक is31fl32xx_parse_child_dt(स्थिर काष्ठा device *dev,
				     स्थिर काष्ठा device_node *child,
				     काष्ठा is31fl32xx_led_data *led_data)
अणु
	काष्ठा led_classdev *cdev = &led_data->cdev;
	पूर्णांक ret = 0;
	u32 reg;

	ret = of_property_पढ़ो_u32(child, "reg", &reg);
	अगर (ret || reg < 1 || reg > led_data->priv->cdef->channels) अणु
		dev_err(dev,
			"Child node %pOF does not have a valid reg property\n",
			child);
		वापस -EINVAL;
	पूर्ण
	led_data->channel = reg;

	cdev->brightness_set_blocking = is31fl32xx_brightness_set;

	वापस 0;
पूर्ण

अटल काष्ठा is31fl32xx_led_data *is31fl32xx_find_led_data(
					काष्ठा is31fl32xx_priv *priv,
					u8 channel)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < priv->num_leds; i++) अणु
		अगर (priv->leds[i].channel == channel)
			वापस &priv->leds[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक is31fl32xx_parse_dt(काष्ठा device *dev,
			       काष्ठा is31fl32xx_priv *priv)
अणु
	काष्ठा device_node *child;
	पूर्णांक ret = 0;

	क्रम_each_available_child_of_node(dev_of_node(dev), child) अणु
		काष्ठा led_init_data init_data = अणुपूर्ण;
		काष्ठा is31fl32xx_led_data *led_data =
			&priv->leds[priv->num_leds];
		स्थिर काष्ठा is31fl32xx_led_data *other_led_data;

		led_data->priv = priv;

		ret = is31fl32xx_parse_child_dt(dev, child, led_data);
		अगर (ret)
			जाओ err;

		/* Detect अगर channel is alपढ़ोy in use by another child */
		other_led_data = is31fl32xx_find_led_data(priv,
							  led_data->channel);
		अगर (other_led_data) अणु
			dev_err(dev,
				"Node %pOF 'reg' conflicts with another LED\n",
				child);
			जाओ err;
		पूर्ण

		init_data.fwnode = of_fwnode_handle(child);

		ret = devm_led_classdev_रेजिस्टर_ext(dev, &led_data->cdev,
						     &init_data);
		अगर (ret) अणु
			dev_err(dev, "Failed to register LED for %pOF: %d\n",
				child, ret);
			जाओ err;
		पूर्ण

		priv->num_leds++;
	पूर्ण

	वापस 0;

err:
	of_node_put(child);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_is31fl32xx_match[] = अणु
	अणु .compatible = "issi,is31fl3236", .data = &is31fl3236_cdef, पूर्ण,
	अणु .compatible = "issi,is31fl3235", .data = &is31fl3235_cdef, पूर्ण,
	अणु .compatible = "issi,is31fl3218", .data = &is31fl3218_cdef, पूर्ण,
	अणु .compatible = "si-en,sn3218",    .data = &is31fl3218_cdef, पूर्ण,
	अणु .compatible = "issi,is31fl3216", .data = &is31fl3216_cdef, पूर्ण,
	अणु .compatible = "si-en,sn3216",    .data = &is31fl3216_cdef, पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_is31fl32xx_match);

अटल पूर्णांक is31fl32xx_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा is31fl32xx_chipdef *cdef;
	काष्ठा device *dev = &client->dev;
	काष्ठा is31fl32xx_priv *priv;
	पूर्णांक count;
	पूर्णांक ret = 0;

	cdef = device_get_match_data(dev);

	count = of_get_available_child_count(dev_of_node(dev));
	अगर (!count)
		वापस -EINVAL;

	priv = devm_kzalloc(dev, काष्ठा_size(priv, leds, count),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->client = client;
	priv->cdef = cdef;
	i2c_set_clientdata(client, priv);

	ret = is31fl32xx_init_regs(priv);
	अगर (ret)
		वापस ret;

	ret = is31fl32xx_parse_dt(dev, priv);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक is31fl32xx_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा is31fl32xx_priv *priv = i2c_get_clientdata(client);

	वापस is31fl32xx_reset_regs(priv);
पूर्ण

/*
 * i2c-core (and modalias) requires that id_table be properly filled,
 * even though it is not used क्रम DeviceTree based instantiation.
 */
अटल स्थिर काष्ठा i2c_device_id is31fl32xx_id[] = अणु
	अणु "is31fl3236" पूर्ण,
	अणु "is31fl3235" पूर्ण,
	अणु "is31fl3218" पूर्ण,
	अणु "sn3218" पूर्ण,
	अणु "is31fl3216" पूर्ण,
	अणु "sn3216" पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, is31fl32xx_id);

अटल काष्ठा i2c_driver is31fl32xx_driver = अणु
	.driver = अणु
		.name	= "is31fl32xx",
		.of_match_table = of_is31fl32xx_match,
	पूर्ण,
	.probe		= is31fl32xx_probe,
	.हटाओ		= is31fl32xx_हटाओ,
	.id_table	= is31fl32xx_id,
पूर्ण;

module_i2c_driver(is31fl32xx_driver);

MODULE_AUTHOR("David Rivshin <drivshin@allworx.com>");
MODULE_DESCRIPTION("ISSI IS31FL32xx LED driver");
MODULE_LICENSE("GPL v2");
