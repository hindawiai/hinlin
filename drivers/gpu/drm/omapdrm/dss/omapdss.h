<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#अगर_अघोषित __OMAP_DRM_DSS_H
#घोषणा __OMAP_DRM_DSS_H

#समावेश <drm/drm_color_mgmt.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_mode.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/platक्रमm_data/omapdss.h>
#समावेश <video/videomode.h>

#घोषणा DISPC_IRQ_FRAMEDONE		(1 << 0)
#घोषणा DISPC_IRQ_VSYNC			(1 << 1)
#घोषणा DISPC_IRQ_EVSYNC_EVEN		(1 << 2)
#घोषणा DISPC_IRQ_EVSYNC_ODD		(1 << 3)
#घोषणा DISPC_IRQ_ACBIAS_COUNT_STAT	(1 << 4)
#घोषणा DISPC_IRQ_PROG_LINE_NUM		(1 << 5)
#घोषणा DISPC_IRQ_GFX_FIFO_UNDERFLOW	(1 << 6)
#घोषणा DISPC_IRQ_GFX_END_WIN		(1 << 7)
#घोषणा DISPC_IRQ_PAL_GAMMA_MASK	(1 << 8)
#घोषणा DISPC_IRQ_OCP_ERR		(1 << 9)
#घोषणा DISPC_IRQ_VID1_FIFO_UNDERFLOW	(1 << 10)
#घोषणा DISPC_IRQ_VID1_END_WIN		(1 << 11)
#घोषणा DISPC_IRQ_VID2_FIFO_UNDERFLOW	(1 << 12)
#घोषणा DISPC_IRQ_VID2_END_WIN		(1 << 13)
#घोषणा DISPC_IRQ_SYNC_LOST		(1 << 14)
#घोषणा DISPC_IRQ_SYNC_LOST_DIGIT	(1 << 15)
#घोषणा DISPC_IRQ_WAKEUP		(1 << 16)
#घोषणा DISPC_IRQ_SYNC_LOST2		(1 << 17)
#घोषणा DISPC_IRQ_VSYNC2		(1 << 18)
#घोषणा DISPC_IRQ_VID3_END_WIN		(1 << 19)
#घोषणा DISPC_IRQ_VID3_FIFO_UNDERFLOW	(1 << 20)
#घोषणा DISPC_IRQ_ACBIAS_COUNT_STAT2	(1 << 21)
#घोषणा DISPC_IRQ_FRAMEDONE2		(1 << 22)
#घोषणा DISPC_IRQ_FRAMEDONEWB		(1 << 23)
#घोषणा DISPC_IRQ_FRAMEDONETV		(1 << 24)
#घोषणा DISPC_IRQ_WBBUFFEROVERFLOW	(1 << 25)
#घोषणा DISPC_IRQ_WBUNCOMPLETEERROR	(1 << 26)
#घोषणा DISPC_IRQ_SYNC_LOST3		(1 << 27)
#घोषणा DISPC_IRQ_VSYNC3		(1 << 28)
#घोषणा DISPC_IRQ_ACBIAS_COUNT_STAT3	(1 << 29)
#घोषणा DISPC_IRQ_FRAMEDONE3		(1 << 30)

काष्ठा dispc_device;
काष्ठा drm_connector;
काष्ठा dss_device;
काष्ठा dss_lcd_mgr_config;
काष्ठा hdmi_avi_infoframe;
काष्ठा omap_drm_निजी;
काष्ठा omap_dss_device;
काष्ठा snd_aes_iec958;
काष्ठा snd_cea_861_aud_अगर;

क्रमागत omap_display_type अणु
	OMAP_DISPLAY_TYPE_NONE		= 0,
	OMAP_DISPLAY_TYPE_DPI		= 1 << 0,
	OMAP_DISPLAY_TYPE_DBI		= 1 << 1,
	OMAP_DISPLAY_TYPE_SDI		= 1 << 2,
	OMAP_DISPLAY_TYPE_DSI		= 1 << 3,
	OMAP_DISPLAY_TYPE_VENC		= 1 << 4,
	OMAP_DISPLAY_TYPE_HDMI		= 1 << 5,
	OMAP_DISPLAY_TYPE_DVI		= 1 << 6,
पूर्ण;

क्रमागत omap_plane_id अणु
	OMAP_DSS_GFX	= 0,
	OMAP_DSS_VIDEO1	= 1,
	OMAP_DSS_VIDEO2	= 2,
	OMAP_DSS_VIDEO3	= 3,
	OMAP_DSS_WB	= 4,
पूर्ण;

क्रमागत omap_channel अणु
	OMAP_DSS_CHANNEL_LCD	= 0,
	OMAP_DSS_CHANNEL_DIGIT	= 1,
	OMAP_DSS_CHANNEL_LCD2	= 2,
	OMAP_DSS_CHANNEL_LCD3	= 3,
	OMAP_DSS_CHANNEL_WB	= 4,
पूर्ण;

क्रमागत omap_color_mode अणु
	_UNUSED_,
पूर्ण;

क्रमागत omap_dss_load_mode अणु
	OMAP_DSS_LOAD_CLUT_AND_FRAME	= 0,
	OMAP_DSS_LOAD_CLUT_ONLY		= 1,
	OMAP_DSS_LOAD_FRAME_ONLY	= 2,
	OMAP_DSS_LOAD_CLUT_ONCE_FRAME	= 3,
पूर्ण;

क्रमागत omap_dss_trans_key_type अणु
	OMAP_DSS_COLOR_KEY_GFX_DST = 0,
	OMAP_DSS_COLOR_KEY_VID_SRC = 1,
पूर्ण;

क्रमागत omap_dss_संकेत_level अणु
	OMAPDSS_SIG_ACTIVE_LOW,
	OMAPDSS_SIG_ACTIVE_HIGH,
पूर्ण;

क्रमागत omap_dss_संकेत_edge अणु
	OMAPDSS_DRIVE_SIG_FALLING_EDGE,
	OMAPDSS_DRIVE_SIG_RISING_EDGE,
पूर्ण;

क्रमागत omap_dss_venc_type अणु
	OMAP_DSS_VENC_TYPE_COMPOSITE,
	OMAP_DSS_VENC_TYPE_SVIDEO,
पूर्ण;

क्रमागत omap_dss_rotation_type अणु
	OMAP_DSS_ROT_NONE	= 0,
	OMAP_DSS_ROT_TILER	= 1 << 0,
पूर्ण;

क्रमागत omap_overlay_caps अणु
	OMAP_DSS_OVL_CAP_SCALE = 1 << 0,
	OMAP_DSS_OVL_CAP_GLOBAL_ALPHA = 1 << 1,
	OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA = 1 << 2,
	OMAP_DSS_OVL_CAP_ZORDER = 1 << 3,
	OMAP_DSS_OVL_CAP_POS = 1 << 4,
	OMAP_DSS_OVL_CAP_REPLICATION = 1 << 5,
पूर्ण;

क्रमागत omap_dss_output_id अणु
	OMAP_DSS_OUTPUT_DPI	= 1 << 0,
	OMAP_DSS_OUTPUT_DBI	= 1 << 1,
	OMAP_DSS_OUTPUT_SDI	= 1 << 2,
	OMAP_DSS_OUTPUT_DSI1	= 1 << 3,
	OMAP_DSS_OUTPUT_DSI2	= 1 << 4,
	OMAP_DSS_OUTPUT_VENC	= 1 << 5,
	OMAP_DSS_OUTPUT_HDMI	= 1 << 6,
पूर्ण;

काष्ठा omap_dss_cpr_coefs अणु
	s16 rr, rg, rb;
	s16 gr, gg, gb;
	s16 br, bg, bb;
पूर्ण;

काष्ठा omap_overlay_info अणु
	dma_addr_t paddr;
	dma_addr_t p_uv_addr;  /* क्रम NV12 क्रमmat */
	u16 screen_width;
	u16 width;
	u16 height;
	u32 fourcc;
	u8 rotation;
	क्रमागत omap_dss_rotation_type rotation_type;

	u16 pos_x;
	u16 pos_y;
	u16 out_width;	/* अगर 0, out_width == width */
	u16 out_height;	/* अगर 0, out_height == height */
	u8 global_alpha;
	u8 pre_mult_alpha;
	u8 zorder;

	क्रमागत drm_color_encoding color_encoding;
	क्रमागत drm_color_range color_range;
पूर्ण;

काष्ठा omap_overlay_manager_info अणु
	u32 शेष_color;

	क्रमागत omap_dss_trans_key_type trans_key_type;
	u32 trans_key;
	bool trans_enabled;

	bool partial_alpha_enabled;

	bool cpr_enable;
	काष्ठा omap_dss_cpr_coefs cpr_coefs;
पूर्ण;

काष्ठा omap_dss_ग_लिखोback_info अणु
	u32 paddr;
	u32 p_uv_addr;
	u16 buf_width;
	u16 width;
	u16 height;
	u32 fourcc;
	u8 rotation;
	क्रमागत omap_dss_rotation_type rotation_type;
	u8 pre_mult_alpha;
पूर्ण;

काष्ठा omapdss_dsi_ops अणु
	पूर्णांक (*update)(काष्ठा omap_dss_device *dssdev);
	bool (*is_video_mode)(काष्ठा omap_dss_device *dssdev);
पूर्ण;

काष्ठा omap_dss_device अणु
	काष्ठा device *dev;

	काष्ठा dss_device *dss;
	काष्ठा drm_bridge *bridge;
	काष्ठा drm_bridge *next_bridge;
	काष्ठा drm_panel *panel;

	काष्ठा list_head list;

	/*
	 * DSS type that this device generates (क्रम DSS पूर्णांकernal devices) or
	 * requires (क्रम बाह्यal encoders, connectors and panels). Must be a
	 * non-zero (dअगरferent than OMAP_DISPLAY_TYPE_NONE) value.
	 */
	क्रमागत omap_display_type type;

	स्थिर अक्षर *name;

	स्थिर काष्ठा omapdss_dsi_ops *dsi_ops;
	u32 bus_flags;

	/* OMAP DSS output specअगरic fields */

	/* DISPC channel क्रम this output */
	क्रमागत omap_channel dispc_channel;

	/* output instance */
	क्रमागत omap_dss_output_id id;

	/* port number in DT */
	अचिन्हित पूर्णांक of_port;
पूर्ण;

काष्ठा dss_pdata अणु
	काष्ठा dss_device *dss;
पूर्ण;

व्योम omapdss_device_रेजिस्टर(काष्ठा omap_dss_device *dssdev);
व्योम omapdss_device_unरेजिस्टर(काष्ठा omap_dss_device *dssdev);
काष्ठा omap_dss_device *omapdss_device_get(काष्ठा omap_dss_device *dssdev);
व्योम omapdss_device_put(काष्ठा omap_dss_device *dssdev);
काष्ठा omap_dss_device *omapdss_find_device_by_node(काष्ठा device_node *node);
पूर्णांक omapdss_device_connect(काष्ठा dss_device *dss,
			   काष्ठा omap_dss_device *src,
			   काष्ठा omap_dss_device *dst);
व्योम omapdss_device_disconnect(काष्ठा omap_dss_device *src,
			       काष्ठा omap_dss_device *dst);

पूर्णांक omap_dss_get_num_overlay_managers(व्योम);

पूर्णांक omap_dss_get_num_overlays(व्योम);

#घोषणा क्रम_each_dss_output(d) \
	जबतक ((d = omapdss_device_next_output(d)) != शून्य)
काष्ठा omap_dss_device *omapdss_device_next_output(काष्ठा omap_dss_device *from);
पूर्णांक omapdss_device_init_output(काष्ठा omap_dss_device *out,
			       काष्ठा drm_bridge *local_bridge);
व्योम omapdss_device_cleanup_output(काष्ठा omap_dss_device *out);

प्रकार व्योम (*omap_dispc_isr_t) (व्योम *arg, u32 mask);
पूर्णांक omap_dispc_रेजिस्टर_isr(omap_dispc_isr_t isr, व्योम *arg, u32 mask);
पूर्णांक omap_dispc_unरेजिस्टर_isr(omap_dispc_isr_t isr, व्योम *arg, u32 mask);

पूर्णांक omapdss_compat_init(व्योम);
व्योम omapdss_compat_uninit(व्योम);

क्रमागत dss_ग_लिखोback_channel अणु
	DSS_WB_LCD1_MGR =	0,
	DSS_WB_LCD2_MGR =	1,
	DSS_WB_TV_MGR =		2,
	DSS_WB_OVL0 =		3,
	DSS_WB_OVL1 =		4,
	DSS_WB_OVL2 =		5,
	DSS_WB_OVL3 =		6,
	DSS_WB_LCD3_MGR =	7,
पूर्ण;

व्योम omap_crtc_dss_start_update(काष्ठा omap_drm_निजी *priv,
				       क्रमागत omap_channel channel);
व्योम omap_crtc_set_enabled(काष्ठा drm_crtc *crtc, bool enable);
पूर्णांक omap_crtc_dss_enable(काष्ठा omap_drm_निजी *priv, क्रमागत omap_channel channel);
व्योम omap_crtc_dss_disable(काष्ठा omap_drm_निजी *priv, क्रमागत omap_channel channel);
व्योम omap_crtc_dss_set_timings(काष्ठा omap_drm_निजी *priv,
		क्रमागत omap_channel channel,
		स्थिर काष्ठा videomode *vm);
व्योम omap_crtc_dss_set_lcd_config(काष्ठा omap_drm_निजी *priv,
		क्रमागत omap_channel channel,
		स्थिर काष्ठा dss_lcd_mgr_config *config);
पूर्णांक omap_crtc_dss_रेजिस्टर_frameकरोne(
		काष्ठा omap_drm_निजी *priv, क्रमागत omap_channel channel,
		व्योम (*handler)(व्योम *), व्योम *data);
व्योम omap_crtc_dss_unरेजिस्टर_frameकरोne(
		काष्ठा omap_drm_निजी *priv, क्रमागत omap_channel channel,
		व्योम (*handler)(व्योम *), व्योम *data);

व्योम dss_mgr_set_timings(काष्ठा omap_dss_device *dssdev,
		स्थिर काष्ठा videomode *vm);
व्योम dss_mgr_set_lcd_config(काष्ठा omap_dss_device *dssdev,
		स्थिर काष्ठा dss_lcd_mgr_config *config);
पूर्णांक dss_mgr_enable(काष्ठा omap_dss_device *dssdev);
व्योम dss_mgr_disable(काष्ठा omap_dss_device *dssdev);
व्योम dss_mgr_start_update(काष्ठा omap_dss_device *dssdev);
पूर्णांक dss_mgr_रेजिस्टर_frameकरोne_handler(काष्ठा omap_dss_device *dssdev,
		व्योम (*handler)(व्योम *), व्योम *data);
व्योम dss_mgr_unरेजिस्टर_frameकरोne_handler(काष्ठा omap_dss_device *dssdev,
		व्योम (*handler)(व्योम *), व्योम *data);

काष्ठा dispc_device *dispc_get_dispc(काष्ठा dss_device *dss);

bool omapdss_stack_is_पढ़ोy(व्योम);
व्योम omapdss_gather_components(काष्ठा device *dev);

पूर्णांक omap_dss_init(व्योम);
व्योम omap_dss_निकास(व्योम);

#पूर्ण_अगर /* __OMAP_DRM_DSS_H */
