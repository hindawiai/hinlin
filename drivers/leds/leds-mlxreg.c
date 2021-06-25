<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
//
// Copyright (c) 2018 Mellanox Technologies. All rights reserved.
// Copyright (c) 2018 Vadim Pasternak <vadimp@mellanox.com>

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_data/mlxreg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* Codes क्रम LEDs. */
#घोषणा MLXREG_LED_OFFSET_BLINK_3HZ	0x01 /* Offset from solid: 3Hz blink */
#घोषणा MLXREG_LED_OFFSET_BLINK_6HZ	0x02 /* Offset from solid: 6Hz blink */
#घोषणा MLXREG_LED_IS_OFF		0x00 /* Off */
#घोषणा MLXREG_LED_RED_SOLID		0x05 /* Solid red */
#घोषणा MLXREG_LED_GREEN_SOLID		0x0D /* Solid green */
#घोषणा MLXREG_LED_AMBER_SOLID		0x09 /* Solid amber */
#घोषणा MLXREG_LED_BLINK_3HZ		167 /* ~167 msec off/on - HW support */
#घोषणा MLXREG_LED_BLINK_6HZ		83 /* ~83 msec off/on - HW support */
#घोषणा MLXREG_LED_CAPABILITY_CLEAR	GENMASK(31, 8) /* Clear mask */

/**
 * काष्ठा mlxreg_led_data - led control data:
 *
 * @data: led configuration data;
 * @led_classdev: led class data;
 * @base_color: base led color (other colors have स्थिरant offset from base);
 * @led_data: led data;
 * @data_parent: poपूर्णांकer to निजी device control data of parent;
 */
काष्ठा mlxreg_led_data अणु
	काष्ठा mlxreg_core_data *data;
	काष्ठा led_classdev led_cdev;
	u8 base_color;
	व्योम *data_parent;
	अक्षर led_cdev_name[MLXREG_CORE_LABEL_MAX_SIZE];
पूर्ण;

#घोषणा cdev_to_priv(c) container_of(c, काष्ठा mlxreg_led_data, led_cdev)

/**
 * काष्ठा mlxreg_led_priv_data - platक्रमm निजी data:
 *
 * @pdev: platक्रमm device;
 * @pdata: platक्रमm data;
 * @access_lock: mutex क्रम attribute IO access;
 */
काष्ठा mlxreg_led_priv_data अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा mlxreg_core_platक्रमm_data *pdata;
	काष्ठा mutex access_lock; /* protect IO operations */
पूर्ण;

अटल पूर्णांक
mlxreg_led_store_hw(काष्ठा mlxreg_led_data *led_data, u8 vset)
अणु
	काष्ठा mlxreg_led_priv_data *priv = led_data->data_parent;
	काष्ठा mlxreg_core_platक्रमm_data *led_pdata = priv->pdata;
	काष्ठा mlxreg_core_data *data = led_data->data;
	u32 regval;
	u32 nib;
	पूर्णांक ret;

	/*
	 * Each LED is controlled through low or high nibble of the relevant
	 * रेजिस्टर byte. Register offset is specअगरied by off parameter.
	 * Parameter vset provides color code: 0x0 क्रम off, 0x5 क्रम solid red,
	 * 0x6 क्रम 3Hz blink red, 0xd क्रम solid green, 0xe क्रम 3Hz blink
	 * green.
	 * Parameter mask specअगरies which nibble is used क्रम specअगरic LED: mask
	 * 0xf0 - lower nibble is to be used (bits from 0 to 3), mask 0x0f -
	 * higher nibble (bits from 4 to 7).
	 */
	mutex_lock(&priv->access_lock);

	ret = regmap_पढ़ो(led_pdata->regmap, data->reg, &regval);
	अगर (ret)
		जाओ access_error;

	nib = (ror32(data->mask, data->bit) == 0xf0) ? rol32(vset, data->bit) :
	      rol32(vset, data->bit + 4);
	regval = (regval & data->mask) | nib;

	ret = regmap_ग_लिखो(led_pdata->regmap, data->reg, regval);

access_error:
	mutex_unlock(&priv->access_lock);

	वापस ret;
पूर्ण

अटल क्रमागत led_brightness
mlxreg_led_get_hw(काष्ठा mlxreg_led_data *led_data)
अणु
	काष्ठा mlxreg_led_priv_data *priv = led_data->data_parent;
	काष्ठा mlxreg_core_platक्रमm_data *led_pdata = priv->pdata;
	काष्ठा mlxreg_core_data *data = led_data->data;
	u32 regval;
	पूर्णांक err;

	/*
	 * Each LED is controlled through low or high nibble of the relevant
	 * रेजिस्टर byte. Register offset is specअगरied by off parameter.
	 * Parameter vset provides color code: 0x0 क्रम off, 0x5 क्रम solid red,
	 * 0x6 क्रम 3Hz blink red, 0xd क्रम solid green, 0xe क्रम 3Hz blink
	 * green.
	 * Parameter mask specअगरies which nibble is used क्रम specअगरic LED: mask
	 * 0xf0 - lower nibble is to be used (bits from 0 to 3), mask 0x0f -
	 * higher nibble (bits from 4 to 7).
	 */
	err = regmap_पढ़ो(led_pdata->regmap, data->reg, &regval);
	अगर (err < 0) अणु
		dev_warn(led_data->led_cdev.dev, "Failed to get current brightness, error: %d\n",
			 err);
		/* Assume the LED is OFF */
		वापस LED_OFF;
	पूर्ण

	regval = regval & ~data->mask;
	regval = (ror32(data->mask, data->bit) == 0xf0) ? ror32(regval,
		 data->bit) : ror32(regval, data->bit + 4);
	अगर (regval >= led_data->base_color &&
	    regval <= (led_data->base_color + MLXREG_LED_OFFSET_BLINK_6HZ))
		वापस LED_FULL;

	वापस LED_OFF;
पूर्ण

अटल पूर्णांक
mlxreg_led_brightness_set(काष्ठा led_classdev *cled, क्रमागत led_brightness value)
अणु
	काष्ठा mlxreg_led_data *led_data = cdev_to_priv(cled);

	अगर (value)
		वापस mlxreg_led_store_hw(led_data, led_data->base_color);
	अन्यथा
		वापस mlxreg_led_store_hw(led_data, MLXREG_LED_IS_OFF);
पूर्ण

अटल क्रमागत led_brightness
mlxreg_led_brightness_get(काष्ठा led_classdev *cled)
अणु
	काष्ठा mlxreg_led_data *led_data = cdev_to_priv(cled);

	वापस mlxreg_led_get_hw(led_data);
पूर्ण

अटल पूर्णांक
mlxreg_led_blink_set(काष्ठा led_classdev *cled, अचिन्हित दीर्घ *delay_on,
		     अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा mlxreg_led_data *led_data = cdev_to_priv(cled);
	पूर्णांक err;

	/*
	 * HW supports two types of blinking: full (6Hz) and half (3Hz).
	 * For delay on/off zero LED is setting to solid color. For others
	 * combination blinking is to be controlled by the software समयr.
	 */
	अगर (!(*delay_on == 0 && *delay_off == 0) &&
	    !(*delay_on == MLXREG_LED_BLINK_3HZ &&
	      *delay_off == MLXREG_LED_BLINK_3HZ) &&
	    !(*delay_on == MLXREG_LED_BLINK_6HZ &&
	      *delay_off == MLXREG_LED_BLINK_6HZ))
		वापस -EINVAL;

	अगर (*delay_on == MLXREG_LED_BLINK_6HZ)
		err = mlxreg_led_store_hw(led_data, led_data->base_color +
					  MLXREG_LED_OFFSET_BLINK_6HZ);
	अन्यथा अगर (*delay_on == MLXREG_LED_BLINK_3HZ)
		err = mlxreg_led_store_hw(led_data, led_data->base_color +
					  MLXREG_LED_OFFSET_BLINK_3HZ);
	अन्यथा
		err = mlxreg_led_store_hw(led_data, led_data->base_color);

	वापस err;
पूर्ण

अटल पूर्णांक mlxreg_led_config(काष्ठा mlxreg_led_priv_data *priv)
अणु
	काष्ठा mlxreg_core_platक्रमm_data *led_pdata = priv->pdata;
	काष्ठा mlxreg_core_data *data = led_pdata->data;
	काष्ठा mlxreg_led_data *led_data;
	काष्ठा led_classdev *led_cdev;
	क्रमागत led_brightness brightness;
	u32 regval;
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < led_pdata->counter; i++, data++) अणु
		led_data = devm_kzalloc(&priv->pdev->dev, माप(*led_data),
					GFP_KERNEL);
		अगर (!led_data)
			वापस -ENOMEM;

		अगर (data->capability) अणु
			err = regmap_पढ़ो(led_pdata->regmap, data->capability,
					  &regval);
			अगर (err) अणु
				dev_err(&priv->pdev->dev, "Failed to query capability register\n");
				वापस err;
			पूर्ण
			अगर (!(regval & data->bit))
				जारी;
			/*
			 * Field "bit" can contain one capability bit in 0 byte
			 * and offset bit in 1-3 bytes. Clear capability bit and
			 * keep only offset bit.
			 */
			data->bit &= MLXREG_LED_CAPABILITY_CLEAR;
		पूर्ण

		led_cdev = &led_data->led_cdev;
		led_data->data_parent = priv;
		अगर (म_माला(data->label, "red") ||
		    म_माला(data->label, "orange")) अणु
			brightness = LED_OFF;
			led_data->base_color = MLXREG_LED_RED_SOLID;
		पूर्ण अन्यथा अगर (म_माला(data->label, "amber")) अणु
			brightness = LED_OFF;
			led_data->base_color = MLXREG_LED_AMBER_SOLID;
		पूर्ण अन्यथा अणु
			brightness = LED_OFF;
			led_data->base_color = MLXREG_LED_GREEN_SOLID;
		पूर्ण
		snम_लिखो(led_data->led_cdev_name, माप(led_data->led_cdev_name),
			 "mlxreg:%s", data->label);
		led_cdev->name = led_data->led_cdev_name;
		led_cdev->brightness = brightness;
		led_cdev->max_brightness = LED_ON;
		led_cdev->brightness_set_blocking =
						mlxreg_led_brightness_set;
		led_cdev->brightness_get = mlxreg_led_brightness_get;
		led_cdev->blink_set = mlxreg_led_blink_set;
		led_cdev->flags = LED_CORE_SUSPENDRESUME;
		led_data->data = data;
		err = devm_led_classdev_रेजिस्टर(&priv->pdev->dev, led_cdev);
		अगर (err)
			वापस err;

		अगर (led_cdev->brightness)
			mlxreg_led_brightness_set(led_cdev,
						  led_cdev->brightness);
		dev_info(led_cdev->dev, "label: %s, mask: 0x%02x, offset:0x%02x\n",
			 data->label, data->mask, data->reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxreg_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxreg_core_platक्रमm_data *led_pdata;
	काष्ठा mlxreg_led_priv_data *priv;

	led_pdata = dev_get_platdata(&pdev->dev);
	अगर (!led_pdata) अणु
		dev_err(&pdev->dev, "Failed to get platform data.\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_init(&priv->access_lock);
	priv->pdev = pdev;
	priv->pdata = led_pdata;

	वापस mlxreg_led_config(priv);
पूर्ण

अटल पूर्णांक mlxreg_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxreg_led_priv_data *priv = dev_get_drvdata(&pdev->dev);

	mutex_destroy(&priv->access_lock);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mlxreg_led_driver = अणु
	.driver = अणु
	    .name = "leds-mlxreg",
	पूर्ण,
	.probe = mlxreg_led_probe,
	.हटाओ = mlxreg_led_हटाओ,
पूर्ण;

module_platक्रमm_driver(mlxreg_led_driver);

MODULE_AUTHOR("Vadim Pasternak <vadimp@mellanox.com>");
MODULE_DESCRIPTION("Mellanox LED regmap driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("platform:leds-mlxreg");
