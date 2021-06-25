<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fs.h>
#समावेश <linux/rwsem.h>
#समावेश "kpc_dma_driver.h"

/**********  IRQ Handlers  **********/
अटल
irqवापस_t  ndd_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा kpc_dma_device *ldev = (काष्ठा kpc_dma_device *)dev_id;

	अगर ((GetEngineControl(ldev) & ENG_CTL_IRQ_ACTIVE) ||
	    (ldev->desc_completed->MyDMAAddr != GetEngineCompletePtr(ldev)))
		schedule_work(&ldev->irq_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल
व्योम  ndd_irq_worker(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा kpc_dma_descriptor *cur;
	काष्ठा kpc_dma_device *eng = container_of(ws, काष्ठा kpc_dma_device, irq_work);

	lock_engine(eng);

	अगर (GetEngineCompletePtr(eng) == 0)
		जाओ out;

	अगर (eng->desc_completed->MyDMAAddr == GetEngineCompletePtr(eng))
		जाओ out;

	cur = eng->desc_completed;
	करो अणु
		cur = cur->Next;
		dev_dbg(&eng->pldev->dev, "Handling completed descriptor %p (acd = %p)\n",
			cur, cur->acd);
		BUG_ON(cur == eng->desc_next); // Ordering failure.

		अगर (cur->DescControlFlags & DMA_DESC_CTL_SOP) अणु
			eng->accumulated_bytes = 0;
			eng->accumulated_flags = 0;
		पूर्ण

		eng->accumulated_bytes += cur->DescByteCount;
		अगर (cur->DescStatusFlags & DMA_DESC_STS_ERROR)
			eng->accumulated_flags |= ACD_FLAG_ENG_ACCUM_ERROR;

		अगर (cur->DescStatusFlags & DMA_DESC_STS_SHORT)
			eng->accumulated_flags |= ACD_FLAG_ENG_ACCUM_SHORT;

		अगर (cur->DescControlFlags & DMA_DESC_CTL_EOP) अणु
			अगर (cur->acd)
				transfer_complete_cb(cur->acd, eng->accumulated_bytes,
						     eng->accumulated_flags | ACD_FLAG_DONE);
		पूर्ण

		eng->desc_completed = cur;
	पूर्ण जबतक (cur->MyDMAAddr != GetEngineCompletePtr(eng));

 out:
	SetClearEngineControl(eng, ENG_CTL_IRQ_ACTIVE, 0);

	unlock_engine(eng);
पूर्ण

/**********  DMA Engine Init/Tearकरोwn  **********/
व्योम  start_dma_engine(काष्ठा kpc_dma_device *eng)
अणु
	eng->desc_next       = eng->desc_pool_first;
	eng->desc_completed  = eng->desc_pool_last;

	// Setup the engine poपूर्णांकer रेजिस्टरs
	SetEngineNextPtr(eng, eng->desc_pool_first);
	SetEngineSWPtr(eng, eng->desc_pool_first);
	ClearEngineCompletePtr(eng);

	WriteEngineControl(eng, ENG_CTL_DMA_ENABLE | ENG_CTL_IRQ_ENABLE);
पूर्ण

पूर्णांक  setup_dma_engine(काष्ठा kpc_dma_device *eng, u32 desc_cnt)
अणु
	u32 caps;
	काष्ठा kpc_dma_descriptor *cur;
	काष्ठा kpc_dma_descriptor *next;
	dma_addr_t next_handle;
	dma_addr_t head_handle;
	अचिन्हित पूर्णांक i;
	पूर्णांक rv;

	caps = GetEngineCapabilities(eng);

	अगर (WARN(!(caps & ENG_CAP_PRESENT), "%s() called for DMA Engine at %p which isn't present in hardware!\n", __func__, eng))
		वापस -ENXIO;

	अगर (caps & ENG_CAP_सूचीECTION)
		eng->dir = DMA_FROM_DEVICE;
	अन्यथा
		eng->dir = DMA_TO_DEVICE;

	eng->desc_pool_cnt = desc_cnt;
	eng->desc_pool = dma_pool_create("KPC DMA Descriptors", &eng->pldev->dev,
					 माप(काष्ठा kpc_dma_descriptor),
					 DMA_DESC_ALIGNMENT, 4096);

	eng->desc_pool_first = dma_pool_alloc(eng->desc_pool, GFP_KERNEL | GFP_DMA, &head_handle);
	अगर (!eng->desc_pool_first) अणु
		dev_err(&eng->pldev->dev, "%s: couldn't allocate desc_pool_first!\n", __func__);
		dma_pool_destroy(eng->desc_pool);
		वापस -ENOMEM;
	पूर्ण

	eng->desc_pool_first->MyDMAAddr = head_handle;
	clear_desc(eng->desc_pool_first);

	cur = eng->desc_pool_first;
	क्रम (i = 1 ; i < eng->desc_pool_cnt ; i++) अणु
		next = dma_pool_alloc(eng->desc_pool, GFP_KERNEL | GFP_DMA, &next_handle);
		अगर (!next)
			जाओ करोne_alloc;

		clear_desc(next);
		next->MyDMAAddr = next_handle;

		cur->DescNextDescPtr = next_handle;
		cur->Next = next;
		cur = next;
	पूर्ण

 करोne_alloc:
	// Link the last descriptor back to the first, so it's a circular linked list
	cur->Next = eng->desc_pool_first;
	cur->DescNextDescPtr = eng->desc_pool_first->MyDMAAddr;

	eng->desc_pool_last = cur;
	eng->desc_completed = eng->desc_pool_last;

	// Setup work queue
	INIT_WORK(&eng->irq_work, ndd_irq_worker);

	// Grab IRQ line
	rv = request_irq(eng->irq, ndd_irq_handler, IRQF_SHARED,
			 KP_DRIVER_NAME_DMA_CONTROLLER, eng);
	अगर (rv) अणु
		dev_err(&eng->pldev->dev, "%s: failed to request_irq: %d\n", __func__, rv);
		वापस rv;
	पूर्ण

	// Turn on the engine!
	start_dma_engine(eng);
	unlock_engine(eng);

	वापस 0;
पूर्ण

व्योम  stop_dma_engine(काष्ठा kpc_dma_device *eng)
अणु
	अचिन्हित दीर्घ समयout;

	// Disable the descriptor engine
	WriteEngineControl(eng, 0);

	// Wait क्रम descriptor engine to finish current operaion
	समयout = jअगरfies + (HZ / 2);
	जबतक (GetEngineControl(eng) & ENG_CTL_DMA_RUNNING) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_crit(&eng->pldev->dev, "DMA_RUNNING still asserted!\n");
			अवरोध;
		पूर्ण
	पूर्ण

	// Request a reset
	WriteEngineControl(eng, ENG_CTL_DMA_RESET_REQUEST);

	// Wait क्रम reset request to be processed
	समयout = jअगरfies + (HZ / 2);
	जबतक (GetEngineControl(eng) & (ENG_CTL_DMA_RUNNING | ENG_CTL_DMA_RESET_REQUEST)) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_crit(&eng->pldev->dev, "ENG_CTL_DMA_RESET_REQUEST still asserted!\n");
			अवरोध;
		पूर्ण
	पूर्ण

	// Request a reset
	WriteEngineControl(eng, ENG_CTL_DMA_RESET);

	// And रुको क्रम reset to complete
	समयout = jअगरfies + (HZ / 2);
	जबतक (GetEngineControl(eng) & ENG_CTL_DMA_RESET) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_crit(&eng->pldev->dev, "DMA_RESET still asserted!\n");
			अवरोध;
		पूर्ण
	पूर्ण

	// Clear any persistent bits just to make sure there is no residue from the reset
	SetClearEngineControl(eng, (ENG_CTL_IRQ_ACTIVE | ENG_CTL_DESC_COMPLETE |
				    ENG_CTL_DESC_ALIGN_ERR | ENG_CTL_DESC_FETCH_ERR |
				    ENG_CTL_SW_ABORT_ERR | ENG_CTL_DESC_CHAIN_END |
				    ENG_CTL_DMA_WAITING_PERSIST), 0);

	// Reset perक्रमmance counters

	// Completely disable the engine
	WriteEngineControl(eng, 0);
पूर्ण

व्योम  destroy_dma_engine(काष्ठा kpc_dma_device *eng)
अणु
	काष्ठा kpc_dma_descriptor *cur;
	dma_addr_t cur_handle;
	अचिन्हित पूर्णांक i;

	stop_dma_engine(eng);

	cur = eng->desc_pool_first;
	cur_handle = eng->desc_pool_first->MyDMAAddr;

	क्रम (i = 0 ; i < eng->desc_pool_cnt ; i++) अणु
		काष्ठा kpc_dma_descriptor *next = cur->Next;
		dma_addr_t next_handle = cur->DescNextDescPtr;

		dma_pool_मुक्त(eng->desc_pool, cur, cur_handle);
		cur_handle = next_handle;
		cur = next;
	पूर्ण

	dma_pool_destroy(eng->desc_pool);

	मुक्त_irq(eng->irq, eng);
पूर्ण

/**********  Helper Functions  **********/
पूर्णांक  count_descriptors_available(काष्ठा kpc_dma_device *eng)
अणु
	u32 count = 0;
	काष्ठा kpc_dma_descriptor *cur = eng->desc_next;

	जबतक (cur != eng->desc_completed) अणु
		BUG_ON(!cur);
		count++;
		cur = cur->Next;
	पूर्ण
	वापस count;
पूर्ण

व्योम  clear_desc(काष्ठा kpc_dma_descriptor *desc)
अणु
	अगर (!desc)
		वापस;
	desc->DescByteCount         = 0;
	desc->DescStatusErrorFlags  = 0;
	desc->DescStatusFlags       = 0;
	desc->DescUserControlLS     = 0;
	desc->DescUserControlMS     = 0;
	desc->DescCardAddrLS        = 0;
	desc->DescBufferByteCount   = 0;
	desc->DescCardAddrMS        = 0;
	desc->DescControlFlags      = 0;
	desc->DescSystemAddrLS      = 0;
	desc->DescSystemAddrMS      = 0;
	desc->acd = शून्य;
पूर्ण
