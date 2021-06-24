<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/suspend.h>
#समावेश "wil6210.h"
#समावेश <linux/rtnetlink.h>
#समावेश <linux/pm_runसमय.स>

अटल पूर्णांक n_msi = 3;
module_param(n_msi, पूर्णांक, 0444);
MODULE_PARM_DESC(n_msi, " Use MSI interrupt: 0 - use INTx, 1 - single, or 3 - (default) ");

bool fपंचांग_mode;
module_param(fपंचांग_mode, bool, 0444);
MODULE_PARM_DESC(fपंचांग_mode, " Set factory test mode, default - false");

अटल पूर्णांक wil6210_pm_notअगरy(काष्ठा notअगरier_block *notअगरy_block,
			     अचिन्हित दीर्घ mode, व्योम *unused);

अटल
पूर्णांक wil_set_capabilities(काष्ठा wil6210_priv *wil)
अणु
	स्थिर अक्षर *wil_fw_name;
	u32 jtag_id = wil_r(wil, RGF_USER_JTAG_DEV_ID);
	u8 chip_revision = (wil_r(wil, RGF_USER_REVISION_ID) &
			    RGF_USER_REVISION_ID_MASK);
	पूर्णांक platक्रमm_capa;
	काष्ठा fw_map *iccm_section, *sct;

	biपंचांगap_zero(wil->hw_capa, hw_capa_last);
	biपंचांगap_zero(wil->fw_capabilities, WMI_FW_CAPABILITY_MAX);
	biपंचांगap_zero(wil->platक्रमm_capa, WIL_PLATFORM_CAPA_MAX);
	wil->wil_fw_name = fपंचांग_mode ? WIL_FW_NAME_FTM_DEFAULT :
			   WIL_FW_NAME_DEFAULT;
	wil->chip_revision = chip_revision;

	चयन (jtag_id) अणु
	हाल JTAG_DEV_ID_SPARROW:
		स_नकल(fw_mapping, sparrow_fw_mapping,
		       माप(sparrow_fw_mapping));
		चयन (chip_revision) अणु
		हाल REVISION_ID_SPARROW_D0:
			wil->hw_name = "Sparrow D0";
			wil->hw_version = HW_VER_SPARROW_D0;
			wil_fw_name = fपंचांग_mode ? WIL_FW_NAME_FTM_SPARROW_PLUS :
				      WIL_FW_NAME_SPARROW_PLUS;

			अगर (wil_fw_verअगरy_file_exists(wil, wil_fw_name))
				wil->wil_fw_name = wil_fw_name;
			sct = wil_find_fw_mapping("mac_rgf_ext");
			अगर (!sct) अणु
				wil_err(wil, "mac_rgf_ext section not found in fw_mapping\n");
				वापस -EINVAL;
			पूर्ण
			स_नकल(sct, &sparrow_d0_mac_rgf_ext, माप(*sct));
			अवरोध;
		हाल REVISION_ID_SPARROW_B0:
			wil->hw_name = "Sparrow B0";
			wil->hw_version = HW_VER_SPARROW_B0;
			अवरोध;
		शेष:
			wil->hw_name = "Unknown";
			wil->hw_version = HW_VER_UNKNOWN;
			अवरोध;
		पूर्ण
		wil->rgf_fw_निश्चित_code_addr = SPARROW_RGF_FW_ASSERT_CODE;
		wil->rgf_ucode_निश्चित_code_addr = SPARROW_RGF_UCODE_ASSERT_CODE;
		अवरोध;
	हाल JTAG_DEV_ID_TALYN:
		wil->hw_name = "Talyn-MA";
		wil->hw_version = HW_VER_TALYN;
		स_नकल(fw_mapping, talyn_fw_mapping, माप(talyn_fw_mapping));
		wil->rgf_fw_निश्चित_code_addr = TALYN_RGF_FW_ASSERT_CODE;
		wil->rgf_ucode_निश्चित_code_addr = TALYN_RGF_UCODE_ASSERT_CODE;
		अगर (wil_r(wil, RGF_USER_OTP_HW_RD_MACHINE_1) &
		    BIT_NO_FLASH_INDICATION)
			set_bit(hw_capa_no_flash, wil->hw_capa);
		wil_fw_name = fपंचांग_mode ? WIL_FW_NAME_FTM_TALYN :
			      WIL_FW_NAME_TALYN;
		अगर (wil_fw_verअगरy_file_exists(wil, wil_fw_name))
			wil->wil_fw_name = wil_fw_name;
		अवरोध;
	हाल JTAG_DEV_ID_TALYN_MB:
		wil->hw_name = "Talyn-MB";
		wil->hw_version = HW_VER_TALYN_MB;
		स_नकल(fw_mapping, talyn_mb_fw_mapping,
		       माप(talyn_mb_fw_mapping));
		wil->rgf_fw_निश्चित_code_addr = TALYN_RGF_FW_ASSERT_CODE;
		wil->rgf_ucode_निश्चित_code_addr = TALYN_RGF_UCODE_ASSERT_CODE;
		set_bit(hw_capa_no_flash, wil->hw_capa);
		wil->use_enhanced_dma_hw = true;
		wil->use_rx_hw_reordering = true;
		wil->use_compressed_rx_status = true;
		wil_fw_name = fपंचांग_mode ? WIL_FW_NAME_FTM_TALYN :
			      WIL_FW_NAME_TALYN;
		अगर (wil_fw_verअगरy_file_exists(wil, wil_fw_name))
			wil->wil_fw_name = wil_fw_name;
		अवरोध;
	शेष:
		wil_err(wil, "Unknown board hardware, chip_id 0x%08x, chip_revision 0x%08x\n",
			jtag_id, chip_revision);
		wil->hw_name = "Unknown";
		wil->hw_version = HW_VER_UNKNOWN;
		वापस -EINVAL;
	पूर्ण

	wil_init_txrx_ops(wil);

	iccm_section = wil_find_fw_mapping("fw_code");
	अगर (!iccm_section) अणु
		wil_err(wil, "fw_code section not found in fw_mapping\n");
		वापस -EINVAL;
	पूर्ण
	wil->iccm_base = iccm_section->host;

	wil_info(wil, "Board hardware is %s, flash %sexist\n", wil->hw_name,
		 test_bit(hw_capa_no_flash, wil->hw_capa) ? "doesn't " : "");

	/* Get platक्रमm capabilities */
	अगर (wil->platक्रमm_ops.get_capa) अणु
		platक्रमm_capa =
			wil->platक्रमm_ops.get_capa(wil->platक्रमm_handle);
		स_नकल(wil->platक्रमm_capa, &platक्रमm_capa,
		       min(माप(wil->platक्रमm_capa), माप(platक्रमm_capa)));
	पूर्ण

	wil_info(wil, "platform_capa 0x%lx\n", *wil->platक्रमm_capa);

	/* extract FW capabilities from file without loading the FW */
	wil_request_firmware(wil, wil->wil_fw_name, false);
	wil_refresh_fw_capabilities(wil);

	वापस 0;
पूर्ण

व्योम wil_disable_irq(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक irq = wil->pdev->irq;

	disable_irq(irq);
	अगर (wil->n_msi == 3) अणु
		disable_irq(irq + 1);
		disable_irq(irq + 2);
	पूर्ण
पूर्ण

व्योम wil_enable_irq(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक irq = wil->pdev->irq;

	enable_irq(irq);
	अगर (wil->n_msi == 3) अणु
		enable_irq(irq + 1);
		enable_irq(irq + 2);
	पूर्ण
पूर्ण

अटल व्योम wil_हटाओ_all_additional_vअगरs(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil6210_vअगर *vअगर;
	पूर्णांक i;

	क्रम (i = 1; i < GET_MAX_VIFS(wil); i++) अणु
		vअगर = wil->vअगरs[i];
		अगर (vअगर) अणु
			wil_vअगर_prepare_stop(vअगर);
			wil_vअगर_हटाओ(wil, vअगर->mid);
		पूर्ण
	पूर्ण
पूर्ण

/* Bus ops */
अटल पूर्णांक wil_अगर_pcie_enable(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा pci_dev *pdev = wil->pdev;
	पूर्णांक rc;
	/* on platक्रमms with buggy ACPI, pdev->msi_enabled may be set to
	 * allow pci_enable_device to work. This indicates INTx was not routed
	 * and only MSI should be used
	 */
	पूर्णांक msi_only = pdev->msi_enabled;

	wil_dbg_misc(wil, "if_pcie_enable\n");

	pci_set_master(pdev);

	/* how many MSI पूर्णांकerrupts to request? */
	चयन (n_msi) अणु
	हाल 3:
	हाल 1:
		wil_dbg_misc(wil, "Setup %d MSI interrupts\n", n_msi);
		अवरोध;
	हाल 0:
		wil_dbg_misc(wil, "MSI interrupts disabled, use INTx\n");
		अवरोध;
	शेष:
		wil_err(wil, "Invalid n_msi=%d, default to 1\n", n_msi);
		n_msi = 1;
	पूर्ण

	अगर (n_msi == 3 &&
	    pci_alloc_irq_vectors(pdev, n_msi, n_msi, PCI_IRQ_MSI) < n_msi) अणु
		wil_err(wil, "3 MSI mode failed, try 1 MSI\n");
		n_msi = 1;
	पूर्ण

	अगर (n_msi == 1 && pci_enable_msi(pdev)) अणु
		wil_err(wil, "pci_enable_msi failed, use INTx\n");
		n_msi = 0;
	पूर्ण

	wil->n_msi = n_msi;

	अगर (wil->n_msi == 0 && msi_only) अणु
		wil_err(wil, "Interrupt pin not routed, unable to use INTx\n");
		rc = -ENODEV;
		जाओ stop_master;
	पूर्ण

	rc = wil6210_init_irq(wil, pdev->irq);
	अगर (rc)
		जाओ release_vectors;

	/* need reset here to obtain MAC */
	mutex_lock(&wil->mutex);
	rc = wil_reset(wil, false);
	mutex_unlock(&wil->mutex);
	अगर (rc)
		जाओ release_irq;

	वापस 0;

 release_irq:
	wil6210_fini_irq(wil, pdev->irq);
 release_vectors:
	/* safe to call अगर no allocation */
	pci_मुक्त_irq_vectors(pdev);
 stop_master:
	pci_clear_master(pdev);
	वापस rc;
पूर्ण

अटल पूर्णांक wil_अगर_pcie_disable(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा pci_dev *pdev = wil->pdev;

	wil_dbg_misc(wil, "if_pcie_disable\n");

	pci_clear_master(pdev);
	/* disable and release IRQ */
	wil6210_fini_irq(wil, pdev->irq);
	/* safe to call अगर no MSI */
	pci_disable_msi(pdev);
	/* TODO: disable HW */

	वापस 0;
पूर्ण

अटल पूर्णांक wil_platक्रमm_rop_ramdump(व्योम *wil_handle, व्योम *buf, uपूर्णांक32_t size)
अणु
	काष्ठा wil6210_priv *wil = wil_handle;

	अगर (!wil)
		वापस -EINVAL;

	वापस wil_fw_copy_crash_dump(wil, buf, size);
पूर्ण

अटल पूर्णांक wil_platक्रमm_rop_fw_recovery(व्योम *wil_handle)
अणु
	काष्ठा wil6210_priv *wil = wil_handle;

	अगर (!wil)
		वापस -EINVAL;

	wil_fw_error_recovery(wil);

	वापस 0;
पूर्ण

अटल व्योम wil_platक्रमm_ops_uninit(काष्ठा wil6210_priv *wil)
अणु
	अगर (wil->platक्रमm_ops.uninit)
		wil->platक्रमm_ops.uninit(wil->platक्रमm_handle);
	स_रखो(&wil->platक्रमm_ops, 0, माप(wil->platक्रमm_ops));
पूर्ण

अटल पूर्णांक wil_pcie_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा wil6210_priv *wil;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक rc;
	स्थिर काष्ठा wil_platक्रमm_rops rops = अणु
		.ramdump = wil_platक्रमm_rop_ramdump,
		.fw_recovery = wil_platक्रमm_rop_fw_recovery,
	पूर्ण;
	u32 bar_size = pci_resource_len(pdev, 0);
	पूर्णांक dma_addr_size[] = अणु64, 48, 40, 32पूर्ण; /* keep descending order */
	पूर्णांक i, start_idx;

	/* check HW */
	dev_info(&pdev->dev, WIL_NAME
		 " device found [%04x:%04x] (rev %x) bar size 0x%x\n",
		 (पूर्णांक)pdev->venकरोr, (पूर्णांक)pdev->device, (पूर्णांक)pdev->revision,
		 bar_size);

	अगर ((bar_size < WIL6210_MIN_MEM_SIZE) ||
	    (bar_size > WIL6210_MAX_MEM_SIZE)) अणु
		dev_err(&pdev->dev, "Unexpected BAR0 size 0x%x\n",
			bar_size);
		वापस -ENODEV;
	पूर्ण

	wil = wil_अगर_alloc(dev);
	अगर (IS_ERR(wil)) अणु
		rc = (पूर्णांक)PTR_ERR(wil);
		dev_err(dev, "wil_if_alloc failed: %d\n", rc);
		वापस rc;
	पूर्ण

	wil->pdev = pdev;
	pci_set_drvdata(pdev, wil);
	wil->bar_size = bar_size;
	/* rollback to अगर_मुक्त */

	wil->platक्रमm_handle =
		wil_platक्रमm_init(&pdev->dev, &wil->platक्रमm_ops, &rops, wil);
	अगर (!wil->platक्रमm_handle) अणु
		rc = -ENODEV;
		wil_err(wil, "wil_platform_init failed\n");
		जाओ अगर_मुक्त;
	पूर्ण
	/* rollback to err_plat */
	rc = pci_enable_device(pdev);
	अगर (rc && pdev->msi_enabled == 0) अणु
		wil_err(wil,
			"pci_enable_device failed, retry with MSI only\n");
		/* Work around क्रम platक्रमms that can't allocate IRQ:
		 * retry with MSI only
		 */
		pdev->msi_enabled = 1;
		rc = pci_enable_device(pdev);
	पूर्ण
	अगर (rc) अणु
		wil_err(wil,
			"pci_enable_device failed, even with MSI only\n");
		जाओ err_plat;
	पूर्ण
	/* rollback to err_disable_pdev */
	pci_set_घातer_state(pdev, PCI_D0);

	rc = pci_request_region(pdev, 0, WIL_NAME);
	अगर (rc) अणु
		wil_err(wil, "pci_request_region failed\n");
		जाओ err_disable_pdev;
	पूर्ण
	/* rollback to err_release_reg */

	wil->csr = pci_ioremap_bar(pdev, 0);
	अगर (!wil->csr) अणु
		wil_err(wil, "pci_ioremap_bar failed\n");
		rc = -ENODEV;
		जाओ err_release_reg;
	पूर्ण
	/* rollback to err_iounmap */
	wil_info(wil, "CSR at %pR -> 0x%p\n", &pdev->resource[0], wil->csr);

	rc = wil_set_capabilities(wil);
	अगर (rc) अणु
		wil_err(wil, "wil_set_capabilities failed, rc %d\n", rc);
		जाओ err_iounmap;
	पूर्ण

	/* device supports >32bit addresses.
	 * क्रम legacy DMA start from 48 bit.
	 */
	start_idx = wil->use_enhanced_dma_hw ? 0 : 1;

	क्रम (i = start_idx; i < ARRAY_SIZE(dma_addr_size); i++) अणु
		rc = dma_set_mask_and_coherent(dev,
					       DMA_BIT_MASK(dma_addr_size[i]));
		अगर (rc) अणु
			dev_err(dev, "dma_set_mask_and_coherent(%d) failed: %d\n",
				dma_addr_size[i], rc);
			जारी;
		पूर्ण
		dev_info(dev, "using dma mask %d", dma_addr_size[i]);
		wil->dma_addr_size = dma_addr_size[i];
		अवरोध;
	पूर्ण

	अगर (wil->dma_addr_size == 0)
		जाओ err_iounmap;

	wil6210_clear_irq(wil);

	/* FW should उठाओ IRQ when पढ़ोy */
	rc = wil_अगर_pcie_enable(wil);
	अगर (rc) अणु
		wil_err(wil, "Enable device failed\n");
		जाओ err_iounmap;
	पूर्ण
	/* rollback to bus_disable */

	wil_clear_fw_log_addr(wil);
	rc = wil_अगर_add(wil);
	अगर (rc) अणु
		wil_err(wil, "wil_if_add failed: %d\n", rc);
		जाओ bus_disable;
	पूर्ण

	/* in हाल of WMI-only FW, perक्रमm full reset and FW loading */
	अगर (test_bit(WMI_FW_CAPABILITY_WMI_ONLY, wil->fw_capabilities)) अणु
		wil_dbg_misc(wil, "Loading WMI only FW\n");
		mutex_lock(&wil->mutex);
		rc = wil_reset(wil, true);
		mutex_unlock(&wil->mutex);
		अगर (rc) अणु
			wil_err(wil, "failed to load WMI only FW\n");
			/* ignore the error to allow debugging */
		पूर्ण
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PM))
		wil->pm_notअगरy.notअगरier_call = wil6210_pm_notअगरy;

	rc = रेजिस्टर_pm_notअगरier(&wil->pm_notअगरy);
	अगर (rc)
		/* Do not fail the driver initialization, as suspend can
		 * be prevented in a later phase अगर needed
		 */
		wil_err(wil, "register_pm_notifier failed: %d\n", rc);

	wil6210_debugfs_init(wil);

	wil_pm_runसमय_allow(wil);

	वापस 0;

bus_disable:
	wil_अगर_pcie_disable(wil);
err_iounmap:
	pci_iounmap(pdev, wil->csr);
err_release_reg:
	pci_release_region(pdev, 0);
err_disable_pdev:
	pci_disable_device(pdev);
err_plat:
	wil_platक्रमm_ops_uninit(wil);
अगर_मुक्त:
	wil_अगर_मुक्त(wil);

	वापस rc;
पूर्ण

अटल व्योम wil_pcie_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा wil6210_priv *wil = pci_get_drvdata(pdev);
	व्योम __iomem *csr = wil->csr;

	wil_dbg_misc(wil, "pcie_remove\n");

	unरेजिस्टर_pm_notअगरier(&wil->pm_notअगरy);

	wil_pm_runसमय_क्रमbid(wil);

	wil6210_debugfs_हटाओ(wil);
	rtnl_lock();
	wiphy_lock(wil->wiphy);
	wil_p2p_wdev_मुक्त(wil);
	wil_हटाओ_all_additional_vअगरs(wil);
	wiphy_unlock(wil->wiphy);
	rtnl_unlock();
	wil_अगर_हटाओ(wil);
	wil_अगर_pcie_disable(wil);
	pci_iounmap(pdev, csr);
	pci_release_region(pdev, 0);
	pci_disable_device(pdev);
	wil_platक्रमm_ops_uninit(wil);
	wil_अगर_मुक्त(wil);
पूर्ण

अटल स्थिर काष्ठा pci_device_id wil6210_pcie_ids[] = अणु
	अणु PCI_DEVICE(0x1ae9, 0x0310) पूर्ण,
	अणु PCI_DEVICE(0x1ae9, 0x0302) पूर्ण, /* same as above, firmware broken */
	अणु PCI_DEVICE(0x17cb, 0x1201) पूर्ण, /* Talyn */
	अणु /* end: all zeroes */	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, wil6210_pcie_ids);

अटल पूर्णांक wil6210_suspend(काष्ठा device *dev, bool is_runसमय)
अणु
	पूर्णांक rc = 0;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा wil6210_priv *wil = pci_get_drvdata(pdev);
	bool keep_radio_on, active_अगरaces;

	wil_dbg_pm(wil, "suspend: %s\n", is_runसमय ? "runtime" : "system");

	mutex_lock(&wil->vअगर_mutex);
	active_अगरaces = wil_has_active_अगरaces(wil, true, false);
	mutex_unlock(&wil->vअगर_mutex);
	keep_radio_on = active_अगरaces && wil->keep_radio_on_during_sleep;

	rc = wil_can_suspend(wil, is_runसमय);
	अगर (rc)
		जाओ out;

	rc = wil_suspend(wil, is_runसमय, keep_radio_on);
	अगर (!rc) अणु
		/* In हाल radio stays on, platक्रमm device will control
		 * PCIe master
		 */
		अगर (!keep_radio_on) अणु
			/* disable bus mastering */
			pci_clear_master(pdev);
			wil->suspend_stats.r_off.successful_suspends++;
		पूर्ण अन्यथा अणु
			wil->suspend_stats.r_on.successful_suspends++;
		पूर्ण
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल पूर्णांक wil6210_resume(काष्ठा device *dev, bool is_runसमय)
अणु
	पूर्णांक rc = 0;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा wil6210_priv *wil = pci_get_drvdata(pdev);
	bool keep_radio_on, active_अगरaces;

	wil_dbg_pm(wil, "resume: %s\n", is_runसमय ? "runtime" : "system");

	mutex_lock(&wil->vअगर_mutex);
	active_अगरaces = wil_has_active_अगरaces(wil, true, false);
	mutex_unlock(&wil->vअगर_mutex);
	keep_radio_on = active_अगरaces && wil->keep_radio_on_during_sleep;

	/* In हाल radio stays on, platक्रमm device will control
	 * PCIe master
	 */
	अगर (!keep_radio_on)
		/* allow master */
		pci_set_master(pdev);
	rc = wil_resume(wil, is_runसमय, keep_radio_on);
	अगर (rc) अणु
		wil_err(wil, "device failed to resume (%d)\n", rc);
		अगर (!keep_radio_on) अणु
			pci_clear_master(pdev);
			wil->suspend_stats.r_off.failed_resumes++;
		पूर्ण अन्यथा अणु
			wil->suspend_stats.r_on.failed_resumes++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (keep_radio_on)
			wil->suspend_stats.r_on.successful_resumes++;
		अन्यथा
			wil->suspend_stats.r_off.successful_resumes++;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक wil6210_pm_notअगरy(काष्ठा notअगरier_block *notअगरy_block,
			     अचिन्हित दीर्घ mode, व्योम *unused)
अणु
	काष्ठा wil6210_priv *wil = container_of(
		notअगरy_block, काष्ठा wil6210_priv, pm_notअगरy);
	पूर्णांक rc = 0;
	क्रमागत wil_platक्रमm_event evt;

	wil_dbg_pm(wil, "pm_notify: mode (%ld)\n", mode);

	चयन (mode) अणु
	हाल PM_HIBERNATION_PREPARE:
	हाल PM_SUSPEND_PREPARE:
	हाल PM_RESTORE_PREPARE:
		rc = wil_can_suspend(wil, false);
		अगर (rc)
			अवरोध;
		evt = WIL_PLATFORM_EVT_PRE_SUSPEND;
		अगर (wil->platक्रमm_ops.notअगरy)
			rc = wil->platक्रमm_ops.notअगरy(wil->platक्रमm_handle,
						      evt);
		अवरोध;
	हाल PM_POST_SUSPEND:
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_RESTORE:
		evt = WIL_PLATFORM_EVT_POST_SUSPEND;
		अगर (wil->platक्रमm_ops.notअगरy)
			rc = wil->platक्रमm_ops.notअगरy(wil->platक्रमm_handle,
						      evt);
		अवरोध;
	शेष:
		wil_dbg_pm(wil, "unhandled notify mode %ld\n", mode);
		अवरोध;
	पूर्ण

	wil_dbg_pm(wil, "notification mode %ld: rc (%d)\n", mode, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक __maybe_unused wil6210_pm_suspend(काष्ठा device *dev)
अणु
	वापस wil6210_suspend(dev, false);
पूर्ण

अटल पूर्णांक __maybe_unused wil6210_pm_resume(काष्ठा device *dev)
अणु
	वापस wil6210_resume(dev, false);
पूर्ण

अटल पूर्णांक __maybe_unused wil6210_pm_runसमय_idle(काष्ठा device *dev)
अणु
	काष्ठा wil6210_priv *wil = dev_get_drvdata(dev);

	wil_dbg_pm(wil, "Runtime idle\n");

	वापस wil_can_suspend(wil, true);
पूर्ण

अटल पूर्णांक __maybe_unused wil6210_pm_runसमय_resume(काष्ठा device *dev)
अणु
	वापस wil6210_resume(dev, true);
पूर्ण

अटल पूर्णांक __maybe_unused wil6210_pm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा wil6210_priv *wil = dev_get_drvdata(dev);

	अगर (test_bit(wil_status_suspended, wil->status)) अणु
		wil_dbg_pm(wil, "trying to suspend while suspended\n");
		वापस 1;
	पूर्ण

	वापस wil6210_suspend(dev, true);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops wil6210_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(wil6210_pm_suspend, wil6210_pm_resume)
	SET_RUNTIME_PM_OPS(wil6210_pm_runसमय_suspend,
			   wil6210_pm_runसमय_resume,
			   wil6210_pm_runसमय_idle)
पूर्ण;

अटल काष्ठा pci_driver wil6210_driver = अणु
	.probe		= wil_pcie_probe,
	.हटाओ		= wil_pcie_हटाओ,
	.id_table	= wil6210_pcie_ids,
	.name		= WIL_NAME,
	.driver		= अणु
		.pm = &wil6210_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init wil6210_driver_init(व्योम)
अणु
	पूर्णांक rc;

	rc = wil_platक्रमm_modinit();
	अगर (rc)
		वापस rc;

	rc = pci_रेजिस्टर_driver(&wil6210_driver);
	अगर (rc)
		wil_platक्रमm_modनिकास();
	वापस rc;
पूर्ण
module_init(wil6210_driver_init);

अटल व्योम __निकास wil6210_driver_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&wil6210_driver);
	wil_platक्रमm_modनिकास();
पूर्ण
module_निकास(wil6210_driver_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Qualcomm Atheros <wil6210@qca.qualcomm.com>");
MODULE_DESCRIPTION("Driver for 60g WiFi WIL6210 card");
