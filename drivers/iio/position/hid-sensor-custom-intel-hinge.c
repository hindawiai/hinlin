<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID Sensors Driver
 * Copyright (c) 2020, Intel Corporation.
 */
#समावेश <linux/hid-sensor-hub.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश "../common/hid-sensors/hid-sensor-trigger.h"

क्रमागत hinge_channel अणु
	CHANNEL_SCAN_INDEX_HINGE_ANGLE,
	CHANNEL_SCAN_INDEX_SCREEN_ANGLE,
	CHANNEL_SCAN_INDEX_KEYBOARD_ANGLE,
	CHANNEL_SCAN_INDEX_MAX,
पूर्ण;

#घोषणा CHANNEL_SCAN_INDEX_TIMESTAMP CHANNEL_SCAN_INDEX_MAX

अटल स्थिर u32 hinge_addresses[CHANNEL_SCAN_INDEX_MAX] = अणु
	HID_USAGE_SENSOR_DATA_FIELD_CUSTOM_VALUE(1),
	HID_USAGE_SENSOR_DATA_FIELD_CUSTOM_VALUE(2),
	HID_USAGE_SENSOR_DATA_FIELD_CUSTOM_VALUE(3)
पूर्ण;

अटल स्थिर अक्षर *स्थिर hinge_labels[CHANNEL_SCAN_INDEX_MAX] = अणु "hinge",
								  "screen",
								  "keyboard" पूर्ण;

काष्ठा hinge_state अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा hid_sensor_hub_attribute_info hinge[CHANNEL_SCAN_INDEX_MAX];
	काष्ठा hid_sensor_hub_callbacks callbacks;
	काष्ठा hid_sensor_common common_attributes;
	स्थिर अक्षर *labels[CHANNEL_SCAN_INDEX_MAX];
	काष्ठा अणु
		u32 hinge_val[3];
		u64 बारtamp __aligned(8);
	पूर्ण scan;

	पूर्णांक scale_pre_decml;
	पूर्णांक scale_post_decml;
	पूर्णांक scale_precision;
	पूर्णांक value_offset;
	u64 बारtamp;
पूर्ण;

अटल स्थिर u32 hinge_sensitivity_addresses[] = अणु
	HID_USAGE_SENSOR_DATA_FIELD_CUSTOM_VALUE(1),
पूर्ण;

/* Channel definitions */
अटल स्थिर काष्ठा iio_chan_spec hinge_channels[] = अणु
	अणु
		.type = IIO_ANGL,
		.indexed = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_SAMP_FREQ) | BIT(IIO_CHAN_INFO_HYSTERESIS),
		.scan_index = CHANNEL_SCAN_INDEX_HINGE_ANGLE,
		.scan_type = अणु
			.sign = 's',
			.storagebits = 32,
		पूर्ण,
	पूर्ण, अणु
		.type = IIO_ANGL,
		.indexed = 1,
		.channel = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_SAMP_FREQ) | BIT(IIO_CHAN_INFO_HYSTERESIS),
		.scan_index = CHANNEL_SCAN_INDEX_SCREEN_ANGLE,
		.scan_type = अणु
			.sign = 's',
			.storagebits = 32,
		पूर्ण,
	पूर्ण, अणु
		.type = IIO_ANGL,
		.indexed = 1,
		.channel = 2,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_SAMP_FREQ) | BIT(IIO_CHAN_INFO_HYSTERESIS),
		.scan_index = CHANNEL_SCAN_INDEX_KEYBOARD_ANGLE,
		.scan_type = अणु
			.sign = 's',
			.storagebits = 32,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(CHANNEL_SCAN_INDEX_TIMESTAMP)
पूर्ण;

/* Adjust channel real bits based on report descriptor */
अटल व्योम hinge_adjust_channel_realbits(काष्ठा iio_chan_spec *channels,
					  पूर्णांक channel, पूर्णांक size)
अणु
	channels[channel].scan_type.realbits = size * 8;
पूर्ण

/* Channel पढ़ो_raw handler */
अटल पूर्णांक hinge_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2,
			  दीर्घ mask)
अणु
	काष्ठा hinge_state *st = iio_priv(indio_dev);
	काष्ठा hid_sensor_hub_device *hsdev;
	पूर्णांक report_id;
	s32 min;

	hsdev = st->common_attributes.hsdev;
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		hid_sensor_घातer_state(&st->common_attributes, true);
		report_id = st->hinge[chan->scan_index].report_id;
		min = st->hinge[chan->scan_index].logical_minimum;
		अगर (report_id < 0) अणु
			hid_sensor_घातer_state(&st->common_attributes, false);
			वापस -EINVAL;
		पूर्ण

		*val = sensor_hub_input_attr_get_raw_value(st->common_attributes.hsdev,
							   hsdev->usage,
							   hinge_addresses[chan->scan_index],
							   report_id,
							   SENSOR_HUB_SYNC, min < 0);

		hid_sensor_घातer_state(&st->common_attributes, false);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = st->scale_pre_decml;
		*val2 = st->scale_post_decml;
		वापस st->scale_precision;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = st->value_offset;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस hid_sensor_पढ़ो_samp_freq_value(&st->common_attributes,
						       val, val2);
	हाल IIO_CHAN_INFO_HYSTERESIS:
		वापस hid_sensor_पढ़ो_raw_hyst_value(&st->common_attributes,
						      val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Channel ग_लिखो_raw handler */
अटल पूर्णांक hinge_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2,
			   दीर्घ mask)
अणु
	काष्ठा hinge_state *st = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस hid_sensor_ग_लिखो_samp_freq_value(&st->common_attributes,
							val, val2);
	हाल IIO_CHAN_INFO_HYSTERESIS:
		वापस hid_sensor_ग_लिखो_raw_hyst_value(&st->common_attributes,
						       val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक hinge_पढ़ो_label(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, अक्षर *label)
अणु
	काष्ठा hinge_state *st = iio_priv(indio_dev);

	वापस प्र_लिखो(label, "%s\n", st->labels[chan->channel]);
पूर्ण

अटल स्थिर काष्ठा iio_info hinge_info = अणु
	.पढ़ो_raw = hinge_पढ़ो_raw,
	.ग_लिखो_raw = hinge_ग_लिखो_raw,
	.पढ़ो_label = hinge_पढ़ो_label,
पूर्ण;

/*
 * Callback handler to send event after all samples are received
 * and captured.
 */
अटल पूर्णांक hinge_proc_event(काष्ठा hid_sensor_hub_device *hsdev,
			    अचिन्हित पूर्णांक usage_id, व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(priv);
	काष्ठा hinge_state *st = iio_priv(indio_dev);

	अगर (atomic_पढ़ो(&st->common_attributes.data_पढ़ोy)) अणु
		अगर (!st->बारtamp)
			st->बारtamp = iio_get_समय_ns(indio_dev);

		iio_push_to_buffers_with_बारtamp(indio_dev, &st->scan,
						   st->बारtamp);

		st->बारtamp = 0;
	पूर्ण
	वापस 0;
पूर्ण

/* Capture samples in local storage */
अटल पूर्णांक hinge_capture_sample(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित पूर्णांक usage_id, माप_प्रकार raw_len,
				अक्षर *raw_data, व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(priv);
	काष्ठा hinge_state *st = iio_priv(indio_dev);
	पूर्णांक offset;

	चयन (usage_id) अणु
	हाल HID_USAGE_SENSOR_DATA_FIELD_CUSTOM_VALUE(1):
	हाल HID_USAGE_SENSOR_DATA_FIELD_CUSTOM_VALUE(2):
	हाल HID_USAGE_SENSOR_DATA_FIELD_CUSTOM_VALUE(3):
		offset = usage_id - HID_USAGE_SENSOR_DATA_FIELD_CUSTOM_VALUE(1);
		st->scan.hinge_val[offset] = *(u32 *)raw_data;
		वापस 0;
	हाल HID_USAGE_SENSOR_TIME_TIMESTAMP:
		st->बारtamp = hid_sensor_convert_बारtamp(&st->common_attributes,
							     *(पूर्णांक64_t *)raw_data);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Parse report which is specअगरic to an usage id */
अटल पूर्णांक hinge_parse_report(काष्ठा platक्रमm_device *pdev,
			      काष्ठा hid_sensor_hub_device *hsdev,
			      काष्ठा iio_chan_spec *channels,
			      अचिन्हित पूर्णांक usage_id, काष्ठा hinge_state *st)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < CHANNEL_SCAN_INDEX_MAX; ++i) अणु
		ret = sensor_hub_input_get_attribute_info(hsdev,
							  HID_INPUT_REPORT,
							  usage_id,
							  hinge_addresses[i],
							  &st->hinge[i]);
		अगर (ret < 0)
			वापस ret;

		hinge_adjust_channel_realbits(channels, i, st->hinge[i].size);
	पूर्ण

	st->scale_precision = hid_sensor_क्रमmat_scale(HID_USAGE_SENSOR_HINGE,
			&st->hinge[CHANNEL_SCAN_INDEX_HINGE_ANGLE],
			&st->scale_pre_decml, &st->scale_post_decml);

	वापस ret;
पूर्ण

/* Function to initialize the processing क्रम usage id */
अटल पूर्णांक hid_hinge_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hinge_state *st;
	काष्ठा iio_dev *indio_dev;
	काष्ठा hid_sensor_hub_device *hsdev = pdev->dev.platक्रमm_data;
	पूर्णांक ret;
	पूर्णांक i;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, indio_dev);

	st = iio_priv(indio_dev);
	st->common_attributes.hsdev = hsdev;
	st->common_attributes.pdev = pdev;
	st->indio_dev = indio_dev;
	क्रम (i = 0; i < CHANNEL_SCAN_INDEX_MAX; i++)
		st->labels[i] = hinge_labels[i];

	ret = hid_sensor_parse_common_attributes(hsdev, hsdev->usage,
						 &st->common_attributes,
						 hinge_sensitivity_addresses,
						 ARRAY_SIZE(hinge_sensitivity_addresses));
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup common attributes\n");
		वापस ret;
	पूर्ण

	indio_dev->num_channels = ARRAY_SIZE(hinge_channels);
	indio_dev->channels = devm_kmemdup(&indio_dev->dev, hinge_channels,
					   माप(hinge_channels), GFP_KERNEL);
	अगर (!indio_dev->channels)
		वापस -ENOMEM;

	ret = hinge_parse_report(pdev, hsdev,
				 (काष्ठा iio_chan_spec *)indio_dev->channels,
				 hsdev->usage, st);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup attributes\n");
		वापस ret;
	पूर्ण

	indio_dev->dev.parent = &pdev->dev;
	indio_dev->info = &hinge_info;
	indio_dev->name = "hinge";
	indio_dev->modes = INDIO_सूचीECT_MODE;

	atomic_set(&st->common_attributes.data_पढ़ोy, 0);
	ret = hid_sensor_setup_trigger(indio_dev, indio_dev->name,
				       &st->common_attributes);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "trigger setup failed\n");
		वापस ret;
	पूर्ण

	st->callbacks.send_event = hinge_proc_event;
	st->callbacks.capture_sample = hinge_capture_sample;
	st->callbacks.pdev = pdev;
	ret = sensor_hub_रेजिस्टर_callback(hsdev, hsdev->usage, &st->callbacks);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "callback reg failed\n");
		जाओ error_हटाओ_trigger;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "device register failed\n");
		जाओ error_हटाओ_callback;
	पूर्ण

	वापस ret;

error_हटाओ_callback:
	sensor_hub_हटाओ_callback(hsdev, hsdev->usage);
error_हटाओ_trigger:
	hid_sensor_हटाओ_trigger(indio_dev, &st->common_attributes);
	वापस ret;
पूर्ण

/* Function to deinitialize the processing क्रम usage id */
अटल पूर्णांक hid_hinge_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hid_sensor_hub_device *hsdev = pdev->dev.platक्रमm_data;
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा hinge_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	sensor_hub_हटाओ_callback(hsdev, hsdev->usage);
	hid_sensor_हटाओ_trigger(indio_dev, &st->common_attributes);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id hid_hinge_ids[] = अणु
	अणु
		/* Format: HID-SENSOR-INT-usage_id_in_hex_lowerहाल */
		.name = "HID-SENSOR-INT-020b",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, hid_hinge_ids);

अटल काष्ठा platक्रमm_driver hid_hinge_platक्रमm_driver = अणु
	.id_table = hid_hinge_ids,
	.driver = अणु
		.name	= KBUILD_MODNAME,
		.pm	= &hid_sensor_pm_ops,
	पूर्ण,
	.probe		= hid_hinge_probe,
	.हटाओ		= hid_hinge_हटाओ,
पूर्ण;
module_platक्रमm_driver(hid_hinge_platक्रमm_driver);

MODULE_DESCRIPTION("HID Sensor INTEL Hinge");
MODULE_AUTHOR("Ye Xiang <xiang.ye@intel.com>");
MODULE_LICENSE("GPL");
