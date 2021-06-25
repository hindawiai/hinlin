<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#अगर_अघोषित __MESON_DRV_H
#घोषणा __MESON_DRV_H

#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

काष्ठा drm_crtc;
काष्ठा drm_device;
काष्ठा drm_plane;
काष्ठा meson_drm;
काष्ठा meson_afbcd_ops;

क्रमागत vpu_compatible अणु
	VPU_COMPATIBLE_GXBB = 0,
	VPU_COMPATIBLE_GXL  = 1,
	VPU_COMPATIBLE_GXM  = 2,
	VPU_COMPATIBLE_G12A = 3,
पूर्ण;

काष्ठा meson_drm_match_data अणु
	क्रमागत vpu_compatible compat;
	काष्ठा meson_afbcd_ops *afbcd_ops;
पूर्ण;

काष्ठा meson_drm_soc_limits अणु
	अचिन्हित पूर्णांक max_hdmi_phy_freq;
पूर्ण;

काष्ठा meson_drm अणु
	काष्ठा device *dev;
	क्रमागत vpu_compatible compat;
	व्योम __iomem *io_base;
	काष्ठा regmap *hhi;
	पूर्णांक vsync_irq;

	काष्ठा meson_canvas *canvas;
	u8 canvas_id_osd1;
	u8 canvas_id_vd1_0;
	u8 canvas_id_vd1_1;
	u8 canvas_id_vd1_2;

	काष्ठा drm_device *drm;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_plane *primary_plane;
	काष्ठा drm_plane *overlay_plane;

	स्थिर काष्ठा meson_drm_soc_limits *limits;

	/* Components Data */
	काष्ठा अणु
		bool osd1_enabled;
		bool osd1_पूर्णांकerlace;
		bool osd1_commit;
		bool osd1_afbcd;
		uपूर्णांक32_t osd1_ctrl_stat;
		uपूर्णांक32_t osd1_ctrl_stat2;
		uपूर्णांक32_t osd1_blk0_cfg[5];
		uपूर्णांक32_t osd1_blk1_cfg4;
		uपूर्णांक32_t osd1_blk2_cfg4;
		uपूर्णांक32_t osd1_addr;
		uपूर्णांक32_t osd1_stride;
		uपूर्णांक32_t osd1_height;
		uपूर्णांक32_t osd1_width;
		uपूर्णांक32_t osd_sc_ctrl0;
		uपूर्णांक32_t osd_sc_i_wh_m1;
		uपूर्णांक32_t osd_sc_o_h_start_end;
		uपूर्णांक32_t osd_sc_o_v_start_end;
		uपूर्णांक32_t osd_sc_v_ini_phase;
		uपूर्णांक32_t osd_sc_v_phase_step;
		uपूर्णांक32_t osd_sc_h_ini_phase;
		uपूर्णांक32_t osd_sc_h_phase_step;
		uपूर्णांक32_t osd_sc_h_ctrl0;
		uपूर्णांक32_t osd_sc_v_ctrl0;
		uपूर्णांक32_t osd_blend_din0_scope_h;
		uपूर्णांक32_t osd_blend_din0_scope_v;
		uपूर्णांक32_t osb_blend0_size;
		uपूर्णांक32_t osb_blend1_size;

		bool vd1_enabled;
		bool vd1_commit;
		bool vd1_afbc;
		अचिन्हित पूर्णांक vd1_planes;
		uपूर्णांक32_t vd1_अगर0_gen_reg;
		uपूर्णांक32_t vd1_अगर0_luma_x0;
		uपूर्णांक32_t vd1_अगर0_luma_y0;
		uपूर्णांक32_t vd1_अगर0_chroma_x0;
		uपूर्णांक32_t vd1_अगर0_chroma_y0;
		uपूर्णांक32_t vd1_अगर0_repeat_loop;
		uपूर्णांक32_t vd1_अगर0_luma0_rpt_pat;
		uपूर्णांक32_t vd1_अगर0_chroma0_rpt_pat;
		uपूर्णांक32_t vd1_range_map_y;
		uपूर्णांक32_t vd1_range_map_cb;
		uपूर्णांक32_t vd1_range_map_cr;
		uपूर्णांक32_t viu_vd1_fmt_w;
		uपूर्णांक32_t vd1_अगर0_canvas0;
		uपूर्णांक32_t vd1_अगर0_gen_reg2;
		uपूर्णांक32_t viu_vd1_fmt_ctrl;
		uपूर्णांक32_t vd1_addr0;
		uपूर्णांक32_t vd1_addr1;
		uपूर्णांक32_t vd1_addr2;
		uपूर्णांक32_t vd1_stride0;
		uपूर्णांक32_t vd1_stride1;
		uपूर्णांक32_t vd1_stride2;
		uपूर्णांक32_t vd1_height0;
		uपूर्णांक32_t vd1_height1;
		uपूर्णांक32_t vd1_height2;
		uपूर्णांक32_t vd1_afbc_mode;
		uपूर्णांक32_t vd1_afbc_en;
		uपूर्णांक32_t vd1_afbc_head_addr;
		uपूर्णांक32_t vd1_afbc_body_addr;
		uपूर्णांक32_t vd1_afbc_conv_ctrl;
		uपूर्णांक32_t vd1_afbc_dec_def_color;
		uपूर्णांक32_t vd1_afbc_vd_cfmt_ctrl;
		uपूर्णांक32_t vd1_afbc_vd_cfmt_w;
		uपूर्णांक32_t vd1_afbc_vd_cfmt_h;
		uपूर्णांक32_t vd1_afbc_mअगर_hor_scope;
		uपूर्णांक32_t vd1_afbc_mअगर_ver_scope;
		uपूर्णांक32_t vd1_afbc_size_out;
		uपूर्णांक32_t vd1_afbc_pixel_hor_scope;
		uपूर्णांक32_t vd1_afbc_pixel_ver_scope;
		uपूर्णांक32_t vd1_afbc_size_in;
		uपूर्णांक32_t vpp_pic_in_height;
		uपूर्णांक32_t vpp_postblend_vd1_h_start_end;
		uपूर्णांक32_t vpp_postblend_vd1_v_start_end;
		uपूर्णांक32_t vpp_hsc_region12_startp;
		uपूर्णांक32_t vpp_hsc_region34_startp;
		uपूर्णांक32_t vpp_hsc_region4_endp;
		uपूर्णांक32_t vpp_hsc_start_phase_step;
		uपूर्णांक32_t vpp_hsc_region1_phase_slope;
		uपूर्णांक32_t vpp_hsc_region3_phase_slope;
		uपूर्णांक32_t vpp_line_in_length;
		uपूर्णांक32_t vpp_preblend_h_size;
		uपूर्णांक32_t vpp_vsc_region12_startp;
		uपूर्णांक32_t vpp_vsc_region34_startp;
		uपूर्णांक32_t vpp_vsc_region4_endp;
		uपूर्णांक32_t vpp_vsc_start_phase_step;
		uपूर्णांक32_t vpp_vsc_ini_phase;
		uपूर्णांक32_t vpp_vsc_phase_ctrl;
		uपूर्णांक32_t vpp_hsc_phase_ctrl;
		uपूर्णांक32_t vpp_blend_vd2_h_start_end;
		uपूर्णांक32_t vpp_blend_vd2_v_start_end;
	पूर्ण viu;

	काष्ठा अणु
		अचिन्हित पूर्णांक current_mode;
		bool hdmi_repeat;
		bool venc_repeat;
		bool hdmi_use_enci;
	पूर्ण venc;

	काष्ठा अणु
		dma_addr_t addr_dma;
		uपूर्णांक32_t *addr;
		अचिन्हित पूर्णांक offset;
	पूर्ण rdma;

	काष्ठा अणु
		काष्ठा meson_afbcd_ops *ops;
		u64 modअगरier;
		u32 क्रमmat;
	पूर्ण afbcd;
पूर्ण;

अटल अंतरभूत पूर्णांक meson_vpu_is_compatible(काष्ठा meson_drm *priv,
					  क्रमागत vpu_compatible family)
अणु
	वापस priv->compat == family;
पूर्ण

#पूर्ण_अगर /* __MESON_DRV_H */
