<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/shmparam.h>
#समावेश <यंत्र/cache_info.h>

बाह्य काष्ठा cache_info L1_cache_info[2];

व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ line_size, flags;
	line_size = L1_cache_info[DCACHE].line_size;
	start = start & ~(line_size - 1);
	end = (end + line_size - 1) & ~(line_size - 1);
	local_irq_save(flags);
	cpu_cache_wbinval_range(start, end, 1);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(flush_icache_range);

व्योम flush_icache_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ kaddr;
	local_irq_save(flags);
	kaddr = (अचिन्हित दीर्घ)kmap_atomic(page);
	cpu_cache_wbinval_page(kaddr, vma->vm_flags & VM_EXEC);
	kunmap_atomic((व्योम *)kaddr);
	local_irq_restore(flags);
पूर्ण

व्योम flush_icache_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
	                     अचिन्हित दीर्घ addr, पूर्णांक len)
अणु
	अचिन्हित दीर्घ kaddr;
	kaddr = (अचिन्हित दीर्घ)kmap_atomic(page) + (addr & ~PAGE_MASK);
	flush_icache_range(kaddr, kaddr + len);
	kunmap_atomic((व्योम *)kaddr);
पूर्ण

व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		      pte_t * pte)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ pfn = pte_pfn(*pte);
	अचिन्हित दीर्घ flags;

	अगर (!pfn_valid(pfn))
		वापस;

	अगर (vma->vm_mm == current->active_mm) अणु
		local_irq_save(flags);
		__nds32__mtsr_dsb(addr, NDS32_SR_TLB_VPN);
		__nds32__tlbop_rwr(*pte);
		__nds32__isb();
		local_irq_restore(flags);
	पूर्ण
	page = pfn_to_page(pfn);

	अगर ((test_and_clear_bit(PG_dcache_dirty, &page->flags)) ||
	    (vma->vm_flags & VM_EXEC)) अणु
		अचिन्हित दीर्घ kaddr;
		local_irq_save(flags);
		kaddr = (अचिन्हित दीर्घ)kmap_atomic(page);
		cpu_cache_wbinval_page(kaddr, vma->vm_flags & VM_EXEC);
		kunmap_atomic((व्योम *)kaddr);
		local_irq_restore(flags);
	पूर्ण
पूर्ण
#अगर_घोषित CONFIG_CPU_CACHE_ALIASING
बाह्य pte_t va_present(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);

अटल अंतरभूत अचिन्हित दीर्घ aliasing(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ page)
अणु
	वापस ((addr & PAGE_MASK) ^ page) & (SHMLBA - 1);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kremap0(अचिन्हित दीर्घ uaddr, अचिन्हित दीर्घ pa)
अणु
	अचिन्हित दीर्घ kaddr, pte;

#घोषणा BASE_ADDR0 0xffffc000
	kaddr = BASE_ADDR0 | (uaddr & L1_cache_info[DCACHE].aliasing_mask);
	pte = (pa | PAGE_KERNEL);
	__nds32__mtsr_dsb(kaddr, NDS32_SR_TLB_VPN);
	__nds32__tlbop_rwlk(pte);
	__nds32__isb();
	वापस kaddr;
पूर्ण

अटल अंतरभूत व्योम kunmap01(अचिन्हित दीर्घ kaddr)
अणु
	__nds32__tlbop_unlk(kaddr);
	__nds32__tlbop_inv(kaddr);
	__nds32__isb();
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kremap1(अचिन्हित दीर्घ uaddr, अचिन्हित दीर्घ pa)
अणु
	अचिन्हित दीर्घ kaddr, pte;

#घोषणा BASE_ADDR1 0xffff8000
	kaddr = BASE_ADDR1 | (uaddr & L1_cache_info[DCACHE].aliasing_mask);
	pte = (pa | PAGE_KERNEL);
	__nds32__mtsr_dsb(kaddr, NDS32_SR_TLB_VPN);
	__nds32__tlbop_rwlk(pte);
	__nds32__isb();
	वापस kaddr;
पूर्ण

व्योम flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	cpu_dcache_wbinval_all();
	cpu_icache_inval_all();
	local_irq_restore(flags);
पूर्ण

व्योम flush_cache_dup_mm(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण

व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
		       अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ flags;

	अगर ((end - start) > 8 * PAGE_SIZE) अणु
		cpu_dcache_wbinval_all();
		अगर (vma->vm_flags & VM_EXEC)
			cpu_icache_inval_all();
		वापस;
	पूर्ण
	local_irq_save(flags);
	जबतक (start < end) अणु
		अगर (va_present(vma->vm_mm, start))
			cpu_cache_wbinval_page(start, vma->vm_flags & VM_EXEC);
		start += PAGE_SIZE;
	पूर्ण
	local_irq_restore(flags);
	वापस;
पूर्ण

व्योम flush_cache_page(काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ vto, flags;

	local_irq_save(flags);
	vto = kremap0(addr, pfn << PAGE_SHIFT);
	cpu_cache_wbinval_page(vto, vma->vm_flags & VM_EXEC);
	kunmap01(vto);
	local_irq_restore(flags);
पूर्ण

व्योम flush_cache_vmap(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	cpu_dcache_wbinval_all();
	cpu_icache_inval_all();
पूर्ण

व्योम flush_cache_vunmap(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	cpu_dcache_wbinval_all();
	cpu_icache_inval_all();
पूर्ण

व्योम copy_user_page(व्योम *vto, व्योम *vfrom, अचिन्हित दीर्घ vaddr,
		    काष्ठा page *to)
अणु
	cpu_dcache_wbinval_page((अचिन्हित दीर्घ)vaddr);
	cpu_icache_inval_page((अचिन्हित दीर्घ)vaddr);
	copy_page(vto, vfrom);
	cpu_dcache_wbinval_page((अचिन्हित दीर्घ)vto);
	cpu_icache_inval_page((अचिन्हित दीर्घ)vto);
पूर्ण

व्योम clear_user_page(व्योम *addr, अचिन्हित दीर्घ vaddr, काष्ठा page *page)
अणु
	cpu_dcache_wbinval_page((अचिन्हित दीर्घ)vaddr);
	cpu_icache_inval_page((अचिन्हित दीर्घ)vaddr);
	clear_page(addr);
	cpu_dcache_wbinval_page((अचिन्हित दीर्घ)addr);
	cpu_icache_inval_page((अचिन्हित दीर्घ)addr);
पूर्ण

व्योम copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
			अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ vto, vfrom, flags, kto, kfrom, pfrom, pto;
	kto = ((अचिन्हित दीर्घ)page_address(to) & PAGE_MASK);
	kfrom = ((अचिन्हित दीर्घ)page_address(from) & PAGE_MASK);
	pto = page_to_phys(to);
	pfrom = page_to_phys(from);

	local_irq_save(flags);
	अगर (aliasing(vaddr, (अचिन्हित दीर्घ)kfrom))
		cpu_dcache_wb_page((अचिन्हित दीर्घ)kfrom);
	vto = kremap0(vaddr, pto);
	vfrom = kremap1(vaddr, pfrom);
	copy_page((व्योम *)vto, (व्योम *)vfrom);
	kunmap01(vfrom);
	kunmap01(vto);
	local_irq_restore(flags);
पूर्ण

EXPORT_SYMBOL(copy_user_highpage);

व्योम clear_user_highpage(काष्ठा page *page, अचिन्हित दीर्घ vaddr)
अणु
	अचिन्हित दीर्घ vto, flags, kto;

	kto = ((अचिन्हित दीर्घ)page_address(page) & PAGE_MASK);

	local_irq_save(flags);
	अगर (aliasing(kto, vaddr) && kto != 0) अणु
		cpu_dcache_inval_page(kto);
		cpu_icache_inval_page(kto);
	पूर्ण
	vto = kremap0(vaddr, page_to_phys(page));
	clear_page((व्योम *)vto);
	kunmap01(vto);
	local_irq_restore(flags);
पूर्ण

EXPORT_SYMBOL(clear_user_highpage);

व्योम flush_dcache_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping;

	mapping = page_mapping_file(page);
	अगर (mapping && !mapping_mapped(mapping))
		set_bit(PG_dcache_dirty, &page->flags);
	अन्यथा अणु
		अचिन्हित दीर्घ kaddr, flags;

		kaddr = (अचिन्हित दीर्घ)page_address(page);
		local_irq_save(flags);
		cpu_dcache_wbinval_page(kaddr);
		अगर (mapping) अणु
			अचिन्हित दीर्घ vaddr, kto;

			vaddr = page->index << PAGE_SHIFT;
			अगर (aliasing(vaddr, kaddr)) अणु
				kto = kremap0(vaddr, page_to_phys(page));
				cpu_dcache_wbinval_page(kto);
				kunmap01(kto);
			पूर्ण
		पूर्ण
		local_irq_restore(flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flush_dcache_page);

व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
		       अचिन्हित दीर्घ vaddr, व्योम *dst, व्योम *src, पूर्णांक len)
अणु
	अचिन्हित दीर्घ line_size, start, end, vto, flags;

	local_irq_save(flags);
	vto = kremap0(vaddr, page_to_phys(page));
	dst = (व्योम *)(vto | (vaddr & (PAGE_SIZE - 1)));
	स_नकल(dst, src, len);
	अगर (vma->vm_flags & VM_EXEC) अणु
		line_size = L1_cache_info[DCACHE].line_size;
		start = (अचिन्हित दीर्घ)dst & ~(line_size - 1);
		end =
		    ((अचिन्हित दीर्घ)dst + len + line_size - 1) & ~(line_size -
								   1);
		cpu_cache_wbinval_range(start, end, 1);
	पूर्ण
	kunmap01(vto);
	local_irq_restore(flags);
पूर्ण

व्योम copy_from_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
			 अचिन्हित दीर्घ vaddr, व्योम *dst, व्योम *src, पूर्णांक len)
अणु
	अचिन्हित दीर्घ vto, flags;

	local_irq_save(flags);
	vto = kremap0(vaddr, page_to_phys(page));
	src = (व्योम *)(vto | (vaddr & (PAGE_SIZE - 1)));
	स_नकल(dst, src, len);
	kunmap01(vto);
	local_irq_restore(flags);
पूर्ण

व्योम flush_anon_page(काष्ठा vm_area_काष्ठा *vma,
		     काष्ठा page *page, अचिन्हित दीर्घ vaddr)
अणु
	अचिन्हित दीर्घ kaddr, flags, kपंचांगp;
	अगर (!PageAnon(page))
		वापस;

	अगर (vma->vm_mm != current->active_mm)
		वापस;

	local_irq_save(flags);
	अगर (vma->vm_flags & VM_EXEC)
		cpu_icache_inval_page(vaddr & PAGE_MASK);
	kaddr = (अचिन्हित दीर्घ)page_address(page);
	अगर (aliasing(vaddr, kaddr)) अणु
		kपंचांगp = kremap0(vaddr, page_to_phys(page));
		cpu_dcache_wbinval_page(kपंचांगp);
		kunmap01(kपंचांगp);
	पूर्ण
	local_irq_restore(flags);
पूर्ण

व्योम flush_kernel_dcache_page(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
	cpu_dcache_wbinval_page((अचिन्हित दीर्घ)page_address(page));
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(flush_kernel_dcache_page);

व्योम flush_kernel_vmap_range(व्योम *addr, पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
	cpu_dcache_wb_range((अचिन्हित दीर्घ)addr, (अचिन्हित दीर्घ)addr +  size);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(flush_kernel_vmap_range);

व्योम invalidate_kernel_vmap_range(व्योम *addr, पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
	cpu_dcache_inval_range((अचिन्हित दीर्घ)addr, (अचिन्हित दीर्घ)addr + size);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(invalidate_kernel_vmap_range);
#पूर्ण_अगर
