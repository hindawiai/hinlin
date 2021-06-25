<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD7785/AD7792/AD7793/AD7794/AD7795 SPI ADC driver
 *
 * Copyright 2011-2012 Analog Devices Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/adc/ad_sigma_delta.h>
#समावेश <linux/platक्रमm_data/ad7793.h>

/* Registers */
#घोषणा AD7793_REG_COMM		0 /* Communications Register (WO, 8-bit) */
#घोषणा AD7793_REG_STAT		0 /* Status Register	     (RO, 8-bit) */
#घोषणा AD7793_REG_MODE		1 /* Mode Register	     (RW, 16-bit */
#घोषणा AD7793_REG_CONF		2 /* Configuration Register  (RW, 16-bit) */
#घोषणा AD7793_REG_DATA		3 /* Data Register	     (RO, 16-/24-bit) */
#घोषणा AD7793_REG_ID		4 /* ID Register	     (RO, 8-bit) */
#घोषणा AD7793_REG_IO		5 /* IO Register	     (RO, 8-bit) */
#घोषणा AD7793_REG_OFFSET	6 /* Offset Register	     (RW, 16-bit
				   * (AD7792)/24-bit (AD7793)) */
#घोषणा AD7793_REG_FULLSALE	7 /* Full-Scale Register
				   * (RW, 16-bit (AD7792)/24-bit (AD7793)) */

/* Communications Register Bit Designations (AD7793_REG_COMM) */
#घोषणा AD7793_COMM_WEN		(1 << 7) /* Write Enable */
#घोषणा AD7793_COMM_WRITE	(0 << 6) /* Write Operation */
#घोषणा AD7793_COMM_READ	(1 << 6) /* Read Operation */
#घोषणा AD7793_COMM_ADDR(x)	(((x) & 0x7) << 3) /* Register Address */
#घोषणा AD7793_COMM_CREAD	(1 << 2) /* Continuous Read of Data Register */

/* Status Register Bit Designations (AD7793_REG_STAT) */
#घोषणा AD7793_STAT_RDY		(1 << 7) /* Ready */
#घोषणा AD7793_STAT_ERR		(1 << 6) /* Error (Overrange, Underrange) */
#घोषणा AD7793_STAT_CH3		(1 << 2) /* Channel 3 */
#घोषणा AD7793_STAT_CH2		(1 << 1) /* Channel 2 */
#घोषणा AD7793_STAT_CH1		(1 << 0) /* Channel 1 */

/* Mode Register Bit Designations (AD7793_REG_MODE) */
#घोषणा AD7793_MODE_SEL(x)	(((x) & 0x7) << 13) /* Operation Mode Select */
#घोषणा AD7793_MODE_SEL_MASK	(0x7 << 13) /* Operation Mode Select mask */
#घोषणा AD7793_MODE_CLKSRC(x)	(((x) & 0x3) << 6) /* ADC Clock Source Select */
#घोषणा AD7793_MODE_RATE(x)	((x) & 0xF) /* Filter Update Rate Select */

#घोषणा AD7793_MODE_CONT		0 /* Continuous Conversion Mode */
#घोषणा AD7793_MODE_SINGLE		1 /* Single Conversion Mode */
#घोषणा AD7793_MODE_IDLE		2 /* Idle Mode */
#घोषणा AD7793_MODE_PWRDN		3 /* Power-Down Mode */
#घोषणा AD7793_MODE_CAL_INT_ZERO	4 /* Internal Zero-Scale Calibration */
#घोषणा AD7793_MODE_CAL_INT_FULL	5 /* Internal Full-Scale Calibration */
#घोषणा AD7793_MODE_CAL_SYS_ZERO	6 /* System Zero-Scale Calibration */
#घोषणा AD7793_MODE_CAL_SYS_FULL	7 /* System Full-Scale Calibration */

#घोषणा AD7793_CLK_INT		0 /* Internal 64 kHz Clock not
				   * available at the CLK pin */
#घोषणा AD7793_CLK_INT_CO	1 /* Internal 64 kHz Clock available
				   * at the CLK pin */
#घोषणा AD7793_CLK_EXT		2 /* External 64 kHz Clock */
#घोषणा AD7793_CLK_EXT_DIV2	3 /* External Clock भागided by 2 */

/* Configuration Register Bit Designations (AD7793_REG_CONF) */
#घोषणा AD7793_CONF_VBIAS(x)	(((x) & 0x3) << 14) /* Bias Voltage
						     * Generator Enable */
#घोषणा AD7793_CONF_BO_EN	(1 << 13) /* Burnout Current Enable */
#घोषणा AD7793_CONF_UNIPOLAR	(1 << 12) /* Unipolar/Bipolar Enable */
#घोषणा AD7793_CONF_BOOST	(1 << 11) /* Boost Enable */
#घोषणा AD7793_CONF_GAIN(x)	(((x) & 0x7) << 8) /* Gain Select */
#घोषणा AD7793_CONF_REFSEL(x)	((x) << 6) /* INT/EXT Reference Select */
#घोषणा AD7793_CONF_BUF		(1 << 4) /* Buffered Mode Enable */
#घोषणा AD7793_CONF_CHAN(x)	((x) & 0xf) /* Channel select */
#घोषणा AD7793_CONF_CHAN_MASK	0xf /* Channel select mask */

#घोषणा AD7793_CH_AIN1P_AIN1M	0 /* AIN1(+) - AIN1(-) */
#घोषणा AD7793_CH_AIN2P_AIN2M	1 /* AIN2(+) - AIN2(-) */
#घोषणा AD7793_CH_AIN3P_AIN3M	2 /* AIN3(+) - AIN3(-) */
#घोषणा AD7793_CH_AIN1M_AIN1M	3 /* AIN1(-) - AIN1(-) */
#घोषणा AD7793_CH_TEMP		6 /* Temp Sensor */
#घोषणा AD7793_CH_AVDD_MONITOR	7 /* AVDD Monitor */

#घोषणा AD7795_CH_AIN4P_AIN4M	4 /* AIN4(+) - AIN4(-) */
#घोषणा AD7795_CH_AIN5P_AIN5M	5 /* AIN5(+) - AIN5(-) */
#घोषणा AD7795_CH_AIN6P_AIN6M	6 /* AIN6(+) - AIN6(-) */
#घोषणा AD7795_CH_AIN1M_AIN1M	8 /* AIN1(-) - AIN1(-) */

/* ID Register Bit Designations (AD7793_REG_ID) */
#घोषणा AD7785_ID		0x3
#घोषणा AD7792_ID		0xA
#घोषणा AD7793_ID		0xB
#घोषणा AD7794_ID		0xF
#घोषणा AD7795_ID		0xF
#घोषणा AD7796_ID		0xA
#घोषणा AD7797_ID		0xB
#घोषणा AD7798_ID		0x8
#घोषणा AD7799_ID		0x9
#घोषणा AD7793_ID_MASK		0xF

/* IO (Excitation Current Sources) Register Bit Designations (AD7793_REG_IO) */
#घोषणा AD7793_IO_IEXC1_IOUT1_IEXC2_IOUT2	0 /* IEXC1 connect to IOUT1,
						   * IEXC2 connect to IOUT2 */
#घोषणा AD7793_IO_IEXC1_IOUT2_IEXC2_IOUT1	1 /* IEXC1 connect to IOUT2,
						   * IEXC2 connect to IOUT1 */
#घोषणा AD7793_IO_IEXC1_IEXC2_IOUT1		2 /* Both current sources
						   * IEXC1,2 connect to IOUT1 */
#घोषणा AD7793_IO_IEXC1_IEXC2_IOUT2		3 /* Both current sources
						   * IEXC1,2 connect to IOUT2 */

#घोषणा AD7793_IO_IXCEN_10uA	(1 << 0) /* Excitation Current 10uA */
#घोषणा AD7793_IO_IXCEN_210uA	(2 << 0) /* Excitation Current 210uA */
#घोषणा AD7793_IO_IXCEN_1mA	(3 << 0) /* Excitation Current 1mA */

/* NOTE:
 * The AD7792/AD7793 features a dual use data out पढ़ोy DOUT/RDY output.
 * In order to aव्योम contentions on the SPI bus, it's thereक्रमe necessary
 * to use spi bus locking.
 *
 * The DOUT/RDY output must also be wired to an पूर्णांकerrupt capable GPIO.
 */

#घोषणा AD7793_FLAG_HAS_CLKSEL		BIT(0)
#घोषणा AD7793_FLAG_HAS_REFSEL		BIT(1)
#घोषणा AD7793_FLAG_HAS_VBIAS		BIT(2)
#घोषणा AD7793_HAS_EXITATION_CURRENT	BIT(3)
#घोषणा AD7793_FLAG_HAS_GAIN		BIT(4)
#घोषणा AD7793_FLAG_HAS_BUFFER		BIT(5)

काष्ठा ad7793_chip_info अणु
	अचिन्हित पूर्णांक id;
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
	अचिन्हित पूर्णांक flags;

	स्थिर काष्ठा iio_info *iio_info;
	स्थिर u16 *sample_freq_avail;
पूर्ण;

काष्ठा ad7793_state अणु
	स्थिर काष्ठा ad7793_chip_info	*chip_info;
	काष्ठा regulator		*reg;
	u16				पूर्णांक_vref_mv;
	u16				mode;
	u16				conf;
	u32				scale_avail[8][2];

	काष्ठा ad_sigma_delta		sd;

पूर्ण;

क्रमागत ad7793_supported_device_ids अणु
	ID_AD7785,
	ID_AD7792,
	ID_AD7793,
	ID_AD7794,
	ID_AD7795,
	ID_AD7796,
	ID_AD7797,
	ID_AD7798,
	ID_AD7799,
पूर्ण;

अटल काष्ठा ad7793_state *ad_sigma_delta_to_ad7793(काष्ठा ad_sigma_delta *sd)
अणु
	वापस container_of(sd, काष्ठा ad7793_state, sd);
पूर्ण

अटल पूर्णांक ad7793_set_channel(काष्ठा ad_sigma_delta *sd, अचिन्हित पूर्णांक channel)
अणु
	काष्ठा ad7793_state *st = ad_sigma_delta_to_ad7793(sd);

	st->conf &= ~AD7793_CONF_CHAN_MASK;
	st->conf |= AD7793_CONF_CHAN(channel);

	वापस ad_sd_ग_लिखो_reg(&st->sd, AD7793_REG_CONF, 2, st->conf);
पूर्ण

अटल पूर्णांक ad7793_set_mode(काष्ठा ad_sigma_delta *sd,
			   क्रमागत ad_sigma_delta_mode mode)
अणु
	काष्ठा ad7793_state *st = ad_sigma_delta_to_ad7793(sd);

	st->mode &= ~AD7793_MODE_SEL_MASK;
	st->mode |= AD7793_MODE_SEL(mode);

	वापस ad_sd_ग_लिखो_reg(&st->sd, AD7793_REG_MODE, 2, st->mode);
पूर्ण

अटल स्थिर काष्ठा ad_sigma_delta_info ad7793_sigma_delta_info = अणु
	.set_channel = ad7793_set_channel,
	.set_mode = ad7793_set_mode,
	.has_रेजिस्टरs = true,
	.addr_shअगरt = 3,
	.पढ़ो_mask = BIT(6),
	.irq_flags = IRQF_TRIGGER_LOW,
पूर्ण;

अटल स्थिर काष्ठा ad_sd_calib_data ad7793_calib_arr[6] = अणु
	अणुAD7793_MODE_CAL_INT_ZERO, AD7793_CH_AIN1P_AIN1Mपूर्ण,
	अणुAD7793_MODE_CAL_INT_FULL, AD7793_CH_AIN1P_AIN1Mपूर्ण,
	अणुAD7793_MODE_CAL_INT_ZERO, AD7793_CH_AIN2P_AIN2Mपूर्ण,
	अणुAD7793_MODE_CAL_INT_FULL, AD7793_CH_AIN2P_AIN2Mपूर्ण,
	अणुAD7793_MODE_CAL_INT_ZERO, AD7793_CH_AIN3P_AIN3Mपूर्ण,
	अणुAD7793_MODE_CAL_INT_FULL, AD7793_CH_AIN3P_AIN3Mपूर्ण
पूर्ण;

अटल पूर्णांक ad7793_calibrate_all(काष्ठा ad7793_state *st)
अणु
	वापस ad_sd_calibrate_all(&st->sd, ad7793_calib_arr,
				   ARRAY_SIZE(ad7793_calib_arr));
पूर्ण

अटल पूर्णांक ad7793_check_platक्रमm_data(काष्ठा ad7793_state *st,
	स्थिर काष्ठा ad7793_platक्रमm_data *pdata)
अणु
	अगर ((pdata->current_source_direction == AD7793_IEXEC1_IEXEC2_IOUT1 ||
		pdata->current_source_direction == AD7793_IEXEC1_IEXEC2_IOUT2) &&
		((pdata->निकासation_current != AD7793_IX_10uA) &&
		(pdata->निकासation_current != AD7793_IX_210uA)))
		वापस -EINVAL;

	अगर (!(st->chip_info->flags & AD7793_FLAG_HAS_CLKSEL) &&
		pdata->घड़ी_src != AD7793_CLK_SRC_INT)
		वापस -EINVAL;

	अगर (!(st->chip_info->flags & AD7793_FLAG_HAS_REFSEL) &&
		pdata->refsel != AD7793_REFSEL_REFIN1)
		वापस -EINVAL;

	अगर (!(st->chip_info->flags & AD7793_FLAG_HAS_VBIAS) &&
		pdata->bias_voltage != AD7793_BIAS_VOLTAGE_DISABLED)
		वापस -EINVAL;

	अगर (!(st->chip_info->flags & AD7793_HAS_EXITATION_CURRENT) &&
		pdata->निकासation_current != AD7793_IX_DISABLED)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ad7793_setup(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा ad7793_platक्रमm_data *pdata,
	अचिन्हित पूर्णांक vref_mv)
अणु
	काष्ठा ad7793_state *st = iio_priv(indio_dev);
	पूर्णांक i, ret;
	अचिन्हित दीर्घ दीर्घ scale_uv;
	u32 id;

	ret = ad7793_check_platक्रमm_data(st, pdata);
	अगर (ret)
		वापस ret;

	/* reset the serial पूर्णांकerface */
	ret = ad_sd_reset(&st->sd, 32);
	अगर (ret < 0)
		जाओ out;
	usleep_range(500, 2000); /* Wait क्रम at least 500us */

	/* ग_लिखो/पढ़ो test क्रम device presence */
	ret = ad_sd_पढ़ो_reg(&st->sd, AD7793_REG_ID, 1, &id);
	अगर (ret)
		जाओ out;

	id &= AD7793_ID_MASK;

	अगर (id != st->chip_info->id) अणु
		ret = -ENODEV;
		dev_err(&st->sd.spi->dev, "device ID query failed\n");
		जाओ out;
	पूर्ण

	st->mode = AD7793_MODE_RATE(1);
	st->conf = 0;

	अगर (st->chip_info->flags & AD7793_FLAG_HAS_CLKSEL)
		st->mode |= AD7793_MODE_CLKSRC(pdata->घड़ी_src);
	अगर (st->chip_info->flags & AD7793_FLAG_HAS_REFSEL)
		st->conf |= AD7793_CONF_REFSEL(pdata->refsel);
	अगर (st->chip_info->flags & AD7793_FLAG_HAS_VBIAS)
		st->conf |= AD7793_CONF_VBIAS(pdata->bias_voltage);
	अगर (pdata->buffered || !(st->chip_info->flags & AD7793_FLAG_HAS_BUFFER))
		st->conf |= AD7793_CONF_BUF;
	अगर (pdata->boost_enable &&
		(st->chip_info->flags & AD7793_FLAG_HAS_VBIAS))
		st->conf |= AD7793_CONF_BOOST;
	अगर (pdata->burnout_current)
		st->conf |= AD7793_CONF_BO_EN;
	अगर (pdata->unipolar)
		st->conf |= AD7793_CONF_UNIPOLAR;

	अगर (!(st->chip_info->flags & AD7793_FLAG_HAS_GAIN))
		st->conf |= AD7793_CONF_GAIN(7);

	ret = ad7793_set_mode(&st->sd, AD_SD_MODE_IDLE);
	अगर (ret)
		जाओ out;

	ret = ad7793_set_channel(&st->sd, 0);
	अगर (ret)
		जाओ out;

	अगर (st->chip_info->flags & AD7793_HAS_EXITATION_CURRENT) अणु
		ret = ad_sd_ग_लिखो_reg(&st->sd, AD7793_REG_IO, 1,
				pdata->निकासation_current |
				(pdata->current_source_direction << 2));
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = ad7793_calibrate_all(st);
	अगर (ret)
		जाओ out;

	/* Populate available ADC input ranges */
	क्रम (i = 0; i < ARRAY_SIZE(st->scale_avail); i++) अणु
		scale_uv = ((u64)vref_mv * 100000000)
			>> (st->chip_info->channels[0].scan_type.realbits -
			(!!(st->conf & AD7793_CONF_UNIPOLAR) ? 0 : 1));
		scale_uv >>= i;

		st->scale_avail[i][1] = करो_भाग(scale_uv, 100000000) * 10;
		st->scale_avail[i][0] = scale_uv;
	पूर्ण

	वापस 0;
out:
	dev_err(&st->sd.spi->dev, "setup failed\n");
	वापस ret;
पूर्ण

अटल स्थिर u16 ad7793_sample_freq_avail[16] = अणु0, 470, 242, 123, 62, 50, 39,
					33, 19, 17, 16, 12, 10, 8, 6, 4पूर्ण;

अटल स्थिर u16 ad7797_sample_freq_avail[16] = अणु0, 0, 0, 123, 62, 50, 0,
					33, 0, 17, 16, 12, 10, 8, 6, 4पूर्ण;

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL(
	"470 242 123 62 50 39 33 19 17 16 12 10 8 6 4");

अटल IIO_CONST_ATTR_NAMED(sampling_frequency_available_ad7797,
	sampling_frequency_available, "123 62 50 33 17 16 12 10 8 6 4");

अटल पूर्णांक ad7793_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			     दीर्घ mask)
अणु
	काष्ठा ad7793_state *st = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		*vals = (पूर्णांक *)st->scale_avail;
		*type = IIO_VAL_INT_PLUS_न_अंकO;
		/* Values are stored in a 2D matrix  */
		*length = ARRAY_SIZE(st->scale_avail) * 2;

		वापस IIO_AVAIL_LIST;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा attribute *ad7793_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7793_attribute_group = अणु
	.attrs = ad7793_attributes,
पूर्ण;

अटल काष्ठा attribute *ad7797_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available_ad7797.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7797_attribute_group = अणु
	.attrs = ad7797_attributes,
पूर्ण;

अटल पूर्णांक ad7793_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad7793_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	अचिन्हित दीर्घ दीर्घ scale_uv;
	bool unipolar = !!(st->conf & AD7793_CONF_UNIPOLAR);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = ad_sigma_delta_single_conversion(indio_dev, chan, val);
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			अगर (chan->dअगरferential) अणु
				*val = st->
					scale_avail[(st->conf >> 8) & 0x7][0];
				*val2 = st->
					scale_avail[(st->conf >> 8) & 0x7][1];
				वापस IIO_VAL_INT_PLUS_न_अंकO;
			पूर्ण
			/* 1170mV / 2^23 * 6 */
			scale_uv = (1170ULL * 1000000000ULL * 6ULL);
			अवरोध;
		हाल IIO_TEMP:
				/* 1170mV / 0.81 mV/C / 2^23 */
				scale_uv = 1444444444444444ULL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		scale_uv >>= (chan->scan_type.realbits - (unipolar ? 0 : 1));
		*val = 0;
		*val2 = scale_uv;
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	हाल IIO_CHAN_INFO_OFFSET:
		अगर (!unipolar)
			*val = -(1 << (chan->scan_type.realbits - 1));
		अन्यथा
			*val = 0;

		/* Kelvin to Celsius */
		अगर (chan->type == IIO_TEMP) अणु
			अचिन्हित दीर्घ दीर्घ offset;
			अचिन्हित पूर्णांक shअगरt;

			shअगरt = chan->scan_type.realbits - (unipolar ? 0 : 1);
			offset = 273ULL << shअगरt;
			करो_भाग(offset, 1444);
			*val -= offset;
		पूर्ण
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = st->chip_info
			       ->sample_freq_avail[AD7793_MODE_RATE(st->mode)];
		वापस IIO_VAL_INT;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad7793_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा ad7793_state *st = iio_priv(indio_dev);
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक पंचांगp;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		ret = -EINVAL;
		क्रम (i = 0; i < ARRAY_SIZE(st->scale_avail); i++)
			अगर (val2 == st->scale_avail[i][1]) अणु
				ret = 0;
				पंचांगp = st->conf;
				st->conf &= ~AD7793_CONF_GAIN(-1);
				st->conf |= AD7793_CONF_GAIN(i);

				अगर (पंचांगp == st->conf)
					अवरोध;

				ad_sd_ग_लिखो_reg(&st->sd, AD7793_REG_CONF,
						माप(st->conf), st->conf);
				ad7793_calibrate_all(st);
				अवरोध;
			पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (!val) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < 16; i++)
			अगर (val == st->chip_info->sample_freq_avail[i])
				अवरोध;

		अगर (i == 16) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		st->mode &= ~AD7793_MODE_RATE(-1);
		st->mode |= AD7793_MODE_RATE(i);
		ad_sd_ग_लिखो_reg(&st->sd, AD7793_REG_MODE, माप(st->mode),
				st->mode);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	iio_device_release_direct_mode(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक ad7793_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       दीर्घ mask)
अणु
	वापस IIO_VAL_INT_PLUS_न_अंकO;
पूर्ण

अटल स्थिर काष्ठा iio_info ad7793_info = अणु
	.पढ़ो_raw = &ad7793_पढ़ो_raw,
	.ग_लिखो_raw = &ad7793_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = &ad7793_ग_लिखो_raw_get_fmt,
	.पढ़ो_avail = ad7793_पढ़ो_avail,
	.attrs = &ad7793_attribute_group,
	.validate_trigger = ad_sd_validate_trigger,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7797_info = अणु
	.पढ़ो_raw = &ad7793_पढ़ो_raw,
	.ग_लिखो_raw = &ad7793_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = &ad7793_ग_लिखो_raw_get_fmt,
	.attrs = &ad7797_attribute_group,
	.validate_trigger = ad_sd_validate_trigger,
पूर्ण;

#घोषणा __AD7793_CHANNEL(_si, _channel1, _channel2, _address, _bits, \
	_storagebits, _shअगरt, _extend_name, _type, _mask_type_av, _mask_all) \
	अणु \
		.type = (_type), \
		.dअगरferential = (_channel2 == -1 ? 0 : 1), \
		.indexed = 1, \
		.channel = (_channel1), \
		.channel2 = (_channel2), \
		.address = (_address), \
		.extend_name = (_extend_name), \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			BIT(IIO_CHAN_INFO_OFFSET), \
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
		.info_mask_shared_by_type_available = (_mask_type_av), \
		.info_mask_shared_by_all = _mask_all, \
		.scan_index = (_si), \
		.scan_type = अणु \
			.sign = 'u', \
			.realbits = (_bits), \
			.storagebits = (_storagebits), \
			.shअगरt = (_shअगरt), \
			.endianness = IIO_BE, \
		पूर्ण, \
	पूर्ण

#घोषणा AD7793_DIFF_CHANNEL(_si, _channel1, _channel2, _address, _bits, \
	_storagebits, _shअगरt) \
	__AD7793_CHANNEL(_si, _channel1, _channel2, _address, _bits, \
		_storagebits, _shअगरt, शून्य, IIO_VOLTAGE, \
		BIT(IIO_CHAN_INFO_SCALE), \
		BIT(IIO_CHAN_INFO_SAMP_FREQ))

#घोषणा AD7793_SHORTED_CHANNEL(_si, _channel, _address, _bits, \
	_storagebits, _shअगरt) \
	__AD7793_CHANNEL(_si, _channel, _channel, _address, _bits, \
		_storagebits, _shअगरt, "shorted", IIO_VOLTAGE, \
		BIT(IIO_CHAN_INFO_SCALE), \
		BIT(IIO_CHAN_INFO_SAMP_FREQ))

#घोषणा AD7793_TEMP_CHANNEL(_si, _address, _bits, _storagebits, _shअगरt) \
	__AD7793_CHANNEL(_si, 0, -1, _address, _bits, \
		_storagebits, _shअगरt, शून्य, IIO_TEMP, \
		0, \
		BIT(IIO_CHAN_INFO_SAMP_FREQ))

#घोषणा AD7793_SUPPLY_CHANNEL(_si, _channel, _address, _bits, _storagebits, \
	_shअगरt) \
	__AD7793_CHANNEL(_si, _channel, -1, _address, _bits, \
		_storagebits, _shअगरt, "supply", IIO_VOLTAGE, \
		0, \
		BIT(IIO_CHAN_INFO_SAMP_FREQ))

#घोषणा AD7797_DIFF_CHANNEL(_si, _channel1, _channel2, _address, _bits, \
	_storagebits, _shअगरt) \
	__AD7793_CHANNEL(_si, _channel1, _channel2, _address, _bits, \
		_storagebits, _shअगरt, शून्य, IIO_VOLTAGE, \
		0, \
		BIT(IIO_CHAN_INFO_SAMP_FREQ))

#घोषणा AD7797_SHORTED_CHANNEL(_si, _channel, _address, _bits, \
	_storagebits, _shअगरt) \
	__AD7793_CHANNEL(_si, _channel, _channel, _address, _bits, \
		_storagebits, _shअगरt, "shorted", IIO_VOLTAGE, \
		0, \
		BIT(IIO_CHAN_INFO_SAMP_FREQ))

#घोषणा DECLARE_AD7793_CHANNELS(_name, _b, _sb, _s) \
स्थिर काष्ठा iio_chan_spec _name##_channels[] = अणु \
	AD7793_DIFF_CHANNEL(0, 0, 0, AD7793_CH_AIN1P_AIN1M, (_b), (_sb), (_s)), \
	AD7793_DIFF_CHANNEL(1, 1, 1, AD7793_CH_AIN2P_AIN2M, (_b), (_sb), (_s)), \
	AD7793_DIFF_CHANNEL(2, 2, 2, AD7793_CH_AIN3P_AIN3M, (_b), (_sb), (_s)), \
	AD7793_SHORTED_CHANNEL(3, 0, AD7793_CH_AIN1M_AIN1M, (_b), (_sb), (_s)), \
	AD7793_TEMP_CHANNEL(4, AD7793_CH_TEMP, (_b), (_sb), (_s)), \
	AD7793_SUPPLY_CHANNEL(5, 3, AD7793_CH_AVDD_MONITOR, (_b), (_sb), (_s)), \
	IIO_CHAN_SOFT_TIMESTAMP(6), \
पूर्ण

#घोषणा DECLARE_AD7795_CHANNELS(_name, _b, _sb) \
स्थिर काष्ठा iio_chan_spec _name##_channels[] = अणु \
	AD7793_DIFF_CHANNEL(0, 0, 0, AD7793_CH_AIN1P_AIN1M, (_b), (_sb), 0), \
	AD7793_DIFF_CHANNEL(1, 1, 1, AD7793_CH_AIN2P_AIN2M, (_b), (_sb), 0), \
	AD7793_DIFF_CHANNEL(2, 2, 2, AD7793_CH_AIN3P_AIN3M, (_b), (_sb), 0), \
	AD7793_DIFF_CHANNEL(3, 3, 3, AD7795_CH_AIN4P_AIN4M, (_b), (_sb), 0), \
	AD7793_DIFF_CHANNEL(4, 4, 4, AD7795_CH_AIN5P_AIN5M, (_b), (_sb), 0), \
	AD7793_DIFF_CHANNEL(5, 5, 5, AD7795_CH_AIN6P_AIN6M, (_b), (_sb), 0), \
	AD7793_SHORTED_CHANNEL(6, 0, AD7795_CH_AIN1M_AIN1M, (_b), (_sb), 0), \
	AD7793_TEMP_CHANNEL(7, AD7793_CH_TEMP, (_b), (_sb), 0), \
	AD7793_SUPPLY_CHANNEL(8, 3, AD7793_CH_AVDD_MONITOR, (_b), (_sb), 0), \
	IIO_CHAN_SOFT_TIMESTAMP(9), \
पूर्ण

#घोषणा DECLARE_AD7797_CHANNELS(_name, _b, _sb) \
स्थिर काष्ठा iio_chan_spec _name##_channels[] = अणु \
	AD7797_DIFF_CHANNEL(0, 0, 0, AD7793_CH_AIN1P_AIN1M, (_b), (_sb), 0), \
	AD7797_SHORTED_CHANNEL(1, 0, AD7793_CH_AIN1M_AIN1M, (_b), (_sb), 0), \
	AD7793_TEMP_CHANNEL(2, AD7793_CH_TEMP, (_b), (_sb), 0), \
	AD7793_SUPPLY_CHANNEL(3, 3, AD7793_CH_AVDD_MONITOR, (_b), (_sb), 0), \
	IIO_CHAN_SOFT_TIMESTAMP(4), \
पूर्ण

#घोषणा DECLARE_AD7799_CHANNELS(_name, _b, _sb) \
स्थिर काष्ठा iio_chan_spec _name##_channels[] = अणु \
	AD7793_DIFF_CHANNEL(0, 0, 0, AD7793_CH_AIN1P_AIN1M, (_b), (_sb), 0), \
	AD7793_DIFF_CHANNEL(1, 1, 1, AD7793_CH_AIN2P_AIN2M, (_b), (_sb), 0), \
	AD7793_DIFF_CHANNEL(2, 2, 2, AD7793_CH_AIN3P_AIN3M, (_b), (_sb), 0), \
	AD7793_SHORTED_CHANNEL(3, 0, AD7793_CH_AIN1M_AIN1M, (_b), (_sb), 0), \
	AD7793_SUPPLY_CHANNEL(4, 3, AD7793_CH_AVDD_MONITOR, (_b), (_sb), 0), \
	IIO_CHAN_SOFT_TIMESTAMP(5), \
पूर्ण

अटल DECLARE_AD7793_CHANNELS(ad7785, 20, 32, 4);
अटल DECLARE_AD7793_CHANNELS(ad7792, 16, 32, 0);
अटल DECLARE_AD7793_CHANNELS(ad7793, 24, 32, 0);
अटल DECLARE_AD7795_CHANNELS(ad7794, 16, 32);
अटल DECLARE_AD7795_CHANNELS(ad7795, 24, 32);
अटल DECLARE_AD7797_CHANNELS(ad7796, 16, 16);
अटल DECLARE_AD7797_CHANNELS(ad7797, 24, 32);
अटल DECLARE_AD7799_CHANNELS(ad7798, 16, 16);
अटल DECLARE_AD7799_CHANNELS(ad7799, 24, 32);

अटल स्थिर काष्ठा ad7793_chip_info ad7793_chip_info_tbl[] = अणु
	[ID_AD7785] = अणु
		.id = AD7785_ID,
		.channels = ad7785_channels,
		.num_channels = ARRAY_SIZE(ad7785_channels),
		.iio_info = &ad7793_info,
		.sample_freq_avail = ad7793_sample_freq_avail,
		.flags = AD7793_FLAG_HAS_CLKSEL |
			AD7793_FLAG_HAS_REFSEL |
			AD7793_FLAG_HAS_VBIAS |
			AD7793_HAS_EXITATION_CURRENT |
			AD7793_FLAG_HAS_GAIN |
			AD7793_FLAG_HAS_BUFFER,
	पूर्ण,
	[ID_AD7792] = अणु
		.id = AD7792_ID,
		.channels = ad7792_channels,
		.num_channels = ARRAY_SIZE(ad7792_channels),
		.iio_info = &ad7793_info,
		.sample_freq_avail = ad7793_sample_freq_avail,
		.flags = AD7793_FLAG_HAS_CLKSEL |
			AD7793_FLAG_HAS_REFSEL |
			AD7793_FLAG_HAS_VBIAS |
			AD7793_HAS_EXITATION_CURRENT |
			AD7793_FLAG_HAS_GAIN |
			AD7793_FLAG_HAS_BUFFER,
	पूर्ण,
	[ID_AD7793] = अणु
		.id = AD7793_ID,
		.channels = ad7793_channels,
		.num_channels = ARRAY_SIZE(ad7793_channels),
		.iio_info = &ad7793_info,
		.sample_freq_avail = ad7793_sample_freq_avail,
		.flags = AD7793_FLAG_HAS_CLKSEL |
			AD7793_FLAG_HAS_REFSEL |
			AD7793_FLAG_HAS_VBIAS |
			AD7793_HAS_EXITATION_CURRENT |
			AD7793_FLAG_HAS_GAIN |
			AD7793_FLAG_HAS_BUFFER,
	पूर्ण,
	[ID_AD7794] = अणु
		.id = AD7794_ID,
		.channels = ad7794_channels,
		.num_channels = ARRAY_SIZE(ad7794_channels),
		.iio_info = &ad7793_info,
		.sample_freq_avail = ad7793_sample_freq_avail,
		.flags = AD7793_FLAG_HAS_CLKSEL |
			AD7793_FLAG_HAS_REFSEL |
			AD7793_FLAG_HAS_VBIAS |
			AD7793_HAS_EXITATION_CURRENT |
			AD7793_FLAG_HAS_GAIN |
			AD7793_FLAG_HAS_BUFFER,
	पूर्ण,
	[ID_AD7795] = अणु
		.id = AD7795_ID,
		.channels = ad7795_channels,
		.num_channels = ARRAY_SIZE(ad7795_channels),
		.iio_info = &ad7793_info,
		.sample_freq_avail = ad7793_sample_freq_avail,
		.flags = AD7793_FLAG_HAS_CLKSEL |
			AD7793_FLAG_HAS_REFSEL |
			AD7793_FLAG_HAS_VBIAS |
			AD7793_HAS_EXITATION_CURRENT |
			AD7793_FLAG_HAS_GAIN |
			AD7793_FLAG_HAS_BUFFER,
	पूर्ण,
	[ID_AD7796] = अणु
		.id = AD7796_ID,
		.channels = ad7796_channels,
		.num_channels = ARRAY_SIZE(ad7796_channels),
		.iio_info = &ad7797_info,
		.sample_freq_avail = ad7797_sample_freq_avail,
		.flags = AD7793_FLAG_HAS_CLKSEL,
	पूर्ण,
	[ID_AD7797] = अणु
		.id = AD7797_ID,
		.channels = ad7797_channels,
		.num_channels = ARRAY_SIZE(ad7797_channels),
		.iio_info = &ad7797_info,
		.sample_freq_avail = ad7797_sample_freq_avail,
		.flags = AD7793_FLAG_HAS_CLKSEL,
	पूर्ण,
	[ID_AD7798] = अणु
		.id = AD7798_ID,
		.channels = ad7798_channels,
		.num_channels = ARRAY_SIZE(ad7798_channels),
		.iio_info = &ad7793_info,
		.sample_freq_avail = ad7793_sample_freq_avail,
		.flags = AD7793_FLAG_HAS_GAIN |
			AD7793_FLAG_HAS_BUFFER,
	पूर्ण,
	[ID_AD7799] = अणु
		.id = AD7799_ID,
		.channels = ad7799_channels,
		.num_channels = ARRAY_SIZE(ad7799_channels),
		.iio_info = &ad7793_info,
		.sample_freq_avail = ad7793_sample_freq_avail,
		.flags = AD7793_FLAG_HAS_GAIN |
			AD7793_FLAG_HAS_BUFFER,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad7793_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा ad7793_platक्रमm_data *pdata = spi->dev.platक्रमm_data;
	काष्ठा ad7793_state *st;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret, vref_mv = 0;

	अगर (!pdata) अणु
		dev_err(&spi->dev, "no platform data?\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!spi->irq) अणु
		dev_err(&spi->dev, "no IRQ?\n");
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	ad_sd_init(&st->sd, indio_dev, spi, &ad7793_sigma_delta_info);

	अगर (pdata->refsel != AD7793_REFSEL_INTERNAL) अणु
		st->reg = devm_regulator_get(&spi->dev, "refin");
		अगर (IS_ERR(st->reg))
			वापस PTR_ERR(st->reg);

		ret = regulator_enable(st->reg);
		अगर (ret)
			वापस ret;

		vref_mv = regulator_get_voltage(st->reg);
		अगर (vref_mv < 0) अणु
			ret = vref_mv;
			जाओ error_disable_reg;
		पूर्ण

		vref_mv /= 1000;
	पूर्ण अन्यथा अणु
		vref_mv = 1170; /* Build-in ref */
	पूर्ण

	st->chip_info =
		&ad7793_chip_info_tbl[spi_get_device_id(spi)->driver_data];

	spi_set_drvdata(spi, indio_dev);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;
	indio_dev->info = st->chip_info->iio_info;

	ret = ad_sd_setup_buffer_and_trigger(indio_dev);
	अगर (ret)
		जाओ error_disable_reg;

	ret = ad7793_setup(indio_dev, pdata, vref_mv);
	अगर (ret)
		जाओ error_हटाओ_trigger;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_हटाओ_trigger;

	वापस 0;

error_हटाओ_trigger:
	ad_sd_cleanup_buffer_and_trigger(indio_dev);
error_disable_reg:
	अगर (pdata->refsel != AD7793_REFSEL_INTERNAL)
		regulator_disable(st->reg);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7793_हटाओ(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा ad7793_platक्रमm_data *pdata = spi->dev.platक्रमm_data;
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad7793_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	ad_sd_cleanup_buffer_and_trigger(indio_dev);

	अगर (pdata->refsel != AD7793_REFSEL_INTERNAL)
		regulator_disable(st->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad7793_id[] = अणु
	अणु"ad7785", ID_AD7785पूर्ण,
	अणु"ad7792", ID_AD7792पूर्ण,
	अणु"ad7793", ID_AD7793पूर्ण,
	अणु"ad7794", ID_AD7794पूर्ण,
	अणु"ad7795", ID_AD7795पूर्ण,
	अणु"ad7796", ID_AD7796पूर्ण,
	अणु"ad7797", ID_AD7797पूर्ण,
	अणु"ad7798", ID_AD7798पूर्ण,
	अणु"ad7799", ID_AD7799पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7793_id);

अटल काष्ठा spi_driver ad7793_driver = अणु
	.driver = अणु
		.name	= "ad7793",
	पूर्ण,
	.probe		= ad7793_probe,
	.हटाओ		= ad7793_हटाओ,
	.id_table	= ad7793_id,
पूर्ण;
module_spi_driver(ad7793_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7793 and similar ADCs");
MODULE_LICENSE("GPL v2");
