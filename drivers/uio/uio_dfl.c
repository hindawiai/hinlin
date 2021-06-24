<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic DFL driver क्रम Userspace I/O devicess
 *
 * Copyright (C) 2021 Intel Corporation, Inc.
 */
#समावेश <linux/dfl.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/uio_driver.h>

#घोषणा DRIVER_NAME "uio_dfl"

अटल पूर्णांक uio_dfl_probe(काष्ठा dfl_device *ddev)
अणु
	काष्ठा resource *r = &ddev->mmio_res;
	काष्ठा device *dev = &ddev->dev;
	काष्ठा uio_info *uioinfo;
	काष्ठा uio_mem *uiomem;
	पूर्णांक ret;

	uioinfo = devm_kzalloc(dev, माप(काष्ठा uio_info), GFP_KERNEL);
	अगर (!uioinfo)
		वापस -ENOMEM;

	uioinfo->name = DRIVER_NAME;
	uioinfo->version = "0";

	uiomem = &uioinfo->mem[0];
	uiomem->memtype = UIO_MEM_PHYS;
	uiomem->addr = r->start & PAGE_MASK;
	uiomem->offs = r->start & ~PAGE_MASK;
	uiomem->size = (uiomem->offs + resource_size(r)
			+ PAGE_SIZE - 1) & PAGE_MASK;
	uiomem->name = r->name;

	/* Irq is yet to be supported */
	uioinfo->irq = UIO_IRQ_NONE;

	ret = devm_uio_रेजिस्टर_device(dev, uioinfo);
	अगर (ret)
		dev_err(dev, "unable to register uio device\n");

	वापस ret;
पूर्ण

#घोषणा FME_FEATURE_ID_ETH_GROUP	0x10

अटल स्थिर काष्ठा dfl_device_id uio_dfl_ids[] = अणु
	अणु FME_ID, FME_FEATURE_ID_ETH_GROUP पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dfl, uio_dfl_ids);

अटल काष्ठा dfl_driver uio_dfl_driver = अणु
	.drv = अणु
		.name = DRIVER_NAME,
	पूर्ण,
	.id_table	= uio_dfl_ids,
	.probe		= uio_dfl_probe,
पूर्ण;
module_dfl_driver(uio_dfl_driver);

MODULE_DESCRIPTION("Generic DFL driver for Userspace I/O devices");
MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
