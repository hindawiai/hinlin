<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADF4350/ADF4351 SPI Wideband Synthesizer driver
 *
 * Copyright 2012-2013 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/gcd.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/frequency/adf4350.h>

क्रमागत अणु
	ADF4350_FREQ,
	ADF4350_FREQ_REFIN,
	ADF4350_FREQ_RESOLUTION,
	ADF4350_PWRDOWN,
पूर्ण;

काष्ठा adf4350_state अणु
	काष्ठा spi_device		*spi;
	काष्ठा regulator		*reg;
	काष्ठा gpio_desc		*lock_detect_gpiod;
	काष्ठा adf4350_platक्रमm_data	*pdata;
	काष्ठा clk			*clk;
	अचिन्हित दीर्घ			clkin;
	अचिन्हित दीर्घ			chspc; /* Channel Spacing */
	अचिन्हित दीर्घ			fpfd; /* Phase Frequency Detector */
	अचिन्हित दीर्घ			min_out_freq;
	अचिन्हित			r0_fract;
	अचिन्हित			r0_पूर्णांक;
	अचिन्हित			r1_mod;
	अचिन्हित			r4_rf_भाग_sel;
	अचिन्हित दीर्घ			regs[6];
	अचिन्हित दीर्घ			regs_hw[6];
	अचिन्हित दीर्घ दीर्घ		freq_req;
	/*
	 * Lock to protect the state of the device from potential concurrent
	 * ग_लिखोs. The device is configured via a sequence of SPI ग_लिखोs,
	 * and this lock is meant to prevent the start of another sequence
	 * beक्रमe another one has finished.
	 */
	काष्ठा mutex			lock;
	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	__be32				val ____cacheline_aligned;
पूर्ण;

अटल काष्ठा adf4350_platक्रमm_data शेष_pdata = अणु
	.channel_spacing = 10000,
	.r2_user_settings = ADF4350_REG2_PD_POLARITY_POS |
			    ADF4350_REG2_CHARGE_PUMP_CURR_uA(2500),
	.r3_user_settings = ADF4350_REG3_12BIT_CLKDIV_MODE(0),
	.r4_user_settings = ADF4350_REG4_OUTPUT_PWR(3) |
			    ADF4350_REG4_MUTE_TILL_LOCK_EN,
पूर्ण;

अटल पूर्णांक adf4350_sync_config(काष्ठा adf4350_state *st)
अणु
	पूर्णांक ret, i, द्विगुनbuf = 0;

	क्रम (i = ADF4350_REG5; i >= ADF4350_REG0; i--) अणु
		अगर ((st->regs_hw[i] != st->regs[i]) ||
			((i == ADF4350_REG0) && द्विगुनbuf)) अणु
			चयन (i) अणु
			हाल ADF4350_REG1:
			हाल ADF4350_REG4:
				द्विगुनbuf = 1;
				अवरोध;
			पूर्ण

			st->val  = cpu_to_be32(st->regs[i] | i);
			ret = spi_ग_लिखो(st->spi, &st->val, 4);
			अगर (ret < 0)
				वापस ret;
			st->regs_hw[i] = st->regs[i];
			dev_dbg(&st->spi->dev, "[%d] 0x%X\n",
				i, (u32)st->regs[i] | i);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adf4350_reg_access(काष्ठा iio_dev *indio_dev,
			      अचिन्हित reg, अचिन्हित ग_लिखोval,
			      अचिन्हित *पढ़ोval)
अणु
	काष्ठा adf4350_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (reg > ADF4350_REG5)
		वापस -EINVAL;

	mutex_lock(&st->lock);
	अगर (पढ़ोval == शून्य) अणु
		st->regs[reg] = ग_लिखोval & ~(BIT(0) | BIT(1) | BIT(2));
		ret = adf4350_sync_config(st);
	पूर्ण अन्यथा अणु
		*पढ़ोval =  st->regs_hw[reg];
		ret = 0;
	पूर्ण
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक adf4350_tune_r_cnt(काष्ठा adf4350_state *st, अचिन्हित लघु r_cnt)
अणु
	काष्ठा adf4350_platक्रमm_data *pdata = st->pdata;

	करो अणु
		r_cnt++;
		st->fpfd = (st->clkin * (pdata->ref_द्विगुनr_en ? 2 : 1)) /
			   (r_cnt * (pdata->ref_भाग2_en ? 2 : 1));
	पूर्ण जबतक (st->fpfd > ADF4350_MAX_FREQ_PFD);

	वापस r_cnt;
पूर्ण

अटल पूर्णांक adf4350_set_freq(काष्ठा adf4350_state *st, अचिन्हित दीर्घ दीर्घ freq)
अणु
	काष्ठा adf4350_platक्रमm_data *pdata = st->pdata;
	u64 पंचांगp;
	u32 भाग_gcd, prescaler, chspc;
	u16 mभाग, r_cnt = 0;
	u8 band_sel_भाग;

	अगर (freq > ADF4350_MAX_OUT_FREQ || freq < st->min_out_freq)
		वापस -EINVAL;

	अगर (freq > ADF4350_MAX_FREQ_45_PRESC) अणु
		prescaler = ADF4350_REG1_PRESCALER;
		mभाग = 75;
	पूर्ण अन्यथा अणु
		prescaler = 0;
		mभाग = 23;
	पूर्ण

	st->r4_rf_भाग_sel = 0;

	जबतक (freq < ADF4350_MIN_VCO_FREQ) अणु
		freq <<= 1;
		st->r4_rf_भाग_sel++;
	पूर्ण

	/*
	 * Allow a predefined reference भागision factor
	 * अगर not set, compute our own
	 */
	अगर (pdata->ref_भाग_factor)
		r_cnt = pdata->ref_भाग_factor - 1;

	chspc = st->chspc;

	करो  अणु
		करो अणु
			करो अणु
				r_cnt = adf4350_tune_r_cnt(st, r_cnt);
				st->r1_mod = st->fpfd / chspc;
				अगर (r_cnt > ADF4350_MAX_R_CNT) अणु
					/* try higher spacing values */
					chspc++;
					r_cnt = 0;
				पूर्ण
			पूर्ण जबतक ((st->r1_mod > ADF4350_MAX_MODULUS) && r_cnt);
		पूर्ण जबतक (r_cnt == 0);

		पंचांगp = freq * (u64)st->r1_mod + (st->fpfd >> 1);
		करो_भाग(पंचांगp, st->fpfd); /* Div round बंदst (n + d/2)/d */
		st->r0_fract = करो_भाग(पंचांगp, st->r1_mod);
		st->r0_पूर्णांक = पंचांगp;
	पूर्ण जबतक (mभाग > st->r0_पूर्णांक);

	band_sel_भाग = DIV_ROUND_UP(st->fpfd, ADF4350_MAX_BANDSEL_CLK);

	अगर (st->r0_fract && st->r1_mod) अणु
		भाग_gcd = gcd(st->r1_mod, st->r0_fract);
		st->r1_mod /= भाग_gcd;
		st->r0_fract /= भाग_gcd;
	पूर्ण अन्यथा अणु
		st->r0_fract = 0;
		st->r1_mod = 1;
	पूर्ण

	dev_dbg(&st->spi->dev, "VCO: %llu Hz, PFD %lu Hz\n"
		"REF_DIV %d, R0_INT %d, R0_FRACT %d\n"
		"R1_MOD %d, RF_DIV %d\nPRESCALER %s, BAND_SEL_DIV %d\n",
		freq, st->fpfd, r_cnt, st->r0_पूर्णांक, st->r0_fract, st->r1_mod,
		1 << st->r4_rf_भाग_sel, prescaler ? "8/9" : "4/5",
		band_sel_भाग);

	st->regs[ADF4350_REG0] = ADF4350_REG0_INT(st->r0_पूर्णांक) |
				 ADF4350_REG0_FRACT(st->r0_fract);

	st->regs[ADF4350_REG1] = ADF4350_REG1_PHASE(1) |
				 ADF4350_REG1_MOD(st->r1_mod) |
				 prescaler;

	st->regs[ADF4350_REG2] =
		ADF4350_REG2_10BIT_R_CNT(r_cnt) |
		ADF4350_REG2_DOUBLE_BUFF_EN |
		(pdata->ref_द्विगुनr_en ? ADF4350_REG2_RMULT2_EN : 0) |
		(pdata->ref_भाग2_en ? ADF4350_REG2_RDIV2_EN : 0) |
		(pdata->r2_user_settings & (ADF4350_REG2_PD_POLARITY_POS |
		ADF4350_REG2_LDP_6ns | ADF4350_REG2_LDF_INT_N |
		ADF4350_REG2_CHARGE_PUMP_CURR_uA(5000) |
		ADF4350_REG2_MUXOUT(0x7) | ADF4350_REG2_NOISE_MODE(0x3)));

	st->regs[ADF4350_REG3] = pdata->r3_user_settings &
				 (ADF4350_REG3_12BIT_CLKDIV(0xFFF) |
				 ADF4350_REG3_12BIT_CLKDIV_MODE(0x3) |
				 ADF4350_REG3_12BIT_CSR_EN |
				 ADF4351_REG3_CHARGE_CANCELLATION_EN |
				 ADF4351_REG3_ANTI_BACKLASH_3ns_EN |
				 ADF4351_REG3_BAND_SEL_CLOCK_MODE_HIGH);

	st->regs[ADF4350_REG4] =
		ADF4350_REG4_FEEDBACK_FUND |
		ADF4350_REG4_RF_DIV_SEL(st->r4_rf_भाग_sel) |
		ADF4350_REG4_8BIT_BAND_SEL_CLKDIV(band_sel_भाग) |
		ADF4350_REG4_RF_OUT_EN |
		(pdata->r4_user_settings &
		(ADF4350_REG4_OUTPUT_PWR(0x3) |
		ADF4350_REG4_AUX_OUTPUT_PWR(0x3) |
		ADF4350_REG4_AUX_OUTPUT_EN |
		ADF4350_REG4_AUX_OUTPUT_FUND |
		ADF4350_REG4_MUTE_TILL_LOCK_EN));

	st->regs[ADF4350_REG5] = ADF4350_REG5_LD_PIN_MODE_DIGITAL;
	st->freq_req = freq;

	वापस adf4350_sync_config(st);
पूर्ण

अटल sमाप_प्रकार adf4350_ग_लिखो(काष्ठा iio_dev *indio_dev,
				    uपूर्णांकptr_t निजी,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा adf4350_state *st = iio_priv(indio_dev);
	अचिन्हित दीर्घ दीर्घ पढ़ोin;
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret;

	ret = kम_से_अदीर्घl(buf, 10, &पढ़ोin);
	अगर (ret)
		वापस ret;

	mutex_lock(&st->lock);
	चयन ((u32)निजी) अणु
	हाल ADF4350_FREQ:
		ret = adf4350_set_freq(st, पढ़ोin);
		अवरोध;
	हाल ADF4350_FREQ_REFIN:
		अगर (पढ़ोin > ADF4350_MAX_FREQ_REFIN) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (st->clk) अणु
			पंचांगp = clk_round_rate(st->clk, पढ़ोin);
			अगर (पंचांगp != पढ़ोin) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			ret = clk_set_rate(st->clk, पंचांगp);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
		st->clkin = पढ़ोin;
		ret = adf4350_set_freq(st, st->freq_req);
		अवरोध;
	हाल ADF4350_FREQ_RESOLUTION:
		अगर (पढ़ोin == 0)
			ret = -EINVAL;
		अन्यथा
			st->chspc = पढ़ोin;
		अवरोध;
	हाल ADF4350_PWRDOWN:
		अगर (पढ़ोin)
			st->regs[ADF4350_REG2] |= ADF4350_REG2_POWER_DOWN_EN;
		अन्यथा
			st->regs[ADF4350_REG2] &= ~ADF4350_REG2_POWER_DOWN_EN;

		adf4350_sync_config(st);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&st->lock);

	वापस ret ? ret : len;
पूर्ण

अटल sमाप_प्रकार adf4350_पढ़ो(काष्ठा iio_dev *indio_dev,
				   uपूर्णांकptr_t निजी,
				   स्थिर काष्ठा iio_chan_spec *chan,
				   अक्षर *buf)
अणु
	काष्ठा adf4350_state *st = iio_priv(indio_dev);
	अचिन्हित दीर्घ दीर्घ val;
	पूर्णांक ret = 0;

	mutex_lock(&st->lock);
	चयन ((u32)निजी) अणु
	हाल ADF4350_FREQ:
		val = (u64)((st->r0_पूर्णांक * st->r1_mod) + st->r0_fract) *
			(u64)st->fpfd;
		करो_भाग(val, st->r1_mod * (1 << st->r4_rf_भाग_sel));
		/* PLL unlocked? वापस error */
		अगर (st->lock_detect_gpiod)
			अगर (!gpiod_get_value(st->lock_detect_gpiod)) अणु
				dev_dbg(&st->spi->dev, "PLL un-locked\n");
				ret = -EBUSY;
			पूर्ण
		अवरोध;
	हाल ADF4350_FREQ_REFIN:
		अगर (st->clk)
			st->clkin = clk_get_rate(st->clk);

		val = st->clkin;
		अवरोध;
	हाल ADF4350_FREQ_RESOLUTION:
		val = st->chspc;
		अवरोध;
	हाल ADF4350_PWRDOWN:
		val = !!(st->regs[ADF4350_REG2] & ADF4350_REG2_POWER_DOWN_EN);
		अवरोध;
	शेष:
		ret = -EINVAL;
		val = 0;
	पूर्ण
	mutex_unlock(&st->lock);

	वापस ret < 0 ? ret : प्र_लिखो(buf, "%llu\n", val);
पूर्ण

#घोषणा _ADF4350_EXT_INFO(_name, _ident) अणु \
	.name = _name, \
	.पढ़ो = adf4350_पढ़ो, \
	.ग_लिखो = adf4350_ग_लिखो, \
	.निजी = _ident, \
	.shared = IIO_SEPARATE, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info adf4350_ext_info[] = अणु
	/* Ideally we use IIO_CHAN_INFO_FREQUENCY, but there are
	 * values > 2^32 in order to support the entire frequency range
	 * in Hz. Using scale is a bit ugly.
	 */
	_ADF4350_EXT_INFO("frequency", ADF4350_FREQ),
	_ADF4350_EXT_INFO("frequency_resolution", ADF4350_FREQ_RESOLUTION),
	_ADF4350_EXT_INFO("refin_frequency", ADF4350_FREQ_REFIN),
	_ADF4350_EXT_INFO("powerdown", ADF4350_PWRDOWN),
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adf4350_chan = अणु
	.type = IIO_ALTVOLTAGE,
	.indexed = 1,
	.output = 1,
	.ext_info = adf4350_ext_info,
पूर्ण;

अटल स्थिर काष्ठा iio_info adf4350_info = अणु
	.debugfs_reg_access = &adf4350_reg_access,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल काष्ठा adf4350_platक्रमm_data *adf4350_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा adf4350_platक्रमm_data *pdata;
	अचिन्हित पूर्णांक पंचांगp;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	snम_लिखो(&pdata->name[0], SPI_NAME_SIZE - 1, "%pOFn", np);

	पंचांगp = 10000;
	of_property_पढ़ो_u32(np, "adi,channel-spacing", &पंचांगp);
	pdata->channel_spacing = पंचांगp;

	पंचांगp = 0;
	of_property_पढ़ो_u32(np, "adi,power-up-frequency", &पंचांगp);
	pdata->घातer_up_frequency = पंचांगp;

	पंचांगp = 0;
	of_property_पढ़ो_u32(np, "adi,reference-div-factor", &पंचांगp);
	pdata->ref_भाग_factor = पंचांगp;

	pdata->ref_द्विगुनr_en = of_property_पढ़ो_bool(np,
			"adi,reference-doubler-enable");
	pdata->ref_भाग2_en = of_property_पढ़ो_bool(np,
			"adi,reference-div2-enable");

	/* r2_user_settings */
	pdata->r2_user_settings = of_property_पढ़ो_bool(np,
			"adi,phase-detector-polarity-positive-enable") ?
			ADF4350_REG2_PD_POLARITY_POS : 0;
	pdata->r2_user_settings |= of_property_पढ़ो_bool(np,
			"adi,lock-detect-precision-6ns-enable") ?
			ADF4350_REG2_LDP_6ns : 0;
	pdata->r2_user_settings |= of_property_पढ़ो_bool(np,
			"adi,lock-detect-function-integer-n-enable") ?
			ADF4350_REG2_LDF_INT_N : 0;

	पंचांगp = 2500;
	of_property_पढ़ो_u32(np, "adi,charge-pump-current", &पंचांगp);
	pdata->r2_user_settings |= ADF4350_REG2_CHARGE_PUMP_CURR_uA(पंचांगp);

	पंचांगp = 0;
	of_property_पढ़ो_u32(np, "adi,muxout-select", &पंचांगp);
	pdata->r2_user_settings |= ADF4350_REG2_MUXOUT(पंचांगp);

	pdata->r2_user_settings |= of_property_पढ़ो_bool(np,
			"adi,low-spur-mode-enable") ?
			ADF4350_REG2_NOISE_MODE(0x3) : 0;

	/* r3_user_settings */

	pdata->r3_user_settings = of_property_पढ़ो_bool(np,
			"adi,cycle-slip-reduction-enable") ?
			ADF4350_REG3_12BIT_CSR_EN : 0;
	pdata->r3_user_settings |= of_property_पढ़ो_bool(np,
			"adi,charge-cancellation-enable") ?
			ADF4351_REG3_CHARGE_CANCELLATION_EN : 0;

	pdata->r3_user_settings |= of_property_पढ़ो_bool(np,
			"adi,anti-backlash-3ns-enable") ?
			ADF4351_REG3_ANTI_BACKLASH_3ns_EN : 0;
	pdata->r3_user_settings |= of_property_पढ़ो_bool(np,
			"adi,band-select-clock-mode-high-enable") ?
			ADF4351_REG3_BAND_SEL_CLOCK_MODE_HIGH : 0;

	पंचांगp = 0;
	of_property_पढ़ो_u32(np, "adi,12bit-clk-divider", &पंचांगp);
	pdata->r3_user_settings |= ADF4350_REG3_12BIT_CLKDIV(पंचांगp);

	पंचांगp = 0;
	of_property_पढ़ो_u32(np, "adi,clk-divider-mode", &पंचांगp);
	pdata->r3_user_settings |= ADF4350_REG3_12BIT_CLKDIV_MODE(पंचांगp);

	/* r4_user_settings */

	pdata->r4_user_settings = of_property_पढ़ो_bool(np,
			"adi,aux-output-enable") ?
			ADF4350_REG4_AUX_OUTPUT_EN : 0;
	pdata->r4_user_settings |= of_property_पढ़ो_bool(np,
			"adi,aux-output-fundamental-enable") ?
			ADF4350_REG4_AUX_OUTPUT_FUND : 0;
	pdata->r4_user_settings |= of_property_पढ़ो_bool(np,
			"adi,mute-till-lock-enable") ?
			ADF4350_REG4_MUTE_TILL_LOCK_EN : 0;

	पंचांगp = 0;
	of_property_पढ़ो_u32(np, "adi,output-power", &पंचांगp);
	pdata->r4_user_settings |= ADF4350_REG4_OUTPUT_PWR(पंचांगp);

	पंचांगp = 0;
	of_property_पढ़ो_u32(np, "adi,aux-output-power", &पंचांगp);
	pdata->r4_user_settings |= ADF4350_REG4_AUX_OUTPUT_PWR(पंचांगp);

	वापस pdata;
पूर्ण
#अन्यथा
अटल
काष्ठा adf4350_platक्रमm_data *adf4350_parse_dt(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक adf4350_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा adf4350_platक्रमm_data *pdata;
	काष्ठा iio_dev *indio_dev;
	काष्ठा adf4350_state *st;
	काष्ठा clk *clk = शून्य;
	पूर्णांक ret;

	अगर (spi->dev.of_node) अणु
		pdata = adf4350_parse_dt(&spi->dev);
		अगर (pdata == शून्य)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		pdata = spi->dev.platक्रमm_data;
	पूर्ण

	अगर (!pdata) अणु
		dev_warn(&spi->dev, "no platform data? using default\n");
		pdata = &शेष_pdata;
	पूर्ण

	अगर (!pdata->clkin) अणु
		clk = devm_clk_get(&spi->dev, "clkin");
		अगर (IS_ERR(clk))
			वापस -EPROBE_DEFER;

		ret = clk_prepare_enable(clk);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य) अणु
		ret =  -ENOMEM;
		जाओ error_disable_clk;
	पूर्ण

	st = iio_priv(indio_dev);

	st->reg = devm_regulator_get(&spi->dev, "vcc");
	अगर (!IS_ERR(st->reg)) अणु
		ret = regulator_enable(st->reg);
		अगर (ret)
			जाओ error_disable_clk;
	पूर्ण

	spi_set_drvdata(spi, indio_dev);
	st->spi = spi;
	st->pdata = pdata;

	indio_dev->name = (pdata->name[0] != 0) ? pdata->name :
		spi_get_device_id(spi)->name;

	indio_dev->info = &adf4350_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = &adf4350_chan;
	indio_dev->num_channels = 1;

	mutex_init(&st->lock);

	st->chspc = pdata->channel_spacing;
	अगर (clk) अणु
		st->clk = clk;
		st->clkin = clk_get_rate(clk);
	पूर्ण अन्यथा अणु
		st->clkin = pdata->clkin;
	पूर्ण

	st->min_out_freq = spi_get_device_id(spi)->driver_data == 4351 ?
		ADF4351_MIN_OUT_FREQ : ADF4350_MIN_OUT_FREQ;

	स_रखो(st->regs_hw, 0xFF, माप(st->regs_hw));

	st->lock_detect_gpiod = devm_gpiod_get_optional(&spi->dev, शून्य,
							GPIOD_IN);
	अगर (IS_ERR(st->lock_detect_gpiod))
		वापस PTR_ERR(st->lock_detect_gpiod);

	अगर (pdata->घातer_up_frequency) अणु
		ret = adf4350_set_freq(st, pdata->घातer_up_frequency);
		अगर (ret)
			जाओ error_disable_reg;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_disable_reg;

	वापस 0;

error_disable_reg:
	अगर (!IS_ERR(st->reg))
		regulator_disable(st->reg);
error_disable_clk:
	clk_disable_unprepare(clk);

	वापस ret;
पूर्ण

अटल पूर्णांक adf4350_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा adf4350_state *st = iio_priv(indio_dev);
	काष्ठा regulator *reg = st->reg;

	st->regs[ADF4350_REG2] |= ADF4350_REG2_POWER_DOWN_EN;
	adf4350_sync_config(st);

	iio_device_unरेजिस्टर(indio_dev);

	clk_disable_unprepare(st->clk);

	अगर (!IS_ERR(reg))
		regulator_disable(reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id adf4350_of_match[] = अणु
	अणु .compatible = "adi,adf4350", पूर्ण,
	अणु .compatible = "adi,adf4351", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adf4350_of_match);

अटल स्थिर काष्ठा spi_device_id adf4350_id[] = अणु
	अणु"adf4350", 4350पूर्ण,
	अणु"adf4351", 4351पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adf4350_id);

अटल काष्ठा spi_driver adf4350_driver = अणु
	.driver = अणु
		.name	= "adf4350",
		.of_match_table = of_match_ptr(adf4350_of_match),
	पूर्ण,
	.probe		= adf4350_probe,
	.हटाओ		= adf4350_हटाओ,
	.id_table	= adf4350_id,
पूर्ण;
module_spi_driver(adf4350_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices ADF4350/ADF4351 PLL");
MODULE_LICENSE("GPL v2");
