<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * cs35l32.h -- CS35L32 ALSA SoC audio driver
 *
 * Copyright 2014 CirrusLogic, Inc.
 *
 * Author: Brian Austin <brian.austin@cirrus.com>
 */

#अगर_अघोषित __CS35L32_H__
#घोषणा __CS35L32_H__

काष्ठा cs35l32_platक्रमm_data अणु
	/* Low Battery Threshold */
	अचिन्हित पूर्णांक batt_thresh;
	/* Low Battery Recovery */
	अचिन्हित पूर्णांक batt_recov;
	/* LED Current Management*/
	अचिन्हित पूर्णांक led_mng;
	/* Audio Gain w/ LED */
	अचिन्हित पूर्णांक audiogain_mng;
	/* Boost Management */
	अचिन्हित पूर्णांक boost_mng;
	/* Data CFG क्रम DUAL device */
	अचिन्हित पूर्णांक sकरोut_datacfg;
	/* SDOUT Sharing */
	अचिन्हित पूर्णांक sकरोut_share;
पूर्ण;

#घोषणा CS35L32_CHIP_ID		0x00035A32
#घोषणा CS35L32_DEVID_AB	0x01	/* Device ID A & B [RO] */
#घोषणा CS35L32_DEVID_CD	0x02    /* Device ID C & D [RO] */
#घोषणा CS35L32_DEVID_E		0x03    /* Device ID E [RO] */
#घोषणा CS35L32_FAB_ID		0x04	/* Fab ID [RO] */
#घोषणा CS35L32_REV_ID		0x05	/* Revision ID [RO] */
#घोषणा CS35L32_PWRCTL1		0x06    /* Power Ctl 1 */
#घोषणा CS35L32_PWRCTL2		0x07    /* Power Ctl 2 */
#घोषणा CS35L32_CLK_CTL		0x08	/* Clock Ctl */
#घोषणा CS35L32_BATT_THRESHOLD	0x09	/* Low Battery Threshold */
#घोषणा CS35L32_VMON		0x0A	/* Voltage Monitor [RO] */
#घोषणा CS35L32_BST_CPCP_CTL	0x0B	/* Conv Peak Curr Protection CTL */
#घोषणा CS35L32_IMON_SCALING	0x0C	/* IMON Scaling */
#घोषणा CS35L32_AUDIO_LED_MNGR	0x0D	/* Audio/LED Pwr Manager */
#घोषणा CS35L32_ADSP_CTL	0x0F	/* Serial Port Control */
#घोषणा CS35L32_CLASSD_CTL	0x10	/* Class D Amp CTL */
#घोषणा CS35L32_PROTECT_CTL	0x11	/* Protection Release CTL */
#घोषणा CS35L32_INT_MASK_1	0x12	/* Interrupt Mask 1 */
#घोषणा CS35L32_INT_MASK_2	0x13	/* Interrupt Mask 2 */
#घोषणा CS35L32_INT_MASK_3	0x14	/* Interrupt Mask 3 */
#घोषणा CS35L32_INT_STATUS_1	0x15	/* Interrupt Status 1 [RO] */
#घोषणा CS35L32_INT_STATUS_2	0x16	/* Interrupt Status 2 [RO] */
#घोषणा CS35L32_INT_STATUS_3	0x17	/* Interrupt Status 3 [RO] */
#घोषणा CS35L32_LED_STATUS	0x18	/* LED Lighting Status [RO] */
#घोषणा CS35L32_FLASH_MODE	0x19	/* LED Flash Mode Current */
#घोषणा CS35L32_MOVIE_MODE	0x1A	/* LED Movie Mode Current */
#घोषणा CS35L32_FLASH_TIMER	0x1B	/* LED Flash Timer */
#घोषणा CS35L32_FLASH_INHIBIT	0x1C	/* LED Flash Inhibit Current */
#घोषणा CS35L32_MAX_REGISTER	0x1C

#घोषणा CS35L32_MCLK_DIV2	0x01
#घोषणा CS35L32_MCLK_RATIO	0x01
#घोषणा CS35L32_MCLKDIS		0x80
#घोषणा CS35L32_PDN_ALL		0x01
#घोषणा CS35L32_PDN_AMP		0x80
#घोषणा CS35L32_PDN_BOOST	0x04
#घोषणा CS35L32_PDN_IMON	0x40
#घोषणा CS35L32_PDN_VMON	0x80
#घोषणा CS35L32_PDN_VPMON	0x20
#घोषणा CS35L32_PDN_ADSP	0x08

#घोषणा CS35L32_MCLK_DIV2_MASK		0x40
#घोषणा CS35L32_MCLK_RATIO_MASK		0x01
#घोषणा CS35L32_MCLK_MASK		0x41
#घोषणा CS35L32_ADSP_MASTER_MASK	0x40
#घोषणा CS35L32_BOOST_MASK		0x03
#घोषणा CS35L32_GAIN_MGR_MASK		0x08
#घोषणा CS35L32_ADSP_SHARE_MASK		0x08
#घोषणा CS35L32_ADSP_DATACFG_MASK	0x30
#घोषणा CS35L32_SDOUT_3ST		0x08
#घोषणा CS35L32_BATT_REC_MASK		0x0E
#घोषणा CS35L32_BATT_THRESH_MASK	0x30

#घोषणा CS35L32_RATES (SNDRV_PCM_RATE_48000)
#घोषणा CS35L32_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S24_LE | \
			SNDRV_PCM_FMTBIT_S32_LE)


#पूर्ण_अगर
