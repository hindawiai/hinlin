<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 NextThing Co
 * Copyright (C) 2016-2019 Bootlin
 *
 * Author: Maxime Ripard <maxime.ripard@bootlin.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/videobuf2-v4l2.h>

#समावेश "sun4i_csi.h"

काष्ठा sun4i_csi_buffer अणु
	काष्ठा vb2_v4l2_buffer	vb;
	काष्ठा list_head	list;
पूर्ण;

अटल अंतरभूत काष्ठा sun4i_csi_buffer *
vb2_v4l2_to_csi_buffer(स्थिर काष्ठा vb2_v4l2_buffer *p)
अणु
	वापस container_of(p, काष्ठा sun4i_csi_buffer, vb);
पूर्ण

अटल अंतरभूत काष्ठा sun4i_csi_buffer *
vb2_to_csi_buffer(स्थिर काष्ठा vb2_buffer *p)
अणु
	वापस vb2_v4l2_to_csi_buffer(to_vb2_v4l2_buffer(p));
पूर्ण

अटल व्योम sun4i_csi_capture_start(काष्ठा sun4i_csi *csi)
अणु
	ग_लिखोl(CSI_CPT_CTRL_VIDEO_START, csi->regs + CSI_CPT_CTRL_REG);
पूर्ण

अटल व्योम sun4i_csi_capture_stop(काष्ठा sun4i_csi *csi)
अणु
	ग_लिखोl(0, csi->regs + CSI_CPT_CTRL_REG);
पूर्ण

अटल पूर्णांक sun4i_csi_queue_setup(काष्ठा vb2_queue *vq,
				 अचिन्हित पूर्णांक *nbuffers,
				 अचिन्हित पूर्णांक *nplanes,
				 अचिन्हित पूर्णांक sizes[],
				 काष्ठा device *alloc_devs[])
अणु
	काष्ठा sun4i_csi *csi = vb2_get_drv_priv(vq);
	अचिन्हित पूर्णांक num_planes = csi->fmt.num_planes;
	अचिन्हित पूर्णांक i;

	अगर (*nplanes) अणु
		अगर (*nplanes != num_planes)
			वापस -EINVAL;

		क्रम (i = 0; i < num_planes; i++)
			अगर (sizes[i] < csi->fmt.plane_fmt[i].sizeimage)
				वापस -EINVAL;
		वापस 0;
	पूर्ण

	*nplanes = num_planes;
	क्रम (i = 0; i < num_planes; i++)
		sizes[i] = csi->fmt.plane_fmt[i].sizeimage;

	वापस 0;
पूर्ण;

अटल पूर्णांक sun4i_csi_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा sun4i_csi *csi = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < csi->fmt.num_planes; i++) अणु
		अचिन्हित दीर्घ size = csi->fmt.plane_fmt[i].sizeimage;

		अगर (vb2_plane_size(vb, i) < size) अणु
			dev_err(csi->dev, "buffer too small (%lu < %lu)\n",
				vb2_plane_size(vb, i), size);
			वापस -EINVAL;
		पूर्ण

		vb2_set_plane_payload(vb, i, size);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_csi_setup_scratch_buffer(काष्ठा sun4i_csi *csi,
					  अचिन्हित पूर्णांक slot)
अणु
	dma_addr_t addr = csi->scratch.paddr;
	अचिन्हित पूर्णांक plane;

	dev_dbg(csi->dev,
		"No more available buffer, using the scratch buffer\n");

	क्रम (plane = 0; plane < csi->fmt.num_planes; plane++) अणु
		ग_लिखोl(addr, csi->regs + CSI_BUF_ADDR_REG(plane, slot));
		addr += csi->fmt.plane_fmt[plane].sizeimage;
	पूर्ण

	csi->current_buf[slot] = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_csi_buffer_fill_slot(काष्ठा sun4i_csi *csi, अचिन्हित पूर्णांक slot)
अणु
	काष्ठा sun4i_csi_buffer *c_buf;
	काष्ठा vb2_v4l2_buffer *v_buf;
	अचिन्हित पूर्णांक plane;

	/*
	 * We should never end up in a situation where we overग_लिखो an
	 * alपढ़ोy filled slot.
	 */
	अगर (WARN_ON(csi->current_buf[slot]))
		वापस -EINVAL;

	अगर (list_empty(&csi->buf_list))
		वापस sun4i_csi_setup_scratch_buffer(csi, slot);

	c_buf = list_first_entry(&csi->buf_list, काष्ठा sun4i_csi_buffer, list);
	list_del_init(&c_buf->list);

	v_buf = &c_buf->vb;
	csi->current_buf[slot] = v_buf;

	क्रम (plane = 0; plane < csi->fmt.num_planes; plane++) अणु
		dma_addr_t buf_addr;

		buf_addr = vb2_dma_contig_plane_dma_addr(&v_buf->vb2_buf,
							 plane);
		ग_लिखोl(buf_addr, csi->regs + CSI_BUF_ADDR_REG(plane, slot));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_csi_buffer_fill_all(काष्ठा sun4i_csi *csi)
अणु
	अचिन्हित पूर्णांक slot;
	पूर्णांक ret;

	क्रम (slot = 0; slot < CSI_MAX_BUFFER; slot++) अणु
		ret = sun4i_csi_buffer_fill_slot(csi, slot);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sun4i_csi_buffer_mark_करोne(काष्ठा sun4i_csi *csi,
				       अचिन्हित पूर्णांक slot,
				       अचिन्हित पूर्णांक sequence)
अणु
	काष्ठा vb2_v4l2_buffer *v_buf;

	अगर (!csi->current_buf[slot]) अणु
		dev_dbg(csi->dev, "Scratch buffer was used, ignoring..\n");
		वापस;
	पूर्ण

	v_buf = csi->current_buf[slot];
	v_buf->field = csi->fmt.field;
	v_buf->sequence = sequence;
	v_buf->vb2_buf.बारtamp = kसमय_get_ns();
	vb2_buffer_करोne(&v_buf->vb2_buf, VB2_BUF_STATE_DONE);

	csi->current_buf[slot] = शून्य;
पूर्ण

अटल पूर्णांक sun4i_csi_buffer_flip(काष्ठा sun4i_csi *csi, अचिन्हित पूर्णांक sequence)
अणु
	u32 reg = पढ़ोl(csi->regs + CSI_BUF_CTRL_REG);
	अचिन्हित पूर्णांक next;

	/* Our next buffer is not the current buffer */
	next = !(reg & CSI_BUF_CTRL_DBS);

	/* Report the previous buffer as करोne */
	sun4i_csi_buffer_mark_करोne(csi, next, sequence);

	/* Put a new buffer in there */
	वापस sun4i_csi_buffer_fill_slot(csi, next);
पूर्ण

अटल व्योम sun4i_csi_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा sun4i_csi *csi = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा sun4i_csi_buffer *buf = vb2_to_csi_buffer(vb);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&csi->qlock, flags);
	list_add_tail(&buf->list, &csi->buf_list);
	spin_unlock_irqrestore(&csi->qlock, flags);
पूर्ण

अटल व्योम वापस_all_buffers(काष्ठा sun4i_csi *csi,
			       क्रमागत vb2_buffer_state state)
अणु
	काष्ठा sun4i_csi_buffer *buf, *node;
	अचिन्हित पूर्णांक slot;

	list_क्रम_each_entry_safe(buf, node, &csi->buf_list, list) अणु
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
		list_del(&buf->list);
	पूर्ण

	क्रम (slot = 0; slot < CSI_MAX_BUFFER; slot++) अणु
		काष्ठा vb2_v4l2_buffer *v_buf = csi->current_buf[slot];

		अगर (!v_buf)
			जारी;

		vb2_buffer_करोne(&v_buf->vb2_buf, state);
		csi->current_buf[slot] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक sun4i_csi_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा sun4i_csi *csi = vb2_get_drv_priv(vq);
	काष्ठा v4l2_fwnode_bus_parallel *bus = &csi->bus;
	स्थिर काष्ठा sun4i_csi_क्रमmat *csi_fmt;
	अचिन्हित दीर्घ href_pol, pclk_pol, vref_pol;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	csi_fmt = sun4i_csi_find_क्रमmat(&csi->fmt.pixelक्रमmat, शून्य);
	अगर (!csi_fmt)
		वापस -EINVAL;

	dev_dbg(csi->dev, "Starting capture\n");

	csi->sequence = 0;

	/*
	 * We need a scratch buffer in हाल where we'll not have any
	 * more buffer queued so that we करोn't error out. One of those
	 * हालs is when you end up at the last frame to capture, you
	 * करोn't havea any buffer queued any more, and yet it doesn't
	 * really matter since you'll never reach the next buffer.
	 *
	 * Since we support the multi-planar API, we need to have a
	 * buffer क्रम each plane. Allocating a single one large enough
	 * to hold all the buffers is simpler, so let's go क्रम that.
	 */
	csi->scratch.size = 0;
	क्रम (i = 0; i < csi->fmt.num_planes; i++)
		csi->scratch.size += csi->fmt.plane_fmt[i].sizeimage;

	csi->scratch.vaddr = dma_alloc_coherent(csi->dev,
						csi->scratch.size,
						&csi->scratch.paddr,
						GFP_KERNEL);
	अगर (!csi->scratch.vaddr) अणु
		dev_err(csi->dev, "Failed to allocate scratch buffer\n");
		ret = -ENOMEM;
		जाओ err_clear_dma_queue;
	पूर्ण

	ret = media_pipeline_start(&csi->vdev.entity, &csi->vdev.pipe);
	अगर (ret < 0)
		जाओ err_मुक्त_scratch_buffer;

	spin_lock_irqsave(&csi->qlock, flags);

	/* Setup timings */
	ग_लिखोl(CSI_WIN_CTRL_W_ACTIVE(csi->fmt.width * 2),
	       csi->regs + CSI_WIN_CTRL_W_REG);
	ग_लिखोl(CSI_WIN_CTRL_H_ACTIVE(csi->fmt.height),
	       csi->regs + CSI_WIN_CTRL_H_REG);

	/*
	 * This hardware uses [HV]REF instead of [HV]SYNC. Based on the
	 * provided timing diagrams in the manual, positive polarity
	 * equals active high [HV]REF.
	 *
	 * When the back porch is 0, [HV]REF is more or less equivalent
	 * to [HV]SYNC inverted.
	 */
	href_pol = !!(bus->flags & V4L2_MBUS_HSYNC_ACTIVE_LOW);
	vref_pol = !!(bus->flags & V4L2_MBUS_VSYNC_ACTIVE_LOW);
	pclk_pol = !!(bus->flags & V4L2_MBUS_PCLK_SAMPLE_RISING);
	ग_लिखोl(CSI_CFG_INPUT_FMT(csi_fmt->input) |
	       CSI_CFG_OUTPUT_FMT(csi_fmt->output) |
	       CSI_CFG_VREF_POL(vref_pol) |
	       CSI_CFG_HREF_POL(href_pol) |
	       CSI_CFG_PCLK_POL(pclk_pol),
	       csi->regs + CSI_CFG_REG);

	/* Setup buffer length */
	ग_लिखोl(csi->fmt.plane_fmt[0].bytesperline,
	       csi->regs + CSI_BUF_LEN_REG);

	/* Prepare our buffers in hardware */
	ret = sun4i_csi_buffer_fill_all(csi);
	अगर (ret) अणु
		spin_unlock_irqrestore(&csi->qlock, flags);
		जाओ err_disable_pipeline;
	पूर्ण

	/* Enable द्विगुन buffering */
	ग_लिखोl(CSI_BUF_CTRL_DBE, csi->regs + CSI_BUF_CTRL_REG);

	/* Clear the pending पूर्णांकerrupts */
	ग_लिखोl(CSI_INT_FRM_DONE, csi->regs + 0x34);

	/* Enable frame करोne पूर्णांकerrupt */
	ग_लिखोl(CSI_INT_FRM_DONE, csi->regs + CSI_INT_EN_REG);

	sun4i_csi_capture_start(csi);

	spin_unlock_irqrestore(&csi->qlock, flags);

	ret = v4l2_subdev_call(csi->src_subdev, video, s_stream, 1);
	अगर (ret < 0 && ret != -ENOIOCTLCMD)
		जाओ err_disable_device;

	वापस 0;

err_disable_device:
	sun4i_csi_capture_stop(csi);

err_disable_pipeline:
	media_pipeline_stop(&csi->vdev.entity);

err_मुक्त_scratch_buffer:
	dma_मुक्त_coherent(csi->dev, csi->scratch.size, csi->scratch.vaddr,
			  csi->scratch.paddr);

err_clear_dma_queue:
	spin_lock_irqsave(&csi->qlock, flags);
	वापस_all_buffers(csi, VB2_BUF_STATE_QUEUED);
	spin_unlock_irqrestore(&csi->qlock, flags);

	वापस ret;
पूर्ण

अटल व्योम sun4i_csi_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा sun4i_csi *csi = vb2_get_drv_priv(vq);
	अचिन्हित दीर्घ flags;

	dev_dbg(csi->dev, "Stopping capture\n");

	v4l2_subdev_call(csi->src_subdev, video, s_stream, 0);
	sun4i_csi_capture_stop(csi);

	/* Release all active buffers */
	spin_lock_irqsave(&csi->qlock, flags);
	वापस_all_buffers(csi, VB2_BUF_STATE_ERROR);
	spin_unlock_irqrestore(&csi->qlock, flags);

	media_pipeline_stop(&csi->vdev.entity);

	dma_मुक्त_coherent(csi->dev, csi->scratch.size, csi->scratch.vaddr,
			  csi->scratch.paddr);
पूर्ण

अटल स्थिर काष्ठा vb2_ops sun4i_csi_qops = अणु
	.queue_setup		= sun4i_csi_queue_setup,
	.buf_prepare		= sun4i_csi_buffer_prepare,
	.buf_queue		= sun4i_csi_buffer_queue,
	.start_streaming	= sun4i_csi_start_streaming,
	.stop_streaming		= sun4i_csi_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल irqवापस_t sun4i_csi_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sun4i_csi *csi = data;
	u32 reg;

	reg = पढ़ोl(csi->regs + CSI_INT_STA_REG);

	/* Acknowledge the पूर्णांकerrupts */
	ग_लिखोl(reg, csi->regs + CSI_INT_STA_REG);

	अगर (!(reg & CSI_INT_FRM_DONE))
		वापस IRQ_HANDLED;

	spin_lock(&csi->qlock);
	अगर (sun4i_csi_buffer_flip(csi, csi->sequence++)) अणु
		dev_warn(csi->dev, "%s: Flip failed\n", __func__);
		sun4i_csi_capture_stop(csi);
	पूर्ण
	spin_unlock(&csi->qlock);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक sun4i_csi_dma_रेजिस्टर(काष्ठा sun4i_csi *csi, पूर्णांक irq)
अणु
	काष्ठा vb2_queue *q = &csi->queue;
	पूर्णांक ret;
	पूर्णांक i;

	spin_lock_init(&csi->qlock);
	mutex_init(&csi->lock);

	INIT_LIST_HEAD(&csi->buf_list);
	क्रम (i = 0; i < CSI_MAX_BUFFER; i++)
		csi->current_buf[i] = शून्य;

	q->min_buffers_needed = 3;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
	q->lock = &csi->lock;
	q->drv_priv = csi;
	q->buf_काष्ठा_size = माप(काष्ठा sun4i_csi_buffer);
	q->ops = &sun4i_csi_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->dev = csi->dev;

	ret = vb2_queue_init(q);
	अगर (ret < 0) अणु
		dev_err(csi->dev, "failed to initialize VB2 queue\n");
		जाओ err_मुक्त_mutex;
	पूर्ण

	ret = v4l2_device_रेजिस्टर(csi->dev, &csi->v4l);
	अगर (ret) अणु
		dev_err(csi->dev, "Couldn't register the v4l2 device\n");
		जाओ err_मुक्त_mutex;
	पूर्ण

	ret = devm_request_irq(csi->dev, irq, sun4i_csi_irq, 0,
			       dev_name(csi->dev), csi);
	अगर (ret) अणु
		dev_err(csi->dev, "Couldn't register our interrupt\n");
		जाओ err_unरेजिस्टर_device;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_device:
	v4l2_device_unरेजिस्टर(&csi->v4l);

err_मुक्त_mutex:
	mutex_destroy(&csi->lock);
	वापस ret;
पूर्ण

व्योम sun4i_csi_dma_unरेजिस्टर(काष्ठा sun4i_csi *csi)
अणु
	v4l2_device_unरेजिस्टर(&csi->v4l);
	mutex_destroy(&csi->lock);
पूर्ण
