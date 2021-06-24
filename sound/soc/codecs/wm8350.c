<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8350.c -- WM8350 ALSA SoC audio driver
 *
 * Copyright (C) 2007-12 Wolfson Microelectronics PLC.
 *
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/wm8350/audपन.स>
#समावेश <linux/mfd/wm8350/core.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <trace/events/asoc.h>

#समावेश "wm8350.h"

#घोषणा WM8350_OUTn_0dB 0x39

#घोषणा WM8350_RAMP_NONE	0
#घोषणा WM8350_RAMP_UP		1
#घोषणा WM8350_RAMP_DOWN	2

/* We only include the analogue supplies here; the digital supplies
 * need to be available well beक्रमe this driver can be probed.
 */
अटल स्थिर अक्षर *supply_names[] = अणु
	"AVDD",
	"HPVDD",
पूर्ण;

काष्ठा wm8350_output अणु
	u16 active;
	u16 left_vol;
	u16 right_vol;
	u16 ramp;
	u16 mute;
पूर्ण;

काष्ठा wm8350_jack_data अणु
	काष्ठा snd_soc_jack *jack;
	काष्ठा delayed_work work;
	पूर्णांक report;
	पूर्णांक लघु_report;
पूर्ण;

काष्ठा wm8350_data अणु
	काष्ठा wm8350 *wm8350;
	काष्ठा wm8350_output out1;
	काष्ठा wm8350_output out2;
	काष्ठा wm8350_jack_data hpl;
	काष्ठा wm8350_jack_data hpr;
	काष्ठा wm8350_jack_data mic;
	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(supply_names)];
	पूर्णांक fll_freq_out;
	पूर्णांक fll_freq_in;
	काष्ठा delayed_work pga_work;
पूर्ण;

/*
 * Ramp OUT1 PGA volume to minimise pops at stream startup and shutकरोwn.
 */
अटल अंतरभूत पूर्णांक wm8350_out1_ramp_step(काष्ठा wm8350_data *wm8350_data)
अणु
	काष्ठा wm8350_output *out1 = &wm8350_data->out1;
	काष्ठा wm8350 *wm8350 = wm8350_data->wm8350;
	पूर्णांक left_complete = 0, right_complete = 0;
	u16 reg, val;

	/* left channel */
	reg = wm8350_reg_पढ़ो(wm8350, WM8350_LOUT1_VOLUME);
	val = (reg & WM8350_OUT1L_VOL_MASK) >> WM8350_OUT1L_VOL_SHIFT;

	अगर (out1->ramp == WM8350_RAMP_UP) अणु
		/* ramp step up */
		अगर (val < out1->left_vol) अणु
			val++;
			reg &= ~WM8350_OUT1L_VOL_MASK;
			wm8350_reg_ग_लिखो(wm8350, WM8350_LOUT1_VOLUME,
					 reg | (val << WM8350_OUT1L_VOL_SHIFT));
		पूर्ण अन्यथा
			left_complete = 1;
	पूर्ण अन्यथा अगर (out1->ramp == WM8350_RAMP_DOWN) अणु
		/* ramp step करोwn */
		अगर (val > 0) अणु
			val--;
			reg &= ~WM8350_OUT1L_VOL_MASK;
			wm8350_reg_ग_लिखो(wm8350, WM8350_LOUT1_VOLUME,
					 reg | (val << WM8350_OUT1L_VOL_SHIFT));
		पूर्ण अन्यथा
			left_complete = 1;
	पूर्ण अन्यथा
		वापस 1;

	/* right channel */
	reg = wm8350_reg_पढ़ो(wm8350, WM8350_ROUT1_VOLUME);
	val = (reg & WM8350_OUT1R_VOL_MASK) >> WM8350_OUT1R_VOL_SHIFT;
	अगर (out1->ramp == WM8350_RAMP_UP) अणु
		/* ramp step up */
		अगर (val < out1->right_vol) अणु
			val++;
			reg &= ~WM8350_OUT1R_VOL_MASK;
			wm8350_reg_ग_लिखो(wm8350, WM8350_ROUT1_VOLUME,
					 reg | (val << WM8350_OUT1R_VOL_SHIFT));
		पूर्ण अन्यथा
			right_complete = 1;
	पूर्ण अन्यथा अगर (out1->ramp == WM8350_RAMP_DOWN) अणु
		/* ramp step करोwn */
		अगर (val > 0) अणु
			val--;
			reg &= ~WM8350_OUT1R_VOL_MASK;
			wm8350_reg_ग_लिखो(wm8350, WM8350_ROUT1_VOLUME,
					 reg | (val << WM8350_OUT1R_VOL_SHIFT));
		पूर्ण अन्यथा
			right_complete = 1;
	पूर्ण

	/* only hit the update bit अगर either volume has changed this step */
	अगर (!left_complete || !right_complete)
		wm8350_set_bits(wm8350, WM8350_LOUT1_VOLUME, WM8350_OUT1_VU);

	वापस left_complete & right_complete;
पूर्ण

/*
 * Ramp OUT2 PGA volume to minimise pops at stream startup and shutकरोwn.
 */
अटल अंतरभूत पूर्णांक wm8350_out2_ramp_step(काष्ठा wm8350_data *wm8350_data)
अणु
	काष्ठा wm8350_output *out2 = &wm8350_data->out2;
	काष्ठा wm8350 *wm8350 = wm8350_data->wm8350;
	पूर्णांक left_complete = 0, right_complete = 0;
	u16 reg, val;

	/* left channel */
	reg = wm8350_reg_पढ़ो(wm8350, WM8350_LOUT2_VOLUME);
	val = (reg & WM8350_OUT2L_VOL_MASK) >> WM8350_OUT1L_VOL_SHIFT;
	अगर (out2->ramp == WM8350_RAMP_UP) अणु
		/* ramp step up */
		अगर (val < out2->left_vol) अणु
			val++;
			reg &= ~WM8350_OUT2L_VOL_MASK;
			wm8350_reg_ग_लिखो(wm8350, WM8350_LOUT2_VOLUME,
					 reg | (val << WM8350_OUT1L_VOL_SHIFT));
		पूर्ण अन्यथा
			left_complete = 1;
	पूर्ण अन्यथा अगर (out2->ramp == WM8350_RAMP_DOWN) अणु
		/* ramp step करोwn */
		अगर (val > 0) अणु
			val--;
			reg &= ~WM8350_OUT2L_VOL_MASK;
			wm8350_reg_ग_लिखो(wm8350, WM8350_LOUT2_VOLUME,
					 reg | (val << WM8350_OUT1L_VOL_SHIFT));
		पूर्ण अन्यथा
			left_complete = 1;
	पूर्ण अन्यथा
		वापस 1;

	/* right channel */
	reg = wm8350_reg_पढ़ो(wm8350, WM8350_ROUT2_VOLUME);
	val = (reg & WM8350_OUT2R_VOL_MASK) >> WM8350_OUT1R_VOL_SHIFT;
	अगर (out2->ramp == WM8350_RAMP_UP) अणु
		/* ramp step up */
		अगर (val < out2->right_vol) अणु
			val++;
			reg &= ~WM8350_OUT2R_VOL_MASK;
			wm8350_reg_ग_लिखो(wm8350, WM8350_ROUT2_VOLUME,
					 reg | (val << WM8350_OUT1R_VOL_SHIFT));
		पूर्ण अन्यथा
			right_complete = 1;
	पूर्ण अन्यथा अगर (out2->ramp == WM8350_RAMP_DOWN) अणु
		/* ramp step करोwn */
		अगर (val > 0) अणु
			val--;
			reg &= ~WM8350_OUT2R_VOL_MASK;
			wm8350_reg_ग_लिखो(wm8350, WM8350_ROUT2_VOLUME,
					 reg | (val << WM8350_OUT1R_VOL_SHIFT));
		पूर्ण अन्यथा
			right_complete = 1;
	पूर्ण

	/* only hit the update bit अगर either volume has changed this step */
	अगर (!left_complete || !right_complete)
		wm8350_set_bits(wm8350, WM8350_LOUT2_VOLUME, WM8350_OUT2_VU);

	वापस left_complete & right_complete;
पूर्ण

/*
 * This work ramps both output PGAs at stream start/stop समय to
 * minimise pop associated with DAPM घातer चयनing.
 * It's best to enable Zero Cross when ramping occurs to minimise any
 * zipper noises.
 */
अटल व्योम wm8350_pga_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wm8350_data *wm8350_data =
		container_of(work, काष्ठा wm8350_data, pga_work.work);
	काष्ठा wm8350_output *out1 = &wm8350_data->out1,
	    *out2 = &wm8350_data->out2;
	पूर्णांक i, out1_complete, out2_complete;

	/* करो we need to ramp at all ? */
	अगर (out1->ramp == WM8350_RAMP_NONE && out2->ramp == WM8350_RAMP_NONE)
		वापस;

	/* PGA volumes have 6 bits of resolution to ramp */
	क्रम (i = 0; i <= 63; i++) अणु
		out1_complete = 1;
		out2_complete = 1;
		अगर (out1->ramp != WM8350_RAMP_NONE)
			out1_complete = wm8350_out1_ramp_step(wm8350_data);
		अगर (out2->ramp != WM8350_RAMP_NONE)
			out2_complete = wm8350_out2_ramp_step(wm8350_data);

		/* ramp finished ? */
		अगर (out1_complete && out2_complete)
			अवरोध;

		/* we need to delay दीर्घer on the up ramp */
		अगर (out1->ramp == WM8350_RAMP_UP ||
		    out2->ramp == WM8350_RAMP_UP) अणु
			/* delay is दीर्घer over 0dB as increases are larger */
			अगर (i >= WM8350_OUTn_0dB)
				schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies
							       (2));
			अन्यथा
				schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies
							       (1));
		पूर्ण अन्यथा
			udelay(50);	/* करोesn't matter अगर we delay दीर्घer */
	पूर्ण

	out1->ramp = WM8350_RAMP_NONE;
	out2->ramp = WM8350_RAMP_NONE;
पूर्ण

/*
 * WM8350 Controls
 */

अटल पूर्णांक pga_event(काष्ठा snd_soc_dapm_widget *w,
		     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm8350_data *wm8350_data = snd_soc_component_get_drvdata(component);
	काष्ठा wm8350_output *out;

	चयन (w->shअगरt) अणु
	हाल 0:
	हाल 1:
		out = &wm8350_data->out1;
		अवरोध;
	हाल 2:
	हाल 3:
		out = &wm8350_data->out2;
		अवरोध;

	शेष:
		WARN(1, "Invalid shift %d\n", w->shअगरt);
		वापस -1;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		out->ramp = WM8350_RAMP_UP;
		out->active = 1;

		schedule_delayed_work(&wm8350_data->pga_work,
				      msecs_to_jअगरfies(1));
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		out->ramp = WM8350_RAMP_DOWN;
		out->active = 0;

		schedule_delayed_work(&wm8350_data->pga_work,
				      msecs_to_jअगरfies(1));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_put_volsw_2r_vu(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8350_data *wm8350_priv = snd_soc_component_get_drvdata(component);
	काष्ठा wm8350_output *out = शून्य;
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg = mc->reg;
	u16 val;

	/* For OUT1 and OUT2 we shaकरोw the values and only actually ग_लिखो
	 * them out when active in order to ensure the amplअगरier comes on
	 * as quietly as possible. */
	चयन (reg) अणु
	हाल WM8350_LOUT1_VOLUME:
		out = &wm8350_priv->out1;
		अवरोध;
	हाल WM8350_LOUT2_VOLUME:
		out = &wm8350_priv->out2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (out) अणु
		out->left_vol = ucontrol->value.पूर्णांकeger.value[0];
		out->right_vol = ucontrol->value.पूर्णांकeger.value[1];
		अगर (!out->active)
			वापस 1;
	पूर्ण

	ret = snd_soc_put_volsw(kcontrol, ucontrol);
	अगर (ret < 0)
		वापस ret;

	/* now hit the volume update bits (always bit 8) */
	val = snd_soc_component_पढ़ो(component, reg);
	snd_soc_component_ग_लिखो(component, reg, val | WM8350_OUT1_VU);
	वापस 1;
पूर्ण

अटल पूर्णांक wm8350_get_volsw_2r(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8350_data *wm8350_priv = snd_soc_component_get_drvdata(component);
	काष्ठा wm8350_output *out1 = &wm8350_priv->out1;
	काष्ठा wm8350_output *out2 = &wm8350_priv->out2;
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = mc->reg;

	/* If these are cached रेजिस्टरs use the cache */
	चयन (reg) अणु
	हाल WM8350_LOUT1_VOLUME:
		ucontrol->value.पूर्णांकeger.value[0] = out1->left_vol;
		ucontrol->value.पूर्णांकeger.value[1] = out1->right_vol;
		वापस 0;

	हाल WM8350_LOUT2_VOLUME:
		ucontrol->value.पूर्णांकeger.value[0] = out2->left_vol;
		ucontrol->value.पूर्णांकeger.value[1] = out2->right_vol;
		वापस 0;

	शेष:
		अवरोध;
	पूर्ण

	वापस snd_soc_get_volsw(kcontrol, ucontrol);
पूर्ण

अटल स्थिर अक्षर *wm8350_deemp[] = अणु "None", "32kHz", "44.1kHz", "48kHz" पूर्ण;
अटल स्थिर अक्षर *wm8350_pol[] = अणु "Normal", "Inv R", "Inv L", "Inv L & R" पूर्ण;
अटल स्थिर अक्षर *wm8350_dacmutem[] = अणु "Normal", "Soft" पूर्ण;
अटल स्थिर अक्षर *wm8350_dacmutes[] = अणु "Fast", "Slow" पूर्ण;
अटल स्थिर अक्षर *wm8350_adcfilter[] = अणु "None", "High Pass" पूर्ण;
अटल स्थिर अक्षर *wm8350_adchp[] = अणु "44.1kHz", "8kHz", "16kHz", "32kHz" पूर्ण;
अटल स्थिर अक्षर *wm8350_lr[] = अणु "Left", "Right" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत wm8350_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(WM8350_DAC_CONTROL, 4, 4, wm8350_deemp),
	SOC_ENUM_SINGLE(WM8350_DAC_CONTROL, 0, 4, wm8350_pol),
	SOC_ENUM_SINGLE(WM8350_DAC_MUTE_VOLUME, 14, 2, wm8350_dacmutem),
	SOC_ENUM_SINGLE(WM8350_DAC_MUTE_VOLUME, 13, 2, wm8350_dacmutes),
	SOC_ENUM_SINGLE(WM8350_ADC_CONTROL, 15, 2, wm8350_adcfilter),
	SOC_ENUM_SINGLE(WM8350_ADC_CONTROL, 8, 4, wm8350_adchp),
	SOC_ENUM_SINGLE(WM8350_ADC_CONTROL, 0, 4, wm8350_pol),
	SOC_ENUM_SINGLE(WM8350_INPUT_MIXER_VOLUME, 15, 2, wm8350_lr),
पूर्ण;

अटल DECLARE_TLV_DB_SCALE(pre_amp_tlv, -1200, 3525, 0);
अटल DECLARE_TLV_DB_SCALE(out_pga_tlv, -5700, 600, 0);
अटल DECLARE_TLV_DB_SCALE(dac_pcm_tlv, -7163, 36, 1);
अटल DECLARE_TLV_DB_SCALE(adc_pcm_tlv, -12700, 50, 1);
अटल DECLARE_TLV_DB_SCALE(out_mix_tlv, -1500, 300, 1);

अटल स्थिर DECLARE_TLV_DB_RANGE(capture_sd_tlv,
	0, 12, TLV_DB_SCALE_ITEM(-3600, 300, 1),
	13, 15, TLV_DB_SCALE_ITEM(0, 0, 0)
);

अटल स्थिर काष्ठा snd_kcontrol_new wm8350_snd_controls[] = अणु
	SOC_ENUM("Playback Deemphasis", wm8350_क्रमागत[0]),
	SOC_ENUM("Playback DAC Inversion", wm8350_क्रमागत[1]),
	SOC_DOUBLE_R_EXT_TLV("Playback PCM Volume",
				WM8350_DAC_DIGITAL_VOLUME_L,
				WM8350_DAC_DIGITAL_VOLUME_R,
				0, 255, 0, wm8350_get_volsw_2r,
				wm8350_put_volsw_2r_vu, dac_pcm_tlv),
	SOC_ENUM("Playback PCM Mute Function", wm8350_क्रमागत[2]),
	SOC_ENUM("Playback PCM Mute Speed", wm8350_क्रमागत[3]),
	SOC_ENUM("Capture PCM Filter", wm8350_क्रमागत[4]),
	SOC_ENUM("Capture PCM HP Filter", wm8350_क्रमागत[5]),
	SOC_ENUM("Capture ADC Inversion", wm8350_क्रमागत[6]),
	SOC_DOUBLE_R_EXT_TLV("Capture PCM Volume",
				WM8350_ADC_DIGITAL_VOLUME_L,
				WM8350_ADC_DIGITAL_VOLUME_R,
				0, 255, 0, wm8350_get_volsw_2r,
				wm8350_put_volsw_2r_vu, adc_pcm_tlv),
	SOC_DOUBLE_TLV("Capture Sidetone Volume",
		       WM8350_ADC_DIVIDER,
		       8, 4, 15, 1, capture_sd_tlv),
	SOC_DOUBLE_R_EXT_TLV("Capture Volume",
				WM8350_LEFT_INPUT_VOLUME,
				WM8350_RIGHT_INPUT_VOLUME,
				2, 63, 0, wm8350_get_volsw_2r,
				wm8350_put_volsw_2r_vu, pre_amp_tlv),
	SOC_DOUBLE_R("Capture ZC Switch",
		     WM8350_LEFT_INPUT_VOLUME,
		     WM8350_RIGHT_INPUT_VOLUME, 13, 1, 0),
	SOC_SINGLE_TLV("Left Input Left Sidetone Volume",
		       WM8350_OUTPUT_LEFT_MIXER_VOLUME, 1, 7, 0, out_mix_tlv),
	SOC_SINGLE_TLV("Left Input Right Sidetone Volume",
		       WM8350_OUTPUT_LEFT_MIXER_VOLUME,
		       5, 7, 0, out_mix_tlv),
	SOC_SINGLE_TLV("Left Input Bypass Volume",
		       WM8350_OUTPUT_LEFT_MIXER_VOLUME,
		       9, 7, 0, out_mix_tlv),
	SOC_SINGLE_TLV("Right Input Left Sidetone Volume",
		       WM8350_OUTPUT_RIGHT_MIXER_VOLUME,
		       1, 7, 0, out_mix_tlv),
	SOC_SINGLE_TLV("Right Input Right Sidetone Volume",
		       WM8350_OUTPUT_RIGHT_MIXER_VOLUME,
		       5, 7, 0, out_mix_tlv),
	SOC_SINGLE_TLV("Right Input Bypass Volume",
		       WM8350_OUTPUT_RIGHT_MIXER_VOLUME,
		       13, 7, 0, out_mix_tlv),
	SOC_SINGLE("Left Input Mixer +20dB Switch",
		   WM8350_INPUT_MIXER_VOLUME_L, 0, 1, 0),
	SOC_SINGLE("Right Input Mixer +20dB Switch",
		   WM8350_INPUT_MIXER_VOLUME_R, 0, 1, 0),
	SOC_SINGLE_TLV("Out4 Capture Volume",
		       WM8350_INPUT_MIXER_VOLUME,
		       1, 7, 0, out_mix_tlv),
	SOC_DOUBLE_R_EXT_TLV("Out1 Playback Volume",
				WM8350_LOUT1_VOLUME,
				WM8350_ROUT1_VOLUME,
				2, 63, 0, wm8350_get_volsw_2r,
				wm8350_put_volsw_2r_vu, out_pga_tlv),
	SOC_DOUBLE_R("Out1 Playback ZC Switch",
		     WM8350_LOUT1_VOLUME,
		     WM8350_ROUT1_VOLUME, 13, 1, 0),
	SOC_DOUBLE_R_EXT_TLV("Out2 Playback Volume",
				WM8350_LOUT2_VOLUME,
				WM8350_ROUT2_VOLUME,
				2, 63, 0, wm8350_get_volsw_2r,
				wm8350_put_volsw_2r_vu, out_pga_tlv),
	SOC_DOUBLE_R("Out2 Playback ZC Switch", WM8350_LOUT2_VOLUME,
		     WM8350_ROUT2_VOLUME, 13, 1, 0),
	SOC_SINGLE("Out2 Right Invert Switch", WM8350_ROUT2_VOLUME, 10, 1, 0),
	SOC_SINGLE_TLV("Out2 Beep Volume", WM8350_BEEP_VOLUME,
		       5, 7, 0, out_mix_tlv),

	SOC_DOUBLE_R("Out1 Playback Switch",
		     WM8350_LOUT1_VOLUME,
		     WM8350_ROUT1_VOLUME,
		     14, 1, 1),
	SOC_DOUBLE_R("Out2 Playback Switch",
		     WM8350_LOUT2_VOLUME,
		     WM8350_ROUT2_VOLUME,
		     14, 1, 1),
पूर्ण;

/*
 * DAPM Controls
 */

/* Left Playback Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8350_left_play_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Playback Switch",
			WM8350_LEFT_MIXER_CONTROL, 11, 1, 0),
	SOC_DAPM_SINGLE("Left Bypass Switch",
			WM8350_LEFT_MIXER_CONTROL, 2, 1, 0),
	SOC_DAPM_SINGLE("Right Playback Switch",
			WM8350_LEFT_MIXER_CONTROL, 12, 1, 0),
	SOC_DAPM_SINGLE("Left Sidetone Switch",
			WM8350_LEFT_MIXER_CONTROL, 0, 1, 0),
	SOC_DAPM_SINGLE("Right Sidetone Switch",
			WM8350_LEFT_MIXER_CONTROL, 1, 1, 0),
पूर्ण;

/* Right Playback Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8350_right_play_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Playback Switch",
			WM8350_RIGHT_MIXER_CONTROL, 12, 1, 0),
	SOC_DAPM_SINGLE("Right Bypass Switch",
			WM8350_RIGHT_MIXER_CONTROL, 3, 1, 0),
	SOC_DAPM_SINGLE("Left Playback Switch",
			WM8350_RIGHT_MIXER_CONTROL, 11, 1, 0),
	SOC_DAPM_SINGLE("Left Sidetone Switch",
			WM8350_RIGHT_MIXER_CONTROL, 0, 1, 0),
	SOC_DAPM_SINGLE("Right Sidetone Switch",
			WM8350_RIGHT_MIXER_CONTROL, 1, 1, 0),
पूर्ण;

/* Out4 Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8350_out4_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Right Playback Switch",
			WM8350_OUT4_MIXER_CONTROL, 12, 1, 0),
	SOC_DAPM_SINGLE("Left Playback Switch",
			WM8350_OUT4_MIXER_CONTROL, 11, 1, 0),
	SOC_DAPM_SINGLE("Right Capture Switch",
			WM8350_OUT4_MIXER_CONTROL, 9, 1, 0),
	SOC_DAPM_SINGLE("Out3 Playback Switch",
			WM8350_OUT4_MIXER_CONTROL, 2, 1, 0),
	SOC_DAPM_SINGLE("Right Mixer Switch",
			WM8350_OUT4_MIXER_CONTROL, 1, 1, 0),
	SOC_DAPM_SINGLE("Left Mixer Switch",
			WM8350_OUT4_MIXER_CONTROL, 0, 1, 0),
पूर्ण;

/* Out3 Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8350_out3_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left Playback Switch",
			WM8350_OUT3_MIXER_CONTROL, 11, 1, 0),
	SOC_DAPM_SINGLE("Left Capture Switch",
			WM8350_OUT3_MIXER_CONTROL, 8, 1, 0),
	SOC_DAPM_SINGLE("Out4 Playback Switch",
			WM8350_OUT3_MIXER_CONTROL, 3, 1, 0),
	SOC_DAPM_SINGLE("Left Mixer Switch",
			WM8350_OUT3_MIXER_CONTROL, 0, 1, 0),
पूर्ण;

/* Left Input Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8350_left_capt_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_TLV("L2 Capture Volume",
			    WM8350_INPUT_MIXER_VOLUME_L, 1, 7, 0, out_mix_tlv),
	SOC_DAPM_SINGLE_TLV("L3 Capture Volume",
			    WM8350_INPUT_MIXER_VOLUME_L, 9, 7, 0, out_mix_tlv),
	SOC_DAPM_SINGLE("PGA Capture Switch",
			WM8350_LEFT_INPUT_VOLUME, 14, 1, 1),
पूर्ण;

/* Right Input Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8350_right_capt_mixer_controls[] = अणु
	SOC_DAPM_SINGLE_TLV("L2 Capture Volume",
			    WM8350_INPUT_MIXER_VOLUME_R, 5, 7, 0, out_mix_tlv),
	SOC_DAPM_SINGLE_TLV("L3 Capture Volume",
			    WM8350_INPUT_MIXER_VOLUME_R, 13, 7, 0, out_mix_tlv),
	SOC_DAPM_SINGLE("PGA Capture Switch",
			WM8350_RIGHT_INPUT_VOLUME, 14, 1, 1),
पूर्ण;

/* Left Mic Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8350_left_mic_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("INN Capture Switch", WM8350_INPUT_CONTROL, 1, 1, 0),
	SOC_DAPM_SINGLE("INP Capture Switch", WM8350_INPUT_CONTROL, 0, 1, 0),
	SOC_DAPM_SINGLE("IN2 Capture Switch", WM8350_INPUT_CONTROL, 2, 1, 0),
पूर्ण;

/* Right Mic Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8350_right_mic_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("INN Capture Switch", WM8350_INPUT_CONTROL, 9, 1, 0),
	SOC_DAPM_SINGLE("INP Capture Switch", WM8350_INPUT_CONTROL, 8, 1, 0),
	SOC_DAPM_SINGLE("IN2 Capture Switch", WM8350_INPUT_CONTROL, 10, 1, 0),
पूर्ण;

/* Beep Switch */
अटल स्थिर काष्ठा snd_kcontrol_new wm8350_beep_चयन_controls =
SOC_DAPM_SINGLE("Switch", WM8350_BEEP_VOLUME, 15, 1, 1);

/* Out4 Capture Mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8350_out4_capture_controls =
SOC_DAPM_ENUM("Route", wm8350_क्रमागत[7]);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8350_dapm_widमाला_लो[] = अणु

	SND_SOC_DAPM_PGA("IN3R PGA", WM8350_POWER_MGMT_2, 11, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("IN3L PGA", WM8350_POWER_MGMT_2, 10, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_E("Right Out2 PGA", WM8350_POWER_MGMT_3, 3, 0, शून्य,
			   0, pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_PGA_E("Left Out2 PGA", WM8350_POWER_MGMT_3, 2, 0, शून्य, 0,
			   pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_PGA_E("Right Out1 PGA", WM8350_POWER_MGMT_3, 1, 0, शून्य,
			   0, pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_PGA_E("Left Out1 PGA", WM8350_POWER_MGMT_3, 0, 0, शून्य, 0,
			   pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_MIXER("Right Capture Mixer", WM8350_POWER_MGMT_2,
			   7, 0, &wm8350_right_capt_mixer_controls[0],
			   ARRAY_SIZE(wm8350_right_capt_mixer_controls)),

	SND_SOC_DAPM_MIXER("Left Capture Mixer", WM8350_POWER_MGMT_2,
			   6, 0, &wm8350_left_capt_mixer_controls[0],
			   ARRAY_SIZE(wm8350_left_capt_mixer_controls)),

	SND_SOC_DAPM_MIXER("Out4 Mixer", WM8350_POWER_MGMT_2, 5, 0,
			   &wm8350_out4_mixer_controls[0],
			   ARRAY_SIZE(wm8350_out4_mixer_controls)),

	SND_SOC_DAPM_MIXER("Out3 Mixer", WM8350_POWER_MGMT_2, 4, 0,
			   &wm8350_out3_mixer_controls[0],
			   ARRAY_SIZE(wm8350_out3_mixer_controls)),

	SND_SOC_DAPM_MIXER("Right Playback Mixer", WM8350_POWER_MGMT_2, 1, 0,
			   &wm8350_right_play_mixer_controls[0],
			   ARRAY_SIZE(wm8350_right_play_mixer_controls)),

	SND_SOC_DAPM_MIXER("Left Playback Mixer", WM8350_POWER_MGMT_2, 0, 0,
			   &wm8350_left_play_mixer_controls[0],
			   ARRAY_SIZE(wm8350_left_play_mixer_controls)),

	SND_SOC_DAPM_MIXER("Left Mic Mixer", WM8350_POWER_MGMT_2, 8, 0,
			   &wm8350_left_mic_mixer_controls[0],
			   ARRAY_SIZE(wm8350_left_mic_mixer_controls)),

	SND_SOC_DAPM_MIXER("Right Mic Mixer", WM8350_POWER_MGMT_2, 9, 0,
			   &wm8350_right_mic_mixer_controls[0],
			   ARRAY_SIZE(wm8350_right_mic_mixer_controls)),

	/* भव mixer क्रम Beep and Out2R */
	SND_SOC_DAPM_MIXER("Out2 Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SWITCH("Beep", WM8350_POWER_MGMT_3, 7, 0,
			    &wm8350_beep_चयन_controls),

	SND_SOC_DAPM_ADC("Right ADC", "Right Capture",
			 WM8350_POWER_MGMT_4, 3, 0),
	SND_SOC_DAPM_ADC("Left ADC", "Left Capture",
			 WM8350_POWER_MGMT_4, 2, 0),
	SND_SOC_DAPM_DAC("Right DAC", "Right Playback",
			 WM8350_POWER_MGMT_4, 5, 0),
	SND_SOC_DAPM_DAC("Left DAC", "Left Playback",
			 WM8350_POWER_MGMT_4, 4, 0),

	SND_SOC_DAPM_MICBIAS("Mic Bias", WM8350_POWER_MGMT_1, 4, 0),

	SND_SOC_DAPM_MUX("Out4 Capture Channel", SND_SOC_NOPM, 0, 0,
			 &wm8350_out4_capture_controls),

	SND_SOC_DAPM_OUTPUT("OUT1R"),
	SND_SOC_DAPM_OUTPUT("OUT1L"),
	SND_SOC_DAPM_OUTPUT("OUT2R"),
	SND_SOC_DAPM_OUTPUT("OUT2L"),
	SND_SOC_DAPM_OUTPUT("OUT3"),
	SND_SOC_DAPM_OUTPUT("OUT4"),

	SND_SOC_DAPM_INPUT("IN1RN"),
	SND_SOC_DAPM_INPUT("IN1RP"),
	SND_SOC_DAPM_INPUT("IN2R"),
	SND_SOC_DAPM_INPUT("IN1LP"),
	SND_SOC_DAPM_INPUT("IN1LN"),
	SND_SOC_DAPM_INPUT("IN2L"),
	SND_SOC_DAPM_INPUT("IN3R"),
	SND_SOC_DAPM_INPUT("IN3L"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8350_dapm_routes[] = अणु

	/* left playback mixer */
	अणु"Left Playback Mixer", "Playback Switch", "Left DAC"पूर्ण,
	अणु"Left Playback Mixer", "Left Bypass Switch", "IN3L PGA"पूर्ण,
	अणु"Left Playback Mixer", "Right Playback Switch", "Right DAC"पूर्ण,
	अणु"Left Playback Mixer", "Left Sidetone Switch", "Left Mic Mixer"पूर्ण,
	अणु"Left Playback Mixer", "Right Sidetone Switch", "Right Mic Mixer"पूर्ण,

	/* right playback mixer */
	अणु"Right Playback Mixer", "Playback Switch", "Right DAC"पूर्ण,
	अणु"Right Playback Mixer", "Right Bypass Switch", "IN3R PGA"पूर्ण,
	अणु"Right Playback Mixer", "Left Playback Switch", "Left DAC"पूर्ण,
	अणु"Right Playback Mixer", "Left Sidetone Switch", "Left Mic Mixer"पूर्ण,
	अणु"Right Playback Mixer", "Right Sidetone Switch", "Right Mic Mixer"पूर्ण,

	/* out4 playback mixer */
	अणु"Out4 Mixer", "Right Playback Switch", "Right DAC"पूर्ण,
	अणु"Out4 Mixer", "Left Playback Switch", "Left DAC"पूर्ण,
	अणु"Out4 Mixer", "Right Capture Switch", "Right Capture Mixer"पूर्ण,
	अणु"Out4 Mixer", "Out3 Playback Switch", "Out3 Mixer"पूर्ण,
	अणु"Out4 Mixer", "Right Mixer Switch", "Right Playback Mixer"पूर्ण,
	अणु"Out4 Mixer", "Left Mixer Switch", "Left Playback Mixer"पूर्ण,
	अणु"OUT4", शून्य, "Out4 Mixer"पूर्ण,

	/* out3 playback mixer */
	अणु"Out3 Mixer", "Left Playback Switch", "Left DAC"पूर्ण,
	अणु"Out3 Mixer", "Left Capture Switch", "Left Capture Mixer"पूर्ण,
	अणु"Out3 Mixer", "Left Mixer Switch", "Left Playback Mixer"पूर्ण,
	अणु"Out3 Mixer", "Out4 Playback Switch", "Out4 Mixer"पूर्ण,
	अणु"OUT3", शून्य, "Out3 Mixer"पूर्ण,

	/* out2 */
	अणु"Right Out2 PGA", शून्य, "Right Playback Mixer"पूर्ण,
	अणु"Left Out2 PGA", शून्य, "Left Playback Mixer"पूर्ण,
	अणु"OUT2L", शून्य, "Left Out2 PGA"पूर्ण,
	अणु"OUT2R", शून्य, "Right Out2 PGA"पूर्ण,

	/* out1 */
	अणु"Right Out1 PGA", शून्य, "Right Playback Mixer"पूर्ण,
	अणु"Left Out1 PGA", शून्य, "Left Playback Mixer"पूर्ण,
	अणु"OUT1L", शून्य, "Left Out1 PGA"पूर्ण,
	अणु"OUT1R", शून्य, "Right Out1 PGA"पूर्ण,

	/* ADCs */
	अणु"Left ADC", शून्य, "Left Capture Mixer"पूर्ण,
	अणु"Right ADC", शून्य, "Right Capture Mixer"पूर्ण,

	/* Left capture mixer */
	अणु"Left Capture Mixer", "L2 Capture Volume", "IN2L"पूर्ण,
	अणु"Left Capture Mixer", "L3 Capture Volume", "IN3L PGA"पूर्ण,
	अणु"Left Capture Mixer", "PGA Capture Switch", "Left Mic Mixer"पूर्ण,
	अणु"Left Capture Mixer", शून्य, "Out4 Capture Channel"पूर्ण,

	/* Right capture mixer */
	अणु"Right Capture Mixer", "L2 Capture Volume", "IN2R"पूर्ण,
	अणु"Right Capture Mixer", "L3 Capture Volume", "IN3R PGA"पूर्ण,
	अणु"Right Capture Mixer", "PGA Capture Switch", "Right Mic Mixer"पूर्ण,
	अणु"Right Capture Mixer", शून्य, "Out4 Capture Channel"पूर्ण,

	/* L3 Inमाला_दो */
	अणु"IN3L PGA", शून्य, "IN3L"पूर्ण,
	अणु"IN3R PGA", शून्य, "IN3R"पूर्ण,

	/* Left Mic mixer */
	अणु"Left Mic Mixer", "INN Capture Switch", "IN1LN"पूर्ण,
	अणु"Left Mic Mixer", "INP Capture Switch", "IN1LP"पूर्ण,
	अणु"Left Mic Mixer", "IN2 Capture Switch", "IN2L"पूर्ण,

	/* Right Mic mixer */
	अणु"Right Mic Mixer", "INN Capture Switch", "IN1RN"पूर्ण,
	अणु"Right Mic Mixer", "INP Capture Switch", "IN1RP"पूर्ण,
	अणु"Right Mic Mixer", "IN2 Capture Switch", "IN2R"पूर्ण,

	/* out 4 capture */
	अणु"Out4 Capture Channel", शून्य, "Out4 Mixer"पूर्ण,

	/* Beep */
	अणु"Beep", शून्य, "IN3R PGA"पूर्ण,
पूर्ण;

अटल पूर्णांक wm8350_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8350_data *wm8350_data = snd_soc_component_get_drvdata(component);
	काष्ठा wm8350 *wm8350 = wm8350_data->wm8350;
	u16 fll_4;

	चयन (clk_id) अणु
	हाल WM8350_MCLK_SEL_MCLK:
		wm8350_clear_bits(wm8350, WM8350_CLOCK_CONTROL_1,
				  WM8350_MCLK_SEL);
		अवरोध;
	हाल WM8350_MCLK_SEL_PLL_MCLK:
	हाल WM8350_MCLK_SEL_PLL_DAC:
	हाल WM8350_MCLK_SEL_PLL_ADC:
	हाल WM8350_MCLK_SEL_PLL_32K:
		wm8350_set_bits(wm8350, WM8350_CLOCK_CONTROL_1,
				WM8350_MCLK_SEL);
		fll_4 = snd_soc_component_पढ़ो(component, WM8350_FLL_CONTROL_4) &
		    ~WM8350_FLL_CLK_SRC_MASK;
		snd_soc_component_ग_लिखो(component, WM8350_FLL_CONTROL_4, fll_4 | clk_id);
		अवरोध;
	पूर्ण

	/* MCLK direction */
	अगर (dir == SND_SOC_CLOCK_OUT)
		wm8350_set_bits(wm8350, WM8350_CLOCK_CONTROL_2,
				WM8350_MCLK_सूची);
	अन्यथा
		wm8350_clear_bits(wm8350, WM8350_CLOCK_CONTROL_2,
				  WM8350_MCLK_सूची);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_set_clkभाग(काष्ठा snd_soc_dai *codec_dai, पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 val;

	चयन (भाग_id) अणु
	हाल WM8350_ADC_CLKDIV:
		val = snd_soc_component_पढ़ो(component, WM8350_ADC_DIVIDER) &
		    ~WM8350_ADC_CLKDIV_MASK;
		snd_soc_component_ग_लिखो(component, WM8350_ADC_DIVIDER, val | भाग);
		अवरोध;
	हाल WM8350_DAC_CLKDIV:
		val = snd_soc_component_पढ़ो(component, WM8350_DAC_CLOCK_CONTROL) &
		    ~WM8350_DAC_CLKDIV_MASK;
		snd_soc_component_ग_लिखो(component, WM8350_DAC_CLOCK_CONTROL, val | भाग);
		अवरोध;
	हाल WM8350_BCLK_CLKDIV:
		val = snd_soc_component_पढ़ो(component, WM8350_CLOCK_CONTROL_1) &
		    ~WM8350_BCLK_DIV_MASK;
		snd_soc_component_ग_लिखो(component, WM8350_CLOCK_CONTROL_1, val | भाग);
		अवरोध;
	हाल WM8350_OPCLK_CLKDIV:
		val = snd_soc_component_पढ़ो(component, WM8350_CLOCK_CONTROL_1) &
		    ~WM8350_OPCLK_DIV_MASK;
		snd_soc_component_ग_लिखो(component, WM8350_CLOCK_CONTROL_1, val | भाग);
		अवरोध;
	हाल WM8350_SYS_CLKDIV:
		val = snd_soc_component_पढ़ो(component, WM8350_CLOCK_CONTROL_1) &
		    ~WM8350_MCLK_DIV_MASK;
		snd_soc_component_ग_लिखो(component, WM8350_CLOCK_CONTROL_1, val | भाग);
		अवरोध;
	हाल WM8350_DACLR_CLKDIV:
		val = snd_soc_component_पढ़ो(component, WM8350_DAC_LR_RATE) &
		    ~WM8350_DACLRC_RATE_MASK;
		snd_soc_component_ग_लिखो(component, WM8350_DAC_LR_RATE, val | भाग);
		अवरोध;
	हाल WM8350_ADCLR_CLKDIV:
		val = snd_soc_component_पढ़ो(component, WM8350_ADC_LR_RATE) &
		    ~WM8350_ADCLRC_RATE_MASK;
		snd_soc_component_ग_लिखो(component, WM8350_ADC_LR_RATE, val | भाग);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 अगरace = snd_soc_component_पढ़ो(component, WM8350_AI_FORMATING) &
	    ~(WM8350_AIF_BCLK_INV | WM8350_AIF_LRCLK_INV | WM8350_AIF_FMT_MASK);
	u16 master = snd_soc_component_पढ़ो(component, WM8350_AI_DAC_CONTROL) &
	    ~WM8350_BCLK_MSTR;
	u16 dac_lrc = snd_soc_component_पढ़ो(component, WM8350_DAC_LR_RATE) &
	    ~WM8350_DACLRC_ENA;
	u16 adc_lrc = snd_soc_component_पढ़ो(component, WM8350_ADC_LR_RATE) &
	    ~WM8350_ADCLRC_ENA;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		master |= WM8350_BCLK_MSTR;
		dac_lrc |= WM8350_DACLRC_ENA;
		adc_lrc |= WM8350_ADCLRC_ENA;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= 0x2 << 8;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= 0x1 << 8;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace |= 0x3 << 8;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगरace |= 0x3 << 8 | WM8350_AIF_LRCLK_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= WM8350_AIF_LRCLK_INV | WM8350_AIF_BCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= WM8350_AIF_BCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगरace |= WM8350_AIF_LRCLK_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8350_AI_FORMATING, अगरace);
	snd_soc_component_ग_लिखो(component, WM8350_AI_DAC_CONTROL, master);
	snd_soc_component_ग_लिखो(component, WM8350_DAC_LR_RATE, dac_lrc);
	snd_soc_component_ग_लिखो(component, WM8350_ADC_LR_RATE, adc_lrc);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *codec_dai)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8350_data *wm8350_data = snd_soc_component_get_drvdata(component);
	काष्ठा wm8350 *wm8350 = wm8350_data->wm8350;
	u16 अगरace = snd_soc_component_पढ़ो(component, WM8350_AI_FORMATING) &
	    ~WM8350_AIF_WL_MASK;

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		अगरace |= 0x1 << 10;
		अवरोध;
	हाल 24:
		अगरace |= 0x2 << 10;
		अवरोध;
	हाल 32:
		अगरace |= 0x3 << 10;
		अवरोध;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8350_AI_FORMATING, अगरace);

	/* The sloping stopband filter is recommended क्रम use with
	 * lower sample rates to improve perक्रमmance.
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (params_rate(params) < 24000)
			wm8350_set_bits(wm8350, WM8350_DAC_MUTE_VOLUME,
					WM8350_DAC_SB_FILT);
		अन्यथा
			wm8350_clear_bits(wm8350, WM8350_DAC_MUTE_VOLUME,
					  WM8350_DAC_SB_FILT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक val;

	अगर (mute)
		val = WM8350_DAC_MUTE_ENA;
	अन्यथा
		val = 0;

	snd_soc_component_update_bits(component, WM8350_DAC_MUTE, WM8350_DAC_MUTE_ENA, val);

	वापस 0;
पूर्ण

/* FLL भागisors */
काष्ठा _fll_भाग अणु
	पूर्णांक भाग;		/* FLL_OUTDIV */
	पूर्णांक n;
	पूर्णांक k;
	पूर्णांक ratio;		/* FLL_FRATIO */
पूर्ण;

/* The size in bits of the fll भागide multiplied by 10
 * to allow rounding later */
#घोषणा FIXED_FLL_SIZE ((1 << 16) * 10)

अटल अंतरभूत पूर्णांक fll_factors(काष्ठा _fll_भाग *fll_भाग, अचिन्हित पूर्णांक input,
			      अचिन्हित पूर्णांक output)
अणु
	u64 Kpart;
	अचिन्हित पूर्णांक t1, t2, K, Nmod;

	अगर (output >= 2815250 && output <= 3125000)
		fll_भाग->भाग = 0x4;
	अन्यथा अगर (output >= 5625000 && output <= 6250000)
		fll_भाग->भाग = 0x3;
	अन्यथा अगर (output >= 11250000 && output <= 12500000)
		fll_भाग->भाग = 0x2;
	अन्यथा अगर (output >= 22500000 && output <= 25000000)
		fll_भाग->भाग = 0x1;
	अन्यथा अणु
		prपूर्णांकk(KERN_ERR "wm8350: fll freq %d out of range\n", output);
		वापस -EINVAL;
	पूर्ण

	अगर (input > 48000)
		fll_भाग->ratio = 1;
	अन्यथा
		fll_भाग->ratio = 8;

	t1 = output * (1 << (fll_भाग->भाग + 1));
	t2 = input * fll_भाग->ratio;

	fll_भाग->n = t1 / t2;
	Nmod = t1 % t2;

	अगर (Nmod) अणु
		Kpart = FIXED_FLL_SIZE * (दीर्घ दीर्घ)Nmod;
		करो_भाग(Kpart, t2);
		K = Kpart & 0xFFFFFFFF;

		/* Check अगर we need to round */
		अगर ((K % 10) >= 5)
			K += 5;

		/* Move करोwn to proper range now rounding is करोne */
		K /= 10;
		fll_भाग->k = K;
	पूर्ण अन्यथा
		fll_भाग->k = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_set_fll(काष्ठा snd_soc_dai *codec_dai,
			  पूर्णांक pll_id, पूर्णांक source, अचिन्हित पूर्णांक freq_in,
			  अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8350_data *priv = snd_soc_component_get_drvdata(component);
	काष्ठा wm8350 *wm8350 = priv->wm8350;
	काष्ठा _fll_भाग fll_भाग;
	पूर्णांक ret = 0;
	u16 fll_1, fll_4;

	अगर (freq_in == priv->fll_freq_in && freq_out == priv->fll_freq_out)
		वापस 0;

	/* घातer करोwn FLL - we need to करो this क्रम reconfiguration */
	wm8350_clear_bits(wm8350, WM8350_POWER_MGMT_4,
			  WM8350_FLL_ENA | WM8350_FLL_OSC_ENA);

	अगर (freq_out == 0 || freq_in == 0)
		वापस ret;

	ret = fll_factors(&fll_भाग, freq_in, freq_out);
	अगर (ret < 0)
		वापस ret;
	dev_dbg(wm8350->dev,
		"FLL in %u FLL out %u N 0x%x K 0x%x div %d ratio %d",
		freq_in, freq_out, fll_भाग.n, fll_भाग.k, fll_भाग.भाग,
		fll_भाग.ratio);

	/* set up N.K & भागiders */
	fll_1 = snd_soc_component_पढ़ो(component, WM8350_FLL_CONTROL_1) &
	    ~(WM8350_FLL_OUTDIV_MASK | WM8350_FLL_RSP_RATE_MASK | 0xc000);
	snd_soc_component_ग_लिखो(component, WM8350_FLL_CONTROL_1,
			   fll_1 | (fll_भाग.भाग << 8) | 0x50);
	snd_soc_component_ग_लिखो(component, WM8350_FLL_CONTROL_2,
			   (fll_भाग.ratio << 11) | (fll_भाग.
						    n & WM8350_FLL_N_MASK));
	snd_soc_component_ग_लिखो(component, WM8350_FLL_CONTROL_3, fll_भाग.k);
	fll_4 = snd_soc_component_पढ़ो(component, WM8350_FLL_CONTROL_4) &
	    ~(WM8350_FLL_FRAC | WM8350_FLL_SLOW_LOCK_REF);
	snd_soc_component_ग_लिखो(component, WM8350_FLL_CONTROL_4,
			   fll_4 | (fll_भाग.k ? WM8350_FLL_FRAC : 0) |
			   (fll_भाग.ratio == 8 ? WM8350_FLL_SLOW_LOCK_REF : 0));

	/* घातer FLL on */
	wm8350_set_bits(wm8350, WM8350_POWER_MGMT_4, WM8350_FLL_OSC_ENA);
	wm8350_set_bits(wm8350, WM8350_POWER_MGMT_4, WM8350_FLL_ENA);

	priv->fll_freq_out = freq_out;
	priv->fll_freq_in = freq_in;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8350_data *priv = snd_soc_component_get_drvdata(component);
	काष्ठा wm8350 *wm8350 = priv->wm8350;
	काष्ठा wm8350_audio_platक्रमm_data *platक्रमm =
		wm8350->codec.platक्रमm_data;
	u16 pm1;
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		pm1 = wm8350_reg_पढ़ो(wm8350, WM8350_POWER_MGMT_1) &
		    ~(WM8350_VMID_MASK | WM8350_CODEC_ISEL_MASK);
		wm8350_reg_ग_लिखो(wm8350, WM8350_POWER_MGMT_1,
				 pm1 | WM8350_VMID_50K |
				 platक्रमm->codec_current_on << 14);
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		pm1 = wm8350_reg_पढ़ो(wm8350, WM8350_POWER_MGMT_1);
		pm1 &= ~WM8350_VMID_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_POWER_MGMT_1,
				 pm1 | WM8350_VMID_50K);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regulator_bulk_enable(ARRAY_SIZE(priv->supplies),
						    priv->supplies);
			अगर (ret != 0)
				वापस ret;

			/* Enable the प्रणाली घड़ी */
			wm8350_set_bits(wm8350, WM8350_POWER_MGMT_4,
					WM8350_SYSCLK_ENA);

			/* mute DAC & outमाला_दो */
			wm8350_set_bits(wm8350, WM8350_DAC_MUTE,
					WM8350_DAC_MUTE_ENA);

			/* disअक्षरge cap memory */
			wm8350_reg_ग_लिखो(wm8350, WM8350_ANTI_POP_CONTROL,
					 platक्रमm->dis_out1 |
					 (platक्रमm->dis_out2 << 2) |
					 (platक्रमm->dis_out3 << 4) |
					 (platक्रमm->dis_out4 << 6));

			/* रुको क्रम disअक्षरge */
			schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies
						       (platक्रमm->
							cap_disअक्षरge_msecs));

			/* enable antipop */
			wm8350_reg_ग_लिखो(wm8350, WM8350_ANTI_POP_CONTROL,
					 (platक्रमm->vmid_s_curve << 8));

			/* ramp up vmid */
			wm8350_reg_ग_लिखो(wm8350, WM8350_POWER_MGMT_1,
					 (platक्रमm->
					  codec_current_अक्षरge << 14) |
					 WM8350_VMID_5K | WM8350_VMIDEN |
					 WM8350_VBUFEN);

			/* रुको क्रम vmid */
			schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies
						       (platक्रमm->
							vmid_अक्षरge_msecs));

			/* turn on vmid 300k  */
			pm1 = wm8350_reg_पढ़ो(wm8350, WM8350_POWER_MGMT_1) &
			    ~(WM8350_VMID_MASK | WM8350_CODEC_ISEL_MASK);
			pm1 |= WM8350_VMID_300K |
				(platक्रमm->codec_current_standby << 14);
			wm8350_reg_ग_लिखो(wm8350, WM8350_POWER_MGMT_1,
					 pm1);


			/* enable analogue bias */
			pm1 |= WM8350_BIASEN;
			wm8350_reg_ग_लिखो(wm8350, WM8350_POWER_MGMT_1, pm1);

			/* disable antipop */
			wm8350_reg_ग_लिखो(wm8350, WM8350_ANTI_POP_CONTROL, 0);

		पूर्ण अन्यथा अणु
			/* turn on vmid 300k and reduce current */
			pm1 = wm8350_reg_पढ़ो(wm8350, WM8350_POWER_MGMT_1) &
			    ~(WM8350_VMID_MASK | WM8350_CODEC_ISEL_MASK);
			wm8350_reg_ग_लिखो(wm8350, WM8350_POWER_MGMT_1,
					 pm1 | WM8350_VMID_300K |
					 (platक्रमm->
					  codec_current_standby << 14));

		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:

		/* mute DAC & enable outमाला_दो */
		wm8350_set_bits(wm8350, WM8350_DAC_MUTE, WM8350_DAC_MUTE_ENA);

		wm8350_set_bits(wm8350, WM8350_POWER_MGMT_3,
				WM8350_OUT1L_ENA | WM8350_OUT1R_ENA |
				WM8350_OUT2L_ENA | WM8350_OUT2R_ENA);

		/* enable anti pop S curve */
		wm8350_reg_ग_लिखो(wm8350, WM8350_ANTI_POP_CONTROL,
				 (platक्रमm->vmid_s_curve << 8));

		/* turn off vmid  */
		pm1 = wm8350_reg_पढ़ो(wm8350, WM8350_POWER_MGMT_1) &
		    ~WM8350_VMIDEN;
		wm8350_reg_ग_लिखो(wm8350, WM8350_POWER_MGMT_1, pm1);

		/* रुको */
		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies
					       (platक्रमm->
						vmid_disअक्षरge_msecs));

		wm8350_reg_ग_लिखो(wm8350, WM8350_ANTI_POP_CONTROL,
				 (platक्रमm->vmid_s_curve << 8) |
				 platक्रमm->dis_out1 |
				 (platक्रमm->dis_out2 << 2) |
				 (platक्रमm->dis_out3 << 4) |
				 (platक्रमm->dis_out4 << 6));

		/* turn off VBuf and drain */
		pm1 = wm8350_reg_पढ़ो(wm8350, WM8350_POWER_MGMT_1) &
		    ~(WM8350_VBUFEN | WM8350_VMID_MASK);
		wm8350_reg_ग_लिखो(wm8350, WM8350_POWER_MGMT_1,
				 pm1 | WM8350_OUTPUT_DRAIN_EN);

		/* रुको */
		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies
					       (platक्रमm->drain_msecs));

		pm1 &= ~WM8350_BIASEN;
		wm8350_reg_ग_लिखो(wm8350, WM8350_POWER_MGMT_1, pm1);

		/* disable anti-pop */
		wm8350_reg_ग_लिखो(wm8350, WM8350_ANTI_POP_CONTROL, 0);

		wm8350_clear_bits(wm8350, WM8350_LOUT1_VOLUME,
				  WM8350_OUT1L_ENA);
		wm8350_clear_bits(wm8350, WM8350_ROUT1_VOLUME,
				  WM8350_OUT1R_ENA);
		wm8350_clear_bits(wm8350, WM8350_LOUT2_VOLUME,
				  WM8350_OUT2L_ENA);
		wm8350_clear_bits(wm8350, WM8350_ROUT2_VOLUME,
				  WM8350_OUT2R_ENA);

		/* disable घड़ी gen */
		wm8350_clear_bits(wm8350, WM8350_POWER_MGMT_4,
				  WM8350_SYSCLK_ENA);

		regulator_bulk_disable(ARRAY_SIZE(priv->supplies),
				       priv->supplies);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम wm8350_hp_work(काष्ठा wm8350_data *priv,
			   काष्ठा wm8350_jack_data *jack,
			   u16 mask)
अणु
	काष्ठा wm8350 *wm8350 = priv->wm8350;
	u16 reg;
	पूर्णांक report;

	reg = wm8350_reg_पढ़ो(wm8350, WM8350_JACK_PIN_STATUS);
	अगर (reg & mask)
		report = jack->report;
	अन्यथा
		report = 0;

	snd_soc_jack_report(jack->jack, report, jack->report);

पूर्ण

अटल व्योम wm8350_hpl_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wm8350_data *priv =
	    container_of(work, काष्ठा wm8350_data, hpl.work.work);

	wm8350_hp_work(priv, &priv->hpl, WM8350_JACK_L_LVL);
पूर्ण

अटल व्योम wm8350_hpr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wm8350_data *priv =
	    container_of(work, काष्ठा wm8350_data, hpr.work.work);
	
	wm8350_hp_work(priv, &priv->hpr, WM8350_JACK_R_LVL);
पूर्ण

अटल irqवापस_t wm8350_hpl_jack_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm8350_data *priv = data;
	काष्ठा wm8350 *wm8350 = priv->wm8350;

#अगर_अघोषित CONFIG_SND_SOC_WM8350_MODULE
	trace_snd_soc_jack_irq("WM8350 HPL");
#पूर्ण_अगर

	अगर (device_may_wakeup(wm8350->dev))
		pm_wakeup_event(wm8350->dev, 250);

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &priv->hpl.work, msecs_to_jअगरfies(200));

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wm8350_hpr_jack_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm8350_data *priv = data;
	काष्ठा wm8350 *wm8350 = priv->wm8350;

#अगर_अघोषित CONFIG_SND_SOC_WM8350_MODULE
	trace_snd_soc_jack_irq("WM8350 HPR");
#पूर्ण_अगर

	अगर (device_may_wakeup(wm8350->dev))
		pm_wakeup_event(wm8350->dev, 250);

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &priv->hpr.work, msecs_to_jअगरfies(200));

	वापस IRQ_HANDLED;
पूर्ण

/**
 * wm8350_hp_jack_detect - Enable headphone jack detection.
 *
 * @component:  WM8350 component
 * @which:  left or right jack detect संकेत
 * @jack:   jack to report detection events on
 * @report: value to report
 *
 * Enables the headphone jack detection of the WM8350.  If no report
 * is specअगरied then detection is disabled.
 */
पूर्णांक wm8350_hp_jack_detect(काष्ठा snd_soc_component *component, क्रमागत wm8350_jack which,
			  काष्ठा snd_soc_jack *jack, पूर्णांक report)
अणु
	काष्ठा wm8350_data *priv = snd_soc_component_get_drvdata(component);
	काष्ठा wm8350 *wm8350 = priv->wm8350;
	पूर्णांक ena;

	चयन (which) अणु
	हाल WM8350_JDL:
		priv->hpl.jack = jack;
		priv->hpl.report = report;
		ena = WM8350_JDL_ENA;
		अवरोध;

	हाल WM8350_JDR:
		priv->hpr.jack = jack;
		priv->hpr.report = report;
		ena = WM8350_JDR_ENA;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (report) अणु
		wm8350_set_bits(wm8350, WM8350_POWER_MGMT_4, WM8350_TOCLK_ENA);
		wm8350_set_bits(wm8350, WM8350_JACK_DETECT, ena);
	पूर्ण अन्यथा अणु
		wm8350_clear_bits(wm8350, WM8350_JACK_DETECT, ena);
	पूर्ण

	/* Sync status */
	चयन (which) अणु
	हाल WM8350_JDL:
		wm8350_hpl_jack_handler(0, priv);
		अवरोध;
	हाल WM8350_JDR:
		wm8350_hpr_jack_handler(0, priv);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_hp_jack_detect);

अटल irqवापस_t wm8350_mic_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm8350_data *priv = data;
	काष्ठा wm8350 *wm8350 = priv->wm8350;
	u16 reg;
	पूर्णांक report = 0;

#अगर_अघोषित CONFIG_SND_SOC_WM8350_MODULE
	trace_snd_soc_jack_irq("WM8350 mic");
#पूर्ण_अगर

	reg = wm8350_reg_पढ़ो(wm8350, WM8350_JACK_PIN_STATUS);
	अगर (reg & WM8350_JACK_MICSCD_LVL)
		report |= priv->mic.लघु_report;
	अगर (reg & WM8350_JACK_MICSD_LVL)
		report |= priv->mic.report;

	snd_soc_jack_report(priv->mic.jack, report,
			    priv->mic.report | priv->mic.लघु_report);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * wm8350_mic_jack_detect - Enable microphone jack detection.
 *
 * @component:         WM8350 component
 * @jack:          jack to report detection events on
 * @detect_report: value to report when presence detected
 * @लघु_report:  value to report when microphone लघु detected
 *
 * Enables the microphone jack detection of the WM8350.  If both reports
 * are specअगरied as zero then detection is disabled.
 */
पूर्णांक wm8350_mic_jack_detect(काष्ठा snd_soc_component *component,
			   काष्ठा snd_soc_jack *jack,
			   पूर्णांक detect_report, पूर्णांक लघु_report)
अणु
	काष्ठा wm8350_data *priv = snd_soc_component_get_drvdata(component);
	काष्ठा wm8350 *wm8350 = priv->wm8350;

	priv->mic.jack = jack;
	priv->mic.report = detect_report;
	priv->mic.लघु_report = लघु_report;

	अगर (detect_report || लघु_report) अणु
		wm8350_set_bits(wm8350, WM8350_POWER_MGMT_4, WM8350_TOCLK_ENA);
		wm8350_set_bits(wm8350, WM8350_POWER_MGMT_1,
				WM8350_MIC_DET_ENA);
	पूर्ण अन्यथा अणु
		wm8350_clear_bits(wm8350, WM8350_POWER_MGMT_1,
				  WM8350_MIC_DET_ENA);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_mic_jack_detect);

#घोषणा WM8350_RATES (SNDRV_PCM_RATE_8000_96000)

#घोषणा WM8350_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8350_dai_ops = अणु
	 .hw_params	= wm8350_pcm_hw_params,
	 .mute_stream	= wm8350_mute,
	 .set_fmt	= wm8350_set_dai_fmt,
	 .set_sysclk	= wm8350_set_dai_sysclk,
	 .set_pll	= wm8350_set_fll,
	 .set_clkभाग	= wm8350_set_clkभाग,
	 .no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8350_dai = अणु
	.name = "wm8350-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8350_RATES,
		.क्रमmats = WM8350_FORMATS,
	पूर्ण,
	.capture = अणु
		 .stream_name = "Capture",
		 .channels_min = 1,
		 .channels_max = 2,
		 .rates = WM8350_RATES,
		 .क्रमmats = WM8350_FORMATS,
	 पूर्ण,
	.ops = &wm8350_dai_ops,
पूर्ण;

अटल  पूर्णांक wm8350_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_platdata(component->dev);
	काष्ठा wm8350_data *priv;
	काष्ठा wm8350_output *out1;
	काष्ठा wm8350_output *out2;
	पूर्णांक ret, i;

	अगर (wm8350->codec.platक्रमm_data == शून्य) अणु
		dev_err(component->dev, "No audio platform data supplied\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(component->dev, माप(काष्ठा wm8350_data),
			    GFP_KERNEL);
	अगर (priv == शून्य)
		वापस -ENOMEM;

	snd_soc_component_init_regmap(component, wm8350->regmap);
	snd_soc_component_set_drvdata(component, priv);

	priv->wm8350 = wm8350;

	क्रम (i = 0; i < ARRAY_SIZE(supply_names); i++)
		priv->supplies[i].supply = supply_names[i];

	ret = devm_regulator_bulk_get(wm8350->dev, ARRAY_SIZE(priv->supplies),
				 priv->supplies);
	अगर (ret != 0)
		वापस ret;

	/* Put the codec पूर्णांकo reset अगर it wasn't alपढ़ोy */
	wm8350_clear_bits(wm8350, WM8350_POWER_MGMT_5, WM8350_CODEC_ENA);

	INIT_DELAYED_WORK(&priv->pga_work, wm8350_pga_work);
	INIT_DELAYED_WORK(&priv->hpl.work, wm8350_hpl_work);
	INIT_DELAYED_WORK(&priv->hpr.work, wm8350_hpr_work);

	/* Enable the codec */
	wm8350_set_bits(wm8350, WM8350_POWER_MGMT_5, WM8350_CODEC_ENA);

	/* Enable robust घड़ीing mode in ADC */
	snd_soc_component_ग_लिखो(component, WM8350_SECURITY, 0xa7);
	snd_soc_component_ग_लिखो(component, 0xde, 0x13);
	snd_soc_component_ग_लिखो(component, WM8350_SECURITY, 0);

	/* पढ़ो OUT1 & OUT2 volumes */
	out1 = &priv->out1;
	out2 = &priv->out2;
	out1->left_vol = (wm8350_reg_पढ़ो(wm8350, WM8350_LOUT1_VOLUME) &
			  WM8350_OUT1L_VOL_MASK) >> WM8350_OUT1L_VOL_SHIFT;
	out1->right_vol = (wm8350_reg_पढ़ो(wm8350, WM8350_ROUT1_VOLUME) &
			   WM8350_OUT1R_VOL_MASK) >> WM8350_OUT1R_VOL_SHIFT;
	out2->left_vol = (wm8350_reg_पढ़ो(wm8350, WM8350_LOUT2_VOLUME) &
			  WM8350_OUT2L_VOL_MASK) >> WM8350_OUT1L_VOL_SHIFT;
	out2->right_vol = (wm8350_reg_पढ़ो(wm8350, WM8350_ROUT2_VOLUME) &
			   WM8350_OUT2R_VOL_MASK) >> WM8350_OUT1R_VOL_SHIFT;
	wm8350_reg_ग_लिखो(wm8350, WM8350_LOUT1_VOLUME, 0);
	wm8350_reg_ग_लिखो(wm8350, WM8350_ROUT1_VOLUME, 0);
	wm8350_reg_ग_लिखो(wm8350, WM8350_LOUT2_VOLUME, 0);
	wm8350_reg_ग_लिखो(wm8350, WM8350_ROUT2_VOLUME, 0);

	/* Latch VU bits & mute */
	wm8350_set_bits(wm8350, WM8350_LOUT1_VOLUME,
			WM8350_OUT1_VU | WM8350_OUT1L_MUTE);
	wm8350_set_bits(wm8350, WM8350_LOUT2_VOLUME,
			WM8350_OUT2_VU | WM8350_OUT2L_MUTE);
	wm8350_set_bits(wm8350, WM8350_ROUT1_VOLUME,
			WM8350_OUT1_VU | WM8350_OUT1R_MUTE);
	wm8350_set_bits(wm8350, WM8350_ROUT2_VOLUME,
			WM8350_OUT2_VU | WM8350_OUT2R_MUTE);

	/* Make sure AIF tristating is disabled by शेष */
	wm8350_clear_bits(wm8350, WM8350_AI_FORMATING, WM8350_AIF_TRI);

	/* Make sure we've got a sane companding setup too */
	wm8350_clear_bits(wm8350, WM8350_ADC_DAC_COMP,
			  WM8350_DAC_COMP | WM8350_LOOPBACK);

	/* Make sure jack detect is disabled to start off with */
	wm8350_clear_bits(wm8350, WM8350_JACK_DETECT,
			  WM8350_JDL_ENA | WM8350_JDR_ENA);

	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_CODEC_JCK_DET_L,
			    wm8350_hpl_jack_handler, 0, "Left jack detect",
			    priv);
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_CODEC_JCK_DET_R,
			    wm8350_hpr_jack_handler, 0, "Right jack detect",
			    priv);
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_CODEC_MICSCD,
			    wm8350_mic_handler, 0, "Microphone short", priv);
	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_CODEC_MICD,
			    wm8350_mic_handler, 0, "Microphone detect", priv);

	वापस 0;
पूर्ण

अटल व्योम wm8350_component_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8350_data *priv = snd_soc_component_get_drvdata(component);
	काष्ठा wm8350 *wm8350 = dev_get_platdata(component->dev);

	wm8350_clear_bits(wm8350, WM8350_JACK_DETECT,
			  WM8350_JDL_ENA | WM8350_JDR_ENA);
	wm8350_clear_bits(wm8350, WM8350_POWER_MGMT_4, WM8350_TOCLK_ENA);

	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_CODEC_MICD, priv);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_CODEC_MICSCD, priv);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_CODEC_JCK_DET_L, priv);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_CODEC_JCK_DET_R, priv);

	priv->hpl.jack = शून्य;
	priv->hpr.jack = शून्य;
	priv->mic.jack = शून्य;

	cancel_delayed_work_sync(&priv->hpl.work);
	cancel_delayed_work_sync(&priv->hpr.work);

	/* अगर there was any work रुकोing then we run it now and
	 * रुको क्रम its completion */
	flush_delayed_work(&priv->pga_work);

	wm8350_clear_bits(wm8350, WM8350_POWER_MGMT_5, WM8350_CODEC_ENA);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8350 = अणु
	.probe			= wm8350_component_probe,
	.हटाओ			= wm8350_component_हटाओ,
	.set_bias_level		= wm8350_set_bias_level,
	.controls		= wm8350_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8350_snd_controls),
	.dapm_widमाला_लो		= wm8350_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8350_dapm_widमाला_लो),
	.dapm_routes		= wm8350_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8350_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक wm8350_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_wm8350,
			&wm8350_dai, 1);
पूर्ण

अटल काष्ठा platक्रमm_driver wm8350_codec_driver = अणु
	.driver = अणु
		   .name = "wm8350-codec",
		   पूर्ण,
	.probe = wm8350_probe,
पूर्ण;

module_platक्रमm_driver(wm8350_codec_driver);

MODULE_DESCRIPTION("ASoC WM8350 driver");
MODULE_AUTHOR("Liam Girdwood");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm8350-codec");
