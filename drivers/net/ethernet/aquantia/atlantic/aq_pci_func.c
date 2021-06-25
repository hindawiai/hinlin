<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_pci_func.c: Definition of PCI functions. */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>

#समावेश "aq_main.h"
#समावेश "aq_nic.h"
#समावेश "aq_vec.h"
#समावेश "aq_hw.h"
#समावेश "aq_pci_func.h"
#समावेश "hw_atl/hw_atl_a0.h"
#समावेश "hw_atl/hw_atl_b0.h"
#समावेश "hw_atl2/hw_atl2.h"
#समावेश "aq_filters.h"
#समावेश "aq_drvinfo.h"
#समावेश "aq_macsec.h"

अटल स्थिर काष्ठा pci_device_id aq_pci_tbl[] = अणु
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_0001), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_D100), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_D107), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_D108), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_D109), पूर्ण,

	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC100), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC107), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC108), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC109), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC111), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC112), पूर्ण,

	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC100S), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC107S), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC108S), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC109S), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC111S), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC112S), पूर्ण,

	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC113DEV), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC113CS), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC114CS), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC113), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC113C), पूर्ण,
	अणु PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC115C), पूर्ण,

	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा aq_board_revision_s hw_atl_boards[] = अणु
	अणु AQ_DEVICE_ID_0001,	AQ_HWREV_1,	&hw_atl_ops_a0, &hw_atl_a0_caps_aqc107, पूर्ण,
	अणु AQ_DEVICE_ID_D100,	AQ_HWREV_1,	&hw_atl_ops_a0, &hw_atl_a0_caps_aqc100, पूर्ण,
	अणु AQ_DEVICE_ID_D107,	AQ_HWREV_1,	&hw_atl_ops_a0, &hw_atl_a0_caps_aqc107, पूर्ण,
	अणु AQ_DEVICE_ID_D108,	AQ_HWREV_1,	&hw_atl_ops_a0, &hw_atl_a0_caps_aqc108, पूर्ण,
	अणु AQ_DEVICE_ID_D109,	AQ_HWREV_1,	&hw_atl_ops_a0, &hw_atl_a0_caps_aqc109, पूर्ण,

	अणु AQ_DEVICE_ID_0001,	AQ_HWREV_2,	&hw_atl_ops_b0, &hw_atl_b0_caps_aqc107, पूर्ण,
	अणु AQ_DEVICE_ID_D100,	AQ_HWREV_2,	&hw_atl_ops_b0, &hw_atl_b0_caps_aqc100, पूर्ण,
	अणु AQ_DEVICE_ID_D107,	AQ_HWREV_2,	&hw_atl_ops_b0, &hw_atl_b0_caps_aqc107, पूर्ण,
	अणु AQ_DEVICE_ID_D108,	AQ_HWREV_2,	&hw_atl_ops_b0, &hw_atl_b0_caps_aqc108, पूर्ण,
	अणु AQ_DEVICE_ID_D109,	AQ_HWREV_2,	&hw_atl_ops_b0, &hw_atl_b0_caps_aqc109, पूर्ण,

	अणु AQ_DEVICE_ID_AQC100,	AQ_HWREV_ANY,	&hw_atl_ops_b1, &hw_atl_b0_caps_aqc100, पूर्ण,
	अणु AQ_DEVICE_ID_AQC107,	AQ_HWREV_ANY,	&hw_atl_ops_b1, &hw_atl_b0_caps_aqc107, पूर्ण,
	अणु AQ_DEVICE_ID_AQC108,	AQ_HWREV_ANY,	&hw_atl_ops_b1, &hw_atl_b0_caps_aqc108, पूर्ण,
	अणु AQ_DEVICE_ID_AQC109,	AQ_HWREV_ANY,	&hw_atl_ops_b1, &hw_atl_b0_caps_aqc109, पूर्ण,
	अणु AQ_DEVICE_ID_AQC111,	AQ_HWREV_ANY,	&hw_atl_ops_b1, &hw_atl_b0_caps_aqc111, पूर्ण,
	अणु AQ_DEVICE_ID_AQC112,	AQ_HWREV_ANY,	&hw_atl_ops_b1, &hw_atl_b0_caps_aqc112, पूर्ण,

	अणु AQ_DEVICE_ID_AQC100S,	AQ_HWREV_ANY,	&hw_atl_ops_b1, &hw_atl_b0_caps_aqc100s, पूर्ण,
	अणु AQ_DEVICE_ID_AQC107S,	AQ_HWREV_ANY,	&hw_atl_ops_b1, &hw_atl_b0_caps_aqc107s, पूर्ण,
	अणु AQ_DEVICE_ID_AQC108S,	AQ_HWREV_ANY,	&hw_atl_ops_b1, &hw_atl_b0_caps_aqc108s, पूर्ण,
	अणु AQ_DEVICE_ID_AQC109S,	AQ_HWREV_ANY,	&hw_atl_ops_b1, &hw_atl_b0_caps_aqc109s, पूर्ण,
	अणु AQ_DEVICE_ID_AQC111S,	AQ_HWREV_ANY,	&hw_atl_ops_b1, &hw_atl_b0_caps_aqc111s, पूर्ण,
	अणु AQ_DEVICE_ID_AQC112S,	AQ_HWREV_ANY,	&hw_atl_ops_b1, &hw_atl_b0_caps_aqc112s, पूर्ण,

	अणु AQ_DEVICE_ID_AQC113DEV,	AQ_HWREV_ANY,	&hw_atl2_ops, &hw_atl2_caps_aqc113, पूर्ण,
	अणु AQ_DEVICE_ID_AQC113,		AQ_HWREV_ANY,	&hw_atl2_ops, &hw_atl2_caps_aqc113, पूर्ण,
	अणु AQ_DEVICE_ID_AQC113CS,	AQ_HWREV_ANY,	&hw_atl2_ops, &hw_atl2_caps_aqc113, पूर्ण,
	अणु AQ_DEVICE_ID_AQC114CS,	AQ_HWREV_ANY,	&hw_atl2_ops, &hw_atl2_caps_aqc113, पूर्ण,
	अणु AQ_DEVICE_ID_AQC113C,		AQ_HWREV_ANY,	&hw_atl2_ops, &hw_atl2_caps_aqc113, पूर्ण,
	अणु AQ_DEVICE_ID_AQC115C,		AQ_HWREV_ANY,	&hw_atl2_ops, &hw_atl2_caps_aqc113, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, aq_pci_tbl);

अटल पूर्णांक aq_pci_probe_get_hw_by_id(काष्ठा pci_dev *pdev,
				     स्थिर काष्ठा aq_hw_ops **ops,
				     स्थिर काष्ठा aq_hw_caps_s **caps)
अणु
	पूर्णांक i;

	अगर (pdev->venकरोr != PCI_VENDOR_ID_AQUANTIA)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(hw_atl_boards); i++) अणु
		अगर (hw_atl_boards[i].devid == pdev->device &&
		    (hw_atl_boards[i].revision == AQ_HWREV_ANY ||
		     hw_atl_boards[i].revision == pdev->revision)) अणु
			*ops = hw_atl_boards[i].ops;
			*caps = hw_atl_boards[i].caps;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(hw_atl_boards))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक aq_pci_func_init(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक err;

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (!err)
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (err) अणु
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (!err)
			err = pci_set_consistent_dma_mask(pdev,
							  DMA_BIT_MASK(32));
	पूर्ण
	अगर (err != 0) अणु
		err = -ENOSR;
		जाओ err_निकास;
	पूर्ण

	err = pci_request_regions(pdev, AQ_CFG_DRV_NAME "_mmio");
	अगर (err < 0)
		जाओ err_निकास;

	pci_set_master(pdev);

	वापस 0;

err_निकास:
	वापस err;
पूर्ण

पूर्णांक aq_pci_func_alloc_irq(काष्ठा aq_nic_s *self, अचिन्हित पूर्णांक i,
			  अक्षर *name, irq_handler_t irq_handler,
			  व्योम *irq_arg, cpumask_t *affinity_mask)
अणु
	काष्ठा pci_dev *pdev = self->pdev;
	पूर्णांक err;

	अगर (pdev->msix_enabled || pdev->msi_enabled)
		err = request_irq(pci_irq_vector(pdev, i), irq_handler, 0,
				  name, irq_arg);
	अन्यथा
		err = request_irq(pci_irq_vector(pdev, i), aq_vec_isr_legacy,
				  IRQF_SHARED, name, irq_arg);

	अगर (err >= 0) अणु
		self->msix_entry_mask |= (1 << i);

		अगर (pdev->msix_enabled && affinity_mask)
			irq_set_affinity_hपूर्णांक(pci_irq_vector(pdev, i),
					      affinity_mask);
	पूर्ण

	वापस err;
पूर्ण

व्योम aq_pci_func_मुक्त_irqs(काष्ठा aq_nic_s *self)
अणु
	काष्ठा pci_dev *pdev = self->pdev;
	अचिन्हित पूर्णांक i;
	व्योम *irq_data;

	क्रम (i = 32U; i--;) अणु
		अगर (!((1U << i) & self->msix_entry_mask))
			जारी;
		अगर (self->aq_nic_cfg.link_irq_vec &&
		    i == self->aq_nic_cfg.link_irq_vec)
			irq_data = self;
		अन्यथा अगर (i < AQ_CFG_VECS_MAX)
			irq_data = self->aq_vec[i];
		अन्यथा
			जारी;

		अगर (pdev->msix_enabled)
			irq_set_affinity_hपूर्णांक(pci_irq_vector(pdev, i), शून्य);
		मुक्त_irq(pci_irq_vector(pdev, i), irq_data);
		self->msix_entry_mask &= ~(1U << i);
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक aq_pci_func_get_irq_type(काष्ठा aq_nic_s *self)
अणु
	अगर (self->pdev->msix_enabled)
		वापस AQ_HW_IRQ_MSIX;
	अगर (self->pdev->msi_enabled)
		वापस AQ_HW_IRQ_MSI;

	वापस AQ_HW_IRQ_LEGACY;
पूर्ण

अटल व्योम aq_pci_मुक्त_irq_vectors(काष्ठा aq_nic_s *self)
अणु
	pci_मुक्त_irq_vectors(self->pdev);
पूर्ण

अटल पूर्णांक aq_pci_probe(काष्ठा pci_dev *pdev,
			स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा net_device *ndev;
	resource_माप_प्रकार mmio_pa;
	काष्ठा aq_nic_s *self;
	u32 numvecs;
	u32 bar;
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	err = aq_pci_func_init(pdev);
	अगर (err)
		जाओ err_pci_func;

	ndev = aq_ndev_alloc();
	अगर (!ndev) अणु
		err = -ENOMEM;
		जाओ err_ndev;
	पूर्ण

	self = netdev_priv(ndev);
	self->pdev = pdev;
	SET_NETDEV_DEV(ndev, &pdev->dev);
	pci_set_drvdata(pdev, self);

	mutex_init(&self->fwreq_mutex);

	err = aq_pci_probe_get_hw_by_id(pdev, &self->aq_hw_ops,
					&aq_nic_get_cfg(self)->aq_hw_caps);
	अगर (err)
		जाओ err_ioremap;

	self->aq_hw = kzalloc(माप(*self->aq_hw), GFP_KERNEL);
	अगर (!self->aq_hw) अणु
		err = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण
	self->aq_hw->aq_nic_cfg = aq_nic_get_cfg(self);
	अगर (self->aq_hw->aq_nic_cfg->aq_hw_caps->priv_data_len) अणु
		पूर्णांक len = self->aq_hw->aq_nic_cfg->aq_hw_caps->priv_data_len;

		self->aq_hw->priv = kzalloc(len, GFP_KERNEL);
		अगर (!self->aq_hw->priv) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_aq_hw;
		पूर्ण
	पूर्ण

	क्रम (bar = 0; bar < 4; ++bar) अणु
		अगर (IORESOURCE_MEM & pci_resource_flags(pdev, bar)) अणु
			resource_माप_प्रकार reg_sz;

			mmio_pa = pci_resource_start(pdev, bar);
			अगर (mmio_pa == 0U) अणु
				err = -EIO;
				जाओ err_मुक्त_aq_hw_priv;
			पूर्ण

			reg_sz = pci_resource_len(pdev, bar);
			अगर ((reg_sz <= 24 /*ATL_REGS_SIZE*/)) अणु
				err = -EIO;
				जाओ err_मुक्त_aq_hw_priv;
			पूर्ण

			self->aq_hw->mmio = ioremap(mmio_pa, reg_sz);
			अगर (!self->aq_hw->mmio) अणु
				err = -EIO;
				जाओ err_मुक्त_aq_hw_priv;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (bar == 4) अणु
		err = -EIO;
		जाओ err_मुक्त_aq_hw_priv;
	पूर्ण

	numvecs = min((u8)AQ_CFG_VECS_DEF,
		      aq_nic_get_cfg(self)->aq_hw_caps->msix_irqs);
	numvecs = min(numvecs, num_online_cpus());
	/* Request IRQ vector क्रम PTP */
	numvecs += 1;

	numvecs += AQ_HW_SERVICE_IRQS;
	/*enable पूर्णांकerrupts */
#अगर !AQ_CFG_FORCE_LEGACY_INT
	err = pci_alloc_irq_vectors(self->pdev, 1, numvecs,
				    PCI_IRQ_MSIX | PCI_IRQ_MSI |
				    PCI_IRQ_LEGACY);

	अगर (err < 0)
		जाओ err_hwinit;
	numvecs = err;
#पूर्ण_अगर
	self->irqvecs = numvecs;

	/* net device init */
	aq_nic_cfg_start(self);

	aq_nic_ndev_init(self);

	err = aq_nic_ndev_रेजिस्टर(self);
	अगर (err < 0)
		जाओ err_रेजिस्टर;

	aq_drvinfo_init(ndev);

	वापस 0;

err_रेजिस्टर:
	aq_nic_मुक्त_vectors(self);
	aq_pci_मुक्त_irq_vectors(self);
err_hwinit:
	iounmap(self->aq_hw->mmio);
err_मुक्त_aq_hw_priv:
	kमुक्त(self->aq_hw->priv);
err_मुक्त_aq_hw:
	kमुक्त(self->aq_hw);
err_ioremap:
	मुक्त_netdev(ndev);
err_ndev:
	pci_release_regions(pdev);
err_pci_func:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल व्योम aq_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा aq_nic_s *self = pci_get_drvdata(pdev);

	अगर (self->ndev) अणु
		aq_clear_rxnfc_all_rules(self);
		अगर (self->ndev->reg_state == NETREG_REGISTERED)
			unरेजिस्टर_netdev(self->ndev);

#अगर IS_ENABLED(CONFIG_MACSEC)
		aq_macsec_मुक्त(self);
#पूर्ण_अगर
		aq_nic_मुक्त_vectors(self);
		aq_pci_मुक्त_irq_vectors(self);
		iounmap(self->aq_hw->mmio);
		kमुक्त(self->aq_hw->priv);
		kमुक्त(self->aq_hw);
		pci_release_regions(pdev);
		मुक्त_netdev(self->ndev);
	पूर्ण

	pci_disable_device(pdev);
पूर्ण

अटल व्योम aq_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा aq_nic_s *self = pci_get_drvdata(pdev);

	aq_nic_shutकरोwn(self);

	pci_disable_device(pdev);

	अगर (प्रणाली_state == SYSTEM_POWER_OFF) अणु
		pci_wake_from_d3(pdev, false);
		pci_set_घातer_state(pdev, PCI_D3hot);
	पूर्ण
पूर्ण

अटल पूर्णांक aq_suspend_common(काष्ठा device *dev, bool deep)
अणु
	काष्ठा aq_nic_s *nic = pci_get_drvdata(to_pci_dev(dev));

	rtnl_lock();

	nic->घातer_state = AQ_HW_POWER_STATE_D3;
	netअगर_device_detach(nic->ndev);
	netअगर_tx_stop_all_queues(nic->ndev);

	अगर (netअगर_running(nic->ndev))
		aq_nic_stop(nic);

	अगर (deep) अणु
		aq_nic_deinit(nic, !nic->aq_hw->aq_nic_cfg->wol);
		aq_nic_set_घातer(nic);
	पूर्ण

	rtnl_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक atl_resume_common(काष्ठा device *dev, bool deep)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा aq_nic_s *nic;
	पूर्णांक ret = 0;

	nic = pci_get_drvdata(pdev);

	rtnl_lock();

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);

	अगर (deep) अणु
		ret = aq_nic_init(nic);
		अगर (ret)
			जाओ err_निकास;
	पूर्ण

	अगर (netअगर_running(nic->ndev)) अणु
		ret = aq_nic_start(nic);
		अगर (ret)
			जाओ err_निकास;
	पूर्ण

	netअगर_device_attach(nic->ndev);
	netअगर_tx_start_all_queues(nic->ndev);

err_निकास:
	अगर (ret < 0)
		aq_nic_deinit(nic, true);

	rtnl_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक aq_pm_मुक्तze(काष्ठा device *dev)
अणु
	वापस aq_suspend_common(dev, false);
पूर्ण

अटल पूर्णांक aq_pm_suspend_घातeroff(काष्ठा device *dev)
अणु
	वापस aq_suspend_common(dev, true);
पूर्ण

अटल पूर्णांक aq_pm_thaw(काष्ठा device *dev)
अणु
	वापस atl_resume_common(dev, false);
पूर्ण

अटल पूर्णांक aq_pm_resume_restore(काष्ठा device *dev)
अणु
	वापस atl_resume_common(dev, true);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops aq_pm_ops = अणु
	.suspend = aq_pm_suspend_घातeroff,
	.घातeroff = aq_pm_suspend_घातeroff,
	.मुक्तze = aq_pm_मुक्तze,
	.resume = aq_pm_resume_restore,
	.restore = aq_pm_resume_restore,
	.thaw = aq_pm_thaw,
पूर्ण;

अटल काष्ठा pci_driver aq_pci_ops = अणु
	.name = AQ_CFG_DRV_NAME,
	.id_table = aq_pci_tbl,
	.probe = aq_pci_probe,
	.हटाओ = aq_pci_हटाओ,
	.shutकरोwn = aq_pci_shutकरोwn,
#अगर_घोषित CONFIG_PM
	.driver.pm = &aq_pm_ops,
#पूर्ण_अगर
पूर्ण;

पूर्णांक aq_pci_func_रेजिस्टर_driver(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&aq_pci_ops);
पूर्ण

व्योम aq_pci_func_unरेजिस्टर_driver(व्योम)
अणु
	pci_unरेजिस्टर_driver(&aq_pci_ops);
पूर्ण

