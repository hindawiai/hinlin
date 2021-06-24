<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/video/acornfb.h
 *
 *  Copyright (C) 1998,1999 Russell King
 *
 *  Frame buffer code क्रम Acorn platक्रमms
 */
#अगर defined(HAS_VIDC20)
#समावेश <यंत्र/hardware/iomd.h>
#घोषणा VIDC_PALETTE_SIZE	256
#घोषणा VIDC_NAME		"VIDC20"
#पूर्ण_अगर

#घोषणा EXTEND8(x) ((x)|(x)<<8)
#घोषणा EXTEND4(x) ((x)|(x)<<4|(x)<<8|(x)<<12)

काष्ठा vidc20_palette अणु
	u_पूर्णांक red:8;
	u_पूर्णांक green:8;
	u_पूर्णांक blue:8;
	u_पूर्णांक ext:4;
	u_पूर्णांक unused:4;
पूर्ण;

काष्ठा vidc_palette अणु
	u_पूर्णांक red:4;
	u_पूर्णांक green:4;
	u_पूर्णांक blue:4;
	u_पूर्णांक trans:1;
	u_पूर्णांक sbz1:13;
	u_पूर्णांक reg:4;
	u_पूर्णांक sbz2:2;
पूर्ण;

जोड़ palette अणु
	काष्ठा vidc20_palette	vidc20;
	काष्ठा vidc_palette	vidc;
	u_पूर्णांक	p;
पूर्ण;

काष्ठा acornfb_par अणु
	काष्ठा device	*dev;
	अचिन्हित दीर्घ	screen_end;
	अचिन्हित पूर्णांक	dram_size;
	अचिन्हित पूर्णांक	vram_half_sam;
	अचिन्हित पूर्णांक	palette_size;
	  चिन्हित पूर्णांक	montype;
	अचिन्हित पूर्णांक	using_vram	: 1;
	अचिन्हित पूर्णांक	dpms		: 1;

	जोड़ palette palette[VIDC_PALETTE_SIZE];

	u32		pseuकरो_palette[16];
पूर्ण;

काष्ठा vidc_timing अणु
	u_पूर्णांक	h_cycle;
	u_पूर्णांक	h_sync_width;
	u_पूर्णांक	h_border_start;
	u_पूर्णांक	h_display_start;
	u_पूर्णांक	h_display_end;
	u_पूर्णांक	h_border_end;
	u_पूर्णांक	h_पूर्णांकerlace;

	u_पूर्णांक	v_cycle;
	u_पूर्णांक	v_sync_width;
	u_पूर्णांक	v_border_start;
	u_पूर्णांक	v_display_start;
	u_पूर्णांक	v_display_end;
	u_पूर्णांक	v_border_end;

	u_पूर्णांक	control;

	/* VIDC20 only */
	u_पूर्णांक	pll_ctl;
पूर्ण;

काष्ठा modey_params अणु
	u_पूर्णांक	y_res;
	u_पूर्णांक	u_margin;
	u_पूर्णांक	b_margin;
	u_पूर्णांक	vsync_len;
	u_पूर्णांक	vf;
पूर्ण;

काष्ठा modex_params अणु
	u_पूर्णांक	x_res;
	u_पूर्णांक	l_margin;
	u_पूर्णांक	r_margin;
	u_पूर्णांक	hsync_len;
	u_पूर्णांक	घड़ी;
	u_पूर्णांक	hf;
	स्थिर काष्ठा modey_params *modey;
पूर्ण;

#अगर_घोषित HAS_VIDC20
/*
 * VIDC20 रेजिस्टरs
 */
#घोषणा VIDC20_CTRL		0xe0000000
#घोषणा VIDC20_CTRL_PIX_VCLK	(0 << 0)
#घोषणा VIDC20_CTRL_PIX_HCLK	(1 << 0)
#घोषणा VIDC20_CTRL_PIX_RCLK	(2 << 0)
#घोषणा VIDC20_CTRL_PIX_CK	(0 << 2)
#घोषणा VIDC20_CTRL_PIX_CK2	(1 << 2)
#घोषणा VIDC20_CTRL_PIX_CK3	(2 << 2)
#घोषणा VIDC20_CTRL_PIX_CK4	(3 << 2)
#घोषणा VIDC20_CTRL_PIX_CK5	(4 << 2)
#घोषणा VIDC20_CTRL_PIX_CK6	(5 << 2)
#घोषणा VIDC20_CTRL_PIX_CK7	(6 << 2)
#घोषणा VIDC20_CTRL_PIX_CK8	(7 << 2)
#घोषणा VIDC20_CTRL_1BPP	(0 << 5)
#घोषणा VIDC20_CTRL_2BPP	(1 << 5)
#घोषणा VIDC20_CTRL_4BPP	(2 << 5)
#घोषणा VIDC20_CTRL_8BPP	(3 << 5)
#घोषणा VIDC20_CTRL_16BPP	(4 << 5)
#घोषणा VIDC20_CTRL_32BPP	(6 << 5)
#घोषणा VIDC20_CTRL_FIFO_NS	(0 << 8)
#घोषणा VIDC20_CTRL_FIFO_4	(1 << 8)
#घोषणा VIDC20_CTRL_FIFO_8	(2 << 8)
#घोषणा VIDC20_CTRL_FIFO_12	(3 << 8)
#घोषणा VIDC20_CTRL_FIFO_16	(4 << 8)
#घोषणा VIDC20_CTRL_FIFO_20	(5 << 8)
#घोषणा VIDC20_CTRL_FIFO_24	(6 << 8)
#घोषणा VIDC20_CTRL_FIFO_28	(7 << 8)
#घोषणा VIDC20_CTRL_INT		(1 << 12)
#घोषणा VIDC20_CTRL_DUP		(1 << 13)
#घोषणा VIDC20_CTRL_PDOWN	(1 << 14)

#घोषणा VIDC20_ECTL		0xc0000000
#घोषणा VIDC20_ECTL_REG(x)	((x) & 0xf3)
#घोषणा VIDC20_ECTL_ECK		(1 << 2)
#घोषणा VIDC20_ECTL_REDPED	(1 << 8)
#घोषणा VIDC20_ECTL_GREENPED	(1 << 9)
#घोषणा VIDC20_ECTL_BLUEPED	(1 << 10)
#घोषणा VIDC20_ECTL_DAC		(1 << 12)
#घोषणा VIDC20_ECTL_LCDGS	(1 << 13)
#घोषणा VIDC20_ECTL_HRM		(1 << 14)

#घोषणा VIDC20_ECTL_HS_MASK	(3 << 16)
#घोषणा VIDC20_ECTL_HS_HSYNC	(0 << 16)
#घोषणा VIDC20_ECTL_HS_NHSYNC	(1 << 16)
#घोषणा VIDC20_ECTL_HS_CSYNC	(2 << 16)
#घोषणा VIDC20_ECTL_HS_NCSYNC	(3 << 16)

#घोषणा VIDC20_ECTL_VS_MASK	(3 << 18)
#घोषणा VIDC20_ECTL_VS_VSYNC	(0 << 18)
#घोषणा VIDC20_ECTL_VS_NVSYNC	(1 << 18)
#घोषणा VIDC20_ECTL_VS_CSYNC	(2 << 18)
#घोषणा VIDC20_ECTL_VS_NCSYNC	(3 << 18)

#घोषणा VIDC20_DCTL		0xf0000000
/* 0-9 = number of words in scanline */
#घोषणा VIDC20_DCTL_SNA		(1 << 12)
#घोषणा VIDC20_DCTL_HDIS	(1 << 13)
#घोषणा VIDC20_DCTL_BUS_NS	(0 << 16)
#घोषणा VIDC20_DCTL_BUS_D31_0	(1 << 16)
#घोषणा VIDC20_DCTL_BUS_D63_32	(2 << 16)
#घोषणा VIDC20_DCTL_BUS_D63_0	(3 << 16)
#घोषणा VIDC20_DCTL_VRAM_DIS	(0 << 18)
#घोषणा VIDC20_DCTL_VRAM_PXCLK	(1 << 18)
#घोषणा VIDC20_DCTL_VRAM_PXCLK2	(2 << 18)
#घोषणा VIDC20_DCTL_VRAM_PXCLK4	(3 << 18)

#पूर्ण_अगर
