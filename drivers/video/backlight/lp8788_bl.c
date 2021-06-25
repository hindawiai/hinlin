<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI LP8788 MFD - backlight driver
 *
 * Copyright 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/lp8788.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>

/* Register address */
#घोषणा LP8788_BL_CONFIG		0x96
#घोषणा LP8788_BL_EN			BIT(0)
#घोषणा LP8788_BL_PWM_INPUT_EN		BIT(5)
#घोषणा LP8788_BL_FULLSCALE_SHIFT	2
#घोषणा LP8788_BL_DIM_MODE_SHIFT	1
#घोषणा LP8788_BL_PWM_POLARITY_SHIFT	6

#घोषणा LP8788_BL_BRIGHTNESS		0x97

#घोषणा LP8788_BL_RAMP			0x98
#घोषणा LP8788_BL_RAMP_RISE_SHIFT	4

#घोषणा MAX_BRIGHTNESS			127
#घोषणा DEFAULT_BL_NAME			"lcd-backlight"

काष्ठा lp8788_bl_config अणु
	क्रमागत lp8788_bl_ctrl_mode bl_mode;
	क्रमागत lp8788_bl_dim_mode dim_mode;
	क्रमागत lp8788_bl_full_scale_current full_scale;
	क्रमागत lp8788_bl_ramp_step rise_समय;
	क्रमागत lp8788_bl_ramp_step fall_समय;
	क्रमागत pwm_polarity pwm_pol;
पूर्ण;

काष्ठा lp8788_bl अणु
	काष्ठा lp8788 *lp;
	काष्ठा backlight_device *bl_dev;
	काष्ठा lp8788_backlight_platक्रमm_data *pdata;
	क्रमागत lp8788_bl_ctrl_mode mode;
	काष्ठा pwm_device *pwm;
पूर्ण;

अटल काष्ठा lp8788_bl_config शेष_bl_config = अणु
	.bl_mode    = LP8788_BL_REGISTER_ONLY,
	.dim_mode   = LP8788_DIM_EXPONENTIAL,
	.full_scale = LP8788_FULLSCALE_1900uA,
	.rise_समय  = LP8788_RAMP_8192us,
	.fall_समय  = LP8788_RAMP_8192us,
	.pwm_pol    = PWM_POLARITY_NORMAL,
पूर्ण;

अटल अंतरभूत bool is_brightness_ctrl_by_pwm(क्रमागत lp8788_bl_ctrl_mode mode)
अणु
	वापस mode == LP8788_BL_COMB_PWM_BASED;
पूर्ण

अटल अंतरभूत bool is_brightness_ctrl_by_रेजिस्टर(क्रमागत lp8788_bl_ctrl_mode mode)
अणु
	वापस mode == LP8788_BL_REGISTER_ONLY ||
		mode == LP8788_BL_COMB_REGISTER_BASED;
पूर्ण

अटल पूर्णांक lp8788_backlight_configure(काष्ठा lp8788_bl *bl)
अणु
	काष्ठा lp8788_backlight_platक्रमm_data *pdata = bl->pdata;
	काष्ठा lp8788_bl_config *cfg = &शेष_bl_config;
	पूर्णांक ret;
	u8 val;

	/*
	 * Update chip configuration अगर platक्रमm data exists,
	 * otherwise use the शेष settings.
	 */
	अगर (pdata) अणु
		cfg->bl_mode    = pdata->bl_mode;
		cfg->dim_mode   = pdata->dim_mode;
		cfg->full_scale = pdata->full_scale;
		cfg->rise_समय  = pdata->rise_समय;
		cfg->fall_समय  = pdata->fall_समय;
		cfg->pwm_pol    = pdata->pwm_pol;
	पूर्ण

	/* Brightness ramp up/करोwn */
	val = (cfg->rise_समय << LP8788_BL_RAMP_RISE_SHIFT) | cfg->fall_समय;
	ret = lp8788_ग_लिखो_byte(bl->lp, LP8788_BL_RAMP, val);
	अगर (ret)
		वापस ret;

	/* Fullscale current setting */
	val = (cfg->full_scale << LP8788_BL_FULLSCALE_SHIFT) |
		(cfg->dim_mode << LP8788_BL_DIM_MODE_SHIFT);

	/* Brightness control mode */
	चयन (cfg->bl_mode) अणु
	हाल LP8788_BL_REGISTER_ONLY:
		val |= LP8788_BL_EN;
		अवरोध;
	हाल LP8788_BL_COMB_PWM_BASED:
	हाल LP8788_BL_COMB_REGISTER_BASED:
		val |= LP8788_BL_EN | LP8788_BL_PWM_INPUT_EN |
			(cfg->pwm_pol << LP8788_BL_PWM_POLARITY_SHIFT);
		अवरोध;
	शेष:
		dev_err(bl->lp->dev, "invalid mode: %d\n", cfg->bl_mode);
		वापस -EINVAL;
	पूर्ण

	bl->mode = cfg->bl_mode;

	वापस lp8788_ग_लिखो_byte(bl->lp, LP8788_BL_CONFIG, val);
पूर्ण

अटल व्योम lp8788_pwm_ctrl(काष्ठा lp8788_bl *bl, पूर्णांक br, पूर्णांक max_br)
अणु
	अचिन्हित पूर्णांक period;
	अचिन्हित पूर्णांक duty;
	काष्ठा device *dev;
	काष्ठा pwm_device *pwm;

	अगर (!bl->pdata)
		वापस;

	period = bl->pdata->period_ns;
	duty = br * period / max_br;
	dev = bl->lp->dev;

	/* request PWM device with the consumer name */
	अगर (!bl->pwm) अणु
		pwm = devm_pwm_get(dev, LP8788_DEV_BACKLIGHT);
		अगर (IS_ERR(pwm)) अणु
			dev_err(dev, "can not get PWM device\n");
			वापस;
		पूर्ण

		bl->pwm = pwm;

		/*
		 * FIXME: pwm_apply_args() should be हटाओd when चयनing to
		 * the atomic PWM API.
		 */
		pwm_apply_args(pwm);
	पूर्ण

	pwm_config(bl->pwm, duty, period);
	अगर (duty)
		pwm_enable(bl->pwm);
	अन्यथा
		pwm_disable(bl->pwm);
पूर्ण

अटल पूर्णांक lp8788_bl_update_status(काष्ठा backlight_device *bl_dev)
अणु
	काष्ठा lp8788_bl *bl = bl_get_data(bl_dev);
	क्रमागत lp8788_bl_ctrl_mode mode = bl->mode;

	अगर (bl_dev->props.state & BL_CORE_SUSPENDED)
		bl_dev->props.brightness = 0;

	अगर (is_brightness_ctrl_by_pwm(mode)) अणु
		पूर्णांक brt = bl_dev->props.brightness;
		पूर्णांक max = bl_dev->props.max_brightness;

		lp8788_pwm_ctrl(bl, brt, max);
	पूर्ण अन्यथा अगर (is_brightness_ctrl_by_रेजिस्टर(mode)) अणु
		u8 brt = bl_dev->props.brightness;

		lp8788_ग_लिखो_byte(bl->lp, LP8788_BL_BRIGHTNESS, brt);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops lp8788_bl_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.update_status = lp8788_bl_update_status,
पूर्ण;

अटल पूर्णांक lp8788_backlight_रेजिस्टर(काष्ठा lp8788_bl *bl)
अणु
	काष्ठा backlight_device *bl_dev;
	काष्ठा backlight_properties props;
	काष्ठा lp8788_backlight_platक्रमm_data *pdata = bl->pdata;
	पूर्णांक init_brt;
	अक्षर *name;

	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = MAX_BRIGHTNESS;

	/* Initial brightness */
	अगर (pdata)
		init_brt = min_t(पूर्णांक, pdata->initial_brightness,
				props.max_brightness);
	अन्यथा
		init_brt = 0;

	props.brightness = init_brt;

	/* Backlight device name */
	अगर (!pdata || !pdata->name)
		name = DEFAULT_BL_NAME;
	अन्यथा
		name = pdata->name;

	bl_dev = backlight_device_रेजिस्टर(name, bl->lp->dev, bl,
				       &lp8788_bl_ops, &props);
	अगर (IS_ERR(bl_dev))
		वापस PTR_ERR(bl_dev);

	bl->bl_dev = bl_dev;

	वापस 0;
पूर्ण

अटल व्योम lp8788_backlight_unरेजिस्टर(काष्ठा lp8788_bl *bl)
अणु
	काष्ठा backlight_device *bl_dev = bl->bl_dev;

	backlight_device_unरेजिस्टर(bl_dev);
पूर्ण

अटल sमाप_प्रकार lp8788_get_bl_ctl_mode(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lp8788_bl *bl = dev_get_drvdata(dev);
	क्रमागत lp8788_bl_ctrl_mode mode = bl->mode;
	अक्षर *strmode;

	अगर (is_brightness_ctrl_by_pwm(mode))
		strmode = "PWM based";
	अन्यथा अगर (is_brightness_ctrl_by_रेजिस्टर(mode))
		strmode = "Register based";
	अन्यथा
		strmode = "Invalid mode";

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", strmode);
पूर्ण

अटल DEVICE_ATTR(bl_ctl_mode, S_IRUGO, lp8788_get_bl_ctl_mode, शून्य);

अटल काष्ठा attribute *lp8788_attributes[] = अणु
	&dev_attr_bl_ctl_mode.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group lp8788_attr_group = अणु
	.attrs = lp8788_attributes,
पूर्ण;

अटल पूर्णांक lp8788_backlight_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	काष्ठा lp8788_bl *bl;
	पूर्णांक ret;

	bl = devm_kzalloc(lp->dev, माप(काष्ठा lp8788_bl), GFP_KERNEL);
	अगर (!bl)
		वापस -ENOMEM;

	bl->lp = lp;
	अगर (lp->pdata)
		bl->pdata = lp->pdata->bl_pdata;

	platक्रमm_set_drvdata(pdev, bl);

	ret = lp8788_backlight_configure(bl);
	अगर (ret) अणु
		dev_err(lp->dev, "backlight config err: %d\n", ret);
		जाओ err_dev;
	पूर्ण

	ret = lp8788_backlight_रेजिस्टर(bl);
	अगर (ret) अणु
		dev_err(lp->dev, "register backlight err: %d\n", ret);
		जाओ err_dev;
	पूर्ण

	ret = sysfs_create_group(&pdev->dev.kobj, &lp8788_attr_group);
	अगर (ret) अणु
		dev_err(lp->dev, "register sysfs err: %d\n", ret);
		जाओ err_sysfs;
	पूर्ण

	backlight_update_status(bl->bl_dev);

	वापस 0;

err_sysfs:
	lp8788_backlight_unरेजिस्टर(bl);
err_dev:
	वापस ret;
पूर्ण

अटल पूर्णांक lp8788_backlight_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp8788_bl *bl = platक्रमm_get_drvdata(pdev);
	काष्ठा backlight_device *bl_dev = bl->bl_dev;

	bl_dev->props.brightness = 0;
	backlight_update_status(bl_dev);
	sysfs_हटाओ_group(&pdev->dev.kobj, &lp8788_attr_group);
	lp8788_backlight_unरेजिस्टर(bl);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver lp8788_bl_driver = अणु
	.probe = lp8788_backlight_probe,
	.हटाओ = lp8788_backlight_हटाओ,
	.driver = अणु
		.name = LP8788_DEV_BACKLIGHT,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lp8788_bl_driver);

MODULE_DESCRIPTION("Texas Instruments LP8788 Backlight Driver");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lp8788-backlight");
