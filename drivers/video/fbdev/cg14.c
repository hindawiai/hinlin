<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* cg14.c: CGFOURTEEN frame buffer driver
 *
 * Copyright (C) 2003, 2006 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1996,1998 Jakub Jelinek (jj@ultra.linux.cz)
 * Copyright (C) 1995 Miguel de Icaza (miguel@nuclecu.unam.mx)
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
#समावेश <linux/uaccess.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/fbपन.स>

#समावेश "sbuslib.h"

/*
 * Local functions.
 */

अटल पूर्णांक cg14_setcolreg(अचिन्हित, अचिन्हित, अचिन्हित, अचिन्हित,
			 अचिन्हित, काष्ठा fb_info *);

अटल पूर्णांक cg14_mmap(काष्ठा fb_info *, काष्ठा vm_area_काष्ठा *);
अटल पूर्णांक cg14_ioctl(काष्ठा fb_info *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
अटल पूर्णांक cg14_pan_display(काष्ठा fb_var_screeninfo *, काष्ठा fb_info *);

/*
 *  Frame buffer operations
 */

अटल स्थिर काष्ठा fb_ops cg14_ops = अणु
	.owner			= THIS_MODULE,
	.fb_setcolreg		= cg14_setcolreg,
	.fb_pan_display		= cg14_pan_display,
	.fb_fillrect		= cfb_fillrect,
	.fb_copyarea		= cfb_copyarea,
	.fb_imageblit		= cfb_imageblit,
	.fb_mmap		= cg14_mmap,
	.fb_ioctl		= cg14_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.fb_compat_ioctl	= sbusfb_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

#घोषणा CG14_MCR_INTENABLE_SHIFT	7
#घोषणा CG14_MCR_INTENABLE_MASK		0x80
#घोषणा CG14_MCR_VIDENABLE_SHIFT	6
#घोषणा CG14_MCR_VIDENABLE_MASK		0x40
#घोषणा CG14_MCR_PIXMODE_SHIFT		4
#घोषणा CG14_MCR_PIXMODE_MASK		0x30
#घोषणा CG14_MCR_TMR_SHIFT		2
#घोषणा CG14_MCR_TMR_MASK		0x0c
#घोषणा CG14_MCR_TMENABLE_SHIFT		1
#घोषणा CG14_MCR_TMENABLE_MASK		0x02
#घोषणा CG14_MCR_RESET_SHIFT		0
#घोषणा CG14_MCR_RESET_MASK		0x01
#घोषणा CG14_REV_REVISION_SHIFT		4
#घोषणा CG14_REV_REVISION_MASK		0xf0
#घोषणा CG14_REV_IMPL_SHIFT		0
#घोषणा CG14_REV_IMPL_MASK		0x0f
#घोषणा CG14_VBR_FRAMEBASE_SHIFT	12
#घोषणा CG14_VBR_FRAMEBASE_MASK		0x00fff000
#घोषणा CG14_VMCR1_SETUP_SHIFT		0
#घोषणा CG14_VMCR1_SETUP_MASK		0x000001ff
#घोषणा CG14_VMCR1_VCONFIG_SHIFT	9
#घोषणा CG14_VMCR1_VCONFIG_MASK		0x00000e00
#घोषणा CG14_VMCR2_REFRESH_SHIFT	0
#घोषणा CG14_VMCR2_REFRESH_MASK		0x00000001
#घोषणा CG14_VMCR2_TESTROWCNT_SHIFT	1
#घोषणा CG14_VMCR2_TESTROWCNT_MASK	0x00000002
#घोषणा CG14_VMCR2_FBCONFIG_SHIFT	2
#घोषणा CG14_VMCR2_FBCONFIG_MASK	0x0000000c
#घोषणा CG14_VCR_REFRESHREQ_SHIFT	0
#घोषणा CG14_VCR_REFRESHREQ_MASK	0x000003ff
#घोषणा CG14_VCR1_REFRESHENA_SHIFT	10
#घोषणा CG14_VCR1_REFRESHENA_MASK	0x00000400
#घोषणा CG14_VCA_CAD_SHIFT		0
#घोषणा CG14_VCA_CAD_MASK		0x000003ff
#घोषणा CG14_VCA_VERS_SHIFT		10
#घोषणा CG14_VCA_VERS_MASK		0x00000c00
#घोषणा CG14_VCA_RAMSPEED_SHIFT		12
#घोषणा CG14_VCA_RAMSPEED_MASK		0x00001000
#घोषणा CG14_VCA_8MB_SHIFT		13
#घोषणा CG14_VCA_8MB_MASK		0x00002000

#घोषणा CG14_MCR_PIXMODE_8		0
#घोषणा CG14_MCR_PIXMODE_16		2
#घोषणा CG14_MCR_PIXMODE_32		3

काष्ठा cg14_regsअणु
	u8 mcr;	/* Master Control Reg */
	u8 ppr;	/* Packed Pixel Reg */
	u8 पंचांगs[2];	/* Test Mode Status Regs */
	u8 msr;	/* Master Status Reg */
	u8 fsr;	/* Fault Status Reg */
	u8 rev;	/* Revision & Impl */
	u8 ccr;	/* Clock Control Reg */
	u32 पंचांगr;	/* Test Mode Read Back */
	u8 mod;	/* Monitor Operation Data Reg */
	u8 acr;	/* Aux Control */
	u8 xxx0[6];
	u16 hct;	/* Hor Counter */
	u16 vct;	/* Vert Counter */
	u16 hbs;	/* Hor Blank Start */
	u16 hbc;	/* Hor Blank Clear */
	u16 hss;	/* Hor Sync Start */
	u16 hsc;	/* Hor Sync Clear */
	u16 csc;	/* Composite Sync Clear */
	u16 vbs;	/* Vert Blank Start */
	u16 vbc;	/* Vert Blank Clear */
	u16 vss;	/* Vert Sync Start */
	u16 vsc;	/* Vert Sync Clear */
	u16 xcs;
	u16 xcc;
	u16 fsa;	/* Fault Status Address */
	u16 adr;	/* Address Registers */
	u8 xxx1[0xce];
	u8 pcg[0x100]; /* Pixel Clock Generator */
	u32 vbr;	/* Frame Base Row */
	u32 vmcr;	/* VBC Master Control */
	u32 vcr;	/* VBC refresh */
	u32 vca;	/* VBC Config */
पूर्ण;

#घोषणा CG14_CCR_ENABLE	0x04
#घोषणा CG14_CCR_SELECT 0x02	/* HW/Full screen */

काष्ठा cg14_cursor अणु
	u32 cpl0[32];	/* Enable plane 0 */
	u32 cpl1[32];  /* Color selection plane */
	u8 ccr;	/* Cursor Control Reg */
	u8 xxx0[3];
	u16 cursx;	/* Cursor x,y position */
	u16 cursy;	/* Cursor x,y position */
	u32 color0;
	u32 color1;
	u32 xxx1[0x1bc];
	u32 cpl0i[32];	/* Enable plane 0 स्वतःinc */
	u32 cpl1i[32]; /* Color selection स्वतःinc */
पूर्ण;

काष्ठा cg14_dac अणु
	u8 addr;	/* Address Register */
	u8 xxx0[255];
	u8 glut;	/* Gamma table */
	u8 xxx1[255];
	u8 select;	/* Register Select */
	u8 xxx2[255];
	u8 mode;	/* Mode Register */
पूर्ण;

काष्ठा cg14_xlutअणु
	u8 x_xlut [256];
	u8 x_xlutd [256];
	u8 xxx0[0x600];
	u8 x_xlut_inc [256];
	u8 x_xlutd_inc [256];
पूर्ण;

/* Color look up table (clut) */
/* Each one of these arrays hold the color lookup table (क्रम 256
 * colors) क्रम each MDI page (I assume then there should be 4 MDI
 * pages, I still wonder what they are.  I have seen NeXTStep split
 * the screen in four parts, जबतक operating in 24 bits mode.  Each
 * पूर्णांकeger holds 4 values: alpha value (transparency channel, thanks
 * go to John Stone (johns@umr.edu) from OpenBSD), red, green and blue
 *
 * I currently use the clut instead of the Xlut
 */
काष्ठा cg14_clut अणु
	u32 c_clut [256];
	u32 c_clutd [256];    /* i wonder what the 'd' is क्रम */
	u32 c_clut_inc [256];
	u32 c_clutd_inc [256];
पूर्ण;

#घोषणा CG14_MMAP_ENTRIES	16

काष्ठा cg14_par अणु
	spinlock_t		lock;
	काष्ठा cg14_regs	__iomem *regs;
	काष्ठा cg14_clut	__iomem *clut;
	काष्ठा cg14_cursor	__iomem *cursor;

	u32			flags;
#घोषणा CG14_FLAG_BLANKED	0x00000001

	अचिन्हित दीर्घ		iospace;

	काष्ठा sbus_mmap_map	mmap_map[CG14_MMAP_ENTRIES];

	पूर्णांक			mode;
	पूर्णांक			ramsize;
पूर्ण;

अटल व्योम __cg14_reset(काष्ठा cg14_par *par)
अणु
	काष्ठा cg14_regs __iomem *regs = par->regs;
	u8 val;

	val = sbus_पढ़ोb(&regs->mcr);
	val &= ~(CG14_MCR_PIXMODE_MASK);
	sbus_ग_लिखोb(val, &regs->mcr);
पूर्ण

अटल पूर्णांक cg14_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा cg14_par *par = (काष्ठा cg14_par *) info->par;
	अचिन्हित दीर्घ flags;

	/* We just use this to catch चयनes out of
	 * graphics mode.
	 */
	spin_lock_irqsave(&par->lock, flags);
	__cg14_reset(par);
	spin_unlock_irqrestore(&par->lock, flags);

	अगर (var->xoffset || var->yoffset || var->vmode)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/**
 *      cg14_setcolreg - Optional function. Sets a color रेजिस्टर.
 *      @regno: boolean, 0 copy local, 1 get_user() function
 *      @red: frame buffer colormap काष्ठाure
 *      @green: The green value which can be up to 16 bits wide
 *      @blue:  The blue value which can be up to 16 bits wide.
 *      @transp: If supported the alpha value which can be up to 16 bits wide.
 *      @info: frame buffer info काष्ठाure
 */
अटल पूर्णांक cg14_setcolreg(अचिन्हित regno,
			  अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			  अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा cg14_par *par = (काष्ठा cg14_par *) info->par;
	काष्ठा cg14_clut __iomem *clut = par->clut;
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (regno >= 256)
		वापस 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;
	val = (red | (green << 8) | (blue << 16));

	spin_lock_irqsave(&par->lock, flags);
	sbus_ग_लिखोl(val, &clut->c_clut[regno]);
	spin_unlock_irqrestore(&par->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक cg14_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा cg14_par *par = (काष्ठा cg14_par *) info->par;

	वापस sbusfb_mmap_helper(par->mmap_map,
				  info->fix.smem_start, info->fix.smem_len,
				  par->iospace, vma);
पूर्ण

अटल पूर्णांक cg14_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा cg14_par *par = (काष्ठा cg14_par *) info->par;
	काष्ठा cg14_regs __iomem *regs = par->regs;
	काष्ठा mdi_cfginfo kmdi, __user *mdii;
	अचिन्हित दीर्घ flags;
	पूर्णांक cur_mode, mode, ret = 0;

	चयन (cmd) अणु
	हाल MDI_RESET:
		spin_lock_irqsave(&par->lock, flags);
		__cg14_reset(par);
		spin_unlock_irqrestore(&par->lock, flags);
		अवरोध;

	हाल MDI_GET_CFGINFO:
		स_रखो(&kmdi, 0, माप(kmdi));

		spin_lock_irqsave(&par->lock, flags);
		kmdi.mdi_type = FBTYPE_MDICOLOR;
		kmdi.mdi_height = info->var.yres;
		kmdi.mdi_width = info->var.xres;
		kmdi.mdi_mode = par->mode;
		kmdi.mdi_pixfreq = 72; /* FIXME */
		kmdi.mdi_size = par->ramsize;
		spin_unlock_irqrestore(&par->lock, flags);

		mdii = (काष्ठा mdi_cfginfo __user *) arg;
		अगर (copy_to_user(mdii, &kmdi, माप(kmdi)))
			ret = -EFAULT;
		अवरोध;

	हाल MDI_SET_PIXELMODE:
		अगर (get_user(mode, (पूर्णांक __user *) arg)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		spin_lock_irqsave(&par->lock, flags);
		cur_mode = sbus_पढ़ोb(&regs->mcr);
		cur_mode &= ~CG14_MCR_PIXMODE_MASK;
		चयन(mode) अणु
		हाल MDI_32_PIX:
			cur_mode |= (CG14_MCR_PIXMODE_32 <<
				     CG14_MCR_PIXMODE_SHIFT);
			अवरोध;

		हाल MDI_16_PIX:
			cur_mode |= (CG14_MCR_PIXMODE_16 <<
				     CG14_MCR_PIXMODE_SHIFT);
			अवरोध;

		हाल MDI_8_PIX:
			अवरोध;

		शेष:
			ret = -ENOSYS;
			अवरोध;
		पूर्ण
		अगर (!ret) अणु
			sbus_ग_लिखोb(cur_mode, &regs->mcr);
			par->mode = mode;
		पूर्ण
		spin_unlock_irqrestore(&par->lock, flags);
		अवरोध;

	शेष:
		ret = sbusfb_ioctl_helper(cmd, arg, info,
					  FBTYPE_MDICOLOR, 8,
					  info->fix.smem_len);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 *  Initialisation
 */

अटल व्योम cg14_init_fix(काष्ठा fb_info *info, पूर्णांक linebytes,
			  काष्ठा device_node *dp)
अणु
	snम_लिखो(info->fix.id, माप(info->fix.id), "%pOFn", dp);

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	info->fix.line_length = linebytes;

	info->fix.accel = FB_ACCEL_SUN_CG14;
पूर्ण

अटल काष्ठा sbus_mmap_map __cg14_mmap_map[CG14_MMAP_ENTRIES] = अणु
	अणु
		.voff	= CG14_REGS,
		.poff	= 0x80000000,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= CG14_XLUT,
		.poff	= 0x80003000,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= CG14_CLUT1,
		.poff	= 0x80004000,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= CG14_CLUT2,
		.poff	= 0x80005000,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= CG14_CLUT3,
		.poff	= 0x80006000,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= CG3_MMAP_OFFSET - 0x7000,
		.poff	= 0x80000000,
		.size	= 0x7000
	पूर्ण,
	अणु
		.voff	= CG3_MMAP_OFFSET,
		.poff	= 0x00000000,
		.size	= SBUS_MMAP_FBSIZE(1)
	पूर्ण,
	अणु
		.voff	= MDI_CURSOR_MAP,
		.poff	= 0x80001000,
		.size	= 0x1000
	पूर्ण,
	अणु
		.voff	= MDI_CHUNKY_BGR_MAP,
		.poff	= 0x01000000,
		.size	= 0x400000
	पूर्ण,
	अणु
		.voff	= MDI_PLANAR_X16_MAP,
		.poff	= 0x02000000,
		.size	= 0x200000
	पूर्ण,
	अणु
		.voff	= MDI_PLANAR_C16_MAP,
		.poff	= 0x02800000,
		.size	= 0x200000
	पूर्ण,
	अणु
		.voff	= MDI_PLANAR_X32_MAP,
		.poff	= 0x03000000,
		.size	= 0x100000
	पूर्ण,
	अणु
		.voff	= MDI_PLANAR_B32_MAP,
		.poff	= 0x03400000,
		.size	= 0x100000
	पूर्ण,
	अणु
		.voff	= MDI_PLANAR_G32_MAP,
		.poff	= 0x03800000,
		.size	= 0x100000
	पूर्ण,
	अणु
		.voff	= MDI_PLANAR_R32_MAP,
		.poff	= 0x03c00000,
		.size	= 0x100000
	पूर्ण,
	अणु .size = 0 पूर्ण
पूर्ण;

अटल व्योम cg14_unmap_regs(काष्ठा platक्रमm_device *op, काष्ठा fb_info *info,
			    काष्ठा cg14_par *par)
अणु
	अगर (par->regs)
		of_iounmap(&op->resource[0],
			   par->regs, माप(काष्ठा cg14_regs));
	अगर (par->clut)
		of_iounmap(&op->resource[0],
			   par->clut, माप(काष्ठा cg14_clut));
	अगर (par->cursor)
		of_iounmap(&op->resource[0],
			   par->cursor, माप(काष्ठा cg14_cursor));
	अगर (info->screen_base)
		of_iounmap(&op->resource[1],
			   info->screen_base, info->fix.smem_len);
पूर्ण

अटल पूर्णांक cg14_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा fb_info *info;
	काष्ठा cg14_par *par;
	पूर्णांक is_8mb, linebytes, i, err;

	info = framebuffer_alloc(माप(काष्ठा cg14_par), &op->dev);

	err = -ENOMEM;
	अगर (!info)
		जाओ out_err;
	par = info->par;

	spin_lock_init(&par->lock);

	sbusfb_fill_var(&info->var, dp, 8);
	info->var.red.length = 8;
	info->var.green.length = 8;
	info->var.blue.length = 8;

	linebytes = of_getपूर्णांकprop_शेष(dp, "linebytes",
					  info->var.xres);
	info->fix.smem_len = PAGE_ALIGN(linebytes * info->var.yres);

	अगर (of_node_name_eq(dp->parent, "sbus") ||
	    of_node_name_eq(dp->parent, "sbi")) अणु
		info->fix.smem_start = op->resource[0].start;
		par->iospace = op->resource[0].flags & IORESOURCE_BITS;
	पूर्ण अन्यथा अणु
		info->fix.smem_start = op->resource[1].start;
		par->iospace = op->resource[0].flags & IORESOURCE_BITS;
	पूर्ण

	par->regs = of_ioremap(&op->resource[0], 0,
			       माप(काष्ठा cg14_regs), "cg14 regs");
	par->clut = of_ioremap(&op->resource[0], CG14_CLUT1,
			       माप(काष्ठा cg14_clut), "cg14 clut");
	par->cursor = of_ioremap(&op->resource[0], CG14_CURSORREGS,
				 माप(काष्ठा cg14_cursor), "cg14 cursor");

	info->screen_base = of_ioremap(&op->resource[1], 0,
				       info->fix.smem_len, "cg14 ram");

	अगर (!par->regs || !par->clut || !par->cursor || !info->screen_base)
		जाओ out_unmap_regs;

	is_8mb = (resource_size(&op->resource[1]) == (8 * 1024 * 1024));

	BUILD_BUG_ON(माप(par->mmap_map) != माप(__cg14_mmap_map));
		
	स_नकल(&par->mmap_map, &__cg14_mmap_map, माप(par->mmap_map));

	क्रम (i = 0; i < CG14_MMAP_ENTRIES; i++) अणु
		काष्ठा sbus_mmap_map *map = &par->mmap_map[i];

		अगर (!map->size)
			अवरोध;
		अगर (map->poff & 0x80000000)
			map->poff = (map->poff & 0x7fffffff) +
				(op->resource[0].start -
				 op->resource[1].start);
		अगर (is_8mb &&
		    map->size >= 0x100000 &&
		    map->size <= 0x400000)
			map->size *= 2;
	पूर्ण

	par->mode = MDI_8_PIX;
	par->ramsize = (is_8mb ? 0x800000 : 0x400000);

	info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;
	info->fbops = &cg14_ops;

	__cg14_reset(par);

	अगर (fb_alloc_cmap(&info->cmap, 256, 0))
		जाओ out_unmap_regs;

	fb_set_cmap(&info->cmap, info);

	cg14_init_fix(info, linebytes, dp);

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0)
		जाओ out_dealloc_cmap;

	dev_set_drvdata(&op->dev, info);

	prपूर्णांकk(KERN_INFO "%pOF: cgfourteen at %lx:%lx, %dMB\n",
	       dp,
	       par->iospace, info->fix.smem_start,
	       par->ramsize >> 20);

	वापस 0;

out_dealloc_cmap:
	fb_dealloc_cmap(&info->cmap);

out_unmap_regs:
	cg14_unmap_regs(op, info, par);
	framebuffer_release(info);

out_err:
	वापस err;
पूर्ण

अटल पूर्णांक cg14_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(&op->dev);
	काष्ठा cg14_par *par = info->par;

	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);

	cg14_unmap_regs(op, info, par);

	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cg14_match[] = अणु
	अणु
		.name = "cgfourteen",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cg14_match);

अटल काष्ठा platक्रमm_driver cg14_driver = अणु
	.driver = अणु
		.name = "cg14",
		.of_match_table = cg14_match,
	पूर्ण,
	.probe		= cg14_probe,
	.हटाओ		= cg14_हटाओ,
पूर्ण;

अटल पूर्णांक __init cg14_init(व्योम)
अणु
	अगर (fb_get_options("cg14fb", शून्य))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&cg14_driver);
पूर्ण

अटल व्योम __निकास cg14_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&cg14_driver);
पूर्ण

module_init(cg14_init);
module_निकास(cg14_निकास);

MODULE_DESCRIPTION("framebuffer driver for CGfourteen chipsets");
MODULE_AUTHOR("David S. Miller <davem@davemloft.net>");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
