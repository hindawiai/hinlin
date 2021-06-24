<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#अगर_अघोषित __TIDSS_DISPC_H__
#घोषणा __TIDSS_DISPC_H__

#समावेश "tidss_drv.h"

काष्ठा dispc_device;

काष्ठा drm_crtc_state;

क्रमागत tidss_gamma_type अणु TIDSS_GAMMA_8BIT, TIDSS_GAMMA_10BIT पूर्ण;

काष्ठा tidss_vp_feat अणु
	काष्ठा tidss_vp_color_feat अणु
		u32 gamma_size;
		क्रमागत tidss_gamma_type gamma_type;
		bool has_cपंचांग;
	पूर्ण color;
पूर्ण;

काष्ठा tidss_plane_feat अणु
	काष्ठा tidss_plane_color_feat अणु
		u32 encodings;
		u32 ranges;
		क्रमागत drm_color_encoding शेष_encoding;
		क्रमागत drm_color_range शेष_range;
	पूर्ण color;
	काष्ठा tidss_plane_blend_feat अणु
		bool global_alpha;
	पूर्ण blend;
पूर्ण;

काष्ठा dispc_features_scaling अणु
	u32 in_width_max_5tap_rgb;
	u32 in_width_max_3tap_rgb;
	u32 in_width_max_5tap_yuv;
	u32 in_width_max_3tap_yuv;
	u32 upscale_limit;
	u32 करोwnscale_limit_5tap;
	u32 करोwnscale_limit_3tap;
	u32 xinc_max;
पूर्ण;

काष्ठा dispc_errata अणु
	bool i2000; /* DSS Does Not Support YUV Pixel Data Formats */
पूर्ण;

क्रमागत dispc_vp_bus_type अणु
	DISPC_VP_DPI,		/* DPI output */
	DISPC_VP_OLDI,		/* OLDI (LVDS) output */
	DISPC_VP_INTERNAL,	/* SoC पूर्णांकernal routing */
	DISPC_VP_MAX_BUS_TYPE,
पूर्ण;

क्रमागत dispc_dss_subrevision अणु
	DISPC_K2G,
	DISPC_AM65X,
	DISPC_J721E,
पूर्ण;

काष्ठा dispc_features अणु
	पूर्णांक min_pclk_khz;
	पूर्णांक max_pclk_khz[DISPC_VP_MAX_BUS_TYPE];

	काष्ठा dispc_features_scaling scaling;

	क्रमागत dispc_dss_subrevision subrev;

	स्थिर अक्षर *common;
	स्थिर u16 *common_regs;
	u32 num_vps;
	स्थिर अक्षर *vp_name[TIDSS_MAX_PORTS]; /* Should match dt reg names */
	स्थिर अक्षर *ovr_name[TIDSS_MAX_PORTS]; /* Should match dt reg names */
	स्थिर अक्षर *vpclk_name[TIDSS_MAX_PORTS]; /* Should match dt clk names */
	स्थिर क्रमागत dispc_vp_bus_type vp_bus_type[TIDSS_MAX_PORTS];
	काष्ठा tidss_vp_feat vp_feat;
	u32 num_planes;
	स्थिर अक्षर *vid_name[TIDSS_MAX_PLANES]; /* Should match dt reg names */
	bool vid_lite[TIDSS_MAX_PLANES];
	u32 vid_order[TIDSS_MAX_PLANES];
पूर्ण;

बाह्य स्थिर काष्ठा dispc_features dispc_k2g_feats;
बाह्य स्थिर काष्ठा dispc_features dispc_am65x_feats;
बाह्य स्थिर काष्ठा dispc_features dispc_j721e_feats;

व्योम dispc_set_irqenable(काष्ठा dispc_device *dispc, dispc_irq_t mask);
dispc_irq_t dispc_पढ़ो_and_clear_irqstatus(काष्ठा dispc_device *dispc);

व्योम dispc_ovr_set_plane(काष्ठा dispc_device *dispc, u32 hw_plane,
			 u32 hw_videoport, u32 x, u32 y, u32 layer);
व्योम dispc_ovr_enable_layer(काष्ठा dispc_device *dispc,
			    u32 hw_videoport, u32 layer, bool enable);

व्योम dispc_vp_prepare(काष्ठा dispc_device *dispc, u32 hw_videoport,
		      स्थिर काष्ठा drm_crtc_state *state);
व्योम dispc_vp_enable(काष्ठा dispc_device *dispc, u32 hw_videoport,
		     स्थिर काष्ठा drm_crtc_state *state);
व्योम dispc_vp_disable(काष्ठा dispc_device *dispc, u32 hw_videoport);
व्योम dispc_vp_unprepare(काष्ठा dispc_device *dispc, u32 hw_videoport);
bool dispc_vp_go_busy(काष्ठा dispc_device *dispc, u32 hw_videoport);
व्योम dispc_vp_go(काष्ठा dispc_device *dispc, u32 hw_videoport);
पूर्णांक dispc_vp_bus_check(काष्ठा dispc_device *dispc, u32 hw_videoport,
		       स्थिर काष्ठा drm_crtc_state *state);
क्रमागत drm_mode_status dispc_vp_mode_valid(काष्ठा dispc_device *dispc,
					 u32 hw_videoport,
					 स्थिर काष्ठा drm_display_mode *mode);
पूर्णांक dispc_vp_enable_clk(काष्ठा dispc_device *dispc, u32 hw_videoport);
व्योम dispc_vp_disable_clk(काष्ठा dispc_device *dispc, u32 hw_videoport);
पूर्णांक dispc_vp_set_clk_rate(काष्ठा dispc_device *dispc, u32 hw_videoport,
			  अचिन्हित दीर्घ rate);
व्योम dispc_vp_setup(काष्ठा dispc_device *dispc, u32 hw_videoport,
		    स्थिर काष्ठा drm_crtc_state *state, bool newmodeset);

पूर्णांक dispc_runसमय_suspend(काष्ठा dispc_device *dispc);
पूर्णांक dispc_runसमय_resume(काष्ठा dispc_device *dispc);

पूर्णांक dispc_plane_check(काष्ठा dispc_device *dispc, u32 hw_plane,
		      स्थिर काष्ठा drm_plane_state *state,
		      u32 hw_videoport);
पूर्णांक dispc_plane_setup(काष्ठा dispc_device *dispc, u32 hw_plane,
		      स्थिर काष्ठा drm_plane_state *state,
		      u32 hw_videoport);
पूर्णांक dispc_plane_enable(काष्ठा dispc_device *dispc, u32 hw_plane, bool enable);
स्थिर u32 *dispc_plane_क्रमmats(काष्ठा dispc_device *dispc, अचिन्हित पूर्णांक *len);

पूर्णांक dispc_init(काष्ठा tidss_device *tidss);
व्योम dispc_हटाओ(काष्ठा tidss_device *tidss);

#पूर्ण_अगर
