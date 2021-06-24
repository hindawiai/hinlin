<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel I/OAT DMA Linux driver
 * Copyright(c) 2004 - 2015 Intel Corporation.
 */

/*
 * This driver supports an Intel I/OAT DMA engine, which करोes asynchronous
 * copy operations.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/sizes.h>
#समावेश "dma.h"
#समावेश "registers.h"
#समावेश "hw.h"

#समावेश "../dmaengine.h"

अटल पूर्णांक completion_समयout = 200;
module_param(completion_समयout, पूर्णांक, 0644);
MODULE_PARM_DESC(completion_समयout,
		"set ioat completion timeout [msec] (default 200 [msec])");
अटल पूर्णांक idle_समयout = 2000;
module_param(idle_समयout, पूर्णांक, 0644);
MODULE_PARM_DESC(idle_समयout,
		"set ioat idel timeout [msec] (default 2000 [msec])");

#घोषणा IDLE_TIMEOUT msecs_to_jअगरfies(idle_समयout)
#घोषणा COMPLETION_TIMEOUT msecs_to_jअगरfies(completion_समयout)

अटल अक्षर *chanerr_str[] = अणु
	"DMA Transfer Source Address Error",
	"DMA Transfer Destination Address Error",
	"Next Descriptor Address Error",
	"Descriptor Error",
	"Chan Address Value Error",
	"CHANCMD Error",
	"Chipset Uncorrectable Data Integrity Error",
	"DMA Uncorrectable Data Integrity Error",
	"Read Data Error",
	"Write Data Error",
	"Descriptor Control Error",
	"Descriptor Transfer Size Error",
	"Completion Address Error",
	"Interrupt Configuration Error",
	"Super extended descriptor Address Error",
	"Unaffiliated Error",
	"CRC or XOR P Error",
	"XOR Q Error",
	"Descriptor Count Error",
	"DIF All F detect Error",
	"Guard Tag verification Error",
	"Application Tag verification Error",
	"Reference Tag verification Error",
	"Bundle Bit Error",
	"Result DIF All F detect Error",
	"Result Guard Tag verification Error",
	"Result Application Tag verification Error",
	"Result Reference Tag verification Error",
पूर्ण;

अटल व्योम ioat_eh(काष्ठा ioatdma_chan *ioat_chan);

अटल व्योम ioat_prपूर्णांक_chanerrs(काष्ठा ioatdma_chan *ioat_chan, u32 chanerr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(chanerr_str); i++) अणु
		अगर ((chanerr >> i) & 1) अणु
			dev_err(to_dev(ioat_chan), "Err(%d): %s\n",
				i, chanerr_str[i]);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ioat_dma_करो_पूर्णांकerrupt - handler used क्रम single vector पूर्णांकerrupt mode
 * @irq: पूर्णांकerrupt id
 * @data: पूर्णांकerrupt data
 */
irqवापस_t ioat_dma_करो_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ioatdma_device *instance = data;
	काष्ठा ioatdma_chan *ioat_chan;
	अचिन्हित दीर्घ attnstatus;
	पूर्णांक bit;
	u8 पूर्णांकrctrl;

	पूर्णांकrctrl = पढ़ोb(instance->reg_base + IOAT_INTRCTRL_OFFSET);

	अगर (!(पूर्णांकrctrl & IOAT_INTRCTRL_MASTER_INT_EN))
		वापस IRQ_NONE;

	अगर (!(पूर्णांकrctrl & IOAT_INTRCTRL_INT_STATUS)) अणु
		ग_लिखोb(पूर्णांकrctrl, instance->reg_base + IOAT_INTRCTRL_OFFSET);
		वापस IRQ_NONE;
	पूर्ण

	attnstatus = पढ़ोl(instance->reg_base + IOAT_ATTNSTATUS_OFFSET);
	क्रम_each_set_bit(bit, &attnstatus, BITS_PER_LONG) अणु
		ioat_chan = ioat_chan_by_index(instance, bit);
		अगर (test_bit(IOAT_RUN, &ioat_chan->state))
			tasklet_schedule(&ioat_chan->cleanup_task);
	पूर्ण

	ग_लिखोb(पूर्णांकrctrl, instance->reg_base + IOAT_INTRCTRL_OFFSET);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * ioat_dma_करो_पूर्णांकerrupt_msix - handler used क्रम vector-per-channel पूर्णांकerrupt mode
 * @irq: पूर्णांकerrupt id
 * @data: पूर्णांकerrupt data
 */
irqवापस_t ioat_dma_करो_पूर्णांकerrupt_msix(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ioatdma_chan *ioat_chan = data;

	अगर (test_bit(IOAT_RUN, &ioat_chan->state))
		tasklet_schedule(&ioat_chan->cleanup_task);

	वापस IRQ_HANDLED;
पूर्ण

व्योम ioat_stop(काष्ठा ioatdma_chan *ioat_chan)
अणु
	काष्ठा ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	काष्ठा pci_dev *pdev = ioat_dma->pdev;
	पूर्णांक chan_id = chan_num(ioat_chan);
	काष्ठा msix_entry *msix;

	/* 1/ stop irq from firing tasklets
	 * 2/ stop the tasklet from re-arming irqs
	 */
	clear_bit(IOAT_RUN, &ioat_chan->state);

	/* flush inflight पूर्णांकerrupts */
	चयन (ioat_dma->irq_mode) अणु
	हाल IOAT_MSIX:
		msix = &ioat_dma->msix_entries[chan_id];
		synchronize_irq(msix->vector);
		अवरोध;
	हाल IOAT_MSI:
	हाल IOAT_INTX:
		synchronize_irq(pdev->irq);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* flush inflight समयrs */
	del_समयr_sync(&ioat_chan->समयr);

	/* flush inflight tasklet runs */
	tasklet_समाप्त(&ioat_chan->cleanup_task);

	/* final cleanup now that everything is quiesced and can't re-arm */
	ioat_cleanup_event(&ioat_chan->cleanup_task);
पूर्ण

अटल व्योम __ioat_issue_pending(काष्ठा ioatdma_chan *ioat_chan)
अणु
	ioat_chan->dmacount += ioat_ring_pending(ioat_chan);
	ioat_chan->issued = ioat_chan->head;
	ग_लिखोw(ioat_chan->dmacount,
	       ioat_chan->reg_base + IOAT_CHAN_DMACOUNT_OFFSET);
	dev_dbg(to_dev(ioat_chan),
		"%s: head: %#x tail: %#x issued: %#x count: %#x\n",
		__func__, ioat_chan->head, ioat_chan->tail,
		ioat_chan->issued, ioat_chan->dmacount);
पूर्ण

व्योम ioat_issue_pending(काष्ठा dma_chan *c)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);

	अगर (ioat_ring_pending(ioat_chan)) अणु
		spin_lock_bh(&ioat_chan->prep_lock);
		__ioat_issue_pending(ioat_chan);
		spin_unlock_bh(&ioat_chan->prep_lock);
	पूर्ण
पूर्ण

/**
 * ioat_update_pending - log pending descriptors
 * @ioat_chan: ioat+ channel
 *
 * Check अगर the number of unsubmitted descriptors has exceeded the
 * watermark.  Called with prep_lock held
 */
अटल व्योम ioat_update_pending(काष्ठा ioatdma_chan *ioat_chan)
अणु
	अगर (ioat_ring_pending(ioat_chan) > ioat_pending_level)
		__ioat_issue_pending(ioat_chan);
पूर्ण

अटल व्योम __ioat_start_null_desc(काष्ठा ioatdma_chan *ioat_chan)
अणु
	काष्ठा ioat_ring_ent *desc;
	काष्ठा ioat_dma_descriptor *hw;

	अगर (ioat_ring_space(ioat_chan) < 1) अणु
		dev_err(to_dev(ioat_chan),
			"Unable to start null desc - ring full\n");
		वापस;
	पूर्ण

	dev_dbg(to_dev(ioat_chan),
		"%s: head: %#x tail: %#x issued: %#x\n",
		__func__, ioat_chan->head, ioat_chan->tail, ioat_chan->issued);
	desc = ioat_get_ring_ent(ioat_chan, ioat_chan->head);

	hw = desc->hw;
	hw->ctl = 0;
	hw->ctl_f.null = 1;
	hw->ctl_f.पूर्णांक_en = 1;
	hw->ctl_f.compl_ग_लिखो = 1;
	/* set size to non-zero value (channel वापसs error when size is 0) */
	hw->size = शून्य_DESC_BUFFER_SIZE;
	hw->src_addr = 0;
	hw->dst_addr = 0;
	async_tx_ack(&desc->txd);
	ioat_set_chainaddr(ioat_chan, desc->txd.phys);
	dump_desc_dbg(ioat_chan, desc);
	/* make sure descriptors are written beक्रमe we submit */
	wmb();
	ioat_chan->head += 1;
	__ioat_issue_pending(ioat_chan);
पूर्ण

व्योम ioat_start_null_desc(काष्ठा ioatdma_chan *ioat_chan)
अणु
	spin_lock_bh(&ioat_chan->prep_lock);
	अगर (!test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		__ioat_start_null_desc(ioat_chan);
	spin_unlock_bh(&ioat_chan->prep_lock);
पूर्ण

अटल व्योम __ioat_restart_chan(काष्ठा ioatdma_chan *ioat_chan)
अणु
	/* set the tail to be re-issued */
	ioat_chan->issued = ioat_chan->tail;
	ioat_chan->dmacount = 0;
	mod_समयr(&ioat_chan->समयr, jअगरfies + COMPLETION_TIMEOUT);

	dev_dbg(to_dev(ioat_chan),
		"%s: head: %#x tail: %#x issued: %#x count: %#x\n",
		__func__, ioat_chan->head, ioat_chan->tail,
		ioat_chan->issued, ioat_chan->dmacount);

	अगर (ioat_ring_pending(ioat_chan)) अणु
		काष्ठा ioat_ring_ent *desc;

		desc = ioat_get_ring_ent(ioat_chan, ioat_chan->tail);
		ioat_set_chainaddr(ioat_chan, desc->txd.phys);
		__ioat_issue_pending(ioat_chan);
	पूर्ण अन्यथा
		__ioat_start_null_desc(ioat_chan);
पूर्ण

अटल पूर्णांक ioat_quiesce(काष्ठा ioatdma_chan *ioat_chan, अचिन्हित दीर्घ पंचांगo)
अणु
	अचिन्हित दीर्घ end = jअगरfies + पंचांगo;
	पूर्णांक err = 0;
	u32 status;

	status = ioat_chansts(ioat_chan);
	अगर (is_ioat_active(status) || is_ioat_idle(status))
		ioat_suspend(ioat_chan);
	जबतक (is_ioat_active(status) || is_ioat_idle(status)) अणु
		अगर (पंचांगo && समय_after(jअगरfies, end)) अणु
			err = -ETIMEDOUT;
			अवरोध;
		पूर्ण
		status = ioat_chansts(ioat_chan);
		cpu_relax();
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ioat_reset_sync(काष्ठा ioatdma_chan *ioat_chan, अचिन्हित दीर्घ पंचांगo)
अणु
	अचिन्हित दीर्घ end = jअगरfies + पंचांगo;
	पूर्णांक err = 0;

	ioat_reset(ioat_chan);
	जबतक (ioat_reset_pending(ioat_chan)) अणु
		अगर (end && समय_after(jअगरfies, end)) अणु
			err = -ETIMEDOUT;
			अवरोध;
		पूर्ण
		cpu_relax();
	पूर्ण

	वापस err;
पूर्ण

अटल dma_cookie_t ioat_tx_submit_unlock(काष्ठा dma_async_tx_descriptor *tx)
	__releases(&ioat_chan->prep_lock)
अणु
	काष्ठा dma_chan *c = tx->chan;
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);
	dma_cookie_t cookie;

	cookie = dma_cookie_assign(tx);
	dev_dbg(to_dev(ioat_chan), "%s: cookie: %d\n", __func__, cookie);

	अगर (!test_and_set_bit(IOAT_CHAN_ACTIVE, &ioat_chan->state))
		mod_समयr(&ioat_chan->समयr, jअगरfies + COMPLETION_TIMEOUT);

	/* make descriptor updates visible beक्रमe advancing ioat->head,
	 * this is purposefully not smp_wmb() since we are also
	 * publishing the descriptor updates to a dma device
	 */
	wmb();

	ioat_chan->head += ioat_chan->produce;

	ioat_update_pending(ioat_chan);
	spin_unlock_bh(&ioat_chan->prep_lock);

	वापस cookie;
पूर्ण

अटल काष्ठा ioat_ring_ent *
ioat_alloc_ring_ent(काष्ठा dma_chan *chan, पूर्णांक idx, gfp_t flags)
अणु
	काष्ठा ioat_dma_descriptor *hw;
	काष्ठा ioat_ring_ent *desc;
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(chan);
	पूर्णांक chunk;
	dma_addr_t phys;
	u8 *pos;
	off_t offs;

	chunk = idx / IOAT_DESCS_PER_CHUNK;
	idx &= (IOAT_DESCS_PER_CHUNK - 1);
	offs = idx * IOAT_DESC_SZ;
	pos = (u8 *)ioat_chan->descs[chunk].virt + offs;
	phys = ioat_chan->descs[chunk].hw + offs;
	hw = (काष्ठा ioat_dma_descriptor *)pos;
	स_रखो(hw, 0, माप(*hw));

	desc = kmem_cache_zalloc(ioat_cache, flags);
	अगर (!desc)
		वापस शून्य;

	dma_async_tx_descriptor_init(&desc->txd, chan);
	desc->txd.tx_submit = ioat_tx_submit_unlock;
	desc->hw = hw;
	desc->txd.phys = phys;
	वापस desc;
पूर्ण

व्योम ioat_मुक्त_ring_ent(काष्ठा ioat_ring_ent *desc, काष्ठा dma_chan *chan)
अणु
	kmem_cache_मुक्त(ioat_cache, desc);
पूर्ण

काष्ठा ioat_ring_ent **
ioat_alloc_ring(काष्ठा dma_chan *c, पूर्णांक order, gfp_t flags)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);
	काष्ठा ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	काष्ठा ioat_ring_ent **ring;
	पूर्णांक total_descs = 1 << order;
	पूर्णांक i, chunks;

	/* allocate the array to hold the software ring */
	ring = kसुस्मृति(total_descs, माप(*ring), flags);
	अगर (!ring)
		वापस शून्य;

	chunks = (total_descs * IOAT_DESC_SZ) / IOAT_CHUNK_SIZE;
	ioat_chan->desc_chunks = chunks;

	क्रम (i = 0; i < chunks; i++) अणु
		काष्ठा ioat_descs *descs = &ioat_chan->descs[i];

		descs->virt = dma_alloc_coherent(to_dev(ioat_chan),
					IOAT_CHUNK_SIZE, &descs->hw, flags);
		अगर (!descs->virt) अणु
			पूर्णांक idx;

			क्रम (idx = 0; idx < i; idx++) अणु
				descs = &ioat_chan->descs[idx];
				dma_मुक्त_coherent(to_dev(ioat_chan),
						IOAT_CHUNK_SIZE,
						descs->virt, descs->hw);
				descs->virt = शून्य;
				descs->hw = 0;
			पूर्ण

			ioat_chan->desc_chunks = 0;
			kमुक्त(ring);
			वापस शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < total_descs; i++) अणु
		ring[i] = ioat_alloc_ring_ent(c, i, flags);
		अगर (!ring[i]) अणु
			पूर्णांक idx;

			जबतक (i--)
				ioat_मुक्त_ring_ent(ring[i], c);

			क्रम (idx = 0; idx < ioat_chan->desc_chunks; idx++) अणु
				dma_मुक्त_coherent(to_dev(ioat_chan),
						  IOAT_CHUNK_SIZE,
						  ioat_chan->descs[idx].virt,
						  ioat_chan->descs[idx].hw);
				ioat_chan->descs[idx].virt = शून्य;
				ioat_chan->descs[idx].hw = 0;
			पूर्ण

			ioat_chan->desc_chunks = 0;
			kमुक्त(ring);
			वापस शून्य;
		पूर्ण
		set_desc_id(ring[i], i);
	पूर्ण

	/* link descs */
	क्रम (i = 0; i < total_descs-1; i++) अणु
		काष्ठा ioat_ring_ent *next = ring[i+1];
		काष्ठा ioat_dma_descriptor *hw = ring[i]->hw;

		hw->next = next->txd.phys;
	पूर्ण
	ring[i]->hw->next = ring[0]->txd.phys;

	/* setup descriptor pre-fetching क्रम v3.4 */
	अगर (ioat_dma->cap & IOAT_CAP_DPS) अणु
		u16 drsctl = IOAT_CHAN_DRSZ_2MB | IOAT_CHAN_DRS_EN;

		अगर (chunks == 1)
			drsctl |= IOAT_CHAN_DRS_AUTOWRAP;

		ग_लिखोw(drsctl, ioat_chan->reg_base + IOAT_CHAN_DRSCTL_OFFSET);

	पूर्ण

	वापस ring;
पूर्ण

/**
 * ioat_check_space_lock - verअगरy space and grab ring producer lock
 * @ioat_chan: ioat,3 channel (ring) to operate on
 * @num_descs: allocation length
 */
पूर्णांक ioat_check_space_lock(काष्ठा ioatdma_chan *ioat_chan, पूर्णांक num_descs)
	__acquires(&ioat_chan->prep_lock)
अणु
	spin_lock_bh(&ioat_chan->prep_lock);
	/* never allow the last descriptor to be consumed, we need at
	 * least one मुक्त at all बार to allow क्रम on-the-fly ring
	 * resizing.
	 */
	अगर (likely(ioat_ring_space(ioat_chan) > num_descs)) अणु
		dev_dbg(to_dev(ioat_chan), "%s: num_descs: %d (%x:%x:%x)\n",
			__func__, num_descs, ioat_chan->head,
			ioat_chan->tail, ioat_chan->issued);
		ioat_chan->produce = num_descs;
		वापस 0;  /* with ioat->prep_lock held */
	पूर्ण
	spin_unlock_bh(&ioat_chan->prep_lock);

	dev_dbg_ratelimited(to_dev(ioat_chan),
			    "%s: ring full! num_descs: %d (%x:%x:%x)\n",
			    __func__, num_descs, ioat_chan->head,
			    ioat_chan->tail, ioat_chan->issued);

	/* progress reclaim in the allocation failure हाल we may be
	 * called under bh_disabled so we need to trigger the समयr
	 * event directly
	 */
	अगर (समय_is_beक्रमe_jअगरfies(ioat_chan->समयr.expires)
	    && समयr_pending(&ioat_chan->समयr)) अणु
		mod_समयr(&ioat_chan->समयr, jअगरfies + COMPLETION_TIMEOUT);
		ioat_समयr_event(&ioat_chan->समयr);
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल bool desc_has_ext(काष्ठा ioat_ring_ent *desc)
अणु
	काष्ठा ioat_dma_descriptor *hw = desc->hw;

	अगर (hw->ctl_f.op == IOAT_OP_XOR ||
	    hw->ctl_f.op == IOAT_OP_XOR_VAL) अणु
		काष्ठा ioat_xor_descriptor *xor = desc->xor;

		अगर (src_cnt_to_sw(xor->ctl_f.src_cnt) > 5)
			वापस true;
	पूर्ण अन्यथा अगर (hw->ctl_f.op == IOAT_OP_PQ ||
		   hw->ctl_f.op == IOAT_OP_PQ_VAL) अणु
		काष्ठा ioat_pq_descriptor *pq = desc->pq;

		अगर (src_cnt_to_sw(pq->ctl_f.src_cnt) > 3)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम
ioat_मुक्त_sed(काष्ठा ioatdma_device *ioat_dma, काष्ठा ioat_sed_ent *sed)
अणु
	अगर (!sed)
		वापस;

	dma_pool_मुक्त(ioat_dma->sed_hw_pool[sed->hw_pool], sed->hw, sed->dma);
	kmem_cache_मुक्त(ioat_sed_cache, sed);
पूर्ण

अटल u64 ioat_get_current_completion(काष्ठा ioatdma_chan *ioat_chan)
अणु
	u64 phys_complete;
	u64 completion;

	completion = *ioat_chan->completion;
	phys_complete = ioat_chansts_to_addr(completion);

	dev_dbg(to_dev(ioat_chan), "%s: phys_complete: %#llx\n", __func__,
		(अचिन्हित दीर्घ दीर्घ) phys_complete);

	वापस phys_complete;
पूर्ण

अटल bool ioat_cleanup_preamble(काष्ठा ioatdma_chan *ioat_chan,
				   u64 *phys_complete)
अणु
	*phys_complete = ioat_get_current_completion(ioat_chan);
	अगर (*phys_complete == ioat_chan->last_completion)
		वापस false;

	clear_bit(IOAT_COMPLETION_ACK, &ioat_chan->state);
	mod_समयr(&ioat_chan->समयr, jअगरfies + COMPLETION_TIMEOUT);

	वापस true;
पूर्ण

अटल व्योम
desc_get_errstat(काष्ठा ioatdma_chan *ioat_chan, काष्ठा ioat_ring_ent *desc)
अणु
	काष्ठा ioat_dma_descriptor *hw = desc->hw;

	चयन (hw->ctl_f.op) अणु
	हाल IOAT_OP_PQ_VAL:
	हाल IOAT_OP_PQ_VAL_16S:
	अणु
		काष्ठा ioat_pq_descriptor *pq = desc->pq;

		/* check अगर there's error written */
		अगर (!pq->dwbes_f.wbes)
			वापस;

		/* need to set a chanerr var क्रम checking to clear later */

		अगर (pq->dwbes_f.p_val_err)
			*desc->result |= SUM_CHECK_P_RESULT;

		अगर (pq->dwbes_f.q_val_err)
			*desc->result |= SUM_CHECK_Q_RESULT;

		वापस;
	पूर्ण
	शेष:
		वापस;
	पूर्ण
पूर्ण

/**
 * __cleanup - reclaim used descriptors
 * @ioat_chan: channel (ring) to clean
 * @phys_complete: zeroed (or not) completion address (from status)
 */
अटल व्योम __cleanup(काष्ठा ioatdma_chan *ioat_chan, dma_addr_t phys_complete)
अणु
	काष्ठा ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	काष्ठा ioat_ring_ent *desc;
	bool seen_current = false;
	पूर्णांक idx = ioat_chan->tail, i;
	u16 active;

	dev_dbg(to_dev(ioat_chan), "%s: head: %#x tail: %#x issued: %#x\n",
		__func__, ioat_chan->head, ioat_chan->tail, ioat_chan->issued);

	/*
	 * At restart of the channel, the completion address and the
	 * channel status will be 0 due to starting a new chain. Since
	 * it's new chain and the first descriptor "fails", there is
	 * nothing to clean up. We करो not want to reap the entire submitted
	 * chain due to this 0 address value and then BUG.
	 */
	अगर (!phys_complete)
		वापस;

	active = ioat_ring_active(ioat_chan);
	क्रम (i = 0; i < active && !seen_current; i++) अणु
		काष्ठा dma_async_tx_descriptor *tx;

		prefetch(ioat_get_ring_ent(ioat_chan, idx + i + 1));
		desc = ioat_get_ring_ent(ioat_chan, idx + i);
		dump_desc_dbg(ioat_chan, desc);

		/* set err stat अगर we are using dwbes */
		अगर (ioat_dma->cap & IOAT_CAP_DWBES)
			desc_get_errstat(ioat_chan, desc);

		tx = &desc->txd;
		अगर (tx->cookie) अणु
			dma_cookie_complete(tx);
			dma_descriptor_unmap(tx);
			dmaengine_desc_get_callback_invoke(tx, शून्य);
			tx->callback = शून्य;
			tx->callback_result = शून्य;
		पूर्ण

		अगर (tx->phys == phys_complete)
			seen_current = true;

		/* skip extended descriptors */
		अगर (desc_has_ext(desc)) अणु
			BUG_ON(i + 1 >= active);
			i++;
		पूर्ण

		/* cleanup super extended descriptors */
		अगर (desc->sed) अणु
			ioat_मुक्त_sed(ioat_dma, desc->sed);
			desc->sed = शून्य;
		पूर्ण
	पूर्ण

	/* finish all descriptor पढ़ोs beक्रमe incrementing tail */
	smp_mb();
	ioat_chan->tail = idx + i;
	/* no active descs have written a completion? */
	BUG_ON(active && !seen_current);
	ioat_chan->last_completion = phys_complete;

	अगर (active - i == 0) अणु
		dev_dbg(to_dev(ioat_chan), "%s: cancel completion timeout\n",
			__func__);
		mod_समयr(&ioat_chan->समयr, jअगरfies + IDLE_TIMEOUT);
	पूर्ण

	/* microsecond delay by sysfs variable  per pending descriptor */
	अगर (ioat_chan->पूर्णांकr_coalesce != ioat_chan->prev_पूर्णांकr_coalesce) अणु
		ग_लिखोw(min((ioat_chan->पूर्णांकr_coalesce * (active - i)),
		       IOAT_INTRDELAY_MASK),
		       ioat_chan->ioat_dma->reg_base + IOAT_INTRDELAY_OFFSET);
		ioat_chan->prev_पूर्णांकr_coalesce = ioat_chan->पूर्णांकr_coalesce;
	पूर्ण
पूर्ण

अटल व्योम ioat_cleanup(काष्ठा ioatdma_chan *ioat_chan)
अणु
	u64 phys_complete;

	spin_lock_bh(&ioat_chan->cleanup_lock);

	अगर (ioat_cleanup_preamble(ioat_chan, &phys_complete))
		__cleanup(ioat_chan, phys_complete);

	अगर (is_ioat_halted(*ioat_chan->completion)) अणु
		u32 chanerr = पढ़ोl(ioat_chan->reg_base + IOAT_CHANERR_OFFSET);

		अगर (chanerr &
		    (IOAT_CHANERR_HANDLE_MASK | IOAT_CHANERR_RECOVER_MASK)) अणु
			mod_समयr(&ioat_chan->समयr, jअगरfies + IDLE_TIMEOUT);
			ioat_eh(ioat_chan);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&ioat_chan->cleanup_lock);
पूर्ण

व्योम ioat_cleanup_event(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ioatdma_chan *ioat_chan = from_tasklet(ioat_chan, t, cleanup_task);

	ioat_cleanup(ioat_chan);
	अगर (!test_bit(IOAT_RUN, &ioat_chan->state))
		वापस;
	ग_लिखोw(IOAT_CHANCTRL_RUN, ioat_chan->reg_base + IOAT_CHANCTRL_OFFSET);
पूर्ण

अटल व्योम ioat_restart_channel(काष्ठा ioatdma_chan *ioat_chan)
अणु
	u64 phys_complete;

	/* set the completion address रेजिस्टर again */
	ग_लिखोl(lower_32_bits(ioat_chan->completion_dma),
	       ioat_chan->reg_base + IOAT_CHANCMP_OFFSET_LOW);
	ग_लिखोl(upper_32_bits(ioat_chan->completion_dma),
	       ioat_chan->reg_base + IOAT_CHANCMP_OFFSET_HIGH);

	ioat_quiesce(ioat_chan, 0);
	अगर (ioat_cleanup_preamble(ioat_chan, &phys_complete))
		__cleanup(ioat_chan, phys_complete);

	__ioat_restart_chan(ioat_chan);
पूर्ण


अटल व्योम ioat_पात_descs(काष्ठा ioatdma_chan *ioat_chan)
अणु
	काष्ठा ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	काष्ठा ioat_ring_ent *desc;
	u16 active;
	पूर्णांक idx = ioat_chan->tail, i;

	/*
	 * We assume that the failed descriptor has been processed.
	 * Now we are just वापसing all the reमुख्यing submitted
	 * descriptors to पात.
	 */
	active = ioat_ring_active(ioat_chan);

	/* we skip the failed descriptor that tail poपूर्णांकs to */
	क्रम (i = 1; i < active; i++) अणु
		काष्ठा dma_async_tx_descriptor *tx;

		prefetch(ioat_get_ring_ent(ioat_chan, idx + i + 1));
		desc = ioat_get_ring_ent(ioat_chan, idx + i);

		tx = &desc->txd;
		अगर (tx->cookie) अणु
			काष्ठा dmaengine_result res;

			dma_cookie_complete(tx);
			dma_descriptor_unmap(tx);
			res.result = DMA_TRANS_ABORTED;
			dmaengine_desc_get_callback_invoke(tx, &res);
			tx->callback = शून्य;
			tx->callback_result = शून्य;
		पूर्ण

		/* skip extended descriptors */
		अगर (desc_has_ext(desc)) अणु
			WARN_ON(i + 1 >= active);
			i++;
		पूर्ण

		/* cleanup super extended descriptors */
		अगर (desc->sed) अणु
			ioat_मुक्त_sed(ioat_dma, desc->sed);
			desc->sed = शून्य;
		पूर्ण
	पूर्ण

	smp_mb(); /* finish all descriptor पढ़ोs beक्रमe incrementing tail */
	ioat_chan->tail = idx + active;

	desc = ioat_get_ring_ent(ioat_chan, ioat_chan->tail);
	ioat_chan->last_completion = *ioat_chan->completion = desc->txd.phys;
पूर्ण

अटल व्योम ioat_eh(काष्ठा ioatdma_chan *ioat_chan)
अणु
	काष्ठा pci_dev *pdev = to_pdev(ioat_chan);
	काष्ठा ioat_dma_descriptor *hw;
	काष्ठा dma_async_tx_descriptor *tx;
	u64 phys_complete;
	काष्ठा ioat_ring_ent *desc;
	u32 err_handled = 0;
	u32 chanerr_पूर्णांक;
	u32 chanerr;
	bool पात = false;
	काष्ठा dmaengine_result res;

	/* cleanup so tail poपूर्णांकs to descriptor that caused the error */
	अगर (ioat_cleanup_preamble(ioat_chan, &phys_complete))
		__cleanup(ioat_chan, phys_complete);

	chanerr = पढ़ोl(ioat_chan->reg_base + IOAT_CHANERR_OFFSET);
	pci_पढ़ो_config_dword(pdev, IOAT_PCI_CHANERR_INT_OFFSET, &chanerr_पूर्णांक);

	dev_dbg(to_dev(ioat_chan), "%s: error = %x:%x\n",
		__func__, chanerr, chanerr_पूर्णांक);

	desc = ioat_get_ring_ent(ioat_chan, ioat_chan->tail);
	hw = desc->hw;
	dump_desc_dbg(ioat_chan, desc);

	चयन (hw->ctl_f.op) अणु
	हाल IOAT_OP_XOR_VAL:
		अगर (chanerr & IOAT_CHANERR_XOR_P_OR_CRC_ERR) अणु
			*desc->result |= SUM_CHECK_P_RESULT;
			err_handled |= IOAT_CHANERR_XOR_P_OR_CRC_ERR;
		पूर्ण
		अवरोध;
	हाल IOAT_OP_PQ_VAL:
	हाल IOAT_OP_PQ_VAL_16S:
		अगर (chanerr & IOAT_CHANERR_XOR_P_OR_CRC_ERR) अणु
			*desc->result |= SUM_CHECK_P_RESULT;
			err_handled |= IOAT_CHANERR_XOR_P_OR_CRC_ERR;
		पूर्ण
		अगर (chanerr & IOAT_CHANERR_XOR_Q_ERR) अणु
			*desc->result |= SUM_CHECK_Q_RESULT;
			err_handled |= IOAT_CHANERR_XOR_Q_ERR;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (chanerr & IOAT_CHANERR_RECOVER_MASK) अणु
		अगर (chanerr & IOAT_CHANERR_READ_DATA_ERR) अणु
			res.result = DMA_TRANS_READ_FAILED;
			err_handled |= IOAT_CHANERR_READ_DATA_ERR;
		पूर्ण अन्यथा अगर (chanerr & IOAT_CHANERR_WRITE_DATA_ERR) अणु
			res.result = DMA_TRANS_WRITE_FAILED;
			err_handled |= IOAT_CHANERR_WRITE_DATA_ERR;
		पूर्ण

		पात = true;
	पूर्ण अन्यथा
		res.result = DMA_TRANS_NOERROR;

	/* fault on unhandled error or spurious halt */
	अगर (chanerr ^ err_handled || chanerr == 0) अणु
		dev_err(to_dev(ioat_chan), "%s: fatal error (%x:%x)\n",
			__func__, chanerr, err_handled);
		dev_err(to_dev(ioat_chan), "Errors handled:\n");
		ioat_prपूर्णांक_chanerrs(ioat_chan, err_handled);
		dev_err(to_dev(ioat_chan), "Errors not handled:\n");
		ioat_prपूर्णांक_chanerrs(ioat_chan, (chanerr & ~err_handled));

		BUG();
	पूर्ण

	/* cleanup the faulty descriptor since we are continuing */
	tx = &desc->txd;
	अगर (tx->cookie) अणु
		dma_cookie_complete(tx);
		dma_descriptor_unmap(tx);
		dmaengine_desc_get_callback_invoke(tx, &res);
		tx->callback = शून्य;
		tx->callback_result = शून्य;
	पूर्ण

	/* mark faulting descriptor as complete */
	*ioat_chan->completion = desc->txd.phys;

	spin_lock_bh(&ioat_chan->prep_lock);
	/* we need पात all descriptors */
	अगर (पात) अणु
		ioat_पात_descs(ioat_chan);
		/* clean up the channel, we could be in weird state */
		ioat_reset_hw(ioat_chan);
	पूर्ण

	ग_लिखोl(chanerr, ioat_chan->reg_base + IOAT_CHANERR_OFFSET);
	pci_ग_लिखो_config_dword(pdev, IOAT_PCI_CHANERR_INT_OFFSET, chanerr_पूर्णांक);

	ioat_restart_channel(ioat_chan);
	spin_unlock_bh(&ioat_chan->prep_lock);
पूर्ण

अटल व्योम check_active(काष्ठा ioatdma_chan *ioat_chan)
अणु
	अगर (ioat_ring_active(ioat_chan)) अणु
		mod_समयr(&ioat_chan->समयr, jअगरfies + COMPLETION_TIMEOUT);
		वापस;
	पूर्ण

	अगर (test_and_clear_bit(IOAT_CHAN_ACTIVE, &ioat_chan->state))
		mod_समयr(&ioat_chan->समयr, jअगरfies + IDLE_TIMEOUT);
पूर्ण

अटल व्योम ioat_reboot_chan(काष्ठा ioatdma_chan *ioat_chan)
अणु
	spin_lock_bh(&ioat_chan->prep_lock);
	set_bit(IOAT_CHAN_DOWN, &ioat_chan->state);
	spin_unlock_bh(&ioat_chan->prep_lock);

	ioat_पात_descs(ioat_chan);
	dev_warn(to_dev(ioat_chan), "Reset channel...\n");
	ioat_reset_hw(ioat_chan);
	dev_warn(to_dev(ioat_chan), "Restart channel...\n");
	ioat_restart_channel(ioat_chan);

	spin_lock_bh(&ioat_chan->prep_lock);
	clear_bit(IOAT_CHAN_DOWN, &ioat_chan->state);
	spin_unlock_bh(&ioat_chan->prep_lock);
पूर्ण

व्योम ioat_समयr_event(काष्ठा समयr_list *t)
अणु
	काष्ठा ioatdma_chan *ioat_chan = from_समयr(ioat_chan, t, समयr);
	dma_addr_t phys_complete;
	u64 status;

	status = ioat_chansts(ioat_chan);

	/* when halted due to errors check क्रम channel
	 * programming errors beक्रमe advancing the completion state
	 */
	अगर (is_ioat_halted(status)) अणु
		u32 chanerr;

		chanerr = पढ़ोl(ioat_chan->reg_base + IOAT_CHANERR_OFFSET);
		dev_err(to_dev(ioat_chan), "%s: Channel halted (%x)\n",
			__func__, chanerr);
		dev_err(to_dev(ioat_chan), "Errors:\n");
		ioat_prपूर्णांक_chanerrs(ioat_chan, chanerr);

		अगर (test_bit(IOAT_RUN, &ioat_chan->state)) अणु
			spin_lock_bh(&ioat_chan->cleanup_lock);
			ioat_reboot_chan(ioat_chan);
			spin_unlock_bh(&ioat_chan->cleanup_lock);
		पूर्ण

		वापस;
	पूर्ण

	spin_lock_bh(&ioat_chan->cleanup_lock);

	/* handle the no-actives हाल */
	अगर (!ioat_ring_active(ioat_chan)) अणु
		spin_lock_bh(&ioat_chan->prep_lock);
		check_active(ioat_chan);
		spin_unlock_bh(&ioat_chan->prep_lock);
		जाओ unlock_out;
	पूर्ण

	/* handle the missed cleanup हाल */
	अगर (ioat_cleanup_preamble(ioat_chan, &phys_complete)) अणु
		/* समयr restarted in ioat_cleanup_preamble
		 * and IOAT_COMPLETION_ACK cleared
		 */
		__cleanup(ioat_chan, phys_complete);
		जाओ unlock_out;
	पूर्ण

	/* अगर we haven't made progress and we have alपढ़ोy
	 * acknowledged a pending completion once, then be more
	 * क्रमceful with a restart
	 */
	अगर (test_bit(IOAT_COMPLETION_ACK, &ioat_chan->state)) अणु
		u32 chanerr;

		chanerr = पढ़ोl(ioat_chan->reg_base + IOAT_CHANERR_OFFSET);
		dev_err(to_dev(ioat_chan), "CHANSTS: %#Lx CHANERR: %#x\n",
			status, chanerr);
		dev_err(to_dev(ioat_chan), "Errors:\n");
		ioat_prपूर्णांक_chanerrs(ioat_chan, chanerr);

		dev_dbg(to_dev(ioat_chan), "Active descriptors: %d\n",
			ioat_ring_active(ioat_chan));

		ioat_reboot_chan(ioat_chan);

		जाओ unlock_out;
	पूर्ण

	/* handle missed issue pending हाल */
	अगर (ioat_ring_pending(ioat_chan)) अणु
		dev_warn(to_dev(ioat_chan),
			"Completion timeout with pending descriptors\n");
		spin_lock_bh(&ioat_chan->prep_lock);
		__ioat_issue_pending(ioat_chan);
		spin_unlock_bh(&ioat_chan->prep_lock);
	पूर्ण

	set_bit(IOAT_COMPLETION_ACK, &ioat_chan->state);
	mod_समयr(&ioat_chan->समयr, jअगरfies + COMPLETION_TIMEOUT);
unlock_out:
	spin_unlock_bh(&ioat_chan->cleanup_lock);
पूर्ण

क्रमागत dma_status
ioat_tx_status(काष्ठा dma_chan *c, dma_cookie_t cookie,
		काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);
	क्रमागत dma_status ret;

	ret = dma_cookie_status(c, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	ioat_cleanup(ioat_chan);

	वापस dma_cookie_status(c, cookie, txstate);
पूर्ण

पूर्णांक ioat_reset_hw(काष्ठा ioatdma_chan *ioat_chan)
अणु
	/* throw away whatever the channel was करोing and get it
	 * initialized, with ioat3 specअगरic workarounds
	 */
	काष्ठा ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	काष्ठा pci_dev *pdev = ioat_dma->pdev;
	u32 chanerr;
	u16 dev_id;
	पूर्णांक err;

	ioat_quiesce(ioat_chan, msecs_to_jअगरfies(100));

	chanerr = पढ़ोl(ioat_chan->reg_base + IOAT_CHANERR_OFFSET);
	ग_लिखोl(chanerr, ioat_chan->reg_base + IOAT_CHANERR_OFFSET);

	अगर (ioat_dma->version < IOAT_VER_3_3) अणु
		/* clear any pending errors */
		err = pci_पढ़ो_config_dword(pdev,
				IOAT_PCI_CHANERR_INT_OFFSET, &chanerr);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"channel error register unreachable\n");
			वापस err;
		पूर्ण
		pci_ग_लिखो_config_dword(pdev,
				IOAT_PCI_CHANERR_INT_OFFSET, chanerr);

		/* Clear DMAUNCERRSTS Cfg-Reg Parity Error status bit
		 * (workaround क्रम spurious config parity error after restart)
		 */
		pci_पढ़ो_config_word(pdev, IOAT_PCI_DEVICE_ID_OFFSET, &dev_id);
		अगर (dev_id == PCI_DEVICE_ID_INTEL_IOAT_TBG0) अणु
			pci_ग_लिखो_config_dword(pdev,
					       IOAT_PCI_DMAUNCERRSTS_OFFSET,
					       0x10);
		पूर्ण
	पूर्ण

	अगर (is_bwd_ioat(pdev) && (ioat_dma->irq_mode == IOAT_MSIX)) अणु
		ioat_dma->msixtba0 = पढ़ोq(ioat_dma->reg_base + 0x1000);
		ioat_dma->msixdata0 = पढ़ोq(ioat_dma->reg_base + 0x1008);
		ioat_dma->msixpba = पढ़ोq(ioat_dma->reg_base + 0x1800);
	पूर्ण


	err = ioat_reset_sync(ioat_chan, msecs_to_jअगरfies(200));
	अगर (!err) अणु
		अगर (is_bwd_ioat(pdev) && (ioat_dma->irq_mode == IOAT_MSIX)) अणु
			ग_लिखोq(ioat_dma->msixtba0, ioat_dma->reg_base + 0x1000);
			ग_लिखोq(ioat_dma->msixdata0, ioat_dma->reg_base + 0x1008);
			ग_लिखोq(ioat_dma->msixpba, ioat_dma->reg_base + 0x1800);
		पूर्ण
	पूर्ण

	अगर (err)
		dev_err(&pdev->dev, "Failed to reset: %d\n", err);

	वापस err;
पूर्ण
