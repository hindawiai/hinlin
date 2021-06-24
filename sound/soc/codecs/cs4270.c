<शैली गुरु>
/*
 * CS4270 ALSA SoC (ASoC) codec driver
 *
 * Author: Timur Tabi <timur@मुक्तscale.com>
 *
 * Copyright 2007-2009 Freescale Semiconductor, Inc.  This file is licensed
 * under the terms of the GNU General Public License version 2.  This
 * program is licensed "as is" without any warranty of any kind, whether
 * express or implied.
 *
 * This is an ASoC device driver क्रम the Cirrus Logic CS4270 codec.
 *
 * Current features/limitations:
 *
 * - Software mode is supported.  Stand-alone mode is not supported.
 * - Only I2C is supported, not SPI
 * - Support क्रम master and slave mode
 * - The machine driver's 'startup' function must call
 *   cs4270_set_dai_sysclk() with the value of MCLK.
 * - Only I2S and left-justअगरied modes are supported
 * - Power management is supported
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_device.h>

/*
 * The codec isn't really big-endian or little-endian, since the I2S
 * पूर्णांकerface requires data to be sent serially with the MSbit first.
 * However, to support BE and LE I2S devices, we specअगरy both here.  That
 * way, ALSA will always match the bit patterns.
 */
#घोषणा CS4270_FORMATS (SNDRV_PCM_FMTBIT_S8      | \
			SNDRV_PCM_FMTBIT_S16_LE  | SNDRV_PCM_FMTBIT_S16_BE  | \
			SNDRV_PCM_FMTBIT_S18_3LE | SNDRV_PCM_FMTBIT_S18_3BE | \
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S20_3BE | \
			SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_3BE | \
			SNDRV_PCM_FMTBIT_S24_LE  | SNDRV_PCM_FMTBIT_S24_BE)

/* CS4270 रेजिस्टरs addresses */
#घोषणा CS4270_CHIPID	0x01	/* Chip ID */
#घोषणा CS4270_PWRCTL	0x02	/* Power Control */
#घोषणा CS4270_MODE	0x03	/* Mode Control */
#घोषणा CS4270_FORMAT	0x04	/* Serial Format, ADC/DAC Control */
#घोषणा CS4270_TRANS	0x05	/* Transition Control */
#घोषणा CS4270_MUTE	0x06	/* Mute Control */
#घोषणा CS4270_VOLA	0x07	/* DAC Channel A Volume Control */
#घोषणा CS4270_VOLB	0x08	/* DAC Channel B Volume Control */

#घोषणा CS4270_FIRSTREG	0x01
#घोषणा CS4270_LASTREG	0x08
#घोषणा CS4270_NUMREGS	(CS4270_LASTREG - CS4270_FIRSTREG + 1)
#घोषणा CS4270_I2C_INCR	0x80

/* Bit masks क्रम the CS4270 रेजिस्टरs */
#घोषणा CS4270_CHIPID_ID	0xF0
#घोषणा CS4270_CHIPID_REV	0x0F
#घोषणा CS4270_PWRCTL_FREEZE	0x80
#घोषणा CS4270_PWRCTL_PDN_ADC	0x20
#घोषणा CS4270_PWRCTL_PDN_DAC	0x02
#घोषणा CS4270_PWRCTL_PDN	0x01
#घोषणा CS4270_PWRCTL_PDN_ALL	\
	(CS4270_PWRCTL_PDN_ADC | CS4270_PWRCTL_PDN_DAC | CS4270_PWRCTL_PDN)
#घोषणा CS4270_MODE_SPEED_MASK	0x30
#घोषणा CS4270_MODE_1X		0x00
#घोषणा CS4270_MODE_2X		0x10
#घोषणा CS4270_MODE_4X		0x20
#घोषणा CS4270_MODE_SLAVE	0x30
#घोषणा CS4270_MODE_DIV_MASK	0x0E
#घोषणा CS4270_MODE_DIV1	0x00
#घोषणा CS4270_MODE_DIV15	0x02
#घोषणा CS4270_MODE_DIV2	0x04
#घोषणा CS4270_MODE_DIV3	0x06
#घोषणा CS4270_MODE_DIV4	0x08
#घोषणा CS4270_MODE_POPGUARD	0x01
#घोषणा CS4270_FORMAT_FREEZE_A	0x80
#घोषणा CS4270_FORMAT_FREEZE_B	0x40
#घोषणा CS4270_FORMAT_LOOPBACK	0x20
#घोषणा CS4270_FORMAT_DAC_MASK	0x18
#घोषणा CS4270_FORMAT_DAC_LJ	0x00
#घोषणा CS4270_FORMAT_DAC_I2S	0x08
#घोषणा CS4270_FORMAT_DAC_RJ16	0x18
#घोषणा CS4270_FORMAT_DAC_RJ24	0x10
#घोषणा CS4270_FORMAT_ADC_MASK	0x01
#घोषणा CS4270_FORMAT_ADC_LJ	0x00
#घोषणा CS4270_FORMAT_ADC_I2S	0x01
#घोषणा CS4270_TRANS_ONE_VOL	0x80
#घोषणा CS4270_TRANS_SOFT	0x40
#घोषणा CS4270_TRANS_ZERO	0x20
#घोषणा CS4270_TRANS_INV_ADC_A	0x08
#घोषणा CS4270_TRANS_INV_ADC_B	0x10
#घोषणा CS4270_TRANS_INV_DAC_A	0x02
#घोषणा CS4270_TRANS_INV_DAC_B	0x04
#घोषणा CS4270_TRANS_DEEMPH	0x01
#घोषणा CS4270_MUTE_AUTO	0x20
#घोषणा CS4270_MUTE_ADC_A	0x08
#घोषणा CS4270_MUTE_ADC_B	0x10
#घोषणा CS4270_MUTE_POLARITY	0x04
#घोषणा CS4270_MUTE_DAC_A	0x01
#घोषणा CS4270_MUTE_DAC_B	0x02

/* Power-on शेष values क्रम the रेजिस्टरs
 *
 * This array contains the घातer-on शेष values of the रेजिस्टरs, with the
 * exception of the "CHIPID" रेजिस्टर (01h).  The lower four bits of that
 * रेजिस्टर contain the hardware revision, so it is treated as अस्थिर.
 */
अटल स्थिर काष्ठा reg_शेष cs4270_reg_शेषs[] = अणु
	अणु 2, 0x00 पूर्ण,
	अणु 3, 0x30 पूर्ण,
	अणु 4, 0x00 पूर्ण,
	अणु 5, 0x60 पूर्ण,
	अणु 6, 0x20 पूर्ण,
	अणु 7, 0x00 पूर्ण,
	अणु 8, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *supply_names[] = अणु
	"va", "vd", "vlc"
पूर्ण;

/* Private data क्रम the CS4270 */
काष्ठा cs4270_निजी अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक mclk; /* Input frequency of the MCLK pin */
	अचिन्हित पूर्णांक mode; /* The mode (I2S or left-justअगरied) */
	अचिन्हित पूर्णांक slave_mode;
	अचिन्हित पूर्णांक manual_mute;

	/* घातer करोमुख्य regulators */
	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(supply_names)];

	/* reset gpio */
	काष्ठा gpio_desc *reset_gpio;
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cs4270_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("AINL"),
SND_SOC_DAPM_INPUT("AINR"),

SND_SOC_DAPM_OUTPUT("AOUTL"),
SND_SOC_DAPM_OUTPUT("AOUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs4270_dapm_routes[] = अणु
	अणु "Capture", शून्य, "AINL" पूर्ण,
	अणु "Capture", शून्य, "AINR" पूर्ण,

	अणु "AOUTL", शून्य, "Playback" पूर्ण,
	अणु "AOUTR", शून्य, "Playback" पूर्ण,
पूर्ण;

/**
 * काष्ठा cs4270_mode_ratios - घड़ी ratio tables
 * @ratio: the ratio of MCLK to the sample rate
 * @speed_mode: the Speed Mode bits to set in the Mode Control रेजिस्टर क्रम
 *              this ratio
 * @mclk: the Ratio Select bits to set in the Mode Control रेजिस्टर क्रम this
 *        ratio
 *
 * The data क्रम this अक्षरt is taken from Table 5 of the CS4270 reference
 * manual.
 *
 * This table is used to determine how to program the Mode Control रेजिस्टर.
 * It is also used by cs4270_set_dai_sysclk() to tell ALSA which sampling
 * rates the CS4270 currently supports.
 *
 * @speed_mode is the corresponding bit pattern to be written to the
 * MODE bits of the Mode Control Register
 *
 * @mclk is the corresponding bit pattern to be wirten to the MCLK bits of
 * the Mode Control Register.
 *
 * In situations where a single ratio is represented by multiple speed
 * modes, we favor the slowest speed.  E.g, क्रम a ratio of 128, we pick
 * द्विगुन-speed instead of quad-speed.  However, the CS4270 errata states
 * that भागide-By-1.5 can cause failures, so we aव्योम that mode where
 * possible.
 *
 * Errata: There is an errata क्रम the CS4270 where भागide-by-1.5 करोes not
 * work अगर Vd is 3.3V.  If this effects you, select the
 * CONFIG_SND_SOC_CS4270_VD33_ERRATA Kconfig option, and the driver will
 * never select any sample rates that require भागide-by-1.5.
 */
काष्ठा cs4270_mode_ratios अणु
	अचिन्हित पूर्णांक ratio;
	u8 speed_mode;
	u8 mclk;
पूर्ण;

अटल काष्ठा cs4270_mode_ratios cs4270_mode_ratios[] = अणु
	अणु64, CS4270_MODE_4X, CS4270_MODE_DIV1पूर्ण,
#अगर_अघोषित CONFIG_SND_SOC_CS4270_VD33_ERRATA
	अणु96, CS4270_MODE_4X, CS4270_MODE_DIV15पूर्ण,
#पूर्ण_अगर
	अणु128, CS4270_MODE_2X, CS4270_MODE_DIV1पूर्ण,
	अणु192, CS4270_MODE_4X, CS4270_MODE_DIV3पूर्ण,
	अणु256, CS4270_MODE_1X, CS4270_MODE_DIV1पूर्ण,
	अणु384, CS4270_MODE_2X, CS4270_MODE_DIV3पूर्ण,
	अणु512, CS4270_MODE_1X, CS4270_MODE_DIV2पूर्ण,
	अणु768, CS4270_MODE_1X, CS4270_MODE_DIV3पूर्ण,
	अणु1024, CS4270_MODE_1X, CS4270_MODE_DIV4पूर्ण
पूर्ण;

/* The number of MCLK/LRCK ratios supported by the CS4270 */
#घोषणा NUM_MCLK_RATIOS		ARRAY_SIZE(cs4270_mode_ratios)

अटल bool cs4270_reg_is_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg >= CS4270_FIRSTREG) && (reg <= CS4270_LASTREG);
पूर्ण

अटल bool cs4270_reg_is_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* Unपढ़ोable रेजिस्टरs are considered अस्थिर */
	अगर ((reg < CS4270_FIRSTREG) || (reg > CS4270_LASTREG))
		वापस true;

	वापस reg == CS4270_CHIPID;
पूर्ण

/**
 * cs4270_set_dai_sysclk - determine the CS4270 samples rates.
 * @codec_dai: the codec DAI
 * @clk_id: the घड़ी ID (ignored)
 * @freq: the MCLK input frequency
 * @dir: the घड़ी direction (ignored)
 *
 * This function is used to tell the codec driver what the input MCLK
 * frequency is.
 *
 * The value of MCLK is used to determine which sample rates are supported
 * by the CS4270.  The ratio of MCLK / Fs must be equal to one of nine
 * supported values - 64, 96, 128, 192, 256, 384, 512, 768, and 1024.
 *
 * This function calculates the nine ratios and determines which ones match
 * a standard sample rate.  If there's a match, then it is added to the list
 * of supported sample rates.
 *
 * This function must be called by the machine driver's 'startup' function,
 * otherwise the list of supported sample rates will not be available in
 * समय क्रम ALSA.
 *
 * For setups with variable MCLKs, pass 0 as 'freq' argument. This will cause
 * theoretically possible sample rates to be enabled. Call it again with a
 * proper value set one the बाह्यal घड़ी is set (most probably you would करो
 * that from a machine's driver 'hw_param' hook.
 */
अटल पूर्णांक cs4270_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs4270_निजी *cs4270 = snd_soc_component_get_drvdata(component);

	cs4270->mclk = freq;
	वापस 0;
पूर्ण

/**
 * cs4270_set_dai_fmt - configure the codec क्रम the selected audio क्रमmat
 * @codec_dai: the codec DAI
 * @क्रमmat: a SND_SOC_DAIFMT_x value indicating the data क्रमmat
 *
 * This function takes a biपंचांगask of SND_SOC_DAIFMT_x bits and programs the
 * codec accordingly.
 *
 * Currently, this function only supports SND_SOC_DAIFMT_I2S and
 * SND_SOC_DAIFMT_LEFT_J.  The CS4270 codec also supports right-justअगरied
 * data क्रम playback only, but ASoC currently करोes not support dअगरferent
 * क्रमmats क्रम playback vs. record.
 */
अटल पूर्णांक cs4270_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			      अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs4270_निजी *cs4270 = snd_soc_component_get_drvdata(component);

	/* set DAI क्रमmat */
	चयन (क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_LEFT_J:
		cs4270->mode = क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK;
		अवरोध;
	शेष:
		dev_err(component->dev, "invalid dai format\n");
		वापस -EINVAL;
	पूर्ण

	/* set master/slave audio पूर्णांकerface */
	चयन (क्रमmat & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		cs4270->slave_mode = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		cs4270->slave_mode = 0;
		अवरोध;
	शेष:
		/* all other modes are unsupported by the hardware */
		dev_err(component->dev, "Unknown master/slave configuration\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cs4270_hw_params - program the CS4270 with the given hardware parameters.
 * @substream: the audio stream
 * @params: the hardware parameters to set
 * @dai: the SOC DAI (ignored)
 *
 * This function programs the hardware with the values provided.
 * Specअगरically, the sample rate and the data क्रमmat.
 *
 * The .ops functions are used to provide board-specअगरic data, like input
 * frequencies, to this driver.  This function takes that inक्रमmation,
 * combines it with the hardware parameters provided, and programs the
 * hardware accordingly.
 */
अटल पूर्णांक cs4270_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs4270_निजी *cs4270 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक ratio;
	पूर्णांक reg;

	/* Figure out which MCLK/LRCK ratio to use */

	rate = params_rate(params);	/* Sampling rate, in Hz */
	ratio = cs4270->mclk / rate;	/* MCLK/LRCK ratio */

	क्रम (i = 0; i < NUM_MCLK_RATIOS; i++) अणु
		अगर (cs4270_mode_ratios[i].ratio == ratio)
			अवरोध;
	पूर्ण

	अगर (i == NUM_MCLK_RATIOS) अणु
		/* We did not find a matching ratio */
		dev_err(component->dev, "could not find matching ratio\n");
		वापस -EINVAL;
	पूर्ण

	/* Set the sample rate */

	reg = snd_soc_component_पढ़ो(component, CS4270_MODE);
	reg &= ~(CS4270_MODE_SPEED_MASK | CS4270_MODE_DIV_MASK);
	reg |= cs4270_mode_ratios[i].mclk;

	अगर (cs4270->slave_mode)
		reg |= CS4270_MODE_SLAVE;
	अन्यथा
		reg |= cs4270_mode_ratios[i].speed_mode;

	ret = snd_soc_component_ग_लिखो(component, CS4270_MODE, reg);
	अगर (ret < 0) अणु
		dev_err(component->dev, "i2c write failed\n");
		वापस ret;
	पूर्ण

	/* Set the DAI क्रमmat */

	reg = snd_soc_component_पढ़ो(component, CS4270_FORMAT);
	reg &= ~(CS4270_FORMAT_DAC_MASK | CS4270_FORMAT_ADC_MASK);

	चयन (cs4270->mode) अणु
	हाल SND_SOC_DAIFMT_I2S:
		reg |= CS4270_FORMAT_DAC_I2S | CS4270_FORMAT_ADC_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		reg |= CS4270_FORMAT_DAC_LJ | CS4270_FORMAT_ADC_LJ;
		अवरोध;
	शेष:
		dev_err(component->dev, "unknown dai format\n");
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_ग_लिखो(component, CS4270_FORMAT, reg);
	अगर (ret < 0) अणु
		dev_err(component->dev, "i2c write failed\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * cs4270_dai_mute - enable/disable the CS4270 बाह्यal mute
 * @dai: the SOC DAI
 * @mute: 0 = disable mute, 1 = enable mute
 * @direction: (ignored)
 *
 * This function toggles the mute bits in the MUTE रेजिस्टर.  The CS4270's
 * mute capability is पूर्णांकended क्रम बाह्यal muting circuitry, so अगर the
 * board करोes not have the MUTEA or MUTEB pins connected to such circuitry,
 * then this function will करो nothing.
 */
अटल पूर्णांक cs4270_dai_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs4270_निजी *cs4270 = snd_soc_component_get_drvdata(component);
	पूर्णांक reg6;

	reg6 = snd_soc_component_पढ़ो(component, CS4270_MUTE);

	अगर (mute)
		reg6 |= CS4270_MUTE_DAC_A | CS4270_MUTE_DAC_B;
	अन्यथा अणु
		reg6 &= ~(CS4270_MUTE_DAC_A | CS4270_MUTE_DAC_B);
		reg6 |= cs4270->manual_mute;
	पूर्ण

	वापस snd_soc_component_ग_लिखो(component, CS4270_MUTE, reg6);
पूर्ण

/**
 * cs4270_soc_put_mute - put callback क्रम the 'Master Playback switch'
 * 			 alsa control.
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * This function basically passes the arguments on to the generic
 * snd_soc_put_volsw() function and saves the mute inक्रमmation in
 * our निजी data काष्ठाure. This is because we want to prevent
 * cs4270_dai_mute() neglecting the user's decision to manually
 * mute the codec's output.
 *
 * Returns 0 क्रम success.
 */
अटल पूर्णांक cs4270_soc_put_mute(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा cs4270_निजी *cs4270 = snd_soc_component_get_drvdata(component);
	पूर्णांक left = !ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक right = !ucontrol->value.पूर्णांकeger.value[1];

	cs4270->manual_mute = (left ? CS4270_MUTE_DAC_A : 0) |
			      (right ? CS4270_MUTE_DAC_B : 0);

	वापस snd_soc_put_volsw(kcontrol, ucontrol);
पूर्ण

/* A list of non-DAPM controls that the CS4270 supports */
अटल स्थिर काष्ठा snd_kcontrol_new cs4270_snd_controls[] = अणु
	SOC_DOUBLE_R("Master Playback Volume",
		CS4270_VOLA, CS4270_VOLB, 0, 0xFF, 1),
	SOC_SINGLE("Digital Sidetone Switch", CS4270_FORMAT, 5, 1, 0),
	SOC_SINGLE("Soft Ramp Switch", CS4270_TRANS, 6, 1, 0),
	SOC_SINGLE("Zero Cross Switch", CS4270_TRANS, 5, 1, 0),
	SOC_SINGLE("De-emphasis filter", CS4270_TRANS, 0, 1, 0),
	SOC_SINGLE("Popguard Switch", CS4270_MODE, 0, 1, 1),
	SOC_SINGLE("Auto-Mute Switch", CS4270_MUTE, 5, 1, 0),
	SOC_DOUBLE("Master Capture Switch", CS4270_MUTE, 3, 4, 1, 1),
	SOC_DOUBLE_EXT("Master Playback Switch", CS4270_MUTE, 0, 1, 1, 1,
		snd_soc_get_volsw, cs4270_soc_put_mute),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops cs4270_dai_ops = अणु
	.hw_params	= cs4270_hw_params,
	.set_sysclk	= cs4270_set_dai_sysclk,
	.set_fmt	= cs4270_set_dai_fmt,
	.mute_stream	= cs4270_dai_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs4270_dai = अणु
	.name = "cs4270-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min = 4000,
		.rate_max = 216000,
		.क्रमmats = CS4270_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min = 4000,
		.rate_max = 216000,
		.क्रमmats = CS4270_FORMATS,
	पूर्ण,
	.ops = &cs4270_dai_ops,
पूर्ण;

/**
 * cs4270_probe - ASoC probe function
 * @component: ASoC component
 *
 * This function is called when ASoC has all the pieces it needs to
 * instantiate a sound driver.
 */
अटल पूर्णांक cs4270_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs4270_निजी *cs4270 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	/* Disable स्वतः-mute.  This feature appears to be buggy.  In some
	 * situations, स्वतः-mute will not deactivate when it should, so we want
	 * this feature disabled by शेष.  An application (e.g. alsactl) can
	 * re-enabled it by using the controls.
	 */
	ret = snd_soc_component_update_bits(component, CS4270_MUTE, CS4270_MUTE_AUTO, 0);
	अगर (ret < 0) अणु
		dev_err(component->dev, "i2c write failed\n");
		वापस ret;
	पूर्ण

	/* Disable स्वतःmatic volume control.  The hardware enables, and it
	 * causes volume change commands to be delayed, someबार until after
	 * playback has started.  An application (e.g. alsactl) can
	 * re-enabled it by using the controls.
	 */
	ret = snd_soc_component_update_bits(component, CS4270_TRANS,
		CS4270_TRANS_SOFT | CS4270_TRANS_ZERO, 0);
	अगर (ret < 0) अणु
		dev_err(component->dev, "i2c write failed\n");
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(cs4270->supplies),
				    cs4270->supplies);

	वापस ret;
पूर्ण

/**
 * cs4270_हटाओ - ASoC हटाओ function
 * @component: ASoC component
 *
 * This function is the counterpart to cs4270_probe().
 */
अटल व्योम cs4270_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs4270_निजी *cs4270 = snd_soc_component_get_drvdata(component);

	regulator_bulk_disable(ARRAY_SIZE(cs4270->supplies), cs4270->supplies);
पूर्ण;

#अगर_घोषित CONFIG_PM

/* This suspend/resume implementation can handle both - a simple standby
 * where the codec reमुख्यs घातered, and a full suspend, where the voltage
 * करोमुख्य the codec is connected to is teared करोwn and/or any other hardware
 * reset condition is निश्चितed.
 *
 * The codec's own घातer saving features are enabled in the suspend callback,
 * and all रेजिस्टरs are written back to the hardware when resuming.
 */

अटल पूर्णांक cs4270_soc_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs4270_निजी *cs4270 = snd_soc_component_get_drvdata(component);
	पूर्णांक reg, ret;

	reg = snd_soc_component_पढ़ो(component, CS4270_PWRCTL) | CS4270_PWRCTL_PDN_ALL;
	अगर (reg < 0)
		वापस reg;

	ret = snd_soc_component_ग_लिखो(component, CS4270_PWRCTL, reg);
	अगर (ret < 0)
		वापस ret;

	regulator_bulk_disable(ARRAY_SIZE(cs4270->supplies),
			       cs4270->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक cs4270_soc_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs4270_निजी *cs4270 = snd_soc_component_get_drvdata(component);
	पूर्णांक reg, ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(cs4270->supplies),
				    cs4270->supplies);
	अगर (ret != 0)
		वापस ret;

	/* In हाल the device was put to hard reset during sleep, we need to
	 * रुको 500ns here beक्रमe any I2C communication. */
	ndelay(500);

	/* first restore the entire रेजिस्टर cache ... */
	regcache_sync(cs4270->regmap);

	/* ... then disable the घातer-करोwn bits */
	reg = snd_soc_component_पढ़ो(component, CS4270_PWRCTL);
	reg &= ~CS4270_PWRCTL_PDN_ALL;

	वापस snd_soc_component_ग_लिखो(component, CS4270_PWRCTL, reg);
पूर्ण
#अन्यथा
#घोषणा cs4270_soc_suspend	शून्य
#घोषणा cs4270_soc_resume	शून्य
#पूर्ण_अगर /* CONFIG_PM */

/*
 * ASoC codec driver काष्ठाure
 */
अटल स्थिर काष्ठा snd_soc_component_driver soc_component_device_cs4270 = अणु
	.probe			= cs4270_probe,
	.हटाओ			= cs4270_हटाओ,
	.suspend		= cs4270_soc_suspend,
	.resume			= cs4270_soc_resume,
	.controls		= cs4270_snd_controls,
	.num_controls		= ARRAY_SIZE(cs4270_snd_controls),
	.dapm_widमाला_लो		= cs4270_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs4270_dapm_widमाला_लो),
	.dapm_routes		= cs4270_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(cs4270_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

/*
 * cs4270_of_match - the device tree bindings
 */
अटल स्थिर काष्ठा of_device_id cs4270_of_match[] = अणु
	अणु .compatible = "cirrus,cs4270", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cs4270_of_match);

अटल स्थिर काष्ठा regmap_config cs4270_regmap = अणु
	.reg_bits =		8,
	.val_bits =		8,
	.max_रेजिस्टर =		CS4270_LASTREG,
	.reg_शेषs =		cs4270_reg_शेषs,
	.num_reg_शेषs =	ARRAY_SIZE(cs4270_reg_शेषs),
	.cache_type =		REGCACHE_RBTREE,
	.ग_लिखो_flag_mask =	CS4270_I2C_INCR,

	.पढ़ोable_reg =		cs4270_reg_is_पढ़ोable,
	.अस्थिर_reg =		cs4270_reg_is_अस्थिर,
पूर्ण;

/**
 * cs4270_i2c_हटाओ - deinitialize the I2C पूर्णांकerface of the CS4270
 * @i2c_client: the I2C client object
 *
 * This function माला_दो the chip पूर्णांकo low घातer mode when the i2c device
 * is हटाओd.
 */
अटल पूर्णांक cs4270_i2c_हटाओ(काष्ठा i2c_client *i2c_client)
अणु
	काष्ठा cs4270_निजी *cs4270 = i2c_get_clientdata(i2c_client);

	gpiod_set_value_cansleep(cs4270->reset_gpio, 0);

	वापस 0;
पूर्ण

/**
 * cs4270_i2c_probe - initialize the I2C पूर्णांकerface of the CS4270
 * @i2c_client: the I2C client object
 * @id: the I2C device ID (ignored)
 *
 * This function is called whenever the I2C subप्रणाली finds a device that
 * matches the device ID given via a prior call to i2c_add_driver().
 */
अटल पूर्णांक cs4270_i2c_probe(काष्ठा i2c_client *i2c_client,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs4270_निजी *cs4270;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, i;

	cs4270 = devm_kzalloc(&i2c_client->dev, माप(काष्ठा cs4270_निजी),
			      GFP_KERNEL);
	अगर (!cs4270)
		वापस -ENOMEM;

	/* get the घातer supply regulators */
	क्रम (i = 0; i < ARRAY_SIZE(supply_names); i++)
		cs4270->supplies[i].supply = supply_names[i];

	ret = devm_regulator_bulk_get(&i2c_client->dev,
				      ARRAY_SIZE(cs4270->supplies),
				      cs4270->supplies);
	अगर (ret < 0)
		वापस ret;

	/* reset the device */
	cs4270->reset_gpio = devm_gpiod_get_optional(&i2c_client->dev, "reset",
						     GPIOD_OUT_LOW);
	अगर (IS_ERR(cs4270->reset_gpio)) अणु
		dev_dbg(&i2c_client->dev, "Error getting CS4270 reset GPIO\n");
		वापस PTR_ERR(cs4270->reset_gpio);
	पूर्ण

	अगर (cs4270->reset_gpio) अणु
		dev_dbg(&i2c_client->dev, "Found reset GPIO\n");
		gpiod_set_value_cansleep(cs4270->reset_gpio, 1);
	पूर्ण

	/* Sleep 500ns beक्रमe i2c communications */
	ndelay(500);

	cs4270->regmap = devm_regmap_init_i2c(i2c_client, &cs4270_regmap);
	अगर (IS_ERR(cs4270->regmap))
		वापस PTR_ERR(cs4270->regmap);

	/* Verअगरy that we have a CS4270 */
	ret = regmap_पढ़ो(cs4270->regmap, CS4270_CHIPID, &val);
	अगर (ret < 0) अणु
		dev_err(&i2c_client->dev, "failed to read i2c at addr %X\n",
		       i2c_client->addr);
		वापस ret;
	पूर्ण
	/* The top four bits of the chip ID should be 1100. */
	अगर ((val & 0xF0) != 0xC0) अणु
		dev_err(&i2c_client->dev, "device at addr %X is not a CS4270\n",
		       i2c_client->addr);
		वापस -ENODEV;
	पूर्ण

	dev_info(&i2c_client->dev, "found device at i2c address %X\n",
		i2c_client->addr);
	dev_info(&i2c_client->dev, "hardware revision %X\n", val & 0xF);

	i2c_set_clientdata(i2c_client, cs4270);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c_client->dev,
			&soc_component_device_cs4270, &cs4270_dai, 1);
	वापस ret;
पूर्ण

/*
 * cs4270_id - I2C device IDs supported by this driver
 */
अटल स्थिर काष्ठा i2c_device_id cs4270_id[] = अणु
	अणु"cs4270", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cs4270_id);

/*
 * cs4270_i2c_driver - I2C device identअगरication
 *
 * This काष्ठाure tells the I2C subप्रणाली how to identअगरy and support a
 * given I2C device type.
 */
अटल काष्ठा i2c_driver cs4270_i2c_driver = अणु
	.driver = अणु
		.name = "cs4270",
		.of_match_table = cs4270_of_match,
	पूर्ण,
	.id_table = cs4270_id,
	.probe = cs4270_i2c_probe,
	.हटाओ = cs4270_i2c_हटाओ,
पूर्ण;

module_i2c_driver(cs4270_i2c_driver);

MODULE_AUTHOR("Timur Tabi <timur@freescale.com>");
MODULE_DESCRIPTION("Cirrus Logic CS4270 ALSA SoC Codec Driver");
MODULE_LICENSE("GPL");
