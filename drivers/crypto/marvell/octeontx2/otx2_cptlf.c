<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2020 Marvell. */

#समावेश "otx2_cpt_common.h"
#समावेश "otx2_cptlf.h"
#समावेश "rvu_reg.h"

#घोषणा CPT_TIMER_HOLD 0x03F
#घोषणा CPT_COUNT_HOLD 32

अटल व्योम cptlf_करो_set_करोne_समय_रुको(काष्ठा otx2_cptlf_info *lf,
					पूर्णांक समय_रुको)
अणु
	जोड़ otx2_cptx_lf_करोne_रुको करोne_रुको;

	करोne_रुको.u = otx2_cpt_पढ़ो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
				      OTX2_CPT_LF_DONE_WAIT);
	करोne_रुको.s.समय_रुको = समय_रुको;
	otx2_cpt_ग_लिखो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
			 OTX2_CPT_LF_DONE_WAIT, करोne_रुको.u);
पूर्ण

अटल व्योम cptlf_करो_set_करोne_num_रुको(काष्ठा otx2_cptlf_info *lf, पूर्णांक num_रुको)
अणु
	जोड़ otx2_cptx_lf_करोne_रुको करोne_रुको;

	करोne_रुको.u = otx2_cpt_पढ़ो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
				      OTX2_CPT_LF_DONE_WAIT);
	करोne_रुको.s.num_रुको = num_रुको;
	otx2_cpt_ग_लिखो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
			 OTX2_CPT_LF_DONE_WAIT, करोne_रुको.u);
पूर्ण

अटल व्योम cptlf_set_करोne_समय_रुको(काष्ठा otx2_cptlfs_info *lfs,
				     पूर्णांक समय_रुको)
अणु
	पूर्णांक slot;

	क्रम (slot = 0; slot < lfs->lfs_num; slot++)
		cptlf_करो_set_करोne_समय_रुको(&lfs->lf[slot], समय_रुको);
पूर्ण

अटल व्योम cptlf_set_करोne_num_रुको(काष्ठा otx2_cptlfs_info *lfs, पूर्णांक num_रुको)
अणु
	पूर्णांक slot;

	क्रम (slot = 0; slot < lfs->lfs_num; slot++)
		cptlf_करो_set_करोne_num_रुको(&lfs->lf[slot], num_रुको);
पूर्ण

अटल पूर्णांक cptlf_set_pri(काष्ठा otx2_cptlf_info *lf, पूर्णांक pri)
अणु
	काष्ठा otx2_cptlfs_info *lfs = lf->lfs;
	जोड़ otx2_cptx_af_lf_ctrl lf_ctrl;
	पूर्णांक ret;

	ret = otx2_cpt_पढ़ो_af_reg(lfs->mbox, lfs->pdev,
				   CPT_AF_LFX_CTL(lf->slot),
				   &lf_ctrl.u, lfs->blkaddr);
	अगर (ret)
		वापस ret;

	lf_ctrl.s.pri = pri ? 1 : 0;

	ret = otx2_cpt_ग_लिखो_af_reg(lfs->mbox, lfs->pdev,
				    CPT_AF_LFX_CTL(lf->slot),
				    lf_ctrl.u, lfs->blkaddr);
	वापस ret;
पूर्ण

अटल पूर्णांक cptlf_set_eng_grps_mask(काष्ठा otx2_cptlf_info *lf,
				   पूर्णांक eng_grps_mask)
अणु
	काष्ठा otx2_cptlfs_info *lfs = lf->lfs;
	जोड़ otx2_cptx_af_lf_ctrl lf_ctrl;
	पूर्णांक ret;

	ret = otx2_cpt_पढ़ो_af_reg(lfs->mbox, lfs->pdev,
				   CPT_AF_LFX_CTL(lf->slot),
				   &lf_ctrl.u, lfs->blkaddr);
	अगर (ret)
		वापस ret;

	lf_ctrl.s.grp = eng_grps_mask;

	ret = otx2_cpt_ग_लिखो_af_reg(lfs->mbox, lfs->pdev,
				    CPT_AF_LFX_CTL(lf->slot),
				    lf_ctrl.u, lfs->blkaddr);
	वापस ret;
पूर्ण

अटल पूर्णांक cptlf_set_grp_and_pri(काष्ठा otx2_cptlfs_info *lfs,
				 पूर्णांक eng_grp_mask, पूर्णांक pri)
अणु
	पूर्णांक slot, ret = 0;

	क्रम (slot = 0; slot < lfs->lfs_num; slot++) अणु
		ret = cptlf_set_pri(&lfs->lf[slot], pri);
		अगर (ret)
			वापस ret;

		ret = cptlf_set_eng_grps_mask(&lfs->lf[slot], eng_grp_mask);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम cptlf_hw_init(काष्ठा otx2_cptlfs_info *lfs)
अणु
	/* Disable inकाष्ठाion queues */
	otx2_cptlf_disable_iqueues(lfs);

	/* Set inकाष्ठाion queues base addresses */
	otx2_cptlf_set_iqueues_base_addr(lfs);

	/* Set inकाष्ठाion queues sizes */
	otx2_cptlf_set_iqueues_size(lfs);

	/* Set करोne पूर्णांकerrupts समय रुको */
	cptlf_set_करोne_समय_रुको(lfs, CPT_TIMER_HOLD);

	/* Set करोne पूर्णांकerrupts num रुको */
	cptlf_set_करोne_num_रुको(lfs, CPT_COUNT_HOLD);

	/* Enable inकाष्ठाion queues */
	otx2_cptlf_enable_iqueues(lfs);
पूर्ण

अटल व्योम cptlf_hw_cleanup(काष्ठा otx2_cptlfs_info *lfs)
अणु
	/* Disable inकाष्ठाion queues */
	otx2_cptlf_disable_iqueues(lfs);
पूर्ण

अटल व्योम cptlf_set_misc_पूर्णांकrs(काष्ठा otx2_cptlfs_info *lfs, u8 enable)
अणु
	जोड़ otx2_cptx_lf_misc_पूर्णांक_ena_w1s irq_misc = अणु .u = 0x0 पूर्ण;
	u64 reg = enable ? OTX2_CPT_LF_MISC_INT_ENA_W1S :
			   OTX2_CPT_LF_MISC_INT_ENA_W1C;
	पूर्णांक slot;

	irq_misc.s.fault = 0x1;
	irq_misc.s.hwerr = 0x1;
	irq_misc.s.irde = 0x1;
	irq_misc.s.nqerr = 0x1;
	irq_misc.s.nwrp = 0x1;

	क्रम (slot = 0; slot < lfs->lfs_num; slot++)
		otx2_cpt_ग_लिखो64(lfs->reg_base, BLKADDR_CPT0, slot, reg,
				 irq_misc.u);
पूर्ण

अटल व्योम cptlf_enable_पूर्णांकrs(काष्ठा otx2_cptlfs_info *lfs)
अणु
	पूर्णांक slot;

	/* Enable करोne पूर्णांकerrupts */
	क्रम (slot = 0; slot < lfs->lfs_num; slot++)
		otx2_cpt_ग_लिखो64(lfs->reg_base, BLKADDR_CPT0, slot,
				 OTX2_CPT_LF_DONE_INT_ENA_W1S, 0x1);
	/* Enable Misc पूर्णांकerrupts */
	cptlf_set_misc_पूर्णांकrs(lfs, true);
पूर्ण

अटल व्योम cptlf_disable_पूर्णांकrs(काष्ठा otx2_cptlfs_info *lfs)
अणु
	पूर्णांक slot;

	क्रम (slot = 0; slot < lfs->lfs_num; slot++)
		otx2_cpt_ग_लिखो64(lfs->reg_base, BLKADDR_CPT0, slot,
				 OTX2_CPT_LF_DONE_INT_ENA_W1C, 0x1);
	cptlf_set_misc_पूर्णांकrs(lfs, false);
पूर्ण

अटल अंतरभूत पूर्णांक cptlf_पढ़ो_करोne_cnt(काष्ठा otx2_cptlf_info *lf)
अणु
	जोड़ otx2_cptx_lf_करोne irq_cnt;

	irq_cnt.u = otx2_cpt_पढ़ो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
				    OTX2_CPT_LF_DONE);
	वापस irq_cnt.s.करोne;
पूर्ण

अटल irqवापस_t cptlf_misc_पूर्णांकr_handler(पूर्णांक __always_unused irq, व्योम *arg)
अणु
	जोड़ otx2_cptx_lf_misc_पूर्णांक irq_misc, irq_misc_ack;
	काष्ठा otx2_cptlf_info *lf = arg;
	काष्ठा device *dev;

	dev = &lf->lfs->pdev->dev;
	irq_misc.u = otx2_cpt_पढ़ो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
				     OTX2_CPT_LF_MISC_INT);
	irq_misc_ack.u = 0x0;

	अगर (irq_misc.s.fault) अणु
		dev_err(dev, "Memory error detected while executing CPT_INST_S, LF %d.\n",
			lf->slot);
		irq_misc_ack.s.fault = 0x1;

	पूर्ण अन्यथा अगर (irq_misc.s.hwerr) अणु
		dev_err(dev, "HW error from an engine executing CPT_INST_S, LF %d.",
			lf->slot);
		irq_misc_ack.s.hwerr = 0x1;

	पूर्ण अन्यथा अगर (irq_misc.s.nwrp) अणु
		dev_err(dev, "SMMU fault while writing CPT_RES_S to CPT_INST_S[RES_ADDR], LF %d.\n",
			lf->slot);
		irq_misc_ack.s.nwrp = 0x1;

	पूर्ण अन्यथा अगर (irq_misc.s.irde) अणु
		dev_err(dev, "Memory error when accessing instruction memory queue CPT_LF_Q_BASE[ADDR].\n");
		irq_misc_ack.s.irde = 0x1;

	पूर्ण अन्यथा अगर (irq_misc.s.nqerr) अणु
		dev_err(dev, "Error enqueuing an instruction received at CPT_LF_NQ.\n");
		irq_misc_ack.s.nqerr = 0x1;

	पूर्ण अन्यथा अणु
		dev_err(dev, "Unhandled interrupt in CPT LF %d\n", lf->slot);
		वापस IRQ_NONE;
	पूर्ण

	/* Acknowledge पूर्णांकerrupts */
	otx2_cpt_ग_लिखो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
			 OTX2_CPT_LF_MISC_INT, irq_misc_ack.u);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t cptlf_करोne_पूर्णांकr_handler(पूर्णांक irq, व्योम *arg)
अणु
	जोड़ otx2_cptx_lf_करोne_रुको करोne_रुको;
	काष्ठा otx2_cptlf_info *lf = arg;
	पूर्णांक irq_cnt;

	/* Read the number of completed requests */
	irq_cnt = cptlf_पढ़ो_करोne_cnt(lf);
	अगर (irq_cnt) अणु
		करोne_रुको.u = otx2_cpt_पढ़ो64(lf->lfs->reg_base, BLKADDR_CPT0,
					      lf->slot, OTX2_CPT_LF_DONE_WAIT);
		/* Acknowledge the number of completed requests */
		otx2_cpt_ग_लिखो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
				 OTX2_CPT_LF_DONE_ACK, irq_cnt);

		otx2_cpt_ग_लिखो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
				 OTX2_CPT_LF_DONE_WAIT, करोne_रुको.u);
		अगर (unlikely(!lf->wqe)) अणु
			dev_err(&lf->lfs->pdev->dev, "No work for LF %d\n",
				lf->slot);
			वापस IRQ_NONE;
		पूर्ण

		/* Schedule processing of completed requests */
		tasklet_hi_schedule(&lf->wqe->work);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

व्योम otx2_cptlf_unरेजिस्टर_पूर्णांकerrupts(काष्ठा otx2_cptlfs_info *lfs)
अणु
	पूर्णांक i, offs, vector;

	क्रम (i = 0; i < lfs->lfs_num; i++) अणु
		क्रम (offs = 0; offs < OTX2_CPT_LF_MSIX_VECTORS; offs++) अणु
			अगर (!lfs->lf[i].is_irq_reg[offs])
				जारी;

			vector = pci_irq_vector(lfs->pdev,
						lfs->lf[i].msix_offset + offs);
			मुक्त_irq(vector, &lfs->lf[i]);
			lfs->lf[i].is_irq_reg[offs] = false;
		पूर्ण
	पूर्ण
	cptlf_disable_पूर्णांकrs(lfs);
पूर्ण

अटल पूर्णांक cptlf_करो_रेजिस्टर_पूर्णांकerrrupts(काष्ठा otx2_cptlfs_info *lfs,
					 पूर्णांक lf_num, पूर्णांक irq_offset,
					 irq_handler_t handler)
अणु
	पूर्णांक ret, vector;

	vector = pci_irq_vector(lfs->pdev, lfs->lf[lf_num].msix_offset +
				irq_offset);
	ret = request_irq(vector, handler, 0,
			  lfs->lf[lf_num].irq_name[irq_offset],
			  &lfs->lf[lf_num]);
	अगर (ret)
		वापस ret;

	lfs->lf[lf_num].is_irq_reg[irq_offset] = true;

	वापस ret;
पूर्ण

पूर्णांक otx2_cptlf_रेजिस्टर_पूर्णांकerrupts(काष्ठा otx2_cptlfs_info *lfs)
अणु
	पूर्णांक irq_offs, ret, i;

	क्रम (i = 0; i < lfs->lfs_num; i++) अणु
		irq_offs = OTX2_CPT_LF_INT_VEC_E_MISC;
		snम_लिखो(lfs->lf[i].irq_name[irq_offs], 32, "CPTLF Misc%d", i);
		ret = cptlf_करो_रेजिस्टर_पूर्णांकerrrupts(lfs, i, irq_offs,
						    cptlf_misc_पूर्णांकr_handler);
		अगर (ret)
			जाओ मुक्त_irq;

		irq_offs = OTX2_CPT_LF_INT_VEC_E_DONE;
		snम_लिखो(lfs->lf[i].irq_name[irq_offs], 32, "OTX2_CPTLF Done%d",
			 i);
		ret = cptlf_करो_रेजिस्टर_पूर्णांकerrrupts(lfs, i, irq_offs,
						    cptlf_करोne_पूर्णांकr_handler);
		अगर (ret)
			जाओ मुक्त_irq;
	पूर्ण
	cptlf_enable_पूर्णांकrs(lfs);
	वापस 0;

मुक्त_irq:
	otx2_cptlf_unरेजिस्टर_पूर्णांकerrupts(lfs);
	वापस ret;
पूर्ण

व्योम otx2_cptlf_मुक्त_irqs_affinity(काष्ठा otx2_cptlfs_info *lfs)
अणु
	पूर्णांक slot, offs;

	क्रम (slot = 0; slot < lfs->lfs_num; slot++) अणु
		क्रम (offs = 0; offs < OTX2_CPT_LF_MSIX_VECTORS; offs++)
			irq_set_affinity_hपूर्णांक(pci_irq_vector(lfs->pdev,
					      lfs->lf[slot].msix_offset +
					      offs), शून्य);
		मुक्त_cpumask_var(lfs->lf[slot].affinity_mask);
	पूर्ण
पूर्ण

पूर्णांक otx2_cptlf_set_irqs_affinity(काष्ठा otx2_cptlfs_info *lfs)
अणु
	काष्ठा otx2_cptlf_info *lf = lfs->lf;
	पूर्णांक slot, offs, ret;

	क्रम (slot = 0; slot < lfs->lfs_num; slot++) अणु
		अगर (!zalloc_cpumask_var(&lf[slot].affinity_mask, GFP_KERNEL)) अणु
			dev_err(&lfs->pdev->dev,
				"cpumask allocation failed for LF %d", slot);
			ret = -ENOMEM;
			जाओ मुक्त_affinity_mask;
		पूर्ण

		cpumask_set_cpu(cpumask_local_spपढ़ो(slot,
				dev_to_node(&lfs->pdev->dev)),
				lf[slot].affinity_mask);

		क्रम (offs = 0; offs < OTX2_CPT_LF_MSIX_VECTORS; offs++) अणु
			ret = irq_set_affinity_hपूर्णांक(pci_irq_vector(lfs->pdev,
						lf[slot].msix_offset + offs),
						lf[slot].affinity_mask);
			अगर (ret)
				जाओ मुक्त_affinity_mask;
		पूर्ण
	पूर्ण
	वापस 0;

मुक्त_affinity_mask:
	otx2_cptlf_मुक्त_irqs_affinity(lfs);
	वापस ret;
पूर्ण

पूर्णांक otx2_cptlf_init(काष्ठा otx2_cptlfs_info *lfs, u8 eng_grp_mask, पूर्णांक pri,
		    पूर्णांक lfs_num)
अणु
	पूर्णांक slot, ret;

	अगर (!lfs->pdev || !lfs->reg_base)
		वापस -EINVAL;

	lfs->lfs_num = lfs_num;
	क्रम (slot = 0; slot < lfs->lfs_num; slot++) अणु
		lfs->lf[slot].lfs = lfs;
		lfs->lf[slot].slot = slot;
		lfs->lf[slot].lmtline = lfs->reg_base +
			OTX2_CPT_RVU_FUNC_ADDR_S(BLKADDR_LMT, slot,
						 OTX2_CPT_LMT_LF_LMTLINEX(0));
		lfs->lf[slot].ioreg = lfs->reg_base +
			OTX2_CPT_RVU_FUNC_ADDR_S(BLKADDR_CPT0, slot,
						 OTX2_CPT_LF_NQX(0));
	पूर्ण
	/* Send request to attach LFs */
	ret = otx2_cpt_attach_rscrs_msg(lfs);
	अगर (ret)
		जाओ clear_lfs_num;

	ret = otx2_cpt_alloc_inकाष्ठाion_queues(lfs);
	अगर (ret) अणु
		dev_err(&lfs->pdev->dev,
			"Allocating instruction queues failed\n");
		जाओ detach_rsrcs;
	पूर्ण
	cptlf_hw_init(lfs);
	/*
	 * Allow each LF to execute requests destined to any of 8 engine
	 * groups and set queue priority of each LF to high
	 */
	ret = cptlf_set_grp_and_pri(lfs, eng_grp_mask, pri);
	अगर (ret)
		जाओ मुक्त_iq;

	वापस 0;

मुक्त_iq:
	otx2_cpt_मुक्त_inकाष्ठाion_queues(lfs);
	cptlf_hw_cleanup(lfs);
detach_rsrcs:
	otx2_cpt_detach_rsrcs_msg(lfs);
clear_lfs_num:
	lfs->lfs_num = 0;
	वापस ret;
पूर्ण

व्योम otx2_cptlf_shutकरोwn(काष्ठा otx2_cptlfs_info *lfs)
अणु
	lfs->lfs_num = 0;
	/* Cleanup LFs hardware side */
	cptlf_hw_cleanup(lfs);
	/* Send request to detach LFs */
	otx2_cpt_detach_rsrcs_msg(lfs);
पूर्ण
