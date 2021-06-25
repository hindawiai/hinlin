<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Aeroflex Gaisler SVGACTRL framebuffer device.
 *
 * 2011 (c) Aeroflex Gaisler AB
 *
 * Full करोcumentation of the core can be found here:
 * https://www.gaisler.com/products/grlib/grip.pdf
 *
 * Contributors: Kristoffer Glembo <kristoffer@gaisler.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/mm.h>
#समावेश <linux/fb.h>
#समावेश <linux/पन.स>

काष्ठा grvga_regs अणु
	u32 status; 		/* 0x00 */
	u32 video_length; 	/* 0x04 */
	u32 front_porch;	/* 0x08 */
	u32 sync_length;	/* 0x0C */
	u32 line_length;	/* 0x10 */
	u32 fb_pos;		/* 0x14 */
	u32 clk_vector[4];	/* 0x18 */
	u32 clut;	        /* 0x20 */
पूर्ण;

काष्ठा grvga_par अणु
	काष्ठा grvga_regs *regs;
	u32 color_palette[16];  /* 16 entry pseuकरो palette used by fbcon in true color mode */
	पूर्णांक clk_sel;
	पूर्णांक fb_alloced;         /* = 1 अगर framebuffer is allocated in मुख्य memory */
पूर्ण;


अटल स्थिर काष्ठा fb_videomode grvga_modedb[] = अणु
    अणु
	/* 640x480 @ 60 Hz */
	शून्य, 60, 640, 480, 40000, 48, 16, 39, 11, 96, 2,
	0, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 800x600 @ 60 Hz */
	शून्य, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
	0, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 800x600 @ 72 Hz */
	शून्य, 72, 800, 600, 20000, 64, 56, 23, 37, 120, 6,
	0, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 1024x768 @ 60 Hz */
	शून्य, 60, 1024, 768, 15385, 160, 24, 29, 3, 136, 6,
	0, FB_VMODE_NONINTERLACED
    पूर्ण
 पूर्ण;

अटल स्थिर काष्ठा fb_fix_screeninfo grvga_fix = अणु
	.id =		"AG SVGACTRL",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =       FB_VISUAL_PSEUDOCOLOR,
	.xpanstep =	0,
	.ypanstep =	1,
	.ywrapstep =	0,
	.accel =	FB_ACCEL_NONE,
पूर्ण;

अटल पूर्णांक grvga_check_var(काष्ठा fb_var_screeninfo *var,
			   काष्ठा fb_info *info)
अणु
	काष्ठा grvga_par *par = info->par;
	पूर्णांक i;

	अगर (!var->xres)
		var->xres = 1;
	अगर (!var->yres)
		var->yres = 1;
	अगर (var->bits_per_pixel <= 8)
		var->bits_per_pixel = 8;
	अन्यथा अगर (var->bits_per_pixel <= 16)
		var->bits_per_pixel = 16;
	अन्यथा अगर (var->bits_per_pixel <= 24)
		var->bits_per_pixel = 24;
	अन्यथा अगर (var->bits_per_pixel <= 32)
		var->bits_per_pixel = 32;
	अन्यथा
		वापस -EINVAL;

	var->xres_भव = var->xres;
	var->yres_भव = 2*var->yres;

	अगर (info->fix.smem_len) अणु
		अगर ((var->yres_भव*var->xres_भव*var->bits_per_pixel/8) > info->fix.smem_len)
			वापस -ENOMEM;
	पूर्ण

	/* Which घड़ीs that are available can be पढ़ो out in these रेजिस्टरs */
	क्रम (i = 0; i <= 3 ; i++) अणु
		अगर (var->pixघड़ी == par->regs->clk_vector[i])
			अवरोध;
	पूर्ण
	अगर (i <= 3)
		par->clk_sel = i;
	अन्यथा
		वापस -EINVAL;

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		var->red   = (काष्ठा fb_bitfield) अणु0, 8, 0पूर्ण;      /* offset, length, msb-right */
		var->green = (काष्ठा fb_bitfield) अणु0, 8, 0पूर्ण;
		var->blue  = (काष्ठा fb_bitfield) अणु0, 8, 0पूर्ण;
		var->transp = (काष्ठा fb_bitfield) अणु0, 0, 0पूर्ण;
		अवरोध;
	हाल 16:
		var->red   = (काष्ठा fb_bitfield) अणु11, 5, 0पूर्ण;
		var->green = (काष्ठा fb_bitfield) अणु5, 6, 0पूर्ण;
		var->blue  = (काष्ठा fb_bitfield) अणु0, 5, 0पूर्ण;
		var->transp = (काष्ठा fb_bitfield) अणु0, 0, 0पूर्ण;
		अवरोध;
	हाल 24:
	हाल 32:
		var->red   = (काष्ठा fb_bitfield) अणु16, 8, 0पूर्ण;
		var->green = (काष्ठा fb_bitfield) अणु8, 8, 0पूर्ण;
		var->blue  = (काष्ठा fb_bitfield) अणु0, 8, 0पूर्ण;
		var->transp = (काष्ठा fb_bitfield) अणु24, 8, 0पूर्ण;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक grvga_set_par(काष्ठा fb_info *info)
अणु

	u32 func = 0;
	काष्ठा grvga_par *par = info->par;

	__raw_ग_लिखोl(((info->var.yres - 1) << 16) | (info->var.xres - 1),
		     &par->regs->video_length);

	__raw_ग_लिखोl((info->var.lower_margin << 16) | (info->var.right_margin),
		     &par->regs->front_porch);

	__raw_ग_लिखोl((info->var.vsync_len << 16) | (info->var.hsync_len),
		     &par->regs->sync_length);

	__raw_ग_लिखोl(((info->var.yres + info->var.lower_margin + info->var.upper_margin + info->var.vsync_len - 1) << 16) |
		     (info->var.xres + info->var.right_margin + info->var.left_margin + info->var.hsync_len - 1),
		     &par->regs->line_length);

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		func = 1;
		अवरोध;
	हाल 16:
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		func = 2;
		अवरोध;
	हाल 24:
	हाल 32:
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		func = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	__raw_ग_लिखोl((par->clk_sel << 6) | (func << 4) | 1,
		     &par->regs->status);

	info->fix.line_length = (info->var.xres_भव*info->var.bits_per_pixel)/8;
	वापस 0;
पूर्ण

अटल पूर्णांक grvga_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green, अचिन्हित blue, अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा grvga_par *par;
	par = info->par;

	अगर (regno >= 256)	/* Size of CLUT */
		वापस -EINVAL;

	अगर (info->var.grayscale) अणु
		/* grayscale = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	पूर्ण



#घोषणा CNVT_TOHW(val, width) ((((val)<<(width))+0x7FFF-(val))>>16)

	red    = CNVT_TOHW(red,   info->var.red.length);
	green  = CNVT_TOHW(green, info->var.green.length);
	blue   = CNVT_TOHW(blue,  info->var.blue.length);
	transp = CNVT_TOHW(transp, info->var.transp.length);

#अघोषित CNVT_TOHW

	/* In PSEUDOCOLOR we use the hardware CLUT */
	अगर (info->fix.visual == FB_VISUAL_PSEUDOCOLOR)
		__raw_ग_लिखोl((regno << 24) | (red << 16) | (green << 8) | blue,
			     &par->regs->clut);

	/* Truecolor uses the pseuकरो palette */
	अन्यथा अगर (info->fix.visual == FB_VISUAL_TRUECOLOR) अणु
		u32 v;
		अगर (regno >= 16)
			वापस -EINVAL;


		v =     (red    << info->var.red.offset)   |
			(green  << info->var.green.offset) |
			(blue   << info->var.blue.offset)  |
			(transp << info->var.transp.offset);

		((u32 *) (info->pseuकरो_palette))[regno] = v;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक grvga_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	काष्ठा grvga_par *par = info->par;
	काष्ठा fb_fix_screeninfo *fix = &info->fix;
	u32 base_addr;

	अगर (var->xoffset != 0)
		वापस -EINVAL;

	base_addr = fix->smem_start + (var->yoffset * fix->line_length);
	base_addr &= ~3UL;

	/* Set framebuffer base address  */
	__raw_ग_लिखोl(base_addr,
		     &par->regs->fb_pos);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops grvga_ops = अणु
	.owner          = THIS_MODULE,
	.fb_check_var   = grvga_check_var,
	.fb_set_par	= grvga_set_par,
	.fb_setcolreg   = grvga_setcolreg,
	.fb_pan_display = grvga_pan_display,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit
पूर्ण;

अटल पूर्णांक grvga_parse_custom(अक्षर *options,
			      काष्ठा fb_var_screeninfo *screendata)
अणु
	अक्षर *this_opt;
	पूर्णांक count = 0;
	अगर (!options || !*options)
		वापस -1;

	जबतक ((this_opt = strsep(&options, " ")) != शून्य) अणु
		अगर (!*this_opt)
			जारी;

		चयन (count) अणु
		हाल 0:
			screendata->pixघड़ी = simple_म_से_अदीर्घ(this_opt, शून्य, 0);
			count++;
			अवरोध;
		हाल 1:
			screendata->xres = screendata->xres_भव = simple_म_से_अदीर्घ(this_opt, शून्य, 0);
			count++;
			अवरोध;
		हाल 2:
			screendata->right_margin = simple_म_से_अदीर्घ(this_opt, शून्य, 0);
			count++;
			अवरोध;
		हाल 3:
			screendata->hsync_len = simple_म_से_अदीर्घ(this_opt, शून्य, 0);
			count++;
			अवरोध;
		हाल 4:
			screendata->left_margin = simple_म_से_अदीर्घ(this_opt, शून्य, 0);
			count++;
			अवरोध;
		हाल 5:
			screendata->yres = screendata->yres_भव = simple_म_से_अदीर्घ(this_opt, शून्य, 0);
			count++;
			अवरोध;
		हाल 6:
			screendata->lower_margin = simple_म_से_अदीर्घ(this_opt, शून्य, 0);
			count++;
			अवरोध;
		हाल 7:
			screendata->vsync_len = simple_म_से_अदीर्घ(this_opt, शून्य, 0);
			count++;
			अवरोध;
		हाल 8:
			screendata->upper_margin = simple_म_से_अदीर्घ(this_opt, शून्य, 0);
			count++;
			अवरोध;
		हाल 9:
			screendata->bits_per_pixel = simple_म_से_अदीर्घ(this_opt, शून्य, 0);
			count++;
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण
	पूर्ण
	screendata->activate  = FB_ACTIVATE_NOW;
	screendata->vmode     = FB_VMODE_NONINTERLACED;
	वापस 0;
पूर्ण

अटल पूर्णांक grvga_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info;
	पूर्णांक retval = -ENOMEM;
	अचिन्हित दीर्घ भव_start;
	अचिन्हित दीर्घ grvga_fix_addr = 0;
	अचिन्हित दीर्घ physical_start = 0;
	अचिन्हित दीर्घ grvga_mem_size = 0;
	काष्ठा grvga_par *par = शून्य;
	अक्षर *options = शून्य, *mode_opt = शून्य;

	info = framebuffer_alloc(माप(काष्ठा grvga_par), &dev->dev);
	अगर (!info)
		वापस -ENOMEM;

	/* Expecting: "grvga: modestring, [addr:<framebuffer physical address>], [size:<framebuffer size>]
	 *
	 * If modestring is custom:<custom mode string> we parse the string which then contains all videoparameters
	 * If address is left out, we allocate memory,
	 * अगर size is left out we only allocate enough to support the given mode.
	 */
	अगर (fb_get_options("grvga", &options)) अणु
		retval = -ENODEV;
		जाओ मुक्त_fb;
	पूर्ण

	अगर (!options || !*options)
		options =  "640x480-8@60";

	जबतक (1) अणु
		अक्षर *this_opt = strsep(&options, ",");

		अगर (!this_opt)
			अवरोध;

		अगर (!म_भेदन(this_opt, "custom", 6)) अणु
			अगर (grvga_parse_custom(this_opt, &info->var) < 0) अणु
				dev_err(&dev->dev, "Failed to parse custom mode (%s).\n", this_opt);
				retval = -EINVAL;
				जाओ मुक्त_fb;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "addr", 4))
			grvga_fix_addr = simple_म_से_अदीर्घ(this_opt + 5, शून्य, 16);
		अन्यथा अगर (!म_भेदन(this_opt, "size", 4))
			grvga_mem_size = simple_म_से_अदीर्घ(this_opt + 5, शून्य, 0);
		अन्यथा
			mode_opt = this_opt;
	पूर्ण

	par = info->par;
	info->fbops = &grvga_ops;
	info->fix = grvga_fix;
	info->pseuकरो_palette = par->color_palette;
	info->flags = FBINFO_DEFAULT | FBINFO_PARTIAL_PAN_OK | FBINFO_HWACCEL_YPAN;
	info->fix.smem_len = grvga_mem_size;

	अगर (!devm_request_mem_region(&dev->dev, dev->resource[0].start,
		    resource_size(&dev->resource[0]), "grlib-svgactrl regs")) अणु
		dev_err(&dev->dev, "registers already mapped\n");
		retval = -EBUSY;
		जाओ मुक्त_fb;
	पूर्ण

	par->regs = of_ioremap(&dev->resource[0], 0,
			       resource_size(&dev->resource[0]),
			       "grlib-svgactrl regs");

	अगर (!par->regs) अणु
		dev_err(&dev->dev, "failed to map registers\n");
		retval = -ENOMEM;
		जाओ मुक्त_fb;
	पूर्ण

	retval = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (retval < 0) अणु
		dev_err(&dev->dev, "failed to allocate mem with fb_alloc_cmap\n");
		retval = -ENOMEM;
		जाओ unmap_regs;
	पूर्ण

	अगर (mode_opt) अणु
		retval = fb_find_mode(&info->var, info, mode_opt,
				      grvga_modedb, माप(grvga_modedb), &grvga_modedb[0], 8);
		अगर (!retval || retval == 4) अणु
			retval = -EINVAL;
			जाओ dealloc_cmap;
		पूर्ण
	पूर्ण

	अगर (!grvga_mem_size)
		grvga_mem_size = info->var.xres_भव * info->var.yres_भव * info->var.bits_per_pixel/8;

	अगर (grvga_fix_addr) अणु
		/* Got framebuffer base address from argument list */

		physical_start = grvga_fix_addr;

		अगर (!devm_request_mem_region(&dev->dev, physical_start,
					     grvga_mem_size, dev->name)) अणु
			dev_err(&dev->dev, "failed to request memory region\n");
			retval = -ENOMEM;
			जाओ dealloc_cmap;
		पूर्ण

		भव_start = (अचिन्हित दीर्घ) ioremap(physical_start, grvga_mem_size);

		अगर (!भव_start) अणु
			dev_err(&dev->dev, "error mapping framebuffer memory\n");
			retval = -ENOMEM;
			जाओ dealloc_cmap;
		पूर्ण
	पूर्ण अन्यथा अणु	/* Allocate frambuffer memory */

		अचिन्हित दीर्घ page;

		भव_start = (अचिन्हित दीर्घ) __get_मुक्त_pages(GFP_DMA,
								 get_order(grvga_mem_size));
		अगर (!भव_start) अणु
			dev_err(&dev->dev,
				"unable to allocate framebuffer memory (%lu bytes)\n",
				grvga_mem_size);
			retval = -ENOMEM;
			जाओ dealloc_cmap;
		पूर्ण

		physical_start = dma_map_single(&dev->dev, (व्योम *)भव_start, grvga_mem_size, DMA_TO_DEVICE);

		/* Set page reserved so that mmap will work. This is necessary
		 * since we'll be remapping normal memory.
		 */
		क्रम (page = भव_start;
		     page < PAGE_ALIGN(भव_start + grvga_mem_size);
		     page += PAGE_SIZE) अणु
			SetPageReserved(virt_to_page(page));
		पूर्ण

		par->fb_alloced = 1;
	पूर्ण

	स_रखो((अचिन्हित दीर्घ *) भव_start, 0, grvga_mem_size);

	info->screen_base = (अक्षर __iomem *) भव_start;
	info->fix.smem_start = physical_start;
	info->fix.smem_len   = grvga_mem_size;

	dev_set_drvdata(&dev->dev, info);

	dev_info(&dev->dev,
		 "Aeroflex Gaisler framebuffer device (fb%d), %dx%d-%d, using %luK of video memory @ %p\n",
		 info->node, info->var.xres, info->var.yres, info->var.bits_per_pixel,
		 grvga_mem_size >> 10, info->screen_base);

	retval = रेजिस्टर_framebuffer(info);
	अगर (retval < 0) अणु
		dev_err(&dev->dev, "failed to register framebuffer\n");
		जाओ मुक्त_mem;
	पूर्ण

	__raw_ग_लिखोl(physical_start, &par->regs->fb_pos);
	__raw_ग_लिखोl(__raw_पढ़ोl(&par->regs->status) | 1,  /* Enable framebuffer */
		     &par->regs->status);

	वापस 0;

मुक्त_mem:
	अगर (grvga_fix_addr)
		iounmap((व्योम *)भव_start);
	अन्यथा
		kमुक्त((व्योम *)भव_start);
dealloc_cmap:
	fb_dealloc_cmap(&info->cmap);
unmap_regs:
	of_iounmap(&dev->resource[0], par->regs,
		   resource_size(&dev->resource[0]));
मुक्त_fb:
	framebuffer_release(info);

	वापस retval;
पूर्ण

अटल पूर्णांक grvga_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(&device->dev);
	काष्ठा grvga_par *par;

	अगर (info) अणु
		par = info->par;
		unरेजिस्टर_framebuffer(info);
		fb_dealloc_cmap(&info->cmap);

		of_iounmap(&device->resource[0], par->regs,
			   resource_size(&device->resource[0]));

		अगर (!par->fb_alloced)
			iounmap(info->screen_base);
		अन्यथा
			kमुक्त((व्योम *)info->screen_base);

		framebuffer_release(info);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा of_device_id svgactrl_of_match[] = अणु
	अणु
		.name = "GAISLER_SVGACTRL",
	पूर्ण,
	अणु
		.name = "01_063",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, svgactrl_of_match);

अटल काष्ठा platक्रमm_driver grvga_driver = अणु
	.driver = अणु
		.name = "grlib-svgactrl",
		.of_match_table = svgactrl_of_match,
	पूर्ण,
	.probe		= grvga_probe,
	.हटाओ		= grvga_हटाओ,
पूर्ण;

module_platक्रमm_driver(grvga_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aeroflex Gaisler");
MODULE_DESCRIPTION("Aeroflex Gaisler framebuffer device driver");
