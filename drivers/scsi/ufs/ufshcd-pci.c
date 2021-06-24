<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Universal Flash Storage Host controller PCI glue driver
 *
 * This code is based on drivers/scsi/ufs/ufshcd-pci.c
 * Copyright (C) 2011-2013 Samsung India Software Operations
 *
 * Authors:
 *	Santosh Yaraganavi <santosh.sy@samsung.com>
 *	Vinayak Holikatti <h.vinayak@samsung.com>
 */

#समावेश "ufshcd.h"
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_qos.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/uuid.h>
#समावेश <linux/acpi.h>
#समावेश <linux/gpio/consumer.h>

काष्ठा ufs_host अणु
	व्योम (*late_init)(काष्ठा ufs_hba *hba);
पूर्ण;

क्रमागत अणु
	INTEL_DSM_FNS		=  0,
	INTEL_DSM_RESET		=  1,
पूर्ण;

काष्ठा पूर्णांकel_host अणु
	काष्ठा ufs_host ufs_host;
	u32		dsm_fns;
	u32		active_ltr;
	u32		idle_ltr;
	काष्ठा dentry	*debugfs_root;
	काष्ठा gpio_desc *reset_gpio;
पूर्ण;

अटल स्थिर guid_t पूर्णांकel_dsm_guid =
	GUID_INIT(0x1A4832A0, 0x7D03, 0x43CA,
		  0xB0, 0x20, 0xF6, 0xDC, 0xD1, 0x2A, 0x19, 0x50);

अटल पूर्णांक __पूर्णांकel_dsm(काष्ठा पूर्णांकel_host *पूर्णांकel_host, काष्ठा device *dev,
		       अचिन्हित पूर्णांक fn, u32 *result)
अणु
	जोड़ acpi_object *obj;
	पूर्णांक err = 0;
	माप_प्रकार len;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(dev), &पूर्णांकel_dsm_guid, 0, fn, शून्य);
	अगर (!obj)
		वापस -EOPNOTSUPP;

	अगर (obj->type != ACPI_TYPE_BUFFER || obj->buffer.length < 1) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	len = min_t(माप_प्रकार, obj->buffer.length, 4);

	*result = 0;
	स_नकल(result, obj->buffer.poपूर्णांकer, len);
out:
	ACPI_FREE(obj);

	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_dsm(काष्ठा पूर्णांकel_host *पूर्णांकel_host, काष्ठा device *dev,
		     अचिन्हित पूर्णांक fn, u32 *result)
अणु
	अगर (fn > 31 || !(पूर्णांकel_host->dsm_fns & (1 << fn)))
		वापस -EOPNOTSUPP;

	वापस __पूर्णांकel_dsm(पूर्णांकel_host, dev, fn, result);
पूर्ण

अटल व्योम पूर्णांकel_dsm_init(काष्ठा पूर्णांकel_host *पूर्णांकel_host, काष्ठा device *dev)
अणु
	पूर्णांक err;

	err = __पूर्णांकel_dsm(पूर्णांकel_host, dev, INTEL_DSM_FNS, &पूर्णांकel_host->dsm_fns);
	dev_dbg(dev, "DSM fns %#x, error %d\n", पूर्णांकel_host->dsm_fns, err);
पूर्ण

अटल पूर्णांक ufs_पूर्णांकel_hce_enable_notअगरy(काष्ठा ufs_hba *hba,
				       क्रमागत ufs_notअगरy_change_status status)
अणु
	/* Cannot enable ICE until after HC enable */
	अगर (status == POST_CHANGE && hba->caps & UFSHCD_CAP_CRYPTO) अणु
		u32 hce = ufshcd_पढ़ोl(hba, REG_CONTROLLER_ENABLE);

		hce |= CRYPTO_GENERAL_ENABLE;
		ufshcd_ग_लिखोl(hba, hce, REG_CONTROLLER_ENABLE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ufs_पूर्णांकel_disable_lcc(काष्ठा ufs_hba *hba)
अणु
	u32 attr = UIC_ARG_MIB(PA_LOCAL_TX_LCC_ENABLE);
	u32 lcc_enable = 0;

	ufshcd_dme_get(hba, attr, &lcc_enable);
	अगर (lcc_enable)
		ufshcd_disable_host_tx_lcc(hba);

	वापस 0;
पूर्ण

अटल पूर्णांक ufs_पूर्णांकel_link_startup_notअगरy(काष्ठा ufs_hba *hba,
					 क्रमागत ufs_notअगरy_change_status status)
अणु
	पूर्णांक err = 0;

	चयन (status) अणु
	हाल PRE_CHANGE:
		err = ufs_पूर्णांकel_disable_lcc(hba);
		अवरोध;
	हाल POST_CHANGE:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

#घोषणा INTEL_ACTIVELTR		0x804
#घोषणा INTEL_IDLELTR		0x808

#घोषणा INTEL_LTR_REQ		BIT(15)
#घोषणा INTEL_LTR_SCALE_MASK	GENMASK(11, 10)
#घोषणा INTEL_LTR_SCALE_1US	(2 << 10)
#घोषणा INTEL_LTR_SCALE_32US	(3 << 10)
#घोषणा INTEL_LTR_VALUE_MASK	GENMASK(9, 0)

अटल व्योम पूर्णांकel_cache_ltr(काष्ठा ufs_hba *hba)
अणु
	काष्ठा पूर्णांकel_host *host = ufshcd_get_variant(hba);

	host->active_ltr = पढ़ोl(hba->mmio_base + INTEL_ACTIVELTR);
	host->idle_ltr = पढ़ोl(hba->mmio_base + INTEL_IDLELTR);
पूर्ण

अटल व्योम पूर्णांकel_ltr_set(काष्ठा device *dev, s32 val)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);
	काष्ठा पूर्णांकel_host *host = ufshcd_get_variant(hba);
	u32 ltr;

	pm_runसमय_get_sync(dev);

	/*
	 * Program latency tolerance (LTR) accordingly what has been asked
	 * by the PM QoS layer or disable it in हाल we were passed
	 * negative value or PM_QOS_LATENCY_ANY.
	 */
	ltr = पढ़ोl(hba->mmio_base + INTEL_ACTIVELTR);

	अगर (val == PM_QOS_LATENCY_ANY || val < 0) अणु
		ltr &= ~INTEL_LTR_REQ;
	पूर्ण अन्यथा अणु
		ltr |= INTEL_LTR_REQ;
		ltr &= ~INTEL_LTR_SCALE_MASK;
		ltr &= ~INTEL_LTR_VALUE_MASK;

		अगर (val > INTEL_LTR_VALUE_MASK) अणु
			val >>= 5;
			अगर (val > INTEL_LTR_VALUE_MASK)
				val = INTEL_LTR_VALUE_MASK;
			ltr |= INTEL_LTR_SCALE_32US | val;
		पूर्ण अन्यथा अणु
			ltr |= INTEL_LTR_SCALE_1US | val;
		पूर्ण
	पूर्ण

	अगर (ltr == host->active_ltr)
		जाओ out;

	ग_लिखोl(ltr, hba->mmio_base + INTEL_ACTIVELTR);
	ग_लिखोl(ltr, hba->mmio_base + INTEL_IDLELTR);

	/* Cache the values पूर्णांकo पूर्णांकel_host काष्ठाure */
	पूर्णांकel_cache_ltr(hba);
out:
	pm_runसमय_put(dev);
पूर्ण

अटल व्योम पूर्णांकel_ltr_expose(काष्ठा device *dev)
अणु
	dev->घातer.set_latency_tolerance = पूर्णांकel_ltr_set;
	dev_pm_qos_expose_latency_tolerance(dev);
पूर्ण

अटल व्योम पूर्णांकel_ltr_hide(काष्ठा device *dev)
अणु
	dev_pm_qos_hide_latency_tolerance(dev);
	dev->घातer.set_latency_tolerance = शून्य;
पूर्ण

अटल व्योम पूर्णांकel_add_debugfs(काष्ठा ufs_hba *hba)
अणु
	काष्ठा dentry *dir = debugfs_create_dir(dev_name(hba->dev), शून्य);
	काष्ठा पूर्णांकel_host *host = ufshcd_get_variant(hba);

	पूर्णांकel_cache_ltr(hba);

	host->debugfs_root = dir;
	debugfs_create_x32("active_ltr", 0444, dir, &host->active_ltr);
	debugfs_create_x32("idle_ltr", 0444, dir, &host->idle_ltr);
पूर्ण

अटल व्योम पूर्णांकel_हटाओ_debugfs(काष्ठा ufs_hba *hba)
अणु
	काष्ठा पूर्णांकel_host *host = ufshcd_get_variant(hba);

	debugfs_हटाओ_recursive(host->debugfs_root);
पूर्ण

अटल पूर्णांक ufs_पूर्णांकel_device_reset(काष्ठा ufs_hba *hba)
अणु
	काष्ठा पूर्णांकel_host *host = ufshcd_get_variant(hba);

	अगर (host->dsm_fns & INTEL_DSM_RESET) अणु
		u32 result = 0;
		पूर्णांक err;

		err = पूर्णांकel_dsm(host, hba->dev, INTEL_DSM_RESET, &result);
		अगर (!err && !result)
			err = -EIO;
		अगर (err)
			dev_err(hba->dev, "%s: DSM error %d result %u\n",
				__func__, err, result);
		वापस err;
	पूर्ण

	अगर (!host->reset_gpio)
		वापस -EOPNOTSUPP;

	gpiod_set_value_cansleep(host->reset_gpio, 1);
	usleep_range(10, 15);

	gpiod_set_value_cansleep(host->reset_gpio, 0);
	usleep_range(10, 15);

	वापस 0;
पूर्ण

अटल काष्ठा gpio_desc *ufs_पूर्णांकel_get_reset_gpio(काष्ठा device *dev)
अणु
	/* GPIO in _DSD has active low setting */
	वापस devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
पूर्ण

अटल पूर्णांक ufs_पूर्णांकel_common_init(काष्ठा ufs_hba *hba)
अणु
	काष्ठा पूर्णांकel_host *host;

	hba->caps |= UFSHCD_CAP_RPM_AUTOSUSPEND;

	host = devm_kzalloc(hba->dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;
	ufshcd_set_variant(hba, host);
	पूर्णांकel_dsm_init(host, hba->dev);
	अगर (host->dsm_fns & INTEL_DSM_RESET) अणु
		अगर (hba->vops->device_reset)
			hba->caps |= UFSHCD_CAP_DEEPSLEEP;
	पूर्ण अन्यथा अणु
		अगर (hba->vops->device_reset)
			host->reset_gpio = ufs_पूर्णांकel_get_reset_gpio(hba->dev);
		अगर (IS_ERR(host->reset_gpio)) अणु
			dev_err(hba->dev, "%s: failed to get reset GPIO, error %ld\n",
				__func__, PTR_ERR(host->reset_gpio));
			host->reset_gpio = शून्य;
		पूर्ण
		अगर (host->reset_gpio) अणु
			gpiod_set_value_cansleep(host->reset_gpio, 0);
			hba->caps |= UFSHCD_CAP_DEEPSLEEP;
		पूर्ण
	पूर्ण
	पूर्णांकel_ltr_expose(hba->dev);
	पूर्णांकel_add_debugfs(hba);
	वापस 0;
पूर्ण

अटल व्योम ufs_पूर्णांकel_common_निकास(काष्ठा ufs_hba *hba)
अणु
	पूर्णांकel_हटाओ_debugfs(hba);
	पूर्णांकel_ltr_hide(hba->dev);
पूर्ण

अटल पूर्णांक ufs_पूर्णांकel_resume(काष्ठा ufs_hba *hba, क्रमागत ufs_pm_op op)
अणु
	/*
	 * To support S4 (suspend-to-disk) with spm_lvl other than 5, the base
	 * address रेजिस्टरs must be restored because the restore kernel can
	 * have used dअगरferent addresses.
	 */
	ufshcd_ग_लिखोl(hba, lower_32_bits(hba->utrdl_dma_addr),
		      REG_UTP_TRANSFER_REQ_LIST_BASE_L);
	ufshcd_ग_लिखोl(hba, upper_32_bits(hba->utrdl_dma_addr),
		      REG_UTP_TRANSFER_REQ_LIST_BASE_H);
	ufshcd_ग_लिखोl(hba, lower_32_bits(hba->uपंचांगrdl_dma_addr),
		      REG_UTP_TASK_REQ_LIST_BASE_L);
	ufshcd_ग_लिखोl(hba, upper_32_bits(hba->uपंचांगrdl_dma_addr),
		      REG_UTP_TASK_REQ_LIST_BASE_H);

	अगर (ufshcd_is_link_hibern8(hba)) अणु
		पूर्णांक ret = ufshcd_uic_hibern8_निकास(hba);

		अगर (!ret) अणु
			ufshcd_set_link_active(hba);
		पूर्ण अन्यथा अणु
			dev_err(hba->dev, "%s: hibern8 exit failed %d\n",
				__func__, ret);
			/*
			 * Force reset and restore. Any other actions can lead
			 * to an unrecoverable state.
			 */
			ufshcd_set_link_off(hba);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ufs_पूर्णांकel_ehl_init(काष्ठा ufs_hba *hba)
अणु
	hba->quirks |= UFSHCD_QUIRK_BROKEN_AUTO_HIBERN8;
	वापस ufs_पूर्णांकel_common_init(hba);
पूर्ण

अटल व्योम ufs_पूर्णांकel_lkf_late_init(काष्ठा ufs_hba *hba)
अणु
	/* LKF always needs a full reset, so set PM accordingly */
	अगर (hba->caps & UFSHCD_CAP_DEEPSLEEP) अणु
		hba->spm_lvl = UFS_PM_LVL_6;
		hba->rpm_lvl = UFS_PM_LVL_6;
	पूर्ण अन्यथा अणु
		hba->spm_lvl = UFS_PM_LVL_5;
		hba->rpm_lvl = UFS_PM_LVL_5;
	पूर्ण
पूर्ण

अटल पूर्णांक ufs_पूर्णांकel_lkf_init(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_host *ufs_host;
	पूर्णांक err;

	hba->quirks |= UFSHCD_QUIRK_BROKEN_AUTO_HIBERN8;
	hba->caps |= UFSHCD_CAP_CRYPTO;
	err = ufs_पूर्णांकel_common_init(hba);
	ufs_host = ufshcd_get_variant(hba);
	ufs_host->late_init = ufs_पूर्णांकel_lkf_late_init;
	वापस err;
पूर्ण

अटल काष्ठा ufs_hba_variant_ops ufs_पूर्णांकel_cnl_hba_vops = अणु
	.name                   = "intel-pci",
	.init			= ufs_पूर्णांकel_common_init,
	.निकास			= ufs_पूर्णांकel_common_निकास,
	.link_startup_notअगरy	= ufs_पूर्णांकel_link_startup_notअगरy,
	.resume			= ufs_पूर्णांकel_resume,
पूर्ण;

अटल काष्ठा ufs_hba_variant_ops ufs_पूर्णांकel_ehl_hba_vops = अणु
	.name                   = "intel-pci",
	.init			= ufs_पूर्णांकel_ehl_init,
	.निकास			= ufs_पूर्णांकel_common_निकास,
	.link_startup_notअगरy	= ufs_पूर्णांकel_link_startup_notअगरy,
	.resume			= ufs_पूर्णांकel_resume,
पूर्ण;

अटल काष्ठा ufs_hba_variant_ops ufs_पूर्णांकel_lkf_hba_vops = अणु
	.name                   = "intel-pci",
	.init			= ufs_पूर्णांकel_lkf_init,
	.निकास			= ufs_पूर्णांकel_common_निकास,
	.hce_enable_notअगरy	= ufs_पूर्णांकel_hce_enable_notअगरy,
	.link_startup_notअगरy	= ufs_पूर्णांकel_link_startup_notअगरy,
	.resume			= ufs_पूर्णांकel_resume,
	.device_reset		= ufs_पूर्णांकel_device_reset,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
/**
 * ufshcd_pci_suspend - suspend घातer management function
 * @dev: poपूर्णांकer to PCI device handle
 *
 * Returns 0 अगर successful
 * Returns non-zero otherwise
 */
अटल पूर्णांक ufshcd_pci_suspend(काष्ठा device *dev)
अणु
	वापस ufshcd_प्रणाली_suspend(dev_get_drvdata(dev));
पूर्ण

/**
 * ufshcd_pci_resume - resume घातer management function
 * @dev: poपूर्णांकer to PCI device handle
 *
 * Returns 0 अगर successful
 * Returns non-zero otherwise
 */
अटल पूर्णांक ufshcd_pci_resume(काष्ठा device *dev)
अणु
	वापस ufshcd_प्रणाली_resume(dev_get_drvdata(dev));
पूर्ण

/**
 * ufshcd_pci_घातeroff - suspend-to-disk घातeroff function
 * @dev: poपूर्णांकer to PCI device handle
 *
 * Returns 0 अगर successful
 * Returns non-zero otherwise
 */
अटल पूर्णांक ufshcd_pci_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा ufs_hba *hba = dev_get_drvdata(dev);
	पूर्णांक spm_lvl = hba->spm_lvl;
	पूर्णांक ret;

	/*
	 * For घातeroff we need to set the UFS device to PowerDown mode.
	 * Force spm_lvl to ensure that.
	 */
	hba->spm_lvl = 5;
	ret = ufshcd_प्रणाली_suspend(hba);
	hba->spm_lvl = spm_lvl;
	वापस ret;
पूर्ण

#पूर्ण_अगर /* !CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ufshcd_pci_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस ufshcd_runसमय_suspend(dev_get_drvdata(dev));
पूर्ण
अटल पूर्णांक ufshcd_pci_runसमय_resume(काष्ठा device *dev)
अणु
	वापस ufshcd_runसमय_resume(dev_get_drvdata(dev));
पूर्ण
अटल पूर्णांक ufshcd_pci_runसमय_idle(काष्ठा device *dev)
अणु
	वापस ufshcd_runसमय_idle(dev_get_drvdata(dev));
पूर्ण
#पूर्ण_अगर /* !CONFIG_PM */

/**
 * ufshcd_pci_shutकरोwn - मुख्य function to put the controller in reset state
 * @pdev: poपूर्णांकer to PCI device handle
 */
अटल व्योम ufshcd_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	ufshcd_shutकरोwn((काष्ठा ufs_hba *)pci_get_drvdata(pdev));
पूर्ण

/**
 * ufshcd_pci_हटाओ - de-allocate PCI/SCSI host and host memory space
 *		data काष्ठाure memory
 * @pdev: poपूर्णांकer to PCI handle
 */
अटल व्योम ufshcd_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ufs_hba *hba = pci_get_drvdata(pdev);

	pm_runसमय_क्रमbid(&pdev->dev);
	pm_runसमय_get_noresume(&pdev->dev);
	ufshcd_हटाओ(hba);
	ufshcd_dealloc_host(hba);
पूर्ण

/**
 * ufshcd_pci_probe - probe routine of the driver
 * @pdev: poपूर्णांकer to PCI device handle
 * @id: PCI device id
 *
 * Returns 0 on success, non-zero value on failure
 */
अटल पूर्णांक
ufshcd_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ufs_host *ufs_host;
	काष्ठा ufs_hba *hba;
	व्योम __iomem *mmio_base;
	पूर्णांक err;

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "pcim_enable_device failed\n");
		वापस err;
	पूर्ण

	pci_set_master(pdev);

	err = pcim_iomap_regions(pdev, 1 << 0, UFSHCD);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "request and iomap failed\n");
		वापस err;
	पूर्ण

	mmio_base = pcim_iomap_table(pdev)[0];

	err = ufshcd_alloc_host(&pdev->dev, &hba);
	अगर (err) अणु
		dev_err(&pdev->dev, "Allocation failed\n");
		वापस err;
	पूर्ण

	pci_set_drvdata(pdev, hba);

	hba->vops = (काष्ठा ufs_hba_variant_ops *)id->driver_data;

	err = ufshcd_init(hba, mmio_base, pdev->irq);
	अगर (err) अणु
		dev_err(&pdev->dev, "Initialization failed\n");
		ufshcd_dealloc_host(hba);
		वापस err;
	पूर्ण

	ufs_host = ufshcd_get_variant(hba);
	अगर (ufs_host && ufs_host->late_init)
		ufs_host->late_init(hba);

	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_allow(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ufshcd_pci_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ufshcd_pci_suspend,
	.resume		= ufshcd_pci_resume,
	.मुक्तze		= ufshcd_pci_suspend,
	.thaw		= ufshcd_pci_resume,
	.घातeroff	= ufshcd_pci_घातeroff,
	.restore	= ufshcd_pci_resume,
#पूर्ण_अगर
	SET_RUNTIME_PM_OPS(ufshcd_pci_runसमय_suspend,
			   ufshcd_pci_runसमय_resume,
			   ufshcd_pci_runसमय_idle)
पूर्ण;

अटल स्थिर काष्ठा pci_device_id ufshcd_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_SAMSUNG, 0xC00C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9DFA), (kernel_uदीर्घ_t)&ufs_पूर्णांकel_cnl_hba_vops पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4B41), (kernel_uदीर्घ_t)&ufs_पूर्णांकel_ehl_hba_vops पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4B43), (kernel_uदीर्घ_t)&ufs_पूर्णांकel_ehl_hba_vops पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x98FA), (kernel_uदीर्घ_t)&ufs_पूर्णांकel_lkf_hba_vops पूर्ण,
	अणु पूर्ण	/* terminate list */
पूर्ण;

MODULE_DEVICE_TABLE(pci, ufshcd_pci_tbl);

अटल काष्ठा pci_driver ufshcd_pci_driver = अणु
	.name = UFSHCD,
	.id_table = ufshcd_pci_tbl,
	.probe = ufshcd_pci_probe,
	.हटाओ = ufshcd_pci_हटाओ,
	.shutकरोwn = ufshcd_pci_shutकरोwn,
	.driver = अणु
		.pm = &ufshcd_pci_pm_ops
	पूर्ण,
पूर्ण;

module_pci_driver(ufshcd_pci_driver);

MODULE_AUTHOR("Santosh Yaragnavi <santosh.sy@samsung.com>");
MODULE_AUTHOR("Vinayak Holikatti <h.vinayak@samsung.com>");
MODULE_DESCRIPTION("UFS host controller PCI glue driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(UFSHCD_DRIVER_VERSION);
