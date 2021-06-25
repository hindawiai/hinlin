<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* p9100.c: P9100 frame buffer driver
 *
 * Copyright (C) 2003, 2006 David S. Miller (davem@davemloft.net)
 * Copyright 1999 Derrick J Brashear (shaकरोw@dementia.org)
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

अटल पूर्णांक p9100_setcolreg(अचिन्हित, अचिन्हित, अचिन्हित, अचिन्हित,
			   अचिन्हित, काष्ठा fb_info *);
अटल पूर्णांक p9100_blank(पूर्णांक, काष्ठा fb_info *);

अटल पूर्णांक p9100_mmap(काष्ठा fb_info *, काष्ठा vm_area_काष्ठा *);
अटल पूर्णांक p9100_ioctl(काष्ठा fb_info *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);

/*
 *  Frame buffer operations
 */

अटल स्थिर काष्ठा fb_ops p9100_ops = अणु
	.owner			= THIS_MODULE,
	.fb_setcolreg		= p9100_setcolreg,
	.fb_blank		= p9100_blank,
	.fb_fillrect		= cfb_fillrect,
	.fb_copyarea		= cfb_copyarea,
	.fb_imageblit		= cfb_imageblit,
	.fb_mmap		= p9100_mmap,
	.fb_ioctl		= p9100_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.fb_compat_ioctl	= sbusfb_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

/* P9100 control रेजिस्टरs */
#घोषणा P9100_SYSCTL_OFF	0x0UL
#घोषणा P9100_VIDEOCTL_OFF	0x100UL
#घोषणा P9100_VRAMCTL_OFF 	0x180UL
#घोषणा P9100_RAMDAC_OFF 	0x200UL
#घोषणा P9100_VIDEOCOPROC_OFF 	0x400UL

/* P9100 command रेजिस्टरs */
#घोषणा P9100_CMD_OFF 0x0UL

/* P9100 framebuffer memory */
#घोषणा P9100_FB_OFF 0x0UL

/* 3 bits: 2=8bpp 3=16bpp 5=32bpp 7=24bpp */
#घोषणा SYS_CONFIG_PIXELSIZE_SHIFT 26 

#घोषणा SCREENPAINT_TIMECTL1_ENABLE_VIDEO 0x20 /* 0 = off, 1 = on */

काष्ठा p9100_regs अणु
	/* Registers क्रम the प्रणाली control */
	u32 sys_base;
	u32 sys_config;
	u32 sys_पूर्णांकr;
	u32 sys_पूर्णांक_ena;
	u32 sys_alt_rd;
	u32 sys_alt_wr;
	u32 sys_xxx[58];

	/* Registers क्रम the video control */
	u32 vid_base;
	u32 vid_hcnt;
	u32 vid_htotal;
	u32 vid_hsync_rise;
	u32 vid_hblank_rise;
	u32 vid_hblank_fall;
	u32 vid_hcnt_preload;
	u32 vid_vcnt;
	u32 vid_vlen;
	u32 vid_vsync_rise;
	u32 vid_vblank_rise;
	u32 vid_vblank_fall;
	u32 vid_vcnt_preload;
	u32 vid_screenpaपूर्णांक_addr;
	u32 vid_screenpaपूर्णांक_समयctl1;
	u32 vid_screenpaपूर्णांक_qsfcnt;
	u32 vid_screenpaपूर्णांक_समयctl2;
	u32 vid_xxx[15];

	/* Registers क्रम the video control */
	u32 vram_base;
	u32 vram_memcfg;
	u32 vram_refresh_pd;
	u32 vram_refresh_cnt;
	u32 vram_raslo_max;
	u32 vram_raslo_cur;
	u32 pwrup_cfg;
	u32 vram_xxx[25];

	/* Registers क्रम IBM RGB528 Palette */
	u32 ramdac_cmap_wridx; 
	u32 ramdac_palette_data;
	u32 ramdac_pixel_mask;
	u32 ramdac_palette_rdaddr;
	u32 ramdac_idx_lo;
	u32 ramdac_idx_hi;
	u32 ramdac_idx_data;
	u32 ramdac_idx_ctl;
	u32 ramdac_xxx[1784];
पूर्ण;

काष्ठा p9100_cmd_parameng अणु
	u32 parameng_status;
	u32 parameng_bltcmd;
	u32 parameng_quadcmd;
पूर्ण;

काष्ठा p9100_par अणु
	spinlock_t		lock;
	काष्ठा p9100_regs	__iomem *regs;

	u32			flags;
#घोषणा P9100_FLAG_BLANKED	0x00000001

	अचिन्हित दीर्घ		which_io;
पूर्ण;

/**
 *      p9100_setcolreg - Optional function. Sets a color रेजिस्टर.
 *      @regno: boolean, 0 copy local, 1 get_user() function
 *      @red: frame buffer colormap काष्ठाure
 *      @green: The green value which can be up to 16 bits wide
 *      @blue:  The blue value which can be up to 16 bits wide.
 *      @transp: If supported the alpha value which can be up to 16 bits wide.
 *      @info: frame buffer info काष्ठाure
 */
अटल पूर्णांक p9100_setcolreg(अचिन्हित regno,
			   अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			   अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा p9100_par *par = (काष्ठा p9100_par *) info->par;
	काष्ठा p9100_regs __iomem *regs = par->regs;
	अचिन्हित दीर्घ flags;

	अगर (regno >= 256)
		वापस 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	spin_lock_irqsave(&par->lock, flags);

	sbus_ग_लिखोl((regno << 16), &regs->ramdac_cmap_wridx);
	sbus_ग_लिखोl((red << 16), &regs->ramdac_palette_data);
	sbus_ग_लिखोl((green << 16), &regs->ramdac_palette_data);
	sbus_ग_लिखोl((blue << 16), &regs->ramdac_palette_data);

	spin_unlock_irqrestore(&par->lock, flags);

	वापस 0;
पूर्ण

/**
 *      p9100_blank - Optional function.  Blanks the display.
 *      @blank: the blank mode we want.
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 */
अटल पूर्णांक
p9100_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा p9100_par *par = (काष्ठा p9100_par *) info->par;
	काष्ठा p9100_regs __iomem *regs = par->regs;
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&par->lock, flags);

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK: /* Unblanking */
		val = sbus_पढ़ोl(&regs->vid_screenpaपूर्णांक_समयctl1);
		val |= SCREENPAINT_TIMECTL1_ENABLE_VIDEO;
		sbus_ग_लिखोl(val, &regs->vid_screenpaपूर्णांक_समयctl1);
		par->flags &= ~P9100_FLAG_BLANKED;
		अवरोध;

	हाल FB_BLANK_NORMAL: /* Normal blanking */
	हाल FB_BLANK_VSYNC_SUSPEND: /* VESA blank (vsync off) */
	हाल FB_BLANK_HSYNC_SUSPEND: /* VESA blank (hsync off) */
	हाल FB_BLANK_POWERDOWN: /* Poweroff */
		val = sbus_पढ़ोl(&regs->vid_screenpaपूर्णांक_समयctl1);
		val &= ~SCREENPAINT_TIMECTL1_ENABLE_VIDEO;
		sbus_ग_लिखोl(val, &regs->vid_screenpaपूर्णांक_समयctl1);
		par->flags |= P9100_FLAG_BLANKED;
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&par->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा sbus_mmap_map p9100_mmap_map[] = अणु
	अणु CG3_MMAP_OFFSET,	0,		SBUS_MMAP_FBSIZE(1) पूर्ण,
	अणु 0,			0,		0		    पूर्ण
पूर्ण;

अटल पूर्णांक p9100_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा p9100_par *par = (काष्ठा p9100_par *)info->par;

	वापस sbusfb_mmap_helper(p9100_mmap_map,
				  info->fix.smem_start, info->fix.smem_len,
				  par->which_io, vma);
पूर्ण

अटल पूर्णांक p9100_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
		       अचिन्हित दीर्घ arg)
अणु
	/* Make it look like a cg3. */
	वापस sbusfb_ioctl_helper(cmd, arg, info,
				   FBTYPE_SUN3COLOR, 8, info->fix.smem_len);
पूर्ण

/*
 *  Initialisation
 */

अटल व्योम p9100_init_fix(काष्ठा fb_info *info, पूर्णांक linebytes, काष्ठा device_node *dp)
अणु
	snम_लिखो(info->fix.id, माप(info->fix.id), "%pOFn", dp);

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	info->fix.line_length = linebytes;

	info->fix.accel = FB_ACCEL_SUN_CGTHREE;
पूर्ण

अटल पूर्णांक p9100_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा fb_info *info;
	काष्ठा p9100_par *par;
	पूर्णांक linebytes, err;

	info = framebuffer_alloc(माप(काष्ठा p9100_par), &op->dev);

	err = -ENOMEM;
	अगर (!info)
		जाओ out_err;
	par = info->par;

	spin_lock_init(&par->lock);

	/* This is the framebuffer and the only resource apps can mmap.  */
	info->fix.smem_start = op->resource[2].start;
	par->which_io = op->resource[2].flags & IORESOURCE_BITS;

	sbusfb_fill_var(&info->var, dp, 8);
	info->var.red.length = 8;
	info->var.green.length = 8;
	info->var.blue.length = 8;

	linebytes = of_getपूर्णांकprop_शेष(dp, "linebytes", info->var.xres);
	info->fix.smem_len = PAGE_ALIGN(linebytes * info->var.yres);

	par->regs = of_ioremap(&op->resource[0], 0,
			       माप(काष्ठा p9100_regs), "p9100 regs");
	अगर (!par->regs)
		जाओ out_release_fb;

	info->flags = FBINFO_DEFAULT;
	info->fbops = &p9100_ops;
	info->screen_base = of_ioremap(&op->resource[2], 0,
				       info->fix.smem_len, "p9100 ram");
	अगर (!info->screen_base)
		जाओ out_unmap_regs;

	p9100_blank(FB_BLANK_UNBLANK, info);

	अगर (fb_alloc_cmap(&info->cmap, 256, 0))
		जाओ out_unmap_screen;

	p9100_init_fix(info, linebytes, dp);

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0)
		जाओ out_dealloc_cmap;

	fb_set_cmap(&info->cmap, info);

	dev_set_drvdata(&op->dev, info);

	prपूर्णांकk(KERN_INFO "%pOF: p9100 at %lx:%lx\n",
	       dp,
	       par->which_io, info->fix.smem_start);

	वापस 0;

out_dealloc_cmap:
	fb_dealloc_cmap(&info->cmap);

out_unmap_screen:
	of_iounmap(&op->resource[2], info->screen_base, info->fix.smem_len);

out_unmap_regs:
	of_iounmap(&op->resource[0], par->regs, माप(काष्ठा p9100_regs));

out_release_fb:
	framebuffer_release(info);

out_err:
	वापस err;
पूर्ण

अटल पूर्णांक p9100_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(&op->dev);
	काष्ठा p9100_par *par = info->par;

	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);

	of_iounmap(&op->resource[0], par->regs, माप(काष्ठा p9100_regs));
	of_iounmap(&op->resource[2], info->screen_base, info->fix.smem_len);

	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id p9100_match[] = अणु
	अणु
		.name = "p9100",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, p9100_match);

अटल काष्ठा platक्रमm_driver p9100_driver = अणु
	.driver = अणु
		.name = "p9100",
		.of_match_table = p9100_match,
	पूर्ण,
	.probe		= p9100_probe,
	.हटाओ		= p9100_हटाओ,
पूर्ण;

अटल पूर्णांक __init p9100_init(व्योम)
अणु
	अगर (fb_get_options("p9100fb", शून्य))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&p9100_driver);
पूर्ण

अटल व्योम __निकास p9100_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&p9100_driver);
पूर्ण

module_init(p9100_init);
module_निकास(p9100_निकास);

MODULE_DESCRIPTION("framebuffer driver for P9100 chipsets");
MODULE_AUTHOR("David S. Miller <davem@davemloft.net>");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
