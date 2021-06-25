<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015-2016 MediaTek Inc.
 * Author: Houदीर्घ Wei <houदीर्घ.wei@mediatek.com>
 *         Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश "mtk_mdp_core.h"
#समावेश "mtk_mdp_m2m.h"
#समावेश "mtk_mdp_regs.h"
#समावेश "mtk_vpu.h"


/**
 *  काष्ठा mtk_mdp_pix_limit - image pixel size limits
 *  @org_w: source pixel width
 *  @org_h: source pixel height
 *  @target_rot_dis_w: pixel dst scaled width with the rotator is off
 *  @target_rot_dis_h: pixel dst scaled height with the rotator is off
 *  @target_rot_en_w: pixel dst scaled width with the rotator is on
 *  @target_rot_en_h: pixel dst scaled height with the rotator is on
 */
काष्ठा mtk_mdp_pix_limit अणु
	u16 org_w;
	u16 org_h;
	u16 target_rot_dis_w;
	u16 target_rot_dis_h;
	u16 target_rot_en_w;
	u16 target_rot_en_h;
पूर्ण;

अटल काष्ठा mtk_mdp_pix_align mtk_mdp_size_align = अणु
	.org_w			= 16,
	.org_h			= 16,
	.target_w		= 2,
	.target_h		= 2,
पूर्ण;

अटल स्थिर काष्ठा mtk_mdp_fmt mtk_mdp_क्रमmats[] = अणु
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_MT21C,
		.depth		= अणु 8, 4 पूर्ण,
		.row_depth	= अणु 8, 8 पूर्ण,
		.num_planes	= 2,
		.num_comp	= 2,
		.align		= &mtk_mdp_size_align,
		.flags		= MTK_MDP_FMT_FLAG_OUTPUT,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_NV12M,
		.depth		= अणु 8, 4 पूर्ण,
		.row_depth	= अणु 8, 8 पूर्ण,
		.num_planes	= 2,
		.num_comp	= 2,
		.flags		= MTK_MDP_FMT_FLAG_OUTPUT |
				  MTK_MDP_FMT_FLAG_CAPTURE,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YUV420M,
		.depth		= अणु 8, 2, 2 पूर्ण,
		.row_depth	= अणु 8, 4, 4 पूर्ण,
		.num_planes	= 3,
		.num_comp	= 3,
		.flags		= MTK_MDP_FMT_FLAG_OUTPUT |
				  MTK_MDP_FMT_FLAG_CAPTURE,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YVU420,
		.depth		= अणु 12 पूर्ण,
		.row_depth	= अणु 8 पूर्ण,
		.num_planes	= 1,
		.num_comp	= 3,
		.flags		= MTK_MDP_FMT_FLAG_OUTPUT |
				  MTK_MDP_FMT_FLAG_CAPTURE,
	पूर्ण
पूर्ण;

अटल काष्ठा mtk_mdp_pix_limit mtk_mdp_size_max = अणु
	.target_rot_dis_w	= 4096,
	.target_rot_dis_h	= 4096,
	.target_rot_en_w	= 4096,
	.target_rot_en_h	= 4096,
पूर्ण;

अटल काष्ठा mtk_mdp_pix_limit mtk_mdp_size_min = अणु
	.org_w			= 16,
	.org_h			= 16,
	.target_rot_dis_w	= 16,
	.target_rot_dis_h	= 16,
	.target_rot_en_w	= 16,
	.target_rot_en_h	= 16,
पूर्ण;

/* align size क्रम normal raster scan pixel क्रमmat */
अटल काष्ठा mtk_mdp_pix_align mtk_mdp_rs_align = अणु
	.org_w			= 2,
	.org_h			= 2,
	.target_w		= 2,
	.target_h		= 2,
पूर्ण;

अटल काष्ठा mtk_mdp_variant mtk_mdp_शेष_variant = अणु
	.pix_max		= &mtk_mdp_size_max,
	.pix_min		= &mtk_mdp_size_min,
	.pix_align		= &mtk_mdp_rs_align,
	.h_scale_up_max		= 32,
	.v_scale_up_max		= 32,
	.h_scale_करोwn_max	= 32,
	.v_scale_करोwn_max	= 128,
पूर्ण;

अटल स्थिर काष्ठा mtk_mdp_fmt *mtk_mdp_find_fmt(u32 pixelक्रमmat, u32 type)
अणु
	u32 i, flag;

	flag = V4L2_TYPE_IS_OUTPUT(type) ? MTK_MDP_FMT_FLAG_OUTPUT :
					   MTK_MDP_FMT_FLAG_CAPTURE;

	क्रम (i = 0; i < ARRAY_SIZE(mtk_mdp_क्रमmats); ++i) अणु
		अगर (!(mtk_mdp_क्रमmats[i].flags & flag))
			जारी;
		अगर (mtk_mdp_क्रमmats[i].pixelक्रमmat == pixelक्रमmat)
			वापस &mtk_mdp_क्रमmats[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा mtk_mdp_fmt *mtk_mdp_find_fmt_by_index(u32 index, u32 type)
अणु
	u32 i, flag, num = 0;

	flag = V4L2_TYPE_IS_OUTPUT(type) ? MTK_MDP_FMT_FLAG_OUTPUT :
					   MTK_MDP_FMT_FLAG_CAPTURE;

	क्रम (i = 0; i < ARRAY_SIZE(mtk_mdp_क्रमmats); ++i) अणु
		अगर (!(mtk_mdp_क्रमmats[i].flags & flag))
			जारी;
		अगर (index == num)
			वापस &mtk_mdp_क्रमmats[i];
		num++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम mtk_mdp_bound_align_image(u32 *w, अचिन्हित पूर्णांक wmin,
				      अचिन्हित पूर्णांक wmax, अचिन्हित पूर्णांक align_w,
				      u32 *h, अचिन्हित पूर्णांक hmin,
				      अचिन्हित पूर्णांक hmax, अचिन्हित पूर्णांक align_h)
अणु
	पूर्णांक org_w, org_h, step_w, step_h;
	पूर्णांक walign, halign;

	org_w = *w;
	org_h = *h;
	walign = ffs(align_w) - 1;
	halign = ffs(align_h) - 1;
	v4l_bound_align_image(w, wmin, wmax, walign, h, hmin, hmax, halign, 0);

	step_w = 1 << walign;
	step_h = 1 << halign;
	अगर (*w < org_w && (*w + step_w) <= wmax)
		*w += step_w;
	अगर (*h < org_h && (*h + step_h) <= hmax)
		*h += step_h;
पूर्ण

अटल स्थिर काष्ठा mtk_mdp_fmt *mtk_mdp_try_fmt_mplane(काष्ठा mtk_mdp_ctx *ctx,
							काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mtk_mdp_dev *mdp = ctx->mdp_dev;
	काष्ठा mtk_mdp_variant *variant = mdp->variant;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp = &f->fmt.pix_mp;
	स्थिर काष्ठा mtk_mdp_fmt *fmt;
	u32 max_w, max_h, align_w, align_h;
	u32 min_w, min_h, org_w, org_h;
	पूर्णांक i;

	fmt = mtk_mdp_find_fmt(pix_mp->pixelक्रमmat, f->type);
	अगर (!fmt)
		fmt = mtk_mdp_find_fmt_by_index(0, f->type);
	अगर (!fmt) अणु
		dev_dbg(&ctx->mdp_dev->pdev->dev,
			"pixelformat format 0x%X invalid\n",
			pix_mp->pixelक्रमmat);
		वापस शून्य;
	पूर्ण

	pix_mp->field = V4L2_FIELD_NONE;
	pix_mp->pixelक्रमmat = fmt->pixelक्रमmat;
	अगर (V4L2_TYPE_IS_CAPTURE(f->type)) अणु
		pix_mp->colorspace = ctx->colorspace;
		pix_mp->xfer_func = ctx->xfer_func;
		pix_mp->ycbcr_enc = ctx->ycbcr_enc;
		pix_mp->quantization = ctx->quant;
	पूर्ण

	max_w = variant->pix_max->target_rot_dis_w;
	max_h = variant->pix_max->target_rot_dis_h;

	अगर (fmt->align == शून्य) अणु
		/* use शेष alignment */
		align_w = variant->pix_align->org_w;
		align_h = variant->pix_align->org_h;
	पूर्ण अन्यथा अणु
		align_w = fmt->align->org_w;
		align_h = fmt->align->org_h;
	पूर्ण

	अगर (V4L2_TYPE_IS_OUTPUT(f->type)) अणु
		min_w = variant->pix_min->org_w;
		min_h = variant->pix_min->org_h;
	पूर्ण अन्यथा अणु
		min_w = variant->pix_min->target_rot_dis_w;
		min_h = variant->pix_min->target_rot_dis_h;
	पूर्ण

	mtk_mdp_dbg(2, "[%d] type:%d, wxh:%ux%u, align:%ux%u, max:%ux%u",
		    ctx->id, f->type, pix_mp->width, pix_mp->height,
		    align_w, align_h, max_w, max_h);
	/*
	 * To check अगर image size is modअगरied to adjust parameter against
	 * hardware abilities
	 */
	org_w = pix_mp->width;
	org_h = pix_mp->height;

	mtk_mdp_bound_align_image(&pix_mp->width, min_w, max_w, align_w,
				  &pix_mp->height, min_h, max_h, align_h);

	अगर (org_w != pix_mp->width || org_h != pix_mp->height)
		mtk_mdp_dbg(1, "[%d] size change:%ux%u to %ux%u", ctx->id,
			    org_w, org_h, pix_mp->width, pix_mp->height);
	pix_mp->num_planes = fmt->num_planes;

	क्रम (i = 0; i < pix_mp->num_planes; ++i) अणु
		पूर्णांक bpl = (pix_mp->width * fmt->row_depth[i]) / 8;
		पूर्णांक sizeimage = (pix_mp->width * pix_mp->height *
			fmt->depth[i]) / 8;

		pix_mp->plane_fmt[i].bytesperline = bpl;
		अगर (pix_mp->plane_fmt[i].sizeimage < sizeimage)
			pix_mp->plane_fmt[i].sizeimage = sizeimage;
		mtk_mdp_dbg(2, "[%d] p%d, bpl:%d, sizeimage:%u (%u)", ctx->id,
			    i, bpl, pix_mp->plane_fmt[i].sizeimage, sizeimage);
	पूर्ण

	वापस fmt;
पूर्ण

अटल काष्ठा mtk_mdp_frame *mtk_mdp_ctx_get_frame(काष्ठा mtk_mdp_ctx *ctx,
					    क्रमागत v4l2_buf_type type)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(type))
		वापस &ctx->s_frame;
	वापस &ctx->d_frame;
पूर्ण

अटल व्योम mtk_mdp_check_crop_change(u32 new_w, u32 new_h, u32 *w, u32 *h)
अणु
	अगर (new_w != *w || new_h != *h) अणु
		mtk_mdp_dbg(1, "size change:%dx%d to %dx%d",
			    *w, *h, new_w, new_h);

		*w = new_w;
		*h = new_h;
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_mdp_try_crop(काष्ठा mtk_mdp_ctx *ctx, u32 type,
			    काष्ठा v4l2_rect *r)
अणु
	काष्ठा mtk_mdp_frame *frame;
	काष्ठा mtk_mdp_dev *mdp = ctx->mdp_dev;
	काष्ठा mtk_mdp_variant *variant = mdp->variant;
	u32 align_w, align_h, new_w, new_h;
	u32 min_w, min_h, max_w, max_h;

	अगर (r->top < 0 || r->left < 0) अणु
		dev_err(&ctx->mdp_dev->pdev->dev,
			"doesn't support negative values for top & left\n");
		वापस -EINVAL;
	पूर्ण

	mtk_mdp_dbg(2, "[%d] type:%d, set wxh:%dx%d", ctx->id, type,
		    r->width, r->height);

	frame = mtk_mdp_ctx_get_frame(ctx, type);
	max_w = frame->width;
	max_h = frame->height;
	new_w = r->width;
	new_h = r->height;

	अगर (V4L2_TYPE_IS_OUTPUT(type)) अणु
		align_w = 1;
		align_h = 1;
		min_w = 64;
		min_h = 32;
	पूर्ण अन्यथा अणु
		align_w = variant->pix_align->target_w;
		align_h = variant->pix_align->target_h;
		अगर (ctx->ctrls.rotate->val == 90 ||
		    ctx->ctrls.rotate->val == 270) अणु
			max_w = frame->height;
			max_h = frame->width;
			min_w = variant->pix_min->target_rot_en_w;
			min_h = variant->pix_min->target_rot_en_h;
			new_w = r->height;
			new_h = r->width;
		पूर्ण अन्यथा अणु
			min_w = variant->pix_min->target_rot_dis_w;
			min_h = variant->pix_min->target_rot_dis_h;
		पूर्ण
	पूर्ण

	mtk_mdp_dbg(2, "[%d] align:%dx%d, min:%dx%d, new:%dx%d", ctx->id,
		    align_w, align_h, min_w, min_h, new_w, new_h);

	mtk_mdp_bound_align_image(&new_w, min_w, max_w, align_w,
				  &new_h, min_h, max_h, align_h);

	अगर (V4L2_TYPE_IS_CAPTURE(type) &&
	    (ctx->ctrls.rotate->val == 90 || ctx->ctrls.rotate->val == 270))
		mtk_mdp_check_crop_change(new_h, new_w,
					  &r->width, &r->height);
	अन्यथा
		mtk_mdp_check_crop_change(new_w, new_h,
					  &r->width, &r->height);

	/* adjust left/top अगर cropping rectangle is out of bounds */
	/* Need to add code to algin left value with 2's multiple */
	अगर (r->left + new_w > max_w)
		r->left = max_w - new_w;
	अगर (r->top + new_h > max_h)
		r->top = max_h - new_h;

	अगर (r->left & 1)
		r->left -= 1;

	mtk_mdp_dbg(2, "[%d] crop l,t,w,h:%d,%d,%d,%d, max:%dx%d", ctx->id,
		    r->left, r->top, r->width,
		    r->height, max_w, max_h);
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा mtk_mdp_ctx *fh_to_ctx(काष्ठा v4l2_fh *fh)
अणु
	वापस container_of(fh, काष्ठा mtk_mdp_ctx, fh);
पूर्ण

अटल अंतरभूत काष्ठा mtk_mdp_ctx *ctrl_to_ctx(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस container_of(ctrl->handler, काष्ठा mtk_mdp_ctx, ctrl_handler);
पूर्ण

व्योम mtk_mdp_ctx_state_lock_set(काष्ठा mtk_mdp_ctx *ctx, u32 state)
अणु
	mutex_lock(&ctx->slock);
	ctx->state |= state;
	mutex_unlock(&ctx->slock);
पूर्ण

अटल bool mtk_mdp_ctx_state_is_set(काष्ठा mtk_mdp_ctx *ctx, u32 mask)
अणु
	bool ret;

	mutex_lock(&ctx->slock);
	ret = (ctx->state & mask) == mask;
	mutex_unlock(&ctx->slock);
	वापस ret;
पूर्ण

अटल व्योम mtk_mdp_set_frame_size(काष्ठा mtk_mdp_frame *frame, पूर्णांक width,
				   पूर्णांक height)
अणु
	frame->width = width;
	frame->height = height;
	frame->crop.width = width;
	frame->crop.height = height;
	frame->crop.left = 0;
	frame->crop.top = 0;
पूर्ण

अटल पूर्णांक mtk_mdp_m2m_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा mtk_mdp_ctx *ctx = q->drv_priv;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(&ctx->mdp_dev->pdev->dev);
	अगर (ret < 0)
		mtk_mdp_dbg(1, "[%d] pm_runtime_get_sync failed:%d",
			    ctx->id, ret);

	वापस 0;
पूर्ण

अटल व्योम *mtk_mdp_m2m_buf_हटाओ(काष्ठा mtk_mdp_ctx *ctx,
				    क्रमागत v4l2_buf_type type)
अणु
	अगर (V4L2_TYPE_IS_OUTPUT(type))
		वापस v4l2_m2m_src_buf_हटाओ(ctx->m2m_ctx);
	अन्यथा
		वापस v4l2_m2m_dst_buf_हटाओ(ctx->m2m_ctx);
पूर्ण

अटल व्योम mtk_mdp_m2m_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा mtk_mdp_ctx *ctx = q->drv_priv;
	काष्ठा vb2_buffer *vb;

	vb = mtk_mdp_m2m_buf_हटाओ(ctx, q->type);
	जबतक (vb != शून्य) अणु
		v4l2_m2m_buf_करोne(to_vb2_v4l2_buffer(vb), VB2_BUF_STATE_ERROR);
		vb = mtk_mdp_m2m_buf_हटाओ(ctx, q->type);
	पूर्ण

	pm_runसमय_put(&ctx->mdp_dev->pdev->dev);
पूर्ण

/* The color क्रमmat (num_planes) must be alपढ़ोy configured. */
अटल व्योम mtk_mdp_prepare_addr(काष्ठा mtk_mdp_ctx *ctx,
				 काष्ठा vb2_buffer *vb,
				 काष्ठा mtk_mdp_frame *frame,
				 काष्ठा mtk_mdp_addr *addr)
अणु
	u32 pix_size, planes, i;

	pix_size = frame->width * frame->height;
	planes = min_t(u32, frame->fmt->num_planes, ARRAY_SIZE(addr->addr));
	क्रम (i = 0; i < planes; i++)
		addr->addr[i] = vb2_dma_contig_plane_dma_addr(vb, i);

	अगर (planes == 1) अणु
		अगर (frame->fmt->pixelक्रमmat == V4L2_PIX_FMT_YVU420) अणु
			addr->addr[1] = (dma_addr_t)(addr->addr[0] + pix_size);
			addr->addr[2] = (dma_addr_t)(addr->addr[1] +
					(pix_size >> 2));
		पूर्ण अन्यथा अणु
			dev_err(&ctx->mdp_dev->pdev->dev,
				"Invalid pixelformat:0x%x\n",
				frame->fmt->pixelक्रमmat);
		पूर्ण
	पूर्ण
	mtk_mdp_dbg(3, "[%d] planes:%d, size:%d, addr:%p,%p,%p",
		    ctx->id, planes, pix_size, (व्योम *)addr->addr[0],
		    (व्योम *)addr->addr[1], (व्योम *)addr->addr[2]);
पूर्ण

अटल व्योम mtk_mdp_m2m_get_bufs(काष्ठा mtk_mdp_ctx *ctx)
अणु
	काष्ठा mtk_mdp_frame *s_frame, *d_frame;
	काष्ठा vb2_v4l2_buffer *src_vbuf, *dst_vbuf;

	s_frame = &ctx->s_frame;
	d_frame = &ctx->d_frame;

	src_vbuf = v4l2_m2m_next_src_buf(ctx->m2m_ctx);
	mtk_mdp_prepare_addr(ctx, &src_vbuf->vb2_buf, s_frame, &s_frame->addr);

	dst_vbuf = v4l2_m2m_next_dst_buf(ctx->m2m_ctx);
	mtk_mdp_prepare_addr(ctx, &dst_vbuf->vb2_buf, d_frame, &d_frame->addr);

	dst_vbuf->vb2_buf.बारtamp = src_vbuf->vb2_buf.बारtamp;
पूर्ण

अटल व्योम mtk_mdp_process_करोne(व्योम *priv, पूर्णांक vb_state)
अणु
	काष्ठा mtk_mdp_dev *mdp = priv;
	काष्ठा mtk_mdp_ctx *ctx;
	काष्ठा vb2_v4l2_buffer *src_vbuf, *dst_vbuf;

	ctx = v4l2_m2m_get_curr_priv(mdp->m2m_dev);
	अगर (!ctx)
		वापस;

	src_vbuf = v4l2_m2m_src_buf_हटाओ(ctx->m2m_ctx);
	dst_vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->m2m_ctx);

	dst_vbuf->vb2_buf.बारtamp = src_vbuf->vb2_buf.बारtamp;
	dst_vbuf->समयcode = src_vbuf->समयcode;
	dst_vbuf->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	dst_vbuf->flags |= src_vbuf->flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK;

	v4l2_m2m_buf_करोne(src_vbuf, vb_state);
	v4l2_m2m_buf_करोne(dst_vbuf, vb_state);
	v4l2_m2m_job_finish(ctx->mdp_dev->m2m_dev, ctx->m2m_ctx);
पूर्ण

अटल व्योम mtk_mdp_m2m_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mtk_mdp_ctx *ctx =
				container_of(work, काष्ठा mtk_mdp_ctx, work);
	काष्ठा mtk_mdp_dev *mdp = ctx->mdp_dev;
	क्रमागत vb2_buffer_state buf_state = VB2_BUF_STATE_ERROR;
	पूर्णांक ret;

	अगर (mtk_mdp_ctx_state_is_set(ctx, MTK_MDP_CTX_ERROR)) अणु
		dev_err(&mdp->pdev->dev, "ctx is in error state");
		जाओ worker_end;
	पूर्ण

	mtk_mdp_m2m_get_bufs(ctx);

	mtk_mdp_hw_set_input_addr(ctx, &ctx->s_frame.addr);
	mtk_mdp_hw_set_output_addr(ctx, &ctx->d_frame.addr);

	mtk_mdp_hw_set_in_size(ctx);
	mtk_mdp_hw_set_in_image_क्रमmat(ctx);

	mtk_mdp_hw_set_out_size(ctx);
	mtk_mdp_hw_set_out_image_क्रमmat(ctx);

	mtk_mdp_hw_set_rotation(ctx);
	mtk_mdp_hw_set_global_alpha(ctx);

	ret = mtk_mdp_vpu_process(&ctx->vpu);
	अगर (ret) अणु
		dev_err(&mdp->pdev->dev, "processing failed: %d", ret);
		जाओ worker_end;
	पूर्ण

	buf_state = VB2_BUF_STATE_DONE;

worker_end:
	mtk_mdp_process_करोne(mdp, buf_state);
पूर्ण

अटल व्योम mtk_mdp_m2m_device_run(व्योम *priv)
अणु
	काष्ठा mtk_mdp_ctx *ctx = priv;

	queue_work(ctx->mdp_dev->job_wq, &ctx->work);
पूर्ण

अटल पूर्णांक mtk_mdp_m2m_queue_setup(काष्ठा vb2_queue *vq,
			अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा mtk_mdp_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा mtk_mdp_frame *frame;
	पूर्णांक i;

	frame = mtk_mdp_ctx_get_frame(ctx, vq->type);
	*num_planes = frame->fmt->num_planes;
	क्रम (i = 0; i < frame->fmt->num_planes; i++)
		sizes[i] = frame->payload[i];
	mtk_mdp_dbg(2, "[%d] type:%d, planes:%d, buffers:%d, size:%u,%u",
		    ctx->id, vq->type, *num_planes, *num_buffers,
		    sizes[0], sizes[1]);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_mdp_m2m_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा mtk_mdp_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा mtk_mdp_frame *frame;
	पूर्णांक i;

	frame = mtk_mdp_ctx_get_frame(ctx, vb->vb2_queue->type);

	अगर (!V4L2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) अणु
		क्रम (i = 0; i < frame->fmt->num_planes; i++)
			vb2_set_plane_payload(vb, i, frame->payload[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_mdp_m2m_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा mtk_mdp_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_m2m_buf_queue(ctx->m2m_ctx, to_vb2_v4l2_buffer(vb));
पूर्ण

अटल स्थिर काष्ठा vb2_ops mtk_mdp_m2m_qops = अणु
	.queue_setup	 = mtk_mdp_m2m_queue_setup,
	.buf_prepare	 = mtk_mdp_m2m_buf_prepare,
	.buf_queue	 = mtk_mdp_m2m_buf_queue,
	.stop_streaming	 = mtk_mdp_m2m_stop_streaming,
	.start_streaming = mtk_mdp_m2m_start_streaming,
	.रुको_prepare	 = vb2_ops_रुको_prepare,
	.रुको_finish	 = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक mtk_mdp_m2m_querycap(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_capability *cap)
अणु
	काष्ठा mtk_mdp_ctx *ctx = fh_to_ctx(fh);
	काष्ठा mtk_mdp_dev *mdp = ctx->mdp_dev;

	strscpy(cap->driver, MTK_MDP_MODULE_NAME, माप(cap->driver));
	strscpy(cap->card, mdp->pdev->name, माप(cap->card));
	strscpy(cap->bus_info, "platform:mt8173", माप(cap->bus_info));

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_mdp_क्रमागत_fmt(काष्ठा v4l2_fmtdesc *f, u32 type)
अणु
	स्थिर काष्ठा mtk_mdp_fmt *fmt;

	fmt = mtk_mdp_find_fmt_by_index(f->index, type);
	अगर (!fmt)
		वापस -EINVAL;

	f->pixelक्रमmat = fmt->pixelक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_mdp_m2m_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	वापस mtk_mdp_क्रमागत_fmt(f, V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
पूर्ण

अटल पूर्णांक mtk_mdp_m2m_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	वापस mtk_mdp_क्रमागत_fmt(f, V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
पूर्ण

अटल पूर्णांक mtk_mdp_m2m_g_fmt_mplane(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mtk_mdp_ctx *ctx = fh_to_ctx(fh);
	काष्ठा mtk_mdp_frame *frame;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp;
	पूर्णांक i;

	mtk_mdp_dbg(2, "[%d] type:%d", ctx->id, f->type);

	frame = mtk_mdp_ctx_get_frame(ctx, f->type);
	pix_mp = &f->fmt.pix_mp;

	pix_mp->width = frame->width;
	pix_mp->height = frame->height;
	pix_mp->field = V4L2_FIELD_NONE;
	pix_mp->pixelक्रमmat = frame->fmt->pixelक्रमmat;
	pix_mp->num_planes = frame->fmt->num_planes;
	pix_mp->colorspace = ctx->colorspace;
	pix_mp->xfer_func = ctx->xfer_func;
	pix_mp->ycbcr_enc = ctx->ycbcr_enc;
	pix_mp->quantization = ctx->quant;
	mtk_mdp_dbg(2, "[%d] wxh:%dx%d", ctx->id,
		    pix_mp->width, pix_mp->height);

	क्रम (i = 0; i < pix_mp->num_planes; ++i) अणु
		pix_mp->plane_fmt[i].bytesperline = (frame->width *
			frame->fmt->row_depth[i]) / 8;
		pix_mp->plane_fmt[i].sizeimage = (frame->width *
			frame->height * frame->fmt->depth[i]) / 8;

		mtk_mdp_dbg(2, "[%d] p%d, bpl:%d, sizeimage:%d", ctx->id, i,
			    pix_mp->plane_fmt[i].bytesperline,
			    pix_mp->plane_fmt[i].sizeimage);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_mdp_m2m_try_fmt_mplane(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mtk_mdp_ctx *ctx = fh_to_ctx(fh);

	अगर (!mtk_mdp_try_fmt_mplane(ctx, f))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_mdp_m2m_s_fmt_mplane(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mtk_mdp_ctx *ctx = fh_to_ctx(fh);
	काष्ठा vb2_queue *vq;
	काष्ठा mtk_mdp_frame *frame;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp;
	स्थिर काष्ठा mtk_mdp_fmt *fmt;
	पूर्णांक i;

	mtk_mdp_dbg(2, "[%d] type:%d", ctx->id, f->type);

	frame = mtk_mdp_ctx_get_frame(ctx, f->type);
	fmt = mtk_mdp_try_fmt_mplane(ctx, f);
	अगर (!fmt) अणु
		mtk_mdp_err("[%d] try_fmt failed, type:%d", ctx->id, f->type);
		वापस -EINVAL;
	पूर्ण
	frame->fmt = fmt;

	vq = v4l2_m2m_get_vq(ctx->m2m_ctx, f->type);
	अगर (vb2_is_streaming(vq)) अणु
		dev_info(&ctx->mdp_dev->pdev->dev, "queue %d busy", f->type);
		वापस -EBUSY;
	पूर्ण

	pix_mp = &f->fmt.pix_mp;
	क्रम (i = 0; i < frame->fmt->num_planes; i++) अणु
		frame->payload[i] = pix_mp->plane_fmt[i].sizeimage;
		frame->pitch[i] = pix_mp->plane_fmt[i].bytesperline;
	पूर्ण

	mtk_mdp_set_frame_size(frame, pix_mp->width, pix_mp->height);
	अगर (V4L2_TYPE_IS_OUTPUT(f->type)) अणु
		ctx->colorspace = pix_mp->colorspace;
		ctx->xfer_func = pix_mp->xfer_func;
		ctx->ycbcr_enc = pix_mp->ycbcr_enc;
		ctx->quant = pix_mp->quantization;
	पूर्ण

	mtk_mdp_dbg(2, "[%d] type:%d, frame:%dx%d", ctx->id, f->type,
		    frame->width, frame->height);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_mdp_m2m_reqbufs(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_requestbuffers *reqbufs)
अणु
	काष्ठा mtk_mdp_ctx *ctx = fh_to_ctx(fh);

	वापस v4l2_m2m_reqbufs(file, ctx->m2m_ctx, reqbufs);
पूर्ण

अटल पूर्णांक mtk_mdp_m2m_streamon(काष्ठा file *file, व्योम *fh,
				क्रमागत v4l2_buf_type type)
अणु
	काष्ठा mtk_mdp_ctx *ctx = fh_to_ctx(fh);
	पूर्णांक ret;

	अगर (!mtk_mdp_ctx_state_is_set(ctx, MTK_MDP_VPU_INIT)) अणु
		ret = mtk_mdp_vpu_init(&ctx->vpu);
		अगर (ret < 0) अणु
			dev_err(&ctx->mdp_dev->pdev->dev,
				"vpu init failed %d\n",
				ret);
			वापस -EINVAL;
		पूर्ण
		mtk_mdp_ctx_state_lock_set(ctx, MTK_MDP_VPU_INIT);
	पूर्ण

	वापस v4l2_m2m_streamon(file, ctx->m2m_ctx, type);
पूर्ण

अटल अंतरभूत bool mtk_mdp_is_target_compose(u32 target)
अणु
	अगर (target == V4L2_SEL_TGT_COMPOSE_DEFAULT
	    || target == V4L2_SEL_TGT_COMPOSE_BOUNDS
	    || target == V4L2_SEL_TGT_COMPOSE)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool mtk_mdp_is_target_crop(u32 target)
अणु
	अगर (target == V4L2_SEL_TGT_CROP_DEFAULT
	    || target == V4L2_SEL_TGT_CROP_BOUNDS
	    || target == V4L2_SEL_TGT_CROP)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक mtk_mdp_m2m_g_selection(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_selection *s)
अणु
	काष्ठा mtk_mdp_frame *frame;
	काष्ठा mtk_mdp_ctx *ctx = fh_to_ctx(fh);
	bool valid = false;

	अगर (s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		अगर (mtk_mdp_is_target_compose(s->target))
			valid = true;
	पूर्ण अन्यथा अगर (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		अगर (mtk_mdp_is_target_crop(s->target))
			valid = true;
	पूर्ण
	अगर (!valid) अणु
		mtk_mdp_dbg(1, "[%d] invalid type:%d,%u", ctx->id, s->type,
			    s->target);
		वापस -EINVAL;
	पूर्ण

	frame = mtk_mdp_ctx_get_frame(ctx, s->type);

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = frame->width;
		s->r.height = frame->height;
		वापस 0;

	हाल V4L2_SEL_TGT_COMPOSE:
	हाल V4L2_SEL_TGT_CROP:
		s->r.left = frame->crop.left;
		s->r.top = frame->crop.top;
		s->r.width = frame->crop.width;
		s->r.height = frame->crop.height;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mtk_mdp_check_scaler_ratio(काष्ठा mtk_mdp_variant *var, पूर्णांक src_w,
				      पूर्णांक src_h, पूर्णांक dst_w, पूर्णांक dst_h, पूर्णांक rot)
अणु
	पूर्णांक पंचांगp_w, पंचांगp_h;

	अगर (rot == 90 || rot == 270) अणु
		पंचांगp_w = dst_h;
		पंचांगp_h = dst_w;
	पूर्ण अन्यथा अणु
		पंचांगp_w = dst_w;
		पंचांगp_h = dst_h;
	पूर्ण

	अगर ((src_w / पंचांगp_w) > var->h_scale_करोwn_max ||
	    (src_h / पंचांगp_h) > var->v_scale_करोwn_max ||
	    (पंचांगp_w / src_w) > var->h_scale_up_max ||
	    (पंचांगp_h / src_h) > var->v_scale_up_max)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_mdp_m2m_s_selection(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_selection *s)
अणु
	काष्ठा mtk_mdp_frame *frame;
	काष्ठा mtk_mdp_ctx *ctx = fh_to_ctx(fh);
	काष्ठा v4l2_rect new_r;
	काष्ठा mtk_mdp_variant *variant = ctx->mdp_dev->variant;
	पूर्णांक ret;
	bool valid = false;

	अगर (s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		अगर (s->target == V4L2_SEL_TGT_COMPOSE)
			valid = true;
	पूर्ण अन्यथा अगर (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		अगर (s->target == V4L2_SEL_TGT_CROP)
			valid = true;
	पूर्ण
	अगर (!valid) अणु
		mtk_mdp_dbg(1, "[%d] invalid type:%d,%u", ctx->id, s->type,
			    s->target);
		वापस -EINVAL;
	पूर्ण

	new_r = s->r;
	ret = mtk_mdp_try_crop(ctx, s->type, &new_r);
	अगर (ret)
		वापस ret;

	अगर (mtk_mdp_is_target_crop(s->target))
		frame = &ctx->s_frame;
	अन्यथा
		frame = &ctx->d_frame;

	/* Check to see अगर scaling ratio is within supported range */
	अगर (V4L2_TYPE_IS_OUTPUT(s->type))
		ret = mtk_mdp_check_scaler_ratio(variant, new_r.width,
			new_r.height, ctx->d_frame.crop.width,
			ctx->d_frame.crop.height,
			ctx->ctrls.rotate->val);
	अन्यथा
		ret = mtk_mdp_check_scaler_ratio(variant,
			ctx->s_frame.crop.width,
			ctx->s_frame.crop.height, new_r.width,
			new_r.height, ctx->ctrls.rotate->val);

	अगर (ret) अणु
		dev_info(&ctx->mdp_dev->pdev->dev,
			"Out of scaler range");
		वापस -EINVAL;
	पूर्ण

	s->r = new_r;
	frame->crop = new_r;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops mtk_mdp_m2m_ioctl_ops = अणु
	.vidioc_querycap		= mtk_mdp_m2m_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= mtk_mdp_m2m_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_out	= mtk_mdp_m2m_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_cap_mplane	= mtk_mdp_m2m_g_fmt_mplane,
	.vidioc_g_fmt_vid_out_mplane	= mtk_mdp_m2m_g_fmt_mplane,
	.vidioc_try_fmt_vid_cap_mplane	= mtk_mdp_m2m_try_fmt_mplane,
	.vidioc_try_fmt_vid_out_mplane	= mtk_mdp_m2m_try_fmt_mplane,
	.vidioc_s_fmt_vid_cap_mplane	= mtk_mdp_m2m_s_fmt_mplane,
	.vidioc_s_fmt_vid_out_mplane	= mtk_mdp_m2m_s_fmt_mplane,
	.vidioc_reqbufs			= mtk_mdp_m2m_reqbufs,
	.vidioc_create_bufs		= v4l2_m2m_ioctl_create_bufs,
	.vidioc_expbuf			= v4l2_m2m_ioctl_expbuf,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
	.vidioc_querybuf		= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf			= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf			= v4l2_m2m_ioctl_dqbuf,
	.vidioc_streamon		= mtk_mdp_m2m_streamon,
	.vidioc_streamoff		= v4l2_m2m_ioctl_streamoff,
	.vidioc_g_selection		= mtk_mdp_m2m_g_selection,
	.vidioc_s_selection		= mtk_mdp_m2m_s_selection
पूर्ण;

अटल पूर्णांक mtk_mdp_m2m_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
				  काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा mtk_mdp_ctx *ctx = priv;
	पूर्णांक ret;

	स_रखो(src_vq, 0, माप(*src_vq));
	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	src_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	src_vq->drv_priv = ctx;
	src_vq->ops = &mtk_mdp_m2m_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->dev = &ctx->mdp_dev->pdev->dev;
	src_vq->lock = &ctx->mdp_dev->lock;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	स_रखो(dst_vq, 0, माप(*dst_vq));
	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->drv_priv = ctx;
	dst_vq->ops = &mtk_mdp_m2m_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->dev = &ctx->mdp_dev->pdev->dev;
	dst_vq->lock = &ctx->mdp_dev->lock;

	वापस vb2_queue_init(dst_vq);
पूर्ण

अटल पूर्णांक mtk_mdp_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा mtk_mdp_ctx *ctx = ctrl_to_ctx(ctrl);
	काष्ठा mtk_mdp_dev *mdp = ctx->mdp_dev;
	काष्ठा mtk_mdp_variant *variant = mdp->variant;
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
		ret = mtk_mdp_check_scaler_ratio(variant,
				ctx->s_frame.crop.width,
				ctx->s_frame.crop.height,
				ctx->d_frame.crop.width,
				ctx->d_frame.crop.height,
				ctx->ctrls.rotate->val);

		अगर (ret)
			वापस -EINVAL;

		ctx->rotation = ctrl->val;
		अवरोध;
	हाल V4L2_CID_ALPHA_COMPONENT:
		ctx->d_frame.alpha = ctrl->val;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops mtk_mdp_ctrl_ops = अणु
	.s_ctrl = mtk_mdp_s_ctrl,
पूर्ण;

अटल पूर्णांक mtk_mdp_ctrls_create(काष्ठा mtk_mdp_ctx *ctx)
अणु
	v4l2_ctrl_handler_init(&ctx->ctrl_handler, MTK_MDP_MAX_CTRL_NUM);

	ctx->ctrls.rotate = v4l2_ctrl_new_std(&ctx->ctrl_handler,
			&mtk_mdp_ctrl_ops, V4L2_CID_ROTATE, 0, 270, 90, 0);
	ctx->ctrls.hflip = v4l2_ctrl_new_std(&ctx->ctrl_handler,
					     &mtk_mdp_ctrl_ops,
					     V4L2_CID_HFLIP,
					     0, 1, 1, 0);
	ctx->ctrls.vflip = v4l2_ctrl_new_std(&ctx->ctrl_handler,
					     &mtk_mdp_ctrl_ops,
					     V4L2_CID_VFLIP,
					     0, 1, 1, 0);
	ctx->ctrls.global_alpha = v4l2_ctrl_new_std(&ctx->ctrl_handler,
						    &mtk_mdp_ctrl_ops,
						    V4L2_CID_ALPHA_COMPONENT,
						    0, 255, 1, 0);
	ctx->ctrls_rdy = ctx->ctrl_handler.error == 0;

	अगर (ctx->ctrl_handler.error) अणु
		पूर्णांक err = ctx->ctrl_handler.error;

		v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
		dev_err(&ctx->mdp_dev->pdev->dev,
			"Failed to create control handlers\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_mdp_set_शेष_params(काष्ठा mtk_mdp_ctx *ctx)
अणु
	काष्ठा mtk_mdp_dev *mdp = ctx->mdp_dev;
	काष्ठा mtk_mdp_frame *frame;

	frame = mtk_mdp_ctx_get_frame(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
	frame->fmt = mtk_mdp_find_fmt_by_index(0,
					V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
	frame->width = mdp->variant->pix_min->org_w;
	frame->height = mdp->variant->pix_min->org_h;
	frame->payload[0] = frame->width * frame->height;
	frame->payload[1] = frame->payload[0] / 2;

	frame = mtk_mdp_ctx_get_frame(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
	frame->fmt = mtk_mdp_find_fmt_by_index(0,
					V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
	frame->width = mdp->variant->pix_min->target_rot_dis_w;
	frame->height = mdp->variant->pix_min->target_rot_dis_h;
	frame->payload[0] = frame->width * frame->height;
	frame->payload[1] = frame->payload[0] / 2;

पूर्ण

अटल पूर्णांक mtk_mdp_m2m_खोलो(काष्ठा file *file)
अणु
	काष्ठा mtk_mdp_dev *mdp = video_drvdata(file);
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा mtk_mdp_ctx *ctx = शून्य;
	पूर्णांक ret;
	काष्ठा v4l2_क्रमmat शेष_क्रमmat;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	अगर (mutex_lock_पूर्णांकerruptible(&mdp->lock)) अणु
		ret = -ERESTARTSYS;
		जाओ err_lock;
	पूर्ण

	mutex_init(&ctx->slock);
	ctx->id = mdp->id_counter++;
	v4l2_fh_init(&ctx->fh, vfd);
	file->निजी_data = &ctx->fh;
	ret = mtk_mdp_ctrls_create(ctx);
	अगर (ret)
		जाओ error_ctrls;

	/* Use separate control handler per file handle */
	ctx->fh.ctrl_handler = &ctx->ctrl_handler;
	v4l2_fh_add(&ctx->fh);
	INIT_LIST_HEAD(&ctx->list);

	ctx->mdp_dev = mdp;
	mtk_mdp_set_शेष_params(ctx);

	INIT_WORK(&ctx->work, mtk_mdp_m2m_worker);
	ctx->m2m_ctx = v4l2_m2m_ctx_init(mdp->m2m_dev, ctx,
					 mtk_mdp_m2m_queue_init);
	अगर (IS_ERR(ctx->m2m_ctx)) अणु
		dev_err(&mdp->pdev->dev, "Failed to initialize m2m context");
		ret = PTR_ERR(ctx->m2m_ctx);
		जाओ error_m2m_ctx;
	पूर्ण
	ctx->fh.m2m_ctx = ctx->m2m_ctx;
	अगर (mdp->ctx_num++ == 0) अणु
		ret = vpu_load_firmware(mdp->vpu_dev);
		अगर (ret < 0) अणु
			dev_err(&mdp->pdev->dev,
				"vpu_load_firmware failed %d\n", ret);
			जाओ err_load_vpu;
		पूर्ण

		ret = mtk_mdp_vpu_रेजिस्टर(mdp->pdev);
		अगर (ret < 0) अणु
			dev_err(&mdp->pdev->dev,
				"mdp_vpu register failed %d\n", ret);
			जाओ err_load_vpu;
		पूर्ण
	पूर्ण

	list_add(&ctx->list, &mdp->ctx_list);
	mutex_unlock(&mdp->lock);

	/* Default क्रमmat */
	स_रखो(&शेष_क्रमmat, 0, माप(शेष_क्रमmat));
	शेष_क्रमmat.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	शेष_क्रमmat.fmt.pix_mp.width = 32;
	शेष_क्रमmat.fmt.pix_mp.height = 32;
	शेष_क्रमmat.fmt.pix_mp.pixelक्रमmat = V4L2_PIX_FMT_YUV420M;
	mtk_mdp_m2m_s_fmt_mplane(file, &ctx->fh, &शेष_क्रमmat);
	शेष_क्रमmat.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	mtk_mdp_m2m_s_fmt_mplane(file, &ctx->fh, &शेष_क्रमmat);

	mtk_mdp_dbg(0, "%s [%d]", dev_name(&mdp->pdev->dev), ctx->id);

	वापस 0;

err_load_vpu:
	mdp->ctx_num--;
	v4l2_m2m_ctx_release(ctx->m2m_ctx);
error_m2m_ctx:
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
error_ctrls:
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	mutex_unlock(&mdp->lock);
err_lock:
	kमुक्त(ctx);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_mdp_m2m_release(काष्ठा file *file)
अणु
	काष्ठा mtk_mdp_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा mtk_mdp_dev *mdp = ctx->mdp_dev;

	flush_workqueue(mdp->job_wq);
	mutex_lock(&mdp->lock);
	v4l2_m2m_ctx_release(ctx->m2m_ctx);
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	mtk_mdp_vpu_deinit(&ctx->vpu);
	mdp->ctx_num--;
	list_del_init(&ctx->list);

	mtk_mdp_dbg(0, "%s [%d]", dev_name(&mdp->pdev->dev), ctx->id);

	mutex_unlock(&mdp->lock);
	kमुक्त(ctx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations mtk_mdp_m2m_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= mtk_mdp_m2m_खोलो,
	.release	= mtk_mdp_m2m_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_m2m_ops mtk_mdp_m2m_ops = अणु
	.device_run	= mtk_mdp_m2m_device_run,
पूर्ण;

पूर्णांक mtk_mdp_रेजिस्टर_m2m_device(काष्ठा mtk_mdp_dev *mdp)
अणु
	काष्ठा device *dev = &mdp->pdev->dev;
	पूर्णांक ret;

	mdp->variant = &mtk_mdp_शेष_variant;
	mdp->vdev = video_device_alloc();
	अगर (!mdp->vdev) अणु
		dev_err(dev, "failed to allocate video device\n");
		ret = -ENOMEM;
		जाओ err_video_alloc;
	पूर्ण
	mdp->vdev->device_caps = V4L2_CAP_VIDEO_M2M_MPLANE | V4L2_CAP_STREAMING;
	mdp->vdev->fops = &mtk_mdp_m2m_fops;
	mdp->vdev->ioctl_ops = &mtk_mdp_m2m_ioctl_ops;
	mdp->vdev->release = video_device_release;
	mdp->vdev->lock = &mdp->lock;
	mdp->vdev->vfl_dir = VFL_सूची_M2M;
	mdp->vdev->v4l2_dev = &mdp->v4l2_dev;
	snम_लिखो(mdp->vdev->name, माप(mdp->vdev->name), "%s:m2m",
		 MTK_MDP_MODULE_NAME);
	video_set_drvdata(mdp->vdev, mdp);

	mdp->m2m_dev = v4l2_m2m_init(&mtk_mdp_m2m_ops);
	अगर (IS_ERR(mdp->m2m_dev)) अणु
		dev_err(dev, "failed to initialize v4l2-m2m device\n");
		ret = PTR_ERR(mdp->m2m_dev);
		जाओ err_m2m_init;
	पूर्ण

	ret = video_रेजिस्टर_device(mdp->vdev, VFL_TYPE_VIDEO, 2);
	अगर (ret) अणु
		dev_err(dev, "failed to register video device\n");
		जाओ err_vdev_रेजिस्टर;
	पूर्ण

	v4l2_info(&mdp->v4l2_dev, "driver registered as /dev/video%d",
		  mdp->vdev->num);
	वापस 0;

err_vdev_रेजिस्टर:
	v4l2_m2m_release(mdp->m2m_dev);
err_m2m_init:
	video_device_release(mdp->vdev);
err_video_alloc:

	वापस ret;
पूर्ण

व्योम mtk_mdp_unरेजिस्टर_m2m_device(काष्ठा mtk_mdp_dev *mdp)
अणु
	video_unरेजिस्टर_device(mdp->vdev);
	v4l2_m2m_release(mdp->m2m_dev);
पूर्ण
