<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018-2019 Synopsys, Inc. and/or its affiliates.
 * Synopsys DesignWare eDMA core driver
 *
 * Author: Gustavo Pimentel <gustavo.pimentel@synopsys.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/dmaengine.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/dma/edma.h>
#समावेश <linux/dma-mapping.h>

#समावेश "dw-edma-core.h"
#समावेश "dw-edma-v0-core.h"
#समावेश "../dmaengine.h"
#समावेश "../virt-dma.h"

अटल अंतरभूत
काष्ठा device *dchan2dev(काष्ठा dma_chan *dchan)
अणु
	वापस &dchan->dev->device;
पूर्ण

अटल अंतरभूत
काष्ठा device *chan2dev(काष्ठा dw_edma_chan *chan)
अणु
	वापस &chan->vc.chan.dev->device;
पूर्ण

अटल अंतरभूत
काष्ठा dw_edma_desc *vd2dw_edma_desc(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा dw_edma_desc, vd);
पूर्ण

अटल काष्ठा dw_edma_burst *dw_edma_alloc_burst(काष्ठा dw_edma_chunk *chunk)
अणु
	काष्ठा dw_edma_burst *burst;

	burst = kzalloc(माप(*burst), GFP_NOWAIT);
	अगर (unlikely(!burst))
		वापस शून्य;

	INIT_LIST_HEAD(&burst->list);
	अगर (chunk->burst) अणु
		/* Create and add new element पूर्णांकo the linked list */
		chunk->bursts_alloc++;
		list_add_tail(&burst->list, &chunk->burst->list);
	पूर्ण अन्यथा अणु
		/* List head */
		chunk->bursts_alloc = 0;
		chunk->burst = burst;
	पूर्ण

	वापस burst;
पूर्ण

अटल काष्ठा dw_edma_chunk *dw_edma_alloc_chunk(काष्ठा dw_edma_desc *desc)
अणु
	काष्ठा dw_edma_chan *chan = desc->chan;
	काष्ठा dw_edma *dw = chan->chip->dw;
	काष्ठा dw_edma_chunk *chunk;

	chunk = kzalloc(माप(*chunk), GFP_NOWAIT);
	अगर (unlikely(!chunk))
		वापस शून्य;

	INIT_LIST_HEAD(&chunk->list);
	chunk->chan = chan;
	/* Toggling change bit (CB) in each chunk, this is a mechanism to
	 * inक्रमm the eDMA HW block that this is a new linked list पढ़ोy
	 * to be consumed.
	 *  - Odd chunks originate CB equal to 0
	 *  - Even chunks originate CB equal to 1
	 */
	chunk->cb = !(desc->chunks_alloc % 2);
	अगर (chan->dir == EDMA_सूची_WRITE) अणु
		chunk->ll_region.paddr = dw->ll_region_wr[chan->id].paddr;
		chunk->ll_region.vaddr = dw->ll_region_wr[chan->id].vaddr;
	पूर्ण अन्यथा अणु
		chunk->ll_region.paddr = dw->ll_region_rd[chan->id].paddr;
		chunk->ll_region.vaddr = dw->ll_region_rd[chan->id].vaddr;
	पूर्ण

	अगर (desc->chunk) अणु
		/* Create and add new element पूर्णांकo the linked list */
		अगर (!dw_edma_alloc_burst(chunk)) अणु
			kमुक्त(chunk);
			वापस शून्य;
		पूर्ण
		desc->chunks_alloc++;
		list_add_tail(&chunk->list, &desc->chunk->list);
	पूर्ण अन्यथा अणु
		/* List head */
		chunk->burst = शून्य;
		desc->chunks_alloc = 0;
		desc->chunk = chunk;
	पूर्ण

	वापस chunk;
पूर्ण

अटल काष्ठा dw_edma_desc *dw_edma_alloc_desc(काष्ठा dw_edma_chan *chan)
अणु
	काष्ठा dw_edma_desc *desc;

	desc = kzalloc(माप(*desc), GFP_NOWAIT);
	अगर (unlikely(!desc))
		वापस शून्य;

	desc->chan = chan;
	अगर (!dw_edma_alloc_chunk(desc)) अणु
		kमुक्त(desc);
		वापस शून्य;
	पूर्ण

	वापस desc;
पूर्ण

अटल व्योम dw_edma_मुक्त_burst(काष्ठा dw_edma_chunk *chunk)
अणु
	काष्ठा dw_edma_burst *child, *_next;

	/* Remove all the list elements */
	list_क्रम_each_entry_safe(child, _next, &chunk->burst->list, list) अणु
		list_del(&child->list);
		kमुक्त(child);
		chunk->bursts_alloc--;
	पूर्ण

	/* Remove the list head */
	kमुक्त(child);
	chunk->burst = शून्य;
पूर्ण

अटल व्योम dw_edma_मुक्त_chunk(काष्ठा dw_edma_desc *desc)
अणु
	काष्ठा dw_edma_chunk *child, *_next;

	अगर (!desc->chunk)
		वापस;

	/* Remove all the list elements */
	list_क्रम_each_entry_safe(child, _next, &desc->chunk->list, list) अणु
		dw_edma_मुक्त_burst(child);
		list_del(&child->list);
		kमुक्त(child);
		desc->chunks_alloc--;
	पूर्ण

	/* Remove the list head */
	kमुक्त(child);
	desc->chunk = शून्य;
पूर्ण

अटल व्योम dw_edma_मुक्त_desc(काष्ठा dw_edma_desc *desc)
अणु
	dw_edma_मुक्त_chunk(desc);
	kमुक्त(desc);
पूर्ण

अटल व्योम vchan_मुक्त_desc(काष्ठा virt_dma_desc *vdesc)
अणु
	dw_edma_मुक्त_desc(vd2dw_edma_desc(vdesc));
पूर्ण

अटल व्योम dw_edma_start_transfer(काष्ठा dw_edma_chan *chan)
अणु
	काष्ठा dw_edma_chunk *child;
	काष्ठा dw_edma_desc *desc;
	काष्ठा virt_dma_desc *vd;

	vd = vchan_next_desc(&chan->vc);
	अगर (!vd)
		वापस;

	desc = vd2dw_edma_desc(vd);
	अगर (!desc)
		वापस;

	child = list_first_entry_or_null(&desc->chunk->list,
					 काष्ठा dw_edma_chunk, list);
	अगर (!child)
		वापस;

	dw_edma_v0_core_start(child, !desc->xfer_sz);
	desc->xfer_sz += child->ll_region.sz;
	dw_edma_मुक्त_burst(child);
	list_del(&child->list);
	kमुक्त(child);
	desc->chunks_alloc--;
पूर्ण

अटल पूर्णांक dw_edma_device_config(काष्ठा dma_chan *dchan,
				 काष्ठा dma_slave_config *config)
अणु
	काष्ठा dw_edma_chan *chan = dchan2dw_edma_chan(dchan);

	स_नकल(&chan->config, config, माप(*config));
	chan->configured = true;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_edma_device_छोड़ो(काष्ठा dma_chan *dchan)
अणु
	काष्ठा dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	पूर्णांक err = 0;

	अगर (!chan->configured)
		err = -EPERM;
	अन्यथा अगर (chan->status != EDMA_ST_BUSY)
		err = -EPERM;
	अन्यथा अगर (chan->request != EDMA_REQ_NONE)
		err = -EPERM;
	अन्यथा
		chan->request = EDMA_REQ_PAUSE;

	वापस err;
पूर्ण

अटल पूर्णांक dw_edma_device_resume(काष्ठा dma_chan *dchan)
अणु
	काष्ठा dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	पूर्णांक err = 0;

	अगर (!chan->configured) अणु
		err = -EPERM;
	पूर्ण अन्यथा अगर (chan->status != EDMA_ST_PAUSE) अणु
		err = -EPERM;
	पूर्ण अन्यथा अगर (chan->request != EDMA_REQ_NONE) अणु
		err = -EPERM;
	पूर्ण अन्यथा अणु
		chan->status = EDMA_ST_BUSY;
		dw_edma_start_transfer(chan);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dw_edma_device_terminate_all(काष्ठा dma_chan *dchan)
अणु
	काष्ठा dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	पूर्णांक err = 0;
	LIST_HEAD(head);

	अगर (!chan->configured) अणु
		/* Do nothing */
	पूर्ण अन्यथा अगर (chan->status == EDMA_ST_PAUSE) अणु
		chan->status = EDMA_ST_IDLE;
		chan->configured = false;
	पूर्ण अन्यथा अगर (chan->status == EDMA_ST_IDLE) अणु
		chan->configured = false;
	पूर्ण अन्यथा अगर (dw_edma_v0_core_ch_status(chan) == DMA_COMPLETE) अणु
		/*
		 * The channel is in a false BUSY state, probably didn't
		 * receive or lost an पूर्णांकerrupt
		 */
		chan->status = EDMA_ST_IDLE;
		chan->configured = false;
	पूर्ण अन्यथा अगर (chan->request > EDMA_REQ_PAUSE) अणु
		err = -EPERM;
	पूर्ण अन्यथा अणु
		chan->request = EDMA_REQ_STOP;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम dw_edma_device_issue_pending(काष्ठा dma_chan *dchan)
अणु
	काष्ठा dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->vc.lock, flags);
	अगर (chan->configured && chan->request == EDMA_REQ_NONE &&
	    chan->status == EDMA_ST_IDLE && vchan_issue_pending(&chan->vc)) अणु
		chan->status = EDMA_ST_BUSY;
		dw_edma_start_transfer(chan);
	पूर्ण
	spin_unlock_irqrestore(&chan->vc.lock, flags);
पूर्ण

अटल क्रमागत dma_status
dw_edma_device_tx_status(काष्ठा dma_chan *dchan, dma_cookie_t cookie,
			 काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	काष्ठा dw_edma_desc *desc;
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;
	क्रमागत dma_status ret;
	u32 residue = 0;

	ret = dma_cookie_status(dchan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	अगर (ret == DMA_IN_PROGRESS && chan->status == EDMA_ST_PAUSE)
		ret = DMA_PAUSED;

	अगर (!txstate)
		जाओ ret_residue;

	spin_lock_irqsave(&chan->vc.lock, flags);
	vd = vchan_find_desc(&chan->vc, cookie);
	अगर (vd) अणु
		desc = vd2dw_edma_desc(vd);
		अगर (desc)
			residue = desc->alloc_sz - desc->xfer_sz;
	पूर्ण
	spin_unlock_irqrestore(&chan->vc.lock, flags);

ret_residue:
	dma_set_residue(txstate, residue);

	वापस ret;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
dw_edma_device_transfer(काष्ठा dw_edma_transfer *xfer)
अणु
	काष्ठा dw_edma_chan *chan = dchan2dw_edma_chan(xfer->dchan);
	क्रमागत dma_transfer_direction dir = xfer->direction;
	phys_addr_t src_addr, dst_addr;
	काष्ठा scatterlist *sg = शून्य;
	काष्ठा dw_edma_chunk *chunk;
	काष्ठा dw_edma_burst *burst;
	काष्ठा dw_edma_desc *desc;
	u32 cnt = 0;
	पूर्णांक i;

	अगर (!chan->configured)
		वापस शून्य;

	चयन (chan->config.direction) अणु
	हाल DMA_DEV_TO_MEM: /* local DMA */
		अगर (dir == DMA_DEV_TO_MEM && chan->dir == EDMA_सूची_READ)
			अवरोध;
		वापस शून्य;
	हाल DMA_MEM_TO_DEV: /* local DMA */
		अगर (dir == DMA_MEM_TO_DEV && chan->dir == EDMA_सूची_WRITE)
			अवरोध;
		वापस शून्य;
	शेष: /* remote DMA */
		अगर (dir == DMA_MEM_TO_DEV && chan->dir == EDMA_सूची_READ)
			अवरोध;
		अगर (dir == DMA_DEV_TO_MEM && chan->dir == EDMA_सूची_WRITE)
			अवरोध;
		वापस शून्य;
	पूर्ण

	अगर (xfer->type == EDMA_XFER_CYCLIC) अणु
		अगर (!xfer->xfer.cyclic.len || !xfer->xfer.cyclic.cnt)
			वापस शून्य;
	पूर्ण अन्यथा अगर (xfer->type == EDMA_XFER_SCATTER_GATHER) अणु
		अगर (xfer->xfer.sg.len < 1)
			वापस शून्य;
	पूर्ण अन्यथा अगर (xfer->type == EDMA_XFER_INTERLEAVED) अणु
		अगर (!xfer->xfer.il->numf)
			वापस शून्य;
		अगर (xfer->xfer.il->numf > 0 && xfer->xfer.il->frame_size > 0)
			वापस शून्य;
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण

	desc = dw_edma_alloc_desc(chan);
	अगर (unlikely(!desc))
		जाओ err_alloc;

	chunk = dw_edma_alloc_chunk(desc);
	अगर (unlikely(!chunk))
		जाओ err_alloc;

	अगर (xfer->type == EDMA_XFER_INTERLEAVED) अणु
		src_addr = xfer->xfer.il->src_start;
		dst_addr = xfer->xfer.il->dst_start;
	पूर्ण अन्यथा अणु
		src_addr = chan->config.src_addr;
		dst_addr = chan->config.dst_addr;
	पूर्ण

	अगर (xfer->type == EDMA_XFER_CYCLIC) अणु
		cnt = xfer->xfer.cyclic.cnt;
	पूर्ण अन्यथा अगर (xfer->type == EDMA_XFER_SCATTER_GATHER) अणु
		cnt = xfer->xfer.sg.len;
		sg = xfer->xfer.sg.sgl;
	पूर्ण अन्यथा अगर (xfer->type == EDMA_XFER_INTERLEAVED) अणु
		अगर (xfer->xfer.il->numf > 0)
			cnt = xfer->xfer.il->numf;
		अन्यथा
			cnt = xfer->xfer.il->frame_size;
	पूर्ण

	क्रम (i = 0; i < cnt; i++) अणु
		अगर (xfer->type == EDMA_XFER_SCATTER_GATHER && !sg)
			अवरोध;

		अगर (chunk->bursts_alloc == chan->ll_max) अणु
			chunk = dw_edma_alloc_chunk(desc);
			अगर (unlikely(!chunk))
				जाओ err_alloc;
		पूर्ण

		burst = dw_edma_alloc_burst(chunk);
		अगर (unlikely(!burst))
			जाओ err_alloc;

		अगर (xfer->type == EDMA_XFER_CYCLIC)
			burst->sz = xfer->xfer.cyclic.len;
		अन्यथा अगर (xfer->type == EDMA_XFER_SCATTER_GATHER)
			burst->sz = sg_dma_len(sg);
		अन्यथा अगर (xfer->type == EDMA_XFER_INTERLEAVED)
			burst->sz = xfer->xfer.il->sgl[i].size;

		chunk->ll_region.sz += burst->sz;
		desc->alloc_sz += burst->sz;

		अगर (chan->dir == EDMA_सूची_WRITE) अणु
			burst->sar = src_addr;
			अगर (xfer->type == EDMA_XFER_CYCLIC) अणु
				burst->dar = xfer->xfer.cyclic.paddr;
			पूर्ण अन्यथा अगर (xfer->type == EDMA_XFER_SCATTER_GATHER) अणु
				src_addr += sg_dma_len(sg);
				burst->dar = sg_dma_address(sg);
				/* Unlike the typical assumption by other
				 * drivers/IPs the peripheral memory isn't
				 * a FIFO memory, in this हाल, it's a
				 * linear memory and that why the source
				 * and destination addresses are increased
				 * by the same portion (data length)
				 */
			पूर्ण
		पूर्ण अन्यथा अणु
			burst->dar = dst_addr;
			अगर (xfer->type == EDMA_XFER_CYCLIC) अणु
				burst->sar = xfer->xfer.cyclic.paddr;
			पूर्ण अन्यथा अगर (xfer->type == EDMA_XFER_SCATTER_GATHER) अणु
				dst_addr += sg_dma_len(sg);
				burst->sar = sg_dma_address(sg);
				/* Unlike the typical assumption by other
				 * drivers/IPs the peripheral memory isn't
				 * a FIFO memory, in this हाल, it's a
				 * linear memory and that why the source
				 * and destination addresses are increased
				 * by the same portion (data length)
				 */
			पूर्ण
		पूर्ण

		अगर (xfer->type == EDMA_XFER_SCATTER_GATHER) अणु
			sg = sg_next(sg);
		पूर्ण अन्यथा अगर (xfer->type == EDMA_XFER_INTERLEAVED &&
			   xfer->xfer.il->frame_size > 0) अणु
			काष्ठा dma_पूर्णांकerleaved_ढाँचा *il = xfer->xfer.il;
			काष्ठा data_chunk *dc = &il->sgl[i];

			अगर (il->src_sgl) अणु
				src_addr += burst->sz;
				src_addr += dmaengine_get_src_icg(il, dc);
			पूर्ण

			अगर (il->dst_sgl) अणु
				dst_addr += burst->sz;
				dst_addr += dmaengine_get_dst_icg(il, dc);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस vchan_tx_prep(&chan->vc, &desc->vd, xfer->flags);

err_alloc:
	अगर (desc)
		dw_edma_मुक्त_desc(desc);

	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
dw_edma_device_prep_slave_sg(काष्ठा dma_chan *dchan, काष्ठा scatterlist *sgl,
			     अचिन्हित पूर्णांक len,
			     क्रमागत dma_transfer_direction direction,
			     अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा dw_edma_transfer xfer;

	xfer.dchan = dchan;
	xfer.direction = direction;
	xfer.xfer.sg.sgl = sgl;
	xfer.xfer.sg.len = len;
	xfer.flags = flags;
	xfer.type = EDMA_XFER_SCATTER_GATHER;

	वापस dw_edma_device_transfer(&xfer);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
dw_edma_device_prep_dma_cyclic(काष्ठा dma_chan *dchan, dma_addr_t paddr,
			       माप_प्रकार len, माप_प्रकार count,
			       क्रमागत dma_transfer_direction direction,
			       अचिन्हित दीर्घ flags)
अणु
	काष्ठा dw_edma_transfer xfer;

	xfer.dchan = dchan;
	xfer.direction = direction;
	xfer.xfer.cyclic.paddr = paddr;
	xfer.xfer.cyclic.len = len;
	xfer.xfer.cyclic.cnt = count;
	xfer.flags = flags;
	xfer.type = EDMA_XFER_CYCLIC;

	वापस dw_edma_device_transfer(&xfer);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
dw_edma_device_prep_पूर्णांकerleaved_dma(काष्ठा dma_chan *dchan,
				    काष्ठा dma_पूर्णांकerleaved_ढाँचा *ilt,
				    अचिन्हित दीर्घ flags)
अणु
	काष्ठा dw_edma_transfer xfer;

	xfer.dchan = dchan;
	xfer.direction = ilt->dir;
	xfer.xfer.il = ilt;
	xfer.flags = flags;
	xfer.type = EDMA_XFER_INTERLEAVED;

	वापस dw_edma_device_transfer(&xfer);
पूर्ण

अटल व्योम dw_edma_करोne_पूर्णांकerrupt(काष्ठा dw_edma_chan *chan)
अणु
	काष्ठा dw_edma_desc *desc;
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;

	dw_edma_v0_core_clear_करोne_पूर्णांक(chan);

	spin_lock_irqsave(&chan->vc.lock, flags);
	vd = vchan_next_desc(&chan->vc);
	अगर (vd) अणु
		चयन (chan->request) अणु
		हाल EDMA_REQ_NONE:
			desc = vd2dw_edma_desc(vd);
			अगर (desc->chunks_alloc) अणु
				chan->status = EDMA_ST_BUSY;
				dw_edma_start_transfer(chan);
			पूर्ण अन्यथा अणु
				list_del(&vd->node);
				vchan_cookie_complete(vd);
				chan->status = EDMA_ST_IDLE;
			पूर्ण
			अवरोध;

		हाल EDMA_REQ_STOP:
			list_del(&vd->node);
			vchan_cookie_complete(vd);
			chan->request = EDMA_REQ_NONE;
			chan->status = EDMA_ST_IDLE;
			अवरोध;

		हाल EDMA_REQ_PAUSE:
			chan->request = EDMA_REQ_NONE;
			chan->status = EDMA_ST_PAUSE;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&chan->vc.lock, flags);
पूर्ण

अटल व्योम dw_edma_पात_पूर्णांकerrupt(काष्ठा dw_edma_chan *chan)
अणु
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;

	dw_edma_v0_core_clear_पात_पूर्णांक(chan);

	spin_lock_irqsave(&chan->vc.lock, flags);
	vd = vchan_next_desc(&chan->vc);
	अगर (vd) अणु
		list_del(&vd->node);
		vchan_cookie_complete(vd);
	पूर्ण
	spin_unlock_irqrestore(&chan->vc.lock, flags);
	chan->request = EDMA_REQ_NONE;
	chan->status = EDMA_ST_IDLE;
पूर्ण

अटल irqवापस_t dw_edma_पूर्णांकerrupt(पूर्णांक irq, व्योम *data, bool ग_लिखो)
अणु
	काष्ठा dw_edma_irq *dw_irq = data;
	काष्ठा dw_edma *dw = dw_irq->dw;
	अचिन्हित दीर्घ total, pos, val;
	अचिन्हित दीर्घ off;
	u32 mask;

	अगर (ग_लिखो) अणु
		total = dw->wr_ch_cnt;
		off = 0;
		mask = dw_irq->wr_mask;
	पूर्ण अन्यथा अणु
		total = dw->rd_ch_cnt;
		off = dw->wr_ch_cnt;
		mask = dw_irq->rd_mask;
	पूर्ण

	val = dw_edma_v0_core_status_करोne_पूर्णांक(dw, ग_लिखो ?
							  EDMA_सूची_WRITE :
							  EDMA_सूची_READ);
	val &= mask;
	क्रम_each_set_bit(pos, &val, total) अणु
		काष्ठा dw_edma_chan *chan = &dw->chan[pos + off];

		dw_edma_करोne_पूर्णांकerrupt(chan);
	पूर्ण

	val = dw_edma_v0_core_status_पात_पूर्णांक(dw, ग_लिखो ?
							   EDMA_सूची_WRITE :
							   EDMA_सूची_READ);
	val &= mask;
	क्रम_each_set_bit(pos, &val, total) अणु
		काष्ठा dw_edma_chan *chan = &dw->chan[pos + off];

		dw_edma_पात_पूर्णांकerrupt(chan);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत irqवापस_t dw_edma_पूर्णांकerrupt_ग_लिखो(पूर्णांक irq, व्योम *data)
अणु
	वापस dw_edma_पूर्णांकerrupt(irq, data, true);
पूर्ण

अटल अंतरभूत irqवापस_t dw_edma_पूर्णांकerrupt_पढ़ो(पूर्णांक irq, व्योम *data)
अणु
	वापस dw_edma_पूर्णांकerrupt(irq, data, false);
पूर्ण

अटल irqवापस_t dw_edma_पूर्णांकerrupt_common(पूर्णांक irq, व्योम *data)
अणु
	dw_edma_पूर्णांकerrupt(irq, data, true);
	dw_edma_पूर्णांकerrupt(irq, data, false);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dw_edma_alloc_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा dw_edma_chan *chan = dchan2dw_edma_chan(dchan);

	अगर (chan->status != EDMA_ST_IDLE)
		वापस -EBUSY;

	pm_runसमय_get(chan->chip->dev);

	वापस 0;
पूर्ण

अटल व्योम dw_edma_मुक्त_chan_resources(काष्ठा dma_chan *dchan)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(5000);
	काष्ठा dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	पूर्णांक ret;

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		ret = dw_edma_device_terminate_all(dchan);
		अगर (!ret)
			अवरोध;

		अगर (समय_after_eq(jअगरfies, समयout))
			वापस;

		cpu_relax();
	पूर्ण

	pm_runसमय_put(chan->chip->dev);
पूर्ण

अटल पूर्णांक dw_edma_channel_setup(काष्ठा dw_edma_chip *chip, bool ग_लिखो,
				 u32 wr_alloc, u32 rd_alloc)
अणु
	काष्ठा dw_edma_region *dt_region;
	काष्ठा device *dev = chip->dev;
	काष्ठा dw_edma *dw = chip->dw;
	काष्ठा dw_edma_chan *chan;
	काष्ठा dw_edma_irq *irq;
	काष्ठा dma_device *dma;
	u32 alloc, off_alloc;
	u32 i, j, cnt;
	पूर्णांक err = 0;
	u32 pos;

	अगर (ग_लिखो) अणु
		i = 0;
		cnt = dw->wr_ch_cnt;
		dma = &dw->wr_edma;
		alloc = wr_alloc;
		off_alloc = 0;
	पूर्ण अन्यथा अणु
		i = dw->wr_ch_cnt;
		cnt = dw->rd_ch_cnt;
		dma = &dw->rd_edma;
		alloc = rd_alloc;
		off_alloc = wr_alloc;
	पूर्ण

	INIT_LIST_HEAD(&dma->channels);
	क्रम (j = 0; (alloc || dw->nr_irqs == 1) && j < cnt; j++, i++) अणु
		chan = &dw->chan[i];

		dt_region = devm_kzalloc(dev, माप(*dt_region), GFP_KERNEL);
		अगर (!dt_region)
			वापस -ENOMEM;

		chan->vc.chan.निजी = dt_region;

		chan->chip = chip;
		chan->id = j;
		chan->dir = ग_लिखो ? EDMA_सूची_WRITE : EDMA_सूची_READ;
		chan->configured = false;
		chan->request = EDMA_REQ_NONE;
		chan->status = EDMA_ST_IDLE;

		अगर (ग_लिखो)
			chan->ll_max = (dw->ll_region_wr[j].sz / EDMA_LL_SZ);
		अन्यथा
			chan->ll_max = (dw->ll_region_rd[j].sz / EDMA_LL_SZ);
		chan->ll_max -= 1;

		dev_vdbg(dev, "L. List:\tChannel %s[%u] max_cnt=%u\n",
			 ग_लिखो ? "write" : "read", j, chan->ll_max);

		अगर (dw->nr_irqs == 1)
			pos = 0;
		अन्यथा
			pos = off_alloc + (j % alloc);

		irq = &dw->irq[pos];

		अगर (ग_लिखो)
			irq->wr_mask |= BIT(j);
		अन्यथा
			irq->rd_mask |= BIT(j);

		irq->dw = dw;
		स_नकल(&chan->msi, &irq->msi, माप(chan->msi));

		dev_vdbg(dev, "MSI:\t\tChannel %s[%u] addr=0x%.8x%.8x, data=0x%.8x\n",
			 ग_लिखो ? "write" : "read", j,
			 chan->msi.address_hi, chan->msi.address_lo,
			 chan->msi.data);

		chan->vc.desc_मुक्त = vchan_मुक्त_desc;
		vchan_init(&chan->vc, dma);

		अगर (ग_लिखो) अणु
			dt_region->paddr = dw->dt_region_wr[j].paddr;
			dt_region->vaddr = dw->dt_region_wr[j].vaddr;
			dt_region->sz = dw->dt_region_wr[j].sz;
		पूर्ण अन्यथा अणु
			dt_region->paddr = dw->dt_region_rd[j].paddr;
			dt_region->vaddr = dw->dt_region_rd[j].vaddr;
			dt_region->sz = dw->dt_region_rd[j].sz;
		पूर्ण

		dw_edma_v0_core_device_config(chan);
	पूर्ण

	/* Set DMA channel capabilities */
	dma_cap_zero(dma->cap_mask);
	dma_cap_set(DMA_SLAVE, dma->cap_mask);
	dma_cap_set(DMA_CYCLIC, dma->cap_mask);
	dma_cap_set(DMA_PRIVATE, dma->cap_mask);
	dma_cap_set(DMA_INTERLEAVE, dma->cap_mask);
	dma->directions = BIT(ग_लिखो ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV);
	dma->src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	dma->dst_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	dma->residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;
	dma->chancnt = cnt;

	/* Set DMA channel callbacks */
	dma->dev = chip->dev;
	dma->device_alloc_chan_resources = dw_edma_alloc_chan_resources;
	dma->device_मुक्त_chan_resources = dw_edma_मुक्त_chan_resources;
	dma->device_config = dw_edma_device_config;
	dma->device_छोड़ो = dw_edma_device_छोड़ो;
	dma->device_resume = dw_edma_device_resume;
	dma->device_terminate_all = dw_edma_device_terminate_all;
	dma->device_issue_pending = dw_edma_device_issue_pending;
	dma->device_tx_status = dw_edma_device_tx_status;
	dma->device_prep_slave_sg = dw_edma_device_prep_slave_sg;
	dma->device_prep_dma_cyclic = dw_edma_device_prep_dma_cyclic;
	dma->device_prep_पूर्णांकerleaved_dma = dw_edma_device_prep_पूर्णांकerleaved_dma;

	dma_set_max_seg_size(dma->dev, U32_MAX);

	/* Register DMA device */
	err = dma_async_device_रेजिस्टर(dma);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम dw_edma_dec_irq_alloc(पूर्णांक *nr_irqs, u32 *alloc, u16 cnt)
अणु
	अगर (*nr_irqs && *alloc < cnt) अणु
		(*alloc)++;
		(*nr_irqs)--;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम dw_edma_add_irq_mask(u32 *mask, u32 alloc, u16 cnt)
अणु
	जबतक (*mask * alloc < cnt)
		(*mask)++;
पूर्ण

अटल पूर्णांक dw_edma_irq_request(काष्ठा dw_edma_chip *chip,
			       u32 *wr_alloc, u32 *rd_alloc)
अणु
	काष्ठा device *dev = chip->dev;
	काष्ठा dw_edma *dw = chip->dw;
	u32 wr_mask = 1;
	u32 rd_mask = 1;
	पूर्णांक i, err = 0;
	u32 ch_cnt;
	पूर्णांक irq;

	ch_cnt = dw->wr_ch_cnt + dw->rd_ch_cnt;

	अगर (dw->nr_irqs < 1)
		वापस -EINVAL;

	अगर (dw->nr_irqs == 1) अणु
		/* Common IRQ shared among all channels */
		irq = dw->ops->irq_vector(dev, 0);
		err = request_irq(irq, dw_edma_पूर्णांकerrupt_common,
				  IRQF_SHARED, dw->name, &dw->irq[0]);
		अगर (err) अणु
			dw->nr_irqs = 0;
			वापस err;
		पूर्ण

		अगर (irq_get_msi_desc(irq))
			get_cached_msi_msg(irq, &dw->irq[0].msi);
	पूर्ण अन्यथा अणु
		/* Distribute IRQs equally among all channels */
		पूर्णांक पंचांगp = dw->nr_irqs;

		जबतक (पंचांगp && (*wr_alloc + *rd_alloc) < ch_cnt) अणु
			dw_edma_dec_irq_alloc(&पंचांगp, wr_alloc, dw->wr_ch_cnt);
			dw_edma_dec_irq_alloc(&पंचांगp, rd_alloc, dw->rd_ch_cnt);
		पूर्ण

		dw_edma_add_irq_mask(&wr_mask, *wr_alloc, dw->wr_ch_cnt);
		dw_edma_add_irq_mask(&rd_mask, *rd_alloc, dw->rd_ch_cnt);

		क्रम (i = 0; i < (*wr_alloc + *rd_alloc); i++) अणु
			irq = dw->ops->irq_vector(dev, i);
			err = request_irq(irq,
					  i < *wr_alloc ?
						dw_edma_पूर्णांकerrupt_ग_लिखो :
						dw_edma_पूर्णांकerrupt_पढ़ो,
					  IRQF_SHARED, dw->name,
					  &dw->irq[i]);
			अगर (err) अणु
				dw->nr_irqs = i;
				वापस err;
			पूर्ण

			अगर (irq_get_msi_desc(irq))
				get_cached_msi_msg(irq, &dw->irq[i].msi);
		पूर्ण

		dw->nr_irqs = i;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक dw_edma_probe(काष्ठा dw_edma_chip *chip)
अणु
	काष्ठा device *dev;
	काष्ठा dw_edma *dw;
	u32 wr_alloc = 0;
	u32 rd_alloc = 0;
	पूर्णांक i, err;

	अगर (!chip)
		वापस -EINVAL;

	dev = chip->dev;
	अगर (!dev)
		वापस -EINVAL;

	dw = chip->dw;
	अगर (!dw || !dw->irq || !dw->ops || !dw->ops->irq_vector)
		वापस -EINVAL;

	raw_spin_lock_init(&dw->lock);

	dw->wr_ch_cnt = min_t(u16, dw->wr_ch_cnt,
			      dw_edma_v0_core_ch_count(dw, EDMA_सूची_WRITE));
	dw->wr_ch_cnt = min_t(u16, dw->wr_ch_cnt, EDMA_MAX_WR_CH);

	dw->rd_ch_cnt = min_t(u16, dw->rd_ch_cnt,
			      dw_edma_v0_core_ch_count(dw, EDMA_सूची_READ));
	dw->rd_ch_cnt = min_t(u16, dw->rd_ch_cnt, EDMA_MAX_RD_CH);

	अगर (!dw->wr_ch_cnt && !dw->rd_ch_cnt)
		वापस -EINVAL;

	dev_vdbg(dev, "Channels:\twrite=%d, read=%d\n",
		 dw->wr_ch_cnt, dw->rd_ch_cnt);

	/* Allocate channels */
	dw->chan = devm_kसुस्मृति(dev, dw->wr_ch_cnt + dw->rd_ch_cnt,
				माप(*dw->chan), GFP_KERNEL);
	अगर (!dw->chan)
		वापस -ENOMEM;

	snम_लिखो(dw->name, माप(dw->name), "dw-edma-core:%d", chip->id);

	/* Disable eDMA, only to establish the ideal initial conditions */
	dw_edma_v0_core_off(dw);

	/* Request IRQs */
	err = dw_edma_irq_request(chip, &wr_alloc, &rd_alloc);
	अगर (err)
		वापस err;

	/* Setup ग_लिखो channels */
	err = dw_edma_channel_setup(chip, true, wr_alloc, rd_alloc);
	अगर (err)
		जाओ err_irq_मुक्त;

	/* Setup पढ़ो channels */
	err = dw_edma_channel_setup(chip, false, wr_alloc, rd_alloc);
	अगर (err)
		जाओ err_irq_मुक्त;

	/* Power management */
	pm_runसमय_enable(dev);

	/* Turn debugfs on */
	dw_edma_v0_core_debugfs_on(chip);

	वापस 0;

err_irq_मुक्त:
	क्रम (i = (dw->nr_irqs - 1); i >= 0; i--)
		मुक्त_irq(dw->ops->irq_vector(dev, i), &dw->irq[i]);

	dw->nr_irqs = 0;

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(dw_edma_probe);

पूर्णांक dw_edma_हटाओ(काष्ठा dw_edma_chip *chip)
अणु
	काष्ठा dw_edma_chan *chan, *_chan;
	काष्ठा device *dev = chip->dev;
	काष्ठा dw_edma *dw = chip->dw;
	पूर्णांक i;

	/* Disable eDMA */
	dw_edma_v0_core_off(dw);

	/* Free irqs */
	क्रम (i = (dw->nr_irqs - 1); i >= 0; i--)
		मुक्त_irq(dw->ops->irq_vector(dev, i), &dw->irq[i]);

	/* Power management */
	pm_runसमय_disable(dev);

	/* Deरेजिस्टर eDMA device */
	dma_async_device_unरेजिस्टर(&dw->wr_edma);
	list_क्रम_each_entry_safe(chan, _chan, &dw->wr_edma.channels,
				 vc.chan.device_node) अणु
		tasklet_समाप्त(&chan->vc.task);
		list_del(&chan->vc.chan.device_node);
	पूर्ण

	dma_async_device_unरेजिस्टर(&dw->rd_edma);
	list_क्रम_each_entry_safe(chan, _chan, &dw->rd_edma.channels,
				 vc.chan.device_node) अणु
		tasklet_समाप्त(&chan->vc.task);
		list_del(&chan->vc.chan.device_node);
	पूर्ण

	/* Turn debugfs off */
	dw_edma_v0_core_debugfs_off(chip);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dw_edma_हटाओ);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Synopsys DesignWare eDMA controller core driver");
MODULE_AUTHOR("Gustavo Pimentel <gustavo.pimentel@synopsys.com>");
