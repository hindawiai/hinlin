<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-vid-out.c - video output support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-rect.h>

#समावेश "vivid-core.h"
#समावेश "vivid-vid-common.h"
#समावेश "vivid-kthread-out.h"
#समावेश "vivid-vid-out.h"

अटल पूर्णांक vid_out_queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित *nbuffers, अचिन्हित *nplanes,
		       अचिन्हित sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);
	स्थिर काष्ठा vivid_fmt *vfmt = dev->fmt_out;
	अचिन्हित planes = vfmt->buffers;
	अचिन्हित h = dev->fmt_out_rect.height;
	अचिन्हित पूर्णांक size = dev->bytesperline_out[0] * h + vfmt->data_offset[0];
	अचिन्हित p;

	क्रम (p = vfmt->buffers; p < vfmt->planes; p++)
		size += dev->bytesperline_out[p] * h / vfmt->vकरोwnsampling[p] +
			vfmt->data_offset[p];

	अगर (dev->field_out == V4L2_FIELD_ALTERNATE) अणु
		/*
		 * You cannot use ग_लिखो() with FIELD_ALTERNATE since the field
		 * inक्रमmation (TOP/BOTTOM) cannot be passed to the kernel.
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
		 * the number of planes in the current क्रमmat. You can't mix that.
		 */
		अगर (*nplanes != planes)
			वापस -EINVAL;
		अगर (sizes[0] < size)
			वापस -EINVAL;
		क्रम (p = 1; p < planes; p++) अणु
			अगर (sizes[p] < dev->bytesperline_out[p] * h +
				       vfmt->data_offset[p])
				वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (p = 0; p < planes; p++)
			sizes[p] = p ? dev->bytesperline_out[p] * h +
				       vfmt->data_offset[p] : size;
	पूर्ण

	अगर (vq->num_buffers + *nbuffers < 2)
		*nbuffers = 2 - vq->num_buffers;

	*nplanes = planes;

	dprपूर्णांकk(dev, 1, "%s: count=%d\n", __func__, *nbuffers);
	क्रम (p = 0; p < planes; p++)
		dprपूर्णांकk(dev, 1, "%s: size[%u]=%u\n", __func__, p, sizes[p]);
	वापस 0;
पूर्ण

अटल पूर्णांक vid_out_buf_out_validate(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);

	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	अगर (dev->field_out != V4L2_FIELD_ALTERNATE)
		vbuf->field = dev->field_out;
	अन्यथा अगर (vbuf->field != V4L2_FIELD_TOP &&
		 vbuf->field != V4L2_FIELD_BOTTOM)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक vid_out_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	स्थिर काष्ठा vivid_fmt *vfmt = dev->fmt_out;
	अचिन्हित पूर्णांक planes = vfmt->buffers;
	अचिन्हित पूर्णांक h = dev->fmt_out_rect.height;
	अचिन्हित पूर्णांक size = dev->bytesperline_out[0] * h;
	अचिन्हित p;

	क्रम (p = vfmt->buffers; p < vfmt->planes; p++)
		size += dev->bytesperline_out[p] * h / vfmt->vकरोwnsampling[p];

	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	अगर (WARN_ON(शून्य == dev->fmt_out))
		वापस -EINVAL;

	अगर (dev->buf_prepare_error) अणु
		/*
		 * Error injection: test what happens अगर buf_prepare() वापसs
		 * an error.
		 */
		dev->buf_prepare_error = false;
		वापस -EINVAL;
	पूर्ण

	क्रम (p = 0; p < planes; p++) अणु
		अगर (p)
			size = dev->bytesperline_out[p] * h;
		size += vb->planes[p].data_offset;

		अगर (vb2_get_plane_payload(vb, p) < size) अणु
			dprपूर्णांकk(dev, 1, "%s the payload is too small for plane %u (%lu < %u)\n",
					__func__, p, vb2_get_plane_payload(vb, p), size);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vid_out_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vivid_buffer *buf = container_of(vbuf, काष्ठा vivid_buffer, vb);

	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	spin_lock(&dev->slock);
	list_add_tail(&buf->list, &dev->vid_out_active);
	spin_unlock(&dev->slock);
पूर्ण

अटल पूर्णांक vid_out_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित count)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);
	पूर्णांक err;

	अगर (vb2_is_streaming(&dev->vb_vid_cap_q))
		dev->can_loop_video = vivid_vid_can_loop(dev);

	dev->vid_out_seq_count = 0;
	dprपूर्णांकk(dev, 1, "%s\n", __func__);
	अगर (dev->start_streaming_error) अणु
		dev->start_streaming_error = false;
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		err = vivid_start_generating_vid_out(dev, &dev->vid_out_streaming);
	पूर्ण
	अगर (err) अणु
		काष्ठा vivid_buffer *buf, *पंचांगp;

		list_क्रम_each_entry_safe(buf, पंचांगp, &dev->vid_out_active, list) अणु
			list_del(&buf->list);
			vb2_buffer_करोne(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/* पात streaming and रुको क्रम last buffer */
अटल व्योम vid_out_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);

	dprपूर्णांकk(dev, 1, "%s\n", __func__);
	vivid_stop_generating_vid_out(dev, &dev->vid_out_streaming);
	dev->can_loop_video = false;
पूर्ण

अटल व्योम vid_out_buf_request_complete(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_ctrl_request_complete(vb->req_obj.req, &dev->ctrl_hdl_vid_out);
पूर्ण

स्थिर काष्ठा vb2_ops vivid_vid_out_qops = अणु
	.queue_setup		= vid_out_queue_setup,
	.buf_out_validate		= vid_out_buf_out_validate,
	.buf_prepare		= vid_out_buf_prepare,
	.buf_queue		= vid_out_buf_queue,
	.start_streaming	= vid_out_start_streaming,
	.stop_streaming		= vid_out_stop_streaming,
	.buf_request_complete	= vid_out_buf_request_complete,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

/*
 * Called whenever the क्रमmat has to be reset which can occur when
 * changing outमाला_दो, standard, timings, etc.
 */
व्योम vivid_update_क्रमmat_out(काष्ठा vivid_dev *dev)
अणु
	काष्ठा v4l2_bt_timings *bt = &dev->dv_timings_out.bt;
	अचिन्हित size, p;
	u64 pixelघड़ी;

	चयन (dev->output_type[dev->output]) अणु
	हाल SVID:
	शेष:
		dev->field_out = dev->tv_field_out;
		dev->sink_rect.width = 720;
		अगर (dev->std_out & V4L2_STD_525_60) अणु
			dev->sink_rect.height = 480;
			dev->समयperframe_vid_out = (काष्ठा v4l2_fract) अणु 1001, 30000 पूर्ण;
			dev->service_set_out = V4L2_SLICED_CAPTION_525;
		पूर्ण अन्यथा अणु
			dev->sink_rect.height = 576;
			dev->समयperframe_vid_out = (काष्ठा v4l2_fract) अणु 1000, 25000 पूर्ण;
			dev->service_set_out = V4L2_SLICED_WSS_625 | V4L2_SLICED_TELETEXT_B;
		पूर्ण
		dev->colorspace_out = V4L2_COLORSPACE_SMPTE170M;
		अवरोध;
	हाल HDMI:
		dev->sink_rect.width = bt->width;
		dev->sink_rect.height = bt->height;
		size = V4L2_DV_BT_FRAME_WIDTH(bt) * V4L2_DV_BT_FRAME_HEIGHT(bt);

		अगर (can_reduce_fps(bt) && (bt->flags & V4L2_DV_FL_REDUCED_FPS))
			pixelघड़ी = भाग_u64(bt->pixelघड़ी * 1000, 1001);
		अन्यथा
			pixelघड़ी = bt->pixelघड़ी;

		dev->समयperframe_vid_out = (काष्ठा v4l2_fract) अणु
			size / 100, (u32)pixelघड़ी / 100
		पूर्ण;
		अगर (bt->पूर्णांकerlaced)
			dev->field_out = V4L2_FIELD_ALTERNATE;
		अन्यथा
			dev->field_out = V4L2_FIELD_NONE;
		अगर (!dev->dvi_d_out && (bt->flags & V4L2_DV_FL_IS_CE_VIDEO)) अणु
			अगर (bt->width == 720 && bt->height <= 576)
				dev->colorspace_out = V4L2_COLORSPACE_SMPTE170M;
			अन्यथा
				dev->colorspace_out = V4L2_COLORSPACE_REC709;
		पूर्ण अन्यथा अणु
			dev->colorspace_out = V4L2_COLORSPACE_SRGB;
		पूर्ण
		अवरोध;
	पूर्ण
	dev->xfer_func_out = V4L2_XFER_FUNC_DEFAULT;
	dev->ycbcr_enc_out = V4L2_YCBCR_ENC_DEFAULT;
	dev->hsv_enc_out = V4L2_HSV_ENC_180;
	dev->quantization_out = V4L2_QUANTIZATION_DEFAULT;
	dev->compose_out = dev->sink_rect;
	dev->compose_bounds_out = dev->sink_rect;
	dev->crop_out = dev->compose_out;
	अगर (V4L2_FIELD_HAS_T_OR_B(dev->field_out))
		dev->crop_out.height /= 2;
	dev->fmt_out_rect = dev->crop_out;
	क्रम (p = 0; p < dev->fmt_out->planes; p++)
		dev->bytesperline_out[p] =
			(dev->sink_rect.width * dev->fmt_out->bit_depth[p]) / 8;
पूर्ण

/* Map the field to something that is valid क्रम the current output */
अटल क्रमागत v4l2_field vivid_field_out(काष्ठा vivid_dev *dev, क्रमागत v4l2_field field)
अणु
	अगर (vivid_is_svid_out(dev)) अणु
		चयन (field) अणु
		हाल V4L2_FIELD_INTERLACED_TB:
		हाल V4L2_FIELD_INTERLACED_BT:
		हाल V4L2_FIELD_SEQ_TB:
		हाल V4L2_FIELD_SEQ_BT:
		हाल V4L2_FIELD_ALTERNATE:
			वापस field;
		हाल V4L2_FIELD_INTERLACED:
		शेष:
			वापस V4L2_FIELD_INTERLACED;
		पूर्ण
	पूर्ण
	अगर (vivid_is_hdmi_out(dev))
		वापस dev->dv_timings_out.bt.पूर्णांकerlaced ? V4L2_FIELD_ALTERNATE :
						       V4L2_FIELD_NONE;
	वापस V4L2_FIELD_NONE;
पूर्ण

अटल क्रमागत tpg_pixel_aspect vivid_get_pixel_aspect(स्थिर काष्ठा vivid_dev *dev)
अणु
	अगर (vivid_is_svid_out(dev))
		वापस (dev->std_out & V4L2_STD_525_60) ?
			TPG_PIXEL_ASPECT_NTSC : TPG_PIXEL_ASPECT_PAL;

	अगर (vivid_is_hdmi_out(dev) &&
	    dev->sink_rect.width == 720 && dev->sink_rect.height <= 576)
		वापस dev->sink_rect.height == 480 ?
			TPG_PIXEL_ASPECT_NTSC : TPG_PIXEL_ASPECT_PAL;

	वापस TPG_PIXEL_ASPECT_SQUARE;
पूर्ण

पूर्णांक vivid_g_fmt_vid_out(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat_mplane *mp = &f->fmt.pix_mp;
	स्थिर काष्ठा vivid_fmt *fmt = dev->fmt_out;
	अचिन्हित p;

	mp->width        = dev->fmt_out_rect.width;
	mp->height       = dev->fmt_out_rect.height;
	mp->field        = dev->field_out;
	mp->pixelक्रमmat  = fmt->fourcc;
	mp->colorspace   = dev->colorspace_out;
	mp->xfer_func    = dev->xfer_func_out;
	mp->ycbcr_enc    = dev->ycbcr_enc_out;
	mp->quantization = dev->quantization_out;
	mp->num_planes = fmt->buffers;
	क्रम (p = 0; p < mp->num_planes; p++) अणु
		mp->plane_fmt[p].bytesperline = dev->bytesperline_out[p];
		mp->plane_fmt[p].sizeimage =
			mp->plane_fmt[p].bytesperline * mp->height +
			fmt->data_offset[p];
	पूर्ण
	क्रम (p = fmt->buffers; p < fmt->planes; p++) अणु
		अचिन्हित stride = dev->bytesperline_out[p];

		mp->plane_fmt[0].sizeimage +=
			(stride * mp->height) / fmt->vकरोwnsampling[p];
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vivid_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_bt_timings *bt = &dev->dv_timings_out.bt;
	काष्ठा v4l2_pix_क्रमmat_mplane *mp = &f->fmt.pix_mp;
	काष्ठा v4l2_plane_pix_क्रमmat *pfmt = mp->plane_fmt;
	स्थिर काष्ठा vivid_fmt *fmt;
	अचिन्हित bytesperline, max_bpl;
	अचिन्हित factor = 1;
	अचिन्हित w, h;
	अचिन्हित p;

	fmt = vivid_get_क्रमmat(dev, mp->pixelक्रमmat);
	अगर (!fmt) अणु
		dprपूर्णांकk(dev, 1, "Fourcc format (0x%08x) unknown.\n",
			mp->pixelक्रमmat);
		mp->pixelक्रमmat = V4L2_PIX_FMT_YUYV;
		fmt = vivid_get_क्रमmat(dev, mp->pixelक्रमmat);
	पूर्ण

	mp->field = vivid_field_out(dev, mp->field);
	अगर (vivid_is_svid_out(dev)) अणु
		w = 720;
		h = (dev->std_out & V4L2_STD_525_60) ? 480 : 576;
	पूर्ण अन्यथा अणु
		w = dev->sink_rect.width;
		h = dev->sink_rect.height;
	पूर्ण
	अगर (V4L2_FIELD_HAS_T_OR_B(mp->field))
		factor = 2;
	अगर (!dev->has_scaler_out && !dev->has_crop_out && !dev->has_compose_out) अणु
		mp->width = w;
		mp->height = h / factor;
	पूर्ण अन्यथा अणु
		काष्ठा v4l2_rect r = अणु 0, 0, mp->width, mp->height * factor पूर्ण;

		v4l2_rect_set_min_size(&r, &vivid_min_rect);
		v4l2_rect_set_max_size(&r, &vivid_max_rect);
		अगर (dev->has_scaler_out && !dev->has_crop_out) अणु
			काष्ठा v4l2_rect max_r = अणु 0, 0, MAX_ZOOM * w, MAX_ZOOM * h पूर्ण;

			v4l2_rect_set_max_size(&r, &max_r);
		पूर्ण अन्यथा अगर (!dev->has_scaler_out && dev->has_compose_out && !dev->has_crop_out) अणु
			v4l2_rect_set_max_size(&r, &dev->sink_rect);
		पूर्ण अन्यथा अगर (!dev->has_scaler_out && !dev->has_compose_out) अणु
			v4l2_rect_set_min_size(&r, &dev->sink_rect);
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

	mp->xfer_func = V4L2_XFER_FUNC_DEFAULT;
	mp->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	mp->quantization = V4L2_QUANTIZATION_DEFAULT;
	अगर (vivid_is_svid_out(dev)) अणु
		mp->colorspace = V4L2_COLORSPACE_SMPTE170M;
	पूर्ण अन्यथा अगर (dev->dvi_d_out || !(bt->flags & V4L2_DV_FL_IS_CE_VIDEO)) अणु
		mp->colorspace = V4L2_COLORSPACE_SRGB;
		अगर (dev->dvi_d_out)
			mp->quantization = V4L2_QUANTIZATION_LIM_RANGE;
	पूर्ण अन्यथा अगर (bt->width == 720 && bt->height <= 576) अणु
		mp->colorspace = V4L2_COLORSPACE_SMPTE170M;
	पूर्ण अन्यथा अगर (mp->colorspace != V4L2_COLORSPACE_SMPTE170M &&
		   mp->colorspace != V4L2_COLORSPACE_REC709 &&
		   mp->colorspace != V4L2_COLORSPACE_OPRGB &&
		   mp->colorspace != V4L2_COLORSPACE_BT2020 &&
		   mp->colorspace != V4L2_COLORSPACE_SRGB) अणु
		mp->colorspace = V4L2_COLORSPACE_REC709;
	पूर्ण
	स_रखो(mp->reserved, 0, माप(mp->reserved));
	वापस 0;
पूर्ण

पूर्णांक vivid_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *mp = &f->fmt.pix_mp;
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_rect *crop = &dev->crop_out;
	काष्ठा v4l2_rect *compose = &dev->compose_out;
	काष्ठा vb2_queue *q = &dev->vb_vid_out_q;
	पूर्णांक ret = vivid_try_fmt_vid_out(file, priv, f);
	अचिन्हित factor = 1;
	अचिन्हित p;

	अगर (ret < 0)
		वापस ret;

	अगर (vb2_is_busy(q) &&
	    (vivid_is_svid_out(dev) ||
	     mp->width != dev->fmt_out_rect.width ||
	     mp->height != dev->fmt_out_rect.height ||
	     mp->pixelक्रमmat != dev->fmt_out->fourcc ||
	     mp->field != dev->field_out)) अणु
		dprपूर्णांकk(dev, 1, "%s device busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	/*
	 * Allow क्रम changing the colorspace on the fly. Useful क्रम testing
	 * purposes, and it is something that HDMI transmitters are able
	 * to करो.
	 */
	अगर (vb2_is_busy(q))
		जाओ set_colorspace;

	dev->fmt_out = vivid_get_क्रमmat(dev, mp->pixelक्रमmat);
	अगर (V4L2_FIELD_HAS_T_OR_B(mp->field))
		factor = 2;

	अगर (dev->has_scaler_out || dev->has_crop_out || dev->has_compose_out) अणु
		काष्ठा v4l2_rect r = अणु 0, 0, mp->width, mp->height पूर्ण;

		अगर (dev->has_scaler_out) अणु
			अगर (dev->has_crop_out)
				v4l2_rect_map_inside(crop, &r);
			अन्यथा
				*crop = r;
			अगर (dev->has_compose_out && !dev->has_crop_out) अणु
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

				v4l2_rect_set_min_size(compose, &min_r);
				v4l2_rect_set_max_size(compose, &max_r);
				v4l2_rect_map_inside(compose, &dev->compose_bounds_out);
			पूर्ण अन्यथा अगर (dev->has_compose_out) अणु
				काष्ठा v4l2_rect min_r = अणु
					0, 0,
					crop->width / MAX_ZOOM,
					factor * crop->height / MAX_ZOOM
				पूर्ण;
				काष्ठा v4l2_rect max_r = अणु
					0, 0,
					crop->width * MAX_ZOOM,
					factor * crop->height * MAX_ZOOM
				पूर्ण;

				v4l2_rect_set_min_size(compose, &min_r);
				v4l2_rect_set_max_size(compose, &max_r);
				v4l2_rect_map_inside(compose, &dev->compose_bounds_out);
			पूर्ण
		पूर्ण अन्यथा अगर (dev->has_compose_out && !dev->has_crop_out) अणु
			v4l2_rect_set_माप_प्रकारo(crop, &r);
			r.height *= factor;
			v4l2_rect_set_माप_प्रकारo(compose, &r);
			v4l2_rect_map_inside(compose, &dev->compose_bounds_out);
		पूर्ण अन्यथा अगर (!dev->has_compose_out) अणु
			v4l2_rect_map_inside(crop, &r);
			r.height /= factor;
			v4l2_rect_set_माप_प्रकारo(compose, &r);
		पूर्ण अन्यथा अणु
			r.height *= factor;
			v4l2_rect_set_max_size(compose, &r);
			v4l2_rect_map_inside(compose, &dev->compose_bounds_out);
			crop->top *= factor;
			crop->height *= factor;
			v4l2_rect_set_माप_प्रकारo(crop, compose);
			v4l2_rect_map_inside(crop, &r);
			crop->top /= factor;
			crop->height /= factor;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा v4l2_rect r = अणु 0, 0, mp->width, mp->height पूर्ण;

		v4l2_rect_set_माप_प्रकारo(crop, &r);
		r.height /= factor;
		v4l2_rect_set_माप_प्रकारo(compose, &r);
	पूर्ण

	dev->fmt_out_rect.width = mp->width;
	dev->fmt_out_rect.height = mp->height;
	क्रम (p = 0; p < mp->num_planes; p++)
		dev->bytesperline_out[p] = mp->plane_fmt[p].bytesperline;
	क्रम (p = dev->fmt_out->buffers; p < dev->fmt_out->planes; p++)
		dev->bytesperline_out[p] =
			(dev->bytesperline_out[0] * dev->fmt_out->bit_depth[p]) /
			dev->fmt_out->bit_depth[0];
	dev->field_out = mp->field;
	अगर (vivid_is_svid_out(dev))
		dev->tv_field_out = mp->field;

set_colorspace:
	dev->colorspace_out = mp->colorspace;
	dev->xfer_func_out = mp->xfer_func;
	dev->ycbcr_enc_out = mp->ycbcr_enc;
	dev->quantization_out = mp->quantization;
	अगर (dev->loop_video) अणु
		vivid_send_source_change(dev, SVID);
		vivid_send_source_change(dev, HDMI);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vidioc_g_fmt_vid_out_mplane(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!dev->multiplanar)
		वापस -ENOTTY;
	वापस vivid_g_fmt_vid_out(file, priv, f);
पूर्ण

पूर्णांक vidioc_try_fmt_vid_out_mplane(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!dev->multiplanar)
		वापस -ENOTTY;
	वापस vivid_try_fmt_vid_out(file, priv, f);
पूर्ण

पूर्णांक vidioc_s_fmt_vid_out_mplane(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!dev->multiplanar)
		वापस -ENOTTY;
	वापस vivid_s_fmt_vid_out(file, priv, f);
पूर्ण

पूर्णांक vidioc_g_fmt_vid_out(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (dev->multiplanar)
		वापस -ENOTTY;
	वापस fmt_sp2mp_func(file, priv, f, vivid_g_fmt_vid_out);
पूर्ण

पूर्णांक vidioc_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (dev->multiplanar)
		वापस -ENOTTY;
	वापस fmt_sp2mp_func(file, priv, f, vivid_try_fmt_vid_out);
पूर्ण

पूर्णांक vidioc_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (dev->multiplanar)
		वापस -ENOTTY;
	वापस fmt_sp2mp_func(file, priv, f, vivid_s_fmt_vid_out);
पूर्ण

पूर्णांक vivid_vid_out_g_selection(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_selection *sel)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!dev->has_crop_out && !dev->has_compose_out)
		वापस -ENOTTY;
	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	sel->r.left = sel->r.top = 0;
	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		अगर (!dev->has_crop_out)
			वापस -EINVAL;
		sel->r = dev->crop_out;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		अगर (!dev->has_crop_out)
			वापस -EINVAL;
		sel->r = dev->fmt_out_rect;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		अगर (!dev->has_crop_out)
			वापस -EINVAL;
		sel->r = vivid_max_rect;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		अगर (!dev->has_compose_out)
			वापस -EINVAL;
		sel->r = dev->compose_out;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		अगर (!dev->has_compose_out)
			वापस -EINVAL;
		sel->r = dev->sink_rect;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vivid_vid_out_s_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *s)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_rect *crop = &dev->crop_out;
	काष्ठा v4l2_rect *compose = &dev->compose_out;
	अचिन्हित factor = V4L2_FIELD_HAS_T_OR_B(dev->field_out) ? 2 : 1;
	पूर्णांक ret;

	अगर (!dev->has_crop_out && !dev->has_compose_out)
		वापस -ENOTTY;
	अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		अगर (!dev->has_crop_out)
			वापस -EINVAL;
		ret = vivid_vid_adjust_sel(s->flags, &s->r);
		अगर (ret)
			वापस ret;
		v4l2_rect_set_min_size(&s->r, &vivid_min_rect);
		v4l2_rect_set_max_size(&s->r, &dev->fmt_out_rect);
		अगर (dev->has_scaler_out) अणु
			काष्ठा v4l2_rect max_rect = अणु
				0, 0,
				dev->sink_rect.width * MAX_ZOOM,
				(dev->sink_rect.height / factor) * MAX_ZOOM
			पूर्ण;

			v4l2_rect_set_max_size(&s->r, &max_rect);
			अगर (dev->has_compose_out) अणु
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

				v4l2_rect_set_min_size(compose, &min_rect);
				v4l2_rect_set_max_size(compose, &max_rect);
				v4l2_rect_map_inside(compose, &dev->compose_bounds_out);
			पूर्ण
		पूर्ण अन्यथा अगर (dev->has_compose_out) अणु
			s->r.top *= factor;
			s->r.height *= factor;
			v4l2_rect_set_max_size(&s->r, &dev->sink_rect);
			v4l2_rect_set_माप_प्रकारo(compose, &s->r);
			v4l2_rect_map_inside(compose, &dev->compose_bounds_out);
			s->r.top /= factor;
			s->r.height /= factor;
		पूर्ण अन्यथा अणु
			v4l2_rect_set_माप_प्रकारo(&s->r, &dev->sink_rect);
			s->r.height /= factor;
		पूर्ण
		v4l2_rect_map_inside(&s->r, &dev->fmt_out_rect);
		*crop = s->r;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		अगर (!dev->has_compose_out)
			वापस -EINVAL;
		ret = vivid_vid_adjust_sel(s->flags, &s->r);
		अगर (ret)
			वापस ret;
		v4l2_rect_set_min_size(&s->r, &vivid_min_rect);
		v4l2_rect_set_max_size(&s->r, &dev->sink_rect);
		v4l2_rect_map_inside(&s->r, &dev->compose_bounds_out);
		s->r.top /= factor;
		s->r.height /= factor;
		अगर (dev->has_scaler_out) अणु
			काष्ठा v4l2_rect fmt = dev->fmt_out_rect;
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
			अगर (!dev->has_crop_out)
				v4l2_rect_set_max_size(&fmt, &max_rect);
			अगर (!v4l2_rect_same_size(&dev->fmt_out_rect, &fmt) &&
			    vb2_is_busy(&dev->vb_vid_out_q))
				वापस -EBUSY;
			अगर (dev->has_crop_out) अणु
				v4l2_rect_set_min_size(crop, &min_rect);
				v4l2_rect_set_max_size(crop, &max_rect);
			पूर्ण
			dev->fmt_out_rect = fmt;
		पूर्ण अन्यथा अगर (dev->has_crop_out) अणु
			काष्ठा v4l2_rect fmt = dev->fmt_out_rect;

			v4l2_rect_set_min_size(&fmt, &s->r);
			अगर (!v4l2_rect_same_size(&dev->fmt_out_rect, &fmt) &&
			    vb2_is_busy(&dev->vb_vid_out_q))
				वापस -EBUSY;
			dev->fmt_out_rect = fmt;
			v4l2_rect_set_माप_प्रकारo(crop, &s->r);
			v4l2_rect_map_inside(crop, &dev->fmt_out_rect);
		पूर्ण अन्यथा अणु
			अगर (!v4l2_rect_same_size(&s->r, &dev->fmt_out_rect) &&
			    vb2_is_busy(&dev->vb_vid_out_q))
				वापस -EBUSY;
			v4l2_rect_set_माप_प्रकारo(&dev->fmt_out_rect, &s->r);
			v4l2_rect_set_माप_प्रकारo(crop, &s->r);
			crop->height /= factor;
			v4l2_rect_map_inside(crop, &dev->fmt_out_rect);
		पूर्ण
		s->r.top *= factor;
		s->r.height *= factor;
		अगर (dev->biपंचांगap_out && (compose->width != s->r.width ||
					compose->height != s->r.height)) अणु
			vमुक्त(dev->biपंचांगap_out);
			dev->biपंचांगap_out = शून्य;
		पूर्ण
		*compose = s->r;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vivid_vid_out_g_pixelaspect(काष्ठा file *file, व्योम *priv,
				पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
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

पूर्णांक vidioc_g_fmt_vid_out_overlay(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	स्थिर काष्ठा v4l2_rect *compose = &dev->compose_out;
	काष्ठा v4l2_winकरोw *win = &f->fmt.win;
	अचिन्हित clipcount = win->clipcount;

	अगर (!dev->has_fb)
		वापस -EINVAL;
	win->w.top = dev->overlay_out_top;
	win->w.left = dev->overlay_out_left;
	win->w.width = compose->width;
	win->w.height = compose->height;
	win->clipcount = dev->clipcount_out;
	win->field = V4L2_FIELD_ANY;
	win->chromakey = dev->chromakey_out;
	win->global_alpha = dev->global_alpha_out;
	अगर (clipcount > dev->clipcount_out)
		clipcount = dev->clipcount_out;
	अगर (dev->biपंचांगap_out == शून्य)
		win->biपंचांगap = शून्य;
	अन्यथा अगर (win->biपंचांगap) अणु
		अगर (copy_to_user(win->biपंचांगap, dev->biपंचांगap_out,
		    ((dev->compose_out.width + 7) / 8) * dev->compose_out.height))
			वापस -EFAULT;
	पूर्ण
	अगर (clipcount && win->clips)
		स_नकल(win->clips, dev->clips_out,
		       clipcount * माप(dev->clips_out[0]));
	वापस 0;
पूर्ण

पूर्णांक vidioc_try_fmt_vid_out_overlay(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	स्थिर काष्ठा v4l2_rect *compose = &dev->compose_out;
	काष्ठा v4l2_winकरोw *win = &f->fmt.win;
	पूर्णांक i, j;

	अगर (!dev->has_fb)
		वापस -EINVAL;
	win->w.left = clamp_t(पूर्णांक, win->w.left,
			      -dev->display_width, dev->display_width);
	win->w.top = clamp_t(पूर्णांक, win->w.top,
			     -dev->display_height, dev->display_height);
	win->w.width = compose->width;
	win->w.height = compose->height;
	/*
	 * It makes no sense क्रम an OSD to overlay only top or bottom fields,
	 * so always set this to ANY.
	 */
	win->field = V4L2_FIELD_ANY;
	अगर (win->clipcount && !win->clips)
		win->clipcount = 0;
	अगर (win->clipcount > MAX_CLIPS)
		win->clipcount = MAX_CLIPS;
	अगर (win->clipcount) अणु
		स_नकल(dev->try_clips_out, win->clips,
		       win->clipcount * माप(dev->clips_out[0]));
		क्रम (i = 0; i < win->clipcount; i++) अणु
			काष्ठा v4l2_rect *r = &dev->try_clips_out[i].c;

			r->top = clamp_t(s32, r->top, 0, dev->display_height - 1);
			r->height = clamp_t(s32, r->height, 1, dev->display_height - r->top);
			r->left = clamp_t(u32, r->left, 0, dev->display_width - 1);
			r->width = clamp_t(u32, r->width, 1, dev->display_width - r->left);
		पूर्ण
		/*
		 * Yeah, so sue me, it's an O(n^2) algorithm. But n is a small
		 * number and it's typically a one-समय deal.
		 */
		क्रम (i = 0; i < win->clipcount - 1; i++) अणु
			काष्ठा v4l2_rect *r1 = &dev->try_clips_out[i].c;

			क्रम (j = i + 1; j < win->clipcount; j++) अणु
				काष्ठा v4l2_rect *r2 = &dev->try_clips_out[j].c;

				अगर (v4l2_rect_overlap(r1, r2))
					वापस -EINVAL;
			पूर्ण
		पूर्ण
		स_नकल(win->clips, dev->try_clips_out,
		       win->clipcount * माप(dev->clips_out[0]));
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vidioc_s_fmt_vid_out_overlay(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	स्थिर काष्ठा v4l2_rect *compose = &dev->compose_out;
	काष्ठा v4l2_winकरोw *win = &f->fmt.win;
	पूर्णांक ret = vidioc_try_fmt_vid_out_overlay(file, priv, f);
	अचिन्हित biपंचांगap_size = ((compose->width + 7) / 8) * compose->height;
	अचिन्हित clips_size = win->clipcount * माप(dev->clips_out[0]);
	व्योम *new_biपंचांगap = शून्य;

	अगर (ret)
		वापस ret;

	अगर (win->biपंचांगap) अणु
		new_biपंचांगap = vzalloc(biपंचांगap_size);

		अगर (!new_biपंचांगap)
			वापस -ENOMEM;
		अगर (copy_from_user(new_biपंचांगap, win->biपंचांगap, biपंचांगap_size)) अणु
			vमुक्त(new_biपंचांगap);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	dev->overlay_out_top = win->w.top;
	dev->overlay_out_left = win->w.left;
	vमुक्त(dev->biपंचांगap_out);
	dev->biपंचांगap_out = new_biपंचांगap;
	dev->clipcount_out = win->clipcount;
	अगर (dev->clipcount_out)
		स_नकल(dev->clips_out, dev->try_clips_out, clips_size);
	dev->chromakey_out = win->chromakey;
	dev->global_alpha_out = win->global_alpha;
	वापस ret;
पूर्ण

पूर्णांक vivid_vid_out_overlay(काष्ठा file *file, व्योम *fh, अचिन्हित i)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (i && !dev->fmt_out->can_करो_overlay) अणु
		dprपूर्णांकk(dev, 1, "unsupported output format for output overlay\n");
		वापस -EINVAL;
	पूर्ण

	dev->overlay_out_enabled = i;
	वापस 0;
पूर्ण

पूर्णांक vivid_vid_out_g_fbuf(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_framebuffer *a)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	a->capability = V4L2_FBUF_CAP_EXTERNOVERLAY |
			V4L2_FBUF_CAP_BITMAP_CLIPPING |
			V4L2_FBUF_CAP_LIST_CLIPPING |
			V4L2_FBUF_CAP_CHROMAKEY |
			V4L2_FBUF_CAP_SRC_CHROMAKEY |
			V4L2_FBUF_CAP_GLOBAL_ALPHA |
			V4L2_FBUF_CAP_LOCAL_ALPHA |
			V4L2_FBUF_CAP_LOCAL_INV_ALPHA;
	a->flags = V4L2_FBUF_FLAG_OVERLAY | dev->fbuf_out_flags;
	a->base = (व्योम *)dev->video_pbase;
	a->fmt.width = dev->display_width;
	a->fmt.height = dev->display_height;
	अगर (dev->fb_defined.green.length == 5)
		a->fmt.pixelक्रमmat = V4L2_PIX_FMT_ARGB555;
	अन्यथा
		a->fmt.pixelक्रमmat = V4L2_PIX_FMT_RGB565;
	a->fmt.bytesperline = dev->display_byte_stride;
	a->fmt.sizeimage = a->fmt.height * a->fmt.bytesperline;
	a->fmt.field = V4L2_FIELD_NONE;
	a->fmt.colorspace = V4L2_COLORSPACE_SRGB;
	a->fmt.priv = 0;
	वापस 0;
पूर्ण

पूर्णांक vivid_vid_out_s_fbuf(काष्ठा file *file, व्योम *fh,
				स्थिर काष्ठा v4l2_framebuffer *a)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	स्थिर अचिन्हित chroma_flags = V4L2_FBUF_FLAG_CHROMAKEY |
				      V4L2_FBUF_FLAG_SRC_CHROMAKEY;
	स्थिर अचिन्हित alpha_flags = V4L2_FBUF_FLAG_GLOBAL_ALPHA |
				     V4L2_FBUF_FLAG_LOCAL_ALPHA |
				     V4L2_FBUF_FLAG_LOCAL_INV_ALPHA;


	अगर ((a->flags & chroma_flags) == chroma_flags)
		वापस -EINVAL;
	चयन (a->flags & alpha_flags) अणु
	हाल 0:
	हाल V4L2_FBUF_FLAG_GLOBAL_ALPHA:
	हाल V4L2_FBUF_FLAG_LOCAL_ALPHA:
	हाल V4L2_FBUF_FLAG_LOCAL_INV_ALPHA:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	dev->fbuf_out_flags &= ~(chroma_flags | alpha_flags);
	dev->fbuf_out_flags |= a->flags & (chroma_flags | alpha_flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_audioout vivid_audio_outमाला_दो[] = अणु
	अणु 0, "Line-Out 1" पूर्ण,
	अणु 1, "Line-Out 2" पूर्ण,
पूर्ण;

पूर्णांक vidioc_क्रमागत_output(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_output *out)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (out->index >= dev->num_outमाला_दो)
		वापस -EINVAL;

	out->type = V4L2_OUTPUT_TYPE_ANALOG;
	चयन (dev->output_type[out->index]) अणु
	हाल SVID:
		snम_लिखो(out->name, माप(out->name), "S-Video %u",
				dev->output_name_counter[out->index]);
		out->std = V4L2_STD_ALL;
		अगर (dev->has_audio_outमाला_दो)
			out->audioset = (1 << ARRAY_SIZE(vivid_audio_outमाला_दो)) - 1;
		out->capabilities = V4L2_OUT_CAP_STD;
		अवरोध;
	हाल HDMI:
		snम_लिखो(out->name, माप(out->name), "HDMI %u",
				dev->output_name_counter[out->index]);
		out->capabilities = V4L2_OUT_CAP_DV_TIMINGS;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vidioc_g_output(काष्ठा file *file, व्योम *priv, अचिन्हित *o)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	*o = dev->output;
	वापस 0;
पूर्ण

पूर्णांक vidioc_s_output(काष्ठा file *file, व्योम *priv, अचिन्हित o)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (o >= dev->num_outमाला_दो)
		वापस -EINVAL;

	अगर (o == dev->output)
		वापस 0;

	अगर (vb2_is_busy(&dev->vb_vid_out_q) ||
	    vb2_is_busy(&dev->vb_vbi_out_q) ||
	    vb2_is_busy(&dev->vb_meta_out_q))
		वापस -EBUSY;

	dev->output = o;
	dev->tv_audio_output = 0;
	अगर (dev->output_type[o] == SVID)
		dev->vid_out_dev.tvnorms = V4L2_STD_ALL;
	अन्यथा
		dev->vid_out_dev.tvnorms = 0;

	dev->vbi_out_dev.tvnorms = dev->vid_out_dev.tvnorms;
	dev->meta_out_dev.tvnorms = dev->vid_out_dev.tvnorms;
	vivid_update_क्रमmat_out(dev);

	v4l2_ctrl_activate(dev->ctrl_display_present, vivid_is_hdmi_out(dev));
	अगर (vivid_is_hdmi_out(dev))
		v4l2_ctrl_s_ctrl(dev->ctrl_display_present,
				 dev->display_present[dev->output]);

	वापस 0;
पूर्ण

पूर्णांक vidioc_क्रमागतauकरोut(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audioout *vout)
अणु
	अगर (vout->index >= ARRAY_SIZE(vivid_audio_outमाला_दो))
		वापस -EINVAL;
	*vout = vivid_audio_outमाला_दो[vout->index];
	वापस 0;
पूर्ण

पूर्णांक vidioc_g_auकरोut(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audioout *vout)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!vivid_is_svid_out(dev))
		वापस -EINVAL;
	*vout = vivid_audio_outमाला_दो[dev->tv_audio_output];
	वापस 0;
पूर्ण

पूर्णांक vidioc_s_auकरोut(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_audioout *vout)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!vivid_is_svid_out(dev))
		वापस -EINVAL;
	अगर (vout->index >= ARRAY_SIZE(vivid_audio_outमाला_दो))
		वापस -EINVAL;
	dev->tv_audio_output = vout->index;
	वापस 0;
पूर्ण

पूर्णांक vivid_vid_out_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (!vivid_is_svid_out(dev))
		वापस -ENODATA;
	अगर (dev->std_out == id)
		वापस 0;
	अगर (vb2_is_busy(&dev->vb_vid_out_q) || vb2_is_busy(&dev->vb_vbi_out_q))
		वापस -EBUSY;
	dev->std_out = id;
	vivid_update_क्रमmat_out(dev);
	वापस 0;
पूर्ण

अटल bool valid_cvt_gtf_timings(काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा v4l2_bt_timings *bt = &timings->bt;

	अगर ((bt->standards & (V4L2_DV_BT_STD_CVT | V4L2_DV_BT_STD_GTF)) &&
	    v4l2_valid_dv_timings(timings, &vivid_dv_timings_cap, शून्य, शून्य))
		वापस true;

	वापस false;
पूर्ण

पूर्णांक vivid_vid_out_s_dv_timings(काष्ठा file *file, व्योम *_fh,
				    काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	अगर (!vivid_is_hdmi_out(dev))
		वापस -ENODATA;
	अगर (!v4l2_find_dv_timings_cap(timings, &vivid_dv_timings_cap,
				0, शून्य, शून्य) &&
	    !valid_cvt_gtf_timings(timings))
		वापस -EINVAL;
	अगर (v4l2_match_dv_timings(timings, &dev->dv_timings_out, 0, true))
		वापस 0;
	अगर (vb2_is_busy(&dev->vb_vid_out_q))
		वापस -EBUSY;
	dev->dv_timings_out = *timings;
	vivid_update_क्रमmat_out(dev);
	वापस 0;
पूर्ण

पूर्णांक vivid_vid_out_g_parm(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (parm->type != (dev->multiplanar ?
			   V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE :
			   V4L2_BUF_TYPE_VIDEO_OUTPUT))
		वापस -EINVAL;

	parm->parm.output.capability   = V4L2_CAP_TIMEPERFRAME;
	parm->parm.output.समयperframe = dev->समयperframe_vid_out;
	parm->parm.output.ग_लिखोbuffers  = 1;

	वापस 0;
पूर्ण

पूर्णांक vidioc_subscribe_event(काष्ठा v4l2_fh *fh,
			स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_SOURCE_CHANGE:
		अगर (fh->vdev->vfl_dir == VFL_सूची_RX)
			वापस v4l2_src_change_event_subscribe(fh, sub);
		अवरोध;
	शेष:
		वापस v4l2_ctrl_subscribe_event(fh, sub);
	पूर्ण
	वापस -EINVAL;
पूर्ण
