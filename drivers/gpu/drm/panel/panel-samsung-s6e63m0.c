<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * S6E63M0 AMOLED LCD drm_panel driver.
 *
 * Copyright (C) 2019 Paweध Chmiel <pawel.mikolaj.chmiel@gmail.com>
 * Derived from drivers/gpu/drm/panel-samsung-ld9040.c
 *
 * Andrzej Hajda <a.hajda@samsung.com>
 */

#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/media-bus-क्रमmat.h>

#समावेश <video/mipi_display.h>

#समावेश "panel-samsung-s6e63m0.h"

/* Manufacturer Command Set */
#घोषणा MCS_ELVSS_ON		0xb1
#घोषणा MCS_TEMP_SWIRE		0xb2
#घोषणा MCS_PENTILE_1		0xb3
#घोषणा MCS_PENTILE_2		0xb4
#घोषणा MCS_GAMMA_DELTA_Y_RED	0xb5
#घोषणा MCS_GAMMA_DELTA_X_RED	0xb6
#घोषणा MCS_GAMMA_DELTA_Y_GREEN	0xb7
#घोषणा MCS_GAMMA_DELTA_X_GREEN	0xb8
#घोषणा MCS_GAMMA_DELTA_Y_BLUE	0xb9
#घोषणा MCS_GAMMA_DELTA_X_BLUE	0xba
#घोषणा MCS_MIECTL1		0xc0
#घोषणा MCS_BCMODE		0xc1
#घोषणा MCS_ERROR_CHECK		0xd5
#घोषणा MCS_READ_ID1		0xda
#घोषणा MCS_READ_ID2		0xdb
#घोषणा MCS_READ_ID3		0xdc
#घोषणा MCS_LEVEL_2_KEY		0xf0
#घोषणा MCS_MTP_KEY		0xf1
#घोषणा MCS_DISCTL		0xf2
#घोषणा MCS_SRCCTL		0xf6
#घोषणा MCS_IFCTL		0xf7
#घोषणा MCS_PANELCTL		0xf8
#घोषणा MCS_PGAMMACTL		0xfa

#घोषणा S6E63M0_LCD_ID_VALUE_M2		0xA4
#घोषणा S6E63M0_LCD_ID_VALUE_SM2	0xB4
#घोषणा S6E63M0_LCD_ID_VALUE_SM2_1	0xB6

#घोषणा NUM_GAMMA_LEVELS	28
#घोषणा GAMMA_TABLE_COUNT	23

#घोषणा MAX_BRIGHTNESS		(NUM_GAMMA_LEVELS - 1)

/* array of gamma tables क्रम gamma value 2.2 */
अटल u8 स्थिर s6e63m0_gamma_22[NUM_GAMMA_LEVELS][GAMMA_TABLE_COUNT] = अणु
	/* 30 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0xA1, 0x51, 0x7B, 0xCE,
	  0xCB, 0xC2, 0xC7, 0xCB, 0xBC, 0xDA, 0xDD,
	  0xD3, 0x00, 0x53, 0x00, 0x52, 0x00, 0x6F, पूर्ण,
	/* 40 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x97, 0x58, 0x71, 0xCC,
	  0xCB, 0xC0, 0xC5, 0xC9, 0xBA, 0xD9, 0xDC,
	  0xD1, 0x00, 0x5B, 0x00, 0x5A, 0x00, 0x7A, पूर्ण,
	/* 50 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x96, 0x58, 0x72, 0xCB,
	  0xCA, 0xBF, 0xC6, 0xC9, 0xBA, 0xD6, 0xD9,
	  0xCD, 0x00, 0x61, 0x00, 0x61, 0x00, 0x83, पूर्ण,
	/* 60 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x91, 0x5E, 0x6E, 0xC9,
	  0xC9, 0xBD, 0xC4, 0xC9, 0xB8, 0xD3, 0xD7,
	  0xCA, 0x00, 0x69, 0x00, 0x67, 0x00, 0x8D, पूर्ण,
	/* 70 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x8E, 0x62, 0x6B, 0xC7,
	  0xC9, 0xBB, 0xC3, 0xC7, 0xB7, 0xD3, 0xD7,
	  0xCA, 0x00, 0x6E, 0x00, 0x6C, 0x00, 0x94, पूर्ण,
	/* 80 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x89, 0x68, 0x65, 0xC9,
	  0xC9, 0xBC, 0xC1, 0xC5, 0xB6, 0xD2, 0xD5,
	  0xC9, 0x00, 0x73, 0x00, 0x72, 0x00, 0x9A, पूर्ण,
	/* 90 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x89, 0x69, 0x64, 0xC7,
	  0xC8, 0xBB, 0xC0, 0xC5, 0xB4, 0xD2, 0xD5,
	  0xC9, 0x00, 0x77, 0x00, 0x76, 0x00, 0xA0, पूर्ण,
	/* 100 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x86, 0x69, 0x60, 0xC6,
	  0xC8, 0xBA, 0xBF, 0xC4, 0xB4, 0xD0, 0xD4,
	  0xC6, 0x00, 0x7C, 0x00, 0x7A, 0x00, 0xA7, पूर्ण,
	/* 110 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x86, 0x6A, 0x60, 0xC5,
	  0xC7, 0xBA, 0xBD, 0xC3, 0xB2, 0xD0, 0xD4,
	  0xC5, 0x00, 0x80, 0x00, 0x7E, 0x00, 0xAD, पूर्ण,
	/* 120 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x82, 0x6B, 0x5E, 0xC4,
	  0xC8, 0xB9, 0xBD, 0xC2, 0xB1, 0xCE, 0xD2,
	  0xC4, 0x00, 0x85, 0x00, 0x82, 0x00, 0xB3, पूर्ण,
	/* 130 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x8C, 0x6C, 0x60, 0xC3,
	  0xC7, 0xB9, 0xBC, 0xC1, 0xAF, 0xCE, 0xD2,
	  0xC3, 0x00, 0x88, 0x00, 0x86, 0x00, 0xB8, पूर्ण,
	/* 140 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x80, 0x6C, 0x5F, 0xC1,
	  0xC6, 0xB7, 0xBC, 0xC1, 0xAE, 0xCD, 0xD0,
	  0xC2, 0x00, 0x8C, 0x00, 0x8A, 0x00, 0xBE, पूर्ण,
	/* 150 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x80, 0x6E, 0x5F, 0xC1,
	  0xC6, 0xB6, 0xBC, 0xC0, 0xAE, 0xCC, 0xD0,
	  0xC2, 0x00, 0x8F, 0x00, 0x8D, 0x00, 0xC2, पूर्ण,
	/* 160 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x7F, 0x6E, 0x5F, 0xC0,
	  0xC6, 0xB5, 0xBA, 0xBF, 0xAD, 0xCB, 0xCF,
	  0xC0, 0x00, 0x94, 0x00, 0x91, 0x00, 0xC8, पूर्ण,
	/* 170 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x7C, 0x6D, 0x5C, 0xC0,
	  0xC6, 0xB4, 0xBB, 0xBE, 0xAD, 0xCA, 0xCF,
	  0xC0, 0x00, 0x96, 0x00, 0x94, 0x00, 0xCC, पूर्ण,
	/* 180 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x7B, 0x6D, 0x5B, 0xC0,
	  0xC5, 0xB3, 0xBA, 0xBE, 0xAD, 0xCA, 0xCE,
	  0xBF,	0x00, 0x99, 0x00, 0x97, 0x00, 0xD0, पूर्ण,
	/* 190 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x7A, 0x6D, 0x59, 0xC1,
	  0xC5, 0xB4, 0xB8, 0xBD, 0xAC, 0xC9, 0xCE,
	  0xBE, 0x00, 0x9D, 0x00, 0x9A, 0x00, 0xD5, पूर्ण,
	/* 200 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x79, 0x6D, 0x58, 0xC1,
	  0xC4, 0xB4, 0xB6, 0xBD, 0xAA, 0xCA, 0xCD,
	  0xBE, 0x00, 0x9F, 0x00, 0x9D, 0x00, 0xD9, पूर्ण,
	/* 210 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x79, 0x6D, 0x57, 0xC0,
	  0xC4, 0xB4, 0xB7, 0xBD, 0xAA, 0xC8, 0xCC,
	  0xBD, 0x00, 0xA2, 0x00, 0xA0, 0x00, 0xDD, पूर्ण,
	/* 220 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x78, 0x6F, 0x58, 0xBF,
	  0xC4, 0xB3, 0xB5, 0xBB, 0xA9, 0xC8, 0xCC,
	  0xBC, 0x00, 0xA6, 0x00, 0xA3, 0x00, 0xE2, पूर्ण,
	/* 230 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x75, 0x6F, 0x56, 0xBF,
	  0xC3, 0xB2, 0xB6, 0xBB, 0xA8, 0xC7, 0xCB,
	  0xBC, 0x00, 0xA8, 0x00, 0xA6, 0x00, 0xE6, पूर्ण,
	/* 240 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x76, 0x6F, 0x56, 0xC0,
	  0xC3, 0xB2, 0xB5, 0xBA, 0xA8, 0xC6, 0xCB,
	  0xBB, 0x00, 0xAA, 0x00, 0xA8, 0x00, 0xE9, पूर्ण,
	/* 250 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x74, 0x6D, 0x54, 0xBF,
	  0xC3, 0xB2, 0xB4, 0xBA, 0xA7, 0xC6, 0xCA,
	  0xBA, 0x00, 0xAD, 0x00, 0xAB, 0x00, 0xED, पूर्ण,
	/* 260 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x74, 0x6E, 0x54, 0xBD,
	  0xC2, 0xB0, 0xB5, 0xBA, 0xA7, 0xC5, 0xC9,
	  0xBA, 0x00, 0xB0, 0x00, 0xAE, 0x00, 0xF1, पूर्ण,
	/* 270 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x71, 0x6C, 0x50, 0xBD,
	  0xC3, 0xB0, 0xB4, 0xB8, 0xA6, 0xC6, 0xC9,
	  0xBB, 0x00, 0xB2, 0x00, 0xB1, 0x00, 0xF4, पूर्ण,
	/* 280 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x6E, 0x6C, 0x4D, 0xBE,
	  0xC3, 0xB1, 0xB3, 0xB8, 0xA5, 0xC6, 0xC8,
	  0xBB, 0x00, 0xB4, 0x00, 0xB3, 0x00, 0xF7, पूर्ण,
	/* 290 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x71, 0x70, 0x50, 0xBD,
	  0xC1, 0xB0, 0xB2, 0xB8, 0xA4, 0xC6, 0xC7,
	  0xBB, 0x00, 0xB6, 0x00, 0xB6, 0x00, 0xFA, पूर्ण,
	/* 300 cd */
	अणु MCS_PGAMMACTL, 0x02,
	  0x18, 0x08, 0x24, 0x70, 0x6E, 0x4E, 0xBC,
	  0xC0, 0xAF, 0xB3, 0xB8, 0xA5, 0xC5, 0xC7,
	  0xBB, 0x00, 0xB9, 0x00, 0xB8, 0x00, 0xFC, पूर्ण,
पूर्ण;

#घोषणा NUM_ACL_LEVELS 7
#घोषणा ACL_TABLE_COUNT 28

अटल u8 स्थिर s6e63m0_acl[NUM_ACL_LEVELS][ACL_TABLE_COUNT] = अणु
	/* शून्य ACL */
	अणु MCS_BCMODE,
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00 पूर्ण,
	/* 40P ACL */
	अणु MCS_BCMODE,
	  0x4D, 0x96, 0x1D, 0x00, 0x00, 0x01, 0xDF, 0x00,
	  0x00, 0x03, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x01, 0x06, 0x0C, 0x11, 0x16, 0x1C, 0x21, 0x26,
	  0x2B, 0x31, 0x36 पूर्ण,
	/* 43P ACL */
	अणु MCS_BCMODE,
	  0x4D, 0x96, 0x1D, 0x00, 0x00, 0x01, 0xDF, 0x00,
	  0x00, 0x03, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x01, 0x07, 0x0C, 0x12, 0x18, 0x1E, 0x23, 0x29,
	  0x2F, 0x34, 0x3A पूर्ण,
	/* 45P ACL */
	अणु MCS_BCMODE,
	  0x4D, 0x96, 0x1D, 0x00, 0x00, 0x01, 0xDF, 0x00,
	  0x00, 0x03, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x01, 0x07, 0x0D, 0x13, 0x19, 0x1F, 0x25, 0x2B,
	  0x31, 0x37, 0x3D पूर्ण,
	/* 47P ACL */
	अणु MCS_BCMODE,
	  0x4D, 0x96, 0x1D, 0x00, 0x00, 0x01, 0xDF, 0x00,
	  0x00, 0x03, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x01, 0x07, 0x0E, 0x14, 0x1B, 0x21, 0x27, 0x2E,
	  0x34, 0x3B, 0x41 पूर्ण,
	/* 48P ACL */
	अणु MCS_BCMODE,
	  0x4D, 0x96, 0x1D, 0x00, 0x00, 0x01, 0xDF, 0x00,
	  0x00, 0x03, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x01, 0x08, 0x0E, 0x15, 0x1B, 0x22, 0x29, 0x2F,
	  0x36, 0x3C, 0x43 पूर्ण,
	/* 50P ACL */
	अणु MCS_BCMODE,
	  0x4D, 0x96, 0x1D, 0x00, 0x00, 0x01, 0xDF, 0x00,
	  0x00, 0x03, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x01, 0x08, 0x0F, 0x16, 0x1D, 0x24, 0x2A, 0x31,
	  0x38, 0x3F, 0x46 पूर्ण,
पूर्ण;

/* This tells us which ACL level goes with which gamma */
अटल u8 स्थिर s6e63m0_acl_per_gamma[NUM_GAMMA_LEVELS] = अणु
	/* 30 - 60 cd: ACL off/शून्य */
	0, 0, 0, 0,
	/* 70 - 250 cd: 40P ACL */
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	/* 260 - 300 cd: 50P ACL */
	6, 6, 6, 6, 6,
पूर्ण;

/* The ELVSS backlight regulator has 5 levels */
#घोषणा S6E63M0_ELVSS_LEVELS 5

अटल u8 स्थिर s6e63m0_elvss_offsets[S6E63M0_ELVSS_LEVELS] = अणु
	0x00,   /* not set */
	0x0D,   /* 30 cd - 100 cd */
	0x09,   /* 110 cd - 160 cd */
	0x07,   /* 170 cd - 200 cd */
	0x00,   /* 210 cd - 300 cd */
पूर्ण;

/* This tells us which ELVSS level goes with which gamma */
अटल u8 स्थिर s6e63m0_elvss_per_gamma[NUM_GAMMA_LEVELS] = अणु
	/* 30 - 100 cd */
	1, 1, 1, 1, 1, 1, 1, 1,
	/* 110 - 160 cd */
	2, 2, 2, 2, 2, 2,
	/* 170 - 200 cd */
	3, 3, 3, 3,
	/* 210 - 300 cd */
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
पूर्ण;

काष्ठा s6e63m0 अणु
	काष्ठा device *dev;
	पूर्णांक (*dcs_पढ़ो)(काष्ठा device *dev, स्थिर u8 cmd, u8 *val);
	पूर्णांक (*dcs_ग_लिखो)(काष्ठा device *dev, स्थिर u8 *data, माप_प्रकार len);
	काष्ठा drm_panel panel;
	काष्ठा backlight_device *bl_dev;
	u8 lcd_type;
	u8 elvss_pulse;
	bool dsi_mode;

	काष्ठा regulator_bulk_data supplies[2];
	काष्ठा gpio_desc *reset_gpio;

	bool prepared;
	bool enabled;

	/*
	 * This field is tested by functions directly accessing bus beक्रमe
	 * transfer, transfer is skipped अगर it is set. In हाल of transfer
	 * failure or unexpected response the field is set to error value.
	 * Such स्थिरruct allows to eliminate many checks in higher level
	 * functions.
	 */
	पूर्णांक error;
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.घड़ी		= 25628,
	.hdisplay	= 480,
	.hsync_start	= 480 + 16,
	.hsync_end	= 480 + 16 + 2,
	.htotal		= 480 + 16 + 2 + 16,
	.vdisplay	= 800,
	.vsync_start	= 800 + 28,
	.vsync_end	= 800 + 28 + 2,
	.vtotal		= 800 + 28 + 2 + 1,
	.width_mm	= 53,
	.height_mm	= 89,
	.flags		= DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल अंतरभूत काष्ठा s6e63m0 *panel_to_s6e63m0(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा s6e63m0, panel);
पूर्ण

अटल पूर्णांक s6e63m0_clear_error(काष्ठा s6e63m0 *ctx)
अणु
	पूर्णांक ret = ctx->error;

	ctx->error = 0;
	वापस ret;
पूर्ण

अटल व्योम s6e63m0_dcs_पढ़ो(काष्ठा s6e63m0 *ctx, स्थिर u8 cmd, u8 *data)
अणु
	अगर (ctx->error < 0)
		वापस;

	ctx->error = ctx->dcs_पढ़ो(ctx->dev, cmd, data);
पूर्ण

अटल व्योम s6e63m0_dcs_ग_लिखो(काष्ठा s6e63m0 *ctx, स्थिर u8 *data, माप_प्रकार len)
अणु
	अगर (ctx->error < 0 || len == 0)
		वापस;

	ctx->error = ctx->dcs_ग_लिखो(ctx->dev, data, len);
पूर्ण

#घोषणा s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, seq ...) \
	(अणु \
		अटल स्थिर u8 d[] = अणु seq पूर्ण; \
		s6e63m0_dcs_ग_लिखो(ctx, d, ARRAY_SIZE(d)); \
	पूर्ण)

अटल पूर्णांक s6e63m0_check_lcd_type(काष्ठा s6e63m0 *ctx)
अणु
	u8 id1, id2, id3;
	पूर्णांक ret;

	s6e63m0_dcs_पढ़ो(ctx, MCS_READ_ID1, &id1);
	s6e63m0_dcs_पढ़ो(ctx, MCS_READ_ID2, &id2);
	s6e63m0_dcs_पढ़ो(ctx, MCS_READ_ID3, &id3);

	ret = s6e63m0_clear_error(ctx);
	अगर (ret) अणु
		dev_err(ctx->dev, "error checking LCD type (%d)\n", ret);
		ctx->lcd_type = 0x00;
		वापस ret;
	पूर्ण

	dev_info(ctx->dev, "MTP ID: %02x %02x %02x\n", id1, id2, id3);

	/*
	 * We attempt to detect what panel is mounted on the controller.
	 * The third ID byte represents the desired ELVSS pulse क्रम
	 * some displays.
	 */
	चयन (id2) अणु
	हाल S6E63M0_LCD_ID_VALUE_M2:
		dev_info(ctx->dev, "detected LCD panel AMS397GE MIPI M2\n");
		ctx->elvss_pulse = id3;
		अवरोध;
	हाल S6E63M0_LCD_ID_VALUE_SM2:
	हाल S6E63M0_LCD_ID_VALUE_SM2_1:
		dev_info(ctx->dev, "detected LCD panel AMS397GE MIPI SM2\n");
		ctx->elvss_pulse = id3;
		अवरोध;
	शेष:
		dev_info(ctx->dev, "unknown LCD panel type %02x\n", id2);
		/* Default ELVSS pulse level */
		ctx->elvss_pulse = 0x16;
		अवरोध;
	पूर्ण

	ctx->lcd_type = id2;

	वापस 0;
पूर्ण

अटल व्योम s6e63m0_init(काष्ठा s6e63m0 *ctx)
अणु
	/*
	 * We करो not know why there is a dअगरference in the DSI mode.
	 * (No datasheet.)
	 *
	 * In the venकरोr driver this sequence is called
	 * "SEQ_PANEL_CONDITION_SET" or "DCS_CMD_SEQ_PANEL_COND_SET".
	 */
	अगर (ctx->dsi_mode)
		s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_PANELCTL,
					     0x01, 0x2c, 0x2c, 0x07, 0x07, 0x5f, 0xb3,
					     0x6d, 0x97, 0x1d, 0x3a, 0x0f, 0x00, 0x00);
	अन्यथा
		s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_PANELCTL,
					     0x01, 0x27, 0x27, 0x07, 0x07, 0x54, 0x9f,
					     0x63, 0x8f, 0x1a, 0x33, 0x0d, 0x00, 0x00);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_DISCTL,
				     0x02, 0x03, 0x1c, 0x10, 0x10);
	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_IFCTL,
				     0x03, 0x00, 0x00);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_PGAMMACTL,
				     0x00, 0x18, 0x08, 0x24, 0x64, 0x56, 0x33,
				     0xb6, 0xba, 0xa8, 0xac, 0xb1, 0x9d, 0xc1,
				     0xc1, 0xb7, 0x00, 0x9c, 0x00, 0x9f, 0x00,
				     0xd6);
	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_PGAMMACTL,
				     0x01);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_SRCCTL,
				     0x00, 0x8e, 0x07);
	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_PENTILE_1, 0x6c);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_GAMMA_DELTA_Y_RED,
				     0x2c, 0x12, 0x0c, 0x0a, 0x10, 0x0e, 0x17,
				     0x13, 0x1f, 0x1a, 0x2a, 0x24, 0x1f, 0x1b,
				     0x1a, 0x17, 0x2b, 0x26, 0x22, 0x20, 0x3a,
				     0x34, 0x30, 0x2c, 0x29, 0x26, 0x25, 0x23,
				     0x21, 0x20, 0x1e, 0x1e);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_GAMMA_DELTA_X_RED,
				     0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x44,
				     0x44, 0x55, 0x55, 0x66, 0x66, 0x66, 0x66,
				     0x66, 0x66);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_GAMMA_DELTA_Y_GREEN,
				     0x2c, 0x12, 0x0c, 0x0a, 0x10, 0x0e, 0x17,
				     0x13, 0x1f, 0x1a, 0x2a, 0x24, 0x1f, 0x1b,
				     0x1a, 0x17, 0x2b, 0x26, 0x22, 0x20, 0x3a,
				     0x34, 0x30, 0x2c, 0x29, 0x26, 0x25, 0x23,
				     0x21, 0x20, 0x1e, 0x1e);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_GAMMA_DELTA_X_GREEN,
				     0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x44,
				     0x44, 0x55, 0x55, 0x66, 0x66, 0x66, 0x66,
				     0x66, 0x66);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_GAMMA_DELTA_Y_BLUE,
				     0x2c, 0x12, 0x0c, 0x0a, 0x10, 0x0e, 0x17,
				     0x13, 0x1f, 0x1a, 0x2a, 0x24, 0x1f, 0x1b,
				     0x1a, 0x17, 0x2b, 0x26, 0x22, 0x20, 0x3a,
				     0x34, 0x30, 0x2c, 0x29, 0x26, 0x25, 0x23,
				     0x21, 0x20, 0x1e, 0x1e);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_GAMMA_DELTA_X_BLUE,
				     0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x44,
				     0x44, 0x55, 0x55, 0x66, 0x66, 0x66, 0x66,
				     0x66, 0x66);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_BCMODE,
				     0x4d, 0x96, 0x1d, 0x00, 0x00, 0x01, 0xdf,
				     0x00, 0x00, 0x03, 0x1f, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06,
				     0x09, 0x0d, 0x0f, 0x12, 0x15, 0x18);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_TEMP_SWIRE,
				     0x10, 0x10, 0x0b, 0x05);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_MIECTL1,
				     0x01);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_ELVSS_ON,
				     0x0b);
पूर्ण

अटल पूर्णांक s6e63m0_घातer_on(काष्ठा s6e63m0 *ctx)
अणु
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	अगर (ret < 0)
		वापस ret;

	msleep(25);

	/* Be sure to send a reset pulse */
	gpiod_set_value(ctx->reset_gpio, 1);
	msleep(5);
	gpiod_set_value(ctx->reset_gpio, 0);
	msleep(120);

	वापस 0;
पूर्ण

अटल पूर्णांक s6e63m0_घातer_off(काष्ठा s6e63m0 *ctx)
अणु
	पूर्णांक ret;

	gpiod_set_value(ctx->reset_gpio, 1);
	msleep(120);

	ret = regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक s6e63m0_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा s6e63m0 *ctx = panel_to_s6e63m0(panel);

	अगर (!ctx->enabled)
		वापस 0;

	backlight_disable(ctx->bl_dev);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MIPI_DCS_SET_DISPLAY_OFF);
	msleep(10);
	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MIPI_DCS_ENTER_SLEEP_MODE);
	msleep(120);

	ctx->enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक s6e63m0_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा s6e63m0 *ctx = panel_to_s6e63m0(panel);
	पूर्णांक ret;

	अगर (!ctx->prepared)
		वापस 0;

	s6e63m0_clear_error(ctx);

	ret = s6e63m0_घातer_off(ctx);
	अगर (ret < 0)
		वापस ret;

	ctx->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक s6e63m0_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा s6e63m0 *ctx = panel_to_s6e63m0(panel);
	पूर्णांक ret;

	अगर (ctx->prepared)
		वापस 0;

	ret = s6e63m0_घातer_on(ctx);
	अगर (ret < 0)
		वापस ret;

	/* Magic to unlock level 2 control of the display */
	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_LEVEL_2_KEY, 0x5a, 0x5a);
	/* Magic to unlock MTP पढ़ोing */
	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_MTP_KEY, 0x5a, 0x5a);

	ret = s6e63m0_check_lcd_type(ctx);
	अगर (ret < 0)
		वापस ret;

	s6e63m0_init(ctx);

	ret = s6e63m0_clear_error(ctx);

	अगर (ret < 0)
		s6e63m0_unprepare(panel);

	ctx->prepared = true;

	वापस ret;
पूर्ण

अटल पूर्णांक s6e63m0_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा s6e63m0 *ctx = panel_to_s6e63m0(panel);

	अगर (ctx->enabled)
		वापस 0;

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MIPI_DCS_EXIT_SLEEP_MODE);
	msleep(120);
	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MIPI_DCS_SET_DISPLAY_ON);
	msleep(10);

	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_ERROR_CHECK,
				     0xE7, 0x14, 0x60, 0x17, 0x0A, 0x49, 0xC3,
				     0x8F, 0x19, 0x64, 0x91, 0x84, 0x76, 0x20,
				     0x0F, 0x00);

	backlight_enable(ctx->bl_dev);

	ctx->enabled = true;

	वापस 0;
पूर्ण

अटल पूर्णांक s6e63m0_get_modes(काष्ठा drm_panel *panel,
			     काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;
	अटल स्थिर u32 bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;

	mode = drm_mode_duplicate(connector->dev, &शेष_mode);
	अगर (!mode) अणु
		dev_err(panel->dev, "failed to add mode %ux%u@%u\n",
			शेष_mode.hdisplay, शेष_mode.vdisplay,
			drm_mode_vrefresh(&शेष_mode));
		वापस -ENOMEM;
	पूर्ण

	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_display_info_set_bus_क्रमmats(&connector->display_info,
					 &bus_क्रमmat, 1);
	connector->display_info.bus_flags = DRM_BUS_FLAG_DE_LOW |
		DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs s6e63m0_drm_funcs = अणु
	.disable	= s6e63m0_disable,
	.unprepare	= s6e63m0_unprepare,
	.prepare	= s6e63m0_prepare,
	.enable		= s6e63m0_enable,
	.get_modes	= s6e63m0_get_modes,
पूर्ण;

अटल पूर्णांक s6e63m0_set_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा s6e63m0 *ctx = bl_get_data(bd);
	पूर्णांक brightness = bd->props.brightness;
	u8 elvss_val;
	u8 elvss_cmd_set[5];
	पूर्णांक i;

	/* Adjust ELVSS to candela level */
	i = s6e63m0_elvss_per_gamma[brightness];
	elvss_val = ctx->elvss_pulse + s6e63m0_elvss_offsets[i];
	अगर (elvss_val > 0x1f)
		elvss_val = 0x1f;
	elvss_cmd_set[0] = MCS_TEMP_SWIRE;
	elvss_cmd_set[1] = elvss_val;
	elvss_cmd_set[2] = elvss_val;
	elvss_cmd_set[3] = elvss_val;
	elvss_cmd_set[4] = elvss_val;
	s6e63m0_dcs_ग_लिखो(ctx, elvss_cmd_set, 5);

	/* Update the ACL per gamma value */
	i = s6e63m0_acl_per_gamma[brightness];
	s6e63m0_dcs_ग_लिखो(ctx, s6e63m0_acl[i],
			  ARRAY_SIZE(s6e63m0_acl[i]));

	/* Update gamma table */
	s6e63m0_dcs_ग_लिखो(ctx, s6e63m0_gamma_22[brightness],
			  ARRAY_SIZE(s6e63m0_gamma_22[brightness]));
	s6e63m0_dcs_ग_लिखो_seq_अटल(ctx, MCS_PGAMMACTL, 0x03);


	वापस s6e63m0_clear_error(ctx);
पूर्ण

अटल स्थिर काष्ठा backlight_ops s6e63m0_backlight_ops = अणु
	.update_status	= s6e63m0_set_brightness,
पूर्ण;

अटल पूर्णांक s6e63m0_backlight_रेजिस्टर(काष्ठा s6e63m0 *ctx, u32 max_brightness)
अणु
	काष्ठा backlight_properties props = अणु
		.type		= BACKLIGHT_RAW,
		.brightness	= max_brightness,
		.max_brightness = max_brightness,
	पूर्ण;
	काष्ठा device *dev = ctx->dev;
	पूर्णांक ret = 0;

	ctx->bl_dev = devm_backlight_device_रेजिस्टर(dev, "panel", dev, ctx,
						     &s6e63m0_backlight_ops,
						     &props);
	अगर (IS_ERR(ctx->bl_dev)) अणु
		ret = PTR_ERR(ctx->bl_dev);
		dev_err(dev, "error registering backlight device (%d)\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक s6e63m0_probe(काष्ठा device *dev,
		  पूर्णांक (*dcs_पढ़ो)(काष्ठा device *dev, स्थिर u8 cmd, u8 *val),
		  पूर्णांक (*dcs_ग_लिखो)(काष्ठा device *dev, स्थिर u8 *data, माप_प्रकार len),
		  bool dsi_mode)
अणु
	काष्ठा s6e63m0 *ctx;
	u32 max_brightness;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(काष्ठा s6e63m0), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dsi_mode = dsi_mode;
	ctx->dcs_पढ़ो = dcs_पढ़ो;
	ctx->dcs_ग_लिखो = dcs_ग_लिखो;
	dev_set_drvdata(dev, ctx);

	ctx->dev = dev;
	ctx->enabled = false;
	ctx->prepared = false;

	ret = device_property_पढ़ो_u32(dev, "max-brightness", &max_brightness);
	अगर (ret)
		max_brightness = MAX_BRIGHTNESS;
	अगर (max_brightness > MAX_BRIGHTNESS) अणु
		dev_err(dev, "illegal max brightness specified\n");
		max_brightness = MAX_BRIGHTNESS;
	पूर्ण

	ctx->supplies[0].supply = "vdd3";
	ctx->supplies[1].supply = "vci";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ctx->reset_gpio)) अणु
		dev_err(dev, "cannot get reset-gpios %ld\n", PTR_ERR(ctx->reset_gpio));
		वापस PTR_ERR(ctx->reset_gpio);
	पूर्ण

	drm_panel_init(&ctx->panel, dev, &s6e63m0_drm_funcs,
		       dsi_mode ? DRM_MODE_CONNECTOR_DSI :
		       DRM_MODE_CONNECTOR_DPI);

	ret = s6e63m0_backlight_रेजिस्टर(ctx, max_brightness);
	अगर (ret < 0)
		वापस ret;

	drm_panel_add(&ctx->panel);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(s6e63m0_probe);

पूर्णांक s6e63m0_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा s6e63m0 *ctx = dev_get_drvdata(dev);

	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(s6e63m0_हटाओ);

MODULE_AUTHOR("Paweध Chmiel <pawel.mikolaj.chmiel@gmail.com>");
MODULE_DESCRIPTION("s6e63m0 LCD Driver");
MODULE_LICENSE("GPL v2");
