<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#समावेश <linux/slab.h>

#समावेश "reg_helper.h"
#समावेश "dce_audio.h"
#समावेश "dce/dce_11_0_d.h"
#समावेश "dce/dce_11_0_sh_mask.h"

#घोषणा DCE_AUD(audio)\
	container_of(audio, काष्ठा dce_audio, base)

#घोषणा CTX \
	aud->base.ctx

#घोषणा DC_LOGGER_INIT()

#घोषणा REG(reg)\
	(aud->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	aud->shअगरts->field_name, aud->masks->field_name

#घोषणा IX_REG(reg)\
	ix ## reg

#घोषणा AZ_REG_READ(reg_name) \
		पढ़ो_indirect_azalia_reg(audio, IX_REG(reg_name))

#घोषणा AZ_REG_WRITE(reg_name, value) \
		ग_लिखो_indirect_azalia_reg(audio, IX_REG(reg_name), value)

अटल व्योम ग_लिखो_indirect_azalia_reg(काष्ठा audio *audio,
	uपूर्णांक32_t reg_index,
	uपूर्णांक32_t reg_data)
अणु
	काष्ठा dce_audio *aud = DCE_AUD(audio);

	/* AZALIA_F0_CODEC_ENDPOINT_INDEX  endpoपूर्णांक index  */
	REG_SET(AZALIA_F0_CODEC_ENDPOINT_INDEX, 0,
			AZALIA_ENDPOINT_REG_INDEX, reg_index);

	/* AZALIA_F0_CODEC_ENDPOINT_DATA  endpoपूर्णांक data  */
	REG_SET(AZALIA_F0_CODEC_ENDPOINT_DATA, 0,
			AZALIA_ENDPOINT_REG_DATA, reg_data);

	DC_LOG_HW_AUDIO("AUDIO:write_indirect_azalia_reg: index: %u  data: %u\n",
		reg_index, reg_data);
पूर्ण

अटल uपूर्णांक32_t पढ़ो_indirect_azalia_reg(काष्ठा audio *audio, uपूर्णांक32_t reg_index)
अणु
	काष्ठा dce_audio *aud = DCE_AUD(audio);

	uपूर्णांक32_t value = 0;

	/* AZALIA_F0_CODEC_ENDPOINT_INDEX  endpoपूर्णांक index  */
	REG_SET(AZALIA_F0_CODEC_ENDPOINT_INDEX, 0,
			AZALIA_ENDPOINT_REG_INDEX, reg_index);

	/* AZALIA_F0_CODEC_ENDPOINT_DATA  endpoपूर्णांक data  */
	value = REG_READ(AZALIA_F0_CODEC_ENDPOINT_DATA);

	DC_LOG_HW_AUDIO("AUDIO:read_indirect_azalia_reg: index: %u  data: %u\n",
		reg_index, value);

	वापस value;
पूर्ण

अटल bool is_audio_क्रमmat_supported(
	स्थिर काष्ठा audio_info *audio_info,
	क्रमागत audio_क्रमmat_code audio_क्रमmat_code,
	uपूर्णांक32_t *क्रमmat_index)
अणु
	uपूर्णांक32_t index;
	uपूर्णांक32_t max_channe_index = 0;
	bool found = false;

	अगर (audio_info == शून्य)
		वापस found;

	/* pass through whole array */
	क्रम (index = 0; index < audio_info->mode_count; index++) अणु
		अगर (audio_info->modes[index].क्रमmat_code == audio_क्रमmat_code) अणु
			अगर (found) अणु
				/* क्रमmat has multiply entries, choose one with
				 *  highst number of channels */
				अगर (audio_info->modes[index].channel_count >
		audio_info->modes[max_channe_index].channel_count) अणु
					max_channe_index = index;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* क्रमmat found, save it's index */
				found = true;
				max_channe_index = index;
			पूर्ण
		पूर्ण
	पूर्ण

	/* वापस index */
	अगर (found && क्रमmat_index != शून्य)
		*क्रमmat_index = max_channe_index;

	वापस found;
पूर्ण

/*For HDMI, calculate अगर specअगरied sample rates can fit पूर्णांकo a given timing */
अटल व्योम check_audio_bandwidth_hdmi(
	स्थिर काष्ठा audio_crtc_info *crtc_info,
	uपूर्णांक32_t channel_count,
	जोड़ audio_sample_rates *sample_rates)
अणु
	uपूर्णांक32_t samples;
	uपूर्णांक32_t  h_blank;
	bool limit_freq_to_48_khz = false;
	bool limit_freq_to_88_2_khz = false;
	bool limit_freq_to_96_khz = false;
	bool limit_freq_to_174_4_khz = false;
	अगर (!crtc_info)
		वापस;

	/* For two channels supported वापस whatever sink support,unmodअगरied*/
	अगर (channel_count > 2) अणु

		/* Based on HDMI spec 1.3 Table 7.5 */
		अगर ((crtc_info->requested_pixel_घड़ी_100Hz <= 270000) &&
		(crtc_info->v_active <= 576) &&
		!(crtc_info->पूर्णांकerlaced) &&
		!(crtc_info->pixel_repetition == 2 ||
		crtc_info->pixel_repetition == 4)) अणु
			limit_freq_to_48_khz = true;

		पूर्ण अन्यथा अगर ((crtc_info->requested_pixel_घड़ी_100Hz <= 270000) &&
				(crtc_info->v_active <= 576) &&
				(crtc_info->पूर्णांकerlaced) &&
				(crtc_info->pixel_repetition == 2)) अणु
			limit_freq_to_88_2_khz = true;

		पूर्ण अन्यथा अगर ((crtc_info->requested_pixel_घड़ी_100Hz <= 540000) &&
				(crtc_info->v_active <= 576) &&
				!(crtc_info->पूर्णांकerlaced)) अणु
			limit_freq_to_174_4_khz = true;
		पूर्ण
	पूर्ण

	/* Also करो some calculation क्रम the available Audio Bandwidth क्रम the
	 * 8 ch (i.e. क्रम the Layout 1 => ch > 2)
	 */
	h_blank = crtc_info->h_total - crtc_info->h_active;

	अगर (crtc_info->pixel_repetition)
		h_blank *= crtc_info->pixel_repetition;

	/*based on HDMI spec 1.3 Table 7.5 */
	h_blank -= 58;
	/*क्रम Control Period */
	h_blank -= 16;

	samples = h_blank * 10;
	/* Number of Audio Packets (multiplied by 10) per Line (क्रम 8 ch number
	 * of Audio samples per line multiplied by 10 - Layout 1)
	 */
	samples /= 32;
	samples *= crtc_info->v_active;
	/*Number of samples multiplied by 10, per second */
	samples *= crtc_info->refresh_rate;
	/*Number of Audio samples per second */
	samples /= 10;

	/* @toकरो करो it after deep color is implemented
	 * 8xx - deep color bandwidth scaling
	 * Extra bandwidth is avaliable in deep color b/c link runs faster than
	 * pixel rate. This has the effect of allowing more पंचांगds अक्षरacters to
	 * be transmitted during blank
	 */

	चयन (crtc_info->color_depth) अणु
	हाल COLOR_DEPTH_888:
		samples *= 4;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		samples *= 5;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		samples *= 6;
		अवरोध;
	शेष:
		samples *= 4;
		अवरोध;
	पूर्ण

	samples /= 4;

	/*check limitation*/
	अगर (samples < 88200)
		limit_freq_to_48_khz = true;
	अन्यथा अगर (samples < 96000)
		limit_freq_to_88_2_khz = true;
	अन्यथा अगर (samples < 176400)
		limit_freq_to_96_khz = true;
	अन्यथा अगर (samples < 192000)
		limit_freq_to_174_4_khz = true;

	अगर (sample_rates != शून्य) अणु
		/* limit frequencies */
		अगर (limit_freq_to_174_4_khz)
			sample_rates->rate.RATE_192 = 0;

		अगर (limit_freq_to_96_khz) अणु
			sample_rates->rate.RATE_192 = 0;
			sample_rates->rate.RATE_176_4 = 0;
		पूर्ण
		अगर (limit_freq_to_88_2_khz) अणु
			sample_rates->rate.RATE_192 = 0;
			sample_rates->rate.RATE_176_4 = 0;
			sample_rates->rate.RATE_96 = 0;
		पूर्ण
		अगर (limit_freq_to_48_khz) अणु
			sample_rates->rate.RATE_192 = 0;
			sample_rates->rate.RATE_176_4 = 0;
			sample_rates->rate.RATE_96 = 0;
			sample_rates->rate.RATE_88_2 = 0;
		पूर्ण
	पूर्ण
पूर्ण

/*For DP SST, calculate अगर specअगरied sample rates can fit पूर्णांकo a given timing */
अटल व्योम check_audio_bandwidth_dpsst(
	स्थिर काष्ठा audio_crtc_info *crtc_info,
	uपूर्णांक32_t channel_count,
	जोड़ audio_sample_rates *sample_rates)
अणु
	/* करो nothing */
पूर्ण

/*For DP MST, calculate अगर specअगरied sample rates can fit पूर्णांकo a given timing */
अटल व्योम check_audio_bandwidth_dpmst(
	स्थिर काष्ठा audio_crtc_info *crtc_info,
	uपूर्णांक32_t channel_count,
	जोड़ audio_sample_rates *sample_rates)
अणु
	/* करो nothing  */
पूर्ण

अटल व्योम check_audio_bandwidth(
	स्थिर काष्ठा audio_crtc_info *crtc_info,
	uपूर्णांक32_t channel_count,
	क्रमागत संकेत_type संकेत,
	जोड़ audio_sample_rates *sample_rates)
अणु
	चयन (संकेत) अणु
	हाल SIGNAL_TYPE_HDMI_TYPE_A:
		check_audio_bandwidth_hdmi(
			crtc_info, channel_count, sample_rates);
		अवरोध;
	हाल SIGNAL_TYPE_EDP:
	हाल SIGNAL_TYPE_DISPLAY_PORT:
		check_audio_bandwidth_dpsst(
			crtc_info, channel_count, sample_rates);
		अवरोध;
	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		check_audio_bandwidth_dpmst(
			crtc_info, channel_count, sample_rates);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/* expose/not expose HBR capability to Audio driver */
अटल व्योम set_high_bit_rate_capable(
	काष्ठा audio *audio,
	bool capable)
अणु
	uपूर्णांक32_t value = 0;

	/* set high bit rate audio capable*/
	value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_HBR);

	set_reg_field_value(value, capable,
		AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_HBR,
		HBR_CAPABLE);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_HBR, value);
पूर्ण

/* set video latency in in ms/2+1 */
अटल व्योम set_video_latency(
	काष्ठा audio *audio,
	पूर्णांक latency_in_ms)
अणु
	uपूर्णांक32_t value = 0;

	अगर ((latency_in_ms < 0) || (latency_in_ms > 255))
		वापस;

	value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC);

	set_reg_field_value(value, latency_in_ms,
		AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC,
		VIDEO_LIPSYNC);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC,
		value);
पूर्ण

/* set audio latency in in ms/2+1 */
अटल व्योम set_audio_latency(
	काष्ठा audio *audio,
	पूर्णांक latency_in_ms)
अणु
	uपूर्णांक32_t value = 0;

	अगर (latency_in_ms < 0)
		latency_in_ms = 0;

	अगर (latency_in_ms > 255)
		latency_in_ms = 255;

	value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC);

	set_reg_field_value(value, latency_in_ms,
		AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC,
		AUDIO_LIPSYNC);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC,
		value);
पूर्ण

व्योम dce_aud_az_enable(काष्ठा audio *audio)
अणु
	uपूर्णांक32_t value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL);
	DC_LOGGER_INIT();

	set_reg_field_value(value, 1,
			    AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			    CLOCK_GATING_DISABLE);
	set_reg_field_value(value, 1,
			    AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			    AUDIO_ENABLED);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL, value);
	set_reg_field_value(value, 0,
			AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			CLOCK_GATING_DISABLE);
	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL, value);

	DC_LOG_HW_AUDIO("\n\t========= AUDIO:dce_aud_az_enable: index: %u  data: 0x%x\n",
			audio->inst, value);
पूर्ण

व्योम dce_aud_az_disable(काष्ठा audio *audio)
अणु
	uपूर्णांक32_t value;
	DC_LOGGER_INIT();

	value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL);
	set_reg_field_value(value, 1,
			AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			CLOCK_GATING_DISABLE);
	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL, value);

	set_reg_field_value(value, 0,
		AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
		AUDIO_ENABLED);
	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL, value);

	set_reg_field_value(value, 0,
			AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			CLOCK_GATING_DISABLE);
	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL, value);
	value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL);
	DC_LOG_HW_AUDIO("\n\t========= AUDIO:dce_aud_az_disable: index: %u  data: 0x%x\n",
			audio->inst, value);
पूर्ण

व्योम dce_aud_az_configure(
	काष्ठा audio *audio,
	क्रमागत संकेत_type संकेत,
	स्थिर काष्ठा audio_crtc_info *crtc_info,
	स्थिर काष्ठा audio_info *audio_info)
अणु
	काष्ठा dce_audio *aud = DCE_AUD(audio);

	uपूर्णांक32_t speakers = audio_info->flags.info.ALLSPEAKERS;
	uपूर्णांक32_t value;
	uपूर्णांक32_t field = 0;
	क्रमागत audio_क्रमmat_code audio_क्रमmat_code;
	uपूर्णांक32_t क्रमmat_index;
	uपूर्णांक32_t index;
	bool is_ac3_supported = false;
	जोड़ audio_sample_rates sample_rate;
	uपूर्णांक32_t म_माप = 0;
	value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL);
	set_reg_field_value(value, 1,
			AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			CLOCK_GATING_DISABLE);
	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL, value);

	/* Speaker Allocation */
	/*
	uपूर्णांक32_t value;
	uपूर्णांक32_t field = 0;*/
	value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER);

	set_reg_field_value(value,
		speakers,
		AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER,
		SPEAKER_ALLOCATION);

	/* LFE_PLAYBACK_LEVEL = LFEPBL
	 * LFEPBL = 0 : Unknown or refer to other inक्रमmation
	 * LFEPBL = 1 : 0dB playback
	 * LFEPBL = 2 : +10dB playback
	 * LFE_BL = 3 : Reserved
	 */
	set_reg_field_value(value,
		0,
		AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER,
		LFE_PLAYBACK_LEVEL);
	/* toकरो: according to reg spec LFE_PLAYBACK_LEVEL is पढ़ो only.
	 *  why are we writing to it?  DCE8 करोes not ग_लिखो this */


	set_reg_field_value(value,
		0,
		AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER,
		HDMI_CONNECTION);

	set_reg_field_value(value,
		0,
		AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER,
		DP_CONNECTION);

	field = get_reg_field_value(value,
			AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER,
			EXTRA_CONNECTION_INFO);

	field &= ~0x1;

	set_reg_field_value(value,
		field,
		AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER,
		EXTRA_CONNECTION_INFO);

	/* set audio क्रम output संकेत */
	चयन (संकेत) अणु
	हाल SIGNAL_TYPE_HDMI_TYPE_A:
		set_reg_field_value(value,
			1,
			AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER,
			HDMI_CONNECTION);

		अवरोध;

	हाल SIGNAL_TYPE_EDP:
	हाल SIGNAL_TYPE_DISPLAY_PORT:
	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		set_reg_field_value(value,
			1,
			AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER,
			DP_CONNECTION);
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER, value);

	/*  Audio Descriptors   */
	/* pass through all क्रमmats */
	क्रम (क्रमmat_index = 0; क्रमmat_index < AUDIO_FORMAT_CODE_COUNT;
			क्रमmat_index++) अणु
		audio_क्रमmat_code =
			(AUDIO_FORMAT_CODE_FIRST + क्रमmat_index);

		/* those are unsupported, skip programming */
		अगर (audio_क्रमmat_code == AUDIO_FORMAT_CODE_1BITAUDIO ||
			audio_क्रमmat_code == AUDIO_FORMAT_CODE_DST)
			जारी;

		value = 0;

		/* check अगर supported */
		अगर (is_audio_क्रमmat_supported(
				audio_info, audio_क्रमmat_code, &index)) अणु
			स्थिर काष्ठा audio_mode *audio_mode =
					&audio_info->modes[index];
			जोड़ audio_sample_rates sample_rates =
					audio_mode->sample_rates;
			uपूर्णांक8_t byte2 = audio_mode->max_bit_rate;

			/* adjust specअगरic properties */
			चयन (audio_क्रमmat_code) अणु
			हाल AUDIO_FORMAT_CODE_LINEARPCM: अणु
				check_audio_bandwidth(
					crtc_info,
					audio_mode->channel_count,
					संकेत,
					&sample_rates);

				byte2 = audio_mode->sample_size;

				set_reg_field_value(value,
						sample_rates.all,
						AZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR0,
						SUPPORTED_FREQUENCIES_STEREO);
				पूर्ण
				अवरोध;
			हाल AUDIO_FORMAT_CODE_AC3:
				is_ac3_supported = true;
				अवरोध;
			हाल AUDIO_FORMAT_CODE_DOLBYDIGITALPLUS:
			हाल AUDIO_FORMAT_CODE_DTS_HD:
			हाल AUDIO_FORMAT_CODE_MAT_MLP:
			हाल AUDIO_FORMAT_CODE_DST:
			हाल AUDIO_FORMAT_CODE_WMAPRO:
				byte2 = audio_mode->venकरोr_specअगरic;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			/* fill audio क्रमmat data */
			set_reg_field_value(value,
					audio_mode->channel_count - 1,
					AZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR0,
					MAX_CHANNELS);

			set_reg_field_value(value,
					sample_rates.all,
					AZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR0,
					SUPPORTED_FREQUENCIES);

			set_reg_field_value(value,
					byte2,
					AZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR0,
					DESCRIPTOR_BYTE_2);
		पूर्ण /* अगर */

		AZ_REG_WRITE(
				AZALIA_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR0 + क्रमmat_index,
				value);
	पूर्ण /* क्रम */

	अगर (is_ac3_supported)
		/* toकरो: this reg global.  why program global रेजिस्टर? */
		REG_WRITE(AZALIA_F0_CODEC_FUNCTION_PARAMETER_STREAM_FORMATS,
				0x05);

	/* check क्रम 192khz/8-Ch support क्रम HBR requirements */
	sample_rate.all = 0;
	sample_rate.rate.RATE_192 = 1;

	check_audio_bandwidth(
		crtc_info,
		8,
		संकेत,
		&sample_rate);

	set_high_bit_rate_capable(audio, sample_rate.rate.RATE_192);

	/* Audio and Video Lipsync */
	set_video_latency(audio, audio_info->video_latency);
	set_audio_latency(audio, audio_info->audio_latency);

	value = 0;
	set_reg_field_value(value, audio_info->manufacture_id,
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO0,
		MANUFACTURER_ID);

	set_reg_field_value(value, audio_info->product_id,
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO0,
		PRODUCT_ID);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO0,
		value);

	value = 0;

	/*get display name string length */
	जबतक (audio_info->display_name[म_माप++] != '\0') अणु
		अगर (म_माप >=
		MAX_HW_AUDIO_INFO_DISPLAY_NAME_SIZE_IN_CHARS)
			अवरोध;
		पूर्ण
	set_reg_field_value(value, म_माप,
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO1,
		SINK_DESCRIPTION_LEN);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO1,
		value);
	DC_LOG_HW_AUDIO("\n\tAUDIO:az_configure: index: %u data, 0x%x, displayName %s: \n",
		audio->inst, value, audio_info->display_name);

	/*
	*ग_लिखो the port ID:
	*PORT_ID0 = display index
	*PORT_ID1 = 16bit BDF
	*(क्रमmat MSB->LSB: 8bit Bus, 5bit Device, 3bit Function)
	*/

	value = 0;

	set_reg_field_value(value, audio_info->port_id[0],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO2,
		PORT_ID0);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO2, value);

	value = 0;
	set_reg_field_value(value, audio_info->port_id[1],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO3,
		PORT_ID1);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO3, value);

	/*ग_लिखो the 18 अक्षर monitor string */

	value = 0;
	set_reg_field_value(value, audio_info->display_name[0],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO4,
		DESCRIPTION0);

	set_reg_field_value(value, audio_info->display_name[1],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO4,
		DESCRIPTION1);

	set_reg_field_value(value, audio_info->display_name[2],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO4,
		DESCRIPTION2);

	set_reg_field_value(value, audio_info->display_name[3],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO4,
		DESCRIPTION3);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO4, value);

	value = 0;
	set_reg_field_value(value, audio_info->display_name[4],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO5,
		DESCRIPTION4);

	set_reg_field_value(value, audio_info->display_name[5],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO5,
		DESCRIPTION5);

	set_reg_field_value(value, audio_info->display_name[6],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO5,
		DESCRIPTION6);

	set_reg_field_value(value, audio_info->display_name[7],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO5,
		DESCRIPTION7);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO5, value);

	value = 0;
	set_reg_field_value(value, audio_info->display_name[8],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO6,
		DESCRIPTION8);

	set_reg_field_value(value, audio_info->display_name[9],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO6,
		DESCRIPTION9);

	set_reg_field_value(value, audio_info->display_name[10],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO6,
		DESCRIPTION10);

	set_reg_field_value(value, audio_info->display_name[11],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO6,
		DESCRIPTION11);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO6, value);

	value = 0;
	set_reg_field_value(value, audio_info->display_name[12],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO7,
		DESCRIPTION12);

	set_reg_field_value(value, audio_info->display_name[13],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO7,
		DESCRIPTION13);

	set_reg_field_value(value, audio_info->display_name[14],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO7,
		DESCRIPTION14);

	set_reg_field_value(value, audio_info->display_name[15],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO7,
		DESCRIPTION15);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO7, value);

	value = 0;
	set_reg_field_value(value, audio_info->display_name[16],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO8,
		DESCRIPTION16);

	set_reg_field_value(value, audio_info->display_name[17],
		AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO8,
		DESCRIPTION17);

	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_SINK_INFO8, value);
	value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL);
	set_reg_field_value(value, 0,
			AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			CLOCK_GATING_DISABLE);
	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL, value);
पूर्ण

/*
* toकरो: wall clk related functionality probably beदीर्घ to घड़ी_src.
*/

/* search pixel घड़ी value क्रम Azalia HDMI Audio */
अटल व्योम get_azalia_घड़ी_info_hdmi(
	uपूर्णांक32_t crtc_pixel_घड़ी_100hz,
	uपूर्णांक32_t actual_pixel_घड़ी_100Hz,
	काष्ठा azalia_घड़ी_info *azalia_घड़ी_info)
अणु
	/* audio_dto_phase= 24 * 10,000;
	 *   24MHz in [100Hz] units */
	azalia_घड़ी_info->audio_dto_phase =
			24 * 10000;

	/* audio_dto_module = PCLKFrequency * 10,000;
	 *  [khz] -> [100Hz] */
	azalia_घड़ी_info->audio_dto_module =
			actual_pixel_घड़ी_100Hz;
पूर्ण

अटल व्योम get_azalia_घड़ी_info_dp(
	uपूर्णांक32_t requested_pixel_घड़ी_100Hz,
	स्थिर काष्ठा audio_pll_info *pll_info,
	काष्ठा azalia_घड़ी_info *azalia_घड़ी_info)
अणु
	/* Reported dpDtoSourceClockInkhz value क्रम
	 * DCE8 alपढ़ोy adjusted क्रम SS, करो not need any
	 * adjusपंचांगent here anymore
	 */

	/*audio_dto_phase = 24 * 10,000;
	 * 24MHz in [100Hz] units */
	azalia_घड़ी_info->audio_dto_phase = 24 * 10000;

	/*audio_dto_module = dpDtoSourceClockInkhz * 10,000;
	 *  [khz] ->[100Hz] */
	azalia_घड़ी_info->audio_dto_module =
		pll_info->dp_dto_source_घड़ी_in_khz * 10;
पूर्ण

व्योम dce_aud_wall_dto_setup(
	काष्ठा audio *audio,
	क्रमागत संकेत_type संकेत,
	स्थिर काष्ठा audio_crtc_info *crtc_info,
	स्थिर काष्ठा audio_pll_info *pll_info)
अणु
	काष्ठा dce_audio *aud = DCE_AUD(audio);

	काष्ठा azalia_घड़ी_info घड़ी_info = अणु 0 पूर्ण;

	अगर (dc_is_hdmi_पंचांगds_संकेत(संकेत)) अणु
		uपूर्णांक32_t src_sel;

		/*DTO0 Programming goal:
		-generate 24MHz, 128*Fs from 24MHz
		-use DTO0 when an active HDMI port is connected
		(optionally a DP is connected) */

		/* calculate DTO settings */
		get_azalia_घड़ी_info_hdmi(
			crtc_info->requested_pixel_घड़ी_100Hz,
			crtc_info->calculated_pixel_घड़ी_100Hz,
			&घड़ी_info);

		DC_LOG_HW_AUDIO("\n%s:Input::requested_pixel_clock_100Hz = %d"\
				"calculated_pixel_clock_100Hz =%d\n"\
				"audio_dto_module = %d audio_dto_phase =%d \n\n", __func__,\
				crtc_info->requested_pixel_घड़ी_100Hz,\
				crtc_info->calculated_pixel_घड़ी_100Hz,\
				घड़ी_info.audio_dto_module,\
				घड़ी_info.audio_dto_phase);

		/* On TN/SI, Program DTO source select and DTO select beक्रमe
		programming DTO modulo and DTO phase. These bits must be
		programmed first, otherwise there will be no HDMI audio at boot
		up. This is a HW sequence change (dअगरferent from old ASICs).
		Caution when changing this programming sequence.

		HDMI enabled, using DTO0
		program master CRTC क्रम DTO0 */
		src_sel = pll_info->dto_source - DTO_SOURCE_ID0;
		REG_UPDATE_2(DCCG_AUDIO_DTO_SOURCE,
			DCCG_AUDIO_DTO0_SOURCE_SEL, src_sel,
			DCCG_AUDIO_DTO_SEL, 0);

		/* module */
		REG_UPDATE(DCCG_AUDIO_DTO0_MODULE,
			DCCG_AUDIO_DTO0_MODULE, घड़ी_info.audio_dto_module);

		/* phase */
		REG_UPDATE(DCCG_AUDIO_DTO0_PHASE,
			DCCG_AUDIO_DTO0_PHASE, घड़ी_info.audio_dto_phase);
	पूर्ण अन्यथा अणु
		/*DTO1 Programming goal:
		-generate 24MHz, 512*Fs, 128*Fs from 24MHz
		-शेष is to used DTO1, and चयन to DTO0 when an audio
		master HDMI port is connected
		-use as शेष क्रम DP

		calculate DTO settings */
		get_azalia_घड़ी_info_dp(
			crtc_info->requested_pixel_घड़ी_100Hz,
			pll_info,
			&घड़ी_info);

		/* Program DTO select beक्रमe programming DTO modulo and DTO
		phase. शेष to use DTO1 */

		REG_UPDATE(DCCG_AUDIO_DTO_SOURCE,
				DCCG_AUDIO_DTO_SEL, 1);

			/* DCCG_AUDIO_DTO2_USE_512FBR_DTO, 1)
			 * Select 512fs क्रम DP TODO: web रेजिस्टर definition
			 * करोes not match रेजिस्टर header file
			 * DCE11 version it's commented out while DCE8 it's set to 1
			*/

		/* module */
		REG_UPDATE(DCCG_AUDIO_DTO1_MODULE,
				DCCG_AUDIO_DTO1_MODULE, घड़ी_info.audio_dto_module);

		/* phase */
		REG_UPDATE(DCCG_AUDIO_DTO1_PHASE,
				DCCG_AUDIO_DTO1_PHASE, घड़ी_info.audio_dto_phase);

		REG_UPDATE(DCCG_AUDIO_DTO_SOURCE,
				DCCG_AUDIO_DTO2_USE_512FBR_DTO, 1);

	पूर्ण
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल व्योम dce60_aud_wall_dto_setup(
	काष्ठा audio *audio,
	क्रमागत संकेत_type संकेत,
	स्थिर काष्ठा audio_crtc_info *crtc_info,
	स्थिर काष्ठा audio_pll_info *pll_info)
अणु
	काष्ठा dce_audio *aud = DCE_AUD(audio);

	काष्ठा azalia_घड़ी_info घड़ी_info = अणु 0 पूर्ण;

	अगर (dc_is_hdmi_संकेत(संकेत)) अणु
		uपूर्णांक32_t src_sel;

		/*DTO0 Programming goal:
		-generate 24MHz, 128*Fs from 24MHz
		-use DTO0 when an active HDMI port is connected
		(optionally a DP is connected) */

		/* calculate DTO settings */
		get_azalia_घड़ी_info_hdmi(
			crtc_info->requested_pixel_घड़ी_100Hz,
			crtc_info->calculated_pixel_घड़ी_100Hz,
			&घड़ी_info);

		DC_LOG_HW_AUDIO("\n%s:Input::requested_pixel_clock_100Hz = %d"\
				"calculated_pixel_clock_100Hz =%d\n"\
				"audio_dto_module = %d audio_dto_phase =%d \n\n", __func__,\
				crtc_info->requested_pixel_घड़ी_100Hz,\
				crtc_info->calculated_pixel_घड़ी_100Hz,\
				घड़ी_info.audio_dto_module,\
				घड़ी_info.audio_dto_phase);

		/* On TN/SI, Program DTO source select and DTO select beक्रमe
		programming DTO modulo and DTO phase. These bits must be
		programmed first, otherwise there will be no HDMI audio at boot
		up. This is a HW sequence change (dअगरferent from old ASICs).
		Caution when changing this programming sequence.

		HDMI enabled, using DTO0
		program master CRTC क्रम DTO0 */
		src_sel = pll_info->dto_source - DTO_SOURCE_ID0;
		REG_UPDATE_2(DCCG_AUDIO_DTO_SOURCE,
			DCCG_AUDIO_DTO0_SOURCE_SEL, src_sel,
			DCCG_AUDIO_DTO_SEL, 0);

		/* module */
		REG_UPDATE(DCCG_AUDIO_DTO0_MODULE,
			DCCG_AUDIO_DTO0_MODULE, घड़ी_info.audio_dto_module);

		/* phase */
		REG_UPDATE(DCCG_AUDIO_DTO0_PHASE,
			DCCG_AUDIO_DTO0_PHASE, घड़ी_info.audio_dto_phase);
	पूर्ण अन्यथा अणु
		/*DTO1 Programming goal:
		-generate 24MHz, 128*Fs from 24MHz (DCE6 करोes not support 512*Fs)
		-शेष is to used DTO1, and चयन to DTO0 when an audio
		master HDMI port is connected
		-use as शेष क्रम DP

		calculate DTO settings */
		get_azalia_घड़ी_info_dp(
			crtc_info->requested_pixel_घड़ी_100Hz,
			pll_info,
			&घड़ी_info);

		/* Program DTO select beक्रमe programming DTO modulo and DTO
		phase. शेष to use DTO1 */

		REG_UPDATE(DCCG_AUDIO_DTO_SOURCE,
				DCCG_AUDIO_DTO_SEL, 1);

			/* DCCG_AUDIO_DTO2_USE_512FBR_DTO, 1)
			 * Cannot select 512fs क्रम DP
			 *
			 * DCE6 has no DCCG_AUDIO_DTO2_USE_512FBR_DTO mask
			*/

		/* module */
		REG_UPDATE(DCCG_AUDIO_DTO1_MODULE,
				DCCG_AUDIO_DTO1_MODULE, घड़ी_info.audio_dto_module);

		/* phase */
		REG_UPDATE(DCCG_AUDIO_DTO1_PHASE,
				DCCG_AUDIO_DTO1_PHASE, घड़ी_info.audio_dto_phase);

		/* DCE6 has no DCCG_AUDIO_DTO2_USE_512FBR_DTO mask in DCCG_AUDIO_DTO_SOURCE reg */

	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल bool dce_aud_endpoपूर्णांक_valid(काष्ठा audio *audio)
अणु
	uपूर्णांक32_t value;
	uपूर्णांक32_t port_connectivity;

	value = AZ_REG_READ(
			AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT);

	port_connectivity = get_reg_field_value(value,
			AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT,
			PORT_CONNECTIVITY);

	वापस !(port_connectivity == 1);
पूर्ण

/* initialize HW state */
व्योम dce_aud_hw_init(
		काष्ठा audio *audio)
अणु
	uपूर्णांक32_t value;
	काष्ठा dce_audio *aud = DCE_AUD(audio);

	/* we only need to program the following रेजिस्टरs once, so we only करो
	it क्रम the inst 0*/
	अगर (audio->inst != 0)
		वापस;

	/* Suport R5 - 32khz
	 * Suport R6 - 44.1khz
	 * Suport R7 - 48khz
	 */
	/*disable घड़ी gating beक्रमe ग_लिखो to endpoपूर्णांक रेजिस्टर*/
	value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL);
	set_reg_field_value(value, 1,
			AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			CLOCK_GATING_DISABLE);
	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL, value);
	REG_UPDATE(AZALIA_F0_CODEC_FUNCTION_PARAMETER_SUPPORTED_SIZE_RATES,
			AUDIO_RATE_CAPABILITIES, 0x70);

	/*Keep alive bit to verअगरy HW block in BU. */
	REG_UPDATE_2(AZALIA_F0_CODEC_FUNCTION_PARAMETER_POWER_STATES,
			CLKSTOP, 1,
			EPSS, 1);
	set_reg_field_value(value, 0,
			AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			CLOCK_GATING_DISABLE);
	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL, value);
पूर्ण

अटल स्थिर काष्ठा audio_funcs funcs = अणु
	.endpoपूर्णांक_valid = dce_aud_endpoपूर्णांक_valid,
	.hw_init = dce_aud_hw_init,
	.wall_dto_setup = dce_aud_wall_dto_setup,
	.az_enable = dce_aud_az_enable,
	.az_disable = dce_aud_az_disable,
	.az_configure = dce_aud_az_configure,
	.destroy = dce_aud_destroy,
पूर्ण;

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल स्थिर काष्ठा audio_funcs dce60_funcs = अणु
	.endpoपूर्णांक_valid = dce_aud_endpoपूर्णांक_valid,
	.hw_init = dce_aud_hw_init,
	.wall_dto_setup = dce60_aud_wall_dto_setup,
	.az_enable = dce_aud_az_enable,
	.az_disable = dce_aud_az_disable,
	.az_configure = dce_aud_az_configure,
	.destroy = dce_aud_destroy,
पूर्ण;
#पूर्ण_अगर

व्योम dce_aud_destroy(काष्ठा audio **audio)
अणु
	काष्ठा dce_audio *aud = DCE_AUD(*audio);

	kमुक्त(aud);
	*audio = शून्य;
पूर्ण

काष्ठा audio *dce_audio_create(
		काष्ठा dc_context *ctx,
		अचिन्हित पूर्णांक inst,
		स्थिर काष्ठा dce_audio_रेजिस्टरs *reg,
		स्थिर काष्ठा dce_audio_shअगरt *shअगरts,
		स्थिर काष्ठा dce_audio_mask *masks
		)
अणु
	काष्ठा dce_audio *audio = kzalloc(माप(*audio), GFP_KERNEL);

	अगर (audio == शून्य) अणु
		ASSERT_CRITICAL(audio);
		वापस शून्य;
	पूर्ण

	audio->base.ctx = ctx;
	audio->base.inst = inst;
	audio->base.funcs = &funcs;

	audio->regs = reg;
	audio->shअगरts = shअगरts;
	audio->masks = masks;
	वापस &audio->base;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
काष्ठा audio *dce60_audio_create(
		काष्ठा dc_context *ctx,
		अचिन्हित पूर्णांक inst,
		स्थिर काष्ठा dce_audio_रेजिस्टरs *reg,
		स्थिर काष्ठा dce_audio_shअगरt *shअगरts,
		स्थिर काष्ठा dce_audio_mask *masks
		)
अणु
	काष्ठा dce_audio *audio = kzalloc(माप(*audio), GFP_KERNEL);

	अगर (audio == शून्य) अणु
		ASSERT_CRITICAL(audio);
		वापस शून्य;
	पूर्ण

	audio->base.ctx = ctx;
	audio->base.inst = inst;
	audio->base.funcs = &dce60_funcs;

	audio->regs = reg;
	audio->shअगरts = shअगरts;
	audio->masks = masks;
	वापस &audio->base;
पूर्ण
#पूर्ण_अगर
