<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ispvideo.c
 *
 * TI OMAP3 ISP - Generic video node
 *
 * Copyright (C) 2009-2010 Nokia Corporation
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <linux/clk.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "ispvideo.h"
#समावेश "isp.h"


/* -----------------------------------------------------------------------------
 * Helper functions
 */

/*
 * NOTE: When adding new media bus codes, always remember to add
 * corresponding in-memory क्रमmats to the table below!!!
 */
अटल काष्ठा isp_क्रमmat_info क्रमmats[] = अणु
	अणु MEDIA_BUS_FMT_Y8_1X8, MEDIA_BUS_FMT_Y8_1X8,
	  MEDIA_BUS_FMT_Y8_1X8, MEDIA_BUS_FMT_Y8_1X8,
	  V4L2_PIX_FMT_GREY, 8, 1, पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_1X10, MEDIA_BUS_FMT_Y10_1X10,
	  MEDIA_BUS_FMT_Y10_1X10, MEDIA_BUS_FMT_Y8_1X8,
	  V4L2_PIX_FMT_Y10, 10, 2, पूर्ण,
	अणु MEDIA_BUS_FMT_Y12_1X12, MEDIA_BUS_FMT_Y10_1X10,
	  MEDIA_BUS_FMT_Y12_1X12, MEDIA_BUS_FMT_Y8_1X8,
	  V4L2_PIX_FMT_Y12, 12, 2, पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR8_1X8, MEDIA_BUS_FMT_SBGGR8_1X8,
	  MEDIA_BUS_FMT_SBGGR8_1X8, MEDIA_BUS_FMT_SBGGR8_1X8,
	  V4L2_PIX_FMT_SBGGR8, 8, 1, पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG8_1X8, MEDIA_BUS_FMT_SGBRG8_1X8,
	  MEDIA_BUS_FMT_SGBRG8_1X8, MEDIA_BUS_FMT_SGBRG8_1X8,
	  V4L2_PIX_FMT_SGBRG8, 8, 1, पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, MEDIA_BUS_FMT_SGRBG8_1X8,
	  MEDIA_BUS_FMT_SGRBG8_1X8, MEDIA_BUS_FMT_SGRBG8_1X8,
	  V4L2_PIX_FMT_SGRBG8, 8, 1, पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB8_1X8, MEDIA_BUS_FMT_SRGGB8_1X8,
	  MEDIA_BUS_FMT_SRGGB8_1X8, MEDIA_BUS_FMT_SRGGB8_1X8,
	  V4L2_PIX_FMT_SRGGB8, 8, 1, पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_DPCM8_1X8, MEDIA_BUS_FMT_SBGGR10_DPCM8_1X8,
	  MEDIA_BUS_FMT_SBGGR10_1X10, 0,
	  V4L2_PIX_FMT_SBGGR10DPCM8, 8, 1, पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_DPCM8_1X8, MEDIA_BUS_FMT_SGBRG10_DPCM8_1X8,
	  MEDIA_BUS_FMT_SGBRG10_1X10, 0,
	  V4L2_PIX_FMT_SGBRG10DPCM8, 8, 1, पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8, MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8,
	  MEDIA_BUS_FMT_SGRBG10_1X10, 0,
	  V4L2_PIX_FMT_SGRBG10DPCM8, 8, 1, पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_DPCM8_1X8, MEDIA_BUS_FMT_SRGGB10_DPCM8_1X8,
	  MEDIA_BUS_FMT_SRGGB10_1X10, 0,
	  V4L2_PIX_FMT_SRGGB10DPCM8, 8, 1, पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_1X10, MEDIA_BUS_FMT_SBGGR10_1X10,
	  MEDIA_BUS_FMT_SBGGR10_1X10, MEDIA_BUS_FMT_SBGGR8_1X8,
	  V4L2_PIX_FMT_SBGGR10, 10, 2, पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_1X10, MEDIA_BUS_FMT_SGBRG10_1X10,
	  MEDIA_BUS_FMT_SGBRG10_1X10, MEDIA_BUS_FMT_SGBRG8_1X8,
	  V4L2_PIX_FMT_SGBRG10, 10, 2, पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, MEDIA_BUS_FMT_SGRBG10_1X10,
	  MEDIA_BUS_FMT_SGRBG10_1X10, MEDIA_BUS_FMT_SGRBG8_1X8,
	  V4L2_PIX_FMT_SGRBG10, 10, 2, पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, MEDIA_BUS_FMT_SRGGB10_1X10,
	  MEDIA_BUS_FMT_SRGGB10_1X10, MEDIA_BUS_FMT_SRGGB8_1X8,
	  V4L2_PIX_FMT_SRGGB10, 10, 2, पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR12_1X12, MEDIA_BUS_FMT_SBGGR10_1X10,
	  MEDIA_BUS_FMT_SBGGR12_1X12, MEDIA_BUS_FMT_SBGGR8_1X8,
	  V4L2_PIX_FMT_SBGGR12, 12, 2, पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG12_1X12, MEDIA_BUS_FMT_SGBRG10_1X10,
	  MEDIA_BUS_FMT_SGBRG12_1X12, MEDIA_BUS_FMT_SGBRG8_1X8,
	  V4L2_PIX_FMT_SGBRG12, 12, 2, पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG12_1X12, MEDIA_BUS_FMT_SGRBG10_1X10,
	  MEDIA_BUS_FMT_SGRBG12_1X12, MEDIA_BUS_FMT_SGRBG8_1X8,
	  V4L2_PIX_FMT_SGRBG12, 12, 2, पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB12_1X12, MEDIA_BUS_FMT_SRGGB10_1X10,
	  MEDIA_BUS_FMT_SRGGB12_1X12, MEDIA_BUS_FMT_SRGGB8_1X8,
	  V4L2_PIX_FMT_SRGGB12, 12, 2, पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_1X16, MEDIA_BUS_FMT_UYVY8_1X16,
	  MEDIA_BUS_FMT_UYVY8_1X16, 0,
	  V4L2_PIX_FMT_UYVY, 16, 2, पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_1X16, MEDIA_BUS_FMT_YUYV8_1X16,
	  MEDIA_BUS_FMT_YUYV8_1X16, 0,
	  V4L2_PIX_FMT_YUYV, 16, 2, पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_2X8, MEDIA_BUS_FMT_UYVY8_2X8,
	  MEDIA_BUS_FMT_UYVY8_2X8, 0,
	  V4L2_PIX_FMT_UYVY, 8, 2, पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, MEDIA_BUS_FMT_YUYV8_2X8,
	  MEDIA_BUS_FMT_YUYV8_2X8, 0,
	  V4L2_PIX_FMT_YUYV, 8, 2, पूर्ण,
	/* Empty entry to catch the unsupported pixel code (0) used by the CCDC
	 * module and aव्योम शून्य poपूर्णांकer dereferences.
	 */
	अणु 0, पूर्ण
पूर्ण;

स्थिर काष्ठा isp_क्रमmat_info *omap3isp_video_क्रमmat_info(u32 code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); ++i) अणु
		अगर (क्रमmats[i].code == code)
			वापस &क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * isp_video_mbus_to_pix - Convert v4l2_mbus_framefmt to v4l2_pix_क्रमmat
 * @video: ISP video instance
 * @mbus: v4l2_mbus_framefmt क्रमmat (input)
 * @pix: v4l2_pix_क्रमmat क्रमmat (output)
 *
 * Fill the output pix काष्ठाure with inक्रमmation from the input mbus क्रमmat.
 * The bytesperline and sizeimage fields are computed from the requested bytes
 * per line value in the pix क्रमmat and inक्रमmation from the video instance.
 *
 * Return the number of padding bytes at end of line.
 */
अटल अचिन्हित पूर्णांक isp_video_mbus_to_pix(स्थिर काष्ठा isp_video *video,
					  स्थिर काष्ठा v4l2_mbus_framefmt *mbus,
					  काष्ठा v4l2_pix_क्रमmat *pix)
अणु
	अचिन्हित पूर्णांक bpl = pix->bytesperline;
	अचिन्हित पूर्णांक min_bpl;
	अचिन्हित पूर्णांक i;

	स_रखो(pix, 0, माप(*pix));
	pix->width = mbus->width;
	pix->height = mbus->height;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); ++i) अणु
		अगर (क्रमmats[i].code == mbus->code)
			अवरोध;
	पूर्ण

	अगर (WARN_ON(i == ARRAY_SIZE(क्रमmats)))
		वापस 0;

	min_bpl = pix->width * क्रमmats[i].bpp;

	/* Clamp the requested bytes per line value. If the maximum bytes per
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

	वापस bpl - min_bpl;
पूर्ण

अटल व्योम isp_video_pix_to_mbus(स्थिर काष्ठा v4l2_pix_क्रमmat *pix,
				  काष्ठा v4l2_mbus_framefmt *mbus)
अणु
	अचिन्हित पूर्णांक i;

	स_रखो(mbus, 0, माप(*mbus));
	mbus->width = pix->width;
	mbus->height = pix->height;

	/* Skip the last क्रमmat in the loop so that it will be selected अगर no
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
isp_video_remote_subdev(काष्ठा isp_video *video, u32 *pad)
अणु
	काष्ठा media_pad *remote;

	remote = media_entity_remote_pad(&video->pad);

	अगर (!remote || !is_media_entity_v4l2_subdev(remote->entity))
		वापस शून्य;

	अगर (pad)
		*pad = remote->index;

	वापस media_entity_to_v4l2_subdev(remote->entity);
पूर्ण

/* Return a poपूर्णांकer to the ISP video instance at the far end of the pipeline. */
अटल पूर्णांक isp_video_get_graph_data(काष्ठा isp_video *video,
				    काष्ठा isp_pipeline *pipe)
अणु
	काष्ठा media_graph graph;
	काष्ठा media_entity *entity = &video->video.entity;
	काष्ठा media_device *mdev = entity->graph_obj.mdev;
	काष्ठा isp_video *far_end = शून्य;
	पूर्णांक ret;

	mutex_lock(&mdev->graph_mutex);
	ret = media_graph_walk_init(&graph, mdev);
	अगर (ret) अणु
		mutex_unlock(&mdev->graph_mutex);
		वापस ret;
	पूर्ण

	media_graph_walk_start(&graph, entity);

	जबतक ((entity = media_graph_walk_next(&graph))) अणु
		काष्ठा isp_video *__video;

		media_entity_क्रमागत_set(&pipe->ent_क्रमागत, entity);

		अगर (far_end != शून्य)
			जारी;

		अगर (entity == &video->video.entity)
			जारी;

		अगर (!is_media_entity_v4l2_video_device(entity))
			जारी;

		__video = to_isp_video(media_entity_to_video_device(entity));
		अगर (__video->type != video->type)
			far_end = __video;
	पूर्ण

	mutex_unlock(&mdev->graph_mutex);

	media_graph_walk_cleanup(&graph);

	अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		pipe->input = far_end;
		pipe->output = video;
	पूर्ण अन्यथा अणु
		अगर (far_end == शून्य)
			वापस -EPIPE;

		pipe->input = video;
		pipe->output = far_end;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
__isp_video_get_क्रमmat(काष्ठा isp_video *video, काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt;
	काष्ठा v4l2_subdev *subdev;
	u32 pad;
	पूर्णांक ret;

	subdev = isp_video_remote_subdev(video, &pad);
	अगर (subdev == शून्य)
		वापस -EINVAL;

	fmt.pad = pad;
	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;

	mutex_lock(&video->mutex);
	ret = v4l2_subdev_call(subdev, pad, get_fmt, शून्य, &fmt);
	mutex_unlock(&video->mutex);

	अगर (ret)
		वापस ret;

	क्रमmat->type = video->type;
	वापस isp_video_mbus_to_pix(video, &fmt.क्रमmat, &क्रमmat->fmt.pix);
पूर्ण

अटल पूर्णांक
isp_video_check_क्रमmat(काष्ठा isp_video *video, काष्ठा isp_video_fh *vfh)
अणु
	काष्ठा v4l2_क्रमmat क्रमmat;
	पूर्णांक ret;

	स_नकल(&क्रमmat, &vfh->क्रमmat, माप(क्रमmat));
	ret = __isp_video_get_क्रमmat(video, &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	अगर (vfh->क्रमmat.fmt.pix.pixelक्रमmat != क्रमmat.fmt.pix.pixelक्रमmat ||
	    vfh->क्रमmat.fmt.pix.height != क्रमmat.fmt.pix.height ||
	    vfh->क्रमmat.fmt.pix.width != क्रमmat.fmt.pix.width ||
	    vfh->क्रमmat.fmt.pix.bytesperline != क्रमmat.fmt.pix.bytesperline ||
	    vfh->क्रमmat.fmt.pix.sizeimage != क्रमmat.fmt.pix.sizeimage ||
	    vfh->क्रमmat.fmt.pix.field != क्रमmat.fmt.pix.field)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Video queue operations
 */

अटल पूर्णांक isp_video_queue_setup(काष्ठा vb2_queue *queue,
				 अचिन्हित पूर्णांक *count, अचिन्हित पूर्णांक *num_planes,
				 अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा isp_video_fh *vfh = vb2_get_drv_priv(queue);
	काष्ठा isp_video *video = vfh->video;

	*num_planes = 1;

	sizes[0] = vfh->क्रमmat.fmt.pix.sizeimage;
	अगर (sizes[0] == 0)
		वापस -EINVAL;

	*count = min(*count, video->capture_mem / PAGE_ALIGN(sizes[0]));

	वापस 0;
पूर्ण

अटल पूर्णांक isp_video_buffer_prepare(काष्ठा vb2_buffer *buf)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(buf);
	काष्ठा isp_video_fh *vfh = vb2_get_drv_priv(buf->vb2_queue);
	काष्ठा isp_buffer *buffer = to_isp_buffer(vbuf);
	काष्ठा isp_video *video = vfh->video;
	dma_addr_t addr;

	/* Refuse to prepare the buffer is the video node has रेजिस्टरed an
	 * error. We करोn't need to take any lock here as the operation is
	 * inherently racy. The authoritative check will be perक्रमmed in the
	 * queue handler, which can't वापस an error, this check is just a best
	 * efक्रमt to notअगरy userspace as early as possible.
	 */
	अगर (unlikely(video->error))
		वापस -EIO;

	addr = vb2_dma_contig_plane_dma_addr(buf, 0);
	अगर (!IS_ALIGNED(addr, 32)) अणु
		dev_dbg(video->isp->dev,
			"Buffer address must be aligned to 32 bytes boundary.\n");
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(&buffer->vb.vb2_buf, 0,
			      vfh->क्रमmat.fmt.pix.sizeimage);
	buffer->dma = addr;

	वापस 0;
पूर्ण

/*
 * isp_video_buffer_queue - Add buffer to streaming queue
 * @buf: Video buffer
 *
 * In memory-to-memory mode, start streaming on the pipeline अगर buffers are
 * queued on both the input and the output, अगर the pipeline isn't alपढ़ोy busy.
 * If the pipeline is busy, it will be restarted in the output module पूर्णांकerrupt
 * handler.
 */
अटल व्योम isp_video_buffer_queue(काष्ठा vb2_buffer *buf)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(buf);
	काष्ठा isp_video_fh *vfh = vb2_get_drv_priv(buf->vb2_queue);
	काष्ठा isp_buffer *buffer = to_isp_buffer(vbuf);
	काष्ठा isp_video *video = vfh->video;
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&video->video.entity);
	क्रमागत isp_pipeline_state state;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक empty;
	अचिन्हित पूर्णांक start;

	spin_lock_irqsave(&video->irqlock, flags);

	अगर (unlikely(video->error)) अणु
		vb2_buffer_करोne(&buffer->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		spin_unlock_irqrestore(&video->irqlock, flags);
		वापस;
	पूर्ण

	empty = list_empty(&video->dmaqueue);
	list_add_tail(&buffer->irqlist, &video->dmaqueue);

	spin_unlock_irqrestore(&video->irqlock, flags);

	अगर (empty) अणु
		अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
			state = ISP_PIPELINE_QUEUE_OUTPUT;
		अन्यथा
			state = ISP_PIPELINE_QUEUE_INPUT;

		spin_lock_irqsave(&pipe->lock, flags);
		pipe->state |= state;
		video->ops->queue(video, buffer);
		video->dmaqueue_flags |= ISP_VIDEO_DMAQUEUE_QUEUED;

		start = isp_pipeline_पढ़ोy(pipe);
		अगर (start)
			pipe->state |= ISP_PIPELINE_STREAM;
		spin_unlock_irqrestore(&pipe->lock, flags);

		अगर (start)
			omap3isp_pipeline_set_stream(pipe,
						ISP_PIPELINE_STREAM_SINGLESHOT);
	पूर्ण
पूर्ण

/*
 * omap3isp_video_वापस_buffers - Return all queued buffers to videobuf2
 * @video: ISP video object
 * @state: new state क्रम the वापसed buffers
 *
 * Return all buffers queued on the video node to videobuf2 in the given state.
 * The buffer state should be VB2_BUF_STATE_QUEUED अगर called due to an error
 * when starting the stream, or VB2_BUF_STATE_ERROR otherwise.
 *
 * The function must be called with the video irqlock held.
 */
अटल व्योम omap3isp_video_वापस_buffers(काष्ठा isp_video *video,
					  क्रमागत vb2_buffer_state state)
अणु
	जबतक (!list_empty(&video->dmaqueue)) अणु
		काष्ठा isp_buffer *buf;

		buf = list_first_entry(&video->dmaqueue,
				       काष्ठा isp_buffer, irqlist);
		list_del(&buf->irqlist);
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
	पूर्ण
पूर्ण

अटल पूर्णांक isp_video_start_streaming(काष्ठा vb2_queue *queue,
				     अचिन्हित पूर्णांक count)
अणु
	काष्ठा isp_video_fh *vfh = vb2_get_drv_priv(queue);
	काष्ठा isp_video *video = vfh->video;
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&video->video.entity);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* In sensor-to-memory mode, the stream can be started synchronously
	 * to the stream on command. In memory-to-memory mode, it will be
	 * started when buffers are queued on both the input and output.
	 */
	अगर (pipe->input)
		वापस 0;

	ret = omap3isp_pipeline_set_stream(pipe,
					   ISP_PIPELINE_STREAM_CONTINUOUS);
	अगर (ret < 0) अणु
		spin_lock_irqsave(&video->irqlock, flags);
		omap3isp_video_वापस_buffers(video, VB2_BUF_STATE_QUEUED);
		spin_unlock_irqrestore(&video->irqlock, flags);
		वापस ret;
	पूर्ण

	spin_lock_irqsave(&video->irqlock, flags);
	अगर (list_empty(&video->dmaqueue))
		video->dmaqueue_flags |= ISP_VIDEO_DMAQUEUE_UNDERRUN;
	spin_unlock_irqrestore(&video->irqlock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vb2_ops isp_video_queue_ops = अणु
	.queue_setup = isp_video_queue_setup,
	.buf_prepare = isp_video_buffer_prepare,
	.buf_queue = isp_video_buffer_queue,
	.start_streaming = isp_video_start_streaming,
पूर्ण;

/*
 * omap3isp_video_buffer_next - Complete the current buffer and वापस the next
 * @video: ISP video object
 *
 * Remove the current video buffer from the DMA queue and fill its बारtamp and
 * field count beक्रमe handing it back to videobuf2.
 *
 * For capture video nodes the buffer state is set to VB2_BUF_STATE_DONE अगर no
 * error has been flagged in the pipeline, or to VB2_BUF_STATE_ERROR otherwise.
 * For video output nodes the buffer state is always set to VB2_BUF_STATE_DONE.
 *
 * The DMA queue is expected to contain at least one buffer.
 *
 * Return a poपूर्णांकer to the next buffer in the DMA queue, or शून्य अगर the queue is
 * empty.
 */
काष्ठा isp_buffer *omap3isp_video_buffer_next(काष्ठा isp_video *video)
अणु
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&video->video.entity);
	क्रमागत vb2_buffer_state vb_state;
	काष्ठा isp_buffer *buf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&video->irqlock, flags);
	अगर (WARN_ON(list_empty(&video->dmaqueue))) अणु
		spin_unlock_irqrestore(&video->irqlock, flags);
		वापस शून्य;
	पूर्ण

	buf = list_first_entry(&video->dmaqueue, काष्ठा isp_buffer,
			       irqlist);
	list_del(&buf->irqlist);
	spin_unlock_irqrestore(&video->irqlock, flags);

	buf->vb.vb2_buf.बारtamp = kसमय_get_ns();

	/* Do frame number propagation only अगर this is the output video node.
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

	अगर (pipe->field != V4L2_FIELD_NONE)
		buf->vb.sequence /= 2;

	buf->vb.field = pipe->field;

	/* Report pipeline errors to userspace on the capture device side. */
	अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE && pipe->error) अणु
		vb_state = VB2_BUF_STATE_ERROR;
		pipe->error = false;
	पूर्ण अन्यथा अणु
		vb_state = VB2_BUF_STATE_DONE;
	पूर्ण

	vb2_buffer_करोne(&buf->vb.vb2_buf, vb_state);

	spin_lock_irqsave(&video->irqlock, flags);

	अगर (list_empty(&video->dmaqueue)) अणु
		क्रमागत isp_pipeline_state state;

		spin_unlock_irqrestore(&video->irqlock, flags);

		अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
			state = ISP_PIPELINE_QUEUE_OUTPUT
			      | ISP_PIPELINE_STREAM;
		अन्यथा
			state = ISP_PIPELINE_QUEUE_INPUT
			      | ISP_PIPELINE_STREAM;

		spin_lock_irqsave(&pipe->lock, flags);
		pipe->state &= ~state;
		अगर (video->pipe.stream_state == ISP_PIPELINE_STREAM_CONTINUOUS)
			video->dmaqueue_flags |= ISP_VIDEO_DMAQUEUE_UNDERRUN;
		spin_unlock_irqrestore(&pipe->lock, flags);
		वापस शून्य;
	पूर्ण

	अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE && pipe->input != शून्य) अणु
		spin_lock(&pipe->lock);
		pipe->state &= ~ISP_PIPELINE_STREAM;
		spin_unlock(&pipe->lock);
	पूर्ण

	buf = list_first_entry(&video->dmaqueue, काष्ठा isp_buffer,
			       irqlist);

	spin_unlock_irqrestore(&video->irqlock, flags);

	वापस buf;
पूर्ण

/*
 * omap3isp_video_cancel_stream - Cancel stream on a video node
 * @video: ISP video object
 *
 * Cancelling a stream वापसs all buffers queued on the video node to videobuf2
 * in the erroneous state and makes sure no new buffer can be queued.
 */
व्योम omap3isp_video_cancel_stream(काष्ठा isp_video *video)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&video->irqlock, flags);
	omap3isp_video_वापस_buffers(video, VB2_BUF_STATE_ERROR);
	video->error = true;
	spin_unlock_irqrestore(&video->irqlock, flags);
पूर्ण

/*
 * omap3isp_video_resume - Perक्रमm resume operation on the buffers
 * @video: ISP video object
 * @continuous: Pipeline is in single shot mode अगर 0 or continuous mode otherwise
 *
 * This function is पूर्णांकended to be used on suspend/resume scenario. It
 * requests video queue layer to discard buffers marked as DONE अगर it's in
 * continuous mode and requests ISP modules to queue again the ACTIVE buffer
 * अगर there's any.
 */
व्योम omap3isp_video_resume(काष्ठा isp_video *video, पूर्णांक continuous)
अणु
	काष्ठा isp_buffer *buf = शून्य;

	अगर (continuous && video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		mutex_lock(&video->queue_lock);
		vb2_discard_करोne(video->queue);
		mutex_unlock(&video->queue_lock);
	पूर्ण

	अगर (!list_empty(&video->dmaqueue)) अणु
		buf = list_first_entry(&video->dmaqueue,
				       काष्ठा isp_buffer, irqlist);
		video->ops->queue(video, buf);
		video->dmaqueue_flags |= ISP_VIDEO_DMAQUEUE_QUEUED;
	पूर्ण अन्यथा अणु
		अगर (continuous)
			video->dmaqueue_flags |= ISP_VIDEO_DMAQUEUE_UNDERRUN;
	पूर्ण
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 ioctls
 */

अटल पूर्णांक
isp_video_querycap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_capability *cap)
अणु
	काष्ठा isp_video *video = video_drvdata(file);

	strscpy(cap->driver, ISP_VIDEO_DRIVER_NAME, माप(cap->driver));
	strscpy(cap->card, video->video.name, माप(cap->card));
	strscpy(cap->bus_info, "media", माप(cap->bus_info));

	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_VIDEO_OUTPUT
		| V4L2_CAP_STREAMING | V4L2_CAP_DEVICE_CAPS;


	वापस 0;
पूर्ण

अटल पूर्णांक
isp_video_get_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा isp_video_fh *vfh = to_isp_video_fh(fh);
	काष्ठा isp_video *video = video_drvdata(file);

	अगर (क्रमmat->type != video->type)
		वापस -EINVAL;

	mutex_lock(&video->mutex);
	*क्रमmat = vfh->क्रमmat;
	mutex_unlock(&video->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
isp_video_set_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा isp_video_fh *vfh = to_isp_video_fh(fh);
	काष्ठा isp_video *video = video_drvdata(file);
	काष्ठा v4l2_mbus_framefmt fmt;

	अगर (क्रमmat->type != video->type)
		वापस -EINVAL;

	/* Replace unsupported field orders with sane शेषs. */
	चयन (क्रमmat->fmt.pix.field) अणु
	हाल V4L2_FIELD_NONE:
		/* Progressive is supported everywhere. */
		अवरोध;
	हाल V4L2_FIELD_ALTERNATE:
		/* ALTERNATE is not supported on output nodes. */
		अगर (video->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
			क्रमmat->fmt.pix.field = V4L2_FIELD_NONE;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED:
		/* The ISP has no concept of video standard, select the
		 * top-bottom order when the unqualअगरied पूर्णांकerlaced order is
		 * requested.
		 */
		क्रमmat->fmt.pix.field = V4L2_FIELD_INTERLACED_TB;
		fallthrough;
	हाल V4L2_FIELD_INTERLACED_TB:
	हाल V4L2_FIELD_INTERLACED_BT:
		/* Interlaced orders are only supported at the CCDC output. */
		अगर (video != &video->isp->isp_ccdc.video_out)
			क्रमmat->fmt.pix.field = V4L2_FIELD_NONE;
		अवरोध;
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
	हाल V4L2_FIELD_SEQ_TB:
	हाल V4L2_FIELD_SEQ_BT:
	शेष:
		/* All other field orders are currently unsupported, शेष to
		 * progressive.
		 */
		क्रमmat->fmt.pix.field = V4L2_FIELD_NONE;
		अवरोध;
	पूर्ण

	/* Fill the bytesperline and sizeimage fields by converting to media bus
	 * क्रमmat and back to pixel क्रमmat.
	 */
	isp_video_pix_to_mbus(&क्रमmat->fmt.pix, &fmt);
	isp_video_mbus_to_pix(video, &fmt, &क्रमmat->fmt.pix);

	mutex_lock(&video->mutex);
	vfh->क्रमmat = *क्रमmat;
	mutex_unlock(&video->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
isp_video_try_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा isp_video *video = video_drvdata(file);
	काष्ठा v4l2_subdev_क्रमmat fmt;
	काष्ठा v4l2_subdev *subdev;
	u32 pad;
	पूर्णांक ret;

	अगर (क्रमmat->type != video->type)
		वापस -EINVAL;

	subdev = isp_video_remote_subdev(video, &pad);
	अगर (subdev == शून्य)
		वापस -EINVAL;

	isp_video_pix_to_mbus(&क्रमmat->fmt.pix, &fmt.क्रमmat);

	fmt.pad = pad;
	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(subdev, pad, get_fmt, शून्य, &fmt);
	अगर (ret)
		वापस ret == -ENOIOCTLCMD ? -ENOTTY : ret;

	isp_video_mbus_to_pix(video, &fmt.क्रमmat, &क्रमmat->fmt.pix);
	वापस 0;
पूर्ण

अटल पूर्णांक
isp_video_get_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *sel)
अणु
	काष्ठा isp_video *video = video_drvdata(file);
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
	subdev = isp_video_remote_subdev(video, &pad);
	अगर (subdev == शून्य)
		वापस -EINVAL;

	/* Try the get selection operation first and fallback to get क्रमmat अगर not
	 * implemented.
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
isp_video_set_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *sel)
अणु
	काष्ठा isp_video *video = video_drvdata(file);
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
	subdev = isp_video_remote_subdev(video, &pad);
	अगर (subdev == शून्य)
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
isp_video_get_param(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा isp_video_fh *vfh = to_isp_video_fh(fh);
	काष्ठा isp_video *video = video_drvdata(file);

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
isp_video_set_param(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा isp_video_fh *vfh = to_isp_video_fh(fh);
	काष्ठा isp_video *video = video_drvdata(file);

	अगर (video->type != V4L2_BUF_TYPE_VIDEO_OUTPUT ||
	    video->type != a->type)
		वापस -EINVAL;

	अगर (a->parm.output.समयperframe.denominator == 0)
		a->parm.output.समयperframe.denominator = 1;

	vfh->समयperframe = a->parm.output.समयperframe;

	वापस 0;
पूर्ण

अटल पूर्णांक
isp_video_reqbufs(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_requestbuffers *rb)
अणु
	काष्ठा isp_video_fh *vfh = to_isp_video_fh(fh);
	काष्ठा isp_video *video = video_drvdata(file);
	पूर्णांक ret;

	mutex_lock(&video->queue_lock);
	ret = vb2_reqbufs(&vfh->queue, rb);
	mutex_unlock(&video->queue_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
isp_video_querybuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा isp_video_fh *vfh = to_isp_video_fh(fh);
	काष्ठा isp_video *video = video_drvdata(file);
	पूर्णांक ret;

	mutex_lock(&video->queue_lock);
	ret = vb2_querybuf(&vfh->queue, b);
	mutex_unlock(&video->queue_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
isp_video_qbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा isp_video_fh *vfh = to_isp_video_fh(fh);
	काष्ठा isp_video *video = video_drvdata(file);
	पूर्णांक ret;

	mutex_lock(&video->queue_lock);
	ret = vb2_qbuf(&vfh->queue, video->video.v4l2_dev->mdev, b);
	mutex_unlock(&video->queue_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
isp_video_dqbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा isp_video_fh *vfh = to_isp_video_fh(fh);
	काष्ठा isp_video *video = video_drvdata(file);
	पूर्णांक ret;

	mutex_lock(&video->queue_lock);
	ret = vb2_dqbuf(&vfh->queue, b, file->f_flags & O_NONBLOCK);
	mutex_unlock(&video->queue_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक isp_video_check_बाह्यal_subdevs(काष्ठा isp_video *video,
					    काष्ठा isp_pipeline *pipe)
अणु
	काष्ठा isp_device *isp = video->isp;
	काष्ठा media_entity *ents[] = अणु
		&isp->isp_csi2a.subdev.entity,
		&isp->isp_csi2c.subdev.entity,
		&isp->isp_ccp2.subdev.entity,
		&isp->isp_ccdc.subdev.entity
	पूर्ण;
	काष्ठा media_pad *source_pad;
	काष्ठा media_entity *source = शून्य;
	काष्ठा media_entity *sink;
	काष्ठा v4l2_subdev_क्रमmat fmt;
	काष्ठा v4l2_ext_controls ctrls;
	काष्ठा v4l2_ext_control ctrl;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Memory-to-memory pipelines have no बाह्यal subdev. */
	अगर (pipe->input != शून्य)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(ents); i++) अणु
		/* Is the entity part of the pipeline? */
		अगर (!media_entity_क्रमागत_test(&pipe->ent_क्रमागत, ents[i]))
			जारी;

		/* ISP entities have always sink pad == 0. Find source. */
		source_pad = media_entity_remote_pad(&ents[i]->pads[0]);
		अगर (source_pad == शून्य)
			जारी;

		source = source_pad->entity;
		sink = ents[i];
		अवरोध;
	पूर्ण

	अगर (!source) अणु
		dev_warn(isp->dev, "can't find source, failing now\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!is_media_entity_v4l2_subdev(source))
		वापस 0;

	pipe->बाह्यal = media_entity_to_v4l2_subdev(source);

	fmt.pad = source_pad->index;
	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(media_entity_to_v4l2_subdev(sink),
			       pad, get_fmt, शून्य, &fmt);
	अगर (unlikely(ret < 0)) अणु
		dev_warn(isp->dev, "get_fmt returned null!\n");
		वापस ret;
	पूर्ण

	pipe->बाह्यal_width =
		omap3isp_video_क्रमmat_info(fmt.क्रमmat.code)->width;

	स_रखो(&ctrls, 0, माप(ctrls));
	स_रखो(&ctrl, 0, माप(ctrl));

	ctrl.id = V4L2_CID_PIXEL_RATE;

	ctrls.count = 1;
	ctrls.controls = &ctrl;
	ret = v4l2_g_ext_ctrls(pipe->बाह्यal->ctrl_handler, &video->video,
			       शून्य, &ctrls);
	अगर (ret < 0) अणु
		dev_warn(isp->dev, "no pixel rate control in subdev %s\n",
			 pipe->बाह्यal->name);
		वापस ret;
	पूर्ण

	pipe->बाह्यal_rate = ctrl.value64;

	अगर (media_entity_क्रमागत_test(&pipe->ent_क्रमागत,
				   &isp->isp_ccdc.subdev.entity)) अणु
		अचिन्हित पूर्णांक rate = अच_पूर्णांक_उच्च;
		/*
		 * Check that maximum allowed CCDC pixel rate isn't
		 * exceeded by the pixel rate.
		 */
		omap3isp_ccdc_max_rate(&isp->isp_ccdc, &rate);
		अगर (pipe->बाह्यal_rate > rate)
			वापस -ENOSPC;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Stream management
 *
 * Every ISP pipeline has a single input and a single output. The input can be
 * either a sensor or a video node. The output is always a video node.
 *
 * As every pipeline has an output video node, the ISP video objects at the
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
 * synchronization between the input and output. ISP modules can't be stopped
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
isp_video_streamon(काष्ठा file *file, व्योम *fh, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा isp_video_fh *vfh = to_isp_video_fh(fh);
	काष्ठा isp_video *video = video_drvdata(file);
	क्रमागत isp_pipeline_state state;
	काष्ठा isp_pipeline *pipe;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (type != video->type)
		वापस -EINVAL;

	mutex_lock(&video->stream_lock);

	/* Start streaming on the pipeline. No link touching an entity in the
	 * pipeline can be activated or deactivated once streaming is started.
	 */
	pipe = video->video.entity.pipe
	     ? to_isp_pipeline(&video->video.entity) : &video->pipe;

	ret = media_entity_क्रमागत_init(&pipe->ent_क्रमागत, &video->isp->media_dev);
	अगर (ret)
		जाओ err_क्रमागत_init;

	/* TODO: Implement PM QoS */
	pipe->l3_ick = clk_get_rate(video->isp->घड़ी[ISP_CLK_L3_ICK]);
	pipe->max_rate = pipe->l3_ick;

	ret = media_pipeline_start(&video->video.entity, &pipe->pipe);
	अगर (ret < 0)
		जाओ err_pipeline_start;

	/* Verअगरy that the currently configured क्रमmat matches the output of
	 * the connected subdev.
	 */
	ret = isp_video_check_क्रमmat(video, vfh);
	अगर (ret < 0)
		जाओ err_check_क्रमmat;

	video->bpl_padding = ret;
	video->bpl_value = vfh->क्रमmat.fmt.pix.bytesperline;

	ret = isp_video_get_graph_data(video, pipe);
	अगर (ret < 0)
		जाओ err_check_क्रमmat;

	अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		state = ISP_PIPELINE_STREAM_OUTPUT | ISP_PIPELINE_IDLE_OUTPUT;
	अन्यथा
		state = ISP_PIPELINE_STREAM_INPUT | ISP_PIPELINE_IDLE_INPUT;

	ret = isp_video_check_बाह्यal_subdevs(video, pipe);
	अगर (ret < 0)
		जाओ err_check_क्रमmat;

	pipe->error = false;

	spin_lock_irqsave(&pipe->lock, flags);
	pipe->state &= ~ISP_PIPELINE_STREAM;
	pipe->state |= state;
	spin_unlock_irqrestore(&pipe->lock, flags);

	/* Set the maximum समय per frame as the value requested by userspace.
	 * This is a soft limit that can be overridden अगर the hardware करोesn't
	 * support the request limit.
	 */
	अगर (video->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		pipe->max_समयperframe = vfh->समयperframe;

	video->queue = &vfh->queue;
	INIT_LIST_HEAD(&video->dmaqueue);
	atomic_set(&pipe->frame_number, -1);
	pipe->field = vfh->क्रमmat.fmt.pix.field;

	mutex_lock(&video->queue_lock);
	ret = vb2_streamon(&vfh->queue, type);
	mutex_unlock(&video->queue_lock);
	अगर (ret < 0)
		जाओ err_check_क्रमmat;

	mutex_unlock(&video->stream_lock);

	वापस 0;

err_check_क्रमmat:
	media_pipeline_stop(&video->video.entity);
err_pipeline_start:
	/* TODO: Implement PM QoS */
	/* The DMA queue must be emptied here, otherwise CCDC पूर्णांकerrupts that
	 * will get triggered the next समय the CCDC is घातered up will try to
	 * access buffers that might have been मुक्तd but still present in the
	 * DMA queue. This can easily get triggered अगर the above
	 * omap3isp_pipeline_set_stream() call fails on a प्रणाली with a
	 * मुक्त-running sensor.
	 */
	INIT_LIST_HEAD(&video->dmaqueue);
	video->queue = शून्य;

	media_entity_क्रमागत_cleanup(&pipe->ent_क्रमागत);

err_क्रमागत_init:
	mutex_unlock(&video->stream_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
isp_video_streamoff(काष्ठा file *file, व्योम *fh, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा isp_video_fh *vfh = to_isp_video_fh(fh);
	काष्ठा isp_video *video = video_drvdata(file);
	काष्ठा isp_pipeline *pipe = to_isp_pipeline(&video->video.entity);
	क्रमागत isp_pipeline_state state;
	अचिन्हित पूर्णांक streaming;
	अचिन्हित दीर्घ flags;

	अगर (type != video->type)
		वापस -EINVAL;

	mutex_lock(&video->stream_lock);

	/* Make sure we're not streaming yet. */
	mutex_lock(&video->queue_lock);
	streaming = vb2_is_streaming(&vfh->queue);
	mutex_unlock(&video->queue_lock);

	अगर (!streaming)
		जाओ करोne;

	/* Update the pipeline state. */
	अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		state = ISP_PIPELINE_STREAM_OUTPUT
		      | ISP_PIPELINE_QUEUE_OUTPUT;
	अन्यथा
		state = ISP_PIPELINE_STREAM_INPUT
		      | ISP_PIPELINE_QUEUE_INPUT;

	spin_lock_irqsave(&pipe->lock, flags);
	pipe->state &= ~state;
	spin_unlock_irqrestore(&pipe->lock, flags);

	/* Stop the stream. */
	omap3isp_pipeline_set_stream(pipe, ISP_PIPELINE_STREAM_STOPPED);
	omap3isp_video_cancel_stream(video);

	mutex_lock(&video->queue_lock);
	vb2_streamoff(&vfh->queue, type);
	mutex_unlock(&video->queue_lock);
	video->queue = शून्य;
	video->error = false;

	/* TODO: Implement PM QoS */
	media_pipeline_stop(&video->video.entity);

	media_entity_क्रमागत_cleanup(&pipe->ent_क्रमागत);

करोne:
	mutex_unlock(&video->stream_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
isp_video_क्रमागत_input(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_input *input)
अणु
	अगर (input->index > 0)
		वापस -EINVAL;

	strscpy(input->name, "camera", माप(input->name));
	input->type = V4L2_INPUT_TYPE_CAMERA;

	वापस 0;
पूर्ण

अटल पूर्णांक
isp_video_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *input)
अणु
	*input = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
isp_video_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक input)
अणु
	वापस input == 0 ? 0 : -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops isp_video_ioctl_ops = अणु
	.vidioc_querycap		= isp_video_querycap,
	.vidioc_g_fmt_vid_cap		= isp_video_get_क्रमmat,
	.vidioc_s_fmt_vid_cap		= isp_video_set_क्रमmat,
	.vidioc_try_fmt_vid_cap		= isp_video_try_क्रमmat,
	.vidioc_g_fmt_vid_out		= isp_video_get_क्रमmat,
	.vidioc_s_fmt_vid_out		= isp_video_set_क्रमmat,
	.vidioc_try_fmt_vid_out		= isp_video_try_क्रमmat,
	.vidioc_g_selection		= isp_video_get_selection,
	.vidioc_s_selection		= isp_video_set_selection,
	.vidioc_g_parm			= isp_video_get_param,
	.vidioc_s_parm			= isp_video_set_param,
	.vidioc_reqbufs			= isp_video_reqbufs,
	.vidioc_querybuf		= isp_video_querybuf,
	.vidioc_qbuf			= isp_video_qbuf,
	.vidioc_dqbuf			= isp_video_dqbuf,
	.vidioc_streamon		= isp_video_streamon,
	.vidioc_streamoff		= isp_video_streamoff,
	.vidioc_क्रमागत_input		= isp_video_क्रमागत_input,
	.vidioc_g_input			= isp_video_g_input,
	.vidioc_s_input			= isp_video_s_input,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 file operations
 */

अटल पूर्णांक isp_video_खोलो(काष्ठा file *file)
अणु
	काष्ठा isp_video *video = video_drvdata(file);
	काष्ठा isp_video_fh *handle;
	काष्ठा vb2_queue *queue;
	पूर्णांक ret = 0;

	handle = kzalloc(माप(*handle), GFP_KERNEL);
	अगर (handle == शून्य)
		वापस -ENOMEM;

	v4l2_fh_init(&handle->vfh, &video->video);
	v4l2_fh_add(&handle->vfh);

	/* If this is the first user, initialise the pipeline. */
	अगर (omap3isp_get(video->isp) == शून्य) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	ret = v4l2_pipeline_pm_get(&video->video.entity);
	अगर (ret < 0) अणु
		omap3isp_put(video->isp);
		जाओ करोne;
	पूर्ण

	queue = &handle->queue;
	queue->type = video->type;
	queue->io_modes = VB2_MMAP | VB2_USERPTR;
	queue->drv_priv = handle;
	queue->ops = &isp_video_queue_ops;
	queue->mem_ops = &vb2_dma_contig_memops;
	queue->buf_काष्ठा_size = माप(काष्ठा isp_buffer);
	queue->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	queue->dev = video->isp->dev;

	ret = vb2_queue_init(&handle->queue);
	अगर (ret < 0) अणु
		omap3isp_put(video->isp);
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

अटल पूर्णांक isp_video_release(काष्ठा file *file)
अणु
	काष्ठा isp_video *video = video_drvdata(file);
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा isp_video_fh *handle = to_isp_video_fh(vfh);

	/* Disable streaming and मुक्त the buffers queue resources. */
	isp_video_streamoff(file, vfh, video->type);

	mutex_lock(&video->queue_lock);
	vb2_queue_release(&handle->queue);
	mutex_unlock(&video->queue_lock);

	v4l2_pipeline_pm_put(&video->video.entity);

	/* Release the file handle. */
	v4l2_fh_del(vfh);
	v4l2_fh_निकास(vfh);
	kमुक्त(handle);
	file->निजी_data = शून्य;

	omap3isp_put(video->isp);

	वापस 0;
पूर्ण

अटल __poll_t isp_video_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा isp_video_fh *vfh = to_isp_video_fh(file->निजी_data);
	काष्ठा isp_video *video = video_drvdata(file);
	__poll_t ret;

	mutex_lock(&video->queue_lock);
	ret = vb2_poll(&vfh->queue, file, रुको);
	mutex_unlock(&video->queue_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक isp_video_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा isp_video_fh *vfh = to_isp_video_fh(file->निजी_data);

	वापस vb2_mmap(&vfh->queue, vma);
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations isp_video_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = video_ioctl2,
	.खोलो = isp_video_खोलो,
	.release = isp_video_release,
	.poll = isp_video_poll,
	.mmap = isp_video_mmap,
पूर्ण;

/* -----------------------------------------------------------------------------
 * ISP video core
 */

अटल स्थिर काष्ठा isp_video_operations isp_video_dummy_ops = अणु
पूर्ण;

पूर्णांक omap3isp_video_init(काष्ठा isp_video *video, स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *direction;
	पूर्णांक ret;

	चयन (video->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		direction = "output";
		video->pad.flags = MEDIA_PAD_FL_SINK
				   | MEDIA_PAD_FL_MUST_CONNECT;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		direction = "input";
		video->pad.flags = MEDIA_PAD_FL_SOURCE
				   | MEDIA_PAD_FL_MUST_CONNECT;
		video->video.vfl_dir = VFL_सूची_TX;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = media_entity_pads_init(&video->video.entity, 1, &video->pad);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&video->mutex);
	atomic_set(&video->active, 0);

	spin_lock_init(&video->pipe.lock);
	mutex_init(&video->stream_lock);
	mutex_init(&video->queue_lock);
	spin_lock_init(&video->irqlock);

	/* Initialize the video device. */
	अगर (video->ops == शून्य)
		video->ops = &isp_video_dummy_ops;

	video->video.fops = &isp_video_fops;
	snम_लिखो(video->video.name, माप(video->video.name),
		 "OMAP3 ISP %s %s", name, direction);
	video->video.vfl_type = VFL_TYPE_VIDEO;
	video->video.release = video_device_release_empty;
	video->video.ioctl_ops = &isp_video_ioctl_ops;
	अगर (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		video->video.device_caps = V4L2_CAP_VIDEO_CAPTURE
					 | V4L2_CAP_STREAMING;
	अन्यथा
		video->video.device_caps = V4L2_CAP_VIDEO_OUTPUT
					 | V4L2_CAP_STREAMING;

	video->pipe.stream_state = ISP_PIPELINE_STREAM_STOPPED;

	video_set_drvdata(&video->video, video);

	वापस 0;
पूर्ण

व्योम omap3isp_video_cleanup(काष्ठा isp_video *video)
अणु
	media_entity_cleanup(&video->video.entity);
	mutex_destroy(&video->queue_lock);
	mutex_destroy(&video->stream_lock);
	mutex_destroy(&video->mutex);
पूर्ण

पूर्णांक omap3isp_video_रेजिस्टर(काष्ठा isp_video *video, काष्ठा v4l2_device *vdev)
अणु
	पूर्णांक ret;

	video->video.v4l2_dev = vdev;

	ret = video_रेजिस्टर_device(&video->video, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0)
		dev_err(video->isp->dev,
			"%s: could not register video device (%d)\n",
			__func__, ret);

	वापस ret;
पूर्ण

व्योम omap3isp_video_unरेजिस्टर(काष्ठा isp_video *video)
अणु
	video_unरेजिस्टर_device(&video->video);
पूर्ण
