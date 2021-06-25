<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/video/wmt_ge_rops.c
 *
 *  Accelerators क्रम raster operations using WonderMedia Graphics Engine
 *
 *  Copyright (C) 2010 Alexey Charkov <alअक्षरk@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/fb.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "core/fb_draw.h"
#समावेश "wmt_ge_rops.h"

#घोषणा GE_COMMAND_OFF		0x00
#घोषणा GE_DEPTH_OFF		0x04
#घोषणा GE_HIGHCOLOR_OFF	0x08
#घोषणा GE_ROPCODE_OFF		0x14
#घोषणा GE_FIRE_OFF		0x18
#घोषणा GE_SRCBASE_OFF		0x20
#घोषणा GE_SRCDISPW_OFF		0x24
#घोषणा GE_SRCDISPH_OFF		0x28
#घोषणा GE_SRCAREAX_OFF		0x2c
#घोषणा GE_SRCAREAY_OFF		0x30
#घोषणा GE_SRCAREAW_OFF		0x34
#घोषणा GE_SRCAREAH_OFF		0x38
#घोषणा GE_DESTBASE_OFF		0x3c
#घोषणा GE_DESTDISPW_OFF	0x40
#घोषणा GE_DESTDISPH_OFF	0x44
#घोषणा GE_DESTAREAX_OFF	0x48
#घोषणा GE_DESTAREAY_OFF	0x4c
#घोषणा GE_DESTAREAW_OFF	0x50
#घोषणा GE_DESTAREAH_OFF	0x54
#घोषणा GE_PAT0C_OFF		0x88	/* Pattern 0 color */
#घोषणा GE_ENABLE_OFF		0xec
#घोषणा GE_INTEN_OFF		0xf0
#घोषणा GE_STATUS_OFF		0xf8

अटल व्योम __iomem *regbase;

व्योम wmt_ge_fillrect(काष्ठा fb_info *p, स्थिर काष्ठा fb_fillrect *rect)
अणु
	अचिन्हित दीर्घ fg, pat;

	अगर (p->state != FBINFO_STATE_RUNNING)
		वापस;

	अगर (p->fix.visual == FB_VISUAL_TRUECOLOR ||
	    p->fix.visual == FB_VISUAL_सूचीECTCOLOR)
		fg = ((u32 *) (p->pseuकरो_palette))[rect->color];
	अन्यथा
		fg = rect->color;

	pat = pixel_to_pat(p->var.bits_per_pixel, fg);

	अगर (p->fbops->fb_sync)
		p->fbops->fb_sync(p);

	ग_लिखोl(p->var.bits_per_pixel == 32 ? 3 :
	      (p->var.bits_per_pixel == 8 ? 0 : 1), regbase + GE_DEPTH_OFF);
	ग_लिखोl(p->var.bits_per_pixel == 15 ? 1 : 0, regbase + GE_HIGHCOLOR_OFF);
	ग_लिखोl(p->fix.smem_start, regbase + GE_DESTBASE_OFF);
	ग_लिखोl(p->var.xres_भव - 1, regbase + GE_DESTDISPW_OFF);
	ग_लिखोl(p->var.yres_भव - 1, regbase + GE_DESTDISPH_OFF);
	ग_लिखोl(rect->dx, regbase + GE_DESTAREAX_OFF);
	ग_लिखोl(rect->dy, regbase + GE_DESTAREAY_OFF);
	ग_लिखोl(rect->width - 1, regbase + GE_DESTAREAW_OFF);
	ग_लिखोl(rect->height - 1, regbase + GE_DESTAREAH_OFF);

	ग_लिखोl(pat, regbase + GE_PAT0C_OFF);
	ग_लिखोl(1, regbase + GE_COMMAND_OFF);
	ग_लिखोl(rect->rop == ROP_XOR ? 0x5a : 0xf0, regbase + GE_ROPCODE_OFF);
	ग_लिखोl(1, regbase + GE_FIRE_OFF);
पूर्ण
EXPORT_SYMBOL_GPL(wmt_ge_fillrect);

व्योम wmt_ge_copyarea(काष्ठा fb_info *p, स्थिर काष्ठा fb_copyarea *area)
अणु
	अगर (p->state != FBINFO_STATE_RUNNING)
		वापस;

	अगर (p->fbops->fb_sync)
		p->fbops->fb_sync(p);

	ग_लिखोl(p->var.bits_per_pixel > 16 ? 3 :
	      (p->var.bits_per_pixel > 8 ? 1 : 0), regbase + GE_DEPTH_OFF);

	ग_लिखोl(p->fix.smem_start, regbase + GE_SRCBASE_OFF);
	ग_लिखोl(p->var.xres_भव - 1, regbase + GE_SRCDISPW_OFF);
	ग_लिखोl(p->var.yres_भव - 1, regbase + GE_SRCDISPH_OFF);
	ग_लिखोl(area->sx, regbase + GE_SRCAREAX_OFF);
	ग_लिखोl(area->sy, regbase + GE_SRCAREAY_OFF);
	ग_लिखोl(area->width - 1, regbase + GE_SRCAREAW_OFF);
	ग_लिखोl(area->height - 1, regbase + GE_SRCAREAH_OFF);

	ग_लिखोl(p->fix.smem_start, regbase + GE_DESTBASE_OFF);
	ग_लिखोl(p->var.xres_भव - 1, regbase + GE_DESTDISPW_OFF);
	ग_लिखोl(p->var.yres_भव - 1, regbase + GE_DESTDISPH_OFF);
	ग_लिखोl(area->dx, regbase + GE_DESTAREAX_OFF);
	ग_लिखोl(area->dy, regbase + GE_DESTAREAY_OFF);
	ग_लिखोl(area->width - 1, regbase + GE_DESTAREAW_OFF);
	ग_लिखोl(area->height - 1, regbase + GE_DESTAREAH_OFF);

	ग_लिखोl(0xcc, regbase + GE_ROPCODE_OFF);
	ग_लिखोl(1, regbase + GE_COMMAND_OFF);
	ग_लिखोl(1, regbase + GE_FIRE_OFF);
पूर्ण
EXPORT_SYMBOL_GPL(wmt_ge_copyarea);

पूर्णांक wmt_ge_sync(काष्ठा fb_info *p)
अणु
	पूर्णांक loops = 5000000;
	जबतक ((पढ़ोl(regbase + GE_STATUS_OFF) & 4) && --loops)
		cpu_relax();
	वापस loops > 0 ? 0 : -EBUSY;
पूर्ण
EXPORT_SYMBOL_GPL(wmt_ge_sync);

अटल पूर्णांक wmt_ge_rops_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "no I/O memory resource defined\n");
		वापस -ENODEV;
	पूर्ण

	/* Only one ROP engine is presently supported. */
	अगर (unlikely(regbase)) अणु
		WARN_ON(1);
		वापस -EBUSY;
	पूर्ण

	regbase = ioremap(res->start, resource_size(res));
	अगर (regbase == शून्य) अणु
		dev_err(&pdev->dev, "failed to map I/O memory\n");
		वापस -EBUSY;
	पूर्ण

	ग_लिखोl(1, regbase + GE_ENABLE_OFF);
	prपूर्णांकk(KERN_INFO "Enabled support for WMT GE raster acceleration\n");

	वापस 0;
पूर्ण

अटल पूर्णांक wmt_ge_rops_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	iounmap(regbase);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id wmt_dt_ids[] = अणु
	अणु .compatible = "wm,prizm-ge-rops", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver wmt_ge_rops_driver = अणु
	.probe		= wmt_ge_rops_probe,
	.हटाओ		= wmt_ge_rops_हटाओ,
	.driver		= अणु
		.name	= "wmt_ge_rops",
		.of_match_table = wmt_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wmt_ge_rops_driver);

MODULE_AUTHOR("Alexey Charkov <alchark@gmail.com>");
MODULE_DESCRIPTION("Accelerators for raster operations using "
		   "WonderMedia Graphics Engine");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, wmt_dt_ids);
