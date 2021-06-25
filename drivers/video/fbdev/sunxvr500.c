<शैली गुरु>
/* sunxvr500.c: Sun 3DLABS XVR-500 Expert3D fb driver क्रम sparc64 प्रणालीs
 *
 * License: GPL
 *
 * Copyright (C) 2007 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/fb.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/पन.स>

/* XXX This device has a 'dev-comm' property which apparently is
 * XXX a poपूर्णांकer पूर्णांकo the खोलोfirmware's address space which is
 * XXX a shared area the kernel driver can use to keep OBP
 * XXX inक्रमmed about the current resolution setting.  The idea
 * XXX is that the kernel can change resolutions, and as दीर्घ
 * XXX as the values in the 'dev-comm' area are accurate then
 * XXX OBP can still render text properly to the console.
 * XXX
 * XXX I'm still working out the layout of this and whether there
 * XXX are any signatures we need to look क्रम etc.
 */
काष्ठा e3d_info अणु
	काष्ठा fb_info		*info;
	काष्ठा pci_dev		*pdev;

	spinlock_t		lock;

	अक्षर __iomem		*fb_base;
	अचिन्हित दीर्घ		fb_base_phys;

	अचिन्हित दीर्घ		fb8_buf_dअगरf;
	अचिन्हित दीर्घ		regs_base_phys;

	व्योम __iomem		*ramdac;

	काष्ठा device_node	*of_node;

	अचिन्हित पूर्णांक		width;
	अचिन्हित पूर्णांक		height;
	अचिन्हित पूर्णांक		depth;
	अचिन्हित पूर्णांक		fb_size;

	u32			fb_base_reg;
	u32			fb8_0_off;
	u32			fb8_1_off;

	u32			pseuकरो_palette[16];
पूर्ण;

अटल पूर्णांक e3d_get_props(काष्ठा e3d_info *ep)
अणु
	ep->width = of_getपूर्णांकprop_शेष(ep->of_node, "width", 0);
	ep->height = of_getपूर्णांकprop_शेष(ep->of_node, "height", 0);
	ep->depth = of_getपूर्णांकprop_शेष(ep->of_node, "depth", 8);

	अगर (!ep->width || !ep->height) अणु
		prपूर्णांकk(KERN_ERR "e3d: Critical properties missing for %s\n",
		       pci_name(ep->pdev));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* My XVR-500 comes up, at 1280x768 and a FB base रेजिस्टर value of
 * 0x04000000, the following video layout रेजिस्टर values:
 *
 * RAMDAC_VID_WH	0x03ff04ff
 * RAMDAC_VID_CFG	0x1a0b0088
 * RAMDAC_VID_32FB_0	0x04000000
 * RAMDAC_VID_32FB_1	0x04800000
 * RAMDAC_VID_8FB_0	0x05000000
 * RAMDAC_VID_8FB_1	0x05200000
 * RAMDAC_VID_XXXFB	0x05400000
 * RAMDAC_VID_YYYFB	0x05c00000
 * RAMDAC_VID_ZZZFB	0x05e00000
 */
/* Video layout रेजिस्टरs */
#घोषणा RAMDAC_VID_WH		0x00000070UL /* (height-1)<<16 | (width-1) */
#घोषणा RAMDAC_VID_CFG		0x00000074UL /* 0x1a000088|(linesz_log2<<16) */
#घोषणा RAMDAC_VID_32FB_0	0x00000078UL /* PCI base 32bpp FB buffer 0 */
#घोषणा RAMDAC_VID_32FB_1	0x0000007cUL /* PCI base 32bpp FB buffer 1 */
#घोषणा RAMDAC_VID_8FB_0	0x00000080UL /* PCI base 8bpp FB buffer 0 */
#घोषणा RAMDAC_VID_8FB_1	0x00000084UL /* PCI base 8bpp FB buffer 1 */
#घोषणा RAMDAC_VID_XXXFB	0x00000088UL /* PCI base of XXX FB */
#घोषणा RAMDAC_VID_YYYFB	0x0000008cUL /* PCI base of YYY FB */
#घोषणा RAMDAC_VID_ZZZFB	0x00000090UL /* PCI base of ZZZ FB */

/* CLUT रेजिस्टरs */
#घोषणा RAMDAC_INDEX		0x000000bcUL
#घोषणा RAMDAC_DATA		0x000000c0UL

अटल व्योम e3d_clut_ग_लिखो(काष्ठा e3d_info *ep, पूर्णांक index, u32 val)
अणु
	व्योम __iomem *ramdac = ep->ramdac;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ep->lock, flags);

	ग_लिखोl(index, ramdac + RAMDAC_INDEX);
	ग_लिखोl(val, ramdac + RAMDAC_DATA);

	spin_unlock_irqrestore(&ep->lock, flags);
पूर्ण

अटल पूर्णांक e3d_setcolreg(अचिन्हित regno,
			 अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			 अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा e3d_info *ep = info->par;
	u32 red_8, green_8, blue_8;
	u32 red_10, green_10, blue_10;
	u32 value;

	अगर (regno >= 256)
		वापस 1;

	red_8 = red >> 8;
	green_8 = green >> 8;
	blue_8 = blue >> 8;

	value = (blue_8 << 24) | (green_8 << 16) | (red_8 << 8);

	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR && regno < 16)
		((u32 *)info->pseuकरो_palette)[regno] = value;


	red_10 = red >> 6;
	green_10 = green >> 6;
	blue_10 = blue >> 6;

	value = (blue_10 << 20) | (green_10 << 10) | (red_10 << 0);
	e3d_clut_ग_लिखो(ep, regno, value);

	वापस 0;
पूर्ण

/* XXX This is a bit of a hack.  I can't figure out exactly how the
 * XXX two 8bpp areas of the framebuffer work.  I imagine there is
 * XXX a WID attribute somewhere अन्यथा in the framebuffer which tells
 * XXX the ramdac which of the two 8bpp framebuffer regions to take
 * XXX the pixel from.  So, क्रम now, render पूर्णांकo both regions to make
 * XXX sure the pixel shows up.
 */
अटल व्योम e3d_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा e3d_info *ep = info->par;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ep->lock, flags);
	cfb_imageblit(info, image);
	info->screen_base += ep->fb8_buf_dअगरf;
	cfb_imageblit(info, image);
	info->screen_base -= ep->fb8_buf_dअगरf;
	spin_unlock_irqrestore(&ep->lock, flags);
पूर्ण

अटल व्योम e3d_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा e3d_info *ep = info->par;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ep->lock, flags);
	cfb_fillrect(info, rect);
	info->screen_base += ep->fb8_buf_dअगरf;
	cfb_fillrect(info, rect);
	info->screen_base -= ep->fb8_buf_dअगरf;
	spin_unlock_irqrestore(&ep->lock, flags);
पूर्ण

अटल व्योम e3d_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा e3d_info *ep = info->par;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ep->lock, flags);
	cfb_copyarea(info, area);
	info->screen_base += ep->fb8_buf_dअगरf;
	cfb_copyarea(info, area);
	info->screen_base -= ep->fb8_buf_dअगरf;
	spin_unlock_irqrestore(&ep->lock, flags);
पूर्ण

अटल स्थिर काष्ठा fb_ops e3d_ops = अणु
	.owner			= THIS_MODULE,
	.fb_setcolreg		= e3d_setcolreg,
	.fb_fillrect		= e3d_fillrect,
	.fb_copyarea		= e3d_copyarea,
	.fb_imageblit		= e3d_imageblit,
पूर्ण;

अटल पूर्णांक e3d_set_fbinfo(काष्ठा e3d_info *ep)
अणु
	काष्ठा fb_info *info = ep->info;
	काष्ठा fb_var_screeninfo *var = &info->var;

	info->flags = FBINFO_DEFAULT;
	info->fbops = &e3d_ops;
	info->screen_base = ep->fb_base;
	info->screen_size = ep->fb_size;

	info->pseuकरो_palette = ep->pseuकरो_palette;

	/* Fill fix common fields */
	strlcpy(info->fix.id, "e3d", माप(info->fix.id));
        info->fix.smem_start = ep->fb_base_phys;
        info->fix.smem_len = ep->fb_size;
        info->fix.type = FB_TYPE_PACKED_PIXELS;
	अगर (ep->depth == 32 || ep->depth == 24)
		info->fix.visual = FB_VISUAL_TRUECOLOR;
	अन्यथा
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	var->xres = ep->width;
	var->yres = ep->height;
	var->xres_भव = var->xres;
	var->yres_भव = var->yres;
	var->bits_per_pixel = ep->depth;

	var->red.offset = 8;
	var->red.length = 8;
	var->green.offset = 16;
	var->green.length = 8;
	var->blue.offset = 24;
	var->blue.length = 8;
	var->transp.offset = 0;
	var->transp.length = 0;

	अगर (fb_alloc_cmap(&info->cmap, 256, 0)) अणु
		prपूर्णांकk(KERN_ERR "e3d: Cannot allocate color map.\n");
		वापस -ENOMEM;
	पूर्ण

        वापस 0;
पूर्ण

अटल पूर्णांक e3d_pci_रेजिस्टर(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device_node *of_node;
	स्थिर अक्षर *device_type;
	काष्ठा fb_info *info;
	काष्ठा e3d_info *ep;
	अचिन्हित पूर्णांक line_length;
	पूर्णांक err;

	of_node = pci_device_to_OF_node(pdev);
	अगर (!of_node) अणु
		prपूर्णांकk(KERN_ERR "e3d: Cannot find OF node of %s\n",
		       pci_name(pdev));
		वापस -ENODEV;
	पूर्ण

	device_type = of_get_property(of_node, "device_type", शून्य);
	अगर (!device_type) अणु
		prपूर्णांकk(KERN_INFO "e3d: Ignoring secondary output device "
		       "at %s\n", pci_name(pdev));
		वापस -ENODEV;
	पूर्ण

	err = pci_enable_device(pdev);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "e3d: Cannot enable PCI device %s\n",
		       pci_name(pdev));
		जाओ err_out;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा e3d_info), &pdev->dev);
	अगर (!info) अणु
		err = -ENOMEM;
		जाओ err_disable;
	पूर्ण

	ep = info->par;
	ep->info = info;
	ep->pdev = pdev;
	spin_lock_init(&ep->lock);
	ep->of_node = of_node;

	/* Read the PCI base रेजिस्टर of the frame buffer, which we
	 * need in order to पूर्णांकerpret the RAMDAC_VID_*FB* values in
	 * the ramdac correctly.
	 */
	pci_पढ़ो_config_dword(pdev, PCI_BASE_ADDRESS_0,
			      &ep->fb_base_reg);
	ep->fb_base_reg &= PCI_BASE_ADDRESS_MEM_MASK;

	ep->regs_base_phys = pci_resource_start (pdev, 1);
	err = pci_request_region(pdev, 1, "e3d regs");
	अगर (err < 0) अणु
		prपूर्णांकk("e3d: Cannot request region 1 for %s\n",
		       pci_name(pdev));
		जाओ err_release_fb;
	पूर्ण
	ep->ramdac = ioremap(ep->regs_base_phys + 0x8000, 0x1000);
	अगर (!ep->ramdac) अणु
		err = -ENOMEM;
		जाओ err_release_pci1;
	पूर्ण

	ep->fb8_0_off = पढ़ोl(ep->ramdac + RAMDAC_VID_8FB_0);
	ep->fb8_0_off -= ep->fb_base_reg;

	ep->fb8_1_off = पढ़ोl(ep->ramdac + RAMDAC_VID_8FB_1);
	ep->fb8_1_off -= ep->fb_base_reg;

	ep->fb8_buf_dअगरf = ep->fb8_1_off - ep->fb8_0_off;

	ep->fb_base_phys = pci_resource_start (pdev, 0);
	ep->fb_base_phys += ep->fb8_0_off;

	err = pci_request_region(pdev, 0, "e3d framebuffer");
	अगर (err < 0) अणु
		prपूर्णांकk("e3d: Cannot request region 0 for %s\n",
		       pci_name(pdev));
		जाओ err_unmap_ramdac;
	पूर्ण

	err = e3d_get_props(ep);
	अगर (err)
		जाओ err_release_pci0;

	line_length = (पढ़ोl(ep->ramdac + RAMDAC_VID_CFG) >> 16) & 0xff;
	line_length = 1 << line_length;

	चयन (ep->depth) अणु
	हाल 8:
		info->fix.line_length = line_length;
		अवरोध;
	हाल 16:
		info->fix.line_length = line_length * 2;
		अवरोध;
	हाल 24:
		info->fix.line_length = line_length * 3;
		अवरोध;
	हाल 32:
		info->fix.line_length = line_length * 4;
		अवरोध;
	पूर्ण
	ep->fb_size = info->fix.line_length * ep->height;

	ep->fb_base = ioremap(ep->fb_base_phys, ep->fb_size);
	अगर (!ep->fb_base) अणु
		err = -ENOMEM;
		जाओ err_release_pci0;
	पूर्ण

	err = e3d_set_fbinfo(ep);
	अगर (err)
		जाओ err_unmap_fb;

	pci_set_drvdata(pdev, info);

	prपूर्णांकk("e3d: Found device at %s\n", pci_name(pdev));

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "e3d: Could not register framebuffer %s\n",
		       pci_name(pdev));
		जाओ err_मुक्त_cmap;
	पूर्ण

	वापस 0;

err_मुक्त_cmap:
	fb_dealloc_cmap(&info->cmap);

err_unmap_fb:
	iounmap(ep->fb_base);

err_release_pci0:
	pci_release_region(pdev, 0);

err_unmap_ramdac:
	iounmap(ep->ramdac);

err_release_pci1:
	pci_release_region(pdev, 1);

err_release_fb:
        framebuffer_release(info);

err_disable:
	pci_disable_device(pdev);

err_out:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा pci_device_id e3d_pci_table[] = अणु
	अणु	PCI_DEVICE(PCI_VENDOR_ID_3DLABS, 0x7a0),	पूर्ण,
	अणु	PCI_DEVICE(0x1091, 0x7a0),			पूर्ण,
	अणु	PCI_DEVICE(PCI_VENDOR_ID_3DLABS, 0x7a2),	पूर्ण,
	अणु	.venकरोr = PCI_VENDOR_ID_3DLABS,
		.device = PCI_ANY_ID,
		.subvenकरोr = PCI_VENDOR_ID_3DLABS,
		.subdevice = 0x0108,
	पूर्ण,
	अणु	.venकरोr = PCI_VENDOR_ID_3DLABS,
		.device = PCI_ANY_ID,
		.subvenकरोr = PCI_VENDOR_ID_3DLABS,
		.subdevice = 0x0140,
	पूर्ण,
	अणु	.venकरोr = PCI_VENDOR_ID_3DLABS,
		.device = PCI_ANY_ID,
		.subvenकरोr = PCI_VENDOR_ID_3DLABS,
		.subdevice = 0x1024,
	पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver e3d_driver = अणु
	.driver = अणु
		.suppress_bind_attrs = true,
	पूर्ण,
	.name		= "e3d",
	.id_table	= e3d_pci_table,
	.probe		= e3d_pci_रेजिस्टर,
पूर्ण;

अटल पूर्णांक __init e3d_init(व्योम)
अणु
	अगर (fb_get_options("e3d", शून्य))
		वापस -ENODEV;

	वापस pci_रेजिस्टर_driver(&e3d_driver);
पूर्ण
device_initcall(e3d_init);
