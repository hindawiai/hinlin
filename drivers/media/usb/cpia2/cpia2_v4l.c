<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/****************************************************************************
 *
 *  Filename: cpia2_v4l.c
 *
 *  Copyright 2001, STMicrolectronics, Inc.
 *      Contact:  steve.miller@st.com
 *  Copyright 2001,2005, Scott J. Bertin <scottbertin@yahoo.com>
 *
 *  Description:
 *     This is a USB driver क्रम CPia2 based video cameras.
 *     The infraकाष्ठाure of this driver is based on the cpia usb driver by
 *     Jochen Sअक्षरrlach and Johannes Erdfeldt.
 *
 *  Stripped of 2.4 stuff पढ़ोy क्रम मुख्य kernel submit by
 *		Alan Cox <alan@lxorguk.ukuu.org.uk>
 ****************************************************************************/

#घोषणा CPIA_VERSION "3.0.1"

#समावेश <linux/module.h>
#समावेश <linux/समय.स>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/stringअगरy.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>

#समावेश "cpia2.h"

अटल पूर्णांक video_nr = -1;
module_param(video_nr, पूर्णांक, 0);
MODULE_PARM_DESC(video_nr, "video device to register (0=/dev/video0, etc)");

अटल पूर्णांक buffer_size = 68 * 1024;
module_param(buffer_size, पूर्णांक, 0);
MODULE_PARM_DESC(buffer_size, "Size for each frame buffer in bytes (default 68k)");

अटल पूर्णांक num_buffers = 3;
module_param(num_buffers, पूर्णांक, 0);
MODULE_PARM_DESC(num_buffers, "Number of frame buffers (1-"
		 __stringअगरy(VIDEO_MAX_FRAME) ", default 3)");

अटल पूर्णांक alternate = DEFAULT_ALT;
module_param(alternate, पूर्णांक, 0);
MODULE_PARM_DESC(alternate, "USB Alternate (" __stringअगरy(USBIF_ISO_1) "-"
		 __stringअगरy(USBIF_ISO_6) ", default "
		 __stringअगरy(DEFAULT_ALT) ")");

अटल पूर्णांक flicker_mode;
module_param(flicker_mode, पूर्णांक, 0);
MODULE_PARM_DESC(flicker_mode, "Flicker frequency (0 (disabled), " __stringअगरy(50) " or "
		 __stringअगरy(60) ", default 0)");

MODULE_AUTHOR("Steve Miller (STMicroelectronics) <steve.miller@st.com>");
MODULE_DESCRIPTION("V4L-driver for STMicroelectronics CPiA2 based cameras");
MODULE_LICENSE("GPL");
MODULE_VERSION(CPIA_VERSION);

#घोषणा ABOUT "V4L-Driver for Vision CPiA2 based cameras"
#घोषणा CPIA2_CID_USB_ALT (V4L2_CID_USER_BASE | 0xf000)

/******************************************************************************
 *
 *  cpia2_खोलो
 *
 *****************************************************************************/
अटल पूर्णांक cpia2_खोलो(काष्ठा file *file)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);
	पूर्णांक retval;

	अगर (mutex_lock_पूर्णांकerruptible(&cam->v4l2_lock))
		वापस -ERESTARTSYS;
	retval = v4l2_fh_खोलो(file);
	अगर (retval)
		जाओ खोलो_unlock;

	अगर (v4l2_fh_is_singular_file(file)) अणु
		अगर (cpia2_allocate_buffers(cam)) अणु
			v4l2_fh_release(file);
			retval = -ENOMEM;
			जाओ खोलो_unlock;
		पूर्ण

		/* reset the camera */
		अगर (cpia2_reset_camera(cam) < 0) अणु
			v4l2_fh_release(file);
			retval = -EIO;
			जाओ खोलो_unlock;
		पूर्ण

		cam->APP_len = 0;
		cam->COM_len = 0;
	पूर्ण

	cpia2_dbg_dump_रेजिस्टरs(cam);
खोलो_unlock:
	mutex_unlock(&cam->v4l2_lock);
	वापस retval;
पूर्ण

/******************************************************************************
 *
 *  cpia2_बंद
 *
 *****************************************************************************/
अटल पूर्णांक cpia2_बंद(काष्ठा file *file)
अणु
	काष्ठा video_device *dev = video_devdata(file);
	काष्ठा camera_data *cam = video_get_drvdata(dev);

	mutex_lock(&cam->v4l2_lock);
	अगर (video_is_रेजिस्टरed(&cam->vdev) && v4l2_fh_is_singular_file(file)) अणु
		cpia2_usb_stream_stop(cam);

		/* save camera state क्रम later खोलो */
		cpia2_save_camera_state(cam);

		cpia2_set_low_घातer(cam);
		cpia2_मुक्त_buffers(cam);
	पूर्ण

	अगर (cam->stream_fh == file->निजी_data) अणु
		cam->stream_fh = शून्य;
		cam->mmapped = 0;
	पूर्ण
	mutex_unlock(&cam->v4l2_lock);
	वापस v4l2_fh_release(file);
पूर्ण

/******************************************************************************
 *
 *  cpia2_v4l_पढ़ो
 *
 *****************************************************************************/
अटल sमाप_प्रकार cpia2_v4l_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			      loff_t *off)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);
	पूर्णांक noblock = file->f_flags&O_NONBLOCK;
	sमाप_प्रकार ret;

	अगर(!cam)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&cam->v4l2_lock))
		वापस -ERESTARTSYS;
	ret = cpia2_पढ़ो(cam, buf, count, noblock);
	mutex_unlock(&cam->v4l2_lock);
	वापस ret;
पूर्ण


/******************************************************************************
 *
 *  cpia2_v4l_poll
 *
 *****************************************************************************/
अटल __poll_t cpia2_v4l_poll(काष्ठा file *filp, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा camera_data *cam = video_drvdata(filp);
	__poll_t res;

	mutex_lock(&cam->v4l2_lock);
	res = cpia2_poll(cam, filp, रुको);
	mutex_unlock(&cam->v4l2_lock);
	वापस res;
पूर्ण


अटल पूर्णांक sync(काष्ठा camera_data *cam, पूर्णांक frame_nr)
अणु
	काष्ठा framebuf *frame = &cam->buffers[frame_nr];

	जबतक (1) अणु
		अगर (frame->status == FRAME_READY)
			वापस 0;

		अगर (!cam->streaming) अणु
			frame->status = FRAME_READY;
			frame->length = 0;
			वापस 0;
		पूर्ण

		mutex_unlock(&cam->v4l2_lock);
		रुको_event_पूर्णांकerruptible(cam->wq_stream,
					 !cam->streaming ||
					 frame->status == FRAME_READY);
		mutex_lock(&cam->v4l2_lock);
		अगर (संकेत_pending(current))
			वापस -ERESTARTSYS;
		अगर (!video_is_रेजिस्टरed(&cam->vdev))
			वापस -ENOTTY;
	पूर्ण
पूर्ण

/******************************************************************************
 *
 *  ioctl_querycap
 *
 *  V4L2 device capabilities
 *
 *****************************************************************************/

अटल पूर्णांक cpia2_querycap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_capability *vc)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);

	strscpy(vc->driver, "cpia2", माप(vc->driver));

	अगर (cam->params.pnp_id.product == 0x151)
		strscpy(vc->card, "QX5 Microscope", माप(vc->card));
	अन्यथा
		strscpy(vc->card, "CPiA2 Camera", माप(vc->card));
	चयन (cam->params.pnp_id.device_type) अणु
	हाल DEVICE_STV_672:
		म_जोड़ो(vc->card, " (672/");
		अवरोध;
	हाल DEVICE_STV_676:
		म_जोड़ो(vc->card, " (676/");
		अवरोध;
	शेष:
		म_जोड़ो(vc->card, " (XXX/");
		अवरोध;
	पूर्ण
	चयन (cam->params.version.sensor_flags) अणु
	हाल CPIA2_VP_SENSOR_FLAGS_404:
		म_जोड़ो(vc->card, "404)");
		अवरोध;
	हाल CPIA2_VP_SENSOR_FLAGS_407:
		म_जोड़ो(vc->card, "407)");
		अवरोध;
	हाल CPIA2_VP_SENSOR_FLAGS_409:
		म_जोड़ो(vc->card, "409)");
		अवरोध;
	हाल CPIA2_VP_SENSOR_FLAGS_410:
		म_जोड़ो(vc->card, "410)");
		अवरोध;
	हाल CPIA2_VP_SENSOR_FLAGS_500:
		म_जोड़ो(vc->card, "500)");
		अवरोध;
	शेष:
		म_जोड़ो(vc->card, "XXX)");
		अवरोध;
	पूर्ण

	अगर (usb_make_path(cam->dev, vc->bus_info, माप(vc->bus_info)) <0)
		स_रखो(vc->bus_info,0, माप(vc->bus_info));
	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  ioctl_input
 *
 *  V4L2 input get/set/क्रमागतerate
 *
 *****************************************************************************/

अटल पूर्णांक cpia2_क्रमागत_input(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_input *i)
अणु
	अगर (i->index)
		वापस -EINVAL;
	strscpy(i->name, "Camera", माप(i->name));
	i->type = V4L2_INPUT_TYPE_CAMERA;
	वापस 0;
पूर्ण

अटल पूर्णांक cpia2_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक cpia2_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक i)
अणु
	वापस i ? -EINVAL : 0;
पूर्ण

/******************************************************************************
 *
 *  ioctl_क्रमागत_fmt
 *
 *  V4L2 क्रमmat क्रमागतerate
 *
 *****************************************************************************/

अटल पूर्णांक cpia2_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
					    काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index > 1)
		वापस -EINVAL;

	अगर (f->index == 0)
		f->pixelक्रमmat = V4L2_PIX_FMT_MJPEG;
	अन्यथा
		f->pixelक्रमmat = V4L2_PIX_FMT_JPEG;
	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  ioctl_try_fmt
 *
 *  V4L2 क्रमmat try
 *
 *****************************************************************************/

अटल पूर्णांक cpia2_try_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
					  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);

	अगर (f->fmt.pix.pixelक्रमmat != V4L2_PIX_FMT_MJPEG &&
	    f->fmt.pix.pixelक्रमmat != V4L2_PIX_FMT_JPEG)
	       वापस -EINVAL;

	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage = cam->frame_size;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_JPEG;

	चयन (cpia2_match_video_size(f->fmt.pix.width, f->fmt.pix.height)) अणु
	हाल VIDEOSIZE_VGA:
		f->fmt.pix.width = 640;
		f->fmt.pix.height = 480;
		अवरोध;
	हाल VIDEOSIZE_CIF:
		f->fmt.pix.width = 352;
		f->fmt.pix.height = 288;
		अवरोध;
	हाल VIDEOSIZE_QVGA:
		f->fmt.pix.width = 320;
		f->fmt.pix.height = 240;
		अवरोध;
	हाल VIDEOSIZE_288_216:
		f->fmt.pix.width = 288;
		f->fmt.pix.height = 216;
		अवरोध;
	हाल VIDEOSIZE_256_192:
		f->fmt.pix.width = 256;
		f->fmt.pix.height = 192;
		अवरोध;
	हाल VIDEOSIZE_224_168:
		f->fmt.pix.width = 224;
		f->fmt.pix.height = 168;
		अवरोध;
	हाल VIDEOSIZE_192_144:
		f->fmt.pix.width = 192;
		f->fmt.pix.height = 144;
		अवरोध;
	हाल VIDEOSIZE_QCIF:
	शेष:
		f->fmt.pix.width = 176;
		f->fmt.pix.height = 144;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  ioctl_set_fmt
 *
 *  V4L2 क्रमmat set
 *
 *****************************************************************************/

अटल पूर्णांक cpia2_s_fmt_vid_cap(काष्ठा file *file, व्योम *_fh,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);
	पूर्णांक err, frame;

	err = cpia2_try_fmt_vid_cap(file, _fh, f);
	अगर(err != 0)
		वापस err;

	cam->pixelक्रमmat = f->fmt.pix.pixelक्रमmat;

	/* NOTE: This should be set to 1 क्रम MJPEG, but some apps करोn't handle
	 * the missing Huffman table properly. */
	cam->params.compression.inhibit_htables = 0;
		/*f->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_MJPEG;*/

	/* we set the video winकरोw to something smaller or equal to what
	 * is requested by the user???
	 */
	DBG("Requested width = %d, height = %d\n",
	    f->fmt.pix.width, f->fmt.pix.height);
	अगर (f->fmt.pix.width != cam->width ||
	    f->fmt.pix.height != cam->height) अणु
		cam->width = f->fmt.pix.width;
		cam->height = f->fmt.pix.height;
		cam->params.roi.width = f->fmt.pix.width;
		cam->params.roi.height = f->fmt.pix.height;
		cpia2_set_क्रमmat(cam);
	पूर्ण

	क्रम (frame = 0; frame < cam->num_frames; ++frame) अणु
		अगर (cam->buffers[frame].status == FRAME_READING)
			अगर ((err = sync(cam, frame)) < 0)
				वापस err;

		cam->buffers[frame].status = FRAME_EMPTY;
	पूर्ण

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  ioctl_get_fmt
 *
 *  V4L2 क्रमmat get
 *
 *****************************************************************************/

अटल पूर्णांक cpia2_g_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);

	f->fmt.pix.width = cam->width;
	f->fmt.pix.height = cam->height;
	f->fmt.pix.pixelक्रमmat = cam->pixelक्रमmat;
	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage = cam->frame_size;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_JPEG;

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  ioctl_cropcap
 *
 *  V4L2 query cropping capabilities
 *  NOTE: cropping is currently disabled
 *
 *****************************************************************************/

अटल पूर्णांक cpia2_g_selection(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_selection *s)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = cam->width;
		s->r.height = cam->height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा framerate_info अणु
	पूर्णांक value;
	काष्ठा v4l2_fract period;
पूर्ण;

अटल स्थिर काष्ठा framerate_info framerate_controls[] = अणु
	अणु CPIA2_VP_FRAMERATE_6_25, अणु 4, 25 पूर्ण पूर्ण,
	अणु CPIA2_VP_FRAMERATE_7_5,  अणु 2, 15 पूर्ण पूर्ण,
	अणु CPIA2_VP_FRAMERATE_12_5, अणु 2, 25 पूर्ण पूर्ण,
	अणु CPIA2_VP_FRAMERATE_15,   अणु 1, 15 पूर्ण पूर्ण,
	अणु CPIA2_VP_FRAMERATE_25,   अणु 1, 25 पूर्ण पूर्ण,
	अणु CPIA2_VP_FRAMERATE_30,   अणु 1, 30 पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक cpia2_g_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *p)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);
	काष्ठा v4l2_captureparm *cap = &p->parm.capture;
	पूर्णांक i;

	अगर (p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	cap->capability = V4L2_CAP_TIMEPERFRAME;
	cap->पढ़ोbuffers = cam->num_frames;
	क्रम (i = 0; i < ARRAY_SIZE(framerate_controls); i++)
		अगर (cam->params.vp_params.frame_rate == framerate_controls[i].value) अणु
			cap->समयperframe = framerate_controls[i].period;
			अवरोध;
		पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cpia2_s_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *p)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);
	काष्ठा v4l2_captureparm *cap = &p->parm.capture;
	काष्ठा v4l2_fract tpf = cap->समयperframe;
	पूर्णांक max = ARRAY_SIZE(framerate_controls) - 1;
	पूर्णांक ret;
	पूर्णांक i;

	ret = cpia2_g_parm(file, fh, p);
	अगर (ret || !tpf.denominator || !tpf.numerator)
		वापस ret;

	/* Maximum 15 fps क्रम this model */
	अगर (cam->params.pnp_id.device_type == DEVICE_STV_672 &&
	    cam->params.version.sensor_flags == CPIA2_VP_SENSOR_FLAGS_500)
		max -= 2;
	क्रम (i = 0; i <= max; i++) अणु
		काष्ठा v4l2_fract f1 = tpf;
		काष्ठा v4l2_fract f2 = framerate_controls[i].period;

		f1.numerator *= f2.denominator;
		f2.numerator *= f1.denominator;
		अगर (f1.numerator >= f2.numerator)
			अवरोध;
	पूर्ण
	अगर (i > max)
		i = max;
	cap->समयperframe = framerate_controls[i].period;
	वापस cpia2_set_fps(cam, framerate_controls[i].value);
पूर्ण

अटल स्थिर काष्ठा अणु
	u32 width;
	u32 height;
पूर्ण cpia2_framesizes[] = अणु
	अणु 640, 480 पूर्ण,
	अणु 352, 288 पूर्ण,
	अणु 320, 240 पूर्ण,
	अणु 288, 216 पूर्ण,
	अणु 256, 192 पूर्ण,
	अणु 224, 168 पूर्ण,
	अणु 192, 144 पूर्ण,
	अणु 176, 144 पूर्ण,
पूर्ण;

अटल पूर्णांक cpia2_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
					 काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु

	अगर (fsize->pixel_क्रमmat != V4L2_PIX_FMT_MJPEG &&
	    fsize->pixel_क्रमmat != V4L2_PIX_FMT_JPEG)
		वापस -EINVAL;
	अगर (fsize->index >= ARRAY_SIZE(cpia2_framesizes))
		वापस -EINVAL;
	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = cpia2_framesizes[fsize->index].width;
	fsize->discrete.height = cpia2_framesizes[fsize->index].height;

	वापस 0;
पूर्ण

अटल पूर्णांक cpia2_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *fh,
					   काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);
	पूर्णांक max = ARRAY_SIZE(framerate_controls) - 1;
	पूर्णांक i;

	अगर (fival->pixel_क्रमmat != V4L2_PIX_FMT_MJPEG &&
	    fival->pixel_क्रमmat != V4L2_PIX_FMT_JPEG)
		वापस -EINVAL;

	/* Maximum 15 fps क्रम this model */
	अगर (cam->params.pnp_id.device_type == DEVICE_STV_672 &&
	    cam->params.version.sensor_flags == CPIA2_VP_SENSOR_FLAGS_500)
		max -= 2;
	अगर (fival->index > max)
		वापस -EINVAL;
	क्रम (i = 0; i < ARRAY_SIZE(cpia2_framesizes); i++)
		अगर (fival->width == cpia2_framesizes[i].width &&
		    fival->height == cpia2_framesizes[i].height)
			अवरोध;
	अगर (i == ARRAY_SIZE(cpia2_framesizes))
		वापस -EINVAL;
	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = framerate_controls[fival->index].period;
	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  ioctl_s_ctrl
 *
 *  V4L2 set the value of a control variable
 *
 *****************************************************************************/

अटल पूर्णांक cpia2_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा camera_data *cam =
		container_of(ctrl->handler, काष्ठा camera_data, hdl);
	अटल स्थिर पूर्णांक flicker_table[] = अणु
		NEVER_FLICKER,
		FLICKER_50,
		FLICKER_60,
	पूर्ण;

	DBG("Set control id:%d, value:%d\n", ctrl->id, ctrl->val);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		cpia2_set_brightness(cam, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		cpia2_set_contrast(cam, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		cpia2_set_saturation(cam, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		cpia2_set_property_mirror(cam, ctrl->val);
		अवरोध;
	हाल V4L2_CID_VFLIP:
		cpia2_set_property_flip(cam, ctrl->val);
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		वापस cpia2_set_flicker_mode(cam, flicker_table[ctrl->val]);
	हाल V4L2_CID_ILLUMINATORS_1:
		वापस cpia2_set_gpio(cam, (cam->top_light->val << 6) |
					   (cam->bottom_light->val << 7));
	हाल V4L2_CID_JPEG_ACTIVE_MARKER:
		cam->params.compression.inhibit_htables =
			!(ctrl->val & V4L2_JPEG_ACTIVE_MARKER_DHT);
		अवरोध;
	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:
		cam->params.vc_params.quality = ctrl->val;
		अवरोध;
	हाल CPIA2_CID_USB_ALT:
		cam->params.camera_state.stream_mode = ctrl->val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  ioctl_g_jpegcomp
 *
 *  V4L2 get the JPEG compression parameters
 *
 *****************************************************************************/

अटल पूर्णांक cpia2_g_jpegcomp(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_jpegcompression *parms)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);

	स_रखो(parms, 0, माप(*parms));

	parms->quality = 80; // TODO: Can this be made meaningful?

	parms->jpeg_markers = V4L2_JPEG_MARKER_DQT | V4L2_JPEG_MARKER_DRI;
	अगर(!cam->params.compression.inhibit_htables) अणु
		parms->jpeg_markers |= V4L2_JPEG_MARKER_DHT;
	पूर्ण

	parms->APPn = cam->APPn;
	parms->APP_len = cam->APP_len;
	अगर(cam->APP_len > 0) अणु
		स_नकल(parms->APP_data, cam->APP_data, cam->APP_len);
		parms->jpeg_markers |= V4L2_JPEG_MARKER_APP;
	पूर्ण

	parms->COM_len = cam->COM_len;
	अगर(cam->COM_len > 0) अणु
		स_नकल(parms->COM_data, cam->COM_data, cam->COM_len);
		parms->jpeg_markers |= JPEG_MARKER_COM;
	पूर्ण

	DBG("G_JPEGCOMP APP_len:%d COM_len:%d\n",
	    parms->APP_len, parms->COM_len);

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  ioctl_s_jpegcomp
 *
 *  V4L2 set the JPEG compression parameters
 *  NOTE: quality and some jpeg_markers are ignored.
 *
 *****************************************************************************/

अटल पूर्णांक cpia2_s_jpegcomp(काष्ठा file *file, व्योम *fh,
		स्थिर काष्ठा v4l2_jpegcompression *parms)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);

	DBG("S_JPEGCOMP APP_len:%d COM_len:%d\n",
	    parms->APP_len, parms->COM_len);

	cam->params.compression.inhibit_htables =
		!(parms->jpeg_markers & V4L2_JPEG_MARKER_DHT);

	अगर(parms->APP_len != 0) अणु
		अगर(parms->APP_len > 0 &&
		   parms->APP_len <= माप(cam->APP_data) &&
		   parms->APPn >= 0 && parms->APPn <= 15) अणु
			cam->APPn = parms->APPn;
			cam->APP_len = parms->APP_len;
			स_नकल(cam->APP_data, parms->APP_data, parms->APP_len);
		पूर्ण अन्यथा अणु
			LOG("Bad APPn Params n=%d len=%d\n",
			    parms->APPn, parms->APP_len);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		cam->APP_len = 0;
	पूर्ण

	अगर(parms->COM_len != 0) अणु
		अगर(parms->COM_len > 0 &&
		   parms->COM_len <= माप(cam->COM_data)) अणु
			cam->COM_len = parms->COM_len;
			स_नकल(cam->COM_data, parms->COM_data, parms->COM_len);
		पूर्ण अन्यथा अणु
			LOG("Bad COM_len=%d\n", parms->COM_len);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  ioctl_reqbufs
 *
 *  V4L2 Initiate memory mapping.
 *  NOTE: The user's request is ignored. For now the buffers are fixed.
 *
 *****************************************************************************/

अटल पूर्णांक cpia2_reqbufs(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_requestbuffers *req)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);

	अगर(req->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	   req->memory != V4L2_MEMORY_MMAP)
		वापस -EINVAL;

	DBG("REQBUFS requested:%d returning:%d\n", req->count, cam->num_frames);
	req->count = cam->num_frames;
	स_रखो(&req->reserved, 0, माप(req->reserved));

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  ioctl_querybuf
 *
 *  V4L2 Query memory buffer status.
 *
 *****************************************************************************/

अटल पूर्णांक cpia2_querybuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);

	अगर(buf->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	   buf->index >= cam->num_frames)
		वापस -EINVAL;

	buf->m.offset = cam->buffers[buf->index].data - cam->frame_buffer;
	buf->length = cam->frame_size;

	buf->memory = V4L2_MEMORY_MMAP;

	अगर(cam->mmapped)
		buf->flags = V4L2_BUF_FLAG_MAPPED;
	अन्यथा
		buf->flags = 0;

	buf->flags |= V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;

	चयन (cam->buffers[buf->index].status) अणु
	हाल FRAME_EMPTY:
	हाल FRAME_ERROR:
	हाल FRAME_READING:
		buf->bytesused = 0;
		buf->flags = V4L2_BUF_FLAG_QUEUED;
		अवरोध;
	हाल FRAME_READY:
		buf->bytesused = cam->buffers[buf->index].length;
		v4l2_buffer_set_बारtamp(buf, cam->buffers[buf->index].ts);
		buf->sequence = cam->buffers[buf->index].seq;
		buf->flags = V4L2_BUF_FLAG_DONE;
		अवरोध;
	पूर्ण

	DBG("QUERYBUF index:%d offset:%d flags:%d seq:%d bytesused:%d\n",
	     buf->index, buf->m.offset, buf->flags, buf->sequence,
	     buf->bytesused);

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  ioctl_qbuf
 *
 *  V4L2 User is मुक्तing buffer
 *
 *****************************************************************************/

अटल पूर्णांक cpia2_qbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);

	अगर(buf->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	   buf->memory != V4L2_MEMORY_MMAP ||
	   buf->index >= cam->num_frames)
		वापस -EINVAL;

	DBG("QBUF #%d\n", buf->index);

	अगर(cam->buffers[buf->index].status == FRAME_READY)
		cam->buffers[buf->index].status = FRAME_EMPTY;

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  find_earliest_filled_buffer
 *
 *  Helper क्रम ioctl_dqbuf. Find the next पढ़ोy buffer.
 *
 *****************************************************************************/

अटल पूर्णांक find_earliest_filled_buffer(काष्ठा camera_data *cam)
अणु
	पूर्णांक i;
	पूर्णांक found = -1;
	क्रम (i=0; i<cam->num_frames; i++) अणु
		अगर(cam->buffers[i].status == FRAME_READY) अणु
			अगर(found < 0) अणु
				found = i;
			पूर्ण अन्यथा अणु
				/* find which buffer is earlier */
				अगर (cam->buffers[i].ts < cam->buffers[found].ts)
					found = i;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस found;
पूर्ण

/******************************************************************************
 *
 *  ioctl_dqbuf
 *
 *  V4L2 User is asking क्रम a filled buffer.
 *
 *****************************************************************************/

अटल पूर्णांक cpia2_dqbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);
	पूर्णांक frame;

	अगर(buf->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	   buf->memory != V4L2_MEMORY_MMAP)
		वापस -EINVAL;

	frame = find_earliest_filled_buffer(cam);

	अगर(frame < 0 && file->f_flags&O_NONBLOCK)
		वापस -EAGAIN;

	अगर(frame < 0) अणु
		/* Wait क्रम a frame to become available */
		काष्ठा framebuf *cb=cam->curbuff;
		mutex_unlock(&cam->v4l2_lock);
		रुको_event_पूर्णांकerruptible(cam->wq_stream,
					 !video_is_रेजिस्टरed(&cam->vdev) ||
					 (cb=cam->curbuff)->status == FRAME_READY);
		mutex_lock(&cam->v4l2_lock);
		अगर (संकेत_pending(current))
			वापस -ERESTARTSYS;
		अगर (!video_is_रेजिस्टरed(&cam->vdev))
			वापस -ENOTTY;
		frame = cb->num;
	पूर्ण


	buf->index = frame;
	buf->bytesused = cam->buffers[buf->index].length;
	buf->flags = V4L2_BUF_FLAG_MAPPED | V4L2_BUF_FLAG_DONE
		| V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	buf->field = V4L2_FIELD_NONE;
	v4l2_buffer_set_बारtamp(buf, cam->buffers[buf->index].ts);
	buf->sequence = cam->buffers[buf->index].seq;
	buf->m.offset = cam->buffers[buf->index].data - cam->frame_buffer;
	buf->length = cam->frame_size;
	buf->reserved2 = 0;
	buf->request_fd = 0;
	स_रखो(&buf->समयcode, 0, माप(buf->समयcode));

	DBG("DQBUF #%d status:%d seq:%d length:%d\n", buf->index,
	    cam->buffers[buf->index].status, buf->sequence, buf->bytesused);

	वापस 0;
पूर्ण

अटल पूर्णांक cpia2_streamon(काष्ठा file *file, व्योम *fh, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);
	पूर्णांक ret = -EINVAL;

	DBG("VIDIOC_STREAMON, streaming=%d\n", cam->streaming);
	अगर (!cam->mmapped || type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (!cam->streaming) अणु
		ret = cpia2_usb_stream_start(cam,
				cam->params.camera_state.stream_mode);
		अगर (!ret)
			v4l2_ctrl_grab(cam->usb_alt, true);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cpia2_streamoff(काष्ठा file *file, व्योम *fh, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);
	पूर्णांक ret = -EINVAL;

	DBG("VIDIOC_STREAMOFF, streaming=%d\n", cam->streaming);
	अगर (!cam->mmapped || type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (cam->streaming) अणु
		ret = cpia2_usb_stream_stop(cam);
		अगर (!ret)
			v4l2_ctrl_grab(cam->usb_alt, false);
	पूर्ण
	वापस ret;
पूर्ण

/******************************************************************************
 *
 *  cpia2_mmap
 *
 *****************************************************************************/
अटल पूर्णांक cpia2_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *area)
अणु
	काष्ठा camera_data *cam = video_drvdata(file);
	पूर्णांक retval;

	अगर (mutex_lock_पूर्णांकerruptible(&cam->v4l2_lock))
		वापस -ERESTARTSYS;
	retval = cpia2_remap_buffer(cam, area);

	अगर(!retval)
		cam->stream_fh = file->निजी_data;
	mutex_unlock(&cam->v4l2_lock);
	वापस retval;
पूर्ण

/******************************************************************************
 *
 *  reset_camera_काष्ठा_v4l
 *
 *  Sets all values to the शेषs
 *****************************************************************************/
अटल व्योम reset_camera_काष्ठा_v4l(काष्ठा camera_data *cam)
अणु
	cam->width = cam->params.roi.width;
	cam->height = cam->params.roi.height;

	cam->frame_size = buffer_size;
	cam->num_frames = num_buffers;

	/* Flicker modes */
	cam->params.flicker_control.flicker_mode_req = flicker_mode;

	/* stream modes */
	cam->params.camera_state.stream_mode = alternate;

	cam->pixelक्रमmat = V4L2_PIX_FMT_JPEG;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops cpia2_ioctl_ops = अणु
	.vidioc_querycap		    = cpia2_querycap,
	.vidioc_क्रमागत_input		    = cpia2_क्रमागत_input,
	.vidioc_g_input			    = cpia2_g_input,
	.vidioc_s_input			    = cpia2_s_input,
	.vidioc_क्रमागत_fmt_vid_cap	    = cpia2_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		    = cpia2_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		    = cpia2_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		    = cpia2_try_fmt_vid_cap,
	.vidioc_g_jpegcomp		    = cpia2_g_jpegcomp,
	.vidioc_s_jpegcomp		    = cpia2_s_jpegcomp,
	.vidioc_g_selection		    = cpia2_g_selection,
	.vidioc_reqbufs			    = cpia2_reqbufs,
	.vidioc_querybuf		    = cpia2_querybuf,
	.vidioc_qbuf			    = cpia2_qbuf,
	.vidioc_dqbuf			    = cpia2_dqbuf,
	.vidioc_streamon		    = cpia2_streamon,
	.vidioc_streamoff		    = cpia2_streamoff,
	.vidioc_s_parm			    = cpia2_s_parm,
	.vidioc_g_parm			    = cpia2_g_parm,
	.vidioc_क्रमागत_framesizes		    = cpia2_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals	    = cpia2_क्रमागत_frameपूर्णांकervals,
	.vidioc_subscribe_event		    = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	    = v4l2_event_unsubscribe,
पूर्ण;

/***
 * The v4l video device काष्ठाure initialized क्रम this device
 ***/
अटल स्थिर काष्ठा v4l2_file_operations cpia2_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= cpia2_खोलो,
	.release	= cpia2_बंद,
	.पढ़ो		= cpia2_v4l_पढ़ो,
	.poll		= cpia2_v4l_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= cpia2_mmap,
पूर्ण;

अटल स्थिर काष्ठा video_device cpia2_ढाँचा = अणु
	/* I could not find any place क्रम the old .initialize initializer?? */
	.name =		"CPiA2 Camera",
	.fops =		&cpia2_fops,
	.ioctl_ops =	&cpia2_ioctl_ops,
	.release =	video_device_release_empty,
पूर्ण;

व्योम cpia2_camera_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा camera_data *cam =
		container_of(v4l2_dev, काष्ठा camera_data, v4l2_dev);

	v4l2_ctrl_handler_मुक्त(&cam->hdl);
	v4l2_device_unरेजिस्टर(&cam->v4l2_dev);
	kमुक्त(cam);
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops cpia2_ctrl_ops = अणु
	.s_ctrl = cpia2_s_ctrl,
पूर्ण;

/******************************************************************************
 *
 *  cpia2_रेजिस्टर_camera
 *
 *****************************************************************************/
पूर्णांक cpia2_रेजिस्टर_camera(काष्ठा camera_data *cam)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &cam->hdl;
	काष्ठा v4l2_ctrl_config cpia2_usb_alt = अणु
		.ops = &cpia2_ctrl_ops,
		.id = CPIA2_CID_USB_ALT,
		.name = "USB Alternate",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = USBIF_ISO_1,
		.max = USBIF_ISO_6,
		.step = 1,
	पूर्ण;
	पूर्णांक ret;

	v4l2_ctrl_handler_init(hdl, 12);
	v4l2_ctrl_new_std(hdl, &cpia2_ctrl_ops,
			V4L2_CID_BRIGHTNESS,
			cam->params.pnp_id.device_type == DEVICE_STV_672 ? 1 : 0,
			255, 1, DEFAULT_BRIGHTNESS);
	v4l2_ctrl_new_std(hdl, &cpia2_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, DEFAULT_CONTRAST);
	v4l2_ctrl_new_std(hdl, &cpia2_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, DEFAULT_SATURATION);
	v4l2_ctrl_new_std(hdl, &cpia2_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(hdl, &cpia2_ctrl_ops,
			V4L2_CID_JPEG_ACTIVE_MARKER, 0,
			V4L2_JPEG_ACTIVE_MARKER_DHT, 0,
			V4L2_JPEG_ACTIVE_MARKER_DHT);
	v4l2_ctrl_new_std(hdl, &cpia2_ctrl_ops,
			V4L2_CID_JPEG_COMPRESSION_QUALITY, 1,
			100, 1, 100);
	cpia2_usb_alt.def = alternate;
	cam->usb_alt = v4l2_ctrl_new_custom(hdl, &cpia2_usb_alt, शून्य);
	/* VP5 Only */
	अगर (cam->params.pnp_id.device_type != DEVICE_STV_672)
		v4l2_ctrl_new_std(hdl, &cpia2_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	/* Flicker control only valid क्रम 672 */
	अगर (cam->params.pnp_id.device_type == DEVICE_STV_672)
		v4l2_ctrl_new_std_menu(hdl, &cpia2_ctrl_ops,
			V4L2_CID_POWER_LINE_FREQUENCY,
			V4L2_CID_POWER_LINE_FREQUENCY_60HZ, 0, 0);
	/* Light control only valid क्रम the QX5 Microscope */
	अगर (cam->params.pnp_id.product == 0x151) अणु
		cam->top_light = v4l2_ctrl_new_std(hdl, &cpia2_ctrl_ops,
				V4L2_CID_ILLUMINATORS_1, 0, 1, 1, 0);
		cam->bottom_light = v4l2_ctrl_new_std(hdl, &cpia2_ctrl_ops,
				V4L2_CID_ILLUMINATORS_2, 0, 1, 1, 0);
		v4l2_ctrl_cluster(2, &cam->top_light);
	पूर्ण

	अगर (hdl->error) अणु
		ret = hdl->error;
		v4l2_ctrl_handler_मुक्त(hdl);
		वापस ret;
	पूर्ण

	cam->vdev = cpia2_ढाँचा;
	video_set_drvdata(&cam->vdev, cam);
	cam->vdev.lock = &cam->v4l2_lock;
	cam->vdev.ctrl_handler = hdl;
	cam->vdev.v4l2_dev = &cam->v4l2_dev;
	cam->vdev.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
				V4L2_CAP_STREAMING;

	reset_camera_काष्ठा_v4l(cam);

	/* रेजिस्टर v4l device */
	अगर (video_रेजिस्टर_device(&cam->vdev, VFL_TYPE_VIDEO, video_nr) < 0) अणु
		ERR("video_register_device failed\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  cpia2_unरेजिस्टर_camera
 *
 *****************************************************************************/
व्योम cpia2_unरेजिस्टर_camera(काष्ठा camera_data *cam)
अणु
	video_unरेजिस्टर_device(&cam->vdev);
पूर्ण

/******************************************************************************
 *
 *  check_parameters
 *
 *  Make sure that all user-supplied parameters are sensible
 *****************************************************************************/
अटल व्योम __init check_parameters(व्योम)
अणु
	अगर(buffer_size < PAGE_SIZE) अणु
		buffer_size = PAGE_SIZE;
		LOG("buffer_size too small, setting to %d\n", buffer_size);
	पूर्ण अन्यथा अगर(buffer_size > 1024*1024) अणु
		/* arbitrary upper limiit */
		buffer_size = 1024*1024;
		LOG("buffer_size ridiculously large, setting to %d\n",
		    buffer_size);
	पूर्ण अन्यथा अणु
		buffer_size += PAGE_SIZE-1;
		buffer_size &= ~(PAGE_SIZE-1);
	पूर्ण

	अगर(num_buffers < 1) अणु
		num_buffers = 1;
		LOG("num_buffers too small, setting to %d\n", num_buffers);
	पूर्ण अन्यथा अगर(num_buffers > VIDEO_MAX_FRAME) अणु
		num_buffers = VIDEO_MAX_FRAME;
		LOG("num_buffers too large, setting to %d\n", num_buffers);
	पूर्ण

	अगर(alternate < USBIF_ISO_1 || alternate > USBIF_ISO_6) अणु
		alternate = DEFAULT_ALT;
		LOG("alternate specified is invalid, using %d\n", alternate);
	पूर्ण

	अगर (flicker_mode != 0 && flicker_mode != FLICKER_50 && flicker_mode != FLICKER_60) अणु
		flicker_mode = 0;
		LOG("Flicker mode specified is invalid, using %d\n",
		    flicker_mode);
	पूर्ण

	DBG("Using %d buffers, each %d bytes, alternate=%d\n",
	    num_buffers, buffer_size, alternate);
पूर्ण

/************   Module Stuff ***************/


/******************************************************************************
 *
 * cpia2_init/module_init
 *
 *****************************************************************************/
अटल पूर्णांक __init cpia2_init(व्योम)
अणु
	LOG("%s v%s\n",
	    ABOUT, CPIA_VERSION);
	check_parameters();
	वापस cpia2_usb_init();
पूर्ण


/******************************************************************************
 *
 * cpia2_निकास/module_निकास
 *
 *****************************************************************************/
अटल व्योम __निकास cpia2_निकास(व्योम)
अणु
	cpia2_usb_cleanup();
	schedule_समयout(2 * HZ);
पूर्ण

module_init(cpia2_init);
module_निकास(cpia2_निकास);
