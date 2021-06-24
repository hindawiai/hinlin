<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTX CPT driver
 *
 * Copyright (C) 2019 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश "otx_cpt_common.h"
#समावेश "otx_cptpf.h"

#घोषणा DRV_NAME	"octeontx-cpt"
#घोषणा DRV_VERSION	"1.0"

अटल व्योम otx_cpt_disable_mbox_पूर्णांकerrupts(काष्ठा otx_cpt_device *cpt)
अणु
	/* Disable mbox(0) पूर्णांकerrupts क्रम all VFs */
	ग_लिखोq(~0ull, cpt->reg_base + OTX_CPT_PF_MBOX_ENA_W1CX(0));
पूर्ण

अटल व्योम otx_cpt_enable_mbox_पूर्णांकerrupts(काष्ठा otx_cpt_device *cpt)
अणु
	/* Enable mbox(0) पूर्णांकerrupts क्रम all VFs */
	ग_लिखोq(~0ull, cpt->reg_base + OTX_CPT_PF_MBOX_ENA_W1SX(0));
पूर्ण

अटल irqवापस_t otx_cpt_mbx0_पूर्णांकr_handler(पूर्णांक __always_unused irq,
					     व्योम *cpt)
अणु
	otx_cpt_mbox_पूर्णांकr_handler(cpt, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम otx_cpt_reset(काष्ठा otx_cpt_device *cpt)
अणु
	ग_लिखोq(1, cpt->reg_base + OTX_CPT_PF_RESET);
पूर्ण

अटल व्योम otx_cpt_find_max_enabled_cores(काष्ठा otx_cpt_device *cpt)
अणु
	जोड़ otx_cptx_pf_स्थिरants pf_cnsts = अणु0पूर्ण;

	pf_cnsts.u = पढ़ोq(cpt->reg_base + OTX_CPT_PF_CONSTANTS);
	cpt->eng_grps.avail.max_se_cnt = pf_cnsts.s.se;
	cpt->eng_grps.avail.max_ae_cnt = pf_cnsts.s.ae;
पूर्ण

अटल u32 otx_cpt_check_bist_status(काष्ठा otx_cpt_device *cpt)
अणु
	जोड़ otx_cptx_pf_bist_status bist_sts = अणु0पूर्ण;

	bist_sts.u = पढ़ोq(cpt->reg_base + OTX_CPT_PF_BIST_STATUS);
	वापस bist_sts.u;
पूर्ण

अटल u64 otx_cpt_check_exe_bist_status(काष्ठा otx_cpt_device *cpt)
अणु
	जोड़ otx_cptx_pf_exe_bist_status bist_sts = अणु0पूर्ण;

	bist_sts.u = पढ़ोq(cpt->reg_base + OTX_CPT_PF_EXE_BIST_STATUS);
	वापस bist_sts.u;
पूर्ण

अटल पूर्णांक otx_cpt_device_init(काष्ठा otx_cpt_device *cpt)
अणु
	काष्ठा device *dev = &cpt->pdev->dev;
	u16 sdevid;
	u64 bist;

	/* Reset the PF when probed first */
	otx_cpt_reset(cpt);
	mdelay(100);

	pci_पढ़ो_config_word(cpt->pdev, PCI_SUBSYSTEM_ID, &sdevid);

	/* Check BIST status */
	bist = (u64)otx_cpt_check_bist_status(cpt);
	अगर (bist) अणु
		dev_err(dev, "RAM BIST failed with code 0x%llx\n", bist);
		वापस -ENODEV;
	पूर्ण

	bist = otx_cpt_check_exe_bist_status(cpt);
	अगर (bist) अणु
		dev_err(dev, "Engine BIST failed with code 0x%llx\n", bist);
		वापस -ENODEV;
	पूर्ण

	/* Get max enabled cores */
	otx_cpt_find_max_enabled_cores(cpt);

	अगर ((sdevid == OTX_CPT_PCI_PF_SUBSYS_ID) &&
	    (cpt->eng_grps.avail.max_se_cnt == 0)) अणु
		cpt->pf_type = OTX_CPT_AE;
	पूर्ण अन्यथा अगर ((sdevid == OTX_CPT_PCI_PF_SUBSYS_ID) &&
		   (cpt->eng_grps.avail.max_ae_cnt == 0)) अणु
		cpt->pf_type = OTX_CPT_SE;
	पूर्ण

	/* Get max VQs/VFs supported by the device */
	cpt->max_vfs = pci_sriov_get_totalvfs(cpt->pdev);

	/* Disable all cores */
	otx_cpt_disable_all_cores(cpt);

	वापस 0;
पूर्ण

अटल पूर्णांक otx_cpt_रेजिस्टर_पूर्णांकerrupts(काष्ठा otx_cpt_device *cpt)
अणु
	काष्ठा device *dev = &cpt->pdev->dev;
	u32 mbox_पूर्णांक_idx = OTX_CPT_PF_MBOX_INT;
	u32 num_vec = OTX_CPT_PF_MSIX_VECTORS;
	पूर्णांक ret;

	/* Enable MSI-X */
	ret = pci_alloc_irq_vectors(cpt->pdev, num_vec, num_vec, PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		dev_err(&cpt->pdev->dev,
			"Request for #%d msix vectors failed\n",
			num_vec);
		वापस ret;
	पूर्ण

	/* Register mailbox पूर्णांकerrupt handlers */
	ret = request_irq(pci_irq_vector(cpt->pdev,
				OTX_CPT_PF_INT_VEC_E_MBOXX(mbox_पूर्णांक_idx, 0)),
				otx_cpt_mbx0_पूर्णांकr_handler, 0, "CPT Mbox0", cpt);
	अगर (ret) अणु
		dev_err(dev, "Request irq failed\n");
		pci_मुक्त_irq_vectors(cpt->pdev);
		वापस ret;
	पूर्ण
	/* Enable mailbox पूर्णांकerrupt */
	otx_cpt_enable_mbox_पूर्णांकerrupts(cpt);
	वापस 0;
पूर्ण

अटल व्योम otx_cpt_unरेजिस्टर_पूर्णांकerrupts(काष्ठा otx_cpt_device *cpt)
अणु
	u32 mbox_पूर्णांक_idx = OTX_CPT_PF_MBOX_INT;

	otx_cpt_disable_mbox_पूर्णांकerrupts(cpt);
	मुक्त_irq(pci_irq_vector(cpt->pdev,
				OTX_CPT_PF_INT_VEC_E_MBOXX(mbox_पूर्णांक_idx, 0)),
				cpt);
	pci_मुक्त_irq_vectors(cpt->pdev);
पूर्ण


अटल पूर्णांक otx_cpt_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक numvfs)
अणु
	काष्ठा otx_cpt_device *cpt = pci_get_drvdata(pdev);
	पूर्णांक ret = 0;

	अगर (numvfs > cpt->max_vfs)
		numvfs = cpt->max_vfs;

	अगर (numvfs > 0) अणु
		ret = otx_cpt_try_create_शेष_eng_grps(cpt->pdev,
							  &cpt->eng_grps,
							  cpt->pf_type);
		अगर (ret)
			वापस ret;

		cpt->vfs_enabled = numvfs;
		ret = pci_enable_sriov(pdev, numvfs);
		अगर (ret) अणु
			cpt->vfs_enabled = 0;
			वापस ret;
		पूर्ण
		otx_cpt_set_eng_grps_is_rकरोnly(&cpt->eng_grps, true);
		try_module_get(THIS_MODULE);
		ret = numvfs;
	पूर्ण अन्यथा अणु
		pci_disable_sriov(pdev);
		otx_cpt_set_eng_grps_is_rकरोnly(&cpt->eng_grps, false);
		module_put(THIS_MODULE);
		cpt->vfs_enabled = 0;
	पूर्ण
	dev_notice(&cpt->pdev->dev, "VFs enabled: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक otx_cpt_probe(काष्ठा pci_dev *pdev,
			 स्थिर काष्ठा pci_device_id __always_unused *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा otx_cpt_device *cpt;
	पूर्णांक err;

	cpt = devm_kzalloc(dev, माप(*cpt), GFP_KERNEL);
	अगर (!cpt)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, cpt);
	cpt->pdev = pdev;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device\n");
		जाओ err_clear_drvdata;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		जाओ err_disable_device;
	पूर्ण

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(48));
	अगर (err) अणु
		dev_err(dev, "Unable to get usable 48-bit DMA configuration\n");
		जाओ err_release_regions;
	पूर्ण

	/* MAP PF's configuration रेजिस्टरs */
	cpt->reg_base = pci_iomap(pdev, OTX_CPT_PF_PCI_CFG_BAR, 0);
	अगर (!cpt->reg_base) अणु
		dev_err(dev, "Cannot map config register space, aborting\n");
		err = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण

	/* CPT device HW initialization */
	err = otx_cpt_device_init(cpt);
	अगर (err)
		जाओ err_unmap_region;

	/* Register पूर्णांकerrupts */
	err = otx_cpt_रेजिस्टर_पूर्णांकerrupts(cpt);
	अगर (err)
		जाओ err_unmap_region;

	/* Initialize engine groups */
	err = otx_cpt_init_eng_grps(pdev, &cpt->eng_grps, cpt->pf_type);
	अगर (err)
		जाओ err_unरेजिस्टर_पूर्णांकerrupts;

	वापस 0;

err_unरेजिस्टर_पूर्णांकerrupts:
	otx_cpt_unरेजिस्टर_पूर्णांकerrupts(cpt);
err_unmap_region:
	pci_iounmap(pdev, cpt->reg_base);
err_release_regions:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
err_clear_drvdata:
	pci_set_drvdata(pdev, शून्य);

	वापस err;
पूर्ण

अटल व्योम otx_cpt_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा otx_cpt_device *cpt = pci_get_drvdata(pdev);

	अगर (!cpt)
		वापस;

	/* Disable VFs */
	pci_disable_sriov(pdev);
	/* Cleanup engine groups */
	otx_cpt_cleanup_eng_grps(pdev, &cpt->eng_grps);
	/* Disable CPT PF पूर्णांकerrupts */
	otx_cpt_unरेजिस्टर_पूर्णांकerrupts(cpt);
	/* Disengage SE and AE cores from all groups */
	otx_cpt_disable_all_cores(cpt);
	pci_iounmap(pdev, cpt->reg_base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id otx_cpt_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, OTX_CPT_PCI_PF_DEVICE_ID) पूर्ण,
	अणु 0, पूर्ण  /* end of table */
पूर्ण;

अटल काष्ठा pci_driver otx_cpt_pci_driver = अणु
	.name = DRV_NAME,
	.id_table = otx_cpt_id_table,
	.probe = otx_cpt_probe,
	.हटाओ = otx_cpt_हटाओ,
	.sriov_configure = otx_cpt_sriov_configure
पूर्ण;

module_pci_driver(otx_cpt_pci_driver);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_DESCRIPTION("Marvell OcteonTX CPT Physical Function Driver");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRV_VERSION);
MODULE_DEVICE_TABLE(pci, otx_cpt_id_table);
