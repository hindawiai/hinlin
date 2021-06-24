<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007 Google, Inc.
 * Copyright (C) 2012 Intel, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>

क्रमागत अणु
	FB_GET_WIDTH        = 0x00,
	FB_GET_HEIGHT       = 0x04,
	FB_INT_STATUS       = 0x08,
	FB_INT_ENABLE       = 0x0c,
	FB_SET_BASE         = 0x10,
	FB_SET_ROTATION     = 0x14,
	FB_SET_BLANK        = 0x18,
	FB_GET_PHYS_WIDTH   = 0x1c,
	FB_GET_PHYS_HEIGHT  = 0x20,

	FB_INT_VSYNC             = 1U << 0,
	FB_INT_BASE_UPDATE_DONE  = 1U << 1
पूर्ण;

काष्ठा goldfish_fb अणु
	व्योम __iomem *reg_base;
	पूर्णांक irq;
	spinlock_t lock;
	रुको_queue_head_t रुको;
	पूर्णांक base_update_count;
	पूर्णांक rotation;
	काष्ठा fb_info fb;
	u32 cmap[16];
पूर्ण;

अटल irqवापस_t goldfish_fb_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ irq_flags;
	काष्ठा goldfish_fb *fb = dev_id;
	u32 status;

	spin_lock_irqsave(&fb->lock, irq_flags);
	status = पढ़ोl(fb->reg_base + FB_INT_STATUS);
	अगर (status & FB_INT_BASE_UPDATE_DONE) अणु
		fb->base_update_count++;
		wake_up(&fb->रुको);
	पूर्ण
	spin_unlock_irqrestore(&fb->lock, irq_flags);
	वापस status ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल अंतरभूत u32 convert_bitfield(पूर्णांक val, काष्ठा fb_bitfield *bf)
अणु
	अचिन्हित पूर्णांक mask = (1 << bf->length) - 1;

	वापस (val >> (16 - bf->length) & mask) << bf->offset;
पूर्ण

अटल पूर्णांक
goldfish_fb_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red, अचिन्हित पूर्णांक green,
		 अचिन्हित पूर्णांक blue, अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा goldfish_fb *fb = container_of(info, काष्ठा goldfish_fb, fb);

	अगर (regno < 16) अणु
		fb->cmap[regno] = convert_bitfield(transp, &fb->fb.var.transp) |
				  convert_bitfield(blue, &fb->fb.var.blue) |
				  convert_bitfield(green, &fb->fb.var.green) |
				  convert_bitfield(red, &fb->fb.var.red);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक goldfish_fb_check_var(काष्ठा fb_var_screeninfo *var,
							काष्ठा fb_info *info)
अणु
	अगर ((var->rotate & 1) != (info->var.rotate & 1)) अणु
		अगर ((var->xres != info->var.yres) ||
				(var->yres != info->var.xres) ||
				(var->xres_भव != info->var.yres) ||
				(var->yres_भव > info->var.xres * 2) ||
				(var->yres_भव < info->var.xres)) अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((var->xres != info->var.xres) ||
		   (var->yres != info->var.yres) ||
		   (var->xres_भव != info->var.xres) ||
		   (var->yres_भव > info->var.yres * 2) ||
		   (var->yres_भव < info->var.yres)) अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर ((var->xoffset != info->var.xoffset) ||
			(var->bits_per_pixel != info->var.bits_per_pixel) ||
			(var->grayscale != info->var.grayscale)) अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक goldfish_fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा goldfish_fb *fb = container_of(info, काष्ठा goldfish_fb, fb);

	अगर (fb->rotation != fb->fb.var.rotate) अणु
		info->fix.line_length = info->var.xres * 2;
		fb->rotation = fb->fb.var.rotate;
		ग_लिखोl(fb->rotation, fb->reg_base + FB_SET_ROTATION);
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक goldfish_fb_pan_display(काष्ठा fb_var_screeninfo *var,
							काष्ठा fb_info *info)
अणु
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक base_update_count;
	काष्ठा goldfish_fb *fb = container_of(info, काष्ठा goldfish_fb, fb);

	spin_lock_irqsave(&fb->lock, irq_flags);
	base_update_count = fb->base_update_count;
	ग_लिखोl(fb->fb.fix.smem_start + fb->fb.var.xres * 2 * var->yoffset,
						fb->reg_base + FB_SET_BASE);
	spin_unlock_irqrestore(&fb->lock, irq_flags);
	रुको_event_समयout(fb->रुको,
			fb->base_update_count != base_update_count, HZ / 15);
	अगर (fb->base_update_count == base_update_count)
		pr_err("%s: timeout waiting for base update\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक goldfish_fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा goldfish_fb *fb = container_of(info, काष्ठा goldfish_fb, fb);

	चयन (blank) अणु
	हाल FB_BLANK_NORMAL:
		ग_लिखोl(1, fb->reg_base + FB_SET_BLANK);
		अवरोध;
	हाल FB_BLANK_UNBLANK:
		ग_लिखोl(0, fb->reg_base + FB_SET_BLANK);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops goldfish_fb_ops = अणु
	.owner          = THIS_MODULE,
	.fb_check_var   = goldfish_fb_check_var,
	.fb_set_par     = goldfish_fb_set_par,
	.fb_setcolreg   = goldfish_fb_setcolreg,
	.fb_pan_display = goldfish_fb_pan_display,
	.fb_blank	= goldfish_fb_blank,
	.fb_fillrect    = cfb_fillrect,
	.fb_copyarea    = cfb_copyarea,
	.fb_imageblit   = cfb_imageblit,
पूर्ण;


अटल पूर्णांक goldfish_fb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा resource *r;
	काष्ठा goldfish_fb *fb;
	माप_प्रकार framesize;
	u32 width, height;
	dma_addr_t fbpaddr;

	fb = kzalloc(माप(*fb), GFP_KERNEL);
	अगर (fb == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_fb_alloc_failed;
	पूर्ण
	spin_lock_init(&fb->lock);
	init_रुकोqueue_head(&fb->रुको);
	platक्रमm_set_drvdata(pdev, fb);

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (r == शून्य) अणु
		ret = -ENODEV;
		जाओ err_no_io_base;
	पूर्ण
	fb->reg_base = ioremap(r->start, PAGE_SIZE);
	अगर (fb->reg_base == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_no_io_base;
	पूर्ण

	fb->irq = platक्रमm_get_irq(pdev, 0);
	अगर (fb->irq <= 0) अणु
		ret = -ENODEV;
		जाओ err_no_irq;
	पूर्ण

	width = पढ़ोl(fb->reg_base + FB_GET_WIDTH);
	height = पढ़ोl(fb->reg_base + FB_GET_HEIGHT);

	fb->fb.fbops		= &goldfish_fb_ops;
	fb->fb.flags		= FBINFO_FLAG_DEFAULT;
	fb->fb.pseuकरो_palette	= fb->cmap;
	fb->fb.fix.type		= FB_TYPE_PACKED_PIXELS;
	fb->fb.fix.visual = FB_VISUAL_TRUECOLOR;
	fb->fb.fix.line_length = width * 2;
	fb->fb.fix.accel	= FB_ACCEL_NONE;
	fb->fb.fix.ypanstep = 1;

	fb->fb.var.xres		= width;
	fb->fb.var.yres		= height;
	fb->fb.var.xres_भव	= width;
	fb->fb.var.yres_भव	= height * 2;
	fb->fb.var.bits_per_pixel = 16;
	fb->fb.var.activate	= FB_ACTIVATE_NOW;
	fb->fb.var.height	= पढ़ोl(fb->reg_base + FB_GET_PHYS_HEIGHT);
	fb->fb.var.width	= पढ़ोl(fb->reg_base + FB_GET_PHYS_WIDTH);
	fb->fb.var.pixघड़ी	= 0;

	fb->fb.var.red.offset = 11;
	fb->fb.var.red.length = 5;
	fb->fb.var.green.offset = 5;
	fb->fb.var.green.length = 6;
	fb->fb.var.blue.offset = 0;
	fb->fb.var.blue.length = 5;

	framesize = width * height * 2 * 2;
	fb->fb.screen_base = (अक्षर __क्रमce __iomem *)dma_alloc_coherent(
						&pdev->dev, framesize,
						&fbpaddr, GFP_KERNEL);
	pr_debug("allocating frame buffer %d * %d, got %p\n",
					width, height, fb->fb.screen_base);
	अगर (fb->fb.screen_base == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_alloc_screen_base_failed;
	पूर्ण
	fb->fb.fix.smem_start = fbpaddr;
	fb->fb.fix.smem_len = framesize;

	ret = fb_set_var(&fb->fb, &fb->fb.var);
	अगर (ret)
		जाओ err_fb_set_var_failed;

	ret = request_irq(fb->irq, goldfish_fb_पूर्णांकerrupt, IRQF_SHARED,
							pdev->name, fb);
	अगर (ret)
		जाओ err_request_irq_failed;

	ग_लिखोl(FB_INT_BASE_UPDATE_DONE, fb->reg_base + FB_INT_ENABLE);
	goldfish_fb_pan_display(&fb->fb.var, &fb->fb); /* updates base */

	ret = रेजिस्टर_framebuffer(&fb->fb);
	अगर (ret)
		जाओ err_रेजिस्टर_framebuffer_failed;
	वापस 0;

err_रेजिस्टर_framebuffer_failed:
	मुक्त_irq(fb->irq, fb);
err_request_irq_failed:
err_fb_set_var_failed:
	dma_मुक्त_coherent(&pdev->dev, framesize,
				(व्योम *)fb->fb.screen_base,
				fb->fb.fix.smem_start);
err_alloc_screen_base_failed:
err_no_irq:
	iounmap(fb->reg_base);
err_no_io_base:
	kमुक्त(fb);
err_fb_alloc_failed:
	वापस ret;
पूर्ण

अटल पूर्णांक goldfish_fb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	माप_प्रकार framesize;
	काष्ठा goldfish_fb *fb = platक्रमm_get_drvdata(pdev);

	framesize = fb->fb.var.xres_भव * fb->fb.var.yres_भव * 2;
	unरेजिस्टर_framebuffer(&fb->fb);
	मुक्त_irq(fb->irq, fb);

	dma_मुक्त_coherent(&pdev->dev, framesize, (व्योम *)fb->fb.screen_base,
						fb->fb.fix.smem_start);
	iounmap(fb->reg_base);
	kमुक्त(fb);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id goldfish_fb_of_match[] = अणु
	अणु .compatible = "google,goldfish-fb", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, goldfish_fb_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id goldfish_fb_acpi_match[] = अणु
	अणु "GFSH0004", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, goldfish_fb_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver goldfish_fb_driver = अणु
	.probe		= goldfish_fb_probe,
	.हटाओ		= goldfish_fb_हटाओ,
	.driver = अणु
		.name = "goldfish_fb",
		.of_match_table = goldfish_fb_of_match,
		.acpi_match_table = ACPI_PTR(goldfish_fb_acpi_match),
	पूर्ण
पूर्ण;

module_platक्रमm_driver(goldfish_fb_driver);

MODULE_LICENSE("GPL v2");
