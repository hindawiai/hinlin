<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AD5446 SPI DAC driver
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/list.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा MODE_PWRDWN_1k		0x1
#घोषणा MODE_PWRDWN_100k	0x2
#घोषणा MODE_PWRDWN_TRISTATE	0x3

/**
 * काष्ठा ad5446_state - driver instance specअगरic data
 * @dev:		this device
 * @chip_info:		chip model specअगरic स्थिरants, available modes etc
 * @reg:		supply regulator
 * @vref_mv:		actual reference voltage used
 * @cached_val:		store/retrieve values during घातer करोwn
 * @pwr_करोwn_mode:	घातer करोwn mode (1k, 100k or tristate)
 * @pwr_करोwn:		true अगर the device is in घातer करोwn
 * @lock:		lock to protect the data buffer during ग_लिखो ops
 */

काष्ठा ad5446_state अणु
	काष्ठा device		*dev;
	स्थिर काष्ठा ad5446_chip_info	*chip_info;
	काष्ठा regulator		*reg;
	अचिन्हित लघु			vref_mv;
	अचिन्हित			cached_val;
	अचिन्हित			pwr_करोwn_mode;
	अचिन्हित			pwr_करोwn;
	काष्ठा mutex			lock;
पूर्ण;

/**
 * काष्ठा ad5446_chip_info - chip specअगरic inक्रमmation
 * @channel:		channel spec क्रम the DAC
 * @पूर्णांक_vref_mv:	AD5620/40/60: the पूर्णांकernal reference voltage
 * @ग_लिखो:		chip specअगरic helper function to ग_लिखो to the रेजिस्टर
 */

काष्ठा ad5446_chip_info अणु
	काष्ठा iio_chan_spec	channel;
	u16			पूर्णांक_vref_mv;
	पूर्णांक			(*ग_लिखो)(काष्ठा ad5446_state *st, अचिन्हित val);
पूर्ण;

अटल स्थिर अक्षर * स्थिर ad5446_घातerकरोwn_modes[] = अणु
	"1kohm_to_gnd", "100kohm_to_gnd", "three_state"
पूर्ण;

अटल पूर्णांक ad5446_set_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ad5446_state *st = iio_priv(indio_dev);

	st->pwr_करोwn_mode = mode + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ad5446_get_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा ad5446_state *st = iio_priv(indio_dev);

	वापस st->pwr_करोwn_mode - 1;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत ad5446_घातerकरोwn_mode_क्रमागत = अणु
	.items = ad5446_घातerकरोwn_modes,
	.num_items = ARRAY_SIZE(ad5446_घातerकरोwn_modes),
	.get = ad5446_get_घातerकरोwn_mode,
	.set = ad5446_set_घातerकरोwn_mode,
पूर्ण;

अटल sमाप_प्रकार ad5446_पढ़ो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
					   uपूर्णांकptr_t निजी,
					   स्थिर काष्ठा iio_chan_spec *chan,
					   अक्षर *buf)
अणु
	काष्ठा ad5446_state *st = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n", st->pwr_करोwn);
पूर्ण

अटल sमाप_प्रकार ad5446_ग_लिखो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
					    uपूर्णांकptr_t निजी,
					    स्थिर काष्ठा iio_chan_spec *chan,
					    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा ad5446_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक val;
	bool घातerकरोwn;
	पूर्णांक ret;

	ret = strtobool(buf, &घातerकरोwn);
	अगर (ret)
		वापस ret;

	mutex_lock(&st->lock);
	st->pwr_करोwn = घातerकरोwn;

	अगर (st->pwr_करोwn) अणु
		shअगरt = chan->scan_type.realbits + chan->scan_type.shअगरt;
		val = st->pwr_करोwn_mode << shअगरt;
	पूर्ण अन्यथा अणु
		val = st->cached_val;
	पूर्ण

	ret = st->chip_info->ग_लिखो(st, val);
	mutex_unlock(&st->lock);

	वापस ret ? ret : len;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info ad5446_ext_info_घातerकरोwn[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = ad5446_पढ़ो_dac_घातerकरोwn,
		.ग_लिखो = ad5446_ग_लिखो_dac_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	IIO_ENUM("powerdown_mode", IIO_SEPARATE, &ad5446_घातerकरोwn_mode_क्रमागत),
	IIO_ENUM_AVAILABLE("powerdown_mode", &ad5446_घातerकरोwn_mode_क्रमागत),
	अणु पूर्ण,
पूर्ण;

#घोषणा _AD5446_CHANNEL(bits, storage, _shअगरt, ext) अणु \
	.type = IIO_VOLTAGE, \
	.indexed = 1, \
	.output = 1, \
	.channel = 0, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = (bits), \
		.storagebits = (storage), \
		.shअगरt = (_shअगरt), \
		पूर्ण, \
	.ext_info = (ext), \
पूर्ण

#घोषणा AD5446_CHANNEL(bits, storage, shअगरt) \
	_AD5446_CHANNEL(bits, storage, shअगरt, शून्य)

#घोषणा AD5446_CHANNEL_POWERDOWN(bits, storage, shअगरt) \
	_AD5446_CHANNEL(bits, storage, shअगरt, ad5446_ext_info_घातerकरोwn)

अटल पूर्णांक ad5446_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad5446_state *st = iio_priv(indio_dev);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		*val = st->cached_val;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = st->vref_mv;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5446_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा ad5446_state *st = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val >= (1 << chan->scan_type.realbits) || val < 0)
			वापस -EINVAL;

		val <<= chan->scan_type.shअगरt;
		mutex_lock(&st->lock);
		st->cached_val = val;
		अगर (!st->pwr_करोwn)
			ret = st->chip_info->ग_लिखो(st, val);
		mutex_unlock(&st->lock);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info ad5446_info = अणु
	.पढ़ो_raw = ad5446_पढ़ो_raw,
	.ग_लिखो_raw = ad5446_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक ad5446_probe(काष्ठा device *dev, स्थिर अक्षर *name,
			स्थिर काष्ठा ad5446_chip_info *chip_info)
अणु
	काष्ठा ad5446_state *st;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regulator *reg;
	पूर्णांक ret, voltage_uv = 0;

	reg = devm_regulator_get(dev, "vcc");
	अगर (!IS_ERR(reg)) अणु
		ret = regulator_enable(reg);
		अगर (ret)
			वापस ret;

		ret = regulator_get_voltage(reg);
		अगर (ret < 0)
			जाओ error_disable_reg;

		voltage_uv = ret;
	पूर्ण

	indio_dev = devm_iio_device_alloc(dev, माप(*st));
	अगर (indio_dev == शून्य) अणु
		ret = -ENOMEM;
		जाओ error_disable_reg;
	पूर्ण
	st = iio_priv(indio_dev);
	st->chip_info = chip_info;

	dev_set_drvdata(dev, indio_dev);
	st->reg = reg;
	st->dev = dev;

	indio_dev->name = name;
	indio_dev->info = &ad5446_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = &st->chip_info->channel;
	indio_dev->num_channels = 1;

	mutex_init(&st->lock);

	st->pwr_करोwn_mode = MODE_PWRDWN_1k;

	अगर (st->chip_info->पूर्णांक_vref_mv)
		st->vref_mv = st->chip_info->पूर्णांक_vref_mv;
	अन्यथा अगर (voltage_uv)
		st->vref_mv = voltage_uv / 1000;
	अन्यथा
		dev_warn(dev, "reference voltage unspecified\n");

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_disable_reg;

	वापस 0;

error_disable_reg:
	अगर (!IS_ERR(reg))
		regulator_disable(reg);
	वापस ret;
पूर्ण

अटल पूर्णांक ad5446_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा ad5446_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	अगर (!IS_ERR(st->reg))
		regulator_disable(st->reg);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_SPI_MASTER)

अटल पूर्णांक ad5446_ग_लिखो(काष्ठा ad5446_state *st, अचिन्हित val)
अणु
	काष्ठा spi_device *spi = to_spi_device(st->dev);
	__be16 data = cpu_to_be16(val);

	वापस spi_ग_लिखो(spi, &data, माप(data));
पूर्ण

अटल पूर्णांक ad5660_ग_लिखो(काष्ठा ad5446_state *st, अचिन्हित val)
अणु
	काष्ठा spi_device *spi = to_spi_device(st->dev);
	uपूर्णांक8_t data[3];

	put_unaligned_be24(val, &data[0]);

	वापस spi_ग_लिखो(spi, data, माप(data));
पूर्ण

/*
 * ad5446_supported_spi_device_ids:
 * The AD5620/40/60 parts are available in dअगरferent fixed पूर्णांकernal reference
 * voltage options. The actual part numbers may look dअगरferently
 * (and a bit cryptic), however this style is used to make clear which
 * parts are supported here.
 */
क्रमागत ad5446_supported_spi_device_ids अणु
	ID_AD5300,
	ID_AD5310,
	ID_AD5320,
	ID_AD5444,
	ID_AD5446,
	ID_AD5450,
	ID_AD5451,
	ID_AD5541A,
	ID_AD5512A,
	ID_AD5553,
	ID_AD5600,
	ID_AD5601,
	ID_AD5611,
	ID_AD5621,
	ID_AD5641,
	ID_AD5620_2500,
	ID_AD5620_1250,
	ID_AD5640_2500,
	ID_AD5640_1250,
	ID_AD5660_2500,
	ID_AD5660_1250,
	ID_AD5662,
पूर्ण;

अटल स्थिर काष्ठा ad5446_chip_info ad5446_spi_chip_info[] = अणु
	[ID_AD5300] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(8, 16, 4),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5310] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(10, 16, 2),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5320] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(12, 16, 0),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5444] = अणु
		.channel = AD5446_CHANNEL(12, 16, 2),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5446] = अणु
		.channel = AD5446_CHANNEL(14, 16, 0),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5450] = अणु
		.channel = AD5446_CHANNEL(8, 16, 6),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5451] = अणु
		.channel = AD5446_CHANNEL(10, 16, 4),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5541A] = अणु
		.channel = AD5446_CHANNEL(16, 16, 0),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5512A] = अणु
		.channel = AD5446_CHANNEL(12, 16, 4),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5553] = अणु
		.channel = AD5446_CHANNEL(14, 16, 0),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5600] = अणु
		.channel = AD5446_CHANNEL(16, 16, 0),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5601] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(8, 16, 6),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5611] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(10, 16, 4),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5621] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(12, 16, 2),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5641] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(14, 16, 0),
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5620_2500] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(12, 16, 2),
		.पूर्णांक_vref_mv = 2500,
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5620_1250] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(12, 16, 2),
		.पूर्णांक_vref_mv = 1250,
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5640_2500] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(14, 16, 0),
		.पूर्णांक_vref_mv = 2500,
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5640_1250] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(14, 16, 0),
		.पूर्णांक_vref_mv = 1250,
		.ग_लिखो = ad5446_ग_लिखो,
	पूर्ण,
	[ID_AD5660_2500] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(16, 16, 0),
		.पूर्णांक_vref_mv = 2500,
		.ग_लिखो = ad5660_ग_लिखो,
	पूर्ण,
	[ID_AD5660_1250] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(16, 16, 0),
		.पूर्णांक_vref_mv = 1250,
		.ग_लिखो = ad5660_ग_लिखो,
	पूर्ण,
	[ID_AD5662] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(16, 16, 0),
		.ग_लिखो = ad5660_ग_लिखो,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा spi_device_id ad5446_spi_ids[] = अणु
	अणु"ad5300", ID_AD5300पूर्ण,
	अणु"ad5310", ID_AD5310पूर्ण,
	अणु"ad5320", ID_AD5320पूर्ण,
	अणु"ad5444", ID_AD5444पूर्ण,
	अणु"ad5446", ID_AD5446पूर्ण,
	अणु"ad5450", ID_AD5450पूर्ण,
	अणु"ad5451", ID_AD5451पूर्ण,
	अणु"ad5452", ID_AD5444पूर्ण, /* ad5452 is compatible to the ad5444 */
	अणु"ad5453", ID_AD5446पूर्ण, /* ad5453 is compatible to the ad5446 */
	अणु"ad5512a", ID_AD5512Aपूर्ण,
	अणु"ad5541a", ID_AD5541Aपूर्ण,
	अणु"ad5542a", ID_AD5541Aपूर्ण, /* ad5541a and ad5542a are compatible */
	अणु"ad5543", ID_AD5541Aपूर्ण, /* ad5541a and ad5543 are compatible */
	अणु"ad5553", ID_AD5553पूर्ण,
	अणु"ad5600", ID_AD5600पूर्ण,
	अणु"ad5601", ID_AD5601पूर्ण,
	अणु"ad5611", ID_AD5611पूर्ण,
	अणु"ad5621", ID_AD5621पूर्ण,
	अणु"ad5641", ID_AD5641पूर्ण,
	अणु"ad5620-2500", ID_AD5620_2500पूर्ण, /* AD5620/40/60: */
	अणु"ad5620-1250", ID_AD5620_1250पूर्ण, /* part numbers may look dअगरferently */
	अणु"ad5640-2500", ID_AD5640_2500पूर्ण,
	अणु"ad5640-1250", ID_AD5640_1250पूर्ण,
	अणु"ad5660-2500", ID_AD5660_2500पूर्ण,
	अणु"ad5660-1250", ID_AD5660_1250पूर्ण,
	अणु"ad5662", ID_AD5662पूर्ण,
	अणु"dac081s101", ID_AD5300पूर्ण, /* compatible Texas Instruments chips */
	अणु"dac101s101", ID_AD5310पूर्ण,
	अणु"dac121s101", ID_AD5320पूर्ण,
	अणु"dac7512", ID_AD5320पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5446_spi_ids);

अटल स्थिर काष्ठा of_device_id ad5446_of_ids[] = अणु
	अणु .compatible = "ti,dac7512" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad5446_of_ids);

अटल पूर्णांक ad5446_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	वापस ad5446_probe(&spi->dev, id->name,
		&ad5446_spi_chip_info[id->driver_data]);
पूर्ण

अटल पूर्णांक ad5446_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस ad5446_हटाओ(&spi->dev);
पूर्ण

अटल काष्ठा spi_driver ad5446_spi_driver = अणु
	.driver = अणु
		.name	= "ad5446",
		.of_match_table = ad5446_of_ids,
	पूर्ण,
	.probe		= ad5446_spi_probe,
	.हटाओ		= ad5446_spi_हटाओ,
	.id_table	= ad5446_spi_ids,
पूर्ण;

अटल पूर्णांक __init ad5446_spi_रेजिस्टर_driver(व्योम)
अणु
	वापस spi_रेजिस्टर_driver(&ad5446_spi_driver);
पूर्ण

अटल व्योम ad5446_spi_unरेजिस्टर_driver(व्योम)
अणु
	spi_unरेजिस्टर_driver(&ad5446_spi_driver);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक ad5446_spi_रेजिस्टर_driver(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ad5446_spi_unरेजिस्टर_driver(व्योम) अणु पूर्ण

#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_I2C)

अटल पूर्णांक ad5622_ग_लिखो(काष्ठा ad5446_state *st, अचिन्हित val)
अणु
	काष्ठा i2c_client *client = to_i2c_client(st->dev);
	__be16 data = cpu_to_be16(val);

	वापस i2c_master_send(client, (अक्षर *)&data, माप(data));
पूर्ण

/*
 * ad5446_supported_i2c_device_ids:
 * The AD5620/40/60 parts are available in dअगरferent fixed पूर्णांकernal reference
 * voltage options. The actual part numbers may look dअगरferently
 * (and a bit cryptic), however this style is used to make clear which
 * parts are supported here.
 */
क्रमागत ad5446_supported_i2c_device_ids अणु
	ID_AD5602,
	ID_AD5612,
	ID_AD5622,
पूर्ण;

अटल स्थिर काष्ठा ad5446_chip_info ad5446_i2c_chip_info[] = अणु
	[ID_AD5602] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(8, 16, 4),
		.ग_लिखो = ad5622_ग_लिखो,
	पूर्ण,
	[ID_AD5612] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(10, 16, 2),
		.ग_लिखो = ad5622_ग_लिखो,
	पूर्ण,
	[ID_AD5622] = अणु
		.channel = AD5446_CHANNEL_POWERDOWN(12, 16, 0),
		.ग_लिखो = ad5622_ग_लिखो,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad5446_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	वापस ad5446_probe(&i2c->dev, id->name,
		&ad5446_i2c_chip_info[id->driver_data]);
पूर्ण

अटल पूर्णांक ad5446_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	वापस ad5446_हटाओ(&i2c->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad5446_i2c_ids[] = अणु
	अणु"ad5301", ID_AD5602पूर्ण,
	अणु"ad5311", ID_AD5612पूर्ण,
	अणु"ad5321", ID_AD5622पूर्ण,
	अणु"ad5602", ID_AD5602पूर्ण,
	अणु"ad5612", ID_AD5612पूर्ण,
	अणु"ad5622", ID_AD5622पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad5446_i2c_ids);

अटल काष्ठा i2c_driver ad5446_i2c_driver = अणु
	.driver = अणु
		   .name = "ad5446",
	पूर्ण,
	.probe = ad5446_i2c_probe,
	.हटाओ = ad5446_i2c_हटाओ,
	.id_table = ad5446_i2c_ids,
पूर्ण;

अटल पूर्णांक __init ad5446_i2c_रेजिस्टर_driver(व्योम)
अणु
	वापस i2c_add_driver(&ad5446_i2c_driver);
पूर्ण

अटल व्योम __निकास ad5446_i2c_unरेजिस्टर_driver(व्योम)
अणु
	i2c_del_driver(&ad5446_i2c_driver);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक ad5446_i2c_रेजिस्टर_driver(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ad5446_i2c_unरेजिस्टर_driver(व्योम) अणु पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __init ad5446_init(व्योम)
अणु
	पूर्णांक ret;

	ret = ad5446_spi_रेजिस्टर_driver();
	अगर (ret)
		वापस ret;

	ret = ad5446_i2c_रेजिस्टर_driver();
	अगर (ret) अणु
		ad5446_spi_unरेजिस्टर_driver();
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
module_init(ad5446_init);

अटल व्योम __निकास ad5446_निकास(व्योम)
अणु
	ad5446_i2c_unरेजिस्टर_driver();
	ad5446_spi_unरेजिस्टर_driver();
पूर्ण
module_निकास(ad5446_निकास);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD5444/AD5446 DAC");
MODULE_LICENSE("GPL v2");
