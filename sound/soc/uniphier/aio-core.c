<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Socionext UniPhier AIO ALSA common driver.
//
// Copyright (c) 2016-2018 Socionext Inc.

#समावेश <linux/bitfield.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "aio.h"
#समावेश "aio-reg.h"

अटल u64 rb_cnt(u64 wr, u64 rd, u64 len)
अणु
	अगर (rd <= wr)
		वापस wr - rd;
	अन्यथा
		वापस len - (rd - wr);
पूर्ण

अटल u64 rb_cnt_to_end(u64 wr, u64 rd, u64 len)
अणु
	अगर (rd <= wr)
		वापस wr - rd;
	अन्यथा
		वापस len - rd;
पूर्ण

अटल u64 rb_space(u64 wr, u64 rd, u64 len)
अणु
	अगर (rd <= wr)
		वापस len - (wr - rd) - 8;
	अन्यथा
		वापस rd - wr - 8;
पूर्ण

अटल u64 rb_space_to_end(u64 wr, u64 rd, u64 len)
अणु
	अगर (rd > wr)
		वापस rd - wr - 8;
	अन्यथा अगर (rd > 0)
		वापस len - wr;
	अन्यथा
		वापस len - wr - 8;
पूर्ण

u64 aio_rb_cnt(काष्ठा uniphier_aio_sub *sub)
अणु
	वापस rb_cnt(sub->wr_offs, sub->rd_offs, sub->compr_bytes);
पूर्ण

u64 aio_rbt_cnt_to_end(काष्ठा uniphier_aio_sub *sub)
अणु
	वापस rb_cnt_to_end(sub->wr_offs, sub->rd_offs, sub->compr_bytes);
पूर्ण

u64 aio_rb_space(काष्ठा uniphier_aio_sub *sub)
अणु
	वापस rb_space(sub->wr_offs, sub->rd_offs, sub->compr_bytes);
पूर्ण

u64 aio_rb_space_to_end(काष्ठा uniphier_aio_sub *sub)
अणु
	वापस rb_space_to_end(sub->wr_offs, sub->rd_offs, sub->compr_bytes);
पूर्ण

/**
 * aio_iecout_set_enable - setup IEC output via SoC glue
 * @chip: the AIO chip poपूर्णांकer
 * @enable: false to stop the output, true to start
 *
 * Set enabled or disabled S/PDIF संकेत output to out of SoC via AOnIEC pins.
 * This function need to call at driver startup.
 *
 * The regmap of SoC glue is specअगरied by 'socionext,syscon' optional property
 * of DT. This function has no effect अगर no property.
 */
व्योम aio_iecout_set_enable(काष्ठा uniphier_aio_chip *chip, bool enable)
अणु
	काष्ठा regmap *r = chip->regmap_sg;

	अगर (!r)
		वापस;

	regmap_ग_लिखो(r, SG_AOUTEN, (enable) ? ~0 : 0);
पूर्ण

/**
 * aio_chip_set_pll - set frequency to audio PLL
 * @chip: the AIO chip poपूर्णांकer
 * @pll_id: PLL
 * @freq: frequency in Hz, 0 is ignored
 *
 * Sets frequency of audio PLL. This function can be called anyसमय,
 * but it takes समय till PLL is locked.
 *
 * Return: Zero अगर successful, otherwise a negative value on error.
 */
पूर्णांक aio_chip_set_pll(काष्ठा uniphier_aio_chip *chip, पूर्णांक pll_id,
		     अचिन्हित पूर्णांक freq)
अणु
	काष्ठा device *dev = &chip->pdev->dev;
	काष्ठा regmap *r = chip->regmap;
	पूर्णांक shअगरt;
	u32 v;

	/* Not change */
	अगर (freq == 0)
		वापस 0;

	चयन (pll_id) अणु
	हाल AUD_PLL_A1:
		shअगरt = 0;
		अवरोध;
	हाल AUD_PLL_F1:
		shअगरt = 1;
		अवरोध;
	हाल AUD_PLL_A2:
		shअगरt = 2;
		अवरोध;
	हाल AUD_PLL_F2:
		shअगरt = 3;
		अवरोध;
	शेष:
		dev_err(dev, "PLL(%d) not supported\n", pll_id);
		वापस -EINVAL;
	पूर्ण

	चयन (freq) अणु
	हाल 36864000:
		v = A2APLLCTR1_APLLX_36MHZ;
		अवरोध;
	हाल 33868800:
		v = A2APLLCTR1_APLLX_33MHZ;
		अवरोध;
	शेष:
		dev_err(dev, "PLL frequency not supported(%d)\n", freq);
		वापस -EINVAL;
	पूर्ण
	chip->plls[pll_id].freq = freq;

	regmap_update_bits(r, A2APLLCTR1, A2APLLCTR1_APLLX_MASK << shअगरt,
			   v << shअगरt);

	वापस 0;
पूर्ण

/**
 * aio_chip_init - initialize AIO whole settings
 * @chip: the AIO chip poपूर्णांकer
 *
 * Sets AIO fixed and whole device settings to AIO.
 * This function need to call once at driver startup.
 *
 * The रेजिस्टर area that is changed by this function is shared by all
 * modules of AIO. But there is not race condition since this function
 * has always set the same initialize values.
 */
व्योम aio_chip_init(काष्ठा uniphier_aio_chip *chip)
अणु
	काष्ठा regmap *r = chip->regmap;

	regmap_update_bits(r, A2APLLCTR0,
			   A2APLLCTR0_APLLXPOW_MASK,
			   A2APLLCTR0_APLLXPOW_PWON);

	regmap_update_bits(r, A2EXMCLKSEL0,
			   A2EXMCLKSEL0_EXMCLK_MASK,
			   A2EXMCLKSEL0_EXMCLK_OUTPUT);

	regmap_update_bits(r, A2AIOINPUTSEL, A2AIOINPUTSEL_RXSEL_MASK,
			   A2AIOINPUTSEL_RXSEL_PCMI1_HDMIRX1 |
			   A2AIOINPUTSEL_RXSEL_PCMI2_SIF |
			   A2AIOINPUTSEL_RXSEL_PCMI3_EVEA |
			   A2AIOINPUTSEL_RXSEL_IECI1_HDMIRX1);

	अगर (chip->chip_spec->addr_ext)
		regmap_update_bits(r, CDA2D_TEST, CDA2D_TEST_DDR_MODE_MASK,
				   CDA2D_TEST_DDR_MODE_EXTON0);
	अन्यथा
		regmap_update_bits(r, CDA2D_TEST, CDA2D_TEST_DDR_MODE_MASK,
				   CDA2D_TEST_DDR_MODE_EXTOFF1);
पूर्ण

/**
 * aio_init - initialize AIO substream
 * @sub: the AIO substream poपूर्णांकer
 *
 * Sets fixed settings of each AIO substreams.
 * This function need to call once at substream startup.
 *
 * Return: Zero अगर successful, otherwise a negative value on error.
 */
पूर्णांक aio_init(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा device *dev = &sub->aio->chip->pdev->dev;
	काष्ठा regmap *r = sub->aio->chip->regmap;

	regmap_ग_लिखो(r, A2RBNMAPCTR0(sub->swm->rb.hw),
		     MAPCTR0_EN | sub->swm->rb.map);
	regmap_ग_लिखो(r, A2CHNMAPCTR0(sub->swm->ch.hw),
		     MAPCTR0_EN | sub->swm->ch.map);

	चयन (sub->swm->type) अणु
	हाल PORT_TYPE_I2S:
	हाल PORT_TYPE_SPDIF:
	हाल PORT_TYPE_EVE:
		अगर (sub->swm->dir == PORT_सूची_INPUT) अणु
			regmap_ग_लिखो(r, A2IIFNMAPCTR0(sub->swm->iअगर.hw),
				     MAPCTR0_EN | sub->swm->iअगर.map);
			regmap_ग_लिखो(r, A2IPORTNMAPCTR0(sub->swm->iport.hw),
				     MAPCTR0_EN | sub->swm->iport.map);
		पूर्ण अन्यथा अणु
			regmap_ग_लिखो(r, A2OIFNMAPCTR0(sub->swm->oअगर.hw),
				     MAPCTR0_EN | sub->swm->oअगर.map);
			regmap_ग_लिखो(r, A2OPORTNMAPCTR0(sub->swm->oport.hw),
				     MAPCTR0_EN | sub->swm->oport.map);
		पूर्ण
		अवरोध;
	हाल PORT_TYPE_CONV:
		regmap_ग_लिखो(r, A2OIFNMAPCTR0(sub->swm->oअगर.hw),
			     MAPCTR0_EN | sub->swm->oअगर.map);
		regmap_ग_लिखो(r, A2OPORTNMAPCTR0(sub->swm->oport.hw),
			     MAPCTR0_EN | sub->swm->oport.map);
		regmap_ग_लिखो(r, A2CHNMAPCTR0(sub->swm->och.hw),
			     MAPCTR0_EN | sub->swm->och.map);
		regmap_ग_लिखो(r, A2IIFNMAPCTR0(sub->swm->iअगर.hw),
			     MAPCTR0_EN | sub->swm->iअगर.map);
		अवरोध;
	शेष:
		dev_err(dev, "Unknown port type %d.\n", sub->swm->type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * aio_port_reset - reset AIO port block
 * @sub: the AIO substream poपूर्णांकer
 *
 * Resets the digital संकेत input/output port block of AIO.
 */
व्योम aio_port_reset(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;

	अगर (sub->swm->dir == PORT_सूची_OUTPUT) अणु
		regmap_ग_लिखो(r, AOUTRSTCTR0, BIT(sub->swm->oport.map));
		regmap_ग_लिखो(r, AOUTRSTCTR1, BIT(sub->swm->oport.map));
	पूर्ण अन्यथा अणु
		regmap_update_bits(r, IPORTMXRSTCTR(sub->swm->iport.map),
				   IPORTMXRSTCTR_RSTPI_MASK,
				   IPORTMXRSTCTR_RSTPI_RESET);
		regmap_update_bits(r, IPORTMXRSTCTR(sub->swm->iport.map),
				   IPORTMXRSTCTR_RSTPI_MASK,
				   IPORTMXRSTCTR_RSTPI_RELEASE);
	पूर्ण
पूर्ण

/**
 * aio_port_set_ch - set channels of LPCM
 * @sub: the AIO substream poपूर्णांकer, PCM substream only
 *
 * Set suitable slot selecting to input/output port block of AIO.
 *
 * This function may वापस error अगर non-PCM substream.
 *
 * Return: Zero अगर successful, otherwise a negative value on error.
 */
अटल पूर्णांक aio_port_set_ch(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	u32 slotsel_2ch[] = अणु
		0, 0, 0, 0, 0,
	पूर्ण;
	u32 slotsel_multi[] = अणु
		OPORTMXTYSLOTCTR_SLOTSEL_SLOT0,
		OPORTMXTYSLOTCTR_SLOTSEL_SLOT1,
		OPORTMXTYSLOTCTR_SLOTSEL_SLOT2,
		OPORTMXTYSLOTCTR_SLOTSEL_SLOT3,
		OPORTMXTYSLOTCTR_SLOTSEL_SLOT4,
	पूर्ण;
	u32 mode, *slotsel;
	पूर्णांक i;

	चयन (params_channels(&sub->params)) अणु
	हाल 8:
	हाल 6:
		mode = OPORTMXTYSLOTCTR_MODE;
		slotsel = slotsel_multi;
		अवरोध;
	हाल 2:
		mode = 0;
		slotsel = slotsel_2ch;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < AUD_MAX_SLOTSEL; i++) अणु
		regmap_update_bits(r, OPORTMXTYSLOTCTR(sub->swm->oport.map, i),
				   OPORTMXTYSLOTCTR_MODE, mode);
		regmap_update_bits(r, OPORTMXTYSLOTCTR(sub->swm->oport.map, i),
				   OPORTMXTYSLOTCTR_SLOTSEL_MASK, slotsel[i]);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * aio_port_set_rate - set sampling rate of LPCM
 * @sub: the AIO substream poपूर्णांकer, PCM substream only
 * @rate: Sampling rate in Hz.
 *
 * Set suitable I2S क्रमmat settings to input/output port block of AIO.
 * Parameter is specअगरied by hw_params().
 *
 * This function may वापस error अगर non-PCM substream.
 *
 * Return: Zero अगर successful, otherwise a negative value on error.
 */
अटल पूर्णांक aio_port_set_rate(काष्ठा uniphier_aio_sub *sub, पूर्णांक rate)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	काष्ठा device *dev = &sub->aio->chip->pdev->dev;
	u32 v;

	अगर (sub->swm->dir == PORT_सूची_OUTPUT) अणु
		चयन (rate) अणु
		हाल 8000:
			v = OPORTMXCTR1_FSSEL_8;
			अवरोध;
		हाल 11025:
			v = OPORTMXCTR1_FSSEL_11_025;
			अवरोध;
		हाल 12000:
			v = OPORTMXCTR1_FSSEL_12;
			अवरोध;
		हाल 16000:
			v = OPORTMXCTR1_FSSEL_16;
			अवरोध;
		हाल 22050:
			v = OPORTMXCTR1_FSSEL_22_05;
			अवरोध;
		हाल 24000:
			v = OPORTMXCTR1_FSSEL_24;
			अवरोध;
		हाल 32000:
			v = OPORTMXCTR1_FSSEL_32;
			अवरोध;
		हाल 44100:
			v = OPORTMXCTR1_FSSEL_44_1;
			अवरोध;
		हाल 48000:
			v = OPORTMXCTR1_FSSEL_48;
			अवरोध;
		हाल 88200:
			v = OPORTMXCTR1_FSSEL_88_2;
			अवरोध;
		हाल 96000:
			v = OPORTMXCTR1_FSSEL_96;
			अवरोध;
		हाल 176400:
			v = OPORTMXCTR1_FSSEL_176_4;
			अवरोध;
		हाल 192000:
			v = OPORTMXCTR1_FSSEL_192;
			अवरोध;
		शेष:
			dev_err(dev, "Rate not supported(%d)\n", rate);
			वापस -EINVAL;
		पूर्ण

		regmap_update_bits(r, OPORTMXCTR1(sub->swm->oport.map),
				   OPORTMXCTR1_FSSEL_MASK, v);
	पूर्ण अन्यथा अणु
		चयन (rate) अणु
		हाल 8000:
			v = IPORTMXCTR1_FSSEL_8;
			अवरोध;
		हाल 11025:
			v = IPORTMXCTR1_FSSEL_11_025;
			अवरोध;
		हाल 12000:
			v = IPORTMXCTR1_FSSEL_12;
			अवरोध;
		हाल 16000:
			v = IPORTMXCTR1_FSSEL_16;
			अवरोध;
		हाल 22050:
			v = IPORTMXCTR1_FSSEL_22_05;
			अवरोध;
		हाल 24000:
			v = IPORTMXCTR1_FSSEL_24;
			अवरोध;
		हाल 32000:
			v = IPORTMXCTR1_FSSEL_32;
			अवरोध;
		हाल 44100:
			v = IPORTMXCTR1_FSSEL_44_1;
			अवरोध;
		हाल 48000:
			v = IPORTMXCTR1_FSSEL_48;
			अवरोध;
		हाल 88200:
			v = IPORTMXCTR1_FSSEL_88_2;
			अवरोध;
		हाल 96000:
			v = IPORTMXCTR1_FSSEL_96;
			अवरोध;
		हाल 176400:
			v = IPORTMXCTR1_FSSEL_176_4;
			अवरोध;
		हाल 192000:
			v = IPORTMXCTR1_FSSEL_192;
			अवरोध;
		शेष:
			dev_err(dev, "Rate not supported(%d)\n", rate);
			वापस -EINVAL;
		पूर्ण

		regmap_update_bits(r, IPORTMXCTR1(sub->swm->iport.map),
				   IPORTMXCTR1_FSSEL_MASK, v);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * aio_port_set_fmt - set क्रमmat of I2S data
 * @sub: the AIO substream poपूर्णांकer, PCM substream only
 * This parameter has no effect अगर substream is I2S or PCM.
 *
 * Set suitable I2S क्रमmat settings to input/output port block of AIO.
 * Parameter is specअगरied by set_fmt().
 *
 * This function may वापस error अगर non-PCM substream.
 *
 * Return: Zero अगर successful, otherwise a negative value on error.
 */
अटल पूर्णांक aio_port_set_fmt(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	काष्ठा device *dev = &sub->aio->chip->pdev->dev;
	u32 v;

	अगर (sub->swm->dir == PORT_सूची_OUTPUT) अणु
		चयन (sub->aio->fmt) अणु
		हाल SND_SOC_DAIFMT_LEFT_J:
			v = OPORTMXCTR1_I2SLRSEL_LEFT;
			अवरोध;
		हाल SND_SOC_DAIFMT_RIGHT_J:
			v = OPORTMXCTR1_I2SLRSEL_RIGHT;
			अवरोध;
		हाल SND_SOC_DAIFMT_I2S:
			v = OPORTMXCTR1_I2SLRSEL_I2S;
			अवरोध;
		शेष:
			dev_err(dev, "Format is not supported(%d)\n",
				sub->aio->fmt);
			वापस -EINVAL;
		पूर्ण

		v |= OPORTMXCTR1_OUTBITSEL_24;
		regmap_update_bits(r, OPORTMXCTR1(sub->swm->oport.map),
				   OPORTMXCTR1_I2SLRSEL_MASK |
				   OPORTMXCTR1_OUTBITSEL_MASK, v);
	पूर्ण अन्यथा अणु
		चयन (sub->aio->fmt) अणु
		हाल SND_SOC_DAIFMT_LEFT_J:
			v = IPORTMXCTR1_LRSEL_LEFT;
			अवरोध;
		हाल SND_SOC_DAIFMT_RIGHT_J:
			v = IPORTMXCTR1_LRSEL_RIGHT;
			अवरोध;
		हाल SND_SOC_DAIFMT_I2S:
			v = IPORTMXCTR1_LRSEL_I2S;
			अवरोध;
		शेष:
			dev_err(dev, "Format is not supported(%d)\n",
				sub->aio->fmt);
			वापस -EINVAL;
		पूर्ण

		v |= IPORTMXCTR1_OUTBITSEL_24 |
			IPORTMXCTR1_CHSEL_ALL;
		regmap_update_bits(r, IPORTMXCTR1(sub->swm->iport.map),
				   IPORTMXCTR1_LRSEL_MASK |
				   IPORTMXCTR1_OUTBITSEL_MASK |
				   IPORTMXCTR1_CHSEL_MASK, v);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * aio_port_set_clk - set घड़ी and भागider of AIO port block
 * @sub: the AIO substream poपूर्णांकer
 *
 * Set suitable PLL घड़ी भागider and relational settings to
 * input/output port block of AIO. Parameters are specअगरied by
 * set_sysclk() and set_pll().
 *
 * Return: Zero अगर successful, otherwise a negative value on error.
 */
अटल पूर्णांक aio_port_set_clk(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा uniphier_aio_chip *chip = sub->aio->chip;
	काष्ठा device *dev = &sub->aio->chip->pdev->dev;
	काष्ठा regmap *r = sub->aio->chip->regmap;
	u32 v_pll[] = अणु
		OPORTMXCTR2_ACLKSEL_A1, OPORTMXCTR2_ACLKSEL_F1,
		OPORTMXCTR2_ACLKSEL_A2, OPORTMXCTR2_ACLKSEL_F2,
		OPORTMXCTR2_ACLKSEL_A2PLL,
		OPORTMXCTR2_ACLKSEL_RX1,
	पूर्ण;
	u32 v_भाग[] = अणु
		OPORTMXCTR2_DACCKSEL_1_2, OPORTMXCTR2_DACCKSEL_1_3,
		OPORTMXCTR2_DACCKSEL_1_1, OPORTMXCTR2_DACCKSEL_2_3,
	पूर्ण;
	u32 v;

	अगर (sub->swm->dir == PORT_सूची_OUTPUT) अणु
		अगर (sub->swm->type == PORT_TYPE_I2S) अणु
			अगर (sub->aio->pll_out >= ARRAY_SIZE(v_pll)) अणु
				dev_err(dev, "PLL(%d) is invalid\n",
					sub->aio->pll_out);
				वापस -EINVAL;
			पूर्ण
			अगर (sub->aio->plद_भाग >= ARRAY_SIZE(v_भाग)) अणु
				dev_err(dev, "PLL divider(%d) is invalid\n",
					sub->aio->plद_भाग);
				वापस -EINVAL;
			पूर्ण

			v = v_pll[sub->aio->pll_out] |
				OPORTMXCTR2_MSSEL_MASTER |
				v_भाग[sub->aio->plद_भाग];

			चयन (chip->plls[sub->aio->pll_out].freq) अणु
			हाल 0:
			हाल 36864000:
			हाल 33868800:
				v |= OPORTMXCTR2_EXTLSIFSSEL_36;
				अवरोध;
			शेष:
				v |= OPORTMXCTR2_EXTLSIFSSEL_24;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (sub->swm->type == PORT_TYPE_EVE) अणु
			v = OPORTMXCTR2_ACLKSEL_A2PLL |
				OPORTMXCTR2_MSSEL_MASTER |
				OPORTMXCTR2_EXTLSIFSSEL_36 |
				OPORTMXCTR2_DACCKSEL_1_2;
		पूर्ण अन्यथा अगर (sub->swm->type == PORT_TYPE_SPDIF) अणु
			अगर (sub->aio->pll_out >= ARRAY_SIZE(v_pll)) अणु
				dev_err(dev, "PLL(%d) is invalid\n",
					sub->aio->pll_out);
				वापस -EINVAL;
			पूर्ण
			v = v_pll[sub->aio->pll_out] |
				OPORTMXCTR2_MSSEL_MASTER |
				OPORTMXCTR2_DACCKSEL_1_2;

			चयन (chip->plls[sub->aio->pll_out].freq) अणु
			हाल 0:
			हाल 36864000:
			हाल 33868800:
				v |= OPORTMXCTR2_EXTLSIFSSEL_36;
				अवरोध;
			शेष:
				v |= OPORTMXCTR2_EXTLSIFSSEL_24;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			v = OPORTMXCTR2_ACLKSEL_A1 |
				OPORTMXCTR2_MSSEL_MASTER |
				OPORTMXCTR2_EXTLSIFSSEL_36 |
				OPORTMXCTR2_DACCKSEL_1_2;
		पूर्ण
		regmap_ग_लिखो(r, OPORTMXCTR2(sub->swm->oport.map), v);
	पूर्ण अन्यथा अणु
		v = IPORTMXCTR2_ACLKSEL_A1 |
			IPORTMXCTR2_MSSEL_SLAVE |
			IPORTMXCTR2_EXTLSIFSSEL_36 |
			IPORTMXCTR2_DACCKSEL_1_2;
		regmap_ग_लिखो(r, IPORTMXCTR2(sub->swm->iport.map), v);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * aio_port_set_param - set parameters of AIO port block
 * @sub: the AIO substream poपूर्णांकer
 * @pass_through: Zero अगर sound data is LPCM, otherwise अगर data is not LPCM.
 * This parameter has no effect अगर substream is I2S or PCM.
 * @params: hardware parameters of ALSA
 *
 * Set suitable setting to input/output port block of AIO to process the
 * specअगरied in params.
 *
 * Return: Zero अगर successful, otherwise a negative value on error.
 */
पूर्णांक aio_port_set_param(काष्ठा uniphier_aio_sub *sub, पूर्णांक pass_through,
		       स्थिर काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	अचिन्हित पूर्णांक rate;
	u32 v;
	पूर्णांक ret;

	अगर (!pass_through) अणु
		अगर (sub->swm->type == PORT_TYPE_EVE ||
		    sub->swm->type == PORT_TYPE_CONV) अणु
			rate = 48000;
		पूर्ण अन्यथा अणु
			rate = params_rate(params);
		पूर्ण

		ret = aio_port_set_ch(sub);
		अगर (ret)
			वापस ret;

		ret = aio_port_set_rate(sub, rate);
		अगर (ret)
			वापस ret;

		ret = aio_port_set_fmt(sub);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = aio_port_set_clk(sub);
	अगर (ret)
		वापस ret;

	अगर (sub->swm->dir == PORT_सूची_OUTPUT) अणु
		अगर (pass_through)
			v = OPORTMXCTR3_SRCSEL_STREAM |
				OPORTMXCTR3_VALID_STREAM;
		अन्यथा
			v = OPORTMXCTR3_SRCSEL_PCM |
				OPORTMXCTR3_VALID_PCM;

		v |= OPORTMXCTR3_IECTHUR_IECOUT |
			OPORTMXCTR3_PMSEL_PAUSE |
			OPORTMXCTR3_PMSW_MUTE_OFF;
		regmap_ग_लिखो(r, OPORTMXCTR3(sub->swm->oport.map), v);
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(r, IPORTMXACLKSEL0EX(sub->swm->iport.map),
			     IPORTMXACLKSEL0EX_ACLKSEL0EX_INTERNAL);
		regmap_ग_लिखो(r, IPORTMXEXNOE(sub->swm->iport.map),
			     IPORTMXEXNOE_PCMINOE_INPUT);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * aio_port_set_enable - start or stop of AIO port block
 * @sub: the AIO substream poपूर्णांकer
 * @enable: zero to stop the block, otherwise to start
 *
 * Start or stop the संकेत input/output port block of AIO.
 */
व्योम aio_port_set_enable(काष्ठा uniphier_aio_sub *sub, पूर्णांक enable)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;

	अगर (sub->swm->dir == PORT_सूची_OUTPUT) अणु
		regmap_ग_लिखो(r, OPORTMXPATH(sub->swm->oport.map),
			     sub->swm->oअगर.map);

		regmap_update_bits(r, OPORTMXMASK(sub->swm->oport.map),
				   OPORTMXMASK_IUDXMSK_MASK |
				   OPORTMXMASK_IUXCKMSK_MASK |
				   OPORTMXMASK_DXMSK_MASK |
				   OPORTMXMASK_XCKMSK_MASK,
				   OPORTMXMASK_IUDXMSK_OFF |
				   OPORTMXMASK_IUXCKMSK_OFF |
				   OPORTMXMASK_DXMSK_OFF |
				   OPORTMXMASK_XCKMSK_OFF);

		अगर (enable)
			regmap_ग_लिखो(r, AOUTENCTR0, BIT(sub->swm->oport.map));
		अन्यथा
			regmap_ग_लिखो(r, AOUTENCTR1, BIT(sub->swm->oport.map));
	पूर्ण अन्यथा अणु
		regmap_update_bits(r, IPORTMXMASK(sub->swm->iport.map),
				   IPORTMXMASK_IUXCKMSK_MASK |
				   IPORTMXMASK_XCKMSK_MASK,
				   IPORTMXMASK_IUXCKMSK_OFF |
				   IPORTMXMASK_XCKMSK_OFF);

		अगर (enable)
			regmap_update_bits(r,
					   IPORTMXCTR2(sub->swm->iport.map),
					   IPORTMXCTR2_REQEN_MASK,
					   IPORTMXCTR2_REQEN_ENABLE);
		अन्यथा
			regmap_update_bits(r,
					   IPORTMXCTR2(sub->swm->iport.map),
					   IPORTMXCTR2_REQEN_MASK,
					   IPORTMXCTR2_REQEN_DISABLE);
	पूर्ण
पूर्ण

/**
 * aio_port_get_volume - get volume of AIO port block
 * @sub: the AIO substream poपूर्णांकer
 *
 * Return: current volume, range is 0x0000 - 0xffff
 */
पूर्णांक aio_port_get_volume(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	u32 v;

	regmap_पढ़ो(r, OPORTMXTYVOLGAINSTATUS(sub->swm->oport.map, 0), &v);

	वापस FIELD_GET(OPORTMXTYVOLGAINSTATUS_CUR_MASK, v);
पूर्ण

/**
 * aio_port_set_volume - set volume of AIO port block
 * @sub: the AIO substream poपूर्णांकer
 * @vol: target volume, range is 0x0000 - 0xffff.
 *
 * Change digital volume and perfome fade-out/fade-in effect क्रम specअगरied
 * output slot of port. Gained PCM value can calculate as the following:
 *   Gained = Original * vol / 0x4000
 */
व्योम aio_port_set_volume(काष्ठा uniphier_aio_sub *sub, पूर्णांक vol)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	पूर्णांक oport_map = sub->swm->oport.map;
	पूर्णांक cur, dअगरf, slope = 0, fs;

	अगर (sub->swm->dir == PORT_सूची_INPUT)
		वापस;

	cur = aio_port_get_volume(sub);
	dअगरf = असल(vol - cur);
	fs = params_rate(&sub->params);
	अगर (fs)
		slope = dअगरf / AUD_VOL_FADE_TIME * 1000 / fs;
	slope = max(1, slope);

	regmap_update_bits(r, OPORTMXTYVOLPARA1(oport_map, 0),
			   OPORTMXTYVOLPARA1_SLOPEU_MASK, slope << 16);
	regmap_update_bits(r, OPORTMXTYVOLPARA2(oport_map, 0),
			   OPORTMXTYVOLPARA2_TARGET_MASK, vol);

	अगर (cur < vol)
		regmap_update_bits(r, OPORTMXTYVOLPARA2(oport_map, 0),
				   OPORTMXTYVOLPARA2_FADE_MASK,
				   OPORTMXTYVOLPARA2_FADE_FADEIN);
	अन्यथा
		regmap_update_bits(r, OPORTMXTYVOLPARA2(oport_map, 0),
				   OPORTMXTYVOLPARA2_FADE_MASK,
				   OPORTMXTYVOLPARA2_FADE_FADEOUT);

	regmap_ग_लिखो(r, AOUTFADECTR0, BIT(oport_map));
पूर्ण

/**
 * aio_अगर_set_param - set parameters of AIO DMA I/F block
 * @sub: the AIO substream poपूर्णांकer
 * @pass_through: Zero अगर sound data is LPCM, otherwise अगर data is not LPCM.
 * This parameter has no effect अगर substream is I2S or PCM.
 *
 * Set suitable setting to DMA पूर्णांकerface block of AIO to process the
 * specअगरied in settings.
 *
 * Return: Zero अगर successful, otherwise a negative value on error.
 */
पूर्णांक aio_अगर_set_param(काष्ठा uniphier_aio_sub *sub, पूर्णांक pass_through)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	u32 memfmt, v;

	अगर (sub->swm->dir == PORT_सूची_OUTPUT) अणु
		अगर (pass_through) अणु
			v = PBOUTMXCTR0_ENDIAN_0123 |
				PBOUTMXCTR0_MEMFMT_STREAM;
		पूर्ण अन्यथा अणु
			चयन (params_channels(&sub->params)) अणु
			हाल 2:
				memfmt = PBOUTMXCTR0_MEMFMT_2CH;
				अवरोध;
			हाल 6:
				memfmt = PBOUTMXCTR0_MEMFMT_6CH;
				अवरोध;
			हाल 8:
				memfmt = PBOUTMXCTR0_MEMFMT_8CH;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
			v = PBOUTMXCTR0_ENDIAN_3210 | memfmt;
		पूर्ण

		regmap_ग_लिखो(r, PBOUTMXCTR0(sub->swm->oअगर.map), v);
		regmap_ग_लिखो(r, PBOUTMXCTR1(sub->swm->oअगर.map), 0);
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(r, PBINMXCTR(sub->swm->iअगर.map),
			     PBINMXCTR_NCONNECT_CONNECT |
			     PBINMXCTR_INOUTSEL_IN |
			     (sub->swm->iport.map << PBINMXCTR_PBINSEL_SHIFT) |
			     PBINMXCTR_ENDIAN_3210 |
			     PBINMXCTR_MEMFMT_D0);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * aio_oport_set_stream_type - set parameters of AIO playback port block
 * @sub: the AIO substream poपूर्णांकer
 * @pc: Pc type of IEC61937
 *
 * Set special setting to output port block of AIO to output the stream
 * via S/PDIF.
 *
 * Return: Zero अगर successful, otherwise a negative value on error.
 */
पूर्णांक aio_oport_set_stream_type(काष्ठा uniphier_aio_sub *sub,
			      क्रमागत IEC61937_PC pc)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	u32 repet = 0, छोड़ो = OPORTMXPAUDAT_PAUSEPC_CMN;

	चयन (pc) अणु
	हाल IEC61937_PC_AC3:
		repet = OPORTMXREPET_STRLENGTH_AC3 |
			OPORTMXREPET_PMLENGTH_AC3;
		छोड़ो |= OPORTMXPAUDAT_PAUSEPD_AC3;
		अवरोध;
	हाल IEC61937_PC_MPA:
		repet = OPORTMXREPET_STRLENGTH_MPA |
			OPORTMXREPET_PMLENGTH_MPA;
		छोड़ो |= OPORTMXPAUDAT_PAUSEPD_MPA;
		अवरोध;
	हाल IEC61937_PC_MP3:
		repet = OPORTMXREPET_STRLENGTH_MP3 |
			OPORTMXREPET_PMLENGTH_MP3;
		छोड़ो |= OPORTMXPAUDAT_PAUSEPD_MP3;
		अवरोध;
	हाल IEC61937_PC_DTS1:
		repet = OPORTMXREPET_STRLENGTH_DTS1 |
			OPORTMXREPET_PMLENGTH_DTS1;
		छोड़ो |= OPORTMXPAUDAT_PAUSEPD_DTS1;
		अवरोध;
	हाल IEC61937_PC_DTS2:
		repet = OPORTMXREPET_STRLENGTH_DTS2 |
			OPORTMXREPET_PMLENGTH_DTS2;
		छोड़ो |= OPORTMXPAUDAT_PAUSEPD_DTS2;
		अवरोध;
	हाल IEC61937_PC_DTS3:
		repet = OPORTMXREPET_STRLENGTH_DTS3 |
			OPORTMXREPET_PMLENGTH_DTS3;
		छोड़ो |= OPORTMXPAUDAT_PAUSEPD_DTS3;
		अवरोध;
	हाल IEC61937_PC_AAC:
		repet = OPORTMXREPET_STRLENGTH_AAC |
			OPORTMXREPET_PMLENGTH_AAC;
		छोड़ो |= OPORTMXPAUDAT_PAUSEPD_AAC;
		अवरोध;
	हाल IEC61937_PC_PAUSE:
		/* Do nothing */
		अवरोध;
	पूर्ण

	regmap_ग_लिखो(r, OPORTMXREPET(sub->swm->oport.map), repet);
	regmap_ग_लिखो(r, OPORTMXPAUDAT(sub->swm->oport.map), छोड़ो);

	वापस 0;
पूर्ण

/**
 * aio_src_reset - reset AIO SRC block
 * @sub: the AIO substream poपूर्णांकer
 *
 * Resets the digital संकेत input/output port with sampling rate converter
 * block of AIO.
 * This function has no effect अगर substream is not supported rate converter.
 */
व्योम aio_src_reset(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;

	अगर (sub->swm->dir != PORT_सूची_OUTPUT)
		वापस;

	regmap_ग_लिखो(r, AOUTSRCRSTCTR0, BIT(sub->swm->oport.map));
	regmap_ग_लिखो(r, AOUTSRCRSTCTR1, BIT(sub->swm->oport.map));
पूर्ण

/**
 * aio_src_set_param - set parameters of AIO SRC block
 * @sub: the AIO substream poपूर्णांकer
 * @params: hardware parameters of ALSA
 *
 * Set suitable setting to input/output port with sampling rate converter
 * block of AIO to process the specअगरied in params.
 * This function has no effect अगर substream is not supported rate converter.
 *
 * Return: Zero अगर successful, otherwise a negative value on error.
 */
पूर्णांक aio_src_set_param(काष्ठा uniphier_aio_sub *sub,
		      स्थिर काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	u32 v;

	अगर (sub->swm->dir != PORT_सूची_OUTPUT)
		वापस 0;

	regmap_ग_लिखो(r, OPORTMXSRC1CTR(sub->swm->oport.map),
		     OPORTMXSRC1CTR_THMODE_SRC |
		     OPORTMXSRC1CTR_SRCPATH_CALC |
		     OPORTMXSRC1CTR_SYNC_ASYNC |
		     OPORTMXSRC1CTR_FSIIPSEL_INNER |
		     OPORTMXSRC1CTR_FSISEL_ACLK);

	चयन (params_rate(params)) अणु
	शेष:
	हाल 48000:
		v = OPORTMXRATE_I_ACLKSEL_APLLA1 |
			OPORTMXRATE_I_MCKSEL_36 |
			OPORTMXRATE_I_FSSEL_48;
		अवरोध;
	हाल 44100:
		v = OPORTMXRATE_I_ACLKSEL_APLLA2 |
			OPORTMXRATE_I_MCKSEL_33 |
			OPORTMXRATE_I_FSSEL_44_1;
		अवरोध;
	हाल 32000:
		v = OPORTMXRATE_I_ACLKSEL_APLLA1 |
			OPORTMXRATE_I_MCKSEL_36 |
			OPORTMXRATE_I_FSSEL_32;
		अवरोध;
	पूर्ण

	regmap_ग_लिखो(r, OPORTMXRATE_I(sub->swm->oport.map),
		     v | OPORTMXRATE_I_ACLKSRC_APLL |
		     OPORTMXRATE_I_LRCKSTP_STOP);
	regmap_update_bits(r, OPORTMXRATE_I(sub->swm->oport.map),
			   OPORTMXRATE_I_LRCKSTP_MASK,
			   OPORTMXRATE_I_LRCKSTP_START);

	वापस 0;
पूर्ण

पूर्णांक aio_srcअगर_set_param(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;

	regmap_ग_लिखो(r, PBINMXCTR(sub->swm->iअगर.map),
		     PBINMXCTR_NCONNECT_CONNECT |
		     PBINMXCTR_INOUTSEL_OUT |
		     (sub->swm->oport.map << PBINMXCTR_PBINSEL_SHIFT) |
		     PBINMXCTR_ENDIAN_3210 |
		     PBINMXCTR_MEMFMT_D0);

	वापस 0;
पूर्ण

पूर्णांक aio_srcch_set_param(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;

	regmap_ग_लिखो(r, CDA2D_CHMXCTRL1(sub->swm->och.map),
		     CDA2D_CHMXCTRL1_INDSIZE_INFINITE);

	regmap_ग_लिखो(r, CDA2D_CHMXSRCAMODE(sub->swm->och.map),
		     CDA2D_CHMXAMODE_ENDIAN_3210 |
		     CDA2D_CHMXAMODE_AUPDT_FIX |
		     CDA2D_CHMXAMODE_TYPE_NORMAL);

	regmap_ग_लिखो(r, CDA2D_CHMXDSTAMODE(sub->swm->och.map),
		     CDA2D_CHMXAMODE_ENDIAN_3210 |
		     CDA2D_CHMXAMODE_AUPDT_INC |
		     CDA2D_CHMXAMODE_TYPE_RING |
		     (sub->swm->och.map << CDA2D_CHMXAMODE_RSSEL_SHIFT));

	वापस 0;
पूर्ण

व्योम aio_srcch_set_enable(काष्ठा uniphier_aio_sub *sub, पूर्णांक enable)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	u32 v;

	अगर (enable)
		v = CDA2D_STRT0_STOP_START;
	अन्यथा
		v = CDA2D_STRT0_STOP_STOP;

	regmap_ग_लिखो(r, CDA2D_STRT0,
		     v | BIT(sub->swm->och.map));
पूर्ण

पूर्णांक aiodma_ch_set_param(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	u32 v;

	regmap_ग_लिखो(r, CDA2D_CHMXCTRL1(sub->swm->ch.map),
		     CDA2D_CHMXCTRL1_INDSIZE_INFINITE);

	v = CDA2D_CHMXAMODE_ENDIAN_3210 |
		CDA2D_CHMXAMODE_AUPDT_INC |
		CDA2D_CHMXAMODE_TYPE_NORMAL |
		(sub->swm->rb.map << CDA2D_CHMXAMODE_RSSEL_SHIFT);
	अगर (sub->swm->dir == PORT_सूची_OUTPUT)
		regmap_ग_लिखो(r, CDA2D_CHMXSRCAMODE(sub->swm->ch.map), v);
	अन्यथा
		regmap_ग_लिखो(r, CDA2D_CHMXDSTAMODE(sub->swm->ch.map), v);

	वापस 0;
पूर्ण

व्योम aiodma_ch_set_enable(काष्ठा uniphier_aio_sub *sub, पूर्णांक enable)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;

	अगर (enable) अणु
		regmap_ग_लिखो(r, CDA2D_STRT0,
			     CDA2D_STRT0_STOP_START | BIT(sub->swm->ch.map));

		regmap_update_bits(r, INTRBIM(0),
				   BIT(sub->swm->rb.map),
				   BIT(sub->swm->rb.map));
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(r, CDA2D_STRT0,
			     CDA2D_STRT0_STOP_STOP | BIT(sub->swm->ch.map));

		regmap_update_bits(r, INTRBIM(0),
				   BIT(sub->swm->rb.map),
				   0);
	पूर्ण
पूर्ण

अटल u64 aiodma_rb_get_rp(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	u32 pos_u, pos_l;
	पूर्णांक i;

	regmap_ग_लिखो(r, CDA2D_RDPTRLOAD,
		     CDA2D_RDPTRLOAD_LSFLAG_STORE | BIT(sub->swm->rb.map));
	/* Wait क्रम setup */
	क्रम (i = 0; i < 6; i++)
		regmap_पढ़ो(r, CDA2D_RBMXRDPTR(sub->swm->rb.map), &pos_l);

	regmap_पढ़ो(r, CDA2D_RBMXRDPTR(sub->swm->rb.map), &pos_l);
	regmap_पढ़ो(r, CDA2D_RBMXRDPTRU(sub->swm->rb.map), &pos_u);
	pos_u = FIELD_GET(CDA2D_RBMXPTRU_PTRU_MASK, pos_u);

	वापस ((u64)pos_u << 32) | pos_l;
पूर्ण

अटल व्योम aiodma_rb_set_rp(काष्ठा uniphier_aio_sub *sub, u64 pos)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	u32 पंचांगp;
	पूर्णांक i;

	regmap_ग_लिखो(r, CDA2D_RBMXRDPTR(sub->swm->rb.map), (u32)pos);
	regmap_ग_लिखो(r, CDA2D_RBMXRDPTRU(sub->swm->rb.map), (u32)(pos >> 32));
	regmap_ग_लिखो(r, CDA2D_RDPTRLOAD, BIT(sub->swm->rb.map));
	/* Wait क्रम setup */
	क्रम (i = 0; i < 6; i++)
		regmap_पढ़ो(r, CDA2D_RBMXRDPTR(sub->swm->rb.map), &पंचांगp);
पूर्ण

अटल u64 aiodma_rb_get_wp(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	u32 pos_u, pos_l;
	पूर्णांक i;

	regmap_ग_लिखो(r, CDA2D_WRPTRLOAD,
		     CDA2D_WRPTRLOAD_LSFLAG_STORE | BIT(sub->swm->rb.map));
	/* Wait क्रम setup */
	क्रम (i = 0; i < 6; i++)
		regmap_पढ़ो(r, CDA2D_RBMXWRPTR(sub->swm->rb.map), &pos_l);

	regmap_पढ़ो(r, CDA2D_RBMXWRPTR(sub->swm->rb.map), &pos_l);
	regmap_पढ़ो(r, CDA2D_RBMXWRPTRU(sub->swm->rb.map), &pos_u);
	pos_u = FIELD_GET(CDA2D_RBMXPTRU_PTRU_MASK, pos_u);

	वापस ((u64)pos_u << 32) | pos_l;
पूर्ण

अटल व्योम aiodma_rb_set_wp(काष्ठा uniphier_aio_sub *sub, u64 pos)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	u32 पंचांगp;
	पूर्णांक i;

	regmap_ग_लिखो(r, CDA2D_RBMXWRPTR(sub->swm->rb.map),
		     lower_32_bits(pos));
	regmap_ग_लिखो(r, CDA2D_RBMXWRPTRU(sub->swm->rb.map),
		     upper_32_bits(pos));
	regmap_ग_लिखो(r, CDA2D_WRPTRLOAD, BIT(sub->swm->rb.map));
	/* Wait क्रम setup */
	क्रम (i = 0; i < 6; i++)
		regmap_पढ़ो(r, CDA2D_RBMXWRPTR(sub->swm->rb.map), &पंचांगp);
पूर्ण

पूर्णांक aiodma_rb_set_threshold(काष्ठा uniphier_aio_sub *sub, u64 size, u32 th)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;

	अगर (size <= th)
		वापस -EINVAL;

	regmap_ग_लिखो(r, CDA2D_RBMXBTH(sub->swm->rb.map), th);
	regmap_ग_लिखो(r, CDA2D_RBMXRTH(sub->swm->rb.map), th);

	वापस 0;
पूर्ण

पूर्णांक aiodma_rb_set_buffer(काष्ठा uniphier_aio_sub *sub, u64 start, u64 end,
			 पूर्णांक period)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	u64 size = end - start;
	पूर्णांक ret;

	अगर (end < start || period < 0)
		वापस -EINVAL;

	regmap_ग_लिखो(r, CDA2D_RBMXCNFG(sub->swm->rb.map), 0);
	regmap_ग_लिखो(r, CDA2D_RBMXBGNADRS(sub->swm->rb.map),
		     lower_32_bits(start));
	regmap_ग_लिखो(r, CDA2D_RBMXBGNADRSU(sub->swm->rb.map),
		     upper_32_bits(start));
	regmap_ग_लिखो(r, CDA2D_RBMXENDADRS(sub->swm->rb.map),
		     lower_32_bits(end));
	regmap_ग_लिखो(r, CDA2D_RBMXENDADRSU(sub->swm->rb.map),
		     upper_32_bits(end));

	regmap_ग_लिखो(r, CDA2D_RBADRSLOAD, BIT(sub->swm->rb.map));

	ret = aiodma_rb_set_threshold(sub, size, 2 * period);
	अगर (ret)
		वापस ret;

	अगर (sub->swm->dir == PORT_सूची_OUTPUT) अणु
		aiodma_rb_set_rp(sub, start);
		aiodma_rb_set_wp(sub, end - period);

		regmap_update_bits(r, CDA2D_RBMXIE(sub->swm->rb.map),
				   CDA2D_RBMXIX_SPACE,
				   CDA2D_RBMXIX_SPACE);
	पूर्ण अन्यथा अणु
		aiodma_rb_set_rp(sub, end - period);
		aiodma_rb_set_wp(sub, start);

		regmap_update_bits(r, CDA2D_RBMXIE(sub->swm->rb.map),
				   CDA2D_RBMXIX_REMAIN,
				   CDA2D_RBMXIX_REMAIN);
	पूर्ण

	sub->threshold = 2 * period;
	sub->rd_offs = 0;
	sub->wr_offs = 0;
	sub->rd_org = 0;
	sub->wr_org = 0;
	sub->rd_total = 0;
	sub->wr_total = 0;

	वापस 0;
पूर्ण

व्योम aiodma_rb_sync(काष्ठा uniphier_aio_sub *sub, u64 start, u64 size,
		    पूर्णांक period)
अणु
	अगर (sub->swm->dir == PORT_सूची_OUTPUT) अणु
		sub->rd_offs = aiodma_rb_get_rp(sub) - start;

		अगर (sub->use_mmap) अणु
			sub->threshold = 2 * period;
			aiodma_rb_set_threshold(sub, size, 2 * period);

			sub->wr_offs = sub->rd_offs - period;
			अगर (sub->rd_offs < period)
				sub->wr_offs += size;
		पूर्ण
		aiodma_rb_set_wp(sub, sub->wr_offs + start);
	पूर्ण अन्यथा अणु
		sub->wr_offs = aiodma_rb_get_wp(sub) - start;

		अगर (sub->use_mmap) अणु
			sub->threshold = 2 * period;
			aiodma_rb_set_threshold(sub, size, 2 * period);

			sub->rd_offs = sub->wr_offs - period;
			अगर (sub->wr_offs < period)
				sub->rd_offs += size;
		पूर्ण
		aiodma_rb_set_rp(sub, sub->rd_offs + start);
	पूर्ण

	sub->rd_total += sub->rd_offs - sub->rd_org;
	अगर (sub->rd_offs < sub->rd_org)
		sub->rd_total += size;
	sub->wr_total += sub->wr_offs - sub->wr_org;
	अगर (sub->wr_offs < sub->wr_org)
		sub->wr_total += size;

	sub->rd_org = sub->rd_offs;
	sub->wr_org = sub->wr_offs;
पूर्ण

bool aiodma_rb_is_irq(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;
	u32 ir;

	regmap_पढ़ो(r, CDA2D_RBMXIR(sub->swm->rb.map), &ir);

	अगर (sub->swm->dir == PORT_सूची_OUTPUT)
		वापस !!(ir & CDA2D_RBMXIX_SPACE);
	अन्यथा
		वापस !!(ir & CDA2D_RBMXIX_REMAIN);
पूर्ण

व्योम aiodma_rb_clear_irq(काष्ठा uniphier_aio_sub *sub)
अणु
	काष्ठा regmap *r = sub->aio->chip->regmap;

	अगर (sub->swm->dir == PORT_सूची_OUTPUT)
		regmap_ग_लिखो(r, CDA2D_RBMXIR(sub->swm->rb.map),
			     CDA2D_RBMXIX_SPACE);
	अन्यथा
		regmap_ग_लिखो(r, CDA2D_RBMXIR(sub->swm->rb.map),
			     CDA2D_RBMXIX_REMAIN);
पूर्ण
