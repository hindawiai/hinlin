<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* max31856.c
 *
 * Maxim MAX31856 thermocouple sensor driver
 *
 * Copyright (C) 2018-2019 Rockwell Collins
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/util_macros.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <dt-bindings/iio/temperature/thermocouple.h>
/*
 * The MSB of the रेजिस्टर value determines whether the following byte will
 * be written or पढ़ो. If it is 0, one or more byte पढ़ोs will follow.
 */
#घोषणा MAX31856_RD_WR_BIT         BIT(7)

#घोषणा MAX31856_CR0_AUTOCONVERT   BIT(7)
#घोषणा MAX31856_CR0_1SHOT         BIT(6)
#घोषणा MAX31856_CR0_OCFAULT       BIT(4)
#घोषणा MAX31856_CR0_OCFAULT_MASK  GENMASK(5, 4)
#घोषणा MAX31856_CR0_FILTER_50HZ   BIT(0)
#घोषणा MAX31856_AVERAGING_MASK    GENMASK(6, 4)
#घोषणा MAX31856_AVERAGING_SHIFT   4
#घोषणा MAX31856_TC_TYPE_MASK      GENMASK(3, 0)
#घोषणा MAX31856_FAULT_OVUV        BIT(1)
#घोषणा MAX31856_FAULT_OPEN        BIT(0)

/* The MAX31856 रेजिस्टरs */
#घोषणा MAX31856_CR0_REG           0x00
#घोषणा MAX31856_CR1_REG           0x01
#घोषणा MAX31856_MASK_REG          0x02
#घोषणा MAX31856_CJHF_REG          0x03
#घोषणा MAX31856_CJLF_REG          0x04
#घोषणा MAX31856_LTHFTH_REG        0x05
#घोषणा MAX31856_LTHFTL_REG        0x06
#घोषणा MAX31856_LTLFTH_REG        0x07
#घोषणा MAX31856_LTLFTL_REG        0x08
#घोषणा MAX31856_CJTO_REG          0x09
#घोषणा MAX31856_CJTH_REG          0x0A
#घोषणा MAX31856_CJTL_REG          0x0B
#घोषणा MAX31856_LTCBH_REG         0x0C
#घोषणा MAX31856_LTCBM_REG         0x0D
#घोषणा MAX31856_LTCBL_REG         0x0E
#घोषणा MAX31856_SR_REG            0x0F

अटल स्थिर काष्ठा iio_chan_spec max31856_channels[] = अणु
	अणु	/* Thermocouple Temperature */
		.type = IIO_TEMP,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_THERMOCOUPLE_TYPE),
		.info_mask_shared_by_type =
			BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO)
	पूर्ण,
	अणु	/* Cold Junction Temperature */
		.type = IIO_TEMP,
		.channel2 = IIO_MOD_TEMP_AMBIENT,
		.modअगरied = 1,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_type =
			BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO)
	पूर्ण,
पूर्ण;

काष्ठा max31856_data अणु
	काष्ठा spi_device *spi;
	u32 thermocouple_type;
	bool filter_50hz;
	पूर्णांक averaging;
पूर्ण;

अटल स्थिर अक्षर max31856_tc_types[] = अणु
	'B', 'E', 'J', 'K', 'N', 'R', 'S', 'T'
पूर्ण;

अटल पूर्णांक max31856_पढ़ो(काष्ठा max31856_data *data, u8 reg,
			 u8 val[], अचिन्हित पूर्णांक पढ़ो_size)
अणु
	वापस spi_ग_लिखो_then_पढ़ो(data->spi, &reg, 1, val, पढ़ो_size);
पूर्ण

अटल पूर्णांक max31856_ग_लिखो(काष्ठा max31856_data *data, u8 reg,
			  अचिन्हित पूर्णांक val)
अणु
	u8 buf[2];

	buf[0] = reg | (MAX31856_RD_WR_BIT);
	buf[1] = val;

	वापस spi_ग_लिखो(data->spi, buf, 2);
पूर्ण

अटल पूर्णांक max31856_init(काष्ठा max31856_data *data)
अणु
	पूर्णांक ret;
	u8 reg_cr0_val, reg_cr1_val;

	/* Start by changing to Off mode beक्रमe making changes as
	 * some settings are recommended to be set only when the device
	 * is off
	 */
	ret = max31856_पढ़ो(data, MAX31856_CR0_REG, &reg_cr0_val, 1);
	अगर (ret)
		वापस ret;

	reg_cr0_val &= ~MAX31856_CR0_AUTOCONVERT;
	ret = max31856_ग_लिखो(data, MAX31856_CR0_REG, reg_cr0_val);
	अगर (ret)
		वापस ret;

	/* Set thermocouple type based on dts property */
	ret = max31856_पढ़ो(data, MAX31856_CR1_REG, &reg_cr1_val, 1);
	अगर (ret)
		वापस ret;

	reg_cr1_val &= ~MAX31856_TC_TYPE_MASK;
	reg_cr1_val |= data->thermocouple_type;

	reg_cr1_val &= ~MAX31856_AVERAGING_MASK;
	reg_cr1_val |= data->averaging << MAX31856_AVERAGING_SHIFT;

	ret = max31856_ग_लिखो(data, MAX31856_CR1_REG, reg_cr1_val);
	अगर (ret)
		वापस ret;

	/*
	 * Enable Open circuit fault detection
	 * Read datasheet क्रम more inक्रमmation: Table 4.
	 * Value 01 means : Enabled (Once every 16 conversions)
	 */
	reg_cr0_val &= ~MAX31856_CR0_OCFAULT_MASK;
	reg_cr0_val |= MAX31856_CR0_OCFAULT;

	/* Set Auto Conversion Mode */
	reg_cr0_val &= ~MAX31856_CR0_1SHOT;
	reg_cr0_val |= MAX31856_CR0_AUTOCONVERT;

	अगर (data->filter_50hz)
		reg_cr0_val |= MAX31856_CR0_FILTER_50HZ;
	अन्यथा
		reg_cr0_val &= ~MAX31856_CR0_FILTER_50HZ;

	वापस max31856_ग_लिखो(data, MAX31856_CR0_REG, reg_cr0_val);
पूर्ण

अटल पूर्णांक max31856_thermocouple_पढ़ो(काष्ठा max31856_data *data,
				      काष्ठा iio_chan_spec स्थिर *chan,
				      पूर्णांक *val)
अणु
	पूर्णांक ret, offset_cjto;
	u8 reg_val[3];

	चयन (chan->channel2) अणु
	हाल IIO_NO_MOD:
		/*
		 * Multibyte Read
		 * MAX31856_LTCBH_REG, MAX31856_LTCBM_REG, MAX31856_LTCBL_REG
		 */
		ret = max31856_पढ़ो(data, MAX31856_LTCBH_REG, reg_val, 3);
		अगर (ret)
			वापस ret;
		/* Skip last 5 dead bits of LTCBL */
		*val = get_unaligned_be24(&reg_val[0]) >> 5;
		/* Check 7th bit of LTCBH reg. value क्रम sign*/
		अगर (reg_val[0] & 0x80)
			*val -= 0x80000;
		अवरोध;

	हाल IIO_MOD_TEMP_AMBIENT:
		/*
		 * Multibyte Read
		 * MAX31856_CJTO_REG, MAX31856_CJTH_REG, MAX31856_CJTL_REG
		 */
		ret = max31856_पढ़ो(data, MAX31856_CJTO_REG, reg_val, 3);
		अगर (ret)
			वापस ret;
		/* Get Cold Junction Temp. offset रेजिस्टर value */
		offset_cjto = reg_val[0];
		/* Get CJTH and CJTL value and skip last 2 dead bits of CJTL */
		*val = get_unaligned_be16(&reg_val[1]) >> 2;
		/* As per datasheet add offset पूर्णांकo CJTH and CJTL */
		*val += offset_cjto;
		/* Check 7th bit of CJTH reg. value क्रम sign */
		अगर (reg_val[1] & 0x80)
			*val -= 0x4000;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = max31856_पढ़ो(data, MAX31856_SR_REG, reg_val, 1);
	अगर (ret)
		वापस ret;
	/* Check क्रम over/under voltage or खोलो circuit fault */
	अगर (reg_val[0] & (MAX31856_FAULT_OVUV | MAX31856_FAULT_OPEN))
		वापस -EIO;

	वापस ret;
पूर्ण

अटल पूर्णांक max31856_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा max31856_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = max31856_thermocouple_पढ़ो(data, chan, val);
		अगर (ret)
			वापस ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->channel2) अणु
		हाल IIO_MOD_TEMP_AMBIENT:
			/* Cold junction Temp. Data resolution is 0.015625 */
			*val = 15;
			*val2 = 625000; /* 1000 * 0.015625 */
			ret = IIO_VAL_INT_PLUS_MICRO;
			अवरोध;
		शेष:
			/* Thermocouple Temp. Data resolution is 0.0078125 */
			*val = 7;
			*val2 = 812500; /* 1000 * 0.0078125) */
			वापस IIO_VAL_INT_PLUS_MICRO;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		*val = 1 << data->averaging;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_THERMOCOUPLE_TYPE:
		*val = max31856_tc_types[data->thermocouple_type];
		वापस IIO_VAL_CHAR;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक max31856_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				      काष्ठा iio_chan_spec स्थिर *chan,
				      दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_THERMOCOUPLE_TYPE:
		वापस IIO_VAL_CHAR;
	शेष:
		वापस IIO_VAL_INT;
	पूर्ण
पूर्ण

अटल पूर्णांक max31856_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा max31856_data *data = iio_priv(indio_dev);
	पूर्णांक msb;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		अगर (val > 16 || val < 1)
			वापस -EINVAL;
		msb = fls(val) - 1;
		/* Round up to next 2घात अगर needed */
		अगर (BIT(msb) < val)
			msb++;

		data->averaging = msb;
		max31856_init(data);
		अवरोध;
	हाल IIO_CHAN_INFO_THERMOCOUPLE_TYPE:
	अणु
		पूर्णांक tc_type = -1;
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(max31856_tc_types); i++) अणु
			अगर (max31856_tc_types[i] == बड़े(val)) अणु
				tc_type = i;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (tc_type < 0)
			वापस -EINVAL;

		data->thermocouple_type = tc_type;
		max31856_init(data);
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_fault(काष्ठा device *dev, u8 faultbit, अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा max31856_data *data = iio_priv(indio_dev);
	u8 reg_val;
	पूर्णांक ret;
	bool fault;

	ret = max31856_पढ़ो(data, MAX31856_SR_REG, &reg_val, 1);
	अगर (ret)
		वापस ret;

	fault = reg_val & faultbit;

	वापस प्र_लिखो(buf, "%d\n", fault);
पूर्ण

अटल sमाप_प्रकार show_fault_ovuv(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	वापस show_fault(dev, MAX31856_FAULT_OVUV, buf);
पूर्ण

अटल sमाप_प्रकार show_fault_oc(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	वापस show_fault(dev, MAX31856_FAULT_OPEN, buf);
पूर्ण

अटल sमाप_प्रकार show_filter(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा max31856_data *data = iio_priv(indio_dev);

	वापस प्र_लिखो(buf, "%d\n", data->filter_50hz ? 50 : 60);
पूर्ण

अटल sमाप_प्रकार set_filter(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf,
			  माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा max31856_data *data = iio_priv(indio_dev);
	अचिन्हित पूर्णांक freq;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 10, &freq);
	अगर (ret)
		वापस ret;

	चयन (freq) अणु
	हाल 50:
		data->filter_50hz = true;
		अवरोध;
	हाल 60:
		data->filter_50hz = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	max31856_init(data);
	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(fault_ovuv, 0444, show_fault_ovuv, शून्य, 0);
अटल IIO_DEVICE_ATTR(fault_oc, 0444, show_fault_oc, शून्य, 0);
अटल IIO_DEVICE_ATTR(in_temp_filter_notch_center_frequency, 0644,
		       show_filter, set_filter, 0);

अटल काष्ठा attribute *max31856_attributes[] = अणु
	&iio_dev_attr_fault_ovuv.dev_attr.attr,
	&iio_dev_attr_fault_oc.dev_attr.attr,
	&iio_dev_attr_in_temp_filter_notch_center_frequency.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group max31856_group = अणु
	.attrs = max31856_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info max31856_info = अणु
	.पढ़ो_raw = max31856_पढ़ो_raw,
	.ग_लिखो_raw = max31856_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = max31856_ग_लिखो_raw_get_fmt,
	.attrs = &max31856_group,
पूर्ण;

अटल पूर्णांक max31856_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा iio_dev *indio_dev;
	काष्ठा max31856_data *data;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->spi = spi;
	data->filter_50hz = false;

	spi_set_drvdata(spi, indio_dev);

	indio_dev->info = &max31856_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = max31856_channels;
	indio_dev->num_channels = ARRAY_SIZE(max31856_channels);

	ret = of_property_पढ़ो_u32(spi->dev.of_node, "thermocouple-type",
				   &data->thermocouple_type);

	अगर (ret) अणु
		dev_info(&spi->dev,
			 "Could not read thermocouple type DT property, configuring as a K-Type\n");
		data->thermocouple_type = THERMOCOUPLE_TYPE_K;
	पूर्ण

	/*
	 * no need to translate values as the supported types
	 * have the same value as the #घोषणाs
	 */
	चयन (data->thermocouple_type) अणु
	हाल THERMOCOUPLE_TYPE_B:
	हाल THERMOCOUPLE_TYPE_E:
	हाल THERMOCOUPLE_TYPE_J:
	हाल THERMOCOUPLE_TYPE_K:
	हाल THERMOCOUPLE_TYPE_N:
	हाल THERMOCOUPLE_TYPE_R:
	हाल THERMOCOUPLE_TYPE_S:
	हाल THERMOCOUPLE_TYPE_T:
		अवरोध;
	शेष:
		dev_err(&spi->dev,
			"error: thermocouple-type %u not supported by max31856\n"
			, data->thermocouple_type);
		वापस -EINVAL;
	पूर्ण

	ret = max31856_init(data);
	अगर (ret) अणु
		dev_err(&spi->dev, "error: Failed to configure max31856\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id max31856_id[] = अणु
	अणु "max31856", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, max31856_id);

अटल स्थिर काष्ठा of_device_id max31856_of_match[] = अणु
	अणु .compatible = "maxim,max31856" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max31856_of_match);

अटल काष्ठा spi_driver max31856_driver = अणु
	.driver = अणु
		.name = "max31856",
		.of_match_table = max31856_of_match,
	पूर्ण,
	.probe = max31856_probe,
	.id_table = max31856_id,
पूर्ण;
module_spi_driver(max31856_driver);

MODULE_AUTHOR("Paresh Chaudhary <paresh.chaudhary@rockwellcollins.com>");
MODULE_AUTHOR("Patrick Havelange <patrick.havelange@essensium.com>");
MODULE_DESCRIPTION("Maxim MAX31856 thermocouple sensor driver");
MODULE_LICENSE("GPL");
