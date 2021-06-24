<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:Mark Yao <mark.yao@rock-chips.com>
 */

#समावेश <linux/component.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "rockchip_drm_vop.h"
#समावेश "rockchip_vop_reg.h"
#समावेश "rockchip_drm_drv.h"

#घोषणा _VOP_REG(off, _mask, _shअगरt, _ग_लिखो_mask, _relaxed) \
		अणु \
		 .offset = off, \
		 .mask = _mask, \
		 .shअगरt = _shअगरt, \
		 .ग_लिखो_mask = _ग_लिखो_mask, \
		 .relaxed = _relaxed, \
		पूर्ण

#घोषणा VOP_REG(off, _mask, _shअगरt) \
		_VOP_REG(off, _mask, _shअगरt, false, true)

#घोषणा VOP_REG_SYNC(off, _mask, _shअगरt) \
		_VOP_REG(off, _mask, _shअगरt, false, false)

#घोषणा VOP_REG_MASK_SYNC(off, _mask, _shअगरt) \
		_VOP_REG(off, _mask, _shअगरt, true, false)

अटल स्थिर uपूर्णांक32_t क्रमmats_win_full[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_BGR888,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_BGR565,
	DRM_FORMAT_NV12,
	DRM_FORMAT_NV16,
	DRM_FORMAT_NV24,
पूर्ण;

अटल स्थिर uपूर्णांक64_t क्रमmat_modअगरiers_win_full[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID,
पूर्ण;

अटल स्थिर uपूर्णांक64_t क्रमmat_modअगरiers_win_full_afbc[] = अणु
	ROCKCHIP_AFBC_MOD,
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID,
पूर्ण;

अटल स्थिर uपूर्णांक32_t क्रमmats_win_lite[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_BGR888,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_BGR565,
पूर्ण;

अटल स्थिर uपूर्णांक64_t क्रमmat_modअगरiers_win_lite[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID,
पूर्ण;

अटल स्थिर काष्ठा vop_scl_regs rk3036_win_scl = अणु
	.scale_yrgb_x = VOP_REG(RK3036_WIN0_SCL_FACTOR_YRGB, 0xffff, 0x0),
	.scale_yrgb_y = VOP_REG(RK3036_WIN0_SCL_FACTOR_YRGB, 0xffff, 16),
	.scale_cbcr_x = VOP_REG(RK3036_WIN0_SCL_FACTOR_CBR, 0xffff, 0x0),
	.scale_cbcr_y = VOP_REG(RK3036_WIN0_SCL_FACTOR_CBR, 0xffff, 16),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy rk3036_win0_data = अणु
	.scl = &rk3036_win_scl,
	.data_क्रमmats = क्रमmats_win_full,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_full),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_full,
	.enable = VOP_REG(RK3036_SYS_CTRL, 0x1, 0),
	.क्रमmat = VOP_REG(RK3036_SYS_CTRL, 0x7, 3),
	.rb_swap = VOP_REG(RK3036_SYS_CTRL, 0x1, 15),
	.act_info = VOP_REG(RK3036_WIN0_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_REG(RK3036_WIN0_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_REG(RK3036_WIN0_DSP_ST, 0x1fff1fff, 0),
	.yrgb_mst = VOP_REG(RK3036_WIN0_YRGB_MST, 0xffffffff, 0),
	.uv_mst = VOP_REG(RK3036_WIN0_CBR_MST, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(RK3036_WIN0_VIR, 0xffff, 0),
	.uv_vir = VOP_REG(RK3036_WIN0_VIR, 0x1fff, 16),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy rk3036_win1_data = अणु
	.data_क्रमmats = क्रमmats_win_lite,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_lite),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_lite,
	.enable = VOP_REG(RK3036_SYS_CTRL, 0x1, 1),
	.क्रमmat = VOP_REG(RK3036_SYS_CTRL, 0x7, 6),
	.rb_swap = VOP_REG(RK3036_SYS_CTRL, 0x1, 19),
	.act_info = VOP_REG(RK3036_WIN1_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_REG(RK3036_WIN1_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_REG(RK3036_WIN1_DSP_ST, 0x1fff1fff, 0),
	.yrgb_mst = VOP_REG(RK3036_WIN1_MST, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(RK3036_WIN1_VIR, 0xffff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_win_data rk3036_vop_win_data[] = अणु
	अणु .base = 0x00, .phy = &rk3036_win0_data,
	  .type = DRM_PLANE_TYPE_PRIMARY पूर्ण,
	अणु .base = 0x00, .phy = &rk3036_win1_data,
	  .type = DRM_PLANE_TYPE_CURSOR पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक rk3036_vop_पूर्णांकrs[] = अणु
	DSP_HOLD_VALID_INTR,
	FS_INTR,
	LINE_FLAG_INTR,
	BUS_ERROR_INTR,
पूर्ण;

अटल स्थिर काष्ठा vop_पूर्णांकr rk3036_पूर्णांकr = अणु
	.पूर्णांकrs = rk3036_vop_पूर्णांकrs,
	.nपूर्णांकrs = ARRAY_SIZE(rk3036_vop_पूर्णांकrs),
	.line_flag_num[0] = VOP_REG(RK3036_INT_STATUS, 0xfff, 12),
	.status = VOP_REG_SYNC(RK3036_INT_STATUS, 0xf, 0),
	.enable = VOP_REG_SYNC(RK3036_INT_STATUS, 0xf, 4),
	.clear = VOP_REG_SYNC(RK3036_INT_STATUS, 0xf, 8),
पूर्ण;

अटल स्थिर काष्ठा vop_modeset rk3036_modeset = अणु
	.htotal_pw = VOP_REG(RK3036_DSP_HTOTAL_HS_END, 0x1fff1fff, 0),
	.hact_st_end = VOP_REG(RK3036_DSP_HACT_ST_END, 0x1fff1fff, 0),
	.vtotal_pw = VOP_REG(RK3036_DSP_VTOTAL_VS_END, 0x1fff1fff, 0),
	.vact_st_end = VOP_REG(RK3036_DSP_VACT_ST_END, 0x1fff1fff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_output rk3036_output = अणु
	.pin_pol = VOP_REG(RK3036_DSP_CTRL0, 0xf, 4),
पूर्ण;

अटल स्थिर काष्ठा vop_common rk3036_common = अणु
	.standby = VOP_REG_SYNC(RK3036_SYS_CTRL, 0x1, 30),
	.out_mode = VOP_REG(RK3036_DSP_CTRL0, 0xf, 0),
	.dsp_blank = VOP_REG(RK3036_DSP_CTRL1, 0x1, 24),
	.dither_करोwn_sel = VOP_REG(RK3036_DSP_CTRL0, 0x1, 27),
	.dither_करोwn_en = VOP_REG(RK3036_DSP_CTRL0, 0x1, 11),
	.dither_करोwn_mode = VOP_REG(RK3036_DSP_CTRL0, 0x1, 10),
	.cfg_करोne = VOP_REG_SYNC(RK3036_REG_CFG_DONE, 0x1, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_data rk3036_vop = अणु
	.पूर्णांकr = &rk3036_पूर्णांकr,
	.common = &rk3036_common,
	.modeset = &rk3036_modeset,
	.output = &rk3036_output,
	.win = rk3036_vop_win_data,
	.win_size = ARRAY_SIZE(rk3036_vop_win_data),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy rk3126_win1_data = अणु
	.data_क्रमmats = क्रमmats_win_lite,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_lite),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_lite,
	.enable = VOP_REG(RK3036_SYS_CTRL, 0x1, 1),
	.क्रमmat = VOP_REG(RK3036_SYS_CTRL, 0x7, 6),
	.rb_swap = VOP_REG(RK3036_SYS_CTRL, 0x1, 19),
	.dsp_info = VOP_REG(RK3126_WIN1_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_REG(RK3126_WIN1_DSP_ST, 0x1fff1fff, 0),
	.yrgb_mst = VOP_REG(RK3126_WIN1_MST, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(RK3036_WIN1_VIR, 0xffff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_win_data rk3126_vop_win_data[] = अणु
	अणु .base = 0x00, .phy = &rk3036_win0_data,
	  .type = DRM_PLANE_TYPE_PRIMARY पूर्ण,
	अणु .base = 0x00, .phy = &rk3126_win1_data,
	  .type = DRM_PLANE_TYPE_CURSOR पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vop_data rk3126_vop = अणु
	.पूर्णांकr = &rk3036_पूर्णांकr,
	.common = &rk3036_common,
	.modeset = &rk3036_modeset,
	.output = &rk3036_output,
	.win = rk3126_vop_win_data,
	.win_size = ARRAY_SIZE(rk3126_vop_win_data),
पूर्ण;

अटल स्थिर पूर्णांक px30_vop_पूर्णांकrs[] = अणु
	FS_INTR,
	0, 0,
	LINE_FLAG_INTR,
	0,
	BUS_ERROR_INTR,
	0, 0,
	DSP_HOLD_VALID_INTR,
पूर्ण;

अटल स्थिर काष्ठा vop_पूर्णांकr px30_पूर्णांकr = अणु
	.पूर्णांकrs = px30_vop_पूर्णांकrs,
	.nपूर्णांकrs = ARRAY_SIZE(px30_vop_पूर्णांकrs),
	.line_flag_num[0] = VOP_REG(PX30_LINE_FLAG, 0xfff, 0),
	.status = VOP_REG_MASK_SYNC(PX30_INTR_STATUS, 0xffff, 0),
	.enable = VOP_REG_MASK_SYNC(PX30_INTR_EN, 0xffff, 0),
	.clear = VOP_REG_MASK_SYNC(PX30_INTR_CLEAR, 0xffff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_common px30_common = अणु
	.standby = VOP_REG_SYNC(PX30_SYS_CTRL2, 0x1, 1),
	.out_mode = VOP_REG(PX30_DSP_CTRL2, 0xf, 16),
	.dsp_blank = VOP_REG(PX30_DSP_CTRL2, 0x1, 14),
	.dither_करोwn_en = VOP_REG(PX30_DSP_CTRL2, 0x1, 8),
	.dither_करोwn_sel = VOP_REG(PX30_DSP_CTRL2, 0x1, 7),
	.dither_करोwn_mode = VOP_REG(PX30_DSP_CTRL2, 0x1, 6),
	.cfg_करोne = VOP_REG_SYNC(PX30_REG_CFG_DONE, 0x1, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_modeset px30_modeset = अणु
	.htotal_pw = VOP_REG(PX30_DSP_HTOTAL_HS_END, 0x0fff0fff, 0),
	.hact_st_end = VOP_REG(PX30_DSP_HACT_ST_END, 0x0fff0fff, 0),
	.vtotal_pw = VOP_REG(PX30_DSP_VTOTAL_VS_END, 0x0fff0fff, 0),
	.vact_st_end = VOP_REG(PX30_DSP_VACT_ST_END, 0x0fff0fff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_output px30_output = अणु
	.rgb_dclk_pol = VOP_REG(PX30_DSP_CTRL0, 0x1, 1),
	.rgb_pin_pol = VOP_REG(PX30_DSP_CTRL0, 0x7, 2),
	.rgb_en = VOP_REG(PX30_DSP_CTRL0, 0x1, 0),
	.mipi_dclk_pol = VOP_REG(PX30_DSP_CTRL0, 0x1, 25),
	.mipi_pin_pol = VOP_REG(PX30_DSP_CTRL0, 0x7, 26),
	.mipi_en = VOP_REG(PX30_DSP_CTRL0, 0x1, 24),
पूर्ण;

अटल स्थिर काष्ठा vop_scl_regs px30_win_scl = अणु
	.scale_yrgb_x = VOP_REG(PX30_WIN0_SCL_FACTOR_YRGB, 0xffff, 0x0),
	.scale_yrgb_y = VOP_REG(PX30_WIN0_SCL_FACTOR_YRGB, 0xffff, 16),
	.scale_cbcr_x = VOP_REG(PX30_WIN0_SCL_FACTOR_CBR, 0xffff, 0x0),
	.scale_cbcr_y = VOP_REG(PX30_WIN0_SCL_FACTOR_CBR, 0xffff, 16),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy px30_win0_data = अणु
	.scl = &px30_win_scl,
	.data_क्रमmats = क्रमmats_win_full,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_full),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_full,
	.enable = VOP_REG(PX30_WIN0_CTRL0, 0x1, 0),
	.क्रमmat = VOP_REG(PX30_WIN0_CTRL0, 0x7, 1),
	.rb_swap = VOP_REG(PX30_WIN0_CTRL0, 0x1, 12),
	.act_info = VOP_REG(PX30_WIN0_ACT_INFO, 0xffffffff, 0),
	.dsp_info = VOP_REG(PX30_WIN0_DSP_INFO, 0xffffffff, 0),
	.dsp_st = VOP_REG(PX30_WIN0_DSP_ST, 0xffffffff, 0),
	.yrgb_mst = VOP_REG(PX30_WIN0_YRGB_MST0, 0xffffffff, 0),
	.uv_mst = VOP_REG(PX30_WIN0_CBR_MST0, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(PX30_WIN0_VIR, 0x1fff, 0),
	.uv_vir = VOP_REG(PX30_WIN0_VIR, 0x1fff, 16),
	.alpha_pre_mul = VOP_REG(PX30_WIN0_ALPHA_CTRL, 0x1, 2),
	.alpha_mode = VOP_REG(PX30_WIN0_ALPHA_CTRL, 0x1, 1),
	.alpha_en = VOP_REG(PX30_WIN0_ALPHA_CTRL, 0x1, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy px30_win1_data = अणु
	.data_क्रमmats = क्रमmats_win_lite,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_lite),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_lite,
	.enable = VOP_REG(PX30_WIN1_CTRL0, 0x1, 0),
	.क्रमmat = VOP_REG(PX30_WIN1_CTRL0, 0x7, 4),
	.rb_swap = VOP_REG(PX30_WIN1_CTRL0, 0x1, 12),
	.dsp_info = VOP_REG(PX30_WIN1_DSP_INFO, 0xffffffff, 0),
	.dsp_st = VOP_REG(PX30_WIN1_DSP_ST, 0xffffffff, 0),
	.yrgb_mst = VOP_REG(PX30_WIN1_MST, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(PX30_WIN1_VIR, 0x1fff, 0),
	.alpha_pre_mul = VOP_REG(PX30_WIN1_ALPHA_CTRL, 0x1, 2),
	.alpha_mode = VOP_REG(PX30_WIN1_ALPHA_CTRL, 0x1, 1),
	.alpha_en = VOP_REG(PX30_WIN1_ALPHA_CTRL, 0x1, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy px30_win2_data = अणु
	.data_क्रमmats = क्रमmats_win_lite,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_lite),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_lite,
	.gate = VOP_REG(PX30_WIN2_CTRL0, 0x1, 4),
	.enable = VOP_REG(PX30_WIN2_CTRL0, 0x1, 0),
	.क्रमmat = VOP_REG(PX30_WIN2_CTRL0, 0x3, 5),
	.rb_swap = VOP_REG(PX30_WIN2_CTRL0, 0x1, 20),
	.dsp_info = VOP_REG(PX30_WIN2_DSP_INFO0, 0x0fff0fff, 0),
	.dsp_st = VOP_REG(PX30_WIN2_DSP_ST0, 0x1fff1fff, 0),
	.yrgb_mst = VOP_REG(PX30_WIN2_MST0, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(PX30_WIN2_VIR0_1, 0x1fff, 0),
	.alpha_pre_mul = VOP_REG(PX30_WIN2_ALPHA_CTRL, 0x1, 2),
	.alpha_mode = VOP_REG(PX30_WIN2_ALPHA_CTRL, 0x1, 1),
	.alpha_en = VOP_REG(PX30_WIN2_ALPHA_CTRL, 0x1, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_win_data px30_vop_big_win_data[] = अणु
	अणु .base = 0x00, .phy = &px30_win0_data,
	  .type = DRM_PLANE_TYPE_PRIMARY पूर्ण,
	अणु .base = 0x00, .phy = &px30_win1_data,
	  .type = DRM_PLANE_TYPE_OVERLAY पूर्ण,
	अणु .base = 0x00, .phy = &px30_win2_data,
	  .type = DRM_PLANE_TYPE_CURSOR पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vop_data px30_vop_big = अणु
	.पूर्णांकr = &px30_पूर्णांकr,
	.feature = VOP_FEATURE_INTERNAL_RGB,
	.common = &px30_common,
	.modeset = &px30_modeset,
	.output = &px30_output,
	.win = px30_vop_big_win_data,
	.win_size = ARRAY_SIZE(px30_vop_big_win_data),
पूर्ण;

अटल स्थिर काष्ठा vop_win_data px30_vop_lit_win_data[] = अणु
	अणु .base = 0x00, .phy = &px30_win1_data,
	  .type = DRM_PLANE_TYPE_PRIMARY पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vop_data px30_vop_lit = अणु
	.पूर्णांकr = &px30_पूर्णांकr,
	.feature = VOP_FEATURE_INTERNAL_RGB,
	.common = &px30_common,
	.modeset = &px30_modeset,
	.output = &px30_output,
	.win = px30_vop_lit_win_data,
	.win_size = ARRAY_SIZE(px30_vop_lit_win_data),
पूर्ण;

अटल स्थिर काष्ठा vop_scl_regs rk3066_win_scl = अणु
	.scale_yrgb_x = VOP_REG(RK3066_WIN0_SCL_FACTOR_YRGB, 0xffff, 0x0),
	.scale_yrgb_y = VOP_REG(RK3066_WIN0_SCL_FACTOR_YRGB, 0xffff, 16),
	.scale_cbcr_x = VOP_REG(RK3066_WIN0_SCL_FACTOR_CBR, 0xffff, 0x0),
	.scale_cbcr_y = VOP_REG(RK3066_WIN0_SCL_FACTOR_CBR, 0xffff, 16),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy rk3066_win0_data = अणु
	.scl = &rk3066_win_scl,
	.data_क्रमmats = क्रमmats_win_full,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_full),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_full,
	.enable = VOP_REG(RK3066_SYS_CTRL1, 0x1, 0),
	.क्रमmat = VOP_REG(RK3066_SYS_CTRL0, 0x7, 4),
	.rb_swap = VOP_REG(RK3066_SYS_CTRL0, 0x1, 19),
	.act_info = VOP_REG(RK3066_WIN0_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_REG(RK3066_WIN0_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_REG(RK3066_WIN0_DSP_ST, 0x1fff1fff, 0),
	.yrgb_mst = VOP_REG(RK3066_WIN0_YRGB_MST0, 0xffffffff, 0),
	.uv_mst = VOP_REG(RK3066_WIN0_CBR_MST0, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(RK3066_WIN0_VIR, 0xffff, 0),
	.uv_vir = VOP_REG(RK3066_WIN0_VIR, 0x1fff, 16),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy rk3066_win1_data = अणु
	.scl = &rk3066_win_scl,
	.data_क्रमmats = क्रमmats_win_full,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_full),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_full,
	.enable = VOP_REG(RK3066_SYS_CTRL1, 0x1, 1),
	.क्रमmat = VOP_REG(RK3066_SYS_CTRL0, 0x7, 7),
	.rb_swap = VOP_REG(RK3066_SYS_CTRL0, 0x1, 23),
	.act_info = VOP_REG(RK3066_WIN1_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_REG(RK3066_WIN1_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_REG(RK3066_WIN1_DSP_ST, 0x1fff1fff, 0),
	.yrgb_mst = VOP_REG(RK3066_WIN1_YRGB_MST, 0xffffffff, 0),
	.uv_mst = VOP_REG(RK3066_WIN1_CBR_MST, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(RK3066_WIN1_VIR, 0xffff, 0),
	.uv_vir = VOP_REG(RK3066_WIN1_VIR, 0x1fff, 16),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy rk3066_win2_data = अणु
	.data_क्रमmats = क्रमmats_win_lite,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_lite),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_lite,
	.enable = VOP_REG(RK3066_SYS_CTRL1, 0x1, 2),
	.क्रमmat = VOP_REG(RK3066_SYS_CTRL0, 0x7, 10),
	.rb_swap = VOP_REG(RK3066_SYS_CTRL0, 0x1, 27),
	.dsp_info = VOP_REG(RK3066_WIN2_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_REG(RK3066_WIN2_DSP_ST, 0x1fff1fff, 0),
	.yrgb_mst = VOP_REG(RK3066_WIN2_MST, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(RK3066_WIN2_VIR, 0xffff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_modeset rk3066_modeset = अणु
	.htotal_pw = VOP_REG(RK3066_DSP_HTOTAL_HS_END, 0x1fff1fff, 0),
	.hact_st_end = VOP_REG(RK3066_DSP_HACT_ST_END, 0x1fff1fff, 0),
	.vtotal_pw = VOP_REG(RK3066_DSP_VTOTAL_VS_END, 0x1fff1fff, 0),
	.vact_st_end = VOP_REG(RK3066_DSP_VACT_ST_END, 0x1fff1fff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_output rk3066_output = अणु
	.pin_pol = VOP_REG(RK3066_DSP_CTRL0, 0x7, 4),
पूर्ण;

अटल स्थिर काष्ठा vop_common rk3066_common = अणु
	.standby = VOP_REG(RK3066_SYS_CTRL0, 0x1, 1),
	.out_mode = VOP_REG(RK3066_DSP_CTRL0, 0xf, 0),
	.cfg_करोne = VOP_REG(RK3066_REG_CFG_DONE, 0x1, 0),
	.dither_करोwn_en = VOP_REG(RK3066_DSP_CTRL0, 0x1, 11),
	.dither_करोwn_mode = VOP_REG(RK3066_DSP_CTRL0, 0x1, 10),
	.dsp_blank = VOP_REG(RK3066_DSP_CTRL1, 0x1, 24),
पूर्ण;

अटल स्थिर काष्ठा vop_win_data rk3066_vop_win_data[] = अणु
	अणु .base = 0x00, .phy = &rk3066_win0_data,
	  .type = DRM_PLANE_TYPE_PRIMARY पूर्ण,
	अणु .base = 0x00, .phy = &rk3066_win1_data,
	  .type = DRM_PLANE_TYPE_OVERLAY पूर्ण,
	अणु .base = 0x00, .phy = &rk3066_win2_data,
	  .type = DRM_PLANE_TYPE_CURSOR पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक rk3066_vop_पूर्णांकrs[] = अणु
	/*
	 * hs_start पूर्णांकerrupt fires at frame-start, so serves
	 * the same purpose as dsp_hold in the driver.
	 */
	DSP_HOLD_VALID_INTR,
	FS_INTR,
	LINE_FLAG_INTR,
	BUS_ERROR_INTR,
पूर्ण;

अटल स्थिर काष्ठा vop_पूर्णांकr rk3066_पूर्णांकr = अणु
	.पूर्णांकrs = rk3066_vop_पूर्णांकrs,
	.nपूर्णांकrs = ARRAY_SIZE(rk3066_vop_पूर्णांकrs),
	.line_flag_num[0] = VOP_REG(RK3066_INT_STATUS, 0xfff, 12),
	.status = VOP_REG(RK3066_INT_STATUS, 0xf, 0),
	.enable = VOP_REG(RK3066_INT_STATUS, 0xf, 4),
	.clear = VOP_REG(RK3066_INT_STATUS, 0xf, 8),
पूर्ण;

अटल स्थिर काष्ठा vop_data rk3066_vop = अणु
	.version = VOP_VERSION(2, 1),
	.पूर्णांकr = &rk3066_पूर्णांकr,
	.common = &rk3066_common,
	.modeset = &rk3066_modeset,
	.output = &rk3066_output,
	.win = rk3066_vop_win_data,
	.win_size = ARRAY_SIZE(rk3066_vop_win_data),
पूर्ण;

अटल स्थिर काष्ठा vop_scl_regs rk3188_win_scl = अणु
	.scale_yrgb_x = VOP_REG(RK3188_WIN0_SCL_FACTOR_YRGB, 0xffff, 0x0),
	.scale_yrgb_y = VOP_REG(RK3188_WIN0_SCL_FACTOR_YRGB, 0xffff, 16),
	.scale_cbcr_x = VOP_REG(RK3188_WIN0_SCL_FACTOR_CBR, 0xffff, 0x0),
	.scale_cbcr_y = VOP_REG(RK3188_WIN0_SCL_FACTOR_CBR, 0xffff, 16),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy rk3188_win0_data = अणु
	.scl = &rk3188_win_scl,
	.data_क्रमmats = क्रमmats_win_full,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_full),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_full,
	.enable = VOP_REG(RK3188_SYS_CTRL, 0x1, 0),
	.क्रमmat = VOP_REG(RK3188_SYS_CTRL, 0x7, 3),
	.rb_swap = VOP_REG(RK3188_SYS_CTRL, 0x1, 15),
	.act_info = VOP_REG(RK3188_WIN0_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_REG(RK3188_WIN0_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_REG(RK3188_WIN0_DSP_ST, 0x1fff1fff, 0),
	.yrgb_mst = VOP_REG(RK3188_WIN0_YRGB_MST0, 0xffffffff, 0),
	.uv_mst = VOP_REG(RK3188_WIN0_CBR_MST0, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(RK3188_WIN_VIR, 0x1fff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy rk3188_win1_data = अणु
	.data_क्रमmats = क्रमmats_win_lite,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_lite),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_lite,
	.enable = VOP_REG(RK3188_SYS_CTRL, 0x1, 1),
	.क्रमmat = VOP_REG(RK3188_SYS_CTRL, 0x7, 6),
	.rb_swap = VOP_REG(RK3188_SYS_CTRL, 0x1, 19),
	/* no act_info on winकरोw1 */
	.dsp_info = VOP_REG(RK3188_WIN1_DSP_INFO, 0x07ff07ff, 0),
	.dsp_st = VOP_REG(RK3188_WIN1_DSP_ST, 0x0fff0fff, 0),
	.yrgb_mst = VOP_REG(RK3188_WIN1_MST, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(RK3188_WIN_VIR, 0x1fff, 16),
पूर्ण;

अटल स्थिर काष्ठा vop_modeset rk3188_modeset = अणु
	.htotal_pw = VOP_REG(RK3188_DSP_HTOTAL_HS_END, 0x0fff0fff, 0),
	.hact_st_end = VOP_REG(RK3188_DSP_HACT_ST_END, 0x0fff0fff, 0),
	.vtotal_pw = VOP_REG(RK3188_DSP_VTOTAL_VS_END, 0x0fff0fff, 0),
	.vact_st_end = VOP_REG(RK3188_DSP_VACT_ST_END, 0x0fff0fff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_output rk3188_output = अणु
	.pin_pol = VOP_REG(RK3188_DSP_CTRL0, 0xf, 4),
पूर्ण;

अटल स्थिर काष्ठा vop_common rk3188_common = अणु
	.gate_en = VOP_REG(RK3188_SYS_CTRL, 0x1, 31),
	.standby = VOP_REG(RK3188_SYS_CTRL, 0x1, 30),
	.out_mode = VOP_REG(RK3188_DSP_CTRL0, 0xf, 0),
	.cfg_करोne = VOP_REG(RK3188_REG_CFG_DONE, 0x1, 0),
	.dither_करोwn_sel = VOP_REG(RK3188_DSP_CTRL0, 0x1, 27),
	.dither_करोwn_en = VOP_REG(RK3188_DSP_CTRL0, 0x1, 11),
	.dither_करोwn_mode = VOP_REG(RK3188_DSP_CTRL0, 0x1, 10),
	.dsp_blank = VOP_REG(RK3188_DSP_CTRL1, 0x3, 24),
पूर्ण;

अटल स्थिर काष्ठा vop_win_data rk3188_vop_win_data[] = अणु
	अणु .base = 0x00, .phy = &rk3188_win0_data,
	  .type = DRM_PLANE_TYPE_PRIMARY पूर्ण,
	अणु .base = 0x00, .phy = &rk3188_win1_data,
	  .type = DRM_PLANE_TYPE_CURSOR पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक rk3188_vop_पूर्णांकrs[] = अणु
	/*
	 * hs_start पूर्णांकerrupt fires at frame-start, so serves
	 * the same purpose as dsp_hold in the driver.
	 */
	DSP_HOLD_VALID_INTR,
	FS_INTR,
	LINE_FLAG_INTR,
	BUS_ERROR_INTR,
पूर्ण;

अटल स्थिर काष्ठा vop_पूर्णांकr rk3188_vop_पूर्णांकr = अणु
	.पूर्णांकrs = rk3188_vop_पूर्णांकrs,
	.nपूर्णांकrs = ARRAY_SIZE(rk3188_vop_पूर्णांकrs),
	.line_flag_num[0] = VOP_REG(RK3188_INT_STATUS, 0xfff, 12),
	.status = VOP_REG(RK3188_INT_STATUS, 0xf, 0),
	.enable = VOP_REG(RK3188_INT_STATUS, 0xf, 4),
	.clear = VOP_REG(RK3188_INT_STATUS, 0xf, 8),
पूर्ण;

अटल स्थिर काष्ठा vop_data rk3188_vop = अणु
	.पूर्णांकr = &rk3188_vop_पूर्णांकr,
	.common = &rk3188_common,
	.modeset = &rk3188_modeset,
	.output = &rk3188_output,
	.win = rk3188_vop_win_data,
	.win_size = ARRAY_SIZE(rk3188_vop_win_data),
	.feature = VOP_FEATURE_INTERNAL_RGB,
पूर्ण;

अटल स्थिर काष्ठा vop_scl_extension rk3288_win_full_scl_ext = अणु
	.cbcr_vsd_mode = VOP_REG(RK3288_WIN0_CTRL1, 0x1, 31),
	.cbcr_vsu_mode = VOP_REG(RK3288_WIN0_CTRL1, 0x1, 30),
	.cbcr_hsd_mode = VOP_REG(RK3288_WIN0_CTRL1, 0x3, 28),
	.cbcr_ver_scl_mode = VOP_REG(RK3288_WIN0_CTRL1, 0x3, 26),
	.cbcr_hor_scl_mode = VOP_REG(RK3288_WIN0_CTRL1, 0x3, 24),
	.yrgb_vsd_mode = VOP_REG(RK3288_WIN0_CTRL1, 0x1, 23),
	.yrgb_vsu_mode = VOP_REG(RK3288_WIN0_CTRL1, 0x1, 22),
	.yrgb_hsd_mode = VOP_REG(RK3288_WIN0_CTRL1, 0x3, 20),
	.yrgb_ver_scl_mode = VOP_REG(RK3288_WIN0_CTRL1, 0x3, 18),
	.yrgb_hor_scl_mode = VOP_REG(RK3288_WIN0_CTRL1, 0x3, 16),
	.line_load_mode = VOP_REG(RK3288_WIN0_CTRL1, 0x1, 15),
	.cbcr_axi_gather_num = VOP_REG(RK3288_WIN0_CTRL1, 0x7, 12),
	.yrgb_axi_gather_num = VOP_REG(RK3288_WIN0_CTRL1, 0xf, 8),
	.vsd_cbcr_gt2 = VOP_REG(RK3288_WIN0_CTRL1, 0x1, 7),
	.vsd_cbcr_gt4 = VOP_REG(RK3288_WIN0_CTRL1, 0x1, 6),
	.vsd_yrgb_gt2 = VOP_REG(RK3288_WIN0_CTRL1, 0x1, 5),
	.vsd_yrgb_gt4 = VOP_REG(RK3288_WIN0_CTRL1, 0x1, 4),
	.bic_coe_sel = VOP_REG(RK3288_WIN0_CTRL1, 0x3, 2),
	.cbcr_axi_gather_en = VOP_REG(RK3288_WIN0_CTRL1, 0x1, 1),
	.yrgb_axi_gather_en = VOP_REG(RK3288_WIN0_CTRL1, 0x1, 0),
	.lb_mode = VOP_REG(RK3288_WIN0_CTRL0, 0x7, 5),
पूर्ण;

अटल स्थिर काष्ठा vop_scl_regs rk3288_win_full_scl = अणु
	.ext = &rk3288_win_full_scl_ext,
	.scale_yrgb_x = VOP_REG(RK3288_WIN0_SCL_FACTOR_YRGB, 0xffff, 0x0),
	.scale_yrgb_y = VOP_REG(RK3288_WIN0_SCL_FACTOR_YRGB, 0xffff, 16),
	.scale_cbcr_x = VOP_REG(RK3288_WIN0_SCL_FACTOR_CBR, 0xffff, 0x0),
	.scale_cbcr_y = VOP_REG(RK3288_WIN0_SCL_FACTOR_CBR, 0xffff, 16),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy rk3288_win01_data = अणु
	.scl = &rk3288_win_full_scl,
	.data_क्रमmats = क्रमmats_win_full,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_full),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_full,
	.enable = VOP_REG(RK3288_WIN0_CTRL0, 0x1, 0),
	.क्रमmat = VOP_REG(RK3288_WIN0_CTRL0, 0x7, 1),
	.rb_swap = VOP_REG(RK3288_WIN0_CTRL0, 0x1, 12),
	.act_info = VOP_REG(RK3288_WIN0_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_REG(RK3288_WIN0_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_REG(RK3288_WIN0_DSP_ST, 0x1fff1fff, 0),
	.yrgb_mst = VOP_REG(RK3288_WIN0_YRGB_MST, 0xffffffff, 0),
	.uv_mst = VOP_REG(RK3288_WIN0_CBR_MST, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(RK3288_WIN0_VIR, 0x3fff, 0),
	.uv_vir = VOP_REG(RK3288_WIN0_VIR, 0x3fff, 16),
	.src_alpha_ctl = VOP_REG(RK3288_WIN0_SRC_ALPHA_CTRL, 0xff, 0),
	.dst_alpha_ctl = VOP_REG(RK3288_WIN0_DST_ALPHA_CTRL, 0xff, 0),
	.channel = VOP_REG(RK3288_WIN0_CTRL2, 0xff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy rk3288_win23_data = अणु
	.data_क्रमmats = क्रमmats_win_lite,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_lite),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_lite,
	.enable = VOP_REG(RK3288_WIN2_CTRL0, 0x1, 4),
	.gate = VOP_REG(RK3288_WIN2_CTRL0, 0x1, 0),
	.क्रमmat = VOP_REG(RK3288_WIN2_CTRL0, 0x7, 1),
	.rb_swap = VOP_REG(RK3288_WIN2_CTRL0, 0x1, 12),
	.dsp_info = VOP_REG(RK3288_WIN2_DSP_INFO0, 0x0fff0fff, 0),
	.dsp_st = VOP_REG(RK3288_WIN2_DSP_ST0, 0x1fff1fff, 0),
	.yrgb_mst = VOP_REG(RK3288_WIN2_MST0, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(RK3288_WIN2_VIR0_1, 0x1fff, 0),
	.src_alpha_ctl = VOP_REG(RK3288_WIN2_SRC_ALPHA_CTRL, 0xff, 0),
	.dst_alpha_ctl = VOP_REG(RK3288_WIN2_DST_ALPHA_CTRL, 0xff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_modeset rk3288_modeset = अणु
	.htotal_pw = VOP_REG(RK3288_DSP_HTOTAL_HS_END, 0x1fff1fff, 0),
	.hact_st_end = VOP_REG(RK3288_DSP_HACT_ST_END, 0x1fff1fff, 0),
	.vtotal_pw = VOP_REG(RK3288_DSP_VTOTAL_VS_END, 0x1fff1fff, 0),
	.vact_st_end = VOP_REG(RK3288_DSP_VACT_ST_END, 0x1fff1fff, 0),
	.hpost_st_end = VOP_REG(RK3288_POST_DSP_HACT_INFO, 0x1fff1fff, 0),
	.vpost_st_end = VOP_REG(RK3288_POST_DSP_VACT_INFO, 0x1fff1fff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_output rk3288_output = अणु
	.pin_pol = VOP_REG(RK3288_DSP_CTRL0, 0xf, 4),
	.rgb_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 12),
	.hdmi_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 13),
	.edp_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 14),
	.mipi_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 15),
पूर्ण;

अटल स्थिर काष्ठा vop_common rk3288_common = अणु
	.standby = VOP_REG_SYNC(RK3288_SYS_CTRL, 0x1, 22),
	.gate_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 23),
	.mmu_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 20),
	.dither_करोwn_sel = VOP_REG(RK3288_DSP_CTRL1, 0x1, 4),
	.dither_करोwn_mode = VOP_REG(RK3288_DSP_CTRL1, 0x1, 3),
	.dither_करोwn_en = VOP_REG(RK3288_DSP_CTRL1, 0x1, 2),
	.pre_dither_करोwn = VOP_REG(RK3288_DSP_CTRL1, 0x1, 1),
	.dither_up = VOP_REG(RK3288_DSP_CTRL1, 0x1, 6),
	.dsp_lut_en = VOP_REG(RK3288_DSP_CTRL1, 0x1, 0),
	.data_blank = VOP_REG(RK3288_DSP_CTRL0, 0x1, 19),
	.dsp_blank = VOP_REG(RK3288_DSP_CTRL0, 0x3, 18),
	.out_mode = VOP_REG(RK3288_DSP_CTRL0, 0xf, 0),
	.cfg_करोne = VOP_REG_SYNC(RK3288_REG_CFG_DONE, 0x1, 0),
पूर्ण;

/*
 * Note: rk3288 has a dedicated 'cursor' winकरोw, however, that winकरोw requires
 * special support to get alpha blending working.  For now, just use overlay
 * winकरोw 3 क्रम the drm cursor.
 *
 */
अटल स्थिर काष्ठा vop_win_data rk3288_vop_win_data[] = अणु
	अणु .base = 0x00, .phy = &rk3288_win01_data,
	  .type = DRM_PLANE_TYPE_PRIMARY पूर्ण,
	अणु .base = 0x40, .phy = &rk3288_win01_data,
	  .type = DRM_PLANE_TYPE_OVERLAY पूर्ण,
	अणु .base = 0x00, .phy = &rk3288_win23_data,
	  .type = DRM_PLANE_TYPE_OVERLAY पूर्ण,
	अणु .base = 0x50, .phy = &rk3288_win23_data,
	  .type = DRM_PLANE_TYPE_CURSOR पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक rk3288_vop_पूर्णांकrs[] = अणु
	DSP_HOLD_VALID_INTR,
	FS_INTR,
	LINE_FLAG_INTR,
	BUS_ERROR_INTR,
पूर्ण;

अटल स्थिर काष्ठा vop_पूर्णांकr rk3288_vop_पूर्णांकr = अणु
	.पूर्णांकrs = rk3288_vop_पूर्णांकrs,
	.nपूर्णांकrs = ARRAY_SIZE(rk3288_vop_पूर्णांकrs),
	.line_flag_num[0] = VOP_REG(RK3288_INTR_CTRL0, 0x1fff, 12),
	.status = VOP_REG(RK3288_INTR_CTRL0, 0xf, 0),
	.enable = VOP_REG(RK3288_INTR_CTRL0, 0xf, 4),
	.clear = VOP_REG(RK3288_INTR_CTRL0, 0xf, 8),
पूर्ण;

अटल स्थिर काष्ठा vop_data rk3288_vop = अणु
	.version = VOP_VERSION(3, 1),
	.feature = VOP_FEATURE_OUTPUT_RGB10,
	.पूर्णांकr = &rk3288_vop_पूर्णांकr,
	.common = &rk3288_common,
	.modeset = &rk3288_modeset,
	.output = &rk3288_output,
	.win = rk3288_vop_win_data,
	.win_size = ARRAY_SIZE(rk3288_vop_win_data),
	.lut_size = 1024,
पूर्ण;

अटल स्थिर पूर्णांक rk3368_vop_पूर्णांकrs[] = अणु
	FS_INTR,
	0, 0,
	LINE_FLAG_INTR,
	0,
	BUS_ERROR_INTR,
	0, 0, 0, 0, 0, 0, 0,
	DSP_HOLD_VALID_INTR,
पूर्ण;

अटल स्थिर काष्ठा vop_पूर्णांकr rk3368_vop_पूर्णांकr = अणु
	.पूर्णांकrs = rk3368_vop_पूर्णांकrs,
	.nपूर्णांकrs = ARRAY_SIZE(rk3368_vop_पूर्णांकrs),
	.line_flag_num[0] = VOP_REG(RK3368_LINE_FLAG, 0xffff, 0),
	.line_flag_num[1] = VOP_REG(RK3368_LINE_FLAG, 0xffff, 16),
	.status = VOP_REG_MASK_SYNC(RK3368_INTR_STATUS, 0x3fff, 0),
	.enable = VOP_REG_MASK_SYNC(RK3368_INTR_EN, 0x3fff, 0),
	.clear = VOP_REG_MASK_SYNC(RK3368_INTR_CLEAR, 0x3fff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy rk3368_win01_data = अणु
	.scl = &rk3288_win_full_scl,
	.data_क्रमmats = क्रमmats_win_full,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_full),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_full,
	.enable = VOP_REG(RK3368_WIN0_CTRL0, 0x1, 0),
	.क्रमmat = VOP_REG(RK3368_WIN0_CTRL0, 0x7, 1),
	.rb_swap = VOP_REG(RK3368_WIN0_CTRL0, 0x1, 12),
	.x_mir_en = VOP_REG(RK3368_WIN0_CTRL0, 0x1, 21),
	.y_mir_en = VOP_REG(RK3368_WIN0_CTRL0, 0x1, 22),
	.act_info = VOP_REG(RK3368_WIN0_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_REG(RK3368_WIN0_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_REG(RK3368_WIN0_DSP_ST, 0x1fff1fff, 0),
	.yrgb_mst = VOP_REG(RK3368_WIN0_YRGB_MST, 0xffffffff, 0),
	.uv_mst = VOP_REG(RK3368_WIN0_CBR_MST, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(RK3368_WIN0_VIR, 0x3fff, 0),
	.uv_vir = VOP_REG(RK3368_WIN0_VIR, 0x3fff, 16),
	.src_alpha_ctl = VOP_REG(RK3368_WIN0_SRC_ALPHA_CTRL, 0xff, 0),
	.dst_alpha_ctl = VOP_REG(RK3368_WIN0_DST_ALPHA_CTRL, 0xff, 0),
	.channel = VOP_REG(RK3368_WIN0_CTRL2, 0xff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_win_phy rk3368_win23_data = अणु
	.data_क्रमmats = क्रमmats_win_lite,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_lite),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_lite,
	.gate = VOP_REG(RK3368_WIN2_CTRL0, 0x1, 0),
	.enable = VOP_REG(RK3368_WIN2_CTRL0, 0x1, 4),
	.क्रमmat = VOP_REG(RK3368_WIN2_CTRL0, 0x3, 5),
	.rb_swap = VOP_REG(RK3368_WIN2_CTRL0, 0x1, 20),
	.y_mir_en = VOP_REG(RK3368_WIN2_CTRL1, 0x1, 15),
	.dsp_info = VOP_REG(RK3368_WIN2_DSP_INFO0, 0x0fff0fff, 0),
	.dsp_st = VOP_REG(RK3368_WIN2_DSP_ST0, 0x1fff1fff, 0),
	.yrgb_mst = VOP_REG(RK3368_WIN2_MST0, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(RK3368_WIN2_VIR0_1, 0x1fff, 0),
	.src_alpha_ctl = VOP_REG(RK3368_WIN2_SRC_ALPHA_CTRL, 0xff, 0),
	.dst_alpha_ctl = VOP_REG(RK3368_WIN2_DST_ALPHA_CTRL, 0xff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_win_data rk3368_vop_win_data[] = अणु
	अणु .base = 0x00, .phy = &rk3368_win01_data,
	  .type = DRM_PLANE_TYPE_PRIMARY पूर्ण,
	अणु .base = 0x40, .phy = &rk3368_win01_data,
	  .type = DRM_PLANE_TYPE_OVERLAY पूर्ण,
	अणु .base = 0x00, .phy = &rk3368_win23_data,
	  .type = DRM_PLANE_TYPE_OVERLAY पूर्ण,
	अणु .base = 0x50, .phy = &rk3368_win23_data,
	  .type = DRM_PLANE_TYPE_CURSOR पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vop_output rk3368_output = अणु
	.rgb_dclk_pol = VOP_REG(RK3368_DSP_CTRL1, 0x1, 19),
	.hdmi_dclk_pol = VOP_REG(RK3368_DSP_CTRL1, 0x1, 23),
	.edp_dclk_pol = VOP_REG(RK3368_DSP_CTRL1, 0x1, 27),
	.mipi_dclk_pol = VOP_REG(RK3368_DSP_CTRL1, 0x1, 31),
	.rgb_pin_pol = VOP_REG(RK3368_DSP_CTRL1, 0x7, 16),
	.hdmi_pin_pol = VOP_REG(RK3368_DSP_CTRL1, 0x7, 20),
	.edp_pin_pol = VOP_REG(RK3368_DSP_CTRL1, 0x7, 24),
	.mipi_pin_pol = VOP_REG(RK3368_DSP_CTRL1, 0x7, 28),
	.rgb_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 12),
	.hdmi_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 13),
	.edp_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 14),
	.mipi_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 15),
पूर्ण;

अटल स्थिर काष्ठा vop_misc rk3368_misc = अणु
	.global_regकरोne_en = VOP_REG(RK3368_SYS_CTRL, 0x1, 11),
पूर्ण;

अटल स्थिर काष्ठा vop_data rk3368_vop = अणु
	.version = VOP_VERSION(3, 2),
	.पूर्णांकr = &rk3368_vop_पूर्णांकr,
	.common = &rk3288_common,
	.modeset = &rk3288_modeset,
	.output = &rk3368_output,
	.misc = &rk3368_misc,
	.win = rk3368_vop_win_data,
	.win_size = ARRAY_SIZE(rk3368_vop_win_data),
पूर्ण;

अटल स्थिर काष्ठा vop_पूर्णांकr rk3366_vop_पूर्णांकr = अणु
	.पूर्णांकrs = rk3368_vop_पूर्णांकrs,
	.nपूर्णांकrs = ARRAY_SIZE(rk3368_vop_पूर्णांकrs),
	.line_flag_num[0] = VOP_REG(RK3366_LINE_FLAG, 0xffff, 0),
	.line_flag_num[1] = VOP_REG(RK3366_LINE_FLAG, 0xffff, 16),
	.status = VOP_REG_MASK_SYNC(RK3366_INTR_STATUS0, 0xffff, 0),
	.enable = VOP_REG_MASK_SYNC(RK3366_INTR_EN0, 0xffff, 0),
	.clear = VOP_REG_MASK_SYNC(RK3366_INTR_CLEAR0, 0xffff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_data rk3366_vop = अणु
	.version = VOP_VERSION(3, 4),
	.पूर्णांकr = &rk3366_vop_पूर्णांकr,
	.common = &rk3288_common,
	.modeset = &rk3288_modeset,
	.output = &rk3368_output,
	.misc = &rk3368_misc,
	.win = rk3368_vop_win_data,
	.win_size = ARRAY_SIZE(rk3368_vop_win_data),
पूर्ण;

अटल स्थिर काष्ठा vop_output rk3399_output = अणु
	.dp_dclk_pol = VOP_REG(RK3399_DSP_CTRL1, 0x1, 19),
	.rgb_dclk_pol = VOP_REG(RK3368_DSP_CTRL1, 0x1, 19),
	.hdmi_dclk_pol = VOP_REG(RK3368_DSP_CTRL1, 0x1, 23),
	.edp_dclk_pol = VOP_REG(RK3368_DSP_CTRL1, 0x1, 27),
	.mipi_dclk_pol = VOP_REG(RK3368_DSP_CTRL1, 0x1, 31),
	.dp_pin_pol = VOP_REG(RK3399_DSP_CTRL1, 0x7, 16),
	.rgb_pin_pol = VOP_REG(RK3368_DSP_CTRL1, 0x7, 16),
	.hdmi_pin_pol = VOP_REG(RK3368_DSP_CTRL1, 0x7, 20),
	.edp_pin_pol = VOP_REG(RK3368_DSP_CTRL1, 0x7, 24),
	.mipi_pin_pol = VOP_REG(RK3368_DSP_CTRL1, 0x7, 28),
	.dp_en = VOP_REG(RK3399_SYS_CTRL, 0x1, 11),
	.rgb_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 12),
	.hdmi_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 13),
	.edp_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 14),
	.mipi_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 15),
	.mipi_dual_channel_en = VOP_REG(RK3288_SYS_CTRL, 0x1, 3),
पूर्ण;

अटल स्थिर काष्ठा vop_yuv2yuv_phy rk3399_yuv2yuv_win01_data = अणु
	.y2r_coefficients = अणु
		VOP_REG(RK3399_WIN0_YUV2YUV_Y2R + 0, 0xffff, 0),
		VOP_REG(RK3399_WIN0_YUV2YUV_Y2R + 0, 0xffff, 16),
		VOP_REG(RK3399_WIN0_YUV2YUV_Y2R + 4, 0xffff, 0),
		VOP_REG(RK3399_WIN0_YUV2YUV_Y2R + 4, 0xffff, 16),
		VOP_REG(RK3399_WIN0_YUV2YUV_Y2R + 8, 0xffff, 0),
		VOP_REG(RK3399_WIN0_YUV2YUV_Y2R + 8, 0xffff, 16),
		VOP_REG(RK3399_WIN0_YUV2YUV_Y2R + 12, 0xffff, 0),
		VOP_REG(RK3399_WIN0_YUV2YUV_Y2R + 12, 0xffff, 16),
		VOP_REG(RK3399_WIN0_YUV2YUV_Y2R + 16, 0xffff, 0),
		VOP_REG(RK3399_WIN0_YUV2YUV_Y2R + 20, 0xffffffff, 0),
		VOP_REG(RK3399_WIN0_YUV2YUV_Y2R + 24, 0xffffffff, 0),
		VOP_REG(RK3399_WIN0_YUV2YUV_Y2R + 28, 0xffffffff, 0),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vop_yuv2yuv_phy rk3399_yuv2yuv_win23_data = अणु पूर्ण;

अटल स्थिर काष्ठा vop_win_yuv2yuv_data rk3399_vop_big_win_yuv2yuv_data[] = अणु
	अणु .base = 0x00, .phy = &rk3399_yuv2yuv_win01_data,
	  .y2r_en = VOP_REG(RK3399_YUV2YUV_WIN, 0x1, 1) पूर्ण,
	अणु .base = 0x60, .phy = &rk3399_yuv2yuv_win01_data,
	  .y2r_en = VOP_REG(RK3399_YUV2YUV_WIN, 0x1, 9) पूर्ण,
	अणु .base = 0xC0, .phy = &rk3399_yuv2yuv_win23_data पूर्ण,
	अणु .base = 0x120, .phy = &rk3399_yuv2yuv_win23_data पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा vop_win_phy rk3399_win01_data = अणु
	.scl = &rk3288_win_full_scl,
	.data_क्रमmats = क्रमmats_win_full,
	.nक्रमmats = ARRAY_SIZE(क्रमmats_win_full),
	.क्रमmat_modअगरiers = क्रमmat_modअगरiers_win_full_afbc,
	.enable = VOP_REG(RK3288_WIN0_CTRL0, 0x1, 0),
	.क्रमmat = VOP_REG(RK3288_WIN0_CTRL0, 0x7, 1),
	.rb_swap = VOP_REG(RK3288_WIN0_CTRL0, 0x1, 12),
	.y_mir_en = VOP_REG(RK3288_WIN0_CTRL0, 0x1, 22),
	.act_info = VOP_REG(RK3288_WIN0_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_REG(RK3288_WIN0_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_REG(RK3288_WIN0_DSP_ST, 0x1fff1fff, 0),
	.yrgb_mst = VOP_REG(RK3288_WIN0_YRGB_MST, 0xffffffff, 0),
	.uv_mst = VOP_REG(RK3288_WIN0_CBR_MST, 0xffffffff, 0),
	.yrgb_vir = VOP_REG(RK3288_WIN0_VIR, 0x3fff, 0),
	.uv_vir = VOP_REG(RK3288_WIN0_VIR, 0x3fff, 16),
	.src_alpha_ctl = VOP_REG(RK3288_WIN0_SRC_ALPHA_CTRL, 0xff, 0),
	.dst_alpha_ctl = VOP_REG(RK3288_WIN0_DST_ALPHA_CTRL, 0xff, 0),
पूर्ण;

/*
 * rk3399 vop big winकरोws रेजिस्टर layout is same as rk3288, but we
 * have a separate rk3399 win data array here so that we can advertise
 * AFBC on the primary plane.
 */
अटल स्थिर काष्ठा vop_win_data rk3399_vop_win_data[] = अणु
	अणु .base = 0x00, .phy = &rk3399_win01_data,
	  .type = DRM_PLANE_TYPE_PRIMARY पूर्ण,
	अणु .base = 0x40, .phy = &rk3288_win01_data,
	  .type = DRM_PLANE_TYPE_OVERLAY पूर्ण,
	अणु .base = 0x00, .phy = &rk3288_win23_data,
	  .type = DRM_PLANE_TYPE_OVERLAY पूर्ण,
	अणु .base = 0x50, .phy = &rk3288_win23_data,
	  .type = DRM_PLANE_TYPE_CURSOR पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vop_afbc rk3399_vop_afbc = अणु
	.rstn = VOP_REG(RK3399_AFBCD0_CTRL, 0x1, 3),
	.enable = VOP_REG(RK3399_AFBCD0_CTRL, 0x1, 0),
	.win_sel = VOP_REG(RK3399_AFBCD0_CTRL, 0x3, 1),
	.क्रमmat = VOP_REG(RK3399_AFBCD0_CTRL, 0x1f, 16),
	.hreg_block_split = VOP_REG(RK3399_AFBCD0_CTRL, 0x1, 21),
	.hdr_ptr = VOP_REG(RK3399_AFBCD0_HDR_PTR, 0xffffffff, 0),
	.pic_size = VOP_REG(RK3399_AFBCD0_PIC_SIZE, 0xffffffff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_data rk3399_vop_big = अणु
	.version = VOP_VERSION(3, 5),
	.feature = VOP_FEATURE_OUTPUT_RGB10,
	.पूर्णांकr = &rk3366_vop_पूर्णांकr,
	.common = &rk3288_common,
	.modeset = &rk3288_modeset,
	.output = &rk3399_output,
	.afbc = &rk3399_vop_afbc,
	.misc = &rk3368_misc,
	.win = rk3399_vop_win_data,
	.win_size = ARRAY_SIZE(rk3399_vop_win_data),
	.win_yuv2yuv = rk3399_vop_big_win_yuv2yuv_data,
पूर्ण;

अटल स्थिर काष्ठा vop_win_data rk3399_vop_lit_win_data[] = अणु
	अणु .base = 0x00, .phy = &rk3368_win01_data,
	  .type = DRM_PLANE_TYPE_PRIMARY पूर्ण,
	अणु .base = 0x00, .phy = &rk3368_win23_data,
	  .type = DRM_PLANE_TYPE_CURSORपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vop_win_yuv2yuv_data rk3399_vop_lit_win_yuv2yuv_data[] = अणु
	अणु .base = 0x00, .phy = &rk3399_yuv2yuv_win01_data,
	  .y2r_en = VOP_REG(RK3399_YUV2YUV_WIN, 0x1, 1)पूर्ण,
	अणु .base = 0x60, .phy = &rk3399_yuv2yuv_win23_data पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vop_data rk3399_vop_lit = अणु
	.version = VOP_VERSION(3, 6),
	.पूर्णांकr = &rk3366_vop_पूर्णांकr,
	.common = &rk3288_common,
	.modeset = &rk3288_modeset,
	.output = &rk3399_output,
	.misc = &rk3368_misc,
	.win = rk3399_vop_lit_win_data,
	.win_size = ARRAY_SIZE(rk3399_vop_lit_win_data),
	.win_yuv2yuv = rk3399_vop_lit_win_yuv2yuv_data,
पूर्ण;

अटल स्थिर काष्ठा vop_win_data rk3228_vop_win_data[] = अणु
	अणु .base = 0x00, .phy = &rk3288_win01_data,
	  .type = DRM_PLANE_TYPE_PRIMARY पूर्ण,
	अणु .base = 0x40, .phy = &rk3288_win01_data,
	  .type = DRM_PLANE_TYPE_CURSOR पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vop_data rk3228_vop = अणु
	.version = VOP_VERSION(3, 7),
	.feature = VOP_FEATURE_OUTPUT_RGB10,
	.पूर्णांकr = &rk3366_vop_पूर्णांकr,
	.common = &rk3288_common,
	.modeset = &rk3288_modeset,
	.output = &rk3399_output,
	.misc = &rk3368_misc,
	.win = rk3228_vop_win_data,
	.win_size = ARRAY_SIZE(rk3228_vop_win_data),
पूर्ण;

अटल स्थिर काष्ठा vop_modeset rk3328_modeset = अणु
	.htotal_pw = VOP_REG(RK3328_DSP_HTOTAL_HS_END, 0x1fff1fff, 0),
	.hact_st_end = VOP_REG(RK3328_DSP_HACT_ST_END, 0x1fff1fff, 0),
	.vtotal_pw = VOP_REG(RK3328_DSP_VTOTAL_VS_END, 0x1fff1fff, 0),
	.vact_st_end = VOP_REG(RK3328_DSP_VACT_ST_END, 0x1fff1fff, 0),
	.hpost_st_end = VOP_REG(RK3328_POST_DSP_HACT_INFO, 0x1fff1fff, 0),
	.vpost_st_end = VOP_REG(RK3328_POST_DSP_VACT_INFO, 0x1fff1fff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_output rk3328_output = अणु
	.rgb_dclk_pol = VOP_REG(RK3328_DSP_CTRL1, 0x1, 19),
	.hdmi_dclk_pol = VOP_REG(RK3328_DSP_CTRL1, 0x1, 23),
	.edp_dclk_pol = VOP_REG(RK3328_DSP_CTRL1, 0x1, 27),
	.mipi_dclk_pol = VOP_REG(RK3328_DSP_CTRL1, 0x1, 31),
	.rgb_en = VOP_REG(RK3328_SYS_CTRL, 0x1, 12),
	.hdmi_en = VOP_REG(RK3328_SYS_CTRL, 0x1, 13),
	.edp_en = VOP_REG(RK3328_SYS_CTRL, 0x1, 14),
	.mipi_en = VOP_REG(RK3328_SYS_CTRL, 0x1, 15),
	.rgb_pin_pol = VOP_REG(RK3328_DSP_CTRL1, 0x7, 16),
	.hdmi_pin_pol = VOP_REG(RK3328_DSP_CTRL1, 0x7, 20),
	.edp_pin_pol = VOP_REG(RK3328_DSP_CTRL1, 0x7, 24),
	.mipi_pin_pol = VOP_REG(RK3328_DSP_CTRL1, 0x7, 28),
पूर्ण;

अटल स्थिर काष्ठा vop_misc rk3328_misc = अणु
	.global_regकरोne_en = VOP_REG(RK3328_SYS_CTRL, 0x1, 11),
पूर्ण;

अटल स्थिर काष्ठा vop_common rk3328_common = अणु
	.standby = VOP_REG_SYNC(RK3328_SYS_CTRL, 0x1, 22),
	.dither_करोwn_sel = VOP_REG(RK3328_DSP_CTRL1, 0x1, 4),
	.dither_करोwn_mode = VOP_REG(RK3328_DSP_CTRL1, 0x1, 3),
	.dither_करोwn_en = VOP_REG(RK3328_DSP_CTRL1, 0x1, 2),
	.pre_dither_करोwn = VOP_REG(RK3328_DSP_CTRL1, 0x1, 1),
	.dither_up = VOP_REG(RK3328_DSP_CTRL1, 0x1, 6),
	.dsp_blank = VOP_REG(RK3328_DSP_CTRL0, 0x3, 18),
	.out_mode = VOP_REG(RK3328_DSP_CTRL0, 0xf, 0),
	.cfg_करोne = VOP_REG_SYNC(RK3328_REG_CFG_DONE, 0x1, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_पूर्णांकr rk3328_vop_पूर्णांकr = अणु
	.पूर्णांकrs = rk3368_vop_पूर्णांकrs,
	.nपूर्णांकrs = ARRAY_SIZE(rk3368_vop_पूर्णांकrs),
	.line_flag_num[0] = VOP_REG(RK3328_LINE_FLAG, 0xffff, 0),
	.line_flag_num[1] = VOP_REG(RK3328_LINE_FLAG, 0xffff, 16),
	.status = VOP_REG_MASK_SYNC(RK3328_INTR_STATUS0, 0xffff, 0),
	.enable = VOP_REG_MASK_SYNC(RK3328_INTR_EN0, 0xffff, 0),
	.clear = VOP_REG_MASK_SYNC(RK3328_INTR_CLEAR0, 0xffff, 0),
पूर्ण;

अटल स्थिर काष्ठा vop_win_data rk3328_vop_win_data[] = अणु
	अणु .base = 0xd0, .phy = &rk3368_win01_data,
	  .type = DRM_PLANE_TYPE_PRIMARY पूर्ण,
	अणु .base = 0x1d0, .phy = &rk3368_win01_data,
	  .type = DRM_PLANE_TYPE_OVERLAY पूर्ण,
	अणु .base = 0x2d0, .phy = &rk3368_win01_data,
	  .type = DRM_PLANE_TYPE_CURSOR पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vop_data rk3328_vop = अणु
	.version = VOP_VERSION(3, 8),
	.feature = VOP_FEATURE_OUTPUT_RGB10,
	.पूर्णांकr = &rk3328_vop_पूर्णांकr,
	.common = &rk3328_common,
	.modeset = &rk3328_modeset,
	.output = &rk3328_output,
	.misc = &rk3328_misc,
	.win = rk3328_vop_win_data,
	.win_size = ARRAY_SIZE(rk3328_vop_win_data),
पूर्ण;

अटल स्थिर काष्ठा of_device_id vop_driver_dt_match[] = अणु
	अणु .compatible = "rockchip,rk3036-vop",
	  .data = &rk3036_vop पूर्ण,
	अणु .compatible = "rockchip,rk3126-vop",
	  .data = &rk3126_vop पूर्ण,
	अणु .compatible = "rockchip,px30-vop-big",
	  .data = &px30_vop_big पूर्ण,
	अणु .compatible = "rockchip,px30-vop-lit",
	  .data = &px30_vop_lit पूर्ण,
	अणु .compatible = "rockchip,rk3066-vop",
	  .data = &rk3066_vop पूर्ण,
	अणु .compatible = "rockchip,rk3188-vop",
	  .data = &rk3188_vop पूर्ण,
	अणु .compatible = "rockchip,rk3288-vop",
	  .data = &rk3288_vop पूर्ण,
	अणु .compatible = "rockchip,rk3368-vop",
	  .data = &rk3368_vop पूर्ण,
	अणु .compatible = "rockchip,rk3366-vop",
	  .data = &rk3366_vop पूर्ण,
	अणु .compatible = "rockchip,rk3399-vop-big",
	  .data = &rk3399_vop_big पूर्ण,
	अणु .compatible = "rockchip,rk3399-vop-lit",
	  .data = &rk3399_vop_lit पूर्ण,
	अणु .compatible = "rockchip,rk3228-vop",
	  .data = &rk3228_vop पूर्ण,
	अणु .compatible = "rockchip,rk3328-vop",
	  .data = &rk3328_vop पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, vop_driver_dt_match);

अटल पूर्णांक vop_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	अगर (!dev->of_node) अणु
		DRM_DEV_ERROR(dev, "can't find vop devices\n");
		वापस -ENODEV;
	पूर्ण

	वापस component_add(dev, &vop_component_ops);
पूर्ण

अटल पूर्णांक vop_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &vop_component_ops);

	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver vop_platक्रमm_driver = अणु
	.probe = vop_probe,
	.हटाओ = vop_हटाओ,
	.driver = अणु
		.name = "rockchip-vop",
		.of_match_table = of_match_ptr(vop_driver_dt_match),
	पूर्ण,
पूर्ण;
