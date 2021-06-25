<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID Sensors Driver
 * Copyright (c) 2012, Intel Corporation.
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

क्रमागत accel_3d_channel अणु
	CHANNEL_SCAN_INDEX_X,
	CHANNEL_SCAN_INDEX_Y,
	CHANNEL_SCAN_INDEX_Z,
	ACCEL_3D_CHANNEL_MAX,
पूर्ण;

#घोषणा CHANNEL_SCAN_INDEX_TIMESTAMP ACCEL_3D_CHANNEL_MAX
काष्ठा accel_3d_state अणु
	काष्ठा hid_sensor_hub_callbacks callbacks;
	काष्ठा hid_sensor_common common_attributes;
	काष्ठा hid_sensor_hub_attribute_info accel[ACCEL_3D_CHANNEL_MAX];
	/* Reserve क्रम 3 channels + padding + बारtamp */
	u32 accel_val[ACCEL_3D_CHANNEL_MAX + 3];
	पूर्णांक scale_pre_decml;
	पूर्णांक scale_post_decml;
	पूर्णांक scale_precision;
	पूर्णांक value_offset;
	पूर्णांक64_t बारtamp;
पूर्ण;

अटल स्थिर u32 accel_3d_addresses[ACCEL_3D_CHANNEL_MAX] = अणु
	HID_USAGE_SENSOR_ACCEL_X_AXIS,
	HID_USAGE_SENSOR_ACCEL_Y_AXIS,
	HID_USAGE_SENSOR_ACCEL_Z_AXIS
पूर्ण;

अटल स्थिर u32 accel_3d_sensitivity_addresses[] = अणु
	HID_USAGE_SENSOR_DATA_ACCELERATION,
पूर्ण;

/* Channel definitions */
अटल स्थिर काष्ठा iio_chan_spec accel_3d_channels[] = अणु
	अणु
		.type = IIO_ACCEL,
		.modअगरied = 1,
		.channel2 = IIO_MOD_X,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
		.scan_index = CHANNEL_SCAN_INDEX_X,
	पूर्ण, अणु
		.type = IIO_ACCEL,
		.modअगरied = 1,
		.channel2 = IIO_MOD_Y,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
		.scan_index = CHANNEL_SCAN_INDEX_Y,
	पूर्ण, अणु
		.type = IIO_ACCEL,
		.modअगरied = 1,
		.channel2 = IIO_MOD_Z,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
		.scan_index = CHANNEL_SCAN_INDEX_Z,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(CHANNEL_SCAN_INDEX_TIMESTAMP)
पूर्ण;

/* Channel definitions */
अटल स्थिर काष्ठा iio_chan_spec gravity_channels[] = अणु
	अणु
		.type = IIO_GRAVITY,
		.modअगरied = 1,
		.channel2 = IIO_MOD_X,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
		.scan_index = CHANNEL_SCAN_INDEX_X,
	पूर्ण, अणु
		.type = IIO_GRAVITY,
		.modअगरied = 1,
		.channel2 = IIO_MOD_Y,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
		.scan_index = CHANNEL_SCAN_INDEX_Y,
	पूर्ण, अणु
		.type = IIO_GRAVITY,
		.modअगरied = 1,
		.channel2 = IIO_MOD_Z,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
		.scan_index = CHANNEL_SCAN_INDEX_Z,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(CHANNEL_SCAN_INDEX_TIMESTAMP),
पूर्ण;

/* Adjust channel real bits based on report descriptor */
अटल व्योम accel_3d_adjust_channel_bit_mask(काष्ठा iio_chan_spec *channels,
						पूर्णांक channel, पूर्णांक size)
अणु
	channels[channel].scan_type.sign = 's';
	/* Real storage bits will change based on the report desc. */
	channels[channel].scan_type.realbits = size * 8;
	/* Maximum size of a sample to capture is u32 */
	channels[channel].scan_type.storagebits = माप(u32) * 8;
पूर्ण

/* Channel पढ़ो_raw handler */
अटल पूर्णांक accel_3d_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक *val, पूर्णांक *val2,
			      दीर्घ mask)
अणु
	काष्ठा accel_3d_state *accel_state = iio_priv(indio_dev);
	पूर्णांक report_id = -1;
	u32 address;
	पूर्णांक ret_type;
	s32 min;
	काष्ठा hid_sensor_hub_device *hsdev =
					accel_state->common_attributes.hsdev;

	*val = 0;
	*val2 = 0;
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		hid_sensor_घातer_state(&accel_state->common_attributes, true);
		report_id = accel_state->accel[chan->scan_index].report_id;
		min = accel_state->accel[chan->scan_index].logical_minimum;
		address = accel_3d_addresses[chan->scan_index];
		अगर (report_id >= 0)
			*val = sensor_hub_input_attr_get_raw_value(
					accel_state->common_attributes.hsdev,
					hsdev->usage, address, report_id,
					SENSOR_HUB_SYNC,
					min < 0);
		अन्यथा अणु
			*val = 0;
			hid_sensor_घातer_state(&accel_state->common_attributes,
						 false);
			वापस -EINVAL;
		पूर्ण
		hid_sensor_घातer_state(&accel_state->common_attributes, false);
		ret_type = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		*val = accel_state->scale_pre_decml;
		*val2 = accel_state->scale_post_decml;
		ret_type = accel_state->scale_precision;
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = accel_state->value_offset;
		ret_type = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret_type = hid_sensor_पढ़ो_samp_freq_value(
			&accel_state->common_attributes, val, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_HYSTERESIS:
		ret_type = hid_sensor_पढ़ो_raw_hyst_value(
			&accel_state->common_attributes, val, val2);
		अवरोध;
	शेष:
		ret_type = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret_type;
पूर्ण

/* Channel ग_लिखो_raw handler */
अटल पूर्णांक accel_3d_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा accel_3d_state *accel_state = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = hid_sensor_ग_लिखो_samp_freq_value(
				&accel_state->common_attributes, val, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_HYSTERESIS:
		ret = hid_sensor_ग_लिखो_raw_hyst_value(
				&accel_state->common_attributes, val, val2);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info accel_3d_info = अणु
	.पढ़ो_raw = &accel_3d_पढ़ो_raw,
	.ग_लिखो_raw = &accel_3d_ग_लिखो_raw,
पूर्ण;

/* Function to push data to buffer */
अटल व्योम hid_sensor_push_data(काष्ठा iio_dev *indio_dev, व्योम *data,
				 पूर्णांक len, पूर्णांक64_t बारtamp)
अणु
	dev_dbg(&indio_dev->dev, "hid_sensor_push_data\n");
	iio_push_to_buffers_with_बारtamp(indio_dev, data, बारtamp);
पूर्ण

/* Callback handler to send event after all samples are received and captured */
अटल पूर्णांक accel_3d_proc_event(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित usage_id,
				व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(priv);
	काष्ठा accel_3d_state *accel_state = iio_priv(indio_dev);

	dev_dbg(&indio_dev->dev, "accel_3d_proc_event\n");
	अगर (atomic_पढ़ो(&accel_state->common_attributes.data_पढ़ोy)) अणु
		अगर (!accel_state->बारtamp)
			accel_state->बारtamp = iio_get_समय_ns(indio_dev);

		hid_sensor_push_data(indio_dev,
				     accel_state->accel_val,
				     माप(accel_state->accel_val),
				     accel_state->बारtamp);

		accel_state->बारtamp = 0;
	पूर्ण

	वापस 0;
पूर्ण

/* Capture samples in local storage */
अटल पूर्णांक accel_3d_capture_sample(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित usage_id,
				माप_प्रकार raw_len, अक्षर *raw_data,
				व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(priv);
	काष्ठा accel_3d_state *accel_state = iio_priv(indio_dev);
	पूर्णांक offset;
	पूर्णांक ret = -EINVAL;

	चयन (usage_id) अणु
	हाल HID_USAGE_SENSOR_ACCEL_X_AXIS:
	हाल HID_USAGE_SENSOR_ACCEL_Y_AXIS:
	हाल HID_USAGE_SENSOR_ACCEL_Z_AXIS:
		offset = usage_id - HID_USAGE_SENSOR_ACCEL_X_AXIS;
		accel_state->accel_val[CHANNEL_SCAN_INDEX_X + offset] =
						*(u32 *)raw_data;
		ret = 0;
	अवरोध;
	हाल HID_USAGE_SENSOR_TIME_TIMESTAMP:
		accel_state->बारtamp =
			hid_sensor_convert_बारtamp(
					&accel_state->common_attributes,
					*(पूर्णांक64_t *)raw_data);
	अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* Parse report which is specअगरic to an usage id*/
अटल पूर्णांक accel_3d_parse_report(काष्ठा platक्रमm_device *pdev,
				काष्ठा hid_sensor_hub_device *hsdev,
				काष्ठा iio_chan_spec *channels,
				अचिन्हित usage_id,
				काष्ठा accel_3d_state *st)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i <= CHANNEL_SCAN_INDEX_Z; ++i) अणु
		ret = sensor_hub_input_get_attribute_info(hsdev,
				HID_INPUT_REPORT,
				usage_id,
				HID_USAGE_SENSOR_ACCEL_X_AXIS + i,
				&st->accel[CHANNEL_SCAN_INDEX_X + i]);
		अगर (ret < 0)
			अवरोध;
		accel_3d_adjust_channel_bit_mask(channels,
				CHANNEL_SCAN_INDEX_X + i,
				st->accel[CHANNEL_SCAN_INDEX_X + i].size);
	पूर्ण
	dev_dbg(&pdev->dev, "accel_3d %x:%x, %x:%x, %x:%x\n",
			st->accel[0].index,
			st->accel[0].report_id,
			st->accel[1].index, st->accel[1].report_id,
			st->accel[2].index, st->accel[2].report_id);

	st->scale_precision = hid_sensor_क्रमmat_scale(
				hsdev->usage,
				&st->accel[CHANNEL_SCAN_INDEX_X],
				&st->scale_pre_decml, &st->scale_post_decml);

	वापस ret;
पूर्ण

/* Function to initialize the processing क्रम usage id */
अटल पूर्णांक hid_accel_3d_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	स्थिर अक्षर *name;
	काष्ठा iio_dev *indio_dev;
	काष्ठा accel_3d_state *accel_state;
	स्थिर काष्ठा iio_chan_spec *channel_spec;
	पूर्णांक channel_size;

	काष्ठा hid_sensor_hub_device *hsdev = pdev->dev.platक्रमm_data;

	indio_dev = devm_iio_device_alloc(&pdev->dev,
					  माप(काष्ठा accel_3d_state));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, indio_dev);

	accel_state = iio_priv(indio_dev);
	accel_state->common_attributes.hsdev = hsdev;
	accel_state->common_attributes.pdev = pdev;

	अगर (hsdev->usage == HID_USAGE_SENSOR_ACCEL_3D) अणु
		name = "accel_3d";
		channel_spec = accel_3d_channels;
		channel_size = माप(accel_3d_channels);
		indio_dev->num_channels = ARRAY_SIZE(accel_3d_channels);
	पूर्ण अन्यथा अणु
		name = "gravity";
		channel_spec = gravity_channels;
		channel_size = माप(gravity_channels);
		indio_dev->num_channels = ARRAY_SIZE(gravity_channels);
	पूर्ण
	ret = hid_sensor_parse_common_attributes(hsdev,
						 hsdev->usage,
						 &accel_state->common_attributes,
						 accel_3d_sensitivity_addresses,
						 ARRAY_SIZE(accel_3d_sensitivity_addresses));
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup common attributes\n");
		वापस ret;
	पूर्ण
	indio_dev->channels = kmemdup(channel_spec, channel_size, GFP_KERNEL);

	अगर (!indio_dev->channels) अणु
		dev_err(&pdev->dev, "failed to duplicate channels\n");
		वापस -ENOMEM;
	पूर्ण
	ret = accel_3d_parse_report(pdev, hsdev,
				(काष्ठा iio_chan_spec *)indio_dev->channels,
				hsdev->usage, accel_state);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup attributes\n");
		जाओ error_मुक्त_dev_mem;
	पूर्ण

	indio_dev->info = &accel_3d_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	atomic_set(&accel_state->common_attributes.data_पढ़ोy, 0);

	ret = hid_sensor_setup_trigger(indio_dev, name,
					&accel_state->common_attributes);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "trigger setup failed\n");
		जाओ error_मुक्त_dev_mem;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "device register failed\n");
		जाओ error_हटाओ_trigger;
	पूर्ण

	accel_state->callbacks.send_event = accel_3d_proc_event;
	accel_state->callbacks.capture_sample = accel_3d_capture_sample;
	accel_state->callbacks.pdev = pdev;
	ret = sensor_hub_रेजिस्टर_callback(hsdev, hsdev->usage,
					&accel_state->callbacks);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "callback reg failed\n");
		जाओ error_iio_unreg;
	पूर्ण

	वापस ret;

error_iio_unreg:
	iio_device_unरेजिस्टर(indio_dev);
error_हटाओ_trigger:
	hid_sensor_हटाओ_trigger(indio_dev, &accel_state->common_attributes);
error_मुक्त_dev_mem:
	kमुक्त(indio_dev->channels);
	वापस ret;
पूर्ण

/* Function to deinitialize the processing क्रम usage id */
अटल पूर्णांक hid_accel_3d_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hid_sensor_hub_device *hsdev = pdev->dev.platक्रमm_data;
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा accel_3d_state *accel_state = iio_priv(indio_dev);

	sensor_hub_हटाओ_callback(hsdev, hsdev->usage);
	iio_device_unरेजिस्टर(indio_dev);
	hid_sensor_हटाओ_trigger(indio_dev, &accel_state->common_attributes);
	kमुक्त(indio_dev->channels);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id hid_accel_3d_ids[] = अणु
	अणु
		/* Format: HID-SENSOR-usage_id_in_hex_lowerहाल */
		.name = "HID-SENSOR-200073",
	पूर्ण,
	अणु	/* gravity sensor */
		.name = "HID-SENSOR-20007b",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, hid_accel_3d_ids);

अटल काष्ठा platक्रमm_driver hid_accel_3d_platक्रमm_driver = अणु
	.id_table = hid_accel_3d_ids,
	.driver = अणु
		.name	= KBUILD_MODNAME,
		.pm	= &hid_sensor_pm_ops,
	पूर्ण,
	.probe		= hid_accel_3d_probe,
	.हटाओ		= hid_accel_3d_हटाओ,
पूर्ण;
module_platक्रमm_driver(hid_accel_3d_platक्रमm_driver);

MODULE_DESCRIPTION("HID Sensor Accel 3D");
MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@intel.com>");
MODULE_LICENSE("GPL");
