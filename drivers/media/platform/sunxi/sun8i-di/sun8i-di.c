<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Allwinner sun8i deपूर्णांकerlacer with scaler driver
 *
 * Copyright (C) 2019 Jernej Skrabec <jernej.skrabec@siol.net>
 *
 * Based on vim2m driver.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mem2स्मृति.स>

#समावेश "sun8i-di.h"

#घोषणा FLAG_SIZE (DEINTERLACE_MAX_WIDTH * DEINTERLACE_MAX_HEIGHT / 4)

अटल u32 deपूर्णांकerlace_क्रमmats[] = अणु
	V4L2_PIX_FMT_NV12,
	V4L2_PIX_FMT_NV21,
पूर्ण;

अटल अंतरभूत u32 deपूर्णांकerlace_पढ़ो(काष्ठा deपूर्णांकerlace_dev *dev, u32 reg)
अणु
	वापस पढ़ोl(dev->base + reg);
पूर्ण

अटल अंतरभूत व्योम deपूर्णांकerlace_ग_लिखो(काष्ठा deपूर्णांकerlace_dev *dev,
				     u32 reg, u32 value)
अणु
	ग_लिखोl(value, dev->base + reg);
पूर्ण

अटल अंतरभूत व्योम deपूर्णांकerlace_set_bits(काष्ठा deपूर्णांकerlace_dev *dev,
					u32 reg, u32 bits)
अणु
	ग_लिखोl(पढ़ोl(dev->base + reg) | bits, dev->base + reg);
पूर्ण

अटल अंतरभूत व्योम deपूर्णांकerlace_clr_set_bits(काष्ठा deपूर्णांकerlace_dev *dev,
					    u32 reg, u32 clr, u32 set)
अणु
	u32 val = पढ़ोl(dev->base + reg);

	val &= ~clr;
	val |= set;

	ग_लिखोl(val, dev->base + reg);
पूर्ण

अटल व्योम deपूर्णांकerlace_device_run(व्योम *priv)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = priv;
	काष्ठा deपूर्णांकerlace_dev *dev = ctx->dev;
	u32 size, stride, width, height, val;
	काष्ठा vb2_v4l2_buffer *src, *dst;
	अचिन्हित पूर्णांक hstep, vstep;
	dma_addr_t addr;

	src = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	v4l2_m2m_buf_copy_metadata(src, dst, true);

	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_MOD_ENABLE,
			  DEINTERLACE_MOD_ENABLE_EN);

	अगर (ctx->field) अणु
		deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_TILE_FLAG0,
				  ctx->flag1_buf_dma);
		deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_TILE_FLAG1,
				  ctx->flag2_buf_dma);
	पूर्ण अन्यथा अणु
		deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_TILE_FLAG0,
				  ctx->flag2_buf_dma);
		deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_TILE_FLAG1,
				  ctx->flag1_buf_dma);
	पूर्ण
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_FLAG_LINE_STRIDE, 0x200);

	width = ctx->src_fmt.width;
	height = ctx->src_fmt.height;
	stride = ctx->src_fmt.bytesperline;
	size = stride * height;

	addr = vb2_dma_contig_plane_dma_addr(&src->vb2_buf, 0);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_BUF_ADDR0, addr);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_BUF_ADDR1, addr + size);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_BUF_ADDR2, 0);

	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_LINE_STRIDE0, stride);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_LINE_STRIDE1, stride);

	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_CH0_IN_SIZE,
			  DEINTERLACE_SIZE(width, height));
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_CH1_IN_SIZE,
			  DEINTERLACE_SIZE(width / 2, height / 2));

	val = DEINTERLACE_IN_FMT_FMT(DEINTERLACE_IN_FMT_YUV420) |
	      DEINTERLACE_IN_FMT_MOD(DEINTERLACE_MODE_UV_COMBINED);
	चयन (ctx->src_fmt.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12:
		val |= DEINTERLACE_IN_FMT_PS(DEINTERLACE_PS_UVUV);
		अवरोध;
	हाल V4L2_PIX_FMT_NV21:
		val |= DEINTERLACE_IN_FMT_PS(DEINTERLACE_PS_VUVU);
		अवरोध;
	पूर्ण
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_IN_FMT, val);

	अगर (ctx->prev)
		addr = vb2_dma_contig_plane_dma_addr(&ctx->prev->vb2_buf, 0);

	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_PRELUMA, addr);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_PRECHROMA, addr + size);

	val = DEINTERLACE_OUT_FMT_FMT(DEINTERLACE_OUT_FMT_YUV420SP);
	चयन (ctx->src_fmt.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12:
		val |= DEINTERLACE_OUT_FMT_PS(DEINTERLACE_PS_UVUV);
		अवरोध;
	हाल V4L2_PIX_FMT_NV21:
		val |= DEINTERLACE_OUT_FMT_PS(DEINTERLACE_PS_VUVU);
		अवरोध;
	पूर्ण
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_OUT_FMT, val);

	width = ctx->dst_fmt.width;
	height = ctx->dst_fmt.height;
	stride = ctx->dst_fmt.bytesperline;
	size = stride * height;

	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_CH0_OUT_SIZE,
			  DEINTERLACE_SIZE(width, height));
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_CH1_OUT_SIZE,
			  DEINTERLACE_SIZE(width / 2, height / 2));

	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_WB_LINE_STRIDE0, stride);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_WB_LINE_STRIDE1, stride);

	addr = vb2_dma_contig_plane_dma_addr(&dst->vb2_buf, 0);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_WB_ADDR0, addr);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_WB_ADDR1, addr + size);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_WB_ADDR2, 0);

	hstep = (ctx->src_fmt.width << 16) / ctx->dst_fmt.width;
	vstep = (ctx->src_fmt.height << 16) / ctx->dst_fmt.height;
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_CH0_HORZ_FACT, hstep);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_CH0_VERT_FACT, vstep);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_CH1_HORZ_FACT, hstep);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_CH1_VERT_FACT, vstep);

	deपूर्णांकerlace_clr_set_bits(dev, DEINTERLACE_FIELD_CTRL,
				 DEINTERLACE_FIELD_CTRL_FIELD_CNT_MSK,
				 DEINTERLACE_FIELD_CTRL_FIELD_CNT(ctx->field));

	deपूर्णांकerlace_set_bits(dev, DEINTERLACE_FRM_CTRL,
			     DEINTERLACE_FRM_CTRL_START);

	deपूर्णांकerlace_set_bits(dev, DEINTERLACE_FRM_CTRL,
			     DEINTERLACE_FRM_CTRL_REG_READY);

	deपूर्णांकerlace_set_bits(dev, DEINTERLACE_INT_ENABLE,
			     DEINTERLACE_INT_ENABLE_WB_EN);

	deपूर्णांकerlace_set_bits(dev, DEINTERLACE_FRM_CTRL,
			     DEINTERLACE_FRM_CTRL_WB_EN);
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_job_पढ़ोy(व्योम *priv)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = priv;

	वापस v4l2_m2m_num_src_bufs_पढ़ोy(ctx->fh.m2m_ctx) >= 1 &&
	       v4l2_m2m_num_dst_bufs_पढ़ोy(ctx->fh.m2m_ctx) >= 2;
पूर्ण

अटल व्योम deपूर्णांकerlace_job_पात(व्योम *priv)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = priv;

	/* Will cancel the transaction in the next पूर्णांकerrupt handler */
	ctx->पातing = 1;
पूर्ण

अटल irqवापस_t deपूर्णांकerlace_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा deपूर्णांकerlace_dev *dev = data;
	काष्ठा vb2_v4l2_buffer *src, *dst;
	क्रमागत vb2_buffer_state state;
	काष्ठा deपूर्णांकerlace_ctx *ctx;
	अचिन्हित पूर्णांक val;

	ctx = v4l2_m2m_get_curr_priv(dev->m2m_dev);
	अगर (!ctx) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Instance released before the end of transaction\n");
		वापस IRQ_NONE;
	पूर्ण

	val = deपूर्णांकerlace_पढ़ो(dev, DEINTERLACE_INT_STATUS);
	अगर (!(val & DEINTERLACE_INT_STATUS_WRITEBACK))
		वापस IRQ_NONE;

	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_INT_ENABLE, 0);
	deपूर्णांकerlace_set_bits(dev, DEINTERLACE_INT_STATUS,
			     DEINTERLACE_INT_STATUS_WRITEBACK);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_MOD_ENABLE, 0);
	deपूर्णांकerlace_clr_set_bits(dev, DEINTERLACE_FRM_CTRL,
				 DEINTERLACE_FRM_CTRL_START, 0);

	val = deपूर्णांकerlace_पढ़ो(dev, DEINTERLACE_STATUS);
	अगर (val & DEINTERLACE_STATUS_WB_ERROR)
		state = VB2_BUF_STATE_ERROR;
	अन्यथा
		state = VB2_BUF_STATE_DONE;

	dst = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
	v4l2_m2m_buf_करोne(dst, state);

	अगर (ctx->field != ctx->first_field || ctx->पातing) अणु
		ctx->field = ctx->first_field;

		src = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		अगर (ctx->prev)
			v4l2_m2m_buf_करोne(ctx->prev, state);
		ctx->prev = src;

		v4l2_m2m_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx);
	पूर्ण अन्यथा अणु
		ctx->field = !ctx->first_field;
		deपूर्णांकerlace_device_run(ctx);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम deपूर्णांकerlace_init(काष्ठा deपूर्णांकerlace_dev *dev)
अणु
	u32 val;
	पूर्णांक i;

	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_BYPASS,
			  DEINTERLACE_BYPASS_CSC);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_WB_LINE_STRIDE_CTRL,
			  DEINTERLACE_WB_LINE_STRIDE_CTRL_EN);
	deपूर्णांकerlace_set_bits(dev, DEINTERLACE_FRM_CTRL,
			     DEINTERLACE_FRM_CTRL_OUT_CTRL);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_AGTH_SEL,
			  DEINTERLACE_AGTH_SEL_LINEBUF);

	val = DEINTERLACE_CTRL_EN |
	      DEINTERLACE_CTRL_MODE_MIXED |
	      DEINTERLACE_CTRL_DIAG_INTP_EN |
	      DEINTERLACE_CTRL_TEMP_DIFF_EN;
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_CTRL, val);

	deपूर्णांकerlace_clr_set_bits(dev, DEINTERLACE_LUMA_TH,
				 DEINTERLACE_LUMA_TH_MIN_LUMA_MSK,
				 DEINTERLACE_LUMA_TH_MIN_LUMA(4));

	deपूर्णांकerlace_clr_set_bits(dev, DEINTERLACE_SPAT_COMP,
				 DEINTERLACE_SPAT_COMP_TH2_MSK,
				 DEINTERLACE_SPAT_COMP_TH2(5));

	deपूर्णांकerlace_clr_set_bits(dev, DEINTERLACE_TEMP_DIFF,
				 DEINTERLACE_TEMP_DIFF_AMBIGUITY_TH_MSK,
				 DEINTERLACE_TEMP_DIFF_AMBIGUITY_TH(5));

	val = DEINTERLACE_DIAG_INTP_TH0(60) |
	      DEINTERLACE_DIAG_INTP_TH1(0) |
	      DEINTERLACE_DIAG_INTP_TH3(30);
	deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_DIAG_INTP, val);

	deपूर्णांकerlace_clr_set_bits(dev, DEINTERLACE_CHROMA_DIFF,
				 DEINTERLACE_CHROMA_DIFF_TH_MSK,
				 DEINTERLACE_CHROMA_DIFF_TH(5));

	/* neutral filter coefficients */
	deपूर्णांकerlace_set_bits(dev, DEINTERLACE_FRM_CTRL,
			     DEINTERLACE_FRM_CTRL_COEF_ACCESS);
	पढ़ोl_poll_समयout(dev->base + DEINTERLACE_STATUS, val,
			   val & DEINTERLACE_STATUS_COEF_STATUS, 2, 40);

	क्रम (i = 0; i < 32; i++) अणु
		deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_CH0_HORZ_COEF0 + i * 4,
				  DEINTERLACE_IDENTITY_COEF);
		deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_CH0_VERT_COEF + i * 4,
				  DEINTERLACE_IDENTITY_COEF);
		deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_CH1_HORZ_COEF0 + i * 4,
				  DEINTERLACE_IDENTITY_COEF);
		deपूर्णांकerlace_ग_लिखो(dev, DEINTERLACE_CH1_VERT_COEF + i * 4,
				  DEINTERLACE_IDENTITY_COEF);
	पूर्ण

	deपूर्णांकerlace_clr_set_bits(dev, DEINTERLACE_FRM_CTRL,
				 DEINTERLACE_FRM_CTRL_COEF_ACCESS, 0);
पूर्ण

अटल अंतरभूत काष्ठा deपूर्णांकerlace_ctx *deपूर्णांकerlace_file2ctx(काष्ठा file *file)
अणु
	वापस container_of(file->निजी_data, काष्ठा deपूर्णांकerlace_ctx, fh);
पूर्ण

अटल bool deपूर्णांकerlace_check_क्रमmat(u32 pixelक्रमmat)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(deपूर्णांकerlace_क्रमmats); i++)
		अगर (deपूर्णांकerlace_क्रमmats[i] == pixelक्रमmat)
			वापस true;

	वापस false;
पूर्ण

अटल व्योम deपूर्णांकerlace_prepare_क्रमmat(काष्ठा v4l2_pix_क्रमmat *pix_fmt)
अणु
	अचिन्हित पूर्णांक height = pix_fmt->height;
	अचिन्हित पूर्णांक width = pix_fmt->width;
	अचिन्हित पूर्णांक bytesperline;
	अचिन्हित पूर्णांक sizeimage;

	width = clamp(width, DEINTERLACE_MIN_WIDTH,
		      DEINTERLACE_MAX_WIDTH);
	height = clamp(height, DEINTERLACE_MIN_HEIGHT,
		       DEINTERLACE_MAX_HEIGHT);

	bytesperline = ALIGN(width, 2);
	/* luma */
	sizeimage = bytesperline * height;
	/* chroma */
	sizeimage += bytesperline * height / 2;

	pix_fmt->width = width;
	pix_fmt->height = height;
	pix_fmt->bytesperline = bytesperline;
	pix_fmt->sizeimage = sizeimage;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_querycap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, DEINTERLACE_NAME, माप(cap->driver));
	strscpy(cap->card, DEINTERLACE_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "platform:%s", DEINTERLACE_NAME);

	वापस 0;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_क्रमागत_fmt(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index < ARRAY_SIZE(deपूर्णांकerlace_क्रमmats)) अणु
		f->pixelक्रमmat = deपूर्णांकerlace_क्रमmats[f->index];

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_क्रमागत_framesizes(काष्ठा file *file, व्योम *priv,
				       काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	अगर (fsize->index != 0)
		वापस -EINVAL;

	अगर (!deपूर्णांकerlace_check_क्रमmat(fsize->pixel_क्रमmat))
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	fsize->stepwise.min_width = DEINTERLACE_MIN_WIDTH;
	fsize->stepwise.min_height = DEINTERLACE_MIN_HEIGHT;
	fsize->stepwise.max_width = DEINTERLACE_MAX_WIDTH;
	fsize->stepwise.max_height = DEINTERLACE_MAX_HEIGHT;
	fsize->stepwise.step_width = 2;
	fsize->stepwise.step_height = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = deपूर्णांकerlace_file2ctx(file);

	f->fmt.pix = ctx->dst_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_g_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = deपूर्णांकerlace_file2ctx(file);

	f->fmt.pix = ctx->src_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				       काष्ठा v4l2_क्रमmat *f)
अणु
	अगर (!deपूर्णांकerlace_check_क्रमmat(f->fmt.pix.pixelक्रमmat))
		f->fmt.pix.pixelक्रमmat = deपूर्णांकerlace_क्रमmats[0];

	अगर (f->fmt.pix.field != V4L2_FIELD_NONE)
		f->fmt.pix.field = V4L2_FIELD_NONE;

	deपूर्णांकerlace_prepare_क्रमmat(&f->fmt.pix);

	वापस 0;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				       काष्ठा v4l2_क्रमmat *f)
अणु
	अगर (!deपूर्णांकerlace_check_क्रमmat(f->fmt.pix.pixelक्रमmat))
		f->fmt.pix.pixelक्रमmat = deपूर्णांकerlace_क्रमmats[0];

	अगर (f->fmt.pix.field != V4L2_FIELD_INTERLACED_TB &&
	    f->fmt.pix.field != V4L2_FIELD_INTERLACED_BT &&
	    f->fmt.pix.field != V4L2_FIELD_INTERLACED)
		f->fmt.pix.field = V4L2_FIELD_INTERLACED;

	deपूर्णांकerlace_prepare_क्रमmat(&f->fmt.pix);

	वापस 0;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = deपूर्णांकerlace_file2ctx(file);
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	ret = deपूर्णांकerlace_try_fmt_vid_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_busy(vq))
		वापस -EBUSY;

	ctx->dst_fmt = f->fmt.pix;

	वापस 0;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = deपूर्णांकerlace_file2ctx(file);
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	ret = deपूर्णांकerlace_try_fmt_vid_out(file, priv, f);
	अगर (ret)
		वापस ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	अगर (vb2_is_busy(vq))
		वापस -EBUSY;

	ctx->src_fmt = f->fmt.pix;

	/* Propagate colorspace inक्रमmation to capture. */
	ctx->dst_fmt.colorspace = f->fmt.pix.colorspace;
	ctx->dst_fmt.xfer_func = f->fmt.pix.xfer_func;
	ctx->dst_fmt.ycbcr_enc = f->fmt.pix.ycbcr_enc;
	ctx->dst_fmt.quantization = f->fmt.pix.quantization;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops deपूर्णांकerlace_ioctl_ops = अणु
	.vidioc_querycap		= deपूर्णांकerlace_querycap,

	.vidioc_क्रमागत_framesizes		= deपूर्णांकerlace_क्रमागत_framesizes,

	.vidioc_क्रमागत_fmt_vid_cap	= deपूर्णांकerlace_क्रमागत_fmt,
	.vidioc_g_fmt_vid_cap		= deपूर्णांकerlace_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		= deपूर्णांकerlace_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= deपूर्णांकerlace_s_fmt_vid_cap,

	.vidioc_क्रमागत_fmt_vid_out	= deपूर्णांकerlace_क्रमागत_fmt,
	.vidioc_g_fmt_vid_out		= deपूर्णांकerlace_g_fmt_vid_out,
	.vidioc_try_fmt_vid_out		= deपूर्णांकerlace_try_fmt_vid_out,
	.vidioc_s_fmt_vid_out		= deपूर्णांकerlace_s_fmt_vid_out,

	.vidioc_reqbufs			= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf		= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf			= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf			= v4l2_m2m_ioctl_dqbuf,
	.vidioc_prepare_buf		= v4l2_m2m_ioctl_prepare_buf,
	.vidioc_create_bufs		= v4l2_m2m_ioctl_create_bufs,
	.vidioc_expbuf			= v4l2_m2m_ioctl_expbuf,

	.vidioc_streamon		= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff		= v4l2_m2m_ioctl_streamoff,
पूर्ण;

अटल पूर्णांक deपूर्णांकerlace_queue_setup(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक *nbuffers,
				   अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[],
				   काष्ठा device *alloc_devs[])
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा v4l2_pix_क्रमmat *pix_fmt;

	अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
		pix_fmt = &ctx->src_fmt;
	अन्यथा
		pix_fmt = &ctx->dst_fmt;

	अगर (*nplanes) अणु
		अगर (sizes[0] < pix_fmt->sizeimage)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		sizes[0] = pix_fmt->sizeimage;
		*nplanes = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा deपूर्णांकerlace_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा v4l2_pix_क्रमmat *pix_fmt;

	अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
		pix_fmt = &ctx->src_fmt;
	अन्यथा
		pix_fmt = &ctx->dst_fmt;

	अगर (vb2_plane_size(vb, 0) < pix_fmt->sizeimage)
		वापस -EINVAL;

	vb2_set_plane_payload(vb, 0, pix_fmt->sizeimage);

	वापस 0;
पूर्ण

अटल व्योम deपूर्णांकerlace_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा deपूर्णांकerlace_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल व्योम deपूर्णांकerlace_queue_cleanup(काष्ठा vb2_queue *vq, u32 state)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा vb2_v4l2_buffer *vbuf;

	करो अणु
		अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
			vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		अन्यथा
			vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);

		अगर (vbuf)
			v4l2_m2m_buf_करोne(vbuf, state);
	पूर्ण जबतक (vbuf);

	अगर (V4L2_TYPE_IS_OUTPUT(vq->type) && ctx->prev)
		v4l2_m2m_buf_करोne(ctx->prev, state);
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा device *dev = ctx->dev->dev;
	पूर्णांक ret;

	अगर (V4L2_TYPE_IS_OUTPUT(vq->type)) अणु
		ret = pm_runसमय_resume_and_get(dev);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to enable module\n");

			जाओ err_runसमय_get;
		पूर्ण

		ctx->first_field =
			ctx->src_fmt.field == V4L2_FIELD_INTERLACED_BT;
		ctx->field = ctx->first_field;

		ctx->prev = शून्य;
		ctx->पातing = 0;

		ctx->flag1_buf = dma_alloc_coherent(dev, FLAG_SIZE,
						    &ctx->flag1_buf_dma,
						    GFP_KERNEL);
		अगर (!ctx->flag1_buf) अणु
			ret = -ENOMEM;

			जाओ err_no_mem1;
		पूर्ण

		ctx->flag2_buf = dma_alloc_coherent(dev, FLAG_SIZE,
						    &ctx->flag2_buf_dma,
						    GFP_KERNEL);
		अगर (!ctx->flag2_buf) अणु
			ret = -ENOMEM;

			जाओ err_no_mem2;
		पूर्ण
	पूर्ण

	वापस 0;

err_no_mem2:
	dma_मुक्त_coherent(dev, FLAG_SIZE, ctx->flag1_buf,
			  ctx->flag1_buf_dma);
err_no_mem1:
	pm_runसमय_put(dev);
err_runसमय_get:
	deपूर्णांकerlace_queue_cleanup(vq, VB2_BUF_STATE_QUEUED);

	वापस ret;
पूर्ण

अटल व्योम deपूर्णांकerlace_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = vb2_get_drv_priv(vq);

	अगर (V4L2_TYPE_IS_OUTPUT(vq->type)) अणु
		काष्ठा device *dev = ctx->dev->dev;

		dma_मुक्त_coherent(dev, FLAG_SIZE, ctx->flag1_buf,
				  ctx->flag1_buf_dma);
		dma_मुक्त_coherent(dev, FLAG_SIZE, ctx->flag2_buf,
				  ctx->flag2_buf_dma);

		pm_runसमय_put(dev);
	पूर्ण

	deपूर्णांकerlace_queue_cleanup(vq, VB2_BUF_STATE_ERROR);
पूर्ण

अटल स्थिर काष्ठा vb2_ops deपूर्णांकerlace_qops = अणु
	.queue_setup		= deपूर्णांकerlace_queue_setup,
	.buf_prepare		= deपूर्णांकerlace_buf_prepare,
	.buf_queue		= deपूर्णांकerlace_buf_queue,
	.start_streaming	= deपूर्णांकerlace_start_streaming,
	.stop_streaming		= deपूर्णांकerlace_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक deपूर्णांकerlace_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
				  काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा deपूर्णांकerlace_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->min_buffers_needed = 1;
	src_vq->ops = &deपूर्णांकerlace_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->dev->dev_mutex;
	src_vq->dev = ctx->dev->dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->min_buffers_needed = 2;
	dst_vq->ops = &deपूर्णांकerlace_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->dev->dev_mutex;
	dst_vq->dev = ctx->dev->dev;

	ret = vb2_queue_init(dst_vq);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_खोलो(काष्ठा file *file)
अणु
	काष्ठा deपूर्णांकerlace_dev *dev = video_drvdata(file);
	काष्ठा deपूर्णांकerlace_ctx *ctx = शून्य;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->dev_mutex))
		वापस -ERESTARTSYS;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		mutex_unlock(&dev->dev_mutex);
		वापस -ENOMEM;
	पूर्ण

	/* शेष output क्रमmat */
	ctx->src_fmt.pixelक्रमmat = deपूर्णांकerlace_क्रमmats[0];
	ctx->src_fmt.field = V4L2_FIELD_INTERLACED;
	ctx->src_fmt.width = 640;
	ctx->src_fmt.height = 480;
	deपूर्णांकerlace_prepare_क्रमmat(&ctx->src_fmt);

	/* शेष capture क्रमmat */
	ctx->dst_fmt.pixelक्रमmat = deपूर्णांकerlace_क्रमmats[0];
	ctx->dst_fmt.field = V4L2_FIELD_NONE;
	ctx->dst_fmt.width = 640;
	ctx->dst_fmt.height = 480;
	deपूर्णांकerlace_prepare_क्रमmat(&ctx->dst_fmt);

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	ctx->dev = dev;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev, ctx,
					    &deपूर्णांकerlace_queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		जाओ err_मुक्त;
	पूर्ण

	v4l2_fh_add(&ctx->fh);

	mutex_unlock(&dev->dev_mutex);

	वापस 0;

err_मुक्त:
	kमुक्त(ctx);
	mutex_unlock(&dev->dev_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_release(काष्ठा file *file)
अणु
	काष्ठा deपूर्णांकerlace_dev *dev = video_drvdata(file);
	काष्ठा deपूर्णांकerlace_ctx *ctx = container_of(file->निजी_data,
						   काष्ठा deपूर्णांकerlace_ctx, fh);

	mutex_lock(&dev->dev_mutex);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);

	kमुक्त(ctx);

	mutex_unlock(&dev->dev_mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations deपूर्णांकerlace_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= deपूर्णांकerlace_खोलो,
	.release	= deपूर्णांकerlace_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा video_device deपूर्णांकerlace_video_device = अणु
	.name		= DEINTERLACE_NAME,
	.vfl_dir	= VFL_सूची_M2M,
	.fops		= &deपूर्णांकerlace_fops,
	.ioctl_ops	= &deपूर्णांकerlace_ioctl_ops,
	.minor		= -1,
	.release	= video_device_release_empty,
	.device_caps	= V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops deपूर्णांकerlace_m2m_ops = अणु
	.device_run	= deपूर्णांकerlace_device_run,
	.job_पढ़ोy	= deपूर्णांकerlace_job_पढ़ोy,
	.job_पात	= deपूर्णांकerlace_job_पात,
पूर्ण;

अटल पूर्णांक deपूर्णांकerlace_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा deपूर्णांकerlace_dev *dev;
	काष्ठा video_device *vfd;
	काष्ठा resource *res;
	पूर्णांक irq, ret;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->vfd = deपूर्णांकerlace_video_device;
	dev->dev = &pdev->dev;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq;

	ret = devm_request_irq(dev->dev, irq, deपूर्णांकerlace_irq,
			       0, dev_name(dev->dev), dev);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to request IRQ\n");

		वापस ret;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dev->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dev->base))
		वापस PTR_ERR(dev->base);

	dev->bus_clk = devm_clk_get(dev->dev, "bus");
	अगर (IS_ERR(dev->bus_clk)) अणु
		dev_err(dev->dev, "Failed to get bus clock\n");

		वापस PTR_ERR(dev->bus_clk);
	पूर्ण

	dev->mod_clk = devm_clk_get(dev->dev, "mod");
	अगर (IS_ERR(dev->mod_clk)) अणु
		dev_err(dev->dev, "Failed to get mod clock\n");

		वापस PTR_ERR(dev->mod_clk);
	पूर्ण

	dev->ram_clk = devm_clk_get(dev->dev, "ram");
	अगर (IS_ERR(dev->ram_clk)) अणु
		dev_err(dev->dev, "Failed to get ram clock\n");

		वापस PTR_ERR(dev->ram_clk);
	पूर्ण

	dev->rstc = devm_reset_control_get(dev->dev, शून्य);
	अगर (IS_ERR(dev->rstc)) अणु
		dev_err(dev->dev, "Failed to get reset control\n");

		वापस PTR_ERR(dev->rstc);
	पूर्ण

	mutex_init(&dev->dev_mutex);

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dev->v4l2_dev);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to register V4L2 device\n");

		वापस ret;
	पूर्ण

	vfd = &dev->vfd;
	vfd->lock = &dev->dev_mutex;
	vfd->v4l2_dev = &dev->v4l2_dev;

	snम_लिखो(vfd->name, माप(vfd->name), "%s",
		 deपूर्णांकerlace_video_device.name);
	video_set_drvdata(vfd, dev);

	ret = video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, 0);
	अगर (ret) अणु
		v4l2_err(&dev->v4l2_dev, "Failed to register video device\n");

		जाओ err_v4l2;
	पूर्ण

	v4l2_info(&dev->v4l2_dev,
		  "Device registered as /dev/video%d\n", vfd->num);

	dev->m2m_dev = v4l2_m2m_init(&deपूर्णांकerlace_m2m_ops);
	अगर (IS_ERR(dev->m2m_dev)) अणु
		v4l2_err(&dev->v4l2_dev,
			 "Failed to initialize V4L2 M2M device\n");
		ret = PTR_ERR(dev->m2m_dev);

		जाओ err_video;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dev);

	pm_runसमय_enable(dev->dev);

	वापस 0;

err_video:
	video_unरेजिस्टर_device(&dev->vfd);
err_v4l2:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा deपूर्णांकerlace_dev *dev = platक्रमm_get_drvdata(pdev);

	v4l2_m2m_release(dev->m2m_dev);
	video_unरेजिस्टर_device(&dev->vfd);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	pm_runसमय_क्रमce_suspend(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_runसमय_resume(काष्ठा device *device)
अणु
	काष्ठा deपूर्णांकerlace_dev *dev = dev_get_drvdata(device);
	पूर्णांक ret;

	ret = clk_set_rate_exclusive(dev->mod_clk, 300000000);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to set exclusive mod clock rate\n");

		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(dev->bus_clk);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to enable bus clock\n");

		जाओ err_exclusive_rate;
	पूर्ण

	ret = clk_prepare_enable(dev->mod_clk);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to enable mod clock\n");

		जाओ err_bus_clk;
	पूर्ण

	ret = clk_prepare_enable(dev->ram_clk);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to enable ram clock\n");

		जाओ err_mod_clk;
	पूर्ण

	ret = reset_control_deनिश्चित(dev->rstc);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to apply reset\n");

		जाओ err_ram_clk;
	पूर्ण

	deपूर्णांकerlace_init(dev);

	वापस 0;

err_ram_clk:
	clk_disable_unprepare(dev->ram_clk);
err_mod_clk:
	clk_disable_unprepare(dev->mod_clk);
err_bus_clk:
	clk_disable_unprepare(dev->bus_clk);
err_exclusive_rate:
	clk_rate_exclusive_put(dev->mod_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक deपूर्णांकerlace_runसमय_suspend(काष्ठा device *device)
अणु
	काष्ठा deपूर्णांकerlace_dev *dev = dev_get_drvdata(device);

	reset_control_निश्चित(dev->rstc);

	clk_disable_unprepare(dev->ram_clk);
	clk_disable_unprepare(dev->mod_clk);
	clk_disable_unprepare(dev->bus_clk);
	clk_rate_exclusive_put(dev->mod_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id deपूर्णांकerlace_dt_match[] = अणु
	अणु .compatible = "allwinner,sun8i-h3-deinterlace" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, deपूर्णांकerlace_dt_match);

अटल स्थिर काष्ठा dev_pm_ops deपूर्णांकerlace_pm_ops = अणु
	.runसमय_resume		= deपूर्णांकerlace_runसमय_resume,
	.runसमय_suspend	= deपूर्णांकerlace_runसमय_suspend,
पूर्ण;

अटल काष्ठा platक्रमm_driver deपूर्णांकerlace_driver = अणु
	.probe		= deपूर्णांकerlace_probe,
	.हटाओ		= deपूर्णांकerlace_हटाओ,
	.driver		= अणु
		.name		= DEINTERLACE_NAME,
		.of_match_table	= deपूर्णांकerlace_dt_match,
		.pm		= &deपूर्णांकerlace_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(deपूर्णांकerlace_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jernej Skrabec <jernej.skrabec@siol.net>");
MODULE_DESCRIPTION("Allwinner Deinterlace driver");
