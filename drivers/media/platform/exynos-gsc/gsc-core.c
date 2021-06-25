<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011 - 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Samsung EXYNOS5 SoC series G-Scaler driver
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश "gsc-core.h"

अटल स्थिर काष्ठा gsc_fmt gsc_क्रमmats[] = अणु
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_RGB565X,
		.depth		= अणु 16 पूर्ण,
		.color		= GSC_RGB,
		.num_planes	= 1,
		.num_comp	= 1,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_BGR32,
		.depth		= अणु 32 पूर्ण,
		.color		= GSC_RGB,
		.num_planes	= 1,
		.num_comp	= 1,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YUYV,
		.depth		= अणु 16 पूर्ण,
		.color		= GSC_YUV422,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CBCR,
		.num_planes	= 1,
		.num_comp	= 1,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_UYVY,
		.depth		= अणु 16 पूर्ण,
		.color		= GSC_YUV422,
		.yorder		= GSC_LSB_C,
		.corder		= GSC_CBCR,
		.num_planes	= 1,
		.num_comp	= 1,
		.mbus_code	= MEDIA_BUS_FMT_UYVY8_2X8,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_VYUY,
		.depth		= अणु 16 पूर्ण,
		.color		= GSC_YUV422,
		.yorder		= GSC_LSB_C,
		.corder		= GSC_CRCB,
		.num_planes	= 1,
		.num_comp	= 1,
		.mbus_code	= MEDIA_BUS_FMT_VYUY8_2X8,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YVYU,
		.depth		= अणु 16 पूर्ण,
		.color		= GSC_YUV422,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CRCB,
		.num_planes	= 1,
		.num_comp	= 1,
		.mbus_code	= MEDIA_BUS_FMT_YVYU8_2X8,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YUV32,
		.depth		= अणु 32 पूर्ण,
		.color		= GSC_YUV444,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CBCR,
		.num_planes	= 1,
		.num_comp	= 1,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YUV422P,
		.depth		= अणु 16 पूर्ण,
		.color		= GSC_YUV422,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CBCR,
		.num_planes	= 1,
		.num_comp	= 3,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_NV16,
		.depth		= अणु 16 पूर्ण,
		.color		= GSC_YUV422,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CBCR,
		.num_planes	= 1,
		.num_comp	= 2,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_NV16M,
		.depth		= अणु 8, 8 पूर्ण,
		.color		= GSC_YUV422,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CBCR,
		.num_planes	= 2,
		.num_comp	= 2,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_NV61,
		.depth		= अणु 16 पूर्ण,
		.color		= GSC_YUV422,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CRCB,
		.num_planes	= 1,
		.num_comp	= 2,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_NV61M,
		.depth		= अणु 8, 8 पूर्ण,
		.color		= GSC_YUV422,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CRCB,
		.num_planes	= 2,
		.num_comp	= 2,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YUV420,
		.depth		= अणु 12 पूर्ण,
		.color		= GSC_YUV420,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CBCR,
		.num_planes	= 1,
		.num_comp	= 3,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YVU420,
		.depth		= अणु 12 पूर्ण,
		.color		= GSC_YUV420,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CRCB,
		.num_planes	= 1,
		.num_comp	= 3,

	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_NV12,
		.depth		= अणु 12 पूर्ण,
		.color		= GSC_YUV420,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CBCR,
		.num_planes	= 1,
		.num_comp	= 2,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_NV21,
		.depth		= अणु 12 पूर्ण,
		.color		= GSC_YUV420,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CRCB,
		.num_planes	= 1,
		.num_comp	= 2,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_NV21M,
		.depth		= अणु 8, 4 पूर्ण,
		.color		= GSC_YUV420,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CRCB,
		.num_planes	= 2,
		.num_comp	= 2,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_NV12M,
		.depth		= अणु 8, 4 पूर्ण,
		.color		= GSC_YUV420,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CBCR,
		.num_planes	= 2,
		.num_comp	= 2,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YUV420M,
		.depth		= अणु 8, 2, 2 पूर्ण,
		.color		= GSC_YUV420,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CBCR,
		.num_planes	= 3,
		.num_comp	= 3,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YVU420M,
		.depth		= अणु 8, 2, 2 पूर्ण,
		.color		= GSC_YUV420,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CRCB,
		.num_planes	= 3,
		.num_comp	= 3,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_NV12MT_16X16,
		.depth		= अणु 8, 4 पूर्ण,
		.color		= GSC_YUV420,
		.yorder		= GSC_LSB_Y,
		.corder		= GSC_CBCR,
		.num_planes	= 2,
		.num_comp	= 2,
	पूर्ण
पूर्ण;

स्थिर काष्ठा gsc_fmt *get_क्रमmat(पूर्णांक index)
अणु
	अगर (index >= ARRAY_SIZE(gsc_क्रमmats))
		वापस शून्य;

	वापस (काष्ठा gsc_fmt *)&gsc_क्रमmats[index];
पूर्ण

स्थिर काष्ठा gsc_fmt *find_fmt(u32 *pixelक्रमmat, u32 *mbus_code, u32 index)
अणु
	स्थिर काष्ठा gsc_fmt *fmt, *def_fmt = शून्य;
	अचिन्हित पूर्णांक i;

	अगर (index >= ARRAY_SIZE(gsc_क्रमmats))
		वापस शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(gsc_क्रमmats); ++i) अणु
		fmt = get_क्रमmat(i);
		अगर (pixelक्रमmat && fmt->pixelक्रमmat == *pixelक्रमmat)
			वापस fmt;
		अगर (mbus_code && fmt->mbus_code == *mbus_code)
			वापस fmt;
		अगर (index == i)
			def_fmt = fmt;
	पूर्ण
	वापस def_fmt;

पूर्ण

व्योम gsc_set_frame_size(काष्ठा gsc_frame *frame, पूर्णांक width, पूर्णांक height)
अणु
	frame->f_width	= width;
	frame->f_height	= height;
	frame->crop.width = width;
	frame->crop.height = height;
	frame->crop.left = 0;
	frame->crop.top = 0;
पूर्ण

पूर्णांक gsc_cal_prescaler_ratio(काष्ठा gsc_variant *var, u32 src, u32 dst,
								u32 *ratio)
अणु
	अगर ((dst > src) || (dst >= src / var->poly_sc_करोwn_max)) अणु
		*ratio = 1;
		वापस 0;
	पूर्ण

	अगर ((src / var->poly_sc_करोwn_max / var->pre_sc_करोwn_max) > dst) अणु
		pr_err("Exceeded maximum downscaling ratio (1/16))");
		वापस -EINVAL;
	पूर्ण

	*ratio = (dst > (src / 8)) ? 2 : 4;

	वापस 0;
पूर्ण

व्योम gsc_get_prescaler_shfactor(u32 hratio, u32 vratio, u32 *sh)
अणु
	अगर (hratio == 4 && vratio == 4)
		*sh = 4;
	अन्यथा अगर ((hratio == 4 && vratio == 2) ||
		 (hratio == 2 && vratio == 4))
		*sh = 3;
	अन्यथा अगर ((hratio == 4 && vratio == 1) ||
		 (hratio == 1 && vratio == 4) ||
		 (hratio == 2 && vratio == 2))
		*sh = 2;
	अन्यथा अगर (hratio == 1 && vratio == 1)
		*sh = 0;
	अन्यथा
		*sh = 1;
पूर्ण

व्योम gsc_check_src_scale_info(काष्ठा gsc_variant *var,
				काष्ठा gsc_frame *s_frame, u32 *wratio,
				 u32 tx, u32 ty, u32 *hratio)
अणु
	पूर्णांक reमुख्यder = 0, walign, halign;

	अगर (is_yuv420(s_frame->fmt->color)) अणु
		walign = GSC_SC_ALIGN_4;
		halign = GSC_SC_ALIGN_4;
	पूर्ण अन्यथा अगर (is_yuv422(s_frame->fmt->color)) अणु
		walign = GSC_SC_ALIGN_4;
		halign = GSC_SC_ALIGN_2;
	पूर्ण अन्यथा अणु
		walign = GSC_SC_ALIGN_2;
		halign = GSC_SC_ALIGN_2;
	पूर्ण

	reमुख्यder = s_frame->crop.width % (*wratio * walign);
	अगर (reमुख्यder) अणु
		s_frame->crop.width -= reमुख्यder;
		gsc_cal_prescaler_ratio(var, s_frame->crop.width, tx, wratio);
		pr_info("cropped src width size is recalculated from %d to %d",
			s_frame->crop.width + reमुख्यder, s_frame->crop.width);
	पूर्ण

	reमुख्यder = s_frame->crop.height % (*hratio * halign);
	अगर (reमुख्यder) अणु
		s_frame->crop.height -= reमुख्यder;
		gsc_cal_prescaler_ratio(var, s_frame->crop.height, ty, hratio);
		pr_info("cropped src height size is recalculated from %d to %d",
			s_frame->crop.height + reमुख्यder, s_frame->crop.height);
	पूर्ण
पूर्ण

पूर्णांक gsc_क्रमागत_fmt(काष्ठा v4l2_fmtdesc *f)
अणु
	स्थिर काष्ठा gsc_fmt *fmt;

	fmt = find_fmt(शून्य, शून्य, f->index);
	अगर (!fmt)
		वापस -EINVAL;

	f->pixelक्रमmat = fmt->pixelक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक get_plane_info(काष्ठा gsc_frame *frm, u32 addr, u32 *index, u32 *ret_addr)
अणु
	अगर (frm->addr.y == addr) अणु
		*index = 0;
		*ret_addr = frm->addr.y;
	पूर्ण अन्यथा अगर (frm->addr.cb == addr) अणु
		*index = 1;
		*ret_addr = frm->addr.cb;
	पूर्ण अन्यथा अगर (frm->addr.cr == addr) अणु
		*index = 2;
		*ret_addr = frm->addr.cr;
	पूर्ण अन्यथा अणु
		pr_err("Plane address is wrong");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

व्योम gsc_set_prefbuf(काष्ठा gsc_dev *gsc, काष्ठा gsc_frame *frm)
अणु
	u32 f_chk_addr, f_chk_len, s_chk_addr, s_chk_len;
	f_chk_addr = f_chk_len = s_chk_addr = s_chk_len = 0;

	f_chk_addr = frm->addr.y;
	f_chk_len = frm->payload[0];
	अगर (frm->fmt->num_planes == 2) अणु
		s_chk_addr = frm->addr.cb;
		s_chk_len = frm->payload[1];
	पूर्ण अन्यथा अगर (frm->fmt->num_planes == 3) अणु
		u32 low_addr, low_plane, mid_addr, mid_plane;
		u32 high_addr, high_plane;
		u32 t_min, t_max;

		t_min = min3(frm->addr.y, frm->addr.cb, frm->addr.cr);
		अगर (get_plane_info(frm, t_min, &low_plane, &low_addr))
			वापस;
		t_max = max3(frm->addr.y, frm->addr.cb, frm->addr.cr);
		अगर (get_plane_info(frm, t_max, &high_plane, &high_addr))
			वापस;

		mid_plane = 3 - (low_plane + high_plane);
		अगर (mid_plane == 0)
			mid_addr = frm->addr.y;
		अन्यथा अगर (mid_plane == 1)
			mid_addr = frm->addr.cb;
		अन्यथा अगर (mid_plane == 2)
			mid_addr = frm->addr.cr;
		अन्यथा
			वापस;

		f_chk_addr = low_addr;
		अगर (mid_addr + frm->payload[mid_plane] - low_addr >
		    high_addr + frm->payload[high_plane] - mid_addr) अणु
			f_chk_len = frm->payload[low_plane];
			s_chk_addr = mid_addr;
			s_chk_len = high_addr +
					frm->payload[high_plane] - mid_addr;
		पूर्ण अन्यथा अणु
			f_chk_len = mid_addr +
					frm->payload[mid_plane] - low_addr;
			s_chk_addr = high_addr;
			s_chk_len = frm->payload[high_plane];
		पूर्ण
	पूर्ण
	pr_debug("f_addr = 0x%08x, f_len = %d, s_addr = 0x%08x, s_len = %d\n",
			f_chk_addr, f_chk_len, s_chk_addr, s_chk_len);
पूर्ण

पूर्णांक gsc_try_fmt_mplane(काष्ठा gsc_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा gsc_dev *gsc = ctx->gsc_dev;
	काष्ठा gsc_variant *variant = gsc->variant;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp = &f->fmt.pix_mp;
	स्थिर काष्ठा gsc_fmt *fmt;
	u32 max_w, max_h, mod_x, mod_y;
	u32 min_w, min_h, पंचांगp_w, पंचांगp_h;
	पूर्णांक i;

	pr_debug("user put w: %d, h: %d", pix_mp->width, pix_mp->height);

	fmt = find_fmt(&pix_mp->pixelक्रमmat, शून्य, 0);
	अगर (!fmt) अणु
		pr_err("pixelformat format (0x%X) invalid\n",
						pix_mp->pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (pix_mp->field == V4L2_FIELD_ANY)
		pix_mp->field = V4L2_FIELD_NONE;
	अन्यथा अगर (pix_mp->field != V4L2_FIELD_NONE) अणु
		pr_debug("Not supported field order(%d)\n", pix_mp->field);
		वापस -EINVAL;
	पूर्ण

	max_w = variant->pix_max->target_rot_dis_w;
	max_h = variant->pix_max->target_rot_dis_h;

	mod_x = ffs(variant->pix_align->org_w) - 1;
	अगर (is_yuv420(fmt->color))
		mod_y = ffs(variant->pix_align->org_h) - 1;
	अन्यथा
		mod_y = ffs(variant->pix_align->org_h) - 2;

	अगर (V4L2_TYPE_IS_OUTPUT(f->type)) अणु
		min_w = variant->pix_min->org_w;
		min_h = variant->pix_min->org_h;
	पूर्ण अन्यथा अणु
		min_w = variant->pix_min->target_rot_dis_w;
		min_h = variant->pix_min->target_rot_dis_h;
		pix_mp->colorspace = ctx->out_colorspace;
	पूर्ण

	pr_debug("mod_x: %d, mod_y: %d, max_w: %d, max_h = %d",
			mod_x, mod_y, max_w, max_h);

	/* To check अगर image size is modअगरied to adjust parameter against
	   hardware abilities */
	पंचांगp_w = pix_mp->width;
	पंचांगp_h = pix_mp->height;

	v4l_bound_align_image(&pix_mp->width, min_w, max_w, mod_x,
		&pix_mp->height, min_h, max_h, mod_y, 0);
	अगर (पंचांगp_w != pix_mp->width || पंचांगp_h != pix_mp->height)
		pr_debug("Image size has been modified from %dx%d to %dx%d\n",
			 पंचांगp_w, पंचांगp_h, pix_mp->width, pix_mp->height);

	pix_mp->num_planes = fmt->num_planes;

	अगर (V4L2_TYPE_IS_OUTPUT(f->type))
		ctx->out_colorspace = pix_mp->colorspace;

	क्रम (i = 0; i < pix_mp->num_planes; ++i) अणु
		काष्ठा v4l2_plane_pix_क्रमmat *plane_fmt = &pix_mp->plane_fmt[i];
		u32 bpl = plane_fmt->bytesperline;

		अगर (fmt->num_comp == 1 && /* Packed */
		    (bpl == 0 || (bpl * 8 / fmt->depth[i]) < pix_mp->width))
			bpl = pix_mp->width * fmt->depth[i] / 8;

		अगर (fmt->num_comp > 1 && /* Planar */
		    (bpl == 0 || bpl < pix_mp->width))
			bpl = pix_mp->width;

		अगर (i != 0 && fmt->num_comp == 3)
			bpl /= 2;

		plane_fmt->bytesperline = bpl;
		plane_fmt->sizeimage = max(pix_mp->width * pix_mp->height *
					   fmt->depth[i] / 8,
					   plane_fmt->sizeimage);
		pr_debug("[%d]: bpl: %d, sizeimage: %d",
				i, bpl, pix_mp->plane_fmt[i].sizeimage);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gsc_g_fmt_mplane(काष्ठा gsc_ctx *ctx, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा gsc_frame *frame;
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp;
	पूर्णांक i;

	frame = ctx_get_frame(ctx, f->type);
	अगर (IS_ERR(frame))
		वापस PTR_ERR(frame);

	pix_mp = &f->fmt.pix_mp;

	pix_mp->width		= frame->f_width;
	pix_mp->height		= frame->f_height;
	pix_mp->field		= V4L2_FIELD_NONE;
	pix_mp->pixelक्रमmat	= frame->fmt->pixelक्रमmat;
	pix_mp->num_planes	= frame->fmt->num_planes;
	pix_mp->colorspace = ctx->out_colorspace;

	क्रम (i = 0; i < pix_mp->num_planes; ++i) अणु
		pix_mp->plane_fmt[i].bytesperline = (frame->f_width *
			frame->fmt->depth[i]) / 8;
		pix_mp->plane_fmt[i].sizeimage =
			 pix_mp->plane_fmt[i].bytesperline * frame->f_height;
	पूर्ण

	वापस 0;
पूर्ण

व्योम gsc_check_crop_change(u32 पंचांगp_w, u32 पंचांगp_h, u32 *w, u32 *h)
अणु
	अगर (पंचांगp_w != *w || पंचांगp_h != *h) अणु
		pr_info("Cropped size has been modified from %dx%d to %dx%d",
							*w, *h, पंचांगp_w, पंचांगp_h);
		*w = पंचांगp_w;
		*h = पंचांगp_h;
	पूर्ण
पूर्ण

पूर्णांक gsc_try_selection(काष्ठा gsc_ctx *ctx, काष्ठा v4l2_selection *s)
अणु
	काष्ठा gsc_frame *f;
	काष्ठा gsc_dev *gsc = ctx->gsc_dev;
	काष्ठा gsc_variant *variant = gsc->variant;
	u32 mod_x = 0, mod_y = 0, पंचांगp_w, पंचांगp_h;
	u32 min_w, min_h, max_w, max_h;

	अगर (s->r.top < 0 || s->r.left < 0) अणु
		pr_err("doesn't support negative values for top & left\n");
		वापस -EINVAL;
	पूर्ण
	pr_debug("user put w: %d, h: %d", s->r.width, s->r.height);

	अगर (s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		f = &ctx->d_frame;
	अन्यथा अगर (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		f = &ctx->s_frame;
	अन्यथा
		वापस -EINVAL;

	max_w = f->f_width;
	max_h = f->f_height;
	पंचांगp_w = s->r.width;
	पंचांगp_h = s->r.height;

	अगर (V4L2_TYPE_IS_OUTPUT(s->type)) अणु
		अगर ((is_yuv422(f->fmt->color) && f->fmt->num_comp == 1) ||
		    is_rgb(f->fmt->color))
			min_w = 32;
		अन्यथा
			min_w = 64;
		अगर ((is_yuv422(f->fmt->color) && f->fmt->num_comp == 3) ||
		    is_yuv420(f->fmt->color))
			min_h = 32;
		अन्यथा
			min_h = 16;
	पूर्ण अन्यथा अणु
		अगर (is_yuv420(f->fmt->color) || is_yuv422(f->fmt->color))
			mod_x = ffs(variant->pix_align->target_w) - 1;
		अगर (is_yuv420(f->fmt->color))
			mod_y = ffs(variant->pix_align->target_h) - 1;
		अगर (ctx->gsc_ctrls.rotate->val == 90 ||
		    ctx->gsc_ctrls.rotate->val == 270) अणु
			max_w = f->f_height;
			max_h = f->f_width;
			min_w = variant->pix_min->target_rot_en_w;
			min_h = variant->pix_min->target_rot_en_h;
			पंचांगp_w = s->r.height;
			पंचांगp_h = s->r.width;
		पूर्ण अन्यथा अणु
			min_w = variant->pix_min->target_rot_dis_w;
			min_h = variant->pix_min->target_rot_dis_h;
		पूर्ण
	पूर्ण
	pr_debug("mod_x: %d, mod_y: %d, min_w: %d, min_h = %d",
					mod_x, mod_y, min_w, min_h);
	pr_debug("tmp_w : %d, tmp_h : %d", पंचांगp_w, पंचांगp_h);

	v4l_bound_align_image(&पंचांगp_w, min_w, max_w, mod_x,
			      &पंचांगp_h, min_h, max_h, mod_y, 0);

	अगर (V4L2_TYPE_IS_CAPTURE(s->type) &&
	    (ctx->gsc_ctrls.rotate->val == 90 ||
	     ctx->gsc_ctrls.rotate->val == 270))
		gsc_check_crop_change(पंचांगp_h, पंचांगp_w,
					&s->r.width, &s->r.height);
	अन्यथा
		gsc_check_crop_change(पंचांगp_w, पंचांगp_h,
					&s->r.width, &s->r.height);


	/* adjust left/top अगर cropping rectangle is out of bounds */
	/* Need to add code to algin left value with 2's multiple */
	अगर (s->r.left + पंचांगp_w > max_w)
		s->r.left = max_w - पंचांगp_w;
	अगर (s->r.top + पंचांगp_h > max_h)
		s->r.top = max_h - पंचांगp_h;

	अगर ((is_yuv420(f->fmt->color) || is_yuv422(f->fmt->color)) &&
	    s->r.left & 1)
		s->r.left -= 1;

	pr_debug("Aligned l:%d, t:%d, w:%d, h:%d, f_w: %d, f_h: %d",
		 s->r.left, s->r.top, s->r.width, s->r.height, max_w, max_h);

	वापस 0;
पूर्ण

पूर्णांक gsc_check_scaler_ratio(काष्ठा gsc_variant *var, पूर्णांक sw, पूर्णांक sh, पूर्णांक dw,
			   पूर्णांक dh, पूर्णांक rot, पूर्णांक out_path)
अणु
	पूर्णांक पंचांगp_w, पंचांगp_h, sc_करोwn_max;

	अगर (out_path == GSC_DMA)
		sc_करोwn_max = var->sc_करोwn_max;
	अन्यथा
		sc_करोwn_max = var->local_sc_करोwn;

	अगर (rot == 90 || rot == 270) अणु
		पंचांगp_w = dh;
		पंचांगp_h = dw;
	पूर्ण अन्यथा अणु
		पंचांगp_w = dw;
		पंचांगp_h = dh;
	पूर्ण

	अगर ((sw / पंचांगp_w) > sc_करोwn_max ||
	    (sh / पंचांगp_h) > sc_करोwn_max ||
	    (पंचांगp_w / sw) > var->sc_up_max ||
	    (पंचांगp_h / sh) > var->sc_up_max)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक gsc_set_scaler_info(काष्ठा gsc_ctx *ctx)
अणु
	काष्ठा gsc_scaler *sc = &ctx->scaler;
	काष्ठा gsc_frame *s_frame = &ctx->s_frame;
	काष्ठा gsc_frame *d_frame = &ctx->d_frame;
	काष्ठा gsc_variant *variant = ctx->gsc_dev->variant;
	काष्ठा device *dev = &ctx->gsc_dev->pdev->dev;
	पूर्णांक tx, ty;
	पूर्णांक ret;

	ret = gsc_check_scaler_ratio(variant, s_frame->crop.width,
		s_frame->crop.height, d_frame->crop.width, d_frame->crop.height,
		ctx->gsc_ctrls.rotate->val, ctx->out_path);
	अगर (ret) अणु
		pr_err("out of scaler range");
		वापस ret;
	पूर्ण

	अगर (ctx->gsc_ctrls.rotate->val == 90 ||
	    ctx->gsc_ctrls.rotate->val == 270) अणु
		ty = d_frame->crop.width;
		tx = d_frame->crop.height;
	पूर्ण अन्यथा अणु
		tx = d_frame->crop.width;
		ty = d_frame->crop.height;
	पूर्ण

	अगर (tx <= 0 || ty <= 0) अणु
		dev_err(dev, "Invalid target size: %dx%d", tx, ty);
		वापस -EINVAL;
	पूर्ण

	ret = gsc_cal_prescaler_ratio(variant, s_frame->crop.width,
				      tx, &sc->pre_hratio);
	अगर (ret) अणु
		pr_err("Horizontal scale ratio is out of range");
		वापस ret;
	पूर्ण

	ret = gsc_cal_prescaler_ratio(variant, s_frame->crop.height,
				      ty, &sc->pre_vratio);
	अगर (ret) अणु
		pr_err("Vertical scale ratio is out of range");
		वापस ret;
	पूर्ण

	gsc_check_src_scale_info(variant, s_frame, &sc->pre_hratio,
				 tx, ty, &sc->pre_vratio);

	gsc_get_prescaler_shfactor(sc->pre_hratio, sc->pre_vratio,
				   &sc->pre_shfactor);

	sc->मुख्य_hratio = (s_frame->crop.width << 16) / tx;
	sc->मुख्य_vratio = (s_frame->crop.height << 16) / ty;

	pr_debug("scaler input/output size : sx = %d, sy = %d, tx = %d, ty = %d",
			s_frame->crop.width, s_frame->crop.height, tx, ty);
	pr_debug("scaler ratio info : pre_shfactor : %d, pre_h : %d",
			sc->pre_shfactor, sc->pre_hratio);
	pr_debug("pre_v :%d, main_h : %d, main_v : %d",
			sc->pre_vratio, sc->मुख्य_hratio, sc->मुख्य_vratio);

	वापस 0;
पूर्ण

अटल पूर्णांक __gsc_s_ctrl(काष्ठा gsc_ctx *ctx, काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gsc_dev *gsc = ctx->gsc_dev;
	काष्ठा gsc_variant *variant = gsc->variant;
	अचिन्हित पूर्णांक flags = GSC_DST_FMT | GSC_SRC_FMT;
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
		अगर ((ctx->state & flags) == flags) अणु
			ret = gsc_check_scaler_ratio(variant,
					ctx->s_frame.crop.width,
					ctx->s_frame.crop.height,
					ctx->d_frame.crop.width,
					ctx->d_frame.crop.height,
					ctx->gsc_ctrls.rotate->val,
					ctx->out_path);

			अगर (ret)
				वापस -EINVAL;
		पूर्ण

		ctx->rotation = ctrl->val;
		अवरोध;

	हाल V4L2_CID_ALPHA_COMPONENT:
		ctx->d_frame.alpha = ctrl->val;
		अवरोध;
	पूर्ण

	ctx->state |= GSC_PARAMS;
	वापस 0;
पूर्ण

अटल पूर्णांक gsc_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gsc_ctx *ctx = ctrl_to_ctx(ctrl);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ctx->gsc_dev->slock, flags);
	ret = __gsc_s_ctrl(ctx, ctrl);
	spin_unlock_irqrestore(&ctx->gsc_dev->slock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops gsc_ctrl_ops = अणु
	.s_ctrl = gsc_s_ctrl,
पूर्ण;

पूर्णांक gsc_ctrls_create(काष्ठा gsc_ctx *ctx)
अणु
	अगर (ctx->ctrls_rdy) अणु
		pr_err("Control handler of this context was created already");
		वापस 0;
	पूर्ण

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, GSC_MAX_CTRL_NUM);

	ctx->gsc_ctrls.rotate = v4l2_ctrl_new_std(&ctx->ctrl_handler,
				&gsc_ctrl_ops, V4L2_CID_ROTATE, 0, 270, 90, 0);
	ctx->gsc_ctrls.hflip = v4l2_ctrl_new_std(&ctx->ctrl_handler,
				&gsc_ctrl_ops, V4L2_CID_HFLIP, 0, 1, 1, 0);
	ctx->gsc_ctrls.vflip = v4l2_ctrl_new_std(&ctx->ctrl_handler,
				&gsc_ctrl_ops, V4L2_CID_VFLIP, 0, 1, 1, 0);
	ctx->gsc_ctrls.global_alpha = v4l2_ctrl_new_std(&ctx->ctrl_handler,
			&gsc_ctrl_ops, V4L2_CID_ALPHA_COMPONENT, 0, 255, 1, 0);

	ctx->ctrls_rdy = ctx->ctrl_handler.error == 0;

	अगर (ctx->ctrl_handler.error) अणु
		पूर्णांक err = ctx->ctrl_handler.error;
		v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
		pr_err("Failed to create G-Scaler control handlers");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम gsc_ctrls_delete(काष्ठा gsc_ctx *ctx)
अणु
	अगर (ctx->ctrls_rdy) अणु
		v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
		ctx->ctrls_rdy = false;
	पूर्ण
पूर्ण

/* The color क्रमmat (num_comp, num_planes) must be alपढ़ोy configured. */
पूर्णांक gsc_prepare_addr(काष्ठा gsc_ctx *ctx, काष्ठा vb2_buffer *vb,
			काष्ठा gsc_frame *frame, काष्ठा gsc_addr *addr)
अणु
	पूर्णांक ret = 0;
	u32 pix_size;

	अगर ((vb == शून्य) || (frame == शून्य))
		वापस -EINVAL;

	pix_size = frame->f_width * frame->f_height;

	pr_debug("num_planes= %d, num_comp= %d, pix_size= %d",
		frame->fmt->num_planes, frame->fmt->num_comp, pix_size);

	addr->y = vb2_dma_contig_plane_dma_addr(vb, 0);

	अगर (frame->fmt->num_planes == 1) अणु
		चयन (frame->fmt->num_comp) अणु
		हाल 1:
			addr->cb = 0;
			addr->cr = 0;
			अवरोध;
		हाल 2:
			/* decompose Y पूर्णांकo Y/Cb */
			addr->cb = (dma_addr_t)(addr->y + pix_size);
			addr->cr = 0;
			अवरोध;
		हाल 3:
			/* decompose Y पूर्णांकo Y/Cb/Cr */
			addr->cb = (dma_addr_t)(addr->y + pix_size);
			अगर (GSC_YUV420 == frame->fmt->color)
				addr->cr = (dma_addr_t)(addr->cb
						+ (pix_size >> 2));
			अन्यथा /* 422 */
				addr->cr = (dma_addr_t)(addr->cb
						+ (pix_size >> 1));
			अवरोध;
		शेष:
			pr_err("Invalid the number of color planes");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (frame->fmt->num_planes >= 2)
			addr->cb = vb2_dma_contig_plane_dma_addr(vb, 1);

		अगर (frame->fmt->num_planes == 3)
			addr->cr = vb2_dma_contig_plane_dma_addr(vb, 2);
	पूर्ण

	अगर ((frame->fmt->pixelक्रमmat == V4L2_PIX_FMT_VYUY) ||
		(frame->fmt->pixelक्रमmat == V4L2_PIX_FMT_YVYU) ||
		(frame->fmt->pixelक्रमmat == V4L2_PIX_FMT_YVU420) ||
		(frame->fmt->pixelक्रमmat == V4L2_PIX_FMT_YVU420M))
		swap(addr->cb, addr->cr);

	pr_debug("ADDR: y= %pad  cb= %pad cr= %pad ret= %d",
		&addr->y, &addr->cb, &addr->cr, ret);

	वापस ret;
पूर्ण

अटल irqवापस_t gsc_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा gsc_dev *gsc = priv;
	काष्ठा gsc_ctx *ctx;
	पूर्णांक gsc_irq;

	gsc_irq = gsc_hw_get_irq_status(gsc);
	gsc_hw_clear_irq(gsc, gsc_irq);

	अगर (gsc_irq == GSC_IRQ_OVERRUN) अणु
		pr_err("Local path input over-run interrupt has occurred!\n");
		वापस IRQ_HANDLED;
	पूर्ण

	spin_lock(&gsc->slock);

	अगर (test_and_clear_bit(ST_M2M_PEND, &gsc->state)) अणु

		gsc_hw_enable_control(gsc, false);

		अगर (test_and_clear_bit(ST_M2M_SUSPENDING, &gsc->state)) अणु
			set_bit(ST_M2M_SUSPENDED, &gsc->state);
			wake_up(&gsc->irq_queue);
			जाओ isr_unlock;
		पूर्ण
		ctx = v4l2_m2m_get_curr_priv(gsc->m2m.m2m_dev);

		अगर (!ctx || !ctx->m2m_ctx)
			जाओ isr_unlock;

		spin_unlock(&gsc->slock);
		gsc_m2m_job_finish(ctx, VB2_BUF_STATE_DONE);

		/* wake_up job_पात, stop_streaming */
		अगर (ctx->state & GSC_CTX_STOP_REQ) अणु
			ctx->state &= ~GSC_CTX_STOP_REQ;
			wake_up(&gsc->irq_queue);
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण

isr_unlock:
	spin_unlock(&gsc->slock);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा gsc_pix_max gsc_v_100_max = अणु
	.org_scaler_bypass_w	= 8192,
	.org_scaler_bypass_h	= 8192,
	.org_scaler_input_w	= 4800,
	.org_scaler_input_h	= 3344,
	.real_rot_dis_w		= 4800,
	.real_rot_dis_h		= 3344,
	.real_rot_en_w		= 2047,
	.real_rot_en_h		= 2047,
	.target_rot_dis_w	= 4800,
	.target_rot_dis_h	= 3344,
	.target_rot_en_w	= 2016,
	.target_rot_en_h	= 2016,
पूर्ण;

अटल काष्ठा gsc_pix_max gsc_v_5250_max = अणु
	.org_scaler_bypass_w	= 8192,
	.org_scaler_bypass_h	= 8192,
	.org_scaler_input_w	= 4800,
	.org_scaler_input_h	= 3344,
	.real_rot_dis_w		= 4800,
	.real_rot_dis_h		= 3344,
	.real_rot_en_w		= 2016,
	.real_rot_en_h		= 2016,
	.target_rot_dis_w	= 4800,
	.target_rot_dis_h	= 3344,
	.target_rot_en_w	= 2016,
	.target_rot_en_h	= 2016,
पूर्ण;

अटल काष्ठा gsc_pix_max gsc_v_5420_max = अणु
	.org_scaler_bypass_w	= 8192,
	.org_scaler_bypass_h	= 8192,
	.org_scaler_input_w	= 4800,
	.org_scaler_input_h	= 3344,
	.real_rot_dis_w		= 4800,
	.real_rot_dis_h		= 3344,
	.real_rot_en_w		= 2048,
	.real_rot_en_h		= 2048,
	.target_rot_dis_w	= 4800,
	.target_rot_dis_h	= 3344,
	.target_rot_en_w	= 2016,
	.target_rot_en_h	= 2016,
पूर्ण;

अटल काष्ठा gsc_pix_max gsc_v_5433_max = अणु
	.org_scaler_bypass_w	= 8192,
	.org_scaler_bypass_h	= 8192,
	.org_scaler_input_w	= 4800,
	.org_scaler_input_h	= 3344,
	.real_rot_dis_w		= 4800,
	.real_rot_dis_h		= 3344,
	.real_rot_en_w		= 2047,
	.real_rot_en_h		= 2047,
	.target_rot_dis_w	= 4800,
	.target_rot_dis_h	= 3344,
	.target_rot_en_w	= 2016,
	.target_rot_en_h	= 2016,
पूर्ण;

अटल काष्ठा gsc_pix_min gsc_v_100_min = अणु
	.org_w			= 64,
	.org_h			= 32,
	.real_w			= 64,
	.real_h			= 32,
	.target_rot_dis_w	= 64,
	.target_rot_dis_h	= 32,
	.target_rot_en_w	= 32,
	.target_rot_en_h	= 16,
पूर्ण;

अटल काष्ठा gsc_pix_align gsc_v_100_align = अणु
	.org_h			= 16,
	.org_w			= 16, /* yuv420 : 16, others : 8 */
	.offset_h		= 2,  /* yuv420/422 : 2, others : 1 */
	.real_w			= 16, /* yuv420/422 : 4~16, others : 2~8 */
	.real_h			= 16, /* yuv420 : 4~16, others : 1 */
	.target_w		= 2,  /* yuv420/422 : 2, others : 1 */
	.target_h		= 2,  /* yuv420 : 2, others : 1 */
पूर्ण;

अटल काष्ठा gsc_variant gsc_v_100_variant = अणु
	.pix_max		= &gsc_v_100_max,
	.pix_min		= &gsc_v_100_min,
	.pix_align		= &gsc_v_100_align,
	.in_buf_cnt		= 32,
	.out_buf_cnt		= 32,
	.sc_up_max		= 8,
	.sc_करोwn_max		= 16,
	.poly_sc_करोwn_max	= 4,
	.pre_sc_करोwn_max	= 4,
	.local_sc_करोwn		= 2,
पूर्ण;

अटल काष्ठा gsc_variant gsc_v_5250_variant = अणु
	.pix_max		= &gsc_v_5250_max,
	.pix_min		= &gsc_v_100_min,
	.pix_align		= &gsc_v_100_align,
	.in_buf_cnt		= 32,
	.out_buf_cnt		= 32,
	.sc_up_max		= 8,
	.sc_करोwn_max		= 16,
	.poly_sc_करोwn_max	= 4,
	.pre_sc_करोwn_max	= 4,
	.local_sc_करोwn		= 2,
पूर्ण;

अटल काष्ठा gsc_variant gsc_v_5420_variant = अणु
	.pix_max		= &gsc_v_5420_max,
	.pix_min		= &gsc_v_100_min,
	.pix_align		= &gsc_v_100_align,
	.in_buf_cnt		= 32,
	.out_buf_cnt		= 32,
	.sc_up_max		= 8,
	.sc_करोwn_max		= 16,
	.poly_sc_करोwn_max	= 4,
	.pre_sc_करोwn_max	= 4,
	.local_sc_करोwn		= 2,
पूर्ण;

अटल काष्ठा gsc_variant gsc_v_5433_variant = अणु
	.pix_max		= &gsc_v_5433_max,
	.pix_min		= &gsc_v_100_min,
	.pix_align		= &gsc_v_100_align,
	.in_buf_cnt		= 32,
	.out_buf_cnt		= 32,
	.sc_up_max		= 8,
	.sc_करोwn_max		= 16,
	.poly_sc_करोwn_max	= 4,
	.pre_sc_करोwn_max	= 4,
	.local_sc_करोwn		= 2,
पूर्ण;

अटल काष्ठा gsc_driverdata gsc_v_100_drvdata = अणु
	.variant = अणु
		[0] = &gsc_v_100_variant,
		[1] = &gsc_v_100_variant,
		[2] = &gsc_v_100_variant,
		[3] = &gsc_v_100_variant,
	पूर्ण,
	.num_entities = 4,
	.clk_names = अणु "gscl" पूर्ण,
	.num_घड़ीs = 1,
पूर्ण;

अटल काष्ठा gsc_driverdata gsc_v_5250_drvdata = अणु
	.variant = अणु
		[0] = &gsc_v_5250_variant,
		[1] = &gsc_v_5250_variant,
		[2] = &gsc_v_5250_variant,
		[3] = &gsc_v_5250_variant,
	पूर्ण,
	.num_entities = 4,
	.clk_names = अणु "gscl" पूर्ण,
	.num_घड़ीs = 1,
पूर्ण;

अटल काष्ठा gsc_driverdata gsc_v_5420_drvdata = अणु
	.variant = अणु
		[0] = &gsc_v_5420_variant,
		[1] = &gsc_v_5420_variant,
	पूर्ण,
	.num_entities = 2,
	.clk_names = अणु "gscl" पूर्ण,
	.num_घड़ीs = 1,
पूर्ण;

अटल काष्ठा gsc_driverdata gsc_5433_drvdata = अणु
	.variant = अणु
		[0] = &gsc_v_5433_variant,
		[1] = &gsc_v_5433_variant,
		[2] = &gsc_v_5433_variant,
	पूर्ण,
	.num_entities = 3,
	.clk_names = अणु "pclk", "aclk", "aclk_xiu", "aclk_gsclbend" पूर्ण,
	.num_घड़ीs = 4,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_gsc_match[] = अणु
	अणु
		.compatible = "samsung,exynos5250-gsc",
		.data = &gsc_v_5250_drvdata,
	पूर्ण,
	अणु
		.compatible = "samsung,exynos5420-gsc",
		.data = &gsc_v_5420_drvdata,
	पूर्ण,
	अणु
		.compatible = "samsung,exynos5433-gsc",
		.data = &gsc_5433_drvdata,
	पूर्ण,
	अणु
		.compatible = "samsung,exynos5-gsc",
		.data = &gsc_v_100_drvdata,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_gsc_match);

अटल पूर्णांक gsc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gsc_dev *gsc;
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा gsc_driverdata *drv_data = of_device_get_match_data(dev);
	पूर्णांक ret;
	पूर्णांक i;

	gsc = devm_kzalloc(dev, माप(काष्ठा gsc_dev), GFP_KERNEL);
	अगर (!gsc)
		वापस -ENOMEM;

	ret = of_alias_get_id(pdev->dev.of_node, "gsc");
	अगर (ret < 0)
		वापस ret;

	अगर (drv_data == &gsc_v_100_drvdata)
		dev_info(dev, "compatible 'exynos5-gsc' is deprecated\n");

	gsc->id = ret;
	अगर (gsc->id >= drv_data->num_entities) अणु
		dev_err(dev, "Invalid platform device id: %d\n", gsc->id);
		वापस -EINVAL;
	पूर्ण

	gsc->num_घड़ीs = drv_data->num_घड़ीs;
	gsc->variant = drv_data->variant[gsc->id];
	gsc->pdev = pdev;

	init_रुकोqueue_head(&gsc->irq_queue);
	spin_lock_init(&gsc->slock);
	mutex_init(&gsc->lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	gsc->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(gsc->regs))
		वापस PTR_ERR(gsc->regs);

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(dev, "failed to get IRQ resource\n");
		वापस -ENXIO;
	पूर्ण

	क्रम (i = 0; i < gsc->num_घड़ीs; i++) अणु
		gsc->घड़ी[i] = devm_clk_get(dev, drv_data->clk_names[i]);
		अगर (IS_ERR(gsc->घड़ी[i])) अणु
			dev_err(dev, "failed to get clock: %s\n",
				drv_data->clk_names[i]);
			वापस PTR_ERR(gsc->घड़ी[i]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < gsc->num_घड़ीs; i++) अणु
		ret = clk_prepare_enable(gsc->घड़ी[i]);
		अगर (ret) अणु
			dev_err(dev, "clock prepare failed for clock: %s\n",
				drv_data->clk_names[i]);
			जबतक (--i >= 0)
				clk_disable_unprepare(gsc->घड़ी[i]);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_request_irq(dev, res->start, gsc_irq_handler,
				0, pdev->name, gsc);
	अगर (ret) अणु
		dev_err(dev, "failed to install irq (%d)\n", ret);
		जाओ err_clk;
	पूर्ण

	ret = v4l2_device_रेजिस्टर(dev, &gsc->v4l2_dev);
	अगर (ret)
		जाओ err_clk;

	ret = gsc_रेजिस्टर_m2m_device(gsc);
	अगर (ret)
		जाओ err_v4l2;

	platक्रमm_set_drvdata(pdev, gsc);

	gsc_hw_set_sw_reset(gsc);
	gsc_रुको_reset(gsc);

	vb2_dma_contig_set_max_seg_size(dev, DMA_BIT_MASK(32));

	dev_dbg(dev, "gsc-%d registered successfully\n", gsc->id);

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	वापस 0;

err_v4l2:
	v4l2_device_unरेजिस्टर(&gsc->v4l2_dev);
err_clk:
	क्रम (i = gsc->num_घड़ीs - 1; i >= 0; i--)
		clk_disable_unprepare(gsc->घड़ी[i]);
	वापस ret;
पूर्ण

अटल पूर्णांक gsc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gsc_dev *gsc = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	pm_runसमय_get_sync(&pdev->dev);

	gsc_unरेजिस्टर_m2m_device(gsc);
	v4l2_device_unरेजिस्टर(&gsc->v4l2_dev);

	vb2_dma_contig_clear_max_seg_size(&pdev->dev);
	क्रम (i = 0; i < gsc->num_घड़ीs; i++)
		clk_disable_unprepare(gsc->घड़ी[i]);

	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	dev_dbg(&pdev->dev, "%s driver unloaded\n", pdev->name);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक gsc_m2m_suspend(काष्ठा gsc_dev *gsc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक समयout;

	spin_lock_irqsave(&gsc->slock, flags);
	अगर (!gsc_m2m_pending(gsc)) अणु
		spin_unlock_irqrestore(&gsc->slock, flags);
		वापस 0;
	पूर्ण
	clear_bit(ST_M2M_SUSPENDED, &gsc->state);
	set_bit(ST_M2M_SUSPENDING, &gsc->state);
	spin_unlock_irqrestore(&gsc->slock, flags);

	समयout = रुको_event_समयout(gsc->irq_queue,
			     test_bit(ST_M2M_SUSPENDED, &gsc->state),
			     GSC_SHUTDOWN_TIMEOUT);

	clear_bit(ST_M2M_SUSPENDING, &gsc->state);
	वापस समयout == 0 ? -EAGAIN : 0;
पूर्ण

अटल व्योम gsc_m2m_resume(काष्ठा gsc_dev *gsc)
अणु
	काष्ठा gsc_ctx *ctx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gsc->slock, flags);
	/* Clear क्रम full H/W setup in first run after resume */
	ctx = gsc->m2m.ctx;
	gsc->m2m.ctx = शून्य;
	spin_unlock_irqrestore(&gsc->slock, flags);

	अगर (test_and_clear_bit(ST_M2M_SUSPENDED, &gsc->state))
		gsc_m2m_job_finish(ctx, VB2_BUF_STATE_ERROR);
पूर्ण

अटल पूर्णांक gsc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा gsc_dev *gsc = dev_get_drvdata(dev);
	पूर्णांक ret = 0;
	पूर्णांक i;

	pr_debug("gsc%d: state: 0x%lx\n", gsc->id, gsc->state);

	क्रम (i = 0; i < gsc->num_घड़ीs; i++) अणु
		ret = clk_prepare_enable(gsc->घड़ी[i]);
		अगर (ret) अणु
			जबतक (--i >= 0)
				clk_disable_unprepare(gsc->घड़ी[i]);
			वापस ret;
		पूर्ण
	पूर्ण

	gsc_hw_set_sw_reset(gsc);
	gsc_रुको_reset(gsc);
	gsc_m2m_resume(gsc);

	वापस 0;
पूर्ण

अटल पूर्णांक gsc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा gsc_dev *gsc = dev_get_drvdata(dev);
	पूर्णांक ret = 0;
	पूर्णांक i;

	ret = gsc_m2m_suspend(gsc);
	अगर (ret)
		वापस ret;

	क्रम (i = gsc->num_घड़ीs - 1; i >= 0; i--)
		clk_disable_unprepare(gsc->घड़ी[i]);

	pr_debug("gsc%d: state: 0x%lx\n", gsc->id, gsc->state);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops gsc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(gsc_runसमय_suspend, gsc_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver gsc_driver = अणु
	.probe		= gsc_probe,
	.हटाओ		= gsc_हटाओ,
	.driver = अणु
		.name	= GSC_MODULE_NAME,
		.pm	= &gsc_pm_ops,
		.of_match_table = exynos_gsc_match,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(gsc_driver);

MODULE_AUTHOR("Hyunwong Kim <khw0178.kim@samsung.com>");
MODULE_DESCRIPTION("Samsung EXYNOS5 Soc series G-Scaler driver");
MODULE_LICENSE("GPL");
