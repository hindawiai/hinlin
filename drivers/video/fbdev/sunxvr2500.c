<शैली गुरु>
/* sunxvr2500.c: Sun 3DLABS XVR-2500 et al. fb driver क्रम sparc64 प्रणालीs
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

काष्ठा s3d_info अणु
	काष्ठा fb_info		*info;
	काष्ठा pci_dev		*pdev;

	अक्षर __iomem		*fb_base;
	अचिन्हित दीर्घ		fb_base_phys;

	काष्ठा device_node	*of_node;

	अचिन्हित पूर्णांक		width;
	अचिन्हित पूर्णांक		height;
	अचिन्हित पूर्णांक		depth;
	अचिन्हित पूर्णांक		fb_size;

	u32			pseuकरो_palette[16];
पूर्ण;

अटल पूर्णांक s3d_get_props(काष्ठा s3d_info *sp)
अणु
	sp->width = of_getपूर्णांकprop_शेष(sp->of_node, "width", 0);
	sp->height = of_getपूर्णांकprop_शेष(sp->of_node, "height", 0);
	sp->depth = of_getपूर्णांकprop_शेष(sp->of_node, "depth", 8);

	अगर (!sp->width || !sp->height) अणु
		prपूर्णांकk(KERN_ERR "s3d: Critical properties missing for %s\n",
		       pci_name(sp->pdev));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3d_setcolreg(अचिन्हित regno,
			 अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			 अचिन्हित transp, काष्ठा fb_info *info)
अणु
	u32 value;

	अगर (regno < 16) अणु
		red >>= 8;
		green >>= 8;
		blue >>= 8;

		value = (blue << 24) | (green << 16) | (red << 8);
		((u32 *)info->pseuकरो_palette)[regno] = value;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops s3d_ops = अणु
	.owner			= THIS_MODULE,
	.fb_setcolreg		= s3d_setcolreg,
	.fb_fillrect		= cfb_fillrect,
	.fb_copyarea		= cfb_copyarea,
	.fb_imageblit		= cfb_imageblit,
पूर्ण;

अटल पूर्णांक s3d_set_fbinfo(काष्ठा s3d_info *sp)
अणु
	काष्ठा fb_info *info = sp->info;
	काष्ठा fb_var_screeninfo *var = &info->var;

	info->flags = FBINFO_DEFAULT;
	info->fbops = &s3d_ops;
	info->screen_base = sp->fb_base;
	info->screen_size = sp->fb_size;

	info->pseuकरो_palette = sp->pseuकरो_palette;

	/* Fill fix common fields */
	strlcpy(info->fix.id, "s3d", माप(info->fix.id));
        info->fix.smem_start = sp->fb_base_phys;
        info->fix.smem_len = sp->fb_size;
        info->fix.type = FB_TYPE_PACKED_PIXELS;
	अगर (sp->depth == 32 || sp->depth == 24)
		info->fix.visual = FB_VISUAL_TRUECOLOR;
	अन्यथा
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	var->xres = sp->width;
	var->yres = sp->height;
	var->xres_भव = var->xres;
	var->yres_भव = var->yres;
	var->bits_per_pixel = sp->depth;

	var->red.offset = 8;
	var->red.length = 8;
	var->green.offset = 16;
	var->green.length = 8;
	var->blue.offset = 24;
	var->blue.length = 8;
	var->transp.offset = 0;
	var->transp.length = 0;

	अगर (fb_alloc_cmap(&info->cmap, 256, 0)) अणु
		prपूर्णांकk(KERN_ERR "s3d: Cannot allocate color map.\n");
		वापस -ENOMEM;
	पूर्ण

        वापस 0;
पूर्ण

अटल पूर्णांक s3d_pci_रेजिस्टर(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा fb_info *info;
	काष्ठा s3d_info *sp;
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "s3d: Cannot enable PCI device %s\n",
		       pci_name(pdev));
		जाओ err_out;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा s3d_info), &pdev->dev);
	अगर (!info) अणु
		err = -ENOMEM;
		जाओ err_disable;
	पूर्ण

	sp = info->par;
	sp->info = info;
	sp->pdev = pdev;
	sp->of_node = pci_device_to_OF_node(pdev);
	अगर (!sp->of_node) अणु
		prपूर्णांकk(KERN_ERR "s3d: Cannot find OF node of %s\n",
		       pci_name(pdev));
		err = -ENODEV;
		जाओ err_release_fb;
	पूर्ण

	sp->fb_base_phys = pci_resource_start (pdev, 1);

	err = pci_request_region(pdev, 1, "s3d framebuffer");
	अगर (err < 0) अणु
		prपूर्णांकk("s3d: Cannot request region 1 for %s\n",
		       pci_name(pdev));
		जाओ err_release_fb;
	पूर्ण

	err = s3d_get_props(sp);
	अगर (err)
		जाओ err_release_pci;

	/* XXX 'linebytes' is often wrong, it is equal to the width
	 * XXX with depth of 32 on my XVR-2500 which is clearly not
	 * XXX right.  So we करोn't try to use it.
	 */
	चयन (sp->depth) अणु
	हाल 8:
		info->fix.line_length = sp->width;
		अवरोध;
	हाल 16:
		info->fix.line_length = sp->width * 2;
		अवरोध;
	हाल 24:
		info->fix.line_length = sp->width * 3;
		अवरोध;
	हाल 32:
		info->fix.line_length = sp->width * 4;
		अवरोध;
	पूर्ण
	sp->fb_size = info->fix.line_length * sp->height;

	sp->fb_base = ioremap(sp->fb_base_phys, sp->fb_size);
	अगर (!sp->fb_base) अणु
		err = -ENOMEM;
		जाओ err_release_pci;
	पूर्ण

	err = s3d_set_fbinfo(sp);
	अगर (err)
		जाओ err_unmap_fb;

	pci_set_drvdata(pdev, info);

	prपूर्णांकk("s3d: Found device at %s\n", pci_name(pdev));

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "s3d: Could not register framebuffer %s\n",
		       pci_name(pdev));
		जाओ err_unmap_fb;
	पूर्ण

	वापस 0;

err_unmap_fb:
	iounmap(sp->fb_base);

err_release_pci:
	pci_release_region(pdev, 1);

err_release_fb:
        framebuffer_release(info);

err_disable:
	pci_disable_device(pdev);

err_out:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा pci_device_id s3d_pci_table[] = अणु
	अणु	PCI_DEVICE(PCI_VENDOR_ID_3DLABS, 0x002c),	पूर्ण,
	अणु	PCI_DEVICE(PCI_VENDOR_ID_3DLABS, 0x002d),	पूर्ण,
	अणु	PCI_DEVICE(PCI_VENDOR_ID_3DLABS, 0x002e),	पूर्ण,
	अणु	PCI_DEVICE(PCI_VENDOR_ID_3DLABS, 0x002f),	पूर्ण,
	अणु	PCI_DEVICE(PCI_VENDOR_ID_3DLABS, 0x0030),	पूर्ण,
	अणु	PCI_DEVICE(PCI_VENDOR_ID_3DLABS, 0x0031),	पूर्ण,
	अणु	PCI_DEVICE(PCI_VENDOR_ID_3DLABS, 0x0032),	पूर्ण,
	अणु	PCI_DEVICE(PCI_VENDOR_ID_3DLABS, 0x0033),	पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver s3d_driver = अणु
	.driver = अणु
		.suppress_bind_attrs = true,
	पूर्ण,
	.name		= "s3d",
	.id_table	= s3d_pci_table,
	.probe		= s3d_pci_रेजिस्टर,
पूर्ण;

अटल पूर्णांक __init s3d_init(व्योम)
अणु
	अगर (fb_get_options("s3d", शून्य))
		वापस -ENODEV;

	वापस pci_रेजिस्टर_driver(&s3d_driver);
पूर्ण
device_initcall(s3d_init);
