<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ALSA SoC Texas Instruments TAS6424 Quad-Channel Audio Amplअगरier
 *
 * Copyright (C) 2016-2017 Texas Instruments Incorporated - https://www.ti.com/
 *	Author: Andreas Dannenberg <dannenberg@ti.com>
 *	Andrew F. Davis <afd@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>

#समावेश "tas6424.h"

/* Define how often to check (and clear) the fault status रेजिस्टर (in ms) */
#घोषणा TAS6424_FAULT_CHECK_INTERVAL 200

अटल स्थिर अक्षर * स्थिर tas6424_supply_names[] = अणु
	"dvdd", /* Digital घातer supply. Connect to 3.3-V supply. */
	"vbat", /* Supply used क्रम higher voltage analog circuits. */
	"pvdd", /* Class-D amp output FETs supply. */
पूर्ण;
#घोषणा TAS6424_NUM_SUPPLIES ARRAY_SIZE(tas6424_supply_names)

काष्ठा tas6424_data अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[TAS6424_NUM_SUPPLIES];
	काष्ठा delayed_work fault_check_work;
	अचिन्हित पूर्णांक last_cfault;
	अचिन्हित पूर्णांक last_fault1;
	अचिन्हित पूर्णांक last_fault2;
	अचिन्हित पूर्णांक last_warn;
	काष्ठा gpio_desc *standby_gpio;
	काष्ठा gpio_desc *mute_gpio;
पूर्ण;

/*
 * DAC digital volumes. From -103.5 to 24 dB in 0.5 dB steps. Note that
 * setting the gain below -100 dB (रेजिस्टर value <0x7) is effectively a MUTE
 * as per device datasheet.
 */
अटल DECLARE_TLV_DB_SCALE(dac_tlv, -10350, 50, 0);

अटल स्थिर काष्ठा snd_kcontrol_new tas6424_snd_controls[] = अणु
	SOC_SINGLE_TLV("Speaker Driver CH1 Playback Volume",
		       TAS6424_CH1_VOL_CTRL, 0, 0xff, 0, dac_tlv),
	SOC_SINGLE_TLV("Speaker Driver CH2 Playback Volume",
		       TAS6424_CH2_VOL_CTRL, 0, 0xff, 0, dac_tlv),
	SOC_SINGLE_TLV("Speaker Driver CH3 Playback Volume",
		       TAS6424_CH3_VOL_CTRL, 0, 0xff, 0, dac_tlv),
	SOC_SINGLE_TLV("Speaker Driver CH4 Playback Volume",
		       TAS6424_CH4_VOL_CTRL, 0, 0xff, 0, dac_tlv),
	SOC_SINGLE_STROBE("Auto Diagnostics Switch", TAS6424_DC_DIAG_CTRL1,
			  TAS6424_LDGBYPASS_SHIFT, 1),
पूर्ण;

अटल पूर्णांक tas6424_dac_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा tas6424_data *tas6424 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "%s() event=0x%0x\n", __func__, event);

	अगर (event & SND_SOC_DAPM_POST_PMU) अणु
		/* Observe codec shutकरोwn-to-active समय */
		msleep(12);

		/* Turn on TAS6424 periodic fault checking/handling */
		tas6424->last_fault1 = 0;
		tas6424->last_fault2 = 0;
		tas6424->last_warn = 0;
		schedule_delayed_work(&tas6424->fault_check_work,
				      msecs_to_jअगरfies(TAS6424_FAULT_CHECK_INTERVAL));
	पूर्ण अन्यथा अगर (event & SND_SOC_DAPM_PRE_PMD) अणु
		/* Disable TAS6424 periodic fault checking/handling */
		cancel_delayed_work_sync(&tas6424->fault_check_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget tas6424_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("DAC IN", "Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC_E("DAC", शून्य, SND_SOC_NOPM, 0, 0, tas6424_dac_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_OUTPUT("OUT")
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tas6424_audio_map[] = अणु
	अणु "DAC", शून्य, "DAC IN" पूर्ण,
	अणु "OUT", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल पूर्णांक tas6424_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक width = params_width(params);
	u8 sap_ctrl = 0;

	dev_dbg(component->dev, "%s() rate=%u width=%u\n", __func__, rate, width);

	चयन (rate) अणु
	हाल 44100:
		sap_ctrl |= TAS6424_SAP_RATE_44100;
		अवरोध;
	हाल 48000:
		sap_ctrl |= TAS6424_SAP_RATE_48000;
		अवरोध;
	हाल 96000:
		sap_ctrl |= TAS6424_SAP_RATE_96000;
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported sample rate: %u\n", rate);
		वापस -EINVAL;
	पूर्ण

	चयन (width) अणु
	हाल 16:
		sap_ctrl |= TAS6424_SAP_TDM_SLOT_SZ_16;
		अवरोध;
	हाल 24:
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported sample width: %u\n", width);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, TAS6424_SAP_CTRL,
			    TAS6424_SAP_RATE_MASK |
			    TAS6424_SAP_TDM_SLOT_SZ_16,
			    sap_ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक tas6424_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 serial_क्रमmat = 0;

	dev_dbg(component->dev, "%s() fmt=0x%0x\n", __func__, fmt);

	/* घड़ी masters */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI master/slave interface\n");
		वापस -EINVAL;
	पूर्ण

	/* संकेत polarity */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI clock signal polarity\n");
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		serial_क्रमmat |= TAS6424_SAP_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		serial_क्रमmat |= TAS6424_SAP_DSP;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		/*
		 * We can use the fact that the TAS6424 करोes not care about the
		 * LRCLK duty cycle during TDM to receive DSP_B क्रमmatted data
		 * in LEFTJ mode (no delaying of the 1st data bit).
		 */
		serial_क्रमmat |= TAS6424_SAP_LEFTJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		serial_क्रमmat |= TAS6424_SAP_LEFTJ;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI interface format\n");
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, TAS6424_SAP_CTRL,
			    TAS6424_SAP_FMT_MASK, serial_क्रमmat);

	वापस 0;
पूर्ण

अटल पूर्णांक tas6424_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
				    अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				    पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक first_slot, last_slot;
	bool sap_tdm_slot_last;

	dev_dbg(component->dev, "%s() tx_mask=%d rx_mask=%d\n", __func__,
		tx_mask, rx_mask);

	अगर (!tx_mask || !rx_mask)
		वापस 0; /* nothing needed to disable TDM mode */

	/*
	 * Determine the first slot and last slot that is being requested so
	 * we'll be able to more easily enक्रमce certain स्थिरraपूर्णांकs as the
	 * TAS6424's TDM पूर्णांकerface is not fully configurable.
	 */
	first_slot = __ffs(tx_mask);
	last_slot = __fls(rx_mask);

	अगर (last_slot - first_slot != 4) अणु
		dev_err(component->dev, "tdm mask must cover 4 contiguous slots\n");
		वापस -EINVAL;
	पूर्ण

	चयन (first_slot) अणु
	हाल 0:
		sap_tdm_slot_last = false;
		अवरोध;
	हाल 4:
		sap_tdm_slot_last = true;
		अवरोध;
	शेष:
		dev_err(component->dev, "tdm mask must start at slot 0 or 4\n");
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, TAS6424_SAP_CTRL, TAS6424_SAP_TDM_SLOT_LAST,
			    sap_tdm_slot_last ? TAS6424_SAP_TDM_SLOT_LAST : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक tas6424_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas6424_data *tas6424 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	dev_dbg(component->dev, "%s() mute=%d\n", __func__, mute);

	अगर (tas6424->mute_gpio) अणु
		gpiod_set_value_cansleep(tas6424->mute_gpio, mute);
		वापस 0;
	पूर्ण

	अगर (mute)
		val = TAS6424_ALL_STATE_MUTE;
	अन्यथा
		val = TAS6424_ALL_STATE_PLAY;

	snd_soc_component_ग_लिखो(component, TAS6424_CH_STATE_CTRL, val);

	वापस 0;
पूर्ण

अटल पूर्णांक tas6424_घातer_off(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas6424_data *tas6424 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	snd_soc_component_ग_लिखो(component, TAS6424_CH_STATE_CTRL, TAS6424_ALL_STATE_HIZ);

	regcache_cache_only(tas6424->regmap, true);
	regcache_mark_dirty(tas6424->regmap);

	ret = regulator_bulk_disable(ARRAY_SIZE(tas6424->supplies),
				     tas6424->supplies);
	अगर (ret < 0) अणु
		dev_err(component->dev, "failed to disable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tas6424_घातer_on(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas6424_data *tas6424 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;
	u8 chan_states;
	पूर्णांक no_स्वतः_diags = 0;
	अचिन्हित पूर्णांक reg_val;

	अगर (!regmap_पढ़ो(tas6424->regmap, TAS6424_DC_DIAG_CTRL1, &reg_val))
		no_स्वतः_diags = reg_val & TAS6424_LDGBYPASS_MASK;

	ret = regulator_bulk_enable(ARRAY_SIZE(tas6424->supplies),
				    tas6424->supplies);
	अगर (ret < 0) अणु
		dev_err(component->dev, "failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	regcache_cache_only(tas6424->regmap, false);

	ret = regcache_sync(tas6424->regmap);
	अगर (ret < 0) अणु
		dev_err(component->dev, "failed to sync regcache: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (tas6424->mute_gpio) अणु
		gpiod_set_value_cansleep(tas6424->mute_gpio, 0);
		/*
		 * channels are muted via the mute pin.  Don't also mute
		 * them via the रेजिस्टरs so that subsequent रेजिस्टर
		 * access is not necessary to un-mute the channels
		 */
		chan_states = TAS6424_ALL_STATE_PLAY;
	पूर्ण अन्यथा अणु
		chan_states = TAS6424_ALL_STATE_MUTE;
	पूर्ण
	snd_soc_component_ग_लिखो(component, TAS6424_CH_STATE_CTRL, chan_states);

	/* any समय we come out of HIZ, the output channels स्वतःmatically run DC
	 * load diagnostics अगर स्वतःdiagnotics are enabled. रुको here until this
	 * completes.
	 */
	अगर (!no_स्वतः_diags)
		msleep(230);

	वापस 0;
पूर्ण

अटल पूर्णांक tas6424_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	dev_dbg(component->dev, "%s() level=%d\n", __func__, level);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			tas6424_घातer_on(component);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		tas6424_घातer_off(component);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_component_driver soc_codec_dev_tas6424 = अणु
	.set_bias_level		= tas6424_set_bias_level,
	.controls		= tas6424_snd_controls,
	.num_controls		= ARRAY_SIZE(tas6424_snd_controls),
	.dapm_widमाला_लो		= tas6424_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tas6424_dapm_widमाला_लो),
	.dapm_routes		= tas6424_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(tas6424_audio_map),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops tas6424_speaker_dai_ops = अणु
	.hw_params	= tas6424_hw_params,
	.set_fmt	= tas6424_set_dai_fmt,
	.set_tdm_slot	= tas6424_set_dai_tdm_slot,
	.mute_stream	= tas6424_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver tas6424_dai[] = अणु
	अणु
		.name = "tas6424-amplifier",
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 1,
			.channels_max = 4,
			.rates = TAS6424_RATES,
			.क्रमmats = TAS6424_FORMATS,
		पूर्ण,
		.ops = &tas6424_speaker_dai_ops,
	पूर्ण,
पूर्ण;

अटल व्योम tas6424_fault_check_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tas6424_data *tas6424 = container_of(work, काष्ठा tas6424_data,
						    fault_check_work.work);
	काष्ठा device *dev = tas6424->dev;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tas6424->regmap, TAS6424_CHANNEL_FAULT, &reg);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read CHANNEL_FAULT register: %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (!reg) अणु
		tas6424->last_cfault = reg;
		जाओ check_global_fault1_reg;
	पूर्ण

	/*
	 * Only flag errors once क्रम a given occurrence. This is needed as
	 * the TAS6424 will take समय clearing the fault condition पूर्णांकernally
	 * during which we करोn't want to bombard the प्रणाली with the same
	 * error message over and over.
	 */
	अगर ((reg & TAS6424_FAULT_OC_CH1) && !(tas6424->last_cfault & TAS6424_FAULT_OC_CH1))
		dev_crit(dev, "experienced a channel 1 overcurrent fault\n");

	अगर ((reg & TAS6424_FAULT_OC_CH2) && !(tas6424->last_cfault & TAS6424_FAULT_OC_CH2))
		dev_crit(dev, "experienced a channel 2 overcurrent fault\n");

	अगर ((reg & TAS6424_FAULT_OC_CH3) && !(tas6424->last_cfault & TAS6424_FAULT_OC_CH3))
		dev_crit(dev, "experienced a channel 3 overcurrent fault\n");

	अगर ((reg & TAS6424_FAULT_OC_CH4) && !(tas6424->last_cfault & TAS6424_FAULT_OC_CH4))
		dev_crit(dev, "experienced a channel 4 overcurrent fault\n");

	अगर ((reg & TAS6424_FAULT_DC_CH1) && !(tas6424->last_cfault & TAS6424_FAULT_DC_CH1))
		dev_crit(dev, "experienced a channel 1 DC fault\n");

	अगर ((reg & TAS6424_FAULT_DC_CH2) && !(tas6424->last_cfault & TAS6424_FAULT_DC_CH2))
		dev_crit(dev, "experienced a channel 2 DC fault\n");

	अगर ((reg & TAS6424_FAULT_DC_CH3) && !(tas6424->last_cfault & TAS6424_FAULT_DC_CH3))
		dev_crit(dev, "experienced a channel 3 DC fault\n");

	अगर ((reg & TAS6424_FAULT_DC_CH4) && !(tas6424->last_cfault & TAS6424_FAULT_DC_CH4))
		dev_crit(dev, "experienced a channel 4 DC fault\n");

	/* Store current fault1 value so we can detect any changes next समय */
	tas6424->last_cfault = reg;

check_global_fault1_reg:
	ret = regmap_पढ़ो(tas6424->regmap, TAS6424_GLOB_FAULT1, &reg);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read GLOB_FAULT1 register: %d\n", ret);
		जाओ out;
	पूर्ण

	/*
	 * Ignore any घड़ी faults as there is no clean way to check क्रम them.
	 * We would need to start checking क्रम those faults *after* the SAIF
	 * stream has been setup, and stop checking *beक्रमe* the stream is
	 * stopped to aव्योम any false-positives. However there are no
	 * appropriate hooks to monitor these events.
	 */
	reg &= TAS6424_FAULT_PVDD_OV |
	       TAS6424_FAULT_VBAT_OV |
	       TAS6424_FAULT_PVDD_UV |
	       TAS6424_FAULT_VBAT_UV;

	अगर (!reg) अणु
		tas6424->last_fault1 = reg;
		जाओ check_global_fault2_reg;
	पूर्ण

	अगर ((reg & TAS6424_FAULT_PVDD_OV) && !(tas6424->last_fault1 & TAS6424_FAULT_PVDD_OV))
		dev_crit(dev, "experienced a PVDD overvoltage fault\n");

	अगर ((reg & TAS6424_FAULT_VBAT_OV) && !(tas6424->last_fault1 & TAS6424_FAULT_VBAT_OV))
		dev_crit(dev, "experienced a VBAT overvoltage fault\n");

	अगर ((reg & TAS6424_FAULT_PVDD_UV) && !(tas6424->last_fault1 & TAS6424_FAULT_PVDD_UV))
		dev_crit(dev, "experienced a PVDD undervoltage fault\n");

	अगर ((reg & TAS6424_FAULT_VBAT_UV) && !(tas6424->last_fault1 & TAS6424_FAULT_VBAT_UV))
		dev_crit(dev, "experienced a VBAT undervoltage fault\n");

	/* Store current fault1 value so we can detect any changes next समय */
	tas6424->last_fault1 = reg;

check_global_fault2_reg:
	ret = regmap_पढ़ो(tas6424->regmap, TAS6424_GLOB_FAULT2, &reg);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read GLOB_FAULT2 register: %d\n", ret);
		जाओ out;
	पूर्ण

	reg &= TAS6424_FAULT_OTSD |
	       TAS6424_FAULT_OTSD_CH1 |
	       TAS6424_FAULT_OTSD_CH2 |
	       TAS6424_FAULT_OTSD_CH3 |
	       TAS6424_FAULT_OTSD_CH4;

	अगर (!reg) अणु
		tas6424->last_fault2 = reg;
		जाओ check_warn_reg;
	पूर्ण

	अगर ((reg & TAS6424_FAULT_OTSD) && !(tas6424->last_fault2 & TAS6424_FAULT_OTSD))
		dev_crit(dev, "experienced a global overtemp shutdown\n");

	अगर ((reg & TAS6424_FAULT_OTSD_CH1) && !(tas6424->last_fault2 & TAS6424_FAULT_OTSD_CH1))
		dev_crit(dev, "experienced an overtemp shutdown on CH1\n");

	अगर ((reg & TAS6424_FAULT_OTSD_CH2) && !(tas6424->last_fault2 & TAS6424_FAULT_OTSD_CH2))
		dev_crit(dev, "experienced an overtemp shutdown on CH2\n");

	अगर ((reg & TAS6424_FAULT_OTSD_CH3) && !(tas6424->last_fault2 & TAS6424_FAULT_OTSD_CH3))
		dev_crit(dev, "experienced an overtemp shutdown on CH3\n");

	अगर ((reg & TAS6424_FAULT_OTSD_CH4) && !(tas6424->last_fault2 & TAS6424_FAULT_OTSD_CH4))
		dev_crit(dev, "experienced an overtemp shutdown on CH4\n");

	/* Store current fault2 value so we can detect any changes next समय */
	tas6424->last_fault2 = reg;

check_warn_reg:
	ret = regmap_पढ़ो(tas6424->regmap, TAS6424_WARN, &reg);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read WARN register: %d\n", ret);
		जाओ out;
	पूर्ण

	reg &= TAS6424_WARN_VDD_UV |
	       TAS6424_WARN_VDD_POR |
	       TAS6424_WARN_VDD_OTW |
	       TAS6424_WARN_VDD_OTW_CH1 |
	       TAS6424_WARN_VDD_OTW_CH2 |
	       TAS6424_WARN_VDD_OTW_CH3 |
	       TAS6424_WARN_VDD_OTW_CH4;

	अगर (!reg) अणु
		tas6424->last_warn = reg;
		जाओ out;
	पूर्ण

	अगर ((reg & TAS6424_WARN_VDD_UV) && !(tas6424->last_warn & TAS6424_WARN_VDD_UV))
		dev_warn(dev, "experienced a VDD under voltage condition\n");

	अगर ((reg & TAS6424_WARN_VDD_POR) && !(tas6424->last_warn & TAS6424_WARN_VDD_POR))
		dev_warn(dev, "experienced a VDD POR condition\n");

	अगर ((reg & TAS6424_WARN_VDD_OTW) && !(tas6424->last_warn & TAS6424_WARN_VDD_OTW))
		dev_warn(dev, "experienced a global overtemp warning\n");

	अगर ((reg & TAS6424_WARN_VDD_OTW_CH1) && !(tas6424->last_warn & TAS6424_WARN_VDD_OTW_CH1))
		dev_warn(dev, "experienced an overtemp warning on CH1\n");

	अगर ((reg & TAS6424_WARN_VDD_OTW_CH2) && !(tas6424->last_warn & TAS6424_WARN_VDD_OTW_CH2))
		dev_warn(dev, "experienced an overtemp warning on CH2\n");

	अगर ((reg & TAS6424_WARN_VDD_OTW_CH3) && !(tas6424->last_warn & TAS6424_WARN_VDD_OTW_CH3))
		dev_warn(dev, "experienced an overtemp warning on CH3\n");

	अगर ((reg & TAS6424_WARN_VDD_OTW_CH4) && !(tas6424->last_warn & TAS6424_WARN_VDD_OTW_CH4))
		dev_warn(dev, "experienced an overtemp warning on CH4\n");

	/* Store current warn value so we can detect any changes next समय */
	tas6424->last_warn = reg;

	/* Clear any warnings by toggling the CLEAR_FAULT control bit */
	ret = regmap_ग_लिखो_bits(tas6424->regmap, TAS6424_MISC_CTRL3,
				TAS6424_CLEAR_FAULT, TAS6424_CLEAR_FAULT);
	अगर (ret < 0)
		dev_err(dev, "failed to write MISC_CTRL3 register: %d\n", ret);

	ret = regmap_ग_लिखो_bits(tas6424->regmap, TAS6424_MISC_CTRL3,
				TAS6424_CLEAR_FAULT, 0);
	अगर (ret < 0)
		dev_err(dev, "failed to write MISC_CTRL3 register: %d\n", ret);

out:
	/* Schedule the next fault check at the specअगरied पूर्णांकerval */
	schedule_delayed_work(&tas6424->fault_check_work,
			      msecs_to_jअगरfies(TAS6424_FAULT_CHECK_INTERVAL));
पूर्ण

अटल स्थिर काष्ठा reg_शेष tas6424_reg_शेषs[] = अणु
	अणु TAS6424_MODE_CTRL,		0x00 पूर्ण,
	अणु TAS6424_MISC_CTRL1,		0x32 पूर्ण,
	अणु TAS6424_MISC_CTRL2,		0x62 पूर्ण,
	अणु TAS6424_SAP_CTRL,		0x04 पूर्ण,
	अणु TAS6424_CH_STATE_CTRL,	0x55 पूर्ण,
	अणु TAS6424_CH1_VOL_CTRL,		0xcf पूर्ण,
	अणु TAS6424_CH2_VOL_CTRL,		0xcf पूर्ण,
	अणु TAS6424_CH3_VOL_CTRL,		0xcf पूर्ण,
	अणु TAS6424_CH4_VOL_CTRL,		0xcf पूर्ण,
	अणु TAS6424_DC_DIAG_CTRL1,	0x00 पूर्ण,
	अणु TAS6424_DC_DIAG_CTRL2,	0x11 पूर्ण,
	अणु TAS6424_DC_DIAG_CTRL3,	0x11 पूर्ण,
	अणु TAS6424_PIN_CTRL,		0xff पूर्ण,
	अणु TAS6424_AC_DIAG_CTRL1,	0x00 पूर्ण,
	अणु TAS6424_MISC_CTRL3,		0x00 पूर्ण,
	अणु TAS6424_CLIP_CTRL,		0x01 पूर्ण,
	अणु TAS6424_CLIP_WINDOW,		0x14 पूर्ण,
	अणु TAS6424_CLIP_WARN,		0x00 पूर्ण,
	अणु TAS6424_CBC_STAT,		0x00 पूर्ण,
	अणु TAS6424_MISC_CTRL4,		0x40 पूर्ण,
पूर्ण;

अटल bool tas6424_is_writable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TAS6424_MODE_CTRL:
	हाल TAS6424_MISC_CTRL1:
	हाल TAS6424_MISC_CTRL2:
	हाल TAS6424_SAP_CTRL:
	हाल TAS6424_CH_STATE_CTRL:
	हाल TAS6424_CH1_VOL_CTRL:
	हाल TAS6424_CH2_VOL_CTRL:
	हाल TAS6424_CH3_VOL_CTRL:
	हाल TAS6424_CH4_VOL_CTRL:
	हाल TAS6424_DC_DIAG_CTRL1:
	हाल TAS6424_DC_DIAG_CTRL2:
	हाल TAS6424_DC_DIAG_CTRL3:
	हाल TAS6424_PIN_CTRL:
	हाल TAS6424_AC_DIAG_CTRL1:
	हाल TAS6424_MISC_CTRL3:
	हाल TAS6424_CLIP_CTRL:
	हाल TAS6424_CLIP_WINDOW:
	हाल TAS6424_CLIP_WARN:
	हाल TAS6424_CBC_STAT:
	हाल TAS6424_MISC_CTRL4:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tas6424_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TAS6424_DC_LOAD_DIAG_REP12:
	हाल TAS6424_DC_LOAD_DIAG_REP34:
	हाल TAS6424_DC_LOAD_DIAG_REPLO:
	हाल TAS6424_CHANNEL_STATE:
	हाल TAS6424_CHANNEL_FAULT:
	हाल TAS6424_GLOB_FAULT1:
	हाल TAS6424_GLOB_FAULT2:
	हाल TAS6424_WARN:
	हाल TAS6424_AC_LOAD_DIAG_REP1:
	हाल TAS6424_AC_LOAD_DIAG_REP2:
	हाल TAS6424_AC_LOAD_DIAG_REP3:
	हाल TAS6424_AC_LOAD_DIAG_REP4:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config tas6424_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.ग_लिखोable_reg = tas6424_is_writable_reg,
	.अस्थिर_reg = tas6424_is_अस्थिर_reg,

	.max_रेजिस्टर = TAS6424_MAX,
	.reg_शेषs = tas6424_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(tas6424_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id tas6424_of_ids[] = अणु
	अणु .compatible = "ti,tas6424", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tas6424_of_ids);
#पूर्ण_अगर

अटल पूर्णांक tas6424_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा tas6424_data *tas6424;
	पूर्णांक ret;
	पूर्णांक i;

	tas6424 = devm_kzalloc(dev, माप(*tas6424), GFP_KERNEL);
	अगर (!tas6424)
		वापस -ENOMEM;
	dev_set_drvdata(dev, tas6424);

	tas6424->dev = dev;

	tas6424->regmap = devm_regmap_init_i2c(client, &tas6424_regmap_config);
	अगर (IS_ERR(tas6424->regmap)) अणु
		ret = PTR_ERR(tas6424->regmap);
		dev_err(dev, "unable to allocate register map: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Get control of the standby pin and set it LOW to take the codec
	 * out of the stand-by mode.
	 * Note: The actual pin polarity is taken care of in the GPIO lib
	 * according the polarity specअगरied in the DTS.
	 */
	tas6424->standby_gpio = devm_gpiod_get_optional(dev, "standby",
						      GPIOD_OUT_LOW);
	अगर (IS_ERR(tas6424->standby_gpio)) अणु
		अगर (PTR_ERR(tas6424->standby_gpio) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_info(dev, "failed to get standby GPIO: %ld\n",
			PTR_ERR(tas6424->standby_gpio));
		tas6424->standby_gpio = शून्य;
	पूर्ण

	/*
	 * Get control of the mute pin and set it HIGH in order to start with
	 * all the output muted.
	 * Note: The actual pin polarity is taken care of in the GPIO lib
	 * according the polarity specअगरied in the DTS.
	 */
	tas6424->mute_gpio = devm_gpiod_get_optional(dev, "mute",
						      GPIOD_OUT_HIGH);
	अगर (IS_ERR(tas6424->mute_gpio)) अणु
		अगर (PTR_ERR(tas6424->mute_gpio) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_info(dev, "failed to get nmute GPIO: %ld\n",
			PTR_ERR(tas6424->mute_gpio));
		tas6424->mute_gpio = शून्य;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tas6424->supplies); i++)
		tas6424->supplies[i].supply = tas6424_supply_names[i];
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(tas6424->supplies),
				      tas6424->supplies);
	अगर (ret) अणु
		dev_err(dev, "unable to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(tas6424->supplies),
				    tas6424->supplies);
	अगर (ret) अणु
		dev_err(dev, "unable to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Reset device to establish well-defined startup state */
	ret = regmap_update_bits(tas6424->regmap, TAS6424_MODE_CTRL,
				 TAS6424_RESET, TAS6424_RESET);
	अगर (ret) अणु
		dev_err(dev, "unable to reset device: %d\n", ret);
		वापस ret;
	पूर्ण

	INIT_DELAYED_WORK(&tas6424->fault_check_work, tas6424_fault_check_work);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &soc_codec_dev_tas6424,
				     tas6424_dai, ARRAY_SIZE(tas6424_dai));
	अगर (ret < 0) अणु
		dev_err(dev, "unable to register codec: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tas6424_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा tas6424_data *tas6424 = dev_get_drvdata(dev);
	पूर्णांक ret;

	cancel_delayed_work_sync(&tas6424->fault_check_work);

	/* put the codec in stand-by */
	अगर (tas6424->standby_gpio)
		gpiod_set_value_cansleep(tas6424->standby_gpio, 1);

	ret = regulator_bulk_disable(ARRAY_SIZE(tas6424->supplies),
				     tas6424->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to disable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tas6424_i2c_ids[] = अणु
	अणु "tas6424", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tas6424_i2c_ids);

अटल काष्ठा i2c_driver tas6424_i2c_driver = अणु
	.driver = अणु
		.name = "tas6424",
		.of_match_table = of_match_ptr(tas6424_of_ids),
	पूर्ण,
	.probe = tas6424_i2c_probe,
	.हटाओ = tas6424_i2c_हटाओ,
	.id_table = tas6424_i2c_ids,
पूर्ण;
module_i2c_driver(tas6424_i2c_driver);

MODULE_AUTHOR("Andreas Dannenberg <dannenberg@ti.com>");
MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("TAS6424 Audio amplifier driver");
MODULE_LICENSE("GPL v2");
