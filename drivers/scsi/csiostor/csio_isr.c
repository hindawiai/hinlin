<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2008-2012 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/माला.स>

#समावेश "csio_init.h"
#समावेश "csio_hw.h"

अटल irqवापस_t
csio_nondata_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा csio_hw *hw = (काष्ठा csio_hw *) dev_id;
	पूर्णांक rv;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!hw))
		वापस IRQ_NONE;

	अगर (unlikely(pci_channel_offline(hw->pdev))) अणु
		CSIO_INC_STATS(hw, n_pcich_offline);
		वापस IRQ_NONE;
	पूर्ण

	spin_lock_irqsave(&hw->lock, flags);
	csio_hw_slow_पूर्णांकr_handler(hw);
	rv = csio_mb_isr_handler(hw);

	अगर (rv == 0 && !(hw->flags & CSIO_HWF_FWEVT_PENDING)) अणु
		hw->flags |= CSIO_HWF_FWEVT_PENDING;
		spin_unlock_irqrestore(&hw->lock, flags);
		schedule_work(&hw->evtq_work);
		वापस IRQ_HANDLED;
	पूर्ण
	spin_unlock_irqrestore(&hw->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * csio_fwevt_handler - Common FW event handler routine.
 * @hw: HW module.
 *
 * This is the ISR क्रम FW events. It is shared b/w MSIX
 * and INTx handlers.
 */
अटल व्योम
csio_fwevt_handler(काष्ठा csio_hw *hw)
अणु
	पूर्णांक rv;
	अचिन्हित दीर्घ flags;

	rv = csio_fwevtq_handler(hw);

	spin_lock_irqsave(&hw->lock, flags);
	अगर (rv == 0 && !(hw->flags & CSIO_HWF_FWEVT_PENDING)) अणु
		hw->flags |= CSIO_HWF_FWEVT_PENDING;
		spin_unlock_irqrestore(&hw->lock, flags);
		schedule_work(&hw->evtq_work);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&hw->lock, flags);

पूर्ण /* csio_fwevt_handler */

/*
 * csio_fwevt_isr() - FW events MSIX ISR
 * @irq:
 * @dev_id:
 *
 * Process WRs on the FW event queue.
 *
 */
अटल irqवापस_t
csio_fwevt_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा csio_hw *hw = (काष्ठा csio_hw *) dev_id;

	अगर (unlikely(!hw))
		वापस IRQ_NONE;

	अगर (unlikely(pci_channel_offline(hw->pdev))) अणु
		CSIO_INC_STATS(hw, n_pcich_offline);
		वापस IRQ_NONE;
	पूर्ण

	csio_fwevt_handler(hw);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * csio_fwevt_isr() - INTx wrapper क्रम handling FW events.
 * @irq:
 * @dev_id:
 */
व्योम
csio_fwevt_पूर्णांकx_handler(काष्ठा csio_hw *hw, व्योम *wr, uपूर्णांक32_t len,
			   काष्ठा csio_fl_dma_buf *flb, व्योम *priv)
अणु
	csio_fwevt_handler(hw);
पूर्ण /* csio_fwevt_पूर्णांकx_handler */

/*
 * csio_process_scsi_cmpl - Process a SCSI WR completion.
 * @hw: HW module.
 * @wr: The completed WR from the ingress queue.
 * @len: Length of the WR.
 * @flb: Freelist buffer array.
 *
 */
अटल व्योम
csio_process_scsi_cmpl(काष्ठा csio_hw *hw, व्योम *wr, uपूर्णांक32_t len,
			काष्ठा csio_fl_dma_buf *flb, व्योम *cbfn_q)
अणु
	काष्ठा csio_ioreq *ioreq;
	uपूर्णांक8_t *scsiwr;
	uपूर्णांक8_t subop;
	व्योम *cmnd;
	अचिन्हित दीर्घ flags;

	ioreq = csio_scsi_cmpl_handler(hw, wr, len, flb, शून्य, &scsiwr);
	अगर (likely(ioreq)) अणु
		अगर (unlikely(*scsiwr == FW_SCSI_ABRT_CLS_WR)) अणु
			subop = FW_SCSI_ABRT_CLS_WR_SUB_OPCODE_GET(
					((काष्ठा fw_scsi_abrt_cls_wr *)
					    scsiwr)->sub_opcode_to_chk_all_io);

			csio_dbg(hw, "%s cmpl recvd ioreq:%p status:%d\n",
				    subop ? "Close" : "Abort",
				    ioreq, ioreq->wr_status);

			spin_lock_irqsave(&hw->lock, flags);
			अगर (subop)
				csio_scsi_बंदd(ioreq,
						 (काष्ठा list_head *)cbfn_q);
			अन्यथा
				csio_scsi_पातed(ioreq,
						  (काष्ठा list_head *)cbfn_q);
			/*
			 * We call scsi_करोne क्रम I/Os that driver thinks पातs
			 * have समयd out. If there is a race caused by FW
			 * completing पात at the exact same समय that the
			 * driver has deteced the पात समयout, the following
			 * check prevents calling of scsi_करोne twice क्रम the
			 * same command: once from the eh_पात_handler, another
			 * from csio_scsi_isr_handler(). This also aव्योमs the
			 * need to check अगर csio_scsi_cmnd(req) is शून्य in the
			 * fast path.
			 */
			cmnd = csio_scsi_cmnd(ioreq);
			अगर (unlikely(cmnd == शून्य))
				list_del_init(&ioreq->sm.sm_list);

			spin_unlock_irqrestore(&hw->lock, flags);

			अगर (unlikely(cmnd == शून्य))
				csio_put_scsi_ioreq_lock(hw,
						csio_hw_to_scsim(hw), ioreq);
		पूर्ण अन्यथा अणु
			spin_lock_irqsave(&hw->lock, flags);
			csio_scsi_completed(ioreq, (काष्ठा list_head *)cbfn_q);
			spin_unlock_irqrestore(&hw->lock, flags);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * csio_scsi_isr_handler() - Common SCSI ISR handler.
 * @iq: Ingress queue poपूर्णांकer.
 *
 * Processes SCSI completions on the SCSI IQ indicated by scm->iq_idx
 * by calling csio_wr_process_iq_idx. If there are completions on the
 * isr_cbfn_q, yank them out पूर्णांकo a local queue and call their io_cbfns.
 * Once करोne, add these completions onto the मुक्तlist.
 * This routine is shared b/w MSIX and INTx.
 */
अटल अंतरभूत irqवापस_t
csio_scsi_isr_handler(काष्ठा csio_q *iq)
अणु
	काष्ठा csio_hw *hw = (काष्ठा csio_hw *)iq->owner;
	LIST_HEAD(cbfn_q);
	काष्ठा list_head *पंचांगp;
	काष्ठा csio_scsim *scm;
	काष्ठा csio_ioreq *ioreq;
	पूर्णांक isr_completions = 0;

	scm = csio_hw_to_scsim(hw);

	अगर (unlikely(csio_wr_process_iq(hw, iq, csio_process_scsi_cmpl,
					&cbfn_q) != 0))
		वापस IRQ_NONE;

	/* Call back the completion routines */
	list_क्रम_each(पंचांगp, &cbfn_q) अणु
		ioreq = (काष्ठा csio_ioreq *)पंचांगp;
		isr_completions++;
		ioreq->io_cbfn(hw, ioreq);
		/* Release ddp buffer अगर used क्रम this req */
		अगर (unlikely(ioreq->dcopy))
			csio_put_scsi_ddp_list_lock(hw, scm, &ioreq->gen_list,
						    ioreq->nsge);
	पूर्ण

	अगर (isr_completions) अणु
		/* Return the ioreqs back to ioreq->मुक्तlist */
		csio_put_scsi_ioreq_list_lock(hw, scm, &cbfn_q,
					      isr_completions);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * csio_scsi_isr() - SCSI MSIX handler
 * @irq:
 * @dev_id:
 *
 * This is the top level SCSI MSIX handler. Calls csio_scsi_isr_handler()
 * क्रम handling SCSI completions.
 */
अटल irqवापस_t
csio_scsi_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा csio_q *iq = (काष्ठा csio_q *) dev_id;
	काष्ठा csio_hw *hw;

	अगर (unlikely(!iq))
		वापस IRQ_NONE;

	hw = (काष्ठा csio_hw *)iq->owner;

	अगर (unlikely(pci_channel_offline(hw->pdev))) अणु
		CSIO_INC_STATS(hw, n_pcich_offline);
		वापस IRQ_NONE;
	पूर्ण

	csio_scsi_isr_handler(iq);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * csio_scsi_पूर्णांकx_handler() - SCSI INTx handler
 * @irq:
 * @dev_id:
 *
 * This is the top level SCSI INTx handler. Calls csio_scsi_isr_handler()
 * क्रम handling SCSI completions.
 */
व्योम
csio_scsi_पूर्णांकx_handler(काष्ठा csio_hw *hw, व्योम *wr, uपूर्णांक32_t len,
			काष्ठा csio_fl_dma_buf *flb, व्योम *priv)
अणु
	काष्ठा csio_q *iq = priv;

	csio_scsi_isr_handler(iq);

पूर्ण /* csio_scsi_पूर्णांकx_handler */

/*
 * csio_fcoe_isr() - INTx/MSI पूर्णांकerrupt service routine क्रम FCoE.
 * @irq:
 * @dev_id:
 *
 *
 */
अटल irqवापस_t
csio_fcoe_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा csio_hw *hw = (काष्ठा csio_hw *) dev_id;
	काष्ठा csio_q *पूर्णांकx_q = शून्य;
	पूर्णांक rv;
	irqवापस_t ret = IRQ_NONE;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!hw))
		वापस IRQ_NONE;

	अगर (unlikely(pci_channel_offline(hw->pdev))) अणु
		CSIO_INC_STATS(hw, n_pcich_offline);
		वापस IRQ_NONE;
	पूर्ण

	/* Disable the पूर्णांकerrupt क्रम this PCI function. */
	अगर (hw->पूर्णांकr_mode == CSIO_IM_INTX)
		csio_wr_reg32(hw, 0, MYPF_REG(PCIE_PF_CLI_A));

	/*
	 * The पढ़ो in the following function will flush the
	 * above ग_लिखो.
	 */
	अगर (csio_hw_slow_पूर्णांकr_handler(hw))
		ret = IRQ_HANDLED;

	/* Get the INTx Forward पूर्णांकerrupt IQ. */
	पूर्णांकx_q = csio_get_q(hw, hw->पूर्णांकr_iq_idx);

	CSIO_DB_ASSERT(पूर्णांकx_q);

	/* IQ handler is not possible क्रम पूर्णांकx_q, hence pass in शून्य */
	अगर (likely(csio_wr_process_iq(hw, पूर्णांकx_q, शून्य, शून्य) == 0))
		ret = IRQ_HANDLED;

	spin_lock_irqsave(&hw->lock, flags);
	rv = csio_mb_isr_handler(hw);
	अगर (rv == 0 && !(hw->flags & CSIO_HWF_FWEVT_PENDING)) अणु
		hw->flags |= CSIO_HWF_FWEVT_PENDING;
		spin_unlock_irqrestore(&hw->lock, flags);
		schedule_work(&hw->evtq_work);
		वापस IRQ_HANDLED;
	पूर्ण
	spin_unlock_irqrestore(&hw->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम
csio_add_msix_desc(काष्ठा csio_hw *hw)
अणु
	पूर्णांक i;
	काष्ठा csio_msix_entries *entryp = &hw->msix_entries[0];
	पूर्णांक k = CSIO_EXTRA_VECS;
	पूर्णांक len = माप(entryp->desc) - 1;
	पूर्णांक cnt = hw->num_sqsets + k;

	/* Non-data vector */
	स_रखो(entryp->desc, 0, len + 1);
	snम_लिखो(entryp->desc, len, "csio-%02x:%02x:%x-nondata",
		 CSIO_PCI_BUS(hw), CSIO_PCI_DEV(hw), CSIO_PCI_FUNC(hw));

	entryp++;
	स_रखो(entryp->desc, 0, len + 1);
	snम_लिखो(entryp->desc, len, "csio-%02x:%02x:%x-fwevt",
		 CSIO_PCI_BUS(hw), CSIO_PCI_DEV(hw), CSIO_PCI_FUNC(hw));
	entryp++;

	/* Name SCSI vecs */
	क्रम (i = k; i < cnt; i++, entryp++) अणु
		स_रखो(entryp->desc, 0, len + 1);
		snम_लिखो(entryp->desc, len, "csio-%02x:%02x:%x-scsi%d",
			 CSIO_PCI_BUS(hw), CSIO_PCI_DEV(hw),
			 CSIO_PCI_FUNC(hw), i - CSIO_EXTRA_VECS);
	पूर्ण
पूर्ण

पूर्णांक
csio_request_irqs(काष्ठा csio_hw *hw)
अणु
	पूर्णांक rv, i, j, k = 0;
	काष्ठा csio_msix_entries *entryp = &hw->msix_entries[0];
	काष्ठा csio_scsi_cpu_info *info;
	काष्ठा pci_dev *pdev = hw->pdev;

	अगर (hw->पूर्णांकr_mode != CSIO_IM_MSIX) अणु
		rv = request_irq(pci_irq_vector(pdev, 0), csio_fcoe_isr,
				hw->पूर्णांकr_mode == CSIO_IM_MSI ? 0 : IRQF_SHARED,
				KBUILD_MODNAME, hw);
		अगर (rv) अणु
			csio_err(hw, "Failed to allocate interrupt line.\n");
			जाओ out_मुक्त_irqs;
		पूर्ण

		जाओ out;
	पूर्ण

	/* Add the MSIX vector descriptions */
	csio_add_msix_desc(hw);

	rv = request_irq(pci_irq_vector(pdev, k), csio_nondata_isr, 0,
			 entryp[k].desc, hw);
	अगर (rv) अणु
		csio_err(hw, "IRQ request failed for vec %d err:%d\n",
			 pci_irq_vector(pdev, k), rv);
		जाओ out_मुक्त_irqs;
	पूर्ण

	entryp[k++].dev_id = hw;

	rv = request_irq(pci_irq_vector(pdev, k), csio_fwevt_isr, 0,
			 entryp[k].desc, hw);
	अगर (rv) अणु
		csio_err(hw, "IRQ request failed for vec %d err:%d\n",
			 pci_irq_vector(pdev, k), rv);
		जाओ out_मुक्त_irqs;
	पूर्ण

	entryp[k++].dev_id = (व्योम *)hw;

	/* Allocate IRQs क्रम SCSI */
	क्रम (i = 0; i < hw->num_pports; i++) अणु
		info = &hw->scsi_cpu_info[i];
		क्रम (j = 0; j < info->max_cpus; j++, k++) अणु
			काष्ठा csio_scsi_qset *sqset = &hw->sqset[i][j];
			काष्ठा csio_q *q = hw->wrm.q_arr[sqset->iq_idx];

			rv = request_irq(pci_irq_vector(pdev, k), csio_scsi_isr, 0,
					 entryp[k].desc, q);
			अगर (rv) अणु
				csio_err(hw,
				       "IRQ request failed for vec %d err:%d\n",
				       pci_irq_vector(pdev, k), rv);
				जाओ out_मुक्त_irqs;
			पूर्ण

			entryp[k].dev_id = q;

		पूर्ण /* क्रम all scsi cpus */
	पूर्ण /* क्रम all ports */

out:
	hw->flags |= CSIO_HWF_HOST_INTR_ENABLED;
	वापस 0;

out_मुक्त_irqs:
	क्रम (i = 0; i < k; i++)
		मुक्त_irq(pci_irq_vector(pdev, i), hw->msix_entries[i].dev_id);
	pci_मुक्त_irq_vectors(hw->pdev);
	वापस -EINVAL;
पूर्ण

/* Reduce per-port max possible CPUs */
अटल व्योम
csio_reduce_sqsets(काष्ठा csio_hw *hw, पूर्णांक cnt)
अणु
	पूर्णांक i;
	काष्ठा csio_scsi_cpu_info *info;

	जबतक (cnt < hw->num_sqsets) अणु
		क्रम (i = 0; i < hw->num_pports; i++) अणु
			info = &hw->scsi_cpu_info[i];
			अगर (info->max_cpus > 1) अणु
				info->max_cpus--;
				hw->num_sqsets--;
				अगर (hw->num_sqsets <= cnt)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	csio_dbg(hw, "Reduced sqsets to %d\n", hw->num_sqsets);
पूर्ण

अटल व्योम csio_calc_sets(काष्ठा irq_affinity *affd, अचिन्हित पूर्णांक nvecs)
अणु
	काष्ठा csio_hw *hw = affd->priv;
	u8 i;

	अगर (!nvecs)
		वापस;

	अगर (nvecs < hw->num_pports) अणु
		affd->nr_sets = 1;
		affd->set_size[0] = nvecs;
		वापस;
	पूर्ण

	affd->nr_sets = hw->num_pports;
	क्रम (i = 0; i < hw->num_pports; i++)
		affd->set_size[i] = nvecs / hw->num_pports;
पूर्ण

अटल पूर्णांक
csio_enable_msix(काष्ठा csio_hw *hw)
अणु
	पूर्णांक i, j, k, n, min, cnt;
	पूर्णांक extra = CSIO_EXTRA_VECS;
	काष्ठा csio_scsi_cpu_info *info;
	काष्ठा irq_affinity desc = अणु
		.pre_vectors = CSIO_EXTRA_VECS,
		.calc_sets = csio_calc_sets,
		.priv = hw,
	पूर्ण;

	अगर (hw->num_pports > IRQ_AFFINITY_MAX_SETS)
		वापस -ENOSPC;

	min = hw->num_pports + extra;
	cnt = hw->num_sqsets + extra;

	/* Max vectors required based on #niqs configured in fw */
	अगर (hw->flags & CSIO_HWF_USING_SOFT_PARAMS || !csio_is_hw_master(hw))
		cnt = min_t(uपूर्णांक8_t, hw->cfg_niq, cnt);

	csio_dbg(hw, "FW supp #niq:%d, trying %d msix's\n", hw->cfg_niq, cnt);

	cnt = pci_alloc_irq_vectors_affinity(hw->pdev, min, cnt,
			PCI_IRQ_MSIX | PCI_IRQ_AFFINITY, &desc);
	अगर (cnt < 0)
		वापस cnt;

	अगर (cnt < (hw->num_sqsets + extra)) अणु
		csio_dbg(hw, "Reducing sqsets to %d\n", cnt - extra);
		csio_reduce_sqsets(hw, cnt - extra);
	पूर्ण

	/* Distribute vectors */
	k = 0;
	csio_set_nondata_पूर्णांकr_idx(hw, k);
	csio_set_mb_पूर्णांकr_idx(csio_hw_to_mbm(hw), k++);
	csio_set_fwevt_पूर्णांकr_idx(hw, k++);

	क्रम (i = 0; i < hw->num_pports; i++) अणु
		info = &hw->scsi_cpu_info[i];

		क्रम (j = 0; j < hw->num_scsi_msix_cpus; j++) अणु
			n = (j % info->max_cpus) +  k;
			hw->sqset[i][j].पूर्णांकr_idx = n;
		पूर्ण

		k += info->max_cpus;
	पूर्ण

	वापस 0;
पूर्ण

व्योम
csio_पूर्णांकr_enable(काष्ठा csio_hw *hw)
अणु
	hw->पूर्णांकr_mode = CSIO_IM_NONE;
	hw->flags &= ~CSIO_HWF_HOST_INTR_ENABLED;

	/* Try MSIX, then MSI or fall back to INTx */
	अगर ((csio_msi == 2) && !csio_enable_msix(hw))
		hw->पूर्णांकr_mode = CSIO_IM_MSIX;
	अन्यथा अणु
		/* Max iqs required based on #niqs configured in fw */
		अगर (hw->flags & CSIO_HWF_USING_SOFT_PARAMS ||
			!csio_is_hw_master(hw)) अणु
			पूर्णांक extra = CSIO_EXTRA_MSI_IQS;

			अगर (hw->cfg_niq < (hw->num_sqsets + extra)) अणु
				csio_dbg(hw, "Reducing sqsets to %d\n",
					 hw->cfg_niq - extra);
				csio_reduce_sqsets(hw, hw->cfg_niq - extra);
			पूर्ण
		पूर्ण

		अगर ((csio_msi == 1) && !pci_enable_msi(hw->pdev))
			hw->पूर्णांकr_mode = CSIO_IM_MSI;
		अन्यथा
			hw->पूर्णांकr_mode = CSIO_IM_INTX;
	पूर्ण

	csio_dbg(hw, "Using %s interrupt mode.\n",
		(hw->पूर्णांकr_mode == CSIO_IM_MSIX) ? "MSIX" :
		((hw->पूर्णांकr_mode == CSIO_IM_MSI) ? "MSI" : "INTx"));
पूर्ण

व्योम
csio_पूर्णांकr_disable(काष्ठा csio_hw *hw, bool मुक्त)
अणु
	csio_hw_पूर्णांकr_disable(hw);

	अगर (मुक्त) अणु
		पूर्णांक i;

		चयन (hw->पूर्णांकr_mode) अणु
		हाल CSIO_IM_MSIX:
			क्रम (i = 0; i < hw->num_sqsets + CSIO_EXTRA_VECS; i++) अणु
				मुक्त_irq(pci_irq_vector(hw->pdev, i),
					 hw->msix_entries[i].dev_id);
			पूर्ण
			अवरोध;
		हाल CSIO_IM_MSI:
		हाल CSIO_IM_INTX:
			मुक्त_irq(pci_irq_vector(hw->pdev, 0), hw);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	pci_मुक्त_irq_vectors(hw->pdev);
	hw->पूर्णांकr_mode = CSIO_IM_NONE;
	hw->flags &= ~CSIO_HWF_HOST_INTR_ENABLED;
पूर्ण
