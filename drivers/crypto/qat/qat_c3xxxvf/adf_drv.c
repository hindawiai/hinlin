<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पन.स>
#समावेश <adf_accel_devices.h>
#समावेश <adf_common_drv.h>
#समावेश <adf_cfg.h>
#समावेश "adf_c3xxxvf_hw_data.h"

अटल स्थिर काष्ठा pci_device_id adf_pci_tbl[] = अणु
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_QAT_C3XXX_VF), पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, adf_pci_tbl);

अटल पूर्णांक adf_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *ent);
अटल व्योम adf_हटाओ(काष्ठा pci_dev *dev);

अटल काष्ठा pci_driver adf_driver = अणु
	.id_table = adf_pci_tbl,
	.name = ADF_C3XXXVF_DEVICE_NAME,
	.probe = adf_probe,
	.हटाओ = adf_हटाओ,
पूर्ण;

अटल व्योम adf_cleanup_pci_dev(काष्ठा adf_accel_dev *accel_dev)
अणु
	pci_release_regions(accel_dev->accel_pci_dev.pci_dev);
	pci_disable_device(accel_dev->accel_pci_dev.pci_dev);
पूर्ण

अटल व्योम adf_cleanup_accel(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_accel_pci *accel_pci_dev = &accel_dev->accel_pci_dev;
	काष्ठा adf_accel_dev *pf;
	पूर्णांक i;

	क्रम (i = 0; i < ADF_PCI_MAX_BARS; i++) अणु
		काष्ठा adf_bar *bar = &accel_pci_dev->pci_bars[i];

		अगर (bar->virt_addr)
			pci_iounmap(accel_pci_dev->pci_dev, bar->virt_addr);
	पूर्ण

	अगर (accel_dev->hw_device) अणु
		चयन (accel_pci_dev->pci_dev->device) अणु
		हाल PCI_DEVICE_ID_INTEL_QAT_C3XXX_VF:
			adf_clean_hw_data_c3xxxiov(accel_dev->hw_device);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		kमुक्त(accel_dev->hw_device);
		accel_dev->hw_device = शून्य;
	पूर्ण
	adf_cfg_dev_हटाओ(accel_dev);
	debugfs_हटाओ(accel_dev->debugfs_dir);
	pf = adf_devmgr_pci_to_accel_dev(accel_pci_dev->pci_dev->physfn);
	adf_devmgr_rm_dev(accel_dev, pf);
पूर्ण

अटल पूर्णांक adf_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा adf_accel_dev *accel_dev;
	काष्ठा adf_accel_dev *pf;
	काष्ठा adf_accel_pci *accel_pci_dev;
	काष्ठा adf_hw_device_data *hw_data;
	अक्षर name[ADF_DEVICE_NAME_LENGTH];
	अचिन्हित पूर्णांक i, bar_nr;
	अचिन्हित दीर्घ bar_mask;
	पूर्णांक ret;

	चयन (ent->device) अणु
	हाल PCI_DEVICE_ID_INTEL_QAT_C3XXX_VF:
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Invalid device 0x%x.\n", ent->device);
		वापस -ENODEV;
	पूर्ण

	accel_dev = kzalloc_node(माप(*accel_dev), GFP_KERNEL,
				 dev_to_node(&pdev->dev));
	अगर (!accel_dev)
		वापस -ENOMEM;

	accel_dev->is_vf = true;
	pf = adf_devmgr_pci_to_accel_dev(pdev->physfn);
	accel_pci_dev = &accel_dev->accel_pci_dev;
	accel_pci_dev->pci_dev = pdev;

	/* Add accel device to accel table */
	अगर (adf_devmgr_add_dev(accel_dev, pf)) अणु
		dev_err(&pdev->dev, "Failed to add new accelerator device.\n");
		kमुक्त(accel_dev);
		वापस -EFAULT;
	पूर्ण
	INIT_LIST_HEAD(&accel_dev->crypto_list);

	accel_dev->owner = THIS_MODULE;
	/* Allocate and configure device configuration काष्ठाure */
	hw_data = kzalloc_node(माप(*hw_data), GFP_KERNEL,
			       dev_to_node(&pdev->dev));
	अगर (!hw_data) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण
	accel_dev->hw_device = hw_data;
	adf_init_hw_data_c3xxxiov(accel_dev->hw_device);

	/* Get Accelerators and Accelerators Engines masks */
	hw_data->accel_mask = hw_data->get_accel_mask(hw_data);
	hw_data->ae_mask = hw_data->get_ae_mask(hw_data);
	accel_pci_dev->sku = hw_data->get_sku(hw_data);

	/* Create dev top level debugfs entry */
	snम_लिखो(name, माप(name), "%s%s_%s", ADF_DEVICE_NAME_PREFIX,
		 hw_data->dev_class->name, pci_name(pdev));

	accel_dev->debugfs_dir = debugfs_create_dir(name, शून्य);

	/* Create device configuration table */
	ret = adf_cfg_dev_add(accel_dev);
	अगर (ret)
		जाओ out_err;

	/* enable PCI device */
	अगर (pci_enable_device(pdev)) अणु
		ret = -EFAULT;
		जाओ out_err;
	पूर्ण

	/* set dma identअगरier */
	अगर (pci_set_dma_mask(pdev, DMA_BIT_MASK(64))) अणु
		अगर ((pci_set_dma_mask(pdev, DMA_BIT_MASK(32)))) अणु
			dev_err(&pdev->dev, "No usable DMA configuration\n");
			ret = -EFAULT;
			जाओ out_err_disable;
		पूर्ण अन्यथा अणु
			pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		पूर्ण

	पूर्ण अन्यथा अणु
		pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	पूर्ण

	अगर (pci_request_regions(pdev, ADF_C3XXXVF_DEVICE_NAME)) अणु
		ret = -EFAULT;
		जाओ out_err_disable;
	पूर्ण

	/* Find and map all the device's BARS */
	i = 0;
	bar_mask = pci_select_bars(pdev, IORESOURCE_MEM);
	क्रम_each_set_bit(bar_nr, &bar_mask, ADF_PCI_MAX_BARS * 2) अणु
		काष्ठा adf_bar *bar = &accel_pci_dev->pci_bars[i++];

		bar->base_addr = pci_resource_start(pdev, bar_nr);
		अगर (!bar->base_addr)
			अवरोध;
		bar->size = pci_resource_len(pdev, bar_nr);
		bar->virt_addr = pci_iomap(accel_pci_dev->pci_dev, bar_nr, 0);
		अगर (!bar->virt_addr) अणु
			dev_err(&pdev->dev, "Failed to map BAR %d\n", bar_nr);
			ret = -EFAULT;
			जाओ out_err_मुक्त_reg;
		पूर्ण
	पूर्ण
	pci_set_master(pdev);
	/* Completion क्रम VF2PF request/response message exchange */
	init_completion(&accel_dev->vf.iov_msg_completion);

	ret = qat_crypto_dev_config(accel_dev);
	अगर (ret)
		जाओ out_err_मुक्त_reg;

	ret = adf_dev_init(accel_dev);
	अगर (ret)
		जाओ out_err_dev_shutकरोwn;

	set_bit(ADF_STATUS_PF_RUNNING, &accel_dev->status);

	ret = adf_dev_start(accel_dev);
	अगर (ret)
		जाओ out_err_dev_stop;

	वापस ret;

out_err_dev_stop:
	adf_dev_stop(accel_dev);
out_err_dev_shutकरोwn:
	adf_dev_shutकरोwn(accel_dev);
out_err_मुक्त_reg:
	pci_release_regions(accel_pci_dev->pci_dev);
out_err_disable:
	pci_disable_device(accel_pci_dev->pci_dev);
out_err:
	adf_cleanup_accel(accel_dev);
	kमुक्त(accel_dev);
	वापस ret;
पूर्ण

अटल व्योम adf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा adf_accel_dev *accel_dev = adf_devmgr_pci_to_accel_dev(pdev);

	अगर (!accel_dev) अणु
		pr_err("QAT: Driver removal failed\n");
		वापस;
	पूर्ण
	adf_dev_stop(accel_dev);
	adf_dev_shutकरोwn(accel_dev);
	adf_cleanup_accel(accel_dev);
	adf_cleanup_pci_dev(accel_dev);
	kमुक्त(accel_dev);
पूर्ण

अटल पूर्णांक __init adfdrv_init(व्योम)
अणु
	request_module("intel_qat");

	अगर (pci_रेजिस्टर_driver(&adf_driver)) अणु
		pr_err("QAT: Driver initialization failed\n");
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास adfdrv_release(व्योम)
अणु
	pci_unरेजिस्टर_driver(&adf_driver);
	adf_clean_vf_map(true);
पूर्ण

module_init(adfdrv_init);
module_निकास(adfdrv_release);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Intel");
MODULE_DESCRIPTION("Intel(R) QuickAssist Technology");
MODULE_VERSION(ADF_DRV_VERSION);
