<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID Sensors Driver
 * Copyright (c) 2017, Intel Corporation.
 */
#समावेश <linux/device.h>
#समावेश <linux/hid-sensor-hub.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "../common/hid-sensors/hid-sensor-trigger.h"

काष्ठा temperature_state अणु
	काष्ठा hid_sensor_common common_attributes;
	काष्ठा hid_sensor_hub_attribute_info temperature_attr;
	काष्ठा अणु
		s32 temperature_data;
		u64 बारtamp __aligned(8);
	पूर्ण scan;
	पूर्णांक scale_pre_decml;
	पूर्णांक scale_post_decml;
	पूर्णांक scale_precision;
	पूर्णांक value_offset;
पूर्ण;

अटल स्थिर u32 temperature_sensitivity_addresses[] = अणु
	HID_USAGE_SENSOR_DATA_ENVIRONMENTAL_TEMPERATURE,
पूर्ण;

/* Channel definitions */
अटल स्थिर काष्ठा iio_chan_spec temperature_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_SAMP_FREQ) |
			BIT(IIO_CHAN_INFO_HYSTERESIS),
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

/* Adjust channel real bits based on report descriptor */
अटल व्योम temperature_adjust_channel_bit_mask(काष्ठा iio_chan_spec *channels,
					पूर्णांक channel, पूर्णांक size)
अणु
	channels[channel].scan_type.sign = 's';
	/* Real storage bits will change based on the report desc. */
	channels[channel].scan_type.realbits = size * 8;
	/* Maximum size of a sample to capture is s32 */
	channels[channel].scan_type.storagebits = माप(s32) * 8;
पूर्ण

अटल पूर्णांक temperature_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा temperature_state *temp_st = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->type != IIO_TEMP)
			वापस -EINVAL;
		hid_sensor_घातer_state(
			&temp_st->common_attributes, true);
		*val = sensor_hub_input_attr_get_raw_value(
			temp_st->common_attributes.hsdev,
			HID_USAGE_SENSOR_TEMPERATURE,
			HID_USAGE_SENSOR_DATA_ENVIRONMENTAL_TEMPERATURE,
			temp_st->temperature_attr.report_id,
			SENSOR_HUB_SYNC,
			temp_st->temperature_attr.logical_minimum < 0);
		hid_sensor_घातer_state(
				&temp_st->common_attributes,
				false);

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = temp_st->scale_pre_decml;
		*val2 = temp_st->scale_post_decml;
		वापस temp_st->scale_precision;

	हाल IIO_CHAN_INFO_OFFSET:
		*val = temp_st->value_offset;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस hid_sensor_पढ़ो_samp_freq_value(
				&temp_st->common_attributes, val, val2);

	हाल IIO_CHAN_INFO_HYSTERESIS:
		वापस hid_sensor_पढ़ो_raw_hyst_value(
				&temp_st->common_attributes, val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक temperature_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा temperature_state *temp_st = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस hid_sensor_ग_लिखो_samp_freq_value(
				&temp_st->common_attributes, val, val2);
	हाल IIO_CHAN_INFO_HYSTERESIS:
		वापस hid_sensor_ग_लिखो_raw_hyst_value(
				&temp_st->common_attributes, val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info temperature_info = अणु
	.पढ़ो_raw = &temperature_पढ़ो_raw,
	.ग_लिखो_raw = &temperature_ग_लिखो_raw,
पूर्ण;

/* Callback handler to send event after all samples are received and captured */
अटल पूर्णांक temperature_proc_event(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित पूर्णांक usage_id, व्योम *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा temperature_state *temp_st = iio_priv(indio_dev);

	अगर (atomic_पढ़ो(&temp_st->common_attributes.data_पढ़ोy))
		iio_push_to_buffers_with_बारtamp(indio_dev, &temp_st->scan,
						   iio_get_समय_ns(indio_dev));

	वापस 0;
पूर्ण

/* Capture samples in local storage */
अटल पूर्णांक temperature_capture_sample(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित पूर्णांक usage_id, माप_प्रकार raw_len,
				अक्षर *raw_data, व्योम *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा temperature_state *temp_st = iio_priv(indio_dev);

	चयन (usage_id) अणु
	हाल HID_USAGE_SENSOR_DATA_ENVIRONMENTAL_TEMPERATURE:
		temp_st->scan.temperature_data = *(s32 *)raw_data;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Parse report which is specअगरic to an usage id*/
अटल पूर्णांक temperature_parse_report(काष्ठा platक्रमm_device *pdev,
				काष्ठा hid_sensor_hub_device *hsdev,
				काष्ठा iio_chan_spec *channels,
				अचिन्हित पूर्णांक usage_id,
				काष्ठा temperature_state *st)
अणु
	पूर्णांक ret;

	ret = sensor_hub_input_get_attribute_info(hsdev, HID_INPUT_REPORT,
			usage_id,
			HID_USAGE_SENSOR_DATA_ENVIRONMENTAL_TEMPERATURE,
			&st->temperature_attr);
	अगर (ret < 0)
		वापस ret;

	temperature_adjust_channel_bit_mask(channels, 0,
					st->temperature_attr.size);

	st->scale_precision = hid_sensor_क्रमmat_scale(
				HID_USAGE_SENSOR_TEMPERATURE,
				&st->temperature_attr,
				&st->scale_pre_decml, &st->scale_post_decml);

	वापस ret;
पूर्ण

अटल काष्ठा hid_sensor_hub_callbacks temperature_callbacks = अणु
	.send_event = &temperature_proc_event,
	.capture_sample = &temperature_capture_sample,
पूर्ण;

/* Function to initialize the processing क्रम usage id */
अटल पूर्णांक hid_temperature_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अटल स्थिर अक्षर *name = "temperature";
	काष्ठा iio_dev *indio_dev;
	काष्ठा temperature_state *temp_st;
	काष्ठा iio_chan_spec *temp_chans;
	काष्ठा hid_sensor_hub_device *hsdev = dev_get_platdata(&pdev->dev);
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*temp_st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	temp_st = iio_priv(indio_dev);
	temp_st->common_attributes.hsdev = hsdev;
	temp_st->common_attributes.pdev = pdev;

	ret = hid_sensor_parse_common_attributes(hsdev,
					HID_USAGE_SENSOR_TEMPERATURE,
					&temp_st->common_attributes,
					temperature_sensitivity_addresses,
					ARRAY_SIZE(temperature_sensitivity_addresses));
	अगर (ret)
		वापस ret;

	temp_chans = devm_kmemdup(&indio_dev->dev, temperature_channels,
				माप(temperature_channels), GFP_KERNEL);
	अगर (!temp_chans)
		वापस -ENOMEM;

	ret = temperature_parse_report(pdev, hsdev, temp_chans,
				HID_USAGE_SENSOR_TEMPERATURE, temp_st);
	अगर (ret)
		वापस ret;

	indio_dev->channels = temp_chans;
	indio_dev->num_channels = ARRAY_SIZE(temperature_channels);
	indio_dev->info = &temperature_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	atomic_set(&temp_st->common_attributes.data_पढ़ोy, 0);

	ret = hid_sensor_setup_trigger(indio_dev, name,
				&temp_st->common_attributes);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, indio_dev);

	temperature_callbacks.pdev = pdev;
	ret = sensor_hub_रेजिस्टर_callback(hsdev, HID_USAGE_SENSOR_TEMPERATURE,
					&temperature_callbacks);
	अगर (ret)
		जाओ error_हटाओ_trigger;

	ret = devm_iio_device_रेजिस्टर(indio_dev->dev.parent, indio_dev);
	अगर (ret)
		जाओ error_हटाओ_callback;

	वापस ret;

error_हटाओ_callback:
	sensor_hub_हटाओ_callback(hsdev, HID_USAGE_SENSOR_TEMPERATURE);
error_हटाओ_trigger:
	hid_sensor_हटाओ_trigger(indio_dev, &temp_st->common_attributes);
	वापस ret;
पूर्ण

/* Function to deinitialize the processing क्रम usage id */
अटल पूर्णांक hid_temperature_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hid_sensor_hub_device *hsdev = dev_get_platdata(&pdev->dev);
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा temperature_state *temp_st = iio_priv(indio_dev);

	sensor_hub_हटाओ_callback(hsdev, HID_USAGE_SENSOR_TEMPERATURE);
	hid_sensor_हटाओ_trigger(indio_dev, &temp_st->common_attributes);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id hid_temperature_ids[] = अणु
	अणु
		/* Format: HID-SENSOR-usage_id_in_hex_lowerहाल */
		.name = "HID-SENSOR-200033",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, hid_temperature_ids);

अटल काष्ठा platक्रमm_driver hid_temperature_platक्रमm_driver = अणु
	.id_table = hid_temperature_ids,
	.driver = अणु
		.name	= "temperature-sensor",
		.pm	= &hid_sensor_pm_ops,
	पूर्ण,
	.probe		= hid_temperature_probe,
	.हटाओ		= hid_temperature_हटाओ,
पूर्ण;
module_platक्रमm_driver(hid_temperature_platक्रमm_driver);

MODULE_DESCRIPTION("HID Environmental temperature sensor");
MODULE_AUTHOR("Song Hongyan <hongyan.song@intel.com>");
MODULE_LICENSE("GPL v2");
