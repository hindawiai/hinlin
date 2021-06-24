<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	cपंचांगixer.c
 *
 * @Brief
 * This file contains the implementation of alsa mixer device functions.
 *
 * @Author	Liu Chun
 * @Date 	May 28 2008
 */


#समावेश "ctmixer.h"
#समावेश "ctamixer.h"
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/pcm.h>
#समावेश <sound/tlv.h>

क्रमागत CT_SUM_CTL अणु
	SUM_IN_F,
	SUM_IN_R,
	SUM_IN_C,
	SUM_IN_S,
	SUM_IN_F_C,

	NUM_CT_SUMS
पूर्ण;

क्रमागत CT_AMIXER_CTL अणु
	/* volume control mixers */
	AMIXER_MASTER_F,
	AMIXER_MASTER_R,
	AMIXER_MASTER_C,
	AMIXER_MASTER_S,
	AMIXER_PCM_F,
	AMIXER_PCM_R,
	AMIXER_PCM_C,
	AMIXER_PCM_S,
	AMIXER_SPDIFI,
	AMIXER_LINEIN,
	AMIXER_MIC,
	AMIXER_SPDIFO,
	AMIXER_WAVE_F,
	AMIXER_WAVE_R,
	AMIXER_WAVE_C,
	AMIXER_WAVE_S,
	AMIXER_MASTER_F_C,
	AMIXER_PCM_F_C,
	AMIXER_SPDIFI_C,
	AMIXER_LINEIN_C,
	AMIXER_MIC_C,

	/* this should always be the last one */
	NUM_CT_AMIXERS
पूर्ण;

क्रमागत CTALSA_MIXER_CTL अणु
	/* volume control mixers */
	MIXER_MASTER_P,
	MIXER_PCM_P,
	MIXER_LINEIN_P,
	MIXER_MIC_P,
	MIXER_SPDIFI_P,
	MIXER_SPDIFO_P,
	MIXER_WAVEF_P,
	MIXER_WAVER_P,
	MIXER_WAVEC_P,
	MIXER_WAVES_P,
	MIXER_MASTER_C,
	MIXER_PCM_C,
	MIXER_LINEIN_C,
	MIXER_MIC_C,
	MIXER_SPDIFI_C,

	/* चयन control mixers */
	MIXER_PCM_C_S,
	MIXER_LINEIN_C_S,
	MIXER_MIC_C_S,
	MIXER_SPDIFI_C_S,
	MIXER_SPDIFO_P_S,
	MIXER_WAVEF_P_S,
	MIXER_WAVER_P_S,
	MIXER_WAVEC_P_S,
	MIXER_WAVES_P_S,
	MIXER_DIGITAL_IO_S,
	MIXER_IEC958_MASK,
	MIXER_IEC958_DEFAULT,
	MIXER_IEC958_STREAM,

	/* this should always be the last one */
	NUM_CTALSA_MIXERS
पूर्ण;

#घोषणा VOL_MIXER_START		MIXER_MASTER_P
#घोषणा VOL_MIXER_END		MIXER_SPDIFI_C
#घोषणा VOL_MIXER_NUM		(VOL_MIXER_END - VOL_MIXER_START + 1)
#घोषणा SWH_MIXER_START		MIXER_PCM_C_S
#घोषणा SWH_MIXER_END		MIXER_DIGITAL_IO_S
#घोषणा SWH_CAPTURE_START	MIXER_PCM_C_S
#घोषणा SWH_CAPTURE_END		MIXER_SPDIFI_C_S

#घोषणा CHN_NUM		2

काष्ठा ct_kcontrol_init अणु
	अचिन्हित अक्षर ctl;
	अक्षर *name;
पूर्ण;

अटल काष्ठा ct_kcontrol_init
ct_kcontrol_init_table[NUM_CTALSA_MIXERS] = अणु
	[MIXER_MASTER_P] = अणु
		.ctl = 1,
		.name = "Master Playback Volume",
	पूर्ण,
	[MIXER_MASTER_C] = अणु
		.ctl = 1,
		.name = "Master Capture Volume",
	पूर्ण,
	[MIXER_PCM_P] = अणु
		.ctl = 1,
		.name = "PCM Playback Volume",
	पूर्ण,
	[MIXER_PCM_C] = अणु
		.ctl = 1,
		.name = "PCM Capture Volume",
	पूर्ण,
	[MIXER_LINEIN_P] = अणु
		.ctl = 1,
		.name = "Line Playback Volume",
	पूर्ण,
	[MIXER_LINEIN_C] = अणु
		.ctl = 1,
		.name = "Line Capture Volume",
	पूर्ण,
	[MIXER_MIC_P] = अणु
		.ctl = 1,
		.name = "Mic Playback Volume",
	पूर्ण,
	[MIXER_MIC_C] = अणु
		.ctl = 1,
		.name = "Mic Capture Volume",
	पूर्ण,
	[MIXER_SPDIFI_P] = अणु
		.ctl = 1,
		.name = "IEC958 Playback Volume",
	पूर्ण,
	[MIXER_SPDIFI_C] = अणु
		.ctl = 1,
		.name = "IEC958 Capture Volume",
	पूर्ण,
	[MIXER_SPDIFO_P] = अणु
		.ctl = 1,
		.name = "Digital Playback Volume",
	पूर्ण,
	[MIXER_WAVEF_P] = अणु
		.ctl = 1,
		.name = "Front Playback Volume",
	पूर्ण,
	[MIXER_WAVES_P] = अणु
		.ctl = 1,
		.name = "Side Playback Volume",
	पूर्ण,
	[MIXER_WAVEC_P] = अणु
		.ctl = 1,
		.name = "Center/LFE Playback Volume",
	पूर्ण,
	[MIXER_WAVER_P] = अणु
		.ctl = 1,
		.name = "Surround Playback Volume",
	पूर्ण,
	[MIXER_PCM_C_S] = अणु
		.ctl = 1,
		.name = "PCM Capture Switch",
	पूर्ण,
	[MIXER_LINEIN_C_S] = अणु
		.ctl = 1,
		.name = "Line Capture Switch",
	पूर्ण,
	[MIXER_MIC_C_S] = अणु
		.ctl = 1,
		.name = "Mic Capture Switch",
	पूर्ण,
	[MIXER_SPDIFI_C_S] = अणु
		.ctl = 1,
		.name = "IEC958 Capture Switch",
	पूर्ण,
	[MIXER_SPDIFO_P_S] = अणु
		.ctl = 1,
		.name = "Digital Playback Switch",
	पूर्ण,
	[MIXER_WAVEF_P_S] = अणु
		.ctl = 1,
		.name = "Front Playback Switch",
	पूर्ण,
	[MIXER_WAVES_P_S] = अणु
		.ctl = 1,
		.name = "Side Playback Switch",
	पूर्ण,
	[MIXER_WAVEC_P_S] = अणु
		.ctl = 1,
		.name = "Center/LFE Playback Switch",
	पूर्ण,
	[MIXER_WAVER_P_S] = अणु
		.ctl = 1,
		.name = "Surround Playback Switch",
	पूर्ण,
	[MIXER_DIGITAL_IO_S] = अणु
		.ctl = 0,
		.name = "Digit-IO Playback Switch",
	पूर्ण,
पूर्ण;

अटल व्योम
ct_mixer_recording_select(काष्ठा ct_mixer *mixer, क्रमागत CT_AMIXER_CTL type);

अटल व्योम
ct_mixer_recording_unselect(काष्ठा ct_mixer *mixer, क्रमागत CT_AMIXER_CTL type);

/* FIXME: this अटल looks like it would fail अगर more than one card was */
/* installed. */
अटल काष्ठा snd_kcontrol *kctls[2] = अणुशून्यपूर्ण;

अटल क्रमागत CT_AMIXER_CTL get_amixer_index(क्रमागत CTALSA_MIXER_CTL alsa_index)
अणु
	चयन (alsa_index) अणु
	हाल MIXER_MASTER_P:	वापस AMIXER_MASTER_F;
	हाल MIXER_MASTER_C:	वापस AMIXER_MASTER_F_C;
	हाल MIXER_PCM_P:	वापस AMIXER_PCM_F;
	हाल MIXER_PCM_C:
	हाल MIXER_PCM_C_S:	वापस AMIXER_PCM_F_C;
	हाल MIXER_LINEIN_P:	वापस AMIXER_LINEIN;
	हाल MIXER_LINEIN_C:
	हाल MIXER_LINEIN_C_S:	वापस AMIXER_LINEIN_C;
	हाल MIXER_MIC_P:	वापस AMIXER_MIC;
	हाल MIXER_MIC_C:
	हाल MIXER_MIC_C_S:	वापस AMIXER_MIC_C;
	हाल MIXER_SPDIFI_P:	वापस AMIXER_SPDIFI;
	हाल MIXER_SPDIFI_C:
	हाल MIXER_SPDIFI_C_S:	वापस AMIXER_SPDIFI_C;
	हाल MIXER_SPDIFO_P:	वापस AMIXER_SPDIFO;
	हाल MIXER_WAVEF_P:	वापस AMIXER_WAVE_F;
	हाल MIXER_WAVES_P:	वापस AMIXER_WAVE_S;
	हाल MIXER_WAVEC_P:	वापस AMIXER_WAVE_C;
	हाल MIXER_WAVER_P:	वापस AMIXER_WAVE_R;
	शेष:		वापस NUM_CT_AMIXERS;
	पूर्ण
पूर्ण

अटल क्रमागत CT_AMIXER_CTL get_recording_amixer(क्रमागत CT_AMIXER_CTL index)
अणु
	चयन (index) अणु
	हाल AMIXER_MASTER_F:	वापस AMIXER_MASTER_F_C;
	हाल AMIXER_PCM_F:	वापस AMIXER_PCM_F_C;
	हाल AMIXER_SPDIFI:	वापस AMIXER_SPDIFI_C;
	हाल AMIXER_LINEIN:	वापस AMIXER_LINEIN_C;
	हाल AMIXER_MIC:	वापस AMIXER_MIC_C;
	शेष:		वापस NUM_CT_AMIXERS;
	पूर्ण
पूर्ण

अटल अचिन्हित अक्षर
get_चयन_state(काष्ठा ct_mixer *mixer, क्रमागत CTALSA_MIXER_CTL type)
अणु
	वापस (mixer->चयन_state & (0x1 << (type - SWH_MIXER_START)))
		? 1 : 0;
पूर्ण

अटल व्योम
set_चयन_state(काष्ठा ct_mixer *mixer,
		 क्रमागत CTALSA_MIXER_CTL type, अचिन्हित अक्षर state)
अणु
	अगर (state)
		mixer->चयन_state |= (0x1 << (type - SWH_MIXER_START));
	अन्यथा
		mixer->चयन_state &= ~(0x1 << (type - SWH_MIXER_START));
पूर्ण

#अगर 0 /* not used */
/* Map पूर्णांकeger value ranging from 0 to 65535 to 14-bit भग्न value ranging
 * from 2^-6 to (1+1023/1024) */
अटल अचिन्हित पूर्णांक uपूर्णांक16_to_भग्न14(अचिन्हित पूर्णांक x)
अणु
	अचिन्हित पूर्णांक i;

	अगर (x < 17)
		वापस 0;

	x *= 2031;
	x /= 65535;
	x += 16;

	/* i <= 6 */
	क्रम (i = 0; !(x & 0x400); i++)
		x <<= 1;

	x = (((7 - i) & 0x7) << 10) | (x & 0x3ff);

	वापस x;
पूर्ण

अटल अचिन्हित पूर्णांक भग्न14_to_uपूर्णांक16(अचिन्हित पूर्णांक x)
अणु
	अचिन्हित पूर्णांक e;

	अगर (!x)
		वापस x;

	e = (x >> 10) & 0x7;
	x &= 0x3ff;
	x += 1024;
	x >>= (7 - e);
	x -= 16;
	x *= 65535;
	x /= 2031;

	वापस x;
पूर्ण
#पूर्ण_अगर /* not used */

#घोषणा VOL_SCALE	0x1c
#घोषणा VOL_MAX		0x100

अटल स्थिर DECLARE_TLV_DB_SCALE(ct_vol_db_scale, -6400, 25, 1);

अटल पूर्णांक ct_alsa_mix_volume_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = VOL_MAX;

	वापस 0;
पूर्ण

अटल पूर्णांक ct_alsa_mix_volume_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ct_atc *atc = snd_kcontrol_chip(kcontrol);
	क्रमागत CT_AMIXER_CTL type = get_amixer_index(kcontrol->निजी_value);
	काष्ठा amixer *amixer;
	पूर्णांक i, val;

	क्रम (i = 0; i < 2; i++) अणु
		amixer = ((काष्ठा ct_mixer *)atc->mixer)->
						amixers[type*CHN_NUM+i];
		val = amixer->ops->get_scale(amixer) / VOL_SCALE;
		अगर (val < 0)
			val = 0;
		अन्यथा अगर (val > VOL_MAX)
			val = VOL_MAX;
		ucontrol->value.पूर्णांकeger.value[i] = val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ct_alsa_mix_volume_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ct_atc *atc = snd_kcontrol_chip(kcontrol);
	काष्ठा ct_mixer *mixer = atc->mixer;
	क्रमागत CT_AMIXER_CTL type = get_amixer_index(kcontrol->निजी_value);
	काष्ठा amixer *amixer;
	पूर्णांक i, j, val, oval, change = 0;

	क्रम (i = 0; i < 2; i++) अणु
		val = ucontrol->value.पूर्णांकeger.value[i];
		अगर (val < 0)
			val = 0;
		अन्यथा अगर (val > VOL_MAX)
			val = VOL_MAX;
		val *= VOL_SCALE;
		amixer = mixer->amixers[type*CHN_NUM+i];
		oval = amixer->ops->get_scale(amixer);
		अगर (val != oval) अणु
			amixer->ops->set_scale(amixer, val);
			amixer->ops->commit_ग_लिखो(amixer);
			change = 1;
			/* Synchronize Master/PCM playback AMIXERs. */
			अगर (AMIXER_MASTER_F == type || AMIXER_PCM_F == type) अणु
				क्रम (j = 1; j < 4; j++) अणु
					amixer = mixer->
						amixers[(type+j)*CHN_NUM+i];
					amixer->ops->set_scale(amixer, val);
					amixer->ops->commit_ग_लिखो(amixer);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस change;
पूर्ण

अटल काष्ठा snd_kcontrol_new vol_ctl = अणु
	.access		= SNDRV_CTL_ELEM_ACCESS_READWRITE |
			  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
	.अगरace		= SNDRV_CTL_ELEM_IFACE_MIXER,
	.info		= ct_alsa_mix_volume_info,
	.get		= ct_alsa_mix_volume_get,
	.put		= ct_alsa_mix_volume_put,
	.tlv		= अणु .p =  ct_vol_db_scale पूर्ण,
पूर्ण;

अटल पूर्णांक output_चयन_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[3] = अणु
	  "FP Headphones", "Headphones", "Speakers"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 3, names);
पूर्ण

अटल पूर्णांक output_चयन_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ct_atc *atc = snd_kcontrol_chip(kcontrol);
	ucontrol->value.क्रमागतerated.item[0] = atc->output_चयन_get(atc);
	वापस 0;
पूर्ण

अटल पूर्णांक output_चयन_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ct_atc *atc = snd_kcontrol_chip(kcontrol);
	अगर (ucontrol->value.क्रमागतerated.item[0] > 2)
		वापस -EINVAL;
	वापस atc->output_चयन_put(atc, ucontrol->value.क्रमागतerated.item[0]);
पूर्ण

अटल काष्ठा snd_kcontrol_new output_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Analog Output Playback Enum",
	.info = output_चयन_info,
	.get = output_चयन_get,
	.put = output_चयन_put,
पूर्ण;

अटल पूर्णांक mic_source_चयन_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[3] = अणु
	  "Mic", "FP Mic", "Aux"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 3, names);
पूर्ण

अटल पूर्णांक mic_source_चयन_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ct_atc *atc = snd_kcontrol_chip(kcontrol);
	ucontrol->value.क्रमागतerated.item[0] = atc->mic_source_चयन_get(atc);
	वापस 0;
पूर्ण

अटल पूर्णांक mic_source_चयन_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ct_atc *atc = snd_kcontrol_chip(kcontrol);
	अगर (ucontrol->value.क्रमागतerated.item[0] > 2)
		वापस -EINVAL;
	वापस atc->mic_source_चयन_put(atc,
					ucontrol->value.क्रमागतerated.item[0]);
पूर्ण

अटल काष्ठा snd_kcontrol_new mic_source_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Mic Source Capture Enum",
	.info = mic_source_चयन_info,
	.get = mic_source_चयन_get,
	.put = mic_source_चयन_put,
पूर्ण;

अटल व्योम
करो_line_mic_चयन(काष्ठा ct_atc *atc, क्रमागत CTALSA_MIXER_CTL type)
अणु

	अगर (MIXER_LINEIN_C_S == type) अणु
		atc->select_line_in(atc);
		set_चयन_state(atc->mixer, MIXER_MIC_C_S, 0);
		snd_ctl_notअगरy(atc->card, SNDRV_CTL_EVENT_MASK_VALUE,
							&kctls[1]->id);
	पूर्ण अन्यथा अगर (MIXER_MIC_C_S == type) अणु
		atc->select_mic_in(atc);
		set_चयन_state(atc->mixer, MIXER_LINEIN_C_S, 0);
		snd_ctl_notअगरy(atc->card, SNDRV_CTL_EVENT_MASK_VALUE,
							&kctls[0]->id);
	पूर्ण
पूर्ण

अटल व्योम
करो_digit_io_चयन(काष्ठा ct_atc *atc, पूर्णांक state)
अणु
	काष्ठा ct_mixer *mixer = atc->mixer;

	अगर (state) अणु
		atc->select_digit_io(atc);
		atc->spdअगर_out_unmute(atc,
				get_चयन_state(mixer, MIXER_SPDIFO_P_S));
		atc->spdअगर_in_unmute(atc, 1);
		atc->line_in_unmute(atc, 0);
		वापस;
	पूर्ण

	अगर (get_चयन_state(mixer, MIXER_LINEIN_C_S))
		atc->select_line_in(atc);
	अन्यथा अगर (get_चयन_state(mixer, MIXER_MIC_C_S))
		atc->select_mic_in(atc);

	atc->spdअगर_out_unmute(atc, 0);
	atc->spdअगर_in_unmute(atc, 0);
	atc->line_in_unmute(atc, 1);
	वापस;
पूर्ण

अटल व्योम करो_चयन(काष्ठा ct_atc *atc, क्रमागत CTALSA_MIXER_CTL type, पूर्णांक state)
अणु
	काष्ठा ct_mixer *mixer = atc->mixer;
	काष्ठा capabilities cap = atc->capabilities(atc);

	/* Do changes in mixer. */
	अगर ((SWH_CAPTURE_START <= type) && (SWH_CAPTURE_END >= type)) अणु
		अगर (state) अणु
			ct_mixer_recording_select(mixer,
						  get_amixer_index(type));
		पूर्ण अन्यथा अणु
			ct_mixer_recording_unselect(mixer,
						    get_amixer_index(type));
		पूर्ण
	पूर्ण
	/* Do changes out of mixer. */
	अगर (!cap.dedicated_mic &&
	    (MIXER_LINEIN_C_S == type || MIXER_MIC_C_S == type)) अणु
		अगर (state)
			करो_line_mic_चयन(atc, type);
		atc->line_in_unmute(atc, state);
	पूर्ण अन्यथा अगर (cap.dedicated_mic && (MIXER_LINEIN_C_S == type))
		atc->line_in_unmute(atc, state);
	अन्यथा अगर (cap.dedicated_mic && (MIXER_MIC_C_S == type))
		atc->mic_unmute(atc, state);
	अन्यथा अगर (MIXER_SPDIFI_C_S == type)
		atc->spdअगर_in_unmute(atc, state);
	अन्यथा अगर (MIXER_WAVEF_P_S == type)
		atc->line_front_unmute(atc, state);
	अन्यथा अगर (MIXER_WAVES_P_S == type)
		atc->line_surround_unmute(atc, state);
	अन्यथा अगर (MIXER_WAVEC_P_S == type)
		atc->line_clfe_unmute(atc, state);
	अन्यथा अगर (MIXER_WAVER_P_S == type)
		atc->line_rear_unmute(atc, state);
	अन्यथा अगर (MIXER_SPDIFO_P_S == type)
		atc->spdअगर_out_unmute(atc, state);
	अन्यथा अगर (MIXER_DIGITAL_IO_S == type)
		करो_digit_io_चयन(atc, state);

	वापस;
पूर्ण

अटल पूर्णांक ct_alsa_mix_चयन_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	uinfo->value.पूर्णांकeger.step = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ct_alsa_mix_चयन_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ct_mixer *mixer =
		((काष्ठा ct_atc *)snd_kcontrol_chip(kcontrol))->mixer;
	क्रमागत CTALSA_MIXER_CTL type = kcontrol->निजी_value;

	ucontrol->value.पूर्णांकeger.value[0] = get_चयन_state(mixer, type);
	वापस 0;
पूर्ण

अटल पूर्णांक ct_alsa_mix_चयन_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ct_atc *atc = snd_kcontrol_chip(kcontrol);
	काष्ठा ct_mixer *mixer = atc->mixer;
	क्रमागत CTALSA_MIXER_CTL type = kcontrol->निजी_value;
	पूर्णांक state;

	state = ucontrol->value.पूर्णांकeger.value[0];
	अगर (get_चयन_state(mixer, type) == state)
		वापस 0;

	set_चयन_state(mixer, type, state);
	करो_चयन(atc, type, state);

	वापस 1;
पूर्ण

अटल काष्ठा snd_kcontrol_new swh_ctl = अणु
	.access		= SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.अगरace		= SNDRV_CTL_ELEM_IFACE_MIXER,
	.info		= ct_alsa_mix_चयन_info,
	.get		= ct_alsa_mix_चयन_get,
	.put		= ct_alsa_mix_चयन_put
पूर्ण;

अटल पूर्णांक ct_spdअगर_info(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ct_spdअगर_get_mask(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = 0xff;
	ucontrol->value.iec958.status[1] = 0xff;
	ucontrol->value.iec958.status[2] = 0xff;
	ucontrol->value.iec958.status[3] = 0xff;
	वापस 0;
पूर्ण

अटल पूर्णांक ct_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ct_atc *atc = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक status;

	atc->spdअगर_out_get_status(atc, &status);

	अगर (status == 0)
		status = SNDRV_PCM_DEFAULT_CON_SPDIF;

	ucontrol->value.iec958.status[0] = (status >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (status >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (status >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (status >> 24) & 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक ct_spdअगर_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ct_atc *atc = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक status, old_status;

	status = (ucontrol->value.iec958.status[0] << 0) |
		 (ucontrol->value.iec958.status[1] << 8) |
		 (ucontrol->value.iec958.status[2] << 16) |
		 (ucontrol->value.iec958.status[3] << 24);

	atc->spdअगर_out_get_status(atc, &old_status);
	change = (old_status != status);
	अगर (change)
		atc->spdअगर_out_set_status(atc, status);

	वापस change;
पूर्ण

अटल काष्ठा snd_kcontrol_new iec958_mask_ctl = अणु
	.access		= SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace		= SNDRV_CTL_ELEM_IFACE_PCM,
	.name		= SNDRV_CTL_NAME_IEC958("", PLAYBACK, MASK),
	.count		= 1,
	.info		= ct_spdअगर_info,
	.get		= ct_spdअगर_get_mask,
	.निजी_value	= MIXER_IEC958_MASK
पूर्ण;

अटल काष्ठा snd_kcontrol_new iec958_शेष_ctl = अणु
	.अगरace		= SNDRV_CTL_ELEM_IFACE_PCM,
	.name		= SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
	.count		= 1,
	.info		= ct_spdअगर_info,
	.get		= ct_spdअगर_get,
	.put		= ct_spdअगर_put,
	.निजी_value	= MIXER_IEC958_DEFAULT
पूर्ण;

अटल काष्ठा snd_kcontrol_new iec958_ctl = अणु
	.access		= SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.अगरace		= SNDRV_CTL_ELEM_IFACE_PCM,
	.name		= SNDRV_CTL_NAME_IEC958("", PLAYBACK, PCM_STREAM),
	.count		= 1,
	.info		= ct_spdअगर_info,
	.get		= ct_spdअगर_get,
	.put		= ct_spdअगर_put,
	.निजी_value	= MIXER_IEC958_STREAM
पूर्ण;

#घोषणा NUM_IEC958_CTL 3

अटल पूर्णांक
ct_mixer_kcontrol_new(काष्ठा ct_mixer *mixer, काष्ठा snd_kcontrol_new *new)
अणु
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक err;

	kctl = snd_ctl_new1(new, mixer->atc);
	अगर (!kctl)
		वापस -ENOMEM;

	अगर (SNDRV_CTL_ELEM_IFACE_PCM == kctl->id.अगरace)
		kctl->id.device = IEC958;

	err = snd_ctl_add(mixer->atc->card, kctl);
	अगर (err)
		वापस err;

	चयन (new->निजी_value) अणु
	हाल MIXER_LINEIN_C_S:
		kctls[0] = kctl; अवरोध;
	हाल MIXER_MIC_C_S:
		kctls[1] = kctl; अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ct_mixer_kcontrols_create(काष्ठा ct_mixer *mixer)
अणु
	क्रमागत CTALSA_MIXER_CTL type;
	काष्ठा ct_atc *atc = mixer->atc;
	काष्ठा capabilities cap = atc->capabilities(atc);
	पूर्णांक err;

	/* Create snd kcontrol instances on demand */
	क्रम (type = VOL_MIXER_START; type <= VOL_MIXER_END; type++) अणु
		अगर (ct_kcontrol_init_table[type].ctl) अणु
			vol_ctl.name = ct_kcontrol_init_table[type].name;
			vol_ctl.निजी_value = (अचिन्हित दीर्घ)type;
			err = ct_mixer_kcontrol_new(mixer, &vol_ctl);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	ct_kcontrol_init_table[MIXER_DIGITAL_IO_S].ctl = cap.digit_io_चयन;

	क्रम (type = SWH_MIXER_START; type <= SWH_MIXER_END; type++) अणु
		अगर (ct_kcontrol_init_table[type].ctl) अणु
			swh_ctl.name = ct_kcontrol_init_table[type].name;
			swh_ctl.निजी_value = (अचिन्हित दीर्घ)type;
			err = ct_mixer_kcontrol_new(mixer, &swh_ctl);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	err = ct_mixer_kcontrol_new(mixer, &iec958_mask_ctl);
	अगर (err)
		वापस err;

	err = ct_mixer_kcontrol_new(mixer, &iec958_शेष_ctl);
	अगर (err)
		वापस err;

	err = ct_mixer_kcontrol_new(mixer, &iec958_ctl);
	अगर (err)
		वापस err;

	अगर (cap.output_चयन) अणु
		err = ct_mixer_kcontrol_new(mixer, &output_ctl);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (cap.mic_source_चयन) अणु
		err = ct_mixer_kcontrol_new(mixer, &mic_source_ctl);
		अगर (err)
			वापस err;
	पूर्ण
	atc->line_front_unmute(atc, 1);
	set_चयन_state(mixer, MIXER_WAVEF_P_S, 1);
	atc->line_surround_unmute(atc, 0);
	set_चयन_state(mixer, MIXER_WAVES_P_S, 0);
	atc->line_clfe_unmute(atc, 0);
	set_चयन_state(mixer, MIXER_WAVEC_P_S, 0);
	atc->line_rear_unmute(atc, 0);
	set_चयन_state(mixer, MIXER_WAVER_P_S, 0);
	atc->spdअगर_out_unmute(atc, 0);
	set_चयन_state(mixer, MIXER_SPDIFO_P_S, 0);
	atc->line_in_unmute(atc, 0);
	अगर (cap.dedicated_mic)
		atc->mic_unmute(atc, 0);
	atc->spdअगर_in_unmute(atc, 0);
	set_चयन_state(mixer, MIXER_PCM_C_S, 0);
	set_चयन_state(mixer, MIXER_LINEIN_C_S, 0);
	set_चयन_state(mixer, MIXER_SPDIFI_C_S, 0);

	वापस 0;
पूर्ण

अटल व्योम
ct_mixer_recording_select(काष्ठा ct_mixer *mixer, क्रमागत CT_AMIXER_CTL type)
अणु
	काष्ठा amixer *amix_d;
	काष्ठा sum *sum_c;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		amix_d = mixer->amixers[type*CHN_NUM+i];
		sum_c = mixer->sums[SUM_IN_F_C*CHN_NUM+i];
		amix_d->ops->set_sum(amix_d, sum_c);
		amix_d->ops->commit_ग_लिखो(amix_d);
	पूर्ण
पूर्ण

अटल व्योम
ct_mixer_recording_unselect(काष्ठा ct_mixer *mixer, क्रमागत CT_AMIXER_CTL type)
अणु
	काष्ठा amixer *amix_d;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		amix_d = mixer->amixers[type*CHN_NUM+i];
		amix_d->ops->set_sum(amix_d, शून्य);
		amix_d->ops->commit_ग_लिखो(amix_d);
	पूर्ण
पूर्ण

अटल पूर्णांक ct_mixer_get_resources(काष्ठा ct_mixer *mixer)
अणु
	काष्ठा sum_mgr *sum_mgr;
	काष्ठा sum *sum;
	काष्ठा sum_desc sum_desc = अणु0पूर्ण;
	काष्ठा amixer_mgr *amixer_mgr;
	काष्ठा amixer *amixer;
	काष्ठा amixer_desc am_desc = अणु0पूर्ण;
	पूर्णांक err;
	पूर्णांक i;

	/* Allocate sum resources क्रम mixer obj */
	sum_mgr = (काष्ठा sum_mgr *)mixer->atc->rsc_mgrs[SUM];
	sum_desc.msr = mixer->atc->msr;
	क्रम (i = 0; i < (NUM_CT_SUMS * CHN_NUM); i++) अणु
		err = sum_mgr->get_sum(sum_mgr, &sum_desc, &sum);
		अगर (err) अणु
			dev_err(mixer->atc->card->dev,
				"Failed to get sum resources for front output!\n");
			अवरोध;
		पूर्ण
		mixer->sums[i] = sum;
	पूर्ण
	अगर (err)
		जाओ error1;

	/* Allocate amixer resources क्रम mixer obj */
	amixer_mgr = (काष्ठा amixer_mgr *)mixer->atc->rsc_mgrs[AMIXER];
	am_desc.msr = mixer->atc->msr;
	क्रम (i = 0; i < (NUM_CT_AMIXERS * CHN_NUM); i++) अणु
		err = amixer_mgr->get_amixer(amixer_mgr, &am_desc, &amixer);
		अगर (err) अणु
			dev_err(mixer->atc->card->dev,
				"Failed to get amixer resources for mixer obj!\n");
			अवरोध;
		पूर्ण
		mixer->amixers[i] = amixer;
	पूर्ण
	अगर (err)
		जाओ error2;

	वापस 0;

error2:
	क्रम (i = 0; i < (NUM_CT_AMIXERS * CHN_NUM); i++) अणु
		अगर (शून्य != mixer->amixers[i]) अणु
			amixer = mixer->amixers[i];
			amixer_mgr->put_amixer(amixer_mgr, amixer);
			mixer->amixers[i] = शून्य;
		पूर्ण
	पूर्ण
error1:
	क्रम (i = 0; i < (NUM_CT_SUMS * CHN_NUM); i++) अणु
		अगर (शून्य != mixer->sums[i]) अणु
			sum_mgr->put_sum(sum_mgr, (काष्ठा sum *)mixer->sums[i]);
			mixer->sums[i] = शून्य;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ct_mixer_get_mem(काष्ठा ct_mixer **rmixer)
अणु
	काष्ठा ct_mixer *mixer;
	पूर्णांक err;

	*rmixer = शून्य;
	/* Allocate mem क्रम mixer obj */
	mixer = kzalloc(माप(*mixer), GFP_KERNEL);
	अगर (!mixer)
		वापस -ENOMEM;

	mixer->amixers = kसुस्मृति(NUM_CT_AMIXERS * CHN_NUM, माप(व्योम *),
				 GFP_KERNEL);
	अगर (!mixer->amixers) अणु
		err = -ENOMEM;
		जाओ error1;
	पूर्ण
	mixer->sums = kसुस्मृति(NUM_CT_SUMS * CHN_NUM, माप(व्योम *),
			      GFP_KERNEL);
	अगर (!mixer->sums) अणु
		err = -ENOMEM;
		जाओ error2;
	पूर्ण

	*rmixer = mixer;
	वापस 0;

error2:
	kमुक्त(mixer->amixers);
error1:
	kमुक्त(mixer);
	वापस err;
पूर्ण

अटल पूर्णांक ct_mixer_topology_build(काष्ठा ct_mixer *mixer)
अणु
	काष्ठा sum *sum;
	काष्ठा amixer *amix_d, *amix_s;
	क्रमागत CT_AMIXER_CTL i, j;
	क्रमागत CT_SUM_CTL k;

	/* Build topology from destination to source */

	/* Set up Master mixer */
	क्रम (i = AMIXER_MASTER_F, k = SUM_IN_F;
					i <= AMIXER_MASTER_S; i++, k++) अणु
		amix_d = mixer->amixers[i*CHN_NUM];
		sum = mixer->sums[k*CHN_NUM];
		amix_d->ops->setup(amix_d, &sum->rsc, INIT_VOL, शून्य);
		amix_d = mixer->amixers[i*CHN_NUM+1];
		sum = mixer->sums[k*CHN_NUM+1];
		amix_d->ops->setup(amix_d, &sum->rsc, INIT_VOL, शून्य);
	पूर्ण

	/* Set up Wave-out mixer */
	क्रम (i = AMIXER_WAVE_F, j = AMIXER_MASTER_F;
					i <= AMIXER_WAVE_S; i++, j++) अणु
		amix_d = mixer->amixers[i*CHN_NUM];
		amix_s = mixer->amixers[j*CHN_NUM];
		amix_d->ops->setup(amix_d, &amix_s->rsc, INIT_VOL, शून्य);
		amix_d = mixer->amixers[i*CHN_NUM+1];
		amix_s = mixer->amixers[j*CHN_NUM+1];
		amix_d->ops->setup(amix_d, &amix_s->rsc, INIT_VOL, शून्य);
	पूर्ण

	/* Set up S/PDIF-out mixer */
	amix_d = mixer->amixers[AMIXER_SPDIFO*CHN_NUM];
	amix_s = mixer->amixers[AMIXER_MASTER_F*CHN_NUM];
	amix_d->ops->setup(amix_d, &amix_s->rsc, INIT_VOL, शून्य);
	amix_d = mixer->amixers[AMIXER_SPDIFO*CHN_NUM+1];
	amix_s = mixer->amixers[AMIXER_MASTER_F*CHN_NUM+1];
	amix_d->ops->setup(amix_d, &amix_s->rsc, INIT_VOL, शून्य);

	/* Set up PCM-in mixer */
	क्रम (i = AMIXER_PCM_F, k = SUM_IN_F; i <= AMIXER_PCM_S; i++, k++) अणु
		amix_d = mixer->amixers[i*CHN_NUM];
		sum = mixer->sums[k*CHN_NUM];
		amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);
		amix_d = mixer->amixers[i*CHN_NUM+1];
		sum = mixer->sums[k*CHN_NUM+1];
		amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);
	पूर्ण

	/* Set up Line-in mixer */
	amix_d = mixer->amixers[AMIXER_LINEIN*CHN_NUM];
	sum = mixer->sums[SUM_IN_F*CHN_NUM];
	amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);
	amix_d = mixer->amixers[AMIXER_LINEIN*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F*CHN_NUM+1];
	amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);

	/* Set up Mic-in mixer */
	amix_d = mixer->amixers[AMIXER_MIC*CHN_NUM];
	sum = mixer->sums[SUM_IN_F*CHN_NUM];
	amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);
	amix_d = mixer->amixers[AMIXER_MIC*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F*CHN_NUM+1];
	amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);

	/* Set up S/PDIF-in mixer */
	amix_d = mixer->amixers[AMIXER_SPDIFI*CHN_NUM];
	sum = mixer->sums[SUM_IN_F*CHN_NUM];
	amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);
	amix_d = mixer->amixers[AMIXER_SPDIFI*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F*CHN_NUM+1];
	amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);

	/* Set up Master recording mixer */
	amix_d = mixer->amixers[AMIXER_MASTER_F_C*CHN_NUM];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, &sum->rsc, INIT_VOL, शून्य);
	amix_d = mixer->amixers[AMIXER_MASTER_F_C*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, &sum->rsc, INIT_VOL, शून्य);

	/* Set up PCM-in recording mixer */
	amix_d = mixer->amixers[AMIXER_PCM_F_C*CHN_NUM];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);
	amix_d = mixer->amixers[AMIXER_PCM_F_C*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);

	/* Set up Line-in recording mixer */
	amix_d = mixer->amixers[AMIXER_LINEIN_C*CHN_NUM];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);
	amix_d = mixer->amixers[AMIXER_LINEIN_C*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);

	/* Set up Mic-in recording mixer */
	amix_d = mixer->amixers[AMIXER_MIC_C*CHN_NUM];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);
	amix_d = mixer->amixers[AMIXER_MIC_C*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);

	/* Set up S/PDIF-in recording mixer */
	amix_d = mixer->amixers[AMIXER_SPDIFI_C*CHN_NUM];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);
	amix_d = mixer->amixers[AMIXER_SPDIFI_C*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, शून्य, INIT_VOL, sum);

	वापस 0;
पूर्ण

अटल पूर्णांक mixer_set_input_port(काष्ठा amixer *amixer, काष्ठा rsc *rsc)
अणु
	amixer->ops->set_input(amixer, rsc);
	amixer->ops->commit_ग_लिखो(amixer);

	वापस 0;
पूर्ण

अटल क्रमागत CT_AMIXER_CTL port_to_amixer(क्रमागत MIXER_PORT_T type)
अणु
	चयन (type) अणु
	हाल MIX_WAVE_FRONT:	वापस AMIXER_WAVE_F;
	हाल MIX_WAVE_SURROUND:	वापस AMIXER_WAVE_S;
	हाल MIX_WAVE_CENTLFE:	वापस AMIXER_WAVE_C;
	हाल MIX_WAVE_REAR:	वापस AMIXER_WAVE_R;
	हाल MIX_PCMO_FRONT:	वापस AMIXER_MASTER_F_C;
	हाल MIX_SPDIF_OUT:	वापस AMIXER_SPDIFO;
	हाल MIX_LINE_IN:	वापस AMIXER_LINEIN;
	हाल MIX_MIC_IN:	वापस AMIXER_MIC;
	हाल MIX_SPDIF_IN:	वापस AMIXER_SPDIFI;
	हाल MIX_PCMI_FRONT:	वापस AMIXER_PCM_F;
	हाल MIX_PCMI_SURROUND:	वापस AMIXER_PCM_S;
	हाल MIX_PCMI_CENTLFE:	वापस AMIXER_PCM_C;
	हाल MIX_PCMI_REAR:	वापस AMIXER_PCM_R;
	शेष: 		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक mixer_get_output_ports(काष्ठा ct_mixer *mixer,
				  क्रमागत MIXER_PORT_T type,
				  काष्ठा rsc **rleft, काष्ठा rsc **rright)
अणु
	क्रमागत CT_AMIXER_CTL amix = port_to_amixer(type);

	अगर (शून्य != rleft)
		*rleft = &((काष्ठा amixer *)mixer->amixers[amix*CHN_NUM])->rsc;

	अगर (शून्य != rright)
		*rright =
			&((काष्ठा amixer *)mixer->amixers[amix*CHN_NUM+1])->rsc;

	वापस 0;
पूर्ण

अटल पूर्णांक mixer_set_input_left(काष्ठा ct_mixer *mixer,
				क्रमागत MIXER_PORT_T type, काष्ठा rsc *rsc)
अणु
	क्रमागत CT_AMIXER_CTL amix = port_to_amixer(type);

	mixer_set_input_port(mixer->amixers[amix*CHN_NUM], rsc);
	amix = get_recording_amixer(amix);
	अगर (amix < NUM_CT_AMIXERS)
		mixer_set_input_port(mixer->amixers[amix*CHN_NUM], rsc);

	वापस 0;
पूर्ण

अटल पूर्णांक
mixer_set_input_right(काष्ठा ct_mixer *mixer,
		      क्रमागत MIXER_PORT_T type, काष्ठा rsc *rsc)
अणु
	क्रमागत CT_AMIXER_CTL amix = port_to_amixer(type);

	mixer_set_input_port(mixer->amixers[amix*CHN_NUM+1], rsc);
	amix = get_recording_amixer(amix);
	अगर (amix < NUM_CT_AMIXERS)
		mixer_set_input_port(mixer->amixers[amix*CHN_NUM+1], rsc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mixer_resume(काष्ठा ct_mixer *mixer)
अणु
	पूर्णांक i, state;
	काष्ठा amixer *amixer;

	/* resume topology and volume gain. */
	क्रम (i = 0; i < NUM_CT_AMIXERS*CHN_NUM; i++) अणु
		amixer = mixer->amixers[i];
		amixer->ops->commit_ग_लिखो(amixer);
	पूर्ण

	/* resume चयन state. */
	क्रम (i = SWH_MIXER_START; i <= SWH_MIXER_END; i++) अणु
		state = get_चयन_state(mixer, i);
		करो_चयन(mixer->atc, i, state);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक ct_mixer_destroy(काष्ठा ct_mixer *mixer)
अणु
	काष्ठा sum_mgr *sum_mgr = (काष्ठा sum_mgr *)mixer->atc->rsc_mgrs[SUM];
	काष्ठा amixer_mgr *amixer_mgr =
			(काष्ठा amixer_mgr *)mixer->atc->rsc_mgrs[AMIXER];
	काष्ठा amixer *amixer;
	पूर्णांक i = 0;

	/* Release amixer resources */
	क्रम (i = 0; i < (NUM_CT_AMIXERS * CHN_NUM); i++) अणु
		अगर (शून्य != mixer->amixers[i]) अणु
			amixer = mixer->amixers[i];
			amixer_mgr->put_amixer(amixer_mgr, amixer);
		पूर्ण
	पूर्ण

	/* Release sum resources */
	क्रम (i = 0; i < (NUM_CT_SUMS * CHN_NUM); i++) अणु
		अगर (शून्य != mixer->sums[i])
			sum_mgr->put_sum(sum_mgr, (काष्ठा sum *)mixer->sums[i]);
	पूर्ण

	/* Release mem asचिन्हित to mixer object */
	kमुक्त(mixer->sums);
	kमुक्त(mixer->amixers);
	kमुक्त(mixer);

	वापस 0;
पूर्ण

पूर्णांक ct_mixer_create(काष्ठा ct_atc *atc, काष्ठा ct_mixer **rmixer)
अणु
	काष्ठा ct_mixer *mixer;
	पूर्णांक err;

	*rmixer = शून्य;

	/* Allocate mem क्रम mixer obj */
	err = ct_mixer_get_mem(&mixer);
	अगर (err)
		वापस err;

	mixer->चयन_state = 0;
	mixer->atc = atc;
	/* Set operations */
	mixer->get_output_ports = mixer_get_output_ports;
	mixer->set_input_left = mixer_set_input_left;
	mixer->set_input_right = mixer_set_input_right;
#अगर_घोषित CONFIG_PM_SLEEP
	mixer->resume = mixer_resume;
#पूर्ण_अगर

	/* Allocate chip resources क्रम mixer obj */
	err = ct_mixer_get_resources(mixer);
	अगर (err)
		जाओ error;

	/* Build पूर्णांकernal mixer topology */
	ct_mixer_topology_build(mixer);

	*rmixer = mixer;

	वापस 0;

error:
	ct_mixer_destroy(mixer);
	वापस err;
पूर्ण

पूर्णांक ct_alsa_mix_create(काष्ठा ct_atc *atc,
		       क्रमागत CTALSADEVS device,
		       स्थिर अक्षर *device_name)
अणु
	पूर्णांक err;

	/* Create snd kcontrol instances on demand */
	/* vol_ctl.device = swh_ctl.device = device; */ /* better w/ device 0 */
	err = ct_mixer_kcontrols_create((काष्ठा ct_mixer *)atc->mixer);
	अगर (err)
		वापस err;

	म_नकल(atc->card->mixername, device_name);

	वापस 0;
पूर्ण
