<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 * Copyright (C) 2020 Marvell.
 */
#अगर_अघोषित __OTX2_CPTLF_H
#घोषणा __OTX2_CPTLF_H

#समावेश <linux/soc/marvell/octeontx2/यंत्र.h>
#समावेश <mbox.h>
#समावेश <rvu.h>
#समावेश "otx2_cpt_common.h"
#समावेश "otx2_cpt_reqmgr.h"

/*
 * CPT inकाष्ठाion and pending queues user requested length in CPT_INST_S msgs
 */
#घोषणा OTX2_CPT_USER_REQUESTED_QLEN_MSGS 8200

/*
 * CPT inकाष्ठाion queue size passed to HW is in units of 40*CPT_INST_S
 * messages.
 */
#घोषणा OTX2_CPT_SIZE_DIV40 (OTX2_CPT_USER_REQUESTED_QLEN_MSGS/40)

/*
 * CPT inकाष्ठाion and pending queues length in CPT_INST_S messages
 */
#घोषणा OTX2_CPT_INST_QLEN_MSGS	((OTX2_CPT_SIZE_DIV40 - 1) * 40)

/* CPT inकाष्ठाion queue length in bytes */
#घोषणा OTX2_CPT_INST_QLEN_BYTES (OTX2_CPT_SIZE_DIV40 * 40 * \
				  OTX2_CPT_INST_SIZE)

/* CPT inकाष्ठाion group queue length in bytes */
#घोषणा OTX2_CPT_INST_GRP_QLEN_BYTES (OTX2_CPT_SIZE_DIV40 * 16)

/* CPT FC length in bytes */
#घोषणा OTX2_CPT_Q_FC_LEN 128

/* CPT inकाष्ठाion queue alignment */
#घोषणा OTX2_CPT_INST_Q_ALIGNMENT  128

/* Mask which selects all engine groups */
#घोषणा OTX2_CPT_ALL_ENG_GRPS_MASK 0xFF

/* Maximum LFs supported in OcteonTX2 क्रम CPT */
#घोषणा OTX2_CPT_MAX_LFS_NUM    64

/* Queue priority */
#घोषणा OTX2_CPT_QUEUE_HI_PRIO  0x1
#घोषणा OTX2_CPT_QUEUE_LOW_PRIO 0x0

क्रमागत otx2_cptlf_state अणु
	OTX2_CPTLF_IN_RESET,
	OTX2_CPTLF_STARTED,
पूर्ण;

काष्ठा otx2_cpt_inst_queue अणु
	u8 *vaddr;
	u8 *real_vaddr;
	dma_addr_t dma_addr;
	dma_addr_t real_dma_addr;
	u32 size;
पूर्ण;

काष्ठा otx2_cptlfs_info;
काष्ठा otx2_cptlf_wqe अणु
	काष्ठा tasklet_काष्ठा work;
	काष्ठा otx2_cptlfs_info *lfs;
	u8 lf_num;
पूर्ण;

काष्ठा otx2_cptlf_info अणु
	काष्ठा otx2_cptlfs_info *lfs;           /* Ptr to cptlfs_info काष्ठा */
	व्योम __iomem *lmtline;                  /* Address of LMTLINE */
	व्योम __iomem *ioreg;                    /* LMTLINE send रेजिस्टर */
	पूर्णांक msix_offset;                        /* MSI-X पूर्णांकerrupts offset */
	cpumask_var_t affinity_mask;            /* IRQs affinity mask */
	u8 irq_name[OTX2_CPT_LF_MSIX_VECTORS][32];/* Interrupts name */
	u8 is_irq_reg[OTX2_CPT_LF_MSIX_VECTORS];  /* Is पूर्णांकerrupt रेजिस्टरed */
	u8 slot;                                /* Slot number of this LF */

	काष्ठा otx2_cpt_inst_queue iqueue;/* Inकाष्ठाion queue */
	काष्ठा otx2_cpt_pending_queue pqueue; /* Pending queue */
	काष्ठा otx2_cptlf_wqe *wqe;       /* Tasklet work info */
पूर्ण;

काष्ठा otx2_cptlfs_info अणु
	/* Registers start address of VF/PF LFs are attached to */
	व्योम __iomem *reg_base;
	काष्ठा pci_dev *pdev;   /* Device LFs are attached to */
	काष्ठा otx2_cptlf_info lf[OTX2_CPT_MAX_LFS_NUM];
	काष्ठा otx2_mbox *mbox;
	u8 are_lfs_attached;	/* Whether CPT LFs are attached */
	u8 lfs_num;		/* Number of CPT LFs */
	u8 kcrypto_eng_grp_num;	/* Kernel crypto engine group number */
	u8 kvf_limits;          /* Kernel crypto limits */
	atomic_t state;         /* LF's state. started/reset */
	पूर्णांक blkaddr;            /* CPT blkaddr: BLKADDR_CPT0/BLKADDR_CPT1 */
पूर्ण;

अटल अंतरभूत व्योम otx2_cpt_मुक्त_inकाष्ठाion_queues(
					काष्ठा otx2_cptlfs_info *lfs)
अणु
	काष्ठा otx2_cpt_inst_queue *iq;
	पूर्णांक i;

	क्रम (i = 0; i < lfs->lfs_num; i++) अणु
		iq = &lfs->lf[i].iqueue;
		अगर (iq->real_vaddr)
			dma_मुक्त_coherent(&lfs->pdev->dev,
					  iq->size,
					  iq->real_vaddr,
					  iq->real_dma_addr);
		iq->real_vaddr = शून्य;
		iq->vaddr = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक otx2_cpt_alloc_inकाष्ठाion_queues(
					काष्ठा otx2_cptlfs_info *lfs)
अणु
	काष्ठा otx2_cpt_inst_queue *iq;
	पूर्णांक ret = 0, i;

	अगर (!lfs->lfs_num)
		वापस -EINVAL;

	क्रम (i = 0; i < lfs->lfs_num; i++) अणु
		iq = &lfs->lf[i].iqueue;
		iq->size = OTX2_CPT_INST_QLEN_BYTES +
			   OTX2_CPT_Q_FC_LEN +
			   OTX2_CPT_INST_GRP_QLEN_BYTES +
			   OTX2_CPT_INST_Q_ALIGNMENT;
		iq->real_vaddr = dma_alloc_coherent(&lfs->pdev->dev, iq->size,
					&iq->real_dma_addr, GFP_KERNEL);
		अगर (!iq->real_vaddr) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण
		iq->vaddr = iq->real_vaddr + OTX2_CPT_INST_GRP_QLEN_BYTES;
		iq->dma_addr = iq->real_dma_addr + OTX2_CPT_INST_GRP_QLEN_BYTES;

		/* Align poपूर्णांकers */
		iq->vaddr = PTR_ALIGN(iq->vaddr, OTX2_CPT_INST_Q_ALIGNMENT);
		iq->dma_addr = PTR_ALIGN(iq->dma_addr,
					 OTX2_CPT_INST_Q_ALIGNMENT);
	पूर्ण
	वापस 0;

error:
	otx2_cpt_मुक्त_inकाष्ठाion_queues(lfs);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम otx2_cptlf_set_iqueues_base_addr(
					काष्ठा otx2_cptlfs_info *lfs)
अणु
	जोड़ otx2_cptx_lf_q_base lf_q_base;
	पूर्णांक slot;

	क्रम (slot = 0; slot < lfs->lfs_num; slot++) अणु
		lf_q_base.u = lfs->lf[slot].iqueue.dma_addr;
		otx2_cpt_ग_लिखो64(lfs->reg_base, BLKADDR_CPT0, slot,
				 OTX2_CPT_LF_Q_BASE, lf_q_base.u);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम otx2_cptlf_करो_set_iqueue_size(काष्ठा otx2_cptlf_info *lf)
अणु
	जोड़ otx2_cptx_lf_q_size lf_q_size = अणु .u = 0x0 पूर्ण;

	lf_q_size.s.size_भाग40 = OTX2_CPT_SIZE_DIV40;
	otx2_cpt_ग_लिखो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
			 OTX2_CPT_LF_Q_SIZE, lf_q_size.u);
पूर्ण

अटल अंतरभूत व्योम otx2_cptlf_set_iqueues_size(काष्ठा otx2_cptlfs_info *lfs)
अणु
	पूर्णांक slot;

	क्रम (slot = 0; slot < lfs->lfs_num; slot++)
		otx2_cptlf_करो_set_iqueue_size(&lfs->lf[slot]);
पूर्ण

अटल अंतरभूत व्योम otx2_cptlf_करो_disable_iqueue(काष्ठा otx2_cptlf_info *lf)
अणु
	जोड़ otx2_cptx_lf_ctl lf_ctl = अणु .u = 0x0 पूर्ण;
	जोड़ otx2_cptx_lf_inprog lf_inprog;
	पूर्णांक समयout = 20;

	/* Disable inकाष्ठाions enqueuing */
	otx2_cpt_ग_लिखो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
			 OTX2_CPT_LF_CTL, lf_ctl.u);

	/* Wait क्रम inकाष्ठाion queue to become empty */
	करो अणु
		lf_inprog.u = otx2_cpt_पढ़ो64(lf->lfs->reg_base, BLKADDR_CPT0,
					      lf->slot, OTX2_CPT_LF_INPROG);
		अगर (!lf_inprog.s.inflight)
			अवरोध;

		usleep_range(10000, 20000);
		अगर (समयout-- < 0) अणु
			dev_err(&lf->lfs->pdev->dev,
				"Error LF %d is still busy.\n", lf->slot);
			अवरोध;
		पूर्ण

	पूर्ण जबतक (1);

	/*
	 * Disable executions in the LF's queue,
	 * the queue should be empty at this poपूर्णांक
	 */
	lf_inprog.s.eena = 0x0;
	otx2_cpt_ग_लिखो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
			 OTX2_CPT_LF_INPROG, lf_inprog.u);
पूर्ण

अटल अंतरभूत व्योम otx2_cptlf_disable_iqueues(काष्ठा otx2_cptlfs_info *lfs)
अणु
	पूर्णांक slot;

	क्रम (slot = 0; slot < lfs->lfs_num; slot++)
		otx2_cptlf_करो_disable_iqueue(&lfs->lf[slot]);
पूर्ण

अटल अंतरभूत व्योम otx2_cptlf_set_iqueue_enq(काष्ठा otx2_cptlf_info *lf,
					     bool enable)
अणु
	जोड़ otx2_cptx_lf_ctl lf_ctl;

	lf_ctl.u = otx2_cpt_पढ़ो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
				   OTX2_CPT_LF_CTL);

	/* Set iqueue's enqueuing */
	lf_ctl.s.ena = enable ? 0x1 : 0x0;
	otx2_cpt_ग_लिखो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
			 OTX2_CPT_LF_CTL, lf_ctl.u);
पूर्ण

अटल अंतरभूत व्योम otx2_cptlf_enable_iqueue_enq(काष्ठा otx2_cptlf_info *lf)
अणु
	otx2_cptlf_set_iqueue_enq(lf, true);
पूर्ण

अटल अंतरभूत व्योम otx2_cptlf_set_iqueue_exec(काष्ठा otx2_cptlf_info *lf,
					      bool enable)
अणु
	जोड़ otx2_cptx_lf_inprog lf_inprog;

	lf_inprog.u = otx2_cpt_पढ़ो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
				      OTX2_CPT_LF_INPROG);

	/* Set iqueue's execution */
	lf_inprog.s.eena = enable ? 0x1 : 0x0;
	otx2_cpt_ग_लिखो64(lf->lfs->reg_base, BLKADDR_CPT0, lf->slot,
			 OTX2_CPT_LF_INPROG, lf_inprog.u);
पूर्ण

अटल अंतरभूत व्योम otx2_cptlf_enable_iqueue_exec(काष्ठा otx2_cptlf_info *lf)
अणु
	otx2_cptlf_set_iqueue_exec(lf, true);
पूर्ण

अटल अंतरभूत व्योम otx2_cptlf_disable_iqueue_exec(काष्ठा otx2_cptlf_info *lf)
अणु
	otx2_cptlf_set_iqueue_exec(lf, false);
पूर्ण

अटल अंतरभूत व्योम otx2_cptlf_enable_iqueues(काष्ठा otx2_cptlfs_info *lfs)
अणु
	पूर्णांक slot;

	क्रम (slot = 0; slot < lfs->lfs_num; slot++) अणु
		otx2_cptlf_enable_iqueue_exec(&lfs->lf[slot]);
		otx2_cptlf_enable_iqueue_enq(&lfs->lf[slot]);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम otx2_cpt_fill_inst(जोड़ otx2_cpt_inst_s *cptinst,
				      काष्ठा otx2_cpt_iq_command *iq_cmd,
				      u64 comp_baddr)
अणु
	cptinst->u[0] = 0x0;
	cptinst->s.करोneपूर्णांक = true;
	cptinst->s.res_addr = comp_baddr;
	cptinst->u[2] = 0x0;
	cptinst->u[3] = 0x0;
	cptinst->s.ei0 = iq_cmd->cmd.u;
	cptinst->s.ei1 = iq_cmd->dptr;
	cptinst->s.ei2 = iq_cmd->rptr;
	cptinst->s.ei3 = iq_cmd->cptr.u;
पूर्ण

/*
 * On OcteonTX2 platक्रमm the parameter insts_num is used as a count of
 * inकाष्ठाions to be enqueued. The valid values क्रम insts_num are:
 * 1 - 1 CPT inकाष्ठाion will be enqueued during LMTST operation
 * 2 - 2 CPT inकाष्ठाions will be enqueued during LMTST operation
 */
अटल अंतरभूत व्योम otx2_cpt_send_cmd(जोड़ otx2_cpt_inst_s *cptinst,
				     u32 insts_num, काष्ठा otx2_cptlf_info *lf)
अणु
	व्योम __iomem *lmtline = lf->lmtline;
	दीर्घ ret;

	/*
	 * Make sure memory areas poपूर्णांकed in CPT_INST_S
	 * are flushed beक्रमe the inकाष्ठाion is sent to CPT
	 */
	dma_wmb();

	करो अणु
		/* Copy CPT command to LMTLINE */
		स_नकल_toio(lmtline, cptinst, insts_num * OTX2_CPT_INST_SIZE);

		/*
		 * LDEOR initiates atomic transfer to I/O device
		 * The following will cause the LMTST to fail (the LDEOR
		 * वापसs zero):
		 * - No stores have been perक्रमmed to the LMTLINE since it was
		 * last invalidated.
		 * - The bytes which have been stored to LMTLINE since it was
		 * last invalidated क्रमm a pattern that is non-contiguous, करोes
		 * not start at byte 0, or करोes not end on a 8-byte boundary.
		 * (i.e.comprises a क्रमmation of other than 1ै 16 8-byte
		 * words.)
		 *
		 * These rules are deचिन्हित such that an operating प्रणाली
		 * context चयन or hypervisor guest चयन need have no
		 * knowledge of the LMTST operations; the चयन code करोes not
		 * need to store to LMTCANCEL. Also note as LMTLINE data cannot
		 * be पढ़ो, there is no inक्रमmation leakage between processes.
		 */
		ret = otx2_lmt_flush(lf->ioreg);

	पूर्ण जबतक (!ret);
पूर्ण

अटल अंतरभूत bool otx2_cptlf_started(काष्ठा otx2_cptlfs_info *lfs)
अणु
	वापस atomic_पढ़ो(&lfs->state) == OTX2_CPTLF_STARTED;
पूर्ण

पूर्णांक otx2_cptlf_init(काष्ठा otx2_cptlfs_info *lfs, u8 eng_grp_msk, पूर्णांक pri,
		    पूर्णांक lfs_num);
व्योम otx2_cptlf_shutकरोwn(काष्ठा otx2_cptlfs_info *lfs);
पूर्णांक otx2_cptlf_रेजिस्टर_पूर्णांकerrupts(काष्ठा otx2_cptlfs_info *lfs);
व्योम otx2_cptlf_unरेजिस्टर_पूर्णांकerrupts(काष्ठा otx2_cptlfs_info *lfs);
व्योम otx2_cptlf_मुक्त_irqs_affinity(काष्ठा otx2_cptlfs_info *lfs);
पूर्णांक otx2_cptlf_set_irqs_affinity(काष्ठा otx2_cptlfs_info *lfs);

#पूर्ण_अगर /* __OTX2_CPTLF_H */
