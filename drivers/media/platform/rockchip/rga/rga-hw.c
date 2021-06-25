<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author: Jacob Chen <jacob-chen@iotwrt.com>
 */

#समावेश <linux/pm_runसमय.स>

#समावेश "rga-hw.h"
#समावेश "rga.h"

क्रमागत e_rga_start_pos अणु
	LT = 0,
	LB = 1,
	RT = 2,
	RB = 3,
पूर्ण;

काष्ठा rga_addr_offset अणु
	अचिन्हित पूर्णांक y_off;
	अचिन्हित पूर्णांक u_off;
	अचिन्हित पूर्णांक v_off;
पूर्ण;

काष्ठा rga_corners_addr_offset अणु
	काष्ठा rga_addr_offset left_top;
	काष्ठा rga_addr_offset right_top;
	काष्ठा rga_addr_offset left_bottom;
	काष्ठा rga_addr_offset right_bottom;
पूर्ण;

अटल अचिन्हित पूर्णांक rga_get_scaling(अचिन्हित पूर्णांक src, अचिन्हित पूर्णांक dst)
अणु
	/*
	 * The rga hw scaling factor is a normalized inverse of the
	 * scaling factor.
	 * For example: When source width is 100 and destination width is 200
	 * (scaling of 2x), then the hw factor is NC * 100 / 200.
	 * The normalization factor (NC) is 2^16 = 0x10000.
	 */

	वापस (src > dst) ? ((dst << 16) / src) : ((src << 16) / dst);
पूर्ण

अटल काष्ठा rga_corners_addr_offset
rga_get_addr_offset(काष्ठा rga_frame *frm, अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y,
		    अचिन्हित पूर्णांक w, अचिन्हित पूर्णांक h)
अणु
	काष्ठा rga_corners_addr_offset offsets;
	काष्ठा rga_addr_offset *lt, *lb, *rt, *rb;
	अचिन्हित पूर्णांक x_भाग = 0,
		     y_भाग = 0, uv_stride = 0, pixel_width = 0, uv_factor = 0;

	lt = &offsets.left_top;
	lb = &offsets.left_bottom;
	rt = &offsets.right_top;
	rb = &offsets.right_bottom;

	x_भाग = frm->fmt->x_भाग;
	y_भाग = frm->fmt->y_भाग;
	uv_factor = frm->fmt->uv_factor;
	uv_stride = frm->stride / x_भाग;
	pixel_width = frm->stride / frm->width;

	lt->y_off = y * frm->stride + x * pixel_width;
	lt->u_off =
		frm->width * frm->height + (y / y_भाग) * uv_stride + x / x_भाग;
	lt->v_off = lt->u_off + frm->width * frm->height / uv_factor;

	lb->y_off = lt->y_off + (h - 1) * frm->stride;
	lb->u_off = lt->u_off + (h / y_भाग - 1) * uv_stride;
	lb->v_off = lt->v_off + (h / y_भाग - 1) * uv_stride;

	rt->y_off = lt->y_off + (w - 1) * pixel_width;
	rt->u_off = lt->u_off + w / x_भाग - 1;
	rt->v_off = lt->v_off + w / x_भाग - 1;

	rb->y_off = lb->y_off + (w - 1) * pixel_width;
	rb->u_off = lb->u_off + w / x_भाग - 1;
	rb->v_off = lb->v_off + w / x_भाग - 1;

	वापस offsets;
पूर्ण

अटल काष्ठा rga_addr_offset *rga_lookup_draw_pos(काष्ठा
		rga_corners_addr_offset
		* offsets, u32 rotate_mode,
		u32 mirr_mode)
अणु
	अटल क्रमागत e_rga_start_pos rot_mir_poपूर्णांक_matrix[4][4] = अणु
		अणु
			LT, RT, LB, RB,
		पूर्ण,
		अणु
			RT, LT, RB, LB,
		पूर्ण,
		अणु
			RB, LB, RT, LT,
		पूर्ण,
		अणु
			LB, RB, LT, RT,
		पूर्ण,
	पूर्ण;

	अगर (!offsets)
		वापस शून्य;

	चयन (rot_mir_poपूर्णांक_matrix[rotate_mode][mirr_mode]) अणु
	हाल LT:
		वापस &offsets->left_top;
	हाल LB:
		वापस &offsets->left_bottom;
	हाल RT:
		वापस &offsets->right_top;
	हाल RB:
		वापस &offsets->right_bottom;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम rga_cmd_set_src_addr(काष्ठा rga_ctx *ctx, व्योम *mmu_pages)
अणु
	काष्ठा rockchip_rga *rga = ctx->rga;
	u32 *dest = rga->cmdbuf_virt;
	अचिन्हित पूर्णांक reg;

	reg = RGA_MMU_SRC_BASE - RGA_MODE_BASE_REG;
	dest[reg >> 2] = virt_to_phys(mmu_pages) >> 4;

	reg = RGA_MMU_CTRL1 - RGA_MODE_BASE_REG;
	dest[reg >> 2] |= 0x7;
पूर्ण

अटल व्योम rga_cmd_set_src1_addr(काष्ठा rga_ctx *ctx, व्योम *mmu_pages)
अणु
	काष्ठा rockchip_rga *rga = ctx->rga;
	u32 *dest = rga->cmdbuf_virt;
	अचिन्हित पूर्णांक reg;

	reg = RGA_MMU_SRC1_BASE - RGA_MODE_BASE_REG;
	dest[reg >> 2] = virt_to_phys(mmu_pages) >> 4;

	reg = RGA_MMU_CTRL1 - RGA_MODE_BASE_REG;
	dest[reg >> 2] |= 0x7 << 4;
पूर्ण

अटल व्योम rga_cmd_set_dst_addr(काष्ठा rga_ctx *ctx, व्योम *mmu_pages)
अणु
	काष्ठा rockchip_rga *rga = ctx->rga;
	u32 *dest = rga->cmdbuf_virt;
	अचिन्हित पूर्णांक reg;

	reg = RGA_MMU_DST_BASE - RGA_MODE_BASE_REG;
	dest[reg >> 2] = virt_to_phys(mmu_pages) >> 4;

	reg = RGA_MMU_CTRL1 - RGA_MODE_BASE_REG;
	dest[reg >> 2] |= 0x7 << 8;
पूर्ण

अटल व्योम rga_cmd_set_trans_info(काष्ठा rga_ctx *ctx)
अणु
	काष्ठा rockchip_rga *rga = ctx->rga;
	u32 *dest = rga->cmdbuf_virt;
	अचिन्हित पूर्णांक scale_dst_w, scale_dst_h;
	अचिन्हित पूर्णांक src_h, src_w, src_x, src_y, dst_h, dst_w, dst_x, dst_y;
	जोड़ rga_src_info src_info;
	जोड़ rga_dst_info dst_info;
	जोड़ rga_src_x_factor x_factor;
	जोड़ rga_src_y_factor y_factor;
	जोड़ rga_src_vir_info src_vir_info;
	जोड़ rga_src_act_info src_act_info;
	जोड़ rga_dst_vir_info dst_vir_info;
	जोड़ rga_dst_act_info dst_act_info;

	काष्ठा rga_addr_offset *dst_offset;
	काष्ठा rga_corners_addr_offset offsets;
	काष्ठा rga_corners_addr_offset src_offsets;

	src_h = ctx->in.crop.height;
	src_w = ctx->in.crop.width;
	src_x = ctx->in.crop.left;
	src_y = ctx->in.crop.top;
	dst_h = ctx->out.crop.height;
	dst_w = ctx->out.crop.width;
	dst_x = ctx->out.crop.left;
	dst_y = ctx->out.crop.top;

	src_info.val = dest[(RGA_SRC_INFO - RGA_MODE_BASE_REG) >> 2];
	dst_info.val = dest[(RGA_DST_INFO - RGA_MODE_BASE_REG) >> 2];
	x_factor.val = dest[(RGA_SRC_X_FACTOR - RGA_MODE_BASE_REG) >> 2];
	y_factor.val = dest[(RGA_SRC_Y_FACTOR - RGA_MODE_BASE_REG) >> 2];
	src_vir_info.val = dest[(RGA_SRC_VIR_INFO - RGA_MODE_BASE_REG) >> 2];
	src_act_info.val = dest[(RGA_SRC_ACT_INFO - RGA_MODE_BASE_REG) >> 2];
	dst_vir_info.val = dest[(RGA_DST_VIR_INFO - RGA_MODE_BASE_REG) >> 2];
	dst_act_info.val = dest[(RGA_DST_ACT_INFO - RGA_MODE_BASE_REG) >> 2];

	src_info.data.क्रमmat = ctx->in.fmt->hw_क्रमmat;
	src_info.data.swap = ctx->in.fmt->color_swap;
	dst_info.data.क्रमmat = ctx->out.fmt->hw_क्रमmat;
	dst_info.data.swap = ctx->out.fmt->color_swap;

	/*
	 * CSC mode must only be set when the colorspace families dअगरfer between
	 * input and output. It must reमुख्य unset (zeroed) अगर both are the same.
	 */

	अगर (RGA_COLOR_FMT_IS_YUV(ctx->in.fmt->hw_क्रमmat) &&
	    RGA_COLOR_FMT_IS_RGB(ctx->out.fmt->hw_क्रमmat)) अणु
		चयन (ctx->in.colorspace) अणु
		हाल V4L2_COLORSPACE_REC709:
			src_info.data.csc_mode = RGA_SRC_CSC_MODE_BT709_R0;
			अवरोध;
		शेष:
			src_info.data.csc_mode = RGA_SRC_CSC_MODE_BT601_R0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (RGA_COLOR_FMT_IS_RGB(ctx->in.fmt->hw_क्रमmat) &&
	    RGA_COLOR_FMT_IS_YUV(ctx->out.fmt->hw_क्रमmat)) अणु
		चयन (ctx->out.colorspace) अणु
		हाल V4L2_COLORSPACE_REC709:
			dst_info.data.csc_mode = RGA_SRC_CSC_MODE_BT709_R0;
			अवरोध;
		शेष:
			dst_info.data.csc_mode = RGA_DST_CSC_MODE_BT601_R0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ctx->vflip)
		src_info.data.mir_mode |= RGA_SRC_MIRR_MODE_X;

	अगर (ctx->hflip)
		src_info.data.mir_mode |= RGA_SRC_MIRR_MODE_Y;

	चयन (ctx->rotate) अणु
	हाल 90:
		src_info.data.rot_mode = RGA_SRC_ROT_MODE_90_DEGREE;
		अवरोध;
	हाल 180:
		src_info.data.rot_mode = RGA_SRC_ROT_MODE_180_DEGREE;
		अवरोध;
	हाल 270:
		src_info.data.rot_mode = RGA_SRC_ROT_MODE_270_DEGREE;
		अवरोध;
	शेष:
		src_info.data.rot_mode = RGA_SRC_ROT_MODE_0_DEGREE;
		अवरोध;
	पूर्ण

	/*
	 * Calculate the up/करोwn scaling mode/factor.
	 *
	 * RGA used to scale the picture first, and then rotate second,
	 * so we need to swap the w/h when rotate degree is 90/270.
	 */
	अगर (src_info.data.rot_mode == RGA_SRC_ROT_MODE_90_DEGREE ||
	    src_info.data.rot_mode == RGA_SRC_ROT_MODE_270_DEGREE) अणु
		अगर (rga->version.major == 0 || rga->version.minor == 0) अणु
			अगर (dst_w == src_h)
				src_h -= 8;
			अगर (असल(src_w - dst_h) < 16)
				src_w -= 16;
		पूर्ण

		scale_dst_h = dst_w;
		scale_dst_w = dst_h;
	पूर्ण अन्यथा अणु
		scale_dst_w = dst_w;
		scale_dst_h = dst_h;
	पूर्ण

	अगर (src_w == scale_dst_w) अणु
		src_info.data.hscl_mode = RGA_SRC_HSCL_MODE_NO;
		x_factor.val = 0;
	पूर्ण अन्यथा अगर (src_w > scale_dst_w) अणु
		src_info.data.hscl_mode = RGA_SRC_HSCL_MODE_DOWN;
		x_factor.data.करोwn_scale_factor =
			rga_get_scaling(src_w, scale_dst_w) + 1;
	पूर्ण अन्यथा अणु
		src_info.data.hscl_mode = RGA_SRC_HSCL_MODE_UP;
		x_factor.data.up_scale_factor =
			rga_get_scaling(src_w - 1, scale_dst_w - 1);
	पूर्ण

	अगर (src_h == scale_dst_h) अणु
		src_info.data.vscl_mode = RGA_SRC_VSCL_MODE_NO;
		y_factor.val = 0;
	पूर्ण अन्यथा अगर (src_h > scale_dst_h) अणु
		src_info.data.vscl_mode = RGA_SRC_VSCL_MODE_DOWN;
		y_factor.data.करोwn_scale_factor =
			rga_get_scaling(src_h, scale_dst_h) + 1;
	पूर्ण अन्यथा अणु
		src_info.data.vscl_mode = RGA_SRC_VSCL_MODE_UP;
		y_factor.data.up_scale_factor =
			rga_get_scaling(src_h - 1, scale_dst_h - 1);
	पूर्ण

	/*
	 * Calculate the framebuffer भव strides and active size,
	 * note that the step of vir_stride / vir_width is 4 byte words
	 */
	src_vir_info.data.vir_stride = ctx->in.stride >> 2;
	src_vir_info.data.vir_width = ctx->in.stride >> 2;

	src_act_info.data.act_height = src_h - 1;
	src_act_info.data.act_width = src_w - 1;

	dst_vir_info.data.vir_stride = ctx->out.stride >> 2;
	dst_act_info.data.act_height = dst_h - 1;
	dst_act_info.data.act_width = dst_w - 1;

	/*
	 * Calculate the source framebuffer base address with offset pixel.
	 */
	src_offsets = rga_get_addr_offset(&ctx->in, src_x, src_y,
					  src_w, src_h);

	/*
	 * Configure the dest framebuffer base address with pixel offset.
	 */
	offsets = rga_get_addr_offset(&ctx->out, dst_x, dst_y, dst_w, dst_h);
	dst_offset = rga_lookup_draw_pos(&offsets, src_info.data.rot_mode,
					 src_info.data.mir_mode);

	dest[(RGA_SRC_Y_RGB_BASE_ADDR - RGA_MODE_BASE_REG) >> 2] =
		src_offsets.left_top.y_off;
	dest[(RGA_SRC_CB_BASE_ADDR - RGA_MODE_BASE_REG) >> 2] =
		src_offsets.left_top.u_off;
	dest[(RGA_SRC_CR_BASE_ADDR - RGA_MODE_BASE_REG) >> 2] =
		src_offsets.left_top.v_off;

	dest[(RGA_SRC_X_FACTOR - RGA_MODE_BASE_REG) >> 2] = x_factor.val;
	dest[(RGA_SRC_Y_FACTOR - RGA_MODE_BASE_REG) >> 2] = y_factor.val;
	dest[(RGA_SRC_VIR_INFO - RGA_MODE_BASE_REG) >> 2] = src_vir_info.val;
	dest[(RGA_SRC_ACT_INFO - RGA_MODE_BASE_REG) >> 2] = src_act_info.val;

	dest[(RGA_SRC_INFO - RGA_MODE_BASE_REG) >> 2] = src_info.val;

	dest[(RGA_DST_Y_RGB_BASE_ADDR - RGA_MODE_BASE_REG) >> 2] =
		dst_offset->y_off;
	dest[(RGA_DST_CB_BASE_ADDR - RGA_MODE_BASE_REG) >> 2] =
		dst_offset->u_off;
	dest[(RGA_DST_CR_BASE_ADDR - RGA_MODE_BASE_REG) >> 2] =
		dst_offset->v_off;

	dest[(RGA_DST_VIR_INFO - RGA_MODE_BASE_REG) >> 2] = dst_vir_info.val;
	dest[(RGA_DST_ACT_INFO - RGA_MODE_BASE_REG) >> 2] = dst_act_info.val;

	dest[(RGA_DST_INFO - RGA_MODE_BASE_REG) >> 2] = dst_info.val;
पूर्ण

अटल व्योम rga_cmd_set_mode(काष्ठा rga_ctx *ctx)
अणु
	काष्ठा rockchip_rga *rga = ctx->rga;
	u32 *dest = rga->cmdbuf_virt;
	जोड़ rga_mode_ctrl mode;
	जोड़ rga_alpha_ctrl0 alpha_ctrl0;
	जोड़ rga_alpha_ctrl1 alpha_ctrl1;

	mode.val = 0;
	alpha_ctrl0.val = 0;
	alpha_ctrl1.val = 0;

	mode.data.gradient_sat = 1;
	mode.data.render = RGA_MODE_RENDER_BITBLT;
	mode.data.bitblt = RGA_MODE_BITBLT_MODE_SRC_TO_DST;

	/* disable alpha blending */
	dest[(RGA_ALPHA_CTRL0 - RGA_MODE_BASE_REG) >> 2] = alpha_ctrl0.val;
	dest[(RGA_ALPHA_CTRL1 - RGA_MODE_BASE_REG) >> 2] = alpha_ctrl1.val;

	dest[(RGA_MODE_CTRL - RGA_MODE_BASE_REG) >> 2] = mode.val;
पूर्ण

अटल व्योम rga_cmd_set(काष्ठा rga_ctx *ctx)
अणु
	काष्ठा rockchip_rga *rga = ctx->rga;

	स_रखो(rga->cmdbuf_virt, 0, RGA_CMDBUF_SIZE * 4);

	rga_cmd_set_src_addr(ctx, rga->src_mmu_pages);
	/*
	 * Due to hardware bug,
	 * src1 mmu also should be configured when using alpha blending.
	 */
	rga_cmd_set_src1_addr(ctx, rga->dst_mmu_pages);

	rga_cmd_set_dst_addr(ctx, rga->dst_mmu_pages);
	rga_cmd_set_mode(ctx);

	rga_cmd_set_trans_info(ctx);

	rga_ग_लिखो(rga, RGA_CMD_BASE, rga->cmdbuf_phy);

	/* sync CMD buf क्रम RGA */
	dma_sync_single_क्रम_device(rga->dev, rga->cmdbuf_phy,
		PAGE_SIZE, DMA_BIसूचीECTIONAL);
पूर्ण

व्योम rga_hw_start(काष्ठा rockchip_rga *rga)
अणु
	काष्ठा rga_ctx *ctx = rga->curr;

	rga_cmd_set(ctx);

	rga_ग_लिखो(rga, RGA_SYS_CTRL, 0x00);

	rga_ग_लिखो(rga, RGA_SYS_CTRL, 0x22);

	rga_ग_लिखो(rga, RGA_INT, 0x600);

	rga_ग_लिखो(rga, RGA_CMD_CTRL, 0x1);
पूर्ण
