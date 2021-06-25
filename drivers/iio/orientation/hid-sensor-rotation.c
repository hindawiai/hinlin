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
#समावेश <linux/hid-sensor-hub.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश "../common/hid-sensors/hid-sensor-trigger.h"

काष्ठा dev_rot_state अणु
	काष्ठा hid_sensor_hub_callbacks callbacks;
	काष्ठा hid_sensor_common common_attributes;
	काष्ठा hid_sensor_hub_attribute_info quaternion;
	काष्ठा अणु
		s32 sampled_vals[4] __aligned(16);
		u64 बारtamp __aligned(8);
	पूर्ण scan;
	पूर्णांक scale_pre_decml;
	पूर्णांक scale_post_decml;
	पूर्णांक scale_precision;
	पूर्णांक value_offset;
	s64 बारtamp;
पूर्ण;

अटल स्थिर u32 rotation_sensitivity_addresses[] = अणु
	HID_USAGE_SENSOR_DATA_ORIENTATION,
	HID_USAGE_SENSOR_ORIENT_QUATERNION,
पूर्ण;

/* Channel definitions */
अटल स्थिर काष्ठा iio_chan_spec dev_rot_channels[] = अणु
	अणु
		.type = IIO_ROT,
		.modअगरied = 1,
		.channel2 = IIO_MOD_QUATERNION,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SAMP_FREQ) |
					BIT(IIO_CHAN_INFO_OFFSET) |
					BIT(IIO_CHAN_INFO_SCALE) |
					BIT(IIO_CHAN_INFO_HYSTERESIS),
		.scan_index = 0
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1)
पूर्ण;

/* Adjust channel real bits based on report descriptor */
अटल व्योम dev_rot_adjust_channel_bit_mask(काष्ठा iio_chan_spec *chan,
						पूर्णांक size)
अणु
	chan->scan_type.sign = 's';
	/* Real storage bits will change based on the report desc. */
	chan->scan_type.realbits = size * 8;
	/* Maximum size of a sample to capture is u32 */
	chan->scan_type.storagebits = माप(u32) * 8;
	chan->scan_type.repeat = 4;
पूर्ण

/* Channel पढ़ो_raw handler */
अटल पूर्णांक dev_rot_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक size, पूर्णांक *vals, पूर्णांक *val_len,
				दीर्घ mask)
अणु
	काष्ठा dev_rot_state *rot_state = iio_priv(indio_dev);
	पूर्णांक ret_type;
	पूर्णांक i;

	vals[0] = 0;
	vals[1] = 0;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (size >= 4) अणु
			क्रम (i = 0; i < 4; ++i)
				vals[i] = rot_state->scan.sampled_vals[i];
			ret_type = IIO_VAL_INT_MULTIPLE;
			*val_len =  4;
		पूर्ण अन्यथा
			ret_type = -EINVAL;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		vals[0] = rot_state->scale_pre_decml;
		vals[1] = rot_state->scale_post_decml;
		वापस rot_state->scale_precision;

	हाल IIO_CHAN_INFO_OFFSET:
		*vals = rot_state->value_offset;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret_type = hid_sensor_पढ़ो_samp_freq_value(
			&rot_state->common_attributes, &vals[0], &vals[1]);
		अवरोध;
	हाल IIO_CHAN_INFO_HYSTERESIS:
		ret_type = hid_sensor_पढ़ो_raw_hyst_value(
			&rot_state->common_attributes, &vals[0], &vals[1]);
		अवरोध;
	शेष:
		ret_type = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret_type;
पूर्ण

/* Channel ग_लिखो_raw handler */
अटल पूर्णांक dev_rot_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा dev_rot_state *rot_state = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = hid_sensor_ग_लिखो_samp_freq_value(
				&rot_state->common_attributes, val, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_HYSTERESIS:
		ret = hid_sensor_ग_लिखो_raw_hyst_value(
				&rot_state->common_attributes, val, val2);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info dev_rot_info = अणु
	.पढ़ो_raw_multi = &dev_rot_पढ़ो_raw,
	.ग_लिखो_raw = &dev_rot_ग_लिखो_raw,
पूर्ण;

/* Callback handler to send event after all samples are received and captured */
अटल पूर्णांक dev_rot_proc_event(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित usage_id,
				व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(priv);
	काष्ठा dev_rot_state *rot_state = iio_priv(indio_dev);

	dev_dbg(&indio_dev->dev, "dev_rot_proc_event\n");
	अगर (atomic_पढ़ो(&rot_state->common_attributes.data_पढ़ोy)) अणु
		अगर (!rot_state->बारtamp)
			rot_state->बारtamp = iio_get_समय_ns(indio_dev);

		iio_push_to_buffers_with_बारtamp(indio_dev, &rot_state->scan,
						   rot_state->बारtamp);

		rot_state->बारtamp = 0;
	पूर्ण

	वापस 0;
पूर्ण

/* Capture samples in local storage */
अटल पूर्णांक dev_rot_capture_sample(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित usage_id,
				माप_प्रकार raw_len, अक्षर *raw_data,
				व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(priv);
	काष्ठा dev_rot_state *rot_state = iio_priv(indio_dev);

	अगर (usage_id == HID_USAGE_SENSOR_ORIENT_QUATERNION) अणु
		अगर (raw_len / 4 == माप(s16)) अणु
			rot_state->scan.sampled_vals[0] = ((s16 *)raw_data)[0];
			rot_state->scan.sampled_vals[1] = ((s16 *)raw_data)[1];
			rot_state->scan.sampled_vals[2] = ((s16 *)raw_data)[2];
			rot_state->scan.sampled_vals[3] = ((s16 *)raw_data)[3];
		पूर्ण अन्यथा अणु
			स_नकल(&rot_state->scan.sampled_vals, raw_data,
			       माप(rot_state->scan.sampled_vals));
		पूर्ण

		dev_dbg(&indio_dev->dev, "Recd Quat len:%zu::%zu\n", raw_len,
			माप(rot_state->scan.sampled_vals));
	पूर्ण अन्यथा अगर (usage_id == HID_USAGE_SENSOR_TIME_TIMESTAMP) अणु
		rot_state->बारtamp = hid_sensor_convert_बारtamp(&rot_state->common_attributes,
								    *(s64 *)raw_data);
	पूर्ण

	वापस 0;
पूर्ण

/* Parse report which is specअगरic to an usage id*/
अटल पूर्णांक dev_rot_parse_report(काष्ठा platक्रमm_device *pdev,
				काष्ठा hid_sensor_hub_device *hsdev,
				काष्ठा iio_chan_spec *channels,
				अचिन्हित usage_id,
				काष्ठा dev_rot_state *st)
अणु
	पूर्णांक ret;

	ret = sensor_hub_input_get_attribute_info(hsdev,
				HID_INPUT_REPORT,
				usage_id,
				HID_USAGE_SENSOR_ORIENT_QUATERNION,
				&st->quaternion);
	अगर (ret)
		वापस ret;

	dev_rot_adjust_channel_bit_mask(&channels[0],
		st->quaternion.size / 4);

	dev_dbg(&pdev->dev, "dev_rot %x:%x\n", st->quaternion.index,
		st->quaternion.report_id);

	dev_dbg(&pdev->dev, "dev_rot: attrib size %d\n",
				st->quaternion.size);

	st->scale_precision = hid_sensor_क्रमmat_scale(
				hsdev->usage,
				&st->quaternion,
				&st->scale_pre_decml, &st->scale_post_decml);

	वापस 0;
पूर्ण

/* Function to initialize the processing क्रम usage id */
अटल पूर्णांक hid_dev_rot_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	अक्षर *name;
	काष्ठा iio_dev *indio_dev;
	काष्ठा dev_rot_state *rot_state;
	काष्ठा hid_sensor_hub_device *hsdev = pdev->dev.platक्रमm_data;

	indio_dev = devm_iio_device_alloc(&pdev->dev,
					  माप(काष्ठा dev_rot_state));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, indio_dev);

	rot_state = iio_priv(indio_dev);
	rot_state->common_attributes.hsdev = hsdev;
	rot_state->common_attributes.pdev = pdev;

	चयन (hsdev->usage) अणु
	हाल HID_USAGE_SENSOR_DEVICE_ORIENTATION:
		name = "dev_rotation";
		अवरोध;
	हाल HID_USAGE_SENSOR_RELATIVE_ORIENTATION:
		name = "relative_orientation";
		अवरोध;
	हाल HID_USAGE_SENSOR_GEOMAGNETIC_ORIENTATION:
		name = "geomagnetic_orientation";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = hid_sensor_parse_common_attributes(hsdev,
						 hsdev->usage,
						 &rot_state->common_attributes,
						 rotation_sensitivity_addresses,
						 ARRAY_SIZE(rotation_sensitivity_addresses));
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup common attributes\n");
		वापस ret;
	पूर्ण

	indio_dev->channels = devm_kmemdup(&pdev->dev, dev_rot_channels,
					   माप(dev_rot_channels),
					   GFP_KERNEL);
	अगर (!indio_dev->channels) अणु
		dev_err(&pdev->dev, "failed to duplicate channels\n");
		वापस -ENOMEM;
	पूर्ण

	ret = dev_rot_parse_report(pdev, hsdev,
				   (काष्ठा iio_chan_spec *)indio_dev->channels,
					hsdev->usage, rot_state);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup attributes\n");
		वापस ret;
	पूर्ण

	indio_dev->num_channels = ARRAY_SIZE(dev_rot_channels);
	indio_dev->info = &dev_rot_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	atomic_set(&rot_state->common_attributes.data_पढ़ोy, 0);

	ret = hid_sensor_setup_trigger(indio_dev, name,
					&rot_state->common_attributes);
	अगर (ret) अणु
		dev_err(&pdev->dev, "trigger setup failed\n");
		वापस ret;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "device register failed\n");
		जाओ error_हटाओ_trigger;
	पूर्ण

	rot_state->callbacks.send_event = dev_rot_proc_event;
	rot_state->callbacks.capture_sample = dev_rot_capture_sample;
	rot_state->callbacks.pdev = pdev;
	ret = sensor_hub_रेजिस्टर_callback(hsdev, hsdev->usage,
					&rot_state->callbacks);
	अगर (ret) अणु
		dev_err(&pdev->dev, "callback reg failed\n");
		जाओ error_iio_unreg;
	पूर्ण

	वापस 0;

error_iio_unreg:
	iio_device_unरेजिस्टर(indio_dev);
error_हटाओ_trigger:
	hid_sensor_हटाओ_trigger(indio_dev, &rot_state->common_attributes);
	वापस ret;
पूर्ण

/* Function to deinitialize the processing क्रम usage id */
अटल पूर्णांक hid_dev_rot_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hid_sensor_hub_device *hsdev = pdev->dev.platक्रमm_data;
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा dev_rot_state *rot_state = iio_priv(indio_dev);

	sensor_hub_हटाओ_callback(hsdev, hsdev->usage);
	iio_device_unरेजिस्टर(indio_dev);
	hid_sensor_हटाओ_trigger(indio_dev, &rot_state->common_attributes);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id hid_dev_rot_ids[] = अणु
	अणु
		/* Format: HID-SENSOR-usage_id_in_hex_lowerहाल */
		.name = "HID-SENSOR-20008a",
	पूर्ण,
	अणु
		/* Relative orientation(AG) sensor */
		.name = "HID-SENSOR-20008e",
	पूर्ण,
	अणु
		/* Geomagnetic orientation(AM) sensor */
		.name = "HID-SENSOR-2000c1",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, hid_dev_rot_ids);

अटल काष्ठा platक्रमm_driver hid_dev_rot_platक्रमm_driver = अणु
	.id_table = hid_dev_rot_ids,
	.driver = अणु
		.name	= KBUILD_MODNAME,
		.pm     = &hid_sensor_pm_ops,
	पूर्ण,
	.probe		= hid_dev_rot_probe,
	.हटाओ		= hid_dev_rot_हटाओ,
पूर्ण;
module_platक्रमm_driver(hid_dev_rot_platक्रमm_driver);

MODULE_DESCRIPTION("HID Sensor Device Rotation");
MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_LICENSE("GPL");
