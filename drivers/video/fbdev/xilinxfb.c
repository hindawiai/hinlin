<शैली गुरु>
/*
 * Xilinx TFT frame buffer driver
 *
 * Author: MontaVista Software, Inc.
 *         source@mvista.com
 *
 * 2002-2007 (c) MontaVista Software, Inc.
 * 2007 (c) Secret Lab Technologies, Ltd.
 * 2009 (c) Xilinx Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

/*
 * This driver was based on au1100fb.c by MontaVista rewritten क्रम 2.6
 * by Embedded Alley Solutions <source@embeddedalley.com>, which in turn
 * was based on skeletonfb.c, Skeleton क्रम a frame buffer device by
 * Geert Uytterhoeven.
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#अगर_घोषित CONFIG_PPC_DCR
#समावेश <यंत्र/dcr.h>
#पूर्ण_अगर

#घोषणा DRIVER_NAME		"xilinxfb"

/*
 * Xilinx calls it "TFT LCD Controller" though it can also be used क्रम
 * the VGA port on the Xilinx ML40x board. This is a hardware display
 * controller क्रम a 640x480 resolution TFT or VGA screen.
 *
 * The पूर्णांकerface to the framebuffer is nice and simple.  There are two
 * control रेजिस्टरs.  The first tells the LCD पूर्णांकerface where in memory
 * the frame buffer is (only the 11 most signअगरicant bits are used, so
 * करोn't start thinking about scrolling).  The second allows the LCD to
 * be turned on or off as well as rotated 180 degrees.
 *
 * In हाल of direct BUS access the second control रेजिस्टर will be at
 * an offset of 4 as compared to the DCR access where the offset is 1
 * i.e. REG_CTRL. So this is taken care in the function
 * xilinx_fb_out32 where it left shअगरts the offset 2 बार in हाल of
 * direct BUS access.
 */
#घोषणा NUM_REGS	2
#घोषणा REG_FB_ADDR	0
#घोषणा REG_CTRL	1
#घोषणा REG_CTRL_ENABLE	 0x0001
#घोषणा REG_CTRL_ROTATE	 0x0002

/*
 * The hardware only handles a single mode: 640x480 24 bit true
 * color. Each pixel माला_लो a word (32 bits) of memory.  Within each word,
 * the 8 most signअगरicant bits are ignored, the next 8 bits are the red
 * level, the next 8 bits are the green level and the 8 least
 * signअगरicant bits are the blue level.  Each row of the LCD uses 1024
 * words, but only the first 640 pixels are displayed with the other 384
 * words being ignored.  There are 480 rows.
 */
#घोषणा BYTES_PER_PIXEL	4
#घोषणा BITS_PER_PIXEL	(BYTES_PER_PIXEL * 8)

#घोषणा RED_SHIFT	16
#घोषणा GREEN_SHIFT	8
#घोषणा BLUE_SHIFT	0

#घोषणा PALETTE_ENTRIES_NO	16	/* passed to fb_alloc_cmap() */

/* ML300/403 reference design framebuffer driver platक्रमm data काष्ठा */
काष्ठा xilinxfb_platक्रमm_data अणु
	u32 rotate_screen;      /* Flag to rotate display 180 degrees */
	u32 screen_height_mm;   /* Physical dimensions of screen in mm */
	u32 screen_width_mm;
	u32 xres, yres;         /* resolution of screen in pixels */
	u32 xvirt, yvirt;       /* resolution of memory buffer */

	/* Physical address of framebuffer memory; If non-zero, driver
	 * will use provided memory address instead of allocating one from
	 * the consistent pool.
	 */
	u32 fb_phys;
पूर्ण;

/*
 * Default xilinxfb configuration
 */
अटल स्थिर काष्ठा xilinxfb_platक्रमm_data xilinx_fb_शेष_pdata = अणु
	.xres = 640,
	.yres = 480,
	.xvirt = 1024,
	.yvirt = 480,
पूर्ण;

/*
 * Here are the शेष fb_fix_screeninfo and fb_var_screeninfo काष्ठाures
 */
अटल स्थिर काष्ठा fb_fix_screeninfo xilinx_fb_fix = अणु
	.id =		"Xilinx",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_TRUECOLOR,
	.accel =	FB_ACCEL_NONE
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo xilinx_fb_var = अणु
	.bits_per_pixel =	BITS_PER_PIXEL,

	.red =		अणु RED_SHIFT, 8, 0 पूर्ण,
	.green =	अणु GREEN_SHIFT, 8, 0 पूर्ण,
	.blue =		अणु BLUE_SHIFT, 8, 0 पूर्ण,
	.transp =	अणु 0, 0, 0 पूर्ण,

	.activate =	FB_ACTIVATE_NOW
पूर्ण;

#घोषणा BUS_ACCESS_FLAG		0x1 /* 1 = BUS, 0 = DCR */
#घोषणा LITTLE_ENDIAN_ACCESS	0x2 /* LITTLE ENDIAN IO functions */

काष्ठा xilinxfb_drvdata अणु
	काष्ठा fb_info	info;		/* FB driver info record */

	phys_addr_t	regs_phys;	/* phys. address of the control
					 * रेजिस्टरs
					 */
	व्योम __iomem	*regs;		/* virt. address of the control
					 * रेजिस्टरs
					 */
#अगर_घोषित CONFIG_PPC_DCR
	dcr_host_t      dcr_host;
	अचिन्हित पूर्णांक    dcr_len;
#पूर्ण_अगर
	व्योम		*fb_virt;	/* virt. address of the frame buffer */
	dma_addr_t	fb_phys;	/* phys. address of the frame buffer */
	पूर्णांक		fb_alloced;	/* Flag, was the fb memory alloced? */

	u8		flags;		/* features of the driver */

	u32		reg_ctrl_शेष;

	u32		pseuकरो_palette[PALETTE_ENTRIES_NO];
					/* Fake palette of 16 colors */
पूर्ण;

#घोषणा to_xilinxfb_drvdata(_info) \
	container_of(_info, काष्ठा xilinxfb_drvdata, info)

/*
 * The XPS TFT Controller can be accessed through BUS or DCR पूर्णांकerface.
 * To perक्रमm the पढ़ो/ग_लिखो on the रेजिस्टरs we need to check on
 * which bus its connected and call the appropriate ग_लिखो API.
 */
अटल व्योम xilinx_fb_out32(काष्ठा xilinxfb_drvdata *drvdata, u32 offset,
			    u32 val)
अणु
	अगर (drvdata->flags & BUS_ACCESS_FLAG) अणु
		अगर (drvdata->flags & LITTLE_ENDIAN_ACCESS)
			ioग_लिखो32(val, drvdata->regs + (offset << 2));
		अन्यथा
			ioग_लिखो32be(val, drvdata->regs + (offset << 2));
	पूर्ण
#अगर_घोषित CONFIG_PPC_DCR
	अन्यथा
		dcr_ग_लिखो(drvdata->dcr_host, offset, val);
#पूर्ण_अगर
पूर्ण

अटल u32 xilinx_fb_in32(काष्ठा xilinxfb_drvdata *drvdata, u32 offset)
अणु
	अगर (drvdata->flags & BUS_ACCESS_FLAG) अणु
		अगर (drvdata->flags & LITTLE_ENDIAN_ACCESS)
			वापस ioपढ़ो32(drvdata->regs + (offset << 2));
		अन्यथा
			वापस ioपढ़ो32be(drvdata->regs + (offset << 2));
	पूर्ण
#अगर_घोषित CONFIG_PPC_DCR
	अन्यथा
		वापस dcr_पढ़ो(drvdata->dcr_host, offset);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक
xilinx_fb_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red, अचिन्हित पूर्णांक green,
		    अचिन्हित पूर्णांक blue, अचिन्हित पूर्णांक transp, काष्ठा fb_info *fbi)
अणु
	u32 *palette = fbi->pseuकरो_palette;

	अगर (regno >= PALETTE_ENTRIES_NO)
		वापस -EINVAL;

	अगर (fbi->var.grayscale) अणु
		/* Convert color to grayscale.
		 * grayscale = 0.30*R + 0.59*G + 0.11*B
		 */
		blue = (red * 77 + green * 151 + blue * 28 + 127) >> 8;
		green = blue;
		red = green;
	पूर्ण

	/* fbi->fix.visual is always FB_VISUAL_TRUECOLOR */

	/* We only handle 8 bits of each color. */
	red >>= 8;
	green >>= 8;
	blue >>= 8;
	palette[regno] = (red << RED_SHIFT) | (green << GREEN_SHIFT) |
			 (blue << BLUE_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक
xilinx_fb_blank(पूर्णांक blank_mode, काष्ठा fb_info *fbi)
अणु
	काष्ठा xilinxfb_drvdata *drvdata = to_xilinxfb_drvdata(fbi);

	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		/* turn on panel */
		xilinx_fb_out32(drvdata, REG_CTRL, drvdata->reg_ctrl_शेष);
		अवरोध;

	हाल FB_BLANK_NORMAL:
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_POWERDOWN:
		/* turn off panel */
		xilinx_fb_out32(drvdata, REG_CTRL, 0);
	शेष:
		अवरोध;
	पूर्ण
	वापस 0; /* success */
पूर्ण

अटल स्थिर काष्ठा fb_ops xilinxfb_ops = अणु
	.owner			= THIS_MODULE,
	.fb_setcolreg		= xilinx_fb_setcolreg,
	.fb_blank		= xilinx_fb_blank,
	.fb_fillrect		= cfb_fillrect,
	.fb_copyarea		= cfb_copyarea,
	.fb_imageblit		= cfb_imageblit,
पूर्ण;

/* ---------------------------------------------------------------------
 * Bus independent setup/tearकरोwn
 */

अटल पूर्णांक xilinxfb_assign(काष्ठा platक्रमm_device *pdev,
			   काष्ठा xilinxfb_drvdata *drvdata,
			   काष्ठा xilinxfb_platक्रमm_data *pdata)
अणु
	पूर्णांक rc;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक fbsize = pdata->xvirt * pdata->yvirt * BYTES_PER_PIXEL;

	अगर (drvdata->flags & BUS_ACCESS_FLAG) अणु
		काष्ठा resource *res;

		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		drvdata->regs = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(drvdata->regs))
			वापस PTR_ERR(drvdata->regs);

		drvdata->regs_phys = res->start;
	पूर्ण

	/* Allocate the framebuffer memory */
	अगर (pdata->fb_phys) अणु
		drvdata->fb_phys = pdata->fb_phys;
		drvdata->fb_virt = ioremap(pdata->fb_phys, fbsize);
	पूर्ण अन्यथा अणु
		drvdata->fb_alloced = 1;
		drvdata->fb_virt = dma_alloc_coherent(dev, PAGE_ALIGN(fbsize),
						      &drvdata->fb_phys,
						      GFP_KERNEL);
	पूर्ण

	अगर (!drvdata->fb_virt) अणु
		dev_err(dev, "Could not allocate frame buffer memory\n");
		वापस -ENOMEM;
	पूर्ण

	/* Clear (turn to black) the framebuffer */
	स_रखो_io((व्योम __iomem *)drvdata->fb_virt, 0, fbsize);

	/* Tell the hardware where the frame buffer is */
	xilinx_fb_out32(drvdata, REG_FB_ADDR, drvdata->fb_phys);
	rc = xilinx_fb_in32(drvdata, REG_FB_ADDR);
	/* Endianness detection */
	अगर (rc != drvdata->fb_phys) अणु
		drvdata->flags |= LITTLE_ENDIAN_ACCESS;
		xilinx_fb_out32(drvdata, REG_FB_ADDR, drvdata->fb_phys);
	पूर्ण

	/* Turn on the display */
	drvdata->reg_ctrl_शेष = REG_CTRL_ENABLE;
	अगर (pdata->rotate_screen)
		drvdata->reg_ctrl_शेष |= REG_CTRL_ROTATE;
	xilinx_fb_out32(drvdata, REG_CTRL, drvdata->reg_ctrl_शेष);

	/* Fill काष्ठा fb_info */
	drvdata->info.device = dev;
	drvdata->info.screen_base = (व्योम __iomem *)drvdata->fb_virt;
	drvdata->info.fbops = &xilinxfb_ops;
	drvdata->info.fix = xilinx_fb_fix;
	drvdata->info.fix.smem_start = drvdata->fb_phys;
	drvdata->info.fix.smem_len = fbsize;
	drvdata->info.fix.line_length = pdata->xvirt * BYTES_PER_PIXEL;

	drvdata->info.pseuकरो_palette = drvdata->pseuकरो_palette;
	drvdata->info.flags = FBINFO_DEFAULT;
	drvdata->info.var = xilinx_fb_var;
	drvdata->info.var.height = pdata->screen_height_mm;
	drvdata->info.var.width = pdata->screen_width_mm;
	drvdata->info.var.xres = pdata->xres;
	drvdata->info.var.yres = pdata->yres;
	drvdata->info.var.xres_भव = pdata->xvirt;
	drvdata->info.var.yres_भव = pdata->yvirt;

	/* Allocate a colour map */
	rc = fb_alloc_cmap(&drvdata->info.cmap, PALETTE_ENTRIES_NO, 0);
	अगर (rc) अणु
		dev_err(dev, "Fail to allocate colormap (%d entries)\n",
			PALETTE_ENTRIES_NO);
		जाओ err_cmap;
	पूर्ण

	/* Register new frame buffer */
	rc = रेजिस्टर_framebuffer(&drvdata->info);
	अगर (rc) अणु
		dev_err(dev, "Could not register frame buffer\n");
		जाओ err_regfb;
	पूर्ण

	अगर (drvdata->flags & BUS_ACCESS_FLAG) अणु
		/* Put a banner in the log (क्रम DEBUG) */
		dev_dbg(dev, "regs: phys=%pa, virt=%p\n",
			&drvdata->regs_phys, drvdata->regs);
	पूर्ण
	/* Put a banner in the log (क्रम DEBUG) */
	dev_dbg(dev, "fb: phys=%llx, virt=%p, size=%x\n",
		(अचिन्हित दीर्घ दीर्घ)drvdata->fb_phys, drvdata->fb_virt, fbsize);

	वापस 0;	/* success */

err_regfb:
	fb_dealloc_cmap(&drvdata->info.cmap);

err_cmap:
	अगर (drvdata->fb_alloced)
		dma_मुक्त_coherent(dev, PAGE_ALIGN(fbsize), drvdata->fb_virt,
				  drvdata->fb_phys);
	अन्यथा
		iounmap(drvdata->fb_virt);

	/* Turn off the display */
	xilinx_fb_out32(drvdata, REG_CTRL, 0);

	वापस rc;
पूर्ण

अटल पूर्णांक xilinxfb_release(काष्ठा device *dev)
अणु
	काष्ठा xilinxfb_drvdata *drvdata = dev_get_drvdata(dev);

#अगर !defined(CONFIG_FRAMEBUFFER_CONSOLE) && defined(CONFIG_LOGO)
	xilinx_fb_blank(VESA_POWERDOWN, &drvdata->info);
#पूर्ण_अगर

	unरेजिस्टर_framebuffer(&drvdata->info);

	fb_dealloc_cmap(&drvdata->info.cmap);

	अगर (drvdata->fb_alloced)
		dma_मुक्त_coherent(dev, PAGE_ALIGN(drvdata->info.fix.smem_len),
				  drvdata->fb_virt, drvdata->fb_phys);
	अन्यथा
		iounmap(drvdata->fb_virt);

	/* Turn off the display */
	xilinx_fb_out32(drvdata, REG_CTRL, 0);

#अगर_घोषित CONFIG_PPC_DCR
	/* Release the resources, as allocated based on पूर्णांकerface */
	अगर (!(drvdata->flags & BUS_ACCESS_FLAG))
		dcr_unmap(drvdata->dcr_host, drvdata->dcr_len);
#पूर्ण_अगर

	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------
 * OF bus binding
 */

अटल पूर्णांक xilinxfb_of_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर u32 *prop;
	u32 tft_access = 0;
	काष्ठा xilinxfb_platक्रमm_data pdata;
	पूर्णांक size;
	काष्ठा xilinxfb_drvdata *drvdata;

	/* Copy with the शेष pdata (not a ptr reference!) */
	pdata = xilinx_fb_शेष_pdata;

	/* Allocate the driver data region */
	drvdata = devm_kzalloc(&pdev->dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	/*
	 * To check whether the core is connected directly to DCR or BUS
	 * पूर्णांकerface and initialize the tft_access accordingly.
	 */
	of_property_पढ़ो_u32(pdev->dev.of_node, "xlnx,dcr-splb-slave-if",
			     &tft_access);

	/*
	 * Fill the resource काष्ठाure अगर its direct BUS पूर्णांकerface
	 * otherwise fill the dcr_host काष्ठाure.
	 */
	अगर (tft_access)
		drvdata->flags |= BUS_ACCESS_FLAG;
#अगर_घोषित CONFIG_PPC_DCR
	अन्यथा अणु
		पूर्णांक start;

		start = dcr_resource_start(pdev->dev.of_node, 0);
		drvdata->dcr_len = dcr_resource_len(pdev->dev.of_node, 0);
		drvdata->dcr_host = dcr_map(pdev->dev.of_node, start, drvdata->dcr_len);
		अगर (!DCR_MAP_OK(drvdata->dcr_host)) अणु
			dev_err(&pdev->dev, "invalid DCR address\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	prop = of_get_property(pdev->dev.of_node, "phys-size", &size);
	अगर ((prop) && (size >= माप(u32) * 2)) अणु
		pdata.screen_width_mm = prop[0];
		pdata.screen_height_mm = prop[1];
	पूर्ण

	prop = of_get_property(pdev->dev.of_node, "resolution", &size);
	अगर ((prop) && (size >= माप(u32) * 2)) अणु
		pdata.xres = prop[0];
		pdata.yres = prop[1];
	पूर्ण

	prop = of_get_property(pdev->dev.of_node, "virtual-resolution", &size);
	अगर ((prop) && (size >= माप(u32) * 2)) अणु
		pdata.xvirt = prop[0];
		pdata.yvirt = prop[1];
	पूर्ण

	अगर (of_find_property(pdev->dev.of_node, "rotate-display", शून्य))
		pdata.rotate_screen = 1;

	platक्रमm_set_drvdata(pdev, drvdata);
	वापस xilinxfb_assign(pdev, drvdata, &pdata);
पूर्ण

अटल पूर्णांक xilinxfb_of_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	वापस xilinxfb_release(&op->dev);
पूर्ण

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id xilinxfb_of_match[] = अणु
	अणु .compatible = "xlnx,xps-tft-1.00.a", पूर्ण,
	अणु .compatible = "xlnx,xps-tft-2.00.a", पूर्ण,
	अणु .compatible = "xlnx,xps-tft-2.01.a", पूर्ण,
	अणु .compatible = "xlnx,plb-tft-cntlr-ref-1.00.a", पूर्ण,
	अणु .compatible = "xlnx,plb-dvi-cntlr-ref-1.00.c", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xilinxfb_of_match);

अटल काष्ठा platक्रमm_driver xilinxfb_of_driver = अणु
	.probe = xilinxfb_of_probe,
	.हटाओ = xilinxfb_of_हटाओ,
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = xilinxfb_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xilinxfb_of_driver);

MODULE_AUTHOR("MontaVista Software, Inc. <source@mvista.com>");
MODULE_DESCRIPTION("Xilinx TFT frame buffer driver");
MODULE_LICENSE("GPL");
