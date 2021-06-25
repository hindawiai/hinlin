<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * AD7124 SPI ADC driver
 *
 * Copyright 2018 Analog Devices Inc.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/adc/ad_sigma_delta.h>
#समावेश <linux/iio/sysfs.h>

/* AD7124 रेजिस्टरs */
#घोषणा AD7124_COMMS			0x00
#घोषणा AD7124_STATUS			0x00
#घोषणा AD7124_ADC_CONTROL		0x01
#घोषणा AD7124_DATA			0x02
#घोषणा AD7124_IO_CONTROL_1		0x03
#घोषणा AD7124_IO_CONTROL_2		0x04
#घोषणा AD7124_ID			0x05
#घोषणा AD7124_ERROR			0x06
#घोषणा AD7124_ERROR_EN		0x07
#घोषणा AD7124_MCLK_COUNT		0x08
#घोषणा AD7124_CHANNEL(x)		(0x09 + (x))
#घोषणा AD7124_CONFIG(x)		(0x19 + (x))
#घोषणा AD7124_FILTER(x)		(0x21 + (x))
#घोषणा AD7124_OFFSET(x)		(0x29 + (x))
#घोषणा AD7124_GAIN(x)			(0x31 + (x))

/* AD7124_STATUS */
#घोषणा AD7124_STATUS_POR_FLAG_MSK	BIT(4)

/* AD7124_ADC_CONTROL */
#घोषणा AD7124_ADC_CTRL_REF_EN_MSK	BIT(8)
#घोषणा AD7124_ADC_CTRL_REF_EN(x)	FIELD_PREP(AD7124_ADC_CTRL_REF_EN_MSK, x)
#घोषणा AD7124_ADC_CTRL_PWR_MSK	GENMASK(7, 6)
#घोषणा AD7124_ADC_CTRL_PWR(x)		FIELD_PREP(AD7124_ADC_CTRL_PWR_MSK, x)
#घोषणा AD7124_ADC_CTRL_MODE_MSK	GENMASK(5, 2)
#घोषणा AD7124_ADC_CTRL_MODE(x)	FIELD_PREP(AD7124_ADC_CTRL_MODE_MSK, x)

/* AD7124 ID */
#घोषणा AD7124_DEVICE_ID_MSK		GENMASK(7, 4)
#घोषणा AD7124_DEVICE_ID_GET(x)		FIELD_GET(AD7124_DEVICE_ID_MSK, x)
#घोषणा AD7124_SILICON_REV_MSK		GENMASK(3, 0)
#घोषणा AD7124_SILICON_REV_GET(x)	FIELD_GET(AD7124_SILICON_REV_MSK, x)

#घोषणा CHIPID_AD7124_4			0x0
#घोषणा CHIPID_AD7124_8			0x1

/* AD7124_CHANNEL_X */
#घोषणा AD7124_CHANNEL_EN_MSK		BIT(15)
#घोषणा AD7124_CHANNEL_EN(x)		FIELD_PREP(AD7124_CHANNEL_EN_MSK, x)
#घोषणा AD7124_CHANNEL_SETUP_MSK	GENMASK(14, 12)
#घोषणा AD7124_CHANNEL_SETUP(x)	FIELD_PREP(AD7124_CHANNEL_SETUP_MSK, x)
#घोषणा AD7124_CHANNEL_AINP_MSK	GENMASK(9, 5)
#घोषणा AD7124_CHANNEL_AINP(x)		FIELD_PREP(AD7124_CHANNEL_AINP_MSK, x)
#घोषणा AD7124_CHANNEL_AINM_MSK	GENMASK(4, 0)
#घोषणा AD7124_CHANNEL_AINM(x)		FIELD_PREP(AD7124_CHANNEL_AINM_MSK, x)

/* AD7124_CONFIG_X */
#घोषणा AD7124_CONFIG_BIPOLAR_MSK	BIT(11)
#घोषणा AD7124_CONFIG_BIPOLAR(x)	FIELD_PREP(AD7124_CONFIG_BIPOLAR_MSK, x)
#घोषणा AD7124_CONFIG_REF_SEL_MSK	GENMASK(4, 3)
#घोषणा AD7124_CONFIG_REF_SEL(x)	FIELD_PREP(AD7124_CONFIG_REF_SEL_MSK, x)
#घोषणा AD7124_CONFIG_PGA_MSK		GENMASK(2, 0)
#घोषणा AD7124_CONFIG_PGA(x)		FIELD_PREP(AD7124_CONFIG_PGA_MSK, x)
#घोषणा AD7124_CONFIG_IN_BUFF_MSK	GENMASK(7, 6)
#घोषणा AD7124_CONFIG_IN_BUFF(x)	FIELD_PREP(AD7124_CONFIG_IN_BUFF_MSK, x)

/* AD7124_FILTER_X */
#घोषणा AD7124_FILTER_FS_MSK		GENMASK(10, 0)
#घोषणा AD7124_FILTER_FS(x)		FIELD_PREP(AD7124_FILTER_FS_MSK, x)
#घोषणा AD7124_FILTER_TYPE_MSK		GENMASK(23, 21)
#घोषणा AD7124_FILTER_TYPE_SEL(x)	FIELD_PREP(AD7124_FILTER_TYPE_MSK, x)

#घोषणा AD7124_SINC3_FILTER 2
#घोषणा AD7124_SINC4_FILTER 0

#घोषणा AD7124_CONF_ADDR_OFFSET	20
#घोषणा AD7124_MAX_CONFIGS	8
#घोषणा AD7124_MAX_CHANNELS	16

क्रमागत ad7124_ids अणु
	ID_AD7124_4,
	ID_AD7124_8,
पूर्ण;

क्रमागत ad7124_ref_sel अणु
	AD7124_REFIN1,
	AD7124_REFIN2,
	AD7124_INT_REF,
	AD7124_AVDD_REF,
पूर्ण;

क्रमागत ad7124_घातer_mode अणु
	AD7124_LOW_POWER,
	AD7124_MID_POWER,
	AD7124_FULL_POWER,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ad7124_gain[8] = अणु
	1, 2, 4, 8, 16, 32, 64, 128
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ad7124_reg_size[] = अणु
	1, 2, 3, 3, 2, 1, 3, 3, 1, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3
पूर्ण;

अटल स्थिर पूर्णांक ad7124_master_clk_freq_hz[3] = अणु
	[AD7124_LOW_POWER] = 76800,
	[AD7124_MID_POWER] = 153600,
	[AD7124_FULL_POWER] = 614400,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ad7124_ref_names[] = अणु
	[AD7124_REFIN1] = "refin1",
	[AD7124_REFIN2] = "refin2",
	[AD7124_INT_REF] = "int",
	[AD7124_AVDD_REF] = "avdd",
पूर्ण;

काष्ठा ad7124_chip_info अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक chip_id;
	अचिन्हित पूर्णांक num_inमाला_दो;
पूर्ण;

काष्ठा ad7124_channel_config अणु
	bool live;
	अचिन्हित पूर्णांक cfg_slot;
	क्रमागत ad7124_ref_sel refsel;
	bool bipolar;
	bool buf_positive;
	bool buf_negative;
	अचिन्हित पूर्णांक vref_mv;
	अचिन्हित पूर्णांक pga_bits;
	अचिन्हित पूर्णांक odr;
	अचिन्हित पूर्णांक odr_sel_bits;
	अचिन्हित पूर्णांक filter_type;
पूर्ण;

काष्ठा ad7124_channel अणु
	अचिन्हित पूर्णांक nr;
	काष्ठा ad7124_channel_config cfg;
	अचिन्हित पूर्णांक ain;
	अचिन्हित पूर्णांक slot;
पूर्ण;

काष्ठा ad7124_state अणु
	स्थिर काष्ठा ad7124_chip_info *chip_info;
	काष्ठा ad_sigma_delta sd;
	काष्ठा ad7124_channel *channels;
	काष्ठा regulator *vref[4];
	काष्ठा clk *mclk;
	अचिन्हित पूर्णांक adc_control;
	अचिन्हित पूर्णांक num_channels;
	काष्ठा mutex cfgs_lock; /* lock क्रम configs access */
	अचिन्हित दीर्घ cfg_slots_status; /* biपंचांगap with slot status (1 means it is used) */
	DECLARE_KFIFO(live_cfgs_fअगरo, काष्ठा ad7124_channel_config *, AD7124_MAX_CONFIGS);
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad7124_channel_ढाँचा = अणु
	.type = IIO_VOLTAGE,
	.indexed = 1,
	.dअगरferential = 1,
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		BIT(IIO_CHAN_INFO_SCALE) |
		BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |
		BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY),
	.scan_type = अणु
		.sign = 'u',
		.realbits = 24,
		.storagebits = 32,
		.shअगरt = 8,
		.endianness = IIO_BE,
	पूर्ण,
पूर्ण;

अटल काष्ठा ad7124_chip_info ad7124_chip_info_tbl[] = अणु
	[ID_AD7124_4] = अणु
		.name = "ad7124-4",
		.chip_id = CHIPID_AD7124_4,
		.num_inमाला_दो = 8,
	पूर्ण,
	[ID_AD7124_8] = अणु
		.name = "ad7124-8",
		.chip_id = CHIPID_AD7124_8,
		.num_inमाला_दो = 16,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad7124_find_बंदst_match(स्थिर पूर्णांक *array,
				     अचिन्हित पूर्णांक size, पूर्णांक val)
अणु
	पूर्णांक i, idx;
	अचिन्हित पूर्णांक dअगरf_new, dअगरf_old;

	dअगरf_old = U32_MAX;
	idx = 0;

	क्रम (i = 0; i < size; i++) अणु
		dअगरf_new = असल(val - array[i]);
		अगर (dअगरf_new < dअगरf_old) अणु
			dअगरf_old = dअगरf_new;
			idx = i;
		पूर्ण
	पूर्ण

	वापस idx;
पूर्ण

अटल पूर्णांक ad7124_spi_ग_लिखो_mask(काष्ठा ad7124_state *st,
				 अचिन्हित पूर्णांक addr,
				 अचिन्हित दीर्घ mask,
				 अचिन्हित पूर्णांक val,
				 अचिन्हित पूर्णांक bytes)
अणु
	अचिन्हित पूर्णांक पढ़ोval;
	पूर्णांक ret;

	ret = ad_sd_पढ़ो_reg(&st->sd, addr, bytes, &पढ़ोval);
	अगर (ret < 0)
		वापस ret;

	पढ़ोval &= ~mask;
	पढ़ोval |= val;

	वापस ad_sd_ग_लिखो_reg(&st->sd, addr, bytes, पढ़ोval);
पूर्ण

अटल पूर्णांक ad7124_set_mode(काष्ठा ad_sigma_delta *sd,
			   क्रमागत ad_sigma_delta_mode mode)
अणु
	काष्ठा ad7124_state *st = container_of(sd, काष्ठा ad7124_state, sd);

	st->adc_control &= ~AD7124_ADC_CTRL_MODE_MSK;
	st->adc_control |= AD7124_ADC_CTRL_MODE(mode);

	वापस ad_sd_ग_लिखो_reg(&st->sd, AD7124_ADC_CONTROL, 2, st->adc_control);
पूर्ण

अटल व्योम ad7124_set_channel_odr(काष्ठा ad7124_state *st, अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक odr)
अणु
	अचिन्हित पूर्णांक fclk, odr_sel_bits;

	fclk = clk_get_rate(st->mclk);
	/*
	 * FS[10:0] = fCLK / (fADC x 32) where:
	 * fADC is the output data rate
	 * fCLK is the master घड़ी frequency
	 * FS[10:0] are the bits in the filter रेजिस्टर
	 * FS[10:0] can have a value from 1 to 2047
	 */
	odr_sel_bits = DIV_ROUND_CLOSEST(fclk, odr * 32);
	अगर (odr_sel_bits < 1)
		odr_sel_bits = 1;
	अन्यथा अगर (odr_sel_bits > 2047)
		odr_sel_bits = 2047;

	अगर (odr_sel_bits != st->channels[channel].cfg.odr_sel_bits)
		st->channels[channel].cfg.live = false;

	/* fADC = fCLK / (FS[10:0] x 32) */
	st->channels[channel].cfg.odr = DIV_ROUND_CLOSEST(fclk, odr_sel_bits * 32);
	st->channels[channel].cfg.odr_sel_bits = odr_sel_bits;
पूर्ण

अटल पूर्णांक ad7124_get_3db_filter_freq(काष्ठा ad7124_state *st,
				      अचिन्हित पूर्णांक channel)
अणु
	अचिन्हित पूर्णांक fadc;

	fadc = st->channels[channel].cfg.odr;

	चयन (st->channels[channel].cfg.filter_type) अणु
	हाल AD7124_SINC3_FILTER:
		वापस DIV_ROUND_CLOSEST(fadc * 230, 1000);
	हाल AD7124_SINC4_FILTER:
		वापस DIV_ROUND_CLOSEST(fadc * 262, 1000);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम ad7124_set_3db_filter_freq(काष्ठा ad7124_state *st, अचिन्हित पूर्णांक channel,
				       अचिन्हित पूर्णांक freq)
अणु
	अचिन्हित पूर्णांक sinc4_3db_odr;
	अचिन्हित पूर्णांक sinc3_3db_odr;
	अचिन्हित पूर्णांक new_filter;
	अचिन्हित पूर्णांक new_odr;

	sinc4_3db_odr = DIV_ROUND_CLOSEST(freq * 1000, 230);
	sinc3_3db_odr = DIV_ROUND_CLOSEST(freq * 1000, 262);

	अगर (sinc4_3db_odr > sinc3_3db_odr) अणु
		new_filter = AD7124_SINC3_FILTER;
		new_odr = sinc4_3db_odr;
	पूर्ण अन्यथा अणु
		new_filter = AD7124_SINC4_FILTER;
		new_odr = sinc3_3db_odr;
	पूर्ण

	अगर (new_odr != st->channels[channel].cfg.odr)
		st->channels[channel].cfg.live = false;

	st->channels[channel].cfg.filter_type = new_filter;
	st->channels[channel].cfg.odr = new_odr;
पूर्ण

अटल काष्ठा ad7124_channel_config *ad7124_find_similar_live_cfg(काष्ठा ad7124_state *st,
								  काष्ठा ad7124_channel_config *cfg)
अणु
	काष्ठा ad7124_channel_config *cfg_aux;
	सूचक_भेद_प्रकार cmp_size;
	पूर्णांक i;

	cmp_size = (u8 *)&cfg->live - (u8 *)cfg;
	क्रम (i = 0; i < st->num_channels; i++) अणु
		cfg_aux = &st->channels[i].cfg;

		अगर (cfg_aux->live && !स_भेद(cfg, cfg_aux, cmp_size))
			वापस cfg_aux;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक ad7124_find_मुक्त_config_slot(काष्ठा ad7124_state *st)
अणु
	अचिन्हित पूर्णांक मुक्त_cfg_slot;

	मुक्त_cfg_slot = find_next_zero_bit(&st->cfg_slots_status, AD7124_MAX_CONFIGS, 0);
	अगर (मुक्त_cfg_slot == AD7124_MAX_CONFIGS)
		वापस -1;

	वापस मुक्त_cfg_slot;
पूर्ण

अटल पूर्णांक ad7124_init_config_vref(काष्ठा ad7124_state *st, काष्ठा ad7124_channel_config *cfg)
अणु
	अचिन्हित पूर्णांक refsel = cfg->refsel;

	चयन (refsel) अणु
	हाल AD7124_REFIN1:
	हाल AD7124_REFIN2:
	हाल AD7124_AVDD_REF:
		अगर (IS_ERR(st->vref[refsel])) अणु
			dev_err(&st->sd.spi->dev,
				"Error, trying to use external voltage reference without a %s regulator.\n",
				ad7124_ref_names[refsel]);
			वापस PTR_ERR(st->vref[refsel]);
		पूर्ण
		cfg->vref_mv = regulator_get_voltage(st->vref[refsel]);
		/* Conversion from uV to mV */
		cfg->vref_mv /= 1000;
		वापस 0;
	हाल AD7124_INT_REF:
		cfg->vref_mv = 2500;
		st->adc_control &= ~AD7124_ADC_CTRL_REF_EN_MSK;
		st->adc_control |= AD7124_ADC_CTRL_REF_EN(1);
		वापस ad_sd_ग_लिखो_reg(&st->sd, AD7124_ADC_CONTROL,
				      2, st->adc_control);
	शेष:
		dev_err(&st->sd.spi->dev, "Invalid reference %d\n", refsel);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad7124_ग_लिखो_config(काष्ठा ad7124_state *st, काष्ठा ad7124_channel_config *cfg,
			       अचिन्हित पूर्णांक cfg_slot)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	cfg->cfg_slot = cfg_slot;

	पंचांगp = (cfg->buf_positive << 1) + cfg->buf_negative;
	val = AD7124_CONFIG_BIPOLAR(cfg->bipolar) | AD7124_CONFIG_REF_SEL(cfg->refsel) |
	      AD7124_CONFIG_IN_BUFF(पंचांगp);
	ret = ad_sd_ग_लिखो_reg(&st->sd, AD7124_CONFIG(cfg->cfg_slot), 2, val);
	अगर (ret < 0)
		वापस ret;

	पंचांगp = AD7124_FILTER_TYPE_SEL(cfg->filter_type);
	ret = ad7124_spi_ग_लिखो_mask(st, AD7124_FILTER(cfg->cfg_slot), AD7124_FILTER_TYPE_MSK,
				    पंचांगp, 3);
	अगर (ret < 0)
		वापस ret;

	ret = ad7124_spi_ग_लिखो_mask(st, AD7124_FILTER(cfg->cfg_slot), AD7124_FILTER_FS_MSK,
				    AD7124_FILTER_FS(cfg->odr_sel_bits), 3);
	अगर (ret < 0)
		वापस ret;

	वापस ad7124_spi_ग_लिखो_mask(st, AD7124_CONFIG(cfg->cfg_slot), AD7124_CONFIG_PGA_MSK,
				     AD7124_CONFIG_PGA(cfg->pga_bits), 2);
पूर्ण

अटल काष्ठा ad7124_channel_config *ad7124_pop_config(काष्ठा ad7124_state *st)
अणु
	काष्ठा ad7124_channel_config *lru_cfg;
	काष्ठा ad7124_channel_config *cfg;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * Pop least recently used config from the fअगरo
	 * in order to make room क्रम the new one
	 */
	ret = kfअगरo_get(&st->live_cfgs_fअगरo, &lru_cfg);
	अगर (ret <= 0)
		वापस शून्य;

	lru_cfg->live = false;

	/* mark slot as मुक्त */
	assign_bit(lru_cfg->cfg_slot, &st->cfg_slots_status, 0);

	/* invalidate all other configs that poपूर्णांकed to this one */
	क्रम (i = 0; i < st->num_channels; i++) अणु
		cfg = &st->channels[i].cfg;

		अगर (cfg->cfg_slot == lru_cfg->cfg_slot)
			cfg->live = false;
	पूर्ण

	वापस lru_cfg;
पूर्ण

अटल पूर्णांक ad7124_push_config(काष्ठा ad7124_state *st, काष्ठा ad7124_channel_config *cfg)
अणु
	काष्ठा ad7124_channel_config *lru_cfg;
	पूर्णांक मुक्त_cfg_slot;

	मुक्त_cfg_slot = ad7124_find_मुक्त_config_slot(st);
	अगर (मुक्त_cfg_slot >= 0) अणु
		/* push the new config in configs queue */
		kfअगरo_put(&st->live_cfgs_fअगरo, cfg);
	पूर्ण अन्यथा अणु
		/* pop one config to make room क्रम the new one */
		lru_cfg = ad7124_pop_config(st);
		अगर (!lru_cfg)
			वापस -EINVAL;

		/* push the new config in configs queue */
		मुक्त_cfg_slot = lru_cfg->cfg_slot;
		kfअगरo_put(&st->live_cfgs_fअगरo, cfg);
	पूर्ण

	/* mark slot as used */
	assign_bit(मुक्त_cfg_slot, &st->cfg_slots_status, 1);

	वापस ad7124_ग_लिखो_config(st, cfg, मुक्त_cfg_slot);
पूर्ण

अटल पूर्णांक ad7124_enable_channel(काष्ठा ad7124_state *st, काष्ठा ad7124_channel *ch)
अणु
	ch->cfg.live = true;
	वापस ad_sd_ग_लिखो_reg(&st->sd, AD7124_CHANNEL(ch->nr), 2, ch->ain |
			      AD7124_CHANNEL_SETUP(ch->cfg.cfg_slot) | AD7124_CHANNEL_EN(1));
पूर्ण

अटल पूर्णांक ad7124_prepare_पढ़ो(काष्ठा ad7124_state *st, पूर्णांक address)
अणु
	काष्ठा ad7124_channel_config *cfg = &st->channels[address].cfg;
	काष्ठा ad7124_channel_config *live_cfg;

	/*
	 * Beक्रमe करोing any पढ़ोs assign the channel a configuration.
	 * Check अगर channel's config is on the device
	 */
	अगर (!cfg->live) अणु
		/* check अगर config matches another one */
		live_cfg = ad7124_find_similar_live_cfg(st, cfg);
		अगर (!live_cfg)
			ad7124_push_config(st, cfg);
		अन्यथा
			cfg->cfg_slot = live_cfg->cfg_slot;
	पूर्ण

	/* poपूर्णांक channel to the config slot and enable */
	वापस ad7124_enable_channel(st, &st->channels[address]);
पूर्ण

अटल पूर्णांक ad7124_set_channel(काष्ठा ad_sigma_delta *sd, अचिन्हित पूर्णांक channel)
अणु
	काष्ठा ad7124_state *st = container_of(sd, काष्ठा ad7124_state, sd);
	पूर्णांक ret;

	mutex_lock(&st->cfgs_lock);
	ret = ad7124_prepare_पढ़ो(st, channel);
	mutex_unlock(&st->cfgs_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ad_sigma_delta_info ad7124_sigma_delta_info = अणु
	.set_channel = ad7124_set_channel,
	.set_mode = ad7124_set_mode,
	.has_रेजिस्टरs = true,
	.addr_shअगरt = 0,
	.पढ़ो_mask = BIT(6),
	.data_reg = AD7124_DATA,
	.irq_flags = IRQF_TRIGGER_FALLING
पूर्ण;

अटल पूर्णांक ad7124_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा ad7124_state *st = iio_priv(indio_dev);
	पूर्णांक idx, ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = ad_sigma_delta_single_conversion(indio_dev, chan, val);
		अगर (ret < 0)
			वापस ret;

		/* After the conversion is perक्रमmed, disable the channel */
		ret = ad_sd_ग_लिखो_reg(&st->sd, AD7124_CHANNEL(chan->address), 2,
				      st->channels[chan->address].ain | AD7124_CHANNEL_EN(0));
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		mutex_lock(&st->cfgs_lock);

		idx = st->channels[chan->address].cfg.pga_bits;
		*val = st->channels[chan->address].cfg.vref_mv;
		अगर (st->channels[chan->address].cfg.bipolar)
			*val2 = chan->scan_type.realbits - 1 + idx;
		अन्यथा
			*val2 = chan->scan_type.realbits + idx;

		mutex_unlock(&st->cfgs_lock);
		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_OFFSET:
		mutex_lock(&st->cfgs_lock);
		अगर (st->channels[chan->address].cfg.bipolar)
			*val = -(1 << (chan->scan_type.realbits - 1));
		अन्यथा
			*val = 0;

		mutex_unlock(&st->cfgs_lock);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&st->cfgs_lock);
		*val = st->channels[chan->address].cfg.odr;
		mutex_unlock(&st->cfgs_lock);

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		mutex_lock(&st->cfgs_lock);
		*val = ad7124_get_3db_filter_freq(st, chan->scan_index);
		mutex_unlock(&st->cfgs_lock);

		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad7124_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	काष्ठा ad7124_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक res, gain, full_scale, vref;
	पूर्णांक ret = 0;

	mutex_lock(&st->cfgs_lock);

	चयन (info) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (val2 != 0) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ad7124_set_channel_odr(st, chan->address, val);
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (val != 0) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (st->channels[chan->address].cfg.bipolar)
			full_scale = 1 << (chan->scan_type.realbits - 1);
		अन्यथा
			full_scale = 1 << chan->scan_type.realbits;

		vref = st->channels[chan->address].cfg.vref_mv * 1000000LL;
		res = DIV_ROUND_CLOSEST(vref, full_scale);
		gain = DIV_ROUND_CLOSEST(res, val2);
		res = ad7124_find_बंदst_match(ad7124_gain, ARRAY_SIZE(ad7124_gain), gain);

		अगर (st->channels[chan->address].cfg.pga_bits != res)
			st->channels[chan->address].cfg.live = false;

		st->channels[chan->address].cfg.pga_bits = res;
		अवरोध;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		अगर (val2 != 0) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ad7124_set_3db_filter_freq(st, chan->address, val);
		अवरोध;
	शेष:
		ret =  -EINVAL;
	पूर्ण

	mutex_unlock(&st->cfgs_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ad7124_reg_access(काष्ठा iio_dev *indio_dev,
			     अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक ग_लिखोval,
			     अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा ad7124_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (reg >= ARRAY_SIZE(ad7124_reg_size))
		वापस -EINVAL;

	अगर (पढ़ोval)
		ret = ad_sd_पढ़ो_reg(&st->sd, reg, ad7124_reg_size[reg],
				     पढ़ोval);
	अन्यथा
		ret = ad_sd_ग_लिखो_reg(&st->sd, reg, ad7124_reg_size[reg],
				      ग_लिखोval);

	वापस ret;
पूर्ण

अटल IIO_CONST_ATTR(in_voltage_scale_available,
	"0.000001164 0.000002328 0.000004656 0.000009313 0.000018626 0.000037252 0.000074505 0.000149011 0.000298023");

अटल काष्ठा attribute *ad7124_attributes[] = अणु
	&iio_स्थिर_attr_in_voltage_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7124_attrs_group = अणु
	.attrs = ad7124_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7124_info = अणु
	.पढ़ो_raw = ad7124_पढ़ो_raw,
	.ग_लिखो_raw = ad7124_ग_लिखो_raw,
	.debugfs_reg_access = &ad7124_reg_access,
	.validate_trigger = ad_sd_validate_trigger,
	.attrs = &ad7124_attrs_group,
पूर्ण;

अटल पूर्णांक ad7124_soft_reset(काष्ठा ad7124_state *st)
अणु
	अचिन्हित पूर्णांक पढ़ोval, समयout;
	पूर्णांक ret;

	ret = ad_sd_reset(&st->sd, 64);
	अगर (ret < 0)
		वापस ret;

	समयout = 100;
	करो अणु
		ret = ad_sd_पढ़ो_reg(&st->sd, AD7124_STATUS, 1, &पढ़ोval);
		अगर (ret < 0)
			वापस ret;

		अगर (!(पढ़ोval & AD7124_STATUS_POR_FLAG_MSK))
			वापस 0;

		/* The AD7124 requires typically 2ms to घातer up and settle */
		usleep_range(100, 2000);
	पूर्ण जबतक (--समयout);

	dev_err(&st->sd.spi->dev, "Soft reset failed\n");

	वापस -EIO;
पूर्ण

अटल पूर्णांक ad7124_check_chip_id(काष्ठा ad7124_state *st)
अणु
	अचिन्हित पूर्णांक पढ़ोval, chip_id, silicon_rev;
	पूर्णांक ret;

	ret = ad_sd_पढ़ो_reg(&st->sd, AD7124_ID, 1, &पढ़ोval);
	अगर (ret < 0)
		वापस ret;

	chip_id = AD7124_DEVICE_ID_GET(पढ़ोval);
	silicon_rev = AD7124_SILICON_REV_GET(पढ़ोval);

	अगर (chip_id != st->chip_info->chip_id) अणु
		dev_err(&st->sd.spi->dev,
			"Chip ID mismatch: expected %u, got %u\n",
			st->chip_info->chip_id, chip_id);
		वापस -ENODEV;
	पूर्ण

	अगर (silicon_rev == 0) अणु
		dev_err(&st->sd.spi->dev,
			"Silicon revision empty. Chip may not be present\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad7124_of_parse_channel_config(काष्ठा iio_dev *indio_dev,
					  काष्ठा device_node *np)
अणु
	काष्ठा ad7124_state *st = iio_priv(indio_dev);
	काष्ठा ad7124_channel_config *cfg;
	काष्ठा ad7124_channel *channels;
	काष्ठा device_node *child;
	काष्ठा iio_chan_spec *chan;
	अचिन्हित पूर्णांक ain[2], channel = 0, पंचांगp;
	पूर्णांक ret;

	st->num_channels = of_get_available_child_count(np);
	अगर (!st->num_channels) अणु
		dev_err(indio_dev->dev.parent, "no channel children\n");
		वापस -ENODEV;
	पूर्ण

	chan = devm_kसुस्मृति(indio_dev->dev.parent, st->num_channels,
			    माप(*chan), GFP_KERNEL);
	अगर (!chan)
		वापस -ENOMEM;

	channels = devm_kसुस्मृति(indio_dev->dev.parent, st->num_channels, माप(*channels),
				GFP_KERNEL);
	अगर (!channels)
		वापस -ENOMEM;

	indio_dev->channels = chan;
	indio_dev->num_channels = st->num_channels;
	st->channels = channels;

	क्रम_each_available_child_of_node(np, child) अणु
		cfg = &st->channels[channel].cfg;

		ret = of_property_पढ़ो_u32(child, "reg", &channel);
		अगर (ret)
			जाओ err;

		अगर (channel >= indio_dev->num_channels) अणु
			dev_err(indio_dev->dev.parent,
				"Channel index >= number of channels\n");
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		ret = of_property_पढ़ो_u32_array(child, "diff-channels",
						 ain, 2);
		अगर (ret)
			जाओ err;

		st->channels[channel].nr = channel;
		st->channels[channel].ain = AD7124_CHANNEL_AINP(ain[0]) |
						  AD7124_CHANNEL_AINM(ain[1]);

		cfg->bipolar = of_property_पढ़ो_bool(child, "bipolar");

		ret = of_property_पढ़ो_u32(child, "adi,reference-select", &पंचांगp);
		अगर (ret)
			cfg->refsel = AD7124_INT_REF;
		अन्यथा
			cfg->refsel = पंचांगp;

		cfg->buf_positive = of_property_पढ़ो_bool(child, "adi,buffered-positive");
		cfg->buf_negative = of_property_पढ़ो_bool(child, "adi,buffered-negative");

		chan[channel] = ad7124_channel_ढाँचा;
		chan[channel].address = channel;
		chan[channel].scan_index = channel;
		chan[channel].channel = ain[0];
		chan[channel].channel2 = ain[1];
	पूर्ण

	वापस 0;
err:
	of_node_put(child);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7124_setup(काष्ठा ad7124_state *st)
अणु
	अचिन्हित पूर्णांक fclk, घातer_mode;
	पूर्णांक i, ret;

	fclk = clk_get_rate(st->mclk);
	अगर (!fclk)
		वापस -EINVAL;

	/* The घातer mode changes the master घड़ी frequency */
	घातer_mode = ad7124_find_बंदst_match(ad7124_master_clk_freq_hz,
					ARRAY_SIZE(ad7124_master_clk_freq_hz),
					fclk);
	अगर (fclk != ad7124_master_clk_freq_hz[घातer_mode]) अणु
		ret = clk_set_rate(st->mclk, fclk);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Set the घातer mode */
	st->adc_control &= ~AD7124_ADC_CTRL_PWR_MSK;
	st->adc_control |= AD7124_ADC_CTRL_PWR(घातer_mode);
	ret = ad_sd_ग_लिखो_reg(&st->sd, AD7124_ADC_CONTROL, 2, st->adc_control);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&st->cfgs_lock);
	INIT_KFIFO(st->live_cfgs_fअगरo);
	क्रम (i = 0; i < st->num_channels; i++) अणु

		ret = ad7124_init_config_vref(st, &st->channels[i].cfg);
		अगर (ret < 0)
			वापस ret;

		/*
		 * 9.38 SPS is the minimum output data rate supported
		 * regardless of the selected घातer mode. Round it up to 10 and
		 * set all channels to this शेष value.
		 */
		ad7124_set_channel_odr(st, i, 10);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ad7124_reg_disable(व्योम *r)
अणु
	regulator_disable(r);
पूर्ण

अटल पूर्णांक ad7124_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा ad7124_chip_info *info;
	काष्ठा ad7124_state *st;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक i, ret;

	info = of_device_get_match_data(&spi->dev);
	अगर (!info)
		वापस -ENODEV;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	st->chip_info = info;

	ad_sd_init(&st->sd, indio_dev, spi, &ad7124_sigma_delta_info);

	spi_set_drvdata(spi, indio_dev);

	indio_dev->name = st->chip_info->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &ad7124_info;

	ret = ad7124_of_parse_channel_config(indio_dev, spi->dev.of_node);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(st->vref); i++) अणु
		अगर (i == AD7124_INT_REF)
			जारी;

		st->vref[i] = devm_regulator_get_optional(&spi->dev,
						ad7124_ref_names[i]);
		अगर (PTR_ERR(st->vref[i]) == -ENODEV)
			जारी;
		अन्यथा अगर (IS_ERR(st->vref[i]))
			वापस PTR_ERR(st->vref[i]);

		ret = regulator_enable(st->vref[i]);
		अगर (ret)
			वापस ret;

		ret = devm_add_action_or_reset(&spi->dev, ad7124_reg_disable,
					       st->vref[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	st->mclk = devm_clk_get(&spi->dev, "mclk");
	अगर (IS_ERR(st->mclk))
		वापस PTR_ERR(st->mclk);

	ret = clk_prepare_enable(st->mclk);
	अगर (ret < 0)
		वापस ret;

	ret = ad7124_soft_reset(st);
	अगर (ret < 0)
		जाओ error_clk_disable_unprepare;

	ret = ad7124_check_chip_id(st);
	अगर (ret)
		जाओ error_clk_disable_unprepare;

	ret = ad7124_setup(st);
	अगर (ret < 0)
		जाओ error_clk_disable_unprepare;

	ret = ad_sd_setup_buffer_and_trigger(indio_dev);
	अगर (ret < 0)
		जाओ error_clk_disable_unprepare;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "Failed to register iio device\n");
		जाओ error_हटाओ_trigger;
	पूर्ण

	वापस 0;

error_हटाओ_trigger:
	ad_sd_cleanup_buffer_and_trigger(indio_dev);
error_clk_disable_unprepare:
	clk_disable_unprepare(st->mclk);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7124_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad7124_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	ad_sd_cleanup_buffer_and_trigger(indio_dev);
	clk_disable_unprepare(st->mclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ad7124_of_match[] = अणु
	अणु .compatible = "adi,ad7124-4",
		.data = &ad7124_chip_info_tbl[ID_AD7124_4], पूर्ण,
	अणु .compatible = "adi,ad7124-8",
		.data = &ad7124_chip_info_tbl[ID_AD7124_8], पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7124_of_match);

अटल काष्ठा spi_driver ad71124_driver = अणु
	.driver = अणु
		.name = "ad7124",
		.of_match_table = ad7124_of_match,
	पूर्ण,
	.probe = ad7124_probe,
	.हटाओ	= ad7124_हटाओ,
पूर्ण;
module_spi_driver(ad71124_driver);

MODULE_AUTHOR("Stefan Popa <stefan.popa@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7124 SPI driver");
MODULE_LICENSE("GPL");
