<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* bw2.c: BWTWO frame buffer driver
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

अटल पूर्णांक bw2_blank(पूर्णांक, काष्ठा fb_info *);

अटल पूर्णांक bw2_mmap(काष्ठा fb_info *, काष्ठा vm_area_काष्ठा *);
अटल पूर्णांक bw2_ioctl(काष्ठा fb_info *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);

/*
 *  Frame buffer operations
 */

अटल स्थिर काष्ठा fb_ops bw2_ops = अणु
	.owner			= THIS_MODULE,
	.fb_blank		= bw2_blank,
	.fb_fillrect		= cfb_fillrect,
	.fb_copyarea		= cfb_copyarea,
	.fb_imageblit		= cfb_imageblit,
	.fb_mmap		= bw2_mmap,
	.fb_ioctl		= bw2_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.fb_compat_ioctl	= sbusfb_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

/* OBio addresses क्रम the bwtwo रेजिस्टरs */
#घोषणा BWTWO_REGISTER_OFFSET 0x400000

काष्ठा bt_regs अणु
	u32 addr;
	u32 color_map;
	u32 control;
	u32 cursor;
पूर्ण;

काष्ठा bw2_regs अणु
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

/* Status Register Constants */
#घोषणा BWTWO_SR_RES_MASK	0x70
#घोषणा BWTWO_SR_1600_1280	0x50
#घोषणा BWTWO_SR_1152_900_76_A	0x40
#घोषणा BWTWO_SR_1152_900_76_B	0x60
#घोषणा BWTWO_SR_ID_MASK	0x0f
#घोषणा BWTWO_SR_ID_MONO	0x02
#घोषणा BWTWO_SR_ID_MONO_ECL	0x03
#घोषणा BWTWO_SR_ID_MSYNC	0x04
#घोषणा BWTWO_SR_ID_NOCONN	0x0a

/* Control Register Constants */
#घोषणा BWTWO_CTL_ENABLE_INTS   0x80
#घोषणा BWTWO_CTL_ENABLE_VIDEO  0x40
#घोषणा BWTWO_CTL_ENABLE_TIMING 0x20
#घोषणा BWTWO_CTL_ENABLE_CURCMP 0x10
#घोषणा BWTWO_CTL_XTAL_MASK     0x0C
#घोषणा BWTWO_CTL_DIVISOR_MASK  0x03

/* Status Register Constants */
#घोषणा BWTWO_STAT_PENDING_INT  0x80
#घोषणा BWTWO_STAT_MSENSE_MASK  0x70
#घोषणा BWTWO_STAT_ID_MASK      0x0f

काष्ठा bw2_par अणु
	spinlock_t		lock;
	काष्ठा bw2_regs		__iomem *regs;

	u32			flags;
#घोषणा BW2_FLAG_BLANKED	0x00000001

	अचिन्हित दीर्घ		which_io;
पूर्ण;

/**
 *      bw2_blank - Optional function.  Blanks the display.
 *      @blank: the blank mode we want.
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 */
अटल पूर्णांक
bw2_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा bw2_par *par = (काष्ठा bw2_par *) info->par;
	काष्ठा bw2_regs __iomem *regs = par->regs;
	अचिन्हित दीर्घ flags;
	u8 val;

	spin_lock_irqsave(&par->lock, flags);

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK: /* Unblanking */
		val = sbus_पढ़ोb(&regs->control);
		val |= BWTWO_CTL_ENABLE_VIDEO;
		sbus_ग_लिखोb(val, &regs->control);
		par->flags &= ~BW2_FLAG_BLANKED;
		अवरोध;

	हाल FB_BLANK_NORMAL: /* Normal blanking */
	हाल FB_BLANK_VSYNC_SUSPEND: /* VESA blank (vsync off) */
	हाल FB_BLANK_HSYNC_SUSPEND: /* VESA blank (hsync off) */
	हाल FB_BLANK_POWERDOWN: /* Poweroff */
		val = sbus_पढ़ोb(&regs->control);
		val &= ~BWTWO_CTL_ENABLE_VIDEO;
		sbus_ग_लिखोb(val, &regs->control);
		par->flags |= BW2_FLAG_BLANKED;
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&par->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा sbus_mmap_map bw2_mmap_map[] = अणु
	अणु
		.size = SBUS_MMAP_FBSIZE(1)
	पूर्ण,
	अणु .size = 0 पूर्ण
पूर्ण;

अटल पूर्णांक bw2_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा bw2_par *par = (काष्ठा bw2_par *)info->par;

	वापस sbusfb_mmap_helper(bw2_mmap_map,
				  info->fix.smem_start, info->fix.smem_len,
				  par->which_io,
				  vma);
पूर्ण

अटल पूर्णांक bw2_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस sbusfb_ioctl_helper(cmd, arg, info,
				   FBTYPE_SUN2BW, 1, info->fix.smem_len);
पूर्ण

/*
 *  Initialisation
 */

अटल व्योम bw2_init_fix(काष्ठा fb_info *info, पूर्णांक linebytes)
अणु
	strlcpy(info->fix.id, "bwtwo", माप(info->fix.id));

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_MONO01;

	info->fix.line_length = linebytes;

	info->fix.accel = FB_ACCEL_SUN_BWTWO;
पूर्ण

अटल u8 bw2regs_1600[] = अणु
	0x14, 0x8b,	0x15, 0x28,	0x16, 0x03,	0x17, 0x13,
	0x18, 0x7b,	0x19, 0x05,	0x1a, 0x34,	0x1b, 0x2e,
	0x1c, 0x00,	0x1d, 0x0a,	0x1e, 0xff,	0x1f, 0x01,
	0x10, 0x21,	0
पूर्ण;

अटल u8 bw2regs_ecl[] = अणु
	0x14, 0x65,	0x15, 0x1e,	0x16, 0x04,	0x17, 0x0c,
	0x18, 0x5e,	0x19, 0x03,	0x1a, 0xa7,	0x1b, 0x23,
	0x1c, 0x00,	0x1d, 0x08,	0x1e, 0xff,	0x1f, 0x01,
	0x10, 0x20,	0
पूर्ण;

अटल u8 bw2regs_analog[] = अणु
	0x14, 0xbb,	0x15, 0x2b,	0x16, 0x03,	0x17, 0x13,
	0x18, 0xb0,	0x19, 0x03,	0x1a, 0xa6,	0x1b, 0x22,
	0x1c, 0x01,	0x1d, 0x05,	0x1e, 0xff,	0x1f, 0x01,
	0x10, 0x20,	0
पूर्ण;

अटल u8 bw2regs_76hz[] = अणु
	0x14, 0xb7,	0x15, 0x27,	0x16, 0x03,	0x17, 0x0f,
	0x18, 0xae,	0x19, 0x03,	0x1a, 0xae,	0x1b, 0x2a,
	0x1c, 0x01,	0x1d, 0x09,	0x1e, 0xff,	0x1f, 0x01,
	0x10, 0x24,	0
पूर्ण;

अटल u8 bw2regs_66hz[] = अणु
	0x14, 0xbb,	0x15, 0x2b,	0x16, 0x04,	0x17, 0x14,
	0x18, 0xae,	0x19, 0x03,	0x1a, 0xa8,	0x1b, 0x24,
	0x1c, 0x01,	0x1d, 0x05,	0x1e, 0xff,	0x1f, 0x01,
	0x10, 0x20,	0
पूर्ण;

अटल पूर्णांक bw2_करो_शेष_mode(काष्ठा bw2_par *par, काष्ठा fb_info *info,
			       पूर्णांक *linebytes)
अणु
	u8 status, mon;
	u8 *p;

	status = sbus_पढ़ोb(&par->regs->status);
	mon = status & BWTWO_SR_RES_MASK;
	चयन (status & BWTWO_SR_ID_MASK) अणु
	हाल BWTWO_SR_ID_MONO_ECL:
		अगर (mon == BWTWO_SR_1600_1280) अणु
			p = bw2regs_1600;
			info->var.xres = info->var.xres_भव = 1600;
			info->var.yres = info->var.yres_भव = 1280;
			*linebytes = 1600 / 8;
		पूर्ण अन्यथा
			p = bw2regs_ecl;
		अवरोध;

	हाल BWTWO_SR_ID_MONO:
		p = bw2regs_analog;
		अवरोध;

	हाल BWTWO_SR_ID_MSYNC:
		अगर (mon == BWTWO_SR_1152_900_76_A ||
		    mon == BWTWO_SR_1152_900_76_B)
			p = bw2regs_76hz;
		अन्यथा
			p = bw2regs_66hz;
		अवरोध;

	हाल BWTWO_SR_ID_NOCONN:
		वापस 0;

	शेष:
		prपूर्णांकk(KERN_ERR "bw2: can't handle SR %02x\n",
		       status);
		वापस -EINVAL;
	पूर्ण
	क्रम ( ; *p; p += 2) अणु
		u8 __iomem *regp = &((u8 __iomem *)par->regs)[p[0]];
		sbus_ग_लिखोb(p[1], regp);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bw2_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा fb_info *info;
	काष्ठा bw2_par *par;
	पूर्णांक linebytes, err;

	info = framebuffer_alloc(माप(काष्ठा bw2_par), &op->dev);

	err = -ENOMEM;
	अगर (!info)
		जाओ out_err;
	par = info->par;

	spin_lock_init(&par->lock);

	info->fix.smem_start = op->resource[0].start;
	par->which_io = op->resource[0].flags & IORESOURCE_BITS;

	sbusfb_fill_var(&info->var, dp, 1);
	linebytes = of_getपूर्णांकprop_शेष(dp, "linebytes",
					  info->var.xres);

	info->var.red.length = info->var.green.length =
		info->var.blue.length = info->var.bits_per_pixel;
	info->var.red.offset = info->var.green.offset =
		info->var.blue.offset = 0;

	par->regs = of_ioremap(&op->resource[0], BWTWO_REGISTER_OFFSET,
			       माप(काष्ठा bw2_regs), "bw2 regs");
	अगर (!par->regs)
		जाओ out_release_fb;

	अगर (!of_find_property(dp, "width", शून्य)) अणु
		err = bw2_करो_शेष_mode(par, info, &linebytes);
		अगर (err)
			जाओ out_unmap_regs;
	पूर्ण

	info->fix.smem_len = PAGE_ALIGN(linebytes * info->var.yres);

	info->flags = FBINFO_DEFAULT;
	info->fbops = &bw2_ops;

	info->screen_base = of_ioremap(&op->resource[0], 0,
				       info->fix.smem_len, "bw2 ram");
	अगर (!info->screen_base) अणु
		err = -ENOMEM;
		जाओ out_unmap_regs;
	पूर्ण

	bw2_blank(FB_BLANK_UNBLANK, info);

	bw2_init_fix(info, linebytes);

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0)
		जाओ out_unmap_screen;

	dev_set_drvdata(&op->dev, info);

	prपूर्णांकk(KERN_INFO "%pOF: bwtwo at %lx:%lx\n",
	       dp, par->which_io, info->fix.smem_start);

	वापस 0;

out_unmap_screen:
	of_iounmap(&op->resource[0], info->screen_base, info->fix.smem_len);

out_unmap_regs:
	of_iounmap(&op->resource[0], par->regs, माप(काष्ठा bw2_regs));

out_release_fb:
	framebuffer_release(info);

out_err:
	वापस err;
पूर्ण

अटल पूर्णांक bw2_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(&op->dev);
	काष्ठा bw2_par *par = info->par;

	unरेजिस्टर_framebuffer(info);

	of_iounmap(&op->resource[0], par->regs, माप(काष्ठा bw2_regs));
	of_iounmap(&op->resource[0], info->screen_base, info->fix.smem_len);

	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bw2_match[] = अणु
	अणु
		.name = "bwtwo",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bw2_match);

अटल काष्ठा platक्रमm_driver bw2_driver = अणु
	.driver = अणु
		.name = "bw2",
		.of_match_table = bw2_match,
	पूर्ण,
	.probe		= bw2_probe,
	.हटाओ		= bw2_हटाओ,
पूर्ण;

अटल पूर्णांक __init bw2_init(व्योम)
अणु
	अगर (fb_get_options("bw2fb", शून्य))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&bw2_driver);
पूर्ण

अटल व्योम __निकास bw2_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&bw2_driver);
पूर्ण

module_init(bw2_init);
module_निकास(bw2_निकास);

MODULE_DESCRIPTION("framebuffer driver for BWTWO chipsets");
MODULE_AUTHOR("David S. Miller <davem@davemloft.net>");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
