<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Secure VM platक्रमm
 *
 * Copyright 2018 IBM Corporation
 * Author: Anshuman Khandual <khandual@linux.vnet.ibm.com>
 */

#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/svm.h>
#समावेश <यंत्र/swiotlb.h>
#समावेश <यंत्र/ultravisor.h>
#समावेश <यंत्र/dtl.h>

अटल पूर्णांक __init init_svm(व्योम)
अणु
	अगर (!is_secure_guest())
		वापस 0;

	/* Don't release the SWIOTLB buffer. */
	ppc_swiotlb_enable = 1;

	/*
	 * Since the guest memory is inaccessible to the host, devices always
	 * need to use the SWIOTLB buffer क्रम DMA even अगर dma_capable() says
	 * otherwise.
	 */
	swiotlb_क्रमce = SWIOTLB_FORCE;

	/* Share the SWIOTLB buffer with the host. */
	swiotlb_update_mem_attributes();

	वापस 0;
पूर्ण
machine_early_initcall(pseries, init_svm);

/*
 * Initialize SWIOTLB. Essentially the same as swiotlb_init(), except that it
 * can allocate the buffer anywhere in memory. Since the hypervisor करोesn't have
 * any addressing limitation, we करोn't need to allocate it in low addresses.
 */
व्योम __init svm_swiotlb_init(व्योम)
अणु
	अचिन्हित अक्षर *vstart;
	अचिन्हित दीर्घ bytes, io_tlb_nsद_असल;

	io_tlb_nsद_असल = (swiotlb_size_or_शेष() >> IO_TLB_SHIFT);
	io_tlb_nsद_असल = ALIGN(io_tlb_nsद_असल, IO_TLB_SEGSIZE);

	bytes = io_tlb_nsद_असल << IO_TLB_SHIFT;

	vstart = memblock_alloc(PAGE_ALIGN(bytes), PAGE_SIZE);
	अगर (vstart && !swiotlb_init_with_tbl(vstart, io_tlb_nsद_असल, false))
		वापस;


	memblock_मुक्त_early(__pa(vstart),
			    PAGE_ALIGN(io_tlb_nsद_असल << IO_TLB_SHIFT));
	panic("SVM: Cannot allocate SWIOTLB buffer");
पूर्ण

पूर्णांक set_memory_encrypted(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	अगर (!PAGE_ALIGNED(addr))
		वापस -EINVAL;

	uv_unshare_page(PHYS_PFN(__pa(addr)), numpages);

	वापस 0;
पूर्ण

पूर्णांक set_memory_decrypted(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	अगर (!PAGE_ALIGNED(addr))
		वापस -EINVAL;

	uv_share_page(PHYS_PFN(__pa(addr)), numpages);

	वापस 0;
पूर्ण

/* There's one dispatch log per CPU. */
#घोषणा NR_DTL_PAGE (DISPATCH_LOG_BYTES * CONFIG_NR_CPUS / PAGE_SIZE)

अटल काष्ठा page *dtl_page_store[NR_DTL_PAGE];
अटल दीर्घ dtl_nr_pages;

अटल bool is_dtl_page_shared(काष्ठा page *page)
अणु
	दीर्घ i;

	क्रम (i = 0; i < dtl_nr_pages; i++)
		अगर (dtl_page_store[i] == page)
			वापस true;

	वापस false;
पूर्ण

व्योम dtl_cache_ctor(व्योम *addr)
अणु
	अचिन्हित दीर्घ pfn = PHYS_PFN(__pa(addr));
	काष्ठा page *page = pfn_to_page(pfn);

	अगर (!is_dtl_page_shared(page)) अणु
		dtl_page_store[dtl_nr_pages] = page;
		dtl_nr_pages++;
		WARN_ON(dtl_nr_pages >= NR_DTL_PAGE);
		uv_share_page(pfn, 1);
	पूर्ण
पूर्ण
