<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Simple PWM based backlight control, board code has to setup
 * 1) pin configuration so PWM waveक्रमms can output
 * 2) platक्रमm_data being correctly configured
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/err.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

काष्ठा pwm_bl_data अणु
	काष्ठा pwm_device	*pwm;
	काष्ठा device		*dev;
	अचिन्हित पूर्णांक		lth_brightness;
	अचिन्हित पूर्णांक		*levels;
	bool			enabled;
	काष्ठा regulator	*घातer_supply;
	काष्ठा gpio_desc	*enable_gpio;
	अचिन्हित पूर्णांक		scale;
	bool			legacy;
	अचिन्हित पूर्णांक		post_pwm_on_delay;
	अचिन्हित पूर्णांक		pwm_off_delay;
	पूर्णांक			(*notअगरy)(काष्ठा device *,
					  पूर्णांक brightness);
	व्योम			(*notअगरy_after)(काष्ठा device *,
					पूर्णांक brightness);
	पूर्णांक			(*check_fb)(काष्ठा device *, काष्ठा fb_info *);
	व्योम			(*निकास)(काष्ठा device *);
पूर्ण;

अटल व्योम pwm_backlight_घातer_on(काष्ठा pwm_bl_data *pb)
अणु
	काष्ठा pwm_state state;
	पूर्णांक err;

	pwm_get_state(pb->pwm, &state);
	अगर (pb->enabled)
		वापस;

	err = regulator_enable(pb->घातer_supply);
	अगर (err < 0)
		dev_err(pb->dev, "failed to enable power supply\n");

	state.enabled = true;
	pwm_apply_state(pb->pwm, &state);

	अगर (pb->post_pwm_on_delay)
		msleep(pb->post_pwm_on_delay);

	अगर (pb->enable_gpio)
		gpiod_set_value_cansleep(pb->enable_gpio, 1);

	pb->enabled = true;
पूर्ण

अटल व्योम pwm_backlight_घातer_off(काष्ठा pwm_bl_data *pb)
अणु
	काष्ठा pwm_state state;

	pwm_get_state(pb->pwm, &state);
	अगर (!pb->enabled)
		वापस;

	अगर (pb->enable_gpio)
		gpiod_set_value_cansleep(pb->enable_gpio, 0);

	अगर (pb->pwm_off_delay)
		msleep(pb->pwm_off_delay);

	state.enabled = false;
	state.duty_cycle = 0;
	pwm_apply_state(pb->pwm, &state);

	regulator_disable(pb->घातer_supply);
	pb->enabled = false;
पूर्ण

अटल पूर्णांक compute_duty_cycle(काष्ठा pwm_bl_data *pb, पूर्णांक brightness)
अणु
	अचिन्हित पूर्णांक lth = pb->lth_brightness;
	काष्ठा pwm_state state;
	u64 duty_cycle;

	pwm_get_state(pb->pwm, &state);

	अगर (pb->levels)
		duty_cycle = pb->levels[brightness];
	अन्यथा
		duty_cycle = brightness;

	duty_cycle *= state.period - lth;
	करो_भाग(duty_cycle, pb->scale);

	वापस duty_cycle + lth;
पूर्ण

अटल पूर्णांक pwm_backlight_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा pwm_bl_data *pb = bl_get_data(bl);
	पूर्णांक brightness = backlight_get_brightness(bl);
	काष्ठा pwm_state state;

	अगर (pb->notअगरy)
		brightness = pb->notअगरy(pb->dev, brightness);

	अगर (brightness > 0) अणु
		pwm_get_state(pb->pwm, &state);
		state.duty_cycle = compute_duty_cycle(pb, brightness);
		pwm_apply_state(pb->pwm, &state);
		pwm_backlight_घातer_on(pb);
	पूर्ण अन्यथा अणु
		pwm_backlight_घातer_off(pb);
	पूर्ण

	अगर (pb->notअगरy_after)
		pb->notअगरy_after(pb->dev, brightness);

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_backlight_check_fb(काष्ठा backlight_device *bl,
				  काष्ठा fb_info *info)
अणु
	काष्ठा pwm_bl_data *pb = bl_get_data(bl);

	वापस !pb->check_fb || pb->check_fb(pb->dev, info);
पूर्ण

अटल स्थिर काष्ठा backlight_ops pwm_backlight_ops = अणु
	.update_status	= pwm_backlight_update_status,
	.check_fb	= pwm_backlight_check_fb,
पूर्ण;

#अगर_घोषित CONFIG_OF
#घोषणा PWM_LUMIन_अंकCE_SHIFT	16
#घोषणा PWM_LUMIन_अंकCE_SCALE	(1 << PWM_LUMIन_अंकCE_SHIFT) /* luminance scale */

/*
 * CIE lightness to PWM conversion.
 *
 * The CIE 1931 lightness क्रमmula is what actually describes how we perceive
 * light:
 *          Y = (L* / 903.3)           अगर L* ै	अ 8
 *          Y = ((L* + 16) / 116)^3    अगर L* > 8
 *
 * Where Y is the luminance, the amount of light coming out of the screen, and
 * is a number between 0.0 and 1.0; and L* is the lightness, how bright a human
 * perceives the screen to be, and is a number between 0 and 100.
 *
 * The following function करोes the fixed poपूर्णांक maths needed to implement the
 * above क्रमmula.
 */
अटल u64 cie1931(अचिन्हित पूर्णांक lightness)
अणु
	u64 retval;

	/*
	 * @lightness is given as a number between 0 and 1, expressed
	 * as a fixed-poपूर्णांक number in scale
	 * PWM_LUMIन_अंकCE_SCALE. Convert to a percentage, still
	 * expressed as a fixed-poपूर्णांक number, so the above क्रमmulas
	 * can be applied.
	 */
	lightness *= 100;
	अगर (lightness <= (8 * PWM_LUMIन_अंकCE_SCALE)) अणु
		retval = DIV_ROUND_CLOSEST(lightness * 10, 9033);
	पूर्ण अन्यथा अणु
		retval = (lightness + (16 * PWM_LUMIन_अंकCE_SCALE)) / 116;
		retval *= retval * retval;
		retval += 1ULL << (2*PWM_LUMIन_अंकCE_SHIFT - 1);
		retval >>= 2*PWM_LUMIन_अंकCE_SHIFT;
	पूर्ण

	वापस retval;
पूर्ण

/*
 * Create a शेष correction table क्रम PWM values to create linear brightness
 * क्रम LED based backlights using the CIE1931 algorithm.
 */
अटल
पूर्णांक pwm_backlight_brightness_शेष(काष्ठा device *dev,
				     काष्ठा platक्रमm_pwm_backlight_data *data,
				     अचिन्हित पूर्णांक period)
अणु
	अचिन्हित पूर्णांक i;
	u64 retval;

	/*
	 * Once we have 4096 levels there's little poपूर्णांक going much higher...
	 * neither पूर्णांकeractive sliders nor animation benefits from having
	 * more values in the table.
	 */
	data->max_brightness =
		min((पूर्णांक)DIV_ROUND_UP(period, fls(period)), 4096);

	data->levels = devm_kसुस्मृति(dev, data->max_brightness,
				    माप(*data->levels), GFP_KERNEL);
	अगर (!data->levels)
		वापस -ENOMEM;

	/* Fill the table using the cie1931 algorithm */
	क्रम (i = 0; i < data->max_brightness; i++) अणु
		retval = cie1931((i * PWM_LUMIन_अंकCE_SCALE) /
				 data->max_brightness) * period;
		retval = DIV_ROUND_CLOSEST_ULL(retval, PWM_LUMIन_अंकCE_SCALE);
		अगर (retval > अच_पूर्णांक_उच्च)
			वापस -EINVAL;
		data->levels[i] = (अचिन्हित पूर्णांक)retval;
	पूर्ण

	data->dft_brightness = data->max_brightness / 2;
	data->max_brightness--;

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_backlight_parse_dt(काष्ठा device *dev,
				  काष्ठा platक्रमm_pwm_backlight_data *data)
अणु
	काष्ठा device_node *node = dev->of_node;
	अचिन्हित पूर्णांक num_levels;
	अचिन्हित पूर्णांक num_steps = 0;
	काष्ठा property *prop;
	अचिन्हित पूर्णांक *table;
	पूर्णांक length;
	u32 value;
	पूर्णांक ret;

	अगर (!node)
		वापस -ENODEV;

	स_रखो(data, 0, माप(*data));

	/*
	 * These values are optional and set as 0 by शेष, the out values
	 * are modअगरied only अगर a valid u32 value can be decoded.
	 */
	of_property_पढ़ो_u32(node, "post-pwm-on-delay-ms",
			     &data->post_pwm_on_delay);
	of_property_पढ़ो_u32(node, "pwm-off-delay-ms", &data->pwm_off_delay);

	/*
	 * Determine the number of brightness levels, अगर this property is not
	 * set a शेष table of brightness levels will be used.
	 */
	prop = of_find_property(node, "brightness-levels", &length);
	अगर (!prop)
		वापस 0;

	num_levels = length / माप(u32);

	/* पढ़ो brightness levels from DT property */
	अगर (num_levels > 0) अणु
		माप_प्रकार size = माप(*data->levels) * num_levels;

		data->levels = devm_kzalloc(dev, size, GFP_KERNEL);
		अगर (!data->levels)
			वापस -ENOMEM;

		ret = of_property_पढ़ो_u32_array(node, "brightness-levels",
						 data->levels,
						 num_levels);
		अगर (ret < 0)
			वापस ret;

		ret = of_property_पढ़ो_u32(node, "default-brightness-level",
					   &value);
		अगर (ret < 0)
			वापस ret;

		data->dft_brightness = value;

		/*
		 * This property is optional, अगर is set enables linear
		 * पूर्णांकerpolation between each of the values of brightness levels
		 * and creates a new pre-computed table.
		 */
		of_property_पढ़ो_u32(node, "num-interpolated-steps",
				     &num_steps);

		/*
		 * Make sure that there is at least two entries in the
		 * brightness-levels table, otherwise we can't पूर्णांकerpolate
		 * between two poपूर्णांकs.
		 */
		अगर (num_steps) अणु
			अचिन्हित पूर्णांक num_input_levels = num_levels;
			अचिन्हित पूर्णांक i;
			u32 x1, x2, x, dx;
			u32 y1, y2;
			s64 dy;

			अगर (num_input_levels < 2) अणु
				dev_err(dev, "can't interpolate\n");
				वापस -EINVAL;
			पूर्ण

			/*
			 * Recalculate the number of brightness levels, now
			 * taking in consideration the number of पूर्णांकerpolated
			 * steps between two levels.
			 */
			num_levels = (num_input_levels - 1) * num_steps + 1;
			dev_dbg(dev, "new number of brightness levels: %d\n",
				num_levels);

			/*
			 * Create a new table of brightness levels with all the
			 * पूर्णांकerpolated steps.
			 */
			size = माप(*table) * num_levels;
			table = devm_kzalloc(dev, size, GFP_KERNEL);
			अगर (!table)
				वापस -ENOMEM;
			/*
			 * Fill the पूर्णांकerpolated table[x] = y
			 * by draw lines between each (x1, y1) to (x2, y2).
			 */
			dx = num_steps;
			क्रम (i = 0; i < num_input_levels - 1; i++) अणु
				x1 = i * dx;
				x2 = x1 + dx;
				y1 = data->levels[i];
				y2 = data->levels[i + 1];
				dy = (s64)y2 - y1;

				क्रम (x = x1; x < x2; x++) अणु
					table[x] = y1 +
						भाग_s64(dy * (x - x1), dx);
				पूर्ण
			पूर्ण
			/* Fill in the last poपूर्णांक, since no line starts here. */
			table[x2] = y2;

			/*
			 * As we use पूर्णांकerpolation lets हटाओ current
			 * brightness levels table and replace क्रम the
			 * new पूर्णांकerpolated table.
			 */
			devm_kमुक्त(dev, data->levels);
			data->levels = table;
		पूर्ण

		data->max_brightness = num_levels - 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pwm_backlight_of_match[] = अणु
	अणु .compatible = "pwm-backlight" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, pwm_backlight_of_match);
#अन्यथा
अटल पूर्णांक pwm_backlight_parse_dt(काष्ठा device *dev,
				  काष्ठा platक्रमm_pwm_backlight_data *data)
अणु
	वापस -ENODEV;
पूर्ण

अटल
पूर्णांक pwm_backlight_brightness_शेष(काष्ठा device *dev,
				     काष्ठा platक्रमm_pwm_backlight_data *data,
				     अचिन्हित पूर्णांक period)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल bool pwm_backlight_is_linear(काष्ठा platक्रमm_pwm_backlight_data *data)
अणु
	अचिन्हित पूर्णांक nlevels = data->max_brightness + 1;
	अचिन्हित पूर्णांक min_val = data->levels[0];
	अचिन्हित पूर्णांक max_val = data->levels[nlevels - 1];
	/*
	 * Multiplying by 128 means that even in pathological हालs such
	 * as (max_val - min_val) == nlevels the error at max_val is less
	 * than 1%.
	 */
	अचिन्हित पूर्णांक slope = (128 * (max_val - min_val)) / nlevels;
	अचिन्हित पूर्णांक margin = (max_val - min_val) / 20; /* 5% */
	पूर्णांक i;

	क्रम (i = 1; i < nlevels; i++) अणु
		अचिन्हित पूर्णांक linear_value = min_val + ((i * slope) / 128);
		अचिन्हित पूर्णांक delta = असल(linear_value - data->levels[i]);

		अगर (delta > margin)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक pwm_backlight_initial_घातer_state(स्थिर काष्ठा pwm_bl_data *pb)
अणु
	काष्ठा device_node *node = pb->dev->of_node;

	/* Not booted with device tree or no phandle link to the node */
	अगर (!node || !node->phandle)
		वापस FB_BLANK_UNBLANK;

	/*
	 * If the driver is probed from the device tree and there is a
	 * phandle link poपूर्णांकing to the backlight node, it is safe to
	 * assume that another driver will enable the backlight at the
	 * appropriate समय. Thereक्रमe, अगर it is disabled, keep it so.
	 */

	/* अगर the enable GPIO is disabled, करो not enable the backlight */
	अगर (pb->enable_gpio && gpiod_get_value_cansleep(pb->enable_gpio) == 0)
		वापस FB_BLANK_POWERDOWN;

	/* The regulator is disabled, करो not enable the backlight */
	अगर (!regulator_is_enabled(pb->घातer_supply))
		वापस FB_BLANK_POWERDOWN;

	/* The PWM is disabled, keep it like this */
	अगर (!pwm_is_enabled(pb->pwm))
		वापस FB_BLANK_POWERDOWN;

	वापस FB_BLANK_UNBLANK;
पूर्ण

अटल पूर्णांक pwm_backlight_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_pwm_backlight_data *data = dev_get_platdata(&pdev->dev);
	काष्ठा platक्रमm_pwm_backlight_data defdata;
	काष्ठा backlight_properties props;
	काष्ठा backlight_device *bl;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा pwm_bl_data *pb;
	काष्ठा pwm_state state;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!data) अणु
		ret = pwm_backlight_parse_dt(&pdev->dev, &defdata);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "failed to find platform data\n");
			वापस ret;
		पूर्ण

		data = &defdata;
	पूर्ण

	अगर (data->init) अणु
		ret = data->init(&pdev->dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	pb = devm_kzalloc(&pdev->dev, माप(*pb), GFP_KERNEL);
	अगर (!pb) अणु
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	pb->notअगरy = data->notअगरy;
	pb->notअगरy_after = data->notअगरy_after;
	pb->check_fb = data->check_fb;
	pb->निकास = data->निकास;
	pb->dev = &pdev->dev;
	pb->enabled = false;
	pb->post_pwm_on_delay = data->post_pwm_on_delay;
	pb->pwm_off_delay = data->pwm_off_delay;

	pb->enable_gpio = devm_gpiod_get_optional(&pdev->dev, "enable",
						  GPIOD_ASIS);
	अगर (IS_ERR(pb->enable_gpio)) अणु
		ret = PTR_ERR(pb->enable_gpio);
		जाओ err_alloc;
	पूर्ण

	/*
	 * If the GPIO is not known to be alपढ़ोy configured as output, that
	 * is, अगर gpiod_get_direction वापसs either 1 or -EINVAL, change the
	 * direction to output and set the GPIO as active.
	 * Do not क्रमce the GPIO to active when it was alपढ़ोy output as it
	 * could cause backlight flickering or we would enable the backlight too
	 * early. Leave the decision of the initial backlight state क्रम later.
	 */
	अगर (pb->enable_gpio &&
	    gpiod_get_direction(pb->enable_gpio) != 0)
		gpiod_direction_output(pb->enable_gpio, 1);

	pb->घातer_supply = devm_regulator_get(&pdev->dev, "power");
	अगर (IS_ERR(pb->घातer_supply)) अणु
		ret = PTR_ERR(pb->घातer_supply);
		जाओ err_alloc;
	पूर्ण

	pb->pwm = devm_pwm_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pb->pwm) && PTR_ERR(pb->pwm) != -EPROBE_DEFER && !node) अणु
		dev_err(&pdev->dev, "unable to request PWM, trying legacy API\n");
		pb->legacy = true;
		pb->pwm = pwm_request(data->pwm_id, "pwm-backlight");
	पूर्ण

	अगर (IS_ERR(pb->pwm)) अणु
		ret = PTR_ERR(pb->pwm);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "unable to request PWM\n");
		जाओ err_alloc;
	पूर्ण

	dev_dbg(&pdev->dev, "got pwm for backlight\n");

	/* Sync up PWM state. */
	pwm_init_state(pb->pwm, &state);

	/*
	 * The DT हाल will set the pwm_period_ns field to 0 and store the
	 * period, parsed from the DT, in the PWM device. For the non-DT हाल,
	 * set the period from platक्रमm data अगर it has not alपढ़ोy been set
	 * via the PWM lookup table.
	 */
	अगर (!state.period && (data->pwm_period_ns > 0))
		state.period = data->pwm_period_ns;

	ret = pwm_apply_state(pb->pwm, &state);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to apply initial PWM state: %d\n",
			ret);
		जाओ err_alloc;
	पूर्ण

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));

	अगर (data->levels) अणु
		pb->levels = data->levels;

		/*
		 * For the DT हाल, only when brightness levels is defined
		 * data->levels is filled. For the non-DT हाल, data->levels
		 * can come from platक्रमm data, however is not usual.
		 */
		क्रम (i = 0; i <= data->max_brightness; i++)
			अगर (data->levels[i] > pb->scale)
				pb->scale = data->levels[i];

		अगर (pwm_backlight_is_linear(data))
			props.scale = BACKLIGHT_SCALE_LINEAR;
		अन्यथा
			props.scale = BACKLIGHT_SCALE_NON_LINEAR;
	पूर्ण अन्यथा अगर (!data->max_brightness) अणु
		/*
		 * If no brightness levels are provided and max_brightness is
		 * not set, use the शेष brightness table. For the DT हाल,
		 * max_brightness is set to 0 when brightness levels is not
		 * specअगरied. For the non-DT हाल, max_brightness is usually
		 * set to some value.
		 */

		/* Get the PWM period (in nanoseconds) */
		pwm_get_state(pb->pwm, &state);

		ret = pwm_backlight_brightness_शेष(&pdev->dev, data,
						       state.period);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev,
				"failed to setup default brightness table\n");
			जाओ err_alloc;
		पूर्ण

		क्रम (i = 0; i <= data->max_brightness; i++) अणु
			अगर (data->levels[i] > pb->scale)
				pb->scale = data->levels[i];

			pb->levels = data->levels;
		पूर्ण

		props.scale = BACKLIGHT_SCALE_NON_LINEAR;
	पूर्ण अन्यथा अणु
		/*
		 * That only happens क्रम the non-DT हाल, where platक्रमm data
		 * sets the max_brightness value.
		 */
		pb->scale = data->max_brightness;
	पूर्ण

	pb->lth_brightness = data->lth_brightness * (भाग_u64(state.period,
				pb->scale));

	props.type = BACKLIGHT_RAW;
	props.max_brightness = data->max_brightness;
	bl = backlight_device_रेजिस्टर(dev_name(&pdev->dev), &pdev->dev, pb,
				       &pwm_backlight_ops, &props);
	अगर (IS_ERR(bl)) अणु
		dev_err(&pdev->dev, "failed to register backlight\n");
		ret = PTR_ERR(bl);
		अगर (pb->legacy)
			pwm_मुक्त(pb->pwm);
		जाओ err_alloc;
	पूर्ण

	अगर (data->dft_brightness > data->max_brightness) अणु
		dev_warn(&pdev->dev,
			 "invalid default brightness level: %u, using %u\n",
			 data->dft_brightness, data->max_brightness);
		data->dft_brightness = data->max_brightness;
	पूर्ण

	bl->props.brightness = data->dft_brightness;
	bl->props.घातer = pwm_backlight_initial_घातer_state(pb);
	backlight_update_status(bl);

	platक्रमm_set_drvdata(pdev, bl);
	वापस 0;

err_alloc:
	अगर (data->निकास)
		data->निकास(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक pwm_backlight_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_device *bl = platक्रमm_get_drvdata(pdev);
	काष्ठा pwm_bl_data *pb = bl_get_data(bl);

	backlight_device_unरेजिस्टर(bl);
	pwm_backlight_घातer_off(pb);

	अगर (pb->निकास)
		pb->निकास(&pdev->dev);
	अगर (pb->legacy)
		pwm_मुक्त(pb->pwm);

	वापस 0;
पूर्ण

अटल व्योम pwm_backlight_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_device *bl = platक्रमm_get_drvdata(pdev);
	काष्ठा pwm_bl_data *pb = bl_get_data(bl);

	pwm_backlight_घातer_off(pb);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pwm_backlight_suspend(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bl = dev_get_drvdata(dev);
	काष्ठा pwm_bl_data *pb = bl_get_data(bl);

	अगर (pb->notअगरy)
		pb->notअगरy(pb->dev, 0);

	pwm_backlight_घातer_off(pb);

	अगर (pb->notअगरy_after)
		pb->notअगरy_after(pb->dev, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_backlight_resume(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bl = dev_get_drvdata(dev);

	backlight_update_status(bl);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops pwm_backlight_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend = pwm_backlight_suspend,
	.resume = pwm_backlight_resume,
	.घातeroff = pwm_backlight_suspend,
	.restore = pwm_backlight_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा platक्रमm_driver pwm_backlight_driver = अणु
	.driver		= अणु
		.name		= "pwm-backlight",
		.pm		= &pwm_backlight_pm_ops,
		.of_match_table	= of_match_ptr(pwm_backlight_of_match),
	पूर्ण,
	.probe		= pwm_backlight_probe,
	.हटाओ		= pwm_backlight_हटाओ,
	.shutकरोwn	= pwm_backlight_shutकरोwn,
पूर्ण;

module_platक्रमm_driver(pwm_backlight_driver);

MODULE_DESCRIPTION("PWM based Backlight Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:pwm-backlight");
