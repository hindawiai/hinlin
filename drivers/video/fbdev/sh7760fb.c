<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7760/SH7763 LCDC Framebuffer driver.
 *
 * (c) 2006-2008 MSC Vertriebsges.m.b.H.,
 *             Manuel Lauss <mano@roarinelk.homelinux.net>
 * (c) 2008 Nobuhiro Iwamatsu <iwamatsu.nobuhiro@renesas.com>
 *
 * PLEASE HAVE A LOOK AT Documentation/fb/sh7760fb.rst!
 *
 * Thanks to Siegfried Schaefer <s.schaefer at schaefer-edv.de>
 *     क्रम his original source and testing!
 *
 * sh7760_setcolreg get from drivers/video/sh_mobile_lcdcfb.c
 */

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fb.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/sh7760fb.h>

काष्ठा sh7760fb_par अणु
	व्योम __iomem *base;
	पूर्णांक irq;

	काष्ठा sh7760fb_platdata *pd;	/* display inक्रमmation */

	dma_addr_t fbdma;	/* physical address */

	पूर्णांक rot;		/* rotation enabled? */

	u32 pseuकरो_palette[16];

	काष्ठा platक्रमm_device *dev;
	काष्ठा resource *ioarea;
	काष्ठा completion vsync;	/* vsync irq event */
पूर्ण;

अटल irqवापस_t sh7760fb_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा completion *c = data;

	complete(c);

	वापस IRQ_HANDLED;
पूर्ण

/* रुको_क्रम_lps - रुको until घातer supply has reached a certain state. */
अटल पूर्णांक रुको_क्रम_lps(काष्ठा sh7760fb_par *par, पूर्णांक val)
अणु
	पूर्णांक i = 100;
	जबतक (--i && ((ioपढ़ो16(par->base + LDPMMR) & 3) != val))
		msleep(1);

	अगर (i <= 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

/* en/disable the LCDC */
अटल पूर्णांक sh7760fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा sh7760fb_par *par = info->par;
	काष्ठा sh7760fb_platdata *pd = par->pd;
	अचिन्हित लघु cntr = ioपढ़ो16(par->base + LDCNTR);
	अचिन्हित लघु पूर्णांकr = ioपढ़ो16(par->base + LDINTR);
	पूर्णांक lps;

	अगर (blank == FB_BLANK_UNBLANK) अणु
		पूर्णांकr |= VINT_START;
		cntr = LDCNTR_DON2 | LDCNTR_DON;
		lps = 3;
	पूर्ण अन्यथा अणु
		पूर्णांकr &= ~VINT_START;
		cntr = LDCNTR_DON2;
		lps = 0;
	पूर्ण

	अगर (pd->blank)
		pd->blank(blank);

	ioग_लिखो16(पूर्णांकr, par->base + LDINTR);
	ioग_लिखो16(cntr, par->base + LDCNTR);

	वापस रुको_क्रम_lps(par, lps);
पूर्ण

अटल पूर्णांक sh7760_setcolreg (u_पूर्णांक regno,
	u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
	u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	u32 *palette = info->pseuकरो_palette;

	अगर (regno >= 16)
		वापस -EINVAL;

	/* only FB_VISUAL_TRUECOLOR supported */

	red >>= 16 - info->var.red.length;
	green >>= 16 - info->var.green.length;
	blue >>= 16 - info->var.blue.length;
	transp >>= 16 - info->var.transp.length;

	palette[regno] = (red << info->var.red.offset) |
		(green << info->var.green.offset) |
		(blue << info->var.blue.offset) |
		(transp << info->var.transp.offset);

	वापस 0;
पूर्ण

अटल पूर्णांक sh7760fb_get_color_info(काष्ठा device *dev,
				   u16 lddfr, पूर्णांक *bpp, पूर्णांक *gray)
अणु
	पूर्णांक lbpp, lgray;

	lgray = lbpp = 0;

	चयन (lddfr & LDDFR_COLOR_MASK) अणु
	हाल LDDFR_1BPP_MONO:
		lgray = 1;
		lbpp = 1;
		अवरोध;
	हाल LDDFR_2BPP_MONO:
		lgray = 1;
		lbpp = 2;
		अवरोध;
	हाल LDDFR_4BPP_MONO:
		lgray = 1;
	हाल LDDFR_4BPP:
		lbpp = 4;
		अवरोध;
	हाल LDDFR_6BPP_MONO:
		lgray = 1;
	हाल LDDFR_8BPP:
		lbpp = 8;
		अवरोध;
	हाल LDDFR_16BPP_RGB555:
	हाल LDDFR_16BPP_RGB565:
		lbpp = 16;
		lgray = 0;
		अवरोध;
	शेष:
		dev_dbg(dev, "unsupported LDDFR bit depth.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (bpp)
		*bpp = lbpp;
	अगर (gray)
		*gray = lgray;

	वापस 0;
पूर्ण

अटल पूर्णांक sh7760fb_check_var(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	काष्ठा fb_fix_screeninfo *fix = &info->fix;
	काष्ठा sh7760fb_par *par = info->par;
	पूर्णांक ret, bpp;

	/* get color info from रेजिस्टर value */
	ret = sh7760fb_get_color_info(info->dev, par->pd->lddfr, &bpp, शून्य);
	अगर (ret)
		वापस ret;

	var->bits_per_pixel = bpp;

	अगर ((var->grayscale) && (var->bits_per_pixel == 1))
		fix->visual = FB_VISUAL_MONO10;
	अन्यथा अगर (var->bits_per_pixel >= 15)
		fix->visual = FB_VISUAL_TRUECOLOR;
	अन्यथा
		fix->visual = FB_VISUAL_PSEUDOCOLOR;

	/* TODO: add some more validation here */
	वापस 0;
पूर्ण

/*
 * sh7760fb_set_par - set videomode.
 *
 * NOTE: The rotation, grayscale and DSTN codepaths are
 *     totally untested!
 */
अटल पूर्णांक sh7760fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा sh7760fb_par *par = info->par;
	काष्ठा fb_videomode *vm = par->pd->def_mode;
	अचिन्हित दीर्घ sbase, dstn_off, ldsarl, stride;
	अचिन्हित लघु hsynp, hsynw, htcn, hdcn;
	अचिन्हित लघु vsynp, vsynw, vtln, vdln;
	अचिन्हित लघु lddfr, ldmtr;
	पूर्णांक ret, bpp, gray;

	par->rot = par->pd->rotate;

	/* rotate only works with xres <= 320 */
	अगर (par->rot && (vm->xres > 320)) अणु
		dev_dbg(info->dev, "rotation disabled due to display size\n");
		par->rot = 0;
	पूर्ण

	/* calculate LCDC reg vals from display parameters */
	hsynp = vm->right_margin + vm->xres;
	hsynw = vm->hsync_len;
	htcn = vm->left_margin + hsynp + hsynw;
	hdcn = vm->xres;
	vsynp = vm->lower_margin + vm->yres;
	vsynw = vm->vsync_len;
	vtln = vm->upper_margin + vsynp + vsynw;
	vdln = vm->yres;

	/* get color info from रेजिस्टर value */
	ret = sh7760fb_get_color_info(info->dev, par->pd->lddfr, &bpp, &gray);
	अगर (ret)
		वापस ret;

	dev_dbg(info->dev, "%dx%d %dbpp %s (orientation %s)\n", hdcn,
		vdln, bpp, gray ? "grayscale" : "color",
		par->rot ? "rotated" : "normal");

#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
	lddfr = par->pd->lddfr | (1 << 8);
#अन्यथा
	lddfr = par->pd->lddfr & ~(1 << 8);
#पूर्ण_अगर

	ldmtr = par->pd->ldmtr;

	अगर (!(vm->sync & FB_SYNC_HOR_HIGH_ACT))
		ldmtr |= LDMTR_CL1POL;
	अगर (!(vm->sync & FB_SYNC_VERT_HIGH_ACT))
		ldmtr |= LDMTR_FLMPOL;

	/* shut करोwn LCDC beक्रमe changing display parameters */
	sh7760fb_blank(FB_BLANK_POWERDOWN, info);

	ioग_लिखो16(par->pd->ldickr, par->base + LDICKR);	/* pixघड़ी */
	ioग_लिखो16(ldmtr, par->base + LDMTR);	/* polarities */
	ioग_लिखो16(lddfr, par->base + LDDFR);	/* color/depth */
	ioग_लिखो16((par->rot ? 1 << 13 : 0), par->base + LDSMR);	/* rotate */
	ioग_लिखो16(par->pd->ldpmmr, par->base + LDPMMR);	/* Power Management */
	ioग_लिखो16(par->pd->ldpspr, par->base + LDPSPR);	/* Power Supply Ctrl */

	/* display resolution */
	ioग_लिखो16(((htcn >> 3) - 1) | (((hdcn >> 3) - 1) << 8),
		  par->base + LDHCNR);
	ioग_लिखो16(vdln - 1, par->base + LDVDLNR);
	ioग_लिखो16(vtln - 1, par->base + LDVTLNR);
	/* h/v sync संकेतs */
	ioग_लिखो16((vsynp - 1) | ((vsynw - 1) << 12), par->base + LDVSYNR);
	ioग_लिखो16(((hsynp >> 3) - 1) | (((hsynw >> 3) - 1) << 12),
		  par->base + LDHSYNR);
	/* AC modulation sig */
	ioग_लिखो16(par->pd->ldaclnr, par->base + LDACLNR);

	stride = (par->rot) ? vtln : hdcn;
	अगर (!gray)
		stride *= (bpp + 7) >> 3;
	अन्यथा अणु
		अगर (bpp == 1)
			stride >>= 3;
		अन्यथा अगर (bpp == 2)
			stride >>= 2;
		अन्यथा अगर (bpp == 4)
			stride >>= 1;
		/* 6 bpp == 8 bpp */
	पूर्ण

	/* अगर rotated, stride must be घातer of 2 */
	अगर (par->rot) अणु
		अचिन्हित दीर्घ bit = 1 << 31;
		जबतक (bit) अणु
			अगर (stride & bit)
				अवरोध;
			bit >>= 1;
		पूर्ण
		अगर (stride & ~bit)
			stride = bit << 1;	/* not P-o-2, round up */
	पूर्ण
	ioग_लिखो16(stride, par->base + LDLAOR);

	/* set display mem start address */
	sbase = (अचिन्हित दीर्घ)par->fbdma;
	अगर (par->rot)
		sbase += (hdcn - 1) * stride;

	ioग_लिखो32(sbase, par->base + LDSARU);

	/*
	 * क्रम DSTN need to set address क्रम lower half.
	 * I (mlau) करोn't know which address to set it to,
	 * so I guessed at (stride * yres/2).
	 */
	अगर (((ldmtr & 0x003f) >= LDMTR_DSTN_MONO_8) &&
	    ((ldmtr & 0x003f) <= LDMTR_DSTN_COLOR_16)) अणु

		dev_dbg(info->dev, " ***** DSTN untested! *****\n");

		dstn_off = stride;
		अगर (par->rot)
			dstn_off *= hdcn >> 1;
		अन्यथा
			dstn_off *= vdln >> 1;

		ldsarl = sbase + dstn_off;
	पूर्ण अन्यथा
		ldsarl = 0;

	ioग_लिखो32(ldsarl, par->base + LDSARL);	/* mem क्रम lower half of DSTN */

	info->fix.line_length = stride;

	sh7760fb_check_var(&info->var, info);

	sh7760fb_blank(FB_BLANK_UNBLANK, info);	/* panel on! */

	dev_dbg(info->dev, "hdcn  : %6d htcn  : %6d\n", hdcn, htcn);
	dev_dbg(info->dev, "hsynw : %6d hsynp : %6d\n", hsynw, hsynp);
	dev_dbg(info->dev, "vdln  : %6d vtln  : %6d\n", vdln, vtln);
	dev_dbg(info->dev, "vsynw : %6d vsynp : %6d\n", vsynw, vsynp);
	dev_dbg(info->dev, "clksrc: %6d clkdiv: %6d\n",
		(par->pd->ldickr >> 12) & 3, par->pd->ldickr & 0x1f);
	dev_dbg(info->dev, "ldpmmr: 0x%04x ldpspr: 0x%04x\n", par->pd->ldpmmr,
		par->pd->ldpspr);
	dev_dbg(info->dev, "ldmtr : 0x%04x lddfr : 0x%04x\n", ldmtr, lddfr);
	dev_dbg(info->dev, "ldlaor: %ld\n", stride);
	dev_dbg(info->dev, "ldsaru: 0x%08lx ldsarl: 0x%08lx\n", sbase, ldsarl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops sh7760fb_ops = अणु
	.owner = THIS_MODULE,
	.fb_blank = sh7760fb_blank,
	.fb_check_var = sh7760fb_check_var,
	.fb_setcolreg = sh7760_setcolreg,
	.fb_set_par = sh7760fb_set_par,
	.fb_fillrect = cfb_fillrect,
	.fb_copyarea = cfb_copyarea,
	.fb_imageblit = cfb_imageblit,
पूर्ण;

अटल व्योम sh7760fb_मुक्त_mem(काष्ठा fb_info *info)
अणु
	काष्ठा sh7760fb_par *par = info->par;

	अगर (!info->screen_base)
		वापस;

	dma_मुक्त_coherent(info->dev, info->screen_size,
			  info->screen_base, par->fbdma);

	par->fbdma = 0;
	info->screen_base = शून्य;
	info->screen_size = 0;
पूर्ण

/* allocate the framebuffer memory. This memory must be in Area3,
 * (dictated by the DMA engine) and contiguous, at a 512 byte boundary.
 */
अटल पूर्णांक sh7760fb_alloc_mem(काष्ठा fb_info *info)
अणु
	काष्ठा sh7760fb_par *par = info->par;
	व्योम *fbmem;
	अचिन्हित दीर्घ vram;
	पूर्णांक ret, bpp;

	अगर (info->screen_base)
		वापस 0;

	/* get color info from रेजिस्टर value */
	ret = sh7760fb_get_color_info(info->dev, par->pd->lddfr, &bpp, शून्य);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "colinfo\n");
		वापस ret;
	पूर्ण

	/* min VRAM: xres_min = 16, yres_min = 1, bpp = 1: 2byte -> 1 page
	   max VRAM: xres_max = 1024, yres_max = 1024, bpp = 16: 2MB */

	vram = info->var.xres * info->var.yres;
	अगर (info->var.grayscale) अणु
		अगर (bpp == 1)
			vram >>= 3;
		अन्यथा अगर (bpp == 2)
			vram >>= 2;
		अन्यथा अगर (bpp == 4)
			vram >>= 1;
	पूर्ण अन्यथा अगर (bpp > 8)
		vram *= 2;
	अगर ((vram < 1) || (vram > 1024 * 2048)) अणु
		dev_dbg(info->dev, "too much VRAM required. Check settings\n");
		वापस -ENODEV;
	पूर्ण

	अगर (vram < PAGE_SIZE)
		vram = PAGE_SIZE;

	fbmem = dma_alloc_coherent(info->dev, vram, &par->fbdma, GFP_KERNEL);

	अगर (!fbmem)
		वापस -ENOMEM;

	अगर ((par->fbdma & SH7760FB_DMA_MASK) != SH7760FB_DMA_MASK) अणु
		sh7760fb_मुक्त_mem(info);
		dev_err(info->dev, "kernel gave me memory at 0x%08lx, which is"
			"unusable for the LCDC\n", (अचिन्हित दीर्घ)par->fbdma);
		वापस -ENOMEM;
	पूर्ण

	info->screen_base = fbmem;
	info->screen_size = vram;
	info->fix.smem_start = (अचिन्हित दीर्घ)info->screen_base;
	info->fix.smem_len = info->screen_size;

	वापस 0;
पूर्ण

अटल पूर्णांक sh7760fb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *info;
	काष्ठा resource *res;
	काष्ठा sh7760fb_par *par;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (unlikely(res == शून्य)) अणु
		dev_err(&pdev->dev, "invalid resource\n");
		वापस -EINVAL;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा sh7760fb_par), &pdev->dev);
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	par->dev = pdev;

	par->pd = pdev->dev.platक्रमm_data;
	अगर (!par->pd) अणु
		dev_dbg(info->dev, "no display setup data!\n");
		ret = -ENODEV;
		जाओ out_fb;
	पूर्ण

	par->ioarea = request_mem_region(res->start,
					 resource_size(res), pdev->name);
	अगर (!par->ioarea) अणु
		dev_err(&pdev->dev, "mmio area busy\n");
		ret = -EBUSY;
		जाओ out_fb;
	पूर्ण

	par->base = ioremap(res->start, resource_size(res));
	अगर (!par->base) अणु
		dev_err(&pdev->dev, "cannot remap\n");
		ret = -ENODEV;
		जाओ out_res;
	पूर्ण

	ioग_लिखो16(0, par->base + LDINTR);	/* disable vsync irq */
	par->irq = platक्रमm_get_irq(pdev, 0);
	अगर (par->irq >= 0) अणु
		ret = request_irq(par->irq, sh7760fb_irq, 0,
				  "sh7760-lcdc", &par->vsync);
		अगर (ret) अणु
			dev_err(&pdev->dev, "cannot grab IRQ\n");
			par->irq = -ENXIO;
		पूर्ण अन्यथा
			disable_irq_nosync(par->irq);
	पूर्ण

	fb_videomode_to_var(&info->var, par->pd->def_mode);

	ret = sh7760fb_alloc_mem(info);
	अगर (ret) अणु
		dev_dbg(info->dev, "framebuffer memory allocation failed!\n");
		जाओ out_unmap;
	पूर्ण

	info->pseuकरो_palette = par->pseuकरो_palette;

	/* fixup color रेजिस्टर bitpositions. These are fixed by hardware */
	info->var.red.offset = 11;
	info->var.red.length = 5;
	info->var.red.msb_right = 0;

	info->var.green.offset = 5;
	info->var.green.length = 6;
	info->var.green.msb_right = 0;

	info->var.blue.offset = 0;
	info->var.blue.length = 5;
	info->var.blue.msb_right = 0;

	info->var.transp.offset = 0;
	info->var.transp.length = 0;
	info->var.transp.msb_right = 0;

	म_नकल(info->fix.id, "sh7760-lcdc");

	/* set the DON2 bit now, beक्रमe cmap allocation, as it will अक्रमomize
	 * palette memory.
	 */
	ioग_लिखो16(LDCNTR_DON2, par->base + LDCNTR);
	info->fbops = &sh7760fb_ops;

	ret = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (ret) अणु
		dev_dbg(info->dev, "Unable to allocate cmap memory\n");
		जाओ out_mem;
	पूर्ण

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0) अणु
		dev_dbg(info->dev, "cannot register fb!\n");
		जाओ out_cmap;
	पूर्ण
	platक्रमm_set_drvdata(pdev, info);

	prपूर्णांकk(KERN_INFO "%s: memory at phys 0x%08lx-0x%08lx, size %ld KiB\n",
	       pdev->name,
	       (अचिन्हित दीर्घ)par->fbdma,
	       (अचिन्हित दीर्घ)(par->fbdma + info->screen_size - 1),
	       info->screen_size >> 10);

	वापस 0;

out_cmap:
	sh7760fb_blank(FB_BLANK_POWERDOWN, info);
	fb_dealloc_cmap(&info->cmap);
out_mem:
	sh7760fb_मुक्त_mem(info);
out_unmap:
	अगर (par->irq >= 0)
		मुक्त_irq(par->irq, &par->vsync);
	iounmap(par->base);
out_res:
	release_mem_region(res->start, resource_size(res));
out_fb:
	framebuffer_release(info);
	वापस ret;
पूर्ण

अटल पूर्णांक sh7760fb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);
	काष्ठा sh7760fb_par *par = info->par;

	sh7760fb_blank(FB_BLANK_POWERDOWN, info);
	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);
	sh7760fb_मुक्त_mem(info);
	अगर (par->irq >= 0)
		मुक्त_irq(par->irq, &par->vsync);
	iounmap(par->base);
	release_mem_region(par->ioarea->start, resource_size(par->ioarea));
	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sh7760_lcdc_driver = अणु
	.driver = अणु
		   .name = "sh7760-lcdc",
		   पूर्ण,
	.probe = sh7760fb_probe,
	.हटाओ = sh7760fb_हटाओ,
पूर्ण;

module_platक्रमm_driver(sh7760_lcdc_driver);

MODULE_AUTHOR("Nobuhiro Iwamatsu, Manuel Lauss");
MODULE_DESCRIPTION("FBdev for SH7760/63 integrated LCD Controller");
MODULE_LICENSE("GPL v2");
