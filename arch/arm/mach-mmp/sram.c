<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/sram.c
 *
 *  based on mach-davinci/sram.c - DaVinci simple SRAM allocator
 *
 *  Copyright (c) 2011 Marvell Semiconductors Inc.
 *  All Rights Reserved
 *
 *  Add क्रम mmp sram support - Leo Yan <leoy@marvell.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/genभाग.स>

#समावेश <linux/platक्रमm_data/dma-mmp_tdma.h>

काष्ठा sram_bank_info अणु
	अक्षर *pool_name;
	काष्ठा gen_pool *gpool;
	पूर्णांक granularity;

	phys_addr_t sram_phys;
	व्योम __iomem *sram_virt;
	u32 sram_size;

	काष्ठा list_head node;
पूर्ण;

अटल DEFINE_MUTEX(sram_lock);
अटल LIST_HEAD(sram_bank_list);

काष्ठा gen_pool *sram_get_gpool(अक्षर *pool_name)
अणु
	काष्ठा sram_bank_info *info = शून्य;

	अगर (!pool_name)
		वापस शून्य;

	mutex_lock(&sram_lock);

	list_क्रम_each_entry(info, &sram_bank_list, node)
		अगर (!म_भेद(pool_name, info->pool_name))
			अवरोध;

	mutex_unlock(&sram_lock);

	अगर (&info->node == &sram_bank_list)
		वापस शून्य;

	वापस info->gpool;
पूर्ण
EXPORT_SYMBOL(sram_get_gpool);

अटल पूर्णांक sram_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sram_platdata *pdata = pdev->dev.platक्रमm_data;
	काष्ठा sram_bank_info *info;
	काष्ठा resource *res;
	पूर्णांक ret = 0;

	अगर (!pdata || !pdata->pool_name)
		वापस -ENODEV;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "no memory resource defined\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!resource_size(res))
		वापस 0;

	info->sram_phys   = (phys_addr_t)res->start;
	info->sram_size   = resource_size(res);
	info->sram_virt   = ioremap(info->sram_phys, info->sram_size);
	info->pool_name	  = kstrdup(pdata->pool_name, GFP_KERNEL);
	info->granularity = pdata->granularity;

	info->gpool = gen_pool_create(ilog2(info->granularity), -1);
	अगर (!info->gpool) अणु
		dev_err(&pdev->dev, "create pool failed\n");
		ret = -ENOMEM;
		जाओ create_pool_err;
	पूर्ण

	ret = gen_pool_add_virt(info->gpool, (अचिन्हित दीर्घ)info->sram_virt,
				info->sram_phys, info->sram_size, -1);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "add new chunk failed\n");
		ret = -ENOMEM;
		जाओ add_chunk_err;
	पूर्ण

	mutex_lock(&sram_lock);
	list_add(&info->node, &sram_bank_list);
	mutex_unlock(&sram_lock);

	platक्रमm_set_drvdata(pdev, info);

	dev_info(&pdev->dev, "initialized\n");
	वापस 0;

add_chunk_err:
	gen_pool_destroy(info->gpool);
create_pool_err:
	iounmap(info->sram_virt);
	kमुक्त(info->pool_name);
out:
	kमुक्त(info);
	वापस ret;
पूर्ण

अटल पूर्णांक sram_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sram_bank_info *info;

	info = platक्रमm_get_drvdata(pdev);
	अगर (info == शून्य)
		वापस -ENODEV;

	mutex_lock(&sram_lock);
	list_del(&info->node);
	mutex_unlock(&sram_lock);

	gen_pool_destroy(info->gpool);
	iounmap(info->sram_virt);
	kमुक्त(info->pool_name);
	kमुक्त(info);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id sram_id_table[] = अणु
	अणु "asram", MMP_ASRAM पूर्ण,
	अणु "isram", MMP_ISRAM पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sram_driver = अणु
	.probe		= sram_probe,
	.हटाओ		= sram_हटाओ,
	.driver		= अणु
		.name	= "mmp-sram",
	पूर्ण,
	.id_table	= sram_id_table,
पूर्ण;

अटल पूर्णांक __init sram_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sram_driver);
पूर्ण
core_initcall(sram_init);

MODULE_LICENSE("GPL");
