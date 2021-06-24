<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * si1145.c - Support क्रम Siद_असल SI1132 and SI1141/2/3/5/6/7 combined ambient
 * light, UV index and proximity sensors
 *
 * Copyright 2014-16 Peter Meerwald-Stadler <pmeerw@pmeerw.net>
 * Copyright 2016 Crestez Dan Leonard <leonard.crestez@पूर्णांकel.com>
 *
 * SI1132 (7-bit I2C slave address 0x60)
 * SI1141/2/3 (7-bit I2C slave address 0x5a)
 * SI1145/6/6 (7-bit I2C slave address 0x60)
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/util_macros.h>

#घोषणा SI1145_REG_PART_ID		0x00
#घोषणा SI1145_REG_REV_ID		0x01
#घोषणा SI1145_REG_SEQ_ID		0x02
#घोषणा SI1145_REG_INT_CFG		0x03
#घोषणा SI1145_REG_IRQ_ENABLE		0x04
#घोषणा SI1145_REG_IRQ_MODE		0x05
#घोषणा SI1145_REG_HW_KEY		0x07
#घोषणा SI1145_REG_MEAS_RATE		0x08
#घोषणा SI1145_REG_PS_LED21		0x0f
#घोषणा SI1145_REG_PS_LED3		0x10
#घोषणा SI1145_REG_UCOEF1		0x13
#घोषणा SI1145_REG_UCOEF2		0x14
#घोषणा SI1145_REG_UCOEF3		0x15
#घोषणा SI1145_REG_UCOEF4		0x16
#घोषणा SI1145_REG_PARAM_WR		0x17
#घोषणा SI1145_REG_COMMAND		0x18
#घोषणा SI1145_REG_RESPONSE		0x20
#घोषणा SI1145_REG_IRQ_STATUS		0x21
#घोषणा SI1145_REG_ALSVIS_DATA		0x22
#घोषणा SI1145_REG_ALSIR_DATA		0x24
#घोषणा SI1145_REG_PS1_DATA		0x26
#घोषणा SI1145_REG_PS2_DATA		0x28
#घोषणा SI1145_REG_PS3_DATA		0x2a
#घोषणा SI1145_REG_AUX_DATA		0x2c
#घोषणा SI1145_REG_PARAM_RD		0x2e
#घोषणा SI1145_REG_CHIP_STAT		0x30

#घोषणा SI1145_UCOEF1_DEFAULT		0x7b
#घोषणा SI1145_UCOEF2_DEFAULT		0x6b
#घोषणा SI1145_UCOEF3_DEFAULT		0x01
#घोषणा SI1145_UCOEF4_DEFAULT		0x00

/* Helper to figure out PS_LED रेजिस्टर / shअगरt per channel */
#घोषणा SI1145_PS_LED_REG(ch) \
	(((ch) == 2) ? SI1145_REG_PS_LED3 : SI1145_REG_PS_LED21)
#घोषणा SI1145_PS_LED_SHIFT(ch) \
	(((ch) == 1) ? 4 : 0)

/* Parameter offsets */
#घोषणा SI1145_PARAM_CHLIST		0x01
#घोषणा SI1145_PARAM_PSLED12_SELECT	0x02
#घोषणा SI1145_PARAM_PSLED3_SELECT	0x03
#घोषणा SI1145_PARAM_PS_ENCODING	0x05
#घोषणा SI1145_PARAM_ALS_ENCODING	0x06
#घोषणा SI1145_PARAM_PS1_ADC_MUX	0x07
#घोषणा SI1145_PARAM_PS2_ADC_MUX	0x08
#घोषणा SI1145_PARAM_PS3_ADC_MUX	0x09
#घोषणा SI1145_PARAM_PS_ADC_COUNTER	0x0a
#घोषणा SI1145_PARAM_PS_ADC_GAIN	0x0b
#घोषणा SI1145_PARAM_PS_ADC_MISC	0x0c
#घोषणा SI1145_PARAM_ALS_ADC_MUX	0x0d
#घोषणा SI1145_PARAM_ALSIR_ADC_MUX	0x0e
#घोषणा SI1145_PARAM_AUX_ADC_MUX	0x0f
#घोषणा SI1145_PARAM_ALSVIS_ADC_COUNTER	0x10
#घोषणा SI1145_PARAM_ALSVIS_ADC_GAIN	0x11
#घोषणा SI1145_PARAM_ALSVIS_ADC_MISC	0x12
#घोषणा SI1145_PARAM_LED_RECOVERY	0x1c
#घोषणा SI1145_PARAM_ALSIR_ADC_COUNTER	0x1d
#घोषणा SI1145_PARAM_ALSIR_ADC_GAIN	0x1e
#घोषणा SI1145_PARAM_ALSIR_ADC_MISC	0x1f
#घोषणा SI1145_PARAM_ADC_OFFSET		0x1a

/* Channel enable masks क्रम CHLIST parameter */
#घोषणा SI1145_CHLIST_EN_PS1		BIT(0)
#घोषणा SI1145_CHLIST_EN_PS2		BIT(1)
#घोषणा SI1145_CHLIST_EN_PS3		BIT(2)
#घोषणा SI1145_CHLIST_EN_ALSVIS		BIT(4)
#घोषणा SI1145_CHLIST_EN_ALSIR		BIT(5)
#घोषणा SI1145_CHLIST_EN_AUX		BIT(6)
#घोषणा SI1145_CHLIST_EN_UV		BIT(7)

/* Proximity measurement mode क्रम ADC_MISC parameter */
#घोषणा SI1145_PS_ADC_MODE_NORMAL	BIT(2)
/* Signal range mask क्रम ADC_MISC parameter */
#घोषणा SI1145_ADC_MISC_RANGE		BIT(5)

/* Commands क्रम REG_COMMAND */
#घोषणा SI1145_CMD_NOP			0x00
#घोषणा SI1145_CMD_RESET		0x01
#घोषणा SI1145_CMD_PS_FORCE		0x05
#घोषणा SI1145_CMD_ALS_FORCE		0x06
#घोषणा SI1145_CMD_PSALS_FORCE		0x07
#घोषणा SI1145_CMD_PS_PAUSE		0x09
#घोषणा SI1145_CMD_ALS_PAUSE		0x0a
#घोषणा SI1145_CMD_PSALS_PAUSE		0x0b
#घोषणा SI1145_CMD_PS_AUTO		0x0d
#घोषणा SI1145_CMD_ALS_AUTO		0x0e
#घोषणा SI1145_CMD_PSALS_AUTO		0x0f
#घोषणा SI1145_CMD_PARAM_QUERY		0x80
#घोषणा SI1145_CMD_PARAM_SET		0xa0

#घोषणा SI1145_RSP_INVALID_SETTING	0x80
#घोषणा SI1145_RSP_COUNTER_MASK		0x0F

/* Minimum sleep after each command to ensure it's received */
#घोषणा SI1145_COMMAND_MINSLEEP_MS	5
/* Return -ETIMEDOUT after this दीर्घ */
#घोषणा SI1145_COMMAND_TIMEOUT_MS	25

/* Interrupt configuration masks क्रम INT_CFG रेजिस्टर */
#घोषणा SI1145_INT_CFG_OE		BIT(0) /* enable पूर्णांकerrupt */
#घोषणा SI1145_INT_CFG_MODE		BIT(1) /* स्वतः reset पूर्णांकerrupt pin */

/* Interrupt enable masks क्रम IRQ_ENABLE रेजिस्टर */
#घोषणा SI1145_MASK_ALL_IE		(BIT(4) | BIT(3) | BIT(2) | BIT(0))

#घोषणा SI1145_MUX_TEMP			0x65
#घोषणा SI1145_MUX_VDD			0x75

/* Proximity LED current; see Table 2 in datasheet */
#घोषणा SI1145_LED_CURRENT_45mA		0x04

क्रमागत अणु
	SI1132,
	SI1141,
	SI1142,
	SI1143,
	SI1145,
	SI1146,
	SI1147,
पूर्ण;

काष्ठा si1145_part_info अणु
	u8 part;
	स्थिर काष्ठा iio_info *iio_info;
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
	अचिन्हित पूर्णांक num_leds;
	bool uncompressed_meas_rate;
पूर्ण;

/**
 * काष्ठा si1145_data - si1145 chip state data
 * @client:	I2C client
 * @lock:	mutex to protect shared state.
 * @cmdlock:	Low-level mutex to protect command execution only
 * @rsp_seq:	Next expected response number or -1 अगर counter reset required
 * @scan_mask:	Saved scan mask to aव्योम duplicate set_chlist
 * @स्वतःnomous: If स्वतःmatic measurements are active (क्रम buffer support)
 * @part_info:	Part inक्रमmation
 * @trig:	Poपूर्णांकer to iio trigger
 * @meas_rate:	Value of MEAS_RATE रेजिस्टर. Only set in HW in स्वतः mode
 * @buffer:	Used to pack data पढ़ो from sensor.
 */
काष्ठा si1145_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	काष्ठा mutex cmdlock;
	पूर्णांक rsp_seq;
	स्थिर काष्ठा si1145_part_info *part_info;
	अचिन्हित दीर्घ scan_mask;
	bool स्वतःnomous;
	काष्ठा iio_trigger *trig;
	पूर्णांक meas_rate;
	/*
	 * Ensure बारtamp will be naturally aligned अगर present.
	 * Maximum buffer size (may be only partly used अगर not all
	 * channels are enabled):
	 *   6*2 bytes channels data + 4 bytes alignment +
	 *   8 bytes बारtamp
	 */
	u8 buffer[24] __aligned(8);
पूर्ण;

/*
 * __si1145_command_reset() - Send CMD_NOP and रुको क्रम response 0
 *
 * Does not modअगरy data->rsp_seq
 *
 * Return: 0 on success and -त्रुटि_सं on error.
 */
अटल पूर्णांक __si1145_command_reset(काष्ठा si1145_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	अचिन्हित दीर्घ stop_jअगरfies;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, SI1145_REG_COMMAND,
						      SI1145_CMD_NOP);
	अगर (ret < 0)
		वापस ret;
	msleep(SI1145_COMMAND_MINSLEEP_MS);

	stop_jअगरfies = jअगरfies + SI1145_COMMAND_TIMEOUT_MS * HZ / 1000;
	जबतक (true) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client,
					       SI1145_REG_RESPONSE);
		अगर (ret <= 0)
			वापस ret;
		अगर (समय_after(jअगरfies, stop_jअगरfies)) अणु
			dev_warn(dev, "timeout on reset\n");
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(SI1145_COMMAND_MINSLEEP_MS);
		जारी;
	पूर्ण
पूर्ण

/*
 * si1145_command() - Execute a command and poll the response रेजिस्टर
 *
 * All conversion overflows are reported as -EOVERFLOW
 * INVALID_SETTING is reported as -EINVAL
 * Timeouts are reported as -ETIMEDOUT
 *
 * Return: 0 on success or -त्रुटि_सं on failure
 */
अटल पूर्णांक si1145_command(काष्ठा si1145_data *data, u8 cmd)
अणु
	काष्ठा device *dev = &data->client->dev;
	अचिन्हित दीर्घ stop_jअगरfies;
	पूर्णांक ret;

	mutex_lock(&data->cmdlock);

	अगर (data->rsp_seq < 0) अणु
		ret = __si1145_command_reset(data);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to reset command counter, ret=%d\n",
				ret);
			जाओ out;
		पूर्ण
		data->rsp_seq = 0;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, SI1145_REG_COMMAND, cmd);
	अगर (ret) अणु
		dev_warn(dev, "failed to write command, ret=%d\n", ret);
		जाओ out;
	पूर्ण
	/* Sleep a little to ensure the command is received */
	msleep(SI1145_COMMAND_MINSLEEP_MS);

	stop_jअगरfies = jअगरfies + SI1145_COMMAND_TIMEOUT_MS * HZ / 1000;
	जबतक (true) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client,
					       SI1145_REG_RESPONSE);
		अगर (ret < 0) अणु
			dev_warn(dev, "failed to read response, ret=%d\n", ret);
			अवरोध;
		पूर्ण

		अगर ((ret & ~SI1145_RSP_COUNTER_MASK) == 0) अणु
			अगर (ret == data->rsp_seq) अणु
				अगर (समय_after(jअगरfies, stop_jअगरfies)) अणु
					dev_warn(dev, "timeout on command %#02hhx\n",
						 cmd);
					ret = -ETIMEDOUT;
					अवरोध;
				पूर्ण
				msleep(SI1145_COMMAND_MINSLEEP_MS);
				जारी;
			पूर्ण
			अगर (ret == ((data->rsp_seq + 1) &
				SI1145_RSP_COUNTER_MASK)) अणु
				data->rsp_seq = ret;
				ret = 0;
				अवरोध;
			पूर्ण
			dev_warn(dev, "unexpected response counter %d instead of %d\n",
				 ret, (data->rsp_seq + 1) &
					SI1145_RSP_COUNTER_MASK);
			ret = -EIO;
		पूर्ण अन्यथा अणु
			अगर (ret == SI1145_RSP_INVALID_SETTING) अणु
				dev_warn(dev, "INVALID_SETTING error on command %#02hhx\n",
					 cmd);
				ret = -EINVAL;
			पूर्ण अन्यथा अणु
				/* All overflows are treated identically */
				dev_dbg(dev, "overflow, ret=%d, cmd=%#02hhx\n",
					ret, cmd);
				ret = -EOVERFLOW;
			पूर्ण
		पूर्ण

		/* Force a counter reset next समय */
		data->rsp_seq = -1;
		अवरोध;
	पूर्ण

out:
	mutex_unlock(&data->cmdlock);

	वापस ret;
पूर्ण

अटल पूर्णांक si1145_param_update(काष्ठा si1145_data *data, u8 op, u8 param,
			       u8 value)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
		SI1145_REG_PARAM_WR, value);
	अगर (ret < 0)
		वापस ret;

	वापस si1145_command(data, op | (param & 0x1F));
पूर्ण

अटल पूर्णांक si1145_param_set(काष्ठा si1145_data *data, u8 param, u8 value)
अणु
	वापस si1145_param_update(data, SI1145_CMD_PARAM_SET, param, value);
पूर्ण

/* Set param. Returns negative त्रुटि_सं or current value */
अटल पूर्णांक si1145_param_query(काष्ठा si1145_data *data, u8 param)
अणु
	पूर्णांक ret;

	ret = si1145_command(data, SI1145_CMD_PARAM_QUERY | (param & 0x1F));
	अगर (ret < 0)
		वापस ret;

	वापस i2c_smbus_पढ़ो_byte_data(data->client, SI1145_REG_PARAM_RD);
पूर्ण

/* Expand 8 bit compressed value to 16 bit, see Siद_असल AN498 */
अटल u16 si1145_uncompress(u8 x)
अणु
	u16 result = 0;
	u8 exponent = 0;

	अगर (x < 8)
		वापस 0;

	exponent = (x & 0xf0) >> 4;
	result = 0x10 | (x & 0x0f);

	अगर (exponent >= 4)
		वापस result << (exponent - 4);
	वापस result >> (4 - exponent);
पूर्ण

/* Compress 16 bit value to 8 bit, see Siद_असल AN498 */
अटल u8 si1145_compress(u16 x)
अणु
	u32 exponent = 0;
	u32 signअगरicand = 0;
	u32 पंचांगp = x;

	अगर (x == 0x0000)
		वापस 0x00;
	अगर (x == 0x0001)
		वापस 0x08;

	जबतक (1) अणु
		पंचांगp >>= 1;
		exponent += 1;
		अगर (पंचांगp == 1)
			अवरोध;
	पूर्ण

	अगर (exponent < 5) अणु
		signअगरicand = x << (4 - exponent);
		वापस (exponent << 4) | (signअगरicand & 0xF);
	पूर्ण

	signअगरicand = x >> (exponent - 5);
	अगर (signअगरicand & 1) अणु
		signअगरicand += 2;
		अगर (signअगरicand & 0x0040) अणु
			exponent += 1;
			signअगरicand >>= 1;
		पूर्ण
	पूर्ण

	वापस (exponent << 4) | ((signअगरicand >> 1) & 0xF);
पूर्ण

/* Write meas_rate in hardware */
अटल पूर्णांक si1145_set_meas_rate(काष्ठा si1145_data *data, पूर्णांक पूर्णांकerval)
अणु
	अगर (data->part_info->uncompressed_meas_rate)
		वापस i2c_smbus_ग_लिखो_word_data(data->client,
			SI1145_REG_MEAS_RATE, पूर्णांकerval);
	अन्यथा
		वापस i2c_smbus_ग_लिखो_byte_data(data->client,
			SI1145_REG_MEAS_RATE, पूर्णांकerval);
पूर्ण

अटल पूर्णांक si1145_पढ़ो_samp_freq(काष्ठा si1145_data *data, पूर्णांक *val, पूर्णांक *val2)
अणु
	*val = 32000;
	अगर (data->part_info->uncompressed_meas_rate)
		*val2 = data->meas_rate;
	अन्यथा
		*val2 = si1145_uncompress(data->meas_rate);
	वापस IIO_VAL_FRACTIONAL;
पूर्ण

/* Set the samp freq in driver निजी data */
अटल पूर्णांक si1145_store_samp_freq(काष्ठा si1145_data *data, पूर्णांक val)
अणु
	पूर्णांक ret = 0;
	पूर्णांक meas_rate;

	अगर (val <= 0 || val > 32000)
		वापस -दुस्फल;
	meas_rate = 32000 / val;

	mutex_lock(&data->lock);
	अगर (data->स्वतःnomous) अणु
		ret = si1145_set_meas_rate(data, meas_rate);
		अगर (ret)
			जाओ out;
	पूर्ण
	अगर (data->part_info->uncompressed_meas_rate)
		data->meas_rate = meas_rate;
	अन्यथा
		data->meas_rate = si1145_compress(meas_rate);

out:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल irqवापस_t si1145_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा si1145_data *data = iio_priv(indio_dev);
	पूर्णांक i, j = 0;
	पूर्णांक ret;
	u8 irq_status = 0;

	अगर (!data->स्वतःnomous) अणु
		ret = si1145_command(data, SI1145_CMD_PSALS_FORCE);
		अगर (ret < 0 && ret != -EOVERFLOW)
			जाओ करोne;
	पूर्ण अन्यथा अणु
		irq_status = ret = i2c_smbus_पढ़ो_byte_data(data->client,
				SI1145_REG_IRQ_STATUS);
		अगर (ret < 0)
			जाओ करोne;
		अगर (!(irq_status & SI1145_MASK_ALL_IE))
			जाओ करोne;
	पूर्ण

	क्रम_each_set_bit(i, indio_dev->active_scan_mask,
		indio_dev->masklength) अणु
		पूर्णांक run = 1;

		जबतक (i + run < indio_dev->masklength) अणु
			अगर (!test_bit(i + run, indio_dev->active_scan_mask))
				अवरोध;
			अगर (indio_dev->channels[i + run].address !=
				indio_dev->channels[i].address + 2 * run)
				अवरोध;
			run++;
		पूर्ण

		ret = i2c_smbus_पढ़ो_i2c_block_data_or_emulated(
				data->client, indio_dev->channels[i].address,
				माप(u16) * run, &data->buffer[j]);
		अगर (ret < 0)
			जाओ करोne;
		j += run * माप(u16);
		i += run - 1;
	पूर्ण

	अगर (data->स्वतःnomous) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(data->client,
				SI1145_REG_IRQ_STATUS,
				irq_status & SI1145_MASK_ALL_IE);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
		iio_get_समय_ns(indio_dev));

करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक si1145_set_chlist(काष्ठा iio_dev *indio_dev, अचिन्हित दीर्घ scan_mask)
अणु
	काष्ठा si1145_data *data = iio_priv(indio_dev);
	u8 reg = 0, mux;
	पूर्णांक ret;
	पूर्णांक i;

	/* channel list alपढ़ोy set, no need to reprogram */
	अगर (data->scan_mask == scan_mask)
		वापस 0;

	क्रम_each_set_bit(i, &scan_mask, indio_dev->masklength) अणु
		चयन (indio_dev->channels[i].address) अणु
		हाल SI1145_REG_ALSVIS_DATA:
			reg |= SI1145_CHLIST_EN_ALSVIS;
			अवरोध;
		हाल SI1145_REG_ALSIR_DATA:
			reg |= SI1145_CHLIST_EN_ALSIR;
			अवरोध;
		हाल SI1145_REG_PS1_DATA:
			reg |= SI1145_CHLIST_EN_PS1;
			अवरोध;
		हाल SI1145_REG_PS2_DATA:
			reg |= SI1145_CHLIST_EN_PS2;
			अवरोध;
		हाल SI1145_REG_PS3_DATA:
			reg |= SI1145_CHLIST_EN_PS3;
			अवरोध;
		हाल SI1145_REG_AUX_DATA:
			चयन (indio_dev->channels[i].type) अणु
			हाल IIO_UVINDEX:
				reg |= SI1145_CHLIST_EN_UV;
				अवरोध;
			शेष:
				reg |= SI1145_CHLIST_EN_AUX;
				अगर (indio_dev->channels[i].type == IIO_TEMP)
					mux = SI1145_MUX_TEMP;
				अन्यथा
					mux = SI1145_MUX_VDD;
				ret = si1145_param_set(data,
					SI1145_PARAM_AUX_ADC_MUX, mux);
				अगर (ret < 0)
					वापस ret;

				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	data->scan_mask = scan_mask;
	ret = si1145_param_set(data, SI1145_PARAM_CHLIST, reg);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक si1145_measure(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan)
अणु
	काष्ठा si1145_data *data = iio_priv(indio_dev);
	u8 cmd;
	पूर्णांक ret;

	ret = si1145_set_chlist(indio_dev, BIT(chan->scan_index));
	अगर (ret < 0)
		वापस ret;

	cmd = (chan->type == IIO_PROXIMITY) ? SI1145_CMD_PS_FORCE :
		SI1145_CMD_ALS_FORCE;
	ret = si1145_command(data, cmd);
	अगर (ret < 0 && ret != -EOVERFLOW)
		वापस ret;

	वापस i2c_smbus_पढ़ो_word_data(data->client, chan->address);
पूर्ण

/*
 * Conversion between iio scale and ADC_GAIN values
 * These could be further adjusted but proximity/पूर्णांकensity are dimensionless
 */
अटल स्थिर पूर्णांक si1145_proximity_scale_available[] = अणु
	128, 64, 32, 16, 8, 4पूर्ण;
अटल स्थिर पूर्णांक si1145_पूर्णांकensity_scale_available[] = अणु
	128, 64, 32, 16, 8, 4, 2, 1पूर्ण;
अटल IIO_CONST_ATTR(in_proximity_scale_available,
	"128 64 32 16 8 4");
अटल IIO_CONST_ATTR(in_पूर्णांकensity_scale_available,
	"128 64 32 16 8 4 2 1");
अटल IIO_CONST_ATTR(in_पूर्णांकensity_ir_scale_available,
	"128 64 32 16 8 4 2 1");

अटल पूर्णांक si1145_scale_from_adcgain(पूर्णांक regval)
अणु
	वापस 128 >> regval;
पूर्ण

अटल पूर्णांक si1145_proximity_adcgain_from_scale(पूर्णांक val, पूर्णांक val2)
अणु
	val = find_बंदst_descending(val, si1145_proximity_scale_available,
				ARRAY_SIZE(si1145_proximity_scale_available));
	अगर (val < 0 || val > 5 || val2 != 0)
		वापस -EINVAL;

	वापस val;
पूर्ण

अटल पूर्णांक si1145_पूर्णांकensity_adcgain_from_scale(पूर्णांक val, पूर्णांक val2)
अणु
	val = find_बंदst_descending(val, si1145_पूर्णांकensity_scale_available,
				ARRAY_SIZE(si1145_पूर्णांकensity_scale_available));
	अगर (val < 0 || val > 7 || val2 != 0)
		वापस -EINVAL;

	वापस val;
पूर्ण

अटल पूर्णांक si1145_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा si1145_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	u8 reg;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
		हाल IIO_PROXIMITY:
		हाल IIO_VOLTAGE:
		हाल IIO_TEMP:
		हाल IIO_UVINDEX:
			ret = iio_device_claim_direct_mode(indio_dev);
			अगर (ret)
				वापस ret;
			ret = si1145_measure(indio_dev, chan);
			iio_device_release_direct_mode(indio_dev);

			अगर (ret < 0)
				वापस ret;

			*val = ret;

			वापस IIO_VAL_INT;
		हाल IIO_CURRENT:
			ret = i2c_smbus_पढ़ो_byte_data(data->client,
				SI1145_PS_LED_REG(chan->channel));
			अगर (ret < 0)
				वापस ret;

			*val = (ret >> SI1145_PS_LED_SHIFT(chan->channel))
				& 0x0f;

			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_PROXIMITY:
			reg = SI1145_PARAM_PS_ADC_GAIN;
			अवरोध;
		हाल IIO_INTENSITY:
			अगर (chan->channel2 == IIO_MOD_LIGHT_IR)
				reg = SI1145_PARAM_ALSIR_ADC_GAIN;
			अन्यथा
				reg = SI1145_PARAM_ALSVIS_ADC_GAIN;
			अवरोध;
		हाल IIO_TEMP:
			*val = 28;
			*val2 = 571429;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_UVINDEX:
			*val = 0;
			*val2 = 10000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = si1145_param_query(data, reg);
		अगर (ret < 0)
			वापस ret;

		*val = si1145_scale_from_adcgain(ret & 0x07);

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_OFFSET:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			/*
			 * -ADC offset - ADC counts @ 25तओC -
			 *   35 * ADC counts / तओC
			 */
			*val = -256 - 11136 + 25 * 35;
			वापस IIO_VAL_INT;
		शेष:
			/*
			 * All ADC measurements have are by शेष offset
			 * by -256
			 * See AN498 5.6.3
			 */
			ret = si1145_param_query(data, SI1145_PARAM_ADC_OFFSET);
			अगर (ret < 0)
				वापस ret;
			*val = -si1145_uncompress(ret);
			वापस IIO_VAL_INT;
		पूर्ण
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस si1145_पढ़ो_samp_freq(data, val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक si1145_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा si1145_data *data = iio_priv(indio_dev);
	u8 reg1, reg2, shअगरt;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_PROXIMITY:
			val = si1145_proximity_adcgain_from_scale(val, val2);
			अगर (val < 0)
				वापस val;
			reg1 = SI1145_PARAM_PS_ADC_GAIN;
			reg2 = SI1145_PARAM_PS_ADC_COUNTER;
			अवरोध;
		हाल IIO_INTENSITY:
			val = si1145_पूर्णांकensity_adcgain_from_scale(val, val2);
			अगर (val < 0)
				वापस val;
			अगर (chan->channel2 == IIO_MOD_LIGHT_IR) अणु
				reg1 = SI1145_PARAM_ALSIR_ADC_GAIN;
				reg2 = SI1145_PARAM_ALSIR_ADC_COUNTER;
			पूर्ण अन्यथा अणु
				reg1 = SI1145_PARAM_ALSVIS_ADC_GAIN;
				reg2 = SI1145_PARAM_ALSVIS_ADC_COUNTER;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = si1145_param_set(data, reg1, val);
		अगर (ret < 0) अणु
			iio_device_release_direct_mode(indio_dev);
			वापस ret;
		पूर्ण
		/* Set recovery period to one's complement of gain */
		ret = si1145_param_set(data, reg2, (~val & 0x07) << 4);
		iio_device_release_direct_mode(indio_dev);
		वापस ret;
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->type != IIO_CURRENT)
			वापस -EINVAL;

		अगर (val < 0 || val > 15 || val2 != 0)
			वापस -EINVAL;

		reg1 = SI1145_PS_LED_REG(chan->channel);
		shअगरt = SI1145_PS_LED_SHIFT(chan->channel);

		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = i2c_smbus_पढ़ो_byte_data(data->client, reg1);
		अगर (ret < 0) अणु
			iio_device_release_direct_mode(indio_dev);
			वापस ret;
		पूर्ण
		ret = i2c_smbus_ग_लिखो_byte_data(data->client, reg1,
			(ret & ~(0x0f << shअगरt)) |
			((val & 0x0f) << shअगरt));
		iio_device_release_direct_mode(indio_dev);
		वापस ret;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस si1145_store_samp_freq(data, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#घोषणा SI1145_ST अणु \
	.sign = 'u', \
	.realbits = 16, \
	.storagebits = 16, \
	.endianness = IIO_LE, \
पूर्ण

#घोषणा SI1145_INTENSITY_CHANNEL(_si) अणु \
	.type = IIO_INTENSITY, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			      BIT(IIO_CHAN_INFO_OFFSET) | \
			      BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.scan_type = SI1145_ST, \
	.scan_index = _si, \
	.address = SI1145_REG_ALSVIS_DATA, \
पूर्ण

#घोषणा SI1145_INTENSITY_IR_CHANNEL(_si) अणु \
	.type = IIO_INTENSITY, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			      BIT(IIO_CHAN_INFO_OFFSET) | \
			      BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_LIGHT_IR, \
	.scan_type = SI1145_ST, \
	.scan_index = _si, \
	.address = SI1145_REG_ALSIR_DATA, \
पूर्ण

#घोषणा SI1145_TEMP_CHANNEL(_si) अणु \
	.type = IIO_TEMP, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			      BIT(IIO_CHAN_INFO_OFFSET) | \
			      BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.scan_type = SI1145_ST, \
	.scan_index = _si, \
	.address = SI1145_REG_AUX_DATA, \
पूर्ण

#घोषणा SI1145_UV_CHANNEL(_si) अणु \
	.type = IIO_UVINDEX, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			      BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.scan_type = SI1145_ST, \
	.scan_index = _si, \
	.address = SI1145_REG_AUX_DATA, \
पूर्ण

#घोषणा SI1145_PROXIMITY_CHANNEL(_si, _ch) अणु \
	.type = IIO_PROXIMITY, \
	.indexed = 1, \
	.channel = _ch, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) | \
				    BIT(IIO_CHAN_INFO_OFFSET), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.scan_type = SI1145_ST, \
	.scan_index = _si, \
	.address = SI1145_REG_PS1_DATA + _ch * 2, \
पूर्ण

#घोषणा SI1145_VOLTAGE_CHANNEL(_si) अणु \
	.type = IIO_VOLTAGE, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.scan_type = SI1145_ST, \
	.scan_index = _si, \
	.address = SI1145_REG_AUX_DATA, \
पूर्ण

#घोषणा SI1145_CURRENT_CHANNEL(_ch) अणु \
	.type = IIO_CURRENT, \
	.indexed = 1, \
	.channel = _ch, \
	.output = 1, \
	.scan_index = -1, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec si1132_channels[] = अणु
	SI1145_INTENSITY_CHANNEL(0),
	SI1145_INTENSITY_IR_CHANNEL(1),
	SI1145_TEMP_CHANNEL(2),
	SI1145_VOLTAGE_CHANNEL(3),
	SI1145_UV_CHANNEL(4),
	IIO_CHAN_SOFT_TIMESTAMP(6),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec si1141_channels[] = अणु
	SI1145_INTENSITY_CHANNEL(0),
	SI1145_INTENSITY_IR_CHANNEL(1),
	SI1145_PROXIMITY_CHANNEL(2, 0),
	SI1145_TEMP_CHANNEL(3),
	SI1145_VOLTAGE_CHANNEL(4),
	IIO_CHAN_SOFT_TIMESTAMP(5),
	SI1145_CURRENT_CHANNEL(0),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec si1142_channels[] = अणु
	SI1145_INTENSITY_CHANNEL(0),
	SI1145_INTENSITY_IR_CHANNEL(1),
	SI1145_PROXIMITY_CHANNEL(2, 0),
	SI1145_PROXIMITY_CHANNEL(3, 1),
	SI1145_TEMP_CHANNEL(4),
	SI1145_VOLTAGE_CHANNEL(5),
	IIO_CHAN_SOFT_TIMESTAMP(6),
	SI1145_CURRENT_CHANNEL(0),
	SI1145_CURRENT_CHANNEL(1),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec si1143_channels[] = अणु
	SI1145_INTENSITY_CHANNEL(0),
	SI1145_INTENSITY_IR_CHANNEL(1),
	SI1145_PROXIMITY_CHANNEL(2, 0),
	SI1145_PROXIMITY_CHANNEL(3, 1),
	SI1145_PROXIMITY_CHANNEL(4, 2),
	SI1145_TEMP_CHANNEL(5),
	SI1145_VOLTAGE_CHANNEL(6),
	IIO_CHAN_SOFT_TIMESTAMP(7),
	SI1145_CURRENT_CHANNEL(0),
	SI1145_CURRENT_CHANNEL(1),
	SI1145_CURRENT_CHANNEL(2),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec si1145_channels[] = अणु
	SI1145_INTENSITY_CHANNEL(0),
	SI1145_INTENSITY_IR_CHANNEL(1),
	SI1145_PROXIMITY_CHANNEL(2, 0),
	SI1145_TEMP_CHANNEL(3),
	SI1145_VOLTAGE_CHANNEL(4),
	SI1145_UV_CHANNEL(5),
	IIO_CHAN_SOFT_TIMESTAMP(6),
	SI1145_CURRENT_CHANNEL(0),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec si1146_channels[] = अणु
	SI1145_INTENSITY_CHANNEL(0),
	SI1145_INTENSITY_IR_CHANNEL(1),
	SI1145_TEMP_CHANNEL(2),
	SI1145_VOLTAGE_CHANNEL(3),
	SI1145_UV_CHANNEL(4),
	SI1145_PROXIMITY_CHANNEL(5, 0),
	SI1145_PROXIMITY_CHANNEL(6, 1),
	IIO_CHAN_SOFT_TIMESTAMP(7),
	SI1145_CURRENT_CHANNEL(0),
	SI1145_CURRENT_CHANNEL(1),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec si1147_channels[] = अणु
	SI1145_INTENSITY_CHANNEL(0),
	SI1145_INTENSITY_IR_CHANNEL(1),
	SI1145_PROXIMITY_CHANNEL(2, 0),
	SI1145_PROXIMITY_CHANNEL(3, 1),
	SI1145_PROXIMITY_CHANNEL(4, 2),
	SI1145_TEMP_CHANNEL(5),
	SI1145_VOLTAGE_CHANNEL(6),
	SI1145_UV_CHANNEL(7),
	IIO_CHAN_SOFT_TIMESTAMP(8),
	SI1145_CURRENT_CHANNEL(0),
	SI1145_CURRENT_CHANNEL(1),
	SI1145_CURRENT_CHANNEL(2),
पूर्ण;

अटल काष्ठा attribute *si1132_attributes[] = अणु
	&iio_स्थिर_attr_in_पूर्णांकensity_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_in_पूर्णांकensity_ir_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *si114x_attributes[] = अणु
	&iio_स्थिर_attr_in_पूर्णांकensity_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_in_पूर्णांकensity_ir_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_in_proximity_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group si1132_attribute_group = अणु
	.attrs = si1132_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group si114x_attribute_group = अणु
	.attrs = si114x_attributes,
पूर्ण;


अटल स्थिर काष्ठा iio_info si1132_info = अणु
	.पढ़ो_raw = si1145_पढ़ो_raw,
	.ग_लिखो_raw = si1145_ग_लिखो_raw,
	.attrs = &si1132_attribute_group,
पूर्ण;

अटल स्थिर काष्ठा iio_info si114x_info = अणु
	.पढ़ो_raw = si1145_पढ़ो_raw,
	.ग_लिखो_raw = si1145_ग_लिखो_raw,
	.attrs = &si114x_attribute_group,
पूर्ण;

#घोषणा SI1145_PART(id, iio_info, chans, leds, uncompressed_meas_rate) \
	अणुid, iio_info, chans, ARRAY_SIZE(chans), leds, uncompressed_meas_rateपूर्ण

अटल स्थिर काष्ठा si1145_part_info si1145_part_info[] = अणु
	[SI1132] = SI1145_PART(0x32, &si1132_info, si1132_channels, 0, true),
	[SI1141] = SI1145_PART(0x41, &si114x_info, si1141_channels, 1, false),
	[SI1142] = SI1145_PART(0x42, &si114x_info, si1142_channels, 2, false),
	[SI1143] = SI1145_PART(0x43, &si114x_info, si1143_channels, 3, false),
	[SI1145] = SI1145_PART(0x45, &si114x_info, si1145_channels, 1, true),
	[SI1146] = SI1145_PART(0x46, &si114x_info, si1146_channels, 2, true),
	[SI1147] = SI1145_PART(0x47, &si114x_info, si1147_channels, 3, true),
पूर्ण;

अटल पूर्णांक si1145_initialize(काष्ठा si1145_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, SI1145_REG_COMMAND,
					SI1145_CMD_RESET);
	अगर (ret < 0)
		वापस ret;
	msleep(SI1145_COMMAND_TIMEOUT_MS);

	/* Hardware key, magic value */
	ret = i2c_smbus_ग_लिखो_byte_data(client, SI1145_REG_HW_KEY, 0x17);
	अगर (ret < 0)
		वापस ret;
	msleep(SI1145_COMMAND_TIMEOUT_MS);

	/* Turn off स्वतःnomous mode */
	ret = si1145_set_meas_rate(data, 0);
	अगर (ret < 0)
		वापस ret;

	/* Initialize sampling freq to 10 Hz */
	ret = si1145_store_samp_freq(data, 10);
	अगर (ret < 0)
		वापस ret;

	/* Set LED currents to 45 mA; have 4 bits, see Table 2 in datasheet */
	चयन (data->part_info->num_leds) अणु
	हाल 3:
		ret = i2c_smbus_ग_लिखो_byte_data(client,
						SI1145_REG_PS_LED3,
						SI1145_LED_CURRENT_45mA);
		अगर (ret < 0)
			वापस ret;
		fallthrough;
	हाल 2:
		ret = i2c_smbus_ग_लिखो_byte_data(client,
						SI1145_REG_PS_LED21,
						(SI1145_LED_CURRENT_45mA << 4) |
						SI1145_LED_CURRENT_45mA);
		अवरोध;
	हाल 1:
		ret = i2c_smbus_ग_लिखो_byte_data(client,
						SI1145_REG_PS_LED21,
						SI1145_LED_CURRENT_45mA);
		अवरोध;
	शेष:
		ret = 0;
		अवरोध;
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	/* Set normal proximity measurement mode */
	ret = si1145_param_set(data, SI1145_PARAM_PS_ADC_MISC,
			       SI1145_PS_ADC_MODE_NORMAL);
	अगर (ret < 0)
		वापस ret;

	ret = si1145_param_set(data, SI1145_PARAM_PS_ADC_GAIN, 0x01);
	अगर (ret < 0)
		वापस ret;

	/* ADC_COUNTER should be one complement of ADC_GAIN */
	ret = si1145_param_set(data, SI1145_PARAM_PS_ADC_COUNTER, 0x06 << 4);
	अगर (ret < 0)
		वापस ret;

	/* Set ALS visible measurement mode */
	ret = si1145_param_set(data, SI1145_PARAM_ALSVIS_ADC_MISC,
			       SI1145_ADC_MISC_RANGE);
	अगर (ret < 0)
		वापस ret;

	ret = si1145_param_set(data, SI1145_PARAM_ALSVIS_ADC_GAIN, 0x03);
	अगर (ret < 0)
		वापस ret;

	ret = si1145_param_set(data, SI1145_PARAM_ALSVIS_ADC_COUNTER,
			       0x04 << 4);
	अगर (ret < 0)
		वापस ret;

	/* Set ALS IR measurement mode */
	ret = si1145_param_set(data, SI1145_PARAM_ALSIR_ADC_MISC,
			       SI1145_ADC_MISC_RANGE);
	अगर (ret < 0)
		वापस ret;

	ret = si1145_param_set(data, SI1145_PARAM_ALSIR_ADC_GAIN, 0x01);
	अगर (ret < 0)
		वापस ret;

	ret = si1145_param_set(data, SI1145_PARAM_ALSIR_ADC_COUNTER,
			       0x06 << 4);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Initialize UCOEF to शेष values in datasheet
	 * These रेजिस्टरs are normally zero on reset
	 */
	अगर (data->part_info == &si1145_part_info[SI1132] ||
		data->part_info == &si1145_part_info[SI1145] ||
		data->part_info == &si1145_part_info[SI1146] ||
		data->part_info == &si1145_part_info[SI1147]) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(data->client,
						SI1145_REG_UCOEF1,
						SI1145_UCOEF1_DEFAULT);
		अगर (ret < 0)
			वापस ret;
		ret = i2c_smbus_ग_लिखो_byte_data(data->client,
				SI1145_REG_UCOEF2, SI1145_UCOEF2_DEFAULT);
		अगर (ret < 0)
			वापस ret;
		ret = i2c_smbus_ग_लिखो_byte_data(data->client,
				SI1145_REG_UCOEF3, SI1145_UCOEF3_DEFAULT);
		अगर (ret < 0)
			वापस ret;
		ret = i2c_smbus_ग_लिखो_byte_data(data->client,
				SI1145_REG_UCOEF4, SI1145_UCOEF4_DEFAULT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Program the channels we want to measure with CMD_PSALS_AUTO. No need क्रम
 * _postdisable as we stop with CMD_PSALS_PAUSE; single measurement (direct)
 * mode reprograms the channels list anyway...
 */
अटल पूर्णांक si1145_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा si1145_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = si1145_set_chlist(indio_dev, *indio_dev->active_scan_mask);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल bool si1145_validate_scan_mask(काष्ठा iio_dev *indio_dev,
			       स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा si1145_data *data = iio_priv(indio_dev);
	अचिन्हित पूर्णांक count = 0;
	पूर्णांक i;

	/* Check that at most one AUX channel is enabled */
	क्रम_each_set_bit(i, scan_mask, data->part_info->num_channels) अणु
		अगर (indio_dev->channels[i].address == SI1145_REG_AUX_DATA)
			count++;
	पूर्ण

	वापस count <= 1;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops si1145_buffer_setup_ops = अणु
	.preenable = si1145_buffer_preenable,
	.validate_scan_mask = si1145_validate_scan_mask,
पूर्ण;

/*
 * si1145_trigger_set_state() - Set trigger state
 *
 * When not using triggers पूर्णांकerrupts are disabled and measurement rate is
 * set to zero in order to minimize घातer consumption.
 */
अटल पूर्णांक si1145_trigger_set_state(काष्ठा iio_trigger *trig, bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा si1145_data *data = iio_priv(indio_dev);
	पूर्णांक err = 0, ret;

	mutex_lock(&data->lock);

	अगर (state) अणु
		data->स्वतःnomous = true;
		err = i2c_smbus_ग_लिखो_byte_data(data->client,
				SI1145_REG_INT_CFG, SI1145_INT_CFG_OE);
		अगर (err < 0)
			जाओ disable;
		err = i2c_smbus_ग_लिखो_byte_data(data->client,
				SI1145_REG_IRQ_ENABLE, SI1145_MASK_ALL_IE);
		अगर (err < 0)
			जाओ disable;
		err = si1145_set_meas_rate(data, data->meas_rate);
		अगर (err < 0)
			जाओ disable;
		err = si1145_command(data, SI1145_CMD_PSALS_AUTO);
		अगर (err < 0)
			जाओ disable;
	पूर्ण अन्यथा अणु
disable:
		/* Disable as much as possible skipping errors */
		ret = si1145_command(data, SI1145_CMD_PSALS_PAUSE);
		अगर (ret < 0 && !err)
			err = ret;
		ret = si1145_set_meas_rate(data, 0);
		अगर (ret < 0 && !err)
			err = ret;
		ret = i2c_smbus_ग_लिखो_byte_data(data->client,
						SI1145_REG_IRQ_ENABLE, 0);
		अगर (ret < 0 && !err)
			err = ret;
		ret = i2c_smbus_ग_लिखो_byte_data(data->client,
						SI1145_REG_INT_CFG, 0);
		अगर (ret < 0 && !err)
			err = ret;
		data->स्वतःnomous = false;
	पूर्ण

	mutex_unlock(&data->lock);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops si1145_trigger_ops = अणु
	.set_trigger_state = si1145_trigger_set_state,
पूर्ण;

अटल पूर्णांक si1145_probe_trigger(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा si1145_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा iio_trigger *trig;
	पूर्णांक ret;

	trig = devm_iio_trigger_alloc(&client->dev,
			"%s-dev%d", indio_dev->name, indio_dev->id);
	अगर (!trig)
		वापस -ENOMEM;

	trig->ops = &si1145_trigger_ops;
	iio_trigger_set_drvdata(trig, indio_dev);

	ret = devm_request_irq(&client->dev, client->irq,
			  iio_trigger_generic_data_rdy_poll,
			  IRQF_TRIGGER_FALLING,
			  "si1145_irq",
			  trig);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "irq request failed\n");
		वापस ret;
	पूर्ण

	ret = devm_iio_trigger_रेजिस्टर(&client->dev, trig);
	अगर (ret)
		वापस ret;

	data->trig = trig;
	indio_dev->trig = iio_trigger_get(data->trig);

	वापस 0;
पूर्ण

अटल पूर्णांक si1145_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा si1145_data *data;
	काष्ठा iio_dev *indio_dev;
	u8 part_id, rev_id, seq_id;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->part_info = &si1145_part_info[id->driver_data];

	part_id = ret = i2c_smbus_पढ़ो_byte_data(data->client,
						 SI1145_REG_PART_ID);
	अगर (ret < 0)
		वापस ret;
	rev_id = ret = i2c_smbus_पढ़ो_byte_data(data->client,
						SI1145_REG_REV_ID);
	अगर (ret < 0)
		वापस ret;
	seq_id = ret = i2c_smbus_पढ़ो_byte_data(data->client,
						SI1145_REG_SEQ_ID);
	अगर (ret < 0)
		वापस ret;
	dev_info(&client->dev, "device ID part %#02hhx rev %#02hhx seq %#02hhx\n",
			part_id, rev_id, seq_id);
	अगर (part_id != data->part_info->part) अणु
		dev_err(&client->dev, "part ID mismatch got %#02hhx, expected %#02x\n",
				part_id, data->part_info->part);
		वापस -ENODEV;
	पूर्ण

	indio_dev->name = id->name;
	indio_dev->channels = data->part_info->channels;
	indio_dev->num_channels = data->part_info->num_channels;
	indio_dev->info = data->part_info->iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	mutex_init(&data->lock);
	mutex_init(&data->cmdlock);

	ret = si1145_initialize(data);
	अगर (ret < 0)
		वापस ret;

	ret = devm_iio_triggered_buffer_setup(&client->dev,
		indio_dev, शून्य,
		si1145_trigger_handler, &si1145_buffer_setup_ops);
	अगर (ret < 0)
		वापस ret;

	अगर (client->irq) अणु
		ret = si1145_probe_trigger(indio_dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		dev_info(&client->dev, "no irq, using polling\n");
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id si1145_ids[] = अणु
	अणु "si1132", SI1132 पूर्ण,
	अणु "si1141", SI1141 पूर्ण,
	अणु "si1142", SI1142 पूर्ण,
	अणु "si1143", SI1143 पूर्ण,
	अणु "si1145", SI1145 पूर्ण,
	अणु "si1146", SI1146 पूर्ण,
	अणु "si1147", SI1147 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, si1145_ids);

अटल काष्ठा i2c_driver si1145_driver = अणु
	.driver = अणु
		.name   = "si1145",
	पूर्ण,
	.probe  = si1145_probe,
	.id_table = si1145_ids,
पूर्ण;

module_i2c_driver(si1145_driver);

MODULE_AUTHOR("Peter Meerwald-Stadler <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("Silabs SI1132 and SI1141/2/3/5/6/7 proximity, ambient light and UV index sensor driver");
MODULE_LICENSE("GPL");
