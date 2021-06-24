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

क्रमागत magn_3d_channel अणु
	CHANNEL_SCAN_INDEX_X,
	CHANNEL_SCAN_INDEX_Y,
	CHANNEL_SCAN_INDEX_Z,
	CHANNEL_SCAN_INDEX_NORTH_MAGN_TILT_COMP,
	CHANNEL_SCAN_INDEX_NORTH_TRUE_TILT_COMP,
	CHANNEL_SCAN_INDEX_NORTH_MAGN,
	CHANNEL_SCAN_INDEX_NORTH_TRUE,
	CHANNEL_SCAN_INDEX_TIMESTAMP,
	MAGN_3D_CHANNEL_MAX,
पूर्ण;

काष्ठा common_attributes अणु
	पूर्णांक scale_pre_decml;
	पूर्णांक scale_post_decml;
	पूर्णांक scale_precision;
	पूर्णांक value_offset;
पूर्ण;

काष्ठा magn_3d_state अणु
	काष्ठा hid_sensor_hub_callbacks callbacks;
	काष्ठा hid_sensor_common magn_flux_attributes;
	काष्ठा hid_sensor_common rot_attributes;
	काष्ठा hid_sensor_hub_attribute_info magn[MAGN_3D_CHANNEL_MAX];

	/* dynamically sized array to hold sensor values */
	u32 *iio_vals;
	/* array of poपूर्णांकers to sensor value */
	u32 *magn_val_addr[MAGN_3D_CHANNEL_MAX];

	काष्ठा common_attributes magn_flux_attr;
	काष्ठा common_attributes rot_attr;
	s64 बारtamp;
पूर्ण;

अटल स्थिर u32 magn_3d_addresses[MAGN_3D_CHANNEL_MAX] = अणु
	HID_USAGE_SENSOR_ORIENT_MAGN_FLUX_X_AXIS,
	HID_USAGE_SENSOR_ORIENT_MAGN_FLUX_Y_AXIS,
	HID_USAGE_SENSOR_ORIENT_MAGN_FLUX_Z_AXIS,
	HID_USAGE_SENSOR_ORIENT_COMP_MAGN_NORTH,
	HID_USAGE_SENSOR_ORIENT_COMP_TRUE_NORTH,
	HID_USAGE_SENSOR_ORIENT_MAGN_NORTH,
	HID_USAGE_SENSOR_ORIENT_TRUE_NORTH,
	HID_USAGE_SENSOR_TIME_TIMESTAMP,
पूर्ण;

अटल स्थिर u32 magn_3d_sensitivity_addresses[] = अणु
	HID_USAGE_SENSOR_DATA_ORIENTATION,
	HID_USAGE_SENSOR_ORIENT_MAGN_FLUX,
पूर्ण;

/* Channel definitions */
अटल स्थिर काष्ठा iio_chan_spec magn_3d_channels[] = अणु
	अणु
		.type = IIO_MAGN,
		.modअगरied = 1,
		.channel2 = IIO_MOD_X,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
	पूर्ण, अणु
		.type = IIO_MAGN,
		.modअगरied = 1,
		.channel2 = IIO_MOD_Y,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
	पूर्ण, अणु
		.type = IIO_MAGN,
		.modअगरied = 1,
		.channel2 = IIO_MOD_Z,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
	पूर्ण, अणु
		.type = IIO_ROT,
		.modअगरied = 1,
		.channel2 = IIO_MOD_NORTH_MAGN_TILT_COMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
	पूर्ण, अणु
		.type = IIO_ROT,
		.modअगरied = 1,
		.channel2 = IIO_MOD_NORTH_TRUE_TILT_COMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
	पूर्ण, अणु
		.type = IIO_ROT,
		.modअगरied = 1,
		.channel2 = IIO_MOD_NORTH_MAGN,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
	पूर्ण, अणु
		.type = IIO_ROT,
		.modअगरied = 1,
		.channel2 = IIO_MOD_NORTH_TRUE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_HYSTERESIS),
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(7)
पूर्ण;

/* Adjust channel real bits based on report descriptor */
अटल व्योम magn_3d_adjust_channel_bit_mask(काष्ठा iio_chan_spec *channels,
						पूर्णांक channel, पूर्णांक size)
अणु
	channels[channel].scan_type.sign = 's';
	/* Real storage bits will change based on the report desc. */
	channels[channel].scan_type.realbits = size * 8;
	/* Maximum size of a sample to capture is u32 */
	channels[channel].scan_type.storagebits = माप(u32) * 8;
पूर्ण

/* Channel पढ़ो_raw handler */
अटल पूर्णांक magn_3d_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक *val, पूर्णांक *val2,
			      दीर्घ mask)
अणु
	काष्ठा magn_3d_state *magn_state = iio_priv(indio_dev);
	पूर्णांक report_id = -1;
	u32 address;
	पूर्णांक ret_type;
	s32 min;

	*val = 0;
	*val2 = 0;
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		hid_sensor_घातer_state(&magn_state->magn_flux_attributes, true);
		report_id = magn_state->magn[chan->address].report_id;
		min = magn_state->magn[chan->address].logical_minimum;
		address = magn_3d_addresses[chan->address];
		अगर (report_id >= 0)
			*val = sensor_hub_input_attr_get_raw_value(
				magn_state->magn_flux_attributes.hsdev,
				HID_USAGE_SENSOR_COMPASS_3D, address,
				report_id,
				SENSOR_HUB_SYNC,
				min < 0);
		अन्यथा अणु
			*val = 0;
			hid_sensor_घातer_state(
				&magn_state->magn_flux_attributes,
				false);
			वापस -EINVAL;
		पूर्ण
		hid_sensor_घातer_state(&magn_state->magn_flux_attributes,
					false);
		ret_type = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_MAGN:
			*val = magn_state->magn_flux_attr.scale_pre_decml;
			*val2 = magn_state->magn_flux_attr.scale_post_decml;
			ret_type = magn_state->magn_flux_attr.scale_precision;
			अवरोध;
		हाल IIO_ROT:
			*val = magn_state->rot_attr.scale_pre_decml;
			*val2 = magn_state->rot_attr.scale_post_decml;
			ret_type = magn_state->rot_attr.scale_precision;
			अवरोध;
		शेष:
			ret_type = -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		चयन (chan->type) अणु
		हाल IIO_MAGN:
			*val = magn_state->magn_flux_attr.value_offset;
			ret_type = IIO_VAL_INT;
			अवरोध;
		हाल IIO_ROT:
			*val = magn_state->rot_attr.value_offset;
			ret_type = IIO_VAL_INT;
			अवरोध;
		शेष:
			ret_type = -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret_type = hid_sensor_पढ़ो_samp_freq_value(
			&magn_state->magn_flux_attributes, val, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_HYSTERESIS:
		चयन (chan->type) अणु
		हाल IIO_MAGN:
			ret_type = hid_sensor_पढ़ो_raw_hyst_value(
				&magn_state->magn_flux_attributes, val, val2);
			अवरोध;
		हाल IIO_ROT:
			ret_type = hid_sensor_पढ़ो_raw_hyst_value(
				&magn_state->rot_attributes, val, val2);
			अवरोध;
		शेष:
			ret_type = -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		ret_type = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret_type;
पूर्ण

/* Channel ग_लिखो_raw handler */
अटल पूर्णांक magn_3d_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा magn_3d_state *magn_state = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = hid_sensor_ग_लिखो_samp_freq_value(
				&magn_state->magn_flux_attributes, val, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_HYSTERESIS:
		चयन (chan->type) अणु
		हाल IIO_MAGN:
			ret = hid_sensor_ग_लिखो_raw_hyst_value(
				&magn_state->magn_flux_attributes, val, val2);
			अवरोध;
		हाल IIO_ROT:
			ret = hid_sensor_ग_लिखो_raw_hyst_value(
				&magn_state->rot_attributes, val, val2);
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info magn_3d_info = अणु
	.पढ़ो_raw = &magn_3d_पढ़ो_raw,
	.ग_लिखो_raw = &magn_3d_ग_लिखो_raw,
पूर्ण;

/* Callback handler to send event after all samples are received and captured */
अटल पूर्णांक magn_3d_proc_event(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित usage_id,
				व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(priv);
	काष्ठा magn_3d_state *magn_state = iio_priv(indio_dev);

	dev_dbg(&indio_dev->dev, "magn_3d_proc_event\n");
	अगर (atomic_पढ़ो(&magn_state->magn_flux_attributes.data_पढ़ोy)) अणु
		अगर (!magn_state->बारtamp)
			magn_state->बारtamp = iio_get_समय_ns(indio_dev);

		iio_push_to_buffers_with_बारtamp(indio_dev,
						   magn_state->iio_vals,
						   magn_state->बारtamp);
		magn_state->बारtamp = 0;
	पूर्ण

	वापस 0;
पूर्ण

/* Capture samples in local storage */
अटल पूर्णांक magn_3d_capture_sample(काष्ठा hid_sensor_hub_device *hsdev,
				अचिन्हित usage_id,
				माप_प्रकार raw_len, अक्षर *raw_data,
				व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(priv);
	काष्ठा magn_3d_state *magn_state = iio_priv(indio_dev);
	पूर्णांक offset;
	पूर्णांक ret = 0;
	u32 *iio_val = शून्य;

	चयन (usage_id) अणु
	हाल HID_USAGE_SENSOR_ORIENT_MAGN_FLUX_X_AXIS:
	हाल HID_USAGE_SENSOR_ORIENT_MAGN_FLUX_Y_AXIS:
	हाल HID_USAGE_SENSOR_ORIENT_MAGN_FLUX_Z_AXIS:
		offset = (usage_id - HID_USAGE_SENSOR_ORIENT_MAGN_FLUX_X_AXIS)
				+ CHANNEL_SCAN_INDEX_X;
	अवरोध;
	हाल HID_USAGE_SENSOR_ORIENT_COMP_MAGN_NORTH:
	हाल HID_USAGE_SENSOR_ORIENT_COMP_TRUE_NORTH:
	हाल HID_USAGE_SENSOR_ORIENT_MAGN_NORTH:
	हाल HID_USAGE_SENSOR_ORIENT_TRUE_NORTH:
		offset = (usage_id - HID_USAGE_SENSOR_ORIENT_COMP_MAGN_NORTH)
				+ CHANNEL_SCAN_INDEX_NORTH_MAGN_TILT_COMP;
	अवरोध;
	हाल HID_USAGE_SENSOR_TIME_TIMESTAMP:
		magn_state->बारtamp =
			hid_sensor_convert_बारtamp(&magn_state->magn_flux_attributes,
						     *(s64 *)raw_data);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण

	iio_val = magn_state->magn_val_addr[offset];

	अगर (iio_val != शून्य)
		*iio_val = *((u32 *)raw_data);
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

/* Parse report which is specअगरic to an usage id*/
अटल पूर्णांक magn_3d_parse_report(काष्ठा platक्रमm_device *pdev,
				काष्ठा hid_sensor_hub_device *hsdev,
				काष्ठा iio_chan_spec **channels,
				पूर्णांक *chan_count,
				अचिन्हित usage_id,
				काष्ठा magn_3d_state *st)
अणु
	पूर्णांक i;
	पूर्णांक attr_count = 0;
	काष्ठा iio_chan_spec *_channels;

	/* Scan क्रम each usage attribute supported */
	क्रम (i = 0; i < MAGN_3D_CHANNEL_MAX; i++) अणु
		पूर्णांक status;
		u32 address = magn_3d_addresses[i];

		/* Check अगर usage attribute exists in the sensor hub device */
		status = sensor_hub_input_get_attribute_info(hsdev,
			HID_INPUT_REPORT,
			usage_id,
			address,
			&(st->magn[i]));
		अगर (!status)
			attr_count++;
	पूर्ण

	अगर (attr_count <= 0) अणु
		dev_err(&pdev->dev,
			"failed to find any supported usage attributes in report\n");
		वापस  -EINVAL;
	पूर्ण

	dev_dbg(&pdev->dev, "magn_3d Found %d usage attributes\n",
			attr_count);
	dev_dbg(&pdev->dev, "magn_3d X: %x:%x Y: %x:%x Z: %x:%x\n",
			st->magn[0].index,
			st->magn[0].report_id,
			st->magn[1].index, st->magn[1].report_id,
			st->magn[2].index, st->magn[2].report_id);

	/* Setup IIO channel array */
	_channels = devm_kसुस्मृति(&pdev->dev, attr_count,
				माप(काष्ठा iio_chan_spec),
				GFP_KERNEL);
	अगर (!_channels) अणु
		dev_err(&pdev->dev,
			"failed to allocate space for iio channels\n");
		वापस -ENOMEM;
	पूर्ण

	/* attr_count include बारtamp channel, and the iio_vals should be aligned to 8byte */
	st->iio_vals = devm_kसुस्मृति(&pdev->dev,
				    ((attr_count + 1) % 2 + (attr_count + 1) / 2) * 2,
				    माप(u32), GFP_KERNEL);
	अगर (!st->iio_vals) अणु
		dev_err(&pdev->dev,
			"failed to allocate space for iio values array\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0, *chan_count = 0;
	i < MAGN_3D_CHANNEL_MAX && *chan_count < attr_count;
	i++)अणु
		अगर (st->magn[i].index >= 0) अणु
			/* Setup IIO channel काष्ठा */
			(_channels[*chan_count]) = magn_3d_channels[i];
			(_channels[*chan_count]).scan_index = *chan_count;
			(_channels[*chan_count]).address = i;

			अगर (i != CHANNEL_SCAN_INDEX_TIMESTAMP) अणु
				/* Set magn_val_addr to iio value address */
				st->magn_val_addr[i] = &st->iio_vals[*chan_count];
				magn_3d_adjust_channel_bit_mask(_channels,
								*chan_count,
								st->magn[i].size);
			पूर्ण
			(*chan_count)++;
		पूर्ण
	पूर्ण

	अगर (*chan_count <= 0) अणु
		dev_err(&pdev->dev,
			"failed to find any magnetic channels setup\n");
		वापस -EINVAL;
	पूर्ण

	*channels = _channels;

	dev_dbg(&pdev->dev, "magn_3d Setup %d IIO channels\n",
			*chan_count);

	st->magn_flux_attr.scale_precision = hid_sensor_क्रमmat_scale(
				HID_USAGE_SENSOR_COMPASS_3D,
				&st->magn[CHANNEL_SCAN_INDEX_X],
				&st->magn_flux_attr.scale_pre_decml,
				&st->magn_flux_attr.scale_post_decml);
	st->rot_attr.scale_precision
		= hid_sensor_क्रमmat_scale(
			HID_USAGE_SENSOR_ORIENT_COMP_MAGN_NORTH,
			&st->magn[CHANNEL_SCAN_INDEX_NORTH_MAGN_TILT_COMP],
			&st->rot_attr.scale_pre_decml,
			&st->rot_attr.scale_post_decml);

	अगर (st->rot_attributes.sensitivity.index < 0) अणु
		sensor_hub_input_get_attribute_info(hsdev,
			HID_FEATURE_REPORT, usage_id,
			HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_ABS |
			HID_USAGE_SENSOR_ORIENT_COMP_MAGN_NORTH,
			&st->rot_attributes.sensitivity);
		dev_dbg(&pdev->dev, "Sensitivity index:report %d:%d\n",
			st->rot_attributes.sensitivity.index,
			st->rot_attributes.sensitivity.report_id);
	पूर्ण

	वापस 0;
पूर्ण

/* Function to initialize the processing क्रम usage id */
अटल पूर्णांक hid_magn_3d_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	अटल अक्षर *name = "magn_3d";
	काष्ठा iio_dev *indio_dev;
	काष्ठा magn_3d_state *magn_state;
	काष्ठा hid_sensor_hub_device *hsdev = pdev->dev.platक्रमm_data;
	काष्ठा iio_chan_spec *channels;
	पूर्णांक chan_count = 0;

	indio_dev = devm_iio_device_alloc(&pdev->dev,
					  माप(काष्ठा magn_3d_state));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, indio_dev);

	magn_state = iio_priv(indio_dev);
	magn_state->magn_flux_attributes.hsdev = hsdev;
	magn_state->magn_flux_attributes.pdev = pdev;

	ret = hid_sensor_parse_common_attributes(hsdev,
				HID_USAGE_SENSOR_COMPASS_3D,
				&magn_state->magn_flux_attributes,
				magn_3d_sensitivity_addresses,
				ARRAY_SIZE(magn_3d_sensitivity_addresses));
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to setup common attributes\n");
		वापस ret;
	पूर्ण
	magn_state->rot_attributes = magn_state->magn_flux_attributes;
	/* sensitivity of rot_attribute is not the same as magn_flux_attributes */
	magn_state->rot_attributes.sensitivity.index = -1;

	ret = magn_3d_parse_report(pdev, hsdev,
				&channels, &chan_count,
				HID_USAGE_SENSOR_COMPASS_3D, magn_state);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to parse report\n");
		वापस ret;
	पूर्ण

	indio_dev->channels = channels;
	indio_dev->num_channels = chan_count;
	indio_dev->info = &magn_3d_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	atomic_set(&magn_state->magn_flux_attributes.data_पढ़ोy, 0);

	ret = hid_sensor_setup_trigger(indio_dev, name,
					&magn_state->magn_flux_attributes);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "trigger setup failed\n");
		वापस ret;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "device register failed\n");
		जाओ error_हटाओ_trigger;
	पूर्ण

	magn_state->callbacks.send_event = magn_3d_proc_event;
	magn_state->callbacks.capture_sample = magn_3d_capture_sample;
	magn_state->callbacks.pdev = pdev;
	ret = sensor_hub_रेजिस्टर_callback(hsdev, HID_USAGE_SENSOR_COMPASS_3D,
					&magn_state->callbacks);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "callback reg failed\n");
		जाओ error_iio_unreg;
	पूर्ण

	वापस ret;

error_iio_unreg:
	iio_device_unरेजिस्टर(indio_dev);
error_हटाओ_trigger:
	hid_sensor_हटाओ_trigger(indio_dev, &magn_state->magn_flux_attributes);
	वापस ret;
पूर्ण

/* Function to deinitialize the processing क्रम usage id */
अटल पूर्णांक hid_magn_3d_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hid_sensor_hub_device *hsdev = pdev->dev.platक्रमm_data;
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा magn_3d_state *magn_state = iio_priv(indio_dev);

	sensor_hub_हटाओ_callback(hsdev, HID_USAGE_SENSOR_COMPASS_3D);
	iio_device_unरेजिस्टर(indio_dev);
	hid_sensor_हटाओ_trigger(indio_dev, &magn_state->magn_flux_attributes);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id hid_magn_3d_ids[] = अणु
	अणु
		/* Format: HID-SENSOR-usage_id_in_hex_lowerहाल */
		.name = "HID-SENSOR-200083",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, hid_magn_3d_ids);

अटल काष्ठा platक्रमm_driver hid_magn_3d_platक्रमm_driver = अणु
	.id_table = hid_magn_3d_ids,
	.driver = अणु
		.name	= KBUILD_MODNAME,
		.pm	= &hid_sensor_pm_ops,
	पूर्ण,
	.probe		= hid_magn_3d_probe,
	.हटाओ		= hid_magn_3d_हटाओ,
पूर्ण;
module_platक्रमm_driver(hid_magn_3d_platक्रमm_driver);

MODULE_DESCRIPTION("HID Sensor Magnetometer 3D");
MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@intel.com>");
MODULE_LICENSE("GPL");
