<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * framebuffer-coreboot.c
 *
 * Memory based framebuffer accessed through coreboot table.
 *
 * Copyright 2012-2013 David Herrmann <dh.herrmann@gmail.com>
 * Copyright 2017 Google Inc.
 * Copyright 2017 Samuel Holland <samuel@sholland.org>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/simplefb.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "coreboot_table.h"

#घोषणा CB_TAG_FRAMEBUFFER 0x12

अटल स्थिर काष्ठा simplefb_क्रमmat क्रमmats[] = SIMPLEFB_FORMATS;

अटल पूर्णांक framebuffer_probe(काष्ठा coreboot_device *dev)
अणु
	पूर्णांक i;
	u32 length;
	काष्ठा lb_framebuffer *fb = &dev->framebuffer;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource res;
	काष्ठा simplefb_platक्रमm_data pdata = अणु
		.width = fb->x_resolution,
		.height = fb->y_resolution,
		.stride = fb->bytes_per_line,
		.क्रमmat = शून्य,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); ++i) अणु
		अगर (fb->bits_per_pixel     == क्रमmats[i].bits_per_pixel &&
		    fb->red_mask_pos       == क्रमmats[i].red.offset &&
		    fb->red_mask_size      == क्रमmats[i].red.length &&
		    fb->green_mask_pos     == क्रमmats[i].green.offset &&
		    fb->green_mask_size    == क्रमmats[i].green.length &&
		    fb->blue_mask_pos      == क्रमmats[i].blue.offset &&
		    fb->blue_mask_size     == क्रमmats[i].blue.length &&
		    fb->reserved_mask_pos  == क्रमmats[i].transp.offset &&
		    fb->reserved_mask_size == क्रमmats[i].transp.length)
			pdata.क्रमmat = क्रमmats[i].name;
	पूर्ण
	अगर (!pdata.क्रमmat)
		वापस -ENODEV;

	स_रखो(&res, 0, माप(res));
	res.flags = IORESOURCE_MEM | IORESOURCE_BUSY;
	res.name = "Coreboot Framebuffer";
	res.start = fb->physical_address;
	length = PAGE_ALIGN(fb->y_resolution * fb->bytes_per_line);
	res.end = res.start + length - 1;
	अगर (res.end <= res.start)
		वापस -EINVAL;

	pdev = platक्रमm_device_रेजिस्टर_resndata(&dev->dev,
						 "simple-framebuffer", 0,
						 &res, 1, &pdata,
						 माप(pdata));
	अगर (IS_ERR(pdev))
		pr_warn("coreboot: could not register framebuffer\n");
	अन्यथा
		dev_set_drvdata(&dev->dev, pdev);

	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण

अटल व्योम framebuffer_हटाओ(काष्ठा coreboot_device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev_get_drvdata(&dev->dev);

	platक्रमm_device_unरेजिस्टर(pdev);
पूर्ण

अटल काष्ठा coreboot_driver framebuffer_driver = अणु
	.probe = framebuffer_probe,
	.हटाओ = framebuffer_हटाओ,
	.drv = अणु
		.name = "framebuffer",
	पूर्ण,
	.tag = CB_TAG_FRAMEBUFFER,
पूर्ण;
module_coreboot_driver(framebuffer_driver);

MODULE_AUTHOR("Samuel Holland <samuel@sholland.org>");
MODULE_LICENSE("GPL");
