<शैली गुरु>
/*
 * drivers/dma/fsl_raid.c
 *
 * Freescale RAID Engine device driver
 *
 * Author:
 *	Harninder Rai <harninder.rai@मुक्तscale.com>
 *	Naveen Burmi <naveenburmi@मुक्तscale.com>
 *
 * Reग_लिखो:
 *	Xuelin Shi <xuelin.shi@मुक्तscale.com>
 *
 * Copyright (c) 2010-2014 Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Theory of operation:
 *
 * General capabilities:
 *	RAID Engine (RE) block is capable of offloading XOR, स_नकल and P/Q
 *	calculations required in RAID5 and RAID6 operations. RE driver
 *	रेजिस्टरs with Linux's ASYNC layer as dma driver. RE hardware
 *	मुख्यtains strict ordering of the requests through chained
 *	command queueing.
 *
 * Data flow:
 *	Software RAID layer of Linux (MD layer) मुख्यtains RAID partitions,
 *	strips, stripes etc. It sends requests to the underlying ASYNC layer
 *	which further passes it to RE driver. ASYNC layer decides which request
 *	goes to which job ring of RE hardware. For every request processed by
 *	RAID Engine, driver माला_लो an पूर्णांकerrupt unless coalescing is set. The
 *	per job ring पूर्णांकerrupt handler checks the status रेजिस्टर क्रम errors,
 *	clears the पूर्णांकerrupt and leave the post पूर्णांकerrupt processing to the irq
 *	thपढ़ो.
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>

#समावेश "dmaengine.h"
#समावेश "fsl_raid.h"

#घोषणा FSL_RE_MAX_XOR_SRCS	16
#घोषणा FSL_RE_MAX_PQ_SRCS	16
#घोषणा FSL_RE_MIN_DESCS	256
#घोषणा FSL_RE_MAX_DESCS	(4 * FSL_RE_MIN_DESCS)
#घोषणा FSL_RE_FRAME_FORMAT	0x1
#घोषणा FSL_RE_MAX_DATA_LEN	(1024*1024)

#घोषणा to_fsl_re_dma_desc(tx) container_of(tx, काष्ठा fsl_re_desc, async_tx)

/* Add descriptors पूर्णांकo per chan software queue - submit_q */
अटल dma_cookie_t fsl_re_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा fsl_re_desc *desc;
	काष्ठा fsl_re_chan *re_chan;
	dma_cookie_t cookie;
	अचिन्हित दीर्घ flags;

	desc = to_fsl_re_dma_desc(tx);
	re_chan = container_of(tx->chan, काष्ठा fsl_re_chan, chan);

	spin_lock_irqsave(&re_chan->desc_lock, flags);
	cookie = dma_cookie_assign(tx);
	list_add_tail(&desc->node, &re_chan->submit_q);
	spin_unlock_irqrestore(&re_chan->desc_lock, flags);

	वापस cookie;
पूर्ण

/* Copy descriptor from per chan software queue पूर्णांकo hardware job ring */
अटल व्योम fsl_re_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा fsl_re_chan *re_chan;
	पूर्णांक avail;
	काष्ठा fsl_re_desc *desc, *_desc;
	अचिन्हित दीर्घ flags;

	re_chan = container_of(chan, काष्ठा fsl_re_chan, chan);

	spin_lock_irqsave(&re_chan->desc_lock, flags);
	avail = FSL_RE_SLOT_AVAIL(
		in_be32(&re_chan->jrregs->inbring_slot_avail));

	list_क्रम_each_entry_safe(desc, _desc, &re_chan->submit_q, node) अणु
		अगर (!avail)
			अवरोध;

		list_move_tail(&desc->node, &re_chan->active_q);

		स_नकल(&re_chan->inb_ring_virt_addr[re_chan->inb_count],
		       &desc->hwdesc, माप(काष्ठा fsl_re_hw_desc));

		re_chan->inb_count = (re_chan->inb_count + 1) &
						FSL_RE_RING_SIZE_MASK;
		out_be32(&re_chan->jrregs->inbring_add_job, FSL_RE_ADD_JOB(1));
		avail--;
	पूर्ण
	spin_unlock_irqrestore(&re_chan->desc_lock, flags);
पूर्ण

अटल व्योम fsl_re_desc_करोne(काष्ठा fsl_re_desc *desc)
अणु
	dma_cookie_complete(&desc->async_tx);
	dma_descriptor_unmap(&desc->async_tx);
	dmaengine_desc_get_callback_invoke(&desc->async_tx, शून्य);
पूर्ण

अटल व्योम fsl_re_cleanup_descs(काष्ठा fsl_re_chan *re_chan)
अणु
	काष्ठा fsl_re_desc *desc, *_desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&re_chan->desc_lock, flags);
	list_क्रम_each_entry_safe(desc, _desc, &re_chan->ack_q, node) अणु
		अगर (async_tx_test_ack(&desc->async_tx))
			list_move_tail(&desc->node, &re_chan->मुक्त_q);
	पूर्ण
	spin_unlock_irqrestore(&re_chan->desc_lock, flags);

	fsl_re_issue_pending(&re_chan->chan);
पूर्ण

अटल व्योम fsl_re_dequeue(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा fsl_re_chan *re_chan = from_tasklet(re_chan, t, irqtask);
	काष्ठा fsl_re_desc *desc, *_desc;
	काष्ठा fsl_re_hw_desc *hwdesc;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक count, oub_count;
	पूर्णांक found;

	fsl_re_cleanup_descs(re_chan);

	spin_lock_irqsave(&re_chan->desc_lock, flags);
	count =	FSL_RE_SLOT_FULL(in_be32(&re_chan->jrregs->oubring_slot_full));
	जबतक (count--) अणु
		found = 0;
		hwdesc = &re_chan->oub_ring_virt_addr[re_chan->oub_count];
		list_क्रम_each_entry_safe(desc, _desc, &re_chan->active_q,
					 node) अणु
			/* compare the hw dma addr to find the completed */
			अगर (desc->hwdesc.lbea32 == hwdesc->lbea32 &&
			    desc->hwdesc.addr_low == hwdesc->addr_low) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (found) अणु
			fsl_re_desc_करोne(desc);
			list_move_tail(&desc->node, &re_chan->ack_q);
		पूर्ण अन्यथा अणु
			dev_err(re_chan->dev,
				"found hwdesc not in sw queue, discard it\n");
		पूर्ण

		oub_count = (re_chan->oub_count + 1) & FSL_RE_RING_SIZE_MASK;
		re_chan->oub_count = oub_count;

		out_be32(&re_chan->jrregs->oubring_job_rmvd,
			 FSL_RE_RMVD_JOB(1));
	पूर्ण
	spin_unlock_irqrestore(&re_chan->desc_lock, flags);
पूर्ण

/* Per Job Ring पूर्णांकerrupt handler */
अटल irqवापस_t fsl_re_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fsl_re_chan *re_chan;
	u32 irqstate, status;

	re_chan = dev_get_drvdata((काष्ठा device *)data);

	irqstate = in_be32(&re_chan->jrregs->jr_पूर्णांकerrupt_status);
	अगर (!irqstate)
		वापस IRQ_NONE;

	/*
	 * There's no way in upper layer (पढ़ो MD layer) to recover from
	 * error conditions except restart everything. In दीर्घ term we
	 * need to करो something more than just crashing
	 */
	अगर (irqstate & FSL_RE_ERROR) अणु
		status = in_be32(&re_chan->jrregs->jr_status);
		dev_err(re_chan->dev, "chan error irqstate: %x, status: %x\n",
			irqstate, status);
	पूर्ण

	/* Clear पूर्णांकerrupt */
	out_be32(&re_chan->jrregs->jr_पूर्णांकerrupt_status, FSL_RE_CLR_INTR);

	tasklet_schedule(&re_chan->irqtask);

	वापस IRQ_HANDLED;
पूर्ण

अटल क्रमागत dma_status fsl_re_tx_status(काष्ठा dma_chan *chan,
					dma_cookie_t cookie,
					काष्ठा dma_tx_state *txstate)
अणु
	वापस dma_cookie_status(chan, cookie, txstate);
पूर्ण

अटल व्योम fill_cfd_frame(काष्ठा fsl_re_cmpnd_frame *cf, u8 index,
			   माप_प्रकार length, dma_addr_t addr, bool final)
अणु
	u32 efrl = length & FSL_RE_CF_LENGTH_MASK;

	efrl |= final << FSL_RE_CF_FINAL_SHIFT;
	cf[index].efrl32 = efrl;
	cf[index].addr_high = upper_32_bits(addr);
	cf[index].addr_low = lower_32_bits(addr);
पूर्ण

अटल काष्ठा fsl_re_desc *fsl_re_init_desc(काष्ठा fsl_re_chan *re_chan,
					    काष्ठा fsl_re_desc *desc,
					    व्योम *cf, dma_addr_t paddr)
अणु
	desc->re_chan = re_chan;
	desc->async_tx.tx_submit = fsl_re_tx_submit;
	dma_async_tx_descriptor_init(&desc->async_tx, &re_chan->chan);
	INIT_LIST_HEAD(&desc->node);

	desc->hwdesc.fmt32 = FSL_RE_FRAME_FORMAT << FSL_RE_HWDESC_FMT_SHIFT;
	desc->hwdesc.lbea32 = upper_32_bits(paddr);
	desc->hwdesc.addr_low = lower_32_bits(paddr);
	desc->cf_addr = cf;
	desc->cf_paddr = paddr;

	desc->cdb_addr = (व्योम *)(cf + FSL_RE_CF_DESC_SIZE);
	desc->cdb_paddr = paddr + FSL_RE_CF_DESC_SIZE;

	वापस desc;
पूर्ण

अटल काष्ठा fsl_re_desc *fsl_re_chan_alloc_desc(काष्ठा fsl_re_chan *re_chan,
						  अचिन्हित दीर्घ flags)
अणु
	काष्ठा fsl_re_desc *desc = शून्य;
	व्योम *cf;
	dma_addr_t paddr;
	अचिन्हित दीर्घ lock_flag;

	fsl_re_cleanup_descs(re_chan);

	spin_lock_irqsave(&re_chan->desc_lock, lock_flag);
	अगर (!list_empty(&re_chan->मुक्त_q)) अणु
		/* take one desc from मुक्त_q */
		desc = list_first_entry(&re_chan->मुक्त_q,
					काष्ठा fsl_re_desc, node);
		list_del(&desc->node);

		desc->async_tx.flags = flags;
	पूर्ण
	spin_unlock_irqrestore(&re_chan->desc_lock, lock_flag);

	अगर (!desc) अणु
		desc = kzalloc(माप(*desc), GFP_NOWAIT);
		अगर (!desc)
			वापस शून्य;

		cf = dma_pool_alloc(re_chan->re_dev->cf_desc_pool, GFP_NOWAIT,
				    &paddr);
		अगर (!cf) अणु
			kमुक्त(desc);
			वापस शून्य;
		पूर्ण

		desc = fsl_re_init_desc(re_chan, desc, cf, paddr);
		desc->async_tx.flags = flags;

		spin_lock_irqsave(&re_chan->desc_lock, lock_flag);
		re_chan->alloc_count++;
		spin_unlock_irqrestore(&re_chan->desc_lock, lock_flag);
	पूर्ण

	वापस desc;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *fsl_re_prep_dma_genq(
		काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t *src,
		अचिन्हित पूर्णांक src_cnt, स्थिर अचिन्हित अक्षर *scf, माप_प्रकार len,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा fsl_re_chan *re_chan;
	काष्ठा fsl_re_desc *desc;
	काष्ठा fsl_re_xor_cdb *xor;
	काष्ठा fsl_re_cmpnd_frame *cf;
	u32 cdb;
	अचिन्हित पूर्णांक i, j;
	अचिन्हित पूर्णांक save_src_cnt = src_cnt;
	पूर्णांक cont_q = 0;

	re_chan = container_of(chan, काष्ठा fsl_re_chan, chan);
	अगर (len > FSL_RE_MAX_DATA_LEN) अणु
		dev_err(re_chan->dev, "genq tx length %zu, max length %d\n",
			len, FSL_RE_MAX_DATA_LEN);
		वापस शून्य;
	पूर्ण

	desc = fsl_re_chan_alloc_desc(re_chan, flags);
	अगर (desc <= 0)
		वापस शून्य;

	अगर (scf && (flags & DMA_PREP_CONTINUE)) अणु
		cont_q = 1;
		src_cnt += 1;
	पूर्ण

	/* Filling xor CDB */
	cdb = FSL_RE_XOR_OPCODE << FSL_RE_CDB_OPCODE_SHIFT;
	cdb |= (src_cnt - 1) << FSL_RE_CDB_NRCS_SHIFT;
	cdb |= FSL_RE_BLOCK_SIZE << FSL_RE_CDB_BLKSIZE_SHIFT;
	cdb |= FSL_RE_INTR_ON_ERROR << FSL_RE_CDB_ERROR_SHIFT;
	cdb |= FSL_RE_DATA_DEP << FSL_RE_CDB_DEPEND_SHIFT;
	xor = desc->cdb_addr;
	xor->cdb32 = cdb;

	अगर (scf) अणु
		/* compute q = src0*coef0^src1*coef1^..., * is GF(8) mult */
		क्रम (i = 0; i < save_src_cnt; i++)
			xor->gfm[i] = scf[i];
		अगर (cont_q)
			xor->gfm[i++] = 1;
	पूर्ण अन्यथा अणु
		/* compute P, that is XOR all srcs */
		क्रम (i = 0; i < src_cnt; i++)
			xor->gfm[i] = 1;
	पूर्ण

	/* Filling frame 0 of compound frame descriptor with CDB */
	cf = desc->cf_addr;
	fill_cfd_frame(cf, 0, माप(*xor), desc->cdb_paddr, 0);

	/* Fill CFD's 1st frame with dest buffer */
	fill_cfd_frame(cf, 1, len, dest, 0);

	/* Fill CFD's rest of the frames with source buffers */
	क्रम (i = 2, j = 0; j < save_src_cnt; i++, j++)
		fill_cfd_frame(cf, i, len, src[j], 0);

	अगर (cont_q)
		fill_cfd_frame(cf, i++, len, dest, 0);

	/* Setting the final bit in the last source buffer frame in CFD */
	cf[i - 1].efrl32 |= 1 << FSL_RE_CF_FINAL_SHIFT;

	वापस &desc->async_tx;
पूर्ण

/*
 * Prep function क्रम P parity calculation.In RAID Engine terminology,
 * XOR calculation is called GenQ calculation करोne through GenQ command
 */
अटल काष्ठा dma_async_tx_descriptor *fsl_re_prep_dma_xor(
		काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t *src,
		अचिन्हित पूर्णांक src_cnt, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	/* शून्य let genq take all coef as 1 */
	वापस fsl_re_prep_dma_genq(chan, dest, src, src_cnt, शून्य, len, flags);
पूर्ण

/*
 * Prep function क्रम P/Q parity calculation.In RAID Engine terminology,
 * P/Q calculation is called GenQQ करोne through GenQQ command
 */
अटल काष्ठा dma_async_tx_descriptor *fsl_re_prep_dma_pq(
		काष्ठा dma_chan *chan, dma_addr_t *dest, dma_addr_t *src,
		अचिन्हित पूर्णांक src_cnt, स्थिर अचिन्हित अक्षर *scf, माप_प्रकार len,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा fsl_re_chan *re_chan;
	काष्ठा fsl_re_desc *desc;
	काष्ठा fsl_re_pq_cdb *pq;
	काष्ठा fsl_re_cmpnd_frame *cf;
	u32 cdb;
	u8 *p;
	पूर्णांक gfmq_len, i, j;
	अचिन्हित पूर्णांक save_src_cnt = src_cnt;

	re_chan = container_of(chan, काष्ठा fsl_re_chan, chan);
	अगर (len > FSL_RE_MAX_DATA_LEN) अणु
		dev_err(re_chan->dev, "pq tx length is %zu, max length is %d\n",
			len, FSL_RE_MAX_DATA_LEN);
		वापस शून्य;
	पूर्ण

	/*
	 * RE requires at least 2 sources, अगर given only one source, we pass the
	 * second source same as the first one.
	 * With only one source, generating P is meaningless, only generate Q.
	 */
	अगर (src_cnt == 1) अणु
		काष्ठा dma_async_tx_descriptor *tx;
		dma_addr_t dma_src[2];
		अचिन्हित अक्षर coef[2];

		dma_src[0] = *src;
		coef[0] = *scf;
		dma_src[1] = *src;
		coef[1] = 0;
		tx = fsl_re_prep_dma_genq(chan, dest[1], dma_src, 2, coef, len,
					  flags);
		अगर (tx)
			desc = to_fsl_re_dma_desc(tx);

		वापस tx;
	पूर्ण

	/*
	 * During RAID6 array creation, Linux's MD layer माला_लो P and Q
	 * calculated separately in two steps. But our RAID Engine has
	 * the capability to calculate both P and Q with a single command
	 * Hence to merge well with MD layer, we need to provide a hook
	 * here and call re_jq_prep_dma_genq() function
	 */

	अगर (flags & DMA_PREP_PQ_DISABLE_P)
		वापस fsl_re_prep_dma_genq(chan, dest[1], src, src_cnt,
				scf, len, flags);

	अगर (flags & DMA_PREP_CONTINUE)
		src_cnt += 3;

	desc = fsl_re_chan_alloc_desc(re_chan, flags);
	अगर (desc <= 0)
		वापस शून्य;

	/* Filling GenQQ CDB */
	cdb = FSL_RE_PQ_OPCODE << FSL_RE_CDB_OPCODE_SHIFT;
	cdb |= (src_cnt - 1) << FSL_RE_CDB_NRCS_SHIFT;
	cdb |= FSL_RE_BLOCK_SIZE << FSL_RE_CDB_BLKSIZE_SHIFT;
	cdb |= FSL_RE_BUFFER_OUTPUT << FSL_RE_CDB_BUFFER_SHIFT;
	cdb |= FSL_RE_DATA_DEP << FSL_RE_CDB_DEPEND_SHIFT;

	pq = desc->cdb_addr;
	pq->cdb32 = cdb;

	p = pq->gfm_q1;
	/* Init gfm_q1[] */
	क्रम (i = 0; i < src_cnt; i++)
		p[i] = 1;

	/* Align gfm[] to 32bit */
	gfmq_len = ALIGN(src_cnt, 4);

	/* Init gfm_q2[] */
	p += gfmq_len;
	क्रम (i = 0; i < src_cnt; i++)
		p[i] = scf[i];

	/* Filling frame 0 of compound frame descriptor with CDB */
	cf = desc->cf_addr;
	fill_cfd_frame(cf, 0, माप(काष्ठा fsl_re_pq_cdb), desc->cdb_paddr, 0);

	/* Fill CFD's 1st & 2nd frame with dest buffers */
	क्रम (i = 1, j = 0; i < 3; i++, j++)
		fill_cfd_frame(cf, i, len, dest[j], 0);

	/* Fill CFD's rest of the frames with source buffers */
	क्रम (i = 3, j = 0; j < save_src_cnt; i++, j++)
		fill_cfd_frame(cf, i, len, src[j], 0);

	/* PQ computation continuation */
	अगर (flags & DMA_PREP_CONTINUE) अणु
		अगर (src_cnt - save_src_cnt == 3) अणु
			p[save_src_cnt] = 0;
			p[save_src_cnt + 1] = 0;
			p[save_src_cnt + 2] = 1;
			fill_cfd_frame(cf, i++, len, dest[0], 0);
			fill_cfd_frame(cf, i++, len, dest[1], 0);
			fill_cfd_frame(cf, i++, len, dest[1], 0);
		पूर्ण अन्यथा अणु
			dev_err(re_chan->dev, "PQ tx continuation error!\n");
			वापस शून्य;
		पूर्ण
	पूर्ण

	/* Setting the final bit in the last source buffer frame in CFD */
	cf[i - 1].efrl32 |= 1 << FSL_RE_CF_FINAL_SHIFT;

	वापस &desc->async_tx;
पूर्ण

/*
 * Prep function क्रम स_नकल. In RAID Engine, स_नकल is करोne through MOVE
 * command. Logic of this function will need to be modअगरied once multipage
 * support is added in Linux's MD/ASYNC Layer
 */
अटल काष्ठा dma_async_tx_descriptor *fsl_re_prep_dma_स_नकल(
		काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
		माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा fsl_re_chan *re_chan;
	काष्ठा fsl_re_desc *desc;
	माप_प्रकार length;
	काष्ठा fsl_re_cmpnd_frame *cf;
	काष्ठा fsl_re_move_cdb *move;
	u32 cdb;

	re_chan = container_of(chan, काष्ठा fsl_re_chan, chan);

	अगर (len > FSL_RE_MAX_DATA_LEN) अणु
		dev_err(re_chan->dev, "cp tx length is %zu, max length is %d\n",
			len, FSL_RE_MAX_DATA_LEN);
		वापस शून्य;
	पूर्ण

	desc = fsl_re_chan_alloc_desc(re_chan, flags);
	अगर (desc <= 0)
		वापस शून्य;

	/* Filling move CDB */
	cdb = FSL_RE_MOVE_OPCODE << FSL_RE_CDB_OPCODE_SHIFT;
	cdb |= FSL_RE_BLOCK_SIZE << FSL_RE_CDB_BLKSIZE_SHIFT;
	cdb |= FSL_RE_INTR_ON_ERROR << FSL_RE_CDB_ERROR_SHIFT;
	cdb |= FSL_RE_DATA_DEP << FSL_RE_CDB_DEPEND_SHIFT;

	move = desc->cdb_addr;
	move->cdb32 = cdb;

	/* Filling frame 0 of CFD with move CDB */
	cf = desc->cf_addr;
	fill_cfd_frame(cf, 0, माप(*move), desc->cdb_paddr, 0);

	length = min_t(माप_प्रकार, len, FSL_RE_MAX_DATA_LEN);

	/* Fill CFD's 1st frame with dest buffer */
	fill_cfd_frame(cf, 1, length, dest, 0);

	/* Fill CFD's 2nd frame with src buffer */
	fill_cfd_frame(cf, 2, length, src, 1);

	वापस &desc->async_tx;
पूर्ण

अटल पूर्णांक fsl_re_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा fsl_re_chan *re_chan;
	काष्ठा fsl_re_desc *desc;
	व्योम *cf;
	dma_addr_t paddr;
	पूर्णांक i;

	re_chan = container_of(chan, काष्ठा fsl_re_chan, chan);
	क्रम (i = 0; i < FSL_RE_MIN_DESCS; i++) अणु
		desc = kzalloc(माप(*desc), GFP_KERNEL);
		अगर (!desc)
			अवरोध;

		cf = dma_pool_alloc(re_chan->re_dev->cf_desc_pool, GFP_KERNEL,
				    &paddr);
		अगर (!cf) अणु
			kमुक्त(desc);
			अवरोध;
		पूर्ण

		INIT_LIST_HEAD(&desc->node);
		fsl_re_init_desc(re_chan, desc, cf, paddr);

		list_add_tail(&desc->node, &re_chan->मुक्त_q);
		re_chan->alloc_count++;
	पूर्ण
	वापस re_chan->alloc_count;
पूर्ण

अटल व्योम fsl_re_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा fsl_re_chan *re_chan;
	काष्ठा fsl_re_desc *desc;

	re_chan = container_of(chan, काष्ठा fsl_re_chan, chan);
	जबतक (re_chan->alloc_count--) अणु
		desc = list_first_entry(&re_chan->मुक्त_q,
					काष्ठा fsl_re_desc,
					node);

		list_del(&desc->node);
		dma_pool_मुक्त(re_chan->re_dev->cf_desc_pool, desc->cf_addr,
			      desc->cf_paddr);
		kमुक्त(desc);
	पूर्ण

	अगर (!list_empty(&re_chan->मुक्त_q))
		dev_err(re_chan->dev, "chan resource cannot be cleaned!\n");
पूर्ण

अटल पूर्णांक fsl_re_chan_probe(काष्ठा platक्रमm_device *ofdev,
		      काष्ठा device_node *np, u8 q, u32 off)
अणु
	काष्ठा device *dev, *chandev;
	काष्ठा fsl_re_drv_निजी *re_priv;
	काष्ठा fsl_re_chan *chan;
	काष्ठा dma_device *dma_dev;
	u32 ptr;
	u32 status;
	पूर्णांक ret = 0, rc;
	काष्ठा platक्रमm_device *chan_ofdev;

	dev = &ofdev->dev;
	re_priv = dev_get_drvdata(dev);
	dma_dev = &re_priv->dma_dev;

	chan = devm_kzalloc(dev, माप(*chan), GFP_KERNEL);
	अगर (!chan)
		वापस -ENOMEM;

	/* create platक्रमm device क्रम chan node */
	chan_ofdev = of_platक्रमm_device_create(np, शून्य, dev);
	अगर (!chan_ofdev) अणु
		dev_err(dev, "Not able to create ofdev for jr %d\n", q);
		ret = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	/* पढ़ो reg property from dts */
	rc = of_property_पढ़ो_u32(np, "reg", &ptr);
	अगर (rc) अणु
		dev_err(dev, "Reg property not found in jr %d\n", q);
		ret = -ENODEV;
		जाओ err_मुक्त;
	पूर्ण

	chan->jrregs = (काष्ठा fsl_re_chan_cfg *)((u8 *)re_priv->re_regs +
			off + ptr);

	/* पढ़ो irq property from dts */
	chan->irq = irq_of_parse_and_map(np, 0);
	अगर (!chan->irq) अणु
		dev_err(dev, "No IRQ defined for JR %d\n", q);
		ret = -ENODEV;
		जाओ err_मुक्त;
	पूर्ण

	snम_लिखो(chan->name, माप(chan->name), "re_jr%02d", q);

	chandev = &chan_ofdev->dev;
	tasklet_setup(&chan->irqtask, fsl_re_dequeue);

	ret = request_irq(chan->irq, fsl_re_isr, 0, chan->name, chandev);
	अगर (ret) अणु
		dev_err(dev, "Unable to register interrupt for JR %d\n", q);
		ret = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	re_priv->re_jrs[q] = chan;
	chan->chan.device = dma_dev;
	chan->chan.निजी = chan;
	chan->dev = chandev;
	chan->re_dev = re_priv;

	spin_lock_init(&chan->desc_lock);
	INIT_LIST_HEAD(&chan->ack_q);
	INIT_LIST_HEAD(&chan->active_q);
	INIT_LIST_HEAD(&chan->submit_q);
	INIT_LIST_HEAD(&chan->मुक्त_q);

	chan->inb_ring_virt_addr = dma_pool_alloc(chan->re_dev->hw_desc_pool,
		GFP_KERNEL, &chan->inb_phys_addr);
	अगर (!chan->inb_ring_virt_addr) अणु
		dev_err(dev, "No dma memory for inb_ring_virt_addr\n");
		ret = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	chan->oub_ring_virt_addr = dma_pool_alloc(chan->re_dev->hw_desc_pool,
		GFP_KERNEL, &chan->oub_phys_addr);
	अगर (!chan->oub_ring_virt_addr) अणु
		dev_err(dev, "No dma memory for oub_ring_virt_addr\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_1;
	पूर्ण

	/* Program the Inbound/Outbound ring base addresses and size */
	out_be32(&chan->jrregs->inbring_base_h,
		 chan->inb_phys_addr & FSL_RE_ADDR_BIT_MASK);
	out_be32(&chan->jrregs->oubring_base_h,
		 chan->oub_phys_addr & FSL_RE_ADDR_BIT_MASK);
	out_be32(&chan->jrregs->inbring_base_l,
		 chan->inb_phys_addr >> FSL_RE_ADDR_BIT_SHIFT);
	out_be32(&chan->jrregs->oubring_base_l,
		 chan->oub_phys_addr >> FSL_RE_ADDR_BIT_SHIFT);
	out_be32(&chan->jrregs->inbring_size,
		 FSL_RE_RING_SIZE << FSL_RE_RING_SIZE_SHIFT);
	out_be32(&chan->jrregs->oubring_size,
		 FSL_RE_RING_SIZE << FSL_RE_RING_SIZE_SHIFT);

	/* Read LIODN value from u-boot */
	status = in_be32(&chan->jrregs->jr_config_1) & FSL_RE_REG_LIODN_MASK;

	/* Program the CFG reg */
	out_be32(&chan->jrregs->jr_config_1,
		 FSL_RE_CFG1_CBSI | FSL_RE_CFG1_CBS0 | status);

	dev_set_drvdata(chandev, chan);

	/* Enable RE/CHAN */
	out_be32(&chan->jrregs->jr_command, FSL_RE_ENABLE);

	वापस 0;

err_मुक्त_1:
	dma_pool_मुक्त(chan->re_dev->hw_desc_pool, chan->inb_ring_virt_addr,
		      chan->inb_phys_addr);
err_मुक्त:
	वापस ret;
पूर्ण

/* Probe function क्रम RAID Engine */
अटल पूर्णांक fsl_re_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा fsl_re_drv_निजी *re_priv;
	काष्ठा device_node *np;
	काष्ठा device_node *child;
	u32 off;
	u8 ridx = 0;
	काष्ठा dma_device *dma_dev;
	काष्ठा resource *res;
	पूर्णांक rc;
	काष्ठा device *dev = &ofdev->dev;

	re_priv = devm_kzalloc(dev, माप(*re_priv), GFP_KERNEL);
	अगर (!re_priv)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(ofdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	/* IOMAP the entire RAID Engine region */
	re_priv->re_regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!re_priv->re_regs)
		वापस -EBUSY;

	/* Program the RE mode */
	out_be32(&re_priv->re_regs->global_config, FSL_RE_NON_DPAA_MODE);

	/* Program Galois Field polynomial */
	out_be32(&re_priv->re_regs->galois_field_config, FSL_RE_GFM_POLY);

	dev_info(dev, "version %x, mode %x, gfp %x\n",
		 in_be32(&re_priv->re_regs->re_version_id),
		 in_be32(&re_priv->re_regs->global_config),
		 in_be32(&re_priv->re_regs->galois_field_config));

	dma_dev = &re_priv->dma_dev;
	dma_dev->dev = dev;
	INIT_LIST_HEAD(&dma_dev->channels);
	dma_set_mask(dev, DMA_BIT_MASK(40));

	dma_dev->device_alloc_chan_resources = fsl_re_alloc_chan_resources;
	dma_dev->device_tx_status = fsl_re_tx_status;
	dma_dev->device_issue_pending = fsl_re_issue_pending;

	dma_dev->max_xor = FSL_RE_MAX_XOR_SRCS;
	dma_dev->device_prep_dma_xor = fsl_re_prep_dma_xor;
	dma_cap_set(DMA_XOR, dma_dev->cap_mask);

	dma_dev->max_pq = FSL_RE_MAX_PQ_SRCS;
	dma_dev->device_prep_dma_pq = fsl_re_prep_dma_pq;
	dma_cap_set(DMA_PQ, dma_dev->cap_mask);

	dma_dev->device_prep_dma_स_नकल = fsl_re_prep_dma_स_नकल;
	dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);

	dma_dev->device_मुक्त_chan_resources = fsl_re_मुक्त_chan_resources;

	re_priv->total_chans = 0;

	re_priv->cf_desc_pool = dmam_pool_create("fsl_re_cf_desc_pool", dev,
					FSL_RE_CF_CDB_SIZE,
					FSL_RE_CF_CDB_ALIGN, 0);

	अगर (!re_priv->cf_desc_pool) अणु
		dev_err(dev, "No memory for fsl re_cf desc pool\n");
		वापस -ENOMEM;
	पूर्ण

	re_priv->hw_desc_pool = dmam_pool_create("fsl_re_hw_desc_pool", dev,
			माप(काष्ठा fsl_re_hw_desc) * FSL_RE_RING_SIZE,
			FSL_RE_FRAME_ALIGN, 0);
	अगर (!re_priv->hw_desc_pool) अणु
		dev_err(dev, "No memory for fsl re_hw desc pool\n");
		वापस -ENOMEM;
	पूर्ण

	dev_set_drvdata(dev, re_priv);

	/* Parse Device tree to find out the total number of JQs present */
	क्रम_each_compatible_node(np, शून्य, "fsl,raideng-v1.0-job-queue") अणु
		rc = of_property_पढ़ो_u32(np, "reg", &off);
		अगर (rc) अणु
			dev_err(dev, "Reg property not found in JQ node\n");
			of_node_put(np);
			वापस -ENODEV;
		पूर्ण
		/* Find out the Job Rings present under each JQ */
		क्रम_each_child_of_node(np, child) अणु
			rc = of_device_is_compatible(child,
					     "fsl,raideng-v1.0-job-ring");
			अगर (rc) अणु
				fsl_re_chan_probe(ofdev, child, ridx++, off);
				re_priv->total_chans++;
			पूर्ण
		पूर्ण
	पूर्ण

	dma_async_device_रेजिस्टर(dma_dev);

	वापस 0;
पूर्ण

अटल व्योम fsl_re_हटाओ_chan(काष्ठा fsl_re_chan *chan)
अणु
	tasklet_समाप्त(&chan->irqtask);

	dma_pool_मुक्त(chan->re_dev->hw_desc_pool, chan->inb_ring_virt_addr,
		      chan->inb_phys_addr);

	dma_pool_मुक्त(chan->re_dev->hw_desc_pool, chan->oub_ring_virt_addr,
		      chan->oub_phys_addr);
पूर्ण

अटल पूर्णांक fsl_re_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा fsl_re_drv_निजी *re_priv;
	काष्ठा device *dev;
	पूर्णांक i;

	dev = &ofdev->dev;
	re_priv = dev_get_drvdata(dev);

	/* Cleanup chan related memory areas */
	क्रम (i = 0; i < re_priv->total_chans; i++)
		fsl_re_हटाओ_chan(re_priv->re_jrs[i]);

	/* Unरेजिस्टर the driver */
	dma_async_device_unरेजिस्टर(&re_priv->dma_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_re_ids[] = अणु
	अणु .compatible = "fsl,raideng-v1.0", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_re_ids);

अटल काष्ठा platक्रमm_driver fsl_re_driver = अणु
	.driver = अणु
		.name = "fsl-raideng",
		.of_match_table = fsl_re_ids,
	पूर्ण,
	.probe = fsl_re_probe,
	.हटाओ = fsl_re_हटाओ,
पूर्ण;

module_platक्रमm_driver(fsl_re_driver);

MODULE_AUTHOR("Harninder Rai <harninder.rai@freescale.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Freescale RAID Engine Device Driver");
