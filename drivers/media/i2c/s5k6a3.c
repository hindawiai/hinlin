<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung S5K6A3 image sensor driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा S5K6A3_SENSOR_MAX_WIDTH		1412
#घोषणा S5K6A3_SENSOR_MAX_HEIGHT	1412
#घोषणा S5K6A3_SENSOR_MIN_WIDTH		32
#घोषणा S5K6A3_SENSOR_MIN_HEIGHT	32

#घोषणा S5K6A3_DEFAULT_WIDTH		1296
#घोषणा S5K6A3_DEFAULT_HEIGHT		732

#घोषणा S5K6A3_DRV_NAME			"S5K6A3"
#घोषणा S5K6A3_CLK_NAME			"extclk"
#घोषणा S5K6A3_DEFAULT_CLK_FREQ		24000000U

क्रमागत अणु
	S5K6A3_SUPP_VDDA,
	S5K6A3_SUPP_VDDIO,
	S5K6A3_SUPP_AFVDD,
	S5K6A3_NUM_SUPPLIES,
पूर्ण;

/**
 * काष्ठा s5k6a3 - fimc-is sensor data काष्ठाure
 * @dev: poपूर्णांकer to this I2C client device काष्ठाure
 * @subdev: the image sensor's v4l2 subdev
 * @pad: subdev media source pad
 * @supplies: image sensor's voltage regulator supplies
 * @gpio_reset: GPIO connected to the sensor's reset pin
 * @lock: mutex protecting the काष्ठाure's members below
 * @क्रमmat: media bus क्रमmat at the sensor's source pad
 * @घड़ी: poपूर्णांकer to &काष्ठा clk.
 * @घड़ी_frequency: घड़ी frequency
 * @घातer_count: stores state अगर device is घातered
 */
काष्ठा s5k6a3 अणु
	काष्ठा device *dev;
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pad;
	काष्ठा regulator_bulk_data supplies[S5K6A3_NUM_SUPPLIES];
	पूर्णांक gpio_reset;
	काष्ठा mutex lock;
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	काष्ठा clk *घड़ी;
	u32 घड़ी_frequency;
	पूर्णांक घातer_count;
पूर्ण;

अटल स्थिर अक्षर * स्थिर s5k6a3_supply_names[] = अणु
	[S5K6A3_SUPP_VDDA]	= "svdda",
	[S5K6A3_SUPP_VDDIO]	= "svddio",
	[S5K6A3_SUPP_AFVDD]	= "afvdd",
पूर्ण;

अटल अंतरभूत काष्ठा s5k6a3 *sd_to_s5k6a3(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा s5k6a3, subdev);
पूर्ण

अटल स्थिर काष्ठा v4l2_mbus_framefmt s5k6a3_क्रमmats[] = अणु
	अणु
		.code = MEDIA_BUS_FMT_SGRBG10_1X10,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.field = V4L2_FIELD_NONE,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा v4l2_mbus_framefmt *find_sensor_क्रमmat(
	काष्ठा v4l2_mbus_framefmt *mf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(s5k6a3_क्रमmats); i++)
		अगर (mf->code == s5k6a3_क्रमmats[i].code)
			वापस &s5k6a3_क्रमmats[i];

	वापस &s5k6a3_क्रमmats[0];
पूर्ण

अटल पूर्णांक s5k6a3_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= ARRAY_SIZE(s5k6a3_क्रमmats))
		वापस -EINVAL;

	code->code = s5k6a3_क्रमmats[code->index].code;
	वापस 0;
पूर्ण

अटल व्योम s5k6a3_try_क्रमmat(काष्ठा v4l2_mbus_framefmt *mf)
अणु
	स्थिर काष्ठा v4l2_mbus_framefmt *fmt;

	fmt = find_sensor_क्रमmat(mf);
	mf->code = fmt->code;
	mf->field = V4L2_FIELD_NONE;
	v4l_bound_align_image(&mf->width, S5K6A3_SENSOR_MIN_WIDTH,
			      S5K6A3_SENSOR_MAX_WIDTH, 0,
			      &mf->height, S5K6A3_SENSOR_MIN_HEIGHT,
			      S5K6A3_SENSOR_MAX_HEIGHT, 0, 0);
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *__s5k6a3_get_क्रमmat(
		काष्ठा s5k6a3 *sensor, काष्ठा v4l2_subdev_pad_config *cfg,
		u32 pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस cfg ? v4l2_subdev_get_try_क्रमmat(&sensor->subdev, cfg, pad) : शून्य;

	वापस &sensor->क्रमmat;
पूर्ण

अटल पूर्णांक s5k6a3_set_fmt(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा s5k6a3 *sensor = sd_to_s5k6a3(sd);
	काष्ठा v4l2_mbus_framefmt *mf;

	s5k6a3_try_क्रमmat(&fmt->क्रमmat);

	mf = __s5k6a3_get_क्रमmat(sensor, cfg, fmt->pad, fmt->which);
	अगर (mf) अणु
		mutex_lock(&sensor->lock);
		*mf = fmt->क्रमmat;
		mutex_unlock(&sensor->lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5k6a3_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा s5k6a3 *sensor = sd_to_s5k6a3(sd);
	काष्ठा v4l2_mbus_framefmt *mf;

	mf = __s5k6a3_get_क्रमmat(sensor, cfg, fmt->pad, fmt->which);

	mutex_lock(&sensor->lock);
	fmt->क्रमmat = *mf;
	mutex_unlock(&sensor->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops s5k6a3_pad_ops = अणु
	.क्रमागत_mbus_code	= s5k6a3_क्रमागत_mbus_code,
	.get_fmt	= s5k6a3_get_fmt,
	.set_fmt	= s5k6a3_set_fmt,
पूर्ण;

अटल पूर्णांक s5k6a3_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);

	*क्रमmat		= s5k6a3_क्रमmats[0];
	क्रमmat->width	= S5K6A3_DEFAULT_WIDTH;
	क्रमmat->height	= S5K6A3_DEFAULT_HEIGHT;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops s5k6a3_sd_पूर्णांकernal_ops = अणु
	.खोलो = s5k6a3_खोलो,
पूर्ण;

अटल पूर्णांक __s5k6a3_घातer_on(काष्ठा s5k6a3 *sensor)
अणु
	पूर्णांक i = S5K6A3_SUPP_VDDA;
	पूर्णांक ret;

	ret = clk_set_rate(sensor->घड़ी, sensor->घड़ी_frequency);
	अगर (ret < 0)
		वापस ret;

	ret = pm_runसमय_get(sensor->dev);
	अगर (ret < 0)
		जाओ error_rpm_put;

	ret = regulator_enable(sensor->supplies[i].consumer);
	अगर (ret < 0)
		जाओ error_rpm_put;

	ret = clk_prepare_enable(sensor->घड़ी);
	अगर (ret < 0)
		जाओ error_reg_dis;

	क्रम (i++; i < S5K6A3_NUM_SUPPLIES; i++) अणु
		ret = regulator_enable(sensor->supplies[i].consumer);
		अगर (ret < 0)
			जाओ error_reg_dis;
	पूर्ण

	gpio_set_value(sensor->gpio_reset, 1);
	usleep_range(600, 800);
	gpio_set_value(sensor->gpio_reset, 0);
	usleep_range(600, 800);
	gpio_set_value(sensor->gpio_reset, 1);

	/* Delay needed क्रम the sensor initialization */
	msleep(20);
	वापस 0;

error_reg_dis:
	क्रम (--i; i >= 0; --i)
		regulator_disable(sensor->supplies[i].consumer);
error_rpm_put:
	pm_runसमय_put(sensor->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक __s5k6a3_घातer_off(काष्ठा s5k6a3 *sensor)
अणु
	पूर्णांक i;

	gpio_set_value(sensor->gpio_reset, 0);

	क्रम (i = S5K6A3_NUM_SUPPLIES - 1; i >= 0; i--)
		regulator_disable(sensor->supplies[i].consumer);

	clk_disable_unprepare(sensor->घड़ी);
	pm_runसमय_put(sensor->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक s5k6a3_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा s5k6a3 *sensor = sd_to_s5k6a3(sd);
	पूर्णांक ret = 0;

	mutex_lock(&sensor->lock);

	अगर (sensor->घातer_count == !on) अणु
		अगर (on)
			ret = __s5k6a3_घातer_on(sensor);
		अन्यथा
			ret = __s5k6a3_घातer_off(sensor);

		अगर (ret == 0)
			sensor->घातer_count += on ? 1 : -1;
	पूर्ण

	mutex_unlock(&sensor->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops s5k6a3_core_ops = अणु
	.s_घातer = s5k6a3_s_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops s5k6a3_subdev_ops = अणु
	.core = &s5k6a3_core_ops,
	.pad = &s5k6a3_pad_ops,
पूर्ण;

अटल पूर्णांक s5k6a3_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा s5k6a3 *sensor;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक gpio, i, ret;

	sensor = devm_kzalloc(dev, माप(*sensor), GFP_KERNEL);
	अगर (!sensor)
		वापस -ENOMEM;

	mutex_init(&sensor->lock);
	sensor->gpio_reset = -EINVAL;
	sensor->घड़ी = ERR_PTR(-EINVAL);
	sensor->dev = dev;

	sensor->घड़ी = devm_clk_get(sensor->dev, S5K6A3_CLK_NAME);
	अगर (IS_ERR(sensor->घड़ी))
		वापस PTR_ERR(sensor->घड़ी);

	gpio = of_get_gpio_flags(dev->of_node, 0, शून्य);
	अगर (!gpio_is_valid(gpio))
		वापस gpio;

	ret = devm_gpio_request_one(dev, gpio, GPIOF_OUT_INIT_LOW,
						S5K6A3_DRV_NAME);
	अगर (ret < 0)
		वापस ret;

	sensor->gpio_reset = gpio;

	अगर (of_property_पढ़ो_u32(dev->of_node, "clock-frequency",
				 &sensor->घड़ी_frequency)) अणु
		sensor->घड़ी_frequency = S5K6A3_DEFAULT_CLK_FREQ;
		dev_info(dev, "using default %u Hz clock frequency\n",
					sensor->घड़ी_frequency);
	पूर्ण

	क्रम (i = 0; i < S5K6A3_NUM_SUPPLIES; i++)
		sensor->supplies[i].supply = s5k6a3_supply_names[i];

	ret = devm_regulator_bulk_get(&client->dev, S5K6A3_NUM_SUPPLIES,
				      sensor->supplies);
	अगर (ret < 0)
		वापस ret;

	sd = &sensor->subdev;
	v4l2_i2c_subdev_init(sd, client, &s5k6a3_subdev_ops);
	sensor->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	sd->पूर्णांकernal_ops = &s5k6a3_sd_पूर्णांकernal_ops;

	sensor->क्रमmat.code = s5k6a3_क्रमmats[0].code;
	sensor->क्रमmat.width = S5K6A3_DEFAULT_WIDTH;
	sensor->क्रमmat.height = S5K6A3_DEFAULT_HEIGHT;

	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
	sensor->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&sd->entity, 1, &sensor->pad);
	अगर (ret < 0)
		वापस ret;

	pm_runसमय_no_callbacks(dev);
	pm_runसमय_enable(dev);

	ret = v4l2_async_रेजिस्टर_subdev(sd);

	अगर (ret < 0) अणु
		pm_runसमय_disable(&client->dev);
		media_entity_cleanup(&sd->entity);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक s5k6a3_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	pm_runसमय_disable(&client->dev);
	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id s5k6a3_ids[] = अणु
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, s5k6a3_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id s5k6a3_of_match[] = अणु
	अणु .compatible = "samsung,s5k6a3" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, s5k6a3_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver s5k6a3_driver = अणु
	.driver = अणु
		.of_match_table	= of_match_ptr(s5k6a3_of_match),
		.name		= S5K6A3_DRV_NAME,
	पूर्ण,
	.probe_new	= s5k6a3_probe,
	.हटाओ		= s5k6a3_हटाओ,
	.id_table	= s5k6a3_ids,
पूर्ण;

module_i2c_driver(s5k6a3_driver);

MODULE_DESCRIPTION("S5K6A3 image sensor subdev driver");
MODULE_AUTHOR("Sylwester Nawrocki <s.nawrocki@samsung.com>");
MODULE_LICENSE("GPL v2");
