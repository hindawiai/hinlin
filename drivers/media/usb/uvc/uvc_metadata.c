<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      uvc_metadata.c  --  USB Video Class driver - Metadata handling
 *
 *      Copyright (C) 2016
 *          Guennadi Liakhovetski (guennadi.liakhovetski@पूर्णांकel.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "uvcvideo.h"

/* -----------------------------------------------------------------------------
 * V4L2 ioctls
 */

अटल पूर्णांक uvc_meta_v4l2_querycap(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_capability *cap)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा uvc_streaming *stream = video_get_drvdata(vfh->vdev);
	काष्ठा uvc_video_chain *chain = stream->chain;

	strscpy(cap->driver, "uvcvideo", माप(cap->driver));
	strscpy(cap->card, vfh->vdev->name, माप(cap->card));
	usb_make_path(stream->dev->udev, cap->bus_info, माप(cap->bus_info));
	cap->capabilities = V4L2_CAP_DEVICE_CAPS | V4L2_CAP_STREAMING
			  | chain->caps;

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_meta_v4l2_get_क्रमmat(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा uvc_streaming *stream = video_get_drvdata(vfh->vdev);
	काष्ठा v4l2_meta_क्रमmat *fmt = &क्रमmat->fmt.meta;

	अगर (क्रमmat->type != vfh->vdev->queue->type)
		वापस -EINVAL;

	स_रखो(fmt, 0, माप(*fmt));

	fmt->dataक्रमmat = stream->meta.क्रमmat;
	fmt->buffersize = UVC_METADATA_BUF_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_meta_v4l2_try_क्रमmat(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा uvc_streaming *stream = video_get_drvdata(vfh->vdev);
	काष्ठा uvc_device *dev = stream->dev;
	काष्ठा v4l2_meta_क्रमmat *fmt = &क्रमmat->fmt.meta;
	u32 fmeta = fmt->dataक्रमmat;

	अगर (क्रमmat->type != vfh->vdev->queue->type)
		वापस -EINVAL;

	स_रखो(fmt, 0, माप(*fmt));

	fmt->dataक्रमmat = fmeta == dev->info->meta_क्रमmat
			? fmeta : V4L2_META_FMT_UVC;
	fmt->buffersize = UVC_METADATA_BUF_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक uvc_meta_v4l2_set_क्रमmat(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा uvc_streaming *stream = video_get_drvdata(vfh->vdev);
	काष्ठा v4l2_meta_क्रमmat *fmt = &क्रमmat->fmt.meta;
	पूर्णांक ret;

	ret = uvc_meta_v4l2_try_क्रमmat(file, fh, क्रमmat);
	अगर (ret < 0)
		वापस ret;

	/*
	 * We could in principle चयन at any समय, also during streaming.
	 * Metadata buffers would still be perfectly parseable, but it's more
	 * consistent and cleaner to disallow that.
	 */
	mutex_lock(&stream->mutex);

	अगर (uvc_queue_allocated(&stream->queue))
		ret = -EBUSY;
	अन्यथा
		stream->meta.क्रमmat = fmt->dataक्रमmat;

	mutex_unlock(&stream->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक uvc_meta_v4l2_क्रमागत_क्रमmats(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_fmtdesc *fdesc)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा uvc_streaming *stream = video_get_drvdata(vfh->vdev);
	काष्ठा uvc_device *dev = stream->dev;
	u32 index = fdesc->index;

	अगर (fdesc->type != vfh->vdev->queue->type ||
	    index > 1U || (index && !dev->info->meta_क्रमmat))
		वापस -EINVAL;

	स_रखो(fdesc, 0, माप(*fdesc));

	fdesc->type = vfh->vdev->queue->type;
	fdesc->index = index;
	fdesc->pixelक्रमmat = index ? dev->info->meta_क्रमmat : V4L2_META_FMT_UVC;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops uvc_meta_ioctl_ops = अणु
	.vidioc_querycap		= uvc_meta_v4l2_querycap,
	.vidioc_g_fmt_meta_cap		= uvc_meta_v4l2_get_क्रमmat,
	.vidioc_s_fmt_meta_cap		= uvc_meta_v4l2_set_क्रमmat,
	.vidioc_try_fmt_meta_cap	= uvc_meta_v4l2_try_क्रमmat,
	.vidioc_क्रमागत_fmt_meta_cap	= uvc_meta_v4l2_क्रमागत_क्रमmats,
	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 File Operations
 */

अटल स्थिर काष्ठा v4l2_file_operations uvc_meta_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = video_ioctl2,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.poll = vb2_fop_poll,
	.mmap = vb2_fop_mmap,
पूर्ण;

पूर्णांक uvc_meta_रेजिस्टर(काष्ठा uvc_streaming *stream)
अणु
	काष्ठा uvc_device *dev = stream->dev;
	काष्ठा video_device *vdev = &stream->meta.vdev;
	काष्ठा uvc_video_queue *queue = &stream->meta.queue;

	stream->meta.क्रमmat = V4L2_META_FMT_UVC;

	/*
	 * The video पूर्णांकerface queue uses manual locking and thus करोes not set
	 * the queue poपूर्णांकer. Set it manually here.
	 */
	vdev->queue = &queue->queue;

	वापस uvc_रेजिस्टर_video_device(dev, stream, vdev, queue,
					 V4L2_BUF_TYPE_META_CAPTURE,
					 &uvc_meta_fops, &uvc_meta_ioctl_ops);
पूर्ण
