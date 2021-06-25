<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

    bttv - Bt848 frame grabber driver
    vbi पूर्णांकerface

    (c) 2002 Gerd Knorr <kraxel@bytesex.org>

    Copyright (C) 2005, 2006 Michael H. Schimek <mschimek@gmx.at>
    Sponsored by OPQ Systems AB

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kdev_t.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <यंत्र/पन.स>
#समावेश "bttvp.h"

/* Offset from line sync pulse leading edge (0H) to start of VBI capture,
   in fCLKx2 pixels.  According to the datasheet, VBI capture starts
   VBI_HDELAY fCLKx1 pixels from the tailing edgeof /HRESET, and /HRESET
   is 64 fCLKx1 pixels wide.  VBI_HDELAY is set to 0, so this should be
   (64 + 0) * 2 = 128 fCLKx2 pixels.  But it's not!  The datasheet is
   Just Plain Wrong.  The real value appears to be dअगरferent क्रम
   dअगरferent revisions of the bt8x8 chips, and to be affected by the
   horizontal scaling factor.  Experimentally, the value is measured
   to be about 244.  */
#घोषणा VBI_OFFSET 244

/* 2048 क्रम compatibility with earlier driver versions. The driver
   really stores 1024 + tvnorm->vbipack * 4 samples per line in the
   buffer. Note tvnorm->vbipack is <= 0xFF (limit of VBIPACK_LO + HI
   is 0x1FF DWORDs) and VBI पढ़ो()s store a frame counter in the last
   four bytes of the VBI image. */
#घोषणा VBI_BPL 2048

/* Compatibility. */
#घोषणा VBI_DEFLINES 16

अटल अचिन्हित पूर्णांक vbibufs = 4;
अटल अचिन्हित पूर्णांक vbi_debug;

module_param(vbibufs,   पूर्णांक, 0444);
module_param(vbi_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(vbibufs,"number of vbi buffers, range 2-32, default 4");
MODULE_PARM_DESC(vbi_debug,"vbi code debug messages, default is 0 (no)");

#अगर_घोषित dprपूर्णांकk
# undef dprपूर्णांकk
#पूर्ण_अगर
#घोषणा dprपूर्णांकk(fmt, ...)						\
करो अणु									\
	अगर (vbi_debug)							\
		pr_debug("%d: " fmt, btv->c.nr, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

#घोषणा IMAGE_SIZE(fmt) \
	(((fmt)->count[0] + (fmt)->count[1]) * (fmt)->samples_per_line)

/* ----------------------------------------------------------------------- */
/* vbi risc code + mm                                                      */

अटल पूर्णांक vbi_buffer_setup(काष्ठा videobuf_queue *q,
			    अचिन्हित पूर्णांक *count, अचिन्हित पूर्णांक *size)
अणु
	काष्ठा bttv_fh *fh = q->priv_data;
	काष्ठा bttv *btv = fh->btv;

	अगर (0 == *count)
		*count = vbibufs;

	*size = IMAGE_SIZE(&fh->vbi_fmt.fmt);

	dprपूर्णांकk("setup: samples=%u start=%d,%d count=%u,%u\n",
		fh->vbi_fmt.fmt.samples_per_line,
		fh->vbi_fmt.fmt.start[0],
		fh->vbi_fmt.fmt.start[1],
		fh->vbi_fmt.fmt.count[0],
		fh->vbi_fmt.fmt.count[1]);

	वापस 0;
पूर्ण

अटल पूर्णांक vbi_buffer_prepare(काष्ठा videobuf_queue *q,
			      काष्ठा videobuf_buffer *vb,
			      क्रमागत v4l2_field field)
अणु
	काष्ठा bttv_fh *fh = q->priv_data;
	काष्ठा bttv *btv = fh->btv;
	काष्ठा bttv_buffer *buf = container_of(vb,काष्ठा bttv_buffer,vb);
	स्थिर काष्ठा bttv_tvnorm *tvnorm;
	अचिन्हित पूर्णांक skip_lines0, skip_lines1, min_vdelay;
	पूर्णांक reकरो_dma_risc;
	पूर्णांक rc;

	buf->vb.size = IMAGE_SIZE(&fh->vbi_fmt.fmt);
	अगर (0 != buf->vb.baddr  &&  buf->vb.bsize < buf->vb.size)
		वापस -EINVAL;

	tvnorm = fh->vbi_fmt.tvnorm;

	/* There's no VBI_VDELAY रेजिस्टर, RISC must skip the lines
	   we करोn't want. With शेष parameters we skip zero lines
	   as earlier driver versions did. The driver permits video
	   standard changes जबतक capturing, so we use vbi_fmt.tvnorm
	   instead of btv->tvnorm to skip zero lines after video
	   standard changes as well. */

	skip_lines0 = 0;
	skip_lines1 = 0;

	अगर (fh->vbi_fmt.fmt.count[0] > 0)
		skip_lines0 = max(0, (fh->vbi_fmt.fmt.start[0]
				      - tvnorm->vbistart[0]));
	अगर (fh->vbi_fmt.fmt.count[1] > 0)
		skip_lines1 = max(0, (fh->vbi_fmt.fmt.start[1]
				      - tvnorm->vbistart[1]));

	reकरो_dma_risc = 0;

	अगर (buf->vbi_skip[0] != skip_lines0 ||
	    buf->vbi_skip[1] != skip_lines1 ||
	    buf->vbi_count[0] != fh->vbi_fmt.fmt.count[0] ||
	    buf->vbi_count[1] != fh->vbi_fmt.fmt.count[1]) अणु
		buf->vbi_skip[0] = skip_lines0;
		buf->vbi_skip[1] = skip_lines1;
		buf->vbi_count[0] = fh->vbi_fmt.fmt.count[0];
		buf->vbi_count[1] = fh->vbi_fmt.fmt.count[1];
		reकरो_dma_risc = 1;
	पूर्ण

	अगर (VIDEOBUF_NEEDS_INIT == buf->vb.state) अणु
		reकरो_dma_risc = 1;
		अगर (0 != (rc = videobuf_iolock(q, &buf->vb, शून्य)))
			जाओ fail;
	पूर्ण

	अगर (reकरो_dma_risc) अणु
		अचिन्हित पूर्णांक bpl, padding, offset;
		काष्ठा videobuf_dmabuf *dma=videobuf_to_dma(&buf->vb);

		bpl = 2044; /* max. vbipack */
		padding = VBI_BPL - bpl;

		अगर (fh->vbi_fmt.fmt.count[0] > 0) अणु
			rc = bttv_risc_packed(btv, &buf->top,
					      dma->sglist,
					      /* offset */ 0, bpl,
					      padding, skip_lines0,
					      fh->vbi_fmt.fmt.count[0]);
			अगर (0 != rc)
				जाओ fail;
		पूर्ण

		अगर (fh->vbi_fmt.fmt.count[1] > 0) अणु
			offset = fh->vbi_fmt.fmt.count[0] * VBI_BPL;

			rc = bttv_risc_packed(btv, &buf->bottom,
					      dma->sglist,
					      offset, bpl,
					      padding, skip_lines1,
					      fh->vbi_fmt.fmt.count[1]);
			अगर (0 != rc)
				जाओ fail;
		पूर्ण
	पूर्ण

	/* VBI capturing ends at VDELAY, start of video capturing,
	   no matter where the RISC program ends. VDELAY minimum is 2,
	   bounds.top is the corresponding first field line number
	   बार two. VDELAY counts half field lines. */
	min_vdelay = MIN_VDELAY;
	अगर (fh->vbi_fmt.end >= tvnorm->cropcap.bounds.top)
		min_vdelay += fh->vbi_fmt.end - tvnorm->cropcap.bounds.top;

	/* For bttv_buffer_activate_vbi(). */
	buf->geo.vdelay = min_vdelay;

	buf->vb.state = VIDEOBUF_PREPARED;
	buf->vb.field = field;
	dprपूर्णांकk("buf prepare %p: top=%p bottom=%p field=%s\n",
		vb, &buf->top, &buf->bottom,
		v4l2_field_names[buf->vb.field]);
	वापस 0;

 fail:
	bttv_dma_मुक्त(q,btv,buf);
	वापस rc;
पूर्ण

अटल व्योम
vbi_buffer_queue(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा bttv_fh *fh = q->priv_data;
	काष्ठा bttv *btv = fh->btv;
	काष्ठा bttv_buffer *buf = container_of(vb,काष्ठा bttv_buffer,vb);

	dprपूर्णांकk("queue %p\n",vb);
	buf->vb.state = VIDEOBUF_QUEUED;
	list_add_tail(&buf->vb.queue,&btv->vcapture);
	अगर (शून्य == btv->cvbi) अणु
		fh->btv->loop_irq |= 4;
		bttv_set_dma(btv,0x0c);
	पूर्ण
पूर्ण

अटल व्योम vbi_buffer_release(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा bttv_fh *fh = q->priv_data;
	काष्ठा bttv *btv = fh->btv;
	काष्ठा bttv_buffer *buf = container_of(vb,काष्ठा bttv_buffer,vb);

	dprपूर्णांकk("free %p\n",vb);
	bttv_dma_मुक्त(q,fh->btv,buf);
पूर्ण

स्थिर काष्ठा videobuf_queue_ops bttv_vbi_qops = अणु
	.buf_setup    = vbi_buffer_setup,
	.buf_prepare  = vbi_buffer_prepare,
	.buf_queue    = vbi_buffer_queue,
	.buf_release  = vbi_buffer_release,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल पूर्णांक try_fmt(काष्ठा v4l2_vbi_क्रमmat *f, स्थिर काष्ठा bttv_tvnorm *tvnorm,
			__s32 crop_start)
अणु
	__s32 min_start, max_start, max_end, f2_offset;
	अचिन्हित पूर्णांक i;

	/* For compatibility with earlier driver versions we must pretend
	   the VBI and video capture winकरोw may overlap. In reality RISC
	   magic पातs VBI capturing at the first line of video capturing,
	   leaving the rest of the buffer unchanged, usually all zero.
	   VBI capturing must always start beक्रमe video capturing. >> 1
	   because cropping counts field lines बार two. */
	min_start = tvnorm->vbistart[0];
	max_start = (crop_start >> 1) - 1;
	max_end = (tvnorm->cropcap.bounds.top
		   + tvnorm->cropcap.bounds.height) >> 1;

	अगर (min_start > max_start)
		वापस -EBUSY;

	BUG_ON(max_start >= max_end);

	f->sampling_rate    = tvnorm->Fsc;
	f->samples_per_line = VBI_BPL;
	f->sample_क्रमmat    = V4L2_PIX_FMT_GREY;
	f->offset           = VBI_OFFSET;

	f2_offset = tvnorm->vbistart[1] - tvnorm->vbistart[0];

	क्रम (i = 0; i < 2; ++i) अणु
		अगर (0 == f->count[i]) अणु
			/* No data from this field. We leave f->start[i]
			   alone because VIDIOCSVBIFMT is w/o and EINVALs
			   when a driver करोes not support exactly the
			   requested parameters. */
		पूर्ण अन्यथा अणु
			s64 start, count;

			start = clamp(f->start[i], min_start, max_start);
			/* s64 to prevent overflow. */
			count = (s64) f->start[i] + f->count[i] - start;
			f->start[i] = start;
			f->count[i] = clamp(count, (s64) 1,
					    max_end - start);
		पूर्ण

		min_start += f2_offset;
		max_start += f2_offset;
		max_end += f2_offset;
	पूर्ण

	अगर (0 == (f->count[0] | f->count[1])) अणु
		/* As in earlier driver versions. */
		f->start[0] = tvnorm->vbistart[0];
		f->start[1] = tvnorm->vbistart[1];
		f->count[0] = 1;
		f->count[1] = 1;
	पूर्ण

	f->flags = 0;

	f->reserved[0] = 0;
	f->reserved[1] = 0;

	वापस 0;
पूर्ण

पूर्णांक bttv_try_fmt_vbi_cap(काष्ठा file *file, व्योम *f, काष्ठा v4l2_क्रमmat *frt)
अणु
	काष्ठा bttv_fh *fh = f;
	काष्ठा bttv *btv = fh->btv;
	स्थिर काष्ठा bttv_tvnorm *tvnorm;
	__s32 crop_start;

	mutex_lock(&btv->lock);

	tvnorm = &bttv_tvnorms[btv->tvnorm];
	crop_start = btv->crop_start;

	mutex_unlock(&btv->lock);

	वापस try_fmt(&frt->fmt.vbi, tvnorm, crop_start);
पूर्ण


पूर्णांक bttv_s_fmt_vbi_cap(काष्ठा file *file, व्योम *f, काष्ठा v4l2_क्रमmat *frt)
अणु
	काष्ठा bttv_fh *fh = f;
	काष्ठा bttv *btv = fh->btv;
	स्थिर काष्ठा bttv_tvnorm *tvnorm;
	__s32 start1, end;
	पूर्णांक rc;

	mutex_lock(&btv->lock);

	rc = -EBUSY;
	अगर (fh->resources & RESOURCE_VBI)
		जाओ fail;

	tvnorm = &bttv_tvnorms[btv->tvnorm];

	rc = try_fmt(&frt->fmt.vbi, tvnorm, btv->crop_start);
	अगर (0 != rc)
		जाओ fail;

	start1 = frt->fmt.vbi.start[1] - tvnorm->vbistart[1] +
		tvnorm->vbistart[0];

	/* First possible line of video capturing. Should be
	   max(f->start[0] + f->count[0], start1 + f->count[1]) * 2
	   when capturing both fields. But क्रम compatibility we must
	   pretend the VBI and video capture winकरोw may overlap,
	   so end = start + 1, the lowest possible value, बार two
	   because vbi_fmt.end counts field lines बार two. */
	end = max(frt->fmt.vbi.start[0], start1) * 2 + 2;

	mutex_lock(&fh->vbi.vb_lock);

	fh->vbi_fmt.fmt    = frt->fmt.vbi;
	fh->vbi_fmt.tvnorm = tvnorm;
	fh->vbi_fmt.end    = end;

	mutex_unlock(&fh->vbi.vb_lock);

	rc = 0;

 fail:
	mutex_unlock(&btv->lock);

	वापस rc;
पूर्ण


पूर्णांक bttv_g_fmt_vbi_cap(काष्ठा file *file, व्योम *f, काष्ठा v4l2_क्रमmat *frt)
अणु
	काष्ठा bttv_fh *fh = f;
	स्थिर काष्ठा bttv_tvnorm *tvnorm;

	frt->fmt.vbi = fh->vbi_fmt.fmt;

	tvnorm = &bttv_tvnorms[fh->btv->tvnorm];

	अगर (tvnorm != fh->vbi_fmt.tvnorm) अणु
		__s32 max_end;
		अचिन्हित पूर्णांक i;

		/* As in vbi_buffer_prepare() this imitates the
		   behaviour of earlier driver versions after video
		   standard changes, with शेष parameters anyway. */

		max_end = (tvnorm->cropcap.bounds.top
			   + tvnorm->cropcap.bounds.height) >> 1;

		frt->fmt.vbi.sampling_rate = tvnorm->Fsc;

		क्रम (i = 0; i < 2; ++i) अणु
			__s32 new_start;

			new_start = frt->fmt.vbi.start[i]
				+ tvnorm->vbistart[i]
				- fh->vbi_fmt.tvnorm->vbistart[i];

			frt->fmt.vbi.start[i] = min(new_start, max_end - 1);
			frt->fmt.vbi.count[i] =
				min((__s32) frt->fmt.vbi.count[i],
					  max_end - frt->fmt.vbi.start[i]);

			max_end += tvnorm->vbistart[1]
				- tvnorm->vbistart[0];
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम bttv_vbi_fmt_reset(काष्ठा bttv_vbi_fmt *f, अचिन्हित पूर्णांक norm)
अणु
	स्थिर काष्ठा bttv_tvnorm *tvnorm;
	अचिन्हित पूर्णांक real_samples_per_line;
	अचिन्हित पूर्णांक real_count;

	tvnorm = &bttv_tvnorms[norm];

	f->fmt.sampling_rate    = tvnorm->Fsc;
	f->fmt.samples_per_line = VBI_BPL;
	f->fmt.sample_क्रमmat    = V4L2_PIX_FMT_GREY;
	f->fmt.offset           = VBI_OFFSET;
	f->fmt.start[0]		= tvnorm->vbistart[0];
	f->fmt.start[1]		= tvnorm->vbistart[1];
	f->fmt.count[0]		= VBI_DEFLINES;
	f->fmt.count[1]		= VBI_DEFLINES;
	f->fmt.flags            = 0;
	f->fmt.reserved[0]      = 0;
	f->fmt.reserved[1]      = 0;

	/* For compatibility the buffer size must be 2 * VBI_DEFLINES *
	   VBI_BPL regardless of the current video standard. */
	real_samples_per_line   = 1024 + tvnorm->vbipack * 4;
	real_count              = ((tvnorm->cropcap.defrect.top >> 1)
				   - tvnorm->vbistart[0]);

	BUG_ON(real_samples_per_line > VBI_BPL);
	BUG_ON(real_count > VBI_DEFLINES);

	f->tvnorm               = tvnorm;

	/* See bttv_vbi_fmt_set(). */
	f->end                  = tvnorm->vbistart[0] * 2 + 2;
पूर्ण
