<शैली गुरु>
/*
 * DMM IOMMU driver support functions क्रम TI OMAP processors.
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Rob Clark <rob@ti.com>
 *         Andy Gross <andy.gross@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h> /* platक्रमm_device() */
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/रुको.h>

#समावेश "omap_dmm_tiler.h"
#समावेश "omap_dmm_priv.h"

#घोषणा DMM_DRIVER_NAME "dmm"

/* mappings क्रम associating views to luts */
अटल काष्ठा tcm *containers[TILFMT_NFORMATS];
अटल काष्ठा dmm *omap_dmm;

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id dmm_of_match[];
#पूर्ण_अगर

/* global spinlock क्रम protecting lists */
अटल DEFINE_SPINLOCK(list_lock);

/* Geometry table */
#घोषणा GEOM(xshअगरt, yshअगरt, bytes_per_pixel) अणु \
		.x_shft = (xshअगरt), \
		.y_shft = (yshअगरt), \
		.cpp    = (bytes_per_pixel), \
		.slot_w = 1 << (SLOT_WIDTH_BITS - (xshअगरt)), \
		.slot_h = 1 << (SLOT_HEIGHT_BITS - (yshअगरt)), \
	पूर्ण

अटल स्थिर काष्ठा अणु
	u32 x_shft;	/* unused X-bits (as part of bpp) */
	u32 y_shft;	/* unused Y-bits (as part of bpp) */
	u32 cpp;		/* bytes/अक्षरs per pixel */
	u32 slot_w;	/* width of each slot (in pixels) */
	u32 slot_h;	/* height of each slot (in pixels) */
पूर्ण geom[TILFMT_NFORMATS] = अणु
	[TILFMT_8BIT]  = GEOM(0, 0, 1),
	[TILFMT_16BIT] = GEOM(0, 1, 2),
	[TILFMT_32BIT] = GEOM(1, 1, 4),
	[TILFMT_PAGE]  = GEOM(SLOT_WIDTH_BITS, SLOT_HEIGHT_BITS, 1),
पूर्ण;


/* lookup table क्रम रेजिस्टरs w/ per-engine instances */
अटल स्थिर u32 reg[][4] = अणु
	[PAT_STATUS] = अणुDMM_PAT_STATUS__0, DMM_PAT_STATUS__1,
			DMM_PAT_STATUS__2, DMM_PAT_STATUS__3पूर्ण,
	[PAT_DESCR]  = अणुDMM_PAT_DESCR__0, DMM_PAT_DESCR__1,
			DMM_PAT_DESCR__2, DMM_PAT_DESCR__3पूर्ण,
पूर्ण;

अटल पूर्णांक dmm_dma_copy(काष्ठा dmm *dmm, dma_addr_t src, dma_addr_t dst)
अणु
	काष्ठा dma_async_tx_descriptor *tx;
	क्रमागत dma_status status;
	dma_cookie_t cookie;

	tx = dmaengine_prep_dma_स_नकल(dmm->wa_dma_chan, dst, src, 4, 0);
	अगर (!tx) अणु
		dev_err(dmm->dev, "Failed to prepare DMA memcpy\n");
		वापस -EIO;
	पूर्ण

	cookie = tx->tx_submit(tx);
	अगर (dma_submit_error(cookie)) अणु
		dev_err(dmm->dev, "Failed to do DMA tx_submit\n");
		वापस -EIO;
	पूर्ण

	status = dma_sync_रुको(dmm->wa_dma_chan, cookie);
	अगर (status != DMA_COMPLETE)
		dev_err(dmm->dev, "i878 wa DMA copy failure\n");

	dmaengine_terminate_all(dmm->wa_dma_chan);
	वापस 0;
पूर्ण

अटल u32 dmm_पढ़ो_wa(काष्ठा dmm *dmm, u32 reg)
अणु
	dma_addr_t src, dst;
	पूर्णांक r;

	src = dmm->phys_base + reg;
	dst = dmm->wa_dma_handle;

	r = dmm_dma_copy(dmm, src, dst);
	अगर (r) अणु
		dev_err(dmm->dev, "sDMA read transfer timeout\n");
		वापस पढ़ोl(dmm->base + reg);
	पूर्ण

	/*
	 * As per i878 workaround, the DMA is used to access the DMM रेजिस्टरs.
	 * Make sure that the पढ़ोl is not moved by the compiler or the CPU
	 * earlier than the DMA finished writing the value to memory.
	 */
	rmb();
	वापस पढ़ोl(dmm->wa_dma_data);
पूर्ण

अटल व्योम dmm_ग_लिखो_wa(काष्ठा dmm *dmm, u32 val, u32 reg)
अणु
	dma_addr_t src, dst;
	पूर्णांक r;

	ग_लिखोl(val, dmm->wa_dma_data);
	/*
	 * As per i878 workaround, the DMA is used to access the DMM रेजिस्टरs.
	 * Make sure that the ग_लिखोl is not moved by the compiler or the CPU, so
	 * the data will be in place beक्रमe we start the DMA to करो the actual
	 * रेजिस्टर ग_लिखो.
	 */
	wmb();

	src = dmm->wa_dma_handle;
	dst = dmm->phys_base + reg;

	r = dmm_dma_copy(dmm, src, dst);
	अगर (r) अणु
		dev_err(dmm->dev, "sDMA write transfer timeout\n");
		ग_लिखोl(val, dmm->base + reg);
	पूर्ण
पूर्ण

अटल u32 dmm_पढ़ो(काष्ठा dmm *dmm, u32 reg)
अणु
	अगर (dmm->dmm_workaround) अणु
		u32 v;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&dmm->wa_lock, flags);
		v = dmm_पढ़ो_wa(dmm, reg);
		spin_unlock_irqrestore(&dmm->wa_lock, flags);

		वापस v;
	पूर्ण अन्यथा अणु
		वापस पढ़ोl(dmm->base + reg);
	पूर्ण
पूर्ण

अटल व्योम dmm_ग_लिखो(काष्ठा dmm *dmm, u32 val, u32 reg)
अणु
	अगर (dmm->dmm_workaround) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&dmm->wa_lock, flags);
		dmm_ग_लिखो_wa(dmm, val, reg);
		spin_unlock_irqrestore(&dmm->wa_lock, flags);
	पूर्ण अन्यथा अणु
		ग_लिखोl(val, dmm->base + reg);
	पूर्ण
पूर्ण

अटल पूर्णांक dmm_workaround_init(काष्ठा dmm *dmm)
अणु
	dma_cap_mask_t mask;

	spin_lock_init(&dmm->wa_lock);

	dmm->wa_dma_data = dma_alloc_coherent(dmm->dev,  माप(u32),
					      &dmm->wa_dma_handle, GFP_KERNEL);
	अगर (!dmm->wa_dma_data)
		वापस -ENOMEM;

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	dmm->wa_dma_chan = dma_request_channel(mask, शून्य, शून्य);
	अगर (!dmm->wa_dma_chan) अणु
		dma_मुक्त_coherent(dmm->dev, 4, dmm->wa_dma_data, dmm->wa_dma_handle);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dmm_workaround_uninit(काष्ठा dmm *dmm)
अणु
	dma_release_channel(dmm->wa_dma_chan);

	dma_मुक्त_coherent(dmm->dev, 4, dmm->wa_dma_data, dmm->wa_dma_handle);
पूर्ण

/* simple allocator to grab next 16 byte aligned memory from txn */
अटल व्योम *alloc_dma(काष्ठा dmm_txn *txn, माप_प्रकार sz, dma_addr_t *pa)
अणु
	व्योम *ptr;
	काष्ठा refill_engine *engine = txn->engine_handle;

	/* dmm programming requires 16 byte aligned addresses */
	txn->current_pa = round_up(txn->current_pa, 16);
	txn->current_va = (व्योम *)round_up((दीर्घ)txn->current_va, 16);

	ptr = txn->current_va;
	*pa = txn->current_pa;

	txn->current_pa += sz;
	txn->current_va += sz;

	BUG_ON((txn->current_va - engine->refill_va) > REFILL_BUFFER_SIZE);

	वापस ptr;
पूर्ण

/* check status and spin until रुको_mask comes true */
अटल पूर्णांक रुको_status(काष्ठा refill_engine *engine, u32 रुको_mask)
अणु
	काष्ठा dmm *dmm = engine->dmm;
	u32 r = 0, err, i;

	i = DMM_FIXED_RETRY_COUNT;
	जबतक (true) अणु
		r = dmm_पढ़ो(dmm, reg[PAT_STATUS][engine->id]);
		err = r & DMM_PATSTATUS_ERR;
		अगर (err) अणु
			dev_err(dmm->dev,
				"%s: error (engine%d). PAT_STATUS: 0x%08x\n",
				__func__, engine->id, r);
			वापस -EFAULT;
		पूर्ण

		अगर ((r & रुको_mask) == रुको_mask)
			अवरोध;

		अगर (--i == 0) अणु
			dev_err(dmm->dev,
				"%s: timeout (engine%d). PAT_STATUS: 0x%08x\n",
				__func__, engine->id, r);
			वापस -ETIMEDOUT;
		पूर्ण

		udelay(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम release_engine(काष्ठा refill_engine *engine)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&list_lock, flags);
	list_add(&engine->idle_node, &omap_dmm->idle_head);
	spin_unlock_irqrestore(&list_lock, flags);

	atomic_inc(&omap_dmm->engine_counter);
	wake_up_पूर्णांकerruptible(&omap_dmm->engine_queue);
पूर्ण

अटल irqवापस_t omap_dmm_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा dmm *dmm = arg;
	u32 status = dmm_पढ़ो(dmm, DMM_PAT_IRQSTATUS);
	पूर्णांक i;

	/* ack IRQ */
	dmm_ग_लिखो(dmm, status, DMM_PAT_IRQSTATUS);

	क्रम (i = 0; i < dmm->num_engines; i++) अणु
		अगर (status & DMM_IRQSTAT_ERR_MASK)
			dev_err(dmm->dev,
				"irq error(engine%d): IRQSTAT 0x%02x\n",
				i, status & 0xff);

		अगर (status & DMM_IRQSTAT_LST) अणु
			अगर (dmm->engines[i].async)
				release_engine(&dmm->engines[i]);

			complete(&dmm->engines[i].compl);
		पूर्ण

		status >>= 8;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Get a handle क्रम a DMM transaction
 */
अटल काष्ठा dmm_txn *dmm_txn_init(काष्ठा dmm *dmm, काष्ठा tcm *tcm)
अणु
	काष्ठा dmm_txn *txn = शून्य;
	काष्ठा refill_engine *engine = शून्य;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;


	/* रुको until an engine is available */
	ret = रुको_event_पूर्णांकerruptible(omap_dmm->engine_queue,
		atomic_add_unless(&omap_dmm->engine_counter, -1, 0));
	अगर (ret)
		वापस ERR_PTR(ret);

	/* grab an idle engine */
	spin_lock_irqsave(&list_lock, flags);
	अगर (!list_empty(&dmm->idle_head)) अणु
		engine = list_entry(dmm->idle_head.next, काष्ठा refill_engine,
					idle_node);
		list_del(&engine->idle_node);
	पूर्ण
	spin_unlock_irqrestore(&list_lock, flags);

	BUG_ON(!engine);

	txn = &engine->txn;
	engine->tcm = tcm;
	txn->engine_handle = engine;
	txn->last_pat = शून्य;
	txn->current_va = engine->refill_va;
	txn->current_pa = engine->refill_pa;

	वापस txn;
पूर्ण

/*
 * Add region to DMM transaction.  If pages or pages[i] is शून्य, then the
 * corresponding slot is cleared (ie. dummy_pa is programmed)
 */
अटल व्योम dmm_txn_append(काष्ठा dmm_txn *txn, काष्ठा pat_area *area,
		काष्ठा page **pages, u32 npages, u32 roll)
अणु
	dma_addr_t pat_pa = 0, data_pa = 0;
	u32 *data;
	काष्ठा pat *pat;
	काष्ठा refill_engine *engine = txn->engine_handle;
	पूर्णांक columns = (1 + area->x1 - area->x0);
	पूर्णांक rows = (1 + area->y1 - area->y0);
	पूर्णांक i = columns*rows;

	pat = alloc_dma(txn, माप(*pat), &pat_pa);

	अगर (txn->last_pat)
		txn->last_pat->next_pa = (u32)pat_pa;

	pat->area = *area;

	/* adjust Y coordinates based off of container parameters */
	pat->area.y0 += engine->tcm->y_offset;
	pat->area.y1 += engine->tcm->y_offset;

	pat->ctrl = (काष्ठा pat_ctrl)अणु
			.start = 1,
			.lut_id = engine->tcm->lut_id,
		पूर्ण;

	data = alloc_dma(txn, 4*i, &data_pa);
	/* FIXME: what अगर data_pa is more than 32-bit ? */
	pat->data_pa = data_pa;

	जबतक (i--) अणु
		पूर्णांक n = i + roll;
		अगर (n >= npages)
			n -= npages;
		data[i] = (pages && pages[n]) ?
			page_to_phys(pages[n]) : engine->dmm->dummy_pa;
	पूर्ण

	txn->last_pat = pat;

	वापस;
पूर्ण

/*
 * Commit the DMM transaction.
 */
अटल पूर्णांक dmm_txn_commit(काष्ठा dmm_txn *txn, bool रुको)
अणु
	पूर्णांक ret = 0;
	काष्ठा refill_engine *engine = txn->engine_handle;
	काष्ठा dmm *dmm = engine->dmm;

	अगर (!txn->last_pat) अणु
		dev_err(engine->dmm->dev, "need at least one txn\n");
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण

	txn->last_pat->next_pa = 0;
	/* ensure that the written descriptors are visible to DMM */
	wmb();

	/*
	 * NOTE: the wmb() above should be enough, but there seems to be a bug
	 * in OMAP's memory barrier implementation, which in some rare हालs may
	 * cause the ग_लिखोs not to be observable after wmb().
	 */

	/* पढ़ो back to ensure the data is in RAM */
	पढ़ोl(&txn->last_pat->next_pa);

	/* ग_लिखो to PAT_DESCR to clear out any pending transaction */
	dmm_ग_लिखो(dmm, 0x0, reg[PAT_DESCR][engine->id]);

	/* रुको क्रम engine पढ़ोy: */
	ret = रुको_status(engine, DMM_PATSTATUS_READY);
	अगर (ret) अणु
		ret = -EFAULT;
		जाओ cleanup;
	पूर्ण

	/* mark whether it is async to denote list management in IRQ handler */
	engine->async = रुको ? false : true;
	reinit_completion(&engine->compl);
	/* verअगरy that the irq handler sees the 'async' and completion value */
	smp_mb();

	/* kick reload */
	dmm_ग_लिखो(dmm, engine->refill_pa, reg[PAT_DESCR][engine->id]);

	अगर (रुको) अणु
		अगर (!रुको_क्रम_completion_समयout(&engine->compl,
				msecs_to_jअगरfies(100))) अणु
			dev_err(dmm->dev, "timed out waiting for done\n");
			ret = -ETIMEDOUT;
			जाओ cleanup;
		पूर्ण

		/* Check the engine status beक्रमe जारी */
		ret = रुको_status(engine, DMM_PATSTATUS_READY |
				  DMM_PATSTATUS_VALID | DMM_PATSTATUS_DONE);
	पूर्ण

cleanup:
	/* only place engine back on list अगर we are करोne with it */
	अगर (ret || रुको)
		release_engine(engine);

	वापस ret;
पूर्ण

/*
 * DMM programming
 */
अटल पूर्णांक fill(काष्ठा tcm_area *area, काष्ठा page **pages,
		u32 npages, u32 roll, bool रुको)
अणु
	पूर्णांक ret = 0;
	काष्ठा tcm_area slice, area_s;
	काष्ठा dmm_txn *txn;

	/*
	 * FIXME
	 *
	 * Asynchronous fill करोes not work reliably, as the driver करोes not
	 * handle errors in the async code paths. The fill operation may
	 * silently fail, leading to leaking DMM engines, which may eventually
	 * lead to deadlock अगर we run out of DMM engines.
	 *
	 * For now, always set 'wait' so that we only use sync fills. Async
	 * fills should be fixed, or alternatively we could decide to only
	 * support sync fills and so the whole async code path could be हटाओd.
	 */

	रुको = true;

	txn = dmm_txn_init(omap_dmm, area->tcm);
	अगर (IS_ERR_OR_शून्य(txn))
		वापस -ENOMEM;

	tcm_क्रम_each_slice(slice, *area, area_s) अणु
		काष्ठा pat_area p_area = अणु
				.x0 = slice.p0.x,  .y0 = slice.p0.y,
				.x1 = slice.p1.x,  .y1 = slice.p1.y,
		पूर्ण;

		dmm_txn_append(txn, &p_area, pages, npages, roll);

		roll += tcm_माप(slice);
	पूर्ण

	ret = dmm_txn_commit(txn, रुको);

	वापस ret;
पूर्ण

/*
 * Pin/unpin
 */

/* note: slots क्रम which pages[i] == शून्य are filled w/ dummy page
 */
पूर्णांक tiler_pin(काष्ठा tiler_block *block, काष्ठा page **pages,
		u32 npages, u32 roll, bool रुको)
अणु
	पूर्णांक ret;

	ret = fill(&block->area, pages, npages, roll, रुको);

	अगर (ret)
		tiler_unpin(block);

	वापस ret;
पूर्ण

पूर्णांक tiler_unpin(काष्ठा tiler_block *block)
अणु
	वापस fill(&block->area, शून्य, 0, 0, false);
पूर्ण

/*
 * Reserve/release
 */
काष्ठा tiler_block *tiler_reserve_2d(क्रमागत tiler_fmt fmt, u16 w,
		u16 h, u16 align)
अणु
	काष्ठा tiler_block *block;
	u32 min_align = 128;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	u32 slot_bytes;

	block = kzalloc(माप(*block), GFP_KERNEL);
	अगर (!block)
		वापस ERR_PTR(-ENOMEM);

	BUG_ON(!validfmt(fmt));

	/* convert width/height to slots */
	w = DIV_ROUND_UP(w, geom[fmt].slot_w);
	h = DIV_ROUND_UP(h, geom[fmt].slot_h);

	/* convert alignment to slots */
	slot_bytes = geom[fmt].slot_w * geom[fmt].cpp;
	min_align = max(min_align, slot_bytes);
	align = (align > min_align) ? ALIGN(align, min_align) : min_align;
	align /= slot_bytes;

	block->fmt = fmt;

	ret = tcm_reserve_2d(containers[fmt], w, h, align, -1, slot_bytes,
			&block->area);
	अगर (ret) अणु
		kमुक्त(block);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* add to allocation list */
	spin_lock_irqsave(&list_lock, flags);
	list_add(&block->alloc_node, &omap_dmm->alloc_head);
	spin_unlock_irqrestore(&list_lock, flags);

	वापस block;
पूर्ण

काष्ठा tiler_block *tiler_reserve_1d(माप_प्रकार size)
अणु
	काष्ठा tiler_block *block = kzalloc(माप(*block), GFP_KERNEL);
	पूर्णांक num_pages = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	अचिन्हित दीर्घ flags;

	अगर (!block)
		वापस ERR_PTR(-ENOMEM);

	block->fmt = TILFMT_PAGE;

	अगर (tcm_reserve_1d(containers[TILFMT_PAGE], num_pages,
				&block->area)) अणु
		kमुक्त(block);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	spin_lock_irqsave(&list_lock, flags);
	list_add(&block->alloc_node, &omap_dmm->alloc_head);
	spin_unlock_irqrestore(&list_lock, flags);

	वापस block;
पूर्ण

/* note: अगर you have pin'd pages, you should have already unpin'd first! */
पूर्णांक tiler_release(काष्ठा tiler_block *block)
अणु
	पूर्णांक ret = tcm_मुक्त(&block->area);
	अचिन्हित दीर्घ flags;

	अगर (block->area.tcm)
		dev_err(omap_dmm->dev, "failed to release block\n");

	spin_lock_irqsave(&list_lock, flags);
	list_del(&block->alloc_node);
	spin_unlock_irqrestore(&list_lock, flags);

	kमुक्त(block);
	वापस ret;
पूर्ण

/*
 * Utils
 */

/* calculate the tiler space address of a pixel in a view orientation...
 * below description copied from the display subप्रणाली section of TRM:
 *
 * When the TILER is addressed, the bits:
 *   [28:27] = 0x0 क्रम 8-bit tiled
 *             0x1 क्रम 16-bit tiled
 *             0x2 क्रम 32-bit tiled
 *             0x3 क्रम page mode
 *   [31:29] = 0x0 क्रम 0-degree view
 *             0x1 क्रम 180-degree view + mirroring
 *             0x2 क्रम 0-degree view + mirroring
 *             0x3 क्रम 180-degree view
 *             0x4 क्रम 270-degree view + mirroring
 *             0x5 क्रम 270-degree view
 *             0x6 क्रम 90-degree view
 *             0x7 क्रम 90-degree view + mirroring
 * Otherwise the bits indicated the corresponding bit address to access
 * the SDRAM.
 */
अटल u32 tiler_get_address(क्रमागत tiler_fmt fmt, u32 orient, u32 x, u32 y)
अणु
	u32 x_bits, y_bits, पंचांगp, x_mask, y_mask, alignment;

	x_bits = CONT_WIDTH_BITS - geom[fmt].x_shft;
	y_bits = CONT_HEIGHT_BITS - geom[fmt].y_shft;
	alignment = geom[fmt].x_shft + geom[fmt].y_shft;

	/* validate coordinate */
	x_mask = MASK(x_bits);
	y_mask = MASK(y_bits);

	अगर (x < 0 || x > x_mask || y < 0 || y > y_mask) अणु
		DBG("invalid coords: %u < 0 || %u > %u || %u < 0 || %u > %u",
				x, x, x_mask, y, y, y_mask);
		वापस 0;
	पूर्ण

	/* account क्रम mirroring */
	अगर (orient & MASK_X_INVERT)
		x ^= x_mask;
	अगर (orient & MASK_Y_INVERT)
		y ^= y_mask;

	/* get coordinate address */
	अगर (orient & MASK_XY_FLIP)
		पंचांगp = ((x << y_bits) + y);
	अन्यथा
		पंचांगp = ((y << x_bits) + x);

	वापस TIL_ADDR((पंचांगp << alignment), orient, fmt);
पूर्ण

dma_addr_t tiler_ssptr(काष्ठा tiler_block *block)
अणु
	BUG_ON(!validfmt(block->fmt));

	वापस TILVIEW_8BIT + tiler_get_address(block->fmt, 0,
			block->area.p0.x * geom[block->fmt].slot_w,
			block->area.p0.y * geom[block->fmt].slot_h);
पूर्ण

dma_addr_t tiler_tsptr(काष्ठा tiler_block *block, u32 orient,
		u32 x, u32 y)
अणु
	काष्ठा tcm_pt *p = &block->area.p0;
	BUG_ON(!validfmt(block->fmt));

	वापस tiler_get_address(block->fmt, orient,
			(p->x * geom[block->fmt].slot_w) + x,
			(p->y * geom[block->fmt].slot_h) + y);
पूर्ण

व्योम tiler_align(क्रमागत tiler_fmt fmt, u16 *w, u16 *h)
अणु
	BUG_ON(!validfmt(fmt));
	*w = round_up(*w, geom[fmt].slot_w);
	*h = round_up(*h, geom[fmt].slot_h);
पूर्ण

u32 tiler_stride(क्रमागत tiler_fmt fmt, u32 orient)
अणु
	BUG_ON(!validfmt(fmt));

	अगर (orient & MASK_XY_FLIP)
		वापस 1 << (CONT_HEIGHT_BITS + geom[fmt].x_shft);
	अन्यथा
		वापस 1 << (CONT_WIDTH_BITS + geom[fmt].y_shft);
पूर्ण

माप_प्रकार tiler_size(क्रमागत tiler_fmt fmt, u16 w, u16 h)
अणु
	tiler_align(fmt, &w, &h);
	वापस geom[fmt].cpp * w * h;
पूर्ण

माप_प्रकार tiler_vsize(क्रमागत tiler_fmt fmt, u16 w, u16 h)
अणु
	BUG_ON(!validfmt(fmt));
	वापस round_up(geom[fmt].cpp * w, PAGE_SIZE) * h;
पूर्ण

u32 tiler_get_cpu_cache_flags(व्योम)
अणु
	वापस omap_dmm->plat_data->cpu_cache_flags;
पूर्ण

bool dmm_is_available(व्योम)
अणु
	वापस omap_dmm ? true : false;
पूर्ण

अटल पूर्णांक omap_dmm_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tiler_block *block, *_block;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (omap_dmm) अणु
		/* Disable all enabled पूर्णांकerrupts */
		dmm_ग_लिखो(omap_dmm, 0x7e7e7e7e, DMM_PAT_IRQENABLE_CLR);
		मुक्त_irq(omap_dmm->irq, omap_dmm);

		/* मुक्त all area regions */
		spin_lock_irqsave(&list_lock, flags);
		list_क्रम_each_entry_safe(block, _block, &omap_dmm->alloc_head,
					alloc_node) अणु
			list_del(&block->alloc_node);
			kमुक्त(block);
		पूर्ण
		spin_unlock_irqrestore(&list_lock, flags);

		क्रम (i = 0; i < omap_dmm->num_lut; i++)
			अगर (omap_dmm->tcm && omap_dmm->tcm[i])
				omap_dmm->tcm[i]->deinit(omap_dmm->tcm[i]);
		kमुक्त(omap_dmm->tcm);

		kमुक्त(omap_dmm->engines);
		अगर (omap_dmm->refill_va)
			dma_मुक्त_wc(omap_dmm->dev,
				    REFILL_BUFFER_SIZE * omap_dmm->num_engines,
				    omap_dmm->refill_va, omap_dmm->refill_pa);
		अगर (omap_dmm->dummy_page)
			__मुक्त_page(omap_dmm->dummy_page);

		अगर (omap_dmm->dmm_workaround)
			dmm_workaround_uninit(omap_dmm);

		iounmap(omap_dmm->base);
		kमुक्त(omap_dmm);
		omap_dmm = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_dmm_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret = -EFAULT, i;
	काष्ठा tcm_area area = अणु0पूर्ण;
	u32 hwinfo, pat_geom;
	काष्ठा resource *mem;

	omap_dmm = kzalloc(माप(*omap_dmm), GFP_KERNEL);
	अगर (!omap_dmm)
		जाओ fail;

	/* initialize lists */
	INIT_LIST_HEAD(&omap_dmm->alloc_head);
	INIT_LIST_HEAD(&omap_dmm->idle_head);

	init_रुकोqueue_head(&omap_dmm->engine_queue);

	अगर (dev->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *match;

		match = of_match_node(dmm_of_match, dev->dev.of_node);
		अगर (!match) अणु
			dev_err(&dev->dev, "failed to find matching device node\n");
			ret = -ENODEV;
			जाओ fail;
		पूर्ण

		omap_dmm->plat_data = match->data;
	पूर्ण

	/* lookup hwmod data - base address and irq */
	mem = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!mem) अणु
		dev_err(&dev->dev, "failed to get base address resource\n");
		जाओ fail;
	पूर्ण

	omap_dmm->phys_base = mem->start;
	omap_dmm->base = ioremap(mem->start, SZ_2K);

	अगर (!omap_dmm->base) अणु
		dev_err(&dev->dev, "failed to get dmm base address\n");
		जाओ fail;
	पूर्ण

	omap_dmm->irq = platक्रमm_get_irq(dev, 0);
	अगर (omap_dmm->irq < 0) अणु
		dev_err(&dev->dev, "failed to get IRQ resource\n");
		जाओ fail;
	पूर्ण

	omap_dmm->dev = &dev->dev;

	अगर (of_machine_is_compatible("ti,dra7")) अणु
		/*
		 * DRA7 Errata i878 says that MPU should not be used to access
		 * RAM and DMM at the same समय. As it's not possible to prevent
		 * MPU accessing RAM, we need to access DMM via a proxy.
		 */
		अगर (!dmm_workaround_init(omap_dmm)) अणु
			omap_dmm->dmm_workaround = true;
			dev_info(&dev->dev,
				"workaround for errata i878 in use\n");
		पूर्ण अन्यथा अणु
			dev_warn(&dev->dev,
				 "failed to initialize work-around for i878\n");
		पूर्ण
	पूर्ण

	hwinfo = dmm_पढ़ो(omap_dmm, DMM_PAT_HWINFO);
	omap_dmm->num_engines = (hwinfo >> 24) & 0x1F;
	omap_dmm->num_lut = (hwinfo >> 16) & 0x1F;
	omap_dmm->container_width = 256;
	omap_dmm->container_height = 128;

	atomic_set(&omap_dmm->engine_counter, omap_dmm->num_engines);

	/* पढ़ो out actual LUT width and height */
	pat_geom = dmm_पढ़ो(omap_dmm, DMM_PAT_GEOMETRY);
	omap_dmm->lut_width = ((pat_geom >> 16) & 0xF) << 5;
	omap_dmm->lut_height = ((pat_geom >> 24) & 0xF) << 5;

	/* increment LUT by one अगर on OMAP5 */
	/* LUT has twice the height, and is split पूर्णांकo a separate container */
	अगर (omap_dmm->lut_height != omap_dmm->container_height)
		omap_dmm->num_lut++;

	/* initialize DMM रेजिस्टरs */
	dmm_ग_लिखो(omap_dmm, 0x88888888, DMM_PAT_VIEW__0);
	dmm_ग_लिखो(omap_dmm, 0x88888888, DMM_PAT_VIEW__1);
	dmm_ग_लिखो(omap_dmm, 0x80808080, DMM_PAT_VIEW_MAP__0);
	dmm_ग_लिखो(omap_dmm, 0x80000000, DMM_PAT_VIEW_MAP_BASE);
	dmm_ग_लिखो(omap_dmm, 0x88888888, DMM_TILER_OR__0);
	dmm_ग_लिखो(omap_dmm, 0x88888888, DMM_TILER_OR__1);

	omap_dmm->dummy_page = alloc_page(GFP_KERNEL | __GFP_DMA32);
	अगर (!omap_dmm->dummy_page) अणु
		dev_err(&dev->dev, "could not allocate dummy page\n");
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* set dma mask क्रम device */
	ret = dma_set_coherent_mask(&dev->dev, DMA_BIT_MASK(32));
	अगर (ret)
		जाओ fail;

	omap_dmm->dummy_pa = page_to_phys(omap_dmm->dummy_page);

	/* alloc refill memory */
	omap_dmm->refill_va = dma_alloc_wc(&dev->dev,
					   REFILL_BUFFER_SIZE * omap_dmm->num_engines,
					   &omap_dmm->refill_pa, GFP_KERNEL);
	अगर (!omap_dmm->refill_va) अणु
		dev_err(&dev->dev, "could not allocate refill memory\n");
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* alloc engines */
	omap_dmm->engines = kसुस्मृति(omap_dmm->num_engines,
				    माप(*omap_dmm->engines), GFP_KERNEL);
	अगर (!omap_dmm->engines) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	क्रम (i = 0; i < omap_dmm->num_engines; i++) अणु
		omap_dmm->engines[i].id = i;
		omap_dmm->engines[i].dmm = omap_dmm;
		omap_dmm->engines[i].refill_va = omap_dmm->refill_va +
						(REFILL_BUFFER_SIZE * i);
		omap_dmm->engines[i].refill_pa = omap_dmm->refill_pa +
						(REFILL_BUFFER_SIZE * i);
		init_completion(&omap_dmm->engines[i].compl);

		list_add(&omap_dmm->engines[i].idle_node, &omap_dmm->idle_head);
	पूर्ण

	omap_dmm->tcm = kसुस्मृति(omap_dmm->num_lut, माप(*omap_dmm->tcm),
				GFP_KERNEL);
	अगर (!omap_dmm->tcm) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* init containers */
	/* Each LUT is associated with a TCM (container manager).  We use the
	   lut_id to denote the lut_id used to identअगरy the correct LUT क्रम
	   programming during reill operations */
	क्रम (i = 0; i < omap_dmm->num_lut; i++) अणु
		omap_dmm->tcm[i] = sita_init(omap_dmm->container_width,
						omap_dmm->container_height);

		अगर (!omap_dmm->tcm[i]) अणु
			dev_err(&dev->dev, "failed to allocate container\n");
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		omap_dmm->tcm[i]->lut_id = i;
	पूर्ण

	/* assign access mode containers to applicable tcm container */
	/* OMAP 4 has 1 container क्रम all 4 views */
	/* OMAP 5 has 2 containers, 1 क्रम 2D and 1 क्रम 1D */
	containers[TILFMT_8BIT] = omap_dmm->tcm[0];
	containers[TILFMT_16BIT] = omap_dmm->tcm[0];
	containers[TILFMT_32BIT] = omap_dmm->tcm[0];

	अगर (omap_dmm->container_height != omap_dmm->lut_height) अणु
		/* second LUT is used क्रम PAGE mode.  Programming must use
		   y offset that is added to all y coordinates.  LUT id is still
		   0, because it is the same LUT, just the upper 128 lines */
		containers[TILFMT_PAGE] = omap_dmm->tcm[1];
		omap_dmm->tcm[1]->y_offset = OMAP5_LUT_OFFSET;
		omap_dmm->tcm[1]->lut_id = 0;
	पूर्ण अन्यथा अणु
		containers[TILFMT_PAGE] = omap_dmm->tcm[0];
	पूर्ण

	area = (काष्ठा tcm_area) अणु
		.tcm = शून्य,
		.p1.x = omap_dmm->container_width - 1,
		.p1.y = omap_dmm->container_height - 1,
	पूर्ण;

	ret = request_irq(omap_dmm->irq, omap_dmm_irq_handler, IRQF_SHARED,
				"omap_dmm_irq_handler", omap_dmm);

	अगर (ret) अणु
		dev_err(&dev->dev, "couldn't register IRQ %d, error %d\n",
			omap_dmm->irq, ret);
		omap_dmm->irq = -1;
		जाओ fail;
	पूर्ण

	/* Enable all पूर्णांकerrupts क्रम each refill engine except
	 * ERR_LUT_MISS<n> (which is just advisory, and we करोn't care
	 * about because we want to be able to refill live scanout
	 * buffers क्रम accelerated pan/scroll) and FILL_DSC<n> which
	 * we just generally करोn't care about.
	 */
	dmm_ग_लिखो(omap_dmm, 0x7e7e7e7e, DMM_PAT_IRQENABLE_SET);

	/* initialize all LUTs to dummy page entries */
	क्रम (i = 0; i < omap_dmm->num_lut; i++) अणु
		area.tcm = omap_dmm->tcm[i];
		अगर (fill(&area, शून्य, 0, 0, true))
			dev_err(omap_dmm->dev, "refill failed");
	पूर्ण

	dev_info(omap_dmm->dev, "initialized all PAT entries\n");

	वापस 0;

fail:
	अगर (omap_dmm_हटाओ(dev))
		dev_err(&dev->dev, "cleanup failed\n");
	वापस ret;
पूर्ण

/*
 * debugfs support
 */

#अगर_घोषित CONFIG_DEBUG_FS

अटल स्थिर अक्षर *alphabet = "abcdefghijklmnopqrstuvwxyz"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
अटल स्थिर अक्षर *special = ".,:;'\"`~!^-+";

अटल व्योम fill_map(अक्षर **map, पूर्णांक xभाग, पूर्णांक yभाग, काष्ठा tcm_area *a,
							अक्षर c, bool ovw)
अणु
	पूर्णांक x, y;
	क्रम (y = a->p0.y / yभाग; y <= a->p1.y / yभाग; y++)
		क्रम (x = a->p0.x / xभाग; x <= a->p1.x / xभाग; x++)
			अगर (map[y][x] == ' ' || ovw)
				map[y][x] = c;
पूर्ण

अटल व्योम fill_map_pt(अक्षर **map, पूर्णांक xभाग, पूर्णांक yभाग, काष्ठा tcm_pt *p,
									अक्षर c)
अणु
	map[p->y / yभाग][p->x / xभाग] = c;
पूर्ण

अटल अक्षर पढ़ो_map_pt(अक्षर **map, पूर्णांक xभाग, पूर्णांक yभाग, काष्ठा tcm_pt *p)
अणु
	वापस map[p->y / yभाग][p->x / xभाग];
पूर्ण

अटल पूर्णांक map_width(पूर्णांक xभाग, पूर्णांक x0, पूर्णांक x1)
अणु
	वापस (x1 / xभाग) - (x0 / xभाग) + 1;
पूर्ण

अटल व्योम text_map(अक्षर **map, पूर्णांक xभाग, अक्षर *nice, पूर्णांक yd, पूर्णांक x0, पूर्णांक x1)
अणु
	अक्षर *p = map[yd] + (x0 / xभाग);
	पूर्णांक w = (map_width(xभाग, x0, x1) - म_माप(nice)) / 2;
	अगर (w >= 0) अणु
		p += w;
		जबतक (*nice)
			*p++ = *nice++;
	पूर्ण
पूर्ण

अटल व्योम map_1d_info(अक्षर **map, पूर्णांक xभाग, पूर्णांक yभाग, अक्षर *nice,
							काष्ठा tcm_area *a)
अणु
	प्र_लिखो(nice, "%dK", tcm_माप(*a) * 4);
	अगर (a->p0.y + 1 < a->p1.y) अणु
		text_map(map, xभाग, nice, (a->p0.y + a->p1.y) / 2 / yभाग, 0,
							256 - 1);
	पूर्ण अन्यथा अगर (a->p0.y < a->p1.y) अणु
		अगर (म_माप(nice) < map_width(xभाग, a->p0.x, 256 - 1))
			text_map(map, xभाग, nice, a->p0.y / yभाग,
					a->p0.x + xभाग,	256 - 1);
		अन्यथा अगर (म_माप(nice) < map_width(xभाग, 0, a->p1.x))
			text_map(map, xभाग, nice, a->p1.y / yभाग,
					0, a->p1.y - xभाग);
	पूर्ण अन्यथा अगर (म_माप(nice) + 1 < map_width(xभाग, a->p0.x, a->p1.x)) अणु
		text_map(map, xभाग, nice, a->p0.y / yभाग, a->p0.x, a->p1.x);
	पूर्ण
पूर्ण

अटल व्योम map_2d_info(अक्षर **map, पूर्णांक xभाग, पूर्णांक yभाग, अक्षर *nice,
							काष्ठा tcm_area *a)
अणु
	प्र_लिखो(nice, "(%d*%d)", tcm_awidth(*a), tcm_aheight(*a));
	अगर (म_माप(nice) + 1 < map_width(xभाग, a->p0.x, a->p1.x))
		text_map(map, xभाग, nice, (a->p0.y + a->p1.y) / 2 / yभाग,
							a->p0.x, a->p1.x);
पूर्ण

पूर्णांक tiler_map_show(काष्ठा seq_file *s, व्योम *arg)
अणु
	पूर्णांक xभाग = 2, yभाग = 1;
	अक्षर **map = शून्य, *global_map;
	काष्ठा tiler_block *block;
	काष्ठा tcm_area a, p;
	पूर्णांक i;
	स्थिर अक्षर *m2d = alphabet;
	स्थिर अक्षर *a2d = special;
	स्थिर अक्षर *m2dp = m2d, *a2dp = a2d;
	अक्षर nice[128];
	पूर्णांक h_adj;
	पूर्णांक w_adj;
	अचिन्हित दीर्घ flags;
	पूर्णांक lut_idx;


	अगर (!omap_dmm) अणु
		/* early वापस अगर dmm/tiler device is not initialized */
		वापस 0;
	पूर्ण

	h_adj = omap_dmm->container_height / yभाग;
	w_adj = omap_dmm->container_width / xभाग;

	map = kदो_स्मृति_array(h_adj, माप(*map), GFP_KERNEL);
	global_map = kदो_स्मृति_array(w_adj + 1, h_adj, GFP_KERNEL);

	अगर (!map || !global_map)
		जाओ error;

	क्रम (lut_idx = 0; lut_idx < omap_dmm->num_lut; lut_idx++) अणु
		स_रखो(map, 0, h_adj * माप(*map));
		स_रखो(global_map, ' ', (w_adj + 1) * h_adj);

		क्रम (i = 0; i < omap_dmm->container_height; i++) अणु
			map[i] = global_map + i * (w_adj + 1);
			map[i][w_adj] = 0;
		पूर्ण

		spin_lock_irqsave(&list_lock, flags);

		list_क्रम_each_entry(block, &omap_dmm->alloc_head, alloc_node) अणु
			अगर (block->area.tcm == omap_dmm->tcm[lut_idx]) अणु
				अगर (block->fmt != TILFMT_PAGE) अणु
					fill_map(map, xभाग, yभाग, &block->area,
						*m2dp, true);
					अगर (!*++a2dp)
						a2dp = a2d;
					अगर (!*++m2dp)
						m2dp = m2d;
					map_2d_info(map, xभाग, yभाग, nice,
							&block->area);
				पूर्ण अन्यथा अणु
					bool start = पढ़ो_map_pt(map, xभाग,
						yभाग, &block->area.p0) == ' ';
					bool end = पढ़ो_map_pt(map, xभाग, yभाग,
							&block->area.p1) == ' ';

					tcm_क्रम_each_slice(a, block->area, p)
						fill_map(map, xभाग, yभाग, &a,
							'=', true);
					fill_map_pt(map, xभाग, yभाग,
							&block->area.p0,
							start ? '<' : 'X');
					fill_map_pt(map, xभाग, yभाग,
							&block->area.p1,
							end ? '>' : 'X');
					map_1d_info(map, xभाग, yभाग, nice,
							&block->area);
				पूर्ण
			पूर्ण
		पूर्ण

		spin_unlock_irqrestore(&list_lock, flags);

		अगर (s) अणु
			seq_म_लिखो(s, "CONTAINER %d DUMP BEGIN\n", lut_idx);
			क्रम (i = 0; i < 128; i++)
				seq_म_लिखो(s, "%03d:%s\n", i, map[i]);
			seq_म_लिखो(s, "CONTAINER %d DUMP END\n", lut_idx);
		पूर्ण अन्यथा अणु
			dev_dbg(omap_dmm->dev, "CONTAINER %d DUMP BEGIN\n",
				lut_idx);
			क्रम (i = 0; i < 128; i++)
				dev_dbg(omap_dmm->dev, "%03d:%s\n", i, map[i]);
			dev_dbg(omap_dmm->dev, "CONTAINER %d DUMP END\n",
				lut_idx);
		पूर्ण
	पूर्ण

error:
	kमुक्त(map);
	kमुक्त(global_map);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक omap_dmm_resume(काष्ठा device *dev)
अणु
	काष्ठा tcm_area area;
	पूर्णांक i;

	अगर (!omap_dmm)
		वापस -ENODEV;

	area = (काष्ठा tcm_area) अणु
		.tcm = शून्य,
		.p1.x = omap_dmm->container_width - 1,
		.p1.y = omap_dmm->container_height - 1,
	पूर्ण;

	/* initialize all LUTs to dummy page entries */
	क्रम (i = 0; i < omap_dmm->num_lut; i++) अणु
		area.tcm = omap_dmm->tcm[i];
		अगर (fill(&area, शून्य, 0, 0, true))
			dev_err(dev, "refill failed");
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(omap_dmm_pm_ops, शून्य, omap_dmm_resume);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा dmm_platक्रमm_data dmm_omap4_platक्रमm_data = अणु
	.cpu_cache_flags = OMAP_BO_WC,
पूर्ण;

अटल स्थिर काष्ठा dmm_platक्रमm_data dmm_omap5_platक्रमm_data = अणु
	.cpu_cache_flags = OMAP_BO_UNCACHED,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dmm_of_match[] = अणु
	अणु
		.compatible = "ti,omap4-dmm",
		.data = &dmm_omap4_platक्रमm_data,
	पूर्ण,
	अणु
		.compatible = "ti,omap5-dmm",
		.data = &dmm_omap5_platक्रमm_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

काष्ठा platक्रमm_driver omap_dmm_driver = अणु
	.probe = omap_dmm_probe,
	.हटाओ = omap_dmm_हटाओ,
	.driver = अणु
		.owner = THIS_MODULE,
		.name = DMM_DRIVER_NAME,
		.of_match_table = of_match_ptr(dmm_of_match),
		.pm = &omap_dmm_pm_ops,
	पूर्ण,
पूर्ण;

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Andy Gross <andy.gross@ti.com>");
MODULE_DESCRIPTION("OMAP DMM/Tiler Driver");
