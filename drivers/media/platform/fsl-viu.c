<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2008-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 *  Freescale VIU video driver
 *
 *  Authors: Hongjun Chen <hong-jun.chen@मुक्तscale.com>
 *	     Porting to 2.6.35 by DENX Software Engineering,
 *	     Anम_से_दij Gustschin <agust@denx.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf-dma-contig.h>

#घोषणा DRV_NAME		"fsl_viu"
#घोषणा VIU_VERSION		"0.5.1"

#घोषणा BUFFER_TIMEOUT		msecs_to_jअगरfies(500)  /* 0.5 seconds */

#घोषणा	VIU_VID_MEM_LIMIT	4	/* Video memory limit, in Mb */

/* I2C address of video decoder chip is 0x4A */
#घोषणा VIU_VIDEO_DECODER_ADDR	0x25

अटल पूर्णांक info_level;

#घोषणा dprपूर्णांकk(level, fmt, arg...)					\
	करो अणु								\
		अगर (level <= info_level)				\
			prपूर्णांकk(KERN_DEBUG "viu: " fmt , ## arg);	\
	पूर्ण जबतक (0)

/*
 * Basic काष्ठाures
 */
काष्ठा viu_fmt अणु
	u32   fourcc;		/* v4l2 क्रमmat id */
	u32   pixelक्रमmat;
	पूर्णांक   depth;
पूर्ण;

अटल काष्ठा viu_fmt क्रमmats[] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB565,
		.pixelक्रमmat	= V4L2_PIX_FMT_RGB565,
		.depth		= 16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB32,
		.pixelक्रमmat	= V4L2_PIX_FMT_RGB32,
		.depth		= 32,
	पूर्ण
पूर्ण;

काष्ठा viu_dev;
काष्ठा viu_buf;

/* buffer क्रम one video frame */
काष्ठा viu_buf अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा videobuf_buffer vb;
	काष्ठा viu_fmt *fmt;
पूर्ण;

काष्ठा viu_dmaqueue अणु
	काष्ठा viu_dev		*dev;
	काष्ठा list_head	active;
	काष्ठा list_head	queued;
	काष्ठा समयr_list	समयout;
पूर्ण;

काष्ठा viu_status अणु
	u32 field_irq;
	u32 vsync_irq;
	u32 hsync_irq;
	u32 vstart_irq;
	u32 dma_end_irq;
	u32 error_irq;
पूर्ण;

काष्ठा viu_reg अणु
	u32 status_cfg;
	u32 luminance;
	u32 chroma_r;
	u32 chroma_g;
	u32 chroma_b;
	u32 field_base_addr;
	u32 dma_inc;
	u32 picture_count;
	u32 req_alarm;
	u32 alpha;
पूर्ण __attribute__ ((packed));

काष्ठा viu_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा mutex		lock;
	spinlock_t		slock;
	पूर्णांक			users;

	काष्ठा device		*dev;
	/* various device info */
	काष्ठा video_device	*vdev;
	काष्ठा viu_dmaqueue	vidq;
	क्रमागत v4l2_field		capfield;
	पूर्णांक			field;
	पूर्णांक			first;
	पूर्णांक			dma_करोne;

	/* Hardware रेजिस्टर area */
	काष्ठा viu_reg __iomem	*vr;

	/* Interrupt vector */
	पूर्णांक			irq;
	काष्ठा viu_status	irqs;

	/* video overlay */
	काष्ठा v4l2_framebuffer	ovbuf;
	काष्ठा viu_fmt		*ovfmt;
	अचिन्हित पूर्णांक		ovenable;
	क्रमागत v4l2_field		ovfield;

	/* crop */
	काष्ठा v4l2_rect	crop_current;

	/* घड़ी poपूर्णांकer */
	काष्ठा clk		*clk;

	/* decoder */
	काष्ठा v4l2_subdev	*decoder;

	v4l2_std_id		std;
पूर्ण;

काष्ठा viu_fh अणु
	/* must reमुख्य the first field of this काष्ठा */
	काष्ठा v4l2_fh		fh;
	काष्ठा viu_dev		*dev;

	/* video capture */
	काष्ठा videobuf_queue	vb_vidq;
	spinlock_t		vbq_lock; /* spinlock क्रम the videobuf queue */

	/* video overlay */
	काष्ठा v4l2_winकरोw	win;
	काष्ठा v4l2_clip	clips[1];

	/* video capture */
	काष्ठा viu_fmt		*fmt;
	पूर्णांक			width, height, sizeimage;
	क्रमागत v4l2_buf_type	type;
पूर्ण;

अटल काष्ठा viu_reg reg_val;

/*
 * Macro definitions of VIU रेजिस्टरs
 */

/* STATUS_CONFIG रेजिस्टर */
क्रमागत status_config अणु
	SOFT_RST		= 1 << 0,

	ERR_MASK		= 0x0f << 4,	/* Error code mask */
	ERR_NO			= 0x00,		/* No error */
	ERR_DMA_V		= 0x01 << 4,	/* DMA in vertical active */
	ERR_DMA_VB		= 0x02 << 4,	/* DMA in vertical blanking */
	ERR_LINE_TOO_LONG	= 0x04 << 4,	/* Line too दीर्घ */
	ERR_TOO_MANG_LINES	= 0x05 << 4,	/* Too many lines in field */
	ERR_LINE_TOO_SHORT	= 0x06 << 4,	/* Line too लघु */
	ERR_NOT_ENOUGH_LINE	= 0x07 << 4,	/* Not enough lines in field */
	ERR_FIFO_OVERFLOW	= 0x08 << 4,	/* FIFO overflow */
	ERR_FIFO_UNDERFLOW	= 0x09 << 4,	/* FIFO underflow */
	ERR_1bit_ECC		= 0x0a << 4,	/* One bit ECC error */
	ERR_MORE_ECC		= 0x0b << 4,	/* Two/more bits ECC error */

	INT_FIELD_EN		= 0x01 << 8,	/* Enable field पूर्णांकerrupt */
	INT_VSYNC_EN		= 0x01 << 9,	/* Enable vsync पूर्णांकerrupt */
	INT_HSYNC_EN		= 0x01 << 10,	/* Enable hsync पूर्णांकerrupt */
	INT_VSTART_EN		= 0x01 << 11,	/* Enable vstart पूर्णांकerrupt */
	INT_DMA_END_EN		= 0x01 << 12,	/* Enable DMA end पूर्णांकerrupt */
	INT_ERROR_EN		= 0x01 << 13,	/* Enable error पूर्णांकerrupt */
	INT_ECC_EN		= 0x01 << 14,	/* Enable ECC पूर्णांकerrupt */

	INT_FIELD_STATUS	= 0x01 << 16,	/* field पूर्णांकerrupt status */
	INT_VSYNC_STATUS	= 0x01 << 17,	/* vsync पूर्णांकerrupt status */
	INT_HSYNC_STATUS	= 0x01 << 18,	/* hsync पूर्णांकerrupt status */
	INT_VSTART_STATUS	= 0x01 << 19,	/* vstart पूर्णांकerrupt status */
	INT_DMA_END_STATUS	= 0x01 << 20,	/* DMA end पूर्णांकerrupt status */
	INT_ERROR_STATUS	= 0x01 << 21,	/* error पूर्णांकerrupt status */

	DMA_ACT			= 0x01 << 27,	/* Enable DMA transfer */
	FIELD_NO		= 0x01 << 28,	/* Field number */
	DITHER_ON		= 0x01 << 29,	/* Dithering is on */
	ROUND_ON		= 0x01 << 30,	/* Round is on */
	MODE_32BIT		= 1UL << 31,	/* Data in RGBa888,
						 * 0 in RGB565
						 */
पूर्ण;

#घोषणा norm_maxw()	720
#घोषणा norm_maxh()	576

#घोषणा INT_ALL_STATUS	(INT_FIELD_STATUS | INT_VSYNC_STATUS | \
			 INT_HSYNC_STATUS | INT_VSTART_STATUS | \
			 INT_DMA_END_STATUS | INT_ERROR_STATUS)

#घोषणा NUM_FORMATS	ARRAY_SIZE(क्रमmats)

अटल irqवापस_t viu_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);

अटल काष्ठा viu_fmt *क्रमmat_by_fourcc(पूर्णांक fourcc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_FORMATS; i++) अणु
		अगर (क्रमmats[i].pixelक्रमmat == fourcc)
			वापस क्रमmats + i;
	पूर्ण

	dprपूर्णांकk(0, "unknown pixelformat:'%4.4s'\n", (अक्षर *)&fourcc);
	वापस शून्य;
पूर्ण

अटल व्योम viu_start_dma(काष्ठा viu_dev *dev)
अणु
	काष्ठा viu_reg __iomem *vr = dev->vr;

	dev->field = 0;

	/* Enable DMA operation */
	ioग_लिखो32be(SOFT_RST, &vr->status_cfg);
	ioग_लिखो32be(INT_FIELD_EN, &vr->status_cfg);
पूर्ण

अटल व्योम viu_stop_dma(काष्ठा viu_dev *dev)
अणु
	काष्ठा viu_reg __iomem *vr = dev->vr;
	पूर्णांक cnt = 100;
	u32 status_cfg;

	ioग_लिखो32be(0, &vr->status_cfg);

	/* Clear pending पूर्णांकerrupts */
	status_cfg = ioपढ़ो32be(&vr->status_cfg);
	अगर (status_cfg & 0x3f0000)
		ioग_लिखो32be(status_cfg & 0x3f0000, &vr->status_cfg);

	अगर (status_cfg & DMA_ACT) अणु
		करो अणु
			status_cfg = ioपढ़ो32be(&vr->status_cfg);
			अगर (status_cfg & INT_DMA_END_STATUS)
				अवरोध;
		पूर्ण जबतक (cnt--);

		अगर (cnt < 0) अणु
			/* समयd out, issue soft reset */
			ioग_लिखो32be(SOFT_RST, &vr->status_cfg);
			ioग_लिखो32be(0, &vr->status_cfg);
		पूर्ण अन्यथा अणु
			/* clear DMA_END and other pending irqs */
			ioग_लिखो32be(status_cfg & 0x3f0000, &vr->status_cfg);
		पूर्ण
	पूर्ण

	dev->field = 0;
पूर्ण

अटल पूर्णांक restart_video_queue(काष्ठा viu_dmaqueue *vidq)
अणु
	काष्ठा viu_buf *buf, *prev;

	dprपूर्णांकk(1, "%s vidq=%p\n", __func__, vidq);
	अगर (!list_empty(&vidq->active)) अणु
		buf = list_entry(vidq->active.next, काष्ठा viu_buf, vb.queue);
		dprपूर्णांकk(2, "restart_queue [%p/%d]: restart dma\n",
			buf, buf->vb.i);

		viu_stop_dma(vidq->dev);

		/* cancel all outstanding capture requests */
		list_क्रम_each_entry_safe(buf, prev, &vidq->active, vb.queue) अणु
			list_del(&buf->vb.queue);
			buf->vb.state = VIDEOBUF_ERROR;
			wake_up(&buf->vb.करोne);
		पूर्ण
		mod_समयr(&vidq->समयout, jअगरfies+BUFFER_TIMEOUT);
		वापस 0;
	पूर्ण

	prev = शून्य;
	क्रम (;;) अणु
		अगर (list_empty(&vidq->queued))
			वापस 0;
		buf = list_entry(vidq->queued.next, काष्ठा viu_buf, vb.queue);
		अगर (prev == शून्य) अणु
			list_move_tail(&buf->vb.queue, &vidq->active);

			dprपूर्णांकk(1, "Restarting video dma\n");
			viu_stop_dma(vidq->dev);
			viu_start_dma(vidq->dev);

			buf->vb.state = VIDEOBUF_ACTIVE;
			mod_समयr(&vidq->समयout, jअगरfies+BUFFER_TIMEOUT);
			dprपूर्णांकk(2, "[%p/%d] restart_queue - first active\n",
				buf, buf->vb.i);

		पूर्ण अन्यथा अगर (prev->vb.width  == buf->vb.width  &&
			   prev->vb.height == buf->vb.height &&
			   prev->fmt       == buf->fmt) अणु
			list_move_tail(&buf->vb.queue, &vidq->active);
			buf->vb.state = VIDEOBUF_ACTIVE;
			dprपूर्णांकk(2, "[%p/%d] restart_queue - move to active\n",
				buf, buf->vb.i);
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
		prev = buf;
	पूर्ण
पूर्ण

अटल व्योम viu_vid_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा viu_dev *dev = from_समयr(dev, t, vidq.समयout);
	काष्ठा viu_buf *buf;
	काष्ठा viu_dmaqueue *vidq = &dev->vidq;

	जबतक (!list_empty(&vidq->active)) अणु
		buf = list_entry(vidq->active.next, काष्ठा viu_buf, vb.queue);
		list_del(&buf->vb.queue);
		buf->vb.state = VIDEOBUF_ERROR;
		wake_up(&buf->vb.करोne);
		dprपूर्णांकk(1, "viu/0: [%p/%d] timeout\n", buf, buf->vb.i);
	पूर्ण

	restart_video_queue(vidq);
पूर्ण

/*
 * Videobuf operations
 */
अटल पूर्णांक buffer_setup(काष्ठा videobuf_queue *vq, अचिन्हित पूर्णांक *count,
			अचिन्हित पूर्णांक *size)
अणु
	काष्ठा viu_fh *fh = vq->priv_data;

	*size = fh->width * fh->height * fh->fmt->depth >> 3;
	अगर (*count == 0)
		*count = 32;

	जबतक (*size * *count > VIU_VID_MEM_LIMIT * 1024 * 1024)
		(*count)--;

	dprपूर्णांकk(1, "%s, count=%d, size=%d\n", __func__, *count, *size);
	वापस 0;
पूर्ण

अटल व्योम मुक्त_buffer(काष्ठा videobuf_queue *vq, काष्ठा viu_buf *buf)
अणु
	काष्ठा videobuf_buffer *vb = &buf->vb;
	व्योम *vaddr = शून्य;

	videobuf_रुकोon(vq, &buf->vb, 0, 0);

	अगर (vq->पूर्णांक_ops && vq->पूर्णांक_ops->vaddr)
		vaddr = vq->पूर्णांक_ops->vaddr(vb);

	अगर (vaddr)
		videobuf_dma_contig_मुक्त(vq, &buf->vb);

	buf->vb.state = VIDEOBUF_NEEDS_INIT;
पूर्ण

अंतरभूत पूर्णांक buffer_activate(काष्ठा viu_dev *dev, काष्ठा viu_buf *buf)
अणु
	काष्ठा viu_reg __iomem *vr = dev->vr;
	पूर्णांक bpp;

	/* setup the DMA base address */
	reg_val.field_base_addr = videobuf_to_dma_contig(&buf->vb);

	dprपूर्णांकk(1, "buffer_activate [%p/%d]: dma addr 0x%lx\n",
		buf, buf->vb.i, (अचिन्हित दीर्घ)reg_val.field_base_addr);

	/* पूर्णांकerlace is on by शेष, set horizontal DMA increment */
	reg_val.status_cfg = 0;
	bpp = buf->fmt->depth >> 3;
	चयन (bpp) अणु
	हाल 2:
		reg_val.status_cfg &= ~MODE_32BIT;
		reg_val.dma_inc = buf->vb.width * 2;
		अवरोध;
	हाल 4:
		reg_val.status_cfg |= MODE_32BIT;
		reg_val.dma_inc = buf->vb.width * 4;
		अवरोध;
	शेष:
		dprपूर्णांकk(0, "doesn't support color depth(%d)\n",
			bpp * 8);
		वापस -EINVAL;
	पूर्ण

	/* setup picture_count रेजिस्टर */
	reg_val.picture_count = (buf->vb.height / 2) << 16 |
				buf->vb.width;

	reg_val.status_cfg |= DMA_ACT | INT_DMA_END_EN | INT_FIELD_EN;

	buf->vb.state = VIDEOBUF_ACTIVE;
	dev->capfield = buf->vb.field;

	/* reset dma increment अगर needed */
	अगर (!V4L2_FIELD_HAS_BOTH(buf->vb.field))
		reg_val.dma_inc = 0;

	ioग_लिखो32be(reg_val.dma_inc, &vr->dma_inc);
	ioग_लिखो32be(reg_val.picture_count, &vr->picture_count);
	ioग_लिखो32be(reg_val.field_base_addr, &vr->field_base_addr);
	mod_समयr(&dev->vidq.समयout, jअगरfies + BUFFER_TIMEOUT);
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा videobuf_queue *vq,
			  काष्ठा videobuf_buffer *vb,
			  क्रमागत v4l2_field field)
अणु
	काष्ठा viu_fh  *fh  = vq->priv_data;
	काष्ठा viu_buf *buf = container_of(vb, काष्ठा viu_buf, vb);
	पूर्णांक rc;

	BUG_ON(fh->fmt == शून्य);

	अगर (fh->width  < 48 || fh->width  > norm_maxw() ||
	    fh->height < 32 || fh->height > norm_maxh())
		वापस -EINVAL;
	buf->vb.size = (fh->width * fh->height * fh->fmt->depth) >> 3;
	अगर (buf->vb.baddr != 0 && buf->vb.bsize < buf->vb.size)
		वापस -EINVAL;

	अगर (buf->fmt       != fh->fmt	 ||
	    buf->vb.width  != fh->width  ||
	    buf->vb.height != fh->height ||
	    buf->vb.field  != field) अणु
		buf->fmt       = fh->fmt;
		buf->vb.width  = fh->width;
		buf->vb.height = fh->height;
		buf->vb.field  = field;
	पूर्ण

	अगर (buf->vb.state == VIDEOBUF_NEEDS_INIT) अणु
		rc = videobuf_iolock(vq, &buf->vb, शून्य);
		अगर (rc != 0)
			जाओ fail;

		buf->vb.width  = fh->width;
		buf->vb.height = fh->height;
		buf->vb.field  = field;
		buf->fmt       = fh->fmt;
	पूर्ण

	buf->vb.state = VIDEOBUF_PREPARED;
	वापस 0;

fail:
	मुक्त_buffer(vq, buf);
	वापस rc;
पूर्ण

अटल व्योम buffer_queue(काष्ठा videobuf_queue *vq, काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा viu_buf       *buf     = container_of(vb, काष्ठा viu_buf, vb);
	काष्ठा viu_fh        *fh      = vq->priv_data;
	काष्ठा viu_dev       *dev     = fh->dev;
	काष्ठा viu_dmaqueue  *vidq    = &dev->vidq;
	काष्ठा viu_buf       *prev;

	अगर (!list_empty(&vidq->queued)) अणु
		dprपूर्णांकk(1, "adding vb queue=%p\n", &buf->vb.queue);
		dprपूर्णांकk(1, "vidq pointer 0x%p, queued 0x%p\n",
				vidq, &vidq->queued);
		dprपूर्णांकk(1, "dev %p, queued: self %p, next %p, head %p\n",
			dev, &vidq->queued, vidq->queued.next,
			vidq->queued.prev);
		list_add_tail(&buf->vb.queue, &vidq->queued);
		buf->vb.state = VIDEOBUF_QUEUED;
		dprपूर्णांकk(2, "[%p/%d] buffer_queue - append to queued\n",
			buf, buf->vb.i);
	पूर्ण अन्यथा अगर (list_empty(&vidq->active)) अणु
		dprपूर्णांकk(1, "adding vb active=%p\n", &buf->vb.queue);
		list_add_tail(&buf->vb.queue, &vidq->active);
		buf->vb.state = VIDEOBUF_ACTIVE;
		mod_समयr(&vidq->समयout, jअगरfies+BUFFER_TIMEOUT);
		dprपूर्णांकk(2, "[%p/%d] buffer_queue - first active\n",
			buf, buf->vb.i);

		buffer_activate(dev, buf);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(1, "adding vb queue2=%p\n", &buf->vb.queue);
		prev = list_entry(vidq->active.prev, काष्ठा viu_buf, vb.queue);
		अगर (prev->vb.width  == buf->vb.width  &&
		    prev->vb.height == buf->vb.height &&
		    prev->fmt       == buf->fmt) अणु
			list_add_tail(&buf->vb.queue, &vidq->active);
			buf->vb.state = VIDEOBUF_ACTIVE;
			dprपूर्णांकk(2, "[%p/%d] buffer_queue - append to active\n",
				buf, buf->vb.i);
		पूर्ण अन्यथा अणु
			list_add_tail(&buf->vb.queue, &vidq->queued);
			buf->vb.state = VIDEOBUF_QUEUED;
			dprपूर्णांकk(2, "[%p/%d] buffer_queue - first queued\n",
				buf, buf->vb.i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम buffer_release(काष्ठा videobuf_queue *vq,
				काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा viu_buf *buf  = container_of(vb, काष्ठा viu_buf, vb);
	काष्ठा viu_fh  *fh   = vq->priv_data;
	काष्ठा viu_dev *dev  = (काष्ठा viu_dev *)fh->dev;

	viu_stop_dma(dev);
	मुक्त_buffer(vq, buf);
पूर्ण

अटल स्थिर काष्ठा videobuf_queue_ops viu_video_qops = अणु
	.buf_setup      = buffer_setup,
	.buf_prepare    = buffer_prepare,
	.buf_queue      = buffer_queue,
	.buf_release    = buffer_release,
पूर्ण;

/*
 * IOCTL vidioc handling
 */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, "viu", माप(cap->driver));
	strscpy(cap->card, "viu", माप(cap->card));
	strscpy(cap->bus_info, "platform:viu", माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	पूर्णांक index = f->index;

	अगर (f->index >= NUM_FORMATS)
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[index].fourcc;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा viu_fh *fh = priv;

	f->fmt.pix.width        = fh->width;
	f->fmt.pix.height       = fh->height;
	f->fmt.pix.field        = fh->vb_vidq.field;
	f->fmt.pix.pixelक्रमmat  = fh->fmt->pixelक्रमmat;
	f->fmt.pix.bytesperline =
			(f->fmt.pix.width * fh->fmt->depth) >> 3;
	f->fmt.pix.sizeimage	= fh->sizeimage;
	f->fmt.pix.colorspace	= V4L2_COLORSPACE_SMPTE170M;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा viu_fmt *fmt;
	अचिन्हित पूर्णांक maxw, maxh;

	fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	अगर (!fmt) अणु
		dprपूर्णांकk(1, "Fourcc format (0x%08x) invalid.",
			f->fmt.pix.pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	maxw  = norm_maxw();
	maxh  = norm_maxh();

	f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	अगर (f->fmt.pix.height < 32)
		f->fmt.pix.height = 32;
	अगर (f->fmt.pix.height > maxh)
		f->fmt.pix.height = maxh;
	अगर (f->fmt.pix.width < 48)
		f->fmt.pix.width = 48;
	अगर (f->fmt.pix.width > maxw)
		f->fmt.pix.width = maxw;
	f->fmt.pix.width &= ~0x03;
	f->fmt.pix.bytesperline =
		(f->fmt.pix.width * fmt->depth) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा viu_fh *fh = priv;
	पूर्णांक ret;

	ret = vidioc_try_fmt_cap(file, fh, f);
	अगर (ret < 0)
		वापस ret;

	fh->fmt           = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	fh->width         = f->fmt.pix.width;
	fh->height        = f->fmt.pix.height;
	fh->sizeimage     = f->fmt.pix.sizeimage;
	fh->vb_vidq.field = f->fmt.pix.field;
	fh->type          = f->type;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_overlay(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा viu_fh *fh = priv;

	f->fmt.win = fh->win;
	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_preview(काष्ठा viu_dev *dev, काष्ठा v4l2_winकरोw *win)
अणु
	क्रमागत v4l2_field field;
	पूर्णांक maxw, maxh;

	अगर (dev->ovbuf.base == शून्य)
		वापस -EINVAL;
	अगर (dev->ovfmt == शून्य)
		वापस -EINVAL;
	अगर (win->w.width < 48 || win->w.height < 32)
		वापस -EINVAL;

	field = win->field;
	maxw  = dev->crop_current.width;
	maxh  = dev->crop_current.height;

	अगर (field == V4L2_FIELD_ANY) अणु
		field = (win->w.height > maxh/2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_TOP;
	पूर्ण
	चयन (field) अणु
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
		maxh = maxh / 2;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	win->field = field;
	अगर (win->w.width > maxw)
		win->w.width = maxw;
	अगर (win->w.height > maxh)
		win->w.height = maxh;
	वापस 0;
पूर्ण

अंतरभूत व्योम viu_activate_overlay(काष्ठा viu_reg __iomem *vr)
अणु
	ioग_लिखो32be(reg_val.field_base_addr, &vr->field_base_addr);
	ioग_लिखो32be(reg_val.dma_inc, &vr->dma_inc);
	ioग_लिखो32be(reg_val.picture_count, &vr->picture_count);
पूर्ण

अटल पूर्णांक viu_setup_preview(काष्ठा viu_dev *dev, काष्ठा viu_fh *fh)
अणु
	पूर्णांक bpp;

	dprपूर्णांकk(1, "%s %dx%d\n", __func__,
		fh->win.w.width, fh->win.w.height);

	reg_val.status_cfg = 0;

	/* setup winकरोw */
	reg_val.picture_count = (fh->win.w.height / 2) << 16 |
				fh->win.w.width;

	/* setup color depth and dma increment */
	bpp = dev->ovfmt->depth / 8;
	चयन (bpp) अणु
	हाल 2:
		reg_val.status_cfg &= ~MODE_32BIT;
		reg_val.dma_inc = fh->win.w.width * 2;
		अवरोध;
	हाल 4:
		reg_val.status_cfg |= MODE_32BIT;
		reg_val.dma_inc = fh->win.w.width * 4;
		अवरोध;
	शेष:
		dprपूर्णांकk(0, "device doesn't support color depth(%d)\n",
			bpp * 8);
		वापस -EINVAL;
	पूर्ण

	dev->ovfield = fh->win.field;
	अगर (!V4L2_FIELD_HAS_BOTH(dev->ovfield))
		reg_val.dma_inc = 0;

	reg_val.status_cfg |= DMA_ACT | INT_DMA_END_EN | INT_FIELD_EN;

	/* setup the base address of the overlay buffer */
	reg_val.field_base_addr = (u32)(दीर्घ)dev->ovbuf.base;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_overlay(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा viu_fh  *fh  = priv;
	काष्ठा viu_dev *dev = (काष्ठा viu_dev *)fh->dev;
	अचिन्हित दीर्घ  flags;
	पूर्णांक err;

	err = verअगरy_preview(dev, &f->fmt.win);
	अगर (err)
		वापस err;

	fh->win = f->fmt.win;

	spin_lock_irqsave(&dev->slock, flags);
	viu_setup_preview(dev, fh);
	spin_unlock_irqrestore(&dev->slock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_overlay(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_overlay(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक on)
अणु
	काष्ठा viu_fh  *fh  = priv;
	काष्ठा viu_dev *dev = (काष्ठा viu_dev *)fh->dev;
	अचिन्हित दीर्घ  flags;

	अगर (on) अणु
		spin_lock_irqsave(&dev->slock, flags);
		viu_activate_overlay(dev->vr);
		dev->ovenable = 1;

		/* start dma */
		viu_start_dma(dev);
		spin_unlock_irqrestore(&dev->slock, flags);
	पूर्ण अन्यथा अणु
		viu_stop_dma(dev);
		dev->ovenable = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_framebuffer *arg)
अणु
	काष्ठा viu_fh  *fh = priv;
	काष्ठा viu_dev *dev = fh->dev;
	काष्ठा v4l2_framebuffer *fb = arg;

	*fb = dev->ovbuf;
	fb->capability = V4L2_FBUF_CAP_LIST_CLIPPING;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fbuf(काष्ठा file *file, व्योम *priv, स्थिर काष्ठा v4l2_framebuffer *arg)
अणु
	काष्ठा viu_fh  *fh = priv;
	काष्ठा viu_dev *dev = fh->dev;
	स्थिर काष्ठा v4l2_framebuffer *fb = arg;
	काष्ठा viu_fmt *fmt;

	अगर (!capable(CAP_SYS_ADMIN) && !capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	/* check args */
	fmt = क्रमmat_by_fourcc(fb->fmt.pixelक्रमmat);
	अगर (fmt == शून्य)
		वापस -EINVAL;

	/* ok, accept it */
	dev->ovbuf = *fb;
	dev->ovfmt = fmt;
	अगर (dev->ovbuf.fmt.bytesperline == 0) अणु
		dev->ovbuf.fmt.bytesperline =
			dev->ovbuf.fmt.width * fmt->depth / 8;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_reqbufs(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_requestbuffers *p)
अणु
	काष्ठा viu_fh *fh = priv;

	वापस videobuf_reqbufs(&fh->vb_vidq, p);
पूर्ण

अटल पूर्णांक vidioc_querybuf(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_buffer *p)
अणु
	काष्ठा viu_fh *fh = priv;

	वापस videobuf_querybuf(&fh->vb_vidq, p);
पूर्ण

अटल पूर्णांक vidioc_qbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *p)
अणु
	काष्ठा viu_fh *fh = priv;

	वापस videobuf_qbuf(&fh->vb_vidq, p);
पूर्ण

अटल पूर्णांक vidioc_dqbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *p)
अणु
	काष्ठा viu_fh *fh = priv;

	वापस videobuf_dqbuf(&fh->vb_vidq, p,
				file->f_flags & O_NONBLOCK);
पूर्ण

अटल पूर्णांक vidioc_streamon(काष्ठा file *file, व्योम *priv, क्रमागत v4l2_buf_type i)
अणु
	काष्ठा viu_fh *fh = priv;
	काष्ठा viu_dev *dev = fh->dev;

	अगर (fh->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	अगर (fh->type != i)
		वापस -EINVAL;

	अगर (dev->ovenable)
		dev->ovenable = 0;

	viu_start_dma(fh->dev);

	वापस videobuf_streamon(&fh->vb_vidq);
पूर्ण

अटल पूर्णांक vidioc_streamoff(काष्ठा file *file, व्योम *priv, क्रमागत v4l2_buf_type i)
अणु
	काष्ठा viu_fh  *fh = priv;

	अगर (fh->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	अगर (fh->type != i)
		वापस -EINVAL;

	viu_stop_dma(fh->dev);

	वापस videobuf_streamoff(&fh->vb_vidq);
पूर्ण

#घोषणा decoder_call(viu, o, f, args...) \
	v4l2_subdev_call(viu->decoder, o, f, ##args)

अटल पूर्णांक vidioc_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *std_id)
अणु
	काष्ठा viu_fh *fh = priv;

	decoder_call(fh->dev, video, querystd, std_id);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id)
अणु
	काष्ठा viu_fh *fh = priv;

	fh->dev->std = id;
	decoder_call(fh->dev, video, s_std, id);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *std_id)
अणु
	काष्ठा viu_fh *fh = priv;

	*std_id = fh->dev->std;
	वापस 0;
पूर्ण

/* only one input in this driver */
अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_input *inp)
अणु
	काष्ठा viu_fh *fh = priv;

	अगर (inp->index != 0)
		वापस -EINVAL;

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	inp->std = fh->dev->vdev->tvnorms;
	strscpy(inp->name, "Camera", माप(inp->name));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा viu_fh *fh = priv;

	अगर (i)
		वापस -EINVAL;

	decoder_call(fh->dev, video, s_routing, i, 0, 0);
	वापस 0;
पूर्ण

अंतरभूत व्योम viu_activate_next_buf(काष्ठा viu_dev *dev,
				काष्ठा viu_dmaqueue *viuq)
अणु
	काष्ठा viu_dmaqueue *vidq = viuq;
	काष्ठा viu_buf *buf;

	/* launch another DMA operation क्रम an active/queued buffer */
	अगर (!list_empty(&vidq->active)) अणु
		buf = list_entry(vidq->active.next, काष्ठा viu_buf,
					vb.queue);
		dprपूर्णांकk(1, "start another queued buffer: 0x%p\n", buf);
		buffer_activate(dev, buf);
	पूर्ण अन्यथा अगर (!list_empty(&vidq->queued)) अणु
		buf = list_entry(vidq->queued.next, काष्ठा viu_buf,
					vb.queue);
		list_del(&buf->vb.queue);

		dprपूर्णांकk(1, "start another queued buffer: 0x%p\n", buf);
		list_add_tail(&buf->vb.queue, &vidq->active);
		buf->vb.state = VIDEOBUF_ACTIVE;
		buffer_activate(dev, buf);
	पूर्ण
पूर्ण

अंतरभूत व्योम viu_शेष_settings(काष्ठा viu_reg __iomem *vr)
अणु
	ioग_लिखो32be(0x9512A254, &vr->luminance);
	ioग_लिखो32be(0x03310000, &vr->chroma_r);
	ioग_लिखो32be(0x06600F38, &vr->chroma_g);
	ioग_लिखो32be(0x00000409, &vr->chroma_b);
	ioग_लिखो32be(0x000000ff, &vr->alpha);
	ioग_लिखो32be(0x00000090, &vr->req_alarm);
	dprपूर्णांकk(1, "status reg: 0x%08x, field base: 0x%08x\n",
		ioपढ़ो32be(&vr->status_cfg), ioपढ़ो32be(&vr->field_base_addr));
पूर्ण

अटल व्योम viu_overlay_पूर्णांकr(काष्ठा viu_dev *dev, u32 status)
अणु
	काष्ठा viu_reg __iomem *vr = dev->vr;

	अगर (status & INT_DMA_END_STATUS)
		dev->dma_करोne = 1;

	अगर (status & INT_FIELD_STATUS) अणु
		अगर (dev->dma_करोne) अणु
			u32 addr = reg_val.field_base_addr;

			dev->dma_करोne = 0;
			अगर (status & FIELD_NO)
				addr += reg_val.dma_inc;

			ioग_लिखो32be(addr, &vr->field_base_addr);
			ioग_लिखो32be(reg_val.dma_inc, &vr->dma_inc);
			ioग_लिखो32be((status & 0xffc0ffff) |
				 (status & INT_ALL_STATUS) |
				 reg_val.status_cfg, &vr->status_cfg);
		पूर्ण अन्यथा अगर (status & INT_VSYNC_STATUS) अणु
			ioग_लिखो32be((status & 0xffc0ffff) |
				 (status & INT_ALL_STATUS) |
				 reg_val.status_cfg, &vr->status_cfg);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम viu_capture_पूर्णांकr(काष्ठा viu_dev *dev, u32 status)
अणु
	काष्ठा viu_dmaqueue *vidq = &dev->vidq;
	काष्ठा viu_reg __iomem *vr = dev->vr;
	काष्ठा viu_buf *buf;
	पूर्णांक field_num;
	पूर्णांक need_two;
	पूर्णांक dma_करोne = 0;

	field_num = status & FIELD_NO;
	need_two = V4L2_FIELD_HAS_BOTH(dev->capfield);

	अगर (status & INT_DMA_END_STATUS) अणु
		dma_करोne = 1;
		अगर (((field_num == 0) && (dev->field == 0)) ||
		    (field_num && (dev->field == 1)))
			dev->field++;
	पूर्ण

	अगर (status & INT_FIELD_STATUS) अणु
		dprपूर्णांकk(1, "irq: field %d, done %d\n",
			!!field_num, dma_करोne);
		अगर (unlikely(dev->first)) अणु
			अगर (field_num == 0) अणु
				dev->first = 0;
				dprपूर्णांकk(1, "activate first buf\n");
				viu_activate_next_buf(dev, vidq);
			पूर्ण अन्यथा
				dprपूर्णांकk(1, "wait field 0\n");
			वापस;
		पूर्ण

		/* setup buffer address क्रम next dma operation */
		अगर (!list_empty(&vidq->active)) अणु
			u32 addr = reg_val.field_base_addr;

			अगर (field_num && need_two) अणु
				addr += reg_val.dma_inc;
				dprपूर्णांकk(1, "field 1, 0x%lx, dev field %d\n",
					(अचिन्हित दीर्घ)addr, dev->field);
			पूर्ण
			ioग_लिखो32be(addr, &vr->field_base_addr);
			ioग_लिखो32be(reg_val.dma_inc, &vr->dma_inc);
			ioग_लिखो32be((status & 0xffc0ffff) |
				 (status & INT_ALL_STATUS) |
				 reg_val.status_cfg, &vr->status_cfg);
			वापस;
		पूर्ण
	पूर्ण

	अगर (dma_करोne && field_num && (dev->field == 2)) अणु
		dev->field = 0;
		buf = list_entry(vidq->active.next,
				 काष्ठा viu_buf, vb.queue);
		dprपूर्णांकk(1, "viu/0: [%p/%d] 0x%lx/0x%lx: dma complete\n",
			buf, buf->vb.i,
			(अचिन्हित दीर्घ)videobuf_to_dma_contig(&buf->vb),
			(अचिन्हित दीर्घ)ioपढ़ो32be(&vr->field_base_addr));

		अगर (रुकोqueue_active(&buf->vb.करोne)) अणु
			list_del(&buf->vb.queue);
			buf->vb.ts = kसमय_get_ns();
			buf->vb.state = VIDEOBUF_DONE;
			buf->vb.field_count++;
			wake_up(&buf->vb.करोne);
		पूर्ण
		/* activate next dma buffer */
		viu_activate_next_buf(dev, vidq);
	पूर्ण
पूर्ण

अटल irqवापस_t viu_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा viu_dev *dev  = (काष्ठा viu_dev *)dev_id;
	काष्ठा viu_reg __iomem *vr = dev->vr;
	u32 status;
	u32 error;

	status = ioपढ़ो32be(&vr->status_cfg);

	अगर (status & INT_ERROR_STATUS) अणु
		dev->irqs.error_irq++;
		error = status & ERR_MASK;
		अगर (error)
			dprपूर्णांकk(1, "Err: error(%d), times:%d!\n",
				error >> 4, dev->irqs.error_irq);
		/* Clear पूर्णांकerrupt error bit and error flags */
		ioग_लिखो32be((status & 0xffc0ffff) | INT_ERROR_STATUS,
			    &vr->status_cfg);
	पूर्ण

	अगर (status & INT_DMA_END_STATUS) अणु
		dev->irqs.dma_end_irq++;
		dev->dma_करोne = 1;
		dprपूर्णांकk(2, "VIU DMA end interrupt times: %d\n",
					dev->irqs.dma_end_irq);
	पूर्ण

	अगर (status & INT_HSYNC_STATUS)
		dev->irqs.hsync_irq++;

	अगर (status & INT_FIELD_STATUS) अणु
		dev->irqs.field_irq++;
		dprपूर्णांकk(2, "VIU field interrupt times: %d\n",
					dev->irqs.field_irq);
	पूर्ण

	अगर (status & INT_VSTART_STATUS)
		dev->irqs.vstart_irq++;

	अगर (status & INT_VSYNC_STATUS) अणु
		dev->irqs.vsync_irq++;
		dprपूर्णांकk(2, "VIU vsync interrupt times: %d\n",
			dev->irqs.vsync_irq);
	पूर्ण

	/* clear all pending irqs */
	status = ioपढ़ो32be(&vr->status_cfg);
	ioग_लिखो32be((status & 0xffc0ffff) | (status & INT_ALL_STATUS),
		    &vr->status_cfg);

	अगर (dev->ovenable) अणु
		viu_overlay_पूर्णांकr(dev, status);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Capture mode */
	viu_capture_पूर्णांकr(dev, status);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * File operations क्रम the device
 */
अटल पूर्णांक viu_खोलो(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा viu_dev *dev = video_get_drvdata(vdev);
	काष्ठा viu_fh *fh;
	काष्ठा viu_reg __iomem *vr;
	पूर्णांक minor = vdev->minor;
	u32 status_cfg;

	dprपूर्णांकk(1, "viu: open (minor=%d)\n", minor);

	dev->users++;
	अगर (dev->users > 1) अणु
		dev->users--;
		वापस -EBUSY;
	पूर्ण

	vr = dev->vr;

	dprपूर्णांकk(1, "open minor=%d type=%s users=%d\n", minor,
		v4l2_type_names[V4L2_BUF_TYPE_VIDEO_CAPTURE], dev->users);

	अगर (mutex_lock_पूर्णांकerruptible(&dev->lock)) अणु
		dev->users--;
		वापस -ERESTARTSYS;
	पूर्ण

	/* allocate and initialize per filehandle data */
	fh = kzalloc(माप(*fh), GFP_KERNEL);
	अगर (!fh) अणु
		dev->users--;
		mutex_unlock(&dev->lock);
		वापस -ENOMEM;
	पूर्ण

	v4l2_fh_init(&fh->fh, vdev);
	file->निजी_data = fh;
	fh->dev = dev;

	fh->type     = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fh->fmt      = क्रमmat_by_fourcc(V4L2_PIX_FMT_RGB32);
	fh->width    = norm_maxw();
	fh->height   = norm_maxh();
	dev->crop_current.width  = fh->width;
	dev->crop_current.height = fh->height;

	dprपूर्णांकk(1, "Open: fh=%p, dev=%p, dev->vidq=%p\n", fh, dev, &dev->vidq);
	dprपूर्णांकk(1, "Open: list_empty queued=%d\n",
		list_empty(&dev->vidq.queued));
	dprपूर्णांकk(1, "Open: list_empty active=%d\n",
		list_empty(&dev->vidq.active));

	viu_शेष_settings(vr);

	status_cfg = ioपढ़ो32be(&vr->status_cfg);
	ioग_लिखो32be(status_cfg & ~(INT_VSYNC_EN | INT_HSYNC_EN |
				INT_FIELD_EN | INT_VSTART_EN |
				INT_DMA_END_EN | INT_ERROR_EN | INT_ECC_EN),
		    &vr->status_cfg);

	status_cfg = ioपढ़ो32be(&vr->status_cfg);
	ioग_लिखो32be(status_cfg | INT_ALL_STATUS, &vr->status_cfg);

	spin_lock_init(&fh->vbq_lock);
	videobuf_queue_dma_contig_init(&fh->vb_vidq, &viu_video_qops,
				       dev->dev, &fh->vbq_lock,
				       fh->type, V4L2_FIELD_INTERLACED,
				       माप(काष्ठा viu_buf), fh,
				       &fh->dev->lock);
	v4l2_fh_add(&fh->fh);
	mutex_unlock(&dev->lock);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार viu_पढ़ो(काष्ठा file *file, अक्षर __user *data, माप_प्रकार count,
			loff_t *ppos)
अणु
	काष्ठा viu_fh *fh = file->निजी_data;
	काष्ठा viu_dev *dev = fh->dev;
	पूर्णांक ret = 0;

	dprपूर्णांकk(2, "%s\n", __func__);
	अगर (dev->ovenable)
		dev->ovenable = 0;

	अगर (fh->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&dev->lock))
			वापस -ERESTARTSYS;
		viu_start_dma(dev);
		ret = videobuf_पढ़ो_stream(&fh->vb_vidq, data, count,
				ppos, 0, file->f_flags & O_NONBLOCK);
		mutex_unlock(&dev->lock);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल __poll_t viu_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा viu_fh *fh = file->निजी_data;
	काष्ठा videobuf_queue *q = &fh->vb_vidq;
	काष्ठा viu_dev *dev = fh->dev;
	__poll_t req_events = poll_requested_events(रुको);
	__poll_t res = v4l2_ctrl_poll(file, रुको);

	अगर (V4L2_BUF_TYPE_VIDEO_CAPTURE != fh->type)
		वापस EPOLLERR;

	अगर (!(req_events & (EPOLLIN | EPOLLRDNORM)))
		वापस res;

	mutex_lock(&dev->lock);
	res |= videobuf_poll_stream(file, q, रुको);
	mutex_unlock(&dev->lock);
	वापस res;
पूर्ण

अटल पूर्णांक viu_release(काष्ठा file *file)
अणु
	काष्ठा viu_fh *fh = file->निजी_data;
	काष्ठा viu_dev *dev = fh->dev;
	पूर्णांक minor = video_devdata(file)->minor;

	mutex_lock(&dev->lock);
	viu_stop_dma(dev);
	videobuf_stop(&fh->vb_vidq);
	videobuf_mmap_मुक्त(&fh->vb_vidq);
	v4l2_fh_del(&fh->fh);
	v4l2_fh_निकास(&fh->fh);
	mutex_unlock(&dev->lock);

	kमुक्त(fh);

	dev->users--;
	dprपूर्णांकk(1, "close (minor=%d, users=%d)\n",
		minor, dev->users);
	वापस 0;
पूर्ण

अटल व्योम viu_reset(काष्ठा viu_reg __iomem *reg)
अणु
	ioग_लिखो32be(0, &reg->status_cfg);
	ioग_लिखो32be(0x9512a254, &reg->luminance);
	ioग_लिखो32be(0x03310000, &reg->chroma_r);
	ioग_लिखो32be(0x06600f38, &reg->chroma_g);
	ioग_लिखो32be(0x00000409, &reg->chroma_b);
	ioग_लिखो32be(0, &reg->field_base_addr);
	ioग_लिखो32be(0, &reg->dma_inc);
	ioग_लिखो32be(0x01e002d0, &reg->picture_count);
	ioग_लिखो32be(0x00000090, &reg->req_alarm);
	ioग_लिखो32be(0x000000ff, &reg->alpha);
पूर्ण

अटल पूर्णांक viu_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा viu_fh *fh = file->निजी_data;
	काष्ठा viu_dev *dev = fh->dev;
	पूर्णांक ret;

	dprपूर्णांकk(1, "mmap called, vma=%p\n", vma);

	अगर (mutex_lock_पूर्णांकerruptible(&dev->lock))
		वापस -ERESTARTSYS;
	ret = videobuf_mmap_mapper(&fh->vb_vidq, vma);
	mutex_unlock(&dev->lock);

	dprपूर्णांकk(1, "vma start=0x%08lx, size=%ld, ret=%d\n",
		(अचिन्हित दीर्घ)vma->vm_start,
		(अचिन्हित दीर्घ)vma->vm_end-(अचिन्हित दीर्घ)vma->vm_start,
		ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations viu_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= viu_खोलो,
	.release	= viu_release,
	.पढ़ो		= viu_पढ़ो,
	.poll		= viu_poll,
	.unlocked_ioctl	= video_ioctl2, /* V4L2 ioctl handler */
	.mmap		= viu_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops viu_ioctl_ops = अणु
	.vidioc_querycap	= vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap  = vidioc_क्रमागत_fmt,
	.vidioc_g_fmt_vid_cap     = vidioc_g_fmt_cap,
	.vidioc_try_fmt_vid_cap   = vidioc_try_fmt_cap,
	.vidioc_s_fmt_vid_cap     = vidioc_s_fmt_cap,
	.vidioc_क्रमागत_fmt_vid_overlay = vidioc_क्रमागत_fmt,
	.vidioc_g_fmt_vid_overlay = vidioc_g_fmt_overlay,
	.vidioc_try_fmt_vid_overlay = vidioc_try_fmt_overlay,
	.vidioc_s_fmt_vid_overlay = vidioc_s_fmt_overlay,
	.vidioc_overlay	      = vidioc_overlay,
	.vidioc_g_fbuf	      = vidioc_g_fbuf,
	.vidioc_s_fbuf	      = vidioc_s_fbuf,
	.vidioc_reqbufs       = vidioc_reqbufs,
	.vidioc_querybuf      = vidioc_querybuf,
	.vidioc_qbuf          = vidioc_qbuf,
	.vidioc_dqbuf         = vidioc_dqbuf,
	.vidioc_g_std         = vidioc_g_std,
	.vidioc_s_std         = vidioc_s_std,
	.vidioc_querystd      = vidioc_querystd,
	.vidioc_क्रमागत_input    = vidioc_क्रमागत_input,
	.vidioc_g_input       = vidioc_g_input,
	.vidioc_s_input       = vidioc_s_input,
	.vidioc_streamon      = vidioc_streamon,
	.vidioc_streamoff     = vidioc_streamoff,
	.vidioc_log_status    = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा video_device viu_ढाँचा = अणु
	.name		= "FSL viu",
	.fops		= &viu_fops,
	.minor		= -1,
	.ioctl_ops	= &viu_ioctl_ops,
	.release	= video_device_release,

	.tvnorms        = V4L2_STD_NTSC_M | V4L2_STD_PAL,
	.device_caps	= V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
			  V4L2_CAP_VIDEO_OVERLAY | V4L2_CAP_READWRITE,
पूर्ण;

अटल पूर्णांक viu_of_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा viu_dev *viu_dev;
	काष्ठा video_device *vdev;
	काष्ठा resource r;
	काष्ठा viu_reg __iomem *viu_regs;
	काष्ठा i2c_adapter *ad;
	पूर्णांक ret, viu_irq;
	काष्ठा clk *clk;

	ret = of_address_to_resource(op->dev.of_node, 0, &r);
	अगर (ret) अणु
		dev_err(&op->dev, "Can't parse device node resource\n");
		वापस -ENODEV;
	पूर्ण

	viu_irq = irq_of_parse_and_map(op->dev.of_node, 0);
	अगर (!viu_irq) अणु
		dev_err(&op->dev, "Error while mapping the irq\n");
		वापस -EINVAL;
	पूर्ण

	/* request mem region */
	अगर (!devm_request_mem_region(&op->dev, r.start,
				     माप(काष्ठा viu_reg), DRV_NAME)) अणु
		dev_err(&op->dev, "Error while requesting mem region\n");
		ret = -EBUSY;
		जाओ err_irq;
	पूर्ण

	/* remap रेजिस्टरs */
	viu_regs = devm_ioremap(&op->dev, r.start, माप(काष्ठा viu_reg));
	अगर (!viu_regs) अणु
		dev_err(&op->dev, "Can't map register set\n");
		ret = -ENOMEM;
		जाओ err_irq;
	पूर्ण

	/* Prepare our निजी काष्ठाure */
	viu_dev = devm_kzalloc(&op->dev, माप(काष्ठा viu_dev), GFP_ATOMIC);
	अगर (!viu_dev) अणु
		dev_err(&op->dev, "Can't allocate private structure\n");
		ret = -ENOMEM;
		जाओ err_irq;
	पूर्ण

	viu_dev->vr = viu_regs;
	viu_dev->irq = viu_irq;
	viu_dev->dev = &op->dev;

	/* init video dma queues */
	INIT_LIST_HEAD(&viu_dev->vidq.active);
	INIT_LIST_HEAD(&viu_dev->vidq.queued);

	snम_लिखो(viu_dev->v4l2_dev.name,
		 माप(viu_dev->v4l2_dev.name), "%s", "VIU");
	ret = v4l2_device_रेजिस्टर(viu_dev->dev, &viu_dev->v4l2_dev);
	अगर (ret < 0) अणु
		dev_err(&op->dev, "v4l2_device_register() failed: %d\n", ret);
		जाओ err_irq;
	पूर्ण

	ad = i2c_get_adapter(0);
	अगर (!ad) अणु
		ret = -EFAULT;
		dev_err(&op->dev, "couldn't get i2c adapter\n");
		जाओ err_v4l2;
	पूर्ण

	v4l2_ctrl_handler_init(&viu_dev->hdl, 5);
	अगर (viu_dev->hdl.error) अणु
		ret = viu_dev->hdl.error;
		dev_err(&op->dev, "couldn't register control\n");
		जाओ err_i2c;
	पूर्ण
	/* This control handler will inherit the control(s) from the
	   sub-device(s). */
	viu_dev->v4l2_dev.ctrl_handler = &viu_dev->hdl;
	viu_dev->decoder = v4l2_i2c_new_subdev(&viu_dev->v4l2_dev, ad,
			"saa7113", VIU_VIDEO_DECODER_ADDR, शून्य);

	समयr_setup(&viu_dev->vidq.समयout, viu_vid_समयout, 0);
	viu_dev->std = V4L2_STD_NTSC_M;
	viu_dev->first = 1;

	/* Allocate memory क्रम video device */
	vdev = video_device_alloc();
	अगर (vdev == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_hdl;
	पूर्ण

	*vdev = viu_ढाँचा;

	vdev->v4l2_dev = &viu_dev->v4l2_dev;

	viu_dev->vdev = vdev;

	/* initialize locks */
	mutex_init(&viu_dev->lock);
	viu_dev->vdev->lock = &viu_dev->lock;
	spin_lock_init(&viu_dev->slock);

	video_set_drvdata(viu_dev->vdev, viu_dev);

	mutex_lock(&viu_dev->lock);

	ret = video_रेजिस्टर_device(viu_dev->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0) अणु
		video_device_release(viu_dev->vdev);
		जाओ err_unlock;
	पूर्ण

	/* enable VIU घड़ी */
	clk = devm_clk_get(&op->dev, "ipg");
	अगर (IS_ERR(clk)) अणु
		dev_err(&op->dev, "failed to lookup the clock!\n");
		ret = PTR_ERR(clk);
		जाओ err_vdev;
	पूर्ण
	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(&op->dev, "failed to enable the clock!\n");
		जाओ err_vdev;
	पूर्ण
	viu_dev->clk = clk;

	/* reset VIU module */
	viu_reset(viu_dev->vr);

	/* install पूर्णांकerrupt handler */
	अगर (request_irq(viu_dev->irq, viu_पूर्णांकr, 0, "viu", (व्योम *)viu_dev)) अणु
		dev_err(&op->dev, "Request VIU IRQ failed.\n");
		ret = -ENODEV;
		जाओ err_clk;
	पूर्ण

	mutex_unlock(&viu_dev->lock);

	dev_info(&op->dev, "Freescale VIU Video Capture Board\n");
	वापस ret;

err_clk:
	clk_disable_unprepare(viu_dev->clk);
err_vdev:
	video_unरेजिस्टर_device(viu_dev->vdev);
err_unlock:
	mutex_unlock(&viu_dev->lock);
err_hdl:
	v4l2_ctrl_handler_मुक्त(&viu_dev->hdl);
err_i2c:
	i2c_put_adapter(ad);
err_v4l2:
	v4l2_device_unरेजिस्टर(&viu_dev->v4l2_dev);
err_irq:
	irq_dispose_mapping(viu_irq);
	वापस ret;
पूर्ण

अटल पूर्णांक viu_of_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा v4l2_device *v4l2_dev = platक्रमm_get_drvdata(op);
	काष्ठा viu_dev *dev = container_of(v4l2_dev, काष्ठा viu_dev, v4l2_dev);
	काष्ठा v4l2_subdev *sdev = list_entry(v4l2_dev->subdevs.next,
					      काष्ठा v4l2_subdev, list);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sdev);

	मुक्त_irq(dev->irq, (व्योम *)dev);
	irq_dispose_mapping(dev->irq);

	clk_disable_unprepare(dev->clk);

	v4l2_ctrl_handler_मुक्त(&dev->hdl);
	video_unरेजिस्टर_device(dev->vdev);
	i2c_put_adapter(client->adapter);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक viu_suspend(काष्ठा platक्रमm_device *op, pm_message_t state)
अणु
	काष्ठा v4l2_device *v4l2_dev = platक्रमm_get_drvdata(op);
	काष्ठा viu_dev *dev = container_of(v4l2_dev, काष्ठा viu_dev, v4l2_dev);

	clk_disable(dev->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक viu_resume(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा v4l2_device *v4l2_dev = platक्रमm_get_drvdata(op);
	काष्ठा viu_dev *dev = container_of(v4l2_dev, काष्ठा viu_dev, v4l2_dev);

	clk_enable(dev->clk);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Initialization and module stuff
 */
अटल स्थिर काष्ठा of_device_id mpc512x_viu_of_match[] = अणु
	अणु
		.compatible = "fsl,mpc5121-viu",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mpc512x_viu_of_match);

अटल काष्ठा platक्रमm_driver viu_of_platक्रमm_driver = अणु
	.probe = viu_of_probe,
	.हटाओ = viu_of_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend = viu_suspend,
	.resume = viu_resume,
#पूर्ण_अगर
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = mpc512x_viu_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(viu_of_platक्रमm_driver);

MODULE_DESCRIPTION("Freescale Video-In(VIU)");
MODULE_AUTHOR("Hongjun Chen");
MODULE_LICENSE("GPL");
MODULE_VERSION(VIU_VERSION);
