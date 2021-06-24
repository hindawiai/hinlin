<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * न_अंकD Flash Controller Device Driver
 * Copyright तऊ 2009-2010, Intel Corporation and its suppliers.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "denali.h"

#घोषणा DENALI_न_अंकD_NAME    "denali-nand-pci"

#घोषणा INTEL_CE4100	1
#घोषणा INTEL_MRST	2

/* List of platक्रमms this न_अंकD controller has be पूर्णांकegrated पूर्णांकo */
अटल स्थिर काष्ठा pci_device_id denali_pci_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x0701), INTEL_CE4100 पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0809), INTEL_MRST पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, denali_pci_ids);

न_अंकD_ECC_CAPS_SINGLE(denali_pci_ecc_caps, denali_calc_ecc_bytes, 512, 8, 15);

अटल पूर्णांक denali_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	resource_माप_प्रकार csr_base, mem_base;
	अचिन्हित दीर्घ csr_len, mem_len;
	काष्ठा denali_controller *denali;
	काष्ठा denali_chip *dchip;
	पूर्णांक nsels, ret, i;

	denali = devm_kzalloc(&dev->dev, माप(*denali), GFP_KERNEL);
	अगर (!denali)
		वापस -ENOMEM;

	ret = pcim_enable_device(dev);
	अगर (ret) अणु
		dev_err(&dev->dev, "Spectra: pci_enable_device failed.\n");
		वापस ret;
	पूर्ण

	अगर (id->driver_data == INTEL_CE4100) अणु
		mem_base = pci_resource_start(dev, 0);
		mem_len = pci_resource_len(dev, 1);
		csr_base = pci_resource_start(dev, 1);
		csr_len = pci_resource_len(dev, 1);
	पूर्ण अन्यथा अणु
		csr_base = pci_resource_start(dev, 0);
		csr_len = pci_resource_len(dev, 0);
		mem_base = pci_resource_start(dev, 1);
		mem_len = pci_resource_len(dev, 1);
		अगर (!mem_len) अणु
			mem_base = csr_base + csr_len;
			mem_len = csr_len;
		पूर्ण
	पूर्ण

	pci_set_master(dev);
	denali->dev = &dev->dev;
	denali->irq = dev->irq;
	denali->ecc_caps = &denali_pci_ecc_caps;
	denali->clk_rate = 50000000;		/* 50 MHz */
	denali->clk_x_rate = 200000000;		/* 200 MHz */

	ret = pci_request_regions(dev, DENALI_न_अंकD_NAME);
	अगर (ret) अणु
		dev_err(&dev->dev, "Spectra: Unable to request memory regions\n");
		वापस ret;
	पूर्ण

	denali->reg = ioremap(csr_base, csr_len);
	अगर (!denali->reg) अणु
		dev_err(&dev->dev, "Spectra: Unable to remap memory region\n");
		वापस -ENOMEM;
	पूर्ण

	denali->host = ioremap(mem_base, mem_len);
	अगर (!denali->host) अणु
		dev_err(&dev->dev, "Spectra: ioremap failed!");
		ret = -ENOMEM;
		जाओ out_unmap_reg;
	पूर्ण

	ret = denali_init(denali);
	अगर (ret)
		जाओ out_unmap_host;

	nsels = denali->nbanks;

	dchip = devm_kzalloc(denali->dev, काष्ठा_size(dchip, sels, nsels),
			     GFP_KERNEL);
	अगर (!dchip) अणु
		ret = -ENOMEM;
		जाओ out_हटाओ_denali;
	पूर्ण

	dchip->chip.base.ecc.user_conf.flags |= न_अंकD_ECC_MAXIMIZE_STRENGTH;

	dchip->nsels = nsels;

	क्रम (i = 0; i < nsels; i++)
		dchip->sels[i].bank = i;

	ret = denali_chip_init(denali, dchip);
	अगर (ret)
		जाओ out_हटाओ_denali;

	pci_set_drvdata(dev, denali);

	वापस 0;

out_हटाओ_denali:
	denali_हटाओ(denali);
out_unmap_host:
	iounmap(denali->host);
out_unmap_reg:
	iounmap(denali->reg);
	वापस ret;
पूर्ण

अटल व्योम denali_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा denali_controller *denali = pci_get_drvdata(dev);

	denali_हटाओ(denali);
	iounmap(denali->reg);
	iounmap(denali->host);
पूर्ण

अटल काष्ठा pci_driver denali_pci_driver = अणु
	.name = DENALI_न_अंकD_NAME,
	.id_table = denali_pci_ids,
	.probe = denali_pci_probe,
	.हटाओ = denali_pci_हटाओ,
पूर्ण;
module_pci_driver(denali_pci_driver);

MODULE_DESCRIPTION("PCI driver for Denali NAND controller");
MODULE_AUTHOR("Intel Corporation and its suppliers");
MODULE_LICENSE("GPL v2");
