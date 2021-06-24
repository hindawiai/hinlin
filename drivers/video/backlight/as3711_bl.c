<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AS3711 PMIC backlight driver, using DCDC Step Up Converters
 *
 * Copyright (C) 2012 Renesas Electronics Corporation
 * Author: Guennadi Liakhovetski, <g.liakhovetski@gmx.de>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/as3711.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

क्रमागत as3711_bl_type अणु
	AS3711_BL_SU1,
	AS3711_BL_SU2,
पूर्ण;

काष्ठा as3711_bl_data अणु
	bool घातered;
	क्रमागत as3711_bl_type type;
	पूर्णांक brightness;
	काष्ठा backlight_device *bl;
पूर्ण;

काष्ठा as3711_bl_supply अणु
	काष्ठा as3711_bl_data su1;
	काष्ठा as3711_bl_data su2;
	स्थिर काष्ठा as3711_bl_pdata *pdata;
	काष्ठा as3711 *as3711;
पूर्ण;

अटल काष्ठा as3711_bl_supply *to_supply(काष्ठा as3711_bl_data *su)
अणु
	चयन (su->type) अणु
	हाल AS3711_BL_SU1:
		वापस container_of(su, काष्ठा as3711_bl_supply, su1);
	हाल AS3711_BL_SU2:
		वापस container_of(su, काष्ठा as3711_bl_supply, su2);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक as3711_set_brightness_स्वतः_i(काष्ठा as3711_bl_data *data,
					अचिन्हित पूर्णांक brightness)
अणु
	काष्ठा as3711_bl_supply *supply = to_supply(data);
	काष्ठा as3711 *as3711 = supply->as3711;
	स्थिर काष्ठा as3711_bl_pdata *pdata = supply->pdata;
	पूर्णांक ret = 0;

	/* Only all equal current values are supported */
	अगर (pdata->su2_स्वतः_curr1)
		ret = regmap_ग_लिखो(as3711->regmap, AS3711_CURR1_VALUE,
				   brightness);
	अगर (!ret && pdata->su2_स्वतः_curr2)
		ret = regmap_ग_लिखो(as3711->regmap, AS3711_CURR2_VALUE,
				   brightness);
	अगर (!ret && pdata->su2_स्वतः_curr3)
		ret = regmap_ग_लिखो(as3711->regmap, AS3711_CURR3_VALUE,
				   brightness);

	वापस ret;
पूर्ण

अटल पूर्णांक as3711_set_brightness_v(काष्ठा as3711 *as3711,
				   अचिन्हित पूर्णांक brightness,
				   अचिन्हित पूर्णांक reg)
अणु
	अगर (brightness > 31)
		वापस -EINVAL;

	वापस regmap_update_bits(as3711->regmap, reg, 0xf0,
				  brightness << 4);
पूर्ण

अटल पूर्णांक as3711_bl_su2_reset(काष्ठा as3711_bl_supply *supply)
अणु
	काष्ठा as3711 *as3711 = supply->as3711;
	पूर्णांक ret = regmap_update_bits(as3711->regmap, AS3711_STEPUP_CONTROL_5,
				     3, supply->pdata->su2_fbprot);
	अगर (!ret)
		ret = regmap_update_bits(as3711->regmap,
					 AS3711_STEPUP_CONTROL_2, 1, 0);
	अगर (!ret)
		ret = regmap_update_bits(as3711->regmap,
					 AS3711_STEPUP_CONTROL_2, 1, 1);
	वापस ret;
पूर्ण

/*
 * Someone with less fragile or less expensive hardware could try to simplअगरy
 * the brightness adjusपंचांगent procedure.
 */
अटल पूर्णांक as3711_bl_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा as3711_bl_data *data = bl_get_data(bl);
	काष्ठा as3711_bl_supply *supply = to_supply(data);
	काष्ठा as3711 *as3711 = supply->as3711;
	पूर्णांक brightness;
	पूर्णांक ret = 0;

	brightness = backlight_get_brightness(bl);

	अगर (data->type == AS3711_BL_SU1) अणु
		ret = as3711_set_brightness_v(as3711, brightness,
					      AS3711_STEPUP_CONTROL_1);
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा as3711_bl_pdata *pdata = supply->pdata;

		चयन (pdata->su2_feedback) अणु
		हाल AS3711_SU2_VOLTAGE:
			ret = as3711_set_brightness_v(as3711, brightness,
						      AS3711_STEPUP_CONTROL_2);
			अवरोध;
		हाल AS3711_SU2_CURR_AUTO:
			ret = as3711_set_brightness_स्वतः_i(data, brightness / 4);
			अगर (ret < 0)
				वापस ret;
			अगर (brightness) अणु
				ret = as3711_bl_su2_reset(supply);
				अगर (ret < 0)
					वापस ret;
				udelay(500);
				ret = as3711_set_brightness_स्वतः_i(data, brightness);
			पूर्ण अन्यथा अणु
				ret = regmap_update_bits(as3711->regmap,
						AS3711_STEPUP_CONTROL_2, 1, 0);
			पूर्ण
			अवरोध;
		/* Manual one current feedback pin below */
		हाल AS3711_SU2_CURR1:
			ret = regmap_ग_लिखो(as3711->regmap, AS3711_CURR1_VALUE,
					   brightness);
			अवरोध;
		हाल AS3711_SU2_CURR2:
			ret = regmap_ग_लिखो(as3711->regmap, AS3711_CURR2_VALUE,
					   brightness);
			अवरोध;
		हाल AS3711_SU2_CURR3:
			ret = regmap_ग_लिखो(as3711->regmap, AS3711_CURR3_VALUE,
					   brightness);
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
	पूर्ण
	अगर (!ret)
		data->brightness = brightness;

	वापस ret;
पूर्ण

अटल पूर्णांक as3711_bl_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा as3711_bl_data *data = bl_get_data(bl);

	वापस data->brightness;
पूर्ण

अटल स्थिर काष्ठा backlight_ops as3711_bl_ops = अणु
	.update_status	= as3711_bl_update_status,
	.get_brightness	= as3711_bl_get_brightness,
पूर्ण;

अटल पूर्णांक as3711_bl_init_su2(काष्ठा as3711_bl_supply *supply)
अणु
	काष्ठा as3711 *as3711 = supply->as3711;
	स्थिर काष्ठा as3711_bl_pdata *pdata = supply->pdata;
	u8 ctl = 0;
	पूर्णांक ret;

	dev_dbg(as3711->dev, "%s(): use %u\n", __func__, pdata->su2_feedback);

	/* Turn SU2 off */
	ret = regmap_ग_लिखो(as3711->regmap, AS3711_STEPUP_CONTROL_2, 0);
	अगर (ret < 0)
		वापस ret;

	चयन (pdata->su2_feedback) अणु
	हाल AS3711_SU2_VOLTAGE:
		ret = regmap_update_bits(as3711->regmap, AS3711_STEPUP_CONTROL_4, 3, 0);
		अवरोध;
	हाल AS3711_SU2_CURR1:
		ctl = 1;
		ret = regmap_update_bits(as3711->regmap, AS3711_STEPUP_CONTROL_4, 3, 1);
		अवरोध;
	हाल AS3711_SU2_CURR2:
		ctl = 4;
		ret = regmap_update_bits(as3711->regmap, AS3711_STEPUP_CONTROL_4, 3, 2);
		अवरोध;
	हाल AS3711_SU2_CURR3:
		ctl = 0x10;
		ret = regmap_update_bits(as3711->regmap, AS3711_STEPUP_CONTROL_4, 3, 3);
		अवरोध;
	हाल AS3711_SU2_CURR_AUTO:
		अगर (pdata->su2_स्वतः_curr1)
			ctl = 2;
		अगर (pdata->su2_स्वतः_curr2)
			ctl |= 8;
		अगर (pdata->su2_स्वतः_curr3)
			ctl |= 0x20;
		ret = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!ret)
		ret = regmap_ग_लिखो(as3711->regmap, AS3711_CURR_CONTROL, ctl);

	वापस ret;
पूर्ण

अटल पूर्णांक as3711_bl_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
			      अचिन्हित पूर्णांक max_brightness, काष्ठा as3711_bl_data *su)
अणु
	काष्ठा backlight_properties props = अणु.type = BACKLIGHT_RAW,पूर्ण;
	काष्ठा backlight_device *bl;

	/* max tuning I = 31uA क्रम voltage- and 38250uA क्रम current-feedback */
	props.max_brightness = max_brightness;

	bl = devm_backlight_device_रेजिस्टर(&pdev->dev,
				       su->type == AS3711_BL_SU1 ?
				       "as3711-su1" : "as3711-su2",
				       &pdev->dev, su,
				       &as3711_bl_ops, &props);
	अगर (IS_ERR(bl)) अणु
		dev_err(&pdev->dev, "failed to register backlight\n");
		वापस PTR_ERR(bl);
	पूर्ण

	bl->props.brightness = props.max_brightness;

	backlight_update_status(bl);

	su->bl = bl;

	वापस 0;
पूर्ण

अटल पूर्णांक as3711_backlight_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा as3711_bl_pdata *pdata = dev_get_platdata(dev);
	काष्ठा device_node *bl, *fb;
	पूर्णांक ret;

	bl = of_get_child_by_name(dev->parent->of_node, "backlight");
	अगर (!bl) अणु
		dev_dbg(dev, "backlight node not found\n");
		वापस -ENODEV;
	पूर्ण

	fb = of_parse_phandle(bl, "su1-dev", 0);
	अगर (fb) अणु
		of_node_put(fb);

		pdata->su1_fb = true;

		ret = of_property_पढ़ो_u32(bl, "su1-max-uA", &pdata->su1_max_uA);
		अगर (pdata->su1_max_uA <= 0)
			ret = -EINVAL;
		अगर (ret < 0)
			जाओ err_put_bl;
	पूर्ण

	fb = of_parse_phandle(bl, "su2-dev", 0);
	अगर (fb) अणु
		पूर्णांक count = 0;

		of_node_put(fb);

		pdata->su2_fb = true;

		ret = of_property_पढ़ो_u32(bl, "su2-max-uA", &pdata->su2_max_uA);
		अगर (pdata->su2_max_uA <= 0)
			ret = -EINVAL;
		अगर (ret < 0)
			जाओ err_put_bl;

		अगर (of_find_property(bl, "su2-feedback-voltage", शून्य)) अणु
			pdata->su2_feedback = AS3711_SU2_VOLTAGE;
			count++;
		पूर्ण
		अगर (of_find_property(bl, "su2-feedback-curr1", शून्य)) अणु
			pdata->su2_feedback = AS3711_SU2_CURR1;
			count++;
		पूर्ण
		अगर (of_find_property(bl, "su2-feedback-curr2", शून्य)) अणु
			pdata->su2_feedback = AS3711_SU2_CURR2;
			count++;
		पूर्ण
		अगर (of_find_property(bl, "su2-feedback-curr3", शून्य)) अणु
			pdata->su2_feedback = AS3711_SU2_CURR3;
			count++;
		पूर्ण
		अगर (of_find_property(bl, "su2-feedback-curr-auto", शून्य)) अणु
			pdata->su2_feedback = AS3711_SU2_CURR_AUTO;
			count++;
		पूर्ण
		अगर (count != 1) अणु
			ret = -EINVAL;
			जाओ err_put_bl;
		पूर्ण

		count = 0;
		अगर (of_find_property(bl, "su2-fbprot-lx-sd4", शून्य)) अणु
			pdata->su2_fbprot = AS3711_SU2_LX_SD4;
			count++;
		पूर्ण
		अगर (of_find_property(bl, "su2-fbprot-gpio2", शून्य)) अणु
			pdata->su2_fbprot = AS3711_SU2_GPIO2;
			count++;
		पूर्ण
		अगर (of_find_property(bl, "su2-fbprot-gpio3", शून्य)) अणु
			pdata->su2_fbprot = AS3711_SU2_GPIO3;
			count++;
		पूर्ण
		अगर (of_find_property(bl, "su2-fbprot-gpio4", शून्य)) अणु
			pdata->su2_fbprot = AS3711_SU2_GPIO4;
			count++;
		पूर्ण
		अगर (count != 1) अणु
			ret = -EINVAL;
			जाओ err_put_bl;
		पूर्ण

		count = 0;
		अगर (of_find_property(bl, "su2-auto-curr1", शून्य)) अणु
			pdata->su2_स्वतः_curr1 = true;
			count++;
		पूर्ण
		अगर (of_find_property(bl, "su2-auto-curr2", शून्य)) अणु
			pdata->su2_स्वतः_curr2 = true;
			count++;
		पूर्ण
		अगर (of_find_property(bl, "su2-auto-curr3", शून्य)) अणु
			pdata->su2_स्वतः_curr3 = true;
			count++;
		पूर्ण

		/*
		 * At least one su2-स्वतः-curr* must be specअगरied अगरf
		 * AS3711_SU2_CURR_AUTO is used
		 */
		अगर (!count ^ (pdata->su2_feedback != AS3711_SU2_CURR_AUTO)) अणु
			ret = -EINVAL;
			जाओ err_put_bl;
		पूर्ण
	पूर्ण

	of_node_put(bl);

	वापस 0;

err_put_bl:
	of_node_put(bl);

	वापस ret;
पूर्ण

अटल पूर्णांक as3711_backlight_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा as3711_bl_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा as3711 *as3711 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा as3711_bl_supply *supply;
	काष्ठा as3711_bl_data *su;
	अचिन्हित पूर्णांक max_brightness;
	पूर्णांक ret;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "No platform data, exiting...\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pdev->dev.parent->of_node) अणु
		ret = as3711_backlight_parse_dt(&pdev->dev);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "DT parsing failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!pdata->su1_fb && !pdata->su2_fb) अणु
		dev_err(&pdev->dev, "No framebuffer specified\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Due to possible hardware damage I chose to block all modes,
	 * unsupported on my hardware. Anyone, wishing to use any of those modes
	 * will have to first review the code, then activate and test it.
	 */
	अगर (pdata->su1_fb ||
	    pdata->su2_fbprot != AS3711_SU2_GPIO4 ||
	    pdata->su2_feedback != AS3711_SU2_CURR_AUTO) अणु
		dev_warn(&pdev->dev,
			 "Attention! An untested mode has been chosen!\n"
			 "Please, review the code, enable, test, and report success:-)\n");
		वापस -EINVAL;
	पूर्ण

	supply = devm_kzalloc(&pdev->dev, माप(*supply), GFP_KERNEL);
	अगर (!supply)
		वापस -ENOMEM;

	supply->as3711 = as3711;
	supply->pdata = pdata;

	अगर (pdata->su1_fb) अणु
		su = &supply->su1;
		su->type = AS3711_BL_SU1;

		max_brightness = min(pdata->su1_max_uA, 31);
		ret = as3711_bl_रेजिस्टर(pdev, max_brightness, su);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (pdata->su2_fb) अणु
		su = &supply->su2;
		su->type = AS3711_BL_SU2;

		चयन (pdata->su2_fbprot) अणु
		हाल AS3711_SU2_GPIO2:
		हाल AS3711_SU2_GPIO3:
		हाल AS3711_SU2_GPIO4:
		हाल AS3711_SU2_LX_SD4:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		चयन (pdata->su2_feedback) अणु
		हाल AS3711_SU2_VOLTAGE:
			max_brightness = min(pdata->su2_max_uA, 31);
			अवरोध;
		हाल AS3711_SU2_CURR1:
		हाल AS3711_SU2_CURR2:
		हाल AS3711_SU2_CURR3:
		हाल AS3711_SU2_CURR_AUTO:
			max_brightness = min(pdata->su2_max_uA / 150, 255);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = as3711_bl_init_su2(supply);
		अगर (ret < 0)
			वापस ret;

		ret = as3711_bl_रेजिस्टर(pdev, max_brightness, su);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, supply);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver as3711_backlight_driver = अणु
	.driver		= अणु
		.name	= "as3711-backlight",
	पूर्ण,
	.probe		= as3711_backlight_probe,
पूर्ण;

module_platक्रमm_driver(as3711_backlight_driver);

MODULE_DESCRIPTION("Backlight Driver for AS3711 PMICs");
MODULE_AUTHOR("Guennadi Liakhovetski <g.liakhovetski@gmx.de");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:as3711-backlight");
