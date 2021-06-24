<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __KVM_HYP_MM_H
#घोषणा __KVM_HYP_MM_H

#समावेश <यंत्र/kvm_pgtable.h>
#समावेश <यंत्र/spectre.h>
#समावेश <linux/memblock.h>
#समावेश <linux/types.h>

#समावेश <nvhe/memory.h>
#समावेश <nvhe/spinlock.h>

#घोषणा HYP_MEMBLOCK_REGIONS 128
बाह्य काष्ठा memblock_region kvm_nvhe_sym(hyp_memory)[];
बाह्य अचिन्हित पूर्णांक kvm_nvhe_sym(hyp_memblock_nr);
बाह्य काष्ठा kvm_pgtable pkvm_pgtable;
बाह्य hyp_spinlock_t pkvm_pgd_lock;
बाह्य काष्ठा hyp_pool hpool;
बाह्य u64 __io_map_base;

पूर्णांक hyp_create_idmap(u32 hyp_va_bits);
पूर्णांक hyp_map_vectors(व्योम);
पूर्णांक hyp_back_vmemmap(phys_addr_t phys, अचिन्हित दीर्घ size, phys_addr_t back);
पूर्णांक pkvm_cpu_set_vector(क्रमागत arm64_hyp_spectre_vector slot);
पूर्णांक pkvm_create_mappings(व्योम *from, व्योम *to, क्रमागत kvm_pgtable_prot prot);
पूर्णांक __pkvm_create_mappings(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
			   अचिन्हित दीर्घ phys, क्रमागत kvm_pgtable_prot prot);
अचिन्हित दीर्घ __pkvm_create_निजी_mapping(phys_addr_t phys, माप_प्रकार size,
					    क्रमागत kvm_pgtable_prot prot);

अटल अंतरभूत व्योम hyp_vmemmap_range(phys_addr_t phys, अचिन्हित दीर्घ size,
				     अचिन्हित दीर्घ *start, अचिन्हित दीर्घ *end)
अणु
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;
	काष्ठा hyp_page *p = hyp_phys_to_page(phys);

	*start = (अचिन्हित दीर्घ)p;
	*end = *start + nr_pages * माप(काष्ठा hyp_page);
	*start = ALIGN_DOWN(*start, PAGE_SIZE);
	*end = ALIGN(*end, PAGE_SIZE);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __hyp_pgtable_max_pages(अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ total = 0, i;

	/* Provision the worst हाल scenario */
	क्रम (i = 0; i < KVM_PGTABLE_MAX_LEVELS; i++) अणु
		nr_pages = DIV_ROUND_UP(nr_pages, PTRS_PER_PTE);
		total += nr_pages;
	पूर्ण

	वापस total;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __hyp_pgtable_total_pages(व्योम)
अणु
	अचिन्हित दीर्घ res = 0, i;

	/* Cover all of memory with page-granularity */
	क्रम (i = 0; i < kvm_nvhe_sym(hyp_memblock_nr); i++) अणु
		काष्ठा memblock_region *reg = &kvm_nvhe_sym(hyp_memory)[i];
		res += __hyp_pgtable_max_pages(reg->size >> PAGE_SHIFT);
	पूर्ण

	वापस res;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hyp_s1_pgtable_pages(व्योम)
अणु
	अचिन्हित दीर्घ res;

	res = __hyp_pgtable_total_pages();

	/* Allow 1 GiB क्रम निजी mappings */
	res += __hyp_pgtable_max_pages(SZ_1G >> PAGE_SHIFT);

	वापस res;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ host_s2_mem_pgtable_pages(व्योम)
अणु
	/*
	 * Include an extra 16 pages to safely upper-bound the worst हाल of
	 * concatenated pgds.
	 */
	वापस __hyp_pgtable_total_pages() + 16;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ host_s2_dev_pgtable_pages(व्योम)
अणु
	/* Allow 1 GiB क्रम MMIO mappings */
	वापस __hyp_pgtable_max_pages(SZ_1G >> PAGE_SHIFT);
पूर्ण

#पूर्ण_अगर /* __KVM_HYP_MM_H */
