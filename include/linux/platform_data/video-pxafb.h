<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Support क्रम the xscale frame buffer.
 *
 *  Author:     Jean-Frederic Clere
 *  Created:    Sep 22, 2003
 *  Copyright:  jfclere@sinix.net
 */

#समावेश <linux/fb.h>
#समावेश <mach/regs-lcd.h>

/*
 * Supported LCD connections
 *
 * bits 0 - 3: क्रम LCD panel type:
 *
 *   STN  - क्रम passive matrix
 *   DSTN - क्रम dual scan passive matrix
 *   TFT  - क्रम active matrix
 *
 * bits 4 - 9 : क्रम bus width
 * bits 10-17 : क्रम AC Bias Pin Frequency
 * bit     18 : क्रम output enable polarity
 * bit     19 : क्रम pixel घड़ी edge
 * bit     20 : क्रम output pixel क्रमmat when base is RGBT16
 */
#घोषणा LCD_CONN_TYPE(_x)	((_x) & 0x0f)
#घोषणा LCD_CONN_WIDTH(_x)	(((_x) >> 4) & 0x1f)

#घोषणा LCD_TYPE_MASK		0xf
#घोषणा LCD_TYPE_UNKNOWN	0
#घोषणा LCD_TYPE_MONO_STN	1
#घोषणा LCD_TYPE_MONO_DSTN	2
#घोषणा LCD_TYPE_COLOR_STN	3
#घोषणा LCD_TYPE_COLOR_DSTN	4
#घोषणा LCD_TYPE_COLOR_TFT	5
#घोषणा LCD_TYPE_SMART_PANEL	6
#घोषणा LCD_TYPE_MAX		7

#घोषणा LCD_MONO_STN_4BPP	((4  << 4) | LCD_TYPE_MONO_STN)
#घोषणा LCD_MONO_STN_8BPP	((8  << 4) | LCD_TYPE_MONO_STN)
#घोषणा LCD_MONO_DSTN_8BPP	((8  << 4) | LCD_TYPE_MONO_DSTN)
#घोषणा LCD_COLOR_STN_8BPP	((8  << 4) | LCD_TYPE_COLOR_STN)
#घोषणा LCD_COLOR_DSTN_16BPP	((16 << 4) | LCD_TYPE_COLOR_DSTN)
#घोषणा LCD_COLOR_TFT_8BPP	((8  << 4) | LCD_TYPE_COLOR_TFT)
#घोषणा LCD_COLOR_TFT_16BPP	((16 << 4) | LCD_TYPE_COLOR_TFT)
#घोषणा LCD_COLOR_TFT_18BPP	((18 << 4) | LCD_TYPE_COLOR_TFT)
#घोषणा LCD_SMART_PANEL_8BPP	((8  << 4) | LCD_TYPE_SMART_PANEL)
#घोषणा LCD_SMART_PANEL_16BPP	((16 << 4) | LCD_TYPE_SMART_PANEL)
#घोषणा LCD_SMART_PANEL_18BPP	((18 << 4) | LCD_TYPE_SMART_PANEL)

#घोषणा LCD_AC_BIAS_FREQ(x)	(((x) & 0xff) << 10)
#घोषणा LCD_BIAS_ACTIVE_HIGH	(0 << 18)
#घोषणा LCD_BIAS_ACTIVE_LOW	(1 << 18)
#घोषणा LCD_PCLK_EDGE_RISE	(0 << 19)
#घोषणा LCD_PCLK_EDGE_FALL	(1 << 19)
#घोषणा LCD_ALTERNATE_MAPPING	(1 << 20)

/*
 * This काष्ठाure describes the machine which we are running on.
 * It is set in linux/arch/arm/mach-pxa/machine_name.c and used in the probe routine
 * of linux/drivers/video/pxafb.c
 */
काष्ठा pxafb_mode_info अणु
	u_दीर्घ		pixघड़ी;

	u_लघु		xres;
	u_लघु		yres;

	u_अक्षर		bpp;
	u_पूर्णांक		cmap_greyscale:1,
			depth:8,
			transparency:1,
			unused:22;

	/* Parallel Mode Timing */
	u_अक्षर		hsync_len;
	u_अक्षर		left_margin;
	u_अक्षर		right_margin;

	u_अक्षर		vsync_len;
	u_अक्षर		upper_margin;
	u_अक्षर		lower_margin;
	u_अक्षर		sync;

	/* Smart Panel Mode Timing - see PXA27x DM 7.4.15.0.3 क्रम details
	 * Note:
	 * 1. all parameters in nanosecond (ns)
	 * 2. a0csअणुrd,wrपूर्ण_set_hld are controlled by the same रेजिस्टर bits
	 *    in pxa27x and pxa3xx, initialize them to the same value or
	 *    the larger one will be used
	 * 3. same to अणुrd,wrपूर्ण_pulse_width
	 *
	 * 4. LCD_PCLK_EDGE_अणुRISE,FALLपूर्ण controls the L_PCLK_WR polarity
	 * 5. sync & FB_SYNC_HOR_HIGH_ACT controls the L_LCLK_A0
	 * 6. sync & FB_SYNC_VERT_HIGH_ACT controls the L_LCLK_RD
	 */
	अचिन्हित	a0csrd_set_hld;	/* A0 and CS Setup/Hold Time beक्रमe/after L_FCLK_RD */
	अचिन्हित	a0cswr_set_hld;	/* A0 and CS Setup/Hold Time beक्रमe/after L_PCLK_WR */
	अचिन्हित	wr_pulse_width;	/* L_PCLK_WR pulse width */
	अचिन्हित	rd_pulse_width;	/* L_FCLK_RD pulse width */
	अचिन्हित	cmd_inh_समय;	/* Command Inhibit समय between two ग_लिखोs */
	अचिन्हित	op_hold_समय;	/* Output Hold समय from L_FCLK_RD negation */
पूर्ण;

काष्ठा pxafb_mach_info अणु
	काष्ठा pxafb_mode_info *modes;
	अचिन्हित पूर्णांक num_modes;

	अचिन्हित पूर्णांक	lcd_conn;
	अचिन्हित दीर्घ	video_mem_size;

	u_पूर्णांक		fixed_modes:1,
			cmap_inverse:1,
			cmap_अटल:1,
			acceleration_enabled:1,
			unused:28;

	/* The following should be defined in LCCR0
	 *      LCCR0_Act or LCCR0_Pas          Active or Passive
	 *      LCCR0_Sngl or LCCR0_Dual        Single/Dual panel
	 *      LCCR0_Mono or LCCR0_Color       Mono/Color
	 *      LCCR0_4PixMono or LCCR0_8PixMono (in mono single mode)
	 *      LCCR0_DMADel(Tcpu) (optional)   DMA request delay
	 *
	 * The following should not be defined in LCCR0:
	 *      LCCR0_OUM, LCCR0_BM, LCCR0_QDM, LCCR0_DIS, LCCR0_EFM
	 *      LCCR0_IUM, LCCR0_SFM, LCCR0_LDM, LCCR0_ENB
	 */
	u_पूर्णांक		lccr0;
	/* The following should be defined in LCCR3
	 *      LCCR3_OutEnH or LCCR3_OutEnL    Output enable polarity
	 *      LCCR3_PixRsEdg or LCCR3_PixFlEdg Pixel घड़ी edge type
	 *      LCCR3_Acb(X)                    AB Bias pin frequency
	 *      LCCR3_DPC (optional)            Double Pixel Clock mode (untested)
	 *
	 * The following should not be defined in LCCR3
	 *      LCCR3_HSP, LCCR3_VSP, LCCR0_Pcd(x), LCCR3_Bpp
	 */
	u_पूर्णांक		lccr3;
	/* The following should be defined in LCCR4
	 *	LCCR4_PAL_FOR_0 or LCCR4_PAL_FOR_1 or LCCR4_PAL_FOR_2
	 *
	 * All other bits in LCCR4 should be left alone.
	 */
	u_पूर्णांक		lccr4;
	व्योम (*pxafb_backlight_घातer)(पूर्णांक);
	व्योम (*pxafb_lcd_घातer)(पूर्णांक, काष्ठा fb_var_screeninfo *);
	व्योम (*smart_update)(काष्ठा fb_info *);
पूर्ण;

व्योम pxa_set_fb_info(काष्ठा device *, काष्ठा pxafb_mach_info *);
अचिन्हित दीर्घ pxafb_get_hsync_समय(काष्ठा device *dev);

#अगर_घोषित CONFIG_FB_PXA_SMARTPANEL
बाह्य पूर्णांक pxafb_smart_queue(काष्ठा fb_info *info, uपूर्णांक16_t *cmds, पूर्णांक);
बाह्य पूर्णांक pxafb_smart_flush(काष्ठा fb_info *info);
#अन्यथा
अटल अंतरभूत पूर्णांक pxafb_smart_queue(काष्ठा fb_info *info,
				    uपूर्णांक16_t *cmds, पूर्णांक n)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pxafb_smart_flush(काष्ठा fb_info *info)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
