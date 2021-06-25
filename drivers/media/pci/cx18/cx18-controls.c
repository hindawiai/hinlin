<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 ioctl control functions
 *
 *  Derived from ivtv-controls.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "cx18-driver.h"
#समावेश "cx18-cards.h"
#समावेश "cx18-ioctl.h"
#समावेश "cx18-audio.h"
#समावेश "cx18-mailbox.h"
#समावेश "cx18-controls.h"

अटल पूर्णांक cx18_s_stream_vbi_fmt(काष्ठा cx2341x_handler *cxhdl, u32 fmt)
अणु
	काष्ठा cx18 *cx = container_of(cxhdl, काष्ठा cx18, cxhdl);
	पूर्णांक type = cxhdl->stream_type->val;

	अगर (atomic_पढ़ो(&cx->ana_capturing) > 0)
		वापस -EBUSY;

	अगर (fmt != V4L2_MPEG_STREAM_VBI_FMT_IVTV ||
	    !(type == V4L2_MPEG_STREAM_TYPE_MPEG2_PS ||
	      type == V4L2_MPEG_STREAM_TYPE_MPEG2_DVD ||
	      type == V4L2_MPEG_STREAM_TYPE_MPEG2_SVCD)) अणु
		/* Only IVTV fmt VBI insertion & only MPEG-2 PS type streams */
		cx->vbi.insert_mpeg = V4L2_MPEG_STREAM_VBI_FMT_NONE;
		CX18_DEBUG_INFO("disabled insertion of sliced VBI data into the MPEG stream\n");
		वापस 0;
	पूर्ण

	/* Allocate sliced VBI buffers अगर needed. */
	अगर (cx->vbi.sliced_mpeg_data[0] == शून्य) अणु
		पूर्णांक i;

		क्रम (i = 0; i < CX18_VBI_FRAMES; i++) अणु
			cx->vbi.sliced_mpeg_data[i] =
			       kदो_स्मृति(CX18_SLICED_MPEG_DATA_BUFSZ, GFP_KERNEL);
			अगर (cx->vbi.sliced_mpeg_data[i] == शून्य) अणु
				जबतक (--i >= 0) अणु
					kमुक्त(cx->vbi.sliced_mpeg_data[i]);
					cx->vbi.sliced_mpeg_data[i] = शून्य;
				पूर्ण
				cx->vbi.insert_mpeg =
						  V4L2_MPEG_STREAM_VBI_FMT_NONE;
				CX18_WARN("Unable to allocate buffers for sliced VBI data insertion\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
	पूर्ण

	cx->vbi.insert_mpeg = fmt;
	CX18_DEBUG_INFO("enabled insertion of sliced VBI data into the MPEG PS,when sliced VBI is enabled\n");

	/*
	 * If our current settings have no lines set क्रम capture, store a valid,
	 * शेष set of service lines to capture, in our current settings.
	 */
	अगर (cx18_get_service_set(cx->vbi.sliced_in) == 0) अणु
		अगर (cx->is_60hz)
			cx->vbi.sliced_in->service_set =
							V4L2_SLICED_CAPTION_525;
		अन्यथा
			cx->vbi.sliced_in->service_set = V4L2_SLICED_WSS_625;
		cx18_expand_service_set(cx->vbi.sliced_in, cx->is_50hz);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_s_video_encoding(काष्ठा cx2341x_handler *cxhdl, u32 val)
अणु
	काष्ठा cx18 *cx = container_of(cxhdl, काष्ठा cx18, cxhdl);
	पूर्णांक is_mpeg1 = val == V4L2_MPEG_VIDEO_ENCODING_MPEG_1;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat.क्रमmat;

	/* fix videodecoder resolution */
	fmt->width = cxhdl->width / (is_mpeg1 ? 2 : 1);
	fmt->height = cxhdl->height;
	fmt->code = MEDIA_BUS_FMT_FIXED;
	v4l2_subdev_call(cx->sd_av, pad, set_fmt, शून्य, &क्रमmat);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_s_audio_sampling_freq(काष्ठा cx2341x_handler *cxhdl, u32 idx)
अणु
	अटल स्थिर u32 freqs[3] = अणु 44100, 48000, 32000 पूर्ण;
	काष्ठा cx18 *cx = container_of(cxhdl, काष्ठा cx18, cxhdl);

	/* The audio घड़ी of the digitizer must match the codec sample
	   rate otherwise you get some very strange effects. */
	अगर (idx < ARRAY_SIZE(freqs))
		cx18_call_all(cx, audio, s_घड़ी_freq, freqs[idx]);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_s_audio_mode(काष्ठा cx2341x_handler *cxhdl, u32 val)
अणु
	काष्ठा cx18 *cx = container_of(cxhdl, काष्ठा cx18, cxhdl);

	cx->dualwatch_stereo_mode = val;
	वापस 0;
पूर्ण

स्थिर काष्ठा cx2341x_handler_ops cx18_cxhdl_ops = अणु
	.s_audio_mode = cx18_s_audio_mode,
	.s_audio_sampling_freq = cx18_s_audio_sampling_freq,
	.s_video_encoding = cx18_s_video_encoding,
	.s_stream_vbi_fmt = cx18_s_stream_vbi_fmt,
पूर्ण;
