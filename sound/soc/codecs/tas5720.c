<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tas5720.c - ALSA SoC Texas Instruments TAS5720 Mono Audio Amplअगरier
 *
 * Copyright (C)2015-2016 Texas Instruments Incorporated -  https://www.ti.com
 *
 * Author: Andreas Dannenberg <dannenberg@ti.com>
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

#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>

#समावेश "tas5720.h"

/* Define how often to check (and clear) the fault status रेजिस्टर (in ms) */
#घोषणा TAS5720_FAULT_CHECK_INTERVAL		200

क्रमागत tas572x_type अणु
	TAS5720,
	TAS5722,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tas5720_supply_names[] = अणु
	"dvdd",		/* Digital घातer supply. Connect to 3.3-V supply. */
	"pvdd",		/* Class-D amp and analog घातer supply (connected). */
पूर्ण;

#घोषणा TAS5720_NUM_SUPPLIES	ARRAY_SIZE(tas5720_supply_names)

काष्ठा tas5720_data अणु
	काष्ठा snd_soc_component *component;
	काष्ठा regmap *regmap;
	काष्ठा i2c_client *tas5720_client;
	क्रमागत tas572x_type devtype;
	काष्ठा regulator_bulk_data supplies[TAS5720_NUM_SUPPLIES];
	काष्ठा delayed_work fault_check_work;
	अचिन्हित पूर्णांक last_fault;
पूर्ण;

अटल पूर्णांक tas5720_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक rate = params_rate(params);
	bool ssz_ds;
	पूर्णांक ret;

	चयन (rate) अणु
	हाल 44100:
	हाल 48000:
		ssz_ds = false;
		अवरोध;
	हाल 88200:
	हाल 96000:
		ssz_ds = true;
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported sample rate: %u\n", rate);
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(component, TAS5720_DIGITAL_CTRL1_REG,
				  TAS5720_SSZ_DS, ssz_ds);
	अगर (ret < 0) अणु
		dev_err(component->dev, "error setting sample rate: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tas5720_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 serial_क्रमmat;
	पूर्णांक ret;

	अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS) अणु
		dev_vdbg(component->dev, "DAI Format master is not found\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & (SND_SOC_DAIFMT_FORMAT_MASK |
		       SND_SOC_DAIFMT_INV_MASK)) अणु
	हाल (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF):
		/* 1st data bit occur one BCLK cycle after the frame sync */
		serial_क्रमmat = TAS5720_SAIF_I2S;
		अवरोध;
	हाल (SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_NB_NF):
		/*
		 * Note that although the TAS5720 करोes not have a dedicated DSP
		 * mode it करोesn't care about the LRCLK duty cycle during TDM
		 * operation. Thereक्रमe we can use the device's I2S mode with
		 * its delaying of the 1st data bit to receive DSP_A क्रमmatted
		 * data. See device datasheet क्रम additional details.
		 */
		serial_क्रमmat = TAS5720_SAIF_I2S;
		अवरोध;
	हाल (SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_NB_NF):
		/*
		 * Similar to DSP_A, we can use the fact that the TAS5720 करोes
		 * not care about the LRCLK duty cycle during TDM to receive
		 * DSP_B क्रमmatted data in LEFTJ mode (no delaying of the 1st
		 * data bit).
		 */
		serial_क्रमmat = TAS5720_SAIF_LEFTJ;
		अवरोध;
	हाल (SND_SOC_DAIFMT_LEFT_J | SND_SOC_DAIFMT_NB_NF):
		/* No delay after the frame sync */
		serial_क्रमmat = TAS5720_SAIF_LEFTJ;
		अवरोध;
	शेष:
		dev_vdbg(component->dev, "DAI Format is not found\n");
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(component, TAS5720_DIGITAL_CTRL1_REG,
				  TAS5720_SAIF_FORMAT_MASK,
				  serial_क्रमmat);
	अगर (ret < 0) अणु
		dev_err(component->dev, "error setting SAIF format: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tas5720_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
				    अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				    पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas5720_data *tas5720 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक first_slot;
	पूर्णांक ret;

	अगर (!tx_mask) अणु
		dev_err(component->dev, "tx masks must not be 0\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Determine the first slot that is being requested. We will only
	 * use the first slot that is found since the TAS5720 is a mono
	 * amplअगरier.
	 */
	first_slot = __ffs(tx_mask);

	अगर (first_slot > 7) अणु
		dev_err(component->dev, "slot selection out of bounds (%u)\n",
			first_slot);
		वापस -EINVAL;
	पूर्ण

	/* Enable manual TDM slot selection (instead of I2C ID based) */
	ret = snd_soc_component_update_bits(component, TAS5720_DIGITAL_CTRL1_REG,
				  TAS5720_TDM_CFG_SRC, TAS5720_TDM_CFG_SRC);
	अगर (ret < 0)
		जाओ error_snd_soc_component_update_bits;

	/* Configure the TDM slot to process audio from */
	ret = snd_soc_component_update_bits(component, TAS5720_DIGITAL_CTRL2_REG,
				  TAS5720_TDM_SLOT_SEL_MASK, first_slot);
	अगर (ret < 0)
		जाओ error_snd_soc_component_update_bits;

	/* Configure TDM slot width. This is only applicable to TAS5722. */
	चयन (tas5720->devtype) अणु
	हाल TAS5722:
		ret = snd_soc_component_update_bits(component, TAS5722_DIGITAL_CTRL2_REG,
						    TAS5722_TDM_SLOT_16B,
						    slot_width == 16 ?
						    TAS5722_TDM_SLOT_16B : 0);
		अगर (ret < 0)
			जाओ error_snd_soc_component_update_bits;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;

error_snd_soc_component_update_bits:
	dev_err(component->dev, "error configuring TDM mode: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tas5720_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक ret;

	ret = snd_soc_component_update_bits(component, TAS5720_DIGITAL_CTRL2_REG,
				  TAS5720_MUTE, mute ? TAS5720_MUTE : 0);
	अगर (ret < 0) अणु
		dev_err(component->dev, "error (un-)muting device: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tas5720_fault_check_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tas5720_data *tas5720 = container_of(work, काष्ठा tas5720_data,
			fault_check_work.work);
	काष्ठा device *dev = tas5720->component->dev;
	अचिन्हित पूर्णांक curr_fault;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tas5720->regmap, TAS5720_FAULT_REG, &curr_fault);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read FAULT register: %d\n", ret);
		जाओ out;
	पूर्ण

	/* Check/handle all errors except SAIF घड़ी errors */
	curr_fault &= TAS5720_OCE | TAS5720_DCE | TAS5720_OTE;

	/*
	 * Only flag errors once क्रम a given occurrence. This is needed as
	 * the TAS5720 will take समय clearing the fault condition पूर्णांकernally
	 * during which we करोn't want to bombard the प्रणाली with the same
	 * error message over and over.
	 */
	अगर ((curr_fault & TAS5720_OCE) && !(tas5720->last_fault & TAS5720_OCE))
		dev_crit(dev, "experienced an over current hardware fault\n");

	अगर ((curr_fault & TAS5720_DCE) && !(tas5720->last_fault & TAS5720_DCE))
		dev_crit(dev, "experienced a DC detection fault\n");

	अगर ((curr_fault & TAS5720_OTE) && !(tas5720->last_fault & TAS5720_OTE))
		dev_crit(dev, "experienced an over temperature fault\n");

	/* Store current fault value so we can detect any changes next समय */
	tas5720->last_fault = curr_fault;

	अगर (!curr_fault)
		जाओ out;

	/*
	 * Periodically toggle SDZ (shutकरोwn bit) H->L->H to clear any latching
	 * faults as दीर्घ as a fault condition persists. Always going through
	 * the full sequence no matter the first वापस value to minimizes
	 * chances क्रम the device to end up in shutकरोwn mode.
	 */
	ret = regmap_ग_लिखो_bits(tas5720->regmap, TAS5720_POWER_CTRL_REG,
				TAS5720_SDZ, 0);
	अगर (ret < 0)
		dev_err(dev, "failed to write POWER_CTRL register: %d\n", ret);

	ret = regmap_ग_लिखो_bits(tas5720->regmap, TAS5720_POWER_CTRL_REG,
				TAS5720_SDZ, TAS5720_SDZ);
	अगर (ret < 0)
		dev_err(dev, "failed to write POWER_CTRL register: %d\n", ret);

out:
	/* Schedule the next fault check at the specअगरied पूर्णांकerval */
	schedule_delayed_work(&tas5720->fault_check_work,
			      msecs_to_jअगरfies(TAS5720_FAULT_CHECK_INTERVAL));
पूर्ण

अटल पूर्णांक tas5720_codec_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas5720_data *tas5720 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक device_id, expected_device_id;
	पूर्णांक ret;

	tas5720->component = component;

	ret = regulator_bulk_enable(ARRAY_SIZE(tas5720->supplies),
				    tas5720->supplies);
	अगर (ret != 0) अणु
		dev_err(component->dev, "failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Take a liberal approach to checking the device ID to allow the
	 * driver to be used even अगर the device ID करोes not match, however
	 * issue a warning अगर there is a mismatch.
	 */
	ret = regmap_पढ़ो(tas5720->regmap, TAS5720_DEVICE_ID_REG, &device_id);
	अगर (ret < 0) अणु
		dev_err(component->dev, "failed to read device ID register: %d\n",
			ret);
		जाओ probe_fail;
	पूर्ण

	चयन (tas5720->devtype) अणु
	हाल TAS5720:
		expected_device_id = TAS5720_DEVICE_ID;
		अवरोध;
	हाल TAS5722:
		expected_device_id = TAS5722_DEVICE_ID;
		अवरोध;
	शेष:
		dev_err(component->dev, "unexpected private driver data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (device_id != expected_device_id)
		dev_warn(component->dev, "wrong device ID. expected: %u read: %u\n",
			 expected_device_id, device_id);

	/* Set device to mute */
	ret = snd_soc_component_update_bits(component, TAS5720_DIGITAL_CTRL2_REG,
				  TAS5720_MUTE, TAS5720_MUTE);
	अगर (ret < 0)
		जाओ error_snd_soc_component_update_bits;

	/*
	 * Enter shutकरोwn mode - our शेष when not playing audio - to
	 * minimize current consumption. On the TAS5720 there is no real करोwn
	 * side करोing so as all device रेजिस्टरs are preserved and the wakeup
	 * of the codec is rather quick which we करो using a dapm widget.
	 */
	ret = snd_soc_component_update_bits(component, TAS5720_POWER_CTRL_REG,
				  TAS5720_SDZ, 0);
	अगर (ret < 0)
		जाओ error_snd_soc_component_update_bits;

	INIT_DELAYED_WORK(&tas5720->fault_check_work, tas5720_fault_check_work);

	वापस 0;

error_snd_soc_component_update_bits:
	dev_err(component->dev, "error configuring device registers: %d\n", ret);

probe_fail:
	regulator_bulk_disable(ARRAY_SIZE(tas5720->supplies),
			       tas5720->supplies);
	वापस ret;
पूर्ण

अटल व्योम tas5720_codec_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas5720_data *tas5720 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	cancel_delayed_work_sync(&tas5720->fault_check_work);

	ret = regulator_bulk_disable(ARRAY_SIZE(tas5720->supplies),
				     tas5720->supplies);
	अगर (ret < 0)
		dev_err(component->dev, "failed to disable supplies: %d\n", ret);
पूर्ण;

अटल पूर्णांक tas5720_dac_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा tas5720_data *tas5720 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	अगर (event & SND_SOC_DAPM_POST_PMU) अणु
		/* Take TAS5720 out of shutकरोwn mode */
		ret = snd_soc_component_update_bits(component, TAS5720_POWER_CTRL_REG,
					  TAS5720_SDZ, TAS5720_SDZ);
		अगर (ret < 0) अणु
			dev_err(component->dev, "error waking component: %d\n", ret);
			वापस ret;
		पूर्ण

		/*
		 * Observe codec shutकरोwn-to-active समय. The datasheet only
		 * lists a nominal value however just use-it as-is without
		 * additional padding to minimize the delay पूर्णांकroduced in
		 * starting to play audio (actually there is other setup करोne
		 * by the ASoC framework that will provide additional delays,
		 * so we should always be safe).
		 */
		msleep(25);

		/* Turn on TAS5720 periodic fault checking/handling */
		tas5720->last_fault = 0;
		schedule_delayed_work(&tas5720->fault_check_work,
				msecs_to_jअगरfies(TAS5720_FAULT_CHECK_INTERVAL));
	पूर्ण अन्यथा अगर (event & SND_SOC_DAPM_PRE_PMD) अणु
		/* Disable TAS5720 periodic fault checking/handling */
		cancel_delayed_work_sync(&tas5720->fault_check_work);

		/* Place TAS5720 in shutकरोwn mode to minimize current draw */
		ret = snd_soc_component_update_bits(component, TAS5720_POWER_CTRL_REG,
					  TAS5720_SDZ, 0);
		अगर (ret < 0) अणु
			dev_err(component->dev, "error shutting down component: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tas5720_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas5720_data *tas5720 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	regcache_cache_only(tas5720->regmap, true);
	regcache_mark_dirty(tas5720->regmap);

	ret = regulator_bulk_disable(ARRAY_SIZE(tas5720->supplies),
				     tas5720->supplies);
	अगर (ret < 0)
		dev_err(component->dev, "failed to disable supplies: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक tas5720_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas5720_data *tas5720 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(tas5720->supplies),
				    tas5720->supplies);
	अगर (ret < 0) अणु
		dev_err(component->dev, "failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	regcache_cache_only(tas5720->regmap, false);

	ret = regcache_sync(tas5720->regmap);
	अगर (ret < 0) अणु
		dev_err(component->dev, "failed to sync regcache: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा tas5720_suspend शून्य
#घोषणा tas5720_resume शून्य
#पूर्ण_अगर

अटल bool tas5720_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TAS5720_DEVICE_ID_REG:
	हाल TAS5720_FAULT_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config tas5720_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = TAS5720_MAX_REG,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = tas5720_is_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tas5722_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = TAS5722_MAX_REG,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = tas5720_is_अस्थिर_reg,
पूर्ण;

/*
 * DAC analog gain. There are four discrete values to select from, ranging
 * from 19.2 dB to 26.3dB.
 */
अटल स्थिर DECLARE_TLV_DB_RANGE(dac_analog_tlv,
	0x0, 0x0, TLV_DB_SCALE_ITEM(1920, 0, 0),
	0x1, 0x1, TLV_DB_SCALE_ITEM(2070, 0, 0),
	0x2, 0x2, TLV_DB_SCALE_ITEM(2350, 0, 0),
	0x3, 0x3, TLV_DB_SCALE_ITEM(2630, 0, 0),
);

/*
 * DAC digital volumes. From -103.5 to 24 dB in 0.5 dB or 0.25 dB steps
 * depending on the device. Note that setting the gain below -100 dB
 * (रेजिस्टर value <0x7) is effectively a MUTE as per device datasheet.
 *
 * Note that क्रम the TAS5722 the digital volume controls are actually split
 * over two रेजिस्टरs, so we need custom getters/setters क्रम access.
 */
अटल DECLARE_TLV_DB_SCALE(tas5720_dac_tlv, -10350, 50, 0);
अटल DECLARE_TLV_DB_SCALE(tas5722_dac_tlv, -10350, 25, 0);

अटल पूर्णांक tas5722_volume_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, TAS5720_VOLUME_CTRL_REG);
	ucontrol->value.पूर्णांकeger.value[0] = val << 1;

	val = snd_soc_component_पढ़ो(component, TAS5722_DIGITAL_CTRL2_REG);
	ucontrol->value.पूर्णांकeger.value[0] |= val & TAS5722_VOL_CONTROL_LSB;

	वापस 0;
पूर्ण

अटल पूर्णांक tas5722_volume_set(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक sel = ucontrol->value.पूर्णांकeger.value[0];

	snd_soc_component_ग_लिखो(component, TAS5720_VOLUME_CTRL_REG, sel >> 1);
	snd_soc_component_update_bits(component, TAS5722_DIGITAL_CTRL2_REG,
				      TAS5722_VOL_CONTROL_LSB, sel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new tas5720_snd_controls[] = अणु
	SOC_SINGLE_TLV("Speaker Driver Playback Volume",
		       TAS5720_VOLUME_CTRL_REG, 0, 0xff, 0, tas5720_dac_tlv),
	SOC_SINGLE_TLV("Speaker Driver Analog Gain", TAS5720_ANALOG_CTRL_REG,
		       TAS5720_ANALOG_GAIN_SHIFT, 3, 0, dac_analog_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tas5722_snd_controls[] = अणु
	SOC_SINGLE_EXT_TLV("Speaker Driver Playback Volume",
			   0, 0, 511, 0,
			   tas5722_volume_get, tas5722_volume_set,
			   tas5722_dac_tlv),
	SOC_SINGLE_TLV("Speaker Driver Analog Gain", TAS5720_ANALOG_CTRL_REG,
		       TAS5720_ANALOG_GAIN_SHIFT, 3, 0, dac_analog_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tas5720_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("DAC IN", "Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC_E("DAC", शून्य, SND_SOC_NOPM, 0, 0, tas5720_dac_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_OUTPUT("OUT")
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tas5720_audio_map[] = अणु
	अणु "DAC", शून्य, "DAC IN" पूर्ण,
	अणु "OUT", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_tas5720 = अणु
	.probe			= tas5720_codec_probe,
	.हटाओ			= tas5720_codec_हटाओ,
	.suspend		= tas5720_suspend,
	.resume			= tas5720_resume,
	.controls		= tas5720_snd_controls,
	.num_controls		= ARRAY_SIZE(tas5720_snd_controls),
	.dapm_widमाला_लो		= tas5720_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tas5720_dapm_widमाला_लो),
	.dapm_routes		= tas5720_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(tas5720_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_tas5722 = अणु
	.probe = tas5720_codec_probe,
	.हटाओ = tas5720_codec_हटाओ,
	.suspend = tas5720_suspend,
	.resume = tas5720_resume,
	.controls = tas5722_snd_controls,
	.num_controls = ARRAY_SIZE(tas5722_snd_controls),
	.dapm_widमाला_लो = tas5720_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tas5720_dapm_widमाला_लो),
	.dapm_routes = tas5720_audio_map,
	.num_dapm_routes = ARRAY_SIZE(tas5720_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

/* PCM rates supported by the TAS5720 driver */
#घोषणा TAS5720_RATES	(SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |\
			 SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000)

/* Formats supported by TAS5720 driver */
#घोषणा TAS5720_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S18_3LE |\
			 SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops tas5720_speaker_dai_ops = अणु
	.hw_params	= tas5720_hw_params,
	.set_fmt	= tas5720_set_dai_fmt,
	.set_tdm_slot	= tas5720_set_dai_tdm_slot,
	.mute_stream	= tas5720_mute,
	.no_capture_mute = 1,
पूर्ण;

/*
 * TAS5720 DAI काष्ठाure
 *
 * Note that were are advertising .playback.channels_max = 2 despite this being
 * a mono amplअगरier. The reason क्रम that is that some serial ports such as TI's
 * McASP module have a minimum number of channels (2) that they can output.
 * Advertising more channels than we have will allow us to पूर्णांकerface with such
 * a serial port without really any negative side effects as the TAS5720 will
 * simply ignore any extra channel(s) asides from the one channel that is
 * configured to be played back.
 */
अटल काष्ठा snd_soc_dai_driver tas5720_dai[] = अणु
	अणु
		.name = "tas5720-amplifier",
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = TAS5720_RATES,
			.क्रमmats = TAS5720_FORMATS,
		पूर्ण,
		.ops = &tas5720_speaker_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक tas5720_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा tas5720_data *data;
	स्थिर काष्ठा regmap_config *regmap_config;
	पूर्णांक ret;
	पूर्णांक i;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->tas5720_client = client;
	data->devtype = id->driver_data;

	चयन (id->driver_data) अणु
	हाल TAS5720:
		regmap_config = &tas5720_regmap_config;
		अवरोध;
	हाल TAS5722:
		regmap_config = &tas5722_regmap_config;
		अवरोध;
	शेष:
		dev_err(dev, "unexpected private driver data\n");
		वापस -EINVAL;
	पूर्ण
	data->regmap = devm_regmap_init_i2c(client, regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		ret = PTR_ERR(data->regmap);
		dev_err(dev, "failed to allocate register map: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data->supplies); i++)
		data->supplies[i].supply = tas5720_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(data->supplies),
				      data->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_set_drvdata(dev, data);

	चयन (id->driver_data) अणु
	हाल TAS5720:
		ret = devm_snd_soc_रेजिस्टर_component(&client->dev,
					&soc_component_dev_tas5720,
					tas5720_dai,
					ARRAY_SIZE(tas5720_dai));
		अवरोध;
	हाल TAS5722:
		ret = devm_snd_soc_रेजिस्टर_component(&client->dev,
					&soc_component_dev_tas5722,
					tas5720_dai,
					ARRAY_SIZE(tas5720_dai));
		अवरोध;
	शेष:
		dev_err(dev, "unexpected private driver data\n");
		वापस -EINVAL;
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register component: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tas5720_id[] = अणु
	अणु "tas5720", TAS5720 पूर्ण,
	अणु "tas5722", TAS5722 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tas5720_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id tas5720_of_match[] = अणु
	अणु .compatible = "ti,tas5720", पूर्ण,
	अणु .compatible = "ti,tas5722", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tas5720_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver tas5720_i2c_driver = अणु
	.driver = अणु
		.name = "tas5720",
		.of_match_table = of_match_ptr(tas5720_of_match),
	पूर्ण,
	.probe = tas5720_probe,
	.id_table = tas5720_id,
पूर्ण;

module_i2c_driver(tas5720_i2c_driver);

MODULE_AUTHOR("Andreas Dannenberg <dannenberg@ti.com>");
MODULE_DESCRIPTION("TAS5720 Audio amplifier driver");
MODULE_LICENSE("GPL");
