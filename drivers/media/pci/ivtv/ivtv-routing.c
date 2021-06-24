<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Audio/video-routing-related ivtv functions.
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-i2c.h"
#समावेश "ivtv-cards.h"
#समावेश "ivtv-gpio.h"
#समावेश "ivtv-routing.h"

#समावेश <media/drv-पूर्णांकf/msp3400.h>
#समावेश <media/i2c/m52790.h>
#समावेश <media/i2c/upd64031a.h>
#समावेश <media/i2c/upd64083.h>

/* Selects the audio input and output according to the current
   settings. */
व्योम ivtv_audio_set_io(काष्ठा ivtv *itv)
अणु
	स्थिर काष्ठा ivtv_card_audio_input *in;
	u32 input, output = 0;

	/* Determine which input to use */
	अगर (test_bit(IVTV_F_I_RADIO_USER, &itv->i_flags))
		in = &itv->card->radio_input;
	अन्यथा
		in = &itv->card->audio_inमाला_दो[itv->audio_input];

	/* handle muxer chips */
	input = in->muxer_input;
	अगर (itv->card->hw_muxer & IVTV_HW_M52790)
		output = M52790_OUT_STEREO;
	v4l2_subdev_call(itv->sd_muxer, audio, s_routing,
			input, output, 0);

	input = in->audio_input;
	output = 0;
	अगर (itv->card->hw_audio & IVTV_HW_MSP34XX)
		output = MSP_OUTPUT(MSP_SC_IN_DSP_SCART1);
	ivtv_call_hw(itv, itv->card->hw_audio, audio, s_routing,
			input, output, 0);
पूर्ण

/* Selects the video input and output according to the current
   settings. */
व्योम ivtv_video_set_io(काष्ठा ivtv *itv)
अणु
	पूर्णांक inp = itv->active_input;
	u32 input;
	u32 type;

	v4l2_subdev_call(itv->sd_video, video, s_routing,
		itv->card->video_inमाला_दो[inp].video_input, 0, 0);

	type = itv->card->video_inमाला_दो[inp].video_type;

	अगर (type == IVTV_CARD_INPUT_VID_TUNER) अणु
		input = 0;  /* Tuner */
	पूर्ण अन्यथा अगर (type < IVTV_CARD_INPUT_COMPOSITE1) अणु
		input = 2;  /* S-Video */
	पूर्ण अन्यथा अणु
		input = 1;  /* Composite */
	पूर्ण

	अगर (itv->card->hw_video & IVTV_HW_GPIO)
		ivtv_call_hw(itv, IVTV_HW_GPIO, video, s_routing,
				input, 0, 0);

	अगर (itv->card->hw_video & IVTV_HW_UPD64031A) अणु
		अगर (type == IVTV_CARD_INPUT_VID_TUNER ||
		    type >= IVTV_CARD_INPUT_COMPOSITE1) अणु
			/* Composite: GR on, connect to 3DYCS */
			input = UPD64031A_GR_ON | UPD64031A_3DYCS_COMPOSITE;
		पूर्ण अन्यथा अणु
			/* S-Video: GR bypassed, turn it off */
			input = UPD64031A_GR_OFF | UPD64031A_3DYCS_DISABLE;
		पूर्ण
		input |= itv->card->gr_config;

		ivtv_call_hw(itv, IVTV_HW_UPD64031A, video, s_routing,
				input, 0, 0);
	पूर्ण

	अगर (itv->card->hw_video & IVTV_HW_UPD6408X) अणु
		input = UPD64083_YCS_MODE;
		अगर (type > IVTV_CARD_INPUT_VID_TUNER &&
		    type < IVTV_CARD_INPUT_COMPOSITE1) अणु
			/* S-Video uses YCNR mode and पूर्णांकernal Y-ADC, the
			   upd64031a is not used. */
			input |= UPD64083_YCNR_MODE;
		पूर्ण
		अन्यथा अगर (itv->card->hw_video & IVTV_HW_UPD64031A) अणु
			/* Use upd64031a output क्रम tuner and
			   composite(CX23416GYC only) inमाला_दो */
			अगर (type == IVTV_CARD_INPUT_VID_TUNER ||
			    itv->card->type == IVTV_CARD_CX23416GYC) अणु
				input |= UPD64083_EXT_Y_ADC;
			पूर्ण
		पूर्ण
		ivtv_call_hw(itv, IVTV_HW_UPD6408X, video, s_routing,
				input, 0, 0);
	पूर्ण
पूर्ण
