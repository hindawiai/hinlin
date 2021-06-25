<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2011-2018 Magewell Electronics Co., Ltd. (Nanjing)
 * All rights reserved.
 * Author: Yong Deng <yong.deng@magewell.com>
 */

#समावेश <linux/of.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/videobuf2-v4l2.h>

#समावेश "sun6i_csi.h"
#समावेश "sun6i_video.h"

/* This is got from BSP sources. */
#घोषणा MIN_WIDTH	(32)
#घोषणा MIN_HEIGHT	(32)
#घोषणा MAX_WIDTH	(4800)
#घोषणा MAX_HEIGHT	(4800)

काष्ठा sun6i_csi_buffer अणु
	काष्ठा vb2_v4l2_buffer		vb;
	काष्ठा list_head		list;

	dma_addr_t			dma_addr;
	bool				queued_to_csi;
पूर्ण;

अटल स्थिर u32 supported_pixक्रमmats[] = अणु
	V4L2_PIX_FMT_SBGGR8,
	V4L2_PIX_FMT_SGBRG8,
	V4L2_PIX_FMT_SGRBG8,
	V4L2_PIX_FMT_SRGGB8,
	V4L2_PIX_FMT_SBGGR10,
	V4L2_PIX_FMT_SGBRG10,
	V4L2_PIX_FMT_SGRBG10,
	V4L2_PIX_FMT_SRGGB10,
	V4L2_PIX_FMT_SBGGR12,
	V4L2_PIX_FMT_SGBRG12,
	V4L2_PIX_FMT_SGRBG12,
	V4L2_PIX_FMT_SRGGB12,
	V4L2_PIX_FMT_YUYV,
	V4L2_PIX_FMT_YVYU,
	V4L2_PIX_FMT_UYVY,
	V4L2_PIX_FMT_VYUY,
	V4L2_PIX_FMT_HM12,
	V4L2_PIX_FMT_NV12,
	V4L2_PIX_FMT_NV21,
	V4L2_PIX_FMT_YUV420,
	V4L2_PIX_FMT_YVU420,
	V4L2_PIX_FMT_NV16,
	V4L2_PIX_FMT_NV61,
	V4L2_PIX_FMT_YUV422P,
	V4L2_PIX_FMT_RGB565,
	V4L2_PIX_FMT_RGB565X,
	V4L2_PIX_FMT_JPEG,
पूर्ण;

अटल bool is_pixक्रमmat_valid(अचिन्हित पूर्णांक pixक्रमmat)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(supported_pixक्रमmats); i++)
		अगर (supported_pixक्रमmats[i] == pixक्रमmat)
			वापस true;

	वापस false;
पूर्ण

अटल काष्ठा v4l2_subdev *
sun6i_video_remote_subdev(काष्ठा sun6i_video *video, u32 *pad)
अणु
	काष्ठा media_pad *remote;

	remote = media_entity_remote_pad(&video->pad);

	अगर (!remote || !is_media_entity_v4l2_subdev(remote->entity))
		वापस शून्य;

	अगर (pad)
		*pad = remote->index;

	वापस media_entity_to_v4l2_subdev(remote->entity);
पूर्ण

अटल पूर्णांक sun6i_video_queue_setup(काष्ठा vb2_queue *vq,
				   अचिन्हित पूर्णांक *nbuffers,
				   अचिन्हित पूर्णांक *nplanes,
				   अचिन्हित पूर्णांक sizes[],
				   काष्ठा device *alloc_devs[])
अणु
	काष्ठा sun6i_video *video = vb2_get_drv_priv(vq);
	अचिन्हित पूर्णांक size = video->fmt.fmt.pix.sizeimage;

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_video_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा sun6i_csi_buffer *buf =
			container_of(vbuf, काष्ठा sun6i_csi_buffer, vb);
	काष्ठा sun6i_video *video = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ size = video->fmt.fmt.pix.sizeimage;

	अगर (vb2_plane_size(vb, 0) < size) अणु
		v4l2_err(video->vdev.v4l2_dev, "buffer too small (%lu < %lu)\n",
			 vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, size);

	buf->dma_addr = vb2_dma_contig_plane_dma_addr(vb, 0);

	vbuf->field = video->fmt.fmt.pix.field;

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_video_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा sun6i_video *video = vb2_get_drv_priv(vq);
	काष्ठा sun6i_csi_buffer *buf;
	काष्ठा sun6i_csi_buffer *next_buf;
	काष्ठा sun6i_csi_config config;
	काष्ठा v4l2_subdev *subdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	video->sequence = 0;

	ret = media_pipeline_start(&video->vdev.entity, &video->vdev.pipe);
	अगर (ret < 0)
		जाओ clear_dma_queue;

	अगर (video->mbus_code == 0) अणु
		ret = -EINVAL;
		जाओ stop_media_pipeline;
	पूर्ण

	subdev = sun6i_video_remote_subdev(video, शून्य);
	अगर (!subdev) अणु
		ret = -EINVAL;
		जाओ stop_media_pipeline;
	पूर्ण

	config.pixelक्रमmat = video->fmt.fmt.pix.pixelक्रमmat;
	config.code = video->mbus_code;
	config.field = video->fmt.fmt.pix.field;
	config.width = video->fmt.fmt.pix.width;
	config.height = video->fmt.fmt.pix.height;

	ret = sun6i_csi_update_config(video->csi, &config);
	अगर (ret < 0)
		जाओ stop_media_pipeline;

	spin_lock_irqsave(&video->dma_queue_lock, flags);

	buf = list_first_entry(&video->dma_queue,
			       काष्ठा sun6i_csi_buffer, list);
	buf->queued_to_csi = true;
	sun6i_csi_update_buf_addr(video->csi, buf->dma_addr);

	sun6i_csi_set_stream(video->csi, true);

	/*
	 * CSI will lookup the next dma buffer क्रम next frame beक्रमe the
	 * the current frame करोne IRQ triggered. This is not करोcumented
	 * but reported by Ondधej Jirman.
	 * The BSP code has workaround क्रम this too. It skip to mark the
	 * first buffer as frame करोne क्रम VB2 and pass the second buffer
	 * to CSI in the first frame करोne ISR call. Then in second frame
	 * करोne ISR call, it mark the first buffer as frame करोne क्रम VB2
	 * and pass the third buffer to CSI. And so on. The bad thing is
	 * that the first buffer will be written twice and the first frame
	 * is dropped even the queued buffer is sufficient.
	 * So, I make some improvement here. Pass the next buffer to CSI
	 * just follow starting the CSI. In this हाल, the first frame
	 * will be stored in first buffer, second frame in second buffer.
	 * This method is used to aव्योम dropping the first frame, it
	 * would also drop frame when lacking of queued buffer.
	 */
	next_buf = list_next_entry(buf, list);
	next_buf->queued_to_csi = true;
	sun6i_csi_update_buf_addr(video->csi, next_buf->dma_addr);

	spin_unlock_irqrestore(&video->dma_queue_lock, flags);

	ret = v4l2_subdev_call(subdev, video, s_stream, 1);
	अगर (ret && ret != -ENOIOCTLCMD)
		जाओ stop_csi_stream;

	वापस 0;

stop_csi_stream:
	sun6i_csi_set_stream(video->csi, false);
stop_media_pipeline:
	media_pipeline_stop(&video->vdev.entity);
clear_dma_queue:
	spin_lock_irqsave(&video->dma_queue_lock, flags);
	list_क्रम_each_entry(buf, &video->dma_queue, list)
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
	INIT_LIST_HEAD(&video->dma_queue);
	spin_unlock_irqrestore(&video->dma_queue_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम sun6i_video_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा sun6i_video *video = vb2_get_drv_priv(vq);
	काष्ठा v4l2_subdev *subdev;
	अचिन्हित दीर्घ flags;
	काष्ठा sun6i_csi_buffer *buf;

	subdev = sun6i_video_remote_subdev(video, शून्य);
	अगर (subdev)
		v4l2_subdev_call(subdev, video, s_stream, 0);

	sun6i_csi_set_stream(video->csi, false);

	media_pipeline_stop(&video->vdev.entity);

	/* Release all active buffers */
	spin_lock_irqsave(&video->dma_queue_lock, flags);
	list_क्रम_each_entry(buf, &video->dma_queue, list)
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	INIT_LIST_HEAD(&video->dma_queue);
	spin_unlock_irqrestore(&video->dma_queue_lock, flags);
पूर्ण

अटल व्योम sun6i_video_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा sun6i_csi_buffer *buf =
			container_of(vbuf, काष्ठा sun6i_csi_buffer, vb);
	काष्ठा sun6i_video *video = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&video->dma_queue_lock, flags);
	buf->queued_to_csi = false;
	list_add_tail(&buf->list, &video->dma_queue);
	spin_unlock_irqrestore(&video->dma_queue_lock, flags);
पूर्ण

व्योम sun6i_video_frame_करोne(काष्ठा sun6i_video *video)
अणु
	काष्ठा sun6i_csi_buffer *buf;
	काष्ठा sun6i_csi_buffer *next_buf;
	काष्ठा vb2_v4l2_buffer *vbuf;

	spin_lock(&video->dma_queue_lock);

	buf = list_first_entry(&video->dma_queue,
			       काष्ठा sun6i_csi_buffer, list);
	अगर (list_is_last(&buf->list, &video->dma_queue)) अणु
		dev_dbg(video->csi->dev, "Frame dropped!\n");
		जाओ unlock;
	पूर्ण

	next_buf = list_next_entry(buf, list);
	/* If a new buffer (#next_buf) had not been queued to CSI, the old
	 * buffer (#buf) is still holding by CSI क्रम storing the next
	 * frame. So, we queue a new buffer (#next_buf) to CSI then रुको
	 * क्रम next ISR call.
	 */
	अगर (!next_buf->queued_to_csi) अणु
		next_buf->queued_to_csi = true;
		sun6i_csi_update_buf_addr(video->csi, next_buf->dma_addr);
		dev_dbg(video->csi->dev, "Frame dropped!\n");
		जाओ unlock;
	पूर्ण

	list_del(&buf->list);
	vbuf = &buf->vb;
	vbuf->vb2_buf.बारtamp = kसमय_get_ns();
	vbuf->sequence = video->sequence;
	vb2_buffer_करोne(&vbuf->vb2_buf, VB2_BUF_STATE_DONE);

	/* Prepare buffer क्रम next frame but one.  */
	अगर (!list_is_last(&next_buf->list, &video->dma_queue)) अणु
		next_buf = list_next_entry(next_buf, list);
		next_buf->queued_to_csi = true;
		sun6i_csi_update_buf_addr(video->csi, next_buf->dma_addr);
	पूर्ण अन्यथा अणु
		dev_dbg(video->csi->dev, "Next frame will be dropped!\n");
	पूर्ण

unlock:
	video->sequence++;
	spin_unlock(&video->dma_queue_lock);
पूर्ण

अटल स्थिर काष्ठा vb2_ops sun6i_csi_vb2_ops = अणु
	.queue_setup		= sun6i_video_queue_setup,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
	.buf_prepare		= sun6i_video_buffer_prepare,
	.start_streaming	= sun6i_video_start_streaming,
	.stop_streaming		= sun6i_video_stop_streaming,
	.buf_queue		= sun6i_video_buffer_queue,
पूर्ण;

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा sun6i_video *video = video_drvdata(file);

	strscpy(cap->driver, "sun6i-video", माप(cap->driver));
	strscpy(cap->card, video->vdev.name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 video->csi->dev->of_node->name);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	u32 index = f->index;

	अगर (index >= ARRAY_SIZE(supported_pixक्रमmats))
		वापस -EINVAL;

	f->pixelक्रमmat = supported_pixक्रमmats[index];

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा sun6i_video *video = video_drvdata(file);

	*fmt = video->fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_video_try_fmt(काष्ठा sun6i_video *video,
			       काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat *pixfmt = &f->fmt.pix;
	पूर्णांक bpp;

	अगर (!is_pixक्रमmat_valid(pixfmt->pixelक्रमmat))
		pixfmt->pixelक्रमmat = supported_pixक्रमmats[0];

	v4l_bound_align_image(&pixfmt->width, MIN_WIDTH, MAX_WIDTH, 1,
			      &pixfmt->height, MIN_HEIGHT, MAX_WIDTH, 1, 1);

	bpp = sun6i_csi_get_bpp(pixfmt->pixelक्रमmat);
	pixfmt->bytesperline = (pixfmt->width * bpp) >> 3;
	pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height;

	अगर (pixfmt->field == V4L2_FIELD_ANY)
		pixfmt->field = V4L2_FIELD_NONE;

	pixfmt->colorspace = V4L2_COLORSPACE_RAW;
	pixfmt->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	pixfmt->quantization = V4L2_QUANTIZATION_DEFAULT;
	pixfmt->xfer_func = V4L2_XFER_FUNC_DEFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_video_set_fmt(काष्ठा sun6i_video *video, काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;

	ret = sun6i_video_try_fmt(video, f);
	अगर (ret)
		वापस ret;

	video->fmt = *f;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा sun6i_video *video = video_drvdata(file);

	अगर (vb2_is_busy(&video->vb2_vidq))
		वापस -EBUSY;

	वापस sun6i_video_set_fmt(video, f);
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा sun6i_video *video = video_drvdata(file);

	वापस sun6i_video_try_fmt(video, f);
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_input *inp)
अणु
	अगर (inp->index != 0)
		वापस -EINVAL;

	strscpy(inp->name, "camera", माप(inp->name));
	inp->type = V4L2_INPUT_TYPE_CAMERA;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक i)
अणु
	अगर (i != 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops sun6i_video_ioctl_ops = अणु
	.vidioc_querycap		= vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= vidioc_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= vidioc_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		= vidioc_try_fmt_vid_cap,

	.vidioc_क्रमागत_input		= vidioc_क्रमागत_input,
	.vidioc_s_input			= vidioc_s_input,
	.vidioc_g_input			= vidioc_g_input,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,

	.vidioc_log_status		= v4l2_ctrl_log_status,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 file operations
 */
अटल पूर्णांक sun6i_video_खोलो(काष्ठा file *file)
अणु
	काष्ठा sun6i_video *video = video_drvdata(file);
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&video->lock))
		वापस -ERESTARTSYS;

	ret = v4l2_fh_खोलो(file);
	अगर (ret < 0)
		जाओ unlock;

	ret = v4l2_pipeline_pm_get(&video->vdev.entity);
	अगर (ret < 0)
		जाओ fh_release;

	/* check अगर alपढ़ोy घातered */
	अगर (!v4l2_fh_is_singular_file(file))
		जाओ unlock;

	ret = sun6i_csi_set_घातer(video->csi, true);
	अगर (ret < 0)
		जाओ fh_release;

	mutex_unlock(&video->lock);
	वापस 0;

fh_release:
	v4l2_fh_release(file);
unlock:
	mutex_unlock(&video->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक sun6i_video_बंद(काष्ठा file *file)
अणु
	काष्ठा sun6i_video *video = video_drvdata(file);
	bool last_fh;

	mutex_lock(&video->lock);

	last_fh = v4l2_fh_is_singular_file(file);

	_vb2_fop_release(file, शून्य);

	v4l2_pipeline_pm_put(&video->vdev.entity);

	अगर (last_fh)
		sun6i_csi_set_घातer(video->csi, false);

	mutex_unlock(&video->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations sun6i_video_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= sun6i_video_खोलो,
	.release	= sun6i_video_बंद,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= vb2_fop_mmap,
	.poll		= vb2_fop_poll
पूर्ण;

/* -----------------------------------------------------------------------------
 * Media Operations
 */
अटल पूर्णांक sun6i_video_link_validate_get_क्रमmat(काष्ठा media_pad *pad,
						काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	अगर (is_media_entity_v4l2_subdev(pad->entity)) अणु
		काष्ठा v4l2_subdev *sd =
				media_entity_to_v4l2_subdev(pad->entity);

		fmt->which = V4L2_SUBDEV_FORMAT_ACTIVE;
		fmt->pad = pad->index;
		वापस v4l2_subdev_call(sd, pad, get_fmt, शून्य, fmt);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sun6i_video_link_validate(काष्ठा media_link *link)
अणु
	काष्ठा video_device *vdev = container_of(link->sink->entity,
						 काष्ठा video_device, entity);
	काष्ठा sun6i_video *video = video_get_drvdata(vdev);
	काष्ठा v4l2_subdev_क्रमmat source_fmt;
	पूर्णांक ret;

	video->mbus_code = 0;

	अगर (!media_entity_remote_pad(link->sink->entity->pads)) अणु
		dev_info(video->csi->dev,
			 "video node %s pad not connected\n", vdev->name);
		वापस -ENOLINK;
	पूर्ण

	ret = sun6i_video_link_validate_get_क्रमmat(link->source, &source_fmt);
	अगर (ret < 0)
		वापस ret;

	अगर (!sun6i_csi_is_क्रमmat_supported(video->csi,
					   video->fmt.fmt.pix.pixelक्रमmat,
					   source_fmt.क्रमmat.code)) अणु
		dev_err(video->csi->dev,
			"Unsupported pixformat: 0x%x with mbus code: 0x%x!\n",
			video->fmt.fmt.pix.pixelक्रमmat,
			source_fmt.क्रमmat.code);
		वापस -EPIPE;
	पूर्ण

	अगर (source_fmt.क्रमmat.width != video->fmt.fmt.pix.width ||
	    source_fmt.क्रमmat.height != video->fmt.fmt.pix.height) अणु
		dev_err(video->csi->dev,
			"Wrong width or height %ux%u (%ux%u expected)\n",
			video->fmt.fmt.pix.width, video->fmt.fmt.pix.height,
			source_fmt.क्रमmat.width, source_fmt.क्रमmat.height);
		वापस -EPIPE;
	पूर्ण

	video->mbus_code = source_fmt.क्रमmat.code;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा media_entity_operations sun6i_video_media_ops = अणु
	.link_validate = sun6i_video_link_validate
पूर्ण;

पूर्णांक sun6i_video_init(काष्ठा sun6i_video *video, काष्ठा sun6i_csi *csi,
		     स्थिर अक्षर *name)
अणु
	काष्ठा video_device *vdev = &video->vdev;
	काष्ठा vb2_queue *vidq = &video->vb2_vidq;
	काष्ठा v4l2_क्रमmat fmt = अणु 0 पूर्ण;
	पूर्णांक ret;

	video->csi = csi;

	/* Initialize the media entity... */
	video->pad.flags = MEDIA_PAD_FL_SINK | MEDIA_PAD_FL_MUST_CONNECT;
	vdev->entity.ops = &sun6i_video_media_ops;
	ret = media_entity_pads_init(&vdev->entity, 1, &video->pad);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&video->lock);

	INIT_LIST_HEAD(&video->dma_queue);
	spin_lock_init(&video->dma_queue_lock);

	video->sequence = 0;

	/* Setup शेष क्रमmat */
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.pixelक्रमmat = supported_pixक्रमmats[0];
	fmt.fmt.pix.width = 1280;
	fmt.fmt.pix.height = 720;
	fmt.fmt.pix.field = V4L2_FIELD_NONE;
	sun6i_video_set_fmt(video, &fmt);

	/* Initialize videobuf2 queue */
	vidq->type			= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vidq->io_modes			= VB2_MMAP | VB2_DMABUF;
	vidq->drv_priv			= video;
	vidq->buf_काष्ठा_size		= माप(काष्ठा sun6i_csi_buffer);
	vidq->ops			= &sun6i_csi_vb2_ops;
	vidq->mem_ops			= &vb2_dma_contig_memops;
	vidq->बारtamp_flags		= V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	vidq->lock			= &video->lock;
	/* Make sure non-dropped frame */
	vidq->min_buffers_needed	= 3;
	vidq->dev			= csi->dev;

	ret = vb2_queue_init(vidq);
	अगर (ret) अणु
		v4l2_err(&csi->v4l2_dev, "vb2_queue_init failed: %d\n", ret);
		जाओ clean_entity;
	पूर्ण

	/* Register video device */
	strscpy(vdev->name, name, माप(vdev->name));
	vdev->release		= video_device_release_empty;
	vdev->fops		= &sun6i_video_fops;
	vdev->ioctl_ops		= &sun6i_video_ioctl_ops;
	vdev->vfl_type		= VFL_TYPE_VIDEO;
	vdev->vfl_dir		= VFL_सूची_RX;
	vdev->v4l2_dev		= &csi->v4l2_dev;
	vdev->queue		= vidq;
	vdev->lock		= &video->lock;
	vdev->device_caps	= V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE;
	video_set_drvdata(vdev, video);

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0) अणु
		v4l2_err(&csi->v4l2_dev,
			 "video_register_device failed: %d\n", ret);
		जाओ clean_entity;
	पूर्ण

	वापस 0;

clean_entity:
	media_entity_cleanup(&video->vdev.entity);
	mutex_destroy(&video->lock);
	वापस ret;
पूर्ण

व्योम sun6i_video_cleanup(काष्ठा sun6i_video *video)
अणु
	vb2_video_unरेजिस्टर_device(&video->vdev);
	media_entity_cleanup(&video->vdev.entity);
	mutex_destroy(&video->lock);
पूर्ण
