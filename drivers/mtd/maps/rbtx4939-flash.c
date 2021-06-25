<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rbtx4939-flash (based on physmap.c)
 *
 * This is a simplअगरied physmap driver with map_init callback function.
 *
 * Copyright (C) 2009 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <यंत्र/txx9/rbtx4939.h>

काष्ठा rbtx4939_flash_info अणु
	काष्ठा mtd_info *mtd;
	काष्ठा map_info map;
पूर्ण;

अटल पूर्णांक rbtx4939_flash_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा rbtx4939_flash_info *info;

	info = platक्रमm_get_drvdata(dev);
	अगर (!info)
		वापस 0;

	अगर (info->mtd) अणु
		mtd_device_unरेजिस्टर(info->mtd);
		map_destroy(info->mtd);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर rom_probe_types[] = अणु
	"cfi_probe", "jedec_probe", शून्य पूर्ण;

अटल पूर्णांक rbtx4939_flash_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा rbtx4939_flash_data *pdata;
	काष्ठा rbtx4939_flash_info *info;
	काष्ठा resource *res;
	स्थिर अक्षर * स्थिर *probe_type;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ size;

	pdata = dev_get_platdata(&dev->dev);
	अगर (!pdata)
		वापस -ENODEV;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;
	info = devm_kzalloc(&dev->dev, माप(काष्ठा rbtx4939_flash_info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(dev, info);

	size = resource_size(res);
	pr_notice("rbtx4939 platform flash device: %pR\n", res);

	अगर (!devm_request_mem_region(&dev->dev, res->start, size,
				     dev_name(&dev->dev)))
		वापस -EBUSY;

	info->map.name = dev_name(&dev->dev);
	info->map.phys = res->start;
	info->map.size = size;
	info->map.bankwidth = pdata->width;

	info->map.virt = devm_ioremap(&dev->dev, info->map.phys, size);
	अगर (!info->map.virt)
		वापस -EBUSY;

	अगर (pdata->map_init)
		(*pdata->map_init)(&info->map);
	अन्यथा
		simple_map_init(&info->map);

	probe_type = rom_probe_types;
	क्रम (; !info->mtd && *probe_type; probe_type++)
		info->mtd = करो_map_probe(*probe_type, &info->map);
	अगर (!info->mtd) अणु
		dev_err(&dev->dev, "map_probe failed\n");
		err = -ENXIO;
		जाओ err_out;
	पूर्ण
	info->mtd->dev.parent = &dev->dev;
	err = mtd_device_रेजिस्टर(info->mtd, pdata->parts, pdata->nr_parts);

	अगर (err)
		जाओ err_out;
	वापस 0;

err_out:
	rbtx4939_flash_हटाओ(dev);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम rbtx4939_flash_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा rbtx4939_flash_info *info = platक्रमm_get_drvdata(dev);

	अगर (mtd_suspend(info->mtd) == 0)
		mtd_resume(info->mtd);
पूर्ण
#अन्यथा
#घोषणा rbtx4939_flash_shutकरोwn शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver rbtx4939_flash_driver = अणु
	.probe		= rbtx4939_flash_probe,
	.हटाओ		= rbtx4939_flash_हटाओ,
	.shutकरोwn	= rbtx4939_flash_shutकरोwn,
	.driver		= अणु
		.name	= "rbtx4939-flash",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rbtx4939_flash_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("RBTX4939 MTD map driver");
MODULE_ALIAS("platform:rbtx4939-flash");
