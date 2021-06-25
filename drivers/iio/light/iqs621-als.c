<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Azoteq IQS621/622 Ambient Light Sensors
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

#घोषणा IQS621_ALS_FLAGS_LIGHT			BIT(7)
#घोषणा IQS621_ALS_FLAGS_RANGE			GENMASK(3, 0)

#घोषणा IQS621_ALS_UI_OUT			0x17

#घोषणा IQS621_ALS_THRESH_DARK			0x80
#घोषणा IQS621_ALS_THRESH_LIGHT			0x81

#घोषणा IQS622_IR_RANGE				0x15
#घोषणा IQS622_IR_FLAGS				0x16
#घोषणा IQS622_IR_FLAGS_TOUCH			BIT(1)
#घोषणा IQS622_IR_FLAGS_PROX			BIT(0)

#घोषणा IQS622_IR_UI_OUT			0x17

#घोषणा IQS622_IR_THRESH_PROX			0x91
#घोषणा IQS622_IR_THRESH_TOUCH			0x92

काष्ठा iqs621_als_निजी अणु
	काष्ठा iqs62x_core *iqs62x;
	काष्ठा iio_dev *indio_dev;
	काष्ठा notअगरier_block notअगरier;
	काष्ठा mutex lock;
	bool light_en;
	bool range_en;
	bool prox_en;
	u8 als_flags;
	u8 ir_flags_mask;
	u8 ir_flags;
	u8 thresh_light;
	u8 thresh_dark;
	u8 thresh_prox;
पूर्ण;

अटल पूर्णांक iqs621_als_init(काष्ठा iqs621_als_निजी *iqs621_als)
अणु
	काष्ठा iqs62x_core *iqs62x = iqs621_als->iqs62x;
	अचिन्हित पूर्णांक event_mask = 0;
	पूर्णांक ret;

	चयन (iqs621_als->ir_flags_mask) अणु
	हाल IQS622_IR_FLAGS_TOUCH:
		ret = regmap_ग_लिखो(iqs62x->regmap, IQS622_IR_THRESH_TOUCH,
				   iqs621_als->thresh_prox);
		अवरोध;

	हाल IQS622_IR_FLAGS_PROX:
		ret = regmap_ग_लिखो(iqs62x->regmap, IQS622_IR_THRESH_PROX,
				   iqs621_als->thresh_prox);
		अवरोध;

	शेष:
		ret = regmap_ग_लिखो(iqs62x->regmap, IQS621_ALS_THRESH_LIGHT,
				   iqs621_als->thresh_light);
		अगर (ret)
			वापस ret;

		ret = regmap_ग_लिखो(iqs62x->regmap, IQS621_ALS_THRESH_DARK,
				   iqs621_als->thresh_dark);
	पूर्ण

	अगर (ret)
		वापस ret;

	अगर (iqs621_als->light_en || iqs621_als->range_en)
		event_mask |= iqs62x->dev_desc->als_mask;

	अगर (iqs621_als->prox_en)
		event_mask |= iqs62x->dev_desc->ir_mask;

	वापस regmap_update_bits(iqs62x->regmap, IQS620_GLBL_EVENT_MASK,
				  event_mask, 0);
पूर्ण

अटल पूर्णांक iqs621_als_notअगरier(काष्ठा notअगरier_block *notअगरier,
			       अचिन्हित दीर्घ event_flags, व्योम *context)
अणु
	काष्ठा iqs62x_event_data *event_data = context;
	काष्ठा iqs621_als_निजी *iqs621_als;
	काष्ठा iio_dev *indio_dev;
	bool light_new, light_old;
	bool prox_new, prox_old;
	u8 range_new, range_old;
	s64 बारtamp;
	पूर्णांक ret;

	iqs621_als = container_of(notअगरier, काष्ठा iqs621_als_निजी,
				  notअगरier);
	indio_dev = iqs621_als->indio_dev;
	बारtamp = iio_get_समय_ns(indio_dev);

	mutex_lock(&iqs621_als->lock);

	अगर (event_flags & BIT(IQS62X_EVENT_SYS_RESET)) अणु
		ret = iqs621_als_init(iqs621_als);
		अगर (ret) अणु
			dev_err(indio_dev->dev.parent,
				"Failed to re-initialize device: %d\n", ret);
			ret = NOTIFY_BAD;
		पूर्ण अन्यथा अणु
			ret = NOTIFY_OK;
		पूर्ण

		जाओ err_mutex;
	पूर्ण

	अगर (!iqs621_als->light_en && !iqs621_als->range_en &&
	    !iqs621_als->prox_en) अणु
		ret = NOTIFY_DONE;
		जाओ err_mutex;
	पूर्ण

	/* IQS621 only */
	light_new = event_data->als_flags & IQS621_ALS_FLAGS_LIGHT;
	light_old = iqs621_als->als_flags & IQS621_ALS_FLAGS_LIGHT;

	अगर (iqs621_als->light_en && light_new && !light_old)
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_LIGHT, 0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_RISING),
			       बारtamp);
	अन्यथा अगर (iqs621_als->light_en && !light_new && light_old)
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_LIGHT, 0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_FALLING),
			       बारtamp);

	/* IQS621 and IQS622 */
	range_new = event_data->als_flags & IQS621_ALS_FLAGS_RANGE;
	range_old = iqs621_als->als_flags & IQS621_ALS_FLAGS_RANGE;

	अगर (iqs621_als->range_en && (range_new > range_old))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_INTENSITY, 0,
						    IIO_EV_TYPE_CHANGE,
						    IIO_EV_सूची_RISING),
			       बारtamp);
	अन्यथा अगर (iqs621_als->range_en && (range_new < range_old))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_INTENSITY, 0,
						    IIO_EV_TYPE_CHANGE,
						    IIO_EV_सूची_FALLING),
			       बारtamp);

	/* IQS622 only */
	prox_new = event_data->ir_flags & iqs621_als->ir_flags_mask;
	prox_old = iqs621_als->ir_flags & iqs621_als->ir_flags_mask;

	अगर (iqs621_als->prox_en && prox_new && !prox_old)
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, 0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_RISING),
			       बारtamp);
	अन्यथा अगर (iqs621_als->prox_en && !prox_new && prox_old)
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, 0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_FALLING),
			       बारtamp);

	iqs621_als->als_flags = event_data->als_flags;
	iqs621_als->ir_flags = event_data->ir_flags;
	ret = NOTIFY_OK;

err_mutex:
	mutex_unlock(&iqs621_als->lock);

	वापस ret;
पूर्ण

अटल व्योम iqs621_als_notअगरier_unरेजिस्टर(व्योम *context)
अणु
	काष्ठा iqs621_als_निजी *iqs621_als = context;
	काष्ठा iio_dev *indio_dev = iqs621_als->indio_dev;
	पूर्णांक ret;

	ret = blocking_notअगरier_chain_unरेजिस्टर(&iqs621_als->iqs62x->nh,
						 &iqs621_als->notअगरier);
	अगर (ret)
		dev_err(indio_dev->dev.parent,
			"Failed to unregister notifier: %d\n", ret);
पूर्ण

अटल पूर्णांक iqs621_als_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा iqs621_als_निजी *iqs621_als = iio_priv(indio_dev);
	काष्ठा iqs62x_core *iqs62x = iqs621_als->iqs62x;
	पूर्णांक ret;
	__le16 val_buf;

	चयन (chan->type) अणु
	हाल IIO_INTENSITY:
		ret = regmap_पढ़ो(iqs62x->regmap, chan->address, val);
		अगर (ret)
			वापस ret;

		*val &= IQS621_ALS_FLAGS_RANGE;
		वापस IIO_VAL_INT;

	हाल IIO_PROXIMITY:
	हाल IIO_LIGHT:
		ret = regmap_raw_पढ़ो(iqs62x->regmap, chan->address, &val_buf,
				      माप(val_buf));
		अगर (ret)
			वापस ret;

		*val = le16_to_cpu(val_buf);
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक iqs621_als_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan,
					क्रमागत iio_event_type type,
					क्रमागत iio_event_direction dir)
अणु
	काष्ठा iqs621_als_निजी *iqs621_als = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&iqs621_als->lock);

	चयन (chan->type) अणु
	हाल IIO_LIGHT:
		ret = iqs621_als->light_en;
		अवरोध;

	हाल IIO_INTENSITY:
		ret = iqs621_als->range_en;
		अवरोध;

	हाल IIO_PROXIMITY:
		ret = iqs621_als->prox_en;
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&iqs621_als->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक iqs621_als_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
					 स्थिर काष्ठा iio_chan_spec *chan,
					 क्रमागत iio_event_type type,
					 क्रमागत iio_event_direction dir,
					 पूर्णांक state)
अणु
	काष्ठा iqs621_als_निजी *iqs621_als = iio_priv(indio_dev);
	काष्ठा iqs62x_core *iqs62x = iqs621_als->iqs62x;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	mutex_lock(&iqs621_als->lock);

	ret = regmap_पढ़ो(iqs62x->regmap, iqs62x->dev_desc->als_flags, &val);
	अगर (ret)
		जाओ err_mutex;
	iqs621_als->als_flags = val;

	चयन (chan->type) अणु
	हाल IIO_LIGHT:
		ret = regmap_update_bits(iqs62x->regmap, IQS620_GLBL_EVENT_MASK,
					 iqs62x->dev_desc->als_mask,
					 iqs621_als->range_en || state ? 0 :
									 0xFF);
		अगर (!ret)
			iqs621_als->light_en = state;
		अवरोध;

	हाल IIO_INTENSITY:
		ret = regmap_update_bits(iqs62x->regmap, IQS620_GLBL_EVENT_MASK,
					 iqs62x->dev_desc->als_mask,
					 iqs621_als->light_en || state ? 0 :
									 0xFF);
		अगर (!ret)
			iqs621_als->range_en = state;
		अवरोध;

	हाल IIO_PROXIMITY:
		ret = regmap_पढ़ो(iqs62x->regmap, IQS622_IR_FLAGS, &val);
		अगर (ret)
			जाओ err_mutex;
		iqs621_als->ir_flags = val;

		ret = regmap_update_bits(iqs62x->regmap, IQS620_GLBL_EVENT_MASK,
					 iqs62x->dev_desc->ir_mask,
					 state ? 0 : 0xFF);
		अगर (!ret)
			iqs621_als->prox_en = state;
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

err_mutex:
	mutex_unlock(&iqs621_als->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक iqs621_als_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
				       स्थिर काष्ठा iio_chan_spec *chan,
				       क्रमागत iio_event_type type,
				       क्रमागत iio_event_direction dir,
				       क्रमागत iio_event_info info,
				       पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा iqs621_als_निजी *iqs621_als = iio_priv(indio_dev);
	पूर्णांक ret = IIO_VAL_INT;

	mutex_lock(&iqs621_als->lock);

	चयन (dir) अणु
	हाल IIO_EV_सूची_RISING:
		*val = iqs621_als->thresh_light * 16;
		अवरोध;

	हाल IIO_EV_सूची_FALLING:
		*val = iqs621_als->thresh_dark * 4;
		अवरोध;

	हाल IIO_EV_सूची_EITHER:
		अगर (iqs621_als->ir_flags_mask == IQS622_IR_FLAGS_TOUCH)
			*val = iqs621_als->thresh_prox * 4;
		अन्यथा
			*val = iqs621_als->thresh_prox;
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&iqs621_als->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक iqs621_als_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan,
					क्रमागत iio_event_type type,
					क्रमागत iio_event_direction dir,
					क्रमागत iio_event_info info,
					पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा iqs621_als_निजी *iqs621_als = iio_priv(indio_dev);
	काष्ठा iqs62x_core *iqs62x = iqs621_als->iqs62x;
	अचिन्हित पूर्णांक thresh_reg, thresh_val;
	u8 ir_flags_mask, *thresh_cache;
	पूर्णांक ret = -EINVAL;

	mutex_lock(&iqs621_als->lock);

	चयन (dir) अणु
	हाल IIO_EV_सूची_RISING:
		thresh_reg = IQS621_ALS_THRESH_LIGHT;
		thresh_val = val / 16;

		thresh_cache = &iqs621_als->thresh_light;
		ir_flags_mask = 0;
		अवरोध;

	हाल IIO_EV_सूची_FALLING:
		thresh_reg = IQS621_ALS_THRESH_DARK;
		thresh_val = val / 4;

		thresh_cache = &iqs621_als->thresh_dark;
		ir_flags_mask = 0;
		अवरोध;

	हाल IIO_EV_सूची_EITHER:
		/*
		 * The IQS622 supports two detection thresholds, both measured
		 * in the same arbitrary units reported by पढ़ो_raw: proximity
		 * (0 through 255 in steps of 1), and touch (0 through 1020 in
		 * steps of 4).
		 *
		 * Based on the single detection threshold chosen by the user,
		 * select the hardware threshold that gives the best trade-off
		 * between range and resolution.
		 *
		 * By शेष, the बंद-range (but coarse) touch threshold is
		 * chosen during probe.
		 */
		चयन (val) अणु
		हाल 0 ... 255:
			thresh_reg = IQS622_IR_THRESH_PROX;
			thresh_val = val;

			ir_flags_mask = IQS622_IR_FLAGS_PROX;
			अवरोध;

		हाल 256 ... 1020:
			thresh_reg = IQS622_IR_THRESH_TOUCH;
			thresh_val = val / 4;

			ir_flags_mask = IQS622_IR_FLAGS_TOUCH;
			अवरोध;

		शेष:
			जाओ err_mutex;
		पूर्ण

		thresh_cache = &iqs621_als->thresh_prox;
		अवरोध;

	शेष:
		जाओ err_mutex;
	पूर्ण

	अगर (thresh_val > 0xFF)
		जाओ err_mutex;

	ret = regmap_ग_लिखो(iqs62x->regmap, thresh_reg, thresh_val);
	अगर (ret)
		जाओ err_mutex;

	*thresh_cache = thresh_val;
	iqs621_als->ir_flags_mask = ir_flags_mask;

err_mutex:
	mutex_unlock(&iqs621_als->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info iqs621_als_info = अणु
	.पढ़ो_raw = &iqs621_als_पढ़ो_raw,
	.पढ़ो_event_config = iqs621_als_पढ़ो_event_config,
	.ग_लिखो_event_config = iqs621_als_ग_लिखो_event_config,
	.पढ़ो_event_value = iqs621_als_पढ़ो_event_value,
	.ग_लिखो_event_value = iqs621_als_ग_लिखो_event_value,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec iqs621_als_range_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_CHANGE,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec iqs621_als_light_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण,
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec iqs621_als_channels[] = अणु
	अणु
		.type = IIO_INTENSITY,
		.address = IQS621_ALS_FLAGS,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.event_spec = iqs621_als_range_events,
		.num_event_specs = ARRAY_SIZE(iqs621_als_range_events),
	पूर्ण,
	अणु
		.type = IIO_LIGHT,
		.address = IQS621_ALS_UI_OUT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.event_spec = iqs621_als_light_events,
		.num_event_specs = ARRAY_SIZE(iqs621_als_light_events),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec iqs622_als_prox_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE) |
				 BIT(IIO_EV_INFO_VALUE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec iqs622_als_channels[] = अणु
	अणु
		.type = IIO_INTENSITY,
		.channel2 = IIO_MOD_LIGHT_BOTH,
		.address = IQS622_ALS_FLAGS,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.event_spec = iqs621_als_range_events,
		.num_event_specs = ARRAY_SIZE(iqs621_als_range_events),
		.modअगरied = true,
	पूर्ण,
	अणु
		.type = IIO_INTENSITY,
		.channel2 = IIO_MOD_LIGHT_IR,
		.address = IQS622_IR_RANGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.modअगरied = true,
	पूर्ण,
	अणु
		.type = IIO_PROXIMITY,
		.address = IQS622_IR_UI_OUT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.event_spec = iqs622_als_prox_events,
		.num_event_specs = ARRAY_SIZE(iqs622_als_prox_events),
	पूर्ण,
पूर्ण;

अटल पूर्णांक iqs621_als_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iqs62x_core *iqs62x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा iqs621_als_निजी *iqs621_als;
	काष्ठा iio_dev *indio_dev;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*iqs621_als));
	अगर (!indio_dev)
		वापस -ENOMEM;

	iqs621_als = iio_priv(indio_dev);
	iqs621_als->iqs62x = iqs62x;
	iqs621_als->indio_dev = indio_dev;

	अगर (iqs62x->dev_desc->prod_num == IQS622_PROD_NUM) अणु
		ret = regmap_पढ़ो(iqs62x->regmap, IQS622_IR_THRESH_TOUCH,
				  &val);
		अगर (ret)
			वापस ret;
		iqs621_als->thresh_prox = val;
		iqs621_als->ir_flags_mask = IQS622_IR_FLAGS_TOUCH;

		indio_dev->channels = iqs622_als_channels;
		indio_dev->num_channels = ARRAY_SIZE(iqs622_als_channels);
	पूर्ण अन्यथा अणु
		ret = regmap_पढ़ो(iqs62x->regmap, IQS621_ALS_THRESH_LIGHT,
				  &val);
		अगर (ret)
			वापस ret;
		iqs621_als->thresh_light = val;

		ret = regmap_पढ़ो(iqs62x->regmap, IQS621_ALS_THRESH_DARK,
				  &val);
		अगर (ret)
			वापस ret;
		iqs621_als->thresh_dark = val;

		indio_dev->channels = iqs621_als_channels;
		indio_dev->num_channels = ARRAY_SIZE(iqs621_als_channels);
	पूर्ण

	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->name = iqs62x->dev_desc->dev_name;
	indio_dev->info = &iqs621_als_info;

	mutex_init(&iqs621_als->lock);

	iqs621_als->notअगरier.notअगरier_call = iqs621_als_notअगरier;
	ret = blocking_notअगरier_chain_रेजिस्टर(&iqs621_als->iqs62x->nh,
					       &iqs621_als->notअगरier);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register notifier: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&pdev->dev,
				       iqs621_als_notअगरier_unरेजिस्टर,
				       iqs621_als);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&pdev->dev, indio_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver iqs621_als_platक्रमm_driver = अणु
	.driver = अणु
		.name = "iqs621-als",
	पूर्ण,
	.probe = iqs621_als_probe,
पूर्ण;
module_platक्रमm_driver(iqs621_als_platक्रमm_driver);

MODULE_AUTHOR("Jeff LaBundy <jeff@labundy.com>");
MODULE_DESCRIPTION("Azoteq IQS621/622 Ambient Light Sensors");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:iqs621-als");
