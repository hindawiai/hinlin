<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-vid-cap.c - video capture support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-rect.h>

#समावेश "vivid-core.h"
#समावेश "vivid-vid-common.h"
#समावेश "vivid-kthread-cap.h"
#समावेश "vivid-vid-cap.h"

अटल स्थिर काष्ठा vivid_fmt क्रमmats_ovl[] = अणु
	अणु
		.fourcc   = V4L2_PIX_FMT_RGB565, /* gggbbbbb rrrrrggg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_XRGB555, /* gggbbbbb arrrrrgg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
	अणु
		.fourcc   = V4L2_PIX_FMT_ARGB555, /* gggbbbbb arrrrrgg */
		.vकरोwnsampling = अणु 1 पूर्ण,
		.bit_depth = अणु 16 पूर्ण,
		.planes   = 1,
		.buffers = 1,
	पूर्ण,
पूर्ण;

/* The number of discrete webcam framesizes */
#घोषणा VIVID_WEBCAM_SIZES 6
/* The number of discrete webcam frameपूर्णांकervals */
#घोषणा VIVID_WEBCAM_IVALS (VIVID_WEBCAM_SIZES * 2)

/* Sizes must be in increasing order */
अटल स्थिर काष्ठा v4l2_frmsize_discrete webcam_sizes[VIVID_WEBCAM_SIZES] = अणु
	अणु  320, 180 पूर्ण,
	अणु  640, 360 पूर्ण,
	अणु  640, 480 पूर्ण,
	अणु 1280, 720 पूर्ण,
	अणु 1920, 1080 पूर्ण,
	अणु 3840, 2160 पूर्ण,
पूर्ण;

/*
 * Intervals must be in increasing order and there must be twice as many
 * elements in this array as there are in webcam_sizes.
 */
अटल स्थिर काष्ठा v4l2_fract webcam_पूर्णांकervals[VIVID_WEBCAM_IVALS] = अणु
	अणु  1, 1 पूर्ण,
	अणु  1, 2 पूर्ण,
	अणु  1, 4 पूर्ण,
	अणु  1, 5 पूर्ण,
	अणु  1, 10 पूर्ण,
	अणु  2, 25 पूर्ण,
	अणु  1, 15 पूर्ण,
	अणु  1, 25 पूर्ण,
	अणु  1, 30 पूर्ण,
	अणु  1, 40 पूर्ण,
	अणु  1, 50 पूर्ण,
	अणु  1, 60 पूर्ण,
पूर्ण;

अटल पूर्णांक vid_cap_queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित *nbuffers, अचिन्हित *nplanes,
		       अचिन्हित sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);
	अचिन्हित buffers = tpg_g_buffers(&dev->tpg);
	अचिन्हित h = dev->fmt_cap_rect.height;
	अचिन्हित p;

	अगर (dev->field_cap == V4L2_FIELD_ALTERNATE) अणु
		/*
		 * You cannot use पढ़ो() with FIELD_ALTERNATE since the field
		 * inक्रमmation (TOP/BOTTOM) cannot be passed back to the user.
		 */
		अगर (vb2_fileio_is_active(vq))
			वापस -EINVAL;
	पूर्ण

	अगर (dev->queue_setup_error) अणु
		/*
		 * Error injection: test what happens अगर queue_setup() वापसs
		 * an error.
		 */
		dev->queue_setup_error = false;
		वापस -EINVAL;
	पूर्ण
	अगर (*nplanes) अणु
		/*
		 * Check अगर the number of requested planes match
		 * the number of buffers in the current क्रमmat. You can't mix that.
		 */
		अगर (*nplanes != buffers)
			वापस -EINVAL;
		क्रम (p = 0; p < buffers; p++) अणु
			अगर (sizes[p] < tpg_g_line_width(&dev->tpg, p) * h +
						dev->fmt_cap->data_offset[p])
				वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (p = 0; p < buffers; p++)
			sizes[p] = (tpg_g_line_width(&dev->tpg, p) * h) /
					dev->fmt_cap->vकरोwnsampling[p] +
					dev->fmt_cap->data_offset[p];
	पूर्ण

	अगर (vq->num_buffers + *nbuffers < 2)
		*nbuffers = 2 - vq->num_buffers;

	*nplanes = buffers;

	dprपूर्णांकk(dev, 1, "%s: count=%d\n", __func__, *nbuffers);
	क्रम (p = 0; p < buffers; p++)
		dprपूर्णांकk(dev, 1, "%s: size[%u]=%u\n", __func__, p, sizes[p]);

	वापस 0;
पूर्ण

अटल पूर्णांक vid_cap_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ size;
	अचिन्हित buffers = tpg_g_buffers(&dev->tpg);
	अचिन्हित p;

	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	अगर (WARN_ON(शून्य == dev->fmt_cap))
		वापस -EINVAL;

	अगर (dev->buf_prepare_error) अणु
		/*
		 * Error injection: test what happens अगर buf_prepare() वापसs
		 * an error.
		 */
		dev->buf_prepare_error = false;
		वापस -EINVAL;
	पूर्ण
	क्रम (p = 0; p < buffers; p++) अणु
		size = (tpg_g_line_width(&dev->tpg, p) *
			dev->fmt_cap_rect.height) /
			dev->fmt_cap->vकरोwnsampling[p] +
			dev->fmt_cap->data_offset[p];

		अगर (vb2_plane_size(vb, p) < size) अणु
			dprपूर्णांकk(dev, 1, "%s data will not fit into plane %u (%lu < %lu)\n",
					__func__, p, vb2_plane_size(vb, p), size);
			वापस -EINVAL;
		पूर्ण

		vb2_set_plane_payload(vb, p, size);
		vb->planes[p].data_offset = dev->fmt_cap->data_offset[p];
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vid_cap_buf_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा v4l2_समयcode *tc = &vbuf->समयcode;
	अचिन्हित fps = 25;
	अचिन्हित seq = vbuf->sequence;

	अगर (!vivid_is_sdtv_cap(dev))
		वापस;

	/*
	 * Set the समयcode. Rarely used, so it is पूर्णांकeresting to
	 * test this.
	 */
	vbuf->flags |= V4L2_BUF_FLAG_TIMECODE;
	अगर (dev->std_cap[dev->input] & V4L2_STD_525_60)
		fps = 30;
	tc->type = (fps == 30) ? V4L2_TC_TYPE_30FPS : V4L2_TC_TYPE_25FPS;
	tc->flags = 0;
	tc->frames = seq % fps;
	tc->seconds = (seq / fps) % 60;
	tc->minutes = (seq / (60 * fps)) % 60;
	tc->hours = (seq / (60 * 60 * fps)) % 24;
पूर्ण

अटल व्योम vid_cap_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vivid_buffer *buf = container_of(vbuf, काष्ठा vivid_buffer, vb);

	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	spin_lock(&dev->slock);
	list_add_tail(&buf->list, &dev->vid_cap_active);
	spin_unlock(&dev->slock);
पूर्ण

अटल पूर्णांक vid_cap_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित count)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);
	अचिन्हित i;
	पूर्णांक err;

	अगर (vb2_is_streaming(&dev->vb_vid_out_q))
		dev->can_loop_video = vivid_vid_can_loop(dev);

	dev->vid_cap_seq_count = 0;
	dprपूर्णांकk(dev, 1, "%s\n", __func__);
	क्रम (i = 0; i < VIDEO_MAX_FRAME; i++)
		dev->must_blank[i] = tpg_g_perc_fill(&dev->tpg) < 100;
	अगर (dev->start_streaming_error) अणु
		dev->start_streaming_error = false;
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		err = vivid_start_generating_vid_cap(dev, &dev->vid_cap_streaming);
	पूर्ण
	अगर (err) अणु
		काष्ठा vivid_buffer *buf, *पंचांगp;

		list_क्रम_each_entry_safe(buf, पंचांगp, &dev->vid_cap_active, list) अणु
			list_del(&buf->list);
			vb2_buffer_करोne(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/* पात streaming and रुको क्रम last buffer */
अटल व्योम vid_cap_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);

	dprपूर्णांकk(dev, 1, "%s\n", __func__);
	vivid_stop_generating_vid_cap(dev, &dev->vid_cap_streaming);
	dev->can_loop_video = false;
पूर्ण

अटल व्योम vid_cap_buf_request_complete(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_ctrl_request_complete(vb->req_obj.req, &dev->ctrl_hdl_vid_cap);
पूर्ण

स्थिर काष्ठा vb2_ops vivid_vid_cap_qops = अणु
	.queue_setup		= vid_cap_queue_setup,
	.buf_prepare		= vid_cap_buf_prepare,
	.buf_finish		= vid_cap_buf_finish,
	.buf_queue		= vid_cap_buf_queue,
	.start_streaming	= vid_cap_start_streaming,
	.stop_streaming		= vid_cap_stop_streaming,
	.buf_request_complete	= vid_cap_buf_request_complete,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

/*
 * Determine the 'picture' quality based on the current TV frequency: either
 * COLOR क्रम a good 'signal', GRAY (grayscale picture) क्रम a slightly off
 * संकेत or NOISE क्रम no संकेत.
 */
व्योम vivid_update_quality(काष्ठा vivid_dev *dev)
अणु
	अचिन्हित freq_modulus;

	अगर (dev->loop_video && (vivid_is_svid_cap(dev) || vivid_is_hdmi_cap(dev))) अणु
		/*
		 * The 'noise' will only be replaced by the actual video
		 * अगर the output video matches the input video settings.
		 */
		tpg_s_quality(&dev->tpg, TPG_QUAL_NOISE, 0);
		वापस;
	पूर्ण
	अगर (vivid_is_hdmi_cap(dev) &&
	    VIVID_INVALID_SIGNAL(dev->dv_timings_संकेत_mode[dev->input])) अणु
		tpg_s_quality(&dev->tpg, TPG_QUAL_NOISE, 0);
		वापस;
	पूर्ण
	अगर (vivid_is_sdtv_cap(dev) &&
	    VIVID_INVALID_SIGNAL(dev->std_संकेत_mode[dev->input])) अणु
		tpg_s_quality(&dev->tpg, TPG_QUAL_NOISE, 0);
		वापस;
	पूर्ण
	अगर (!vivid_is_tv_cap(dev)) अणु
		tpg_s_quality(&dev->tpg, TPG_QUAL_COLOR, 0);
		वापस;
	पूर्ण

	/*
	 * There is a fake channel every 6 MHz at 49.25, 55.25, etc.
	 * From +/- 0.25 MHz around the channel there is color, and from
	 * +/- 1 MHz there is grayscale (chroma is lost).
	 * Everywhere अन्यथा it is just noise.
	 */
	freq_modulus = (dev->tv_freq - 676 /* (43.25-1) * 16 */) % (6 * 16);
	अगर (freq_modulus > 2 * 16) अणु
		tpg_s_quality(&dev->tpg, TPG_QUAL_NOISE,
			next_pseuकरो_अक्रमom32(dev->tv_freq ^ 0x55) & 0x3f);
		वापस;
	पूर्ण
	अगर (freq_modulus < 12 /*0.75 * 16*/ || freq_modulus > 20 /*1.25 * 16*/)
		tpg_s_quality(&dev->tpg, TPG_QUAL_GRAY, 0);
	अन्यथा
		tpg_s_quality(&dev->tpg, TPG_QUAL_COLOR, 0);
पूर्ण

/*
 * Get the current picture quality and the associated afc value.
 */
अटल क्रमागत tpg_quality vivid_get_quality(काष्ठा vivid_dev *dev, s32 *afc)
अणु
	अचिन्हित freq_modulus;

	अगर (afc)
		*afc = 0;
	अगर (tpg_g_quality(&dev->tpg) == TPG_QUAL_COLOR ||
	    tpg_g_quality(&dev->tpg) == TPG_QUAL_NOISE)
		वापस tpg_g_quality(&dev->tpg);

	/*
	 * There is a fake channel every 6 MHz at 49.25, 55.25, etc.
	 * From +/- 0.25 MHz around the channel there is color, and from
	 * +/- 1 MHz there is grayscale (chroma is lost).
	 * Everywhere अन्यथा it is just gray.
	 */
	freq_modulus = (dev->tv_freq - 676 /* (43.25-1) * 16 */) % (6 * 16);
	अगर (afc)
		*afc = freq_modulus - 1 * 16;
	वापस TPG_QUAL_GRAY;
पूर्ण

क्रमागत tpg_video_aspect vivid_get_video_aspect(स्थिर काष्ठा vivid_dev *dev)
अणु
	अगर (vivid_is_sdtv_cap(dev))
		वापस dev->std_aspect_ratio[dev->input];

	अगर (vivid_is_hdmi_cap(dev))
		वापस dev->dv_timings_aspect_ratio[dev->input];

	वापस TPG_VIDEO_ASPECT_IMAGE;
पूर्ण

अटल क्रमागत tpg_pixel_aspect vivid_get_pixel_aspect(स्थिर काष्ठा vivid_dev *dev)
अणु
	अगर (vivid_is_sdtv_cap(dev))
		वापस (dev->std_cap[dev->input] & V4L2_STD_525_60) ?
			TPG_PIXEL_ASPECT_NTSC : TPG_PIXEL_ASPECT_PAL;

	अगर (vivid_is_hdmi_cap(dev) &&
	    dev->src_rect.width == 720 && dev->src_rect.height <= 576)
		वापस dev->src_rect.height == 480 ?
			TPG_PIXEL_ASPECT_NTSC : TPG_PIXEL_ASPECT_PAL;

	वापस TPG_PIXEL_ASPECT_SQUARE;
पूर्ण

/*
 * Called whenever the क्रमmat has to be reset which can occur when
 * changing inमाला_दो, standard, timings, etc.
 */
व्योम vivid_update_क्रमmat_cap(काष्ठा vivid_dev *dev, bool keep_controls)
अणु
	काष्ठा v4l2_bt_timings *bt = &dev->dv_timings_cap[dev->input].bt;
	अचिन्हित size;
	u64 pixelघड़ी;

	चयन (dev->input_type[dev->input]) अणु
	हाल WEBCAM:
	शेष:
		dev->src_rect.width = webcam_sizes[dev->webcam_size_idx].width;
		dev->src_rect.height = webcam_sizes[dev->webcam_size_idx].height;
		dev->समयperframe_vid_cap = webcam_पूर्णांकervals[dev->webcam_ival_idx];
		dev->field_cap = V4L2_FIELD_NONE;
		tpg_s_rgb_range(&dev->tpg, V4L2_DV_RGB_RANGE_AUTO);
		अवरोध;
	हाल TV:
	हाल SVID:
		dev->field_cap = dev->tv_field_cap;
		dev->src_rect.width = 720;
		अगर (dev->std_cap[dev->input] & V4L2_STD_525_60) अणु
			dev->src_rect.height = 480;
			dev->समयperframe_vid_cap = (काष्ठा v4l2_fract) अणु 1001, 30000 पूर्ण;
			dev->service_set_cap = V4L2_SLICED_CAPTION_525;
		पूर्ण अन्यथा अणु
			dev->src_rect.height = 576;
			dev->समयperframe_vid_cap = (काष्ठा v4l2_fract) अणु 1000, 25000 पूर्ण;
			dev->service_set_cap = V4L2_SLICED_WSS_625 | V4L2_SLICED_TELETEXT_B;
		पूर्ण
		tpg_s_rgb_range(&dev->tpg, V4L2_DV_RGB_RANGE_AUTO);
		अवरोध;
	हाल HDMI:
		dev->src_rect.width = bt->width;
		dev->src_rect.height = bt->height;
		size = V4L2_DV_BT_FRAME_WIDTH(bt) * V4L2_DV_BT_FRAME_HEIGHT(bt);
		अगर (dev->reduced_fps && can_reduce_fps(bt)) अणु
			pixelघड़ी = भाग_u64(bt->pixelघड़ी * 1000, 1001);
			bt->flags |= V4L2_DV_FL_REDUCED_FPS;
		पूर्ण अन्यथा अणु
			pixelघड़ी = bt->pixelघड़ी;
			bt->flags &= ~V4L2_DV_FL_REDUCED_FPS;
		पूर्ण
		dev->समयperframe_vid_cap = (काष्ठा v4l2_fract) अणु
			size / 100, (u32)pixelघड़ी / 100
		पूर्ण;
		अगर (bt->पूर्णांकerlaced)
			dev->field_cap = V4L2_FIELD_ALTERNATE;
		अन्यथा
			dev->field_cap = V4L2_FIELD_NONE;

		/*
		 * We can be called from within s_ctrl, in that हाल we can't
		 * set/get controls. Luckily we करोn't need to in that हाल.
		 */
		अगर (keep_controls || !dev->colorspace)
			अवरोध;
		अगर (bt->flags & V4L2_DV_FL_IS_CE_VIDEO) अणु
			अगर (bt->width == 720 && bt->height <= 576)
				v4l2_ctrl_s_ctrl(dev->colorspace, VIVID_CS_170M);
			अन्यथा
				v4l2_ctrl_s_ctrl(dev->colorspace, VIVID_CS_709);
			v4l2_ctrl_s_ctrl(dev->real_rgb_range_cap, 1);
		पूर्ण अन्यथा अणु
			v4l2_ctrl_s_ctrl(dev->colorspace, VIVID_CS_SRGB);
			v4l2_ctrl_s_ctrl(dev->real_rgb_range_cap, 0);
		पूर्ण
		tpg_s_rgb_range(&dev->tpg, v4l2_ctrl_g_ctrl(dev->rgb_range_cap));
		अवरोध;
	पूर्ण
	vमुक्त(dev->biपंचांगap_cap);
	dev->biपंचांगap_cap = शून्य;
	vivid_update_quality(dev);
	tpg_reset_source(&dev->tpg, dev->src_rect.width, dev->src_rect.height, dev->field_cap);
	dev->crop_cap = dev->src_rect;
	dev->crop_bounds_cap = dev->src_rect;
	dev->compose_cap = dev->crop_cap;
	अगर (V4L2_FIELD_HAS_T_OR_B(dev->field_cap))
		dev->compose_cap.height /= 2;
	dev->fmt_cap_rect = dev->compose_cap;
	tpg_s_video_aspect(&dev->tpg, vivid_get_video_aspect(dev));
	tpg_s_pixel_aspect(&dev->tpg, vivid_get_pixel_aspect(dev));
	tpg_update_mv_step(&dev->tpg);
पूर्ण

/* Map the field to something that is valid क्रम the current input */
अटल क्रमागत v4l2_field vivid_field_cap(काष्ठा vivid_dev *dev, क्रमागत v4l2_field field)
अणु
	अगर (vivid_is_sdtv_cap(dev)) अणु
		चयन (field) अणु
		हाल V4L2_FIELD_INTERLACED_TB:
		हाल V4L2_FIELD_INTERLACED_BT:
		हाल V4L2_FIELD_SEQ_TB:
		हाल V4L2_FIELD_SEQ_BT:
		हाल V4L2_FIELD_TOP:
		हाल V4L2_FIELD_BOTTOM:
		हाल V4L2_FIELD_ALTERNATE:
			वापस field;
		हाल V4L2_FIELD_INTERLACED:
		शेष:
			वापस V4L2_FIELD_INTERLACED;
		पूर्ण
	पूर्ण
	अगर (vivid_is_hdmi_cap(dev))
		वापस dev->dv_timings_cap[dev->input].bt.पूर्णांकerlaced ?
			V4L2_FIELD_ALTERNATE : V4L2_FIELD_NONE;
	वापस V4L2_FIELD_NONE;
पूर्ण

अटल अचिन्हित vivid_colorspace_cap(काष्ठा vivid_dev *dev)
अणु
	अगर (!dev->loop_video || vivid_is_webcam(dev) || vivid_is_tv_cap(dev))
		वापस tpg_g_colorspace(&dev->tpg);
	वापस dev->colorspace_out;
पूर्ण

अटल अचिन्हित vivid_xfer_func_cap(काष्ठा vivid_dev *dev)
अणु
	अगर (!dev->loop_video || vivid_is_webcam(dev) || vivid_is_tv_cap(dev))
		वापस tpg_g_xfer_func(&dev->tpg);
	वापस dev->xfer_func_out;
पूर्ण

अटल अचिन्हित vivid_ycbcr_enc_cap(काष्ठा vivid_dev *dev)
अणु
	अगर (!dev->loop_video || vivid_is_webcam(dev) || vivid_is_tv_cap(dev))
		वापस tpg_g_ycbcr_enc(&dev->tpg);
	वापस dev->ycbcr_enc_out;
पूर्ण

अटल अचिन्हित पूर्णांक vivid_hsv_enc_cap(काष्ठा vivid_dev *dev)
अणु
	अगर (!dev->loop_video || vivid_is_webcam(dev) || vivid_is_tv_cap(dev))
		वापस tpg_g_hsv_enc(&dev->tpg);
	वापस dev->hsv_enc_out;
पूर्ण

अटल अचिन्हित vivid_quantization_cap(काष्ठा vivid_dev *dev)
अणु
	अगर (!dev->loop_video || vivid_is_webcam(dev) || vivid_is_tv_cap(dev))
		वापस tpg_g_quantization(&dev->tpg);
	वापस dev->quantization_out;
पूर्ण

पूर्णांक vivid_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat_mplane *mp = &f->fmt.pix_mp;
	अचिन्हित p;

	mp->width        = dev->fmt_cap_rect.width;
	mp->height       = dev->fmt_cap_rect.height;
	mp->field        = dev->field_cap;
	mp->pixelक्रमmat  = dev->fmt_cap->fourcc;
	mp->colorspace   = vivid_colorspace_cap(dev);
	mp->xfer_func    = vivid_xfer_func_cap(dev);
	अगर (dev->fmt_cap->color_enc == TGP_COLOR_ENC_HSV)
		mp->hsv_enc    = vivid_hsv_enc_cap(dev);
	अन्यथा
		mp->ycbcr_enc    = vivid_ycbcr_enc_cap(dev);
	mp->quantization = vivid_quantization_cap(dev);
	mp->num_planes = dev->fmt_cap->buffers;
	क्रम (p = 0; p < mp->num_planes; p++) अणु
		mp->plane_fmt[p].bytesperline = tpg_g_bytesperline(&dev->tpg, p);
		mp->plane_fmt[p].sizeimage =
			(tpg_g_line_width(&dev->tpg, p) * mp->height) /
			dev->fmt_cap->vकरोwnsampling[p] +
			dev->fmt_cap->data_offset[p];
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vivid_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *mp = &f->fmt.pix_mp;
	काष्ठा v4l2_plane_pix_क्रमmat *pfmt = mp->plane_fmt;
	काष्ठा vivid_dev *dev = video_drvdata(file);
	स्थिर काष्ठा vivid_fmt *fmt;
	अचिन्हित bytesperline, max_bpl;
	अचिन्हित factor = 1;
	अचिन्हित w, h;
	अचिन्हित p;
	bool user_set_csc = !!(mp->flags & V4L2_PIX_FMT_FLAG_SET_CSC);

	fmt = vivid_get_क्रमmat(dev, mp->pixelक्रमmat);
	अगर (!fmt) अणु
		dprपूर्णांकk(dev, 1, "Fourcc format (0x%08x) unknown.\n",
			mp->pixelक्रमmat);
		mp->pixelक्रमmat = V4L2_PIX_FMT_YUYV;
		fmt = vivid_get_क्रमmat(dev, mp->pixelक्रमmat);
	पूर्ण

	mp->field = vivid_field_cap(dev, mp->field);
	अगर (vivid_is_webcam(dev)) अणु
		स्थिर काष्ठा v4l2_frmsize_discrete *sz =
			v4l2_find_nearest_size(webcam_sizes,
					       VIVID_WEBCAM_SIZES, width,
					       height, mp->width, mp->height);

		w = sz->width;
		h = sz->height;
	पूर्ण अन्यथा अगर (vivid_is_sdtv_cap(dev)) अणु
		w = 720;
		h = (dev->std_cap[dev->input] & V4L2_STD_525_60) ? 480 : 576;
	पूर्ण अन्यथा अणु
		w = dev->src_rect.width;
		h = dev->src_rect.height;
	पूर्ण
	अगर (V4L2_FIELD_HAS_T_OR_B(mp->field))
		factor = 2;
	अगर (vivid_is_webcam(dev) ||
	    (!dev->has_scaler_cap && !dev->has_crop_cap && !dev->has_compose_cap)) अणु
		mp->width = w;
		mp->height = h / factor;
	पूर्ण अन्यथा अणु
		काष्ठा v4l2_rect r = अणु 0, 0, mp->width, mp->height * factor पूर्ण;

		v4l2_rect_set_min_size(&r, &vivid_min_rect);
		v4l2_rect_set_max_size(&r, &vivid_max_rect);
		अगर (dev->has_scaler_cap && !dev->has_compose_cap) अणु
			काष्ठा v4l2_rect max_r = अणु 0, 0, MAX_ZOOM * w, MAX_ZOOM * h पूर्ण;

			v4l2_rect_set_max_size(&r, &max_r);
		पूर्ण अन्यथा अगर (!dev->has_scaler_cap && dev->has_crop_cap && !dev->has_compose_cap) अणु
			v4l2_rect_set_max_size(&r, &dev->src_rect);
		पूर्ण अन्यथा अगर (!dev->has_scaler_cap && !dev->has_crop_cap) अणु
			v4l2_rect_set_min_size(&r, &dev->src_rect);
		पूर्ण
		mp->width = r.width;
		mp->height = r.height / factor;
	पूर्ण

	/* This driver supports custom bytesperline values */

	mp->num_planes = fmt->buffers;
	क्रम (p = 0; p < fmt->buffers; p++) अणु
		/* Calculate the minimum supported bytesperline value */
		bytesperline = (mp->width * fmt->bit_depth[p]) >> 3;
		/* Calculate the maximum supported bytesperline value */
		max_bpl = (MAX_ZOOM * MAX_WIDTH * fmt->bit_depth[p]) >> 3;

		अगर (pfmt[p].bytesperline > max_bpl)
			pfmt[p].bytesperline = max_bpl;
		अगर (pfmt[p].bytesperline < bytesperline)
			pfmt[p].bytesperline = bytesperline;

		pfmt[p].sizeimage = (pfmt[p].bytesperline * mp->height) /
				fmt->vकरोwnsampling[p] + fmt->data_offset[p];

		स_रखो(pfmt[p].reserved, 0, माप(pfmt[p].reserved));
	पूर्ण
	क्रम (p = fmt->buffers; p < fmt->planes; p++)
		pfmt[0].sizeimage += (pfmt[0].bytesperline * mp->height *
			(fmt->bit_depth[p] / fmt->vकरोwnsampling[p])) /
			(fmt->bit_depth[0] / fmt->vकरोwnsampling[0]);

	अगर (!user_set_csc || !v4l2_is_colorspace_valid(mp->colorspace))
		mp->colorspace = vivid_colorspace_cap(dev);

	अगर (!user_set_csc || !v4l2_is_xfer_func_valid(mp->xfer_func))
		mp->xfer_func = vivid_xfer_func_cap(dev);

	अगर (fmt->color_enc == TGP_COLOR_ENC_HSV) अणु
		अगर (!user_set_csc || !v4l2_is_hsv_enc_valid(mp->hsv_enc))
			mp->hsv_enc = vivid_hsv_enc_cap(dev);
	पूर्ण अन्यथा अगर (fmt->color_enc == TGP_COLOR_ENC_YCBCR) अणु
		अगर (!user_set_csc || !v4l2_is_ycbcr_enc_valid(mp->ycbcr_enc))
			mp->ycbcr_enc = vivid_ycbcr_enc_cap(dev);
	पूर्ण अन्यथा अणु
		mp->ycbcr_enc = vivid_ycbcr_enc_cap(dev);
	पूर्ण

	अगर (fmt->color_enc == TGP_COLOR_ENC_YCBCR ||
	    fmt->color_enc == TGP_COLOR_ENC_RGB) अणु
		अगर (!user_set_csc || !v4l2_is_quant_valid(mp->quantization))
			mp->quantization = vivid_quantization_cap(dev);
	पूर्ण अन्यथा अणु
		mp->quantization = vivid_quantization_cap(dev);
	पूर्ण

	स_रखो(mp->reserved, 0, माप(mp->reserved));
	वापस 0;
पूर्ण

पूर्णांक vivid_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *mp = &f->fmt.pix_mp;
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_rect *crop = &dev->crop_cap;
	काष्ठा v4l2_rect *compose = &dev->compose_cap;
	काष्ठा vb2_queue *q = &dev->vb_vid_cap_q;
	पूर्णांक ret = vivid_try_fmt_vid_cap(file, priv, f);
	अचिन्हित factor = 1;
	अचिन्हित p;
	अचिन्हित i;

	अगर (ret < 0)
		वापस ret;

	अगर (vb2_is_busy(q)) अणु
		dprपूर्णांकk(dev, 1, "%s device busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	अगर (dev->overlay_cap_owner && dev->fb_cap.fmt.pixelक्रमmat != mp->pixelक्रमmat) अणु
		dprपूर्णांकk(dev, 1, "overlay is active, can't change pixelformat\n");
		वापस -EBUSY;
	पूर्ण

	dev->fmt_cap = vivid_get_क्रमmat(dev, mp->pixelक्रमmat);
	अगर (V4L2_FIELD_HAS_T_OR_B(mp->field))
		factor = 2;

	/* Note: the webcam input करोesn't support scaling, cropping or composing */

	अगर (!vivid_is_webcam(dev) &&
	    (dev->has_scaler_cap || dev->has_crop_cap || dev->has_compose_cap)) अणु
		काष्ठा v4l2_rect r = अणु 0, 0, mp->width, mp->height पूर्ण;

		अगर (dev->has_scaler_cap) अणु
			अगर (dev->has_compose_cap)
				v4l2_rect_map_inside(compose, &r);
			अन्यथा
				*compose = r;
			अगर (dev->has_crop_cap && !dev->has_compose_cap) अणु
				काष्ठा v4l2_rect min_r = अणु
					0, 0,
					r.width / MAX_ZOOM,
					factor * r.height / MAX_ZOOM
				पूर्ण;
				काष्ठा v4l2_rect max_r = अणु
					0, 0,
					r.width * MAX_ZOOM,
					factor * r.height * MAX_ZOOM
				पूर्ण;

				v4l2_rect_set_min_size(crop, &min_r);
				v4l2_rect_set_max_size(crop, &max_r);
				v4l2_rect_map_inside(crop, &dev->crop_bounds_cap);
			पूर्ण अन्यथा अगर (dev->has_crop_cap) अणु
				काष्ठा v4l2_rect min_r = अणु
					0, 0,
					compose->width / MAX_ZOOM,
					factor * compose->height / MAX_ZOOM
				पूर्ण;
				काष्ठा v4l2_rect max_r = अणु
					0, 0,
					compose->width * MAX_ZOOM,
					factor * compose->height * MAX_ZOOM
				पूर्ण;

				v4l2_rect_set_min_size(crop, &min_r);
				v4l2_rect_set_max_size(crop, &max_r);
				v4l2_rect_map_inside(crop, &dev->crop_bounds_cap);
			पूर्ण
		पूर्ण अन्यथा अगर (dev->has_crop_cap && !dev->has_compose_cap) अणु
			r.height *= factor;
			v4l2_rect_set_माप_प्रकारo(crop, &r);
			v4l2_rect_map_inside(crop, &dev->crop_bounds_cap);
			r = *crop;
			r.height /= factor;
			v4l2_rect_set_माप_प्रकारo(compose, &r);
		पूर्ण अन्यथा अगर (!dev->has_crop_cap) अणु
			v4l2_rect_map_inside(compose, &r);
		पूर्ण अन्यथा अणु
			r.height *= factor;
			v4l2_rect_set_max_size(crop, &r);
			v4l2_rect_map_inside(crop, &dev->crop_bounds_cap);
			compose->top *= factor;
			compose->height *= factor;
			v4l2_rect_set_माप_प्रकारo(compose, crop);
			v4l2_rect_map_inside(compose, &r);
			compose->top /= factor;
			compose->height /= factor;
		पूर्ण
	पूर्ण अन्यथा अगर (vivid_is_webcam(dev)) अणु
		/* Guaranteed to be a match */
		क्रम (i = 0; i < ARRAY_SIZE(webcam_sizes); i++)
			अगर (webcam_sizes[i].width == mp->width &&
					webcam_sizes[i].height == mp->height)
				अवरोध;
		dev->webcam_size_idx = i;
		अगर (dev->webcam_ival_idx >= 2 * (VIVID_WEBCAM_SIZES - i))
			dev->webcam_ival_idx = 2 * (VIVID_WEBCAM_SIZES - i) - 1;
		vivid_update_क्रमmat_cap(dev, false);
	पूर्ण अन्यथा अणु
		काष्ठा v4l2_rect r = अणु 0, 0, mp->width, mp->height पूर्ण;

		v4l2_rect_set_माप_प्रकारo(compose, &r);
		r.height *= factor;
		v4l2_rect_set_माप_प्रकारo(crop, &r);
	पूर्ण

	dev->fmt_cap_rect.width = mp->width;
	dev->fmt_cap_rect.height = mp->height;
	tpg_s_buf_height(&dev->tpg, mp->height);
	tpg_s_fourcc(&dev->tpg, dev->fmt_cap->fourcc);
	क्रम (p = 0; p < tpg_g_buffers(&dev->tpg); p++)
		tpg_s_bytesperline(&dev->tpg, p, mp->plane_fmt[p].bytesperline);
	dev->field_cap = mp->field;
	अगर (dev->field_cap == V4L2_FIELD_ALTERNATE)
		tpg_s_field(&dev->tpg, V4L2_FIELD_TOP, true);
	अन्यथा
		tpg_s_field(&dev->tpg, dev->field_cap, false);
	tpg_s_crop_compose(&dev->tpg, &dev->crop_cap, &dev->compose_cap);
	अगर (vivid_is_sdtv_cap(dev))
		dev->tv_field_cap = mp->field;
	tpg_update_mv_step(&dev->tpg);
	dev->tpg.colorspace = mp->colorspace;
	dev->tpg.xfer_func = mp->xfer_func;
	अगर (dev->fmt_cap->color_enc == TGP_COLOR_ENC_YCBCR)
		dev->tpg.ycbcr_enc = mp->ycbcr_enc;
	अन्यथा
		dev->tpg.hsv_enc = mp->hsv_enc;
	dev->tpg.quantization = mp->quantization;

	वापस 0;
पूर्ण

पूर्णांक vidioc_g_fmt_vid_cap_mplane(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!dev->multiplanar)
		वापस -ENOTTY;
	वापस vivid_g_fmt_vid_cap(file, priv, f);
पूर्ण

पूर्णांक vidioc_try_fmt_vid_cap_mplane(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!dev->multiplanar)
		वापस -ENOTTY;
	वापस vivid_try_fmt_vid_cap(file, priv, f);
पूर्ण

पूर्णांक vidioc_s_fmt_vid_cap_mplane(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!dev->multiplanar)
		वापस -ENOTTY;
	वापस vivid_s_fmt_vid_cap(file, priv, f);
पूर्ण

पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (dev->multiplanar)
		वापस -ENOTTY;
	वापस fmt_sp2mp_func(file, priv, f, vivid_g_fmt_vid_cap);
पूर्ण

पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (dev->multiplanar)
		वापस -ENOTTY;
	वापस fmt_sp2mp_func(file, priv, f, vivid_try_fmt_vid_cap);
पूर्ण

पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (dev->multiplanar)
		वापस -ENOTTY;
	वापस fmt_sp2mp_func(file, priv, f, vivid_s_fmt_vid_cap);
पूर्ण

पूर्णांक vivid_vid_cap_g_selection(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_selection *sel)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!dev->has_crop_cap && !dev->has_compose_cap)
		वापस -ENOTTY;
	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	अगर (vivid_is_webcam(dev))
		वापस -ENODATA;

	sel->r.left = sel->r.top = 0;
	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		अगर (!dev->has_crop_cap)
			वापस -EINVAL;
		sel->r = dev->crop_cap;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		अगर (!dev->has_crop_cap)
			वापस -EINVAL;
		sel->r = dev->src_rect;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		अगर (!dev->has_compose_cap)
			वापस -EINVAL;
		sel->r = vivid_max_rect;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		अगर (!dev->has_compose_cap)
			वापस -EINVAL;
		sel->r = dev->compose_cap;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
		अगर (!dev->has_compose_cap)
			वापस -EINVAL;
		sel->r = dev->fmt_cap_rect;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vivid_vid_cap_s_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *s)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_rect *crop = &dev->crop_cap;
	काष्ठा v4l2_rect *compose = &dev->compose_cap;
	अचिन्हित factor = V4L2_FIELD_HAS_T_OR_B(dev->field_cap) ? 2 : 1;
	पूर्णांक ret;

	अगर (!dev->has_crop_cap && !dev->has_compose_cap)
		वापस -ENOTTY;
	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	अगर (vivid_is_webcam(dev))
		वापस -ENODATA;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		अगर (!dev->has_crop_cap)
			वापस -EINVAL;
		ret = vivid_vid_adjust_sel(s->flags, &s->r);
		अगर (ret)
			वापस ret;
		v4l2_rect_set_min_size(&s->r, &vivid_min_rect);
		v4l2_rect_set_max_size(&s->r, &dev->src_rect);
		v4l2_rect_map_inside(&s->r, &dev->crop_bounds_cap);
		s->r.top /= factor;
		s->r.height /= factor;
		अगर (dev->has_scaler_cap) अणु
			काष्ठा v4l2_rect fmt = dev->fmt_cap_rect;
			काष्ठा v4l2_rect max_rect = अणु
				0, 0,
				s->r.width * MAX_ZOOM,
				s->r.height * MAX_ZOOM
			पूर्ण;
			काष्ठा v4l2_rect min_rect = अणु
				0, 0,
				s->r.width / MAX_ZOOM,
				s->r.height / MAX_ZOOM
			पूर्ण;

			v4l2_rect_set_min_size(&fmt, &min_rect);
			अगर (!dev->has_compose_cap)
				v4l2_rect_set_max_size(&fmt, &max_rect);
			अगर (!v4l2_rect_same_size(&dev->fmt_cap_rect, &fmt) &&
			    vb2_is_busy(&dev->vb_vid_cap_q))
				वापस -EBUSY;
			अगर (dev->has_compose_cap) अणु
				v4l2_rect_set_min_size(compose, &min_rect);
				v4l2_rect_set_max_size(compose, &max_rect);
			पूर्ण
			dev->fmt_cap_rect = fmt;
			tpg_s_buf_height(&dev->tpg, fmt.height);
		पूर्ण अन्यथा अगर (dev->has_compose_cap) अणु
			काष्ठा v4l2_rect fmt = dev->fmt_cap_rect;

			v4l2_rect_set_min_size(&fmt, &s->r);
			अगर (!v4l2_rect_same_size(&dev->fmt_cap_rect, &fmt) &&
			    vb2_is_busy(&dev->vb_vid_cap_q))
				वापस -EBUSY;
			dev->fmt_cap_rect = fmt;
			tpg_s_buf_height(&dev->tpg, fmt.height);
			v4l2_rect_set_माप_प्रकारo(compose, &s->r);
			v4l2_rect_map_inside(compose, &dev->fmt_cap_rect);
		पूर्ण अन्यथा अणु
			अगर (!v4l2_rect_same_size(&s->r, &dev->fmt_cap_rect) &&
			    vb2_is_busy(&dev->vb_vid_cap_q))
				वापस -EBUSY;
			v4l2_rect_set_माप_प्रकारo(&dev->fmt_cap_rect, &s->r);
			v4l2_rect_set_माप_प्रकारo(compose, &s->r);
			v4l2_rect_map_inside(compose, &dev->fmt_cap_rect);
			tpg_s_buf_height(&dev->tpg, dev->fmt_cap_rect.height);
		पूर्ण
		s->r.top *= factor;
		s->r.height *= factor;
		*crop = s->r;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		अगर (!dev->has_compose_cap)
			वापस -EINVAL;
		ret = vivid_vid_adjust_sel(s->flags, &s->r);
		अगर (ret)
			वापस ret;
		v4l2_rect_set_min_size(&s->r, &vivid_min_rect);
		v4l2_rect_set_max_size(&s->r, &dev->fmt_cap_rect);
		अगर (dev->has_scaler_cap) अणु
			काष्ठा v4l2_rect max_rect = अणु
				0, 0,
				dev->src_rect.width * MAX_ZOOM,
				(dev->src_rect.height / factor) * MAX_ZOOM
			पूर्ण;

			v4l2_rect_set_max_size(&s->r, &max_rect);
			अगर (dev->has_crop_cap) अणु
				काष्ठा v4l2_rect min_rect = अणु
					0, 0,
					s->r.width / MAX_ZOOM,
					(s->r.height * factor) / MAX_ZOOM
				पूर्ण;
				काष्ठा v4l2_rect max_rect = अणु
					0, 0,
					s->r.width * MAX_ZOOM,
					(s->r.height * factor) * MAX_ZOOM
				पूर्ण;

				v4l2_rect_set_min_size(crop, &min_rect);
				v4l2_rect_set_max_size(crop, &max_rect);
				v4l2_rect_map_inside(crop, &dev->crop_bounds_cap);
			पूर्ण
		पूर्ण अन्यथा अगर (dev->has_crop_cap) अणु
			s->r.top *= factor;
			s->r.height *= factor;
			v4l2_rect_set_max_size(&s->r, &dev->src_rect);
			v4l2_rect_set_माप_प्रकारo(crop, &s->r);
			v4l2_rect_map_inside(crop, &dev->crop_bounds_cap);
			s->r.top /= factor;
			s->r.height /= factor;
		पूर्ण अन्यथा अणु
			v4l2_rect_set_माप_प्रकारo(&s->r, &dev->src_rect);
			s->r.height /= factor;
		पूर्ण
		v4l2_rect_map_inside(&s->r, &dev->fmt_cap_rect);
		अगर (dev->biपंचांगap_cap && (compose->width != s->r.width ||
					compose->height != s->r.height)) अणु
			vमुक्त(dev->biपंचांगap_cap);
			dev->biपंचांगap_cap = शून्य;
		पूर्ण
		*compose = s->r;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	tpg_s_crop_compose(&dev->tpg, crop, compose);
	वापस 0;
पूर्ण

पूर्णांक vivid_vid_cap_g_pixelaspect(काष्ठा file *file, व्योम *priv,
				पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (vivid_get_pixel_aspect(dev)) अणु
	हाल TPG_PIXEL_ASPECT_NTSC:
		f->numerator = 11;
		f->denominator = 10;
		अवरोध;
	हाल TPG_PIXEL_ASPECT_PAL:
		f->numerator = 54;
		f->denominator = 59;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vidioc_क्रमागत_fmt_vid_overlay(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	स्थिर काष्ठा vivid_fmt *fmt;

	अगर (dev->multiplanar)
		वापस -ENOTTY;

	अगर (f->index >= ARRAY_SIZE(क्रमmats_ovl))
		वापस -EINVAL;

	fmt = &क्रमmats_ovl[f->index];

	f->pixelक्रमmat = fmt->fourcc;
	वापस 0;
पूर्ण

पूर्णांक vidioc_g_fmt_vid_overlay(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	स्थिर काष्ठा v4l2_rect *compose = &dev->compose_cap;
	काष्ठा v4l2_winकरोw *win = &f->fmt.win;
	अचिन्हित clipcount = win->clipcount;

	अगर (dev->multiplanar)
		वापस -ENOTTY;

	win->w.top = dev->overlay_cap_top;
	win->w.left = dev->overlay_cap_left;
	win->w.width = compose->width;
	win->w.height = compose->height;
	win->field = dev->overlay_cap_field;
	win->clipcount = dev->clipcount_cap;
	अगर (clipcount > dev->clipcount_cap)
		clipcount = dev->clipcount_cap;
	अगर (dev->biपंचांगap_cap == शून्य)
		win->biपंचांगap = शून्य;
	अन्यथा अगर (win->biपंचांगap) अणु
		अगर (copy_to_user(win->biपंचांगap, dev->biपंचांगap_cap,
		    ((compose->width + 7) / 8) * compose->height))
			वापस -EFAULT;
	पूर्ण
	अगर (clipcount && win->clips)
		स_नकल(win->clips, dev->clips_cap,
		       clipcount * माप(dev->clips_cap[0]));
	वापस 0;
पूर्ण

पूर्णांक vidioc_try_fmt_vid_overlay(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	स्थिर काष्ठा v4l2_rect *compose = &dev->compose_cap;
	काष्ठा v4l2_winकरोw *win = &f->fmt.win;
	पूर्णांक i, j;

	अगर (dev->multiplanar)
		वापस -ENOTTY;

	win->w.left = clamp_t(पूर्णांक, win->w.left,
			      -dev->fb_cap.fmt.width, dev->fb_cap.fmt.width);
	win->w.top = clamp_t(पूर्णांक, win->w.top,
			     -dev->fb_cap.fmt.height, dev->fb_cap.fmt.height);
	win->w.width = compose->width;
	win->w.height = compose->height;
	अगर (win->field != V4L2_FIELD_BOTTOM && win->field != V4L2_FIELD_TOP)
		win->field = V4L2_FIELD_ANY;
	win->chromakey = 0;
	win->global_alpha = 0;
	अगर (win->clipcount && !win->clips)
		win->clipcount = 0;
	अगर (win->clipcount > MAX_CLIPS)
		win->clipcount = MAX_CLIPS;
	अगर (win->clipcount) अणु
		स_नकल(dev->try_clips_cap, win->clips,
		       win->clipcount * माप(dev->clips_cap[0]));
		क्रम (i = 0; i < win->clipcount; i++) अणु
			काष्ठा v4l2_rect *r = &dev->try_clips_cap[i].c;

			r->top = clamp_t(s32, r->top, 0, dev->fb_cap.fmt.height - 1);
			r->height = clamp_t(s32, r->height, 1, dev->fb_cap.fmt.height - r->top);
			r->left = clamp_t(u32, r->left, 0, dev->fb_cap.fmt.width - 1);
			r->width = clamp_t(u32, r->width, 1, dev->fb_cap.fmt.width - r->left);
		पूर्ण
		/*
		 * Yeah, so sue me, it's an O(n^2) algorithm. But n is a small
		 * number and it's typically a one-समय deal.
		 */
		क्रम (i = 0; i < win->clipcount - 1; i++) अणु
			काष्ठा v4l2_rect *r1 = &dev->try_clips_cap[i].c;

			क्रम (j = i + 1; j < win->clipcount; j++) अणु
				काष्ठा v4l2_rect *r2 = &dev->try_clips_cap[j].c;

				अगर (v4l2_rect_overlap(r1, r2))
					वापस -EINVAL;
			पूर्ण
		पूर्ण
		स_नकल(win->clips, dev->try_clips_cap,
		       win->clipcount * माप(dev->clips_cap[0]));
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vidioc_s_fmt_vid_overlay(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	स्थिर काष्ठा v4l2_rect *compose = &dev->compose_cap;
	काष्ठा v4l2_winकरोw *win = &f->fmt.win;
	पूर्णांक ret = vidioc_try_fmt_vid_overlay(file, priv, f);
	अचिन्हित biपंचांगap_size = ((compose->width + 7) / 8) * compose->height;
	अचिन्हित clips_size = win->clipcount * माप(dev->clips_cap[0]);
	व्योम *new_biपंचांगap = शून्य;

	अगर (ret)
		वापस ret;

	अगर (win->biपंचांगap) अणु
		new_biपंचांगap = vzalloc(biपंचांगap_size);

		अगर (new_biपंचांगap == शून्य)
			वापस -ENOMEM;
		अगर (copy_from_user(new_biपंचांगap, win->biपंचांगap, biपंचांगap_size)) अणु
			vमुक्त(new_biपंचांगap);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	dev->overlay_cap_top = win->w.top;
	dev->overlay_cap_left = win->w.left;
	dev->overlay_cap_field = win->field;
	vमुक्त(dev->biपंचांगap_cap);
	dev->biपंचांगap_cap = new_biपंचांगap;
	dev->clipcount_cap = win->clipcount;
	अगर (dev->clipcount_cap)
		स_नकल(dev->clips_cap, dev->try_clips_cap, clips_size);
	वापस 0;
पूर्ण

पूर्णांक vivid_vid_cap_overlay(काष्ठा file *file, व्योम *fh, अचिन्हित i)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (dev->multiplanar)
		वापस -ENOTTY;

	अगर (i && dev->fb_vbase_cap == शून्य)
		वापस -EINVAL;

	अगर (i && dev->fb_cap.fmt.pixelक्रमmat != dev->fmt_cap->fourcc) अणु
		dprपूर्णांकk(dev, 1, "mismatch between overlay and video capture pixelformats\n");
		वापस -EINVAL;
	पूर्ण

	अगर (dev->overlay_cap_owner && dev->overlay_cap_owner != fh)
		वापस -EBUSY;
	dev->overlay_cap_owner = i ? fh : शून्य;
	वापस 0;
पूर्ण

पूर्णांक vivid_vid_cap_g_fbuf(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_framebuffer *a)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (dev->multiplanar)
		वापस -ENOTTY;

	*a = dev->fb_cap;
	a->capability = V4L2_FBUF_CAP_BITMAP_CLIPPING |
			V4L2_FBUF_CAP_LIST_CLIPPING;
	a->flags = V4L2_FBUF_FLAG_PRIMARY;
	a->fmt.field = V4L2_FIELD_NONE;
	a->fmt.colorspace = V4L2_COLORSPACE_SRGB;
	a->fmt.priv = 0;
	वापस 0;
पूर्ण

पूर्णांक vivid_vid_cap_s_fbuf(काष्ठा file *file, व्योम *fh,
				स्थिर काष्ठा v4l2_framebuffer *a)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	स्थिर काष्ठा vivid_fmt *fmt;

	अगर (dev->multiplanar)
		वापस -ENOTTY;

	अगर (!capable(CAP_SYS_ADMIN) && !capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	अगर (dev->overlay_cap_owner)
		वापस -EBUSY;

	अगर (a->base == शून्य) अणु
		dev->fb_cap.base = शून्य;
		dev->fb_vbase_cap = शून्य;
		वापस 0;
	पूर्ण

	अगर (a->fmt.width < 48 || a->fmt.height < 32)
		वापस -EINVAL;
	fmt = vivid_get_क्रमmat(dev, a->fmt.pixelक्रमmat);
	अगर (!fmt || !fmt->can_करो_overlay)
		वापस -EINVAL;
	अगर (a->fmt.bytesperline < (a->fmt.width * fmt->bit_depth[0]) / 8)
		वापस -EINVAL;
	अगर (a->fmt.height * a->fmt.bytesperline < a->fmt.sizeimage)
		वापस -EINVAL;

	dev->fb_vbase_cap = phys_to_virt((अचिन्हित दीर्घ)a->base);
	dev->fb_cap = *a;
	dev->overlay_cap_left = clamp_t(पूर्णांक, dev->overlay_cap_left,
				    -dev->fb_cap.fmt.width, dev->fb_cap.fmt.width);
	dev->overlay_cap_top = clamp_t(पूर्णांक, dev->overlay_cap_top,
				   -dev->fb_cap.fmt.height, dev->fb_cap.fmt.height);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_audio vivid_audio_inमाला_दो[] = अणु
	अणु 0, "TV", V4L2_AUDCAP_STEREO पूर्ण,
	अणु 1, "Line-In", V4L2_AUDCAP_STEREO पूर्ण,
पूर्ण;

पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_input *inp)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (inp->index >= dev->num_inमाला_दो)
		वापस -EINVAL;

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	चयन (dev->input_type[inp->index]) अणु
	हाल WEBCAM:
		snम_लिखो(inp->name, माप(inp->name), "Webcam %u",
				dev->input_name_counter[inp->index]);
		inp->capabilities = 0;
		अवरोध;
	हाल TV:
		snम_लिखो(inp->name, माप(inp->name), "TV %u",
				dev->input_name_counter[inp->index]);
		inp->type = V4L2_INPUT_TYPE_TUNER;
		inp->std = V4L2_STD_ALL;
		अगर (dev->has_audio_inमाला_दो)
			inp->audioset = (1 << ARRAY_SIZE(vivid_audio_inमाला_दो)) - 1;
		inp->capabilities = V4L2_IN_CAP_STD;
		अवरोध;
	हाल SVID:
		snम_लिखो(inp->name, माप(inp->name), "S-Video %u",
				dev->input_name_counter[inp->index]);
		inp->std = V4L2_STD_ALL;
		अगर (dev->has_audio_inमाला_दो)
			inp->audioset = (1 << ARRAY_SIZE(vivid_audio_inमाला_दो)) - 1;
		inp->capabilities = V4L2_IN_CAP_STD;
		अवरोध;
	हाल HDMI:
		snम_लिखो(inp->name, माप(inp->name), "HDMI %u",
				dev->input_name_counter[inp->index]);
		inp->capabilities = V4L2_IN_CAP_DV_TIMINGS;
		अगर (dev->edid_blocks == 0 ||
		    dev->dv_timings_संकेत_mode[dev->input] == NO_SIGNAL)
			inp->status |= V4L2_IN_ST_NO_SIGNAL;
		अन्यथा अगर (dev->dv_timings_संकेत_mode[dev->input] == NO_LOCK ||
			 dev->dv_timings_संकेत_mode[dev->input] == OUT_OF_RANGE)
			inp->status |= V4L2_IN_ST_NO_H_LOCK;
		अवरोध;
	पूर्ण
	अगर (dev->sensor_hflip)
		inp->status |= V4L2_IN_ST_HFLIP;
	अगर (dev->sensor_vflip)
		inp->status |= V4L2_IN_ST_VFLIP;
	अगर (dev->input == inp->index && vivid_is_sdtv_cap(dev)) अणु
		अगर (dev->std_संकेत_mode[dev->input] == NO_SIGNAL) अणु
			inp->status |= V4L2_IN_ST_NO_SIGNAL;
		पूर्ण अन्यथा अगर (dev->std_संकेत_mode[dev->input] == NO_LOCK) अणु
			inp->status |= V4L2_IN_ST_NO_H_LOCK;
		पूर्ण अन्यथा अगर (vivid_is_tv_cap(dev)) अणु
			चयन (tpg_g_quality(&dev->tpg)) अणु
			हाल TPG_QUAL_GRAY:
				inp->status |= V4L2_IN_ST_COLOR_KILL;
				अवरोध;
			हाल TPG_QUAL_NOISE:
				inp->status |= V4L2_IN_ST_NO_H_LOCK;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित *i)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	*i = dev->input;
	वापस 0;
पूर्ण

पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित i)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_bt_timings *bt = &dev->dv_timings_cap[dev->input].bt;
	अचिन्हित brightness;

	अगर (i >= dev->num_inमाला_दो)
		वापस -EINVAL;

	अगर (i == dev->input)
		वापस 0;

	अगर (vb2_is_busy(&dev->vb_vid_cap_q) ||
	    vb2_is_busy(&dev->vb_vbi_cap_q) ||
	    vb2_is_busy(&dev->vb_meta_cap_q))
		वापस -EBUSY;

	dev->input = i;
	dev->vid_cap_dev.tvnorms = 0;
	अगर (dev->input_type[i] == TV || dev->input_type[i] == SVID) अणु
		dev->tv_audio_input = (dev->input_type[i] == TV) ? 0 : 1;
		dev->vid_cap_dev.tvnorms = V4L2_STD_ALL;
	पूर्ण
	dev->vbi_cap_dev.tvnorms = dev->vid_cap_dev.tvnorms;
	dev->meta_cap_dev.tvnorms = dev->vid_cap_dev.tvnorms;
	vivid_update_क्रमmat_cap(dev, false);

	अगर (dev->colorspace) अणु
		चयन (dev->input_type[i]) अणु
		हाल WEBCAM:
			v4l2_ctrl_s_ctrl(dev->colorspace, VIVID_CS_SRGB);
			अवरोध;
		हाल TV:
		हाल SVID:
			v4l2_ctrl_s_ctrl(dev->colorspace, VIVID_CS_170M);
			अवरोध;
		हाल HDMI:
			अगर (bt->flags & V4L2_DV_FL_IS_CE_VIDEO) अणु
				अगर (dev->src_rect.width == 720 && dev->src_rect.height <= 576)
					v4l2_ctrl_s_ctrl(dev->colorspace, VIVID_CS_170M);
				अन्यथा
					v4l2_ctrl_s_ctrl(dev->colorspace, VIVID_CS_709);
			पूर्ण अन्यथा अणु
				v4l2_ctrl_s_ctrl(dev->colorspace, VIVID_CS_SRGB);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Modअगरy the brightness range depending on the input.
	 * This makes it easy to use vivid to test अगर applications can
	 * handle control range modअगरications and is also how this is
	 * typically used in practice as dअगरferent inमाला_दो may be hooked
	 * up to dअगरferent receivers with dअगरferent control ranges.
	 */
	brightness = 128 * i + dev->input_brightness[i];
	v4l2_ctrl_modअगरy_range(dev->brightness,
			128 * i, 255 + 128 * i, 1, 128 + 128 * i);
	v4l2_ctrl_s_ctrl(dev->brightness, brightness);

	/* Restore per-input states. */
	v4l2_ctrl_activate(dev->ctrl_dv_timings_संकेत_mode,
			   vivid_is_hdmi_cap(dev));
	v4l2_ctrl_activate(dev->ctrl_dv_timings, vivid_is_hdmi_cap(dev) &&
			   dev->dv_timings_संकेत_mode[dev->input] ==
			   SELECTED_DV_TIMINGS);
	v4l2_ctrl_activate(dev->ctrl_std_संकेत_mode, vivid_is_sdtv_cap(dev));
	v4l2_ctrl_activate(dev->ctrl_standard, vivid_is_sdtv_cap(dev) &&
			   dev->std_संकेत_mode[dev->input]);

	अगर (vivid_is_hdmi_cap(dev)) अणु
		v4l2_ctrl_s_ctrl(dev->ctrl_dv_timings_संकेत_mode,
				 dev->dv_timings_संकेत_mode[dev->input]);
		v4l2_ctrl_s_ctrl(dev->ctrl_dv_timings,
				 dev->query_dv_timings[dev->input]);
	पूर्ण अन्यथा अगर (vivid_is_sdtv_cap(dev)) अणु
		v4l2_ctrl_s_ctrl(dev->ctrl_std_संकेत_mode,
				 dev->std_संकेत_mode[dev->input]);
		v4l2_ctrl_s_ctrl(dev->ctrl_standard,
				 dev->std_संकेत_mode[dev->input]);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vidioc_क्रमागतaudio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *vin)
अणु
	अगर (vin->index >= ARRAY_SIZE(vivid_audio_inमाला_दो))
		वापस -EINVAL;
	*vin = vivid_audio_inमाला_दो[vin->index];
	वापस 0;
पूर्ण

पूर्णांक vidioc_g_audio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *vin)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!vivid_is_sdtv_cap(dev))
		वापस -EINVAL;
	*vin = vivid_audio_inमाला_दो[dev->tv_audio_input];
	वापस 0;
पूर्ण

पूर्णांक vidioc_s_audio(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_audio *vin)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!vivid_is_sdtv_cap(dev))
		वापस -EINVAL;
	अगर (vin->index >= ARRAY_SIZE(vivid_audio_inमाला_दो))
		वापस -EINVAL;
	dev->tv_audio_input = vin->index;
	वापस 0;
पूर्ण

पूर्णांक vivid_video_g_frequency(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (vf->tuner != 0)
		वापस -EINVAL;
	vf->frequency = dev->tv_freq;
	वापस 0;
पूर्ण

पूर्णांक vivid_video_s_frequency(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (vf->tuner != 0)
		वापस -EINVAL;
	dev->tv_freq = clamp_t(अचिन्हित, vf->frequency, MIN_TV_FREQ, MAX_TV_FREQ);
	अगर (vivid_is_tv_cap(dev))
		vivid_update_quality(dev);
	वापस 0;
पूर्ण

पूर्णांक vivid_video_s_tuner(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (vt->index != 0)
		वापस -EINVAL;
	अगर (vt->audmode > V4L2_TUNER_MODE_LANG1_LANG2)
		वापस -EINVAL;
	dev->tv_audmode = vt->audmode;
	वापस 0;
पूर्ण

पूर्णांक vivid_video_g_tuner(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	क्रमागत tpg_quality qual;

	अगर (vt->index != 0)
		वापस -EINVAL;

	vt->capability = V4L2_TUNER_CAP_NORM | V4L2_TUNER_CAP_STEREO |
			 V4L2_TUNER_CAP_LANG1 | V4L2_TUNER_CAP_LANG2;
	vt->audmode = dev->tv_audmode;
	vt->rangelow = MIN_TV_FREQ;
	vt->rangehigh = MAX_TV_FREQ;
	qual = vivid_get_quality(dev, &vt->afc);
	अगर (qual == TPG_QUAL_COLOR)
		vt->संकेत = 0xffff;
	अन्यथा अगर (qual == TPG_QUAL_GRAY)
		vt->संकेत = 0x8000;
	अन्यथा
		vt->संकेत = 0;
	अगर (qual == TPG_QUAL_NOISE) अणु
		vt->rxsubchans = 0;
	पूर्ण अन्यथा अगर (qual == TPG_QUAL_GRAY) अणु
		vt->rxsubchans = V4L2_TUNER_SUB_MONO;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक channel_nr = dev->tv_freq / (6 * 16);
		अचिन्हित पूर्णांक options =
			(dev->std_cap[dev->input] & V4L2_STD_NTSC_M) ? 4 : 3;

		चयन (channel_nr % options) अणु
		हाल 0:
			vt->rxsubchans = V4L2_TUNER_SUB_MONO;
			अवरोध;
		हाल 1:
			vt->rxsubchans = V4L2_TUNER_SUB_STEREO;
			अवरोध;
		हाल 2:
			अगर (dev->std_cap[dev->input] & V4L2_STD_NTSC_M)
				vt->rxsubchans = V4L2_TUNER_SUB_MONO | V4L2_TUNER_SUB_SAP;
			अन्यथा
				vt->rxsubchans = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
			अवरोध;
		हाल 3:
			vt->rxsubchans = V4L2_TUNER_SUB_STEREO | V4L2_TUNER_SUB_SAP;
			अवरोध;
		पूर्ण
	पूर्ण
	strscpy(vt->name, "TV Tuner", माप(vt->name));
	वापस 0;
पूर्ण

/* Must reमुख्य in sync with the vivid_ctrl_standard_strings array */
स्थिर v4l2_std_id vivid_standard[] = अणु
	V4L2_STD_NTSC_M,
	V4L2_STD_NTSC_M_JP,
	V4L2_STD_NTSC_M_KR,
	V4L2_STD_NTSC_443,
	V4L2_STD_PAL_BG | V4L2_STD_PAL_H,
	V4L2_STD_PAL_I,
	V4L2_STD_PAL_DK,
	V4L2_STD_PAL_M,
	V4L2_STD_PAL_N,
	V4L2_STD_PAL_Nc,
	V4L2_STD_PAL_60,
	V4L2_STD_SECAM_B | V4L2_STD_SECAM_G | V4L2_STD_SECAM_H,
	V4L2_STD_SECAM_DK,
	V4L2_STD_SECAM_L,
	V4L2_STD_SECAM_LC,
	V4L2_STD_UNKNOWN
पूर्ण;

/* Must reमुख्य in sync with the vivid_standard array */
स्थिर अक्षर * स्थिर vivid_ctrl_standard_strings[] = अणु
	"NTSC-M",
	"NTSC-M-JP",
	"NTSC-M-KR",
	"NTSC-443",
	"PAL-BGH",
	"PAL-I",
	"PAL-DK",
	"PAL-M",
	"PAL-N",
	"PAL-Nc",
	"PAL-60",
	"SECAM-BGH",
	"SECAM-DK",
	"SECAM-L",
	"SECAM-Lc",
	शून्य,
पूर्ण;

पूर्णांक vidioc_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *id)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	अचिन्हित पूर्णांक last = dev->query_std_last[dev->input];

	अगर (!vivid_is_sdtv_cap(dev))
		वापस -ENODATA;
	अगर (dev->std_संकेत_mode[dev->input] == NO_SIGNAL ||
	    dev->std_संकेत_mode[dev->input] == NO_LOCK) अणु
		*id = V4L2_STD_UNKNOWN;
		वापस 0;
	पूर्ण
	अगर (vivid_is_tv_cap(dev) && tpg_g_quality(&dev->tpg) == TPG_QUAL_NOISE) अणु
		*id = V4L2_STD_UNKNOWN;
	पूर्ण अन्यथा अगर (dev->std_संकेत_mode[dev->input] == CURRENT_STD) अणु
		*id = dev->std_cap[dev->input];
	पूर्ण अन्यथा अगर (dev->std_संकेत_mode[dev->input] == SELECTED_STD) अणु
		*id = dev->query_std[dev->input];
	पूर्ण अन्यथा अणु
		*id = vivid_standard[last];
		dev->query_std_last[dev->input] =
			(last + 1) % ARRAY_SIZE(vivid_standard);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vivid_vid_cap_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!vivid_is_sdtv_cap(dev))
		वापस -ENODATA;
	अगर (dev->std_cap[dev->input] == id)
		वापस 0;
	अगर (vb2_is_busy(&dev->vb_vid_cap_q) || vb2_is_busy(&dev->vb_vbi_cap_q))
		वापस -EBUSY;
	dev->std_cap[dev->input] = id;
	vivid_update_क्रमmat_cap(dev, false);
	वापस 0;
पूर्ण

अटल व्योम find_aspect_ratio(u32 width, u32 height,
			       u32 *num, u32 *denom)
अणु
	अगर (!(height % 3) && ((height * 4 / 3) == width)) अणु
		*num = 4;
		*denom = 3;
	पूर्ण अन्यथा अगर (!(height % 9) && ((height * 16 / 9) == width)) अणु
		*num = 16;
		*denom = 9;
	पूर्ण अन्यथा अगर (!(height % 10) && ((height * 16 / 10) == width)) अणु
		*num = 16;
		*denom = 10;
	पूर्ण अन्यथा अगर (!(height % 4) && ((height * 5 / 4) == width)) अणु
		*num = 5;
		*denom = 4;
	पूर्ण अन्यथा अगर (!(height % 9) && ((height * 15 / 9) == width)) अणु
		*num = 15;
		*denom = 9;
	पूर्ण अन्यथा अणु /* शेष to 16:9 */
		*num = 16;
		*denom = 9;
	पूर्ण
पूर्ण

अटल bool valid_cvt_gtf_timings(काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा v4l2_bt_timings *bt = &timings->bt;
	u32 total_h_pixel;
	u32 total_v_lines;
	u32 h_freq;

	अगर (!v4l2_valid_dv_timings(timings, &vivid_dv_timings_cap,
				शून्य, शून्य))
		वापस false;

	total_h_pixel = V4L2_DV_BT_FRAME_WIDTH(bt);
	total_v_lines = V4L2_DV_BT_FRAME_HEIGHT(bt);

	h_freq = (u32)bt->pixelघड़ी / total_h_pixel;

	अगर (bt->standards == 0 || (bt->standards & V4L2_DV_BT_STD_CVT)) अणु
		अगर (v4l2_detect_cvt(total_v_lines, h_freq, bt->vsync, bt->width,
				    bt->polarities, bt->पूर्णांकerlaced, timings))
			वापस true;
	पूर्ण

	अगर (bt->standards == 0 || (bt->standards & V4L2_DV_BT_STD_GTF)) अणु
		काष्ठा v4l2_fract aspect_ratio;

		find_aspect_ratio(bt->width, bt->height,
				  &aspect_ratio.numerator,
				  &aspect_ratio.denominator);
		अगर (v4l2_detect_gtf(total_v_lines, h_freq, bt->vsync,
				    bt->polarities, bt->पूर्णांकerlaced,
				    aspect_ratio, timings))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक vivid_vid_cap_s_dv_timings(काष्ठा file *file, व्योम *_fh,
				    काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!vivid_is_hdmi_cap(dev))
		वापस -ENODATA;
	अगर (!v4l2_find_dv_timings_cap(timings, &vivid_dv_timings_cap,
				      0, शून्य, शून्य) &&
	    !valid_cvt_gtf_timings(timings))
		वापस -EINVAL;

	अगर (v4l2_match_dv_timings(timings, &dev->dv_timings_cap[dev->input],
				  0, false))
		वापस 0;
	अगर (vb2_is_busy(&dev->vb_vid_cap_q))
		वापस -EBUSY;

	dev->dv_timings_cap[dev->input] = *timings;
	vivid_update_क्रमmat_cap(dev, false);
	वापस 0;
पूर्ण

पूर्णांक vidioc_query_dv_timings(काष्ठा file *file, व्योम *_fh,
				    काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	अचिन्हित पूर्णांक input = dev->input;
	अचिन्हित पूर्णांक last = dev->query_dv_timings_last[input];

	अगर (!vivid_is_hdmi_cap(dev))
		वापस -ENODATA;
	अगर (dev->dv_timings_संकेत_mode[input] == NO_SIGNAL ||
	    dev->edid_blocks == 0)
		वापस -ENOLINK;
	अगर (dev->dv_timings_संकेत_mode[input] == NO_LOCK)
		वापस -ENOLCK;
	अगर (dev->dv_timings_संकेत_mode[input] == OUT_OF_RANGE) अणु
		timings->bt.pixelघड़ी = vivid_dv_timings_cap.bt.max_pixelघड़ी * 2;
		वापस -दुस्फल;
	पूर्ण
	अगर (dev->dv_timings_संकेत_mode[input] == CURRENT_DV_TIMINGS) अणु
		*timings = dev->dv_timings_cap[input];
	पूर्ण अन्यथा अगर (dev->dv_timings_संकेत_mode[input] ==
		   SELECTED_DV_TIMINGS) अणु
		*timings =
			v4l2_dv_timings_presets[dev->query_dv_timings[input]];
	पूर्ण अन्यथा अणु
		*timings =
			v4l2_dv_timings_presets[last];
		dev->query_dv_timings_last[input] =
			(last + 1) % dev->query_dv_timings_size;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vidioc_s_edid(काष्ठा file *file, व्योम *_fh,
			 काष्ठा v4l2_edid *edid)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	u16 phys_addr;
	u32 display_present = 0;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret;

	स_रखो(edid->reserved, 0, माप(edid->reserved));
	अगर (edid->pad >= dev->num_inमाला_दो)
		वापस -EINVAL;
	अगर (dev->input_type[edid->pad] != HDMI || edid->start_block)
		वापस -EINVAL;
	अगर (edid->blocks == 0) अणु
		dev->edid_blocks = 0;
		v4l2_ctrl_s_ctrl(dev->ctrl_tx_edid_present, 0);
		v4l2_ctrl_s_ctrl(dev->ctrl_tx_hotplug, 0);
		phys_addr = CEC_PHYS_ADDR_INVALID;
		जाओ set_phys_addr;
	पूर्ण
	अगर (edid->blocks > dev->edid_max_blocks) अणु
		edid->blocks = dev->edid_max_blocks;
		वापस -E2BIG;
	पूर्ण
	phys_addr = cec_get_edid_phys_addr(edid->edid, edid->blocks * 128, शून्य);
	ret = v4l2_phys_addr_validate(phys_addr, &phys_addr, शून्य);
	अगर (ret)
		वापस ret;

	अगर (vb2_is_busy(&dev->vb_vid_cap_q))
		वापस -EBUSY;

	dev->edid_blocks = edid->blocks;
	स_नकल(dev->edid, edid->edid, edid->blocks * 128);

	क्रम (i = 0, j = 0; i < dev->num_outमाला_दो; i++)
		अगर (dev->output_type[i] == HDMI)
			display_present |=
				dev->display_present[i] << j++;

	v4l2_ctrl_s_ctrl(dev->ctrl_tx_edid_present, display_present);
	v4l2_ctrl_s_ctrl(dev->ctrl_tx_hotplug, display_present);

set_phys_addr:
	/* TODO: a proper hotplug detect cycle should be emulated here */
	cec_s_phys_addr(dev->cec_rx_adap, phys_addr, false);

	क्रम (i = 0; i < MAX_OUTPUTS && dev->cec_tx_adap[i]; i++)
		cec_s_phys_addr(dev->cec_tx_adap[i],
				dev->display_present[i] ?
				v4l2_phys_addr_क्रम_input(phys_addr, i + 1) :
				CEC_PHYS_ADDR_INVALID,
				false);
	वापस 0;
पूर्ण

पूर्णांक vidioc_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
					 काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!vivid_is_webcam(dev) && !dev->has_scaler_cap)
		वापस -EINVAL;
	अगर (vivid_get_क्रमmat(dev, fsize->pixel_क्रमmat) == शून्य)
		वापस -EINVAL;
	अगर (vivid_is_webcam(dev)) अणु
		अगर (fsize->index >= ARRAY_SIZE(webcam_sizes))
			वापस -EINVAL;
		fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
		fsize->discrete = webcam_sizes[fsize->index];
		वापस 0;
	पूर्ण
	अगर (fsize->index)
		वापस -EINVAL;
	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	fsize->stepwise.min_width = MIN_WIDTH;
	fsize->stepwise.max_width = MAX_WIDTH * MAX_ZOOM;
	fsize->stepwise.step_width = 2;
	fsize->stepwise.min_height = MIN_HEIGHT;
	fsize->stepwise.max_height = MAX_HEIGHT * MAX_ZOOM;
	fsize->stepwise.step_height = 2;
	वापस 0;
पूर्ण

/* समयperframe is arbitrary and continuous */
पूर्णांक vidioc_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *priv,
					     काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	स्थिर काष्ठा vivid_fmt *fmt;
	पूर्णांक i;

	fmt = vivid_get_क्रमmat(dev, fival->pixel_क्रमmat);
	अगर (!fmt)
		वापस -EINVAL;

	अगर (!vivid_is_webcam(dev)) अणु
		अगर (fival->index)
			वापस -EINVAL;
		अगर (fival->width < MIN_WIDTH || fival->width > MAX_WIDTH * MAX_ZOOM)
			वापस -EINVAL;
		अगर (fival->height < MIN_HEIGHT || fival->height > MAX_HEIGHT * MAX_ZOOM)
			वापस -EINVAL;
		fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
		fival->discrete = dev->समयperframe_vid_cap;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(webcam_sizes); i++)
		अगर (fival->width == webcam_sizes[i].width &&
		    fival->height == webcam_sizes[i].height)
			अवरोध;
	अगर (i == ARRAY_SIZE(webcam_sizes))
		वापस -EINVAL;
	अगर (fival->index >= 2 * (VIVID_WEBCAM_SIZES - i))
		वापस -EINVAL;
	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = webcam_पूर्णांकervals[fival->index];
	वापस 0;
पूर्ण

पूर्णांक vivid_vid_cap_g_parm(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (parm->type != (dev->multiplanar ?
			   V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE :
			   V4L2_BUF_TYPE_VIDEO_CAPTURE))
		वापस -EINVAL;

	parm->parm.capture.capability   = V4L2_CAP_TIMEPERFRAME;
	parm->parm.capture.समयperframe = dev->समयperframe_vid_cap;
	parm->parm.capture.पढ़ोbuffers  = 1;
	वापस 0;
पूर्ण

पूर्णांक vivid_vid_cap_s_parm(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	अचिन्हित ival_sz = 2 * (VIVID_WEBCAM_SIZES - dev->webcam_size_idx);
	काष्ठा v4l2_fract tpf;
	अचिन्हित i;

	अगर (parm->type != (dev->multiplanar ?
			   V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE :
			   V4L2_BUF_TYPE_VIDEO_CAPTURE))
		वापस -EINVAL;
	अगर (!vivid_is_webcam(dev))
		वापस vivid_vid_cap_g_parm(file, priv, parm);

	tpf = parm->parm.capture.समयperframe;

	अगर (tpf.denominator == 0)
		tpf = webcam_पूर्णांकervals[ival_sz - 1];
	क्रम (i = 0; i < ival_sz; i++)
		अगर (V4L2_FRACT_COMPARE(tpf, >=, webcam_पूर्णांकervals[i]))
			अवरोध;
	अगर (i == ival_sz)
		i = ival_sz - 1;
	dev->webcam_ival_idx = i;
	tpf = webcam_पूर्णांकervals[dev->webcam_ival_idx];

	/* resync the thपढ़ो's timings */
	dev->cap_seq_resync = true;
	dev->समयperframe_vid_cap = tpf;
	parm->parm.capture.capability   = V4L2_CAP_TIMEPERFRAME;
	parm->parm.capture.समयperframe = tpf;
	parm->parm.capture.पढ़ोbuffers  = 1;
	वापस 0;
पूर्ण
