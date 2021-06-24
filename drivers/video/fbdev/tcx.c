<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* tcx.c: TCX frame buffer driver
 *
 * Copyright (C) 2003, 2006 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1996,1998 Jakub Jelinek (jj@ultra.linux.cz)
 * Copyright (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)
 * Copyright (C) 1996 Eddie C. Dost (ecd@skynet.be)
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

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/fbपन.स>

#समावेश "sbuslib.h"

/*
 * Local functions.
 */

अटल पूर्णांक tcx_setcolreg(अचिन्हित, अचिन्हित, अचिन्हित, अचिन्हित,
			 अचिन्हित, काष्ठा fb_info *);
अटल पूर्णांक tcx_blank(पूर्णांक, काष्ठा fb_info *);

अटल पूर्णांक tcx_mmap(काष्ठा fb_info *, काष्ठा vm_area_काष्ठा *);
अटल पूर्णांक tcx_ioctl(काष्ठा fb_info *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
अटल पूर्णांक tcx_pan_display(काष्ठा fb_var_screeninfo *, काष्ठा fb_info *);

/*
 *  Frame buffer operations
 */

अटल स्थिर काष्ठा fb_ops tcx_ops = अणु
	.owner			= THIS_MODULE,
	.fb_setcolreg		= tcx_setcolreg,
	.fb_blank		= tcx_blank,
	.fb_pan_display		= tcx_pan_display,
	.fb_fillrect		= cfb_fillrect,
	.fb_copyarea		= cfb_copyarea,
	.fb_imageblit		= cfb_imageblit,
	.fb_mmap		= tcx_mmap,
	.fb_ioctl		= tcx_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.fb_compat_ioctl	= sbusfb_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

/* THC definitions */
#घोषणा TCX_THC_MISC_REV_SHIFT       16
#घोषणा TCX_THC_MISC_REV_MASK        15
#घोषणा TCX_THC_MISC_VSYNC_DIS       (1 << 25)
#घोषणा TCX_THC_MISC_HSYNC_DIS       (1 << 24)
#घोषणा TCX_THC_MISC_RESET           (1 << 12)
#घोषणा TCX_THC_MISC_VIDEO           (1 << 10)
#घोषणा TCX_THC_MISC_SYNC            (1 << 9)
#घोषणा TCX_THC_MISC_VSYNC           (1 << 8)
#घोषणा TCX_THC_MISC_SYNC_ENAB       (1 << 7)
#घोषणा TCX_THC_MISC_CURS_RES        (1 << 6)
#घोषणा TCX_THC_MISC_INT_ENAB        (1 << 5)
#घोषणा TCX_THC_MISC_INT             (1 << 4)
#घोषणा TCX_THC_MISC_INIT            0x9f
#घोषणा TCX_THC_REV_REV_SHIFT        20
#घोषणा TCX_THC_REV_REV_MASK         15
#घोषणा TCX_THC_REV_MINREV_SHIFT     28
#घोषणा TCX_THC_REV_MINREV_MASK      15

/* The contents are unknown */
काष्ठा tcx_tec अणु
	u32 tec_matrix;
	u32 tec_clip;
	u32 tec_vdc;
पूर्ण;

काष्ठा tcx_thc अणु
	u32 thc_rev;
	u32 thc_pad0[511];
	u32 thc_hs;		/* hsync timing */
	u32 thc_hsdvs;
	u32 thc_hd;
	u32 thc_vs;		/* vsync timing */
	u32 thc_vd;
	u32 thc_refresh;
	u32 thc_misc;
	u32 thc_pad1[56];
	u32 thc_cursxy;	/* cursor x,y position (16 bits each) */
	u32 thc_cursmask[32];	/* cursor mask bits */
	u32 thc_cursbits[32];	/* what to show where mask enabled */
पूर्ण;

काष्ठा bt_regs अणु
	u32 addr;
	u32 color_map;
	u32 control;
	u32 cursor;
पूर्ण;

#घोषणा TCX_MMAP_ENTRIES 14

काष्ठा tcx_par अणु
	spinlock_t		lock;
	काष्ठा bt_regs		__iomem *bt;
	काष्ठा tcx_thc		__iomem *thc;
	काष्ठा tcx_tec		__iomem *tec;
	u32			__iomem *cplane;

	u32			flags;
#घोषणा TCX_FLAG_BLANKED	0x00000001

	अचिन्हित दीर्घ		which_io;

	काष्ठा sbus_mmap_map	mmap_map[TCX_MMAP_ENTRIES];
	पूर्णांक			lowdepth;
पूर्ण;

/* Reset control plane so that WID is 8-bit plane. */
अटल व्योम __tcx_set_control_plane(काष्ठा fb_info *info)
अणु
	काष्ठा tcx_par *par = info->par;
	u32 __iomem *p, *pend;

	अगर (par->lowdepth)
		वापस;

	p = par->cplane;
	अगर (p == शून्य)
		वापस;
	क्रम (pend = p + info->fix.smem_len; p < pend; p++) अणु
		u32 पंचांगp = sbus_पढ़ोl(p);

		पंचांगp &= 0xffffff;
		sbus_ग_लिखोl(पंचांगp, p);
	पूर्ण
पूर्ण

अटल व्योम tcx_reset(काष्ठा fb_info *info)
अणु
	काष्ठा tcx_par *par = (काष्ठा tcx_par *) info->par;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&par->lock, flags);
	__tcx_set_control_plane(info);
	spin_unlock_irqrestore(&par->lock, flags);
पूर्ण

अटल पूर्णांक tcx_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	tcx_reset(info);
	वापस 0;
पूर्ण

/**
 *      tcx_setcolreg - Optional function. Sets a color रेजिस्टर.
 *      @regno: boolean, 0 copy local, 1 get_user() function
 *      @red: frame buffer colormap काष्ठाure
 *      @green: The green value which can be up to 16 bits wide
 *      @blue:  The blue value which can be up to 16 bits wide.
 *      @transp: If supported the alpha value which can be up to 16 bits wide.
 *      @info: frame buffer info काष्ठाure
 */
अटल पूर्णांक tcx_setcolreg(अचिन्हित regno,
			 अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			 अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा tcx_par *par = (काष्ठा tcx_par *) info->par;
	काष्ठा bt_regs __iomem *bt = par->bt;
	अचिन्हित दीर्घ flags;

	अगर (regno >= 256)
		वापस 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	spin_lock_irqsave(&par->lock, flags);

	sbus_ग_लिखोl(regno << 24, &bt->addr);
	sbus_ग_लिखोl(red << 24, &bt->color_map);
	sbus_ग_लिखोl(green << 24, &bt->color_map);
	sbus_ग_लिखोl(blue << 24, &bt->color_map);

	spin_unlock_irqrestore(&par->lock, flags);

	वापस 0;
पूर्ण

/**
 *      tcx_blank - Optional function.  Blanks the display.
 *      @blank: the blank mode we want.
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 */
अटल पूर्णांक
tcx_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा tcx_par *par = (काष्ठा tcx_par *) info->par;
	काष्ठा tcx_thc __iomem *thc = par->thc;
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&par->lock, flags);

	val = sbus_पढ़ोl(&thc->thc_misc);

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK: /* Unblanking */
		val &= ~(TCX_THC_MISC_VSYNC_DIS |
			 TCX_THC_MISC_HSYNC_DIS);
		val |= TCX_THC_MISC_VIDEO;
		par->flags &= ~TCX_FLAG_BLANKED;
		अवरोध;

	हाल FB_BLANK_NORMAL: /* Normal blanking */
		val &= ~TCX_THC_MISC_VIDEO;
		par->flags |= TCX_FLAG_BLANKED;
		अवरोध;

	हाल FB_BLANK_VSYNC_SUSPEND: /* VESA blank (vsync off) */
		val |= TCX_THC_MISC_VSYNC_DIS;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND: /* VESA blank (hsync off) */
		val |= TCX_THC_MISC_HSYNC_DIS;
		अवरोध;

	हाल FB_BLANK_POWERDOWN: /* Poweroff */
		अवरोध;
	पूर्ण

	sbus_ग_लिखोl(val, &thc->thc_misc);

	spin_unlock_irqrestore(&par->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा sbus_mmap_map __tcx_mmap_map[TCX_MMAP_ENTRIES] = अणु
	अणु
		.voff	= TCX_RAM8BIT,
		.size	= SBUS_MMAP_FBSIZE(1)
	पूर्ण,
	अणु
		.voff	= TCX_RAM24BIT,
		.size	= SBUS_MMAP_FBSIZE(4)
	पूर्ण,
	अणु
		.voff	= TCX_UNK3,
		.size	= SBUS_MMAP_FBSIZE(8)
	पूर्ण,
	अणु
		.voff	= TCX_UNK4,
		.size	= SBUS_MMAP_FBSIZE(8)
	पूर्ण,
	अणु
		.voff	= TCX_CONTROLPLANE,
		.size	= SBUS_MMAP_FBSIZE(4)
	पूर्ण,
	अणु
		.voff	= TCX_UNK6,
		.size	= SBUS_MMAP_FBSIZE(8)
	पूर्ण,
	अणु
		.voff	= TCX_UNK7,
		.size	= SBUS_MMAP_FBSIZE(8)
	पूर्ण,
	अणु
		.voff	= TCX_TEC,
		.size	= PAGE_SIZE
	पूर्ण,
	अणु
		.voff	= TCX_BTREGS,
		.size	= PAGE_SIZE
	पूर्ण,
	अणु
		.voff	= TCX_THC,
		.size	= PAGE_SIZE
	पूर्ण,
	अणु
		.voff	= TCX_DHC,
		.size	= PAGE_SIZE
	पूर्ण,
	अणु
		.voff	= TCX_ALT,
		.size	= PAGE_SIZE
	पूर्ण,
	अणु
		.voff	= TCX_UNK2,
		.size	= 0x20000
	पूर्ण,
	अणु .size = 0 पूर्ण
पूर्ण;

अटल पूर्णांक tcx_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा tcx_par *par = (काष्ठा tcx_par *)info->par;

	वापस sbusfb_mmap_helper(par->mmap_map,
				  info->fix.smem_start, info->fix.smem_len,
				  par->which_io, vma);
पूर्ण

अटल पूर्णांक tcx_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
		     अचिन्हित दीर्घ arg)
अणु
	काष्ठा tcx_par *par = (काष्ठा tcx_par *) info->par;

	वापस sbusfb_ioctl_helper(cmd, arg, info,
				   FBTYPE_TCXCOLOR,
				   (par->lowdepth ? 8 : 24),
				   info->fix.smem_len);
पूर्ण

/*
 *  Initialisation
 */

अटल व्योम
tcx_init_fix(काष्ठा fb_info *info, पूर्णांक linebytes)
अणु
	काष्ठा tcx_par *par = (काष्ठा tcx_par *)info->par;
	स्थिर अक्षर *tcx_name;

	अगर (par->lowdepth)
		tcx_name = "TCX8";
	अन्यथा
		tcx_name = "TCX24";

	strlcpy(info->fix.id, tcx_name, माप(info->fix.id));

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	info->fix.line_length = linebytes;

	info->fix.accel = FB_ACCEL_SUN_TCX;
पूर्ण

अटल व्योम tcx_unmap_regs(काष्ठा platक्रमm_device *op, काष्ठा fb_info *info,
			   काष्ठा tcx_par *par)
अणु
	अगर (par->tec)
		of_iounmap(&op->resource[7],
			   par->tec, माप(काष्ठा tcx_tec));
	अगर (par->thc)
		of_iounmap(&op->resource[9],
			   par->thc, माप(काष्ठा tcx_thc));
	अगर (par->bt)
		of_iounmap(&op->resource[8],
			   par->bt, माप(काष्ठा bt_regs));
	अगर (par->cplane)
		of_iounmap(&op->resource[4],
			   par->cplane, info->fix.smem_len * माप(u32));
	अगर (info->screen_base)
		of_iounmap(&op->resource[0],
			   info->screen_base, info->fix.smem_len);
पूर्ण

अटल पूर्णांक tcx_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा fb_info *info;
	काष्ठा tcx_par *par;
	पूर्णांक linebytes, i, err;

	info = framebuffer_alloc(माप(काष्ठा tcx_par), &op->dev);

	err = -ENOMEM;
	अगर (!info)
		जाओ out_err;
	par = info->par;

	spin_lock_init(&par->lock);

	par->lowdepth =
		(of_find_property(dp, "tcx-8-bit", शून्य) != शून्य);

	sbusfb_fill_var(&info->var, dp, 8);
	info->var.red.length = 8;
	info->var.green.length = 8;
	info->var.blue.length = 8;

	linebytes = of_getपूर्णांकprop_शेष(dp, "linebytes",
					  info->var.xres);
	info->fix.smem_len = PAGE_ALIGN(linebytes * info->var.yres);

	par->tec = of_ioremap(&op->resource[7], 0,
				  माप(काष्ठा tcx_tec), "tcx tec");
	par->thc = of_ioremap(&op->resource[9], 0,
				  माप(काष्ठा tcx_thc), "tcx thc");
	par->bt = of_ioremap(&op->resource[8], 0,
				 माप(काष्ठा bt_regs), "tcx dac");
	info->screen_base = of_ioremap(&op->resource[0], 0,
					   info->fix.smem_len, "tcx ram");
	अगर (!par->tec || !par->thc ||
	    !par->bt || !info->screen_base)
		जाओ out_unmap_regs;

	स_नकल(&par->mmap_map, &__tcx_mmap_map, माप(par->mmap_map));
	अगर (!par->lowdepth) अणु
		par->cplane = of_ioremap(&op->resource[4], 0,
					     info->fix.smem_len * माप(u32),
					     "tcx cplane");
		अगर (!par->cplane)
			जाओ out_unmap_regs;
	पूर्ण अन्यथा अणु
		par->mmap_map[1].size = SBUS_MMAP_EMPTY;
		par->mmap_map[4].size = SBUS_MMAP_EMPTY;
		par->mmap_map[5].size = SBUS_MMAP_EMPTY;
		par->mmap_map[6].size = SBUS_MMAP_EMPTY;
	पूर्ण

	info->fix.smem_start = op->resource[0].start;
	par->which_io = op->resource[0].flags & IORESOURCE_BITS;

	क्रम (i = 0; i < TCX_MMAP_ENTRIES; i++) अणु
		पूर्णांक j;

		चयन (i) अणु
		हाल 10:
			j = 12;
			अवरोध;

		हाल 11: हाल 12:
			j = i - 1;
			अवरोध;

		शेष:
			j = i;
			अवरोध;
		पूर्ण
		par->mmap_map[i].poff = op->resource[j].start;
	पूर्ण

	info->flags = FBINFO_DEFAULT;
	info->fbops = &tcx_ops;

	/* Initialize brooktree DAC. */
	sbus_ग_लिखोl(0x04 << 24, &par->bt->addr);         /* color planes */
	sbus_ग_लिखोl(0xff << 24, &par->bt->control);
	sbus_ग_लिखोl(0x05 << 24, &par->bt->addr);
	sbus_ग_लिखोl(0x00 << 24, &par->bt->control);
	sbus_ग_लिखोl(0x06 << 24, &par->bt->addr);         /* overlay plane */
	sbus_ग_लिखोl(0x73 << 24, &par->bt->control);
	sbus_ग_लिखोl(0x07 << 24, &par->bt->addr);
	sbus_ग_लिखोl(0x00 << 24, &par->bt->control);

	tcx_reset(info);

	tcx_blank(FB_BLANK_UNBLANK, info);

	अगर (fb_alloc_cmap(&info->cmap, 256, 0))
		जाओ out_unmap_regs;

	fb_set_cmap(&info->cmap, info);
	tcx_init_fix(info, linebytes);

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0)
		जाओ out_dealloc_cmap;

	dev_set_drvdata(&op->dev, info);

	prपूर्णांकk(KERN_INFO "%pOF: TCX at %lx:%lx, %s\n",
	       dp,
	       par->which_io,
	       info->fix.smem_start,
	       par->lowdepth ? "8-bit only" : "24-bit depth");

	वापस 0;

out_dealloc_cmap:
	fb_dealloc_cmap(&info->cmap);

out_unmap_regs:
	tcx_unmap_regs(op, info, par);
	framebuffer_release(info);

out_err:
	वापस err;
पूर्ण

अटल पूर्णांक tcx_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(&op->dev);
	काष्ठा tcx_par *par = info->par;

	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);

	tcx_unmap_regs(op, info, par);

	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tcx_match[] = अणु
	अणु
		.name = "SUNW,tcx",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tcx_match);

अटल काष्ठा platक्रमm_driver tcx_driver = अणु
	.driver = अणु
		.name = "tcx",
		.of_match_table = tcx_match,
	पूर्ण,
	.probe		= tcx_probe,
	.हटाओ		= tcx_हटाओ,
पूर्ण;

अटल पूर्णांक __init tcx_init(व्योम)
अणु
	अगर (fb_get_options("tcxfb", शून्य))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&tcx_driver);
पूर्ण

अटल व्योम __निकास tcx_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tcx_driver);
पूर्ण

module_init(tcx_init);
module_निकास(tcx_निकास);

MODULE_DESCRIPTION("framebuffer driver for TCX chipsets");
MODULE_AUTHOR("David S. Miller <davem@davemloft.net>");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
