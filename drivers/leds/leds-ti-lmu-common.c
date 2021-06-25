<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright 2015 Texas Instruments
// Copyright 2018 Sebastian Reichel
// Copyright 2018 Pavel Machek <pavel@ucw.cz>
// TI LMU LED common framework, based on previous work from
// Milo Kim <milo.kim@ti.com>

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/of_device.h>

#समावेश <linux/leds-ti-lmu-common.h>

अटल स्थिर अचिन्हित पूर्णांक ramp_table[16] = अणु2048, 262000, 524000, 1049000,
				2090000, 4194000, 8389000, 16780000, 33550000,
				41940000, 50330000, 58720000, 67110000,
				83880000, 100660000, 117440000पूर्ण;

अटल पूर्णांक ti_lmu_common_update_brightness(काष्ठा ti_lmu_bank *lmu_bank,
					   पूर्णांक brightness)
अणु
	काष्ठा regmap *regmap = lmu_bank->regmap;
	u8 reg, val;
	पूर्णांक ret;

	/*
	 * Brightness रेजिस्टर update
	 *
	 * 11 bit dimming: update LSB bits and ग_लिखो MSB byte.
	 *		   MSB brightness should be shअगरted.
	 *  8 bit dimming: ग_लिखो MSB byte.
	 */
	अगर (lmu_bank->max_brightness == MAX_BRIGHTNESS_11BIT) अणु
		reg = lmu_bank->lsb_brightness_reg;
		ret = regmap_update_bits(regmap, reg,
					 LMU_11BIT_LSB_MASK,
					 brightness);
		अगर (ret)
			वापस ret;

		val = brightness >> LMU_11BIT_MSB_SHIFT;
	पूर्ण अन्यथा अणु
		val = brightness;
	पूर्ण

	reg = lmu_bank->msb_brightness_reg;

	वापस regmap_ग_लिखो(regmap, reg, val);
पूर्ण

पूर्णांक ti_lmu_common_set_brightness(काष्ठा ti_lmu_bank *lmu_bank, पूर्णांक brightness)
अणु
	वापस ti_lmu_common_update_brightness(lmu_bank, brightness);
पूर्ण
EXPORT_SYMBOL(ti_lmu_common_set_brightness);

अटल अचिन्हित पूर्णांक ti_lmu_common_convert_ramp_to_index(अचिन्हित पूर्णांक usec)
अणु
	पूर्णांक size = ARRAY_SIZE(ramp_table);
	पूर्णांक i;

	अगर (usec <= ramp_table[0])
		वापस 0;

	अगर (usec > ramp_table[size - 1])
		वापस size - 1;

	क्रम (i = 1; i < size; i++) अणु
		अगर (usec == ramp_table[i])
			वापस i;

		/* Find an approximate index by looking up the table */
		अगर (usec > ramp_table[i - 1] && usec < ramp_table[i]) अणु
			अगर (usec - ramp_table[i - 1] < ramp_table[i] - usec)
				वापस i - 1;
			अन्यथा
				वापस i;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ti_lmu_common_set_ramp(काष्ठा ti_lmu_bank *lmu_bank)
अणु
	काष्ठा regmap *regmap = lmu_bank->regmap;
	u8 ramp, ramp_up, ramp_करोwn;

	अगर (lmu_bank->ramp_up_usec == 0 && lmu_bank->ramp_करोwn_usec == 0) अणु
		ramp_up = 0;
		ramp_करोwn = 0;
	पूर्ण अन्यथा अणु
		ramp_up = ti_lmu_common_convert_ramp_to_index(lmu_bank->ramp_up_usec);
		ramp_करोwn = ti_lmu_common_convert_ramp_to_index(lmu_bank->ramp_करोwn_usec);
	पूर्ण

	ramp = (ramp_up << 4) | ramp_करोwn;

	वापस regmap_ग_लिखो(regmap, lmu_bank->runसमय_ramp_reg, ramp);

पूर्ण
EXPORT_SYMBOL(ti_lmu_common_set_ramp);

पूर्णांक ti_lmu_common_get_ramp_params(काष्ठा device *dev,
				  काष्ठा fwnode_handle *child,
				  काष्ठा ti_lmu_bank *lmu_data)
अणु
	पूर्णांक ret;

	ret = fwnode_property_पढ़ो_u32(child, "ramp-up-us",
				 &lmu_data->ramp_up_usec);
	अगर (ret)
		dev_warn(dev, "ramp-up-us property missing\n");


	ret = fwnode_property_पढ़ो_u32(child, "ramp-down-us",
				 &lmu_data->ramp_करोwn_usec);
	अगर (ret)
		dev_warn(dev, "ramp-down-us property missing\n");

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ti_lmu_common_get_ramp_params);

पूर्णांक ti_lmu_common_get_brt_res(काष्ठा device *dev, काष्ठा fwnode_handle *child,
				  काष्ठा ti_lmu_bank *lmu_data)
अणु
	पूर्णांक ret;

	ret = device_property_पढ़ो_u32(dev, "ti,brightness-resolution",
				       &lmu_data->max_brightness);
	अगर (ret)
		ret = fwnode_property_पढ़ो_u32(child,
					       "ti,brightness-resolution",
					       &lmu_data->max_brightness);
	अगर (lmu_data->max_brightness <= 0) अणु
		lmu_data->max_brightness = MAX_BRIGHTNESS_8BIT;
		वापस ret;
	पूर्ण

	अगर (lmu_data->max_brightness > MAX_BRIGHTNESS_11BIT)
			lmu_data->max_brightness = MAX_BRIGHTNESS_11BIT;


	वापस 0;
पूर्ण
EXPORT_SYMBOL(ti_lmu_common_get_brt_res);

MODULE_DESCRIPTION("TI LMU common LED framework");
MODULE_AUTHOR("Sebastian Reichel");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("ti-lmu-led-common");
