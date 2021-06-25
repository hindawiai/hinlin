<शैली गुरु>
/*
 * Header file क्रम TI DA8XX LCD controller platक्रमm data.
 *
 * Copyright (C) 2008-2009 MontaVista Software Inc.
 * Copyright (C) 2008-2009 Texas Instruments Inc
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित DA8XX_FB_H
#घोषणा DA8XX_FB_H

क्रमागत panel_shade अणु
	MONOCHROME = 0,
	COLOR_ACTIVE,
	COLOR_PASSIVE,
पूर्ण;

क्रमागत raster_load_mode अणु
	LOAD_DATA = 1,
	LOAD_PALETTE,
पूर्ण;

क्रमागत da8xx_frame_complete अणु
	DA8XX_FRAME_WAIT,
	DA8XX_FRAME_NOWAIT,
पूर्ण;

काष्ठा da8xx_lcdc_platक्रमm_data अणु
	स्थिर अक्षर manu_name[10];
	व्योम *controller_data;
	स्थिर अक्षर type[25];
पूर्ण;

काष्ठा lcd_ctrl_config अणु
	क्रमागत panel_shade panel_shade;

	/* AC Bias Pin Frequency */
	पूर्णांक ac_bias;

	/* AC Bias Pin Transitions per Interrupt */
	पूर्णांक ac_bias_पूर्णांकrpt;

	/* DMA burst size */
	पूर्णांक dma_burst_sz;

	/* Bits per pixel */
	पूर्णांक bpp;

	/* FIFO DMA Request Delay */
	पूर्णांक fdd;

	/* TFT Alternative Signal Mapping (Only क्रम active) */
	अचिन्हित अक्षर tft_alt_mode;

	/* 12 Bit Per Pixel (5-6-5) Mode (Only क्रम passive) */
	अचिन्हित अक्षर stn_565_mode;

	/* Mono 8-bit Mode: 1=D0-D7 or 0=D0-D3 */
	अचिन्हित अक्षर mono_8bit_mode;

	/* Horizontal and Vertical Sync Edge: 0=rising 1=falling */
	अचिन्हित अक्षर sync_edge;

	/* Raster Data Order Select: 1=Most-to-least 0=Least-to-most */
	अचिन्हित अक्षर raster_order;

	/* DMA FIFO threshold */
	पूर्णांक fअगरo_th;
पूर्ण;

काष्ठा lcd_sync_arg अणु
	पूर्णांक back_porch;
	पूर्णांक front_porch;
	पूर्णांक pulse_width;
पूर्ण;

/* ioctls */
#घोषणा FBIOGET_CONTRAST	_IOR('F', 1, पूर्णांक)
#घोषणा FBIOPUT_CONTRAST	_IOW('F', 2, पूर्णांक)
#घोषणा FBIGET_BRIGHTNESS	_IOR('F', 3, पूर्णांक)
#घोषणा FBIPUT_BRIGHTNESS	_IOW('F', 3, पूर्णांक)
#घोषणा FBIGET_COLOR		_IOR('F', 5, पूर्णांक)
#घोषणा FBIPUT_COLOR		_IOW('F', 6, पूर्णांक)
#घोषणा FBIPUT_HSYNC		_IOW('F', 9, पूर्णांक)
#घोषणा FBIPUT_VSYNC		_IOW('F', 10, पूर्णांक)

/* Proprietary FB_SYNC_ flags */
#घोषणा FB_SYNC_CLK_INVERT 0x40000000

#पूर्ण_अगर  /* अगरndef DA8XX_FB_H */

