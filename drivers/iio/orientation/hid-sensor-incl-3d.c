<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID Sensors Driver
 * Copyright (c) 2013, Intel Corporation.
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

क्रमागत incl_3d_channel अणु
	CHANNEL_SCAN_INDEX_X,
	CHANNEL_SCAN_INDEX_Y,
	CHANNEL_SCAN_INDEX_Z,
	INCLI_3D_CHANNEL_MAX,
पूर्ण;

#घोषणा CHANNEL_SCAN_INDEX_TIMESTAMP INCLI_3D_CHANNEL_MAX

काष्ठा incl_3d_state अणु
	काष्ठा hid_sensor_hub_callbacks callbacks;
	काष्ठा hid_sensor_common common_attributes;
	काष्ठा hid_sensor_hub_attribute_info incl[INCLI_3D_CHANNEL_MAX];
	काष्ठा अणु
		u32 incl_val[INCLI_3D_CHANNEL_MAX];
		u64 बारtamp __aligned(8);
	पूर्ण scan;
	पूर्णांक scale_pre_decml;
	पूर्णांक scale_post_decml;
	पूर्णांक scale_precision;
	पूर्णांक value_offset;
	s64 बारtamp;
पूर्ण;

अटल स्थिर u32 incl_3d_addresses[INCLI_3D_CHANNEL_MAX] = अणु
	HID_USAGE_SENSOR_ORIENT_TILT_X,
	HID_USAGE_SENSOR_ORIENT_TILT_Y,
	HID_USAGE_SENSOR_ORIENT_TILT_Z
पूर्ण;

अटल स्थिर u32 incl_3d_sensitivity_addresses[] = अणु
	HID_USAGE_SENSOR_DATA_ORIENTATION,
	HID_USAGE_SENSOR_ORIENT_TILT,
पूर्ण;

/* Channel definitions */
अटल स्थिर काष्ठा iio_chan_spec incl_3d_channels[] = अणु
	अणु
		.type = IIO_INCLI,
		.modअगरied = 1,
		.channel2 = IIO_MOD_X,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
		.scan_index = CHANNEL_SCAN_INDEX_X,
	पूर्ण, अणु
		.type = IIO_INCLI,
		.modअगरied = 1,
		.channel2 = IIO_MOD_Y,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
		.scan_index = CHANNEL_SCAN_INDEX_Y,
	पूर्ण, अणु
		.type = IIO_INCLI,
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
अटल व्योम incl_3d_adjust_channel_bit_mask(काष्ठा iio_chan_spec *chan,
						पूर्णांक size)
अणु
	chan->scan_type.sign = 's';
	/* Real storage bits will change based on the report desc. */
	chan->scan_type.realbits = size * 8;
	/* Maximum size of a sample to capture is u32 */
	chan->scan_type.storagebits = माप(u32) * 8;
पूर्ण

/* Channel पढ़ो_raw handler */
अटल पूर्णांक incl_3d_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक *val, पूर्णांक *val2,
			      दीर्घ mask)
अणु
	काष्ठा incl_3d_state *incl_state = iio_priv(indio_dev);
	पूर्णांक report_id = -1;
	u32 address;
	पूर्णांक ret_type;
	s32 min;

	*val = 0;
	*val2 = 0;
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		hid_sensor_घातer_state(&incl_state->common_attributes, true);
		report_id = incl_state->incl[chan->scan_index].report_id;
		min = incl_state->incl[chan->scan_index].logical_minimum;
		address = incl_3d_addresses[chan->scan_index];
		अगर (report_id >= 0)
			*val = sensor_hub_input_attr_get_raw_value(
				incl_state->common_attributes.hsdev,
				HID_USAGE_SENSOR_INCLINOMETER_3D, address,
				report_id,
				SENSOR_HUB_SYNC,
				min < 0);
		अन्यथा अणु
			hid_sensor_घातer_state(&incl_state->common_attributes,
						false);
			वापस -EINVAL;
		पूर्ण
		hid_sensor_घातer_state(&incl_state->common_attributes, false);
		ret_type = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		*val = incl_state->scale_pre_decml;
		*val2 = incl_state->scale_post_decml;
		ret_type = incl_state->scale_precision;
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = incl_state->value_offset;
		ret_type = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret_type = hid_sensor_पढ़ो_samp_freq_value(
			&incl_state->common_attributes, val, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_HYSTERESIS:
		ret_type = hid_sensor_पढ़ो_raw_hyst_value(
			&incl_state->common_attributes, val, val2);
		अवरोध;
	शेष:
		ret_type = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret_type;
पूर्ण

/* Channel ग_लिखो_raw handler */
अटल पूर्णांक incl_3d_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा incl_3d_state *incl_state = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = hid_sensor_ग_लिखो_samp_freq_value(
				&incl_state->common_attributes, val, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_HYSTERESIS:
		ret = hid_sensor_ग_लिखो_raw_hyst_value(
				&incl_state->common_attributes, val, val2);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info incl_3d_info = अणु
	.पढ़ो_raw = &incl_3d_पढ़ो_raw,
	.ग_लिखो_raw = &incl_3d_ग_लिखो_raw,
पूर्ण;

/* Callback handler to send event after all samples are received and captured */
अटल पूर्णांक incl_3d_proc_event(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित usage_id,
				व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(priv);
	काष्ठा incl_3d_state *incl_state = iio_priv(indio_dev);

	dev_dbg(&indio_dev->dev, "incl_3d_proc_event\n");
	अगर (atomic_पढ़ो(&incl_state->common_attributes.data_पढ़ोy)) अणु
		अगर (!incl_state->बारtamp)
			incl_state->बारtamp = iio_get_समय_ns(indio_dev);

		iio_push_to_buffers_with_बारtamp(indio_dev,
						   &incl_state->scan,
						   incl_state->बारtamp);

		incl_state->बारtamp = 0;
	पूर्ण

	वापस 0;
पूर्ण

/* Capture samples in local storage */
अटल पूर्णांक incl_3d_capture_sample(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित usage_id,
				माप_प्रकार raw_len, अक्षर *raw_data,
				व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(priv);
	काष्ठा incl_3d_state *incl_state = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	चयन (usage_id) अणु
	हाल HID_USAGE_SENSOR_ORIENT_TILT_X:
		incl_state->scan.incl_val[CHANNEL_SCAN_INDEX_X] = *(u32 *)raw_data;
	अवरोध;
	हाल HID_USAGE_SENSOR_ORIENT_TILT_Y:
		incl_state->scan.incl_val[CHANNEL_SCAN_INDEX_Y] = *(u32 *)raw_data;
	अवरोध;
	हाल HID_USAGE_SENSOR_ORIENT_TILT_Z:
		incl_state->scan.incl_val[CHANNEL_SCAN_INDEX_Z] = *(u32 *)raw_data;
	अवरोध;
	हाल HID_USAGE_SENSOR_TIME_TIMESTAMP:
		incl_state->बारtamp =
			hid_sensor_convert_बारtamp(&incl_state->common_attributes,
						     *(s64 *)raw_data);
	अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* Parse report which is specअगरic to an usage id*/
अटल पूर्णांक incl_3d_parse_report(काष्ठा platक्रमm_device *pdev,
				काष्ठा hid_sensor_hub_device *hsdev,
				काष्ठा iio_chan_spec *channels,
				अचिन्हित usage_id,
				काष्ठा incl_3d_state *st)
अणु
	पूर्णांक ret;

	ret = sensor_hub_input_get_attribute_info(hsdev,
				HID_INPUT_REPORT,
				usage_id,
				HID_USAGE_SENSOR_ORIENT_TILT_X,
				&st->incl[CHANNEL_SCAN_INDEX_X]);
	अगर (ret)
		वापस ret;
	incl_3d_adjust_channel_bit_mask(&channels[CHANNEL_SCAN_INDEX_X],
				st->incl[CHANNEL_SCAN_INDEX_X].size);

	ret = sensor_hub_input_get_attribute_info(hsdev,
				HID_INPUT_REPORT,
				usage_id,
				HID_USAGE_SENSOR_ORIENT_TILT_Y,
				&st->incl[CHANNEL_SCAN_INDEX_Y]);
	अगर (ret)
		वापस ret;
	incl_3d_adjust_channel_bit_mask(&channels[CHANNEL_SCAN_INDEX_Y],
				st->incl[CHANNEL_SCAN_INDEX_Y].size);

	ret = sensor_hub_input_get_attribute_info(hsdev,
				HID_INPUT_REPORT,
				usage_id,
				HID_USAGE_SENSOR_ORIENT_TILT_Z,
				&st->incl[CHANNEL_SCAN_INDEX_Z]);
	अगर (ret)
		वापस ret;
	incl_3d_adjust_channel_bit_mask(&channels[CHANNEL_SCAN_INDEX_Z],
				st->incl[CHANNEL_SCAN_INDEX_Z].size);

	dev_dbg(&pdev->dev, "incl_3d %x:%x, %x:%x, %x:%x\n",
			st->incl[0].index,
			st->incl[0].report_id,
			st->incl[1].index, st->incl[1].report_id,
			st->incl[2].index, st->incl[2].report_id);

	st->scale_precision = hid_sensor_क्रमmat_scale(
				HID_USAGE_SENSOR_INCLINOMETER_3D,
				&st->incl[CHANNEL_SCAN_INDEX_X],
				&st->scale_pre_decml, &st->scale_post_decml);

	वापस ret;
पूर्ण

/* Function to initialize the processing क्रम usage id */
अटल पूर्णांक hid_incl_3d_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	अटल अक्षर *name = "incli_3d";
	काष्ठा iio_dev *indio_dev;
	काष्ठा incl_3d_state *incl_state;
	काष्ठा hid_sensor_hub_device *hsdev = pdev->dev.platक्रमm_data;

	indio_dev = devm_iio_device_alloc(&pdev->dev,
					  माप(काष्ठा incl_3d_state));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, indio_dev);

	incl_state = iio_priv(indio_dev);
	incl_state->common_attributes.hsdev = hsdev;
	incl_state->common_attributes.pdev = pdev;

	ret = hid_sensor_parse_common_attributes(hsdev,
				HID_USAGE_SENSOR_INCLINOMETER_3D,
				&incl_state->common_attributes,
				incl_3d_sensitivity_addresses,
				ARRAY_SIZE(incl_3d_sensitivity_addresses));
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup common attributes\n");
		वापस ret;
	पूर्ण

	indio_dev->channels = kmemdup(incl_3d_channels,
				      माप(incl_3d_channels), GFP_KERNEL);
	अगर (!indio_dev->channels) अणु
		dev_err(&pdev->dev, "failed to duplicate channels\n");
		वापस -ENOMEM;
	पूर्ण

	ret = incl_3d_parse_report(pdev, hsdev,
				   (काष्ठा iio_chan_spec *)indio_dev->channels,
				   HID_USAGE_SENSOR_INCLINOMETER_3D,
				   incl_state);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup attributes\n");
		जाओ error_मुक्त_dev_mem;
	पूर्ण

	indio_dev->num_channels = ARRAY_SIZE(incl_3d_channels);
	indio_dev->info = &incl_3d_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	atomic_set(&incl_state->common_attributes.data_पढ़ोy, 0);

	ret = hid_sensor_setup_trigger(indio_dev, name,
					&incl_state->common_attributes);
	अगर (ret) अणु
		dev_err(&pdev->dev, "trigger setup failed\n");
		जाओ error_मुक्त_dev_mem;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "device register failed\n");
		जाओ error_हटाओ_trigger;
	पूर्ण

	incl_state->callbacks.send_event = incl_3d_proc_event;
	incl_state->callbacks.capture_sample = incl_3d_capture_sample;
	incl_state->callbacks.pdev = pdev;
	ret = sensor_hub_रेजिस्टर_callback(hsdev,
					HID_USAGE_SENSOR_INCLINOMETER_3D,
					&incl_state->callbacks);
	अगर (ret) अणु
		dev_err(&pdev->dev, "callback reg failed\n");
		जाओ error_iio_unreg;
	पूर्ण

	वापस 0;

error_iio_unreg:
	iio_device_unरेजिस्टर(indio_dev);
error_हटाओ_trigger:
	hid_sensor_हटाओ_trigger(indio_dev, &incl_state->common_attributes);
error_मुक्त_dev_mem:
	kमुक्त(indio_dev->channels);
	वापस ret;
पूर्ण

/* Function to deinitialize the processing क्रम usage id */
अटल पूर्णांक hid_incl_3d_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hid_sensor_hub_device *hsdev = pdev->dev.platक्रमm_data;
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा incl_3d_state *incl_state = iio_priv(indio_dev);

	sensor_hub_हटाओ_callback(hsdev, HID_USAGE_SENSOR_INCLINOMETER_3D);
	iio_device_unरेजिस्टर(indio_dev);
	hid_sensor_हटाओ_trigger(indio_dev, &incl_state->common_attributes);
	kमुक्त(indio_dev->channels);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id hid_incl_3d_ids[] = अणु
	अणु
		/* Format: HID-SENSOR-usage_id_in_hex_lowerहाल */
		.name = "HID-SENSOR-200086",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, hid_incl_3d_ids);

अटल काष्ठा platक्रमm_driver hid_incl_3d_platक्रमm_driver = अणु
	.id_table = hid_incl_3d_ids,
	.driver = अणु
		.name	= KBUILD_MODNAME,
		.pm	= &hid_sensor_pm_ops,
	पूर्ण,
	.probe		= hid_incl_3d_probe,
	.हटाओ		= hid_incl_3d_हटाओ,
पूर्ण;
module_platक्रमm_driver(hid_incl_3d_platक्रमm_driver);

MODULE_DESCRIPTION("HID Sensor Inclinometer 3D");
MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_LICENSE("GPL");
