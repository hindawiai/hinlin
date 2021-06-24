<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2020 Marvell. */

#समावेश "otx2_cpt_common.h"
#समावेश "otx2_cptvf.h"
#समावेश "otx2_cptlf.h"
#समावेश "otx2_cptvf_algs.h"
#समावेश <rvu_reg.h>

#घोषणा OTX2_CPTVF_DRV_NAME "octeontx2-cptvf"

अटल व्योम cptvf_enable_pfvf_mbox_पूर्णांकrs(काष्ठा otx2_cptvf_dev *cptvf)
अणु
	/* Clear पूर्णांकerrupt अगर any */
	otx2_cpt_ग_लिखो64(cptvf->reg_base, BLKADDR_RVUM, 0, OTX2_RVU_VF_INT,
			 0x1ULL);

	/* Enable PF-VF पूर्णांकerrupt */
	otx2_cpt_ग_लिखो64(cptvf->reg_base, BLKADDR_RVUM, 0,
			 OTX2_RVU_VF_INT_ENA_W1S, 0x1ULL);
पूर्ण

अटल व्योम cptvf_disable_pfvf_mbox_पूर्णांकrs(काष्ठा otx2_cptvf_dev *cptvf)
अणु
	/* Disable PF-VF पूर्णांकerrupt */
	otx2_cpt_ग_लिखो64(cptvf->reg_base, BLKADDR_RVUM, 0,
			 OTX2_RVU_VF_INT_ENA_W1C, 0x1ULL);

	/* Clear पूर्णांकerrupt अगर any */
	otx2_cpt_ग_लिखो64(cptvf->reg_base, BLKADDR_RVUM, 0, OTX2_RVU_VF_INT,
			 0x1ULL);
पूर्ण

अटल पूर्णांक cptvf_रेजिस्टर_पूर्णांकerrupts(काष्ठा otx2_cptvf_dev *cptvf)
अणु
	पूर्णांक ret, irq;
	पूर्णांक num_vec;

	num_vec = pci_msix_vec_count(cptvf->pdev);
	अगर (num_vec <= 0)
		वापस -EINVAL;

	/* Enable MSI-X */
	ret = pci_alloc_irq_vectors(cptvf->pdev, num_vec, num_vec,
				    PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		dev_err(&cptvf->pdev->dev,
			"Request for %d msix vectors failed\n", num_vec);
		वापस ret;
	पूर्ण
	irq = pci_irq_vector(cptvf->pdev, OTX2_CPT_VF_INT_VEC_E_MBOX);
	/* Register VF<=>PF mailbox पूर्णांकerrupt handler */
	ret = devm_request_irq(&cptvf->pdev->dev, irq,
			       otx2_cptvf_pfvf_mbox_पूर्णांकr, 0,
			       "CPTPFVF Mbox", cptvf);
	अगर (ret)
		वापस ret;
	/* Enable PF-VF mailbox पूर्णांकerrupts */
	cptvf_enable_pfvf_mbox_पूर्णांकrs(cptvf);

	ret = otx2_cpt_send_पढ़ोy_msg(&cptvf->pfvf_mbox, cptvf->pdev);
	अगर (ret) अणु
		dev_warn(&cptvf->pdev->dev,
			 "PF not responding to mailbox, deferring probe\n");
		cptvf_disable_pfvf_mbox_पूर्णांकrs(cptvf);
		वापस -EPROBE_DEFER;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cptvf_pfvf_mbox_init(काष्ठा otx2_cptvf_dev *cptvf)
अणु
	पूर्णांक ret;

	cptvf->pfvf_mbox_wq = alloc_workqueue("cpt_pfvf_mailbox",
					      WQ_UNBOUND | WQ_HIGHPRI |
					      WQ_MEM_RECLAIM, 1);
	अगर (!cptvf->pfvf_mbox_wq)
		वापस -ENOMEM;

	ret = otx2_mbox_init(&cptvf->pfvf_mbox, cptvf->pfvf_mbox_base,
			     cptvf->pdev, cptvf->reg_base, MBOX_सूची_VFPF, 1);
	अगर (ret)
		जाओ मुक्त_wqe;

	INIT_WORK(&cptvf->pfvf_mbox_work, otx2_cptvf_pfvf_mbox_handler);
	वापस 0;

मुक्त_wqe:
	destroy_workqueue(cptvf->pfvf_mbox_wq);
	वापस ret;
पूर्ण

अटल व्योम cptvf_pfvf_mbox_destroy(काष्ठा otx2_cptvf_dev *cptvf)
अणु
	destroy_workqueue(cptvf->pfvf_mbox_wq);
	otx2_mbox_destroy(&cptvf->pfvf_mbox);
पूर्ण

अटल व्योम cptlf_work_handler(अचिन्हित दीर्घ data)
अणु
	otx2_cpt_post_process((काष्ठा otx2_cptlf_wqe *) data);
पूर्ण

अटल व्योम cleanup_tasklet_work(काष्ठा otx2_cptlfs_info *lfs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <  lfs->lfs_num; i++) अणु
		अगर (!lfs->lf[i].wqe)
			जारी;

		tasklet_समाप्त(&lfs->lf[i].wqe->work);
		kमुक्त(lfs->lf[i].wqe);
		lfs->lf[i].wqe = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक init_tasklet_work(काष्ठा otx2_cptlfs_info *lfs)
अणु
	काष्ठा otx2_cptlf_wqe *wqe;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < lfs->lfs_num; i++) अणु
		wqe = kzalloc(माप(काष्ठा otx2_cptlf_wqe), GFP_KERNEL);
		अगर (!wqe) अणु
			ret = -ENOMEM;
			जाओ cleanup_tasklet;
		पूर्ण

		tasklet_init(&wqe->work, cptlf_work_handler, (u64) wqe);
		wqe->lfs = lfs;
		wqe->lf_num = i;
		lfs->lf[i].wqe = wqe;
	पूर्ण
	वापस 0;

cleanup_tasklet:
	cleanup_tasklet_work(lfs);
	वापस ret;
पूर्ण

अटल व्योम मुक्त_pending_queues(काष्ठा otx2_cptlfs_info *lfs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < lfs->lfs_num; i++) अणु
		kमुक्त(lfs->lf[i].pqueue.head);
		lfs->lf[i].pqueue.head = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_pending_queues(काष्ठा otx2_cptlfs_info *lfs)
अणु
	पूर्णांक size, ret, i;

	अगर (!lfs->lfs_num)
		वापस -EINVAL;

	क्रम (i = 0; i < lfs->lfs_num; i++) अणु
		lfs->lf[i].pqueue.qlen = OTX2_CPT_INST_QLEN_MSGS;
		size = lfs->lf[i].pqueue.qlen *
		       माप(काष्ठा otx2_cpt_pending_entry);

		lfs->lf[i].pqueue.head = kzalloc(size, GFP_KERNEL);
		अगर (!lfs->lf[i].pqueue.head) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण

		/* Initialize spin lock */
		spin_lock_init(&lfs->lf[i].pqueue.lock);
	पूर्ण
	वापस 0;

error:
	मुक्त_pending_queues(lfs);
	वापस ret;
पूर्ण

अटल व्योम lf_sw_cleanup(काष्ठा otx2_cptlfs_info *lfs)
अणु
	cleanup_tasklet_work(lfs);
	मुक्त_pending_queues(lfs);
पूर्ण

अटल पूर्णांक lf_sw_init(काष्ठा otx2_cptlfs_info *lfs)
अणु
	पूर्णांक ret;

	ret = alloc_pending_queues(lfs);
	अगर (ret) अणु
		dev_err(&lfs->pdev->dev,
			"Allocating pending queues failed\n");
		वापस ret;
	पूर्ण
	ret = init_tasklet_work(lfs);
	अगर (ret) अणु
		dev_err(&lfs->pdev->dev,
			"Tasklet work init failed\n");
		जाओ pending_queues_मुक्त;
	पूर्ण
	वापस 0;

pending_queues_मुक्त:
	मुक्त_pending_queues(lfs);
	वापस ret;
पूर्ण

अटल व्योम cptvf_lf_shutकरोwn(काष्ठा otx2_cptlfs_info *lfs)
अणु
	atomic_set(&lfs->state, OTX2_CPTLF_IN_RESET);

	/* Remove पूर्णांकerrupts affinity */
	otx2_cptlf_मुक्त_irqs_affinity(lfs);
	/* Disable inकाष्ठाion queue */
	otx2_cptlf_disable_iqueues(lfs);
	/* Unरेजिस्टर crypto algorithms */
	otx2_cpt_crypto_निकास(lfs->pdev, THIS_MODULE);
	/* Unरेजिस्टर LFs पूर्णांकerrupts */
	otx2_cptlf_unरेजिस्टर_पूर्णांकerrupts(lfs);
	/* Cleanup LFs software side */
	lf_sw_cleanup(lfs);
	/* Send request to detach LFs */
	otx2_cpt_detach_rsrcs_msg(lfs);
पूर्ण

अटल पूर्णांक cptvf_lf_init(काष्ठा otx2_cptvf_dev *cptvf)
अणु
	काष्ठा otx2_cptlfs_info *lfs = &cptvf->lfs;
	काष्ठा device *dev = &cptvf->pdev->dev;
	पूर्णांक ret, lfs_num;
	u8 eng_grp_msk;

	/* Get engine group number क्रम symmetric crypto */
	cptvf->lfs.kcrypto_eng_grp_num = OTX2_CPT_INVALID_CRYPTO_ENG_GRP;
	ret = otx2_cptvf_send_eng_grp_num_msg(cptvf, OTX2_CPT_SE_TYPES);
	अगर (ret)
		वापस ret;

	अगर (cptvf->lfs.kcrypto_eng_grp_num == OTX2_CPT_INVALID_CRYPTO_ENG_GRP) अणु
		dev_err(dev, "Engine group for kernel crypto not available\n");
		ret = -ENOENT;
		वापस ret;
	पूर्ण
	eng_grp_msk = 1 << cptvf->lfs.kcrypto_eng_grp_num;

	ret = otx2_cptvf_send_kvf_limits_msg(cptvf);
	अगर (ret)
		वापस ret;

	lfs->reg_base = cptvf->reg_base;
	lfs->pdev = cptvf->pdev;
	lfs->mbox = &cptvf->pfvf_mbox;

	lfs_num = cptvf->lfs.kvf_limits ? cptvf->lfs.kvf_limits :
		  num_online_cpus();
	ret = otx2_cptlf_init(lfs, eng_grp_msk, OTX2_CPT_QUEUE_HI_PRIO,
			      lfs_num);
	अगर (ret)
		वापस ret;

	/* Get msix offsets क्रम attached LFs */
	ret = otx2_cpt_msix_offset_msg(lfs);
	अगर (ret)
		जाओ cleanup_lf;

	/* Initialize LFs software side */
	ret = lf_sw_init(lfs);
	अगर (ret)
		जाओ cleanup_lf;

	/* Register LFs पूर्णांकerrupts */
	ret = otx2_cptlf_रेजिस्टर_पूर्णांकerrupts(lfs);
	अगर (ret)
		जाओ cleanup_lf_sw;

	/* Set पूर्णांकerrupts affinity */
	ret = otx2_cptlf_set_irqs_affinity(lfs);
	अगर (ret)
		जाओ unरेजिस्टर_पूर्णांकr;

	atomic_set(&lfs->state, OTX2_CPTLF_STARTED);
	/* Register crypto algorithms */
	ret = otx2_cpt_crypto_init(lfs->pdev, THIS_MODULE, lfs_num, 1);
	अगर (ret) अणु
		dev_err(&lfs->pdev->dev, "algorithms registration failed\n");
		जाओ disable_irqs;
	पूर्ण
	वापस 0;

disable_irqs:
	otx2_cptlf_मुक्त_irqs_affinity(lfs);
unरेजिस्टर_पूर्णांकr:
	otx2_cptlf_unरेजिस्टर_पूर्णांकerrupts(lfs);
cleanup_lf_sw:
	lf_sw_cleanup(lfs);
cleanup_lf:
	otx2_cptlf_shutकरोwn(lfs);

	वापस ret;
पूर्ण

अटल पूर्णांक otx2_cptvf_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	resource_माप_प्रकार offset, size;
	काष्ठा otx2_cptvf_dev *cptvf;
	पूर्णांक ret;

	cptvf = devm_kzalloc(dev, माप(*cptvf), GFP_KERNEL);
	अगर (!cptvf)
		वापस -ENOMEM;

	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable PCI device\n");
		जाओ clear_drvdata;
	पूर्ण

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(48));
	अगर (ret) अणु
		dev_err(dev, "Unable to get usable DMA configuration\n");
		जाओ clear_drvdata;
	पूर्ण
	/* Map VF's configuration रेजिस्टरs */
	ret = pcim_iomap_regions_request_all(pdev, 1 << PCI_PF_REG_BAR_NUM,
					     OTX2_CPTVF_DRV_NAME);
	अगर (ret) अणु
		dev_err(dev, "Couldn't get PCI resources 0x%x\n", ret);
		जाओ clear_drvdata;
	पूर्ण
	pci_set_master(pdev);
	pci_set_drvdata(pdev, cptvf);
	cptvf->pdev = pdev;

	cptvf->reg_base = pcim_iomap_table(pdev)[PCI_PF_REG_BAR_NUM];

	offset = pci_resource_start(pdev, PCI_MBOX_BAR_NUM);
	size = pci_resource_len(pdev, PCI_MBOX_BAR_NUM);
	/* Map PF-VF mailbox memory */
	cptvf->pfvf_mbox_base = devm_ioremap_wc(dev, offset, size);
	अगर (!cptvf->pfvf_mbox_base) अणु
		dev_err(&pdev->dev, "Unable to map BAR4\n");
		ret = -ENODEV;
		जाओ clear_drvdata;
	पूर्ण
	/* Initialize PF<=>VF mailbox */
	ret = cptvf_pfvf_mbox_init(cptvf);
	अगर (ret)
		जाओ clear_drvdata;

	/* Register पूर्णांकerrupts */
	ret = cptvf_रेजिस्टर_पूर्णांकerrupts(cptvf);
	अगर (ret)
		जाओ destroy_pfvf_mbox;

	/* Initialize CPT LFs */
	ret = cptvf_lf_init(cptvf);
	अगर (ret)
		जाओ unरेजिस्टर_पूर्णांकerrupts;

	वापस 0;

unरेजिस्टर_पूर्णांकerrupts:
	cptvf_disable_pfvf_mbox_पूर्णांकrs(cptvf);
destroy_pfvf_mbox:
	cptvf_pfvf_mbox_destroy(cptvf);
clear_drvdata:
	pci_set_drvdata(pdev, शून्य);

	वापस ret;
पूर्ण

अटल व्योम otx2_cptvf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा otx2_cptvf_dev *cptvf = pci_get_drvdata(pdev);

	अगर (!cptvf) अणु
		dev_err(&pdev->dev, "Invalid CPT VF device.\n");
		वापस;
	पूर्ण
	cptvf_lf_shutकरोwn(&cptvf->lfs);
	/* Disable PF-VF mailbox पूर्णांकerrupt */
	cptvf_disable_pfvf_mbox_पूर्णांकrs(cptvf);
	/* Destroy PF-VF mbox */
	cptvf_pfvf_mbox_destroy(cptvf);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id otx2_cptvf_id_table[] = अणु
	अणुPCI_VDEVICE(CAVIUM, OTX2_CPT_PCI_VF_DEVICE_ID), 0पूर्ण,
	अणु 0, पूर्ण  /* end of table */
पूर्ण;

अटल काष्ठा pci_driver otx2_cptvf_pci_driver = अणु
	.name = OTX2_CPTVF_DRV_NAME,
	.id_table = otx2_cptvf_id_table,
	.probe = otx2_cptvf_probe,
	.हटाओ = otx2_cptvf_हटाओ,
पूर्ण;

module_pci_driver(otx2_cptvf_pci_driver);

MODULE_AUTHOR("Marvell");
MODULE_DESCRIPTION("Marvell OcteonTX2 CPT Virtual Function Driver");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(pci, otx2_cptvf_id_table);
