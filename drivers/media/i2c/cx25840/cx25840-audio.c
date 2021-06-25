<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* cx25840 audio functions
 */


#समावेश <linux/videodev2.h>
#समावेश <linux/i2c.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/drv-पूर्णांकf/cx25840.h>

#समावेश "cx25840-core.h"

/*
 * Note: The PLL and SRC parameters are based on a reference frequency that
 * would ideally be:
 *
 * NTSC Color subcarrier freq * 8 = 4.5 MHz/286 * 455/2 * 8 = 28.63636363... MHz
 *
 * However, it's not the exact reference frequency that matters, only that the
 * firmware and modules that comprise the driver क्रम a particular board all
 * use the same value (बंद to the ideal value).
 *
 * Comments below will note which reference frequency is assumed क्रम various
 * parameters.  They will usually be one of
 *
 *	ref_freq = 28.636360 MHz
 *		or
 *	ref_freq = 28.636363 MHz
 */

अटल पूर्णांक cx25840_set_audclk_freq(काष्ठा i2c_client *client, u32 freq)
अणु
	काष्ठा cx25840_state *state = to_state(i2c_get_clientdata(client));

	अगर (state->aud_input != CX25840_AUDIO_SERIAL) अणु
		चयन (freq) अणु
		हाल 32000:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x06, AUX PLL Post Divider = 0x10
			 */
			cx25840_ग_लिखो4(client, 0x108, 0x1006040f);

			/*
			 * VID_PLL Fraction (रेजिस्टर 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pre-postभागide
			 */

			/*
			 * AUX_PLL Fraction = 0x1bb39ee
			 * 28636363 * 0x6.dd9cf70/0x10 = 32000 * 384
			 * 196.6 MHz pre-postभागide
			 * FIXME < 200 MHz is out of specअगरied valid range
			 * FIXME 28636363 ref_freq करोesn't match VID PLL ref
			 */
			cx25840_ग_लिखो4(client, 0x110, 0x01bb39ee);

			/*
			 * SA_MCLK_SEL = 1
			 * SA_MCLK_DIV = 0x10 = 384/384 * AUX_PLL post dvivider
			 */
			cx25840_ग_लिखो(client, 0x127, 0x50);

			अगर (is_cx2583x(state))
				अवरोध;

			/* src3/4/6_ctl */
			/* 0x1.f77f = (4 * 28636360/8 * 2/455) / 32000 */
			cx25840_ग_लिखो4(client, 0x900, 0x0801f77f);
			cx25840_ग_लिखो4(client, 0x904, 0x0801f77f);
			cx25840_ग_लिखो4(client, 0x90c, 0x0801f77f);
			अवरोध;

		हाल 44100:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x09, AUX PLL Post Divider = 0x10
			 */
			cx25840_ग_लिखो4(client, 0x108, 0x1009040f);

			/*
			 * VID_PLL Fraction (रेजिस्टर 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pre-postभागide
			 */

			/*
			 * AUX_PLL Fraction = 0x0ec6bd6
			 * 28636363 * 0x9.7635eb0/0x10 = 44100 * 384
			 * 271 MHz pre-postभागide
			 * FIXME 28636363 ref_freq करोesn't match VID PLL ref
			 */
			cx25840_ग_लिखो4(client, 0x110, 0x00ec6bd6);

			/*
			 * SA_MCLK_SEL = 1
			 * SA_MCLK_DIV = 0x10 = 384/384 * AUX_PLL post dvivider
			 */
			cx25840_ग_लिखो(client, 0x127, 0x50);

			अगर (is_cx2583x(state))
				अवरोध;

			/* src3/4/6_ctl */
			/* 0x1.6d59 = (4 * 28636360/8 * 2/455) / 44100 */
			cx25840_ग_लिखो4(client, 0x900, 0x08016d59);
			cx25840_ग_लिखो4(client, 0x904, 0x08016d59);
			cx25840_ग_लिखो4(client, 0x90c, 0x08016d59);
			अवरोध;

		हाल 48000:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x0a, AUX PLL Post Divider = 0x10
			 */
			cx25840_ग_लिखो4(client, 0x108, 0x100a040f);

			/*
			 * VID_PLL Fraction (रेजिस्टर 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pre-postभागide
			 */

			/*
			 * AUX_PLL Fraction = 0x098d6e5
			 * 28636363 * 0xa.4c6b728/0x10 = 48000 * 384
			 * 295 MHz pre-postभागide
			 * FIXME 28636363 ref_freq करोesn't match VID PLL ref
			 */
			cx25840_ग_लिखो4(client, 0x110, 0x0098d6e5);

			/*
			 * SA_MCLK_SEL = 1
			 * SA_MCLK_DIV = 0x10 = 384/384 * AUX_PLL post dvivider
			 */
			cx25840_ग_लिखो(client, 0x127, 0x50);

			अगर (is_cx2583x(state))
				अवरोध;

			/* src3/4/6_ctl */
			/* 0x1.4faa = (4 * 28636360/8 * 2/455) / 48000 */
			cx25840_ग_लिखो4(client, 0x900, 0x08014faa);
			cx25840_ग_लिखो4(client, 0x904, 0x08014faa);
			cx25840_ग_लिखो4(client, 0x90c, 0x08014faa);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (freq) अणु
		हाल 32000:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x08, AUX PLL Post Divider = 0x1e
			 */
			cx25840_ग_लिखो4(client, 0x108, 0x1e08040f);

			/*
			 * VID_PLL Fraction (रेजिस्टर 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pre-postभागide
			 */

			/*
			 * AUX_PLL Fraction = 0x12a0869
			 * 28636363 * 0x8.9504348/0x1e = 32000 * 256
			 * 246 MHz pre-postभागide
			 * FIXME 28636363 ref_freq करोesn't match VID PLL ref
			 */
			cx25840_ग_लिखो4(client, 0x110, 0x012a0869);

			/*
			 * SA_MCLK_SEL = 1
			 * SA_MCLK_DIV = 0x14 = 256/384 * AUX_PLL post dvivider
			 */
			cx25840_ग_लिखो(client, 0x127, 0x54);

			अगर (is_cx2583x(state))
				अवरोध;

			/* src1_ctl */
			/* 0x1.0000 = 32000/32000 */
			cx25840_ग_लिखो4(client, 0x8f8, 0x08010000);

			/* src3/4/6_ctl */
			/* 0x2.0000 = 2 * (32000/32000) */
			cx25840_ग_लिखो4(client, 0x900, 0x08020000);
			cx25840_ग_लिखो4(client, 0x904, 0x08020000);
			cx25840_ग_लिखो4(client, 0x90c, 0x08020000);
			अवरोध;

		हाल 44100:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x09, AUX PLL Post Divider = 0x18
			 */
			cx25840_ग_लिखो4(client, 0x108, 0x1809040f);

			/*
			 * VID_PLL Fraction (रेजिस्टर 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pre-postभागide
			 */

			/*
			 * AUX_PLL Fraction = 0x0ec6bd6
			 * 28636363 * 0x9.7635eb0/0x18 = 44100 * 256
			 * 271 MHz pre-postभागide
			 * FIXME 28636363 ref_freq करोesn't match VID PLL ref
			 */
			cx25840_ग_लिखो4(client, 0x110, 0x00ec6bd6);

			/*
			 * SA_MCLK_SEL = 1
			 * SA_MCLK_DIV = 0x10 = 256/384 * AUX_PLL post dvivider
			 */
			cx25840_ग_लिखो(client, 0x127, 0x50);

			अगर (is_cx2583x(state))
				अवरोध;

			/* src1_ctl */
			/* 0x1.60cd = 44100/32000 */
			cx25840_ग_लिखो4(client, 0x8f8, 0x080160cd);

			/* src3/4/6_ctl */
			/* 0x1.7385 = 2 * (32000/44100) */
			cx25840_ग_लिखो4(client, 0x900, 0x08017385);
			cx25840_ग_लिखो4(client, 0x904, 0x08017385);
			cx25840_ग_लिखो4(client, 0x90c, 0x08017385);
			अवरोध;

		हाल 48000:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x0a, AUX PLL Post Divider = 0x18
			 */
			cx25840_ग_लिखो4(client, 0x108, 0x180a040f);

			/*
			 * VID_PLL Fraction (रेजिस्टर 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pre-postभागide
			 */

			/*
			 * AUX_PLL Fraction = 0x098d6e5
			 * 28636363 * 0xa.4c6b728/0x18 = 48000 * 256
			 * 295 MHz pre-postभागide
			 * FIXME 28636363 ref_freq करोesn't match VID PLL ref
			 */
			cx25840_ग_लिखो4(client, 0x110, 0x0098d6e5);

			/*
			 * SA_MCLK_SEL = 1
			 * SA_MCLK_DIV = 0x10 = 256/384 * AUX_PLL post dvivider
			 */
			cx25840_ग_लिखो(client, 0x127, 0x50);

			अगर (is_cx2583x(state))
				अवरोध;

			/* src1_ctl */
			/* 0x1.8000 = 48000/32000 */
			cx25840_ग_लिखो4(client, 0x8f8, 0x08018000);

			/* src3/4/6_ctl */
			/* 0x1.5555 = 2 * (32000/48000) */
			cx25840_ग_लिखो4(client, 0x900, 0x08015555);
			cx25840_ग_लिखो4(client, 0x904, 0x08015555);
			cx25840_ग_लिखो4(client, 0x90c, 0x08015555);
			अवरोध;
		पूर्ण
	पूर्ण

	state->audclk_freq = freq;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cx25836_set_audclk_freq(काष्ठा i2c_client *client, u32 freq)
अणु
	वापस cx25840_set_audclk_freq(client, freq);
पूर्ण

अटल पूर्णांक cx23885_set_audclk_freq(काष्ठा i2c_client *client, u32 freq)
अणु
	काष्ठा cx25840_state *state = to_state(i2c_get_clientdata(client));

	अगर (state->aud_input != CX25840_AUDIO_SERIAL) अणु
		चयन (freq) अणु
		हाल 32000:
		हाल 44100:
		हाल 48000:
			/* We करोn't have रेजिस्टर values
			 * so aव्योम destroying रेजिस्टरs. */
			/* FIXME वापस -EINVAL; */
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (freq) अणु
		हाल 32000:
		हाल 44100:
			/* We करोn't have रेजिस्टर values
			 * so aव्योम destroying रेजिस्टरs. */
			/* FIXME वापस -EINVAL; */
			अवरोध;

		हाल 48000:
			/* src1_ctl */
			/* 0x1.867c = 48000 / (2 * 28636360/8 * 2/455) */
			cx25840_ग_लिखो4(client, 0x8f8, 0x0801867c);

			/* src3/4/6_ctl */
			/* 0x1.4faa = (4 * 28636360/8 * 2/455) / 48000 */
			cx25840_ग_लिखो4(client, 0x900, 0x08014faa);
			cx25840_ग_लिखो4(client, 0x904, 0x08014faa);
			cx25840_ग_लिखो4(client, 0x90c, 0x08014faa);
			अवरोध;
		पूर्ण
	पूर्ण

	state->audclk_freq = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक cx231xx_set_audclk_freq(काष्ठा i2c_client *client, u32 freq)
अणु
	काष्ठा cx25840_state *state = to_state(i2c_get_clientdata(client));

	अगर (state->aud_input != CX25840_AUDIO_SERIAL) अणु
		चयन (freq) अणु
		हाल 32000:
			/* src3/4/6_ctl */
			/* 0x1.f77f = (4 * 28636360/8 * 2/455) / 32000 */
			cx25840_ग_लिखो4(client, 0x900, 0x0801f77f);
			cx25840_ग_लिखो4(client, 0x904, 0x0801f77f);
			cx25840_ग_लिखो4(client, 0x90c, 0x0801f77f);
			अवरोध;

		हाल 44100:
			/* src3/4/6_ctl */
			/* 0x1.6d59 = (4 * 28636360/8 * 2/455) / 44100 */
			cx25840_ग_लिखो4(client, 0x900, 0x08016d59);
			cx25840_ग_लिखो4(client, 0x904, 0x08016d59);
			cx25840_ग_लिखो4(client, 0x90c, 0x08016d59);
			अवरोध;

		हाल 48000:
			/* src3/4/6_ctl */
			/* 0x1.4faa = (4 * 28636360/8 * 2/455) / 48000 */
			cx25840_ग_लिखो4(client, 0x900, 0x08014faa);
			cx25840_ग_लिखो4(client, 0x904, 0x08014faa);
			cx25840_ग_लिखो4(client, 0x90c, 0x08014faa);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (freq) अणु
		/* FIXME These हालs make dअगरferent assumptions about audclk */
		हाल 32000:
			/* src1_ctl */
			/* 0x1.0000 = 32000/32000 */
			cx25840_ग_लिखो4(client, 0x8f8, 0x08010000);

			/* src3/4/6_ctl */
			/* 0x2.0000 = 2 * (32000/32000) */
			cx25840_ग_लिखो4(client, 0x900, 0x08020000);
			cx25840_ग_लिखो4(client, 0x904, 0x08020000);
			cx25840_ग_लिखो4(client, 0x90c, 0x08020000);
			अवरोध;

		हाल 44100:
			/* src1_ctl */
			/* 0x1.60cd = 44100/32000 */
			cx25840_ग_लिखो4(client, 0x8f8, 0x080160cd);

			/* src3/4/6_ctl */
			/* 0x1.7385 = 2 * (32000/44100) */
			cx25840_ग_लिखो4(client, 0x900, 0x08017385);
			cx25840_ग_लिखो4(client, 0x904, 0x08017385);
			cx25840_ग_लिखो4(client, 0x90c, 0x08017385);
			अवरोध;

		हाल 48000:
			/* src1_ctl */
			/* 0x1.867c = 48000 / (2 * 28636360/8 * 2/455) */
			cx25840_ग_लिखो4(client, 0x8f8, 0x0801867c);

			/* src3/4/6_ctl */
			/* 0x1.4faa = (4 * 28636360/8 * 2/455) / 48000 */
			cx25840_ग_लिखो4(client, 0x900, 0x08014faa);
			cx25840_ग_लिखो4(client, 0x904, 0x08014faa);
			cx25840_ग_लिखो4(client, 0x90c, 0x08014faa);
			अवरोध;
		पूर्ण
	पूर्ण

	state->audclk_freq = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक set_audclk_freq(काष्ठा i2c_client *client, u32 freq)
अणु
	काष्ठा cx25840_state *state = to_state(i2c_get_clientdata(client));

	अगर (freq != 32000 && freq != 44100 && freq != 48000)
		वापस -EINVAL;

	अगर (is_cx231xx(state))
		वापस cx231xx_set_audclk_freq(client, freq);

	अगर (is_cx2388x(state))
		वापस cx23885_set_audclk_freq(client, freq);

	अगर (is_cx2583x(state))
		वापस cx25836_set_audclk_freq(client, freq);

	वापस cx25840_set_audclk_freq(client, freq);
पूर्ण

व्योम cx25840_audio_set_path(काष्ठा i2c_client *client)
अणु
	काष्ठा cx25840_state *state = to_state(i2c_get_clientdata(client));

	अगर (!is_cx2583x(state)) अणु
		/* निश्चित soft reset */
		cx25840_and_or(client, 0x810, ~0x1, 0x01);

		/* stop microcontroller */
		cx25840_and_or(client, 0x803, ~0x10, 0);

		/* Mute everything to prevent the PFFT! */
		cx25840_ग_लिखो(client, 0x8d3, 0x1f);

		अगर (state->aud_input == CX25840_AUDIO_SERIAL) अणु
			/* Set Path1 to Serial Audio Input */
			cx25840_ग_लिखो4(client, 0x8d0, 0x01011012);

			/* The microcontroller should not be started क्रम the
			 * non-tuner inमाला_दो: स्वतःdetection is specअगरic क्रम
			 * TV audio. */
		पूर्ण अन्यथा अणु
			/* Set Path1 to Analog Demod Main Channel */
			cx25840_ग_लिखो4(client, 0x8d0, 0x1f063870);
		पूर्ण
	पूर्ण

	set_audclk_freq(client, state->audclk_freq);

	अगर (!is_cx2583x(state)) अणु
		अगर (state->aud_input != CX25840_AUDIO_SERIAL) अणु
			/* When the microcontroller detects the
			 * audio क्रमmat, it will unmute the lines */
			cx25840_and_or(client, 0x803, ~0x10, 0x10);
		पूर्ण

		/* deनिश्चित soft reset */
		cx25840_and_or(client, 0x810, ~0x1, 0x00);

		/* Ensure the controller is running when we निकास */
		अगर (is_cx2388x(state) || is_cx231xx(state))
			cx25840_and_or(client, 0x803, ~0x10, 0x10);
	पूर्ण
पूर्ण

अटल व्योम set_volume(काष्ठा i2c_client *client, पूर्णांक volume)
अणु
	पूर्णांक vol;

	/* Convert the volume to msp3400 values (0-127) */
	vol = volume >> 9;

	/* now scale it up to cx25840 values
	 * -114dB to -96dB maps to 0
	 * this should be 19, but in my testing that was 4dB too loud */
	अगर (vol <= 23) अणु
		vol = 0;
	पूर्ण अन्यथा अणु
		vol -= 23;
	पूर्ण

	/* PATH1_VOLUME */
	cx25840_ग_लिखो(client, 0x8d4, 228 - (vol * 2));
पूर्ण

अटल व्योम set_balance(काष्ठा i2c_client *client, पूर्णांक balance)
अणु
	पूर्णांक bal = balance >> 8;
	अगर (bal > 0x80) अणु
		/* PATH1_BAL_LEFT */
		cx25840_and_or(client, 0x8d5, 0x7f, 0x80);
		/* PATH1_BAL_LEVEL */
		cx25840_and_or(client, 0x8d5, ~0x7f, bal & 0x7f);
	पूर्ण अन्यथा अणु
		/* PATH1_BAL_LEFT */
		cx25840_and_or(client, 0x8d5, 0x7f, 0x00);
		/* PATH1_BAL_LEVEL */
		cx25840_and_or(client, 0x8d5, ~0x7f, 0x80 - bal);
	पूर्ण
पूर्ण

पूर्णांक cx25840_s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा cx25840_state *state = to_state(sd);
	पूर्णांक retval;

	अगर (!is_cx2583x(state))
		cx25840_and_or(client, 0x810, ~0x1, 1);
	अगर (state->aud_input != CX25840_AUDIO_SERIAL) अणु
		cx25840_and_or(client, 0x803, ~0x10, 0);
		cx25840_ग_लिखो(client, 0x8d3, 0x1f);
	पूर्ण
	retval = set_audclk_freq(client, freq);
	अगर (state->aud_input != CX25840_AUDIO_SERIAL)
		cx25840_and_or(client, 0x803, ~0x10, 0x10);
	अगर (!is_cx2583x(state))
		cx25840_and_or(client, 0x810, ~0x1, 0);
	वापस retval;
पूर्ण

अटल पूर्णांक cx25840_audio_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा cx25840_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_VOLUME:
		अगर (state->mute->val)
			set_volume(client, 0);
		अन्यथा
			set_volume(client, state->volume->val);
		अवरोध;
	हाल V4L2_CID_AUDIO_BASS:
		/* PATH1_EQ_BASS_VOL */
		cx25840_and_or(client, 0x8d9, ~0x3f,
					48 - (ctrl->val * 48 / 0xffff));
		अवरोध;
	हाल V4L2_CID_AUDIO_TREBLE:
		/* PATH1_EQ_TREBLE_VOL */
		cx25840_and_or(client, 0x8db, ~0x3f,
					48 - (ctrl->val * 48 / 0xffff));
		अवरोध;
	हाल V4L2_CID_AUDIO_BALANCE:
		set_balance(client, ctrl->val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा v4l2_ctrl_ops cx25840_audio_ctrl_ops = अणु
	.s_ctrl = cx25840_audio_s_ctrl,
पूर्ण;
