<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Avionic Design GmbH
 * Copyright (C) 2012 NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित TEGRA_DC_H
#घोषणा TEGRA_DC_H 1

#समावेश <linux/host1x.h>

#समावेश <drm/drm_crtc.h>

#समावेश "drm.h"

काष्ठा tegra_output;

काष्ठा tegra_dc_state अणु
	काष्ठा drm_crtc_state base;

	काष्ठा clk *clk;
	अचिन्हित दीर्घ pclk;
	अचिन्हित पूर्णांक भाग;

	u32 planes;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_dc_state *to_dc_state(काष्ठा drm_crtc_state *state)
अणु
	अगर (state)
		वापस container_of(state, काष्ठा tegra_dc_state, base);

	वापस शून्य;
पूर्ण

काष्ठा tegra_dc_stats अणु
	अचिन्हित दीर्घ frames;
	अचिन्हित दीर्घ vblank;
	अचिन्हित दीर्घ underflow;
	अचिन्हित दीर्घ overflow;
पूर्ण;

काष्ठा tegra_winकरोwgroup_soc अणु
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक dc;
	स्थिर अचिन्हित पूर्णांक *winकरोws;
	अचिन्हित पूर्णांक num_winकरोws;
पूर्ण;

काष्ठा tegra_dc_soc_info अणु
	bool supports_background_color;
	bool supports_पूर्णांकerlacing;
	bool supports_cursor;
	bool supports_block_linear;
	bool supports_sector_layout;
	bool has_legacy_blending;
	अचिन्हित पूर्णांक pitch_align;
	bool has_घातergate;
	bool coupled_pm;
	bool has_nvdisplay;
	स्थिर काष्ठा tegra_winकरोwgroup_soc *wgrps;
	अचिन्हित पूर्णांक num_wgrps;
	स्थिर u32 *primary_क्रमmats;
	अचिन्हित पूर्णांक num_primary_क्रमmats;
	स्थिर u32 *overlay_क्रमmats;
	अचिन्हित पूर्णांक num_overlay_क्रमmats;
	स्थिर u64 *modअगरiers;
	bool has_win_a_without_filters;
	bool has_win_c_without_vert_filter;
पूर्ण;

काष्ठा tegra_dc अणु
	काष्ठा host1x_client client;
	काष्ठा host1x_syncpt *syncpt;
	काष्ठा device *dev;

	काष्ठा drm_crtc base;
	अचिन्हित पूर्णांक घातergate;
	पूर्णांक pipe;

	काष्ठा clk *clk;
	काष्ठा reset_control *rst;
	व्योम __iomem *regs;
	पूर्णांक irq;

	काष्ठा tegra_output *rgb;

	काष्ठा tegra_dc_stats stats;
	काष्ठा list_head list;

	काष्ठा drm_info_list *debugfs_files;

	स्थिर काष्ठा tegra_dc_soc_info *soc;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_dc *
host1x_client_to_dc(काष्ठा host1x_client *client)
अणु
	वापस container_of(client, काष्ठा tegra_dc, client);
पूर्ण

अटल अंतरभूत काष्ठा tegra_dc *to_tegra_dc(काष्ठा drm_crtc *crtc)
अणु
	वापस crtc ? container_of(crtc, काष्ठा tegra_dc, base) : शून्य;
पूर्ण

अटल अंतरभूत व्योम tegra_dc_ग_लिखोl(काष्ठा tegra_dc *dc, u32 value,
				   अचिन्हित पूर्णांक offset)
अणु
	trace_dc_ग_लिखोl(dc->dev, offset, value);
	ग_लिखोl(value, dc->regs + (offset << 2));
पूर्ण

अटल अंतरभूत u32 tegra_dc_पढ़ोl(काष्ठा tegra_dc *dc, अचिन्हित पूर्णांक offset)
अणु
	u32 value = पढ़ोl(dc->regs + (offset << 2));

	trace_dc_पढ़ोl(dc->dev, offset, value);

	वापस value;
पूर्ण

काष्ठा tegra_dc_winकरोw अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक x;
		अचिन्हित पूर्णांक y;
		अचिन्हित पूर्णांक w;
		अचिन्हित पूर्णांक h;
	पूर्ण src;
	काष्ठा अणु
		अचिन्हित पूर्णांक x;
		अचिन्हित पूर्णांक y;
		अचिन्हित पूर्णांक w;
		अचिन्हित पूर्णांक h;
	पूर्ण dst;
	अचिन्हित पूर्णांक bits_per_pixel;
	अचिन्हित पूर्णांक stride[2];
	अचिन्हित दीर्घ base[3];
	अचिन्हित पूर्णांक zpos;
	bool reflect_x;
	bool reflect_y;

	काष्ठा tegra_bo_tiling tiling;
	u32 क्रमmat;
	u32 swap;
पूर्ण;

/* from dc.c */
bool tegra_dc_has_output(काष्ठा tegra_dc *dc, काष्ठा device *dev);
व्योम tegra_dc_commit(काष्ठा tegra_dc *dc);
पूर्णांक tegra_dc_state_setup_घड़ी(काष्ठा tegra_dc *dc,
			       काष्ठा drm_crtc_state *crtc_state,
			       काष्ठा clk *clk, अचिन्हित दीर्घ pclk,
			       अचिन्हित पूर्णांक भाग);

/* from rgb.c */
पूर्णांक tegra_dc_rgb_probe(काष्ठा tegra_dc *dc);
पूर्णांक tegra_dc_rgb_हटाओ(काष्ठा tegra_dc *dc);
पूर्णांक tegra_dc_rgb_init(काष्ठा drm_device *drm, काष्ठा tegra_dc *dc);
पूर्णांक tegra_dc_rgb_निकास(काष्ठा tegra_dc *dc);

#घोषणा DC_CMD_GENERAL_INCR_SYNCPT		0x000
#घोषणा DC_CMD_GENERAL_INCR_SYNCPT_CNTRL	0x001
#घोषणा  SYNCPT_CNTRL_NO_STALL   (1 << 8)
#घोषणा  SYNCPT_CNTRL_SOFT_RESET (1 << 0)
#घोषणा DC_CMD_GENERAL_INCR_SYNCPT_ERROR	0x002
#घोषणा DC_CMD_WIN_A_INCR_SYNCPT		0x008
#घोषणा DC_CMD_WIN_A_INCR_SYNCPT_CNTRL		0x009
#घोषणा DC_CMD_WIN_A_INCR_SYNCPT_ERROR		0x00a
#घोषणा DC_CMD_WIN_B_INCR_SYNCPT		0x010
#घोषणा DC_CMD_WIN_B_INCR_SYNCPT_CNTRL		0x011
#घोषणा DC_CMD_WIN_B_INCR_SYNCPT_ERROR		0x012
#घोषणा DC_CMD_WIN_C_INCR_SYNCPT		0x018
#घोषणा DC_CMD_WIN_C_INCR_SYNCPT_CNTRL		0x019
#घोषणा DC_CMD_WIN_C_INCR_SYNCPT_ERROR		0x01a
#घोषणा DC_CMD_CONT_SYNCPT_VSYNC		0x028
#घोषणा  SYNCPT_VSYNC_ENABLE (1 << 8)
#घोषणा DC_CMD_DISPLAY_COMMAND_OPTION0		0x031
#घोषणा DC_CMD_DISPLAY_COMMAND			0x032
#घोषणा DISP_CTRL_MODE_STOP (0 << 5)
#घोषणा DISP_CTRL_MODE_C_DISPLAY (1 << 5)
#घोषणा DISP_CTRL_MODE_NC_DISPLAY (2 << 5)
#घोषणा DISP_CTRL_MODE_MASK (3 << 5)
#घोषणा DC_CMD_SIGNAL_RAISE			0x033
#घोषणा DC_CMD_DISPLAY_POWER_CONTROL		0x036
#घोषणा PW0_ENABLE (1 <<  0)
#घोषणा PW1_ENABLE (1 <<  2)
#घोषणा PW2_ENABLE (1 <<  4)
#घोषणा PW3_ENABLE (1 <<  6)
#घोषणा PW4_ENABLE (1 <<  8)
#घोषणा PM0_ENABLE (1 << 16)
#घोषणा PM1_ENABLE (1 << 18)

#घोषणा DC_CMD_INT_STATUS			0x037
#घोषणा DC_CMD_INT_MASK				0x038
#घोषणा DC_CMD_INT_ENABLE			0x039
#घोषणा DC_CMD_INT_TYPE				0x03a
#घोषणा DC_CMD_INT_POLARITY			0x03b
#घोषणा CTXSW_INT                (1 << 0)
#घोषणा FRAME_END_INT            (1 << 1)
#घोषणा VBLANK_INT               (1 << 2)
#घोषणा V_PULSE3_INT             (1 << 4)
#घोषणा V_PULSE2_INT             (1 << 5)
#घोषणा REGION_CRC_INT           (1 << 6)
#घोषणा REG_TMOUT_INT            (1 << 7)
#घोषणा WIN_A_UF_INT             (1 << 8)
#घोषणा WIN_B_UF_INT             (1 << 9)
#घोषणा WIN_C_UF_INT             (1 << 10)
#घोषणा MSF_INT                  (1 << 12)
#घोषणा WIN_A_OF_INT             (1 << 14)
#घोषणा WIN_B_OF_INT             (1 << 15)
#घोषणा WIN_C_OF_INT             (1 << 16)
#घोषणा HEAD_UF_INT              (1 << 23)
#घोषणा SD3_BUCKET_WALK_DONE_INT (1 << 24)
#घोषणा DSC_OBUF_UF_INT          (1 << 26)
#घोषणा DSC_RBUF_UF_INT          (1 << 27)
#घोषणा DSC_BBUF_UF_INT          (1 << 28)
#घोषणा DSC_TO_UF_INT            (1 << 29)

#घोषणा DC_CMD_SIGNAL_RAISE1			0x03c
#घोषणा DC_CMD_SIGNAL_RAISE2			0x03d
#घोषणा DC_CMD_SIGNAL_RAISE3			0x03e

#घोषणा DC_CMD_STATE_ACCESS			0x040
#घोषणा READ_MUX  (1 << 0)
#घोषणा WRITE_MUX (1 << 2)

#घोषणा DC_CMD_STATE_CONTROL			0x041
#घोषणा GENERAL_ACT_REQ (1 <<  0)
#घोषणा WIN_A_ACT_REQ   (1 <<  1)
#घोषणा WIN_B_ACT_REQ   (1 <<  2)
#घोषणा WIN_C_ACT_REQ   (1 <<  3)
#घोषणा CURSOR_ACT_REQ  (1 <<  7)
#घोषणा GENERAL_UPDATE  (1 <<  8)
#घोषणा WIN_A_UPDATE    (1 <<  9)
#घोषणा WIN_B_UPDATE    (1 << 10)
#घोषणा WIN_C_UPDATE    (1 << 11)
#घोषणा CURSOR_UPDATE   (1 << 15)
#घोषणा COMMON_ACTREQ   (1 << 16)
#घोषणा COMMON_UPDATE   (1 << 17)
#घोषणा NC_HOST_TRIG    (1 << 24)

#घोषणा DC_CMD_DISPLAY_WINDOW_HEADER		0x042
#घोषणा WINDOW_A_SELECT (1 << 4)
#घोषणा WINDOW_B_SELECT (1 << 5)
#घोषणा WINDOW_C_SELECT (1 << 6)

#घोषणा DC_CMD_REG_ACT_CONTROL			0x043

#घोषणा DC_COM_CRC_CONTROL			0x300
#घोषणा  DC_COM_CRC_CONTROL_ALWAYS (1 << 3)
#घोषणा  DC_COM_CRC_CONTROL_FULL_FRAME  (0 << 2)
#घोषणा  DC_COM_CRC_CONTROL_ACTIVE_DATA (1 << 2)
#घोषणा  DC_COM_CRC_CONTROL_WAIT (1 << 1)
#घोषणा  DC_COM_CRC_CONTROL_ENABLE (1 << 0)
#घोषणा DC_COM_CRC_CHECKSUM			0x301
#घोषणा DC_COM_PIN_OUTPUT_ENABLE(x) (0x302 + (x))
#घोषणा DC_COM_PIN_OUTPUT_POLARITY(x) (0x306 + (x))
#घोषणा LVS_OUTPUT_POLARITY_LOW (1 << 28)
#घोषणा LHS_OUTPUT_POLARITY_LOW (1 << 30)
#घोषणा DC_COM_PIN_OUTPUT_DATA(x) (0x30a + (x))
#घोषणा DC_COM_PIN_INPUT_ENABLE(x) (0x30e + (x))
#घोषणा DC_COM_PIN_INPUT_DATA(x) (0x312 + (x))
#घोषणा DC_COM_PIN_OUTPUT_SELECT(x) (0x314 + (x))

#घोषणा DC_COM_PIN_MISC_CONTROL			0x31b
#घोषणा DC_COM_PIN_PM0_CONTROL			0x31c
#घोषणा DC_COM_PIN_PM0_DUTY_CYCLE		0x31d
#घोषणा DC_COM_PIN_PM1_CONTROL			0x31e
#घोषणा DC_COM_PIN_PM1_DUTY_CYCLE		0x31f

#घोषणा DC_COM_SPI_CONTROL			0x320
#घोषणा DC_COM_SPI_START_BYTE			0x321
#घोषणा DC_COM_HSPI_WRITE_DATA_AB		0x322
#घोषणा DC_COM_HSPI_WRITE_DATA_CD		0x323
#घोषणा DC_COM_HSPI_CS_DC			0x324
#घोषणा DC_COM_SCRATCH_REGISTER_A		0x325
#घोषणा DC_COM_SCRATCH_REGISTER_B		0x326
#घोषणा DC_COM_GPIO_CTRL			0x327
#घोषणा DC_COM_GPIO_DEBOUNCE_COUNTER		0x328
#घोषणा DC_COM_CRC_CHECKSUM_LATCHED		0x329

#घोषणा DC_COM_RG_UNDERFLOW			0x365
#घोषणा  UNDERFLOW_MODE_RED      (1 << 8)
#घोषणा  UNDERFLOW_REPORT_ENABLE (1 << 0)

#घोषणा DC_DISP_DISP_SIGNAL_OPTIONS0		0x400
#घोषणा H_PULSE0_ENABLE (1 <<  8)
#घोषणा H_PULSE1_ENABLE (1 << 10)
#घोषणा H_PULSE2_ENABLE (1 << 12)

#घोषणा DC_DISP_DISP_SIGNAL_OPTIONS1		0x401

#घोषणा DC_DISP_DISP_WIN_OPTIONS		0x402
#घोषणा HDMI_ENABLE	(1 << 30)
#घोषणा DSI_ENABLE	(1 << 29)
#घोषणा SOR1_TIMING_CYA	(1 << 27)
#घोषणा CURSOR_ENABLE	(1 << 16)

#घोषणा SOR_ENABLE(x)	(1 << (25 + (((x) > 1) ? ((x) + 1) : (x))))

#घोषणा DC_DISP_DISP_MEM_HIGH_PRIORITY		0x403
#घोषणा CURSOR_THRESHOLD(x)   (((x) & 0x03) << 24)
#घोषणा WINDOW_A_THRESHOLD(x) (((x) & 0x7f) << 16)
#घोषणा WINDOW_B_THRESHOLD(x) (((x) & 0x7f) <<  8)
#घोषणा WINDOW_C_THRESHOLD(x) (((x) & 0xff) <<  0)

#घोषणा DC_DISP_DISP_MEM_HIGH_PRIORITY_TIMER	0x404
#घोषणा CURSOR_DELAY(x)   (((x) & 0x3f) << 24)
#घोषणा WINDOW_A_DELAY(x) (((x) & 0x3f) << 16)
#घोषणा WINDOW_B_DELAY(x) (((x) & 0x3f) <<  8)
#घोषणा WINDOW_C_DELAY(x) (((x) & 0x3f) <<  0)

#घोषणा DC_DISP_DISP_TIMING_OPTIONS		0x405
#घोषणा VSYNC_H_POSITION(x) ((x) & 0xfff)

#घोषणा DC_DISP_REF_TO_SYNC			0x406
#घोषणा DC_DISP_SYNC_WIDTH			0x407
#घोषणा DC_DISP_BACK_PORCH			0x408
#घोषणा DC_DISP_ACTIVE				0x409
#घोषणा DC_DISP_FRONT_PORCH			0x40a
#घोषणा DC_DISP_H_PULSE0_CONTROL		0x40b
#घोषणा DC_DISP_H_PULSE0_POSITION_A		0x40c
#घोषणा DC_DISP_H_PULSE0_POSITION_B		0x40d
#घोषणा DC_DISP_H_PULSE0_POSITION_C		0x40e
#घोषणा DC_DISP_H_PULSE0_POSITION_D		0x40f
#घोषणा DC_DISP_H_PULSE1_CONTROL		0x410
#घोषणा DC_DISP_H_PULSE1_POSITION_A		0x411
#घोषणा DC_DISP_H_PULSE1_POSITION_B		0x412
#घोषणा DC_DISP_H_PULSE1_POSITION_C		0x413
#घोषणा DC_DISP_H_PULSE1_POSITION_D		0x414
#घोषणा DC_DISP_H_PULSE2_CONTROL		0x415
#घोषणा DC_DISP_H_PULSE2_POSITION_A		0x416
#घोषणा DC_DISP_H_PULSE2_POSITION_B		0x417
#घोषणा DC_DISP_H_PULSE2_POSITION_C		0x418
#घोषणा DC_DISP_H_PULSE2_POSITION_D		0x419
#घोषणा DC_DISP_V_PULSE0_CONTROL		0x41a
#घोषणा DC_DISP_V_PULSE0_POSITION_A		0x41b
#घोषणा DC_DISP_V_PULSE0_POSITION_B		0x41c
#घोषणा DC_DISP_V_PULSE0_POSITION_C		0x41d
#घोषणा DC_DISP_V_PULSE1_CONTROL		0x41e
#घोषणा DC_DISP_V_PULSE1_POSITION_A		0x41f
#घोषणा DC_DISP_V_PULSE1_POSITION_B		0x420
#घोषणा DC_DISP_V_PULSE1_POSITION_C		0x421
#घोषणा DC_DISP_V_PULSE2_CONTROL		0x422
#घोषणा DC_DISP_V_PULSE2_POSITION_A		0x423
#घोषणा DC_DISP_V_PULSE3_CONTROL		0x424
#घोषणा DC_DISP_V_PULSE3_POSITION_A		0x425
#घोषणा DC_DISP_M0_CONTROL			0x426
#घोषणा DC_DISP_M1_CONTROL			0x427
#घोषणा DC_DISP_DI_CONTROL			0x428
#घोषणा DC_DISP_PP_CONTROL			0x429
#घोषणा DC_DISP_PP_SELECT_A			0x42a
#घोषणा DC_DISP_PP_SELECT_B			0x42b
#घोषणा DC_DISP_PP_SELECT_C			0x42c
#घोषणा DC_DISP_PP_SELECT_D			0x42d

#घोषणा PULSE_MODE_NORMAL    (0 << 3)
#घोषणा PULSE_MODE_ONE_CLOCK (1 << 3)
#घोषणा PULSE_POLARITY_HIGH  (0 << 4)
#घोषणा PULSE_POLARITY_LOW   (1 << 4)
#घोषणा PULSE_QUAL_ALWAYS    (0 << 6)
#घोषणा PULSE_QUAL_VACTIVE   (2 << 6)
#घोषणा PULSE_QUAL_VACTIVE1  (3 << 6)
#घोषणा PULSE_LAST_START_A   (0 << 8)
#घोषणा PULSE_LAST_END_A     (1 << 8)
#घोषणा PULSE_LAST_START_B   (2 << 8)
#घोषणा PULSE_LAST_END_B     (3 << 8)
#घोषणा PULSE_LAST_START_C   (4 << 8)
#घोषणा PULSE_LAST_END_C     (5 << 8)
#घोषणा PULSE_LAST_START_D   (6 << 8)
#घोषणा PULSE_LAST_END_D     (7 << 8)

#घोषणा PULSE_START(x) (((x) & 0xfff) <<  0)
#घोषणा PULSE_END(x)   (((x) & 0xfff) << 16)

#घोषणा DC_DISP_DISP_CLOCK_CONTROL		0x42e
#घोषणा PIXEL_CLK_DIVIDER_PCD1  (0 << 8)
#घोषणा PIXEL_CLK_DIVIDER_PCD1H (1 << 8)
#घोषणा PIXEL_CLK_DIVIDER_PCD2  (2 << 8)
#घोषणा PIXEL_CLK_DIVIDER_PCD3  (3 << 8)
#घोषणा PIXEL_CLK_DIVIDER_PCD4  (4 << 8)
#घोषणा PIXEL_CLK_DIVIDER_PCD6  (5 << 8)
#घोषणा PIXEL_CLK_DIVIDER_PCD8  (6 << 8)
#घोषणा PIXEL_CLK_DIVIDER_PCD9  (7 << 8)
#घोषणा PIXEL_CLK_DIVIDER_PCD12 (8 << 8)
#घोषणा PIXEL_CLK_DIVIDER_PCD16 (9 << 8)
#घोषणा PIXEL_CLK_DIVIDER_PCD18 (10 << 8)
#घोषणा PIXEL_CLK_DIVIDER_PCD24 (11 << 8)
#घोषणा PIXEL_CLK_DIVIDER_PCD13 (12 << 8)
#घोषणा SHIFT_CLK_DIVIDER(x)    ((x) & 0xff)

#घोषणा DC_DISP_DISP_INTERFACE_CONTROL		0x42f
#घोषणा DISP_DATA_FORMAT_DF1P1C    (0 << 0)
#घोषणा DISP_DATA_FORMAT_DF1P2C24B (1 << 0)
#घोषणा DISP_DATA_FORMAT_DF1P2C18B (2 << 0)
#घोषणा DISP_DATA_FORMAT_DF1P2C16B (3 << 0)
#घोषणा DISP_DATA_FORMAT_DF2S      (4 << 0)
#घोषणा DISP_DATA_FORMAT_DF3S      (5 << 0)
#घोषणा DISP_DATA_FORMAT_DFSPI     (6 << 0)
#घोषणा DISP_DATA_FORMAT_DF1P3C24B (7 << 0)
#घोषणा DISP_DATA_FORMAT_DF1P3C18B (8 << 0)
#घोषणा DISP_ALIGNMENT_MSB         (0 << 8)
#घोषणा DISP_ALIGNMENT_LSB         (1 << 8)
#घोषणा DISP_ORDER_RED_BLUE        (0 << 9)
#घोषणा DISP_ORDER_BLUE_RED        (1 << 9)

#घोषणा DC_DISP_DISP_COLOR_CONTROL		0x430
#घोषणा BASE_COLOR_SIZE666     ( 0 << 0)
#घोषणा BASE_COLOR_SIZE111     ( 1 << 0)
#घोषणा BASE_COLOR_SIZE222     ( 2 << 0)
#घोषणा BASE_COLOR_SIZE333     ( 3 << 0)
#घोषणा BASE_COLOR_SIZE444     ( 4 << 0)
#घोषणा BASE_COLOR_SIZE555     ( 5 << 0)
#घोषणा BASE_COLOR_SIZE565     ( 6 << 0)
#घोषणा BASE_COLOR_SIZE332     ( 7 << 0)
#घोषणा BASE_COLOR_SIZE888     ( 8 << 0)
#घोषणा BASE_COLOR_SIZE101010  (10 << 0)
#घोषणा BASE_COLOR_SIZE121212  (12 << 0)
#घोषणा DITHER_CONTROL_MASK    (3 << 8)
#घोषणा DITHER_CONTROL_DISABLE (0 << 8)
#घोषणा DITHER_CONTROL_ORDERED (2 << 8)
#घोषणा DITHER_CONTROL_ERRDIFF (3 << 8)
#घोषणा BASE_COLOR_SIZE_MASK   (0xf << 0)
#घोषणा BASE_COLOR_SIZE_666    (  0 << 0)
#घोषणा BASE_COLOR_SIZE_111    (  1 << 0)
#घोषणा BASE_COLOR_SIZE_222    (  2 << 0)
#घोषणा BASE_COLOR_SIZE_333    (  3 << 0)
#घोषणा BASE_COLOR_SIZE_444    (  4 << 0)
#घोषणा BASE_COLOR_SIZE_555    (  5 << 0)
#घोषणा BASE_COLOR_SIZE_565    (  6 << 0)
#घोषणा BASE_COLOR_SIZE_332    (  7 << 0)
#घोषणा BASE_COLOR_SIZE_888    (  8 << 0)
#घोषणा BASE_COLOR_SIZE_101010 ( 10 << 0)
#घोषणा BASE_COLOR_SIZE_121212 ( 12 << 0)

#घोषणा DC_DISP_SHIFT_CLOCK_OPTIONS		0x431
#घोषणा  SC1_H_QUALIFIER_NONE	(1 << 16)
#घोषणा  SC0_H_QUALIFIER_NONE	(1 <<  0)

#घोषणा DC_DISP_DATA_ENABLE_OPTIONS		0x432
#घोषणा DE_SELECT_ACTIVE_BLANK  (0 << 0)
#घोषणा DE_SELECT_ACTIVE        (1 << 0)
#घोषणा DE_SELECT_ACTIVE_IS     (2 << 0)
#घोषणा DE_CONTROL_ONECLK       (0 << 2)
#घोषणा DE_CONTROL_NORMAL       (1 << 2)
#घोषणा DE_CONTROL_EARLY_EXT    (2 << 2)
#घोषणा DE_CONTROL_EARLY        (3 << 2)
#घोषणा DE_CONTROL_ACTIVE_BLANK (4 << 2)

#घोषणा DC_DISP_SERIAL_INTERFACE_OPTIONS	0x433
#घोषणा DC_DISP_LCD_SPI_OPTIONS			0x434
#घोषणा DC_DISP_BORDER_COLOR			0x435
#घोषणा DC_DISP_COLOR_KEY0_LOWER		0x436
#घोषणा DC_DISP_COLOR_KEY0_UPPER		0x437
#घोषणा DC_DISP_COLOR_KEY1_LOWER		0x438
#घोषणा DC_DISP_COLOR_KEY1_UPPER		0x439

#घोषणा DC_DISP_CURSOR_FOREGROUND		0x43c
#घोषणा DC_DISP_CURSOR_BACKGROUND		0x43d

#घोषणा DC_DISP_CURSOR_START_ADDR		0x43e
#घोषणा CURSOR_CLIP_DISPLAY	(0 << 28)
#घोषणा CURSOR_CLIP_WIN_A	(1 << 28)
#घोषणा CURSOR_CLIP_WIN_B	(2 << 28)
#घोषणा CURSOR_CLIP_WIN_C	(3 << 28)
#घोषणा CURSOR_SIZE_32x32	(0 << 24)
#घोषणा CURSOR_SIZE_64x64	(1 << 24)
#घोषणा CURSOR_SIZE_128x128	(2 << 24)
#घोषणा CURSOR_SIZE_256x256	(3 << 24)
#घोषणा DC_DISP_CURSOR_START_ADDR_NS		0x43f

#घोषणा DC_DISP_CURSOR_POSITION			0x440
#घोषणा DC_DISP_CURSOR_POSITION_NS		0x441

#घोषणा DC_DISP_INIT_SEQ_CONTROL		0x442
#घोषणा DC_DISP_SPI_INIT_SEQ_DATA_A		0x443
#घोषणा DC_DISP_SPI_INIT_SEQ_DATA_B		0x444
#घोषणा DC_DISP_SPI_INIT_SEQ_DATA_C		0x445
#घोषणा DC_DISP_SPI_INIT_SEQ_DATA_D		0x446

#घोषणा DC_DISP_DC_MCCIF_FIFOCTRL		0x480
#घोषणा DC_DISP_MCCIF_DISPLAY0A_HYST		0x481
#घोषणा DC_DISP_MCCIF_DISPLAY0B_HYST		0x482
#घोषणा DC_DISP_MCCIF_DISPLAY1A_HYST		0x483
#घोषणा DC_DISP_MCCIF_DISPLAY1B_HYST		0x484

#घोषणा DC_DISP_DAC_CRT_CTRL			0x4c0
#घोषणा DC_DISP_DISP_MISC_CONTROL		0x4c1
#घोषणा DC_DISP_SD_CONTROL			0x4c2
#घोषणा DC_DISP_SD_CSC_COEFF			0x4c3
#घोषणा DC_DISP_SD_LUT(x)			(0x4c4 + (x))
#घोषणा DC_DISP_SD_FLICKER_CONTROL		0x4cd
#घोषणा DC_DISP_DC_PIXEL_COUNT			0x4ce
#घोषणा DC_DISP_SD_HISTOGRAM(x)			(0x4cf + (x))
#घोषणा DC_DISP_SD_BL_PARAMETERS		0x4d7
#घोषणा DC_DISP_SD_BL_TF(x)			(0x4d8 + (x))
#घोषणा DC_DISP_SD_BL_CONTROL			0x4dc
#घोषणा DC_DISP_SD_HW_K_VALUES			0x4dd
#घोषणा DC_DISP_SD_MAN_K_VALUES			0x4de

#घोषणा DC_DISP_BLEND_BACKGROUND_COLOR		0x4e4
#घोषणा  BACKGROUND_COLOR_ALPHA(x) (((x) & 0xff) << 24)
#घोषणा  BACKGROUND_COLOR_BLUE(x)  (((x) & 0xff) << 16)
#घोषणा  BACKGROUND_COLOR_GREEN(x) (((x) & 0xff) << 8)
#घोषणा  BACKGROUND_COLOR_RED(x)   (((x) & 0xff) << 0)

#घोषणा DC_DISP_INTERLACE_CONTROL		0x4e5
#घोषणा  INTERLACE_STATUS (1 << 2)
#घोषणा  INTERLACE_START  (1 << 1)
#घोषणा  INTERLACE_ENABLE (1 << 0)

#घोषणा DC_DISP_CURSOR_START_ADDR_HI		0x4ec
#घोषणा DC_DISP_BLEND_CURSOR_CONTROL		0x4f1
#घोषणा CURSOR_COMPOSITION_MODE_BLEND		(0 << 25)
#घोषणा CURSOR_COMPOSITION_MODE_XOR		(1 << 25)
#घोषणा CURSOR_MODE_LEGACY			(0 << 24)
#घोषणा CURSOR_MODE_NORMAL			(1 << 24)
#घोषणा CURSOR_DST_BLEND_ZERO			(0 << 16)
#घोषणा CURSOR_DST_BLEND_K1			(1 << 16)
#घोषणा CURSOR_DST_BLEND_NEG_K1_TIMES_SRC	(2 << 16)
#घोषणा CURSOR_DST_BLEND_MASK			(3 << 16)
#घोषणा CURSOR_SRC_BLEND_K1			(0 << 8)
#घोषणा CURSOR_SRC_BLEND_K1_TIMES_SRC		(1 << 8)
#घोषणा CURSOR_SRC_BLEND_MASK			(3 << 8)
#घोषणा CURSOR_ALPHA				0xff

#घोषणा DC_WIN_CORE_ACT_CONTROL 0x50e
#घोषणा  VCOUNTER (0 << 0)
#घोषणा  HCOUNTER (1 << 0)

#घोषणा DC_WIN_CORE_IHUB_WGRP_LATENCY_CTLA 0x543
#घोषणा  LATENCY_CTL_MODE_ENABLE (1 << 2)

#घोषणा DC_WIN_CORE_IHUB_WGRP_LATENCY_CTLB 0x544
#घोषणा  WATERMARK_MASK 0x1fffffff

#घोषणा DC_WIN_CORE_PRECOMP_WGRP_PIPE_METER 0x560
#घोषणा  PIPE_METER_INT(x)  (((x) & 0xff) << 8)
#घोषणा  PIPE_METER_FRAC(x) (((x) & 0xff) << 0)

#घोषणा DC_WIN_CORE_IHUB_WGRP_POOL_CONFIG 0x561
#घोषणा  MEMPOOL_ENTRIES(x) (((x) & 0xffff) << 0)

#घोषणा DC_WIN_CORE_IHUB_WGRP_FETCH_METER 0x562
#घोषणा  SLOTS(x) (((x) & 0xff) << 0)

#घोषणा DC_WIN_CORE_IHUB_LINEBUF_CONFIG 0x563
#घोषणा  MODE_TWO_LINES  (0 << 14)
#घोषणा  MODE_FOUR_LINES (1 << 14)

#घोषणा DC_WIN_CORE_IHUB_THREAD_GROUP 0x568
#घोषणा  THREAD_NUM_MASK (0x1f << 1)
#घोषणा  THREAD_NUM(x) (((x) & 0x1f) << 1)
#घोषणा  THREAD_GROUP_ENABLE (1 << 0)

#घोषणा DC_WIN_H_FILTER_P(p)			(0x601 + (p))
#घोषणा DC_WIN_V_FILTER_P(p)			(0x619 + (p))

#घोषणा DC_WIN_CSC_YOF				0x611
#घोषणा DC_WIN_CSC_KYRGB			0x612
#घोषणा DC_WIN_CSC_KUR				0x613
#घोषणा DC_WIN_CSC_KVR				0x614
#घोषणा DC_WIN_CSC_KUG				0x615
#घोषणा DC_WIN_CSC_KVG				0x616
#घोषणा DC_WIN_CSC_KUB				0x617
#घोषणा DC_WIN_CSC_KVB				0x618

#घोषणा DC_WIN_WIN_OPTIONS			0x700
#घोषणा H_सूचीECTION  (1 <<  0)
#घोषणा V_सूचीECTION  (1 <<  2)
#घोषणा COLOR_EXPAND (1 <<  6)
#घोषणा H_FILTER     (1 <<  8)
#घोषणा V_FILTER     (1 << 10)
#घोषणा CSC_ENABLE   (1 << 18)
#घोषणा WIN_ENABLE   (1 << 30)

#घोषणा DC_WIN_BYTE_SWAP			0x701
#घोषणा BYTE_SWAP_NOSWAP  (0 << 0)
#घोषणा BYTE_SWAP_SWAP2   (1 << 0)
#घोषणा BYTE_SWAP_SWAP4   (2 << 0)
#घोषणा BYTE_SWAP_SWAP4HW (3 << 0)

#घोषणा DC_WIN_BUFFER_CONTROL			0x702
#घोषणा BUFFER_CONTROL_HOST  (0 << 0)
#घोषणा BUFFER_CONTROL_VI    (1 << 0)
#घोषणा BUFFER_CONTROL_EPP   (2 << 0)
#घोषणा BUFFER_CONTROL_MPEGE (3 << 0)
#घोषणा BUFFER_CONTROL_SB2D  (4 << 0)

#घोषणा DC_WIN_COLOR_DEPTH			0x703
#घोषणा WIN_COLOR_DEPTH_P1              0
#घोषणा WIN_COLOR_DEPTH_P2              1
#घोषणा WIN_COLOR_DEPTH_P4              2
#घोषणा WIN_COLOR_DEPTH_P8              3
#घोषणा WIN_COLOR_DEPTH_B4G4R4A4        4
#घोषणा WIN_COLOR_DEPTH_B5G5R5A1        5
#घोषणा WIN_COLOR_DEPTH_B5G6R5          6
#घोषणा WIN_COLOR_DEPTH_A1B5G5R5        7
#घोषणा WIN_COLOR_DEPTH_B8G8R8A8       12
#घोषणा WIN_COLOR_DEPTH_R8G8B8A8       13
#घोषणा WIN_COLOR_DEPTH_B6x2G6x2R6x2A8 14
#घोषणा WIN_COLOR_DEPTH_R6x2G6x2B6x2A8 15
#घोषणा WIN_COLOR_DEPTH_YCbCr422       16
#घोषणा WIN_COLOR_DEPTH_YUV422         17
#घोषणा WIN_COLOR_DEPTH_YCbCr420P      18
#घोषणा WIN_COLOR_DEPTH_YUV420P        19
#घोषणा WIN_COLOR_DEPTH_YCbCr422P      20
#घोषणा WIN_COLOR_DEPTH_YUV422P        21
#घोषणा WIN_COLOR_DEPTH_YCbCr422R      22
#घोषणा WIN_COLOR_DEPTH_YUV422R        23
#घोषणा WIN_COLOR_DEPTH_YCbCr422RA     24
#घोषणा WIN_COLOR_DEPTH_YUV422RA       25
#घोषणा WIN_COLOR_DEPTH_R4G4B4A4       27
#घोषणा WIN_COLOR_DEPTH_R5G5B5A        28
#घोषणा WIN_COLOR_DEPTH_AR5G5B5        29
#घोषणा WIN_COLOR_DEPTH_B5G5R5X1       30
#घोषणा WIN_COLOR_DEPTH_X1B5G5R5       31
#घोषणा WIN_COLOR_DEPTH_R5G5B5X1       32
#घोषणा WIN_COLOR_DEPTH_X1R5G5B5       33
#घोषणा WIN_COLOR_DEPTH_R5G6B5         34
#घोषणा WIN_COLOR_DEPTH_A8R8G8B8       35
#घोषणा WIN_COLOR_DEPTH_A8B8G8R8       36
#घोषणा WIN_COLOR_DEPTH_B8G8R8X8       37
#घोषणा WIN_COLOR_DEPTH_R8G8B8X8       38
#घोषणा WIN_COLOR_DEPTH_X8B8G8R8       65
#घोषणा WIN_COLOR_DEPTH_X8R8G8B8       66

#घोषणा DC_WIN_POSITION				0x704
#घोषणा H_POSITION(x) (((x) & 0x1fff) <<  0) /* XXX 0x7fff on Tegra186 */
#घोषणा V_POSITION(x) (((x) & 0x1fff) << 16) /* XXX 0x7fff on Tegra186 */

#घोषणा DC_WIN_SIZE				0x705
#घोषणा H_SIZE(x) (((x) & 0x1fff) <<  0) /* XXX 0x7fff on Tegra186 */
#घोषणा V_SIZE(x) (((x) & 0x1fff) << 16) /* XXX 0x7fff on Tegra186 */

#घोषणा DC_WIN_PRESCALED_SIZE			0x706
#घोषणा H_PRESCALED_SIZE(x) (((x) & 0x7fff) <<  0)
#घोषणा V_PRESCALED_SIZE(x) (((x) & 0x1fff) << 16) /* XXX 0x7fff on Tegra186 */

#घोषणा DC_WIN_H_INITIAL_DDA			0x707
#घोषणा DC_WIN_V_INITIAL_DDA			0x708
#घोषणा DC_WIN_DDA_INC				0x709
#घोषणा H_DDA_INC(x) (((x) & 0xffff) <<  0)
#घोषणा V_DDA_INC(x) (((x) & 0xffff) << 16)

#घोषणा DC_WIN_LINE_STRIDE			0x70a
#घोषणा DC_WIN_BUF_STRIDE			0x70b
#घोषणा DC_WIN_UV_BUF_STRIDE			0x70c
#घोषणा DC_WIN_BUFFER_ADDR_MODE			0x70d
#घोषणा DC_WIN_BUFFER_ADDR_MODE_LINEAR		(0 <<  0)
#घोषणा DC_WIN_BUFFER_ADDR_MODE_TILE		(1 <<  0)
#घोषणा DC_WIN_BUFFER_ADDR_MODE_LINEAR_UV	(0 << 16)
#घोषणा DC_WIN_BUFFER_ADDR_MODE_TILE_UV		(1 << 16)

#घोषणा DC_WIN_DV_CONTROL			0x70e

#घोषणा DC_WIN_BLEND_NOKEY			0x70f
#घोषणा  BLEND_WEIGHT1(x) (((x) & 0xff) << 16)
#घोषणा  BLEND_WEIGHT0(x) (((x) & 0xff) <<  8)

#घोषणा DC_WIN_BLEND_1WIN			0x710
#घोषणा  BLEND_CONTROL_FIX    (0 << 2)
#घोषणा  BLEND_CONTROL_ALPHA  (1 << 2)
#घोषणा  BLEND_COLOR_KEY_NONE (0 << 0)
#घोषणा  BLEND_COLOR_KEY_0    (1 << 0)
#घोषणा  BLEND_COLOR_KEY_1    (2 << 0)
#घोषणा  BLEND_COLOR_KEY_BOTH (3 << 0)

#घोषणा DC_WIN_BLEND_2WIN_X			0x711
#घोषणा  BLEND_CONTROL_DEPENDENT (2 << 2)

#घोषणा DC_WIN_BLEND_2WIN_Y			0x712
#घोषणा DC_WIN_BLEND_3WIN_XY			0x713

#घोषणा DC_WIN_HP_FETCH_CONTROL			0x714

#घोषणा DC_WINBUF_START_ADDR			0x800
#घोषणा DC_WINBUF_START_ADDR_NS			0x801
#घोषणा DC_WINBUF_START_ADDR_U			0x802
#घोषणा DC_WINBUF_START_ADDR_U_NS		0x803
#घोषणा DC_WINBUF_START_ADDR_V			0x804
#घोषणा DC_WINBUF_START_ADDR_V_NS		0x805

#घोषणा DC_WINBUF_ADDR_H_OFFSET			0x806
#घोषणा DC_WINBUF_ADDR_H_OFFSET_NS		0x807
#घोषणा DC_WINBUF_ADDR_V_OFFSET			0x808
#घोषणा DC_WINBUF_ADDR_V_OFFSET_NS		0x809

#घोषणा DC_WINBUF_UFLOW_STATUS			0x80a
#घोषणा DC_WINBUF_SURFACE_KIND			0x80b
#घोषणा DC_WINBUF_SURFACE_KIND_PITCH	(0 << 0)
#घोषणा DC_WINBUF_SURFACE_KIND_TILED	(1 << 0)
#घोषणा DC_WINBUF_SURFACE_KIND_BLOCK	(2 << 0)
#घोषणा DC_WINBUF_SURFACE_KIND_BLOCK_HEIGHT(x) (((x) & 0x7) << 4)

#घोषणा DC_WINBUF_START_ADDR_HI			0x80d

#घोषणा DC_WINBUF_CDE_CONTROL			0x82f
#घोषणा  ENABLE_SURFACE (1 << 0)

#घोषणा DC_WINBUF_AD_UFLOW_STATUS		0xbca
#घोषणा DC_WINBUF_BD_UFLOW_STATUS		0xdca
#घोषणा DC_WINBUF_CD_UFLOW_STATUS		0xfca

/* Tegra186 and later */
#घोषणा DC_DISP_CORE_SOR_SET_CONTROL(x)		(0x403 + (x))
#घोषणा PROTOCOL_MASK (0xf << 8)
#घोषणा PROTOCOL_SINGLE_TMDS_A (0x1 << 8)

#घोषणा DC_DISP_PCALC_HEAD_SET_CROPPED_POINT_IN_CURSOR	0x442
#घोषणा DC_DISP_PCALC_HEAD_SET_CROPPED_SIZE_IN_CURSOR	0x446

#घोषणा DC_WIN_CORE_WINDOWGROUP_SET_CONTROL	0x702
#घोषणा OWNER_MASK (0xf << 0)
#घोषणा OWNER(x) (((x) & 0xf) << 0)

#घोषणा DC_WIN_CROPPED_SIZE			0x706

#घोषणा DC_WIN_PLANAR_STORAGE			0x709
#घोषणा PITCH(x) (((x) >> 6) & 0x1fff)

#घोषणा DC_WIN_SET_PARAMS			0x70d
#घोषणा  CLAMP_BEFORE_BLEND (1 << 15)
#घोषणा  DEGAMMA_NONE (0 << 13)
#घोषणा  DEGAMMA_SRGB (1 << 13)
#घोषणा  DEGAMMA_YUV8_10 (2 << 13)
#घोषणा  DEGAMMA_YUV12 (3 << 13)
#घोषणा  INPUT_RANGE_BYPASS (0 << 10)
#घोषणा  INPUT_RANGE_LIMITED (1 << 10)
#घोषणा  INPUT_RANGE_FULL (2 << 10)
#घोषणा  COLOR_SPACE_RGB (0 << 8)
#घोषणा  COLOR_SPACE_YUV_601 (1 << 8)
#घोषणा  COLOR_SPACE_YUV_709 (2 << 8)
#घोषणा  COLOR_SPACE_YUV_2020 (3 << 8)

#घोषणा DC_WIN_WINDOWGROUP_SET_CONTROL_INPUT_SCALER	0x70e
#घोषणा  HORIZONTAL_TAPS_2 (1 << 3)
#घोषणा  HORIZONTAL_TAPS_5 (4 << 3)
#घोषणा  VERTICAL_TAPS_2 (1 << 0)
#घोषणा  VERTICAL_TAPS_5 (4 << 0)

#घोषणा DC_WIN_WINDOWGROUP_SET_INPUT_SCALER_USAGE	0x711
#घोषणा  INPUT_SCALER_USE422  (1 << 2)
#घोषणा  INPUT_SCALER_VBYPASS (1 << 1)
#घोषणा  INPUT_SCALER_HBYPASS (1 << 0)

#घोषणा DC_WIN_BLEND_LAYER_CONTROL		0x716
#घोषणा  COLOR_KEY_NONE (0 << 25)
#घोषणा  COLOR_KEY_SRC (1 << 25)
#घोषणा  COLOR_KEY_DST (2 << 25)
#घोषणा  BLEND_BYPASS (1 << 24)
#घोषणा  K2(x) (((x) & 0xff) << 16)
#घोषणा  K1(x) (((x) & 0xff) << 8)
#घोषणा  WINDOW_LAYER_DEPTH(x) (((x) & 0xff) << 0)

#घोषणा DC_WIN_BLEND_MATCH_SELECT		0x717
#घोषणा  BLEND_FACTOR_DST_ALPHA_ZERO			(0 << 12)
#घोषणा  BLEND_FACTOR_DST_ALPHA_ONE			(1 << 12)
#घोषणा  BLEND_FACTOR_DST_ALPHA_NEG_K1_TIMES_SRC	(2 << 12)
#घोषणा  BLEND_FACTOR_DST_ALPHA_K2			(3 << 12)
#घोषणा  BLEND_FACTOR_SRC_ALPHA_ZERO			(0 << 8)
#घोषणा  BLEND_FACTOR_SRC_ALPHA_K1			(1 << 8)
#घोषणा  BLEND_FACTOR_SRC_ALPHA_K2			(2 << 8)
#घोषणा  BLEND_FACTOR_SRC_ALPHA_NEG_K1_TIMES_DST	(3 << 8)
#घोषणा  BLEND_FACTOR_DST_COLOR_ZERO			(0 << 4)
#घोषणा  BLEND_FACTOR_DST_COLOR_ONE			(1 << 4)
#घोषणा  BLEND_FACTOR_DST_COLOR_K1			(2 << 4)
#घोषणा  BLEND_FACTOR_DST_COLOR_K2			(3 << 4)
#घोषणा  BLEND_FACTOR_DST_COLOR_K1_TIMES_DST		(4 << 4)
#घोषणा  BLEND_FACTOR_DST_COLOR_NEG_K1_TIMES_DST	(5 << 4)
#घोषणा  BLEND_FACTOR_DST_COLOR_NEG_K1_TIMES_SRC	(6 << 4)
#घोषणा  BLEND_FACTOR_DST_COLOR_NEG_K1			(7 << 4)
#घोषणा  BLEND_FACTOR_SRC_COLOR_ZERO			(0 << 0)
#घोषणा  BLEND_FACTOR_SRC_COLOR_ONE			(1 << 0)
#घोषणा  BLEND_FACTOR_SRC_COLOR_K1			(2 << 0)
#घोषणा  BLEND_FACTOR_SRC_COLOR_K1_TIMES_DST		(3 << 0)
#घोषणा  BLEND_FACTOR_SRC_COLOR_NEG_K1_TIMES_DST	(4 << 0)
#घोषणा  BLEND_FACTOR_SRC_COLOR_K1_TIMES_SRC		(5 << 0)

#घोषणा DC_WIN_BLEND_NOMATCH_SELECT		0x718

#घोषणा DC_WIN_PRECOMP_WGRP_PARAMS		0x724
#घोषणा  SWAP_UV (1 << 0)

#घोषणा DC_WIN_WINDOW_SET_CONTROL		0x730
#घोषणा  CONTROL_CSC_ENABLE (1 << 5)

#घोषणा DC_WINBUF_CROPPED_POINT			0x806
#घोषणा OFFSET_Y(x) (((x) & 0xffff) << 16)
#घोषणा OFFSET_X(x) (((x) & 0xffff) << 0)

#पूर्ण_अगर /* TEGRA_DC_H */
