<शैली गुरु>
/*
 * Copyright (c) 2006, 2007, 2008, 2009 QLogic Corporation. All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
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

#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/device.h>

#समावेश "qib.h"

अटल व्योम __qib_release_user_pages(काष्ठा page **p, माप_प्रकार num_pages,
				     पूर्णांक dirty)
अणु
	unpin_user_pages_dirty_lock(p, num_pages, dirty);
पूर्ण

/*
 * qib_map_page - a safety wrapper around pci_map_page()
 *
 * A dma_addr of all 0's is पूर्णांकerpreted by the chip as "disabled".
 * Unक्रमtunately, it can also be a valid dma_addr वापसed on some
 * architectures.
 *
 * The घातerpc iommu assigns dma_addrs in ascending order, so we करोn't
 * have to bother with retries or mapping a dummy page to insure we
 * करोn't just get the same mapping again.
 *
 * I'm sure we won't be so lucky with other iommu's, so FIXME.
 */
पूर्णांक qib_map_page(काष्ठा pci_dev *hwdev, काष्ठा page *page, dma_addr_t *daddr)
अणु
	dma_addr_t phys;

	phys = pci_map_page(hwdev, page, 0, PAGE_SIZE, PCI_DMA_FROMDEVICE);
	अगर (pci_dma_mapping_error(hwdev, phys))
		वापस -ENOMEM;

	अगर (!phys) अणु
		pci_unmap_page(hwdev, phys, PAGE_SIZE, PCI_DMA_FROMDEVICE);
		phys = pci_map_page(hwdev, page, 0, PAGE_SIZE,
				    PCI_DMA_FROMDEVICE);
		अगर (pci_dma_mapping_error(hwdev, phys))
			वापस -ENOMEM;
		/*
		 * FIXME: If we get 0 again, we should keep this page,
		 * map another, then मुक्त the 0 page.
		 */
	पूर्ण
	*daddr = phys;
	वापस 0;
पूर्ण

/**
 * qib_get_user_pages - lock user pages पूर्णांकo memory
 * @start_page: the start page
 * @num_pages: the number of pages
 * @p: the output page काष्ठाures
 *
 * This function takes a given start page (page aligned user भव
 * address) and pins it and the following specअगरied number of pages.  For
 * now, num_pages is always 1, but that will probably change at some poपूर्णांक
 * (because caller is करोing expected sends on a single भवly contiguous
 * buffer, so we can करो all pages at once).
 */
पूर्णांक qib_get_user_pages(अचिन्हित दीर्घ start_page, माप_प्रकार num_pages,
		       काष्ठा page **p)
अणु
	अचिन्हित दीर्घ locked, lock_limit;
	माप_प्रकार got;
	पूर्णांक ret;

	lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	locked = atomic64_add_वापस(num_pages, &current->mm->pinned_vm);

	अगर (locked > lock_limit && !capable(CAP_IPC_LOCK)) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण

	mmap_पढ़ो_lock(current->mm);
	क्रम (got = 0; got < num_pages; got += ret) अणु
		ret = pin_user_pages(start_page + got * PAGE_SIZE,
				     num_pages - got,
				     FOLL_LONGTERM | FOLL_WRITE | FOLL_FORCE,
				     p + got, शून्य);
		अगर (ret < 0) अणु
			mmap_पढ़ो_unlock(current->mm);
			जाओ bail_release;
		पूर्ण
	पूर्ण
	mmap_पढ़ो_unlock(current->mm);

	वापस 0;
bail_release:
	__qib_release_user_pages(p, got, 0);
bail:
	atomic64_sub(num_pages, &current->mm->pinned_vm);
	वापस ret;
पूर्ण

व्योम qib_release_user_pages(काष्ठा page **p, माप_प्रकार num_pages)
अणु
	__qib_release_user_pages(p, num_pages, 1);

	/* during बंद after संकेत, mm can be शून्य */
	अगर (current->mm)
		atomic64_sub(num_pages, &current->mm->pinned_vm);
पूर्ण
