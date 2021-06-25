<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	uvc_v4l2.c  --  USB Video Class Gadget driver
 *
 *	Copyright (C) 2009-2010
 *	    Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/usb/g_uvc.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/रुको.h>

#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश "f_uvc.h"
#समावेश "uvc.h"
#समावेश "uvc_queue.h"
#समावेश "uvc_video.h"
#समावेश "uvc_v4l2.h"

/* --------------------------------------------------------------------------
 * Requests handling
 */

अटल पूर्णांक
uvc_send_response(काष्ठा uvc_device *uvc, काष्ठा uvc_request_data *data)
अणु
	काष्ठा usb_composite_dev *cdev = uvc->func.config->cdev;
	काष्ठा usb_request *req = uvc->control_req;

	अगर (data->length < 0)
		वापस usb_ep_set_halt(cdev->gadget->ep0);

	req->length = min_t(अचिन्हित पूर्णांक, uvc->event_length, data->length);
	req->zero = data->length < uvc->event_length;

	स_नकल(req->buf, data->data, req->length);

	वापस usb_ep_queue(cdev->gadget->ep0, req, GFP_KERNEL);
पूर्ण

/* --------------------------------------------------------------------------
 * V4L2 ioctls
 */

काष्ठा uvc_क्रमmat अणु
	u8 bpp;
	u32 fcc;
पूर्ण;

अटल काष्ठा uvc_क्रमmat uvc_क्रमmats[] = अणु
	अणु 16, V4L2_PIX_FMT_YUYV  पूर्ण,
	अणु 0,  V4L2_PIX_FMT_MJPEG पूर्ण,
पूर्ण;

अटल पूर्णांक
uvc_v4l2_querycap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_capability *cap)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);
	काष्ठा usb_composite_dev *cdev = uvc->func.config->cdev;

	strlcpy(cap->driver, "g_uvc", माप(cap->driver));
	strlcpy(cap->card, cdev->gadget->name, माप(cap->card));
	strlcpy(cap->bus_info, dev_name(&cdev->gadget->dev),
		माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक
uvc_v4l2_get_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);
	काष्ठा uvc_video *video = &uvc->video;

	fmt->fmt.pix.pixelक्रमmat = video->fcc;
	fmt->fmt.pix.width = video->width;
	fmt->fmt.pix.height = video->height;
	fmt->fmt.pix.field = V4L2_FIELD_NONE;
	fmt->fmt.pix.bytesperline = video->bpp * video->width / 8;
	fmt->fmt.pix.sizeimage = video->imagesize;
	fmt->fmt.pix.colorspace = V4L2_COLORSPACE_SRGB;
	fmt->fmt.pix.priv = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
uvc_v4l2_set_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);
	काष्ठा uvc_video *video = &uvc->video;
	काष्ठा uvc_क्रमmat *क्रमmat;
	अचिन्हित पूर्णांक imagesize;
	अचिन्हित पूर्णांक bpl;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(uvc_क्रमmats); ++i) अणु
		क्रमmat = &uvc_क्रमmats[i];
		अगर (क्रमmat->fcc == fmt->fmt.pix.pixelक्रमmat)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(uvc_क्रमmats)) अणु
		uvcg_info(&uvc->func, "Unsupported format 0x%08x.\n",
			  fmt->fmt.pix.pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	bpl = क्रमmat->bpp * fmt->fmt.pix.width / 8;
	imagesize = bpl ? bpl * fmt->fmt.pix.height : fmt->fmt.pix.sizeimage;

	video->fcc = क्रमmat->fcc;
	video->bpp = क्रमmat->bpp;
	video->width = fmt->fmt.pix.width;
	video->height = fmt->fmt.pix.height;
	video->imagesize = imagesize;

	fmt->fmt.pix.field = V4L2_FIELD_NONE;
	fmt->fmt.pix.bytesperline = bpl;
	fmt->fmt.pix.sizeimage = imagesize;
	fmt->fmt.pix.colorspace = V4L2_COLORSPACE_SRGB;
	fmt->fmt.pix.priv = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
uvc_v4l2_reqbufs(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_requestbuffers *b)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);
	काष्ठा uvc_video *video = &uvc->video;

	अगर (b->type != video->queue.queue.type)
		वापस -EINVAL;

	वापस uvcg_alloc_buffers(&video->queue, b);
पूर्ण

अटल पूर्णांक
uvc_v4l2_querybuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);
	काष्ठा uvc_video *video = &uvc->video;

	वापस uvcg_query_buffer(&video->queue, b);
पूर्ण

अटल पूर्णांक
uvc_v4l2_qbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);
	काष्ठा uvc_video *video = &uvc->video;
	पूर्णांक ret;

	ret = uvcg_queue_buffer(&video->queue, b);
	अगर (ret < 0)
		वापस ret;

	schedule_work(&video->pump);

	वापस ret;
पूर्ण

अटल पूर्णांक
uvc_v4l2_dqbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);
	काष्ठा uvc_video *video = &uvc->video;

	वापस uvcg_dequeue_buffer(&video->queue, b, file->f_flags & O_NONBLOCK);
पूर्ण

अटल पूर्णांक
uvc_v4l2_streamon(काष्ठा file *file, व्योम *fh, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);
	काष्ठा uvc_video *video = &uvc->video;
	पूर्णांक ret;

	अगर (type != video->queue.queue.type)
		वापस -EINVAL;

	/* Enable UVC video. */
	ret = uvcg_video_enable(video, 1);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Complete the alternate setting selection setup phase now that
	 * userspace is पढ़ोy to provide video frames.
	 */
	uvc_function_setup_जारी(uvc);
	uvc->state = UVC_STATE_STREAMING;

	वापस 0;
पूर्ण

अटल पूर्णांक
uvc_v4l2_streamoff(काष्ठा file *file, व्योम *fh, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);
	काष्ठा uvc_video *video = &uvc->video;

	अगर (type != video->queue.queue.type)
		वापस -EINVAL;

	वापस uvcg_video_enable(video, 0);
पूर्ण

अटल पूर्णांक
uvc_v4l2_subscribe_event(काष्ठा v4l2_fh *fh,
			 स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	अगर (sub->type < UVC_EVENT_FIRST || sub->type > UVC_EVENT_LAST)
		वापस -EINVAL;

	वापस v4l2_event_subscribe(fh, sub, 2, शून्य);
पूर्ण

अटल पूर्णांक
uvc_v4l2_unsubscribe_event(काष्ठा v4l2_fh *fh,
			   स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	वापस v4l2_event_unsubscribe(fh, sub);
पूर्ण

अटल दीर्घ
uvc_v4l2_ioctl_शेष(काष्ठा file *file, व्योम *fh, bool valid_prio,
		       अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);

	चयन (cmd) अणु
	हाल UVCIOC_SEND_RESPONSE:
		वापस uvc_send_response(uvc, arg);

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

स्थिर काष्ठा v4l2_ioctl_ops uvc_v4l2_ioctl_ops = अणु
	.vidioc_querycap = uvc_v4l2_querycap,
	.vidioc_g_fmt_vid_out = uvc_v4l2_get_क्रमmat,
	.vidioc_s_fmt_vid_out = uvc_v4l2_set_क्रमmat,
	.vidioc_reqbufs = uvc_v4l2_reqbufs,
	.vidioc_querybuf = uvc_v4l2_querybuf,
	.vidioc_qbuf = uvc_v4l2_qbuf,
	.vidioc_dqbuf = uvc_v4l2_dqbuf,
	.vidioc_streamon = uvc_v4l2_streamon,
	.vidioc_streamoff = uvc_v4l2_streamoff,
	.vidioc_subscribe_event = uvc_v4l2_subscribe_event,
	.vidioc_unsubscribe_event = uvc_v4l2_unsubscribe_event,
	.vidioc_शेष = uvc_v4l2_ioctl_शेष,
पूर्ण;

/* --------------------------------------------------------------------------
 * V4L2
 */

अटल पूर्णांक
uvc_v4l2_खोलो(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);
	काष्ठा uvc_file_handle *handle;

	handle = kzalloc(माप(*handle), GFP_KERNEL);
	अगर (handle == शून्य)
		वापस -ENOMEM;

	v4l2_fh_init(&handle->vfh, vdev);
	v4l2_fh_add(&handle->vfh);

	handle->device = &uvc->video;
	file->निजी_data = &handle->vfh;

	uvc_function_connect(uvc);
	वापस 0;
पूर्ण

अटल पूर्णांक
uvc_v4l2_release(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);
	काष्ठा uvc_file_handle *handle = to_uvc_file_handle(file->निजी_data);
	काष्ठा uvc_video *video = handle->device;

	uvc_function_disconnect(uvc);

	mutex_lock(&video->mutex);
	uvcg_video_enable(video, 0);
	uvcg_मुक्त_buffers(&video->queue);
	mutex_unlock(&video->mutex);

	file->निजी_data = शून्य;
	v4l2_fh_del(&handle->vfh);
	v4l2_fh_निकास(&handle->vfh);
	kमुक्त(handle);

	वापस 0;
पूर्ण

अटल पूर्णांक
uvc_v4l2_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);

	वापस uvcg_queue_mmap(&uvc->video.queue, vma);
पूर्ण

अटल __poll_t
uvc_v4l2_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);

	वापस uvcg_queue_poll(&uvc->video.queue, file, रुको);
पूर्ण

#अगर_अघोषित CONFIG_MMU
अटल अचिन्हित दीर्घ uvcg_v4l2_get_unmapped_area(काष्ठा file *file,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा uvc_device *uvc = video_get_drvdata(vdev);

	वापस uvcg_queue_get_unmapped_area(&uvc->video.queue, pgoff);
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा v4l2_file_operations uvc_v4l2_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= uvc_v4l2_खोलो,
	.release	= uvc_v4l2_release,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= uvc_v4l2_mmap,
	.poll		= uvc_v4l2_poll,
#अगर_अघोषित CONFIG_MMU
	.get_unmapped_area = uvcg_v4l2_get_unmapped_area,
#पूर्ण_अगर
पूर्ण;

