<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Framebuffer driver क्रम mdpy (mediated भव pci display device).
 *
 * See mdpy-defs.h क्रम device specs
 *
 *   (c) Gerd Hoffmann <kraxel@redhat.com>
 *
 * Using some code snippets from simplefb and cirrusfb.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <drm/drm_fourcc.h>
#समावेश "mdpy-defs.h"

अटल स्थिर काष्ठा fb_fix_screeninfo mdpy_fb_fix = अणु
	.id		= "mdpy-fb",
	.type		= FB_TYPE_PACKED_PIXELS,
	.visual		= FB_VISUAL_TRUECOLOR,
	.accel		= FB_ACCEL_NONE,
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo mdpy_fb_var = अणु
	.height		= -1,
	.width		= -1,
	.activate	= FB_ACTIVATE_NOW,
	.vmode		= FB_VMODE_NONINTERLACED,

	.bits_per_pixel = 32,
	.transp.offset	= 24,
	.red.offset	= 16,
	.green.offset	= 8,
	.blue.offset	= 0,
	.transp.length	= 8,
	.red.length	= 8,
	.green.length	= 8,
	.blue.length	= 8,
पूर्ण;

#घोषणा PSEUDO_PALETTE_SIZE 16

काष्ठा mdpy_fb_par अणु
	u32 palette[PSEUDO_PALETTE_SIZE];
पूर्ण;

अटल पूर्णांक mdpy_fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			      u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	u32 *pal = info->pseuकरो_palette;
	u32 cr = red >> (16 - info->var.red.length);
	u32 cg = green >> (16 - info->var.green.length);
	u32 cb = blue >> (16 - info->var.blue.length);
	u32 value, mask;

	अगर (regno >= PSEUDO_PALETTE_SIZE)
		वापस -EINVAL;

	value = (cr << info->var.red.offset) |
		(cg << info->var.green.offset) |
		(cb << info->var.blue.offset);
	अगर (info->var.transp.length > 0) अणु
		mask = (1 << info->var.transp.length) - 1;
		mask <<= info->var.transp.offset;
		value |= mask;
	पूर्ण
	pal[regno] = value;

	वापस 0;
पूर्ण

अटल व्योम mdpy_fb_destroy(काष्ठा fb_info *info)
अणु
	अगर (info->screen_base)
		iounmap(info->screen_base);
पूर्ण

अटल स्थिर काष्ठा fb_ops mdpy_fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_destroy	= mdpy_fb_destroy,
	.fb_setcolreg	= mdpy_fb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल पूर्णांक mdpy_fb_probe(काष्ठा pci_dev *pdev,
			 स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा fb_info *info;
	काष्ठा mdpy_fb_par *par;
	u32 क्रमmat, width, height;
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret < 0)
		वापस ret;

	ret = pci_request_regions(pdev, "mdpy-fb");
	अगर (ret < 0)
		वापस ret;

	pci_पढ़ो_config_dword(pdev, MDPY_FORMAT_OFFSET, &क्रमmat);
	pci_पढ़ो_config_dword(pdev, MDPY_WIDTH_OFFSET,	&width);
	pci_पढ़ो_config_dword(pdev, MDPY_HEIGHT_OFFSET, &height);
	अगर (क्रमmat != DRM_FORMAT_XRGB8888) अणु
		pci_err(pdev, "format mismatch (0x%x != 0x%x)\n",
			क्रमmat, DRM_FORMAT_XRGB8888);
		ret = -EINVAL;
		जाओ err_release_regions;
	पूर्ण
	अगर (width < 100	 || width > 10000) अणु
		pci_err(pdev, "width (%d) out of range\n", width);
		ret = -EINVAL;
		जाओ err_release_regions;
	पूर्ण
	अगर (height < 100 || height > 10000) अणु
		pci_err(pdev, "height (%d) out of range\n", height);
		ret = -EINVAL;
		जाओ err_release_regions;
	पूर्ण
	pci_info(pdev, "mdpy found: %dx%d framebuffer\n",
		 width, height);

	info = framebuffer_alloc(माप(काष्ठा mdpy_fb_par), &pdev->dev);
	अगर (!info) अणु
		ret = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण
	pci_set_drvdata(pdev, info);
	par = info->par;

	info->fix = mdpy_fb_fix;
	info->fix.smem_start = pci_resource_start(pdev, 0);
	info->fix.smem_len = pci_resource_len(pdev, 0);
	info->fix.line_length = width * 4;

	info->var = mdpy_fb_var;
	info->var.xres = width;
	info->var.yres = height;
	info->var.xres_भव = width;
	info->var.yres_भव = height;

	info->screen_size = info->fix.smem_len;
	info->screen_base = ioremap(info->fix.smem_start,
				    info->screen_size);
	अगर (!info->screen_base) अणु
		pci_err(pdev, "ioremap(pcibar) failed\n");
		ret = -EIO;
		जाओ err_release_fb;
	पूर्ण

	info->apertures = alloc_apertures(1);
	अगर (!info->apertures) अणु
		ret = -ENOMEM;
		जाओ err_unmap;
	पूर्ण
	info->apertures->ranges[0].base = info->fix.smem_start;
	info->apertures->ranges[0].size = info->fix.smem_len;

	info->fbops = &mdpy_fb_ops;
	info->flags = FBINFO_DEFAULT;
	info->pseuकरो_palette = par->palette;

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0) अणु
		pci_err(pdev, "mdpy-fb device register failed: %d\n", ret);
		जाओ err_unmap;
	पूर्ण

	pci_info(pdev, "fb%d registered\n", info->node);
	वापस 0;

err_unmap:
	iounmap(info->screen_base);

err_release_fb:
	framebuffer_release(info);

err_release_regions:
	pci_release_regions(pdev);

	वापस ret;
पूर्ण

अटल व्योम mdpy_fb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pdev);

	unरेजिस्टर_framebuffer(info);
	framebuffer_release(info);
पूर्ण

अटल काष्ठा pci_device_id mdpy_fb_pci_table[] = अणु
	अणु
		.venकरोr	   = MDPY_PCI_VENDOR_ID,
		.device	   = MDPY_PCI_DEVICE_ID,
		.subvenकरोr = MDPY_PCI_SUBVENDOR_ID,
		.subdevice = MDPY_PCI_SUBDEVICE_ID,
	पूर्ण, अणु
		/* end of list */
	पूर्ण
पूर्ण;

अटल काष्ठा pci_driver mdpy_fb_pci_driver = अणु
	.name		= "mdpy-fb",
	.id_table	= mdpy_fb_pci_table,
	.probe		= mdpy_fb_probe,
	.हटाओ		= mdpy_fb_हटाओ,
पूर्ण;

अटल पूर्णांक __init mdpy_fb_init(व्योम)
अणु
	पूर्णांक ret;

	ret = pci_रेजिस्टर_driver(&mdpy_fb_pci_driver);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

module_init(mdpy_fb_init);

MODULE_DEVICE_TABLE(pci, mdpy_fb_pci_table);
MODULE_LICENSE("GPL v2");
