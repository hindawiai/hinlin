<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * drivers/media/video/tvp514x.h
 *
 * Copyright (C) 2008 Texas Instruments Inc
 * Author: Vaibhav Hiremath <hvaibhav@ti.com>
 *
 * Contributors:
 *     Sivaraj R <sivaraj@ti.com>
 *     Brijesh R Jadav <brijesh.j@ti.com>
 *     Hardik Shah <hardik.shah@ti.com>
 *     Manjunath Hadli <mrh@ti.com>
 *     Karicheri Muralidharan <m-karicheri2@ti.com>
 */

#अगर_अघोषित _TVP514X_H
#घोषणा _TVP514X_H

/*
 * Other macros
 */
#घोषणा TVP514X_MODULE_NAME		"tvp514x"

#घोषणा TVP514X_XCLK_BT656		(27000000)

/* Number of pixels and number of lines per frame क्रम dअगरferent standards */
#घोषणा NTSC_NUM_ACTIVE_PIXELS		(720)
#घोषणा NTSC_NUM_ACTIVE_LINES		(480)
#घोषणा PAL_NUM_ACTIVE_PIXELS		(720)
#घोषणा PAL_NUM_ACTIVE_LINES		(576)

/* क्रमागत क्रम dअगरferent decoder input pin configuration */
क्रमागत tvp514x_input अणु
	/*
	 * CVBS input selection
	 */
	INPUT_CVBS_VI1A = 0x0,
	INPUT_CVBS_VI1B,
	INPUT_CVBS_VI1C,
	INPUT_CVBS_VI2A = 0x04,
	INPUT_CVBS_VI2B,
	INPUT_CVBS_VI2C,
	INPUT_CVBS_VI3A = 0x08,
	INPUT_CVBS_VI3B,
	INPUT_CVBS_VI3C,
	INPUT_CVBS_VI4A = 0x0C,
	/*
	 * S-Video input selection
	 */
	INPUT_SVIDEO_VI2A_VI1A = 0x44,
	INPUT_SVIDEO_VI2B_VI1B,
	INPUT_SVIDEO_VI2C_VI1C,
	INPUT_SVIDEO_VI2A_VI3A = 0x54,
	INPUT_SVIDEO_VI2B_VI3B,
	INPUT_SVIDEO_VI2C_VI3C,
	INPUT_SVIDEO_VI4A_VI1A = 0x4C,
	INPUT_SVIDEO_VI4A_VI1B,
	INPUT_SVIDEO_VI4A_VI1C,
	INPUT_SVIDEO_VI4A_VI3A = 0x5C,
	INPUT_SVIDEO_VI4A_VI3B,
	INPUT_SVIDEO_VI4A_VI3C,

	/* Need to add entries क्रम
	 * RGB, YPbPr and SCART.
	 */
	INPUT_INVALID
पूर्ण;

/* क्रमागत क्रम output क्रमmat supported. */
क्रमागत tvp514x_output अणु
	OUTPUT_10BIT_422_EMBEDDED_SYNC = 0,
	OUTPUT_20BIT_422_SEPERATE_SYNC,
	OUTPUT_10BIT_422_SEPERATE_SYNC = 3,
	OUTPUT_INVALID
पूर्ण;

/**
 * काष्ठा tvp514x_platक्रमm_data - Platक्रमm data values and access functions.
 * @clk_polarity: Clock polarity of the current पूर्णांकerface.
 * @hs_polarity: HSYNC Polarity configuration क्रम current पूर्णांकerface.
 * @vs_polarity: VSYNC Polarity configuration क्रम current पूर्णांकerface.
 */
काष्ठा tvp514x_platक्रमm_data अणु
	/* Interface control params */
	bool clk_polarity;
	bool hs_polarity;
	bool vs_polarity;
पूर्ण;


#पूर्ण_अगर				/* अगरndef _TVP514X_H */
