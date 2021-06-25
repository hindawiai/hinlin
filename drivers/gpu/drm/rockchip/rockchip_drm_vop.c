<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:Mark Yao <mark.yao@rock-chips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/delay.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/overflow.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_flip_work.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_self_refresh_helper.h>
#समावेश <drm/drm_vblank.h>

#अगर_घोषित CONFIG_DRM_ANALOGIX_DP
#समावेश <drm/bridge/analogix_dp.h>
#पूर्ण_अगर

#समावेश "rockchip_drm_drv.h"
#समावेश "rockchip_drm_gem.h"
#समावेश "rockchip_drm_fb.h"
#समावेश "rockchip_drm_vop.h"
#समावेश "rockchip_rgb.h"

#घोषणा VOP_WIN_SET(vop, win, name, v) \
		vop_reg_set(vop, &win->phy->name, win->base, ~0, v, #name)
#घोषणा VOP_SCL_SET(vop, win, name, v) \
		vop_reg_set(vop, &win->phy->scl->name, win->base, ~0, v, #name)
#घोषणा VOP_SCL_SET_EXT(vop, win, name, v) \
		vop_reg_set(vop, &win->phy->scl->ext->name, \
			    win->base, ~0, v, #name)

#घोषणा VOP_WIN_YUV2YUV_SET(vop, win_yuv2yuv, name, v) \
	करो अणु \
		अगर (win_yuv2yuv && win_yuv2yuv->name.mask) \
			vop_reg_set(vop, &win_yuv2yuv->name, 0, ~0, v, #name); \
	पूर्ण जबतक (0)

#घोषणा VOP_WIN_YUV2YUV_COEFFICIENT_SET(vop, win_yuv2yuv, name, v) \
	करो अणु \
		अगर (win_yuv2yuv && win_yuv2yuv->phy->name.mask) \
			vop_reg_set(vop, &win_yuv2yuv->phy->name, win_yuv2yuv->base, ~0, v, #name); \
	पूर्ण जबतक (0)

#घोषणा VOP_INTR_SET_MASK(vop, name, mask, v) \
		vop_reg_set(vop, &vop->data->पूर्णांकr->name, 0, mask, v, #name)

#घोषणा VOP_REG_SET(vop, group, name, v) \
		    vop_reg_set(vop, &vop->data->group->name, 0, ~0, v, #name)

#घोषणा VOP_INTR_SET_TYPE(vop, name, type, v) \
	करो अणु \
		पूर्णांक i, reg = 0, mask = 0; \
		क्रम (i = 0; i < vop->data->पूर्णांकr->nपूर्णांकrs; i++) अणु \
			अगर (vop->data->पूर्णांकr->पूर्णांकrs[i] & type) अणु \
				reg |= (v) << i; \
				mask |= 1 << i; \
			पूर्ण \
		पूर्ण \
		VOP_INTR_SET_MASK(vop, name, mask, reg); \
	पूर्ण जबतक (0)
#घोषणा VOP_INTR_GET_TYPE(vop, name, type) \
		vop_get_पूर्णांकr_type(vop, &vop->data->पूर्णांकr->name, type)

#घोषणा VOP_WIN_GET(vop, win, name) \
		vop_पढ़ो_reg(vop, win->base, &win->phy->name)

#घोषणा VOP_WIN_HAS_REG(win, name) \
	(!!(win->phy->name.mask))

#घोषणा VOP_WIN_GET_YRGBADDR(vop, win) \
		vop_पढ़ोl(vop, win->base + win->phy->yrgb_mst.offset)

#घोषणा VOP_WIN_TO_INDEX(vop_win) \
	((vop_win) - (vop_win)->vop->win)

#घोषणा VOP_AFBC_SET(vop, name, v) \
	करो अणु \
		अगर ((vop)->data->afbc) \
			vop_reg_set((vop), &(vop)->data->afbc->name, \
				    0, ~0, v, #name); \
	पूर्ण जबतक (0)

#घोषणा to_vop(x) container_of(x, काष्ठा vop, crtc)
#घोषणा to_vop_win(x) container_of(x, काष्ठा vop_win, base)

#घोषणा AFBC_FMT_RGB565		0x0
#घोषणा AFBC_FMT_U8U8U8U8	0x5
#घोषणा AFBC_FMT_U8U8U8		0x4

#घोषणा AFBC_TILE_16x16		BIT(4)

/*
 * The coefficients of the following matrix are all fixed poपूर्णांकs.
 * The क्रमmat is S2.10 क्रम the 3x3 part of the matrix, and S9.12 क्रम the offsets.
 * They are all represented in two's complement.
 */
अटल स्थिर uपूर्णांक32_t bt601_yuv2rgb[] = अणु
	0x4A8, 0x0,    0x662,
	0x4A8, 0x1E6F, 0x1CBF,
	0x4A8, 0x812,  0x0,
	0x321168, 0x0877CF, 0x2EB127
पूर्ण;

क्रमागत vop_pending अणु
	VOP_PENDING_FB_UNREF,
पूर्ण;

काष्ठा vop_win अणु
	काष्ठा drm_plane base;
	स्थिर काष्ठा vop_win_data *data;
	स्थिर काष्ठा vop_win_yuv2yuv_data *yuv2yuv_data;
	काष्ठा vop *vop;
पूर्ण;

काष्ठा rockchip_rgb;
काष्ठा vop अणु
	काष्ठा drm_crtc crtc;
	काष्ठा device *dev;
	काष्ठा drm_device *drm_dev;
	bool is_enabled;

	काष्ठा completion dsp_hold_completion;
	अचिन्हित पूर्णांक win_enabled;

	/* रक्षित by dev->event_lock */
	काष्ठा drm_pending_vblank_event *event;

	काष्ठा drm_flip_work fb_unref_work;
	अचिन्हित दीर्घ pending;

	काष्ठा completion line_flag_completion;

	स्थिर काष्ठा vop_data *data;

	uपूर्णांक32_t *regsbak;
	व्योम __iomem *regs;
	व्योम __iomem *lut_regs;

	/* physical map length of vop रेजिस्टर */
	uपूर्णांक32_t len;

	/* one समय only one process allowed to config the रेजिस्टर */
	spinlock_t reg_lock;
	/* lock vop irq reg */
	spinlock_t irq_lock;
	/* protects crtc enable/disable */
	काष्ठा mutex vop_lock;

	अचिन्हित पूर्णांक irq;

	/* vop AHP clk */
	काष्ठा clk *hclk;
	/* vop dclk */
	काष्ठा clk *dclk;
	/* vop share memory frequency */
	काष्ठा clk *aclk;

	/* vop dclk reset */
	काष्ठा reset_control *dclk_rst;

	/* optional पूर्णांकernal rgb encoder */
	काष्ठा rockchip_rgb *rgb;

	काष्ठा vop_win win[];
पूर्ण;

अटल अंतरभूत व्योम vop_ग_लिखोl(काष्ठा vop *vop, uपूर्णांक32_t offset, uपूर्णांक32_t v)
अणु
	ग_लिखोl(v, vop->regs + offset);
	vop->regsbak[offset >> 2] = v;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t vop_पढ़ोl(काष्ठा vop *vop, uपूर्णांक32_t offset)
अणु
	वापस पढ़ोl(vop->regs + offset);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t vop_पढ़ो_reg(काष्ठा vop *vop, uपूर्णांक32_t base,
				    स्थिर काष्ठा vop_reg *reg)
अणु
	वापस (vop_पढ़ोl(vop, base + reg->offset) >> reg->shअगरt) & reg->mask;
पूर्ण

अटल व्योम vop_reg_set(काष्ठा vop *vop, स्थिर काष्ठा vop_reg *reg,
			uपूर्णांक32_t _offset, uपूर्णांक32_t _mask, uपूर्णांक32_t v,
			स्थिर अक्षर *reg_name)
अणु
	पूर्णांक offset, mask, shअगरt;

	अगर (!reg || !reg->mask) अणु
		DRM_DEV_DEBUG(vop->dev, "Warning: not support %s\n", reg_name);
		वापस;
	पूर्ण

	offset = reg->offset + _offset;
	mask = reg->mask & _mask;
	shअगरt = reg->shअगरt;

	अगर (reg->ग_लिखो_mask) अणु
		v = ((v << shअगरt) & 0xffff) | (mask << (shअगरt + 16));
	पूर्ण अन्यथा अणु
		uपूर्णांक32_t cached_val = vop->regsbak[offset >> 2];

		v = (cached_val & ~(mask << shअगरt)) | ((v & mask) << shअगरt);
		vop->regsbak[offset >> 2] = v;
	पूर्ण

	अगर (reg->relaxed)
		ग_लिखोl_relaxed(v, vop->regs + offset);
	अन्यथा
		ग_लिखोl(v, vop->regs + offset);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t vop_get_पूर्णांकr_type(काष्ठा vop *vop,
					 स्थिर काष्ठा vop_reg *reg, पूर्णांक type)
अणु
	uपूर्णांक32_t i, ret = 0;
	uपूर्णांक32_t regs = vop_पढ़ो_reg(vop, 0, reg);

	क्रम (i = 0; i < vop->data->पूर्णांकr->nपूर्णांकrs; i++) अणु
		अगर ((type & vop->data->पूर्णांकr->पूर्णांकrs[i]) && (regs & 1 << i))
			ret |= vop->data->पूर्णांकr->पूर्णांकrs[i];
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम vop_cfg_करोne(काष्ठा vop *vop)
अणु
	VOP_REG_SET(vop, common, cfg_करोne, 1);
पूर्ण

अटल bool has_rb_swapped(uपूर्णांक32_t क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ABGR8888:
	हाल DRM_FORMAT_BGR888:
	हाल DRM_FORMAT_BGR565:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल क्रमागत vop_data_क्रमmat vop_convert_क्रमmat(uपूर्णांक32_t क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ABGR8888:
		वापस VOP_FMT_ARGB8888;
	हाल DRM_FORMAT_RGB888:
	हाल DRM_FORMAT_BGR888:
		वापस VOP_FMT_RGB888;
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_BGR565:
		वापस VOP_FMT_RGB565;
	हाल DRM_FORMAT_NV12:
		वापस VOP_FMT_YUV420SP;
	हाल DRM_FORMAT_NV16:
		वापस VOP_FMT_YUV422SP;
	हाल DRM_FORMAT_NV24:
		वापस VOP_FMT_YUV444SP;
	शेष:
		DRM_ERROR("unsupported format[%08x]\n", क्रमmat);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक vop_convert_afbc_क्रमmat(uपूर्णांक32_t क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ABGR8888:
		वापस AFBC_FMT_U8U8U8U8;
	हाल DRM_FORMAT_RGB888:
	हाल DRM_FORMAT_BGR888:
		वापस AFBC_FMT_U8U8U8;
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_BGR565:
		वापस AFBC_FMT_RGB565;
	/* either of the below should not be reachable */
	शेष:
		DRM_WARN_ONCE("unsupported AFBC format[%08x]\n", क्रमmat);
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल uपूर्णांक16_t scl_vop_cal_scale(क्रमागत scale_mode mode, uपूर्णांक32_t src,
				  uपूर्णांक32_t dst, bool is_horizontal,
				  पूर्णांक vsu_mode, पूर्णांक *vskiplines)
अणु
	uपूर्णांक16_t val = 1 << SCL_FT_DEFAULT_FIXPOINT_SHIFT;

	अगर (vskiplines)
		*vskiplines = 0;

	अगर (is_horizontal) अणु
		अगर (mode == SCALE_UP)
			val = GET_SCL_FT_BIC(src, dst);
		अन्यथा अगर (mode == SCALE_DOWN)
			val = GET_SCL_FT_BILI_DN(src, dst);
	पूर्ण अन्यथा अणु
		अगर (mode == SCALE_UP) अणु
			अगर (vsu_mode == SCALE_UP_BIL)
				val = GET_SCL_FT_BILI_UP(src, dst);
			अन्यथा
				val = GET_SCL_FT_BIC(src, dst);
		पूर्ण अन्यथा अगर (mode == SCALE_DOWN) अणु
			अगर (vskiplines) अणु
				*vskiplines = scl_get_vskiplines(src, dst);
				val = scl_get_bili_dn_vskip(src, dst,
							    *vskiplines);
			पूर्ण अन्यथा अणु
				val = GET_SCL_FT_BILI_DN(src, dst);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम scl_vop_cal_scl_fac(काष्ठा vop *vop, स्थिर काष्ठा vop_win_data *win,
			     uपूर्णांक32_t src_w, uपूर्णांक32_t src_h, uपूर्णांक32_t dst_w,
			     uपूर्णांक32_t dst_h, स्थिर काष्ठा drm_क्रमmat_info *info)
अणु
	uपूर्णांक16_t yrgb_hor_scl_mode, yrgb_ver_scl_mode;
	uपूर्णांक16_t cbcr_hor_scl_mode = SCALE_NONE;
	uपूर्णांक16_t cbcr_ver_scl_mode = SCALE_NONE;
	bool is_yuv = false;
	uपूर्णांक16_t cbcr_src_w = src_w / info->hsub;
	uपूर्णांक16_t cbcr_src_h = src_h / info->vsub;
	uपूर्णांक16_t vsu_mode;
	uपूर्णांक16_t lb_mode;
	uपूर्णांक32_t val;
	पूर्णांक vskiplines;

	अगर (info->is_yuv)
		is_yuv = true;

	अगर (dst_w > 3840) अणु
		DRM_DEV_ERROR(vop->dev, "Maximum dst width (3840) exceeded\n");
		वापस;
	पूर्ण

	अगर (!win->phy->scl->ext) अणु
		VOP_SCL_SET(vop, win, scale_yrgb_x,
			    scl_cal_scale2(src_w, dst_w));
		VOP_SCL_SET(vop, win, scale_yrgb_y,
			    scl_cal_scale2(src_h, dst_h));
		अगर (is_yuv) अणु
			VOP_SCL_SET(vop, win, scale_cbcr_x,
				    scl_cal_scale2(cbcr_src_w, dst_w));
			VOP_SCL_SET(vop, win, scale_cbcr_y,
				    scl_cal_scale2(cbcr_src_h, dst_h));
		पूर्ण
		वापस;
	पूर्ण

	yrgb_hor_scl_mode = scl_get_scl_mode(src_w, dst_w);
	yrgb_ver_scl_mode = scl_get_scl_mode(src_h, dst_h);

	अगर (is_yuv) अणु
		cbcr_hor_scl_mode = scl_get_scl_mode(cbcr_src_w, dst_w);
		cbcr_ver_scl_mode = scl_get_scl_mode(cbcr_src_h, dst_h);
		अगर (cbcr_hor_scl_mode == SCALE_DOWN)
			lb_mode = scl_vop_cal_lb_mode(dst_w, true);
		अन्यथा
			lb_mode = scl_vop_cal_lb_mode(cbcr_src_w, true);
	पूर्ण अन्यथा अणु
		अगर (yrgb_hor_scl_mode == SCALE_DOWN)
			lb_mode = scl_vop_cal_lb_mode(dst_w, false);
		अन्यथा
			lb_mode = scl_vop_cal_lb_mode(src_w, false);
	पूर्ण

	VOP_SCL_SET_EXT(vop, win, lb_mode, lb_mode);
	अगर (lb_mode == LB_RGB_3840X2) अणु
		अगर (yrgb_ver_scl_mode != SCALE_NONE) अणु
			DRM_DEV_ERROR(vop->dev, "not allow yrgb ver scale\n");
			वापस;
		पूर्ण
		अगर (cbcr_ver_scl_mode != SCALE_NONE) अणु
			DRM_DEV_ERROR(vop->dev, "not allow cbcr ver scale\n");
			वापस;
		पूर्ण
		vsu_mode = SCALE_UP_BIL;
	पूर्ण अन्यथा अगर (lb_mode == LB_RGB_2560X4) अणु
		vsu_mode = SCALE_UP_BIL;
	पूर्ण अन्यथा अणु
		vsu_mode = SCALE_UP_BIC;
	पूर्ण

	val = scl_vop_cal_scale(yrgb_hor_scl_mode, src_w, dst_w,
				true, 0, शून्य);
	VOP_SCL_SET(vop, win, scale_yrgb_x, val);
	val = scl_vop_cal_scale(yrgb_ver_scl_mode, src_h, dst_h,
				false, vsu_mode, &vskiplines);
	VOP_SCL_SET(vop, win, scale_yrgb_y, val);

	VOP_SCL_SET_EXT(vop, win, vsd_yrgb_gt4, vskiplines == 4);
	VOP_SCL_SET_EXT(vop, win, vsd_yrgb_gt2, vskiplines == 2);

	VOP_SCL_SET_EXT(vop, win, yrgb_hor_scl_mode, yrgb_hor_scl_mode);
	VOP_SCL_SET_EXT(vop, win, yrgb_ver_scl_mode, yrgb_ver_scl_mode);
	VOP_SCL_SET_EXT(vop, win, yrgb_hsd_mode, SCALE_DOWN_BIL);
	VOP_SCL_SET_EXT(vop, win, yrgb_vsd_mode, SCALE_DOWN_BIL);
	VOP_SCL_SET_EXT(vop, win, yrgb_vsu_mode, vsu_mode);
	अगर (is_yuv) अणु
		val = scl_vop_cal_scale(cbcr_hor_scl_mode, cbcr_src_w,
					dst_w, true, 0, शून्य);
		VOP_SCL_SET(vop, win, scale_cbcr_x, val);
		val = scl_vop_cal_scale(cbcr_ver_scl_mode, cbcr_src_h,
					dst_h, false, vsu_mode, &vskiplines);
		VOP_SCL_SET(vop, win, scale_cbcr_y, val);

		VOP_SCL_SET_EXT(vop, win, vsd_cbcr_gt4, vskiplines == 4);
		VOP_SCL_SET_EXT(vop, win, vsd_cbcr_gt2, vskiplines == 2);
		VOP_SCL_SET_EXT(vop, win, cbcr_hor_scl_mode, cbcr_hor_scl_mode);
		VOP_SCL_SET_EXT(vop, win, cbcr_ver_scl_mode, cbcr_ver_scl_mode);
		VOP_SCL_SET_EXT(vop, win, cbcr_hsd_mode, SCALE_DOWN_BIL);
		VOP_SCL_SET_EXT(vop, win, cbcr_vsd_mode, SCALE_DOWN_BIL);
		VOP_SCL_SET_EXT(vop, win, cbcr_vsu_mode, vsu_mode);
	पूर्ण
पूर्ण

अटल व्योम vop_dsp_hold_valid_irq_enable(काष्ठा vop *vop)
अणु
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(!vop->is_enabled))
		वापस;

	spin_lock_irqsave(&vop->irq_lock, flags);

	VOP_INTR_SET_TYPE(vop, clear, DSP_HOLD_VALID_INTR, 1);
	VOP_INTR_SET_TYPE(vop, enable, DSP_HOLD_VALID_INTR, 1);

	spin_unlock_irqrestore(&vop->irq_lock, flags);
पूर्ण

अटल व्योम vop_dsp_hold_valid_irq_disable(काष्ठा vop *vop)
अणु
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(!vop->is_enabled))
		वापस;

	spin_lock_irqsave(&vop->irq_lock, flags);

	VOP_INTR_SET_TYPE(vop, enable, DSP_HOLD_VALID_INTR, 0);

	spin_unlock_irqrestore(&vop->irq_lock, flags);
पूर्ण

/*
 * (1) each frame starts at the start of the Vsync pulse which is संकेतed by
 *     the "FRAME_SYNC" पूर्णांकerrupt.
 * (2) the active data region of each frame ends at dsp_vact_end
 * (3) we should program this same number (dsp_vact_end) पूर्णांकo dsp_line_frag_num,
 *      to get "LINE_FLAG" पूर्णांकerrupt at the end of the active on screen data.
 *
 * VOP_INTR_CTRL0.dsp_line_frag_num = VOP_DSP_VACT_ST_END.dsp_vact_end
 * Interrupts
 * LINE_FLAG -------------------------------+
 * FRAME_SYNC ----+                         |
 *                |                         |
 *                v                         v
 *                | Vsync | Vbp |  Vactive  | Vfp |
 *                        ^     ^           ^     ^
 *                        |     |           |     |
 *                        |     |           |     |
 * dsp_vs_end ------------+     |           |     |   VOP_DSP_VTOTAL_VS_END
 * dsp_vact_start --------------+           |     |   VOP_DSP_VACT_ST_END
 * dsp_vact_end ----------------------------+     |   VOP_DSP_VACT_ST_END
 * dsp_total -------------------------------------+   VOP_DSP_VTOTAL_VS_END
 */
अटल bool vop_line_flag_irq_is_enabled(काष्ठा vop *vop)
अणु
	uपूर्णांक32_t line_flag_irq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vop->irq_lock, flags);

	line_flag_irq = VOP_INTR_GET_TYPE(vop, enable, LINE_FLAG_INTR);

	spin_unlock_irqrestore(&vop->irq_lock, flags);

	वापस !!line_flag_irq;
पूर्ण

अटल व्योम vop_line_flag_irq_enable(काष्ठा vop *vop)
अणु
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(!vop->is_enabled))
		वापस;

	spin_lock_irqsave(&vop->irq_lock, flags);

	VOP_INTR_SET_TYPE(vop, clear, LINE_FLAG_INTR, 1);
	VOP_INTR_SET_TYPE(vop, enable, LINE_FLAG_INTR, 1);

	spin_unlock_irqrestore(&vop->irq_lock, flags);
पूर्ण

अटल व्योम vop_line_flag_irq_disable(काष्ठा vop *vop)
अणु
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(!vop->is_enabled))
		वापस;

	spin_lock_irqsave(&vop->irq_lock, flags);

	VOP_INTR_SET_TYPE(vop, enable, LINE_FLAG_INTR, 0);

	spin_unlock_irqrestore(&vop->irq_lock, flags);
पूर्ण

अटल पूर्णांक vop_core_clks_enable(काष्ठा vop *vop)
अणु
	पूर्णांक ret;

	ret = clk_enable(vop->hclk);
	अगर (ret < 0)
		वापस ret;

	ret = clk_enable(vop->aclk);
	अगर (ret < 0)
		जाओ err_disable_hclk;

	वापस 0;

err_disable_hclk:
	clk_disable(vop->hclk);
	वापस ret;
पूर्ण

अटल व्योम vop_core_clks_disable(काष्ठा vop *vop)
अणु
	clk_disable(vop->aclk);
	clk_disable(vop->hclk);
पूर्ण

अटल व्योम vop_win_disable(काष्ठा vop *vop, स्थिर काष्ठा vop_win *vop_win)
अणु
	स्थिर काष्ठा vop_win_data *win = vop_win->data;

	अगर (win->phy->scl && win->phy->scl->ext) अणु
		VOP_SCL_SET_EXT(vop, win, yrgb_hor_scl_mode, SCALE_NONE);
		VOP_SCL_SET_EXT(vop, win, yrgb_ver_scl_mode, SCALE_NONE);
		VOP_SCL_SET_EXT(vop, win, cbcr_hor_scl_mode, SCALE_NONE);
		VOP_SCL_SET_EXT(vop, win, cbcr_ver_scl_mode, SCALE_NONE);
	पूर्ण

	VOP_WIN_SET(vop, win, enable, 0);
	vop->win_enabled &= ~BIT(VOP_WIN_TO_INDEX(vop_win));
पूर्ण

अटल पूर्णांक vop_enable(काष्ठा drm_crtc *crtc, काष्ठा drm_crtc_state *old_state)
अणु
	काष्ठा vop *vop = to_vop(crtc);
	पूर्णांक ret, i;

	ret = pm_runसमय_get_sync(vop->dev);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(vop->dev, "failed to get pm runtime: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = vop_core_clks_enable(vop);
	अगर (WARN_ON(ret < 0))
		जाओ err_put_pm_runसमय;

	ret = clk_enable(vop->dclk);
	अगर (WARN_ON(ret < 0))
		जाओ err_disable_core;

	/*
	 * Slave iommu shares घातer, irq and घड़ी with vop.  It was associated
	 * स्वतःmatically with this master device via common driver code.
	 * Now that we have enabled the घड़ी we attach it to the shared drm
	 * mapping.
	 */
	ret = rockchip_drm_dma_attach_device(vop->drm_dev, vop->dev);
	अगर (ret) अणु
		DRM_DEV_ERROR(vop->dev,
			      "failed to attach dma mapping, %d\n", ret);
		जाओ err_disable_dclk;
	पूर्ण

	spin_lock(&vop->reg_lock);
	क्रम (i = 0; i < vop->len; i += 4)
		ग_लिखोl_relaxed(vop->regsbak[i / 4], vop->regs + i);

	/*
	 * We need to make sure that all winकरोws are disabled beक्रमe we
	 * enable the crtc. Otherwise we might try to scan from a destroyed
	 * buffer later.
	 *
	 * In the हाल of enable-after-PSR, we करोn't need to worry about this
	 * हाल since the buffer is guaranteed to be valid and disabling the
	 * winकरोw will result in screen glitches on PSR निकास.
	 */
	अगर (!old_state || !old_state->self_refresh_active) अणु
		क्रम (i = 0; i < vop->data->win_size; i++) अणु
			काष्ठा vop_win *vop_win = &vop->win[i];

			vop_win_disable(vop, vop_win);
		पूर्ण
	पूर्ण

	अगर (vop->data->afbc) अणु
		काष्ठा rockchip_crtc_state *s;
		/*
		 * Disable AFBC and क्रमget there was a vop winकरोw with AFBC
		 */
		VOP_AFBC_SET(vop, enable, 0);
		s = to_rockchip_crtc_state(crtc->state);
		s->enable_afbc = false;
	पूर्ण

	vop_cfg_करोne(vop);

	spin_unlock(&vop->reg_lock);

	/*
	 * At here, vop घड़ी & iommu is enable, R/W vop regs would be safe.
	 */
	vop->is_enabled = true;

	spin_lock(&vop->reg_lock);

	VOP_REG_SET(vop, common, standby, 1);

	spin_unlock(&vop->reg_lock);

	drm_crtc_vblank_on(crtc);

	वापस 0;

err_disable_dclk:
	clk_disable(vop->dclk);
err_disable_core:
	vop_core_clks_disable(vop);
err_put_pm_runसमय:
	pm_runसमय_put_sync(vop->dev);
	वापस ret;
पूर्ण

अटल व्योम rockchip_drm_set_win_enabled(काष्ठा drm_crtc *crtc, bool enabled)
अणु
        काष्ठा vop *vop = to_vop(crtc);
        पूर्णांक i;

        spin_lock(&vop->reg_lock);

        क्रम (i = 0; i < vop->data->win_size; i++) अणु
                काष्ठा vop_win *vop_win = &vop->win[i];
                स्थिर काष्ठा vop_win_data *win = vop_win->data;

                VOP_WIN_SET(vop, win, enable,
                            enabled && (vop->win_enabled & BIT(i)));
        पूर्ण
        vop_cfg_करोne(vop);

        spin_unlock(&vop->reg_lock);
पूर्ण

अटल व्योम vop_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा vop *vop = to_vop(crtc);

	WARN_ON(vop->event);

	अगर (crtc->state->self_refresh_active)
		rockchip_drm_set_win_enabled(crtc, false);

	mutex_lock(&vop->vop_lock);

	drm_crtc_vblank_off(crtc);

	अगर (crtc->state->self_refresh_active)
		जाओ out;

	/*
	 * Vop standby will take effect at end of current frame,
	 * अगर dsp hold valid irq happen, it means standby complete.
	 *
	 * we must रुको standby complete when we want to disable aclk,
	 * अगर not, memory bus maybe dead.
	 */
	reinit_completion(&vop->dsp_hold_completion);
	vop_dsp_hold_valid_irq_enable(vop);

	spin_lock(&vop->reg_lock);

	VOP_REG_SET(vop, common, standby, 1);

	spin_unlock(&vop->reg_lock);

	रुको_क्रम_completion(&vop->dsp_hold_completion);

	vop_dsp_hold_valid_irq_disable(vop);

	vop->is_enabled = false;

	/*
	 * vop standby complete, so iommu detach is safe.
	 */
	rockchip_drm_dma_detach_device(vop->drm_dev, vop->dev);

	clk_disable(vop->dclk);
	vop_core_clks_disable(vop);
	pm_runसमय_put(vop->dev);

out:
	mutex_unlock(&vop->vop_lock);

	अगर (crtc->state->event && !crtc->state->active) अणु
		spin_lock_irq(&crtc->dev->event_lock);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		spin_unlock_irq(&crtc->dev->event_lock);

		crtc->state->event = शून्य;
	पूर्ण
पूर्ण

अटल व्योम vop_plane_destroy(काष्ठा drm_plane *plane)
अणु
	drm_plane_cleanup(plane);
पूर्ण

अटल अंतरभूत bool rockchip_afbc(u64 modअगरier)
अणु
	वापस modअगरier == ROCKCHIP_AFBC_MOD;
पूर्ण

अटल bool rockchip_mod_supported(काष्ठा drm_plane *plane,
				   u32 क्रमmat, u64 modअगरier)
अणु
	अगर (modअगरier == DRM_FORMAT_MOD_LINEAR)
		वापस true;

	अगर (!rockchip_afbc(modअगरier)) अणु
		DRM_DEBUG_KMS("Unsupported format modifier 0x%llx\n", modअगरier);

		वापस false;
	पूर्ण

	वापस vop_convert_afbc_क्रमmat(क्रमmat) >= 0;
पूर्ण

अटल पूर्णांक vop_plane_atomic_check(काष्ठा drm_plane *plane,
			   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_crtc *crtc = new_plane_state->crtc;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_framebuffer *fb = new_plane_state->fb;
	काष्ठा vop_win *vop_win = to_vop_win(plane);
	स्थिर काष्ठा vop_win_data *win = vop_win->data;
	पूर्णांक ret;
	पूर्णांक min_scale = win->phy->scl ? FRAC_16_16(1, 8) :
					DRM_PLANE_HELPER_NO_SCALING;
	पूर्णांक max_scale = win->phy->scl ? FRAC_16_16(8, 1) :
					DRM_PLANE_HELPER_NO_SCALING;

	अगर (!crtc || WARN_ON(!fb))
		वापस 0;

	crtc_state = drm_atomic_get_existing_crtc_state(state,
							crtc);
	अगर (WARN_ON(!crtc_state))
		वापस -EINVAL;

	ret = drm_atomic_helper_check_plane_state(new_plane_state, crtc_state,
						  min_scale, max_scale,
						  true, true);
	अगर (ret)
		वापस ret;

	अगर (!new_plane_state->visible)
		वापस 0;

	ret = vop_convert_क्रमmat(fb->क्रमmat->क्रमmat);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Src.x1 can be odd when करो clip, but yuv plane start poपूर्णांक
	 * need align with 2 pixel.
	 */
	अगर (fb->क्रमmat->is_yuv && ((new_plane_state->src.x1 >> 16) % 2)) अणु
		DRM_ERROR("Invalid Source: Yuv format not support odd xpos\n");
		वापस -EINVAL;
	पूर्ण

	अगर (fb->क्रमmat->is_yuv && new_plane_state->rotation & DRM_MODE_REFLECT_Y) अणु
		DRM_ERROR("Invalid Source: Yuv format does not support this rotation\n");
		वापस -EINVAL;
	पूर्ण

	अगर (rockchip_afbc(fb->modअगरier)) अणु
		काष्ठा vop *vop = to_vop(crtc);

		अगर (!vop->data->afbc) अणु
			DRM_ERROR("vop does not support AFBC\n");
			वापस -EINVAL;
		पूर्ण

		ret = vop_convert_afbc_क्रमmat(fb->क्रमmat->क्रमmat);
		अगर (ret < 0)
			वापस ret;

		अगर (new_plane_state->src.x1 || new_plane_state->src.y1) अणु
			DRM_ERROR("AFBC does not support offset display, xpos=%d, ypos=%d, offset=%d\n",
				  new_plane_state->src.x1,
				  new_plane_state->src.y1, fb->offsets[0]);
			वापस -EINVAL;
		पूर्ण

		अगर (new_plane_state->rotation && new_plane_state->rotation != DRM_MODE_ROTATE_0) अणु
			DRM_ERROR("No rotation support in AFBC, rotation=%d\n",
				  new_plane_state->rotation);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vop_plane_atomic_disable(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा vop_win *vop_win = to_vop_win(plane);
	काष्ठा vop *vop = to_vop(old_state->crtc);

	अगर (!old_state->crtc)
		वापस;

	spin_lock(&vop->reg_lock);

	vop_win_disable(vop, vop_win);

	spin_unlock(&vop->reg_lock);
पूर्ण

अटल व्योम vop_plane_atomic_update(काष्ठा drm_plane *plane,
		काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_crtc *crtc = new_state->crtc;
	काष्ठा vop_win *vop_win = to_vop_win(plane);
	स्थिर काष्ठा vop_win_data *win = vop_win->data;
	स्थिर काष्ठा vop_win_yuv2yuv_data *win_yuv2yuv = vop_win->yuv2yuv_data;
	काष्ठा vop *vop = to_vop(new_state->crtc);
	काष्ठा drm_framebuffer *fb = new_state->fb;
	अचिन्हित पूर्णांक actual_w, actual_h;
	अचिन्हित पूर्णांक dsp_stx, dsp_sty;
	uपूर्णांक32_t act_info, dsp_info, dsp_st;
	काष्ठा drm_rect *src = &new_state->src;
	काष्ठा drm_rect *dest = &new_state->dst;
	काष्ठा drm_gem_object *obj, *uv_obj;
	काष्ठा rockchip_gem_object *rk_obj, *rk_uv_obj;
	अचिन्हित दीर्घ offset;
	dma_addr_t dma_addr;
	uपूर्णांक32_t val;
	bool rb_swap;
	पूर्णांक win_index = VOP_WIN_TO_INDEX(vop_win);
	पूर्णांक क्रमmat;
	पूर्णांक is_yuv = fb->क्रमmat->is_yuv;
	पूर्णांक i;

	/*
	 * can't update plane when vop is disabled.
	 */
	अगर (WARN_ON(!crtc))
		वापस;

	अगर (WARN_ON(!vop->is_enabled))
		वापस;

	अगर (!new_state->visible) अणु
		vop_plane_atomic_disable(plane, state);
		वापस;
	पूर्ण

	obj = fb->obj[0];
	rk_obj = to_rockchip_obj(obj);

	actual_w = drm_rect_width(src) >> 16;
	actual_h = drm_rect_height(src) >> 16;
	act_info = (actual_h - 1) << 16 | ((actual_w - 1) & 0xffff);

	dsp_info = (drm_rect_height(dest) - 1) << 16;
	dsp_info |= (drm_rect_width(dest) - 1) & 0xffff;

	dsp_stx = dest->x1 + crtc->mode.htotal - crtc->mode.hsync_start;
	dsp_sty = dest->y1 + crtc->mode.vtotal - crtc->mode.vsync_start;
	dsp_st = dsp_sty << 16 | (dsp_stx & 0xffff);

	offset = (src->x1 >> 16) * fb->क्रमmat->cpp[0];
	offset += (src->y1 >> 16) * fb->pitches[0];
	dma_addr = rk_obj->dma_addr + offset + fb->offsets[0];

	/*
	 * For y-mirroring we need to move address
	 * to the beginning of the last line.
	 */
	अगर (new_state->rotation & DRM_MODE_REFLECT_Y)
		dma_addr += (actual_h - 1) * fb->pitches[0];

	क्रमmat = vop_convert_क्रमmat(fb->क्रमmat->क्रमmat);

	spin_lock(&vop->reg_lock);

	अगर (rockchip_afbc(fb->modअगरier)) अणु
		पूर्णांक afbc_क्रमmat = vop_convert_afbc_क्रमmat(fb->क्रमmat->क्रमmat);

		VOP_AFBC_SET(vop, क्रमmat, afbc_क्रमmat | AFBC_TILE_16x16);
		VOP_AFBC_SET(vop, hreg_block_split, 0);
		VOP_AFBC_SET(vop, win_sel, VOP_WIN_TO_INDEX(vop_win));
		VOP_AFBC_SET(vop, hdr_ptr, dma_addr);
		VOP_AFBC_SET(vop, pic_size, act_info);
	पूर्ण

	VOP_WIN_SET(vop, win, क्रमmat, क्रमmat);
	VOP_WIN_SET(vop, win, yrgb_vir, DIV_ROUND_UP(fb->pitches[0], 4));
	VOP_WIN_SET(vop, win, yrgb_mst, dma_addr);
	VOP_WIN_YUV2YUV_SET(vop, win_yuv2yuv, y2r_en, is_yuv);
	VOP_WIN_SET(vop, win, y_mir_en,
		    (new_state->rotation & DRM_MODE_REFLECT_Y) ? 1 : 0);
	VOP_WIN_SET(vop, win, x_mir_en,
		    (new_state->rotation & DRM_MODE_REFLECT_X) ? 1 : 0);

	अगर (is_yuv) अणु
		पूर्णांक hsub = fb->क्रमmat->hsub;
		पूर्णांक vsub = fb->क्रमmat->vsub;
		पूर्णांक bpp = fb->क्रमmat->cpp[1];

		uv_obj = fb->obj[1];
		rk_uv_obj = to_rockchip_obj(uv_obj);

		offset = (src->x1 >> 16) * bpp / hsub;
		offset += (src->y1 >> 16) * fb->pitches[1] / vsub;

		dma_addr = rk_uv_obj->dma_addr + offset + fb->offsets[1];
		VOP_WIN_SET(vop, win, uv_vir, DIV_ROUND_UP(fb->pitches[1], 4));
		VOP_WIN_SET(vop, win, uv_mst, dma_addr);

		क्रम (i = 0; i < NUM_YUV2YUV_COEFFICIENTS; i++) अणु
			VOP_WIN_YUV2YUV_COEFFICIENT_SET(vop,
							win_yuv2yuv,
							y2r_coefficients[i],
							bt601_yuv2rgb[i]);
		पूर्ण
	पूर्ण

	अगर (win->phy->scl)
		scl_vop_cal_scl_fac(vop, win, actual_w, actual_h,
				    drm_rect_width(dest), drm_rect_height(dest),
				    fb->क्रमmat);

	VOP_WIN_SET(vop, win, act_info, act_info);
	VOP_WIN_SET(vop, win, dsp_info, dsp_info);
	VOP_WIN_SET(vop, win, dsp_st, dsp_st);

	rb_swap = has_rb_swapped(fb->क्रमmat->क्रमmat);
	VOP_WIN_SET(vop, win, rb_swap, rb_swap);

	/*
	 * Blending win0 with the background color करोesn't seem to work
	 * correctly. We only get the background color, no matter the contents
	 * of the win0 framebuffer.  However, blending pre-multiplied color
	 * with the शेष opaque black शेष background color is a no-op,
	 * so we can just disable blending to get the correct result.
	 */
	अगर (fb->क्रमmat->has_alpha && win_index > 0) अणु
		VOP_WIN_SET(vop, win, dst_alpha_ctl,
			    DST_FACTOR_M0(ALPHA_SRC_INVERSE));
		val = SRC_ALPHA_EN(1) | SRC_COLOR_M0(ALPHA_SRC_PRE_MUL) |
			SRC_ALPHA_M0(ALPHA_STRAIGHT) |
			SRC_BLEND_M0(ALPHA_PER_PIX) |
			SRC_ALPHA_CAL_M0(ALPHA_NO_SATURATION) |
			SRC_FACTOR_M0(ALPHA_ONE);
		VOP_WIN_SET(vop, win, src_alpha_ctl, val);

		VOP_WIN_SET(vop, win, alpha_pre_mul, ALPHA_SRC_PRE_MUL);
		VOP_WIN_SET(vop, win, alpha_mode, ALPHA_PER_PIX);
		VOP_WIN_SET(vop, win, alpha_en, 1);
	पूर्ण अन्यथा अणु
		VOP_WIN_SET(vop, win, src_alpha_ctl, SRC_ALPHA_EN(0));
	पूर्ण

	VOP_WIN_SET(vop, win, enable, 1);
	vop->win_enabled |= BIT(win_index);
	spin_unlock(&vop->reg_lock);
पूर्ण

अटल पूर्णांक vop_plane_atomic_async_check(काष्ठा drm_plane *plane,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा vop_win *vop_win = to_vop_win(plane);
	स्थिर काष्ठा vop_win_data *win = vop_win->data;
	पूर्णांक min_scale = win->phy->scl ? FRAC_16_16(1, 8) :
					DRM_PLANE_HELPER_NO_SCALING;
	पूर्णांक max_scale = win->phy->scl ? FRAC_16_16(8, 1) :
					DRM_PLANE_HELPER_NO_SCALING;
	काष्ठा drm_crtc_state *crtc_state;

	अगर (plane != new_plane_state->crtc->cursor)
		वापस -EINVAL;

	अगर (!plane->state)
		वापस -EINVAL;

	अगर (!plane->state->fb)
		वापस -EINVAL;

	अगर (state)
		crtc_state = drm_atomic_get_existing_crtc_state(state,
								new_plane_state->crtc);
	अन्यथा /* Special हाल क्रम asynchronous cursor updates. */
		crtc_state = plane->crtc->state;

	वापस drm_atomic_helper_check_plane_state(plane->state, crtc_state,
						   min_scale, max_scale,
						   true, true);
पूर्ण

अटल व्योम vop_plane_atomic_async_update(काष्ठा drm_plane *plane,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा vop *vop = to_vop(plane->state->crtc);
	काष्ठा drm_framebuffer *old_fb = plane->state->fb;

	plane->state->crtc_x = new_state->crtc_x;
	plane->state->crtc_y = new_state->crtc_y;
	plane->state->crtc_h = new_state->crtc_h;
	plane->state->crtc_w = new_state->crtc_w;
	plane->state->src_x = new_state->src_x;
	plane->state->src_y = new_state->src_y;
	plane->state->src_h = new_state->src_h;
	plane->state->src_w = new_state->src_w;
	swap(plane->state->fb, new_state->fb);

	अगर (vop->is_enabled) अणु
		vop_plane_atomic_update(plane, state);
		spin_lock(&vop->reg_lock);
		vop_cfg_करोne(vop);
		spin_unlock(&vop->reg_lock);

		/*
		 * A scanout can still be occurring, so we can't drop the
		 * reference to the old framebuffer. To solve this we get a
		 * reference to old_fb and set a worker to release it later.
		 * FIXME: अगर we perक्रमm 500 async_update calls beक्रमe the
		 * vblank, then we can have 500 dअगरferent framebuffers रुकोing
		 * to be released.
		 */
		अगर (old_fb && plane->state->fb != old_fb) अणु
			drm_framebuffer_get(old_fb);
			WARN_ON(drm_crtc_vblank_get(plane->state->crtc) != 0);
			drm_flip_work_queue(&vop->fb_unref_work, old_fb);
			set_bit(VOP_PENDING_FB_UNREF, &vop->pending);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs plane_helper_funcs = अणु
	.atomic_check = vop_plane_atomic_check,
	.atomic_update = vop_plane_atomic_update,
	.atomic_disable = vop_plane_atomic_disable,
	.atomic_async_check = vop_plane_atomic_async_check,
	.atomic_async_update = vop_plane_atomic_async_update,
	.prepare_fb = drm_gem_plane_helper_prepare_fb,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs vop_plane_funcs = अणु
	.update_plane	= drm_atomic_helper_update_plane,
	.disable_plane	= drm_atomic_helper_disable_plane,
	.destroy = vop_plane_destroy,
	.reset = drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
	.क्रमmat_mod_supported = rockchip_mod_supported,
पूर्ण;

अटल पूर्णांक vop_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vop *vop = to_vop(crtc);
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(!vop->is_enabled))
		वापस -EPERM;

	spin_lock_irqsave(&vop->irq_lock, flags);

	VOP_INTR_SET_TYPE(vop, clear, FS_INTR, 1);
	VOP_INTR_SET_TYPE(vop, enable, FS_INTR, 1);

	spin_unlock_irqrestore(&vop->irq_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम vop_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vop *vop = to_vop(crtc);
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(!vop->is_enabled))
		वापस;

	spin_lock_irqsave(&vop->irq_lock, flags);

	VOP_INTR_SET_TYPE(vop, enable, FS_INTR, 0);

	spin_unlock_irqrestore(&vop->irq_lock, flags);
पूर्ण

अटल bool vop_crtc_mode_fixup(काष्ठा drm_crtc *crtc,
				स्थिर काष्ठा drm_display_mode *mode,
				काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा vop *vop = to_vop(crtc);
	अचिन्हित दीर्घ rate;

	/*
	 * Clock craziness.
	 *
	 * Key poपूर्णांकs:
	 *
	 * - DRM works in in kHz.
	 * - Clock framework works in Hz.
	 * - Rockchip's घड़ी driver picks the घड़ी rate that is the
	 *   same _OR LOWER_ than the one requested.
	 *
	 * Action plan:
	 *
	 * 1. When DRM gives us a mode, we should add 999 Hz to it.  That way
	 *    अगर the घड़ी we need is 60000001 Hz (~60 MHz) and DRM tells us to
	 *    make 60000 kHz then the घड़ी framework will actually give us
	 *    the right घड़ी.
	 *
	 *    NOTE: अगर the PLL (maybe through a भागider) could actually make
	 *    a घड़ी rate 999 Hz higher instead of the one we want then this
	 *    could be a problem.  Unक्रमtunately there's not much we can करो
	 *    since it's baked into DRM to use kHz.  It shouldn't matter in
	 *    practice since Rockchip PLLs are controlled by tables and
	 *    even अगर there is a भागider in the middle I wouldn't expect PLL
	 *    rates in the table that are just a few kHz dअगरferent.
	 *
	 * 2. Get the घड़ी framework to round the rate क्रम us to tell us
	 *    what it will actually make.
	 *
	 * 3. Store the rounded up rate so that we करोn't need to worry about
	 *    this in the actual clk_set_rate().
	 */
	rate = clk_round_rate(vop->dclk, adjusted_mode->घड़ी * 1000 + 999);
	adjusted_mode->घड़ी = DIV_ROUND_UP(rate, 1000);

	वापस true;
पूर्ण

अटल bool vop_dsp_lut_is_enabled(काष्ठा vop *vop)
अणु
	वापस vop_पढ़ो_reg(vop, 0, &vop->data->common->dsp_lut_en);
पूर्ण

अटल व्योम vop_crtc_ग_लिखो_gamma_lut(काष्ठा vop *vop, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_color_lut *lut = crtc->state->gamma_lut->data;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < crtc->gamma_size; i++) अणु
		u32 word;

		word = (drm_color_lut_extract(lut[i].red, 10) << 20) |
		       (drm_color_lut_extract(lut[i].green, 10) << 10) |
			drm_color_lut_extract(lut[i].blue, 10);
		ग_लिखोl(word, vop->lut_regs + i * 4);
	पूर्ण
पूर्ण

अटल व्योम vop_crtc_gamma_set(काष्ठा vop *vop, काष्ठा drm_crtc *crtc,
			       काष्ठा drm_crtc_state *old_state)
अणु
	काष्ठा drm_crtc_state *state = crtc->state;
	अचिन्हित पूर्णांक idle;
	पूर्णांक ret;

	अगर (!vop->lut_regs)
		वापस;
	/*
	 * To disable gamma (gamma_lut is null) or to ग_लिखो
	 * an update to the LUT, clear dsp_lut_en.
	 */
	spin_lock(&vop->reg_lock);
	VOP_REG_SET(vop, common, dsp_lut_en, 0);
	vop_cfg_करोne(vop);
	spin_unlock(&vop->reg_lock);

	/*
	 * In order to ग_लिखो the LUT to the पूर्णांकernal memory,
	 * we need to first make sure the dsp_lut_en bit is cleared.
	 */
	ret = पढ़ोx_poll_समयout(vop_dsp_lut_is_enabled, vop,
				 idle, !idle, 5, 30 * 1000);
	अगर (ret) अणु
		DRM_DEV_ERROR(vop->dev, "display LUT RAM enable timeout!\n");
		वापस;
	पूर्ण

	अगर (!state->gamma_lut)
		वापस;

	spin_lock(&vop->reg_lock);
	vop_crtc_ग_लिखो_gamma_lut(vop, crtc);
	VOP_REG_SET(vop, common, dsp_lut_en, 1);
	vop_cfg_करोne(vop);
	spin_unlock(&vop->reg_lock);
पूर्ण

अटल व्योम vop_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा drm_crtc_state *old_crtc_state = drm_atomic_get_old_crtc_state(state,
									      crtc);
	काष्ठा vop *vop = to_vop(crtc);

	/*
	 * Only update GAMMA अगर the 'active' flag is not changed,
	 * otherwise it's updated by .atomic_enable.
	 */
	अगर (crtc_state->color_mgmt_changed &&
	    !crtc_state->active_changed)
		vop_crtc_gamma_set(vop, crtc, old_crtc_state);
पूर्ण

अटल व्योम vop_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_state = drm_atomic_get_old_crtc_state(state,
									 crtc);
	काष्ठा vop *vop = to_vop(crtc);
	स्थिर काष्ठा vop_data *vop_data = vop->data;
	काष्ठा rockchip_crtc_state *s = to_rockchip_crtc_state(crtc->state);
	काष्ठा drm_display_mode *adjusted_mode = &crtc->state->adjusted_mode;
	u16 hsync_len = adjusted_mode->hsync_end - adjusted_mode->hsync_start;
	u16 hdisplay = adjusted_mode->hdisplay;
	u16 htotal = adjusted_mode->htotal;
	u16 hact_st = adjusted_mode->htotal - adjusted_mode->hsync_start;
	u16 hact_end = hact_st + hdisplay;
	u16 vdisplay = adjusted_mode->vdisplay;
	u16 vtotal = adjusted_mode->vtotal;
	u16 vsync_len = adjusted_mode->vsync_end - adjusted_mode->vsync_start;
	u16 vact_st = adjusted_mode->vtotal - adjusted_mode->vsync_start;
	u16 vact_end = vact_st + vdisplay;
	uपूर्णांक32_t pin_pol, val;
	पूर्णांक dither_bpc = s->output_bpc ? s->output_bpc : 10;
	पूर्णांक ret;

	अगर (old_state && old_state->self_refresh_active) अणु
		drm_crtc_vblank_on(crtc);
		rockchip_drm_set_win_enabled(crtc, true);
		वापस;
	पूर्ण

	/*
	 * If we have a GAMMA LUT in the state, then let's make sure
	 * it's updated. We might be coming out of suspend,
	 * which means the LUT पूर्णांकernal memory needs to be re-written.
	 */
	अगर (crtc->state->gamma_lut)
		vop_crtc_gamma_set(vop, crtc, old_state);

	mutex_lock(&vop->vop_lock);

	WARN_ON(vop->event);

	ret = vop_enable(crtc, old_state);
	अगर (ret) अणु
		mutex_unlock(&vop->vop_lock);
		DRM_DEV_ERROR(vop->dev, "Failed to enable vop (%d)\n", ret);
		वापस;
	पूर्ण
	pin_pol = (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC) ?
		   BIT(HSYNC_POSITIVE) : 0;
	pin_pol |= (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC) ?
		   BIT(VSYNC_POSITIVE) : 0;
	VOP_REG_SET(vop, output, pin_pol, pin_pol);
	VOP_REG_SET(vop, output, mipi_dual_channel_en, 0);

	चयन (s->output_type) अणु
	हाल DRM_MODE_CONNECTOR_LVDS:
		VOP_REG_SET(vop, output, rgb_dclk_pol, 1);
		VOP_REG_SET(vop, output, rgb_pin_pol, pin_pol);
		VOP_REG_SET(vop, output, rgb_en, 1);
		अवरोध;
	हाल DRM_MODE_CONNECTOR_eDP:
		VOP_REG_SET(vop, output, edp_dclk_pol, 1);
		VOP_REG_SET(vop, output, edp_pin_pol, pin_pol);
		VOP_REG_SET(vop, output, edp_en, 1);
		अवरोध;
	हाल DRM_MODE_CONNECTOR_HDMIA:
		VOP_REG_SET(vop, output, hdmi_dclk_pol, 1);
		VOP_REG_SET(vop, output, hdmi_pin_pol, pin_pol);
		VOP_REG_SET(vop, output, hdmi_en, 1);
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DSI:
		VOP_REG_SET(vop, output, mipi_dclk_pol, 1);
		VOP_REG_SET(vop, output, mipi_pin_pol, pin_pol);
		VOP_REG_SET(vop, output, mipi_en, 1);
		VOP_REG_SET(vop, output, mipi_dual_channel_en,
			    !!(s->output_flags & ROCKCHIP_OUTPUT_DSI_DUAL));
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DisplayPort:
		VOP_REG_SET(vop, output, dp_dclk_pol, 0);
		VOP_REG_SET(vop, output, dp_pin_pol, pin_pol);
		VOP_REG_SET(vop, output, dp_en, 1);
		अवरोध;
	शेष:
		DRM_DEV_ERROR(vop->dev, "unsupported connector_type [%d]\n",
			      s->output_type);
	पूर्ण

	/*
	 * अगर vop is not support RGB10 output, need क्रमce RGB10 to RGB888.
	 */
	अगर (s->output_mode == ROCKCHIP_OUT_MODE_AAAA &&
	    !(vop_data->feature & VOP_FEATURE_OUTPUT_RGB10))
		s->output_mode = ROCKCHIP_OUT_MODE_P888;

	अगर (s->output_mode == ROCKCHIP_OUT_MODE_AAAA && dither_bpc <= 8)
		VOP_REG_SET(vop, common, pre_dither_करोwn, 1);
	अन्यथा
		VOP_REG_SET(vop, common, pre_dither_करोwn, 0);

	अगर (dither_bpc == 6) अणु
		VOP_REG_SET(vop, common, dither_करोwn_sel, DITHER_DOWN_ALLEGRO);
		VOP_REG_SET(vop, common, dither_करोwn_mode, RGB888_TO_RGB666);
		VOP_REG_SET(vop, common, dither_करोwn_en, 1);
	पूर्ण अन्यथा अणु
		VOP_REG_SET(vop, common, dither_करोwn_en, 0);
	पूर्ण

	VOP_REG_SET(vop, common, out_mode, s->output_mode);

	VOP_REG_SET(vop, modeset, htotal_pw, (htotal << 16) | hsync_len);
	val = hact_st << 16;
	val |= hact_end;
	VOP_REG_SET(vop, modeset, hact_st_end, val);
	VOP_REG_SET(vop, modeset, hpost_st_end, val);

	VOP_REG_SET(vop, modeset, vtotal_pw, (vtotal << 16) | vsync_len);
	val = vact_st << 16;
	val |= vact_end;
	VOP_REG_SET(vop, modeset, vact_st_end, val);
	VOP_REG_SET(vop, modeset, vpost_st_end, val);

	VOP_REG_SET(vop, पूर्णांकr, line_flag_num[0], vact_end);

	clk_set_rate(vop->dclk, adjusted_mode->घड़ी * 1000);

	VOP_REG_SET(vop, common, standby, 0);
	mutex_unlock(&vop->vop_lock);
पूर्ण

अटल bool vop_fs_irq_is_pending(काष्ठा vop *vop)
अणु
	वापस VOP_INTR_GET_TYPE(vop, status, FS_INTR);
पूर्ण

अटल व्योम vop_रुको_क्रम_irq_handler(काष्ठा vop *vop)
अणु
	bool pending;
	पूर्णांक ret;

	/*
	 * Spin until frame start पूर्णांकerrupt status bit goes low, which means
	 * that पूर्णांकerrupt handler was invoked and cleared it. The समयout of
	 * 10 msecs is really too दीर्घ, but it is just a safety measure अगर
	 * something goes really wrong. The रुको will only happen in the very
	 * unlikely हाल of a vblank happening exactly at the same समय and
	 * shouldn't exceed microseconds range.
	 */
	ret = पढ़ोx_poll_समयout_atomic(vop_fs_irq_is_pending, vop, pending,
					!pending, 0, 10 * 1000);
	अगर (ret)
		DRM_DEV_ERROR(vop->dev, "VOP vblank IRQ stuck for 10 ms\n");

	synchronize_irq(vop->irq);
पूर्ण

अटल पूर्णांक vop_crtc_atomic_check(काष्ठा drm_crtc *crtc,
				 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा vop *vop = to_vop(crtc);
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *plane_state;
	काष्ठा rockchip_crtc_state *s;
	पूर्णांक afbc_planes = 0;

	अगर (vop->lut_regs && crtc_state->color_mgmt_changed &&
	    crtc_state->gamma_lut) अणु
		अचिन्हित पूर्णांक len;

		len = drm_color_lut_size(crtc_state->gamma_lut);
		अगर (len != crtc->gamma_size) अणु
			DRM_DEBUG_KMS("Invalid LUT size; got %d, expected %d\n",
				      len, crtc->gamma_size);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	drm_atomic_crtc_state_क्रम_each_plane(plane, crtc_state) अणु
		plane_state =
			drm_atomic_get_plane_state(crtc_state->state, plane);
		अगर (IS_ERR(plane_state)) अणु
			DRM_DEBUG_KMS("Cannot get plane state for plane %s\n",
				      plane->name);
			वापस PTR_ERR(plane_state);
		पूर्ण

		अगर (drm_is_afbc(plane_state->fb->modअगरier))
			++afbc_planes;
	पूर्ण

	अगर (afbc_planes > 1) अणु
		DRM_DEBUG_KMS("Invalid number of AFBC planes; got %d, expected at most 1\n", afbc_planes);
		वापस -EINVAL;
	पूर्ण

	s = to_rockchip_crtc_state(crtc_state);
	s->enable_afbc = afbc_planes > 0;

	वापस 0;
पूर्ण

अटल व्योम vop_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_crtc_state = drm_atomic_get_old_crtc_state(state,
									      crtc);
	काष्ठा drm_atomic_state *old_state = old_crtc_state->state;
	काष्ठा drm_plane_state *old_plane_state, *new_plane_state;
	काष्ठा vop *vop = to_vop(crtc);
	काष्ठा drm_plane *plane;
	काष्ठा rockchip_crtc_state *s;
	पूर्णांक i;

	अगर (WARN_ON(!vop->is_enabled))
		वापस;

	spin_lock(&vop->reg_lock);

	/* Enable AFBC अगर there is some AFBC winकरोw, disable otherwise. */
	s = to_rockchip_crtc_state(crtc->state);
	VOP_AFBC_SET(vop, enable, s->enable_afbc);
	vop_cfg_करोne(vop);

	spin_unlock(&vop->reg_lock);

	/*
	 * There is a (rather unlikely) possiblity that a vblank पूर्णांकerrupt
	 * fired beक्रमe we set the cfg_करोne bit. To aव्योम spuriously
	 * संकेतling flip completion we need to रुको क्रम it to finish.
	 */
	vop_रुको_क्रम_irq_handler(vop);

	spin_lock_irq(&crtc->dev->event_lock);
	अगर (crtc->state->event) अणु
		WARN_ON(drm_crtc_vblank_get(crtc) != 0);
		WARN_ON(vop->event);

		vop->event = crtc->state->event;
		crtc->state->event = शून्य;
	पूर्ण
	spin_unlock_irq(&crtc->dev->event_lock);

	क्रम_each_oldnew_plane_in_state(old_state, plane, old_plane_state,
				       new_plane_state, i) अणु
		अगर (!old_plane_state->fb)
			जारी;

		अगर (old_plane_state->fb == new_plane_state->fb)
			जारी;

		drm_framebuffer_get(old_plane_state->fb);
		WARN_ON(drm_crtc_vblank_get(crtc) != 0);
		drm_flip_work_queue(&vop->fb_unref_work, old_plane_state->fb);
		set_bit(VOP_PENDING_FB_UNREF, &vop->pending);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs vop_crtc_helper_funcs = अणु
	.mode_fixup = vop_crtc_mode_fixup,
	.atomic_check = vop_crtc_atomic_check,
	.atomic_begin = vop_crtc_atomic_begin,
	.atomic_flush = vop_crtc_atomic_flush,
	.atomic_enable = vop_crtc_atomic_enable,
	.atomic_disable = vop_crtc_atomic_disable,
पूर्ण;

अटल व्योम vop_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	drm_crtc_cleanup(crtc);
पूर्ण

अटल काष्ठा drm_crtc_state *vop_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा rockchip_crtc_state *rockchip_state;

	rockchip_state = kzalloc(माप(*rockchip_state), GFP_KERNEL);
	अगर (!rockchip_state)
		वापस शून्य;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &rockchip_state->base);
	वापस &rockchip_state->base;
पूर्ण

अटल व्योम vop_crtc_destroy_state(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_crtc_state *state)
अणु
	काष्ठा rockchip_crtc_state *s = to_rockchip_crtc_state(state);

	__drm_atomic_helper_crtc_destroy_state(&s->base);
	kमुक्त(s);
पूर्ण

अटल व्योम vop_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा rockchip_crtc_state *crtc_state =
		kzalloc(माप(*crtc_state), GFP_KERNEL);

	अगर (crtc->state)
		vop_crtc_destroy_state(crtc, crtc->state);

	__drm_atomic_helper_crtc_reset(crtc, &crtc_state->base);
पूर्ण

#अगर_घोषित CONFIG_DRM_ANALOGIX_DP
अटल काष्ठा drm_connector *vop_get_edp_connector(काष्ठा vop *vop)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;

	drm_connector_list_iter_begin(vop->drm_dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP) अणु
			drm_connector_list_iter_end(&conn_iter);
			वापस connector;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस शून्य;
पूर्ण

अटल पूर्णांक vop_crtc_set_crc_source(काष्ठा drm_crtc *crtc,
				   स्थिर अक्षर *source_name)
अणु
	काष्ठा vop *vop = to_vop(crtc);
	काष्ठा drm_connector *connector;
	पूर्णांक ret;

	connector = vop_get_edp_connector(vop);
	अगर (!connector)
		वापस -EINVAL;

	अगर (source_name && म_भेद(source_name, "auto") == 0)
		ret = analogix_dp_start_crc(connector);
	अन्यथा अगर (!source_name)
		ret = analogix_dp_stop_crc(connector);
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक
vop_crtc_verअगरy_crc_source(काष्ठा drm_crtc *crtc, स्थिर अक्षर *source_name,
			   माप_प्रकार *values_cnt)
अणु
	अगर (source_name && म_भेद(source_name, "auto") != 0)
		वापस -EINVAL;

	*values_cnt = 3;
	वापस 0;
पूर्ण

#अन्यथा
अटल पूर्णांक vop_crtc_set_crc_source(काष्ठा drm_crtc *crtc,
				   स्थिर अक्षर *source_name)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
vop_crtc_verअगरy_crc_source(काष्ठा drm_crtc *crtc, स्थिर अक्षर *source_name,
			   माप_प्रकार *values_cnt)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा drm_crtc_funcs vop_crtc_funcs = अणु
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.destroy = vop_crtc_destroy,
	.reset = vop_crtc_reset,
	.atomic_duplicate_state = vop_crtc_duplicate_state,
	.atomic_destroy_state = vop_crtc_destroy_state,
	.enable_vblank = vop_crtc_enable_vblank,
	.disable_vblank = vop_crtc_disable_vblank,
	.set_crc_source = vop_crtc_set_crc_source,
	.verअगरy_crc_source = vop_crtc_verअगरy_crc_source,
पूर्ण;

अटल व्योम vop_fb_unref_worker(काष्ठा drm_flip_work *work, व्योम *val)
अणु
	काष्ठा vop *vop = container_of(work, काष्ठा vop, fb_unref_work);
	काष्ठा drm_framebuffer *fb = val;

	drm_crtc_vblank_put(&vop->crtc);
	drm_framebuffer_put(fb);
पूर्ण

अटल व्योम vop_handle_vblank(काष्ठा vop *vop)
अणु
	काष्ठा drm_device *drm = vop->drm_dev;
	काष्ठा drm_crtc *crtc = &vop->crtc;

	spin_lock(&drm->event_lock);
	अगर (vop->event) अणु
		drm_crtc_send_vblank_event(crtc, vop->event);
		drm_crtc_vblank_put(crtc);
		vop->event = शून्य;
	पूर्ण
	spin_unlock(&drm->event_lock);

	अगर (test_and_clear_bit(VOP_PENDING_FB_UNREF, &vop->pending))
		drm_flip_work_commit(&vop->fb_unref_work, प्रणाली_unbound_wq);
पूर्ण

अटल irqवापस_t vop_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा vop *vop = data;
	काष्ठा drm_crtc *crtc = &vop->crtc;
	uपूर्णांक32_t active_irqs;
	पूर्णांक ret = IRQ_NONE;

	/*
	 * The irq is shared with the iommu. If the runसमय-pm state of the
	 * vop-device is disabled the irq has to be targeted at the iommu.
	 */
	अगर (!pm_runसमय_get_अगर_in_use(vop->dev))
		वापस IRQ_NONE;

	अगर (vop_core_clks_enable(vop)) अणु
		DRM_DEV_ERROR_RATELIMITED(vop->dev, "couldn't enable clocks\n");
		जाओ out;
	पूर्ण

	/*
	 * पूर्णांकerrupt रेजिस्टर has पूर्णांकerrupt status, enable and clear bits, we
	 * must hold irq_lock to aव्योम a race with enable/disable_vblank().
	*/
	spin_lock(&vop->irq_lock);

	active_irqs = VOP_INTR_GET_TYPE(vop, status, INTR_MASK);
	/* Clear all active पूर्णांकerrupt sources */
	अगर (active_irqs)
		VOP_INTR_SET_TYPE(vop, clear, active_irqs, 1);

	spin_unlock(&vop->irq_lock);

	/* This is expected क्रम vop iommu irqs, since the irq is shared */
	अगर (!active_irqs)
		जाओ out_disable;

	अगर (active_irqs & DSP_HOLD_VALID_INTR) अणु
		complete(&vop->dsp_hold_completion);
		active_irqs &= ~DSP_HOLD_VALID_INTR;
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (active_irqs & LINE_FLAG_INTR) अणु
		complete(&vop->line_flag_completion);
		active_irqs &= ~LINE_FLAG_INTR;
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (active_irqs & FS_INTR) अणु
		drm_crtc_handle_vblank(crtc);
		vop_handle_vblank(vop);
		active_irqs &= ~FS_INTR;
		ret = IRQ_HANDLED;
	पूर्ण

	/* Unhandled irqs are spurious. */
	अगर (active_irqs)
		DRM_DEV_ERROR(vop->dev, "Unknown VOP IRQs: %#02x\n",
			      active_irqs);

out_disable:
	vop_core_clks_disable(vop);
out:
	pm_runसमय_put(vop->dev);
	वापस ret;
पूर्ण

अटल व्योम vop_plane_add_properties(काष्ठा drm_plane *plane,
				     स्थिर काष्ठा vop_win_data *win_data)
अणु
	अचिन्हित पूर्णांक flags = 0;

	flags |= VOP_WIN_HAS_REG(win_data, x_mir_en) ? DRM_MODE_REFLECT_X : 0;
	flags |= VOP_WIN_HAS_REG(win_data, y_mir_en) ? DRM_MODE_REFLECT_Y : 0;
	अगर (flags)
		drm_plane_create_rotation_property(plane, DRM_MODE_ROTATE_0,
						   DRM_MODE_ROTATE_0 | flags);
पूर्ण

अटल पूर्णांक vop_create_crtc(काष्ठा vop *vop)
अणु
	स्थिर काष्ठा vop_data *vop_data = vop->data;
	काष्ठा device *dev = vop->dev;
	काष्ठा drm_device *drm_dev = vop->drm_dev;
	काष्ठा drm_plane *primary = शून्य, *cursor = शून्य, *plane, *पंचांगp;
	काष्ठा drm_crtc *crtc = &vop->crtc;
	काष्ठा device_node *port;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * Create drm_plane क्रम primary and cursor planes first, since we need
	 * to pass them to drm_crtc_init_with_planes, which sets the
	 * "possible_crtcs" to the newly initialized crtc.
	 */
	क्रम (i = 0; i < vop_data->win_size; i++) अणु
		काष्ठा vop_win *vop_win = &vop->win[i];
		स्थिर काष्ठा vop_win_data *win_data = vop_win->data;

		अगर (win_data->type != DRM_PLANE_TYPE_PRIMARY &&
		    win_data->type != DRM_PLANE_TYPE_CURSOR)
			जारी;

		ret = drm_universal_plane_init(vop->drm_dev, &vop_win->base,
					       0, &vop_plane_funcs,
					       win_data->phy->data_क्रमmats,
					       win_data->phy->nक्रमmats,
					       win_data->phy->क्रमmat_modअगरiers,
					       win_data->type, शून्य);
		अगर (ret) अणु
			DRM_DEV_ERROR(vop->dev, "failed to init plane %d\n",
				      ret);
			जाओ err_cleanup_planes;
		पूर्ण

		plane = &vop_win->base;
		drm_plane_helper_add(plane, &plane_helper_funcs);
		vop_plane_add_properties(plane, win_data);
		अगर (plane->type == DRM_PLANE_TYPE_PRIMARY)
			primary = plane;
		अन्यथा अगर (plane->type == DRM_PLANE_TYPE_CURSOR)
			cursor = plane;
	पूर्ण

	ret = drm_crtc_init_with_planes(drm_dev, crtc, primary, cursor,
					&vop_crtc_funcs, शून्य);
	अगर (ret)
		जाओ err_cleanup_planes;

	drm_crtc_helper_add(crtc, &vop_crtc_helper_funcs);
	अगर (vop->lut_regs) अणु
		drm_mode_crtc_set_gamma_size(crtc, vop_data->lut_size);
		drm_crtc_enable_color_mgmt(crtc, 0, false, vop_data->lut_size);
	पूर्ण

	/*
	 * Create drm_planes क्रम overlay winकरोws with possible_crtcs restricted
	 * to the newly created crtc.
	 */
	क्रम (i = 0; i < vop_data->win_size; i++) अणु
		काष्ठा vop_win *vop_win = &vop->win[i];
		स्थिर काष्ठा vop_win_data *win_data = vop_win->data;
		अचिन्हित दीर्घ possible_crtcs = drm_crtc_mask(crtc);

		अगर (win_data->type != DRM_PLANE_TYPE_OVERLAY)
			जारी;

		ret = drm_universal_plane_init(vop->drm_dev, &vop_win->base,
					       possible_crtcs,
					       &vop_plane_funcs,
					       win_data->phy->data_क्रमmats,
					       win_data->phy->nक्रमmats,
					       win_data->phy->क्रमmat_modअगरiers,
					       win_data->type, शून्य);
		अगर (ret) अणु
			DRM_DEV_ERROR(vop->dev, "failed to init overlay %d\n",
				      ret);
			जाओ err_cleanup_crtc;
		पूर्ण
		drm_plane_helper_add(&vop_win->base, &plane_helper_funcs);
		vop_plane_add_properties(&vop_win->base, win_data);
	पूर्ण

	port = of_get_child_by_name(dev->of_node, "port");
	अगर (!port) अणु
		DRM_DEV_ERROR(vop->dev, "no port node found in %pOF\n",
			      dev->of_node);
		ret = -ENOENT;
		जाओ err_cleanup_crtc;
	पूर्ण

	drm_flip_work_init(&vop->fb_unref_work, "fb_unref",
			   vop_fb_unref_worker);

	init_completion(&vop->dsp_hold_completion);
	init_completion(&vop->line_flag_completion);
	crtc->port = port;

	ret = drm_self_refresh_helper_init(crtc);
	अगर (ret)
		DRM_DEV_DEBUG_KMS(vop->dev,
			"Failed to init %s with SR helpers %d, ignoring\n",
			crtc->name, ret);

	वापस 0;

err_cleanup_crtc:
	drm_crtc_cleanup(crtc);
err_cleanup_planes:
	list_क्रम_each_entry_safe(plane, पंचांगp, &drm_dev->mode_config.plane_list,
				 head)
		drm_plane_cleanup(plane);
	वापस ret;
पूर्ण

अटल व्योम vop_destroy_crtc(काष्ठा vop *vop)
अणु
	काष्ठा drm_crtc *crtc = &vop->crtc;
	काष्ठा drm_device *drm_dev = vop->drm_dev;
	काष्ठा drm_plane *plane, *पंचांगp;

	drm_self_refresh_helper_cleanup(crtc);

	of_node_put(crtc->port);

	/*
	 * We need to cleanup the planes now.  Why?
	 *
	 * The planes are "&vop->win[i].base".  That means the memory is
	 * all part of the big "struct vop" chunk of memory.  That memory
	 * was devm allocated and associated with this component.  We need to
	 * मुक्त it ourselves beक्रमe vop_unbind() finishes.
	 */
	list_क्रम_each_entry_safe(plane, पंचांगp, &drm_dev->mode_config.plane_list,
				 head)
		vop_plane_destroy(plane);

	/*
	 * Destroy CRTC after vop_plane_destroy() since vop_disable_plane()
	 * references the CRTC.
	 */
	drm_crtc_cleanup(crtc);
	drm_flip_work_cleanup(&vop->fb_unref_work);
पूर्ण

अटल पूर्णांक vop_initial(काष्ठा vop *vop)
अणु
	काष्ठा reset_control *ahb_rst;
	पूर्णांक i, ret;

	vop->hclk = devm_clk_get(vop->dev, "hclk_vop");
	अगर (IS_ERR(vop->hclk)) अणु
		DRM_DEV_ERROR(vop->dev, "failed to get hclk source\n");
		वापस PTR_ERR(vop->hclk);
	पूर्ण
	vop->aclk = devm_clk_get(vop->dev, "aclk_vop");
	अगर (IS_ERR(vop->aclk)) अणु
		DRM_DEV_ERROR(vop->dev, "failed to get aclk source\n");
		वापस PTR_ERR(vop->aclk);
	पूर्ण
	vop->dclk = devm_clk_get(vop->dev, "dclk_vop");
	अगर (IS_ERR(vop->dclk)) अणु
		DRM_DEV_ERROR(vop->dev, "failed to get dclk source\n");
		वापस PTR_ERR(vop->dclk);
	पूर्ण

	ret = pm_runसमय_get_sync(vop->dev);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(vop->dev, "failed to get pm runtime: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare(vop->dclk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(vop->dev, "failed to prepare dclk\n");
		जाओ err_put_pm_runसमय;
	पूर्ण

	/* Enable both the hclk and aclk to setup the vop */
	ret = clk_prepare_enable(vop->hclk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(vop->dev, "failed to prepare/enable hclk\n");
		जाओ err_unprepare_dclk;
	पूर्ण

	ret = clk_prepare_enable(vop->aclk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(vop->dev, "failed to prepare/enable aclk\n");
		जाओ err_disable_hclk;
	पूर्ण

	/*
	 * करो hclk_reset, reset all vop रेजिस्टरs.
	 */
	ahb_rst = devm_reset_control_get(vop->dev, "ahb");
	अगर (IS_ERR(ahb_rst)) अणु
		DRM_DEV_ERROR(vop->dev, "failed to get ahb reset\n");
		ret = PTR_ERR(ahb_rst);
		जाओ err_disable_aclk;
	पूर्ण
	reset_control_निश्चित(ahb_rst);
	usleep_range(10, 20);
	reset_control_deनिश्चित(ahb_rst);

	VOP_INTR_SET_TYPE(vop, clear, INTR_MASK, 1);
	VOP_INTR_SET_TYPE(vop, enable, INTR_MASK, 0);

	क्रम (i = 0; i < vop->len; i += माप(u32))
		vop->regsbak[i / 4] = पढ़ोl_relaxed(vop->regs + i);

	VOP_REG_SET(vop, misc, global_regकरोne_en, 1);
	VOP_REG_SET(vop, common, dsp_blank, 0);

	क्रम (i = 0; i < vop->data->win_size; i++) अणु
		काष्ठा vop_win *vop_win = &vop->win[i];
		स्थिर काष्ठा vop_win_data *win = vop_win->data;
		पूर्णांक channel = i * 2 + 1;

		VOP_WIN_SET(vop, win, channel, (channel + 1) << 4 | channel);
		vop_win_disable(vop, vop_win);
		VOP_WIN_SET(vop, win, gate, 1);
	पूर्ण

	vop_cfg_करोne(vop);

	/*
	 * करो dclk_reset, let all config take affect.
	 */
	vop->dclk_rst = devm_reset_control_get(vop->dev, "dclk");
	अगर (IS_ERR(vop->dclk_rst)) अणु
		DRM_DEV_ERROR(vop->dev, "failed to get dclk reset\n");
		ret = PTR_ERR(vop->dclk_rst);
		जाओ err_disable_aclk;
	पूर्ण
	reset_control_निश्चित(vop->dclk_rst);
	usleep_range(10, 20);
	reset_control_deनिश्चित(vop->dclk_rst);

	clk_disable(vop->hclk);
	clk_disable(vop->aclk);

	vop->is_enabled = false;

	pm_runसमय_put_sync(vop->dev);

	वापस 0;

err_disable_aclk:
	clk_disable_unprepare(vop->aclk);
err_disable_hclk:
	clk_disable_unprepare(vop->hclk);
err_unprepare_dclk:
	clk_unprepare(vop->dclk);
err_put_pm_runसमय:
	pm_runसमय_put_sync(vop->dev);
	वापस ret;
पूर्ण

/*
 * Initialize the vop->win array elements.
 */
अटल व्योम vop_win_init(काष्ठा vop *vop)
अणु
	स्थिर काष्ठा vop_data *vop_data = vop->data;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < vop_data->win_size; i++) अणु
		काष्ठा vop_win *vop_win = &vop->win[i];
		स्थिर काष्ठा vop_win_data *win_data = &vop_data->win[i];

		vop_win->data = win_data;
		vop_win->vop = vop;

		अगर (vop_data->win_yuv2yuv)
			vop_win->yuv2yuv_data = &vop_data->win_yuv2yuv[i];
	पूर्ण
पूर्ण

/**
 * rockchip_drm_रुको_vact_end
 * @crtc: CRTC to enable line flag
 * @msसमयout: millisecond क्रम समयout
 *
 * Wait क्रम vact_end line flag irq or समयout.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक rockchip_drm_रुको_vact_end(काष्ठा drm_crtc *crtc, अचिन्हित पूर्णांक msसमयout)
अणु
	काष्ठा vop *vop = to_vop(crtc);
	अचिन्हित दीर्घ jअगरfies_left;
	पूर्णांक ret = 0;

	अगर (!crtc || !vop->is_enabled)
		वापस -ENODEV;

	mutex_lock(&vop->vop_lock);
	अगर (msसमयout <= 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (vop_line_flag_irq_is_enabled(vop)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	reinit_completion(&vop->line_flag_completion);
	vop_line_flag_irq_enable(vop);

	jअगरfies_left = रुको_क्रम_completion_समयout(&vop->line_flag_completion,
						   msecs_to_jअगरfies(msसमयout));
	vop_line_flag_irq_disable(vop);

	अगर (jअगरfies_left == 0) अणु
		DRM_DEV_ERROR(vop->dev, "Timeout waiting for IRQ\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&vop->vop_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rockchip_drm_रुको_vact_end);

अटल पूर्णांक vop_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	स्थिर काष्ठा vop_data *vop_data;
	काष्ठा drm_device *drm_dev = data;
	काष्ठा vop *vop;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	vop_data = of_device_get_match_data(dev);
	अगर (!vop_data)
		वापस -ENODEV;

	/* Allocate vop काष्ठा and its vop_win array */
	vop = devm_kzalloc(dev, काष्ठा_size(vop, win, vop_data->win_size),
			   GFP_KERNEL);
	अगर (!vop)
		वापस -ENOMEM;

	vop->dev = dev;
	vop->data = vop_data;
	vop->drm_dev = drm_dev;
	dev_set_drvdata(dev, vop);

	vop_win_init(vop);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	vop->len = resource_size(res);
	vop->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(vop->regs))
		वापस PTR_ERR(vop->regs);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (res) अणु
		अगर (!vop_data->lut_size) अणु
			DRM_DEV_ERROR(dev, "no gamma LUT size defined\n");
			वापस -EINVAL;
		पूर्ण
		vop->lut_regs = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(vop->lut_regs))
			वापस PTR_ERR(vop->lut_regs);
	पूर्ण

	vop->regsbak = devm_kzalloc(dev, vop->len, GFP_KERNEL);
	अगर (!vop->regsbak)
		वापस -ENOMEM;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		DRM_DEV_ERROR(dev, "cannot find irq for vop\n");
		वापस irq;
	पूर्ण
	vop->irq = (अचिन्हित पूर्णांक)irq;

	spin_lock_init(&vop->reg_lock);
	spin_lock_init(&vop->irq_lock);
	mutex_init(&vop->vop_lock);

	ret = vop_create_crtc(vop);
	अगर (ret)
		वापस ret;

	pm_runसमय_enable(&pdev->dev);

	ret = vop_initial(vop);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(&pdev->dev,
			      "cannot initial vop dev - err %d\n", ret);
		जाओ err_disable_pm_runसमय;
	पूर्ण

	ret = devm_request_irq(dev, vop->irq, vop_isr,
			       IRQF_SHARED, dev_name(dev), vop);
	अगर (ret)
		जाओ err_disable_pm_runसमय;

	अगर (vop->data->feature & VOP_FEATURE_INTERNAL_RGB) अणु
		vop->rgb = rockchip_rgb_init(dev, &vop->crtc, vop->drm_dev);
		अगर (IS_ERR(vop->rgb)) अणु
			ret = PTR_ERR(vop->rgb);
			जाओ err_disable_pm_runसमय;
		पूर्ण
	पूर्ण

	वापस 0;

err_disable_pm_runसमय:
	pm_runसमय_disable(&pdev->dev);
	vop_destroy_crtc(vop);
	वापस ret;
पूर्ण

अटल व्योम vop_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा vop *vop = dev_get_drvdata(dev);

	अगर (vop->rgb)
		rockchip_rgb_fini(vop->rgb);

	pm_runसमय_disable(dev);
	vop_destroy_crtc(vop);

	clk_unprepare(vop->aclk);
	clk_unprepare(vop->hclk);
	clk_unprepare(vop->dclk);
पूर्ण

स्थिर काष्ठा component_ops vop_component_ops = अणु
	.bind = vop_bind,
	.unbind = vop_unbind,
पूर्ण;
EXPORT_SYMBOL_GPL(vop_component_ops);
