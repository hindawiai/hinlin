<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Audio driver क्रम AK4458 DAC
//
// Copyright (C) 2016 Asahi Kasei Microdevices Corporation
// Copyright 2018 NXP

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>

#समावेश "ak4458.h"

#घोषणा AK4458_NUM_SUPPLIES 2
अटल स्थिर अक्षर *ak4458_supply_names[AK4458_NUM_SUPPLIES] = अणु
	"DVDD",
	"AVDD",
पूर्ण;

क्रमागत ak4458_type अणु
	AK4458 = 0,
	AK4497 = 1,
पूर्ण;

काष्ठा ak4458_drvdata अणु
	काष्ठा snd_soc_dai_driver *dai_drv;
	स्थिर काष्ठा snd_soc_component_driver *comp_drv;
	क्रमागत ak4458_type type;
पूर्ण;

/* AK4458 Codec Private Data */
काष्ठा ak4458_priv अणु
	काष्ठा regulator_bulk_data supplies[AK4458_NUM_SUPPLIES];
	स्थिर काष्ठा ak4458_drvdata *drvdata;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *reset_gpiod;
	काष्ठा gpio_desc *mute_gpiod;
	पूर्णांक digfil;	/* SSLOW, SD, SLOW bits */
	पूर्णांक fs;		/* sampling rate */
	पूर्णांक fmt;
	पूर्णांक slots;
	पूर्णांक slot_width;
	u32 dsd_path;    /* For ak4497 */
पूर्ण;

अटल स्थिर काष्ठा reg_शेष ak4458_reg_शेषs[] = अणु
	अणु 0x00, 0x0C पूर्ण,	/*	0x00	AK4458_00_CONTROL1	*/
	अणु 0x01, 0x22 पूर्ण,	/*	0x01	AK4458_01_CONTROL2	*/
	अणु 0x02, 0x00 पूर्ण,	/*	0x02	AK4458_02_CONTROL3	*/
	अणु 0x03, 0xFF पूर्ण,	/*	0x03	AK4458_03_LCHATT	*/
	अणु 0x04, 0xFF पूर्ण,	/*	0x04	AK4458_04_RCHATT	*/
	अणु 0x05, 0x00 पूर्ण,	/*	0x05	AK4458_05_CONTROL4	*/
	अणु 0x06, 0x00 पूर्ण,	/*	0x06	AK4458_06_DSD1		*/
	अणु 0x07, 0x03 पूर्ण,	/*	0x07	AK4458_07_CONTROL5	*/
	अणु 0x08, 0x00 पूर्ण,	/*	0x08	AK4458_08_SOUND_CONTROL	*/
	अणु 0x09, 0x00 पूर्ण,	/*	0x09	AK4458_09_DSD2		*/
	अणु 0x0A, 0x0D पूर्ण,	/*	0x0A	AK4458_0A_CONTROL6	*/
	अणु 0x0B, 0x0C पूर्ण,	/*	0x0B	AK4458_0B_CONTROL7	*/
	अणु 0x0C, 0x00 पूर्ण,	/*	0x0C	AK4458_0C_CONTROL8	*/
	अणु 0x0D, 0x00 पूर्ण,	/*	0x0D	AK4458_0D_CONTROL9	*/
	अणु 0x0E, 0x50 पूर्ण,	/*	0x0E	AK4458_0E_CONTROL10	*/
	अणु 0x0F, 0xFF पूर्ण,	/*	0x0F	AK4458_0F_L2CHATT	*/
	अणु 0x10, 0xFF पूर्ण,	/*	0x10	AK4458_10_R2CHATT	*/
	अणु 0x11, 0xFF पूर्ण,	/*	0x11	AK4458_11_L3CHATT	*/
	अणु 0x12, 0xFF पूर्ण,	/*	0x12	AK4458_12_R3CHATT	*/
	अणु 0x13, 0xFF पूर्ण,	/*	0x13	AK4458_13_L4CHATT	*/
	अणु 0x14, 0xFF पूर्ण,	/*	0x14	AK4458_14_R4CHATT	*/
पूर्ण;

/*
 * Volume control:
 * from -127 to 0 dB in 0.5 dB steps (mute instead of -127.5 dB)
 */
अटल DECLARE_TLV_DB_SCALE(dac_tlv, -12750, 50, 1);

/*
 * DEM1 bit DEM0 bit Mode
 * 0 0 44.1kHz
 * 0 1 OFF (शेष)
 * 1 0 48kHz
 * 1 1 32kHz
 */
अटल स्थिर अक्षर * स्थिर ak4458_dem_select_texts[] = अणु
	"44.1kHz", "OFF", "48kHz", "32kHz"
पूर्ण;

/*
 * SSLOW, SD, SLOW bits Digital Filter Setting
 * 0, 0, 0 : Sharp Roll-Off Filter
 * 0, 0, 1 : Slow Roll-Off Filter
 * 0, 1, 0 : Short delay Sharp Roll-Off Filter
 * 0, 1, 1 : Short delay Slow Roll-Off Filter
 * 1, *, * : Super Slow Roll-Off Filter
 */
अटल स्थिर अक्षर * स्थिर ak4458_digfil_select_texts[] = अणु
	"Sharp Roll-Off Filter",
	"Slow Roll-Off Filter",
	"Short delay Sharp Roll-Off Filter",
	"Short delay Slow Roll-Off Filter",
	"Super Slow Roll-Off Filter"
पूर्ण;

/*
 * DZFB: Inverting Enable of DZF
 * 0: DZF goes H at Zero Detection
 * 1: DZF goes L at Zero Detection
 */
अटल स्थिर अक्षर * स्थिर ak4458_dzfb_select_texts[] = अणु"H", "L"पूर्ण;

/*
 * SC1-0 bits: Sound Mode Setting
 * 0 0 : Sound Mode 0
 * 0 1 : Sound Mode 1
 * 1 0 : Sound Mode 2
 * 1 1 : Reserved
 */
अटल स्थिर अक्षर * स्थिर ak4458_sc_select_texts[] = अणु
	"Sound Mode 0", "Sound Mode 1", "Sound Mode 2"
पूर्ण;

/* FIR2-0 bits: FIR Filter Mode Setting */
अटल स्थिर अक्षर * स्थिर ak4458_fir_select_texts[] = अणु
	"Mode 0", "Mode 1", "Mode 2", "Mode 3",
	"Mode 4", "Mode 5", "Mode 6", "Mode 7",
पूर्ण;

/* ATS1-0 bits Attenuation Speed */
अटल स्थिर अक्षर * स्थिर ak4458_ats_select_texts[] = अणु
	"4080/fs", "2040/fs", "510/fs", "255/fs",
पूर्ण;

/* DIF2 bit Audio Interface Format Setting(BICK fs) */
अटल स्थिर अक्षर * स्थिर ak4458_dअगर_select_texts[] = अणु"32fs,48fs", "64fs",पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत ak4458_dac1_dem_क्रमागत =
	SOC_ENUM_SINGLE(AK4458_01_CONTROL2, 1,
			ARRAY_SIZE(ak4458_dem_select_texts),
			ak4458_dem_select_texts);
अटल स्थिर काष्ठा soc_क्रमागत ak4458_dac2_dem_क्रमागत =
	SOC_ENUM_SINGLE(AK4458_0A_CONTROL6, 0,
			ARRAY_SIZE(ak4458_dem_select_texts),
			ak4458_dem_select_texts);
अटल स्थिर काष्ठा soc_क्रमागत ak4458_dac3_dem_क्रमागत =
	SOC_ENUM_SINGLE(AK4458_0E_CONTROL10, 4,
			ARRAY_SIZE(ak4458_dem_select_texts),
			ak4458_dem_select_texts);
अटल स्थिर काष्ठा soc_क्रमागत ak4458_dac4_dem_क्रमागत =
	SOC_ENUM_SINGLE(AK4458_0E_CONTROL10, 6,
			ARRAY_SIZE(ak4458_dem_select_texts),
			ak4458_dem_select_texts);
अटल स्थिर काष्ठा soc_क्रमागत ak4458_digfil_क्रमागत =
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(ak4458_digfil_select_texts),
			    ak4458_digfil_select_texts);
अटल स्थिर काष्ठा soc_क्रमागत ak4458_dzfb_क्रमागत =
	SOC_ENUM_SINGLE(AK4458_02_CONTROL3, 2,
			ARRAY_SIZE(ak4458_dzfb_select_texts),
			ak4458_dzfb_select_texts);
अटल स्थिर काष्ठा soc_क्रमागत ak4458_sm_क्रमागत =
	SOC_ENUM_SINGLE(AK4458_08_SOUND_CONTROL, 0,
			ARRAY_SIZE(ak4458_sc_select_texts),
			ak4458_sc_select_texts);
अटल स्थिर काष्ठा soc_क्रमागत ak4458_fir_क्रमागत =
	SOC_ENUM_SINGLE(AK4458_0C_CONTROL8, 0,
			ARRAY_SIZE(ak4458_fir_select_texts),
			ak4458_fir_select_texts);
अटल स्थिर काष्ठा soc_क्रमागत ak4458_ats_क्रमागत =
	SOC_ENUM_SINGLE(AK4458_0B_CONTROL7, 6,
			ARRAY_SIZE(ak4458_ats_select_texts),
			ak4458_ats_select_texts);
अटल स्थिर काष्ठा soc_क्रमागत ak4458_dअगर_क्रमागत =
	SOC_ENUM_SINGLE(AK4458_00_CONTROL1, 3,
			ARRAY_SIZE(ak4458_dअगर_select_texts),
			ak4458_dअगर_select_texts);

अटल पूर्णांक get_digfil(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा ak4458_priv *ak4458 = snd_soc_component_get_drvdata(component);

	ucontrol->value.क्रमागतerated.item[0] = ak4458->digfil;

	वापस 0;
पूर्ण

अटल पूर्णांक set_digfil(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा ak4458_priv *ak4458 = snd_soc_component_get_drvdata(component);
	पूर्णांक num;

	num = ucontrol->value.क्रमागतerated.item[0];
	अगर (num > 4)
		वापस -EINVAL;

	ak4458->digfil = num;

	/* ग_लिखो SD bit */
	snd_soc_component_update_bits(component, AK4458_01_CONTROL2,
			    AK4458_SD_MASK,
			    ((ak4458->digfil & 0x02) << 4));

	/* ग_लिखो SLOW bit */
	snd_soc_component_update_bits(component, AK4458_02_CONTROL3,
			    AK4458_SLOW_MASK,
			    (ak4458->digfil & 0x01));

	/* ग_लिखो SSLOW bit */
	snd_soc_component_update_bits(component, AK4458_05_CONTROL4,
			    AK4458_SSLOW_MASK,
			    ((ak4458->digfil & 0x04) >> 2));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new ak4458_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("DAC1 Playback Volume", AK4458_03_LCHATT,
			 AK4458_04_RCHATT, 0, 0xFF, 0, dac_tlv),
	SOC_DOUBLE_R_TLV("DAC2 Playback Volume", AK4458_0F_L2CHATT,
			 AK4458_10_R2CHATT, 0, 0xFF, 0, dac_tlv),
	SOC_DOUBLE_R_TLV("DAC3 Playback Volume", AK4458_11_L3CHATT,
			 AK4458_12_R3CHATT, 0, 0xFF, 0, dac_tlv),
	SOC_DOUBLE_R_TLV("DAC4 Playback Volume", AK4458_13_L4CHATT,
			 AK4458_14_R4CHATT, 0, 0xFF, 0, dac_tlv),
	SOC_ENUM("AK4458 De-emphasis Response DAC1", ak4458_dac1_dem_क्रमागत),
	SOC_ENUM("AK4458 De-emphasis Response DAC2", ak4458_dac2_dem_क्रमागत),
	SOC_ENUM("AK4458 De-emphasis Response DAC3", ak4458_dac3_dem_क्रमागत),
	SOC_ENUM("AK4458 De-emphasis Response DAC4", ak4458_dac4_dem_क्रमागत),
	SOC_ENUM_EXT("AK4458 Digital Filter Setting", ak4458_digfil_क्रमागत,
		     get_digfil, set_digfil),
	SOC_ENUM("AK4458 Inverting Enable of DZFB", ak4458_dzfb_क्रमागत),
	SOC_ENUM("AK4458 Sound Mode", ak4458_sm_क्रमागत),
	SOC_ENUM("AK4458 FIR Filter Mode Setting", ak4458_fir_क्रमागत),
	SOC_ENUM("AK4458 Attenuation transition Time Setting",
		 ak4458_ats_क्रमागत),
	SOC_ENUM("AK4458 BICK fs Setting", ak4458_dअगर_क्रमागत),
पूर्ण;

/* ak4458 dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget ak4458_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("AK4458 DAC1", शून्य, AK4458_0A_CONTROL6, 2, 0),/*pw*/
	SND_SOC_DAPM_AIF_IN("AK4458 SDTI", "Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUTPUT("AK4458 AOUTA"),

	SND_SOC_DAPM_DAC("AK4458 DAC2", शून्य, AK4458_0A_CONTROL6, 3, 0),/*pw*/
	SND_SOC_DAPM_OUTPUT("AK4458 AOUTB"),

	SND_SOC_DAPM_DAC("AK4458 DAC3", शून्य, AK4458_0B_CONTROL7, 2, 0),/*pw*/
	SND_SOC_DAPM_OUTPUT("AK4458 AOUTC"),

	SND_SOC_DAPM_DAC("AK4458 DAC4", शून्य, AK4458_0B_CONTROL7, 3, 0),/*pw*/
	SND_SOC_DAPM_OUTPUT("AK4458 AOUTD"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ak4458_पूर्णांकercon[] = अणु
	अणु"AK4458 DAC1",		शून्य,	"AK4458 SDTI"पूर्ण,
	अणु"AK4458 AOUTA",	शून्य,	"AK4458 DAC1"पूर्ण,

	अणु"AK4458 DAC2",		शून्य,	"AK4458 SDTI"पूर्ण,
	अणु"AK4458 AOUTB",	शून्य,	"AK4458 DAC2"पूर्ण,

	अणु"AK4458 DAC3",		शून्य,	"AK4458 SDTI"पूर्ण,
	अणु"AK4458 AOUTC",	शून्य,	"AK4458 DAC3"पूर्ण,

	अणु"AK4458 DAC4",		शून्य,	"AK4458 SDTI"पूर्ण,
	अणु"AK4458 AOUTD",	शून्य,	"AK4458 DAC4"पूर्ण,
पूर्ण;

/* ak4497 controls */
अटल स्थिर काष्ठा snd_kcontrol_new ak4497_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("DAC Playback Volume", AK4458_03_LCHATT,
			 AK4458_04_RCHATT, 0, 0xFF, 0, dac_tlv),
	SOC_ENUM("AK4497 De-emphasis Response DAC", ak4458_dac1_dem_क्रमागत),
	SOC_ENUM_EXT("AK4497 Digital Filter Setting", ak4458_digfil_क्रमागत,
		     get_digfil, set_digfil),
	SOC_ENUM("AK4497 Inverting Enable of DZFB", ak4458_dzfb_क्रमागत),
	SOC_ENUM("AK4497 Sound Mode", ak4458_sm_क्रमागत),
	SOC_ENUM("AK4497 Attenuation transition Time Setting",
		 ak4458_ats_क्रमागत),
पूर्ण;

/* ak4497 dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget ak4497_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("AK4497 DAC", शून्य, AK4458_0A_CONTROL6, 2, 0),
	SND_SOC_DAPM_AIF_IN("AK4497 SDTI", "Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUTPUT("AK4497 AOUT"),
पूर्ण;

/* ak4497 dapm routes */
अटल स्थिर काष्ठा snd_soc_dapm_route ak4497_पूर्णांकercon[] = अणु
	अणु"AK4497 DAC",		शून्य,	"AK4497 SDTI"पूर्ण,
	अणु"AK4497 AOUT",		शून्य,	"AK4497 DAC"पूर्ण,

पूर्ण;

अटल पूर्णांक ak4458_get_tdm_mode(काष्ठा ak4458_priv *ak4458)
अणु
	चयन (ak4458->slots * ak4458->slot_width) अणु
	हाल 128:
		वापस 1;
	हाल 256:
		वापस 2;
	हाल 512:
		वापस 3;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ak4458_rstn_control(काष्ठा snd_soc_component *component, पूर्णांक bit)
अणु
	पूर्णांक ret;

	अगर (bit)
		ret = snd_soc_component_update_bits(component,
					  AK4458_00_CONTROL1,
					  AK4458_RSTN_MASK,
					  0x1);
	अन्यथा
		ret = snd_soc_component_update_bits(component,
					  AK4458_00_CONTROL1,
					  AK4458_RSTN_MASK,
					  0x0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ak4458_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak4458_priv *ak4458 = snd_soc_component_get_drvdata(component);
	पूर्णांक pcm_width = max(params_physical_width(params), ak4458->slot_width);
	u8 क्रमmat, dsdsel0, dsdsel1, dchn;
	पूर्णांक nfs1, dsd_bclk, ret, channels, channels_max;

	nfs1 = params_rate(params);
	ak4458->fs = nfs1;

	/* calculate bit घड़ी */
	channels = params_channels(params);
	channels_max = dai->driver->playback.channels_max;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_DSD_U8:
	हाल SNDRV_PCM_FORMAT_DSD_U16_LE:
	हाल SNDRV_PCM_FORMAT_DSD_U16_BE:
	हाल SNDRV_PCM_FORMAT_DSD_U32_LE:
	हाल SNDRV_PCM_FORMAT_DSD_U32_BE:
		dsd_bclk = nfs1 * params_physical_width(params);
		चयन (dsd_bclk) अणु
		हाल 2822400:
			dsdsel0 = 0;
			dsdsel1 = 0;
			अवरोध;
		हाल 5644800:
			dsdsel0 = 1;
			dsdsel1 = 0;
			अवरोध;
		हाल 11289600:
			dsdsel0 = 0;
			dsdsel1 = 1;
			अवरोध;
		हाल 22579200:
			अगर (ak4458->drvdata->type == AK4497) अणु
				dsdsel0 = 1;
				dsdsel1 = 1;
			पूर्ण अन्यथा अणु
				dev_err(dai->dev, "DSD512 not supported.\n");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			dev_err(dai->dev, "Unsupported dsd bclk.\n");
			वापस -EINVAL;
		पूर्ण

		snd_soc_component_update_bits(component, AK4458_06_DSD1,
					      AK4458_DSDSEL_MASK, dsdsel0);
		snd_soc_component_update_bits(component, AK4458_09_DSD2,
					      AK4458_DSDSEL_MASK, dsdsel1);
		अवरोध;
	पूर्ण

	/* Master Clock Frequency Auto Setting Mode Enable */
	snd_soc_component_update_bits(component, AK4458_00_CONTROL1, 0x80, 0x80);

	चयन (pcm_width) अणु
	हाल 16:
		अगर (ak4458->fmt == SND_SOC_DAIFMT_I2S)
			क्रमmat = AK4458_DIF_24BIT_I2S;
		अन्यथा
			क्रमmat = AK4458_DIF_16BIT_LSB;
		अवरोध;
	हाल 32:
		चयन (ak4458->fmt) अणु
		हाल SND_SOC_DAIFMT_I2S:
			क्रमmat = AK4458_DIF_32BIT_I2S;
			अवरोध;
		हाल SND_SOC_DAIFMT_LEFT_J:
			क्रमmat = AK4458_DIF_32BIT_MSB;
			अवरोध;
		हाल SND_SOC_DAIFMT_RIGHT_J:
			क्रमmat = AK4458_DIF_32BIT_LSB;
			अवरोध;
		हाल SND_SOC_DAIFMT_DSP_B:
			क्रमmat = AK4458_DIF_32BIT_MSB;
			अवरोध;
		हाल SND_SOC_DAIFMT_PDM:
			क्रमmat = AK4458_DIF_32BIT_MSB;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AK4458_00_CONTROL1,
			    AK4458_DIF_MASK, क्रमmat);

	/*
	 * Enable/disable Daisy Chain अगर in TDM mode and the number of played
	 * channels is bigger than the maximum supported number of channels
	 */
	dchn = ak4458_get_tdm_mode(ak4458) &&
		(ak4458->fmt == SND_SOC_DAIFMT_DSP_B) &&
		(channels > channels_max) ? AK4458_DCHAIN_MASK : 0;

	snd_soc_component_update_bits(component, AK4458_0B_CONTROL7,
				      AK4458_DCHAIN_MASK, dchn);

	ret = ak4458_rstn_control(component, 0);
	अगर (ret)
		वापस ret;

	ret = ak4458_rstn_control(component, 1);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ak4458_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak4458_priv *ak4458 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS: /* Slave Mode */
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM: /* Master Mode is not supported */
	हाल SND_SOC_DAIFMT_CBS_CFM:
	हाल SND_SOC_DAIFMT_CBM_CFS:
	शेष:
		dev_err(component->dev, "Master mode unsupported\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_RIGHT_J:
	हाल SND_SOC_DAIFMT_DSP_B:
	हाल SND_SOC_DAIFMT_PDM:
		ak4458->fmt = fmt & SND_SOC_DAIFMT_FORMAT_MASK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Audio format 0x%02X unsupported\n",
			fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		वापस -EINVAL;
	पूर्ण

	/* DSD mode */
	snd_soc_component_update_bits(component, AK4458_02_CONTROL3,
				      AK4458_DP_MASK,
				      ak4458->fmt == SND_SOC_DAIFMT_PDM ?
				      AK4458_DP_MASK : 0);

	ret = ak4458_rstn_control(component, 0);
	अगर (ret)
		वापस ret;

	ret = ak4458_rstn_control(component, 1);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक att_speed[] = अणु 4080, 2040, 510, 255 पूर्ण;

अटल पूर्णांक ak4458_set_dai_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak4458_priv *ak4458 = snd_soc_component_get_drvdata(component);
	पूर्णांक nfs, ndt, reg;
	पूर्णांक ats;

	nfs = ak4458->fs;

	reg = snd_soc_component_पढ़ो(component, AK4458_0B_CONTROL7);
	ats = (reg & AK4458_ATS_MASK) >> AK4458_ATS_SHIFT;

	ndt = att_speed[ats] / (nfs / 1000);

	अगर (mute) अणु
		snd_soc_component_update_bits(component, AK4458_01_CONTROL2,  0x01, 1);
		mdelay(ndt);
		अगर (ak4458->mute_gpiod)
			gpiod_set_value_cansleep(ak4458->mute_gpiod, 1);
	पूर्ण अन्यथा अणु
		अगर (ak4458->mute_gpiod)
			gpiod_set_value_cansleep(ak4458->mute_gpiod, 0);
		snd_soc_component_update_bits(component, AK4458_01_CONTROL2, 0x01, 0);
		mdelay(ndt);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ak4458_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			       अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak4458_priv *ak4458 = snd_soc_component_get_drvdata(component);
	पूर्णांक mode;

	ak4458->slots = slots;
	ak4458->slot_width = slot_width;

	mode = ak4458_get_tdm_mode(ak4458) << AK4458_MODE_SHIFT;

	snd_soc_component_update_bits(component, AK4458_0A_CONTROL6,
			    AK4458_MODE_MASK,
			    mode);

	वापस 0;
पूर्ण

#घोषणा AK4458_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE |\
			 SNDRV_PCM_FMTBIT_S24_LE |\
			 SNDRV_PCM_FMTBIT_S32_LE |\
			 SNDRV_PCM_FMTBIT_DSD_U8 |\
			 SNDRV_PCM_FMTBIT_DSD_U16_LE |\
			 SNDRV_PCM_FMTBIT_DSD_U32_LE)

अटल स्थिर अचिन्हित पूर्णांक ak4458_rates[] = अणु
	8000, 11025,  16000, 22050,
	32000, 44100, 48000, 88200,
	96000, 176400, 192000, 352800,
	384000, 705600, 768000, 1411200,
	2822400,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list ak4458_rate_स्थिरraपूर्णांकs = अणु
	.count = ARRAY_SIZE(ak4458_rates),
	.list = ak4458_rates,
पूर्ण;

अटल पूर्णांक ak4458_startup(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					 SNDRV_PCM_HW_PARAM_RATE,
					 &ak4458_rate_स्थिरraपूर्णांकs);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ak4458_dai_ops = अणु
	.startup        = ak4458_startup,
	.hw_params	= ak4458_hw_params,
	.set_fmt	= ak4458_set_dai_fmt,
	.mute_stream	= ak4458_set_dai_mute,
	.set_tdm_slot	= ak4458_set_tdm_slot,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ak4458_dai = अणु
	.name = "ak4458-aif",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = AK4458_FORMATS,
	पूर्ण,
	.ops = &ak4458_dai_ops,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ak4497_dai = अणु
	.name = "ak4497-aif",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = AK4458_FORMATS,
	पूर्ण,
	.ops = &ak4458_dai_ops,
पूर्ण;

अटल व्योम ak4458_reset(काष्ठा ak4458_priv *ak4458, bool active)
अणु
	अगर (ak4458->reset_gpiod) अणु
		gpiod_set_value_cansleep(ak4458->reset_gpiod, active);
		usleep_range(1000, 2000);
	पूर्ण
पूर्ण

अटल पूर्णांक ak4458_init(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ak4458_priv *ak4458 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	/* External Mute ON */
	अगर (ak4458->mute_gpiod)
		gpiod_set_value_cansleep(ak4458->mute_gpiod, 1);

	ak4458_reset(ak4458, false);

	ret = snd_soc_component_update_bits(component, AK4458_00_CONTROL1,
			    0x80, 0x80);   /* ACKS bit = 1; 10000000 */
	अगर (ret < 0)
		वापस ret;

	अगर (ak4458->drvdata->type == AK4497) अणु
		ret = snd_soc_component_update_bits(component, AK4458_09_DSD2,
						    0x4, (ak4458->dsd_path << 2));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ak4458_rstn_control(component, 1);
पूर्ण

अटल पूर्णांक ak4458_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ak4458_priv *ak4458 = snd_soc_component_get_drvdata(component);

	ak4458->fs = 48000;

	वापस ak4458_init(component);
पूर्ण

अटल व्योम ak4458_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ak4458_priv *ak4458 = snd_soc_component_get_drvdata(component);

	ak4458_reset(ak4458, true);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक __maybe_unused ak4458_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा ak4458_priv *ak4458 = dev_get_drvdata(dev);

	regcache_cache_only(ak4458->regmap, true);

	ak4458_reset(ak4458, true);

	अगर (ak4458->mute_gpiod)
		gpiod_set_value_cansleep(ak4458->mute_gpiod, 0);

	regulator_bulk_disable(ARRAY_SIZE(ak4458->supplies),
			       ak4458->supplies);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ak4458_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा ak4458_priv *ak4458 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ak4458->supplies),
				    ak4458->supplies);
	अगर (ret != 0) अणु
		dev_err(ak4458->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ak4458->mute_gpiod)
		gpiod_set_value_cansleep(ak4458->mute_gpiod, 1);

	ak4458_reset(ak4458, true);
	ak4458_reset(ak4458, false);

	regcache_cache_only(ak4458->regmap, false);
	regcache_mark_dirty(ak4458->regmap);

	वापस regcache_sync(ak4458->regmap);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_dev_ak4458 = अणु
	.probe			= ak4458_probe,
	.हटाओ			= ak4458_हटाओ,
	.controls		= ak4458_snd_controls,
	.num_controls		= ARRAY_SIZE(ak4458_snd_controls),
	.dapm_widमाला_लो		= ak4458_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ak4458_dapm_widमाला_लो),
	.dapm_routes		= ak4458_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(ak4458_पूर्णांकercon),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_dev_ak4497 = अणु
	.probe			= ak4458_probe,
	.हटाओ			= ak4458_हटाओ,
	.controls		= ak4497_snd_controls,
	.num_controls		= ARRAY_SIZE(ak4497_snd_controls),
	.dapm_widमाला_लो		= ak4497_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ak4497_dapm_widमाला_लो),
	.dapm_routes		= ak4497_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(ak4497_पूर्णांकercon),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ak4458_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = AK4458_14_R4CHATT,
	.reg_शेषs = ak4458_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(ak4458_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा ak4458_drvdata ak4458_drvdata = अणु
	.dai_drv = &ak4458_dai,
	.comp_drv = &soc_codec_dev_ak4458,
	.type = AK4458,
पूर्ण;

अटल स्थिर काष्ठा ak4458_drvdata ak4497_drvdata = अणु
	.dai_drv = &ak4497_dai,
	.comp_drv = &soc_codec_dev_ak4497,
	.type = AK4497,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops ak4458_pm = अणु
	SET_RUNTIME_PM_OPS(ak4458_runसमय_suspend, ak4458_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल पूर्णांक ak4458_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा ak4458_priv *ak4458;
	पूर्णांक ret, i;

	ak4458 = devm_kzalloc(&i2c->dev, माप(*ak4458), GFP_KERNEL);
	अगर (!ak4458)
		वापस -ENOMEM;

	ak4458->regmap = devm_regmap_init_i2c(i2c, &ak4458_regmap);
	अगर (IS_ERR(ak4458->regmap))
		वापस PTR_ERR(ak4458->regmap);

	i2c_set_clientdata(i2c, ak4458);
	ak4458->dev = &i2c->dev;

	ak4458->drvdata = of_device_get_match_data(&i2c->dev);

	ak4458->reset_gpiod = devm_gpiod_get_optional(ak4458->dev, "reset",
						      GPIOD_OUT_LOW);
	अगर (IS_ERR(ak4458->reset_gpiod))
		वापस PTR_ERR(ak4458->reset_gpiod);

	ak4458->mute_gpiod = devm_gpiod_get_optional(ak4458->dev, "mute",
						     GPIOD_OUT_LOW);
	अगर (IS_ERR(ak4458->mute_gpiod))
		वापस PTR_ERR(ak4458->mute_gpiod);

	/* Optional property क्रम ak4497 */
	of_property_पढ़ो_u32(i2c->dev.of_node, "dsd-path", &ak4458->dsd_path);

	क्रम (i = 0; i < ARRAY_SIZE(ak4458->supplies); i++)
		ak4458->supplies[i].supply = ak4458_supply_names[i];

	ret = devm_regulator_bulk_get(ak4458->dev, ARRAY_SIZE(ak4458->supplies),
				      ak4458->supplies);
	अगर (ret != 0) अणु
		dev_err(ak4458->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(ak4458->dev,
					      ak4458->drvdata->comp_drv,
					      ak4458->drvdata->dai_drv, 1);
	अगर (ret < 0) अणु
		dev_err(ak4458->dev, "Failed to register CODEC: %d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_enable(&i2c->dev);
	regcache_cache_only(ak4458->regmap, true);

	वापस 0;
पूर्ण

अटल पूर्णांक ak4458_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	pm_runसमय_disable(&i2c->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ak4458_of_match[] = अणु
	अणु .compatible = "asahi-kasei,ak4458", .data = &ak4458_drvdataपूर्ण,
	अणु .compatible = "asahi-kasei,ak4497", .data = &ak4497_drvdataपूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ak4458_of_match);

अटल काष्ठा i2c_driver ak4458_i2c_driver = अणु
	.driver = अणु
		.name = "ak4458",
		.pm = &ak4458_pm,
		.of_match_table = ak4458_of_match,
		पूर्ण,
	.probe_new = ak4458_i2c_probe,
	.हटाओ = ak4458_i2c_हटाओ,
पूर्ण;

module_i2c_driver(ak4458_i2c_driver);

MODULE_AUTHOR("Junichi Wakasugi <wakasugi.jb@om.asahi-kasei.co.jp>");
MODULE_AUTHOR("Mihai Serban <mihai.serban@nxp.com>");
MODULE_DESCRIPTION("ASoC AK4458 DAC driver");
MODULE_LICENSE("GPL v2");
