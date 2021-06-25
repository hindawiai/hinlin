<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* leo.c: LEO frame buffer driver
 *
 * Copyright (C) 2003, 2006 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1996-1999 Jakub Jelinek (jj@ultra.linux.cz)
 * Copyright (C) 1997 Michal Rehacek (Michal.Rehacek@st.mff.cuni.cz)
 *
 * Driver layout based loosely on tgafb.c, see that file क्रम credits.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/fb.h>
#समावेश <linux/mm.h>
#समावेश <linux/of_device.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/fbपन.स>

#समावेश "sbuslib.h"

/*
 * Local functions.
 */

अटल पूर्णांक leo_setcolreg(अचिन्हित, अचिन्हित, अचिन्हित, अचिन्हित,
			 अचिन्हित, काष्ठा fb_info *);
अटल पूर्णांक leo_blank(पूर्णांक, काष्ठा fb_info *);

अटल पूर्णांक leo_mmap(काष्ठा fb_info *, काष्ठा vm_area_काष्ठा *);
अटल पूर्णांक leo_ioctl(काष्ठा fb_info *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
अटल पूर्णांक leo_pan_display(काष्ठा fb_var_screeninfo *, काष्ठा fb_info *);

/*
 *  Frame buffer operations
 */

अटल स्थिर काष्ठा fb_ops leo_ops = अणु
	.owner			= THIS_MODULE,
	.fb_setcolreg		= leo_setcolreg,
	.fb_blank		= leo_blank,
	.fb_pan_display		= leo_pan_display,
	.fb_fillrect		= cfb_fillrect,
	.fb_copyarea		= cfb_copyarea,
	.fb_imageblit		= cfb_imageblit,
	.fb_mmap		= leo_mmap,
	.fb_ioctl		= leo_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.fb_compat_ioctl	= sbusfb_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

#घोषणा LEO_OFF_LC_SS0_KRN	0x00200000UL
#घोषणा LEO_OFF_LC_SS0_USR	0x00201000UL
#घोषणा LEO_OFF_LC_SS1_KRN	0x01200000UL
#घोषणा LEO_OFF_LC_SS1_USR	0x01201000UL
#घोषणा LEO_OFF_LD_SS0		0x00400000UL
#घोषणा LEO_OFF_LD_SS1		0x01400000UL
#घोषणा LEO_OFF_LD_GBL		0x00401000UL
#घोषणा LEO_OFF_LX_KRN		0x00600000UL
#घोषणा LEO_OFF_LX_CURSOR	0x00601000UL
#घोषणा LEO_OFF_SS0		0x00800000UL
#घोषणा LEO_OFF_SS1		0x01800000UL
#घोषणा LEO_OFF_UNK		0x00602000UL
#घोषणा LEO_OFF_UNK2		0x00000000UL

#घोषणा LEO_CUR_ENABLE		0x00000080
#घोषणा LEO_CUR_UPDATE		0x00000030
#घोषणा LEO_CUR_PROGRESS	0x00000006
#घोषणा LEO_CUR_UPDATECMAP	0x00000003

#घोषणा LEO_CUR_TYPE_MASK	0x00000000
#घोषणा LEO_CUR_TYPE_IMAGE	0x00000020
#घोषणा LEO_CUR_TYPE_CMAP	0x00000050

काष्ठा leo_cursor अणु
	u8	xxx0[16];
	u32	cur_type;
	u32	cur_misc;
	u32	cur_cursxy;
	u32	cur_data;
पूर्ण;

#घोषणा LEO_KRN_TYPE_CLUT0	0x00001000
#घोषणा LEO_KRN_TYPE_CLUT1	0x00001001
#घोषणा LEO_KRN_TYPE_CLUT2	0x00001002
#घोषणा LEO_KRN_TYPE_WID	0x00001003
#घोषणा LEO_KRN_TYPE_UNK	0x00001006
#घोषणा LEO_KRN_TYPE_VIDEO	0x00002003
#घोषणा LEO_KRN_TYPE_CLUTDATA	0x00004000
#घोषणा LEO_KRN_CSR_ENABLE	0x00000008
#घोषणा LEO_KRN_CSR_PROGRESS	0x00000004
#घोषणा LEO_KRN_CSR_UNK		0x00000002
#घोषणा LEO_KRN_CSR_UNK2	0x00000001

काष्ठा leo_lx_krn अणु
	u32	krn_type;
	u32	krn_csr;
	u32	krn_value;
पूर्ण;

काष्ठा leo_lc_ss0_krn अणु
	u32 	misc;
	u8	xxx0[0x800-4];
	u32	rev;
पूर्ण;

काष्ठा leo_lc_ss0_usr अणु
	u32	csr;
	u32	addrspace;
	u32 	fonपंचांगsk;
	u32	fontt;
	u32	extent;
	u32	src;
	u32	dst;
	u32	copy;
	u32	fill;
पूर्ण;

काष्ठा leo_lc_ss1_krn अणु
	u8	unknown;
पूर्ण;

काष्ठा leo_lc_ss1_usr अणु
	u8	unknown;
पूर्ण;

काष्ठा leo_ld_ss0 अणु
	u8	xxx0[0xe00];
	u32	csr;
	u32	wid;
	u32	wmask;
	u32	widclip;
	u32	vclipmin;
	u32	vclipmax;
	u32	pickmin;	/* SS1 only */
	u32	pickmax;	/* SS1 only */
	u32	fg;
	u32	bg;
	u32	src;		/* Copy/Scroll (SS0 only) */
	u32	dst;		/* Copy/Scroll/Fill (SS0 only) */
	u32	extent;		/* Copy/Scroll/Fill size (SS0 only) */
	u32	xxx1[3];
	u32	setsem;		/* SS1 only */
	u32	clrsem;		/* SS1 only */
	u32	clrpick;	/* SS1 only */
	u32	clrdat;		/* SS1 only */
	u32	alpha;		/* SS1 only */
	u8	xxx2[0x2c];
	u32	winbg;
	u32	planemask;
	u32	rop;
	u32	z;
	u32	dczf;		/* SS1 only */
	u32	dczb;		/* SS1 only */
	u32	dcs;		/* SS1 only */
	u32	dczs;		/* SS1 only */
	u32	pickfb;		/* SS1 only */
	u32	pickbb;		/* SS1 only */
	u32	dcfc;		/* SS1 only */
	u32	क्रमcecol;	/* SS1 only */
	u32	करोor[8];	/* SS1 only */
	u32	pick[5];	/* SS1 only */
पूर्ण;

#घोषणा LEO_SS1_MISC_ENABLE	0x00000001
#घोषणा LEO_SS1_MISC_STEREO	0x00000002
काष्ठा leo_ld_ss1 अणु
	u8	xxx0[0xef4];
	u32	ss1_misc;
पूर्ण;

काष्ठा leo_ld_gbl अणु
	u8	unknown;
पूर्ण;

काष्ठा leo_par अणु
	spinlock_t		lock;
	काष्ठा leo_lx_krn	__iomem *lx_krn;
	काष्ठा leo_lc_ss0_usr	__iomem *lc_ss0_usr;
	काष्ठा leo_ld_ss0	__iomem *ld_ss0;
	काष्ठा leo_ld_ss1	__iomem *ld_ss1;
	काष्ठा leo_cursor	__iomem *cursor;
	u32			extent;
	u32			clut_data[256];

	u32			flags;
#घोषणा LEO_FLAG_BLANKED	0x00000001

	अचिन्हित दीर्घ		which_io;
पूर्ण;

अटल व्योम leo_रुको(काष्ठा leo_lx_krn __iomem *lx_krn)
अणु
	पूर्णांक i;

	क्रम (i = 0;
	     (sbus_पढ़ोl(&lx_krn->krn_csr) & LEO_KRN_CSR_PROGRESS) &&
	     i < 300000;
	     i++)
		udelay(1); /* Busy रुको at most 0.3 sec */
	वापस;
पूर्ण

अटल व्योम leo_चयन_from_graph(काष्ठा fb_info *info)
अणु
	काष्ठा leo_par *par = (काष्ठा leo_par *) info->par;
	काष्ठा leo_ld_ss0 __iomem *ss = par->ld_ss0;
	काष्ठा leo_cursor __iomem *cursor = par->cursor;
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&par->lock, flags);

	par->extent = ((info->var.xres - 1) |
		       ((info->var.yres - 1) << 16));

	sbus_ग_लिखोl(0xffffffff, &ss->wid);
	sbus_ग_लिखोl(0xffff, &ss->wmask);
	sbus_ग_लिखोl(0, &ss->vclipmin);
	sbus_ग_लिखोl(par->extent, &ss->vclipmax);
	sbus_ग_लिखोl(0, &ss->fg);
	sbus_ग_लिखोl(0xff000000, &ss->planemask);
	sbus_ग_लिखोl(0x310850, &ss->rop);
	sbus_ग_लिखोl(0, &ss->widclip);
	sbus_ग_लिखोl((info->var.xres-1) | ((info->var.yres-1) << 11),
		    &par->lc_ss0_usr->extent);
	sbus_ग_लिखोl(4, &par->lc_ss0_usr->addrspace);
	sbus_ग_लिखोl(0x80000000, &par->lc_ss0_usr->fill);
	sbus_ग_लिखोl(0, &par->lc_ss0_usr->fontt);
	करो अणु
		val = sbus_पढ़ोl(&par->lc_ss0_usr->csr);
	पूर्ण जबतक (val & 0x20000000);

	/* setup screen buffer क्रम cfb_* functions */
	sbus_ग_लिखोl(1, &ss->wid);
	sbus_ग_लिखोl(0x00ffffff, &ss->planemask);
	sbus_ग_लिखोl(0x310b90, &ss->rop);
	sbus_ग_लिखोl(0, &par->lc_ss0_usr->addrspace);

	/* hide cursor */
	sbus_ग_लिखोl(sbus_पढ़ोl(&cursor->cur_misc) & ~LEO_CUR_ENABLE, &cursor->cur_misc);

	spin_unlock_irqrestore(&par->lock, flags);
पूर्ण

अटल पूर्णांक leo_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	/* We just use this to catch चयनes out of
	 * graphics mode.
	 */
	leo_चयन_from_graph(info);

	अगर (var->xoffset || var->yoffset || var->vmode)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/**
 *      leo_setcolreg - Optional function. Sets a color रेजिस्टर.
 *      @regno: boolean, 0 copy local, 1 get_user() function
 *      @red: frame buffer colormap काष्ठाure
 *      @green: The green value which can be up to 16 bits wide
 *      @blue:  The blue value which can be up to 16 bits wide.
 *      @transp: If supported the alpha value which can be up to 16 bits wide.
 *      @info: frame buffer info काष्ठाure
 */
अटल पूर्णांक leo_setcolreg(अचिन्हित regno,
			 अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			 अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा leo_par *par = (काष्ठा leo_par *) info->par;
	काष्ठा leo_lx_krn __iomem *lx_krn = par->lx_krn;
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक i;

	अगर (regno >= 256)
		वापस 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	par->clut_data[regno] = red | (green << 8) | (blue << 16);

	spin_lock_irqsave(&par->lock, flags);

	leo_रुको(lx_krn);

	sbus_ग_लिखोl(LEO_KRN_TYPE_CLUTDATA, &lx_krn->krn_type);
	क्रम (i = 0; i < 256; i++)
		sbus_ग_लिखोl(par->clut_data[i], &lx_krn->krn_value);
	sbus_ग_लिखोl(LEO_KRN_TYPE_CLUT0, &lx_krn->krn_type);

	val = sbus_पढ़ोl(&lx_krn->krn_csr);
	val |= (LEO_KRN_CSR_UNK | LEO_KRN_CSR_UNK2);
	sbus_ग_लिखोl(val, &lx_krn->krn_csr);

	spin_unlock_irqrestore(&par->lock, flags);

	वापस 0;
पूर्ण

/**
 *      leo_blank - Optional function.  Blanks the display.
 *      @blank: the blank mode we want.
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 */
अटल पूर्णांक leo_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा leo_par *par = (काष्ठा leo_par *) info->par;
	काष्ठा leo_lx_krn __iomem *lx_krn = par->lx_krn;
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&par->lock, flags);

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK: /* Unblanking */
		val = sbus_पढ़ोl(&lx_krn->krn_csr);
		val |= LEO_KRN_CSR_ENABLE;
		sbus_ग_लिखोl(val, &lx_krn->krn_csr);
		par->flags &= ~LEO_FLAG_BLANKED;
		अवरोध;

	हाल FB_BLANK_NORMAL: /* Normal blanking */
	हाल FB_BLANK_VSYNC_SUSPEND: /* VESA blank (vsync off) */
	हाल FB_BLANK_HSYNC_SUSPEND: /* VESA blank (hsync off) */
	हाल FB_BLANK_POWERDOWN: /* Poweroff */
		val = sbus_पढ़ोl(&lx_krn->krn_csr);
		val &= ~LEO_KRN_CSR_ENABLE;
		sbus_ग_लिखोl(val, &lx_krn->krn_csr);
		par->flags |= LEO_FLAG_BLANKED;
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&par->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा sbus_mmap_map leo_mmap_map[] = अणु
	अणु
		.voff	= LEO_SS0_MAP,
		.poff	= LEO_OFF_SS0,
		.size	= 0x800000
	पूर्ण,
	अणु
		.voff	= LEO_LC_SS0_USR_MAP,
		.poff	= LEO_OFF_LC_SS0_USR,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= LEO_LD_SS0_MAP,
		.poff	= LEO_OFF_LD_SS0,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= LEO_LX_CURSOR_MAP,
		.poff	= LEO_OFF_LX_CURSOR,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= LEO_SS1_MAP,
		.poff	= LEO_OFF_SS1,
		.size	= 0x800000
	पूर्ण,
	अणु
		.voff	= LEO_LC_SS1_USR_MAP,
		.poff	= LEO_OFF_LC_SS1_USR,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= LEO_LD_SS1_MAP,
		.poff	= LEO_OFF_LD_SS1,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= LEO_UNK_MAP,
		.poff	= LEO_OFF_UNK,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= LEO_LX_KRN_MAP,
		.poff	= LEO_OFF_LX_KRN,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= LEO_LC_SS0_KRN_MAP,
		.poff	= LEO_OFF_LC_SS0_KRN,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= LEO_LC_SS1_KRN_MAP,
		.poff	= LEO_OFF_LC_SS1_KRN,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= LEO_LD_GBL_MAP,
		.poff	= LEO_OFF_LD_GBL,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= LEO_UNK2_MAP,
		.poff	= LEO_OFF_UNK2,
		.size	= 0x100000
	पूर्ण,
	अणु .size = 0 पूर्ण
पूर्ण;

अटल पूर्णांक leo_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा leo_par *par = (काष्ठा leo_par *)info->par;

	वापस sbusfb_mmap_helper(leo_mmap_map,
				  info->fix.smem_start, info->fix.smem_len,
				  par->which_io, vma);
पूर्ण

अटल पूर्णांक leo_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस sbusfb_ioctl_helper(cmd, arg, info,
				   FBTYPE_SUNLEO, 32, info->fix.smem_len);
पूर्ण

/*
 *  Initialisation
 */

अटल व्योम
leo_init_fix(काष्ठा fb_info *info, काष्ठा device_node *dp)
अणु
	snम_लिखो(info->fix.id, माप(info->fix.id), "%pOFn", dp);

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_TRUECOLOR;

	info->fix.line_length = 8192;

	info->fix.accel = FB_ACCEL_SUN_LEO;
पूर्ण

अटल व्योम leo_wid_put(काष्ठा fb_info *info, काष्ठा fb_wid_list *wl)
अणु
	काष्ठा leo_par *par = (काष्ठा leo_par *) info->par;
	काष्ठा leo_lx_krn __iomem *lx_krn = par->lx_krn;
	काष्ठा fb_wid_item *wi;
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक i, j;

	spin_lock_irqsave(&par->lock, flags);

	leo_रुको(lx_krn);

	क्रम (i = 0, wi = wl->wl_list; i < wl->wl_count; i++, wi++) अणु
		चयन (wi->wi_type) अणु
		हाल FB_WID_DBL_8:
			j = (wi->wi_index & 0xf) + 0x40;
			अवरोध;

		हाल FB_WID_DBL_24:
			j = wi->wi_index & 0x3f;
			अवरोध;

		शेष:
			जारी;
		पूर्ण
		sbus_ग_लिखोl(0x5800 + j, &lx_krn->krn_type);
		sbus_ग_लिखोl(wi->wi_values[0], &lx_krn->krn_value);
	पूर्ण
	sbus_ग_लिखोl(LEO_KRN_TYPE_WID, &lx_krn->krn_type);

	val = sbus_पढ़ोl(&lx_krn->krn_csr);
	val |= (LEO_KRN_CSR_UNK | LEO_KRN_CSR_UNK2);
	sbus_ग_लिखोl(val, &lx_krn->krn_csr);

	spin_unlock_irqrestore(&par->lock, flags);
पूर्ण

अटल व्योम leo_init_wids(काष्ठा fb_info *info)
अणु
	काष्ठा fb_wid_item wi;
	काष्ठा fb_wid_list wl;

	wl.wl_count = 1;
	wl.wl_list = &wi;
	wi.wi_type = FB_WID_DBL_8;
	wi.wi_index = 0;
	wi.wi_values [0] = 0x2c0;
	leo_wid_put(info, &wl);
	wi.wi_index = 1;
	wi.wi_values [0] = 0x30;
	leo_wid_put(info, &wl);
	wi.wi_index = 2;
	wi.wi_values [0] = 0x20;
	leo_wid_put(info, &wl);
	wi.wi_type = FB_WID_DBL_24;
	wi.wi_index = 1;
	wi.wi_values [0] = 0x30;
	leo_wid_put(info, &wl);
पूर्ण

अटल व्योम leo_init_hw(काष्ठा fb_info *info)
अणु
	काष्ठा leo_par *par = (काष्ठा leo_par *) info->par;
	u32 val;

	val = sbus_पढ़ोl(&par->ld_ss1->ss1_misc);
	val |= LEO_SS1_MISC_ENABLE;
	sbus_ग_लिखोl(val, &par->ld_ss1->ss1_misc);

	leo_चयन_from_graph(info);
पूर्ण

अटल व्योम leo_fixup_var_rgb(काष्ठा fb_var_screeninfo *var)
अणु
	var->red.offset = 0;
	var->red.length = 8;
	var->green.offset = 8;
	var->green.length = 8;
	var->blue.offset = 16;
	var->blue.length = 8;
	var->transp.offset = 0;
	var->transp.length = 0;
पूर्ण

अटल व्योम leo_unmap_regs(काष्ठा platक्रमm_device *op, काष्ठा fb_info *info,
			   काष्ठा leo_par *par)
अणु
	अगर (par->lc_ss0_usr)
		of_iounmap(&op->resource[0], par->lc_ss0_usr, 0x1000);
	अगर (par->ld_ss0)
		of_iounmap(&op->resource[0], par->ld_ss0, 0x1000);
	अगर (par->ld_ss1)
		of_iounmap(&op->resource[0], par->ld_ss1, 0x1000);
	अगर (par->lx_krn)
		of_iounmap(&op->resource[0], par->lx_krn, 0x1000);
	अगर (par->cursor)
		of_iounmap(&op->resource[0],
			   par->cursor, माप(काष्ठा leo_cursor));
	अगर (info->screen_base)
		of_iounmap(&op->resource[0], info->screen_base, 0x800000);
पूर्ण

अटल पूर्णांक leo_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा fb_info *info;
	काष्ठा leo_par *par;
	पूर्णांक linebytes, err;

	info = framebuffer_alloc(माप(काष्ठा leo_par), &op->dev);

	err = -ENOMEM;
	अगर (!info)
		जाओ out_err;
	par = info->par;

	spin_lock_init(&par->lock);

	info->fix.smem_start = op->resource[0].start;
	par->which_io = op->resource[0].flags & IORESOURCE_BITS;

	sbusfb_fill_var(&info->var, dp, 32);
	leo_fixup_var_rgb(&info->var);

	linebytes = of_getपूर्णांकprop_शेष(dp, "linebytes",
					  info->var.xres);
	info->fix.smem_len = PAGE_ALIGN(linebytes * info->var.yres);

	par->lc_ss0_usr =
		of_ioremap(&op->resource[0], LEO_OFF_LC_SS0_USR,
			   0x1000, "leolc ss0usr");
	par->ld_ss0 =
		of_ioremap(&op->resource[0], LEO_OFF_LD_SS0,
			   0x1000, "leold ss0");
	par->ld_ss1 =
		of_ioremap(&op->resource[0], LEO_OFF_LD_SS1,
			   0x1000, "leold ss1");
	par->lx_krn =
		of_ioremap(&op->resource[0], LEO_OFF_LX_KRN,
			   0x1000, "leolx krn");
	par->cursor =
		of_ioremap(&op->resource[0], LEO_OFF_LX_CURSOR,
			   माप(काष्ठा leo_cursor), "leolx cursor");
	info->screen_base =
		of_ioremap(&op->resource[0], LEO_OFF_SS0,
			   0x800000, "leo ram");
	अगर (!par->lc_ss0_usr ||
	    !par->ld_ss0 ||
	    !par->ld_ss1 ||
	    !par->lx_krn ||
	    !par->cursor ||
	    !info->screen_base)
		जाओ out_unmap_regs;

	info->flags = FBINFO_DEFAULT;
	info->fbops = &leo_ops;
	info->pseuकरो_palette = par->clut_data;

	leo_init_wids(info);
	leo_init_hw(info);

	leo_blank(FB_BLANK_UNBLANK, info);

	अगर (fb_alloc_cmap(&info->cmap, 256, 0))
		जाओ out_unmap_regs;

	leo_init_fix(info, dp);

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0)
		जाओ out_dealloc_cmap;

	dev_set_drvdata(&op->dev, info);

	prपूर्णांकk(KERN_INFO "%pOF: leo at %lx:%lx\n",
	       dp,
	       par->which_io, info->fix.smem_start);

	वापस 0;

out_dealloc_cmap:
	fb_dealloc_cmap(&info->cmap);

out_unmap_regs:
	leo_unmap_regs(op, info, par);
	framebuffer_release(info);

out_err:
	वापस err;
पूर्ण

अटल पूर्णांक leo_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(&op->dev);
	काष्ठा leo_par *par = info->par;

	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);

	leo_unmap_regs(op, info, par);

	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id leo_match[] = अणु
	अणु
		.name = "SUNW,leo",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, leo_match);

अटल काष्ठा platक्रमm_driver leo_driver = अणु
	.driver = अणु
		.name = "leo",
		.of_match_table = leo_match,
	पूर्ण,
	.probe		= leo_probe,
	.हटाओ		= leo_हटाओ,
पूर्ण;

अटल पूर्णांक __init leo_init(व्योम)
अणु
	अगर (fb_get_options("leofb", शून्य))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&leo_driver);
पूर्ण

अटल व्योम __निकास leo_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&leo_driver);
पूर्ण

module_init(leo_init);
module_निकास(leo_निकास);

MODULE_DESCRIPTION("framebuffer driver for LEO chipsets");
MODULE_AUTHOR("David S. Miller <davem@davemloft.net>");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
