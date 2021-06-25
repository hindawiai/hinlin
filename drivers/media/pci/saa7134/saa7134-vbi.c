<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * device driver क्रम philips saa7134 based TV cards
 * video4linux video पूर्णांकerface
 *
 * (c) 2001,02 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]
 */

#समावेश "saa7134.h"
#समावेश "saa7134-reg.h"

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

/* ------------------------------------------------------------------ */

अटल अचिन्हित पूर्णांक vbi_debug;
module_param(vbi_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(vbi_debug,"enable debug messages [vbi]");

अटल अचिन्हित पूर्णांक vbibufs = 4;
module_param(vbibufs, पूर्णांक, 0444);
MODULE_PARM_DESC(vbibufs,"number of vbi buffers, range 2-32");

#घोषणा vbi_dbg(fmt, arg...) करो अणु \
	अगर (vbi_debug) \
		prपूर्णांकk(KERN_DEBUG pr_fmt("vbi: " fmt), ## arg); \
	पूर्ण जबतक (0)

/* ------------------------------------------------------------------ */

#घोषणा VBI_LINE_COUNT     17
#घोषणा VBI_LINE_LENGTH  2048
#घोषणा VBI_SCALE       0x200

अटल व्योम task_init(काष्ठा saa7134_dev *dev, काष्ठा saa7134_buf *buf,
		      पूर्णांक task)
अणु
	काष्ठा saa7134_tvnorm *norm = dev->tvnorm;

	/* setup video scaler */
	saa_ग_लिखोb(SAA7134_VBI_H_START1(task), norm->h_start     &  0xff);
	saa_ग_लिखोb(SAA7134_VBI_H_START2(task), norm->h_start     >> 8);
	saa_ग_लिखोb(SAA7134_VBI_H_STOP1(task),  norm->h_stop      &  0xff);
	saa_ग_लिखोb(SAA7134_VBI_H_STOP2(task),  norm->h_stop      >> 8);
	saa_ग_लिखोb(SAA7134_VBI_V_START1(task), norm->vbi_v_start_0 &  0xff);
	saa_ग_लिखोb(SAA7134_VBI_V_START2(task), norm->vbi_v_start_0 >> 8);
	saa_ग_लिखोb(SAA7134_VBI_V_STOP1(task),  norm->vbi_v_stop_0  &  0xff);
	saa_ग_लिखोb(SAA7134_VBI_V_STOP2(task),  norm->vbi_v_stop_0  >> 8);

	saa_ग_लिखोb(SAA7134_VBI_H_SCALE_INC1(task),        VBI_SCALE & 0xff);
	saa_ग_लिखोb(SAA7134_VBI_H_SCALE_INC2(task),        VBI_SCALE >> 8);
	saa_ग_लिखोb(SAA7134_VBI_PHASE_OFFSET_LUMA(task),   0x00);
	saa_ग_लिखोb(SAA7134_VBI_PHASE_OFFSET_CHROMA(task), 0x00);

	saa_ग_लिखोb(SAA7134_VBI_H_LEN1(task), dev->vbi_hlen & 0xff);
	saa_ग_लिखोb(SAA7134_VBI_H_LEN2(task), dev->vbi_hlen >> 8);
	saa_ग_लिखोb(SAA7134_VBI_V_LEN1(task), dev->vbi_vlen & 0xff);
	saa_ग_लिखोb(SAA7134_VBI_V_LEN2(task), dev->vbi_vlen >> 8);

	saa_anकरोrb(SAA7134_DATA_PATH(task), 0xc0, 0x00);
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक buffer_activate(काष्ठा saa7134_dev *dev,
			   काष्ठा saa7134_buf *buf,
			   काष्ठा saa7134_buf *next)
अणु
	काष्ठा saa7134_dmaqueue *dmaq = buf->vb2.vb2_buf.vb2_queue->drv_priv;
	अचिन्हित दीर्घ control, base;

	vbi_dbg("buffer_activate [%p]\n", buf);
	buf->top_seen = 0;

	task_init(dev, buf, TASK_A);
	task_init(dev, buf, TASK_B);
	saa_ग_लिखोb(SAA7134_OFMT_DATA_A, 0x06);
	saa_ग_लिखोb(SAA7134_OFMT_DATA_B, 0x06);

	/* DMA: setup channel 2+3 (= VBI Task A+B) */
	base    = saa7134_buffer_base(buf);
	control = SAA7134_RS_CONTROL_BURST_16 |
		SAA7134_RS_CONTROL_ME |
		(dmaq->pt.dma >> 12);
	saa_ग_लिखोl(SAA7134_RS_BA1(2), base);
	saa_ग_लिखोl(SAA7134_RS_BA2(2), base + dev->vbi_hlen * dev->vbi_vlen);
	saa_ग_लिखोl(SAA7134_RS_PITCH(2), dev->vbi_hlen);
	saa_ग_लिखोl(SAA7134_RS_CONTROL(2), control);
	saa_ग_लिखोl(SAA7134_RS_BA1(3), base);
	saa_ग_लिखोl(SAA7134_RS_BA2(3), base + dev->vbi_hlen * dev->vbi_vlen);
	saa_ग_लिखोl(SAA7134_RS_PITCH(3), dev->vbi_hlen);
	saa_ग_लिखोl(SAA7134_RS_CONTROL(3), control);

	/* start DMA */
	saa7134_set_dmabits(dev);
	mod_समयr(&dmaq->समयout, jअगरfies + BUFFER_TIMEOUT);

	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb2)
अणु
	काष्ठा saa7134_dmaqueue *dmaq = vb2->vb2_queue->drv_priv;
	काष्ठा saa7134_dev *dev = dmaq->dev;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb2);
	काष्ठा saa7134_buf *buf = container_of(vbuf, काष्ठा saa7134_buf, vb2);
	काष्ठा sg_table *dma = vb2_dma_sg_plane_desc(vb2, 0);
	अचिन्हित पूर्णांक size;

	अगर (dma->sgl->offset) अणु
		pr_err("The buffer is not page-aligned\n");
		वापस -EINVAL;
	पूर्ण
	size = dev->vbi_hlen * dev->vbi_vlen * 2;
	अगर (vb2_plane_size(vb2, 0) < size)
		वापस -EINVAL;

	vb2_set_plane_payload(vb2, 0, size);

	वापस saa7134_pgtable_build(dev->pci, &dmaq->pt, dma->sgl, dma->nents,
				    saa7134_buffer_startpage(buf));
पूर्ण

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *q,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा saa7134_dmaqueue *dmaq = q->drv_priv;
	काष्ठा saa7134_dev *dev = dmaq->dev;
	अचिन्हित पूर्णांक size;

	dev->vbi_vlen = dev->tvnorm->vbi_v_stop_0 - dev->tvnorm->vbi_v_start_0 + 1;
	अगर (dev->vbi_vlen > VBI_LINE_COUNT)
		dev->vbi_vlen = VBI_LINE_COUNT;
	dev->vbi_hlen = VBI_LINE_LENGTH;
	size = dev->vbi_hlen * dev->vbi_vlen * 2;

	*nbuffers = saa7134_buffer_count(size, *nbuffers);
	*nplanes = 1;
	sizes[0] = size;
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_init(काष्ठा vb2_buffer *vb2)
अणु
	काष्ठा saa7134_dmaqueue *dmaq = vb2->vb2_queue->drv_priv;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb2);
	काष्ठा saa7134_buf *buf = container_of(vbuf, काष्ठा saa7134_buf, vb2);

	dmaq->curr = शून्य;
	buf->activate = buffer_activate;
	वापस 0;
पूर्ण

स्थिर काष्ठा vb2_ops saa7134_vbi_qops = अणु
	.queue_setup	= queue_setup,
	.buf_init	= buffer_init,
	.buf_prepare	= buffer_prepare,
	.buf_queue	= saa7134_vb2_buffer_queue,
	.रुको_prepare	= vb2_ops_रुको_prepare,
	.रुको_finish	= vb2_ops_रुको_finish,
	.start_streaming = saa7134_vb2_start_streaming,
	.stop_streaming = saa7134_vb2_stop_streaming,
पूर्ण;

/* ------------------------------------------------------------------ */

पूर्णांक saa7134_vbi_init1(काष्ठा saa7134_dev *dev)
अणु
	INIT_LIST_HEAD(&dev->vbi_q.queue);
	समयr_setup(&dev->vbi_q.समयout, saa7134_buffer_समयout, 0);
	dev->vbi_q.dev              = dev;

	अगर (vbibufs < 2)
		vbibufs = 2;
	अगर (vbibufs > VIDEO_MAX_FRAME)
		vbibufs = VIDEO_MAX_FRAME;
	वापस 0;
पूर्ण

पूर्णांक saa7134_vbi_fini(काष्ठा saa7134_dev *dev)
अणु
	/* nothing */
	वापस 0;
पूर्ण

व्योम saa7134_irq_vbi_करोne(काष्ठा saa7134_dev *dev, अचिन्हित दीर्घ status)
अणु
	spin_lock(&dev->slock);
	अगर (dev->vbi_q.curr) अणु
		/* make sure we have seen both fields */
		अगर ((status & 0x10) == 0x00) अणु
			dev->vbi_q.curr->top_seen = 1;
			जाओ करोne;
		पूर्ण
		अगर (!dev->vbi_q.curr->top_seen)
			जाओ करोne;

		saa7134_buffer_finish(dev, &dev->vbi_q, VB2_BUF_STATE_DONE);
	पूर्ण
	saa7134_buffer_next(dev, &dev->vbi_q);

 करोne:
	spin_unlock(&dev->slock);
पूर्ण
