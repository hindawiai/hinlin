<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम STM32 Digital Camera Memory Interface
 *
 * Copyright (C) STMicroelectronics SA 2017
 * Authors: Yannick Fertre <yannick.fertre@st.com>
 *          Hugues Fruchet <hugues.fruchet@st.com>
 *          क्रम STMicroelectronics.
 *
 * This driver is based on aपंचांगel_isi.c
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-image-sizes.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-rect.h>
#समावेश <media/videobuf2-dma-contig.h>

#घोषणा DRV_NAME "stm32-dcmi"

/* Registers offset क्रम DCMI */
#घोषणा DCMI_CR		0x00 /* Control Register */
#घोषणा DCMI_SR		0x04 /* Status Register */
#घोषणा DCMI_RIS	0x08 /* Raw Interrupt Status रेजिस्टर */
#घोषणा DCMI_IER	0x0C /* Interrupt Enable Register */
#घोषणा DCMI_MIS	0x10 /* Masked Interrupt Status रेजिस्टर */
#घोषणा DCMI_ICR	0x14 /* Interrupt Clear Register */
#घोषणा DCMI_ESCR	0x18 /* Embedded Synchronization Code Register */
#घोषणा DCMI_ESUR	0x1C /* Embedded Synchronization Unmask Register */
#घोषणा DCMI_CWSTRT	0x20 /* Crop Winकरोw STaRT */
#घोषणा DCMI_CWSIZE	0x24 /* Crop Winकरोw SIZE */
#घोषणा DCMI_DR		0x28 /* Data Register */
#घोषणा DCMI_IDR	0x2C /* IDentअगरier Register */

/* Bits definition क्रम control रेजिस्टर (DCMI_CR) */
#घोषणा CR_CAPTURE	BIT(0)
#घोषणा CR_CM		BIT(1)
#घोषणा CR_CROP		BIT(2)
#घोषणा CR_JPEG		BIT(3)
#घोषणा CR_ESS		BIT(4)
#घोषणा CR_PCKPOL	BIT(5)
#घोषणा CR_HSPOL	BIT(6)
#घोषणा CR_VSPOL	BIT(7)
#घोषणा CR_FCRC_0	BIT(8)
#घोषणा CR_FCRC_1	BIT(9)
#घोषणा CR_EDM_0	BIT(10)
#घोषणा CR_EDM_1	BIT(11)
#घोषणा CR_ENABLE	BIT(14)

/* Bits definition क्रम status रेजिस्टर (DCMI_SR) */
#घोषणा SR_HSYNC	BIT(0)
#घोषणा SR_VSYNC	BIT(1)
#घोषणा SR_FNE		BIT(2)

/*
 * Bits definition क्रम पूर्णांकerrupt रेजिस्टरs
 * (DCMI_RIS, DCMI_IER, DCMI_MIS, DCMI_ICR)
 */
#घोषणा IT_FRAME	BIT(0)
#घोषणा IT_OVR		BIT(1)
#घोषणा IT_ERR		BIT(2)
#घोषणा IT_VSYNC	BIT(3)
#घोषणा IT_LINE		BIT(4)

क्रमागत state अणु
	STOPPED = 0,
	WAIT_FOR_BUFFER,
	RUNNING,
पूर्ण;

#घोषणा MIN_WIDTH	16U
#घोषणा MAX_WIDTH	2592U
#घोषणा MIN_HEIGHT	16U
#घोषणा MAX_HEIGHT	2592U

#घोषणा TIMEOUT_MS	1000

#घोषणा OVERRUN_ERROR_THRESHOLD	3

काष्ठा dcmi_क्रमmat अणु
	u32	fourcc;
	u32	mbus_code;
	u8	bpp;
पूर्ण;

काष्ठा dcmi_framesize अणु
	u32	width;
	u32	height;
पूर्ण;

काष्ठा dcmi_buf अणु
	काष्ठा vb2_v4l2_buffer	vb;
	bool			prepared;
	dma_addr_t		paddr;
	माप_प्रकार			size;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा sपंचांग32_dcmi अणु
	/* Protects the access of variables shared within the पूर्णांकerrupt */
	spinlock_t			irqlock;
	काष्ठा device			*dev;
	व्योम __iomem			*regs;
	काष्ठा resource			*res;
	काष्ठा reset_control		*rstc;
	पूर्णांक				sequence;
	काष्ठा list_head		buffers;
	काष्ठा dcmi_buf			*active;

	काष्ठा v4l2_device		v4l2_dev;
	काष्ठा video_device		*vdev;
	काष्ठा v4l2_async_notअगरier	notअगरier;
	काष्ठा v4l2_subdev		*source;
	काष्ठा v4l2_क्रमmat		fmt;
	काष्ठा v4l2_rect		crop;
	bool				करो_crop;

	स्थिर काष्ठा dcmi_क्रमmat	**sd_क्रमmats;
	अचिन्हित पूर्णांक			num_of_sd_क्रमmats;
	स्थिर काष्ठा dcmi_क्रमmat	*sd_क्रमmat;
	काष्ठा dcmi_framesize		*sd_framesizes;
	अचिन्हित पूर्णांक			num_of_sd_framesizes;
	काष्ठा dcmi_framesize		sd_framesize;
	काष्ठा v4l2_rect		sd_bounds;

	/* Protect this data काष्ठाure */
	काष्ठा mutex			lock;
	काष्ठा vb2_queue		queue;

	काष्ठा v4l2_fwnode_bus_parallel	bus;
	क्रमागत v4l2_mbus_type		bus_type;
	काष्ठा completion		complete;
	काष्ठा clk			*mclk;
	क्रमागत state			state;
	काष्ठा dma_chan			*dma_chan;
	dma_cookie_t			dma_cookie;
	u32				misr;
	पूर्णांक				errors_count;
	पूर्णांक				overrun_count;
	पूर्णांक				buffers_count;

	/* Ensure DMA operations atomicity */
	काष्ठा mutex			dma_lock;

	काष्ठा media_device		mdev;
	काष्ठा media_pad		vid_cap_pad;
	काष्ठा media_pipeline		pipeline;
पूर्ण;

अटल अंतरभूत काष्ठा sपंचांग32_dcmi *notअगरier_to_dcmi(काष्ठा v4l2_async_notअगरier *n)
अणु
	वापस container_of(n, काष्ठा sपंचांग32_dcmi, notअगरier);
पूर्ण

अटल अंतरभूत u32 reg_पढ़ो(व्योम __iomem *base, u32 reg)
अणु
	वापस पढ़ोl_relaxed(base + reg);
पूर्ण

अटल अंतरभूत व्योम reg_ग_लिखो(व्योम __iomem *base, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, base + reg);
पूर्ण

अटल अंतरभूत व्योम reg_set(व्योम __iomem *base, u32 reg, u32 mask)
अणु
	reg_ग_लिखो(base, reg, reg_पढ़ो(base, reg) | mask);
पूर्ण

अटल अंतरभूत व्योम reg_clear(व्योम __iomem *base, u32 reg, u32 mask)
अणु
	reg_ग_लिखो(base, reg, reg_पढ़ो(base, reg) & ~mask);
पूर्ण

अटल पूर्णांक dcmi_start_capture(काष्ठा sपंचांग32_dcmi *dcmi, काष्ठा dcmi_buf *buf);

अटल व्योम dcmi_buffer_करोne(काष्ठा sपंचांग32_dcmi *dcmi,
			     काष्ठा dcmi_buf *buf,
			     माप_प्रकार bytesused,
			     पूर्णांक err)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf;

	अगर (!buf)
		वापस;

	list_del_init(&buf->list);

	vbuf = &buf->vb;

	vbuf->sequence = dcmi->sequence++;
	vbuf->field = V4L2_FIELD_NONE;
	vbuf->vb2_buf.बारtamp = kसमय_get_ns();
	vb2_set_plane_payload(&vbuf->vb2_buf, 0, bytesused);
	vb2_buffer_करोne(&vbuf->vb2_buf,
			err ? VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
	dev_dbg(dcmi->dev, "buffer[%d] done seq=%d, bytesused=%zu\n",
		vbuf->vb2_buf.index, vbuf->sequence, bytesused);

	dcmi->buffers_count++;
	dcmi->active = शून्य;
पूर्ण

अटल पूर्णांक dcmi_restart_capture(काष्ठा sपंचांग32_dcmi *dcmi)
अणु
	काष्ठा dcmi_buf *buf;

	spin_lock_irq(&dcmi->irqlock);

	अगर (dcmi->state != RUNNING) अणु
		spin_unlock_irq(&dcmi->irqlock);
		वापस -EINVAL;
	पूर्ण

	/* Restart a new DMA transfer with next buffer */
	अगर (list_empty(&dcmi->buffers)) अणु
		dev_dbg(dcmi->dev, "Capture restart is deferred to next buffer queueing\n");
		dcmi->state = WAIT_FOR_BUFFER;
		spin_unlock_irq(&dcmi->irqlock);
		वापस 0;
	पूर्ण
	buf = list_entry(dcmi->buffers.next, काष्ठा dcmi_buf, list);
	dcmi->active = buf;

	spin_unlock_irq(&dcmi->irqlock);

	वापस dcmi_start_capture(dcmi, buf);
पूर्ण

अटल व्योम dcmi_dma_callback(व्योम *param)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = (काष्ठा sपंचांग32_dcmi *)param;
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;
	काष्ठा dcmi_buf *buf = dcmi->active;

	spin_lock_irq(&dcmi->irqlock);

	/* Check DMA status */
	status = dmaengine_tx_status(dcmi->dma_chan, dcmi->dma_cookie, &state);

	चयन (status) अणु
	हाल DMA_IN_PROGRESS:
		dev_dbg(dcmi->dev, "%s: Received DMA_IN_PROGRESS\n", __func__);
		अवरोध;
	हाल DMA_PAUSED:
		dev_err(dcmi->dev, "%s: Received DMA_PAUSED\n", __func__);
		अवरोध;
	हाल DMA_ERROR:
		dev_err(dcmi->dev, "%s: Received DMA_ERROR\n", __func__);

		/* Return buffer to V4L2 in error state */
		dcmi_buffer_करोne(dcmi, buf, 0, -EIO);
		अवरोध;
	हाल DMA_COMPLETE:
		dev_dbg(dcmi->dev, "%s: Received DMA_COMPLETE\n", __func__);

		/* Return buffer to V4L2 */
		dcmi_buffer_करोne(dcmi, buf, buf->size, 0);

		spin_unlock_irq(&dcmi->irqlock);

		/* Restart capture */
		अगर (dcmi_restart_capture(dcmi))
			dev_err(dcmi->dev, "%s: Cannot restart capture on DMA complete\n",
				__func__);
		वापस;
	शेष:
		dev_err(dcmi->dev, "%s: Received unknown status\n", __func__);
		अवरोध;
	पूर्ण

	spin_unlock_irq(&dcmi->irqlock);
पूर्ण

अटल पूर्णांक dcmi_start_dma(काष्ठा sपंचांग32_dcmi *dcmi,
			  काष्ठा dcmi_buf *buf)
अणु
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	काष्ठा dma_slave_config config;
	पूर्णांक ret;

	स_रखो(&config, 0, माप(config));

	config.src_addr = (dma_addr_t)dcmi->res->start + DCMI_DR;
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	config.dst_maxburst = 4;

	/* Configure DMA channel */
	ret = dmaengine_slave_config(dcmi->dma_chan, &config);
	अगर (ret < 0) अणु
		dev_err(dcmi->dev, "%s: DMA channel config failed (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/*
	 * Aव्योम call of dmaengine_terminate_sync() between
	 * dmaengine_prep_slave_single() and dmaengine_submit()
	 * by locking the whole DMA submission sequence
	 */
	mutex_lock(&dcmi->dma_lock);

	/* Prepare a DMA transaction */
	desc = dmaengine_prep_slave_single(dcmi->dma_chan, buf->paddr,
					   buf->size,
					   DMA_DEV_TO_MEM,
					   DMA_PREP_INTERRUPT);
	अगर (!desc) अणु
		dev_err(dcmi->dev, "%s: DMA dmaengine_prep_slave_single failed for buffer phy=%pad size=%zu\n",
			__func__, &buf->paddr, buf->size);
		mutex_unlock(&dcmi->dma_lock);
		वापस -EINVAL;
	पूर्ण

	/* Set completion callback routine क्रम notअगरication */
	desc->callback = dcmi_dma_callback;
	desc->callback_param = dcmi;

	/* Push current DMA transaction in the pending queue */
	dcmi->dma_cookie = dmaengine_submit(desc);
	अगर (dma_submit_error(dcmi->dma_cookie)) अणु
		dev_err(dcmi->dev, "%s: DMA submission failed\n", __func__);
		mutex_unlock(&dcmi->dma_lock);
		वापस -ENXIO;
	पूर्ण

	mutex_unlock(&dcmi->dma_lock);

	dma_async_issue_pending(dcmi->dma_chan);

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_start_capture(काष्ठा sपंचांग32_dcmi *dcmi, काष्ठा dcmi_buf *buf)
अणु
	पूर्णांक ret;

	अगर (!buf)
		वापस -EINVAL;

	ret = dcmi_start_dma(dcmi, buf);
	अगर (ret) अणु
		dcmi->errors_count++;
		वापस ret;
	पूर्ण

	/* Enable capture */
	reg_set(dcmi->regs, DCMI_CR, CR_CAPTURE);

	वापस 0;
पूर्ण

अटल व्योम dcmi_set_crop(काष्ठा sपंचांग32_dcmi *dcmi)
अणु
	u32 size, start;

	/* Crop resolution */
	size = ((dcmi->crop.height - 1) << 16) |
		((dcmi->crop.width << 1) - 1);
	reg_ग_लिखो(dcmi->regs, DCMI_CWSIZE, size);

	/* Crop start poपूर्णांक */
	start = ((dcmi->crop.top) << 16) |
		 ((dcmi->crop.left << 1));
	reg_ग_लिखो(dcmi->regs, DCMI_CWSTRT, start);

	dev_dbg(dcmi->dev, "Cropping to %ux%u@%u:%u\n",
		dcmi->crop.width, dcmi->crop.height,
		dcmi->crop.left, dcmi->crop.top);

	/* Enable crop */
	reg_set(dcmi->regs, DCMI_CR, CR_CROP);
पूर्ण

अटल व्योम dcmi_process_jpeg(काष्ठा sपंचांग32_dcmi *dcmi)
अणु
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;
	काष्ठा dcmi_buf *buf = dcmi->active;

	अगर (!buf)
		वापस;

	/*
	 * Because of variable JPEG buffer size sent by sensor,
	 * DMA transfer never completes due to transfer size never reached.
	 * In order to ensure that all the JPEG data are transferred
	 * in active buffer memory, DMA is drained.
	 * Then DMA tx status gives the amount of data transferred
	 * to memory, which is then वापसed to V4L2 through the active
	 * buffer payload.
	 */

	/* Drain DMA */
	dmaengine_synchronize(dcmi->dma_chan);

	/* Get DMA residue to get JPEG size */
	status = dmaengine_tx_status(dcmi->dma_chan, dcmi->dma_cookie, &state);
	अगर (status != DMA_ERROR && state.residue < buf->size) अणु
		/* Return JPEG buffer to V4L2 with received JPEG buffer size */
		dcmi_buffer_करोne(dcmi, buf, buf->size - state.residue, 0);
	पूर्ण अन्यथा अणु
		dcmi->errors_count++;
		dev_err(dcmi->dev, "%s: Cannot get JPEG size from DMA\n",
			__func__);
		/* Return JPEG buffer to V4L2 in ERROR state */
		dcmi_buffer_करोne(dcmi, buf, 0, -EIO);
	पूर्ण

	/* Abort DMA operation */
	dmaengine_terminate_sync(dcmi->dma_chan);

	/* Restart capture */
	अगर (dcmi_restart_capture(dcmi))
		dev_err(dcmi->dev, "%s: Cannot restart capture on JPEG received\n",
			__func__);
पूर्ण

अटल irqवापस_t dcmi_irq_thपढ़ो(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = arg;

	spin_lock_irq(&dcmi->irqlock);

	अगर (dcmi->misr & IT_OVR) अणु
		dcmi->overrun_count++;
		अगर (dcmi->overrun_count > OVERRUN_ERROR_THRESHOLD)
			dcmi->errors_count++;
	पूर्ण
	अगर (dcmi->misr & IT_ERR)
		dcmi->errors_count++;

	अगर (dcmi->sd_क्रमmat->fourcc == V4L2_PIX_FMT_JPEG &&
	    dcmi->misr & IT_FRAME) अणु
		/* JPEG received */
		spin_unlock_irq(&dcmi->irqlock);
		dcmi_process_jpeg(dcmi);
		वापस IRQ_HANDLED;
	पूर्ण

	spin_unlock_irq(&dcmi->irqlock);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t dcmi_irq_callback(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = arg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dcmi->irqlock, flags);

	dcmi->misr = reg_पढ़ो(dcmi->regs, DCMI_MIS);

	/* Clear पूर्णांकerrupt */
	reg_set(dcmi->regs, DCMI_ICR, IT_FRAME | IT_OVR | IT_ERR);

	spin_unlock_irqrestore(&dcmi->irqlock, flags);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल पूर्णांक dcmi_queue_setup(काष्ठा vb2_queue *vq,
			    अचिन्हित पूर्णांक *nbuffers,
			    अचिन्हित पूर्णांक *nplanes,
			    अचिन्हित पूर्णांक sizes[],
			    काष्ठा device *alloc_devs[])
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = vb2_get_drv_priv(vq);
	अचिन्हित पूर्णांक size;

	size = dcmi->fmt.fmt.pix.sizeimage;

	/* Make sure the image size is large enough */
	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;

	dev_dbg(dcmi->dev, "Setup queue, count=%d, size=%d\n",
		*nbuffers, size);

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_buf_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा dcmi_buf *buf = container_of(vbuf, काष्ठा dcmi_buf, vb);

	INIT_LIST_HEAD(&buf->list);

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi =  vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा dcmi_buf *buf = container_of(vbuf, काष्ठा dcmi_buf, vb);
	अचिन्हित दीर्घ size;

	size = dcmi->fmt.fmt.pix.sizeimage;

	अगर (vb2_plane_size(vb, 0) < size) अणु
		dev_err(dcmi->dev, "%s data will not fit into plane (%lu < %lu)\n",
			__func__, vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, size);

	अगर (!buf->prepared) अणु
		/* Get memory addresses */
		buf->paddr =
			vb2_dma_contig_plane_dma_addr(&buf->vb.vb2_buf, 0);
		buf->size = vb2_plane_size(&buf->vb.vb2_buf, 0);
		buf->prepared = true;

		vb2_set_plane_payload(&buf->vb.vb2_buf, 0, buf->size);

		dev_dbg(dcmi->dev, "buffer[%d] phy=%pad size=%zu\n",
			vb->index, &buf->paddr, buf->size);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dcmi_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi =  vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा dcmi_buf *buf = container_of(vbuf, काष्ठा dcmi_buf, vb);

	spin_lock_irq(&dcmi->irqlock);

	/* Enqueue to video buffers list */
	list_add_tail(&buf->list, &dcmi->buffers);

	अगर (dcmi->state == WAIT_FOR_BUFFER) अणु
		dcmi->state = RUNNING;
		dcmi->active = buf;

		dev_dbg(dcmi->dev, "Starting capture on buffer[%d] queued\n",
			buf->vb.vb2_buf.index);

		spin_unlock_irq(&dcmi->irqlock);
		अगर (dcmi_start_capture(dcmi, buf))
			dev_err(dcmi->dev, "%s: Cannot restart capture on overflow or error\n",
				__func__);
		वापस;
	पूर्ण

	spin_unlock_irq(&dcmi->irqlock);
पूर्ण

अटल काष्ठा media_entity *dcmi_find_source(काष्ठा sपंचांग32_dcmi *dcmi)
अणु
	काष्ठा media_entity *entity = &dcmi->vdev->entity;
	काष्ठा media_pad *pad;

	/* Walk searching क्रम entity having no sink */
	जबतक (1) अणु
		pad = &entity->pads[0];
		अगर (!(pad->flags & MEDIA_PAD_FL_SINK))
			अवरोध;

		pad = media_entity_remote_pad(pad);
		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			अवरोध;

		entity = pad->entity;
	पूर्ण

	वापस entity;
पूर्ण

अटल पूर्णांक dcmi_pipeline_s_fmt(काष्ठा sपंचांग32_dcmi *dcmi,
			       काष्ठा v4l2_subdev_pad_config *pad_cfg,
			       काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा media_entity *entity = &dcmi->source->entity;
	काष्ठा v4l2_subdev *subdev;
	काष्ठा media_pad *sink_pad = शून्य;
	काष्ठा media_pad *src_pad = शून्य;
	काष्ठा media_pad *pad = शून्य;
	काष्ठा v4l2_subdev_क्रमmat fmt = *क्रमmat;
	bool found = false;
	पूर्णांक ret;

	/*
	 * Starting from sensor subdevice, walk within
	 * pipeline and set क्रमmat on each subdevice
	 */
	जबतक (1) अणु
		अचिन्हित पूर्णांक i;

		/* Search अगर current entity has a source pad */
		क्रम (i = 0; i < entity->num_pads; i++) अणु
			pad = &entity->pads[i];
			अगर (pad->flags & MEDIA_PAD_FL_SOURCE) अणु
				src_pad = pad;
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!found)
			अवरोध;

		subdev = media_entity_to_v4l2_subdev(entity);

		/* Propagate क्रमmat on sink pad अगर any, otherwise source pad */
		अगर (sink_pad)
			pad = sink_pad;

		dev_dbg(dcmi->dev, "\"%s\":%d pad format set to 0x%x %ux%u\n",
			subdev->name, pad->index, क्रमmat->क्रमmat.code,
			क्रमmat->क्रमmat.width, क्रमmat->क्रमmat.height);

		fmt.pad = pad->index;
		ret = v4l2_subdev_call(subdev, pad, set_fmt, pad_cfg, &fmt);
		अगर (ret < 0) अणु
			dev_err(dcmi->dev, "%s: Failed to set format 0x%x %ux%u on \"%s\":%d pad (%d)\n",
				__func__, क्रमmat->क्रमmat.code,
				क्रमmat->क्रमmat.width, क्रमmat->क्रमmat.height,
				subdev->name, pad->index, ret);
			वापस ret;
		पूर्ण

		अगर (fmt.क्रमmat.code != क्रमmat->क्रमmat.code ||
		    fmt.क्रमmat.width != क्रमmat->क्रमmat.width ||
		    fmt.क्रमmat.height != क्रमmat->क्रमmat.height) अणु
			dev_dbg(dcmi->dev, "\"%s\":%d pad format has been changed to 0x%x %ux%u\n",
				subdev->name, pad->index, fmt.क्रमmat.code,
				fmt.क्रमmat.width, fmt.क्रमmat.height);
		पूर्ण

		/* Walk to next entity */
		sink_pad = media_entity_remote_pad(src_pad);
		अगर (!sink_pad || !is_media_entity_v4l2_subdev(sink_pad->entity))
			अवरोध;

		entity = sink_pad->entity;
	पूर्ण
	*क्रमmat = fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_pipeline_s_stream(काष्ठा sपंचांग32_dcmi *dcmi, पूर्णांक state)
अणु
	काष्ठा media_entity *entity = &dcmi->vdev->entity;
	काष्ठा v4l2_subdev *subdev;
	काष्ठा media_pad *pad;
	पूर्णांक ret;

	/* Start/stop all entities within pipeline */
	जबतक (1) अणु
		pad = &entity->pads[0];
		अगर (!(pad->flags & MEDIA_PAD_FL_SINK))
			अवरोध;

		pad = media_entity_remote_pad(pad);
		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			अवरोध;

		entity = pad->entity;
		subdev = media_entity_to_v4l2_subdev(entity);

		ret = v4l2_subdev_call(subdev, video, s_stream, state);
		अगर (ret < 0 && ret != -ENOIOCTLCMD) अणु
			dev_err(dcmi->dev, "%s: \"%s\" failed to %s streaming (%d)\n",
				__func__, subdev->name,
				state ? "start" : "stop", ret);
			वापस ret;
		पूर्ण

		dev_dbg(dcmi->dev, "\"%s\" is %s\n",
			subdev->name, state ? "started" : "stopped");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_pipeline_start(काष्ठा sपंचांग32_dcmi *dcmi)
अणु
	वापस dcmi_pipeline_s_stream(dcmi, 1);
पूर्ण

अटल व्योम dcmi_pipeline_stop(काष्ठा sपंचांग32_dcmi *dcmi)
अणु
	dcmi_pipeline_s_stream(dcmi, 0);
पूर्ण

अटल पूर्णांक dcmi_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = vb2_get_drv_priv(vq);
	काष्ठा dcmi_buf *buf, *node;
	u32 val = 0;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dcmi->dev);
	अगर (ret < 0) अणु
		dev_err(dcmi->dev, "%s: Failed to start streaming, cannot get sync (%d)\n",
			__func__, ret);
		जाओ err_pm_put;
	पूर्ण

	ret = media_pipeline_start(&dcmi->vdev->entity, &dcmi->pipeline);
	अगर (ret < 0) अणु
		dev_err(dcmi->dev, "%s: Failed to start streaming, media pipeline start error (%d)\n",
			__func__, ret);
		जाओ err_pm_put;
	पूर्ण

	ret = dcmi_pipeline_start(dcmi);
	अगर (ret)
		जाओ err_media_pipeline_stop;

	spin_lock_irq(&dcmi->irqlock);

	/* Set bus width */
	चयन (dcmi->bus.bus_width) अणु
	हाल 14:
		val |= CR_EDM_0 | CR_EDM_1;
		अवरोध;
	हाल 12:
		val |= CR_EDM_1;
		अवरोध;
	हाल 10:
		val |= CR_EDM_0;
		अवरोध;
	शेष:
		/* Set bus width to 8 bits by शेष */
		अवरोध;
	पूर्ण

	/* Set vertical synchronization polarity */
	अगर (dcmi->bus.flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
		val |= CR_VSPOL;

	/* Set horizontal synchronization polarity */
	अगर (dcmi->bus.flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
		val |= CR_HSPOL;

	/* Set pixel घड़ी polarity */
	अगर (dcmi->bus.flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
		val |= CR_PCKPOL;

	/*
	 * BT656 embedded synchronisation bus mode.
	 *
	 * Default SAV/EAV mode is supported here with शेष codes
	 * SAV=0xff000080 & EAV=0xff00009d.
	 * With DCMI this means LSC=SAV=0x80 & LEC=EAV=0x9d.
	 */
	अगर (dcmi->bus_type == V4L2_MBUS_BT656) अणु
		val |= CR_ESS;

		/* Unmask all codes */
		reg_ग_लिखो(dcmi->regs, DCMI_ESUR, 0xffffffff);/* FEC:LEC:LSC:FSC */

		/* Trig on LSC=0x80 & LEC=0x9d codes, ignore FSC and FEC */
		reg_ग_लिखो(dcmi->regs, DCMI_ESCR, 0xff9d80ff);/* FEC:LEC:LSC:FSC */
	पूर्ण

	reg_ग_लिखो(dcmi->regs, DCMI_CR, val);

	/* Set crop */
	अगर (dcmi->करो_crop)
		dcmi_set_crop(dcmi);

	/* Enable jpeg capture */
	अगर (dcmi->sd_क्रमmat->fourcc == V4L2_PIX_FMT_JPEG)
		reg_set(dcmi->regs, DCMI_CR, CR_CM);/* Snapshot mode */

	/* Enable dcmi */
	reg_set(dcmi->regs, DCMI_CR, CR_ENABLE);

	dcmi->sequence = 0;
	dcmi->errors_count = 0;
	dcmi->overrun_count = 0;
	dcmi->buffers_count = 0;

	/*
	 * Start transfer अगर at least one buffer has been queued,
	 * otherwise transfer is deferred at buffer queueing
	 */
	अगर (list_empty(&dcmi->buffers)) अणु
		dev_dbg(dcmi->dev, "Start streaming is deferred to next buffer queueing\n");
		dcmi->state = WAIT_FOR_BUFFER;
		spin_unlock_irq(&dcmi->irqlock);
		वापस 0;
	पूर्ण

	buf = list_entry(dcmi->buffers.next, काष्ठा dcmi_buf, list);
	dcmi->active = buf;

	dcmi->state = RUNNING;

	dev_dbg(dcmi->dev, "Start streaming, starting capture\n");

	spin_unlock_irq(&dcmi->irqlock);
	ret = dcmi_start_capture(dcmi, buf);
	अगर (ret) अणु
		dev_err(dcmi->dev, "%s: Start streaming failed, cannot start capture\n",
			__func__);
		जाओ err_pipeline_stop;
	पूर्ण

	/* Enable पूर्णांकerruptions */
	अगर (dcmi->sd_क्रमmat->fourcc == V4L2_PIX_FMT_JPEG)
		reg_set(dcmi->regs, DCMI_IER, IT_FRAME | IT_OVR | IT_ERR);
	अन्यथा
		reg_set(dcmi->regs, DCMI_IER, IT_OVR | IT_ERR);

	वापस 0;

err_pipeline_stop:
	dcmi_pipeline_stop(dcmi);

err_media_pipeline_stop:
	media_pipeline_stop(&dcmi->vdev->entity);

err_pm_put:
	pm_runसमय_put(dcmi->dev);
	spin_lock_irq(&dcmi->irqlock);
	/*
	 * Return all buffers to vb2 in QUEUED state.
	 * This will give ownership back to userspace
	 */
	list_क्रम_each_entry_safe(buf, node, &dcmi->buffers, list) अणु
		list_del_init(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
	पूर्ण
	dcmi->active = शून्य;
	spin_unlock_irq(&dcmi->irqlock);

	वापस ret;
पूर्ण

अटल व्योम dcmi_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = vb2_get_drv_priv(vq);
	काष्ठा dcmi_buf *buf, *node;

	dcmi_pipeline_stop(dcmi);

	media_pipeline_stop(&dcmi->vdev->entity);

	spin_lock_irq(&dcmi->irqlock);

	/* Disable पूर्णांकerruptions */
	reg_clear(dcmi->regs, DCMI_IER, IT_FRAME | IT_OVR | IT_ERR);

	/* Disable DCMI */
	reg_clear(dcmi->regs, DCMI_CR, CR_ENABLE);

	/* Return all queued buffers to vb2 in ERROR state */
	list_क्रम_each_entry_safe(buf, node, &dcmi->buffers, list) अणु
		list_del_init(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण

	dcmi->active = शून्य;
	dcmi->state = STOPPED;

	spin_unlock_irq(&dcmi->irqlock);

	/* Stop all pending DMA operations */
	mutex_lock(&dcmi->dma_lock);
	dmaengine_terminate_sync(dcmi->dma_chan);
	mutex_unlock(&dcmi->dma_lock);

	pm_runसमय_put(dcmi->dev);

	अगर (dcmi->errors_count)
		dev_warn(dcmi->dev, "Some errors found while streaming: errors=%d (overrun=%d), buffers=%d\n",
			 dcmi->errors_count, dcmi->overrun_count,
			 dcmi->buffers_count);
	dev_dbg(dcmi->dev, "Stop streaming, errors=%d (overrun=%d), buffers=%d\n",
		dcmi->errors_count, dcmi->overrun_count,
		dcmi->buffers_count);
पूर्ण

अटल स्थिर काष्ठा vb2_ops dcmi_video_qops = अणु
	.queue_setup		= dcmi_queue_setup,
	.buf_init		= dcmi_buf_init,
	.buf_prepare		= dcmi_buf_prepare,
	.buf_queue		= dcmi_buf_queue,
	.start_streaming	= dcmi_start_streaming,
	.stop_streaming		= dcmi_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक dcmi_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = video_drvdata(file);

	*fmt = dcmi->fmt;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dcmi_क्रमmat *find_क्रमmat_by_fourcc(काष्ठा sपंचांग32_dcmi *dcmi,
						       अचिन्हित पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक num_क्रमmats = dcmi->num_of_sd_क्रमmats;
	स्थिर काष्ठा dcmi_क्रमmat *fmt;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_क्रमmats; i++) अणु
		fmt = dcmi->sd_क्रमmats[i];
		अगर (fmt->fourcc == fourcc)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम __find_outer_frame_size(काष्ठा sपंचांग32_dcmi *dcmi,
				    काष्ठा v4l2_pix_क्रमmat *pix,
				    काष्ठा dcmi_framesize *framesize)
अणु
	काष्ठा dcmi_framesize *match = शून्य;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक min_err = अच_पूर्णांक_उच्च;

	क्रम (i = 0; i < dcmi->num_of_sd_framesizes; i++) अणु
		काष्ठा dcmi_framesize *fsize = &dcmi->sd_framesizes[i];
		पूर्णांक w_err = (fsize->width - pix->width);
		पूर्णांक h_err = (fsize->height - pix->height);
		पूर्णांक err = w_err + h_err;

		अगर (w_err >= 0 && h_err >= 0 && err < min_err) अणु
			min_err = err;
			match = fsize;
		पूर्ण
	पूर्ण
	अगर (!match)
		match = &dcmi->sd_framesizes[0];

	*framesize = *match;
पूर्ण

अटल पूर्णांक dcmi_try_fmt(काष्ठा sपंचांग32_dcmi *dcmi, काष्ठा v4l2_क्रमmat *f,
			स्थिर काष्ठा dcmi_क्रमmat **sd_क्रमmat,
			काष्ठा dcmi_framesize *sd_framesize)
अणु
	स्थिर काष्ठा dcmi_क्रमmat *sd_fmt;
	काष्ठा dcmi_framesize sd_fsize;
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा v4l2_subdev_pad_config pad_cfg;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_TRY,
	पूर्ण;
	bool करो_crop;
	पूर्णांक ret;

	sd_fmt = find_क्रमmat_by_fourcc(dcmi, pix->pixelक्रमmat);
	अगर (!sd_fmt) अणु
		अगर (!dcmi->num_of_sd_क्रमmats)
			वापस -ENODATA;

		sd_fmt = dcmi->sd_क्रमmats[dcmi->num_of_sd_क्रमmats - 1];
		pix->pixelक्रमmat = sd_fmt->fourcc;
	पूर्ण

	/* Limit to hardware capabilities */
	pix->width = clamp(pix->width, MIN_WIDTH, MAX_WIDTH);
	pix->height = clamp(pix->height, MIN_HEIGHT, MAX_HEIGHT);

	/* No crop अगर JPEG is requested */
	करो_crop = dcmi->करो_crop && (pix->pixelक्रमmat != V4L2_PIX_FMT_JPEG);

	अगर (करो_crop && dcmi->num_of_sd_framesizes) अणु
		काष्ठा dcmi_framesize outer_sd_fsize;
		/*
		 * If crop is requested and sensor have discrete frame sizes,
		 * select the frame size that is just larger than request
		 */
		__find_outer_frame_size(dcmi, pix, &outer_sd_fsize);
		pix->width = outer_sd_fsize.width;
		pix->height = outer_sd_fsize.height;
	पूर्ण

	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, pix, sd_fmt->mbus_code);
	ret = v4l2_subdev_call(dcmi->source, pad, set_fmt,
			       &pad_cfg, &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	/* Update pix regarding to what sensor can करो */
	v4l2_fill_pix_क्रमmat(pix, &क्रमmat.क्रमmat);

	/* Save resolution that sensor can actually करो */
	sd_fsize.width = pix->width;
	sd_fsize.height = pix->height;

	अगर (करो_crop) अणु
		काष्ठा v4l2_rect c = dcmi->crop;
		काष्ठा v4l2_rect max_rect;

		/*
		 * Adjust crop by making the पूर्णांकersection between
		 * क्रमmat resolution request and crop request
		 */
		max_rect.top = 0;
		max_rect.left = 0;
		max_rect.width = pix->width;
		max_rect.height = pix->height;
		v4l2_rect_map_inside(&c, &max_rect);
		c.top  = clamp_t(s32, c.top, 0, pix->height - c.height);
		c.left = clamp_t(s32, c.left, 0, pix->width - c.width);
		dcmi->crop = c;

		/* Adjust क्रमmat resolution request to crop */
		pix->width = dcmi->crop.width;
		pix->height = dcmi->crop.height;
	पूर्ण

	pix->field = V4L2_FIELD_NONE;
	pix->bytesperline = pix->width * sd_fmt->bpp;
	pix->sizeimage = pix->bytesperline * pix->height;

	अगर (sd_क्रमmat)
		*sd_क्रमmat = sd_fmt;
	अगर (sd_framesize)
		*sd_framesize = sd_fsize;

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_set_fmt(काष्ठा sपंचांग32_dcmi *dcmi, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	स्थिर काष्ठा dcmi_क्रमmat *sd_क्रमmat;
	काष्ठा dcmi_framesize sd_framesize;
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat.क्रमmat;
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	पूर्णांक ret;

	/*
	 * Try क्रमmat, fmt.width/height could have been changed
	 * to match sensor capability or crop request
	 * sd_क्रमmat & sd_framesize will contain what subdev
	 * can करो क्रम this request.
	 */
	ret = dcmi_try_fmt(dcmi, f, &sd_क्रमmat, &sd_framesize);
	अगर (ret)
		वापस ret;

	/* Disable crop अगर JPEG is requested or BT656 bus is selected */
	अगर (pix->pixelक्रमmat == V4L2_PIX_FMT_JPEG &&
	    dcmi->bus_type != V4L2_MBUS_BT656)
		dcmi->करो_crop = false;

	/* pix to mbus क्रमmat */
	v4l2_fill_mbus_क्रमmat(mf, pix,
			      sd_क्रमmat->mbus_code);
	mf->width = sd_framesize.width;
	mf->height = sd_framesize.height;

	ret = dcmi_pipeline_s_fmt(dcmi, शून्य, &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(dcmi->dev, "Sensor format set to 0x%x %ux%u\n",
		mf->code, mf->width, mf->height);
	dev_dbg(dcmi->dev, "Buffer format set to %4.4s %ux%u\n",
		(अक्षर *)&pix->pixelक्रमmat,
		pix->width, pix->height);

	dcmi->fmt = *f;
	dcmi->sd_क्रमmat = sd_क्रमmat;
	dcmi->sd_framesize = sd_framesize;

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = video_drvdata(file);

	अगर (vb2_is_streaming(&dcmi->queue))
		वापस -EBUSY;

	वापस dcmi_set_fmt(dcmi, f);
पूर्ण

अटल पूर्णांक dcmi_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = video_drvdata(file);

	वापस dcmi_try_fmt(dcmi, f, शून्य, शून्य);
पूर्ण

अटल पूर्णांक dcmi_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
				 काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = video_drvdata(file);

	अगर (f->index >= dcmi->num_of_sd_क्रमmats)
		वापस -EINVAL;

	f->pixelक्रमmat = dcmi->sd_क्रमmats[f->index]->fourcc;
	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_get_sensor_क्रमmat(काष्ठा sपंचांग32_dcmi *dcmi,
				  काष्ठा v4l2_pix_क्रमmat *pix)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret;

	ret = v4l2_subdev_call(dcmi->source, pad, get_fmt, शून्य, &fmt);
	अगर (ret)
		वापस ret;

	v4l2_fill_pix_क्रमmat(pix, &fmt.क्रमmat);

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_set_sensor_क्रमmat(काष्ठा sपंचांग32_dcmi *dcmi,
				  काष्ठा v4l2_pix_क्रमmat *pix)
अणु
	स्थिर काष्ठा dcmi_क्रमmat *sd_fmt;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_TRY,
	पूर्ण;
	काष्ठा v4l2_subdev_pad_config pad_cfg;
	पूर्णांक ret;

	sd_fmt = find_क्रमmat_by_fourcc(dcmi, pix->pixelक्रमmat);
	अगर (!sd_fmt) अणु
		अगर (!dcmi->num_of_sd_क्रमmats)
			वापस -ENODATA;

		sd_fmt = dcmi->sd_क्रमmats[dcmi->num_of_sd_क्रमmats - 1];
		pix->pixelक्रमmat = sd_fmt->fourcc;
	पूर्ण

	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, pix, sd_fmt->mbus_code);
	ret = v4l2_subdev_call(dcmi->source, pad, set_fmt,
			       &pad_cfg, &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_get_sensor_bounds(काष्ठा sपंचांग32_dcmi *dcmi,
				  काष्ठा v4l2_rect *r)
अणु
	काष्ठा v4l2_subdev_selection bounds = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = V4L2_SEL_TGT_CROP_BOUNDS,
	पूर्ण;
	अचिन्हित पूर्णांक max_width, max_height, max_pixsize;
	काष्ठा v4l2_pix_क्रमmat pix;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/*
	 * Get sensor bounds first
	 */
	ret = v4l2_subdev_call(dcmi->source, pad, get_selection,
			       शून्य, &bounds);
	अगर (!ret)
		*r = bounds.r;
	अगर (ret != -ENOIOCTLCMD)
		वापस ret;

	/*
	 * If selection is not implemented,
	 * fallback by क्रमागतerating sensor frame sizes
	 * and take the largest one
	 */
	max_width = 0;
	max_height = 0;
	max_pixsize = 0;
	क्रम (i = 0; i < dcmi->num_of_sd_framesizes; i++) अणु
		काष्ठा dcmi_framesize *fsize = &dcmi->sd_framesizes[i];
		अचिन्हित पूर्णांक pixsize = fsize->width * fsize->height;

		अगर (pixsize > max_pixsize) अणु
			max_pixsize = pixsize;
			max_width = fsize->width;
			max_height = fsize->height;
		पूर्ण
	पूर्ण
	अगर (max_pixsize > 0) अणु
		r->top = 0;
		r->left = 0;
		r->width = max_width;
		r->height = max_height;
		वापस 0;
	पूर्ण

	/*
	 * If frame sizes क्रमागतeration is not implemented,
	 * fallback by getting current sensor frame size
	 */
	ret = dcmi_get_sensor_क्रमmat(dcmi, &pix);
	अगर (ret)
		वापस ret;

	r->top = 0;
	r->left = 0;
	r->width = pix.width;
	r->height = pix.height;

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_g_selection(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_selection *s)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = video_drvdata(file);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		s->r = dcmi->sd_bounds;
		वापस 0;
	हाल V4L2_SEL_TGT_CROP:
		अगर (dcmi->करो_crop) अणु
			s->r = dcmi->crop;
		पूर्ण अन्यथा अणु
			s->r.top = 0;
			s->r.left = 0;
			s->r.width = dcmi->fmt.fmt.pix.width;
			s->r.height = dcmi->fmt.fmt.pix.height;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_s_selection(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_selection *s)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = video_drvdata(file);
	काष्ठा v4l2_rect r = s->r;
	काष्ठा v4l2_rect max_rect;
	काष्ठा v4l2_pix_क्रमmat pix;

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	    s->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	/* Reset sensor resolution to max resolution */
	pix.pixelक्रमmat = dcmi->fmt.fmt.pix.pixelक्रमmat;
	pix.width = dcmi->sd_bounds.width;
	pix.height = dcmi->sd_bounds.height;
	dcmi_set_sensor_क्रमmat(dcmi, &pix);

	/*
	 * Make the पूर्णांकersection between
	 * sensor resolution
	 * and crop request
	 */
	max_rect.top = 0;
	max_rect.left = 0;
	max_rect.width = pix.width;
	max_rect.height = pix.height;
	v4l2_rect_map_inside(&r, &max_rect);
	r.top  = clamp_t(s32, r.top, 0, pix.height - r.height);
	r.left = clamp_t(s32, r.left, 0, pix.width - r.width);

	अगर (!(r.top == dcmi->sd_bounds.top &&
	      r.left == dcmi->sd_bounds.left &&
	      r.width == dcmi->sd_bounds.width &&
	      r.height == dcmi->sd_bounds.height)) अणु
		/* Crop अगर request is dअगरferent than sensor resolution */
		dcmi->करो_crop = true;
		dcmi->crop = r;
		dev_dbg(dcmi->dev, "s_selection: crop %ux%u@(%u,%u) from %ux%u\n",
			r.width, r.height, r.left, r.top,
			pix.width, pix.height);
	पूर्ण अन्यथा अणु
		/* Disable crop */
		dcmi->करो_crop = false;
		dev_dbg(dcmi->dev, "s_selection: crop is disabled\n");
	पूर्ण

	s->r = r;
	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_querycap(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, DRV_NAME, माप(cap->driver));
	strscpy(cap->card, "STM32 Camera Memory Interface",
		माप(cap->card));
	strscpy(cap->bus_info, "platform:dcmi", माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_input *i)
अणु
	अगर (i->index != 0)
		वापस -EINVAL;

	i->type = V4L2_INPUT_TYPE_CAMERA;
	strscpy(i->name, "Camera", माप(i->name));
	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	अगर (i > 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = video_drvdata(file);
	स्थिर काष्ठा dcmi_क्रमmat *sd_fmt;
	काष्ठा v4l2_subdev_frame_size_क्रमागत fse = अणु
		.index = fsize->index,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret;

	sd_fmt = find_क्रमmat_by_fourcc(dcmi, fsize->pixel_क्रमmat);
	अगर (!sd_fmt)
		वापस -EINVAL;

	fse.code = sd_fmt->mbus_code;

	ret = v4l2_subdev_call(dcmi->source, pad, क्रमागत_frame_size,
			       शून्य, &fse);
	अगर (ret)
		वापस ret;

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = fse.max_width;
	fsize->discrete.height = fse.max_height;

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_g_parm(काष्ठा file *file, व्योम *priv,
		       काष्ठा v4l2_streamparm *p)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = video_drvdata(file);

	वापस v4l2_g_parm_cap(video_devdata(file), dcmi->source, p);
पूर्ण

अटल पूर्णांक dcmi_s_parm(काष्ठा file *file, व्योम *priv,
		       काष्ठा v4l2_streamparm *p)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = video_drvdata(file);

	वापस v4l2_s_parm_cap(video_devdata(file), dcmi->source, p);
पूर्ण

अटल पूर्णांक dcmi_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = video_drvdata(file);
	स्थिर काष्ठा dcmi_क्रमmat *sd_fmt;
	काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत fie = अणु
		.index = fival->index,
		.width = fival->width,
		.height = fival->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret;

	sd_fmt = find_क्रमmat_by_fourcc(dcmi, fival->pixel_क्रमmat);
	अगर (!sd_fmt)
		वापस -EINVAL;

	fie.code = sd_fmt->mbus_code;

	ret = v4l2_subdev_call(dcmi->source, pad,
			       क्रमागत_frame_पूर्णांकerval, शून्य, &fie);
	अगर (ret)
		वापस ret;

	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = fie.पूर्णांकerval;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sपंचांग32_dcmi_of_match[] = अणु
	अणु .compatible = "st,stm32-dcmi"पूर्ण,
	अणु /* end node */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_dcmi_of_match);

अटल पूर्णांक dcmi_खोलो(काष्ठा file *file)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = dcmi->source;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&dcmi->lock))
		वापस -ERESTARTSYS;

	ret = v4l2_fh_खोलो(file);
	अगर (ret < 0)
		जाओ unlock;

	अगर (!v4l2_fh_is_singular_file(file))
		जाओ fh_rel;

	ret = v4l2_subdev_call(sd, core, s_घातer, 1);
	अगर (ret < 0 && ret != -ENOIOCTLCMD)
		जाओ fh_rel;

	ret = dcmi_set_fmt(dcmi, &dcmi->fmt);
	अगर (ret)
		v4l2_subdev_call(sd, core, s_घातer, 0);
fh_rel:
	अगर (ret)
		v4l2_fh_release(file);
unlock:
	mutex_unlock(&dcmi->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dcmi_release(काष्ठा file *file)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = dcmi->source;
	bool fh_singular;
	पूर्णांक ret;

	mutex_lock(&dcmi->lock);

	fh_singular = v4l2_fh_is_singular_file(file);

	ret = _vb2_fop_release(file, शून्य);

	अगर (fh_singular)
		v4l2_subdev_call(sd, core, s_घातer, 0);

	mutex_unlock(&dcmi->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops dcmi_ioctl_ops = अणु
	.vidioc_querycap		= dcmi_querycap,

	.vidioc_try_fmt_vid_cap		= dcmi_try_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= dcmi_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= dcmi_s_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_cap	= dcmi_क्रमागत_fmt_vid_cap,
	.vidioc_g_selection		= dcmi_g_selection,
	.vidioc_s_selection		= dcmi_s_selection,

	.vidioc_क्रमागत_input		= dcmi_क्रमागत_input,
	.vidioc_g_input			= dcmi_g_input,
	.vidioc_s_input			= dcmi_s_input,

	.vidioc_g_parm			= dcmi_g_parm,
	.vidioc_s_parm			= dcmi_s_parm,

	.vidioc_क्रमागत_framesizes		= dcmi_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals	= dcmi_क्रमागत_frameपूर्णांकervals,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,

	.vidioc_log_status		= v4l2_ctrl_log_status,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations dcmi_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= video_ioctl2,
	.खोलो		= dcmi_खोलो,
	.release	= dcmi_release,
	.poll		= vb2_fop_poll,
	.mmap		= vb2_fop_mmap,
#अगर_अघोषित CONFIG_MMU
	.get_unmapped_area = vb2_fop_get_unmapped_area,
#पूर्ण_अगर
	.पढ़ो		= vb2_fop_पढ़ो,
पूर्ण;

अटल पूर्णांक dcmi_set_शेष_fmt(काष्ठा sपंचांग32_dcmi *dcmi)
अणु
	काष्ठा v4l2_क्रमmat f = अणु
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
		.fmt.pix = अणु
			.width		= CIF_WIDTH,
			.height		= CIF_HEIGHT,
			.field		= V4L2_FIELD_NONE,
			.pixelक्रमmat	= dcmi->sd_क्रमmats[0]->fourcc,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = dcmi_try_fmt(dcmi, &f, शून्य, शून्य);
	अगर (ret)
		वापस ret;
	dcmi->sd_क्रमmat = dcmi->sd_क्रमmats[0];
	dcmi->fmt = f;
	वापस 0;
पूर्ण

/*
 * FIXME: For the समय being we only support subdevices
 * which expose RGB & YUV "parallel form" mbus code (_2X8).
 * Nevertheless, this allows to support serial source subdevices
 * and serial to parallel bridges which conक्रमm to this.
 */
अटल स्थिर काष्ठा dcmi_क्रमmat dcmi_क्रमmats[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_RGB565,
		.mbus_code = MEDIA_BUS_FMT_RGB565_2X8_LE,
		.bpp = 2,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUYV,
		.mbus_code = MEDIA_BUS_FMT_YUYV8_2X8,
		.bpp = 2,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_UYVY,
		.mbus_code = MEDIA_BUS_FMT_UYVY8_2X8,
		.bpp = 2,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_JPEG,
		.mbus_code = MEDIA_BUS_FMT_JPEG_1X8,
		.bpp = 1,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SBGGR8,
		.mbus_code = MEDIA_BUS_FMT_SBGGR8_1X8,
		.bpp = 1,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SGBRG8,
		.mbus_code = MEDIA_BUS_FMT_SGBRG8_1X8,
		.bpp = 1,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SGRBG8,
		.mbus_code = MEDIA_BUS_FMT_SGRBG8_1X8,
		.bpp = 1,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_SRGGB8,
		.mbus_code = MEDIA_BUS_FMT_SRGGB8_1X8,
		.bpp = 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक dcmi_क्रमmats_init(काष्ठा sपंचांग32_dcmi *dcmi)
अणु
	स्थिर काष्ठा dcmi_क्रमmat *sd_fmts[ARRAY_SIZE(dcmi_क्रमmats)];
	अचिन्हित पूर्णांक num_fmts = 0, i, j;
	काष्ठा v4l2_subdev *subdev = dcmi->source;
	काष्ठा v4l2_subdev_mbus_code_क्रमागत mbus_code = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	जबतक (!v4l2_subdev_call(subdev, pad, क्रमागत_mbus_code,
				 शून्य, &mbus_code)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(dcmi_क्रमmats); i++) अणु
			अगर (dcmi_क्रमmats[i].mbus_code != mbus_code.code)
				जारी;

			/* Exclude JPEG अगर BT656 bus is selected */
			अगर (dcmi_क्रमmats[i].fourcc == V4L2_PIX_FMT_JPEG &&
			    dcmi->bus_type == V4L2_MBUS_BT656)
				जारी;

			/* Code supported, have we got this fourcc yet? */
			क्रम (j = 0; j < num_fmts; j++)
				अगर (sd_fmts[j]->fourcc ==
						dcmi_क्रमmats[i].fourcc) अणु
					/* Alपढ़ोy available */
					dev_dbg(dcmi->dev, "Skipping fourcc/code: %4.4s/0x%x\n",
						(अक्षर *)&sd_fmts[j]->fourcc,
						mbus_code.code);
					अवरोध;
				पूर्ण
			अगर (j == num_fmts) अणु
				/* New */
				sd_fmts[num_fmts++] = dcmi_क्रमmats + i;
				dev_dbg(dcmi->dev, "Supported fourcc/code: %4.4s/0x%x\n",
					(अक्षर *)&sd_fmts[num_fmts - 1]->fourcc,
					sd_fmts[num_fmts - 1]->mbus_code);
			पूर्ण
		पूर्ण
		mbus_code.index++;
	पूर्ण

	अगर (!num_fmts)
		वापस -ENXIO;

	dcmi->num_of_sd_क्रमmats = num_fmts;
	dcmi->sd_क्रमmats = devm_kसुस्मृति(dcmi->dev,
					num_fmts, माप(काष्ठा dcmi_क्रमmat *),
					GFP_KERNEL);
	अगर (!dcmi->sd_क्रमmats) अणु
		dev_err(dcmi->dev, "Could not allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	स_नकल(dcmi->sd_क्रमmats, sd_fmts,
	       num_fmts * माप(काष्ठा dcmi_क्रमmat *));
	dcmi->sd_क्रमmat = dcmi->sd_क्रमmats[0];

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_framesizes_init(काष्ठा sपंचांग32_dcmi *dcmi)
अणु
	अचिन्हित पूर्णांक num_fsize = 0;
	काष्ठा v4l2_subdev *subdev = dcmi->source;
	काष्ठा v4l2_subdev_frame_size_क्रमागत fse = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.code = dcmi->sd_क्रमmat->mbus_code,
	पूर्ण;
	अचिन्हित पूर्णांक ret;
	अचिन्हित पूर्णांक i;

	/* Allocate discrete framesizes array */
	जबतक (!v4l2_subdev_call(subdev, pad, क्रमागत_frame_size,
				 शून्य, &fse))
		fse.index++;

	num_fsize = fse.index;
	अगर (!num_fsize)
		वापस 0;

	dcmi->num_of_sd_framesizes = num_fsize;
	dcmi->sd_framesizes = devm_kसुस्मृति(dcmi->dev, num_fsize,
					   माप(काष्ठा dcmi_framesize),
					   GFP_KERNEL);
	अगर (!dcmi->sd_framesizes) अणु
		dev_err(dcmi->dev, "Could not allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	/* Fill array with sensor supported framesizes */
	dev_dbg(dcmi->dev, "Sensor supports %u frame sizes:\n", num_fsize);
	क्रम (i = 0; i < dcmi->num_of_sd_framesizes; i++) अणु
		fse.index = i;
		ret = v4l2_subdev_call(subdev, pad, क्रमागत_frame_size,
				       शून्य, &fse);
		अगर (ret)
			वापस ret;
		dcmi->sd_framesizes[fse.index].width = fse.max_width;
		dcmi->sd_framesizes[fse.index].height = fse.max_height;
		dev_dbg(dcmi->dev, "%ux%u\n", fse.max_width, fse.max_height);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_graph_notअगरy_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = notअगरier_to_dcmi(notअगरier);
	पूर्णांक ret;

	/*
	 * Now that the graph is complete,
	 * we search क्रम the source subdevice
	 * in order to expose it through V4L2 पूर्णांकerface
	 */
	dcmi->source = media_entity_to_v4l2_subdev(dcmi_find_source(dcmi));
	अगर (!dcmi->source) अणु
		dev_err(dcmi->dev, "Source subdevice not found\n");
		वापस -ENODEV;
	पूर्ण

	dcmi->vdev->ctrl_handler = dcmi->source->ctrl_handler;

	ret = dcmi_क्रमmats_init(dcmi);
	अगर (ret) अणु
		dev_err(dcmi->dev, "No supported mediabus format found\n");
		वापस ret;
	पूर्ण

	ret = dcmi_framesizes_init(dcmi);
	अगर (ret) अणु
		dev_err(dcmi->dev, "Could not initialize framesizes\n");
		वापस ret;
	पूर्ण

	ret = dcmi_get_sensor_bounds(dcmi, &dcmi->sd_bounds);
	अगर (ret) अणु
		dev_err(dcmi->dev, "Could not get sensor bounds\n");
		वापस ret;
	पूर्ण

	ret = dcmi_set_शेष_fmt(dcmi);
	अगर (ret) अणु
		dev_err(dcmi->dev, "Could not set default format\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dcmi_graph_notअगरy_unbind(काष्ठा v4l2_async_notअगरier *notअगरier,
				     काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = notअगरier_to_dcmi(notअगरier);

	dev_dbg(dcmi->dev, "Removing %s\n", video_device_node_name(dcmi->vdev));

	/* Checks पूर्णांकernally अगर vdev has been init or not */
	video_unरेजिस्टर_device(dcmi->vdev);
पूर्ण

अटल पूर्णांक dcmi_graph_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				   काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = notअगरier_to_dcmi(notअगरier);
	अचिन्हित पूर्णांक ret;
	पूर्णांक src_pad;

	dev_dbg(dcmi->dev, "Subdev \"%s\" bound\n", subdev->name);

	/*
	 * Link this sub-device to DCMI, it could be
	 * a parallel camera sensor or a bridge
	 */
	src_pad = media_entity_get_fwnode_pad(&subdev->entity,
					      subdev->fwnode,
					      MEDIA_PAD_FL_SOURCE);

	ret = media_create_pad_link(&subdev->entity, src_pad,
				    &dcmi->vdev->entity, 0,
				    MEDIA_LNK_FL_IMMUTABLE |
				    MEDIA_LNK_FL_ENABLED);
	अगर (ret)
		dev_err(dcmi->dev, "Failed to create media pad link with subdev \"%s\"\n",
			subdev->name);
	अन्यथा
		dev_dbg(dcmi->dev, "DCMI is now linked to \"%s\"\n",
			subdev->name);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations dcmi_graph_notअगरy_ops = अणु
	.bound = dcmi_graph_notअगरy_bound,
	.unbind = dcmi_graph_notअगरy_unbind,
	.complete = dcmi_graph_notअगरy_complete,
पूर्ण;

अटल पूर्णांक dcmi_graph_init(काष्ठा sपंचांग32_dcmi *dcmi)
अणु
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा device_node *ep;
	पूर्णांक ret;

	ep = of_graph_get_next_endpoपूर्णांक(dcmi->dev->of_node, शून्य);
	अगर (!ep) अणु
		dev_err(dcmi->dev, "Failed to get next endpoint\n");
		वापस -EINVAL;
	पूर्ण

	v4l2_async_notअगरier_init(&dcmi->notअगरier);

	asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
		&dcmi->notअगरier, of_fwnode_handle(ep),
		काष्ठा v4l2_async_subdev);

	of_node_put(ep);

	अगर (IS_ERR(asd)) अणु
		dev_err(dcmi->dev, "Failed to add subdev notifier\n");
		वापस PTR_ERR(asd);
	पूर्ण

	dcmi->notअगरier.ops = &dcmi_graph_notअगरy_ops;

	ret = v4l2_async_notअगरier_रेजिस्टर(&dcmi->v4l2_dev, &dcmi->notअगरier);
	अगर (ret < 0) अणु
		dev_err(dcmi->dev, "Failed to register notifier\n");
		v4l2_async_notअगरier_cleanup(&dcmi->notअगरier);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dcmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match = शून्य;
	काष्ठा v4l2_fwnode_endpoपूर्णांक ep = अणु .bus_type = 0 पूर्ण;
	काष्ठा sपंचांग32_dcmi *dcmi;
	काष्ठा vb2_queue *q;
	काष्ठा dma_chan *chan;
	काष्ठा clk *mclk;
	पूर्णांक irq;
	पूर्णांक ret = 0;

	match = of_match_device(of_match_ptr(sपंचांग32_dcmi_of_match), &pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "Could not find a match in devicetree\n");
		वापस -ENODEV;
	पूर्ण

	dcmi = devm_kzalloc(&pdev->dev, माप(काष्ठा sपंचांग32_dcmi), GFP_KERNEL);
	अगर (!dcmi)
		वापस -ENOMEM;

	dcmi->rstc = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(dcmi->rstc)) अणु
		अगर (PTR_ERR(dcmi->rstc) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Could not get reset control\n");

		वापस PTR_ERR(dcmi->rstc);
	पूर्ण

	/* Get bus अक्षरacteristics from devicetree */
	np = of_graph_get_next_endpoपूर्णांक(np, शून्य);
	अगर (!np) अणु
		dev_err(&pdev->dev, "Could not find the endpoint\n");
		वापस -ENODEV;
	पूर्ण

	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(np), &ep);
	of_node_put(np);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not parse the endpoint\n");
		वापस ret;
	पूर्ण

	अगर (ep.bus_type == V4L2_MBUS_CSI2_DPHY) अणु
		dev_err(&pdev->dev, "CSI bus not supported\n");
		वापस -ENODEV;
	पूर्ण

	अगर (ep.bus_type == V4L2_MBUS_BT656 &&
	    ep.bus.parallel.bus_width != 8) अणु
		dev_err(&pdev->dev, "BT656 bus conflicts with %u bits bus width (8 bits required)\n",
			ep.bus.parallel.bus_width);
		वापस -ENODEV;
	पूर्ण

	dcmi->bus.flags = ep.bus.parallel.flags;
	dcmi->bus.bus_width = ep.bus.parallel.bus_width;
	dcmi->bus.data_shअगरt = ep.bus.parallel.data_shअगरt;
	dcmi->bus_type = ep.bus_type;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq ? irq : -ENXIO;

	dcmi->res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!dcmi->res) अणु
		dev_err(&pdev->dev, "Could not get resource\n");
		वापस -ENODEV;
	पूर्ण

	dcmi->regs = devm_ioremap_resource(&pdev->dev, dcmi->res);
	अगर (IS_ERR(dcmi->regs)) अणु
		dev_err(&pdev->dev, "Could not map registers\n");
		वापस PTR_ERR(dcmi->regs);
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, dcmi_irq_callback,
					dcmi_irq_thपढ़ो, IRQF_ONESHOT,
					dev_name(&pdev->dev), dcmi);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to request irq %d\n", irq);
		वापस ret;
	पूर्ण

	mclk = devm_clk_get(&pdev->dev, "mclk");
	अगर (IS_ERR(mclk)) अणु
		अगर (PTR_ERR(mclk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Unable to get mclk\n");
		वापस PTR_ERR(mclk);
	पूर्ण

	chan = dma_request_chan(&pdev->dev, "tx");
	अगर (IS_ERR(chan)) अणु
		ret = PTR_ERR(chan);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"Failed to request DMA channel: %d\n", ret);
		वापस ret;
	पूर्ण

	spin_lock_init(&dcmi->irqlock);
	mutex_init(&dcmi->lock);
	mutex_init(&dcmi->dma_lock);
	init_completion(&dcmi->complete);
	INIT_LIST_HEAD(&dcmi->buffers);

	dcmi->dev = &pdev->dev;
	dcmi->mclk = mclk;
	dcmi->state = STOPPED;
	dcmi->dma_chan = chan;

	q = &dcmi->queue;

	dcmi->v4l2_dev.mdev = &dcmi->mdev;

	/* Initialize media device */
	strscpy(dcmi->mdev.model, DRV_NAME, माप(dcmi->mdev.model));
	snम_लिखो(dcmi->mdev.bus_info, माप(dcmi->mdev.bus_info),
		 "platform:%s", DRV_NAME);
	dcmi->mdev.dev = &pdev->dev;
	media_device_init(&dcmi->mdev);

	/* Initialize the top-level काष्ठाure */
	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dcmi->v4l2_dev);
	अगर (ret)
		जाओ err_media_device_cleanup;

	dcmi->vdev = video_device_alloc();
	अगर (!dcmi->vdev) अणु
		ret = -ENOMEM;
		जाओ err_device_unरेजिस्टर;
	पूर्ण

	/* Video node */
	dcmi->vdev->fops = &dcmi_fops;
	dcmi->vdev->v4l2_dev = &dcmi->v4l2_dev;
	dcmi->vdev->queue = &dcmi->queue;
	strscpy(dcmi->vdev->name, KBUILD_MODNAME, माप(dcmi->vdev->name));
	dcmi->vdev->release = video_device_release;
	dcmi->vdev->ioctl_ops = &dcmi_ioctl_ops;
	dcmi->vdev->lock = &dcmi->lock;
	dcmi->vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
				  V4L2_CAP_READWRITE;
	video_set_drvdata(dcmi->vdev, dcmi);

	/* Media entity pads */
	dcmi->vid_cap_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&dcmi->vdev->entity,
				     1, &dcmi->vid_cap_pad);
	अगर (ret) अणु
		dev_err(dcmi->dev, "Failed to init media entity pad\n");
		जाओ err_device_release;
	पूर्ण
	dcmi->vdev->entity.flags |= MEDIA_ENT_FL_DEFAULT;

	ret = video_रेजिस्टर_device(dcmi->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		dev_err(dcmi->dev, "Failed to register video device\n");
		जाओ err_media_entity_cleanup;
	पूर्ण

	dev_dbg(dcmi->dev, "Device registered as %s\n",
		video_device_node_name(dcmi->vdev));

	/* Buffer queue */
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_READ | VB2_DMABUF;
	q->lock = &dcmi->lock;
	q->drv_priv = dcmi;
	q->buf_काष्ठा_size = माप(काष्ठा dcmi_buf);
	q->ops = &dcmi_video_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed = 2;
	q->dev = &pdev->dev;

	ret = vb2_queue_init(q);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to initialize vb2 queue\n");
		जाओ err_media_entity_cleanup;
	पूर्ण

	ret = dcmi_graph_init(dcmi);
	अगर (ret < 0)
		जाओ err_media_entity_cleanup;

	/* Reset device */
	ret = reset_control_निश्चित(dcmi->rstc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to assert the reset line\n");
		जाओ err_cleanup;
	पूर्ण

	usleep_range(3000, 5000);

	ret = reset_control_deनिश्चित(dcmi->rstc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to deassert the reset line\n");
		जाओ err_cleanup;
	पूर्ण

	dev_info(&pdev->dev, "Probe done\n");

	platक्रमm_set_drvdata(pdev, dcmi);

	pm_runसमय_enable(&pdev->dev);

	वापस 0;

err_cleanup:
	v4l2_async_notअगरier_cleanup(&dcmi->notअगरier);
err_media_entity_cleanup:
	media_entity_cleanup(&dcmi->vdev->entity);
err_device_release:
	video_device_release(dcmi->vdev);
err_device_unरेजिस्टर:
	v4l2_device_unरेजिस्टर(&dcmi->v4l2_dev);
err_media_device_cleanup:
	media_device_cleanup(&dcmi->mdev);
	dma_release_channel(dcmi->dma_chan);

	वापस ret;
पूर्ण

अटल पूर्णांक dcmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);

	v4l2_async_notअगरier_unरेजिस्टर(&dcmi->notअगरier);
	v4l2_async_notअगरier_cleanup(&dcmi->notअगरier);
	media_entity_cleanup(&dcmi->vdev->entity);
	v4l2_device_unरेजिस्टर(&dcmi->v4l2_dev);
	media_device_cleanup(&dcmi->mdev);

	dma_release_channel(dcmi->dma_chan);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक dcmi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = dev_get_drvdata(dev);

	clk_disable_unprepare(dcmi->mclk);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक dcmi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_dcmi *dcmi = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(dcmi->mclk);
	अगर (ret)
		dev_err(dev, "%s: Failed to prepare_enable clock\n", __func__);

	वापस ret;
पूर्ण

अटल __maybe_unused पूर्णांक dcmi_suspend(काष्ठा device *dev)
अणु
	/* disable घड़ी */
	pm_runसमय_क्रमce_suspend(dev);

	/* change pinctrl state */
	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक dcmi_resume(काष्ठा device *dev)
अणु
	/* restore pinctl शेष state */
	pinctrl_pm_select_शेष_state(dev);

	/* घड़ी enable */
	pm_runसमय_क्रमce_resume(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dcmi_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dcmi_suspend, dcmi_resume)
	SET_RUNTIME_PM_OPS(dcmi_runसमय_suspend,
			   dcmi_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sपंचांग32_dcmi_driver = अणु
	.probe		= dcmi_probe,
	.हटाओ		= dcmi_हटाओ,
	.driver		= अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(sपंचांग32_dcmi_of_match),
		.pm = &dcmi_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sपंचांग32_dcmi_driver);

MODULE_AUTHOR("Yannick Fertre <yannick.fertre@st.com>");
MODULE_AUTHOR("Hugues Fruchet <hugues.fruchet@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 Digital Camera Memory Interface driver");
MODULE_LICENSE("GPL");
