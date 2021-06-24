<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cros_ec_sensors_core - Common function क्रम Chrome OS EC sensor driver.
 *
 * Copyright (C) 2016 Google, Inc
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/common/cros_ec_sensors_core.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_data/cros_ec_sensorhub.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * Hard coded to the first device to support sensor fअगरo.  The EC has a 2048
 * byte fअगरo and will trigger an पूर्णांकerrupt when fअगरo is 2/3 full.
 */
#घोषणा CROS_EC_FIFO_SIZE (2048 * 2 / 3)

अटल अक्षर *cros_ec_loc[] = अणु
	[MOTIONSENSE_LOC_BASE] = "base",
	[MOTIONSENSE_LOC_LID] = "lid",
	[MOTIONSENSE_LOC_MAX] = "unknown",
पूर्ण;

अटल पूर्णांक cros_ec_get_host_cmd_version_mask(काष्ठा cros_ec_device *ec_dev,
					     u16 cmd_offset, u16 cmd, u32 *mask)
अणु
	पूर्णांक ret;
	काष्ठा अणु
		काष्ठा cros_ec_command msg;
		जोड़ अणु
			काष्ठा ec_params_get_cmd_versions params;
			काष्ठा ec_response_get_cmd_versions resp;
		पूर्ण;
	पूर्ण __packed buf = अणु
		.msg = अणु
			.command = EC_CMD_GET_CMD_VERSIONS + cmd_offset,
			.insize = माप(काष्ठा ec_response_get_cmd_versions),
			.outsize = माप(काष्ठा ec_params_get_cmd_versions)
			पूर्ण,
		.params = अणु.cmd = cmdपूर्ण
	पूर्ण;

	ret = cros_ec_cmd_xfer_status(ec_dev, &buf.msg);
	अगर (ret >= 0)
		*mask = buf.resp.version_mask;
	वापस ret;
पूर्ण

अटल व्योम get_शेष_min_max_freq(क्रमागत motionsensor_type type,
				     u32 *min_freq,
				     u32 *max_freq,
				     u32 *max_fअगरo_events)
अणु
	/*
	 * We करोn't know fअगरo size, set to size previously used by older
	 * hardware.
	 */
	*max_fअगरo_events = CROS_EC_FIFO_SIZE;

	चयन (type) अणु
	हाल MOTIONSENSE_TYPE_ACCEL:
		*min_freq = 12500;
		*max_freq = 100000;
		अवरोध;
	हाल MOTIONSENSE_TYPE_GYRO:
		*min_freq = 25000;
		*max_freq = 100000;
		अवरोध;
	हाल MOTIONSENSE_TYPE_MAG:
		*min_freq = 5000;
		*max_freq = 25000;
		अवरोध;
	हाल MOTIONSENSE_TYPE_PROX:
	हाल MOTIONSENSE_TYPE_LIGHT:
		*min_freq = 100;
		*max_freq = 50000;
		अवरोध;
	हाल MOTIONSENSE_TYPE_BARO:
		*min_freq = 250;
		*max_freq = 20000;
		अवरोध;
	हाल MOTIONSENSE_TYPE_ACTIVITY:
	शेष:
		*min_freq = 0;
		*max_freq = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक cros_ec_sensor_set_ec_rate(काष्ठा cros_ec_sensors_core_state *st,
				      पूर्णांक rate)
अणु
	पूर्णांक ret;

	अगर (rate > U16_MAX)
		rate = U16_MAX;

	mutex_lock(&st->cmd_lock);
	st->param.cmd = MOTIONSENSE_CMD_EC_RATE;
	st->param.ec_rate.data = rate;
	ret = cros_ec_motion_send_host_cmd(st, 0);
	mutex_unlock(&st->cmd_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार cros_ec_sensor_set_report_latency(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	पूर्णांक पूर्णांकeger, fract, ret;
	पूर्णांक latency;

	ret = iio_str_to_fixpoपूर्णांक(buf, 100000, &पूर्णांकeger, &fract);
	अगर (ret)
		वापस ret;

	/* EC rate is in ms. */
	latency = पूर्णांकeger * 1000 + fract / 1000;
	ret = cros_ec_sensor_set_ec_rate(st, latency);
	अगर (ret < 0)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार cros_ec_sensor_get_report_latency(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	पूर्णांक latency, ret;

	mutex_lock(&st->cmd_lock);
	st->param.cmd = MOTIONSENSE_CMD_EC_RATE;
	st->param.ec_rate.data = EC_MOTION_SENSE_NO_VALUE;

	ret = cros_ec_motion_send_host_cmd(st, 0);
	latency = st->resp->ec_rate.ret;
	mutex_unlock(&st->cmd_lock);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d.%06u\n",
		       latency / 1000,
		       (latency % 1000) * 1000);
पूर्ण

अटल IIO_DEVICE_ATTR(hwfअगरo_समयout, 0644,
		       cros_ec_sensor_get_report_latency,
		       cros_ec_sensor_set_report_latency, 0);

अटल sमाप_प्रकार hwfअगरo_watermark_max_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);

	वापस प्र_लिखो(buf, "%d\n", st->fअगरo_max_event_count);
पूर्ण

अटल IIO_DEVICE_ATTR_RO(hwfअगरo_watermark_max, 0);

अटल स्थिर काष्ठा attribute *cros_ec_sensor_fअगरo_attributes[] = अणु
	&iio_dev_attr_hwfअगरo_समयout.dev_attr.attr,
	&iio_dev_attr_hwfअगरo_watermark_max.dev_attr.attr,
	शून्य,
पूर्ण;

पूर्णांक cros_ec_sensors_push_data(काष्ठा iio_dev *indio_dev,
			      s16 *data,
			      s64 बारtamp)
अणु
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	s16 *out;
	s64 delta;
	अचिन्हित पूर्णांक i;

	/*
	 * Ignore samples अगर the buffer is not set: it is needed अगर the ODR is
	 * set but the buffer is not enabled yet.
	 */
	अगर (!iio_buffer_enabled(indio_dev))
		वापस 0;

	out = (s16 *)st->samples;
	क्रम_each_set_bit(i,
			 indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		*out = data[i];
		out++;
	पूर्ण

	अगर (iio_device_get_घड़ी(indio_dev) != CLOCK_BOOTTIME)
		delta = iio_get_समय_ns(indio_dev) - cros_ec_get_समय_ns();
	अन्यथा
		delta = 0;

	iio_push_to_buffers_with_बारtamp(indio_dev, st->samples,
					   बारtamp + delta);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cros_ec_sensors_push_data);

अटल व्योम cros_ec_sensors_core_clean(व्योम *arg)
अणु
	काष्ठा platक्रमm_device *pdev = (काष्ठा platक्रमm_device *)arg;
	काष्ठा cros_ec_sensorhub *sensor_hub =
		dev_get_drvdata(pdev->dev.parent);
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	u8 sensor_num = st->param.info.sensor_num;

	cros_ec_sensorhub_unरेजिस्टर_push_data(sensor_hub, sensor_num);
पूर्ण

/**
 * cros_ec_sensors_core_init() - basic initialization of the core काष्ठाure
 * @pdev:		platक्रमm device created क्रम the sensors
 * @indio_dev:		iio device काष्ठाure of the device
 * @physical_device:	true अगर the device refers to a physical device
 * @trigger_capture:    function poपूर्णांकer to call buffer is triggered,
 *    क्रम backward compatibility.
 * @push_data:          function to call when cros_ec_sensorhub receives
 *    a sample क्रम that sensor.
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक cros_ec_sensors_core_init(काष्ठा platक्रमm_device *pdev,
			      काष्ठा iio_dev *indio_dev,
			      bool physical_device,
			      cros_ec_sensors_capture_t trigger_capture,
			      cros_ec_sensorhub_push_data_cb_t push_data)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cros_ec_sensors_core_state *state = iio_priv(indio_dev);
	काष्ठा cros_ec_sensorhub *sensor_hub = dev_get_drvdata(dev->parent);
	काष्ठा cros_ec_dev *ec = sensor_hub->ec;
	काष्ठा cros_ec_sensor_platक्रमm *sensor_platक्रमm = dev_get_platdata(dev);
	u32 ver_mask, temp;
	पूर्णांक frequencies[ARRAY_SIZE(state->frequencies) / 2] = अणु 0 पूर्ण;
	पूर्णांक ret, i;

	platक्रमm_set_drvdata(pdev, indio_dev);

	state->ec = ec->ec_dev;
	state->msg = devm_kzalloc(&pdev->dev,
				max((u16)माप(काष्ठा ec_params_motion_sense),
				state->ec->max_response), GFP_KERNEL);
	अगर (!state->msg)
		वापस -ENOMEM;

	state->resp = (काष्ठा ec_response_motion_sense *)state->msg->data;

	mutex_init(&state->cmd_lock);

	ret = cros_ec_get_host_cmd_version_mask(state->ec,
						ec->cmd_offset,
						EC_CMD_MOTION_SENSE_CMD,
						&ver_mask);
	अगर (ret < 0)
		वापस ret;

	/* Set up the host command काष्ठाure. */
	state->msg->version = fls(ver_mask) - 1;
	state->msg->command = EC_CMD_MOTION_SENSE_CMD + ec->cmd_offset;
	state->msg->outsize = माप(काष्ठा ec_params_motion_sense);

	indio_dev->name = pdev->name;

	अगर (physical_device) अणु
		state->param.cmd = MOTIONSENSE_CMD_INFO;
		state->param.info.sensor_num = sensor_platक्रमm->sensor_num;
		ret = cros_ec_motion_send_host_cmd(state, 0);
		अगर (ret) अणु
			dev_warn(dev, "Can not access sensor info\n");
			वापस ret;
		पूर्ण
		state->type = state->resp->info.type;
		state->loc = state->resp->info.location;

		/* Set sign vector, only used क्रम backward compatibility. */
		स_रखो(state->sign, 1, CROS_EC_SENSOR_MAX_AXIS);

		क्रम (i = CROS_EC_SENSOR_X; i < CROS_EC_SENSOR_MAX_AXIS; i++)
			state->calib[i].scale = MOTION_SENSE_DEFAULT_SCALE;

		/* 0 is a correct value used to stop the device */
		अगर (state->msg->version < 3) अणु
			get_शेष_min_max_freq(state->resp->info.type,
						 &frequencies[1],
						 &frequencies[2],
						 &state->fअगरo_max_event_count);
		पूर्ण अन्यथा अणु
			अगर (state->resp->info_3.max_frequency == 0) अणु
				get_शेष_min_max_freq(state->resp->info.type,
							 &frequencies[1],
							 &frequencies[2],
							 &temp);
			पूर्ण अन्यथा अणु
				frequencies[1] = state->resp->info_3.min_frequency;
				frequencies[2] = state->resp->info_3.max_frequency;
			पूर्ण
			state->fअगरo_max_event_count = state->resp->info_3.fअगरo_max_event_count;
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(frequencies); i++) अणु
			state->frequencies[2 * i] = frequencies[i] / 1000;
			state->frequencies[2 * i + 1] =
				(frequencies[i] % 1000) * 1000;
		पूर्ण

		अगर (cros_ec_check_features(ec, EC_FEATURE_MOTION_SENSE_FIFO)) अणु
			/*
			 * Create a software buffer, feed by the EC FIFO.
			 * We can not use trigger here, as events are generated
			 * as soon as sample_frequency is set.
			 */
			ret = devm_iio_kfअगरo_buffer_setup_ext(dev, indio_dev,
							      INDIO_BUFFER_SOFTWARE, शून्य,
							      cros_ec_sensor_fअगरo_attributes);
			अगर (ret)
				वापस ret;

			ret = cros_ec_sensorhub_रेजिस्टर_push_data(
					sensor_hub, sensor_platक्रमm->sensor_num,
					indio_dev, push_data);
			अगर (ret)
				वापस ret;

			ret = devm_add_action_or_reset(
					dev, cros_ec_sensors_core_clean, pdev);
			अगर (ret)
				वापस ret;

			/* Timestamp coming from FIFO are in ns since boot. */
			ret = iio_device_set_घड़ी(indio_dev, CLOCK_BOOTTIME);
			अगर (ret)
				वापस ret;

		पूर्ण अन्यथा अणु
			/*
			 * The only way to get samples in buffer is to set a
			 * software trigger (systrig, hrसमयr).
			 */
			ret = devm_iio_triggered_buffer_setup(dev, indio_dev,
					शून्य, trigger_capture, शून्य);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cros_ec_sensors_core_init);

/**
 * cros_ec_motion_send_host_cmd() - send motion sense host command
 * @state:		poपूर्णांकer to state inक्रमmation क्रम device
 * @opt_length:	optional length to reduce the response size, useful on the data
 *		path. Otherwise, the maximal allowed response size is used
 *
 * When called, the sub-command is assumed to be set in param->cmd.
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक cros_ec_motion_send_host_cmd(काष्ठा cros_ec_sensors_core_state *state,
				 u16 opt_length)
अणु
	पूर्णांक ret;

	अगर (opt_length)
		state->msg->insize = min(opt_length, state->ec->max_response);
	अन्यथा
		state->msg->insize = state->ec->max_response;

	स_नकल(state->msg->data, &state->param, माप(state->param));

	ret = cros_ec_cmd_xfer_status(state->ec, state->msg);
	अगर (ret < 0)
		वापस ret;

	अगर (ret &&
	    state->resp != (काष्ठा ec_response_motion_sense *)state->msg->data)
		स_नकल(state->resp, state->msg->data, ret);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cros_ec_motion_send_host_cmd);

अटल sमाप_प्रकार cros_ec_sensors_calibrate(काष्ठा iio_dev *indio_dev,
		uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan,
		स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	पूर्णांक ret, i;
	bool calibrate;

	ret = strtobool(buf, &calibrate);
	अगर (ret < 0)
		वापस ret;
	अगर (!calibrate)
		वापस -EINVAL;

	mutex_lock(&st->cmd_lock);
	st->param.cmd = MOTIONSENSE_CMD_PERFORM_CALIB;
	ret = cros_ec_motion_send_host_cmd(st, 0);
	अगर (ret != 0) अणु
		dev_warn(&indio_dev->dev, "Unable to calibrate sensor\n");
	पूर्ण अन्यथा अणु
		/* Save values */
		क्रम (i = CROS_EC_SENSOR_X; i < CROS_EC_SENSOR_MAX_AXIS; i++)
			st->calib[i].offset = st->resp->perक्रमm_calib.offset[i];
	पूर्ण
	mutex_unlock(&st->cmd_lock);

	वापस ret ? ret : len;
पूर्ण

अटल sमाप_प्रकार cros_ec_sensors_id(काष्ठा iio_dev *indio_dev,
				  uपूर्णांकptr_t निजी,
				  स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf)
अणु
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", st->param.info.sensor_num);
पूर्ण

अटल sमाप_प्रकार cros_ec_sensors_loc(काष्ठा iio_dev *indio_dev,
		uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan,
		अक्षर *buf)
अणु
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", cros_ec_loc[st->loc]);
पूर्ण

स्थिर काष्ठा iio_chan_spec_ext_info cros_ec_sensors_ext_info[] = अणु
	अणु
		.name = "calibrate",
		.shared = IIO_SHARED_BY_ALL,
		.ग_लिखो = cros_ec_sensors_calibrate
	पूर्ण,
	अणु
		.name = "id",
		.shared = IIO_SHARED_BY_ALL,
		.पढ़ो = cros_ec_sensors_id
	पूर्ण,
	अणु
		.name = "location",
		.shared = IIO_SHARED_BY_ALL,
		.पढ़ो = cros_ec_sensors_loc
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(cros_ec_sensors_ext_info);

/**
 * cros_ec_sensors_idx_to_reg - convert index पूर्णांकo offset in shared memory
 * @st:		poपूर्णांकer to state inक्रमmation क्रम device
 * @idx:	sensor index (should be element of क्रमागत sensor_index)
 *
 * Return:	address to पढ़ो at
 */
अटल अचिन्हित पूर्णांक cros_ec_sensors_idx_to_reg(
					काष्ठा cros_ec_sensors_core_state *st,
					अचिन्हित पूर्णांक idx)
अणु
	/*
	 * When using LPC पूर्णांकerface, only space क्रम 2 Accel and one Gyro.
	 * First halfword of MOTIONSENSE_TYPE_ACCEL is used by angle.
	 */
	अगर (st->type == MOTIONSENSE_TYPE_ACCEL)
		वापस EC_MEMMAP_ACC_DATA + माप(u16) *
			(1 + idx + st->param.info.sensor_num *
			 CROS_EC_SENSOR_MAX_AXIS);

	वापस EC_MEMMAP_GYRO_DATA + माप(u16) * idx;
पूर्ण

अटल पूर्णांक cros_ec_sensors_cmd_पढ़ो_u8(काष्ठा cros_ec_device *ec,
				       अचिन्हित पूर्णांक offset, u8 *dest)
अणु
	वापस ec->cmd_पढ़ोmem(ec, offset, 1, dest);
पूर्ण

अटल पूर्णांक cros_ec_sensors_cmd_पढ़ो_u16(काष्ठा cros_ec_device *ec,
					 अचिन्हित पूर्णांक offset, u16 *dest)
अणु
	__le16 पंचांगp;
	पूर्णांक ret = ec->cmd_पढ़ोmem(ec, offset, 2, &पंचांगp);

	अगर (ret >= 0)
		*dest = le16_to_cpu(पंचांगp);

	वापस ret;
पूर्ण

/**
 * cros_ec_sensors_पढ़ो_until_not_busy() - पढ़ो until is not busy
 *
 * @st:	poपूर्णांकer to state inक्रमmation क्रम device
 *
 * Read from EC status byte until it पढ़ोs not busy.
 * Return: 8-bit status अगर ok, -त्रुटि_सं on failure.
 */
अटल पूर्णांक cros_ec_sensors_पढ़ो_until_not_busy(
					काष्ठा cros_ec_sensors_core_state *st)
अणु
	काष्ठा cros_ec_device *ec = st->ec;
	u8 status;
	पूर्णांक ret, attempts = 0;

	ret = cros_ec_sensors_cmd_पढ़ो_u8(ec, EC_MEMMAP_ACC_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	जबतक (status & EC_MEMMAP_ACC_STATUS_BUSY_BIT) अणु
		/* Give up after enough attempts, वापस error. */
		अगर (attempts++ >= 50)
			वापस -EIO;

		/* Small delay every so often. */
		अगर (attempts % 5 == 0)
			msleep(25);

		ret = cros_ec_sensors_cmd_पढ़ो_u8(ec, EC_MEMMAP_ACC_STATUS,
						  &status);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस status;
पूर्ण

/**
 * cros_ec_sensors_पढ़ो_data_unsafe() - पढ़ो acceleration data from EC shared memory
 * @indio_dev:	poपूर्णांकer to IIO device
 * @scan_mask:	biपंचांगap of the sensor indices to scan
 * @data:	location to store data
 *
 * This is the unsafe function क्रम पढ़ोing the EC data. It करोes not guarantee
 * that the EC will not modअगरy the data as it is being पढ़ो in.
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक cros_ec_sensors_पढ़ो_data_unsafe(काष्ठा iio_dev *indio_dev,
			 अचिन्हित दीर्घ scan_mask, s16 *data)
अणु
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	काष्ठा cros_ec_device *ec = st->ec;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Read all sensors enabled in scan_mask. Each value is 2 bytes. */
	क्रम_each_set_bit(i, &scan_mask, indio_dev->masklength) अणु
		ret = cros_ec_sensors_cmd_पढ़ो_u16(ec,
					     cros_ec_sensors_idx_to_reg(st, i),
					     data);
		अगर (ret < 0)
			वापस ret;

		*data *= st->sign[i];
		data++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cros_ec_sensors_पढ़ो_lpc() - पढ़ो acceleration data from EC shared memory.
 * @indio_dev: poपूर्णांकer to IIO device.
 * @scan_mask: biपंचांगap of the sensor indices to scan.
 * @data: location to store data.
 *
 * Note: this is the safe function क्रम पढ़ोing the EC data. It guarantees
 * that the data sampled was not modअगरied by the EC जबतक being पढ़ो.
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक cros_ec_sensors_पढ़ो_lpc(काष्ठा iio_dev *indio_dev,
			     अचिन्हित दीर्घ scan_mask, s16 *data)
अणु
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	काष्ठा cros_ec_device *ec = st->ec;
	u8 samp_id = 0xff, status = 0;
	पूर्णांक ret, attempts = 0;

	/*
	 * Continually पढ़ो all data from EC until the status byte after
	 * all पढ़ोs reflects that the EC is not busy and the sample id
	 * matches the sample id from beक्रमe all पढ़ोs. This guarantees
	 * that data पढ़ो in was not modअगरied by the EC जबतक पढ़ोing.
	 */
	जबतक ((status & (EC_MEMMAP_ACC_STATUS_BUSY_BIT |
			  EC_MEMMAP_ACC_STATUS_SAMPLE_ID_MASK)) != samp_id) अणु
		/* If we have tried to पढ़ो too many बार, वापस error. */
		अगर (attempts++ >= 5)
			वापस -EIO;

		/* Read status byte until EC is not busy. */
		ret = cros_ec_sensors_पढ़ो_until_not_busy(st);
		अगर (ret < 0)
			वापस ret;

		/*
		 * Store the current sample id so that we can compare to the
		 * sample id after पढ़ोing the data.
		 */
		samp_id = ret & EC_MEMMAP_ACC_STATUS_SAMPLE_ID_MASK;

		/* Read all EC data, क्रमmat it, and store it पूर्णांकo data. */
		ret = cros_ec_sensors_पढ़ो_data_unsafe(indio_dev, scan_mask,
						       data);
		अगर (ret < 0)
			वापस ret;

		/* Read status byte. */
		ret = cros_ec_sensors_cmd_पढ़ो_u8(ec, EC_MEMMAP_ACC_STATUS,
						  &status);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cros_ec_sensors_पढ़ो_lpc);

/**
 * cros_ec_sensors_पढ़ो_cmd() - retrieve data using the EC command protocol
 * @indio_dev:	poपूर्णांकer to IIO device
 * @scan_mask:	biपंचांगap of the sensor indices to scan
 * @data:	location to store data
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक cros_ec_sensors_पढ़ो_cmd(काष्ठा iio_dev *indio_dev,
			     अचिन्हित दीर्घ scan_mask, s16 *data)
अणु
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;

	/* Read all sensor data through a command. */
	st->param.cmd = MOTIONSENSE_CMD_DATA;
	ret = cros_ec_motion_send_host_cmd(st, माप(st->resp->data));
	अगर (ret != 0) अणु
		dev_warn(&indio_dev->dev, "Unable to read sensor data\n");
		वापस ret;
	पूर्ण

	क्रम_each_set_bit(i, &scan_mask, indio_dev->masklength) अणु
		*data = st->resp->data.data[i];
		data++;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cros_ec_sensors_पढ़ो_cmd);

/**
 * cros_ec_sensors_capture() - the trigger handler function
 * @irq:	the पूर्णांकerrupt number.
 * @p:		a poपूर्णांकer to the poll function.
 *
 * On a trigger event occurring, अगर the pollfunc is attached then this
 * handler is called as a thपढ़ोed पूर्णांकerrupt (and hence may sleep). It
 * is responsible क्रम grabbing data from the device and pushing it पूर्णांकo
 * the associated buffer.
 *
 * Return: IRQ_HANDLED
 */
irqवापस_t cros_ec_sensors_capture(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->cmd_lock);

	/* Clear capture data. */
	स_रखो(st->samples, 0, indio_dev->scan_bytes);

	/* Read data based on which channels are enabled in scan mask. */
	ret = st->पढ़ो_ec_sensors_data(indio_dev,
				       *(indio_dev->active_scan_mask),
				       (s16 *)st->samples);
	अगर (ret < 0)
		जाओ करोne;

	iio_push_to_buffers_with_बारtamp(indio_dev, st->samples,
					   iio_get_समय_ns(indio_dev));

करोne:
	/*
	 * Tell the core we are करोne with this trigger and पढ़ोy क्रम the
	 * next one.
	 */
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	mutex_unlock(&st->cmd_lock);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL_GPL(cros_ec_sensors_capture);

/**
 * cros_ec_sensors_core_पढ़ो() - function to request a value from the sensor
 * @st:		poपूर्णांकer to state inक्रमmation क्रम device
 * @chan:	channel specअगरication काष्ठाure table
 * @val:	will contain one element making up the वापसed value
 * @val2:	will contain another element making up the वापसed value
 * @mask:	specअगरies which values to be requested
 *
 * Return:	the type of value वापसed by the device
 */
पूर्णांक cros_ec_sensors_core_पढ़ो(काष्ठा cros_ec_sensors_core_state *st,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret, frequency;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		st->param.cmd = MOTIONSENSE_CMD_SENSOR_ODR;
		st->param.sensor_odr.data =
			EC_MOTION_SENSE_NO_VALUE;

		ret = cros_ec_motion_send_host_cmd(st, 0);
		अगर (ret)
			अवरोध;

		frequency = st->resp->sensor_odr.ret;
		*val = frequency / 1000;
		*val2 = (frequency % 1000) * 1000;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cros_ec_sensors_core_पढ़ो);

/**
 * cros_ec_sensors_core_पढ़ो_avail() - get available values
 * @indio_dev:		poपूर्णांकer to state inक्रमmation क्रम device
 * @chan:	channel specअगरication काष्ठाure table
 * @vals:	list of available values
 * @type:	type of data वापसed
 * @length:	number of data वापसed in the array
 * @mask:	specअगरies which values to be requested
 *
 * Return:	an error code, IIO_AVAIL_RANGE or IIO_AVAIL_LIST
 */
पूर्णांक cros_ec_sensors_core_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
				    काष्ठा iio_chan_spec स्थिर *chan,
				    स्थिर पूर्णांक **vals,
				    पूर्णांक *type,
				    पूर्णांक *length,
				    दीर्घ mask)
अणु
	काष्ठा cros_ec_sensors_core_state *state = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*length = ARRAY_SIZE(state->frequencies);
		*vals = (स्थिर पूर्णांक *)&state->frequencies;
		*type = IIO_VAL_INT_PLUS_MICRO;
		वापस IIO_AVAIL_LIST;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(cros_ec_sensors_core_पढ़ो_avail);

/**
 * cros_ec_sensors_core_ग_लिखो() - function to ग_लिखो a value to the sensor
 * @st:		poपूर्णांकer to state inक्रमmation क्रम device
 * @chan:	channel specअगरication काष्ठाure table
 * @val:	first part of value to ग_लिखो
 * @val2:	second part of value to ग_लिखो
 * @mask:	specअगरies which values to ग_लिखो
 *
 * Return:	the type of value वापसed by the device
 */
पूर्णांक cros_ec_sensors_core_ग_लिखो(काष्ठा cros_ec_sensors_core_state *st,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक ret, frequency;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		frequency = val * 1000 + val2 / 1000;
		st->param.cmd = MOTIONSENSE_CMD_SENSOR_ODR;
		st->param.sensor_odr.data = frequency;

		/* Always roundup, so caller माला_लो at least what it asks क्रम. */
		st->param.sensor_odr.roundup = 1;

		ret = cros_ec_motion_send_host_cmd(st, 0);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cros_ec_sensors_core_ग_लिखो);

अटल पूर्णांक __maybe_unused cros_ec_sensors_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	अगर (st->range_updated) अणु
		mutex_lock(&st->cmd_lock);
		st->param.cmd = MOTIONSENSE_CMD_SENSOR_RANGE;
		st->param.sensor_range.data = st->curr_range;
		st->param.sensor_range.roundup = 1;
		ret = cros_ec_motion_send_host_cmd(st, 0);
		mutex_unlock(&st->cmd_lock);
	पूर्ण
	वापस ret;
पूर्ण

SIMPLE_DEV_PM_OPS(cros_ec_sensors_pm_ops, शून्य, cros_ec_sensors_resume);
EXPORT_SYMBOL_GPL(cros_ec_sensors_pm_ops);

MODULE_DESCRIPTION("ChromeOS EC sensor hub core functions");
MODULE_LICENSE("GPL v2");
