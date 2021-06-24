<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2007-2009 Texas Instruments Inc
 * Copyright (C) 2007 MontaVista Software, Inc.
 *
 * Andy Lowe (alowe@mvista.com), MontaVista Software
 * - Initial version
 * Murali Karicheri (mkaricheri@gmail.com), Texas Instruments Ltd.
 * - ported to sub device पूर्णांकerface
 */
#अगर_अघोषित _OSD_H
#घोषणा _OSD_H

#समावेश <media/davinci/vpbe_types.h>

#घोषणा DM644X_VPBE_OSD_SUBDEV_NAME	"dm644x,vpbe-osd"
#घोषणा DM365_VPBE_OSD_SUBDEV_NAME	"dm365,vpbe-osd"
#घोषणा DM355_VPBE_OSD_SUBDEV_NAME	"dm355,vpbe-osd"

/**
 * क्रमागत osd_layer
 * @WIN_OSD0: On-Screen Display Winकरोw 0
 * @WIN_VID0: Video Winकरोw 0
 * @WIN_OSD1: On-Screen Display Winकरोw 1
 * @WIN_VID1: Video Winकरोw 1
 *
 * Description:
 * An क्रमागतeration of the osd display layers.
 */
क्रमागत osd_layer अणु
	WIN_OSD0,
	WIN_VID0,
	WIN_OSD1,
	WIN_VID1,
पूर्ण;

/**
 * क्रमागत osd_win_layer
 * @OSDWIN_OSD0: On-Screen Display Winकरोw 0
 * @OSDWIN_OSD1: On-Screen Display Winकरोw 1
 *
 * Description:
 * An क्रमागतeration of the OSD Winकरोw layers.
 */
क्रमागत osd_win_layer अणु
	OSDWIN_OSD0,
	OSDWIN_OSD1,
पूर्ण;

/**
 * क्रमागत osd_pix_क्रमmat
 * @PIXFMT_1BPP: 1-bit-per-pixel biपंचांगap
 * @PIXFMT_2BPP: 2-bits-per-pixel biपंचांगap
 * @PIXFMT_4BPP: 4-bits-per-pixel biपंचांगap
 * @PIXFMT_8BPP: 8-bits-per-pixel biपंचांगap
 * @PIXFMT_RGB565: 16-bits-per-pixel RGB565
 * @PIXFMT_YCBCRI: YUV 4:2:2
 * @PIXFMT_RGB888: 24-bits-per-pixel RGB888
 * @PIXFMT_YCRCBI: YUV 4:2:2 with chroma swap
 * @PIXFMT_NV12: YUV 4:2:0 planar
 * @PIXFMT_OSD_ATTR: OSD Attribute Winकरोw pixel क्रमmat (4bpp)
 *
 * Description:
 * An क्रमागतeration of the DaVinci pixel क्रमmats.
 */
क्रमागत osd_pix_क्रमmat अणु
	PIXFMT_1BPP = 0,
	PIXFMT_2BPP,
	PIXFMT_4BPP,
	PIXFMT_8BPP,
	PIXFMT_RGB565,
	PIXFMT_YCBCRI,
	PIXFMT_RGB888,
	PIXFMT_YCRCBI,
	PIXFMT_NV12,
	PIXFMT_OSD_ATTR,
पूर्ण;

/**
 * क्रमागत osd_h_exp_ratio
 * @H_EXP_OFF: no expansion (1/1)
 * @H_EXP_9_OVER_8: 9/8 expansion ratio
 * @H_EXP_3_OVER_2: 3/2 expansion ratio
 *
 * Description:
 * An क्रमागतeration of the available horizontal expansion ratios.
 */
क्रमागत osd_h_exp_ratio अणु
	H_EXP_OFF,
	H_EXP_9_OVER_8,
	H_EXP_3_OVER_2,
पूर्ण;

/**
 * क्रमागत osd_v_exp_ratio
 * @V_EXP_OFF: no expansion (1/1)
 * @V_EXP_6_OVER_5: 6/5 expansion ratio
 *
 * Description:
 * An क्रमागतeration of the available vertical expansion ratios.
 */
क्रमागत osd_v_exp_ratio अणु
	V_EXP_OFF,
	V_EXP_6_OVER_5,
पूर्ण;

/**
 * क्रमागत osd_zoom_factor
 * @ZOOM_X1: no zoom (x1)
 * @ZOOM_X2: x2 zoom
 * @ZOOM_X4: x4 zoom
 *
 * Description:
 * An क्रमागतeration of the available zoom factors.
 */
क्रमागत osd_zoom_factor अणु
	ZOOM_X1,
	ZOOM_X2,
	ZOOM_X4,
पूर्ण;

/**
 * क्रमागत osd_clut
 * @ROM_CLUT: ROM CLUT
 * @RAM_CLUT: RAM CLUT
 *
 * Description:
 * An क्रमागतeration of the available Color Lookup Tables (CLUTs).
 */
क्रमागत osd_clut अणु
	ROM_CLUT,
	RAM_CLUT,
पूर्ण;

/**
 * क्रमागत osd_rom_clut
 * @ROM_CLUT0: Macपूर्णांकosh CLUT
 * @ROM_CLUT1: CLUT from DM270 and prior devices
 *
 * Description:
 * An क्रमागतeration of the ROM Color Lookup Table (CLUT) options.
 */
क्रमागत osd_rom_clut अणु
	ROM_CLUT0,
	ROM_CLUT1,
पूर्ण;

/**
 * क्रमागत osd_blending_factor
 * @OSD_0_VID_8: OSD pixels are fully transparent
 * @OSD_1_VID_7: OSD pixels contribute 1/8, video pixels contribute 7/8
 * @OSD_2_VID_6: OSD pixels contribute 2/8, video pixels contribute 6/8
 * @OSD_3_VID_5: OSD pixels contribute 3/8, video pixels contribute 5/8
 * @OSD_4_VID_4: OSD pixels contribute 4/8, video pixels contribute 4/8
 * @OSD_5_VID_3: OSD pixels contribute 5/8, video pixels contribute 3/8
 * @OSD_6_VID_2: OSD pixels contribute 6/8, video pixels contribute 2/8
 * @OSD_8_VID_0: OSD pixels are fully opaque
 *
 * Description:
 * An क्रमागतeration of the DaVinci pixel blending factor options.
 */
क्रमागत osd_blending_factor अणु
	OSD_0_VID_8,
	OSD_1_VID_7,
	OSD_2_VID_6,
	OSD_3_VID_5,
	OSD_4_VID_4,
	OSD_5_VID_3,
	OSD_6_VID_2,
	OSD_8_VID_0,
पूर्ण;

/**
 * क्रमागत osd_blink_पूर्णांकerval
 * @BLINK_X1: blink पूर्णांकerval is 1 vertical refresh cycle
 * @BLINK_X2: blink पूर्णांकerval is 2 vertical refresh cycles
 * @BLINK_X3: blink पूर्णांकerval is 3 vertical refresh cycles
 * @BLINK_X4: blink पूर्णांकerval is 4 vertical refresh cycles
 *
 * Description:
 * An क्रमागतeration of the DaVinci pixel blinking पूर्णांकerval options.
 */
क्रमागत osd_blink_पूर्णांकerval अणु
	BLINK_X1,
	BLINK_X2,
	BLINK_X3,
	BLINK_X4,
पूर्ण;

/**
 * क्रमागत osd_cursor_h_width
 * @H_WIDTH_1: horizontal line width is 1 pixel
 * @H_WIDTH_4: horizontal line width is 4 pixels
 * @H_WIDTH_8: horizontal line width is 8 pixels
 * @H_WIDTH_12: horizontal line width is 12 pixels
 * @H_WIDTH_16: horizontal line width is 16 pixels
 * @H_WIDTH_20: horizontal line width is 20 pixels
 * @H_WIDTH_24: horizontal line width is 24 pixels
 * @H_WIDTH_28: horizontal line width is 28 pixels
 */
क्रमागत osd_cursor_h_width अणु
	H_WIDTH_1,
	H_WIDTH_4,
	H_WIDTH_8,
	H_WIDTH_12,
	H_WIDTH_16,
	H_WIDTH_20,
	H_WIDTH_24,
	H_WIDTH_28,
पूर्ण;

/**
 * क्रमागत osd_cursor_v_width
 * @V_WIDTH_1: vertical line width is 1 line
 * @V_WIDTH_2: vertical line width is 2 lines
 * @V_WIDTH_4: vertical line width is 4 lines
 * @V_WIDTH_6: vertical line width is 6 lines
 * @V_WIDTH_8: vertical line width is 8 lines
 * @V_WIDTH_10: vertical line width is 10 lines
 * @V_WIDTH_12: vertical line width is 12 lines
 * @V_WIDTH_14: vertical line width is 14 lines
 */
क्रमागत osd_cursor_v_width अणु
	V_WIDTH_1,
	V_WIDTH_2,
	V_WIDTH_4,
	V_WIDTH_6,
	V_WIDTH_8,
	V_WIDTH_10,
	V_WIDTH_12,
	V_WIDTH_14,
पूर्ण;

/**
 * काष्ठा osd_cursor_config
 * @xsize: horizontal size in pixels
 * @ysize: vertical size in lines
 * @xpos: horizontal offset in pixels from the left edge of the display
 * @ypos: vertical offset in lines from the top of the display
 * @पूर्णांकerlaced: Non-zero अगर the display is पूर्णांकerlaced, or zero otherwise
 * @h_width: horizontal line width
 * @v_width: vertical line width
 * @clut: the CLUT selector (ROM or RAM) क्रम the cursor color
 * @clut_index: an index पूर्णांकo the CLUT क्रम the cursor color
 *
 * Description:
 * A काष्ठाure describing the configuration parameters of the hardware
 * rectangular cursor.
 */
काष्ठा osd_cursor_config अणु
	अचिन्हित xsize;
	अचिन्हित ysize;
	अचिन्हित xpos;
	अचिन्हित ypos;
	पूर्णांक पूर्णांकerlaced;
	क्रमागत osd_cursor_h_width h_width;
	क्रमागत osd_cursor_v_width v_width;
	क्रमागत osd_clut clut;
	अचिन्हित अक्षर clut_index;
पूर्ण;

/**
 * काष्ठा osd_layer_config
 * @pixfmt: pixel क्रमmat
 * @line_length: offset in bytes between start of each line in memory
 * @xsize: number of horizontal pixels displayed per line
 * @ysize: number of lines displayed
 * @xpos: horizontal offset in pixels from the left edge of the display
 * @ypos: vertical offset in lines from the top of the display
 * @पूर्णांकerlaced: Non-zero अगर the display is पूर्णांकerlaced, or zero otherwise
 *
 * Description:
 * A काष्ठाure describing the configuration parameters of an On-Screen Display
 * (OSD) or video layer related to how the image is stored in memory.
 * @line_length must be a multiple of the cache line size (32 bytes).
 */
काष्ठा osd_layer_config अणु
	क्रमागत osd_pix_क्रमmat pixfmt;
	अचिन्हित line_length;
	अचिन्हित xsize;
	अचिन्हित ysize;
	अचिन्हित xpos;
	अचिन्हित ypos;
	पूर्णांक पूर्णांकerlaced;
पूर्ण;

/* parameters that apply on a per-winकरोw (OSD or video) basis */
काष्ठा osd_winकरोw_state अणु
	पूर्णांक is_allocated;
	पूर्णांक is_enabled;
	अचिन्हित दीर्घ fb_base_phys;
	क्रमागत osd_zoom_factor h_zoom;
	क्रमागत osd_zoom_factor v_zoom;
	काष्ठा osd_layer_config lconfig;
पूर्ण;

/* parameters that apply on a per-OSD-winकरोw basis */
काष्ठा osd_osdwin_state अणु
	क्रमागत osd_clut clut;
	क्रमागत osd_blending_factor blend;
	पूर्णांक colorkey_blending;
	अचिन्हित colorkey;
	पूर्णांक rec601_attenuation;
	/* index is pixel value */
	अचिन्हित अक्षर palette_map[16];
पूर्ण;

/* hardware rectangular cursor parameters */
काष्ठा osd_cursor_state अणु
	पूर्णांक is_enabled;
	काष्ठा osd_cursor_config config;
पूर्ण;

काष्ठा osd_state;

काष्ठा vpbe_osd_ops अणु
	पूर्णांक (*initialize)(काष्ठा osd_state *sd);
	पूर्णांक (*request_layer)(काष्ठा osd_state *sd, क्रमागत osd_layer layer);
	व्योम (*release_layer)(काष्ठा osd_state *sd, क्रमागत osd_layer layer);
	पूर्णांक (*enable_layer)(काष्ठा osd_state *sd, क्रमागत osd_layer layer,
			    पूर्णांक otherwin);
	व्योम (*disable_layer)(काष्ठा osd_state *sd, क्रमागत osd_layer layer);
	पूर्णांक (*set_layer_config)(काष्ठा osd_state *sd, क्रमागत osd_layer layer,
				काष्ठा osd_layer_config *lconfig);
	व्योम (*get_layer_config)(काष्ठा osd_state *sd, क्रमागत osd_layer layer,
				 काष्ठा osd_layer_config *lconfig);
	व्योम (*start_layer)(काष्ठा osd_state *sd, क्रमागत osd_layer layer,
			    अचिन्हित दीर्घ fb_base_phys,
			    अचिन्हित दीर्घ cbcr_ofst);
	व्योम (*set_left_margin)(काष्ठा osd_state *sd, u32 val);
	व्योम (*set_top_margin)(काष्ठा osd_state *sd, u32 val);
	व्योम (*set_पूर्णांकerpolation_filter)(काष्ठा osd_state *sd, पूर्णांक filter);
	पूर्णांक (*set_vid_expansion)(काष्ठा osd_state *sd,
					क्रमागत osd_h_exp_ratio h_exp,
					क्रमागत osd_v_exp_ratio v_exp);
	व्योम (*get_vid_expansion)(काष्ठा osd_state *sd,
					क्रमागत osd_h_exp_ratio *h_exp,
					क्रमागत osd_v_exp_ratio *v_exp);
	व्योम (*set_zoom)(काष्ठा osd_state *sd, क्रमागत osd_layer layer,
				क्रमागत osd_zoom_factor h_zoom,
				क्रमागत osd_zoom_factor v_zoom);
पूर्ण;

काष्ठा osd_state अणु
	क्रमागत vpbe_version vpbe_type;
	spinlock_t lock;
	काष्ठा device *dev;
	dma_addr_t osd_base_phys;
	व्योम __iomem *osd_base;
	अचिन्हित दीर्घ osd_size;
	/* 1-->the isr will toggle the VID0 ping-pong buffer */
	पूर्णांक pingpong;
	पूर्णांक पूर्णांकerpolation_filter;
	पूर्णांक field_inversion;
	क्रमागत osd_h_exp_ratio osd_h_exp;
	क्रमागत osd_v_exp_ratio osd_v_exp;
	क्रमागत osd_h_exp_ratio vid_h_exp;
	क्रमागत osd_v_exp_ratio vid_v_exp;
	क्रमागत osd_clut backg_clut;
	अचिन्हित backg_clut_index;
	क्रमागत osd_rom_clut rom_clut;
	पूर्णांक is_blinking;
	/* attribute winकरोw blinking enabled */
	क्रमागत osd_blink_पूर्णांकerval blink;
	/* YCbCrI or YCrCbI */
	क्रमागत osd_pix_क्रमmat yc_pixfmt;
	/* columns are Y, Cb, Cr */
	अचिन्हित अक्षर clut_ram[256][3];
	काष्ठा osd_cursor_state cursor;
	/* OSD0, VID0, OSD1, VID1 */
	काष्ठा osd_winकरोw_state win[4];
	/* OSD0, OSD1 */
	काष्ठा osd_osdwin_state osdwin[2];
	/* OSD device Operations */
	काष्ठा vpbe_osd_ops ops;
पूर्ण;

काष्ठा osd_platक्रमm_data अणु
	पूर्णांक  field_inv_wa_enable;
पूर्ण;

#पूर्ण_अगर
