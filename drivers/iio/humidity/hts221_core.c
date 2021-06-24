<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics hts221 sensor driver
 *
 * Copyright 2016 STMicroelectronics Inc.
 *
 * Lorenzo Bianconi <lorenzo.bianconi@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bitfield.h>

#समावेश "hts221.h"

#घोषणा HTS221_REG_WHOAMI_ADDR		0x0f
#घोषणा HTS221_REG_WHOAMI_VAL		0xbc

#घोषणा HTS221_REG_CNTRL1_ADDR		0x20
#घोषणा HTS221_REG_CNTRL2_ADDR		0x21

#घोषणा HTS221_ODR_MASK			0x03
#घोषणा HTS221_BDU_MASK			BIT(2)
#घोषणा HTS221_ENABLE_MASK		BIT(7)

/* calibration रेजिस्टरs */
#घोषणा HTS221_REG_0RH_CAL_X_H		0x36
#घोषणा HTS221_REG_1RH_CAL_X_H		0x3a
#घोषणा HTS221_REG_0RH_CAL_Y_H		0x30
#घोषणा HTS221_REG_1RH_CAL_Y_H		0x31
#घोषणा HTS221_REG_0T_CAL_X_L		0x3c
#घोषणा HTS221_REG_1T_CAL_X_L		0x3e
#घोषणा HTS221_REG_0T_CAL_Y_H		0x32
#घोषणा HTS221_REG_1T_CAL_Y_H		0x33
#घोषणा HTS221_REG_T1_T0_CAL_Y_H	0x35

काष्ठा hts221_odr अणु
	u8 hz;
	u8 val;
पूर्ण;

#घोषणा HTS221_AVG_DEPTH		8
काष्ठा hts221_avg अणु
	u8 addr;
	u8 mask;
	u16 avg_avl[HTS221_AVG_DEPTH];
पूर्ण;

अटल स्थिर काष्ठा hts221_odr hts221_odr_table[] = अणु
	अणु  1, 0x01 पूर्ण,	/* 1Hz */
	अणु  7, 0x02 पूर्ण,	/* 7Hz */
	अणु 13, 0x03 पूर्ण,	/* 12.5Hz */
पूर्ण;

अटल स्थिर काष्ठा hts221_avg hts221_avg_list[] = अणु
	अणु
		.addr = 0x10,
		.mask = 0x07,
		.avg_avl = अणु
			4, /* 0.4 %RH */
			8, /* 0.3 %RH */
			16, /* 0.2 %RH */
			32, /* 0.15 %RH */
			64, /* 0.1 %RH */
			128, /* 0.07 %RH */
			256, /* 0.05 %RH */
			512, /* 0.03 %RH */
		पूर्ण,
	पूर्ण,
	अणु
		.addr = 0x10,
		.mask = 0x38,
		.avg_avl = अणु
			2, /* 0.08 degC */
			4, /* 0.05 degC */
			8, /* 0.04 degC */
			16, /* 0.03 degC */
			32, /* 0.02 degC */
			64, /* 0.015 degC */
			128, /* 0.01 degC */
			256, /* 0.007 degC */
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec hts221_channels[] = अणु
	अणु
		.type = IIO_HUMIDITYRELATIVE,
		.address = 0x28,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_OFFSET) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_LE,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.address = 0x2a,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_OFFSET) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.scan_index = 1,
		.scan_type = अणु
			.sign = 's',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_LE,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(2),
पूर्ण;

अटल पूर्णांक hts221_check_whoami(काष्ठा hts221_hw *hw)
अणु
	पूर्णांक err, data;

	err = regmap_पढ़ो(hw->regmap, HTS221_REG_WHOAMI_ADDR, &data);
	अगर (err < 0) अणु
		dev_err(hw->dev, "failed to read whoami register\n");
		वापस err;
	पूर्ण

	अगर (data != HTS221_REG_WHOAMI_VAL) अणु
		dev_err(hw->dev, "wrong whoami {%02x vs %02x}\n",
			data, HTS221_REG_WHOAMI_VAL);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hts221_update_odr(काष्ठा hts221_hw *hw, u8 odr)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < ARRAY_SIZE(hts221_odr_table); i++)
		अगर (hts221_odr_table[i].hz == odr)
			अवरोध;

	अगर (i == ARRAY_SIZE(hts221_odr_table))
		वापस -EINVAL;

	err = regmap_update_bits(hw->regmap, HTS221_REG_CNTRL1_ADDR,
				 HTS221_ODR_MASK,
				 FIELD_PREP(HTS221_ODR_MASK,
					    hts221_odr_table[i].val));
	अगर (err < 0)
		वापस err;

	hw->odr = odr;

	वापस 0;
पूर्ण

अटल पूर्णांक hts221_update_avg(काष्ठा hts221_hw *hw,
			     क्रमागत hts221_sensor_type type,
			     u16 val)
अणु
	स्थिर काष्ठा hts221_avg *avg = &hts221_avg_list[type];
	पूर्णांक i, err, data;

	क्रम (i = 0; i < HTS221_AVG_DEPTH; i++)
		अगर (avg->avg_avl[i] == val)
			अवरोध;

	अगर (i == HTS221_AVG_DEPTH)
		वापस -EINVAL;

	data = ((i << __ffs(avg->mask)) & avg->mask);
	err = regmap_update_bits(hw->regmap, avg->addr,
				 avg->mask, data);
	अगर (err < 0)
		वापस err;

	hw->sensors[type].cur_avg_idx = i;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार hts221_sysfs_sampling_freq(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	पूर्णांक i;
	sमाप_प्रकार len = 0;

	क्रम (i = 0; i < ARRAY_SIZE(hts221_odr_table); i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d ",
				 hts221_odr_table[i].hz);
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार
hts221_sysfs_rh_oversampling_avail(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	स्थिर काष्ठा hts221_avg *avg = &hts221_avg_list[HTS221_SENSOR_H];
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(avg->avg_avl); i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d ",
				 avg->avg_avl[i]);
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार
hts221_sysfs_temp_oversampling_avail(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	स्थिर काष्ठा hts221_avg *avg = &hts221_avg_list[HTS221_SENSOR_T];
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(avg->avg_avl); i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d ",
				 avg->avg_avl[i]);
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

पूर्णांक hts221_set_enable(काष्ठा hts221_hw *hw, bool enable)
अणु
	पूर्णांक err;

	err = regmap_update_bits(hw->regmap, HTS221_REG_CNTRL1_ADDR,
				 HTS221_ENABLE_MASK,
				 FIELD_PREP(HTS221_ENABLE_MASK, enable));
	अगर (err < 0)
		वापस err;

	hw->enabled = enable;

	वापस 0;
पूर्ण

अटल पूर्णांक hts221_parse_temp_caldata(काष्ठा hts221_hw *hw)
अणु
	पूर्णांक err, *slope, *b_gen, cal0, cal1;
	s16 cal_x0, cal_x1, cal_y0, cal_y1;
	__le16 val;

	err = regmap_पढ़ो(hw->regmap, HTS221_REG_0T_CAL_Y_H, &cal0);
	अगर (err < 0)
		वापस err;

	err = regmap_पढ़ो(hw->regmap, HTS221_REG_T1_T0_CAL_Y_H, &cal1);
	अगर (err < 0)
		वापस err;
	cal_y0 = ((cal1 & 0x3) << 8) | cal0;

	err = regmap_पढ़ो(hw->regmap, HTS221_REG_1T_CAL_Y_H, &cal0);
	अगर (err < 0)
		वापस err;
	cal_y1 = (((cal1 & 0xc) >> 2) << 8) | cal0;

	err = regmap_bulk_पढ़ो(hw->regmap, HTS221_REG_0T_CAL_X_L,
			       &val, माप(val));
	अगर (err < 0)
		वापस err;
	cal_x0 = le16_to_cpu(val);

	err = regmap_bulk_पढ़ो(hw->regmap, HTS221_REG_1T_CAL_X_L,
			       &val, माप(val));
	अगर (err < 0)
		वापस err;
	cal_x1 = le16_to_cpu(val);

	slope = &hw->sensors[HTS221_SENSOR_T].slope;
	b_gen = &hw->sensors[HTS221_SENSOR_T].b_gen;

	*slope = ((cal_y1 - cal_y0) * 8000) / (cal_x1 - cal_x0);
	*b_gen = (((s32)cal_x1 * cal_y0 - (s32)cal_x0 * cal_y1) * 1000) /
		 (cal_x1 - cal_x0);
	*b_gen *= 8;

	वापस 0;
पूर्ण

अटल पूर्णांक hts221_parse_rh_caldata(काष्ठा hts221_hw *hw)
अणु
	पूर्णांक err, *slope, *b_gen, data;
	s16 cal_x0, cal_x1, cal_y0, cal_y1;
	__le16 val;

	err = regmap_पढ़ो(hw->regmap, HTS221_REG_0RH_CAL_Y_H, &data);
	अगर (err < 0)
		वापस err;
	cal_y0 = data;

	err = regmap_पढ़ो(hw->regmap, HTS221_REG_1RH_CAL_Y_H, &data);
	अगर (err < 0)
		वापस err;
	cal_y1 = data;

	err = regmap_bulk_पढ़ो(hw->regmap, HTS221_REG_0RH_CAL_X_H,
			       &val, माप(val));
	अगर (err < 0)
		वापस err;
	cal_x0 = le16_to_cpu(val);

	err = regmap_bulk_पढ़ो(hw->regmap, HTS221_REG_1RH_CAL_X_H,
			       &val, माप(val));
	अगर (err < 0)
		वापस err;
	cal_x1 = le16_to_cpu(val);

	slope = &hw->sensors[HTS221_SENSOR_H].slope;
	b_gen = &hw->sensors[HTS221_SENSOR_H].b_gen;

	*slope = ((cal_y1 - cal_y0) * 8000) / (cal_x1 - cal_x0);
	*b_gen = (((s32)cal_x1 * cal_y0 - (s32)cal_x0 * cal_y1) * 1000) /
		 (cal_x1 - cal_x0);
	*b_gen *= 8;

	वापस 0;
पूर्ण

अटल पूर्णांक hts221_get_sensor_scale(काष्ठा hts221_hw *hw,
				   क्रमागत iio_chan_type ch_type,
				   पूर्णांक *val, पूर्णांक *val2)
अणु
	s64 पंचांगp;
	s32 rem, भाग, data;

	चयन (ch_type) अणु
	हाल IIO_HUMIDITYRELATIVE:
		data = hw->sensors[HTS221_SENSOR_H].slope;
		भाग = (1 << 4) * 1000;
		अवरोध;
	हाल IIO_TEMP:
		data = hw->sensors[HTS221_SENSOR_T].slope;
		भाग = (1 << 6) * 1000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	पंचांगp = भाग_s64(data * 1000000000LL, भाग);
	पंचांगp = भाग_s64_rem(पंचांगp, 1000000000LL, &rem);

	*val = पंचांगp;
	*val2 = rem;

	वापस IIO_VAL_INT_PLUS_न_अंकO;
पूर्ण

अटल पूर्णांक hts221_get_sensor_offset(काष्ठा hts221_hw *hw,
				    क्रमागत iio_chan_type ch_type,
				    पूर्णांक *val, पूर्णांक *val2)
अणु
	s64 पंचांगp;
	s32 rem, भाग, data;

	चयन (ch_type) अणु
	हाल IIO_HUMIDITYRELATIVE:
		data = hw->sensors[HTS221_SENSOR_H].b_gen;
		भाग = hw->sensors[HTS221_SENSOR_H].slope;
		अवरोध;
	हाल IIO_TEMP:
		data = hw->sensors[HTS221_SENSOR_T].b_gen;
		भाग = hw->sensors[HTS221_SENSOR_T].slope;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	पंचांगp = भाग_s64(data * 1000000000LL, भाग);
	पंचांगp = भाग_s64_rem(पंचांगp, 1000000000LL, &rem);

	*val = पंचांगp;
	*val2 = rem;

	वापस IIO_VAL_INT_PLUS_न_अंकO;
पूर्ण

अटल पूर्णांक hts221_पढ़ो_oneshot(काष्ठा hts221_hw *hw, u8 addr, पूर्णांक *val)
अणु
	__le16 data;
	पूर्णांक err;

	err = hts221_set_enable(hw, true);
	अगर (err < 0)
		वापस err;

	msleep(50);

	err = regmap_bulk_पढ़ो(hw->regmap, addr, &data, माप(data));
	अगर (err < 0)
		वापस err;

	hts221_set_enable(hw, false);

	*val = (s16)le16_to_cpu(data);

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक hts221_पढ़ो_raw(काष्ठा iio_dev *iio_dev,
			   काष्ठा iio_chan_spec स्थिर *ch,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा hts221_hw *hw = iio_priv(iio_dev);
	पूर्णांक ret;

	ret = iio_device_claim_direct_mode(iio_dev);
	अगर (ret)
		वापस ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = hts221_पढ़ो_oneshot(hw, ch->address, val);
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		ret = hts221_get_sensor_scale(hw, ch->type, val, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		ret = hts221_get_sensor_offset(hw, ch->type, val, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = hw->odr;
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO: अणु
		u8 idx;
		स्थिर काष्ठा hts221_avg *avg;

		चयन (ch->type) अणु
		हाल IIO_HUMIDITYRELATIVE:
			avg = &hts221_avg_list[HTS221_SENSOR_H];
			idx = hw->sensors[HTS221_SENSOR_H].cur_avg_idx;
			*val = avg->avg_avl[idx];
			ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_TEMP:
			avg = &hts221_avg_list[HTS221_SENSOR_T];
			idx = hw->sensors[HTS221_SENSOR_T].cur_avg_idx;
			*val = avg->avg_avl[idx];
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	iio_device_release_direct_mode(iio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक hts221_ग_लिखो_raw(काष्ठा iio_dev *iio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा hts221_hw *hw = iio_priv(iio_dev);
	पूर्णांक ret;

	ret = iio_device_claim_direct_mode(iio_dev);
	अगर (ret)
		वापस ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = hts221_update_odr(hw, val);
		अवरोध;
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		चयन (chan->type) अणु
		हाल IIO_HUMIDITYRELATIVE:
			ret = hts221_update_avg(hw, HTS221_SENSOR_H, val);
			अवरोध;
		हाल IIO_TEMP:
			ret = hts221_update_avg(hw, HTS221_SENSOR_T, val);
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	iio_device_release_direct_mode(iio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक hts221_validate_trigger(काष्ठा iio_dev *iio_dev,
				   काष्ठा iio_trigger *trig)
अणु
	काष्ठा hts221_hw *hw = iio_priv(iio_dev);

	वापस hw->trig == trig ? 0 : -EINVAL;
पूर्ण

अटल IIO_DEVICE_ATTR(in_humidity_oversampling_ratio_available, S_IRUGO,
		       hts221_sysfs_rh_oversampling_avail, शून्य, 0);
अटल IIO_DEVICE_ATTR(in_temp_oversampling_ratio_available, S_IRUGO,
		       hts221_sysfs_temp_oversampling_avail, शून्य, 0);
अटल IIO_DEV_ATTR_SAMP_FREQ_AVAIL(hts221_sysfs_sampling_freq);

अटल काष्ठा attribute *hts221_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_in_humidity_oversampling_ratio_available.dev_attr.attr,
	&iio_dev_attr_in_temp_oversampling_ratio_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hts221_attribute_group = अणु
	.attrs = hts221_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info hts221_info = अणु
	.attrs = &hts221_attribute_group,
	.पढ़ो_raw = hts221_पढ़ो_raw,
	.ग_लिखो_raw = hts221_ग_लिखो_raw,
	.validate_trigger = hts221_validate_trigger,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ hts221_scan_masks[] = अणु0x3, 0x0पूर्ण;

अटल पूर्णांक hts221_init_regulators(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *iio_dev = dev_get_drvdata(dev);
	काष्ठा hts221_hw *hw = iio_priv(iio_dev);
	पूर्णांक err;

	hw->vdd = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(hw->vdd))
		वापस dev_err_probe(dev, PTR_ERR(hw->vdd),
				     "failed to get vdd regulator\n");

	err = regulator_enable(hw->vdd);
	अगर (err) अणु
		dev_err(dev, "failed to enable vdd regulator: %d\n", err);
		वापस err;
	पूर्ण

	msleep(50);

	वापस 0;
पूर्ण

अटल व्योम hts221_chip_uninit(व्योम *data)
अणु
	काष्ठा hts221_hw *hw = data;

	regulator_disable(hw->vdd);
पूर्ण

पूर्णांक hts221_probe(काष्ठा device *dev, पूर्णांक irq, स्थिर अक्षर *name,
		 काष्ठा regmap *regmap)
अणु
	काष्ठा iio_dev *iio_dev;
	काष्ठा hts221_hw *hw;
	पूर्णांक err;
	u8 data;

	iio_dev = devm_iio_device_alloc(dev, माप(*hw));
	अगर (!iio_dev)
		वापस -ENOMEM;

	dev_set_drvdata(dev, (व्योम *)iio_dev);

	hw = iio_priv(iio_dev);
	hw->name = name;
	hw->dev = dev;
	hw->irq = irq;
	hw->regmap = regmap;

	err = hts221_init_regulators(dev);
	अगर (err)
		वापस err;

	err = devm_add_action_or_reset(dev, hts221_chip_uninit, hw);
	अगर (err)
		वापस err;

	err = hts221_check_whoami(hw);
	अगर (err < 0)
		वापस err;

	iio_dev->modes = INDIO_सूचीECT_MODE;
	iio_dev->available_scan_masks = hts221_scan_masks;
	iio_dev->channels = hts221_channels;
	iio_dev->num_channels = ARRAY_SIZE(hts221_channels);
	iio_dev->name = HTS221_DEV_NAME;
	iio_dev->info = &hts221_info;

	/* enable Block Data Update */
	err = regmap_update_bits(hw->regmap, HTS221_REG_CNTRL1_ADDR,
				 HTS221_BDU_MASK,
				 FIELD_PREP(HTS221_BDU_MASK, 1));
	अगर (err < 0)
		वापस err;

	err = hts221_update_odr(hw, hts221_odr_table[0].hz);
	अगर (err < 0)
		वापस err;

	/* configure humidity sensor */
	err = hts221_parse_rh_caldata(hw);
	अगर (err < 0) अणु
		dev_err(hw->dev, "failed to get rh calibration data\n");
		वापस err;
	पूर्ण

	data = hts221_avg_list[HTS221_SENSOR_H].avg_avl[3];
	err = hts221_update_avg(hw, HTS221_SENSOR_H, data);
	अगर (err < 0) अणु
		dev_err(hw->dev, "failed to set rh oversampling ratio\n");
		वापस err;
	पूर्ण

	/* configure temperature sensor */
	err = hts221_parse_temp_caldata(hw);
	अगर (err < 0) अणु
		dev_err(hw->dev,
			"failed to get temperature calibration data\n");
		वापस err;
	पूर्ण

	data = hts221_avg_list[HTS221_SENSOR_T].avg_avl[3];
	err = hts221_update_avg(hw, HTS221_SENSOR_T, data);
	अगर (err < 0) अणु
		dev_err(hw->dev,
			"failed to set temperature oversampling ratio\n");
		वापस err;
	पूर्ण

	अगर (hw->irq > 0) अणु
		err = hts221_allocate_buffers(iio_dev);
		अगर (err < 0)
			वापस err;

		err = hts221_allocate_trigger(iio_dev);
		अगर (err)
			वापस err;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(hw->dev, iio_dev);
पूर्ण
EXPORT_SYMBOL(hts221_probe);

अटल पूर्णांक __maybe_unused hts221_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *iio_dev = dev_get_drvdata(dev);
	काष्ठा hts221_hw *hw = iio_priv(iio_dev);

	वापस regmap_update_bits(hw->regmap, HTS221_REG_CNTRL1_ADDR,
				  HTS221_ENABLE_MASK,
				  FIELD_PREP(HTS221_ENABLE_MASK, false));
पूर्ण

अटल पूर्णांक __maybe_unused hts221_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *iio_dev = dev_get_drvdata(dev);
	काष्ठा hts221_hw *hw = iio_priv(iio_dev);
	पूर्णांक err = 0;

	अगर (hw->enabled)
		err = regmap_update_bits(hw->regmap, HTS221_REG_CNTRL1_ADDR,
					 HTS221_ENABLE_MASK,
					 FIELD_PREP(HTS221_ENABLE_MASK,
						    true));
	वापस err;
पूर्ण

स्थिर काष्ठा dev_pm_ops hts221_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(hts221_suspend, hts221_resume)
पूर्ण;
EXPORT_SYMBOL(hts221_pm_ops);

MODULE_AUTHOR("Lorenzo Bianconi <lorenzo.bianconi@st.com>");
MODULE_DESCRIPTION("STMicroelectronics hts221 sensor driver");
MODULE_LICENSE("GPL v2");
