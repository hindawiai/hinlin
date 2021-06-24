<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments ADS131E0x 4-, 6- and 8-Channel ADCs
 *
 * Copyright (c) 2020 AVL DiTEST GmbH
 *   Tomislav Denis <tomislav.denis@avl.com>
 *
 * Datasheet: https://www.ti.com/lit/ds/symlink/ads131e08.pdf
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश <यंत्र/unaligned.h>

/* Commands */
#घोषणा ADS131E08_CMD_RESET		0x06
#घोषणा ADS131E08_CMD_START		0x08
#घोषणा ADS131E08_CMD_STOP		0x0A
#घोषणा ADS131E08_CMD_OFFSETCAL		0x1A
#घोषणा ADS131E08_CMD_SDATAC		0x11
#घोषणा ADS131E08_CMD_RDATA		0x12
#घोषणा ADS131E08_CMD_RREG(r)		(BIT(5) | (r & GENMASK(4, 0)))
#घोषणा ADS131E08_CMD_WREG(r)		(BIT(6) | (r & GENMASK(4, 0)))

/* Registers */
#घोषणा ADS131E08_ADR_CFG1R		0x01
#घोषणा ADS131E08_ADR_CFG3R		0x03
#घोषणा ADS131E08_ADR_CH0R		0x05

/* Configuration रेजिस्टर 1 */
#घोषणा ADS131E08_CFG1R_DR_MASK		GENMASK(2, 0)

/* Configuration रेजिस्टर 3 */
#घोषणा ADS131E08_CFG3R_PDB_REFBUF_MASK	BIT(7)
#घोषणा ADS131E08_CFG3R_VREF_4V_MASK	BIT(5)

/* Channel settings रेजिस्टर */
#घोषणा ADS131E08_CHR_GAIN_MASK		GENMASK(6, 4)
#घोषणा ADS131E08_CHR_MUX_MASK		GENMASK(2, 0)
#घोषणा ADS131E08_CHR_PWD_MASK		BIT(7)

/* ADC  misc */
#घोषणा ADS131E08_DEFAULT_DATA_RATE	1
#घोषणा ADS131E08_DEFAULT_PGA_GAIN	1
#घोषणा ADS131E08_DEFAULT_MUX		0

#घोषणा ADS131E08_VREF_2V4_mV		2400
#घोषणा ADS131E08_VREF_4V_mV		4000

#घोषणा ADS131E08_WAIT_RESET_CYCLES	18
#घोषणा ADS131E08_WAIT_SDECODE_CYCLES	4
#घोषणा ADS131E08_WAIT_OFFSETCAL_MS	153
#घोषणा ADS131E08_MAX_SETTLING_TIME_MS	6

#घोषणा ADS131E08_NUM_STATUS_BYTES	3
#घोषणा ADS131E08_NUM_DATA_BYTES_MAX	24
#घोषणा ADS131E08_NUM_DATA_BYTES(dr)	(((dr) >= 32) ? 2 : 3)
#घोषणा ADS131E08_NUM_DATA_BITS(dr)	(ADS131E08_NUM_DATA_BYTES(dr) * 8)
#घोषणा ADS131E08_NUM_STORAGE_BYTES	4

क्रमागत ads131e08_ids अणु
	ads131e04,
	ads131e06,
	ads131e08,
पूर्ण;

काष्ठा ads131e08_info अणु
	अचिन्हित पूर्णांक max_channels;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा ads131e08_channel_config अणु
	अचिन्हित पूर्णांक pga_gain;
	अचिन्हित पूर्णांक mux;
पूर्ण;

काष्ठा ads131e08_state अणु
	स्थिर काष्ठा ads131e08_info *info;
	काष्ठा spi_device *spi;
	काष्ठा iio_trigger *trig;
	काष्ठा clk *adc_clk;
	काष्ठा regulator *vref_reg;
	काष्ठा ads131e08_channel_config *channel_config;
	अचिन्हित पूर्णांक data_rate;
	अचिन्हित पूर्णांक vref_mv;
	अचिन्हित पूर्णांक sdecode_delay_us;
	अचिन्हित पूर्णांक reset_delay_us;
	अचिन्हित पूर्णांक पढ़ोback_len;
	काष्ठा completion completion;
	काष्ठा अणु
		u8 data[ADS131E08_NUM_DATA_BYTES_MAX];
		s64 ts __aligned(8);
	पूर्ण पंचांगp_buf;

	u8 tx_buf[3] ____cacheline_aligned;
	/*
	 * Add extra one padding byte to be able to access the last channel
	 * value using u32 poपूर्णांकer
	 */
	u8 rx_buf[ADS131E08_NUM_STATUS_BYTES +
		ADS131E08_NUM_DATA_BYTES_MAX + 1];
पूर्ण;

अटल स्थिर काष्ठा ads131e08_info ads131e08_info_tbl[] = अणु
	[ads131e04] = अणु
		.max_channels = 4,
		.name = "ads131e04",
	पूर्ण,
	[ads131e06] = अणु
		.max_channels = 6,
		.name = "ads131e06",
	पूर्ण,
	[ads131e08] = अणु
		.max_channels = 8,
		.name = "ads131e08",
	पूर्ण,
पूर्ण;

काष्ठा ads131e08_data_rate_desc अणु
	अचिन्हित पूर्णांक rate;  /* data rate in kSPS */
	u8 reg;             /* reg value */
पूर्ण;

अटल स्थिर काष्ठा ads131e08_data_rate_desc ads131e08_data_rate_tbl[] = अणु
	अणु .rate = 64,   .reg = 0x00 पूर्ण,
	अणु .rate = 32,   .reg = 0x01 पूर्ण,
	अणु .rate = 16,   .reg = 0x02 पूर्ण,
	अणु .rate = 8,    .reg = 0x03 पूर्ण,
	अणु .rate = 4,    .reg = 0x04 पूर्ण,
	अणु .rate = 2,    .reg = 0x05 पूर्ण,
	अणु .rate = 1,    .reg = 0x06 पूर्ण,
पूर्ण;

काष्ठा ads131e08_pga_gain_desc अणु
	अचिन्हित पूर्णांक gain;  /* PGA gain value */
	u8 reg;             /* field value */
पूर्ण;

अटल स्थिर काष्ठा ads131e08_pga_gain_desc ads131e08_pga_gain_tbl[] = अणु
	अणु .gain = 1,   .reg = 0x01 पूर्ण,
	अणु .gain = 2,   .reg = 0x02 पूर्ण,
	अणु .gain = 4,   .reg = 0x04 पूर्ण,
	अणु .gain = 8,   .reg = 0x05 पूर्ण,
	अणु .gain = 12,  .reg = 0x06 पूर्ण,
पूर्ण;

अटल स्थिर u8 ads131e08_valid_channel_mux_values[] = अणु 0, 1, 3, 4 पूर्ण;

अटल पूर्णांक ads131e08_exec_cmd(काष्ठा ads131e08_state *st, u8 cmd)
अणु
	पूर्णांक ret;

	ret = spi_ग_लिखो_then_पढ़ो(st->spi, &cmd, 1, शून्य, 0);
	अगर (ret)
		dev_err(&st->spi->dev, "Exec cmd(%02x) failed\n", cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक ads131e08_पढ़ो_reg(काष्ठा ads131e08_state *st, u8 reg)
अणु
	पूर्णांक ret;
	काष्ठा spi_transfer transfer[] = अणु
		अणु
			.tx_buf = &st->tx_buf,
			.len = 2,
			.delay = अणु
				.value = st->sdecode_delay_us,
				.unit = SPI_DELAY_UNIT_USECS,
			पूर्ण,
		पूर्ण, अणु
			.rx_buf = &st->rx_buf,
			.len = 1,
		पूर्ण,
	पूर्ण;

	st->tx_buf[0] = ADS131E08_CMD_RREG(reg);
	st->tx_buf[1] = 0;

	ret = spi_sync_transfer(st->spi, transfer, ARRAY_SIZE(transfer));
	अगर (ret) अणु
		dev_err(&st->spi->dev, "Read register failed\n");
		वापस ret;
	पूर्ण

	वापस st->rx_buf[0];
पूर्ण

अटल पूर्णांक ads131e08_ग_लिखो_reg(काष्ठा ads131e08_state *st, u8 reg, u8 value)
अणु
	पूर्णांक ret;
	काष्ठा spi_transfer transfer[] = अणु
		अणु
			.tx_buf = &st->tx_buf,
			.len = 3,
			.delay = अणु
				.value = st->sdecode_delay_us,
				.unit = SPI_DELAY_UNIT_USECS,
			पूर्ण,
		पूर्ण
	पूर्ण;

	st->tx_buf[0] = ADS131E08_CMD_WREG(reg);
	st->tx_buf[1] = 0;
	st->tx_buf[2] = value;

	ret = spi_sync_transfer(st->spi, transfer, ARRAY_SIZE(transfer));
	अगर (ret)
		dev_err(&st->spi->dev, "Write register failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक ads131e08_पढ़ो_data(काष्ठा ads131e08_state *st, पूर्णांक rx_len)
अणु
	पूर्णांक ret;
	काष्ठा spi_transfer transfer[] = अणु
		अणु
			.tx_buf = &st->tx_buf,
			.len = 1,
		पूर्ण, अणु
			.rx_buf = &st->rx_buf,
			.len = rx_len,
		पूर्ण,
	पूर्ण;

	st->tx_buf[0] = ADS131E08_CMD_RDATA;

	ret = spi_sync_transfer(st->spi, transfer, ARRAY_SIZE(transfer));
	अगर (ret)
		dev_err(&st->spi->dev, "Read data failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक ads131e08_set_data_rate(काष्ठा ads131e08_state *st, पूर्णांक data_rate)
अणु
	पूर्णांक i, reg, ret;

	क्रम (i = 0; i < ARRAY_SIZE(ads131e08_data_rate_tbl); i++) अणु
		अगर (ads131e08_data_rate_tbl[i].rate == data_rate)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(ads131e08_data_rate_tbl)) अणु
		dev_err(&st->spi->dev, "invalid data rate value\n");
		वापस -EINVAL;
	पूर्ण

	reg = ads131e08_पढ़ो_reg(st, ADS131E08_ADR_CFG1R);
	अगर (reg < 0)
		वापस reg;

	reg &= ~ADS131E08_CFG1R_DR_MASK;
	reg |= FIELD_PREP(ADS131E08_CFG1R_DR_MASK,
		ads131e08_data_rate_tbl[i].reg);

	ret = ads131e08_ग_लिखो_reg(st, ADS131E08_ADR_CFG1R, reg);
	अगर (ret)
		वापस ret;

	st->data_rate = data_rate;
	st->पढ़ोback_len = ADS131E08_NUM_STATUS_BYTES +
		ADS131E08_NUM_DATA_BYTES(st->data_rate) *
		st->info->max_channels;

	वापस 0;
पूर्ण

अटल पूर्णांक ads131e08_pga_gain_to_field_value(काष्ठा ads131e08_state *st,
	अचिन्हित पूर्णांक pga_gain)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ads131e08_pga_gain_tbl); i++) अणु
		अगर (ads131e08_pga_gain_tbl[i].gain == pga_gain)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(ads131e08_pga_gain_tbl)) अणु
		dev_err(&st->spi->dev, "invalid PGA gain value\n");
		वापस -EINVAL;
	पूर्ण

	वापस ads131e08_pga_gain_tbl[i].reg;
पूर्ण

अटल पूर्णांक ads131e08_set_pga_gain(काष्ठा ads131e08_state *st,
	अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक pga_gain)
अणु
	पूर्णांक field_value, reg;

	field_value = ads131e08_pga_gain_to_field_value(st, pga_gain);
	अगर (field_value < 0)
		वापस field_value;

	reg = ads131e08_पढ़ो_reg(st, ADS131E08_ADR_CH0R + channel);
	अगर (reg < 0)
		वापस reg;

	reg &= ~ADS131E08_CHR_GAIN_MASK;
	reg |= FIELD_PREP(ADS131E08_CHR_GAIN_MASK, field_value);

	वापस ads131e08_ग_लिखो_reg(st, ADS131E08_ADR_CH0R + channel, reg);
पूर्ण

अटल पूर्णांक ads131e08_validate_channel_mux(काष्ठा ads131e08_state *st,
	अचिन्हित पूर्णांक mux)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ads131e08_valid_channel_mux_values); i++) अणु
		अगर (ads131e08_valid_channel_mux_values[i] == mux)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(ads131e08_valid_channel_mux_values)) अणु
		dev_err(&st->spi->dev, "invalid channel mux value\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ads131e08_set_channel_mux(काष्ठा ads131e08_state *st,
	अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक mux)
अणु
	पूर्णांक reg;

	reg = ads131e08_पढ़ो_reg(st, ADS131E08_ADR_CH0R + channel);
	अगर (reg < 0)
		वापस reg;

	reg &= ~ADS131E08_CHR_MUX_MASK;
	reg |= FIELD_PREP(ADS131E08_CHR_MUX_MASK, mux);

	वापस ads131e08_ग_लिखो_reg(st, ADS131E08_ADR_CH0R + channel, reg);
पूर्ण

अटल पूर्णांक ads131e08_घातer_करोwn_channel(काष्ठा ads131e08_state *st,
	अचिन्हित पूर्णांक channel, bool value)
अणु
	पूर्णांक reg;

	reg = ads131e08_पढ़ो_reg(st, ADS131E08_ADR_CH0R + channel);
	अगर (reg < 0)
		वापस reg;

	reg &= ~ADS131E08_CHR_PWD_MASK;
	reg |= FIELD_PREP(ADS131E08_CHR_PWD_MASK, value);

	वापस ads131e08_ग_लिखो_reg(st, ADS131E08_ADR_CH0R + channel, reg);
पूर्ण

अटल पूर्णांक ads131e08_config_reference_voltage(काष्ठा ads131e08_state *st)
अणु
	पूर्णांक reg;

	reg = ads131e08_पढ़ो_reg(st, ADS131E08_ADR_CFG3R);
	अगर (reg < 0)
		वापस reg;

	reg &= ~ADS131E08_CFG3R_PDB_REFBUF_MASK;
	अगर (!st->vref_reg) अणु
		reg |= FIELD_PREP(ADS131E08_CFG3R_PDB_REFBUF_MASK, 1);
		reg &= ~ADS131E08_CFG3R_VREF_4V_MASK;
		reg |= FIELD_PREP(ADS131E08_CFG3R_VREF_4V_MASK,
			st->vref_mv == ADS131E08_VREF_4V_mV);
	पूर्ण

	वापस ads131e08_ग_लिखो_reg(st, ADS131E08_ADR_CFG3R, reg);
पूर्ण

अटल पूर्णांक ads131e08_initial_config(काष्ठा iio_dev *indio_dev)
अणु
	स्थिर काष्ठा iio_chan_spec *channel = indio_dev->channels;
	काष्ठा ads131e08_state *st = iio_priv(indio_dev);
	अचिन्हित दीर्घ active_channels = 0;
	पूर्णांक ret, i;

	ret = ads131e08_exec_cmd(st, ADS131E08_CMD_RESET);
	अगर (ret)
		वापस ret;

	udelay(st->reset_delay_us);

	/* Disable पढ़ो data in continuous mode (enabled by शेष) */
	ret = ads131e08_exec_cmd(st, ADS131E08_CMD_SDATAC);
	अगर (ret)
		वापस ret;

	ret = ads131e08_set_data_rate(st, ADS131E08_DEFAULT_DATA_RATE);
	अगर (ret)
		वापस ret;

	ret = ads131e08_config_reference_voltage(st);
	अगर (ret)
		वापस ret;

	क्रम (i = 0;  i < indio_dev->num_channels; i++) अणु
		ret = ads131e08_set_pga_gain(st, channel->channel,
			st->channel_config[i].pga_gain);
		अगर (ret)
			वापस ret;

		ret = ads131e08_set_channel_mux(st, channel->channel,
			st->channel_config[i].mux);
		अगर (ret)
			वापस ret;

		active_channels |= BIT(channel->channel);
		channel++;
	पूर्ण

	/* Power करोwn unused channels */
	क्रम_each_clear_bit(i, &active_channels, st->info->max_channels) अणु
		ret = ads131e08_घातer_करोwn_channel(st, i, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Request channel offset calibration */
	ret = ads131e08_exec_cmd(st, ADS131E08_CMD_OFFSETCAL);
	अगर (ret)
		वापस ret;

	/*
	 * Channel offset calibration is triggered with the first START
	 * command. Since calibration takes more समय than settling operation,
	 * this causes समयout error when command START is sent first
	 * समय (e.g. first call of the ads131e08_पढ़ो_direct method).
	 * To aव्योम this problem offset calibration is triggered here.
	 */
	ret = ads131e08_exec_cmd(st, ADS131E08_CMD_START);
	अगर (ret)
		वापस ret;

	msleep(ADS131E08_WAIT_OFFSETCAL_MS);

	वापस ads131e08_exec_cmd(st, ADS131E08_CMD_STOP);
पूर्ण

अटल पूर्णांक ads131e08_pool_data(काष्ठा ads131e08_state *st)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	reinit_completion(&st->completion);

	ret = ads131e08_exec_cmd(st, ADS131E08_CMD_START);
	अगर (ret)
		वापस ret;

	समयout = msecs_to_jअगरfies(ADS131E08_MAX_SETTLING_TIME_MS);
	ret = रुको_क्रम_completion_समयout(&st->completion, समयout);
	अगर (!ret)
		वापस -ETIMEDOUT;

	ret = ads131e08_पढ़ो_data(st, st->पढ़ोback_len);
	अगर (ret)
		वापस ret;

	वापस ads131e08_exec_cmd(st, ADS131E08_CMD_STOP);
पूर्ण

अटल पूर्णांक ads131e08_पढ़ो_direct(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *value)
अणु
	काष्ठा ads131e08_state *st = iio_priv(indio_dev);
	u8 num_bits, *src;
	पूर्णांक ret;

	ret = ads131e08_pool_data(st);
	अगर (ret)
		वापस ret;

	src = st->rx_buf + ADS131E08_NUM_STATUS_BYTES +
		channel->channel * ADS131E08_NUM_DATA_BYTES(st->data_rate);

	num_bits = ADS131E08_NUM_DATA_BITS(st->data_rate);
	*value = sign_extend32(get_unaligned_be32(src) >> (32 - num_bits), num_bits - 1);

	वापस 0;
पूर्ण

अटल पूर्णांक ads131e08_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *value,
	पूर्णांक *value2, दीर्घ mask)
अणु
	काष्ठा ads131e08_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = ads131e08_पढ़ो_direct(indio_dev, channel, value);
		iio_device_release_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		अगर (st->vref_reg) अणु
			ret = regulator_get_voltage(st->vref_reg);
			अगर (ret < 0)
				वापस ret;

			*value = ret / 1000;
		पूर्ण अन्यथा अणु
			*value = st->vref_mv;
		पूर्ण

		*value /= st->channel_config[channel->address].pga_gain;
		*value2 = ADS131E08_NUM_DATA_BITS(st->data_rate) - 1;

		वापस IIO_VAL_FRACTIONAL_LOG2;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*value = st->data_rate;

		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ads131e08_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक value,
	पूर्णांक value2, दीर्घ mask)
अणु
	काष्ठा ads131e08_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = ads131e08_set_data_rate(st, value);
		iio_device_release_direct_mode(indio_dev);
		वापस ret;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("1 2 4 8 16 32 64");

अटल काष्ठा attribute *ads131e08_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ads131e08_attribute_group = अणु
	.attrs = ads131e08_attributes,
पूर्ण;

अटल पूर्णांक ads131e08_debugfs_reg_access(काष्ठा iio_dev *indio_dev,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक ग_लिखोval, अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा ads131e08_state *st = iio_priv(indio_dev);

	अगर (पढ़ोval) अणु
		पूर्णांक ret = ads131e08_पढ़ो_reg(st, reg);
		*पढ़ोval = ret;
		वापस ret;
	पूर्ण

	वापस ads131e08_ग_लिखो_reg(st, reg, ग_लिखोval);
पूर्ण

अटल स्थिर काष्ठा iio_info ads131e08_iio_info = अणु
	.पढ़ो_raw = ads131e08_पढ़ो_raw,
	.ग_लिखो_raw = ads131e08_ग_लिखो_raw,
	.attrs = &ads131e08_attribute_group,
	.debugfs_reg_access = &ads131e08_debugfs_reg_access,
पूर्ण;

अटल पूर्णांक ads131e08_set_trigger_state(काष्ठा iio_trigger *trig, bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा ads131e08_state *st = iio_priv(indio_dev);
	u8 cmd = state ? ADS131E08_CMD_START : ADS131E08_CMD_STOP;

	वापस ads131e08_exec_cmd(st, cmd);
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops ads131e08_trigger_ops = अणु
	.set_trigger_state = &ads131e08_set_trigger_state,
	.validate_device = &iio_trigger_validate_own_device,
पूर्ण;

अटल irqवापस_t ads131e08_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ads131e08_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक chn, i = 0;
	u8 *src, *dest;
	पूर्णांक ret;

	/*
	 * The number of data bits per channel depends on the data rate.
	 * For 32 and 64 ksps data rates, number of data bits per channel
	 * is 16. This हाल is not compliant with used (fixed) scan element
	 * type (be:s24/32>>8). So we use a little tweak to pack properly
	 * 16 bits of data पूर्णांकo the buffer.
	 */
	अचिन्हित पूर्णांक num_bytes = ADS131E08_NUM_DATA_BYTES(st->data_rate);
	u8 tweek_offset = num_bytes == 2 ? 1 : 0;

	अगर (iio_trigger_using_own(indio_dev))
		ret = ads131e08_पढ़ो_data(st, st->पढ़ोback_len);
	अन्यथा
		ret = ads131e08_pool_data(st);

	अगर (ret)
		जाओ out;

	क्रम_each_set_bit(chn, indio_dev->active_scan_mask, indio_dev->masklength) अणु
		src = st->rx_buf + ADS131E08_NUM_STATUS_BYTES + chn * num_bytes;
		dest = st->पंचांगp_buf.data + i * ADS131E08_NUM_STORAGE_BYTES;

		/*
		 * Tweek offset is 0:
		 * +---+---+---+---+
		 * |D0 |D1 |D2 | X | (3 data bytes)
		 * +---+---+---+---+
		 *  a+0 a+1 a+2 a+3
		 *
		 * Tweek offset is 1:
		 * +---+---+---+---+
		 * |P0 |D0 |D1 | X | (one padding byte and 2 data bytes)
		 * +---+---+---+---+
		 *  a+0 a+1 a+2 a+3
		 */
		स_नकल(dest + tweek_offset, src, num_bytes);

		/*
		 * Data conversion from 16 bits of data to 24 bits of data
		 * is करोne by sign extension (properly filling padding byte).
		 */
		अगर (tweek_offset)
			*dest = *src & BIT(7) ? 0xff : 0x00;

		i++;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, st->पंचांगp_buf.data,
		iio_get_समय_ns(indio_dev));

out:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ads131e08_पूर्णांकerrupt(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा ads131e08_state *st = iio_priv(indio_dev);

	अगर (iio_buffer_enabled(indio_dev) && iio_trigger_using_own(indio_dev))
		iio_trigger_poll(st->trig);
	अन्यथा
		complete(&st->completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ads131e08_alloc_channels(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ads131e08_state *st = iio_priv(indio_dev);
	काष्ठा ads131e08_channel_config *channel_config;
	काष्ठा device *dev = &st->spi->dev;
	काष्ठा iio_chan_spec *channels;
	काष्ठा fwnode_handle *node;
	अचिन्हित पूर्णांक channel, पंचांगp;
	पूर्णांक num_channels, i, ret;

	ret = device_property_पढ़ो_u32(dev, "ti,vref-internal", &पंचांगp);
	अगर (ret)
		पंचांगp = 0;

	चयन (पंचांगp) अणु
	हाल 0:
		st->vref_mv = ADS131E08_VREF_2V4_mV;
		अवरोध;
	हाल 1:
		st->vref_mv = ADS131E08_VREF_4V_mV;
		अवरोध;
	शेष:
		dev_err(&st->spi->dev, "invalid internal voltage reference\n");
		वापस -EINVAL;
	पूर्ण

	num_channels = device_get_child_node_count(dev);
	अगर (num_channels == 0) अणु
		dev_err(&st->spi->dev, "no channel children\n");
		वापस -ENODEV;
	पूर्ण

	अगर (num_channels > st->info->max_channels) अणु
		dev_err(&st->spi->dev, "num of channel children out of range\n");
		वापस -EINVAL;
	पूर्ण

	channels = devm_kसुस्मृति(&st->spi->dev, num_channels,
		माप(*channels), GFP_KERNEL);
	अगर (!channels)
		वापस -ENOMEM;

	channel_config = devm_kसुस्मृति(&st->spi->dev, num_channels,
		माप(*channel_config), GFP_KERNEL);
	अगर (!channel_config)
		वापस -ENOMEM;

	i = 0;
	device_क्रम_each_child_node(dev, node) अणु
		ret = fwnode_property_पढ़ो_u32(node, "reg", &channel);
		अगर (ret)
			वापस ret;

		ret = fwnode_property_पढ़ो_u32(node, "ti,gain", &पंचांगp);
		अगर (ret) अणु
			channel_config[i].pga_gain = ADS131E08_DEFAULT_PGA_GAIN;
		पूर्ण अन्यथा अणु
			ret = ads131e08_pga_gain_to_field_value(st, पंचांगp);
			अगर (ret < 0)
				वापस ret;

			channel_config[i].pga_gain = पंचांगp;
		पूर्ण

		ret = fwnode_property_पढ़ो_u32(node, "ti,mux", &पंचांगp);
		अगर (ret) अणु
			channel_config[i].mux = ADS131E08_DEFAULT_MUX;
		पूर्ण अन्यथा अणु
			ret = ads131e08_validate_channel_mux(st, पंचांगp);
			अगर (ret)
				वापस ret;

			channel_config[i].mux = पंचांगp;
		पूर्ण

		channels[i].type = IIO_VOLTAGE;
		channels[i].indexed = 1;
		channels[i].channel = channel;
		channels[i].address = i;
		channels[i].info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
						BIT(IIO_CHAN_INFO_SCALE);
		channels[i].info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SAMP_FREQ);
		channels[i].scan_index = channel;
		channels[i].scan_type.sign = 's';
		channels[i].scan_type.realbits = 24;
		channels[i].scan_type.storagebits = 32;
		channels[i].scan_type.shअगरt = 8;
		channels[i].scan_type.endianness = IIO_BE;
		i++;
	पूर्ण

	indio_dev->channels = channels;
	indio_dev->num_channels = num_channels;
	st->channel_config = channel_config;

	वापस 0;
पूर्ण

अटल व्योम ads131e08_regulator_disable(व्योम *data)
अणु
	काष्ठा ads131e08_state *st = data;

	regulator_disable(st->vref_reg);
पूर्ण

अटल व्योम ads131e08_clk_disable(व्योम *data)
अणु
	काष्ठा ads131e08_state *st = data;

	clk_disable_unprepare(st->adc_clk);
पूर्ण

अटल पूर्णांक ads131e08_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा ads131e08_info *info;
	काष्ठा ads131e08_state *st;
	काष्ठा iio_dev *indio_dev;
	अचिन्हित दीर्घ adc_clk_hz;
	अचिन्हित दीर्घ adc_clk_ns;
	पूर्णांक ret;

	info = device_get_match_data(&spi->dev);
	अगर (!info) अणु
		dev_err(&spi->dev, "failed to get match data\n");
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev) अणु
		dev_err(&spi->dev, "failed to allocate IIO device\n");
		वापस -ENOMEM;
	पूर्ण

	st = iio_priv(indio_dev);
	st->info = info;
	st->spi = spi;

	ret = ads131e08_alloc_channels(indio_dev);
	अगर (ret)
		वापस ret;

	indio_dev->name = st->info->name;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &ads131e08_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	init_completion(&st->completion);

	अगर (spi->irq) अणु
		ret = devm_request_irq(&spi->dev, spi->irq,
			ads131e08_पूर्णांकerrupt,
			IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
			spi->dev.driver->name, indio_dev);
		अगर (ret)
			वापस dev_err_probe(&spi->dev, ret,
					     "request irq failed\n");
	पूर्ण अन्यथा अणु
		dev_err(&spi->dev, "data ready IRQ missing\n");
		वापस -ENODEV;
	पूर्ण

	st->trig = devm_iio_trigger_alloc(&spi->dev, "%s-dev%d",
		indio_dev->name, indio_dev->id);
	अगर (!st->trig) अणु
		dev_err(&spi->dev, "failed to allocate IIO trigger\n");
		वापस -ENOMEM;
	पूर्ण

	st->trig->ops = &ads131e08_trigger_ops;
	st->trig->dev.parent = &spi->dev;
	iio_trigger_set_drvdata(st->trig, indio_dev);
	ret = devm_iio_trigger_रेजिस्टर(&spi->dev, st->trig);
	अगर (ret) अणु
		dev_err(&spi->dev, "failed to register IIO trigger\n");
		वापस -ENOMEM;
	पूर्ण

	indio_dev->trig = iio_trigger_get(st->trig);

	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev,
		शून्य, &ads131e08_trigger_handler, शून्य);
	अगर (ret) अणु
		dev_err(&spi->dev, "failed to setup IIO buffer\n");
		वापस ret;
	पूर्ण

	st->vref_reg = devm_regulator_get_optional(&spi->dev, "vref");
	अगर (!IS_ERR(st->vref_reg)) अणु
		ret = regulator_enable(st->vref_reg);
		अगर (ret) अणु
			dev_err(&spi->dev,
				"failed to enable external vref supply\n");
			वापस ret;
		पूर्ण

		ret = devm_add_action_or_reset(&spi->dev, ads131e08_regulator_disable, st);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		अगर (PTR_ERR(st->vref_reg) != -ENODEV)
			वापस PTR_ERR(st->vref_reg);

		st->vref_reg = शून्य;
	पूर्ण

	st->adc_clk = devm_clk_get(&spi->dev, "adc-clk");
	अगर (IS_ERR(st->adc_clk))
		वापस dev_err_probe(&spi->dev, PTR_ERR(st->adc_clk),
				     "failed to get the ADC clock\n");

	ret = clk_prepare_enable(st->adc_clk);
	अगर (ret) अणु
		dev_err(&spi->dev, "failed to prepare/enable the ADC clock\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&spi->dev, ads131e08_clk_disable, st);
	अगर (ret)
		वापस ret;

	adc_clk_hz = clk_get_rate(st->adc_clk);
	अगर (!adc_clk_hz) अणु
		dev_err(&spi->dev, "failed to get the ADC clock rate\n");
		वापस  -EINVAL;
	पूर्ण

	adc_clk_ns = NSEC_PER_SEC / adc_clk_hz;
	st->sdecode_delay_us = DIV_ROUND_UP(
		ADS131E08_WAIT_SDECODE_CYCLES * adc_clk_ns, NSEC_PER_USEC);
	st->reset_delay_us = DIV_ROUND_UP(
		ADS131E08_WAIT_RESET_CYCLES * adc_clk_ns, NSEC_PER_USEC);

	ret = ads131e08_initial_config(indio_dev);
	अगर (ret) अणु
		dev_err(&spi->dev, "initial configuration failed\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ads131e08_of_match[] = अणु
	अणु .compatible = "ti,ads131e04",
	  .data = &ads131e08_info_tbl[ads131e04], पूर्ण,
	अणु .compatible = "ti,ads131e06",
	  .data = &ads131e08_info_tbl[ads131e06], पूर्ण,
	अणु .compatible = "ti,ads131e08",
	  .data = &ads131e08_info_tbl[ads131e08], पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ads131e08_of_match);

अटल काष्ठा spi_driver ads131e08_driver = अणु
	.driver = अणु
		.name = "ads131e08",
		.of_match_table = ads131e08_of_match,
	पूर्ण,
	.probe = ads131e08_probe,
पूर्ण;
module_spi_driver(ads131e08_driver);

MODULE_AUTHOR("Tomislav Denis <tomislav.denis@avl.com>");
MODULE_DESCRIPTION("Driver for ADS131E0x ADC family");
MODULE_LICENSE("GPL v2");
