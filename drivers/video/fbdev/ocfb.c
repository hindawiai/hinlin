<शैली गुरु>
/*
 * OpenCores VGA/LCD 2.0 core frame buffer driver
 *
 * Copyright (C) 2013 Stefan Kristiansson, stefan.kristiansson@saunalahti.fi
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

/* OCFB रेजिस्टर defines */
#घोषणा OCFB_CTRL	0x000
#घोषणा OCFB_STAT	0x004
#घोषणा OCFB_HTIM	0x008
#घोषणा OCFB_VTIM	0x00c
#घोषणा OCFB_HVLEN	0x010
#घोषणा OCFB_VBARA	0x014
#घोषणा OCFB_PALETTE	0x800

#घोषणा OCFB_CTRL_VEN	0x00000001 /* Video Enable */
#घोषणा OCFB_CTRL_HIE	0x00000002 /* HSync Interrupt Enable */
#घोषणा OCFB_CTRL_PC	0x00000800 /* 8-bit Pseuकरो Color Enable*/
#घोषणा OCFB_CTRL_CD8	0x00000000 /* Color Depth 8 */
#घोषणा OCFB_CTRL_CD16	0x00000200 /* Color Depth 16 */
#घोषणा OCFB_CTRL_CD24	0x00000400 /* Color Depth 24 */
#घोषणा OCFB_CTRL_CD32	0x00000600 /* Color Depth 32 */
#घोषणा OCFB_CTRL_VBL1	0x00000000 /* Burst Length 1 */
#घोषणा OCFB_CTRL_VBL2	0x00000080 /* Burst Length 2 */
#घोषणा OCFB_CTRL_VBL4	0x00000100 /* Burst Length 4 */
#घोषणा OCFB_CTRL_VBL8	0x00000180 /* Burst Length 8 */

#घोषणा PALETTE_SIZE	256

#घोषणा OCFB_NAME	"OC VGA/LCD"

अटल अक्षर *mode_option;

अटल स्थिर काष्ठा fb_videomode शेष_mode = अणु
	/* 640x480 @ 60 Hz, 31.5 kHz hsync */
	शून्य, 60, 640, 480, 39721, 40, 24, 32, 11, 96, 2,
	0, FB_VMODE_NONINTERLACED
पूर्ण;

काष्ठा ocfb_dev अणु
	काष्ठा fb_info info;
	व्योम __iomem *regs;
	/* flag indicating whether the regs are little endian accessed */
	पूर्णांक little_endian;
	/* Physical and भव addresses of framebuffer */
	dma_addr_t fb_phys;
	व्योम __iomem *fb_virt;
	u32 pseuकरो_palette[PALETTE_SIZE];
पूर्ण;

#अगर_अघोषित MODULE
अटल पूर्णांक __init ocfb_setup(अक्षर *options)
अणु
	अक्षर *curr_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((curr_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*curr_opt)
			जारी;
		mode_option = curr_opt;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत u32 ocfb_पढ़ोreg(काष्ठा ocfb_dev *fbdev, loff_t offset)
अणु
	अगर (fbdev->little_endian)
		वापस ioपढ़ो32(fbdev->regs + offset);
	अन्यथा
		वापस ioपढ़ो32be(fbdev->regs + offset);
पूर्ण

अटल व्योम ocfb_ग_लिखोreg(काष्ठा ocfb_dev *fbdev, loff_t offset, u32 data)
अणु
	अगर (fbdev->little_endian)
		ioग_लिखो32(data, fbdev->regs + offset);
	अन्यथा
		ioग_लिखो32be(data, fbdev->regs + offset);
पूर्ण

अटल पूर्णांक ocfb_setupfb(काष्ठा ocfb_dev *fbdev)
अणु
	अचिन्हित दीर्घ bpp_config;
	काष्ठा fb_var_screeninfo *var = &fbdev->info.var;
	काष्ठा device *dev = fbdev->info.device;
	u32 hlen;
	u32 vlen;

	/* Disable display */
	ocfb_ग_लिखोreg(fbdev, OCFB_CTRL, 0);

	/* Register framebuffer address */
	fbdev->little_endian = 0;
	ocfb_ग_लिखोreg(fbdev, OCFB_VBARA, fbdev->fb_phys);

	/* Detect endianess */
	अगर (ocfb_पढ़ोreg(fbdev, OCFB_VBARA) != fbdev->fb_phys) अणु
		fbdev->little_endian = 1;
		ocfb_ग_लिखोreg(fbdev, OCFB_VBARA, fbdev->fb_phys);
	पूर्ण

	/* Horizontal timings */
	ocfb_ग_लिखोreg(fbdev, OCFB_HTIM, (var->hsync_len - 1) << 24 |
		      (var->left_margin - 1) << 16 | (var->xres - 1));

	/* Vertical timings */
	ocfb_ग_लिखोreg(fbdev, OCFB_VTIM, (var->vsync_len - 1) << 24 |
		      (var->upper_margin - 1) << 16 | (var->yres - 1));

	/* Total length of frame */
	hlen = var->left_margin + var->right_margin + var->hsync_len +
		var->xres;

	vlen = var->upper_margin + var->lower_margin + var->vsync_len +
		var->yres;

	ocfb_ग_लिखोreg(fbdev, OCFB_HVLEN, (hlen - 1) << 16 | (vlen - 1));

	bpp_config = OCFB_CTRL_CD8;
	चयन (var->bits_per_pixel) अणु
	हाल 8:
		अगर (!var->grayscale)
			bpp_config |= OCFB_CTRL_PC;  /* enable palette */
		अवरोध;

	हाल 16:
		bpp_config |= OCFB_CTRL_CD16;
		अवरोध;

	हाल 24:
		bpp_config |= OCFB_CTRL_CD24;
		अवरोध;

	हाल 32:
		bpp_config |= OCFB_CTRL_CD32;
		अवरोध;

	शेष:
		dev_err(dev, "no bpp specified\n");
		अवरोध;
	पूर्ण

	/* maximum (8) VBL (video memory burst length) */
	bpp_config |= OCFB_CTRL_VBL8;

	/* Enable output */
	ocfb_ग_लिखोreg(fbdev, OCFB_CTRL, (OCFB_CTRL_VEN | bpp_config));

	वापस 0;
पूर्ण

अटल पूर्णांक ocfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			  अचिन्हित blue, अचिन्हित transp,
			  काष्ठा fb_info *info)
अणु
	काष्ठा ocfb_dev *fbdev = (काष्ठा ocfb_dev *)info->par;
	u32 color;

	अगर (regno >= info->cmap.len) अणु
		dev_err(info->device, "regno >= cmap.len\n");
		वापस 1;
	पूर्ण

	अगर (info->var.grayscale) अणु
		/* grayscale = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	पूर्ण

	red >>= (16 - info->var.red.length);
	green >>= (16 - info->var.green.length);
	blue >>= (16 - info->var.blue.length);
	transp >>= (16 - info->var.transp.length);

	अगर (info->var.bits_per_pixel == 8 && !info->var.grayscale) अणु
		regno <<= 2;
		color = (red << 16) | (green << 8) | blue;
		ocfb_ग_लिखोreg(fbdev, OCFB_PALETTE + regno, color);
	पूर्ण अन्यथा अणु
		((u32 *)(info->pseuकरो_palette))[regno] =
			(red << info->var.red.offset) |
			(green << info->var.green.offset) |
			(blue << info->var.blue.offset) |
			(transp << info->var.transp.offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ocfb_init_fix(काष्ठा ocfb_dev *fbdev)
अणु
	काष्ठा fb_var_screeninfo *var = &fbdev->info.var;
	काष्ठा fb_fix_screeninfo *fix = &fbdev->info.fix;

	म_नकल(fix->id, OCFB_NAME);

	fix->line_length = var->xres * var->bits_per_pixel/8;
	fix->smem_len = fix->line_length * var->yres;
	fix->type = FB_TYPE_PACKED_PIXELS;

	अगर (var->bits_per_pixel == 8 && !var->grayscale)
		fix->visual = FB_VISUAL_PSEUDOCOLOR;
	अन्यथा
		fix->visual = FB_VISUAL_TRUECOLOR;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfb_init_var(काष्ठा ocfb_dev *fbdev)
अणु
	काष्ठा fb_var_screeninfo *var = &fbdev->info.var;

	var->accel_flags = FB_ACCEL_NONE;
	var->activate = FB_ACTIVATE_NOW;
	var->xres_भव = var->xres;
	var->yres_भव = var->yres;

	चयन (var->bits_per_pixel) अणु
	हाल 8:
		var->transp.offset = 0;
		var->transp.length = 0;
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		अवरोध;

	हाल 16:
		var->transp.offset = 0;
		var->transp.length = 0;
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length  = 5;
		अवरोध;

	हाल 24:
		var->transp.offset = 0;
		var->transp.length = 0;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		अवरोध;

	हाल 32:
		var->transp.offset = 24;
		var->transp.length = 8;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops ocfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_setcolreg	= ocfb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल पूर्णांक ocfb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfb_dev *fbdev;
	पूर्णांक fbsize;

	fbdev = devm_kzalloc(&pdev->dev, माप(*fbdev), GFP_KERNEL);
	अगर (!fbdev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, fbdev);

	fbdev->info.fbops = &ocfb_ops;
	fbdev->info.device = &pdev->dev;
	fbdev->info.par = fbdev;

	/* Video mode setup */
	अगर (!fb_find_mode(&fbdev->info.var, &fbdev->info, mode_option,
			  शून्य, 0, &शेष_mode, 16)) अणु
		dev_err(&pdev->dev, "No valid video modes found\n");
		वापस -EINVAL;
	पूर्ण
	ocfb_init_var(fbdev);
	ocfb_init_fix(fbdev);

	fbdev->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(fbdev->regs))
		वापस PTR_ERR(fbdev->regs);

	/* Allocate framebuffer memory */
	fbsize = fbdev->info.fix.smem_len;
	fbdev->fb_virt = dma_alloc_coherent(&pdev->dev, PAGE_ALIGN(fbsize),
					    &fbdev->fb_phys, GFP_KERNEL);
	अगर (!fbdev->fb_virt) अणु
		dev_err(&pdev->dev,
			"Frame buffer memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण
	fbdev->info.fix.smem_start = fbdev->fb_phys;
	fbdev->info.screen_base = fbdev->fb_virt;
	fbdev->info.pseuकरो_palette = fbdev->pseuकरो_palette;

	/* Clear framebuffer */
	स_रखो_io(fbdev->fb_virt, 0, fbsize);

	/* Setup and enable the framebuffer */
	ocfb_setupfb(fbdev);

	अगर (fbdev->little_endian)
		fbdev->info.flags |= FBINFO_FOREIGN_ENDIAN;

	/* Allocate color map */
	ret = fb_alloc_cmap(&fbdev->info.cmap, PALETTE_SIZE, 0);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Color map allocation failed\n");
		जाओ err_dma_मुक्त;
	पूर्ण

	/* Register framebuffer */
	ret = रेजिस्टर_framebuffer(&fbdev->info);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Framebuffer registration failed\n");
		जाओ err_dealloc_cmap;
	पूर्ण

	वापस 0;

err_dealloc_cmap:
	fb_dealloc_cmap(&fbdev->info.cmap);

err_dma_मुक्त:
	dma_मुक्त_coherent(&pdev->dev, PAGE_ALIGN(fbsize), fbdev->fb_virt,
			  fbdev->fb_phys);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ocfb_dev *fbdev = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_framebuffer(&fbdev->info);
	fb_dealloc_cmap(&fbdev->info.cmap);
	dma_मुक्त_coherent(&pdev->dev, PAGE_ALIGN(fbdev->info.fix.smem_len),
			  fbdev->fb_virt, fbdev->fb_phys);

	/* Disable display */
	ocfb_ग_लिखोreg(fbdev, OCFB_CTRL, 0);

	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा of_device_id ocfb_match[] = अणु
	अणु .compatible = "opencores,ocfb", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ocfb_match);

अटल काष्ठा platक्रमm_driver ocfb_driver = अणु
	.probe  = ocfb_probe,
	.हटाओ	= ocfb_हटाओ,
	.driver = अणु
		.name = "ocfb_fb",
		.of_match_table = ocfb_match,
	पूर्ण
पूर्ण;

/*
 * Init and निकास routines
 */
अटल पूर्णांक __init ocfb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("ocfb", &option))
		वापस -ENODEV;
	ocfb_setup(option);
#पूर्ण_अगर
	वापस platक्रमm_driver_रेजिस्टर(&ocfb_driver);
पूर्ण

अटल व्योम __निकास ocfb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ocfb_driver);
पूर्ण

module_init(ocfb_init);
module_निकास(ocfb_निकास);

MODULE_AUTHOR("Stefan Kristiansson <stefan.kristiansson@saunalahti.fi>");
MODULE_DESCRIPTION("OpenCores VGA/LCD 2.0 frame buffer driver");
MODULE_LICENSE("GPL v2");
module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Video mode ('<xres>x<yres>[-<bpp>][@refresh]')");
