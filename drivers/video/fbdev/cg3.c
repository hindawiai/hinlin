<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* cg3.c: CGTHREE frame buffer driver
 *
 * Copyright (C) 2003, 2006 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1996,1998 Jakub Jelinek (jj@ultra.linux.cz)
 * Copyright (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)
 * Copyright (C) 1997 Eddie C. Dost (ecd@skynet.be)
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

अटल पूर्णांक cg3_setcolreg(अचिन्हित, अचिन्हित, अचिन्हित, अचिन्हित,
			 अचिन्हित, काष्ठा fb_info *);
अटल पूर्णांक cg3_blank(पूर्णांक, काष्ठा fb_info *);

अटल पूर्णांक cg3_mmap(काष्ठा fb_info *, काष्ठा vm_area_काष्ठा *);
अटल पूर्णांक cg3_ioctl(काष्ठा fb_info *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);

/*
 *  Frame buffer operations
 */

अटल स्थिर काष्ठा fb_ops cg3_ops = अणु
	.owner			= THIS_MODULE,
	.fb_setcolreg		= cg3_setcolreg,
	.fb_blank		= cg3_blank,
	.fb_fillrect		= cfb_fillrect,
	.fb_copyarea		= cfb_copyarea,
	.fb_imageblit		= cfb_imageblit,
	.fb_mmap		= cg3_mmap,
	.fb_ioctl		= cg3_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.fb_compat_ioctl	= sbusfb_compat_ioctl,
#पूर्ण_अगर
पूर्ण;


/* Control Register Constants */
#घोषणा CG3_CR_ENABLE_INTS      0x80
#घोषणा CG3_CR_ENABLE_VIDEO     0x40
#घोषणा CG3_CR_ENABLE_TIMING    0x20
#घोषणा CG3_CR_ENABLE_CURCMP    0x10
#घोषणा CG3_CR_XTAL_MASK        0x0c
#घोषणा CG3_CR_DIVISOR_MASK     0x03

/* Status Register Constants */
#घोषणा CG3_SR_PENDING_INT      0x80
#घोषणा CG3_SR_RES_MASK         0x70
#घोषणा CG3_SR_1152_900_76_A    0x40
#घोषणा CG3_SR_1152_900_76_B    0x60
#घोषणा CG3_SR_ID_MASK          0x0f
#घोषणा CG3_SR_ID_COLOR         0x01
#घोषणा CG3_SR_ID_MONO          0x02
#घोषणा CG3_SR_ID_MONO_ECL      0x03

क्रमागत cg3_type अणु
	CG3_AT_66HZ = 0,
	CG3_AT_76HZ,
	CG3_RDI
पूर्ण;

काष्ठा bt_regs अणु
	u32 addr;
	u32 color_map;
	u32 control;
	u32 cursor;
पूर्ण;

काष्ठा cg3_regs अणु
	काष्ठा bt_regs	cmap;
	u8	control;
	u8	status;
	u8	cursor_start;
	u8	cursor_end;
	u8	h_blank_start;
	u8	h_blank_end;
	u8	h_sync_start;
	u8	h_sync_end;
	u8	comp_sync_end;
	u8	v_blank_start_high;
	u8	v_blank_start_low;
	u8	v_blank_end;
	u8	v_sync_start;
	u8	v_sync_end;
	u8	xfer_holकरोff_start;
	u8	xfer_holकरोff_end;
पूर्ण;

/* Offset of पूर्णांकeresting काष्ठाures in the OBIO space */
#घोषणा CG3_REGS_OFFSET	     0x400000UL
#घोषणा CG3_RAM_OFFSET	     0x800000UL

काष्ठा cg3_par अणु
	spinlock_t		lock;
	काष्ठा cg3_regs		__iomem *regs;
	u32			sw_cmap[((256 * 3) + 3) / 4];

	u32			flags;
#घोषणा CG3_FLAG_BLANKED	0x00000001
#घोषणा CG3_FLAG_RDI		0x00000002

	अचिन्हित दीर्घ		which_io;
पूर्ण;

/**
 *      cg3_setcolreg - Optional function. Sets a color रेजिस्टर.
 *      @regno: boolean, 0 copy local, 1 get_user() function
 *      @red: frame buffer colormap काष्ठाure
 *      @green: The green value which can be up to 16 bits wide
 *      @blue:  The blue value which can be up to 16 bits wide.
 *      @transp: If supported the alpha value which can be up to 16 bits wide.
 *      @info: frame buffer info काष्ठाure
 *
 * The cg3 palette is loaded with 4 color values at each समय
 * so you end up with: (rgb)(r), (gb)(rg), (b)(rgb), and so on.
 * We keep a sw copy of the hw cmap to assist us in this esoteric
 * loading procedure.
 */
अटल पूर्णांक cg3_setcolreg(अचिन्हित regno,
			 अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			 अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा cg3_par *par = (काष्ठा cg3_par *) info->par;
	काष्ठा bt_regs __iomem *bt = &par->regs->cmap;
	अचिन्हित दीर्घ flags;
	u32 *p32;
	u8 *p8;
	पूर्णांक count;

	अगर (regno >= 256)
		वापस 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	spin_lock_irqsave(&par->lock, flags);

	p8 = (u8 *)par->sw_cmap + (regno * 3);
	p8[0] = red;
	p8[1] = green;
	p8[2] = blue;

#घोषणा D4M3(x) ((((x)>>2)<<1) + ((x)>>2))      /* (x/4)*3 */
#घोषणा D4M4(x) ((x)&~0x3)                      /* (x/4)*4 */

	count = 3;
	p32 = &par->sw_cmap[D4M3(regno)];
	sbus_ग_लिखोl(D4M4(regno), &bt->addr);
	जबतक (count--)
		sbus_ग_लिखोl(*p32++, &bt->color_map);

#अघोषित D4M3
#अघोषित D4M4

	spin_unlock_irqrestore(&par->lock, flags);

	वापस 0;
पूर्ण

/**
 *      cg3_blank - Optional function.  Blanks the display.
 *      @blank: the blank mode we want.
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 */
अटल पूर्णांक cg3_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा cg3_par *par = (काष्ठा cg3_par *) info->par;
	काष्ठा cg3_regs __iomem *regs = par->regs;
	अचिन्हित दीर्घ flags;
	u8 val;

	spin_lock_irqsave(&par->lock, flags);

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK: /* Unblanking */
		val = sbus_पढ़ोb(&regs->control);
		val |= CG3_CR_ENABLE_VIDEO;
		sbus_ग_लिखोb(val, &regs->control);
		par->flags &= ~CG3_FLAG_BLANKED;
		अवरोध;

	हाल FB_BLANK_NORMAL: /* Normal blanking */
	हाल FB_BLANK_VSYNC_SUSPEND: /* VESA blank (vsync off) */
	हाल FB_BLANK_HSYNC_SUSPEND: /* VESA blank (hsync off) */
	हाल FB_BLANK_POWERDOWN: /* Poweroff */
		val = sbus_पढ़ोb(&regs->control);
		val &= ~CG3_CR_ENABLE_VIDEO;
		sbus_ग_लिखोb(val, &regs->control);
		par->flags |= CG3_FLAG_BLANKED;
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&par->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा sbus_mmap_map cg3_mmap_map[] = अणु
	अणु
		.voff	= CG3_MMAP_OFFSET,
		.poff	= CG3_RAM_OFFSET,
		.size	= SBUS_MMAP_FBSIZE(1)
	पूर्ण,
	अणु .size = 0 पूर्ण
पूर्ण;

अटल पूर्णांक cg3_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा cg3_par *par = (काष्ठा cg3_par *)info->par;

	वापस sbusfb_mmap_helper(cg3_mmap_map,
				  info->fix.smem_start, info->fix.smem_len,
				  par->which_io,
				  vma);
पूर्ण

अटल पूर्णांक cg3_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस sbusfb_ioctl_helper(cmd, arg, info,
				   FBTYPE_SUN3COLOR, 8, info->fix.smem_len);
पूर्ण

/*
 *  Initialisation
 */

अटल व्योम cg3_init_fix(काष्ठा fb_info *info, पूर्णांक linebytes,
			 काष्ठा device_node *dp)
अणु
	snम_लिखो(info->fix.id, माप(info->fix.id), "%pOFn", dp);

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	info->fix.line_length = linebytes;

	info->fix.accel = FB_ACCEL_SUN_CGTHREE;
पूर्ण

अटल व्योम cg3_rdi_maybe_fixup_var(काष्ठा fb_var_screeninfo *var,
				    काष्ठा device_node *dp)
अणु
	स्थिर अक्षर *params;
	अक्षर *p;
	पूर्णांक ww, hh;

	params = of_get_property(dp, "params", शून्य);
	अगर (params) अणु
		ww = simple_म_से_अदीर्घ(params, &p, 10);
		अगर (ww && *p == 'x') अणु
			hh = simple_म_से_अदीर्घ(p + 1, &p, 10);
			अगर (hh && *p == '-') अणु
				अगर (var->xres != ww ||
				    var->yres != hh) अणु
					var->xres = var->xres_भव = ww;
					var->yres = var->yres_भव = hh;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल u8 cg3regvals_66hz[] = अणु	/* 1152 x 900, 66 Hz */
	0x14, 0xbb,	0x15, 0x2b,	0x16, 0x04,	0x17, 0x14,
	0x18, 0xae,	0x19, 0x03,	0x1a, 0xa8,	0x1b, 0x24,
	0x1c, 0x01,	0x1d, 0x05,	0x1e, 0xff,	0x1f, 0x01,
	0x10, 0x20,	0
पूर्ण;

अटल u8 cg3regvals_76hz[] = अणु	/* 1152 x 900, 76 Hz */
	0x14, 0xb7,	0x15, 0x27,	0x16, 0x03,	0x17, 0x0f,
	0x18, 0xae,	0x19, 0x03,	0x1a, 0xae,	0x1b, 0x2a,
	0x1c, 0x01,	0x1d, 0x09,	0x1e, 0xff,	0x1f, 0x01,
	0x10, 0x24,	0
पूर्ण;

अटल u8 cg3regvals_rdi[] = अणु	/* 640 x 480, cgRDI */
	0x14, 0x70,	0x15, 0x20,	0x16, 0x08,	0x17, 0x10,
	0x18, 0x06,	0x19, 0x02,	0x1a, 0x31,	0x1b, 0x51,
	0x1c, 0x06,	0x1d, 0x0c,	0x1e, 0xff,	0x1f, 0x01,
	0x10, 0x22,	0
पूर्ण;

अटल u8 *cg3_regvals[] = अणु
	cg3regvals_66hz, cg3regvals_76hz, cg3regvals_rdi
पूर्ण;

अटल u_अक्षर cg3_dacvals[] = अणु
	4, 0xff,	5, 0x00,	6, 0x70,	7, 0x00,	0
पूर्ण;

अटल पूर्णांक cg3_करो_शेष_mode(काष्ठा cg3_par *par)
अणु
	क्रमागत cg3_type type;
	u8 *p;

	अगर (par->flags & CG3_FLAG_RDI)
		type = CG3_RDI;
	अन्यथा अणु
		u8 status = sbus_पढ़ोb(&par->regs->status), mon;
		अगर ((status & CG3_SR_ID_MASK) == CG3_SR_ID_COLOR) अणु
			mon = status & CG3_SR_RES_MASK;
			अगर (mon == CG3_SR_1152_900_76_A ||
			    mon == CG3_SR_1152_900_76_B)
				type = CG3_AT_76HZ;
			अन्यथा
				type = CG3_AT_66HZ;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "cgthree: can't handle SR %02x\n",
			       status);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम (p = cg3_regvals[type]; *p; p += 2) अणु
		u8 __iomem *regp = &((u8 __iomem *)par->regs)[p[0]];
		sbus_ग_लिखोb(p[1], regp);
	पूर्ण
	क्रम (p = cg3_dacvals; *p; p += 2) अणु
		u8 __iomem *regp;

		regp = (u8 __iomem *)&par->regs->cmap.addr;
		sbus_ग_लिखोb(p[0], regp);
		regp = (u8 __iomem *)&par->regs->cmap.control;
		sbus_ग_लिखोb(p[1], regp);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cg3_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा fb_info *info;
	काष्ठा cg3_par *par;
	पूर्णांक linebytes, err;

	info = framebuffer_alloc(माप(काष्ठा cg3_par), &op->dev);

	err = -ENOMEM;
	अगर (!info)
		जाओ out_err;
	par = info->par;

	spin_lock_init(&par->lock);

	info->fix.smem_start = op->resource[0].start;
	par->which_io = op->resource[0].flags & IORESOURCE_BITS;

	sbusfb_fill_var(&info->var, dp, 8);
	info->var.red.length = 8;
	info->var.green.length = 8;
	info->var.blue.length = 8;
	अगर (of_node_name_eq(dp, "cgRDI"))
		par->flags |= CG3_FLAG_RDI;
	अगर (par->flags & CG3_FLAG_RDI)
		cg3_rdi_maybe_fixup_var(&info->var, dp);

	linebytes = of_getपूर्णांकprop_शेष(dp, "linebytes",
					  info->var.xres);
	info->fix.smem_len = PAGE_ALIGN(linebytes * info->var.yres);

	par->regs = of_ioremap(&op->resource[0], CG3_REGS_OFFSET,
			       माप(काष्ठा cg3_regs), "cg3 regs");
	अगर (!par->regs)
		जाओ out_release_fb;

	info->flags = FBINFO_DEFAULT;
	info->fbops = &cg3_ops;
	info->screen_base = of_ioremap(&op->resource[0], CG3_RAM_OFFSET,
				       info->fix.smem_len, "cg3 ram");
	अगर (!info->screen_base)
		जाओ out_unmap_regs;

	cg3_blank(FB_BLANK_UNBLANK, info);

	अगर (!of_find_property(dp, "width", शून्य)) अणु
		err = cg3_करो_शेष_mode(par);
		अगर (err)
			जाओ out_unmap_screen;
	पूर्ण

	err = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (err)
		जाओ out_unmap_screen;

	fb_set_cmap(&info->cmap, info);

	cg3_init_fix(info, linebytes, dp);

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0)
		जाओ out_dealloc_cmap;

	dev_set_drvdata(&op->dev, info);

	prपूर्णांकk(KERN_INFO "%pOF: cg3 at %lx:%lx\n",
	       dp, par->which_io, info->fix.smem_start);

	वापस 0;

out_dealloc_cmap:
	fb_dealloc_cmap(&info->cmap);

out_unmap_screen:
	of_iounmap(&op->resource[0], info->screen_base, info->fix.smem_len);

out_unmap_regs:
	of_iounmap(&op->resource[0], par->regs, माप(काष्ठा cg3_regs));

out_release_fb:
	framebuffer_release(info);

out_err:
	वापस err;
पूर्ण

अटल पूर्णांक cg3_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(&op->dev);
	काष्ठा cg3_par *par = info->par;

	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);

	of_iounmap(&op->resource[0], par->regs, माप(काष्ठा cg3_regs));
	of_iounmap(&op->resource[0], info->screen_base, info->fix.smem_len);

	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cg3_match[] = अणु
	अणु
		.name = "cgthree",
	पूर्ण,
	अणु
		.name = "cgRDI",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cg3_match);

अटल काष्ठा platक्रमm_driver cg3_driver = अणु
	.driver = अणु
		.name = "cg3",
		.of_match_table = cg3_match,
	पूर्ण,
	.probe		= cg3_probe,
	.हटाओ		= cg3_हटाओ,
पूर्ण;

अटल पूर्णांक __init cg3_init(व्योम)
अणु
	अगर (fb_get_options("cg3fb", शून्य))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&cg3_driver);
पूर्ण

अटल व्योम __निकास cg3_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&cg3_driver);
पूर्ण

module_init(cg3_init);
module_निकास(cg3_निकास);

MODULE_DESCRIPTION("framebuffer driver for CGthree chipsets");
MODULE_AUTHOR("David S. Miller <davem@davemloft.net>");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
