<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2020 Marvell. */

#समावेश <linux/firmware.h>
#समावेश "otx2_cpt_hw_types.h"
#समावेश "otx2_cpt_common.h"
#समावेश "otx2_cptpf_ucode.h"
#समावेश "otx2_cptpf.h"
#समावेश "rvu_reg.h"

#घोषणा OTX2_CPT_DRV_NAME    "octeontx2-cpt"
#घोषणा OTX2_CPT_DRV_STRING  "Marvell OcteonTX2 CPT Physical Function Driver"

अटल व्योम cptpf_enable_vfpf_mbox_पूर्णांकr(काष्ठा otx2_cptpf_dev *cptpf,
					पूर्णांक num_vfs)
अणु
	पूर्णांक ena_bits;

	/* Clear any pending पूर्णांकerrupts */
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0,
			 RVU_PF_VFPF_MBOX_INTX(0), ~0x0ULL);
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0,
			 RVU_PF_VFPF_MBOX_INTX(1), ~0x0ULL);

	/* Enable VF पूर्णांकerrupts क्रम VFs from 0 to 63 */
	ena_bits = ((num_vfs - 1) % 64);
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0,
			 RVU_PF_VFPF_MBOX_INT_ENA_W1SX(0),
			 GENMASK_ULL(ena_bits, 0));

	अगर (num_vfs > 64) अणु
		/* Enable VF पूर्णांकerrupts क्रम VFs from 64 to 127 */
		ena_bits = num_vfs - 64 - 1;
		otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0,
				RVU_PF_VFPF_MBOX_INT_ENA_W1SX(1),
				GENMASK_ULL(ena_bits, 0));
	पूर्ण
पूर्ण

अटल व्योम cptpf_disable_vfpf_mbox_पूर्णांकr(काष्ठा otx2_cptpf_dev *cptpf,
					 पूर्णांक num_vfs)
अणु
	पूर्णांक vector;

	/* Disable VF-PF पूर्णांकerrupts */
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0,
			 RVU_PF_VFPF_MBOX_INT_ENA_W1CX(0), ~0ULL);
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0,
			 RVU_PF_VFPF_MBOX_INT_ENA_W1CX(1), ~0ULL);
	/* Clear any pending पूर्णांकerrupts */
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0,
			 RVU_PF_VFPF_MBOX_INTX(0), ~0ULL);

	vector = pci_irq_vector(cptpf->pdev, RVU_PF_INT_VEC_VFPF_MBOX0);
	मुक्त_irq(vector, cptpf);

	अगर (num_vfs > 64) अणु
		otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0,
				 RVU_PF_VFPF_MBOX_INTX(1), ~0ULL);
		vector = pci_irq_vector(cptpf->pdev, RVU_PF_INT_VEC_VFPF_MBOX1);
		मुक्त_irq(vector, cptpf);
	पूर्ण
पूर्ण

अटल व्योम cptpf_enable_vf_flr_पूर्णांकrs(काष्ठा otx2_cptpf_dev *cptpf)
अणु
	/* Clear पूर्णांकerrupt अगर any */
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0, RVU_PF_VFFLR_INTX(0),
			~0x0ULL);
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0, RVU_PF_VFFLR_INTX(1),
			~0x0ULL);

	/* Enable VF FLR पूर्णांकerrupts */
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0,
			 RVU_PF_VFFLR_INT_ENA_W1SX(0), ~0x0ULL);
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0,
			 RVU_PF_VFFLR_INT_ENA_W1SX(1), ~0x0ULL);
पूर्ण

अटल व्योम cptpf_disable_vf_flr_पूर्णांकrs(काष्ठा otx2_cptpf_dev *cptpf,
				       पूर्णांक num_vfs)
अणु
	पूर्णांक vector;

	/* Disable VF FLR पूर्णांकerrupts */
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0,
			 RVU_PF_VFFLR_INT_ENA_W1CX(0), ~0x0ULL);
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0,
			 RVU_PF_VFFLR_INT_ENA_W1CX(1), ~0x0ULL);

	/* Clear पूर्णांकerrupt अगर any */
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0, RVU_PF_VFFLR_INTX(0),
			 ~0x0ULL);
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0, RVU_PF_VFFLR_INTX(1),
			 ~0x0ULL);

	vector = pci_irq_vector(cptpf->pdev, RVU_PF_INT_VEC_VFFLR0);
	मुक्त_irq(vector, cptpf);

	अगर (num_vfs > 64) अणु
		vector = pci_irq_vector(cptpf->pdev, RVU_PF_INT_VEC_VFFLR1);
		मुक्त_irq(vector, cptpf);
	पूर्ण
पूर्ण

अटल व्योम cptpf_flr_wq_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cptpf_flr_work *flr_work;
	काष्ठा otx2_cptpf_dev *pf;
	काष्ठा mbox_msghdr *req;
	काष्ठा otx2_mbox *mbox;
	पूर्णांक vf, reg = 0;

	flr_work = container_of(work, काष्ठा cptpf_flr_work, work);
	pf = flr_work->pf;
	mbox = &pf->afpf_mbox;

	vf = flr_work - pf->flr_work;

	req = otx2_mbox_alloc_msg_rsp(mbox, 0, माप(*req),
				      माप(काष्ठा msg_rsp));
	अगर (!req)
		वापस;

	req->sig = OTX2_MBOX_REQ_SIG;
	req->id = MBOX_MSG_VF_FLR;
	req->pcअगरunc &= RVU_PFVF_FUNC_MASK;
	req->pcअगरunc |= (vf + 1) & RVU_PFVF_FUNC_MASK;

	otx2_cpt_send_mbox_msg(mbox, pf->pdev);

	अगर (vf >= 64) अणु
		reg = 1;
		vf = vf - 64;
	पूर्ण
	/* Clear transaction pending रेजिस्टर */
	otx2_cpt_ग_लिखो64(pf->reg_base, BLKADDR_RVUM, 0,
			 RVU_PF_VFTRPENDX(reg), BIT_ULL(vf));
	otx2_cpt_ग_लिखो64(pf->reg_base, BLKADDR_RVUM, 0,
			 RVU_PF_VFFLR_INT_ENA_W1SX(reg), BIT_ULL(vf));
पूर्ण

अटल irqवापस_t cptpf_vf_flr_पूर्णांकr(पूर्णांक __always_unused irq, व्योम *arg)
अणु
	पूर्णांक reg, dev, vf, start_vf, num_reg = 1;
	काष्ठा otx2_cptpf_dev *cptpf = arg;
	u64 पूर्णांकr;

	अगर (cptpf->max_vfs > 64)
		num_reg = 2;

	क्रम (reg = 0; reg < num_reg; reg++) अणु
		पूर्णांकr = otx2_cpt_पढ़ो64(cptpf->reg_base, BLKADDR_RVUM, 0,
				       RVU_PF_VFFLR_INTX(reg));
		अगर (!पूर्णांकr)
			जारी;
		start_vf = 64 * reg;
		क्रम (vf = 0; vf < 64; vf++) अणु
			अगर (!(पूर्णांकr & BIT_ULL(vf)))
				जारी;
			dev = vf + start_vf;
			queue_work(cptpf->flr_wq, &cptpf->flr_work[dev].work);
			/* Clear पूर्णांकerrupt */
			otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0,
					 RVU_PF_VFFLR_INTX(reg), BIT_ULL(vf));
			/* Disable the पूर्णांकerrupt */
			otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0,
					 RVU_PF_VFFLR_INT_ENA_W1CX(reg),
					 BIT_ULL(vf));
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम cptpf_unरेजिस्टर_vfpf_पूर्णांकr(काष्ठा otx2_cptpf_dev *cptpf,
				       पूर्णांक num_vfs)
अणु
	cptpf_disable_vfpf_mbox_पूर्णांकr(cptpf, num_vfs);
	cptpf_disable_vf_flr_पूर्णांकrs(cptpf, num_vfs);
पूर्ण

अटल पूर्णांक cptpf_रेजिस्टर_vfpf_पूर्णांकr(काष्ठा otx2_cptpf_dev *cptpf, पूर्णांक num_vfs)
अणु
	काष्ठा pci_dev *pdev = cptpf->pdev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret, vector;

	vector = pci_irq_vector(pdev, RVU_PF_INT_VEC_VFPF_MBOX0);
	/* Register VF-PF mailbox पूर्णांकerrupt handler */
	ret = request_irq(vector, otx2_cptpf_vfpf_mbox_पूर्णांकr, 0, "CPTVFPF Mbox0",
			  cptpf);
	अगर (ret) अणु
		dev_err(dev,
			"IRQ registration failed for PFVF mbox0 irq\n");
		वापस ret;
	पूर्ण
	vector = pci_irq_vector(pdev, RVU_PF_INT_VEC_VFFLR0);
	/* Register VF FLR पूर्णांकerrupt handler */
	ret = request_irq(vector, cptpf_vf_flr_पूर्णांकr, 0, "CPTPF FLR0", cptpf);
	अगर (ret) अणु
		dev_err(dev,
			"IRQ registration failed for VFFLR0 irq\n");
		जाओ मुक्त_mbox0_irq;
	पूर्ण
	अगर (num_vfs > 64) अणु
		vector = pci_irq_vector(pdev, RVU_PF_INT_VEC_VFPF_MBOX1);
		ret = request_irq(vector, otx2_cptpf_vfpf_mbox_पूर्णांकr, 0,
				  "CPTVFPF Mbox1", cptpf);
		अगर (ret) अणु
			dev_err(dev,
				"IRQ registration failed for PFVF mbox1 irq\n");
			जाओ मुक्त_flr0_irq;
		पूर्ण
		vector = pci_irq_vector(pdev, RVU_PF_INT_VEC_VFFLR1);
		/* Register VF FLR पूर्णांकerrupt handler */
		ret = request_irq(vector, cptpf_vf_flr_पूर्णांकr, 0, "CPTPF FLR1",
				  cptpf);
		अगर (ret) अणु
			dev_err(dev,
				"IRQ registration failed for VFFLR1 irq\n");
			जाओ मुक्त_mbox1_irq;
		पूर्ण
	पूर्ण
	cptpf_enable_vfpf_mbox_पूर्णांकr(cptpf, num_vfs);
	cptpf_enable_vf_flr_पूर्णांकrs(cptpf);

	वापस 0;

मुक्त_mbox1_irq:
	vector = pci_irq_vector(pdev, RVU_PF_INT_VEC_VFPF_MBOX1);
	मुक्त_irq(vector, cptpf);
मुक्त_flr0_irq:
	vector = pci_irq_vector(pdev, RVU_PF_INT_VEC_VFFLR0);
	मुक्त_irq(vector, cptpf);
मुक्त_mbox0_irq:
	vector = pci_irq_vector(pdev, RVU_PF_INT_VEC_VFPF_MBOX0);
	मुक्त_irq(vector, cptpf);
	वापस ret;
पूर्ण

अटल व्योम cptpf_flr_wq_destroy(काष्ठा otx2_cptpf_dev *pf)
अणु
	अगर (!pf->flr_wq)
		वापस;
	destroy_workqueue(pf->flr_wq);
	pf->flr_wq = शून्य;
	kमुक्त(pf->flr_work);
पूर्ण

अटल पूर्णांक cptpf_flr_wq_init(काष्ठा otx2_cptpf_dev *cptpf, पूर्णांक num_vfs)
अणु
	पूर्णांक vf;

	cptpf->flr_wq = alloc_ordered_workqueue("cptpf_flr_wq", 0);
	अगर (!cptpf->flr_wq)
		वापस -ENOMEM;

	cptpf->flr_work = kसुस्मृति(num_vfs, माप(काष्ठा cptpf_flr_work),
				  GFP_KERNEL);
	अगर (!cptpf->flr_work)
		जाओ destroy_wq;

	क्रम (vf = 0; vf < num_vfs; vf++) अणु
		cptpf->flr_work[vf].pf = cptpf;
		INIT_WORK(&cptpf->flr_work[vf].work, cptpf_flr_wq_handler);
	पूर्ण
	वापस 0;

destroy_wq:
	destroy_workqueue(cptpf->flr_wq);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक cptpf_vfpf_mbox_init(काष्ठा otx2_cptpf_dev *cptpf, पूर्णांक num_vfs)
अणु
	काष्ठा device *dev = &cptpf->pdev->dev;
	u64 vfpf_mbox_base;
	पूर्णांक err, i;

	cptpf->vfpf_mbox_wq = alloc_workqueue("cpt_vfpf_mailbox",
					      WQ_UNBOUND | WQ_HIGHPRI |
					      WQ_MEM_RECLAIM, 1);
	अगर (!cptpf->vfpf_mbox_wq)
		वापस -ENOMEM;

	/* Map VF-PF mailbox memory */
	vfpf_mbox_base = पढ़ोq(cptpf->reg_base + RVU_PF_VF_BAR4_ADDR);
	अगर (!vfpf_mbox_base) अणु
		dev_err(dev, "VF-PF mailbox address not configured\n");
		err = -ENOMEM;
		जाओ मुक्त_wqe;
	पूर्ण
	cptpf->vfpf_mbox_base = devm_ioremap_wc(dev, vfpf_mbox_base,
						MBOX_SIZE * cptpf->max_vfs);
	अगर (!cptpf->vfpf_mbox_base) अणु
		dev_err(dev, "Mapping of VF-PF mailbox address failed\n");
		err = -ENOMEM;
		जाओ मुक्त_wqe;
	पूर्ण
	err = otx2_mbox_init(&cptpf->vfpf_mbox, cptpf->vfpf_mbox_base,
			     cptpf->pdev, cptpf->reg_base, MBOX_सूची_PFVF,
			     num_vfs);
	अगर (err)
		जाओ मुक्त_wqe;

	क्रम (i = 0; i < num_vfs; i++) अणु
		cptpf->vf[i].vf_id = i;
		cptpf->vf[i].cptpf = cptpf;
		cptpf->vf[i].पूर्णांकr_idx = i % 64;
		INIT_WORK(&cptpf->vf[i].vfpf_mbox_work,
			  otx2_cptpf_vfpf_mbox_handler);
	पूर्ण
	वापस 0;

मुक्त_wqe:
	destroy_workqueue(cptpf->vfpf_mbox_wq);
	वापस err;
पूर्ण

अटल व्योम cptpf_vfpf_mbox_destroy(काष्ठा otx2_cptpf_dev *cptpf)
अणु
	destroy_workqueue(cptpf->vfpf_mbox_wq);
	otx2_mbox_destroy(&cptpf->vfpf_mbox);
पूर्ण

अटल व्योम cptpf_disable_afpf_mbox_पूर्णांकr(काष्ठा otx2_cptpf_dev *cptpf)
अणु
	/* Disable AF-PF पूर्णांकerrupt */
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0, RVU_PF_INT_ENA_W1C,
			 0x1ULL);
	/* Clear पूर्णांकerrupt अगर any */
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0, RVU_PF_INT, 0x1ULL);
पूर्ण

अटल पूर्णांक cptpf_रेजिस्टर_afpf_mbox_पूर्णांकr(काष्ठा otx2_cptpf_dev *cptpf)
अणु
	काष्ठा pci_dev *pdev = cptpf->pdev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret, irq;

	irq = pci_irq_vector(pdev, RVU_PF_INT_VEC_AFPF_MBOX);
	/* Register AF-PF mailbox पूर्णांकerrupt handler */
	ret = devm_request_irq(dev, irq, otx2_cptpf_afpf_mbox_पूर्णांकr, 0,
			       "CPTAFPF Mbox", cptpf);
	अगर (ret) अणु
		dev_err(dev,
			"IRQ registration failed for PFAF mbox irq\n");
		वापस ret;
	पूर्ण
	/* Clear पूर्णांकerrupt अगर any, to aव्योम spurious पूर्णांकerrupts */
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0, RVU_PF_INT, 0x1ULL);
	/* Enable AF-PF पूर्णांकerrupt */
	otx2_cpt_ग_लिखो64(cptpf->reg_base, BLKADDR_RVUM, 0, RVU_PF_INT_ENA_W1S,
			 0x1ULL);

	ret = otx2_cpt_send_पढ़ोy_msg(&cptpf->afpf_mbox, cptpf->pdev);
	अगर (ret) अणु
		dev_warn(dev,
			 "AF not responding to mailbox, deferring probe\n");
		cptpf_disable_afpf_mbox_पूर्णांकr(cptpf);
		वापस -EPROBE_DEFER;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cptpf_afpf_mbox_init(काष्ठा otx2_cptpf_dev *cptpf)
अणु
	पूर्णांक err;

	cptpf->afpf_mbox_wq = alloc_workqueue("cpt_afpf_mailbox",
					      WQ_UNBOUND | WQ_HIGHPRI |
					      WQ_MEM_RECLAIM, 1);
	अगर (!cptpf->afpf_mbox_wq)
		वापस -ENOMEM;

	err = otx2_mbox_init(&cptpf->afpf_mbox, cptpf->afpf_mbox_base,
			     cptpf->pdev, cptpf->reg_base, MBOX_सूची_PFAF, 1);
	अगर (err)
		जाओ error;

	INIT_WORK(&cptpf->afpf_mbox_work, otx2_cptpf_afpf_mbox_handler);
	वापस 0;

error:
	destroy_workqueue(cptpf->afpf_mbox_wq);
	वापस err;
पूर्ण

अटल व्योम cptpf_afpf_mbox_destroy(काष्ठा otx2_cptpf_dev *cptpf)
अणु
	destroy_workqueue(cptpf->afpf_mbox_wq);
	otx2_mbox_destroy(&cptpf->afpf_mbox);
पूर्ण

अटल sमाप_प्रकार kvf_limits_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा otx2_cptpf_dev *cptpf = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", cptpf->kvf_limits);
पूर्ण

अटल sमाप_प्रकार kvf_limits_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा otx2_cptpf_dev *cptpf = dev_get_drvdata(dev);
	पूर्णांक lfs_num;

	अगर (kstrtoपूर्णांक(buf, 0, &lfs_num)) अणु
		dev_err(dev, "lfs count %d must be in range [1 - %d]\n",
			lfs_num, num_online_cpus());
		वापस -EINVAL;
	पूर्ण
	अगर (lfs_num < 1 || lfs_num > num_online_cpus()) अणु
		dev_err(dev, "lfs count %d must be in range [1 - %d]\n",
			lfs_num, num_online_cpus());
		वापस -EINVAL;
	पूर्ण
	cptpf->kvf_limits = lfs_num;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(kvf_limits);
अटल काष्ठा attribute *cptpf_attrs[] = अणु
	&dev_attr_kvf_limits.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group cptpf_sysfs_group = अणु
	.attrs = cptpf_attrs,
पूर्ण;

अटल पूर्णांक cpt_is_pf_usable(काष्ठा otx2_cptpf_dev *cptpf)
अणु
	u64 rev;

	rev = otx2_cpt_पढ़ो64(cptpf->reg_base, BLKADDR_RVUM, 0,
			      RVU_PF_BLOCK_ADDRX_DISC(BLKADDR_RVUM));
	rev = (rev >> 12) & 0xFF;
	/*
	 * Check अगर AF has setup revision क्रम RVUM block, otherwise
	 * driver probe should be deferred until AF driver comes up
	 */
	अगर (!rev) अणु
		dev_warn(&cptpf->pdev->dev,
			 "AF is not initialized, deferring probe\n");
		वापस -EPROBE_DEFER;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cptx_device_reset(काष्ठा otx2_cptpf_dev *cptpf, पूर्णांक blkaddr)
अणु
	पूर्णांक समयout = 10, ret;
	u64 reg = 0;

	ret = otx2_cpt_ग_लिखो_af_reg(&cptpf->afpf_mbox, cptpf->pdev,
				    CPT_AF_BLK_RST, 0x1, blkaddr);
	अगर (ret)
		वापस ret;

	करो अणु
		ret = otx2_cpt_पढ़ो_af_reg(&cptpf->afpf_mbox, cptpf->pdev,
					   CPT_AF_BLK_RST, &reg, blkaddr);
		अगर (ret)
			वापस ret;

		अगर (!((reg >> 63) & 0x1))
			अवरोध;

		usleep_range(10000, 20000);
		अगर (समयout-- < 0)
			वापस -EBUSY;
	पूर्ण जबतक (1);

	वापस ret;
पूर्ण

अटल पूर्णांक cptpf_device_reset(काष्ठा otx2_cptpf_dev *cptpf)
अणु
	पूर्णांक ret = 0;

	अगर (cptpf->has_cpt1) अणु
		ret = cptx_device_reset(cptpf, BLKADDR_CPT1);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस cptx_device_reset(cptpf, BLKADDR_CPT0);
पूर्ण

अटल व्योम cptpf_check_block_implemented(काष्ठा otx2_cptpf_dev *cptpf)
अणु
	u64 cfg;

	cfg = otx2_cpt_पढ़ो64(cptpf->reg_base, BLKADDR_RVUM, 0,
			      RVU_PF_BLOCK_ADDRX_DISC(BLKADDR_CPT1));
	अगर (cfg & BIT_ULL(11))
		cptpf->has_cpt1 = true;
पूर्ण

अटल पूर्णांक cptpf_device_init(काष्ठा otx2_cptpf_dev *cptpf)
अणु
	जोड़ otx2_cptx_af_स्थिरants1 af_cnsts1 = अणु0पूर्ण;
	पूर्णांक ret = 0;

	/* check अगर 'implemented' bit is set क्रम block BLKADDR_CPT1 */
	cptpf_check_block_implemented(cptpf);
	/* Reset the CPT PF device */
	ret = cptpf_device_reset(cptpf);
	अगर (ret)
		वापस ret;

	/* Get number of SE, IE and AE engines */
	ret = otx2_cpt_पढ़ो_af_reg(&cptpf->afpf_mbox, cptpf->pdev,
				   CPT_AF_CONSTANTS1, &af_cnsts1.u,
				   BLKADDR_CPT0);
	अगर (ret)
		वापस ret;

	cptpf->eng_grps.avail.max_se_cnt = af_cnsts1.s.se;
	cptpf->eng_grps.avail.max_ie_cnt = af_cnsts1.s.ie;
	cptpf->eng_grps.avail.max_ae_cnt = af_cnsts1.s.ae;

	/* Disable all cores */
	ret = otx2_cpt_disable_all_cores(cptpf);

	वापस ret;
पूर्ण

अटल पूर्णांक cptpf_sriov_disable(काष्ठा pci_dev *pdev)
अणु
	काष्ठा otx2_cptpf_dev *cptpf = pci_get_drvdata(pdev);
	पूर्णांक num_vfs = pci_num_vf(pdev);

	अगर (!num_vfs)
		वापस 0;

	pci_disable_sriov(pdev);
	cptpf_unरेजिस्टर_vfpf_पूर्णांकr(cptpf, num_vfs);
	cptpf_flr_wq_destroy(cptpf);
	cptpf_vfpf_mbox_destroy(cptpf);
	module_put(THIS_MODULE);
	cptpf->enabled_vfs = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक cptpf_sriov_enable(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	काष्ठा otx2_cptpf_dev *cptpf = pci_get_drvdata(pdev);
	पूर्णांक ret;

	/* Initialize VF<=>PF mailbox */
	ret = cptpf_vfpf_mbox_init(cptpf, num_vfs);
	अगर (ret)
		वापस ret;

	ret = cptpf_flr_wq_init(cptpf, num_vfs);
	अगर (ret)
		जाओ destroy_mbox;
	/* Register VF<=>PF mailbox पूर्णांकerrupt */
	ret = cptpf_रेजिस्टर_vfpf_पूर्णांकr(cptpf, num_vfs);
	अगर (ret)
		जाओ destroy_flr;

	/* Get CPT HW capabilities using LOAD_FVC operation. */
	ret = otx2_cpt_discover_eng_capabilities(cptpf);
	अगर (ret)
		जाओ disable_पूर्णांकr;

	ret = otx2_cpt_create_eng_grps(cptpf->pdev, &cptpf->eng_grps);
	अगर (ret)
		जाओ disable_पूर्णांकr;

	cptpf->enabled_vfs = num_vfs;
	ret = pci_enable_sriov(pdev, num_vfs);
	अगर (ret)
		जाओ disable_पूर्णांकr;

	dev_notice(&cptpf->pdev->dev, "VFs enabled: %d\n", num_vfs);

	try_module_get(THIS_MODULE);
	वापस num_vfs;

disable_पूर्णांकr:
	cptpf_unरेजिस्टर_vfpf_पूर्णांकr(cptpf, num_vfs);
	cptpf->enabled_vfs = 0;
destroy_flr:
	cptpf_flr_wq_destroy(cptpf);
destroy_mbox:
	cptpf_vfpf_mbox_destroy(cptpf);
	वापस ret;
पूर्ण

अटल पूर्णांक otx2_cptpf_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	अगर (num_vfs > 0) अणु
		वापस cptpf_sriov_enable(pdev, num_vfs);
	पूर्ण अन्यथा अणु
		वापस cptpf_sriov_disable(pdev);
	पूर्ण
पूर्ण

अटल पूर्णांक otx2_cptpf_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	resource_माप_प्रकार offset, size;
	काष्ठा otx2_cptpf_dev *cptpf;
	पूर्णांक err;

	cptpf = devm_kzalloc(dev, माप(*cptpf), GFP_KERNEL);
	अगर (!cptpf)
		वापस -ENOMEM;

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device\n");
		जाओ clear_drvdata;
	पूर्ण

	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(48));
	अगर (err) अणु
		dev_err(dev, "Unable to get usable DMA configuration\n");
		जाओ clear_drvdata;
	पूर्ण
	/* Map PF's configuration रेजिस्टरs */
	err = pcim_iomap_regions_request_all(pdev, 1 << PCI_PF_REG_BAR_NUM,
					     OTX2_CPT_DRV_NAME);
	अगर (err) अणु
		dev_err(dev, "Couldn't get PCI resources 0x%x\n", err);
		जाओ clear_drvdata;
	पूर्ण
	pci_set_master(pdev);
	pci_set_drvdata(pdev, cptpf);
	cptpf->pdev = pdev;

	cptpf->reg_base = pcim_iomap_table(pdev)[PCI_PF_REG_BAR_NUM];

	/* Check अगर AF driver is up, otherwise defer probe */
	err = cpt_is_pf_usable(cptpf);
	अगर (err)
		जाओ clear_drvdata;

	offset = pci_resource_start(pdev, PCI_MBOX_BAR_NUM);
	size = pci_resource_len(pdev, PCI_MBOX_BAR_NUM);
	/* Map AF-PF mailbox memory */
	cptpf->afpf_mbox_base = devm_ioremap_wc(dev, offset, size);
	अगर (!cptpf->afpf_mbox_base) अणु
		dev_err(&pdev->dev, "Unable to map BAR4\n");
		err = -ENODEV;
		जाओ clear_drvdata;
	पूर्ण
	err = pci_alloc_irq_vectors(pdev, RVU_PF_INT_VEC_CNT,
				    RVU_PF_INT_VEC_CNT, PCI_IRQ_MSIX);
	अगर (err < 0) अणु
		dev_err(dev, "Request for %d msix vectors failed\n",
			RVU_PF_INT_VEC_CNT);
		जाओ clear_drvdata;
	पूर्ण
	/* Initialize AF-PF mailbox */
	err = cptpf_afpf_mbox_init(cptpf);
	अगर (err)
		जाओ clear_drvdata;
	/* Register mailbox पूर्णांकerrupt */
	err = cptpf_रेजिस्टर_afpf_mbox_पूर्णांकr(cptpf);
	अगर (err)
		जाओ destroy_afpf_mbox;

	cptpf->max_vfs = pci_sriov_get_totalvfs(pdev);

	/* Initialize CPT PF device */
	err = cptpf_device_init(cptpf);
	अगर (err)
		जाओ unरेजिस्टर_पूर्णांकr;

	/* Initialize engine groups */
	err = otx2_cpt_init_eng_grps(pdev, &cptpf->eng_grps);
	अगर (err)
		जाओ unरेजिस्टर_पूर्णांकr;

	err = sysfs_create_group(&dev->kobj, &cptpf_sysfs_group);
	अगर (err)
		जाओ cleanup_eng_grps;
	वापस 0;

cleanup_eng_grps:
	otx2_cpt_cleanup_eng_grps(pdev, &cptpf->eng_grps);
unरेजिस्टर_पूर्णांकr:
	cptpf_disable_afpf_mbox_पूर्णांकr(cptpf);
destroy_afpf_mbox:
	cptpf_afpf_mbox_destroy(cptpf);
clear_drvdata:
	pci_set_drvdata(pdev, शून्य);
	वापस err;
पूर्ण

अटल व्योम otx2_cptpf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा otx2_cptpf_dev *cptpf = pci_get_drvdata(pdev);

	अगर (!cptpf)
		वापस;

	cptpf_sriov_disable(pdev);
	/* Delete sysfs entry created क्रम kernel VF limits */
	sysfs_हटाओ_group(&pdev->dev.kobj, &cptpf_sysfs_group);
	/* Cleanup engine groups */
	otx2_cpt_cleanup_eng_grps(pdev, &cptpf->eng_grps);
	/* Disable AF-PF mailbox पूर्णांकerrupt */
	cptpf_disable_afpf_mbox_पूर्णांकr(cptpf);
	/* Destroy AF-PF mbox */
	cptpf_afpf_mbox_destroy(cptpf);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id otx2_cpt_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, OTX2_CPT_PCI_PF_DEVICE_ID) पूर्ण,
	अणु 0, पूर्ण  /* end of table */
पूर्ण;

अटल काष्ठा pci_driver otx2_cpt_pci_driver = अणु
	.name = OTX2_CPT_DRV_NAME,
	.id_table = otx2_cpt_id_table,
	.probe = otx2_cptpf_probe,
	.हटाओ = otx2_cptpf_हटाओ,
	.sriov_configure = otx2_cptpf_sriov_configure
पूर्ण;

module_pci_driver(otx2_cpt_pci_driver);

MODULE_AUTHOR("Marvell");
MODULE_DESCRIPTION(OTX2_CPT_DRV_STRING);
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(pci, otx2_cpt_id_table);
