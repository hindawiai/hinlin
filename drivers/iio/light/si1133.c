<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * si1133.c - Support क्रम Siद_असल SI1133 combined ambient
 * light and UV index sensors
 *
 * Copyright 2018 Maxime Roussin-Belanger <maxime.roussinbelanger@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश <linux/util_macros.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा SI1133_REG_PART_ID		0x00
#घोषणा SI1133_REG_REV_ID		0x01
#घोषणा SI1133_REG_MFR_ID		0x02
#घोषणा SI1133_REG_INFO0		0x03
#घोषणा SI1133_REG_INFO1		0x04

#घोषणा SI1133_PART_ID			0x33

#घोषणा SI1133_REG_HOSTIN0		0x0A
#घोषणा SI1133_REG_COMMAND		0x0B
#घोषणा SI1133_REG_IRQ_ENABLE		0x0F
#घोषणा SI1133_REG_RESPONSE1		0x10
#घोषणा SI1133_REG_RESPONSE0		0x11
#घोषणा SI1133_REG_IRQ_STATUS		0x12
#घोषणा SI1133_REG_MEAS_RATE		0x1A

#घोषणा SI1133_IRQ_CHANNEL_ENABLE	0xF

#घोषणा SI1133_CMD_RESET_CTR		0x00
#घोषणा SI1133_CMD_RESET_SW		0x01
#घोषणा SI1133_CMD_FORCE		0x11
#घोषणा SI1133_CMD_START_AUTONOMOUS	0x13
#घोषणा SI1133_CMD_PARAM_SET		0x80
#घोषणा SI1133_CMD_PARAM_QUERY		0x40
#घोषणा SI1133_CMD_PARAM_MASK		0x3F

#घोषणा SI1133_CMD_ERR_MASK		BIT(4)
#घोषणा SI1133_CMD_SEQ_MASK		0xF
#घोषणा SI1133_MAX_CMD_CTR		0xF

#घोषणा SI1133_PARAM_REG_CHAN_LIST	0x01
#घोषणा SI1133_PARAM_REG_ADCCONFIG(x)	((x) * 4) + 2
#घोषणा SI1133_PARAM_REG_ADCSENS(x)	((x) * 4) + 3
#घोषणा SI1133_PARAM_REG_ADCPOST(x)	((x) * 4) + 4

#घोषणा SI1133_ADCMUX_MASK 0x1F

#घोषणा SI1133_ADCCONFIG_DECIM_RATE(x)	(x) << 5

#घोषणा SI1133_ADCSENS_SCALE_MASK 0x70
#घोषणा SI1133_ADCSENS_SCALE_SHIFT 4
#घोषणा SI1133_ADCSENS_HSIG_MASK BIT(7)
#घोषणा SI1133_ADCSENS_HSIG_SHIFT 7
#घोषणा SI1133_ADCSENS_HW_GAIN_MASK 0xF
#घोषणा SI1133_ADCSENS_NB_MEAS(x)	fls(x) << SI1133_ADCSENS_SCALE_SHIFT

#घोषणा SI1133_ADCPOST_24BIT_EN BIT(6)
#घोषणा SI1133_ADCPOST_POSTSHIFT_BITQTY(x) (x & GENMASK(2, 0)) << 3

#घोषणा SI1133_PARAM_ADCMUX_SMALL_IR	0x0
#घोषणा SI1133_PARAM_ADCMUX_MED_IR	0x1
#घोषणा SI1133_PARAM_ADCMUX_LARGE_IR	0x2
#घोषणा SI1133_PARAM_ADCMUX_WHITE	0xB
#घोषणा SI1133_PARAM_ADCMUX_LARGE_WHITE	0xD
#घोषणा SI1133_PARAM_ADCMUX_UV		0x18
#घोषणा SI1133_PARAM_ADCMUX_UV_DEEP	0x19

#घोषणा SI1133_ERR_INVALID_CMD		0x0
#घोषणा SI1133_ERR_INVALID_LOCATION_CMD 0x1
#घोषणा SI1133_ERR_SATURATION_ADC_OR_OVERFLOW_ACCUMULATION 0x2
#घोषणा SI1133_ERR_OUTPUT_BUFFER_OVERFLOW 0x3

#घोषणा SI1133_COMPLETION_TIMEOUT_MS	500

#घोषणा SI1133_CMD_MINSLEEP_US_LOW	5000
#घोषणा SI1133_CMD_MINSLEEP_US_HIGH	7500
#घोषणा SI1133_CMD_TIMEOUT_MS		25
#घोषणा SI1133_CMD_LUX_TIMEOUT_MS	5000
#घोषणा SI1133_CMD_TIMEOUT_US		SI1133_CMD_TIMEOUT_MS * 1000

#घोषणा SI1133_REG_HOSTOUT(x)		(x) + 0x13

#घोषणा SI1133_MEASUREMENT_FREQUENCY 1250

#घोषणा SI1133_X_ORDER_MASK            0x0070
#घोषणा SI1133_Y_ORDER_MASK            0x0007
#घोषणा si1133_get_x_order(m)          ((m) & SI1133_X_ORDER_MASK) >> 4
#घोषणा si1133_get_y_order(m)          ((m) & SI1133_Y_ORDER_MASK)

#घोषणा SI1133_LUX_ADC_MASK		0xE
#घोषणा SI1133_ADC_THRESHOLD		16000
#घोषणा SI1133_INPUT_FRACTION_HIGH	7
#घोषणा SI1133_INPUT_FRACTION_LOW	15
#घोषणा SI1133_LUX_OUTPUT_FRACTION	12
#घोषणा SI1133_LUX_BUFFER_SIZE		9
#घोषणा SI1133_MEASURE_BUFFER_SIZE	3

अटल स्थिर पूर्णांक si1133_scale_available[] = अणु
	1, 2, 4, 8, 16, 32, 64, 128पूर्ण;

अटल IIO_CONST_ATTR(scale_available, "1 2 4 8 16 32 64 128");

अटल IIO_CONST_ATTR_INT_TIME_AVAIL("0.0244 0.0488 0.0975 0.195 0.390 0.780 "
				     "1.560 3.120 6.24 12.48 25.0 50.0");

/* A.K.A. HW_GAIN in datasheet */
क्रमागत si1133_पूर्णांक_समय अणु
	    _24_4_us = 0,
	    _48_8_us = 1,
	    _97_5_us = 2,
	   _195_0_us = 3,
	   _390_0_us = 4,
	   _780_0_us = 5,
	 _1_560_0_us = 6,
	 _3_120_0_us = 7,
	 _6_240_0_us = 8,
	_12_480_0_us = 9,
	_25_ms = 10,
	_50_ms = 11,
पूर्ण;

/* Integration समय in milliseconds, nanoseconds */
अटल स्थिर पूर्णांक si1133_पूर्णांक_समय_प्रकारable[][2] = अणु
	[_24_4_us] = अणु0, 24400पूर्ण,
	[_48_8_us] = अणु0, 48800पूर्ण,
	[_97_5_us] = अणु0, 97500पूर्ण,
	[_195_0_us] = अणु0, 195000पूर्ण,
	[_390_0_us] = अणु0, 390000पूर्ण,
	[_780_0_us] = अणु0, 780000पूर्ण,
	[_1_560_0_us] = अणु1, 560000पूर्ण,
	[_3_120_0_us] = अणु3, 120000पूर्ण,
	[_6_240_0_us] = अणु6, 240000पूर्ण,
	[_12_480_0_us] = अणु12, 480000पूर्ण,
	[_25_ms] = अणु25, 000000पूर्ण,
	[_50_ms] = अणु50, 000000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range si1133_reg_ranges[] = अणु
	regmap_reg_range(0x00, 0x02),
	regmap_reg_range(0x0A, 0x0B),
	regmap_reg_range(0x0F, 0x0F),
	regmap_reg_range(0x10, 0x12),
	regmap_reg_range(0x13, 0x2C),
पूर्ण;

अटल स्थिर काष्ठा regmap_range si1133_reg_ro_ranges[] = अणु
	regmap_reg_range(0x00, 0x02),
	regmap_reg_range(0x10, 0x2C),
पूर्ण;

अटल स्थिर काष्ठा regmap_range si1133_precious_ranges[] = अणु
	regmap_reg_range(0x12, 0x12),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table si1133_ग_लिखो_ranges_table = अणु
	.yes_ranges	= si1133_reg_ranges,
	.n_yes_ranges	= ARRAY_SIZE(si1133_reg_ranges),
	.no_ranges	= si1133_reg_ro_ranges,
	.n_no_ranges	= ARRAY_SIZE(si1133_reg_ro_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table si1133_पढ़ो_ranges_table = अणु
	.yes_ranges	= si1133_reg_ranges,
	.n_yes_ranges	= ARRAY_SIZE(si1133_reg_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table si1133_precious_table = अणु
	.yes_ranges	= si1133_precious_ranges,
	.n_yes_ranges	= ARRAY_SIZE(si1133_precious_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config si1133_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = 0x2C,

	.wr_table = &si1133_ग_लिखो_ranges_table,
	.rd_table = &si1133_पढ़ो_ranges_table,

	.precious_table = &si1133_precious_table,
पूर्ण;

काष्ठा si1133_data अणु
	काष्ठा regmap *regmap;
	काष्ठा i2c_client *client;

	/* Lock protecting one command at a समय can be processed */
	काष्ठा mutex mutex;

	पूर्णांक rsp_seq;
	u8 scan_mask;
	u8 adc_sens[6];
	u8 adc_config[6];

	काष्ठा completion completion;
पूर्ण;

काष्ठा si1133_coeff अणु
	s16 info;
	u16 mag;
पूर्ण;

काष्ठा si1133_lux_coeff अणु
	काष्ठा si1133_coeff coeff_high[4];
	काष्ठा si1133_coeff coeff_low[9];
पूर्ण;

अटल स्थिर काष्ठा si1133_lux_coeff lux_coeff = अणु
	अणु
		अणु  0,   209पूर्ण,
		अणु 1665,  93पूर्ण,
		अणु 2064,  65पूर्ण,
		अणु-2671, 234पूर्ण
	पूर्ण,
	अणु
		अणु    0,     0पूर्ण,
		अणु 1921, 29053पूर्ण,
		अणु-1022, 36363पूर्ण,
		अणु 2320, 20789पूर्ण,
		अणु -367, 57909पूर्ण,
		अणु-1774, 38240पूर्ण,
		अणु -608, 46775पूर्ण,
		अणु-1503, 51831पूर्ण,
		अणु-1886, 58928पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक si1133_calculate_polynomial_inner(s32 input, u8 fraction, u16 mag,
					     s8 shअगरt)
अणु
	वापस ((input << fraction) / mag) << shअगरt;
पूर्ण

अटल पूर्णांक si1133_calculate_output(s32 x, s32 y, u8 x_order, u8 y_order,
				   u8 input_fraction, s8 sign,
				   स्थिर काष्ठा si1133_coeff *coeffs)
अणु
	s8 shअगरt;
	पूर्णांक x1 = 1;
	पूर्णांक x2 = 1;
	पूर्णांक y1 = 1;
	पूर्णांक y2 = 1;

	shअगरt = ((u16)coeffs->info & 0xFF00) >> 8;
	shअगरt ^= 0xFF;
	shअगरt += 1;
	shअगरt = -shअगरt;

	अगर (x_order > 0) अणु
		x1 = si1133_calculate_polynomial_inner(x, input_fraction,
						       coeffs->mag, shअगरt);
		अगर (x_order > 1)
			x2 = x1;
	पूर्ण

	अगर (y_order > 0) अणु
		y1 = si1133_calculate_polynomial_inner(y, input_fraction,
						       coeffs->mag, shअगरt);
		अगर (y_order > 1)
			y2 = y1;
	पूर्ण

	वापस sign * x1 * x2 * y1 * y2;
पूर्ण

/*
 * The algorithm is from:
 * https://siliconद_असल.github.io/Gecko_SDK_Doc/efm32zg/hपंचांगl/si1133_8c_source.hपंचांगl#l00716
 */
अटल पूर्णांक si1133_calc_polynomial(s32 x, s32 y, u8 input_fraction, u8 num_coeff,
				  स्थिर काष्ठा si1133_coeff *coeffs)
अणु
	u8 x_order, y_order;
	u8 counter;
	s8 sign;
	पूर्णांक output = 0;

	क्रम (counter = 0; counter < num_coeff; counter++) अणु
		अगर (coeffs->info < 0)
			sign = -1;
		अन्यथा
			sign = 1;

		x_order = si1133_get_x_order(coeffs->info);
		y_order = si1133_get_y_order(coeffs->info);

		अगर ((x_order == 0) && (y_order == 0))
			output +=
			       sign * coeffs->mag << SI1133_LUX_OUTPUT_FRACTION;
		अन्यथा
			output += si1133_calculate_output(x, y, x_order,
							  y_order,
							  input_fraction, sign,
							  coeffs);
		coeffs++;
	पूर्ण

	वापस असल(output);
पूर्ण

अटल पूर्णांक si1133_cmd_reset_sw(काष्ठा si1133_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	अचिन्हित पूर्णांक resp;
	अचिन्हित दीर्घ समयout;
	पूर्णांक err;

	err = regmap_ग_लिखो(data->regmap, SI1133_REG_COMMAND,
			   SI1133_CMD_RESET_SW);
	अगर (err)
		वापस err;

	समयout = jअगरfies + msecs_to_jअगरfies(SI1133_CMD_TIMEOUT_MS);
	जबतक (true) अणु
		err = regmap_पढ़ो(data->regmap, SI1133_REG_RESPONSE0, &resp);
		अगर (err == -ENXIO) अणु
			usleep_range(SI1133_CMD_MINSLEEP_US_LOW,
				     SI1133_CMD_MINSLEEP_US_HIGH);
			जारी;
		पूर्ण

		अगर ((resp & SI1133_MAX_CMD_CTR) == SI1133_MAX_CMD_CTR)
			अवरोध;

		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_warn(dev, "Timeout on reset ctr resp: %d\n", resp);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	अगर (!err)
		data->rsp_seq = SI1133_MAX_CMD_CTR;

	वापस err;
पूर्ण

अटल पूर्णांक si1133_parse_response_err(काष्ठा device *dev, u32 resp, u8 cmd)
अणु
	resp &= 0xF;

	चयन (resp) अणु
	हाल SI1133_ERR_OUTPUT_BUFFER_OVERFLOW:
		dev_warn(dev, "Output buffer overflow: %#02hhx\n", cmd);
		वापस -EOVERFLOW;
	हाल SI1133_ERR_SATURATION_ADC_OR_OVERFLOW_ACCUMULATION:
		dev_warn(dev, "Saturation of the ADC or overflow of accumulation: %#02hhx\n",
			 cmd);
		वापस -EOVERFLOW;
	हाल SI1133_ERR_INVALID_LOCATION_CMD:
		dev_warn(dev,
			 "Parameter access to an invalid location: %#02hhx\n",
			 cmd);
		वापस -EINVAL;
	हाल SI1133_ERR_INVALID_CMD:
		dev_warn(dev, "Invalid command %#02hhx\n", cmd);
		वापस -EINVAL;
	शेष:
		dev_warn(dev, "Unknown error %#02hhx\n", cmd);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक si1133_cmd_reset_counter(काष्ठा si1133_data *data)
अणु
	पूर्णांक err = regmap_ग_लिखो(data->regmap, SI1133_REG_COMMAND,
			       SI1133_CMD_RESET_CTR);
	अगर (err)
		वापस err;

	data->rsp_seq = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक si1133_command(काष्ठा si1133_data *data, u8 cmd)
अणु
	काष्ठा device *dev = &data->client->dev;
	u32 resp;
	पूर्णांक err;
	पूर्णांक expected_seq;

	mutex_lock(&data->mutex);

	expected_seq = (data->rsp_seq + 1) & SI1133_MAX_CMD_CTR;

	अगर (cmd == SI1133_CMD_FORCE)
		reinit_completion(&data->completion);

	err = regmap_ग_लिखो(data->regmap, SI1133_REG_COMMAND, cmd);
	अगर (err) अणु
		dev_warn(dev, "Failed to write command %#02hhx, ret=%d\n", cmd,
			 err);
		जाओ out;
	पूर्ण

	अगर (cmd == SI1133_CMD_FORCE) अणु
		/* रुको क्रम irq */
		अगर (!रुको_क्रम_completion_समयout(&data->completion,
			msecs_to_jअगरfies(SI1133_COMPLETION_TIMEOUT_MS))) अणु
			err = -ETIMEDOUT;
			जाओ out;
		पूर्ण
		err = regmap_पढ़ो(data->regmap, SI1133_REG_RESPONSE0, &resp);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अणु
		err = regmap_पढ़ो_poll_समयout(data->regmap,
					       SI1133_REG_RESPONSE0, resp,
					       (resp & SI1133_CMD_SEQ_MASK) ==
					       expected_seq ||
					       (resp & SI1133_CMD_ERR_MASK),
					       SI1133_CMD_MINSLEEP_US_LOW,
					       SI1133_CMD_TIMEOUT_MS * 1000);
		अगर (err) अणु
			dev_warn(dev,
				 "Failed to read command %#02hhx, ret=%d\n",
				 cmd, err);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (resp & SI1133_CMD_ERR_MASK) अणु
		err = si1133_parse_response_err(dev, resp, cmd);
		si1133_cmd_reset_counter(data);
	पूर्ण अन्यथा अणु
		data->rsp_seq = expected_seq;
	पूर्ण

out:
	mutex_unlock(&data->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक si1133_param_set(काष्ठा si1133_data *data, u8 param, u32 value)
अणु
	पूर्णांक err = regmap_ग_लिखो(data->regmap, SI1133_REG_HOSTIN0, value);

	अगर (err)
		वापस err;

	वापस si1133_command(data, SI1133_CMD_PARAM_SET |
			      (param & SI1133_CMD_PARAM_MASK));
पूर्ण

अटल पूर्णांक si1133_param_query(काष्ठा si1133_data *data, u8 param, u32 *result)
अणु
	पूर्णांक err = si1133_command(data, SI1133_CMD_PARAM_QUERY |
				 (param & SI1133_CMD_PARAM_MASK));
	अगर (err)
		वापस err;

	वापस regmap_पढ़ो(data->regmap, SI1133_REG_RESPONSE1, result);
पूर्ण

#घोषणा SI1133_CHANNEL(_ch, _type) \
	.type = _type, \
	.channel = _ch, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_INT_TIME) | \
		BIT(IIO_CHAN_INFO_SCALE) | \
		BIT(IIO_CHAN_INFO_HARDWAREGAIN), \

अटल स्थिर काष्ठा iio_chan_spec si1133_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.channel = 0,
	पूर्ण,
	अणु
		SI1133_CHANNEL(SI1133_PARAM_ADCMUX_WHITE, IIO_INTENSITY)
		.channel2 = IIO_MOD_LIGHT_BOTH,
	पूर्ण,
	अणु
		SI1133_CHANNEL(SI1133_PARAM_ADCMUX_LARGE_WHITE, IIO_INTENSITY)
		.channel2 = IIO_MOD_LIGHT_BOTH,
		.extend_name = "large",
	पूर्ण,
	अणु
		SI1133_CHANNEL(SI1133_PARAM_ADCMUX_SMALL_IR, IIO_INTENSITY)
		.extend_name = "small",
		.modअगरied = 1,
		.channel2 = IIO_MOD_LIGHT_IR,
	पूर्ण,
	अणु
		SI1133_CHANNEL(SI1133_PARAM_ADCMUX_MED_IR, IIO_INTENSITY)
		.modअगरied = 1,
		.channel2 = IIO_MOD_LIGHT_IR,
	पूर्ण,
	अणु
		SI1133_CHANNEL(SI1133_PARAM_ADCMUX_LARGE_IR, IIO_INTENSITY)
		.extend_name = "large",
		.modअगरied = 1,
		.channel2 = IIO_MOD_LIGHT_IR,
	पूर्ण,
	अणु
		SI1133_CHANNEL(SI1133_PARAM_ADCMUX_UV, IIO_UVINDEX)
	पूर्ण,
	अणु
		SI1133_CHANNEL(SI1133_PARAM_ADCMUX_UV_DEEP, IIO_UVINDEX)
		.modअगरied = 1,
		.channel2 = IIO_MOD_LIGHT_DUV,
	पूर्ण
पूर्ण;

अटल पूर्णांक si1133_get_पूर्णांक_समय_index(पूर्णांक milliseconds, पूर्णांक nanoseconds)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(si1133_पूर्णांक_समय_प्रकारable); i++) अणु
		अगर (milliseconds == si1133_पूर्णांक_समय_प्रकारable[i][0] &&
		    nanoseconds == si1133_पूर्णांक_समय_प्रकारable[i][1])
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक si1133_set_पूर्णांकegration_समय(काष्ठा si1133_data *data, u8 adc,
				       पूर्णांक milliseconds, पूर्णांक nanoseconds)
अणु
	पूर्णांक index;

	index = si1133_get_पूर्णांक_समय_index(milliseconds, nanoseconds);
	अगर (index < 0)
		वापस index;

	data->adc_sens[adc] &= 0xF0;
	data->adc_sens[adc] |= index;

	वापस si1133_param_set(data, SI1133_PARAM_REG_ADCSENS(0),
				data->adc_sens[adc]);
पूर्ण

अटल पूर्णांक si1133_set_chlist(काष्ठा si1133_data *data, u8 scan_mask)
अणु
	/* channel list alपढ़ोy set, no need to reprogram */
	अगर (data->scan_mask == scan_mask)
		वापस 0;

	data->scan_mask = scan_mask;

	वापस si1133_param_set(data, SI1133_PARAM_REG_CHAN_LIST, scan_mask);
पूर्ण

अटल पूर्णांक si1133_chan_set_adcconfig(काष्ठा si1133_data *data, u8 adc,
				     u8 adc_config)
अणु
	पूर्णांक err;

	err = si1133_param_set(data, SI1133_PARAM_REG_ADCCONFIG(adc),
			       adc_config);
	अगर (err)
		वापस err;

	data->adc_config[adc] = adc_config;

	वापस 0;
पूर्ण

अटल पूर्णांक si1133_update_adcconfig(काष्ठा si1133_data *data, uपूर्णांक8_t adc,
				   u8 mask, u8 shअगरt, u8 value)
अणु
	u32 adc_config;
	पूर्णांक err;

	err = si1133_param_query(data, SI1133_PARAM_REG_ADCCONFIG(adc),
				 &adc_config);
	अगर (err)
		वापस err;

	adc_config &= ~mask;
	adc_config |= (value << shअगरt);

	वापस si1133_chan_set_adcconfig(data, adc, adc_config);
पूर्ण

अटल पूर्णांक si1133_set_adcmux(काष्ठा si1133_data *data, u8 adc, u8 mux)
अणु
	अगर ((mux & data->adc_config[adc]) == mux)
		वापस 0; /* mux alपढ़ोy set to correct value */

	वापस si1133_update_adcconfig(data, adc, SI1133_ADCMUX_MASK, 0, mux);
पूर्ण

अटल पूर्णांक si1133_क्रमce_measurement(काष्ठा si1133_data *data)
अणु
	वापस si1133_command(data, SI1133_CMD_FORCE);
पूर्ण

अटल पूर्णांक si1133_bulk_पढ़ो(काष्ठा si1133_data *data, u8 start_reg, u8 length,
			    u8 *buffer)
अणु
	पूर्णांक err;

	err = si1133_क्रमce_measurement(data);
	अगर (err)
		वापस err;

	वापस regmap_bulk_पढ़ो(data->regmap, start_reg, buffer, length);
पूर्ण

अटल पूर्णांक si1133_measure(काष्ठा si1133_data *data,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  पूर्णांक *val)
अणु
	पूर्णांक err;

	u8 buffer[SI1133_MEASURE_BUFFER_SIZE];

	err = si1133_set_adcmux(data, 0, chan->channel);
	अगर (err)
		वापस err;

	/* Deactivate lux measurements अगर they were active */
	err = si1133_set_chlist(data, BIT(0));
	अगर (err)
		वापस err;

	err = si1133_bulk_पढ़ो(data, SI1133_REG_HOSTOUT(0), माप(buffer),
			       buffer);
	अगर (err)
		वापस err;

	*val = sign_extend32(get_unaligned_be24(&buffer[0]), 23);

	वापस err;
पूर्ण

अटल irqवापस_t si1133_thपढ़ोed_irq_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *iio_dev = निजी;
	काष्ठा si1133_data *data = iio_priv(iio_dev);
	u32 irq_status;
	पूर्णांक err;

	err = regmap_पढ़ो(data->regmap, SI1133_REG_IRQ_STATUS, &irq_status);
	अगर (err) अणु
		dev_err_ratelimited(&iio_dev->dev, "Error reading IRQ\n");
		जाओ out;
	पूर्ण

	अगर (irq_status != data->scan_mask)
		वापस IRQ_NONE;

out:
	complete(&data->completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक si1133_scale_to_swgain(पूर्णांक scale_पूर्णांकeger, पूर्णांक scale_fractional)
अणु
	scale_पूर्णांकeger = find_बंदst(scale_पूर्णांकeger, si1133_scale_available,
				     ARRAY_SIZE(si1133_scale_available));
	अगर (scale_पूर्णांकeger < 0 ||
	    scale_पूर्णांकeger > ARRAY_SIZE(si1133_scale_available) ||
	    scale_fractional != 0)
		वापस -EINVAL;

	वापस scale_पूर्णांकeger;
पूर्ण

अटल पूर्णांक si1133_chan_set_adcsens(काष्ठा si1133_data *data, u8 adc,
				   u8 adc_sens)
अणु
	पूर्णांक err;

	err = si1133_param_set(data, SI1133_PARAM_REG_ADCSENS(adc), adc_sens);
	अगर (err)
		वापस err;

	data->adc_sens[adc] = adc_sens;

	वापस 0;
पूर्ण

अटल पूर्णांक si1133_update_adcsens(काष्ठा si1133_data *data, u8 mask,
				 u8 shअगरt, u8 value)
अणु
	पूर्णांक err;
	u32 adc_sens;

	err = si1133_param_query(data, SI1133_PARAM_REG_ADCSENS(0),
				 &adc_sens);
	अगर (err)
		वापस err;

	adc_sens &= ~mask;
	adc_sens |= (value << shअगरt);

	वापस si1133_chan_set_adcsens(data, 0, adc_sens);
पूर्ण

अटल पूर्णांक si1133_get_lux(काष्ठा si1133_data *data, पूर्णांक *val)
अणु
	पूर्णांक err;
	पूर्णांक lux;
	s32 high_vis;
	s32 low_vis;
	s32 ir;
	u8 buffer[SI1133_LUX_BUFFER_SIZE];

	/* Activate lux channels */
	err = si1133_set_chlist(data, SI1133_LUX_ADC_MASK);
	अगर (err)
		वापस err;

	err = si1133_bulk_पढ़ो(data, SI1133_REG_HOSTOUT(0),
			       SI1133_LUX_BUFFER_SIZE, buffer);
	अगर (err)
		वापस err;

	high_vis = sign_extend32(get_unaligned_be24(&buffer[0]), 23);

	low_vis = sign_extend32(get_unaligned_be24(&buffer[3]), 23);

	ir = sign_extend32(get_unaligned_be24(&buffer[6]), 23);

	अगर (high_vis > SI1133_ADC_THRESHOLD || ir > SI1133_ADC_THRESHOLD)
		lux = si1133_calc_polynomial(high_vis, ir,
					     SI1133_INPUT_FRACTION_HIGH,
					     ARRAY_SIZE(lux_coeff.coeff_high),
					     &lux_coeff.coeff_high[0]);
	अन्यथा
		lux = si1133_calc_polynomial(low_vis, ir,
					     SI1133_INPUT_FRACTION_LOW,
					     ARRAY_SIZE(lux_coeff.coeff_low),
					     &lux_coeff.coeff_low[0]);

	*val = lux >> SI1133_LUX_OUTPUT_FRACTION;

	वापस err;
पूर्ण

अटल पूर्णांक si1133_पढ़ो_raw(काष्ठा iio_dev *iio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा si1133_data *data = iio_priv(iio_dev);
	u8 adc_sens = data->adc_sens[0];
	पूर्णांक err;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			err = si1133_get_lux(data, val);
			अगर (err)
				वापस err;

			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
		हाल IIO_UVINDEX:
			err = si1133_measure(data, chan, val);
			अगर (err)
				वापस err;

			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_INT_TIME:
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
		हाल IIO_UVINDEX:
			adc_sens &= SI1133_ADCSENS_HW_GAIN_MASK;

			*val = si1133_पूर्णांक_समय_प्रकारable[adc_sens][0];
			*val2 = si1133_पूर्णांक_समय_प्रकारable[adc_sens][1];
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
		हाल IIO_UVINDEX:
			adc_sens &= SI1133_ADCSENS_SCALE_MASK;
			adc_sens >>= SI1133_ADCSENS_SCALE_SHIFT;

			*val = BIT(adc_sens);

			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
		हाल IIO_UVINDEX:
			adc_sens >>= SI1133_ADCSENS_HSIG_SHIFT;

			*val = adc_sens;

			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक si1133_ग_लिखो_raw(काष्ठा iio_dev *iio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा si1133_data *data = iio_priv(iio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
		हाल IIO_UVINDEX:
			val = si1133_scale_to_swgain(val, val2);
			अगर (val < 0)
				वापस val;

			वापस si1133_update_adcsens(data,
						     SI1133_ADCSENS_SCALE_MASK,
						     SI1133_ADCSENS_SCALE_SHIFT,
						     val);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_INT_TIME:
		वापस si1133_set_पूर्णांकegration_समय(data, 0, val, val2);
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
		हाल IIO_UVINDEX:
			अगर (val != 0 && val != 1)
				वापस -EINVAL;

			वापस si1133_update_adcsens(data,
						     SI1133_ADCSENS_HSIG_MASK,
						     SI1133_ADCSENS_HSIG_SHIFT,
						     val);
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा attribute *si1133_attributes[] = अणु
	&iio_स्थिर_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	&iio_स्थिर_attr_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group si1133_attribute_group = अणु
	.attrs = si1133_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info si1133_info = अणु
	.पढ़ो_raw = si1133_पढ़ो_raw,
	.ग_लिखो_raw = si1133_ग_लिखो_raw,
	.attrs = &si1133_attribute_group,
पूर्ण;

/*
 * si1133_init_lux_channels - Configure 3 dअगरferent channels(adc) (1,2 and 3)
 * The channel configuration क्रम the lux measurement was taken from :
 * https://siliconद_असल.github.io/Gecko_SDK_Doc/efm32zg/hपंचांगl/si1133_8c_source.hपंचांगl#l00578
 *
 * Reserved the channel 0 क्रम the other raw measurements
 */
अटल पूर्णांक si1133_init_lux_channels(काष्ठा si1133_data *data)
अणु
	पूर्णांक err;

	err = si1133_chan_set_adcconfig(data, 1,
					SI1133_ADCCONFIG_DECIM_RATE(1) |
					SI1133_PARAM_ADCMUX_LARGE_WHITE);
	अगर (err)
		वापस err;

	err = si1133_param_set(data, SI1133_PARAM_REG_ADCPOST(1),
			       SI1133_ADCPOST_24BIT_EN |
			       SI1133_ADCPOST_POSTSHIFT_BITQTY(0));
	अगर (err)
		वापस err;
	err = si1133_chan_set_adcsens(data, 1, SI1133_ADCSENS_HSIG_MASK |
				      SI1133_ADCSENS_NB_MEAS(64) | _48_8_us);
	अगर (err)
		वापस err;

	err = si1133_chan_set_adcconfig(data, 2,
					SI1133_ADCCONFIG_DECIM_RATE(1) |
					SI1133_PARAM_ADCMUX_LARGE_WHITE);
	अगर (err)
		वापस err;

	err = si1133_param_set(data, SI1133_PARAM_REG_ADCPOST(2),
			       SI1133_ADCPOST_24BIT_EN |
			       SI1133_ADCPOST_POSTSHIFT_BITQTY(2));
	अगर (err)
		वापस err;

	err = si1133_chan_set_adcsens(data, 2, SI1133_ADCSENS_HSIG_MASK |
				      SI1133_ADCSENS_NB_MEAS(1) | _3_120_0_us);
	अगर (err)
		वापस err;

	err = si1133_chan_set_adcconfig(data, 3,
					SI1133_ADCCONFIG_DECIM_RATE(1) |
					SI1133_PARAM_ADCMUX_MED_IR);
	अगर (err)
		वापस err;

	err = si1133_param_set(data, SI1133_PARAM_REG_ADCPOST(3),
			       SI1133_ADCPOST_24BIT_EN |
			       SI1133_ADCPOST_POSTSHIFT_BITQTY(2));
	अगर (err)
		वापस err;

	वापस  si1133_chan_set_adcsens(data, 3, SI1133_ADCSENS_HSIG_MASK |
					SI1133_ADCSENS_NB_MEAS(64) | _48_8_us);
पूर्ण

अटल पूर्णांक si1133_initialize(काष्ठा si1133_data *data)
अणु
	पूर्णांक err;

	err = si1133_cmd_reset_sw(data);
	अगर (err)
		वापस err;

	/* Turn off स्वतःnomous mode */
	err = si1133_param_set(data, SI1133_REG_MEAS_RATE, 0);
	अगर (err)
		वापस err;

	err = si1133_init_lux_channels(data);
	अगर (err)
		वापस err;

	वापस regmap_ग_लिखो(data->regmap, SI1133_REG_IRQ_ENABLE,
			    SI1133_IRQ_CHANNEL_ENABLE);
पूर्ण

अटल पूर्णांक si1133_validate_ids(काष्ठा iio_dev *iio_dev)
अणु
	काष्ठा si1133_data *data = iio_priv(iio_dev);

	अचिन्हित पूर्णांक part_id, rev_id, mfr_id;
	पूर्णांक err;

	err = regmap_पढ़ो(data->regmap, SI1133_REG_PART_ID, &part_id);
	अगर (err)
		वापस err;

	err = regmap_पढ़ो(data->regmap, SI1133_REG_REV_ID, &rev_id);
	अगर (err)
		वापस err;

	err = regmap_पढ़ो(data->regmap, SI1133_REG_MFR_ID, &mfr_id);
	अगर (err)
		वापस err;

	dev_info(&iio_dev->dev,
		 "Device ID part %#02hhx rev %#02hhx mfr %#02hhx\n",
		 part_id, rev_id, mfr_id);
	अगर (part_id != SI1133_PART_ID) अणु
		dev_err(&iio_dev->dev,
			"Part ID mismatch got %#02hhx, expected %#02x\n",
			part_id, SI1133_PART_ID);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si1133_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा si1133_data *data;
	काष्ठा iio_dev *iio_dev;
	पूर्णांक err;

	iio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!iio_dev)
		वापस -ENOMEM;

	data = iio_priv(iio_dev);

	init_completion(&data->completion);

	data->regmap = devm_regmap_init_i2c(client, &si1133_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		err = PTR_ERR(data->regmap);
		dev_err(&client->dev, "Failed to initialise regmap: %d\n", err);
		वापस err;
	पूर्ण

	i2c_set_clientdata(client, iio_dev);
	data->client = client;

	iio_dev->name = id->name;
	iio_dev->channels = si1133_channels;
	iio_dev->num_channels = ARRAY_SIZE(si1133_channels);
	iio_dev->info = &si1133_info;
	iio_dev->modes = INDIO_सूचीECT_MODE;

	mutex_init(&data->mutex);

	err = si1133_validate_ids(iio_dev);
	अगर (err)
		वापस err;

	err = si1133_initialize(data);
	अगर (err) अणु
		dev_err(&client->dev,
			"Error when initializing chip: %d\n", err);
		वापस err;
	पूर्ण

	अगर (!client->irq) अणु
		dev_err(&client->dev,
			"Required interrupt not provided, cannot proceed\n");
		वापस -EINVAL;
	पूर्ण

	err = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य,
					si1133_thपढ़ोed_irq_handler,
					IRQF_ONESHOT | IRQF_SHARED,
					client->name, iio_dev);
	अगर (err) अणु
		dev_warn(&client->dev, "Request irq %d failed: %i\n",
			 client->irq, err);
		वापस err;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&client->dev, iio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id si1133_ids[] = अणु
	अणु "si1133", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, si1133_ids);

अटल काष्ठा i2c_driver si1133_driver = अणु
	.driver = अणु
	    .name   = "si1133",
	पूर्ण,
	.probe  = si1133_probe,
	.id_table = si1133_ids,
पूर्ण;

module_i2c_driver(si1133_driver);

MODULE_AUTHOR("Maxime Roussin-Belanger <maxime.roussinbelanger@gmail.com>");
MODULE_DESCRIPTION("Silabs SI1133, UV index sensor and ambient light sensor driver");
MODULE_LICENSE("GPL");
