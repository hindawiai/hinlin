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
#समावेश <linux/delay.h>

/* ------------------------------------------------------------------ */

अटल अचिन्हित पूर्णांक ts_debug;
module_param(ts_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(ts_debug,"enable debug messages [ts]");

#घोषणा ts_dbg(fmt, arg...) करो अणु \
	अगर (ts_debug) \
		prपूर्णांकk(KERN_DEBUG pr_fmt("ts: " fmt), ## arg); \
	पूर्ण जबतक (0)

/* ------------------------------------------------------------------ */
अटल पूर्णांक buffer_activate(काष्ठा saa7134_dev *dev,
			   काष्ठा saa7134_buf *buf,
			   काष्ठा saa7134_buf *next)
अणु

	ts_dbg("buffer_activate [%p]", buf);
	buf->top_seen = 0;

	अगर (!dev->ts_started)
		dev->ts_field = V4L2_FIELD_TOP;

	अगर (शून्य == next)
		next = buf;
	अगर (V4L2_FIELD_TOP == dev->ts_field) अणु
		ts_dbg("- [top]     buf=%p next=%p\n", buf, next);
		saa_ग_लिखोl(SAA7134_RS_BA1(5),saa7134_buffer_base(buf));
		saa_ग_लिखोl(SAA7134_RS_BA2(5),saa7134_buffer_base(next));
		dev->ts_field = V4L2_FIELD_BOTTOM;
	पूर्ण अन्यथा अणु
		ts_dbg("- [bottom]  buf=%p next=%p\n", buf, next);
		saa_ग_लिखोl(SAA7134_RS_BA1(5),saa7134_buffer_base(next));
		saa_ग_लिखोl(SAA7134_RS_BA2(5),saa7134_buffer_base(buf));
		dev->ts_field = V4L2_FIELD_TOP;
	पूर्ण

	/* start DMA */
	saa7134_set_dmabits(dev);

	mod_समयr(&dev->ts_q.समयout, jअगरfies+TS_BUFFER_TIMEOUT);

	अगर (!dev->ts_started)
		saa7134_ts_start(dev);

	वापस 0;
पूर्ण

पूर्णांक saa7134_ts_buffer_init(काष्ठा vb2_buffer *vb2)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb2);
	काष्ठा saa7134_dmaqueue *dmaq = vb2->vb2_queue->drv_priv;
	काष्ठा saa7134_buf *buf = container_of(vbuf, काष्ठा saa7134_buf, vb2);

	dmaq->curr = शून्य;
	buf->activate = buffer_activate;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_ts_buffer_init);

पूर्णांक saa7134_ts_buffer_prepare(काष्ठा vb2_buffer *vb2)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb2);
	काष्ठा saa7134_dmaqueue *dmaq = vb2->vb2_queue->drv_priv;
	काष्ठा saa7134_dev *dev = dmaq->dev;
	काष्ठा saa7134_buf *buf = container_of(vbuf, काष्ठा saa7134_buf, vb2);
	काष्ठा sg_table *dma = vb2_dma_sg_plane_desc(vb2, 0);
	अचिन्हित पूर्णांक lines, llength, size;

	ts_dbg("buffer_prepare [%p]\n", buf);

	llength = TS_PACKET_SIZE;
	lines = dev->ts.nr_packets;

	size = lines * llength;
	अगर (vb2_plane_size(vb2, 0) < size)
		वापस -EINVAL;

	vb2_set_plane_payload(vb2, 0, size);
	vbuf->field = dev->field;

	वापस saa7134_pgtable_build(dev->pci, &dmaq->pt, dma->sgl, dma->nents,
				    saa7134_buffer_startpage(buf));
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_ts_buffer_prepare);

पूर्णांक saa7134_ts_queue_setup(काष्ठा vb2_queue *q,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा saa7134_dmaqueue *dmaq = q->drv_priv;
	काष्ठा saa7134_dev *dev = dmaq->dev;
	पूर्णांक size = TS_PACKET_SIZE * dev->ts.nr_packets;

	अगर (0 == *nbuffers)
		*nbuffers = dev->ts.nr_bufs;
	*nbuffers = saa7134_buffer_count(size, *nbuffers);
	अगर (*nbuffers < 3)
		*nbuffers = 3;
	*nplanes = 1;
	sizes[0] = size;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_ts_queue_setup);

पूर्णांक saa7134_ts_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा saa7134_dmaqueue *dmaq = vq->drv_priv;
	काष्ठा saa7134_dev *dev = dmaq->dev;

	/*
	 * Planar video capture and TS share the same DMA channel,
	 * so only one can be active at a समय.
	 */
	अगर (vb2_is_busy(&dev->video_vbq) && dev->fmt->planar) अणु
		काष्ठा saa7134_buf *buf, *पंचांगp;

		list_क्रम_each_entry_safe(buf, पंचांगp, &dmaq->queue, entry) अणु
			list_del(&buf->entry);
			vb2_buffer_करोne(&buf->vb2.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		पूर्ण
		अगर (dmaq->curr) अणु
			vb2_buffer_करोne(&dmaq->curr->vb2.vb2_buf,
					VB2_BUF_STATE_QUEUED);
			dmaq->curr = शून्य;
		पूर्ण
		वापस -EBUSY;
	पूर्ण
	dmaq->seq_nr = 0;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_ts_start_streaming);

व्योम saa7134_ts_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा saa7134_dmaqueue *dmaq = vq->drv_priv;
	काष्ठा saa7134_dev *dev = dmaq->dev;

	saa7134_ts_stop(dev);
	saa7134_stop_streaming(dev, dmaq);
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_ts_stop_streaming);

काष्ठा vb2_ops saa7134_ts_qops = अणु
	.queue_setup	= saa7134_ts_queue_setup,
	.buf_init	= saa7134_ts_buffer_init,
	.buf_prepare	= saa7134_ts_buffer_prepare,
	.buf_queue	= saa7134_vb2_buffer_queue,
	.रुको_prepare	= vb2_ops_रुको_prepare,
	.रुको_finish	= vb2_ops_रुको_finish,
	.stop_streaming = saa7134_ts_stop_streaming,
पूर्ण;
EXPORT_SYMBOL_GPL(saa7134_ts_qops);

/* ----------------------------------------------------------- */
/* exported stuff                                              */

अटल अचिन्हित पूर्णांक tsbufs = 8;
module_param(tsbufs, पूर्णांक, 0444);
MODULE_PARM_DESC(tsbufs, "number of ts buffers for read/write IO, range 2-32");

अटल अचिन्हित पूर्णांक ts_nr_packets = 64;
module_param(ts_nr_packets, पूर्णांक, 0444);
MODULE_PARM_DESC(ts_nr_packets,"size of a ts buffers (in ts packets)");

पूर्णांक saa7134_ts_init_hw(काष्ठा saa7134_dev *dev)
अणु
	/* deactivate TS softreset */
	saa_ग_लिखोb(SAA7134_TS_SERIAL1, 0x00);
	/* TSSOP high active, TSVAL high active, TSLOCK ignored */
	saa_ग_लिखोb(SAA7134_TS_PARALLEL, 0x6c);
	saa_ग_लिखोb(SAA7134_TS_PARALLEL_SERIAL, (TS_PACKET_SIZE-1));
	saa_ग_लिखोb(SAA7134_TS_DMA0, ((dev->ts.nr_packets-1)&0xff));
	saa_ग_लिखोb(SAA7134_TS_DMA1, (((dev->ts.nr_packets-1)>>8)&0xff));
	/* TSNOPIT=0, TSCOLAP=0 */
	saa_ग_लिखोb(SAA7134_TS_DMA2,
		((((dev->ts.nr_packets-1)>>16)&0x3f) | 0x00));

	वापस 0;
पूर्ण

पूर्णांक saa7134_ts_init1(काष्ठा saa7134_dev *dev)
अणु
	/* sanitycheck insmod options */
	अगर (tsbufs < 2)
		tsbufs = 2;
	अगर (tsbufs > VIDEO_MAX_FRAME)
		tsbufs = VIDEO_MAX_FRAME;
	अगर (ts_nr_packets < 4)
		ts_nr_packets = 4;
	अगर (ts_nr_packets > 312)
		ts_nr_packets = 312;
	dev->ts.nr_bufs    = tsbufs;
	dev->ts.nr_packets = ts_nr_packets;

	INIT_LIST_HEAD(&dev->ts_q.queue);
	समयr_setup(&dev->ts_q.समयout, saa7134_buffer_समयout, 0);
	dev->ts_q.dev              = dev;
	dev->ts_q.need_two         = 1;
	dev->ts_started            = 0;
	saa7134_pgtable_alloc(dev->pci, &dev->ts_q.pt);

	/* init TS hw */
	saa7134_ts_init_hw(dev);

	वापस 0;
पूर्ण

/* Function क्रम stop TS */
पूर्णांक saa7134_ts_stop(काष्ठा saa7134_dev *dev)
अणु
	ts_dbg("TS stop\n");

	अगर (!dev->ts_started)
		वापस 0;

	/* Stop TS stream */
	चयन (saa7134_boards[dev->board].ts_type) अणु
	हाल SAA7134_MPEG_TS_PARALLEL:
		saa_ग_लिखोb(SAA7134_TS_PARALLEL, 0x6c);
		dev->ts_started = 0;
		अवरोध;
	हाल SAA7134_MPEG_TS_SERIAL:
		saa_ग_लिखोb(SAA7134_TS_SERIAL0, 0x40);
		dev->ts_started = 0;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* Function क्रम start TS */
पूर्णांक saa7134_ts_start(काष्ठा saa7134_dev *dev)
अणु
	ts_dbg("TS start\n");

	अगर (WARN_ON(dev->ts_started))
		वापस 0;

	/* dma: setup channel 5 (= TS) */
	saa_ग_लिखोb(SAA7134_TS_DMA0, (dev->ts.nr_packets - 1) & 0xff);
	saa_ग_लिखोb(SAA7134_TS_DMA1,
		((dev->ts.nr_packets - 1) >> 8) & 0xff);
	/* TSNOPIT=0, TSCOLAP=0 */
	saa_ग_लिखोb(SAA7134_TS_DMA2,
		(((dev->ts.nr_packets - 1) >> 16) & 0x3f) | 0x00);
	saa_ग_लिखोl(SAA7134_RS_PITCH(5), TS_PACKET_SIZE);
	saa_ग_लिखोl(SAA7134_RS_CONTROL(5), SAA7134_RS_CONTROL_BURST_16 |
					  SAA7134_RS_CONTROL_ME |
					  (dev->ts_q.pt.dma >> 12));

	/* reset hardware TS buffers */
	saa_ग_लिखोb(SAA7134_TS_SERIAL1, 0x00);
	saa_ग_लिखोb(SAA7134_TS_SERIAL1, 0x03);
	saa_ग_लिखोb(SAA7134_TS_SERIAL1, 0x00);
	saa_ग_लिखोb(SAA7134_TS_SERIAL1, 0x01);

	/* TS घड़ी non-inverted */
	saa_ग_लिखोb(SAA7134_TS_SERIAL1, 0x00);

	/* Start TS stream */
	चयन (saa7134_boards[dev->board].ts_type) अणु
	हाल SAA7134_MPEG_TS_PARALLEL:
		saa_ग_लिखोb(SAA7134_TS_SERIAL0, 0x40);
		saa_ग_लिखोb(SAA7134_TS_PARALLEL, 0xec |
			(saa7134_boards[dev->board].ts_क्रमce_val << 4));
		अवरोध;
	हाल SAA7134_MPEG_TS_SERIAL:
		saa_ग_लिखोb(SAA7134_TS_SERIAL0, 0xd8);
		saa_ग_लिखोb(SAA7134_TS_PARALLEL, 0x6c |
			(saa7134_boards[dev->board].ts_क्रमce_val << 4));
		saa_ग_लिखोb(SAA7134_TS_PARALLEL_SERIAL, 0xbc);
		saa_ग_लिखोb(SAA7134_TS_SERIAL1, 0x02);
		अवरोध;
	पूर्ण

	dev->ts_started = 1;

	वापस 0;
पूर्ण

पूर्णांक saa7134_ts_fini(काष्ठा saa7134_dev *dev)
अणु
	saa7134_pgtable_मुक्त(dev->pci, &dev->ts_q.pt);
	वापस 0;
पूर्ण

व्योम saa7134_irq_ts_करोne(काष्ठा saa7134_dev *dev, अचिन्हित दीर्घ status)
अणु
	क्रमागत v4l2_field field;

	spin_lock(&dev->slock);
	अगर (dev->ts_q.curr) अणु
		field = dev->ts_field;
		अगर (field != V4L2_FIELD_TOP) अणु
			अगर ((status & 0x100000) != 0x000000)
				जाओ करोne;
		पूर्ण अन्यथा अणु
			अगर ((status & 0x100000) != 0x100000)
				जाओ करोne;
		पूर्ण
		saa7134_buffer_finish(dev, &dev->ts_q, VB2_BUF_STATE_DONE);
	पूर्ण
	saa7134_buffer_next(dev,&dev->ts_q);

 करोne:
	spin_unlock(&dev->slock);
पूर्ण
