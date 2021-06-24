<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Map driver क्रम Intel XScale PXA2xx platक्रमms.
 *
 * Author:	Nicolas Pitre
 * Copyright:	(C) 2001 MontaVista Software Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <यंत्र/पन.स>
#समावेश <mach/hardware.h>

#समावेश <यंत्र/mach/flash.h>

#घोषणा CACHELINESIZE	32

अटल व्योम pxa2xx_map_inval_cache(काष्ठा map_info *map, अचिन्हित दीर्घ from,
				      sमाप_प्रकार len)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)map->cached + from;
	अचिन्हित दीर्घ end = start + len;

	start &= ~(CACHELINESIZE - 1);
	जबतक (start < end) अणु
		/* invalidate D cache line */
		यंत्र अस्थिर ("mcr p15, 0, %0, c7, c6, 1" : : "r" (start));
		start += CACHELINESIZE;
	पूर्ण
पूर्ण

काष्ठा pxa2xx_flash_info अणु
	काष्ठा mtd_info		*mtd;
	काष्ठा map_info		map;
पूर्ण;

अटल स्थिर अक्षर * स्थिर probes[] = अणु "RedBoot", "cmdlinepart", शून्य पूर्ण;

अटल पूर्णांक pxa2xx_flash_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा flash_platक्रमm_data *flash = dev_get_platdata(&pdev->dev);
	काष्ठा pxa2xx_flash_info *info;
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	info = kzalloc(माप(काष्ठा pxa2xx_flash_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->map.name = flash->name;
	info->map.bankwidth = flash->width;
	info->map.phys = res->start;
	info->map.size = resource_size(res);

	info->map.virt = ioremap(info->map.phys, info->map.size);
	अगर (!info->map.virt) अणु
		prपूर्णांकk(KERN_WARNING "Failed to ioremap %s\n",
		       info->map.name);
		वापस -ENOMEM;
	पूर्ण
	info->map.cached = ioremap_cache(info->map.phys, info->map.size);
	अगर (!info->map.cached)
		prपूर्णांकk(KERN_WARNING "Failed to ioremap cached %s\n",
		       info->map.name);
	info->map.inval_cache = pxa2xx_map_inval_cache;
	simple_map_init(&info->map);

	prपूर्णांकk(KERN_NOTICE
	       "Probing %s at physical address 0x%08lx"
	       " (%d-bit bankwidth)\n",
	       info->map.name, (अचिन्हित दीर्घ)info->map.phys,
	       info->map.bankwidth * 8);

	info->mtd = करो_map_probe(flash->map_name, &info->map);

	अगर (!info->mtd) अणु
		iounmap((व्योम *)info->map.virt);
		अगर (info->map.cached)
			iounmap(info->map.cached);
		वापस -EIO;
	पूर्ण
	info->mtd->dev.parent = &pdev->dev;

	mtd_device_parse_रेजिस्टर(info->mtd, probes, शून्य, flash->parts,
				  flash->nr_parts);

	platक्रमm_set_drvdata(pdev, info);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_flash_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा pxa2xx_flash_info *info = platक्रमm_get_drvdata(dev);

	mtd_device_unरेजिस्टर(info->mtd);

	map_destroy(info->mtd);
	iounmap(info->map.virt);
	अगर (info->map.cached)
		iounmap(info->map.cached);
	kमुक्त(info);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम pxa2xx_flash_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा pxa2xx_flash_info *info = platक्रमm_get_drvdata(dev);

	अगर (info && mtd_suspend(info->mtd) == 0)
		mtd_resume(info->mtd);
पूर्ण
#अन्यथा
#घोषणा pxa2xx_flash_shutकरोwn शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver pxa2xx_flash_driver = अणु
	.driver = अणु
		.name		= "pxa2xx-flash",
	पूर्ण,
	.probe		= pxa2xx_flash_probe,
	.हटाओ		= pxa2xx_flash_हटाओ,
	.shutकरोwn	= pxa2xx_flash_shutकरोwn,
पूर्ण;

module_platक्रमm_driver(pxa2xx_flash_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nicolas Pitre <nico@fluxnic.net>");
MODULE_DESCRIPTION("MTD map driver for Intel XScale PXA2xx");
