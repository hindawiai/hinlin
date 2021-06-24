<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Speed Select Interface: MMIO Interface
 * Copyright (c) 2019, Intel Corporation.
 * All rights reserved.
 *
 * Author: Srinivas Pandruvada <srinivas.pandruvada@linux.पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uaccess.h>
#समावेश <uapi/linux/isst_अगर.h>

#समावेश "isst_if_common.h"

काष्ठा isst_mmio_range अणु
	पूर्णांक beg;
	पूर्णांक end;
पूर्ण;

अटल काष्ठा isst_mmio_range mmio_range_devid_0[] = अणु
	अणु0x04, 0x14पूर्ण,
	अणु0x20, 0xD0पूर्ण,
पूर्ण;

अटल काष्ठा isst_mmio_range mmio_range_devid_1[] = अणु
	अणु0x04, 0x14पूर्ण,
	अणु0x20, 0x11Cपूर्ण,
पूर्ण;

काष्ठा isst_अगर_device अणु
	व्योम __iomem *punit_mmio;
	u32 range_0[5];
	u32 range_1[64];
	काष्ठा isst_mmio_range *mmio_range;
	काष्ठा mutex mutex;
पूर्ण;

अटल दीर्घ isst_अगर_mmio_rd_wr(u8 *cmd_ptr, पूर्णांक *ग_लिखो_only, पूर्णांक resume)
अणु
	काष्ठा isst_अगर_device *punit_dev;
	काष्ठा isst_अगर_io_reg *io_reg;
	काष्ठा pci_dev *pdev;

	io_reg = (काष्ठा isst_अगर_io_reg *)cmd_ptr;

	अगर (io_reg->reg % 4)
		वापस -EINVAL;

	अगर (io_reg->पढ़ो_ग_लिखो && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	pdev = isst_अगर_get_pci_dev(io_reg->logical_cpu, 0, 0, 1);
	अगर (!pdev)
		वापस -EINVAL;

	punit_dev = pci_get_drvdata(pdev);
	अगर (!punit_dev)
		वापस -EINVAL;

	अगर (io_reg->reg < punit_dev->mmio_range[0].beg ||
	    io_reg->reg > punit_dev->mmio_range[1].end)
		वापस -EINVAL;

	/*
	 * Ensure that operation is complete on a PCI device to aव्योम पढ़ो
	 * ग_लिखो race by using per PCI device mutex.
	 */
	mutex_lock(&punit_dev->mutex);
	अगर (io_reg->पढ़ो_ग_लिखो) अणु
		ग_लिखोl(io_reg->value, punit_dev->punit_mmio+io_reg->reg);
		*ग_लिखो_only = 1;
	पूर्ण अन्यथा अणु
		io_reg->value = पढ़ोl(punit_dev->punit_mmio+io_reg->reg);
		*ग_लिखो_only = 0;
	पूर्ण
	mutex_unlock(&punit_dev->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id isst_अगर_ids[] = अणु
	अणु PCI_DEVICE_DATA(INTEL, RAPL_PRIO_DEVID_0, &mmio_range_devid_0)पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, RAPL_PRIO_DEVID_1, &mmio_range_devid_1)पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, isst_अगर_ids);

अटल पूर्णांक isst_अगर_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा isst_अगर_device *punit_dev;
	काष्ठा isst_अगर_cmd_cb cb;
	u32 mmio_base, pcu_base;
	u64 base_addr;
	पूर्णांक ret;

	punit_dev = devm_kzalloc(&pdev->dev, माप(*punit_dev), GFP_KERNEL);
	अगर (!punit_dev)
		वापस -ENOMEM;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	ret = pci_पढ़ो_config_dword(pdev, 0xD0, &mmio_base);
	अगर (ret)
		वापस ret;

	ret = pci_पढ़ो_config_dword(pdev, 0xFC, &pcu_base);
	अगर (ret)
		वापस ret;

	pcu_base &= GENMASK(10, 0);
	base_addr = (u64)mmio_base << 23 | (u64) pcu_base << 12;
	punit_dev->punit_mmio = devm_ioremap(&pdev->dev, base_addr, 256);
	अगर (!punit_dev->punit_mmio)
		वापस -ENOMEM;

	mutex_init(&punit_dev->mutex);
	pci_set_drvdata(pdev, punit_dev);
	punit_dev->mmio_range = (काष्ठा isst_mmio_range *) ent->driver_data;

	स_रखो(&cb, 0, माप(cb));
	cb.cmd_size = माप(काष्ठा isst_अगर_io_reg);
	cb.offset = दुरत्व(काष्ठा isst_अगर_io_regs, io_reg);
	cb.cmd_callback = isst_अगर_mmio_rd_wr;
	cb.owner = THIS_MODULE;
	ret = isst_अगर_cdev_रेजिस्टर(ISST_IF_DEV_MMIO, &cb);
	अगर (ret)
		mutex_destroy(&punit_dev->mutex);

	वापस ret;
पूर्ण

अटल व्योम isst_अगर_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा isst_अगर_device *punit_dev;

	punit_dev = pci_get_drvdata(pdev);
	isst_अगर_cdev_unरेजिस्टर(ISST_IF_DEV_MMIO);
	mutex_destroy(&punit_dev->mutex);
पूर्ण

अटल पूर्णांक __maybe_unused isst_अगर_suspend(काष्ठा device *device)
अणु
	काष्ठा isst_अगर_device *punit_dev = dev_get_drvdata(device);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(punit_dev->range_0); ++i)
		punit_dev->range_0[i] = पढ़ोl(punit_dev->punit_mmio +
						punit_dev->mmio_range[0].beg + 4 * i);
	क्रम (i = 0; i < ARRAY_SIZE(punit_dev->range_1); ++i) अणु
		u32 addr;

		addr = punit_dev->mmio_range[1].beg + 4 * i;
		अगर (addr > punit_dev->mmio_range[1].end)
			अवरोध;
		punit_dev->range_1[i] = पढ़ोl(punit_dev->punit_mmio + addr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused isst_अगर_resume(काष्ठा device *device)
अणु
	काष्ठा isst_अगर_device *punit_dev = dev_get_drvdata(device);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(punit_dev->range_0); ++i)
		ग_लिखोl(punit_dev->range_0[i], punit_dev->punit_mmio +
						punit_dev->mmio_range[0].beg + 4 * i);
	क्रम (i = 0; i < ARRAY_SIZE(punit_dev->range_1); ++i) अणु
		u32 addr;

		addr = punit_dev->mmio_range[1].beg + 4 * i;
		अगर (addr > punit_dev->mmio_range[1].end)
			अवरोध;

		ग_लिखोl(punit_dev->range_1[i], punit_dev->punit_mmio + addr);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(isst_अगर_pm_ops, isst_अगर_suspend, isst_अगर_resume);

अटल काष्ठा pci_driver isst_अगर_pci_driver = अणु
	.name			= "isst_if_pci",
	.id_table		= isst_अगर_ids,
	.probe			= isst_अगर_probe,
	.हटाओ			= isst_अगर_हटाओ,
	.driver.pm		= &isst_अगर_pm_ops,
पूर्ण;

module_pci_driver(isst_अगर_pci_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel speed select interface mmio driver");
