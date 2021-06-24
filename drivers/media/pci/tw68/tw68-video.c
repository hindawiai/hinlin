<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  tw68 functions to handle video data
 *
 *  Much of this code is derived from the cx88 and sa7134 drivers, which
 *  were in turn derived from the bt87x driver.  The original work was by
 *  Gerd Knorr; more recently the code was enhanced by Mauro Carvalho Chehab,
 *  Hans Verkuil, Andy Walls and many others.  Their work is gratefully
 *  acknowledged.  Full credit goes to them - any problems within this code
 *  are mine.
 *
 *  Copyright (C) 2009  William M. Brack
 *
 *  Refactored and updated to the latest v4l core frameworks:
 *
 *  Copyright (C) 2014 Hans Verkuil <hverkuil@xs4all.nl>
 */

#समावेश <linux/module.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-dma-sg.h>

#समावेश "tw68.h"
#समावेश "tw68-reg.h"

/* ------------------------------------------------------------------ */
/* data काष्ठाs क्रम video                                             */
/*
 * FIXME -
 * Note that the saa7134 has क्रमmats, e.g. YUV420, which are classअगरied
 * as "planar".  These affect overlay mode, and are flagged with a field
 * ".planar" in the क्रमmat.  Do we need to implement this in this driver?
 */
अटल स्थिर काष्ठा tw68_क्रमmat क्रमmats[] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB555,
		.depth		= 16,
		.twक्रमmat	= ColorFormatRGB15,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB555X,
		.depth		= 16,
		.twक्रमmat	= ColorFormatRGB15 | ColorFormatBSWAP,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB565,
		.depth		= 16,
		.twक्रमmat	= ColorFormatRGB16,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB565X,
		.depth		= 16,
		.twक्रमmat	= ColorFormatRGB16 | ColorFormatBSWAP,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_BGR24,
		.depth		= 24,
		.twक्रमmat	= ColorFormatRGB24,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB24,
		.depth		= 24,
		.twक्रमmat	= ColorFormatRGB24 | ColorFormatBSWAP,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_BGR32,
		.depth		= 32,
		.twक्रमmat	= ColorFormatRGB32,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB32,
		.depth		= 32,
		.twक्रमmat	= ColorFormatRGB32 | ColorFormatBSWAP |
				  ColorFormatWSWAP,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_YUYV,
		.depth		= 16,
		.twक्रमmat	= ColorFormatYUY2,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_UYVY,
		.depth		= 16,
		.twक्रमmat	= ColorFormatYUY2 | ColorFormatBSWAP,
	पूर्ण
पूर्ण;
#घोषणा FORMATS ARRAY_SIZE(क्रमmats)

#घोषणा NORM_625_50			\
		.h_delay	= 3,	\
		.h_delay0	= 133,	\
		.h_start	= 0,	\
		.h_stop		= 719,	\
		.v_delay	= 24,	\
		.vbi_v_start_0	= 7,	\
		.vbi_v_stop_0	= 22,	\
		.video_v_start	= 24,	\
		.video_v_stop	= 311,	\
		.vbi_v_start_1	= 319

#घोषणा NORM_525_60			\
		.h_delay	= 8,	\
		.h_delay0	= 138,	\
		.h_start	= 0,	\
		.h_stop		= 719,	\
		.v_delay	= 22,	\
		.vbi_v_start_0	= 10,	\
		.vbi_v_stop_0	= 21,	\
		.video_v_start	= 22,	\
		.video_v_stop	= 262,	\
		.vbi_v_start_1	= 273

/*
 * The following table is searched by tw68_s_std, first क्रम a specअगरic
 * match, then क्रम an entry which contains the desired id.  The table
 * entries should thereक्रमe be ordered in ascending order of specअगरicity.
 */
अटल स्थिर काष्ठा tw68_tvnorm tvnorms[] = अणु
	अणु
		.name		= "PAL", /* स्वतःdetect */
		.id		= V4L2_STD_PAL,
		NORM_625_50,

		.sync_control	= 0x18,
		.luma_control	= 0x40,
		.chroma_ctrl1	= 0x81,
		.chroma_gain	= 0x2a,
		.chroma_ctrl2	= 0x06,
		.vgate_misc	= 0x1c,
		.क्रमmat		= VideoFormatPALBDGHI,
	पूर्ण, अणु
		.name		= "NTSC",
		.id		= V4L2_STD_NTSC,
		NORM_525_60,

		.sync_control	= 0x59,
		.luma_control	= 0x40,
		.chroma_ctrl1	= 0x89,
		.chroma_gain	= 0x2a,
		.chroma_ctrl2	= 0x0e,
		.vgate_misc	= 0x18,
		.क्रमmat		= VideoFormatNTSC,
	पूर्ण, अणु
		.name		= "SECAM",
		.id		= V4L2_STD_SECAM,
		NORM_625_50,

		.sync_control	= 0x18,
		.luma_control	= 0x1b,
		.chroma_ctrl1	= 0xd1,
		.chroma_gain	= 0x80,
		.chroma_ctrl2	= 0x00,
		.vgate_misc	= 0x1c,
		.क्रमmat		= VideoFormatSECAM,
	पूर्ण, अणु
		.name		= "PAL-M",
		.id		= V4L2_STD_PAL_M,
		NORM_525_60,

		.sync_control	= 0x59,
		.luma_control	= 0x40,
		.chroma_ctrl1	= 0xb9,
		.chroma_gain	= 0x2a,
		.chroma_ctrl2	= 0x0e,
		.vgate_misc	= 0x18,
		.क्रमmat		= VideoFormatPALM,
	पूर्ण, अणु
		.name		= "PAL-Nc",
		.id		= V4L2_STD_PAL_Nc,
		NORM_625_50,

		.sync_control	= 0x18,
		.luma_control	= 0x40,
		.chroma_ctrl1	= 0xa1,
		.chroma_gain	= 0x2a,
		.chroma_ctrl2	= 0x06,
		.vgate_misc	= 0x1c,
		.क्रमmat		= VideoFormatPALNC,
	पूर्ण, अणु
		.name		= "PAL-60",
		.id		= V4L2_STD_PAL_60,
		.h_delay	= 186,
		.h_start	= 0,
		.h_stop		= 719,
		.v_delay	= 26,
		.video_v_start	= 23,
		.video_v_stop	= 262,
		.vbi_v_start_0	= 10,
		.vbi_v_stop_0	= 21,
		.vbi_v_start_1	= 273,

		.sync_control	= 0x18,
		.luma_control	= 0x40,
		.chroma_ctrl1	= 0x81,
		.chroma_gain	= 0x2a,
		.chroma_ctrl2	= 0x06,
		.vgate_misc	= 0x1c,
		.क्रमmat		= VideoFormatPAL60,
	पूर्ण
पूर्ण;
#घोषणा TVNORMS ARRAY_SIZE(tvnorms)

अटल स्थिर काष्ठा tw68_क्रमmat *क्रमmat_by_fourcc(अचिन्हित पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < FORMATS; i++)
		अगर (क्रमmats[i].fourcc == fourcc)
			वापस क्रमmats+i;
	वापस शून्य;
पूर्ण


/* ------------------------------------------------------------------ */
/*
 * Note that the cropping rectangles are described in terms of a single
 * frame, i.e. line positions are only 1/2 the पूर्णांकerlaced equivalent
 */
अटल व्योम set_tvnorm(काष्ठा tw68_dev *dev, स्थिर काष्ठा tw68_tvnorm *norm)
अणु
	अगर (norm != dev->tvnorm) अणु
		dev->width = 720;
		dev->height = (norm->id & V4L2_STD_525_60) ? 480 : 576;
		dev->tvnorm = norm;
		tw68_set_tvnorm_hw(dev);
	पूर्ण
पूर्ण

/*
 * tw68_set_scale
 *
 * Scaling and Cropping क्रम video decoding
 *
 * We are working with 3 values क्रम horizontal and vertical - scale,
 * delay and active.
 *
 * HACTIVE represent the actual number of pixels in the "usable" image,
 * beक्रमe scaling.  HDELAY represents the number of pixels skipped
 * between the start of the horizontal sync and the start of the image.
 * HSCALE is calculated using the क्रमmula
 *	HSCALE = (HACTIVE / (#pixels desired)) * 256
 *
 * The vertical रेजिस्टरs are similar, except based upon the total number
 * of lines in the image, and the first line of the image (i.e. ignoring
 * vertical sync and VBI).
 *
 * Note that the number of bytes reaching the FIFO (and hence needing
 * to be processed by the DMAP program) is completely dependent upon
 * these values, especially HSCALE.
 *
 * Parameters:
 *	@dev		poपूर्णांकer to the device काष्ठाure, needed क्रम
 *			getting current norm (as well as debug prपूर्णांक)
 *	@width		actual image width (from user buffer)
 *	@height		actual image height
 *	@field		indicates Top, Bottom or Interlaced
 */
अटल पूर्णांक tw68_set_scale(काष्ठा tw68_dev *dev, अचिन्हित पूर्णांक width,
			  अचिन्हित पूर्णांक height, क्रमागत v4l2_field field)
अणु
	स्थिर काष्ठा tw68_tvnorm *norm = dev->tvnorm;
	/* set inभागidually क्रम debugging clarity */
	पूर्णांक hactive, hdelay, hscale;
	पूर्णांक vactive, vdelay, vscale;
	पूर्णांक comb;

	अगर (V4L2_FIELD_HAS_BOTH(field))	/* अगर field is पूर्णांकerlaced */
		height /= 2;		/* we must set क्रम 1-frame */

	pr_debug("%s: width=%d, height=%d, both=%d\n"
		 "  tvnorm h_delay=%d, h_start=%d, h_stop=%d, v_delay=%d, v_start=%d, v_stop=%d\n",
		__func__, width, height, V4L2_FIELD_HAS_BOTH(field),
		norm->h_delay, norm->h_start, norm->h_stop,
		norm->v_delay, norm->video_v_start,
		norm->video_v_stop);

	चयन (dev->vdecoder) अणु
	हाल TW6800:
		hdelay = norm->h_delay0;
		अवरोध;
	शेष:
		hdelay = norm->h_delay;
		अवरोध;
	पूर्ण

	hdelay += norm->h_start;
	hactive = norm->h_stop - norm->h_start + 1;

	hscale = (hactive * 256) / (width);

	vdelay = norm->v_delay;
	vactive = ((norm->id & V4L2_STD_525_60) ? 524 : 624) / 2 - norm->video_v_start;
	vscale = (vactive * 256) / height;

	pr_debug("%s: %dx%d [%s%s,%s]\n", __func__,
		width, height,
		V4L2_FIELD_HAS_TOP(field)    ? "T" : "",
		V4L2_FIELD_HAS_BOTTOM(field) ? "B" : "",
		v4l2_norm_to_name(dev->tvnorm->id));
	pr_debug("%s: hactive=%d, hdelay=%d, hscale=%d; vactive=%d, vdelay=%d, vscale=%d\n",
		 __func__,
		hactive, hdelay, hscale, vactive, vdelay, vscale);

	comb =	((vdelay & 0x300)  >> 2) |
		((vactive & 0x300) >> 4) |
		((hdelay & 0x300)  >> 6) |
		((hactive & 0x300) >> 8);
	pr_debug("%s: setting CROP_HI=%02x, VDELAY_LO=%02x, VACTIVE_LO=%02x, HDELAY_LO=%02x, HACTIVE_LO=%02x\n",
		__func__, comb, vdelay, vactive, hdelay, hactive);
	tw_ग_लिखोb(TW68_CROP_HI, comb);
	tw_ग_लिखोb(TW68_VDELAY_LO, vdelay & 0xff);
	tw_ग_लिखोb(TW68_VACTIVE_LO, vactive & 0xff);
	tw_ग_लिखोb(TW68_HDELAY_LO, hdelay & 0xff);
	tw_ग_लिखोb(TW68_HACTIVE_LO, hactive & 0xff);

	comb = ((vscale & 0xf00) >> 4) | ((hscale & 0xf00) >> 8);
	pr_debug("%s: setting SCALE_HI=%02x, VSCALE_LO=%02x, HSCALE_LO=%02x\n",
		 __func__, comb, vscale, hscale);
	tw_ग_लिखोb(TW68_SCALE_HI, comb);
	tw_ग_लिखोb(TW68_VSCALE_LO, vscale);
	tw_ग_लिखोb(TW68_HSCALE_LO, hscale);

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

पूर्णांक tw68_video_start_dma(काष्ठा tw68_dev *dev, काष्ठा tw68_buf *buf)
अणु
	/* Set cropping and scaling */
	tw68_set_scale(dev, dev->width, dev->height, dev->field);
	/*
	 *  Set start address क्रम RISC program.  Note that अगर the DMAP
	 *  processor is currently running, it must be stopped beक्रमe
	 *  a new address can be set.
	 */
	tw_clearl(TW68_DMAC, TW68_DMAP_EN);
	tw_ग_लिखोl(TW68_DMAP_SA, buf->dma);
	/* Clear any pending पूर्णांकerrupts */
	tw_ग_लिखोl(TW68_INTSTAT, dev->board_virqmask);
	/* Enable the risc engine and the fअगरo */
	tw_anकरोrl(TW68_DMAC, 0xff, dev->fmt->twक्रमmat |
		ColorFormatGamma | TW68_DMAP_EN | TW68_FIFO_EN);
	dev->pci_irqmask |= dev->board_virqmask;
	tw_setl(TW68_INTMASK, dev->pci_irqmask);
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

/* calc max # of buffers from size (must not exceed the 4MB भव
 * address space per DMA channel) */
अटल पूर्णांक tw68_buffer_count(अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक maxcount;

	maxcount = (4 * 1024 * 1024) / roundup(size, PAGE_SIZE);
	अगर (count > maxcount)
		count = maxcount;
	वापस count;
पूर्ण

/* ------------------------------------------------------------- */
/* vb2 queue operations                                          */

अटल पूर्णांक tw68_queue_setup(काष्ठा vb2_queue *q,
			   अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा tw68_dev *dev = vb2_get_drv_priv(q);
	अचिन्हित tot_bufs = q->num_buffers + *num_buffers;
	अचिन्हित size = (dev->fmt->depth * dev->width * dev->height) >> 3;

	अगर (tot_bufs < 2)
		tot_bufs = 2;
	tot_bufs = tw68_buffer_count(size, tot_bufs);
	*num_buffers = tot_bufs - q->num_buffers;
	/*
	 * We allow create_bufs, but only अगर the sizeimage is >= as the
	 * current sizeimage. The tw68_buffer_count calculation becomes quite
	 * dअगरficult otherwise.
	 */
	अगर (*num_planes)
		वापस sizes[0] < size ? -EINVAL : 0;
	*num_planes = 1;
	sizes[0] = size;

	वापस 0;
पूर्ण

/*
 * The risc program क्रम each buffers works as follows: it starts with a simple
 * 'JUMP to addr + 8', which is effectively a NOP. Then the program to DMA the
 * buffer follows and at the end we have a JUMP back to the start + 8 (skipping
 * the initial JUMP).
 *
 * This is the program of the first buffer to be queued अगर the active list is
 * empty and it just keeps DMAing this buffer without generating any पूर्णांकerrupts.
 *
 * If a new buffer is added then the initial JUMP in the program generates an
 * पूर्णांकerrupt as well which संकेतs that the previous buffer has been DMAed
 * successfully and that it can be वापसed to userspace.
 *
 * It also sets the final jump of the previous buffer to the start of the new
 * buffer, thus chaining the new buffer पूर्णांकo the DMA chain. This is a single
 * atomic u32 ग_लिखो, so there is no race condition.
 *
 * The end-result of all this that you only get an पूर्णांकerrupt when a buffer
 * is पढ़ोy, so the control flow is very easy.
 */
अटल व्योम tw68_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा tw68_dev *dev = vb2_get_drv_priv(vq);
	काष्ठा tw68_buf *buf = container_of(vbuf, काष्ठा tw68_buf, vb);
	काष्ठा tw68_buf *prev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->slock, flags);

	/* append a 'JUMP to start of buffer' to the buffer risc program */
	buf->jmp[0] = cpu_to_le32(RISC_JUMP);
	buf->jmp[1] = cpu_to_le32(buf->dma + 8);

	अगर (!list_empty(&dev->active)) अणु
		prev = list_entry(dev->active.prev, काष्ठा tw68_buf, list);
		buf->cpu[0] |= cpu_to_le32(RISC_INT_BIT);
		prev->jmp[1] = cpu_to_le32(buf->dma);
	पूर्ण
	list_add_tail(&buf->list, &dev->active);
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

/*
 * buffer_prepare
 *
 * Set the ancillary inक्रमmation पूर्णांकo the buffer काष्ठाure.  This
 * includes generating the necessary risc program अगर it hasn't alपढ़ोy
 * been करोne क्रम the current buffer क्रमmat.
 * The काष्ठाure fh contains the details of the क्रमmat requested by the
 * user - type, width, height and #fields.  This is compared with the
 * last क्रमmat set क्रम the current buffer.  If they dअगरfer, the risc
 * code (which controls the filling of the buffer) is (re-)generated.
 */
अटल पूर्णांक tw68_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा tw68_dev *dev = vb2_get_drv_priv(vq);
	काष्ठा tw68_buf *buf = container_of(vbuf, काष्ठा tw68_buf, vb);
	काष्ठा sg_table *dma = vb2_dma_sg_plane_desc(vb, 0);
	अचिन्हित size, bpl;

	size = (dev->width * dev->height * dev->fmt->depth) >> 3;
	अगर (vb2_plane_size(vb, 0) < size)
		वापस -EINVAL;
	vb2_set_plane_payload(vb, 0, size);

	bpl = (dev->width * dev->fmt->depth) >> 3;
	चयन (dev->field) अणु
	हाल V4L2_FIELD_TOP:
		tw68_risc_buffer(dev->pci, buf, dma->sgl,
				 0, UNSET, bpl, 0, dev->height);
		अवरोध;
	हाल V4L2_FIELD_BOTTOM:
		tw68_risc_buffer(dev->pci, buf, dma->sgl,
				 UNSET, 0, bpl, 0, dev->height);
		अवरोध;
	हाल V4L2_FIELD_SEQ_TB:
		tw68_risc_buffer(dev->pci, buf, dma->sgl,
				 0, bpl * (dev->height >> 1),
				 bpl, 0, dev->height >> 1);
		अवरोध;
	हाल V4L2_FIELD_SEQ_BT:
		tw68_risc_buffer(dev->pci, buf, dma->sgl,
				 bpl * (dev->height >> 1), 0,
				 bpl, 0, dev->height >> 1);
		अवरोध;
	हाल V4L2_FIELD_INTERLACED:
	शेष:
		tw68_risc_buffer(dev->pci, buf, dma->sgl,
				 0, bpl, bpl, bpl, dev->height >> 1);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tw68_buf_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा tw68_dev *dev = vb2_get_drv_priv(vq);
	काष्ठा tw68_buf *buf = container_of(vbuf, काष्ठा tw68_buf, vb);

	dma_मुक्त_coherent(&dev->pci->dev, buf->size, buf->cpu, buf->dma);
पूर्ण

अटल पूर्णांक tw68_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा tw68_dev *dev = vb2_get_drv_priv(q);
	काष्ठा tw68_buf *buf =
		container_of(dev->active.next, काष्ठा tw68_buf, list);

	dev->seqnr = 0;
	tw68_video_start_dma(dev, buf);
	वापस 0;
पूर्ण

अटल व्योम tw68_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा tw68_dev *dev = vb2_get_drv_priv(q);

	/* Stop risc & fअगरo */
	tw_clearl(TW68_DMAC, TW68_DMAP_EN | TW68_FIFO_EN);
	जबतक (!list_empty(&dev->active)) अणु
		काष्ठा tw68_buf *buf =
			container_of(dev->active.next, काष्ठा tw68_buf, list);

		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vb2_ops tw68_video_qops = अणु
	.queue_setup	= tw68_queue_setup,
	.buf_queue	= tw68_buf_queue,
	.buf_prepare	= tw68_buf_prepare,
	.buf_finish	= tw68_buf_finish,
	.start_streaming = tw68_start_streaming,
	.stop_streaming = tw68_stop_streaming,
	.रुको_prepare	= vb2_ops_रुको_prepare,
	.रुको_finish	= vb2_ops_रुको_finish,
पूर्ण;

/* ------------------------------------------------------------------ */

अटल पूर्णांक tw68_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा tw68_dev *dev =
		container_of(ctrl->handler, काष्ठा tw68_dev, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		tw_ग_लिखोb(TW68_BRIGHT, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		tw_ग_लिखोb(TW68_HUE, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		tw_ग_लिखोb(TW68_CONTRAST, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		tw_ग_लिखोb(TW68_SAT_U, ctrl->val);
		tw_ग_लिखोb(TW68_SAT_V, ctrl->val);
		अवरोध;
	हाल V4L2_CID_COLOR_KILLER:
		अगर (ctrl->val)
			tw_anकरोrb(TW68_MISC2, 0xe0, 0xe0);
		अन्यथा
			tw_anकरोrb(TW68_MISC2, 0xe0, 0x00);
		अवरोध;
	हाल V4L2_CID_CHROMA_AGC:
		अगर (ctrl->val)
			tw_anकरोrb(TW68_LOOP, 0x30, 0x20);
		अन्यथा
			tw_anकरोrb(TW68_LOOP, 0x30, 0x00);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

/*
 * Note that this routine वापसs what is stored in the fh काष्ठाure, and
 * करोes not पूर्णांकerrogate any of the device रेजिस्टरs.
 */
अटल पूर्णांक tw68_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा tw68_dev *dev = video_drvdata(file);

	f->fmt.pix.width        = dev->width;
	f->fmt.pix.height       = dev->height;
	f->fmt.pix.field        = dev->field;
	f->fmt.pix.pixelक्रमmat  = dev->fmt->fourcc;
	f->fmt.pix.bytesperline =
		(f->fmt.pix.width * (dev->fmt->depth)) >> 3;
	f->fmt.pix.sizeimage =
		f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace	= V4L2_COLORSPACE_SMPTE170M;
	वापस 0;
पूर्ण

अटल पूर्णांक tw68_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
						काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा tw68_dev *dev = video_drvdata(file);
	स्थिर काष्ठा tw68_क्रमmat *fmt;
	क्रमागत v4l2_field field;
	अचिन्हित पूर्णांक maxh;

	fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	अगर (शून्य == fmt)
		वापस -EINVAL;

	field = f->fmt.pix.field;
	maxh  = (dev->tvnorm->id & V4L2_STD_525_60) ? 480 : 576;

	चयन (field) अणु
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
		अवरोध;
	हाल V4L2_FIELD_INTERLACED:
	हाल V4L2_FIELD_SEQ_BT:
	हाल V4L2_FIELD_SEQ_TB:
		maxh = maxh * 2;
		अवरोध;
	शेष:
		field = (f->fmt.pix.height > maxh / 2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_BOTTOM;
		अवरोध;
	पूर्ण

	f->fmt.pix.field = field;
	अगर (f->fmt.pix.width  < 48)
		f->fmt.pix.width  = 48;
	अगर (f->fmt.pix.height < 32)
		f->fmt.pix.height = 32;
	अगर (f->fmt.pix.width > 720)
		f->fmt.pix.width = 720;
	अगर (f->fmt.pix.height > maxh)
		f->fmt.pix.height = maxh;
	f->fmt.pix.width &= ~0x03;
	f->fmt.pix.bytesperline =
		(f->fmt.pix.width * (fmt->depth)) >> 3;
	f->fmt.pix.sizeimage =
		f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	वापस 0;
पूर्ण

/*
 * Note that tw68_s_fmt_vid_cap sets the inक्रमmation पूर्णांकo the fh काष्ठाure,
 * and it will be used क्रम all future new buffers.  However, there could be
 * some number of buffers on the "active" chain which will be filled beक्रमe
 * the change takes place.
 */
अटल पूर्णांक tw68_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा tw68_dev *dev = video_drvdata(file);
	पूर्णांक err;

	err = tw68_try_fmt_vid_cap(file, priv, f);
	अगर (0 != err)
		वापस err;

	dev->fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	dev->width = f->fmt.pix.width;
	dev->height = f->fmt.pix.height;
	dev->field = f->fmt.pix.field;
	वापस 0;
पूर्ण

अटल पूर्णांक tw68_क्रमागत_input(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_input *i)
अणु
	काष्ठा tw68_dev *dev = video_drvdata(file);
	अचिन्हित पूर्णांक n;

	n = i->index;
	अगर (n >= TW68_INPUT_MAX)
		वापस -EINVAL;
	i->index = n;
	i->type = V4L2_INPUT_TYPE_CAMERA;
	snम_लिखो(i->name, माप(i->name), "Composite %d", n);

	/* If the query is क्रम the current input, get live data */
	अगर (n == dev->input) अणु
		पूर्णांक v1 = tw_पढ़ोb(TW68_STATUS1);
		पूर्णांक v2 = tw_पढ़ोb(TW68_MVSN);

		अगर (0 != (v1 & (1 << 7)))
			i->status |= V4L2_IN_ST_NO_SYNC;
		अगर (0 != (v1 & (1 << 6)))
			i->status |= V4L2_IN_ST_NO_H_LOCK;
		अगर (0 != (v1 & (1 << 2)))
			i->status |= V4L2_IN_ST_NO_SIGNAL;
		अगर (0 != (v1 & 1 << 1))
			i->status |= V4L2_IN_ST_NO_COLOR;
		अगर (0 != (v2 & (1 << 2)))
			i->status |= V4L2_IN_ST_MACROVISION;
	पूर्ण
	i->std = video_devdata(file)->tvnorms;
	वापस 0;
पूर्ण

अटल पूर्णांक tw68_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा tw68_dev *dev = video_drvdata(file);

	*i = dev->input;
	वापस 0;
पूर्ण

अटल पूर्णांक tw68_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा tw68_dev *dev = video_drvdata(file);

	अगर (i >= TW68_INPUT_MAX)
		वापस -EINVAL;
	dev->input = i;
	tw_anकरोrb(TW68_INFORM, 0x03 << 2, dev->input << 2);
	वापस 0;
पूर्ण

अटल पूर्णांक tw68_querycap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_capability *cap)
अणु
	काष्ठा tw68_dev *dev = video_drvdata(file);

	strscpy(cap->driver, "tw68", माप(cap->driver));
	strscpy(cap->card, "Techwell Capture Card",
		माप(cap->card));
	प्र_लिखो(cap->bus_info, "PCI:%s", pci_name(dev->pci));
	वापस 0;
पूर्ण

अटल पूर्णांक tw68_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id)
अणु
	काष्ठा tw68_dev *dev = video_drvdata(file);
	अचिन्हित पूर्णांक i;

	अगर (vb2_is_busy(&dev->vidq))
		वापस -EBUSY;

	/* Look क्रम match on complete norm id (may have mult bits) */
	क्रम (i = 0; i < TVNORMS; i++) अणु
		अगर (id == tvnorms[i].id)
			अवरोध;
	पूर्ण

	/* If no exact match, look क्रम norm which contains this one */
	अगर (i == TVNORMS) अणु
		क्रम (i = 0; i < TVNORMS; i++)
			अगर (id & tvnorms[i].id)
				अवरोध;
	पूर्ण
	/* If still not matched, give up */
	अगर (i == TVNORMS)
		वापस -EINVAL;

	set_tvnorm(dev, &tvnorms[i]);	/* करो the actual setting */
	वापस 0;
पूर्ण

अटल पूर्णांक tw68_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *id)
अणु
	काष्ठा tw68_dev *dev = video_drvdata(file);

	*id = dev->tvnorm->id;
	वापस 0;
पूर्ण

अटल पूर्णांक tw68_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index >= FORMATS)
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[f->index].fourcc;

	वापस 0;
पूर्ण

/*
 * Used strictly क्रम पूर्णांकernal development and debugging, this routine
 * prपूर्णांकs out the current रेजिस्टर contents क्रम the tw68xx device.
 */
अटल व्योम tw68_dump_regs(काष्ठा tw68_dev *dev)
अणु
	अचिन्हित अक्षर line[80];
	पूर्णांक i, j, k;
	अचिन्हित अक्षर *cptr;

	pr_info("Full dump of TW68 registers:\n");
	/* First we करो the PCI regs, 8 4-byte regs per line */
	क्रम (i = 0; i < 0x100; i += 32) अणु
		cptr = line;
		cptr += प्र_लिखो(cptr, "%03x  ", i);
		/* j steps through the next 4 words */
		क्रम (j = i; j < i + 16; j += 4)
			cptr += प्र_लिखो(cptr, "%08x ", tw_पढ़ोl(j));
		*cptr++ = ' ';
		क्रम (; j < i + 32; j += 4)
			cptr += प्र_लिखो(cptr, "%08x ", tw_पढ़ोl(j));
		*cptr++ = '\n';
		*cptr = 0;
		pr_info("%s", line);
	पूर्ण
	/* Next the control regs, which are single-byte, address mod 4 */
	जबतक (i < 0x400) अणु
		cptr = line;
		cptr += प्र_लिखो(cptr, "%03x ", i);
		/* Prपूर्णांक out 4 groups of 4 bytes */
		क्रम (j = 0; j < 4; j++) अणु
			क्रम (k = 0; k < 4; k++) अणु
				cptr += प्र_लिखो(cptr, "%02x ",
					tw_पढ़ोb(i));
				i += 4;
			पूर्ण
			*cptr++ = ' ';
		पूर्ण
		*cptr++ = '\n';
		*cptr = 0;
		pr_info("%s", line);
	पूर्ण
पूर्ण

अटल पूर्णांक vidioc_log_status(काष्ठा file *file, व्योम *priv)
अणु
	काष्ठा tw68_dev *dev = video_drvdata(file);

	tw68_dump_regs(dev);
	वापस v4l2_ctrl_log_status(file, priv);
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक vidioc_g_रेजिस्टर(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा tw68_dev *dev = video_drvdata(file);

	अगर (reg->size == 1)
		reg->val = tw_पढ़ोb(reg->reg);
	अन्यथा
		reg->val = tw_पढ़ोl(reg->reg);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_रेजिस्टर(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा tw68_dev *dev = video_drvdata(file);

	अगर (reg->size == 1)
		tw_ग_लिखोb(reg->reg, reg->val);
	अन्यथा
		tw_ग_लिखोl(reg->reg & 0xffff, reg->val);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा v4l2_ctrl_ops tw68_ctrl_ops = अणु
	.s_ctrl = tw68_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations video_fops = अणु
	.owner			= THIS_MODULE,
	.खोलो			= v4l2_fh_खोलो,
	.release		= vb2_fop_release,
	.पढ़ो			= vb2_fop_पढ़ो,
	.poll			= vb2_fop_poll,
	.mmap			= vb2_fop_mmap,
	.unlocked_ioctl		= video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops video_ioctl_ops = अणु
	.vidioc_querycap		= tw68_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= tw68_क्रमागत_fmt_vid_cap,
	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_s_std			= tw68_s_std,
	.vidioc_g_std			= tw68_g_std,
	.vidioc_क्रमागत_input		= tw68_क्रमागत_input,
	.vidioc_g_input			= tw68_g_input,
	.vidioc_s_input			= tw68_s_input,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
	.vidioc_g_fmt_vid_cap		= tw68_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		= tw68_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= tw68_s_fmt_vid_cap,
	.vidioc_log_status		= vidioc_log_status,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर              = vidioc_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर              = vidioc_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा video_device tw68_video_ढाँचा = अणु
	.name			= "tw68_video",
	.fops			= &video_fops,
	.ioctl_ops		= &video_ioctl_ops,
	.release		= video_device_release_empty,
	.tvnorms		= TW68_NORMS,
	.device_caps		= V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
				  V4L2_CAP_STREAMING,
पूर्ण;

/* ------------------------------------------------------------------ */
/* exported stuff                                                     */
व्योम tw68_set_tvnorm_hw(काष्ठा tw68_dev *dev)
अणु
	tw_anकरोrb(TW68_SDT, 0x07, dev->tvnorm->क्रमmat);
पूर्ण

पूर्णांक tw68_video_init1(काष्ठा tw68_dev *dev)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &dev->hdl;

	v4l2_ctrl_handler_init(hdl, 6);
	v4l2_ctrl_new_std(hdl, &tw68_ctrl_ops,
			V4L2_CID_BRIGHTNESS, -128, 127, 1, 20);
	v4l2_ctrl_new_std(hdl, &tw68_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 100);
	v4l2_ctrl_new_std(hdl, &tw68_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 128);
	/* NTSC only */
	v4l2_ctrl_new_std(hdl, &tw68_ctrl_ops,
			V4L2_CID_HUE, -128, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, &tw68_ctrl_ops,
			V4L2_CID_COLOR_KILLER, 0, 1, 1, 0);
	v4l2_ctrl_new_std(hdl, &tw68_ctrl_ops,
			V4L2_CID_CHROMA_AGC, 0, 1, 1, 1);
	अगर (hdl->error) अणु
		v4l2_ctrl_handler_मुक्त(hdl);
		वापस hdl->error;
	पूर्ण
	dev->v4l2_dev.ctrl_handler = hdl;
	v4l2_ctrl_handler_setup(hdl);
	वापस 0;
पूर्ण

पूर्णांक tw68_video_init2(काष्ठा tw68_dev *dev, पूर्णांक video_nr)
अणु
	पूर्णांक ret;

	set_tvnorm(dev, &tvnorms[0]);

	dev->fmt      = क्रमmat_by_fourcc(V4L2_PIX_FMT_BGR24);
	dev->width    = 720;
	dev->height   = 576;
	dev->field    = V4L2_FIELD_INTERLACED;

	INIT_LIST_HEAD(&dev->active);
	dev->vidq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dev->vidq.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	dev->vidq.io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ | VB2_DMABUF;
	dev->vidq.ops = &tw68_video_qops;
	dev->vidq.mem_ops = &vb2_dma_sg_memops;
	dev->vidq.drv_priv = dev;
	dev->vidq.gfp_flags = __GFP_DMA32 | __GFP_KSWAPD_RECLAIM;
	dev->vidq.buf_काष्ठा_size = माप(काष्ठा tw68_buf);
	dev->vidq.lock = &dev->lock;
	dev->vidq.min_buffers_needed = 2;
	dev->vidq.dev = &dev->pci->dev;
	ret = vb2_queue_init(&dev->vidq);
	अगर (ret)
		वापस ret;
	dev->vdev = tw68_video_ढाँचा;
	dev->vdev.v4l2_dev = &dev->v4l2_dev;
	dev->vdev.lock = &dev->lock;
	dev->vdev.queue = &dev->vidq;
	video_set_drvdata(&dev->vdev, dev);
	वापस video_रेजिस्टर_device(&dev->vdev, VFL_TYPE_VIDEO, video_nr);
पूर्ण

/*
 * tw68_irq_video_करोne
 */
व्योम tw68_irq_video_करोne(काष्ठा tw68_dev *dev, अचिन्हित दीर्घ status)
अणु
	__u32 reg;

	/* reset पूर्णांकerrupts handled by this routine */
	tw_ग_लिखोl(TW68_INTSTAT, status);
	/*
	 * Check most likely first
	 *
	 * DMAPI shows we have reached the end of the risc code
	 * क्रम the current buffer.
	 */
	अगर (status & TW68_DMAPI) अणु
		काष्ठा tw68_buf *buf;

		spin_lock(&dev->slock);
		buf = list_entry(dev->active.next, काष्ठा tw68_buf, list);
		list_del(&buf->list);
		spin_unlock(&dev->slock);
		buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
		buf->vb.field = dev->field;
		buf->vb.sequence = dev->seqnr++;
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
		status &= ~(TW68_DMAPI);
		अगर (0 == status)
			वापस;
	पूर्ण
	अगर (status & (TW68_VLOCK | TW68_HLOCK))
		dev_dbg(&dev->pci->dev, "Lost sync\n");
	अगर (status & TW68_PABORT)
		dev_err(&dev->pci->dev, "PABORT interrupt\n");
	अगर (status & TW68_DMAPERR)
		dev_err(&dev->pci->dev, "DMAPERR interrupt\n");
	/*
	 * On TW6800, FDMIS is apparently generated अगर video input is चयनed
	 * during operation.  Thereक्रमe, it is not enabled क्रम that chip.
	 */
	अगर (status & TW68_FDMIS)
		dev_dbg(&dev->pci->dev, "FDMIS interrupt\n");
	अगर (status & TW68_FFOF) अणु
		/* probably a logic error */
		reg = tw_पढ़ोl(TW68_DMAC) & TW68_FIFO_EN;
		tw_clearl(TW68_DMAC, TW68_FIFO_EN);
		dev_dbg(&dev->pci->dev, "FFOF interrupt\n");
		tw_setl(TW68_DMAC, reg);
	पूर्ण
	अगर (status & TW68_FFERR)
		dev_dbg(&dev->pci->dev, "FFERR interrupt\n");
पूर्ण
