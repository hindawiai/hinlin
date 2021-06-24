<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * A V4L2 driver क्रम OmniVision OV7670 cameras.
 *
 * Copyright 2010 One Laptop Per Child
 */

#अगर_अघोषित __OV7670_H
#घोषणा __OV7670_H

काष्ठा ov7670_config अणु
	पूर्णांक min_width;			/* Filter out smaller sizes */
	पूर्णांक min_height;			/* Filter out smaller sizes */
	पूर्णांक घड़ी_speed;		/* External घड़ी speed (MHz) */
	bool use_smbus;			/* Use smbus I/O instead of I2C */
	bool pll_bypass;		/* Choose whether to bypass the PLL */
	bool pclk_hb_disable;		/* Disable toggling pixclk during horizontal blanking */
पूर्ण;

#पूर्ण_अगर
