<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 - 2018 Intel Corporation
 * Copyright 2017 Google LLC
 *
 * Based on Intel IPU4 driver.
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "ipu3.h"
#समावेश "ipu3-dmamap.h"
#समावेश "ipu3-mmu.h"

#घोषणा IMGU_PCI_ID			0x1919
#घोषणा IMGU_PCI_BAR			0
#घोषणा IMGU_DMA_MASK			DMA_BIT_MASK(39)
#घोषणा IMGU_MAX_QUEUE_DEPTH		(2 + 2)

/*
 * pre-allocated buffer size क्रम IMGU dummy buffers. Those
 * values should be tuned to big enough to aव्योम buffer
 * re-allocation when streaming to lower streaming latency.
 */
#घोषणा CSS_QUEUE_IN_BUF_SIZE		0
#घोषणा CSS_QUEUE_PARAMS_BUF_SIZE	0
#घोषणा CSS_QUEUE_OUT_BUF_SIZE		(4160 * 3120 * 12 / 8)
#घोषणा CSS_QUEUE_VF_BUF_SIZE		(1920 * 1080 * 12 / 8)
#घोषणा CSS_QUEUE_STAT_3A_BUF_SIZE	माप(काष्ठा ipu3_uapi_stats_3a)

अटल स्थिर माप_प्रकार css_queue_buf_size_map[IPU3_CSS_QUEUES] = अणु
	[IPU3_CSS_QUEUE_IN] = CSS_QUEUE_IN_BUF_SIZE,
	[IPU3_CSS_QUEUE_PARAMS] = CSS_QUEUE_PARAMS_BUF_SIZE,
	[IPU3_CSS_QUEUE_OUT] = CSS_QUEUE_OUT_BUF_SIZE,
	[IPU3_CSS_QUEUE_VF] = CSS_QUEUE_VF_BUF_SIZE,
	[IPU3_CSS_QUEUE_STAT_3A] = CSS_QUEUE_STAT_3A_BUF_SIZE,
पूर्ण;

अटल स्थिर काष्ठा imgu_node_mapping imgu_node_map[IMGU_NODE_NUM] = अणु
	[IMGU_NODE_IN] = अणुIPU3_CSS_QUEUE_IN, "input"पूर्ण,
	[IMGU_NODE_PARAMS] = अणुIPU3_CSS_QUEUE_PARAMS, "parameters"पूर्ण,
	[IMGU_NODE_OUT] = अणुIPU3_CSS_QUEUE_OUT, "output"पूर्ण,
	[IMGU_NODE_VF] = अणुIPU3_CSS_QUEUE_VF, "viewfinder"पूर्ण,
	[IMGU_NODE_STAT_3A] = अणुIPU3_CSS_QUEUE_STAT_3A, "3a stat"पूर्ण,
पूर्ण;

अचिन्हित पूर्णांक imgu_node_to_queue(अचिन्हित पूर्णांक node)
अणु
	वापस imgu_node_map[node].css_queue;
पूर्ण

अचिन्हित पूर्णांक imgu_map_node(काष्ठा imgu_device *imgu, अचिन्हित पूर्णांक css_queue)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IMGU_NODE_NUM; i++)
		अगर (imgu_node_map[i].css_queue == css_queue)
			अवरोध;

	वापस i;
पूर्ण

/**************** Dummy buffers ****************/

अटल व्योम imgu_dummybufs_cleanup(काष्ठा imgu_device *imgu, अचिन्हित पूर्णांक pipe)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	क्रम (i = 0; i < IPU3_CSS_QUEUES; i++)
		imgu_dmamap_मुक्त(imgu,
				 &imgu_pipe->queues[i].dmap);
पूर्ण

अटल पूर्णांक imgu_dummybufs_pपुनः_स्मृतिate(काष्ठा imgu_device *imgu,
				      अचिन्हित पूर्णांक pipe)
अणु
	अचिन्हित पूर्णांक i;
	माप_प्रकार size;
	काष्ठा imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	क्रम (i = 0; i < IPU3_CSS_QUEUES; i++) अणु
		size = css_queue_buf_size_map[i];
		/*
		 * Do not enable dummy buffers क्रम master queue,
		 * always require that real buffers from user are
		 * available.
		 */
		अगर (i == IMGU_QUEUE_MASTER || size == 0)
			जारी;

		अगर (!imgu_dmamap_alloc(imgu,
				       &imgu_pipe->queues[i].dmap, size)) अणु
			imgu_dummybufs_cleanup(imgu, pipe);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imgu_dummybufs_init(काष्ठा imgu_device *imgu, अचिन्हित पूर्णांक pipe)
अणु
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *mpix;
	स्थिर काष्ठा v4l2_meta_क्रमmat	*meta;
	अचिन्हित पूर्णांक i, k, node;
	माप_प्रकार size;
	काष्ठा imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	/* Allocate a dummy buffer क्रम each queue where buffer is optional */
	क्रम (i = 0; i < IPU3_CSS_QUEUES; i++) अणु
		node = imgu_map_node(imgu, i);
		अगर (!imgu_pipe->queue_enabled[node] || i == IMGU_QUEUE_MASTER)
			जारी;

		अगर (!imgu_pipe->nodes[IMGU_NODE_VF].enabled &&
		    i == IPU3_CSS_QUEUE_VF)
			/*
			 * Do not enable dummy buffers क्रम VF अगर it is not
			 * requested by the user.
			 */
			जारी;

		meta = &imgu_pipe->nodes[node].vdev_fmt.fmt.meta;
		mpix = &imgu_pipe->nodes[node].vdev_fmt.fmt.pix_mp;

		अगर (node == IMGU_NODE_STAT_3A || node == IMGU_NODE_PARAMS)
			size = meta->buffersize;
		अन्यथा
			size = mpix->plane_fmt[0].sizeimage;

		अगर (imgu_css_dma_buffer_resize(imgu,
					       &imgu_pipe->queues[i].dmap,
					       size)) अणु
			imgu_dummybufs_cleanup(imgu, pipe);
			वापस -ENOMEM;
		पूर्ण

		क्रम (k = 0; k < IMGU_MAX_QUEUE_DEPTH; k++)
			imgu_css_buf_init(&imgu_pipe->queues[i].dummybufs[k], i,
					  imgu_pipe->queues[i].dmap.daddr);
	पूर्ण

	वापस 0;
पूर्ण

/* May be called from atomic context */
अटल काष्ठा imgu_css_buffer *imgu_dummybufs_get(काष्ठा imgu_device *imgu,
						   पूर्णांक queue, अचिन्हित पूर्णांक pipe)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	/* dummybufs are not allocated क्रम master q */
	अगर (queue == IPU3_CSS_QUEUE_IN)
		वापस शून्य;

	अगर (WARN_ON(!imgu_pipe->queues[queue].dmap.vaddr))
		/* Buffer should not be allocated here */
		वापस शून्य;

	क्रम (i = 0; i < IMGU_MAX_QUEUE_DEPTH; i++)
		अगर (imgu_css_buf_state(&imgu_pipe->queues[queue].dummybufs[i]) !=
			IPU3_CSS_BUFFER_QUEUED)
			अवरोध;

	अगर (i == IMGU_MAX_QUEUE_DEPTH)
		वापस शून्य;

	imgu_css_buf_init(&imgu_pipe->queues[queue].dummybufs[i], queue,
			  imgu_pipe->queues[queue].dmap.daddr);

	वापस &imgu_pipe->queues[queue].dummybufs[i];
पूर्ण

/* Check अगर given buffer is a dummy buffer */
अटल bool imgu_dummybufs_check(काष्ठा imgu_device *imgu,
				 काष्ठा imgu_css_buffer *buf,
				 अचिन्हित पूर्णांक pipe)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	क्रम (i = 0; i < IMGU_MAX_QUEUE_DEPTH; i++)
		अगर (buf == &imgu_pipe->queues[buf->queue].dummybufs[i])
			अवरोध;

	वापस i < IMGU_MAX_QUEUE_DEPTH;
पूर्ण

अटल व्योम imgu_buffer_करोne(काष्ठा imgu_device *imgu, काष्ठा vb2_buffer *vb,
			     क्रमागत vb2_buffer_state state)
अणु
	mutex_lock(&imgu->lock);
	imgu_v4l2_buffer_करोne(vb, state);
	mutex_unlock(&imgu->lock);
पूर्ण

अटल काष्ठा imgu_css_buffer *imgu_queue_getbuf(काष्ठा imgu_device *imgu,
						 अचिन्हित पूर्णांक node,
						 अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा imgu_buffer *buf;
	काष्ठा imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	अगर (WARN_ON(node >= IMGU_NODE_NUM))
		वापस शून्य;

	/* Find first मुक्त buffer from the node */
	list_क्रम_each_entry(buf, &imgu_pipe->nodes[node].buffers, vid_buf.list) अणु
		अगर (imgu_css_buf_state(&buf->css_buf) == IPU3_CSS_BUFFER_NEW)
			वापस &buf->css_buf;
	पूर्ण

	/* There were no मुक्त buffers, try to वापस a dummy buffer */
	वापस imgu_dummybufs_get(imgu, imgu_node_map[node].css_queue, pipe);
पूर्ण

/*
 * Queue as many buffers to CSS as possible. If all buffers करोn't fit पूर्णांकo
 * CSS buffer queues, they reमुख्य unqueued and will be queued later.
 */
पूर्णांक imgu_queue_buffers(काष्ठा imgu_device *imgu, bool initial, अचिन्हित पूर्णांक pipe)
अणु
	अचिन्हित पूर्णांक node;
	पूर्णांक r = 0;
	काष्ठा imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	अगर (!imgu_css_is_streaming(&imgu->css))
		वापस 0;

	dev_dbg(&imgu->pci_dev->dev, "Queue buffers to pipe %d", pipe);
	mutex_lock(&imgu->lock);

	अगर (!imgu_css_pipe_queue_empty(&imgu->css, pipe)) अणु
		mutex_unlock(&imgu->lock);
		वापस 0;
	पूर्ण

	/* Buffer set is queued to FW only when input buffer is पढ़ोy */
	क्रम (node = IMGU_NODE_NUM - 1;
	     imgu_queue_getbuf(imgu, IMGU_NODE_IN, pipe);
	     node = node ? node - 1 : IMGU_NODE_NUM - 1) अणु
		अगर (node == IMGU_NODE_VF &&
		    !imgu_pipe->nodes[IMGU_NODE_VF].enabled) अणु
			dev_warn(&imgu->pci_dev->dev,
				 "Vf not enabled, ignore queue");
			जारी;
		पूर्ण अन्यथा अगर (node == IMGU_NODE_PARAMS &&
			   imgu_pipe->nodes[node].enabled) अणु
			काष्ठा vb2_buffer *vb;
			काष्ठा imgu_vb2_buffer *ivb;

			/* No parameters क्रम this frame */
			अगर (list_empty(&imgu_pipe->nodes[node].buffers))
				जारी;

			ivb = list_first_entry(&imgu_pipe->nodes[node].buffers,
					       काष्ठा imgu_vb2_buffer, list);
			list_del(&ivb->list);
			vb = &ivb->vbb.vb2_buf;
			r = imgu_css_set_parameters(&imgu->css, pipe,
						    vb2_plane_vaddr(vb, 0));
			अगर (r) अणु
				vb2_buffer_करोne(vb, VB2_BUF_STATE_ERROR);
				dev_warn(&imgu->pci_dev->dev,
					 "set parameters failed.");
				जारी;
			पूर्ण

			vb2_buffer_करोne(vb, VB2_BUF_STATE_DONE);
			dev_dbg(&imgu->pci_dev->dev,
				"queue user parameters %d to css.", vb->index);
		पूर्ण अन्यथा अगर (imgu_pipe->queue_enabled[node]) अणु
			काष्ठा imgu_css_buffer *buf =
				imgu_queue_getbuf(imgu, node, pipe);
			काष्ठा imgu_buffer *ibuf = शून्य;
			bool dummy;

			अगर (!buf)
				अवरोध;

			r = imgu_css_buf_queue(&imgu->css, pipe, buf);
			अगर (r)
				अवरोध;
			dummy = imgu_dummybufs_check(imgu, buf, pipe);
			अगर (!dummy)
				ibuf = container_of(buf, काष्ठा imgu_buffer,
						    css_buf);
			dev_dbg(&imgu->pci_dev->dev,
				"queue %s %s buffer %u to css da: 0x%08x\n",
				dummy ? "dummy" : "user",
				imgu_node_map[node].name,
				dummy ? 0 : ibuf->vid_buf.vbb.vb2_buf.index,
				(u32)buf->daddr);
		पूर्ण
	पूर्ण
	mutex_unlock(&imgu->lock);

	अगर (r && r != -EBUSY)
		जाओ failed;

	वापस 0;

failed:
	/*
	 * On error, mark all buffers as failed which are not
	 * yet queued to CSS
	 */
	dev_err(&imgu->pci_dev->dev,
		"failed to queue buffer to CSS on queue %i (%d)\n",
		node, r);

	अगर (initial)
		/* If we were called from streamon(), no need to finish bufs */
		वापस r;

	क्रम (node = 0; node < IMGU_NODE_NUM; node++) अणु
		काष्ठा imgu_buffer *buf, *buf0;

		अगर (!imgu_pipe->queue_enabled[node])
			जारी;	/* Skip disabled queues */

		mutex_lock(&imgu->lock);
		list_क्रम_each_entry_safe(buf, buf0,
					 &imgu_pipe->nodes[node].buffers,
					 vid_buf.list) अणु
			अगर (imgu_css_buf_state(&buf->css_buf) ==
			    IPU3_CSS_BUFFER_QUEUED)
				जारी;	/* Was alपढ़ोy queued, skip */

			imgu_v4l2_buffer_करोne(&buf->vid_buf.vbb.vb2_buf,
					      VB2_BUF_STATE_ERROR);
		पूर्ण
		mutex_unlock(&imgu->lock);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक imgu_घातerup(काष्ठा imgu_device *imgu)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक pipe;
	अचिन्हित पूर्णांक freq = 200;
	काष्ठा v4l2_mbus_framefmt *fmt;

	/* input larger than 2048*1152, ask imgu to work on high freq */
	क्रम_each_set_bit(pipe, imgu->css.enabled_pipes, IMGU_MAX_PIPE_NUM) अणु
		fmt = &imgu->imgu_pipe[pipe].nodes[IMGU_NODE_IN].pad_fmt;
		dev_dbg(&imgu->pci_dev->dev, "pipe %u input format = %ux%u",
			pipe, fmt->width, fmt->height);
		अगर ((fmt->width * fmt->height) >= (2048 * 1152))
			freq = 450;
	पूर्ण

	r = imgu_css_set_घातerup(&imgu->pci_dev->dev, imgu->base, freq);
	अगर (r)
		वापस r;

	imgu_mmu_resume(imgu->mmu);
	वापस 0;
पूर्ण

अटल व्योम imgu_घातerकरोwn(काष्ठा imgu_device *imgu)
अणु
	imgu_mmu_suspend(imgu->mmu);
	imgu_css_set_घातerकरोwn(&imgu->pci_dev->dev, imgu->base);
पूर्ण

पूर्णांक imgu_s_stream(काष्ठा imgu_device *imgu, पूर्णांक enable)
अणु
	काष्ठा device *dev = &imgu->pci_dev->dev;
	पूर्णांक r, pipe;

	अगर (!enable) अणु
		/* Stop streaming */
		dev_dbg(dev, "stream off\n");
		/* Block new buffers to be queued to CSS. */
		atomic_set(&imgu->qbuf_barrier, 1);
		imgu_css_stop_streaming(&imgu->css);
		synchronize_irq(imgu->pci_dev->irq);
		atomic_set(&imgu->qbuf_barrier, 0);
		imgu_घातerकरोwn(imgu);
		pm_runसमय_put(&imgu->pci_dev->dev);

		वापस 0;
	पूर्ण

	/* Set Power */
	r = pm_runसमय_get_sync(dev);
	अगर (r < 0) अणु
		dev_err(dev, "failed to set imgu power\n");
		pm_runसमय_put(dev);
		वापस r;
	पूर्ण

	r = imgu_घातerup(imgu);
	अगर (r) अणु
		dev_err(dev, "failed to power up imgu\n");
		pm_runसमय_put(dev);
		वापस r;
	पूर्ण

	/* Start CSS streaming */
	r = imgu_css_start_streaming(&imgu->css);
	अगर (r) अणु
		dev_err(dev, "failed to start css streaming (%d)", r);
		जाओ fail_start_streaming;
	पूर्ण

	क्रम_each_set_bit(pipe, imgu->css.enabled_pipes, IMGU_MAX_PIPE_NUM) अणु
		/* Initialize dummy buffers */
		r = imgu_dummybufs_init(imgu, pipe);
		अगर (r) अणु
			dev_err(dev, "failed to initialize dummy buffers (%d)", r);
			जाओ fail_dummybufs;
		पूर्ण

		/* Queue as many buffers from queue as possible */
		r = imgu_queue_buffers(imgu, true, pipe);
		अगर (r) अणु
			dev_err(dev, "failed to queue initial buffers (%d)", r);
			जाओ fail_queueing;
		पूर्ण
	पूर्ण

	वापस 0;
fail_queueing:
	क्रम_each_set_bit(pipe, imgu->css.enabled_pipes, IMGU_MAX_PIPE_NUM)
		imgu_dummybufs_cleanup(imgu, pipe);
fail_dummybufs:
	imgu_css_stop_streaming(&imgu->css);
fail_start_streaming:
	pm_runसमय_put(dev);

	वापस r;
पूर्ण

अटल पूर्णांक imgu_video_nodes_init(काष्ठा imgu_device *imgu)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *fmts[IPU3_CSS_QUEUES] = अणु शून्य पूर्ण;
	काष्ठा v4l2_rect *rects[IPU3_CSS_RECTS] = अणु शून्य पूर्ण;
	काष्ठा imgu_media_pipe *imgu_pipe;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक r;

	imgu->buf_काष्ठा_size = माप(काष्ठा imgu_buffer);

	क्रम (j = 0; j < IMGU_MAX_PIPE_NUM; j++) अणु
		imgu_pipe = &imgu->imgu_pipe[j];

		क्रम (i = 0; i < IMGU_NODE_NUM; i++) अणु
			imgu_pipe->nodes[i].name = imgu_node_map[i].name;
			imgu_pipe->nodes[i].output = i < IMGU_QUEUE_FIRST_INPUT;
			imgu_pipe->nodes[i].enabled = false;

			अगर (i != IMGU_NODE_PARAMS && i != IMGU_NODE_STAT_3A)
				fmts[imgu_node_map[i].css_queue] =
					&imgu_pipe->nodes[i].vdev_fmt.fmt.pix_mp;
			atomic_set(&imgu_pipe->nodes[i].sequence, 0);
		पूर्ण
	पूर्ण

	r = imgu_v4l2_रेजिस्टर(imgu);
	अगर (r)
		वापस r;

	/* Set initial क्रमmats and initialize क्रमmats of video nodes */
	क्रम (j = 0; j < IMGU_MAX_PIPE_NUM; j++) अणु
		imgu_pipe = &imgu->imgu_pipe[j];

		rects[IPU3_CSS_RECT_EFFECTIVE] = &imgu_pipe->imgu_sd.rect.eff;
		rects[IPU3_CSS_RECT_BDS] = &imgu_pipe->imgu_sd.rect.bds;
		imgu_css_fmt_set(&imgu->css, fmts, rects, j);

		/* Pre-allocate dummy buffers */
		r = imgu_dummybufs_pपुनः_स्मृतिate(imgu, j);
		अगर (r) अणु
			dev_err(&imgu->pci_dev->dev,
				"failed to pre-allocate dummy buffers (%d)", r);
			जाओ out_cleanup;
		पूर्ण
	पूर्ण

	वापस 0;

out_cleanup:
	क्रम (j = 0; j < IMGU_MAX_PIPE_NUM; j++)
		imgu_dummybufs_cleanup(imgu, j);

	imgu_v4l2_unरेजिस्टर(imgu);

	वापस r;
पूर्ण

अटल व्योम imgu_video_nodes_निकास(काष्ठा imgu_device *imgu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IMGU_MAX_PIPE_NUM; i++)
		imgu_dummybufs_cleanup(imgu, i);

	imgu_v4l2_unरेजिस्टर(imgu);
पूर्ण

/**************** PCI पूर्णांकerface ****************/

अटल irqवापस_t imgu_isr_thपढ़ोed(पूर्णांक irq, व्योम *imgu_ptr)
अणु
	काष्ठा imgu_device *imgu = imgu_ptr;
	काष्ठा imgu_media_pipe *imgu_pipe;
	पूर्णांक p;

	/* Dequeue / queue buffers */
	करो अणु
		u64 ns = kसमय_get_ns();
		काष्ठा imgu_css_buffer *b;
		काष्ठा imgu_buffer *buf = शून्य;
		अचिन्हित पूर्णांक node, pipe;
		bool dummy;

		करो अणु
			mutex_lock(&imgu->lock);
			b = imgu_css_buf_dequeue(&imgu->css);
			mutex_unlock(&imgu->lock);
		पूर्ण जबतक (PTR_ERR(b) == -EAGAIN);

		अगर (IS_ERR(b)) अणु
			अगर (PTR_ERR(b) != -EBUSY)	/* All करोne */
				dev_err(&imgu->pci_dev->dev,
					"failed to dequeue buffers (%ld)\n",
					PTR_ERR(b));
			अवरोध;
		पूर्ण

		node = imgu_map_node(imgu, b->queue);
		pipe = b->pipe;
		dummy = imgu_dummybufs_check(imgu, b, pipe);
		अगर (!dummy)
			buf = container_of(b, काष्ठा imgu_buffer, css_buf);
		dev_dbg(&imgu->pci_dev->dev,
			"dequeue %s %s buffer %d daddr 0x%x from css\n",
			dummy ? "dummy" : "user",
			imgu_node_map[node].name,
			dummy ? 0 : buf->vid_buf.vbb.vb2_buf.index,
			(u32)b->daddr);

		अगर (dummy)
			/* It was a dummy buffer, skip it */
			जारी;

		/* Fill vb2 buffer entries and tell it's पढ़ोy */
		imgu_pipe = &imgu->imgu_pipe[pipe];
		अगर (!imgu_pipe->nodes[node].output) अणु
			buf->vid_buf.vbb.vb2_buf.बारtamp = ns;
			buf->vid_buf.vbb.field = V4L2_FIELD_NONE;
			buf->vid_buf.vbb.sequence =
				atomic_inc_वापस(
				&imgu_pipe->nodes[node].sequence);
			dev_dbg(&imgu->pci_dev->dev, "vb2 buffer sequence %d",
				buf->vid_buf.vbb.sequence);
		पूर्ण
		imgu_buffer_करोne(imgu, &buf->vid_buf.vbb.vb2_buf,
				 imgu_css_buf_state(&buf->css_buf) ==
						    IPU3_CSS_BUFFER_DONE ?
						    VB2_BUF_STATE_DONE :
						    VB2_BUF_STATE_ERROR);
		mutex_lock(&imgu->lock);
		अगर (imgu_css_queue_empty(&imgu->css))
			wake_up_all(&imgu->buf_drain_wq);
		mutex_unlock(&imgu->lock);
	पूर्ण जबतक (1);

	/*
	 * Try to queue more buffers क्रम CSS.
	 * qbuf_barrier is used to disable new buffers
	 * to be queued to CSS.
	 */
	अगर (!atomic_पढ़ो(&imgu->qbuf_barrier))
		क्रम_each_set_bit(p, imgu->css.enabled_pipes, IMGU_MAX_PIPE_NUM)
			imgu_queue_buffers(imgu, false, p);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t imgu_isr(पूर्णांक irq, व्योम *imgu_ptr)
अणु
	काष्ठा imgu_device *imgu = imgu_ptr;

	/* acknowledge पूर्णांकerruption */
	अगर (imgu_css_irq_ack(&imgu->css) < 0)
		वापस IRQ_NONE;

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल पूर्णांक imgu_pci_config_setup(काष्ठा pci_dev *dev)
अणु
	u16 pci_command;
	पूर्णांक r = pci_enable_msi(dev);

	अगर (r) अणु
		dev_err(&dev->dev, "failed to enable MSI (%d)\n", r);
		वापस r;
	पूर्ण

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &pci_command);
	pci_command |= PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER |
			PCI_COMMAND_INTX_DISABLE;
	pci_ग_लिखो_config_word(dev, PCI_COMMAND, pci_command);

	वापस 0;
पूर्ण

अटल पूर्णांक imgu_pci_probe(काष्ठा pci_dev *pci_dev,
			  स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा imgu_device *imgu;
	phys_addr_t phys;
	अचिन्हित दीर्घ phys_len;
	व्योम __iomem *स्थिर *iomap;
	पूर्णांक r;

	imgu = devm_kzalloc(&pci_dev->dev, माप(*imgu), GFP_KERNEL);
	अगर (!imgu)
		वापस -ENOMEM;

	imgu->pci_dev = pci_dev;

	r = pcim_enable_device(pci_dev);
	अगर (r) अणु
		dev_err(&pci_dev->dev, "failed to enable device (%d)\n", r);
		वापस r;
	पूर्ण

	dev_info(&pci_dev->dev, "device 0x%x (rev: 0x%x)\n",
		 pci_dev->device, pci_dev->revision);

	phys = pci_resource_start(pci_dev, IMGU_PCI_BAR);
	phys_len = pci_resource_len(pci_dev, IMGU_PCI_BAR);

	r = pcim_iomap_regions(pci_dev, 1 << IMGU_PCI_BAR, pci_name(pci_dev));
	अगर (r) अणु
		dev_err(&pci_dev->dev, "failed to remap I/O memory (%d)\n", r);
		वापस r;
	पूर्ण
	dev_info(&pci_dev->dev, "physical base address %pap, %lu bytes\n",
		 &phys, phys_len);

	iomap = pcim_iomap_table(pci_dev);
	अगर (!iomap) अणु
		dev_err(&pci_dev->dev, "failed to iomap table\n");
		वापस -ENODEV;
	पूर्ण

	imgu->base = iomap[IMGU_PCI_BAR];

	pci_set_drvdata(pci_dev, imgu);

	pci_set_master(pci_dev);

	r = dma_coerce_mask_and_coherent(&pci_dev->dev, IMGU_DMA_MASK);
	अगर (r) अणु
		dev_err(&pci_dev->dev, "failed to set DMA mask (%d)\n", r);
		वापस -ENODEV;
	पूर्ण

	r = imgu_pci_config_setup(pci_dev);
	अगर (r)
		वापस r;

	mutex_init(&imgu->lock);
	mutex_init(&imgu->streaming_lock);
	atomic_set(&imgu->qbuf_barrier, 0);
	init_रुकोqueue_head(&imgu->buf_drain_wq);

	r = imgu_css_set_घातerup(&pci_dev->dev, imgu->base, 200);
	अगर (r) अणु
		dev_err(&pci_dev->dev,
			"failed to power up CSS (%d)\n", r);
		जाओ out_mutex_destroy;
	पूर्ण

	imgu->mmu = imgu_mmu_init(&pci_dev->dev, imgu->base);
	अगर (IS_ERR(imgu->mmu)) अणु
		r = PTR_ERR(imgu->mmu);
		dev_err(&pci_dev->dev, "failed to initialize MMU (%d)\n", r);
		जाओ out_css_घातerकरोwn;
	पूर्ण

	r = imgu_dmamap_init(imgu);
	अगर (r) अणु
		dev_err(&pci_dev->dev,
			"failed to initialize DMA mapping (%d)\n", r);
		जाओ out_mmu_निकास;
	पूर्ण

	/* ISP programming */
	r = imgu_css_init(&pci_dev->dev, &imgu->css, imgu->base, phys_len);
	अगर (r) अणु
		dev_err(&pci_dev->dev, "failed to initialize CSS (%d)\n", r);
		जाओ out_dmamap_निकास;
	पूर्ण

	/* v4l2 sub-device registration */
	r = imgu_video_nodes_init(imgu);
	अगर (r) अणु
		dev_err(&pci_dev->dev, "failed to create V4L2 devices (%d)\n",
			r);
		जाओ out_css_cleanup;
	पूर्ण

	r = devm_request_thपढ़ोed_irq(&pci_dev->dev, pci_dev->irq,
				      imgu_isr, imgu_isr_thपढ़ोed,
				      IRQF_SHARED, IMGU_NAME, imgu);
	अगर (r) अणु
		dev_err(&pci_dev->dev, "failed to request IRQ (%d)\n", r);
		जाओ out_video_निकास;
	पूर्ण

	pm_runसमय_put_noidle(&pci_dev->dev);
	pm_runसमय_allow(&pci_dev->dev);

	वापस 0;

out_video_निकास:
	imgu_video_nodes_निकास(imgu);
out_css_cleanup:
	imgu_css_cleanup(&imgu->css);
out_dmamap_निकास:
	imgu_dmamap_निकास(imgu);
out_mmu_निकास:
	imgu_mmu_निकास(imgu->mmu);
out_css_घातerकरोwn:
	imgu_css_set_घातerकरोwn(&pci_dev->dev, imgu->base);
out_mutex_destroy:
	mutex_destroy(&imgu->streaming_lock);
	mutex_destroy(&imgu->lock);

	वापस r;
पूर्ण

अटल व्योम imgu_pci_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा imgu_device *imgu = pci_get_drvdata(pci_dev);

	pm_runसमय_क्रमbid(&pci_dev->dev);
	pm_runसमय_get_noresume(&pci_dev->dev);

	imgu_video_nodes_निकास(imgu);
	imgu_css_cleanup(&imgu->css);
	imgu_css_set_घातerकरोwn(&pci_dev->dev, imgu->base);
	imgu_dmamap_निकास(imgu);
	imgu_mmu_निकास(imgu->mmu);
	mutex_destroy(&imgu->streaming_lock);
	mutex_destroy(&imgu->lock);
पूर्ण

अटल पूर्णांक __maybe_unused imgu_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा imgu_device *imgu = pci_get_drvdata(pci_dev);

	dev_dbg(dev, "enter %s\n", __func__);
	imgu->suspend_in_stream = imgu_css_is_streaming(&imgu->css);
	अगर (!imgu->suspend_in_stream)
		जाओ out;
	/* Block new buffers to be queued to CSS. */
	atomic_set(&imgu->qbuf_barrier, 1);
	/*
	 * Wait क्रम currently running irq handler to be करोne so that
	 * no new buffers will be queued to fw later.
	 */
	synchronize_irq(pci_dev->irq);
	/* Wait until all buffers in CSS are करोne. */
	अगर (!रुको_event_समयout(imgu->buf_drain_wq,
	    imgu_css_queue_empty(&imgu->css), msecs_to_jअगरfies(1000)))
		dev_err(dev, "wait buffer drain timeout.\n");

	imgu_css_stop_streaming(&imgu->css);
	atomic_set(&imgu->qbuf_barrier, 0);
	imgu_घातerकरोwn(imgu);
	pm_runसमय_क्रमce_suspend(dev);
out:
	dev_dbg(dev, "leave %s\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imgu_resume(काष्ठा device *dev)
अणु
	काष्ठा imgu_device *imgu = dev_get_drvdata(dev);
	पूर्णांक r = 0;
	अचिन्हित पूर्णांक pipe;

	dev_dbg(dev, "enter %s\n", __func__);

	अगर (!imgu->suspend_in_stream)
		जाओ out;

	pm_runसमय_क्रमce_resume(dev);

	r = imgu_घातerup(imgu);
	अगर (r) अणु
		dev_err(dev, "failed to power up imgu\n");
		जाओ out;
	पूर्ण

	/* Start CSS streaming */
	r = imgu_css_start_streaming(&imgu->css);
	अगर (r) अणु
		dev_err(dev, "failed to resume css streaming (%d)", r);
		जाओ out;
	पूर्ण

	क्रम_each_set_bit(pipe, imgu->css.enabled_pipes, IMGU_MAX_PIPE_NUM) अणु
		r = imgu_queue_buffers(imgu, true, pipe);
		अगर (r)
			dev_err(dev, "failed to queue buffers to pipe %d (%d)",
				pipe, r);
	पूर्ण

out:
	dev_dbg(dev, "leave %s\n", __func__);

	वापस r;
पूर्ण

/*
 * PCI rpm framework checks the existence of driver rpm callbacks.
 * Place a dummy callback here to aव्योम rpm going पूर्णांकo error state.
 */
अटल __maybe_unused पूर्णांक imgu_rpm_dummy_cb(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops imgu_pm_ops = अणु
	SET_RUNTIME_PM_OPS(&imgu_rpm_dummy_cb, &imgu_rpm_dummy_cb, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(&imgu_suspend, &imgu_resume)
पूर्ण;

अटल स्थिर काष्ठा pci_device_id imgu_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, IMGU_PCI_ID) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, imgu_pci_tbl);

अटल काष्ठा pci_driver imgu_pci_driver = अणु
	.name = IMGU_NAME,
	.id_table = imgu_pci_tbl,
	.probe = imgu_pci_probe,
	.हटाओ = imgu_pci_हटाओ,
	.driver = अणु
		.pm = &imgu_pm_ops,
	पूर्ण,
पूर्ण;

module_pci_driver(imgu_pci_driver);

MODULE_AUTHOR("Tuukka Toivonen <tuukka.toivonen@intel.com>");
MODULE_AUTHOR("Tianshu Qiu <tian.shu.qiu@intel.com>");
MODULE_AUTHOR("Jian Xu Zheng <jian.xu.zheng@intel.com>");
MODULE_AUTHOR("Yuning Pu <yuning.pu@intel.com>");
MODULE_AUTHOR("Yong Zhi <yong.zhi@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel ipu3_imgu PCI driver");
