<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम panels based on Sitronix ST7703 controller, souch as:
 *
 * - Rocktech jh057n00900 5.5" MIPI-DSI panel
 *
 * Copyright (C) Purism SPC 2019
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/media-bus-क्रमmat.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/display_timing.h>
#समावेश <video/mipi_display.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#घोषणा DRV_NAME "panel-sitronix-st7703"

/* Manufacturer specअगरic Commands send via DSI */
#घोषणा ST7703_CMD_ALL_PIXEL_OFF 0x22
#घोषणा ST7703_CMD_ALL_PIXEL_ON	 0x23
#घोषणा ST7703_CMD_SETDISP	 0xB2
#घोषणा ST7703_CMD_SETRGBIF	 0xB3
#घोषणा ST7703_CMD_SETCYC	 0xB4
#घोषणा ST7703_CMD_SETBGP	 0xB5
#घोषणा ST7703_CMD_SETVCOM	 0xB6
#घोषणा ST7703_CMD_SETOTP	 0xB7
#घोषणा ST7703_CMD_SETPOWER_EXT	 0xB8
#घोषणा ST7703_CMD_SETEXTC	 0xB9
#घोषणा ST7703_CMD_SETMIPI	 0xBA
#घोषणा ST7703_CMD_SETVDC	 0xBC
#घोषणा ST7703_CMD_UNKNOWN_BF	 0xBF
#घोषणा ST7703_CMD_SETSCR	 0xC0
#घोषणा ST7703_CMD_SETPOWER	 0xC1
#घोषणा ST7703_CMD_SETPANEL	 0xCC
#घोषणा ST7703_CMD_UNKNOWN_C6	 0xC6
#घोषणा ST7703_CMD_SETGAMMA	 0xE0
#घोषणा ST7703_CMD_SETEQ	 0xE3
#घोषणा ST7703_CMD_SETGIP1	 0xE9
#घोषणा ST7703_CMD_SETGIP2	 0xEA

काष्ठा st7703 अणु
	काष्ठा device *dev;
	काष्ठा drm_panel panel;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा regulator *vcc;
	काष्ठा regulator *iovcc;
	bool prepared;

	काष्ठा dentry *debugfs;
	स्थिर काष्ठा st7703_panel_desc *desc;
पूर्ण;

काष्ठा st7703_panel_desc अणु
	स्थिर काष्ठा drm_display_mode *mode;
	अचिन्हित पूर्णांक lanes;
	अचिन्हित दीर्घ mode_flags;
	क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat;
	पूर्णांक (*init_sequence)(काष्ठा st7703 *ctx);
पूर्ण;

अटल अंतरभूत काष्ठा st7703 *panel_to_st7703(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा st7703, panel);
पूर्ण

#घोषणा dsi_generic_ग_लिखो_seq(dsi, seq...) करो अणु				\
		अटल स्थिर u8 d[] = अणु seq पूर्ण;				\
		पूर्णांक ret;						\
		ret = mipi_dsi_generic_ग_लिखो(dsi, d, ARRAY_SIZE(d));	\
		अगर (ret < 0)						\
			वापस ret;					\
	पूर्ण जबतक (0)

अटल पूर्णांक jh057n_init_sequence(काष्ठा st7703 *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	/*
	 * Init sequence was supplied by the panel venकरोr. Most of the commands
	 * resemble the ST7703 but the number of parameters often करोn't match
	 * so it's likely a clone.
	 */
	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_SETEXTC,
			      0xF1, 0x12, 0x83);
	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_SETRGBIF,
			      0x10, 0x10, 0x05, 0x05, 0x03, 0xFF, 0x00, 0x00,
			      0x00, 0x00);
	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_SETSCR,
			      0x73, 0x73, 0x50, 0x50, 0x00, 0x00, 0x08, 0x70,
			      0x00);
	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_SETVDC, 0x4E);
	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_SETPANEL, 0x0B);
	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_SETCYC, 0x80);
	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_SETDISP, 0xF0, 0x12, 0x30);
	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_SETEQ,
			      0x07, 0x07, 0x0B, 0x0B, 0x03, 0x0B, 0x00, 0x00,
			      0x00, 0x00, 0xFF, 0x00, 0xC0, 0x10);
	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_SETBGP, 0x08, 0x08);
	msleep(20);

	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_SETVCOM, 0x3F, 0x3F);
	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_UNKNOWN_BF, 0x02, 0x11, 0x00);
	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_SETGIP1,
			      0x82, 0x10, 0x06, 0x05, 0x9E, 0x0A, 0xA5, 0x12,
			      0x31, 0x23, 0x37, 0x83, 0x04, 0xBC, 0x27, 0x38,
			      0x0C, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0C, 0x00,
			      0x03, 0x00, 0x00, 0x00, 0x75, 0x75, 0x31, 0x88,
			      0x88, 0x88, 0x88, 0x88, 0x88, 0x13, 0x88, 0x64,
			      0x64, 0x20, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
			      0x02, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_SETGIP2,
			      0x02, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			      0x00, 0x00, 0x00, 0x00, 0x02, 0x46, 0x02, 0x88,
			      0x88, 0x88, 0x88, 0x88, 0x88, 0x64, 0x88, 0x13,
			      0x57, 0x13, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
			      0x75, 0x88, 0x23, 0x14, 0x00, 0x00, 0x02, 0x00,
			      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0A,
			      0xA5, 0x00, 0x00, 0x00, 0x00);
	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_SETGAMMA,
			      0x00, 0x09, 0x0E, 0x29, 0x2D, 0x3C, 0x41, 0x37,
			      0x07, 0x0B, 0x0D, 0x10, 0x11, 0x0F, 0x10, 0x11,
			      0x18, 0x00, 0x09, 0x0E, 0x29, 0x2D, 0x3C, 0x41,
			      0x37, 0x07, 0x0B, 0x0D, 0x10, 0x11, 0x0F, 0x10,
			      0x11, 0x18);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode jh057n00900_mode = अणु
	.hdisplay    = 720,
	.hsync_start = 720 + 90,
	.hsync_end   = 720 + 90 + 20,
	.htotal	     = 720 + 90 + 20 + 20,
	.vdisplay    = 1440,
	.vsync_start = 1440 + 20,
	.vsync_end   = 1440 + 20 + 4,
	.vtotal	     = 1440 + 20 + 4 + 12,
	.घड़ी	     = 75276,
	.flags	     = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	.width_mm    = 65,
	.height_mm   = 130,
पूर्ण;

अटल स्थिर काष्ठा st7703_panel_desc jh057n00900_panel_desc = अणु
	.mode = &jh057n00900_mode,
	.lanes = 4,
	.mode_flags = MIPI_DSI_MODE_VIDEO |
		MIPI_DSI_MODE_VIDEO_BURST | MIPI_DSI_MODE_VIDEO_SYNC_PULSE,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.init_sequence = jh057n_init_sequence,
पूर्ण;

#घोषणा dsi_dcs_ग_लिखो_seq(dsi, cmd, seq...) करो अणु			\
		अटल स्थिर u8 d[] = अणु seq पूर्ण;				\
		पूर्णांक ret;						\
		ret = mipi_dsi_dcs_ग_लिखो(dsi, cmd, d, ARRAY_SIZE(d));	\
		अगर (ret < 0)						\
			वापस ret;					\
	पूर्ण जबतक (0)


अटल पूर्णांक xbd599_init_sequence(काष्ठा st7703 *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	/*
	 * Init sequence was supplied by the panel venकरोr.
	 */

	/* Magic sequence to unlock user commands below. */
	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETEXTC, 0xF1, 0x12, 0x83);

	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETMIPI,
			  0x33, /* VC_मुख्य = 0, Lane_Number = 3 (4 lanes) */
			  0x81, /* DSI_LDO_SEL = 1.7V, RTERM = 90 Ohm */
			  0x05, /* IHSRX = x6 (Low High Speed driving ability) */
			  0xF9, /* TX_CLK_SEL = fDSICLK/16 */
			  0x0E, /* HFP_OSC (min. HFP number in DSI mode) */
			  0x0E, /* HBP_OSC (min. HBP number in DSI mode) */
			  /* The rest is unकरोcumented in ST7703 datasheet */
			  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			  0x44, 0x25, 0x00, 0x91, 0x0a, 0x00, 0x00, 0x02,
			  0x4F, 0x11, 0x00, 0x00, 0x37);

	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETPOWER_EXT,
			  0x25, /* PCCS = 2, ECP_DC_DIV = 1/4 HSYNC */
			  0x22, /* DT = 15ms XDK_ECP = x2 */
			  0x20, /* PFM_DC_DIV = /1 */
			  0x03  /* ECP_SYNC_EN = 1, VGX_SYNC_EN = 1 */);

	/* RGB I/F porch timing */
	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETRGBIF,
			  0x10, /* VBP_RGB_GEN */
			  0x10, /* VFP_RGB_GEN */
			  0x05, /* DE_BP_RGB_GEN */
			  0x05, /* DE_FP_RGB_GEN */
			  /* The rest is unकरोcumented in ST7703 datasheet */
			  0x03, 0xFF,
			  0x00, 0x00,
			  0x00, 0x00);

	/* Source driving settings. */
	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETSCR,
			  0x73, /* N_POPON */
			  0x73, /* N_NOPON */
			  0x50, /* I_POPON */
			  0x50, /* I_NOPON */
			  0x00, /* SCR[31,24] */
			  0xC0, /* SCR[23,16] */
			  0x08, /* SCR[15,8] */
			  0x70, /* SCR[7,0] */
			  0x00  /* Unकरोcumented */);

	/* NVDDD_SEL = -1.8V, VDDD_SEL = out of range (possibly 1.9V?) */
	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETVDC, 0x4E);

	/*
	 * SS_PANEL = 1 (reverse scan), GS_PANEL = 0 (normal scan)
	 * REV_PANEL = 1 (normally black panel), BGR_PANEL = 1 (BGR)
	 */
	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETPANEL, 0x0B);

	/* Zig-Zag Type C column inversion. */
	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETCYC, 0x80);

	/* Set display resolution. */
	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETDISP,
			  0xF0, /* NL = 240 */
			  0x12, /* RES_V_LSB = 0, BLK_CON = VSSD,
				 * RESO_SEL = 720RGB
				 */
			  0xF0  /* WHITE_GND_EN = 1 (GND),
				 * WHITE_FRAME_SEL = 7 frames,
				 * ISC = 0 frames
				 */);

	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETEQ,
			  0x00, /* PNOEQ */
			  0x00, /* NNOEQ */
			  0x0B, /* PEQGND */
			  0x0B, /* NEQGND */
			  0x10, /* PEQVCI */
			  0x10, /* NEQVCI */
			  0x00, /* PEQVCI1 */
			  0x00, /* NEQVCI1 */
			  0x00, /* reserved */
			  0x00, /* reserved */
			  0xFF, /* reserved */
			  0x00, /* reserved */
			  0xC0, /* ESD_DET_DATA_WHITE = 1, ESD_WHITE_EN = 1 */
			  0x10  /* SLPIN_OPTION = 1 (no need vsync after sleep-in)
				 * VEDIO_NO_CHECK_EN = 0
				 * ESD_WHITE_GND_EN = 0
				 * ESD_DET_TIME_SEL = 0 frames
				 */);

	/* Unकरोcumented command. */
	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_UNKNOWN_C6, 0x01, 0x00, 0xFF, 0xFF, 0x00);

	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETPOWER,
			  0x74, /* VBTHS, VBTLS: VGH = 17V, VBL = -11V */
			  0x00, /* FBOFF_VGH = 0, FBOFF_VGL = 0 */
			  0x32, /* VRP  */
			  0x32, /* VRN */
			  0x77, /* reserved */
			  0xF1, /* APS = 1 (small),
				 * VGL_DET_EN = 1, VGH_DET_EN = 1,
				 * VGL_TURBO = 1, VGH_TURBO = 1
				 */
			  0xFF, /* VGH1_L_DIV, VGL1_L_DIV (1.5MHz) */
			  0xFF, /* VGH1_R_DIV, VGL1_R_DIV (1.5MHz) */
			  0xCC, /* VGH2_L_DIV, VGL2_L_DIV (2.6MHz) */
			  0xCC, /* VGH2_R_DIV, VGL2_R_DIV (2.6MHz) */
			  0x77, /* VGH3_L_DIV, VGL3_L_DIV (4.5MHz) */
			  0x77  /* VGH3_R_DIV, VGL3_R_DIV (4.5MHz) */);

	/* Reference voltage. */
	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETBGP,
			  0x07, /* VREF_SEL = 4.2V */
			  0x07  /* NVREF_SEL = 4.2V */);
	msleep(20);

	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETVCOM,
			  0x2C, /* VCOMDC_F = -0.67V */
			  0x2C  /* VCOMDC_B = -0.67V */);

	/* Unकरोcumented command. */
	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_UNKNOWN_BF, 0x02, 0x11, 0x00);

	/* This command is to set क्रमward GIP timing. */
	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETGIP1,
			  0x82, 0x10, 0x06, 0x05, 0xA2, 0x0A, 0xA5, 0x12,
			  0x31, 0x23, 0x37, 0x83, 0x04, 0xBC, 0x27, 0x38,
			  0x0C, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0C, 0x00,
			  0x03, 0x00, 0x00, 0x00, 0x75, 0x75, 0x31, 0x88,
			  0x88, 0x88, 0x88, 0x88, 0x88, 0x13, 0x88, 0x64,
			  0x64, 0x20, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
			  0x02, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

	/* This command is to set backward GIP timing. */
	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETGIP2,
			  0x02, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			  0x00, 0x00, 0x00, 0x00, 0x02, 0x46, 0x02, 0x88,
			  0x88, 0x88, 0x88, 0x88, 0x88, 0x64, 0x88, 0x13,
			  0x57, 0x13, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
			  0x75, 0x88, 0x23, 0x14, 0x00, 0x00, 0x02, 0x00,
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0A,
			  0xA5, 0x00, 0x00, 0x00, 0x00);

	/* Adjust the gamma अक्षरacteristics of the panel. */
	dsi_dcs_ग_लिखो_seq(dsi, ST7703_CMD_SETGAMMA,
			  0x00, 0x09, 0x0D, 0x23, 0x27, 0x3C, 0x41, 0x35,
			  0x07, 0x0D, 0x0E, 0x12, 0x13, 0x10, 0x12, 0x12,
			  0x18, 0x00, 0x09, 0x0D, 0x23, 0x27, 0x3C, 0x41,
			  0x35, 0x07, 0x0D, 0x0E, 0x12, 0x13, 0x10, 0x12,
			  0x12, 0x18);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode xbd599_mode = अणु
	.hdisplay    = 720,
	.hsync_start = 720 + 40,
	.hsync_end   = 720 + 40 + 40,
	.htotal	     = 720 + 40 + 40 + 40,
	.vdisplay    = 1440,
	.vsync_start = 1440 + 18,
	.vsync_end   = 1440 + 18 + 10,
	.vtotal	     = 1440 + 18 + 10 + 17,
	.घड़ी	     = 69000,
	.flags	     = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	.width_mm    = 68,
	.height_mm   = 136,
पूर्ण;

अटल स्थिर काष्ठा st7703_panel_desc xbd599_desc = अणु
	.mode = &xbd599_mode,
	.lanes = 4,
	.mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.init_sequence = xbd599_init_sequence,
पूर्ण;

अटल पूर्णांक st7703_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा st7703 *ctx = panel_to_st7703(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	ret = ctx->desc->init_sequence(ctx);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Panel init sequence failed: %d\n", ret);
		वापस ret;
	पूर्ण

	msleep(20);

	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to exit sleep mode: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Panel is operational 120 msec after reset */
	msleep(60);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret)
		वापस ret;

	dev_dbg(ctx->dev, "Panel init sequence done\n");

	वापस 0;
पूर्ण

अटल पूर्णांक st7703_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा st7703 *ctx = panel_to_st7703(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret < 0)
		dev_err(ctx->dev, "Failed to turn off the display: %d\n", ret);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret < 0)
		dev_err(ctx->dev, "Failed to enter sleep mode: %d\n", ret);

	वापस 0;
पूर्ण

अटल पूर्णांक st7703_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा st7703 *ctx = panel_to_st7703(panel);

	अगर (!ctx->prepared)
		वापस 0;

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	regulator_disable(ctx->iovcc);
	regulator_disable(ctx->vcc);
	ctx->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक st7703_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा st7703 *ctx = panel_to_st7703(panel);
	पूर्णांक ret;

	अगर (ctx->prepared)
		वापस 0;

	dev_dbg(ctx->dev, "Resetting the panel\n");
	ret = regulator_enable(ctx->vcc);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to enable vcc supply: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = regulator_enable(ctx->iovcc);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to enable iovcc supply: %d\n", ret);
		जाओ disable_vcc;
	पूर्ण

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(20, 40);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);

	ctx->prepared = true;

	वापस 0;

disable_vcc:
	regulator_disable(ctx->vcc);
	वापस ret;
पूर्ण

अटल पूर्णांक st7703_get_modes(काष्ठा drm_panel *panel,
			    काष्ठा drm_connector *connector)
अणु
	काष्ठा st7703 *ctx = panel_to_st7703(panel);
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, ctx->desc->mode);
	अगर (!mode) अणु
		dev_err(ctx->dev, "Failed to add mode %ux%u@%u\n",
			ctx->desc->mode->hdisplay, ctx->desc->mode->vdisplay,
			drm_mode_vrefresh(ctx->desc->mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs st7703_drm_funcs = अणु
	.disable   = st7703_disable,
	.unprepare = st7703_unprepare,
	.prepare   = st7703_prepare,
	.enable	   = st7703_enable,
	.get_modes = st7703_get_modes,
पूर्ण;

अटल पूर्णांक allpixelson_set(व्योम *data, u64 val)
अणु
	काष्ठा st7703 *ctx = data;
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	dev_dbg(ctx->dev, "Setting all pixels on\n");
	dsi_generic_ग_लिखो_seq(dsi, ST7703_CMD_ALL_PIXEL_ON);
	msleep(val * 1000);
	/* Reset the panel to get video back */
	drm_panel_disable(&ctx->panel);
	drm_panel_unprepare(&ctx->panel);
	drm_panel_prepare(&ctx->panel);
	drm_panel_enable(&ctx->panel);

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(allpixelson_fops, शून्य,
			allpixelson_set, "%llu\n");

अटल व्योम st7703_debugfs_init(काष्ठा st7703 *ctx)
अणु
	ctx->debugfs = debugfs_create_dir(DRV_NAME, शून्य);

	debugfs_create_file("allpixelson", 0600, ctx->debugfs, ctx,
			    &allpixelson_fops);
पूर्ण

अटल व्योम st7703_debugfs_हटाओ(काष्ठा st7703 *ctx)
अणु
	debugfs_हटाओ_recursive(ctx->debugfs);
	ctx->debugfs = शून्य;
पूर्ण

अटल पूर्णांक st7703_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा st7703 *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->reset_gpio))
		वापस dev_err_probe(dev, PTR_ERR(ctx->reset_gpio), "Failed to get reset gpio\n");

	mipi_dsi_set_drvdata(dsi, ctx);

	ctx->dev = dev;
	ctx->desc = of_device_get_match_data(dev);

	dsi->mode_flags = ctx->desc->mode_flags;
	dsi->क्रमmat = ctx->desc->क्रमmat;
	dsi->lanes = ctx->desc->lanes;

	ctx->vcc = devm_regulator_get(dev, "vcc");
	अगर (IS_ERR(ctx->vcc))
		वापस dev_err_probe(dev, PTR_ERR(ctx->vcc), "Failed to request vcc regulator\n");

	ctx->iovcc = devm_regulator_get(dev, "iovcc");
	अगर (IS_ERR(ctx->iovcc))
		वापस dev_err_probe(dev, PTR_ERR(ctx->iovcc),
				     "Failed to request iovcc regulator\n");

	drm_panel_init(&ctx->panel, dev, &st7703_drm_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&ctx->panel);
	अगर (ret)
		वापस ret;

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "mipi_dsi_attach failed (%d). Is host ready?\n", ret);
		drm_panel_हटाओ(&ctx->panel);
		वापस ret;
	पूर्ण

	dev_info(dev, "%ux%u@%u %ubpp dsi %udl - ready\n",
		 ctx->desc->mode->hdisplay, ctx->desc->mode->vdisplay,
		 drm_mode_vrefresh(ctx->desc->mode),
		 mipi_dsi_pixel_क्रमmat_to_bpp(dsi->क्रमmat), dsi->lanes);

	st7703_debugfs_init(ctx);
	वापस 0;
पूर्ण

अटल व्योम st7703_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा st7703 *ctx = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	ret = drm_panel_unprepare(&ctx->panel);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to unprepare panel: %d\n", ret);

	ret = drm_panel_disable(&ctx->panel);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to disable panel: %d\n", ret);
पूर्ण

अटल पूर्णांक st7703_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा st7703 *ctx = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	st7703_shutकरोwn(dsi);

	ret = mipi_dsi_detach(dsi);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_हटाओ(&ctx->panel);

	st7703_debugfs_हटाओ(ctx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id st7703_of_match[] = अणु
	अणु .compatible = "rocktech,jh057n00900", .data = &jh057n00900_panel_desc पूर्ण,
	अणु .compatible = "xingbangda,xbd599", .data = &xbd599_desc पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, st7703_of_match);

अटल काष्ठा mipi_dsi_driver st7703_driver = अणु
	.probe	= st7703_probe,
	.हटाओ = st7703_हटाओ,
	.shutकरोwn = st7703_shutकरोwn,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = st7703_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(st7703_driver);

MODULE_AUTHOR("Guido Gथञnther <agx@sigxcpu.org>");
MODULE_DESCRIPTION("DRM driver for Sitronix ST7703 based MIPI DSI panels");
MODULE_LICENSE("GPL v2");
