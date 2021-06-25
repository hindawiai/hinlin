<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 Texas Instruments, Inc.
 */

#अगर_अघोषित __OMAPFB_DSS_H
#घोषणा __OMAPFB_DSS_H

#समावेश <linux/list.h>
#समावेश <linux/kobject.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
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

काष्ठा omap_dss_device;
काष्ठा omap_overlay_manager;
काष्ठा dss_lcd_mgr_config;
काष्ठा snd_aes_iec958;
काष्ठा snd_cea_861_aud_अगर;
काष्ठा hdmi_avi_infoframe;

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

क्रमागत omap_plane अणु
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
	OMAP_DSS_COLOR_CLUT1	= 1 << 0,  /* BITMAP 1 */
	OMAP_DSS_COLOR_CLUT2	= 1 << 1,  /* BITMAP 2 */
	OMAP_DSS_COLOR_CLUT4	= 1 << 2,  /* BITMAP 4 */
	OMAP_DSS_COLOR_CLUT8	= 1 << 3,  /* BITMAP 8 */
	OMAP_DSS_COLOR_RGB12U	= 1 << 4,  /* RGB12, 16-bit container */
	OMAP_DSS_COLOR_ARGB16	= 1 << 5,  /* ARGB16 */
	OMAP_DSS_COLOR_RGB16	= 1 << 6,  /* RGB16 */
	OMAP_DSS_COLOR_RGB24U	= 1 << 7,  /* RGB24, 32-bit container */
	OMAP_DSS_COLOR_RGB24P	= 1 << 8,  /* RGB24, 24-bit container */
	OMAP_DSS_COLOR_YUV2	= 1 << 9,  /* YUV2 4:2:2 co-sited */
	OMAP_DSS_COLOR_UYVY	= 1 << 10, /* UYVY 4:2:2 co-sited */
	OMAP_DSS_COLOR_ARGB32	= 1 << 11, /* ARGB32 */
	OMAP_DSS_COLOR_RGBA32	= 1 << 12, /* RGBA32 */
	OMAP_DSS_COLOR_RGBX32	= 1 << 13, /* RGBx32 */
	OMAP_DSS_COLOR_NV12		= 1 << 14, /* NV12 क्रमmat: YUV 4:2:0 */
	OMAP_DSS_COLOR_RGBA16		= 1 << 15, /* RGBA16 - 4444 */
	OMAP_DSS_COLOR_RGBX16		= 1 << 16, /* RGBx16 - 4444 */
	OMAP_DSS_COLOR_ARGB16_1555	= 1 << 17, /* ARGB16 - 1555 */
	OMAP_DSS_COLOR_XRGB16_1555	= 1 << 18, /* xRGB16 - 1555 */
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

क्रमागत omap_dss_dsi_pixel_क्रमmat अणु
	OMAP_DSS_DSI_FMT_RGB888,
	OMAP_DSS_DSI_FMT_RGB666,
	OMAP_DSS_DSI_FMT_RGB666_PACKED,
	OMAP_DSS_DSI_FMT_RGB565,
पूर्ण;

क्रमागत omap_dss_dsi_mode अणु
	OMAP_DSS_DSI_CMD_MODE = 0,
	OMAP_DSS_DSI_VIDEO_MODE,
पूर्ण;

क्रमागत omap_display_caps अणु
	OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE	= 1 << 0,
	OMAP_DSS_DISPLAY_CAP_TEAR_ELIM		= 1 << 1,
पूर्ण;

क्रमागत omap_dss_display_state अणु
	OMAP_DSS_DISPLAY_DISABLED = 0,
	OMAP_DSS_DISPLAY_ACTIVE,
पूर्ण;

क्रमागत omap_dss_rotation_type अणु
	OMAP_DSS_ROT_DMA	= 1 << 0,
	OMAP_DSS_ROT_VRFB	= 1 << 1,
	OMAP_DSS_ROT_TILER	= 1 << 2,
पूर्ण;

/* घड़ीwise rotation angle */
क्रमागत omap_dss_rotation_angle अणु
	OMAP_DSS_ROT_0   = 0,
	OMAP_DSS_ROT_90  = 1,
	OMAP_DSS_ROT_180 = 2,
	OMAP_DSS_ROT_270 = 3,
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

/* DSI */

क्रमागत omap_dss_dsi_trans_mode अणु
	/* Sync Pulses: both sync start and end packets sent */
	OMAP_DSS_DSI_PULSE_MODE,
	/* Sync Events: only sync start packets sent */
	OMAP_DSS_DSI_EVENT_MODE,
	/* Burst: only sync start packets sent, pixels are समय compressed */
	OMAP_DSS_DSI_BURST_MODE,
पूर्ण;

काष्ठा omap_dss_dsi_videomode_timings अणु
	अचिन्हित दीर्घ hsclk;

	अचिन्हित ndl;
	अचिन्हित bitspp;

	/* pixels */
	u16 hact;
	/* lines */
	u16 vact;

	/* DSI video mode blanking data */
	/* Unit: byte घड़ी cycles */
	u16 hss;
	u16 hsa;
	u16 hse;
	u16 hfp;
	u16 hbp;
	/* Unit: line घड़ीs */
	u16 vsa;
	u16 vfp;
	u16 vbp;

	/* DSI blanking modes */
	पूर्णांक blanking_mode;
	पूर्णांक hsa_blanking_mode;
	पूर्णांक hbp_blanking_mode;
	पूर्णांक hfp_blanking_mode;

	क्रमागत omap_dss_dsi_trans_mode trans_mode;

	bool ddr_clk_always_on;
	पूर्णांक winकरोw_sync;
पूर्ण;

काष्ठा omap_dss_dsi_config अणु
	क्रमागत omap_dss_dsi_mode mode;
	क्रमागत omap_dss_dsi_pixel_क्रमmat pixel_क्रमmat;
	स्थिर काष्ठा omap_video_timings *timings;

	अचिन्हित दीर्घ hs_clk_min, hs_clk_max;
	अचिन्हित दीर्घ lp_clk_min, lp_clk_max;

	bool ddr_clk_always_on;
	क्रमागत omap_dss_dsi_trans_mode trans_mode;
पूर्ण;

काष्ठा omap_video_timings अणु
	/* Unit: pixels */
	u16 x_res;
	/* Unit: pixels */
	u16 y_res;
	/* Unit: Hz */
	u32 pixelघड़ी;
	/* Unit: pixel घड़ीs */
	u16 hsw;	/* Horizontal synchronization pulse width */
	/* Unit: pixel घड़ीs */
	u16 hfp;	/* Horizontal front porch */
	/* Unit: pixel घड़ीs */
	u16 hbp;	/* Horizontal back porch */
	/* Unit: line घड़ीs */
	u16 vsw;	/* Vertical synchronization pulse width */
	/* Unit: line घड़ीs */
	u16 vfp;	/* Vertical front porch */
	/* Unit: line घड़ीs */
	u16 vbp;	/* Vertical back porch */

	/* Vsync logic level */
	क्रमागत omap_dss_संकेत_level vsync_level;
	/* Hsync logic level */
	क्रमागत omap_dss_संकेत_level hsync_level;
	/* Interlaced or Progressive timings */
	bool पूर्णांकerlace;
	/* Pixel घड़ी edge to drive LCD data */
	क्रमागत omap_dss_संकेत_edge data_pclk_edge;
	/* Data enable logic level */
	क्रमागत omap_dss_संकेत_level de_level;
	/* Pixel घड़ी edges to drive HSYNC and VSYNC संकेतs */
	क्रमागत omap_dss_संकेत_edge sync_pclk_edge;

	bool द्विगुन_pixel;
पूर्ण;

/* Hardcoded timings क्रम tv modes. Venc only uses these to
 * identअगरy the mode, and करोes not actually use the configs
 * itself. However, the configs should be something that
 * a normal monitor can also show */
बाह्य स्थिर काष्ठा omap_video_timings omap_dss_pal_timings;
बाह्य स्थिर काष्ठा omap_video_timings omap_dss_ntsc_timings;

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
	क्रमागत omap_color_mode color_mode;
	u8 rotation;
	क्रमागत omap_dss_rotation_type rotation_type;
	bool mirror;

	u16 pos_x;
	u16 pos_y;
	u16 out_width;	/* अगर 0, out_width == width */
	u16 out_height;	/* अगर 0, out_height == height */
	u8 global_alpha;
	u8 pre_mult_alpha;
	u8 zorder;
पूर्ण;

काष्ठा omap_overlay अणु
	काष्ठा kobject kobj;
	काष्ठा list_head list;

	/* अटल fields */
	स्थिर अक्षर *name;
	क्रमागत omap_plane id;
	क्रमागत omap_color_mode supported_modes;
	क्रमागत omap_overlay_caps caps;

	/* dynamic fields */
	काष्ठा omap_overlay_manager *manager;

	/*
	 * The following functions करो not block:
	 *
	 * is_enabled
	 * set_overlay_info
	 * get_overlay_info
	 *
	 * The rest of the functions may block and cannot be called from
	 * पूर्णांकerrupt context
	 */

	पूर्णांक (*enable)(काष्ठा omap_overlay *ovl);
	पूर्णांक (*disable)(काष्ठा omap_overlay *ovl);
	bool (*is_enabled)(काष्ठा omap_overlay *ovl);

	पूर्णांक (*set_manager)(काष्ठा omap_overlay *ovl,
		काष्ठा omap_overlay_manager *mgr);
	पूर्णांक (*unset_manager)(काष्ठा omap_overlay *ovl);

	पूर्णांक (*set_overlay_info)(काष्ठा omap_overlay *ovl,
			काष्ठा omap_overlay_info *info);
	व्योम (*get_overlay_info)(काष्ठा omap_overlay *ovl,
			काष्ठा omap_overlay_info *info);

	पूर्णांक (*रुको_क्रम_go)(काष्ठा omap_overlay *ovl);

	काष्ठा omap_dss_device *(*get_device)(काष्ठा omap_overlay *ovl);
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

काष्ठा omap_overlay_manager अणु
	काष्ठा kobject kobj;

	/* अटल fields */
	स्थिर अक्षर *name;
	क्रमागत omap_channel id;
	काष्ठा list_head overlays;
	क्रमागत omap_display_type supported_displays;
	क्रमागत omap_dss_output_id supported_outमाला_दो;

	/* dynamic fields */
	काष्ठा omap_dss_device *output;

	/*
	 * The following functions करो not block:
	 *
	 * set_manager_info
	 * get_manager_info
	 * apply
	 *
	 * The rest of the functions may block and cannot be called from
	 * पूर्णांकerrupt context
	 */

	पूर्णांक (*set_output)(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_dss_device *output);
	पूर्णांक (*unset_output)(काष्ठा omap_overlay_manager *mgr);

	पूर्णांक (*set_manager_info)(काष्ठा omap_overlay_manager *mgr,
			काष्ठा omap_overlay_manager_info *info);
	व्योम (*get_manager_info)(काष्ठा omap_overlay_manager *mgr,
			काष्ठा omap_overlay_manager_info *info);

	पूर्णांक (*apply)(काष्ठा omap_overlay_manager *mgr);
	पूर्णांक (*रुको_क्रम_go)(काष्ठा omap_overlay_manager *mgr);
	पूर्णांक (*रुको_क्रम_vsync)(काष्ठा omap_overlay_manager *mgr);

	काष्ठा omap_dss_device *(*get_device)(काष्ठा omap_overlay_manager *mgr);
पूर्ण;

/* 22 pins means 1 clk lane and 10 data lanes */
#घोषणा OMAP_DSS_MAX_DSI_PINS 22

काष्ठा omap_dsi_pin_config अणु
	पूर्णांक num_pins;
	/*
	 * pin numbers in the following order:
	 * clk+, clk-
	 * data1+, data1-
	 * data2+, data2-
	 * ...
	 */
	पूर्णांक pins[OMAP_DSS_MAX_DSI_PINS];
पूर्ण;

काष्ठा omap_dss_ग_लिखोback_info अणु
	u32 paddr;
	u32 p_uv_addr;
	u16 buf_width;
	u16 width;
	u16 height;
	क्रमागत omap_color_mode color_mode;
	u8 rotation;
	क्रमागत omap_dss_rotation_type rotation_type;
	bool mirror;
	u8 pre_mult_alpha;
पूर्ण;

काष्ठा omapdss_dpi_ops अणु
	पूर्णांक (*connect)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_dss_device *dst);
	व्योम (*disconnect)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_dss_device *dst);

	पूर्णांक (*enable)(काष्ठा omap_dss_device *dssdev);
	व्योम (*disable)(काष्ठा omap_dss_device *dssdev);

	पूर्णांक (*check_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);
	व्योम (*set_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);
	व्योम (*get_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);

	व्योम (*set_data_lines)(काष्ठा omap_dss_device *dssdev, पूर्णांक data_lines);
पूर्ण;

काष्ठा omapdss_sdi_ops अणु
	पूर्णांक (*connect)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_dss_device *dst);
	व्योम (*disconnect)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_dss_device *dst);

	पूर्णांक (*enable)(काष्ठा omap_dss_device *dssdev);
	व्योम (*disable)(काष्ठा omap_dss_device *dssdev);

	पूर्णांक (*check_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);
	व्योम (*set_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);
	व्योम (*get_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);

	व्योम (*set_datapairs)(काष्ठा omap_dss_device *dssdev, पूर्णांक datapairs);
पूर्ण;

काष्ठा omapdss_dvi_ops अणु
	पूर्णांक (*connect)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_dss_device *dst);
	व्योम (*disconnect)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_dss_device *dst);

	पूर्णांक (*enable)(काष्ठा omap_dss_device *dssdev);
	व्योम (*disable)(काष्ठा omap_dss_device *dssdev);

	पूर्णांक (*check_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);
	व्योम (*set_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);
	व्योम (*get_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);
पूर्ण;

काष्ठा omapdss_atv_ops अणु
	पूर्णांक (*connect)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_dss_device *dst);
	व्योम (*disconnect)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_dss_device *dst);

	पूर्णांक (*enable)(काष्ठा omap_dss_device *dssdev);
	व्योम (*disable)(काष्ठा omap_dss_device *dssdev);

	पूर्णांक (*check_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);
	व्योम (*set_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);
	व्योम (*get_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);

	व्योम (*set_type)(काष्ठा omap_dss_device *dssdev,
		क्रमागत omap_dss_venc_type type);
	व्योम (*invert_vid_out_polarity)(काष्ठा omap_dss_device *dssdev,
		bool invert_polarity);

	पूर्णांक (*set_wss)(काष्ठा omap_dss_device *dssdev, u32 wss);
	u32 (*get_wss)(काष्ठा omap_dss_device *dssdev);
पूर्ण;

काष्ठा omapdss_hdmi_ops अणु
	पूर्णांक (*connect)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_dss_device *dst);
	व्योम (*disconnect)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_dss_device *dst);

	पूर्णांक (*enable)(काष्ठा omap_dss_device *dssdev);
	व्योम (*disable)(काष्ठा omap_dss_device *dssdev);

	पूर्णांक (*check_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);
	व्योम (*set_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);
	व्योम (*get_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);

	पूर्णांक (*पढ़ो_edid)(काष्ठा omap_dss_device *dssdev, u8 *buf, पूर्णांक len);
	bool (*detect)(काष्ठा omap_dss_device *dssdev);

	पूर्णांक (*set_hdmi_mode)(काष्ठा omap_dss_device *dssdev, bool hdmi_mode);
	पूर्णांक (*set_infoframe)(काष्ठा omap_dss_device *dssdev,
		स्थिर काष्ठा hdmi_avi_infoframe *avi);
पूर्ण;

काष्ठा omapdss_dsi_ops अणु
	पूर्णांक (*connect)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_dss_device *dst);
	व्योम (*disconnect)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_dss_device *dst);

	पूर्णांक (*enable)(काष्ठा omap_dss_device *dssdev);
	व्योम (*disable)(काष्ठा omap_dss_device *dssdev, bool disconnect_lanes,
			bool enter_ulps);

	/* bus configuration */
	पूर्णांक (*set_config)(काष्ठा omap_dss_device *dssdev,
			स्थिर काष्ठा omap_dss_dsi_config *cfg);
	पूर्णांक (*configure_pins)(काष्ठा omap_dss_device *dssdev,
			स्थिर काष्ठा omap_dsi_pin_config *pin_cfg);

	व्योम (*enable_hs)(काष्ठा omap_dss_device *dssdev, पूर्णांक channel,
			bool enable);
	पूर्णांक (*enable_te)(काष्ठा omap_dss_device *dssdev, bool enable);

	पूर्णांक (*update)(काष्ठा omap_dss_device *dssdev, पूर्णांक channel,
			व्योम (*callback)(पूर्णांक, व्योम *), व्योम *data);

	व्योम (*bus_lock)(काष्ठा omap_dss_device *dssdev);
	व्योम (*bus_unlock)(काष्ठा omap_dss_device *dssdev);

	पूर्णांक (*enable_video_output)(काष्ठा omap_dss_device *dssdev, पूर्णांक channel);
	व्योम (*disable_video_output)(काष्ठा omap_dss_device *dssdev,
			पूर्णांक channel);

	पूर्णांक (*request_vc)(काष्ठा omap_dss_device *dssdev, पूर्णांक *channel);
	पूर्णांक (*set_vc_id)(काष्ठा omap_dss_device *dssdev, पूर्णांक channel,
			पूर्णांक vc_id);
	व्योम (*release_vc)(काष्ठा omap_dss_device *dssdev, पूर्णांक channel);

	/* data transfer */
	पूर्णांक (*dcs_ग_लिखो)(काष्ठा omap_dss_device *dssdev, पूर्णांक channel,
			u8 *data, पूर्णांक len);
	पूर्णांक (*dcs_ग_लिखो_nosync)(काष्ठा omap_dss_device *dssdev, पूर्णांक channel,
			u8 *data, पूर्णांक len);
	पूर्णांक (*dcs_पढ़ो)(काष्ठा omap_dss_device *dssdev, पूर्णांक channel, u8 dcs_cmd,
			u8 *data, पूर्णांक len);

	पूर्णांक (*gen_ग_लिखो)(काष्ठा omap_dss_device *dssdev, पूर्णांक channel,
			u8 *data, पूर्णांक len);
	पूर्णांक (*gen_ग_लिखो_nosync)(काष्ठा omap_dss_device *dssdev, पूर्णांक channel,
			u8 *data, पूर्णांक len);
	पूर्णांक (*gen_पढ़ो)(काष्ठा omap_dss_device *dssdev, पूर्णांक channel,
			u8 *reqdata, पूर्णांक reqlen,
			u8 *data, पूर्णांक len);

	पूर्णांक (*bta_sync)(काष्ठा omap_dss_device *dssdev, पूर्णांक channel);

	पूर्णांक (*set_max_rx_packet_size)(काष्ठा omap_dss_device *dssdev,
			पूर्णांक channel, u16 plen);
पूर्ण;

काष्ठा omap_dss_device अणु
	काष्ठा kobject kobj;
	काष्ठा device *dev;

	काष्ठा module *owner;

	काष्ठा list_head panel_list;

	/* alias in the क्रमm of "display%d" */
	अक्षर alias[16];

	क्रमागत omap_display_type type;
	क्रमागत omap_display_type output_type;

	जोड़ अणु
		काष्ठा अणु
			u8 data_lines;
		पूर्ण dpi;

		काष्ठा अणु
			u8 datapairs;
		पूर्ण sdi;

		काष्ठा अणु
			पूर्णांक module;
		पूर्ण dsi;

		काष्ठा अणु
			क्रमागत omap_dss_venc_type type;
			bool invert_polarity;
		पूर्ण venc;
	पूर्ण phy;

	काष्ठा अणु
		काष्ठा omap_video_timings timings;

		क्रमागत omap_dss_dsi_pixel_क्रमmat dsi_pix_fmt;
		क्रमागत omap_dss_dsi_mode dsi_mode;
	पूर्ण panel;

	काष्ठा अणु
		u8 pixel_size;
	पूर्ण ctrl;

	स्थिर अक्षर *name;

	/* used to match device to driver */
	स्थिर अक्षर *driver_name;

	व्योम *data;

	काष्ठा omap_dss_driver *driver;

	जोड़ अणु
		स्थिर काष्ठा omapdss_dpi_ops *dpi;
		स्थिर काष्ठा omapdss_sdi_ops *sdi;
		स्थिर काष्ठा omapdss_dvi_ops *dvi;
		स्थिर काष्ठा omapdss_hdmi_ops *hdmi;
		स्थिर काष्ठा omapdss_atv_ops *atv;
		स्थिर काष्ठा omapdss_dsi_ops *dsi;
	पूर्ण ops;

	/* helper variable क्रम driver suspend/resume */
	bool activate_after_resume;

	क्रमागत omap_display_caps caps;

	काष्ठा omap_dss_device *src;

	क्रमागत omap_dss_display_state state;

	/* OMAP DSS output specअगरic fields */

	काष्ठा list_head list;

	/* DISPC channel क्रम this output */
	क्रमागत omap_channel dispc_channel;
	bool dispc_channel_connected;

	/* output instance */
	क्रमागत omap_dss_output_id id;

	/* the port number in the DT node */
	पूर्णांक port_num;

	/* dynamic fields */
	काष्ठा omap_overlay_manager *manager;

	काष्ठा omap_dss_device *dst;
पूर्ण;

काष्ठा omap_dss_driver अणु
	पूर्णांक (*probe)(काष्ठा omap_dss_device *);
	व्योम (*हटाओ)(काष्ठा omap_dss_device *);

	पूर्णांक (*connect)(काष्ठा omap_dss_device *dssdev);
	व्योम (*disconnect)(काष्ठा omap_dss_device *dssdev);

	पूर्णांक (*enable)(काष्ठा omap_dss_device *display);
	व्योम (*disable)(काष्ठा omap_dss_device *display);
	पूर्णांक (*run_test)(काष्ठा omap_dss_device *display, पूर्णांक test);

	पूर्णांक (*update)(काष्ठा omap_dss_device *dssdev,
			       u16 x, u16 y, u16 w, u16 h);
	पूर्णांक (*sync)(काष्ठा omap_dss_device *dssdev);

	पूर्णांक (*enable_te)(काष्ठा omap_dss_device *dssdev, bool enable);
	पूर्णांक (*get_te)(काष्ठा omap_dss_device *dssdev);

	u8 (*get_rotate)(काष्ठा omap_dss_device *dssdev);
	पूर्णांक (*set_rotate)(काष्ठा omap_dss_device *dssdev, u8 rotate);

	bool (*get_mirror)(काष्ठा omap_dss_device *dssdev);
	पूर्णांक (*set_mirror)(काष्ठा omap_dss_device *dssdev, bool enable);

	पूर्णांक (*memory_पढ़ो)(काष्ठा omap_dss_device *dssdev,
			व्योम *buf, माप_प्रकार size,
			u16 x, u16 y, u16 w, u16 h);

	व्योम (*get_resolution)(काष्ठा omap_dss_device *dssdev,
			u16 *xres, u16 *yres);
	व्योम (*get_dimensions)(काष्ठा omap_dss_device *dssdev,
			u32 *width, u32 *height);
	पूर्णांक (*get_recommended_bpp)(काष्ठा omap_dss_device *dssdev);

	पूर्णांक (*check_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);
	व्योम (*set_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);
	व्योम (*get_timings)(काष्ठा omap_dss_device *dssdev,
			काष्ठा omap_video_timings *timings);

	पूर्णांक (*set_wss)(काष्ठा omap_dss_device *dssdev, u32 wss);
	u32 (*get_wss)(काष्ठा omap_dss_device *dssdev);

	पूर्णांक (*पढ़ो_edid)(काष्ठा omap_dss_device *dssdev, u8 *buf, पूर्णांक len);
	bool (*detect)(काष्ठा omap_dss_device *dssdev);

	पूर्णांक (*set_hdmi_mode)(काष्ठा omap_dss_device *dssdev, bool hdmi_mode);
	पूर्णांक (*set_hdmi_infoframe)(काष्ठा omap_dss_device *dssdev,
		स्थिर काष्ठा hdmi_avi_infoframe *avi);
पूर्ण;

#घोषणा क्रम_each_dss_dev(d) जबतक ((d = omap_dss_get_next_device(d)) != शून्य)

प्रकार व्योम (*omap_dispc_isr_t) (व्योम *arg, u32 mask);

#अगर IS_ENABLED(CONFIG_FB_OMAP2)

क्रमागत omapdss_version omapdss_get_version(व्योम);
bool omapdss_is_initialized(व्योम);

पूर्णांक omap_dss_रेजिस्टर_driver(काष्ठा omap_dss_driver *);
व्योम omap_dss_unरेजिस्टर_driver(काष्ठा omap_dss_driver *);

पूर्णांक omapdss_रेजिस्टर_display(काष्ठा omap_dss_device *dssdev);
व्योम omapdss_unरेजिस्टर_display(काष्ठा omap_dss_device *dssdev);

काष्ठा omap_dss_device *omap_dss_get_device(काष्ठा omap_dss_device *dssdev);
व्योम omap_dss_put_device(काष्ठा omap_dss_device *dssdev);
काष्ठा omap_dss_device *omap_dss_get_next_device(काष्ठा omap_dss_device *from);
काष्ठा omap_dss_device *omap_dss_find_device(व्योम *data,
		पूर्णांक (*match)(काष्ठा omap_dss_device *dssdev, व्योम *data));
स्थिर अक्षर *omapdss_get_शेष_display_name(व्योम);

व्योम videomode_to_omap_video_timings(स्थिर काष्ठा videomode *vm,
		काष्ठा omap_video_timings *ovt);
व्योम omap_video_timings_to_videomode(स्थिर काष्ठा omap_video_timings *ovt,
		काष्ठा videomode *vm);

पूर्णांक dss_feat_get_num_mgrs(व्योम);
पूर्णांक dss_feat_get_num_ovls(व्योम);
क्रमागत omap_color_mode dss_feat_get_supported_color_modes(क्रमागत omap_plane plane);



पूर्णांक omap_dss_get_num_overlay_managers(व्योम);
काष्ठा omap_overlay_manager *omap_dss_get_overlay_manager(पूर्णांक num);

पूर्णांक omap_dss_get_num_overlays(व्योम);
काष्ठा omap_overlay *omap_dss_get_overlay(पूर्णांक num);

पूर्णांक omapdss_रेजिस्टर_output(काष्ठा omap_dss_device *output);
व्योम omapdss_unरेजिस्टर_output(काष्ठा omap_dss_device *output);
काष्ठा omap_dss_device *omap_dss_get_output(क्रमागत omap_dss_output_id id);
काष्ठा omap_dss_device *omap_dss_find_output(स्थिर अक्षर *name);
काष्ठा omap_dss_device *omap_dss_find_output_by_port_node(काष्ठा device_node *port);
पूर्णांक omapdss_output_set_device(काष्ठा omap_dss_device *out,
		काष्ठा omap_dss_device *dssdev);
पूर्णांक omapdss_output_unset_device(काष्ठा omap_dss_device *out);

काष्ठा omap_dss_device *omapdss_find_output_from_display(काष्ठा omap_dss_device *dssdev);
काष्ठा omap_overlay_manager *omapdss_find_mgr_from_display(काष्ठा omap_dss_device *dssdev);

व्योम omapdss_शेष_get_resolution(काष्ठा omap_dss_device *dssdev,
		u16 *xres, u16 *yres);
पूर्णांक omapdss_शेष_get_recommended_bpp(काष्ठा omap_dss_device *dssdev);
व्योम omapdss_शेष_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings);

पूर्णांक omap_dispc_रेजिस्टर_isr(omap_dispc_isr_t isr, व्योम *arg, u32 mask);
पूर्णांक omap_dispc_unरेजिस्टर_isr(omap_dispc_isr_t isr, व्योम *arg, u32 mask);

पूर्णांक omapdss_compat_init(व्योम);
व्योम omapdss_compat_uninit(व्योम);

अटल अंतरभूत bool omapdss_device_is_connected(काष्ठा omap_dss_device *dssdev)
अणु
	वापस dssdev->src;
पूर्ण

अटल अंतरभूत bool omapdss_device_is_enabled(काष्ठा omap_dss_device *dssdev)
अणु
	वापस dssdev->state == OMAP_DSS_DISPLAY_ACTIVE;
पूर्ण

काष्ठा device_node *
omapdss_of_get_next_port(स्थिर काष्ठा device_node *parent,
			 काष्ठा device_node *prev);

काष्ठा device_node *
omapdss_of_get_next_endpoपूर्णांक(स्थिर काष्ठा device_node *parent,
			     काष्ठा device_node *prev);

काष्ठा device_node *
omapdss_of_get_first_endpoपूर्णांक(स्थिर काष्ठा device_node *parent);

काष्ठा omap_dss_device *
omapdss_of_find_source_क्रम_first_ep(काष्ठा device_node *node);
#अन्यथा

अटल अंतरभूत क्रमागत omapdss_version omapdss_get_version(व्योम)
अणु वापस OMAPDSS_VER_UNKNOWN; पूर्ण;

अटल अंतरभूत bool omapdss_is_initialized(व्योम)
अणु वापस false; पूर्ण;

अटल अंतरभूत पूर्णांक omap_dispc_रेजिस्टर_isr(omap_dispc_isr_t isr,
					  व्योम *arg, u32 mask)
अणु वापस 0; पूर्ण;

अटल अंतरभूत पूर्णांक omap_dispc_unरेजिस्टर_isr(omap_dispc_isr_t isr,
					    व्योम *arg, u32 mask)
अणु वापस 0; पूर्ण;

अटल अंतरभूत काष्ठा omap_dss_device
*omap_dss_get_device(काष्ठा omap_dss_device *dssdev)
अणु वापस शून्य; पूर्ण;

अटल अंतरभूत काष्ठा omap_dss_device
*omap_dss_get_next_device(काष्ठा omap_dss_device *from)
अणुवापस शून्य; पूर्ण;

अटल अंतरभूत व्योम omap_dss_put_device(काष्ठा omap_dss_device *dssdev) अणुपूर्ण;

अटल अंतरभूत पूर्णांक omapdss_compat_init(व्योम)
अणु वापस 0; पूर्ण;

अटल अंतरभूत व्योम omapdss_compat_uninit(व्योम) अणुपूर्ण;

अटल अंतरभूत पूर्णांक omap_dss_get_num_overlay_managers(व्योम)
अणु वापस 0; पूर्ण;

अटल अंतरभूत काष्ठा omap_overlay_manager *omap_dss_get_overlay_manager(पूर्णांक num)
अणु वापस शून्य; पूर्ण;

अटल अंतरभूत पूर्णांक omap_dss_get_num_overlays(व्योम)
अणु वापस 0; पूर्ण;

अटल अंतरभूत काष्ठा omap_overlay *omap_dss_get_overlay(पूर्णांक num)
अणु वापस शून्य; पूर्ण;


#पूर्ण_अगर /* FB_OMAP2 */


#पूर्ण_अगर /* __OMAPFB_DSS_H */
