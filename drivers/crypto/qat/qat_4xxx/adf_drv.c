<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2020 Intel Corporation */
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <adf_accel_devices.h>
#समावेश <adf_cfg.h>
#समावेश <adf_common_drv.h>

#समावेश "adf_4xxx_hw_data.h"
#समावेश "qat_crypto.h"
#समावेश "adf_transport_access_macros.h"

अटल स्थिर काष्ठा pci_device_id adf_pci_tbl[] = अणु
	अणु PCI_VDEVICE(INTEL, ADF_4XXX_PCI_DEVICE_ID), पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, adf_pci_tbl);

अटल व्योम adf_cleanup_accel(काष्ठा adf_accel_dev *accel_dev)
अणु
	अगर (accel_dev->hw_device) अणु
		adf_clean_hw_data_4xxx(accel_dev->hw_device);
		accel_dev->hw_device = शून्य;
	पूर्ण
	adf_cfg_dev_हटाओ(accel_dev);
	debugfs_हटाओ(accel_dev->debugfs_dir);
	adf_devmgr_rm_dev(accel_dev, शून्य);
पूर्ण

अटल पूर्णांक adf_crypto_dev_config(काष्ठा adf_accel_dev *accel_dev)
अणु
	अक्षर key[ADF_CFG_MAX_KEY_LEN_IN_BYTES];
	पूर्णांक banks = GET_MAX_BANKS(accel_dev);
	पूर्णांक cpus = num_online_cpus();
	अचिन्हित दीर्घ bank, val;
	पूर्णांक instances;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (adf_hw_dev_has_crypto(accel_dev))
		instances = min(cpus, banks / 2);
	अन्यथा
		instances = 0;

	ret = adf_cfg_section_add(accel_dev, ADF_KERNEL_SEC);
	अगर (ret)
		जाओ err;

	ret = adf_cfg_section_add(accel_dev, "Accelerator0");
	अगर (ret)
		जाओ err;

	क्रम (i = 0; i < instances; i++) अणु
		val = i;
		bank = i * 2;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_ASYM_BANK_NUM, i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &bank, ADF_DEC);
		अगर (ret)
			जाओ err;

		bank += 1;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_SYM_BANK_NUM, i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &bank, ADF_DEC);
		अगर (ret)
			जाओ err;

		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_ETRMGR_CORE_AFFINITY,
			 i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_ASYM_SIZE, i);
		val = 128;
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		val = 512;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_SYM_SIZE, i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		val = 0;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_ASYM_TX, i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		val = 0;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_SYM_TX, i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		val = 1;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_ASYM_RX, i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		val = 1;
		snम_लिखो(key, माप(key), ADF_CY "%d" ADF_RING_SYM_RX, i);
		ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;

		val = ADF_COALESCING_DEF_TIME;
		snम_लिखो(key, माप(key), ADF_ETRMGR_COALESCE_TIMER_FORMAT, i);
		ret = adf_cfg_add_key_value_param(accel_dev, "Accelerator0",
						  key, &val, ADF_DEC);
		अगर (ret)
			जाओ err;
	पूर्ण

	val = i;
	ret = adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC, ADF_NUM_CY,
					  &val, ADF_DEC);
	अगर (ret)
		जाओ err;

	set_bit(ADF_STATUS_CONFIGURED, &accel_dev->status);
	वापस 0;
err:
	dev_err(&GET_DEV(accel_dev), "Failed to start QAT accel dev\n");
	वापस ret;
पूर्ण

अटल पूर्णांक adf_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा adf_accel_dev *accel_dev;
	काष्ठा adf_accel_pci *accel_pci_dev;
	काष्ठा adf_hw_device_data *hw_data;
	अक्षर name[ADF_DEVICE_NAME_LENGTH];
	अचिन्हित पूर्णांक i, bar_nr;
	अचिन्हित दीर्घ bar_mask;
	काष्ठा adf_bar *bar;
	पूर्णांक ret;

	अगर (num_possible_nodes() > 1 && dev_to_node(&pdev->dev) < 0) अणु
		/*
		 * If the accelerator is connected to a node with no memory
		 * there is no poपूर्णांक in using the accelerator since the remote
		 * memory transaction will be very slow.
		 */
		dev_err(&pdev->dev, "Invalid NUMA configuration.\n");
		वापस -EINVAL;
	पूर्ण

	accel_dev = devm_kzalloc(&pdev->dev, माप(*accel_dev), GFP_KERNEL);
	अगर (!accel_dev)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&accel_dev->crypto_list);
	accel_pci_dev = &accel_dev->accel_pci_dev;
	accel_pci_dev->pci_dev = pdev;

	/*
	 * Add accel device to accel table
	 * This should be called beक्रमe adf_cleanup_accel is called
	 */
	अगर (adf_devmgr_add_dev(accel_dev, शून्य)) अणु
		dev_err(&pdev->dev, "Failed to add new accelerator device.\n");
		वापस -EFAULT;
	पूर्ण

	accel_dev->owner = THIS_MODULE;
	/* Allocate and initialise device hardware meta-data काष्ठाure */
	hw_data = devm_kzalloc(&pdev->dev, माप(*hw_data), GFP_KERNEL);
	अगर (!hw_data) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	accel_dev->hw_device = hw_data;
	adf_init_hw_data_4xxx(accel_dev->hw_device);

	pci_पढ़ो_config_byte(pdev, PCI_REVISION_ID, &accel_pci_dev->revid);
	pci_पढ़ो_config_dword(pdev, ADF_4XXX_FUSECTL4_OFFSET, &hw_data->fuses);

	/* Get Accelerators and Accelerators Engines masks */
	hw_data->accel_mask = hw_data->get_accel_mask(hw_data);
	hw_data->ae_mask = hw_data->get_ae_mask(hw_data);
	accel_pci_dev->sku = hw_data->get_sku(hw_data);
	/* If the device has no acceleration engines then ignore it */
	अगर (!hw_data->accel_mask || !hw_data->ae_mask ||
	    (~hw_data->ae_mask & 0x01)) अणु
		dev_err(&pdev->dev, "No acceleration units found.\n");
		ret = -EFAULT;
		जाओ out_err;
	पूर्ण

	/* Create dev top level debugfs entry */
	snम_लिखो(name, माप(name), "%s%s_%s", ADF_DEVICE_NAME_PREFIX,
		 hw_data->dev_class->name, pci_name(pdev));

	accel_dev->debugfs_dir = debugfs_create_dir(name, शून्य);

	/* Create device configuration table */
	ret = adf_cfg_dev_add(accel_dev);
	अगर (ret)
		जाओ out_err;

	/* Enable PCI device */
	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't enable PCI device.\n");
		जाओ out_err;
	पूर्ण

	/* Set DMA identअगरier */
	अगर (pci_set_dma_mask(pdev, DMA_BIT_MASK(64))) अणु
		अगर ((pci_set_dma_mask(pdev, DMA_BIT_MASK(32)))) अणु
			dev_err(&pdev->dev, "No usable DMA configuration.\n");
			ret = -EFAULT;
			जाओ out_err;
		पूर्ण अन्यथा अणु
			pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		पूर्ण
	पूर्ण अन्यथा अणु
		pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	पूर्ण

	/* Get accelerator capabilities mask */
	hw_data->accel_capabilities_mask = hw_data->get_accel_cap(accel_dev);

	/* Find and map all the device's BARS */
	bar_mask = pci_select_bars(pdev, IORESOURCE_MEM) & ADF_4XXX_BAR_MASK;

	ret = pcim_iomap_regions_request_all(pdev, bar_mask, pci_name(pdev));
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to map pci regions.\n");
		जाओ out_err;
	पूर्ण

	i = 0;
	क्रम_each_set_bit(bar_nr, &bar_mask, PCI_STD_NUM_BARS) अणु
		bar = &accel_pci_dev->pci_bars[i++];
		bar->virt_addr = pcim_iomap_table(pdev)[bar_nr];
	पूर्ण

	pci_set_master(pdev);

	अगर (adf_enable_aer(accel_dev)) अणु
		dev_err(&pdev->dev, "Failed to enable aer.\n");
		ret = -EFAULT;
		जाओ out_err;
	पूर्ण

	अगर (pci_save_state(pdev)) अणु
		dev_err(&pdev->dev, "Failed to save pci state.\n");
		ret = -ENOMEM;
		जाओ out_err_disable_aer;
	पूर्ण

	ret = adf_crypto_dev_config(accel_dev);
	अगर (ret)
		जाओ out_err_disable_aer;

	ret = adf_dev_init(accel_dev);
	अगर (ret)
		जाओ out_err_dev_shutकरोwn;

	ret = adf_dev_start(accel_dev);
	अगर (ret)
		जाओ out_err_dev_stop;

	वापस ret;

out_err_dev_stop:
	adf_dev_stop(accel_dev);
out_err_dev_shutकरोwn:
	adf_dev_shutकरोwn(accel_dev);
out_err_disable_aer:
	adf_disable_aer(accel_dev);
out_err:
	adf_cleanup_accel(accel_dev);
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
	adf_disable_aer(accel_dev);
	adf_cleanup_accel(accel_dev);
पूर्ण

अटल काष्ठा pci_driver adf_driver = अणु
	.id_table = adf_pci_tbl,
	.name = ADF_4XXX_DEVICE_NAME,
	.probe = adf_probe,
	.हटाओ = adf_हटाओ,
	.sriov_configure = adf_sriov_configure,
पूर्ण;

module_pci_driver(adf_driver);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Intel");
MODULE_FIRMWARE(ADF_4XXX_FW);
MODULE_FIRMWARE(ADF_4XXX_MMP);
MODULE_DESCRIPTION("Intel(R) QuickAssist Technology");
MODULE_VERSION(ADF_DRV_VERSION);
MODULE_SOFTDEP("pre: crypto-intel_qat");
