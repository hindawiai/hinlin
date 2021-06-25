<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Novatek NT35510 panel driver
 * Copyright (C) 2020 Linus Walleij <linus.walleij@linaro.org>
 * Based on code by Robert Teather (C) 2012 Samsung
 *
 * This display driver (and I refer to the physical component NT35510,
 * not this Linux kernel software driver) can handle:
 * 480x864, 480x854, 480x800, 480x720 and 480x640 pixel displays.
 * It has 480x840x24bit SRAM embedded क्रम storing a frame.
 * When घातered on the display is by शेष in 480x800 mode.
 *
 * The actual panels using this component have dअगरferent names, but
 * the code needed to set up and configure the panel will be similar,
 * so they should all use the NT35510 driver with appropriate configuration
 * per-panel, e.g. क्रम physical size.
 *
 * This driver is क्रम the DSI पूर्णांकerface to panels using the NT35510.
 *
 * The NT35510 can also use an RGB (DPI) पूर्णांकerface combined with an
 * I2C or SPI पूर्णांकerface क्रम setting up the NT35510. If this is needed
 * this panel driver should be refactored to also support that use
 * हाल.
 */
#समावेश <linux/backlight.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#घोषणा MCS_CMD_MAUCCTR		0xF0 /* Manufacturer command enable */
#घोषणा MCS_CMD_READ_ID1	0xDA
#घोषणा MCS_CMD_READ_ID2	0xDB
#घोषणा MCS_CMD_READ_ID3	0xDC
#घोषणा MCS_CMD_MTP_READ_SETTING 0xF8 /* Uncertain about name */
#घोषणा MCS_CMD_MTP_READ_PARAM 0xFF /* Uncertain about name */

/*
 * These manufacturer commands are available after we enable manufacturer
 * command set (MCS) क्रम page 0.
 */
#घोषणा NT35510_P0_DOPCTR 0xB1
#घोषणा NT35510_P0_SDHDTCTR 0xB6
#घोषणा NT35510_P0_GSEQCTR 0xB7
#घोषणा NT35510_P0_SDEQCTR 0xB8
#घोषणा NT35510_P0_SDVPCTR 0xBA
#घोषणा NT35510_P0_DPFRCTR1 0xBD
#घोषणा NT35510_P0_DPFRCTR2 0xBE
#घोषणा NT35510_P0_DPFRCTR3 0xBF
#घोषणा NT35510_P0_DPMCTR12 0xCC

#घोषणा NT35510_P0_DOPCTR_LEN 2
#घोषणा NT35510_P0_GSEQCTR_LEN 2
#घोषणा NT35510_P0_SDEQCTR_LEN 4
#घोषणा NT35510_P0_SDVPCTR_LEN 1
#घोषणा NT35510_P0_DPFRCTR1_LEN 5
#घोषणा NT35510_P0_DPFRCTR2_LEN 5
#घोषणा NT35510_P0_DPFRCTR3_LEN 5
#घोषणा NT35510_P0_DPMCTR12_LEN 3

#घोषणा NT35510_DOPCTR_0_RAMKP BIT(7) /* Contents kept in sleep */
#घोषणा NT35510_DOPCTR_0_DSITE BIT(6) /* Enable TE संकेत */
#घोषणा NT35510_DOPCTR_0_DSIG BIT(5) /* Enable generic पढ़ो/ग_लिखो */
#घोषणा NT35510_DOPCTR_0_DSIM BIT(4) /* Enable video mode on DSI */
#घोषणा NT35510_DOPCTR_0_EOTP BIT(3) /* Support EoTP */
#घोषणा NT35510_DOPCTR_0_N565 BIT(2) /* RGB or BGR pixel क्रमmat */
#घोषणा NT35510_DOPCTR_1_TW_PWR_SEL BIT(4) /* TE घातer selector */
#घोषणा NT35510_DOPCTR_1_CRGB BIT(3) /* RGB or BGR byte order */
#घोषणा NT35510_DOPCTR_1_CTB BIT(2) /* Vertical scanning direction */
#घोषणा NT35510_DOPCTR_1_CRL BIT(1) /* Source driver data shअगरt */
#घोषणा NT35510_P0_SDVPCTR_PRG BIT(2) /* 0 = normal operation, 1 = VGLO */
#घोषणा NT35510_P0_SDVPCTR_AVDD 0 /* source driver output = AVDD */
#घोषणा NT35510_P0_SDVPCTR_OFFCOL 1 /* source driver output = off color */
#घोषणा NT35510_P0_SDVPCTR_AVSS 2 /* source driver output = AVSS */
#घोषणा NT35510_P0_SDVPCTR_HI_Z 3 /* source driver output = High impedance */

/*
 * These manufacturer commands are available after we enable manufacturer
 * command set (MCS) क्रम page 1.
 */
#घोषणा NT35510_P1_SETAVDD 0xB0
#घोषणा NT35510_P1_SETAVEE 0xB1
#घोषणा NT35510_P1_SETVCL 0xB2
#घोषणा NT35510_P1_SETVGH 0xB3
#घोषणा NT35510_P1_SETVRGH 0xB4
#घोषणा NT35510_P1_SETVGL 0xB5
#घोषणा NT35510_P1_BT1CTR 0xB6
#घोषणा NT35510_P1_BT2CTR 0xB7
#घोषणा NT35510_P1_BT3CTR 0xB8
#घोषणा NT35510_P1_BT4CTR 0xB9 /* VGH boosting बार/freq */
#घोषणा NT35510_P1_BT5CTR 0xBA
#घोषणा NT35510_P1_PFMCTR 0xBB
#घोषणा NT35510_P1_SETVGP 0xBC
#घोषणा NT35510_P1_SETVGN 0xBD
#घोषणा NT35510_P1_SETVCMOFF 0xBE
#घोषणा NT35510_P1_VGHCTR 0xBF /* VGH output ctrl */
#घोषणा NT35510_P1_SET_GAMMA_RED_POS 0xD1
#घोषणा NT35510_P1_SET_GAMMA_GREEN_POS 0xD2
#घोषणा NT35510_P1_SET_GAMMA_BLUE_POS 0xD3
#घोषणा NT35510_P1_SET_GAMMA_RED_NEG 0xD4
#घोषणा NT35510_P1_SET_GAMMA_GREEN_NEG 0xD5
#घोषणा NT35510_P1_SET_GAMMA_BLUE_NEG 0xD6

/* AVDD and AVEE setting 3 bytes */
#घोषणा NT35510_P1_AVDD_LEN 3
#घोषणा NT35510_P1_AVEE_LEN 3
#घोषणा NT35510_P1_VGH_LEN 3
#घोषणा NT35510_P1_VGL_LEN 3
#घोषणा NT35510_P1_VGP_LEN 3
#घोषणा NT35510_P1_VGN_LEN 3
/* BT1CTR thru BT5CTR setting 3 bytes */
#घोषणा NT35510_P1_BT1CTR_LEN 3
#घोषणा NT35510_P1_BT2CTR_LEN 3
#घोषणा NT35510_P1_BT4CTR_LEN 3
#घोषणा NT35510_P1_BT5CTR_LEN 3
/* 52 gamma parameters बार two per color: positive and negative */
#घोषणा NT35510_P1_GAMMA_LEN 52

/**
 * काष्ठा nt35510_config - the display-specअगरic NT35510 configuration
 *
 * Some of the settings provide an array of bytes, A, B C which mean:
 * A = normal / idle off mode
 * B = idle on mode
 * C = partial / idle off mode
 *
 * Gamma correction arrays are 10bit numbers, two consecutive bytes
 * makes out one poपूर्णांक on the gamma correction curve. The poपूर्णांकs are
 * not linearly placed aदीर्घ the X axis, we get poपूर्णांकs 0, 1, 3, 5
 * 7, 11, 15, 23, 31, 47, 63, 95, 127, 128, 160, 192, 208, 224, 232,
 * 240, 244, 248, 250, 252, 254, 255. The voltages tuples क्रमm
 * V0, V1, V3 ... V255, with 0x0000 being the lowest voltage and
 * 0x03FF being the highest voltage.
 *
 * Each value must be strictly higher than the previous value क्रमming
 * a rising curve like this:
 *
 * ^
 * |                                        V255
 * |                                 V254
 * |                         ....
 * |                    V5
 * |           V3
 * |     V1
 * | V0
 * +------------------------------------------->
 *
 * The details about all settings can be found in the NT35510 Application
 * Note.
 */
काष्ठा nt35510_config अणु
	/**
	 * @width_mm: physical panel width [mm]
	 */
	u32 width_mm;
	/**
	 * @height_mm: physical panel height [mm]
	 */
	u32 height_mm;
	/**
	 * @mode: the display mode. This is only relevant outside the panel
	 * in video mode: in command mode this is configuring the पूर्णांकernal
	 * timing in the display controller.
	 */
	स्थिर काष्ठा drm_display_mode mode;
	/**
	 * @avdd: setting क्रम AVDD ranging from 0x00 = 6.5V to 0x14 = 4.5V
	 * in 0.1V steps the शेष is 0x05 which means 6.0V
	 */
	u8 avdd[NT35510_P1_AVDD_LEN];
	/**
	 * @bt1ctr: setting क्रम boost घातer control क्रम the AVDD step-up
	 * circuit (1)
	 * bits 0..2 in the lower nibble controls PCK, the booster घड़ी
	 * frequency क्रम the step-up circuit:
	 * 0 = Hsync/32
	 * 1 = Hsync/16
	 * 2 = Hsync/8
	 * 3 = Hsync/4
	 * 4 = Hsync/2
	 * 5 = Hsync
	 * 6 = Hsync x 2
	 * 7 = Hsync x 4
	 * bits 4..6 in the upper nibble controls BTP, the boosting
	 * amplअगरication क्रम the the step-up circuit:
	 * 0 = Disable
	 * 1 = 1.5 x VDDB
	 * 2 = 1.66 x VDDB
	 * 3 = 2 x VDDB
	 * 4 = 2.5 x VDDB
	 * 5 = 3 x VDDB
	 * The शेषs are 4 and 4 yielding 0x44
	 */
	u8 bt1ctr[NT35510_P1_BT1CTR_LEN];
	/**
	 * @avee: setting क्रम AVEE ranging from 0x00 = -6.5V to 0x14 = -4.5V
	 * in 0.1V steps the शेष is 0x05 which means -6.0V
	 */
	u8 avee[NT35510_P1_AVEE_LEN];
	/**
	 * @bt2ctr: setting क्रम boost घातer control क्रम the AVEE step-up
	 * circuit (2)
	 * bits 0..2 in the lower nibble controls NCK, the booster घड़ी
	 * frequency, the values are the same as क्रम PCK in @bt1ctr.
	 * bits 4..5 in the upper nibble controls BTN, the boosting
	 * amplअगरication क्रम the the step-up circuit.
	 * 0 = Disable
	 * 1 = -1.5 x VDDB
	 * 2 = -2 x VDDB
	 * 3 = -2.5 x VDDB
	 * 4 = -3 x VDDB
	 * The शेषs are 4 and 3 yielding 0x34
	 */
	u8 bt2ctr[NT35510_P1_BT2CTR_LEN];
	/**
	 * @vgh: setting क्रम VGH ranging from 0x00 = 7.0V to 0x0B = 18.0V
	 * in 1V steps, the शेष is 0x08 which means 15V
	 */
	u8 vgh[NT35510_P1_VGH_LEN];
	/**
	 * @bt4ctr: setting क्रम boost घातer control क्रम the VGH step-up
	 * circuit (4)
	 * bits 0..2 in the lower nibble controls HCK, the booster घड़ी
	 * frequency, the values are the same as क्रम PCK in @bt1ctr.
	 * bits 4..5 in the upper nibble controls BTH, the boosting
	 * amplअगरication क्रम the the step-up circuit.
	 * 0 = AVDD + VDDB
	 * 1 = AVDD - AVEE
	 * 2 = AVDD - AVEE + VDDB
	 * 3 = AVDD x 2 - AVEE
	 * The शेषs are 4 and 3 yielding 0x34
	 */
	u8 bt4ctr[NT35510_P1_BT4CTR_LEN];
	/**
	 * @vgl: setting क्रम VGL ranging from 0x00 = -2V to 0x0f = -15V in
	 * 1V steps, the शेष is 0x08 which means -10V
	 */
	u8 vgl[NT35510_P1_VGL_LEN];
	/**
	 * @bt5ctr: setting क्रम boost घातer control क्रम the VGL step-up
	 * circuit (5)
	 * bits 0..2 in the lower nibble controls LCK, the booster घड़ी
	 * frequency, the values are the same as क्रम PCK in @bt1ctr.
	 * bits 4..5 in the upper nibble controls BTL, the boosting
	 * amplअगरication क्रम the the step-up circuit.
	 * 0 = AVEE + VCL
	 * 1 = AVEE - AVDD
	 * 2 = AVEE + VCL - AVDD
	 * 3 = AVEE x 2 - AVDD
	 * The शेषs are 3 and 2 yielding 0x32
	 */
	u8 bt5ctr[NT35510_P1_BT5CTR_LEN];
	/**
	 * @vgp: setting क्रम VGP, the positive gamma भागider voltages
	 * VGMP the high voltage and VGSP the low voltage.
	 * The first byte contains bit 8 of VGMP and VGSP in bits 4 and 0
	 * The second byte contains bit 0..7 of VGMP
	 * The third byte contains bit 0..7 of VGSP
	 * VGMP 0x00 = 3.0V .. 0x108 = 6.3V in steps of 12.5mV
	 * VGSP 0x00 = 0V .. 0x111 = 3.7V in steps of 12.5mV
	 */
	u8 vgp[NT35510_P1_VGP_LEN];
	/**
	 * @vgn: setting क्रम VGN, the negative gamma भागider voltages,
	 * same layout of bytes as @vgp.
	 */
	u8 vgn[NT35510_P1_VGN_LEN];
	/**
	 * @sdeqctr: Source driver control settings, first byte is
	 * 0 क्रम mode 1 and 1 क्रम mode 2. Mode 1 uses two steps and
	 * mode 2 uses three steps meaning EQS3 is not used in mode
	 * 1. Mode 2 is शेष. The last three parameters are EQS1, EQS2
	 * and EQS3, setting the rise समय क्रम each equalizer step:
	 * 0x00 = 0.0 us to 0x0f = 7.5 us in steps of 0.5us. The शेष
	 * is 0x07 = 3.5 us.
	 */
	u8 sdeqctr[NT35510_P0_SDEQCTR_LEN];
	/**
	 * @sdvpctr: घातer/voltage behaviour during vertical porch समय
	 */
	u8 sdvpctr;
	/**
	 * @t1: the number of pixel घड़ीs on one scanline, range
	 * 0x100 (258 ticks) .. 0x3FF (1024 ticks) so the value + 1
	 * घड़ी ticks.
	 */
	u16 t1;
	/**
	 * @vbp: vertical back porch toward the PANEL note: not toward
	 * the DSI host; these are separate पूर्णांकerfaces, in from DSI host
	 * and out to the panel.
	 */
	u8 vbp;
	/**
	 * @vfp: vertical front porch toward the PANEL.
	 */
	u8 vfp;
	/**
	 * @psel: pixel घड़ी भागisor: 0 = 1, 1 = 2, 2 = 4, 3 = 8.
	 */
	u8 psel;
	/**
	 * @dpmctr12: Display timing control 12
	 * Byte 1 bit 4 selects LVGL voltage level: 0 = VGLX, 1 = VGL_REG
	 * Byte 1 bit 1 selects gate संकेत mode: 0 = non-overlap, 1 = overlap
	 * Byte 1 bit 0 selects output संकेत control R/L swap, 0 = normal
	 * 1 = swap all O->E, L->R
	 * Byte 2 is CLW delay घड़ी क्रम CK O/E and CKB O/E संकेतs:
	 * 0x00 = 0us .. 0xFF = 12.75us in 0.05us steps
	 * Byte 3 is FTI_H0 delay समय क्रम STP O/E संकेतs:
	 * 0x00 = 0us .. 0xFF = 12.75us in 0.05us steps
	 */
	u8 dpmctr12[NT35510_P0_DPMCTR12_LEN];
	/**
	 * @gamma_corr_pos_r: Red gamma correction parameters, positive
	 */
	u8 gamma_corr_pos_r[NT35510_P1_GAMMA_LEN];
	/**
	 * @gamma_corr_pos_g: Green gamma correction parameters, positive
	 */
	u8 gamma_corr_pos_g[NT35510_P1_GAMMA_LEN];
	/**
	 * @gamma_corr_pos_b: Blue gamma correction parameters, positive
	 */
	u8 gamma_corr_pos_b[NT35510_P1_GAMMA_LEN];
	/**
	 * @gamma_corr_neg_r: Red gamma correction parameters, negative
	 */
	u8 gamma_corr_neg_r[NT35510_P1_GAMMA_LEN];
	/**
	 * @gamma_corr_neg_g: Green gamma correction parameters, negative
	 */
	u8 gamma_corr_neg_g[NT35510_P1_GAMMA_LEN];
	/**
	 * @gamma_corr_neg_b: Blue gamma correction parameters, negative
	 */
	u8 gamma_corr_neg_b[NT35510_P1_GAMMA_LEN];
पूर्ण;

/**
 * काष्ठा nt35510 - state container क्रम the NT35510 panel
 */
काष्ठा nt35510 अणु
	/**
	 * @dev: the container device
	 */
	काष्ठा device *dev;
	/**
	 * @conf: the specअगरic panel configuration, as the NT35510
	 * can be combined with many physical panels, they can have
	 * dअगरferent physical dimensions and gamma correction etc,
	 * so this is stored in the config.
	 */
	स्थिर काष्ठा nt35510_config *conf;
	/**
	 * @panel: the DRM panel object क्रम the instance
	 */
	काष्ठा drm_panel panel;
	/**
	 * @supplies: regulators supplying the panel
	 */
	काष्ठा regulator_bulk_data supplies[2];
	/**
	 * @reset_gpio: the reset line
	 */
	काष्ठा gpio_desc *reset_gpio;
पूर्ण;

/* Manufacturer command has strictly this byte sequence */
अटल स्थिर u8 nt35510_mauc_mtp_पढ़ो_param[] = अणु 0xAA, 0x55, 0x25, 0x01 पूर्ण;
अटल स्थिर u8 nt35510_mauc_mtp_पढ़ो_setting[] = अणु 0x01, 0x02, 0x00, 0x20,
						    0x33, 0x13, 0x00, 0x40,
						    0x00, 0x00, 0x23, 0x02 पूर्ण;
अटल स्थिर u8 nt35510_mauc_select_page_0[] = अणु 0x55, 0xAA, 0x52, 0x08, 0x00 पूर्ण;
अटल स्थिर u8 nt35510_mauc_select_page_1[] = अणु 0x55, 0xAA, 0x52, 0x08, 0x01 पूर्ण;
अटल स्थिर u8 nt35510_vgh_on[] = अणु 0x01 पूर्ण;

अटल अंतरभूत काष्ठा nt35510 *panel_to_nt35510(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा nt35510, panel);
पूर्ण

#घोषणा NT35510_ROTATE_0_SETTING	0x02
#घोषणा NT35510_ROTATE_180_SETTING	0x00

अटल पूर्णांक nt35510_send_दीर्घ(काष्ठा nt35510 *nt, काष्ठा mipi_dsi_device *dsi,
			     u8 cmd, u8 cmdlen, स्थिर u8 *seq)
अणु
	स्थिर u8 *seqp = seq;
	पूर्णांक cmdwritten = 0;
	पूर्णांक chunk = cmdlen;
	पूर्णांक ret;

	अगर (chunk > 15)
		chunk = 15;
	ret = mipi_dsi_dcs_ग_लिखो(dsi, cmd, seqp, chunk);
	अगर (ret < 0) अणु
		dev_err(nt->dev, "error sending DCS command seq cmd %02x\n", cmd);
		वापस ret;
	पूर्ण
	cmdwritten += chunk;
	seqp += chunk;

	जबतक (cmdwritten < cmdlen) अणु
		chunk = cmdlen - cmdwritten;
		अगर (chunk > 15)
			chunk = 15;
		ret = mipi_dsi_generic_ग_लिखो(dsi, seqp, chunk);
		अगर (ret < 0) अणु
			dev_err(nt->dev, "error sending generic write seq %02x\n", cmd);
			वापस ret;
		पूर्ण
		cmdwritten += chunk;
		seqp += chunk;
	पूर्ण
	dev_dbg(nt->dev, "sent command %02x %02x bytes\n", cmd, cmdlen);
	वापस 0;
पूर्ण

अटल पूर्णांक nt35510_पढ़ो_id(काष्ठा nt35510 *nt)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	u8 id1, id2, id3;
	पूर्णांक ret;

	ret = mipi_dsi_dcs_पढ़ो(dsi, MCS_CMD_READ_ID1, &id1, 1);
	अगर (ret < 0) अणु
		dev_err(nt->dev, "could not read MTP ID1\n");
		वापस ret;
	पूर्ण
	ret = mipi_dsi_dcs_पढ़ो(dsi, MCS_CMD_READ_ID2, &id2, 1);
	अगर (ret < 0) अणु
		dev_err(nt->dev, "could not read MTP ID2\n");
		वापस ret;
	पूर्ण
	ret = mipi_dsi_dcs_पढ़ो(dsi, MCS_CMD_READ_ID3, &id3, 1);
	अगर (ret < 0) अणु
		dev_err(nt->dev, "could not read MTP ID3\n");
		वापस ret;
	पूर्ण

	/*
	 * Multi-Time Programmable (?) memory contains manufacturer
	 * ID (e.g. Hydis 0x55), driver ID (e.g. NT35510 0xc0) and
	 * version.
	 */
	dev_info(nt->dev, "MTP ID manufacturer: %02x version: %02x driver: %02x\n", id1, id2, id3);

	वापस 0;
पूर्ण

/**
 * nt35510_setup_घातer() - set up घातer config in page 1
 * @nt: the display instance to set up
 */
अटल पूर्णांक nt35510_setup_घातer(काष्ठा nt35510 *nt)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	पूर्णांक ret;

	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_SETAVDD,
				NT35510_P1_AVDD_LEN,
				nt->conf->avdd);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_BT1CTR,
				NT35510_P1_BT1CTR_LEN,
				nt->conf->bt1ctr);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_SETAVEE,
				NT35510_P1_AVEE_LEN,
				nt->conf->avee);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_BT2CTR,
				NT35510_P1_BT2CTR_LEN,
				nt->conf->bt2ctr);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_SETVGH,
				NT35510_P1_VGH_LEN,
				nt->conf->vgh);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_BT4CTR,
				NT35510_P1_BT4CTR_LEN,
				nt->conf->bt4ctr);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_VGHCTR,
				ARRAY_SIZE(nt35510_vgh_on),
				nt35510_vgh_on);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_SETVGL,
				NT35510_P1_VGL_LEN,
				nt->conf->vgl);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_BT5CTR,
				NT35510_P1_BT5CTR_LEN,
				nt->conf->bt5ctr);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_SETVGP,
				NT35510_P1_VGP_LEN,
				nt->conf->vgp);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_SETVGN,
				NT35510_P1_VGN_LEN,
				nt->conf->vgn);
	अगर (ret)
		वापस ret;

	/* Typically 10 ms */
	usleep_range(10000, 20000);

	वापस 0;
पूर्ण

/**
 * nt35510_setup_display() - set up display config in page 0
 * @nt: the display instance to set up
 */
अटल पूर्णांक nt35510_setup_display(काष्ठा nt35510 *nt)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	स्थिर काष्ठा nt35510_config *conf = nt->conf;
	u8 करोpctr[NT35510_P0_DOPCTR_LEN];
	u8 gseqctr[NT35510_P0_GSEQCTR_LEN];
	u8 dpfrctr[NT35510_P0_DPFRCTR1_LEN];
	/* FIXME: set up any rotation (assume none क्रम now) */
	u8 addr_mode = NT35510_ROTATE_0_SETTING;
	u8 val;
	पूर्णांक ret;

	/* Enable TE, EoTP and RGB pixel क्रमmat */
	करोpctr[0] = NT35510_DOPCTR_0_DSITE | NT35510_DOPCTR_0_EOTP |
		NT35510_DOPCTR_0_N565;
	करोpctr[1] = NT35510_DOPCTR_1_CTB;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P0_DOPCTR,
				NT35510_P0_DOPCTR_LEN,
				करोpctr);
	अगर (ret)
		वापस ret;

	ret = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_SET_ADDRESS_MODE, &addr_mode,
				 माप(addr_mode));
	अगर (ret < 0)
		वापस ret;

	/*
	 * Source data hold समय, शेष 0x05 = 2.5us
	 * 0x00..0x3F = 0 .. 31.5us in steps of 0.5us
	 * 0x0A = 5us
	 */
	val = 0x0A;
	ret = mipi_dsi_dcs_ग_लिखो(dsi, NT35510_P0_SDHDTCTR, &val,
				 माप(val));
	अगर (ret < 0)
		वापस ret;

	/* EQ control क्रम gate संकेतs, 0x00 = 0 us */
	gseqctr[0] = 0x00;
	gseqctr[1] = 0x00;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P0_GSEQCTR,
				NT35510_P0_GSEQCTR_LEN,
				gseqctr);
	अगर (ret)
		वापस ret;

	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P0_SDEQCTR,
				NT35510_P0_SDEQCTR_LEN,
				conf->sdeqctr);
	अगर (ret)
		वापस ret;

	ret = mipi_dsi_dcs_ग_लिखो(dsi, NT35510_P0_SDVPCTR,
				 &conf->sdvpctr, 1);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Display timing control क्रम active and idle off mode:
	 * the first byte contains
	 * the two high bits of T1A and second byte the low 8 bits, and
	 * the valid range is 0x100 (257) to 0x3ff (1023) representing
	 * 258..1024 (+1) pixel घड़ी ticks क्रम one scanline. At 20MHz pixel
	 * घड़ी this covers the range of 12.90us .. 51.20us in steps of
	 * 0.05us, the शेष is 0x184 (388) representing 389 ticks.
	 * The third byte is VBPDA, vertical back porch display active
	 * and the fourth VFPDA, vertical front porch display active,
	 * both given in number of scanlines in the range 0x02..0xff
	 * क्रम 2..255 scanlines. The fअगरth byte is 2 bits selecting
	 * PSEL क्रम active and idle off mode, how much the 20MHz घड़ी
	 * is भागided by 0..3.  This needs to be adjusted to get the right
	 * frame rate.
	 */
	dpfrctr[0] = (conf->t1 >> 8) & 0xFF;
	dpfrctr[1] = conf->t1 & 0xFF;
	/* Vertical back porch */
	dpfrctr[2] = conf->vbp;
	/* Vertical front porch */
	dpfrctr[3] = conf->vfp;
	dpfrctr[4] = conf->psel;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P0_DPFRCTR1,
				NT35510_P0_DPFRCTR1_LEN,
				dpfrctr);
	अगर (ret)
		वापस ret;
	/* For idle and partial idle off mode we decrease front porch by one */
	dpfrctr[3]--;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P0_DPFRCTR2,
				NT35510_P0_DPFRCTR2_LEN,
				dpfrctr);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P0_DPFRCTR3,
				NT35510_P0_DPFRCTR3_LEN,
				dpfrctr);
	अगर (ret)
		वापस ret;

	/* Enable TE on vblank */
	ret = mipi_dsi_dcs_set_tear_on(dsi, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	अगर (ret)
		वापस ret;

	/* Turn on the pads? */
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P0_DPMCTR12,
				NT35510_P0_DPMCTR12_LEN,
				conf->dpmctr12);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक nt35510_set_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा nt35510 *nt = bl_get_data(bl);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	u8 brightness = bl->props.brightness;
	पूर्णांक ret;

	dev_dbg(nt->dev, "set brightness %d\n", brightness);
	ret = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_SET_DISPLAY_BRIGHTNESS,
				 &brightness,
				 माप(brightness));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops nt35510_bl_ops = अणु
	.update_status = nt35510_set_brightness,
पूर्ण;

/*
 * This घातer-on sequence
 */
अटल पूर्णांक nt35510_घातer_on(काष्ठा nt35510 *nt)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(nt->supplies), nt->supplies);
	अगर (ret < 0) अणु
		dev_err(nt->dev, "unable to enable regulators\n");
		वापस ret;
	पूर्ण

	/* Toggle RESET in accordance with datasheet page 370 */
	अगर (nt->reset_gpio) अणु
		gpiod_set_value(nt->reset_gpio, 1);
		/* Active min 10 us according to datasheet, let's say 20 */
		usleep_range(20, 1000);
		gpiod_set_value(nt->reset_gpio, 0);
		/*
		 * 5 ms during sleep mode, 120 ms during sleep out mode
		 * according to datasheet, let's use 120-140 ms.
		 */
		usleep_range(120000, 140000);
	पूर्ण

	ret = nt35510_send_दीर्घ(nt, dsi, MCS_CMD_MTP_READ_PARAM,
				ARRAY_SIZE(nt35510_mauc_mtp_पढ़ो_param),
				nt35510_mauc_mtp_पढ़ो_param);
	अगर (ret)
		वापस ret;

	ret = nt35510_send_दीर्घ(nt, dsi, MCS_CMD_MTP_READ_SETTING,
				ARRAY_SIZE(nt35510_mauc_mtp_पढ़ो_setting),
				nt35510_mauc_mtp_पढ़ो_setting);
	अगर (ret)
		वापस ret;

	ret = nt35510_पढ़ो_id(nt);
	अगर (ret)
		वापस ret;

	/* Set up stuff in  manufacturer control, page 1 */
	ret = nt35510_send_दीर्घ(nt, dsi, MCS_CMD_MAUCCTR,
				ARRAY_SIZE(nt35510_mauc_select_page_1),
				nt35510_mauc_select_page_1);
	अगर (ret)
		वापस ret;

	ret = nt35510_setup_घातer(nt);
	अगर (ret)
		वापस ret;

	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_SET_GAMMA_RED_POS,
				NT35510_P1_GAMMA_LEN,
				nt->conf->gamma_corr_pos_r);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_SET_GAMMA_GREEN_POS,
				NT35510_P1_GAMMA_LEN,
				nt->conf->gamma_corr_pos_g);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_SET_GAMMA_BLUE_POS,
				NT35510_P1_GAMMA_LEN,
				nt->conf->gamma_corr_pos_b);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_SET_GAMMA_RED_NEG,
				NT35510_P1_GAMMA_LEN,
				nt->conf->gamma_corr_neg_r);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_SET_GAMMA_GREEN_NEG,
				NT35510_P1_GAMMA_LEN,
				nt->conf->gamma_corr_neg_g);
	अगर (ret)
		वापस ret;
	ret = nt35510_send_दीर्घ(nt, dsi, NT35510_P1_SET_GAMMA_BLUE_NEG,
				NT35510_P1_GAMMA_LEN,
				nt->conf->gamma_corr_neg_b);
	अगर (ret)
		वापस ret;

	/* Set up stuff in  manufacturer control, page 0 */
	ret = nt35510_send_दीर्घ(nt, dsi, MCS_CMD_MAUCCTR,
				ARRAY_SIZE(nt35510_mauc_select_page_0),
				nt35510_mauc_select_page_0);
	अगर (ret)
		वापस ret;

	ret = nt35510_setup_display(nt);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक nt35510_घातer_off(काष्ठा nt35510 *nt)
अणु
	पूर्णांक ret;

	ret = regulator_bulk_disable(ARRAY_SIZE(nt->supplies), nt->supplies);
	अगर (ret)
		वापस ret;

	अगर (nt->reset_gpio)
		gpiod_set_value(nt->reset_gpio, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक nt35510_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा nt35510 *nt = panel_to_nt35510(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	पूर्णांक ret;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret) अणु
		dev_err(nt->dev, "failed to turn display off (%d)\n", ret);
		वापस ret;
	पूर्ण
	usleep_range(10000, 20000);

	/* Enter sleep mode */
	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret) अणु
		dev_err(nt->dev, "failed to enter sleep mode (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* Wait 4 frames, how much is that 5ms in the venकरोr driver */
	usleep_range(5000, 10000);

	ret = nt35510_घातer_off(nt);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक nt35510_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा nt35510 *nt = panel_to_nt35510(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	पूर्णांक ret;

	ret = nt35510_घातer_on(nt);
	अगर (ret)
		वापस ret;

	/* Exit sleep mode */
	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret) अणु
		dev_err(nt->dev, "failed to exit sleep mode (%d)\n", ret);
		वापस ret;
	पूर्ण
	/* Up to 120 ms */
	usleep_range(120000, 150000);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret) अणु
		dev_err(nt->dev, "failed to turn display on (%d)\n", ret);
		वापस ret;
	पूर्ण
	/* Some 10 ms */
	usleep_range(10000, 20000);

	वापस 0;
पूर्ण

अटल पूर्णांक nt35510_get_modes(काष्ठा drm_panel *panel,
			     काष्ठा drm_connector *connector)
अणु
	काष्ठा nt35510 *nt = panel_to_nt35510(panel);
	काष्ठा drm_display_mode *mode;
	काष्ठा drm_display_info *info;

	info = &connector->display_info;
	info->width_mm = nt->conf->width_mm;
	info->height_mm = nt->conf->height_mm;
	mode = drm_mode_duplicate(connector->dev, &nt->conf->mode);
	अगर (!mode) अणु
		dev_err(panel->dev, "bad mode or failed to add mode\n");
		वापस -EINVAL;
	पूर्ण
	drm_mode_set_name(mode);
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;

	mode->width_mm = nt->conf->width_mm;
	mode->height_mm = nt->conf->height_mm;
	drm_mode_probed_add(connector, mode);

	वापस 1; /* Number of modes */
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs nt35510_drm_funcs = अणु
	.unprepare = nt35510_unprepare,
	.prepare = nt35510_prepare,
	.get_modes = nt35510_get_modes,
पूर्ण;

अटल पूर्णांक nt35510_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा nt35510 *nt;
	पूर्णांक ret;

	nt = devm_kzalloc(dev, माप(काष्ठा nt35510), GFP_KERNEL);
	अगर (!nt)
		वापस -ENOMEM;
	mipi_dsi_set_drvdata(dsi, nt);
	nt->dev = dev;

	dsi->lanes = 2;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	/*
	 * Datasheet suggests max HS rate क्रम NT35510 is 250 MHz
	 * (period समय 4ns, see figure 7.6.4 page 365) and max LP rate is
	 * 20 MHz (period समय 50ns, see figure 7.6.6. page 366).
	 * However these frequencies appear in source code क्रम the Hydis
	 * HVA40WV1 panel and setting up the LP frequency makes the panel
	 * not work.
	 *
	 * TODO: अगर other panels prove to be बंदr to the datasheet,
	 * maybe make this a per-panel config in काष्ठा nt35510_config?
	 */
	dsi->hs_rate = 349440000;
	dsi->lp_rate = 9600000;
	dsi->mode_flags = MIPI_DSI_CLOCK_NON_CONTINUOUS;

	/*
	 * Every new incarnation of this display must have a unique
	 * data entry क्रम the प्रणाली in this driver.
	 */
	nt->conf = of_device_get_match_data(dev);
	अगर (!nt->conf) अणु
		dev_err(dev, "missing device configuration\n");
		वापस -ENODEV;
	पूर्ण

	nt->supplies[0].supply = "vdd"; /* 2.3-4.8 V */
	nt->supplies[1].supply = "vddi"; /* 1.65-3.3V */
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(nt->supplies),
				      nt->supplies);
	अगर (ret < 0)
		वापस ret;
	ret = regulator_set_voltage(nt->supplies[0].consumer,
				    2300000, 4800000);
	अगर (ret)
		वापस ret;
	ret = regulator_set_voltage(nt->supplies[1].consumer,
				    1650000, 3300000);
	अगर (ret)
		वापस ret;

	nt->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_ASIS);
	अगर (IS_ERR(nt->reset_gpio)) अणु
		dev_err(dev, "error getting RESET GPIO\n");
		वापस PTR_ERR(nt->reset_gpio);
	पूर्ण

	drm_panel_init(&nt->panel, dev, &nt35510_drm_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	/*
	 * First, try to locate an बाह्यal backlight (such as on GPIO)
	 * अगर this fails, assume we will want to use the पूर्णांकernal backlight
	 * control.
	 */
	ret = drm_panel_of_backlight(&nt->panel);
	अगर (ret) अणु
		dev_err(dev, "error getting external backlight %d\n", ret);
		वापस ret;
	पूर्ण
	अगर (!nt->panel.backlight) अणु
		काष्ठा backlight_device *bl;

		bl = devm_backlight_device_रेजिस्टर(dev, "nt35510", dev, nt,
						    &nt35510_bl_ops, शून्य);
		अगर (IS_ERR(bl)) अणु
			dev_err(dev, "failed to register backlight device\n");
			वापस PTR_ERR(bl);
		पूर्ण
		bl->props.max_brightness = 255;
		bl->props.brightness = 255;
		bl->props.घातer = FB_BLANK_POWERDOWN;
		nt->panel.backlight = bl;
	पूर्ण

	drm_panel_add(&nt->panel);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0)
		drm_panel_हटाओ(&nt->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक nt35510_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा nt35510 *nt = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	mipi_dsi_detach(dsi);
	/* Power off */
	ret = nt35510_घातer_off(nt);
	drm_panel_हटाओ(&nt->panel);

	वापस ret;
पूर्ण

/*
 * These gamma correction values are 10bit tuples, so only bits 0 and 1 is
 * ever used in the first byte. They क्रमm a positive and negative gamma
 * correction curve क्रम each color, values must be strictly higher क्रम each
 * step on the curve. As can be seen these शेष curves goes from 0x0001
 * to 0x03FE.
 */
#घोषणा NT35510_GAMMA_POS_DEFAULT 0x00, 0x01, 0x00, 0x43, 0x00, \
		0x6B, 0x00, 0x87, 0x00, 0xA3, 0x00, 0xCE, 0x00, 0xF1, 0x01, \
		0x27, 0x01, 0x53, 0x01, 0x98, 0x01, 0xCE, 0x02, 0x22, 0x02, \
		0x83, 0x02, 0x78, 0x02, 0x9E, 0x02, 0xDD, 0x03, 0x00, 0x03, \
		0x2E, 0x03, 0x54, 0x03, 0x7F, 0x03, 0x95, 0x03, 0xB3, 0x03, \
		0xC2, 0x03, 0xE1, 0x03, 0xF1, 0x03, 0xFE

#घोषणा NT35510_GAMMA_NEG_DEFAULT 0x00, 0x01, 0x00, 0x43, 0x00, \
		0x6B, 0x00, 0x87, 0x00, 0xA3, 0x00, 0xCE, 0x00, 0xF1, 0x01, \
		0x27, 0x01, 0x53, 0x01, 0x98, 0x01, 0xCE, 0x02, 0x22, 0x02, \
		0x43, 0x02, 0x50, 0x02, 0x9E, 0x02, 0xDD, 0x03, 0x00, 0x03, \
		0x2E, 0x03, 0x54, 0x03, 0x7F, 0x03, 0x95, 0x03, 0xB3, 0x03, \
		0xC2, 0x03, 0xE1, 0x03, 0xF1, 0x03, 0xFE

/*
 * The Hydis HVA40WV1 panel
 */
अटल स्थिर काष्ठा nt35510_config nt35510_hydis_hva40wv1 = अणु
	.width_mm = 52,
	.height_mm = 86,
	/**
	 * As the Hydis panel is used in command mode, the porches etc
	 * are settings programmed पूर्णांकernally पूर्णांकo the NT35510 controller
	 * and generated toward the physical display. As the panel is not
	 * used in video mode, these are not really exposed to the DSI
	 * host.
	 *
	 * Display frame rate control:
	 * Frame rate = (20 MHz / 1) / (389 * (7 + 50 + 800)) ~= 60 Hz
	 */
	.mode = अणु
		/* The पूर्णांकernal pixel घड़ी of the NT35510 is 20 MHz */
		.घड़ी = 20000,
		.hdisplay = 480,
		.hsync_start = 480 + 2, /* HFP = 2 */
		.hsync_end = 480 + 2 + 0, /* HSync = 0 */
		.htotal = 480 + 2 + 0 + 5, /* HFP = 5 */
		.vdisplay = 800,
		.vsync_start = 800 + 2, /* VFP = 2 */
		.vsync_end = 800 + 2 + 0, /* VSync = 0 */
		.vtotal = 800 + 2 + 0 + 5, /* VBP = 5 */
		.flags = 0,
	पूर्ण,
	/* 0x09: AVDD = 5.6V */
	.avdd = अणु 0x09, 0x09, 0x09 पूर्ण,
	/* 0x34: PCK = Hsync/2, BTP = 2 x VDDB */
	.bt1ctr = अणु 0x34, 0x34, 0x34 पूर्ण,
	/* 0x09: AVEE = -5.6V */
	.avee = अणु 0x09, 0x09, 0x09 पूर्ण,
	/* 0x24: NCK = Hsync/2, BTN =  -2 x VDDB */
	.bt2ctr = अणु 0x24, 0x24, 0x24 पूर्ण,
	/* 0x05 = 12V */
	.vgh = अणु 0x05, 0x05, 0x05 पूर्ण,
	/* 0x24: NCKA = Hsync/2, VGH = 2 x AVDD - AVEE */
	.bt4ctr = अणु 0x24, 0x24, 0x24 पूर्ण,
	/* 0x0B = -13V */
	.vgl = अणु 0x0B, 0x0B, 0x0B पूर्ण,
	/* 0x24: LCKA = Hsync, VGL = AVDD + VCL - AVDD */
	.bt5ctr = अणु 0x24, 0x24, 0x24 पूर्ण,
	/* VGMP: 0x0A3 = 5.0375V, VGSP = 0V */
	.vgp = अणु 0x00, 0xA3, 0x00 पूर्ण,
	/* VGMP: 0x0A3 = 5.0375V, VGSP = 0V */
	.vgn = अणु 0x00, 0xA3, 0x00 पूर्ण,
	/* SDEQCTR: source driver EQ mode 2, 2.5 us rise समय on each step */
	.sdeqctr = अणु 0x01, 0x05, 0x05, 0x05 पूर्ण,
	/* SDVPCTR: Normal operation off color during v porch */
	.sdvpctr = 0x01,
	/* T1: number of pixel घड़ीs on one scanline: 0x184 = 389 घड़ीs */
	.t1 = 0x0184,
	/* VBP: vertical back porch toward the panel */
	.vbp = 7,
	/* VFP: vertical front porch toward the panel */
	.vfp = 50,
	/* PSEL: भागide pixel घड़ी 20MHz with 1 (no घड़ी करोwnscaling) */
	.psel = 0,
	/* DPTMCTR12: 0x03: LVGL = VGLX, overlap mode, swap R->L O->E */
	.dpmctr12 = अणु 0x03, 0x00, 0x00, पूर्ण,
	/* Default gamma correction values */
	.gamma_corr_pos_r = अणु NT35510_GAMMA_POS_DEFAULT पूर्ण,
	.gamma_corr_pos_g = अणु NT35510_GAMMA_POS_DEFAULT पूर्ण,
	.gamma_corr_pos_b = अणु NT35510_GAMMA_POS_DEFAULT पूर्ण,
	.gamma_corr_neg_r = अणु NT35510_GAMMA_NEG_DEFAULT पूर्ण,
	.gamma_corr_neg_g = अणु NT35510_GAMMA_NEG_DEFAULT पूर्ण,
	.gamma_corr_neg_b = अणु NT35510_GAMMA_NEG_DEFAULT पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id nt35510_of_match[] = अणु
	अणु
		.compatible = "hydis,hva40wv1",
		.data = &nt35510_hydis_hva40wv1,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nt35510_of_match);

अटल काष्ठा mipi_dsi_driver nt35510_driver = अणु
	.probe = nt35510_probe,
	.हटाओ = nt35510_हटाओ,
	.driver = अणु
		.name = "panel-novatek-nt35510",
		.of_match_table = nt35510_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(nt35510_driver);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("NT35510-based panel driver");
MODULE_LICENSE("GPL v2");
