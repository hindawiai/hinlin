<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2009 Marvell International Ltd.
 */

#अगर_अघोषित __ASM_MACH_PXA168FB_H
#घोषणा __ASM_MACH_PXA168FB_H

#समावेश <linux/fb.h>
#समावेश <linux/पूर्णांकerrupt.h>

/* Dumb पूर्णांकerface */
#घोषणा PIN_MODE_DUMB_24		0
#घोषणा PIN_MODE_DUMB_18_SPI		1
#घोषणा PIN_MODE_DUMB_18_GPIO		2
#घोषणा PIN_MODE_DUMB_16_SPI		3
#घोषणा PIN_MODE_DUMB_16_GPIO		4
#घोषणा PIN_MODE_DUMB_12_SPI_GPIO	5
#घोषणा PIN_MODE_SMART_18_SPI		6
#घोषणा PIN_MODE_SMART_16_SPI		7
#घोषणा PIN_MODE_SMART_8_SPI_GPIO	8

/* Dumb पूर्णांकerface pin allocation */
#घोषणा DUMB_MODE_RGB565		0
#घोषणा DUMB_MODE_RGB565_UPPER		1
#घोषणा DUMB_MODE_RGB666		2
#घोषणा DUMB_MODE_RGB666_UPPER		3
#घोषणा DUMB_MODE_RGB444		4
#घोषणा DUMB_MODE_RGB444_UPPER		5
#घोषणा DUMB_MODE_RGB888		6

/* शेष fb buffer size WVGA-32bits */
#घोषणा DEFAULT_FB_SIZE	(800 * 480 * 4)

/*
 * Buffer pixel क्रमmat
 * bit0 is क्रम rb swap.
 * bit12 is क्रम Y UorV swap
 */
#घोषणा PIX_FMT_RGB565		0
#घोषणा PIX_FMT_BGR565		1
#घोषणा PIX_FMT_RGB1555		2
#घोषणा PIX_FMT_BGR1555		3
#घोषणा PIX_FMT_RGB888PACK	4
#घोषणा PIX_FMT_BGR888PACK	5
#घोषणा PIX_FMT_RGB888UNPACK	6
#घोषणा PIX_FMT_BGR888UNPACK	7
#घोषणा PIX_FMT_RGBA888		8
#घोषणा PIX_FMT_BGRA888		9
#घोषणा PIX_FMT_YUV422PACK	10
#घोषणा PIX_FMT_YVU422PACK	11
#घोषणा PIX_FMT_YUV422PLANAR	12
#घोषणा PIX_FMT_YVU422PLANAR	13
#घोषणा PIX_FMT_YUV420PLANAR	14
#घोषणा PIX_FMT_YVU420PLANAR	15
#घोषणा PIX_FMT_PSEUDOCOLOR	20
#घोषणा PIX_FMT_UYVY422PACK	(0x1000|PIX_FMT_YUV422PACK)

/*
 * PXA LCD controller निजी state.
 */
काष्ठा pxa168fb_info अणु
	काष्ठा device		*dev;
	काष्ठा clk		*clk;
	काष्ठा fb_info		*info;

	व्योम __iomem		*reg_base;
	dma_addr_t		fb_start_dma;
	u32			pseuकरो_palette[16];

	पूर्णांक			pix_fmt;
	अचिन्हित		is_blanked:1;
	अचिन्हित		panel_rbswap:1;
	अचिन्हित		active:1;
पूर्ण;

/*
 * PXA fb machine inक्रमmation
 */
काष्ठा pxa168fb_mach_info अणु
	अक्षर	id[16];

	पूर्णांक		num_modes;
	काष्ठा fb_videomode *modes;

	/*
	 * Pix_fmt
	 */
	अचिन्हित	pix_fmt;

	/*
	 * I/O pin allocation.
	 */
	अचिन्हित	io_pin_allocation_mode:4;

	/*
	 * Dumb panel -- assignment of R/G/B component info to the 24
	 * available बाह्यal data lanes.
	 */
	अचिन्हित	dumb_mode:4;
	अचिन्हित	panel_rgb_reverse_lanes:1;

	/*
	 * Dumb panel -- GPIO output data.
	 */
	अचिन्हित	gpio_output_mask:8;
	अचिन्हित	gpio_output_data:8;

	/*
	 * Dumb panel -- configurable output संकेत polarity.
	 */
	अचिन्हित	invert_composite_blank:1;
	अचिन्हित	invert_pix_val_ena:1;
	अचिन्हित	invert_pixघड़ी:1;
	अचिन्हित	panel_rbswap:1;
	अचिन्हित	active:1;
	अचिन्हित	enable_lcd:1;
पूर्ण;

#पूर्ण_अगर /* __ASM_MACH_PXA168FB_H */
