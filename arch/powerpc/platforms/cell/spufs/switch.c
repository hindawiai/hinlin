<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * spu_चयन.c
 *
 * (C) Copyright IBM Corp. 2005
 *
 * Author: Mark Nutter <mnutter@us.ibm.com>
 *
 * Host-side part of SPU context चयन sequence outlined in
 * Synergistic Processor Element, Book IV.
 *
 * A fully premptive चयन of an SPE is very expensive in terms
 * of समय and प्रणाली resources.  SPE Book IV indicates that SPE
 * allocation should follow a "serially reusable device" model,
 * in which the SPE is asचिन्हित a task until it completes.  When
 * this is not possible, this sequence may be used to premptively
 * save, and then later (optionally) restore the context of a
 * program executing on an SPE.
 */

#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hardirq.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_priv1.h>
#समावेश <यंत्र/spu_csa.h>
#समावेश <यंत्र/mmu_context.h>

#समावेश "spufs.h"

#समावेश "spu_save_dump.h"
#समावेश "spu_restore_dump.h"

#अगर 0
#घोषणा POLL_WHILE_TRUE(_c) अणु				\
    करो अणु						\
    पूर्ण जबतक (_c);					\
  पूर्ण
#अन्यथा
#घोषणा RELAX_SPIN_COUNT				1000
#घोषणा POLL_WHILE_TRUE(_c) अणु				\
    करो अणु						\
	पूर्णांक _i;						\
	क्रम (_i=0; _i<RELAX_SPIN_COUNT && (_c); _i++) अणु \
	    cpu_relax();				\
	पूर्ण						\
	अगर (unlikely(_c)) yield();			\
	अन्यथा अवरोध;					\
    पूर्ण जबतक (_c);					\
  पूर्ण
#पूर्ण_अगर				/* debug */

#घोषणा POLL_WHILE_FALSE(_c)	POLL_WHILE_TRUE(!(_c))

अटल अंतरभूत व्योम acquire_spu_lock(काष्ठा spu *spu)
अणु
	/* Save, Step 1:
	 * Restore, Step 1:
	 *    Acquire SPU-specअगरic mutual exclusion lock.
	 *    TBD.
	 */
पूर्ण

अटल अंतरभूत व्योम release_spu_lock(काष्ठा spu *spu)
अणु
	/* Restore, Step 76:
	 *    Release SPU-specअगरic mutual exclusion lock.
	 *    TBD.
	 */
पूर्ण

अटल अंतरभूत पूर्णांक check_spu_isolate(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;
	u32 isolate_state;

	/* Save, Step 2:
	 * Save, Step 6:
	 *     If SPU_Status[E,L,IS] any field is '1', this
	 *     SPU is in isolate state and cannot be context
	 *     saved at this समय.
	 */
	isolate_state = SPU_STATUS_ISOLATED_STATE |
	    SPU_STATUS_ISOLATED_LOAD_STATUS | SPU_STATUS_ISOLATED_EXIT_STATUS;
	वापस (in_be32(&prob->spu_status_R) & isolate_state) ? 1 : 0;
पूर्ण

अटल अंतरभूत व्योम disable_पूर्णांकerrupts(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Save, Step 3:
	 * Restore, Step 2:
	 *     Save INT_Mask_class0 in CSA.
	 *     Write INT_MASK_class0 with value of 0.
	 *     Save INT_Mask_class1 in CSA.
	 *     Write INT_MASK_class1 with value of 0.
	 *     Save INT_Mask_class2 in CSA.
	 *     Write INT_MASK_class2 with value of 0.
	 *     Synchronize all three पूर्णांकerrupts to be sure
	 *     we no दीर्घer execute a handler on another CPU.
	 */
	spin_lock_irq(&spu->रेजिस्टर_lock);
	अगर (csa) अणु
		csa->priv1.पूर्णांक_mask_class0_RW = spu_पूर्णांक_mask_get(spu, 0);
		csa->priv1.पूर्णांक_mask_class1_RW = spu_पूर्णांक_mask_get(spu, 1);
		csa->priv1.पूर्णांक_mask_class2_RW = spu_पूर्णांक_mask_get(spu, 2);
	पूर्ण
	spu_पूर्णांक_mask_set(spu, 0, 0ul);
	spu_पूर्णांक_mask_set(spu, 1, 0ul);
	spu_पूर्णांक_mask_set(spu, 2, 0ul);
	eieio();
	spin_unlock_irq(&spu->रेजिस्टर_lock);

	/*
	 * This flag needs to be set beक्रमe calling synchronize_irq so
	 * that the update will be visible to the relevant handlers
	 * via a simple load.
	 */
	set_bit(SPU_CONTEXT_SWITCH_PENDING, &spu->flags);
	clear_bit(SPU_CONTEXT_FAULT_PENDING, &spu->flags);
	synchronize_irq(spu->irqs[0]);
	synchronize_irq(spu->irqs[1]);
	synchronize_irq(spu->irqs[2]);
पूर्ण

अटल अंतरभूत व्योम set_watchकरोg_समयr(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Save, Step 4:
	 * Restore, Step 25.
	 *    Set a software watchकरोg समयr, which specअगरies the
	 *    maximum allowable समय क्रम a context save sequence.
	 *
	 *    For present, this implementation will not set a global
	 *    watchकरोg समयr, as भवization & variable प्रणाली load
	 *    may cause unpredictable execution बार.
	 */
पूर्ण

अटल अंतरभूत व्योम inhibit_user_access(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Save, Step 5:
	 * Restore, Step 3:
	 *     Inhibit user-space access (अगर provided) to this
	 *     SPU by unmapping the भव pages asचिन्हित to
	 *     the SPU memory-mapped I/O (MMIO) क्रम problem
	 *     state. TBD.
	 */
पूर्ण

अटल अंतरभूत व्योम set_चयन_pending(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Save, Step 7:
	 * Restore, Step 5:
	 *     Set a software context चयन pending flag.
	 *     Done above in Step 3 - disable_पूर्णांकerrupts().
	 */
पूर्ण

अटल अंतरभूत व्योम save_mfc_cntl(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 8:
	 *     Suspend DMA and save MFC_CNTL.
	 */
	चयन (in_be64(&priv2->mfc_control_RW) &
	       MFC_CNTL_SUSPEND_DMA_STATUS_MASK) अणु
	हाल MFC_CNTL_SUSPEND_IN_PROGRESS:
		POLL_WHILE_FALSE((in_be64(&priv2->mfc_control_RW) &
				  MFC_CNTL_SUSPEND_DMA_STATUS_MASK) ==
				 MFC_CNTL_SUSPEND_COMPLETE);
		fallthrough;
	हाल MFC_CNTL_SUSPEND_COMPLETE:
		अगर (csa)
			csa->priv2.mfc_control_RW =
				in_be64(&priv2->mfc_control_RW) |
				MFC_CNTL_SUSPEND_DMA_QUEUE;
		अवरोध;
	हाल MFC_CNTL_NORMAL_DMA_QUEUE_OPERATION:
		out_be64(&priv2->mfc_control_RW, MFC_CNTL_SUSPEND_DMA_QUEUE);
		POLL_WHILE_FALSE((in_be64(&priv2->mfc_control_RW) &
				  MFC_CNTL_SUSPEND_DMA_STATUS_MASK) ==
				 MFC_CNTL_SUSPEND_COMPLETE);
		अगर (csa)
			csa->priv2.mfc_control_RW =
				in_be64(&priv2->mfc_control_RW) &
				~MFC_CNTL_SUSPEND_DMA_QUEUE &
				~MFC_CNTL_SUSPEND_MASK;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम save_spu_runcntl(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Save, Step 9:
	 *     Save SPU_Runcntl in the CSA.  This value contains
	 *     the "Application Desired State".
	 */
	csa->prob.spu_runcntl_RW = in_be32(&prob->spu_runcntl_RW);
पूर्ण

अटल अंतरभूत व्योम save_mfc_sr1(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Save, Step 10:
	 *     Save MFC_SR1 in the CSA.
	 */
	csa->priv1.mfc_sr1_RW = spu_mfc_sr1_get(spu);
पूर्ण

अटल अंतरभूत व्योम save_spu_status(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Save, Step 11:
	 *     Read SPU_Status[R], and save to CSA.
	 */
	अगर ((in_be32(&prob->spu_status_R) & SPU_STATUS_RUNNING) == 0) अणु
		csa->prob.spu_status_R = in_be32(&prob->spu_status_R);
	पूर्ण अन्यथा अणु
		u32 stopped;

		out_be32(&prob->spu_runcntl_RW, SPU_RUNCNTL_STOP);
		eieio();
		POLL_WHILE_TRUE(in_be32(&prob->spu_status_R) &
				SPU_STATUS_RUNNING);
		stopped =
		    SPU_STATUS_INVALID_INSTR | SPU_STATUS_SINGLE_STEP |
		    SPU_STATUS_STOPPED_BY_HALT | SPU_STATUS_STOPPED_BY_STOP;
		अगर ((in_be32(&prob->spu_status_R) & stopped) == 0)
			csa->prob.spu_status_R = SPU_STATUS_RUNNING;
		अन्यथा
			csa->prob.spu_status_R = in_be32(&prob->spu_status_R);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम save_mfc_stopped_status(काष्ठा spu_state *csa,
		काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	स्थिर u64 mask = MFC_CNTL_DECREMENTER_RUNNING |
			MFC_CNTL_DMA_QUEUES_EMPTY;

	/* Save, Step 12:
	 *     Read MFC_CNTL[Ds].  Update saved copy of
	 *     CSA.MFC_CNTL[Ds].
	 *
	 * update: करो the same with MFC_CNTL[Q].
	 */
	csa->priv2.mfc_control_RW &= ~mask;
	csa->priv2.mfc_control_RW |= in_be64(&priv2->mfc_control_RW) & mask;
पूर्ण

अटल अंतरभूत व्योम halt_mfc_decr(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 13:
	 *     Write MFC_CNTL[Dh] set to a '1' to halt
	 *     the decrementer.
	 */
	out_be64(&priv2->mfc_control_RW,
		 MFC_CNTL_DECREMENTER_HALTED | MFC_CNTL_SUSPEND_MASK);
	eieio();
पूर्ण

अटल अंतरभूत व्योम save_समयbase(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Save, Step 14:
	 *    Read PPE Timebase High and Timebase low रेजिस्टरs
	 *    and save in CSA.  TBD.
	 */
	csa->suspend_समय = get_cycles();
पूर्ण

अटल अंतरभूत व्योम हटाओ_other_spu_access(काष्ठा spu_state *csa,
					   काष्ठा spu *spu)
अणु
	/* Save, Step 15:
	 *     Remove other SPU access to this SPU by unmapping
	 *     this SPU's pages from their address space.  TBD.
	 */
पूर्ण

अटल अंतरभूत व्योम करो_mfc_mssync(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Save, Step 16:
	 * Restore, Step 11.
	 *     Write SPU_MSSync रेजिस्टर. Poll SPU_MSSync[P]
	 *     क्रम a value of 0.
	 */
	out_be64(&prob->spc_mssync_RW, 1UL);
	POLL_WHILE_TRUE(in_be64(&prob->spc_mssync_RW) & MS_SYNC_PENDING);
पूर्ण

अटल अंतरभूत व्योम issue_mfc_tlbie(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Save, Step 17:
	 * Restore, Step 12.
	 * Restore, Step 48.
	 *     Write TLB_Invalidate_Entry[IS,VPN,L,Lp]=0 रेजिस्टर.
	 *     Then issue a PPE sync inकाष्ठाion.
	 */
	spu_tlb_invalidate(spu);
	mb();
पूर्ण

अटल अंतरभूत व्योम handle_pending_पूर्णांकerrupts(काष्ठा spu_state *csa,
					     काष्ठा spu *spu)
अणु
	/* Save, Step 18:
	 *     Handle any pending पूर्णांकerrupts from this SPU
	 *     here.  This is OS or hypervisor specअगरic.  One
	 *     option is to re-enable पूर्णांकerrupts to handle any
	 *     pending पूर्णांकerrupts, with the पूर्णांकerrupt handlers
	 *     recognizing the software Context Switch Pending
	 *     flag, to ensure the SPU execution or MFC command
	 *     queue is not restarted.  TBD.
	 */
पूर्ण

अटल अंतरभूत व्योम save_mfc_queues(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	पूर्णांक i;

	/* Save, Step 19:
	 *     If MFC_Cntl[Se]=0 then save
	 *     MFC command queues.
	 */
	अगर ((in_be64(&priv2->mfc_control_RW) & MFC_CNTL_DMA_QUEUES_EMPTY) == 0) अणु
		क्रम (i = 0; i < 8; i++) अणु
			csa->priv2.puq[i].mfc_cq_data0_RW =
			    in_be64(&priv2->puq[i].mfc_cq_data0_RW);
			csa->priv2.puq[i].mfc_cq_data1_RW =
			    in_be64(&priv2->puq[i].mfc_cq_data1_RW);
			csa->priv2.puq[i].mfc_cq_data2_RW =
			    in_be64(&priv2->puq[i].mfc_cq_data2_RW);
			csa->priv2.puq[i].mfc_cq_data3_RW =
			    in_be64(&priv2->puq[i].mfc_cq_data3_RW);
		पूर्ण
		क्रम (i = 0; i < 16; i++) अणु
			csa->priv2.spuq[i].mfc_cq_data0_RW =
			    in_be64(&priv2->spuq[i].mfc_cq_data0_RW);
			csa->priv2.spuq[i].mfc_cq_data1_RW =
			    in_be64(&priv2->spuq[i].mfc_cq_data1_RW);
			csa->priv2.spuq[i].mfc_cq_data2_RW =
			    in_be64(&priv2->spuq[i].mfc_cq_data2_RW);
			csa->priv2.spuq[i].mfc_cq_data3_RW =
			    in_be64(&priv2->spuq[i].mfc_cq_data3_RW);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम save_ppu_querymask(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Save, Step 20:
	 *     Save the PPU_QueryMask रेजिस्टर
	 *     in the CSA.
	 */
	csa->prob.dma_querymask_RW = in_be32(&prob->dma_querymask_RW);
पूर्ण

अटल अंतरभूत व्योम save_ppu_querytype(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Save, Step 21:
	 *     Save the PPU_QueryType रेजिस्टर
	 *     in the CSA.
	 */
	csa->prob.dma_querytype_RW = in_be32(&prob->dma_querytype_RW);
पूर्ण

अटल अंतरभूत व्योम save_ppu_tagstatus(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Save the Prxy_TagStatus रेजिस्टर in the CSA.
	 *
	 * It is unnecessary to restore dma_tagstatus_R, however,
	 * dma_tagstatus_R in the CSA is accessed via backing_ops, so
	 * we must save it.
	 */
	csa->prob.dma_tagstatus_R = in_be32(&prob->dma_tagstatus_R);
पूर्ण

अटल अंतरभूत व्योम save_mfc_csr_tsq(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 22:
	 *     Save the MFC_CSR_TSQ रेजिस्टर
	 *     in the LSCSA.
	 */
	csa->priv2.spu_tag_status_query_RW =
	    in_be64(&priv2->spu_tag_status_query_RW);
पूर्ण

अटल अंतरभूत व्योम save_mfc_csr_cmd(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 23:
	 *     Save the MFC_CSR_CMD1 and MFC_CSR_CMD2
	 *     रेजिस्टरs in the CSA.
	 */
	csa->priv2.spu_cmd_buf1_RW = in_be64(&priv2->spu_cmd_buf1_RW);
	csa->priv2.spu_cmd_buf2_RW = in_be64(&priv2->spu_cmd_buf2_RW);
पूर्ण

अटल अंतरभूत व्योम save_mfc_csr_ato(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 24:
	 *     Save the MFC_CSR_ATO रेजिस्टर in
	 *     the CSA.
	 */
	csa->priv2.spu_atomic_status_RW = in_be64(&priv2->spu_atomic_status_RW);
पूर्ण

अटल अंतरभूत व्योम save_mfc_tclass_id(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Save, Step 25:
	 *     Save the MFC_TCLASS_ID रेजिस्टर in
	 *     the CSA.
	 */
	csa->priv1.mfc_tclass_id_RW = spu_mfc_tclass_id_get(spu);
पूर्ण

अटल अंतरभूत व्योम set_mfc_tclass_id(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Save, Step 26:
	 * Restore, Step 23.
	 *     Write the MFC_TCLASS_ID रेजिस्टर with
	 *     the value 0x10000000.
	 */
	spu_mfc_tclass_id_set(spu, 0x10000000);
	eieio();
पूर्ण

अटल अंतरभूत व्योम purge_mfc_queue(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 27:
	 * Restore, Step 14.
	 *     Write MFC_CNTL[Pc]=1 (purge queue).
	 */
	out_be64(&priv2->mfc_control_RW,
			MFC_CNTL_PURGE_DMA_REQUEST |
			MFC_CNTL_SUSPEND_MASK);
	eieio();
पूर्ण

अटल अंतरभूत व्योम रुको_purge_complete(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 28:
	 *     Poll MFC_CNTL[Ps] until value '11' is पढ़ो
	 *     (purge complete).
	 */
	POLL_WHILE_FALSE((in_be64(&priv2->mfc_control_RW) &
			 MFC_CNTL_PURGE_DMA_STATUS_MASK) ==
			 MFC_CNTL_PURGE_DMA_COMPLETE);
पूर्ण

अटल अंतरभूत व्योम setup_mfc_sr1(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Save, Step 30:
	 * Restore, Step 18:
	 *     Write MFC_SR1 with MFC_SR1[D=0,S=1] and
	 *     MFC_SR1[TL,R,Pr,T] set correctly क्रम the
	 *     OS specअगरic environment.
	 *
	 *     Implementation note: The SPU-side code
	 *     क्रम save/restore is privileged, so the
	 *     MFC_SR1[Pr] bit is not set.
	 *
	 */
	spu_mfc_sr1_set(spu, (MFC_STATE1_MASTER_RUN_CONTROL_MASK |
			      MFC_STATE1_RELOCATE_MASK |
			      MFC_STATE1_BUS_TLBIE_MASK));
पूर्ण

अटल अंतरभूत व्योम save_spu_npc(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Save, Step 31:
	 *     Save SPU_NPC in the CSA.
	 */
	csa->prob.spu_npc_RW = in_be32(&prob->spu_npc_RW);
पूर्ण

अटल अंतरभूत व्योम save_spu_privcntl(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 32:
	 *     Save SPU_PrivCntl in the CSA.
	 */
	csa->priv2.spu_privcntl_RW = in_be64(&priv2->spu_privcntl_RW);
पूर्ण

अटल अंतरभूत व्योम reset_spu_privcntl(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 33:
	 * Restore, Step 16:
	 *     Write SPU_PrivCntl[S,Le,A] fields reset to 0.
	 */
	out_be64(&priv2->spu_privcntl_RW, 0UL);
	eieio();
पूर्ण

अटल अंतरभूत व्योम save_spu_lslr(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 34:
	 *     Save SPU_LSLR in the CSA.
	 */
	csa->priv2.spu_lslr_RW = in_be64(&priv2->spu_lslr_RW);
पूर्ण

अटल अंतरभूत व्योम reset_spu_lslr(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 35:
	 * Restore, Step 17.
	 *     Reset SPU_LSLR.
	 */
	out_be64(&priv2->spu_lslr_RW, LS_ADDR_MASK);
	eieio();
पूर्ण

अटल अंतरभूत व्योम save_spu_cfg(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 36:
	 *     Save SPU_Cfg in the CSA.
	 */
	csa->priv2.spu_cfg_RW = in_be64(&priv2->spu_cfg_RW);
पूर्ण

अटल अंतरभूत व्योम save_pm_trace(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Save, Step 37:
	 *     Save PM_Trace_Tag_Wait_Mask in the CSA.
	 *     Not perक्रमmed by this implementation.
	 */
पूर्ण

अटल अंतरभूत व्योम save_mfc_rag(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Save, Step 38:
	 *     Save RA_GROUP_ID रेजिस्टर and the
	 *     RA_ENABLE reigster in the CSA.
	 */
	csa->priv1.resource_allocation_groupID_RW =
		spu_resource_allocation_groupID_get(spu);
	csa->priv1.resource_allocation_enable_RW =
		spu_resource_allocation_enable_get(spu);
पूर्ण

अटल अंतरभूत व्योम save_ppu_mb_stat(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Save, Step 39:
	 *     Save MB_Stat रेजिस्टर in the CSA.
	 */
	csa->prob.mb_stat_R = in_be32(&prob->mb_stat_R);
पूर्ण

अटल अंतरभूत व्योम save_ppu_mb(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Save, Step 40:
	 *     Save the PPU_MB रेजिस्टर in the CSA.
	 */
	csa->prob.pu_mb_R = in_be32(&prob->pu_mb_R);
पूर्ण

अटल अंतरभूत व्योम save_ppuपूर्णांक_mb(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 41:
	 *     Save the PPUINT_MB रेजिस्टर in the CSA.
	 */
	csa->priv2.puपूर्णांक_mb_R = in_be64(&priv2->puपूर्णांक_mb_R);
पूर्ण

अटल अंतरभूत व्योम save_ch_part1(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	u64 idx, ch_indices[] = अणु 0UL, 3UL, 4UL, 24UL, 25UL, 27UL पूर्ण;
	पूर्णांक i;

	/* Save, Step 42:
	 */

	/* Save CH 1, without channel count */
	out_be64(&priv2->spu_chnlcntptr_RW, 1);
	csa->spu_chnldata_RW[1] = in_be64(&priv2->spu_chnldata_RW);

	/* Save the following CH: [0,3,4,24,25,27] */
	क्रम (i = 0; i < ARRAY_SIZE(ch_indices); i++) अणु
		idx = ch_indices[i];
		out_be64(&priv2->spu_chnlcntptr_RW, idx);
		eieio();
		csa->spu_chnldata_RW[idx] = in_be64(&priv2->spu_chnldata_RW);
		csa->spu_chnlcnt_RW[idx] = in_be64(&priv2->spu_chnlcnt_RW);
		out_be64(&priv2->spu_chnldata_RW, 0UL);
		out_be64(&priv2->spu_chnlcnt_RW, 0UL);
		eieio();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम save_spu_mb(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	पूर्णांक i;

	/* Save, Step 43:
	 *     Save SPU Read Mailbox Channel.
	 */
	out_be64(&priv2->spu_chnlcntptr_RW, 29UL);
	eieio();
	csa->spu_chnlcnt_RW[29] = in_be64(&priv2->spu_chnlcnt_RW);
	क्रम (i = 0; i < 4; i++) अणु
		csa->spu_mailbox_data[i] = in_be64(&priv2->spu_chnldata_RW);
	पूर्ण
	out_be64(&priv2->spu_chnlcnt_RW, 0UL);
	eieio();
पूर्ण

अटल अंतरभूत व्योम save_mfc_cmd(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 44:
	 *     Save MFC_CMD Channel.
	 */
	out_be64(&priv2->spu_chnlcntptr_RW, 21UL);
	eieio();
	csa->spu_chnlcnt_RW[21] = in_be64(&priv2->spu_chnlcnt_RW);
	eieio();
पूर्ण

अटल अंतरभूत व्योम reset_ch(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	u64 ch_indices[4] = अणु 21UL, 23UL, 28UL, 30UL पूर्ण;
	u64 ch_counts[4] = अणु 16UL, 1UL, 1UL, 1UL पूर्ण;
	u64 idx;
	पूर्णांक i;

	/* Save, Step 45:
	 *     Reset the following CH: [21, 23, 28, 30]
	 */
	क्रम (i = 0; i < 4; i++) अणु
		idx = ch_indices[i];
		out_be64(&priv2->spu_chnlcntptr_RW, idx);
		eieio();
		out_be64(&priv2->spu_chnlcnt_RW, ch_counts[i]);
		eieio();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम resume_mfc_queue(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Save, Step 46:
	 * Restore, Step 25.
	 *     Write MFC_CNTL[Sc]=0 (resume queue processing).
	 */
	out_be64(&priv2->mfc_control_RW, MFC_CNTL_RESUME_DMA_QUEUE);
पूर्ण

अटल अंतरभूत व्योम setup_mfc_slbs(काष्ठा spu_state *csa, काष्ठा spu *spu,
		अचिन्हित पूर्णांक *code, पूर्णांक code_size)
अणु
	/* Save, Step 47:
	 * Restore, Step 30.
	 *     If MFC_SR1[R]=1, ग_लिखो 0 to SLB_Invalidate_All
	 *     रेजिस्टर, then initialize SLB_VSID and SLB_ESID
	 *     to provide access to SPU context save code and
	 *     LSCSA.
	 *
	 *     This implementation places both the context
	 *     चयन code and LSCSA in kernel address space.
	 *
	 *     Further this implementation assumes that the
	 *     MFC_SR1[R]=1 (in other words, assume that
	 *     translation is desired by OS environment).
	 */
	spu_invalidate_slbs(spu);
	spu_setup_kernel_slbs(spu, csa->lscsa, code, code_size);
पूर्ण

अटल अंतरभूत व्योम set_चयन_active(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Save, Step 48:
	 * Restore, Step 23.
	 *     Change the software context चयन pending flag
	 *     to context चयन active.  This implementation करोes
	 *     not uses a चयन active flag.
	 *
	 * Now that we have saved the mfc in the csa, we can add in the
	 * restart command अगर an exception occurred.
	 */
	अगर (test_bit(SPU_CONTEXT_FAULT_PENDING, &spu->flags))
		csa->priv2.mfc_control_RW |= MFC_CNTL_RESTART_DMA_COMMAND;
	clear_bit(SPU_CONTEXT_SWITCH_PENDING, &spu->flags);
	mb();
पूर्ण

अटल अंतरभूत व्योम enable_पूर्णांकerrupts(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	अचिन्हित दीर्घ class1_mask = CLASS1_ENABLE_SEGMENT_FAULT_INTR |
	    CLASS1_ENABLE_STORAGE_FAULT_INTR;

	/* Save, Step 49:
	 * Restore, Step 22:
	 *     Reset and then enable पूर्णांकerrupts, as
	 *     needed by OS.
	 *
	 *     This implementation enables only class1
	 *     (translation) पूर्णांकerrupts.
	 */
	spin_lock_irq(&spu->रेजिस्टर_lock);
	spu_पूर्णांक_stat_clear(spu, 0, CLASS0_INTR_MASK);
	spu_पूर्णांक_stat_clear(spu, 1, CLASS1_INTR_MASK);
	spu_पूर्णांक_stat_clear(spu, 2, CLASS2_INTR_MASK);
	spu_पूर्णांक_mask_set(spu, 0, 0ul);
	spu_पूर्णांक_mask_set(spu, 1, class1_mask);
	spu_पूर्णांक_mask_set(spu, 2, 0ul);
	spin_unlock_irq(&spu->रेजिस्टर_lock);
पूर्ण

अटल अंतरभूत पूर्णांक send_mfc_dma(काष्ठा spu *spu, अचिन्हित दीर्घ ea,
			       अचिन्हित पूर्णांक ls_offset, अचिन्हित पूर्णांक size,
			       अचिन्हित पूर्णांक tag, अचिन्हित पूर्णांक rclass,
			       अचिन्हित पूर्णांक cmd)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;
	जोड़ mfc_tag_size_class_cmd command;
	अचिन्हित पूर्णांक transfer_size;
	अस्थिर अचिन्हित पूर्णांक status = 0x0;

	जबतक (size > 0) अणु
		transfer_size =
		    (size > MFC_MAX_DMA_SIZE) ? MFC_MAX_DMA_SIZE : size;
		command.u.mfc_size = transfer_size;
		command.u.mfc_tag = tag;
		command.u.mfc_rclassid = rclass;
		command.u.mfc_cmd = cmd;
		करो अणु
			out_be32(&prob->mfc_lsa_W, ls_offset);
			out_be64(&prob->mfc_ea_W, ea);
			out_be64(&prob->mfc_जोड़_W.all64, command.all64);
			status =
			    in_be32(&prob->mfc_जोड़_W.by32.mfc_class_cmd32);
			अगर (unlikely(status & 0x2)) अणु
				cpu_relax();
			पूर्ण
		पूर्ण जबतक (status & 0x3);
		size -= transfer_size;
		ea += transfer_size;
		ls_offset += transfer_size;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम save_ls_16kb(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)&csa->lscsa->ls[0];
	अचिन्हित पूर्णांक ls_offset = 0x0;
	अचिन्हित पूर्णांक size = 16384;
	अचिन्हित पूर्णांक tag = 0;
	अचिन्हित पूर्णांक rclass = 0;
	अचिन्हित पूर्णांक cmd = MFC_PUT_CMD;

	/* Save, Step 50:
	 *     Issue a DMA command to copy the first 16K bytes
	 *     of local storage to the CSA.
	 */
	send_mfc_dma(spu, addr, ls_offset, size, tag, rclass, cmd);
पूर्ण

अटल अंतरभूत व्योम set_spu_npc(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Save, Step 51:
	 * Restore, Step 31.
	 *     Write SPU_NPC[IE]=0 and SPU_NPC[LSA] to entry
	 *     poपूर्णांक address of context save code in local
	 *     storage.
	 *
	 *     This implementation uses SPU-side save/restore
	 *     programs with entry poपूर्णांकs at LSA of 0.
	 */
	out_be32(&prob->spu_npc_RW, 0);
	eieio();
पूर्ण

अटल अंतरभूत व्योम set_signot1(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;
	जोड़ अणु
		u64 ull;
		u32 ui[2];
	पूर्ण addr64;

	/* Save, Step 52:
	 * Restore, Step 32:
	 *    Write SPU_Sig_Notअगरy_1 रेजिस्टर with upper 32-bits
	 *    of the CSA.LSCSA effective address.
	 */
	addr64.ull = (u64) csa->lscsa;
	out_be32(&prob->संकेत_notअगरy1, addr64.ui[0]);
	eieio();
पूर्ण

अटल अंतरभूत व्योम set_signot2(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;
	जोड़ अणु
		u64 ull;
		u32 ui[2];
	पूर्ण addr64;

	/* Save, Step 53:
	 * Restore, Step 33:
	 *    Write SPU_Sig_Notअगरy_2 रेजिस्टर with lower 32-bits
	 *    of the CSA.LSCSA effective address.
	 */
	addr64.ull = (u64) csa->lscsa;
	out_be32(&prob->संकेत_notअगरy2, addr64.ui[1]);
	eieio();
पूर्ण

अटल अंतरभूत व्योम send_save_code(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)&spu_save_code[0];
	अचिन्हित पूर्णांक ls_offset = 0x0;
	अचिन्हित पूर्णांक size = माप(spu_save_code);
	अचिन्हित पूर्णांक tag = 0;
	अचिन्हित पूर्णांक rclass = 0;
	अचिन्हित पूर्णांक cmd = MFC_GETFS_CMD;

	/* Save, Step 54:
	 *     Issue a DMA command to copy context save code
	 *     to local storage and start SPU.
	 */
	send_mfc_dma(spu, addr, ls_offset, size, tag, rclass, cmd);
पूर्ण

अटल अंतरभूत व्योम set_ppu_querymask(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Save, Step 55:
	 * Restore, Step 38.
	 *     Write PPU_QueryMask=1 (enable Tag Group 0)
	 *     and issue eieio inकाष्ठाion.
	 */
	out_be32(&prob->dma_querymask_RW, MFC_TAGID_TO_TAGMASK(0));
	eieio();
पूर्ण

अटल अंतरभूत व्योम रुको_tag_complete(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;
	u32 mask = MFC_TAGID_TO_TAGMASK(0);
	अचिन्हित दीर्घ flags;

	/* Save, Step 56:
	 * Restore, Step 39.
	 * Restore, Step 39.
	 * Restore, Step 46.
	 *     Poll PPU_TagStatus[gn] until 01 (Tag group 0 complete)
	 *     or ग_लिखो PPU_QueryType[TS]=01 and रुको क्रम Tag Group
	 *     Complete Interrupt.  Write INT_Stat_Class0 or
	 *     INT_Stat_Class2 with value of 'handled'.
	 */
	POLL_WHILE_FALSE(in_be32(&prob->dma_tagstatus_R) & mask);

	local_irq_save(flags);
	spu_पूर्णांक_stat_clear(spu, 0, CLASS0_INTR_MASK);
	spu_पूर्णांक_stat_clear(spu, 2, CLASS2_INTR_MASK);
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम रुको_spu_stopped(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;
	अचिन्हित दीर्घ flags;

	/* Save, Step 57:
	 * Restore, Step 40.
	 *     Poll until SPU_Status[R]=0 or रुको क्रम SPU Class 0
	 *     or SPU Class 2 पूर्णांकerrupt.  Write INT_Stat_class0
	 *     or INT_Stat_class2 with value of handled.
	 */
	POLL_WHILE_TRUE(in_be32(&prob->spu_status_R) & SPU_STATUS_RUNNING);

	local_irq_save(flags);
	spu_पूर्णांक_stat_clear(spu, 0, CLASS0_INTR_MASK);
	spu_पूर्णांक_stat_clear(spu, 2, CLASS2_INTR_MASK);
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत पूर्णांक check_save_status(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;
	u32 complete;

	/* Save, Step 54:
	 *     If SPU_Status[P]=1 and SPU_Status[SC] = "success",
	 *     context save succeeded, otherwise context save
	 *     failed.
	 */
	complete = ((SPU_SAVE_COMPLETE << SPU_STOP_STATUS_SHIFT) |
		    SPU_STATUS_STOPPED_BY_STOP);
	वापस (in_be32(&prob->spu_status_R) != complete) ? 1 : 0;
पूर्ण

अटल अंतरभूत व्योम terminate_spu_app(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Restore, Step 4:
	 *    If required, notअगरy the "using application" that
	 *    the SPU task has been terminated.  TBD.
	 */
पूर्ण

अटल अंतरभूत व्योम suspend_mfc_and_halt_decr(काष्ठा spu_state *csa,
		काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Restore, Step 7:
	 *     Write MFC_Cntl[Dh,Sc,Sm]='1','1','0' to suspend
	 *     the queue and halt the decrementer.
	 */
	out_be64(&priv2->mfc_control_RW, MFC_CNTL_SUSPEND_DMA_QUEUE |
		 MFC_CNTL_DECREMENTER_HALTED);
	eieio();
पूर्ण

अटल अंतरभूत व्योम रुको_suspend_mfc_complete(काष्ठा spu_state *csa,
					     काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Restore, Step 8:
	 * Restore, Step 47.
	 *     Poll MFC_CNTL[Ss] until 11 is वापसed.
	 */
	POLL_WHILE_FALSE((in_be64(&priv2->mfc_control_RW) &
			 MFC_CNTL_SUSPEND_DMA_STATUS_MASK) ==
			 MFC_CNTL_SUSPEND_COMPLETE);
पूर्ण

अटल अंतरभूत पूर्णांक suspend_spe(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Restore, Step 9:
	 *    If SPU_Status[R]=1, stop SPU execution
	 *    and रुको क्रम stop to complete.
	 *
	 *    Returns       1 अगर SPU_Status[R]=1 on entry.
	 *                  0 otherwise
	 */
	अगर (in_be32(&prob->spu_status_R) & SPU_STATUS_RUNNING) अणु
		अगर (in_be32(&prob->spu_status_R) &
		    SPU_STATUS_ISOLATED_EXIT_STATUS) अणु
			POLL_WHILE_TRUE(in_be32(&prob->spu_status_R) &
					SPU_STATUS_RUNNING);
		पूर्ण
		अगर ((in_be32(&prob->spu_status_R) &
		     SPU_STATUS_ISOLATED_LOAD_STATUS)
		    || (in_be32(&prob->spu_status_R) &
			SPU_STATUS_ISOLATED_STATE)) अणु
			out_be32(&prob->spu_runcntl_RW, SPU_RUNCNTL_STOP);
			eieio();
			POLL_WHILE_TRUE(in_be32(&prob->spu_status_R) &
					SPU_STATUS_RUNNING);
			out_be32(&prob->spu_runcntl_RW, 0x2);
			eieio();
			POLL_WHILE_TRUE(in_be32(&prob->spu_status_R) &
					SPU_STATUS_RUNNING);
		पूर्ण
		अगर (in_be32(&prob->spu_status_R) &
		    SPU_STATUS_WAITING_FOR_CHANNEL) अणु
			out_be32(&prob->spu_runcntl_RW, SPU_RUNCNTL_STOP);
			eieio();
			POLL_WHILE_TRUE(in_be32(&prob->spu_status_R) &
					SPU_STATUS_RUNNING);
		पूर्ण
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम clear_spu_status(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Restore, Step 10:
	 *    If SPU_Status[R]=0 and SPU_Status[E,L,IS]=1,
	 *    release SPU from isolate state.
	 */
	अगर (!(in_be32(&prob->spu_status_R) & SPU_STATUS_RUNNING)) अणु
		अगर (in_be32(&prob->spu_status_R) &
		    SPU_STATUS_ISOLATED_EXIT_STATUS) अणु
			spu_mfc_sr1_set(spu,
					MFC_STATE1_MASTER_RUN_CONTROL_MASK);
			eieio();
			out_be32(&prob->spu_runcntl_RW, SPU_RUNCNTL_RUNNABLE);
			eieio();
			POLL_WHILE_TRUE(in_be32(&prob->spu_status_R) &
					SPU_STATUS_RUNNING);
		पूर्ण
		अगर ((in_be32(&prob->spu_status_R) &
		     SPU_STATUS_ISOLATED_LOAD_STATUS)
		    || (in_be32(&prob->spu_status_R) &
			SPU_STATUS_ISOLATED_STATE)) अणु
			spu_mfc_sr1_set(spu,
					MFC_STATE1_MASTER_RUN_CONTROL_MASK);
			eieio();
			out_be32(&prob->spu_runcntl_RW, 0x2);
			eieio();
			POLL_WHILE_TRUE(in_be32(&prob->spu_status_R) &
					SPU_STATUS_RUNNING);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम reset_ch_part1(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	u64 ch_indices[] = अणु 0UL, 3UL, 4UL, 24UL, 25UL, 27UL पूर्ण;
	u64 idx;
	पूर्णांक i;

	/* Restore, Step 20:
	 */

	/* Reset CH 1 */
	out_be64(&priv2->spu_chnlcntptr_RW, 1);
	out_be64(&priv2->spu_chnldata_RW, 0UL);

	/* Reset the following CH: [0,3,4,24,25,27] */
	क्रम (i = 0; i < ARRAY_SIZE(ch_indices); i++) अणु
		idx = ch_indices[i];
		out_be64(&priv2->spu_chnlcntptr_RW, idx);
		eieio();
		out_be64(&priv2->spu_chnldata_RW, 0UL);
		out_be64(&priv2->spu_chnlcnt_RW, 0UL);
		eieio();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम reset_ch_part2(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	u64 ch_indices[5] = अणु 21UL, 23UL, 28UL, 29UL, 30UL पूर्ण;
	u64 ch_counts[5] = अणु 16UL, 1UL, 1UL, 0UL, 1UL पूर्ण;
	u64 idx;
	पूर्णांक i;

	/* Restore, Step 21:
	 *     Reset the following CH: [21, 23, 28, 29, 30]
	 */
	क्रम (i = 0; i < 5; i++) अणु
		idx = ch_indices[i];
		out_be64(&priv2->spu_chnlcntptr_RW, idx);
		eieio();
		out_be64(&priv2->spu_chnlcnt_RW, ch_counts[i]);
		eieio();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम setup_spu_status_part1(काष्ठा spu_state *csa,
					  काष्ठा spu *spu)
अणु
	u32 status_P = SPU_STATUS_STOPPED_BY_STOP;
	u32 status_I = SPU_STATUS_INVALID_INSTR;
	u32 status_H = SPU_STATUS_STOPPED_BY_HALT;
	u32 status_S = SPU_STATUS_SINGLE_STEP;
	u32 status_S_I = SPU_STATUS_SINGLE_STEP | SPU_STATUS_INVALID_INSTR;
	u32 status_S_P = SPU_STATUS_SINGLE_STEP | SPU_STATUS_STOPPED_BY_STOP;
	u32 status_P_H = SPU_STATUS_STOPPED_BY_HALT |SPU_STATUS_STOPPED_BY_STOP;
	u32 status_P_I = SPU_STATUS_STOPPED_BY_STOP |SPU_STATUS_INVALID_INSTR;
	u32 status_code;

	/* Restore, Step 27:
	 *     If the CSA.SPU_Status[I,S,H,P]=1 then add the correct
	 *     inकाष्ठाion sequence to the end of the SPU based restore
	 *     code (after the "context restored" stop and संकेत) to
	 *     restore the correct SPU status.
	 *
	 *     NOTE: Rather than modअगरying the SPU executable, we
	 *     instead add a new 'stopped_status' field to the
	 *     LSCSA.  The SPU-side restore पढ़ोs this field and
	 *     takes the appropriate action when निकासing.
	 */

	status_code =
	    (csa->prob.spu_status_R >> SPU_STOP_STATUS_SHIFT) & 0xFFFF;
	अगर ((csa->prob.spu_status_R & status_P_I) == status_P_I) अणु

		/* SPU_Status[P,I]=1 - Illegal Inकाष्ठाion followed
		 * by Stop and Signal inकाष्ठाion, followed by 'br -4'.
		 *
		 */
		csa->lscsa->stopped_status.slot[0] = SPU_STOPPED_STATUS_P_I;
		csa->lscsa->stopped_status.slot[1] = status_code;

	पूर्ण अन्यथा अगर ((csa->prob.spu_status_R & status_P_H) == status_P_H) अणु

		/* SPU_Status[P,H]=1 - Halt Conditional, followed
		 * by Stop and Signal inकाष्ठाion, followed by
		 * 'br -4'.
		 */
		csa->lscsa->stopped_status.slot[0] = SPU_STOPPED_STATUS_P_H;
		csa->lscsa->stopped_status.slot[1] = status_code;

	पूर्ण अन्यथा अगर ((csa->prob.spu_status_R & status_S_P) == status_S_P) अणु

		/* SPU_Status[S,P]=1 - Stop and Signal inकाष्ठाion
		 * followed by 'br -4'.
		 */
		csa->lscsa->stopped_status.slot[0] = SPU_STOPPED_STATUS_S_P;
		csa->lscsa->stopped_status.slot[1] = status_code;

	पूर्ण अन्यथा अगर ((csa->prob.spu_status_R & status_S_I) == status_S_I) अणु

		/* SPU_Status[S,I]=1 - Illegal inकाष्ठाion followed
		 * by 'br -4'.
		 */
		csa->lscsa->stopped_status.slot[0] = SPU_STOPPED_STATUS_S_I;
		csa->lscsa->stopped_status.slot[1] = status_code;

	पूर्ण अन्यथा अगर ((csa->prob.spu_status_R & status_P) == status_P) अणु

		/* SPU_Status[P]=1 - Stop and Signal inकाष्ठाion
		 * followed by 'br -4'.
		 */
		csa->lscsa->stopped_status.slot[0] = SPU_STOPPED_STATUS_P;
		csa->lscsa->stopped_status.slot[1] = status_code;

	पूर्ण अन्यथा अगर ((csa->prob.spu_status_R & status_H) == status_H) अणु

		/* SPU_Status[H]=1 - Halt Conditional, followed
		 * by 'br -4'.
		 */
		csa->lscsa->stopped_status.slot[0] = SPU_STOPPED_STATUS_H;

	पूर्ण अन्यथा अगर ((csa->prob.spu_status_R & status_S) == status_S) अणु

		/* SPU_Status[S]=1 - Two nop inकाष्ठाions.
		 */
		csa->lscsa->stopped_status.slot[0] = SPU_STOPPED_STATUS_S;

	पूर्ण अन्यथा अगर ((csa->prob.spu_status_R & status_I) == status_I) अणु

		/* SPU_Status[I]=1 - Illegal inकाष्ठाion followed
		 * by 'br -4'.
		 */
		csa->lscsa->stopped_status.slot[0] = SPU_STOPPED_STATUS_I;

	पूर्ण
पूर्ण

अटल अंतरभूत व्योम setup_spu_status_part2(काष्ठा spu_state *csa,
					  काष्ठा spu *spu)
अणु
	u32 mask;

	/* Restore, Step 28:
	 *     If the CSA.SPU_Status[I,S,H,P,R]=0 then
	 *     add a 'br *' inकाष्ठाion to the end of
	 *     the SPU based restore code.
	 *
	 *     NOTE: Rather than modअगरying the SPU executable, we
	 *     instead add a new 'stopped_status' field to the
	 *     LSCSA.  The SPU-side restore पढ़ोs this field and
	 *     takes the appropriate action when निकासing.
	 */
	mask = SPU_STATUS_INVALID_INSTR |
	    SPU_STATUS_SINGLE_STEP |
	    SPU_STATUS_STOPPED_BY_HALT |
	    SPU_STATUS_STOPPED_BY_STOP | SPU_STATUS_RUNNING;
	अगर (!(csa->prob.spu_status_R & mask)) अणु
		csa->lscsa->stopped_status.slot[0] = SPU_STOPPED_STATUS_R;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम restore_mfc_rag(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Restore, Step 29:
	 *     Restore RA_GROUP_ID रेजिस्टर and the
	 *     RA_ENABLE reigster from the CSA.
	 */
	spu_resource_allocation_groupID_set(spu,
			csa->priv1.resource_allocation_groupID_RW);
	spu_resource_allocation_enable_set(spu,
			csa->priv1.resource_allocation_enable_RW);
पूर्ण

अटल अंतरभूत व्योम send_restore_code(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)&spu_restore_code[0];
	अचिन्हित पूर्णांक ls_offset = 0x0;
	अचिन्हित पूर्णांक size = माप(spu_restore_code);
	अचिन्हित पूर्णांक tag = 0;
	अचिन्हित पूर्णांक rclass = 0;
	अचिन्हित पूर्णांक cmd = MFC_GETFS_CMD;

	/* Restore, Step 37:
	 *     Issue MFC DMA command to copy context
	 *     restore code to local storage.
	 */
	send_mfc_dma(spu, addr, ls_offset, size, tag, rclass, cmd);
पूर्ण

अटल अंतरभूत व्योम setup_decr(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Restore, Step 34:
	 *     If CSA.MFC_CNTL[Ds]=1 (decrementer was
	 *     running) then adjust decrementer, set
	 *     decrementer running status in LSCSA,
	 *     and set decrementer "wrapped" status
	 *     in LSCSA.
	 */
	अगर (csa->priv2.mfc_control_RW & MFC_CNTL_DECREMENTER_RUNNING) अणु
		cycles_t resume_समय = get_cycles();
		cycles_t delta_समय = resume_समय - csa->suspend_समय;

		csa->lscsa->decr_status.slot[0] = SPU_DECR_STATUS_RUNNING;
		अगर (csa->lscsa->decr.slot[0] < delta_समय) अणु
			csa->lscsa->decr_status.slot[0] |=
				 SPU_DECR_STATUS_WRAPPED;
		पूर्ण

		csa->lscsa->decr.slot[0] -= delta_समय;
	पूर्ण अन्यथा अणु
		csa->lscsa->decr_status.slot[0] = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम setup_ppu_mb(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Restore, Step 35:
	 *     Copy the CSA.PU_MB data पूर्णांकo the LSCSA.
	 */
	csa->lscsa->ppu_mb.slot[0] = csa->prob.pu_mb_R;
पूर्ण

अटल अंतरभूत व्योम setup_ppuपूर्णांक_mb(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Restore, Step 36:
	 *     Copy the CSA.PUINT_MB data पूर्णांकo the LSCSA.
	 */
	csa->lscsa->ppuपूर्णांक_mb.slot[0] = csa->priv2.puपूर्णांक_mb_R;
पूर्ण

अटल अंतरभूत पूर्णांक check_restore_status(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;
	u32 complete;

	/* Restore, Step 40:
	 *     If SPU_Status[P]=1 and SPU_Status[SC] = "success",
	 *     context restore succeeded, otherwise context restore
	 *     failed.
	 */
	complete = ((SPU_RESTORE_COMPLETE << SPU_STOP_STATUS_SHIFT) |
		    SPU_STATUS_STOPPED_BY_STOP);
	वापस (in_be32(&prob->spu_status_R) != complete) ? 1 : 0;
पूर्ण

अटल अंतरभूत व्योम restore_spu_privcntl(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Restore, Step 41:
	 *     Restore SPU_PrivCntl from the CSA.
	 */
	out_be64(&priv2->spu_privcntl_RW, csa->priv2.spu_privcntl_RW);
	eieio();
पूर्ण

अटल अंतरभूत व्योम restore_status_part1(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;
	u32 mask;

	/* Restore, Step 42:
	 *     If any CSA.SPU_Status[I,S,H,P]=1, then
	 *     restore the error or single step state.
	 */
	mask = SPU_STATUS_INVALID_INSTR |
	    SPU_STATUS_SINGLE_STEP |
	    SPU_STATUS_STOPPED_BY_HALT | SPU_STATUS_STOPPED_BY_STOP;
	अगर (csa->prob.spu_status_R & mask) अणु
		out_be32(&prob->spu_runcntl_RW, SPU_RUNCNTL_RUNNABLE);
		eieio();
		POLL_WHILE_TRUE(in_be32(&prob->spu_status_R) &
				SPU_STATUS_RUNNING);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम restore_status_part2(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;
	u32 mask;

	/* Restore, Step 43:
	 *     If all CSA.SPU_Status[I,S,H,P,R]=0 then ग_लिखो
	 *     SPU_RunCntl[R0R1]='01', रुको क्रम SPU_Status[R]=1,
	 *     then ग_लिखो '00' to SPU_RunCntl[R0R1] and रुको
	 *     क्रम SPU_Status[R]=0.
	 */
	mask = SPU_STATUS_INVALID_INSTR |
	    SPU_STATUS_SINGLE_STEP |
	    SPU_STATUS_STOPPED_BY_HALT |
	    SPU_STATUS_STOPPED_BY_STOP | SPU_STATUS_RUNNING;
	अगर (!(csa->prob.spu_status_R & mask)) अणु
		out_be32(&prob->spu_runcntl_RW, SPU_RUNCNTL_RUNNABLE);
		eieio();
		POLL_WHILE_FALSE(in_be32(&prob->spu_status_R) &
				 SPU_STATUS_RUNNING);
		out_be32(&prob->spu_runcntl_RW, SPU_RUNCNTL_STOP);
		eieio();
		POLL_WHILE_TRUE(in_be32(&prob->spu_status_R) &
				SPU_STATUS_RUNNING);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम restore_ls_16kb(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)&csa->lscsa->ls[0];
	अचिन्हित पूर्णांक ls_offset = 0x0;
	अचिन्हित पूर्णांक size = 16384;
	अचिन्हित पूर्णांक tag = 0;
	अचिन्हित पूर्णांक rclass = 0;
	अचिन्हित पूर्णांक cmd = MFC_GET_CMD;

	/* Restore, Step 44:
	 *     Issue a DMA command to restore the first
	 *     16kb of local storage from CSA.
	 */
	send_mfc_dma(spu, addr, ls_offset, size, tag, rclass, cmd);
पूर्ण

अटल अंतरभूत व्योम suspend_mfc(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Restore, Step 47.
	 *     Write MFC_Cntl[Sc,Sm]='1','0' to suspend
	 *     the queue.
	 */
	out_be64(&priv2->mfc_control_RW, MFC_CNTL_SUSPEND_DMA_QUEUE);
	eieio();
पूर्ण

अटल अंतरभूत व्योम clear_पूर्णांकerrupts(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Restore, Step 49:
	 *     Write INT_MASK_class0 with value of 0.
	 *     Write INT_MASK_class1 with value of 0.
	 *     Write INT_MASK_class2 with value of 0.
	 *     Write INT_STAT_class0 with value of -1.
	 *     Write INT_STAT_class1 with value of -1.
	 *     Write INT_STAT_class2 with value of -1.
	 */
	spin_lock_irq(&spu->रेजिस्टर_lock);
	spu_पूर्णांक_mask_set(spu, 0, 0ul);
	spu_पूर्णांक_mask_set(spu, 1, 0ul);
	spu_पूर्णांक_mask_set(spu, 2, 0ul);
	spu_पूर्णांक_stat_clear(spu, 0, CLASS0_INTR_MASK);
	spu_पूर्णांक_stat_clear(spu, 1, CLASS1_INTR_MASK);
	spu_पूर्णांक_stat_clear(spu, 2, CLASS2_INTR_MASK);
	spin_unlock_irq(&spu->रेजिस्टर_lock);
पूर्ण

अटल अंतरभूत व्योम restore_mfc_queues(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	पूर्णांक i;

	/* Restore, Step 50:
	 *     If MFC_Cntl[Se]!=0 then restore
	 *     MFC command queues.
	 */
	अगर ((csa->priv2.mfc_control_RW & MFC_CNTL_DMA_QUEUES_EMPTY_MASK) == 0) अणु
		क्रम (i = 0; i < 8; i++) अणु
			out_be64(&priv2->puq[i].mfc_cq_data0_RW,
				 csa->priv2.puq[i].mfc_cq_data0_RW);
			out_be64(&priv2->puq[i].mfc_cq_data1_RW,
				 csa->priv2.puq[i].mfc_cq_data1_RW);
			out_be64(&priv2->puq[i].mfc_cq_data2_RW,
				 csa->priv2.puq[i].mfc_cq_data2_RW);
			out_be64(&priv2->puq[i].mfc_cq_data3_RW,
				 csa->priv2.puq[i].mfc_cq_data3_RW);
		पूर्ण
		क्रम (i = 0; i < 16; i++) अणु
			out_be64(&priv2->spuq[i].mfc_cq_data0_RW,
				 csa->priv2.spuq[i].mfc_cq_data0_RW);
			out_be64(&priv2->spuq[i].mfc_cq_data1_RW,
				 csa->priv2.spuq[i].mfc_cq_data1_RW);
			out_be64(&priv2->spuq[i].mfc_cq_data2_RW,
				 csa->priv2.spuq[i].mfc_cq_data2_RW);
			out_be64(&priv2->spuq[i].mfc_cq_data3_RW,
				 csa->priv2.spuq[i].mfc_cq_data3_RW);
		पूर्ण
	पूर्ण
	eieio();
पूर्ण

अटल अंतरभूत व्योम restore_ppu_querymask(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Restore, Step 51:
	 *     Restore the PPU_QueryMask रेजिस्टर from CSA.
	 */
	out_be32(&prob->dma_querymask_RW, csa->prob.dma_querymask_RW);
	eieio();
पूर्ण

अटल अंतरभूत व्योम restore_ppu_querytype(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Restore, Step 52:
	 *     Restore the PPU_QueryType रेजिस्टर from CSA.
	 */
	out_be32(&prob->dma_querytype_RW, csa->prob.dma_querytype_RW);
	eieio();
पूर्ण

अटल अंतरभूत व्योम restore_mfc_csr_tsq(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Restore, Step 53:
	 *     Restore the MFC_CSR_TSQ रेजिस्टर from CSA.
	 */
	out_be64(&priv2->spu_tag_status_query_RW,
		 csa->priv2.spu_tag_status_query_RW);
	eieio();
पूर्ण

अटल अंतरभूत व्योम restore_mfc_csr_cmd(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Restore, Step 54:
	 *     Restore the MFC_CSR_CMD1 and MFC_CSR_CMD2
	 *     रेजिस्टरs from CSA.
	 */
	out_be64(&priv2->spu_cmd_buf1_RW, csa->priv2.spu_cmd_buf1_RW);
	out_be64(&priv2->spu_cmd_buf2_RW, csa->priv2.spu_cmd_buf2_RW);
	eieio();
पूर्ण

अटल अंतरभूत व्योम restore_mfc_csr_ato(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Restore, Step 55:
	 *     Restore the MFC_CSR_ATO रेजिस्टर from CSA.
	 */
	out_be64(&priv2->spu_atomic_status_RW, csa->priv2.spu_atomic_status_RW);
पूर्ण

अटल अंतरभूत व्योम restore_mfc_tclass_id(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Restore, Step 56:
	 *     Restore the MFC_TCLASS_ID रेजिस्टर from CSA.
	 */
	spu_mfc_tclass_id_set(spu, csa->priv1.mfc_tclass_id_RW);
	eieio();
पूर्ण

अटल अंतरभूत व्योम set_llr_event(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	u64 ch0_cnt, ch0_data;
	u64 ch1_data;

	/* Restore, Step 57:
	 *    Set the Lock Line Reservation Lost Event by:
	 *      1. OR CSA.SPU_Event_Status with bit 21 (Lr) set to 1.
	 *      2. If CSA.SPU_Channel_0_Count=0 and
	 *         CSA.SPU_Wr_Event_Mask[Lr]=1 and
	 *         CSA.SPU_Event_Status[Lr]=0 then set
	 *         CSA.SPU_Event_Status_Count=1.
	 */
	ch0_cnt = csa->spu_chnlcnt_RW[0];
	ch0_data = csa->spu_chnldata_RW[0];
	ch1_data = csa->spu_chnldata_RW[1];
	csa->spu_chnldata_RW[0] |= MFC_LLR_LOST_EVENT;
	अगर ((ch0_cnt == 0) && !(ch0_data & MFC_LLR_LOST_EVENT) &&
	    (ch1_data & MFC_LLR_LOST_EVENT)) अणु
		csa->spu_chnlcnt_RW[0] = 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम restore_decr_wrapped(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Restore, Step 58:
	 *     If the status of the CSA software decrementer
	 *     "wrapped" flag is set, OR in a '1' to
	 *     CSA.SPU_Event_Status[Tm].
	 */
	अगर (!(csa->lscsa->decr_status.slot[0] & SPU_DECR_STATUS_WRAPPED))
		वापस;

	अगर ((csa->spu_chnlcnt_RW[0] == 0) &&
	    (csa->spu_chnldata_RW[1] & 0x20) &&
	    !(csa->spu_chnldata_RW[0] & 0x20))
		csa->spu_chnlcnt_RW[0] = 1;

	csa->spu_chnldata_RW[0] |= 0x20;
पूर्ण

अटल अंतरभूत व्योम restore_ch_part1(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	u64 idx, ch_indices[] = अणु 0UL, 3UL, 4UL, 24UL, 25UL, 27UL पूर्ण;
	पूर्णांक i;

	/* Restore, Step 59:
	 *	Restore the following CH: [0,3,4,24,25,27]
	 */
	क्रम (i = 0; i < ARRAY_SIZE(ch_indices); i++) अणु
		idx = ch_indices[i];
		out_be64(&priv2->spu_chnlcntptr_RW, idx);
		eieio();
		out_be64(&priv2->spu_chnldata_RW, csa->spu_chnldata_RW[idx]);
		out_be64(&priv2->spu_chnlcnt_RW, csa->spu_chnlcnt_RW[idx]);
		eieio();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम restore_ch_part2(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	u64 ch_indices[3] = अणु 9UL, 21UL, 23UL पूर्ण;
	u64 ch_counts[3] = अणु 1UL, 16UL, 1UL पूर्ण;
	u64 idx;
	पूर्णांक i;

	/* Restore, Step 60:
	 *     Restore the following CH: [9,21,23].
	 */
	ch_counts[0] = 1UL;
	ch_counts[1] = csa->spu_chnlcnt_RW[21];
	ch_counts[2] = 1UL;
	क्रम (i = 0; i < 3; i++) अणु
		idx = ch_indices[i];
		out_be64(&priv2->spu_chnlcntptr_RW, idx);
		eieio();
		out_be64(&priv2->spu_chnlcnt_RW, ch_counts[i]);
		eieio();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम restore_spu_lslr(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Restore, Step 61:
	 *     Restore the SPU_LSLR रेजिस्टर from CSA.
	 */
	out_be64(&priv2->spu_lslr_RW, csa->priv2.spu_lslr_RW);
	eieio();
पूर्ण

अटल अंतरभूत व्योम restore_spu_cfg(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Restore, Step 62:
	 *     Restore the SPU_Cfg रेजिस्टर from CSA.
	 */
	out_be64(&priv2->spu_cfg_RW, csa->priv2.spu_cfg_RW);
	eieio();
पूर्ण

अटल अंतरभूत व्योम restore_pm_trace(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Restore, Step 63:
	 *     Restore PM_Trace_Tag_Wait_Mask from CSA.
	 *     Not perक्रमmed by this implementation.
	 */
पूर्ण

अटल अंतरभूत व्योम restore_spu_npc(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Restore, Step 64:
	 *     Restore SPU_NPC from CSA.
	 */
	out_be32(&prob->spu_npc_RW, csa->prob.spu_npc_RW);
	eieio();
पूर्ण

अटल अंतरभूत व्योम restore_spu_mb(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	पूर्णांक i;

	/* Restore, Step 65:
	 *     Restore MFC_RdSPU_MB from CSA.
	 */
	out_be64(&priv2->spu_chnlcntptr_RW, 29UL);
	eieio();
	out_be64(&priv2->spu_chnlcnt_RW, csa->spu_chnlcnt_RW[29]);
	क्रम (i = 0; i < 4; i++) अणु
		out_be64(&priv2->spu_chnldata_RW, csa->spu_mailbox_data[i]);
	पूर्ण
	eieio();
पूर्ण

अटल अंतरभूत व्योम check_ppu_mb_stat(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;
	u32 dummy = 0;

	/* Restore, Step 66:
	 *     If CSA.MB_Stat[P]=0 (mailbox empty) then
	 *     पढ़ो from the PPU_MB रेजिस्टर.
	 */
	अगर ((csa->prob.mb_stat_R & 0xFF) == 0) अणु
		dummy = in_be32(&prob->pu_mb_R);
		eieio();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम check_ppuपूर्णांक_mb_stat(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;
	u64 dummy = 0UL;

	/* Restore, Step 66:
	 *     If CSA.MB_Stat[I]=0 (mailbox empty) then
	 *     पढ़ो from the PPUINT_MB रेजिस्टर.
	 */
	अगर ((csa->prob.mb_stat_R & 0xFF0000) == 0) अणु
		dummy = in_be64(&priv2->puपूर्णांक_mb_R);
		eieio();
		spu_पूर्णांक_stat_clear(spu, 2, CLASS2_ENABLE_MAILBOX_INTR);
		eieio();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम restore_mfc_sr1(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Restore, Step 69:
	 *     Restore the MFC_SR1 रेजिस्टर from CSA.
	 */
	spu_mfc_sr1_set(spu, csa->priv1.mfc_sr1_RW);
	eieio();
पूर्ण

अटल अंतरभूत व्योम set_पूर्णांक_route(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_context *ctx = spu->ctx;

	spu_cpu_affinity_set(spu, ctx->last_ran);
पूर्ण

अटल अंतरभूत व्योम restore_other_spu_access(काष्ठा spu_state *csa,
					    काष्ठा spu *spu)
अणु
	/* Restore, Step 70:
	 *     Restore other SPU mappings to this SPU. TBD.
	 */
पूर्ण

अटल अंतरभूत व्योम restore_spu_runcntl(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	/* Restore, Step 71:
	 *     If CSA.SPU_Status[R]=1 then ग_लिखो
	 *     SPU_RunCntl[R0R1]='01'.
	 */
	अगर (csa->prob.spu_status_R & SPU_STATUS_RUNNING) अणु
		out_be32(&prob->spu_runcntl_RW, SPU_RUNCNTL_RUNNABLE);
		eieio();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम restore_mfc_cntl(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Restore, Step 72:
	 *    Restore the MFC_CNTL रेजिस्टर क्रम the CSA.
	 */
	out_be64(&priv2->mfc_control_RW, csa->priv2.mfc_control_RW);
	eieio();

	/*
	 * The queue is put back पूर्णांकo the same state that was evident prior to
	 * the context चयन. The suspend flag is added to the saved state in
	 * the csa, अगर the operational state was suspending or suspended. In
	 * this हाल, the code that suspended the mfc is responsible क्रम
	 * continuing it. Note that SPE faults करो not change the operational
	 * state of the spu.
	 */
पूर्ण

अटल अंतरभूत व्योम enable_user_access(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Restore, Step 73:
	 *     Enable user-space access (अगर provided) to this
	 *     SPU by mapping the भव pages asचिन्हित to
	 *     the SPU memory-mapped I/O (MMIO) क्रम problem
	 *     state. TBD.
	 */
पूर्ण

अटल अंतरभूत व्योम reset_चयन_active(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Restore, Step 74:
	 *     Reset the "context switch active" flag.
	 *     Not perक्रमmed by this implementation.
	 */
पूर्ण

अटल अंतरभूत व्योम reenable_पूर्णांकerrupts(काष्ठा spu_state *csa, काष्ठा spu *spu)
अणु
	/* Restore, Step 75:
	 *     Re-enable SPU पूर्णांकerrupts.
	 */
	spin_lock_irq(&spu->रेजिस्टर_lock);
	spu_पूर्णांक_mask_set(spu, 0, csa->priv1.पूर्णांक_mask_class0_RW);
	spu_पूर्णांक_mask_set(spu, 1, csa->priv1.पूर्णांक_mask_class1_RW);
	spu_पूर्णांक_mask_set(spu, 2, csa->priv1.पूर्णांक_mask_class2_RW);
	spin_unlock_irq(&spu->रेजिस्टर_lock);
पूर्ण

अटल पूर्णांक quiece_spu(काष्ठा spu_state *prev, काष्ठा spu *spu)
अणु
	/*
	 * Combined steps 2-18 of SPU context save sequence, which
	 * quiesce the SPU state (disable SPU execution, MFC command
	 * queues, decrementer, SPU पूर्णांकerrupts, etc.).
	 *
	 * Returns      0 on success.
	 *              2 अगर failed step 2.
	 *              6 अगर failed step 6.
	 */

	अगर (check_spu_isolate(prev, spu)) अणु	/* Step 2. */
		वापस 2;
	पूर्ण
	disable_पूर्णांकerrupts(prev, spu);	        /* Step 3. */
	set_watchकरोg_समयr(prev, spu);	        /* Step 4. */
	inhibit_user_access(prev, spu);	        /* Step 5. */
	अगर (check_spu_isolate(prev, spu)) अणु	/* Step 6. */
		वापस 6;
	पूर्ण
	set_चयन_pending(prev, spu);	        /* Step 7. */
	save_mfc_cntl(prev, spu);		/* Step 8. */
	save_spu_runcntl(prev, spu);	        /* Step 9. */
	save_mfc_sr1(prev, spu);	        /* Step 10. */
	save_spu_status(prev, spu);	        /* Step 11. */
	save_mfc_stopped_status(prev, spu);     /* Step 12. */
	halt_mfc_decr(prev, spu);	        /* Step 13. */
	save_समयbase(prev, spu);		/* Step 14. */
	हटाओ_other_spu_access(prev, spu);	/* Step 15. */
	करो_mfc_mssync(prev, spu);	        /* Step 16. */
	issue_mfc_tlbie(prev, spu);	        /* Step 17. */
	handle_pending_पूर्णांकerrupts(prev, spu);	/* Step 18. */

	वापस 0;
पूर्ण

अटल व्योम save_csa(काष्ठा spu_state *prev, काष्ठा spu *spu)
अणु
	/*
	 * Combine steps 19-44 of SPU context save sequence, which
	 * save regions of the privileged & problem state areas.
	 */

	save_mfc_queues(prev, spu);	/* Step 19. */
	save_ppu_querymask(prev, spu);	/* Step 20. */
	save_ppu_querytype(prev, spu);	/* Step 21. */
	save_ppu_tagstatus(prev, spu);  /* NEW.     */
	save_mfc_csr_tsq(prev, spu);	/* Step 22. */
	save_mfc_csr_cmd(prev, spu);	/* Step 23. */
	save_mfc_csr_ato(prev, spu);	/* Step 24. */
	save_mfc_tclass_id(prev, spu);	/* Step 25. */
	set_mfc_tclass_id(prev, spu);	/* Step 26. */
	save_mfc_cmd(prev, spu);	/* Step 26a - moved from 44. */
	purge_mfc_queue(prev, spu);	/* Step 27. */
	रुको_purge_complete(prev, spu);	/* Step 28. */
	setup_mfc_sr1(prev, spu);	/* Step 30. */
	save_spu_npc(prev, spu);	/* Step 31. */
	save_spu_privcntl(prev, spu);	/* Step 32. */
	reset_spu_privcntl(prev, spu);	/* Step 33. */
	save_spu_lslr(prev, spu);	/* Step 34. */
	reset_spu_lslr(prev, spu);	/* Step 35. */
	save_spu_cfg(prev, spu);	/* Step 36. */
	save_pm_trace(prev, spu);	/* Step 37. */
	save_mfc_rag(prev, spu);	/* Step 38. */
	save_ppu_mb_stat(prev, spu);	/* Step 39. */
	save_ppu_mb(prev, spu);	        /* Step 40. */
	save_ppuपूर्णांक_mb(prev, spu);	/* Step 41. */
	save_ch_part1(prev, spu);	/* Step 42. */
	save_spu_mb(prev, spu);	        /* Step 43. */
	reset_ch(prev, spu);	        /* Step 45. */
पूर्ण

अटल व्योम save_lscsa(काष्ठा spu_state *prev, काष्ठा spu *spu)
अणु
	/*
	 * Perक्रमm steps 46-57 of SPU context save sequence,
	 * which save regions of the local store and रेजिस्टर
	 * file.
	 */

	resume_mfc_queue(prev, spu);	/* Step 46. */
	/* Step 47. */
	setup_mfc_slbs(prev, spu, spu_save_code, माप(spu_save_code));
	set_चयन_active(prev, spu);	/* Step 48. */
	enable_पूर्णांकerrupts(prev, spu);	/* Step 49. */
	save_ls_16kb(prev, spu);	/* Step 50. */
	set_spu_npc(prev, spu);	        /* Step 51. */
	set_signot1(prev, spu);		/* Step 52. */
	set_signot2(prev, spu);		/* Step 53. */
	send_save_code(prev, spu);	/* Step 54. */
	set_ppu_querymask(prev, spu);	/* Step 55. */
	रुको_tag_complete(prev, spu);	/* Step 56. */
	रुको_spu_stopped(prev, spu);	/* Step 57. */
पूर्ण

अटल व्योम क्रमce_spu_isolate_निकास(काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;
	काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

	/* Stop SPE execution and रुको क्रम completion. */
	out_be32(&prob->spu_runcntl_RW, SPU_RUNCNTL_STOP);
	iobarrier_rw();
	POLL_WHILE_TRUE(in_be32(&prob->spu_status_R) & SPU_STATUS_RUNNING);

	/* Restart SPE master runcntl. */
	spu_mfc_sr1_set(spu, MFC_STATE1_MASTER_RUN_CONTROL_MASK);
	iobarrier_w();

	/* Initiate isolate निकास request and रुको क्रम completion. */
	out_be64(&priv2->spu_privcntl_RW, 4LL);
	iobarrier_w();
	out_be32(&prob->spu_runcntl_RW, 2);
	iobarrier_rw();
	POLL_WHILE_FALSE((in_be32(&prob->spu_status_R)
				& SPU_STATUS_STOPPED_BY_STOP));

	/* Reset load request to normal. */
	out_be64(&priv2->spu_privcntl_RW, SPU_PRIVCNT_LOAD_REQUEST_NORMAL);
	iobarrier_w();
पूर्ण

/**
 * stop_spu_isolate
 *	Check SPU run-control state and क्रमce isolated
 *	निकास function as necessary.
 */
अटल व्योम stop_spu_isolate(काष्ठा spu *spu)
अणु
	काष्ठा spu_problem __iomem *prob = spu->problem;

	अगर (in_be32(&prob->spu_status_R) & SPU_STATUS_ISOLATED_STATE) अणु
		/* The SPU is in isolated state; the only way
		 * to get it out is to perक्रमm an isolated
		 * निकास (clean) operation.
		 */
		क्रमce_spu_isolate_निकास(spu);
	पूर्ण
पूर्ण

अटल व्योम harvest(काष्ठा spu_state *prev, काष्ठा spu *spu)
अणु
	/*
	 * Perक्रमm steps 2-25 of SPU context restore sequence,
	 * which resets an SPU either after a failed save, or
	 * when using SPU क्रम first समय.
	 */

	disable_पूर्णांकerrupts(prev, spu);	        /* Step 2.  */
	inhibit_user_access(prev, spu);	        /* Step 3.  */
	terminate_spu_app(prev, spu);	        /* Step 4.  */
	set_चयन_pending(prev, spu);	        /* Step 5.  */
	stop_spu_isolate(spu);			/* NEW.     */
	हटाओ_other_spu_access(prev, spu);	/* Step 6.  */
	suspend_mfc_and_halt_decr(prev, spu);	/* Step 7.  */
	रुको_suspend_mfc_complete(prev, spu);	/* Step 8.  */
	अगर (!suspend_spe(prev, spu))	        /* Step 9.  */
		clear_spu_status(prev, spu);	/* Step 10. */
	करो_mfc_mssync(prev, spu);	        /* Step 11. */
	issue_mfc_tlbie(prev, spu);	        /* Step 12. */
	handle_pending_पूर्णांकerrupts(prev, spu);	/* Step 13. */
	purge_mfc_queue(prev, spu);	        /* Step 14. */
	रुको_purge_complete(prev, spu);	        /* Step 15. */
	reset_spu_privcntl(prev, spu);	        /* Step 16. */
	reset_spu_lslr(prev, spu);              /* Step 17. */
	setup_mfc_sr1(prev, spu);	        /* Step 18. */
	spu_invalidate_slbs(spu);		/* Step 19. */
	reset_ch_part1(prev, spu);	        /* Step 20. */
	reset_ch_part2(prev, spu);	        /* Step 21. */
	enable_पूर्णांकerrupts(prev, spu);	        /* Step 22. */
	set_चयन_active(prev, spu);	        /* Step 23. */
	set_mfc_tclass_id(prev, spu);	        /* Step 24. */
	resume_mfc_queue(prev, spu);	        /* Step 25. */
पूर्ण

अटल व्योम restore_lscsa(काष्ठा spu_state *next, काष्ठा spu *spu)
अणु
	/*
	 * Perक्रमm steps 26-40 of SPU context restore sequence,
	 * which restores regions of the local store and रेजिस्टर
	 * file.
	 */

	set_watchकरोg_समयr(next, spu);	        /* Step 26. */
	setup_spu_status_part1(next, spu);	/* Step 27. */
	setup_spu_status_part2(next, spu);	/* Step 28. */
	restore_mfc_rag(next, spu);	        /* Step 29. */
	/* Step 30. */
	setup_mfc_slbs(next, spu, spu_restore_code, माप(spu_restore_code));
	set_spu_npc(next, spu);	                /* Step 31. */
	set_signot1(next, spu);	                /* Step 32. */
	set_signot2(next, spu);	                /* Step 33. */
	setup_decr(next, spu);	                /* Step 34. */
	setup_ppu_mb(next, spu);	        /* Step 35. */
	setup_ppuपूर्णांक_mb(next, spu);	        /* Step 36. */
	send_restore_code(next, spu);	        /* Step 37. */
	set_ppu_querymask(next, spu);	        /* Step 38. */
	रुको_tag_complete(next, spu);	        /* Step 39. */
	रुको_spu_stopped(next, spu);	        /* Step 40. */
पूर्ण

अटल व्योम restore_csa(काष्ठा spu_state *next, काष्ठा spu *spu)
अणु
	/*
	 * Combine steps 41-76 of SPU context restore sequence, which
	 * restore regions of the privileged & problem state areas.
	 */

	restore_spu_privcntl(next, spu);	/* Step 41. */
	restore_status_part1(next, spu);	/* Step 42. */
	restore_status_part2(next, spu);	/* Step 43. */
	restore_ls_16kb(next, spu);	        /* Step 44. */
	रुको_tag_complete(next, spu);	        /* Step 45. */
	suspend_mfc(next, spu);	                /* Step 46. */
	रुको_suspend_mfc_complete(next, spu);	/* Step 47. */
	issue_mfc_tlbie(next, spu);	        /* Step 48. */
	clear_पूर्णांकerrupts(next, spu);	        /* Step 49. */
	restore_mfc_queues(next, spu);	        /* Step 50. */
	restore_ppu_querymask(next, spu);	/* Step 51. */
	restore_ppu_querytype(next, spu);	/* Step 52. */
	restore_mfc_csr_tsq(next, spu);	        /* Step 53. */
	restore_mfc_csr_cmd(next, spu);	        /* Step 54. */
	restore_mfc_csr_ato(next, spu);	        /* Step 55. */
	restore_mfc_tclass_id(next, spu);	/* Step 56. */
	set_llr_event(next, spu);	        /* Step 57. */
	restore_decr_wrapped(next, spu);	/* Step 58. */
	restore_ch_part1(next, spu);	        /* Step 59. */
	restore_ch_part2(next, spu);	        /* Step 60. */
	restore_spu_lslr(next, spu);	        /* Step 61. */
	restore_spu_cfg(next, spu);	        /* Step 62. */
	restore_pm_trace(next, spu);	        /* Step 63. */
	restore_spu_npc(next, spu);	        /* Step 64. */
	restore_spu_mb(next, spu);	        /* Step 65. */
	check_ppu_mb_stat(next, spu);	        /* Step 66. */
	check_ppuपूर्णांक_mb_stat(next, spu);	/* Step 67. */
	spu_invalidate_slbs(spu);		/* Modअगरied Step 68. */
	restore_mfc_sr1(next, spu);	        /* Step 69. */
	set_पूर्णांक_route(next, spu);		/* NEW      */
	restore_other_spu_access(next, spu);	/* Step 70. */
	restore_spu_runcntl(next, spu);	        /* Step 71. */
	restore_mfc_cntl(next, spu);	        /* Step 72. */
	enable_user_access(next, spu);	        /* Step 73. */
	reset_चयन_active(next, spu);	        /* Step 74. */
	reenable_पूर्णांकerrupts(next, spu);	        /* Step 75. */
पूर्ण

अटल पूर्णांक __करो_spu_save(काष्ठा spu_state *prev, काष्ठा spu *spu)
अणु
	पूर्णांक rc;

	/*
	 * SPU context save can be broken पूर्णांकo three phases:
	 *
	 *     (a) quiesce [steps 2-16].
	 *     (b) save of CSA, perक्रमmed by PPE [steps 17-42]
	 *     (c) save of LSCSA, mostly perक्रमmed by SPU [steps 43-52].
	 *
	 * Returns      0 on success.
	 *              2,6 अगर failed to quiece SPU
	 *              53 अगर SPU-side of save failed.
	 */

	rc = quiece_spu(prev, spu);	        /* Steps 2-16. */
	चयन (rc) अणु
	शेष:
	हाल 2:
	हाल 6:
		harvest(prev, spu);
		वापस rc;
		अवरोध;
	हाल 0:
		अवरोध;
	पूर्ण
	save_csa(prev, spu);	                /* Steps 17-43. */
	save_lscsa(prev, spu);	                /* Steps 44-53. */
	वापस check_save_status(prev, spu);	/* Step 54.     */
पूर्ण

अटल पूर्णांक __करो_spu_restore(काष्ठा spu_state *next, काष्ठा spu *spu)
अणु
	पूर्णांक rc;

	/*
	 * SPU context restore can be broken पूर्णांकo three phases:
	 *
	 *    (a) harvest (or reset) SPU [steps 2-24].
	 *    (b) restore LSCSA [steps 25-40], mostly perक्रमmed by SPU.
	 *    (c) restore CSA [steps 41-76], perक्रमmed by PPE.
	 *
	 * The 'harvest' step is not perक्रमmed here, but rather
	 * as needed below.
	 */

	restore_lscsa(next, spu);	        /* Steps 24-39. */
	rc = check_restore_status(next, spu);	/* Step 40.     */
	चयन (rc) अणु
	शेष:
		/* Failed. Return now. */
		वापस rc;
		अवरोध;
	हाल 0:
		/* Fall through to next step. */
		अवरोध;
	पूर्ण
	restore_csa(next, spu);

	वापस 0;
पूर्ण

/**
 * spu_save - SPU context save, with locking.
 * @prev: poपूर्णांकer to SPU context save area, to be saved.
 * @spu: poपूर्णांकer to SPU iomem काष्ठाure.
 *
 * Acquire locks, perक्रमm the save operation then वापस.
 */
पूर्णांक spu_save(काष्ठा spu_state *prev, काष्ठा spu *spu)
अणु
	पूर्णांक rc;

	acquire_spu_lock(spu);	        /* Step 1.     */
	rc = __करो_spu_save(prev, spu);	/* Steps 2-53. */
	release_spu_lock(spu);
	अगर (rc != 0 && rc != 2 && rc != 6) अणु
		panic("%s failed on SPU[%d], rc=%d.\n",
		      __func__, spu->number, rc);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spu_save);

/**
 * spu_restore - SPU context restore, with harvest and locking.
 * @new: poपूर्णांकer to SPU context save area, to be restored.
 * @spu: poपूर्णांकer to SPU iomem काष्ठाure.
 *
 * Perक्रमm harvest + restore, as we may not be coming
 * from a previous successful save operation, and the
 * hardware state is unknown.
 */
पूर्णांक spu_restore(काष्ठा spu_state *new, काष्ठा spu *spu)
अणु
	पूर्णांक rc;

	acquire_spu_lock(spu);
	harvest(शून्य, spu);
	spu->slb_replace = 0;
	rc = __करो_spu_restore(new, spu);
	release_spu_lock(spu);
	अगर (rc) अणु
		panic("%s failed on SPU[%d] rc=%d.\n",
		       __func__, spu->number, rc);
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(spu_restore);

अटल व्योम init_prob(काष्ठा spu_state *csa)
अणु
	csa->spu_chnlcnt_RW[9] = 1;
	csa->spu_chnlcnt_RW[21] = 16;
	csa->spu_chnlcnt_RW[23] = 1;
	csa->spu_chnlcnt_RW[28] = 1;
	csa->spu_chnlcnt_RW[30] = 1;
	csa->prob.spu_runcntl_RW = SPU_RUNCNTL_STOP;
	csa->prob.mb_stat_R = 0x000400;
पूर्ण

अटल व्योम init_priv1(काष्ठा spu_state *csa)
अणु
	/* Enable decode, relocate, tlbie response, master runcntl. */
	csa->priv1.mfc_sr1_RW = MFC_STATE1_LOCAL_STORAGE_DECODE_MASK |
	    MFC_STATE1_MASTER_RUN_CONTROL_MASK |
	    MFC_STATE1_PROBLEM_STATE_MASK |
	    MFC_STATE1_RELOCATE_MASK | MFC_STATE1_BUS_TLBIE_MASK;

	/* Enable OS-specअगरic set of पूर्णांकerrupts. */
	csa->priv1.पूर्णांक_mask_class0_RW = CLASS0_ENABLE_DMA_ALIGNMENT_INTR |
	    CLASS0_ENABLE_INVALID_DMA_COMMAND_INTR |
	    CLASS0_ENABLE_SPU_ERROR_INTR;
	csa->priv1.पूर्णांक_mask_class1_RW = CLASS1_ENABLE_SEGMENT_FAULT_INTR |
	    CLASS1_ENABLE_STORAGE_FAULT_INTR;
	csa->priv1.पूर्णांक_mask_class2_RW = CLASS2_ENABLE_SPU_STOP_INTR |
	    CLASS2_ENABLE_SPU_HALT_INTR |
	    CLASS2_ENABLE_SPU_DMA_TAG_GROUP_COMPLETE_INTR;
पूर्ण

अटल व्योम init_priv2(काष्ठा spu_state *csa)
अणु
	csa->priv2.spu_lslr_RW = LS_ADDR_MASK;
	csa->priv2.mfc_control_RW = MFC_CNTL_RESUME_DMA_QUEUE |
	    MFC_CNTL_NORMAL_DMA_QUEUE_OPERATION |
	    MFC_CNTL_DMA_QUEUES_EMPTY_MASK;
पूर्ण

/**
 * spu_alloc_csa - allocate and initialize an SPU context save area.
 *
 * Allocate and initialize the contents of an SPU context save area.
 * This includes enabling address translation, पूर्णांकerrupt masks, etc.,
 * as appropriate क्रम the given OS environment.
 *
 * Note that storage क्रम the 'lscsa' is allocated separately,
 * as it is by far the largest of the context save regions,
 * and may need to be pinned or otherwise specially aligned.
 */
पूर्णांक spu_init_csa(काष्ठा spu_state *csa)
अणु
	पूर्णांक rc;

	अगर (!csa)
		वापस -EINVAL;
	स_रखो(csa, 0, माप(काष्ठा spu_state));

	rc = spu_alloc_lscsa(csa);
	अगर (rc)
		वापस rc;

	spin_lock_init(&csa->रेजिस्टर_lock);

	init_prob(csa);
	init_priv1(csa);
	init_priv2(csa);

	वापस 0;
पूर्ण

व्योम spu_fini_csa(काष्ठा spu_state *csa)
अणु
	spu_मुक्त_lscsa(csa);
पूर्ण
