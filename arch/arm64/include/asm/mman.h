<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MMAN_H__
#घोषणा __ASM_MMAN_H__

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <uapi/यंत्र/mman.h>

अटल अंतरभूत अचिन्हित दीर्घ arch_calc_vm_prot_bits(अचिन्हित दीर्घ prot,
	अचिन्हित दीर्घ pkey __always_unused)
अणु
	अचिन्हित दीर्घ ret = 0;

	अगर (प्रणाली_supports_bti() && (prot & PROT_BTI))
		ret |= VM_ARM64_BTI;

	अगर (प्रणाली_supports_mte() && (prot & PROT_MTE))
		ret |= VM_MTE;

	वापस ret;
पूर्ण
#घोषणा arch_calc_vm_prot_bits(prot, pkey) arch_calc_vm_prot_bits(prot, pkey)

अटल अंतरभूत अचिन्हित दीर्घ arch_calc_vm_flag_bits(अचिन्हित दीर्घ flags)
अणु
	/*
	 * Only allow MTE on anonymous mappings as these are guaranteed to be
	 * backed by tags-capable memory. The vm_flags may be overridden by a
	 * fileप्रणाली supporting MTE (RAM-based).
	 */
	अगर (प्रणाली_supports_mte() && (flags & MAP_ANONYMOUS))
		वापस VM_MTE_ALLOWED;

	वापस 0;
पूर्ण
#घोषणा arch_calc_vm_flag_bits(flags) arch_calc_vm_flag_bits(flags)

अटल अंतरभूत pgprot_t arch_vm_get_page_prot(अचिन्हित दीर्घ vm_flags)
अणु
	pteval_t prot = 0;

	अगर (vm_flags & VM_ARM64_BTI)
		prot |= PTE_GP;

	/*
	 * There are two conditions required क्रम वापसing a Normal Tagged
	 * memory type: (1) the user requested it via PROT_MTE passed to
	 * mmap() or mprotect() and (2) the corresponding vma supports MTE. We
	 * रेजिस्टर (1) as VM_MTE in the vma->vm_flags and (2) as
	 * VM_MTE_ALLOWED. Note that the latter can only be set during the
	 * mmap() call since mprotect() करोes not accept MAP_* flags.
	 * Checking क्रम VM_MTE only is sufficient since arch_validate_flags()
	 * करोes not permit (VM_MTE & !VM_MTE_ALLOWED).
	 */
	अगर (vm_flags & VM_MTE)
		prot |= PTE_ATTRINDX(MT_NORMAL_TAGGED);

	वापस __pgprot(prot);
पूर्ण
#घोषणा arch_vm_get_page_prot(vm_flags) arch_vm_get_page_prot(vm_flags)

अटल अंतरभूत bool arch_validate_prot(अचिन्हित दीर्घ prot,
	अचिन्हित दीर्घ addr __always_unused)
अणु
	अचिन्हित दीर्घ supported = PROT_READ | PROT_WRITE | PROT_EXEC | PROT_SEM;

	अगर (प्रणाली_supports_bti())
		supported |= PROT_BTI;

	अगर (प्रणाली_supports_mte())
		supported |= PROT_MTE;

	वापस (prot & ~supported) == 0;
पूर्ण
#घोषणा arch_validate_prot(prot, addr) arch_validate_prot(prot, addr)

अटल अंतरभूत bool arch_validate_flags(अचिन्हित दीर्घ vm_flags)
अणु
	अगर (!प्रणाली_supports_mte())
		वापस true;

	/* only allow VM_MTE अगर VM_MTE_ALLOWED has been set previously */
	वापस !(vm_flags & VM_MTE) || (vm_flags & VM_MTE_ALLOWED);
पूर्ण
#घोषणा arch_validate_flags(vm_flags) arch_validate_flags(vm_flags)

#पूर्ण_अगर /* ! __ASM_MMAN_H__ */
