<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम cros-ec proximity sensor exposed through MKBP चयन
 *
 * Copyright 2021 Google LLC.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>

#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश <यंत्र/unaligned.h>

काष्ठा cros_ec_mkbp_proximity_data अणु
	काष्ठा cros_ec_device *ec;
	काष्ठा iio_dev *indio_dev;
	काष्ठा mutex lock;
	काष्ठा notअगरier_block notअगरier;
	पूर्णांक last_proximity;
	bool enabled;
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec cros_ec_mkbp_proximity_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec cros_ec_mkbp_proximity_chan_spec[] = अणु
	अणु
		.type = IIO_PROXIMITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.event_spec = cros_ec_mkbp_proximity_events,
		.num_event_specs = ARRAY_SIZE(cros_ec_mkbp_proximity_events),
	पूर्ण,
पूर्ण;

अटल पूर्णांक cros_ec_mkbp_proximity_parse_state(स्थिर व्योम *data)
अणु
	u32 चयनes = get_unaligned_le32(data);

	वापस !!(चयनes & BIT(EC_MKBP_FRONT_PROXIMITY));
पूर्ण

अटल पूर्णांक cros_ec_mkbp_proximity_query(काष्ठा cros_ec_device *ec_dev,
					पूर्णांक *state)
अणु
	काष्ठा अणु
		काष्ठा cros_ec_command msg;
		जोड़ अणु
			काष्ठा ec_params_mkbp_info params;
			u32 चयनes;
		पूर्ण;
	पूर्ण __packed buf = अणु पूर्ण;
	काष्ठा ec_params_mkbp_info *params = &buf.params;
	काष्ठा cros_ec_command *msg = &buf.msg;
	u32 *चयनes = &buf.चयनes;
	माप_प्रकार insize = माप(*चयनes);
	पूर्णांक ret;

	msg->command = EC_CMD_MKBP_INFO;
	msg->version = 1;
	msg->outsize = माप(*params);
	msg->insize = insize;

	params->info_type = EC_MKBP_INFO_CURRENT;
	params->event_type = EC_MKBP_EVENT_SWITCH;

	ret = cros_ec_cmd_xfer_status(ec_dev, msg);
	अगर (ret < 0)
		वापस ret;

	अगर (ret != insize) अणु
		dev_warn(ec_dev->dev, "wrong result size: %d != %zu\n", ret,
			 insize);
		वापस -EPROTO;
	पूर्ण

	*state = cros_ec_mkbp_proximity_parse_state(चयनes);
	वापस IIO_VAL_INT;
पूर्ण

अटल व्योम cros_ec_mkbp_proximity_push_event(काष्ठा cros_ec_mkbp_proximity_data *data, पूर्णांक state)
अणु
	s64 बारtamp;
	u64 ev;
	पूर्णांक dir;
	काष्ठा iio_dev *indio_dev = data->indio_dev;
	काष्ठा cros_ec_device *ec = data->ec;

	mutex_lock(&data->lock);
	अगर (state != data->last_proximity) अणु
		अगर (data->enabled) अणु
			बारtamp = kसमय_प्रकारo_ns(ec->last_event_समय);
			अगर (iio_device_get_घड़ी(indio_dev) != CLOCK_BOOTTIME)
				बारtamp = iio_get_समय_ns(indio_dev);

			dir = state ? IIO_EV_सूची_FALLING : IIO_EV_सूची_RISING;
			ev = IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, 0,
						  IIO_EV_TYPE_THRESH, dir);
			iio_push_event(indio_dev, ev, बारtamp);
		पूर्ण
		data->last_proximity = state;
	पूर्ण
	mutex_unlock(&data->lock);
पूर्ण

अटल पूर्णांक cros_ec_mkbp_proximity_notअगरy(काष्ठा notअगरier_block *nb,
					 अचिन्हित दीर्घ queued_during_suspend,
					 व्योम *_ec)
अणु
	काष्ठा cros_ec_mkbp_proximity_data *data;
	काष्ठा cros_ec_device *ec = _ec;
	u8 event_type = ec->event_data.event_type & EC_MKBP_EVENT_TYPE_MASK;
	व्योम *चयनes;
	पूर्णांक state;

	अगर (event_type == EC_MKBP_EVENT_SWITCH) अणु
		data = container_of(nb, काष्ठा cros_ec_mkbp_proximity_data,
				    notअगरier);

		चयनes = &ec->event_data.data.चयनes;
		state = cros_ec_mkbp_proximity_parse_state(चयनes);
		cros_ec_mkbp_proximity_push_event(data, state);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक cros_ec_mkbp_proximity_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *val,
			   पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा cros_ec_mkbp_proximity_data *data = iio_priv(indio_dev);
	काष्ठा cros_ec_device *ec = data->ec;

	अगर (chan->type == IIO_PROXIMITY && mask == IIO_CHAN_INFO_RAW)
		वापस cros_ec_mkbp_proximity_query(ec, val);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cros_ec_mkbp_proximity_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir)
अणु
	काष्ठा cros_ec_mkbp_proximity_data *data = iio_priv(indio_dev);

	वापस data->enabled;
पूर्ण

अटल पूर्णांक cros_ec_mkbp_proximity_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा cros_ec_mkbp_proximity_data *data = iio_priv(indio_dev);

	mutex_lock(&data->lock);
	data->enabled = state;
	mutex_unlock(&data->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info cros_ec_mkbp_proximity_info = अणु
	.पढ़ो_raw = cros_ec_mkbp_proximity_पढ़ो_raw,
	.पढ़ो_event_config = cros_ec_mkbp_proximity_पढ़ो_event_config,
	.ग_लिखो_event_config = cros_ec_mkbp_proximity_ग_लिखो_event_config,
पूर्ण;

अटल __maybe_unused पूर्णांक cros_ec_mkbp_proximity_resume(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_mkbp_proximity_data *data = dev_get_drvdata(dev);
	काष्ठा cros_ec_device *ec = data->ec;
	पूर्णांक ret, state;

	ret = cros_ec_mkbp_proximity_query(ec, &state);
	अगर (ret < 0) अणु
		dev_warn(dev, "failed to fetch proximity state on resume: %d\n",
			 ret);
	पूर्ण अन्यथा अणु
		cros_ec_mkbp_proximity_push_event(data, state);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cros_ec_mkbp_proximity_pm_ops, शून्य,
			 cros_ec_mkbp_proximity_resume);

अटल पूर्णांक cros_ec_mkbp_proximity_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cros_ec_device *ec = dev_get_drvdata(dev->parent);
	काष्ठा iio_dev *indio_dev;
	काष्ठा cros_ec_mkbp_proximity_data *data;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->ec = ec;
	data->indio_dev = indio_dev;
	data->last_proximity = -1; /* Unknown to start */
	mutex_init(&data->lock);
	platक्रमm_set_drvdata(pdev, data);

	indio_dev->name = dev->driver->name;
	indio_dev->info = &cros_ec_mkbp_proximity_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = cros_ec_mkbp_proximity_chan_spec;
	indio_dev->num_channels = ARRAY_SIZE(cros_ec_mkbp_proximity_chan_spec);

	ret = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (ret)
		वापस ret;

	data->notअगरier.notअगरier_call = cros_ec_mkbp_proximity_notअगरy;
	blocking_notअगरier_chain_रेजिस्टर(&ec->event_notअगरier, &data->notअगरier);

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_mkbp_proximity_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_mkbp_proximity_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा cros_ec_device *ec = data->ec;

	blocking_notअगरier_chain_unरेजिस्टर(&ec->event_notअगरier,
					   &data->notअगरier);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cros_ec_mkbp_proximity_of_match[] = अणु
	अणु .compatible = "google,cros-ec-mkbp-proximity" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cros_ec_mkbp_proximity_of_match);

अटल काष्ठा platक्रमm_driver cros_ec_mkbp_proximity_driver = अणु
	.driver = अणु
		.name = "cros-ec-mkbp-proximity",
		.of_match_table = cros_ec_mkbp_proximity_of_match,
		.pm = &cros_ec_mkbp_proximity_pm_ops,
	पूर्ण,
	.probe = cros_ec_mkbp_proximity_probe,
	.हटाओ = cros_ec_mkbp_proximity_हटाओ,
पूर्ण;
module_platक्रमm_driver(cros_ec_mkbp_proximity_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ChromeOS EC MKBP proximity sensor driver");
