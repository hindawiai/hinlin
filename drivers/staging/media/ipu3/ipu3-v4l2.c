<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Intel Corporation

#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश "ipu3.h"
#समावेश "ipu3-dmamap.h"

/******************** v4l2_subdev_ops ********************/

#घोषणा IPU3_RUNNING_MODE_VIDEO		0
#घोषणा IPU3_RUNNING_MODE_STILL		1

अटल पूर्णांक imgu_subdev_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा imgu_v4l2_subdev *imgu_sd = container_of(sd,
							काष्ठा imgu_v4l2_subdev,
							subdev);
	काष्ठा imgu_device *imgu = v4l2_get_subdevdata(sd);
	काष्ठा imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[imgu_sd->pipe];
	काष्ठा v4l2_rect try_crop = अणु
		.top = 0,
		.left = 0,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	try_crop.width =
		imgu_pipe->nodes[IMGU_NODE_IN].vdev_fmt.fmt.pix_mp.width;
	try_crop.height =
		imgu_pipe->nodes[IMGU_NODE_IN].vdev_fmt.fmt.pix_mp.height;

	/* Initialize try_fmt */
	क्रम (i = 0; i < IMGU_NODE_NUM; i++) अणु
		काष्ठा v4l2_mbus_framefmt *try_fmt =
			v4l2_subdev_get_try_क्रमmat(sd, fh->pad, i);

		try_fmt->width = try_crop.width;
		try_fmt->height = try_crop.height;
		try_fmt->code = imgu_pipe->nodes[i].pad_fmt.code;
		try_fmt->field = V4L2_FIELD_NONE;
	पूर्ण

	*v4l2_subdev_get_try_crop(sd, fh->pad, IMGU_NODE_IN) = try_crop;
	*v4l2_subdev_get_try_compose(sd, fh->pad, IMGU_NODE_IN) = try_crop;

	वापस 0;
पूर्ण

अटल पूर्णांक imgu_subdev_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक node;
	पूर्णांक r = 0;
	काष्ठा imgu_device *imgu = v4l2_get_subdevdata(sd);
	काष्ठा imgu_v4l2_subdev *imgu_sd = container_of(sd,
							काष्ठा imgu_v4l2_subdev,
							subdev);
	अचिन्हित पूर्णांक pipe = imgu_sd->pipe;
	काष्ठा device *dev = &imgu->pci_dev->dev;
	काष्ठा v4l2_pix_क्रमmat_mplane *fmts[IPU3_CSS_QUEUES] = अणु शून्य पूर्ण;
	काष्ठा v4l2_rect *rects[IPU3_CSS_RECTS] = अणु शून्य पूर्ण;
	काष्ठा imgu_css_pipe *css_pipe = &imgu->css.pipes[pipe];
	काष्ठा imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	dev_dbg(dev, "%s %d for pipe %u", __func__, enable, pipe);
	/* grab ctrl after streamon and वापस after off */
	v4l2_ctrl_grab(imgu_sd->ctrl, enable);

	अगर (!enable) अणु
		imgu_sd->active = false;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < IMGU_NODE_NUM; i++)
		imgu_pipe->queue_enabled[i] = imgu_pipe->nodes[i].enabled;

	/* This is handled specially */
	imgu_pipe->queue_enabled[IPU3_CSS_QUEUE_PARAMS] = false;

	/* Initialize CSS क्रमmats */
	क्रम (i = 0; i < IPU3_CSS_QUEUES; i++) अणु
		node = imgu_map_node(imgu, i);
		/* No need to reconfig meta nodes */
		अगर (node == IMGU_NODE_STAT_3A || node == IMGU_NODE_PARAMS)
			जारी;
		fmts[i] = imgu_pipe->queue_enabled[node] ?
			&imgu_pipe->nodes[node].vdev_fmt.fmt.pix_mp : शून्य;
	पूर्ण

	/* Enable VF output only when VF queue requested by user */
	css_pipe->vf_output_en = false;
	अगर (imgu_pipe->nodes[IMGU_NODE_VF].enabled)
		css_pipe->vf_output_en = true;

	अगर (atomic_पढ़ो(&imgu_sd->running_mode) == IPU3_RUNNING_MODE_VIDEO)
		css_pipe->pipe_id = IPU3_CSS_PIPE_ID_VIDEO;
	अन्यथा
		css_pipe->pipe_id = IPU3_CSS_PIPE_ID_CAPTURE;

	dev_dbg(dev, "IPU3 pipe %u pipe_id %u", pipe, css_pipe->pipe_id);

	rects[IPU3_CSS_RECT_EFFECTIVE] = &imgu_sd->rect.eff;
	rects[IPU3_CSS_RECT_BDS] = &imgu_sd->rect.bds;
	rects[IPU3_CSS_RECT_GDC] = &imgu_sd->rect.gdc;

	r = imgu_css_fmt_set(&imgu->css, fmts, rects, pipe);
	अगर (r) अणु
		dev_err(dev, "failed to set initial formats pipe %u with (%d)",
			pipe, r);
		वापस r;
	पूर्ण

	imgu_sd->active = true;

	वापस 0;
पूर्ण

अटल पूर्णांक imgu_subdev_get_fmt(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा imgu_device *imgu = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *mf;
	काष्ठा imgu_media_pipe *imgu_pipe;
	u32 pad = fmt->pad;
	काष्ठा imgu_v4l2_subdev *imgu_sd = container_of(sd,
							काष्ठा imgu_v4l2_subdev,
							subdev);
	अचिन्हित पूर्णांक pipe = imgu_sd->pipe;

	imgu_pipe = &imgu->imgu_pipe[pipe];
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		fmt->क्रमmat = imgu_pipe->nodes[pad].pad_fmt;
	पूर्ण अन्यथा अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, pad);
		fmt->क्रमmat = *mf;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imgu_subdev_set_fmt(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा imgu_media_pipe *imgu_pipe;
	काष्ठा imgu_device *imgu = v4l2_get_subdevdata(sd);
	काष्ठा imgu_v4l2_subdev *imgu_sd = container_of(sd,
							काष्ठा imgu_v4l2_subdev,
							subdev);
	काष्ठा v4l2_mbus_framefmt *mf;
	u32 pad = fmt->pad;
	अचिन्हित पूर्णांक pipe = imgu_sd->pipe;

	dev_dbg(&imgu->pci_dev->dev, "set subdev %u pad %u fmt to [%ux%u]",
		pipe, pad, fmt->क्रमmat.width, fmt->क्रमmat.height);

	imgu_pipe = &imgu->imgu_pipe[pipe];
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, pad);
	अन्यथा
		mf = &imgu_pipe->nodes[pad].pad_fmt;

	fmt->क्रमmat.code = mf->code;
	/* Clamp the w and h based on the hardware capabilities */
	अगर (imgu_sd->subdev_pads[pad].flags & MEDIA_PAD_FL_SOURCE) अणु
		fmt->क्रमmat.width = clamp(fmt->क्रमmat.width,
					  IPU3_OUTPUT_MIN_WIDTH,
					  IPU3_OUTPUT_MAX_WIDTH);
		fmt->क्रमmat.height = clamp(fmt->क्रमmat.height,
					   IPU3_OUTPUT_MIN_HEIGHT,
					   IPU3_OUTPUT_MAX_HEIGHT);
	पूर्ण अन्यथा अणु
		fmt->क्रमmat.width = clamp(fmt->क्रमmat.width,
					  IPU3_INPUT_MIN_WIDTH,
					  IPU3_INPUT_MAX_WIDTH);
		fmt->क्रमmat.height = clamp(fmt->क्रमmat.height,
					   IPU3_INPUT_MIN_HEIGHT,
					   IPU3_INPUT_MAX_HEIGHT);
	पूर्ण

	*mf = fmt->क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक imgu_subdev_get_selection(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा v4l2_rect *try_sel, *r;
	काष्ठा imgu_v4l2_subdev *imgu_sd = container_of(sd,
							काष्ठा imgu_v4l2_subdev,
							subdev);

	अगर (sel->pad != IMGU_NODE_IN)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		try_sel = v4l2_subdev_get_try_crop(sd, cfg, sel->pad);
		r = &imgu_sd->rect.eff;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		try_sel = v4l2_subdev_get_try_compose(sd, cfg, sel->pad);
		r = &imgu_sd->rect.bds;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY)
		sel->r = *try_sel;
	अन्यथा
		sel->r = *r;

	वापस 0;
पूर्ण

अटल पूर्णांक imgu_subdev_set_selection(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा imgu_device *imgu = v4l2_get_subdevdata(sd);
	काष्ठा imgu_v4l2_subdev *imgu_sd = container_of(sd,
							काष्ठा imgu_v4l2_subdev,
							subdev);
	काष्ठा v4l2_rect *rect, *try_sel;

	dev_dbg(&imgu->pci_dev->dev,
		 "set subdev %u sel which %u target 0x%4x rect [%ux%u]",
		 imgu_sd->pipe, sel->which, sel->target,
		 sel->r.width, sel->r.height);

	अगर (sel->pad != IMGU_NODE_IN)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		try_sel = v4l2_subdev_get_try_crop(sd, cfg, sel->pad);
		rect = &imgu_sd->rect.eff;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		try_sel = v4l2_subdev_get_try_compose(sd, cfg, sel->pad);
		rect = &imgu_sd->rect.bds;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY)
		*try_sel = sel->r;
	अन्यथा
		*rect = sel->r;

	वापस 0;
पूर्ण

/******************** media_entity_operations ********************/

अटल पूर्णांक imgu_link_setup(काष्ठा media_entity *entity,
			   स्थिर काष्ठा media_pad *local,
			   स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा imgu_media_pipe *imgu_pipe;
	काष्ठा v4l2_subdev *sd = container_of(entity, काष्ठा v4l2_subdev,
					      entity);
	काष्ठा imgu_device *imgu = v4l2_get_subdevdata(sd);
	काष्ठा imgu_v4l2_subdev *imgu_sd = container_of(sd,
							काष्ठा imgu_v4l2_subdev,
							subdev);
	अचिन्हित पूर्णांक pipe = imgu_sd->pipe;
	u32 pad = local->index;

	WARN_ON(pad >= IMGU_NODE_NUM);

	dev_dbg(&imgu->pci_dev->dev, "pipe %u pad %u is %s", pipe, pad,
		 flags & MEDIA_LNK_FL_ENABLED ? "enabled" : "disabled");

	imgu_pipe = &imgu->imgu_pipe[pipe];
	imgu_pipe->nodes[pad].enabled = flags & MEDIA_LNK_FL_ENABLED;

	/* enable input node to enable the pipe */
	अगर (pad != IMGU_NODE_IN)
		वापस 0;

	अगर (flags & MEDIA_LNK_FL_ENABLED)
		__set_bit(pipe, imgu->css.enabled_pipes);
	अन्यथा
		__clear_bit(pipe, imgu->css.enabled_pipes);

	dev_dbg(&imgu->pci_dev->dev, "pipe %u is %s", pipe,
		 flags & MEDIA_LNK_FL_ENABLED ? "enabled" : "disabled");

	वापस 0;
पूर्ण

/******************** vb2_ops ********************/

अटल पूर्णांक imgu_vb2_buf_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा sg_table *sg = vb2_dma_sg_plane_desc(vb, 0);
	काष्ठा imgu_device *imgu = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा imgu_buffer *buf = container_of(vb,
		काष्ठा imgu_buffer, vid_buf.vbb.vb2_buf);
	काष्ठा imgu_video_device *node =
		container_of(vb->vb2_queue, काष्ठा imgu_video_device, vbq);
	अचिन्हित पूर्णांक queue = imgu_node_to_queue(node->id);

	अगर (queue == IPU3_CSS_QUEUE_PARAMS)
		वापस 0;

	वापस imgu_dmamap_map_sg(imgu, sg->sgl, sg->nents, &buf->map);
पूर्ण

/* Called when each buffer is मुक्तd */
अटल व्योम imgu_vb2_buf_cleanup(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा imgu_device *imgu = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा imgu_buffer *buf = container_of(vb,
		काष्ठा imgu_buffer, vid_buf.vbb.vb2_buf);
	काष्ठा imgu_video_device *node =
		container_of(vb->vb2_queue, काष्ठा imgu_video_device, vbq);
	अचिन्हित पूर्णांक queue = imgu_node_to_queue(node->id);

	अगर (queue == IPU3_CSS_QUEUE_PARAMS)
		वापस;

	imgu_dmamap_unmap(imgu, &buf->map);
पूर्ण

/* Transfer buffer ownership to me */
अटल व्योम imgu_vb2_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा imgu_device *imgu = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा imgu_video_device *node =
		container_of(vb->vb2_queue, काष्ठा imgu_video_device, vbq);
	अचिन्हित पूर्णांक queue = imgu_node_to_queue(node->id);
	काष्ठा imgu_buffer *buf = container_of(vb, काष्ठा imgu_buffer,
					       vid_buf.vbb.vb2_buf);
	अचिन्हित दीर्घ need_bytes;
	अचिन्हित दीर्घ payload = vb2_get_plane_payload(vb, 0);

	अगर (vb->vb2_queue->type == V4L2_BUF_TYPE_META_CAPTURE ||
	    vb->vb2_queue->type == V4L2_BUF_TYPE_META_OUTPUT)
		need_bytes = node->vdev_fmt.fmt.meta.buffersize;
	अन्यथा
		need_bytes = node->vdev_fmt.fmt.pix_mp.plane_fmt[0].sizeimage;

	अगर (queue == IPU3_CSS_QUEUE_PARAMS && payload && payload < need_bytes) अणु
		dev_err(&imgu->pci_dev->dev, "invalid data size for params.");
		vb2_buffer_करोne(vb, VB2_BUF_STATE_ERROR);
		वापस;
	पूर्ण

	mutex_lock(&imgu->lock);
	अगर (queue != IPU3_CSS_QUEUE_PARAMS)
		imgu_css_buf_init(&buf->css_buf, queue, buf->map.daddr);

	list_add_tail(&buf->vid_buf.list, &node->buffers);
	mutex_unlock(&imgu->lock);

	vb2_set_plane_payload(vb, 0, need_bytes);

	mutex_lock(&imgu->streaming_lock);
	अगर (imgu->streaming)
		imgu_queue_buffers(imgu, false, node->pipe);
	mutex_unlock(&imgu->streaming_lock);

	dev_dbg(&imgu->pci_dev->dev, "%s for pipe %u node %u", __func__,
		node->pipe, node->id);
पूर्ण

अटल पूर्णांक imgu_vb2_queue_setup(काष्ठा vb2_queue *vq,
				अचिन्हित पूर्णांक *num_buffers,
				अचिन्हित पूर्णांक *num_planes,
				अचिन्हित पूर्णांक sizes[],
				काष्ठा device *alloc_devs[])
अणु
	काष्ठा imgu_device *imgu = vb2_get_drv_priv(vq);
	काष्ठा imgu_video_device *node =
		container_of(vq, काष्ठा imgu_video_device, vbq);
	स्थिर काष्ठा v4l2_क्रमmat *fmt = &node->vdev_fmt;
	अचिन्हित पूर्णांक size;

	*num_buffers = clamp_val(*num_buffers, 1, VB2_MAX_FRAME);
	alloc_devs[0] = &imgu->pci_dev->dev;

	अगर (vq->type == V4L2_BUF_TYPE_META_CAPTURE ||
	    vq->type == V4L2_BUF_TYPE_META_OUTPUT)
		size = fmt->fmt.meta.buffersize;
	अन्यथा
		size = fmt->fmt.pix_mp.plane_fmt[0].sizeimage;

	अगर (*num_planes) अणु
		अगर (sizes[0] < size)
			वापस -EINVAL;
		size = sizes[0];
	पूर्ण

	*num_planes = 1;
	sizes[0] = size;

	/* Initialize buffer queue */
	INIT_LIST_HEAD(&node->buffers);

	वापस 0;
पूर्ण

/* Check अगर all enabled video nodes are streaming, exception ignored */
अटल bool imgu_all_nodes_streaming(काष्ठा imgu_device *imgu,
				     काष्ठा imgu_video_device *except)
अणु
	अचिन्हित पूर्णांक i, pipe, p;
	काष्ठा imgu_video_device *node;
	काष्ठा device *dev = &imgu->pci_dev->dev;

	pipe = except->pipe;
	अगर (!test_bit(pipe, imgu->css.enabled_pipes)) अणु
		dev_warn(&imgu->pci_dev->dev,
			 "pipe %u link is not ready yet", pipe);
		वापस false;
	पूर्ण

	क्रम_each_set_bit(p, imgu->css.enabled_pipes, IMGU_MAX_PIPE_NUM) अणु
		क्रम (i = 0; i < IMGU_NODE_NUM; i++) अणु
			node = &imgu->imgu_pipe[p].nodes[i];
			dev_dbg(dev, "%s pipe %u queue %u name %s enabled = %u",
				__func__, p, i, node->name, node->enabled);
			अगर (node == except)
				जारी;
			अगर (node->enabled && !vb2_start_streaming_called(&node->vbq))
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम imgu_वापस_all_buffers(काष्ठा imgu_device *imgu,
				    काष्ठा imgu_video_device *node,
				    क्रमागत vb2_buffer_state state)
अणु
	काष्ठा imgu_vb2_buffer *b, *b0;

	/* Return all buffers */
	mutex_lock(&imgu->lock);
	list_क्रम_each_entry_safe(b, b0, &node->buffers, list) अणु
		list_del(&b->list);
		vb2_buffer_करोne(&b->vbb.vb2_buf, state);
	पूर्ण
	mutex_unlock(&imgu->lock);
पूर्ण

अटल पूर्णांक imgu_vb2_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा imgu_media_pipe *imgu_pipe;
	काष्ठा imgu_device *imgu = vb2_get_drv_priv(vq);
	काष्ठा device *dev = &imgu->pci_dev->dev;
	काष्ठा imgu_video_device *node =
		container_of(vq, काष्ठा imgu_video_device, vbq);
	पूर्णांक r;
	अचिन्हित पूर्णांक pipe;

	dev_dbg(dev, "%s node name %s pipe %u id %u", __func__,
		node->name, node->pipe, node->id);

	mutex_lock(&imgu->streaming_lock);
	अगर (imgu->streaming) अणु
		r = -EBUSY;
		mutex_unlock(&imgu->streaming_lock);
		जाओ fail_वापस_bufs;
	पूर्ण
	mutex_unlock(&imgu->streaming_lock);

	अगर (!node->enabled) अणु
		dev_err(dev, "IMGU node is not enabled");
		r = -EINVAL;
		जाओ fail_वापस_bufs;
	पूर्ण

	pipe = node->pipe;
	imgu_pipe = &imgu->imgu_pipe[pipe];
	r = media_pipeline_start(&node->vdev.entity, &imgu_pipe->pipeline);
	अगर (r < 0)
		जाओ fail_वापस_bufs;

	अगर (!imgu_all_nodes_streaming(imgu, node))
		वापस 0;

	क्रम_each_set_bit(pipe, imgu->css.enabled_pipes, IMGU_MAX_PIPE_NUM) अणु
		r = v4l2_subdev_call(&imgu->imgu_pipe[pipe].imgu_sd.subdev,
				     video, s_stream, 1);
		अगर (r < 0)
			जाओ fail_stop_pipeline;
	पूर्ण

	/* Start streaming of the whole pipeline now */
	dev_dbg(dev, "IMGU streaming is ready to start");
	mutex_lock(&imgu->streaming_lock);
	r = imgu_s_stream(imgu, true);
	अगर (!r)
		imgu->streaming = true;
	mutex_unlock(&imgu->streaming_lock);

	वापस 0;

fail_stop_pipeline:
	media_pipeline_stop(&node->vdev.entity);
fail_वापस_bufs:
	imgu_वापस_all_buffers(imgu, node, VB2_BUF_STATE_QUEUED);

	वापस r;
पूर्ण

अटल व्योम imgu_vb2_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा imgu_media_pipe *imgu_pipe;
	काष्ठा imgu_device *imgu = vb2_get_drv_priv(vq);
	काष्ठा device *dev = &imgu->pci_dev->dev;
	काष्ठा imgu_video_device *node =
		container_of(vq, काष्ठा imgu_video_device, vbq);
	पूर्णांक r;
	अचिन्हित पूर्णांक pipe;

	WARN_ON(!node->enabled);

	pipe = node->pipe;
	dev_dbg(dev, "Try to stream off node [%u][%u]", pipe, node->id);
	imgu_pipe = &imgu->imgu_pipe[pipe];
	r = v4l2_subdev_call(&imgu_pipe->imgu_sd.subdev, video, s_stream, 0);
	अगर (r)
		dev_err(&imgu->pci_dev->dev,
			"failed to stop subdev streaming\n");

	mutex_lock(&imgu->streaming_lock);
	/* Was this the first node with streaming disabled? */
	अगर (imgu->streaming && imgu_all_nodes_streaming(imgu, node)) अणु
		/* Yes, really stop streaming now */
		dev_dbg(dev, "IMGU streaming is ready to stop");
		r = imgu_s_stream(imgu, false);
		अगर (!r)
			imgu->streaming = false;
	पूर्ण

	imgu_वापस_all_buffers(imgu, node, VB2_BUF_STATE_ERROR);
	mutex_unlock(&imgu->streaming_lock);

	media_pipeline_stop(&node->vdev.entity);
पूर्ण

/******************** v4l2_ioctl_ops ********************/

#घोषणा VID_CAPTURE	0
#घोषणा VID_OUTPUT	1
#घोषणा DEF_VID_CAPTURE	0
#घोषणा DEF_VID_OUTPUT	1

काष्ठा imgu_fmt अणु
	u32	fourcc;
	u16	type; /* VID_CAPTURE or VID_OUTPUT not both */
पूर्ण;

/* क्रमmat descriptions क्रम capture and preview */
अटल स्थिर काष्ठा imgu_fmt क्रमmats[] = अणु
	अणु V4L2_PIX_FMT_NV12, VID_CAPTURE पूर्ण,
	अणु V4L2_PIX_FMT_IPU3_SGRBG10, VID_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_IPU3_SBGGR10, VID_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_IPU3_SGBRG10, VID_OUTPUT पूर्ण,
	अणु V4L2_PIX_FMT_IPU3_SRGGB10, VID_OUTPUT पूर्ण,
पूर्ण;

/* Find the first matched क्रमmat, वापस शेष अगर not found */
अटल स्थिर काष्ठा imgu_fmt *find_क्रमmat(काष्ठा v4l2_क्रमmat *f, u32 type)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++) अणु
		अगर (क्रमmats[i].fourcc == f->fmt.pix_mp.pixelक्रमmat &&
		    क्रमmats[i].type == type)
			वापस &क्रमmats[i];
	पूर्ण

	वापस type == VID_CAPTURE ? &क्रमmats[DEF_VID_CAPTURE] :
				     &क्रमmats[DEF_VID_OUTPUT];
पूर्ण

अटल पूर्णांक imgu_vidioc_querycap(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_capability *cap)
अणु
	काष्ठा imgu_video_device *node = file_to_पूर्णांकel_imgu_node(file);

	strscpy(cap->driver, IMGU_NAME, माप(cap->driver));
	strscpy(cap->card, IMGU_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "PCI:%s", node->name);

	वापस 0;
पूर्ण

अटल पूर्णांक क्रमागत_fmts(काष्ठा v4l2_fmtdesc *f, u32 type)
अणु
	अचिन्हित पूर्णांक i, j;

	अगर (f->mbus_code != 0 && f->mbus_code != MEDIA_BUS_FMT_FIXED)
		वापस -EINVAL;

	क्रम (i = j = 0; i < ARRAY_SIZE(क्रमmats); ++i) अणु
		अगर (क्रमmats[i].type == type) अणु
			अगर (j == f->index)
				अवरोध;
			++j;
		पूर्ण
	पूर्ण

	अगर (i < ARRAY_SIZE(क्रमmats)) अणु
		f->pixelक्रमmat = क्रमmats[i].fourcc;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		वापस -EINVAL;

	वापस क्रमागत_fmts(f, VID_CAPTURE);
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		वापस -EINVAL;

	वापस क्रमागत_fmts(f, VID_OUTPUT);
पूर्ण

/* Propagate क्रमward always the क्रमmat from the CIO2 subdev */
अटल पूर्णांक imgu_vidioc_g_fmt(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा imgu_video_device *node = file_to_पूर्णांकel_imgu_node(file);

	f->fmt = node->vdev_fmt.fmt;

	वापस 0;
पूर्ण

/*
 * Set input/output क्रमmat. Unless it is just a try, this also resets
 * selections (ie. effective and BDS resolutions) to शेषs.
 */
अटल पूर्णांक imgu_fmt(काष्ठा imgu_device *imgu, अचिन्हित पूर्णांक pipe, पूर्णांक node,
		    काष्ठा v4l2_क्रमmat *f, bool try)
अणु
	काष्ठा device *dev = &imgu->pci_dev->dev;
	काष्ठा v4l2_pix_क्रमmat_mplane *fmts[IPU3_CSS_QUEUES] = अणु शून्य पूर्ण;
	काष्ठा v4l2_rect *rects[IPU3_CSS_RECTS] = अणु शून्य पूर्ण;
	काष्ठा v4l2_mbus_framefmt pad_fmt;
	अचिन्हित पूर्णांक i, css_q;
	पूर्णांक ret;
	काष्ठा imgu_css_pipe *css_pipe = &imgu->css.pipes[pipe];
	काष्ठा imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];
	काष्ठा imgu_v4l2_subdev *imgu_sd = &imgu_pipe->imgu_sd;

	dev_dbg(dev, "set fmt node [%u][%u](try = %u)", pipe, node, try);

	क्रम (i = 0; i < IMGU_NODE_NUM; i++)
		dev_dbg(dev, "IMGU pipe %u node %u enabled = %u",
			pipe, i, imgu_pipe->nodes[i].enabled);

	अगर (imgu_pipe->nodes[IMGU_NODE_VF].enabled)
		css_pipe->vf_output_en = true;

	अगर (atomic_पढ़ो(&imgu_sd->running_mode) == IPU3_RUNNING_MODE_VIDEO)
		css_pipe->pipe_id = IPU3_CSS_PIPE_ID_VIDEO;
	अन्यथा
		css_pipe->pipe_id = IPU3_CSS_PIPE_ID_CAPTURE;

	dev_dbg(dev, "IPU3 pipe %u pipe_id = %u", pipe, css_pipe->pipe_id);

	css_q = imgu_node_to_queue(node);
	क्रम (i = 0; i < IPU3_CSS_QUEUES; i++) अणु
		अचिन्हित पूर्णांक inode = imgu_map_node(imgu, i);

		/* Skip the meta node */
		अगर (inode == IMGU_NODE_STAT_3A || inode == IMGU_NODE_PARAMS)
			जारी;

		/* CSS expects some क्रमmat on OUT queue */
		अगर (i != IPU3_CSS_QUEUE_OUT &&
		    !imgu_pipe->nodes[inode].enabled) अणु
			fmts[i] = शून्य;
			जारी;
		पूर्ण

		अगर (i == css_q) अणु
			fmts[i] = &f->fmt.pix_mp;
			जारी;
		पूर्ण

		अगर (try) अणु
			fmts[i] = kmemdup(&imgu_pipe->nodes[inode].vdev_fmt.fmt.pix_mp,
					  माप(काष्ठा v4l2_pix_क्रमmat_mplane),
					  GFP_KERNEL);
			अगर (!fmts[i]) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			fmts[i] = &imgu_pipe->nodes[inode].vdev_fmt.fmt.pix_mp;
		पूर्ण

	पूर्ण

	अगर (!try) अणु
		/* eff and bds res got by imgu_s_sel */
		काष्ठा imgu_v4l2_subdev *imgu_sd = &imgu_pipe->imgu_sd;

		rects[IPU3_CSS_RECT_EFFECTIVE] = &imgu_sd->rect.eff;
		rects[IPU3_CSS_RECT_BDS] = &imgu_sd->rect.bds;
		rects[IPU3_CSS_RECT_GDC] = &imgu_sd->rect.gdc;

		/* suppose that pad fmt was set by subdev s_fmt beक्रमe */
		pad_fmt = imgu_pipe->nodes[IMGU_NODE_IN].pad_fmt;
		rects[IPU3_CSS_RECT_GDC]->width = pad_fmt.width;
		rects[IPU3_CSS_RECT_GDC]->height = pad_fmt.height;
	पूर्ण

	अगर (!fmts[css_q]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (try)
		ret = imgu_css_fmt_try(&imgu->css, fmts, rects, pipe);
	अन्यथा
		ret = imgu_css_fmt_set(&imgu->css, fmts, rects, pipe);

	/* ret is the binary number in the firmware blob */
	अगर (ret < 0)
		जाओ out;

	/*
	 * imgu करोesn't set the node to the value given by user
	 * beक्रमe we वापस success from this function, so set it here.
	 */
	अगर (!try)
		imgu_pipe->nodes[node].vdev_fmt.fmt.pix_mp = f->fmt.pix_mp;

out:
	अगर (try) अणु
		क्रम (i = 0; i < IPU3_CSS_QUEUES; i++)
			अगर (i != css_q)
				kमुक्त(fmts[i]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक imgu_try_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pixm = &f->fmt.pix_mp;
	स्थिर काष्ठा imgu_fmt *fmt;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		fmt = find_क्रमmat(f, VID_CAPTURE);
	अन्यथा अगर (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		fmt = find_क्रमmat(f, VID_OUTPUT);
	अन्यथा
		वापस -EINVAL;

	pixm->pixelक्रमmat = fmt->fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक imgu_vidioc_try_fmt(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा imgu_device *imgu = video_drvdata(file);
	काष्ठा device *dev = &imgu->pci_dev->dev;
	काष्ठा imgu_video_device *node = file_to_पूर्णांकel_imgu_node(file);
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp = &f->fmt.pix_mp;
	पूर्णांक r;

	dev_dbg(dev, "%s [%ux%u] for node %u\n", __func__,
		pix_mp->width, pix_mp->height, node->id);

	r = imgu_try_fmt(file, fh, f);
	अगर (r)
		वापस r;

	वापस imgu_fmt(imgu, node->pipe, node->id, f, true);
पूर्ण

अटल पूर्णांक imgu_vidioc_s_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा imgu_device *imgu = video_drvdata(file);
	काष्ठा device *dev = &imgu->pci_dev->dev;
	काष्ठा imgu_video_device *node = file_to_पूर्णांकel_imgu_node(file);
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp = &f->fmt.pix_mp;
	पूर्णांक r;

	dev_dbg(dev, "%s [%ux%u] for node %u\n", __func__,
		pix_mp->width, pix_mp->height, node->id);

	r = imgu_try_fmt(file, fh, f);
	अगर (r)
		वापस r;

	वापस imgu_fmt(imgu, node->pipe, node->id, f, false);
पूर्ण

काष्ठा imgu_meta_fmt अणु
	__u32 fourcc;
	अक्षर *name;
पूर्ण;

/* From drivers/media/v4l2-core/v4l2-ioctl.c */
अटल स्थिर काष्ठा imgu_meta_fmt meta_fmts[] = अणु
	अणु V4L2_META_FMT_IPU3_PARAMS, "IPU3 processing parameters" पूर्ण,
	अणु V4L2_META_FMT_IPU3_STAT_3A, "IPU3 3A statistics" पूर्ण,
पूर्ण;

अटल पूर्णांक imgu_meta_क्रमागत_क्रमmat(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_fmtdesc *fmt)
अणु
	काष्ठा imgu_video_device *node = file_to_पूर्णांकel_imgu_node(file);
	अचिन्हित पूर्णांक i = fmt->type == V4L2_BUF_TYPE_META_OUTPUT ? 0 : 1;

	/* Each node is dedicated to only one meta क्रमmat */
	अगर (fmt->index > 0 || fmt->type != node->vbq.type)
		वापस -EINVAL;

	अगर (fmt->mbus_code != 0 && fmt->mbus_code != MEDIA_BUS_FMT_FIXED)
		वापस -EINVAL;

	strscpy(fmt->description, meta_fmts[i].name, माप(fmt->description));
	fmt->pixelक्रमmat = meta_fmts[i].fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक imgu_vidioc_g_meta_fmt(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा imgu_video_device *node = file_to_पूर्णांकel_imgu_node(file);

	अगर (f->type != node->vbq.type)
		वापस -EINVAL;

	f->fmt = node->vdev_fmt.fmt;

	वापस 0;
पूर्ण

/******************** function poपूर्णांकers ********************/

अटल काष्ठा v4l2_subdev_पूर्णांकernal_ops imgu_subdev_पूर्णांकernal_ops = अणु
	.खोलो = imgu_subdev_खोलो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops imgu_subdev_core_ops = अणु
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops imgu_subdev_video_ops = अणु
	.s_stream = imgu_subdev_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops imgu_subdev_pad_ops = अणु
	.link_validate = v4l2_subdev_link_validate_शेष,
	.get_fmt = imgu_subdev_get_fmt,
	.set_fmt = imgu_subdev_set_fmt,
	.get_selection = imgu_subdev_get_selection,
	.set_selection = imgu_subdev_set_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops imgu_subdev_ops = अणु
	.core = &imgu_subdev_core_ops,
	.video = &imgu_subdev_video_ops,
	.pad = &imgu_subdev_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations imgu_media_ops = अणु
	.link_setup = imgu_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

/****************** vb2_ops of the Q ********************/

अटल स्थिर काष्ठा vb2_ops imgu_vb2_ops = अणु
	.buf_init = imgu_vb2_buf_init,
	.buf_cleanup = imgu_vb2_buf_cleanup,
	.buf_queue = imgu_vb2_buf_queue,
	.queue_setup = imgu_vb2_queue_setup,
	.start_streaming = imgu_vb2_start_streaming,
	.stop_streaming = imgu_vb2_stop_streaming,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
पूर्ण;

/****************** v4l2_file_operations *****************/

अटल स्थिर काष्ठा v4l2_file_operations imgu_v4l2_fops = अणु
	.unlocked_ioctl = video_ioctl2,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.poll = vb2_fop_poll,
	.mmap = vb2_fop_mmap,
पूर्ण;

/******************** v4l2_ioctl_ops ********************/

अटल स्थिर काष्ठा v4l2_ioctl_ops imgu_v4l2_ioctl_ops = अणु
	.vidioc_querycap = imgu_vidioc_querycap,

	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap_mplane = imgu_vidioc_g_fmt,
	.vidioc_s_fmt_vid_cap_mplane = imgu_vidioc_s_fmt,
	.vidioc_try_fmt_vid_cap_mplane = imgu_vidioc_try_fmt,

	.vidioc_क्रमागत_fmt_vid_out = vidioc_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_out_mplane = imgu_vidioc_g_fmt,
	.vidioc_s_fmt_vid_out_mplane = imgu_vidioc_s_fmt,
	.vidioc_try_fmt_vid_out_mplane = imgu_vidioc_try_fmt,

	/* buffer queue management */
	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf = vb2_ioctl_prepare_buf,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,
	.vidioc_expbuf = vb2_ioctl_expbuf,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops imgu_v4l2_meta_ioctl_ops = अणु
	.vidioc_querycap = imgu_vidioc_querycap,

	/* meta capture */
	.vidioc_क्रमागत_fmt_meta_cap = imgu_meta_क्रमागत_क्रमmat,
	.vidioc_g_fmt_meta_cap = imgu_vidioc_g_meta_fmt,
	.vidioc_s_fmt_meta_cap = imgu_vidioc_g_meta_fmt,
	.vidioc_try_fmt_meta_cap = imgu_vidioc_g_meta_fmt,

	/* meta output */
	.vidioc_क्रमागत_fmt_meta_out = imgu_meta_क्रमागत_क्रमmat,
	.vidioc_g_fmt_meta_out = imgu_vidioc_g_meta_fmt,
	.vidioc_s_fmt_meta_out = imgu_vidioc_g_meta_fmt,
	.vidioc_try_fmt_meta_out = imgu_vidioc_g_meta_fmt,

	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf = vb2_ioctl_prepare_buf,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,
	.vidioc_expbuf = vb2_ioctl_expbuf,
पूर्ण;

अटल पूर्णांक imgu_sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा imgu_v4l2_subdev *imgu_sd =
		container_of(ctrl->handler, काष्ठा imgu_v4l2_subdev, ctrl_handler);
	काष्ठा imgu_device *imgu = v4l2_get_subdevdata(&imgu_sd->subdev);
	काष्ठा device *dev = &imgu->pci_dev->dev;

	dev_dbg(dev, "set val %d to ctrl 0x%8x for subdev %u",
		ctrl->val, ctrl->id, imgu_sd->pipe);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_INTEL_IPU3_MODE:
		atomic_set(&imgu_sd->running_mode, ctrl->val);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops imgu_subdev_ctrl_ops = अणु
	.s_ctrl = imgu_sd_s_ctrl,
पूर्ण;

अटल स्थिर अक्षर * स्थिर imgu_ctrl_mode_strings[] = अणु
	"Video mode",
	"Still mode",
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config imgu_subdev_ctrl_mode = अणु
	.ops = &imgu_subdev_ctrl_ops,
	.id = V4L2_CID_INTEL_IPU3_MODE,
	.name = "IPU3 Pipe Mode",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = ARRAY_SIZE(imgu_ctrl_mode_strings) - 1,
	.def = IPU3_RUNNING_MODE_VIDEO,
	.qmenu = imgu_ctrl_mode_strings,
पूर्ण;

/******************** Framework registration ********************/

/* helper function to config node's video properties */
अटल व्योम imgu_node_to_v4l2(u32 node, काष्ठा video_device *vdev,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	u32 cap;

	/* Should not happen */
	WARN_ON(node >= IMGU_NODE_NUM);

	चयन (node) अणु
	हाल IMGU_NODE_IN:
		cap = V4L2_CAP_VIDEO_OUTPUT_MPLANE;
		f->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
		vdev->ioctl_ops = &imgu_v4l2_ioctl_ops;
		अवरोध;
	हाल IMGU_NODE_PARAMS:
		cap = V4L2_CAP_META_OUTPUT;
		f->type = V4L2_BUF_TYPE_META_OUTPUT;
		f->fmt.meta.dataक्रमmat = V4L2_META_FMT_IPU3_PARAMS;
		vdev->ioctl_ops = &imgu_v4l2_meta_ioctl_ops;
		imgu_css_meta_fmt_set(&f->fmt.meta);
		अवरोध;
	हाल IMGU_NODE_STAT_3A:
		cap = V4L2_CAP_META_CAPTURE;
		f->type = V4L2_BUF_TYPE_META_CAPTURE;
		f->fmt.meta.dataक्रमmat = V4L2_META_FMT_IPU3_STAT_3A;
		vdev->ioctl_ops = &imgu_v4l2_meta_ioctl_ops;
		imgu_css_meta_fmt_set(&f->fmt.meta);
		अवरोध;
	शेष:
		cap = V4L2_CAP_VIDEO_CAPTURE_MPLANE;
		f->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
		vdev->ioctl_ops = &imgu_v4l2_ioctl_ops;
	पूर्ण

	vdev->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_IO_MC | cap;
पूर्ण

अटल पूर्णांक imgu_v4l2_subdev_रेजिस्टर(काष्ठा imgu_device *imgu,
				     काष्ठा imgu_v4l2_subdev *imgu_sd,
				     अचिन्हित पूर्णांक pipe)
अणु
	पूर्णांक i, r;
	काष्ठा v4l2_ctrl_handler *hdl = &imgu_sd->ctrl_handler;
	काष्ठा imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	/* Initialize subdev media entity */
	r = media_entity_pads_init(&imgu_sd->subdev.entity, IMGU_NODE_NUM,
				   imgu_sd->subdev_pads);
	अगर (r) अणु
		dev_err(&imgu->pci_dev->dev,
			"failed initialize subdev media entity (%d)\n", r);
		वापस r;
	पूर्ण
	imgu_sd->subdev.entity.ops = &imgu_media_ops;
	क्रम (i = 0; i < IMGU_NODE_NUM; i++) अणु
		imgu_sd->subdev_pads[i].flags = imgu_pipe->nodes[i].output ?
			MEDIA_PAD_FL_SINK : MEDIA_PAD_FL_SOURCE;
	पूर्ण

	/* Initialize subdev */
	v4l2_subdev_init(&imgu_sd->subdev, &imgu_subdev_ops);
	imgu_sd->subdev.entity.function = MEDIA_ENT_F_PROC_VIDEO_STATISTICS;
	imgu_sd->subdev.पूर्णांकernal_ops = &imgu_subdev_पूर्णांकernal_ops;
	imgu_sd->subdev.flags = V4L2_SUBDEV_FL_HAS_DEVNODE |
				V4L2_SUBDEV_FL_HAS_EVENTS;
	snम_लिखो(imgu_sd->subdev.name, माप(imgu_sd->subdev.name),
		 "%s %u", IMGU_NAME, pipe);
	v4l2_set_subdevdata(&imgu_sd->subdev, imgu);
	atomic_set(&imgu_sd->running_mode, IPU3_RUNNING_MODE_VIDEO);
	v4l2_ctrl_handler_init(hdl, 1);
	imgu_sd->subdev.ctrl_handler = hdl;
	imgu_sd->ctrl = v4l2_ctrl_new_custom(hdl, &imgu_subdev_ctrl_mode, शून्य);
	अगर (hdl->error) अणु
		r = hdl->error;
		dev_err(&imgu->pci_dev->dev,
			"failed to create subdev v4l2 ctrl with err %d", r);
		जाओ fail_subdev;
	पूर्ण
	r = v4l2_device_रेजिस्टर_subdev(&imgu->v4l2_dev, &imgu_sd->subdev);
	अगर (r) अणु
		dev_err(&imgu->pci_dev->dev,
			"failed initialize subdev (%d)\n", r);
		जाओ fail_subdev;
	पूर्ण

	imgu_sd->pipe = pipe;
	वापस 0;

fail_subdev:
	v4l2_ctrl_handler_मुक्त(imgu_sd->subdev.ctrl_handler);
	media_entity_cleanup(&imgu_sd->subdev.entity);

	वापस r;
पूर्ण

अटल पूर्णांक imgu_v4l2_node_setup(काष्ठा imgu_device *imgu, अचिन्हित पूर्णांक pipe,
				पूर्णांक node_num)
अणु
	पूर्णांक r;
	u32 flags;
	काष्ठा v4l2_mbus_framefmt def_bus_fmt = अणु 0 पूर्ण;
	काष्ठा v4l2_pix_क्रमmat_mplane def_pix_fmt = अणु 0 पूर्ण;
	काष्ठा device *dev = &imgu->pci_dev->dev;
	काष्ठा imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];
	काष्ठा v4l2_subdev *sd = &imgu_pipe->imgu_sd.subdev;
	काष्ठा imgu_video_device *node = &imgu_pipe->nodes[node_num];
	काष्ठा video_device *vdev = &node->vdev;
	काष्ठा vb2_queue *vbq = &node->vbq;

	/* Initialize क्रमmats to शेष values */
	def_bus_fmt.width = 1920;
	def_bus_fmt.height = 1080;
	def_bus_fmt.code = MEDIA_BUS_FMT_FIXED;
	def_bus_fmt.field = V4L2_FIELD_NONE;
	def_bus_fmt.colorspace = V4L2_COLORSPACE_RAW;
	def_bus_fmt.ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	def_bus_fmt.quantization = V4L2_QUANTIZATION_DEFAULT;
	def_bus_fmt.xfer_func = V4L2_XFER_FUNC_DEFAULT;

	def_pix_fmt.width = def_bus_fmt.width;
	def_pix_fmt.height = def_bus_fmt.height;
	def_pix_fmt.field = def_bus_fmt.field;
	def_pix_fmt.num_planes = 1;
	def_pix_fmt.plane_fmt[0].bytesperline = def_pix_fmt.width * 2;
	def_pix_fmt.plane_fmt[0].sizeimage =
		def_pix_fmt.height * def_pix_fmt.plane_fmt[0].bytesperline;
	def_pix_fmt.flags = 0;
	def_pix_fmt.colorspace = def_bus_fmt.colorspace;
	def_pix_fmt.ycbcr_enc = def_bus_fmt.ycbcr_enc;
	def_pix_fmt.quantization = def_bus_fmt.quantization;
	def_pix_fmt.xfer_func = def_bus_fmt.xfer_func;

	/* Initialize miscellaneous variables */
	mutex_init(&node->lock);
	INIT_LIST_HEAD(&node->buffers);

	/* Initialize क्रमmats to शेष values */
	node->pad_fmt = def_bus_fmt;
	node->id = node_num;
	node->pipe = pipe;
	imgu_node_to_v4l2(node_num, vdev, &node->vdev_fmt);
	अगर (node->vdev_fmt.type ==
	    V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ||
	    node->vdev_fmt.type ==
	    V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		def_pix_fmt.pixelक्रमmat = node->output ?
			V4L2_PIX_FMT_IPU3_SGRBG10 :
			V4L2_PIX_FMT_NV12;
		node->vdev_fmt.fmt.pix_mp = def_pix_fmt;
	पूर्ण

	/* Initialize media entities */
	r = media_entity_pads_init(&vdev->entity, 1, &node->vdev_pad);
	अगर (r) अणु
		dev_err(dev, "failed initialize media entity (%d)\n", r);
		mutex_destroy(&node->lock);
		वापस r;
	पूर्ण
	node->vdev_pad.flags = node->output ?
		MEDIA_PAD_FL_SOURCE : MEDIA_PAD_FL_SINK;
	vdev->entity.ops = शून्य;

	/* Initialize vbq */
	vbq->type = node->vdev_fmt.type;
	vbq->io_modes = VB2_USERPTR | VB2_MMAP | VB2_DMABUF;
	vbq->ops = &imgu_vb2_ops;
	vbq->mem_ops = &vb2_dma_sg_memops;
	अगर (imgu->buf_काष्ठा_size <= 0)
		imgu->buf_काष्ठा_size =
			माप(काष्ठा imgu_vb2_buffer);
	vbq->buf_काष्ठा_size = imgu->buf_काष्ठा_size;
	vbq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	/* can streamon w/o buffers */
	vbq->min_buffers_needed = 0;
	vbq->drv_priv = imgu;
	vbq->lock = &node->lock;
	r = vb2_queue_init(vbq);
	अगर (r) अणु
		dev_err(dev, "failed to initialize video queue (%d)", r);
		media_entity_cleanup(&vdev->entity);
		वापस r;
	पूर्ण

	/* Initialize vdev */
	snम_लिखो(vdev->name, माप(vdev->name), "%s %u %s",
		 IMGU_NAME, pipe, node->name);
	vdev->release = video_device_release_empty;
	vdev->fops = &imgu_v4l2_fops;
	vdev->lock = &node->lock;
	vdev->v4l2_dev = &imgu->v4l2_dev;
	vdev->queue = &node->vbq;
	vdev->vfl_dir = node->output ? VFL_सूची_TX : VFL_सूची_RX;
	video_set_drvdata(vdev, imgu);
	r = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (r) अणु
		dev_err(dev, "failed to register video device (%d)", r);
		media_entity_cleanup(&vdev->entity);
		वापस r;
	पूर्ण

	/* Create link between video node and the subdev pad */
	flags = 0;
	अगर (node->enabled)
		flags |= MEDIA_LNK_FL_ENABLED;
	अगर (node->output) अणु
		r = media_create_pad_link(&vdev->entity, 0, &sd->entity,
					  node_num, flags);
	पूर्ण अन्यथा अणु
		अगर (node->id == IMGU_NODE_OUT) अणु
			flags |= MEDIA_LNK_FL_ENABLED | MEDIA_LNK_FL_IMMUTABLE;
			node->enabled = true;
		पूर्ण

		r = media_create_pad_link(&sd->entity, node_num, &vdev->entity,
					  0, flags);
	पूर्ण
	अगर (r) अणु
		dev_err(dev, "failed to create pad link (%d)", r);
		video_unरेजिस्टर_device(vdev);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम imgu_v4l2_nodes_cleanup_pipe(काष्ठा imgu_device *imgu,
					 अचिन्हित पूर्णांक pipe, पूर्णांक node)
अणु
	पूर्णांक i;
	काष्ठा imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	क्रम (i = 0; i < node; i++) अणु
		video_unरेजिस्टर_device(&imgu_pipe->nodes[i].vdev);
		media_entity_cleanup(&imgu_pipe->nodes[i].vdev.entity);
		mutex_destroy(&imgu_pipe->nodes[i].lock);
	पूर्ण
पूर्ण

अटल पूर्णांक imgu_v4l2_nodes_setup_pipe(काष्ठा imgu_device *imgu, पूर्णांक pipe)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IMGU_NODE_NUM; i++) अणु
		पूर्णांक r = imgu_v4l2_node_setup(imgu, pipe, i);

		अगर (r) अणु
			imgu_v4l2_nodes_cleanup_pipe(imgu, pipe, i);
			वापस r;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम imgu_v4l2_subdev_cleanup(काष्ठा imgu_device *imgu, अचिन्हित पूर्णांक i)
अणु
	काष्ठा imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[i];

	v4l2_device_unरेजिस्टर_subdev(&imgu_pipe->imgu_sd.subdev);
	v4l2_ctrl_handler_मुक्त(imgu_pipe->imgu_sd.subdev.ctrl_handler);
	media_entity_cleanup(&imgu_pipe->imgu_sd.subdev.entity);
पूर्ण

अटल व्योम imgu_v4l2_cleanup_pipes(काष्ठा imgu_device *imgu, अचिन्हित पूर्णांक pipe)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pipe; i++) अणु
		imgu_v4l2_nodes_cleanup_pipe(imgu, i, IMGU_NODE_NUM);
		imgu_v4l2_subdev_cleanup(imgu, i);
	पूर्ण
पूर्ण

अटल पूर्णांक imgu_v4l2_रेजिस्टर_pipes(काष्ठा imgu_device *imgu)
अणु
	काष्ठा imgu_media_pipe *imgu_pipe;
	पूर्णांक i, r;

	क्रम (i = 0; i < IMGU_MAX_PIPE_NUM; i++) अणु
		imgu_pipe = &imgu->imgu_pipe[i];
		r = imgu_v4l2_subdev_रेजिस्टर(imgu, &imgu_pipe->imgu_sd, i);
		अगर (r) अणु
			dev_err(&imgu->pci_dev->dev,
				"failed to register subdev%u ret (%d)\n", i, r);
			जाओ pipes_cleanup;
		पूर्ण
		r = imgu_v4l2_nodes_setup_pipe(imgu, i);
		अगर (r) अणु
			imgu_v4l2_subdev_cleanup(imgu, i);
			जाओ pipes_cleanup;
		पूर्ण
	पूर्ण

	वापस 0;

pipes_cleanup:
	imgu_v4l2_cleanup_pipes(imgu, i);
	वापस r;
पूर्ण

पूर्णांक imgu_v4l2_रेजिस्टर(काष्ठा imgu_device *imgu)
अणु
	पूर्णांक r;

	/* Initialize miscellaneous variables */
	imgu->streaming = false;

	/* Set up media device */
	media_device_pci_init(&imgu->media_dev, imgu->pci_dev, IMGU_NAME);

	/* Set up v4l2 device */
	imgu->v4l2_dev.mdev = &imgu->media_dev;
	imgu->v4l2_dev.ctrl_handler = शून्य;
	r = v4l2_device_रेजिस्टर(&imgu->pci_dev->dev, &imgu->v4l2_dev);
	अगर (r) अणु
		dev_err(&imgu->pci_dev->dev,
			"failed to register V4L2 device (%d)\n", r);
		जाओ fail_v4l2_dev;
	पूर्ण

	r = imgu_v4l2_रेजिस्टर_pipes(imgu);
	अगर (r) अणु
		dev_err(&imgu->pci_dev->dev,
			"failed to register pipes (%d)\n", r);
		जाओ fail_v4l2_pipes;
	पूर्ण

	r = v4l2_device_रेजिस्टर_subdev_nodes(&imgu->v4l2_dev);
	अगर (r) अणु
		dev_err(&imgu->pci_dev->dev,
			"failed to register subdevs (%d)\n", r);
		जाओ fail_subdevs;
	पूर्ण

	r = media_device_रेजिस्टर(&imgu->media_dev);
	अगर (r) अणु
		dev_err(&imgu->pci_dev->dev,
			"failed to register media device (%d)\n", r);
		जाओ fail_subdevs;
	पूर्ण

	वापस 0;

fail_subdevs:
	imgu_v4l2_cleanup_pipes(imgu, IMGU_MAX_PIPE_NUM);
fail_v4l2_pipes:
	v4l2_device_unरेजिस्टर(&imgu->v4l2_dev);
fail_v4l2_dev:
	media_device_cleanup(&imgu->media_dev);

	वापस r;
पूर्ण

पूर्णांक imgu_v4l2_unरेजिस्टर(काष्ठा imgu_device *imgu)
अणु
	media_device_unरेजिस्टर(&imgu->media_dev);
	imgu_v4l2_cleanup_pipes(imgu, IMGU_MAX_PIPE_NUM);
	v4l2_device_unरेजिस्टर(&imgu->v4l2_dev);
	media_device_cleanup(&imgu->media_dev);

	वापस 0;
पूर्ण

व्योम imgu_v4l2_buffer_करोne(काष्ठा vb2_buffer *vb,
			   क्रमागत vb2_buffer_state state)
अणु
	काष्ठा imgu_vb2_buffer *b =
		container_of(vb, काष्ठा imgu_vb2_buffer, vbb.vb2_buf);

	list_del(&b->list);
	vb2_buffer_करोne(&b->vbb.vb2_buf, state);
पूर्ण
