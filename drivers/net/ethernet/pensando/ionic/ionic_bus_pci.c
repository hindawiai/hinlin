<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/pci.h>

#समावेश "ionic.h"
#समावेश "ionic_bus.h"
#समावेश "ionic_lif.h"
#समावेश "ionic_debugfs.h"

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id ionic_id_table[] = अणु
	अणु PCI_VDEVICE(PENSANDO, PCI_DEVICE_ID_PENSANDO_IONIC_ETH_PF) पूर्ण,
	अणु PCI_VDEVICE(PENSANDO, PCI_DEVICE_ID_PENSANDO_IONIC_ETH_VF) पूर्ण,
	अणु 0, पूर्ण	/* end of table */
पूर्ण;
MODULE_DEVICE_TABLE(pci, ionic_id_table);

पूर्णांक ionic_bus_get_irq(काष्ठा ionic *ionic, अचिन्हित पूर्णांक num)
अणु
	वापस pci_irq_vector(ionic->pdev, num);
पूर्ण

स्थिर अक्षर *ionic_bus_info(काष्ठा ionic *ionic)
अणु
	वापस pci_name(ionic->pdev);
पूर्ण

पूर्णांक ionic_bus_alloc_irq_vectors(काष्ठा ionic *ionic, अचिन्हित पूर्णांक nपूर्णांकrs)
अणु
	वापस pci_alloc_irq_vectors(ionic->pdev, nपूर्णांकrs, nपूर्णांकrs,
				     PCI_IRQ_MSIX);
पूर्ण

व्योम ionic_bus_मुक्त_irq_vectors(काष्ठा ionic *ionic)
अणु
	अगर (!ionic->nपूर्णांकrs)
		वापस;

	pci_मुक्त_irq_vectors(ionic->pdev);
पूर्ण

अटल पूर्णांक ionic_map_bars(काष्ठा ionic *ionic)
अणु
	काष्ठा pci_dev *pdev = ionic->pdev;
	काष्ठा device *dev = ionic->dev;
	काष्ठा ionic_dev_bar *bars;
	अचिन्हित पूर्णांक i, j;

	bars = ionic->bars;
	ionic->num_bars = 0;

	क्रम (i = 0, j = 0; i < IONIC_BARS_MAX; i++) अणु
		अगर (!(pci_resource_flags(pdev, i) & IORESOURCE_MEM))
			जारी;
		bars[j].len = pci_resource_len(pdev, i);

		/* only map the whole bar 0 */
		अगर (j > 0) अणु
			bars[j].vaddr = शून्य;
		पूर्ण अन्यथा अणु
			bars[j].vaddr = pci_iomap(pdev, i, bars[j].len);
			अगर (!bars[j].vaddr) अणु
				dev_err(dev,
					"Cannot memory-map BAR %d, aborting\n",
					i);
				वापस -ENODEV;
			पूर्ण
		पूर्ण

		bars[j].bus_addr = pci_resource_start(pdev, i);
		bars[j].res_index = i;
		ionic->num_bars++;
		j++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ionic_unmap_bars(काष्ठा ionic *ionic)
अणु
	काष्ठा ionic_dev_bar *bars = ionic->bars;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IONIC_BARS_MAX; i++) अणु
		अगर (bars[i].vaddr) अणु
			iounmap(bars[i].vaddr);
			bars[i].bus_addr = 0;
			bars[i].vaddr = शून्य;
			bars[i].len = 0;
		पूर्ण
	पूर्ण
पूर्ण

व्योम __iomem *ionic_bus_map_dbpage(काष्ठा ionic *ionic, पूर्णांक page_num)
अणु
	वापस pci_iomap_range(ionic->pdev,
			       ionic->bars[IONIC_PCI_BAR_DBELL].res_index,
			       (u64)page_num << PAGE_SHIFT, PAGE_SIZE);
पूर्ण

व्योम ionic_bus_unmap_dbpage(काष्ठा ionic *ionic, व्योम __iomem *page)
अणु
	iounmap(page);
पूर्ण

अटल व्योम ionic_vf_dealloc_locked(काष्ठा ionic *ionic)
अणु
	काष्ठा ionic_vf *v;
	dma_addr_t dma = 0;
	पूर्णांक i;

	अगर (!ionic->vfs)
		वापस;

	क्रम (i = ionic->num_vfs - 1; i >= 0; i--) अणु
		v = &ionic->vfs[i];

		अगर (v->stats_pa) अणु
			(व्योम)ionic_set_vf_config(ionic, i,
						  IONIC_VF_ATTR_STATSADDR,
						  (u8 *)&dma);
			dma_unmap_single(ionic->dev, v->stats_pa,
					 माप(v->stats), DMA_FROM_DEVICE);
			v->stats_pa = 0;
		पूर्ण
	पूर्ण

	kमुक्त(ionic->vfs);
	ionic->vfs = शून्य;
	ionic->num_vfs = 0;
पूर्ण

अटल व्योम ionic_vf_dealloc(काष्ठा ionic *ionic)
अणु
	करोwn_ग_लिखो(&ionic->vf_op_lock);
	ionic_vf_dealloc_locked(ionic);
	up_ग_लिखो(&ionic->vf_op_lock);
पूर्ण

अटल पूर्णांक ionic_vf_alloc(काष्ठा ionic *ionic, पूर्णांक num_vfs)
अणु
	काष्ठा ionic_vf *v;
	पूर्णांक err = 0;
	पूर्णांक i;

	करोwn_ग_लिखो(&ionic->vf_op_lock);

	ionic->vfs = kसुस्मृति(num_vfs, माप(काष्ठा ionic_vf), GFP_KERNEL);
	अगर (!ionic->vfs) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_vfs; i++) अणु
		v = &ionic->vfs[i];
		v->stats_pa = dma_map_single(ionic->dev, &v->stats,
					     माप(v->stats), DMA_FROM_DEVICE);
		अगर (dma_mapping_error(ionic->dev, v->stats_pa)) अणु
			v->stats_pa = 0;
			err = -ENODEV;
			जाओ out;
		पूर्ण

		/* ignore failures from older FW, we just won't get stats */
		(व्योम)ionic_set_vf_config(ionic, i, IONIC_VF_ATTR_STATSADDR,
					  (u8 *)&v->stats_pa);
		ionic->num_vfs++;
	पूर्ण

out:
	अगर (err)
		ionic_vf_dealloc_locked(ionic);
	up_ग_लिखो(&ionic->vf_op_lock);
	वापस err;
पूर्ण

अटल पूर्णांक ionic_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	काष्ठा ionic *ionic = pci_get_drvdata(pdev);
	काष्ठा device *dev = ionic->dev;
	पूर्णांक ret = 0;

	अगर (ionic->lअगर &&
	    test_bit(IONIC_LIF_F_FW_RESET, ionic->lअगर->state))
		वापस -EBUSY;

	अगर (num_vfs > 0) अणु
		ret = pci_enable_sriov(pdev, num_vfs);
		अगर (ret) अणु
			dev_err(dev, "Cannot enable SRIOV: %d\n", ret);
			जाओ out;
		पूर्ण

		ret = ionic_vf_alloc(ionic, num_vfs);
		अगर (ret) अणु
			dev_err(dev, "Cannot alloc VFs: %d\n", ret);
			pci_disable_sriov(pdev);
			जाओ out;
		पूर्ण

		ret = num_vfs;
	पूर्ण अन्यथा अणु
		pci_disable_sriov(pdev);
		ionic_vf_dealloc(ionic);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ionic_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ionic *ionic;
	पूर्णांक num_vfs;
	पूर्णांक err;

	ionic = ionic_devlink_alloc(dev);
	अगर (!ionic)
		वापस -ENOMEM;

	ionic->pdev = pdev;
	ionic->dev = dev;
	pci_set_drvdata(pdev, ionic);
	mutex_init(&ionic->dev_cmd_lock);

	/* Query प्रणाली क्रम DMA addressing limitation क्रम the device. */
	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(IONIC_ADDR_LEN));
	अगर (err) अणु
		dev_err(dev, "Unable to obtain 64-bit DMA for consistent allocations, aborting.  err=%d\n",
			err);
		जाओ err_out_clear_drvdata;
	पूर्ण

	ionic_debugfs_add_dev(ionic);

	/* Setup PCI device */
	err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		dev_err(dev, "Cannot enable PCI device: %d, aborting\n", err);
		जाओ err_out_debugfs_del_dev;
	पूर्ण

	err = pci_request_regions(pdev, IONIC_DRV_NAME);
	अगर (err) अणु
		dev_err(dev, "Cannot request PCI regions: %d, aborting\n", err);
		जाओ err_out_pci_disable_device;
	पूर्ण

	pcie_prपूर्णांक_link_status(pdev);

	err = ionic_map_bars(ionic);
	अगर (err)
		जाओ err_out_pci_disable_device;

	/* Configure the device */
	err = ionic_setup(ionic);
	अगर (err) अणु
		dev_err(dev, "Cannot setup device: %d, aborting\n", err);
		जाओ err_out_unmap_bars;
	पूर्ण
	pci_set_master(pdev);

	err = ionic_identअगरy(ionic);
	अगर (err) अणु
		dev_err(dev, "Cannot identify device: %d, aborting\n", err);
		जाओ err_out_tearकरोwn;
	पूर्ण
	ionic_debugfs_add_ident(ionic);

	err = ionic_init(ionic);
	अगर (err) अणु
		dev_err(dev, "Cannot init device: %d, aborting\n", err);
		जाओ err_out_tearकरोwn;
	पूर्ण

	/* Configure the ports */
	err = ionic_port_identअगरy(ionic);
	अगर (err) अणु
		dev_err(dev, "Cannot identify port: %d, aborting\n", err);
		जाओ err_out_reset;
	पूर्ण

	err = ionic_port_init(ionic);
	अगर (err) अणु
		dev_err(dev, "Cannot init port: %d, aborting\n", err);
		जाओ err_out_reset;
	पूर्ण

	/* Allocate and init the LIF */
	err = ionic_lअगर_size(ionic);
	अगर (err) अणु
		dev_err(dev, "Cannot size LIF: %d, aborting\n", err);
		जाओ err_out_port_reset;
	पूर्ण

	err = ionic_lअगर_alloc(ionic);
	अगर (err) अणु
		dev_err(dev, "Cannot allocate LIF: %d, aborting\n", err);
		जाओ err_out_मुक्त_irqs;
	पूर्ण

	err = ionic_lअगर_init(ionic->lअगर);
	अगर (err) अणु
		dev_err(dev, "Cannot init LIF: %d, aborting\n", err);
		जाओ err_out_मुक्त_lअगरs;
	पूर्ण

	init_rwsem(&ionic->vf_op_lock);
	num_vfs = pci_num_vf(pdev);
	अगर (num_vfs) अणु
		dev_info(dev, "%d VFs found already enabled\n", num_vfs);
		err = ionic_vf_alloc(ionic, num_vfs);
		अगर (err)
			dev_err(dev, "Cannot enable existing VFs: %d\n", err);
	पूर्ण

	err = ionic_lअगर_रेजिस्टर(ionic->lअगर);
	अगर (err) अणु
		dev_err(dev, "Cannot register LIF: %d, aborting\n", err);
		जाओ err_out_deinit_lअगरs;
	पूर्ण

	err = ionic_devlink_रेजिस्टर(ionic);
	अगर (err) अणु
		dev_err(dev, "Cannot register devlink: %d\n", err);
		जाओ err_out_deरेजिस्टर_lअगरs;
	पूर्ण

	वापस 0;

err_out_deरेजिस्टर_lअगरs:
	ionic_lअगर_unरेजिस्टर(ionic->lअगर);
err_out_deinit_lअगरs:
	ionic_vf_dealloc(ionic);
	ionic_lअगर_deinit(ionic->lअगर);
err_out_मुक्त_lअगरs:
	ionic_lअगर_मुक्त(ionic->lअगर);
	ionic->lअगर = शून्य;
err_out_मुक्त_irqs:
	ionic_bus_मुक्त_irq_vectors(ionic);
err_out_port_reset:
	ionic_port_reset(ionic);
err_out_reset:
	ionic_reset(ionic);
err_out_tearकरोwn:
	del_समयr_sync(&ionic->watchकरोg_समयr);
	pci_clear_master(pdev);
	/* Don't fail the probe क्रम these errors, keep
	 * the hw पूर्णांकerface around क्रम inspection
	 */
	वापस 0;

err_out_unmap_bars:
	ionic_unmap_bars(ionic);
	pci_release_regions(pdev);
err_out_pci_disable_device:
	pci_disable_device(pdev);
err_out_debugfs_del_dev:
	ionic_debugfs_del_dev(ionic);
err_out_clear_drvdata:
	mutex_destroy(&ionic->dev_cmd_lock);
	ionic_devlink_मुक्त(ionic);

	वापस err;
पूर्ण

अटल व्योम ionic_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ionic *ionic = pci_get_drvdata(pdev);

	अगर (!ionic)
		वापस;

	del_समयr_sync(&ionic->watchकरोg_समयr);

	अगर (ionic->lअगर) अणु
		ionic_devlink_unरेजिस्टर(ionic);
		ionic_lअगर_unरेजिस्टर(ionic->lअगर);
		ionic_lअगर_deinit(ionic->lअगर);
		ionic_lअगर_मुक्त(ionic->lअगर);
		ionic->lअगर = शून्य;
		ionic_bus_मुक्त_irq_vectors(ionic);
	पूर्ण

	ionic_port_reset(ionic);
	ionic_reset(ionic);
	pci_clear_master(pdev);
	ionic_unmap_bars(ionic);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	ionic_debugfs_del_dev(ionic);
	mutex_destroy(&ionic->dev_cmd_lock);
	ionic_devlink_मुक्त(ionic);
पूर्ण

अटल काष्ठा pci_driver ionic_driver = अणु
	.name = IONIC_DRV_NAME,
	.id_table = ionic_id_table,
	.probe = ionic_probe,
	.हटाओ = ionic_हटाओ,
	.sriov_configure = ionic_sriov_configure,
पूर्ण;

पूर्णांक ionic_bus_रेजिस्टर_driver(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&ionic_driver);
पूर्ण

व्योम ionic_bus_unरेजिस्टर_driver(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ionic_driver);
पूर्ण
