<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000  Ani Joshi <ajoshi@unixbox.com>
 * Copyright (C) 2000, 2001, 06	 Ralf Baechle <ralf@linux-mips.org>
 * swiped from i386, and cloned क्रम MIPS by Geert, polished by Ralf.
 */
#समावेश <linux/dma-direct.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/highस्मृति.स>

#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/पन.स>

/*
 * The affected CPUs below in 'cpu_needs_post_dma_flush()' can speculatively
 * fill अक्रमom cachelines with stale data at any समय, requiring an extra
 * flush post-DMA.
 *
 * Warning on the terminology - Linux calls an uncached area coherent;  MIPS
 * terminology calls memory areas with hardware मुख्यtained coherency coherent.
 *
 * Note that the R14000 and R16000 should also be checked क्रम in this condition.
 * However this function is only called on non-I/O-coherent प्रणालीs and only the
 * R10000 and R12000 are used in such प्रणालीs, the SGI IP28 Indigoतऑ rsp.
 * SGI IP32 aka O2.
 */
अटल अंतरभूत bool cpu_needs_post_dma_flush(व्योम)
अणु
	चयन (boot_cpu_type()) अणु
	हाल CPU_R10000:
	हाल CPU_R12000:
	हाल CPU_BMIPS5000:
	हाल CPU_LOONGSON2EF:
		वापस true;
	शेष:
		/*
		 * Presence of MAARs suggests that the CPU supports
		 * speculatively prefetching data, and thereक्रमe requires
		 * the post-DMA flush/invalidate.
		 */
		वापस cpu_has_maar;
	पूर्ण
पूर्ण

व्योम arch_dma_prep_coherent(काष्ठा page *page, माप_प्रकार size)
अणु
	dma_cache_wback_inv((अचिन्हित दीर्घ)page_address(page), size);
पूर्ण

व्योम *arch_dma_set_uncached(व्योम *addr, माप_प्रकार size)
अणु
	वापस (व्योम *)(__pa(addr) + UNCAC_BASE);
पूर्ण

अटल अंतरभूत व्योम dma_sync_virt_क्रम_device(व्योम *addr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	चयन (dir) अणु
	हाल DMA_TO_DEVICE:
		dma_cache_wback((अचिन्हित दीर्घ)addr, size);
		अवरोध;
	हाल DMA_FROM_DEVICE:
		dma_cache_inv((अचिन्हित दीर्घ)addr, size);
		अवरोध;
	हाल DMA_BIसूचीECTIONAL:
		dma_cache_wback_inv((अचिन्हित दीर्घ)addr, size);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम dma_sync_virt_क्रम_cpu(व्योम *addr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	चयन (dir) अणु
	हाल DMA_TO_DEVICE:
		अवरोध;
	हाल DMA_FROM_DEVICE:
	हाल DMA_BIसूचीECTIONAL:
		dma_cache_inv((अचिन्हित दीर्घ)addr, size);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * A single sg entry may refer to multiple physically contiguous pages.  But
 * we still need to process highmem pages inभागidually.  If highmem is not
 * configured then the bulk of this loop माला_लो optimized out.
 */
अटल अंतरभूत व्योम dma_sync_phys(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir, bool क्रम_device)
अणु
	काष्ठा page *page = pfn_to_page(paddr >> PAGE_SHIFT);
	अचिन्हित दीर्घ offset = paddr & ~PAGE_MASK;
	माप_प्रकार left = size;

	करो अणु
		माप_प्रकार len = left;
		व्योम *addr;

		अगर (PageHighMem(page)) अणु
			अगर (offset + len > PAGE_SIZE)
				len = PAGE_SIZE - offset;
		पूर्ण

		addr = kmap_atomic(page);
		अगर (क्रम_device)
			dma_sync_virt_क्रम_device(addr + offset, len, dir);
		अन्यथा
			dma_sync_virt_क्रम_cpu(addr + offset, len, dir);
		kunmap_atomic(addr);

		offset = 0;
		page++;
		left -= len;
	पूर्ण जबतक (left);
पूर्ण

व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	dma_sync_phys(paddr, size, dir, true);
पूर्ण

#अगर_घोषित CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU
व्योम arch_sync_dma_क्रम_cpu(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	अगर (cpu_needs_post_dma_flush())
		dma_sync_phys(paddr, size, dir, false);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_HAS_SETUP_DMA_OPS
व्योम arch_setup_dma_ops(काष्ठा device *dev, u64 dma_base, u64 size,
		स्थिर काष्ठा iommu_ops *iommu, bool coherent)
अणु
	dev->dma_coherent = coherent;
पूर्ण
#पूर्ण_अगर
