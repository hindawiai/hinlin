<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Google LLC
 * Author: Quentin Perret <qperret@google.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/kvm_pgtable.h>
#समावेश <यंत्र/spectre.h>

#समावेश <nvhe/early_भाग.स>
#समावेश <nvhe/gfp.h>
#समावेश <nvhe/memory.h>
#समावेश <nvhe/mm.h>
#समावेश <nvhe/spinlock.h>

काष्ठा kvm_pgtable pkvm_pgtable;
hyp_spinlock_t pkvm_pgd_lock;
u64 __io_map_base;

काष्ठा memblock_region hyp_memory[HYP_MEMBLOCK_REGIONS];
अचिन्हित पूर्णांक hyp_memblock_nr;

पूर्णांक __pkvm_create_mappings(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
			  अचिन्हित दीर्घ phys, क्रमागत kvm_pgtable_prot prot)
अणु
	पूर्णांक err;

	hyp_spin_lock(&pkvm_pgd_lock);
	err = kvm_pgtable_hyp_map(&pkvm_pgtable, start, size, phys, prot);
	hyp_spin_unlock(&pkvm_pgd_lock);

	वापस err;
पूर्ण

अचिन्हित दीर्घ __pkvm_create_निजी_mapping(phys_addr_t phys, माप_प्रकार size,
					    क्रमागत kvm_pgtable_prot prot)
अणु
	अचिन्हित दीर्घ addr;
	पूर्णांक err;

	hyp_spin_lock(&pkvm_pgd_lock);

	size = PAGE_ALIGN(size + offset_in_page(phys));
	addr = __io_map_base;
	__io_map_base += size;

	/* Are we overflowing on the vmemmap ? */
	अगर (__io_map_base > __hyp_vmemmap) अणु
		__io_map_base -= size;
		addr = (अचिन्हित दीर्घ)ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	err = kvm_pgtable_hyp_map(&pkvm_pgtable, addr, size, phys, prot);
	अगर (err) अणु
		addr = (अचिन्हित दीर्घ)ERR_PTR(err);
		जाओ out;
	पूर्ण

	addr = addr + offset_in_page(phys);
out:
	hyp_spin_unlock(&pkvm_pgd_lock);

	वापस addr;
पूर्ण

पूर्णांक pkvm_create_mappings(व्योम *from, व्योम *to, क्रमागत kvm_pgtable_prot prot)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)from;
	अचिन्हित दीर्घ end = (अचिन्हित दीर्घ)to;
	अचिन्हित दीर्घ virt_addr;
	phys_addr_t phys;

	start = start & PAGE_MASK;
	end = PAGE_ALIGN(end);

	क्रम (virt_addr = start; virt_addr < end; virt_addr += PAGE_SIZE) अणु
		पूर्णांक err;

		phys = hyp_virt_to_phys((व्योम *)virt_addr);
		err = __pkvm_create_mappings(virt_addr, PAGE_SIZE, phys, prot);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hyp_back_vmemmap(phys_addr_t phys, अचिन्हित दीर्घ size, phys_addr_t back)
अणु
	अचिन्हित दीर्घ start, end;

	hyp_vmemmap_range(phys, size, &start, &end);

	वापस __pkvm_create_mappings(start, end - start, back, PAGE_HYP);
पूर्ण

अटल व्योम *__hyp_bp_vect_base;
पूर्णांक pkvm_cpu_set_vector(क्रमागत arm64_hyp_spectre_vector slot)
अणु
	व्योम *vector;

	चयन (slot) अणु
	हाल HYP_VECTOR_सूचीECT: अणु
		vector = __kvm_hyp_vector;
		अवरोध;
	पूर्ण
	हाल HYP_VECTOR_SPECTRE_सूचीECT: अणु
		vector = __bp_harden_hyp_vecs;
		अवरोध;
	पूर्ण
	हाल HYP_VECTOR_INसूचीECT:
	हाल HYP_VECTOR_SPECTRE_INसूचीECT: अणु
		vector = (व्योम *)__hyp_bp_vect_base;
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	vector = __kvm_vector_slot2addr(vector, slot);
	*this_cpu_ptr(&kvm_hyp_vector) = (अचिन्हित दीर्घ)vector;

	वापस 0;
पूर्ण

पूर्णांक hyp_map_vectors(व्योम)
अणु
	phys_addr_t phys;
	व्योम *bp_base;

	अगर (!cpus_have_स्थिर_cap(ARM64_SPECTRE_V3A))
		वापस 0;

	phys = __hyp_pa(__bp_harden_hyp_vecs);
	bp_base = (व्योम *)__pkvm_create_निजी_mapping(phys,
							__BP_HARDEN_HYP_VECS_SZ,
							PAGE_HYP_EXEC);
	अगर (IS_ERR_OR_शून्य(bp_base))
		वापस PTR_ERR(bp_base);

	__hyp_bp_vect_base = bp_base;

	वापस 0;
पूर्ण

पूर्णांक hyp_create_idmap(u32 hyp_va_bits)
अणु
	अचिन्हित दीर्घ start, end;

	start = hyp_virt_to_phys((व्योम *)__hyp_idmap_text_start);
	start = ALIGN_DOWN(start, PAGE_SIZE);

	end = hyp_virt_to_phys((व्योम *)__hyp_idmap_text_end);
	end = ALIGN(end, PAGE_SIZE);

	/*
	 * One half of the VA space is reserved to linearly map portions of
	 * memory -- see va_layout.c क्रम more details. The other half of the VA
	 * space contains the trampoline page, and needs some care. Split that
	 * second half in two and find the quarter of VA space not conflicting
	 * with the idmap to place the IOs and the vmemmap. IOs use the lower
	 * half of the quarter and the vmemmap the upper half.
	 */
	__io_map_base = start & BIT(hyp_va_bits - 2);
	__io_map_base ^= BIT(hyp_va_bits - 2);
	__hyp_vmemmap = __io_map_base | BIT(hyp_va_bits - 3);

	वापस __pkvm_create_mappings(start, end - start, start, PAGE_HYP_EXEC);
पूर्ण
