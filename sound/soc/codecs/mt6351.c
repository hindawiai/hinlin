<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mt6351.c  --  mt6351 ALSA SoC audio codec driver
//
// Copyright (c) 2018 MediaTek Inc.
// Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/delay.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "mt6351.h"

/* MT6351_TOP_CLKSQ */
#घोषणा RG_CLKSQ_EN_AUD_BIT (0)

/* MT6351_TOP_CKPDN_CON0 */
#घोषणा RG_AUDNCP_CK_PDN_BIT (12)
#घोषणा RG_AUDIF_CK_PDN_BIT (13)
#घोषणा RG_AUD_CK_PDN_BIT (14)
#घोषणा RG_ZCD13M_CK_PDN_BIT (15)

/* MT6351_AUDDEC_ANA_CON0 */
#घोषणा RG_AUDDACLPWRUP_VAUDP32_BIT (0)
#घोषणा RG_AUDDACRPWRUP_VAUDP32_BIT (1)
#घोषणा RG_AUD_DAC_PWR_UP_VA32_BIT (2)
#घोषणा RG_AUD_DAC_PWL_UP_VA32_BIT (3)

#घोषणा RG_AUDHSPWRUP_VAUDP32_BIT (4)

#घोषणा RG_AUDHPLPWRUP_VAUDP32_BIT (5)
#घोषणा RG_AUDHPRPWRUP_VAUDP32_BIT (6)

#घोषणा RG_AUDHSMUXINPUTSEL_VAUDP32_SFT (7)
#घोषणा RG_AUDHSMUXINPUTSEL_VAUDP32_MASK (0x3)

#घोषणा RG_AUDHPLMUXINPUTSEL_VAUDP32_SFT (9)
#घोषणा RG_AUDHPLMUXINPUTSEL_VAUDP32_MASK (0x3)

#घोषणा RG_AUDHPRMUXINPUTSEL_VAUDP32_SFT (11)
#घोषणा RG_AUDHPRMUXINPUTSEL_VAUDP32_MASK (0x3)

#घोषणा RG_AUDHSSCDISABLE_VAUDP32 (13)
#घोषणा RG_AUDHPLSCDISABLE_VAUDP32_BIT (14)
#घोषणा RG_AUDHPRSCDISABLE_VAUDP32_BIT (15)

/* MT6351_AUDDEC_ANA_CON1 */
#घोषणा RG_HSOUTPUTSTBENH_VAUDP32_BIT (8)

/* MT6351_AUDDEC_ANA_CON3 */
#घोषणा RG_AUDLOLPWRUP_VAUDP32_BIT (2)

#घोषणा RG_AUDLOLMUXINPUTSEL_VAUDP32_SFT (3)
#घोषणा RG_AUDLOLMUXINPUTSEL_VAUDP32_MASK (0x3)

#घोषणा RG_AUDLOLSCDISABLE_VAUDP32_BIT (5)
#घोषणा RG_LOOUTPUTSTBENH_VAUDP32_BIT (9)

/* MT6351_AUDDEC_ANA_CON6 */
#घोषणा RG_ABIDEC_RSVD0_VAUDP32_HPL_BIT (8)
#घोषणा RG_ABIDEC_RSVD0_VAUDP32_HPR_BIT (9)
#घोषणा RG_ABIDEC_RSVD0_VAUDP32_HS_BIT (10)
#घोषणा RG_ABIDEC_RSVD0_VAUDP32_LOL_BIT (11)

/* MT6351_AUDDEC_ANA_CON9 */
#घोषणा RG_AUDIBIASPWRDN_VAUDP32_BIT (8)
#घोषणा RG_RSTB_DECODER_VA32_BIT (9)
#घोषणा RG_AUDGLB_PWRDN_VA32_BIT (12)

#घोषणा RG_LCLDO_DEC_EN_VA32_BIT (13)
#घोषणा RG_LCLDO_DEC_REMOTE_SENSE_VA18_BIT (15)
/* MT6351_AUDDEC_ANA_CON10 */
#घोषणा RG_NVREG_EN_VAUDP32_BIT (8)

#घोषणा RG_AUDGLB_LP2_VOW_EN_VA32 10

/* MT6351_AFE_UL_DL_CON0 */
#घोषणा RG_AFE_ON_BIT (0)

/* MT6351_AFE_DL_SRC2_CON0_L */
#घोषणा RG_DL_2_SRC_ON_TMP_CTL_PRE_BIT (0)

/* MT6351_AFE_UL_SRC_CON0_L */
#घोषणा UL_SRC_ON_TMP_CTL (0)

/* MT6351_AFE_TOP_CON0 */
#घोषणा RG_DL_SINE_ON_SFT (0)
#घोषणा RG_DL_SINE_ON_MASK (0x1)

#घोषणा RG_UL_SINE_ON_SFT (1)
#घोषणा RG_UL_SINE_ON_MASK (0x1)

/* MT6351_AUDIO_TOP_CON0 */
#घोषणा AUD_TOP_PDN_RESERVED_BIT 0
#घोषणा AUD_TOP_PWR_CLK_DIS_CTL_BIT 2
#घोषणा AUD_TOP_PDN_ADC_CTL_BIT 5
#घोषणा AUD_TOP_PDN_DAC_CTL_BIT 6
#घोषणा AUD_TOP_PDN_AFE_CTL_BIT 7

/* MT6351_AFE_SGEN_CFG0 */
#घोषणा SGEN_C_MUTE_SW_CTL_BIT 6
#घोषणा SGEN_C_DAC_EN_CTL_BIT 7

/* MT6351_AFE_NCP_CFG0 */
#घोषणा RG_NCP_ON_BIT 0

/* MT6351_LDO_VUSB33_CON0 */
#घोषणा RG_VUSB33_EN 1
#घोषणा RG_VUSB33_ON_CTRL 3

/* MT6351_LDO_VA18_CON0 */
#घोषणा RG_VA18_EN 1
#घोषणा RG_VA18_ON_CTRL 3

/* MT6351_AUDENC_ANA_CON0 */
#घोषणा RG_AUDPREAMPLON 0
#घोषणा RG_AUDPREAMPLDCCEN 1
#घोषणा RG_AUDPREAMPLDCPRECHARGE 2

#घोषणा RG_AUDPREAMPLINPUTSEL_SFT (4)
#घोषणा RG_AUDPREAMPLINPUTSEL_MASK (0x3)

#घोषणा RG_AUDADCLPWRUP 12

#घोषणा RG_AUDADCLINPUTSEL_SFT (13)
#घोषणा RG_AUDADCLINPUTSEL_MASK (0x3)

/* MT6351_AUDENC_ANA_CON1 */
#घोषणा RG_AUDPREAMPRON 0
#घोषणा RG_AUDPREAMPRDCCEN 1
#घोषणा RG_AUDPREAMPRDCPRECHARGE 2

#घोषणा RG_AUDPREAMPRINPUTSEL_SFT (4)
#घोषणा RG_AUDPREAMPRINPUTSEL_MASK (0x3)

#घोषणा RG_AUDADCRPWRUP 12

#घोषणा RG_AUDADCRINPUTSEL_SFT (13)
#घोषणा RG_AUDADCRINPUTSEL_MASK (0x3)

/* MT6351_AUDENC_ANA_CON3 */
#घोषणा RG_AUDADCCLKRSTB 6

/* MT6351_AUDENC_ANA_CON9 */
#घोषणा RG_AUDPWDBMICBIAS0 0
#घोषणा RG_AUDMICBIAS0VREF 4
#घोषणा RG_AUDMICBIAS0LOWPEN 7

#घोषणा RG_AUDPWDBMICBIAS2 8
#घोषणा RG_AUDMICBIAS2VREF 12
#घोषणा RG_AUDMICBIAS2LOWPEN 15

/* MT6351_AUDENC_ANA_CON10 */
#घोषणा RG_AUDPWDBMICBIAS1 0
#घोषणा RG_AUDMICBIAS1DCSW1NEN 2
#घोषणा RG_AUDMICBIAS1VREF 4
#घोषणा RG_AUDMICBIAS1LOWPEN 7

क्रमागत अणु
	AUDIO_ANALOG_VOLUME_HSOUTL,
	AUDIO_ANALOG_VOLUME_HSOUTR,
	AUDIO_ANALOG_VOLUME_HPOUTL,
	AUDIO_ANALOG_VOLUME_HPOUTR,
	AUDIO_ANALOG_VOLUME_LINEOUTL,
	AUDIO_ANALOG_VOLUME_LINEOUTR,
	AUDIO_ANALOG_VOLUME_MICAMP1,
	AUDIO_ANALOG_VOLUME_MICAMP2,
	AUDIO_ANALOG_VOLUME_TYPE_MAX
पूर्ण;

/* Supply subseq */
क्रमागत अणु
	SUPPLY_SUBSEQ_SETTING,
	SUPPLY_SUBSEQ_ENABLE,
	SUPPLY_SUBSEQ_MICBIAS,
पूर्ण;

#घोषणा REG_STRIDE 2

काष्ठा mt6351_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;

	अचिन्हित पूर्णांक dl_rate;
	अचिन्हित पूर्णांक ul_rate;

	पूर्णांक ana_gain[AUDIO_ANALOG_VOLUME_TYPE_MAX];

	पूर्णांक hp_en_counter;
पूर्ण;

अटल व्योम set_hp_gain_zero(काष्ठा snd_soc_component *cmpnt)
अणु
	regmap_update_bits(cmpnt->regmap, MT6351_ZCD_CON2,
			   0x1f << 7, 0x8 << 7);
	regmap_update_bits(cmpnt->regmap, MT6351_ZCD_CON2,
			   0x1f << 0, 0x8 << 0);
पूर्ण

अटल अचिन्हित पूर्णांक get_cap_reg_val(काष्ठा snd_soc_component *cmpnt,
				    अचिन्हित पूर्णांक rate)
अणु
	चयन (rate) अणु
	हाल 8000:
		वापस 0;
	हाल 16000:
		वापस 1;
	हाल 32000:
		वापस 2;
	हाल 48000:
		वापस 3;
	हाल 96000:
		वापस 4;
	हाल 192000:
		वापस 5;
	शेष:
		dev_warn(cmpnt->dev, "%s(), error rate %d, return 3",
			 __func__, rate);
		वापस 3;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक get_play_reg_val(काष्ठा snd_soc_component *cmpnt,
				     अचिन्हित पूर्णांक rate)
अणु
	चयन (rate) अणु
	हाल 8000:
		वापस 0;
	हाल 11025:
		वापस 1;
	हाल 12000:
		वापस 2;
	हाल 16000:
		वापस 3;
	हाल 22050:
		वापस 4;
	हाल 24000:
		वापस 5;
	हाल 32000:
		वापस 6;
	हाल 44100:
		वापस 7;
	हाल 48000:
	हाल 96000:
	हाल 192000:
		वापस 8;
	शेष:
		dev_warn(cmpnt->dev, "%s(), error rate %d, return 8",
			 __func__, rate);
		वापस 8;
	पूर्ण
पूर्ण

अटल पूर्णांक mt6351_codec_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params *params,
				      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *cmpnt = dai->component;
	काष्ठा mt6351_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	अचिन्हित पूर्णांक rate = params_rate(params);

	dev_dbg(priv->dev, "%s(), substream->stream %d, rate %d\n",
		__func__, substream->stream, rate);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		priv->dl_rate = rate;
	अन्यथा अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		priv->ul_rate = rate;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops mt6351_codec_dai_ops = अणु
	.hw_params = mt6351_codec_dai_hw_params,
पूर्ण;

#घोषणा MT6351_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |\
			SNDRV_PCM_FMTBIT_U16_LE | SNDRV_PCM_FMTBIT_U16_BE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE |\
			SNDRV_PCM_FMTBIT_U24_LE | SNDRV_PCM_FMTBIT_U24_BE |\
			SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S32_BE |\
			SNDRV_PCM_FMTBIT_U32_LE | SNDRV_PCM_FMTBIT_U32_BE)

अटल काष्ठा snd_soc_dai_driver mt6351_dai_driver[] = अणु
	अणु
		.name = "mt6351-snd-codec-aif1",
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000 |
				 SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = MT6351_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 |
				 SNDRV_PCM_RATE_32000 |
				 SNDRV_PCM_RATE_48000 |
				 SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000,
			.क्रमmats = MT6351_FORMATS,
		पूर्ण,
		.ops = &mt6351_codec_dai_ops,
	पूर्ण,
पूर्ण;

क्रमागत अणु
	HP_GAIN_SET_ZERO,
	HP_GAIN_RESTORE,
पूर्ण;

अटल व्योम hp_gain_ramp_set(काष्ठा snd_soc_component *cmpnt, पूर्णांक hp_gain_ctl)
अणु
	काष्ठा mt6351_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	पूर्णांक idx, old_idx, offset, reg_idx;

	अगर (hp_gain_ctl == HP_GAIN_SET_ZERO) अणु
		idx = 8;	/* 0dB */
		old_idx = priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTL];
	पूर्ण अन्यथा अणु
		idx = priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTL];
		old_idx = 8;	/* 0dB */
	पूर्ण
	dev_dbg(priv->dev, "%s(), idx %d, old_idx %d\n",
		__func__, idx, old_idx);

	अगर (idx > old_idx)
		offset = idx - old_idx;
	अन्यथा
		offset = old_idx - idx;

	reg_idx = old_idx;

	जबतक (offset > 0) अणु
		reg_idx = idx > old_idx ? reg_idx + 1 : reg_idx - 1;

		/* check valid range, and set value */
		अगर ((reg_idx >= 0 && reg_idx <= 0x12) || reg_idx == 0x1f) अणु
			regmap_update_bits(cmpnt->regmap,
					   MT6351_ZCD_CON2,
					   0xf9f,
					   (reg_idx << 7) | reg_idx);
			usleep_range(100, 120);
		पूर्ण
		offset--;
	पूर्ण
पूर्ण

अटल व्योम hp_zcd_enable(काष्ठा snd_soc_component *cmpnt)
अणु
	/* Enable ZCD, क्रम minimize pop noise */
	/* when adjust gain during HP buffer on */
	regmap_update_bits(cmpnt->regmap, MT6351_ZCD_CON0, 0x7 << 8, 0x1 << 8);
	regmap_update_bits(cmpnt->regmap, MT6351_ZCD_CON0, 0x1 << 7, 0x0 << 7);

	/* समयout, 1=5ms, 0=30ms */
	regmap_update_bits(cmpnt->regmap, MT6351_ZCD_CON0, 0x1 << 6, 0x1 << 6);

	regmap_update_bits(cmpnt->regmap, MT6351_ZCD_CON0, 0x3 << 4, 0x0 << 4);
	regmap_update_bits(cmpnt->regmap, MT6351_ZCD_CON0, 0x7 << 1, 0x5 << 1);
	regmap_update_bits(cmpnt->regmap, MT6351_ZCD_CON0, 0x1 << 0, 0x1 << 0);
पूर्ण

अटल व्योम hp_zcd_disable(काष्ठा snd_soc_component *cmpnt)
अणु
	regmap_ग_लिखो(cmpnt->regmap, MT6351_ZCD_CON0, 0x0000);
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(playback_tlv, -1000, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(pga_tlv, 0, 600, 0);

अटल स्थिर काष्ठा snd_kcontrol_new mt6351_snd_controls[] = अणु
	/* dl pga gain */
	SOC_DOUBLE_TLV("Headphone Volume",
		       MT6351_ZCD_CON2, 0, 7, 0x12, 1,
		       playback_tlv),
	SOC_DOUBLE_TLV("Lineout Volume",
		       MT6351_ZCD_CON1, 0, 7, 0x12, 1,
		       playback_tlv),
	SOC_SINGLE_TLV("Handset Volume",
		       MT6351_ZCD_CON3, 0, 0x12, 1,
		       playback_tlv),
       /* ul pga gain */
	SOC_DOUBLE_R_TLV("PGA Volume",
			 MT6351_AUDENC_ANA_CON0, MT6351_AUDENC_ANA_CON1,
			 8, 4, 0,
			 pga_tlv),
पूर्ण;

/* MUX */

/* LOL MUX */
अटल स्थिर अक्षर *स्थिर lo_in_mux_map[] = अणु
	"Open", "Mute", "Playback", "Test Mode",
पूर्ण;

अटल पूर्णांक lo_in_mux_map_value[] = अणु
	0x0, 0x1, 0x2, 0x3,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(lo_in_mux_map_क्रमागत,
				  MT6351_AUDDEC_ANA_CON3,
				  RG_AUDLOLMUXINPUTSEL_VAUDP32_SFT,
				  RG_AUDLOLMUXINPUTSEL_VAUDP32_MASK,
				  lo_in_mux_map,
				  lo_in_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new lo_in_mux_control =
	SOC_DAPM_ENUM("In Select", lo_in_mux_map_क्रमागत);

/*HP MUX */
अटल स्थिर अक्षर *स्थिर hp_in_mux_map[] = अणु
	"Open", "LoudSPK Playback", "Audio Playback", "Test Mode",
पूर्ण;

अटल पूर्णांक hp_in_mux_map_value[] = अणु
	0x0, 0x1, 0x2, 0x3,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(hpl_in_mux_map_क्रमागत,
				  MT6351_AUDDEC_ANA_CON0,
				  RG_AUDHPLMUXINPUTSEL_VAUDP32_SFT,
				  RG_AUDHPLMUXINPUTSEL_VAUDP32_MASK,
				  hp_in_mux_map,
				  hp_in_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new hpl_in_mux_control =
	SOC_DAPM_ENUM("HPL Select", hpl_in_mux_map_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(hpr_in_mux_map_क्रमागत,
				  MT6351_AUDDEC_ANA_CON0,
				  RG_AUDHPRMUXINPUTSEL_VAUDP32_SFT,
				  RG_AUDHPRMUXINPUTSEL_VAUDP32_MASK,
				  hp_in_mux_map,
				  hp_in_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new hpr_in_mux_control =
	SOC_DAPM_ENUM("HPR Select", hpr_in_mux_map_क्रमागत);

/* RCV MUX */
अटल स्थिर अक्षर *स्थिर rcv_in_mux_map[] = अणु
	"Open", "Mute", "Voice Playback", "Test Mode",
पूर्ण;

अटल पूर्णांक rcv_in_mux_map_value[] = अणु
	0x0, 0x1, 0x2, 0x3,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(rcv_in_mux_map_क्रमागत,
				  MT6351_AUDDEC_ANA_CON0,
				  RG_AUDHSMUXINPUTSEL_VAUDP32_SFT,
				  RG_AUDHSMUXINPUTSEL_VAUDP32_MASK,
				  rcv_in_mux_map,
				  rcv_in_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new rcv_in_mux_control =
	SOC_DAPM_ENUM("RCV Select", rcv_in_mux_map_क्रमागत);

/* DAC In MUX */
अटल स्थिर अक्षर *स्थिर dac_in_mux_map[] = अणु
	"Normal Path", "Sgen",
पूर्ण;

अटल पूर्णांक dac_in_mux_map_value[] = अणु
	0x0, 0x1,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(dac_in_mux_map_क्रमागत,
				  MT6351_AFE_TOP_CON0,
				  RG_DL_SINE_ON_SFT,
				  RG_DL_SINE_ON_MASK,
				  dac_in_mux_map,
				  dac_in_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new dac_in_mux_control =
	SOC_DAPM_ENUM("DAC Select", dac_in_mux_map_क्रमागत);

/* AIF Out MUX */
अटल SOC_VALUE_ENUM_SINGLE_DECL(aअगर_out_mux_map_क्रमागत,
				  MT6351_AFE_TOP_CON0,
				  RG_UL_SINE_ON_SFT,
				  RG_UL_SINE_ON_MASK,
				  dac_in_mux_map,
				  dac_in_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new aअगर_out_mux_control =
	SOC_DAPM_ENUM("AIF Out Select", aअगर_out_mux_map_क्रमागत);

/* ADC L MUX */
अटल स्थिर अक्षर *स्थिर adc_left_mux_map[] = अणु
	"Idle", "AIN0", "Left Preamplifier", "Idle_1",
पूर्ण;

अटल पूर्णांक adc_left_mux_map_value[] = अणु
	0x0, 0x1, 0x2, 0x3,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(adc_left_mux_map_क्रमागत,
				  MT6351_AUDENC_ANA_CON0,
				  RG_AUDADCLINPUTSEL_SFT,
				  RG_AUDADCLINPUTSEL_MASK,
				  adc_left_mux_map,
				  adc_left_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new adc_left_mux_control =
	SOC_DAPM_ENUM("ADC L Select", adc_left_mux_map_क्रमागत);

/* ADC R MUX */
अटल स्थिर अक्षर *स्थिर adc_right_mux_map[] = अणु
	"Idle", "AIN0", "Right Preamplifier", "Idle_1",
पूर्ण;

अटल पूर्णांक adc_right_mux_map_value[] = अणु
	0x0, 0x1, 0x2, 0x3,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(adc_right_mux_map_क्रमागत,
				  MT6351_AUDENC_ANA_CON1,
				  RG_AUDADCRINPUTSEL_SFT,
				  RG_AUDADCRINPUTSEL_MASK,
				  adc_right_mux_map,
				  adc_right_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new adc_right_mux_control =
	SOC_DAPM_ENUM("ADC R Select", adc_right_mux_map_क्रमागत);

/* PGA L MUX */
अटल स्थिर अक्षर *स्थिर pga_left_mux_map[] = अणु
	"None", "AIN0", "AIN1", "AIN2",
पूर्ण;

अटल पूर्णांक pga_left_mux_map_value[] = अणु
	0x0, 0x1, 0x2, 0x3,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(pga_left_mux_map_क्रमागत,
				  MT6351_AUDENC_ANA_CON0,
				  RG_AUDPREAMPLINPUTSEL_SFT,
				  RG_AUDPREAMPLINPUTSEL_MASK,
				  pga_left_mux_map,
				  pga_left_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new pga_left_mux_control =
	SOC_DAPM_ENUM("PGA L Select", pga_left_mux_map_क्रमागत);

/* PGA R MUX */
अटल स्थिर अक्षर *स्थिर pga_right_mux_map[] = अणु
	"None", "AIN0", "AIN3", "AIN2",
पूर्ण;

अटल पूर्णांक pga_right_mux_map_value[] = अणु
	0x0, 0x1, 0x2, 0x3,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(pga_right_mux_map_क्रमागत,
				  MT6351_AUDENC_ANA_CON1,
				  RG_AUDPREAMPRINPUTSEL_SFT,
				  RG_AUDPREAMPRINPUTSEL_MASK,
				  pga_right_mux_map,
				  pga_right_mux_map_value);

अटल स्थिर काष्ठा snd_kcontrol_new pga_right_mux_control =
	SOC_DAPM_ENUM("PGA R Select", pga_right_mux_map_क्रमागत);

अटल पूर्णांक mt_reg_set_clr_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol,
				पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (w->on_val) अणु
			/* SET REG */
			regmap_update_bits(cmpnt->regmap,
					   w->reg + REG_STRIDE,
					   0x1 << w->shअगरt,
					   0x1 << w->shअगरt);
		पूर्ण अन्यथा अणु
			/* CLR REG */
			regmap_update_bits(cmpnt->regmap,
					   w->reg + REG_STRIDE * 2,
					   0x1 << w->shअगरt,
					   0x1 << w->shअगरt);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		अगर (w->off_val) अणु
			/* SET REG */
			regmap_update_bits(cmpnt->regmap,
					   w->reg + REG_STRIDE,
					   0x1 << w->shअगरt,
					   0x1 << w->shअगरt);
		पूर्ण अन्यथा अणु
			/* CLR REG */
			regmap_update_bits(cmpnt->regmap,
					   w->reg + REG_STRIDE * 2,
					   0x1 << w->shअगरt,
					   0x1 << w->shअगरt);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_ncp_event(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *kcontrol,
			पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		regmap_update_bits(cmpnt->regmap, MT6351_AFE_NCP_CFG1,
				   0xffff, 0x1515);
		/* NCP: ck1 and ck2 घड़ी frequecy adjust configure */
		regmap_update_bits(cmpnt->regmap, MT6351_AFE_NCP_CFG0,
				   0xfffe, 0x8C00);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		usleep_range(250, 270);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_sgen_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol,
			 पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		regmap_update_bits(cmpnt->regmap, MT6351_AFE_SGEN_CFG0,
				   0xffef, 0x0008);
		regmap_update_bits(cmpnt->regmap, MT6351_AFE_SGEN_CFG1,
				   0xffff, 0x0101);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_aअगर_in_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol,
			   पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6351_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event 0x%x, rate %d\n",
		__func__, event, priv->dl_rate);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* sdm audio fअगरo घड़ी घातer on */
		regmap_update_bits(cmpnt->regmap, MT6351_AFUNC_AUD_CON2,
				   0xffff, 0x0006);
		/* scrambler घड़ी on enable */
		regmap_update_bits(cmpnt->regmap, MT6351_AFUNC_AUD_CON0,
				   0xffff, 0xC3A1);
		/* sdm घातer on */
		regmap_update_bits(cmpnt->regmap, MT6351_AFUNC_AUD_CON2,
				   0xffff, 0x0003);
		/* sdm fअगरo enable */
		regmap_update_bits(cmpnt->regmap, MT6351_AFUNC_AUD_CON2,
				   0xffff, 0x000B);
		/* set attenuation gain */
		regmap_update_bits(cmpnt->regmap, MT6351_AFE_DL_SDM_CON1,
				   0xffff, 0x001E);

		regmap_ग_लिखो(cmpnt->regmap, MT6351_AFE_PMIC_NEWIF_CFG0,
			     (get_play_reg_val(cmpnt, priv->dl_rate) << 12) |
			     0x330);
		regmap_ग_लिखो(cmpnt->regmap, MT6351_AFE_DL_SRC2_CON0_H,
			     (get_play_reg_val(cmpnt, priv->dl_rate) << 12) |
			     0x300);

		regmap_update_bits(cmpnt->regmap, MT6351_AFE_PMIC_NEWIF_CFG2,
				   0x8000, 0x8000);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_hp_event(काष्ठा snd_soc_dapm_widget *w,
		       काष्ठा snd_kcontrol *kcontrol,
		       पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6351_priv *priv = snd_soc_component_get_drvdata(cmpnt);
	पूर्णांक reg;

	dev_dbg(priv->dev, "%s(), event 0x%x, hp_en_counter %d\n",
		__func__, event, priv->hp_en_counter);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		priv->hp_en_counter++;
		अगर (priv->hp_en_counter > 1)
			अवरोध;	/* alपढ़ोy enabled, करो nothing */
		अन्यथा अगर (priv->hp_en_counter <= 0)
			dev_err(priv->dev, "%s(), hp_en_counter %d <= 0\n",
				__func__,
				priv->hp_en_counter);

		hp_zcd_disable(cmpnt);

		/* from yoyo HQA script */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDDEC_ANA_CON6,
				   0x0700, 0x0700);

		/* save target gain to restore after hardware खोलो complete */
		regmap_पढ़ो(cmpnt->regmap, MT6351_ZCD_CON2, &reg);
		priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTL] = reg & 0x1f;
		priv->ana_gain[AUDIO_ANALOG_VOLUME_HPOUTR] = (reg >> 7) & 0x1f;

		/* Set HPR/HPL gain as minimum (~ -40dB) */
		regmap_update_bits(cmpnt->regmap,
				   MT6351_ZCD_CON2, 0xffff, 0x0F9F);
		/* Set HS gain as minimum (~ -40dB) */
		regmap_update_bits(cmpnt->regmap,
				   MT6351_ZCD_CON3, 0xffff, 0x001F);
		/* De_OSC of HP */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDDEC_ANA_CON2,
				   0x0001, 0x0001);
		/* enable output STBENH */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDDEC_ANA_CON1,
				   0xffff, 0x2000);
		/* De_OSC of voice, enable output STBENH */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDDEC_ANA_CON1,
				   0xffff, 0x2100);
		/* Enable voice driver */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDDEC_ANA_CON0,
				   0x0010, 0xE090);
		/* Enable pre-अक्षरge buffer  */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDDEC_ANA_CON1,
				   0xffff, 0x2140);

		usleep_range(50, 60);

		/* Apply digital DC compensation value to DAC */
		set_hp_gain_zero(cmpnt);

		/* Enable HPR/HPL */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDDEC_ANA_CON1,
				   0xffff, 0x2100);
		/* Disable pre-अक्षरge buffer */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDDEC_ANA_CON1,
				   0xffff, 0x2000);
		/* Disable De_OSC of voice */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDDEC_ANA_CON0,
				   0x0010, 0xF4EF);
		/* Disable voice buffer */

		/* from yoyo HQ */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDDEC_ANA_CON6,
				   0x0700, 0x0300);

		/* Enable ZCD, क्रम minimize pop noise */
		/* when adjust gain during HP buffer on */
		hp_zcd_enable(cmpnt);

		/* apply volume setting */
		hp_gain_ramp_set(cmpnt, HP_GAIN_RESTORE);

		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		priv->hp_en_counter--;
		अगर (priv->hp_en_counter > 0)
			अवरोध;	/* still being used, करोn't बंद */
		अन्यथा अगर (priv->hp_en_counter < 0)
			dev_err(priv->dev, "%s(), hp_en_counter %d <= 0\n",
				__func__,
				priv->hp_en_counter);

		/* Disable AUD_ZCD */
		hp_zcd_disable(cmpnt);

		/* Set HPR/HPL gain as -1dB, step by step */
		hp_gain_ramp_set(cmpnt, HP_GAIN_SET_ZERO);

		set_hp_gain_zero(cmpnt);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		अगर (priv->hp_en_counter > 0)
			अवरोध;	/* still being used, करोn't बंद */
		अन्यथा अगर (priv->hp_en_counter < 0)
			dev_err(priv->dev, "%s(), hp_en_counter %d <= 0\n",
				__func__,
				priv->hp_en_counter);

		/* reset*/
		regmap_update_bits(cmpnt->regmap,
				   MT6351_AUDDEC_ANA_CON6,
				   0x0700,
				   0x0000);
		/* De_OSC of HP */
		regmap_update_bits(cmpnt->regmap,
				   MT6351_AUDDEC_ANA_CON2,
				   0x0001,
				   0x0000);

		/* apply volume setting */
		hp_gain_ramp_set(cmpnt, HP_GAIN_RESTORE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_aअगर_out_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol,
			    पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा mt6351_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	dev_dbg(priv->dev, "%s(), event 0x%x, rate %d\n",
		__func__, event, priv->ul_rate);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* dcclk_भाग=11'b00100000011, dcclk_ref_ck_sel=2'b00 */
		regmap_update_bits(cmpnt->regmap, MT6351_AFE_DCCLK_CFG0,
				   0xffff, 0x2062);
		/* dcclk_pdn=1'b0 */
		regmap_update_bits(cmpnt->regmap, MT6351_AFE_DCCLK_CFG0,
				   0xffff, 0x2060);
		/* dcclk_gen_on=1'b1 */
		regmap_update_bits(cmpnt->regmap, MT6351_AFE_DCCLK_CFG0,
				   0xffff, 0x2061);

		/* UL sample rate and mode configure */
		regmap_update_bits(cmpnt->regmap, MT6351_AFE_UL_SRC_CON0_H,
				   0x000E,
				   get_cap_reg_val(cmpnt, priv->ul_rate) << 1);

		/* fixed 260k path क्रम 8/16/32/48 */
		अगर (priv->ul_rate <= 48000) अणु
			/* anc ul path src on */
			regmap_update_bits(cmpnt->regmap,
					   MT6351_AFE_HPANC_CFG0,
					   0x1 << 1,
					   0x1 << 1);
			/* ANC clk pdn release */
			regmap_update_bits(cmpnt->regmap,
					   MT6351_AFE_HPANC_CFG0,
					   0x1 << 0,
					   0x0 << 0);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		/* fixed 260k path क्रम 8/16/32/48 */
		अगर (priv->ul_rate <= 48000) अणु
			/* anc ul path src on */
			regmap_update_bits(cmpnt->regmap,
					   MT6351_AFE_HPANC_CFG0,
					   0x1 << 1,
					   0x0 << 1);
			/* ANC clk pdn release */
			regmap_update_bits(cmpnt->regmap,
					   MT6351_AFE_HPANC_CFG0,
					   0x1 << 0,
					   0x1 << 0);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt_adc_clkgen_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol,
			       पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Audio ADC घड़ी gen. mode: 00_भागided by 2 (Normal) */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON3,
				   0x3 << 4, 0x0);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		/* ADC CLK from: 00_13MHz from CLKSQ (Default) */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON3,
				   0x3 << 2, 0x0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mt_pga_left_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol,
			     पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Audio L PGA preअक्षरge on */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON0,
				   0x3 << RG_AUDPREAMPLDCPRECHARGE,
				   0x1 << RG_AUDPREAMPLDCPRECHARGE);
		/* Audio L PGA mode: 1_DCC */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON0,
				   0x3 << RG_AUDPREAMPLDCCEN,
				   0x1 << RG_AUDPREAMPLDCCEN);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		usleep_range(100, 120);
		/* Audio L PGA preअक्षरge off */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON0,
				   0x3 << RG_AUDPREAMPLDCPRECHARGE,
				   0x0 << RG_AUDPREAMPLDCPRECHARGE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mt_pga_right_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol,
			      पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Audio R PGA preअक्षरge on */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON1,
				   0x3 << RG_AUDPREAMPRDCPRECHARGE,
				   0x1 << RG_AUDPREAMPRDCPRECHARGE);
		/* Audio R PGA mode: 1_DCC */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON1,
				   0x3 << RG_AUDPREAMPRDCCEN,
				   0x1 << RG_AUDPREAMPRDCCEN);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		usleep_range(100, 120);
		/* Audio R PGA preअक्षरge off */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON1,
				   0x3 << RG_AUDPREAMPRDCPRECHARGE,
				   0x0 << RG_AUDPREAMPRDCPRECHARGE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mt_mic_bias_0_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol,
			       पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* MIC Bias 0 LowPower: 0_Normal */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON9,
				   0x3 << RG_AUDMICBIAS0LOWPEN, 0x0);
		/* MISBIAS0 = 1P9V */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON9,
				   0x7 << RG_AUDMICBIAS0VREF,
				   0x2 << RG_AUDMICBIAS0VREF);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* MISBIAS0 = 1P97 */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON9,
				   0x7 << RG_AUDMICBIAS0VREF,
				   0x0 << RG_AUDMICBIAS0VREF);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mt_mic_bias_1_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol,
			       पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* MIC Bias 1 LowPower: 0_Normal */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON10,
				   0x3 << RG_AUDMICBIAS1LOWPEN, 0x0);
		/* MISBIAS1 = 2P7V */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON10,
				   0x7 << RG_AUDMICBIAS1VREF,
				   0x7 << RG_AUDMICBIAS1VREF);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* MISBIAS1 = 1P7V */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON10,
				   0x7 << RG_AUDMICBIAS1VREF,
				   0x0 << RG_AUDMICBIAS1VREF);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mt_mic_bias_2_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol,
			       पूर्णांक event)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* MIC Bias 2 LowPower: 0_Normal */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON9,
				   0x3 << RG_AUDMICBIAS2LOWPEN, 0x0);
		/* MISBIAS2 = 1P9V */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON9,
				   0x7 << RG_AUDMICBIAS2VREF,
				   0x2 << RG_AUDMICBIAS2VREF);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* MISBIAS2 = 1P97 */
		regmap_update_bits(cmpnt->regmap, MT6351_AUDENC_ANA_CON9,
				   0x7 << RG_AUDMICBIAS2VREF,
				   0x0 << RG_AUDMICBIAS2VREF);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* DAPM Widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget mt6351_dapm_widमाला_लो[] = अणु
	/* Digital Clock */
	SND_SOC_DAPM_SUPPLY("AUDIO_TOP_AFE_CTL", MT6351_AUDIO_TOP_CON0,
			    AUD_TOP_PDN_AFE_CTL_BIT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AUDIO_TOP_DAC_CTL", MT6351_AUDIO_TOP_CON0,
			    AUD_TOP_PDN_DAC_CTL_BIT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AUDIO_TOP_ADC_CTL", MT6351_AUDIO_TOP_CON0,
			    AUD_TOP_PDN_ADC_CTL_BIT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AUDIO_TOP_PWR_CLK", MT6351_AUDIO_TOP_CON0,
			    AUD_TOP_PWR_CLK_DIS_CTL_BIT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AUDIO_TOP_PDN_RESERVED", MT6351_AUDIO_TOP_CON0,
			    AUD_TOP_PDN_RESERVED_BIT, 1, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("NCP", MT6351_AFE_NCP_CFG0,
			    RG_NCP_ON_BIT, 0,
			    mt_ncp_event,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_SUPPLY("DL Digital Clock", SND_SOC_NOPM,
			    0, 0, शून्य, 0),

	/* Global Supply*/
	SND_SOC_DAPM_SUPPLY("AUDGLB", MT6351_AUDDEC_ANA_CON9,
			    RG_AUDGLB_PWRDN_VA32_BIT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLKSQ Audio", MT6351_TOP_CLKSQ,
			    RG_CLKSQ_EN_AUD_BIT, 0,
			    mt_reg_set_clr_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SUPPLY("ZCD13M_CK", MT6351_TOP_CKPDN_CON0,
			    RG_ZCD13M_CK_PDN_BIT, 1,
			    mt_reg_set_clr_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SUPPLY("AUD_CK", MT6351_TOP_CKPDN_CON0,
			    RG_AUD_CK_PDN_BIT, 1,
			    mt_reg_set_clr_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SUPPLY("AUDIF_CK", MT6351_TOP_CKPDN_CON0,
			    RG_AUDIF_CK_PDN_BIT, 1,
			    mt_reg_set_clr_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SUPPLY("AUDNCP_CK", MT6351_TOP_CKPDN_CON0,
			    RG_AUDNCP_CK_PDN_BIT, 1,
			    mt_reg_set_clr_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_SUPPLY("AFE_ON", MT6351_AFE_UL_DL_CON0, RG_AFE_ON_BIT, 0,
			    शून्य, 0),

	/* AIF Rx*/
	SND_SOC_DAPM_AIF_IN_E("AIF_RX", "AIF1 Playback", 0,
			      MT6351_AFE_DL_SRC2_CON0_L,
			      RG_DL_2_SRC_ON_TMP_CTL_PRE_BIT, 0,
			      mt_aअगर_in_event, SND_SOC_DAPM_PRE_PMU),

	/* DL Supply */
	SND_SOC_DAPM_SUPPLY("DL Power Supply", SND_SOC_NOPM,
			    0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("NV Regulator", MT6351_AUDDEC_ANA_CON10,
			    RG_NVREG_EN_VAUDP32_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AUD_CLK", MT6351_AUDDEC_ANA_CON9,
			    RG_RSTB_DECODER_VA32_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("IBIST", MT6351_AUDDEC_ANA_CON9,
			    RG_AUDIBIASPWRDN_VAUDP32_BIT, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("LDO", MT6351_AUDDEC_ANA_CON9,
			    RG_LCLDO_DEC_EN_VA32_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("LDO_REMOTE_SENSE", MT6351_AUDDEC_ANA_CON9,
			    RG_LCLDO_DEC_REMOTE_SENSE_VA18_BIT, 0, शून्य, 0),

	/* DAC */
	SND_SOC_DAPM_MUX("DAC In Mux", SND_SOC_NOPM, 0, 0, &dac_in_mux_control),

	SND_SOC_DAPM_DAC("DACL", शून्य, MT6351_AUDDEC_ANA_CON0,
			 RG_AUDDACLPWRUP_VAUDP32_BIT, 0),
	SND_SOC_DAPM_SUPPLY("DACL_BIASGEN", MT6351_AUDDEC_ANA_CON0,
			    RG_AUD_DAC_PWL_UP_VA32_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_DAC("DACR", शून्य, MT6351_AUDDEC_ANA_CON0,
			 RG_AUDDACRPWRUP_VAUDP32_BIT, 0),
	SND_SOC_DAPM_SUPPLY("DACR_BIASGEN", MT6351_AUDDEC_ANA_CON0,
			    RG_AUD_DAC_PWR_UP_VA32_BIT, 0, शून्य, 0),
	/* LOL */
	SND_SOC_DAPM_MUX("LOL Mux", SND_SOC_NOPM, 0, 0, &lo_in_mux_control),

	SND_SOC_DAPM_SUPPLY("LO Stability Enh", MT6351_AUDDEC_ANA_CON3,
			    RG_LOOUTPUTSTBENH_VAUDP32_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("LOL Bias Gen", MT6351_AUDDEC_ANA_CON6,
			    RG_ABIDEC_RSVD0_VAUDP32_LOL_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_OUT_DRV("LOL Buffer", MT6351_AUDDEC_ANA_CON3,
			     RG_AUDLOLPWRUP_VAUDP32_BIT, 0, शून्य, 0),

	/* Headphone */
	SND_SOC_DAPM_MUX("HPL Mux", SND_SOC_NOPM, 0, 0, &hpl_in_mux_control),
	SND_SOC_DAPM_MUX("HPR Mux", SND_SOC_NOPM, 0, 0, &hpr_in_mux_control),

	SND_SOC_DAPM_OUT_DRV_E("HPL Power", MT6351_AUDDEC_ANA_CON0,
			       RG_AUDHPLPWRUP_VAUDP32_BIT, 0, शून्य, 0,
			       mt_hp_event,
			       SND_SOC_DAPM_PRE_PMU |
			       SND_SOC_DAPM_PRE_PMD |
			       SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUT_DRV_E("HPR Power", MT6351_AUDDEC_ANA_CON0,
			       RG_AUDHPRPWRUP_VAUDP32_BIT, 0, शून्य, 0,
			       mt_hp_event,
			       SND_SOC_DAPM_PRE_PMU |
			       SND_SOC_DAPM_PRE_PMD |
			       SND_SOC_DAPM_POST_PMD),

	/* Receiver */
	SND_SOC_DAPM_MUX("RCV Mux", SND_SOC_NOPM, 0, 0, &rcv_in_mux_control),

	SND_SOC_DAPM_SUPPLY("RCV Stability Enh", MT6351_AUDDEC_ANA_CON1,
			    RG_HSOUTPUTSTBENH_VAUDP32_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RCV Bias Gen", MT6351_AUDDEC_ANA_CON6,
			    RG_ABIDEC_RSVD0_VAUDP32_HS_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_OUT_DRV("RCV Buffer", MT6351_AUDDEC_ANA_CON0,
			     RG_AUDHSPWRUP_VAUDP32_BIT, 0, शून्य, 0),

	/* Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("Receiver"),
	SND_SOC_DAPM_OUTPUT("Headphone L"),
	SND_SOC_DAPM_OUTPUT("Headphone R"),
	SND_SOC_DAPM_OUTPUT("LINEOUT L"),

	/* SGEN */
	SND_SOC_DAPM_SUPPLY("SGEN DL Enable", MT6351_AFE_SGEN_CFG0,
			    SGEN_C_DAC_EN_CTL_BIT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SGEN MUTE", MT6351_AFE_SGEN_CFG0,
			    SGEN_C_MUTE_SW_CTL_BIT, 1,
			    mt_sgen_event, SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_SUPPLY("SGEN DL SRC", MT6351_AFE_DL_SRC2_CON0_L,
			    RG_DL_2_SRC_ON_TMP_CTL_PRE_BIT, 0, शून्य, 0),

	SND_SOC_DAPM_INPUT("SGEN DL"),

	/* Uplinks */
	SND_SOC_DAPM_AIF_OUT_E("AIF1TX", "AIF1 Capture", 0,
			       MT6351_AFE_UL_SRC_CON0_L,
			       UL_SRC_ON_TMP_CTL, 0,
			       mt_aअगर_out_event,
			       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_SUPPLY_S("VUSB33_LDO", SUPPLY_SUBSEQ_ENABLE,
			      MT6351_LDO_VUSB33_CON0, RG_VUSB33_EN, 0,
			      शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("VUSB33_LDO_CTRL", SUPPLY_SUBSEQ_SETTING,
			      MT6351_LDO_VUSB33_CON0, RG_VUSB33_ON_CTRL, 1,
			      शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("VA18_LDO", SUPPLY_SUBSEQ_ENABLE,
			      MT6351_LDO_VA18_CON0, RG_VA18_EN, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("VA18_LDO_CTRL", SUPPLY_SUBSEQ_SETTING,
			      MT6351_LDO_VA18_CON0, RG_VA18_ON_CTRL, 1,
			      शून्य, 0),

	SND_SOC_DAPM_SUPPLY_S("ADC CLKGEN", SUPPLY_SUBSEQ_ENABLE,
			      MT6351_AUDENC_ANA_CON3, RG_AUDADCCLKRSTB, 0,
			      mt_adc_clkgen_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),

	/* Uplinks MUX */
	SND_SOC_DAPM_MUX("AIF Out Mux", SND_SOC_NOPM, 0, 0,
			 &aअगर_out_mux_control),

	SND_SOC_DAPM_MUX("ADC L Mux", SND_SOC_NOPM, 0, 0,
			 &adc_left_mux_control),
	SND_SOC_DAPM_MUX("ADC R Mux", SND_SOC_NOPM, 0, 0,
			 &adc_right_mux_control),

	SND_SOC_DAPM_ADC("ADC L", शून्य,
			 MT6351_AUDENC_ANA_CON0, RG_AUDADCLPWRUP, 0),
	SND_SOC_DAPM_ADC("ADC R", शून्य,
			 MT6351_AUDENC_ANA_CON1, RG_AUDADCRPWRUP, 0),

	SND_SOC_DAPM_MUX("PGA L Mux", SND_SOC_NOPM, 0, 0,
			 &pga_left_mux_control),
	SND_SOC_DAPM_MUX("PGA R Mux", SND_SOC_NOPM, 0, 0,
			 &pga_right_mux_control),

	SND_SOC_DAPM_PGA_E("PGA L", MT6351_AUDENC_ANA_CON0, RG_AUDPREAMPLON, 0,
			   शून्य, 0,
			   mt_pga_left_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("PGA R", MT6351_AUDENC_ANA_CON1, RG_AUDPREAMPRON, 0,
			   शून्य, 0,
			   mt_pga_right_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),

	/* मुख्य mic mic bias */
	SND_SOC_DAPM_SUPPLY_S("Mic Bias 0", SUPPLY_SUBSEQ_MICBIAS,
			      MT6351_AUDENC_ANA_CON9, RG_AUDPWDBMICBIAS0, 0,
			      mt_mic_bias_0_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	/* ref mic mic bias */
	SND_SOC_DAPM_SUPPLY_S("Mic Bias 2", SUPPLY_SUBSEQ_MICBIAS,
			      MT6351_AUDENC_ANA_CON9, RG_AUDPWDBMICBIAS2, 0,
			      mt_mic_bias_2_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	/* headset mic1/2 mic bias */
	SND_SOC_DAPM_SUPPLY_S("Mic Bias 1", SUPPLY_SUBSEQ_MICBIAS,
			      MT6351_AUDENC_ANA_CON10, RG_AUDPWDBMICBIAS1, 0,
			      mt_mic_bias_1_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY_S("Mic Bias 1 DCC pull high", SUPPLY_SUBSEQ_MICBIAS,
			      MT6351_AUDENC_ANA_CON10,
			      RG_AUDMICBIAS1DCSW1NEN, 0,
			      शून्य, 0),

	/* UL input */
	SND_SOC_DAPM_INPUT("AIN0"),
	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),
	SND_SOC_DAPM_INPUT("AIN3"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mt6351_dapm_routes[] = अणु
	/* Capture */
	अणु"AIF1TX", शून्य, "AIF Out Mux"पूर्ण,
	अणु"AIF1TX", शून्य, "VUSB33_LDO"पूर्ण,
	अणु"VUSB33_LDO", शून्य, "VUSB33_LDO_CTRL"पूर्ण,
	अणु"AIF1TX", शून्य, "VA18_LDO"पूर्ण,
	अणु"VA18_LDO", शून्य, "VA18_LDO_CTRL"पूर्ण,

	अणु"AIF1TX", शून्य, "AUDGLB"पूर्ण,
	अणु"AIF1TX", शून्य, "CLKSQ Audio"पूर्ण,

	अणु"AIF1TX", शून्य, "AFE_ON"पूर्ण,

	अणु"AIF1TX", शून्य, "AUDIO_TOP_AFE_CTL"पूर्ण,
	अणु"AIF1TX", शून्य, "AUDIO_TOP_ADC_CTL"पूर्ण,
	अणु"AIF1TX", शून्य, "AUDIO_TOP_PWR_CLK"पूर्ण,
	अणु"AIF1TX", शून्य, "AUDIO_TOP_PDN_RESERVED"पूर्ण,

	अणु"AIF Out Mux", "Normal Path", "ADC L"पूर्ण,
	अणु"AIF Out Mux", "Normal Path", "ADC R"पूर्ण,

	अणु"ADC L", शून्य, "ADC L Mux"पूर्ण,
	अणु"ADC L", शून्य, "AUD_CK"पूर्ण,
	अणु"ADC L", शून्य, "AUDIF_CK"पूर्ण,
	अणु"ADC L", शून्य, "ADC CLKGEN"पूर्ण,
	अणु"ADC R", शून्य, "ADC R Mux"पूर्ण,
	अणु"ADC R", शून्य, "AUD_CK"पूर्ण,
	अणु"ADC R", शून्य, "AUDIF_CK"पूर्ण,
	अणु"ADC R", शून्य, "ADC CLKGEN"पूर्ण,

	अणु"ADC L Mux", "AIN0", "AIN0"पूर्ण,
	अणु"ADC L Mux", "Left Preamplifier", "PGA L"पूर्ण,

	अणु"ADC R Mux", "AIN0", "AIN0"पूर्ण,
	अणु"ADC R Mux", "Right Preamplifier", "PGA R"पूर्ण,

	अणु"PGA L", शून्य, "PGA L Mux"पूर्ण,
	अणु"PGA R", शून्य, "PGA R Mux"पूर्ण,

	अणु"PGA L Mux", "AIN0", "AIN0"पूर्ण,
	अणु"PGA L Mux", "AIN1", "AIN1"पूर्ण,
	अणु"PGA L Mux", "AIN2", "AIN2"पूर्ण,

	अणु"PGA R Mux", "AIN0", "AIN0"पूर्ण,
	अणु"PGA R Mux", "AIN3", "AIN3"पूर्ण,
	अणु"PGA R Mux", "AIN2", "AIN2"पूर्ण,

	अणु"AIN0", शून्य, "Mic Bias 0"पूर्ण,
	अणु"AIN2", शून्य, "Mic Bias 2"पूर्ण,

	अणु"AIN1", शून्य, "Mic Bias 1"पूर्ण,
	अणु"AIN1", शून्य, "Mic Bias 1 DCC pull high"पूर्ण,

	/* DL Supply */
	अणु"DL Power Supply", शून्य, "AUDGLB"पूर्ण,
	अणु"DL Power Supply", शून्य, "CLKSQ Audio"पूर्ण,
	अणु"DL Power Supply", शून्य, "ZCD13M_CK"पूर्ण,
	अणु"DL Power Supply", शून्य, "AUD_CK"पूर्ण,
	अणु"DL Power Supply", शून्य, "AUDIF_CK"पूर्ण,
	अणु"DL Power Supply", शून्य, "AUDNCP_CK"पूर्ण,

	अणु"DL Power Supply", शून्य, "NV Regulator"पूर्ण,
	अणु"DL Power Supply", शून्य, "AUD_CLK"पूर्ण,
	अणु"DL Power Supply", शून्य, "IBIST"पूर्ण,
	अणु"DL Power Supply", शून्य, "LDO"पूर्ण,
	अणु"LDO", शून्य, "LDO_REMOTE_SENSE"पूर्ण,

	/* DL Digital Supply */
	अणु"DL Digital Clock", शून्य, "AUDIO_TOP_AFE_CTL"पूर्ण,
	अणु"DL Digital Clock", शून्य, "AUDIO_TOP_DAC_CTL"पूर्ण,
	अणु"DL Digital Clock", शून्य, "AUDIO_TOP_PWR_CLK"पूर्ण,
	अणु"DL Digital Clock", शून्य, "AUDIO_TOP_PDN_RESERVED"पूर्ण,
	अणु"DL Digital Clock", शून्य, "NCP"पूर्ण,
	अणु"DL Digital Clock", शून्य, "AFE_ON"पूर्ण,

	अणु"AIF_RX", शून्य, "DL Digital Clock"पूर्ण,

	/* DL Path */
	अणु"DAC In Mux", "Normal Path", "AIF_RX"पूर्ण,

	अणु"DAC In Mux", "Sgen", "SGEN DL"पूर्ण,
	अणु"SGEN DL", शून्य, "SGEN DL SRC"पूर्ण,
	अणु"SGEN DL", शून्य, "SGEN MUTE"पूर्ण,
	अणु"SGEN DL", शून्य, "SGEN DL Enable"पूर्ण,
	अणु"SGEN DL", शून्य, "DL Digital Clock"पूर्ण,

	अणु"DACL", शून्य, "DAC In Mux"पूर्ण,
	अणु"DACL", शून्य, "DL Power Supply"पूर्ण,
	अणु"DACL", शून्य, "DACL_BIASGEN"पूर्ण,

	अणु"DACR", शून्य, "DAC In Mux"पूर्ण,
	अणु"DACR", शून्य, "DL Power Supply"पूर्ण,
	अणु"DACR", शून्य, "DACR_BIASGEN"पूर्ण,

	अणु"LOL Mux", "Playback", "DACL"पूर्ण,

	अणु"LOL Buffer", शून्य, "LOL Mux"पूर्ण,
	अणु"LOL Buffer", शून्य, "LO Stability Enh"पूर्ण,
	अणु"LOL Buffer", शून्य, "LOL Bias Gen"पूर्ण,

	अणु"LINEOUT L", शून्य, "LOL Buffer"पूर्ण,

	/* Headphone Path */
	अणु"HPL Mux", "Audio Playback", "DACL"पूर्ण,
	अणु"HPR Mux", "Audio Playback", "DACR"पूर्ण,

	अणु"HPL Mux", "LoudSPK Playback", "DACL"पूर्ण,
	अणु"HPR Mux", "LoudSPK Playback", "DACR"पूर्ण,

	अणु"HPL Power", शून्य, "HPL Mux"पूर्ण,
	अणु"HPR Power", शून्य, "HPR Mux"पूर्ण,

	अणु"Headphone L", शून्य, "HPL Power"पूर्ण,
	अणु"Headphone R", शून्य, "HPR Power"पूर्ण,

	/* Receiver Path */
	अणु"RCV Mux", "Voice Playback", "DACL"पूर्ण,

	अणु"RCV Buffer", शून्य, "RCV Mux"पूर्ण,
	अणु"RCV Buffer", शून्य, "RCV Stability Enh"पूर्ण,
	अणु"RCV Buffer", शून्य, "RCV Bias Gen"पूर्ण,

	अणु"Receiver", शून्य, "RCV Buffer"पूर्ण,
पूर्ण;

अटल पूर्णांक mt6351_codec_init_reg(काष्ठा snd_soc_component *cmpnt)
अणु
	/* Disable CLKSQ 26MHz */
	regmap_update_bits(cmpnt->regmap, MT6351_TOP_CLKSQ, 0x0001, 0x0);
	/* disable AUDGLB */
	regmap_update_bits(cmpnt->regmap, MT6351_AUDDEC_ANA_CON9,
			   0x1000, 0x1000);
	/* Turn off AUDNCP_CLKDIV engine घड़ी,Turn off AUD 26M */
	regmap_update_bits(cmpnt->regmap, MT6351_TOP_CKPDN_CON0_SET,
			   0x3800, 0x3800);
	/* Disable HeadphoneL/HeadphoneR/voice लघु circuit protection */
	regmap_update_bits(cmpnt->regmap, MT6351_AUDDEC_ANA_CON0,
			   0xe000, 0xe000);
	/* [5] = 1, disable LO buffer left लघु circuit protection */
	regmap_update_bits(cmpnt->regmap, MT6351_AUDDEC_ANA_CON3,
			   0x20, 0x20);
	/* Reverse the PMIC घड़ी*/
	regmap_update_bits(cmpnt->regmap, MT6351_AFE_PMIC_NEWIF_CFG2,
			   0x8000, 0x8000);
	वापस 0;
पूर्ण

अटल पूर्णांक mt6351_codec_probe(काष्ठा snd_soc_component *cmpnt)
अणु
	काष्ठा mt6351_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	snd_soc_component_init_regmap(cmpnt, priv->regmap);

	mt6351_codec_init_reg(cmpnt);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver mt6351_soc_component_driver = अणु
	.probe = mt6351_codec_probe,
	.controls = mt6351_snd_controls,
	.num_controls = ARRAY_SIZE(mt6351_snd_controls),
	.dapm_widमाला_लो = mt6351_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(mt6351_dapm_widमाला_लो),
	.dapm_routes = mt6351_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(mt6351_dapm_routes),
पूर्ण;

अटल पूर्णांक mt6351_codec_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6351_priv *priv;

	priv = devm_kzalloc(&pdev->dev,
			    माप(काष्ठा mt6351_priv),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_set_drvdata(&pdev->dev, priv);

	priv->dev = &pdev->dev;

	priv->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!priv->regmap)
		वापस -ENODEV;

	dev_dbg(priv->dev, "%s(), dev name %s\n",
		__func__, dev_name(&pdev->dev));

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					       &mt6351_soc_component_driver,
					       mt6351_dai_driver,
					       ARRAY_SIZE(mt6351_dai_driver));
पूर्ण

अटल स्थिर काष्ठा of_device_id mt6351_of_match[] = अणु
	अणु.compatible = "mediatek,mt6351-sound",पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver mt6351_codec_driver = अणु
	.driver = अणु
		.name = "mt6351-sound",
		.of_match_table = mt6351_of_match,
	पूर्ण,
	.probe = mt6351_codec_driver_probe,
पूर्ण;

module_platक्रमm_driver(mt6351_codec_driver)

/* Module inक्रमmation */
MODULE_DESCRIPTION("MT6351 ALSA SoC codec driver");
MODULE_AUTHOR("KaiChieh Chuang <kaichieh.chuang@mediatek.com>");
MODULE_LICENSE("GPL v2");
