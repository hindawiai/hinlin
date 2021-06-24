<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Maxim Integrated MAX2175 RF to Bits tuner driver
 *
 * This driver & most of the hard coded values are based on the reference
 * application delivered by Maxim क्रम this device.
 *
 * Copyright (C) 2016 Maxim Integrated Products
 * Copyright (C) 2017 Renesas Electronics Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/max2175.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>

#समावेश "max2175.h"

#घोषणा DRIVER_NAME "max2175"

#घोषणा mxm_dbg(ctx, fmt, arg...) dev_dbg(&ctx->client->dev, fmt, ## arg)
#घोषणा mxm_err(ctx, fmt, arg...) dev_err(&ctx->client->dev, fmt, ## arg)

/* Rx mode */
काष्ठा max2175_rxmode अणु
	क्रमागत max2175_band band;		/* Associated band */
	u32 freq;			/* Default freq in Hz */
	u8 i2s_word_size;		/* Bit value */
पूर्ण;

/* Register map to define preset values */
काष्ठा max2175_reg_map अणु
	u8 idx;				/* Register index */
	u8 val;				/* Register value */
पूर्ण;

अटल स्थिर काष्ठा max2175_rxmode eu_rx_modes[] = अणु
	/* EU modes */
	[MAX2175_EU_FM_1_2] = अणु MAX2175_BAND_FM, 98256000, 1 पूर्ण,
	[MAX2175_DAB_1_2]   = अणु MAX2175_BAND_VHF, 182640000, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा max2175_rxmode na_rx_modes[] = अणु
	/* NA modes */
	[MAX2175_NA_FM_1_0] = अणु MAX2175_BAND_FM, 98255520, 1 पूर्ण,
	[MAX2175_NA_FM_2_0] = अणु MAX2175_BAND_FM, 98255520, 6 पूर्ण,
पूर्ण;

/*
 * Preset values:
 * Based on Maxim MAX2175 Register Table revision: 130p10
 */
अटल स्थिर u8 full_fm_eu_1p0[] = अणु
	0x15, 0x04, 0xb8, 0xe3, 0x35, 0x18, 0x7c, 0x00,
	0x00, 0x7d, 0x40, 0x08, 0x70, 0x7a, 0x88, 0x91,
	0x61, 0x61, 0x61, 0x61, 0x5a, 0x0f, 0x34, 0x1c,
	0x14, 0x88, 0x33, 0x02, 0x00, 0x09, 0x00, 0x65,
	0x9f, 0x2b, 0x80, 0x00, 0x95, 0x05, 0x2c, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
	0x4a, 0x08, 0xa8, 0x0e, 0x0e, 0x2f, 0x7e, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xab, 0x5e, 0xa9,
	0xae, 0xbb, 0x57, 0x18, 0x3b, 0x03, 0x3b, 0x64,
	0x40, 0x60, 0x00, 0x2a, 0xbf, 0x3f, 0xff, 0x9f,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
	0xff, 0xfc, 0xef, 0x1c, 0x40, 0x00, 0x00, 0x02,
	0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xac, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x00, 0x00,
	0x00, 0x47, 0x00, 0x00, 0x11, 0x3f, 0x22, 0x00,
	0xf1, 0x00, 0x41, 0x03, 0xb0, 0x00, 0x00, 0x00,
	0x1b,
पूर्ण;

अटल स्थिर u8 full_fm_na_1p0[] = अणु
	0x13, 0x08, 0x8d, 0xc0, 0x35, 0x18, 0x7d, 0x3f,
	0x7d, 0x75, 0x40, 0x08, 0x70, 0x7a, 0x88, 0x91,
	0x61, 0x61, 0x61, 0x61, 0x5c, 0x0f, 0x34, 0x1c,
	0x14, 0x88, 0x33, 0x02, 0x00, 0x01, 0x00, 0x65,
	0x9f, 0x2b, 0x80, 0x00, 0x95, 0x05, 0x2c, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
	0x4a, 0x08, 0xa8, 0x0e, 0x0e, 0xaf, 0x7e, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xab, 0x5e, 0xa9,
	0xae, 0xbb, 0x57, 0x18, 0x3b, 0x03, 0x3b, 0x64,
	0x40, 0x60, 0x00, 0x2a, 0xbf, 0x3f, 0xff, 0x9f,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
	0xff, 0xfc, 0xef, 0x1c, 0x40, 0x00, 0x00, 0x02,
	0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xa6, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x00, 0x00,
	0x00, 0x35, 0x00, 0x00, 0x11, 0x3f, 0x22, 0x00,
	0xf1, 0x00, 0x41, 0x03, 0xb0, 0x00, 0x00, 0x00,
	0x1b,
पूर्ण;

/* DAB1.2 settings */
अटल स्थिर काष्ठा max2175_reg_map dab12_map[] = अणु
	अणु 0x01, 0x13 पूर्ण, अणु 0x02, 0x0d पूर्ण, अणु 0x03, 0x15 पूर्ण, अणु 0x04, 0x55 पूर्ण,
	अणु 0x05, 0x0a पूर्ण, अणु 0x06, 0xa0 पूर्ण, अणु 0x07, 0x40 पूर्ण, अणु 0x08, 0x00 पूर्ण,
	अणु 0x09, 0x00 पूर्ण, अणु 0x0a, 0x7d पूर्ण, अणु 0x0b, 0x4a पूर्ण, अणु 0x0c, 0x28 पूर्ण,
	अणु 0x0e, 0x43 पूर्ण, अणु 0x0f, 0xb5 पूर्ण, अणु 0x10, 0x31 पूर्ण, अणु 0x11, 0x9e पूर्ण,
	अणु 0x12, 0x68 पूर्ण, अणु 0x13, 0x9e पूर्ण, अणु 0x14, 0x68 पूर्ण, अणु 0x15, 0x58 पूर्ण,
	अणु 0x16, 0x2f पूर्ण, अणु 0x17, 0x3f पूर्ण, अणु 0x18, 0x40 पूर्ण, अणु 0x1a, 0x88 पूर्ण,
	अणु 0x1b, 0xaa पूर्ण, अणु 0x1c, 0x9a पूर्ण, अणु 0x1d, 0x00 पूर्ण, अणु 0x1e, 0x00 पूर्ण,
	अणु 0x23, 0x80 पूर्ण, अणु 0x24, 0x00 पूर्ण, अणु 0x25, 0x00 पूर्ण, अणु 0x26, 0x00 पूर्ण,
	अणु 0x27, 0x00 पूर्ण, अणु 0x32, 0x08 पूर्ण, अणु 0x33, 0xf8 पूर्ण, अणु 0x36, 0x2d पूर्ण,
	अणु 0x37, 0x7e पूर्ण, अणु 0x55, 0xaf पूर्ण, अणु 0x56, 0x3f पूर्ण, अणु 0x57, 0xf8 पूर्ण,
	अणु 0x58, 0x99 पूर्ण, अणु 0x76, 0x00 पूर्ण, अणु 0x77, 0x00 पूर्ण, अणु 0x78, 0x02 पूर्ण,
	अणु 0x79, 0x40 पूर्ण, अणु 0x82, 0x00 पूर्ण, अणु 0x83, 0x00 पूर्ण, अणु 0x85, 0x00 पूर्ण,
	अणु 0x86, 0x20 पूर्ण,
पूर्ण;

/* EU FM 1.2 settings */
अटल स्थिर काष्ठा max2175_reg_map fmeu1p2_map[] = अणु
	अणु 0x01, 0x15 पूर्ण, अणु 0x02, 0x04 पूर्ण, अणु 0x03, 0xb8 पूर्ण, अणु 0x04, 0xe3 पूर्ण,
	अणु 0x05, 0x35 पूर्ण, अणु 0x06, 0x18 पूर्ण, अणु 0x07, 0x7c पूर्ण, अणु 0x08, 0x00 पूर्ण,
	अणु 0x09, 0x00 पूर्ण, अणु 0x0a, 0x73 पूर्ण, अणु 0x0b, 0x40 पूर्ण, अणु 0x0c, 0x08 पूर्ण,
	अणु 0x0e, 0x7a पूर्ण, अणु 0x0f, 0x88 पूर्ण, अणु 0x10, 0x91 पूर्ण, अणु 0x11, 0x61 पूर्ण,
	अणु 0x12, 0x61 पूर्ण, अणु 0x13, 0x61 पूर्ण, अणु 0x14, 0x61 पूर्ण, अणु 0x15, 0x5a पूर्ण,
	अणु 0x16, 0x0f पूर्ण, अणु 0x17, 0x34 पूर्ण, अणु 0x18, 0x1c पूर्ण, अणु 0x1a, 0x88 पूर्ण,
	अणु 0x1b, 0x33 पूर्ण, अणु 0x1c, 0x02 पूर्ण, अणु 0x1d, 0x00 पूर्ण, अणु 0x1e, 0x01 पूर्ण,
	अणु 0x23, 0x80 पूर्ण, अणु 0x24, 0x00 पूर्ण, अणु 0x25, 0x95 पूर्ण, अणु 0x26, 0x05 पूर्ण,
	अणु 0x27, 0x2c पूर्ण, अणु 0x32, 0x08 पूर्ण, अणु 0x33, 0xa8 पूर्ण, अणु 0x36, 0x2f पूर्ण,
	अणु 0x37, 0x7e पूर्ण, अणु 0x55, 0xbf पूर्ण, अणु 0x56, 0x3f पूर्ण, अणु 0x57, 0xff पूर्ण,
	अणु 0x58, 0x9f पूर्ण, अणु 0x76, 0xac पूर्ण, अणु 0x77, 0x40 पूर्ण, अणु 0x78, 0x00 पूर्ण,
	अणु 0x79, 0x00 पूर्ण, अणु 0x82, 0x47 पूर्ण, अणु 0x83, 0x00 पूर्ण, अणु 0x85, 0x11 पूर्ण,
	अणु 0x86, 0x3f पूर्ण,
पूर्ण;

/* FM NA 1.0 settings */
अटल स्थिर काष्ठा max2175_reg_map fmna1p0_map[] = अणु
	अणु 0x01, 0x13 पूर्ण, अणु 0x02, 0x08 पूर्ण, अणु 0x03, 0x8d पूर्ण, अणु 0x04, 0xc0 पूर्ण,
	अणु 0x05, 0x35 पूर्ण, अणु 0x06, 0x18 पूर्ण, अणु 0x07, 0x7d पूर्ण, अणु 0x08, 0x3f पूर्ण,
	अणु 0x09, 0x7d पूर्ण, अणु 0x0a, 0x75 पूर्ण, अणु 0x0b, 0x40 पूर्ण, अणु 0x0c, 0x08 पूर्ण,
	अणु 0x0e, 0x7a पूर्ण, अणु 0x0f, 0x88 पूर्ण, अणु 0x10, 0x91 पूर्ण, अणु 0x11, 0x61 पूर्ण,
	अणु 0x12, 0x61 पूर्ण, अणु 0x13, 0x61 पूर्ण, अणु 0x14, 0x61 पूर्ण, अणु 0x15, 0x5c पूर्ण,
	अणु 0x16, 0x0f पूर्ण, अणु 0x17, 0x34 पूर्ण, अणु 0x18, 0x1c पूर्ण, अणु 0x1a, 0x88 पूर्ण,
	अणु 0x1b, 0x33 पूर्ण, अणु 0x1c, 0x02 पूर्ण, अणु 0x1d, 0x00 पूर्ण, अणु 0x1e, 0x01 पूर्ण,
	अणु 0x23, 0x80 पूर्ण, अणु 0x24, 0x00 पूर्ण, अणु 0x25, 0x95 पूर्ण, अणु 0x26, 0x05 पूर्ण,
	अणु 0x27, 0x2c पूर्ण, अणु 0x32, 0x08 पूर्ण, अणु 0x33, 0xa8 पूर्ण, अणु 0x36, 0xaf पूर्ण,
	अणु 0x37, 0x7e पूर्ण, अणु 0x55, 0xbf पूर्ण, अणु 0x56, 0x3f पूर्ण, अणु 0x57, 0xff पूर्ण,
	अणु 0x58, 0x9f पूर्ण, अणु 0x76, 0xa6 पूर्ण, अणु 0x77, 0x40 पूर्ण, अणु 0x78, 0x00 पूर्ण,
	अणु 0x79, 0x00 पूर्ण, अणु 0x82, 0x35 पूर्ण, अणु 0x83, 0x00 पूर्ण, अणु 0x85, 0x11 पूर्ण,
	अणु 0x86, 0x3f पूर्ण,
पूर्ण;

/* FM NA 2.0 settings */
अटल स्थिर काष्ठा max2175_reg_map fmna2p0_map[] = अणु
	अणु 0x01, 0x13 पूर्ण, अणु 0x02, 0x08 पूर्ण, अणु 0x03, 0x8d पूर्ण, अणु 0x04, 0xc0 पूर्ण,
	अणु 0x05, 0x35 पूर्ण, अणु 0x06, 0x18 पूर्ण, अणु 0x07, 0x7c पूर्ण, अणु 0x08, 0x54 पूर्ण,
	अणु 0x09, 0xa7 पूर्ण, अणु 0x0a, 0x55 पूर्ण, अणु 0x0b, 0x42 पूर्ण, अणु 0x0c, 0x48 पूर्ण,
	अणु 0x0e, 0x7a पूर्ण, अणु 0x0f, 0x88 पूर्ण, अणु 0x10, 0x91 पूर्ण, अणु 0x11, 0x61 पूर्ण,
	अणु 0x12, 0x61 पूर्ण, अणु 0x13, 0x61 पूर्ण, अणु 0x14, 0x61 पूर्ण, अणु 0x15, 0x5c पूर्ण,
	अणु 0x16, 0x0f पूर्ण, अणु 0x17, 0x34 पूर्ण, अणु 0x18, 0x1c पूर्ण, अणु 0x1a, 0x88 पूर्ण,
	अणु 0x1b, 0x33 पूर्ण, अणु 0x1c, 0x02 पूर्ण, अणु 0x1d, 0x00 पूर्ण, अणु 0x1e, 0x01 पूर्ण,
	अणु 0x23, 0x80 पूर्ण, अणु 0x24, 0x00 पूर्ण, अणु 0x25, 0x95 पूर्ण, अणु 0x26, 0x05 पूर्ण,
	अणु 0x27, 0x2c पूर्ण, अणु 0x32, 0x08 पूर्ण, अणु 0x33, 0xa8 पूर्ण, अणु 0x36, 0xaf पूर्ण,
	अणु 0x37, 0x7e पूर्ण, अणु 0x55, 0xbf पूर्ण, अणु 0x56, 0x3f पूर्ण, अणु 0x57, 0xff पूर्ण,
	अणु 0x58, 0x9f पूर्ण, अणु 0x76, 0xac पूर्ण, अणु 0x77, 0xc0 पूर्ण, अणु 0x78, 0x00 पूर्ण,
	अणु 0x79, 0x00 पूर्ण, अणु 0x82, 0x6b पूर्ण, अणु 0x83, 0x00 पूर्ण, अणु 0x85, 0x11 पूर्ण,
	अणु 0x86, 0x3f पूर्ण,
पूर्ण;

अटल स्थिर u16 ch_coeff_dab1[] = अणु
	0x001c, 0x0007, 0xffcd, 0x0056, 0xffa4, 0x0033, 0x0027, 0xff61,
	0x010e, 0xfec0, 0x0106, 0xffb8, 0xff1c, 0x023c, 0xfcb2, 0x039b,
	0xfd4e, 0x0055, 0x036a, 0xf7de, 0x0d21, 0xee72, 0x1499, 0x6a51,
पूर्ण;

अटल स्थिर u16 ch_coeff_fmeu[] = अणु
	0x0000, 0xffff, 0x0001, 0x0002, 0xfffa, 0xffff, 0x0015, 0xffec,
	0xffde, 0x0054, 0xfff9, 0xff52, 0x00b8, 0x00a2, 0xfe0a, 0x00af,
	0x02e3, 0xfc14, 0xfe89, 0x089d, 0xfa2e, 0xf30f, 0x25be, 0x4eb6,
पूर्ण;

अटल स्थिर u16 eq_coeff_fmeu1_ra02_m6db[] = अणु
	0x0040, 0xffc6, 0xfffa, 0x002c, 0x000d, 0xff90, 0x0037, 0x006e,
	0xffc0, 0xff5b, 0x006a, 0x00f0, 0xff57, 0xfe94, 0x0112, 0x0252,
	0xfe0c, 0xfc6a, 0x0385, 0x0553, 0xfa49, 0xf789, 0x0b91, 0x1a10,
पूर्ण;

अटल स्थिर u16 ch_coeff_fmna[] = अणु
	0x0001, 0x0003, 0xfffe, 0xfff4, 0x0000, 0x001f, 0x000c, 0xffbc,
	0xffd3, 0x007d, 0x0075, 0xff33, 0xff01, 0x0131, 0x01ef, 0xfe60,
	0xfc7a, 0x020e, 0x0656, 0xfd94, 0xf395, 0x02ab, 0x2857, 0x3d3f,
पूर्ण;

अटल स्थिर u16 eq_coeff_fmna1_ra02_m6db[] = अणु
	0xfff1, 0xffe1, 0xffef, 0x000e, 0x0030, 0x002f, 0xfff6, 0xffa7,
	0xff9d, 0x000a, 0x00a2, 0x00b5, 0xffea, 0xfed9, 0xfec5, 0x003d,
	0x0217, 0x021b, 0xff5a, 0xfc2b, 0xfcbd, 0x02c4, 0x0ac3, 0x0e85,
पूर्ण;

अटल स्थिर u8 adc_presets[2][23] = अणु
	अणु
		0x83, 0x00, 0xcf, 0xb4, 0x0f, 0x2c, 0x0c, 0x49,
		0x00, 0x00, 0x00, 0x8c,	0x02, 0x02, 0x00, 0x04,
		0xec, 0x82, 0x4b, 0xcc, 0x01, 0x88, 0x0c,
	पूर्ण,
	अणु
		0x83, 0x00, 0xcf, 0xb4,	0x0f, 0x2c, 0x0c, 0x49,
		0x00, 0x00, 0x00, 0x8c,	0x02, 0x20, 0x33, 0x8c,
		0x57, 0xd7, 0x59, 0xb7,	0x65, 0x0e, 0x0c,
	पूर्ण,
पूर्ण;

/* Tuner bands */
अटल स्थिर काष्ठा v4l2_frequency_band eu_bands_rf = अणु
	.tuner = 0,
	.type = V4L2_TUNER_RF,
	.index = 0,
	.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
	.rangelow   = 65000000,
	.rangehigh  = 240000000,
पूर्ण;

अटल स्थिर काष्ठा v4l2_frequency_band na_bands_rf = अणु
	.tuner = 0,
	.type = V4L2_TUNER_RF,
	.index = 0,
	.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
	.rangelow   = 65000000,
	.rangehigh  = 108000000,
पूर्ण;

/* Regmap settings */
अटल स्थिर काष्ठा regmap_range max2175_regmap_अस्थिर_range[] = अणु
	regmap_reg_range(0x30, 0x35),
	regmap_reg_range(0x3a, 0x45),
	regmap_reg_range(0x59, 0x5e),
	regmap_reg_range(0x73, 0x75),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table max2175_अस्थिर_regs = अणु
	.yes_ranges = max2175_regmap_अस्थिर_range,
	.n_yes_ranges = ARRAY_SIZE(max2175_regmap_अस्थिर_range),
पूर्ण;

अटल स्थिर काष्ठा reg_शेष max2175_reg_शेषs[] = अणु
	अणु 0x00, 0x07पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max2175_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xff,
	.reg_शेषs = max2175_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(max2175_reg_शेषs),
	.अस्थिर_table = &max2175_अस्थिर_regs,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

काष्ठा max2175 अणु
	काष्ठा v4l2_subdev sd;		/* Sub-device */
	काष्ठा i2c_client *client;	/* I2C client */

	/* Controls */
	काष्ठा v4l2_ctrl_handler ctrl_hdl;
	काष्ठा v4l2_ctrl *lna_gain;	/* LNA gain value */
	काष्ठा v4l2_ctrl *अगर_gain;	/* I/F gain value */
	काष्ठा v4l2_ctrl *pll_lock;	/* PLL lock */
	काष्ठा v4l2_ctrl *i2s_en;	/* I2S output enable */
	काष्ठा v4l2_ctrl *hsls;		/* High-side/Low-side polarity */
	काष्ठा v4l2_ctrl *rx_mode;	/* Receive mode */

	/* Regmap */
	काष्ठा regmap *regmap;

	/* Cached configuration */
	u32 freq;			/* Tuned freq In Hz */
	स्थिर काष्ठा max2175_rxmode *rx_modes;		/* EU or NA modes */
	स्थिर काष्ठा v4l2_frequency_band *bands_rf;	/* EU or NA bands */

	/* Device settings */
	अचिन्हित दीर्घ xtal_freq;	/* Ref Oscillator freq in Hz */
	u32 decim_ratio;
	bool master;			/* Master/Slave */
	bool am_hiz;			/* AM Hi-Z filter */

	/* ROM values */
	u8 rom_bbf_bw_am;
	u8 rom_bbf_bw_fm;
	u8 rom_bbf_bw_dab;

	/* Driver निजी variables */
	bool mode_resolved;		/* Flag to sanity check settings */
पूर्ण;

अटल अंतरभूत काष्ठा max2175 *max2175_from_sd(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा max2175, sd);
पूर्ण

अटल अंतरभूत काष्ठा max2175 *max2175_from_ctrl_hdl(काष्ठा v4l2_ctrl_handler *h)
अणु
	वापस container_of(h, काष्ठा max2175, ctrl_hdl);
पूर्ण

/* Get bitval of a given val */
अटल अंतरभूत u8 max2175_get_bitval(u8 val, u8 msb, u8 lsb)
अणु
	वापस (val & GENMASK(msb, lsb)) >> lsb;
पूर्ण

/* Read/Write bit(s) on top of regmap */
अटल पूर्णांक max2175_पढ़ो(काष्ठा max2175 *ctx, u8 idx, u8 *val)
अणु
	u32 regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(ctx->regmap, idx, &regval);
	अगर (ret)
		mxm_err(ctx, "read ret(%d): idx 0x%02x\n", ret, idx);
	अन्यथा
		*val = regval;

	वापस ret;
पूर्ण

अटल पूर्णांक max2175_ग_लिखो(काष्ठा max2175 *ctx, u8 idx, u8 val)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(ctx->regmap, idx, val);
	अगर (ret)
		mxm_err(ctx, "write ret(%d): idx 0x%02x val 0x%02x\n",
			ret, idx, val);

	वापस ret;
पूर्ण

अटल u8 max2175_पढ़ो_bits(काष्ठा max2175 *ctx, u8 idx, u8 msb, u8 lsb)
अणु
	u8 val;

	अगर (max2175_पढ़ो(ctx, idx, &val))
		वापस 0;

	वापस max2175_get_bitval(val, msb, lsb);
पूर्ण

अटल पूर्णांक max2175_ग_लिखो_bits(काष्ठा max2175 *ctx, u8 idx,
			     u8 msb, u8 lsb, u8 newval)
अणु
	पूर्णांक ret = regmap_update_bits(ctx->regmap, idx, GENMASK(msb, lsb),
				     newval << lsb);

	अगर (ret)
		mxm_err(ctx, "wbits ret(%d): idx 0x%02x\n", ret, idx);

	वापस ret;
पूर्ण

अटल पूर्णांक max2175_ग_लिखो_bit(काष्ठा max2175 *ctx, u8 idx, u8 bit, u8 newval)
अणु
	वापस max2175_ग_लिखो_bits(ctx, idx, bit, bit, newval);
पूर्ण

/* Checks expected pattern every msec until समयout */
अटल पूर्णांक max2175_poll_समयout(काष्ठा max2175 *ctx, u8 idx, u8 msb, u8 lsb,
				u8 exp_bitval, u32 समयout_us)
अणु
	अचिन्हित पूर्णांक val;

	वापस regmap_पढ़ो_poll_समयout(ctx->regmap, idx, val,
			(max2175_get_bitval(val, msb, lsb) == exp_bitval),
			1000, समयout_us);
पूर्ण

अटल पूर्णांक max2175_poll_csm_पढ़ोy(काष्ठा max2175 *ctx)
अणु
	पूर्णांक ret;

	ret = max2175_poll_समयout(ctx, 69, 1, 1, 0, 50000);
	अगर (ret)
		mxm_err(ctx, "csm not ready\n");

	वापस ret;
पूर्ण

#घोषणा MAX2175_IS_BAND_AM(ctx)		\
	(max2175_पढ़ो_bits(ctx, 5, 1, 0) == MAX2175_BAND_AM)

#घोषणा MAX2175_IS_BAND_VHF(ctx)	\
	(max2175_पढ़ो_bits(ctx, 5, 1, 0) == MAX2175_BAND_VHF)

#घोषणा MAX2175_IS_FM_MODE(ctx)		\
	(max2175_पढ़ो_bits(ctx, 12, 5, 4) == 0)

#घोषणा MAX2175_IS_FMHD_MODE(ctx)	\
	(max2175_पढ़ो_bits(ctx, 12, 5, 4) == 1)

#घोषणा MAX2175_IS_DAB_MODE(ctx)	\
	(max2175_पढ़ो_bits(ctx, 12, 5, 4) == 2)

अटल पूर्णांक max2175_band_from_freq(u32 freq)
अणु
	अगर (freq >= 144000 && freq <= 26100000)
		वापस MAX2175_BAND_AM;
	अन्यथा अगर (freq >= 65000000 && freq <= 108000000)
		वापस MAX2175_BAND_FM;

	वापस MAX2175_BAND_VHF;
पूर्ण

अटल व्योम max2175_i2s_enable(काष्ठा max2175 *ctx, bool enable)
अणु
	अगर (enable)
		/* Stuff bits are zeroed */
		max2175_ग_लिखो_bits(ctx, 104, 3, 0, 2);
	अन्यथा
		/* Keep SCK alive */
		max2175_ग_लिखो_bits(ctx, 104, 3, 0, 9);
	mxm_dbg(ctx, "i2s %sabled\n", enable ? "en" : "dis");
पूर्ण

अटल व्योम max2175_set_filter_coeffs(काष्ठा max2175 *ctx, u8 m_sel,
				      u8 bank, स्थिर u16 *coeffs)
अणु
	अचिन्हित पूर्णांक i;
	u8 coeff_addr, upper_address = 24;

	mxm_dbg(ctx, "set_filter_coeffs: m_sel %d bank %d\n", m_sel, bank);
	max2175_ग_लिखो_bits(ctx, 114, 5, 4, m_sel);

	अगर (m_sel == 2)
		upper_address = 12;

	क्रम (i = 0; i < upper_address; i++) अणु
		coeff_addr = i + bank * 24;
		max2175_ग_लिखो(ctx, 115, coeffs[i] >> 8);
		max2175_ग_लिखो(ctx, 116, coeffs[i]);
		max2175_ग_लिखो(ctx, 117, coeff_addr | 1 << 7);
	पूर्ण
	max2175_ग_लिखो_bit(ctx, 117, 7, 0);
पूर्ण

अटल व्योम max2175_load_fmeu_1p2(काष्ठा max2175 *ctx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fmeu1p2_map); i++)
		max2175_ग_लिखो(ctx, fmeu1p2_map[i].idx, fmeu1p2_map[i].val);

	ctx->decim_ratio = 36;

	/* Load the Channel Filter Coefficients पूर्णांकo channel filter bank #2 */
	max2175_set_filter_coeffs(ctx, MAX2175_CH_MSEL, 0, ch_coeff_fmeu);
	max2175_set_filter_coeffs(ctx, MAX2175_EQ_MSEL, 0,
				  eq_coeff_fmeu1_ra02_m6db);
पूर्ण

अटल व्योम max2175_load_dab_1p2(काष्ठा max2175 *ctx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dab12_map); i++)
		max2175_ग_लिखो(ctx, dab12_map[i].idx, dab12_map[i].val);

	ctx->decim_ratio = 1;

	/* Load the Channel Filter Coefficients पूर्णांकo channel filter bank #2 */
	max2175_set_filter_coeffs(ctx, MAX2175_CH_MSEL, 2, ch_coeff_dab1);
पूर्ण

अटल व्योम max2175_load_fmna_1p0(काष्ठा max2175 *ctx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fmna1p0_map); i++)
		max2175_ग_लिखो(ctx, fmna1p0_map[i].idx, fmna1p0_map[i].val);
पूर्ण

अटल व्योम max2175_load_fmna_2p0(काष्ठा max2175 *ctx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fmna2p0_map); i++)
		max2175_ग_लिखो(ctx, fmna2p0_map[i].idx, fmna2p0_map[i].val);
पूर्ण

अटल व्योम max2175_set_bbfilter(काष्ठा max2175 *ctx)
अणु
	अगर (MAX2175_IS_BAND_AM(ctx)) अणु
		max2175_ग_लिखो_bits(ctx, 12, 3, 0, ctx->rom_bbf_bw_am);
		mxm_dbg(ctx, "set_bbfilter AM: rom %d\n", ctx->rom_bbf_bw_am);
	पूर्ण अन्यथा अगर (MAX2175_IS_DAB_MODE(ctx)) अणु
		max2175_ग_लिखो_bits(ctx, 12, 3, 0, ctx->rom_bbf_bw_dab);
		mxm_dbg(ctx, "set_bbfilter DAB: rom %d\n", ctx->rom_bbf_bw_dab);
	पूर्ण अन्यथा अणु
		max2175_ग_लिखो_bits(ctx, 12, 3, 0, ctx->rom_bbf_bw_fm);
		mxm_dbg(ctx, "set_bbfilter FM: rom %d\n", ctx->rom_bbf_bw_fm);
	पूर्ण
पूर्ण

अटल पूर्णांक max2175_set_csm_mode(काष्ठा max2175 *ctx,
			  क्रमागत max2175_csm_mode new_mode)
अणु
	पूर्णांक ret = max2175_poll_csm_पढ़ोy(ctx);

	अगर (ret)
		वापस ret;

	max2175_ग_लिखो_bits(ctx, 0, 2, 0, new_mode);
	mxm_dbg(ctx, "set csm new mode %d\n", new_mode);

	/* Wait क्रम a fixed settle करोwn समय depending on new mode */
	चयन (new_mode) अणु
	हाल MAX2175_PRESET_TUNE:
		usleep_range(51100, 51500);	/* 51.1ms */
		अवरोध;
	/*
	 * Other mode चयनes need dअगरferent sleep values depending on band &
	 * mode
	 */
	शेष:
		अवरोध;
	पूर्ण

	वापस max2175_poll_csm_पढ़ोy(ctx);
पूर्ण

अटल पूर्णांक max2175_csm_action(काष्ठा max2175 *ctx,
			      क्रमागत max2175_csm_mode action)
अणु
	पूर्णांक ret;

	mxm_dbg(ctx, "csm_action: %d\n", action);

	/* Other actions can be added in future when needed */
	ret = max2175_set_csm_mode(ctx, MAX2175_LOAD_TO_BUFFER);
	अगर (ret)
		वापस ret;

	वापस max2175_set_csm_mode(ctx, MAX2175_PRESET_TUNE);
पूर्ण

अटल पूर्णांक max2175_set_lo_freq(काष्ठा max2175 *ctx, u32 lo_freq)
अणु
	u8 lo_mult, loband_bits = 0, vcoभाग_bits = 0;
	u32 पूर्णांक_desired, frac_desired;
	क्रमागत max2175_band band;
	पूर्णांक ret;

	band = max2175_पढ़ो_bits(ctx, 5, 1, 0);
	चयन (band) अणु
	हाल MAX2175_BAND_AM:
		lo_mult = 16;
		अवरोध;
	हाल MAX2175_BAND_FM:
		अगर (lo_freq <= 74700000) अणु
			lo_mult = 16;
		पूर्ण अन्यथा अगर (lo_freq > 74700000 && lo_freq <= 110000000) अणु
			loband_bits = 1;
			lo_mult = 8;
		पूर्ण अन्यथा अणु
			loband_bits = 1;
			vcoभाग_bits = 3;
			lo_mult = 8;
		पूर्ण
		अवरोध;
	हाल MAX2175_BAND_VHF:
		अगर (lo_freq <= 210000000)
			vcoभाग_bits = 2;
		अन्यथा
			vcoभाग_bits = 1;

		loband_bits = 2;
		lo_mult = 4;
		अवरोध;
	शेष:
		loband_bits = 3;
		vcoभाग_bits = 2;
		lo_mult = 2;
		अवरोध;
	पूर्ण

	अगर (band == MAX2175_BAND_L)
		lo_freq /= lo_mult;
	अन्यथा
		lo_freq *= lo_mult;

	पूर्णांक_desired = lo_freq / ctx->xtal_freq;
	frac_desired = भाग64_ul((u64)(lo_freq % ctx->xtal_freq) << 20,
				ctx->xtal_freq);

	/* Check CSM is not busy */
	ret = max2175_poll_csm_पढ़ोy(ctx);
	अगर (ret)
		वापस ret;

	mxm_dbg(ctx, "lo_mult %u int %u  frac %u\n",
		lo_mult, पूर्णांक_desired, frac_desired);

	/* Write the calculated values to the appropriate रेजिस्टरs */
	max2175_ग_लिखो(ctx, 1, पूर्णांक_desired);
	max2175_ग_लिखो_bits(ctx, 2, 3, 0, (frac_desired >> 16) & 0xf);
	max2175_ग_लिखो(ctx, 3, frac_desired >> 8);
	max2175_ग_लिखो(ctx, 4, frac_desired);
	max2175_ग_लिखो_bits(ctx, 5, 3, 2, loband_bits);
	max2175_ग_लिखो_bits(ctx, 6, 7, 6, vcoभाग_bits);

	वापस ret;
पूर्ण

/*
 * Helper similar to DIV_ROUND_CLOSEST but an अंतरभूत function that accepts s64
 * भागidend and s32 भागisor
 */
अटल अंतरभूत s64 max2175_round_बंदst(s64 भागidend, s32 भागisor)
अणु
	अगर ((भागidend > 0 && भागisor > 0) || (भागidend < 0 && भागisor < 0))
		वापस भाग_s64(भागidend + भागisor / 2, भागisor);

	वापस भाग_s64(भागidend - भागisor / 2, भागisor);
पूर्ण

अटल पूर्णांक max2175_set_nco_freq(काष्ठा max2175 *ctx, s32 nco_freq)
अणु
	s32 घड़ी_rate = ctx->xtal_freq / ctx->decim_ratio;
	u32 nco_reg, असल_nco_freq = असल(nco_freq);
	s64 nco_val_desired;
	पूर्णांक ret;

	अगर (असल_nco_freq < घड़ी_rate / 2) अणु
		nco_val_desired = 2 * nco_freq;
	पूर्ण अन्यथा अणु
		nco_val_desired = 2LL * (घड़ी_rate - असल_nco_freq);
		अगर (nco_freq < 0)
			nco_val_desired = -nco_val_desired;
	पूर्ण

	nco_reg = max2175_round_बंदst(nco_val_desired << 20, घड़ी_rate);

	अगर (nco_freq < 0)
		nco_reg += 0x200000;

	/* Check CSM is not busy */
	ret = max2175_poll_csm_पढ़ोy(ctx);
	अगर (ret)
		वापस ret;

	mxm_dbg(ctx, "freq %d desired %lld reg %u\n",
		nco_freq, nco_val_desired, nco_reg);

	/* Write the calculated values to the appropriate रेजिस्टरs */
	max2175_ग_लिखो_bits(ctx, 7, 4, 0, (nco_reg >> 16) & 0x1f);
	max2175_ग_लिखो(ctx, 8, nco_reg >> 8);
	max2175_ग_लिखो(ctx, 9, nco_reg);

	वापस ret;
पूर्ण

अटल पूर्णांक max2175_set_rf_freq_non_am_bands(काष्ठा max2175 *ctx, u64 freq,
					    u32 lo_pos)
अणु
	s64 adj_freq, low_अगर_freq;
	पूर्णांक ret;

	mxm_dbg(ctx, "rf_freq: non AM bands\n");

	अगर (MAX2175_IS_FM_MODE(ctx))
		low_अगर_freq = 128000;
	अन्यथा अगर (MAX2175_IS_FMHD_MODE(ctx))
		low_अगर_freq = 228000;
	अन्यथा
		वापस max2175_set_lo_freq(ctx, freq);

	अगर (MAX2175_IS_BAND_VHF(ctx) == (lo_pos == MAX2175_LO_ABOVE_DESIRED))
		adj_freq = freq + low_अगर_freq;
	अन्यथा
		adj_freq = freq - low_अगर_freq;

	ret = max2175_set_lo_freq(ctx, adj_freq);
	अगर (ret)
		वापस ret;

	वापस max2175_set_nco_freq(ctx, -low_अगर_freq);
पूर्ण

अटल पूर्णांक max2175_set_rf_freq(काष्ठा max2175 *ctx, u64 freq, u32 lo_pos)
अणु
	पूर्णांक ret;

	अगर (MAX2175_IS_BAND_AM(ctx))
		ret = max2175_set_nco_freq(ctx, freq);
	अन्यथा
		ret = max2175_set_rf_freq_non_am_bands(ctx, freq, lo_pos);

	mxm_dbg(ctx, "set_rf_freq: ret %d freq %llu\n", ret, freq);

	वापस ret;
पूर्ण

अटल पूर्णांक max2175_tune_rf_freq(काष्ठा max2175 *ctx, u64 freq, u32 hsls)
अणु
	पूर्णांक ret;

	ret = max2175_set_rf_freq(ctx, freq, hsls);
	अगर (ret)
		वापस ret;

	ret = max2175_csm_action(ctx, MAX2175_BUFFER_PLUS_PRESET_TUNE);
	अगर (ret)
		वापस ret;

	mxm_dbg(ctx, "tune_rf_freq: old %u new %llu\n", ctx->freq, freq);
	ctx->freq = freq;

	वापस ret;
पूर्ण

अटल व्योम max2175_set_hsls(काष्ठा max2175 *ctx, u32 lo_pos)
अणु
	mxm_dbg(ctx, "set_hsls: lo_pos %u\n", lo_pos);

	अगर ((lo_pos == MAX2175_LO_BELOW_DESIRED) == MAX2175_IS_BAND_VHF(ctx))
		max2175_ग_लिखो_bit(ctx, 5, 4, 1);
	अन्यथा
		max2175_ग_लिखो_bit(ctx, 5, 4, 0);
पूर्ण

अटल व्योम max2175_set_eu_rx_mode(काष्ठा max2175 *ctx, u32 rx_mode)
अणु
	चयन (rx_mode) अणु
	हाल MAX2175_EU_FM_1_2:
		max2175_load_fmeu_1p2(ctx);
		अवरोध;

	हाल MAX2175_DAB_1_2:
		max2175_load_dab_1p2(ctx);
		अवरोध;
	पूर्ण
	/* Master is the शेष setting */
	अगर (!ctx->master)
		max2175_ग_लिखो_bit(ctx, 30, 7, 1);
पूर्ण

अटल व्योम max2175_set_na_rx_mode(काष्ठा max2175 *ctx, u32 rx_mode)
अणु
	चयन (rx_mode) अणु
	हाल MAX2175_NA_FM_1_0:
		max2175_load_fmna_1p0(ctx);
		अवरोध;
	हाल MAX2175_NA_FM_2_0:
		max2175_load_fmna_2p0(ctx);
		अवरोध;
	पूर्ण
	/* Master is the शेष setting */
	अगर (!ctx->master)
		max2175_ग_लिखो_bit(ctx, 30, 7, 1);

	ctx->decim_ratio = 27;

	/* Load the Channel Filter Coefficients पूर्णांकo channel filter bank #2 */
	max2175_set_filter_coeffs(ctx, MAX2175_CH_MSEL, 0, ch_coeff_fmna);
	max2175_set_filter_coeffs(ctx, MAX2175_EQ_MSEL, 0,
				  eq_coeff_fmna1_ra02_m6db);
पूर्ण

अटल पूर्णांक max2175_set_rx_mode(काष्ठा max2175 *ctx, u32 rx_mode)
अणु
	mxm_dbg(ctx, "set_rx_mode: %u am_hiz %u\n", rx_mode, ctx->am_hiz);
	अगर (ctx->xtal_freq == MAX2175_EU_XTAL_FREQ)
		max2175_set_eu_rx_mode(ctx, rx_mode);
	अन्यथा
		max2175_set_na_rx_mode(ctx, rx_mode);

	अगर (ctx->am_hiz) अणु
		mxm_dbg(ctx, "setting AM HiZ related config\n");
		max2175_ग_लिखो_bit(ctx, 50, 5, 1);
		max2175_ग_लिखो_bit(ctx, 90, 7, 1);
		max2175_ग_लिखो_bits(ctx, 73, 1, 0, 2);
		max2175_ग_लिखो_bits(ctx, 80, 5, 0, 33);
	पूर्ण

	/* Load BB filter trim values saved in ROM */
	max2175_set_bbfilter(ctx);

	/* Set HSLS */
	max2175_set_hsls(ctx, ctx->hsls->cur.val);

	/* Use i2s enable settings */
	max2175_i2s_enable(ctx, ctx->i2s_en->cur.val);

	ctx->mode_resolved = true;

	वापस 0;
पूर्ण

अटल पूर्णांक max2175_rx_mode_from_freq(काष्ठा max2175 *ctx, u32 freq, u32 *mode)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक band = max2175_band_from_freq(freq);

	/* Pick the first match always */
	क्रम (i = 0; i <= ctx->rx_mode->maximum; i++) अणु
		अगर (ctx->rx_modes[i].band == band) अणु
			*mode = i;
			mxm_dbg(ctx, "rx_mode_from_freq: freq %u mode %d\n",
				freq, *mode);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल bool max2175_freq_rx_mode_valid(काष्ठा max2175 *ctx,
					 u32 mode, u32 freq)
अणु
	पूर्णांक band = max2175_band_from_freq(freq);

	वापस (ctx->rx_modes[mode].band == band);
पूर्ण

अटल व्योम max2175_load_adc_presets(काष्ठा max2175 *ctx)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(adc_presets); i++)
		क्रम (j = 0; j < ARRAY_SIZE(adc_presets[0]); j++)
			max2175_ग_लिखो(ctx, 146 + j + i * 55, adc_presets[i][j]);
पूर्ण

अटल पूर्णांक max2175_init_घातer_manager(काष्ठा max2175 *ctx)
अणु
	पूर्णांक ret;

	/* Execute on-chip घातer-up/calibration */
	max2175_ग_लिखो_bit(ctx, 99, 2, 0);
	usleep_range(1000, 1500);
	max2175_ग_लिखो_bit(ctx, 99, 2, 1);

	/* Wait क्रम the घातer manager to finish. */
	ret = max2175_poll_समयout(ctx, 69, 7, 7, 1, 50000);
	अगर (ret)
		mxm_err(ctx, "init pm failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक max2175_recalibrate_adc(काष्ठा max2175 *ctx)
अणु
	पूर्णांक ret;

	/* ADC Re-calibration */
	max2175_ग_लिखो(ctx, 150, 0xff);
	max2175_ग_लिखो(ctx, 205, 0xff);
	max2175_ग_लिखो(ctx, 147, 0x20);
	max2175_ग_लिखो(ctx, 147, 0x00);
	max2175_ग_लिखो(ctx, 202, 0x20);
	max2175_ग_लिखो(ctx, 202, 0x00);

	ret = max2175_poll_समयout(ctx, 69, 4, 3, 3, 50000);
	अगर (ret)
		mxm_err(ctx, "adc recalibration failed\n");

	वापस ret;
पूर्ण

अटल u8 max2175_पढ़ो_rom(काष्ठा max2175 *ctx, u8 row)
अणु
	u8 data = 0;

	max2175_ग_लिखो_bit(ctx, 56, 4, 0);
	max2175_ग_लिखो_bits(ctx, 56, 3, 0, row);

	usleep_range(2000, 2500);
	max2175_पढ़ो(ctx, 58, &data);

	max2175_ग_लिखो_bits(ctx, 56, 3, 0, 0);

	mxm_dbg(ctx, "read_rom: row %d data 0x%02x\n", row, data);

	वापस data;
पूर्ण

अटल व्योम max2175_load_from_rom(काष्ठा max2175 *ctx)
अणु
	u8 data = 0;

	data = max2175_पढ़ो_rom(ctx, 0);
	ctx->rom_bbf_bw_am = data & 0x0f;
	max2175_ग_लिखो_bits(ctx, 81, 3, 0, data >> 4);

	data = max2175_पढ़ो_rom(ctx, 1);
	ctx->rom_bbf_bw_fm = data & 0x0f;
	ctx->rom_bbf_bw_dab = data >> 4;

	data = max2175_पढ़ो_rom(ctx, 2);
	max2175_ग_लिखो_bits(ctx, 82, 4, 0, data & 0x1f);
	max2175_ग_लिखो_bits(ctx, 82, 7, 5, data >> 5);

	data = max2175_पढ़ो_rom(ctx, 3);
	अगर (ctx->am_hiz) अणु
		data &= 0x0f;
		data |= (max2175_पढ़ो_rom(ctx, 7) & 0x40) >> 2;
		अगर (!data)
			data |= 2;
	पूर्ण अन्यथा अणु
		data = (data & 0xf0) >> 4;
		data |= (max2175_पढ़ो_rom(ctx, 7) & 0x80) >> 3;
		अगर (!data)
			data |= 30;
	पूर्ण
	max2175_ग_लिखो_bits(ctx, 80, 5, 0, data + 31);

	data = max2175_पढ़ो_rom(ctx, 6);
	max2175_ग_लिखो_bits(ctx, 81, 7, 6, data >> 6);
पूर्ण

अटल व्योम max2175_load_full_fm_eu_1p0(काष्ठा max2175 *ctx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(full_fm_eu_1p0); i++)
		max2175_ग_लिखो(ctx, i + 1, full_fm_eu_1p0[i]);

	usleep_range(5000, 5500);
	ctx->decim_ratio = 36;
पूर्ण

अटल व्योम max2175_load_full_fm_na_1p0(काष्ठा max2175 *ctx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(full_fm_na_1p0); i++)
		max2175_ग_लिखो(ctx, i + 1, full_fm_na_1p0[i]);

	usleep_range(5000, 5500);
	ctx->decim_ratio = 27;
पूर्ण

अटल पूर्णांक max2175_core_init(काष्ठा max2175 *ctx, u32 refout_bits)
अणु
	पूर्णांक ret;

	/* MAX2175 uses 36.864MHz घड़ी क्रम EU & 40.154MHz क्रम NA region */
	अगर (ctx->xtal_freq == MAX2175_EU_XTAL_FREQ)
		max2175_load_full_fm_eu_1p0(ctx);
	अन्यथा
		max2175_load_full_fm_na_1p0(ctx);

	/* The शेष settings assume master */
	अगर (!ctx->master)
		max2175_ग_लिखो_bit(ctx, 30, 7, 1);

	mxm_dbg(ctx, "refout_bits %u\n", refout_bits);

	/* Set REFOUT */
	max2175_ग_लिखो_bits(ctx, 56, 7, 5, refout_bits);

	/* ADC Reset */
	max2175_ग_लिखो_bit(ctx, 99, 1, 0);
	usleep_range(1000, 1500);
	max2175_ग_लिखो_bit(ctx, 99, 1, 1);

	/* Load ADC preset values */
	max2175_load_adc_presets(ctx);

	/* Initialize the घातer management state machine */
	ret = max2175_init_घातer_manager(ctx);
	अगर (ret)
		वापस ret;

	/* Recalibrate ADC */
	ret = max2175_recalibrate_adc(ctx);
	अगर (ret)
		वापस ret;

	/* Load ROM values to appropriate रेजिस्टरs */
	max2175_load_from_rom(ctx);

	अगर (ctx->xtal_freq == MAX2175_EU_XTAL_FREQ) अणु
		/* Load FIR coefficients पूर्णांकo bank 0 */
		max2175_set_filter_coeffs(ctx, MAX2175_CH_MSEL, 0,
					  ch_coeff_fmeu);
		max2175_set_filter_coeffs(ctx, MAX2175_EQ_MSEL, 0,
					  eq_coeff_fmeu1_ra02_m6db);
	पूर्ण अन्यथा अणु
		/* Load FIR coefficients पूर्णांकo bank 0 */
		max2175_set_filter_coeffs(ctx, MAX2175_CH_MSEL, 0,
					  ch_coeff_fmna);
		max2175_set_filter_coeffs(ctx, MAX2175_EQ_MSEL, 0,
					  eq_coeff_fmna1_ra02_m6db);
	पूर्ण
	mxm_dbg(ctx, "core initialized\n");

	वापस 0;
पूर्ण

अटल व्योम max2175_s_ctrl_rx_mode(काष्ठा max2175 *ctx, u32 rx_mode)
अणु
	/* Load mode. Range check alपढ़ोy करोne */
	max2175_set_rx_mode(ctx, rx_mode);

	mxm_dbg(ctx, "s_ctrl_rx_mode: %u curr freq %u\n", rx_mode, ctx->freq);

	/* Check अगर current freq valid क्रम mode & update */
	अगर (max2175_freq_rx_mode_valid(ctx, rx_mode, ctx->freq))
		max2175_tune_rf_freq(ctx, ctx->freq, ctx->hsls->cur.val);
	अन्यथा
		/* Use शेष freq of mode अगर current freq is not valid */
		max2175_tune_rf_freq(ctx, ctx->rx_modes[rx_mode].freq,
				     ctx->hsls->cur.val);
पूर्ण

अटल पूर्णांक max2175_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा max2175 *ctx = max2175_from_ctrl_hdl(ctrl->handler);

	mxm_dbg(ctx, "s_ctrl: id 0x%x, val %u\n", ctrl->id, ctrl->val);
	चयन (ctrl->id) अणु
	हाल V4L2_CID_MAX2175_I2S_ENABLE:
		max2175_i2s_enable(ctx, ctrl->val);
		अवरोध;
	हाल V4L2_CID_MAX2175_HSLS:
		max2175_set_hsls(ctx, ctrl->val);
		अवरोध;
	हाल V4L2_CID_MAX2175_RX_MODE:
		max2175_s_ctrl_rx_mode(ctx, ctrl->val);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 max2175_get_lna_gain(काष्ठा max2175 *ctx)
अणु
	क्रमागत max2175_band band = max2175_पढ़ो_bits(ctx, 5, 1, 0);

	चयन (band) अणु
	हाल MAX2175_BAND_AM:
		वापस max2175_पढ़ो_bits(ctx, 51, 3, 0);
	हाल MAX2175_BAND_FM:
		वापस max2175_पढ़ो_bits(ctx, 50, 3, 0);
	हाल MAX2175_BAND_VHF:
		वापस max2175_पढ़ो_bits(ctx, 52, 5, 0);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक max2175_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा max2175 *ctx = max2175_from_ctrl_hdl(ctrl->handler);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_RF_TUNER_LNA_GAIN:
		ctrl->val = max2175_get_lna_gain(ctx);
		अवरोध;
	हाल V4L2_CID_RF_TUNER_IF_GAIN:
		ctrl->val = max2175_पढ़ो_bits(ctx, 49, 4, 0);
		अवरोध;
	हाल V4L2_CID_RF_TUNER_PLL_LOCK:
		ctrl->val = (max2175_पढ़ो_bits(ctx, 60, 7, 6) == 3);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण;

अटल पूर्णांक max2175_set_freq_and_mode(काष्ठा max2175 *ctx, u32 freq)
अणु
	u32 rx_mode;
	पूर्णांक ret;

	/* Get band from frequency */
	ret = max2175_rx_mode_from_freq(ctx, freq, &rx_mode);
	अगर (ret)
		वापस ret;

	mxm_dbg(ctx, "set_freq_and_mode: freq %u rx_mode %d\n", freq, rx_mode);

	/* Load mode */
	max2175_set_rx_mode(ctx, rx_mode);
	ctx->rx_mode->cur.val = rx_mode;

	/* Tune to the new freq given */
	वापस max2175_tune_rf_freq(ctx, freq, ctx->hsls->cur.val);
पूर्ण

अटल पूर्णांक max2175_s_frequency(काष्ठा v4l2_subdev *sd,
			       स्थिर काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा max2175 *ctx = max2175_from_sd(sd);
	u32 freq;
	पूर्णांक ret = 0;

	mxm_dbg(ctx, "s_freq: new %u curr %u, mode_resolved %d\n",
		vf->frequency, ctx->freq, ctx->mode_resolved);

	अगर (vf->tuner != 0)
		वापस -EINVAL;

	freq = clamp(vf->frequency, ctx->bands_rf->rangelow,
		     ctx->bands_rf->rangehigh);

	/* Check new freq valid क्रम rx_mode अगर alपढ़ोy resolved */
	अगर (ctx->mode_resolved &&
	    max2175_freq_rx_mode_valid(ctx, ctx->rx_mode->cur.val, freq))
		ret = max2175_tune_rf_freq(ctx, freq, ctx->hsls->cur.val);
	अन्यथा
		/* Find शेष rx_mode क्रम freq and tune to it */
		ret = max2175_set_freq_and_mode(ctx, freq);

	mxm_dbg(ctx, "s_freq: ret %d curr %u mode_resolved %d mode %u\n",
		ret, ctx->freq, ctx->mode_resolved, ctx->rx_mode->cur.val);

	वापस ret;
पूर्ण

अटल पूर्णांक max2175_g_frequency(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा max2175 *ctx = max2175_from_sd(sd);

	अगर (vf->tuner != 0)
		वापस -EINVAL;

	/* RF freq */
	vf->type = V4L2_TUNER_RF;
	vf->frequency = ctx->freq;

	वापस 0;
पूर्ण

अटल पूर्णांक max2175_क्रमागत_freq_bands(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_frequency_band *band)
अणु
	काष्ठा max2175 *ctx = max2175_from_sd(sd);

	अगर (band->tuner != 0 || band->index != 0)
		वापस -EINVAL;

	*band = *ctx->bands_rf;

	वापस 0;
पूर्ण

अटल पूर्णांक max2175_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा max2175 *ctx = max2175_from_sd(sd);

	अगर (vt->index > 0)
		वापस -EINVAL;

	strscpy(vt->name, "RF", माप(vt->name));
	vt->type = V4L2_TUNER_RF;
	vt->capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
	vt->rangelow = ctx->bands_rf->rangelow;
	vt->rangehigh = ctx->bands_rf->rangehigh;

	वापस 0;
पूर्ण

अटल पूर्णांक max2175_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	/* Check tuner index is valid */
	अगर (vt->index > 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops max2175_tuner_ops = अणु
	.s_frequency = max2175_s_frequency,
	.g_frequency = max2175_g_frequency,
	.क्रमागत_freq_bands = max2175_क्रमागत_freq_bands,
	.g_tuner = max2175_g_tuner,
	.s_tuner = max2175_s_tuner,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops max2175_ops = अणु
	.tuner = &max2175_tuner_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops max2175_ctrl_ops = अणु
	.s_ctrl = max2175_s_ctrl,
	.g_अस्थिर_ctrl = max2175_g_अस्थिर_ctrl,
पूर्ण;

/*
 * I2S output enable/disable configuration. This is a निजी control.
 * Refer to Documentation/userspace-api/media/drivers/max2175.rst क्रम more details.
 */
अटल स्थिर काष्ठा v4l2_ctrl_config max2175_i2s_en = अणु
	.ops = &max2175_ctrl_ops,
	.id = V4L2_CID_MAX2175_I2S_ENABLE,
	.name = "I2S Enable",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 1,
	.is_निजी = 1,
पूर्ण;

/*
 * HSLS value control LO freq adjacent location configuration.
 * Refer to Documentation/userspace-api/media/drivers/max2175.rst क्रम more details.
 */
अटल स्थिर काष्ठा v4l2_ctrl_config max2175_hsls = अणु
	.ops = &max2175_ctrl_ops,
	.id = V4L2_CID_MAX2175_HSLS,
	.name = "HSLS Above/Below Desired",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 1,
पूर्ण;

/*
 * Rx modes below are a set of preset configurations that decides the tuner's
 * sck and sample rate of transmission. They are separate क्रम EU & NA regions.
 * Refer to Documentation/userspace-api/media/drivers/max2175.rst क्रम more details.
 */
अटल स्थिर अक्षर * स्थिर max2175_ctrl_eu_rx_modes[] = अणु
	[MAX2175_EU_FM_1_2]	= "EU FM 1.2",
	[MAX2175_DAB_1_2]	= "DAB 1.2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर max2175_ctrl_na_rx_modes[] = अणु
	[MAX2175_NA_FM_1_0]	= "NA FM 1.0",
	[MAX2175_NA_FM_2_0]	= "NA FM 2.0",
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config max2175_eu_rx_mode = अणु
	.ops = &max2175_ctrl_ops,
	.id = V4L2_CID_MAX2175_RX_MODE,
	.name = "RX Mode",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = ARRAY_SIZE(max2175_ctrl_eu_rx_modes) - 1,
	.def = 0,
	.qmenu = max2175_ctrl_eu_rx_modes,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config max2175_na_rx_mode = अणु
	.ops = &max2175_ctrl_ops,
	.id = V4L2_CID_MAX2175_RX_MODE,
	.name = "RX Mode",
	.type = V4L2_CTRL_TYPE_MENU,
	.max = ARRAY_SIZE(max2175_ctrl_na_rx_modes) - 1,
	.def = 0,
	.qmenu = max2175_ctrl_na_rx_modes,
पूर्ण;

अटल पूर्णांक max2175_refout_load_to_bits(काष्ठा i2c_client *client, u32 load,
				       u32 *bits)
अणु
	अगर (load <= 40)
		*bits = load / 10;
	अन्यथा अगर (load >= 60 && load <= 70)
		*bits = load / 10 - 1;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक max2175_probe(काष्ठा i2c_client *client)
अणु
	bool master = true, am_hiz = false;
	u32 refout_load, refout_bits = 0;	/* REFOUT disabled */
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा device_node *np;
	काष्ठा v4l2_subdev *sd;
	काष्ठा regmap *regmap;
	काष्ठा max2175 *ctx;
	काष्ठा clk *clk;
	पूर्णांक ret;

	/* Parse DT properties */
	np = of_parse_phandle(client->dev.of_node, "maxim,master", 0);
	अगर (np) अणु
		master = false;			/* Slave tuner */
		of_node_put(np);
	पूर्ण

	fwnode = of_fwnode_handle(client->dev.of_node);
	अगर (fwnode_property_present(fwnode, "maxim,am-hiz-filter"))
		am_hiz = true;

	अगर (!fwnode_property_पढ़ो_u32(fwnode, "maxim,refout-load",
				      &refout_load)) अणु
		ret = max2175_refout_load_to_bits(client, refout_load,
						  &refout_bits);
		अगर (ret) अणु
			dev_err(&client->dev, "invalid refout_load %u\n",
				refout_load);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	clk = devm_clk_get(&client->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		dev_err(&client->dev, "cannot get clock %d\n", ret);
		वापस ret;
	पूर्ण

	regmap = devm_regmap_init_i2c(client, &max2175_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&client->dev, "regmap init failed %d\n", ret);
		वापस -ENODEV;
	पूर्ण

	/* Alloc tuner context */
	ctx = devm_kzalloc(&client->dev, माप(*ctx), GFP_KERNEL);
	अगर (ctx == शून्य)
		वापस -ENOMEM;

	sd = &ctx->sd;
	ctx->master = master;
	ctx->am_hiz = am_hiz;
	ctx->mode_resolved = false;
	ctx->regmap = regmap;
	ctx->xtal_freq = clk_get_rate(clk);
	dev_info(&client->dev, "xtal freq %luHz\n", ctx->xtal_freq);

	v4l2_i2c_subdev_init(sd, client, &max2175_ops);
	ctx->client = client;

	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	/* Controls */
	hdl = &ctx->ctrl_hdl;
	ret = v4l2_ctrl_handler_init(hdl, 7);
	अगर (ret)
		वापस ret;

	ctx->lna_gain = v4l2_ctrl_new_std(hdl, &max2175_ctrl_ops,
					  V4L2_CID_RF_TUNER_LNA_GAIN,
					  0, 63, 1, 0);
	ctx->lna_gain->flags |= (V4L2_CTRL_FLAG_VOLATILE |
				 V4L2_CTRL_FLAG_READ_ONLY);
	ctx->अगर_gain = v4l2_ctrl_new_std(hdl, &max2175_ctrl_ops,
					 V4L2_CID_RF_TUNER_IF_GAIN,
					 0, 31, 1, 0);
	ctx->अगर_gain->flags |= (V4L2_CTRL_FLAG_VOLATILE |
				V4L2_CTRL_FLAG_READ_ONLY);
	ctx->pll_lock = v4l2_ctrl_new_std(hdl, &max2175_ctrl_ops,
					  V4L2_CID_RF_TUNER_PLL_LOCK,
					  0, 1, 1, 0);
	ctx->pll_lock->flags |= (V4L2_CTRL_FLAG_VOLATILE |
				 V4L2_CTRL_FLAG_READ_ONLY);
	ctx->i2s_en = v4l2_ctrl_new_custom(hdl, &max2175_i2s_en, शून्य);
	ctx->hsls = v4l2_ctrl_new_custom(hdl, &max2175_hsls, शून्य);

	अगर (ctx->xtal_freq == MAX2175_EU_XTAL_FREQ) अणु
		ctx->rx_mode = v4l2_ctrl_new_custom(hdl,
						    &max2175_eu_rx_mode, शून्य);
		ctx->rx_modes = eu_rx_modes;
		ctx->bands_rf = &eu_bands_rf;
	पूर्ण अन्यथा अणु
		ctx->rx_mode = v4l2_ctrl_new_custom(hdl,
						    &max2175_na_rx_mode, शून्य);
		ctx->rx_modes = na_rx_modes;
		ctx->bands_rf = &na_bands_rf;
	पूर्ण
	ctx->sd.ctrl_handler = &ctx->ctrl_hdl;

	/* Set the शेषs */
	ctx->freq = ctx->bands_rf->rangelow;

	/* Register subdev */
	ret = v4l2_async_रेजिस्टर_subdev(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "register subdev failed\n");
		जाओ err_reg;
	पूर्ण

	/* Initialize device */
	ret = max2175_core_init(ctx, refout_bits);
	अगर (ret)
		जाओ err_init;

	ret = v4l2_ctrl_handler_setup(hdl);
	अगर (ret)
		जाओ err_init;

	वापस 0;

err_init:
	v4l2_async_unरेजिस्टर_subdev(sd);
err_reg:
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_hdl);

	वापस ret;
पूर्ण

अटल पूर्णांक max2175_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा max2175 *ctx = max2175_from_sd(sd);

	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_hdl);
	v4l2_async_unरेजिस्टर_subdev(sd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max2175_id[] = अणु
	अणु DRIVER_NAME, 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max2175_id);

अटल स्थिर काष्ठा of_device_id max2175_of_ids[] = अणु
	अणु .compatible = "maxim,max2175", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max2175_of_ids);

अटल काष्ठा i2c_driver max2175_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
		.of_match_table = max2175_of_ids,
	पूर्ण,
	.probe_new	= max2175_probe,
	.हटाओ		= max2175_हटाओ,
	.id_table	= max2175_id,
पूर्ण;

module_i2c_driver(max2175_driver);

MODULE_DESCRIPTION("Maxim MAX2175 RF to Bits tuner driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ramesh Shanmugasundaram <ramesh.shanmugasundaram@bp.renesas.com>");
