<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2006 Micronas USA Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/unistd.h>
#समावेश <linux/समय.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <media/i2c/saa7115.h>

#समावेश "go7007-priv.h"

#घोषणा call_all(dev, o, f, args...) \
	v4l2_device_call_until_err(dev, 0, o, f, ##args)

अटल bool valid_pixelक्रमmat(u32 pixelक्रमmat)
अणु
	चयन (pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_MJPEG:
	हाल V4L2_PIX_FMT_MPEG1:
	हाल V4L2_PIX_FMT_MPEG2:
	हाल V4L2_PIX_FMT_MPEG4:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल u32 get_frame_type_flag(काष्ठा go7007_buffer *vb, पूर्णांक क्रमmat)
अणु
	u8 *ptr = vb2_plane_vaddr(&vb->vb.vb2_buf, 0);

	चयन (क्रमmat) अणु
	हाल V4L2_PIX_FMT_MJPEG:
		वापस V4L2_BUF_FLAG_KEYFRAME;
	हाल V4L2_PIX_FMT_MPEG4:
		चयन ((ptr[vb->frame_offset + 4] >> 6) & 0x3) अणु
		हाल 0:
			वापस V4L2_BUF_FLAG_KEYFRAME;
		हाल 1:
			वापस V4L2_BUF_FLAG_PFRAME;
		हाल 2:
			वापस V4L2_BUF_FLAG_BFRAME;
		शेष:
			वापस 0;
		पूर्ण
	हाल V4L2_PIX_FMT_MPEG1:
	हाल V4L2_PIX_FMT_MPEG2:
		चयन ((ptr[vb->frame_offset + 5] >> 3) & 0x7) अणु
		हाल 1:
			वापस V4L2_BUF_FLAG_KEYFRAME;
		हाल 2:
			वापस V4L2_BUF_FLAG_PFRAME;
		हाल 3:
			वापस V4L2_BUF_FLAG_BFRAME;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम get_resolution(काष्ठा go7007 *go, पूर्णांक *width, पूर्णांक *height)
अणु
	चयन (go->standard) अणु
	हाल GO7007_STD_NTSC:
		*width = 720;
		*height = 480;
		अवरोध;
	हाल GO7007_STD_PAL:
		*width = 720;
		*height = 576;
		अवरोध;
	हाल GO7007_STD_OTHER:
	शेष:
		*width = go->board_info->sensor_width;
		*height = go->board_info->sensor_height;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम set_क्रमmatting(काष्ठा go7007 *go)
अणु
	अगर (go->क्रमmat == V4L2_PIX_FMT_MJPEG) अणु
		go->pali = 0;
		go->aspect_ratio = GO7007_RATIO_1_1;
		go->gop_size = 0;
		go->ipb = 0;
		go->बंदd_gop = 0;
		go->repeat_seqhead = 0;
		go->seq_header_enable = 0;
		go->gop_header_enable = 0;
		go->dvd_mode = 0;
		वापस;
	पूर्ण

	चयन (go->क्रमmat) अणु
	हाल V4L2_PIX_FMT_MPEG1:
		go->pali = 0;
		अवरोध;
	शेष:
	हाल V4L2_PIX_FMT_MPEG2:
		go->pali = 0x48;
		अवरोध;
	हाल V4L2_PIX_FMT_MPEG4:
		/* For future reference: this is the list of MPEG4
		 * profiles that are available, although they are
		 * untested:
		 *
		 * Profile		pali
		 * --------------	----
		 * PROखाता_S_L0		0x08
		 * PROखाता_S_L1		0x01
		 * PROखाता_S_L2		0x02
		 * PROखाता_S_L3		0x03
		 * PROखाता_ARTS_L1	0x91
		 * PROखाता_ARTS_L2	0x92
		 * PROखाता_ARTS_L3	0x93
		 * PROखाता_ARTS_L4	0x94
		 * PROखाता_AS_L0	0xf0
		 * PROखाता_AS_L1	0xf1
		 * PROखाता_AS_L2	0xf2
		 * PROखाता_AS_L3	0xf3
		 * PROखाता_AS_L4	0xf4
		 * PROखाता_AS_L5	0xf5
		 */
		go->pali = 0xf5;
		अवरोध;
	पूर्ण
	go->gop_size = v4l2_ctrl_g_ctrl(go->mpeg_video_gop_size);
	go->बंदd_gop = v4l2_ctrl_g_ctrl(go->mpeg_video_gop_closure);
	go->ipb = v4l2_ctrl_g_ctrl(go->mpeg_video_b_frames) != 0;
	go->bitrate = v4l2_ctrl_g_ctrl(go->mpeg_video_bitrate);
	go->repeat_seqhead = v4l2_ctrl_g_ctrl(go->mpeg_video_rep_seqheader);
	go->gop_header_enable = 1;
	go->dvd_mode = 0;
	अगर (go->क्रमmat == V4L2_PIX_FMT_MPEG2)
		go->dvd_mode =
			go->bitrate == 9800000 &&
			go->gop_size == 15 &&
			go->ipb == 0 &&
			go->repeat_seqhead == 1 &&
			go->बंदd_gop;

	चयन (v4l2_ctrl_g_ctrl(go->mpeg_video_aspect_ratio)) अणु
	शेष:
	हाल V4L2_MPEG_VIDEO_ASPECT_1x1:
		go->aspect_ratio = GO7007_RATIO_1_1;
		अवरोध;
	हाल V4L2_MPEG_VIDEO_ASPECT_4x3:
		go->aspect_ratio = GO7007_RATIO_4_3;
		अवरोध;
	हाल V4L2_MPEG_VIDEO_ASPECT_16x9:
		go->aspect_ratio = GO7007_RATIO_16_9;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक set_capture_size(काष्ठा go7007 *go, काष्ठा v4l2_क्रमmat *fmt, पूर्णांक try)
अणु
	पूर्णांक sensor_height = 0, sensor_width = 0;
	पूर्णांक width, height;

	अगर (fmt != शून्य && !valid_pixelक्रमmat(fmt->fmt.pix.pixelक्रमmat))
		वापस -EINVAL;

	get_resolution(go, &sensor_width, &sensor_height);

	अगर (fmt == शून्य) अणु
		width = sensor_width;
		height = sensor_height;
	पूर्ण अन्यथा अगर (go->board_info->sensor_flags & GO7007_SENSOR_SCALING) अणु
		अगर (fmt->fmt.pix.width > sensor_width)
			width = sensor_width;
		अन्यथा अगर (fmt->fmt.pix.width < 144)
			width = 144;
		अन्यथा
			width = fmt->fmt.pix.width & ~0x0f;

		अगर (fmt->fmt.pix.height > sensor_height)
			height = sensor_height;
		अन्यथा अगर (fmt->fmt.pix.height < 96)
			height = 96;
		अन्यथा
			height = fmt->fmt.pix.height & ~0x0f;
	पूर्ण अन्यथा अणु
		width = fmt->fmt.pix.width;

		अगर (width <= sensor_width / 4) अणु
			width = sensor_width / 4;
			height = sensor_height / 4;
		पूर्ण अन्यथा अगर (width <= sensor_width / 2) अणु
			width = sensor_width / 2;
			height = sensor_height / 2;
		पूर्ण अन्यथा अणु
			width = sensor_width;
			height = sensor_height;
		पूर्ण
		width &= ~0xf;
		height &= ~0xf;
	पूर्ण

	अगर (fmt != शून्य) अणु
		u32 pixelक्रमmat = fmt->fmt.pix.pixelक्रमmat;

		स_रखो(fmt, 0, माप(*fmt));
		fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		fmt->fmt.pix.width = width;
		fmt->fmt.pix.height = height;
		fmt->fmt.pix.pixelक्रमmat = pixelक्रमmat;
		fmt->fmt.pix.field = V4L2_FIELD_NONE;
		fmt->fmt.pix.bytesperline = 0;
		fmt->fmt.pix.sizeimage = GO7007_BUF_SIZE;
		fmt->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	पूर्ण

	अगर (try)
		वापस 0;

	अगर (fmt)
		go->क्रमmat = fmt->fmt.pix.pixelक्रमmat;
	go->width = width;
	go->height = height;
	go->encoder_h_offset = go->board_info->sensor_h_offset;
	go->encoder_v_offset = go->board_info->sensor_v_offset;

	अगर (go->board_info->sensor_flags & GO7007_SENSOR_SCALING) अणु
		काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
			.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		पूर्ण;

		क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_FIXED;
		क्रमmat.क्रमmat.width = fmt ? fmt->fmt.pix.width : width;
		क्रमmat.क्रमmat.height = height;
		go->encoder_h_halve = 0;
		go->encoder_v_halve = 0;
		go->encoder_subsample = 0;
		call_all(&go->v4l2_dev, pad, set_fmt, शून्य, &क्रमmat);
	पूर्ण अन्यथा अणु
		अगर (width <= sensor_width / 4) अणु
			go->encoder_h_halve = 1;
			go->encoder_v_halve = 1;
			go->encoder_subsample = 1;
		पूर्ण अन्यथा अगर (width <= sensor_width / 2) अणु
			go->encoder_h_halve = 1;
			go->encoder_v_halve = 1;
			go->encoder_subsample = 0;
		पूर्ण अन्यथा अणु
			go->encoder_h_halve = 0;
			go->encoder_v_halve = 0;
			go->encoder_subsample = 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_capability *cap)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	strscpy(cap->driver, "go7007", माप(cap->driver));
	strscpy(cap->card, go->name, माप(cap->card));
	strscpy(cap->bus_info, go->bus_info, माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *fmt)
अणु
	चयन (fmt->index) अणु
	हाल 0:
		fmt->pixelक्रमmat = V4L2_PIX_FMT_MJPEG;
		अवरोध;
	हाल 1:
		fmt->pixelक्रमmat = V4L2_PIX_FMT_MPEG1;
		अवरोध;
	हाल 2:
		fmt->pixelक्रमmat = V4L2_PIX_FMT_MPEG2;
		अवरोध;
	हाल 3:
		fmt->pixelक्रमmat = V4L2_PIX_FMT_MPEG4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt->fmt.pix.width = go->width;
	fmt->fmt.pix.height = go->height;
	fmt->fmt.pix.pixelक्रमmat = go->क्रमmat;
	fmt->fmt.pix.field = V4L2_FIELD_NONE;
	fmt->fmt.pix.bytesperline = 0;
	fmt->fmt.pix.sizeimage = GO7007_BUF_SIZE;
	fmt->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	वापस set_capture_size(go, fmt, 1);
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	अगर (vb2_is_busy(&go->vidq))
		वापस -EBUSY;

	वापस set_capture_size(go, fmt, 0);
पूर्ण

अटल पूर्णांक go7007_queue_setup(काष्ठा vb2_queue *q,
		अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
		अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	sizes[0] = GO7007_BUF_SIZE;
	*num_planes = 1;

	अगर (*num_buffers < 2)
		*num_buffers = 2;

	वापस 0;
पूर्ण

अटल व्योम go7007_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा go7007 *go = vb2_get_drv_priv(vq);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा go7007_buffer *go7007_vb =
		container_of(vbuf, काष्ठा go7007_buffer, vb);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&go->spinlock, flags);
	list_add_tail(&go7007_vb->list, &go->vidq_active);
	spin_unlock_irqrestore(&go->spinlock, flags);
पूर्ण

अटल पूर्णांक go7007_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा go7007_buffer *go7007_vb =
		container_of(vbuf, काष्ठा go7007_buffer, vb);

	go7007_vb->modet_active = 0;
	go7007_vb->frame_offset = 0;
	vb->planes[0].bytesused = 0;
	वापस 0;
पूर्ण

अटल व्योम go7007_buf_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा go7007 *go = vb2_get_drv_priv(vq);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा go7007_buffer *go7007_vb =
		container_of(vbuf, काष्ठा go7007_buffer, vb);
	u32 frame_type_flag = get_frame_type_flag(go7007_vb, go->क्रमmat);

	vbuf->flags &= ~(V4L2_BUF_FLAG_KEYFRAME | V4L2_BUF_FLAG_BFRAME |
			V4L2_BUF_FLAG_PFRAME);
	vbuf->flags |= frame_type_flag;
	vbuf->field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक go7007_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा go7007 *go = vb2_get_drv_priv(q);
	पूर्णांक ret;

	set_क्रमmatting(go);
	mutex_lock(&go->hw_lock);
	go->next_seq = 0;
	go->active_buf = शून्य;
	go->modet_event_status = 0;
	q->streaming = 1;
	अगर (go7007_start_encoder(go) < 0)
		ret = -EIO;
	अन्यथा
		ret = 0;
	mutex_unlock(&go->hw_lock);
	अगर (ret) अणु
		q->streaming = 0;
		वापस ret;
	पूर्ण
	call_all(&go->v4l2_dev, video, s_stream, 1);
	v4l2_ctrl_grab(go->mpeg_video_gop_size, true);
	v4l2_ctrl_grab(go->mpeg_video_gop_closure, true);
	v4l2_ctrl_grab(go->mpeg_video_bitrate, true);
	v4l2_ctrl_grab(go->mpeg_video_aspect_ratio, true);
	/* Turn on Capture LED */
	अगर (go->board_id == GO7007_BOARDID_ADS_USBAV_709)
		go7007_ग_लिखो_addr(go, 0x3c82, 0x0005);
	वापस ret;
पूर्ण

अटल व्योम go7007_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा go7007 *go = vb2_get_drv_priv(q);
	अचिन्हित दीर्घ flags;

	q->streaming = 0;
	go7007_stream_stop(go);
	mutex_lock(&go->hw_lock);
	go7007_reset_encoder(go);
	mutex_unlock(&go->hw_lock);
	call_all(&go->v4l2_dev, video, s_stream, 0);

	spin_lock_irqsave(&go->spinlock, flags);
	INIT_LIST_HEAD(&go->vidq_active);
	spin_unlock_irqrestore(&go->spinlock, flags);
	v4l2_ctrl_grab(go->mpeg_video_gop_size, false);
	v4l2_ctrl_grab(go->mpeg_video_gop_closure, false);
	v4l2_ctrl_grab(go->mpeg_video_bitrate, false);
	v4l2_ctrl_grab(go->mpeg_video_aspect_ratio, false);
	/* Turn on Capture LED */
	अगर (go->board_id == GO7007_BOARDID_ADS_USBAV_709)
		go7007_ग_लिखो_addr(go, 0x3c82, 0x000d);
पूर्ण

अटल स्थिर काष्ठा vb2_ops go7007_video_qops = अणु
	.queue_setup    = go7007_queue_setup,
	.buf_queue      = go7007_buf_queue,
	.buf_prepare    = go7007_buf_prepare,
	.buf_finish     = go7007_buf_finish,
	.start_streaming = go7007_start_streaming,
	.stop_streaming = go7007_stop_streaming,
	.रुको_prepare   = vb2_ops_रुको_prepare,
	.रुको_finish    = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक vidioc_g_parm(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा go7007 *go = video_drvdata(filp);
	काष्ठा v4l2_fract समयperframe = अणु
		.numerator = 1001 *  go->fps_scale,
		.denominator = go->sensor_framerate,
	पूर्ण;

	अगर (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	parm->parm.capture.पढ़ोbuffers = 2;
	parm->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	parm->parm.capture.समयperframe = समयperframe;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_parm(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा go7007 *go = video_drvdata(filp);
	अचिन्हित पूर्णांक n, d;

	अगर (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	n = go->sensor_framerate *
		parm->parm.capture.समयperframe.numerator;
	d = 1001 * parm->parm.capture.समयperframe.denominator;
	अगर (n != 0 && d != 0 && n > d)
		go->fps_scale = (n + d/2) / d;
	अन्यथा
		go->fps_scale = 1;

	वापस vidioc_g_parm(filp, priv, parm);
पूर्ण

/* VIDIOC_ENUMSTD on go7007 were used क्रम क्रमागतerating the supported fps and
   its resolution, when the device is not connected to TV.
   This is were an API abuse, probably used by the lack of specअगरic IOCTL's to
   क्रमागतerate it, by the समय the driver was written.

   However, since kernel 2.6.19, two new ioctls (VIDIOC_ENUM_FRAMEINTERVALS
   and VIDIOC_ENUM_FRAMESIZES) were added क्रम this purpose.

   The two functions below implement the newer ioctls
*/
अटल पूर्णांक vidioc_क्रमागत_framesizes(काष्ठा file *filp, व्योम *priv,
				  काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा go7007 *go = video_drvdata(filp);
	पूर्णांक width, height;

	अगर (fsize->index > 2)
		वापस -EINVAL;

	अगर (!valid_pixelक्रमmat(fsize->pixel_क्रमmat))
		वापस -EINVAL;

	get_resolution(go, &width, &height);
	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = (width >> fsize->index) & ~0xf;
	fsize->discrete.height = (height >> fsize->index) & ~0xf;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_frameपूर्णांकervals(काष्ठा file *filp, व्योम *priv,
				      काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा go7007 *go = video_drvdata(filp);
	पूर्णांक width, height;
	पूर्णांक i;

	अगर (fival->index > 4)
		वापस -EINVAL;

	अगर (!valid_pixelक्रमmat(fival->pixel_क्रमmat))
		वापस -EINVAL;

	अगर (!(go->board_info->sensor_flags & GO7007_SENSOR_SCALING)) अणु
		get_resolution(go, &width, &height);
		क्रम (i = 0; i <= 2; i++)
			अगर (fival->width == ((width >> i) & ~0xf) &&
			    fival->height == ((height >> i) & ~0xf))
				अवरोध;
		अगर (i > 2)
			वापस -EINVAL;
	पूर्ण
	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete.numerator = 1001 * (fival->index + 1);
	fival->discrete.denominator = go->sensor_framerate;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *std)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	*std = go->std;
	वापस 0;
पूर्ण

अटल पूर्णांक go7007_s_std(काष्ठा go7007 *go)
अणु
	अगर (go->std & V4L2_STD_625_50) अणु
		go->standard = GO7007_STD_PAL;
		go->sensor_framerate = 25025;
	पूर्ण अन्यथा अणु
		go->standard = GO7007_STD_NTSC;
		go->sensor_framerate = 30000;
	पूर्ण

	call_all(&go->v4l2_dev, video, s_std, go->std);
	set_capture_size(go, शून्य, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id std)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	अगर (vb2_is_busy(&go->vidq))
		वापस -EBUSY;

	go->std = std;

	वापस go7007_s_std(go);
पूर्ण

अटल पूर्णांक vidioc_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *std)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	वापस call_all(&go->v4l2_dev, video, querystd, std);
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_input *inp)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	अगर (inp->index >= go->board_info->num_inमाला_दो)
		वापस -EINVAL;

	strscpy(inp->name, go->board_info->inमाला_दो[inp->index].name,
		माप(inp->name));

	/* If this board has a tuner, it will be the first input */
	अगर ((go->board_info->flags & GO7007_BOARD_HAS_TUNER) &&
			inp->index == 0)
		inp->type = V4L2_INPUT_TYPE_TUNER;
	अन्यथा
		inp->type = V4L2_INPUT_TYPE_CAMERA;

	अगर (go->board_info->num_aud_inमाला_दो)
		inp->audioset = (1 << go->board_info->num_aud_inमाला_दो) - 1;
	अन्यथा
		inp->audioset = 0;
	inp->tuner = 0;
	अगर (go->board_info->sensor_flags & GO7007_SENSOR_TV)
		inp->std = video_devdata(file)->tvnorms;
	अन्यथा
		inp->std = 0;

	वापस 0;
पूर्ण


अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *input)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	*input = go->input;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागतaudio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *a)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	अगर (a->index >= go->board_info->num_aud_inमाला_दो)
		वापस -EINVAL;
	strscpy(a->name, go->board_info->aud_inमाला_दो[a->index].name,
		माप(a->name));
	a->capability = V4L2_AUDCAP_STEREO;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_audio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *a)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	a->index = go->aud_input;
	strscpy(a->name, go->board_info->aud_inमाला_दो[go->aud_input].name,
		माप(a->name));
	a->capability = V4L2_AUDCAP_STEREO;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_audio(काष्ठा file *file, व्योम *fh,
	स्थिर काष्ठा v4l2_audio *a)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	अगर (a->index >= go->board_info->num_aud_inमाला_दो)
		वापस -EINVAL;
	go->aud_input = a->index;
	v4l2_subdev_call(go->sd_audio, audio, s_routing,
		go->board_info->aud_inमाला_दो[go->aud_input].audio_input, 0, 0);
	वापस 0;
पूर्ण

अटल व्योम go7007_s_input(काष्ठा go7007 *go)
अणु
	अचिन्हित पूर्णांक input = go->input;

	v4l2_subdev_call(go->sd_video, video, s_routing,
			go->board_info->inमाला_दो[input].video_input, 0,
			go->board_info->video_config);
	अगर (go->board_info->num_aud_inमाला_दो) अणु
		पूर्णांक aud_input = go->board_info->inमाला_दो[input].audio_index;

		v4l2_subdev_call(go->sd_audio, audio, s_routing,
			go->board_info->aud_inमाला_दो[aud_input].audio_input, 0, 0);
		go->aud_input = aud_input;
	पूर्ण
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक input)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	अगर (input >= go->board_info->num_inमाला_दो)
		वापस -EINVAL;
	अगर (vb2_is_busy(&go->vidq))
		वापस -EBUSY;

	go->input = input;
	go7007_s_input(go);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_tuner *t)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	अगर (t->index != 0)
		वापस -EINVAL;

	strscpy(t->name, "Tuner", माप(t->name));
	वापस call_all(&go->v4l2_dev, tuner, g_tuner, t);
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	अगर (t->index != 0)
		वापस -EINVAL;

	वापस call_all(&go->v4l2_dev, tuner, s_tuner, t);
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *f)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	अगर (f->tuner)
		वापस -EINVAL;

	वापस call_all(&go->v4l2_dev, tuner, g_frequency, f);
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	अगर (f->tuner)
		वापस -EINVAL;

	वापस call_all(&go->v4l2_dev, tuner, s_frequency, f);
पूर्ण

अटल पूर्णांक vidioc_log_status(काष्ठा file *file, व्योम *priv)
अणु
	काष्ठा go7007 *go = video_drvdata(file);

	v4l2_ctrl_log_status(file, priv);
	वापस call_all(&go->v4l2_dev, core, log_status);
पूर्ण

अटल पूर्णांक vidioc_subscribe_event(काष्ठा v4l2_fh *fh,
				स्थिर काष्ठा v4l2_event_subscription *sub)
अणु

	चयन (sub->type) अणु
	हाल V4L2_EVENT_MOTION_DET:
		/* Allow क्रम up to 30 events (1 second क्रम NTSC) to be
		 * stored. */
		वापस v4l2_event_subscribe(fh, sub, 30, शून्य);
	शेष:
		वापस v4l2_ctrl_subscribe_event(fh, sub);
	पूर्ण
पूर्ण


अटल पूर्णांक go7007_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा go7007 *go =
		container_of(ctrl->handler, काष्ठा go7007, hdl);
	अचिन्हित y;
	u8 *mt;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_PIXEL_THRESHOLD0:
		go->modet[0].pixel_threshold = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MOTION_THRESHOLD0:
		go->modet[0].motion_threshold = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MB_THRESHOLD0:
		go->modet[0].mb_threshold = ctrl->val;
		अवरोध;
	हाल V4L2_CID_PIXEL_THRESHOLD1:
		go->modet[1].pixel_threshold = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MOTION_THRESHOLD1:
		go->modet[1].motion_threshold = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MB_THRESHOLD1:
		go->modet[1].mb_threshold = ctrl->val;
		अवरोध;
	हाल V4L2_CID_PIXEL_THRESHOLD2:
		go->modet[2].pixel_threshold = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MOTION_THRESHOLD2:
		go->modet[2].motion_threshold = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MB_THRESHOLD2:
		go->modet[2].mb_threshold = ctrl->val;
		अवरोध;
	हाल V4L2_CID_PIXEL_THRESHOLD3:
		go->modet[3].pixel_threshold = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MOTION_THRESHOLD3:
		go->modet[3].motion_threshold = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MB_THRESHOLD3:
		go->modet[3].mb_threshold = ctrl->val;
		अवरोध;
	हाल V4L2_CID_DETECT_MD_REGION_GRID:
		mt = go->modet_map;
		क्रम (y = 0; y < go->height / 16; y++, mt += go->width / 16)
			स_नकल(mt, ctrl->p_new.p_u8 + y * (720 / 16), go->width / 16);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations go7007_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= v4l2_fh_खोलो,
	.release	= vb2_fop_release,
	.unlocked_ioctl	= video_ioctl2,
	.पढ़ो		= vb2_fop_पढ़ो,
	.mmap		= vb2_fop_mmap,
	.poll		= vb2_fop_poll,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops video_ioctl_ops = अणु
	.vidioc_querycap          = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap  = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap   = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = vidioc_s_fmt_vid_cap,
	.vidioc_reqbufs           = vb2_ioctl_reqbufs,
	.vidioc_querybuf          = vb2_ioctl_querybuf,
	.vidioc_qbuf              = vb2_ioctl_qbuf,
	.vidioc_dqbuf             = vb2_ioctl_dqbuf,
	.vidioc_g_std             = vidioc_g_std,
	.vidioc_s_std             = vidioc_s_std,
	.vidioc_querystd          = vidioc_querystd,
	.vidioc_क्रमागत_input        = vidioc_क्रमागत_input,
	.vidioc_g_input           = vidioc_g_input,
	.vidioc_s_input           = vidioc_s_input,
	.vidioc_क्रमागतaudio         = vidioc_क्रमागतaudio,
	.vidioc_g_audio           = vidioc_g_audio,
	.vidioc_s_audio           = vidioc_s_audio,
	.vidioc_streamon          = vb2_ioctl_streamon,
	.vidioc_streamoff         = vb2_ioctl_streamoff,
	.vidioc_g_tuner           = vidioc_g_tuner,
	.vidioc_s_tuner           = vidioc_s_tuner,
	.vidioc_g_frequency       = vidioc_g_frequency,
	.vidioc_s_frequency       = vidioc_s_frequency,
	.vidioc_g_parm            = vidioc_g_parm,
	.vidioc_s_parm            = vidioc_s_parm,
	.vidioc_क्रमागत_framesizes   = vidioc_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals = vidioc_क्रमागत_frameपूर्णांकervals,
	.vidioc_log_status        = vidioc_log_status,
	.vidioc_subscribe_event   = vidioc_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा video_device go7007_ढाँचा = अणु
	.name		= "go7007",
	.fops		= &go7007_fops,
	.release	= video_device_release_empty,
	.ioctl_ops	= &video_ioctl_ops,
	.tvnorms	= V4L2_STD_ALL,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops go7007_ctrl_ops = अणु
	.s_ctrl = go7007_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config go7007_pixel_threshold0_ctrl = अणु
	.ops = &go7007_ctrl_ops,
	.id = V4L2_CID_PIXEL_THRESHOLD0,
	.name = "Pixel Threshold Region 0",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.def = 20,
	.max = 32767,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config go7007_motion_threshold0_ctrl = अणु
	.ops = &go7007_ctrl_ops,
	.id = V4L2_CID_MOTION_THRESHOLD0,
	.name = "Motion Threshold Region 0",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.def = 80,
	.max = 32767,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config go7007_mb_threshold0_ctrl = अणु
	.ops = &go7007_ctrl_ops,
	.id = V4L2_CID_MB_THRESHOLD0,
	.name = "MB Threshold Region 0",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.def = 200,
	.max = 32767,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config go7007_pixel_threshold1_ctrl = अणु
	.ops = &go7007_ctrl_ops,
	.id = V4L2_CID_PIXEL_THRESHOLD1,
	.name = "Pixel Threshold Region 1",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.def = 20,
	.max = 32767,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config go7007_motion_threshold1_ctrl = अणु
	.ops = &go7007_ctrl_ops,
	.id = V4L2_CID_MOTION_THRESHOLD1,
	.name = "Motion Threshold Region 1",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.def = 80,
	.max = 32767,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config go7007_mb_threshold1_ctrl = अणु
	.ops = &go7007_ctrl_ops,
	.id = V4L2_CID_MB_THRESHOLD1,
	.name = "MB Threshold Region 1",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.def = 200,
	.max = 32767,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config go7007_pixel_threshold2_ctrl = अणु
	.ops = &go7007_ctrl_ops,
	.id = V4L2_CID_PIXEL_THRESHOLD2,
	.name = "Pixel Threshold Region 2",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.def = 20,
	.max = 32767,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config go7007_motion_threshold2_ctrl = अणु
	.ops = &go7007_ctrl_ops,
	.id = V4L2_CID_MOTION_THRESHOLD2,
	.name = "Motion Threshold Region 2",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.def = 80,
	.max = 32767,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config go7007_mb_threshold2_ctrl = अणु
	.ops = &go7007_ctrl_ops,
	.id = V4L2_CID_MB_THRESHOLD2,
	.name = "MB Threshold Region 2",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.def = 200,
	.max = 32767,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config go7007_pixel_threshold3_ctrl = अणु
	.ops = &go7007_ctrl_ops,
	.id = V4L2_CID_PIXEL_THRESHOLD3,
	.name = "Pixel Threshold Region 3",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.def = 20,
	.max = 32767,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config go7007_motion_threshold3_ctrl = अणु
	.ops = &go7007_ctrl_ops,
	.id = V4L2_CID_MOTION_THRESHOLD3,
	.name = "Motion Threshold Region 3",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.def = 80,
	.max = 32767,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config go7007_mb_threshold3_ctrl = अणु
	.ops = &go7007_ctrl_ops,
	.id = V4L2_CID_MB_THRESHOLD3,
	.name = "MB Threshold Region 3",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.def = 200,
	.max = 32767,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config go7007_mb_regions_ctrl = अणु
	.ops = &go7007_ctrl_ops,
	.id = V4L2_CID_DETECT_MD_REGION_GRID,
	.dims = अणु 576 / 16, 720 / 16 पूर्ण,
	.max = 3,
	.step = 1,
पूर्ण;

पूर्णांक go7007_v4l2_ctrl_init(काष्ठा go7007 *go)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &go->hdl;
	काष्ठा v4l2_ctrl *ctrl;

	v4l2_ctrl_handler_init(hdl, 22);
	go->mpeg_video_gop_size = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_MPEG_VIDEO_GOP_SIZE, 0, 34, 1, 15);
	go->mpeg_video_gop_closure = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_MPEG_VIDEO_GOP_CLOSURE, 0, 1, 1, 1);
	go->mpeg_video_bitrate = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_MPEG_VIDEO_BITRATE,
			64000, 10000000, 1, 9800000);
	go->mpeg_video_b_frames = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_MPEG_VIDEO_B_FRAMES, 0, 2, 2, 0);
	go->mpeg_video_rep_seqheader = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_MPEG_VIDEO_REPEAT_SEQ_HEADER, 0, 1, 1, 1);

	go->mpeg_video_aspect_ratio = v4l2_ctrl_new_std_menu(hdl, शून्य,
			V4L2_CID_MPEG_VIDEO_ASPECT,
			V4L2_MPEG_VIDEO_ASPECT_16x9, 0,
			V4L2_MPEG_VIDEO_ASPECT_1x1);
	ctrl = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_JPEG_ACTIVE_MARKER, 0,
			V4L2_JPEG_ACTIVE_MARKER_DQT |
			V4L2_JPEG_ACTIVE_MARKER_DHT, 0,
			V4L2_JPEG_ACTIVE_MARKER_DQT |
			V4L2_JPEG_ACTIVE_MARKER_DHT);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;
	v4l2_ctrl_new_custom(hdl, &go7007_pixel_threshold0_ctrl, शून्य);
	v4l2_ctrl_new_custom(hdl, &go7007_motion_threshold0_ctrl, शून्य);
	v4l2_ctrl_new_custom(hdl, &go7007_mb_threshold0_ctrl, शून्य);
	v4l2_ctrl_new_custom(hdl, &go7007_pixel_threshold1_ctrl, शून्य);
	v4l2_ctrl_new_custom(hdl, &go7007_motion_threshold1_ctrl, शून्य);
	v4l2_ctrl_new_custom(hdl, &go7007_mb_threshold1_ctrl, शून्य);
	v4l2_ctrl_new_custom(hdl, &go7007_pixel_threshold2_ctrl, शून्य);
	v4l2_ctrl_new_custom(hdl, &go7007_motion_threshold2_ctrl, शून्य);
	v4l2_ctrl_new_custom(hdl, &go7007_mb_threshold2_ctrl, शून्य);
	v4l2_ctrl_new_custom(hdl, &go7007_pixel_threshold3_ctrl, शून्य);
	v4l2_ctrl_new_custom(hdl, &go7007_motion_threshold3_ctrl, शून्य);
	v4l2_ctrl_new_custom(hdl, &go7007_mb_threshold3_ctrl, शून्य);
	v4l2_ctrl_new_custom(hdl, &go7007_mb_regions_ctrl, शून्य);
	go->modet_mode = v4l2_ctrl_new_std_menu(hdl, शून्य,
			V4L2_CID_DETECT_MD_MODE,
			V4L2_DETECT_MD_MODE_REGION_GRID,
			1 << V4L2_DETECT_MD_MODE_THRESHOLD_GRID,
			V4L2_DETECT_MD_MODE_DISABLED);
	अगर (hdl->error) अणु
		पूर्णांक rv = hdl->error;

		v4l2_err(&go->v4l2_dev, "Could not register controls\n");
		वापस rv;
	पूर्ण
	go->v4l2_dev.ctrl_handler = hdl;
	वापस 0;
पूर्ण

पूर्णांक go7007_v4l2_init(काष्ठा go7007 *go)
अणु
	काष्ठा video_device *vdev = &go->vdev;
	पूर्णांक rv;

	mutex_init(&go->serialize_lock);
	mutex_init(&go->queue_lock);

	INIT_LIST_HEAD(&go->vidq_active);
	go->vidq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	go->vidq.io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ;
	go->vidq.ops = &go7007_video_qops;
	go->vidq.mem_ops = &vb2_vदो_स्मृति_memops;
	go->vidq.drv_priv = go;
	go->vidq.buf_काष्ठा_size = माप(काष्ठा go7007_buffer);
	go->vidq.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	go->vidq.lock = &go->queue_lock;
	rv = vb2_queue_init(&go->vidq);
	अगर (rv)
		वापस rv;
	*vdev = go7007_ढाँचा;
	vdev->lock = &go->serialize_lock;
	vdev->queue = &go->vidq;
	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
			    V4L2_CAP_STREAMING;
	अगर (go->board_info->num_aud_inमाला_दो)
		vdev->device_caps |= V4L2_CAP_AUDIO;
	अगर (go->board_info->flags & GO7007_BOARD_HAS_TUNER)
		vdev->device_caps |= V4L2_CAP_TUNER;
	video_set_drvdata(vdev, go);
	vdev->v4l2_dev = &go->v4l2_dev;
	अगर (!v4l2_device_has_op(&go->v4l2_dev, 0, video, querystd))
		v4l2_disable_ioctl(vdev, VIDIOC_QUERYSTD);
	अगर (!(go->board_info->flags & GO7007_BOARD_HAS_TUNER)) अणु
		v4l2_disable_ioctl(vdev, VIDIOC_S_FREQUENCY);
		v4l2_disable_ioctl(vdev, VIDIOC_G_FREQUENCY);
		v4l2_disable_ioctl(vdev, VIDIOC_S_TUNER);
		v4l2_disable_ioctl(vdev, VIDIOC_G_TUNER);
	पूर्ण अन्यथा अणु
		काष्ठा v4l2_frequency f = अणु
			.type = V4L2_TUNER_ANALOG_TV,
			.frequency = 980,
		पूर्ण;

		call_all(&go->v4l2_dev, tuner, s_frequency, &f);
	पूर्ण
	अगर (!(go->board_info->sensor_flags & GO7007_SENSOR_TV)) अणु
		v4l2_disable_ioctl(vdev, VIDIOC_G_STD);
		v4l2_disable_ioctl(vdev, VIDIOC_S_STD);
		vdev->tvnorms = 0;
	पूर्ण
	अगर (go->board_info->sensor_flags & GO7007_SENSOR_SCALING)
		v4l2_disable_ioctl(vdev, VIDIOC_ENUM_FRAMESIZES);
	अगर (go->board_info->num_aud_inमाला_दो == 0) अणु
		v4l2_disable_ioctl(vdev, VIDIOC_G_AUDIO);
		v4l2_disable_ioctl(vdev, VIDIOC_S_AUDIO);
		v4l2_disable_ioctl(vdev, VIDIOC_ENUMAUDIO);
	पूर्ण
	/* Setup correct crystal frequency on this board */
	अगर (go->board_info->sensor_flags & GO7007_SENSOR_SAA7115)
		v4l2_subdev_call(go->sd_video, video, s_crystal_freq,
				SAA7115_FREQ_24_576_MHZ,
				SAA7115_FREQ_FL_APLL | SAA7115_FREQ_FL_UCGC |
				SAA7115_FREQ_FL_DOUBLE_ASCLK);
	go7007_s_input(go);
	अगर (go->board_info->sensor_flags & GO7007_SENSOR_TV)
		go7007_s_std(go);
	rv = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (rv < 0)
		वापस rv;
	dev_info(go->dev, "registered device %s [v4l2]\n",
		 video_device_node_name(vdev));

	वापस 0;
पूर्ण

व्योम go7007_v4l2_हटाओ(काष्ठा go7007 *go)
अणु
	v4l2_ctrl_handler_मुक्त(&go->hdl);
पूर्ण
