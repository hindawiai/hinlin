<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Azoteq IQS624/625 Angular Position Sensors
 *
 * Copyright (C) 2019 Jeff LaBundy <jeff@labundy.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/iqs62x.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा IQS624_POS_DEG_OUT			0x16

#घोषणा IQS624_POS_SCALE1			(314159 / 180)
#घोषणा IQS624_POS_SCALE2			100000

काष्ठा iqs624_pos_निजी अणु
	काष्ठा iqs62x_core *iqs62x;
	काष्ठा iio_dev *indio_dev;
	काष्ठा notअगरier_block notअगरier;
	काष्ठा mutex lock;
	bool angle_en;
	u16 angle;
पूर्ण;

अटल पूर्णांक iqs624_pos_angle_en(काष्ठा iqs62x_core *iqs62x, bool angle_en)
अणु
	अचिन्हित पूर्णांक event_mask = IQS624_HALL_UI_WHL_EVENT;

	/*
	 * The IQS625 reports angular position in the क्रमm of coarse पूर्णांकervals,
	 * so only पूर्णांकerval change events are unmasked. Conversely, the IQS624
	 * reports angular position करोwn to one degree of resolution, so wheel
	 * movement events are unmasked instead.
	 */
	अगर (iqs62x->dev_desc->prod_num == IQS625_PROD_NUM)
		event_mask = IQS624_HALL_UI_INT_EVENT;

	वापस regmap_update_bits(iqs62x->regmap, IQS624_HALL_UI, event_mask,
				  angle_en ? 0 : 0xFF);
पूर्ण

अटल पूर्णांक iqs624_pos_notअगरier(काष्ठा notअगरier_block *notअगरier,
			       अचिन्हित दीर्घ event_flags, व्योम *context)
अणु
	काष्ठा iqs62x_event_data *event_data = context;
	काष्ठा iqs624_pos_निजी *iqs624_pos;
	काष्ठा iqs62x_core *iqs62x;
	काष्ठा iio_dev *indio_dev;
	u16 angle = event_data->ui_data;
	s64 बारtamp;
	पूर्णांक ret;

	iqs624_pos = container_of(notअगरier, काष्ठा iqs624_pos_निजी,
				  notअगरier);
	indio_dev = iqs624_pos->indio_dev;
	बारtamp = iio_get_समय_ns(indio_dev);

	iqs62x = iqs624_pos->iqs62x;
	अगर (iqs62x->dev_desc->prod_num == IQS625_PROD_NUM)
		angle = event_data->पूर्णांकerval;

	mutex_lock(&iqs624_pos->lock);

	अगर (event_flags & BIT(IQS62X_EVENT_SYS_RESET)) अणु
		ret = iqs624_pos_angle_en(iqs62x, iqs624_pos->angle_en);
		अगर (ret) अणु
			dev_err(indio_dev->dev.parent,
				"Failed to re-initialize device: %d\n", ret);
			ret = NOTIFY_BAD;
		पूर्ण अन्यथा अणु
			ret = NOTIFY_OK;
		पूर्ण
	पूर्ण अन्यथा अगर (iqs624_pos->angle_en && (angle != iqs624_pos->angle)) अणु
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_ANGL, 0,
						    IIO_EV_TYPE_CHANGE,
						    IIO_EV_सूची_NONE),
			       बारtamp);

		iqs624_pos->angle = angle;
		ret = NOTIFY_OK;
	पूर्ण अन्यथा अणु
		ret = NOTIFY_DONE;
	पूर्ण

	mutex_unlock(&iqs624_pos->lock);

	वापस ret;
पूर्ण

अटल व्योम iqs624_pos_notअगरier_unरेजिस्टर(व्योम *context)
अणु
	काष्ठा iqs624_pos_निजी *iqs624_pos = context;
	काष्ठा iio_dev *indio_dev = iqs624_pos->indio_dev;
	पूर्णांक ret;

	ret = blocking_notअगरier_chain_unरेजिस्टर(&iqs624_pos->iqs62x->nh,
						 &iqs624_pos->notअगरier);
	अगर (ret)
		dev_err(indio_dev->dev.parent,
			"Failed to unregister notifier: %d\n", ret);
पूर्ण

अटल पूर्णांक iqs624_pos_angle_get(काष्ठा iqs62x_core *iqs62x, अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;
	__le16 val_buf;

	अगर (iqs62x->dev_desc->prod_num == IQS625_PROD_NUM)
		वापस regmap_पढ़ो(iqs62x->regmap, iqs62x->dev_desc->पूर्णांकerval,
				   val);

	ret = regmap_raw_पढ़ो(iqs62x->regmap, IQS624_POS_DEG_OUT, &val_buf,
			      माप(val_buf));
	अगर (ret)
		वापस ret;

	*val = le16_to_cpu(val_buf);

	वापस 0;
पूर्ण

अटल पूर्णांक iqs624_pos_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा iqs624_pos_निजी *iqs624_pos = iio_priv(indio_dev);
	काष्ठा iqs62x_core *iqs62x = iqs624_pos->iqs62x;
	अचिन्हित पूर्णांक scale = 1;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iqs624_pos_angle_get(iqs62x, val);
		अगर (ret)
			वापस ret;

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		अगर (iqs62x->dev_desc->prod_num == IQS625_PROD_NUM) अणु
			ret = regmap_पढ़ो(iqs62x->regmap, IQS624_INTERVAL_DIV,
					  &scale);
			अगर (ret)
				वापस ret;
		पूर्ण

		*val = scale * IQS624_POS_SCALE1;
		*val2 = IQS624_POS_SCALE2;
		वापस IIO_VAL_FRACTIONAL;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक iqs624_pos_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan,
					क्रमागत iio_event_type type,
					क्रमागत iio_event_direction dir)
अणु
	काष्ठा iqs624_pos_निजी *iqs624_pos = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&iqs624_pos->lock);
	ret = iqs624_pos->angle_en;
	mutex_unlock(&iqs624_pos->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक iqs624_pos_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
					 स्थिर काष्ठा iio_chan_spec *chan,
					 क्रमागत iio_event_type type,
					 क्रमागत iio_event_direction dir,
					 पूर्णांक state)
अणु
	काष्ठा iqs624_pos_निजी *iqs624_pos = iio_priv(indio_dev);
	काष्ठा iqs62x_core *iqs62x = iqs624_pos->iqs62x;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	mutex_lock(&iqs624_pos->lock);

	ret = iqs624_pos_angle_get(iqs62x, &val);
	अगर (ret)
		जाओ err_mutex;

	ret = iqs624_pos_angle_en(iqs62x, state);
	अगर (ret)
		जाओ err_mutex;

	iqs624_pos->angle = val;
	iqs624_pos->angle_en = state;

err_mutex:
	mutex_unlock(&iqs624_pos->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info iqs624_pos_info = अणु
	.पढ़ो_raw = &iqs624_pos_पढ़ो_raw,
	.पढ़ो_event_config = iqs624_pos_पढ़ो_event_config,
	.ग_लिखो_event_config = iqs624_pos_ग_लिखो_event_config,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec iqs624_pos_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_CHANGE,
		.dir = IIO_EV_सूची_NONE,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec iqs624_pos_channels[] = अणु
	अणु
		.type = IIO_ANGL,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.event_spec = iqs624_pos_events,
		.num_event_specs = ARRAY_SIZE(iqs624_pos_events),
	पूर्ण,
पूर्ण;

अटल पूर्णांक iqs624_pos_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iqs62x_core *iqs62x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा iqs624_pos_निजी *iqs624_pos;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*iqs624_pos));
	अगर (!indio_dev)
		वापस -ENOMEM;

	iqs624_pos = iio_priv(indio_dev);
	iqs624_pos->iqs62x = iqs62x;
	iqs624_pos->indio_dev = indio_dev;

	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = iqs624_pos_channels;
	indio_dev->num_channels = ARRAY_SIZE(iqs624_pos_channels);
	indio_dev->name = iqs62x->dev_desc->dev_name;
	indio_dev->info = &iqs624_pos_info;

	mutex_init(&iqs624_pos->lock);

	iqs624_pos->notअगरier.notअगरier_call = iqs624_pos_notअगरier;
	ret = blocking_notअगरier_chain_रेजिस्टर(&iqs624_pos->iqs62x->nh,
					       &iqs624_pos->notअगरier);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register notifier: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&pdev->dev,
				       iqs624_pos_notअगरier_unरेजिस्टर,
				       iqs624_pos);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&pdev->dev, indio_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver iqs624_pos_platक्रमm_driver = अणु
	.driver = अणु
		.name = "iqs624-pos",
	पूर्ण,
	.probe = iqs624_pos_probe,
पूर्ण;
module_platक्रमm_driver(iqs624_pos_platक्रमm_driver);

MODULE_AUTHOR("Jeff LaBundy <jeff@labundy.com>");
MODULE_DESCRIPTION("Azoteq IQS624/625 Angular Position Sensors");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:iqs624-pos");
