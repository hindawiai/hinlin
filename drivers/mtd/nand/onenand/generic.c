<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (c) 2005 Samsung Electronics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 *
 *  Overview:
 *   This is a device driver क्रम the Oneन_अंकD flash क्रम generic boards.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/onenand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/पन.स>

/*
 * Note: Driver name and platक्रमm data क्रमmat have been updated!
 *
 * This version of the driver is named "onenand-flash" and takes काष्ठा
 * onenand_platक्रमm_data as platक्रमm data. The old ARM-specअगरic version
 * with the name "onenand" used to take काष्ठा flash_platक्रमm_data.
 */
#घोषणा DRIVER_NAME	"onenand-flash"

काष्ठा onenand_info अणु
	काष्ठा mtd_info		mtd;
	काष्ठा onenand_chip	onenand;
पूर्ण;

अटल पूर्णांक generic_onenand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा onenand_info *info;
	काष्ठा onenand_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा resource *res = pdev->resource;
	अचिन्हित दीर्घ size = resource_size(res);
	पूर्णांक err;

	info = kzalloc(माप(काष्ठा onenand_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	अगर (!request_mem_region(res->start, size, dev_name(&pdev->dev))) अणु
		err = -EBUSY;
		जाओ out_मुक्त_info;
	पूर्ण

	info->onenand.base = ioremap(res->start, size);
	अगर (!info->onenand.base) अणु
		err = -ENOMEM;
		जाओ out_release_mem_region;
	पूर्ण

	info->onenand.mmcontrol = pdata ? pdata->mmcontrol : शून्य;
	info->onenand.irq = platक्रमm_get_irq(pdev, 0);

	info->mtd.dev.parent = &pdev->dev;
	info->mtd.priv = &info->onenand;

	अगर (onenand_scan(&info->mtd, 1)) अणु
		err = -ENXIO;
		जाओ out_iounmap;
	पूर्ण

	err = mtd_device_रेजिस्टर(&info->mtd, pdata ? pdata->parts : शून्य,
				  pdata ? pdata->nr_parts : 0);

	platक्रमm_set_drvdata(pdev, info);

	वापस 0;

out_iounmap:
	iounmap(info->onenand.base);
out_release_mem_region:
	release_mem_region(res->start, size);
out_मुक्त_info:
	kमुक्त(info);

	वापस err;
पूर्ण

अटल पूर्णांक generic_onenand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा onenand_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा resource *res = pdev->resource;
	अचिन्हित दीर्घ size = resource_size(res);

	अगर (info) अणु
		onenand_release(&info->mtd);
		release_mem_region(res->start, size);
		iounmap(info->onenand.base);
		kमुक्त(info);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver generic_onenand_driver = अणु
	.driver = अणु
		.name		= DRIVER_NAME,
	पूर्ण,
	.probe		= generic_onenand_probe,
	.हटाओ		= generic_onenand_हटाओ,
पूर्ण;

module_platक्रमm_driver(generic_onenand_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kyungmin Park <kyungmin.park@samsung.com>");
MODULE_DESCRIPTION("Glue layer for OneNAND flash on generic boards");
MODULE_ALIAS("platform:" DRIVER_NAME);
