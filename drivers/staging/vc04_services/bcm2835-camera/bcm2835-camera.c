<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Broadcom BM2835 V4L2 driver
 *
 * Copyright तऊ 2013 Raspberry Pi (Trading) Ltd.
 *
 * Authors: Vincent Sanders @ Collabora
 *          Dave Stevenson @ Broadcom
 *		(now dave.stevenson@raspberrypi.org)
 *          Simon Mellor @ Broadcom
 *          Luke Diamand @ Broadcom
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-common.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "mmal-common.h"
#समावेश "mmal-encodings.h"
#समावेश "mmal-vchiq.h"
#समावेश "mmal-msg.h"
#समावेश "mmal-parameters.h"
#समावेश "bcm2835-camera.h"

#घोषणा BM2835_MMAL_VERSION "0.0.2"
#घोषणा BM2835_MMAL_MODULE_NAME "bcm2835-v4l2"
#घोषणा MIN_WIDTH 32
#घोषणा MIN_HEIGHT 32
#घोषणा MIN_BUFFER_SIZE (80 * 1024)

#घोषणा MAX_VIDEO_MODE_WIDTH 1280
#घोषणा MAX_VIDEO_MODE_HEIGHT 720

#घोषणा MAX_BCM2835_CAMERAS 2

पूर्णांक bcm2835_v4l2_debug;
module_param_named(debug, bcm2835_v4l2_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(bcm2835_v4l2_debug, "Debug level 0-2");

#घोषणा UNSET (-1)
अटल पूर्णांक video_nr[] = अणु[0 ... (MAX_BCM2835_CAMERAS - 1)] = UNSET पूर्ण;
module_param_array(video_nr, पूर्णांक, शून्य, 0644);
MODULE_PARM_DESC(video_nr, "videoX start numbers, -1 is autodetect");

अटल पूर्णांक max_video_width = MAX_VIDEO_MODE_WIDTH;
अटल पूर्णांक max_video_height = MAX_VIDEO_MODE_HEIGHT;
module_param(max_video_width, पूर्णांक, 0644);
MODULE_PARM_DESC(max_video_width, "Threshold for video mode");
module_param(max_video_height, पूर्णांक, 0644);
MODULE_PARM_DESC(max_video_height, "Threshold for video mode");

/* camera instance counter */
अटल atomic_t camera_instance = ATOMIC_INIT(0);

/* global device data array */
अटल काष्ठा bm2835_mmal_dev *gdev[MAX_BCM2835_CAMERAS];

#घोषणा FPS_MIN 1
#घोषणा FPS_MAX 90

/* समयperframe: min/max and शेष */
अटल स्थिर काष्ठा v4l2_fract
	tpf_min     = अणु.numerator = 1,		.denominator = FPS_MAXपूर्ण,
	tpf_max     = अणु.numerator = 1,	        .denominator = FPS_MINपूर्ण,
	tpf_शेष = अणु.numerator = 1000,	.denominator = 30000पूर्ण;

/* Container क्रम MMAL and VB2 buffers*/
काष्ठा vb2_mmal_buffer अणु
	काष्ठा vb2_v4l2_buffer	vb;
	काष्ठा mmal_buffer	mmal;
पूर्ण;

/* video क्रमmats */
अटल काष्ठा mmal_fmt क्रमmats[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_YUV420,
		.mmal = MMAL_ENCODING_I420,
		.depth = 12,
		.mmal_component = COMP_CAMERA,
		.ybbp = 1,
		.हटाओ_padding = 1,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUYV,
		.mmal = MMAL_ENCODING_YUYV,
		.depth = 16,
		.mmal_component = COMP_CAMERA,
		.ybbp = 2,
		.हटाओ_padding = 0,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_RGB24,
		.mmal = MMAL_ENCODING_RGB24,
		.depth = 24,
		.mmal_component = COMP_CAMERA,
		.ybbp = 3,
		.हटाओ_padding = 0,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_JPEG,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
		.mmal = MMAL_ENCODING_JPEG,
		.depth = 8,
		.mmal_component = COMP_IMAGE_ENCODE,
		.ybbp = 0,
		.हटाओ_padding = 0,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_H264,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
		.mmal = MMAL_ENCODING_H264,
		.depth = 8,
		.mmal_component = COMP_VIDEO_ENCODE,
		.ybbp = 0,
		.हटाओ_padding = 0,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_MJPEG,
		.flags = V4L2_FMT_FLAG_COMPRESSED,
		.mmal = MMAL_ENCODING_MJPEG,
		.depth = 8,
		.mmal_component = COMP_VIDEO_ENCODE,
		.ybbp = 0,
		.हटाओ_padding = 0,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YVYU,
		.mmal = MMAL_ENCODING_YVYU,
		.depth = 16,
		.mmal_component = COMP_CAMERA,
		.ybbp = 2,
		.हटाओ_padding = 0,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_VYUY,
		.mmal = MMAL_ENCODING_VYUY,
		.depth = 16,
		.mmal_component = COMP_CAMERA,
		.ybbp = 2,
		.हटाओ_padding = 0,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_UYVY,
		.mmal = MMAL_ENCODING_UYVY,
		.depth = 16,
		.mmal_component = COMP_CAMERA,
		.ybbp = 2,
		.हटाओ_padding = 0,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV12,
		.mmal = MMAL_ENCODING_NV12,
		.depth = 12,
		.mmal_component = COMP_CAMERA,
		.ybbp = 1,
		.हटाओ_padding = 1,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_BGR24,
		.mmal = MMAL_ENCODING_BGR24,
		.depth = 24,
		.mmal_component = COMP_CAMERA,
		.ybbp = 3,
		.हटाओ_padding = 0,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YVU420,
		.mmal = MMAL_ENCODING_YV12,
		.depth = 12,
		.mmal_component = COMP_CAMERA,
		.ybbp = 1,
		.हटाओ_padding = 1,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV21,
		.mmal = MMAL_ENCODING_NV21,
		.depth = 12,
		.mmal_component = COMP_CAMERA,
		.ybbp = 1,
		.हटाओ_padding = 1,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_BGR32,
		.mmal = MMAL_ENCODING_BGRA,
		.depth = 32,
		.mmal_component = COMP_CAMERA,
		.ybbp = 4,
		.हटाओ_padding = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा mmal_fmt *get_क्रमmat(काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mmal_fmt *fmt;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < ARRAY_SIZE(क्रमmats); k++) अणु
		fmt = &क्रमmats[k];
		अगर (fmt->fourcc == f->fmt.pix.pixelक्रमmat)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

/* ------------------------------------------------------------------
 *	Videobuf queue operations
 * ------------------------------------------------------------------
 */

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_ctxs[])
अणु
	काष्ठा bm2835_mmal_dev *dev = vb2_get_drv_priv(vq);
	अचिन्हित दीर्घ size;

	/* refuse queue setup अगर port is not configured */
	अगर (!dev->capture.port) अणु
		v4l2_err(&dev->v4l2_dev,
			 "%s: capture port not configured\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Handle CREATE_BUFS situation - *nplanes != 0 */
	अगर (*nplanes) अणु
		अगर (*nplanes != 1 ||
		    sizes[0] < dev->capture.port->current_buffer.size) अणु
			v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
				 "%s: dev:%p Invalid buffer request from CREATE_BUFS, size %u < %u, nplanes %u != 1\n",
				 __func__, dev, sizes[0],
				 dev->capture.port->current_buffer.size,
				 *nplanes);
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण

	/* Handle REQBUFS situation */
	size = dev->capture.port->current_buffer.size;
	अगर (size == 0) अणु
		v4l2_err(&dev->v4l2_dev,
			 "%s: capture port buffer size is zero\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (*nbuffers < dev->capture.port->minimum_buffer.num)
		*nbuffers = dev->capture.port->minimum_buffer.num;

	dev->capture.port->current_buffer.num = *nbuffers;

	*nplanes = 1;

	sizes[0] = size;

	/*
	 * videobuf2-vदो_स्मृति allocator is context-less so no need to set
	 * alloc_ctxs array.
	 */

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev, "%s: dev:%p\n",
		 __func__, dev);

	वापस 0;
पूर्ण

अटल पूर्णांक buffer_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा bm2835_mmal_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vb2 = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_mmal_buffer *buf =
				container_of(vb2, काष्ठा vb2_mmal_buffer, vb);

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev, "%s: dev:%p, vb %p\n",
		 __func__, dev, vb);
	buf->mmal.buffer = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
	buf->mmal.buffer_size = vb2_plane_size(&buf->vb.vb2_buf, 0);

	वापस mmal_vchi_buffer_init(dev->instance, &buf->mmal);
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा bm2835_mmal_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ size;

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev, "%s: dev:%p, vb %p\n",
		 __func__, dev, vb);

	अगर (!dev->capture.port || !dev->capture.fmt)
		वापस -ENODEV;

	size = dev->capture.stride * dev->capture.height;
	अगर (vb2_plane_size(vb, 0) < size) अणु
		v4l2_err(&dev->v4l2_dev,
			 "%s data will not fit into plane (%lu < %lu)\n",
			 __func__, vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम buffer_cleanup(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा bm2835_mmal_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vb2 = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_mmal_buffer *buf =
				container_of(vb2, काष्ठा vb2_mmal_buffer, vb);

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev, "%s: dev:%p, vb %p\n",
		 __func__, dev, vb);

	mmal_vchi_buffer_cleanup(&buf->mmal);
पूर्ण

अटल अंतरभूत bool is_capturing(काष्ठा bm2835_mmal_dev *dev)
अणु
	वापस dev->capture.camera_port ==
	    &dev->component[COMP_CAMERA]->output[CAM_PORT_CAPTURE];
पूर्ण

अटल व्योम buffer_cb(काष्ठा vchiq_mmal_instance *instance,
		      काष्ठा vchiq_mmal_port *port,
		      पूर्णांक status,
		      काष्ठा mmal_buffer *mmal_buf)
अणु
	काष्ठा bm2835_mmal_dev *dev = port->cb_ctx;
	काष्ठा vb2_mmal_buffer *buf =
			container_of(mmal_buf, काष्ठा vb2_mmal_buffer, mmal);

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "%s: status:%d, buf:%p, length:%lu, flags %u, pts %lld\n",
		 __func__, status, buf, mmal_buf->length, mmal_buf->mmal_flags,
		 mmal_buf->pts);

	अगर (status) अणु
		/* error in transfer */
		अगर (buf) अणु
			/* there was a buffer with the error so वापस it */
			vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		पूर्ण
		वापस;
	पूर्ण

	अगर (mmal_buf->length == 0) अणु
		/* stream ended */
		अगर (dev->capture.frame_count) अणु
			/* empty buffer whilst capturing - expected to be an
			 * EOS, so grab another frame
			 */
			अगर (is_capturing(dev)) अणु
				v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
					 "Grab another frame");
				vchiq_mmal_port_parameter_set(
					instance,
					dev->capture.camera_port,
					MMAL_PARAMETER_CAPTURE,
					&dev->capture.frame_count,
					माप(dev->capture.frame_count));
			पूर्ण
			अगर (vchiq_mmal_submit_buffer(instance, port,
						     &buf->mmal))
				v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
					 "Failed to return EOS buffer");
		पूर्ण अन्यथा अणु
			/* stopping streaming.
			 * वापस buffer, and संकेत frame completion
			 */
			vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
			complete(&dev->capture.frame_cmplt);
		पूर्ण
		वापस;
	पूर्ण

	अगर (!dev->capture.frame_count) अणु
		/* संकेत frame completion */
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		complete(&dev->capture.frame_cmplt);
		वापस;
	पूर्ण

	अगर (dev->capture.vc_start_बारtamp != -1 && mmal_buf->pts) अणु
		kसमय_प्रकार बारtamp;
		s64 runसमय_us = mmal_buf->pts -
		    dev->capture.vc_start_बारtamp;
		बारtamp = kसमय_add_us(dev->capture.kernel_start_ts,
					 runसमय_us);
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "Convert start time %llu and %llu with offset %llu to %llu\n",
			 kसमय_प्रकारo_ns(dev->capture.kernel_start_ts),
			 dev->capture.vc_start_बारtamp, mmal_buf->pts,
			 kसमय_प्रकारo_ns(बारtamp));
		buf->vb.vb2_buf.बारtamp = kसमय_प्रकारo_ns(बारtamp);
	पूर्ण अन्यथा अणु
		buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
	पूर्ण
	buf->vb.sequence = dev->capture.sequence++;
	buf->vb.field = V4L2_FIELD_NONE;

	vb2_set_plane_payload(&buf->vb.vb2_buf, 0, mmal_buf->length);
	अगर (mmal_buf->mmal_flags & MMAL_BUFFER_HEADER_FLAG_KEYFRAME)
		buf->vb.flags |= V4L2_BUF_FLAG_KEYFRAME;

	vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);

	अगर (mmal_buf->mmal_flags & MMAL_BUFFER_HEADER_FLAG_EOS &&
	    is_capturing(dev)) अणु
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "Grab another frame as buffer has EOS");
		vchiq_mmal_port_parameter_set(
			instance,
			dev->capture.camera_port,
			MMAL_PARAMETER_CAPTURE,
			&dev->capture.frame_count,
			माप(dev->capture.frame_count));
	पूर्ण
पूर्ण

अटल पूर्णांक enable_camera(काष्ठा bm2835_mmal_dev *dev)
अणु
	पूर्णांक ret;

	अगर (!dev->camera_use_count) अणु
		ret = vchiq_mmal_port_parameter_set(
			dev->instance,
			&dev->component[COMP_CAMERA]->control,
			MMAL_PARAMETER_CAMERA_NUM, &dev->camera_num,
			माप(dev->camera_num));
		अगर (ret < 0) अणु
			v4l2_err(&dev->v4l2_dev,
				 "Failed setting camera num, ret %d\n", ret);
			वापस -EINVAL;
		पूर्ण

		ret = vchiq_mmal_component_enable(dev->instance,
						  dev->component[COMP_CAMERA]);
		अगर (ret < 0) अणु
			v4l2_err(&dev->v4l2_dev,
				 "Failed enabling camera, ret %d\n", ret);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	dev->camera_use_count++;
	v4l2_dbg(1, bcm2835_v4l2_debug,
		 &dev->v4l2_dev, "enabled camera (refcount %d)\n",
			dev->camera_use_count);
	वापस 0;
पूर्ण

अटल पूर्णांक disable_camera(काष्ठा bm2835_mmal_dev *dev)
अणु
	पूर्णांक ret;

	अगर (!dev->camera_use_count) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Disabled the camera when already disabled\n");
		वापस -EINVAL;
	पूर्ण
	dev->camera_use_count--;
	अगर (!dev->camera_use_count) अणु
		अचिन्हित पूर्णांक i = 0xFFFFFFFF;

		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "Disabling camera\n");
		ret = vchiq_mmal_component_disable(dev->instance,
						   dev->component[COMP_CAMERA]);
		अगर (ret < 0) अणु
			v4l2_err(&dev->v4l2_dev,
				 "Failed disabling camera, ret %d\n", ret);
			वापस -EINVAL;
		पूर्ण
		vchiq_mmal_port_parameter_set(
			dev->instance,
			&dev->component[COMP_CAMERA]->control,
			MMAL_PARAMETER_CAMERA_NUM, &i,
			माप(i));
	पूर्ण
	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "Camera refcount now %d\n", dev->camera_use_count);
	वापस 0;
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा bm2835_mmal_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vb2 = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_mmal_buffer *buf =
				container_of(vb2, काष्ठा vb2_mmal_buffer, vb);
	पूर्णांक ret;

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "%s: dev:%p buf:%p, idx %u\n",
		 __func__, dev, buf, vb2->vb2_buf.index);

	ret = vchiq_mmal_submit_buffer(dev->instance, dev->capture.port,
				       &buf->mmal);
	अगर (ret < 0)
		v4l2_err(&dev->v4l2_dev, "%s: error submitting buffer\n",
			 __func__);
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा bm2835_mmal_dev *dev = vb2_get_drv_priv(vq);
	पूर्णांक ret;
	u32 parameter_size;

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev, "%s: dev:%p\n",
		 __func__, dev);

	/* ensure a क्रमmat has actually been set */
	अगर (!dev->capture.port)
		वापस -EINVAL;

	अगर (enable_camera(dev) < 0) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to enable camera\n");
		वापस -EINVAL;
	पूर्ण

	/*init_completion(&dev->capture.frame_cmplt); */

	/* enable frame capture */
	dev->capture.frame_count = 1;

	/* reset sequence number */
	dev->capture.sequence = 0;

	/* अगर the preview is not alपढ़ोy running, रुको क्रम a few frames क्रम AGC
	 * to settle करोwn.
	 */
	अगर (!dev->component[COMP_PREVIEW]->enabled)
		msleep(300);

	/* enable the connection from camera to encoder (अगर applicable) */
	अगर (dev->capture.camera_port != dev->capture.port &&
	    dev->capture.camera_port) अणु
		ret = vchiq_mmal_port_enable(dev->instance,
					     dev->capture.camera_port, शून्य);
		अगर (ret) अणु
			v4l2_err(&dev->v4l2_dev,
				 "Failed to enable encode tunnel - error %d\n",
				 ret);
			वापस -1;
		पूर्ण
	पूर्ण

	/* Get VC बारtamp at this poपूर्णांक in समय */
	parameter_size = माप(dev->capture.vc_start_बारtamp);
	अगर (vchiq_mmal_port_parameter_get(dev->instance,
					  dev->capture.camera_port,
					  MMAL_PARAMETER_SYSTEM_TIME,
					  &dev->capture.vc_start_बारtamp,
					  &parameter_size)) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Failed to get VC start time - update your VC f/w\n");

		/* Flag to indicate just to rely on kernel बारtamps */
		dev->capture.vc_start_बारtamp = -1;
	पूर्ण अन्यथा अणु
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "Start time %lld size %d\n",
			 dev->capture.vc_start_बारtamp, parameter_size);
	पूर्ण

	dev->capture.kernel_start_ts = kसमय_get();

	/* enable the camera port */
	dev->capture.port->cb_ctx = dev;
	ret = vchiq_mmal_port_enable(dev->instance, dev->capture.port,
				     buffer_cb);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Failed to enable capture port - error %d. Disabling camera port again\n",
			 ret);

		vchiq_mmal_port_disable(dev->instance,
					dev->capture.camera_port);
		अगर (disable_camera(dev) < 0) अणु
			v4l2_err(&dev->v4l2_dev, "Failed to disable camera\n");
			वापस -EINVAL;
		पूर्ण
		वापस -1;
	पूर्ण

	/* capture the first frame */
	vchiq_mmal_port_parameter_set(dev->instance,
				      dev->capture.camera_port,
				      MMAL_PARAMETER_CAPTURE,
				      &dev->capture.frame_count,
				      माप(dev->capture.frame_count));
	वापस 0;
पूर्ण

/* पात streaming and रुको क्रम last buffer */
अटल व्योम stop_streaming(काष्ठा vb2_queue *vq)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;
	काष्ठा bm2835_mmal_dev *dev = vb2_get_drv_priv(vq);
	काष्ठा vchiq_mmal_port *port = dev->capture.port;

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev, "%s: dev:%p\n",
		 __func__, dev);

	init_completion(&dev->capture.frame_cmplt);
	dev->capture.frame_count = 0;

	/* ensure a क्रमmat has actually been set */
	अगर (!port) अणु
		v4l2_err(&dev->v4l2_dev,
			 "no capture port - stream not started?\n");
		वापस;
	पूर्ण

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev, "stopping capturing\n");

	/* stop capturing frames */
	vchiq_mmal_port_parameter_set(dev->instance,
				      dev->capture.camera_port,
				      MMAL_PARAMETER_CAPTURE,
				      &dev->capture.frame_count,
				      माप(dev->capture.frame_count));

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "disabling connection\n");

	/* disable the connection from camera to encoder */
	ret = vchiq_mmal_port_disable(dev->instance, dev->capture.camera_port);
	अगर (!ret && dev->capture.camera_port != port) अणु
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "disabling port\n");
		ret = vchiq_mmal_port_disable(dev->instance, port);
	पूर्ण अन्यथा अगर (dev->capture.camera_port != port) अणु
		v4l2_err(&dev->v4l2_dev, "port_disable failed, error %d\n",
			 ret);
	पूर्ण

	/* रुको क्रम all buffers to be वापसed */
	जबतक (atomic_पढ़ो(&port->buffers_with_vpu)) अणु
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "%s: Waiting for buffers to be returned - %d outstanding\n",
			 __func__, atomic_पढ़ो(&port->buffers_with_vpu));
		समयout = रुको_क्रम_completion_समयout(&dev->capture.frame_cmplt,
						      HZ);
		अगर (समयout == 0) अणु
			v4l2_err(&dev->v4l2_dev, "%s: Timeout waiting for buffers to be returned - %d outstanding\n",
				 __func__,
				 atomic_पढ़ो(&port->buffers_with_vpu));
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (disable_camera(dev) < 0)
		v4l2_err(&dev->v4l2_dev, "Failed to disable camera\n");
पूर्ण

अटल स्थिर काष्ठा vb2_ops bm2835_mmal_video_qops = अणु
	.queue_setup = queue_setup,
	.buf_init = buffer_init,
	.buf_prepare = buffer_prepare,
	.buf_cleanup = buffer_cleanup,
	.buf_queue = buffer_queue,
	.start_streaming = start_streaming,
	.stop_streaming = stop_streaming,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
पूर्ण;

/* ------------------------------------------------------------------
 *	IOCTL operations
 * ------------------------------------------------------------------
 */

अटल पूर्णांक set_overlay_params(काष्ठा bm2835_mmal_dev *dev,
			      काष्ठा vchiq_mmal_port *port)
अणु
	काष्ठा mmal_parameter_displayregion prev_config = अणु
		.set =	MMAL_DISPLAY_SET_LAYER |
			MMAL_DISPLAY_SET_ALPHA |
			MMAL_DISPLAY_SET_DEST_RECT |
			MMAL_DISPLAY_SET_FULLSCREEN,
		.layer = 2,
		.alpha = dev->overlay.global_alpha,
		.fullscreen = 0,
		.dest_rect = अणु
			.x = dev->overlay.w.left,
			.y = dev->overlay.w.top,
			.width = dev->overlay.w.width,
			.height = dev->overlay.w.height,
		पूर्ण,
	पूर्ण;
	वापस vchiq_mmal_port_parameter_set(dev->instance, port,
					     MMAL_PARAMETER_DISPLAYREGION,
					     &prev_config, माप(prev_config));
पूर्ण

/* overlay ioctl */
अटल पूर्णांक vidioc_क्रमागत_fmt_vid_overlay(काष्ठा file *file, व्योम *priv,
				       काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा mmal_fmt *fmt;

	अगर (f->index >= ARRAY_SIZE(क्रमmats))
		वापस -EINVAL;

	fmt = &क्रमmats[f->index];

	f->pixelक्रमmat = fmt->fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_overlay(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा bm2835_mmal_dev *dev = video_drvdata(file);

	f->fmt.win = dev->overlay;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_overlay(काष्ठा file *file, व्योम *priv,
				      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा bm2835_mmal_dev *dev = video_drvdata(file);

	f->fmt.win.field = V4L2_FIELD_NONE;
	f->fmt.win.chromakey = 0;
	f->fmt.win.clips = शून्य;
	f->fmt.win.clipcount = 0;
	f->fmt.win.biपंचांगap = शून्य;

	v4l_bound_align_image(&f->fmt.win.w.width, MIN_WIDTH, dev->max_width, 1,
			      &f->fmt.win.w.height, MIN_HEIGHT, dev->max_height,
			      1, 0);
	v4l_bound_align_image(&f->fmt.win.w.left, MIN_WIDTH, dev->max_width, 1,
			      &f->fmt.win.w.top, MIN_HEIGHT, dev->max_height,
			      1, 0);

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "Overlay: Now w/h %dx%d l/t %dx%d\n",
		f->fmt.win.w.width, f->fmt.win.w.height,
		f->fmt.win.w.left, f->fmt.win.w.top);

	v4l2_dump_win_क्रमmat(1,
			     bcm2835_v4l2_debug,
			     &dev->v4l2_dev,
			     &f->fmt.win,
			     __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_overlay(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा bm2835_mmal_dev *dev = video_drvdata(file);

	vidioc_try_fmt_vid_overlay(file, priv, f);

	dev->overlay = f->fmt.win;
	अगर (dev->component[COMP_PREVIEW]->enabled) अणु
		set_overlay_params(dev,
				   &dev->component[COMP_PREVIEW]->input[0]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_overlay(काष्ठा file *file, व्योम *f, अचिन्हित पूर्णांक on)
अणु
	पूर्णांक ret;
	काष्ठा bm2835_mmal_dev *dev = video_drvdata(file);
	काष्ठा vchiq_mmal_port *src;
	काष्ठा vchiq_mmal_port *dst;

	अगर ((on && dev->component[COMP_PREVIEW]->enabled) ||
	    (!on && !dev->component[COMP_PREVIEW]->enabled))
		वापस 0;	/* alपढ़ोy in requested state */

	src = &dev->component[COMP_CAMERA]->output[CAM_PORT_PREVIEW];

	अगर (!on) अणु
		/* disconnect preview ports and disable component */
		ret = vchiq_mmal_port_disable(dev->instance, src);
		अगर (!ret)
			ret = vchiq_mmal_port_connect_tunnel(dev->instance, src,
							     शून्य);
		अगर (ret >= 0)
			ret = vchiq_mmal_component_disable(
					dev->instance,
					dev->component[COMP_PREVIEW]);

		disable_camera(dev);
		वापस ret;
	पूर्ण

	/* set preview port क्रमmat and connect it to output */
	dst = &dev->component[COMP_PREVIEW]->input[0];

	ret = vchiq_mmal_port_set_क्रमmat(dev->instance, src);
	अगर (ret < 0)
		वापस ret;

	ret = set_overlay_params(dev, dst);
	अगर (ret < 0)
		वापस ret;

	अगर (enable_camera(dev) < 0)
		वापस -EINVAL;

	ret = vchiq_mmal_component_enable(dev->instance,
					  dev->component[COMP_PREVIEW]);
	अगर (ret < 0)
		वापस ret;

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev, "connecting %p to %p\n",
		 src, dst);
	ret = vchiq_mmal_port_connect_tunnel(dev->instance, src, dst);
	अगर (ret)
		वापस ret;

	वापस vchiq_mmal_port_enable(dev->instance, src, शून्य);
पूर्ण

अटल पूर्णांक vidioc_g_fbuf(काष्ठा file *file, व्योम *fh,
			 काष्ठा v4l2_framebuffer *a)
अणु
	/* The video overlay must stay within the framebuffer and can't be
	 * positioned independently.
	 */
	काष्ठा bm2835_mmal_dev *dev = video_drvdata(file);
	काष्ठा vchiq_mmal_port *preview_port =
		&dev->component[COMP_CAMERA]->output[CAM_PORT_PREVIEW];

	a->capability = V4L2_FBUF_CAP_EXTERNOVERLAY |
			V4L2_FBUF_CAP_GLOBAL_ALPHA;
	a->flags = V4L2_FBUF_FLAG_OVERLAY;
	a->fmt.width = preview_port->es.video.width;
	a->fmt.height = preview_port->es.video.height;
	a->fmt.pixelक्रमmat = V4L2_PIX_FMT_YUV420;
	a->fmt.bytesperline = preview_port->es.video.width;
	a->fmt.sizeimage = (preview_port->es.video.width *
			       preview_port->es.video.height * 3) >> 1;
	a->fmt.colorspace = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

/* input ioctls */
अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_input *inp)
अणु
	/* only a single camera input */
	अगर (inp->index)
		वापस -EINVAL;

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	प्र_लिखो((अक्षर *)inp->name, "Camera %u", inp->index);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	अगर (i)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* capture ioctls */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा bm2835_mmal_dev *dev = video_drvdata(file);
	u32 major;
	u32 minor;

	vchiq_mmal_version(dev->instance, &major, &minor);

	म_नकल((अक्षर *)cap->driver, "bm2835 mmal");
	snम_लिखो((अक्षर *)cap->card, माप(cap->card), "mmal service %d.%d",
		 major, minor);

	snम_लिखो((अक्षर *)cap->bus_info, माप(cap->bus_info),
		 "platform:%s", dev->v4l2_dev.name);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा mmal_fmt *fmt;

	अगर (f->index >= ARRAY_SIZE(क्रमmats))
		वापस -EINVAL;

	fmt = &क्रमmats[f->index];

	f->pixelक्रमmat = fmt->fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा bm2835_mmal_dev *dev = video_drvdata(file);

	f->fmt.pix.width = dev->capture.width;
	f->fmt.pix.height = dev->capture.height;
	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.pixelक्रमmat = dev->capture.fmt->fourcc;
	f->fmt.pix.bytesperline = dev->capture.stride;
	f->fmt.pix.sizeimage = dev->capture.buffersize;

	अगर (dev->capture.fmt->fourcc == V4L2_PIX_FMT_RGB24)
		f->fmt.pix.colorspace = V4L2_COLORSPACE_SRGB;
	अन्यथा अगर (dev->capture.fmt->fourcc == V4L2_PIX_FMT_JPEG)
		f->fmt.pix.colorspace = V4L2_COLORSPACE_JPEG;
	अन्यथा
		f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	f->fmt.pix.priv = 0;

	v4l2_dump_pix_क्रमmat(1, bcm2835_v4l2_debug, &dev->v4l2_dev, &f->fmt.pix,
			     __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा bm2835_mmal_dev *dev = video_drvdata(file);
	काष्ठा mmal_fmt *mfmt;

	mfmt = get_क्रमmat(f);
	अगर (!mfmt) अणु
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "Fourcc format (0x%08x) unknown.\n",
			 f->fmt.pix.pixelक्रमmat);
		f->fmt.pix.pixelक्रमmat = क्रमmats[0].fourcc;
		mfmt = get_क्रमmat(f);
	पूर्ण

	f->fmt.pix.field = V4L2_FIELD_NONE;

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "Clipping/aligning %dx%d format %08X\n",
		 f->fmt.pix.width, f->fmt.pix.height, f->fmt.pix.pixelक्रमmat);

	v4l_bound_align_image(&f->fmt.pix.width, MIN_WIDTH, dev->max_width, 1,
			      &f->fmt.pix.height, MIN_HEIGHT, dev->max_height,
			      1, 0);
	f->fmt.pix.bytesperline = f->fmt.pix.width * mfmt->ybbp;
	अगर (!mfmt->हटाओ_padding) अणु
		अगर (mfmt->depth == 24) अणु
			/*
			 * 24bpp is a pain as we can't use simple masking.
			 * Min stride is width aligned to 16, बार 24bpp.
			 */
			f->fmt.pix.bytesperline =
				((f->fmt.pix.width + 15) & ~15) * 3;
		पूर्ण अन्यथा अणु
			/*
			 * GPU isn't removing padding, so stride is aligned to
			 * 32
			 */
			पूर्णांक align_mask = ((32 * mfmt->depth) >> 3) - 1;

			f->fmt.pix.bytesperline =
				(f->fmt.pix.bytesperline + align_mask) &
							~align_mask;
		पूर्ण
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "Not removing padding, so bytes/line = %d\n",
			 f->fmt.pix.bytesperline);
	पूर्ण

	/* Image buffer has to be padded to allow क्रम alignment, even though
	 * we someबार then हटाओ that padding beक्रमe delivering the buffer.
	 */
	f->fmt.pix.sizeimage = ((f->fmt.pix.height + 15) & ~15) *
			(((f->fmt.pix.width + 31) & ~31) * mfmt->depth) >> 3;

	अगर ((mfmt->flags & V4L2_FMT_FLAG_COMPRESSED) &&
	    f->fmt.pix.sizeimage < MIN_BUFFER_SIZE)
		f->fmt.pix.sizeimage = MIN_BUFFER_SIZE;

	अगर (f->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_RGB24)
		f->fmt.pix.colorspace = V4L2_COLORSPACE_SRGB;
	अन्यथा अगर (f->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_JPEG)
		f->fmt.pix.colorspace = V4L2_COLORSPACE_JPEG;
	अन्यथा
		f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	f->fmt.pix.priv = 0;

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "Now %dx%d format %08X\n",
		f->fmt.pix.width, f->fmt.pix.height, f->fmt.pix.pixelक्रमmat);

	v4l2_dump_pix_क्रमmat(1, bcm2835_v4l2_debug, &dev->v4l2_dev, &f->fmt.pix,
			     __func__);
	वापस 0;
पूर्ण


अटल पूर्णांक mmal_setup_video_component(काष्ठा bm2835_mmal_dev *dev,
				      काष्ठा v4l2_क्रमmat *f)
अणु
	bool overlay_enabled = !!dev->component[COMP_PREVIEW]->enabled;
	काष्ठा vchiq_mmal_port *preview_port;
	पूर्णांक ret;

	preview_port = &dev->component[COMP_CAMERA]->output[CAM_PORT_PREVIEW];

	/* Preview and encode ports need to match on resolution */
	अगर (overlay_enabled) अणु
		/* Need to disable the overlay beक्रमe we can update
		 * the resolution
		 */
		ret = vchiq_mmal_port_disable(dev->instance, preview_port);
		अगर (!ret) अणु
			ret = vchiq_mmal_port_connect_tunnel(dev->instance,
							     preview_port,
							     शून्य);
		पूर्ण
	पूर्ण
	preview_port->es.video.width = f->fmt.pix.width;
	preview_port->es.video.height = f->fmt.pix.height;
	preview_port->es.video.crop.x = 0;
	preview_port->es.video.crop.y = 0;
	preview_port->es.video.crop.width = f->fmt.pix.width;
	preview_port->es.video.crop.height = f->fmt.pix.height;
	preview_port->es.video.frame_rate.num =
				  dev->capture.समयperframe.denominator;
	preview_port->es.video.frame_rate.den =
				  dev->capture.समयperframe.numerator;
	ret = vchiq_mmal_port_set_क्रमmat(dev->instance, preview_port);

	अगर (overlay_enabled) अणु
		ret = vchiq_mmal_port_connect_tunnel(dev->instance,
				preview_port,
				&dev->component[COMP_PREVIEW]->input[0]);
		अगर (ret)
			वापस ret;

		ret = vchiq_mmal_port_enable(dev->instance, preview_port, शून्य);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mmal_setup_encode_component(काष्ठा bm2835_mmal_dev *dev,
				       काष्ठा v4l2_क्रमmat *f,
				       काष्ठा vchiq_mmal_port *port,
				       काष्ठा vchiq_mmal_port *camera_port,
				       काष्ठा vchiq_mmal_component *component)
अणु
	काष्ठा mmal_fmt *mfmt = get_क्रमmat(f);
	पूर्णांक ret;

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "vid_cap - set up encode comp\n");

	/* configure buffering */
	camera_port->current_buffer.size = camera_port->recommended_buffer.size;
	camera_port->current_buffer.num = camera_port->recommended_buffer.num;

	ret = vchiq_mmal_port_connect_tunnel(dev->instance, camera_port,
					     &component->input[0]);
	अगर (ret) अणु
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "%s failed to create connection\n", __func__);
		/* ensure capture is not going to be tried */
		dev->capture.port = शून्य;
		वापस ret;
	पूर्ण

	port->es.video.width = f->fmt.pix.width;
	port->es.video.height = f->fmt.pix.height;
	port->es.video.crop.x = 0;
	port->es.video.crop.y = 0;
	port->es.video.crop.width = f->fmt.pix.width;
	port->es.video.crop.height = f->fmt.pix.height;
	port->es.video.frame_rate.num =
		  dev->capture.समयperframe.denominator;
	port->es.video.frame_rate.den =
		  dev->capture.समयperframe.numerator;

	port->क्रमmat.encoding = mfmt->mmal;
	port->क्रमmat.encoding_variant = 0;
	/* Set any encoding specअगरic parameters */
	चयन (mfmt->mmal_component) अणु
	हाल COMP_VIDEO_ENCODE:
		port->क्रमmat.bitrate = dev->capture.encode_bitrate;
		अवरोध;
	हाल COMP_IMAGE_ENCODE:
		/* Could set EXIF parameters here */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret = vchiq_mmal_port_set_क्रमmat(dev->instance, port);
	अगर (ret) अणु
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "%s failed to set format %dx%d fmt %08X\n",
			 __func__,
			 f->fmt.pix.width,
			 f->fmt.pix.height,
			 f->fmt.pix.pixelक्रमmat);
		वापस ret;
	पूर्ण

	ret = vchiq_mmal_component_enable(dev->instance, component);
	अगर (ret) अणु
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "%s Failed to enable encode components\n", __func__);
		वापस ret;
	पूर्ण

	/* configure buffering */
	port->current_buffer.num = 1;
	port->current_buffer.size = f->fmt.pix.sizeimage;
	अगर (port->क्रमmat.encoding == MMAL_ENCODING_JPEG) अणु
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "JPG - buf size now %d was %d\n",
			 f->fmt.pix.sizeimage,
			 port->current_buffer.size);
		port->current_buffer.size =
		    (f->fmt.pix.sizeimage < (100 << 10)) ?
		    (100 << 10) : f->fmt.pix.sizeimage;
	पूर्ण
	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "vid_cap - cur_buf.size set to %d\n", f->fmt.pix.sizeimage);
	port->current_buffer.alignment = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक mmal_setup_components(काष्ठा bm2835_mmal_dev *dev,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;
	काष्ठा vchiq_mmal_port *port = शून्य, *camera_port = शून्य;
	काष्ठा vchiq_mmal_component *encode_component = शून्य;
	काष्ठा mmal_fmt *mfmt = get_क्रमmat(f);
	u32 हटाओ_padding;

	अगर (!mfmt)
		वापस -EINVAL;

	अगर (dev->capture.encode_component) अणु
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "vid_cap - disconnect previous tunnel\n");

		/* Disconnect any previous connection */
		vchiq_mmal_port_connect_tunnel(dev->instance,
					       dev->capture.camera_port, शून्य);
		dev->capture.camera_port = शून्य;
		ret = vchiq_mmal_component_disable(dev->instance,
						   dev->capture.encode_component);
		अगर (ret)
			v4l2_err(&dev->v4l2_dev,
				 "Failed to disable encode component %d\n",
				 ret);

		dev->capture.encode_component = शून्य;
	पूर्ण
	/* क्रमmat dependent port setup */
	चयन (mfmt->mmal_component) अणु
	हाल COMP_CAMERA:
		/* Make a further decision on port based on resolution */
		अगर (f->fmt.pix.width <= max_video_width &&
		    f->fmt.pix.height <= max_video_height)
			camera_port =
			    &dev->component[COMP_CAMERA]->output[CAM_PORT_VIDEO];
		अन्यथा
			camera_port =
			    &dev->component[COMP_CAMERA]->output[CAM_PORT_CAPTURE];
		port = camera_port;
		अवरोध;
	हाल COMP_IMAGE_ENCODE:
		encode_component = dev->component[COMP_IMAGE_ENCODE];
		port = &dev->component[COMP_IMAGE_ENCODE]->output[0];
		camera_port =
		    &dev->component[COMP_CAMERA]->output[CAM_PORT_CAPTURE];
		अवरोध;
	हाल COMP_VIDEO_ENCODE:
		encode_component = dev->component[COMP_VIDEO_ENCODE];
		port = &dev->component[COMP_VIDEO_ENCODE]->output[0];
		camera_port =
		    &dev->component[COMP_CAMERA]->output[CAM_PORT_VIDEO];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!port)
		वापस -EINVAL;

	अगर (encode_component)
		camera_port->क्रमmat.encoding = MMAL_ENCODING_OPAQUE;
	अन्यथा
		camera_port->क्रमmat.encoding = mfmt->mmal;

	अगर (dev->rgb_bgr_swapped) अणु
		अगर (camera_port->क्रमmat.encoding == MMAL_ENCODING_RGB24)
			camera_port->क्रमmat.encoding = MMAL_ENCODING_BGR24;
		अन्यथा अगर (camera_port->क्रमmat.encoding == MMAL_ENCODING_BGR24)
			camera_port->क्रमmat.encoding = MMAL_ENCODING_RGB24;
	पूर्ण

	हटाओ_padding = mfmt->हटाओ_padding;
	vchiq_mmal_port_parameter_set(dev->instance, camera_port,
				      MMAL_PARAMETER_NO_IMAGE_PADDING,
				      &हटाओ_padding, माप(हटाओ_padding));

	camera_port->क्रमmat.encoding_variant = 0;
	camera_port->es.video.width = f->fmt.pix.width;
	camera_port->es.video.height = f->fmt.pix.height;
	camera_port->es.video.crop.x = 0;
	camera_port->es.video.crop.y = 0;
	camera_port->es.video.crop.width = f->fmt.pix.width;
	camera_port->es.video.crop.height = f->fmt.pix.height;
	camera_port->es.video.frame_rate.num = 0;
	camera_port->es.video.frame_rate.den = 1;
	camera_port->es.video.color_space = MMAL_COLOR_SPACE_JPEG_JFIF;

	ret = vchiq_mmal_port_set_क्रमmat(dev->instance, camera_port);

	अगर (!ret &&
	    camera_port ==
	    &dev->component[COMP_CAMERA]->output[CAM_PORT_VIDEO]) अणु
		ret = mmal_setup_video_component(dev, f);
	पूर्ण

	अगर (ret) अणु
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "%s failed to set format %dx%d %08X\n", __func__,
			 f->fmt.pix.width, f->fmt.pix.height,
			 f->fmt.pix.pixelक्रमmat);
		/* ensure capture is not going to be tried */
		dev->capture.port = शून्य;
		वापस ret;
	पूर्ण

	अगर (encode_component) अणु
		ret = mmal_setup_encode_component(dev, f, port,
						  camera_port,
						  encode_component);

		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* configure buffering */
		camera_port->current_buffer.num = 1;
		camera_port->current_buffer.size = f->fmt.pix.sizeimage;
		camera_port->current_buffer.alignment = 0;
	पूर्ण

	dev->capture.fmt = mfmt;
	dev->capture.stride = f->fmt.pix.bytesperline;
	dev->capture.width = camera_port->es.video.crop.width;
	dev->capture.height = camera_port->es.video.crop.height;
	dev->capture.buffersize = port->current_buffer.size;

	/* select port क्रम capture */
	dev->capture.port = port;
	dev->capture.camera_port = camera_port;
	dev->capture.encode_component = encode_component;
	v4l2_dbg(1, bcm2835_v4l2_debug,
		 &dev->v4l2_dev,
		"Set dev->capture.fmt %08X, %dx%d, stride %d, size %d",
		port->क्रमmat.encoding,
		dev->capture.width, dev->capture.height,
		dev->capture.stride, dev->capture.buffersize);

	/* toकरो: Need to convert the vchiq/mmal error पूर्णांकo a v4l2 error. */
	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;
	काष्ठा bm2835_mmal_dev *dev = video_drvdata(file);
	काष्ठा mmal_fmt *mfmt;

	/* try the क्रमmat to set valid parameters */
	ret = vidioc_try_fmt_vid_cap(file, priv, f);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev,
			 "vid_cap - vidioc_try_fmt_vid_cap failed\n");
		वापस ret;
	पूर्ण

	/* अगर a capture is running refuse to set क्रमmat */
	अगर (vb2_is_busy(&dev->capture.vb_vidq)) अणु
		v4l2_info(&dev->v4l2_dev, "%s device busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	/* If the क्रमmat is unsupported v4l2 says we should चयन to
	 * a supported one and not वापस an error.
	 */
	mfmt = get_क्रमmat(f);
	अगर (!mfmt) अणु
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "Fourcc format (0x%08x) unknown.\n",
			 f->fmt.pix.pixelक्रमmat);
		f->fmt.pix.pixelक्रमmat = क्रमmats[0].fourcc;
		mfmt = get_क्रमmat(f);
	पूर्ण

	ret = mmal_setup_components(dev, f);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev,
			 "%s: failed to setup mmal components: %d\n",
			 __func__, ret);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा bm2835_mmal_dev *dev = video_drvdata(file);
	अटल स्थिर काष्ठा v4l2_frmsize_stepwise sizes = अणु
		MIN_WIDTH, 0, 2,
		MIN_HEIGHT, 0, 2
	पूर्ण;
	पूर्णांक i;

	अगर (fsize->index)
		वापस -EINVAL;
	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++)
		अगर (क्रमmats[i].fourcc == fsize->pixel_क्रमmat)
			अवरोध;
	अगर (i == ARRAY_SIZE(क्रमmats))
		वापस -EINVAL;
	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	fsize->stepwise = sizes;
	fsize->stepwise.max_width = dev->max_width;
	fsize->stepwise.max_height = dev->max_height;
	वापस 0;
पूर्ण

/* समयperframe is arbitrary and continuous */
अटल पूर्णांक vidioc_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *priv,
				      काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा bm2835_mmal_dev *dev = video_drvdata(file);
	पूर्णांक i;

	अगर (fival->index)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++)
		अगर (क्रमmats[i].fourcc == fival->pixel_क्रमmat)
			अवरोध;
	अगर (i == ARRAY_SIZE(क्रमmats))
		वापस -EINVAL;

	/* regarding width & height - we support any within range */
	अगर (fival->width < MIN_WIDTH || fival->width > dev->max_width ||
	    fival->height < MIN_HEIGHT || fival->height > dev->max_height)
		वापस -EINVAL;

	fival->type = V4L2_FRMIVAL_TYPE_CONTINUOUS;

	/* fill in stepwise (step=1.0 is required by V4L2 spec) */
	fival->stepwise.min  = tpf_min;
	fival->stepwise.max  = tpf_max;
	fival->stepwise.step = (काष्ठा v4l2_fract) अणु1, 1पूर्ण;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_parm(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा bm2835_mmal_dev *dev = video_drvdata(file);

	अगर (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	parm->parm.capture.capability   = V4L2_CAP_TIMEPERFRAME;
	parm->parm.capture.समयperframe = dev->capture.समयperframe;
	parm->parm.capture.पढ़ोbuffers  = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_parm(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा bm2835_mmal_dev *dev = video_drvdata(file);
	काष्ठा v4l2_fract tpf;

	अगर (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	tpf = parm->parm.capture.समयperframe;

	/* tpf: अणु*, 0पूर्ण resets timing; clip to [min, max]*/
	tpf = tpf.denominator ? tpf : tpf_शेष;
	tpf = V4L2_FRACT_COMPARE(tpf, <, tpf_min) ? tpf_min : tpf;
	tpf = V4L2_FRACT_COMPARE(tpf, >, tpf_max) ? tpf_max : tpf;

	dev->capture.समयperframe = tpf;
	parm->parm.capture.समयperframe = tpf;
	parm->parm.capture.पढ़ोbuffers  = 1;
	parm->parm.capture.capability   = V4L2_CAP_TIMEPERFRAME;

	set_framerate_params(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops camera0_ioctl_ops = अणु
	/* overlay */
	.vidioc_क्रमागत_fmt_vid_overlay = vidioc_क्रमागत_fmt_vid_overlay,
	.vidioc_g_fmt_vid_overlay = vidioc_g_fmt_vid_overlay,
	.vidioc_try_fmt_vid_overlay = vidioc_try_fmt_vid_overlay,
	.vidioc_s_fmt_vid_overlay = vidioc_s_fmt_vid_overlay,
	.vidioc_overlay = vidioc_overlay,
	.vidioc_g_fbuf = vidioc_g_fbuf,

	/* inमाला_दो */
	.vidioc_क्रमागत_input = vidioc_क्रमागत_input,
	.vidioc_g_input = vidioc_g_input,
	.vidioc_s_input = vidioc_s_input,

	/* capture */
	.vidioc_querycap = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = vidioc_s_fmt_vid_cap,

	/* buffer management */
	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf = vb2_ioctl_prepare_buf,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_क्रमागत_framesizes = vidioc_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals = vidioc_क्रमागत_frameपूर्णांकervals,
	.vidioc_g_parm        = vidioc_g_parm,
	.vidioc_s_parm        = vidioc_s_parm,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,

	.vidioc_log_status = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

/* ------------------------------------------------------------------
 *	Driver init/finalise
 * ------------------------------------------------------------------
 */

अटल स्थिर काष्ठा v4l2_file_operations camera0_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.पढ़ो = vb2_fop_पढ़ो,
	.poll = vb2_fop_poll,
	.unlocked_ioctl = video_ioctl2,	/* V4L2 ioctl handler */
	.mmap = vb2_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा video_device vdev_ढाँचा = अणु
	.name = "camera0",
	.fops = &camera0_fops,
	.ioctl_ops = &camera0_ioctl_ops,
	.release = video_device_release_empty,
	.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_VIDEO_OVERLAY |
		       V4L2_CAP_STREAMING | V4L2_CAP_READWRITE,
पूर्ण;

/* Returns the number of cameras, and also the max resolution supported
 * by those cameras.
 */
अटल पूर्णांक get_num_cameras(काष्ठा vchiq_mmal_instance *instance,
			   अचिन्हित पूर्णांक resolutions[][2], पूर्णांक num_resolutions)
अणु
	पूर्णांक ret;
	काष्ठा vchiq_mmal_component  *cam_info_component;
	काष्ठा mmal_parameter_camera_info cam_info = अणु0पूर्ण;
	u32 param_size = माप(cam_info);
	पूर्णांक i;

	/* create a camera_info component */
	ret = vchiq_mmal_component_init(instance, "camera_info",
					&cam_info_component);
	अगर (ret < 0)
		/* Unusual failure - let's guess one camera. */
		वापस 1;

	अगर (vchiq_mmal_port_parameter_get(instance,
					  &cam_info_component->control,
					  MMAL_PARAMETER_CAMERA_INFO,
					  &cam_info,
					  &param_size)) अणु
		pr_info("Failed to get camera info\n");
	पूर्ण
	क्रम (i = 0;
	     i < min_t(अचिन्हित पूर्णांक, cam_info.num_cameras, num_resolutions);
	     i++) अणु
		resolutions[i][0] = cam_info.cameras[i].max_width;
		resolutions[i][1] = cam_info.cameras[i].max_height;
	पूर्ण

	vchiq_mmal_component_finalise(instance,
				      cam_info_component);

	वापस cam_info.num_cameras;
पूर्ण

अटल पूर्णांक set_camera_parameters(काष्ठा vchiq_mmal_instance *instance,
				 काष्ठा vchiq_mmal_component *camera,
				 काष्ठा bm2835_mmal_dev *dev)
अणु
	काष्ठा mmal_parameter_camera_config cam_config = अणु
		.max_stills_w = dev->max_width,
		.max_stills_h = dev->max_height,
		.stills_yuv422 = 1,
		.one_shot_stills = 1,
		.max_preview_video_w = (max_video_width > 1920) ?
						max_video_width : 1920,
		.max_preview_video_h = (max_video_height > 1088) ?
						max_video_height : 1088,
		.num_preview_video_frames = 3,
		.stills_capture_circular_buffer_height = 0,
		.fast_preview_resume = 0,
		.use_stc_बारtamp = MMAL_PARAM_TIMESTAMP_MODE_RAW_STC
	पूर्ण;

	वापस vchiq_mmal_port_parameter_set(instance, &camera->control,
					    MMAL_PARAMETER_CAMERA_CONFIG,
					    &cam_config, माप(cam_config));
पूर्ण

#घोषणा MAX_SUPPORTED_ENCODINGS 20

/* MMAL instance and component init */
अटल पूर्णांक mmal_init(काष्ठा bm2835_mmal_dev *dev)
अणु
	पूर्णांक ret;
	काष्ठा mmal_es_क्रमmat_local *क्रमmat;
	u32 supported_encodings[MAX_SUPPORTED_ENCODINGS];
	u32 param_size;
	काष्ठा vchiq_mmal_component  *camera;

	ret = vchiq_mmal_init(&dev->instance);
	अगर (ret < 0) अणु
		v4l2_err(&dev->v4l2_dev, "%s: vchiq mmal init failed %d\n",
			 __func__, ret);
		वापस ret;
	पूर्ण

	/* get the camera component पढ़ोy */
	ret = vchiq_mmal_component_init(dev->instance, "ril.camera",
					&dev->component[COMP_CAMERA]);
	अगर (ret < 0)
		जाओ unreg_mmal;

	camera = dev->component[COMP_CAMERA];
	अगर (camera->outमाला_दो < CAM_PORT_COUNT) अणु
		v4l2_err(&dev->v4l2_dev, "%s: too few camera outputs %d needed %d\n",
			 __func__, camera->outमाला_दो, CAM_PORT_COUNT);
		ret = -EINVAL;
		जाओ unreg_camera;
	पूर्ण

	ret = set_camera_parameters(dev->instance,
				    camera,
				    dev);
	अगर (ret < 0) अणु
		v4l2_err(&dev->v4l2_dev, "%s: unable to set camera parameters: %d\n",
			 __func__, ret);
		जाओ unreg_camera;
	पूर्ण

	/* There was an error in the firmware that meant the camera component
	 * produced BGR instead of RGB.
	 * This is now fixed, but in order to support the old firmwares, we
	 * have to check.
	 */
	dev->rgb_bgr_swapped = true;
	param_size = माप(supported_encodings);
	ret = vchiq_mmal_port_parameter_get(dev->instance,
					    &camera->output[CAM_PORT_CAPTURE],
					    MMAL_PARAMETER_SUPPORTED_ENCODINGS,
					    &supported_encodings,
					    &param_size);
	अगर (ret == 0) अणु
		पूर्णांक i;

		क्रम (i = 0; i < param_size / माप(u32); i++) अणु
			अगर (supported_encodings[i] == MMAL_ENCODING_BGR24) अणु
				/* Found BGR24 first - old firmware. */
				अवरोध;
			पूर्ण
			अगर (supported_encodings[i] == MMAL_ENCODING_RGB24) अणु
				/* Found RGB24 first
				 * new firmware, so use RGB24.
				 */
				dev->rgb_bgr_swapped = false;
			अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रमmat = &camera->output[CAM_PORT_PREVIEW].क्रमmat;

	क्रमmat->encoding = MMAL_ENCODING_OPAQUE;
	क्रमmat->encoding_variant = MMAL_ENCODING_I420;

	क्रमmat->es->video.width = 1024;
	क्रमmat->es->video.height = 768;
	क्रमmat->es->video.crop.x = 0;
	क्रमmat->es->video.crop.y = 0;
	क्रमmat->es->video.crop.width = 1024;
	क्रमmat->es->video.crop.height = 768;
	क्रमmat->es->video.frame_rate.num = 0; /* Rely on fps_range */
	क्रमmat->es->video.frame_rate.den = 1;

	क्रमmat = &camera->output[CAM_PORT_VIDEO].क्रमmat;

	क्रमmat->encoding = MMAL_ENCODING_OPAQUE;
	क्रमmat->encoding_variant = MMAL_ENCODING_I420;

	क्रमmat->es->video.width = 1024;
	क्रमmat->es->video.height = 768;
	क्रमmat->es->video.crop.x = 0;
	क्रमmat->es->video.crop.y = 0;
	क्रमmat->es->video.crop.width = 1024;
	क्रमmat->es->video.crop.height = 768;
	क्रमmat->es->video.frame_rate.num = 0; /* Rely on fps_range */
	क्रमmat->es->video.frame_rate.den = 1;

	क्रमmat = &camera->output[CAM_PORT_CAPTURE].क्रमmat;

	क्रमmat->encoding = MMAL_ENCODING_OPAQUE;

	क्रमmat->es->video.width = 2592;
	क्रमmat->es->video.height = 1944;
	क्रमmat->es->video.crop.x = 0;
	क्रमmat->es->video.crop.y = 0;
	क्रमmat->es->video.crop.width = 2592;
	क्रमmat->es->video.crop.height = 1944;
	क्रमmat->es->video.frame_rate.num = 0; /* Rely on fps_range */
	क्रमmat->es->video.frame_rate.den = 1;

	dev->capture.width = क्रमmat->es->video.width;
	dev->capture.height = क्रमmat->es->video.height;
	dev->capture.fmt = &क्रमmats[0];
	dev->capture.encode_component = शून्य;
	dev->capture.समयperframe = tpf_शेष;
	dev->capture.enc_profile = V4L2_MPEG_VIDEO_H264_PROखाता_HIGH;
	dev->capture.enc_level = V4L2_MPEG_VIDEO_H264_LEVEL_4_0;

	/* get the preview component पढ़ोy */
	ret = vchiq_mmal_component_init(dev->instance, "ril.video_render",
					&dev->component[COMP_PREVIEW]);
	अगर (ret < 0)
		जाओ unreg_camera;

	अगर (dev->component[COMP_PREVIEW]->inमाला_दो < 1) अणु
		ret = -EINVAL;
		v4l2_err(&dev->v4l2_dev, "%s: too few input ports %d needed %d\n",
			 __func__, dev->component[COMP_PREVIEW]->inमाला_दो, 1);
		जाओ unreg_preview;
	पूर्ण

	/* get the image encoder component पढ़ोy */
	ret = vchiq_mmal_component_init(dev->instance, "ril.image_encode",
					&dev->component[COMP_IMAGE_ENCODE]);
	अगर (ret < 0)
		जाओ unreg_preview;

	अगर (dev->component[COMP_IMAGE_ENCODE]->inमाला_दो < 1) अणु
		ret = -EINVAL;
		v4l2_err(&dev->v4l2_dev, "%s: too few input ports %d needed %d\n",
			 __func__, dev->component[COMP_IMAGE_ENCODE]->inमाला_दो,
			 1);
		जाओ unreg_image_encoder;
	पूर्ण

	/* get the video encoder component पढ़ोy */
	ret = vchiq_mmal_component_init(dev->instance, "ril.video_encode",
					&dev->component[COMP_VIDEO_ENCODE]);
	अगर (ret < 0)
		जाओ unreg_image_encoder;

	अगर (dev->component[COMP_VIDEO_ENCODE]->inमाला_दो < 1) अणु
		ret = -EINVAL;
		v4l2_err(&dev->v4l2_dev, "%s: too few input ports %d needed %d\n",
			 __func__, dev->component[COMP_VIDEO_ENCODE]->inमाला_दो,
			 1);
		जाओ unreg_vid_encoder;
	पूर्ण

	अणु
		काष्ठा vchiq_mmal_port *encoder_port =
			&dev->component[COMP_VIDEO_ENCODE]->output[0];
		encoder_port->क्रमmat.encoding = MMAL_ENCODING_H264;
		ret = vchiq_mmal_port_set_क्रमmat(dev->instance,
						 encoder_port);
	पूर्ण

	अणु
		अचिन्हित पूर्णांक enable = 1;

		vchiq_mmal_port_parameter_set(
			dev->instance,
			&dev->component[COMP_VIDEO_ENCODE]->control,
			MMAL_PARAMETER_VIDEO_IMMUTABLE_INPUT,
			&enable, माप(enable));

		vchiq_mmal_port_parameter_set(dev->instance,
					      &dev->component[COMP_VIDEO_ENCODE]->control,
					      MMAL_PARAMETER_MINIMISE_FRAGMENTATION,
					      &enable,
					      माप(enable));
	पूर्ण
	ret = bm2835_mmal_set_all_camera_controls(dev);
	अगर (ret < 0) अणु
		v4l2_err(&dev->v4l2_dev, "%s: failed to set all camera controls: %d\n",
			 __func__, ret);
		जाओ unreg_vid_encoder;
	पूर्ण

	वापस 0;

unreg_vid_encoder:
	pr_err("Cleanup: Destroy video encoder\n");
	vchiq_mmal_component_finalise(dev->instance,
				      dev->component[COMP_VIDEO_ENCODE]);

unreg_image_encoder:
	pr_err("Cleanup: Destroy image encoder\n");
	vchiq_mmal_component_finalise(dev->instance,
				      dev->component[COMP_IMAGE_ENCODE]);

unreg_preview:
	pr_err("Cleanup: Destroy video render\n");
	vchiq_mmal_component_finalise(dev->instance,
				      dev->component[COMP_PREVIEW]);

unreg_camera:
	pr_err("Cleanup: Destroy camera\n");
	vchiq_mmal_component_finalise(dev->instance,
				      dev->component[COMP_CAMERA]);

unreg_mmal:
	vchiq_mmal_finalise(dev->instance);
	वापस ret;
पूर्ण

अटल पूर्णांक bm2835_mmal_init_device(काष्ठा bm2835_mmal_dev *dev,
				   काष्ठा video_device *vfd)
अणु
	पूर्णांक ret;

	*vfd = vdev_ढाँचा;

	vfd->v4l2_dev = &dev->v4l2_dev;

	vfd->lock = &dev->mutex;

	vfd->queue = &dev->capture.vb_vidq;

	/* video device needs to be able to access instance data */
	video_set_drvdata(vfd, dev);

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO,
				    video_nr[dev->camera_num]);
	अगर (ret < 0)
		वापस ret;

	v4l2_info(vfd->v4l2_dev,
		  "V4L2 device registered as %s - stills mode > %dx%d\n",
		  video_device_node_name(vfd),
		  max_video_width, max_video_height);

	वापस 0;
पूर्ण

अटल व्योम bcm2835_cleanup_instance(काष्ठा bm2835_mmal_dev *dev)
अणु
	अगर (!dev)
		वापस;

	v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
		  video_device_node_name(&dev->vdev));

	video_unरेजिस्टर_device(&dev->vdev);

	अगर (dev->capture.encode_component) अणु
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "mmal_exit - disconnect tunnel\n");
		vchiq_mmal_port_connect_tunnel(dev->instance,
					       dev->capture.camera_port, शून्य);
		vchiq_mmal_component_disable(dev->instance,
					     dev->capture.encode_component);
	पूर्ण
	vchiq_mmal_component_disable(dev->instance,
				     dev->component[COMP_CAMERA]);

	vchiq_mmal_component_finalise(dev->instance,
				      dev->component[COMP_VIDEO_ENCODE]);

	vchiq_mmal_component_finalise(dev->instance,
				      dev->component[COMP_IMAGE_ENCODE]);

	vchiq_mmal_component_finalise(dev->instance,
				      dev->component[COMP_PREVIEW]);

	vchiq_mmal_component_finalise(dev->instance,
				      dev->component[COMP_CAMERA]);

	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);

	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	kमुक्त(dev);
पूर्ण

अटल काष्ठा v4l2_क्रमmat शेष_v4l2_क्रमmat = अणु
	.fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_JPEG,
	.fmt.pix.width = 1024,
	.fmt.pix.bytesperline = 0,
	.fmt.pix.height = 768,
	.fmt.pix.sizeimage = 1024 * 768,
पूर्ण;

अटल पूर्णांक bcm2835_mmal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा bm2835_mmal_dev *dev;
	काष्ठा vb2_queue *q;
	पूर्णांक camera;
	अचिन्हित पूर्णांक num_cameras;
	काष्ठा vchiq_mmal_instance *instance;
	अचिन्हित पूर्णांक resolutions[MAX_BCM2835_CAMERAS][2];
	पूर्णांक i;

	ret = vchiq_mmal_init(&instance);
	अगर (ret < 0)
		वापस ret;

	num_cameras = get_num_cameras(instance,
				      resolutions,
				      MAX_BCM2835_CAMERAS);

	अगर (num_cameras < 1) अणु
		ret = -ENODEV;
		जाओ cleanup_mmal;
	पूर्ण

	अगर (num_cameras > MAX_BCM2835_CAMERAS)
		num_cameras = MAX_BCM2835_CAMERAS;

	क्रम (camera = 0; camera < num_cameras; camera++) अणु
		dev = kzalloc(माप(*dev), GFP_KERNEL);
		अगर (!dev) अणु
			ret = -ENOMEM;
			जाओ cleanup_gdev;
		पूर्ण

		/* v4l2 core mutex used to protect all fops and v4l2 ioctls. */
		mutex_init(&dev->mutex);
		dev->max_width = resolutions[camera][0];
		dev->max_height = resolutions[camera][1];

		/* setup device शेषs */
		dev->overlay.w.left = 150;
		dev->overlay.w.top = 50;
		dev->overlay.w.width = 1024;
		dev->overlay.w.height = 768;
		dev->overlay.clipcount = 0;
		dev->overlay.field = V4L2_FIELD_NONE;
		dev->overlay.global_alpha = 255;

		dev->capture.fmt = &क्रमmats[3]; /* JPEG */

		/* v4l device registration */
		dev->camera_num = v4l2_device_set_name(&dev->v4l2_dev,
						       BM2835_MMAL_MODULE_NAME,
						       &camera_instance);
		ret = v4l2_device_रेजिस्टर(शून्य, &dev->v4l2_dev);
		अगर (ret) अणु
			dev_err(&pdev->dev, "%s: could not register V4L2 device: %d\n",
				__func__, ret);
			जाओ मुक्त_dev;
		पूर्ण

		/* setup v4l controls */
		ret = bm2835_mmal_init_controls(dev, &dev->ctrl_handler);
		अगर (ret < 0) अणु
			v4l2_err(&dev->v4l2_dev, "%s: could not init controls: %d\n",
				 __func__, ret);
			जाओ unreg_dev;
		पूर्ण
		dev->v4l2_dev.ctrl_handler = &dev->ctrl_handler;

		/* mmal init */
		dev->instance = instance;
		ret = mmal_init(dev);
		अगर (ret < 0) अणु
			v4l2_err(&dev->v4l2_dev, "%s: mmal init failed: %d\n",
				 __func__, ret);
			जाओ unreg_dev;
		पूर्ण
		/* initialize queue */
		q = &dev->capture.vb_vidq;
		स_रखो(q, 0, माप(*q));
		q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ;
		q->drv_priv = dev;
		q->buf_काष्ठा_size = माप(काष्ठा vb2_mmal_buffer);
		q->ops = &bm2835_mmal_video_qops;
		q->mem_ops = &vb2_vदो_स्मृति_memops;
		q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
		q->lock = &dev->mutex;
		ret = vb2_queue_init(q);
		अगर (ret < 0)
			जाओ unreg_dev;

		/* initialise video devices */
		ret = bm2835_mmal_init_device(dev, &dev->vdev);
		अगर (ret < 0) अणु
			v4l2_err(&dev->v4l2_dev, "%s: could not init device: %d\n",
				 __func__, ret);
			जाओ unreg_dev;
		पूर्ण

		/* Really want to call vidioc_s_fmt_vid_cap with the शेष
		 * क्रमmat, but currently the APIs करोn't join up.
		 */
		ret = mmal_setup_components(dev, &शेष_v4l2_क्रमmat);
		अगर (ret < 0) अणु
			v4l2_err(&dev->v4l2_dev, "%s: could not setup components: %d\n",
				 __func__, ret);
			जाओ unreg_dev;
		पूर्ण

		v4l2_info(&dev->v4l2_dev,
			  "Broadcom 2835 MMAL video capture ver %s loaded.\n",
			  BM2835_MMAL_VERSION);

		gdev[camera] = dev;
	पूर्ण
	वापस 0;

unreg_dev:
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

मुक्त_dev:
	kमुक्त(dev);

cleanup_gdev:
	क्रम (i = 0; i < camera; i++) अणु
		bcm2835_cleanup_instance(gdev[i]);
		gdev[i] = शून्य;
	पूर्ण

cleanup_mmal:
	vchiq_mmal_finalise(instance);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm2835_mmal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक camera;
	काष्ठा vchiq_mmal_instance *instance = gdev[0]->instance;

	क्रम (camera = 0; camera < MAX_BCM2835_CAMERAS; camera++) अणु
		bcm2835_cleanup_instance(gdev[camera]);
		gdev[camera] = शून्य;
	पूर्ण
	vchiq_mmal_finalise(instance);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bcm2835_camera_driver = अणु
	.probe		= bcm2835_mmal_probe,
	.हटाओ		= bcm2835_mmal_हटाओ,
	.driver		= अणु
		.name	= "bcm2835-camera",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(bcm2835_camera_driver)

MODULE_DESCRIPTION("Broadcom 2835 MMAL video capture");
MODULE_AUTHOR("Vincent Sanders");
MODULE_LICENSE("GPL");
MODULE_VERSION(BM2835_MMAL_VERSION);
MODULE_ALIAS("platform:bcm2835-camera");
