<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CS4271 ASoC codec driver
 *
 * Copyright (c) 2010 Alexander Sverdlin <subaparts@yandex.ru>
 *
 * This driver support CS4271 codec being master or slave, working
 * in control port mode, connected either via SPI or I2C.
 * The data क्रमmat accepted is I2S or left-justअगरied.
 * DAPM support not implemented.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/cs4271.h>
#समावेश "cs4271.h"

#घोषणा CS4271_PCM_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | \
			    SNDRV_PCM_FMTBIT_S24_LE | \
			    SNDRV_PCM_FMTBIT_S32_LE)
#घोषणा CS4271_PCM_RATES SNDRV_PCM_RATE_8000_192000

/*
 * CS4271 रेजिस्टरs
 */
#घोषणा CS4271_MODE1	0x01	/* Mode Control 1 */
#घोषणा CS4271_DACCTL	0x02	/* DAC Control */
#घोषणा CS4271_DACVOL	0x03	/* DAC Volume & Mixing Control */
#घोषणा CS4271_VOLA	0x04	/* DAC Channel A Volume Control */
#घोषणा CS4271_VOLB	0x05	/* DAC Channel B Volume Control */
#घोषणा CS4271_ADCCTL	0x06	/* ADC Control */
#घोषणा CS4271_MODE2	0x07	/* Mode Control 2 */
#घोषणा CS4271_CHIPID	0x08	/* Chip ID */

#घोषणा CS4271_FIRSTREG	CS4271_MODE1
#घोषणा CS4271_LASTREG	CS4271_MODE2
#घोषणा CS4271_NR_REGS	((CS4271_LASTREG & 0xFF) + 1)

/* Bit masks क्रम the CS4271 रेजिस्टरs */
#घोषणा CS4271_MODE1_MODE_MASK	0xC0
#घोषणा CS4271_MODE1_MODE_1X	0x00
#घोषणा CS4271_MODE1_MODE_2X	0x80
#घोषणा CS4271_MODE1_MODE_4X	0xC0

#घोषणा CS4271_MODE1_DIV_MASK	0x30
#घोषणा CS4271_MODE1_DIV_1	0x00
#घोषणा CS4271_MODE1_DIV_15	0x10
#घोषणा CS4271_MODE1_DIV_2	0x20
#घोषणा CS4271_MODE1_DIV_3	0x30

#घोषणा CS4271_MODE1_MASTER	0x08

#घोषणा CS4271_MODE1_DAC_DIF_MASK	0x07
#घोषणा CS4271_MODE1_DAC_DIF_LJ		0x00
#घोषणा CS4271_MODE1_DAC_DIF_I2S	0x01
#घोषणा CS4271_MODE1_DAC_DIF_RJ16	0x02
#घोषणा CS4271_MODE1_DAC_DIF_RJ24	0x03
#घोषणा CS4271_MODE1_DAC_DIF_RJ20	0x04
#घोषणा CS4271_MODE1_DAC_DIF_RJ18	0x05

#घोषणा CS4271_DACCTL_AMUTE	0x80
#घोषणा CS4271_DACCTL_IF_SLOW	0x40

#घोषणा CS4271_DACCTL_DEM_MASK	0x30
#घोषणा CS4271_DACCTL_DEM_DIS	0x00
#घोषणा CS4271_DACCTL_DEM_441	0x10
#घोषणा CS4271_DACCTL_DEM_48	0x20
#घोषणा CS4271_DACCTL_DEM_32	0x30

#घोषणा CS4271_DACCTL_SVRU	0x08
#घोषणा CS4271_DACCTL_SRD	0x04
#घोषणा CS4271_DACCTL_INVA	0x02
#घोषणा CS4271_DACCTL_INVB	0x01

#घोषणा CS4271_DACVOL_BEQUA	0x40
#घोषणा CS4271_DACVOL_SOFT	0x20
#घोषणा CS4271_DACVOL_ZEROC	0x10

#घोषणा CS4271_DACVOL_ATAPI_MASK	0x0F
#घोषणा CS4271_DACVOL_ATAPI_M_M		0x00
#घोषणा CS4271_DACVOL_ATAPI_M_BR	0x01
#घोषणा CS4271_DACVOL_ATAPI_M_BL	0x02
#घोषणा CS4271_DACVOL_ATAPI_M_BLR2	0x03
#घोषणा CS4271_DACVOL_ATAPI_AR_M	0x04
#घोषणा CS4271_DACVOL_ATAPI_AR_BR	0x05
#घोषणा CS4271_DACVOL_ATAPI_AR_BL	0x06
#घोषणा CS4271_DACVOL_ATAPI_AR_BLR2	0x07
#घोषणा CS4271_DACVOL_ATAPI_AL_M	0x08
#घोषणा CS4271_DACVOL_ATAPI_AL_BR	0x09
#घोषणा CS4271_DACVOL_ATAPI_AL_BL	0x0A
#घोषणा CS4271_DACVOL_ATAPI_AL_BLR2	0x0B
#घोषणा CS4271_DACVOL_ATAPI_ALR2_M	0x0C
#घोषणा CS4271_DACVOL_ATAPI_ALR2_BR	0x0D
#घोषणा CS4271_DACVOL_ATAPI_ALR2_BL	0x0E
#घोषणा CS4271_DACVOL_ATAPI_ALR2_BLR2	0x0F

#घोषणा CS4271_VOLA_MUTE	0x80
#घोषणा CS4271_VOLA_VOL_MASK	0x7F
#घोषणा CS4271_VOLB_MUTE	0x80
#घोषणा CS4271_VOLB_VOL_MASK	0x7F

#घोषणा CS4271_ADCCTL_DITHER16	0x20

#घोषणा CS4271_ADCCTL_ADC_DIF_MASK	0x10
#घोषणा CS4271_ADCCTL_ADC_DIF_LJ	0x00
#घोषणा CS4271_ADCCTL_ADC_DIF_I2S	0x10

#घोषणा CS4271_ADCCTL_MUTEA	0x08
#घोषणा CS4271_ADCCTL_MUTEB	0x04
#घोषणा CS4271_ADCCTL_HPFDA	0x02
#घोषणा CS4271_ADCCTL_HPFDB	0x01

#घोषणा CS4271_MODE2_LOOP	0x10
#घोषणा CS4271_MODE2_MUTECAEQUB	0x08
#घोषणा CS4271_MODE2_FREEZE	0x04
#घोषणा CS4271_MODE2_CPEN	0x02
#घोषणा CS4271_MODE2_PDN	0x01

#घोषणा CS4271_CHIPID_PART_MASK	0xF0
#घोषणा CS4271_CHIPID_REV_MASK	0x0F

/*
 * Default CS4271 घातer-up configuration
 * Array contains non-existing in hw रेजिस्टर at address 0
 * Array करो not include Chip ID, as codec driver करोes not use
 * रेजिस्टरs पढ़ो operations at all
 */
अटल स्थिर काष्ठा reg_शेष cs4271_reg_शेषs[] = अणु
	अणु CS4271_MODE1,		0, पूर्ण,
	अणु CS4271_DACCTL,	CS4271_DACCTL_AMUTE, पूर्ण,
	अणु CS4271_DACVOL,	CS4271_DACVOL_SOFT | CS4271_DACVOL_ATAPI_AL_BR, पूर्ण,
	अणु CS4271_VOLA,		0, पूर्ण,
	अणु CS4271_VOLB,		0, पूर्ण,
	अणु CS4271_ADCCTL,	0, पूर्ण,
	अणु CS4271_MODE2,		0, पूर्ण,
पूर्ण;

अटल bool cs4271_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == CS4271_CHIPID;
पूर्ण

अटल स्थिर अक्षर * स्थिर supply_names[] = अणु
	"vd", "vl", "va"
पूर्ण;

काष्ठा cs4271_निजी अणु
	अचिन्हित पूर्णांक			mclk;
	bool				master;
	bool				deemph;
	काष्ठा regmap			*regmap;
	/* Current sample rate क्रम de-emphasis control */
	पूर्णांक				rate;
	/* GPIO driving Reset pin, अगर any */
	पूर्णांक				gpio_nreset;
	/* GPIO that disable serial bus, अगर any */
	पूर्णांक				gpio_disable;
	/* enable soft reset workaround */
	bool				enable_soft_reset;
	काष्ठा regulator_bulk_data      supplies[ARRAY_SIZE(supply_names)];
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cs4271_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("AINA"),
SND_SOC_DAPM_INPUT("AINB"),

SND_SOC_DAPM_OUTPUT("AOUTA+"),
SND_SOC_DAPM_OUTPUT("AOUTA-"),
SND_SOC_DAPM_OUTPUT("AOUTB+"),
SND_SOC_DAPM_OUTPUT("AOUTB-"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs4271_dapm_routes[] = अणु
	अणु "Capture", शून्य, "AINA" पूर्ण,
	अणु "Capture", शून्य, "AINB" पूर्ण,

	अणु "AOUTA+", शून्य, "Playback" पूर्ण,
	अणु "AOUTA-", शून्य, "Playback" पूर्ण,
	अणु "AOUTB+", शून्य, "Playback" पूर्ण,
	अणु "AOUTB-", शून्य, "Playback" पूर्ण,
पूर्ण;

/*
 * @freq is the desired MCLK rate
 * MCLK rate should (c) be the sample rate, multiplied by one of the
 * ratios listed in cs4271_mclk_fs_ratios table
 */
अटल पूर्णांक cs4271_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs4271_निजी *cs4271 = snd_soc_component_get_drvdata(component);

	cs4271->mclk = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक cs4271_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			      अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs4271_निजी *cs4271 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret;

	चयन (क्रमmat & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		cs4271->master = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		cs4271->master = true;
		val |= CS4271_MODE1_MASTER;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI format\n");
		वापस -EINVAL;
	पूर्ण

	चयन (क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_LEFT_J:
		val |= CS4271_MODE1_DAC_DIF_LJ;
		ret = regmap_update_bits(cs4271->regmap, CS4271_ADCCTL,
			CS4271_ADCCTL_ADC_DIF_MASK, CS4271_ADCCTL_ADC_DIF_LJ);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		val |= CS4271_MODE1_DAC_DIF_I2S;
		ret = regmap_update_bits(cs4271->regmap, CS4271_ADCCTL,
			CS4271_ADCCTL_ADC_DIF_MASK, CS4271_ADCCTL_ADC_DIF_I2S);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI format\n");
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(cs4271->regmap, CS4271_MODE1,
		CS4271_MODE1_DAC_DIF_MASK | CS4271_MODE1_MASTER, val);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक cs4271_deemph[] = अणु0, 44100, 48000, 32000पूर्ण;

अटल पूर्णांक cs4271_set_deemph(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs4271_निजी *cs4271 = snd_soc_component_get_drvdata(component);
	पूर्णांक i, ret;
	पूर्णांक val = CS4271_DACCTL_DEM_DIS;

	अगर (cs4271->deemph) अणु
		/* Find बंदst de-emphasis freq */
		val = 1;
		क्रम (i = 2; i < ARRAY_SIZE(cs4271_deemph); i++)
			अगर (असल(cs4271_deemph[i] - cs4271->rate) <
			    असल(cs4271_deemph[val] - cs4271->rate))
				val = i;
		val <<= 4;
	पूर्ण

	ret = regmap_update_bits(cs4271->regmap, CS4271_DACCTL,
		CS4271_DACCTL_DEM_MASK, val);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक cs4271_get_deemph(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा cs4271_निजी *cs4271 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = cs4271->deemph;
	वापस 0;
पूर्ण

अटल पूर्णांक cs4271_put_deemph(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा cs4271_निजी *cs4271 = snd_soc_component_get_drvdata(component);

	cs4271->deemph = ucontrol->value.पूर्णांकeger.value[0];
	वापस cs4271_set_deemph(component);
पूर्ण

काष्ठा cs4271_clk_cfg अणु
	bool		master;		/* codec mode */
	u8		speed_mode;	/* codec speed mode: 1x, 2x, 4x */
	अचिन्हित लघु	ratio;		/* MCLK / sample rate */
	u8		ratio_mask;	/* ratio bit mask क्रम Master mode */
पूर्ण;

अटल काष्ठा cs4271_clk_cfg cs4271_clk_tab[] = अणु
	अणु1, CS4271_MODE1_MODE_1X, 256,  CS4271_MODE1_DIV_1पूर्ण,
	अणु1, CS4271_MODE1_MODE_1X, 384,  CS4271_MODE1_DIV_15पूर्ण,
	अणु1, CS4271_MODE1_MODE_1X, 512,  CS4271_MODE1_DIV_2पूर्ण,
	अणु1, CS4271_MODE1_MODE_1X, 768,  CS4271_MODE1_DIV_3पूर्ण,
	अणु1, CS4271_MODE1_MODE_2X, 128,  CS4271_MODE1_DIV_1पूर्ण,
	अणु1, CS4271_MODE1_MODE_2X, 192,  CS4271_MODE1_DIV_15पूर्ण,
	अणु1, CS4271_MODE1_MODE_2X, 256,  CS4271_MODE1_DIV_2पूर्ण,
	अणु1, CS4271_MODE1_MODE_2X, 384,  CS4271_MODE1_DIV_3पूर्ण,
	अणु1, CS4271_MODE1_MODE_4X, 64,   CS4271_MODE1_DIV_1पूर्ण,
	अणु1, CS4271_MODE1_MODE_4X, 96,   CS4271_MODE1_DIV_15पूर्ण,
	अणु1, CS4271_MODE1_MODE_4X, 128,  CS4271_MODE1_DIV_2पूर्ण,
	अणु1, CS4271_MODE1_MODE_4X, 192,  CS4271_MODE1_DIV_3पूर्ण,
	अणु0, CS4271_MODE1_MODE_1X, 256,  CS4271_MODE1_DIV_1पूर्ण,
	अणु0, CS4271_MODE1_MODE_1X, 384,  CS4271_MODE1_DIV_1पूर्ण,
	अणु0, CS4271_MODE1_MODE_1X, 512,  CS4271_MODE1_DIV_1पूर्ण,
	अणु0, CS4271_MODE1_MODE_1X, 768,  CS4271_MODE1_DIV_2पूर्ण,
	अणु0, CS4271_MODE1_MODE_1X, 1024, CS4271_MODE1_DIV_2पूर्ण,
	अणु0, CS4271_MODE1_MODE_2X, 128,  CS4271_MODE1_DIV_1पूर्ण,
	अणु0, CS4271_MODE1_MODE_2X, 192,  CS4271_MODE1_DIV_1पूर्ण,
	अणु0, CS4271_MODE1_MODE_2X, 256,  CS4271_MODE1_DIV_1पूर्ण,
	अणु0, CS4271_MODE1_MODE_2X, 384,  CS4271_MODE1_DIV_2पूर्ण,
	अणु0, CS4271_MODE1_MODE_2X, 512,  CS4271_MODE1_DIV_2पूर्ण,
	अणु0, CS4271_MODE1_MODE_4X, 64,   CS4271_MODE1_DIV_1पूर्ण,
	अणु0, CS4271_MODE1_MODE_4X, 96,   CS4271_MODE1_DIV_1पूर्ण,
	अणु0, CS4271_MODE1_MODE_4X, 128,  CS4271_MODE1_DIV_1पूर्ण,
	अणु0, CS4271_MODE1_MODE_4X, 192,  CS4271_MODE1_DIV_2पूर्ण,
	अणु0, CS4271_MODE1_MODE_4X, 256,  CS4271_MODE1_DIV_2पूर्ण,
पूर्ण;

#घोषणा CS4271_NR_RATIOS ARRAY_SIZE(cs4271_clk_tab)

अटल पूर्णांक cs4271_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs4271_निजी *cs4271 = snd_soc_component_get_drvdata(component);
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक ratio, val;

	अगर (cs4271->enable_soft_reset) अणु
		/*
		 * Put the codec in soft reset and back again in हाल it's not
		 * currently streaming data. This way of bringing the codec in
		 * sync to the current घड़ीs is not explicitly करोcumented in
		 * the data sheet, but it seems to work fine, and in contrast
		 * to a पढ़ो hardware reset, we करोn't have to sync back all
		 * रेजिस्टरs every समय.
		 */

		अगर ((substream->stream == SNDRV_PCM_STREAM_PLAYBACK &&
		     !snd_soc_dai_stream_active(dai, SNDRV_PCM_STREAM_CAPTURE)) ||
		    (substream->stream == SNDRV_PCM_STREAM_CAPTURE &&
		     !snd_soc_dai_stream_active(dai, SNDRV_PCM_STREAM_PLAYBACK))) अणु
			ret = regmap_update_bits(cs4271->regmap, CS4271_MODE2,
						 CS4271_MODE2_PDN,
						 CS4271_MODE2_PDN);
			अगर (ret < 0)
				वापस ret;

			ret = regmap_update_bits(cs4271->regmap, CS4271_MODE2,
						 CS4271_MODE2_PDN, 0);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	cs4271->rate = params_rate(params);

	/* Configure DAC */
	अगर (cs4271->rate < 50000)
		val = CS4271_MODE1_MODE_1X;
	अन्यथा अगर (cs4271->rate < 100000)
		val = CS4271_MODE1_MODE_2X;
	अन्यथा
		val = CS4271_MODE1_MODE_4X;

	ratio = cs4271->mclk / cs4271->rate;
	क्रम (i = 0; i < CS4271_NR_RATIOS; i++)
		अगर ((cs4271_clk_tab[i].master == cs4271->master) &&
		    (cs4271_clk_tab[i].speed_mode == val) &&
		    (cs4271_clk_tab[i].ratio == ratio))
			अवरोध;

	अगर (i == CS4271_NR_RATIOS) अणु
		dev_err(component->dev, "Invalid sample rate\n");
		वापस -EINVAL;
	पूर्ण

	val |= cs4271_clk_tab[i].ratio_mask;

	ret = regmap_update_bits(cs4271->regmap, CS4271_MODE1,
		CS4271_MODE1_MODE_MASK | CS4271_MODE1_DIV_MASK, val);
	अगर (ret < 0)
		वापस ret;

	वापस cs4271_set_deemph(component);
पूर्ण

अटल पूर्णांक cs4271_mute_stream(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs4271_निजी *cs4271 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;
	पूर्णांक val_a = 0;
	पूर्णांक val_b = 0;

	अगर (stream != SNDRV_PCM_STREAM_PLAYBACK)
		वापस 0;

	अगर (mute) अणु
		val_a = CS4271_VOLA_MUTE;
		val_b = CS4271_VOLB_MUTE;
	पूर्ण

	ret = regmap_update_bits(cs4271->regmap, CS4271_VOLA,
				 CS4271_VOLA_MUTE, val_a);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(cs4271->regmap, CS4271_VOLB,
				 CS4271_VOLB_MUTE, val_b);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/* CS4271 controls */
अटल DECLARE_TLV_DB_SCALE(cs4271_dac_tlv, -12700, 100, 0);

अटल स्थिर काष्ठा snd_kcontrol_new cs4271_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("Master Playback Volume", CS4271_VOLA, CS4271_VOLB,
		0, 0x7F, 1, cs4271_dac_tlv),
	SOC_SINGLE("Digital Loopback Switch", CS4271_MODE2, 4, 1, 0),
	SOC_SINGLE("Soft Ramp Switch", CS4271_DACVOL, 5, 1, 0),
	SOC_SINGLE("Zero Cross Switch", CS4271_DACVOL, 4, 1, 0),
	SOC_SINGLE_BOOL_EXT("De-emphasis Switch", 0,
		cs4271_get_deemph, cs4271_put_deemph),
	SOC_SINGLE("Auto-Mute Switch", CS4271_DACCTL, 7, 1, 0),
	SOC_SINGLE("Slow Roll Off Filter Switch", CS4271_DACCTL, 6, 1, 0),
	SOC_SINGLE("Soft Volume Ramp-Up Switch", CS4271_DACCTL, 3, 1, 0),
	SOC_SINGLE("Soft Ramp-Down Switch", CS4271_DACCTL, 2, 1, 0),
	SOC_SINGLE("Left Channel Inversion Switch", CS4271_DACCTL, 1, 1, 0),
	SOC_SINGLE("Right Channel Inversion Switch", CS4271_DACCTL, 0, 1, 0),
	SOC_DOUBLE("Master Capture Switch", CS4271_ADCCTL, 3, 2, 1, 1),
	SOC_SINGLE("Dither 16-Bit Data Switch", CS4271_ADCCTL, 5, 1, 0),
	SOC_DOUBLE("High Pass Filter Switch", CS4271_ADCCTL, 1, 0, 1, 1),
	SOC_DOUBLE_R("Master Playback Switch", CS4271_VOLA, CS4271_VOLB,
		7, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops cs4271_dai_ops = अणु
	.hw_params	= cs4271_hw_params,
	.set_sysclk	= cs4271_set_dai_sysclk,
	.set_fmt	= cs4271_set_dai_fmt,
	.mute_stream	= cs4271_mute_stream,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs4271_dai = अणु
	.name = "cs4271-hifi",
	.playback = अणु
		.stream_name	= "Playback",
		.channels_min	= 2,
		.channels_max	= 2,
		.rates		= CS4271_PCM_RATES,
		.क्रमmats	= CS4271_PCM_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name	= "Capture",
		.channels_min	= 2,
		.channels_max	= 2,
		.rates		= CS4271_PCM_RATES,
		.क्रमmats	= CS4271_PCM_FORMATS,
	पूर्ण,
	.ops = &cs4271_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक cs4271_reset(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs4271_निजी *cs4271 = snd_soc_component_get_drvdata(component);

	अगर (gpio_is_valid(cs4271->gpio_nreset)) अणु
		gpio_direction_output(cs4271->gpio_nreset, 0);
		mdelay(1);
		gpio_set_value(cs4271->gpio_nreset, 1);
		mdelay(1);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक cs4271_soc_suspend(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;
	काष्ठा cs4271_निजी *cs4271 = snd_soc_component_get_drvdata(component);

	/* Set घातer-करोwn bit */
	ret = regmap_update_bits(cs4271->regmap, CS4271_MODE2,
				 CS4271_MODE2_PDN, CS4271_MODE2_PDN);
	अगर (ret < 0)
		वापस ret;

	regcache_mark_dirty(cs4271->regmap);
	regulator_bulk_disable(ARRAY_SIZE(cs4271->supplies), cs4271->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक cs4271_soc_resume(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;
	काष्ठा cs4271_निजी *cs4271 = snd_soc_component_get_drvdata(component);

	ret = regulator_bulk_enable(ARRAY_SIZE(cs4271->supplies),
				    cs4271->supplies);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Do a proper reset after घातer up */
	cs4271_reset(component);

	/* Restore codec state */
	ret = regcache_sync(cs4271->regmap);
	अगर (ret < 0)
		वापस ret;

	/* then disable the घातer-करोwn bit */
	ret = regmap_update_bits(cs4271->regmap, CS4271_MODE2,
				 CS4271_MODE2_PDN, 0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा cs4271_soc_suspend	शून्य
#घोषणा cs4271_soc_resume	शून्य
#पूर्ण_अगर /* CONFIG_PM */

#अगर_घोषित CONFIG_OF
स्थिर काष्ठा of_device_id cs4271_dt_ids[] = अणु
	अणु .compatible = "cirrus,cs4271", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cs4271_dt_ids);
EXPORT_SYMBOL_GPL(cs4271_dt_ids);
#पूर्ण_अगर

अटल पूर्णांक cs4271_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs4271_निजी *cs4271 = snd_soc_component_get_drvdata(component);
	काष्ठा cs4271_platक्रमm_data *cs4271plat = component->dev->platक्रमm_data;
	पूर्णांक ret;
	bool amutec_eq_bmutec = false;

#अगर_घोषित CONFIG_OF
	अगर (of_match_device(cs4271_dt_ids, component->dev)) अणु
		अगर (of_get_property(component->dev->of_node,
				     "cirrus,amutec-eq-bmutec", शून्य))
			amutec_eq_bmutec = true;

		अगर (of_get_property(component->dev->of_node,
				     "cirrus,enable-soft-reset", शून्य))
			cs4271->enable_soft_reset = true;
	पूर्ण
#पूर्ण_अगर

	ret = regulator_bulk_enable(ARRAY_SIZE(cs4271->supplies),
				    cs4271->supplies);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (cs4271plat) अणु
		amutec_eq_bmutec = cs4271plat->amutec_eq_bmutec;
		cs4271->enable_soft_reset = cs4271plat->enable_soft_reset;
	पूर्ण

	/* Reset codec */
	cs4271_reset(component);

	ret = regcache_sync(cs4271->regmap);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(cs4271->regmap, CS4271_MODE2,
				 CS4271_MODE2_PDN | CS4271_MODE2_CPEN,
				 CS4271_MODE2_PDN | CS4271_MODE2_CPEN);
	अगर (ret < 0)
		वापस ret;
	ret = regmap_update_bits(cs4271->regmap, CS4271_MODE2,
				 CS4271_MODE2_PDN, 0);
	अगर (ret < 0)
		वापस ret;
	/* Power-up sequence requires 85 uS */
	udelay(85);

	अगर (amutec_eq_bmutec)
		regmap_update_bits(cs4271->regmap, CS4271_MODE2,
				   CS4271_MODE2_MUTECAEQUB,
				   CS4271_MODE2_MUTECAEQUB);

	वापस 0;
पूर्ण

अटल व्योम cs4271_component_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs4271_निजी *cs4271 = snd_soc_component_get_drvdata(component);

	अगर (gpio_is_valid(cs4271->gpio_nreset))
		/* Set codec to the reset state */
		gpio_set_value(cs4271->gpio_nreset, 0);

	regcache_mark_dirty(cs4271->regmap);
	regulator_bulk_disable(ARRAY_SIZE(cs4271->supplies), cs4271->supplies);
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_cs4271 = अणु
	.probe			= cs4271_component_probe,
	.हटाओ			= cs4271_component_हटाओ,
	.suspend		= cs4271_soc_suspend,
	.resume			= cs4271_soc_resume,
	.controls		= cs4271_snd_controls,
	.num_controls		= ARRAY_SIZE(cs4271_snd_controls),
	.dapm_widमाला_लो		= cs4271_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs4271_dapm_widमाला_लो),
	.dapm_routes		= cs4271_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(cs4271_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक cs4271_common_probe(काष्ठा device *dev,
			       काष्ठा cs4271_निजी **c)
अणु
	काष्ठा cs4271_platक्रमm_data *cs4271plat = dev->platक्रमm_data;
	काष्ठा cs4271_निजी *cs4271;
	पूर्णांक i, ret;

	cs4271 = devm_kzalloc(dev, माप(*cs4271), GFP_KERNEL);
	अगर (!cs4271)
		वापस -ENOMEM;

	अगर (of_match_device(cs4271_dt_ids, dev))
		cs4271->gpio_nreset =
			of_get_named_gpio(dev->of_node, "reset-gpio", 0);

	अगर (cs4271plat)
		cs4271->gpio_nreset = cs4271plat->gpio_nreset;

	अगर (gpio_is_valid(cs4271->gpio_nreset)) अणु
		ret = devm_gpio_request(dev, cs4271->gpio_nreset,
					"CS4271 Reset");
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(supply_names); i++)
		cs4271->supplies[i].supply = supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(cs4271->supplies),
					cs4271->supplies);

	अगर (ret < 0) अणु
		dev_err(dev, "Failed to get regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	*c = cs4271;
	वापस 0;
पूर्ण

स्थिर काष्ठा regmap_config cs4271_regmap_config = अणु
	.max_रेजिस्टर = CS4271_LASTREG,

	.reg_शेषs = cs4271_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(cs4271_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = cs4271_अस्थिर_reg,
पूर्ण;
EXPORT_SYMBOL_GPL(cs4271_regmap_config);

पूर्णांक cs4271_probe(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	काष्ठा cs4271_निजी *cs4271;
	पूर्णांक ret;

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	ret = cs4271_common_probe(dev, &cs4271);
	अगर (ret < 0)
		वापस ret;

	dev_set_drvdata(dev, cs4271);
	cs4271->regmap = regmap;

	वापस devm_snd_soc_रेजिस्टर_component(dev, &soc_component_dev_cs4271,
					       &cs4271_dai, 1);
पूर्ण
EXPORT_SYMBOL_GPL(cs4271_probe);

MODULE_AUTHOR("Alexander Sverdlin <subaparts@yandex.ru>");
MODULE_DESCRIPTION("Cirrus Logic CS4271 ALSA SoC Codec Driver");
MODULE_LICENSE("GPL");
