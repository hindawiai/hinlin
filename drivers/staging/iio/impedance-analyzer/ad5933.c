<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD5933 AD5934 Impedance Converter, Network Analyzer
 *
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/iio/sysfs.h>

/* AD5933/AD5934 Registers */
#घोषणा AD5933_REG_CONTROL_HB		0x80	/* R/W, 1 byte */
#घोषणा AD5933_REG_CONTROL_LB		0x81	/* R/W, 1 byte */
#घोषणा AD5933_REG_FREQ_START		0x82	/* R/W, 3 bytes */
#घोषणा AD5933_REG_FREQ_INC		0x85	/* R/W, 3 bytes */
#घोषणा AD5933_REG_INC_NUM		0x88	/* R/W, 2 bytes, 9 bit */
#घोषणा AD5933_REG_SETTLING_CYCLES	0x8A	/* R/W, 2 bytes */
#घोषणा AD5933_REG_STATUS		0x8F	/* R, 1 byte */
#घोषणा AD5933_REG_TEMP_DATA		0x92	/* R, 2 bytes*/
#घोषणा AD5933_REG_REAL_DATA		0x94	/* R, 2 bytes*/
#घोषणा AD5933_REG_IMAG_DATA		0x96	/* R, 2 bytes*/

/* AD5933_REG_CONTROL_HB Bits */
#घोषणा AD5933_CTRL_INIT_START_FREQ	(0x1 << 4)
#घोषणा AD5933_CTRL_START_SWEEP		(0x2 << 4)
#घोषणा AD5933_CTRL_INC_FREQ		(0x3 << 4)
#घोषणा AD5933_CTRL_REPEAT_FREQ		(0x4 << 4)
#घोषणा AD5933_CTRL_MEASURE_TEMP	(0x9 << 4)
#घोषणा AD5933_CTRL_POWER_DOWN		(0xA << 4)
#घोषणा AD5933_CTRL_STANDBY		(0xB << 4)

#घोषणा AD5933_CTRL_RANGE_2000mVpp	(0x0 << 1)
#घोषणा AD5933_CTRL_RANGE_200mVpp	(0x1 << 1)
#घोषणा AD5933_CTRL_RANGE_400mVpp	(0x2 << 1)
#घोषणा AD5933_CTRL_RANGE_1000mVpp	(0x3 << 1)
#घोषणा AD5933_CTRL_RANGE(x)		((x) << 1)

#घोषणा AD5933_CTRL_PGA_GAIN_1		(0x1 << 0)
#घोषणा AD5933_CTRL_PGA_GAIN_5		(0x0 << 0)

/* AD5933_REG_CONTROL_LB Bits */
#घोषणा AD5933_CTRL_RESET		(0x1 << 4)
#घोषणा AD5933_CTRL_INT_SYSCLK		(0x0 << 3)
#घोषणा AD5933_CTRL_EXT_SYSCLK		(0x1 << 3)

/* AD5933_REG_STATUS Bits */
#घोषणा AD5933_STAT_TEMP_VALID		(0x1 << 0)
#घोषणा AD5933_STAT_DATA_VALID		(0x1 << 1)
#घोषणा AD5933_STAT_SWEEP_DONE		(0x1 << 2)

/* I2C Block Commands */
#घोषणा AD5933_I2C_BLOCK_WRITE		0xA0
#घोषणा AD5933_I2C_BLOCK_READ		0xA1
#घोषणा AD5933_I2C_ADDR_POINTER		0xB0

/* Device Specs */
#घोषणा AD5933_INT_OSC_FREQ_Hz		16776000
#घोषणा AD5933_MAX_OUTPUT_FREQ_Hz	100000
#घोषणा AD5933_MAX_RETRIES		100

#घोषणा AD5933_OUT_RANGE		1
#घोषणा AD5933_OUT_RANGE_AVAIL		2
#घोषणा AD5933_OUT_SETTLING_CYCLES	3
#घोषणा AD5933_IN_PGA_GAIN		4
#घोषणा AD5933_IN_PGA_GAIN_AVAIL	5
#घोषणा AD5933_FREQ_POINTS		6

#घोषणा AD5933_POLL_TIME_ms		10
#घोषणा AD5933_INIT_EXCITATION_TIME_ms	100

काष्ठा ad5933_state अणु
	काष्ठा i2c_client		*client;
	काष्ठा regulator		*reg;
	काष्ठा clk			*mclk;
	काष्ठा delayed_work		work;
	काष्ठा mutex			lock; /* Protect sensor state */
	अचिन्हित दीर्घ			mclk_hz;
	अचिन्हित अक्षर			ctrl_hb;
	अचिन्हित अक्षर			ctrl_lb;
	अचिन्हित पूर्णांक			range_avail[4];
	अचिन्हित लघु			vref_mv;
	अचिन्हित लघु			settling_cycles;
	अचिन्हित लघु			freq_poपूर्णांकs;
	अचिन्हित पूर्णांक			freq_start;
	अचिन्हित पूर्णांक			freq_inc;
	अचिन्हित पूर्णांक			state;
	अचिन्हित पूर्णांक			poll_समय_jअगरfies;
पूर्ण;

#घोषणा AD5933_CHANNEL(_type, _extend_name, _info_mask_separate, _address, \
		_scan_index, _realbits) अणु \
	.type = (_type), \
	.extend_name = (_extend_name), \
	.info_mask_separate = (_info_mask_separate), \
	.address = (_address), \
	.scan_index = (_scan_index), \
	.scan_type = अणु \
		.sign = 's', \
		.realbits = (_realbits), \
		.storagebits = 16, \
	पूर्ण, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad5933_channels[] = अणु
	AD5933_CHANNEL(IIO_TEMP, शून्य, BIT(IIO_CHAN_INFO_RAW) |
		BIT(IIO_CHAN_INFO_SCALE), AD5933_REG_TEMP_DATA, -1, 14),
	/* Ring Channels */
	AD5933_CHANNEL(IIO_VOLTAGE, "real", 0, AD5933_REG_REAL_DATA, 0, 16),
	AD5933_CHANNEL(IIO_VOLTAGE, "imag", 0, AD5933_REG_IMAG_DATA, 1, 16),
पूर्ण;

अटल पूर्णांक ad5933_i2c_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 len, u8 *data)
अणु
	पूर्णांक ret;

	जबतक (len--) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client, reg++, *data++);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "I2C write error\n");
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ad5933_i2c_पढ़ो(काष्ठा i2c_client *client, u8 reg, u8 len, u8 *data)
अणु
	पूर्णांक ret;

	जबतक (len--) अणु
		ret = i2c_smbus_पढ़ो_byte_data(client, reg++);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "I2C read error\n");
			वापस ret;
		पूर्ण
		*data++ = ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ad5933_cmd(काष्ठा ad5933_state *st, अचिन्हित अक्षर cmd)
अणु
	अचिन्हित अक्षर dat = st->ctrl_hb | cmd;

	वापस ad5933_i2c_ग_लिखो(st->client,
			AD5933_REG_CONTROL_HB, 1, &dat);
पूर्ण

अटल पूर्णांक ad5933_reset(काष्ठा ad5933_state *st)
अणु
	अचिन्हित अक्षर dat = st->ctrl_lb | AD5933_CTRL_RESET;

	वापस ad5933_i2c_ग_लिखो(st->client,
			AD5933_REG_CONTROL_LB, 1, &dat);
पूर्ण

अटल पूर्णांक ad5933_रुको_busy(काष्ठा ad5933_state *st, अचिन्हित अक्षर event)
अणु
	अचिन्हित अक्षर val, समयout = AD5933_MAX_RETRIES;
	पूर्णांक ret;

	जबतक (समयout--) अणु
		ret =  ad5933_i2c_पढ़ो(st->client, AD5933_REG_STATUS, 1, &val);
		अगर (ret < 0)
			वापस ret;
		अगर (val & event)
			वापस val;
		cpu_relax();
		mdelay(1);
	पूर्ण

	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक ad5933_set_freq(काष्ठा ad5933_state *st,
			   अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ freq)
अणु
	अचिन्हित दीर्घ दीर्घ freqreg;
	जोड़ अणु
		__be32 d32;
		u8 d8[4];
	पूर्ण dat;

	freqreg = (u64)freq * (u64)(1 << 27);
	करो_भाग(freqreg, st->mclk_hz / 4);

	चयन (reg) अणु
	हाल AD5933_REG_FREQ_START:
		st->freq_start = freq;
		अवरोध;
	हाल AD5933_REG_FREQ_INC:
		st->freq_inc = freq;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dat.d32 = cpu_to_be32(freqreg);
	वापस ad5933_i2c_ग_लिखो(st->client, reg, 3, &dat.d8[1]);
पूर्ण

अटल पूर्णांक ad5933_setup(काष्ठा ad5933_state *st)
अणु
	__be16 dat;
	पूर्णांक ret;

	ret = ad5933_reset(st);
	अगर (ret < 0)
		वापस ret;

	ret = ad5933_set_freq(st, AD5933_REG_FREQ_START, 10000);
	अगर (ret < 0)
		वापस ret;

	ret = ad5933_set_freq(st, AD5933_REG_FREQ_INC, 200);
	अगर (ret < 0)
		वापस ret;

	st->settling_cycles = 10;
	dat = cpu_to_be16(st->settling_cycles);

	ret = ad5933_i2c_ग_लिखो(st->client,
			       AD5933_REG_SETTLING_CYCLES,
			       2, (u8 *)&dat);
	अगर (ret < 0)
		वापस ret;

	st->freq_poपूर्णांकs = 100;
	dat = cpu_to_be16(st->freq_poपूर्णांकs);

	वापस ad5933_i2c_ग_लिखो(st->client, AD5933_REG_INC_NUM, 2, (u8 *)&dat);
पूर्ण

अटल व्योम ad5933_calc_out_ranges(काष्ठा ad5933_state *st)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक normalized_3v3[4] = अणु1980, 198, 383, 970पूर्ण;

	क्रम (i = 0; i < 4; i++)
		st->range_avail[i] = normalized_3v3[i] * st->vref_mv / 3300;
पूर्ण

/*
 * handles: AD5933_REG_FREQ_START and AD5933_REG_FREQ_INC
 */

अटल sमाप_प्रकार ad5933_show_frequency(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad5933_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	पूर्णांक ret;
	अचिन्हित दीर्घ दीर्घ freqreg;
	जोड़ अणु
		__be32 d32;
		u8 d8[4];
	पूर्ण dat;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;
	ret = ad5933_i2c_पढ़ो(st->client, this_attr->address, 3, &dat.d8[1]);
	iio_device_release_direct_mode(indio_dev);
	अगर (ret < 0)
		वापस ret;

	freqreg = be32_to_cpu(dat.d32) & 0xFFFFFF;

	freqreg = (u64)freqreg * (u64)(st->mclk_hz / 4);
	करो_भाग(freqreg, BIT(27));

	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)freqreg);
पूर्ण

अटल sमाप_प्रकार ad5933_store_frequency(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf,
				      माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad5933_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val > AD5933_MAX_OUTPUT_FREQ_Hz)
		वापस -EINVAL;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;
	ret = ad5933_set_freq(st, this_attr->address, val);
	iio_device_release_direct_mode(indio_dev);

	वापस ret ? ret : len;
पूर्ण

अटल IIO_DEVICE_ATTR(out_altvoltage0_frequency_start, 0644,
			ad5933_show_frequency,
			ad5933_store_frequency,
			AD5933_REG_FREQ_START);

अटल IIO_DEVICE_ATTR(out_altvoltage0_frequency_increment, 0644,
			ad5933_show_frequency,
			ad5933_store_frequency,
			AD5933_REG_FREQ_INC);

अटल sमाप_प्रकार ad5933_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad5933_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	पूर्णांक ret = 0, len = 0;

	mutex_lock(&st->lock);
	चयन ((u32)this_attr->address) अणु
	हाल AD5933_OUT_RANGE:
		len = प्र_लिखो(buf, "%u\n",
			      st->range_avail[(st->ctrl_hb >> 1) & 0x3]);
		अवरोध;
	हाल AD5933_OUT_RANGE_AVAIL:
		len = प्र_लिखो(buf, "%u %u %u %u\n", st->range_avail[0],
			      st->range_avail[3], st->range_avail[2],
			      st->range_avail[1]);
		अवरोध;
	हाल AD5933_OUT_SETTLING_CYCLES:
		len = प्र_लिखो(buf, "%d\n", st->settling_cycles);
		अवरोध;
	हाल AD5933_IN_PGA_GAIN:
		len = प्र_लिखो(buf, "%s\n",
			      (st->ctrl_hb & AD5933_CTRL_PGA_GAIN_1) ?
			      "1" : "0.2");
		अवरोध;
	हाल AD5933_IN_PGA_GAIN_AVAIL:
		len = प्र_लिखो(buf, "1 0.2\n");
		अवरोध;
	हाल AD5933_FREQ_POINTS:
		len = प्र_लिखो(buf, "%d\n", st->freq_poपूर्णांकs);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&st->lock);
	वापस ret ? ret : len;
पूर्ण

अटल sमाप_प्रकार ad5933_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf,
			    माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad5933_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	u16 val;
	पूर्णांक i, ret = 0;
	__be16 dat;

	अगर (this_attr->address != AD5933_IN_PGA_GAIN) अणु
		ret = kstrtou16(buf, 10, &val);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;
	mutex_lock(&st->lock);
	चयन ((u32)this_attr->address) अणु
	हाल AD5933_OUT_RANGE:
		ret = -EINVAL;
		क्रम (i = 0; i < 4; i++)
			अगर (val == st->range_avail[i]) अणु
				st->ctrl_hb &= ~AD5933_CTRL_RANGE(0x3);
				st->ctrl_hb |= AD5933_CTRL_RANGE(i);
				ret = ad5933_cmd(st, 0);
				अवरोध;
			पूर्ण
		अवरोध;
	हाल AD5933_IN_PGA_GAIN:
		अगर (sysfs_streq(buf, "1")) अणु
			st->ctrl_hb |= AD5933_CTRL_PGA_GAIN_1;
		पूर्ण अन्यथा अगर (sysfs_streq(buf, "0.2")) अणु
			st->ctrl_hb &= ~AD5933_CTRL_PGA_GAIN_1;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = ad5933_cmd(st, 0);
		अवरोध;
	हाल AD5933_OUT_SETTLING_CYCLES:
		val = clamp(val, (u16)0, (u16)0x7FF);
		st->settling_cycles = val;

		/* 2x, 4x handling, see datasheet */
		अगर (val > 1022)
			val = (val >> 2) | (3 << 9);
		अन्यथा अगर (val > 511)
			val = (val >> 1) | BIT(9);

		dat = cpu_to_be16(val);
		ret = ad5933_i2c_ग_लिखो(st->client,
				       AD5933_REG_SETTLING_CYCLES,
				       2, (u8 *)&dat);
		अवरोध;
	हाल AD5933_FREQ_POINTS:
		val = clamp(val, (u16)0, (u16)511);
		st->freq_poपूर्णांकs = val;

		dat = cpu_to_be16(val);
		ret = ad5933_i2c_ग_लिखो(st->client, AD5933_REG_INC_NUM, 2,
				       (u8 *)&dat);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&st->lock);
	iio_device_release_direct_mode(indio_dev);
	वापस ret ? ret : len;
पूर्ण

अटल IIO_DEVICE_ATTR(out_altvoltage0_raw, 0644,
			ad5933_show,
			ad5933_store,
			AD5933_OUT_RANGE);

अटल IIO_DEVICE_ATTR(out_altvoltage0_scale_available, 0444,
			ad5933_show,
			शून्य,
			AD5933_OUT_RANGE_AVAIL);

अटल IIO_DEVICE_ATTR(in_voltage0_scale, 0644,
			ad5933_show,
			ad5933_store,
			AD5933_IN_PGA_GAIN);

अटल IIO_DEVICE_ATTR(in_voltage0_scale_available, 0444,
			ad5933_show,
			शून्य,
			AD5933_IN_PGA_GAIN_AVAIL);

अटल IIO_DEVICE_ATTR(out_altvoltage0_frequency_poपूर्णांकs, 0644,
			ad5933_show,
			ad5933_store,
			AD5933_FREQ_POINTS);

अटल IIO_DEVICE_ATTR(out_altvoltage0_settling_cycles, 0644,
			ad5933_show,
			ad5933_store,
			AD5933_OUT_SETTLING_CYCLES);

/*
 * note:
 * ideally we would handle the scale attributes via the iio_info
 * (पढ़ो|ग_लिखो)_raw methods, however this part is a untypical since we
 * करोn't create dedicated sysfs channel attributes क्रम out0 and in0.
 */
अटल काष्ठा attribute *ad5933_attributes[] = अणु
	&iio_dev_attr_out_altvoltage0_raw.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_scale_available.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_frequency_start.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_frequency_increment.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_frequency_poपूर्णांकs.dev_attr.attr,
	&iio_dev_attr_out_altvoltage0_settling_cycles.dev_attr.attr,
	&iio_dev_attr_in_voltage0_scale.dev_attr.attr,
	&iio_dev_attr_in_voltage0_scale_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad5933_attribute_group = अणु
	.attrs = ad5933_attributes,
पूर्ण;

अटल पूर्णांक ad5933_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad5933_state *st = iio_priv(indio_dev);
	__be16 dat;
	पूर्णांक ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = ad5933_cmd(st, AD5933_CTRL_MEASURE_TEMP);
		अगर (ret < 0)
			जाओ out;
		ret = ad5933_रुको_busy(st, AD5933_STAT_TEMP_VALID);
		अगर (ret < 0)
			जाओ out;

		ret = ad5933_i2c_पढ़ो(st->client,
				      AD5933_REG_TEMP_DATA,
				      2, (u8 *)&dat);
		अगर (ret < 0)
			जाओ out;
		iio_device_release_direct_mode(indio_dev);
		*val = sign_extend32(be16_to_cpu(dat), 13);

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 1000;
		*val2 = 5;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण

	वापस -EINVAL;
out:
	iio_device_release_direct_mode(indio_dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info ad5933_info = अणु
	.पढ़ो_raw = ad5933_पढ़ो_raw,
	.attrs = &ad5933_attribute_group,
पूर्ण;

अटल पूर्णांक ad5933_ring_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad5933_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (biपंचांगap_empty(indio_dev->active_scan_mask, indio_dev->masklength))
		वापस -EINVAL;

	ret = ad5933_reset(st);
	अगर (ret < 0)
		वापस ret;

	ret = ad5933_cmd(st, AD5933_CTRL_STANDBY);
	अगर (ret < 0)
		वापस ret;

	ret = ad5933_cmd(st, AD5933_CTRL_INIT_START_FREQ);
	अगर (ret < 0)
		वापस ret;

	st->state = AD5933_CTRL_INIT_START_FREQ;

	वापस 0;
पूर्ण

अटल पूर्णांक ad5933_ring_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad5933_state *st = iio_priv(indio_dev);

	/*
	 * AD5933_CTRL_INIT_START_FREQ:
	 * High Q complex circuits require a दीर्घ समय to reach steady state.
	 * To facilitate the measurement of such impedances, this mode allows
	 * the user full control of the settling समय requirement beक्रमe
	 * entering start frequency sweep mode where the impedance measurement
	 * takes place. In this mode the impedance is excited with the
	 * programmed start frequency (ad5933_ring_preenable),
	 * but no measurement takes place.
	 */

	schedule_delayed_work(&st->work,
			      msecs_to_jअगरfies(AD5933_INIT_EXCITATION_TIME_ms));
	वापस 0;
पूर्ण

अटल पूर्णांक ad5933_ring_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad5933_state *st = iio_priv(indio_dev);

	cancel_delayed_work_sync(&st->work);
	वापस ad5933_cmd(st, AD5933_CTRL_POWER_DOWN);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops ad5933_ring_setup_ops = अणु
	.preenable = ad5933_ring_preenable,
	.postenable = ad5933_ring_postenable,
	.postdisable = ad5933_ring_postdisable,
पूर्ण;

अटल व्योम ad5933_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ad5933_state *st = container_of(work,
		काष्ठा ad5933_state, work.work);
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(st->client);
	__be16 buf[2];
	पूर्णांक val[2];
	अचिन्हित अक्षर status;
	पूर्णांक ret;

	अगर (st->state == AD5933_CTRL_INIT_START_FREQ) अणु
		/* start sweep */
		ad5933_cmd(st, AD5933_CTRL_START_SWEEP);
		st->state = AD5933_CTRL_START_SWEEP;
		schedule_delayed_work(&st->work, st->poll_समय_jअगरfies);
		वापस;
	पूर्ण

	ret = ad5933_i2c_पढ़ो(st->client, AD5933_REG_STATUS, 1, &status);
	अगर (ret)
		वापस;

	अगर (status & AD5933_STAT_DATA_VALID) अणु
		पूर्णांक scan_count = biपंचांगap_weight(indio_dev->active_scan_mask,
					       indio_dev->masklength);
		ret = ad5933_i2c_पढ़ो(st->client,
				test_bit(1, indio_dev->active_scan_mask) ?
				AD5933_REG_REAL_DATA : AD5933_REG_IMAG_DATA,
				scan_count * 2, (u8 *)buf);
		अगर (ret)
			वापस;

		अगर (scan_count == 2) अणु
			val[0] = be16_to_cpu(buf[0]);
			val[1] = be16_to_cpu(buf[1]);
		पूर्ण अन्यथा अणु
			val[0] = be16_to_cpu(buf[0]);
		पूर्ण
		iio_push_to_buffers(indio_dev, val);
	पूर्ण अन्यथा अणु
		/* no data available - try again later */
		schedule_delayed_work(&st->work, st->poll_समय_jअगरfies);
		वापस;
	पूर्ण

	अगर (status & AD5933_STAT_SWEEP_DONE) अणु
		/*
		 * last sample received - घातer करोwn करो
		 * nothing until the ring enable is toggled
		 */
		ad5933_cmd(st, AD5933_CTRL_POWER_DOWN);
	पूर्ण अन्यथा अणु
		/* we just received a valid datum, move on to the next */
		ad5933_cmd(st, AD5933_CTRL_INC_FREQ);
		schedule_delayed_work(&st->work, st->poll_समय_jअगरfies);
	पूर्ण
पूर्ण

अटल व्योम ad5933_reg_disable(व्योम *data)
अणु
	काष्ठा ad5933_state *st = data;

	regulator_disable(st->reg);
पूर्ण

अटल व्योम ad5933_clk_disable(व्योम *data)
अणु
	काष्ठा ad5933_state *st = data;

	clk_disable_unprepare(st->mclk);
पूर्ण

अटल पूर्णांक ad5933_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा ad5933_state *st;
	काष्ठा iio_dev *indio_dev;
	अचिन्हित दीर्घ ext_clk_hz = 0;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	st->client = client;

	mutex_init(&st->lock);

	st->reg = devm_regulator_get(&client->dev, "vdd");
	अगर (IS_ERR(st->reg))
		वापस PTR_ERR(st->reg);

	ret = regulator_enable(st->reg);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to enable specified VDD supply\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&client->dev, ad5933_reg_disable, st);
	अगर (ret)
		वापस ret;

	ret = regulator_get_voltage(st->reg);
	अगर (ret < 0)
		वापस ret;

	st->vref_mv = ret / 1000;

	st->mclk = devm_clk_get(&client->dev, "mclk");
	अगर (IS_ERR(st->mclk) && PTR_ERR(st->mclk) != -ENOENT)
		वापस PTR_ERR(st->mclk);

	अगर (!IS_ERR(st->mclk)) अणु
		ret = clk_prepare_enable(st->mclk);
		अगर (ret < 0)
			वापस ret;

		ret = devm_add_action_or_reset(&client->dev,
					       ad5933_clk_disable,
					       st);
		अगर (ret)
			वापस ret;

		ext_clk_hz = clk_get_rate(st->mclk);
	पूर्ण

	अगर (ext_clk_hz) अणु
		st->mclk_hz = ext_clk_hz;
		st->ctrl_lb = AD5933_CTRL_EXT_SYSCLK;
	पूर्ण अन्यथा अणु
		st->mclk_hz = AD5933_INT_OSC_FREQ_Hz;
		st->ctrl_lb = AD5933_CTRL_INT_SYSCLK;
	पूर्ण

	ad5933_calc_out_ranges(st);
	INIT_DELAYED_WORK(&st->work, ad5933_work);
	st->poll_समय_jअगरfies = msecs_to_jअगरfies(AD5933_POLL_TIME_ms);

	indio_dev->info = &ad5933_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ad5933_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad5933_channels);

	ret = devm_iio_kfअगरo_buffer_setup(&client->dev, indio_dev,
					  INDIO_BUFFER_SOFTWARE,
					  &ad5933_ring_setup_ops);
	अगर (ret)
		वापस ret;

	ret = ad5933_setup(st);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad5933_id[] = अणु
	अणु "ad5933", 0 पूर्ण,
	अणु "ad5934", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ad5933_id);

अटल स्थिर काष्ठा of_device_id ad5933_of_match[] = अणु
	अणु .compatible = "adi,ad5933" पूर्ण,
	अणु .compatible = "adi,ad5934" पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, ad5933_of_match);

अटल काष्ठा i2c_driver ad5933_driver = अणु
	.driver = अणु
		.name = "ad5933",
		.of_match_table = ad5933_of_match,
	पूर्ण,
	.probe = ad5933_probe,
	.id_table = ad5933_id,
पूर्ण;
module_i2c_driver(ad5933_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD5933 Impedance Conv. Network Analyzer");
MODULE_LICENSE("GPL v2");
