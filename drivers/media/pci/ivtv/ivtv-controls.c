<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    ioctl control functions
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-ioctl.h"
#समावेश "ivtv-controls.h"
#समावेश "ivtv-mailbox.h"

अटल पूर्णांक ivtv_s_stream_vbi_fmt(काष्ठा cx2341x_handler *cxhdl, u32 fmt)
अणु
	काष्ठा ivtv *itv = container_of(cxhdl, काष्ठा ivtv, cxhdl);

	/* First try to allocate sliced VBI buffers अगर needed. */
	अगर (fmt && itv->vbi.sliced_mpeg_data[0] == शून्य) अणु
		पूर्णांक i;

		क्रम (i = 0; i < IVTV_VBI_FRAMES; i++) अणु
			/* Yuck, hardcoded. Needs to be a define */
			itv->vbi.sliced_mpeg_data[i] = kदो_स्मृति(2049, GFP_KERNEL);
			अगर (itv->vbi.sliced_mpeg_data[i] == शून्य) अणु
				जबतक (--i >= 0) अणु
					kमुक्त(itv->vbi.sliced_mpeg_data[i]);
					itv->vbi.sliced_mpeg_data[i] = शून्य;
				पूर्ण
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
	पूर्ण

	itv->vbi.insert_mpeg = fmt;

	अगर (itv->vbi.insert_mpeg == 0) अणु
		वापस 0;
	पूर्ण
	/* Need sliced data क्रम mpeg insertion */
	अगर (ivtv_get_service_set(itv->vbi.sliced_in) == 0) अणु
		अगर (itv->is_60hz)
			itv->vbi.sliced_in->service_set = V4L2_SLICED_CAPTION_525;
		अन्यथा
			itv->vbi.sliced_in->service_set = V4L2_SLICED_WSS_625;
		ivtv_expand_service_set(itv->vbi.sliced_in, itv->is_50hz);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_s_video_encoding(काष्ठा cx2341x_handler *cxhdl, u32 val)
अणु
	काष्ठा ivtv *itv = container_of(cxhdl, काष्ठा ivtv, cxhdl);
	पूर्णांक is_mpeg1 = val == V4L2_MPEG_VIDEO_ENCODING_MPEG_1;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	/* fix videodecoder resolution */
	क्रमmat.क्रमmat.width = cxhdl->width / (is_mpeg1 ? 2 : 1);
	क्रमmat.क्रमmat.height = cxhdl->height;
	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_FIXED;
	v4l2_subdev_call(itv->sd_video, pad, set_fmt, शून्य, &क्रमmat);
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_s_audio_sampling_freq(काष्ठा cx2341x_handler *cxhdl, u32 idx)
अणु
	अटल स्थिर u32 freqs[3] = अणु 44100, 48000, 32000 पूर्ण;
	काष्ठा ivtv *itv = container_of(cxhdl, काष्ठा ivtv, cxhdl);

	/* The audio घड़ी of the digitizer must match the codec sample
	   rate otherwise you get some very strange effects. */
	अगर (idx < ARRAY_SIZE(freqs))
		ivtv_call_all(itv, audio, s_घड़ी_freq, freqs[idx]);
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_s_audio_mode(काष्ठा cx2341x_handler *cxhdl, u32 val)
अणु
	काष्ठा ivtv *itv = container_of(cxhdl, काष्ठा ivtv, cxhdl);

	itv->dualwatch_stereo_mode = val;
	वापस 0;
पूर्ण

स्थिर काष्ठा cx2341x_handler_ops ivtv_cxhdl_ops = अणु
	.s_audio_mode = ivtv_s_audio_mode,
	.s_audio_sampling_freq = ivtv_s_audio_sampling_freq,
	.s_video_encoding = ivtv_s_video_encoding,
	.s_stream_vbi_fmt = ivtv_s_stream_vbi_fmt,
पूर्ण;

पूर्णांक ivtv_g_pts_frame(काष्ठा ivtv *itv, s64 *pts, s64 *frame)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];

	अगर (test_bit(IVTV_F_I_VALID_DEC_TIMINGS, &itv->i_flags)) अणु
		*pts = (s64)((u64)itv->last_dec_timing[2] << 32) |
			(u64)itv->last_dec_timing[1];
		*frame = itv->last_dec_timing[0];
		वापस 0;
	पूर्ण
	*pts = 0;
	*frame = 0;
	अगर (atomic_पढ़ो(&itv->decoding)) अणु
		अगर (ivtv_api(itv, CX2341X_DEC_GET_TIMING_INFO, 5, data)) अणु
			IVTV_DEBUG_WARN("GET_TIMING: couldn't read clock\n");
			वापस -EIO;
		पूर्ण
		स_नकल(itv->last_dec_timing, data, माप(itv->last_dec_timing));
		set_bit(IVTV_F_I_VALID_DEC_TIMINGS, &itv->i_flags);
		*pts = (s64)((u64) data[2] << 32) | (u64) data[1];
		*frame = data[0];
		/*timing->scr = (u64) (((u64) data[4] << 32) | (u64) (data[3]));*/
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ivtv *itv = container_of(ctrl->handler, काष्ठा ivtv, cxhdl.hdl);

	चयन (ctrl->id) अणु
	/* V4L2_CID_MPEG_VIDEO_DEC_PTS and V4L2_CID_MPEG_VIDEO_DEC_FRAME
	   control cluster */
	हाल V4L2_CID_MPEG_VIDEO_DEC_PTS:
		वापस ivtv_g_pts_frame(itv, itv->ctrl_pts->p_new.p_s64,
					     itv->ctrl_frame->p_new.p_s64);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ivtv *itv = container_of(ctrl->handler, काष्ठा ivtv, cxhdl.hdl);

	चयन (ctrl->id) अणु
	/* V4L2_CID_MPEG_AUDIO_DEC_PLAYBACK and MULTILINGUAL_PLAYBACK
	   control cluster */
	हाल V4L2_CID_MPEG_AUDIO_DEC_PLAYBACK:
		itv->audio_stereo_mode = itv->ctrl_audio_playback->val - 1;
		itv->audio_bilingual_mode = itv->ctrl_audio_multilingual_playback->val - 1;
		ivtv_vapi(itv, CX2341X_DEC_SET_AUDIO_MODE, 2, itv->audio_bilingual_mode, itv->audio_stereo_mode);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा v4l2_ctrl_ops ivtv_hdl_out_ops = अणु
	.s_ctrl = ivtv_s_ctrl,
	.g_अस्थिर_ctrl = ivtv_g_अस्थिर_ctrl,
पूर्ण;
