<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm_hubs.c  --  WM8993/4 common code
 *
 * Copyright 2009-12 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/wm8994/रेजिस्टरs.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm8993.h"
#समावेश "wm_hubs.h"

स्थिर DECLARE_TLV_DB_SCALE(wm_hubs_spkmix_tlv, -300, 300, 0);
EXPORT_SYMBOL_GPL(wm_hubs_spkmix_tlv);

अटल स्थिर DECLARE_TLV_DB_SCALE(inpga_tlv, -1650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(inmix_sw_tlv, 0, 3000, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(inmix_tlv, -1500, 300, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(earpiece_tlv, -600, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(ouपंचांगix_tlv, -2100, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(spkmixout_tlv, -1800, 600, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(outpga_tlv, -5700, 100, 0);
अटल स्थिर DECLARE_TLV_DB_RANGE(spkboost_tlv,
	0, 6, TLV_DB_SCALE_ITEM(0, 150, 0),
	7, 7, TLV_DB_SCALE_ITEM(1200, 0, 0)
);
अटल स्थिर DECLARE_TLV_DB_SCALE(line_tlv, -600, 600, 0);

अटल स्थिर अक्षर *speaker_ref_text[] = अणु
	"SPKVDD/2",
	"VMID",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(speaker_ref,
			    WM8993_SPEAKER_MIXER, 8, speaker_ref_text);

अटल स्थिर अक्षर *speaker_mode_text[] = अणु
	"Class D",
	"Class AB",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(speaker_mode,
			    WM8993_SPKMIXR_ATTENUATION, 8, speaker_mode_text);

अटल व्योम रुको_क्रम_dc_servo(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक op)
अणु
	काष्ठा wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg;
	पूर्णांक count = 0;
	पूर्णांक समयout;
	अचिन्हित पूर्णांक val;

	val = op | WM8993_DCS_ENA_CHAN_0 | WM8993_DCS_ENA_CHAN_1;

	/* Trigger the command */
	snd_soc_component_ग_लिखो(component, WM8993_DC_SERVO_0, val);

	dev_dbg(component->dev, "Waiting for DC servo...\n");

	अगर (hubs->dcs_करोne_irq)
		समयout = 4;
	अन्यथा
		समयout = 400;

	करो अणु
		count++;

		अगर (hubs->dcs_करोne_irq)
			रुको_क्रम_completion_समयout(&hubs->dcs_करोne,
						    msecs_to_jअगरfies(250));
		अन्यथा
			msleep(1);

		reg = snd_soc_component_पढ़ो(component, WM8993_DC_SERVO_0);
		dev_dbg(component->dev, "DC servo: %x\n", reg);
	पूर्ण जबतक (reg & op && count < समयout);

	अगर (reg & op)
		dev_err(component->dev, "Timed out waiting for DC Servo %x\n",
			op);
पूर्ण

irqवापस_t wm_hubs_dcs_करोne(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm_hubs_data *hubs = data;

	complete(&hubs->dcs_करोne);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL_GPL(wm_hubs_dcs_करोne);

अटल bool wm_hubs_dac_hp_direct(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक reg;

	/* If we're going via the mixer we'll need to करो additional checks */
	reg = snd_soc_component_पढ़ो(component, WM8993_OUTPUT_MIXER1);
	अगर (!(reg & WM8993_DACL_TO_HPOUT1L)) अणु
		अगर (reg & ~WM8993_DACL_TO_MIXOUTL) अणु
			dev_vdbg(component->dev, "Analogue paths connected: %x\n",
				 reg & ~WM8993_DACL_TO_HPOUT1L);
			वापस false;
		पूर्ण अन्यथा अणु
			dev_vdbg(component->dev, "HPL connected to mixer\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_vdbg(component->dev, "HPL connected to DAC\n");
	पूर्ण

	reg = snd_soc_component_पढ़ो(component, WM8993_OUTPUT_MIXER2);
	अगर (!(reg & WM8993_DACR_TO_HPOUT1R)) अणु
		अगर (reg & ~WM8993_DACR_TO_MIXOUTR) अणु
			dev_vdbg(component->dev, "Analogue paths connected: %x\n",
				 reg & ~WM8993_DACR_TO_HPOUT1R);
			वापस false;
		पूर्ण अन्यथा अणु
			dev_vdbg(component->dev, "HPR connected to mixer\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_vdbg(component->dev, "HPR connected to DAC\n");
	पूर्ण

	वापस true;
पूर्ण

काष्ठा wm_hubs_dcs_cache अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक left;
	अचिन्हित पूर्णांक right;
	u16 dcs_cfg;
पूर्ण;

अटल bool wm_hubs_dcs_cache_get(काष्ठा snd_soc_component *component,
				  काष्ठा wm_hubs_dcs_cache **entry)
अणु
	काष्ठा wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	काष्ठा wm_hubs_dcs_cache *cache;
	अचिन्हित पूर्णांक left, right;

	left = snd_soc_component_पढ़ो(component, WM8993_LEFT_OUTPUT_VOLUME);
	left &= WM8993_HPOUT1L_VOL_MASK;

	right = snd_soc_component_पढ़ो(component, WM8993_RIGHT_OUTPUT_VOLUME);
	right &= WM8993_HPOUT1R_VOL_MASK;

	list_क्रम_each_entry(cache, &hubs->dcs_cache, list) अणु
		अगर (cache->left != left || cache->right != right)
			जारी;

		*entry = cache;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम wm_hubs_dcs_cache_set(काष्ठा snd_soc_component *component, u16 dcs_cfg)
अणु
	काष्ठा wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	काष्ठा wm_hubs_dcs_cache *cache;

	अगर (hubs->no_cache_dac_hp_direct)
		वापस;

	cache = devm_kzalloc(component->dev, माप(*cache), GFP_KERNEL);
	अगर (!cache)
		वापस;

	cache->left = snd_soc_component_पढ़ो(component, WM8993_LEFT_OUTPUT_VOLUME);
	cache->left &= WM8993_HPOUT1L_VOL_MASK;

	cache->right = snd_soc_component_पढ़ो(component, WM8993_RIGHT_OUTPUT_VOLUME);
	cache->right &= WM8993_HPOUT1R_VOL_MASK;

	cache->dcs_cfg = dcs_cfg;

	list_add_tail(&cache->list, &hubs->dcs_cache);
पूर्ण

अटल पूर्णांक wm_hubs_पढ़ो_dc_servo(काष्ठा snd_soc_component *component,
				  u16 *reg_l, u16 *reg_r)
अणु
	काष्ठा wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	u16 dcs_reg, reg;
	पूर्णांक ret = 0;

	चयन (hubs->dcs_पढ़ोback_mode) अणु
	हाल 2:
		dcs_reg = WM8994_DC_SERVO_4E;
		अवरोध;
	हाल 1:
		dcs_reg = WM8994_DC_SERVO_READBACK;
		अवरोध;
	शेष:
		dcs_reg = WM8993_DC_SERVO_3;
		अवरोध;
	पूर्ण

	/* Dअगरferent chips in the family support dअगरferent पढ़ोback
	 * methods.
	 */
	चयन (hubs->dcs_पढ़ोback_mode) अणु
	हाल 0:
		*reg_l = snd_soc_component_पढ़ो(component, WM8993_DC_SERVO_READBACK_1)
			& WM8993_DCS_INTEG_CHAN_0_MASK;
		*reg_r = snd_soc_component_पढ़ो(component, WM8993_DC_SERVO_READBACK_2)
			& WM8993_DCS_INTEG_CHAN_1_MASK;
		अवरोध;
	हाल 2:
	हाल 1:
		reg = snd_soc_component_पढ़ो(component, dcs_reg);
		*reg_r = (reg & WM8993_DCS_DAC_WR_VAL_1_MASK)
			>> WM8993_DCS_DAC_WR_VAL_1_SHIFT;
		*reg_l = reg & WM8993_DCS_DAC_WR_VAL_0_MASK;
		अवरोध;
	शेष:
		WARN(1, "Unknown DCS readback method\n");
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Startup calibration of the DC servo
 */
अटल व्योम enable_dc_servo(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	काष्ठा wm_hubs_dcs_cache *cache;
	s8 offset;
	u16 reg_l, reg_r, dcs_cfg, dcs_reg;

	चयन (hubs->dcs_पढ़ोback_mode) अणु
	हाल 2:
		dcs_reg = WM8994_DC_SERVO_4E;
		अवरोध;
	शेष:
		dcs_reg = WM8993_DC_SERVO_3;
		अवरोध;
	पूर्ण

	/* If we're using a digital only path and have a previously
	 * callibrated DC servo offset stored then use that. */
	अगर (wm_hubs_dac_hp_direct(component) &&
	    wm_hubs_dcs_cache_get(component, &cache)) अणु
		dev_dbg(component->dev, "Using cached DCS offset %x for %d,%d\n",
			cache->dcs_cfg, cache->left, cache->right);
		snd_soc_component_ग_लिखो(component, dcs_reg, cache->dcs_cfg);
		रुको_क्रम_dc_servo(component,
				  WM8993_DCS_TRIG_DAC_WR_0 |
				  WM8993_DCS_TRIG_DAC_WR_1);
		वापस;
	पूर्ण

	अगर (hubs->series_startup) अणु
		/* Set क्रम 32 series updates */
		snd_soc_component_update_bits(component, WM8993_DC_SERVO_1,
				    WM8993_DCS_SERIES_NO_01_MASK,
				    32 << WM8993_DCS_SERIES_NO_01_SHIFT);
		रुको_क्रम_dc_servo(component,
				  WM8993_DCS_TRIG_SERIES_0 |
				  WM8993_DCS_TRIG_SERIES_1);
	पूर्ण अन्यथा अणु
		रुको_क्रम_dc_servo(component,
				  WM8993_DCS_TRIG_STARTUP_0 |
				  WM8993_DCS_TRIG_STARTUP_1);
	पूर्ण

	अगर (wm_hubs_पढ़ो_dc_servo(component, &reg_l, &reg_r) < 0)
		वापस;

	dev_dbg(component->dev, "DCS input: %x %x\n", reg_l, reg_r);

	/* Apply correction to DC servo result */
	अगर (hubs->dcs_codes_l || hubs->dcs_codes_r) अणु
		dev_dbg(component->dev,
			"Applying %d/%d code DC servo correction\n",
			hubs->dcs_codes_l, hubs->dcs_codes_r);

		/* HPOUT1R */
		offset = (s8)reg_r;
		dev_dbg(component->dev, "DCS right %d->%d\n", offset,
			offset + hubs->dcs_codes_r);
		offset += hubs->dcs_codes_r;
		dcs_cfg = (u8)offset << WM8993_DCS_DAC_WR_VAL_1_SHIFT;

		/* HPOUT1L */
		offset = (s8)reg_l;
		dev_dbg(component->dev, "DCS left %d->%d\n", offset,
			offset + hubs->dcs_codes_l);
		offset += hubs->dcs_codes_l;
		dcs_cfg |= (u8)offset;

		dev_dbg(component->dev, "DCS result: %x\n", dcs_cfg);

		/* Do it */
		snd_soc_component_ग_लिखो(component, dcs_reg, dcs_cfg);
		रुको_क्रम_dc_servo(component,
				  WM8993_DCS_TRIG_DAC_WR_0 |
				  WM8993_DCS_TRIG_DAC_WR_1);
	पूर्ण अन्यथा अणु
		dcs_cfg = reg_r << WM8993_DCS_DAC_WR_VAL_1_SHIFT;
		dcs_cfg |= reg_l;
	पूर्ण

	/* Save the callibrated offset अगर we're in class W mode and
	 * thereक्रमe करोn't have any analogue संकेत mixed in. */
	अगर (wm_hubs_dac_hp_direct(component))
		wm_hubs_dcs_cache_set(component, dcs_cfg);
पूर्ण

/*
 * Update the DC servo calibration on gain changes
 */
अटल पूर्णांक wm8993_put_dc_servo(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = snd_soc_put_volsw(kcontrol, ucontrol);

	/* If we're applying an offset correction then updating the
	 * callibration would be likely to पूर्णांकroduce further offsets. */
	अगर (hubs->dcs_codes_l || hubs->dcs_codes_r || hubs->no_series_update)
		वापस ret;

	/* Only need to करो this अगर the outमाला_दो are active */
	अगर (snd_soc_component_पढ़ो(component, WM8993_POWER_MANAGEMENT_1)
	    & (WM8993_HPOUT1L_ENA | WM8993_HPOUT1R_ENA))
		snd_soc_component_update_bits(component,
				    WM8993_DC_SERVO_0,
				    WM8993_DCS_TRIG_SINGLE_0 |
				    WM8993_DCS_TRIG_SINGLE_1,
				    WM8993_DCS_TRIG_SINGLE_0 |
				    WM8993_DCS_TRIG_SINGLE_1);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new analogue_snd_controls[] = अणु
SOC_SINGLE_TLV("IN1L Volume", WM8993_LEFT_LINE_INPUT_1_2_VOLUME, 0, 31, 0,
	       inpga_tlv),
SOC_SINGLE("IN1L Switch", WM8993_LEFT_LINE_INPUT_1_2_VOLUME, 7, 1, 1),
SOC_SINGLE("IN1L ZC Switch", WM8993_LEFT_LINE_INPUT_1_2_VOLUME, 6, 1, 0),

SOC_SINGLE_TLV("IN1R Volume", WM8993_RIGHT_LINE_INPUT_1_2_VOLUME, 0, 31, 0,
	       inpga_tlv),
SOC_SINGLE("IN1R Switch", WM8993_RIGHT_LINE_INPUT_1_2_VOLUME, 7, 1, 1),
SOC_SINGLE("IN1R ZC Switch", WM8993_RIGHT_LINE_INPUT_1_2_VOLUME, 6, 1, 0),


SOC_SINGLE_TLV("IN2L Volume", WM8993_LEFT_LINE_INPUT_3_4_VOLUME, 0, 31, 0,
	       inpga_tlv),
SOC_SINGLE("IN2L Switch", WM8993_LEFT_LINE_INPUT_3_4_VOLUME, 7, 1, 1),
SOC_SINGLE("IN2L ZC Switch", WM8993_LEFT_LINE_INPUT_3_4_VOLUME, 6, 1, 0),

SOC_SINGLE_TLV("IN2R Volume", WM8993_RIGHT_LINE_INPUT_3_4_VOLUME, 0, 31, 0,
	       inpga_tlv),
SOC_SINGLE("IN2R Switch", WM8993_RIGHT_LINE_INPUT_3_4_VOLUME, 7, 1, 1),
SOC_SINGLE("IN2R ZC Switch", WM8993_RIGHT_LINE_INPUT_3_4_VOLUME, 6, 1, 0),

SOC_SINGLE_TLV("MIXINL IN2L Volume", WM8993_INPUT_MIXER3, 7, 1, 0,
	       inmix_sw_tlv),
SOC_SINGLE_TLV("MIXINL IN1L Volume", WM8993_INPUT_MIXER3, 4, 1, 0,
	       inmix_sw_tlv),
SOC_SINGLE_TLV("MIXINL Output Record Volume", WM8993_INPUT_MIXER3, 0, 7, 0,
	       inmix_tlv),
SOC_SINGLE_TLV("MIXINL IN1LP Volume", WM8993_INPUT_MIXER5, 6, 7, 0, inmix_tlv),
SOC_SINGLE_TLV("MIXINL Direct Voice Volume", WM8993_INPUT_MIXER5, 0, 6, 0,
	       inmix_tlv),

SOC_SINGLE_TLV("MIXINR IN2R Volume", WM8993_INPUT_MIXER4, 7, 1, 0,
	       inmix_sw_tlv),
SOC_SINGLE_TLV("MIXINR IN1R Volume", WM8993_INPUT_MIXER4, 4, 1, 0,
	       inmix_sw_tlv),
SOC_SINGLE_TLV("MIXINR Output Record Volume", WM8993_INPUT_MIXER4, 0, 7, 0,
	       inmix_tlv),
SOC_SINGLE_TLV("MIXINR IN1RP Volume", WM8993_INPUT_MIXER6, 6, 7, 0, inmix_tlv),
SOC_SINGLE_TLV("MIXINR Direct Voice Volume", WM8993_INPUT_MIXER6, 0, 6, 0,
	       inmix_tlv),

SOC_SINGLE_TLV("Left Output Mixer IN2RN Volume", WM8993_OUTPUT_MIXER5, 6, 7, 1,
	       ouपंचांगix_tlv),
SOC_SINGLE_TLV("Left Output Mixer IN2LN Volume", WM8993_OUTPUT_MIXER3, 6, 7, 1,
	       ouपंचांगix_tlv),
SOC_SINGLE_TLV("Left Output Mixer IN2LP Volume", WM8993_OUTPUT_MIXER3, 9, 7, 1,
	       ouपंचांगix_tlv),
SOC_SINGLE_TLV("Left Output Mixer IN1L Volume", WM8993_OUTPUT_MIXER3, 0, 7, 1,
	       ouपंचांगix_tlv),
SOC_SINGLE_TLV("Left Output Mixer IN1R Volume", WM8993_OUTPUT_MIXER3, 3, 7, 1,
	       ouपंचांगix_tlv),
SOC_SINGLE_TLV("Left Output Mixer Right Input Volume",
	       WM8993_OUTPUT_MIXER5, 3, 7, 1, ouपंचांगix_tlv),
SOC_SINGLE_TLV("Left Output Mixer Left Input Volume",
	       WM8993_OUTPUT_MIXER5, 0, 7, 1, ouपंचांगix_tlv),
SOC_SINGLE_TLV("Left Output Mixer DAC Volume", WM8993_OUTPUT_MIXER5, 9, 7, 1,
	       ouपंचांगix_tlv),

SOC_SINGLE_TLV("Right Output Mixer IN2LN Volume",
	       WM8993_OUTPUT_MIXER6, 6, 7, 1, ouपंचांगix_tlv),
SOC_SINGLE_TLV("Right Output Mixer IN2RN Volume",
	       WM8993_OUTPUT_MIXER4, 6, 7, 1, ouपंचांगix_tlv),
SOC_SINGLE_TLV("Right Output Mixer IN1L Volume",
	       WM8993_OUTPUT_MIXER4, 3, 7, 1, ouपंचांगix_tlv),
SOC_SINGLE_TLV("Right Output Mixer IN1R Volume",
	       WM8993_OUTPUT_MIXER4, 0, 7, 1, ouपंचांगix_tlv),
SOC_SINGLE_TLV("Right Output Mixer IN2RP Volume",
	       WM8993_OUTPUT_MIXER4, 9, 7, 1, ouपंचांगix_tlv),
SOC_SINGLE_TLV("Right Output Mixer Left Input Volume",
	       WM8993_OUTPUT_MIXER6, 3, 7, 1, ouपंचांगix_tlv),
SOC_SINGLE_TLV("Right Output Mixer Right Input Volume",
	       WM8993_OUTPUT_MIXER6, 6, 7, 1, ouपंचांगix_tlv),
SOC_SINGLE_TLV("Right Output Mixer DAC Volume",
	       WM8993_OUTPUT_MIXER6, 9, 7, 1, ouपंचांगix_tlv),

SOC_DOUBLE_R_TLV("Output Volume", WM8993_LEFT_OPGA_VOLUME,
		 WM8993_RIGHT_OPGA_VOLUME, 0, 63, 0, outpga_tlv),
SOC_DOUBLE_R("Output Switch", WM8993_LEFT_OPGA_VOLUME,
	     WM8993_RIGHT_OPGA_VOLUME, 6, 1, 0),
SOC_DOUBLE_R("Output ZC Switch", WM8993_LEFT_OPGA_VOLUME,
	     WM8993_RIGHT_OPGA_VOLUME, 7, 1, 0),

SOC_SINGLE("Earpiece Switch", WM8993_HPOUT2_VOLUME, 5, 1, 1),
SOC_SINGLE_TLV("Earpiece Volume", WM8993_HPOUT2_VOLUME, 4, 1, 1, earpiece_tlv),

SOC_SINGLE_TLV("SPKL Input Volume", WM8993_SPKMIXL_ATTENUATION,
	       5, 1, 1, wm_hubs_spkmix_tlv),
SOC_SINGLE_TLV("SPKL IN1LP Volume", WM8993_SPKMIXL_ATTENUATION,
	       4, 1, 1, wm_hubs_spkmix_tlv),
SOC_SINGLE_TLV("SPKL Output Volume", WM8993_SPKMIXL_ATTENUATION,
	       3, 1, 1, wm_hubs_spkmix_tlv),

SOC_SINGLE_TLV("SPKR Input Volume", WM8993_SPKMIXR_ATTENUATION,
	       5, 1, 1, wm_hubs_spkmix_tlv),
SOC_SINGLE_TLV("SPKR IN1RP Volume", WM8993_SPKMIXR_ATTENUATION,
	       4, 1, 1, wm_hubs_spkmix_tlv),
SOC_SINGLE_TLV("SPKR Output Volume", WM8993_SPKMIXR_ATTENUATION,
	       3, 1, 1, wm_hubs_spkmix_tlv),

SOC_DOUBLE_R_TLV("Speaker Mixer Volume",
		 WM8993_SPKMIXL_ATTENUATION, WM8993_SPKMIXR_ATTENUATION,
		 0, 3, 1, spkmixout_tlv),
SOC_DOUBLE_R_TLV("Speaker Volume",
		 WM8993_SPEAKER_VOLUME_LEFT, WM8993_SPEAKER_VOLUME_RIGHT,
		 0, 63, 0, outpga_tlv),
SOC_DOUBLE_R("Speaker Switch",
	     WM8993_SPEAKER_VOLUME_LEFT, WM8993_SPEAKER_VOLUME_RIGHT,
	     6, 1, 0),
SOC_DOUBLE_R("Speaker ZC Switch",
	     WM8993_SPEAKER_VOLUME_LEFT, WM8993_SPEAKER_VOLUME_RIGHT,
	     7, 1, 0),
SOC_DOUBLE_TLV("Speaker Boost Volume", WM8993_SPKOUT_BOOST, 3, 0, 7, 0,
	       spkboost_tlv),
SOC_ENUM("Speaker Reference", speaker_ref),
SOC_ENUM("Speaker Mode", speaker_mode),

SOC_DOUBLE_R_EXT_TLV("Headphone Volume",
		     WM8993_LEFT_OUTPUT_VOLUME, WM8993_RIGHT_OUTPUT_VOLUME,
		     0, 63, 0, snd_soc_get_volsw, wm8993_put_dc_servo,
		     outpga_tlv),

SOC_DOUBLE_R("Headphone Switch", WM8993_LEFT_OUTPUT_VOLUME,
	     WM8993_RIGHT_OUTPUT_VOLUME, 6, 1, 0),
SOC_DOUBLE_R("Headphone ZC Switch", WM8993_LEFT_OUTPUT_VOLUME,
	     WM8993_RIGHT_OUTPUT_VOLUME, 7, 1, 0),

SOC_SINGLE("LINEOUT1N Switch", WM8993_LINE_OUTPUTS_VOLUME, 6, 1, 1),
SOC_SINGLE("LINEOUT1P Switch", WM8993_LINE_OUTPUTS_VOLUME, 5, 1, 1),
SOC_SINGLE_TLV("LINEOUT1 Volume", WM8993_LINE_OUTPUTS_VOLUME, 4, 1, 1,
	       line_tlv),

SOC_SINGLE("LINEOUT2N Switch", WM8993_LINE_OUTPUTS_VOLUME, 2, 1, 1),
SOC_SINGLE("LINEOUT2P Switch", WM8993_LINE_OUTPUTS_VOLUME, 1, 1, 1),
SOC_SINGLE_TLV("LINEOUT2 Volume", WM8993_LINE_OUTPUTS_VOLUME, 0, 1, 1,
	       line_tlv),
पूर्ण;

अटल पूर्णांक hp_supply_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		चयन (hubs->hp_startup_mode) अणु
		हाल 0:
			अवरोध;
		हाल 1:
			/* Enable the headphone amp */
			snd_soc_component_update_bits(component, WM8993_POWER_MANAGEMENT_1,
					    WM8993_HPOUT1L_ENA |
					    WM8993_HPOUT1R_ENA,
					    WM8993_HPOUT1L_ENA |
					    WM8993_HPOUT1R_ENA);

			/* Enable the second stage */
			snd_soc_component_update_bits(component, WM8993_ANALOGUE_HP_0,
					    WM8993_HPOUT1L_DLY |
					    WM8993_HPOUT1R_DLY,
					    WM8993_HPOUT1L_DLY |
					    WM8993_HPOUT1R_DLY);
			अवरोध;
		शेष:
			dev_err(component->dev, "Unknown HP startup mode %d\n",
				hubs->hp_startup_mode);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, WM8993_CHARGE_PUMP_1,
				    WM8993_CP_ENA, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hp_event(काष्ठा snd_soc_dapm_widget *w,
		    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	अचिन्हित पूर्णांक reg = snd_soc_component_पढ़ो(component, WM8993_ANALOGUE_HP_0);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, WM8993_CHARGE_PUMP_1,
				    WM8993_CP_ENA, WM8993_CP_ENA);

		msleep(5);

		snd_soc_component_update_bits(component, WM8993_POWER_MANAGEMENT_1,
				    WM8993_HPOUT1L_ENA | WM8993_HPOUT1R_ENA,
				    WM8993_HPOUT1L_ENA | WM8993_HPOUT1R_ENA);

		reg |= WM8993_HPOUT1L_DLY | WM8993_HPOUT1R_DLY;
		snd_soc_component_ग_लिखो(component, WM8993_ANALOGUE_HP_0, reg);

		snd_soc_component_update_bits(component, WM8993_DC_SERVO_1,
				    WM8993_DCS_TIMER_PERIOD_01_MASK, 0);

		enable_dc_servo(component);

		reg |= WM8993_HPOUT1R_OUTP | WM8993_HPOUT1R_RMV_SHORT |
			WM8993_HPOUT1L_OUTP | WM8993_HPOUT1L_RMV_SHORT;
		snd_soc_component_ग_लिखो(component, WM8993_ANALOGUE_HP_0, reg);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, WM8993_ANALOGUE_HP_0,
				    WM8993_HPOUT1L_OUTP |
				    WM8993_HPOUT1R_OUTP |
				    WM8993_HPOUT1L_RMV_SHORT |
				    WM8993_HPOUT1R_RMV_SHORT, 0);

		snd_soc_component_update_bits(component, WM8993_ANALOGUE_HP_0,
				    WM8993_HPOUT1L_DLY |
				    WM8993_HPOUT1R_DLY, 0);

		snd_soc_component_ग_लिखो(component, WM8993_DC_SERVO_0, 0);

		snd_soc_component_update_bits(component, WM8993_POWER_MANAGEMENT_1,
				    WM8993_HPOUT1L_ENA | WM8993_HPOUT1R_ENA,
				    0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक earpiece_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *control, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 reg = snd_soc_component_पढ़ो(component, WM8993_ANTIPOP1) & ~WM8993_HPOUT2_IN_ENA;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		reg |= WM8993_HPOUT2_IN_ENA;
		snd_soc_component_ग_लिखो(component, WM8993_ANTIPOP1, reg);
		udelay(50);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_ग_लिखो(component, WM8993_ANTIPOP1, reg);
		अवरोध;

	शेष:
		WARN(1, "Invalid event %d\n", event);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lineout_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *control, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	bool *flag;

	चयन (w->shअगरt) अणु
	हाल WM8993_LINEOUT1N_ENA_SHIFT:
		flag = &hubs->lineout1n_ena;
		अवरोध;
	हाल WM8993_LINEOUT1P_ENA_SHIFT:
		flag = &hubs->lineout1p_ena;
		अवरोध;
	हाल WM8993_LINEOUT2N_ENA_SHIFT:
		flag = &hubs->lineout2n_ena;
		अवरोध;
	हाल WM8993_LINEOUT2P_ENA_SHIFT:
		flag = &hubs->lineout2p_ena;
		अवरोध;
	शेष:
		WARN(1, "Unknown line output");
		वापस -EINVAL;
	पूर्ण

	*flag = SND_SOC_DAPM_EVENT_ON(event);

	वापस 0;
पूर्ण

अटल पूर्णांक micbias_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);

	चयन (w->shअगरt) अणु
	हाल WM8993_MICB1_ENA_SHIFT:
		अगर (hubs->micb1_delay)
			msleep(hubs->micb1_delay);
		अवरोध;
	हाल WM8993_MICB2_ENA_SHIFT:
		अगर (hubs->micb2_delay)
			msleep(hubs->micb2_delay);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम wm_hubs_update_class_w(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	पूर्णांक enable = WM8993_CP_DYN_V | WM8993_CP_DYN_FREQ;

	अगर (!wm_hubs_dac_hp_direct(component))
		enable = false;

	अगर (hubs->check_class_w_digital && !hubs->check_class_w_digital(component))
		enable = false;

	dev_vdbg(component->dev, "Class W %s\n", enable ? "enabled" : "disabled");

	snd_soc_component_update_bits(component, WM8993_CLASS_W_0,
			    WM8993_CP_DYN_V | WM8993_CP_DYN_FREQ, enable);

	snd_soc_component_ग_लिखो(component, WM8993_LEFT_OUTPUT_VOLUME,
		      snd_soc_component_पढ़ो(component, WM8993_LEFT_OUTPUT_VOLUME));
	snd_soc_component_ग_लिखो(component, WM8993_RIGHT_OUTPUT_VOLUME,
		      snd_soc_component_पढ़ो(component, WM8993_RIGHT_OUTPUT_VOLUME));
पूर्ण
EXPORT_SYMBOL_GPL(wm_hubs_update_class_w);

#घोषणा WM_HUBS_SINGLE_W(xname, reg, shअगरt, max, invert) \
	SOC_SINGLE_EXT(xname, reg, shअगरt, max, invert, \
		snd_soc_dapm_get_volsw, class_w_put_volsw)

अटल पूर्णांक class_w_put_volsw(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	पूर्णांक ret;

	ret = snd_soc_dapm_put_volsw(kcontrol, ucontrol);

	wm_hubs_update_class_w(component);

	वापस ret;
पूर्ण

#घोषणा WM_HUBS_ENUM_W(xname, xक्रमागत) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_क्रमागत_द्विगुन, \
	.get = snd_soc_dapm_get_क्रमागत_द्विगुन, \
	.put = class_w_put_द्विगुन, \
	.निजी_value = (अचिन्हित दीर्घ)&xक्रमागत पूर्ण

अटल पूर्णांक class_w_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	पूर्णांक ret;

	ret = snd_soc_dapm_put_क्रमागत_द्विगुन(kcontrol, ucontrol);

	wm_hubs_update_class_w(component);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *hp_mux_text[] = अणु
	"Mixer",
	"DAC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(hpl_क्रमागत,
			    WM8993_OUTPUT_MIXER1, 8, hp_mux_text);

स्थिर काष्ठा snd_kcontrol_new wm_hubs_hpl_mux =
	WM_HUBS_ENUM_W("Left Headphone Mux", hpl_क्रमागत);
EXPORT_SYMBOL_GPL(wm_hubs_hpl_mux);

अटल SOC_ENUM_SINGLE_DECL(hpr_क्रमागत,
			    WM8993_OUTPUT_MIXER2, 8, hp_mux_text);

स्थिर काष्ठा snd_kcontrol_new wm_hubs_hpr_mux =
	WM_HUBS_ENUM_W("Right Headphone Mux", hpr_क्रमागत);
EXPORT_SYMBOL_GPL(wm_hubs_hpr_mux);

अटल स्थिर काष्ठा snd_kcontrol_new in1l_pga[] = अणु
SOC_DAPM_SINGLE("IN1LP Switch", WM8993_INPUT_MIXER2, 5, 1, 0),
SOC_DAPM_SINGLE("IN1LN Switch", WM8993_INPUT_MIXER2, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new in1r_pga[] = अणु
SOC_DAPM_SINGLE("IN1RP Switch", WM8993_INPUT_MIXER2, 1, 1, 0),
SOC_DAPM_SINGLE("IN1RN Switch", WM8993_INPUT_MIXER2, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new in2l_pga[] = अणु
SOC_DAPM_SINGLE("IN2LP Switch", WM8993_INPUT_MIXER2, 7, 1, 0),
SOC_DAPM_SINGLE("IN2LN Switch", WM8993_INPUT_MIXER2, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new in2r_pga[] = अणु
SOC_DAPM_SINGLE("IN2RP Switch", WM8993_INPUT_MIXER2, 3, 1, 0),
SOC_DAPM_SINGLE("IN2RN Switch", WM8993_INPUT_MIXER2, 2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mixinl[] = अणु
SOC_DAPM_SINGLE("IN2L Switch", WM8993_INPUT_MIXER3, 8, 1, 0),
SOC_DAPM_SINGLE("IN1L Switch", WM8993_INPUT_MIXER3, 5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mixinr[] = अणु
SOC_DAPM_SINGLE("IN2R Switch", WM8993_INPUT_MIXER4, 8, 1, 0),
SOC_DAPM_SINGLE("IN1R Switch", WM8993_INPUT_MIXER4, 5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new left_output_mixer[] = अणु
WM_HUBS_SINGLE_W("Right Input Switch", WM8993_OUTPUT_MIXER1, 7, 1, 0),
WM_HUBS_SINGLE_W("Left Input Switch", WM8993_OUTPUT_MIXER1, 6, 1, 0),
WM_HUBS_SINGLE_W("IN2RN Switch", WM8993_OUTPUT_MIXER1, 5, 1, 0),
WM_HUBS_SINGLE_W("IN2LN Switch", WM8993_OUTPUT_MIXER1, 4, 1, 0),
WM_HUBS_SINGLE_W("IN2LP Switch", WM8993_OUTPUT_MIXER1, 1, 1, 0),
WM_HUBS_SINGLE_W("IN1R Switch", WM8993_OUTPUT_MIXER1, 3, 1, 0),
WM_HUBS_SINGLE_W("IN1L Switch", WM8993_OUTPUT_MIXER1, 2, 1, 0),
WM_HUBS_SINGLE_W("DAC Switch", WM8993_OUTPUT_MIXER1, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new right_output_mixer[] = अणु
WM_HUBS_SINGLE_W("Left Input Switch", WM8993_OUTPUT_MIXER2, 7, 1, 0),
WM_HUBS_SINGLE_W("Right Input Switch", WM8993_OUTPUT_MIXER2, 6, 1, 0),
WM_HUBS_SINGLE_W("IN2LN Switch", WM8993_OUTPUT_MIXER2, 5, 1, 0),
WM_HUBS_SINGLE_W("IN2RN Switch", WM8993_OUTPUT_MIXER2, 4, 1, 0),
WM_HUBS_SINGLE_W("IN1L Switch", WM8993_OUTPUT_MIXER2, 3, 1, 0),
WM_HUBS_SINGLE_W("IN1R Switch", WM8993_OUTPUT_MIXER2, 2, 1, 0),
WM_HUBS_SINGLE_W("IN2RP Switch", WM8993_OUTPUT_MIXER2, 1, 1, 0),
WM_HUBS_SINGLE_W("DAC Switch", WM8993_OUTPUT_MIXER2, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new earpiece_mixer[] = अणु
SOC_DAPM_SINGLE("Direct Voice Switch", WM8993_HPOUT2_MIXER, 5, 1, 0),
SOC_DAPM_SINGLE("Left Output Switch", WM8993_HPOUT2_MIXER, 4, 1, 0),
SOC_DAPM_SINGLE("Right Output Switch", WM8993_HPOUT2_MIXER, 3, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new left_speaker_boost[] = अणु
SOC_DAPM_SINGLE("Direct Voice Switch", WM8993_SPKOUT_MIXERS, 5, 1, 0),
SOC_DAPM_SINGLE("SPKL Switch", WM8993_SPKOUT_MIXERS, 4, 1, 0),
SOC_DAPM_SINGLE("SPKR Switch", WM8993_SPKOUT_MIXERS, 3, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new right_speaker_boost[] = अणु
SOC_DAPM_SINGLE("Direct Voice Switch", WM8993_SPKOUT_MIXERS, 2, 1, 0),
SOC_DAPM_SINGLE("SPKL Switch", WM8993_SPKOUT_MIXERS, 1, 1, 0),
SOC_DAPM_SINGLE("SPKR Switch", WM8993_SPKOUT_MIXERS, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new line1_mix[] = अणु
SOC_DAPM_SINGLE("IN1R Switch", WM8993_LINE_MIXER1, 2, 1, 0),
SOC_DAPM_SINGLE("IN1L Switch", WM8993_LINE_MIXER1, 1, 1, 0),
SOC_DAPM_SINGLE("Output Switch", WM8993_LINE_MIXER1, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new line1n_mix[] = अणु
SOC_DAPM_SINGLE("Left Output Switch", WM8993_LINE_MIXER1, 6, 1, 0),
SOC_DAPM_SINGLE("Right Output Switch", WM8993_LINE_MIXER1, 5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new line1p_mix[] = अणु
SOC_DAPM_SINGLE("Left Output Switch", WM8993_LINE_MIXER1, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new line2_mix[] = अणु
SOC_DAPM_SINGLE("IN1L Switch", WM8993_LINE_MIXER2, 2, 1, 0),
SOC_DAPM_SINGLE("IN1R Switch", WM8993_LINE_MIXER2, 1, 1, 0),
SOC_DAPM_SINGLE("Output Switch", WM8993_LINE_MIXER2, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new line2n_mix[] = अणु
SOC_DAPM_SINGLE("Left Output Switch", WM8993_LINE_MIXER2, 5, 1, 0),
SOC_DAPM_SINGLE("Right Output Switch", WM8993_LINE_MIXER2, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new line2p_mix[] = अणु
SOC_DAPM_SINGLE("Right Output Switch", WM8993_LINE_MIXER2, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget analogue_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("IN1LN"),
SND_SOC_DAPM_INPUT("IN1LP"),
SND_SOC_DAPM_INPUT("IN2LN"),
SND_SOC_DAPM_INPUT("IN2LP:VXRN"),
SND_SOC_DAPM_INPUT("IN1RN"),
SND_SOC_DAPM_INPUT("IN1RP"),
SND_SOC_DAPM_INPUT("IN2RN"),
SND_SOC_DAPM_INPUT("IN2RP:VXRP"),

SND_SOC_DAPM_SUPPLY("MICBIAS2", WM8993_POWER_MANAGEMENT_1, 5, 0,
		    micbias_event, SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_SUPPLY("MICBIAS1", WM8993_POWER_MANAGEMENT_1, 4, 0,
		    micbias_event, SND_SOC_DAPM_POST_PMU),

SND_SOC_DAPM_MIXER("IN1L PGA", WM8993_POWER_MANAGEMENT_2, 6, 0,
		   in1l_pga, ARRAY_SIZE(in1l_pga)),
SND_SOC_DAPM_MIXER("IN1R PGA", WM8993_POWER_MANAGEMENT_2, 4, 0,
		   in1r_pga, ARRAY_SIZE(in1r_pga)),

SND_SOC_DAPM_MIXER("IN2L PGA", WM8993_POWER_MANAGEMENT_2, 7, 0,
		   in2l_pga, ARRAY_SIZE(in2l_pga)),
SND_SOC_DAPM_MIXER("IN2R PGA", WM8993_POWER_MANAGEMENT_2, 5, 0,
		   in2r_pga, ARRAY_SIZE(in2r_pga)),

SND_SOC_DAPM_MIXER("MIXINL", WM8993_POWER_MANAGEMENT_2, 9, 0,
		   mixinl, ARRAY_SIZE(mixinl)),
SND_SOC_DAPM_MIXER("MIXINR", WM8993_POWER_MANAGEMENT_2, 8, 0,
		   mixinr, ARRAY_SIZE(mixinr)),

SND_SOC_DAPM_MIXER("Left Output Mixer", WM8993_POWER_MANAGEMENT_3, 5, 0,
		   left_output_mixer, ARRAY_SIZE(left_output_mixer)),
SND_SOC_DAPM_MIXER("Right Output Mixer", WM8993_POWER_MANAGEMENT_3, 4, 0,
		   right_output_mixer, ARRAY_SIZE(right_output_mixer)),

SND_SOC_DAPM_PGA("Left Output PGA", WM8993_POWER_MANAGEMENT_3, 7, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Right Output PGA", WM8993_POWER_MANAGEMENT_3, 6, 0, शून्य, 0),

SND_SOC_DAPM_SUPPLY("Headphone Supply", SND_SOC_NOPM, 0, 0, hp_supply_event, 
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),
SND_SOC_DAPM_OUT_DRV_E("Headphone PGA", SND_SOC_NOPM, 0, 0, शून्य, 0,
		       hp_event, SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

SND_SOC_DAPM_MIXER("Earpiece Mixer", SND_SOC_NOPM, 0, 0,
		   earpiece_mixer, ARRAY_SIZE(earpiece_mixer)),
SND_SOC_DAPM_PGA_E("Earpiece Driver", WM8993_POWER_MANAGEMENT_1, 11, 0,
		   शून्य, 0, earpiece_event,
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

SND_SOC_DAPM_MIXER("SPKL Boost", SND_SOC_NOPM, 0, 0,
		   left_speaker_boost, ARRAY_SIZE(left_speaker_boost)),
SND_SOC_DAPM_MIXER("SPKR Boost", SND_SOC_NOPM, 0, 0,
		   right_speaker_boost, ARRAY_SIZE(right_speaker_boost)),

SND_SOC_DAPM_SUPPLY("TSHUT", WM8993_POWER_MANAGEMENT_2, 14, 0, शून्य, 0),
SND_SOC_DAPM_OUT_DRV("SPKL Driver", WM8993_POWER_MANAGEMENT_1, 12, 0,
		     शून्य, 0),
SND_SOC_DAPM_OUT_DRV("SPKR Driver", WM8993_POWER_MANAGEMENT_1, 13, 0,
		     शून्य, 0),

SND_SOC_DAPM_MIXER("LINEOUT1 Mixer", SND_SOC_NOPM, 0, 0,
		   line1_mix, ARRAY_SIZE(line1_mix)),
SND_SOC_DAPM_MIXER("LINEOUT2 Mixer", SND_SOC_NOPM, 0, 0,
		   line2_mix, ARRAY_SIZE(line2_mix)),

SND_SOC_DAPM_MIXER("LINEOUT1N Mixer", SND_SOC_NOPM, 0, 0,
		   line1n_mix, ARRAY_SIZE(line1n_mix)),
SND_SOC_DAPM_MIXER("LINEOUT1P Mixer", SND_SOC_NOPM, 0, 0,
		   line1p_mix, ARRAY_SIZE(line1p_mix)),
SND_SOC_DAPM_MIXER("LINEOUT2N Mixer", SND_SOC_NOPM, 0, 0,
		   line2n_mix, ARRAY_SIZE(line2n_mix)),
SND_SOC_DAPM_MIXER("LINEOUT2P Mixer", SND_SOC_NOPM, 0, 0,
		   line2p_mix, ARRAY_SIZE(line2p_mix)),

SND_SOC_DAPM_OUT_DRV_E("LINEOUT1N Driver", WM8993_POWER_MANAGEMENT_3, 13, 0,
		       शून्य, 0, lineout_event,
		     SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
SND_SOC_DAPM_OUT_DRV_E("LINEOUT1P Driver", WM8993_POWER_MANAGEMENT_3, 12, 0,
		       शून्य, 0, lineout_event,
		       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
SND_SOC_DAPM_OUT_DRV_E("LINEOUT2N Driver", WM8993_POWER_MANAGEMENT_3, 11, 0,
		       शून्य, 0, lineout_event,
		       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
SND_SOC_DAPM_OUT_DRV_E("LINEOUT2P Driver", WM8993_POWER_MANAGEMENT_3, 10, 0,
		       शून्य, 0, lineout_event,
		       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

SND_SOC_DAPM_OUTPUT("SPKOUTLP"),
SND_SOC_DAPM_OUTPUT("SPKOUTLN"),
SND_SOC_DAPM_OUTPUT("SPKOUTRP"),
SND_SOC_DAPM_OUTPUT("SPKOUTRN"),
SND_SOC_DAPM_OUTPUT("HPOUT1L"),
SND_SOC_DAPM_OUTPUT("HPOUT1R"),
SND_SOC_DAPM_OUTPUT("HPOUT2P"),
SND_SOC_DAPM_OUTPUT("HPOUT2N"),
SND_SOC_DAPM_OUTPUT("LINEOUT1P"),
SND_SOC_DAPM_OUTPUT("LINEOUT1N"),
SND_SOC_DAPM_OUTPUT("LINEOUT2P"),
SND_SOC_DAPM_OUTPUT("LINEOUT2N"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route analogue_routes[] = अणु
	अणु "MICBIAS1", शून्य, "CLK_SYS" पूर्ण,
	अणु "MICBIAS2", शून्य, "CLK_SYS" पूर्ण,

	अणु "IN1L PGA", "IN1LP Switch", "IN1LP" पूर्ण,
	अणु "IN1L PGA", "IN1LN Switch", "IN1LN" पूर्ण,

	अणु "IN1L PGA", शून्य, "VMID" पूर्ण,
	अणु "IN1R PGA", शून्य, "VMID" पूर्ण,
	अणु "IN2L PGA", शून्य, "VMID" पूर्ण,
	अणु "IN2R PGA", शून्य, "VMID" पूर्ण,

	अणु "IN1R PGA", "IN1RP Switch", "IN1RP" पूर्ण,
	अणु "IN1R PGA", "IN1RN Switch", "IN1RN" पूर्ण,

	अणु "IN2L PGA", "IN2LP Switch", "IN2LP:VXRN" पूर्ण,
	अणु "IN2L PGA", "IN2LN Switch", "IN2LN" पूर्ण,

	अणु "IN2R PGA", "IN2RP Switch", "IN2RP:VXRP" पूर्ण,
	अणु "IN2R PGA", "IN2RN Switch", "IN2RN" पूर्ण,

	अणु "Direct Voice", शून्य, "IN2LP:VXRN" पूर्ण,
	अणु "Direct Voice", शून्य, "IN2RP:VXRP" पूर्ण,

	अणु "MIXINL", "IN1L Switch", "IN1L PGA" पूर्ण,
	अणु "MIXINL", "IN2L Switch", "IN2L PGA" पूर्ण,
	अणु "MIXINL", शून्य, "Direct Voice" पूर्ण,
	अणु "MIXINL", शून्य, "IN1LP" पूर्ण,
	अणु "MIXINL", शून्य, "Left Output Mixer" पूर्ण,
	अणु "MIXINL", शून्य, "VMID" पूर्ण,

	अणु "MIXINR", "IN1R Switch", "IN1R PGA" पूर्ण,
	अणु "MIXINR", "IN2R Switch", "IN2R PGA" पूर्ण,
	अणु "MIXINR", शून्य, "Direct Voice" पूर्ण,
	अणु "MIXINR", शून्य, "IN1RP" पूर्ण,
	अणु "MIXINR", शून्य, "Right Output Mixer" पूर्ण,
	अणु "MIXINR", शून्य, "VMID" पूर्ण,

	अणु "ADCL", शून्य, "MIXINL" पूर्ण,
	अणु "ADCR", शून्य, "MIXINR" पूर्ण,

	अणु "Left Output Mixer", "Left Input Switch", "MIXINL" पूर्ण,
	अणु "Left Output Mixer", "Right Input Switch", "MIXINR" पूर्ण,
	अणु "Left Output Mixer", "IN2RN Switch", "IN2RN" पूर्ण,
	अणु "Left Output Mixer", "IN2LN Switch", "IN2LN" पूर्ण,
	अणु "Left Output Mixer", "IN2LP Switch", "IN2LP:VXRN" पूर्ण,
	अणु "Left Output Mixer", "IN1L Switch", "IN1L PGA" पूर्ण,
	अणु "Left Output Mixer", "IN1R Switch", "IN1R PGA" पूर्ण,

	अणु "Right Output Mixer", "Left Input Switch", "MIXINL" पूर्ण,
	अणु "Right Output Mixer", "Right Input Switch", "MIXINR" पूर्ण,
	अणु "Right Output Mixer", "IN2LN Switch", "IN2LN" पूर्ण,
	अणु "Right Output Mixer", "IN2RN Switch", "IN2RN" पूर्ण,
	अणु "Right Output Mixer", "IN2RP Switch", "IN2RP:VXRP" पूर्ण,
	अणु "Right Output Mixer", "IN1L Switch", "IN1L PGA" पूर्ण,
	अणु "Right Output Mixer", "IN1R Switch", "IN1R PGA" पूर्ण,

	अणु "Left Output PGA", शून्य, "Left Output Mixer" पूर्ण,
	अणु "Left Output PGA", शून्य, "TOCLK" पूर्ण,

	अणु "Right Output PGA", शून्य, "Right Output Mixer" पूर्ण,
	अणु "Right Output PGA", शून्य, "TOCLK" पूर्ण,

	अणु "Earpiece Mixer", "Direct Voice Switch", "Direct Voice" पूर्ण,
	अणु "Earpiece Mixer", "Left Output Switch", "Left Output PGA" पूर्ण,
	अणु "Earpiece Mixer", "Right Output Switch", "Right Output PGA" पूर्ण,

	अणु "Earpiece Driver", शून्य, "VMID" पूर्ण,
	अणु "Earpiece Driver", शून्य, "Earpiece Mixer" पूर्ण,
	अणु "HPOUT2N", शून्य, "Earpiece Driver" पूर्ण,
	अणु "HPOUT2P", शून्य, "Earpiece Driver" पूर्ण,

	अणु "SPKL", "Input Switch", "MIXINL" पूर्ण,
	अणु "SPKL", "IN1LP Switch", "IN1LP" पूर्ण,
	अणु "SPKL", "Output Switch", "Left Output PGA" पूर्ण,
	अणु "SPKL", शून्य, "TOCLK" पूर्ण,

	अणु "SPKR", "Input Switch", "MIXINR" पूर्ण,
	अणु "SPKR", "IN1RP Switch", "IN1RP" पूर्ण,
	अणु "SPKR", "Output Switch", "Right Output PGA" पूर्ण,
	अणु "SPKR", शून्य, "TOCLK" पूर्ण,

	अणु "SPKL Boost", "Direct Voice Switch", "Direct Voice" पूर्ण,
	अणु "SPKL Boost", "SPKL Switch", "SPKL" पूर्ण,
	अणु "SPKL Boost", "SPKR Switch", "SPKR" पूर्ण,

	अणु "SPKR Boost", "Direct Voice Switch", "Direct Voice" पूर्ण,
	अणु "SPKR Boost", "SPKR Switch", "SPKR" पूर्ण,
	अणु "SPKR Boost", "SPKL Switch", "SPKL" पूर्ण,

	अणु "SPKL Driver", शून्य, "VMID" पूर्ण,
	अणु "SPKL Driver", शून्य, "SPKL Boost" पूर्ण,
	अणु "SPKL Driver", शून्य, "CLK_SYS" पूर्ण,
	अणु "SPKL Driver", शून्य, "TSHUT" पूर्ण,

	अणु "SPKR Driver", शून्य, "VMID" पूर्ण,
	अणु "SPKR Driver", शून्य, "SPKR Boost" पूर्ण,
	अणु "SPKR Driver", शून्य, "CLK_SYS" पूर्ण,
	अणु "SPKR Driver", शून्य, "TSHUT" पूर्ण,

	अणु "SPKOUTLP", शून्य, "SPKL Driver" पूर्ण,
	अणु "SPKOUTLN", शून्य, "SPKL Driver" पूर्ण,
	अणु "SPKOUTRP", शून्य, "SPKR Driver" पूर्ण,
	अणु "SPKOUTRN", शून्य, "SPKR Driver" पूर्ण,

	अणु "Left Headphone Mux", "Mixer", "Left Output PGA" पूर्ण,
	अणु "Right Headphone Mux", "Mixer", "Right Output PGA" पूर्ण,

	अणु "Headphone PGA", शून्य, "Left Headphone Mux" पूर्ण,
	अणु "Headphone PGA", शून्य, "Right Headphone Mux" पूर्ण,
	अणु "Headphone PGA", शून्य, "VMID" पूर्ण,
	अणु "Headphone PGA", शून्य, "CLK_SYS" पूर्ण,
	अणु "Headphone PGA", शून्य, "Headphone Supply" पूर्ण,

	अणु "HPOUT1L", शून्य, "Headphone PGA" पूर्ण,
	अणु "HPOUT1R", शून्य, "Headphone PGA" पूर्ण,

	अणु "LINEOUT1N Driver", शून्य, "VMID" पूर्ण,
	अणु "LINEOUT1P Driver", शून्य, "VMID" पूर्ण,
	अणु "LINEOUT2N Driver", शून्य, "VMID" पूर्ण,
	अणु "LINEOUT2P Driver", शून्य, "VMID" पूर्ण,

	अणु "LINEOUT1N", शून्य, "LINEOUT1N Driver" पूर्ण,
	अणु "LINEOUT1P", शून्य, "LINEOUT1P Driver" पूर्ण,
	अणु "LINEOUT2N", शून्य, "LINEOUT2N Driver" पूर्ण,
	अणु "LINEOUT2P", शून्य, "LINEOUT2P Driver" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route lineout1_dअगरf_routes[] = अणु
	अणु "LINEOUT1 Mixer", "IN1L Switch", "IN1L PGA" पूर्ण,
	अणु "LINEOUT1 Mixer", "IN1R Switch", "IN1R PGA" पूर्ण,
	अणु "LINEOUT1 Mixer", "Output Switch", "Left Output PGA" पूर्ण,

	अणु "LINEOUT1N Driver", शून्य, "LINEOUT1 Mixer" पूर्ण,
	अणु "LINEOUT1P Driver", शून्य, "LINEOUT1 Mixer" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route lineout1_se_routes[] = अणु
	अणु "LINEOUT1N Mixer", "Left Output Switch", "Left Output PGA" पूर्ण,
	अणु "LINEOUT1N Mixer", "Right Output Switch", "Right Output PGA" पूर्ण,

	अणु "LINEOUT1P Mixer", "Left Output Switch", "Left Output PGA" पूर्ण,

	अणु "LINEOUT1N Driver", शून्य, "LINEOUT1N Mixer" पूर्ण,
	अणु "LINEOUT1P Driver", शून्य, "LINEOUT1P Mixer" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route lineout2_dअगरf_routes[] = अणु
	अणु "LINEOUT2 Mixer", "IN1L Switch", "IN1L PGA" पूर्ण,
	अणु "LINEOUT2 Mixer", "IN1R Switch", "IN1R PGA" पूर्ण,
	अणु "LINEOUT2 Mixer", "Output Switch", "Right Output PGA" पूर्ण,

	अणु "LINEOUT2N Driver", शून्य, "LINEOUT2 Mixer" पूर्ण,
	अणु "LINEOUT2P Driver", शून्य, "LINEOUT2 Mixer" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route lineout2_se_routes[] = अणु
	अणु "LINEOUT2N Mixer", "Left Output Switch", "Left Output PGA" पूर्ण,
	अणु "LINEOUT2N Mixer", "Right Output Switch", "Right Output PGA" पूर्ण,

	अणु "LINEOUT2P Mixer", "Right Output Switch", "Right Output PGA" पूर्ण,

	अणु "LINEOUT2N Driver", शून्य, "LINEOUT2N Mixer" पूर्ण,
	अणु "LINEOUT2P Driver", शून्य, "LINEOUT2P Mixer" पूर्ण,
पूर्ण;

पूर्णांक wm_hubs_add_analogue_controls(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	/* Latch volume update bits & शेष ZC on */
	snd_soc_component_update_bits(component, WM8993_LEFT_LINE_INPUT_1_2_VOLUME,
			    WM8993_IN1_VU, WM8993_IN1_VU);
	snd_soc_component_update_bits(component, WM8993_RIGHT_LINE_INPUT_1_2_VOLUME,
			    WM8993_IN1_VU, WM8993_IN1_VU);
	snd_soc_component_update_bits(component, WM8993_LEFT_LINE_INPUT_3_4_VOLUME,
			    WM8993_IN2_VU, WM8993_IN2_VU);
	snd_soc_component_update_bits(component, WM8993_RIGHT_LINE_INPUT_3_4_VOLUME,
			    WM8993_IN2_VU, WM8993_IN2_VU);

	snd_soc_component_update_bits(component, WM8993_SPEAKER_VOLUME_LEFT,
			    WM8993_SPKOUT_VU, WM8993_SPKOUT_VU);
	snd_soc_component_update_bits(component, WM8993_SPEAKER_VOLUME_RIGHT,
			    WM8993_SPKOUT_VU, WM8993_SPKOUT_VU);

	snd_soc_component_update_bits(component, WM8993_LEFT_OUTPUT_VOLUME,
			    WM8993_HPOUT1_VU | WM8993_HPOUT1L_ZC,
			    WM8993_HPOUT1_VU | WM8993_HPOUT1L_ZC);
	snd_soc_component_update_bits(component, WM8993_RIGHT_OUTPUT_VOLUME,
			    WM8993_HPOUT1_VU | WM8993_HPOUT1R_ZC,
			    WM8993_HPOUT1_VU | WM8993_HPOUT1R_ZC);

	snd_soc_component_update_bits(component, WM8993_LEFT_OPGA_VOLUME,
			    WM8993_MIXOUTL_ZC | WM8993_MIXOUT_VU,
			    WM8993_MIXOUTL_ZC | WM8993_MIXOUT_VU);
	snd_soc_component_update_bits(component, WM8993_RIGHT_OPGA_VOLUME,
			    WM8993_MIXOUTR_ZC | WM8993_MIXOUT_VU,
			    WM8993_MIXOUTR_ZC | WM8993_MIXOUT_VU);

	snd_soc_add_component_controls(component, analogue_snd_controls,
			     ARRAY_SIZE(analogue_snd_controls));

	snd_soc_dapm_new_controls(dapm, analogue_dapm_widमाला_लो,
				  ARRAY_SIZE(analogue_dapm_widमाला_लो));
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_hubs_add_analogue_controls);

पूर्णांक wm_hubs_add_analogue_routes(काष्ठा snd_soc_component *component,
				पूर्णांक lineout1_dअगरf, पूर्णांक lineout2_dअगरf)
अणु
	काष्ठा wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	hubs->component = component;

	INIT_LIST_HEAD(&hubs->dcs_cache);
	init_completion(&hubs->dcs_करोne);

	snd_soc_dapm_add_routes(dapm, analogue_routes,
				ARRAY_SIZE(analogue_routes));

	अगर (lineout1_dअगरf)
		snd_soc_dapm_add_routes(dapm,
					lineout1_dअगरf_routes,
					ARRAY_SIZE(lineout1_dअगरf_routes));
	अन्यथा
		snd_soc_dapm_add_routes(dapm,
					lineout1_se_routes,
					ARRAY_SIZE(lineout1_se_routes));

	अगर (lineout2_dअगरf)
		snd_soc_dapm_add_routes(dapm,
					lineout2_dअगरf_routes,
					ARRAY_SIZE(lineout2_dअगरf_routes));
	अन्यथा
		snd_soc_dapm_add_routes(dapm,
					lineout2_se_routes,
					ARRAY_SIZE(lineout2_se_routes));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_hubs_add_analogue_routes);

पूर्णांक wm_hubs_handle_analogue_pdata(काष्ठा snd_soc_component *component,
				  पूर्णांक lineout1_dअगरf, पूर्णांक lineout2_dअगरf,
				  पूर्णांक lineout1fb, पूर्णांक lineout2fb,
				  पूर्णांक jd_scthr, पूर्णांक jd_thr,
				  पूर्णांक micbias1_delay, पूर्णांक micbias2_delay,
				  पूर्णांक micbias1_lvl, पूर्णांक micbias2_lvl)
अणु
	काष्ठा wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);

	hubs->lineout1_se = !lineout1_dअगरf;
	hubs->lineout2_se = !lineout2_dअगरf;
	hubs->micb1_delay = micbias1_delay;
	hubs->micb2_delay = micbias2_delay;

	अगर (!lineout1_dअगरf)
		snd_soc_component_update_bits(component, WM8993_LINE_MIXER1,
				    WM8993_LINEOUT1_MODE,
				    WM8993_LINEOUT1_MODE);
	अगर (!lineout2_dअगरf)
		snd_soc_component_update_bits(component, WM8993_LINE_MIXER2,
				    WM8993_LINEOUT2_MODE,
				    WM8993_LINEOUT2_MODE);

	अगर (!lineout1_dअगरf && !lineout2_dअगरf)
		snd_soc_component_update_bits(component, WM8993_ANTIPOP1,
				    WM8993_LINEOUT_VMID_BUF_ENA,
				    WM8993_LINEOUT_VMID_BUF_ENA);

	अगर (lineout1fb)
		snd_soc_component_update_bits(component, WM8993_ADDITIONAL_CONTROL,
				    WM8993_LINEOUT1_FB, WM8993_LINEOUT1_FB);

	अगर (lineout2fb)
		snd_soc_component_update_bits(component, WM8993_ADDITIONAL_CONTROL,
				    WM8993_LINEOUT2_FB, WM8993_LINEOUT2_FB);

	अगर (!hubs->micd_scthr)
		वापस 0;

	snd_soc_component_update_bits(component, WM8993_MICBIAS,
			    WM8993_JD_SCTHR_MASK | WM8993_JD_THR_MASK |
			    WM8993_MICB1_LVL | WM8993_MICB2_LVL,
			    jd_scthr << WM8993_JD_SCTHR_SHIFT |
			    jd_thr << WM8993_JD_THR_SHIFT |
			    micbias1_lvl |
			    micbias2_lvl << WM8993_MICB2_LVL_SHIFT);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm_hubs_handle_analogue_pdata);

व्योम wm_hubs_vmid_ena(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	पूर्णांक val = 0;

	अगर (hubs->lineout1_se)
		val |= WM8993_LINEOUT1N_ENA | WM8993_LINEOUT1P_ENA;

	अगर (hubs->lineout2_se)
		val |= WM8993_LINEOUT2N_ENA | WM8993_LINEOUT2P_ENA;

	/* Enable the line outमाला_दो जबतक we घातer up */
	snd_soc_component_update_bits(component, WM8993_POWER_MANAGEMENT_3, val, val);
पूर्ण
EXPORT_SYMBOL_GPL(wm_hubs_vmid_ena);

व्योम wm_hubs_set_bias_level(काष्ठा snd_soc_component *component,
			    क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	पूर्णांक mask, val;

	चयन (level) अणु
	हाल SND_SOC_BIAS_STANDBY:
		/* Clamp the inमाला_दो to VMID जबतक we ramp to अक्षरge caps */
		snd_soc_component_update_bits(component, WM8993_INPUTS_CLAMP_REG,
				    WM8993_INPUTS_CLAMP, WM8993_INPUTS_CLAMP);
		अवरोध;

	हाल SND_SOC_BIAS_ON:
		/* Turn off any unneeded single ended outमाला_दो */
		val = 0;
		mask = 0;

		अगर (hubs->lineout1_se)
			mask |= WM8993_LINEOUT1N_ENA | WM8993_LINEOUT1P_ENA;

		अगर (hubs->lineout2_se)
			mask |= WM8993_LINEOUT2N_ENA | WM8993_LINEOUT2P_ENA;

		अगर (hubs->lineout1_se && hubs->lineout1n_ena)
			val |= WM8993_LINEOUT1N_ENA;

		अगर (hubs->lineout1_se && hubs->lineout1p_ena)
			val |= WM8993_LINEOUT1P_ENA;

		अगर (hubs->lineout2_se && hubs->lineout2n_ena)
			val |= WM8993_LINEOUT2N_ENA;

		अगर (hubs->lineout2_se && hubs->lineout2p_ena)
			val |= WM8993_LINEOUT2P_ENA;

		snd_soc_component_update_bits(component, WM8993_POWER_MANAGEMENT_3,
				    mask, val);

		/* Remove the input clamps */
		snd_soc_component_update_bits(component, WM8993_INPUTS_CLAMP_REG,
				    WM8993_INPUTS_CLAMP, 0);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(wm_hubs_set_bias_level);

MODULE_DESCRIPTION("Shared support for Wolfson hubs products");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
