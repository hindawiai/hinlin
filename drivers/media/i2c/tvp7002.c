<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Texas Instruments Triple 8-/10-BIT 165-/110-MSPS Video and Graphics
 * Digitizer with Horizontal PLL रेजिस्टरs
 *
 * Copyright (C) 2009 Texas Instruments Inc
 * Author: Santiago Nunez-Corrales <santiago.nunez@ridgerun.com>
 *
 * This code is partially based upon the TVP5150 driver
 * written by Mauro Carvalho Chehab <mchehab@kernel.org>,
 * the TVP514x driver written by Vaibhav Hiremath <hvaibhav@ti.com>
 * and the TVP7002 driver in the TI LSP 2.10.00.14. Revisions by
 * Muralidharan Karicheri and Snehaprabha Narnakaje (TI).
 */
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <media/i2c/tvp7002.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fwnode.h>

#समावेश "tvp7002_reg.h"

MODULE_DESCRIPTION("TI TVP7002 Video and Graphics Digitizer driver");
MODULE_AUTHOR("Santiago Nunez-Corrales <santiago.nunez@ridgerun.com>");
MODULE_LICENSE("GPL");

/* I2C retry attempts */
#घोषणा I2C_RETRY_COUNT		(5)

/* End of रेजिस्टरs */
#घोषणा TVP7002_EOR		0x5c

/* Read ग_लिखो definition क्रम रेजिस्टरs */
#घोषणा TVP7002_READ		0
#घोषणा TVP7002_WRITE		1
#घोषणा TVP7002_RESERVED	2

/* Interlaced vs progressive mask and shअगरt */
#घोषणा TVP7002_IP_SHIFT	5
#घोषणा TVP7002_INPR_MASK	(0x01 << TVP7002_IP_SHIFT)

/* Shअगरt क्रम CPL and LPF रेजिस्टरs */
#घोषणा TVP7002_CL_SHIFT	8
#घोषणा TVP7002_CL_MASK		0x0f

/* Debug functions */
अटल bool debug;
module_param(debug, bool, 0644);
MODULE_PARM_DESC(debug, "Debug level (0-2)");

/* Structure क्रम रेजिस्टर values */
काष्ठा i2c_reg_value अणु
	u8 reg;
	u8 value;
	u8 type;
पूर्ण;

/*
 * Register शेष values (according to tvp7002 datasheet)
 * In the हाल of पढ़ो-only रेजिस्टरs, the value (0xff) is
 * never written. R/W functionality is controlled by the
 * writable bit in the रेजिस्टर काष्ठा definition.
 */
अटल स्थिर काष्ठा i2c_reg_value tvp7002_init_शेष[] = अणु
	अणु TVP7002_CHIP_REV, 0xff, TVP7002_READ पूर्ण,
	अणु TVP7002_HPLL_FDBK_DIV_MSBS, 0x67, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_FDBK_DIV_LSBS, 0x20, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_CRTL, 0xa0, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_PHASE_SEL, 0x80, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_START, 0x32, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_W, 0x20, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HSYNC_OUT_W, 0x60, TVP7002_WRITE पूर्ण,
	अणु TVP7002_B_FINE_GAIN, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_G_FINE_GAIN, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_R_FINE_GAIN, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_B_FINE_OFF_MSBS, 0x80, TVP7002_WRITE पूर्ण,
	अणु TVP7002_G_FINE_OFF_MSBS, 0x80, TVP7002_WRITE पूर्ण,
	अणु TVP7002_R_FINE_OFF_MSBS, 0x80, TVP7002_WRITE पूर्ण,
	अणु TVP7002_SYNC_CTL_1, 0x20, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_AND_CLAMP_CTL, 0x2e, TVP7002_WRITE पूर्ण,
	अणु TVP7002_SYNC_ON_G_THRS, 0x5d, TVP7002_WRITE पूर्ण,
	अणु TVP7002_SYNC_SEPARATOR_THRS, 0x47, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_PRE_COAST, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_POST_COAST, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_SYNC_DETECT_STAT, 0xff, TVP7002_READ पूर्ण,
	अणु TVP7002_OUT_FORMATTER, 0x47, TVP7002_WRITE पूर्ण,
	अणु TVP7002_MISC_CTL_1, 0x01, TVP7002_WRITE पूर्ण,
	अणु TVP7002_MISC_CTL_2, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_MISC_CTL_3, 0x01, TVP7002_WRITE पूर्ण,
	अणु TVP7002_IN_MUX_SEL_1, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_IN_MUX_SEL_2, 0x67, TVP7002_WRITE पूर्ण,
	अणु TVP7002_B_AND_G_COARSE_GAIN, 0x77, TVP7002_WRITE पूर्ण,
	अणु TVP7002_R_COARSE_GAIN, 0x07, TVP7002_WRITE पूर्ण,
	अणु TVP7002_FINE_OFF_LSBS, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_B_COARSE_OFF, 0x10, TVP7002_WRITE पूर्ण,
	अणु TVP7002_G_COARSE_OFF, 0x10, TVP7002_WRITE पूर्ण,
	अणु TVP7002_R_COARSE_OFF, 0x10, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HSOUT_OUT_START, 0x08, TVP7002_WRITE पूर्ण,
	अणु TVP7002_MISC_CTL_4, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_B_DGTL_ALC_OUT_LSBS, 0xff, TVP7002_READ पूर्ण,
	अणु TVP7002_G_DGTL_ALC_OUT_LSBS, 0xff, TVP7002_READ पूर्ण,
	अणु TVP7002_R_DGTL_ALC_OUT_LSBS, 0xff, TVP7002_READ पूर्ण,
	अणु TVP7002_AUTO_LVL_CTL_ENABLE, 0x80, TVP7002_WRITE पूर्ण,
	अणु TVP7002_DGTL_ALC_OUT_MSBS, 0xff, TVP7002_READ पूर्ण,
	अणु TVP7002_AUTO_LVL_CTL_FILTER, 0x53, TVP7002_WRITE पूर्ण,
	अणु 0x29, 0x08, TVP7002_RESERVED पूर्ण,
	अणु TVP7002_FINE_CLAMP_CTL, 0x07, TVP7002_WRITE पूर्ण,
	/* PWR_CTL is controlled only by the probe and reset functions */
	अणु TVP7002_PWR_CTL, 0x00, TVP7002_RESERVED पूर्ण,
	अणु TVP7002_ADC_SETUP, 0x50, TVP7002_WRITE पूर्ण,
	अणु TVP7002_COARSE_CLAMP_CTL, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_SOG_CLAMP, 0x80, TVP7002_WRITE पूर्ण,
	अणु TVP7002_RGB_COARSE_CLAMP_CTL, 0x8c, TVP7002_WRITE पूर्ण,
	अणु TVP7002_SOG_COARSE_CLAMP_CTL, 0x04, TVP7002_WRITE पूर्ण,
	अणु TVP7002_ALC_PLACEMENT, 0x5a, TVP7002_WRITE पूर्ण,
	अणु 0x32, 0x18, TVP7002_RESERVED पूर्ण,
	अणु 0x33, 0x60, TVP7002_RESERVED पूर्ण,
	अणु TVP7002_MVIS_STRIPPER_W, 0xff, TVP7002_RESERVED पूर्ण,
	अणु TVP7002_VSYNC_ALGN, 0x10, TVP7002_WRITE पूर्ण,
	अणु TVP7002_SYNC_BYPASS, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_L_FRAME_STAT_LSBS, 0xff, TVP7002_READ पूर्ण,
	अणु TVP7002_L_FRAME_STAT_MSBS, 0xff, TVP7002_READ पूर्ण,
	अणु TVP7002_CLK_L_STAT_LSBS, 0xff, TVP7002_READ पूर्ण,
	अणु TVP7002_CLK_L_STAT_MSBS, 0xff, TVP7002_READ पूर्ण,
	अणु TVP7002_HSYNC_W, 0xff, TVP7002_READ पूर्ण,
	अणु TVP7002_VSYNC_W, 0xff, TVP7002_READ पूर्ण,
	अणु TVP7002_L_LENGTH_TOL, 0x03, TVP7002_WRITE पूर्ण,
	अणु 0x3e, 0x60, TVP7002_RESERVED पूर्ण,
	अणु TVP7002_VIDEO_BWTH_CTL, 0x01, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_LSBS, 0x01, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_MSBS, 0x2c, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_LSBS, 0x06, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_MSBS, 0x2c, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_START_L_OFF, 0x05, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_START_L_OFF, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_DURATION, 0x1e, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_DURATION, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_FBIT_F_0_START_L_OFF, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_FBIT_F_1_START_L_OFF, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_Y_G_COEF_LSBS, 0xe3, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_Y_G_COEF_MSBS, 0x16, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_Y_B_COEF_LSBS, 0x4f, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_Y_B_COEF_MSBS, 0x02, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_Y_R_COEF_LSBS, 0xce, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_Y_R_COEF_MSBS, 0x06, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_U_G_COEF_LSBS, 0xab, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_U_G_COEF_MSBS, 0xf3, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_U_B_COEF_LSBS, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_U_B_COEF_MSBS, 0x10, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_U_R_COEF_LSBS, 0x55, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_U_R_COEF_MSBS, 0xfc, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_V_G_COEF_LSBS, 0x78, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_V_G_COEF_MSBS, 0xf1, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_V_B_COEF_LSBS, 0x88, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_V_B_COEF_MSBS, 0xfe, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_V_R_COEF_LSBS, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_YUV_V_R_COEF_MSBS, 0x10, TVP7002_WRITE पूर्ण,
	/* This संकेतs end of रेजिस्टर values */
	अणु TVP7002_EOR, 0xff, TVP7002_RESERVED पूर्ण
पूर्ण;

/* Register parameters क्रम 480P */
अटल स्थिर काष्ठा i2c_reg_value tvp7002_parms_480P[] = अणु
	अणु TVP7002_HPLL_FDBK_DIV_MSBS, 0x35, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_FDBK_DIV_LSBS, 0xa0, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_CRTL, 0x02, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_LSBS, 0x91, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_MSBS, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_LSBS, 0x0B, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_MSBS, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_START_L_OFF, 0x03, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_START_L_OFF, 0x01, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_DURATION, 0x13, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_DURATION, 0x13, TVP7002_WRITE पूर्ण,
	अणु TVP7002_ALC_PLACEMENT, 0x18, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_START, 0x06, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_W, 0x10, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_PRE_COAST, 0x03, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_POST_COAST, 0x03, TVP7002_WRITE पूर्ण,
	अणु TVP7002_EOR, 0xff, TVP7002_RESERVED पूर्ण
पूर्ण;

/* Register parameters क्रम 576P */
अटल स्थिर काष्ठा i2c_reg_value tvp7002_parms_576P[] = अणु
	अणु TVP7002_HPLL_FDBK_DIV_MSBS, 0x36, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_FDBK_DIV_LSBS, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_CRTL, 0x18, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_LSBS, 0x9B, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_MSBS, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_LSBS, 0x0F, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_MSBS, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_START_L_OFF, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_START_L_OFF, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_DURATION, 0x2D, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_DURATION, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_ALC_PLACEMENT, 0x18, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_START, 0x06, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_W, 0x10, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_PRE_COAST, 0x03, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_POST_COAST, 0x03, TVP7002_WRITE पूर्ण,
	अणु TVP7002_EOR, 0xff, TVP7002_RESERVED पूर्ण
पूर्ण;

/* Register parameters क्रम 1080I60 */
अटल स्थिर काष्ठा i2c_reg_value tvp7002_parms_1080I60[] = अणु
	अणु TVP7002_HPLL_FDBK_DIV_MSBS, 0x89, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_FDBK_DIV_LSBS, 0x80, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_CRTL, 0x98, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_LSBS, 0x06, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_MSBS, 0x01, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_LSBS, 0x8a, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_MSBS, 0x08, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_START_L_OFF, 0x02, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_START_L_OFF, 0x02, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_DURATION, 0x16, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_DURATION, 0x17, TVP7002_WRITE पूर्ण,
	अणु TVP7002_ALC_PLACEMENT, 0x5a, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_START, 0x32, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_W, 0x20, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_PRE_COAST, 0x01, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_POST_COAST, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_EOR, 0xff, TVP7002_RESERVED पूर्ण
पूर्ण;

/* Register parameters क्रम 1080P60 */
अटल स्थिर काष्ठा i2c_reg_value tvp7002_parms_1080P60[] = अणु
	अणु TVP7002_HPLL_FDBK_DIV_MSBS, 0x89, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_FDBK_DIV_LSBS, 0x80, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_CRTL, 0xE0, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_LSBS, 0x06, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_MSBS, 0x01, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_LSBS, 0x8a, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_MSBS, 0x08, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_START_L_OFF, 0x02, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_START_L_OFF, 0x02, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_DURATION, 0x16, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_DURATION, 0x17, TVP7002_WRITE पूर्ण,
	अणु TVP7002_ALC_PLACEMENT, 0x5a, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_START, 0x32, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_W, 0x20, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_PRE_COAST, 0x01, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_POST_COAST, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_EOR, 0xff, TVP7002_RESERVED पूर्ण
पूर्ण;

/* Register parameters क्रम 1080I50 */
अटल स्थिर काष्ठा i2c_reg_value tvp7002_parms_1080I50[] = अणु
	अणु TVP7002_HPLL_FDBK_DIV_MSBS, 0xa5, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_FDBK_DIV_LSBS, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_CRTL, 0x98, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_LSBS, 0x06, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_MSBS, 0x01, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_LSBS, 0x8a, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_MSBS, 0x08, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_START_L_OFF, 0x02, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_START_L_OFF, 0x02, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_DURATION, 0x16, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_DURATION, 0x17, TVP7002_WRITE पूर्ण,
	अणु TVP7002_ALC_PLACEMENT, 0x5a, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_START, 0x32, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_W, 0x20, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_PRE_COAST, 0x01, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_POST_COAST, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_EOR, 0xff, TVP7002_RESERVED पूर्ण
पूर्ण;

/* Register parameters क्रम 720P60 */
अटल स्थिर काष्ठा i2c_reg_value tvp7002_parms_720P60[] = अणु
	अणु TVP7002_HPLL_FDBK_DIV_MSBS, 0x67, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_FDBK_DIV_LSBS, 0x20, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_CRTL, 0xa0, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_LSBS, 0x47, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_MSBS, 0x01, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_LSBS, 0x4B, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_MSBS, 0x06, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_START_L_OFF, 0x05, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_START_L_OFF, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_DURATION, 0x2D, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_DURATION, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_ALC_PLACEMENT, 0x5a, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_START, 0x32, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_W, 0x20, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_PRE_COAST, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_POST_COAST, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_EOR, 0xff, TVP7002_RESERVED पूर्ण
पूर्ण;

/* Register parameters क्रम 720P50 */
अटल स्थिर काष्ठा i2c_reg_value tvp7002_parms_720P50[] = अणु
	अणु TVP7002_HPLL_FDBK_DIV_MSBS, 0x7b, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_FDBK_DIV_LSBS, 0xc0, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_CRTL, 0x98, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_LSBS, 0x47, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_START_PIXEL_MSBS, 0x01, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_LSBS, 0x4B, TVP7002_WRITE पूर्ण,
	अणु TVP7002_AVID_STOP_PIXEL_MSBS, 0x06, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_START_L_OFF, 0x05, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_START_L_OFF, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_0_DURATION, 0x2D, TVP7002_WRITE पूर्ण,
	अणु TVP7002_VBLK_F_1_DURATION, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_ALC_PLACEMENT, 0x5a, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_START, 0x32, TVP7002_WRITE पूर्ण,
	अणु TVP7002_CLAMP_W, 0x20, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_PRE_COAST, 0x01, TVP7002_WRITE पूर्ण,
	अणु TVP7002_HPLL_POST_COAST, 0x00, TVP7002_WRITE पूर्ण,
	अणु TVP7002_EOR, 0xff, TVP7002_RESERVED पूर्ण
पूर्ण;

/* Timings definition क्रम handling device operation */
काष्ठा tvp7002_timings_definition अणु
	काष्ठा v4l2_dv_timings timings;
	स्थिर काष्ठा i2c_reg_value *p_settings;
	क्रमागत v4l2_colorspace color_space;
	क्रमागत v4l2_field scanmode;
	u16 progressive;
	u16 lines_per_frame;
	u16 cpl_min;
	u16 cpl_max;
पूर्ण;

/* Struct list क्रम digital video timings */
अटल स्थिर काष्ठा tvp7002_timings_definition tvp7002_timings[] = अणु
	अणु
		V4L2_DV_BT_CEA_1280X720P60,
		tvp7002_parms_720P60,
		V4L2_COLORSPACE_REC709,
		V4L2_FIELD_NONE,
		1,
		0x2EE,
		135,
		153
	पूर्ण,
	अणु
		V4L2_DV_BT_CEA_1920X1080I60,
		tvp7002_parms_1080I60,
		V4L2_COLORSPACE_REC709,
		V4L2_FIELD_INTERLACED,
		0,
		0x465,
		181,
		205
	पूर्ण,
	अणु
		V4L2_DV_BT_CEA_1920X1080I50,
		tvp7002_parms_1080I50,
		V4L2_COLORSPACE_REC709,
		V4L2_FIELD_INTERLACED,
		0,
		0x465,
		217,
		245
	पूर्ण,
	अणु
		V4L2_DV_BT_CEA_1280X720P50,
		tvp7002_parms_720P50,
		V4L2_COLORSPACE_REC709,
		V4L2_FIELD_NONE,
		1,
		0x2EE,
		163,
		183
	पूर्ण,
	अणु
		V4L2_DV_BT_CEA_1920X1080P60,
		tvp7002_parms_1080P60,
		V4L2_COLORSPACE_REC709,
		V4L2_FIELD_NONE,
		1,
		0x465,
		90,
		102
	पूर्ण,
	अणु
		V4L2_DV_BT_CEA_720X480P59_94,
		tvp7002_parms_480P,
		V4L2_COLORSPACE_SMPTE170M,
		V4L2_FIELD_NONE,
		1,
		0x20D,
		0xffff,
		0xffff
	पूर्ण,
	अणु
		V4L2_DV_BT_CEA_720X576P50,
		tvp7002_parms_576P,
		V4L2_COLORSPACE_SMPTE170M,
		V4L2_FIELD_NONE,
		1,
		0x271,
		0xffff,
		0xffff
	पूर्ण
पूर्ण;

#घोषणा NUM_TIMINGS ARRAY_SIZE(tvp7002_timings)

/* Device definition */
काष्ठा tvp7002 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	स्थिर काष्ठा tvp7002_config *pdata;

	पूर्णांक ver;
	पूर्णांक streaming;

	स्थिर काष्ठा tvp7002_timings_definition *current_timings;
	काष्ठा media_pad pad;
पूर्ण;

/*
 * to_tvp7002 - Obtain device handler TVP7002
 * @sd: ptr to v4l2_subdev काष्ठा
 *
 * Returns device handler tvp7002.
 */
अटल अंतरभूत काष्ठा tvp7002 *to_tvp7002(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा tvp7002, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा tvp7002, hdl)->sd;
पूर्ण

/*
 * tvp7002_पढ़ो - Read a value from a रेजिस्टर in an TVP7002
 * @sd: ptr to v4l2_subdev काष्ठा
 * @addr: TVP7002 रेजिस्टर address
 * @dst: poपूर्णांकer to 8-bit destination
 *
 * Returns value पढ़ो अगर successful, or non-zero (-1) otherwise.
 */
अटल पूर्णांक tvp7002_पढ़ो(काष्ठा v4l2_subdev *sd, u8 addr, u8 *dst)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	पूर्णांक retry;
	पूर्णांक error;

	क्रम (retry = 0; retry < I2C_RETRY_COUNT; retry++) अणु
		error = i2c_smbus_पढ़ो_byte_data(c, addr);

		अगर (error >= 0) अणु
			*dst = (u8)error;
			वापस 0;
		पूर्ण

		msleep_पूर्णांकerruptible(10);
	पूर्ण
	v4l2_err(sd, "TVP7002 read error %d\n", error);
	वापस error;
पूर्ण

/*
 * tvp7002_पढ़ो_err() - Read a रेजिस्टर value with error code
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @reg: destination रेजिस्टर
 * @val: value to be पढ़ो
 * @err: poपूर्णांकer to error value
 *
 * Read a value in a रेजिस्टर and save error value in poपूर्णांकer.
 * Also update the रेजिस्टर table अगर successful
 */
अटल अंतरभूत व्योम tvp7002_पढ़ो_err(काष्ठा v4l2_subdev *sd, u8 reg,
							u8 *dst, पूर्णांक *err)
अणु
	अगर (!*err)
		*err = tvp7002_पढ़ो(sd, reg, dst);
पूर्ण

/*
 * tvp7002_ग_लिखो() - Write a value to a रेजिस्टर in TVP7002
 * @sd: ptr to v4l2_subdev काष्ठा
 * @addr: TVP7002 रेजिस्टर address
 * @value: value to be written to the रेजिस्टर
 *
 * Write a value to a रेजिस्टर in an TVP7002 decoder device.
 * Returns zero अगर successful, or non-zero otherwise.
 */
अटल पूर्णांक tvp7002_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 addr, u8 value)
अणु
	काष्ठा i2c_client *c;
	पूर्णांक retry;
	पूर्णांक error;

	c = v4l2_get_subdevdata(sd);

	क्रम (retry = 0; retry < I2C_RETRY_COUNT; retry++) अणु
		error = i2c_smbus_ग_लिखो_byte_data(c, addr, value);

		अगर (error >= 0)
			वापस 0;

		v4l2_warn(sd, "Write: retry ... %d\n", retry);
		msleep_पूर्णांकerruptible(10);
	पूर्ण
	v4l2_err(sd, "TVP7002 write error %d\n", error);
	वापस error;
पूर्ण

/*
 * tvp7002_ग_लिखो_err() - Write a रेजिस्टर value with error code
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @reg: destination रेजिस्टर
 * @val: value to be written
 * @err: poपूर्णांकer to error value
 *
 * Write a value in a रेजिस्टर and save error value in poपूर्णांकer.
 * Also update the रेजिस्टर table अगर successful
 */
अटल अंतरभूत व्योम tvp7002_ग_लिखो_err(काष्ठा v4l2_subdev *sd, u8 reg,
							u8 val, पूर्णांक *err)
अणु
	अगर (!*err)
		*err = tvp7002_ग_लिखो(sd, reg, val);
पूर्ण

/*
 * tvp7002_ग_लिखो_inittab() - Write initialization values
 * @sd: ptr to v4l2_subdev काष्ठा
 * @regs: ptr to i2c_reg_value काष्ठा
 *
 * Write initialization values.
 * Returns zero or -EINVAL अगर पढ़ो operation fails.
 */
अटल पूर्णांक tvp7002_ग_लिखो_inittab(काष्ठा v4l2_subdev *sd,
					स्थिर काष्ठा i2c_reg_value *regs)
अणु
	पूर्णांक error = 0;

	/* Initialize the first (defined) रेजिस्टरs */
	जबतक (TVP7002_EOR != regs->reg) अणु
		अगर (TVP7002_WRITE == regs->type)
			tvp7002_ग_लिखो_err(sd, regs->reg, regs->value, &error);
		regs++;
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक tvp7002_s_dv_timings(काष्ठा v4l2_subdev *sd,
					काष्ठा v4l2_dv_timings *dv_timings)
अणु
	काष्ठा tvp7002 *device = to_tvp7002(sd);
	स्थिर काष्ठा v4l2_bt_timings *bt = &dv_timings->bt;
	पूर्णांक i;

	अगर (dv_timings->type != V4L2_DV_BT_656_1120)
		वापस -EINVAL;
	क्रम (i = 0; i < NUM_TIMINGS; i++) अणु
		स्थिर काष्ठा v4l2_bt_timings *t = &tvp7002_timings[i].timings.bt;

		अगर (!स_भेद(bt, t, &bt->standards - &bt->width)) अणु
			device->current_timings = &tvp7002_timings[i];
			वापस tvp7002_ग_लिखो_inittab(sd, tvp7002_timings[i].p_settings);
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tvp7002_g_dv_timings(काष्ठा v4l2_subdev *sd,
					काष्ठा v4l2_dv_timings *dv_timings)
अणु
	काष्ठा tvp7002 *device = to_tvp7002(sd);

	*dv_timings = device->current_timings->timings;
	वापस 0;
पूर्ण

/*
 * tvp7002_s_ctrl() - Set a control
 * @ctrl: ptr to v4l2_ctrl काष्ठा
 *
 * Set a control in TVP7002 decoder device.
 * Returns zero when successful or -EINVAL अगर रेजिस्टर access fails.
 */
अटल पूर्णांक tvp7002_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	पूर्णांक error = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_GAIN:
		tvp7002_ग_लिखो_err(sd, TVP7002_R_FINE_GAIN, ctrl->val, &error);
		tvp7002_ग_लिखो_err(sd, TVP7002_G_FINE_GAIN, ctrl->val, &error);
		tvp7002_ग_लिखो_err(sd, TVP7002_B_FINE_GAIN, ctrl->val, &error);
		वापस error;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * tvp7002_query_dv() - query DV timings
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @index: index पूर्णांकo the tvp7002_timings array
 *
 * Returns the current DV timings detected by TVP7002. If no active input is
 * detected, वापसs -EINVAL
 */
अटल पूर्णांक tvp7002_query_dv(काष्ठा v4l2_subdev *sd, पूर्णांक *index)
अणु
	स्थिर काष्ठा tvp7002_timings_definition *timings = tvp7002_timings;
	u8 progressive;
	u32 lpfr;
	u32 cpln;
	पूर्णांक error = 0;
	u8 lpf_lsb;
	u8 lpf_msb;
	u8 cpl_lsb;
	u8 cpl_msb;

	/* Return invalid index अगर no active input is detected */
	*index = NUM_TIMINGS;

	/* Read standards from device रेजिस्टरs */
	tvp7002_पढ़ो_err(sd, TVP7002_L_FRAME_STAT_LSBS, &lpf_lsb, &error);
	tvp7002_पढ़ो_err(sd, TVP7002_L_FRAME_STAT_MSBS, &lpf_msb, &error);

	अगर (error < 0)
		वापस error;

	tvp7002_पढ़ो_err(sd, TVP7002_CLK_L_STAT_LSBS, &cpl_lsb, &error);
	tvp7002_पढ़ो_err(sd, TVP7002_CLK_L_STAT_MSBS, &cpl_msb, &error);

	अगर (error < 0)
		वापस error;

	/* Get lines per frame, घड़ीs per line and पूर्णांकerlaced/progresive */
	lpfr = lpf_lsb | ((TVP7002_CL_MASK & lpf_msb) << TVP7002_CL_SHIFT);
	cpln = cpl_lsb | ((TVP7002_CL_MASK & cpl_msb) << TVP7002_CL_SHIFT);
	progressive = (lpf_msb & TVP7002_INPR_MASK) >> TVP7002_IP_SHIFT;

	/* Do checking of video modes */
	क्रम (*index = 0; *index < NUM_TIMINGS; (*index)++, timings++)
		अगर (lpfr == timings->lines_per_frame &&
			progressive == timings->progressive) अणु
			अगर (timings->cpl_min == 0xffff)
				अवरोध;
			अगर (cpln >= timings->cpl_min && cpln <= timings->cpl_max)
				अवरोध;
		पूर्ण

	अगर (*index == NUM_TIMINGS) अणु
		v4l2_dbg(1, debug, sd, "detection failed: lpf = %x, cpl = %x\n",
								lpfr, cpln);
		वापस -ENOLINK;
	पूर्ण

	/* Update lines per frame and घड़ीs per line info */
	v4l2_dbg(1, debug, sd, "detected timings: %d\n", *index);
	वापस 0;
पूर्ण

अटल पूर्णांक tvp7002_query_dv_timings(काष्ठा v4l2_subdev *sd,
					काष्ठा v4l2_dv_timings *timings)
अणु
	पूर्णांक index;
	पूर्णांक err = tvp7002_query_dv(sd, &index);

	अगर (err)
		वापस err;
	*timings = tvp7002_timings[index].timings;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
/*
 * tvp7002_g_रेजिस्टर() - Get the value of a रेजिस्टर
 * @sd: ptr to v4l2_subdev काष्ठा
 * @reg: ptr to v4l2_dbg_रेजिस्टर काष्ठा
 *
 * Get the value of a TVP7002 decoder device रेजिस्टर.
 * Returns zero when successful, -EINVAL अगर रेजिस्टर पढ़ो fails or
 * access to I2C client fails.
 */
अटल पूर्णांक tvp7002_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
						काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	u8 val;
	पूर्णांक ret;

	ret = tvp7002_पढ़ो(sd, reg->reg & 0xff, &val);
	अगर (ret < 0)
		वापस ret;
	reg->val = val;
	reg->size = 1;
	वापस 0;
पूर्ण

/*
 * tvp7002_s_रेजिस्टर() - set a control
 * @sd: ptr to v4l2_subdev काष्ठा
 * @reg: ptr to v4l2_dbg_रेजिस्टर काष्ठा
 *
 * Get the value of a TVP7002 decoder device रेजिस्टर.
 * Returns zero when successful, -EINVAL अगर रेजिस्टर पढ़ो fails.
 */
अटल पूर्णांक tvp7002_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
						स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	वापस tvp7002_ग_लिखो(sd, reg->reg & 0xff, reg->val & 0xff);
पूर्ण
#पूर्ण_अगर

/*
 * tvp7002_s_stream() - V4L2 decoder i/f handler क्रम s_stream
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @enable: streaming enable or disable
 *
 * Sets streaming to enable or disable, अगर possible.
 */
अटल पूर्णांक tvp7002_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा tvp7002 *device = to_tvp7002(sd);
	पूर्णांक error;

	अगर (device->streaming == enable)
		वापस 0;

	/* low impedance: on, high impedance: off */
	error = tvp7002_ग_लिखो(sd, TVP7002_MISC_CTL_2, enable ? 0x00 : 0x03);
	अगर (error) अणु
		v4l2_dbg(1, debug, sd, "Fail to set streaming\n");
		वापस error;
	पूर्ण

	device->streaming = enable;
	वापस 0;
पूर्ण

/*
 * tvp7002_log_status() - Prपूर्णांक inक्रमmation about रेजिस्टर settings
 * @sd: ptr to v4l2_subdev काष्ठा
 *
 * Log रेजिस्टर values of a TVP7002 decoder device.
 * Returns zero or -EINVAL अगर पढ़ो operation fails.
 */
अटल पूर्णांक tvp7002_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tvp7002 *device = to_tvp7002(sd);
	स्थिर काष्ठा v4l2_bt_timings *bt;
	पूर्णांक detected;

	/* Find my current timings */
	tvp7002_query_dv(sd, &detected);

	bt = &device->current_timings->timings.bt;
	v4l2_info(sd, "Selected DV Timings: %ux%u\n", bt->width, bt->height);
	अगर (detected == NUM_TIMINGS) अणु
		v4l2_info(sd, "Detected DV Timings: None\n");
	पूर्ण अन्यथा अणु
		bt = &tvp7002_timings[detected].timings.bt;
		v4l2_info(sd, "Detected DV Timings: %ux%u\n",
				bt->width, bt->height);
	पूर्ण
	v4l2_info(sd, "Streaming enabled: %s\n",
					device->streaming ? "yes" : "no");

	/* Prपूर्णांक the current value of the gain control */
	v4l2_ctrl_handler_log_status(&device->hdl, sd->name);

	वापस 0;
पूर्ण

अटल पूर्णांक tvp7002_क्रमागत_dv_timings(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	अगर (timings->pad != 0)
		वापस -EINVAL;

	/* Check requested क्रमmat index is within range */
	अगर (timings->index >= NUM_TIMINGS)
		वापस -EINVAL;

	timings->timings = tvp7002_timings[timings->index].timings;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops tvp7002_ctrl_ops = अणु
	.s_ctrl = tvp7002_s_ctrl,
पूर्ण;

/*
 * tvp7002_क्रमागत_mbus_code() - Enum supported digital video क्रमmat on pad
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @cfg: pad configuration
 * @code: poपूर्णांकer to subdev क्रमागत mbus code काष्ठा
 *
 * Enumerate supported digital video क्रमmats क्रम pad.
 */
अटल पूर्णांक
tvp7002_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
		       काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	/* Check requested क्रमmat index is within range */
	अगर (code->index != 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_YUYV10_1X20;

	वापस 0;
पूर्ण

/*
 * tvp7002_get_pad_क्रमmat() - get video क्रमmat on pad
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @cfg: pad configuration
 * @fmt: poपूर्णांकer to subdev क्रमmat काष्ठा
 *
 * get video क्रमmat क्रम pad.
 */
अटल पूर्णांक
tvp7002_get_pad_क्रमmat(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
		       काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा tvp7002 *tvp7002 = to_tvp7002(sd);

	fmt->क्रमmat.code = MEDIA_BUS_FMT_YUYV10_1X20;
	fmt->क्रमmat.width = tvp7002->current_timings->timings.bt.width;
	fmt->क्रमmat.height = tvp7002->current_timings->timings.bt.height;
	fmt->क्रमmat.field = tvp7002->current_timings->scanmode;
	fmt->क्रमmat.colorspace = tvp7002->current_timings->color_space;

	वापस 0;
पूर्ण

/*
 * tvp7002_set_pad_क्रमmat() - set video क्रमmat on pad
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @cfg: pad configuration
 * @fmt: poपूर्णांकer to subdev क्रमmat काष्ठा
 *
 * set video क्रमmat क्रम pad.
 */
अटल पूर्णांक
tvp7002_set_pad_क्रमmat(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
		       काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	वापस tvp7002_get_pad_क्रमmat(sd, cfg, fmt);
पूर्ण

/* V4L2 core operation handlers */
अटल स्थिर काष्ठा v4l2_subdev_core_ops tvp7002_core_ops = अणु
	.log_status = tvp7002_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = tvp7002_g_रेजिस्टर,
	.s_रेजिस्टर = tvp7002_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

/* Specअगरic video subप्रणाली operation handlers */
अटल स्थिर काष्ठा v4l2_subdev_video_ops tvp7002_video_ops = अणु
	.g_dv_timings = tvp7002_g_dv_timings,
	.s_dv_timings = tvp7002_s_dv_timings,
	.query_dv_timings = tvp7002_query_dv_timings,
	.s_stream = tvp7002_s_stream,
पूर्ण;

/* media pad related operation handlers */
अटल स्थिर काष्ठा v4l2_subdev_pad_ops tvp7002_pad_ops = अणु
	.क्रमागत_mbus_code = tvp7002_क्रमागत_mbus_code,
	.get_fmt = tvp7002_get_pad_क्रमmat,
	.set_fmt = tvp7002_set_pad_क्रमmat,
	.क्रमागत_dv_timings = tvp7002_क्रमागत_dv_timings,
पूर्ण;

/* V4L2 top level operation handlers */
अटल स्थिर काष्ठा v4l2_subdev_ops tvp7002_ops = अणु
	.core = &tvp7002_core_ops,
	.video = &tvp7002_video_ops,
	.pad = &tvp7002_pad_ops,
पूर्ण;

अटल काष्ठा tvp7002_config *
tvp7002_get_pdata(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु .bus_type = 0 पूर्ण;
	काष्ठा tvp7002_config *pdata = शून्य;
	काष्ठा device_node *endpoपूर्णांक;
	अचिन्हित पूर्णांक flags;

	अगर (!IS_ENABLED(CONFIG_OF) || !client->dev.of_node)
		वापस client->dev.platक्रमm_data;

	endpoपूर्णांक = of_graph_get_next_endpoपूर्णांक(client->dev.of_node, शून्य);
	अगर (!endpoपूर्णांक)
		वापस शून्य;

	अगर (v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(endpoपूर्णांक), &bus_cfg))
		जाओ करोne;

	pdata = devm_kzalloc(&client->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		जाओ करोne;

	flags = bus_cfg.bus.parallel.flags;

	अगर (flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
		pdata->hs_polarity = 1;

	अगर (flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
		pdata->vs_polarity = 1;

	अगर (flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
		pdata->clk_polarity = 1;

	अगर (flags & V4L2_MBUS_FIELD_EVEN_HIGH)
		pdata->fid_polarity = 1;

	अगर (flags & V4L2_MBUS_VIDEO_SOG_ACTIVE_HIGH)
		pdata->sog_polarity = 1;

करोne:
	of_node_put(endpoपूर्णांक);
	वापस pdata;
पूर्ण

/*
 * tvp7002_probe - Probe a TVP7002 device
 * @c: ptr to i2c_client काष्ठा
 * @id: ptr to i2c_device_id काष्ठा
 *
 * Initialize the TVP7002 device
 * Returns zero when successful, -EINVAL अगर रेजिस्टर पढ़ो fails or
 * -EIO अगर i2c access is not available.
 */
अटल पूर्णांक tvp7002_probe(काष्ठा i2c_client *c)
अणु
	काष्ठा tvp7002_config *pdata = tvp7002_get_pdata(c);
	काष्ठा v4l2_subdev *sd;
	काष्ठा tvp7002 *device;
	काष्ठा v4l2_dv_timings timings;
	पूर्णांक polarity_a;
	पूर्णांक polarity_b;
	u8 revision;
	पूर्णांक error;

	अगर (pdata == शून्य) अणु
		dev_err(&c->dev, "No platform data\n");
		वापस -EINVAL;
	पूर्ण

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(c->adapter,
		I2C_FUNC_SMBUS_READ_BYTE | I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		वापस -EIO;

	device = devm_kzalloc(&c->dev, माप(काष्ठा tvp7002), GFP_KERNEL);

	अगर (!device)
		वापस -ENOMEM;

	sd = &device->sd;
	device->pdata = pdata;
	device->current_timings = tvp7002_timings;

	/* Tell v4l2 the device is पढ़ोy */
	v4l2_i2c_subdev_init(sd, c, &tvp7002_ops);
	v4l_info(c, "tvp7002 found @ 0x%02x (%s)\n",
					c->addr, c->adapter->name);

	error = tvp7002_पढ़ो(sd, TVP7002_CHIP_REV, &revision);
	अगर (error < 0)
		वापस error;

	/* Get revision number */
	v4l2_info(sd, "Rev. %02x detected.\n", revision);
	अगर (revision != 0x02)
		v4l2_info(sd, "Unknown revision detected.\n");

	/* Initializes TVP7002 to its शेष values */
	error = tvp7002_ग_लिखो_inittab(sd, tvp7002_init_शेष);

	अगर (error < 0)
		वापस error;

	/* Set polarity inक्रमmation after रेजिस्टरs have been set */
	polarity_a = 0x20 | device->pdata->hs_polarity << 5
			| device->pdata->vs_polarity << 2;
	error = tvp7002_ग_लिखो(sd, TVP7002_SYNC_CTL_1, polarity_a);
	अगर (error < 0)
		वापस error;

	polarity_b = 0x01  | device->pdata->fid_polarity << 2
			| device->pdata->sog_polarity << 1
			| device->pdata->clk_polarity;
	error = tvp7002_ग_लिखो(sd, TVP7002_MISC_CTL_3, polarity_b);
	अगर (error < 0)
		वापस error;

	/* Set रेजिस्टरs according to शेष video mode */
	timings = device->current_timings->timings;
	error = tvp7002_s_dv_timings(sd, &timings);

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	device->pad.flags = MEDIA_PAD_FL_SOURCE;
	device->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	device->sd.entity.function = MEDIA_ENT_F_ATV_DECODER;

	error = media_entity_pads_init(&device->sd.entity, 1, &device->pad);
	अगर (error < 0)
		वापस error;
#पूर्ण_अगर

	v4l2_ctrl_handler_init(&device->hdl, 1);
	v4l2_ctrl_new_std(&device->hdl, &tvp7002_ctrl_ops,
			V4L2_CID_GAIN, 0, 255, 1, 0);
	sd->ctrl_handler = &device->hdl;
	अगर (device->hdl.error) अणु
		error = device->hdl.error;
		जाओ error;
	पूर्ण
	v4l2_ctrl_handler_setup(&device->hdl);

	error = v4l2_async_रेजिस्टर_subdev(&device->sd);
	अगर (error)
		जाओ error;

	वापस 0;

error:
	v4l2_ctrl_handler_मुक्त(&device->hdl);
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	media_entity_cleanup(&device->sd.entity);
#पूर्ण_अगर
	वापस error;
पूर्ण

/*
 * tvp7002_हटाओ - Remove TVP7002 device support
 * @c: ptr to i2c_client काष्ठा
 *
 * Reset the TVP7002 device
 * Returns zero.
 */
अटल पूर्णांक tvp7002_हटाओ(काष्ठा i2c_client *c)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(c);
	काष्ठा tvp7002 *device = to_tvp7002(sd);

	v4l2_dbg(1, debug, sd, "Removing tvp7002 adapter"
				"on address 0x%x\n", c->addr);
	v4l2_async_unरेजिस्टर_subdev(&device->sd);
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	media_entity_cleanup(&device->sd.entity);
#पूर्ण_अगर
	v4l2_ctrl_handler_मुक्त(&device->hdl);
	वापस 0;
पूर्ण

/* I2C Device ID table */
अटल स्थिर काष्ठा i2c_device_id tvp7002_id[] = अणु
	अणु "tvp7002", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tvp7002_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id tvp7002_of_match[] = अणु
	अणु .compatible = "ti,tvp7002", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tvp7002_of_match);
#पूर्ण_अगर

/* I2C driver data */
अटल काष्ठा i2c_driver tvp7002_driver = अणु
	.driver = अणु
		.of_match_table = of_match_ptr(tvp7002_of_match),
		.name = TVP7002_MODULE_NAME,
	पूर्ण,
	.probe_new = tvp7002_probe,
	.हटाओ = tvp7002_हटाओ,
	.id_table = tvp7002_id,
पूर्ण;

module_i2c_driver(tvp7002_driver);
