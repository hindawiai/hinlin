<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support eMMa-PrP through mem2mem framework.
 *
 * eMMa-PrP is a piece of HW that allows fetching buffers
 * from one memory location and करो several operations on
 * them such as scaling or क्रमmat conversion giving, as a result
 * a new processed buffer in another memory location.
 *
 * Based on mem2mem_testdev.c by Pawel Osciak.
 *
 * Copyright (c) 2011 Vista Silicon S.L.
 * Javier Martin <javier.martin@vista-silicon.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

#समावेश <linux/platक्रमm_device.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <linux/sizes.h>

#घोषणा EMMAPRP_MODULE_NAME "mem2mem-emmaprp"

MODULE_DESCRIPTION("Mem-to-mem device which supports eMMa-PrP present in mx2 SoCs");
MODULE_AUTHOR("Javier Martin <javier.martin@vista-silicon.com");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

अटल bool debug;
module_param(debug, bool, 0644);

#घोषणा MIN_W 32
#घोषणा MIN_H 32
#घोषणा MAX_W 2040
#घोषणा MAX_H 2046

#घोषणा S_ALIGN		1 /* multiple of 2 */
#घोषणा W_ALIGN_YUV420	3 /* multiple of 8 */
#घोषणा W_ALIGN_OTHERS	2 /* multiple of 4 */
#घोषणा H_ALIGN		1 /* multiple of 2 */

/* Flags that indicate a क्रमmat can be used क्रम capture/output */
#घोषणा MEM2MEM_CAPTURE	(1 << 0)
#घोषणा MEM2MEM_OUTPUT	(1 << 1)

#घोषणा MEM2MEM_NAME		"m2m-emmaprp"

/* In bytes, per queue */
#घोषणा MEM2MEM_VID_MEM_LIMIT	SZ_16M

#घोषणा dprपूर्णांकk(dev, fmt, arg...) \
	v4l2_dbg(1, debug, &dev->v4l2_dev, "%s: " fmt, __func__, ## arg)

/* EMMA PrP */
#घोषणा PRP_CNTL                        0x00
#घोषणा PRP_INTR_CNTL                   0x04
#घोषणा PRP_INTRSTATUS                  0x08
#घोषणा PRP_SOURCE_Y_PTR                0x0c
#घोषणा PRP_SOURCE_CB_PTR               0x10
#घोषणा PRP_SOURCE_CR_PTR               0x14
#घोषणा PRP_DEST_RGB1_PTR               0x18
#घोषणा PRP_DEST_RGB2_PTR               0x1c
#घोषणा PRP_DEST_Y_PTR                  0x20
#घोषणा PRP_DEST_CB_PTR                 0x24
#घोषणा PRP_DEST_CR_PTR                 0x28
#घोषणा PRP_SRC_FRAME_SIZE              0x2c
#घोषणा PRP_DEST_CH1_LINE_STRIDE        0x30
#घोषणा PRP_SRC_PIXEL_FORMAT_CNTL       0x34
#घोषणा PRP_CH1_PIXEL_FORMAT_CNTL       0x38
#घोषणा PRP_CH1_OUT_IMAGE_SIZE          0x3c
#घोषणा PRP_CH2_OUT_IMAGE_SIZE          0x40
#घोषणा PRP_SRC_LINE_STRIDE             0x44
#घोषणा PRP_CSC_COEF_012                0x48
#घोषणा PRP_CSC_COEF_345                0x4c
#घोषणा PRP_CSC_COEF_678                0x50
#घोषणा PRP_CH1_RZ_HORI_COEF1           0x54
#घोषणा PRP_CH1_RZ_HORI_COEF2           0x58
#घोषणा PRP_CH1_RZ_HORI_VALID           0x5c
#घोषणा PRP_CH1_RZ_VERT_COEF1           0x60
#घोषणा PRP_CH1_RZ_VERT_COEF2           0x64
#घोषणा PRP_CH1_RZ_VERT_VALID           0x68
#घोषणा PRP_CH2_RZ_HORI_COEF1           0x6c
#घोषणा PRP_CH2_RZ_HORI_COEF2           0x70
#घोषणा PRP_CH2_RZ_HORI_VALID           0x74
#घोषणा PRP_CH2_RZ_VERT_COEF1           0x78
#घोषणा PRP_CH2_RZ_VERT_COEF2           0x7c
#घोषणा PRP_CH2_RZ_VERT_VALID           0x80

#घोषणा PRP_CNTL_CH1EN          (1 << 0)
#घोषणा PRP_CNTL_CH2EN          (1 << 1)
#घोषणा PRP_CNTL_CSIEN          (1 << 2)
#घोषणा PRP_CNTL_DATA_IN_YUV420 (0 << 3)
#घोषणा PRP_CNTL_DATA_IN_YUV422 (1 << 3)
#घोषणा PRP_CNTL_DATA_IN_RGB16  (2 << 3)
#घोषणा PRP_CNTL_DATA_IN_RGB32  (3 << 3)
#घोषणा PRP_CNTL_CH1_OUT_RGB8   (0 << 5)
#घोषणा PRP_CNTL_CH1_OUT_RGB16  (1 << 5)
#घोषणा PRP_CNTL_CH1_OUT_RGB32  (2 << 5)
#घोषणा PRP_CNTL_CH1_OUT_YUV422 (3 << 5)
#घोषणा PRP_CNTL_CH2_OUT_YUV420 (0 << 7)
#घोषणा PRP_CNTL_CH2_OUT_YUV422 (1 << 7)
#घोषणा PRP_CNTL_CH2_OUT_YUV444 (2 << 7)
#घोषणा PRP_CNTL_CH1_LEN        (1 << 9)
#घोषणा PRP_CNTL_CH2_LEN        (1 << 10)
#घोषणा PRP_CNTL_SKIP_FRAME     (1 << 11)
#घोषणा PRP_CNTL_SWRST          (1 << 12)
#घोषणा PRP_CNTL_CLKEN          (1 << 13)
#घोषणा PRP_CNTL_WEN            (1 << 14)
#घोषणा PRP_CNTL_CH1BYP         (1 << 15)
#घोषणा PRP_CNTL_IN_TSKIP(x)    ((x) << 16)
#घोषणा PRP_CNTL_CH1_TSKIP(x)   ((x) << 19)
#घोषणा PRP_CNTL_CH2_TSKIP(x)   ((x) << 22)
#घोषणा PRP_CNTL_INPUT_FIFO_LEVEL(x)    ((x) << 25)
#घोषणा PRP_CNTL_RZ_FIFO_LEVEL(x)       ((x) << 27)
#घोषणा PRP_CNTL_CH2B1EN        (1 << 29)
#घोषणा PRP_CNTL_CH2B2EN        (1 << 30)
#घोषणा PRP_CNTL_CH2FEN         (1UL << 31)

#घोषणा PRP_SIZE_HEIGHT(x)	(x)
#घोषणा PRP_SIZE_WIDTH(x)	((x) << 16)

/* IRQ Enable and status रेजिस्टर */
#घोषणा PRP_INTR_RDERR          (1 << 0)
#घोषणा PRP_INTR_CH1WERR        (1 << 1)
#घोषणा PRP_INTR_CH2WERR        (1 << 2)
#घोषणा PRP_INTR_CH1FC          (1 << 3)
#घोषणा PRP_INTR_CH2FC          (1 << 5)
#घोषणा PRP_INTR_LBOVF          (1 << 7)
#घोषणा PRP_INTR_CH2OVF         (1 << 8)

#घोषणा PRP_INTR_ST_RDERR	(1 << 0)
#घोषणा PRP_INTR_ST_CH1WERR	(1 << 1)
#घोषणा PRP_INTR_ST_CH2WERR	(1 << 2)
#घोषणा PRP_INTR_ST_CH2B2CI	(1 << 3)
#घोषणा PRP_INTR_ST_CH2B1CI	(1 << 4)
#घोषणा PRP_INTR_ST_CH1B2CI	(1 << 5)
#घोषणा PRP_INTR_ST_CH1B1CI	(1 << 6)
#घोषणा PRP_INTR_ST_LBOVF	(1 << 7)
#घोषणा PRP_INTR_ST_CH2OVF	(1 << 8)

काष्ठा emmaprp_fmt अणु
	u32	fourcc;
	/* Types the क्रमmat can be used क्रम */
	u32	types;
पूर्ण;

अटल काष्ठा emmaprp_fmt क्रमmats[] = अणु
	अणु
		.fourcc	= V4L2_PIX_FMT_YUV420,
		.types	= MEM2MEM_CAPTURE,
	पूर्ण,
	अणु
		.fourcc	= V4L2_PIX_FMT_YUYV,
		.types	= MEM2MEM_OUTPUT,
	पूर्ण,
पूर्ण;

/* Per-queue, driver-specअगरic निजी data */
काष्ठा emmaprp_q_data अणु
	अचिन्हित पूर्णांक		width;
	अचिन्हित पूर्णांक		height;
	अचिन्हित पूर्णांक		sizeimage;
	काष्ठा emmaprp_fmt	*fmt;
पूर्ण;

क्रमागत अणु
	V4L2_M2M_SRC = 0,
	V4L2_M2M_DST = 1,
पूर्ण;

#घोषणा NUM_FORMATS ARRAY_SIZE(क्रमmats)

अटल काष्ठा emmaprp_fmt *find_क्रमmat(काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा emmaprp_fmt *fmt;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < NUM_FORMATS; k++) अणु
		fmt = &क्रमmats[k];
		अगर (fmt->fourcc == f->fmt.pix.pixelक्रमmat)
			अवरोध;
	पूर्ण

	अगर (k == NUM_FORMATS)
		वापस शून्य;

	वापस &क्रमmats[k];
पूर्ण

काष्ठा emmaprp_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	*vfd;

	काष्ठा mutex		dev_mutex;
	spinlock_t		irqlock;

	व्योम __iomem		*base_emma;
	काष्ठा clk		*clk_emma_ahb, *clk_emma_ipg;

	काष्ठा v4l2_m2m_dev	*m2m_dev;
पूर्ण;

काष्ठा emmaprp_ctx अणु
	काष्ठा v4l2_fh		fh;
	काष्ठा emmaprp_dev	*dev;
	/* Abort requested by m2m */
	पूर्णांक			पातing;
	काष्ठा emmaprp_q_data	q_data[2];
पूर्ण;

अटल काष्ठा emmaprp_q_data *get_q_data(काष्ठा emmaprp_ctx *ctx,
					 क्रमागत v4l2_buf_type type)
अणु
	चयन (type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		वापस &(ctx->q_data[V4L2_M2M_SRC]);
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		वापस &(ctx->q_data[V4L2_M2M_DST]);
	शेष:
		BUG();
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * mem2mem callbacks
 */
अटल व्योम emmaprp_job_पात(व्योम *priv)
अणु
	काष्ठा emmaprp_ctx *ctx = priv;
	काष्ठा emmaprp_dev *pcdev = ctx->dev;

	ctx->पातing = 1;

	dprपूर्णांकk(pcdev, "Aborting task\n");

	v4l2_m2m_job_finish(pcdev->m2m_dev, ctx->fh.m2m_ctx);
पूर्ण

अटल अंतरभूत व्योम emmaprp_dump_regs(काष्ठा emmaprp_dev *pcdev)
अणु
	dprपूर्णांकk(pcdev,
		"eMMa-PrP Registers:\n"
		"  SOURCE_Y_PTR = 0x%08X\n"
		"  SRC_FRAME_SIZE = 0x%08X\n"
		"  DEST_Y_PTR = 0x%08X\n"
		"  DEST_CR_PTR = 0x%08X\n"
		"  DEST_CB_PTR = 0x%08X\n"
		"  CH2_OUT_IMAGE_SIZE = 0x%08X\n"
		"  CNTL = 0x%08X\n",
		पढ़ोl(pcdev->base_emma + PRP_SOURCE_Y_PTR),
		पढ़ोl(pcdev->base_emma + PRP_SRC_FRAME_SIZE),
		पढ़ोl(pcdev->base_emma + PRP_DEST_Y_PTR),
		पढ़ोl(pcdev->base_emma + PRP_DEST_CR_PTR),
		पढ़ोl(pcdev->base_emma + PRP_DEST_CB_PTR),
		पढ़ोl(pcdev->base_emma + PRP_CH2_OUT_IMAGE_SIZE),
		पढ़ोl(pcdev->base_emma + PRP_CNTL));
पूर्ण

अटल व्योम emmaprp_device_run(व्योम *priv)
अणु
	काष्ठा emmaprp_ctx *ctx = priv;
	काष्ठा emmaprp_q_data *s_q_data, *d_q_data;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	काष्ठा emmaprp_dev *pcdev = ctx->dev;
	अचिन्हित पूर्णांक s_width, s_height;
	अचिन्हित पूर्णांक d_width, d_height;
	अचिन्हित पूर्णांक d_size;
	dma_addr_t p_in, p_out;
	u32 पंचांगp;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	s_q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	s_width	= s_q_data->width;
	s_height = s_q_data->height;

	d_q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	d_width = d_q_data->width;
	d_height = d_q_data->height;
	d_size = d_width * d_height;

	p_in = vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
	p_out = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);
	अगर (!p_in || !p_out) अणु
		v4l2_err(&pcdev->v4l2_dev,
			 "Acquiring kernel pointers to buffers failed\n");
		वापस;
	पूर्ण

	/* Input frame parameters */
	ग_लिखोl(p_in, pcdev->base_emma + PRP_SOURCE_Y_PTR);
	ग_लिखोl(PRP_SIZE_WIDTH(s_width) | PRP_SIZE_HEIGHT(s_height),
	       pcdev->base_emma + PRP_SRC_FRAME_SIZE);

	/* Output frame parameters */
	ग_लिखोl(p_out, pcdev->base_emma + PRP_DEST_Y_PTR);
	ग_लिखोl(p_out + d_size, pcdev->base_emma + PRP_DEST_CB_PTR);
	ग_लिखोl(p_out + d_size + (d_size >> 2),
	       pcdev->base_emma + PRP_DEST_CR_PTR);
	ग_लिखोl(PRP_SIZE_WIDTH(d_width) | PRP_SIZE_HEIGHT(d_height),
	       pcdev->base_emma + PRP_CH2_OUT_IMAGE_SIZE);

	/* IRQ configuration */
	पंचांगp = पढ़ोl(pcdev->base_emma + PRP_INTR_CNTL);
	ग_लिखोl(पंचांगp | PRP_INTR_RDERR |
		PRP_INTR_CH2WERR |
		PRP_INTR_CH2FC,
		pcdev->base_emma + PRP_INTR_CNTL);

	emmaprp_dump_regs(pcdev);

	/* Enable transfer */
	पंचांगp = पढ़ोl(pcdev->base_emma + PRP_CNTL);
	ग_लिखोl(पंचांगp | PRP_CNTL_CH2_OUT_YUV420 |
		PRP_CNTL_DATA_IN_YUV422 |
		PRP_CNTL_CH2EN,
		pcdev->base_emma + PRP_CNTL);
पूर्ण

अटल irqवापस_t emmaprp_irq(पूर्णांक irq_emma, व्योम *data)
अणु
	काष्ठा emmaprp_dev *pcdev = data;
	काष्ठा emmaprp_ctx *curr_ctx;
	काष्ठा vb2_v4l2_buffer *src_vb, *dst_vb;
	अचिन्हित दीर्घ flags;
	u32 irqst;

	/* Check irq flags and clear irq */
	irqst = पढ़ोl(pcdev->base_emma + PRP_INTRSTATUS);
	ग_लिखोl(irqst, pcdev->base_emma + PRP_INTRSTATUS);
	dprपूर्णांकk(pcdev, "irqst = 0x%08x\n", irqst);

	curr_ctx = v4l2_m2m_get_curr_priv(pcdev->m2m_dev);
	अगर (curr_ctx == शून्य) अणु
		pr_err("Instance released before the end of transaction\n");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (!curr_ctx->पातing) अणु
		अगर ((irqst & PRP_INTR_ST_RDERR) ||
		(irqst & PRP_INTR_ST_CH2WERR)) अणु
			pr_err("PrP bus error occurred, this transfer is probably corrupted\n");
			ग_लिखोl(PRP_CNTL_SWRST, pcdev->base_emma + PRP_CNTL);
		पूर्ण अन्यथा अगर (irqst & PRP_INTR_ST_CH2B1CI) अणु /* buffer पढ़ोy */
			src_vb = v4l2_m2m_src_buf_हटाओ(curr_ctx->fh.m2m_ctx);
			dst_vb = v4l2_m2m_dst_buf_हटाओ(curr_ctx->fh.m2m_ctx);

			dst_vb->vb2_buf.बारtamp = src_vb->vb2_buf.बारtamp;
			dst_vb->flags &=
				~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
			dst_vb->flags |=
				src_vb->flags
				& V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
			dst_vb->समयcode = src_vb->समयcode;

			spin_lock_irqsave(&pcdev->irqlock, flags);
			v4l2_m2m_buf_करोne(src_vb, VB2_BUF_STATE_DONE);
			v4l2_m2m_buf_करोne(dst_vb, VB2_BUF_STATE_DONE);
			spin_unlock_irqrestore(&pcdev->irqlock, flags);
		पूर्ण
	पूर्ण

	v4l2_m2m_job_finish(pcdev->m2m_dev, curr_ctx->fh.m2m_ctx);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * video ioctls
 */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, MEM2MEM_NAME, माप(cap->driver));
	strscpy(cap->card, MEM2MEM_NAME, माप(cap->card));
	वापस 0;
पूर्ण

अटल पूर्णांक क्रमागत_fmt(काष्ठा v4l2_fmtdesc *f, u32 type)
अणु
	पूर्णांक i, num;
	काष्ठा emmaprp_fmt *fmt;

	num = 0;

	क्रम (i = 0; i < NUM_FORMATS; ++i) अणु
		अगर (क्रमmats[i].types & type) अणु
			/* index-th क्रमmat of type type found ? */
			अगर (num == f->index)
				अवरोध;
			/* Correct type but haven't reached our index yet,
			 * just increment per-type index */
			++num;
		पूर्ण
	पूर्ण

	अगर (i < NUM_FORMATS) अणु
		/* Format found */
		fmt = &क्रमmats[i];
		f->pixelक्रमmat = fmt->fourcc;
		वापस 0;
	पूर्ण

	/* Format not found */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस क्रमागत_fmt(f, MEM2MEM_CAPTURE);
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	वापस क्रमागत_fmt(f, MEM2MEM_OUTPUT);
पूर्ण

अटल पूर्णांक vidioc_g_fmt(काष्ठा emmaprp_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vb2_queue *vq;
	काष्ठा emmaprp_q_data *q_data;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = get_q_data(ctx, f->type);

	f->fmt.pix.width	= q_data->width;
	f->fmt.pix.height	= q_data->height;
	f->fmt.pix.field	= V4L2_FIELD_NONE;
	f->fmt.pix.pixelक्रमmat	= q_data->fmt->fourcc;
	अगर (f->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_YUV420)
		f->fmt.pix.bytesperline = q_data->width * 3 / 2;
	अन्यथा /* YUYV */
		f->fmt.pix.bytesperline = q_data->width * 2;
	f->fmt.pix.sizeimage	= q_data->sizeimage;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	वापस vidioc_g_fmt(priv, f);
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	वापस vidioc_g_fmt(priv, f);
पूर्ण

अटल पूर्णांक vidioc_try_fmt(काष्ठा v4l2_क्रमmat *f)
अणु
	क्रमागत v4l2_field field;


	अगर (!find_क्रमmat(f))
		वापस -EINVAL;

	field = f->fmt.pix.field;
	अगर (field == V4L2_FIELD_ANY)
		field = V4L2_FIELD_NONE;
	अन्यथा अगर (V4L2_FIELD_NONE != field)
		वापस -EINVAL;

	/* V4L2 specअगरication suggests the driver corrects the क्रमmat काष्ठा
	 * अगर any of the dimensions is unsupported */
	f->fmt.pix.field = field;

	अगर (f->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_YUV420) अणु
		v4l_bound_align_image(&f->fmt.pix.width, MIN_W, MAX_W,
				      W_ALIGN_YUV420, &f->fmt.pix.height,
				      MIN_H, MAX_H, H_ALIGN, S_ALIGN);
		f->fmt.pix.bytesperline = f->fmt.pix.width * 3 / 2;
	पूर्ण अन्यथा अणु
		v4l_bound_align_image(&f->fmt.pix.width, MIN_W, MAX_W,
				      W_ALIGN_OTHERS, &f->fmt.pix.height,
				      MIN_H, MAX_H, H_ALIGN, S_ALIGN);
		f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	पूर्ण
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा emmaprp_fmt *fmt;
	काष्ठा emmaprp_ctx *ctx = priv;

	fmt = find_क्रमmat(f);
	अगर (!fmt || !(fmt->types & MEM2MEM_CAPTURE)) अणु
		v4l2_err(&ctx->dev->v4l2_dev,
			 "Fourcc format (0x%08x) invalid.\n",
			 f->fmt.pix.pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	वापस vidioc_try_fmt(f);
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा emmaprp_fmt *fmt;
	काष्ठा emmaprp_ctx *ctx = priv;

	fmt = find_क्रमmat(f);
	अगर (!fmt || !(fmt->types & MEM2MEM_OUTPUT)) अणु
		v4l2_err(&ctx->dev->v4l2_dev,
			 "Fourcc format (0x%08x) invalid.\n",
			 f->fmt.pix.pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	वापस vidioc_try_fmt(f);
पूर्ण

अटल पूर्णांक vidioc_s_fmt(काष्ठा emmaprp_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा emmaprp_q_data *q_data;
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = get_q_data(ctx, f->type);
	अगर (!q_data)
		वापस -EINVAL;

	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(&ctx->dev->v4l2_dev, "%s queue busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	ret = vidioc_try_fmt(f);
	अगर (ret)
		वापस ret;

	q_data->fmt		= find_क्रमmat(f);
	q_data->width		= f->fmt.pix.width;
	q_data->height		= f->fmt.pix.height;
	अगर (q_data->fmt->fourcc == V4L2_PIX_FMT_YUV420)
		q_data->sizeimage = q_data->width * q_data->height * 3 / 2;
	अन्यथा /* YUYV */
		q_data->sizeimage = q_data->width * q_data->height * 2;

	dprपूर्णांकk(ctx->dev,
		"Setting format for type %d, wxh: %dx%d, fmt: %d\n",
		f->type, q_data->width, q_data->height, q_data->fmt->fourcc);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;

	ret = vidioc_try_fmt_vid_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	वापस vidioc_s_fmt(priv, f);
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;

	ret = vidioc_try_fmt_vid_out(file, priv, f);
	अगर (ret)
		वापस ret;

	वापस vidioc_s_fmt(priv, f);
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops emmaprp_ioctl_ops = अणु
	.vidioc_querycap	= vidioc_querycap,

	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap	= vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= vidioc_s_fmt_vid_cap,

	.vidioc_क्रमागत_fmt_vid_out = vidioc_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_out	= vidioc_g_fmt_vid_out,
	.vidioc_try_fmt_vid_out	= vidioc_try_fmt_vid_out,
	.vidioc_s_fmt_vid_out	= vidioc_s_fmt_vid_out,

	.vidioc_reqbufs		= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf	= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf		= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf		= v4l2_m2m_ioctl_dqbuf,
	.vidioc_prepare_buf	= v4l2_m2m_ioctl_prepare_buf,
	.vidioc_expbuf		= v4l2_m2m_ioctl_expbuf,
	.vidioc_streamon	= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff	= v4l2_m2m_ioctl_streamoff,
पूर्ण;


/*
 * Queue operations
 */
अटल पूर्णांक emmaprp_queue_setup(काष्ठा vb2_queue *vq,
				अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
				अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा emmaprp_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा emmaprp_q_data *q_data;
	अचिन्हित पूर्णांक size, count = *nbuffers;

	q_data = get_q_data(ctx, vq->type);

	अगर (q_data->fmt->fourcc == V4L2_PIX_FMT_YUV420)
		size = q_data->width * q_data->height * 3 / 2;
	अन्यथा
		size = q_data->width * q_data->height * 2;

	जबतक (size * count > MEM2MEM_VID_MEM_LIMIT)
		(count)--;

	*nplanes = 1;
	*nbuffers = count;
	sizes[0] = size;

	dprपूर्णांकk(ctx->dev, "get %d buffer(s) of size %d each.\n", count, size);

	वापस 0;
पूर्ण

अटल पूर्णांक emmaprp_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा emmaprp_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा emmaprp_q_data *q_data;

	dprपूर्णांकk(ctx->dev, "type: %d\n", vb->vb2_queue->type);

	q_data = get_q_data(ctx, vb->vb2_queue->type);

	अगर (vb2_plane_size(vb, 0) < q_data->sizeimage) अणु
		dprपूर्णांकk(ctx->dev,
			"%s data will not fit into plane(%lu < %lu)\n",
			__func__, vb2_plane_size(vb, 0),
			(दीर्घ)q_data->sizeimage);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, q_data->sizeimage);

	वापस 0;
पूर्ण

अटल व्योम emmaprp_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा emmaprp_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल स्थिर काष्ठा vb2_ops emmaprp_qops = अणु
	.queue_setup	 = emmaprp_queue_setup,
	.buf_prepare	 = emmaprp_buf_prepare,
	.buf_queue	 = emmaprp_buf_queue,
	.रुको_prepare	 = vb2_ops_रुको_prepare,
	.रुको_finish	 = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
		      काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा emmaprp_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->ops = &emmaprp_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->dev = ctx->dev->v4l2_dev.dev;
	src_vq->lock = &ctx->dev->dev_mutex;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->ops = &emmaprp_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->dev = ctx->dev->v4l2_dev.dev;
	dst_vq->lock = &ctx->dev->dev_mutex;

	वापस vb2_queue_init(dst_vq);
पूर्ण

/*
 * File operations
 */
अटल पूर्णांक emmaprp_खोलो(काष्ठा file *file)
अणु
	काष्ठा emmaprp_dev *pcdev = video_drvdata(file);
	काष्ठा emmaprp_ctx *ctx;

	ctx = kzalloc(माप *ctx, GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	ctx->dev = pcdev;

	अगर (mutex_lock_पूर्णांकerruptible(&pcdev->dev_mutex)) अणु
		kमुक्त(ctx);
		वापस -ERESTARTSYS;
	पूर्ण

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(pcdev->m2m_dev, ctx, &queue_init);

	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		पूर्णांक ret = PTR_ERR(ctx->fh.m2m_ctx);

		mutex_unlock(&pcdev->dev_mutex);
		kमुक्त(ctx);
		वापस ret;
	पूर्ण

	clk_prepare_enable(pcdev->clk_emma_ipg);
	clk_prepare_enable(pcdev->clk_emma_ahb);
	ctx->q_data[V4L2_M2M_SRC].fmt = &क्रमmats[1];
	ctx->q_data[V4L2_M2M_DST].fmt = &क्रमmats[0];
	v4l2_fh_add(&ctx->fh);
	mutex_unlock(&pcdev->dev_mutex);

	dprपूर्णांकk(pcdev, "Created instance %p, m2m_ctx: %p\n", ctx, ctx->fh.m2m_ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक emmaprp_release(काष्ठा file *file)
अणु
	काष्ठा emmaprp_dev *pcdev = video_drvdata(file);
	काष्ठा emmaprp_ctx *ctx = file->निजी_data;

	dprपूर्णांकk(pcdev, "Releasing instance %p\n", ctx);

	mutex_lock(&pcdev->dev_mutex);
	clk_disable_unprepare(pcdev->clk_emma_ahb);
	clk_disable_unprepare(pcdev->clk_emma_ipg);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	mutex_unlock(&pcdev->dev_mutex);
	kमुक्त(ctx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations emmaprp_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= emmaprp_खोलो,
	.release	= emmaprp_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा video_device emmaprp_videodev = अणु
	.name		= MEM2MEM_NAME,
	.fops		= &emmaprp_fops,
	.ioctl_ops	= &emmaprp_ioctl_ops,
	.minor		= -1,
	.release	= video_device_release,
	.vfl_dir	= VFL_सूची_M2M,
	.device_caps	= V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops m2m_ops = अणु
	.device_run	= emmaprp_device_run,
	.job_पात	= emmaprp_job_पात,
पूर्ण;

अटल पूर्णांक emmaprp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा emmaprp_dev *pcdev;
	काष्ठा video_device *vfd;
	काष्ठा resource *res;
	पूर्णांक irq, ret;

	pcdev = devm_kzalloc(&pdev->dev, माप(*pcdev), GFP_KERNEL);
	अगर (!pcdev)
		वापस -ENOMEM;

	spin_lock_init(&pcdev->irqlock);

	pcdev->clk_emma_ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(pcdev->clk_emma_ipg)) अणु
		वापस PTR_ERR(pcdev->clk_emma_ipg);
	पूर्ण

	pcdev->clk_emma_ahb = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(pcdev->clk_emma_ahb))
		वापस PTR_ERR(pcdev->clk_emma_ahb);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	pcdev->base_emma = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(pcdev->base_emma))
		वापस PTR_ERR(pcdev->base_emma);

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &pcdev->v4l2_dev);
	अगर (ret)
		वापस ret;

	mutex_init(&pcdev->dev_mutex);

	vfd = video_device_alloc();
	अगर (!vfd) अणु
		v4l2_err(&pcdev->v4l2_dev, "Failed to allocate video device\n");
		ret = -ENOMEM;
		जाओ unreg_dev;
	पूर्ण

	*vfd = emmaprp_videodev;
	vfd->lock = &pcdev->dev_mutex;
	vfd->v4l2_dev = &pcdev->v4l2_dev;

	video_set_drvdata(vfd, pcdev);
	pcdev->vfd = vfd;
	v4l2_info(&pcdev->v4l2_dev, EMMAPRP_MODULE_NAME
		  " Device registered as /dev/video%d\n", vfd->num);

	platक्रमm_set_drvdata(pdev, pcdev);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ rel_vdev;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, emmaprp_irq, 0,
			       dev_name(&pdev->dev), pcdev);
	अगर (ret)
		जाओ rel_vdev;

	pcdev->m2m_dev = v4l2_m2m_init(&m2m_ops);
	अगर (IS_ERR(pcdev->m2m_dev)) अणु
		v4l2_err(&pcdev->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(pcdev->m2m_dev);
		जाओ rel_vdev;
	पूर्ण

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, 0);
	अगर (ret) अणु
		v4l2_err(&pcdev->v4l2_dev, "Failed to register video device\n");
		जाओ rel_m2m;
	पूर्ण

	वापस 0;


rel_m2m:
	v4l2_m2m_release(pcdev->m2m_dev);
rel_vdev:
	video_device_release(vfd);
unreg_dev:
	v4l2_device_unरेजिस्टर(&pcdev->v4l2_dev);

	mutex_destroy(&pcdev->dev_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक emmaprp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा emmaprp_dev *pcdev = platक्रमm_get_drvdata(pdev);

	v4l2_info(&pcdev->v4l2_dev, "Removing " EMMAPRP_MODULE_NAME);

	video_unरेजिस्टर_device(pcdev->vfd);
	v4l2_m2m_release(pcdev->m2m_dev);
	v4l2_device_unरेजिस्टर(&pcdev->v4l2_dev);
	mutex_destroy(&pcdev->dev_mutex);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver emmaprp_pdrv = अणु
	.probe		= emmaprp_probe,
	.हटाओ		= emmaprp_हटाओ,
	.driver		= अणु
		.name	= MEM2MEM_NAME,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(emmaprp_pdrv);
