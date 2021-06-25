<शैली गुरु>
/*
 * Permedia2 framebuffer driver.
 *
 * 2.5/2.6 driver:
 * Copyright (c) 2003 Jim Hague (jim.hague@acm.org)
 *
 * based on 2.4 driver:
 * Copyright (c) 1998-2000 Ilario Nardinocchi (nardinoc@CS.UniBO.IT)
 * Copyright (c) 1999 Jakub Jelinek (jakub@redhat.com)
 *
 * and additional input from James Simmon's port of Hannu Mallat's tdfx
 * driver.
 *
 * I have a Creative Graphics Blaster Exxtreme card - pm2fb on x86. I
 * have no access to other pm2fb implementations. Sparc (and thus
 * hopefully other big-endian) devices now work, thanks to a lot of
 * testing work by Ron Murray. I have no access to CVision hardware,
 * and thereक्रमe क्रम now I am omitting the CVision code.
 *
 * Multiple boards support has been on the TODO list क्रम ages.
 * Don't expect this to change.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <video/permedia2.h>
#समावेश <video/cvisionppc.h>

#अगर !defined(__LITTLE_ENDIAN) && !defined(__BIG_ENDIAN)
#त्रुटि	"The endianness of the target host has not been defined."
#पूर्ण_अगर

#अगर !defined(CONFIG_PCI)
#त्रुटि "Only generic PCI cards supported."
#पूर्ण_अगर

#अघोषित PM2FB_MASTER_DEBUG
#अगर_घोषित PM2FB_MASTER_DEBUG
#घोषणा DPRINTK(a, b...)	\
	prपूर्णांकk(KERN_DEBUG "pm2fb: %s: " a, __func__ , ## b)
#अन्यथा
#घोषणा DPRINTK(a, b...)	no_prपूर्णांकk(a, ##b)
#पूर्ण_अगर

#घोषणा PM2_PIXMAP_SIZE	(1600 * 4)

/*
 * Driver data
 */
अटल पूर्णांक hwcursor = 1;
अटल अक्षर *mode_option;

/*
 * The XFree GLINT driver will (I think to implement hardware cursor
 * support on TVP4010 and similar where there is no RAMDAC - see
 * comment in set_video) always request +ve sync regardless of what
 * the mode requires. This screws me because I have a Sun
 * fixed-frequency monitor which असलolutely has to have -ve sync. So
 * these flags allow the user to specअगरy that requests क्रम +ve sync
 * should be silently turned in -ve sync.
 */
अटल bool lowhsync;
अटल bool lowvsync;
अटल bool noaccel;
अटल bool nomtrr;

/*
 * The hardware state of the graphics card that isn't part of the
 * screeninfo.
 */
काष्ठा pm2fb_par
अणु
	pm2type_t	type;		/* Board type */
	अचिन्हित अक्षर	__iomem *v_regs;/* भव address of p_regs */
	u32		memघड़ी;	/* memघड़ी */
	u32		video;		/* video flags beक्रमe blanking */
	u32		mem_config;	/* MemConfig reg at probe */
	u32		mem_control;	/* MemControl reg at probe */
	u32		boot_address;	/* BootAddress reg at probe */
	u32		palette[16];
	पूर्णांक		wc_cookie;
पूर्ण;

/*
 * Here we define the शेष काष्ठाs fb_fix_screeninfo and fb_var_screeninfo
 * अगर we करोn't use modedb.
 */
अटल काष्ठा fb_fix_screeninfo pm2fb_fix = अणु
	.id =		"",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_PSEUDOCOLOR,
	.xpanstep =	1,
	.ypanstep =	1,
	.ywrapstep =	0,
	.accel =	FB_ACCEL_3DLABS_PERMEDIA2,
पूर्ण;

/*
 * Default video mode. In हाल the modedb करोesn't work.
 */
अटल स्थिर काष्ठा fb_var_screeninfo pm2fb_var = अणु
	/* "640x480, 8 bpp @ 60 Hz */
	.xres =			640,
	.yres =			480,
	.xres_भव =		640,
	.yres_भव =		480,
	.bits_per_pixel =	8,
	.red =			अणु0, 8, 0पूर्ण,
	.blue =			अणु0, 8, 0पूर्ण,
	.green =		अणु0, 8, 0पूर्ण,
	.activate =		FB_ACTIVATE_NOW,
	.height =		-1,
	.width =		-1,
	.accel_flags =		0,
	.pixघड़ी =		39721,
	.left_margin =		40,
	.right_margin =		24,
	.upper_margin =		32,
	.lower_margin =		11,
	.hsync_len =		96,
	.vsync_len =		2,
	.vmode =		FB_VMODE_NONINTERLACED
पूर्ण;

/*
 * Utility functions
 */

अटल अंतरभूत u32 pm2_RD(काष्ठा pm2fb_par *p, s32 off)
अणु
	वापस fb_पढ़ोl(p->v_regs + off);
पूर्ण

अटल अंतरभूत व्योम pm2_WR(काष्ठा pm2fb_par *p, s32 off, u32 v)
अणु
	fb_ग_लिखोl(v, p->v_regs + off);
पूर्ण

अटल अंतरभूत u32 pm2_RDAC_RD(काष्ठा pm2fb_par *p, s32 idx)
अणु
	pm2_WR(p, PM2R_RD_PALETTE_WRITE_ADDRESS, idx);
	mb();
	वापस pm2_RD(p, PM2R_RD_INDEXED_DATA);
पूर्ण

अटल अंतरभूत u32 pm2v_RDAC_RD(काष्ठा pm2fb_par *p, s32 idx)
अणु
	pm2_WR(p, PM2VR_RD_INDEX_LOW, idx & 0xff);
	mb();
	वापस pm2_RD(p,  PM2VR_RD_INDEXED_DATA);
पूर्ण

अटल अंतरभूत व्योम pm2_RDAC_WR(काष्ठा pm2fb_par *p, s32 idx, u32 v)
अणु
	pm2_WR(p, PM2R_RD_PALETTE_WRITE_ADDRESS, idx);
	wmb();
	pm2_WR(p, PM2R_RD_INDEXED_DATA, v);
	wmb();
पूर्ण

अटल अंतरभूत व्योम pm2v_RDAC_WR(काष्ठा pm2fb_par *p, s32 idx, u32 v)
अणु
	pm2_WR(p, PM2VR_RD_INDEX_LOW, idx & 0xff);
	wmb();
	pm2_WR(p, PM2VR_RD_INDEXED_DATA, v);
	wmb();
पूर्ण

#अगर_घोषित CONFIG_FB_PM2_FIFO_DISCONNECT
#घोषणा WAIT_FIFO(p, a)
#अन्यथा
अटल अंतरभूत व्योम WAIT_FIFO(काष्ठा pm2fb_par *p, u32 a)
अणु
	जबतक (pm2_RD(p, PM2R_IN_FIFO_SPACE) < a)
		cpu_relax();
पूर्ण
#पूर्ण_अगर

/*
 * partial products क्रम the supported horizontal resolutions.
 */
#घोषणा PACKPP(p0, p1, p2)	(((p2) << 6) | ((p1) << 3) | (p0))
अटल स्थिर काष्ठा अणु
	u16 width;
	u16 pp;
पूर्ण pp_table[] = अणु
	अणु 32,	PACKPP(1, 0, 0) पूर्ण, अणु 64,	PACKPP(1, 1, 0) पूर्ण,
	अणु 96,	PACKPP(1, 1, 1) पूर्ण, अणु 128,	PACKPP(2, 1, 1) पूर्ण,
	अणु 160,	PACKPP(2, 2, 1) पूर्ण, अणु 192,	PACKPP(2, 2, 2) पूर्ण,
	अणु 224,	PACKPP(3, 2, 1) पूर्ण, अणु 256,	PACKPP(3, 2, 2) पूर्ण,
	अणु 288,	PACKPP(3, 3, 1) पूर्ण, अणु 320,	PACKPP(3, 3, 2) पूर्ण,
	अणु 384,	PACKPP(3, 3, 3) पूर्ण, अणु 416,	PACKPP(4, 3, 1) पूर्ण,
	अणु 448,	PACKPP(4, 3, 2) पूर्ण, अणु 512,	PACKPP(4, 3, 3) पूर्ण,
	अणु 544,	PACKPP(4, 4, 1) पूर्ण, अणु 576,	PACKPP(4, 4, 2) पूर्ण,
	अणु 640,	PACKPP(4, 4, 3) पूर्ण, अणु 768,	PACKPP(4, 4, 4) पूर्ण,
	अणु 800,	PACKPP(5, 4, 1) पूर्ण, अणु 832,	PACKPP(5, 4, 2) पूर्ण,
	अणु 896,	PACKPP(5, 4, 3) पूर्ण, अणु 1024,	PACKPP(5, 4, 4) पूर्ण,
	अणु 1056,	PACKPP(5, 5, 1) पूर्ण, अणु 1088,	PACKPP(5, 5, 2) पूर्ण,
	अणु 1152,	PACKPP(5, 5, 3) पूर्ण, अणु 1280,	PACKPP(5, 5, 4) पूर्ण,
	अणु 1536,	PACKPP(5, 5, 5) पूर्ण, अणु 1568,	PACKPP(6, 5, 1) पूर्ण,
	अणु 1600,	PACKPP(6, 5, 2) पूर्ण, अणु 1664,	PACKPP(6, 5, 3) पूर्ण,
	अणु 1792,	PACKPP(6, 5, 4) पूर्ण, अणु 2048,	PACKPP(6, 5, 5) पूर्ण,
	अणु 0,	0 पूर्ण पूर्ण;

अटल u32 partprod(u32 xres)
अणु
	पूर्णांक i;

	क्रम (i = 0; pp_table[i].width && pp_table[i].width != xres; i++)
		;
	अगर (pp_table[i].width == 0)
		DPRINTK("invalid width %u\n", xres);
	वापस pp_table[i].pp;
पूर्ण

अटल u32 to3264(u32 timing, पूर्णांक bpp, पूर्णांक is64)
अणु
	चयन (bpp) अणु
	हाल 24:
		timing *= 3;
		fallthrough;
	हाल 8:
		timing >>= 1;
		fallthrough;
	हाल 16:
		timing >>= 1;
		fallthrough;
	हाल 32:
		अवरोध;
	पूर्ण
	अगर (is64)
		timing >>= 1;
	वापस timing;
पूर्ण

अटल व्योम pm2_mnp(u32 clk, अचिन्हित अक्षर *mm, अचिन्हित अक्षर *nn,
		    अचिन्हित अक्षर *pp)
अणु
	अचिन्हित अक्षर m;
	अचिन्हित अक्षर n;
	अचिन्हित अक्षर p;
	u32 f;
	s32 curr;
	s32 delta = 100000;

	*mm = *nn = *pp = 0;
	क्रम (n = 2; n < 15; n++) अणु
		क्रम (m = 2; m; m++) अणु
			f = PM2_REFERENCE_CLOCK * m / n;
			अगर (f >= 150000 && f <= 300000) अणु
				क्रम (p = 0; p < 5; p++, f >>= 1) अणु
					curr = (clk > f) ? clk - f : f - clk;
					अगर (curr < delta) अणु
						delta = curr;
						*mm = m;
						*nn = n;
						*pp = p;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pm2v_mnp(u32 clk, अचिन्हित अक्षर *mm, अचिन्हित अक्षर *nn,
		     अचिन्हित अक्षर *pp)
अणु
	अचिन्हित अक्षर m;
	अचिन्हित अक्षर n;
	अचिन्हित अक्षर p;
	u32 f;
	s32 delta = 1000;

	*mm = *nn = *pp = 0;
	क्रम (m = 1; m < 128; m++) अणु
		क्रम (n = 2 * m + 1; n; n++) अणु
			क्रम (p = 0; p < 2; p++) अणु
				f = (PM2_REFERENCE_CLOCK >> (p + 1)) * n / m;
				अगर (clk > f - delta && clk < f + delta) अणु
					delta = (clk > f) ? clk - f : f - clk;
					*mm = m;
					*nn = n;
					*pp = p;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम clear_palette(काष्ठा pm2fb_par *p)
अणु
	पूर्णांक i = 256;

	WAIT_FIFO(p, 1);
	pm2_WR(p, PM2R_RD_PALETTE_WRITE_ADDRESS, 0);
	wmb();
	जबतक (i--) अणु
		WAIT_FIFO(p, 3);
		pm2_WR(p, PM2R_RD_PALETTE_DATA, 0);
		pm2_WR(p, PM2R_RD_PALETTE_DATA, 0);
		pm2_WR(p, PM2R_RD_PALETTE_DATA, 0);
	पूर्ण
पूर्ण

अटल व्योम reset_card(काष्ठा pm2fb_par *p)
अणु
	अगर (p->type == PM2_TYPE_PERMEDIA2V)
		pm2_WR(p, PM2VR_RD_INDEX_HIGH, 0);
	pm2_WR(p, PM2R_RESET_STATUS, 0);
	mb();
	जबतक (pm2_RD(p, PM2R_RESET_STATUS) & PM2F_BEING_RESET)
		cpu_relax();
	mb();
#अगर_घोषित CONFIG_FB_PM2_FIFO_DISCONNECT
	DPRINTK("FIFO disconnect enabled\n");
	pm2_WR(p, PM2R_FIFO_DISCON, 1);
	mb();
#पूर्ण_अगर

	/* Restore stashed memory config inक्रमmation from probe */
	WAIT_FIFO(p, 3);
	pm2_WR(p, PM2R_MEM_CONTROL, p->mem_control);
	pm2_WR(p, PM2R_BOOT_ADDRESS, p->boot_address);
	wmb();
	pm2_WR(p, PM2R_MEM_CONFIG, p->mem_config);
पूर्ण

अटल व्योम reset_config(काष्ठा pm2fb_par *p)
अणु
	WAIT_FIFO(p, 53);
	pm2_WR(p, PM2R_CHIP_CONFIG, pm2_RD(p, PM2R_CHIP_CONFIG) &
			~(PM2F_VGA_ENABLE | PM2F_VGA_FIXED));
	pm2_WR(p, PM2R_BYPASS_WRITE_MASK, ~(0L));
	pm2_WR(p, PM2R_FRAMEBUFFER_WRITE_MASK, ~(0L));
	pm2_WR(p, PM2R_FIFO_CONTROL, 0);
	pm2_WR(p, PM2R_APERTURE_ONE, 0);
	pm2_WR(p, PM2R_APERTURE_TWO, 0);
	pm2_WR(p, PM2R_RASTERIZER_MODE, 0);
	pm2_WR(p, PM2R_DELTA_MODE, PM2F_DELTA_ORDER_RGB);
	pm2_WR(p, PM2R_LB_READ_FORMAT, 0);
	pm2_WR(p, PM2R_LB_WRITE_FORMAT, 0);
	pm2_WR(p, PM2R_LB_READ_MODE, 0);
	pm2_WR(p, PM2R_LB_SOURCE_OFFSET, 0);
	pm2_WR(p, PM2R_FB_SOURCE_OFFSET, 0);
	pm2_WR(p, PM2R_FB_PIXEL_OFFSET, 0);
	pm2_WR(p, PM2R_FB_WINDOW_BASE, 0);
	pm2_WR(p, PM2R_LB_WINDOW_BASE, 0);
	pm2_WR(p, PM2R_FB_SOFT_WRITE_MASK, ~(0L));
	pm2_WR(p, PM2R_FB_HARD_WRITE_MASK, ~(0L));
	pm2_WR(p, PM2R_FB_READ_PIXEL, 0);
	pm2_WR(p, PM2R_DITHER_MODE, 0);
	pm2_WR(p, PM2R_AREA_STIPPLE_MODE, 0);
	pm2_WR(p, PM2R_DEPTH_MODE, 0);
	pm2_WR(p, PM2R_STENCIL_MODE, 0);
	pm2_WR(p, PM2R_TEXTURE_ADDRESS_MODE, 0);
	pm2_WR(p, PM2R_TEXTURE_READ_MODE, 0);
	pm2_WR(p, PM2R_TEXEL_LUT_MODE, 0);
	pm2_WR(p, PM2R_YUV_MODE, 0);
	pm2_WR(p, PM2R_COLOR_DDA_MODE, 0);
	pm2_WR(p, PM2R_TEXTURE_COLOR_MODE, 0);
	pm2_WR(p, PM2R_FOG_MODE, 0);
	pm2_WR(p, PM2R_ALPHA_BLEND_MODE, 0);
	pm2_WR(p, PM2R_LOGICAL_OP_MODE, 0);
	pm2_WR(p, PM2R_STATISTICS_MODE, 0);
	pm2_WR(p, PM2R_SCISSOR_MODE, 0);
	pm2_WR(p, PM2R_FILTER_MODE, PM2F_SYNCHRONIZATION);
	pm2_WR(p, PM2R_RD_PIXEL_MASK, 0xff);
	चयन (p->type) अणु
	हाल PM2_TYPE_PERMEDIA2:
		pm2_RDAC_WR(p, PM2I_RD_MODE_CONTROL, 0); /* no overlay */
		pm2_RDAC_WR(p, PM2I_RD_CURSOR_CONTROL, 0);
		pm2_RDAC_WR(p, PM2I_RD_MISC_CONTROL, PM2F_RD_PALETTE_WIDTH_8);
		pm2_RDAC_WR(p, PM2I_RD_COLOR_KEY_CONTROL, 0);
		pm2_RDAC_WR(p, PM2I_RD_OVERLAY_KEY, 0);
		pm2_RDAC_WR(p, PM2I_RD_RED_KEY, 0);
		pm2_RDAC_WR(p, PM2I_RD_GREEN_KEY, 0);
		pm2_RDAC_WR(p, PM2I_RD_BLUE_KEY, 0);
		अवरोध;
	हाल PM2_TYPE_PERMEDIA2V:
		pm2v_RDAC_WR(p, PM2VI_RD_MISC_CONTROL, 1); /* 8bit */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम set_aperture(काष्ठा pm2fb_par *p, u32 depth)
अणु
	/*
	 * The hardware is little-endian. When used in big-endian
	 * hosts, the on-chip aperture settings are used where
	 * possible to translate from host to card byte order.
	 */
	WAIT_FIFO(p, 2);
#अगर_घोषित __LITTLE_ENDIAN
	pm2_WR(p, PM2R_APERTURE_ONE, PM2F_APERTURE_STANDARD);
#अन्यथा
	चयन (depth) अणु
	हाल 24:	/* RGB->BGR */
		/*
		 * We can't use the aperture to translate host to
		 * card byte order here, so we चयन to BGR mode
		 * in pm2fb_set_par().
		 */
	हाल 8:		/* B->B */
		pm2_WR(p, PM2R_APERTURE_ONE, PM2F_APERTURE_STANDARD);
		अवरोध;
	हाल 16:	/* HL->LH */
		pm2_WR(p, PM2R_APERTURE_ONE, PM2F_APERTURE_HALFWORDSWAP);
		अवरोध;
	हाल 32:	/* RGBA->ABGR */
		pm2_WR(p, PM2R_APERTURE_ONE, PM2F_APERTURE_BYTESWAP);
		अवरोध;
	पूर्ण
#पूर्ण_अगर

	/* We करोn't use aperture two, so this may be superflous */
	pm2_WR(p, PM2R_APERTURE_TWO, PM2F_APERTURE_STANDARD);
पूर्ण

अटल व्योम set_color(काष्ठा pm2fb_par *p, अचिन्हित अक्षर regno,
		      अचिन्हित अक्षर r, अचिन्हित अक्षर g, अचिन्हित अक्षर b)
अणु
	WAIT_FIFO(p, 4);
	pm2_WR(p, PM2R_RD_PALETTE_WRITE_ADDRESS, regno);
	wmb();
	pm2_WR(p, PM2R_RD_PALETTE_DATA, r);
	wmb();
	pm2_WR(p, PM2R_RD_PALETTE_DATA, g);
	wmb();
	pm2_WR(p, PM2R_RD_PALETTE_DATA, b);
पूर्ण

अटल व्योम set_memघड़ी(काष्ठा pm2fb_par *par, u32 clk)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर m, n, p;

	चयन (par->type) अणु
	हाल PM2_TYPE_PERMEDIA2V:
		pm2v_mnp(clk/2, &m, &n, &p);
		WAIT_FIFO(par, 12);
		pm2_WR(par, PM2VR_RD_INDEX_HIGH, PM2VI_RD_MCLK_CONTROL >> 8);
		pm2v_RDAC_WR(par, PM2VI_RD_MCLK_CONTROL, 0);
		pm2v_RDAC_WR(par, PM2VI_RD_MCLK_PRESCALE, m);
		pm2v_RDAC_WR(par, PM2VI_RD_MCLK_FEEDBACK, n);
		pm2v_RDAC_WR(par, PM2VI_RD_MCLK_POSTSCALE, p);
		pm2v_RDAC_WR(par, PM2VI_RD_MCLK_CONTROL, 1);
		rmb();
		क्रम (i = 256; i; i--)
			अगर (pm2v_RDAC_RD(par, PM2VI_RD_MCLK_CONTROL) & 2)
				अवरोध;
		pm2_WR(par, PM2VR_RD_INDEX_HIGH, 0);
		अवरोध;
	हाल PM2_TYPE_PERMEDIA2:
		pm2_mnp(clk, &m, &n, &p);
		WAIT_FIFO(par, 10);
		pm2_RDAC_WR(par, PM2I_RD_MEMORY_CLOCK_3, 6);
		pm2_RDAC_WR(par, PM2I_RD_MEMORY_CLOCK_1, m);
		pm2_RDAC_WR(par, PM2I_RD_MEMORY_CLOCK_2, n);
		pm2_RDAC_WR(par, PM2I_RD_MEMORY_CLOCK_3, 8|p);
		pm2_RDAC_RD(par, PM2I_RD_MEMORY_CLOCK_STATUS);
		rmb();
		क्रम (i = 256; i; i--)
			अगर (pm2_RD(par, PM2R_RD_INDEXED_DATA) & PM2F_PLL_LOCKED)
				अवरोध;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम set_pixघड़ी(काष्ठा pm2fb_par *par, u32 clk)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर m, n, p;

	चयन (par->type) अणु
	हाल PM2_TYPE_PERMEDIA2:
		pm2_mnp(clk, &m, &n, &p);
		WAIT_FIFO(par, 10);
		pm2_RDAC_WR(par, PM2I_RD_PIXEL_CLOCK_A3, 0);
		pm2_RDAC_WR(par, PM2I_RD_PIXEL_CLOCK_A1, m);
		pm2_RDAC_WR(par, PM2I_RD_PIXEL_CLOCK_A2, n);
		pm2_RDAC_WR(par, PM2I_RD_PIXEL_CLOCK_A3, 8|p);
		pm2_RDAC_RD(par, PM2I_RD_PIXEL_CLOCK_STATUS);
		rmb();
		क्रम (i = 256; i; i--)
			अगर (pm2_RD(par, PM2R_RD_INDEXED_DATA) & PM2F_PLL_LOCKED)
				अवरोध;
		अवरोध;
	हाल PM2_TYPE_PERMEDIA2V:
		pm2v_mnp(clk/2, &m, &n, &p);
		WAIT_FIFO(par, 8);
		pm2_WR(par, PM2VR_RD_INDEX_HIGH, PM2VI_RD_CLK0_PRESCALE >> 8);
		pm2v_RDAC_WR(par, PM2VI_RD_CLK0_PRESCALE, m);
		pm2v_RDAC_WR(par, PM2VI_RD_CLK0_FEEDBACK, n);
		pm2v_RDAC_WR(par, PM2VI_RD_CLK0_POSTSCALE, p);
		pm2_WR(par, PM2VR_RD_INDEX_HIGH, 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम set_video(काष्ठा pm2fb_par *p, u32 video)
अणु
	u32 पंचांगp;
	u32 vsync = video;

	DPRINTK("video = 0x%x\n", video);

	/*
	 * The hardware cursor needs +vsync to recognise vert retrace.
	 * We may not be using the hardware cursor, but the X Glपूर्णांक
	 * driver may well. So always set +hsync/+vsync and then set
	 * the RAMDAC to invert the sync अगर necessary.
	 */
	vsync &= ~(PM2F_HSYNC_MASK | PM2F_VSYNC_MASK);
	vsync |= PM2F_HSYNC_ACT_HIGH | PM2F_VSYNC_ACT_HIGH;

	WAIT_FIFO(p, 3);
	pm2_WR(p, PM2R_VIDEO_CONTROL, vsync);

	चयन (p->type) अणु
	हाल PM2_TYPE_PERMEDIA2:
		पंचांगp = PM2F_RD_PALETTE_WIDTH_8;
		अगर ((video & PM2F_HSYNC_MASK) == PM2F_HSYNC_ACT_LOW)
			पंचांगp |= 4; /* invert hsync */
		अगर ((video & PM2F_VSYNC_MASK) == PM2F_VSYNC_ACT_LOW)
			पंचांगp |= 8; /* invert vsync */
		pm2_RDAC_WR(p, PM2I_RD_MISC_CONTROL, पंचांगp);
		अवरोध;
	हाल PM2_TYPE_PERMEDIA2V:
		पंचांगp = 0;
		अगर ((video & PM2F_HSYNC_MASK) == PM2F_HSYNC_ACT_LOW)
			पंचांगp |= 1; /* invert hsync */
		अगर ((video & PM2F_VSYNC_MASK) == PM2F_VSYNC_ACT_LOW)
			पंचांगp |= 4; /* invert vsync */
		pm2v_RDAC_WR(p, PM2VI_RD_SYNC_CONTROL, पंचांगp);
		अवरोध;
	पूर्ण
पूर्ण

/*
 *	pm2fb_check_var - Optional function. Validates a var passed in.
 *	@var: frame buffer variable screen काष्ठाure
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 *
 *	Checks to see अगर the hardware supports the state requested by
 *	var passed in.
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 */
अटल पूर्णांक pm2fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	u32 lpitch;

	अगर (var->bits_per_pixel != 8  && var->bits_per_pixel != 16 &&
	    var->bits_per_pixel != 24 && var->bits_per_pixel != 32) अणु
		DPRINTK("depth not supported: %u\n", var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	अगर (var->xres != var->xres_भव) अणु
		DPRINTK("virtual x resolution != "
			"physical x resolution not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (var->yres > var->yres_भव) अणु
		DPRINTK("virtual y resolution < "
			"physical y resolution not possible\n");
		वापस -EINVAL;
	पूर्ण

	/* permedia cannot blit over 2048 */
	अगर (var->yres_भव > 2047) अणु
		var->yres_भव = 2047;
	पूर्ण

	अगर (var->xoffset) अणु
		DPRINTK("xoffset not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((var->vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED) अणु
		DPRINTK("interlace not supported\n");
		वापस -EINVAL;
	पूर्ण

	var->xres = (var->xres + 15) & ~15; /* could someबार be 8 */
	lpitch = var->xres * ((var->bits_per_pixel + 7) >> 3);

	अगर (var->xres < 320 || var->xres > 1600) अणु
		DPRINTK("width not supported: %u\n", var->xres);
		वापस -EINVAL;
	पूर्ण

	अगर (var->yres < 200 || var->yres > 1200) अणु
		DPRINTK("height not supported: %u\n", var->yres);
		वापस -EINVAL;
	पूर्ण

	अगर (lpitch * var->yres_भव > info->fix.smem_len) अणु
		DPRINTK("no memory for screen (%ux%ux%u)\n",
			var->xres, var->yres_भव, var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	अगर (PICOS2KHZ(var->pixघड़ी) > PM2_MAX_PIXCLOCK) अणु
		DPRINTK("pixclock too high (%ldKHz)\n",
			PICOS2KHZ(var->pixघड़ी));
		वापस -EINVAL;
	पूर्ण

	var->transp.offset = 0;
	var->transp.length = 0;
	चयन (var->bits_per_pixel) अणु
	हाल 8:
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		अवरोध;
	हाल 16:
		var->red.offset   = 11;
		var->red.length   = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset  = 0;
		var->blue.length  = 5;
		अवरोध;
	हाल 32:
		var->transp.offset = 24;
		var->transp.length = 8;
		var->red.offset	  = 16;
		var->green.offset = 8;
		var->blue.offset  = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		अवरोध;
	हाल 24:
#अगर_घोषित __BIG_ENDIAN
		var->red.offset   = 0;
		var->blue.offset  = 16;
#अन्यथा
		var->red.offset   = 16;
		var->blue.offset  = 0;
#पूर्ण_अगर
		var->green.offset = 8;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		अवरोध;
	पूर्ण
	var->height = -1;
	var->width = -1;

	var->accel_flags = 0;	/* Can't mmap अगर this is on */

	DPRINTK("Checking graphics mode at %dx%d depth %d\n",
		var->xres, var->yres, var->bits_per_pixel);
	वापस 0;
पूर्ण

/**
 *	pm2fb_set_par - Alters the hardware state.
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 *
 *	Using the fb_var_screeninfo in fb_info we set the resolution of the
 *	this particular framebuffer.
 */
अटल पूर्णांक pm2fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा pm2fb_par *par = info->par;
	u32 pixघड़ी;
	u32 width = (info->var.xres_भव + 7) & ~7;
	u32 height = info->var.yres_भव;
	u32 depth = (info->var.bits_per_pixel + 7) & ~7;
	u32 hsstart, hsend, hbend, htotal;
	u32 vsstart, vsend, vbend, vtotal;
	u32 stride;
	u32 base;
	u32 video = 0;
	u32 clrmode = PM2F_RD_COLOR_MODE_RGB | PM2F_RD_GUI_ACTIVE;
	u32 txपंचांगap = 0;
	u32 pixsize = 0;
	u32 clrक्रमmat = 0;
	u32 misc = 1; /* 8-bit DAC */
	u32 xres = (info->var.xres + 31) & ~31;
	पूर्णांक data64;

	reset_card(par);
	reset_config(par);
	clear_palette(par);
	अगर (par->memघड़ी)
		set_memघड़ी(par, par->memघड़ी);

	depth = (depth > 32) ? 32 : depth;
	data64 = depth > 8 || par->type == PM2_TYPE_PERMEDIA2V;

	pixघड़ी = PICOS2KHZ(info->var.pixघड़ी);
	अगर (pixघड़ी > PM2_MAX_PIXCLOCK) अणु
		DPRINTK("pixclock too high (%uKHz)\n", pixघड़ी);
		वापस -EINVAL;
	पूर्ण

	hsstart = to3264(info->var.right_margin, depth, data64);
	hsend = hsstart + to3264(info->var.hsync_len, depth, data64);
	hbend = hsend + to3264(info->var.left_margin, depth, data64);
	htotal = to3264(xres, depth, data64) + hbend - 1;
	vsstart = (info->var.lower_margin)
		? info->var.lower_margin - 1
		: 0;	/* FIXME! */
	vsend = info->var.lower_margin + info->var.vsync_len - 1;
	vbend = info->var.lower_margin + info->var.vsync_len +
		info->var.upper_margin;
	vtotal = info->var.yres + vbend - 1;
	stride = to3264(width, depth, 1);
	base = to3264(info->var.yoffset * xres + info->var.xoffset, depth, 1);
	अगर (data64)
		video |= PM2F_DATA_64_ENABLE;

	अगर (info->var.sync & FB_SYNC_HOR_HIGH_ACT) अणु
		अगर (lowhsync) अणु
			DPRINTK("ignoring +hsync, using -hsync.\n");
			video |= PM2F_HSYNC_ACT_LOW;
		पूर्ण अन्यथा
			video |= PM2F_HSYNC_ACT_HIGH;
	पूर्ण अन्यथा
		video |= PM2F_HSYNC_ACT_LOW;

	अगर (info->var.sync & FB_SYNC_VERT_HIGH_ACT) अणु
		अगर (lowvsync) अणु
			DPRINTK("ignoring +vsync, using -vsync.\n");
			video |= PM2F_VSYNC_ACT_LOW;
		पूर्ण अन्यथा
			video |= PM2F_VSYNC_ACT_HIGH;
	पूर्ण अन्यथा
		video |= PM2F_VSYNC_ACT_LOW;

	अगर ((info->var.vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED) अणु
		DPRINTK("interlaced not supported\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((info->var.vmode & FB_VMODE_MASK) == FB_VMODE_DOUBLE)
		video |= PM2F_LINE_DOUBLE;
	अगर ((info->var.activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_NOW)
		video |= PM2F_VIDEO_ENABLE;
	par->video = video;

	info->fix.visual =
		(depth == 8) ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	info->fix.line_length = info->var.xres * depth / 8;
	info->cmap.len = 256;

	/*
	 * Settings calculated. Now ग_लिखो them out.
	 */
	अगर (par->type == PM2_TYPE_PERMEDIA2V) अणु
		WAIT_FIFO(par, 1);
		pm2_WR(par, PM2VR_RD_INDEX_HIGH, 0);
	पूर्ण

	set_aperture(par, depth);

	mb();
	WAIT_FIFO(par, 19);
	चयन (depth) अणु
	हाल 8:
		pm2_WR(par, PM2R_FB_READ_PIXEL, 0);
		clrक्रमmat = 0x2e;
		अवरोध;
	हाल 16:
		pm2_WR(par, PM2R_FB_READ_PIXEL, 1);
		clrmode |= PM2F_RD_TRUECOLOR | PM2F_RD_PIXELFORMAT_RGB565;
		txपंचांगap = PM2F_TEXTEL_SIZE_16;
		pixsize = 1;
		clrक्रमmat = 0x70;
		misc |= 8;
		अवरोध;
	हाल 32:
		pm2_WR(par, PM2R_FB_READ_PIXEL, 2);
		clrmode |= PM2F_RD_TRUECOLOR | PM2F_RD_PIXELFORMAT_RGBA8888;
		txपंचांगap = PM2F_TEXTEL_SIZE_32;
		pixsize = 2;
		clrक्रमmat = 0x20;
		misc |= 8;
		अवरोध;
	हाल 24:
		pm2_WR(par, PM2R_FB_READ_PIXEL, 4);
		clrmode |= PM2F_RD_TRUECOLOR | PM2F_RD_PIXELFORMAT_RGB888;
		txपंचांगap = PM2F_TEXTEL_SIZE_24;
		pixsize = 4;
		clrक्रमmat = 0x20;
		misc |= 8;
		अवरोध;
	पूर्ण
	pm2_WR(par, PM2R_FB_WRITE_MODE, PM2F_FB_WRITE_ENABLE);
	pm2_WR(par, PM2R_FB_READ_MODE, partprod(xres));
	pm2_WR(par, PM2R_LB_READ_MODE, partprod(xres));
	pm2_WR(par, PM2R_TEXTURE_MAP_FORMAT, txपंचांगap | partprod(xres));
	pm2_WR(par, PM2R_H_TOTAL, htotal);
	pm2_WR(par, PM2R_HS_START, hsstart);
	pm2_WR(par, PM2R_HS_END, hsend);
	pm2_WR(par, PM2R_HG_END, hbend);
	pm2_WR(par, PM2R_HB_END, hbend);
	pm2_WR(par, PM2R_V_TOTAL, vtotal);
	pm2_WR(par, PM2R_VS_START, vsstart);
	pm2_WR(par, PM2R_VS_END, vsend);
	pm2_WR(par, PM2R_VB_END, vbend);
	pm2_WR(par, PM2R_SCREEN_STRIDE, stride);
	wmb();
	pm2_WR(par, PM2R_WINDOW_ORIGIN, 0);
	pm2_WR(par, PM2R_SCREEN_SIZE, (height << 16) | width);
	pm2_WR(par, PM2R_SCISSOR_MODE, PM2F_SCREEN_SCISSOR_ENABLE);
	wmb();
	pm2_WR(par, PM2R_SCREEN_BASE, base);
	wmb();
	set_video(par, video);
	WAIT_FIFO(par, 10);
	चयन (par->type) अणु
	हाल PM2_TYPE_PERMEDIA2:
		pm2_RDAC_WR(par, PM2I_RD_COLOR_MODE, clrmode);
		pm2_RDAC_WR(par, PM2I_RD_COLOR_KEY_CONTROL,
				(depth == 8) ? 0 : PM2F_COLOR_KEY_TEST_OFF);
		अवरोध;
	हाल PM2_TYPE_PERMEDIA2V:
		pm2v_RDAC_WR(par, PM2VI_RD_DAC_CONTROL, 0);
		pm2v_RDAC_WR(par, PM2VI_RD_PIXEL_SIZE, pixsize);
		pm2v_RDAC_WR(par, PM2VI_RD_COLOR_FORMAT, clrक्रमmat);
		pm2v_RDAC_WR(par, PM2VI_RD_MISC_CONTROL, misc);
		pm2v_RDAC_WR(par, PM2VI_RD_OVERLAY_KEY, 0);
		अवरोध;
	पूर्ण
	set_pixघड़ी(par, pixघड़ी);
	DPRINTK("Setting graphics mode at %dx%d depth %d\n",
		info->var.xres, info->var.yres, info->var.bits_per_pixel);
	वापस 0;
पूर्ण

/**
 *	pm2fb_setcolreg - Sets a color रेजिस्टर.
 *	@regno: boolean, 0 copy local, 1 get_user() function
 *	@red: frame buffer colormap काष्ठाure
 *	@green: The green value which can be up to 16 bits wide
 *	@blue:  The blue value which can be up to 16 bits wide.
 *	@transp: If supported the alpha value which can be up to 16 bits wide.
 *	@info: frame buffer info काष्ठाure
 *
 *	Set a single color रेजिस्टर. The values supplied have a 16 bit
 *	magnitude which needs to be scaled in this function क्रम the hardware.
 *	Pretty much a direct lअगरt from tdfxfb.c.
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 */
अटल पूर्णांक pm2fb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp,
			   काष्ठा fb_info *info)
अणु
	काष्ठा pm2fb_par *par = info->par;

	अगर (regno >= info->cmap.len)  /* no. of hw रेजिस्टरs */
		वापस -EINVAL;
	/*
	 * Program hardware... करो anything you want with transp
	 */

	/* grayscale works only partially under directcolor */
	/* grayscale = 0.30*R + 0.59*G + 0.11*B */
	अगर (info->var.grayscale)
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;

	/* Directcolor:
	 *   var->अणुcolorपूर्ण.offset contains start of bitfield
	 *   var->अणुcolorपूर्ण.length contains length of bitfield
	 *   अणुhardwarespecअगरicपूर्ण contains width of DAC
	 *   cmap[X] is programmed to
	 *   (X << red.offset) | (X << green.offset) | (X << blue.offset)
	 *   RAMDAC[X] is programmed to (red, green, blue)
	 *
	 * Pseuकरोcolor:
	 *    uses offset = 0 && length = DAC रेजिस्टर width.
	 *    var->अणुcolorपूर्ण.offset is 0
	 *    var->अणुcolorपूर्ण.length contains width of DAC
	 *    cmap is not used
	 *    DAC[X] is programmed to (red, green, blue)
	 * Truecolor:
	 *    करोes not use RAMDAC (usually has 3 of them).
	 *    var->अणुcolorपूर्ण.offset contains start of bitfield
	 *    var->अणुcolorपूर्ण.length contains length of bitfield
	 *    cmap is programmed to
	 *    (red << red.offset) | (green << green.offset) |
	 *    (blue << blue.offset) | (transp << transp.offset)
	 *    RAMDAC करोes not exist
	 */
#घोषणा CNVT_TOHW(val, width) ((((val) << (width)) + 0x7FFF -(val)) >> 16)
	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
	हाल FB_VISUAL_PSEUDOCOLOR:
		red = CNVT_TOHW(red, info->var.red.length);
		green = CNVT_TOHW(green, info->var.green.length);
		blue = CNVT_TOHW(blue, info->var.blue.length);
		transp = CNVT_TOHW(transp, info->var.transp.length);
		अवरोध;
	हाल FB_VISUAL_सूचीECTCOLOR:
		/* example here assumes 8 bit DAC. Might be dअगरferent
		 * क्रम your hardware */
		red = CNVT_TOHW(red, 8);
		green = CNVT_TOHW(green, 8);
		blue = CNVT_TOHW(blue, 8);
		/* hey, there is bug in transp handling... */
		transp = CNVT_TOHW(transp, 8);
		अवरोध;
	पूर्ण
#अघोषित CNVT_TOHW
	/* Truecolor has hardware independent palette */
	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR) अणु
		u32 v;

		अगर (regno >= 16)
			वापस -EINVAL;

		v = (red << info->var.red.offset) |
			(green << info->var.green.offset) |
			(blue << info->var.blue.offset) |
			(transp << info->var.transp.offset);

		चयन (info->var.bits_per_pixel) अणु
		हाल 8:
			अवरोध;
		हाल 16:
		हाल 24:
		हाल 32:
			par->palette[regno] = v;
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा अगर (info->fix.visual == FB_VISUAL_PSEUDOCOLOR)
		set_color(par, regno, red, green, blue);

	वापस 0;
पूर्ण

/**
 *	pm2fb_pan_display - Pans the display.
 *	@var: frame buffer variable screen काष्ठाure
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 *
 *	Pan (or wrap, depending on the `vmode' field) the display using the
 *	`xoffset' and `yoffset' fields of the `var' काष्ठाure.
 *	If the values करोn't fit, वापस -EINVAL.
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 *
 */
अटल पूर्णांक pm2fb_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	काष्ठा pm2fb_par *p = info->par;
	u32 base;
	u32 depth = (info->var.bits_per_pixel + 7) & ~7;
	u32 xres = (info->var.xres + 31) & ~31;

	depth = (depth > 32) ? 32 : depth;
	base = to3264(var->yoffset * xres + var->xoffset, depth, 1);
	WAIT_FIFO(p, 1);
	pm2_WR(p, PM2R_SCREEN_BASE, base);
	वापस 0;
पूर्ण

/**
 *	pm2fb_blank - Blanks the display.
 *	@blank_mode: the blank mode we want.
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 *
 *	Blank the screen अगर blank_mode != 0, अन्यथा unblank. Return 0 अगर
 *	blanking succeeded, != 0 अगर un-/blanking failed due to e.g. a
 *	video mode which करोesn't support it. Implements VESA suspend
 *	and घातerकरोwn modes on hardware that supports disabling hsync/vsync:
 *	blank_mode == 2: suspend vsync
 *	blank_mode == 3: suspend hsync
 *	blank_mode == 4: घातerकरोwn
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 *
 */
अटल पूर्णांक pm2fb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा pm2fb_par *par = info->par;
	u32 video = par->video;

	DPRINTK("blank_mode %d\n", blank_mode);

	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		/* Screen: On */
		video |= PM2F_VIDEO_ENABLE;
		अवरोध;
	हाल FB_BLANK_NORMAL:
		/* Screen: Off */
		video &= ~PM2F_VIDEO_ENABLE;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		/* VSync: Off */
		video &= ~(PM2F_VSYNC_MASK | PM2F_BLANK_LOW);
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		/* HSync: Off */
		video &= ~(PM2F_HSYNC_MASK | PM2F_BLANK_LOW);
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		/* HSync: Off, VSync: Off */
		video &= ~(PM2F_VSYNC_MASK | PM2F_HSYNC_MASK | PM2F_BLANK_LOW);
		अवरोध;
	पूर्ण
	set_video(par, video);
	वापस 0;
पूर्ण

अटल पूर्णांक pm2fb_sync(काष्ठा fb_info *info)
अणु
	काष्ठा pm2fb_par *par = info->par;

	WAIT_FIFO(par, 1);
	pm2_WR(par, PM2R_SYNC, 0);
	mb();
	करो अणु
		जबतक (pm2_RD(par, PM2R_OUT_FIFO_WORDS) == 0)
			cpu_relax();
	पूर्ण जबतक (pm2_RD(par, PM2R_OUT_FIFO) != PM2TAG(PM2R_SYNC));

	वापस 0;
पूर्ण

अटल व्योम pm2fb_fillrect(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_fillrect *region)
अणु
	काष्ठा pm2fb_par *par = info->par;
	काष्ठा fb_fillrect modded;
	पूर्णांक vxres, vyres;
	u32 color = (info->fix.visual == FB_VISUAL_TRUECOLOR) ?
		((u32 *)info->pseuकरो_palette)[region->color] : region->color;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;
	अगर ((info->flags & FBINFO_HWACCEL_DISABLED) ||
		region->rop != ROP_COPY ) अणु
		cfb_fillrect(info, region);
		वापस;
	पूर्ण

	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;

	स_नकल(&modded, region, माप(काष्ठा fb_fillrect));

	अगर (!modded.width || !modded.height ||
	    modded.dx >= vxres || modded.dy >= vyres)
		वापस;

	अगर (modded.dx + modded.width  > vxres)
		modded.width  = vxres - modded.dx;
	अगर (modded.dy + modded.height > vyres)
		modded.height = vyres - modded.dy;

	अगर (info->var.bits_per_pixel == 8)
		color |= color << 8;
	अगर (info->var.bits_per_pixel <= 16)
		color |= color << 16;

	WAIT_FIFO(par, 3);
	pm2_WR(par, PM2R_CONFIG, PM2F_CONFIG_FB_WRITE_ENABLE);
	pm2_WR(par, PM2R_RECTANGLE_ORIGIN, (modded.dy << 16) | modded.dx);
	pm2_WR(par, PM2R_RECTANGLE_SIZE, (modded.height << 16) | modded.width);
	अगर (info->var.bits_per_pixel != 24) अणु
		WAIT_FIFO(par, 2);
		pm2_WR(par, PM2R_FB_BLOCK_COLOR, color);
		wmb();
		pm2_WR(par, PM2R_RENDER,
				PM2F_RENDER_RECTANGLE | PM2F_RENDER_FASTFILL);
	पूर्ण अन्यथा अणु
		WAIT_FIFO(par, 4);
		pm2_WR(par, PM2R_COLOR_DDA_MODE, 1);
		pm2_WR(par, PM2R_CONSTANT_COLOR, color);
		wmb();
		pm2_WR(par, PM2R_RENDER,
				PM2F_RENDER_RECTANGLE |
				PM2F_INCREASE_X | PM2F_INCREASE_Y );
		pm2_WR(par, PM2R_COLOR_DDA_MODE, 0);
	पूर्ण
पूर्ण

अटल व्योम pm2fb_copyarea(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा pm2fb_par *par = info->par;
	काष्ठा fb_copyarea modded;
	u32 vxres, vyres;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;
	अगर (info->flags & FBINFO_HWACCEL_DISABLED) अणु
		cfb_copyarea(info, area);
		वापस;
	पूर्ण

	स_नकल(&modded, area, माप(काष्ठा fb_copyarea));

	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;

	अगर (!modded.width || !modded.height ||
	    modded.sx >= vxres || modded.sy >= vyres ||
	    modded.dx >= vxres || modded.dy >= vyres)
		वापस;

	अगर (modded.sx + modded.width > vxres)
		modded.width = vxres - modded.sx;
	अगर (modded.dx + modded.width > vxres)
		modded.width = vxres - modded.dx;
	अगर (modded.sy + modded.height > vyres)
		modded.height = vyres - modded.sy;
	अगर (modded.dy + modded.height > vyres)
		modded.height = vyres - modded.dy;

	WAIT_FIFO(par, 5);
	pm2_WR(par, PM2R_CONFIG, PM2F_CONFIG_FB_WRITE_ENABLE |
		PM2F_CONFIG_FB_READ_SOURCE_ENABLE);
	pm2_WR(par, PM2R_FB_SOURCE_DELTA,
			((modded.sy - modded.dy) & 0xfff) << 16 |
			((modded.sx - modded.dx) & 0xfff));
	pm2_WR(par, PM2R_RECTANGLE_ORIGIN, (modded.dy << 16) | modded.dx);
	pm2_WR(par, PM2R_RECTANGLE_SIZE, (modded.height << 16) | modded.width);
	wmb();
	pm2_WR(par, PM2R_RENDER, PM2F_RENDER_RECTANGLE |
				(modded.dx < modded.sx ? PM2F_INCREASE_X : 0) |
				(modded.dy < modded.sy ? PM2F_INCREASE_Y : 0));
पूर्ण

अटल व्योम pm2fb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा pm2fb_par *par = info->par;
	u32 height = image->height;
	u32 fgx, bgx;
	स्थिर u32 *src = (स्थिर u32 *)image->data;
	u32 xres = (info->var.xres + 31) & ~31;
	पूर्णांक raster_mode = 1; /* invert bits */

#अगर_घोषित __LITTLE_ENDIAN
	raster_mode |= 3 << 7; /* reverse byte order */
#पूर्ण_अगर

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;
	अगर (info->flags & FBINFO_HWACCEL_DISABLED || image->depth != 1) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण
	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_PSEUDOCOLOR:
		fgx = image->fg_color;
		bgx = image->bg_color;
		अवरोध;
	हाल FB_VISUAL_TRUECOLOR:
	शेष:
		fgx = par->palette[image->fg_color];
		bgx = par->palette[image->bg_color];
		अवरोध;
	पूर्ण
	अगर (info->var.bits_per_pixel == 8) अणु
		fgx |= fgx << 8;
		bgx |= bgx << 8;
	पूर्ण
	अगर (info->var.bits_per_pixel <= 16) अणु
		fgx |= fgx << 16;
		bgx |= bgx << 16;
	पूर्ण

	WAIT_FIFO(par, 13);
	pm2_WR(par, PM2R_FB_READ_MODE, partprod(xres));
	pm2_WR(par, PM2R_SCISSOR_MIN_XY,
			((image->dy & 0xfff) << 16) | (image->dx & 0x0fff));
	pm2_WR(par, PM2R_SCISSOR_MAX_XY,
			(((image->dy + image->height) & 0x0fff) << 16) |
			((image->dx + image->width) & 0x0fff));
	pm2_WR(par, PM2R_SCISSOR_MODE, 1);
	/* GXcopy & UNIT_ENABLE */
	pm2_WR(par, PM2R_LOGICAL_OP_MODE, (0x3 << 1) | 1);
	pm2_WR(par, PM2R_RECTANGLE_ORIGIN,
			((image->dy & 0xfff) << 16) | (image->dx & 0x0fff));
	pm2_WR(par, PM2R_RECTANGLE_SIZE,
			((image->height & 0x0fff) << 16) |
			((image->width) & 0x0fff));
	अगर (info->var.bits_per_pixel == 24) अणु
		pm2_WR(par, PM2R_COLOR_DDA_MODE, 1);
		/* clear area */
		pm2_WR(par, PM2R_CONSTANT_COLOR, bgx);
		pm2_WR(par, PM2R_RENDER,
			PM2F_RENDER_RECTANGLE |
			PM2F_INCREASE_X | PM2F_INCREASE_Y);
		/* BitMapPackEachScanline */
		pm2_WR(par, PM2R_RASTERIZER_MODE, raster_mode | (1 << 9));
		pm2_WR(par, PM2R_CONSTANT_COLOR, fgx);
		pm2_WR(par, PM2R_RENDER,
			PM2F_RENDER_RECTANGLE |
			PM2F_INCREASE_X | PM2F_INCREASE_Y |
			PM2F_RENDER_SYNC_ON_BIT_MASK);
	पूर्ण अन्यथा अणु
		pm2_WR(par, PM2R_COLOR_DDA_MODE, 0);
		/* clear area */
		pm2_WR(par, PM2R_FB_BLOCK_COLOR, bgx);
		pm2_WR(par, PM2R_RENDER,
			PM2F_RENDER_RECTANGLE |
			PM2F_RENDER_FASTFILL |
			PM2F_INCREASE_X | PM2F_INCREASE_Y);
		pm2_WR(par, PM2R_RASTERIZER_MODE, raster_mode);
		pm2_WR(par, PM2R_FB_BLOCK_COLOR, fgx);
		pm2_WR(par, PM2R_RENDER,
			PM2F_RENDER_RECTANGLE |
			PM2F_INCREASE_X | PM2F_INCREASE_Y |
			PM2F_RENDER_FASTFILL |
			PM2F_RENDER_SYNC_ON_BIT_MASK);
	पूर्ण

	जबतक (height--) अणु
		पूर्णांक width = ((image->width + 7) >> 3)
				+ info->pixmap.scan_align - 1;
		width >>= 2;
		WAIT_FIFO(par, width);
		जबतक (width--) अणु
			pm2_WR(par, PM2R_BIT_MASK_PATTERN, *src);
			src++;
		पूर्ण
	पूर्ण
	WAIT_FIFO(par, 3);
	pm2_WR(par, PM2R_RASTERIZER_MODE, 0);
	pm2_WR(par, PM2R_COLOR_DDA_MODE, 0);
	pm2_WR(par, PM2R_SCISSOR_MODE, 0);
पूर्ण

/*
 *	Hardware cursor support.
 */
अटल स्थिर u8 cursor_bits_lookup[16] = अणु
	0x00, 0x40, 0x10, 0x50, 0x04, 0x44, 0x14, 0x54,
	0x01, 0x41, 0x11, 0x51, 0x05, 0x45, 0x15, 0x55
पूर्ण;

अटल पूर्णांक pm2vfb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा pm2fb_par *par = info->par;
	u8 mode = PM2F_CURSORMODE_TYPE_X;
	पूर्णांक x = cursor->image.dx - info->var.xoffset;
	पूर्णांक y = cursor->image.dy - info->var.yoffset;

	अगर (cursor->enable)
		mode |= PM2F_CURSORMODE_CURSOR_ENABLE;

	pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_MODE, mode);

	अगर (!cursor->enable)
		x = 2047;	/* push it outside display */
	pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_X_LOW, x & 0xff);
	pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_X_HIGH, (x >> 8) & 0xf);
	pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_Y_LOW, y & 0xff);
	pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_Y_HIGH, (y >> 8) & 0xf);

	/*
	 * If the cursor is not be changed this means either we want the
	 * current cursor state (अगर enable is set) or we want to query what
	 * we can करो with the cursor (अगर enable is not set)
	 */
	अगर (!cursor->set)
		वापस 0;

	अगर (cursor->set & FB_CUR_SETHOT) अणु
		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_X_HOT,
			     cursor->hot.x & 0x3f);
		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_Y_HOT,
			     cursor->hot.y & 0x3f);
	पूर्ण

	अगर (cursor->set & FB_CUR_SETCMAP) अणु
		u32 fg_idx = cursor->image.fg_color;
		u32 bg_idx = cursor->image.bg_color;
		काष्ठा fb_cmap cmap = info->cmap;

		/* the X11 driver says one should use these color रेजिस्टरs */
		pm2_WR(par, PM2VR_RD_INDEX_HIGH, PM2VI_RD_CURSOR_PALETTE >> 8);
		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_PALETTE + 0,
			     cmap.red[bg_idx] >> 8 );
		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_PALETTE + 1,
			     cmap.green[bg_idx] >> 8 );
		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_PALETTE + 2,
			     cmap.blue[bg_idx] >> 8 );

		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_PALETTE + 3,
			     cmap.red[fg_idx] >> 8 );
		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_PALETTE + 4,
			     cmap.green[fg_idx] >> 8 );
		pm2v_RDAC_WR(par, PM2VI_RD_CURSOR_PALETTE + 5,
			     cmap.blue[fg_idx] >> 8 );
		pm2_WR(par, PM2VR_RD_INDEX_HIGH, 0);
	पूर्ण

	अगर (cursor->set & (FB_CUR_SETSHAPE | FB_CUR_SETIMAGE)) अणु
		u8 *biपंचांगap = (u8 *)cursor->image.data;
		u8 *mask = (u8 *)cursor->mask;
		पूर्णांक i;
		पूर्णांक pos = PM2VI_RD_CURSOR_PATTERN;

		क्रम (i = 0; i < cursor->image.height; i++) अणु
			पूर्णांक j = (cursor->image.width + 7) >> 3;
			पूर्णांक k = 8 - j;

			pm2_WR(par, PM2VR_RD_INDEX_HIGH, pos >> 8);

			क्रम (; j > 0; j--) अणु
				u8 data = *biपंचांगap ^ *mask;

				अगर (cursor->rop == ROP_COPY)
					data = *mask & *biपंचांगap;
				/* Upper 4 bits of biपंचांगap data */
				pm2v_RDAC_WR(par, pos++,
					cursor_bits_lookup[data >> 4] |
					(cursor_bits_lookup[*mask >> 4] << 1));
				/* Lower 4 bits of biपंचांगap */
				pm2v_RDAC_WR(par, pos++,
					cursor_bits_lookup[data & 0xf] |
					(cursor_bits_lookup[*mask & 0xf] << 1));
				biपंचांगap++;
				mask++;
			पूर्ण
			क्रम (; k > 0; k--) अणु
				pm2v_RDAC_WR(par, pos++, 0);
				pm2v_RDAC_WR(par, pos++, 0);
			पूर्ण
		पूर्ण

		जबतक (pos < (1024 + PM2VI_RD_CURSOR_PATTERN)) अणु
			pm2_WR(par, PM2VR_RD_INDEX_HIGH, pos >> 8);
			pm2v_RDAC_WR(par, pos++, 0);
		पूर्ण

		pm2_WR(par, PM2VR_RD_INDEX_HIGH, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pm2fb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा pm2fb_par *par = info->par;
	u8 mode;

	अगर (!hwcursor)
		वापस -EINVAL;	/* just to क्रमce soft_cursor() call */

	/* Too large of a cursor or wrong bpp :-( */
	अगर (cursor->image.width > 64 ||
	    cursor->image.height > 64 ||
	    cursor->image.depth > 1)
		वापस -EINVAL;

	अगर (par->type == PM2_TYPE_PERMEDIA2V)
		वापस pm2vfb_cursor(info, cursor);

	mode = 0x40;
	अगर (cursor->enable)
		 mode = 0x43;

	pm2_RDAC_WR(par, PM2I_RD_CURSOR_CONTROL, mode);

	/*
	 * If the cursor is not be changed this means either we want the
	 * current cursor state (अगर enable is set) or we want to query what
	 * we can करो with the cursor (अगर enable is not set)
	 */
	अगर (!cursor->set)
		वापस 0;

	अगर (cursor->set & FB_CUR_SETPOS) अणु
		पूर्णांक x = cursor->image.dx - info->var.xoffset + 63;
		पूर्णांक y = cursor->image.dy - info->var.yoffset + 63;

		WAIT_FIFO(par, 4);
		pm2_WR(par, PM2R_RD_CURSOR_X_LSB, x & 0xff);
		pm2_WR(par, PM2R_RD_CURSOR_X_MSB, (x >> 8) & 0x7);
		pm2_WR(par, PM2R_RD_CURSOR_Y_LSB, y & 0xff);
		pm2_WR(par, PM2R_RD_CURSOR_Y_MSB, (y >> 8) & 0x7);
	पूर्ण

	अगर (cursor->set & FB_CUR_SETCMAP) अणु
		u32 fg_idx = cursor->image.fg_color;
		u32 bg_idx = cursor->image.bg_color;

		WAIT_FIFO(par, 7);
		pm2_WR(par, PM2R_RD_CURSOR_COLOR_ADDRESS, 1);
		pm2_WR(par, PM2R_RD_CURSOR_COLOR_DATA,
			info->cmap.red[bg_idx] >> 8);
		pm2_WR(par, PM2R_RD_CURSOR_COLOR_DATA,
			info->cmap.green[bg_idx] >> 8);
		pm2_WR(par, PM2R_RD_CURSOR_COLOR_DATA,
			info->cmap.blue[bg_idx] >> 8);

		pm2_WR(par, PM2R_RD_CURSOR_COLOR_DATA,
			info->cmap.red[fg_idx] >> 8);
		pm2_WR(par, PM2R_RD_CURSOR_COLOR_DATA,
			info->cmap.green[fg_idx] >> 8);
		pm2_WR(par, PM2R_RD_CURSOR_COLOR_DATA,
			info->cmap.blue[fg_idx] >> 8);
	पूर्ण

	अगर (cursor->set & (FB_CUR_SETSHAPE | FB_CUR_SETIMAGE)) अणु
		u8 *biपंचांगap = (u8 *)cursor->image.data;
		u8 *mask = (u8 *)cursor->mask;
		पूर्णांक i;

		WAIT_FIFO(par, 1);
		pm2_WR(par, PM2R_RD_PALETTE_WRITE_ADDRESS, 0);

		क्रम (i = 0; i < cursor->image.height; i++) अणु
			पूर्णांक j = (cursor->image.width + 7) >> 3;
			पूर्णांक k = 8 - j;

			WAIT_FIFO(par, 8);
			क्रम (; j > 0; j--) अणु
				u8 data = *biपंचांगap ^ *mask;

				अगर (cursor->rop == ROP_COPY)
					data = *mask & *biपंचांगap;
				/* biपंचांगap data */
				pm2_WR(par, PM2R_RD_CURSOR_DATA, data);
				biपंचांगap++;
				mask++;
			पूर्ण
			क्रम (; k > 0; k--)
				pm2_WR(par, PM2R_RD_CURSOR_DATA, 0);
		पूर्ण
		क्रम (; i < 64; i++) अणु
			पूर्णांक j = 8;
			WAIT_FIFO(par, 8);
			जबतक (j-- > 0)
				pm2_WR(par, PM2R_RD_CURSOR_DATA, 0);
		पूर्ण

		mask = (u8 *)cursor->mask;
		क्रम (i = 0; i < cursor->image.height; i++) अणु
			पूर्णांक j = (cursor->image.width + 7) >> 3;
			पूर्णांक k = 8 - j;

			WAIT_FIFO(par, 8);
			क्रम (; j > 0; j--) अणु
				/* mask */
				pm2_WR(par, PM2R_RD_CURSOR_DATA, *mask);
				mask++;
			पूर्ण
			क्रम (; k > 0; k--)
				pm2_WR(par, PM2R_RD_CURSOR_DATA, 0);
		पूर्ण
		क्रम (; i < 64; i++) अणु
			पूर्णांक j = 8;
			WAIT_FIFO(par, 8);
			जबतक (j-- > 0)
				pm2_WR(par, PM2R_RD_CURSOR_DATA, 0);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* ------------ Hardware Independent Functions ------------ */

/*
 *  Frame buffer operations
 */

अटल स्थिर काष्ठा fb_ops pm2fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= pm2fb_check_var,
	.fb_set_par	= pm2fb_set_par,
	.fb_setcolreg	= pm2fb_setcolreg,
	.fb_blank	= pm2fb_blank,
	.fb_pan_display	= pm2fb_pan_display,
	.fb_fillrect	= pm2fb_fillrect,
	.fb_copyarea	= pm2fb_copyarea,
	.fb_imageblit	= pm2fb_imageblit,
	.fb_sync	= pm2fb_sync,
	.fb_cursor	= pm2fb_cursor,
पूर्ण;

/*
 * PCI stuff
 */


/**
 * Device initialisation
 *
 * Initialise and allocate resource क्रम PCI device.
 *
 * @pdev:	PCI device.
 * @id:		PCI device ID.
 */
अटल पूर्णांक pm2fb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा pm2fb_par *शेष_par;
	काष्ठा fb_info *info;
	पूर्णांक err;
	पूर्णांक retval = -ENXIO;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "pm2fb: Can't enable pdev: %d\n", err);
		वापस err;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा pm2fb_par), &pdev->dev);
	अगर (!info)
		वापस -ENOMEM;
	शेष_par = info->par;

	चयन (pdev->device) अणु
	हाल  PCI_DEVICE_ID_TI_TVP4020:
		म_नकल(pm2fb_fix.id, "TVP4020");
		शेष_par->type = PM2_TYPE_PERMEDIA2;
		अवरोध;
	हाल  PCI_DEVICE_ID_3DLABS_PERMEDIA2:
		म_नकल(pm2fb_fix.id, "Permedia2");
		शेष_par->type = PM2_TYPE_PERMEDIA2;
		अवरोध;
	हाल  PCI_DEVICE_ID_3DLABS_PERMEDIA2V:
		म_नकल(pm2fb_fix.id, "Permedia2v");
		शेष_par->type = PM2_TYPE_PERMEDIA2V;
		अवरोध;
	पूर्ण

	pm2fb_fix.mmio_start = pci_resource_start(pdev, 0);
	pm2fb_fix.mmio_len = PM2_REGS_SIZE;

#अगर defined(__BIG_ENDIAN)
	/*
	 * PM2 has a 64k रेजिस्टर file, mapped twice in 128k. Lower
	 * map is little-endian, upper map is big-endian.
	 */
	pm2fb_fix.mmio_start += PM2_REGS_SIZE;
	DPRINTK("Adjusting register base for big-endian.\n");
#पूर्ण_अगर
	DPRINTK("Register base at 0x%lx\n", pm2fb_fix.mmio_start);

	/* Registers - request region and map it. */
	अगर (!request_mem_region(pm2fb_fix.mmio_start, pm2fb_fix.mmio_len,
				"pm2fb regbase")) अणु
		prपूर्णांकk(KERN_WARNING "pm2fb: Can't reserve regbase.\n");
		जाओ err_निकास_neither;
	पूर्ण
	शेष_par->v_regs =
		ioremap(pm2fb_fix.mmio_start, pm2fb_fix.mmio_len);
	अगर (!शेष_par->v_regs) अणु
		prपूर्णांकk(KERN_WARNING "pm2fb: Can't remap %s register area.\n",
		       pm2fb_fix.id);
		release_mem_region(pm2fb_fix.mmio_start, pm2fb_fix.mmio_len);
		जाओ err_निकास_neither;
	पूर्ण

	/* Stash away memory रेजिस्टर info क्रम use when we reset the board */
	शेष_par->mem_control = pm2_RD(शेष_par, PM2R_MEM_CONTROL);
	शेष_par->boot_address = pm2_RD(शेष_par, PM2R_BOOT_ADDRESS);
	शेष_par->mem_config = pm2_RD(शेष_par, PM2R_MEM_CONFIG);
	DPRINTK("MemControl 0x%x BootAddress 0x%x MemConfig 0x%x\n",
		शेष_par->mem_control, शेष_par->boot_address,
		शेष_par->mem_config);

	अगर (शेष_par->mem_control == 0 &&
		शेष_par->boot_address == 0x31 &&
		शेष_par->mem_config == 0x259fffff) अणु
		शेष_par->memघड़ी = CVPPC_MEMCLOCK;
		शेष_par->mem_control = 0;
		शेष_par->boot_address = 0x20;
		शेष_par->mem_config = 0xe6002021;
		अगर (pdev->subप्रणाली_venकरोr == 0x1048 &&
			pdev->subप्रणाली_device == 0x0a31) अणु
			DPRINTK("subsystem_vendor: %04x, "
				"subsystem_device: %04x\n",
				pdev->subप्रणाली_venकरोr, pdev->subप्रणाली_device);
			DPRINTK("We have not been initialized by VGA BIOS and "
				"are running on an Elsa Winner 2000 Office\n");
			DPRINTK("Initializing card timings manually...\n");
			शेष_par->memघड़ी = 100000;
		पूर्ण
		अगर (pdev->subप्रणाली_venकरोr == 0x3d3d &&
			pdev->subप्रणाली_device == 0x0100) अणु
			DPRINTK("subsystem_vendor: %04x, "
				"subsystem_device: %04x\n",
				pdev->subप्रणाली_venकरोr, pdev->subप्रणाली_device);
			DPRINTK("We have not been initialized by VGA BIOS and "
				"are running on an 3dlabs reference board\n");
			DPRINTK("Initializing card timings manually...\n");
			शेष_par->memघड़ी = 74894;
		पूर्ण
	पूर्ण

	/* Now work out how big lfb is going to be. */
	चयन (शेष_par->mem_config & PM2F_MEM_CONFIG_RAM_MASK) अणु
	हाल PM2F_MEM_BANKS_1:
		pm2fb_fix.smem_len = 0x200000;
		अवरोध;
	हाल PM2F_MEM_BANKS_2:
		pm2fb_fix.smem_len = 0x400000;
		अवरोध;
	हाल PM2F_MEM_BANKS_3:
		pm2fb_fix.smem_len = 0x600000;
		अवरोध;
	हाल PM2F_MEM_BANKS_4:
		pm2fb_fix.smem_len = 0x800000;
		अवरोध;
	पूर्ण
	pm2fb_fix.smem_start = pci_resource_start(pdev, 1);

	/* Linear frame buffer - request region and map it. */
	अगर (!request_mem_region(pm2fb_fix.smem_start, pm2fb_fix.smem_len,
				"pm2fb smem")) अणु
		prपूर्णांकk(KERN_WARNING "pm2fb: Can't reserve smem.\n");
		जाओ err_निकास_mmio;
	पूर्ण
	info->screen_base =
		ioremap_wc(pm2fb_fix.smem_start, pm2fb_fix.smem_len);
	अगर (!info->screen_base) अणु
		prपूर्णांकk(KERN_WARNING "pm2fb: Can't ioremap smem area.\n");
		release_mem_region(pm2fb_fix.smem_start, pm2fb_fix.smem_len);
		जाओ err_निकास_mmio;
	पूर्ण

	अगर (!nomtrr)
		शेष_par->wc_cookie = arch_phys_wc_add(pm2fb_fix.smem_start,
							  pm2fb_fix.smem_len);

	info->fbops		= &pm2fb_ops;
	info->fix		= pm2fb_fix;
	info->pseuकरो_palette	= शेष_par->palette;
	info->flags		= FBINFO_DEFAULT |
				  FBINFO_HWACCEL_YPAN |
				  FBINFO_HWACCEL_COPYAREA |
				  FBINFO_HWACCEL_IMAGEBLIT |
				  FBINFO_HWACCEL_FILLRECT;

	info->pixmap.addr = kदो_स्मृति(PM2_PIXMAP_SIZE, GFP_KERNEL);
	अगर (!info->pixmap.addr) अणु
		retval = -ENOMEM;
		जाओ err_निकास_pixmap;
	पूर्ण
	info->pixmap.size = PM2_PIXMAP_SIZE;
	info->pixmap.buf_align = 4;
	info->pixmap.scan_align = 4;
	info->pixmap.access_align = 32;
	info->pixmap.flags = FB_PIXMAP_SYSTEM;

	अगर (noaccel) अणु
		prपूर्णांकk(KERN_DEBUG "disabling acceleration\n");
		info->flags |= FBINFO_HWACCEL_DISABLED;
		info->pixmap.scan_align = 1;
	पूर्ण

	अगर (!mode_option)
		mode_option = "640x480@60";

	err = fb_find_mode(&info->var, info, mode_option, शून्य, 0, शून्य, 8);
	अगर (!err || err == 4)
		info->var = pm2fb_var;

	retval = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (retval < 0)
		जाओ err_निकास_both;

	retval = रेजिस्टर_framebuffer(info);
	अगर (retval < 0)
		जाओ err_निकास_all;

	fb_info(info, "%s frame buffer device, memory = %dK\n",
		info->fix.id, pm2fb_fix.smem_len / 1024);

	/*
	 * Our driver data
	 */
	pci_set_drvdata(pdev, info);

	वापस 0;

 err_निकास_all:
	fb_dealloc_cmap(&info->cmap);
 err_निकास_both:
	kमुक्त(info->pixmap.addr);
 err_निकास_pixmap:
	iounmap(info->screen_base);
	release_mem_region(pm2fb_fix.smem_start, pm2fb_fix.smem_len);
 err_निकास_mmio:
	iounmap(शेष_par->v_regs);
	release_mem_region(pm2fb_fix.mmio_start, pm2fb_fix.mmio_len);
 err_निकास_neither:
	framebuffer_release(info);
	वापस retval;
पूर्ण

/**
 * Device removal.
 *
 * Release all device resources.
 *
 * @pdev:	PCI device to clean up.
 */
अटल व्योम pm2fb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pdev);
	काष्ठा fb_fix_screeninfo *fix = &info->fix;
	काष्ठा pm2fb_par *par = info->par;

	unरेजिस्टर_framebuffer(info);
	arch_phys_wc_del(par->wc_cookie);
	iounmap(info->screen_base);
	release_mem_region(fix->smem_start, fix->smem_len);
	iounmap(par->v_regs);
	release_mem_region(fix->mmio_start, fix->mmio_len);

	fb_dealloc_cmap(&info->cmap);
	kमुक्त(info->pixmap.addr);
	framebuffer_release(info);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pm2fb_id_table[] = अणु
	अणु PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_TVP4020,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_3DLABS, PCI_DEVICE_ID_3DLABS_PERMEDIA2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_3DLABS, PCI_DEVICE_ID_3DLABS_PERMEDIA2V,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver pm2fb_driver = अणु
	.name		= "pm2fb",
	.id_table	= pm2fb_id_table,
	.probe		= pm2fb_probe,
	.हटाओ		= pm2fb_हटाओ,
पूर्ण;

MODULE_DEVICE_TABLE(pci, pm2fb_id_table);


#अगर_अघोषित MODULE
/*
 * Parse user specअगरied options.
 *
 * This is, comma-separated options following `video=pm2fb:'.
 */
अटल पूर्णांक __init pm2fb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt)
			जारी;
		अगर (!म_भेद(this_opt, "lowhsync"))
			lowhsync = 1;
		अन्यथा अगर (!म_भेद(this_opt, "lowvsync"))
			lowvsync = 1;
		अन्यथा अगर (!म_भेदन(this_opt, "hwcursor=", 9))
			hwcursor = simple_म_से_अदीर्घ(this_opt + 9, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "nomtrr", 6))
			nomtrr = 1;
		अन्यथा अगर (!म_भेदन(this_opt, "noaccel", 7))
			noaccel = 1;
		अन्यथा
			mode_option = this_opt;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर


अटल पूर्णांक __init pm2fb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("pm2fb", &option))
		वापस -ENODEV;
	pm2fb_setup(option);
#पूर्ण_अगर

	वापस pci_रेजिस्टर_driver(&pm2fb_driver);
पूर्ण

module_init(pm2fb_init);

#अगर_घोषित MODULE
/*
 *  Cleanup
 */

अटल व्योम __निकास pm2fb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pm2fb_driver);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित MODULE
module_निकास(pm2fb_निकास);

module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Initial video mode e.g. '648x480-8@60'");
module_param_named(mode, mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode, "Initial video mode e.g. '648x480-8@60' (deprecated)");
module_param(lowhsync, bool, 0);
MODULE_PARM_DESC(lowhsync, "Force horizontal sync low regardless of mode");
module_param(lowvsync, bool, 0);
MODULE_PARM_DESC(lowvsync, "Force vertical sync low regardless of mode");
module_param(noaccel, bool, 0);
MODULE_PARM_DESC(noaccel, "Disable acceleration");
module_param(hwcursor, पूर्णांक, 0644);
MODULE_PARM_DESC(hwcursor, "Enable hardware cursor "
			"(1=enable, 0=disable, default=1)");
module_param(nomtrr, bool, 0);
MODULE_PARM_DESC(nomtrr, "Disable MTRR support (0 or 1=disabled) (default=0)");

MODULE_AUTHOR("Jim Hague <jim.hague@acm.org>");
MODULE_DESCRIPTION("Permedia2 framebuffer device driver");
MODULE_LICENSE("GPL");
#पूर्ण_अगर
