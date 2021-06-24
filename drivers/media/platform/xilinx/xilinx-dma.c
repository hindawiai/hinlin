<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx Video DMA
 *
 * Copyright (C) 2013-2015 Ideas on Board
 * Copyright (C) 2013-2015 Xilinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xilinx.com>
 *           Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/dma/xilinx_dma.h>
#समावेश <linux/lcm.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "xilinx-dma.h"
#समावेश "xilinx-vip.h"
#समावेश "xilinx-vipp.h"

#घोषणा XVIP_DMA_DEF_FORMAT		V4L2_PIX_FMT_YUYV
#घोषणा XVIP_DMA_DEF_WIDTH		1920
#घोषणा XVIP_DMA_DEF_HEIGHT		1080

/* Minimum and maximum widths are expressed in bytes */
#घोषणा XVIP_DMA_MIN_WIDTH		1U
#घोषणा XVIP_DMA_MAX_WIDTH		65535U
#घोषणा XVIP_DMA_MIN_HEIGHT		1U
#घोषणा XVIP_DMA_MAX_HEIGHT		8191U

/* -----------------------------------------------------------------------------
 * Helper functions
 */

अटल काष्ठा v4l2_subdev *
xvip_dma_remote_subdev(काष्ठा media_pad *local, u32 *pad)
अणु
	काष्ठा media_pad *remote;

	remote = media_entity_remote_pad(local);
	अगर (!remote || !is_media_entity_v4l2_subdev(remote->entity))
		वापस शून्य;

	अगर (pad)
		*pad = remote->index;

	वापस media_entity_to_v4l2_subdev(remote->entity);
पूर्ण

अटल पूर्णांक xvip_dma_verअगरy_क्रमmat(काष्ठा xvip_dma *dma)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt;
	काष्ठा v4l2_subdev *subdev;
	पूर्णांक ret;

	subdev = xvip_dma_remote_subdev(&dma->pad, &fmt.pad);
	अगर (subdev == शून्य)
		वापस -EPIPE;

	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = v4l2_subdev_call(subdev, pad, get_fmt, शून्य, &fmt);
	अगर (ret < 0)
		वापस ret == -ENOIOCTLCMD ? -EINVAL : ret;

	अगर (dma->fmtinfo->code != fmt.क्रमmat.code ||
	    dma->क्रमmat.height != fmt.क्रमmat.height ||
	    dma->क्रमmat.width != fmt.क्रमmat.width ||
	    dma->क्रमmat.colorspace != fmt.क्रमmat.colorspace)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Pipeline Stream Management
 */

/**
 * xvip_pipeline_start_stop - Start ot stop streaming on a pipeline
 * @pipe: The pipeline
 * @start: Start (when true) or stop (when false) the pipeline
 *
 * Walk the entities chain starting at the pipeline output video node and start
 * or stop all of them.
 *
 * Return: 0 अगर successful, or the वापस value of the failed video::s_stream
 * operation otherwise.
 */
अटल पूर्णांक xvip_pipeline_start_stop(काष्ठा xvip_pipeline *pipe, bool start)
अणु
	काष्ठा xvip_dma *dma = pipe->output;
	काष्ठा media_entity *entity;
	काष्ठा media_pad *pad;
	काष्ठा v4l2_subdev *subdev;
	पूर्णांक ret;

	entity = &dma->video.entity;
	जबतक (1) अणु
		pad = &entity->pads[0];
		अगर (!(pad->flags & MEDIA_PAD_FL_SINK))
			अवरोध;

		pad = media_entity_remote_pad(pad);
		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			अवरोध;

		entity = pad->entity;
		subdev = media_entity_to_v4l2_subdev(entity);

		ret = v4l2_subdev_call(subdev, video, s_stream, start);
		अगर (start && ret < 0 && ret != -ENOIOCTLCMD)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * xvip_pipeline_set_stream - Enable/disable streaming on a pipeline
 * @pipe: The pipeline
 * @on: Turn the stream on when true or off when false
 *
 * The pipeline is shared between all DMA engines connect at its input and
 * output. While the stream state of DMA engines can be controlled
 * independently, pipelines have a shared stream state that enable or disable
 * all entities in the pipeline. For this reason the pipeline uses a streaming
 * counter that tracks the number of DMA engines that have requested the stream
 * to be enabled.
 *
 * When called with the @on argument set to true, this function will increment
 * the pipeline streaming count. If the streaming count reaches the number of
 * DMA engines in the pipeline it will enable all entities that beदीर्घ to the
 * pipeline.
 *
 * Similarly, when called with the @on argument set to false, this function will
 * decrement the pipeline streaming count and disable all entities in the
 * pipeline when the streaming count reaches zero.
 *
 * Return: 0 अगर successful, or the वापस value of the failed video::s_stream
 * operation otherwise. Stopping the pipeline never fails. The pipeline state is
 * not updated when the operation fails.
 */
अटल पूर्णांक xvip_pipeline_set_stream(काष्ठा xvip_pipeline *pipe, bool on)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&pipe->lock);

	अगर (on) अणु
		अगर (pipe->stream_count == pipe->num_dmas - 1) अणु
			ret = xvip_pipeline_start_stop(pipe, true);
			अगर (ret < 0)
				जाओ करोne;
		पूर्ण
		pipe->stream_count++;
	पूर्ण अन्यथा अणु
		अगर (--pipe->stream_count == 0)
			xvip_pipeline_start_stop(pipe, false);
	पूर्ण

करोne:
	mutex_unlock(&pipe->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक xvip_pipeline_validate(काष्ठा xvip_pipeline *pipe,
				  काष्ठा xvip_dma *start)
अणु
	काष्ठा media_graph graph;
	काष्ठा media_entity *entity = &start->video.entity;
	काष्ठा media_device *mdev = entity->graph_obj.mdev;
	अचिन्हित पूर्णांक num_inमाला_दो = 0;
	अचिन्हित पूर्णांक num_outमाला_दो = 0;
	पूर्णांक ret;

	mutex_lock(&mdev->graph_mutex);

	/* Walk the graph to locate the video nodes. */
	ret = media_graph_walk_init(&graph, mdev);
	अगर (ret) अणु
		mutex_unlock(&mdev->graph_mutex);
		वापस ret;
	पूर्ण

	media_graph_walk_start(&graph, entity);

	जबतक ((entity = media_graph_walk_next(&graph))) अणु
		काष्ठा xvip_dma *dma;

		अगर (entity->function != MEDIA_ENT_F_IO_V4L)
			जारी;

		dma = to_xvip_dma(media_entity_to_video_device(entity));

		अगर (dma->pad.flags & MEDIA_PAD_FL_SINK) अणु
			pipe->output = dma;
			num_outमाला_दो++;
		पूर्ण अन्यथा अणु
			num_inमाला_दो++;
		पूर्ण
	पूर्ण

	mutex_unlock(&mdev->graph_mutex);

	media_graph_walk_cleanup(&graph);

	/* We need exactly one output and zero or one input. */
	अगर (num_outमाला_दो != 1 || num_inमाला_दो > 1)
		वापस -EPIPE;

	pipe->num_dmas = num_inमाला_दो + num_outमाला_दो;

	वापस 0;
पूर्ण

अटल व्योम __xvip_pipeline_cleanup(काष्ठा xvip_pipeline *pipe)
अणु
	pipe->num_dmas = 0;
	pipe->output = शून्य;
पूर्ण

/**
 * xvip_pipeline_cleanup - Cleanup the pipeline after streaming
 * @pipe: the pipeline
 *
 * Decrease the pipeline use count and clean it up अगर we were the last user.
 */
अटल व्योम xvip_pipeline_cleanup(काष्ठा xvip_pipeline *pipe)
अणु
	mutex_lock(&pipe->lock);

	/* If we're the last user clean up the pipeline. */
	अगर (--pipe->use_count == 0)
		__xvip_pipeline_cleanup(pipe);

	mutex_unlock(&pipe->lock);
पूर्ण

/**
 * xvip_pipeline_prepare - Prepare the pipeline क्रम streaming
 * @pipe: the pipeline
 * @dma: DMA engine at one end of the pipeline
 *
 * Validate the pipeline अगर no user exists yet, otherwise just increase the use
 * count.
 *
 * Return: 0 अगर successful or -EPIPE अगर the pipeline is not valid.
 */
अटल पूर्णांक xvip_pipeline_prepare(काष्ठा xvip_pipeline *pipe,
				 काष्ठा xvip_dma *dma)
अणु
	पूर्णांक ret;

	mutex_lock(&pipe->lock);

	/* If we're the first user validate and initialize the pipeline. */
	अगर (pipe->use_count == 0) अणु
		ret = xvip_pipeline_validate(pipe, dma);
		अगर (ret < 0) अणु
			__xvip_pipeline_cleanup(pipe);
			जाओ करोne;
		पूर्ण
	पूर्ण

	pipe->use_count++;
	ret = 0;

करोne:
	mutex_unlock(&pipe->lock);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * videobuf2 queue operations
 */

/**
 * काष्ठा xvip_dma_buffer - Video DMA buffer
 * @buf: vb2 buffer base object
 * @queue: buffer list entry in the DMA engine queued buffers list
 * @dma: DMA channel that uses the buffer
 */
काष्ठा xvip_dma_buffer अणु
	काष्ठा vb2_v4l2_buffer buf;
	काष्ठा list_head queue;
	काष्ठा xvip_dma *dma;
पूर्ण;

#घोषणा to_xvip_dma_buffer(vb)	container_of(vb, काष्ठा xvip_dma_buffer, buf)

अटल व्योम xvip_dma_complete(व्योम *param)
अणु
	काष्ठा xvip_dma_buffer *buf = param;
	काष्ठा xvip_dma *dma = buf->dma;

	spin_lock(&dma->queued_lock);
	list_del(&buf->queue);
	spin_unlock(&dma->queued_lock);

	buf->buf.field = V4L2_FIELD_NONE;
	buf->buf.sequence = dma->sequence++;
	buf->buf.vb2_buf.बारtamp = kसमय_get_ns();
	vb2_set_plane_payload(&buf->buf.vb2_buf, 0, dma->क्रमmat.sizeimage);
	vb2_buffer_करोne(&buf->buf.vb2_buf, VB2_BUF_STATE_DONE);
पूर्ण

अटल पूर्णांक
xvip_dma_queue_setup(काष्ठा vb2_queue *vq,
		     अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		     अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा xvip_dma *dma = vb2_get_drv_priv(vq);

	/* Make sure the image size is large enough. */
	अगर (*nplanes)
		वापस sizes[0] < dma->क्रमmat.sizeimage ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = dma->क्रमmat.sizeimage;

	वापस 0;
पूर्ण

अटल पूर्णांक xvip_dma_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा xvip_dma *dma = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा xvip_dma_buffer *buf = to_xvip_dma_buffer(vbuf);

	buf->dma = dma;

	वापस 0;
पूर्ण

अटल व्योम xvip_dma_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा xvip_dma *dma = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा xvip_dma_buffer *buf = to_xvip_dma_buffer(vbuf);
	काष्ठा dma_async_tx_descriptor *desc;
	dma_addr_t addr = vb2_dma_contig_plane_dma_addr(vb, 0);
	u32 flags;

	अगर (dma->queue.type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		flags = DMA_PREP_INTERRUPT | DMA_CTRL_ACK;
		dma->xt.dir = DMA_DEV_TO_MEM;
		dma->xt.src_sgl = false;
		dma->xt.dst_sgl = true;
		dma->xt.dst_start = addr;
	पूर्ण अन्यथा अणु
		flags = DMA_PREP_INTERRUPT | DMA_CTRL_ACK;
		dma->xt.dir = DMA_MEM_TO_DEV;
		dma->xt.src_sgl = true;
		dma->xt.dst_sgl = false;
		dma->xt.src_start = addr;
	पूर्ण

	dma->xt.frame_size = 1;
	dma->sgl[0].size = dma->क्रमmat.width * dma->fmtinfo->bpp;
	dma->sgl[0].icg = dma->क्रमmat.bytesperline - dma->sgl[0].size;
	dma->xt.numf = dma->क्रमmat.height;

	desc = dmaengine_prep_पूर्णांकerleaved_dma(dma->dma, &dma->xt, flags);
	अगर (!desc) अणु
		dev_err(dma->xdev->dev, "Failed to prepare DMA transfer\n");
		vb2_buffer_करोne(&buf->buf.vb2_buf, VB2_BUF_STATE_ERROR);
		वापस;
	पूर्ण
	desc->callback = xvip_dma_complete;
	desc->callback_param = buf;

	spin_lock_irq(&dma->queued_lock);
	list_add_tail(&buf->queue, &dma->queued_bufs);
	spin_unlock_irq(&dma->queued_lock);

	dmaengine_submit(desc);

	अगर (vb2_is_streaming(&dma->queue))
		dma_async_issue_pending(dma->dma);
पूर्ण

अटल पूर्णांक xvip_dma_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा xvip_dma *dma = vb2_get_drv_priv(vq);
	काष्ठा xvip_dma_buffer *buf, *nbuf;
	काष्ठा xvip_pipeline *pipe;
	पूर्णांक ret;

	dma->sequence = 0;

	/*
	 * Start streaming on the pipeline. No link touching an entity in the
	 * pipeline can be activated or deactivated once streaming is started.
	 *
	 * Use the pipeline object embedded in the first DMA object that starts
	 * streaming.
	 */
	pipe = dma->video.entity.pipe
	     ? to_xvip_pipeline(&dma->video.entity) : &dma->pipe;

	ret = media_pipeline_start(&dma->video.entity, &pipe->pipe);
	अगर (ret < 0)
		जाओ error;

	/* Verअगरy that the configured क्रमmat matches the output of the
	 * connected subdev.
	 */
	ret = xvip_dma_verअगरy_क्रमmat(dma);
	अगर (ret < 0)
		जाओ error_stop;

	ret = xvip_pipeline_prepare(pipe, dma);
	अगर (ret < 0)
		जाओ error_stop;

	/* Start the DMA engine. This must be करोne beक्रमe starting the blocks
	 * in the pipeline to aव्योम DMA synchronization issues.
	 */
	dma_async_issue_pending(dma->dma);

	/* Start the pipeline. */
	xvip_pipeline_set_stream(pipe, true);

	वापस 0;

error_stop:
	media_pipeline_stop(&dma->video.entity);

error:
	/* Give back all queued buffers to videobuf2. */
	spin_lock_irq(&dma->queued_lock);
	list_क्रम_each_entry_safe(buf, nbuf, &dma->queued_bufs, queue) अणु
		vb2_buffer_करोne(&buf->buf.vb2_buf, VB2_BUF_STATE_QUEUED);
		list_del(&buf->queue);
	पूर्ण
	spin_unlock_irq(&dma->queued_lock);

	वापस ret;
पूर्ण

अटल व्योम xvip_dma_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा xvip_dma *dma = vb2_get_drv_priv(vq);
	काष्ठा xvip_pipeline *pipe = to_xvip_pipeline(&dma->video.entity);
	काष्ठा xvip_dma_buffer *buf, *nbuf;

	/* Stop the pipeline. */
	xvip_pipeline_set_stream(pipe, false);

	/* Stop and reset the DMA engine. */
	dmaengine_terminate_all(dma->dma);

	/* Cleanup the pipeline and mark it as being stopped. */
	xvip_pipeline_cleanup(pipe);
	media_pipeline_stop(&dma->video.entity);

	/* Give back all queued buffers to videobuf2. */
	spin_lock_irq(&dma->queued_lock);
	list_क्रम_each_entry_safe(buf, nbuf, &dma->queued_bufs, queue) अणु
		vb2_buffer_करोne(&buf->buf.vb2_buf, VB2_BUF_STATE_ERROR);
		list_del(&buf->queue);
	पूर्ण
	spin_unlock_irq(&dma->queued_lock);
पूर्ण

अटल स्थिर काष्ठा vb2_ops xvip_dma_queue_qops = अणु
	.queue_setup = xvip_dma_queue_setup,
	.buf_prepare = xvip_dma_buffer_prepare,
	.buf_queue = xvip_dma_buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = xvip_dma_start_streaming,
	.stop_streaming = xvip_dma_stop_streaming,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 ioctls
 */

अटल पूर्णांक
xvip_dma_querycap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_capability *cap)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा xvip_dma *dma = to_xvip_dma(vfh->vdev);

	cap->capabilities = dma->xdev->v4l2_caps | V4L2_CAP_STREAMING |
			    V4L2_CAP_DEVICE_CAPS;

	strscpy(cap->driver, "xilinx-vipp", माप(cap->driver));
	strscpy(cap->card, dma->video.name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%pOFn:%u",
		 dma->xdev->dev->of_node, dma->port);

	वापस 0;
पूर्ण

/* FIXME: without this callback function, some applications are not configured
 * with correct क्रमmats, and it results in frames in wrong क्रमmat. Whether this
 * callback needs to be required is not clearly defined, so it should be
 * clarअगरied through the mailing list.
 */
अटल पूर्णांक
xvip_dma_क्रमागत_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा xvip_dma *dma = to_xvip_dma(vfh->vdev);

	अगर (f->index > 0)
		वापस -EINVAL;

	f->pixelक्रमmat = dma->क्रमmat.pixelक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक
xvip_dma_get_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा xvip_dma *dma = to_xvip_dma(vfh->vdev);

	क्रमmat->fmt.pix = dma->क्रमmat;

	वापस 0;
पूर्ण

अटल व्योम
__xvip_dma_try_क्रमmat(काष्ठा xvip_dma *dma, काष्ठा v4l2_pix_क्रमmat *pix,
		      स्थिर काष्ठा xvip_video_क्रमmat **fmtinfo)
अणु
	स्थिर काष्ठा xvip_video_क्रमmat *info;
	अचिन्हित पूर्णांक min_width;
	अचिन्हित पूर्णांक max_width;
	अचिन्हित पूर्णांक min_bpl;
	अचिन्हित पूर्णांक max_bpl;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक align;
	अचिन्हित पूर्णांक bpl;

	/* Retrieve क्रमmat inक्रमmation and select the शेष क्रमmat अगर the
	 * requested क्रमmat isn't supported.
	 */
	info = xvip_get_क्रमmat_by_fourcc(pix->pixelक्रमmat);
	अगर (IS_ERR(info))
		info = xvip_get_क्रमmat_by_fourcc(XVIP_DMA_DEF_FORMAT);

	pix->pixelक्रमmat = info->fourcc;
	pix->field = V4L2_FIELD_NONE;

	/* The transfer alignment requirements are expressed in bytes. Compute
	 * the minimum and maximum values, clamp the requested width and convert
	 * it back to pixels.
	 */
	align = lcm(dma->align, info->bpp);
	min_width = roundup(XVIP_DMA_MIN_WIDTH, align);
	max_width = roundकरोwn(XVIP_DMA_MAX_WIDTH, align);
	width = roundकरोwn(pix->width * info->bpp, align);

	pix->width = clamp(width, min_width, max_width) / info->bpp;
	pix->height = clamp(pix->height, XVIP_DMA_MIN_HEIGHT,
			    XVIP_DMA_MAX_HEIGHT);

	/* Clamp the requested bytes per line value. If the maximum bytes per
	 * line value is zero, the module करोesn't support user configurable line
	 * sizes. Override the requested value with the minimum in that हाल.
	 */
	min_bpl = pix->width * info->bpp;
	max_bpl = roundकरोwn(XVIP_DMA_MAX_WIDTH, dma->align);
	bpl = roundकरोwn(pix->bytesperline, dma->align);

	pix->bytesperline = clamp(bpl, min_bpl, max_bpl);
	pix->sizeimage = pix->bytesperline * pix->height;

	अगर (fmtinfo)
		*fmtinfo = info;
पूर्ण

अटल पूर्णांक
xvip_dma_try_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा xvip_dma *dma = to_xvip_dma(vfh->vdev);

	__xvip_dma_try_क्रमmat(dma, &क्रमmat->fmt.pix, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक
xvip_dma_set_क्रमmat(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा xvip_dma *dma = to_xvip_dma(vfh->vdev);
	स्थिर काष्ठा xvip_video_क्रमmat *info;

	__xvip_dma_try_क्रमmat(dma, &क्रमmat->fmt.pix, &info);

	अगर (vb2_is_busy(&dma->queue))
		वापस -EBUSY;

	dma->क्रमmat = क्रमmat->fmt.pix;
	dma->fmtinfo = info;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops xvip_dma_ioctl_ops = अणु
	.vidioc_querycap		= xvip_dma_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= xvip_dma_क्रमागत_क्रमmat,
	.vidioc_g_fmt_vid_cap		= xvip_dma_get_क्रमmat,
	.vidioc_g_fmt_vid_out		= xvip_dma_get_क्रमmat,
	.vidioc_s_fmt_vid_cap		= xvip_dma_set_क्रमmat,
	.vidioc_s_fmt_vid_out		= xvip_dma_set_क्रमmat,
	.vidioc_try_fmt_vid_cap		= xvip_dma_try_क्रमmat,
	.vidioc_try_fmt_vid_out		= xvip_dma_try_क्रमmat,
	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 file operations
 */

अटल स्थिर काष्ठा v4l2_file_operations xvip_dma_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= video_ioctl2,
	.खोलो		= v4l2_fh_खोलो,
	.release	= vb2_fop_release,
	.poll		= vb2_fop_poll,
	.mmap		= vb2_fop_mmap,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Xilinx Video DMA Core
 */

पूर्णांक xvip_dma_init(काष्ठा xvip_composite_device *xdev, काष्ठा xvip_dma *dma,
		  क्रमागत v4l2_buf_type type, अचिन्हित पूर्णांक port)
अणु
	अक्षर name[16];
	पूर्णांक ret;

	dma->xdev = xdev;
	dma->port = port;
	mutex_init(&dma->lock);
	mutex_init(&dma->pipe.lock);
	INIT_LIST_HEAD(&dma->queued_bufs);
	spin_lock_init(&dma->queued_lock);

	dma->fmtinfo = xvip_get_क्रमmat_by_fourcc(XVIP_DMA_DEF_FORMAT);
	dma->क्रमmat.pixelक्रमmat = dma->fmtinfo->fourcc;
	dma->क्रमmat.colorspace = V4L2_COLORSPACE_SRGB;
	dma->क्रमmat.field = V4L2_FIELD_NONE;
	dma->क्रमmat.width = XVIP_DMA_DEF_WIDTH;
	dma->क्रमmat.height = XVIP_DMA_DEF_HEIGHT;
	dma->क्रमmat.bytesperline = dma->क्रमmat.width * dma->fmtinfo->bpp;
	dma->क्रमmat.sizeimage = dma->क्रमmat.bytesperline * dma->क्रमmat.height;

	/* Initialize the media entity... */
	dma->pad.flags = type == V4L2_BUF_TYPE_VIDEO_CAPTURE
		       ? MEDIA_PAD_FL_SINK : MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&dma->video.entity, 1, &dma->pad);
	अगर (ret < 0)
		जाओ error;

	/* ... and the video node... */
	dma->video.fops = &xvip_dma_fops;
	dma->video.v4l2_dev = &xdev->v4l2_dev;
	dma->video.queue = &dma->queue;
	snम_लिखो(dma->video.name, माप(dma->video.name), "%pOFn %s %u",
		 xdev->dev->of_node,
		 type == V4L2_BUF_TYPE_VIDEO_CAPTURE ? "output" : "input",
		 port);
	dma->video.vfl_type = VFL_TYPE_VIDEO;
	dma->video.vfl_dir = type == V4L2_BUF_TYPE_VIDEO_CAPTURE
			   ? VFL_सूची_RX : VFL_सूची_TX;
	dma->video.release = video_device_release_empty;
	dma->video.ioctl_ops = &xvip_dma_ioctl_ops;
	dma->video.lock = &dma->lock;
	dma->video.device_caps = V4L2_CAP_STREAMING;
	अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		dma->video.device_caps |= V4L2_CAP_VIDEO_CAPTURE;
	अन्यथा
		dma->video.device_caps |= V4L2_CAP_VIDEO_OUTPUT;

	video_set_drvdata(&dma->video, dma);

	/* ... and the buffers queue... */
	/* Don't enable VB2_READ and VB2_WRITE, as using the पढ़ो() and ग_लिखो()
	 * V4L2 APIs would be inefficient. Testing on the command line with a
	 * 'cat /dev/video?' thus won't be possible, but given that the driver
	 * anyway requires a test tool to setup the pipeline beक्रमe any video
	 * stream can be started, requiring a specअगरic V4L2 test tool as well
	 * instead of 'cat' isn't really a drawback.
	 */
	dma->queue.type = type;
	dma->queue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	dma->queue.lock = &dma->lock;
	dma->queue.drv_priv = dma;
	dma->queue.buf_काष्ठा_size = माप(काष्ठा xvip_dma_buffer);
	dma->queue.ops = &xvip_dma_queue_qops;
	dma->queue.mem_ops = &vb2_dma_contig_memops;
	dma->queue.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC
				   | V4L2_BUF_FLAG_TSTAMP_SRC_खातापूर्ण;
	dma->queue.dev = dma->xdev->dev;
	ret = vb2_queue_init(&dma->queue);
	अगर (ret < 0) अणु
		dev_err(dma->xdev->dev, "failed to initialize VB2 queue\n");
		जाओ error;
	पूर्ण

	/* ... and the DMA channel. */
	snम_लिखो(name, माप(name), "port%u", port);
	dma->dma = dma_request_chan(dma->xdev->dev, name);
	अगर (IS_ERR(dma->dma)) अणु
		ret = PTR_ERR(dma->dma);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dma->xdev->dev, "no VDMA channel found\n");
		जाओ error;
	पूर्ण

	dma->align = 1 << dma->dma->device->copy_align;

	ret = video_रेजिस्टर_device(&dma->video, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0) अणु
		dev_err(dma->xdev->dev, "failed to register video device\n");
		जाओ error;
	पूर्ण

	वापस 0;

error:
	xvip_dma_cleanup(dma);
	वापस ret;
पूर्ण

व्योम xvip_dma_cleanup(काष्ठा xvip_dma *dma)
अणु
	अगर (video_is_रेजिस्टरed(&dma->video))
		video_unरेजिस्टर_device(&dma->video);

	अगर (!IS_ERR_OR_शून्य(dma->dma))
		dma_release_channel(dma->dma);

	media_entity_cleanup(&dma->video.entity);

	mutex_destroy(&dma->lock);
	mutex_destroy(&dma->pipe.lock);
पूर्ण
