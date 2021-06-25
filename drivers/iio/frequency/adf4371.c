<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Analog Devices ADF4371 SPI Wideband Synthesizer driver
 *
 * Copyright 2019 Analog Devices Inc.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gcd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/iio/iपन.स>

/* Registers address macro */
#घोषणा ADF4371_REG(x)			(x)

/* ADF4371_REG0 */
#घोषणा ADF4371_ADDR_ASC_MSK		BIT(2)
#घोषणा ADF4371_ADDR_ASC(x)		FIELD_PREP(ADF4371_ADDR_ASC_MSK, x)
#घोषणा ADF4371_ADDR_ASC_R_MSK		BIT(5)
#घोषणा ADF4371_ADDR_ASC_R(x)		FIELD_PREP(ADF4371_ADDR_ASC_R_MSK, x)
#घोषणा ADF4371_RESET_CMD		0x81

/* ADF4371_REG17 */
#घोषणा ADF4371_FRAC2WORD_L_MSK		GENMASK(7, 1)
#घोषणा ADF4371_FRAC2WORD_L(x)		FIELD_PREP(ADF4371_FRAC2WORD_L_MSK, x)
#घोषणा ADF4371_FRAC1WORD_MSK		BIT(0)
#घोषणा ADF4371_FRAC1WORD(x)		FIELD_PREP(ADF4371_FRAC1WORD_MSK, x)

/* ADF4371_REG18 */
#घोषणा ADF4371_FRAC2WORD_H_MSK		GENMASK(6, 0)
#घोषणा ADF4371_FRAC2WORD_H(x)		FIELD_PREP(ADF4371_FRAC2WORD_H_MSK, x)

/* ADF4371_REG1A */
#घोषणा ADF4371_MOD2WORD_MSK		GENMASK(5, 0)
#घोषणा ADF4371_MOD2WORD(x)		FIELD_PREP(ADF4371_MOD2WORD_MSK, x)

/* ADF4371_REG24 */
#घोषणा ADF4371_RF_DIV_SEL_MSK		GENMASK(6, 4)
#घोषणा ADF4371_RF_DIV_SEL(x)		FIELD_PREP(ADF4371_RF_DIV_SEL_MSK, x)

/* ADF4371_REG25 */
#घोषणा ADF4371_MUTE_LD_MSK		BIT(7)
#घोषणा ADF4371_MUTE_LD(x)		FIELD_PREP(ADF4371_MUTE_LD_MSK, x)

/* ADF4371_REG32 */
#घोषणा ADF4371_TIMEOUT_MSK		GENMASK(1, 0)
#घोषणा ADF4371_TIMEOUT(x)		FIELD_PREP(ADF4371_TIMEOUT_MSK, x)

/* ADF4371_REG34 */
#घोषणा ADF4371_VCO_ALC_TOUT_MSK	GENMASK(4, 0)
#घोषणा ADF4371_VCO_ALC_TOUT(x)		FIELD_PREP(ADF4371_VCO_ALC_TOUT_MSK, x)

/* Specअगरications */
#घोषणा ADF4371_MIN_VCO_FREQ		4000000000ULL /* 4000 MHz */
#घोषणा ADF4371_MAX_VCO_FREQ		8000000000ULL /* 8000 MHz */
#घोषणा ADF4371_MAX_OUT_RF8_FREQ	ADF4371_MAX_VCO_FREQ /* Hz */
#घोषणा ADF4371_MIN_OUT_RF8_FREQ	(ADF4371_MIN_VCO_FREQ / 64) /* Hz */
#घोषणा ADF4371_MAX_OUT_RF16_FREQ	(ADF4371_MAX_VCO_FREQ * 2) /* Hz */
#घोषणा ADF4371_MIN_OUT_RF16_FREQ	(ADF4371_MIN_VCO_FREQ * 2) /* Hz */
#घोषणा ADF4371_MAX_OUT_RF32_FREQ	(ADF4371_MAX_VCO_FREQ * 4) /* Hz */
#घोषणा ADF4371_MIN_OUT_RF32_FREQ	(ADF4371_MIN_VCO_FREQ * 4) /* Hz */

#घोषणा ADF4371_MAX_FREQ_PFD		250000000UL /* Hz */
#घोषणा ADF4371_MAX_FREQ_REFIN		600000000UL /* Hz */

/* MOD1 is a 24-bit primary modulus with fixed value of 2^25 */
#घोषणा ADF4371_MODULUS1		33554432ULL
/* MOD2 is the programmable, 14-bit auxiliary fractional modulus */
#घोषणा ADF4371_MAX_MODULUS2		BIT(14)

#घोषणा ADF4371_CHECK_RANGE(freq, range) \
	((freq > ADF4371_MAX_ ## range) || (freq < ADF4371_MIN_ ## range))

क्रमागत अणु
	ADF4371_FREQ,
	ADF4371_POWER_DOWN,
	ADF4371_CHANNEL_NAME
पूर्ण;

क्रमागत अणु
	ADF4371_CH_RF8,
	ADF4371_CH_RFAUX8,
	ADF4371_CH_RF16,
	ADF4371_CH_RF32
पूर्ण;

क्रमागत adf4371_variant अणु
	ADF4371,
	ADF4372
पूर्ण;

काष्ठा adf4371_pwrकरोwn अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक bit;
पूर्ण;

अटल स्थिर अक्षर * स्थिर adf4371_ch_names[] = अणु
	"RF8x", "RFAUX8x", "RF16x", "RF32x"
पूर्ण;

अटल स्थिर काष्ठा adf4371_pwrकरोwn adf4371_pwrकरोwn_ch[4] = अणु
	[ADF4371_CH_RF8] = अणु ADF4371_REG(0x25), 2 पूर्ण,
	[ADF4371_CH_RFAUX8] = अणु ADF4371_REG(0x72), 3 पूर्ण,
	[ADF4371_CH_RF16] = अणु ADF4371_REG(0x25), 3 पूर्ण,
	[ADF4371_CH_RF32] = अणु ADF4371_REG(0x25), 4 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence adf4371_reg_शेषs[] = अणु
	अणु ADF4371_REG(0x0),  0x18 पूर्ण,
	अणु ADF4371_REG(0x12), 0x40 पूर्ण,
	अणु ADF4371_REG(0x1E), 0x48 पूर्ण,
	अणु ADF4371_REG(0x20), 0x14 पूर्ण,
	अणु ADF4371_REG(0x22), 0x00 पूर्ण,
	अणु ADF4371_REG(0x23), 0x00 पूर्ण,
	अणु ADF4371_REG(0x24), 0x80 पूर्ण,
	अणु ADF4371_REG(0x25), 0x07 पूर्ण,
	अणु ADF4371_REG(0x27), 0xC5 पूर्ण,
	अणु ADF4371_REG(0x28), 0x83 पूर्ण,
	अणु ADF4371_REG(0x2C), 0x44 पूर्ण,
	अणु ADF4371_REG(0x2D), 0x11 पूर्ण,
	अणु ADF4371_REG(0x2E), 0x12 पूर्ण,
	अणु ADF4371_REG(0x2F), 0x94 पूर्ण,
	अणु ADF4371_REG(0x32), 0x04 पूर्ण,
	अणु ADF4371_REG(0x35), 0xFA पूर्ण,
	अणु ADF4371_REG(0x36), 0x30 पूर्ण,
	अणु ADF4371_REG(0x39), 0x07 पूर्ण,
	अणु ADF4371_REG(0x3A), 0x55 पूर्ण,
	अणु ADF4371_REG(0x3E), 0x0C पूर्ण,
	अणु ADF4371_REG(0x3F), 0x80 पूर्ण,
	अणु ADF4371_REG(0x40), 0x50 पूर्ण,
	अणु ADF4371_REG(0x41), 0x28 पूर्ण,
	अणु ADF4371_REG(0x47), 0xC0 पूर्ण,
	अणु ADF4371_REG(0x52), 0xF4 पूर्ण,
	अणु ADF4371_REG(0x70), 0x03 पूर्ण,
	अणु ADF4371_REG(0x71), 0x60 पूर्ण,
	अणु ADF4371_REG(0x72), 0x32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config adf4371_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.पढ़ो_flag_mask = BIT(7),
पूर्ण;

काष्ठा adf4371_chip_info अणु
	अचिन्हित पूर्णांक num_channels;
	स्थिर काष्ठा iio_chan_spec *channels;
पूर्ण;

काष्ठा adf4371_state अणु
	काष्ठा spi_device *spi;
	काष्ठा regmap *regmap;
	काष्ठा clk *clkin;
	/*
	 * Lock क्रम accessing device रेजिस्टरs. Some operations require
	 * multiple consecutive R/W operations, during which the device
	 * shouldn't be पूर्णांकerrupted. The buffers are also shared across
	 * all operations so need to be रक्षित on stand alone पढ़ोs and
	 * ग_लिखोs.
	 */
	काष्ठा mutex lock;
	स्थिर काष्ठा adf4371_chip_info *chip_info;
	अचिन्हित दीर्घ clkin_freq;
	अचिन्हित दीर्घ fpfd;
	अचिन्हित पूर्णांक पूर्णांकeger;
	अचिन्हित पूर्णांक fract1;
	अचिन्हित पूर्णांक fract2;
	अचिन्हित पूर्णांक mod2;
	अचिन्हित पूर्णांक rf_भाग_sel;
	अचिन्हित पूर्णांक ref_भाग_factor;
	u8 buf[10] ____cacheline_aligned;
पूर्ण;

अटल अचिन्हित दीर्घ दीर्घ adf4371_pll_fract_n_get_rate(काष्ठा adf4371_state *st,
						       u32 channel)
अणु
	अचिन्हित दीर्घ दीर्घ val, पंचांगp;
	अचिन्हित पूर्णांक ref_भाग_sel;

	val = (((u64)st->पूर्णांकeger * ADF4371_MODULUS1) + st->fract1) * st->fpfd;
	पंचांगp = (u64)st->fract2 * st->fpfd;
	करो_भाग(पंचांगp, st->mod2);
	val += पंचांगp + ADF4371_MODULUS1 / 2;

	अगर (channel == ADF4371_CH_RF8 || channel == ADF4371_CH_RFAUX8)
		ref_भाग_sel = st->rf_भाग_sel;
	अन्यथा
		ref_भाग_sel = 0;

	करो_भाग(val, ADF4371_MODULUS1 * (1 << ref_भाग_sel));

	अगर (channel == ADF4371_CH_RF16)
		val <<= 1;
	अन्यथा अगर (channel == ADF4371_CH_RF32)
		val <<= 2;

	वापस val;
पूर्ण

अटल व्योम adf4371_pll_fract_n_compute(अचिन्हित दीर्घ दीर्घ vco,
				       अचिन्हित दीर्घ दीर्घ pfd,
				       अचिन्हित पूर्णांक *पूर्णांकeger,
				       अचिन्हित पूर्णांक *fract1,
				       अचिन्हित पूर्णांक *fract2,
				       अचिन्हित पूर्णांक *mod2)
अणु
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	u32 gcd_भाग;

	पंचांगp = करो_भाग(vco, pfd);
	पंचांगp = पंचांगp * ADF4371_MODULUS1;
	*fract2 = करो_भाग(पंचांगp, pfd);

	*पूर्णांकeger = vco;
	*fract1 = पंचांगp;

	*mod2 = pfd;

	जबतक (*mod2 > ADF4371_MAX_MODULUS2) अणु
		*mod2 >>= 1;
		*fract2 >>= 1;
	पूर्ण

	gcd_भाग = gcd(*fract2, *mod2);
	*mod2 /= gcd_भाग;
	*fract2 /= gcd_भाग;
पूर्ण

अटल पूर्णांक adf4371_set_freq(काष्ठा adf4371_state *st, अचिन्हित दीर्घ दीर्घ freq,
			    अचिन्हित पूर्णांक channel)
अणु
	u32 cp_bleed;
	u8 पूर्णांक_mode = 0;
	पूर्णांक ret;

	चयन (channel) अणु
	हाल ADF4371_CH_RF8:
	हाल ADF4371_CH_RFAUX8:
		अगर (ADF4371_CHECK_RANGE(freq, OUT_RF8_FREQ))
			वापस -EINVAL;

		st->rf_भाग_sel = 0;

		जबतक (freq < ADF4371_MIN_VCO_FREQ) अणु
			freq <<= 1;
			st->rf_भाग_sel++;
		पूर्ण
		अवरोध;
	हाल ADF4371_CH_RF16:
		/* ADF4371 RF16 8000...16000 MHz */
		अगर (ADF4371_CHECK_RANGE(freq, OUT_RF16_FREQ))
			वापस -EINVAL;

		freq >>= 1;
		अवरोध;
	हाल ADF4371_CH_RF32:
		/* ADF4371 RF32 16000...32000 MHz */
		अगर (ADF4371_CHECK_RANGE(freq, OUT_RF32_FREQ))
			वापस -EINVAL;

		freq >>= 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	adf4371_pll_fract_n_compute(freq, st->fpfd, &st->पूर्णांकeger, &st->fract1,
				    &st->fract2, &st->mod2);
	st->buf[0] = st->पूर्णांकeger >> 8;
	st->buf[1] = 0x40; /* REG12 शेष */
	st->buf[2] = 0x00;
	st->buf[3] = st->fract1 & 0xFF;
	st->buf[4] = st->fract1 >> 8;
	st->buf[5] = st->fract1 >> 16;
	st->buf[6] = ADF4371_FRAC2WORD_L(st->fract2 & 0x7F) |
		     ADF4371_FRAC1WORD(st->fract1 >> 24);
	st->buf[7] = ADF4371_FRAC2WORD_H(st->fract2 >> 7);
	st->buf[8] = st->mod2 & 0xFF;
	st->buf[9] = ADF4371_MOD2WORD(st->mod2 >> 8);

	ret = regmap_bulk_ग_लिखो(st->regmap, ADF4371_REG(0x11), st->buf, 10);
	अगर (ret < 0)
		वापस ret;
	/*
	 * The R counter allows the input reference frequency to be
	 * भागided करोwn to produce the reference घड़ी to the PFD
	 */
	ret = regmap_ग_लिखो(st->regmap, ADF4371_REG(0x1F), st->ref_भाग_factor);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(st->regmap, ADF4371_REG(0x24),
				 ADF4371_RF_DIV_SEL_MSK,
				 ADF4371_RF_DIV_SEL(st->rf_भाग_sel));
	अगर (ret < 0)
		वापस ret;

	cp_bleed = DIV_ROUND_UP(400 * 1750, st->पूर्णांकeger * 375);
	cp_bleed = clamp(cp_bleed, 1U, 255U);
	ret = regmap_ग_लिखो(st->regmap, ADF4371_REG(0x26), cp_bleed);
	अगर (ret < 0)
		वापस ret;
	/*
	 * Set to 1 when in INT mode (when FRAC1 = FRAC2 = 0),
	 * and set to 0 when in FRAC mode.
	 */
	अगर (st->fract1 == 0 && st->fract2 == 0)
		पूर्णांक_mode = 0x01;

	ret = regmap_ग_लिखो(st->regmap, ADF4371_REG(0x2B), पूर्णांक_mode);
	अगर (ret < 0)
		वापस ret;

	वापस regmap_ग_लिखो(st->regmap, ADF4371_REG(0x10), st->पूर्णांकeger & 0xFF);
पूर्ण

अटल sमाप_प्रकार adf4371_पढ़ो(काष्ठा iio_dev *indio_dev,
			    uपूर्णांकptr_t निजी,
			    स्थिर काष्ठा iio_chan_spec *chan,
			    अक्षर *buf)
अणु
	काष्ठा adf4371_state *st = iio_priv(indio_dev);
	अचिन्हित दीर्घ दीर्घ val = 0;
	अचिन्हित पूर्णांक पढ़ोval, reg, bit;
	पूर्णांक ret;

	चयन ((u32)निजी) अणु
	हाल ADF4371_FREQ:
		val = adf4371_pll_fract_n_get_rate(st, chan->channel);
		ret = regmap_पढ़ो(st->regmap, ADF4371_REG(0x7C), &पढ़ोval);
		अगर (ret < 0)
			अवरोध;

		अगर (पढ़ोval == 0x00) अणु
			dev_dbg(&st->spi->dev, "PLL un-locked\n");
			ret = -EBUSY;
		पूर्ण
		अवरोध;
	हाल ADF4371_POWER_DOWN:
		reg = adf4371_pwrकरोwn_ch[chan->channel].reg;
		bit = adf4371_pwrकरोwn_ch[chan->channel].bit;

		ret = regmap_पढ़ो(st->regmap, reg, &पढ़ोval);
		अगर (ret < 0)
			अवरोध;

		val = !(पढ़ोval & BIT(bit));
		अवरोध;
	हाल ADF4371_CHANNEL_NAME:
		वापस प्र_लिखो(buf, "%s\n", adf4371_ch_names[chan->channel]);
	शेष:
		ret = -EINVAL;
		val = 0;
		अवरोध;
	पूर्ण

	वापस ret < 0 ? ret : प्र_लिखो(buf, "%llu\n", val);
पूर्ण

अटल sमाप_प्रकार adf4371_ग_लिखो(काष्ठा iio_dev *indio_dev,
			     uपूर्णांकptr_t निजी,
			     स्थिर काष्ठा iio_chan_spec *chan,
			     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा adf4371_state *st = iio_priv(indio_dev);
	अचिन्हित दीर्घ दीर्घ freq;
	bool घातer_करोwn;
	अचिन्हित पूर्णांक bit, पढ़ोval, reg;
	पूर्णांक ret;

	mutex_lock(&st->lock);
	चयन ((u32)निजी) अणु
	हाल ADF4371_FREQ:
		ret = kम_से_अदीर्घl(buf, 10, &freq);
		अगर (ret)
			अवरोध;

		ret = adf4371_set_freq(st, freq, chan->channel);
		अवरोध;
	हाल ADF4371_POWER_DOWN:
		ret = kstrtobool(buf, &घातer_करोwn);
		अगर (ret)
			अवरोध;

		reg = adf4371_pwrकरोwn_ch[chan->channel].reg;
		bit = adf4371_pwrकरोwn_ch[chan->channel].bit;
		ret = regmap_पढ़ो(st->regmap, reg, &पढ़ोval);
		अगर (ret < 0)
			अवरोध;

		पढ़ोval &= ~BIT(bit);
		पढ़ोval |= (!घातer_करोwn << bit);

		ret = regmap_ग_लिखो(st->regmap, reg, पढ़ोval);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	mutex_unlock(&st->lock);

	वापस ret ? ret : len;
पूर्ण

#घोषणा _ADF4371_EXT_INFO(_name, _ident) अणु \
		.name = _name, \
		.पढ़ो = adf4371_पढ़ो, \
		.ग_लिखो = adf4371_ग_लिखो, \
		.निजी = _ident, \
		.shared = IIO_SEPARATE, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info adf4371_ext_info[] = अणु
	/*
	 * Ideally we use IIO_CHAN_INFO_FREQUENCY, but there are
	 * values > 2^32 in order to support the entire frequency range
	 * in Hz. Using scale is a bit ugly.
	 */
	_ADF4371_EXT_INFO("frequency", ADF4371_FREQ),
	_ADF4371_EXT_INFO("powerdown", ADF4371_POWER_DOWN),
	_ADF4371_EXT_INFO("name", ADF4371_CHANNEL_NAME),
	अणु पूर्ण,
पूर्ण;

#घोषणा ADF4371_CHANNEL(index) अणु \
		.type = IIO_ALTVOLTAGE, \
		.output = 1, \
		.channel = index, \
		.ext_info = adf4371_ext_info, \
		.indexed = 1, \
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adf4371_chan[] = अणु
	ADF4371_CHANNEL(ADF4371_CH_RF8),
	ADF4371_CHANNEL(ADF4371_CH_RFAUX8),
	ADF4371_CHANNEL(ADF4371_CH_RF16),
	ADF4371_CHANNEL(ADF4371_CH_RF32),
पूर्ण;

अटल स्थिर काष्ठा adf4371_chip_info adf4371_chip_info[] = अणु
	[ADF4371] = अणु
		.channels = adf4371_chan,
		.num_channels = 4,
	पूर्ण,
	[ADF4372] = अणु
		.channels = adf4371_chan,
		.num_channels = 3,
	पूर्ण
पूर्ण;

अटल पूर्णांक adf4371_reg_access(काष्ठा iio_dev *indio_dev,
			      अचिन्हित पूर्णांक reg,
			      अचिन्हित पूर्णांक ग_लिखोval,
			      अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा adf4371_state *st = iio_priv(indio_dev);

	अगर (पढ़ोval)
		वापस regmap_पढ़ो(st->regmap, reg, पढ़ोval);
	अन्यथा
		वापस regmap_ग_लिखो(st->regmap, reg, ग_लिखोval);
पूर्ण

अटल स्थिर काष्ठा iio_info adf4371_info = अणु
	.debugfs_reg_access = &adf4371_reg_access,
पूर्ण;

अटल पूर्णांक adf4371_setup(काष्ठा adf4371_state *st)
अणु
	अचिन्हित पूर्णांक synth_समयout = 2, समयout = 1, vco_alc_समयout = 1;
	अचिन्हित पूर्णांक vco_band_भाग, पंचांगp;
	पूर्णांक ret;

	/* Perक्रमm a software reset */
	ret = regmap_ग_लिखो(st->regmap, ADF4371_REG(0x0), ADF4371_RESET_CMD);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_multi_reg_ग_लिखो(st->regmap, adf4371_reg_शेषs,
				     ARRAY_SIZE(adf4371_reg_शेषs));
	अगर (ret < 0)
		वापस ret;

	/* Mute to Lock Detect */
	अगर (device_property_पढ़ो_bool(&st->spi->dev, "adi,mute-till-lock-en")) अणु
		ret = regmap_update_bits(st->regmap, ADF4371_REG(0x25),
					 ADF4371_MUTE_LD_MSK,
					 ADF4371_MUTE_LD(1));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Set address in ascending order, so the bulk_ग_लिखो() will work */
	ret = regmap_update_bits(st->regmap, ADF4371_REG(0x0),
				 ADF4371_ADDR_ASC_MSK | ADF4371_ADDR_ASC_R_MSK,
				 ADF4371_ADDR_ASC(1) | ADF4371_ADDR_ASC_R(1));
	अगर (ret < 0)
		वापस ret;
	/*
	 * Calculate and maximize PFD frequency
	 * fPFD = REFIN थ ((1 + D)/(R थ (1 + T)))
	 * Where D is the REFIN द्विगुनr bit, T is the reference भागide by 2,
	 * R is the reference भागision factor
	 * TODO: it is assumed D and T equal 0.
	 */
	करो अणु
		st->ref_भाग_factor++;
		st->fpfd = st->clkin_freq / st->ref_भाग_factor;
	पूर्ण जबतक (st->fpfd > ADF4371_MAX_FREQ_PFD);

	/* Calculate Timeouts */
	vco_band_भाग = DIV_ROUND_UP(st->fpfd, 2400000U);

	पंचांगp = DIV_ROUND_CLOSEST(st->fpfd, 1000000U);
	करो अणु
		समयout++;
		अगर (समयout > 1023) अणु
			समयout = 2;
			synth_समयout++;
		पूर्ण
	पूर्ण जबतक (synth_समयout * 1024 + समयout <= 20 * पंचांगp);

	करो अणु
		vco_alc_समयout++;
	पूर्ण जबतक (vco_alc_समयout * 1024 - समयout <= 50 * पंचांगp);

	st->buf[0] = vco_band_भाग;
	st->buf[1] = समयout & 0xFF;
	st->buf[2] = ADF4371_TIMEOUT(समयout >> 8) | 0x04;
	st->buf[3] = synth_समयout;
	st->buf[4] = ADF4371_VCO_ALC_TOUT(vco_alc_समयout);

	वापस regmap_bulk_ग_लिखो(st->regmap, ADF4371_REG(0x30), st->buf, 5);
पूर्ण

अटल व्योम adf4371_clk_disable(व्योम *data)
अणु
	काष्ठा adf4371_state *st = data;

	clk_disable_unprepare(st->clkin);
पूर्ण

अटल पूर्णांक adf4371_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा iio_dev *indio_dev;
	काष्ठा adf4371_state *st;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	regmap = devm_regmap_init_spi(spi, &adf4371_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "Error initializing spi regmap: %ld\n",
			PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);
	st->spi = spi;
	st->regmap = regmap;
	mutex_init(&st->lock);

	st->chip_info = &adf4371_chip_info[id->driver_data];
	indio_dev->name = id->name;
	indio_dev->info = &adf4371_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;

	st->clkin = devm_clk_get(&spi->dev, "clkin");
	अगर (IS_ERR(st->clkin))
		वापस PTR_ERR(st->clkin);

	ret = clk_prepare_enable(st->clkin);
	अगर (ret < 0)
		वापस ret;

	ret = devm_add_action_or_reset(&spi->dev, adf4371_clk_disable, st);
	अगर (ret)
		वापस ret;

	st->clkin_freq = clk_get_rate(st->clkin);

	ret = adf4371_setup(st);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "ADF4371 setup failed\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id adf4371_id_table[] = अणु
	अणु "adf4371", ADF4371 पूर्ण,
	अणु "adf4372", ADF4372 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adf4371_id_table);

अटल स्थिर काष्ठा of_device_id adf4371_of_match[] = अणु
	अणु .compatible = "adi,adf4371" पूर्ण,
	अणु .compatible = "adi,adf4372" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adf4371_of_match);

अटल काष्ठा spi_driver adf4371_driver = अणु
	.driver = अणु
		.name = "adf4371",
		.of_match_table = adf4371_of_match,
	पूर्ण,
	.probe = adf4371_probe,
	.id_table = adf4371_id_table,
पूर्ण;
module_spi_driver(adf4371_driver);

MODULE_AUTHOR("Stefan Popa <stefan.popa@analog.com>");
MODULE_DESCRIPTION("Analog Devices ADF4371 SPI PLL");
MODULE_LICENSE("GPL");
