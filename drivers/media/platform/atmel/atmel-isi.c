<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011 Aपंचांगel Corporation
 * Josh Wu, <josh.wu@aपंचांगel.com>
 *
 * Based on previous work by Lars Haring, <lars.haring@aपंचांगel.com>
 * and Sedji Gaouaou
 * Based on the bttv driver क्रम Bt848 with respective copyright holders
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/v4l2-image-sizes.h>

#समावेश "atmel-isi.h"

#घोषणा MAX_SUPPORT_WIDTH		2048U
#घोषणा MAX_SUPPORT_HEIGHT		2048U
#घोषणा MIN_FRAME_RATE			15
#घोषणा FRAME_INTERVAL_MILLI_SEC	(1000 / MIN_FRAME_RATE)

/* Frame buffer descriptor */
काष्ठा fbd अणु
	/* Physical address of the frame buffer */
	u32 fb_address;
	/* DMA Control Register(only in HISI2) */
	u32 dma_ctrl;
	/* Physical address of the next fbd */
	u32 next_fbd_address;
पूर्ण;

अटल व्योम set_dma_ctrl(काष्ठा fbd *fb_desc, u32 ctrl)
अणु
	fb_desc->dma_ctrl = ctrl;
पूर्ण

काष्ठा isi_dma_desc अणु
	काष्ठा list_head list;
	काष्ठा fbd *p_fbd;
	dma_addr_t fbd_phys;
पूर्ण;

/* Frame buffer data */
काष्ठा frame_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा isi_dma_desc *p_dma_desc;
	काष्ठा list_head list;
पूर्ण;

काष्ठा isi_graph_entity अणु
	काष्ठा device_node *node;

	काष्ठा v4l2_subdev *subdev;
पूर्ण;

/*
 * काष्ठा isi_क्रमmat - ISI media bus क्रमmat inक्रमmation
 * @fourcc:		Fourcc code क्रम this क्रमmat
 * @mbus_code:		V4L2 media bus क्रमmat code.
 * @bpp:		Bytes per pixel (when stored in memory)
 * @swap:		Byte swap configuration value
 * @support:		Indicates क्रमmat supported by subdev
 * @skip:		Skip duplicate क्रमmat supported by subdev
 */
काष्ठा isi_क्रमmat अणु
	u32	fourcc;
	u32	mbus_code;
	u8	bpp;
	u32	swap;
पूर्ण;


काष्ठा aपंचांगel_isi अणु
	/* Protects the access of variables shared with the ISR */
	spinlock_t			irqlock;
	काष्ठा device			*dev;
	व्योम __iomem			*regs;

	पूर्णांक				sequence;

	/* Allocate descriptors क्रम dma buffer use */
	काष्ठा fbd			*p_fb_descriptors;
	dma_addr_t			fb_descriptors_phys;
	काष्ठा				list_head dma_desc_head;
	काष्ठा isi_dma_desc		dma_desc[VIDEO_MAX_FRAME];
	bool				enable_preview_path;

	काष्ठा completion		complete;
	/* ISI peripheral घड़ी */
	काष्ठा clk			*pclk;
	अचिन्हित पूर्णांक			irq;

	काष्ठा isi_platक्रमm_data	pdata;
	u16				width_flags;	/* max 12 bits */

	काष्ठा list_head		video_buffer_list;
	काष्ठा frame_buffer		*active;

	काष्ठा v4l2_device		v4l2_dev;
	काष्ठा video_device		*vdev;
	काष्ठा v4l2_async_notअगरier	notअगरier;
	काष्ठा isi_graph_entity		entity;
	काष्ठा v4l2_क्रमmat		fmt;

	स्थिर काष्ठा isi_क्रमmat		**user_क्रमmats;
	अचिन्हित पूर्णांक			num_user_क्रमmats;
	स्थिर काष्ठा isi_क्रमmat		*current_fmt;

	काष्ठा mutex			lock;
	काष्ठा vb2_queue		queue;
पूर्ण;

#घोषणा notअगरier_to_isi(n) container_of(n, काष्ठा aपंचांगel_isi, notअगरier)

अटल व्योम isi_ग_लिखोl(काष्ठा aपंचांगel_isi *isi, u32 reg, u32 val)
अणु
	ग_लिखोl(val, isi->regs + reg);
पूर्ण
अटल u32 isi_पढ़ोl(काष्ठा aपंचांगel_isi *isi, u32 reg)
अणु
	वापस पढ़ोl(isi->regs + reg);
पूर्ण

अटल व्योम configure_geometry(काष्ठा aपंचांगel_isi *isi)
अणु
	u32 cfg2, psize;
	u32 fourcc = isi->current_fmt->fourcc;

	isi->enable_preview_path = fourcc == V4L2_PIX_FMT_RGB565 ||
				   fourcc == V4L2_PIX_FMT_RGB32 ||
				   fourcc == V4L2_PIX_FMT_Y16;

	/* According to sensor's output क्रमmat to set cfg2 */
	cfg2 = isi->current_fmt->swap;

	isi_ग_लिखोl(isi, ISI_CTRL, ISI_CTRL_DIS);
	/* Set width */
	cfg2 |= ((isi->fmt.fmt.pix.width - 1) << ISI_CFG2_IM_HSIZE_OFFSET) &
			ISI_CFG2_IM_HSIZE_MASK;
	/* Set height */
	cfg2 |= ((isi->fmt.fmt.pix.height - 1) << ISI_CFG2_IM_VSIZE_OFFSET)
			& ISI_CFG2_IM_VSIZE_MASK;
	isi_ग_लिखोl(isi, ISI_CFG2, cfg2);

	/* No करोwn sampling, preview size equal to sensor output size */
	psize = ((isi->fmt.fmt.pix.width - 1) << ISI_PSIZE_PREV_HSIZE_OFFSET) &
		ISI_PSIZE_PREV_HSIZE_MASK;
	psize |= ((isi->fmt.fmt.pix.height - 1) << ISI_PSIZE_PREV_VSIZE_OFFSET) &
		ISI_PSIZE_PREV_VSIZE_MASK;
	isi_ग_लिखोl(isi, ISI_PSIZE, psize);
	isi_ग_लिखोl(isi, ISI_PDECF, ISI_PDECF_NO_SAMPLING);
पूर्ण

अटल irqवापस_t aपंचांगel_isi_handle_streaming(काष्ठा aपंचांगel_isi *isi)
अणु
	अगर (isi->active) अणु
		काष्ठा vb2_v4l2_buffer *vbuf = &isi->active->vb;
		काष्ठा frame_buffer *buf = isi->active;

		list_del_init(&buf->list);
		vbuf->vb2_buf.बारtamp = kसमय_get_ns();
		vbuf->sequence = isi->sequence++;
		vbuf->field = V4L2_FIELD_NONE;
		vb2_buffer_करोne(&vbuf->vb2_buf, VB2_BUF_STATE_DONE);
	पूर्ण

	अगर (list_empty(&isi->video_buffer_list)) अणु
		isi->active = शून्य;
	पूर्ण अन्यथा अणु
		/* start next dma frame. */
		isi->active = list_entry(isi->video_buffer_list.next,
					काष्ठा frame_buffer, list);
		अगर (!isi->enable_preview_path) अणु
			isi_ग_लिखोl(isi, ISI_DMA_C_DSCR,
				(u32)isi->active->p_dma_desc->fbd_phys);
			isi_ग_लिखोl(isi, ISI_DMA_C_CTRL,
				ISI_DMA_CTRL_FETCH | ISI_DMA_CTRL_DONE);
			isi_ग_लिखोl(isi, ISI_DMA_CHER, ISI_DMA_CHSR_C_CH);
		पूर्ण अन्यथा अणु
			isi_ग_लिखोl(isi, ISI_DMA_P_DSCR,
				(u32)isi->active->p_dma_desc->fbd_phys);
			isi_ग_लिखोl(isi, ISI_DMA_P_CTRL,
				ISI_DMA_CTRL_FETCH | ISI_DMA_CTRL_DONE);
			isi_ग_लिखोl(isi, ISI_DMA_CHER, ISI_DMA_CHSR_P_CH);
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/* ISI पूर्णांकerrupt service routine */
अटल irqवापस_t isi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा aपंचांगel_isi *isi = dev_id;
	u32 status, mask, pending;
	irqवापस_t ret = IRQ_NONE;

	spin_lock(&isi->irqlock);

	status = isi_पढ़ोl(isi, ISI_STATUS);
	mask = isi_पढ़ोl(isi, ISI_INTMASK);
	pending = status & mask;

	अगर (pending & ISI_CTRL_SRST) अणु
		complete(&isi->complete);
		isi_ग_लिखोl(isi, ISI_INTDIS, ISI_CTRL_SRST);
		ret = IRQ_HANDLED;
	पूर्ण अन्यथा अगर (pending & ISI_CTRL_DIS) अणु
		complete(&isi->complete);
		isi_ग_लिखोl(isi, ISI_INTDIS, ISI_CTRL_DIS);
		ret = IRQ_HANDLED;
	पूर्ण अन्यथा अणु
		अगर (likely(pending & ISI_SR_CXFR_DONE) ||
				likely(pending & ISI_SR_PXFR_DONE))
			ret = aपंचांगel_isi_handle_streaming(isi);
	पूर्ण

	spin_unlock(&isi->irqlock);
	वापस ret;
पूर्ण

#घोषणा	WAIT_ISI_RESET		1
#घोषणा	WAIT_ISI_DISABLE	0
अटल पूर्णांक aपंचांगel_isi_रुको_status(काष्ठा aपंचांगel_isi *isi, पूर्णांक रुको_reset)
अणु
	अचिन्हित दीर्घ समयout;
	/*
	 * The reset or disable will only succeed अगर we have a
	 * pixel घड़ी from the camera.
	 */
	init_completion(&isi->complete);

	अगर (रुको_reset) अणु
		isi_ग_लिखोl(isi, ISI_INTEN, ISI_CTRL_SRST);
		isi_ग_लिखोl(isi, ISI_CTRL, ISI_CTRL_SRST);
	पूर्ण अन्यथा अणु
		isi_ग_लिखोl(isi, ISI_INTEN, ISI_CTRL_DIS);
		isi_ग_लिखोl(isi, ISI_CTRL, ISI_CTRL_DIS);
	पूर्ण

	समयout = रुको_क्रम_completion_समयout(&isi->complete,
			msecs_to_jअगरfies(500));
	अगर (समयout == 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------
	Videobuf operations
   ------------------------------------------------------------------*/
अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
				अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
				अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा aपंचांगel_isi *isi = vb2_get_drv_priv(vq);
	अचिन्हित दीर्घ size;

	size = isi->fmt.fmt.pix.sizeimage;

	/* Make sure the image size is large enough. */
	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;

	isi->active = शून्य;

	dev_dbg(isi->dev, "%s, count=%d, size=%ld\n", __func__,
		*nbuffers, size);

	वापस 0;
पूर्ण

अटल पूर्णांक buffer_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा frame_buffer *buf = container_of(vbuf, काष्ठा frame_buffer, vb);

	buf->p_dma_desc = शून्य;
	INIT_LIST_HEAD(&buf->list);

	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा frame_buffer *buf = container_of(vbuf, काष्ठा frame_buffer, vb);
	काष्ठा aपंचांगel_isi *isi = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ size;
	काष्ठा isi_dma_desc *desc;

	size = isi->fmt.fmt.pix.sizeimage;

	अगर (vb2_plane_size(vb, 0) < size) अणु
		dev_err(isi->dev, "%s data will not fit into plane (%lu < %lu)\n",
				__func__, vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, size);

	अगर (!buf->p_dma_desc) अणु
		अगर (list_empty(&isi->dma_desc_head)) अणु
			dev_err(isi->dev, "Not enough dma descriptors.\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			/* Get an available descriptor */
			desc = list_entry(isi->dma_desc_head.next,
						काष्ठा isi_dma_desc, list);
			/* Delete the descriptor since now it is used */
			list_del_init(&desc->list);

			/* Initialize the dma descriptor */
			desc->p_fbd->fb_address =
					vb2_dma_contig_plane_dma_addr(vb, 0);
			desc->p_fbd->next_fbd_address = 0;
			set_dma_ctrl(desc->p_fbd, ISI_DMA_CTRL_WB);

			buf->p_dma_desc = desc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम buffer_cleanup(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा aपंचांगel_isi *isi = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा frame_buffer *buf = container_of(vbuf, काष्ठा frame_buffer, vb);

	/* This descriptor is available now and we add to head list */
	अगर (buf->p_dma_desc)
		list_add(&buf->p_dma_desc->list, &isi->dma_desc_head);
पूर्ण

अटल व्योम start_dma(काष्ठा aपंचांगel_isi *isi, काष्ठा frame_buffer *buffer)
अणु
	u32 ctrl, cfg1;

	cfg1 = isi_पढ़ोl(isi, ISI_CFG1);
	/* Enable irq: cxfr क्रम the codec path, pxfr क्रम the preview path */
	isi_ग_लिखोl(isi, ISI_INTEN,
			ISI_SR_CXFR_DONE | ISI_SR_PXFR_DONE);

	/* Check अगर alपढ़ोy in a frame */
	अगर (!isi->enable_preview_path) अणु
		अगर (isi_पढ़ोl(isi, ISI_STATUS) & ISI_CTRL_CDC) अणु
			dev_err(isi->dev, "Already in frame handling.\n");
			वापस;
		पूर्ण

		isi_ग_लिखोl(isi, ISI_DMA_C_DSCR,
				(u32)buffer->p_dma_desc->fbd_phys);
		isi_ग_लिखोl(isi, ISI_DMA_C_CTRL,
				ISI_DMA_CTRL_FETCH | ISI_DMA_CTRL_DONE);
		isi_ग_लिखोl(isi, ISI_DMA_CHER, ISI_DMA_CHSR_C_CH);
	पूर्ण अन्यथा अणु
		isi_ग_लिखोl(isi, ISI_DMA_P_DSCR,
				(u32)buffer->p_dma_desc->fbd_phys);
		isi_ग_लिखोl(isi, ISI_DMA_P_CTRL,
				ISI_DMA_CTRL_FETCH | ISI_DMA_CTRL_DONE);
		isi_ग_लिखोl(isi, ISI_DMA_CHER, ISI_DMA_CHSR_P_CH);
	पूर्ण

	cfg1 &= ~ISI_CFG1_FRATE_DIV_MASK;
	/* Enable linked list */
	cfg1 |= isi->pdata.frate | ISI_CFG1_DISCR;

	/* Enable ISI */
	ctrl = ISI_CTRL_EN;

	अगर (!isi->enable_preview_path)
		ctrl |= ISI_CTRL_CDC;

	isi_ग_लिखोl(isi, ISI_CTRL, ctrl);
	isi_ग_लिखोl(isi, ISI_CFG1, cfg1);
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा aपंचांगel_isi *isi = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा frame_buffer *buf = container_of(vbuf, काष्ठा frame_buffer, vb);
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&isi->irqlock, flags);
	list_add_tail(&buf->list, &isi->video_buffer_list);

	अगर (!isi->active) अणु
		isi->active = buf;
		अगर (vb2_is_streaming(vb->vb2_queue))
			start_dma(isi, buf);
	पूर्ण
	spin_unlock_irqrestore(&isi->irqlock, flags);
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा aपंचांगel_isi *isi = vb2_get_drv_priv(vq);
	काष्ठा frame_buffer *buf, *node;
	पूर्णांक ret;

	pm_runसमय_get_sync(isi->dev);

	/* Enable stream on the sub device */
	ret = v4l2_subdev_call(isi->entity.subdev, video, s_stream, 1);
	अगर (ret && ret != -ENOIOCTLCMD) अणु
		dev_err(isi->dev, "stream on failed in subdev\n");
		जाओ err_start_stream;
	पूर्ण

	/* Reset ISI */
	ret = aपंचांगel_isi_रुको_status(isi, WAIT_ISI_RESET);
	अगर (ret < 0) अणु
		dev_err(isi->dev, "Reset ISI timed out\n");
		जाओ err_reset;
	पूर्ण
	/* Disable all पूर्णांकerrupts */
	isi_ग_लिखोl(isi, ISI_INTDIS, (u32)~0UL);

	isi->sequence = 0;
	configure_geometry(isi);

	spin_lock_irq(&isi->irqlock);
	/* Clear any pending पूर्णांकerrupt */
	isi_पढ़ोl(isi, ISI_STATUS);

	start_dma(isi, isi->active);
	spin_unlock_irq(&isi->irqlock);

	वापस 0;

err_reset:
	v4l2_subdev_call(isi->entity.subdev, video, s_stream, 0);

err_start_stream:
	pm_runसमय_put(isi->dev);

	spin_lock_irq(&isi->irqlock);
	isi->active = शून्य;
	/* Release all active buffers */
	list_क्रम_each_entry_safe(buf, node, &isi->video_buffer_list, list) अणु
		list_del_init(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
	पूर्ण
	spin_unlock_irq(&isi->irqlock);

	वापस ret;
पूर्ण

/* पात streaming and रुको क्रम last buffer */
अटल व्योम stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा aपंचांगel_isi *isi = vb2_get_drv_priv(vq);
	काष्ठा frame_buffer *buf, *node;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ समयout;

	/* Disable stream on the sub device */
	ret = v4l2_subdev_call(isi->entity.subdev, video, s_stream, 0);
	अगर (ret && ret != -ENOIOCTLCMD)
		dev_err(isi->dev, "stream off failed in subdev\n");

	spin_lock_irq(&isi->irqlock);
	isi->active = शून्य;
	/* Release all active buffers */
	list_क्रम_each_entry_safe(buf, node, &isi->video_buffer_list, list) अणु
		list_del_init(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irq(&isi->irqlock);

	अगर (!isi->enable_preview_path) अणु
		समयout = jअगरfies + (FRAME_INTERVAL_MILLI_SEC * HZ) / 1000;
		/* Wait until the end of the current frame. */
		जबतक ((isi_पढ़ोl(isi, ISI_STATUS) & ISI_CTRL_CDC) &&
				समय_beक्रमe(jअगरfies, समयout))
			msleep(1);

		अगर (समय_after(jअगरfies, समयout))
			dev_err(isi->dev,
				"Timeout waiting for finishing codec request\n");
	पूर्ण

	/* Disable पूर्णांकerrupts */
	isi_ग_लिखोl(isi, ISI_INTDIS,
			ISI_SR_CXFR_DONE | ISI_SR_PXFR_DONE);

	/* Disable ISI and रुको क्रम it is करोne */
	ret = aपंचांगel_isi_रुको_status(isi, WAIT_ISI_DISABLE);
	अगर (ret < 0)
		dev_err(isi->dev, "Disable ISI timed out\n");

	pm_runसमय_put(isi->dev);
पूर्ण

अटल स्थिर काष्ठा vb2_ops isi_video_qops = अणु
	.queue_setup		= queue_setup,
	.buf_init		= buffer_init,
	.buf_prepare		= buffer_prepare,
	.buf_cleanup		= buffer_cleanup,
	.buf_queue		= buffer_queue,
	.start_streaming	= start_streaming,
	.stop_streaming		= stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक isi_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा aपंचांगel_isi *isi = video_drvdata(file);

	*fmt = isi->fmt;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा isi_क्रमmat *find_क्रमmat_by_fourcc(काष्ठा aपंचांगel_isi *isi,
						      अचिन्हित पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक num_क्रमmats = isi->num_user_क्रमmats;
	स्थिर काष्ठा isi_क्रमmat *fmt;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_क्रमmats; i++) अणु
		fmt = isi->user_क्रमmats[i];
		अगर (fmt->fourcc == fourcc)
			वापस fmt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम isi_try_fse(काष्ठा aपंचांगel_isi *isi, स्थिर काष्ठा isi_क्रमmat *isi_fmt,
			काष्ठा v4l2_subdev_pad_config *pad_cfg)
अणु
	पूर्णांक ret;
	काष्ठा v4l2_subdev_frame_size_क्रमागत fse = अणु
		.code = isi_fmt->mbus_code,
		.which = V4L2_SUBDEV_FORMAT_TRY,
	पूर्ण;

	ret = v4l2_subdev_call(isi->entity.subdev, pad, क्रमागत_frame_size,
			       pad_cfg, &fse);
	/*
	 * Attempt to obtain क्रमmat size from subdev. If not available,
	 * just use the maximum ISI can receive.
	 */
	अगर (ret) अणु
		pad_cfg->try_crop.width = MAX_SUPPORT_WIDTH;
		pad_cfg->try_crop.height = MAX_SUPPORT_HEIGHT;
	पूर्ण अन्यथा अणु
		pad_cfg->try_crop.width = fse.max_width;
		pad_cfg->try_crop.height = fse.max_height;
	पूर्ण
पूर्ण

अटल पूर्णांक isi_try_fmt(काष्ठा aपंचांगel_isi *isi, काष्ठा v4l2_क्रमmat *f,
		       स्थिर काष्ठा isi_क्रमmat **current_fmt)
अणु
	स्थिर काष्ठा isi_क्रमmat *isi_fmt;
	काष्ठा v4l2_pix_क्रमmat *pixfmt = &f->fmt.pix;
	काष्ठा v4l2_subdev_pad_config pad_cfg = अणुपूर्ण;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_TRY,
	पूर्ण;
	पूर्णांक ret;

	isi_fmt = find_क्रमmat_by_fourcc(isi, pixfmt->pixelक्रमmat);
	अगर (!isi_fmt) अणु
		isi_fmt = isi->user_क्रमmats[isi->num_user_क्रमmats - 1];
		pixfmt->pixelक्रमmat = isi_fmt->fourcc;
	पूर्ण

	/* Limit to Aपंचांगel ISI hardware capabilities */
	pixfmt->width = clamp(pixfmt->width, 0U, MAX_SUPPORT_WIDTH);
	pixfmt->height = clamp(pixfmt->height, 0U, MAX_SUPPORT_HEIGHT);

	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, pixfmt, isi_fmt->mbus_code);

	isi_try_fse(isi, isi_fmt, &pad_cfg);

	ret = v4l2_subdev_call(isi->entity.subdev, pad, set_fmt,
			       &pad_cfg, &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	v4l2_fill_pix_क्रमmat(pixfmt, &क्रमmat.क्रमmat);

	pixfmt->field = V4L2_FIELD_NONE;
	pixfmt->bytesperline = pixfmt->width * isi_fmt->bpp;
	pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height;

	अगर (current_fmt)
		*current_fmt = isi_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक isi_set_fmt(काष्ठा aपंचांगel_isi *isi, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	स्थिर काष्ठा isi_क्रमmat *current_fmt;
	पूर्णांक ret;

	ret = isi_try_fmt(isi, f, &current_fmt);
	अगर (ret)
		वापस ret;

	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, &f->fmt.pix,
			      current_fmt->mbus_code);
	ret = v4l2_subdev_call(isi->entity.subdev, pad,
			       set_fmt, शून्य, &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	isi->fmt = *f;
	isi->current_fmt = current_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक isi_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा aपंचांगel_isi *isi = video_drvdata(file);

	अगर (vb2_is_streaming(&isi->queue))
		वापस -EBUSY;

	वापस isi_set_fmt(isi, f);
पूर्ण

अटल पूर्णांक isi_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा aपंचांगel_isi *isi = video_drvdata(file);

	वापस isi_try_fmt(isi, f, शून्य);
पूर्ण

अटल पूर्णांक isi_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
				काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा aपंचांगel_isi *isi = video_drvdata(file);

	अगर (f->index >= isi->num_user_क्रमmats)
		वापस -EINVAL;

	f->pixelक्रमmat = isi->user_क्रमmats[f->index]->fourcc;
	वापस 0;
पूर्ण

अटल पूर्णांक isi_querycap(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, "atmel-isi", माप(cap->driver));
	strscpy(cap->card, "Atmel Image Sensor Interface", माप(cap->card));
	strscpy(cap->bus_info, "platform:isi", माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक isi_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_input *i)
अणु
	अगर (i->index != 0)
		वापस -EINVAL;

	i->type = V4L2_INPUT_TYPE_CAMERA;
	strscpy(i->name, "Camera", माप(i->name));
	वापस 0;
पूर्ण

अटल पूर्णांक isi_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक isi_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	अगर (i > 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक isi_g_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा aपंचांगel_isi *isi = video_drvdata(file);

	वापस v4l2_g_parm_cap(video_devdata(file), isi->entity.subdev, a);
पूर्ण

अटल पूर्णांक isi_s_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा aपंचांगel_isi *isi = video_drvdata(file);

	वापस v4l2_s_parm_cap(video_devdata(file), isi->entity.subdev, a);
पूर्ण

अटल पूर्णांक isi_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा aपंचांगel_isi *isi = video_drvdata(file);
	स्थिर काष्ठा isi_क्रमmat *isi_fmt;
	काष्ठा v4l2_subdev_frame_size_क्रमागत fse = अणु
		.index = fsize->index,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret;

	isi_fmt = find_क्रमmat_by_fourcc(isi, fsize->pixel_क्रमmat);
	अगर (!isi_fmt)
		वापस -EINVAL;

	fse.code = isi_fmt->mbus_code;

	ret = v4l2_subdev_call(isi->entity.subdev, pad, क्रमागत_frame_size,
			       शून्य, &fse);
	अगर (ret)
		वापस ret;

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = fse.max_width;
	fsize->discrete.height = fse.max_height;

	वापस 0;
पूर्ण

अटल पूर्णांक isi_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा aपंचांगel_isi *isi = video_drvdata(file);
	स्थिर काष्ठा isi_क्रमmat *isi_fmt;
	काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत fie = अणु
		.index = fival->index,
		.width = fival->width,
		.height = fival->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret;

	isi_fmt = find_क्रमmat_by_fourcc(isi, fival->pixel_क्रमmat);
	अगर (!isi_fmt)
		वापस -EINVAL;

	fie.code = isi_fmt->mbus_code;

	ret = v4l2_subdev_call(isi->entity.subdev, pad,
			       क्रमागत_frame_पूर्णांकerval, शून्य, &fie);
	अगर (ret)
		वापस ret;

	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = fie.पूर्णांकerval;

	वापस 0;
पूर्ण

अटल व्योम isi_camera_set_bus_param(काष्ठा aपंचांगel_isi *isi)
अणु
	u32 cfg1 = 0;

	/* set bus param क्रम ISI */
	अगर (isi->pdata.hsync_act_low)
		cfg1 |= ISI_CFG1_HSYNC_POL_ACTIVE_LOW;
	अगर (isi->pdata.vsync_act_low)
		cfg1 |= ISI_CFG1_VSYNC_POL_ACTIVE_LOW;
	अगर (isi->pdata.pclk_act_falling)
		cfg1 |= ISI_CFG1_PIXCLK_POL_ACTIVE_FALLING;
	अगर (isi->pdata.has_emb_sync)
		cfg1 |= ISI_CFG1_EMB_SYNC;
	अगर (isi->pdata.full_mode)
		cfg1 |= ISI_CFG1_FULL_MODE;

	cfg1 |= ISI_CFG1_THMASK_BEATS_16;

	/* Enable PM and peripheral घड़ी beक्रमe operate isi रेजिस्टरs */
	pm_runसमय_get_sync(isi->dev);

	isi_ग_लिखोl(isi, ISI_CTRL, ISI_CTRL_DIS);
	isi_ग_लिखोl(isi, ISI_CFG1, cfg1);

	pm_runसमय_put(isi->dev);
पूर्ण

/* -----------------------------------------------------------------------*/
अटल पूर्णांक aपंचांगel_isi_parse_dt(काष्ठा aपंचांगel_isi *isi,
			काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा v4l2_fwnode_endpoपूर्णांक ep = अणु .bus_type = 0 पूर्ण;
	पूर्णांक err;

	/* Default settings क्रम ISI */
	isi->pdata.full_mode = 1;
	isi->pdata.frate = ISI_CFG1_FRATE_CAPTURE_ALL;

	np = of_graph_get_next_endpoपूर्णांक(np, शून्य);
	अगर (!np) अणु
		dev_err(&pdev->dev, "Could not find the endpoint\n");
		वापस -EINVAL;
	पूर्ण

	err = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(np), &ep);
	of_node_put(np);
	अगर (err) अणु
		dev_err(&pdev->dev, "Could not parse the endpoint\n");
		वापस err;
	पूर्ण

	चयन (ep.bus.parallel.bus_width) अणु
	हाल 8:
		isi->pdata.data_width_flags = ISI_DATAWIDTH_8;
		अवरोध;
	हाल 10:
		isi->pdata.data_width_flags =
				ISI_DATAWIDTH_8 | ISI_DATAWIDTH_10;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unsupported bus width: %d\n",
				ep.bus.parallel.bus_width);
		वापस -EINVAL;
	पूर्ण

	अगर (ep.bus.parallel.flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
		isi->pdata.hsync_act_low = true;
	अगर (ep.bus.parallel.flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
		isi->pdata.vsync_act_low = true;
	अगर (ep.bus.parallel.flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
		isi->pdata.pclk_act_falling = true;

	अगर (ep.bus_type == V4L2_MBUS_BT656)
		isi->pdata.has_emb_sync = true;

	वापस 0;
पूर्ण

अटल पूर्णांक isi_खोलो(काष्ठा file *file)
अणु
	काष्ठा aपंचांगel_isi *isi = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = isi->entity.subdev;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&isi->lock))
		वापस -ERESTARTSYS;

	ret = v4l2_fh_खोलो(file);
	अगर (ret < 0)
		जाओ unlock;

	अगर (!v4l2_fh_is_singular_file(file))
		जाओ fh_rel;

	ret = v4l2_subdev_call(sd, core, s_घातer, 1);
	अगर (ret < 0 && ret != -ENOIOCTLCMD)
		जाओ fh_rel;

	ret = isi_set_fmt(isi, &isi->fmt);
	अगर (ret)
		v4l2_subdev_call(sd, core, s_घातer, 0);
fh_rel:
	अगर (ret)
		v4l2_fh_release(file);
unlock:
	mutex_unlock(&isi->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक isi_release(काष्ठा file *file)
अणु
	काष्ठा aपंचांगel_isi *isi = video_drvdata(file);
	काष्ठा v4l2_subdev *sd = isi->entity.subdev;
	bool fh_singular;
	पूर्णांक ret;

	mutex_lock(&isi->lock);

	fh_singular = v4l2_fh_is_singular_file(file);

	ret = _vb2_fop_release(file, शून्य);

	अगर (fh_singular)
		v4l2_subdev_call(sd, core, s_घातer, 0);

	mutex_unlock(&isi->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops isi_ioctl_ops = अणु
	.vidioc_querycap		= isi_querycap,

	.vidioc_try_fmt_vid_cap		= isi_try_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= isi_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= isi_s_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_cap	= isi_क्रमागत_fmt_vid_cap,

	.vidioc_क्रमागत_input		= isi_क्रमागत_input,
	.vidioc_g_input			= isi_g_input,
	.vidioc_s_input			= isi_s_input,

	.vidioc_g_parm			= isi_g_parm,
	.vidioc_s_parm			= isi_s_parm,
	.vidioc_क्रमागत_framesizes		= isi_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals	= isi_क्रमागत_frameपूर्णांकervals,

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

अटल स्थिर काष्ठा v4l2_file_operations isi_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= video_ioctl2,
	.खोलो		= isi_खोलो,
	.release	= isi_release,
	.poll		= vb2_fop_poll,
	.mmap		= vb2_fop_mmap,
	.पढ़ो		= vb2_fop_पढ़ो,
पूर्ण;

अटल पूर्णांक isi_set_शेष_fmt(काष्ठा aपंचांगel_isi *isi)
अणु
	काष्ठा v4l2_क्रमmat f = अणु
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
		.fmt.pix = अणु
			.width		= VGA_WIDTH,
			.height		= VGA_HEIGHT,
			.field		= V4L2_FIELD_NONE,
			.pixelक्रमmat	= isi->user_क्रमmats[0]->fourcc,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = isi_try_fmt(isi, &f, शून्य);
	अगर (ret)
		वापस ret;
	isi->current_fmt = isi->user_क्रमmats[0];
	isi->fmt = f;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा isi_क्रमmat isi_क्रमmats[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_YUYV,
		.mbus_code = MEDIA_BUS_FMT_YUYV8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_DEFAULT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUYV,
		.mbus_code = MEDIA_BUS_FMT_YVYU8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_MODE_1,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUYV,
		.mbus_code = MEDIA_BUS_FMT_UYVY8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_MODE_2,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUYV,
		.mbus_code = MEDIA_BUS_FMT_VYUY8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_MODE_3,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_RGB565,
		.mbus_code = MEDIA_BUS_FMT_YUYV8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_MODE_2,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_RGB565,
		.mbus_code = MEDIA_BUS_FMT_YVYU8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_MODE_3,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_RGB565,
		.mbus_code = MEDIA_BUS_FMT_UYVY8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_DEFAULT,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_RGB565,
		.mbus_code = MEDIA_BUS_FMT_VYUY8_2X8,
		.bpp = 2,
		.swap = ISI_CFG2_YCC_SWAP_MODE_1,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_GREY,
		.mbus_code = MEDIA_BUS_FMT_Y10_1X10,
		.bpp = 1,
		.swap = ISI_CFG2_GS_MODE_2_PIXEL | ISI_CFG2_GRAYSCALE,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_Y16,
		.mbus_code = MEDIA_BUS_FMT_Y10_1X10,
		.bpp = 2,
		.swap = ISI_CFG2_GS_MODE_2_PIXEL | ISI_CFG2_GRAYSCALE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक isi_क्रमmats_init(काष्ठा aपंचांगel_isi *isi)
अणु
	स्थिर काष्ठा isi_क्रमmat *isi_fmts[ARRAY_SIZE(isi_क्रमmats)];
	अचिन्हित पूर्णांक num_fmts = 0, i, j;
	काष्ठा v4l2_subdev *subdev = isi->entity.subdev;
	काष्ठा v4l2_subdev_mbus_code_क्रमागत mbus_code = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	जबतक (!v4l2_subdev_call(subdev, pad, क्रमागत_mbus_code,
				 शून्य, &mbus_code)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(isi_क्रमmats); i++) अणु
			अगर (isi_क्रमmats[i].mbus_code != mbus_code.code)
				जारी;

			/* Code supported, have we got this fourcc yet? */
			क्रम (j = 0; j < num_fmts; j++)
				अगर (isi_fmts[j]->fourcc == isi_क्रमmats[i].fourcc)
					/* Alपढ़ोy available */
					अवरोध;
			अगर (j == num_fmts)
				/* new */
				isi_fmts[num_fmts++] = isi_क्रमmats + i;
		पूर्ण
		mbus_code.index++;
	पूर्ण

	अगर (!num_fmts)
		वापस -ENXIO;

	isi->num_user_क्रमmats = num_fmts;
	isi->user_क्रमmats = devm_kसुस्मृति(isi->dev,
					 num_fmts, माप(काष्ठा isi_क्रमmat *),
					 GFP_KERNEL);
	अगर (!isi->user_क्रमmats)
		वापस -ENOMEM;

	स_नकल(isi->user_क्रमmats, isi_fmts,
	       num_fmts * माप(काष्ठा isi_क्रमmat *));
	isi->current_fmt = isi->user_क्रमmats[0];

	वापस 0;
पूर्ण

अटल पूर्णांक isi_graph_notअगरy_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा aपंचांगel_isi *isi = notअगरier_to_isi(notअगरier);
	पूर्णांक ret;

	isi->vdev->ctrl_handler = isi->entity.subdev->ctrl_handler;
	ret = isi_क्रमmats_init(isi);
	अगर (ret) अणु
		dev_err(isi->dev, "No supported mediabus format found\n");
		वापस ret;
	पूर्ण
	isi_camera_set_bus_param(isi);

	ret = isi_set_शेष_fmt(isi);
	अगर (ret) अणु
		dev_err(isi->dev, "Could not set default format\n");
		वापस ret;
	पूर्ण

	ret = video_रेजिस्टर_device(isi->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		dev_err(isi->dev, "Failed to register video device\n");
		वापस ret;
	पूर्ण

	dev_dbg(isi->dev, "Device registered as %s\n",
		video_device_node_name(isi->vdev));
	वापस 0;
पूर्ण

अटल व्योम isi_graph_notअगरy_unbind(काष्ठा v4l2_async_notअगरier *notअगरier,
				     काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा aपंचांगel_isi *isi = notअगरier_to_isi(notअगरier);

	dev_dbg(isi->dev, "Removing %s\n", video_device_node_name(isi->vdev));

	/* Checks पूर्णांकernally अगर vdev have been init or not */
	video_unरेजिस्टर_device(isi->vdev);
पूर्ण

अटल पूर्णांक isi_graph_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				   काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा aपंचांगel_isi *isi = notअगरier_to_isi(notअगरier);

	dev_dbg(isi->dev, "subdev %s bound\n", subdev->name);

	isi->entity.subdev = subdev;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations isi_graph_notअगरy_ops = अणु
	.bound = isi_graph_notअगरy_bound,
	.unbind = isi_graph_notअगरy_unbind,
	.complete = isi_graph_notअगरy_complete,
पूर्ण;

अटल पूर्णांक isi_graph_init(काष्ठा aपंचांगel_isi *isi)
अणु
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा device_node *ep;
	पूर्णांक ret;

	ep = of_graph_get_next_endpoपूर्णांक(isi->dev->of_node, शून्य);
	अगर (!ep)
		वापस -EINVAL;

	v4l2_async_notअगरier_init(&isi->notअगरier);

	asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
						&isi->notअगरier,
						of_fwnode_handle(ep),
						काष्ठा v4l2_async_subdev);
	of_node_put(ep);

	अगर (IS_ERR(asd))
		वापस PTR_ERR(asd);

	isi->notअगरier.ops = &isi_graph_notअगरy_ops;

	ret = v4l2_async_notअगरier_रेजिस्टर(&isi->v4l2_dev, &isi->notअगरier);
	अगर (ret < 0) अणु
		dev_err(isi->dev, "Notifier registration failed\n");
		v4l2_async_notअगरier_cleanup(&isi->notअगरier);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक aपंचांगel_isi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq;
	काष्ठा aपंचांगel_isi *isi;
	काष्ठा vb2_queue *q;
	काष्ठा resource *regs;
	पूर्णांक ret, i;

	isi = devm_kzalloc(&pdev->dev, माप(काष्ठा aपंचांगel_isi), GFP_KERNEL);
	अगर (!isi)
		वापस -ENOMEM;

	isi->pclk = devm_clk_get(&pdev->dev, "isi_clk");
	अगर (IS_ERR(isi->pclk))
		वापस PTR_ERR(isi->pclk);

	ret = aपंचांगel_isi_parse_dt(isi, pdev);
	अगर (ret)
		वापस ret;

	isi->active = शून्य;
	isi->dev = &pdev->dev;
	mutex_init(&isi->lock);
	spin_lock_init(&isi->irqlock);
	INIT_LIST_HEAD(&isi->video_buffer_list);
	INIT_LIST_HEAD(&isi->dma_desc_head);

	q = &isi->queue;

	/* Initialize the top-level काष्ठाure */
	ret = v4l2_device_रेजिस्टर(&pdev->dev, &isi->v4l2_dev);
	अगर (ret)
		वापस ret;

	isi->vdev = video_device_alloc();
	अगर (!isi->vdev) अणु
		ret = -ENOMEM;
		जाओ err_vdev_alloc;
	पूर्ण

	/* video node */
	isi->vdev->fops = &isi_fops;
	isi->vdev->v4l2_dev = &isi->v4l2_dev;
	isi->vdev->queue = &isi->queue;
	strscpy(isi->vdev->name, KBUILD_MODNAME, माप(isi->vdev->name));
	isi->vdev->release = video_device_release;
	isi->vdev->ioctl_ops = &isi_ioctl_ops;
	isi->vdev->lock = &isi->lock;
	isi->vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
		V4L2_CAP_READWRITE;
	video_set_drvdata(isi->vdev, isi);

	/* buffer queue */
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_READ | VB2_DMABUF;
	q->lock = &isi->lock;
	q->drv_priv = isi;
	q->buf_काष्ठा_size = माप(काष्ठा frame_buffer);
	q->ops = &isi_video_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed = 2;
	q->dev = &pdev->dev;

	ret = vb2_queue_init(q);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to initialize VB2 queue\n");
		जाओ err_vb2_queue;
	पूर्ण
	isi->p_fb_descriptors = dma_alloc_coherent(&pdev->dev,
				माप(काष्ठा fbd) * VIDEO_MAX_FRAME,
				&isi->fb_descriptors_phys,
				GFP_KERNEL);
	अगर (!isi->p_fb_descriptors) अणु
		dev_err(&pdev->dev, "Can't allocate descriptors!\n");
		ret = -ENOMEM;
		जाओ err_dma_alloc;
	पूर्ण

	क्रम (i = 0; i < VIDEO_MAX_FRAME; i++) अणु
		isi->dma_desc[i].p_fbd = isi->p_fb_descriptors + i;
		isi->dma_desc[i].fbd_phys = isi->fb_descriptors_phys +
					i * माप(काष्ठा fbd);
		list_add(&isi->dma_desc[i].list, &isi->dma_desc_head);
	पूर्ण

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	isi->regs = devm_ioremap_resource(&pdev->dev, regs);
	अगर (IS_ERR(isi->regs)) अणु
		ret = PTR_ERR(isi->regs);
		जाओ err_ioremap;
	पूर्ण

	अगर (isi->pdata.data_width_flags & ISI_DATAWIDTH_8)
		isi->width_flags = 1 << 7;
	अगर (isi->pdata.data_width_flags & ISI_DATAWIDTH_10)
		isi->width_flags |= 1 << 9;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ err_req_irq;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, isi_पूर्णांकerrupt, 0, "isi", isi);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to request irq %d\n", irq);
		जाओ err_req_irq;
	पूर्ण
	isi->irq = irq;

	ret = isi_graph_init(isi);
	अगर (ret < 0)
		जाओ err_req_irq;

	pm_suspend_ignore_children(&pdev->dev, true);
	pm_runसमय_enable(&pdev->dev);
	platक्रमm_set_drvdata(pdev, isi);
	वापस 0;

err_req_irq:
err_ioremap:
	dma_मुक्त_coherent(&pdev->dev,
			माप(काष्ठा fbd) * VIDEO_MAX_FRAME,
			isi->p_fb_descriptors,
			isi->fb_descriptors_phys);
err_dma_alloc:
err_vb2_queue:
	video_device_release(isi->vdev);
err_vdev_alloc:
	v4l2_device_unरेजिस्टर(&isi->v4l2_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_isi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_isi *isi = platक्रमm_get_drvdata(pdev);

	dma_मुक्त_coherent(&pdev->dev,
			माप(काष्ठा fbd) * VIDEO_MAX_FRAME,
			isi->p_fb_descriptors,
			isi->fb_descriptors_phys);
	pm_runसमय_disable(&pdev->dev);
	v4l2_async_notअगरier_unरेजिस्टर(&isi->notअगरier);
	v4l2_async_notअगरier_cleanup(&isi->notअगरier);
	v4l2_device_unरेजिस्टर(&isi->v4l2_dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक aपंचांगel_isi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_isi *isi = dev_get_drvdata(dev);

	clk_disable_unprepare(isi->pclk);

	वापस 0;
पूर्ण
अटल पूर्णांक aपंचांगel_isi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_isi *isi = dev_get_drvdata(dev);

	वापस clk_prepare_enable(isi->pclk);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops aपंचांगel_isi_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(aपंचांगel_isi_runसमय_suspend,
				aपंचांगel_isi_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_isi_of_match[] = अणु
	अणु .compatible = "atmel,at91sam9g45-isi" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_isi_of_match);

अटल काष्ठा platक्रमm_driver aपंचांगel_isi_driver = अणु
	.driver		= अणु
		.name = "atmel_isi",
		.of_match_table = of_match_ptr(aपंचांगel_isi_of_match),
		.pm	= &aपंचांगel_isi_dev_pm_ops,
	पूर्ण,
	.probe		= aपंचांगel_isi_probe,
	.हटाओ		= aपंचांगel_isi_हटाओ,
पूर्ण;

module_platक्रमm_driver(aपंचांगel_isi_driver);

MODULE_AUTHOR("Josh Wu <josh.wu@atmel.com>");
MODULE_DESCRIPTION("The V4L2 driver for Atmel Linux");
MODULE_LICENSE("GPL");
