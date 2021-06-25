<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Samsung S5P/EXYNOS4 SoC series FIMC (CAMIF) driver
 *
 * Copyright (C) 2010-2012 Samsung Electronics Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "fimc-core.h"
#समावेश "fimc-reg.h"
#समावेश "media-dev.h"

अटल अक्षर *fimc_घड़ीs[MAX_FIMC_CLOCKS] = अणु
	"sclk_fimc", "fimc"
पूर्ण;

अटल काष्ठा fimc_fmt fimc_क्रमmats[] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB565,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_RGB565,
		.memplanes	= 1,
		.colplanes	= 1,
		.flags		= FMT_FLAGS_M2M,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_BGR666,
		.depth		= अणु 32 पूर्ण,
		.color		= FIMC_FMT_RGB666,
		.memplanes	= 1,
		.colplanes	= 1,
		.flags		= FMT_FLAGS_M2M,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_BGR32,
		.depth		= अणु 32 पूर्ण,
		.color		= FIMC_FMT_RGB888,
		.memplanes	= 1,
		.colplanes	= 1,
		.flags		= FMT_FLAGS_M2M | FMT_HAS_ALPHA,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB555,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_RGB555,
		.memplanes	= 1,
		.colplanes	= 1,
		.flags		= FMT_FLAGS_M2M_OUT | FMT_HAS_ALPHA,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_RGB444,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_RGB444,
		.memplanes	= 1,
		.colplanes	= 1,
		.flags		= FMT_FLAGS_M2M_OUT | FMT_HAS_ALPHA,
	पूर्ण, अणु
		.mbus_code	= MEDIA_BUS_FMT_YUV10_1X30,
		.flags		= FMT_FLAGS_WRITEBACK,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_YUYV,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_YCBYCR422,
		.memplanes	= 1,
		.colplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.flags		= FMT_FLAGS_M2M | FMT_FLAGS_CAM,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_UYVY,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_CBYCRY422,
		.memplanes	= 1,
		.colplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_UYVY8_2X8,
		.flags		= FMT_FLAGS_M2M | FMT_FLAGS_CAM,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_VYUY,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_CRYCBY422,
		.memplanes	= 1,
		.colplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_VYUY8_2X8,
		.flags		= FMT_FLAGS_M2M | FMT_FLAGS_CAM,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_YVYU,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_YCRYCB422,
		.memplanes	= 1,
		.colplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_YVYU8_2X8,
		.flags		= FMT_FLAGS_M2M | FMT_FLAGS_CAM,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_YUV422P,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_YCBYCR422,
		.memplanes	= 1,
		.colplanes	= 3,
		.flags		= FMT_FLAGS_M2M,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_NV16,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_YCBYCR422,
		.memplanes	= 1,
		.colplanes	= 2,
		.flags		= FMT_FLAGS_M2M,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_NV61,
		.depth		= अणु 16 पूर्ण,
		.color		= FIMC_FMT_YCRYCB422,
		.memplanes	= 1,
		.colplanes	= 2,
		.flags		= FMT_FLAGS_M2M,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_YUV420,
		.depth		= अणु 12 पूर्ण,
		.color		= FIMC_FMT_YCBCR420,
		.memplanes	= 1,
		.colplanes	= 3,
		.flags		= FMT_FLAGS_M2M,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_NV12,
		.depth		= अणु 12 पूर्ण,
		.color		= FIMC_FMT_YCBCR420,
		.memplanes	= 1,
		.colplanes	= 2,
		.flags		= FMT_FLAGS_M2M,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_NV12M,
		.color		= FIMC_FMT_YCBCR420,
		.depth		= अणु 8, 4 पूर्ण,
		.memplanes	= 2,
		.colplanes	= 2,
		.flags		= FMT_FLAGS_M2M,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_YUV420M,
		.color		= FIMC_FMT_YCBCR420,
		.depth		= अणु 8, 2, 2 पूर्ण,
		.memplanes	= 3,
		.colplanes	= 3,
		.flags		= FMT_FLAGS_M2M,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_NV12MT,
		.color		= FIMC_FMT_YCBCR420,
		.depth		= अणु 8, 4 पूर्ण,
		.memplanes	= 2,
		.colplanes	= 2,
		.flags		= FMT_FLAGS_M2M,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_JPEG,
		.color		= FIMC_FMT_JPEG,
		.depth		= अणु 8 पूर्ण,
		.memplanes	= 1,
		.colplanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_JPEG_1X8,
		.flags		= FMT_FLAGS_CAM | FMT_FLAGS_COMPRESSED,
	पूर्ण, अणु
		.fourcc		= V4L2_PIX_FMT_S5C_UYVY_JPG,
		.color		= FIMC_FMT_YUYV_JPEG,
		.depth		= अणु 8 पूर्ण,
		.memplanes	= 2,
		.colplanes	= 1,
		.mdataplanes	= 0x2, /* plane 1 holds frame meta data */
		.mbus_code	= MEDIA_BUS_FMT_S5C_UYVY_JPEG_1X8,
		.flags		= FMT_FLAGS_CAM | FMT_FLAGS_COMPRESSED,
	पूर्ण,
पूर्ण;

काष्ठा fimc_fmt *fimc_get_क्रमmat(अचिन्हित पूर्णांक index)
अणु
	अगर (index >= ARRAY_SIZE(fimc_क्रमmats))
		वापस शून्य;

	वापस &fimc_क्रमmats[index];
पूर्ण

पूर्णांक fimc_check_scaler_ratio(काष्ठा fimc_ctx *ctx, पूर्णांक sw, पूर्णांक sh,
			    पूर्णांक dw, पूर्णांक dh, पूर्णांक rotation)
अणु
	अगर (rotation == 90 || rotation == 270)
		swap(dw, dh);

	अगर (!ctx->scaler.enabled)
		वापस (sw == dw && sh == dh) ? 0 : -EINVAL;

	अगर ((sw >= SCALER_MAX_HRATIO * dw) || (sh >= SCALER_MAX_VRATIO * dh))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक fimc_get_scaler_factor(u32 src, u32 tar, u32 *ratio, u32 *shअगरt)
अणु
	u32 sh = 6;

	अगर (src >= 64 * tar)
		वापस -EINVAL;

	जबतक (sh--) अणु
		u32 पंचांगp = 1 << sh;
		अगर (src >= tar * पंचांगp) अणु
			*shअगरt = sh;
			*ratio = पंचांगp;
			वापस 0;
		पूर्ण
	पूर्ण
	*shअगरt = 0;
	*ratio = 1;
	वापस 0;
पूर्ण

पूर्णांक fimc_set_scaler_info(काष्ठा fimc_ctx *ctx)
अणु
	स्थिर काष्ठा fimc_variant *variant = ctx->fimc_dev->variant;
	काष्ठा device *dev = &ctx->fimc_dev->pdev->dev;
	काष्ठा fimc_scaler *sc = &ctx->scaler;
	काष्ठा fimc_frame *s_frame = &ctx->s_frame;
	काष्ठा fimc_frame *d_frame = &ctx->d_frame;
	पूर्णांक tx, ty, sx, sy;
	पूर्णांक ret;

	अगर (ctx->rotation == 90 || ctx->rotation == 270) अणु
		ty = d_frame->width;
		tx = d_frame->height;
	पूर्ण अन्यथा अणु
		tx = d_frame->width;
		ty = d_frame->height;
	पूर्ण
	अगर (tx <= 0 || ty <= 0) अणु
		dev_err(dev, "Invalid target size: %dx%d\n", tx, ty);
		वापस -EINVAL;
	पूर्ण

	sx = s_frame->width;
	sy = s_frame->height;
	अगर (sx <= 0 || sy <= 0) अणु
		dev_err(dev, "Invalid source size: %dx%d\n", sx, sy);
		वापस -EINVAL;
	पूर्ण
	sc->real_width = sx;
	sc->real_height = sy;

	ret = fimc_get_scaler_factor(sx, tx, &sc->pre_hratio, &sc->hfactor);
	अगर (ret)
		वापस ret;

	ret = fimc_get_scaler_factor(sy, ty,  &sc->pre_vratio, &sc->vfactor);
	अगर (ret)
		वापस ret;

	sc->pre_dst_width = sx / sc->pre_hratio;
	sc->pre_dst_height = sy / sc->pre_vratio;

	अगर (variant->has_मुख्यscaler_ext) अणु
		sc->मुख्य_hratio = (sx << 14) / (tx << sc->hfactor);
		sc->मुख्य_vratio = (sy << 14) / (ty << sc->vfactor);
	पूर्ण अन्यथा अणु
		sc->मुख्य_hratio = (sx << 8) / (tx << sc->hfactor);
		sc->मुख्य_vratio = (sy << 8) / (ty << sc->vfactor);

	पूर्ण

	sc->scaleup_h = (tx >= sx) ? 1 : 0;
	sc->scaleup_v = (ty >= sy) ? 1 : 0;

	/* check to see अगर input and output size/क्रमmat dअगरfer */
	अगर (s_frame->fmt->color == d_frame->fmt->color
		&& s_frame->width == d_frame->width
		&& s_frame->height == d_frame->height)
		sc->copy_mode = 1;
	अन्यथा
		sc->copy_mode = 0;

	वापस 0;
पूर्ण

अटल irqवापस_t fimc_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा fimc_dev *fimc = priv;
	काष्ठा fimc_ctx *ctx;

	fimc_hw_clear_irq(fimc);

	spin_lock(&fimc->slock);

	अगर (test_and_clear_bit(ST_M2M_PEND, &fimc->state)) अणु
		अगर (test_and_clear_bit(ST_M2M_SUSPENDING, &fimc->state)) अणु
			set_bit(ST_M2M_SUSPENDED, &fimc->state);
			wake_up(&fimc->irq_queue);
			जाओ out;
		पूर्ण
		ctx = v4l2_m2m_get_curr_priv(fimc->m2m.m2m_dev);
		अगर (ctx != शून्य) अणु
			spin_unlock(&fimc->slock);
			fimc_m2m_job_finish(ctx, VB2_BUF_STATE_DONE);

			अगर (ctx->state & FIMC_CTX_SHUT) अणु
				ctx->state &= ~FIMC_CTX_SHUT;
				wake_up(&fimc->irq_queue);
			पूर्ण
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण अन्यथा अगर (test_bit(ST_CAPT_PEND, &fimc->state)) अणु
		पूर्णांक last_buf = test_bit(ST_CAPT_JPEG, &fimc->state) &&
				fimc->vid_cap.reqbufs_count == 1;
		fimc_capture_irq_handler(fimc, !last_buf);
	पूर्ण
out:
	spin_unlock(&fimc->slock);
	वापस IRQ_HANDLED;
पूर्ण

/* The color क्रमmat (colplanes, memplanes) must be alपढ़ोy configured. */
पूर्णांक fimc_prepare_addr(काष्ठा fimc_ctx *ctx, काष्ठा vb2_buffer *vb,
		      काष्ठा fimc_frame *frame, काष्ठा fimc_addr *addr)
अणु
	पूर्णांक ret = 0;
	u32 pix_size;

	अगर (vb == शून्य || frame == शून्य)
		वापस -EINVAL;

	pix_size = frame->width * frame->height;

	dbg("memplanes= %d, colplanes= %d, pix_size= %d",
		frame->fmt->memplanes, frame->fmt->colplanes, pix_size);

	addr->y = vb2_dma_contig_plane_dma_addr(vb, 0);

	अगर (frame->fmt->memplanes == 1) अणु
		चयन (frame->fmt->colplanes) अणु
		हाल 1:
			addr->cb = 0;
			addr->cr = 0;
			अवरोध;
		हाल 2:
			/* decompose Y पूर्णांकo Y/Cb */
			addr->cb = (u32)(addr->y + pix_size);
			addr->cr = 0;
			अवरोध;
		हाल 3:
			addr->cb = (u32)(addr->y + pix_size);
			/* decompose Y पूर्णांकo Y/Cb/Cr */
			अगर (FIMC_FMT_YCBCR420 == frame->fmt->color)
				addr->cr = (u32)(addr->cb + (pix_size >> 2));
			अन्यथा /* 422 */
				addr->cr = (u32)(addr->cb + (pix_size >> 1));
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (!frame->fmt->mdataplanes) अणु
		अगर (frame->fmt->memplanes >= 2)
			addr->cb = vb2_dma_contig_plane_dma_addr(vb, 1);

		अगर (frame->fmt->memplanes == 3)
			addr->cr = vb2_dma_contig_plane_dma_addr(vb, 2);
	पूर्ण

	dbg("DMA ADDR: y= 0x%X  cb= 0x%X cr= 0x%X ret= %d",
	    addr->y, addr->cb, addr->cr, ret);

	वापस ret;
पूर्ण

/* Set order क्रम 1 and 2 plane YCBCR 4:2:2 क्रमmats. */
व्योम fimc_set_yuv_order(काष्ठा fimc_ctx *ctx)
अणु
	/* The one only mode supported in SoC. */
	ctx->in_order_2p = FIMC_REG_CIOCTRL_ORDER422_2P_LSB_CRCB;
	ctx->out_order_2p = FIMC_REG_CIOCTRL_ORDER422_2P_LSB_CRCB;

	/* Set order क्रम 1 plane input क्रमmats. */
	चयन (ctx->s_frame.fmt->color) अणु
	हाल FIMC_FMT_YCRYCB422:
		ctx->in_order_1p = FIMC_REG_MSCTRL_ORDER422_YCRYCB;
		अवरोध;
	हाल FIMC_FMT_CBYCRY422:
		ctx->in_order_1p = FIMC_REG_MSCTRL_ORDER422_CBYCRY;
		अवरोध;
	हाल FIMC_FMT_CRYCBY422:
		ctx->in_order_1p = FIMC_REG_MSCTRL_ORDER422_CRYCBY;
		अवरोध;
	हाल FIMC_FMT_YCBYCR422:
	शेष:
		ctx->in_order_1p = FIMC_REG_MSCTRL_ORDER422_YCBYCR;
		अवरोध;
	पूर्ण
	dbg("ctx->in_order_1p= %d", ctx->in_order_1p);

	चयन (ctx->d_frame.fmt->color) अणु
	हाल FIMC_FMT_YCRYCB422:
		ctx->out_order_1p = FIMC_REG_CIOCTRL_ORDER422_YCRYCB;
		अवरोध;
	हाल FIMC_FMT_CBYCRY422:
		ctx->out_order_1p = FIMC_REG_CIOCTRL_ORDER422_CBYCRY;
		अवरोध;
	हाल FIMC_FMT_CRYCBY422:
		ctx->out_order_1p = FIMC_REG_CIOCTRL_ORDER422_CRYCBY;
		अवरोध;
	हाल FIMC_FMT_YCBYCR422:
	शेष:
		ctx->out_order_1p = FIMC_REG_CIOCTRL_ORDER422_YCBYCR;
		अवरोध;
	पूर्ण
	dbg("ctx->out_order_1p= %d", ctx->out_order_1p);
पूर्ण

व्योम fimc_prepare_dma_offset(काष्ठा fimc_ctx *ctx, काष्ठा fimc_frame *f)
अणु
	bool pix_hoff = ctx->fimc_dev->drv_data->dma_pix_hoff;
	u32 i, depth = 0;

	क्रम (i = 0; i < f->fmt->memplanes; i++)
		depth += f->fmt->depth[i];

	f->dma_offset.y_h = f->offs_h;
	अगर (!pix_hoff)
		f->dma_offset.y_h *= (depth >> 3);

	f->dma_offset.y_v = f->offs_v;

	f->dma_offset.cb_h = f->offs_h;
	f->dma_offset.cb_v = f->offs_v;

	f->dma_offset.cr_h = f->offs_h;
	f->dma_offset.cr_v = f->offs_v;

	अगर (!pix_hoff) अणु
		अगर (f->fmt->colplanes == 3) अणु
			f->dma_offset.cb_h >>= 1;
			f->dma_offset.cr_h >>= 1;
		पूर्ण
		अगर (f->fmt->color == FIMC_FMT_YCBCR420) अणु
			f->dma_offset.cb_v >>= 1;
			f->dma_offset.cr_v >>= 1;
		पूर्ण
	पूर्ण

	dbg("in_offset: color= %d, y_h= %d, y_v= %d",
	    f->fmt->color, f->dma_offset.y_h, f->dma_offset.y_v);
पूर्ण

अटल पूर्णांक fimc_set_color_effect(काष्ठा fimc_ctx *ctx, क्रमागत v4l2_colorfx colorfx)
अणु
	काष्ठा fimc_effect *effect = &ctx->effect;

	चयन (colorfx) अणु
	हाल V4L2_COLORFX_NONE:
		effect->type = FIMC_REG_CIIMGEFF_FIN_BYPASS;
		अवरोध;
	हाल V4L2_COLORFX_BW:
		effect->type = FIMC_REG_CIIMGEFF_FIN_ARBITRARY;
		effect->pat_cb = 128;
		effect->pat_cr = 128;
		अवरोध;
	हाल V4L2_COLORFX_SEPIA:
		effect->type = FIMC_REG_CIIMGEFF_FIN_ARBITRARY;
		effect->pat_cb = 115;
		effect->pat_cr = 145;
		अवरोध;
	हाल V4L2_COLORFX_NEGATIVE:
		effect->type = FIMC_REG_CIIMGEFF_FIN_NEGATIVE;
		अवरोध;
	हाल V4L2_COLORFX_EMBOSS:
		effect->type = FIMC_REG_CIIMGEFF_FIN_EMBOSSING;
		अवरोध;
	हाल V4L2_COLORFX_ART_FREEZE:
		effect->type = FIMC_REG_CIIMGEFF_FIN_ARTFREEZE;
		अवरोध;
	हाल V4L2_COLORFX_SILHOUETTE:
		effect->type = FIMC_REG_CIIMGEFF_FIN_SILHOUETTE;
		अवरोध;
	हाल V4L2_COLORFX_SET_CBCR:
		effect->type = FIMC_REG_CIIMGEFF_FIN_ARBITRARY;
		effect->pat_cb = ctx->ctrls.colorfx_cbcr->val >> 8;
		effect->pat_cr = ctx->ctrls.colorfx_cbcr->val & 0xff;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * V4L2 controls handling
 */
#घोषणा ctrl_to_ctx(__ctrl) \
	container_of((__ctrl)->handler, काष्ठा fimc_ctx, ctrls.handler)

अटल पूर्णांक __fimc_s_ctrl(काष्ठा fimc_ctx *ctx, काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;
	स्थिर काष्ठा fimc_variant *variant = fimc->variant;
	पूर्णांक ret = 0;

	अगर (ctrl->flags & V4L2_CTRL_FLAG_INACTIVE)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_HFLIP:
		ctx->hflip = ctrl->val;
		अवरोध;

	हाल V4L2_CID_VFLIP:
		ctx->vflip = ctrl->val;
		अवरोध;

	हाल V4L2_CID_ROTATE:
		अगर (fimc_capture_pending(fimc)) अणु
			ret = fimc_check_scaler_ratio(ctx, ctx->s_frame.width,
					ctx->s_frame.height, ctx->d_frame.width,
					ctx->d_frame.height, ctrl->val);
			अगर (ret)
				वापस -EINVAL;
		पूर्ण
		अगर ((ctrl->val == 90 || ctrl->val == 270) &&
		    !variant->has_out_rot)
			वापस -EINVAL;

		ctx->rotation = ctrl->val;
		अवरोध;

	हाल V4L2_CID_ALPHA_COMPONENT:
		ctx->d_frame.alpha = ctrl->val;
		अवरोध;

	हाल V4L2_CID_COLORFX:
		ret = fimc_set_color_effect(ctx, ctrl->val);
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण

	ctx->state |= FIMC_PARAMS;
	set_bit(ST_CAPT_APPLY_CFG, &fimc->state);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा fimc_ctx *ctx = ctrl_to_ctx(ctrl);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ctx->fimc_dev->slock, flags);
	ret = __fimc_s_ctrl(ctx, ctrl);
	spin_unlock_irqrestore(&ctx->fimc_dev->slock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops fimc_ctrl_ops = अणु
	.s_ctrl = fimc_s_ctrl,
पूर्ण;

पूर्णांक fimc_ctrls_create(काष्ठा fimc_ctx *ctx)
अणु
	अचिन्हित पूर्णांक max_alpha = fimc_get_alpha_mask(ctx->d_frame.fmt);
	काष्ठा fimc_ctrls *ctrls = &ctx->ctrls;
	काष्ठा v4l2_ctrl_handler *handler = &ctrls->handler;

	अगर (ctx->ctrls.पढ़ोy)
		वापस 0;

	v4l2_ctrl_handler_init(handler, 6);

	ctrls->rotate = v4l2_ctrl_new_std(handler, &fimc_ctrl_ops,
					V4L2_CID_ROTATE, 0, 270, 90, 0);
	ctrls->hflip = v4l2_ctrl_new_std(handler, &fimc_ctrl_ops,
					V4L2_CID_HFLIP, 0, 1, 1, 0);
	ctrls->vflip = v4l2_ctrl_new_std(handler, &fimc_ctrl_ops,
					V4L2_CID_VFLIP, 0, 1, 1, 0);

	अगर (ctx->fimc_dev->drv_data->alpha_color)
		ctrls->alpha = v4l2_ctrl_new_std(handler, &fimc_ctrl_ops,
					V4L2_CID_ALPHA_COMPONENT,
					0, max_alpha, 1, 0);
	अन्यथा
		ctrls->alpha = शून्य;

	ctrls->colorfx = v4l2_ctrl_new_std_menu(handler, &fimc_ctrl_ops,
				V4L2_CID_COLORFX, V4L2_COLORFX_SET_CBCR,
				~0x983f, V4L2_COLORFX_NONE);

	ctrls->colorfx_cbcr = v4l2_ctrl_new_std(handler, &fimc_ctrl_ops,
				V4L2_CID_COLORFX_CBCR, 0, 0xffff, 1, 0);

	ctx->effect.type = FIMC_REG_CIIMGEFF_FIN_BYPASS;

	अगर (!handler->error) अणु
		v4l2_ctrl_cluster(2, &ctrls->colorfx);
		ctrls->पढ़ोy = true;
	पूर्ण

	वापस handler->error;
पूर्ण

व्योम fimc_ctrls_delete(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_ctrls *ctrls = &ctx->ctrls;

	अगर (ctrls->पढ़ोy) अणु
		v4l2_ctrl_handler_मुक्त(&ctrls->handler);
		ctrls->पढ़ोy = false;
		ctrls->alpha = शून्य;
	पूर्ण
पूर्ण

व्योम fimc_ctrls_activate(काष्ठा fimc_ctx *ctx, bool active)
अणु
	अचिन्हित पूर्णांक has_alpha = ctx->d_frame.fmt->flags & FMT_HAS_ALPHA;
	काष्ठा fimc_ctrls *ctrls = &ctx->ctrls;

	अगर (!ctrls->पढ़ोy)
		वापस;

	mutex_lock(ctrls->handler.lock);
	v4l2_ctrl_activate(ctrls->rotate, active);
	v4l2_ctrl_activate(ctrls->hflip, active);
	v4l2_ctrl_activate(ctrls->vflip, active);
	v4l2_ctrl_activate(ctrls->colorfx, active);
	अगर (ctrls->alpha)
		v4l2_ctrl_activate(ctrls->alpha, active && has_alpha);

	अगर (active) अणु
		fimc_set_color_effect(ctx, ctrls->colorfx->cur.val);
		ctx->rotation = ctrls->rotate->val;
		ctx->hflip    = ctrls->hflip->val;
		ctx->vflip    = ctrls->vflip->val;
	पूर्ण अन्यथा अणु
		ctx->effect.type = FIMC_REG_CIIMGEFF_FIN_BYPASS;
		ctx->rotation = 0;
		ctx->hflip    = 0;
		ctx->vflip    = 0;
	पूर्ण
	mutex_unlock(ctrls->handler.lock);
पूर्ण

/* Update maximum value of the alpha color control */
व्योम fimc_alpha_ctrl_update(काष्ठा fimc_ctx *ctx)
अणु
	काष्ठा fimc_dev *fimc = ctx->fimc_dev;
	काष्ठा v4l2_ctrl *ctrl = ctx->ctrls.alpha;

	अगर (ctrl == शून्य || !fimc->drv_data->alpha_color)
		वापस;

	v4l2_ctrl_lock(ctrl);
	ctrl->maximum = fimc_get_alpha_mask(ctx->d_frame.fmt);

	अगर (ctrl->cur.val > ctrl->maximum)
		ctrl->cur.val = ctrl->maximum;

	v4l2_ctrl_unlock(ctrl);
पूर्ण

व्योम __fimc_get_क्रमmat(काष्ठा fimc_frame *frame, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pixm = &f->fmt.pix_mp;
	पूर्णांक i;

	pixm->width = frame->o_width;
	pixm->height = frame->o_height;
	pixm->field = V4L2_FIELD_NONE;
	pixm->pixelक्रमmat = frame->fmt->fourcc;
	pixm->colorspace = V4L2_COLORSPACE_JPEG;
	pixm->num_planes = frame->fmt->memplanes;

	क्रम (i = 0; i < pixm->num_planes; ++i) अणु
		pixm->plane_fmt[i].bytesperline = frame->bytesperline[i];
		pixm->plane_fmt[i].sizeimage = frame->payload[i];
	पूर्ण
पूर्ण

/**
 * fimc_adjust_mplane_क्रमmat - adjust bytesperline/sizeimage क्रम each plane
 * @fmt: fimc pixel क्रमmat description (input)
 * @width: requested pixel width
 * @height: requested pixel height
 * @pix: multi-plane क्रमmat to adjust
 */
व्योम fimc_adjust_mplane_क्रमmat(काष्ठा fimc_fmt *fmt, u32 width, u32 height,
			       काष्ठा v4l2_pix_क्रमmat_mplane *pix)
अणु
	u32 bytesperline = 0;
	पूर्णांक i;

	pix->colorspace	= V4L2_COLORSPACE_JPEG;
	pix->field = V4L2_FIELD_NONE;
	pix->num_planes = fmt->memplanes;
	pix->pixelक्रमmat = fmt->fourcc;
	pix->height = height;
	pix->width = width;

	क्रम (i = 0; i < pix->num_planes; ++i) अणु
		काष्ठा v4l2_plane_pix_क्रमmat *plane_fmt = &pix->plane_fmt[i];
		u32 bpl = plane_fmt->bytesperline;
		u32 sizeimage;

		अगर (fmt->colplanes > 1 && (bpl == 0 || bpl < pix->width))
			bpl = pix->width; /* Planar */

		अगर (fmt->colplanes == 1 && /* Packed */
		    (bpl == 0 || ((bpl * 8) / fmt->depth[i]) < pix->width))
			bpl = (pix->width * fmt->depth[0]) / 8;
		/*
		 * Currently bytesperline क्रम each plane is same, except
		 * V4L2_PIX_FMT_YUV420M क्रमmat. This calculation may need
		 * to be changed when other multi-planar क्रमmats are added
		 * to the fimc_क्रमmats[] array.
		 */
		अगर (i == 0)
			bytesperline = bpl;
		अन्यथा अगर (i == 1 && fmt->memplanes == 3)
			bytesperline /= 2;

		plane_fmt->bytesperline = bytesperline;
		sizeimage = pix->width * pix->height * fmt->depth[i] / 8;

		/* Ensure full last row क्रम tiled क्रमmats */
		अगर (tiled_fmt(fmt)) अणु
			/* 64 * 32 * plane_fmt->bytesperline / 64 */
			u32 row_size = plane_fmt->bytesperline * 32;

			sizeimage = roundup(sizeimage, row_size);
		पूर्ण

		plane_fmt->sizeimage = max(sizeimage, plane_fmt->sizeimage);
	पूर्ण
पूर्ण

/**
 * fimc_find_क्रमmat - lookup fimc color क्रमmat by fourcc or media bus क्रमmat
 * @pixelक्रमmat: fourcc to match, ignored अगर null
 * @mbus_code: media bus code to match, ignored अगर null
 * @mask: the color flags to match
 * @index: offset in the fimc_क्रमmats array, ignored अगर negative
 */
काष्ठा fimc_fmt *fimc_find_क्रमmat(स्थिर u32 *pixelक्रमmat, स्थिर u32 *mbus_code,
				  अचिन्हित पूर्णांक mask, पूर्णांक index)
अणु
	काष्ठा fimc_fmt *fmt, *def_fmt = शून्य;
	अचिन्हित पूर्णांक i;
	पूर्णांक id = 0;

	अगर (index >= (पूर्णांक)ARRAY_SIZE(fimc_क्रमmats))
		वापस शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(fimc_क्रमmats); ++i) अणु
		fmt = &fimc_क्रमmats[i];
		अगर (!(fmt->flags & mask))
			जारी;
		अगर (pixelक्रमmat && fmt->fourcc == *pixelक्रमmat)
			वापस fmt;
		अगर (mbus_code && fmt->mbus_code == *mbus_code)
			वापस fmt;
		अगर (index == id)
			def_fmt = fmt;
		id++;
	पूर्ण
	वापस def_fmt;
पूर्ण

अटल व्योम fimc_clk_put(काष्ठा fimc_dev *fimc)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < MAX_FIMC_CLOCKS; i++) अणु
		अगर (IS_ERR(fimc->घड़ी[i]))
			जारी;
		clk_unprepare(fimc->घड़ी[i]);
		clk_put(fimc->घड़ी[i]);
		fimc->घड़ी[i] = ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण

अटल पूर्णांक fimc_clk_get(काष्ठा fimc_dev *fimc)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < MAX_FIMC_CLOCKS; i++)
		fimc->घड़ी[i] = ERR_PTR(-EINVAL);

	क्रम (i = 0; i < MAX_FIMC_CLOCKS; i++) अणु
		fimc->घड़ी[i] = clk_get(&fimc->pdev->dev, fimc_घड़ीs[i]);
		अगर (IS_ERR(fimc->घड़ी[i])) अणु
			ret = PTR_ERR(fimc->घड़ी[i]);
			जाओ err;
		पूर्ण
		ret = clk_prepare(fimc->घड़ी[i]);
		अगर (ret < 0) अणु
			clk_put(fimc->घड़ी[i]);
			fimc->घड़ी[i] = ERR_PTR(-EINVAL);
			जाओ err;
		पूर्ण
	पूर्ण
	वापस 0;
err:
	fimc_clk_put(fimc);
	dev_err(&fimc->pdev->dev, "failed to get clock: %s\n",
		fimc_घड़ीs[i]);
	वापस -ENXIO;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक fimc_m2m_suspend(काष्ठा fimc_dev *fimc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक समयout;

	spin_lock_irqsave(&fimc->slock, flags);
	अगर (!fimc_m2m_pending(fimc)) अणु
		spin_unlock_irqrestore(&fimc->slock, flags);
		वापस 0;
	पूर्ण
	clear_bit(ST_M2M_SUSPENDED, &fimc->state);
	set_bit(ST_M2M_SUSPENDING, &fimc->state);
	spin_unlock_irqrestore(&fimc->slock, flags);

	समयout = रुको_event_समयout(fimc->irq_queue,
			     test_bit(ST_M2M_SUSPENDED, &fimc->state),
			     FIMC_SHUTDOWN_TIMEOUT);

	clear_bit(ST_M2M_SUSPENDING, &fimc->state);
	वापस समयout == 0 ? -EAGAIN : 0;
पूर्ण

अटल पूर्णांक fimc_m2m_resume(काष्ठा fimc_dev *fimc)
अणु
	काष्ठा fimc_ctx *ctx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fimc->slock, flags);
	/* Clear क्रम full H/W setup in first run after resume */
	ctx = fimc->m2m.ctx;
	fimc->m2m.ctx = शून्य;
	spin_unlock_irqrestore(&fimc->slock, flags);

	अगर (test_and_clear_bit(ST_M2M_SUSPENDED, &fimc->state))
		fimc_m2m_job_finish(ctx, VB2_BUF_STATE_ERROR);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा of_device_id fimc_of_match[];

अटल पूर्णांक fimc_parse_dt(काष्ठा fimc_dev *fimc, u32 *clk_freq)
अणु
	काष्ठा device *dev = &fimc->pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा fimc_variant *v;
	काष्ठा fimc_pix_limit *lim;
	u32 args[FIMC_PIX_LIMITS_MAX];
	पूर्णांक ret;

	अगर (of_property_पढ़ो_bool(node, "samsung,lcd-wb"))
		वापस -ENODEV;

	v = devm_kzalloc(dev, माप(*v) + माप(*lim), GFP_KERNEL);
	अगर (!v)
		वापस -ENOMEM;

	of_id = of_match_node(fimc_of_match, node);
	अगर (!of_id)
		वापस -EINVAL;
	fimc->drv_data = of_id->data;
	ret = of_property_पढ़ो_u32_array(node, "samsung,pix-limits",
					 args, FIMC_PIX_LIMITS_MAX);
	अगर (ret < 0)
		वापस ret;

	lim = (काष्ठा fimc_pix_limit *)&v[1];

	lim->scaler_en_w = args[0];
	lim->scaler_dis_w = args[1];
	lim->out_rot_en_w = args[2];
	lim->out_rot_dis_w = args[3];
	v->pix_limit = lim;

	ret = of_property_पढ़ो_u32_array(node, "samsung,min-pix-sizes",
								args, 2);
	v->min_inp_pixsize = ret ? FIMC_DEF_MIN_SIZE : args[0];
	v->min_out_pixsize = ret ? FIMC_DEF_MIN_SIZE : args[1];
	ret = of_property_पढ़ो_u32_array(node, "samsung,min-pix-alignment",
								args, 2);
	v->min_vsize_align = ret ? FIMC_DEF_HEIGHT_ALIGN : args[0];
	v->hor_offs_align = ret ? FIMC_DEF_HOR_OFFS_ALIGN : args[1];

	ret = of_property_पढ़ो_u32(node, "samsung,rotators", &args[1]);
	v->has_inp_rot = ret ? 1 : args[1] & 0x01;
	v->has_out_rot = ret ? 1 : args[1] & 0x10;
	v->has_मुख्यscaler_ext = of_property_पढ़ो_bool(node,
					"samsung,mainscaler-ext");

	v->has_isp_wb = of_property_पढ़ो_bool(node, "samsung,isp-wb");
	v->has_cam_अगर = of_property_पढ़ो_bool(node, "samsung,cam-if");
	of_property_पढ़ो_u32(node, "clock-frequency", clk_freq);
	fimc->id = of_alias_get_id(node, "fimc");

	fimc->variant = v;
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	u32 lclk_freq = 0;
	काष्ठा fimc_dev *fimc;
	काष्ठा resource *res;
	पूर्णांक ret = 0;

	fimc = devm_kzalloc(dev, माप(*fimc), GFP_KERNEL);
	अगर (!fimc)
		वापस -ENOMEM;

	fimc->pdev = pdev;

	अगर (dev->of_node) अणु
		ret = fimc_parse_dt(fimc, &lclk_freq);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		fimc->drv_data = fimc_get_drvdata(pdev);
		fimc->id = pdev->id;
	पूर्ण
	अगर (!fimc->drv_data || fimc->id >= fimc->drv_data->num_entities ||
	    fimc->id < 0) अणु
		dev_err(dev, "Invalid driver data or device id (%d)\n",
			fimc->id);
		वापस -EINVAL;
	पूर्ण
	अगर (!dev->of_node)
		fimc->variant = fimc->drv_data->variant[fimc->id];

	init_रुकोqueue_head(&fimc->irq_queue);
	spin_lock_init(&fimc->slock);
	mutex_init(&fimc->lock);

	अगर (fimc->variant->has_isp_wb) अणु
		fimc->sysreg = fimc_get_sysreg_regmap(dev->of_node);
		अगर (IS_ERR(fimc->sysreg))
			वापस PTR_ERR(fimc->sysreg);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	fimc->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(fimc->regs))
		वापस PTR_ERR(fimc->regs);

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (res == शून्य) अणु
		dev_err(dev, "Failed to get IRQ resource\n");
		वापस -ENXIO;
	पूर्ण

	ret = fimc_clk_get(fimc);
	अगर (ret)
		वापस ret;

	अगर (lclk_freq == 0)
		lclk_freq = fimc->drv_data->lclk_frequency;

	ret = clk_set_rate(fimc->घड़ी[CLK_BUS], lclk_freq);
	अगर (ret < 0)
		वापस ret;

	ret = clk_enable(fimc->घड़ी[CLK_BUS]);
	अगर (ret < 0)
		वापस ret;

	ret = devm_request_irq(dev, res->start, fimc_irq_handler,
			       0, dev_name(dev), fimc);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to install irq (%d)\n", ret);
		जाओ err_sclk;
	पूर्ण

	ret = fimc_initialize_capture_subdev(fimc);
	अगर (ret < 0)
		जाओ err_sclk;

	platक्रमm_set_drvdata(pdev, fimc);
	pm_runसमय_enable(dev);

	अगर (!pm_runसमय_enabled(dev)) अणु
		ret = clk_enable(fimc->घड़ी[CLK_GATE]);
		अगर (ret < 0)
			जाओ err_sd;
	पूर्ण

	vb2_dma_contig_set_max_seg_size(dev, DMA_BIT_MASK(32));

	dev_dbg(dev, "FIMC.%d registered successfully\n", fimc->id);
	वापस 0;

err_sd:
	fimc_unरेजिस्टर_capture_subdev(fimc);
err_sclk:
	clk_disable(fimc->घड़ी[CLK_BUS]);
	fimc_clk_put(fimc);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक fimc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fimc_dev *fimc =	dev_get_drvdata(dev);

	dbg("fimc%d: state: 0x%lx", fimc->id, fimc->state);

	/* Enable घड़ीs and perक्रमm basic initialization */
	clk_enable(fimc->घड़ी[CLK_GATE]);
	fimc_hw_reset(fimc);

	/* Resume the capture or mem-to-mem device */
	अगर (fimc_capture_busy(fimc))
		वापस fimc_capture_resume(fimc);

	वापस fimc_m2m_resume(fimc);
पूर्ण

अटल पूर्णांक fimc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fimc_dev *fimc =	dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (fimc_capture_busy(fimc))
		ret = fimc_capture_suspend(fimc);
	अन्यथा
		ret = fimc_m2m_suspend(fimc);
	अगर (!ret)
		clk_disable(fimc->घड़ी[CLK_GATE]);

	dbg("fimc%d: state: 0x%lx", fimc->id, fimc->state);
	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक fimc_resume(काष्ठा device *dev)
अणु
	काष्ठा fimc_dev *fimc =	dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	dbg("fimc%d: state: 0x%lx", fimc->id, fimc->state);

	/* Do not resume अगर the device was idle beक्रमe प्रणाली suspend */
	spin_lock_irqsave(&fimc->slock, flags);
	अगर (!test_and_clear_bit(ST_LPM, &fimc->state) ||
	    (!fimc_m2m_active(fimc) && !fimc_capture_busy(fimc))) अणु
		spin_unlock_irqrestore(&fimc->slock, flags);
		वापस 0;
	पूर्ण
	fimc_hw_reset(fimc);
	spin_unlock_irqrestore(&fimc->slock, flags);

	अगर (fimc_capture_busy(fimc))
		वापस fimc_capture_resume(fimc);

	वापस fimc_m2m_resume(fimc);
पूर्ण

अटल पूर्णांक fimc_suspend(काष्ठा device *dev)
अणु
	काष्ठा fimc_dev *fimc =	dev_get_drvdata(dev);

	dbg("fimc%d: state: 0x%lx", fimc->id, fimc->state);

	अगर (test_and_set_bit(ST_LPM, &fimc->state))
		वापस 0;
	अगर (fimc_capture_busy(fimc))
		वापस fimc_capture_suspend(fimc);

	वापस fimc_m2m_suspend(fimc);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक fimc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fimc_dev *fimc = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		clk_disable(fimc->घड़ी[CLK_GATE]);
	pm_runसमय_set_suspended(&pdev->dev);

	fimc_unरेजिस्टर_capture_subdev(fimc);
	vb2_dma_contig_clear_max_seg_size(&pdev->dev);

	clk_disable(fimc->घड़ी[CLK_BUS]);
	fimc_clk_put(fimc);

	dev_info(&pdev->dev, "driver unloaded\n");
	वापस 0;
पूर्ण

/* S5PV210, S5PC110 */
अटल स्थिर काष्ठा fimc_drvdata fimc_drvdata_s5pv210 = अणु
	.num_entities	= 3,
	.lclk_frequency	= 166000000UL,
	.out_buf_count	= 4,
	.dma_pix_hoff	= 1,
पूर्ण;

/* EXYNOS4210, S5PV310, S5PC210 */
अटल स्थिर काष्ठा fimc_drvdata fimc_drvdata_exynos4210 = अणु
	.num_entities	= 4,
	.lclk_frequency = 166000000UL,
	.dma_pix_hoff	= 1,
	.cistatus2	= 1,
	.alpha_color	= 1,
	.out_buf_count	= 32,
पूर्ण;

/* EXYNOS4412 */
अटल स्थिर काष्ठा fimc_drvdata fimc_drvdata_exynos4x12 = अणु
	.num_entities	= 4,
	.lclk_frequency	= 166000000UL,
	.dma_pix_hoff	= 1,
	.cistatus2	= 1,
	.alpha_color	= 1,
	.out_buf_count	= 32,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fimc_of_match[] = अणु
	अणु
		.compatible = "samsung,s5pv210-fimc",
		.data = &fimc_drvdata_s5pv210,
	पूर्ण, अणु
		.compatible = "samsung,exynos4210-fimc",
		.data = &fimc_drvdata_exynos4210,
	पूर्ण, अणु
		.compatible = "samsung,exynos4212-fimc",
		.data = &fimc_drvdata_exynos4x12,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops fimc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(fimc_suspend, fimc_resume)
	SET_RUNTIME_PM_OPS(fimc_runसमय_suspend, fimc_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver fimc_driver = अणु
	.probe		= fimc_probe,
	.हटाओ		= fimc_हटाओ,
	.driver = अणु
		.of_match_table = fimc_of_match,
		.name		= FIMC_DRIVER_NAME,
		.pm		= &fimc_pm_ops,
	पूर्ण
पूर्ण;

पूर्णांक __init fimc_रेजिस्टर_driver(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&fimc_driver);
पूर्ण

व्योम __निकास fimc_unरेजिस्टर_driver(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&fimc_driver);
पूर्ण
