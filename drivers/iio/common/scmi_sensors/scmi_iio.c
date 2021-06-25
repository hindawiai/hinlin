<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * System Control and Management Interface(SCMI) based IIO sensor driver
 *
 * Copyright (C) 2021 Google LLC
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/scmi_protocol.h>
#समावेश <linux/समय.स>
#समावेश <linux/types.h>

#घोषणा SCMI_IIO_NUM_OF_AXIS 3

काष्ठा scmi_iio_priv अणु
	स्थिर काष्ठा scmi_sensor_proto_ops *sensor_ops;
	काष्ठा scmi_protocol_handle *ph;
	स्थिर काष्ठा scmi_sensor_info *sensor_info;
	काष्ठा iio_dev *indio_dev;
	/* adding one additional channel क्रम बारtamp */
	s64 iio_buf[SCMI_IIO_NUM_OF_AXIS + 1];
	काष्ठा notअगरier_block sensor_update_nb;
	u32 *freq_avail;
पूर्ण;

अटल पूर्णांक scmi_iio_sensor_update_cb(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा scmi_sensor_update_report *sensor_update = data;
	काष्ठा iio_dev *scmi_iio_dev;
	काष्ठा scmi_iio_priv *sensor;
	s8 tstamp_scale;
	u64 समय, समय_ns;
	पूर्णांक i;

	अगर (sensor_update->पढ़ोings_count == 0)
		वापस NOTIFY_DONE;

	sensor = container_of(nb, काष्ठा scmi_iio_priv, sensor_update_nb);

	क्रम (i = 0; i < sensor_update->पढ़ोings_count; i++)
		sensor->iio_buf[i] = sensor_update->पढ़ोings[i].value;

	अगर (!sensor->sensor_info->बारtamped) अणु
		समय_ns = kसमय_प्रकारo_ns(sensor_update->बारtamp);
	पूर्ण अन्यथा अणु
		/*
		 *  All the axes are supposed to have the same value क्रम बारtamp.
		 *  We are just using the values from the Axis 0 here.
		 */
		समय = sensor_update->पढ़ोings[0].बारtamp;

		/*
		 *  Timestamp वापसed by SCMI is in seconds and is equal to
		 *  समय * घातer-of-10 multiplier(tstamp_scale) seconds.
		 *  Converting the बारtamp to nanoseconds below.
		 */
		tstamp_scale = sensor->sensor_info->tstamp_scale +
			       स्थिर_ilog2(NSEC_PER_SEC) / स्थिर_ilog2(10);
		अगर (tstamp_scale < 0) अणु
			करो_भाग(समय, पूर्णांक_घात(10, असल(tstamp_scale)));
			समय_ns = समय;
		पूर्ण अन्यथा अणु
			समय_ns = समय * पूर्णांक_घात(10, tstamp_scale);
		पूर्ण
	पूर्ण

	scmi_iio_dev = sensor->indio_dev;
	iio_push_to_buffers_with_बारtamp(scmi_iio_dev, sensor->iio_buf,
					   समय_ns);
	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक scmi_iio_buffer_preenable(काष्ठा iio_dev *iio_dev)
अणु
	काष्ठा scmi_iio_priv *sensor = iio_priv(iio_dev);
	u32 sensor_config = 0;
	पूर्णांक err;

	अगर (sensor->sensor_info->बारtamped)
		sensor_config |= FIELD_PREP(SCMI_SENS_CFG_TSTAMP_ENABLED_MASK,
					    SCMI_SENS_CFG_TSTAMP_ENABLE);

	sensor_config |= FIELD_PREP(SCMI_SENS_CFG_SENSOR_ENABLED_MASK,
				    SCMI_SENS_CFG_SENSOR_ENABLE);
	err = sensor->sensor_ops->config_set(sensor->ph,
					     sensor->sensor_info->id,
					     sensor_config);
	अगर (err)
		dev_err(&iio_dev->dev, "Error in enabling sensor %s err %d",
			sensor->sensor_info->name, err);

	वापस err;
पूर्ण

अटल पूर्णांक scmi_iio_buffer_postdisable(काष्ठा iio_dev *iio_dev)
अणु
	काष्ठा scmi_iio_priv *sensor = iio_priv(iio_dev);
	u32 sensor_config = 0;
	पूर्णांक err;

	sensor_config |= FIELD_PREP(SCMI_SENS_CFG_SENSOR_ENABLED_MASK,
				    SCMI_SENS_CFG_SENSOR_DISABLE);
	err = sensor->sensor_ops->config_set(sensor->ph,
					     sensor->sensor_info->id,
					     sensor_config);
	अगर (err) अणु
		dev_err(&iio_dev->dev,
			"Error in disabling sensor %s with err %d",
			sensor->sensor_info->name, err);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops scmi_iio_buffer_ops = अणु
	.preenable = scmi_iio_buffer_preenable,
	.postdisable = scmi_iio_buffer_postdisable,
पूर्ण;

अटल पूर्णांक scmi_iio_set_odr_val(काष्ठा iio_dev *iio_dev, पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा scmi_iio_priv *sensor = iio_priv(iio_dev);
	स्थिर अचिन्हित दीर्घ UHZ_PER_HZ = 1000000UL;
	u64 sec, mult, uHz, sf;
	u32 sensor_config;
	अक्षर buf[32];

	पूर्णांक err = sensor->sensor_ops->config_get(sensor->ph,
						 sensor->sensor_info->id,
						 &sensor_config);
	अगर (err) अणु
		dev_err(&iio_dev->dev,
			"Error in getting sensor config for sensor %s err %d",
			sensor->sensor_info->name, err);
		वापस err;
	पूर्ण

	uHz = val * UHZ_PER_HZ + val2;

	/*
	 * The seconds field in the sensor पूर्णांकerval in SCMI is 16 bits दीर्घ
	 * Thereक्रमe seconds  = 1/Hz <= 0xFFFF. As भग्नing poपूर्णांक calculations are
	 * discouraged in the kernel driver code, to calculate the scale factor (sf)
	 * (1* 1000000 * sf)/uHz <= 0xFFFF. Thereक्रमe, sf <= (uHz * 0xFFFF)/1000000
	 * To calculate the multiplier,we convert the sf पूर्णांकo अक्षर string  and
	 * count the number of अक्षरacters
	 */
	sf = (u64)uHz * 0xFFFF;
	करो_भाग(sf,  UHZ_PER_HZ);
	mult = scnम_लिखो(buf, माप(buf), "%llu", sf) - 1;

	sec = पूर्णांक_घात(10, mult) * UHZ_PER_HZ;
	करो_भाग(sec, uHz);
	अगर (sec == 0) अणु
		dev_err(&iio_dev->dev,
			"Trying to set invalid sensor update value for sensor %s",
			sensor->sensor_info->name);
		वापस -EINVAL;
	पूर्ण

	sensor_config &= ~SCMI_SENS_CFG_UPDATE_SECS_MASK;
	sensor_config |= FIELD_PREP(SCMI_SENS_CFG_UPDATE_SECS_MASK, sec);
	sensor_config &= ~SCMI_SENS_CFG_UPDATE_EXP_MASK;
	sensor_config |= FIELD_PREP(SCMI_SENS_CFG_UPDATE_EXP_MASK, -mult);

	अगर (sensor->sensor_info->बारtamped) अणु
		sensor_config &= ~SCMI_SENS_CFG_TSTAMP_ENABLED_MASK;
		sensor_config |= FIELD_PREP(SCMI_SENS_CFG_TSTAMP_ENABLED_MASK,
					    SCMI_SENS_CFG_TSTAMP_ENABLE);
	पूर्ण

	sensor_config &= ~SCMI_SENS_CFG_ROUND_MASK;
	sensor_config |=
		FIELD_PREP(SCMI_SENS_CFG_ROUND_MASK, SCMI_SENS_CFG_ROUND_AUTO);

	err = sensor->sensor_ops->config_set(sensor->ph,
					     sensor->sensor_info->id,
					     sensor_config);
	अगर (err)
		dev_err(&iio_dev->dev,
			"Error in setting sensor update interval for sensor %s value %u err %d",
			sensor->sensor_info->name, sensor_config, err);

	वापस err;
पूर्ण

अटल पूर्णांक scmi_iio_ग_लिखो_raw(काष्ठा iio_dev *iio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
			      पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक err;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&iio_dev->mlock);
		err = scmi_iio_set_odr_val(iio_dev, val, val2);
		mutex_unlock(&iio_dev->mlock);
		वापस err;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक scmi_iio_पढ़ो_avail(काष्ठा iio_dev *iio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			       दीर्घ mask)
अणु
	काष्ठा scmi_iio_priv *sensor = iio_priv(iio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*vals = sensor->freq_avail;
		*type = IIO_VAL_INT_PLUS_MICRO;
		*length = sensor->sensor_info->पूर्णांकervals.count * 2;
		अगर (sensor->sensor_info->पूर्णांकervals.segmented)
			वापस IIO_AVAIL_RANGE;
		अन्यथा
			वापस IIO_AVAIL_LIST;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम convert_ns_to_freq(u64 पूर्णांकerval_ns, u64 *hz, u64 *uhz)
अणु
	u64 rem, freq;

	freq = NSEC_PER_SEC;
	rem = करो_भाग(freq, पूर्णांकerval_ns);
	*hz = freq;
	*uhz = rem * 1000000UL;
	करो_भाग(*uhz, पूर्णांकerval_ns);
पूर्ण

अटल पूर्णांक scmi_iio_get_odr_val(काष्ठा iio_dev *iio_dev, पूर्णांक *val, पूर्णांक *val2)
अणु
	u64 sensor_update_पूर्णांकerval, sensor_पूर्णांकerval_mult, hz, uhz;
	काष्ठा scmi_iio_priv *sensor = iio_priv(iio_dev);
	u32 sensor_config;
	पूर्णांक mult;

	पूर्णांक err = sensor->sensor_ops->config_get(sensor->ph,
						 sensor->sensor_info->id,
						 &sensor_config);
	अगर (err) अणु
		dev_err(&iio_dev->dev,
			"Error in getting sensor config for sensor %s err %d",
			sensor->sensor_info->name, err);
		वापस err;
	पूर्ण

	sensor_update_पूर्णांकerval =
		SCMI_SENS_CFG_GET_UPDATE_SECS(sensor_config) * NSEC_PER_SEC;

	mult = SCMI_SENS_CFG_GET_UPDATE_EXP(sensor_config);
	अगर (mult < 0) अणु
		sensor_पूर्णांकerval_mult = पूर्णांक_घात(10, असल(mult));
		करो_भाग(sensor_update_पूर्णांकerval, sensor_पूर्णांकerval_mult);
	पूर्ण अन्यथा अणु
		sensor_पूर्णांकerval_mult = पूर्णांक_घात(10, mult);
		sensor_update_पूर्णांकerval =
			sensor_update_पूर्णांकerval * sensor_पूर्णांकerval_mult;
	पूर्ण

	convert_ns_to_freq(sensor_update_पूर्णांकerval, &hz, &uhz);
	*val = hz;
	*val2 = uhz;
	वापस 0;
पूर्ण

अटल पूर्णांक scmi_iio_पढ़ो_raw(काष्ठा iio_dev *iio_dev,
			     काष्ठा iio_chan_spec स्थिर *ch, पूर्णांक *val,
			     पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा scmi_iio_priv *sensor = iio_priv(iio_dev);
	s8 scale;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		scale = sensor->sensor_info->axis[ch->scan_index].scale;
		अगर (scale < 0) अणु
			*val = 1;
			*val2 = पूर्णांक_घात(10, असल(scale));
			वापस IIO_VAL_FRACTIONAL;
		पूर्ण
		*val = पूर्णांक_घात(10, scale);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = scmi_iio_get_odr_val(iio_dev, val, val2);
		वापस ret ? ret : IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info scmi_iio_info = अणु
	.पढ़ो_raw = scmi_iio_पढ़ो_raw,
	.पढ़ो_avail = scmi_iio_पढ़ो_avail,
	.ग_लिखो_raw = scmi_iio_ग_लिखो_raw,
पूर्ण;

अटल sमाप_प्रकार scmi_iio_get_raw_available(काष्ठा iio_dev *iio_dev,
					  uपूर्णांकptr_t निजी,
					  स्थिर काष्ठा iio_chan_spec *chan,
					  अक्षर *buf)
अणु
	काष्ठा scmi_iio_priv *sensor = iio_priv(iio_dev);
	u64 resolution, rem;
	s64 min_range, max_range;
	s8 exponent, scale;
	पूर्णांक len = 0;

	/*
	 * All the axes are supposed to have the same value क्रम range and resolution.
	 * We are just using the values from the Axis 0 here.
	 */
	अगर (sensor->sensor_info->axis[0].extended_attrs) अणु
		min_range = sensor->sensor_info->axis[0].attrs.min_range;
		max_range = sensor->sensor_info->axis[0].attrs.max_range;
		resolution = sensor->sensor_info->axis[0].resolution;
		exponent = sensor->sensor_info->axis[0].exponent;
		scale = sensor->sensor_info->axis[0].scale;

		/*
		 * To provide the raw value क्रम the resolution to the userspace,
		 * need to भागide the resolution exponent by the sensor scale
		 */
		exponent = exponent - scale;
		अगर (exponent < 0) अणु
			rem = करो_भाग(resolution,
				     पूर्णांक_घात(10, असल(exponent))
				     );
			len = scnम_लिखो(buf, PAGE_SIZE,
					"[%lld %llu.%llu %lld]\n", min_range,
					resolution, rem, max_range);
		पूर्ण अन्यथा अणु
			resolution = resolution * पूर्णांक_घात(10, exponent);
			len = scnम_लिखो(buf, PAGE_SIZE, "[%lld %llu %lld]\n",
					min_range, resolution, max_range);
		पूर्ण
	पूर्ण
	वापस len;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info scmi_iio_ext_info[] = अणु
	अणु
		.name = "raw_available",
		.पढ़ो = scmi_iio_get_raw_available,
		.shared = IIO_SHARED_BY_TYPE,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम scmi_iio_set_बारtamp_channel(काष्ठा iio_chan_spec *iio_chan,
					   पूर्णांक scan_index)
अणु
	iio_chan->type = IIO_TIMESTAMP;
	iio_chan->channel = -1;
	iio_chan->scan_index = scan_index;
	iio_chan->scan_type.sign = 'u';
	iio_chan->scan_type.realbits = 64;
	iio_chan->scan_type.storagebits = 64;
पूर्ण

अटल व्योम scmi_iio_set_data_channel(काष्ठा iio_chan_spec *iio_chan,
				      क्रमागत iio_chan_type type,
				      क्रमागत iio_modअगरier mod, पूर्णांक scan_index)
अणु
	iio_chan->type = type;
	iio_chan->modअगरied = 1;
	iio_chan->channel2 = mod;
	iio_chan->info_mask_separate = BIT(IIO_CHAN_INFO_SCALE);
	iio_chan->info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SAMP_FREQ);
	iio_chan->info_mask_shared_by_type_available =
		BIT(IIO_CHAN_INFO_SAMP_FREQ);
	iio_chan->scan_index = scan_index;
	iio_chan->scan_type.sign = 's';
	iio_chan->scan_type.realbits = 64;
	iio_chan->scan_type.storagebits = 64;
	iio_chan->scan_type.endianness = IIO_LE;
	iio_chan->ext_info = scmi_iio_ext_info;
पूर्ण

अटल पूर्णांक scmi_iio_get_chan_modअगरier(स्थिर अक्षर *name,
				      क्रमागत iio_modअगरier *modअगरier)
अणु
	अक्षर *pch, mod;

	अगर (!name)
		वापस -EINVAL;

	pch = म_खोजप(name, '_');
	अगर (!pch)
		वापस -EINVAL;

	mod = *(pch + 1);
	चयन (mod) अणु
	हाल 'X':
		*modअगरier = IIO_MOD_X;
		वापस 0;
	हाल 'Y':
		*modअगरier = IIO_MOD_Y;
		वापस 0;
	हाल 'Z':
		*modअगरier = IIO_MOD_Z;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक scmi_iio_get_chan_type(u8 scmi_type, क्रमागत iio_chan_type *iio_type)
अणु
	चयन (scmi_type) अणु
	हाल METERS_SEC_SQUARED:
		*iio_type = IIO_ACCEL;
		वापस 0;
	हाल RADIANS_SEC:
		*iio_type = IIO_ANGL_VEL;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल u64 scmi_iio_convert_पूर्णांकerval_to_ns(u32 val)
अणु
	u64 sensor_update_पूर्णांकerval =
		SCMI_SENS_INTVL_GET_SECS(val) * NSEC_PER_SEC;
	u64 sensor_पूर्णांकerval_mult;
	पूर्णांक mult;

	mult = SCMI_SENS_INTVL_GET_EXP(val);
	अगर (mult < 0) अणु
		sensor_पूर्णांकerval_mult = पूर्णांक_घात(10, असल(mult));
		करो_भाग(sensor_update_पूर्णांकerval, sensor_पूर्णांकerval_mult);
	पूर्ण अन्यथा अणु
		sensor_पूर्णांकerval_mult = पूर्णांक_घात(10, mult);
		sensor_update_पूर्णांकerval =
			sensor_update_पूर्णांकerval * sensor_पूर्णांकerval_mult;
	पूर्ण
	वापस sensor_update_पूर्णांकerval;
पूर्ण

अटल पूर्णांक scmi_iio_set_sampling_freq_avail(काष्ठा iio_dev *iio_dev)
अणु
	u64 cur_पूर्णांकerval_ns, low_पूर्णांकerval_ns, high_पूर्णांकerval_ns, step_size_ns,
		hz, uhz;
	अचिन्हित पूर्णांक cur_पूर्णांकerval, low_पूर्णांकerval, high_पूर्णांकerval, step_size;
	काष्ठा scmi_iio_priv *sensor = iio_priv(iio_dev);
	पूर्णांक i;

	sensor->freq_avail =
		devm_kzalloc(&iio_dev->dev,
			     माप(*sensor->freq_avail) *
				     (sensor->sensor_info->पूर्णांकervals.count * 2),
			     GFP_KERNEL);
	अगर (!sensor->freq_avail)
		वापस -ENOMEM;

	अगर (sensor->sensor_info->पूर्णांकervals.segmented) अणु
		low_पूर्णांकerval = sensor->sensor_info->पूर्णांकervals
				       .desc[SCMI_SENS_INTVL_SEGMENT_LOW];
		low_पूर्णांकerval_ns = scmi_iio_convert_पूर्णांकerval_to_ns(low_पूर्णांकerval);
		convert_ns_to_freq(low_पूर्णांकerval_ns, &hz, &uhz);
		sensor->freq_avail[0] = hz;
		sensor->freq_avail[1] = uhz;

		step_size = sensor->sensor_info->पूर्णांकervals
				    .desc[SCMI_SENS_INTVL_SEGMENT_STEP];
		step_size_ns = scmi_iio_convert_पूर्णांकerval_to_ns(step_size);
		convert_ns_to_freq(step_size_ns, &hz, &uhz);
		sensor->freq_avail[2] = hz;
		sensor->freq_avail[3] = uhz;

		high_पूर्णांकerval = sensor->sensor_info->पूर्णांकervals
					.desc[SCMI_SENS_INTVL_SEGMENT_HIGH];
		high_पूर्णांकerval_ns =
			scmi_iio_convert_पूर्णांकerval_to_ns(high_पूर्णांकerval);
		convert_ns_to_freq(high_पूर्णांकerval_ns, &hz, &uhz);
		sensor->freq_avail[4] = hz;
		sensor->freq_avail[5] = uhz;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < sensor->sensor_info->पूर्णांकervals.count; i++) अणु
			cur_पूर्णांकerval = sensor->sensor_info->पूर्णांकervals.desc[i];
			cur_पूर्णांकerval_ns =
				scmi_iio_convert_पूर्णांकerval_to_ns(cur_पूर्णांकerval);
			convert_ns_to_freq(cur_पूर्णांकerval_ns, &hz, &uhz);
			sensor->freq_avail[i * 2] = hz;
			sensor->freq_avail[i * 2 + 1] = uhz;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा iio_dev *
scmi_alloc_iiodev(काष्ठा scmi_device *sdev,
		  स्थिर काष्ठा scmi_sensor_proto_ops *ops,
		  काष्ठा scmi_protocol_handle *ph,
		  स्थिर काष्ठा scmi_sensor_info *sensor_info)
अणु
	काष्ठा iio_chan_spec *iio_channels;
	काष्ठा scmi_iio_priv *sensor;
	क्रमागत iio_modअगरier modअगरier;
	क्रमागत iio_chan_type type;
	काष्ठा iio_dev *iiodev;
	काष्ठा device *dev = &sdev->dev;
	स्थिर काष्ठा scmi_handle *handle = sdev->handle;
	पूर्णांक i, ret;

	iiodev = devm_iio_device_alloc(dev, माप(*sensor));
	अगर (!iiodev)
		वापस ERR_PTR(-ENOMEM);

	iiodev->modes = INDIO_सूचीECT_MODE;
	iiodev->dev.parent = dev;
	sensor = iio_priv(iiodev);
	sensor->sensor_ops = ops;
	sensor->ph = ph;
	sensor->sensor_info = sensor_info;
	sensor->sensor_update_nb.notअगरier_call = scmi_iio_sensor_update_cb;
	sensor->indio_dev = iiodev;

	/* adding one additional channel क्रम बारtamp */
	iiodev->num_channels = sensor_info->num_axis + 1;
	iiodev->name = sensor_info->name;
	iiodev->info = &scmi_iio_info;

	iio_channels =
		devm_kzalloc(dev,
			     माप(*iio_channels) * (iiodev->num_channels),
			     GFP_KERNEL);
	अगर (!iio_channels)
		वापस ERR_PTR(-ENOMEM);

	ret = scmi_iio_set_sampling_freq_avail(iiodev);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	क्रम (i = 0; i < sensor_info->num_axis; i++) अणु
		ret = scmi_iio_get_chan_type(sensor_info->axis[i].type, &type);
		अगर (ret < 0)
			वापस ERR_PTR(ret);

		ret = scmi_iio_get_chan_modअगरier(sensor_info->axis[i].name,
						 &modअगरier);
		अगर (ret < 0)
			वापस ERR_PTR(ret);

		scmi_iio_set_data_channel(&iio_channels[i], type, modअगरier,
					  sensor_info->axis[i].id);
	पूर्ण

	ret = handle->notअगरy_ops->devm_event_notअगरier_रेजिस्टर(sdev,
				SCMI_PROTOCOL_SENSOR, SCMI_EVENT_SENSOR_UPDATE,
				&sensor->sensor_info->id,
				&sensor->sensor_update_nb);
	अगर (ret) अणु
		dev_err(&iiodev->dev,
			"Error in registering sensor update notifier for sensor %s err %d",
			sensor->sensor_info->name, ret);
		वापस ERR_PTR(ret);
	पूर्ण

	scmi_iio_set_बारtamp_channel(&iio_channels[i], i);
	iiodev->channels = iio_channels;
	वापस iiodev;
पूर्ण

अटल पूर्णांक scmi_iio_dev_probe(काष्ठा scmi_device *sdev)
अणु
	स्थिर काष्ठा scmi_sensor_info *sensor_info;
	काष्ठा scmi_handle *handle = sdev->handle;
	स्थिर काष्ठा scmi_sensor_proto_ops *sensor_ops;
	काष्ठा scmi_protocol_handle *ph;
	काष्ठा device *dev = &sdev->dev;
	काष्ठा iio_dev *scmi_iio_dev;
	u16 nr_sensors;
	पूर्णांक err = -ENODEV, i;

	अगर (!handle)
		वापस -ENODEV;

	sensor_ops = handle->devm_protocol_get(sdev, SCMI_PROTOCOL_SENSOR, &ph);
	अगर (IS_ERR(sensor_ops)) अणु
		dev_err(dev, "SCMI device has no sensor interface\n");
		वापस PTR_ERR(sensor_ops);
	पूर्ण

	nr_sensors = sensor_ops->count_get(ph);
	अगर (!nr_sensors) अणु
		dev_dbg(dev, "0 sensors found via SCMI bus\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < nr_sensors; i++) अणु
		sensor_info = sensor_ops->info_get(ph, i);
		अगर (!sensor_info) अणु
			dev_err(dev, "SCMI sensor %d has missing info\n", i);
			वापस -EINVAL;
		पूर्ण

		/* This driver only supports 3-axis accel and gyro, skipping other sensors */
		अगर (sensor_info->num_axis != SCMI_IIO_NUM_OF_AXIS)
			जारी;

		/* This driver only supports 3-axis accel and gyro, skipping other sensors */
		अगर (sensor_info->axis[0].type != METERS_SEC_SQUARED &&
		    sensor_info->axis[0].type != RADIANS_SEC)
			जारी;

		scmi_iio_dev = scmi_alloc_iiodev(sdev, sensor_ops, ph,
						 sensor_info);
		अगर (IS_ERR(scmi_iio_dev)) अणु
			dev_err(dev,
				"failed to allocate IIO device for sensor %s: %ld\n",
				sensor_info->name, PTR_ERR(scmi_iio_dev));
			वापस PTR_ERR(scmi_iio_dev);
		पूर्ण

		err = devm_iio_kfअगरo_buffer_setup(&scmi_iio_dev->dev,
						  scmi_iio_dev,
						  INDIO_BUFFER_SOFTWARE,
						  &scmi_iio_buffer_ops);
		अगर (err < 0) अणु
			dev_err(dev,
				"IIO buffer setup error at sensor %s: %d\n",
				sensor_info->name, err);
			वापस err;
		पूर्ण

		err = devm_iio_device_रेजिस्टर(dev, scmi_iio_dev);
		अगर (err) अणु
			dev_err(dev,
				"IIO device registration failed at sensor %s: %d\n",
				sensor_info->name, err);
			वापस err;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल स्थिर काष्ठा scmi_device_id scmi_id_table[] = अणु
	अणु SCMI_PROTOCOL_SENSOR, "iiodev" पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(scmi, scmi_id_table);

अटल काष्ठा scmi_driver scmi_iiodev_driver = अणु
	.name = "scmi-sensor-iiodev",
	.probe = scmi_iio_dev_probe,
	.id_table = scmi_id_table,
पूर्ण;

module_scmi_driver(scmi_iiodev_driver);

MODULE_AUTHOR("Jyoti Bhayana <jbhayana@google.com>");
MODULE_DESCRIPTION("SCMI IIO Driver");
MODULE_LICENSE("GPL v2");
