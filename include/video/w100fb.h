<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Support क्रम the w100 frame buffer.
 *
 *  Copyright (c) 2004-2005 Riअक्षरd Purdie
 *  Copyright (c) 2005 Ian Molton
 */

#घोषणा W100_GPIO_PORT_A	0
#घोषणा W100_GPIO_PORT_B	1

#घोषणा CLK_SRC_XTAL  0
#घोषणा CLK_SRC_PLL   1

काष्ठा w100fb_par;

अचिन्हित दीर्घ w100fb_gpio_पढ़ो(पूर्णांक port);
व्योम w100fb_gpio_ग_लिखो(पूर्णांक port, अचिन्हित दीर्घ value);
अचिन्हित दीर्घ w100fb_get_hsynclen(काष्ठा device *dev);

/* LCD Specअगरic Routines and Config */
काष्ठा w100_tg_info अणु
	व्योम (*change)(काष्ठा w100fb_par*);
	व्योम (*suspend)(काष्ठा w100fb_par*);
	व्योम (*resume)(काष्ठा w100fb_par*);
पूर्ण;

/* General Platक्रमm Specअगरic w100 Register Values */
काष्ठा w100_gen_regs अणु
	अचिन्हित दीर्घ lcd_क्रमmat;
	अचिन्हित दीर्घ lcdd_cntl1;
	अचिन्हित दीर्घ lcdd_cntl2;
	अचिन्हित दीर्घ genlcd_cntl1;
	अचिन्हित दीर्घ genlcd_cntl2;
	अचिन्हित दीर्घ genlcd_cntl3;
पूर्ण;

काष्ठा w100_gpio_regs अणु
	अचिन्हित दीर्घ init_data1;
	अचिन्हित दीर्घ init_data2;
	अचिन्हित दीर्घ gpio_dir1;
	अचिन्हित दीर्घ gpio_oe1;
	अचिन्हित दीर्घ gpio_dir2;
	अचिन्हित दीर्घ gpio_oe2;
पूर्ण;

/* Optional External Memory Configuration */
काष्ठा w100_mem_info अणु
	अचिन्हित दीर्घ ext_cntl;
	अचिन्हित दीर्घ sdram_mode_reg;
	अचिन्हित दीर्घ ext_timing_cntl;
	अचिन्हित दीर्घ io_cntl;
	अचिन्हित पूर्णांक size;
पूर्ण;

काष्ठा w100_bm_mem_info अणु
	अचिन्हित दीर्घ ext_mem_bw;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ ext_timing_ctl;
	अचिन्हित दीर्घ ext_cntl;
	अचिन्हित दीर्घ mode_reg;
	अचिन्हित दीर्घ io_cntl;
	अचिन्हित दीर्घ config;
पूर्ण;

/* LCD Mode definition */
काष्ठा w100_mode अणु
	अचिन्हित पूर्णांक xres;
	अचिन्हित पूर्णांक yres;
	अचिन्हित लघु left_margin;
	अचिन्हित लघु right_margin;
	अचिन्हित लघु upper_margin;
	अचिन्हित लघु lower_margin;
	अचिन्हित दीर्घ crtc_ss;
	अचिन्हित दीर्घ crtc_ls;
	अचिन्हित दीर्घ crtc_gs;
	अचिन्हित दीर्घ crtc_vpos_gs;
	अचिन्हित दीर्घ crtc_rev;
	अचिन्हित दीर्घ crtc_dclk;
	अचिन्हित दीर्घ crtc_gclk;
	अचिन्हित दीर्घ crtc_goe;
	अचिन्हित दीर्घ crtc_ps1_active;
	अक्षर pll_freq;
	अक्षर fast_pll_freq;
	पूर्णांक sysclk_src;
	पूर्णांक sysclk_भागider;
	पूर्णांक pixclk_src;
	पूर्णांक pixclk_भागider;
	पूर्णांक pixclk_भागider_rotated;
पूर्ण;

काष्ठा w100_pll_info अणु
	uपूर्णांक16_t freq;  /* desired Fout क्रम PLL (Mhz) */
	uपूर्णांक8_t M;      /* input भागider */
	uपूर्णांक8_t N_पूर्णांक;  /* VCO multiplier */
	uपूर्णांक8_t N_fac;  /* VCO multiplier fractional part */
	uपूर्णांक8_t tfgoal;
	uपूर्णांक8_t lock_समय;
पूर्ण;

/* Initial Video mode orientation flags */
#घोषणा INIT_MODE_ROTATED  0x1
#घोषणा INIT_MODE_FLIPPED  0x2

/*
 * This काष्ठाure describes the machine which we are running on.
 * It is set by machine specअगरic code and used in the probe routine
 * of drivers/video/w100fb.c
 */
काष्ठा w100fb_mach_info अणु
	/* General Platक्रमm Specअगरic Registers */
	काष्ठा w100_gen_regs *regs;
	/* Table of modes the LCD is capable of */
	काष्ठा w100_mode *modelist;
	अचिन्हित पूर्णांक num_modes;
	/* Hooks क्रम any platक्रमm specअगरic tg/lcd code (optional) */
	काष्ठा w100_tg_info *tg;
	/* External memory definition (अगर present) */
	काष्ठा w100_mem_info *mem;
	/* Additional External memory definition (अगर present) */
	काष्ठा w100_bm_mem_info *bm_mem;
	/* GPIO definitions (optional) */
	काष्ठा w100_gpio_regs *gpio;
	/* Initial Mode flags */
	अचिन्हित पूर्णांक init_mode;
	/* Xtal Frequency */
	अचिन्हित पूर्णांक xtal_freq;
	/* Enable Xtal input द्विगुनr (1 == enable) */
	अचिन्हित पूर्णांक xtal_dbl;
पूर्ण;

/* General frame buffer data काष्ठाure */
काष्ठा w100fb_par अणु
	अचिन्हित पूर्णांक chip_id;
	अचिन्हित पूर्णांक xres;
	अचिन्हित पूर्णांक yres;
	अचिन्हित पूर्णांक exपंचांगem_active;
	अचिन्हित पूर्णांक flip;
	अचिन्हित पूर्णांक blanked;
	अचिन्हित पूर्णांक fastpll_mode;
	अचिन्हित दीर्घ hsync_len;
	काष्ठा w100_mode *mode;
	काष्ठा w100_pll_info *pll_table;
	काष्ठा w100fb_mach_info *mach;
	uपूर्णांक32_t *saved_पूर्णांकmem;
	uपूर्णांक32_t *saved_exपंचांगem;
पूर्ण;
