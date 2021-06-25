<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID Sensors Driver
 * Copyright (c) 2014, Intel Corporation.
 */
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/hid-sensor-hub.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश "../common/hid-sensors/hid-sensor-trigger.h"

#घोषणा CHANNEL_SCAN_INDEX_PRESSURE 0

काष्ठा press_state अणु
	काष्ठा hid_sensor_hub_callbacks callbacks;
	काष्ठा hid_sensor_common common_attributes;
	काष्ठा hid_sensor_hub_attribute_info press_attr;
	u32 press_data;
	पूर्णांक scale_pre_decml;
	पूर्णांक scale_post_decml;
	पूर्णांक scale_precision;
	पूर्णांक value_offset;
पूर्ण;

अटल स्थिर u32 press_sensitivity_addresses[] = अणु
	HID_USAGE_SENSOR_DATA_ATMOSPHERIC_PRESSURE,
	HID_USAGE_SENSOR_ATMOSPHERIC_PRESSURE
पूर्ण;

/* Channel definitions */
अटल स्थिर काष्ठा iio_chan_spec press_channels[] = अणु
	अणु
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
		.scan_index = CHANNEL_SCAN_INDEX_PRESSURE,
	पूर्ण
पूर्ण;

/* Adjust channel real bits based on report descriptor */
अटल व्योम press_adjust_channel_bit_mask(काष्ठा iio_chan_spec *channels,
					पूर्णांक channel, पूर्णांक size)
अणु
	channels[channel].scan_type.sign = 's';
	/* Real storage bits will change based on the report desc. */
	channels[channel].scan_type.realbits = size * 8;
	/* Maximum size of a sample to capture is u32 */
	channels[channel].scan_type.storagebits = माप(u32) * 8;
पूर्ण

/* Channel पढ़ो_raw handler */
अटल पूर्णांक press_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक *val, पूर्णांक *val2,
			      दीर्घ mask)
अणु
	काष्ठा press_state *press_state = iio_priv(indio_dev);
	पूर्णांक report_id = -1;
	u32 address;
	पूर्णांक ret_type;
	s32 min;

	*val = 0;
	*val2 = 0;
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->scan_index) अणु
		हाल  CHANNEL_SCAN_INDEX_PRESSURE:
			report_id = press_state->press_attr.report_id;
			min = press_state->press_attr.logical_minimum;
			address = HID_USAGE_SENSOR_ATMOSPHERIC_PRESSURE;
			अवरोध;
		शेष:
			report_id = -1;
			अवरोध;
		पूर्ण
		अगर (report_id >= 0) अणु
			hid_sensor_घातer_state(&press_state->common_attributes,
						true);
			*val = sensor_hub_input_attr_get_raw_value(
				press_state->common_attributes.hsdev,
				HID_USAGE_SENSOR_PRESSURE, address,
				report_id,
				SENSOR_HUB_SYNC,
				min < 0);
			hid_sensor_घातer_state(&press_state->common_attributes,
						false);
		पूर्ण अन्यथा अणु
			*val = 0;
			वापस -EINVAL;
		पूर्ण
		ret_type = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		*val = press_state->scale_pre_decml;
		*val2 = press_state->scale_post_decml;
		ret_type = press_state->scale_precision;
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = press_state->value_offset;
		ret_type = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret_type = hid_sensor_पढ़ो_samp_freq_value(
				&press_state->common_attributes, val, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_HYSTERESIS:
		ret_type = hid_sensor_पढ़ो_raw_hyst_value(
				&press_state->common_attributes, val, val2);
		अवरोध;
	शेष:
		ret_type = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret_type;
पूर्ण

/* Channel ग_लिखो_raw handler */
अटल पूर्णांक press_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा press_state *press_state = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = hid_sensor_ग_लिखो_samp_freq_value(
				&press_state->common_attributes, val, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_HYSTERESIS:
		ret = hid_sensor_ग_लिखो_raw_hyst_value(
				&press_state->common_attributes, val, val2);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info press_info = अणु
	.पढ़ो_raw = &press_पढ़ो_raw,
	.ग_लिखो_raw = &press_ग_लिखो_raw,
पूर्ण;

/* Function to push data to buffer */
अटल व्योम hid_sensor_push_data(काष्ठा iio_dev *indio_dev, स्थिर व्योम *data,
					पूर्णांक len)
अणु
	dev_dbg(&indio_dev->dev, "hid_sensor_push_data\n");
	iio_push_to_buffers(indio_dev, data);
पूर्ण

/* Callback handler to send event after all samples are received and captured */
अटल पूर्णांक press_proc_event(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित usage_id,
				व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(priv);
	काष्ठा press_state *press_state = iio_priv(indio_dev);

	dev_dbg(&indio_dev->dev, "press_proc_event\n");
	अगर (atomic_पढ़ो(&press_state->common_attributes.data_पढ़ोy))
		hid_sensor_push_data(indio_dev,
				&press_state->press_data,
				माप(press_state->press_data));

	वापस 0;
पूर्ण

/* Capture samples in local storage */
अटल पूर्णांक press_capture_sample(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित usage_id,
				माप_प्रकार raw_len, अक्षर *raw_data,
				व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(priv);
	काष्ठा press_state *press_state = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL;

	चयन (usage_id) अणु
	हाल HID_USAGE_SENSOR_ATMOSPHERIC_PRESSURE:
		press_state->press_data = *(u32 *)raw_data;
		ret = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* Parse report which is specअगरic to an usage id*/
अटल पूर्णांक press_parse_report(काष्ठा platक्रमm_device *pdev,
				काष्ठा hid_sensor_hub_device *hsdev,
				काष्ठा iio_chan_spec *channels,
				अचिन्हित usage_id,
				काष्ठा press_state *st)
अणु
	पूर्णांक ret;

	ret = sensor_hub_input_get_attribute_info(hsdev, HID_INPUT_REPORT,
			usage_id,
			HID_USAGE_SENSOR_ATMOSPHERIC_PRESSURE,
			&st->press_attr);
	अगर (ret < 0)
		वापस ret;
	press_adjust_channel_bit_mask(channels, CHANNEL_SCAN_INDEX_PRESSURE,
					st->press_attr.size);

	dev_dbg(&pdev->dev, "press %x:%x\n", st->press_attr.index,
			st->press_attr.report_id);

	st->scale_precision = hid_sensor_क्रमmat_scale(
				HID_USAGE_SENSOR_PRESSURE,
				&st->press_attr,
				&st->scale_pre_decml, &st->scale_post_decml);

	वापस ret;
पूर्ण

/* Function to initialize the processing क्रम usage id */
अटल पूर्णांक hid_press_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	अटल स्थिर अक्षर *name = "press";
	काष्ठा iio_dev *indio_dev;
	काष्ठा press_state *press_state;
	काष्ठा hid_sensor_hub_device *hsdev = pdev->dev.platक्रमm_data;

	indio_dev = devm_iio_device_alloc(&pdev->dev,
				माप(काष्ठा press_state));
	अगर (!indio_dev)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, indio_dev);

	press_state = iio_priv(indio_dev);
	press_state->common_attributes.hsdev = hsdev;
	press_state->common_attributes.pdev = pdev;

	ret = hid_sensor_parse_common_attributes(hsdev,
					HID_USAGE_SENSOR_PRESSURE,
					&press_state->common_attributes,
					press_sensitivity_addresses,
					ARRAY_SIZE(press_sensitivity_addresses));
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup common attributes\n");
		वापस ret;
	पूर्ण

	indio_dev->channels = kmemdup(press_channels, माप(press_channels),
				      GFP_KERNEL);
	अगर (!indio_dev->channels) अणु
		dev_err(&pdev->dev, "failed to duplicate channels\n");
		वापस -ENOMEM;
	पूर्ण

	ret = press_parse_report(pdev, hsdev,
				 (काष्ठा iio_chan_spec *)indio_dev->channels,
				 HID_USAGE_SENSOR_PRESSURE, press_state);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup attributes\n");
		जाओ error_मुक्त_dev_mem;
	पूर्ण

	indio_dev->num_channels =
				ARRAY_SIZE(press_channels);
	indio_dev->info = &press_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	atomic_set(&press_state->common_attributes.data_पढ़ोy, 0);

	ret = hid_sensor_setup_trigger(indio_dev, name,
				&press_state->common_attributes);
	अगर (ret) अणु
		dev_err(&pdev->dev, "trigger setup failed\n");
		जाओ error_मुक्त_dev_mem;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "device register failed\n");
		जाओ error_हटाओ_trigger;
	पूर्ण

	press_state->callbacks.send_event = press_proc_event;
	press_state->callbacks.capture_sample = press_capture_sample;
	press_state->callbacks.pdev = pdev;
	ret = sensor_hub_रेजिस्टर_callback(hsdev, HID_USAGE_SENSOR_PRESSURE,
					&press_state->callbacks);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "callback reg failed\n");
		जाओ error_iio_unreg;
	पूर्ण

	वापस ret;

error_iio_unreg:
	iio_device_unरेजिस्टर(indio_dev);
error_हटाओ_trigger:
	hid_sensor_हटाओ_trigger(indio_dev, &press_state->common_attributes);
error_मुक्त_dev_mem:
	kमुक्त(indio_dev->channels);
	वापस ret;
पूर्ण

/* Function to deinitialize the processing क्रम usage id */
अटल पूर्णांक hid_press_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hid_sensor_hub_device *hsdev = pdev->dev.platक्रमm_data;
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा press_state *press_state = iio_priv(indio_dev);

	sensor_hub_हटाओ_callback(hsdev, HID_USAGE_SENSOR_PRESSURE);
	iio_device_unरेजिस्टर(indio_dev);
	hid_sensor_हटाओ_trigger(indio_dev, &press_state->common_attributes);
	kमुक्त(indio_dev->channels);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id hid_press_ids[] = अणु
	अणु
		/* Format: HID-SENSOR-usage_id_in_hex_lowerहाल */
		.name = "HID-SENSOR-200031",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, hid_press_ids);

अटल काष्ठा platक्रमm_driver hid_press_platक्रमm_driver = अणु
	.id_table = hid_press_ids,
	.driver = अणु
		.name	= KBUILD_MODNAME,
		.pm	= &hid_sensor_pm_ops,
	पूर्ण,
	.probe		= hid_press_probe,
	.हटाओ		= hid_press_हटाओ,
पूर्ण;
module_platक्रमm_driver(hid_press_platक्रमm_driver);

MODULE_DESCRIPTION("HID Sensor Pressure");
MODULE_AUTHOR("Archana Patni <archana.patni@intel.com>");
MODULE_LICENSE("GPL");
