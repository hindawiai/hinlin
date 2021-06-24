<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 */

#समावेश "cx88.h"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

अटल अचिन्हित पूर्णांक vbi_debug;
module_param(vbi_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(vbi_debug, "enable debug messages [vbi]");

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु			\
	अगर (vbi_debug >= level)					\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: vbi:" fmt),	\
			__func__, ##arg);			\
पूर्ण जबतक (0)

/* ------------------------------------------------------------------ */

पूर्णांक cx8800_vbi_fmt(काष्ठा file *file, व्योम *priv,
		   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);

	f->fmt.vbi.samples_per_line = VBI_LINE_LENGTH;
	f->fmt.vbi.sample_क्रमmat = V4L2_PIX_FMT_GREY;
	f->fmt.vbi.offset = 244;

	अगर (dev->core->tvnorm & V4L2_STD_525_60) अणु
		/* ntsc */
		f->fmt.vbi.sampling_rate = 28636363;
		f->fmt.vbi.start[0] = 10;
		f->fmt.vbi.start[1] = 273;
		f->fmt.vbi.count[0] = VBI_LINE_NTSC_COUNT;
		f->fmt.vbi.count[1] = VBI_LINE_NTSC_COUNT;

	पूर्ण अन्यथा अगर (dev->core->tvnorm & V4L2_STD_625_50) अणु
		/* pal */
		f->fmt.vbi.sampling_rate = 35468950;
		f->fmt.vbi.start[0] = V4L2_VBI_ITU_625_F1_START + 5;
		f->fmt.vbi.start[1] = V4L2_VBI_ITU_625_F2_START + 5;
		f->fmt.vbi.count[0] = VBI_LINE_PAL_COUNT;
		f->fmt.vbi.count[1] = VBI_LINE_PAL_COUNT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx8800_start_vbi_dma(काष्ठा cx8800_dev    *dev,
				काष्ठा cx88_dmaqueue *q,
				काष्ठा cx88_buffer   *buf)
अणु
	काष्ठा cx88_core *core = dev->core;

	/* setup fअगरo + क्रमmat */
	cx88_sram_channel_setup(dev->core, &cx88_sram_channels[SRAM_CH24],
				VBI_LINE_LENGTH, buf->risc.dma);

	cx_ग_लिखो(MO_VBOS_CONTROL, (1 << 18) |  /* comb filter delay fixup */
				  (1 << 15) |  /* enable vbi capture */
				  (1 << 11));

	/* reset counter */
	cx_ग_लिखो(MO_VBI_GPCNTRL, GP_COUNT_CONTROL_RESET);
	q->count = 0;

	/* enable irqs */
	cx_set(MO_PCI_INTMSK, core->pci_irqmask | PCI_INT_VIDINT);
	cx_set(MO_VID_INTMSK, 0x0f0088);

	/* enable capture */
	cx_set(VID_CAPTURE_CONTROL, 0x18);

	/* start dma */
	cx_set(MO_DEV_CNTRL2, (1 << 5));
	cx_set(MO_VID_DMACNTRL, 0x88);

	वापस 0;
पूर्ण

व्योम cx8800_stop_vbi_dma(काष्ठा cx8800_dev *dev)
अणु
	काष्ठा cx88_core *core = dev->core;

	/* stop dma */
	cx_clear(MO_VID_DMACNTRL, 0x88);

	/* disable capture */
	cx_clear(VID_CAPTURE_CONTROL, 0x18);

	/* disable irqs */
	cx_clear(MO_PCI_INTMSK, PCI_INT_VIDINT);
	cx_clear(MO_VID_INTMSK, 0x0f0088);
पूर्ण

पूर्णांक cx8800_restart_vbi_queue(काष्ठा cx8800_dev    *dev,
			     काष्ठा cx88_dmaqueue *q)
अणु
	काष्ठा cx88_buffer *buf;

	अगर (list_empty(&q->active))
		वापस 0;

	buf = list_entry(q->active.next, काष्ठा cx88_buffer, list);
	dprपूर्णांकk(2, "restart_queue [%p/%d]: restart dma\n",
		buf, buf->vb.vb2_buf.index);
	cx8800_start_vbi_dma(dev, q, buf);
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *q,
		       अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा cx8800_dev *dev = q->drv_priv;

	*num_planes = 1;
	अगर (dev->core->tvnorm & V4L2_STD_525_60)
		sizes[0] = VBI_LINE_NTSC_COUNT * VBI_LINE_LENGTH * 2;
	अन्यथा
		sizes[0] = VBI_LINE_PAL_COUNT * VBI_LINE_LENGTH * 2;
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx8800_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx88_buffer *buf = container_of(vbuf, काष्ठा cx88_buffer, vb);
	काष्ठा sg_table *sgt = vb2_dma_sg_plane_desc(vb, 0);
	अचिन्हित पूर्णांक lines;
	अचिन्हित पूर्णांक size;

	अगर (dev->core->tvnorm & V4L2_STD_525_60)
		lines = VBI_LINE_NTSC_COUNT;
	अन्यथा
		lines = VBI_LINE_PAL_COUNT;
	size = lines * VBI_LINE_LENGTH * 2;
	अगर (vb2_plane_size(vb, 0) < size)
		वापस -EINVAL;
	vb2_set_plane_payload(vb, 0, size);

	cx88_risc_buffer(dev->pci, &buf->risc, sgt->sgl,
			 0, VBI_LINE_LENGTH * lines,
			 VBI_LINE_LENGTH, 0,
			 lines);
	वापस 0;
पूर्ण

अटल व्योम buffer_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx8800_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx88_buffer *buf = container_of(vbuf, काष्ठा cx88_buffer, vb);
	काष्ठा cx88_riscmem *risc = &buf->risc;

	अगर (risc->cpu)
		pci_मुक्त_consistent(dev->pci, risc->size, risc->cpu, risc->dma);
	स_रखो(risc, 0, माप(*risc));
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx8800_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx88_buffer    *buf = container_of(vbuf, काष्ठा cx88_buffer, vb);
	काष्ठा cx88_buffer    *prev;
	काष्ठा cx88_dmaqueue  *q    = &dev->vbiq;

	/* add jump to start */
	buf->risc.cpu[1] = cpu_to_le32(buf->risc.dma + 8);
	buf->risc.jmp[0] = cpu_to_le32(RISC_JUMP | RISC_CNT_INC);
	buf->risc.jmp[1] = cpu_to_le32(buf->risc.dma + 8);

	अगर (list_empty(&q->active)) अणु
		list_add_tail(&buf->list, &q->active);
		dprपूर्णांकk(2, "[%p/%d] vbi_queue - first active\n",
			buf, buf->vb.vb2_buf.index);

	पूर्ण अन्यथा अणु
		buf->risc.cpu[0] |= cpu_to_le32(RISC_IRQ1);
		prev = list_entry(q->active.prev, काष्ठा cx88_buffer, list);
		list_add_tail(&buf->list, &q->active);
		prev->risc.jmp[1] = cpu_to_le32(buf->risc.dma);
		dprपूर्णांकk(2, "[%p/%d] buffer_queue - append to active\n",
			buf, buf->vb.vb2_buf.index);
	पूर्ण
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cx8800_dev *dev = q->drv_priv;
	काष्ठा cx88_dmaqueue *dmaq = &dev->vbiq;
	काष्ठा cx88_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx88_buffer, list);

	cx8800_start_vbi_dma(dev, dmaq, buf);
	वापस 0;
पूर्ण

अटल व्योम stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा cx8800_dev *dev = q->drv_priv;
	काष्ठा cx88_core *core = dev->core;
	काष्ठा cx88_dmaqueue *dmaq = &dev->vbiq;
	अचिन्हित दीर्घ flags;

	cx_clear(MO_VID_DMACNTRL, 0x11);
	cx_clear(VID_CAPTURE_CONTROL, 0x06);
	cx8800_stop_vbi_dma(dev);
	spin_lock_irqsave(&dev->slock, flags);
	जबतक (!list_empty(&dmaq->active)) अणु
		काष्ठा cx88_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx88_buffer, list);

		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

स्थिर काष्ठा vb2_ops cx8800_vbi_qops = अणु
	.queue_setup    = queue_setup,
	.buf_prepare  = buffer_prepare,
	.buf_finish = buffer_finish,
	.buf_queue    = buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = start_streaming,
	.stop_streaming = stop_streaming,
पूर्ण;
