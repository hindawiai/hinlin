<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD7746 capacitive sensor driver supporting AD7745, AD7746 and AD7747
 *
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/sysfs.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश "ad7746.h"

/*
 * AD7746 Register Definition
 */

#घोषणा AD7746_REG_STATUS		0
#घोषणा AD7746_REG_CAP_DATA_HIGH	1
#घोषणा AD7746_REG_VT_DATA_HIGH		4
#घोषणा AD7746_REG_CAP_SETUP		7
#घोषणा AD7746_REG_VT_SETUP		8
#घोषणा AD7746_REG_EXC_SETUP		9
#घोषणा AD7746_REG_CFG			10
#घोषणा AD7746_REG_CAPDACA		11
#घोषणा AD7746_REG_CAPDACB		12
#घोषणा AD7746_REG_CAP_OFFH		13
#घोषणा AD7746_REG_CAP_GAINH		15
#घोषणा AD7746_REG_VOLT_GAINH		17

/* Status Register Bit Designations (AD7746_REG_STATUS) */
#घोषणा AD7746_STATUS_EXCERR		BIT(3)
#घोषणा AD7746_STATUS_RDY		BIT(2)
#घोषणा AD7746_STATUS_RDYVT		BIT(1)
#घोषणा AD7746_STATUS_RDYCAP		BIT(0)

/* Capacitive Channel Setup Register Bit Designations (AD7746_REG_CAP_SETUP) */
#घोषणा AD7746_CAPSETUP_CAPEN		BIT(7)
#घोषणा AD7746_CAPSETUP_CIN2		BIT(6) /* AD7746 only */
#घोषणा AD7746_CAPSETUP_CAPDIFF		BIT(5)
#घोषणा AD7746_CAPSETUP_CACHOP		BIT(0)

/* Voltage/Temperature Setup Register Bit Designations (AD7746_REG_VT_SETUP) */
#घोषणा AD7746_VTSETUP_VTEN		(1 << 7)
#घोषणा AD7746_VTSETUP_VTMD_INT_TEMP	(0 << 5)
#घोषणा AD7746_VTSETUP_VTMD_EXT_TEMP	(1 << 5)
#घोषणा AD7746_VTSETUP_VTMD_VDD_MON	(2 << 5)
#घोषणा AD7746_VTSETUP_VTMD_EXT_VIN	(3 << 5)
#घोषणा AD7746_VTSETUP_EXTREF		BIT(4)
#घोषणा AD7746_VTSETUP_VTSHORT		BIT(1)
#घोषणा AD7746_VTSETUP_VTCHOP		BIT(0)

/* Excitation Setup Register Bit Designations (AD7746_REG_EXC_SETUP) */
#घोषणा AD7746_EXCSETUP_CLKCTRL		BIT(7)
#घोषणा AD7746_EXCSETUP_EXCON		BIT(6)
#घोषणा AD7746_EXCSETUP_EXCB		BIT(5)
#घोषणा AD7746_EXCSETUP_NEXCB		BIT(4)
#घोषणा AD7746_EXCSETUP_EXCA		BIT(3)
#घोषणा AD7746_EXCSETUP_NEXCA		BIT(2)
#घोषणा AD7746_EXCSETUP_EXCLVL(x)	(((x) & 0x3) << 0)

/* Config Register Bit Designations (AD7746_REG_CFG) */
#घोषणा AD7746_CONF_VTFS_SHIFT		6
#घोषणा AD7746_CONF_CAPFS_SHIFT		3
#घोषणा AD7746_CONF_VTFS_MASK		GENMASK(7, 6)
#घोषणा AD7746_CONF_CAPFS_MASK		GENMASK(5, 3)
#घोषणा AD7746_CONF_MODE_IDLE		(0 << 0)
#घोषणा AD7746_CONF_MODE_CONT_CONV	(1 << 0)
#घोषणा AD7746_CONF_MODE_SINGLE_CONV	(2 << 0)
#घोषणा AD7746_CONF_MODE_PWRDN		(3 << 0)
#घोषणा AD7746_CONF_MODE_OFFS_CAL	(5 << 0)
#घोषणा AD7746_CONF_MODE_GAIN_CAL	(6 << 0)

/* CAPDAC Register Bit Designations (AD7746_REG_CAPDACx) */
#घोषणा AD7746_CAPDAC_DACEN		BIT(7)
#घोषणा AD7746_CAPDAC_DACP(x)		((x) & 0x7F)

/*
 * काष्ठा ad7746_chip_info - chip specअगरic inक्रमmation
 */

काष्ठा ad7746_chip_info अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock; /* protect sensor state */
	/*
	 * Capacitive channel digital filter setup;
	 * conversion समय/update rate setup per channel
	 */
	u8	config;
	u8	cap_setup;
	u8	vt_setup;
	u8	capdac[2][2];
	s8	capdac_set;

	जोड़ अणु
		__be32 d32;
		u8 d8[4];
	पूर्ण data ____cacheline_aligned;
पूर्ण;

क्रमागत ad7746_chan अणु
	VIN,
	VIN_VDD,
	TEMP_INT,
	TEMP_EXT,
	CIN1,
	CIN1_DIFF,
	CIN2,
	CIN2_DIFF,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad7746_channels[] = अणु
	[VIN] = अणु
		.type = IIO_VOLTAGE,
		.indexed = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.address = AD7746_REG_VT_DATA_HIGH << 8 |
			AD7746_VTSETUP_VTMD_EXT_VIN,
	पूर्ण,
	[VIN_VDD] = अणु
		.type = IIO_VOLTAGE,
		.indexed = 1,
		.channel = 1,
		.extend_name = "supply",
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.address = AD7746_REG_VT_DATA_HIGH << 8 |
			AD7746_VTSETUP_VTMD_VDD_MON,
	पूर्ण,
	[TEMP_INT] = अणु
		.type = IIO_TEMP,
		.indexed = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.address = AD7746_REG_VT_DATA_HIGH << 8 |
			AD7746_VTSETUP_VTMD_INT_TEMP,
	पूर्ण,
	[TEMP_EXT] = अणु
		.type = IIO_TEMP,
		.indexed = 1,
		.channel = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.address = AD7746_REG_VT_DATA_HIGH << 8 |
			AD7746_VTSETUP_VTMD_EXT_TEMP,
	पूर्ण,
	[CIN1] = अणु
		.type = IIO_CAPACITANCE,
		.indexed = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		BIT(IIO_CHAN_INFO_CALIBSCALE) | BIT(IIO_CHAN_INFO_OFFSET),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_CALIBBIAS) |
		BIT(IIO_CHAN_INFO_SCALE) | BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.address = AD7746_REG_CAP_DATA_HIGH << 8,
	पूर्ण,
	[CIN1_DIFF] = अणु
		.type = IIO_CAPACITANCE,
		.dअगरferential = 1,
		.indexed = 1,
		.channel = 0,
		.channel2 = 2,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		BIT(IIO_CHAN_INFO_CALIBSCALE) | BIT(IIO_CHAN_INFO_OFFSET),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_CALIBBIAS) |
		BIT(IIO_CHAN_INFO_SCALE) | BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.address = AD7746_REG_CAP_DATA_HIGH << 8 |
			AD7746_CAPSETUP_CAPDIFF
	पूर्ण,
	[CIN2] = अणु
		.type = IIO_CAPACITANCE,
		.indexed = 1,
		.channel = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		BIT(IIO_CHAN_INFO_CALIBSCALE) | BIT(IIO_CHAN_INFO_OFFSET),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_CALIBBIAS) |
		BIT(IIO_CHAN_INFO_SCALE) | BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.address = AD7746_REG_CAP_DATA_HIGH << 8 |
			AD7746_CAPSETUP_CIN2,
	पूर्ण,
	[CIN2_DIFF] = अणु
		.type = IIO_CAPACITANCE,
		.dअगरferential = 1,
		.indexed = 1,
		.channel = 1,
		.channel2 = 3,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		BIT(IIO_CHAN_INFO_CALIBSCALE) | BIT(IIO_CHAN_INFO_OFFSET),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_CALIBBIAS) |
		BIT(IIO_CHAN_INFO_SCALE) | BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.address = AD7746_REG_CAP_DATA_HIGH << 8 |
			AD7746_CAPSETUP_CAPDIFF | AD7746_CAPSETUP_CIN2,
	पूर्ण
पूर्ण;

/* Values are Update Rate (Hz), Conversion Time (ms) + 1*/
अटल स्थिर अचिन्हित अक्षर ad7746_vt_filter_rate_table[][2] = अणु
	अणु50, 20 + 1पूर्ण, अणु31, 32 + 1पूर्ण, अणु16, 62 + 1पूर्ण, अणु8, 122 + 1पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर ad7746_cap_filter_rate_table[][2] = अणु
	अणु91, 11 + 1पूर्ण, अणु84, 12 + 1पूर्ण, अणु50, 20 + 1पूर्ण, अणु26, 38 + 1पूर्ण,
	अणु16, 62 + 1पूर्ण, अणु13, 77 + 1पूर्ण, अणु11, 92 + 1पूर्ण, अणु9, 110 + 1पूर्ण,
पूर्ण;

अटल पूर्णांक ad7746_select_channel(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan)
अणु
	काष्ठा ad7746_chip_info *chip = iio_priv(indio_dev);
	u8 vt_setup, cap_setup;
	पूर्णांक ret, delay, idx;

	चयन (chan->type) अणु
	हाल IIO_CAPACITANCE:
		cap_setup = (chan->address & 0xFF) | AD7746_CAPSETUP_CAPEN;
		vt_setup = chip->vt_setup & ~AD7746_VTSETUP_VTEN;
		idx = (chip->config & AD7746_CONF_CAPFS_MASK) >>
			AD7746_CONF_CAPFS_SHIFT;
		delay = ad7746_cap_filter_rate_table[idx][1];

		अगर (chip->capdac_set != chan->channel) अणु
			ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
				AD7746_REG_CAPDACA,
				chip->capdac[chan->channel][0]);
			अगर (ret < 0)
				वापस ret;
			ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
				AD7746_REG_CAPDACB,
				chip->capdac[chan->channel][1]);
			अगर (ret < 0)
				वापस ret;

			chip->capdac_set = chan->channel;
		पूर्ण
		अवरोध;
	हाल IIO_VOLTAGE:
	हाल IIO_TEMP:
		vt_setup = (chan->address & 0xFF) | AD7746_VTSETUP_VTEN;
		cap_setup = chip->cap_setup & ~AD7746_CAPSETUP_CAPEN;
		idx = (chip->config & AD7746_CONF_VTFS_MASK) >>
			AD7746_CONF_VTFS_SHIFT;
		delay = ad7746_cap_filter_rate_table[idx][1];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (chip->cap_setup != cap_setup) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
						AD7746_REG_CAP_SETUP,
						cap_setup);
		अगर (ret < 0)
			वापस ret;

		chip->cap_setup = cap_setup;
	पूर्ण

	अगर (chip->vt_setup != vt_setup) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
						AD7746_REG_VT_SETUP,
						vt_setup);
		अगर (ret < 0)
			वापस ret;

		chip->vt_setup = vt_setup;
	पूर्ण

	वापस delay;
पूर्ण

अटल अंतरभूत sमाप_प्रकार ad7746_start_calib(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf,
					 माप_प्रकार len,
					 u8 regval)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7746_chip_info *chip = iio_priv(indio_dev);
	पूर्णांक ret, समयout = 10;
	bool करोit;

	ret = strtobool(buf, &करोit);
	अगर (ret < 0)
		वापस ret;

	अगर (!करोit)
		वापस 0;

	mutex_lock(&chip->lock);
	regval |= chip->config;
	ret = i2c_smbus_ग_लिखो_byte_data(chip->client, AD7746_REG_CFG, regval);
	अगर (ret < 0)
		जाओ unlock;

	करो अणु
		msleep(20);
		ret = i2c_smbus_पढ़ो_byte_data(chip->client, AD7746_REG_CFG);
		अगर (ret < 0)
			जाओ unlock;

	पूर्ण जबतक ((ret == regval) && समयout--);

	mutex_unlock(&chip->lock);

	वापस len;

unlock:
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ad7746_start_offset_calib(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf,
					 माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	पूर्णांक ret = ad7746_select_channel(indio_dev,
			      &ad7746_channels[to_iio_dev_attr(attr)->address]);
	अगर (ret < 0)
		वापस ret;

	वापस ad7746_start_calib(dev, attr, buf, len,
				  AD7746_CONF_MODE_OFFS_CAL);
पूर्ण

अटल sमाप_प्रकार ad7746_start_gain_calib(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf,
				       माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	पूर्णांक ret = ad7746_select_channel(indio_dev,
			      &ad7746_channels[to_iio_dev_attr(attr)->address]);
	अगर (ret < 0)
		वापस ret;

	वापस ad7746_start_calib(dev, attr, buf, len,
				  AD7746_CONF_MODE_GAIN_CAL);
पूर्ण

अटल IIO_DEVICE_ATTR(in_capacitance0_calibbias_calibration,
		       0200, शून्य, ad7746_start_offset_calib, CIN1);
अटल IIO_DEVICE_ATTR(in_capacitance1_calibbias_calibration,
		       0200, शून्य, ad7746_start_offset_calib, CIN2);
अटल IIO_DEVICE_ATTR(in_capacitance0_calibscale_calibration,
		       0200, शून्य, ad7746_start_gain_calib, CIN1);
अटल IIO_DEVICE_ATTR(in_capacitance1_calibscale_calibration,
		       0200, शून्य, ad7746_start_gain_calib, CIN2);
अटल IIO_DEVICE_ATTR(in_voltage0_calibscale_calibration,
		       0200, शून्य, ad7746_start_gain_calib, VIN);

अटल पूर्णांक ad7746_store_cap_filter_rate_setup(काष्ठा ad7746_chip_info *chip,
					      पूर्णांक val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ad7746_cap_filter_rate_table); i++)
		अगर (val >= ad7746_cap_filter_rate_table[i][0])
			अवरोध;

	अगर (i >= ARRAY_SIZE(ad7746_cap_filter_rate_table))
		i = ARRAY_SIZE(ad7746_cap_filter_rate_table) - 1;

	chip->config &= ~AD7746_CONF_CAPFS_MASK;
	chip->config |= i << AD7746_CONF_CAPFS_SHIFT;

	वापस 0;
पूर्ण

अटल पूर्णांक ad7746_store_vt_filter_rate_setup(काष्ठा ad7746_chip_info *chip,
					     पूर्णांक val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ad7746_vt_filter_rate_table); i++)
		अगर (val >= ad7746_vt_filter_rate_table[i][0])
			अवरोध;

	अगर (i >= ARRAY_SIZE(ad7746_vt_filter_rate_table))
		i = ARRAY_SIZE(ad7746_vt_filter_rate_table) - 1;

	chip->config &= ~AD7746_CONF_VTFS_MASK;
	chip->config |= i << AD7746_CONF_VTFS_SHIFT;

	वापस 0;
पूर्ण

अटल IIO_CONST_ATTR(in_voltage_sampling_frequency_available, "50 31 16 8");
अटल IIO_CONST_ATTR(in_capacitance_sampling_frequency_available,
		       "91 84 50 26 16 13 11 9");

अटल काष्ठा attribute *ad7746_attributes[] = अणु
	&iio_dev_attr_in_capacitance0_calibbias_calibration.dev_attr.attr,
	&iio_dev_attr_in_capacitance0_calibscale_calibration.dev_attr.attr,
	&iio_dev_attr_in_capacitance1_calibscale_calibration.dev_attr.attr,
	&iio_dev_attr_in_capacitance1_calibbias_calibration.dev_attr.attr,
	&iio_dev_attr_in_voltage0_calibscale_calibration.dev_attr.attr,
	&iio_स्थिर_attr_in_voltage_sampling_frequency_available.dev_attr.attr,
	&iio_स्थिर_attr_in_capacitance_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7746_attribute_group = अणु
	.attrs = ad7746_attributes,
पूर्ण;

अटल पूर्णांक ad7746_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val,
			    पूर्णांक val2,
			    दीर्घ mask)
अणु
	काष्ठा ad7746_chip_info *chip = iio_priv(indio_dev);
	पूर्णांक ret, reg;

	mutex_lock(&chip->lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (val != 1) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		val = (val2 * 1024) / 15625;

		चयन (chan->type) अणु
		हाल IIO_CAPACITANCE:
			reg = AD7746_REG_CAP_GAINH;
			अवरोध;
		हाल IIO_VOLTAGE:
			reg = AD7746_REG_VOLT_GAINH;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		ret = i2c_smbus_ग_लिखो_word_swapped(chip->client, reg, val);
		अगर (ret < 0)
			जाओ out;

		ret = 0;
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		अगर (val < 0 || val > 0xFFFF) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		ret = i2c_smbus_ग_लिखो_word_swapped(chip->client,
						   AD7746_REG_CAP_OFFH, val);
		अगर (ret < 0)
			जाओ out;

		ret = 0;
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		अगर (val < 0 || val > 43008000) अणु /* 21pF */
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		/*
		 * CAPDAC Scale = 21pF_typ / 127
		 * CIN Scale = 8.192pF / 2^24
		 * Offset Scale = CAPDAC Scale / CIN Scale = 338646
		 */

		val /= 338646;

		chip->capdac[chan->channel][chan->dअगरferential] = val > 0 ?
			AD7746_CAPDAC_DACP(val) | AD7746_CAPDAC_DACEN : 0;

		ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
						AD7746_REG_CAPDACA,
						chip->capdac[chan->channel][0]);
		अगर (ret < 0)
			जाओ out;
		ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
						AD7746_REG_CAPDACB,
						chip->capdac[chan->channel][1]);
		अगर (ret < 0)
			जाओ out;

		chip->capdac_set = chan->channel;

		ret = 0;
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (val2) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		चयन (chan->type) अणु
		हाल IIO_CAPACITANCE:
			ret = ad7746_store_cap_filter_rate_setup(chip, val);
			अवरोध;
		हाल IIO_VOLTAGE:
			ret = ad7746_store_vt_filter_rate_setup(chip, val);
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

out:
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ad7746_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2,
			   दीर्घ mask)
अणु
	काष्ठा ad7746_chip_info *chip = iio_priv(indio_dev);
	पूर्णांक ret, delay, idx;
	u8 regval, reg;

	mutex_lock(&chip->lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_PROCESSED:
		ret = ad7746_select_channel(indio_dev, chan);
		अगर (ret < 0)
			जाओ out;
		delay = ret;

		regval = chip->config | AD7746_CONF_MODE_SINGLE_CONV;
		ret = i2c_smbus_ग_लिखो_byte_data(chip->client, AD7746_REG_CFG,
						regval);
		अगर (ret < 0)
			जाओ out;

		msleep(delay);
		/* Now पढ़ो the actual रेजिस्टर */

		ret = i2c_smbus_पढ़ो_i2c_block_data(chip->client,
						    chan->address >> 8, 3,
						    &chip->data.d8[1]);

		अगर (ret < 0)
			जाओ out;

		*val = (be32_to_cpu(chip->data.d32) & 0xFFFFFF) - 0x800000;

		चयन (chan->type) अणु
		हाल IIO_TEMP:
		/*
		 * temperature in milli degrees Celsius
		 * T = ((*val / 2048) - 4096) * 1000
		 */
			*val = (*val * 125) / 256;
			अवरोध;
		हाल IIO_VOLTAGE:
			अगर (chan->channel == 1) /* supply_raw*/
				*val = *val * 6;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		चयन (chan->type) अणु
		हाल IIO_CAPACITANCE:
			reg = AD7746_REG_CAP_GAINH;
			अवरोध;
		हाल IIO_VOLTAGE:
			reg = AD7746_REG_VOLT_GAINH;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		ret = i2c_smbus_पढ़ो_word_swapped(chip->client, reg);
		अगर (ret < 0)
			जाओ out;
		/* 1 + gain_val / 2^16 */
		*val = 1;
		*val2 = (15625 * ret) / 1024;

		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		ret = i2c_smbus_पढ़ो_word_swapped(chip->client,
						  AD7746_REG_CAP_OFFH);
		अगर (ret < 0)
			जाओ out;
		*val = ret;

		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = AD7746_CAPDAC_DACP(chip->capdac[chan->channel]
					  [chan->dअगरferential]) * 338646;

		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_CAPACITANCE:
			/* 8.192pf / 2^24 */
			*val =  0;
			*val2 = 488;
			ret = IIO_VAL_INT_PLUS_न_अंकO;
			अवरोध;
		हाल IIO_VOLTAGE:
			/* 1170mV / 2^23 */
			*val = 1170;
			*val2 = 23;
			ret = IIO_VAL_FRACTIONAL_LOG2;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		चयन (chan->type) अणु
		हाल IIO_CAPACITANCE:
			idx = (chip->config & AD7746_CONF_CAPFS_MASK) >>
				AD7746_CONF_CAPFS_SHIFT;
			*val = ad7746_cap_filter_rate_table[idx][0];
			ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_VOLTAGE:
			idx = (chip->config & AD7746_CONF_VTFS_MASK) >>
				AD7746_CONF_VTFS_SHIFT;
			*val = ad7746_vt_filter_rate_table[idx][0];
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
out:
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info ad7746_info = अणु
	.attrs = &ad7746_attribute_group,
	.पढ़ो_raw = ad7746_पढ़ो_raw,
	.ग_लिखो_raw = ad7746_ग_लिखो_raw,
पूर्ण;

/*
 * device probe and हटाओ
 */

अटल पूर्णांक ad7746_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ad7746_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा ad7746_chip_info *chip;
	काष्ठा iio_dev *indio_dev;
	अचिन्हित अक्षर regval = 0;
	पूर्णांक ret = 0;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*chip));
	अगर (!indio_dev)
		वापस -ENOMEM;
	chip = iio_priv(indio_dev);
	mutex_init(&chip->lock);
	/* this is only used क्रम device removal purposes */
	i2c_set_clientdata(client, indio_dev);

	chip->client = client;
	chip->capdac_set = -1;

	indio_dev->name = id->name;
	indio_dev->info = &ad7746_info;
	indio_dev->channels = ad7746_channels;
	अगर (id->driver_data == 7746)
		indio_dev->num_channels = ARRAY_SIZE(ad7746_channels);
	अन्यथा
		indio_dev->num_channels =  ARRAY_SIZE(ad7746_channels) - 2;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	अगर (pdata) अणु
		अगर (pdata->exca_en) अणु
			अगर (pdata->exca_inv_en)
				regval |= AD7746_EXCSETUP_NEXCA;
			अन्यथा
				regval |= AD7746_EXCSETUP_EXCA;
		पूर्ण

		अगर (pdata->excb_en) अणु
			अगर (pdata->excb_inv_en)
				regval |= AD7746_EXCSETUP_NEXCB;
			अन्यथा
				regval |= AD7746_EXCSETUP_EXCB;
		पूर्ण

		regval |= AD7746_EXCSETUP_EXCLVL(pdata->exclvl);
	पूर्ण अन्यथा अणु
		dev_warn(&client->dev, "No platform data? using default\n");
		regval = AD7746_EXCSETUP_EXCA | AD7746_EXCSETUP_EXCB |
			AD7746_EXCSETUP_EXCLVL(3);
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
					AD7746_REG_EXC_SETUP, regval);
	अगर (ret < 0)
		वापस ret;

	ret = devm_iio_device_रेजिस्टर(indio_dev->dev.parent, indio_dev);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad7746_id[] = अणु
	अणु "ad7745", 7745 पूर्ण,
	अणु "ad7746", 7746 पूर्ण,
	अणु "ad7747", 7747 पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ad7746_id);

अटल स्थिर काष्ठा of_device_id ad7746_of_match[] = अणु
	अणु .compatible = "adi,ad7745" पूर्ण,
	अणु .compatible = "adi,ad7746" पूर्ण,
	अणु .compatible = "adi,ad7747" पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, ad7746_of_match);

अटल काष्ठा i2c_driver ad7746_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = ad7746_of_match,
	पूर्ण,
	.probe = ad7746_probe,
	.id_table = ad7746_id,
पूर्ण;
module_i2c_driver(ad7746_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7746/5/7 capacitive sensor driver");
MODULE_LICENSE("GPL v2");
