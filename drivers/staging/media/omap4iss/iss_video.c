<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * TI OMAP4 ISS V4L2 Driver - Generic video node
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Author: Sergio Aguirre <sergio.a.aguirre@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>

#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mc.h>

#समावेश <यंत्र/cacheflush.h>

#समावेश "iss_video.h"
#समावेश "iss.h"

/* -----------------------------------------------------------------------------
 * Helper functions
 */

अटल काष्ठा iss_क्रमmat_info क्रमmats[] = अणु
	अणु MEDIA_BUS_FMT_Y8_1X8, MEDIA_BUS_FMT_Y8_1X8,
	  MEDIA_BUS_FMT_Y8_1X8, MEDIA_BUS_FMT_Y8_1X8,
	  V4L2_PIX_FMT_GREY, 8, पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_1X10, MEDIA_BUS_FMT_Y10_1X10,
	  MEDIA_BUS_FMT_Y10_1X10, MEDIA_BUS_FMT_Y8_1X8,
	  V4L2_PIX_FMT_Y10, 10, पूर्ण,
	अणु MEDIA_BUS_FMT_Y12_1X12, MEDIA_BUS_FMT_Y10_1X10,
	  MEDIA_BUS_FMT_Y12_1X12, MEDIA_BUS_FMT_Y8_1X8,
	  V4L2_PIX_FMT_Y12, 12, पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR8_1X8, MEDIA_BUS_FMT_SBGGR8_1X8,
	  MEDIA_BUS_FMT_SBGGR8_1X8, MEDIA_BUS_FMT_SBGGR8_1X8,
	  V4L2_PIX_FMT_SBGGR8, 8, पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG8_1X8, MEDIA_BUS_FMT_SGBRG8_1X8,
	  MEDIA_BUS_FMT_SGBRG8_1X8, MEDIA_BUS_FMT_SGBRG8_1X8,
	  V4L2_PIX_FMT_SGBRG8, 8, पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, MEDIA_BUS_FMT_SGRBG8_1X8,
	  MEDIA_BUS_FMT_SGRBG8_1X8, MEDIA_BUS_FMT_SGRBG8_1X8,
	  V4L2_PIX_FMT_SGRBG8, 8, पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB8_1X8, MEDIA_BUS_FMT_SRGGB8_1X8,
	  MEDIA_BUS_FMT_SRGGB8_1X8, MEDIA_BUS_FMT_SRGGB8_1X8,
	  V4L2_PIX_FMT_SRGGB8, 8, पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8, MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8,
	  MEDIA_BUS_FMT_SGRBG10_1X10, 0,
	  V4L2_PIX_FMT_SGRBG10DPCM8, 8, पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_1X10, MEDIA_BUS_FMT_SBGGR10_1X10,
	  MEDIA_BUS_FMT_SBGGR10_1X10, MEDIA_BUS_FMT_SBGGR8_1X8,
	  V4L2_PIX_FMT_SBGGR10, 10, पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_1X10, MEDIA_BUS_FMT_SGBRG10_1X10,
	  MEDIA_BUS_FMT_SGBRG10_1X10, MEDIA_BUS_FMT_SGBRG8_1X8,
	  V4L2_PIX_FMT_SGBRG10, 10, पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, MEDIA_BUS_FMT_SGRBG10_1X10,
	  MEDIA_BUS_FMT_SGRBG10_1X10, MEDIA_BUS_FMT_SGRBG8_1X8,
	  V4L2_PIX_FMT_SGRBG10, 10, पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, MEDIA_BUS_FMT_SRGGB10_1X10,
	  MEDIA_BUS_FMT_SRGGB10_1X10, MEDIA_BUS_FMT_SRGGB8_1X8,
	  V4L2_PIX_FMT_SRGGB10, 10, पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR12_1X12, MEDIA_BUS_FMT_SBGGR10_1X10,
	  MEDIA_BUS_FMT_SBGGR12_1X12, MEDIA_BUS_FMT_SBGGR8_1X8,
	  V4L2_PIX_FMT_SBGGR12, 12, पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG12_1X12, MEDIA_BUS_FMT_SGBRG10_1X10,
	  MEDIA_BUS_FMT_SGBRG12_1X12, MEDIA_BUS_FMT_SGBRG8_1X8,
	  V4L2_PIX_FMT_SGBRG12, 12, पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG12_1X12, MEDIA_BUS_FMT_SGRBG10_1X10,
	  MEDIA_BUS_FMT_SGRBG12_1X12, MEDIA_BUS_FMT_SGRBG8_1X8,
	  V4L2_PIX_FMT_SGRBG12, 12, पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB12_1X12, MEDIA_BUS_FMT_SRGGB10_1X10,
	  MEDIA_BUS_FMT_SRGGB12_1X12, MEDIA_BUS_FMT_SRGGB8_1X8,
	  V4L2_PIX_FMT_SRGGB12, 12, पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_1X16, MEDIA_BUS_FMT_UYVY8_1X16,
	  MEDIA_BUS_FMT_UYVY8_1X16, 0,
	  V4L2_PIX_FMT_UYVY, 16, पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_1X16, MEDIA_BUS_FMT_YUYV8_1X16,
	  MEDIA_BUS_FMT_YUYV8_1X16, 0,
	  V4L2_PIX_FMT_YUYV, 16, पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_1_5X8, MEDIA_BUS_FMT_YUYV8_1_5X8,
	  MEDIA_BUS_FMT_YUYV8_1_5X8, 0,
	  V4L2_PIX_FMT_NV12, 8, पूर्ण,
पूर्ण;

स्थिर काष्ठा iss_क्रमmat_info *
omap4iss_video_क्रमmat_info(u32 code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); ++i) अणु
		अगर (क्रमmats[i].code == code)
			वापस &क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * iss_video_mbus_to_pix - Convert v4l2_mbus_framefmt to v4l2_pix_क्रमmat
 * @video: ISS video instance
 * @mbus: v4l2_mbus_framefmt क्रमmat (input)
 * @pix: v4l2_pix_क्रमmat क्रमmat (output)
 *
 * Fill the output pix काष्ठाure with inक्रमmation from the input mbus क्रमmat.
 * The bytesperline and sizeimage fields are computed from the requested bytes
 * per line value in the pix क्रमmat and inक्रमmation from the video instance.
 *
 * Return the number of padding bytes at end of line.
 */
अटल अचिन्हित पूर्णांक iss_video_mbus_to_pix(स्थिर काष्ठा iss_video *video,
					  स्थिर काष्ठा v4l2_mbus_framefmt *mbus,
					  काष्ठा v4l2_pix_क्रमmat *pix)
अणु
	अचिन्हित पूर्णांक bpl = pix->bytesperline;
	अचिन्हित पूर्णांक min_bpl;
	अचिन्हित पूर्णांक i;

	स_रखो(pix, 0, माप(*pix));
	pix->width = mbus->width;
	pix->height = mbus->height;

	/*
	 * Skip the last क्रमmat in the loop so that it will be selected अगर no
	 * match is found.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats) - 1; ++i) अणु
		अगर (क्रमmats[i].code == mbus->code)
			अवरोध;
	पूर्ण

	min_bpl = pix->width * ALIGN(क्रमmats[i].bpp, 8) / 8;

	/*
	 * Clamp the requested bytes per line value. If the maximum bytes per
	 * line value is zero, the module करोesn't support user configurable line
	 * sizes. Override the requested value with the minimum in that हाल.
	 */
	अगर (video->bpl_max)
		bpl = clamp(bpl, min_bpl, video->bpl_max);
	अन्यथा
		bpl = min_bpl;

	अगर (!video->bpl_zero_padding || bpl != min_bpl)
		bpl = ALIGN(bpl, video->bpl_alignment);

	pix->pixelक्रमmat = क्रमmats[i].pixelक्रमmat;
	pix->bytesperline = bpl;
	pix->sizeimage = pix->bytesperline * pix->height;
	pix->colorspace = mbus->colorspace;
	pix->field = mbus->field;

	/* FIXME: Special हाल क्रम NV12! We should make this nicer... */
	अगर (pix->pixelक्रमmat == V4L2_PIX_FMT_NV12)
		pix->sizeimage += (pix->bytesperline * pix->height) / 2;

	वापस bpl - min_bpl;
पूर्ण

अटल व्योम iss_video_pix_to_mbus(स्थिर काष्ठा v4l2_pix_क्रमmat *pix,
				  काष्ठा v4l2_mbus_framefmt *mbus)
अणु
	अचिन्हित पूर्णांक i;

	स_रखो(mbus, 0, माप(*mbus));
	mbus->width = pix->width;
	mbus->height = pix->height;

	/*
	 * Skip the last क्रमmat in the loop so that it will be selected अगर no
	 * match is found.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats) - 1; ++i) अणु
		अगर (क्रमmats[i].pixelक्रमmat == pix->pixelक्रमmat)
			अवरोध;
	पूर्ण

	mbus->code = क्रमmats[i].code;
	mbus->colorspace = pix->colorspace;
	mbus->field = pix->field;
पूर्ण

अटल काष्ठा v4l2_subdev *
iss_video_remote_subdev(काष्ठा iss_video *video, u32 *pad)
अणु
	काष्ठा media_pad *remote;

	remote = media_entity_remote_pad(&video->pad);

	अगर (!remote || !is_media_entity_v4l2_subdev(remote->entity))
		वापस शून्य;

	अगर (pad)
		*pad = remote->index;

	वापस media_entity_to_v4l2_subdev(remote->entity);
पूर्ण

/* Return a poपूर्णांकer to the ISS video instance at the far end of the pipeline. */
अटल काष्ठा iss_video *
iss_video_far_end(काष्ठा iss_video *video)
अणु
	काष्ठा media_graph graph;
	काष्ठा media_entity *entity = &video->video.entity;
	काष्ठा media_device *mdev = entity->graph_obj.mdev;
	काष्ठा iss_video *far_end = शून्य;

	mutex_lock(&mdev->graph_mutex);

	अगर (media_graph_walk_init(&graph, mdev)) अणु
		mutex_unlock(&mdev->graph_mutex);
		वापस शून्य;
	पूर्ण

	media_graph_walk_start(&graph, entity);

	जबतक ((entity = media_graph_walk_next(&graph))) अणु
		अगर (entity == &video->video.entity)
			जारी;

		अगर (!is_media_entity_v4l2_video_device(entity))
			जारी;

		far_end = to_iss_video(media_entity_to_video_device(entity));
		अगर (far_end->type != video->type)
			अवरोध;

		far_end = शून्य;
	पूर्ण

	mutex_unlock(&mdev->graph_mutex);

	media_graph_walk_cleanup(&graph);

	वापस far_end;
पूर्ण

अटल पूर्णांक
__iss_video_get_क्रमmat(काष्ठा iss_video *video,
		       काष्ठा v4l2_mbus_framefmt *क्रमmat)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt;
	काष्ठा v4l2_subdev *subdev;
	u32 pad;
	पूर्णांक ret;

	subdev = iss_video_remote_subdev(video, &pad);
	अगर (!subdev)
		वापस -EINVAL;

	स_रखो(&fmt, 0, माप(fmt));
	fmt.pad = pad;
	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;

	mutex_lock(&video->mutex);
	ret = v4l2_subdev_call(subdev, pad, get_fmt, शून्य, &fmt);
	mutex_unlock(&video->mutex);

	अगर (ret)
		वापस ret;

	*क्रमmat = fmt.क्रमmat;
	वापस 0;
पूर्ण

अटल पूर्णांक
iss_video_check_क्रमmat(काष्ठा iss_video *video, काष्ठा iss_video_fh *vfh)
अणु
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	काष्ठा v4l2_pix_क्रमmat pixfmt;
	पूर्णांक ret;

	ret = __iss_video_get_क्रमmat(video, &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	pixfmt.bytesperline = 0;
	ret = iss_video_mbus_to_pix(video, &क्रमmat, &pixfmt);

	अगर (vfh->क्रमmat.fmt.pix.pixelक्रमmat != pixfmt.pixelक्रमmat ||
	    vfh->क्रमmat.fmt.pix.height != pixfmt.height ||
	    vfh->क्रमmat.fmt.pix.width != pixfmt.width ||
	    vfh->क्रमmat.fmt.pix.bytesperline != pixfmt.bytesperline ||
	    vfh->क्रमmat.fmt.pix.sizeimage != pixfmt.sizeimage)
		वापस -EINVAL;

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * Video queue operations
 */

अटल पूर्णांक iss_video_queue_setup(काष्ठा vb2_queue *vq,
				 अचिन्हित पूर्णांक *count, अचिन्हित पूर्णांक *num_planes,
				 अचिन्हित पूर्णांक sizes[],
				 काष्ठा device *alloc_devs[])
अणु
	काष्ठा iss_video_fh *vfh = vb2_get_drv_priv(vq);
	काष्ठा iss_video *video = vfh->video;

	/* Revisit multi-planar support क्रम NV12 */
	*num_planes = 1;

	sizes[0] = vfh->क्रमmat.fmt.pix.sizeimage;
	अगर (sizes[0] == 0)
		वापस -EINVAL;

	*count = min(*count, video->capture_mem / PAGE_ALIGN(sizes[0]));

	वापस 0;
पूर्ण

अटल व्योम iss_video_buf_cleanup(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा iss_buffer *buffer = container_of(vbuf, काष्ठा iss_buffer, vb);

	अगर (buffer->iss_addr)
		buffer->iss_addr = 0;
पूर्ण

अटल पूर्णांक iss_video_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा iss_video_fh *vfh = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा iss_buffer *buffer = container_of(vbuf, काष्ठा iss_buffer, vb);
	काष्ठा iss_video *video = vfh->video;
	अचिन्हित दीर्घ size = vfh->क्रमmat.fmt.pix.sizeimage;
	dma_addr_t addr;

	अगर (vb2_plane_size(vb, 0) < size)
		वापस -ENOBUFS;

	addr = vb2_dma_contig_plane_dma_addr(vb, 0);
	अगर (!IS_ALIGNED(addr, 32)) अणु
		dev_dbg(video->iss->dev,
			"Buffer address must be aligned to 32 bytes boundary.\n");
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, size);
	buffer->iss_addr = addr;
	वापस 0;
पूर्ण

अटल व्योम iss_video_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा iss_video_fh *vfh = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा iss_video *video = vfh->video;
	काष्ठा iss_buffer *buffer = container_of(vbuf, काष्ठा iss_buffer, vb);
	काष्ठा iss_pipeline *pipe = to_iss_pipeline(&video->video.entity);
	अचिन्हित दीर्घ flags;
	bool empty;

	spin_lock_irqsave(&video->qlock, flags);

	/*
	 * Mark the buffer is faulty and give it back to the queue immediately
	 * अगर the video node has रेजिस्टरed an error. vb2 will perक्रमm the same
	 * check when preparing the buffer, but that is inherently racy, so we
	 * need to handle the race condition with an authoritative check here.
	 */
	अगर (unlikely(video->error)) अणु
		vb2_buffer_करोne(vb, VB2_BUF_STATE_ERROR);
		spin_unlock_irqrestore(&video->qlock, flags);
		वापस;
	पूर्ण

	empty = list_empty(&video->dmaqueue);
	list_add_tail(&buffer->list, &video->dmaqueue);

	spin_unlock_irqrestore(&video->qlock, flags);

	अगर (empty) अणु
		क्रमागत iss_pipeline_state state;
		अचिन्हित पूर्णांक start;

		अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
			state = ISS_PIPELINE_QUEUE_OUTPUT;
		अन्यथा
			state = ISS_PIPELINE_QUEUE_INPUT;

		spin_lock_irqsave(&pipe->lock, flags);
		pipe->state |= state;
		video->ops->queue(video, buffer);
		video->dmaqueue_flags |= ISS_VIDEO_DMAQUEUE_QUEUED;

		start = iss_pipeline_पढ़ोy(pipe);
		अगर (start)
			pipe->state |= ISS_PIPELINE_STREAM;
		spin_unlock_irqrestore(&pipe->lock, flags);

		अगर (start)
			omap4iss_pipeline_set_stream(pipe,
						ISS_PIPELINE_STREAM_SINGLESHOT);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vb2_ops iss_video_vb2ops = अणु
	.queue_setup	= iss_video_queue_setup,
	.buf_prepare	= iss_video_buf_prepare,
	.buf_queue	= iss_video_buf_queue,
	.buf_cleanup	= iss_video_buf_cleanup,
पूर्ण;

/*
 * omap4iss_video_buffer_next - Complete the current buffer and वापस the next
 * @video: ISS video object
 *
 * Remove the current video buffer from the DMA queue and fill its बारtamp,
 * field count and state fields beक्रमe waking up its completion handler.
 *
 * For capture video nodes, the buffer state is set to VB2_BUF_STATE_DONE अगर no
 * error has been flagged in the pipeline, or to VB2_BUF_STATE_ERROR otherwise.
 *
 * The DMA queue is expected to contain at least one buffer.
 *
 * Return a poपूर्णांकer to the next buffer in the DMA queue, or शून्य अगर the queue is
 * empty.
 */
काष्ठा iss_buffer *omap4iss_video_buffer_next(काष्ठा iss_video *video)
अणु
	काष्ठा iss_pipeline *pipe = to_iss_pipeline(&video->video.entity);
	क्रमागत iss_pipeline_state state;
	काष्ठा iss_buffer *buf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&video->qlock, flags);
	अगर (WARN_ON(list_empty(&video->dmaqueue))) अणु
		spin_unlock_irqrestore(&video->qlock, flags);
		वापस शून्य;
	पूर्ण

	buf = list_first_entry(&video->dmaqueue, काष्ठा iss_buffer,
			       list);
	list_del(&buf->list);
	spin_unlock_irqrestore(&video->qlock, flags);

	buf->vb.vb2_buf.बारtamp = kसमय_get_ns();

	/*
	 * Do frame number propagation only अगर this is the output video node.
	 * Frame number either comes from the CSI receivers or it माला_लो
	 * incremented here अगर H3A is not active.
	 * Note: There is no guarantee that the output buffer will finish
	 * first, so the input number might lag behind by 1 in some हालs.
	 */
	अगर (video == pipe->output && !pipe->करो_propagation)
		buf->vb.sequence =
			atomic_inc_वापस(&pipe->frame_number);
	अन्यथा
		buf->vb.sequence = atomic_पढ़ो(&pipe->frame_number);

	vb2_buffer_करोne(&buf->vb.vb2_buf, pipe->error ?
			VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
	pipe->error = false;

	spin_lock_irqsave(&video->qlock, flags);
	अगर (list_empty(&video->dmaqueue)) अणु
		spin_unlock_irqrestore(&video->qlock, flags);
		अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
			state = ISS_PIPELINE_QUEUE_OUTPUT
			      | ISS_PIPELINE_STREAM;
		अन्यथा
			state = ISS_PIPELINE_QUEUE_INPUT
			      | ISS_PIPELINE_STREAM;

		spin_lock_irqsave(&pipe->lock, flags);
		pipe->state &= ~state;
		अगर (video->pipe.stream_state == ISS_PIPELINE_STREAM_CONTINUOUS)
			video->dmaqueue_flags |= ISS_VIDEO_DMAQUEUE_UNDERRUN;
		spin_unlock_irqrestore(&pipe->lock, flags);
		वापस शून्य;
	पूर्ण

	अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE && pipe->input) अणु
		spin_lock(&pipe->lock);
		pipe->state &= ~ISS_PIPELINE_STREAM;
		spin_unlock(&pipe->lock);
	पूर्ण

	buf = list_first_entry(&video->dmaqueue, काष्ठा iss_buffer,
			       list);
	spin_unlock_irqrestore(&video->qlock, flags);
	buf->vb.vb2_buf.state = VB2_BUF_STATE_ACTIVE;
	वापस buf;
पूर्ण

/*
 * omap4iss_video_cancel_stream - Cancel stream on a video node
 * @video: ISS video object
 *
 * Cancelling a stream mark all buffers on the video node as erroneous and makes
 * sure no new buffer can be queued.
 */
व्योम omap4iss_video_cancel_stream(काष्ठा iss_video *video)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&video->qlock, flags);

	जबतक (!list_empty(&video->dmaqueue)) अणु
		काष्ठा iss_buffer *buf;

		buf = list_first_entry(&video->dmaqueue, काष्ठा iss_buffer,
				       list);
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण

	vb2_queue_error(video->queue);
	video->error = true;

	spin_unlock_irqrestore(&video->qlock, flags);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 ioctls
 */

अटल पूर्णांक
iss_video_querycap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_capability *cap)
अणु
	काष्ठा iss_video *video = video_drvdata(file);

	strscpy(cap->driver, ISS_VIDEO_DRIVER_NAME, माप(cap->driver));
	strscpy(cap->card, video->video.name, माप(cap->card));
	strscpy(cap->bus_info, "media", माप(cap->bus_info));
	cap->capabilities = V4L2_CAP_DEVICE_CAPS | V4L2_CAP_STREAMING
			  | V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_VIDEO_OUTPUT;

	वापस 0;
पूर्ण

अटल पूर्णांक
iss_video_क्रमागत_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा iss_video *video = video_drvdata(file);
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	अचिन्हित पूर्णांक index = f->index;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (f->type != video->type)
		वापस -EINVAL;

	ret = __iss_video_get_क्रमmat(video, &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); ++i) अणु
		स्थिर काष्ठा iss_क्रमmat_info *info = &क्रमmats[i];

		अगर (क्रमmat.code != info->code)
			जारी;

		अगर (index == 0) अणु
			f->pixelक्रमmat = info->pixelक्रमmat;
			वापस 0;
		पूर्ण

		index--;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
iss_video_get_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा iss_video_fh *vfh = to_iss_video_fh(fh);
	काष्ठा iss_video *video = video_drvdata(file);

	अगर (क्रमmat->type != video->type)
		वापस -EINVAL;

	mutex_lock(&video->mutex);
	*क्रमmat = vfh->क्रमmat;
	mutex_unlock(&video->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
iss_video_set_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा iss_video_fh *vfh = to_iss_video_fh(fh);
	काष्ठा iss_video *video = video_drvdata(file);
	काष्ठा v4l2_mbus_framefmt fmt;

	अगर (क्रमmat->type != video->type)
		वापस -EINVAL;

	mutex_lock(&video->mutex);

	/*
	 * Fill the bytesperline and sizeimage fields by converting to media bus
	 * क्रमmat and back to pixel क्रमmat.
	 */
	iss_video_pix_to_mbus(&क्रमmat->fmt.pix, &fmt);
	iss_video_mbus_to_pix(video, &fmt, &क्रमmat->fmt.pix);

	vfh->क्रमmat = *क्रमmat;

	mutex_unlock(&video->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक
iss_video_try_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा iss_video *video = video_drvdata(file);
	काष्ठा v4l2_subdev_क्रमmat fmt;
	काष्ठा v4l2_subdev *subdev;
	u32 pad;
	पूर्णांक ret;

	अगर (क्रमmat->type != video->type)
		वापस -EINVAL;

	subdev = iss_video_remote_subdev(video, &pad);
	अगर (!subdev)
		वापस -EINVAL;

	iss_video_pix_to_mbus(&क्रमmat->fmt.pix, &fmt.क्रमmat);

	fmt.pad = pad;
	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(subdev, pad, get_fmt, शून्य, &fmt);
	अगर (ret)
		वापस ret;

	iss_video_mbus_to_pix(video, &fmt.क्रमmat, &क्रमmat->fmt.pix);
	वापस 0;
पूर्ण

अटल पूर्णांक
iss_video_get_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *sel)
अणु
	काष्ठा iss_video *video = video_drvdata(file);
	काष्ठा v4l2_subdev_क्रमmat क्रमmat;
	काष्ठा v4l2_subdev *subdev;
	काष्ठा v4l2_subdev_selection sdsel = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = sel->target,
	पूर्ण;
	u32 pad;
	पूर्णांक ret;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		अगर (video->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
			वापस -EINVAL;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
		अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	subdev = iss_video_remote_subdev(video, &pad);
	अगर (!subdev)
		वापस -EINVAL;

	/*
	 * Try the get selection operation first and fallback to get क्रमmat अगर
	 * not implemented.
	 */
	sdsel.pad = pad;
	ret = v4l2_subdev_call(subdev, pad, get_selection, शून्य, &sdsel);
	अगर (!ret)
		sel->r = sdsel.r;
	अगर (ret != -ENOIOCTLCMD)
		वापस ret;

	क्रमmat.pad = pad;
	क्रमmat.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(subdev, pad, get_fmt, शून्य, &क्रमmat);
	अगर (ret < 0)
		वापस ret == -ENOIOCTLCMD ? -ENOTTY : ret;

	sel->r.left = 0;
	sel->r.top = 0;
	sel->r.width = क्रमmat.क्रमmat.width;
	sel->r.height = क्रमmat.क्रमmat.height;

	वापस 0;
पूर्ण

अटल पूर्णांक
iss_video_set_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *sel)
अणु
	काष्ठा iss_video *video = video_drvdata(file);
	काष्ठा v4l2_subdev *subdev;
	काष्ठा v4l2_subdev_selection sdsel = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = sel->target,
		.flags = sel->flags,
		.r = sel->r,
	पूर्ण;
	u32 pad;
	पूर्णांक ret;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		अगर (video->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
			वापस -EINVAL;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	subdev = iss_video_remote_subdev(video, &pad);
	अगर (!subdev)
		वापस -EINVAL;

	sdsel.pad = pad;
	mutex_lock(&video->mutex);
	ret = v4l2_subdev_call(subdev, pad, set_selection, शून्य, &sdsel);
	mutex_unlock(&video->mutex);
	अगर (!ret)
		sel->r = sdsel.r;

	वापस ret == -ENOIOCTLCMD ? -ENOTTY : ret;
पूर्ण

अटल पूर्णांक
iss_video_get_param(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा iss_video_fh *vfh = to_iss_video_fh(fh);
	काष्ठा iss_video *video = video_drvdata(file);

	अगर (video->type != V4L2_BUF_TYPE_VIDEO_OUTPUT ||
	    video->type != a->type)
		वापस -EINVAL;

	स_रखो(a, 0, माप(*a));
	a->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	a->parm.output.capability = V4L2_CAP_TIMEPERFRAME;
	a->parm.output.समयperframe = vfh->समयperframe;

	वापस 0;
पूर्ण

अटल पूर्णांक
iss_video_set_param(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा iss_video_fh *vfh = to_iss_video_fh(fh);
	काष्ठा iss_video *video = video_drvdata(file);

	अगर (video->type != V4L2_BUF_TYPE_VIDEO_OUTPUT ||
	    video->type != a->type)
		वापस -EINVAL;

	अगर (a->parm.output.समयperframe.denominator == 0)
		a->parm.output.समयperframe.denominator = 1;

	vfh->समयperframe = a->parm.output.समयperframe;

	वापस 0;
पूर्ण

अटल पूर्णांक
iss_video_reqbufs(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_requestbuffers *rb)
अणु
	काष्ठा iss_video_fh *vfh = to_iss_video_fh(fh);

	वापस vb2_reqbufs(&vfh->queue, rb);
पूर्ण

अटल पूर्णांक
iss_video_querybuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा iss_video_fh *vfh = to_iss_video_fh(fh);

	वापस vb2_querybuf(&vfh->queue, b);
पूर्ण

अटल पूर्णांक
iss_video_qbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा iss_video *video = video_drvdata(file);
	काष्ठा iss_video_fh *vfh = to_iss_video_fh(fh);

	वापस vb2_qbuf(&vfh->queue, video->video.v4l2_dev->mdev, b);
पूर्ण

अटल पूर्णांक
iss_video_expbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_exportbuffer *e)
अणु
	काष्ठा iss_video_fh *vfh = to_iss_video_fh(fh);

	वापस vb2_expbuf(&vfh->queue, e);
पूर्ण

अटल पूर्णांक
iss_video_dqbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा iss_video_fh *vfh = to_iss_video_fh(fh);

	वापस vb2_dqbuf(&vfh->queue, b, file->f_flags & O_NONBLOCK);
पूर्ण

/*
 * Stream management
 *
 * Every ISS pipeline has a single input and a single output. The input can be
 * either a sensor or a video node. The output is always a video node.
 *
 * As every pipeline has an output video node, the ISS video objects at the
 * pipeline output stores the pipeline state. It tracks the streaming state of
 * both the input and output, as well as the availability of buffers.
 *
 * In sensor-to-memory mode, frames are always available at the pipeline input.
 * Starting the sensor usually requires I2C transfers and must be करोne in
 * पूर्णांकerruptible context. The pipeline is started and stopped synchronously
 * to the stream on/off commands. All modules in the pipeline will get their
 * subdev set stream handler called. The module at the end of the pipeline must
 * delay starting the hardware until buffers are available at its output.
 *
 * In memory-to-memory mode, starting/stopping the stream requires
 * synchronization between the input and output. ISS modules can't be stopped
 * in the middle of a frame, and at least some of the modules seem to become
 * busy as soon as they're started, even if they don't receive a frame start
 * event. For that reason frames need to be processed in single-shot mode. The
 * driver needs to रुको until a frame is completely processed and written to
 * memory beक्रमe restarting the pipeline क्रम the next frame. Pipelined
 * processing might be possible but requires more testing.
 *
 * Stream start must be delayed until buffers are available at both the input
 * and output. The pipeline must be started in the videobuf queue callback with
 * the buffers queue spinlock held. The modules subdev set stream operation must
 * not sleep.
 */
अटल पूर्णांक
iss_video_streamon(काष्ठा file *file, व्योम *fh, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा iss_video_fh *vfh = to_iss_video_fh(fh);
	काष्ठा iss_video *video = video_drvdata(file);
	काष्ठा media_graph graph;
	काष्ठा media_entity *entity = &video->video.entity;
	काष्ठा media_device *mdev = entity->graph_obj.mdev;
	क्रमागत iss_pipeline_state state;
	काष्ठा iss_pipeline *pipe;
	काष्ठा iss_video *far_end;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (type != video->type)
		वापस -EINVAL;

	mutex_lock(&video->stream_lock);

	/*
	 * Start streaming on the pipeline. No link touching an entity in the
	 * pipeline can be activated or deactivated once streaming is started.
	 */
	pipe = entity->pipe
	     ? to_iss_pipeline(entity) : &video->pipe;
	pipe->बाह्यal = शून्य;
	pipe->बाह्यal_rate = 0;
	pipe->बाह्यal_bpp = 0;

	ret = media_entity_क्रमागत_init(&pipe->ent_क्रमागत, entity->graph_obj.mdev);
	अगर (ret)
		जाओ err_graph_walk_init;

	ret = media_graph_walk_init(&graph, entity->graph_obj.mdev);
	अगर (ret)
		जाओ err_graph_walk_init;

	अगर (video->iss->pdata->set_स्थिरraपूर्णांकs)
		video->iss->pdata->set_स्थिरraपूर्णांकs(video->iss, true);

	ret = media_pipeline_start(entity, &pipe->pipe);
	अगर (ret < 0)
		जाओ err_media_pipeline_start;

	mutex_lock(&mdev->graph_mutex);
	media_graph_walk_start(&graph, entity);
	जबतक ((entity = media_graph_walk_next(&graph)))
		media_entity_क्रमागत_set(&pipe->ent_क्रमागत, entity);
	mutex_unlock(&mdev->graph_mutex);

	/*
	 * Verअगरy that the currently configured क्रमmat matches the output of
	 * the connected subdev.
	 */
	ret = iss_video_check_क्रमmat(video, vfh);
	अगर (ret < 0)
		जाओ err_iss_video_check_क्रमmat;

	video->bpl_padding = ret;
	video->bpl_value = vfh->क्रमmat.fmt.pix.bytesperline;

	/*
	 * Find the ISS video node connected at the far end of the pipeline and
	 * update the pipeline.
	 */
	far_end = iss_video_far_end(video);

	अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		state = ISS_PIPELINE_STREAM_OUTPUT | ISS_PIPELINE_IDLE_OUTPUT;
		pipe->input = far_end;
		pipe->output = video;
	पूर्ण अन्यथा अणु
		अगर (!far_end) अणु
			ret = -EPIPE;
			जाओ err_iss_video_check_क्रमmat;
		पूर्ण

		state = ISS_PIPELINE_STREAM_INPUT | ISS_PIPELINE_IDLE_INPUT;
		pipe->input = video;
		pipe->output = far_end;
	पूर्ण

	spin_lock_irqsave(&pipe->lock, flags);
	pipe->state &= ~ISS_PIPELINE_STREAM;
	pipe->state |= state;
	spin_unlock_irqrestore(&pipe->lock, flags);

	/*
	 * Set the maximum समय per frame as the value requested by userspace.
	 * This is a soft limit that can be overridden अगर the hardware करोesn't
	 * support the request limit.
	 */
	अगर (video->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		pipe->max_समयperframe = vfh->समयperframe;

	video->queue = &vfh->queue;
	INIT_LIST_HEAD(&video->dmaqueue);
	video->error = false;
	atomic_set(&pipe->frame_number, -1);

	ret = vb2_streamon(&vfh->queue, type);
	अगर (ret < 0)
		जाओ err_iss_video_check_क्रमmat;

	/*
	 * In sensor-to-memory mode, the stream can be started synchronously
	 * to the stream on command. In memory-to-memory mode, it will be
	 * started when buffers are queued on both the input and output.
	 */
	अगर (!pipe->input) अणु
		अचिन्हित दीर्घ flags;

		ret = omap4iss_pipeline_set_stream(pipe,
					      ISS_PIPELINE_STREAM_CONTINUOUS);
		अगर (ret < 0)
			जाओ err_omap4iss_set_stream;
		spin_lock_irqsave(&video->qlock, flags);
		अगर (list_empty(&video->dmaqueue))
			video->dmaqueue_flags |= ISS_VIDEO_DMAQUEUE_UNDERRUN;
		spin_unlock_irqrestore(&video->qlock, flags);
	पूर्ण

	media_graph_walk_cleanup(&graph);

	mutex_unlock(&video->stream_lock);

	वापस 0;

err_omap4iss_set_stream:
	vb2_streamoff(&vfh->queue, type);
err_iss_video_check_क्रमmat:
	media_pipeline_stop(&video->video.entity);
err_media_pipeline_start:
	अगर (video->iss->pdata->set_स्थिरraपूर्णांकs)
		video->iss->pdata->set_स्थिरraपूर्णांकs(video->iss, false);
	video->queue = शून्य;

	media_graph_walk_cleanup(&graph);

err_graph_walk_init:
	media_entity_क्रमागत_cleanup(&pipe->ent_क्रमागत);

	mutex_unlock(&video->stream_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
iss_video_streamoff(काष्ठा file *file, व्योम *fh, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा iss_video_fh *vfh = to_iss_video_fh(fh);
	काष्ठा iss_video *video = video_drvdata(file);
	काष्ठा iss_pipeline *pipe = to_iss_pipeline(&video->video.entity);
	क्रमागत iss_pipeline_state state;
	अचिन्हित दीर्घ flags;

	अगर (type != video->type)
		वापस -EINVAL;

	mutex_lock(&video->stream_lock);

	अगर (!vb2_is_streaming(&vfh->queue))
		जाओ करोne;

	/* Update the pipeline state. */
	अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		state = ISS_PIPELINE_STREAM_OUTPUT
		      | ISS_PIPELINE_QUEUE_OUTPUT;
	अन्यथा
		state = ISS_PIPELINE_STREAM_INPUT
		      | ISS_PIPELINE_QUEUE_INPUT;

	spin_lock_irqsave(&pipe->lock, flags);
	pipe->state &= ~state;
	spin_unlock_irqrestore(&pipe->lock, flags);

	/* Stop the stream. */
	omap4iss_pipeline_set_stream(pipe, ISS_PIPELINE_STREAM_STOPPED);
	vb2_streamoff(&vfh->queue, type);
	video->queue = शून्य;

	media_entity_क्रमागत_cleanup(&pipe->ent_क्रमागत);

	अगर (video->iss->pdata->set_स्थिरraपूर्णांकs)
		video->iss->pdata->set_स्थिरraपूर्णांकs(video->iss, false);
	media_pipeline_stop(&video->video.entity);

करोne:
	mutex_unlock(&video->stream_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
iss_video_क्रमागत_input(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_input *input)
अणु
	अगर (input->index > 0)
		वापस -EINVAL;

	strscpy(input->name, "camera", माप(input->name));
	input->type = V4L2_INPUT_TYPE_CAMERA;

	वापस 0;
पूर्ण

अटल पूर्णांक
iss_video_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *input)
अणु
	*input = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
iss_video_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक input)
अणु
	वापस input == 0 ? 0 : -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops iss_video_ioctl_ops = अणु
	.vidioc_querycap		= iss_video_querycap,
	.vidioc_क्रमागत_fmt_vid_cap        = iss_video_क्रमागत_क्रमmat,
	.vidioc_g_fmt_vid_cap		= iss_video_get_क्रमmat,
	.vidioc_s_fmt_vid_cap		= iss_video_set_क्रमmat,
	.vidioc_try_fmt_vid_cap		= iss_video_try_क्रमmat,
	.vidioc_g_fmt_vid_out		= iss_video_get_क्रमmat,
	.vidioc_s_fmt_vid_out		= iss_video_set_क्रमmat,
	.vidioc_try_fmt_vid_out		= iss_video_try_क्रमmat,
	.vidioc_g_selection		= iss_video_get_selection,
	.vidioc_s_selection		= iss_video_set_selection,
	.vidioc_g_parm			= iss_video_get_param,
	.vidioc_s_parm			= iss_video_set_param,
	.vidioc_reqbufs			= iss_video_reqbufs,
	.vidioc_querybuf		= iss_video_querybuf,
	.vidioc_qbuf			= iss_video_qbuf,
	.vidioc_expbuf			= iss_video_expbuf,
	.vidioc_dqbuf			= iss_video_dqbuf,
	.vidioc_streamon		= iss_video_streamon,
	.vidioc_streamoff		= iss_video_streamoff,
	.vidioc_क्रमागत_input		= iss_video_क्रमागत_input,
	.vidioc_g_input			= iss_video_g_input,
	.vidioc_s_input			= iss_video_s_input,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 file operations
 */

अटल पूर्णांक iss_video_खोलो(काष्ठा file *file)
अणु
	काष्ठा iss_video *video = video_drvdata(file);
	काष्ठा iss_video_fh *handle;
	काष्ठा vb2_queue *q;
	पूर्णांक ret = 0;

	handle = kzalloc(माप(*handle), GFP_KERNEL);
	अगर (!handle)
		वापस -ENOMEM;

	v4l2_fh_init(&handle->vfh, &video->video);
	v4l2_fh_add(&handle->vfh);

	/* If this is the first user, initialise the pipeline. */
	अगर (!omap4iss_get(video->iss)) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	ret = v4l2_pipeline_pm_get(&video->video.entity);
	अगर (ret < 0) अणु
		omap4iss_put(video->iss);
		जाओ करोne;
	पूर्ण

	q = &handle->queue;

	q->type = video->type;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
	q->drv_priv = handle;
	q->ops = &iss_video_vb2ops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_काष्ठा_size = माप(काष्ठा iss_buffer);
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->dev = video->iss->dev;

	ret = vb2_queue_init(q);
	अगर (ret) अणु
		omap4iss_put(video->iss);
		जाओ करोne;
	पूर्ण

	स_रखो(&handle->क्रमmat, 0, माप(handle->क्रमmat));
	handle->क्रमmat.type = video->type;
	handle->समयperframe.denominator = 1;

	handle->video = video;
	file->निजी_data = &handle->vfh;

करोne:
	अगर (ret < 0) अणु
		v4l2_fh_del(&handle->vfh);
		v4l2_fh_निकास(&handle->vfh);
		kमुक्त(handle);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक iss_video_release(काष्ठा file *file)
अणु
	काष्ठा iss_video *video = video_drvdata(file);
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा iss_video_fh *handle = to_iss_video_fh(vfh);

	/* Disable streaming and मुक्त the buffers queue resources. */
	iss_video_streamoff(file, vfh, video->type);

	v4l2_pipeline_pm_put(&video->video.entity);

	/* Release the videobuf2 queue */
	vb2_queue_release(&handle->queue);

	v4l2_fh_del(vfh);
	v4l2_fh_निकास(vfh);
	kमुक्त(handle);
	file->निजी_data = शून्य;

	omap4iss_put(video->iss);

	वापस 0;
पूर्ण

अटल __poll_t iss_video_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा iss_video_fh *vfh = to_iss_video_fh(file->निजी_data);

	वापस vb2_poll(&vfh->queue, file, रुको);
पूर्ण

अटल पूर्णांक iss_video_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा iss_video_fh *vfh = to_iss_video_fh(file->निजी_data);

	वापस vb2_mmap(&vfh->queue, vma);
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations iss_video_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = video_ioctl2,
	.खोलो = iss_video_खोलो,
	.release = iss_video_release,
	.poll = iss_video_poll,
	.mmap = iss_video_mmap,
पूर्ण;

/* -----------------------------------------------------------------------------
 * ISS video core
 */

अटल स्थिर काष्ठा iss_video_operations iss_video_dummy_ops = अणु
पूर्ण;

पूर्णांक omap4iss_video_init(काष्ठा iss_video *video, स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *direction;
	पूर्णांक ret;

	चयन (video->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		direction = "output";
		video->pad.flags = MEDIA_PAD_FL_SINK;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		direction = "input";
		video->pad.flags = MEDIA_PAD_FL_SOURCE;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = media_entity_pads_init(&video->video.entity, 1, &video->pad);
	अगर (ret < 0)
		वापस ret;

	spin_lock_init(&video->qlock);
	mutex_init(&video->mutex);
	atomic_set(&video->active, 0);

	spin_lock_init(&video->pipe.lock);
	mutex_init(&video->stream_lock);

	/* Initialize the video device. */
	अगर (!video->ops)
		video->ops = &iss_video_dummy_ops;

	video->video.fops = &iss_video_fops;
	snम_लिखो(video->video.name, माप(video->video.name),
		 "OMAP4 ISS %s %s", name, direction);
	video->video.vfl_type = VFL_TYPE_VIDEO;
	video->video.release = video_device_release_empty;
	video->video.ioctl_ops = &iss_video_ioctl_ops;
	video->pipe.stream_state = ISS_PIPELINE_STREAM_STOPPED;

	video_set_drvdata(&video->video, video);

	वापस 0;
पूर्ण

व्योम omap4iss_video_cleanup(काष्ठा iss_video *video)
अणु
	media_entity_cleanup(&video->video.entity);
	mutex_destroy(&video->stream_lock);
	mutex_destroy(&video->mutex);
पूर्ण

पूर्णांक omap4iss_video_रेजिस्टर(काष्ठा iss_video *video, काष्ठा v4l2_device *vdev)
अणु
	पूर्णांक ret;

	video->video.v4l2_dev = vdev;
	अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		video->video.device_caps = V4L2_CAP_VIDEO_CAPTURE;
	अन्यथा
		video->video.device_caps = V4L2_CAP_VIDEO_OUTPUT;
	video->video.device_caps |= V4L2_CAP_STREAMING;

	ret = video_रेजिस्टर_device(&video->video, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0)
		dev_err(video->iss->dev,
			"could not register video device (%d)\n", ret);

	वापस ret;
पूर्ण

व्योम omap4iss_video_unरेजिस्टर(काष्ठा iss_video *video)
अणु
	video_unरेजिस्टर_device(&video->video);
पूर्ण
