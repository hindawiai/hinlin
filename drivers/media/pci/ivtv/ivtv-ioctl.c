<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    ioctl प्रणाली call
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-version.h"
#समावेश "ivtv-mailbox.h"
#समावेश "ivtv-i2c.h"
#समावेश "ivtv-queue.h"
#समावेश "ivtv-fileops.h"
#समावेश "ivtv-vbi.h"
#समावेश "ivtv-routing.h"
#समावेश "ivtv-streams.h"
#समावेश "ivtv-yuv.h"
#समावेश "ivtv-ioctl.h"
#समावेश "ivtv-gpio.h"
#समावेश "ivtv-controls.h"
#समावेश "ivtv-cards.h"
#समावेश <media/i2c/saa7127.h>
#समावेश <media/tveeprom.h>
#समावेश <media/v4l2-event.h>
#अगर_घोषित CONFIG_VIDEO_IVTV_DEPRECATED_IOCTLS
#समावेश <linux/compat.h>
#समावेश <linux/dvb/audपन.स>
#समावेश <linux/dvb/video.h>
#पूर्ण_अगर

u16 ivtv_service2vbi(पूर्णांक type)
अणु
	चयन (type) अणु
		हाल V4L2_SLICED_TELETEXT_B:
			वापस IVTV_SLICED_TYPE_TELETEXT_B;
		हाल V4L2_SLICED_CAPTION_525:
			वापस IVTV_SLICED_TYPE_CAPTION_525;
		हाल V4L2_SLICED_WSS_625:
			वापस IVTV_SLICED_TYPE_WSS_625;
		हाल V4L2_SLICED_VPS:
			वापस IVTV_SLICED_TYPE_VPS;
		शेष:
			वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक valid_service_line(पूर्णांक field, पूर्णांक line, पूर्णांक is_pal)
अणु
	वापस (is_pal && line >= 6 && (line != 23 || field == 0)) ||
	       (!is_pal && line >= 10 && line < 22);
पूर्ण

अटल u16 select_service_from_set(पूर्णांक field, पूर्णांक line, u16 set, पूर्णांक is_pal)
अणु
	u16 valid_set = (is_pal ? V4L2_SLICED_VBI_625 : V4L2_SLICED_VBI_525);
	पूर्णांक i;

	set = set & valid_set;
	अगर (set == 0 || !valid_service_line(field, line, is_pal)) अणु
		वापस 0;
	पूर्ण
	अगर (!is_pal) अणु
		अगर (line == 21 && (set & V4L2_SLICED_CAPTION_525))
			वापस V4L2_SLICED_CAPTION_525;
	पूर्ण
	अन्यथा अणु
		अगर (line == 16 && field == 0 && (set & V4L2_SLICED_VPS))
			वापस V4L2_SLICED_VPS;
		अगर (line == 23 && field == 0 && (set & V4L2_SLICED_WSS_625))
			वापस V4L2_SLICED_WSS_625;
		अगर (line == 23)
			वापस 0;
	पूर्ण
	क्रम (i = 0; i < 32; i++) अणु
		अगर (BIT(i) & set)
			वापस BIT(i);
	पूर्ण
	वापस 0;
पूर्ण

व्योम ivtv_expand_service_set(काष्ठा v4l2_sliced_vbi_क्रमmat *fmt, पूर्णांक is_pal)
अणु
	u16 set = fmt->service_set;
	पूर्णांक f, l;

	fmt->service_set = 0;
	क्रम (f = 0; f < 2; f++) अणु
		क्रम (l = 0; l < 24; l++) अणु
			fmt->service_lines[f][l] = select_service_from_set(f, l, set, is_pal);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम check_service_set(काष्ठा v4l2_sliced_vbi_क्रमmat *fmt, पूर्णांक is_pal)
अणु
	पूर्णांक f, l;

	क्रम (f = 0; f < 2; f++) अणु
		क्रम (l = 0; l < 24; l++) अणु
			fmt->service_lines[f][l] = select_service_from_set(f, l, fmt->service_lines[f][l], is_pal);
		पूर्ण
	पूर्ण
पूर्ण

u16 ivtv_get_service_set(काष्ठा v4l2_sliced_vbi_क्रमmat *fmt)
अणु
	पूर्णांक f, l;
	u16 set = 0;

	क्रम (f = 0; f < 2; f++) अणु
		क्रम (l = 0; l < 24; l++) अणु
			set |= fmt->service_lines[f][l];
		पूर्ण
	पूर्ण
	वापस set;
पूर्ण

व्योम ivtv_set_osd_alpha(काष्ठा ivtv *itv)
अणु
	ivtv_vapi(itv, CX2341X_OSD_SET_GLOBAL_ALPHA, 3,
		itv->osd_global_alpha_state, itv->osd_global_alpha, !itv->osd_local_alpha_state);
	ivtv_vapi(itv, CX2341X_OSD_SET_CHROMA_KEY, 2, itv->osd_chroma_key_state, itv->osd_chroma_key);
पूर्ण

पूर्णांक ivtv_set_speed(काष्ठा ivtv *itv, पूर्णांक speed)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	पूर्णांक single_step = (speed == 1 || speed == -1);
	DEFINE_WAIT(रुको);

	अगर (speed == 0) speed = 1000;

	/* No change? */
	अगर (speed == itv->speed && !single_step)
		वापस 0;

	अगर (single_step && (speed < 0) == (itv->speed < 0)) अणु
		/* Single step video and no need to change direction */
		ivtv_vapi(itv, CX2341X_DEC_STEP_VIDEO, 1, 0);
		itv->speed = speed;
		वापस 0;
	पूर्ण
	अगर (single_step)
		/* Need to change direction */
		speed = speed < 0 ? -1000 : 1000;

	data[0] = (speed > 1000 || speed < -1000) ? 0x80000000 : 0;
	data[0] |= (speed > 1000 || speed < -1500) ? 0x40000000 : 0;
	data[1] = (speed < 0);
	data[2] = speed < 0 ? 3 : 7;
	data[3] = v4l2_ctrl_g_ctrl(itv->cxhdl.video_b_frames);
	data[4] = (speed == 1500 || speed == 500) ? itv->speed_mute_audio : 0;
	data[5] = 0;
	data[6] = 0;

	अगर (speed == 1500 || speed == -1500) data[0] |= 1;
	अन्यथा अगर (speed == 2000 || speed == -2000) data[0] |= 2;
	अन्यथा अगर (speed > -1000 && speed < 0) data[0] |= (-1000 / speed);
	अन्यथा अगर (speed < 1000 && speed > 0) data[0] |= (1000 / speed);

	/* If not decoding, just change speed setting */
	अगर (atomic_पढ़ो(&itv->decoding) > 0) अणु
		पूर्णांक got_sig = 0;

		/* Stop all DMA and decoding activity */
		ivtv_vapi(itv, CX2341X_DEC_PAUSE_PLAYBACK, 1, 0);

		/* Wait क्रम any DMA to finish */
		mutex_unlock(&itv->serialize_lock);
		prepare_to_रुको(&itv->dma_रुकोq, &रुको, TASK_INTERRUPTIBLE);
		जबतक (test_bit(IVTV_F_I_DMA, &itv->i_flags)) अणु
			got_sig = संकेत_pending(current);
			अगर (got_sig)
				अवरोध;
			got_sig = 0;
			schedule();
		पूर्ण
		finish_रुको(&itv->dma_रुकोq, &रुको);
		mutex_lock(&itv->serialize_lock);
		अगर (got_sig)
			वापस -EINTR;

		/* Change Speed safely */
		ivtv_api(itv, CX2341X_DEC_SET_PLAYBACK_SPEED, 7, data);
		IVTV_DEBUG_INFO("Setting Speed to 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n",
				data[0], data[1], data[2], data[3], data[4], data[5], data[6]);
	पूर्ण
	अगर (single_step) अणु
		speed = (speed < 0) ? -1 : 1;
		ivtv_vapi(itv, CX2341X_DEC_STEP_VIDEO, 1, 0);
	पूर्ण
	itv->speed = speed;
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_validate_speed(पूर्णांक cur_speed, पूर्णांक new_speed)
अणु
	पूर्णांक fact = new_speed < 0 ? -1 : 1;
	पूर्णांक s;

	अगर (cur_speed == 0)
		cur_speed = 1000;
	अगर (new_speed < 0)
		new_speed = -new_speed;
	अगर (cur_speed < 0)
		cur_speed = -cur_speed;

	अगर (cur_speed <= new_speed) अणु
		अगर (new_speed > 1500)
			वापस fact * 2000;
		अगर (new_speed > 1000)
			वापस fact * 1500;
	पूर्ण
	अन्यथा अणु
		अगर (new_speed >= 2000)
			वापस fact * 2000;
		अगर (new_speed >= 1500)
			वापस fact * 1500;
		अगर (new_speed >= 1000)
			वापस fact * 1000;
	पूर्ण
	अगर (new_speed == 0)
		वापस 1000;
	अगर (new_speed == 1 || new_speed == 1000)
		वापस fact * new_speed;

	s = new_speed;
	new_speed = 1000 / new_speed;
	अगर (1000 / cur_speed == new_speed)
		new_speed += (cur_speed < s) ? -1 : 1;
	अगर (new_speed > 60) वापस 1000 / (fact * 60);
	वापस 1000 / (fact * new_speed);
पूर्ण

अटल पूर्णांक ivtv_video_command(काष्ठा ivtv *itv, काष्ठा ivtv_खोलो_id *id,
		काष्ठा v4l2_decoder_cmd *dc, पूर्णांक try)
अणु
	काष्ठा ivtv_stream *s = &itv->streams[IVTV_DEC_STREAM_TYPE_MPG];

	अगर (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		वापस -EINVAL;

	चयन (dc->cmd) अणु
	हाल V4L2_DEC_CMD_START: अणु
		dc->flags &= V4L2_DEC_CMD_START_MUTE_AUDIO;
		dc->start.speed = ivtv_validate_speed(itv->speed, dc->start.speed);
		अगर (dc->start.speed < 0)
			dc->start.क्रमmat = V4L2_DEC_START_FMT_GOP;
		अन्यथा
			dc->start.क्रमmat = V4L2_DEC_START_FMT_NONE;
		अगर (dc->start.speed != 500 && dc->start.speed != 1500)
			dc->flags = dc->start.speed == 1000 ? 0 :
					V4L2_DEC_CMD_START_MUTE_AUDIO;
		अगर (try) अवरोध;

		itv->speed_mute_audio = dc->flags & V4L2_DEC_CMD_START_MUTE_AUDIO;
		अगर (ivtv_set_output_mode(itv, OUT_MPG) != OUT_MPG)
			वापस -EBUSY;
		अगर (test_and_clear_bit(IVTV_F_I_DEC_PAUSED, &itv->i_flags)) अणु
			/* क्रमces ivtv_set_speed to be called */
			itv->speed = 0;
		पूर्ण
		वापस ivtv_start_decoding(id, dc->start.speed);
	पूर्ण

	हाल V4L2_DEC_CMD_STOP:
		dc->flags &= V4L2_DEC_CMD_STOP_IMMEDIATELY | V4L2_DEC_CMD_STOP_TO_BLACK;
		अगर (dc->flags & V4L2_DEC_CMD_STOP_IMMEDIATELY)
			dc->stop.pts = 0;
		अगर (try) अवरोध;
		अगर (atomic_पढ़ो(&itv->decoding) == 0)
			वापस 0;
		अगर (itv->output_mode != OUT_MPG)
			वापस -EBUSY;

		itv->output_mode = OUT_NONE;
		वापस ivtv_stop_v4l2_decode_stream(s, dc->flags, dc->stop.pts);

	हाल V4L2_DEC_CMD_PAUSE:
		dc->flags &= V4L2_DEC_CMD_PAUSE_TO_BLACK;
		अगर (try) अवरोध;
		अगर (!atomic_पढ़ो(&itv->decoding))
			वापस -EPERM;
		अगर (itv->output_mode != OUT_MPG)
			वापस -EBUSY;
		अगर (atomic_पढ़ो(&itv->decoding) > 0) अणु
			ivtv_vapi(itv, CX2341X_DEC_PAUSE_PLAYBACK, 1,
				(dc->flags & V4L2_DEC_CMD_PAUSE_TO_BLACK) ? 1 : 0);
			set_bit(IVTV_F_I_DEC_PAUSED, &itv->i_flags);
		पूर्ण
		अवरोध;

	हाल V4L2_DEC_CMD_RESUME:
		dc->flags = 0;
		अगर (try) अवरोध;
		अगर (!atomic_पढ़ो(&itv->decoding))
			वापस -EPERM;
		अगर (itv->output_mode != OUT_MPG)
			वापस -EBUSY;
		अगर (test_and_clear_bit(IVTV_F_I_DEC_PAUSED, &itv->i_flags)) अणु
			पूर्णांक speed = itv->speed;
			itv->speed = 0;
			वापस ivtv_start_decoding(id, speed);
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_fmt_sliced_vbi_out(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	काष्ठा v4l2_sliced_vbi_क्रमmat *vbअगरmt = &fmt->fmt.sliced;

	vbअगरmt->reserved[0] = 0;
	vbअगरmt->reserved[1] = 0;
	अगर (!(itv->v4l2_cap & V4L2_CAP_SLICED_VBI_OUTPUT))
		वापस -EINVAL;
	vbअगरmt->io_size = माप(काष्ठा v4l2_sliced_vbi_data) * 36;
	स_रखो(vbअगरmt->service_lines, 0, माप(vbअगरmt->service_lines));
	अगर (itv->is_60hz) अणु
		vbअगरmt->service_lines[0][21] = V4L2_SLICED_CAPTION_525;
		vbअगरmt->service_lines[1][21] = V4L2_SLICED_CAPTION_525;
	पूर्ण अन्यथा अणु
		vbअगरmt->service_lines[0][23] = V4L2_SLICED_WSS_625;
		vbअगरmt->service_lines[0][16] = V4L2_SLICED_VPS;
	पूर्ण
	vbअगरmt->service_set = ivtv_get_service_set(vbअगरmt);
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_fmt_vid_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;
	काष्ठा v4l2_pix_क्रमmat *pixfmt = &fmt->fmt.pix;

	pixfmt->width = itv->cxhdl.width;
	pixfmt->height = itv->cxhdl.height;
	pixfmt->colorspace = V4L2_COLORSPACE_SMPTE170M;
	pixfmt->field = V4L2_FIELD_INTERLACED;
	अगर (id->type == IVTV_ENC_STREAM_TYPE_YUV) अणु
		pixfmt->pixelक्रमmat = V4L2_PIX_FMT_HM12;
		/* YUV size is (Y=(h*720) + UV=(h*(720/2))) */
		pixfmt->sizeimage = pixfmt->height * 720 * 3 / 2;
		pixfmt->bytesperline = 720;
	पूर्ण अन्यथा अणु
		pixfmt->pixelक्रमmat = V4L2_PIX_FMT_MPEG;
		pixfmt->sizeimage = 128 * 1024;
		pixfmt->bytesperline = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_fmt_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	काष्ठा v4l2_vbi_क्रमmat *vbअगरmt = &fmt->fmt.vbi;

	vbअगरmt->sampling_rate = 27000000;
	vbअगरmt->offset = 248;
	vbअगरmt->samples_per_line = itv->vbi.raw_decoder_line_size - 4;
	vbअगरmt->sample_क्रमmat = V4L2_PIX_FMT_GREY;
	vbअगरmt->start[0] = itv->vbi.start[0];
	vbअगरmt->start[1] = itv->vbi.start[1];
	vbअगरmt->count[0] = vbअगरmt->count[1] = itv->vbi.count;
	vbअगरmt->flags = 0;
	vbअगरmt->reserved[0] = 0;
	vbअगरmt->reserved[1] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_fmt_sliced_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा v4l2_sliced_vbi_क्रमmat *vbअगरmt = &fmt->fmt.sliced;
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;

	vbअगरmt->reserved[0] = 0;
	vbअगरmt->reserved[1] = 0;
	vbअगरmt->io_size = माप(काष्ठा v4l2_sliced_vbi_data) * 36;

	अगर (id->type == IVTV_DEC_STREAM_TYPE_VBI) अणु
		vbअगरmt->service_set = itv->is_50hz ? V4L2_SLICED_VBI_625 :
			V4L2_SLICED_VBI_525;
		ivtv_expand_service_set(vbअगरmt, itv->is_50hz);
		vbअगरmt->service_set = ivtv_get_service_set(vbअगरmt);
		वापस 0;
	पूर्ण

	v4l2_subdev_call(itv->sd_video, vbi, g_sliced_fmt, vbअगरmt);
	vbअगरmt->service_set = ivtv_get_service_set(vbअगरmt);
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_fmt_vid_out(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;
	काष्ठा v4l2_pix_क्रमmat *pixfmt = &fmt->fmt.pix;

	अगर (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		वापस -EINVAL;
	pixfmt->width = itv->मुख्य_rect.width;
	pixfmt->height = itv->मुख्य_rect.height;
	pixfmt->colorspace = V4L2_COLORSPACE_SMPTE170M;
	pixfmt->field = V4L2_FIELD_INTERLACED;
	अगर (id->type == IVTV_DEC_STREAM_TYPE_YUV) अणु
		चयन (itv->yuv_info.lace_mode & IVTV_YUV_MODE_MASK) अणु
		हाल IVTV_YUV_MODE_INTERLACED:
			pixfmt->field = (itv->yuv_info.lace_mode & IVTV_YUV_SYNC_MASK) ?
				V4L2_FIELD_INTERLACED_BT : V4L2_FIELD_INTERLACED_TB;
			अवरोध;
		हाल IVTV_YUV_MODE_PROGRESSIVE:
			pixfmt->field = V4L2_FIELD_NONE;
			अवरोध;
		शेष:
			pixfmt->field = V4L2_FIELD_ANY;
			अवरोध;
		पूर्ण
		pixfmt->pixelक्रमmat = V4L2_PIX_FMT_HM12;
		pixfmt->bytesperline = 720;
		pixfmt->width = itv->yuv_info.v4l2_src_w;
		pixfmt->height = itv->yuv_info.v4l2_src_h;
		/* YUV size is (Y=(h*w) + UV=(h*(w/2))) */
		pixfmt->sizeimage =
			1080 * ((pixfmt->height + 31) & ~31);
	पूर्ण अन्यथा अणु
		pixfmt->pixelक्रमmat = V4L2_PIX_FMT_MPEG;
		pixfmt->sizeimage = 128 * 1024;
		pixfmt->bytesperline = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_fmt_vid_out_overlay(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	काष्ठा ivtv_stream *s = &itv->streams[fh2id(fh)->type];
	काष्ठा v4l2_winकरोw *winfmt = &fmt->fmt.win;

	अगर (!(s->caps & V4L2_CAP_VIDEO_OUTPUT_OVERLAY))
		वापस -EINVAL;
	अगर (!itv->osd_video_pbase)
		वापस -EINVAL;
	winfmt->chromakey = itv->osd_chroma_key;
	winfmt->global_alpha = itv->osd_global_alpha;
	winfmt->field = V4L2_FIELD_INTERLACED;
	winfmt->clips = शून्य;
	winfmt->clipcount = 0;
	winfmt->biपंचांगap = शून्य;
	winfmt->w.top = winfmt->w.left = 0;
	winfmt->w.width = itv->osd_rect.width;
	winfmt->w.height = itv->osd_rect.height;
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_try_fmt_sliced_vbi_out(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	वापस ivtv_g_fmt_sliced_vbi_out(file, fh, fmt);
पूर्ण

अटल पूर्णांक ivtv_try_fmt_vid_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;
	पूर्णांक w = fmt->fmt.pix.width;
	पूर्णांक h = fmt->fmt.pix.height;
	पूर्णांक min_h = 2;

	w = min(w, 720);
	w = max(w, 2);
	अगर (id->type == IVTV_ENC_STREAM_TYPE_YUV) अणु
		/* YUV height must be a multiple of 32 */
		h &= ~0x1f;
		min_h = 32;
	पूर्ण
	h = min(h, itv->is_50hz ? 576 : 480);
	h = max(h, min_h);
	ivtv_g_fmt_vid_cap(file, fh, fmt);
	fmt->fmt.pix.width = w;
	fmt->fmt.pix.height = h;
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_try_fmt_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	वापस ivtv_g_fmt_vbi_cap(file, fh, fmt);
पूर्ण

अटल पूर्णांक ivtv_try_fmt_sliced_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा v4l2_sliced_vbi_क्रमmat *vbअगरmt = &fmt->fmt.sliced;
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;

	अगर (id->type == IVTV_DEC_STREAM_TYPE_VBI)
		वापस ivtv_g_fmt_sliced_vbi_cap(file, fh, fmt);

	/* set sliced VBI capture क्रमmat */
	vbअगरmt->io_size = माप(काष्ठा v4l2_sliced_vbi_data) * 36;
	vbअगरmt->reserved[0] = 0;
	vbअगरmt->reserved[1] = 0;

	अगर (vbअगरmt->service_set)
		ivtv_expand_service_set(vbअगरmt, itv->is_50hz);
	check_service_set(vbअगरmt, itv->is_50hz);
	vbअगरmt->service_set = ivtv_get_service_set(vbअगरmt);
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_try_fmt_vid_out(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	s32 w = fmt->fmt.pix.width;
	s32 h = fmt->fmt.pix.height;
	पूर्णांक field = fmt->fmt.pix.field;
	पूर्णांक ret = ivtv_g_fmt_vid_out(file, fh, fmt);

	w = min(w, 720);
	w = max(w, 2);
	/* Why can the height be 576 even when the output is NTSC?

	   Internally the buffers of the PVR350 are always set to 720x576. The
	   decoded video frame will always be placed in the top left corner of
	   this buffer. For any video which is not 720x576, the buffer will
	   then be cropped to हटाओ the unused right and lower areas, with
	   the reमुख्यing image being scaled by the hardware to fit the display
	   area. The video can be scaled both up and करोwn, so a 720x480 video
	   can be displayed full-screen on PAL and a 720x576 video can be
	   displayed without cropping on NTSC.

	   Note that the scaling only occurs on the video stream, the osd
	   resolution is locked to the broadcast standard and not scaled.

	   Thanks to Ian Armstrong क्रम this explanation. */
	h = min(h, 576);
	h = max(h, 2);
	अगर (id->type == IVTV_DEC_STREAM_TYPE_YUV)
		fmt->fmt.pix.field = field;
	fmt->fmt.pix.width = w;
	fmt->fmt.pix.height = h;
	वापस ret;
पूर्ण

अटल पूर्णांक ivtv_try_fmt_vid_out_overlay(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	काष्ठा ivtv_stream *s = &itv->streams[fh2id(fh)->type];
	u32 chromakey = fmt->fmt.win.chromakey;
	u8 global_alpha = fmt->fmt.win.global_alpha;

	अगर (!(s->caps & V4L2_CAP_VIDEO_OUTPUT_OVERLAY))
		वापस -EINVAL;
	अगर (!itv->osd_video_pbase)
		वापस -EINVAL;
	ivtv_g_fmt_vid_out_overlay(file, fh, fmt);
	fmt->fmt.win.chromakey = chromakey;
	fmt->fmt.win.global_alpha = global_alpha;
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_s_fmt_sliced_vbi_out(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	वापस ivtv_g_fmt_sliced_vbi_out(file, fh, fmt);
पूर्ण

अटल पूर्णांक ivtv_s_fmt_vid_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret = ivtv_try_fmt_vid_cap(file, fh, fmt);
	पूर्णांक w = fmt->fmt.pix.width;
	पूर्णांक h = fmt->fmt.pix.height;

	अगर (ret)
		वापस ret;

	अगर (itv->cxhdl.width == w && itv->cxhdl.height == h)
		वापस 0;

	अगर (atomic_पढ़ो(&itv->capturing) > 0)
		वापस -EBUSY;

	itv->cxhdl.width = w;
	itv->cxhdl.height = h;
	अगर (v4l2_ctrl_g_ctrl(itv->cxhdl.video_encoding) == V4L2_MPEG_VIDEO_ENCODING_MPEG_1)
		fmt->fmt.pix.width /= 2;
	क्रमmat.क्रमmat.width = fmt->fmt.pix.width;
	क्रमmat.क्रमmat.height = h;
	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_FIXED;
	v4l2_subdev_call(itv->sd_video, pad, set_fmt, शून्य, &क्रमmat);
	वापस ivtv_g_fmt_vid_cap(file, fh, fmt);
पूर्ण

अटल पूर्णांक ivtv_s_fmt_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	अगर (!ivtv_raw_vbi(itv) && atomic_पढ़ो(&itv->capturing) > 0)
		वापस -EBUSY;
	itv->vbi.sliced_in->service_set = 0;
	itv->vbi.in.type = V4L2_BUF_TYPE_VBI_CAPTURE;
	v4l2_subdev_call(itv->sd_video, vbi, s_raw_fmt, &fmt->fmt.vbi);
	वापस ivtv_g_fmt_vbi_cap(file, fh, fmt);
पूर्ण

अटल पूर्णांक ivtv_s_fmt_sliced_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा v4l2_sliced_vbi_क्रमmat *vbअगरmt = &fmt->fmt.sliced;
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;
	पूर्णांक ret = ivtv_try_fmt_sliced_vbi_cap(file, fh, fmt);

	अगर (ret || id->type == IVTV_DEC_STREAM_TYPE_VBI)
		वापस ret;

	check_service_set(vbअगरmt, itv->is_50hz);
	अगर (ivtv_raw_vbi(itv) && atomic_पढ़ो(&itv->capturing) > 0)
		वापस -EBUSY;
	itv->vbi.in.type = V4L2_BUF_TYPE_SLICED_VBI_CAPTURE;
	v4l2_subdev_call(itv->sd_video, vbi, s_sliced_fmt, vbअगरmt);
	स_नकल(itv->vbi.sliced_in, vbअगरmt, माप(*itv->vbi.sliced_in));
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_s_fmt_vid_out(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	पूर्णांक ret = ivtv_try_fmt_vid_out(file, fh, fmt);

	अगर (ret)
		वापस ret;

	अगर (id->type != IVTV_DEC_STREAM_TYPE_YUV)
		वापस 0;

	/* Return now अगर we alपढ़ोy have some frame data */
	अगर (yi->stream_size)
		वापस -EBUSY;

	yi->v4l2_src_w = fmt->fmt.pix.width;
	yi->v4l2_src_h = fmt->fmt.pix.height;

	चयन (fmt->fmt.pix.field) अणु
	हाल V4L2_FIELD_NONE:
		yi->lace_mode = IVTV_YUV_MODE_PROGRESSIVE;
		अवरोध;
	हाल V4L2_FIELD_ANY:
		yi->lace_mode = IVTV_YUV_MODE_AUTO;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED_BT:
		yi->lace_mode =
			IVTV_YUV_MODE_INTERLACED|IVTV_YUV_SYNC_ODD;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED_TB:
	शेष:
		yi->lace_mode = IVTV_YUV_MODE_INTERLACED;
		अवरोध;
	पूर्ण
	yi->lace_sync_field = (yi->lace_mode & IVTV_YUV_SYNC_MASK) == IVTV_YUV_SYNC_EVEN ? 0 : 1;

	अगर (test_bit(IVTV_F_I_DEC_YUV, &itv->i_flags))
		itv->dma_data_req_size =
			1080 * ((yi->v4l2_src_h + 31) & ~31);

	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_s_fmt_vid_out_overlay(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	पूर्णांक ret = ivtv_try_fmt_vid_out_overlay(file, fh, fmt);

	अगर (ret == 0) अणु
		itv->osd_chroma_key = fmt->fmt.win.chromakey;
		itv->osd_global_alpha = fmt->fmt.win.global_alpha;
		ivtv_set_osd_alpha(itv);
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक ivtv_itvc(काष्ठा ivtv *itv, bool get, u64 reg, u64 *val)
अणु
	अस्थिर u8 __iomem *reg_start;

	अगर (reg & 0x3)
		वापस -EINVAL;
	अगर (reg >= IVTV_REG_OFFSET && reg < IVTV_REG_OFFSET + IVTV_REG_SIZE)
		reg_start = itv->reg_mem - IVTV_REG_OFFSET;
	अन्यथा अगर (itv->has_cx23415 && reg >= IVTV_DECODER_OFFSET &&
			reg < IVTV_DECODER_OFFSET + IVTV_DECODER_SIZE)
		reg_start = itv->dec_mem - IVTV_DECODER_OFFSET;
	अन्यथा अगर (reg < IVTV_ENCODER_SIZE)
		reg_start = itv->enc_mem;
	अन्यथा
		वापस -EINVAL;

	अगर (get)
		*val = पढ़ोl(reg + reg_start);
	अन्यथा
		ग_लिखोl(*val, reg + reg_start);
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_रेजिस्टर(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	reg->size = 4;
	वापस ivtv_itvc(itv, true, reg->reg, &reg->val);
पूर्ण

अटल पूर्णांक ivtv_s_रेजिस्टर(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	u64 val = reg->val;

	वापस ivtv_itvc(itv, false, reg->reg, &val);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ivtv_querycap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_capability *vcap)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(file->निजी_data);
	काष्ठा ivtv *itv = id->itv;

	strscpy(vcap->driver, IVTV_DRIVER_NAME, माप(vcap->driver));
	strscpy(vcap->card, itv->card_name, माप(vcap->card));
	snम_लिखो(vcap->bus_info, माप(vcap->bus_info), "PCI:%s", pci_name(itv->pdev));
	vcap->capabilities = itv->v4l2_cap | V4L2_CAP_DEVICE_CAPS;
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_क्रमागतaudio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *vin)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	वापस ivtv_get_audio_input(itv, vin->index, vin);
पूर्ण

अटल पूर्णांक ivtv_g_audio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *vin)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	vin->index = itv->audio_input;
	वापस ivtv_get_audio_input(itv, vin->index, vin);
पूर्ण

अटल पूर्णांक ivtv_s_audio(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_audio *vout)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	अगर (vout->index >= itv->nof_audio_inमाला_दो)
		वापस -EINVAL;

	itv->audio_input = vout->index;
	ivtv_audio_set_io(itv);

	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_क्रमागतauकरोut(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audioout *vin)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	/* set it to शेषs from our table */
	वापस ivtv_get_audio_output(itv, vin->index, vin);
पूर्ण

अटल पूर्णांक ivtv_g_auकरोut(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audioout *vin)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	vin->index = 0;
	वापस ivtv_get_audio_output(itv, vin->index, vin);
पूर्ण

अटल पूर्णांक ivtv_s_auकरोut(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_audioout *vout)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	अगर (itv->card->video_outमाला_दो == शून्य || vout->index != 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_क्रमागत_input(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_input *vin)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	/* set it to शेषs from our table */
	वापस ivtv_get_input(itv, vin->index, vin);
पूर्ण

अटल पूर्णांक ivtv_क्रमागत_output(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_output *vout)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	वापस ivtv_get_output(itv, vout->index, vout);
पूर्ण

अटल पूर्णांक ivtv_g_pixelaspect(काष्ठा file *file, व्योम *fh,
			      पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;

	अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		f->numerator = itv->is_50hz ? 54 : 11;
		f->denominator = itv->is_50hz ? 59 : 10;
	पूर्ण अन्यथा अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		f->numerator = itv->is_out_50hz ? 54 : 11;
		f->denominator = itv->is_out_50hz ? 59 : 10;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_s_selection(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_selection *sel)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	काष्ठा v4l2_rect r = अणु 0, 0, 720, 0 पूर्ण;
	पूर्णांक streamtype = id->type;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT ||
	    !(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		वापस -EINVAL;

	अगर (sel->target != V4L2_SEL_TGT_COMPOSE)
		वापस -EINVAL;


	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT ||
	    !(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		वापस -EINVAL;

	r.height = itv->is_out_50hz ? 576 : 480;
	अगर (streamtype == IVTV_DEC_STREAM_TYPE_YUV && yi->track_osd) अणु
		r.width = yi->osd_full_w;
		r.height = yi->osd_full_h;
	पूर्ण
	sel->r.width = clamp(sel->r.width, 16U, r.width);
	sel->r.height = clamp(sel->r.height, 16U, r.height);
	sel->r.left = clamp_t(अचिन्हित, sel->r.left, 0, r.width - sel->r.width);
	sel->r.top = clamp_t(अचिन्हित, sel->r.top, 0, r.height - sel->r.height);

	अगर (streamtype == IVTV_DEC_STREAM_TYPE_YUV) अणु
		yi->मुख्य_rect = sel->r;
		वापस 0;
	पूर्ण
	अगर (!ivtv_vapi(itv, CX2341X_OSD_SET_FRAMEBUFFER_WINDOW, 4,
			sel->r.width, sel->r.height, sel->r.left, sel->r.top)) अणु
		itv->मुख्य_rect = sel->r;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ivtv_g_selection(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_selection *sel)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	काष्ठा v4l2_rect r = अणु 0, 0, 720, 0 पूर्ण;
	पूर्णांक streamtype = id->type;

	अगर (sel->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		चयन (sel->target) अणु
		हाल V4L2_SEL_TGT_CROP_DEFAULT:
		हाल V4L2_SEL_TGT_CROP_BOUNDS:
			sel->r.top = sel->r.left = 0;
			sel->r.width = 720;
			sel->r.height = itv->is_50hz ? 576 : 480;
			वापस 0;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT ||
	    !(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE:
		अगर (streamtype == IVTV_DEC_STREAM_TYPE_YUV)
			sel->r = yi->मुख्य_rect;
		अन्यथा
			sel->r = itv->मुख्य_rect;
		वापस 0;
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		r.height = itv->is_out_50hz ? 576 : 480;
		अगर (streamtype == IVTV_DEC_STREAM_TYPE_YUV && yi->track_osd) अणु
			r.width = yi->osd_full_w;
			r.height = yi->osd_full_h;
		पूर्ण
		sel->r = r;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ivtv_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_fmtdesc *fmt)
अणु
	अटल स्थिर काष्ठा v4l2_fmtdesc hm12 = अणु
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
		.description = "HM12 (YUV 4:2:0)",
		.pixelक्रमmat = V4L2_PIX_FMT_HM12,
	पूर्ण;
	अटल स्थिर काष्ठा v4l2_fmtdesc mpeg = अणु
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
		.description = "MPEG",
		.pixelक्रमmat = V4L2_PIX_FMT_MPEG,
	पूर्ण;
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	काष्ठा ivtv_stream *s = &itv->streams[fh2id(fh)->type];

	अगर (fmt->index)
		वापस -EINVAL;
	अगर (s->type == IVTV_ENC_STREAM_TYPE_MPG)
		*fmt = mpeg;
	अन्यथा अगर (s->type == IVTV_ENC_STREAM_TYPE_YUV)
		*fmt = hm12;
	अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_fmtdesc *fmt)
अणु
	अटल स्थिर काष्ठा v4l2_fmtdesc hm12 = अणु
		.type = V4L2_BUF_TYPE_VIDEO_OUTPUT,
		.description = "HM12 (YUV 4:2:0)",
		.pixelक्रमmat = V4L2_PIX_FMT_HM12,
	पूर्ण;
	अटल स्थिर काष्ठा v4l2_fmtdesc mpeg = अणु
		.type = V4L2_BUF_TYPE_VIDEO_OUTPUT,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
		.description = "MPEG",
		.pixelक्रमmat = V4L2_PIX_FMT_MPEG,
	पूर्ण;
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	काष्ठा ivtv_stream *s = &itv->streams[fh2id(fh)->type];

	अगर (fmt->index)
		वापस -EINVAL;
	अगर (s->type == IVTV_DEC_STREAM_TYPE_MPG)
		*fmt = mpeg;
	अन्यथा अगर (s->type == IVTV_DEC_STREAM_TYPE_YUV)
		*fmt = hm12;
	अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	*i = itv->active_input;

	वापस 0;
पूर्ण

पूर्णांक ivtv_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक inp)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	v4l2_std_id std;
	पूर्णांक i;

	अगर (inp >= itv->nof_inमाला_दो)
		वापस -EINVAL;

	अगर (inp == itv->active_input) अणु
		IVTV_DEBUG_INFO("Input unchanged\n");
		वापस 0;
	पूर्ण

	अगर (atomic_पढ़ो(&itv->capturing) > 0) अणु
		वापस -EBUSY;
	पूर्ण

	IVTV_DEBUG_INFO("Changing input from %d to %d\n",
			itv->active_input, inp);

	itv->active_input = inp;
	/* Set the audio input to whatever is appropriate क्रम the
	   input type. */
	itv->audio_input = itv->card->video_inमाला_दो[inp].audio_index;

	अगर (itv->card->video_inमाला_दो[inp].video_type == IVTV_CARD_INPUT_VID_TUNER)
		std = itv->tuner_std;
	अन्यथा
		std = V4L2_STD_ALL;
	क्रम (i = 0; i <= IVTV_ENC_STREAM_TYPE_VBI; i++)
		itv->streams[i].vdev.tvnorms = std;

	/* prevent others from messing with the streams until
	   we're finished changing inमाला_दो. */
	ivtv_mute(itv);
	ivtv_video_set_io(itv);
	ivtv_audio_set_io(itv);
	ivtv_unmute(itv);

	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_output(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	अगर (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		वापस -EINVAL;

	*i = itv->active_output;

	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_s_output(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक outp)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	अगर (outp >= itv->card->nof_outमाला_दो)
		वापस -EINVAL;

	अगर (outp == itv->active_output) अणु
		IVTV_DEBUG_INFO("Output unchanged\n");
		वापस 0;
	पूर्ण
	IVTV_DEBUG_INFO("Changing output from %d to %d\n",
		   itv->active_output, outp);

	itv->active_output = outp;
	ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_routing,
			SAA7127_INPUT_TYPE_NORMAL,
			itv->card->video_outमाला_दो[outp].video_output, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_frequency(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	काष्ठा ivtv_stream *s = &itv->streams[fh2id(fh)->type];

	अगर (s->vdev.vfl_dir)
		वापस -ENOTTY;
	अगर (vf->tuner != 0)
		वापस -EINVAL;

	ivtv_call_all(itv, tuner, g_frequency, vf);
	वापस 0;
पूर्ण

पूर्णांक ivtv_s_frequency(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	काष्ठा ivtv_stream *s = &itv->streams[fh2id(fh)->type];

	अगर (s->vdev.vfl_dir)
		वापस -ENOTTY;
	अगर (vf->tuner != 0)
		वापस -EINVAL;

	ivtv_mute(itv);
	IVTV_DEBUG_INFO("v4l2 ioctl: set frequency %d\n", vf->frequency);
	ivtv_call_all(itv, tuner, s_frequency, vf);
	ivtv_unmute(itv);
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_std(काष्ठा file *file, व्योम *fh, v4l2_std_id *std)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	*std = itv->std;
	वापस 0;
पूर्ण

व्योम ivtv_s_std_enc(काष्ठा ivtv *itv, v4l2_std_id std)
अणु
	itv->std = std;
	itv->is_60hz = (std & V4L2_STD_525_60) ? 1 : 0;
	itv->is_50hz = !itv->is_60hz;
	cx2341x_handler_set_50hz(&itv->cxhdl, itv->is_50hz);
	itv->cxhdl.width = 720;
	itv->cxhdl.height = itv->is_50hz ? 576 : 480;
	itv->vbi.count = itv->is_50hz ? 18 : 12;
	itv->vbi.start[0] = itv->is_50hz ? 6 : 10;
	itv->vbi.start[1] = itv->is_50hz ? 318 : 273;

	अगर (itv->hw_flags & IVTV_HW_CX25840)
		itv->vbi.sliced_decoder_line_size = itv->is_60hz ? 272 : 284;

	/* Tuner */
	ivtv_call_all(itv, video, s_std, itv->std);
पूर्ण

व्योम ivtv_s_std_dec(काष्ठा ivtv *itv, v4l2_std_id std)
अणु
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;
	DEFINE_WAIT(रुको);
	पूर्णांक f;

	/* set display standard */
	itv->std_out = std;
	itv->is_out_60hz = (std & V4L2_STD_525_60) ? 1 : 0;
	itv->is_out_50hz = !itv->is_out_60hz;
	ivtv_call_all(itv, video, s_std_output, itv->std_out);

	/*
	 * The next firmware call is समय sensitive. Time it to
	 * aव्योम risk of a hard lock, by trying to ensure the call
	 * happens within the first 100 lines of the top field.
	 * Make 4 attempts to sync to the decoder beक्रमe giving up.
	 */
	mutex_unlock(&itv->serialize_lock);
	क्रम (f = 0; f < 4; f++) अणु
		prepare_to_रुको(&itv->vsync_रुकोq, &रुको,
				TASK_UNINTERRUPTIBLE);
		अगर ((पढ़ो_reg(IVTV_REG_DEC_LINE_FIELD) >> 16) < 100)
			अवरोध;
		schedule_समयout(msecs_to_jअगरfies(25));
	पूर्ण
	finish_रुको(&itv->vsync_रुकोq, &रुको);
	mutex_lock(&itv->serialize_lock);

	अगर (f == 4)
		IVTV_WARN("Mode change failed to sync to decoder\n");

	ivtv_vapi(itv, CX2341X_DEC_SET_STANDARD, 1, itv->is_out_50hz);
	itv->मुख्य_rect.left = 0;
	itv->मुख्य_rect.top = 0;
	itv->मुख्य_rect.width = 720;
	itv->मुख्य_rect.height = itv->is_out_50hz ? 576 : 480;
	ivtv_vapi(itv, CX2341X_OSD_SET_FRAMEBUFFER_WINDOW, 4,
		720, itv->मुख्य_rect.height, 0, 0);
	yi->मुख्य_rect = itv->मुख्य_rect;
	अगर (!itv->osd_info) अणु
		yi->osd_full_w = 720;
		yi->osd_full_h = itv->is_out_50hz ? 576 : 480;
	पूर्ण
पूर्ण

अटल पूर्णांक ivtv_s_std(काष्ठा file *file, व्योम *fh, v4l2_std_id std)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	अगर ((std & V4L2_STD_ALL) == 0)
		वापस -EINVAL;

	अगर (std == itv->std)
		वापस 0;

	अगर (test_bit(IVTV_F_I_RADIO_USER, &itv->i_flags) ||
	    atomic_पढ़ो(&itv->capturing) > 0 ||
	    atomic_पढ़ो(&itv->decoding) > 0) अणु
		/* Switching standard would mess with alपढ़ोy running
		   streams, prevent that by वापसing EBUSY. */
		वापस -EBUSY;
	पूर्ण

	IVTV_DEBUG_INFO("Switching standard to %llx.\n",
		(अचिन्हित दीर्घ दीर्घ)itv->std);

	ivtv_s_std_enc(itv, std);
	अगर (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT)
		ivtv_s_std_dec(itv, std);

	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_s_tuner(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;

	अगर (vt->index != 0)
		वापस -EINVAL;

	ivtv_call_all(itv, tuner, s_tuner, vt);

	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_tuner(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	अगर (vt->index != 0)
		वापस -EINVAL;

	ivtv_call_all(itv, tuner, g_tuner, vt);

	अगर (vt->type == V4L2_TUNER_RADIO)
		strscpy(vt->name, "ivtv Radio Tuner", माप(vt->name));
	अन्यथा
		strscpy(vt->name, "ivtv TV Tuner", माप(vt->name));
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_sliced_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_sliced_vbi_cap *cap)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	पूर्णांक set = itv->is_50hz ? V4L2_SLICED_VBI_625 : V4L2_SLICED_VBI_525;
	पूर्णांक f, l;

	अगर (cap->type == V4L2_BUF_TYPE_SLICED_VBI_CAPTURE) अणु
		क्रम (f = 0; f < 2; f++) अणु
			क्रम (l = 0; l < 24; l++) अणु
				अगर (valid_service_line(f, l, itv->is_50hz))
					cap->service_lines[f][l] = set;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (cap->type == V4L2_BUF_TYPE_SLICED_VBI_OUTPUT) अणु
		अगर (!(itv->v4l2_cap & V4L2_CAP_SLICED_VBI_OUTPUT))
			वापस -EINVAL;
		अगर (itv->is_60hz) अणु
			cap->service_lines[0][21] = V4L2_SLICED_CAPTION_525;
			cap->service_lines[1][21] = V4L2_SLICED_CAPTION_525;
		पूर्ण अन्यथा अणु
			cap->service_lines[0][23] = V4L2_SLICED_WSS_625;
			cap->service_lines[0][16] = V4L2_SLICED_VPS;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	set = 0;
	क्रम (f = 0; f < 2; f++)
		क्रम (l = 0; l < 24; l++)
			set |= cap->service_lines[f][l];
	cap->service_set = set;
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_g_enc_index(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_enc_idx *idx)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	काष्ठा v4l2_enc_idx_entry *e = idx->entry;
	पूर्णांक entries;
	पूर्णांक i;

	entries = (itv->pgm_info_ग_लिखो_idx + IVTV_MAX_PGM_INDEX - itv->pgm_info_पढ़ो_idx) %
				IVTV_MAX_PGM_INDEX;
	अगर (entries > V4L2_ENC_IDX_ENTRIES)
		entries = V4L2_ENC_IDX_ENTRIES;
	idx->entries = 0;
	idx->entries_cap = IVTV_MAX_PGM_INDEX;
	अगर (!atomic_पढ़ो(&itv->capturing))
		वापस 0;
	क्रम (i = 0; i < entries; i++) अणु
		*e = itv->pgm_info[(itv->pgm_info_पढ़ो_idx + i) % IVTV_MAX_PGM_INDEX];
		अगर ((e->flags & V4L2_ENC_IDX_FRAME_MASK) <= V4L2_ENC_IDX_FRAME_B) अणु
			idx->entries++;
			e++;
		पूर्ण
	पूर्ण
	itv->pgm_info_पढ़ो_idx = (itv->pgm_info_पढ़ो_idx + idx->entries) % IVTV_MAX_PGM_INDEX;
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_encoder_cmd(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_encoder_cmd *enc)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;


	चयन (enc->cmd) अणु
	हाल V4L2_ENC_CMD_START:
		IVTV_DEBUG_IOCTL("V4L2_ENC_CMD_START\n");
		enc->flags = 0;
		वापस ivtv_start_capture(id);

	हाल V4L2_ENC_CMD_STOP:
		IVTV_DEBUG_IOCTL("V4L2_ENC_CMD_STOP\n");
		enc->flags &= V4L2_ENC_CMD_STOP_AT_GOP_END;
		ivtv_stop_capture(id, enc->flags & V4L2_ENC_CMD_STOP_AT_GOP_END);
		वापस 0;

	हाल V4L2_ENC_CMD_PAUSE:
		IVTV_DEBUG_IOCTL("V4L2_ENC_CMD_PAUSE\n");
		enc->flags = 0;

		अगर (!atomic_पढ़ो(&itv->capturing))
			वापस -EPERM;
		अगर (test_and_set_bit(IVTV_F_I_ENC_PAUSED, &itv->i_flags))
			वापस 0;

		ivtv_mute(itv);
		ivtv_vapi(itv, CX2341X_ENC_PAUSE_ENCODER, 1, 0);
		अवरोध;

	हाल V4L2_ENC_CMD_RESUME:
		IVTV_DEBUG_IOCTL("V4L2_ENC_CMD_RESUME\n");
		enc->flags = 0;

		अगर (!atomic_पढ़ो(&itv->capturing))
			वापस -EPERM;

		अगर (!test_and_clear_bit(IVTV_F_I_ENC_PAUSED, &itv->i_flags))
			वापस 0;

		ivtv_vapi(itv, CX2341X_ENC_PAUSE_ENCODER, 1, 1);
		ivtv_unmute(itv);
		अवरोध;
	शेष:
		IVTV_DEBUG_IOCTL("Unknown cmd %d\n", enc->cmd);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_try_encoder_cmd(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_encoder_cmd *enc)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	चयन (enc->cmd) अणु
	हाल V4L2_ENC_CMD_START:
		IVTV_DEBUG_IOCTL("V4L2_ENC_CMD_START\n");
		enc->flags = 0;
		वापस 0;

	हाल V4L2_ENC_CMD_STOP:
		IVTV_DEBUG_IOCTL("V4L2_ENC_CMD_STOP\n");
		enc->flags &= V4L2_ENC_CMD_STOP_AT_GOP_END;
		वापस 0;

	हाल V4L2_ENC_CMD_PAUSE:
		IVTV_DEBUG_IOCTL("V4L2_ENC_CMD_PAUSE\n");
		enc->flags = 0;
		वापस 0;

	हाल V4L2_ENC_CMD_RESUME:
		IVTV_DEBUG_IOCTL("V4L2_ENC_CMD_RESUME\n");
		enc->flags = 0;
		वापस 0;
	शेष:
		IVTV_DEBUG_IOCTL("Unknown cmd %d\n", enc->cmd);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ivtv_g_fbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_framebuffer *fb)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	काष्ठा ivtv_stream *s = &itv->streams[fh2id(fh)->type];
	u32 data[CX2341X_MBOX_MAX_DATA];
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;

	पूर्णांक pixfmt;
	अटल u32 pixel_क्रमmat[16] = अणु
		V4L2_PIX_FMT_PAL8, /* Uses a 256-entry RGB colormap */
		V4L2_PIX_FMT_RGB565,
		V4L2_PIX_FMT_RGB555,
		V4L2_PIX_FMT_RGB444,
		V4L2_PIX_FMT_RGB32,
		0,
		0,
		0,
		V4L2_PIX_FMT_PAL8, /* Uses a 256-entry YUV colormap */
		V4L2_PIX_FMT_YUV565,
		V4L2_PIX_FMT_YUV555,
		V4L2_PIX_FMT_YUV444,
		V4L2_PIX_FMT_YUV32,
		0,
		0,
		0,
	पूर्ण;

	अगर (!(s->caps & V4L2_CAP_VIDEO_OUTPUT_OVERLAY))
		वापस -ENOTTY;
	अगर (!itv->osd_video_pbase)
		वापस -ENOTTY;

	fb->capability = V4L2_FBUF_CAP_EXTERNOVERLAY | V4L2_FBUF_CAP_CHROMAKEY |
		V4L2_FBUF_CAP_GLOBAL_ALPHA;

	ivtv_vapi_result(itv, data, CX2341X_OSD_GET_STATE, 0);
	data[0] |= (पढ़ो_reg(0x2a00) >> 7) & 0x40;
	pixfmt = (data[0] >> 3) & 0xf;

	fb->fmt.pixelक्रमmat = pixel_क्रमmat[pixfmt];
	fb->fmt.width = itv->osd_rect.width;
	fb->fmt.height = itv->osd_rect.height;
	fb->fmt.field = V4L2_FIELD_INTERLACED;
	fb->fmt.bytesperline = fb->fmt.width;
	fb->fmt.colorspace = V4L2_COLORSPACE_SMPTE170M;
	fb->fmt.field = V4L2_FIELD_INTERLACED;
	अगर (fb->fmt.pixelक्रमmat != V4L2_PIX_FMT_PAL8)
		fb->fmt.bytesperline *= 2;
	अगर (fb->fmt.pixelक्रमmat == V4L2_PIX_FMT_RGB32 ||
	    fb->fmt.pixelक्रमmat == V4L2_PIX_FMT_YUV32)
		fb->fmt.bytesperline *= 2;
	fb->fmt.sizeimage = fb->fmt.bytesperline * fb->fmt.height;
	fb->base = (व्योम *)itv->osd_video_pbase;
	fb->flags = 0;

	अगर (itv->osd_chroma_key_state)
		fb->flags |= V4L2_FBUF_FLAG_CHROMAKEY;

	अगर (itv->osd_global_alpha_state)
		fb->flags |= V4L2_FBUF_FLAG_GLOBAL_ALPHA;

	अगर (yi->track_osd)
		fb->flags |= V4L2_FBUF_FLAG_OVERLAY;

	pixfmt &= 7;

	/* no local alpha क्रम RGB565 or unknown क्रमmats */
	अगर (pixfmt == 1 || pixfmt > 4)
		वापस 0;

	/* 16-bit क्रमmats have inverted local alpha */
	अगर (pixfmt == 2 || pixfmt == 3)
		fb->capability |= V4L2_FBUF_CAP_LOCAL_INV_ALPHA;
	अन्यथा
		fb->capability |= V4L2_FBUF_CAP_LOCAL_ALPHA;

	अगर (itv->osd_local_alpha_state) अणु
		/* 16-bit क्रमmats have inverted local alpha */
		अगर (pixfmt == 2 || pixfmt == 3)
			fb->flags |= V4L2_FBUF_FLAG_LOCAL_INV_ALPHA;
		अन्यथा
			fb->flags |= V4L2_FBUF_FLAG_LOCAL_ALPHA;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_s_fbuf(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_framebuffer *fb)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;
	काष्ठा ivtv_stream *s = &itv->streams[fh2id(fh)->type];
	काष्ठा yuv_playback_info *yi = &itv->yuv_info;

	अगर (!(s->caps & V4L2_CAP_VIDEO_OUTPUT_OVERLAY))
		वापस -ENOTTY;
	अगर (!itv->osd_video_pbase)
		वापस -ENOTTY;

	itv->osd_global_alpha_state = (fb->flags & V4L2_FBUF_FLAG_GLOBAL_ALPHA) != 0;
	itv->osd_local_alpha_state =
		(fb->flags & (V4L2_FBUF_FLAG_LOCAL_ALPHA|V4L2_FBUF_FLAG_LOCAL_INV_ALPHA)) != 0;
	itv->osd_chroma_key_state = (fb->flags & V4L2_FBUF_FLAG_CHROMAKEY) != 0;
	ivtv_set_osd_alpha(itv);
	yi->track_osd = (fb->flags & V4L2_FBUF_FLAG_OVERLAY) != 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_overlay(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक on)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(fh);
	काष्ठा ivtv *itv = id->itv;
	काष्ठा ivtv_stream *s = &itv->streams[fh2id(fh)->type];

	अगर (!(s->caps & V4L2_CAP_VIDEO_OUTPUT_OVERLAY))
		वापस -ENOTTY;
	अगर (!itv->osd_video_pbase)
		वापस -ENOTTY;

	ivtv_vapi(itv, CX2341X_OSD_SET_STATE, 1, on != 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_subscribe_event(काष्ठा v4l2_fh *fh, स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_VSYNC:
	हाल V4L2_EVENT_EOS:
		वापस v4l2_event_subscribe(fh, sub, 0, शून्य);
	शेष:
		वापस v4l2_ctrl_subscribe_event(fh, sub);
	पूर्ण
पूर्ण

अटल पूर्णांक ivtv_log_status(काष्ठा file *file, व्योम *fh)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;
	u32 data[CX2341X_MBOX_MAX_DATA];

	पूर्णांक has_output = itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT;
	काष्ठा v4l2_input vidin;
	काष्ठा v4l2_audio audin;
	पूर्णांक i;

	IVTV_INFO("Version: %s Card: %s\n", IVTV_VERSION, itv->card_name);
	अगर (itv->hw_flags & IVTV_HW_TVEEPROM) अणु
		काष्ठा tveeprom tv;

		ivtv_पढ़ो_eeprom(itv, &tv);
	पूर्ण
	ivtv_call_all(itv, core, log_status);
	ivtv_get_input(itv, itv->active_input, &vidin);
	ivtv_get_audio_input(itv, itv->audio_input, &audin);
	IVTV_INFO("Video Input:  %s\n", vidin.name);
	IVTV_INFO("Audio Input:  %s%s\n", audin.name,
		itv->dualwatch_stereo_mode == V4L2_MPEG_AUDIO_MODE_DUAL ?
			" (Bilingual)" : "");
	अगर (has_output) अणु
		काष्ठा v4l2_output viकरोut;
		काष्ठा v4l2_audioout auकरोut;
		पूर्णांक mode = itv->output_mode;
		अटल स्थिर अक्षर * स्थिर output_modes[5] = अणु
			"None",
			"MPEG Streaming",
			"YUV Streaming",
			"YUV Frames",
			"Passthrough",
		पूर्ण;
		अटल स्थिर अक्षर * स्थिर alpha_mode[4] = अणु
			"None",
			"Global",
			"Local",
			"Global and Local"
		पूर्ण;
		अटल स्थिर अक्षर * स्थिर pixel_क्रमmat[16] = अणु
			"ARGB Indexed",
			"RGB 5:6:5",
			"ARGB 1:5:5:5",
			"ARGB 1:4:4:4",
			"ARGB 8:8:8:8",
			"5",
			"6",
			"7",
			"AYUV Indexed",
			"YUV 5:6:5",
			"AYUV 1:5:5:5",
			"AYUV 1:4:4:4",
			"AYUV 8:8:8:8",
			"13",
			"14",
			"15",
		पूर्ण;

		ivtv_get_output(itv, itv->active_output, &viकरोut);
		ivtv_get_audio_output(itv, 0, &auकरोut);
		IVTV_INFO("Video Output: %s\n", viकरोut.name);
		अगर (mode < 0 || mode > OUT_PASSTHROUGH)
			mode = OUT_NONE;
		IVTV_INFO("Output Mode:  %s\n", output_modes[mode]);
		ivtv_vapi_result(itv, data, CX2341X_OSD_GET_STATE, 0);
		data[0] |= (पढ़ो_reg(0x2a00) >> 7) & 0x40;
		IVTV_INFO("Overlay:      %s, Alpha: %s, Pixel Format: %s\n",
			data[0] & 1 ? "On" : "Off",
			alpha_mode[(data[0] >> 1) & 0x3],
			pixel_क्रमmat[(data[0] >> 3) & 0xf]);
	पूर्ण
	IVTV_INFO("Tuner:  %s\n",
		test_bit(IVTV_F_I_RADIO_USER, &itv->i_flags) ? "Radio" : "TV");
	v4l2_ctrl_handler_log_status(&itv->cxhdl.hdl, itv->v4l2_dev.name);
	IVTV_INFO("Status flags:    0x%08lx\n", itv->i_flags);
	क्रम (i = 0; i < IVTV_MAX_STREAMS; i++) अणु
		काष्ठा ivtv_stream *s = &itv->streams[i];

		अगर (s->vdev.v4l2_dev == शून्य || s->buffers == 0)
			जारी;
		IVTV_INFO("Stream %s: status 0x%04lx, %d%% of %d KiB (%d buffers) in use\n", s->name, s->s_flags,
				(s->buffers - s->q_मुक्त.buffers) * 100 / s->buffers,
				(s->buffers * s->buf_size) / 1024, s->buffers);
	पूर्ण

	IVTV_INFO("Read MPG/VBI: %lld/%lld bytes\n",
			(दीर्घ दीर्घ)itv->mpg_data_received,
			(दीर्घ दीर्घ)itv->vbi_data_inserted);
	वापस 0;
पूर्ण

अटल पूर्णांक ivtv_decoder_cmd(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_decoder_cmd *dec)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(file->निजी_data);
	काष्ठा ivtv *itv = id->itv;

	IVTV_DEBUG_IOCTL("VIDIOC_DECODER_CMD %d\n", dec->cmd);
	वापस ivtv_video_command(itv, id, dec, false);
पूर्ण

अटल पूर्णांक ivtv_try_decoder_cmd(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_decoder_cmd *dec)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(file->निजी_data);
	काष्ठा ivtv *itv = id->itv;

	IVTV_DEBUG_IOCTL("VIDIOC_TRY_DECODER_CMD %d\n", dec->cmd);
	वापस ivtv_video_command(itv, id, dec, true);
पूर्ण

#अगर_घोषित CONFIG_VIDEO_IVTV_DEPRECATED_IOCTLS
अटल __अंतरभूत__ व्योम warn_deprecated_ioctl(स्थिर अक्षर *name)
अणु
	pr_warn_once("warning: the %s ioctl is deprecated. Don't use it, as it will be removed soon\n",
		     name);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_video_event अणु
	__s32 type;
	/* unused, make sure to use atomic समय क्रम y2038 अगर it ever माला_लो used */
	compat_दीर्घ_t बारtamp;
	जोड़ अणु
		video_माप_प्रकार size;
		अचिन्हित पूर्णांक frame_rate;        /* in frames per 1000sec */
		अचिन्हित अक्षर vsync_field;      /* unknown/odd/even/progressive */
	पूर्ण u;
पूर्ण;
#घोषणा VIDEO_GET_EVENT32 _IOR('o', 28, काष्ठा compat_video_event)
#पूर्ण_अगर

#पूर्ण_अगर

अटल पूर्णांक ivtv_decoder_ioctls(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा ivtv_खोलो_id *id = fh2id(filp->निजी_data);
	काष्ठा ivtv *itv = id->itv;
	काष्ठा ivtv_stream *s = &itv->streams[id->type];
#अगर_घोषित CONFIG_VIDEO_IVTV_DEPRECATED_IOCTLS
	पूर्णांक nonblocking = filp->f_flags & O_NONBLOCK;
	अचिन्हित दीर्घ iarg = (अचिन्हित दीर्घ)arg;
#पूर्ण_अगर

	चयन (cmd) अणु
	हाल IVTV_IOC_DMA_FRAME: अणु
		काष्ठा ivtv_dma_frame *args = arg;

		IVTV_DEBUG_IOCTL("IVTV_IOC_DMA_FRAME\n");
		अगर (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			वापस -EINVAL;
		अगर (args->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			वापस -EINVAL;
		अगर (itv->output_mode == OUT_UDMA_YUV && args->y_source == शून्य)
			वापस 0;
		अगर (ivtv_start_decoding(id, id->type)) अणु
			वापस -EBUSY;
		पूर्ण
		अगर (ivtv_set_output_mode(itv, OUT_UDMA_YUV) != OUT_UDMA_YUV) अणु
			ivtv_release_stream(s);
			वापस -EBUSY;
		पूर्ण
		/* Mark that this file handle started the UDMA_YUV mode */
		id->yuv_frames = 1;
		अगर (args->y_source == शून्य)
			वापस 0;
		वापस ivtv_yuv_prep_frame(itv, args);
	पूर्ण

	हाल IVTV_IOC_PASSTHROUGH_MODE:
		IVTV_DEBUG_IOCTL("IVTV_IOC_PASSTHROUGH_MODE\n");
		अगर (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			वापस -EINVAL;
		वापस ivtv_passthrough_mode(itv, *(पूर्णांक *)arg != 0);
#अगर_घोषित CONFIG_VIDEO_IVTV_DEPRECATED_IOCTLS
	हाल VIDEO_GET_PTS: अणु
		s64 *pts = arg;
		s64 frame;

		warn_deprecated_ioctl("VIDEO_GET_PTS");
		अगर (s->type < IVTV_DEC_STREAM_TYPE_MPG) अणु
			*pts = s->dma_pts;
			अवरोध;
		पूर्ण
		अगर (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			वापस -EINVAL;
		वापस ivtv_g_pts_frame(itv, pts, &frame);
	पूर्ण

	हाल VIDEO_GET_FRAME_COUNT: अणु
		s64 *frame = arg;
		s64 pts;

		warn_deprecated_ioctl("VIDEO_GET_FRAME_COUNT");
		अगर (s->type < IVTV_DEC_STREAM_TYPE_MPG) अणु
			*frame = 0;
			अवरोध;
		पूर्ण
		अगर (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			वापस -EINVAL;
		वापस ivtv_g_pts_frame(itv, &pts, frame);
	पूर्ण

	हाल VIDEO_PLAY: अणु
		काष्ठा v4l2_decoder_cmd dc;

		warn_deprecated_ioctl("VIDEO_PLAY");
		स_रखो(&dc, 0, माप(dc));
		dc.cmd = V4L2_DEC_CMD_START;
		वापस ivtv_video_command(itv, id, &dc, 0);
	पूर्ण

	हाल VIDEO_STOP: अणु
		काष्ठा v4l2_decoder_cmd dc;

		warn_deprecated_ioctl("VIDEO_STOP");
		स_रखो(&dc, 0, माप(dc));
		dc.cmd = V4L2_DEC_CMD_STOP;
		dc.flags = V4L2_DEC_CMD_STOP_TO_BLACK | V4L2_DEC_CMD_STOP_IMMEDIATELY;
		वापस ivtv_video_command(itv, id, &dc, 0);
	पूर्ण

	हाल VIDEO_FREEZE: अणु
		काष्ठा v4l2_decoder_cmd dc;

		warn_deprecated_ioctl("VIDEO_FREEZE");
		स_रखो(&dc, 0, माप(dc));
		dc.cmd = V4L2_DEC_CMD_PAUSE;
		वापस ivtv_video_command(itv, id, &dc, 0);
	पूर्ण

	हाल VIDEO_CONTINUE: अणु
		काष्ठा v4l2_decoder_cmd dc;

		warn_deprecated_ioctl("VIDEO_CONTINUE");
		स_रखो(&dc, 0, माप(dc));
		dc.cmd = V4L2_DEC_CMD_RESUME;
		वापस ivtv_video_command(itv, id, &dc, 0);
	पूर्ण

	हाल VIDEO_COMMAND:
	हाल VIDEO_TRY_COMMAND: अणु
		/* Note: काष्ठा v4l2_decoder_cmd has the same layout as
		   काष्ठा video_command */
		काष्ठा v4l2_decoder_cmd *dc = arg;
		पूर्णांक try = (cmd == VIDEO_TRY_COMMAND);

		अगर (try)
			warn_deprecated_ioctl("VIDEO_TRY_COMMAND");
		अन्यथा
			warn_deprecated_ioctl("VIDEO_COMMAND");
		वापस ivtv_video_command(itv, id, dc, try);
	पूर्ण

#अगर_घोषित CONFIG_COMPAT
	हाल VIDEO_GET_EVENT32:
#पूर्ण_अगर
	हाल VIDEO_GET_EVENT: अणु
#अगर_घोषित CONFIG_COMPAT
		काष्ठा compat_video_event *ev32 = arg;
#पूर्ण_अगर
		काष्ठा video_event *ev = arg;
		DEFINE_WAIT(रुको);

		warn_deprecated_ioctl("VIDEO_GET_EVENT");
		अगर (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			वापस -EINVAL;
		स_रखो(ev, 0, माप(*ev));
		set_bit(IVTV_F_I_EV_VSYNC_ENABLED, &itv->i_flags);

		जबतक (1) अणु
			अगर (test_and_clear_bit(IVTV_F_I_EV_DEC_STOPPED, &itv->i_flags))
				ev->type = VIDEO_EVENT_DECODER_STOPPED;
			अन्यथा अगर (test_and_clear_bit(IVTV_F_I_EV_VSYNC, &itv->i_flags)) अणु
				अचिन्हित अक्षर vsync_field;

				ev->type = VIDEO_EVENT_VSYNC;
				vsync_field = test_bit(IVTV_F_I_EV_VSYNC_FIELD, &itv->i_flags) ?
					VIDEO_VSYNC_FIELD_ODD : VIDEO_VSYNC_FIELD_EVEN;
				अगर (itv->output_mode == OUT_UDMA_YUV &&
					(itv->yuv_info.lace_mode & IVTV_YUV_MODE_MASK) ==
								IVTV_YUV_MODE_PROGRESSIVE) अणु
					vsync_field = VIDEO_VSYNC_FIELD_PROGRESSIVE;
				पूर्ण
#अगर_घोषित CONFIG_COMPAT
				अगर (cmd == VIDEO_GET_EVENT32)
					ev32->u.vsync_field = vsync_field;
				अन्यथा
#पूर्ण_अगर
					ev->u.vsync_field = vsync_field;
			पूर्ण
			अगर (ev->type)
				वापस 0;
			अगर (nonblocking)
				वापस -EAGAIN;
			/* Wait क्रम event. Note that serialize_lock is locked,
			   so to allow other processes to access the driver जबतक
			   we are रुकोing unlock first and later lock again. */
			mutex_unlock(&itv->serialize_lock);
			prepare_to_रुको(&itv->event_रुकोq, &रुको, TASK_INTERRUPTIBLE);
			अगर (!test_bit(IVTV_F_I_EV_DEC_STOPPED, &itv->i_flags) &&
			    !test_bit(IVTV_F_I_EV_VSYNC, &itv->i_flags))
				schedule();
			finish_रुको(&itv->event_रुकोq, &रुको);
			mutex_lock(&itv->serialize_lock);
			अगर (संकेत_pending(current)) अणु
				/* वापस अगर a संकेत was received */
				IVTV_DEBUG_INFO("User stopped wait for event\n");
				वापस -EINTR;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	हाल VIDEO_SELECT_SOURCE:
		warn_deprecated_ioctl("VIDEO_SELECT_SOURCE");
		अगर (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
			वापस -EINVAL;
		वापस ivtv_passthrough_mode(itv, iarg == VIDEO_SOURCE_DEMUX);

	हाल AUDIO_SET_MUTE:
		warn_deprecated_ioctl("AUDIO_SET_MUTE");
		itv->speed_mute_audio = iarg;
		वापस 0;

	हाल AUDIO_CHANNEL_SELECT:
		warn_deprecated_ioctl("AUDIO_CHANNEL_SELECT");
		अगर (iarg > AUDIO_STEREO_SWAPPED)
			वापस -EINVAL;
		वापस v4l2_ctrl_s_ctrl(itv->ctrl_audio_playback, iarg + 1);

	हाल AUDIO_BILINGUAL_CHANNEL_SELECT:
		warn_deprecated_ioctl("AUDIO_BILINGUAL_CHANNEL_SELECT");
		अगर (iarg > AUDIO_STEREO_SWAPPED)
			वापस -EINVAL;
		वापस v4l2_ctrl_s_ctrl(itv->ctrl_audio_multilingual_playback, iarg + 1);
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ ivtv_शेष(काष्ठा file *file, व्योम *fh, bool valid_prio,
			 अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा ivtv *itv = fh2id(fh)->itv;

	अगर (!valid_prio) अणु
		चयन (cmd) अणु
		हाल IVTV_IOC_PASSTHROUGH_MODE:
#अगर_घोषित CONFIG_VIDEO_IVTV_DEPRECATED_IOCTLS
		हाल VIDEO_PLAY:
		हाल VIDEO_STOP:
		हाल VIDEO_FREEZE:
		हाल VIDEO_CONTINUE:
		हाल VIDEO_COMMAND:
		हाल VIDEO_SELECT_SOURCE:
		हाल AUDIO_SET_MUTE:
		हाल AUDIO_CHANNEL_SELECT:
		हाल AUDIO_BILINGUAL_CHANNEL_SELECT:
#पूर्ण_अगर
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	चयन (cmd) अणु
	हाल VIDIOC_INT_RESET: अणु
		u32 val = *(u32 *)arg;

		अगर ((val == 0 && itv->options.newi2c) || (val & 0x01))
			ivtv_reset_ir_gpio(itv);
		अगर (val & 0x02)
			v4l2_subdev_call(itv->sd_video, core, reset, 0);
		अवरोध;
	पूर्ण

	हाल IVTV_IOC_DMA_FRAME:
	हाल IVTV_IOC_PASSTHROUGH_MODE:
#अगर_घोषित CONFIG_VIDEO_IVTV_DEPRECATED_IOCTLS
	हाल VIDEO_GET_PTS:
	हाल VIDEO_GET_FRAME_COUNT:
	हाल VIDEO_GET_EVENT:
	हाल VIDEO_PLAY:
	हाल VIDEO_STOP:
	हाल VIDEO_FREEZE:
	हाल VIDEO_CONTINUE:
	हाल VIDEO_COMMAND:
	हाल VIDEO_TRY_COMMAND:
	हाल VIDEO_SELECT_SOURCE:
	हाल AUDIO_SET_MUTE:
	हाल AUDIO_CHANNEL_SELECT:
	हाल AUDIO_BILINGUAL_CHANNEL_SELECT:
#पूर्ण_अगर
		वापस ivtv_decoder_ioctls(file, cmd, (व्योम *)arg);

	शेष:
		वापस -ENOTTY;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops ivtv_ioctl_ops = अणु
	.vidioc_querycap		    = ivtv_querycap,
	.vidioc_s_audio			    = ivtv_s_audio,
	.vidioc_g_audio			    = ivtv_g_audio,
	.vidioc_क्रमागतaudio		    = ivtv_क्रमागतaudio,
	.vidioc_s_auकरोut		    = ivtv_s_auकरोut,
	.vidioc_g_auकरोut		    = ivtv_g_auकरोut,
	.vidioc_क्रमागत_input		    = ivtv_क्रमागत_input,
	.vidioc_क्रमागत_output		    = ivtv_क्रमागत_output,
	.vidioc_क्रमागतauकरोut		    = ivtv_क्रमागतauकरोut,
	.vidioc_g_pixelaspect		    = ivtv_g_pixelaspect,
	.vidioc_s_selection		    = ivtv_s_selection,
	.vidioc_g_selection		    = ivtv_g_selection,
	.vidioc_g_input			    = ivtv_g_input,
	.vidioc_s_input			    = ivtv_s_input,
	.vidioc_g_output		    = ivtv_g_output,
	.vidioc_s_output		    = ivtv_s_output,
	.vidioc_g_frequency		    = ivtv_g_frequency,
	.vidioc_s_frequency		    = ivtv_s_frequency,
	.vidioc_s_tuner			    = ivtv_s_tuner,
	.vidioc_g_tuner			    = ivtv_g_tuner,
	.vidioc_g_enc_index		    = ivtv_g_enc_index,
	.vidioc_g_fbuf			    = ivtv_g_fbuf,
	.vidioc_s_fbuf			    = ivtv_s_fbuf,
	.vidioc_g_std			    = ivtv_g_std,
	.vidioc_s_std			    = ivtv_s_std,
	.vidioc_overlay			    = ivtv_overlay,
	.vidioc_log_status		    = ivtv_log_status,
	.vidioc_क्रमागत_fmt_vid_cap	    = ivtv_क्रमागत_fmt_vid_cap,
	.vidioc_encoder_cmd		    = ivtv_encoder_cmd,
	.vidioc_try_encoder_cmd		    = ivtv_try_encoder_cmd,
	.vidioc_decoder_cmd		    = ivtv_decoder_cmd,
	.vidioc_try_decoder_cmd		    = ivtv_try_decoder_cmd,
	.vidioc_क्रमागत_fmt_vid_out	    = ivtv_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_cap		    = ivtv_g_fmt_vid_cap,
	.vidioc_g_fmt_vbi_cap		    = ivtv_g_fmt_vbi_cap,
	.vidioc_g_fmt_sliced_vbi_cap        = ivtv_g_fmt_sliced_vbi_cap,
	.vidioc_g_fmt_vid_out               = ivtv_g_fmt_vid_out,
	.vidioc_g_fmt_vid_out_overlay       = ivtv_g_fmt_vid_out_overlay,
	.vidioc_g_fmt_sliced_vbi_out        = ivtv_g_fmt_sliced_vbi_out,
	.vidioc_s_fmt_vid_cap		    = ivtv_s_fmt_vid_cap,
	.vidioc_s_fmt_vbi_cap		    = ivtv_s_fmt_vbi_cap,
	.vidioc_s_fmt_sliced_vbi_cap        = ivtv_s_fmt_sliced_vbi_cap,
	.vidioc_s_fmt_vid_out               = ivtv_s_fmt_vid_out,
	.vidioc_s_fmt_vid_out_overlay       = ivtv_s_fmt_vid_out_overlay,
	.vidioc_s_fmt_sliced_vbi_out        = ivtv_s_fmt_sliced_vbi_out,
	.vidioc_try_fmt_vid_cap		    = ivtv_try_fmt_vid_cap,
	.vidioc_try_fmt_vbi_cap		    = ivtv_try_fmt_vbi_cap,
	.vidioc_try_fmt_sliced_vbi_cap      = ivtv_try_fmt_sliced_vbi_cap,
	.vidioc_try_fmt_vid_out		    = ivtv_try_fmt_vid_out,
	.vidioc_try_fmt_vid_out_overlay     = ivtv_try_fmt_vid_out_overlay,
	.vidioc_try_fmt_sliced_vbi_out	    = ivtv_try_fmt_sliced_vbi_out,
	.vidioc_g_sliced_vbi_cap	    = ivtv_g_sliced_vbi_cap,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर		    = ivtv_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर		    = ivtv_s_रेजिस्टर,
#पूर्ण_अगर
	.vidioc_शेष			    = ivtv_शेष,
	.vidioc_subscribe_event		    = ivtv_subscribe_event,
	.vidioc_unsubscribe_event	    = v4l2_event_unsubscribe,
पूर्ण;

व्योम ivtv_set_funcs(काष्ठा video_device *vdev)
अणु
	vdev->ioctl_ops = &ivtv_ioctl_ops;
पूर्ण
