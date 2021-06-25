<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    User DMA

    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2004  Chris Kennedy <c@groovy.org>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-udma.h"

व्योम ivtv_udma_get_page_info(काष्ठा ivtv_dma_page_info *dma_page, अचिन्हित दीर्घ first, अचिन्हित दीर्घ size)
अणु
	dma_page->uaddr = first & PAGE_MASK;
	dma_page->offset = first & ~PAGE_MASK;
	dma_page->tail = 1 + ((first+size-1) & ~PAGE_MASK);
	dma_page->first = (first & PAGE_MASK) >> PAGE_SHIFT;
	dma_page->last = ((first+size-1) & PAGE_MASK) >> PAGE_SHIFT;
	dma_page->page_count = dma_page->last - dma_page->first + 1;
	अगर (dma_page->page_count == 1) dma_page->tail -= dma_page->offset;
पूर्ण

पूर्णांक ivtv_udma_fill_sg_list (काष्ठा ivtv_user_dma *dma, काष्ठा ivtv_dma_page_info *dma_page, पूर्णांक map_offset)
अणु
	पूर्णांक i, offset;
	अचिन्हित दीर्घ flags;

	अगर (map_offset < 0)
		वापस map_offset;

	offset = dma_page->offset;

	/* Fill SG Array with new values */
	क्रम (i = 0; i < dma_page->page_count; i++) अणु
		अचिन्हित पूर्णांक len = (i == dma_page->page_count - 1) ?
			dma_page->tail : PAGE_SIZE - offset;

		अगर (PageHighMem(dma->map[map_offset])) अणु
			व्योम *src;

			अगर (dma->bouncemap[map_offset] == शून्य)
				dma->bouncemap[map_offset] = alloc_page(GFP_KERNEL);
			अगर (dma->bouncemap[map_offset] == शून्य)
				वापस -1;
			local_irq_save(flags);
			src = kmap_atomic(dma->map[map_offset]) + offset;
			स_नकल(page_address(dma->bouncemap[map_offset]) + offset, src, len);
			kunmap_atomic(src);
			local_irq_restore(flags);
			sg_set_page(&dma->SGlist[map_offset], dma->bouncemap[map_offset], len, offset);
		पूर्ण
		अन्यथा अणु
			sg_set_page(&dma->SGlist[map_offset], dma->map[map_offset], len, offset);
		पूर्ण
		offset = 0;
		map_offset++;
	पूर्ण
	वापस map_offset;
पूर्ण

व्योम ivtv_udma_fill_sg_array (काष्ठा ivtv_user_dma *dma, u32 buffer_offset, u32 buffer_offset_2, u32 split) अणु
	पूर्णांक i;
	काष्ठा scatterlist *sg;

	क्रम_each_sg(dma->SGlist, sg, dma->SG_length, i) अणु
		dma->SGarray[i].size = cpu_to_le32(sg_dma_len(sg));
		dma->SGarray[i].src = cpu_to_le32(sg_dma_address(sg));
		dma->SGarray[i].dst = cpu_to_le32(buffer_offset);
		buffer_offset += sg_dma_len(sg);

		split -= sg_dma_len(sg);
		अगर (split == 0)
			buffer_offset = buffer_offset_2;
	पूर्ण
पूर्ण

/* User DMA Buffers */
व्योम ivtv_udma_alloc(काष्ठा ivtv *itv)
अणु
	अगर (itv->udma.SG_handle == 0) अणु
		/* Map DMA Page Array Buffer */
		itv->udma.SG_handle = pci_map_single(itv->pdev, itv->udma.SGarray,
			   माप(itv->udma.SGarray), PCI_DMA_TODEVICE);
		ivtv_udma_sync_क्रम_cpu(itv);
	पूर्ण
पूर्ण

पूर्णांक ivtv_udma_setup(काष्ठा ivtv *itv, अचिन्हित दीर्घ ivtv_dest_addr,
		       व्योम __user *userbuf, पूर्णांक size_in_bytes)
अणु
	काष्ठा ivtv_dma_page_info user_dma;
	काष्ठा ivtv_user_dma *dma = &itv->udma;
	पूर्णांक err;

	IVTV_DEBUG_DMA("ivtv_udma_setup, dst: 0x%08x\n", (अचिन्हित पूर्णांक)ivtv_dest_addr);

	/* Still in USE */
	अगर (dma->SG_length || dma->page_count) अणु
		IVTV_DEBUG_WARN("ivtv_udma_setup: SG_length %d page_count %d still full?\n",
			   dma->SG_length, dma->page_count);
		वापस -EBUSY;
	पूर्ण

	ivtv_udma_get_page_info(&user_dma, (अचिन्हित दीर्घ)userbuf, size_in_bytes);

	अगर (user_dma.page_count <= 0) अणु
		IVTV_DEBUG_WARN("ivtv_udma_setup: Error %d page_count from %d bytes %d offset\n",
			   user_dma.page_count, size_in_bytes, user_dma.offset);
		वापस -EINVAL;
	पूर्ण

	/* Pin user pages क्रम DMA Xfer */
	err = pin_user_pages_unlocked(user_dma.uaddr, user_dma.page_count,
			dma->map, FOLL_FORCE);

	अगर (user_dma.page_count != err) अणु
		IVTV_DEBUG_WARN("failed to map user pages, returned %d instead of %d\n",
			   err, user_dma.page_count);
		अगर (err >= 0) अणु
			unpin_user_pages(dma->map, err);
			वापस -EINVAL;
		पूर्ण
		वापस err;
	पूर्ण

	dma->page_count = user_dma.page_count;

	/* Fill SG List with new values */
	अगर (ivtv_udma_fill_sg_list(dma, &user_dma, 0) < 0) अणु
		unpin_user_pages(dma->map, dma->page_count);
		dma->page_count = 0;
		वापस -ENOMEM;
	पूर्ण

	/* Map SG List */
	dma->SG_length = pci_map_sg(itv->pdev, dma->SGlist, dma->page_count, PCI_DMA_TODEVICE);

	/* Fill SG Array with new values */
	ivtv_udma_fill_sg_array (dma, ivtv_dest_addr, 0, -1);

	/* Tag SG Array with Interrupt Bit */
	dma->SGarray[dma->SG_length - 1].size |= cpu_to_le32(0x80000000);

	ivtv_udma_sync_क्रम_device(itv);
	वापस dma->page_count;
पूर्ण

व्योम ivtv_udma_unmap(काष्ठा ivtv *itv)
अणु
	काष्ठा ivtv_user_dma *dma = &itv->udma;

	IVTV_DEBUG_INFO("ivtv_unmap_user_dma\n");

	/* Nothing to मुक्त */
	अगर (dma->page_count == 0)
		वापस;

	/* Unmap Scatterlist */
	अगर (dma->SG_length) अणु
		pci_unmap_sg(itv->pdev, dma->SGlist, dma->page_count, PCI_DMA_TODEVICE);
		dma->SG_length = 0;
	पूर्ण
	/* sync DMA */
	ivtv_udma_sync_क्रम_cpu(itv);

	unpin_user_pages(dma->map, dma->page_count);
	dma->page_count = 0;
पूर्ण

व्योम ivtv_udma_मुक्त(काष्ठा ivtv *itv)
अणु
	पूर्णांक i;

	/* Unmap SG Array */
	अगर (itv->udma.SG_handle) अणु
		pci_unmap_single(itv->pdev, itv->udma.SG_handle,
			 माप(itv->udma.SGarray), PCI_DMA_TODEVICE);
	पूर्ण

	/* Unmap Scatterlist */
	अगर (itv->udma.SG_length) अणु
		pci_unmap_sg(itv->pdev, itv->udma.SGlist, itv->udma.page_count, PCI_DMA_TODEVICE);
	पूर्ण

	क्रम (i = 0; i < IVTV_DMA_SG_OSD_ENT; i++) अणु
		अगर (itv->udma.bouncemap[i])
			__मुक्त_page(itv->udma.bouncemap[i]);
	पूर्ण
पूर्ण

व्योम ivtv_udma_start(काष्ठा ivtv *itv)
अणु
	IVTV_DEBUG_DMA("start UDMA\n");
	ग_लिखो_reg(itv->udma.SG_handle, IVTV_REG_DECDMAADDR);
	ग_लिखो_reg_sync(पढ़ो_reg(IVTV_REG_DMAXFER) | 0x01, IVTV_REG_DMAXFER);
	set_bit(IVTV_F_I_DMA, &itv->i_flags);
	set_bit(IVTV_F_I_UDMA, &itv->i_flags);
	clear_bit(IVTV_F_I_UDMA_PENDING, &itv->i_flags);
पूर्ण

व्योम ivtv_udma_prepare(काष्ठा ivtv *itv)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&itv->dma_reg_lock, flags);
	अगर (!test_bit(IVTV_F_I_DMA, &itv->i_flags))
		ivtv_udma_start(itv);
	अन्यथा
		set_bit(IVTV_F_I_UDMA_PENDING, &itv->i_flags);
	spin_unlock_irqrestore(&itv->dma_reg_lock, flags);
पूर्ण
