<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-2-Clause
/*
 * Copyright 2018-2021 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/utsname.h>
#समावेश <linux/version.h>

#समावेश <rdma/ib_user_verbs.h>

#समावेश "efa.h"

#घोषणा PCI_DEV_ID_EFA0_VF 0xefa0
#घोषणा PCI_DEV_ID_EFA1_VF 0xefa1

अटल स्थिर काष्ठा pci_device_id efa_pci_tbl[] = अणु
	अणु PCI_VDEVICE(AMAZON, PCI_DEV_ID_EFA0_VF) पूर्ण,
	अणु PCI_VDEVICE(AMAZON, PCI_DEV_ID_EFA1_VF) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_AUTHOR("Amazon.com, Inc. or its affiliates");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION(DEVICE_NAME);
MODULE_DEVICE_TABLE(pci, efa_pci_tbl);

#घोषणा EFA_REG_BAR 0
#घोषणा EFA_MEM_BAR 2
#घोषणा EFA_BASE_BAR_MASK (BIT(EFA_REG_BAR) | BIT(EFA_MEM_BAR))

#घोषणा EFA_AENQ_ENABLED_GROUPS \
	(BIT(EFA_ADMIN_FATAL_ERROR) | BIT(EFA_ADMIN_WARNING) | \
	 BIT(EFA_ADMIN_NOTIFICATION) | BIT(EFA_ADMIN_KEEP_ALIVE))

/* This handler will called क्रम unknown event group or unimplemented handlers */
अटल व्योम unimplemented_aenq_handler(व्योम *data,
				       काष्ठा efa_admin_aenq_entry *aenq_e)
अणु
	काष्ठा efa_dev *dev = (काष्ठा efa_dev *)data;

	ibdev_err(&dev->ibdev,
		  "Unknown event was received or event with unimplemented handler\n");
पूर्ण

अटल व्योम efa_keep_alive(व्योम *data, काष्ठा efa_admin_aenq_entry *aenq_e)
अणु
	काष्ठा efa_dev *dev = (काष्ठा efa_dev *)data;

	atomic64_inc(&dev->stats.keep_alive_rcvd);
पूर्ण

अटल काष्ठा efa_aenq_handlers aenq_handlers = अणु
	.handlers = अणु
		[EFA_ADMIN_KEEP_ALIVE] = efa_keep_alive,
	पूर्ण,
	.unimplemented_handler = unimplemented_aenq_handler
पूर्ण;

अटल व्योम efa_release_bars(काष्ठा efa_dev *dev, पूर्णांक bars_mask)
अणु
	काष्ठा pci_dev *pdev = dev->pdev;
	पूर्णांक release_bars;

	release_bars = pci_select_bars(pdev, IORESOURCE_MEM) & bars_mask;
	pci_release_selected_regions(pdev, release_bars);
पूर्ण

अटल irqवापस_t efa_पूर्णांकr_msix_mgmnt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा efa_dev *dev = data;

	efa_com_admin_q_comp_पूर्णांकr_handler(&dev->edev);
	efa_com_aenq_पूर्णांकr_handler(&dev->edev, data);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक efa_request_mgmnt_irq(काष्ठा efa_dev *dev)
अणु
	काष्ठा efa_irq *irq;
	पूर्णांक err;

	irq = &dev->admin_irq;
	err = request_irq(irq->vector, irq->handler, 0, irq->name,
			  irq->data);
	अगर (err) अणु
		dev_err(&dev->pdev->dev, "Failed to request admin irq (%d)\n",
			err);
		वापस err;
	पूर्ण

	dev_dbg(&dev->pdev->dev, "Set affinity hint of mgmnt irq to %*pbl (irq vector: %d)\n",
		nr_cpumask_bits, &irq->affinity_hपूर्णांक_mask, irq->vector);
	irq_set_affinity_hपूर्णांक(irq->vector, &irq->affinity_hपूर्णांक_mask);

	वापस 0;
पूर्ण

अटल व्योम efa_setup_mgmnt_irq(काष्ठा efa_dev *dev)
अणु
	u32 cpu;

	snम_लिखो(dev->admin_irq.name, EFA_IRQNAME_SIZE,
		 "efa-mgmnt@pci:%s", pci_name(dev->pdev));
	dev->admin_irq.handler = efa_पूर्णांकr_msix_mgmnt;
	dev->admin_irq.data = dev;
	dev->admin_irq.vector =
		pci_irq_vector(dev->pdev, dev->admin_msix_vector_idx);
	cpu = cpumask_first(cpu_online_mask);
	dev->admin_irq.cpu = cpu;
	cpumask_set_cpu(cpu,
			&dev->admin_irq.affinity_hपूर्णांक_mask);
	dev_info(&dev->pdev->dev, "Setup irq:0x%p vector:%d name:%s\n",
		 &dev->admin_irq,
		 dev->admin_irq.vector,
		 dev->admin_irq.name);
पूर्ण

अटल व्योम efa_मुक्त_mgmnt_irq(काष्ठा efa_dev *dev)
अणु
	काष्ठा efa_irq *irq;

	irq = &dev->admin_irq;
	irq_set_affinity_hपूर्णांक(irq->vector, शून्य);
	मुक्त_irq(irq->vector, irq->data);
पूर्ण

अटल पूर्णांक efa_set_mgmnt_irq(काष्ठा efa_dev *dev)
अणु
	efa_setup_mgmnt_irq(dev);

	वापस efa_request_mgmnt_irq(dev);
पूर्ण

अटल पूर्णांक efa_request_करोorbell_bar(काष्ठा efa_dev *dev)
अणु
	u8 db_bar_idx = dev->dev_attr.db_bar;
	काष्ठा pci_dev *pdev = dev->pdev;
	पूर्णांक bars;
	पूर्णांक err;

	अगर (!(BIT(db_bar_idx) & EFA_BASE_BAR_MASK)) अणु
		bars = pci_select_bars(pdev, IORESOURCE_MEM) & BIT(db_bar_idx);

		err = pci_request_selected_regions(pdev, bars, DRV_MODULE_NAME);
		अगर (err) अणु
			dev_err(&dev->pdev->dev,
				"pci_request_selected_regions for bar %d failed %d\n",
				db_bar_idx, err);
			वापस err;
		पूर्ण
	पूर्ण

	dev->db_bar_addr = pci_resource_start(dev->pdev, db_bar_idx);
	dev->db_bar_len = pci_resource_len(dev->pdev, db_bar_idx);

	वापस 0;
पूर्ण

अटल व्योम efa_release_करोorbell_bar(काष्ठा efa_dev *dev)
अणु
	अगर (!(BIT(dev->dev_attr.db_bar) & EFA_BASE_BAR_MASK))
		efa_release_bars(dev, BIT(dev->dev_attr.db_bar));
पूर्ण

अटल व्योम efa_update_hw_hपूर्णांकs(काष्ठा efa_dev *dev,
				काष्ठा efa_com_get_hw_hपूर्णांकs_result *hw_hपूर्णांकs)
अणु
	काष्ठा efa_com_dev *edev = &dev->edev;

	अगर (hw_hपूर्णांकs->mmio_पढ़ो_समयout)
		edev->mmio_पढ़ो.mmio_पढ़ो_समयout =
			hw_hपूर्णांकs->mmio_पढ़ो_समयout * 1000;

	अगर (hw_hपूर्णांकs->poll_पूर्णांकerval)
		edev->aq.poll_पूर्णांकerval = hw_hपूर्णांकs->poll_पूर्णांकerval;

	अगर (hw_hपूर्णांकs->admin_completion_समयout)
		edev->aq.completion_समयout =
			hw_hपूर्णांकs->admin_completion_समयout;
पूर्ण

अटल व्योम efa_stats_init(काष्ठा efa_dev *dev)
अणु
	atomic64_t *s = (atomic64_t *)&dev->stats;
	पूर्णांक i;

	क्रम (i = 0; i < माप(dev->stats) / माप(*s); i++, s++)
		atomic64_set(s, 0);
पूर्ण

अटल व्योम efa_set_host_info(काष्ठा efa_dev *dev)
अणु
	काष्ठा efa_admin_set_feature_resp resp = अणुपूर्ण;
	काष्ठा efa_admin_set_feature_cmd cmd = अणुपूर्ण;
	काष्ठा efa_admin_host_info *hinf;
	u32 bufsz = माप(*hinf);
	dma_addr_t hinf_dma;

	अगर (!efa_com_check_supported_feature_id(&dev->edev,
						EFA_ADMIN_HOST_INFO))
		वापस;

	/* Failures in host info set shall not disturb probe */
	hinf = dma_alloc_coherent(&dev->pdev->dev, bufsz, &hinf_dma,
				  GFP_KERNEL);
	अगर (!hinf)
		वापस;

	strscpy(hinf->os_dist_str, utsname()->release,
		माप(hinf->os_dist_str));
	hinf->os_type = EFA_ADMIN_OS_LINUX;
	strscpy(hinf->kernel_ver_str, utsname()->version,
		माप(hinf->kernel_ver_str));
	hinf->kernel_ver = LINUX_VERSION_CODE;
	EFA_SET(&hinf->driver_ver, EFA_ADMIN_HOST_INFO_DRIVER_MAJOR, 0);
	EFA_SET(&hinf->driver_ver, EFA_ADMIN_HOST_INFO_DRIVER_MINOR, 0);
	EFA_SET(&hinf->driver_ver, EFA_ADMIN_HOST_INFO_DRIVER_SUB_MINOR, 0);
	EFA_SET(&hinf->driver_ver, EFA_ADMIN_HOST_INFO_DRIVER_MODULE_TYPE, 0);
	EFA_SET(&hinf->bdf, EFA_ADMIN_HOST_INFO_BUS, dev->pdev->bus->number);
	EFA_SET(&hinf->bdf, EFA_ADMIN_HOST_INFO_DEVICE,
		PCI_SLOT(dev->pdev->devfn));
	EFA_SET(&hinf->bdf, EFA_ADMIN_HOST_INFO_FUNCTION,
		PCI_FUNC(dev->pdev->devfn));
	EFA_SET(&hinf->spec_ver, EFA_ADMIN_HOST_INFO_SPEC_MAJOR,
		EFA_COMMON_SPEC_VERSION_MAJOR);
	EFA_SET(&hinf->spec_ver, EFA_ADMIN_HOST_INFO_SPEC_MINOR,
		EFA_COMMON_SPEC_VERSION_MINOR);
	EFA_SET(&hinf->flags, EFA_ADMIN_HOST_INFO_INTREE, 1);
	EFA_SET(&hinf->flags, EFA_ADMIN_HOST_INFO_GDR, 0);

	efa_com_set_feature_ex(&dev->edev, &resp, &cmd, EFA_ADMIN_HOST_INFO,
			       hinf_dma, bufsz);

	dma_मुक्त_coherent(&dev->pdev->dev, bufsz, hinf, hinf_dma);
पूर्ण

अटल स्थिर काष्ठा ib_device_ops efa_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_EFA,
	.uverbs_abi_ver = EFA_UVERBS_ABI_VERSION,

	.alloc_hw_stats = efa_alloc_hw_stats,
	.alloc_pd = efa_alloc_pd,
	.alloc_ucontext = efa_alloc_ucontext,
	.create_cq = efa_create_cq,
	.create_qp = efa_create_qp,
	.create_user_ah = efa_create_ah,
	.dealloc_pd = efa_dealloc_pd,
	.dealloc_ucontext = efa_dealloc_ucontext,
	.dereg_mr = efa_dereg_mr,
	.destroy_ah = efa_destroy_ah,
	.destroy_cq = efa_destroy_cq,
	.destroy_qp = efa_destroy_qp,
	.get_hw_stats = efa_get_hw_stats,
	.get_link_layer = efa_port_link_layer,
	.get_port_immutable = efa_get_port_immutable,
	.mmap = efa_mmap,
	.mmap_मुक्त = efa_mmap_मुक्त,
	.modअगरy_qp = efa_modअगरy_qp,
	.query_device = efa_query_device,
	.query_gid = efa_query_gid,
	.query_pkey = efa_query_pkey,
	.query_port = efa_query_port,
	.query_qp = efa_query_qp,
	.reg_user_mr = efa_reg_mr,

	INIT_RDMA_OBJ_SIZE(ib_ah, efa_ah, ibah),
	INIT_RDMA_OBJ_SIZE(ib_cq, efa_cq, ibcq),
	INIT_RDMA_OBJ_SIZE(ib_pd, efa_pd, ibpd),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, efa_ucontext, ibucontext),
पूर्ण;

अटल पूर्णांक efa_ib_device_add(काष्ठा efa_dev *dev)
अणु
	काष्ठा efa_com_get_hw_hपूर्णांकs_result hw_hपूर्णांकs;
	काष्ठा pci_dev *pdev = dev->pdev;
	पूर्णांक err;

	efa_stats_init(dev);

	err = efa_com_get_device_attr(&dev->edev, &dev->dev_attr);
	अगर (err)
		वापस err;

	dev_dbg(&dev->pdev->dev, "Doorbells bar (%d)\n", dev->dev_attr.db_bar);
	err = efa_request_करोorbell_bar(dev);
	अगर (err)
		वापस err;

	err = efa_com_get_hw_hपूर्णांकs(&dev->edev, &hw_hपूर्णांकs);
	अगर (err)
		जाओ err_release_करोorbell_bar;

	efa_update_hw_hपूर्णांकs(dev, &hw_hपूर्णांकs);

	/* Try to enable all the available aenq groups */
	err = efa_com_set_aenq_config(&dev->edev, EFA_AENQ_ENABLED_GROUPS);
	अगर (err)
		जाओ err_release_करोorbell_bar;

	efa_set_host_info(dev);

	dev->ibdev.node_type = RDMA_NODE_UNSPECIFIED;
	dev->ibdev.phys_port_cnt = 1;
	dev->ibdev.num_comp_vectors = 1;
	dev->ibdev.dev.parent = &pdev->dev;

	ib_set_device_ops(&dev->ibdev, &efa_dev_ops);

	err = ib_रेजिस्टर_device(&dev->ibdev, "efa_%d", &pdev->dev);
	अगर (err)
		जाओ err_release_करोorbell_bar;

	ibdev_info(&dev->ibdev, "IB device registered\n");

	वापस 0;

err_release_करोorbell_bar:
	efa_release_करोorbell_bar(dev);
	वापस err;
पूर्ण

अटल व्योम efa_ib_device_हटाओ(काष्ठा efa_dev *dev)
अणु
	efa_com_dev_reset(&dev->edev, EFA_REGS_RESET_NORMAL);
	ibdev_info(&dev->ibdev, "Unregister ib device\n");
	ib_unरेजिस्टर_device(&dev->ibdev);
	efa_release_करोorbell_bar(dev);
पूर्ण

अटल व्योम efa_disable_msix(काष्ठा efa_dev *dev)
अणु
	pci_मुक्त_irq_vectors(dev->pdev);
पूर्ण

अटल पूर्णांक efa_enable_msix(काष्ठा efa_dev *dev)
अणु
	पूर्णांक msix_vecs, irq_num;

	/* Reserve the max msix vectors we might need */
	msix_vecs = EFA_NUM_MSIX_VEC;
	dev_dbg(&dev->pdev->dev, "Trying to enable MSI-X, vectors %d\n",
		msix_vecs);

	dev->admin_msix_vector_idx = EFA_MGMNT_MSIX_VEC_IDX;
	irq_num = pci_alloc_irq_vectors(dev->pdev, msix_vecs,
					msix_vecs, PCI_IRQ_MSIX);

	अगर (irq_num < 0) अणु
		dev_err(&dev->pdev->dev, "Failed to enable MSI-X. irq_num %d\n",
			irq_num);
		वापस -ENOSPC;
	पूर्ण

	अगर (irq_num != msix_vecs) अणु
		dev_err(&dev->pdev->dev,
			"Allocated %d MSI-X (out of %d requested)\n",
			irq_num, msix_vecs);
		वापस -ENOSPC;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक efa_device_init(काष्ठा efa_com_dev *edev, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक dma_width;
	पूर्णांक err;

	err = efa_com_dev_reset(edev, EFA_REGS_RESET_NORMAL);
	अगर (err)
		वापस err;

	err = efa_com_validate_version(edev);
	अगर (err)
		वापस err;

	dma_width = efa_com_get_dma_width(edev);
	अगर (dma_width < 0) अणु
		err = dma_width;
		वापस err;
	पूर्ण

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(dma_width));
	अगर (err) अणु
		dev_err(&pdev->dev, "dma_set_mask_and_coherent failed %d\n", err);
		वापस err;
	पूर्ण

	dma_set_max_seg_size(&pdev->dev, अच_पूर्णांक_उच्च);
	वापस 0;
पूर्ण

अटल काष्ठा efa_dev *efa_probe_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा efa_com_dev *edev;
	काष्ठा efa_dev *dev;
	पूर्णांक bars;
	पूर्णांक err;

	err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "pci_enable_device_mem() failed!\n");
		वापस ERR_PTR(err);
	पूर्ण

	pci_set_master(pdev);

	dev = ib_alloc_device(efa_dev, ibdev);
	अगर (!dev) अणु
		dev_err(&pdev->dev, "Device alloc failed\n");
		err = -ENOMEM;
		जाओ err_disable_device;
	पूर्ण

	pci_set_drvdata(pdev, dev);
	edev = &dev->edev;
	edev->efa_dev = dev;
	edev->dmadev = &pdev->dev;
	dev->pdev = pdev;

	bars = pci_select_bars(pdev, IORESOURCE_MEM) & EFA_BASE_BAR_MASK;
	err = pci_request_selected_regions(pdev, bars, DRV_MODULE_NAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "pci_request_selected_regions failed %d\n",
			err);
		जाओ err_ibdev_destroy;
	पूर्ण

	dev->reg_bar_addr = pci_resource_start(pdev, EFA_REG_BAR);
	dev->reg_bar_len = pci_resource_len(pdev, EFA_REG_BAR);
	dev->mem_bar_addr = pci_resource_start(pdev, EFA_MEM_BAR);
	dev->mem_bar_len = pci_resource_len(pdev, EFA_MEM_BAR);

	edev->reg_bar = devm_ioremap(&pdev->dev,
				     dev->reg_bar_addr,
				     dev->reg_bar_len);
	अगर (!edev->reg_bar) अणु
		dev_err(&pdev->dev, "Failed to remap register bar\n");
		err = -EFAULT;
		जाओ err_release_bars;
	पूर्ण

	err = efa_com_mmio_reg_पढ़ो_init(edev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to init readless MMIO\n");
		जाओ err_iounmap;
	पूर्ण

	err = efa_device_init(edev, pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "EFA device init failed\n");
		अगर (err == -ETIME)
			err = -EPROBE_DEFER;
		जाओ err_reg_पढ़ो_destroy;
	पूर्ण

	err = efa_enable_msix(dev);
	अगर (err)
		जाओ err_reg_पढ़ो_destroy;

	edev->aq.msix_vector_idx = dev->admin_msix_vector_idx;
	edev->aenq.msix_vector_idx = dev->admin_msix_vector_idx;

	err = efa_set_mgmnt_irq(dev);
	अगर (err)
		जाओ err_disable_msix;

	err = efa_com_admin_init(edev, &aenq_handlers);
	अगर (err)
		जाओ err_मुक्त_mgmnt_irq;

	वापस dev;

err_मुक्त_mgmnt_irq:
	efa_मुक्त_mgmnt_irq(dev);
err_disable_msix:
	efa_disable_msix(dev);
err_reg_पढ़ो_destroy:
	efa_com_mmio_reg_पढ़ो_destroy(edev);
err_iounmap:
	devm_iounmap(&pdev->dev, edev->reg_bar);
err_release_bars:
	efa_release_bars(dev, EFA_BASE_BAR_MASK);
err_ibdev_destroy:
	ib_dealloc_device(&dev->ibdev);
err_disable_device:
	pci_disable_device(pdev);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम efa_हटाओ_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा efa_dev *dev = pci_get_drvdata(pdev);
	काष्ठा efa_com_dev *edev;

	edev = &dev->edev;
	efa_com_admin_destroy(edev);
	efa_मुक्त_mgmnt_irq(dev);
	efa_disable_msix(dev);
	efa_com_mmio_reg_पढ़ो_destroy(edev);
	devm_iounmap(&pdev->dev, edev->reg_bar);
	efa_release_bars(dev, EFA_BASE_BAR_MASK);
	ib_dealloc_device(&dev->ibdev);
	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक efa_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा efa_dev *dev;
	पूर्णांक err;

	dev = efa_probe_device(pdev);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);

	err = efa_ib_device_add(dev);
	अगर (err)
		जाओ err_हटाओ_device;

	वापस 0;

err_हटाओ_device:
	efa_हटाओ_device(pdev);
	वापस err;
पूर्ण

अटल व्योम efa_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा efa_dev *dev = pci_get_drvdata(pdev);

	efa_ib_device_हटाओ(dev);
	efa_हटाओ_device(pdev);
पूर्ण

अटल काष्ठा pci_driver efa_pci_driver = अणु
	.name           = DRV_MODULE_NAME,
	.id_table       = efa_pci_tbl,
	.probe          = efa_probe,
	.हटाओ         = efa_हटाओ,
पूर्ण;

module_pci_driver(efa_pci_driver);
