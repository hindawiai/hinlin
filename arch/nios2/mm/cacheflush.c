<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2009, Wind River Systems Inc
 * Implemented by fredrik.markstrom@gmail.com and ivarholmqvist@gmail.com
 */

#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpuinfo.h>

अटल व्योम __flush_dcache(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ addr;

	start &= ~(cpuinfo.dcache_line_size - 1);
	end += (cpuinfo.dcache_line_size - 1);
	end &= ~(cpuinfo.dcache_line_size - 1);

	अगर (end > start + cpuinfo.dcache_size)
		end = start + cpuinfo.dcache_size;

	क्रम (addr = start; addr < end; addr += cpuinfo.dcache_line_size) अणु
		__यंत्र__ __अस्थिर__ ("   flushd 0(%0)\n"
					: /* Outमाला_दो */
					: /* Inमाला_दो  */ "r"(addr)
					/* : No clobber */);
	पूर्ण
पूर्ण

अटल व्योम __invalidate_dcache(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ addr;

	start &= ~(cpuinfo.dcache_line_size - 1);
	end += (cpuinfo.dcache_line_size - 1);
	end &= ~(cpuinfo.dcache_line_size - 1);

	क्रम (addr = start; addr < end; addr += cpuinfo.dcache_line_size) अणु
		__यंत्र__ __अस्थिर__ ("   initda 0(%0)\n"
					: /* Outमाला_दो */
					: /* Inमाला_दो  */ "r"(addr)
					/* : No clobber */);
	पूर्ण
पूर्ण

अटल व्योम __flush_icache(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ addr;

	start &= ~(cpuinfo.icache_line_size - 1);
	end += (cpuinfo.icache_line_size - 1);
	end &= ~(cpuinfo.icache_line_size - 1);

	अगर (end > start + cpuinfo.icache_size)
		end = start + cpuinfo.icache_size;

	क्रम (addr = start; addr < end; addr += cpuinfo.icache_line_size) अणु
		__यंत्र__ __अस्थिर__ ("   flushi %0\n"
					: /* Outमाला_दो */
					: /* Inमाला_दो  */ "r"(addr)
					/* : No clobber */);
	पूर्ण
	__यंत्र__ __अस्थिर(" flushp\n");
पूर्ण

अटल व्योम flush_aliases(काष्ठा address_space *mapping, काष्ठा page *page)
अणु
	काष्ठा mm_काष्ठा *mm = current->active_mm;
	काष्ठा vm_area_काष्ठा *mpnt;
	pgoff_t pgoff;

	pgoff = page->index;

	flush_dcache_mmap_lock(mapping);
	vma_पूर्णांकerval_tree_क्रमeach(mpnt, &mapping->i_mmap, pgoff, pgoff) अणु
		अचिन्हित दीर्घ offset;

		अगर (mpnt->vm_mm != mm)
			जारी;
		अगर (!(mpnt->vm_flags & VM_MAYSHARE))
			जारी;

		offset = (pgoff - mpnt->vm_pgoff) << PAGE_SHIFT;
		flush_cache_page(mpnt, mpnt->vm_start + offset,
			page_to_pfn(page));
	पूर्ण
	flush_dcache_mmap_unlock(mapping);
पूर्ण

व्योम flush_cache_all(व्योम)
अणु
	__flush_dcache(0, cpuinfo.dcache_size);
	__flush_icache(0, cpuinfo.icache_size);
पूर्ण

व्योम flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
	flush_cache_all();
पूर्ण

व्योम flush_cache_dup_mm(काष्ठा mm_काष्ठा *mm)
अणु
	flush_cache_all();
पूर्ण

व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	__flush_dcache(start, end);
	__flush_icache(start, end);
पूर्ण

व्योम flush_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	__flush_dcache(start, end);
	__flush_icache(start, end);
पूर्ण
EXPORT_SYMBOL(flush_dcache_range);

व्योम invalidate_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	__invalidate_dcache(start, end);
पूर्ण
EXPORT_SYMBOL(invalidate_dcache_range);

व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ end)
अणु
	__flush_dcache(start, end);
	अगर (vma == शून्य || (vma->vm_flags & VM_EXEC))
		__flush_icache(start, end);
पूर्ण

व्योम flush_icache_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ) page_address(page);
	अचिन्हित दीर्घ end = start + PAGE_SIZE;

	__flush_dcache(start, end);
	__flush_icache(start, end);
पूर्ण

व्योम flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr,
			अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ start = vmaddr;
	अचिन्हित दीर्घ end = start + PAGE_SIZE;

	__flush_dcache(start, end);
	अगर (vma->vm_flags & VM_EXEC)
		__flush_icache(start, end);
पूर्ण

व्योम __flush_dcache_page(काष्ठा address_space *mapping, काष्ठा page *page)
अणु
	/*
	 * Writeback any data associated with the kernel mapping of this
	 * page.  This ensures that data in the physical page is mutually
	 * coherent with the kernels mapping.
	 */
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)page_address(page);

	__flush_dcache(start, start + PAGE_SIZE);
पूर्ण

व्योम flush_dcache_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping;

	/*
	 * The zero page is never written to, so never has any dirty
	 * cache lines, and thereक्रमe never needs to be flushed.
	 */
	अगर (page == ZERO_PAGE(0))
		वापस;

	mapping = page_mapping_file(page);

	/* Flush this page अगर there are aliases. */
	अगर (mapping && !mapping_mapped(mapping)) अणु
		clear_bit(PG_dcache_clean, &page->flags);
	पूर्ण अन्यथा अणु
		__flush_dcache_page(mapping, page);
		अगर (mapping) अणु
			अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)page_address(page);
			flush_aliases(mapping,  page);
			flush_icache_range(start, start + PAGE_SIZE);
		पूर्ण
		set_bit(PG_dcache_clean, &page->flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flush_dcache_page);

व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	pte_t pte = *ptep;
	अचिन्हित दीर्घ pfn = pte_pfn(pte);
	काष्ठा page *page;
	काष्ठा address_space *mapping;

	reload_tlb_page(vma, address, pte);

	अगर (!pfn_valid(pfn))
		वापस;

	/*
	* The zero page is never written to, so never has any dirty
	* cache lines, and thereक्रमe never needs to be flushed.
	*/
	page = pfn_to_page(pfn);
	अगर (page == ZERO_PAGE(0))
		वापस;

	mapping = page_mapping_file(page);
	अगर (!test_and_set_bit(PG_dcache_clean, &page->flags))
		__flush_dcache_page(mapping, page);

	अगर(mapping)
	अणु
		flush_aliases(mapping, page);
		अगर (vma->vm_flags & VM_EXEC)
			flush_icache_page(vma, page);
	पूर्ण
पूर्ण

व्योम copy_user_page(व्योम *vto, व्योम *vfrom, अचिन्हित दीर्घ vaddr,
		    काष्ठा page *to)
अणु
	__flush_dcache(vaddr, vaddr + PAGE_SIZE);
	__flush_icache(vaddr, vaddr + PAGE_SIZE);
	copy_page(vto, vfrom);
	__flush_dcache((अचिन्हित दीर्घ)vto, (अचिन्हित दीर्घ)vto + PAGE_SIZE);
	__flush_icache((अचिन्हित दीर्घ)vto, (अचिन्हित दीर्घ)vto + PAGE_SIZE);
पूर्ण

व्योम clear_user_page(व्योम *addr, अचिन्हित दीर्घ vaddr, काष्ठा page *page)
अणु
	__flush_dcache(vaddr, vaddr + PAGE_SIZE);
	__flush_icache(vaddr, vaddr + PAGE_SIZE);
	clear_page(addr);
	__flush_dcache((अचिन्हित दीर्घ)addr, (अचिन्हित दीर्घ)addr + PAGE_SIZE);
	__flush_icache((अचिन्हित दीर्घ)addr, (अचिन्हित दीर्घ)addr + PAGE_SIZE);
पूर्ण

व्योम copy_from_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
			अचिन्हित दीर्घ user_vaddr,
			व्योम *dst, व्योम *src, पूर्णांक len)
अणु
	flush_cache_page(vma, user_vaddr, page_to_pfn(page));
	स_नकल(dst, src, len);
	__flush_dcache((अचिन्हित दीर्घ)src, (अचिन्हित दीर्घ)src + len);
	अगर (vma->vm_flags & VM_EXEC)
		__flush_icache((अचिन्हित दीर्घ)src, (अचिन्हित दीर्घ)src + len);
पूर्ण

व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
			अचिन्हित दीर्घ user_vaddr,
			व्योम *dst, व्योम *src, पूर्णांक len)
अणु
	flush_cache_page(vma, user_vaddr, page_to_pfn(page));
	स_नकल(dst, src, len);
	__flush_dcache((अचिन्हित दीर्घ)dst, (अचिन्हित दीर्घ)dst + len);
	अगर (vma->vm_flags & VM_EXEC)
		__flush_icache((अचिन्हित दीर्घ)dst, (अचिन्हित दीर्घ)dst + len);
पूर्ण
