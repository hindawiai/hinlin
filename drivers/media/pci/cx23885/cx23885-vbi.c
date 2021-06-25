<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX23885 PCIe bridge
 *
 *  Copyright (c) 2007 Steven Toth <stoth@linuxtv.org>
 */

#समावेश "cx23885.h"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>

अटल अचिन्हित पूर्णांक vbibufs = 4;
module_param(vbibufs, पूर्णांक, 0644);
MODULE_PARM_DESC(vbibufs, "number of vbi buffers, range 2-32");

अटल अचिन्हित पूर्णांक vbi_debug;
module_param(vbi_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(vbi_debug, "enable debug messages [vbi]");

#घोषणा dprपूर्णांकk(level, fmt, arg...)\
	करो अणु अगर (vbi_debug >= level)\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: vbi:" fmt), \
			__func__, ##arg); \
	पूर्ण जबतक (0)

/* ------------------------------------------------------------------ */

#घोषणा VBI_LINE_LENGTH 1440
#घोषणा VBI_NTSC_LINE_COUNT 12
#घोषणा VBI_PAL_LINE_COUNT 18


पूर्णांक cx23885_vbi_fmt(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	f->fmt.vbi.sampling_rate = 27000000;
	f->fmt.vbi.samples_per_line = VBI_LINE_LENGTH;
	f->fmt.vbi.sample_क्रमmat = V4L2_PIX_FMT_GREY;
	f->fmt.vbi.offset = 0;
	f->fmt.vbi.flags = 0;
	अगर (dev->tvnorm & V4L2_STD_525_60) अणु
		/* ntsc */
		f->fmt.vbi.start[0] = V4L2_VBI_ITU_525_F1_START + 9;
		f->fmt.vbi.start[1] = V4L2_VBI_ITU_525_F2_START + 9;
		f->fmt.vbi.count[0] = VBI_NTSC_LINE_COUNT;
		f->fmt.vbi.count[1] = VBI_NTSC_LINE_COUNT;
	पूर्ण अन्यथा अगर (dev->tvnorm & V4L2_STD_625_50) अणु
		/* pal */
		f->fmt.vbi.start[0] = V4L2_VBI_ITU_625_F1_START + 5;
		f->fmt.vbi.start[1] = V4L2_VBI_ITU_625_F2_START + 5;
		f->fmt.vbi.count[0] = VBI_PAL_LINE_COUNT;
		f->fmt.vbi.count[1] = VBI_PAL_LINE_COUNT;
	पूर्ण

	वापस 0;
पूर्ण

/* We're given the Video Interrupt status रेजिस्टर.
 * The cx23885_video_irq() func has alपढ़ोy validated
 * the potential error bits, we just need to
 * deal with vbi payload and वापस indication अगर
 * we actually processed any payload.
 */
पूर्णांक cx23885_vbi_irq(काष्ठा cx23885_dev *dev, u32 status)
अणु
	u32 count;
	पूर्णांक handled = 0;

	अगर (status & VID_BC_MSK_VBI_RISCI1) अणु
		dprपूर्णांकk(1, "%s() VID_BC_MSK_VBI_RISCI1\n", __func__);
		spin_lock(&dev->slock);
		count = cx_पढ़ो(VBI_A_GPCNT);
		cx23885_video_wakeup(dev, &dev->vbiq, count);
		spin_unlock(&dev->slock);
		handled++;
	पूर्ण

	वापस handled;
पूर्ण

अटल पूर्णांक cx23885_start_vbi_dma(काष्ठा cx23885_dev    *dev,
			 काष्ठा cx23885_dmaqueue *q,
			 काष्ठा cx23885_buffer   *buf)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);

	/* setup fअगरo + क्रमmat */
	cx23885_sram_channel_setup(dev, &dev->sram_channels[SRAM_CH02],
				VBI_LINE_LENGTH, buf->risc.dma);

	/* reset counter */
	cx_ग_लिखो(VID_A_VBI_CTRL, 3);
	cx_ग_लिखो(VBI_A_GPCNT_CTL, 3);
	q->count = 0;

	/* enable irq */
	cx23885_irq_add_enable(dev, 0x01);
	cx_set(VID_A_INT_MSK, 0x000022);

	/* start dma */
	cx_set(DEV_CNTRL2, (1<<5));
	cx_set(VID_A_DMA_CTL, 0x22); /* FIFO and RISC enable */

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *q,
			   अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा cx23885_dev *dev = q->drv_priv;
	अचिन्हित lines = VBI_PAL_LINE_COUNT;

	अगर (dev->tvnorm & V4L2_STD_525_60)
		lines = VBI_NTSC_LINE_COUNT;
	*num_planes = 1;
	sizes[0] = lines * VBI_LINE_LENGTH * 2;
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx23885_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx23885_buffer *buf = container_of(vbuf,
		काष्ठा cx23885_buffer, vb);
	काष्ठा sg_table *sgt = vb2_dma_sg_plane_desc(vb, 0);
	अचिन्हित lines = VBI_PAL_LINE_COUNT;

	अगर (dev->tvnorm & V4L2_STD_525_60)
		lines = VBI_NTSC_LINE_COUNT;

	अगर (vb2_plane_size(vb, 0) < lines * VBI_LINE_LENGTH * 2)
		वापस -EINVAL;
	vb2_set_plane_payload(vb, 0, lines * VBI_LINE_LENGTH * 2);

	cx23885_risc_vbibuffer(dev->pci, &buf->risc,
			 sgt->sgl,
			 0, VBI_LINE_LENGTH * lines,
			 VBI_LINE_LENGTH, 0,
			 lines);
	वापस 0;
पूर्ण

अटल व्योम buffer_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx23885_buffer *buf = container_of(vbuf,
		काष्ठा cx23885_buffer, vb);

	cx23885_मुक्त_buffer(vb->vb2_queue->drv_priv, buf);
पूर्ण

/*
 * The risc program क्रम each buffer works as follows: it starts with a simple
 * 'JUMP to addr + 12', which is effectively a NOP. Then the code to DMA the
 * buffer follows and at the end we have a JUMP back to the start + 12 (skipping
 * the initial JUMP).
 *
 * This is the risc program of the first buffer to be queued अगर the active list
 * is empty and it just keeps DMAing this buffer without generating any
 * पूर्णांकerrupts.
 *
 * If a new buffer is added then the initial JUMP in the code क्रम that buffer
 * will generate an पूर्णांकerrupt which संकेतs that the previous buffer has been
 * DMAed successfully and that it can be वापसed to userspace.
 *
 * It also sets the final jump of the previous buffer to the start of the new
 * buffer, thus chaining the new buffer पूर्णांकo the DMA chain. This is a single
 * atomic u32 ग_लिखो, so there is no race condition.
 *
 * The end-result of all this that you only get an पूर्णांकerrupt when a buffer
 * is पढ़ोy, so the control flow is very easy.
 */
अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx23885_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx23885_buffer *buf = container_of(vbuf,
			काष्ठा cx23885_buffer, vb);
	काष्ठा cx23885_buffer *prev;
	काष्ठा cx23885_dmaqueue *q = &dev->vbiq;
	अचिन्हित दीर्घ flags;

	buf->risc.cpu[1] = cpu_to_le32(buf->risc.dma + 12);
	buf->risc.jmp[0] = cpu_to_le32(RISC_JUMP | RISC_CNT_INC);
	buf->risc.jmp[1] = cpu_to_le32(buf->risc.dma + 12);
	buf->risc.jmp[2] = cpu_to_le32(0); /* bits 63-32 */

	अगर (list_empty(&q->active)) अणु
		spin_lock_irqsave(&dev->slock, flags);
		list_add_tail(&buf->queue, &q->active);
		spin_unlock_irqrestore(&dev->slock, flags);
		dprपूर्णांकk(2, "[%p/%d] vbi_queue - first active\n",
			buf, buf->vb.vb2_buf.index);

	पूर्ण अन्यथा अणु
		buf->risc.cpu[0] |= cpu_to_le32(RISC_IRQ1);
		prev = list_entry(q->active.prev, काष्ठा cx23885_buffer,
			queue);
		spin_lock_irqsave(&dev->slock, flags);
		list_add_tail(&buf->queue, &q->active);
		spin_unlock_irqrestore(&dev->slock, flags);
		prev->risc.jmp[1] = cpu_to_le32(buf->risc.dma);
		dprपूर्णांकk(2, "[%p/%d] buffer_queue - append to active\n",
			buf, buf->vb.vb2_buf.index);
	पूर्ण
पूर्ण

अटल पूर्णांक cx23885_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cx23885_dev *dev = q->drv_priv;
	काष्ठा cx23885_dmaqueue *dmaq = &dev->vbiq;
	काष्ठा cx23885_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx23885_buffer, queue);

	cx23885_start_vbi_dma(dev, dmaq, buf);
	वापस 0;
पूर्ण

अटल व्योम cx23885_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा cx23885_dev *dev = q->drv_priv;
	काष्ठा cx23885_dmaqueue *dmaq = &dev->vbiq;
	अचिन्हित दीर्घ flags;

	cx_clear(VID_A_DMA_CTL, 0x22); /* FIFO and RISC enable */
	spin_lock_irqsave(&dev->slock, flags);
	जबतक (!list_empty(&dmaq->active)) अणु
		काष्ठा cx23885_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx23885_buffer, queue);

		list_del(&buf->queue);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण


स्थिर काष्ठा vb2_ops cx23885_vbi_qops = अणु
	.queue_setup    = queue_setup,
	.buf_prepare  = buffer_prepare,
	.buf_finish = buffer_finish,
	.buf_queue    = buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = cx23885_start_streaming,
	.stop_streaming = cx23885_stop_streaming,
पूर्ण;
