<शैली गुरु>
/*
 * tps65217_bl.c
 *
 * TPS65217 backlight driver
 *
 * Copyright (C) 2012 Matthias Kaehlcke
 * Author: Matthias Kaehlcke <matthias@kaehlcke.net>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/backlight.h>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/mfd/tps65217.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

काष्ठा tps65217_bl अणु
	काष्ठा tps65217 *tps;
	काष्ठा device *dev;
	काष्ठा backlight_device *bl;
	bool is_enabled;
पूर्ण;

अटल पूर्णांक tps65217_bl_enable(काष्ठा tps65217_bl *tps65217_bl)
अणु
	पूर्णांक rc;

	rc = tps65217_set_bits(tps65217_bl->tps, TPS65217_REG_WLEDCTRL1,
			TPS65217_WLEDCTRL1_ISINK_ENABLE,
			TPS65217_WLEDCTRL1_ISINK_ENABLE, TPS65217_PROTECT_NONE);
	अगर (rc) अणु
		dev_err(tps65217_bl->dev,
			"failed to enable backlight: %d\n", rc);
		वापस rc;
	पूर्ण

	tps65217_bl->is_enabled = true;

	dev_dbg(tps65217_bl->dev, "backlight enabled\n");

	वापस 0;
पूर्ण

अटल पूर्णांक tps65217_bl_disable(काष्ठा tps65217_bl *tps65217_bl)
अणु
	पूर्णांक rc;

	rc = tps65217_clear_bits(tps65217_bl->tps,
				TPS65217_REG_WLEDCTRL1,
				TPS65217_WLEDCTRL1_ISINK_ENABLE,
				TPS65217_PROTECT_NONE);
	अगर (rc) अणु
		dev_err(tps65217_bl->dev,
			"failed to disable backlight: %d\n", rc);
		वापस rc;
	पूर्ण

	tps65217_bl->is_enabled = false;

	dev_dbg(tps65217_bl->dev, "backlight disabled\n");

	वापस 0;
पूर्ण

अटल पूर्णांक tps65217_bl_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा tps65217_bl *tps65217_bl = bl_get_data(bl);
	पूर्णांक rc;
	पूर्णांक brightness = backlight_get_brightness(bl);

	अगर (brightness > 0) अणु
		rc = tps65217_reg_ग_लिखो(tps65217_bl->tps,
					TPS65217_REG_WLEDCTRL2,
					brightness - 1,
					TPS65217_PROTECT_NONE);
		अगर (rc) अणु
			dev_err(tps65217_bl->dev,
				"failed to set brightness level: %d\n", rc);
			वापस rc;
		पूर्ण

		dev_dbg(tps65217_bl->dev, "brightness set to %d\n", brightness);

		अगर (!tps65217_bl->is_enabled)
			rc = tps65217_bl_enable(tps65217_bl);
	पूर्ण अन्यथा अणु
		rc = tps65217_bl_disable(tps65217_bl);
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा backlight_ops tps65217_bl_ops = अणु
	.options	= BL_CORE_SUSPENDRESUME,
	.update_status	= tps65217_bl_update_status,
पूर्ण;

अटल पूर्णांक tps65217_bl_hw_init(काष्ठा tps65217_bl *tps65217_bl,
			काष्ठा tps65217_bl_pdata *pdata)
अणु
	पूर्णांक rc;

	rc = tps65217_bl_disable(tps65217_bl);
	अगर (rc)
		वापस rc;

	चयन (pdata->isel) अणु
	हाल TPS65217_BL_ISET1:
		/* select ISET_1 current level */
		rc = tps65217_clear_bits(tps65217_bl->tps,
					TPS65217_REG_WLEDCTRL1,
					TPS65217_WLEDCTRL1_ISEL,
					TPS65217_PROTECT_NONE);
		अगर (rc) अणु
			dev_err(tps65217_bl->dev,
				"failed to select ISET1 current level: %d)\n",
				rc);
			वापस rc;
		पूर्ण

		dev_dbg(tps65217_bl->dev, "selected ISET1 current level\n");

		अवरोध;

	हाल TPS65217_BL_ISET2:
		/* select ISET2 current level */
		rc = tps65217_set_bits(tps65217_bl->tps, TPS65217_REG_WLEDCTRL1,
				TPS65217_WLEDCTRL1_ISEL,
				TPS65217_WLEDCTRL1_ISEL, TPS65217_PROTECT_NONE);
		अगर (rc) अणु
			dev_err(tps65217_bl->dev,
				"failed to select ISET2 current level: %d\n",
				rc);
			वापस rc;
		पूर्ण

		dev_dbg(tps65217_bl->dev, "selected ISET2 current level\n");

		अवरोध;

	शेष:
		dev_err(tps65217_bl->dev,
			"invalid value for current level: %d\n", pdata->isel);
		वापस -EINVAL;
	पूर्ण

	/* set PWM frequency */
	rc = tps65217_set_bits(tps65217_bl->tps,
			TPS65217_REG_WLEDCTRL1,
			TPS65217_WLEDCTRL1_FDIM_MASK,
			pdata->fdim,
			TPS65217_PROTECT_NONE);
	अगर (rc) अणु
		dev_err(tps65217_bl->dev,
			"failed to select PWM dimming frequency: %d\n",
			rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा tps65217_bl_pdata *
tps65217_bl_parse_dt(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65217 *tps = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device_node *node;
	काष्ठा tps65217_bl_pdata *pdata, *err;
	u32 val;

	node = of_get_child_by_name(tps->dev->of_node, "backlight");
	अगर (!node)
		वापस ERR_PTR(-ENODEV);

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata) अणु
		err = ERR_PTR(-ENOMEM);
		जाओ err;
	पूर्ण

	pdata->isel = TPS65217_BL_ISET1;
	अगर (!of_property_पढ़ो_u32(node, "isel", &val)) अणु
		अगर (val < TPS65217_BL_ISET1 ||
			val > TPS65217_BL_ISET2) अणु
			dev_err(&pdev->dev,
				"invalid 'isel' value in the device tree\n");
			err = ERR_PTR(-EINVAL);
			जाओ err;
		पूर्ण

		pdata->isel = val;
	पूर्ण

	pdata->fdim = TPS65217_BL_FDIM_200HZ;
	अगर (!of_property_पढ़ो_u32(node, "fdim", &val)) अणु
		चयन (val) अणु
		हाल 100:
			pdata->fdim = TPS65217_BL_FDIM_100HZ;
			अवरोध;

		हाल 200:
			pdata->fdim = TPS65217_BL_FDIM_200HZ;
			अवरोध;

		हाल 500:
			pdata->fdim = TPS65217_BL_FDIM_500HZ;
			अवरोध;

		हाल 1000:
			pdata->fdim = TPS65217_BL_FDIM_1000HZ;
			अवरोध;

		शेष:
			dev_err(&pdev->dev,
				"invalid 'fdim' value in the device tree\n");
			err = ERR_PTR(-EINVAL);
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (!of_property_पढ़ो_u32(node, "default-brightness", &val)) अणु
		अगर (val > 100) अणु
			dev_err(&pdev->dev,
				"invalid 'default-brightness' value in the device tree\n");
			err = ERR_PTR(-EINVAL);
			जाओ err;
		पूर्ण

		pdata->dft_brightness = val;
	पूर्ण

	of_node_put(node);

	वापस pdata;

err:
	of_node_put(node);

	वापस err;
पूर्ण
#अन्यथा
अटल काष्ठा tps65217_bl_pdata *
tps65217_bl_parse_dt(काष्ठा platक्रमm_device *pdev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tps65217_bl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc;
	काष्ठा tps65217 *tps = dev_get_drvdata(pdev->dev.parent);
	काष्ठा tps65217_bl *tps65217_bl;
	काष्ठा tps65217_bl_pdata *pdata;
	काष्ठा backlight_properties bl_props;

	pdata = tps65217_bl_parse_dt(pdev);
	अगर (IS_ERR(pdata))
		वापस PTR_ERR(pdata);

	tps65217_bl = devm_kzalloc(&pdev->dev, माप(*tps65217_bl),
				GFP_KERNEL);
	अगर (tps65217_bl == शून्य)
		वापस -ENOMEM;

	tps65217_bl->tps = tps;
	tps65217_bl->dev = &pdev->dev;
	tps65217_bl->is_enabled = false;

	rc = tps65217_bl_hw_init(tps65217_bl, pdata);
	अगर (rc)
		वापस rc;

	स_रखो(&bl_props, 0, माप(काष्ठा backlight_properties));
	bl_props.type = BACKLIGHT_RAW;
	bl_props.max_brightness = 100;

	tps65217_bl->bl = devm_backlight_device_रेजिस्टर(&pdev->dev, pdev->name,
						tps65217_bl->dev, tps65217_bl,
						&tps65217_bl_ops, &bl_props);
	अगर (IS_ERR(tps65217_bl->bl)) अणु
		dev_err(tps65217_bl->dev,
			"registration of backlight device failed: %d\n", rc);
		वापस PTR_ERR(tps65217_bl->bl);
	पूर्ण

	tps65217_bl->bl->props.brightness = pdata->dft_brightness;
	backlight_update_status(tps65217_bl->bl);
	platक्रमm_set_drvdata(pdev, tps65217_bl);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tps65217_bl_of_match[] = अणु
	अणु .compatible = "ti,tps65217-bl", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tps65217_bl_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver tps65217_bl_driver = अणु
	.probe		= tps65217_bl_probe,
	.driver		= अणु
		.name	= "tps65217-bl",
		.of_match_table = of_match_ptr(tps65217_bl_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(tps65217_bl_driver);

MODULE_DESCRIPTION("TPS65217 Backlight driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Matthias Kaehlcke <matthias@kaehlcke.net>");
