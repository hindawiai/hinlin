<शैली गुरु>
/* via_dmablit.c -- PCI DMA BitBlt support क्रम the VIA Unichrome/Pro
 *
 * Copyright (C) 2005 Thomas Hellstrom, All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Thomas Hellstrom.
 *    Partially based on code obtained from Digeo Inc.
 */


/*
 * Unmaps the DMA mappings.
 * FIXME: Is this a NoOp on x86? Also
 * FIXME: What happens अगर this one is called and a pending blit has previously करोne
 * the same DMA mappings?
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/via_drm.h>

#समावेश "via_dmablit.h"
#समावेश "via_drv.h"

#घोषणा VIA_PGDN(x)	     (((अचिन्हित दीर्घ)(x)) & PAGE_MASK)
#घोषणा VIA_PGOFF(x)	    (((अचिन्हित दीर्घ)(x)) & ~PAGE_MASK)
#घोषणा VIA_PFN(x)	      ((अचिन्हित दीर्घ)(x) >> PAGE_SHIFT)

प्रकार काष्ठा _drm_via_descriptor अणु
	uपूर्णांक32_t mem_addr;
	uपूर्णांक32_t dev_addr;
	uपूर्णांक32_t size;
	uपूर्णांक32_t next;
पूर्ण drm_via_descriptor_t;


/*
 * Unmap a DMA mapping.
 */



अटल व्योम
via_unmap_blit_from_device(काष्ठा pci_dev *pdev, drm_via_sg_info_t *vsg)
अणु
	पूर्णांक num_desc = vsg->num_desc;
	अचिन्हित cur_descriptor_page = num_desc / vsg->descriptors_per_page;
	अचिन्हित descriptor_this_page = num_desc % vsg->descriptors_per_page;
	drm_via_descriptor_t *desc_ptr = vsg->desc_pages[cur_descriptor_page] +
		descriptor_this_page;
	dma_addr_t next = vsg->chain_start;

	जबतक (num_desc--) अणु
		अगर (descriptor_this_page-- == 0) अणु
			cur_descriptor_page--;
			descriptor_this_page = vsg->descriptors_per_page - 1;
			desc_ptr = vsg->desc_pages[cur_descriptor_page] +
				descriptor_this_page;
		पूर्ण
		dma_unmap_single(&pdev->dev, next, माप(*desc_ptr), DMA_TO_DEVICE);
		dma_unmap_page(&pdev->dev, desc_ptr->mem_addr, desc_ptr->size, vsg->direction);
		next = (dma_addr_t) desc_ptr->next;
		desc_ptr--;
	पूर्ण
पूर्ण

/*
 * If mode = 0, count how many descriptors are needed.
 * If mode = 1, Map the DMA pages क्रम the device, put together and map also the descriptors.
 * Descriptors are run in reverse order by the hardware because we are not allowed to update the
 * 'next' field without syncing calls when the descriptor is alपढ़ोy mapped.
 */

अटल व्योम
via_map_blit_क्रम_device(काष्ठा pci_dev *pdev,
		   स्थिर drm_via_dmablit_t *xfer,
		   drm_via_sg_info_t *vsg,
		   पूर्णांक mode)
अणु
	अचिन्हित cur_descriptor_page = 0;
	अचिन्हित num_descriptors_this_page = 0;
	अचिन्हित अक्षर *mem_addr = xfer->mem_addr;
	अचिन्हित अक्षर *cur_mem;
	अचिन्हित अक्षर *first_addr = (अचिन्हित अक्षर *)VIA_PGDN(mem_addr);
	uपूर्णांक32_t fb_addr = xfer->fb_addr;
	uपूर्णांक32_t cur_fb;
	अचिन्हित दीर्घ line_len;
	अचिन्हित reमुख्यing_len;
	पूर्णांक num_desc = 0;
	पूर्णांक cur_line;
	dma_addr_t next = 0 | VIA_DMA_DPR_EC;
	drm_via_descriptor_t *desc_ptr = शून्य;

	अगर (mode == 1)
		desc_ptr = vsg->desc_pages[cur_descriptor_page];

	क्रम (cur_line = 0; cur_line < xfer->num_lines; ++cur_line) अणु

		line_len = xfer->line_length;
		cur_fb = fb_addr;
		cur_mem = mem_addr;

		जबतक (line_len > 0) अणु

			reमुख्यing_len = min(PAGE_SIZE-VIA_PGOFF(cur_mem), line_len);
			line_len -= reमुख्यing_len;

			अगर (mode == 1) अणु
				desc_ptr->mem_addr =
					dma_map_page(&pdev->dev,
						     vsg->pages[VIA_PFN(cur_mem) -
								VIA_PFN(first_addr)],
						     VIA_PGOFF(cur_mem), reमुख्यing_len,
						     vsg->direction);
				desc_ptr->dev_addr = cur_fb;

				desc_ptr->size = reमुख्यing_len;
				desc_ptr->next = (uपूर्णांक32_t) next;
				next = dma_map_single(&pdev->dev, desc_ptr, माप(*desc_ptr),
						      DMA_TO_DEVICE);
				desc_ptr++;
				अगर (++num_descriptors_this_page >= vsg->descriptors_per_page) अणु
					num_descriptors_this_page = 0;
					desc_ptr = vsg->desc_pages[++cur_descriptor_page];
				पूर्ण
			पूर्ण

			num_desc++;
			cur_mem += reमुख्यing_len;
			cur_fb += reमुख्यing_len;
		पूर्ण

		mem_addr += xfer->mem_stride;
		fb_addr += xfer->fb_stride;
	पूर्ण

	अगर (mode == 1) अणु
		vsg->chain_start = next;
		vsg->state = dr_via_device_mapped;
	पूर्ण
	vsg->num_desc = num_desc;
पूर्ण

/*
 * Function that मुक्तs up all resources क्रम a blit. It is usable even अगर the
 * blit info has only been partially built as दीर्घ as the status क्रमागत is consistent
 * with the actual status of the used resources.
 */


अटल व्योम
via_मुक्त_sg_info(काष्ठा pci_dev *pdev, drm_via_sg_info_t *vsg)
अणु
	पूर्णांक i;

	चयन (vsg->state) अणु
	हाल dr_via_device_mapped:
		via_unmap_blit_from_device(pdev, vsg);
		fallthrough;
	हाल dr_via_desc_pages_alloc:
		क्रम (i = 0; i < vsg->num_desc_pages; ++i) अणु
			अगर (vsg->desc_pages[i] != शून्य)
				मुक्त_page((अचिन्हित दीर्घ)vsg->desc_pages[i]);
		पूर्ण
		kमुक्त(vsg->desc_pages);
		fallthrough;
	हाल dr_via_pages_locked:
		unpin_user_pages_dirty_lock(vsg->pages, vsg->num_pages,
					   (vsg->direction == DMA_FROM_DEVICE));
		fallthrough;
	हाल dr_via_pages_alloc:
		vमुक्त(vsg->pages);
		fallthrough;
	शेष:
		vsg->state = dr_via_sg_init;
	पूर्ण
	vमुक्त(vsg->bounce_buffer);
	vsg->bounce_buffer = शून्य;
	vsg->मुक्त_on_sequence = 0;
पूर्ण

/*
 * Fire a blit engine.
 */

अटल व्योम
via_fire_dmablit(काष्ठा drm_device *dev, drm_via_sg_info_t *vsg, पूर्णांक engine)
अणु
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *)dev->dev_निजी;

	via_ग_लिखो(dev_priv, VIA_PCI_DMA_MAR0 + engine*0x10, 0);
	via_ग_लिखो(dev_priv, VIA_PCI_DMA_DAR0 + engine*0x10, 0);
	via_ग_लिखो(dev_priv, VIA_PCI_DMA_CSR0 + engine*0x04, VIA_DMA_CSR_DD | VIA_DMA_CSR_TD |
		  VIA_DMA_CSR_DE);
	via_ग_लिखो(dev_priv, VIA_PCI_DMA_MR0  + engine*0x04, VIA_DMA_MR_CM | VIA_DMA_MR_TDIE);
	via_ग_लिखो(dev_priv, VIA_PCI_DMA_BCR0 + engine*0x10, 0);
	via_ग_लिखो(dev_priv, VIA_PCI_DMA_DPR0 + engine*0x10, vsg->chain_start);
	wmb();
	via_ग_लिखो(dev_priv, VIA_PCI_DMA_CSR0 + engine*0x04, VIA_DMA_CSR_DE | VIA_DMA_CSR_TS);
	via_पढ़ो(dev_priv, VIA_PCI_DMA_CSR0 + engine*0x04);
पूर्ण

/*
 * Obtain a page poपूर्णांकer array and lock all pages पूर्णांकo प्रणाली memory. A segmentation violation will
 * occur here अगर the calling user करोes not have access to the submitted address.
 */

अटल पूर्णांक
via_lock_all_dma_pages(drm_via_sg_info_t *vsg,  drm_via_dmablit_t *xfer)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ first_pfn = VIA_PFN(xfer->mem_addr);
	vsg->num_pages = VIA_PFN(xfer->mem_addr + (xfer->num_lines * xfer->mem_stride - 1)) -
		first_pfn + 1;

	vsg->pages = vzalloc(array_size(माप(काष्ठा page *), vsg->num_pages));
	अगर (शून्य == vsg->pages)
		वापस -ENOMEM;
	ret = pin_user_pages_fast((अचिन्हित दीर्घ)xfer->mem_addr,
			vsg->num_pages,
			vsg->direction == DMA_FROM_DEVICE ? FOLL_WRITE : 0,
			vsg->pages);
	अगर (ret != vsg->num_pages) अणु
		अगर (ret < 0)
			वापस ret;
		vsg->state = dr_via_pages_locked;
		वापस -EINVAL;
	पूर्ण
	vsg->state = dr_via_pages_locked;
	DRM_DEBUG("DMA pages locked\n");
	वापस 0;
पूर्ण

/*
 * Allocate DMA capable memory क्रम the blit descriptor chain, and an array that keeps track of the
 * pages we allocate. We करोn't want to use kदो_स्मृति क्रम the descriptor chain because it may be
 * quite large क्रम some blits, and pages करोn't need to be contiguous.
 */

अटल पूर्णांक
via_alloc_desc_pages(drm_via_sg_info_t *vsg)
अणु
	पूर्णांक i;

	vsg->descriptors_per_page = PAGE_SIZE / माप(drm_via_descriptor_t);
	vsg->num_desc_pages = (vsg->num_desc + vsg->descriptors_per_page - 1) /
		vsg->descriptors_per_page;

	अगर (शून्य ==  (vsg->desc_pages = kसुस्मृति(vsg->num_desc_pages, माप(व्योम *), GFP_KERNEL)))
		वापस -ENOMEM;

	vsg->state = dr_via_desc_pages_alloc;
	क्रम (i = 0; i < vsg->num_desc_pages; ++i) अणु
		अगर (शून्य == (vsg->desc_pages[i] =
			     (drm_via_descriptor_t *) __get_मुक्त_page(GFP_KERNEL)))
			वापस -ENOMEM;
	पूर्ण
	DRM_DEBUG("Allocated %d pages for %d descriptors.\n", vsg->num_desc_pages,
		  vsg->num_desc);
	वापस 0;
पूर्ण

अटल व्योम
via_पात_dmablit(काष्ठा drm_device *dev, पूर्णांक engine)
अणु
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *)dev->dev_निजी;

	via_ग_लिखो(dev_priv, VIA_PCI_DMA_CSR0 + engine*0x04, VIA_DMA_CSR_TA);
पूर्ण

अटल व्योम
via_dmablit_engine_off(काष्ठा drm_device *dev, पूर्णांक engine)
अणु
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *)dev->dev_निजी;

	via_ग_लिखो(dev_priv, VIA_PCI_DMA_CSR0 + engine*0x04, VIA_DMA_CSR_TD | VIA_DMA_CSR_DD);
पूर्ण



/*
 * The dmablit part of the IRQ handler. Trying to करो only reasonably fast things here.
 * The rest, like unmapping and मुक्तing memory क्रम करोne blits is करोne in a separate workqueue
 * task. Basically the task of the पूर्णांकerrupt handler is to submit a new blit to the engine, जबतक
 * the workqueue task takes care of processing associated with the old blit.
 */

व्योम
via_dmablit_handler(काष्ठा drm_device *dev, पूर्णांक engine, पूर्णांक from_irq)
अणु
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *)dev->dev_निजी;
	drm_via_blitq_t *blitq = dev_priv->blit_queues + engine;
	पूर्णांक cur;
	पूर्णांक करोne_transfer;
	अचिन्हित दीर्घ irqsave = 0;
	uपूर्णांक32_t status = 0;

	DRM_DEBUG("DMA blit handler called. engine = %d, from_irq = %d, blitq = 0x%lx\n",
		  engine, from_irq, (अचिन्हित दीर्घ) blitq);

	अगर (from_irq)
		spin_lock(&blitq->blit_lock);
	अन्यथा
		spin_lock_irqsave(&blitq->blit_lock, irqsave);

	करोne_transfer = blitq->is_active &&
	  ((status = via_पढ़ो(dev_priv, VIA_PCI_DMA_CSR0 + engine*0x04)) & VIA_DMA_CSR_TD);
	करोne_transfer = करोne_transfer || (blitq->पातing && !(status & VIA_DMA_CSR_DE));

	cur = blitq->cur;
	अगर (करोne_transfer) अणु

		blitq->blits[cur]->पातed = blitq->पातing;
		blitq->करोne_blit_handle++;
		wake_up(blitq->blit_queue + cur);

		cur++;
		अगर (cur >= VIA_NUM_BLIT_SLOTS)
			cur = 0;
		blitq->cur = cur;

		/*
		 * Clear transfer करोne flag.
		 */

		via_ग_लिखो(dev_priv, VIA_PCI_DMA_CSR0 + engine*0x04,  VIA_DMA_CSR_TD);

		blitq->is_active = 0;
		blitq->पातing = 0;
		schedule_work(&blitq->wq);

	पूर्ण अन्यथा अगर (blitq->is_active && समय_after_eq(jअगरfies, blitq->end)) अणु

		/*
		 * Abort transfer after one second.
		 */

		via_पात_dmablit(dev, engine);
		blitq->पातing = 1;
		blitq->end = jअगरfies + HZ;
	पूर्ण

	अगर (!blitq->is_active) अणु
		अगर (blitq->num_outstanding) अणु
			via_fire_dmablit(dev, blitq->blits[cur], engine);
			blitq->is_active = 1;
			blitq->cur = cur;
			blitq->num_outstanding--;
			blitq->end = jअगरfies + HZ;
			अगर (!समयr_pending(&blitq->poll_समयr))
				mod_समयr(&blitq->poll_समयr, jअगरfies + 1);
		पूर्ण अन्यथा अणु
			अगर (समयr_pending(&blitq->poll_समयr))
				del_समयr(&blitq->poll_समयr);
			via_dmablit_engine_off(dev, engine);
		पूर्ण
	पूर्ण

	अगर (from_irq)
		spin_unlock(&blitq->blit_lock);
	अन्यथा
		spin_unlock_irqrestore(&blitq->blit_lock, irqsave);
पूर्ण



/*
 * Check whether this blit is still active, perक्रमming necessary locking.
 */

अटल पूर्णांक
via_dmablit_active(drm_via_blitq_t *blitq, पूर्णांक engine, uपूर्णांक32_t handle, रुको_queue_head_t **queue)
अणु
	अचिन्हित दीर्घ irqsave;
	uपूर्णांक32_t slot;
	पूर्णांक active;

	spin_lock_irqsave(&blitq->blit_lock, irqsave);

	/*
	 * Allow क्रम handle wraparounds.
	 */

	active = ((blitq->करोne_blit_handle - handle) > (1 << 23)) &&
		((blitq->cur_blit_handle - handle) <= (1 << 23));

	अगर (queue && active) अणु
		slot = handle - blitq->करोne_blit_handle + blitq->cur - 1;
		अगर (slot >= VIA_NUM_BLIT_SLOTS)
			slot -= VIA_NUM_BLIT_SLOTS;
		*queue = blitq->blit_queue + slot;
	पूर्ण

	spin_unlock_irqrestore(&blitq->blit_lock, irqsave);

	वापस active;
पूर्ण

/*
 * Sync. Wait क्रम at least three seconds क्रम the blit to be perक्रमmed.
 */

अटल पूर्णांक
via_dmablit_sync(काष्ठा drm_device *dev, uपूर्णांक32_t handle, पूर्णांक engine)
अणु

	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *)dev->dev_निजी;
	drm_via_blitq_t *blitq = dev_priv->blit_queues + engine;
	रुको_queue_head_t *queue;
	पूर्णांक ret = 0;

	अगर (via_dmablit_active(blitq, engine, handle, &queue)) अणु
		VIA_WAIT_ON(ret, *queue, 3 * HZ,
			    !via_dmablit_active(blitq, engine, handle, शून्य));
	पूर्ण
	DRM_DEBUG("DMA blit sync handle 0x%x engine %d returned %d\n",
		  handle, engine, ret);

	वापस ret;
पूर्ण


/*
 * A समयr that regularly polls the blit engine in हालs where we करोn't have पूर्णांकerrupts:
 * a) Broken hardware (typically those that करोn't have any video capture facility).
 * b) Blit पात. The hardware करोesn't send an पूर्णांकerrupt when a blit is पातed.
 * The समयr and hardware IRQ's can and करो work in parallel. If the hardware has
 * irqs, it will लघुen the latency somewhat.
 */



अटल व्योम
via_dmablit_समयr(काष्ठा समयr_list *t)
अणु
	drm_via_blitq_t *blitq = from_समयr(blitq, t, poll_समयr);
	काष्ठा drm_device *dev = blitq->dev;
	पूर्णांक engine = (पूर्णांक)
		(blitq - ((drm_via_निजी_t *)dev->dev_निजी)->blit_queues);

	DRM_DEBUG("Polling timer called for engine %d, jiffies %lu\n", engine,
		  (अचिन्हित दीर्घ) jअगरfies);

	via_dmablit_handler(dev, engine, 0);

	अगर (!समयr_pending(&blitq->poll_समयr)) अणु
		mod_समयr(&blitq->poll_समयr, jअगरfies + 1);

	       /*
		* Rerun handler to delete समयr अगर engines are off, and
		* to लघुen पात latency. This is a little nasty.
		*/

	       via_dmablit_handler(dev, engine, 0);

	पूर्ण
पूर्ण




/*
 * Workqueue task that मुक्तs data and mappings associated with a blit.
 * Also wakes up रुकोing processes. Each of these tasks handles one
 * blit engine only and may not be called on each पूर्णांकerrupt.
 */


अटल व्योम
via_dmablit_workqueue(काष्ठा work_काष्ठा *work)
अणु
	drm_via_blitq_t *blitq = container_of(work, drm_via_blitq_t, wq);
	काष्ठा drm_device *dev = blitq->dev;
	अचिन्हित दीर्घ irqsave;
	drm_via_sg_info_t *cur_sg;
	पूर्णांक cur_released;


	DRM_DEBUG("Workqueue task called for blit engine %ld\n", (अचिन्हित दीर्घ)
		  (blitq - ((drm_via_निजी_t *)dev->dev_निजी)->blit_queues));

	spin_lock_irqsave(&blitq->blit_lock, irqsave);

	जबतक (blitq->serviced != blitq->cur) अणु

		cur_released = blitq->serviced++;

		DRM_DEBUG("Releasing blit slot %d\n", cur_released);

		अगर (blitq->serviced >= VIA_NUM_BLIT_SLOTS)
			blitq->serviced = 0;

		cur_sg = blitq->blits[cur_released];
		blitq->num_मुक्त++;

		spin_unlock_irqrestore(&blitq->blit_lock, irqsave);

		wake_up(&blitq->busy_queue);

		via_मुक्त_sg_info(dev->pdev, cur_sg);
		kमुक्त(cur_sg);

		spin_lock_irqsave(&blitq->blit_lock, irqsave);
	पूर्ण

	spin_unlock_irqrestore(&blitq->blit_lock, irqsave);
पूर्ण


/*
 * Init all blit engines. Currently we use two, but some hardware have 4.
 */


व्योम
via_init_dmablit(काष्ठा drm_device *dev)
अणु
	पूर्णांक i, j;
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *)dev->dev_निजी;
	drm_via_blitq_t *blitq;

	pci_set_master(dev->pdev);

	क्रम (i = 0; i < VIA_NUM_BLIT_ENGINES; ++i) अणु
		blitq = dev_priv->blit_queues + i;
		blitq->dev = dev;
		blitq->cur_blit_handle = 0;
		blitq->करोne_blit_handle = 0;
		blitq->head = 0;
		blitq->cur = 0;
		blitq->serviced = 0;
		blitq->num_मुक्त = VIA_NUM_BLIT_SLOTS - 1;
		blitq->num_outstanding = 0;
		blitq->is_active = 0;
		blitq->पातing = 0;
		spin_lock_init(&blitq->blit_lock);
		क्रम (j = 0; j < VIA_NUM_BLIT_SLOTS; ++j)
			init_रुकोqueue_head(blitq->blit_queue + j);
		init_रुकोqueue_head(&blitq->busy_queue);
		INIT_WORK(&blitq->wq, via_dmablit_workqueue);
		समयr_setup(&blitq->poll_समयr, via_dmablit_समयr, 0);
	पूर्ण
पूर्ण

/*
 * Build all info and करो all mappings required क्रम a blit.
 */


अटल पूर्णांक
via_build_sg_info(काष्ठा drm_device *dev, drm_via_sg_info_t *vsg, drm_via_dmablit_t *xfer)
अणु
	पूर्णांक draw = xfer->to_fb;
	पूर्णांक ret = 0;

	vsg->direction = (draw) ? DMA_TO_DEVICE : DMA_FROM_DEVICE;
	vsg->bounce_buffer = शून्य;

	vsg->state = dr_via_sg_init;

	अगर (xfer->num_lines <= 0 || xfer->line_length <= 0) अणु
		DRM_ERROR("Zero size bitblt.\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Below check is a driver limitation, not a hardware one. We
	 * करोn't want to lock unused pages, and don't want to incoporate the
	 * extra logic of aव्योमing them. Make sure there are no.
	 * (Not a big limitation anyway.)
	 */

	अगर ((xfer->mem_stride - xfer->line_length) > 2*PAGE_SIZE) अणु
		DRM_ERROR("Too large system memory stride. Stride: %d, "
			  "Length: %d\n", xfer->mem_stride, xfer->line_length);
		वापस -EINVAL;
	पूर्ण

	अगर ((xfer->mem_stride == xfer->line_length) &&
	   (xfer->fb_stride == xfer->line_length)) अणु
		xfer->mem_stride *= xfer->num_lines;
		xfer->line_length = xfer->mem_stride;
		xfer->fb_stride = xfer->mem_stride;
		xfer->num_lines = 1;
	पूर्ण

	/*
	 * Don't lock an arbitrary large number of pages, since that causes a
	 * DOS security hole.
	 */

	अगर (xfer->num_lines > 2048 || (xfer->num_lines*xfer->mem_stride > (2048*2048*4))) अणु
		DRM_ERROR("Too large PCI DMA bitblt.\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * we allow a negative fb stride to allow flipping of images in
	 * transfer.
	 */

	अगर (xfer->mem_stride < xfer->line_length ||
		असल(xfer->fb_stride) < xfer->line_length) अणु
		DRM_ERROR("Invalid frame-buffer / memory stride.\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * A hardware bug seems to be worked around अगर प्रणाली memory addresses start on
	 * 16 byte boundaries. This seems a bit restrictive however. VIA is contacted
	 * about this. Meanजबतक, impose the following restrictions:
	 */

#अगर_घोषित VIA_BUGFREE
	अगर ((((अचिन्हित दीर्घ)xfer->mem_addr & 3) != ((अचिन्हित दीर्घ)xfer->fb_addr & 3)) ||
	    ((xfer->num_lines > 1) && ((xfer->mem_stride & 3) != (xfer->fb_stride & 3)))) अणु
		DRM_ERROR("Invalid DRM bitblt alignment.\n");
		वापस -EINVAL;
	पूर्ण
#अन्यथा
	अगर ((((अचिन्हित दीर्घ)xfer->mem_addr & 15) ||
	      ((अचिन्हित दीर्घ)xfer->fb_addr & 3)) ||
	   ((xfer->num_lines > 1) &&
	   ((xfer->mem_stride & 15) || (xfer->fb_stride & 3)))) अणु
		DRM_ERROR("Invalid DRM bitblt alignment.\n");
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर

	अगर (0 != (ret = via_lock_all_dma_pages(vsg, xfer))) अणु
		DRM_ERROR("Could not lock DMA pages.\n");
		via_मुक्त_sg_info(dev->pdev, vsg);
		वापस ret;
	पूर्ण

	via_map_blit_क्रम_device(dev->pdev, xfer, vsg, 0);
	अगर (0 != (ret = via_alloc_desc_pages(vsg))) अणु
		DRM_ERROR("Could not allocate DMA descriptor pages.\n");
		via_मुक्त_sg_info(dev->pdev, vsg);
		वापस ret;
	पूर्ण
	via_map_blit_क्रम_device(dev->pdev, xfer, vsg, 1);

	वापस 0;
पूर्ण


/*
 * Reserve one मुक्त slot in the blit queue. Will रुको क्रम one second क्रम one
 * to become available. Otherwise -EBUSY is वापसed.
 */

अटल पूर्णांक
via_dmablit_grab_slot(drm_via_blitq_t *blitq, पूर्णांक engine)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ irqsave;

	DRM_DEBUG("Num free is %d\n", blitq->num_मुक्त);
	spin_lock_irqsave(&blitq->blit_lock, irqsave);
	जबतक (blitq->num_मुक्त == 0) अणु
		spin_unlock_irqrestore(&blitq->blit_lock, irqsave);

		VIA_WAIT_ON(ret, blitq->busy_queue, HZ, blitq->num_मुक्त > 0);
		अगर (ret)
			वापस (-EINTR == ret) ? -EAGAIN : ret;

		spin_lock_irqsave(&blitq->blit_lock, irqsave);
	पूर्ण

	blitq->num_मुक्त--;
	spin_unlock_irqrestore(&blitq->blit_lock, irqsave);

	वापस 0;
पूर्ण

/*
 * Hand back a मुक्त slot अगर we changed our mind.
 */

अटल व्योम
via_dmablit_release_slot(drm_via_blitq_t *blitq)
अणु
	अचिन्हित दीर्घ irqsave;

	spin_lock_irqsave(&blitq->blit_lock, irqsave);
	blitq->num_मुक्त++;
	spin_unlock_irqrestore(&blitq->blit_lock, irqsave);
	wake_up(&blitq->busy_queue);
पूर्ण

/*
 * Grab a मुक्त slot. Build blit info and queue a blit.
 */


अटल पूर्णांक
via_dmablit(काष्ठा drm_device *dev, drm_via_dmablit_t *xfer)
अणु
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *)dev->dev_निजी;
	drm_via_sg_info_t *vsg;
	drm_via_blitq_t *blitq;
	पूर्णांक ret;
	पूर्णांक engine;
	अचिन्हित दीर्घ irqsave;

	अगर (dev_priv == शून्य) अणु
		DRM_ERROR("Called without initialization.\n");
		वापस -EINVAL;
	पूर्ण

	engine = (xfer->to_fb) ? 0 : 1;
	blitq = dev_priv->blit_queues + engine;
	अगर (0 != (ret = via_dmablit_grab_slot(blitq, engine)))
		वापस ret;
	अगर (शून्य == (vsg = kदो_स्मृति(माप(*vsg), GFP_KERNEL))) अणु
		via_dmablit_release_slot(blitq);
		वापस -ENOMEM;
	पूर्ण
	अगर (0 != (ret = via_build_sg_info(dev, vsg, xfer))) अणु
		via_dmablit_release_slot(blitq);
		kमुक्त(vsg);
		वापस ret;
	पूर्ण
	spin_lock_irqsave(&blitq->blit_lock, irqsave);

	blitq->blits[blitq->head++] = vsg;
	अगर (blitq->head >= VIA_NUM_BLIT_SLOTS)
		blitq->head = 0;
	blitq->num_outstanding++;
	xfer->sync.sync_handle = ++blitq->cur_blit_handle;

	spin_unlock_irqrestore(&blitq->blit_lock, irqsave);
	xfer->sync.engine = engine;

	via_dmablit_handler(dev, engine, 0);

	वापस 0;
पूर्ण

/*
 * Sync on a previously submitted blit. Note that the X server use संकेतs extensively, and
 * that there is a very big probability that this IOCTL will be पूर्णांकerrupted by a संकेत. In that
 * हाल it वापसs with -EAGAIN क्रम the संकेत to be delivered.
 * The caller should then reissue the IOCTL. This is similar to what is being करोne क्रम drmGetLock().
 */

पूर्णांक
via_dma_blit_sync(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_via_blitsync_t *sync = data;
	पूर्णांक err;

	अगर (sync->engine >= VIA_NUM_BLIT_ENGINES)
		वापस -EINVAL;

	err = via_dmablit_sync(dev, sync->sync_handle, sync->engine);

	अगर (-EINTR == err)
		err = -EAGAIN;

	वापस err;
पूर्ण


/*
 * Queue a blit and hand back a handle to be used क्रम sync. This IOCTL may be पूर्णांकerrupted by a संकेत
 * जबतक रुकोing क्रम a मुक्त slot in the blit queue. In that हाल it वापसs with -EAGAIN and should
 * be reissued. See the above IOCTL code.
 */

पूर्णांक
via_dma_blit(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_via_dmablit_t *xfer = data;
	पूर्णांक err;

	err = via_dmablit(dev, xfer);

	वापस err;
पूर्ण
