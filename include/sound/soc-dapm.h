<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * linux/sound/soc-dapm.h -- ALSA SoC Dynamic Audio Power Management
 *
 * Author:	Liam Girdwood
 * Created:	Aug 11th 2005
 * Copyright:	Wolfson Microelectronics. PLC.
 */

#अगर_अघोषित __LINUX_SND_SOC_DAPM_H
#घोषणा __LINUX_SND_SOC_DAPM_H

#समावेश <linux/types.h>
#समावेश <sound/control.h>
#समावेश <sound/soc-topology.h>
#समावेश <sound/asoc.h>

काष्ठा device;
काष्ठा snd_soc_pcm_runसमय;
काष्ठा soc_क्रमागत;

/* widget has no PM रेजिस्टर bit */
#घोषणा SND_SOC_NOPM	-1

/*
 * SoC dynamic audio घातer management
 *
 * We can have up to 4 घातer करोमुख्यs
 *  1. Codec करोमुख्य - VREF, VMID
 *     Usually controlled at codec probe/हटाओ, although can be set
 *     at stream समय अगर घातer is not needed क्रम sidetone, etc.
 *  2. Platक्रमm/Machine करोमुख्य - physically connected inमाला_दो and outमाला_दो
 *     Is platक्रमm/machine and user action specअगरic, is set in the machine
 *     driver and by userspace e.g when HP are inserted
 *  3. Path करोमुख्य - Internal codec path mixers
 *     Are स्वतःmatically set when mixer and mux settings are
 *     changed by the user.
 *  4. Stream करोमुख्य - DAC's and ADC's.
 *     Enabled when stream playback/capture is started.
 */

/* codec करोमुख्य */
#घोषणा SND_SOC_DAPM_VMID(wname) \
अणु	.id = snd_soc_dapm_vmid, .name = wname, .kcontrol_news = शून्य, \
	.num_kcontrols = 0पूर्ण

/* platक्रमm करोमुख्य */
#घोषणा SND_SOC_DAPM_SIGGEN(wname) \
अणु	.id = snd_soc_dapm_siggen, .name = wname, .kcontrol_news = शून्य, \
	.num_kcontrols = 0, .reg = SND_SOC_NOPM पूर्ण
#घोषणा SND_SOC_DAPM_SINK(wname) \
अणु	.id = snd_soc_dapm_sink, .name = wname, .kcontrol_news = शून्य, \
	.num_kcontrols = 0, .reg = SND_SOC_NOPM पूर्ण
#घोषणा SND_SOC_DAPM_INPUT(wname) \
अणु	.id = snd_soc_dapm_input, .name = wname, .kcontrol_news = शून्य, \
	.num_kcontrols = 0, .reg = SND_SOC_NOPM पूर्ण
#घोषणा SND_SOC_DAPM_OUTPUT(wname) \
अणु	.id = snd_soc_dapm_output, .name = wname, .kcontrol_news = शून्य, \
	.num_kcontrols = 0, .reg = SND_SOC_NOPM पूर्ण
#घोषणा SND_SOC_DAPM_MIC(wname, wevent) \
अणु	.id = snd_soc_dapm_mic, .name = wname, .kcontrol_news = शून्य, \
	.num_kcontrols = 0, .reg = SND_SOC_NOPM, .event = wevent, \
	.event_flags = SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMDपूर्ण
#घोषणा SND_SOC_DAPM_HP(wname, wevent) \
अणु	.id = snd_soc_dapm_hp, .name = wname, .kcontrol_news = शून्य, \
	.num_kcontrols = 0, .reg = SND_SOC_NOPM, .event = wevent, \
	.event_flags = SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMDपूर्ण
#घोषणा SND_SOC_DAPM_SPK(wname, wevent) \
अणु	.id = snd_soc_dapm_spk, .name = wname, .kcontrol_news = शून्य, \
	.num_kcontrols = 0, .reg = SND_SOC_NOPM, .event = wevent, \
	.event_flags = SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMDपूर्ण
#घोषणा SND_SOC_DAPM_LINE(wname, wevent) \
अणु	.id = snd_soc_dapm_line, .name = wname, .kcontrol_news = शून्य, \
	.num_kcontrols = 0, .reg = SND_SOC_NOPM, .event = wevent, \
	.event_flags = SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMDपूर्ण

#घोषणा SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert) \
	.reg = wreg, .mask = 1, .shअगरt = wshअगरt, \
	.on_val = winvert ? 0 : 1, .off_val = winvert ? 1 : 0

/* path करोमुख्य */
#घोषणा SND_SOC_DAPM_PGA(wname, wreg, wshअगरt, winvert,\
	 wcontrols, wncontrols) \
अणु	.id = snd_soc_dapm_pga, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = wncontrolsपूर्ण
#घोषणा SND_SOC_DAPM_OUT_DRV(wname, wreg, wshअगरt, winvert,\
	 wcontrols, wncontrols) \
अणु	.id = snd_soc_dapm_out_drv, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = wncontrolsपूर्ण
#घोषणा SND_SOC_DAPM_MIXER(wname, wreg, wshअगरt, winvert, \
	 wcontrols, wncontrols)\
अणु	.id = snd_soc_dapm_mixer, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = wncontrolsपूर्ण
#घोषणा SND_SOC_DAPM_MIXER_NAMED_CTL(wname, wreg, wshअगरt, winvert, \
	 wcontrols, wncontrols)\
अणु       .id = snd_soc_dapm_mixer_named_ctl, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = wncontrolsपूर्ण
/* DEPRECATED: use SND_SOC_DAPM_SUPPLY */
#घोषणा SND_SOC_DAPM_MICBIAS(wname, wreg, wshअगरt, winvert) \
अणु	.id = snd_soc_dapm_micbias, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = शून्य, .num_kcontrols = 0पूर्ण
#घोषणा SND_SOC_DAPM_SWITCH(wname, wreg, wshअगरt, winvert, wcontrols) \
अणु	.id = snd_soc_dapm_चयन, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = 1पूर्ण
#घोषणा SND_SOC_DAPM_MUX(wname, wreg, wshअगरt, winvert, wcontrols) \
अणु	.id = snd_soc_dapm_mux, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = 1पूर्ण
#घोषणा SND_SOC_DAPM_DEMUX(wname, wreg, wshअगरt, winvert, wcontrols) \
अणु	.id = snd_soc_dapm_demux, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = 1पूर्ण

/* Simplअगरied versions of above macros, assuming wncontrols = ARRAY_SIZE(wcontrols) */
#घोषणा SOC_PGA_ARRAY(wname, wreg, wshअगरt, winvert,\
	 wcontrols) \
अणु	.id = snd_soc_dapm_pga, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = ARRAY_SIZE(wcontrols)पूर्ण
#घोषणा SOC_MIXER_ARRAY(wname, wreg, wshअगरt, winvert, \
	 wcontrols)\
अणु	.id = snd_soc_dapm_mixer, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = ARRAY_SIZE(wcontrols)पूर्ण
#घोषणा SOC_MIXER_NAMED_CTL_ARRAY(wname, wreg, wshअगरt, winvert, \
	 wcontrols)\
अणु       .id = snd_soc_dapm_mixer_named_ctl, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = ARRAY_SIZE(wcontrols)पूर्ण

/* path करोमुख्य with event - event handler must वापस 0 क्रम success */
#घोषणा SND_SOC_DAPM_PGA_E(wname, wreg, wshअगरt, winvert, wcontrols, \
	wncontrols, wevent, wflags) \
अणु	.id = snd_soc_dapm_pga, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = wncontrols, \
	.event = wevent, .event_flags = wflagsपूर्ण
#घोषणा SND_SOC_DAPM_OUT_DRV_E(wname, wreg, wshअगरt, winvert, wcontrols, \
	wncontrols, wevent, wflags) \
अणु	.id = snd_soc_dapm_out_drv, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = wncontrols, \
	.event = wevent, .event_flags = wflagsपूर्ण
#घोषणा SND_SOC_DAPM_MIXER_E(wname, wreg, wshअगरt, winvert, wcontrols, \
	wncontrols, wevent, wflags) \
अणु	.id = snd_soc_dapm_mixer, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = wncontrols, \
	.event = wevent, .event_flags = wflagsपूर्ण
#घोषणा SND_SOC_DAPM_MIXER_NAMED_CTL_E(wname, wreg, wshअगरt, winvert, \
	wcontrols, wncontrols, wevent, wflags) \
अणु       .id = snd_soc_dapm_mixer, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, \
	.num_kcontrols = wncontrols, .event = wevent, .event_flags = wflagsपूर्ण
#घोषणा SND_SOC_DAPM_SWITCH_E(wname, wreg, wshअगरt, winvert, wcontrols, \
	wevent, wflags) \
अणु	.id = snd_soc_dapm_चयन, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = 1, \
	.event = wevent, .event_flags = wflagsपूर्ण
#घोषणा SND_SOC_DAPM_MUX_E(wname, wreg, wshअगरt, winvert, wcontrols, \
	wevent, wflags) \
अणु	.id = snd_soc_dapm_mux, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = 1, \
	.event = wevent, .event_flags = wflagsपूर्ण

/* additional sequencing control within an event type */
#घोषणा SND_SOC_DAPM_PGA_S(wname, wsubseq, wreg, wshअगरt, winvert, \
	wevent, wflags) \
अणु	.id = snd_soc_dapm_pga, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.event = wevent, .event_flags = wflags, \
	.subseq = wsubseqपूर्ण
#घोषणा SND_SOC_DAPM_SUPPLY_S(wname, wsubseq, wreg, wshअगरt, winvert, wevent, \
	wflags)	\
अणु	.id = snd_soc_dapm_supply, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.event = wevent, .event_flags = wflags, .subseq = wsubseqपूर्ण

/* Simplअगरied versions of above macros, assuming wncontrols = ARRAY_SIZE(wcontrols) */
#घोषणा SOC_PGA_E_ARRAY(wname, wreg, wshअगरt, winvert, wcontrols, \
	wevent, wflags) \
अणु	.id = snd_soc_dapm_pga, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = ARRAY_SIZE(wcontrols), \
	.event = wevent, .event_flags = wflagsपूर्ण
#घोषणा SOC_MIXER_E_ARRAY(wname, wreg, wshअगरt, winvert, wcontrols, \
	wevent, wflags) \
अणु	.id = snd_soc_dapm_mixer, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = ARRAY_SIZE(wcontrols), \
	.event = wevent, .event_flags = wflagsपूर्ण
#घोषणा SOC_MIXER_NAMED_CTL_E_ARRAY(wname, wreg, wshअगरt, winvert, \
	wcontrols, wevent, wflags) \
अणु       .id = snd_soc_dapm_mixer, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.kcontrol_news = wcontrols, .num_kcontrols = ARRAY_SIZE(wcontrols), \
	.event = wevent, .event_flags = wflagsपूर्ण

/* events that are pre and post DAPM */
#घोषणा SND_SOC_DAPM_PRE(wname, wevent) \
अणु	.id = snd_soc_dapm_pre, .name = wname, .kcontrol_news = शून्य, \
	.num_kcontrols = 0, .reg = SND_SOC_NOPM, .event = wevent, \
	.event_flags = SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMDपूर्ण
#घोषणा SND_SOC_DAPM_POST(wname, wevent) \
अणु	.id = snd_soc_dapm_post, .name = wname, .kcontrol_news = शून्य, \
	.num_kcontrols = 0, .reg = SND_SOC_NOPM, .event = wevent, \
	.event_flags = SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMDपूर्ण

/* stream करोमुख्य */
#घोषणा SND_SOC_DAPM_AIF_IN(wname, stname, wchan, wreg, wshअगरt, winvert) \
अणु	.id = snd_soc_dapm_aअगर_in, .name = wname, .sname = stname, \
	.channel = wchan, SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), पूर्ण
#घोषणा SND_SOC_DAPM_AIF_IN_E(wname, stname, wchan, wreg, wshअगरt, winvert, \
			      wevent, wflags)				\
अणु	.id = snd_soc_dapm_aअगर_in, .name = wname, .sname = stname, \
	.channel = wchan, SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.event = wevent, .event_flags = wflags पूर्ण
#घोषणा SND_SOC_DAPM_AIF_OUT(wname, stname, wchan, wreg, wshअगरt, winvert) \
अणु	.id = snd_soc_dapm_aअगर_out, .name = wname, .sname = stname, \
	.channel = wchan, SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), पूर्ण
#घोषणा SND_SOC_DAPM_AIF_OUT_E(wname, stname, wchan, wreg, wshअगरt, winvert, \
			     wevent, wflags)				\
अणु	.id = snd_soc_dapm_aअगर_out, .name = wname, .sname = stname, \
	.channel = wchan, SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.event = wevent, .event_flags = wflags पूर्ण
#घोषणा SND_SOC_DAPM_DAC(wname, stname, wreg, wshअगरt, winvert) \
अणु	.id = snd_soc_dapm_dac, .name = wname, .sname = stname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert) पूर्ण
#घोषणा SND_SOC_DAPM_DAC_E(wname, stname, wreg, wshअगरt, winvert, \
			   wevent, wflags)				\
अणु	.id = snd_soc_dapm_dac, .name = wname, .sname = stname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.event = wevent, .event_flags = wflagsपूर्ण

#घोषणा SND_SOC_DAPM_ADC(wname, stname, wreg, wshअगरt, winvert) \
अणु	.id = snd_soc_dapm_adc, .name = wname, .sname = stname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), पूर्ण
#घोषणा SND_SOC_DAPM_ADC_E(wname, stname, wreg, wshअगरt, winvert, \
			   wevent, wflags)				\
अणु	.id = snd_soc_dapm_adc, .name = wname, .sname = stname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.event = wevent, .event_flags = wflagsपूर्ण
#घोषणा SND_SOC_DAPM_CLOCK_SUPPLY(wname) \
अणु	.id = snd_soc_dapm_घड़ी_supply, .name = wname, \
	.reg = SND_SOC_NOPM, .event = dapm_घड़ी_event, \
	.event_flags = SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD पूर्ण

/* generic widमाला_लो */
#घोषणा SND_SOC_DAPM_REG(wid, wname, wreg, wshअगरt, wmask, won_val, woff_val) \
अणु	.id = wid, .name = wname, .kcontrol_news = शून्य, .num_kcontrols = 0, \
	.reg = wreg, .shअगरt = wshअगरt, .mask = wmask, \
	.on_val = won_val, .off_val = woff_val, पूर्ण
#घोषणा SND_SOC_DAPM_SUPPLY(wname, wreg, wshअगरt, winvert, wevent, wflags) \
अणु	.id = snd_soc_dapm_supply, .name = wname, \
	SND_SOC_DAPM_INIT_REG_VAL(wreg, wshअगरt, winvert), \
	.event = wevent, .event_flags = wflagsपूर्ण
#घोषणा SND_SOC_DAPM_REGULATOR_SUPPLY(wname, wdelay, wflags)	    \
अणु	.id = snd_soc_dapm_regulator_supply, .name = wname, \
	.reg = SND_SOC_NOPM, .shअगरt = wdelay, .event = dapm_regulator_event, \
	.event_flags = SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD, \
	.on_val = wflagsपूर्ण
#घोषणा SND_SOC_DAPM_PINCTRL(wname, active, sleep) \
अणु	.id = snd_soc_dapm_pinctrl, .name = wname, \
	.priv = (&(काष्ठा snd_soc_dapm_pinctrl_priv) \
		अणु .active_state = active, .sleep_state = sleep,पूर्ण), \
	.reg = SND_SOC_NOPM, .event = dapm_pinctrl_event, \
	.event_flags = SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD पूर्ण



/* dapm kcontrol types */
#घोषणा SOC_DAPM_DOUBLE(xname, reg, lshअगरt, rshअगरt, max, invert) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_volsw, \
	.get = snd_soc_dapm_get_volsw, .put = snd_soc_dapm_put_volsw, \
	.निजी_value = SOC_DOUBLE_VALUE(reg, lshअगरt, rshअगरt, max, invert, 0) पूर्ण
#घोषणा SOC_DAPM_DOUBLE_R(xname, lreg, rreg, shअगरt, max, invert) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_volsw, \
	.get = snd_soc_dapm_get_volsw, .put = snd_soc_dapm_put_volsw, \
	.निजी_value = SOC_DOUBLE_R_VALUE(lreg, rreg, shअगरt, max, invert) पूर्ण
#घोषणा SOC_DAPM_SINGLE(xname, reg, shअगरt, max, invert) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_volsw, \
	.get = snd_soc_dapm_get_volsw, .put = snd_soc_dapm_put_volsw, \
	.निजी_value = SOC_SINGLE_VALUE(reg, shअगरt, max, invert, 0) पूर्ण
#घोषणा SOC_DAPM_SINGLE_AUTODISABLE(xname, reg, shअगरt, max, invert) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_volsw, \
	.get = snd_soc_dapm_get_volsw, .put = snd_soc_dapm_put_volsw, \
	.निजी_value = SOC_SINGLE_VALUE(reg, shअगरt, max, invert, 1) पूर्ण
#घोषणा SOC_DAPM_SINGLE_VIRT(xname, max) \
	SOC_DAPM_SINGLE(xname, SND_SOC_NOPM, 0, max, 0)
#घोषणा SOC_DAPM_SINGLE_TLV(xname, reg, shअगरt, max, invert, tlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_volsw, \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.tlv.p = (tlv_array), \
	.get = snd_soc_dapm_get_volsw, .put = snd_soc_dapm_put_volsw, \
	.निजी_value = SOC_SINGLE_VALUE(reg, shअगरt, max, invert, 0) पूर्ण
#घोषणा SOC_DAPM_SINGLE_TLV_AUTODISABLE(xname, reg, shअगरt, max, invert, tlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_volsw, \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.tlv.p = (tlv_array), \
	.get = snd_soc_dapm_get_volsw, .put = snd_soc_dapm_put_volsw, \
	.निजी_value = SOC_SINGLE_VALUE(reg, shअगरt, max, invert, 1) पूर्ण
#घोषणा SOC_DAPM_SINGLE_TLV_VIRT(xname, max, tlv_array) \
	SOC_DAPM_SINGLE(xname, SND_SOC_NOPM, 0, max, 0, tlv_array)
#घोषणा SOC_DAPM_ENUM(xname, xक्रमागत) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_क्रमागत_द्विगुन, \
 	.get = snd_soc_dapm_get_क्रमागत_द्विगुन, \
 	.put = snd_soc_dapm_put_क्रमागत_द्विगुन, \
  	.निजी_value = (अचिन्हित दीर्घ)&xक्रमागत पूर्ण
#घोषणा SOC_DAPM_ENUM_EXT(xname, xक्रमागत, xget, xput) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_क्रमागत_द्विगुन, \
	.get = xget, \
	.put = xput, \
	.निजी_value = (अचिन्हित दीर्घ)&xक्रमागत पूर्ण
#घोषणा SOC_DAPM_PIN_SWITCH(xname) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname " Switch", \
	.info = snd_soc_dapm_info_pin_चयन, \
	.get = snd_soc_dapm_get_pin_चयन, \
	.put = snd_soc_dapm_put_pin_चयन, \
	.निजी_value = (अचिन्हित दीर्घ)xname पूर्ण

/* dapm stream operations */
#घोषणा SND_SOC_DAPM_STREAM_NOP			0x0
#घोषणा SND_SOC_DAPM_STREAM_START		0x1
#घोषणा SND_SOC_DAPM_STREAM_STOP		0x2
#घोषणा SND_SOC_DAPM_STREAM_SUSPEND		0x4
#घोषणा SND_SOC_DAPM_STREAM_RESUME		0x8
#घोषणा SND_SOC_DAPM_STREAM_PAUSE_PUSH	0x10
#घोषणा SND_SOC_DAPM_STREAM_PAUSE_RELEASE	0x20

/* dapm event types */
#घोषणा SND_SOC_DAPM_PRE_PMU	0x1 	/* beक्रमe widget घातer up */
#घोषणा SND_SOC_DAPM_POST_PMU	0x2		/* after widget घातer up */
#घोषणा SND_SOC_DAPM_PRE_PMD	0x4 	/* beक्रमe widget घातer करोwn */
#घोषणा SND_SOC_DAPM_POST_PMD	0x8		/* after widget घातer करोwn */
#घोषणा SND_SOC_DAPM_PRE_REG	0x10	/* beक्रमe audio path setup */
#घोषणा SND_SOC_DAPM_POST_REG	0x20	/* after audio path setup */
#घोषणा SND_SOC_DAPM_WILL_PMU   0x40    /* called at start of sequence */
#घोषणा SND_SOC_DAPM_WILL_PMD   0x80    /* called at start of sequence */
#घोषणा SND_SOC_DAPM_PRE_POST_PMD \
				(SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD)
#घोषणा SND_SOC_DAPM_PRE_POST_PMU \
				(SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU)

/* convenience event type detection */
#घोषणा SND_SOC_DAPM_EVENT_ON(e)	\
	(e & (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU))
#घोषणा SND_SOC_DAPM_EVENT_OFF(e)	\
	(e & (SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD))

/* regulator widget flags */
#घोषणा SND_SOC_DAPM_REGULATOR_BYPASS     0x1     /* bypass when disabled */

काष्ठा snd_soc_dapm_widget;
क्रमागत snd_soc_dapm_type;
काष्ठा snd_soc_dapm_path;
काष्ठा snd_soc_dapm_pin;
काष्ठा snd_soc_dapm_route;
काष्ठा snd_soc_dapm_context;
काष्ठा regulator;
काष्ठा snd_soc_dapm_widget_list;
काष्ठा snd_soc_dapm_update;
क्रमागत snd_soc_dapm_direction;

/*
 * Bias levels
 *
 * @ON:      Bias is fully on क्रम audio playback and capture operations.
 * @PREPARE: Prepare क्रम audio operations. Called beक्रमe DAPM चयनing क्रम
 *           stream start and stop operations.
 * @STANDBY: Low घातer standby state when no playback/capture operations are
 *           in progress. NOTE: The transition समय between STANDBY and ON
 *           should be as fast as possible and no दीर्घer than 10ms.
 * @OFF:     Power Off. No restrictions on transition बार.
 */
क्रमागत snd_soc_bias_level अणु
	SND_SOC_BIAS_OFF = 0,
	SND_SOC_BIAS_STANDBY = 1,
	SND_SOC_BIAS_PREPARE = 2,
	SND_SOC_BIAS_ON = 3,
पूर्ण;

पूर्णांक dapm_regulator_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);
पूर्णांक dapm_घड़ी_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);
पूर्णांक dapm_pinctrl_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);

/* dapm controls */
पूर्णांक snd_soc_dapm_put_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_dapm_get_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_dapm_get_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_dapm_put_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_dapm_info_pin_चयन(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo);
पूर्णांक snd_soc_dapm_get_pin_चयन(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *uncontrol);
पूर्णांक snd_soc_dapm_put_pin_चयन(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *uncontrol);
पूर्णांक snd_soc_dapm_new_controls(काष्ठा snd_soc_dapm_context *dapm,
	स्थिर काष्ठा snd_soc_dapm_widget *widget,
	पूर्णांक num);
काष्ठा snd_soc_dapm_widget *snd_soc_dapm_new_control(
		काष्ठा snd_soc_dapm_context *dapm,
		स्थिर काष्ठा snd_soc_dapm_widget *widget);
काष्ठा snd_soc_dapm_widget *snd_soc_dapm_new_control_unlocked(
		काष्ठा snd_soc_dapm_context *dapm,
		स्थिर काष्ठा snd_soc_dapm_widget *widget);
पूर्णांक snd_soc_dapm_new_dai_widमाला_लो(काष्ठा snd_soc_dapm_context *dapm,
				 काष्ठा snd_soc_dai *dai);
पूर्णांक snd_soc_dapm_link_dai_widमाला_लो(काष्ठा snd_soc_card *card);
व्योम snd_soc_dapm_connect_dai_link_widमाला_लो(काष्ठा snd_soc_card *card);

पूर्णांक snd_soc_dapm_update_dai(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai);

/* dapm path setup */
पूर्णांक snd_soc_dapm_new_widमाला_लो(काष्ठा snd_soc_card *card);
व्योम snd_soc_dapm_मुक्त(काष्ठा snd_soc_dapm_context *dapm);
व्योम snd_soc_dapm_init(काष्ठा snd_soc_dapm_context *dapm,
		       काष्ठा snd_soc_card *card,
		       काष्ठा snd_soc_component *component);
पूर्णांक snd_soc_dapm_add_routes(काष्ठा snd_soc_dapm_context *dapm,
			    स्थिर काष्ठा snd_soc_dapm_route *route, पूर्णांक num);
पूर्णांक snd_soc_dapm_del_routes(काष्ठा snd_soc_dapm_context *dapm,
			    स्थिर काष्ठा snd_soc_dapm_route *route, पूर्णांक num);
पूर्णांक snd_soc_dapm_weak_routes(काष्ठा snd_soc_dapm_context *dapm,
			     स्थिर काष्ठा snd_soc_dapm_route *route, पूर्णांक num);
व्योम snd_soc_dapm_मुक्त_widget(काष्ठा snd_soc_dapm_widget *w);
व्योम snd_soc_dapm_reset_cache(काष्ठा snd_soc_dapm_context *dapm);

/* dapm events */
व्योम snd_soc_dapm_stream_event(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक stream,
	पूर्णांक event);
व्योम snd_soc_dapm_stream_stop(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक stream);
व्योम snd_soc_dapm_shutकरोwn(काष्ठा snd_soc_card *card);

/* बाह्यal DAPM widget events */
पूर्णांक snd_soc_dapm_mixer_update_घातer(काष्ठा snd_soc_dapm_context *dapm,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक connect,
		काष्ठा snd_soc_dapm_update *update);
पूर्णांक snd_soc_dapm_mux_update_घातer(काष्ठा snd_soc_dapm_context *dapm,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक mux, काष्ठा soc_क्रमागत *e,
		काष्ठा snd_soc_dapm_update *update);

/* dapm sys fs - used by the core */
बाह्य काष्ठा attribute *soc_dapm_dev_attrs[];
व्योम snd_soc_dapm_debugfs_init(काष्ठा snd_soc_dapm_context *dapm,
				काष्ठा dentry *parent);

/* dapm audio pin control and status */
पूर्णांक snd_soc_dapm_enable_pin(काष्ठा snd_soc_dapm_context *dapm,
			    स्थिर अक्षर *pin);
पूर्णांक snd_soc_dapm_enable_pin_unlocked(काष्ठा snd_soc_dapm_context *dapm,
				     स्थिर अक्षर *pin);
पूर्णांक snd_soc_dapm_disable_pin(काष्ठा snd_soc_dapm_context *dapm,
			     स्थिर अक्षर *pin);
पूर्णांक snd_soc_dapm_disable_pin_unlocked(काष्ठा snd_soc_dapm_context *dapm,
				      स्थिर अक्षर *pin);
पूर्णांक snd_soc_dapm_nc_pin(काष्ठा snd_soc_dapm_context *dapm, स्थिर अक्षर *pin);
पूर्णांक snd_soc_dapm_nc_pin_unlocked(काष्ठा snd_soc_dapm_context *dapm,
				 स्थिर अक्षर *pin);
पूर्णांक snd_soc_dapm_get_pin_status(काष्ठा snd_soc_dapm_context *dapm,
				स्थिर अक्षर *pin);
पूर्णांक snd_soc_dapm_sync(काष्ठा snd_soc_dapm_context *dapm);
पूर्णांक snd_soc_dapm_sync_unlocked(काष्ठा snd_soc_dapm_context *dapm);
पूर्णांक snd_soc_dapm_क्रमce_enable_pin(काष्ठा snd_soc_dapm_context *dapm,
				  स्थिर अक्षर *pin);
पूर्णांक snd_soc_dapm_क्रमce_enable_pin_unlocked(काष्ठा snd_soc_dapm_context *dapm,
					   स्थिर अक्षर *pin);
पूर्णांक snd_soc_dapm_ignore_suspend(काष्ठा snd_soc_dapm_context *dapm,
				स्थिर अक्षर *pin);
अचिन्हित पूर्णांक dapm_kcontrol_get_value(स्थिर काष्ठा snd_kcontrol *kcontrol);

/* Mostly पूर्णांकernal - should not normally be used */
व्योम dapm_mark_endpoपूर्णांकs_dirty(काष्ठा snd_soc_card *card);

/* dapm path query */
पूर्णांक snd_soc_dapm_dai_get_connected_widमाला_लो(काष्ठा snd_soc_dai *dai, पूर्णांक stream,
	काष्ठा snd_soc_dapm_widget_list **list,
	bool (*custom_stop_condition)(काष्ठा snd_soc_dapm_widget *,
				      क्रमागत snd_soc_dapm_direction));
व्योम snd_soc_dapm_dai_मुक्त_widमाला_लो(काष्ठा snd_soc_dapm_widget_list **list);

काष्ठा snd_soc_dapm_context *snd_soc_dapm_kcontrol_dapm(
	काष्ठा snd_kcontrol *kcontrol);

काष्ठा snd_soc_dapm_widget *snd_soc_dapm_kcontrol_widget(
		काष्ठा snd_kcontrol *kcontrol);

पूर्णांक snd_soc_dapm_क्रमce_bias_level(काष्ठा snd_soc_dapm_context *dapm,
	क्रमागत snd_soc_bias_level level);

/* dapm widget types */
क्रमागत snd_soc_dapm_type अणु
	snd_soc_dapm_input = 0,		/* input pin */
	snd_soc_dapm_output,		/* output pin */
	snd_soc_dapm_mux,			/* selects 1 analog संकेत from many inमाला_दो */
	snd_soc_dapm_demux,			/* connects the input to one of multiple outमाला_दो */
	snd_soc_dapm_mixer,			/* mixes several analog संकेतs together */
	snd_soc_dapm_mixer_named_ctl,		/* mixer with named controls */
	snd_soc_dapm_pga,			/* programmable gain/attenuation (volume) */
	snd_soc_dapm_out_drv,			/* output driver */
	snd_soc_dapm_adc,			/* analog to digital converter */
	snd_soc_dapm_dac,			/* digital to analog converter */
	snd_soc_dapm_micbias,		/* microphone bias (घातer) - DEPRECATED: use snd_soc_dapm_supply */
	snd_soc_dapm_mic,			/* microphone */
	snd_soc_dapm_hp,			/* headphones */
	snd_soc_dapm_spk,			/* speaker */
	snd_soc_dapm_line,			/* line input/output */
	snd_soc_dapm_चयन,		/* analog चयन */
	snd_soc_dapm_vmid,			/* codec bias/vmid - to minimise pops */
	snd_soc_dapm_pre,			/* machine specअगरic pre widget - exec first */
	snd_soc_dapm_post,			/* machine specअगरic post widget - exec last */
	snd_soc_dapm_supply,		/* घातer/घड़ी supply */
	snd_soc_dapm_pinctrl,		/* pinctrl */
	snd_soc_dapm_regulator_supply,	/* बाह्यal regulator */
	snd_soc_dapm_घड़ी_supply,	/* बाह्यal घड़ी */
	snd_soc_dapm_aअगर_in,		/* audio पूर्णांकerface input */
	snd_soc_dapm_aअगर_out,		/* audio पूर्णांकerface output */
	snd_soc_dapm_siggen,		/* संकेत generator */
	snd_soc_dapm_sink,
	snd_soc_dapm_dai_in,		/* link to DAI काष्ठाure */
	snd_soc_dapm_dai_out,
	snd_soc_dapm_dai_link,		/* link between two DAI काष्ठाures */
	snd_soc_dapm_kcontrol,		/* Auto-disabled kcontrol */
	snd_soc_dapm_buffer,		/* DSP/CODEC पूर्णांकernal buffer */
	snd_soc_dapm_scheduler,		/* DSP/CODEC पूर्णांकernal scheduler */
	snd_soc_dapm_effect,		/* DSP/CODEC effect component */
	snd_soc_dapm_src,		/* DSP/CODEC SRC component */
	snd_soc_dapm_asrc,		/* DSP/CODEC ASRC component */
	snd_soc_dapm_encoder,		/* FW/SW audio encoder component */
	snd_soc_dapm_decoder,		/* FW/SW audio decoder component */

	/* Don't edit below this line */
	SND_SOC_DAPM_TYPE_COUNT
पूर्ण;

क्रमागत snd_soc_dapm_subclass अणु
	SND_SOC_DAPM_CLASS_INIT		= 0,
	SND_SOC_DAPM_CLASS_RUNTIME	= 1,
पूर्ण;

/*
 * DAPM audio route definition.
 *
 * Defines an audio route originating at source via control and finishing
 * at sink.
 */
काष्ठा snd_soc_dapm_route अणु
	स्थिर अक्षर *sink;
	स्थिर अक्षर *control;
	स्थिर अक्षर *source;

	/* Note: currently only supported क्रम links where source is a supply */
	पूर्णांक (*connected)(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink);

	काष्ठा snd_soc_करोbj करोbj;
पूर्ण;

/* dapm audio path between two widमाला_लो */
काष्ठा snd_soc_dapm_path अणु
	स्थिर अक्षर *name;

	/*
	 * source (input) and sink (output) widमाला_लो
	 * The जोड़ is क्रम convience, since it is a lot nicer to type
	 * p->source, rather than p->node[SND_SOC_DAPM_सूची_IN]
	 */
	जोड़ अणु
		काष्ठा अणु
			काष्ठा snd_soc_dapm_widget *source;
			काष्ठा snd_soc_dapm_widget *sink;
		पूर्ण;
		काष्ठा snd_soc_dapm_widget *node[2];
	पूर्ण;

	/* status */
	u32 connect:1;	/* source and sink widमाला_लो are connected */
	u32 walking:1;  /* path is in the process of being walked */
	u32 weak:1;	/* path ignored क्रम घातer management */
	u32 is_supply:1;	/* At least one of the connected widमाला_लो is a supply */

	पूर्णांक (*connected)(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink);

	काष्ठा list_head list_node[2];
	काष्ठा list_head list_kcontrol;
	काष्ठा list_head list;
पूर्ण;

/* dapm widget */
काष्ठा snd_soc_dapm_widget अणु
	क्रमागत snd_soc_dapm_type id;
	स्थिर अक्षर *name;		/* widget name */
	स्थिर अक्षर *sname;	/* stream name */
	काष्ठा list_head list;
	काष्ठा snd_soc_dapm_context *dapm;

	व्योम *priv;				/* widget specअगरic data */
	काष्ठा regulator *regulator;		/* attached regulator */
	काष्ठा pinctrl *pinctrl;		/* attached pinctrl */

	/* dapm control */
	पूर्णांक reg;				/* negative reg = no direct dapm */
	अचिन्हित अक्षर shअगरt;			/* bits to shअगरt */
	अचिन्हित पूर्णांक mask;			/* non-shअगरted mask */
	अचिन्हित पूर्णांक on_val;			/* on state value */
	अचिन्हित पूर्णांक off_val;			/* off state value */
	अचिन्हित अक्षर घातer:1;			/* block घातer status */
	अचिन्हित अक्षर active:1;			/* active stream on DAC, ADC's */
	अचिन्हित अक्षर connected:1;		/* connected codec pin */
	अचिन्हित अक्षर new:1;			/* cnew complete */
	अचिन्हित अक्षर क्रमce:1;			/* क्रमce state */
	अचिन्हित अक्षर ignore_suspend:1;         /* kept enabled over suspend */
	अचिन्हित अक्षर new_घातer:1;		/* घातer from this run */
	अचिन्हित अक्षर घातer_checked:1;		/* घातer checked this run */
	अचिन्हित अक्षर is_supply:1;		/* Widget is a supply type widget */
	अचिन्हित अक्षर is_ep:2;			/* Widget is a endpoपूर्णांक type widget */
	पूर्णांक subseq;				/* sort within widget type */

	पूर्णांक (*घातer_check)(काष्ठा snd_soc_dapm_widget *w);

	/* बाह्यal events */
	अचिन्हित लघु event_flags;		/* flags to specअगरy event types */
	पूर्णांक (*event)(काष्ठा snd_soc_dapm_widget*, काष्ठा snd_kcontrol *, पूर्णांक);

	/* kcontrols that relate to this widget */
	पूर्णांक num_kcontrols;
	स्थिर काष्ठा snd_kcontrol_new *kcontrol_news;
	काष्ठा snd_kcontrol **kcontrols;
	काष्ठा snd_soc_करोbj करोbj;

	/* widget input and output edges */
	काष्ठा list_head edges[2];

	/* used during DAPM updates */
	काष्ठा list_head work_list;
	काष्ठा list_head घातer_list;
	काष्ठा list_head dirty;
	पूर्णांक endpoपूर्णांकs[2];

	काष्ठा clk *clk;

	पूर्णांक channel;
पूर्ण;

काष्ठा snd_soc_dapm_update अणु
	काष्ठा snd_kcontrol *kcontrol;
	पूर्णांक reg;
	पूर्णांक mask;
	पूर्णांक val;
	पूर्णांक reg2;
	पूर्णांक mask2;
	पूर्णांक val2;
	bool has_second_set;
पूर्ण;

काष्ठा snd_soc_dapm_wcache अणु
	काष्ठा snd_soc_dapm_widget *widget;
पूर्ण;

/* DAPM context */
काष्ठा snd_soc_dapm_context अणु
	क्रमागत snd_soc_bias_level bias_level;
	अचिन्हित पूर्णांक idle_bias_off:1; /* Use BIAS_OFF instead of STANDBY */
	/* Go to BIAS_OFF in suspend अगर the DAPM context is idle */
	अचिन्हित पूर्णांक suspend_bias_off:1;

	काष्ठा device *dev; /* from parent - क्रम debug */
	काष्ठा snd_soc_component *component; /* parent component */
	काष्ठा snd_soc_card *card; /* parent card */

	/* used during DAPM updates */
	क्रमागत snd_soc_bias_level target_bias_level;
	काष्ठा list_head list;

	काष्ठा snd_soc_dapm_wcache path_sink_cache;
	काष्ठा snd_soc_dapm_wcache path_source_cache;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_dapm;
#पूर्ण_अगर
पूर्ण;

/* A list of widमाला_लो associated with an object, typically a snd_kcontrol */
काष्ठा snd_soc_dapm_widget_list अणु
	पूर्णांक num_widमाला_लो;
	काष्ठा snd_soc_dapm_widget *widमाला_लो[];
पूर्ण;

#घोषणा क्रम_each_dapm_widमाला_लो(list, i, widget)				\
	क्रम ((i) = 0;							\
	     (i) < list->num_widमाला_लो && (widget = list->widमाला_लो[i]);	\
	     (i)++)

काष्ठा snd_soc_dapm_stats अणु
	पूर्णांक घातer_checks;
	पूर्णांक path_checks;
	पूर्णांक neighbour_checks;
पूर्ण;

काष्ठा snd_soc_dapm_pinctrl_priv अणु
	स्थिर अक्षर *active_state;
	स्थिर अक्षर *sleep_state;
पूर्ण;

/**
 * snd_soc_dapm_init_bias_level() - Initialize DAPM bias level
 * @dapm: The DAPM context to initialize
 * @level: The DAPM level to initialize to
 *
 * This function only sets the driver पूर्णांकernal state of the DAPM level and will
 * not modअगरy the state of the device. Hence it should not be used during normal
 * operation, but only to synchronize the पूर्णांकernal state to the device state.
 * E.g. during driver probe to set the DAPM level to the one corresponding with
 * the घातer-on reset state of the device.
 *
 * To change the DAPM state of the device use snd_soc_dapm_set_bias_level().
 */
अटल अंतरभूत व्योम snd_soc_dapm_init_bias_level(
	काष्ठा snd_soc_dapm_context *dapm, क्रमागत snd_soc_bias_level level)
अणु
	dapm->bias_level = level;
पूर्ण

/**
 * snd_soc_dapm_get_bias_level() - Get current DAPM bias level
 * @dapm: The context क्रम which to get the bias level
 *
 * Returns: The current bias level of the passed DAPM context.
 */
अटल अंतरभूत क्रमागत snd_soc_bias_level snd_soc_dapm_get_bias_level(
	काष्ठा snd_soc_dapm_context *dapm)
अणु
	वापस dapm->bias_level;
पूर्ण

क्रमागत snd_soc_dapm_direction अणु
	SND_SOC_DAPM_सूची_IN,
	SND_SOC_DAPM_सूची_OUT
पूर्ण;

#घोषणा SND_SOC_DAPM_सूची_TO_EP(x) BIT(x)

#घोषणा SND_SOC_DAPM_EP_SOURCE SND_SOC_DAPM_सूची_TO_EP(SND_SOC_DAPM_सूची_IN)
#घोषणा SND_SOC_DAPM_EP_SINK SND_SOC_DAPM_सूची_TO_EP(SND_SOC_DAPM_सूची_OUT)

/**
 * snd_soc_dapm_widget_क्रम_each_sink_path - Iterates over all paths in the
 *   specअगरied direction of a widget
 * @w: The widget
 * @dir: Whether to iterate over the paths where the specअगरied widget is the
 *       incoming or outgoing widमाला_लो
 * @p: The path iterator variable
 */
#घोषणा snd_soc_dapm_widget_क्रम_each_path(w, dir, p) \
	list_क्रम_each_entry(p, &w->edges[dir], list_node[dir])

/**
 * snd_soc_dapm_widget_क्रम_each_sink_path_safe - Iterates over all paths in the
 *   specअगरied direction of a widget
 * @w: The widget
 * @dir: Whether to iterate over the paths where the specअगरied widget is the
 *       incoming or outgoing widमाला_लो
 * @p: The path iterator variable
 * @next_p: Temporary storage क्रम the next path
 *
 *  This function works like snd_soc_dapm_widget_क्रम_each_sink_path, expect that
 *  it is safe to हटाओ the current path from the list जबतक iterating
 */
#घोषणा snd_soc_dapm_widget_क्रम_each_path_safe(w, dir, p, next_p) \
	list_क्रम_each_entry_safe(p, next_p, &w->edges[dir], list_node[dir])

/**
 * snd_soc_dapm_widget_क्रम_each_sink_path - Iterates over all paths leaving a
 *  widget
 * @w: The widget
 * @p: The path iterator variable
 */
#घोषणा snd_soc_dapm_widget_क्रम_each_sink_path(w, p) \
	snd_soc_dapm_widget_क्रम_each_path(w, SND_SOC_DAPM_सूची_IN, p)

/**
 * snd_soc_dapm_widget_क्रम_each_source_path - Iterates over all paths leading to
 *  a widget
 * @w: The widget
 * @p: The path iterator variable
 */
#घोषणा snd_soc_dapm_widget_क्रम_each_source_path(w, p) \
	snd_soc_dapm_widget_क्रम_each_path(w, SND_SOC_DAPM_सूची_OUT, p)

#पूर्ण_अगर
