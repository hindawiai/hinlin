<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AArch64 code
 *
 * Copyright (C) 2018, Red Hat, Inc.
 */

#समावेश <linux/compiler.h>

#समावेश "kvm_util.h"
#समावेश "../kvm_util_internal.h"
#समावेश "processor.h"

#घोषणा KVM_GUEST_PAGE_TABLE_MIN_PADDR		0x180000
#घोषणा DEFAULT_ARM64_GUEST_STACK_VADDR_MIN	0xac0000

अटल uपूर्णांक64_t page_align(काष्ठा kvm_vm *vm, uपूर्णांक64_t v)
अणु
	वापस (v + vm->page_size) & ~(vm->page_size - 1);
पूर्ण

अटल uपूर्णांक64_t pgd_index(काष्ठा kvm_vm *vm, vm_vaddr_t gva)
अणु
	अचिन्हित पूर्णांक shअगरt = (vm->pgtable_levels - 1) * (vm->page_shअगरt - 3) + vm->page_shअगरt;
	uपूर्णांक64_t mask = (1UL << (vm->va_bits - shअगरt)) - 1;

	वापस (gva >> shअगरt) & mask;
पूर्ण

अटल uपूर्णांक64_t pud_index(काष्ठा kvm_vm *vm, vm_vaddr_t gva)
अणु
	अचिन्हित पूर्णांक shअगरt = 2 * (vm->page_shअगरt - 3) + vm->page_shअगरt;
	uपूर्णांक64_t mask = (1UL << (vm->page_shअगरt - 3)) - 1;

	TEST_ASSERT(vm->pgtable_levels == 4,
		"Mode %d does not have 4 page table levels", vm->mode);

	वापस (gva >> shअगरt) & mask;
पूर्ण

अटल uपूर्णांक64_t pmd_index(काष्ठा kvm_vm *vm, vm_vaddr_t gva)
अणु
	अचिन्हित पूर्णांक shअगरt = (vm->page_shअगरt - 3) + vm->page_shअगरt;
	uपूर्णांक64_t mask = (1UL << (vm->page_shअगरt - 3)) - 1;

	TEST_ASSERT(vm->pgtable_levels >= 3,
		"Mode %d does not have >= 3 page table levels", vm->mode);

	वापस (gva >> shअगरt) & mask;
पूर्ण

अटल uपूर्णांक64_t pte_index(काष्ठा kvm_vm *vm, vm_vaddr_t gva)
अणु
	uपूर्णांक64_t mask = (1UL << (vm->page_shअगरt - 3)) - 1;
	वापस (gva >> vm->page_shअगरt) & mask;
पूर्ण

अटल uपूर्णांक64_t pte_addr(काष्ठा kvm_vm *vm, uपूर्णांक64_t entry)
अणु
	uपूर्णांक64_t mask = ((1UL << (vm->va_bits - vm->page_shअगरt)) - 1) << vm->page_shअगरt;
	वापस entry & mask;
पूर्ण

अटल uपूर्णांक64_t ptrs_per_pgd(काष्ठा kvm_vm *vm)
अणु
	अचिन्हित पूर्णांक shअगरt = (vm->pgtable_levels - 1) * (vm->page_shअगरt - 3) + vm->page_shअगरt;
	वापस 1 << (vm->va_bits - shअगरt);
पूर्ण

अटल uपूर्णांक64_t __maybe_unused ptrs_per_pte(काष्ठा kvm_vm *vm)
अणु
	वापस 1 << (vm->page_shअगरt - 3);
पूर्ण

व्योम virt_pgd_alloc(काष्ठा kvm_vm *vm, uपूर्णांक32_t pgd_memslot)
अणु
	अगर (!vm->pgd_created) अणु
		vm_paddr_t paddr = vm_phy_pages_alloc(vm,
			page_align(vm, ptrs_per_pgd(vm) * 8) / vm->page_size,
			KVM_GUEST_PAGE_TABLE_MIN_PADDR, pgd_memslot);
		vm->pgd = paddr;
		vm->pgd_created = true;
	पूर्ण
पूर्ण

व्योम _virt_pg_map(काष्ठा kvm_vm *vm, uपूर्णांक64_t vaddr, uपूर्णांक64_t paddr,
		  uपूर्णांक32_t pgd_memslot, uपूर्णांक64_t flags)
अणु
	uपूर्णांक8_t attr_idx = flags & 7;
	uपूर्णांक64_t *ptep;

	TEST_ASSERT((vaddr % vm->page_size) == 0,
		"Virtual address not on page boundary,\n"
		"  vaddr: 0x%lx vm->page_size: 0x%x", vaddr, vm->page_size);
	TEST_ASSERT(sparsebit_is_set(vm->vpages_valid,
		(vaddr >> vm->page_shअगरt)),
		"Invalid virtual address, vaddr: 0x%lx", vaddr);
	TEST_ASSERT((paddr % vm->page_size) == 0,
		"Physical address not on page boundary,\n"
		"  paddr: 0x%lx vm->page_size: 0x%x", paddr, vm->page_size);
	TEST_ASSERT((paddr >> vm->page_shअगरt) <= vm->max_gfn,
		"Physical address beyond beyond maximum supported,\n"
		"  paddr: 0x%lx vm->max_gfn: 0x%lx vm->page_size: 0x%x",
		paddr, vm->max_gfn, vm->page_size);

	ptep = addr_gpa2hva(vm, vm->pgd) + pgd_index(vm, vaddr) * 8;
	अगर (!*ptep) अणु
		*ptep = vm_phy_page_alloc(vm, KVM_GUEST_PAGE_TABLE_MIN_PADDR, pgd_memslot);
		*ptep |= 3;
	पूर्ण

	चयन (vm->pgtable_levels) अणु
	हाल 4:
		ptep = addr_gpa2hva(vm, pte_addr(vm, *ptep)) + pud_index(vm, vaddr) * 8;
		अगर (!*ptep) अणु
			*ptep = vm_phy_page_alloc(vm, KVM_GUEST_PAGE_TABLE_MIN_PADDR, pgd_memslot);
			*ptep |= 3;
		पूर्ण
		/* fall through */
	हाल 3:
		ptep = addr_gpa2hva(vm, pte_addr(vm, *ptep)) + pmd_index(vm, vaddr) * 8;
		अगर (!*ptep) अणु
			*ptep = vm_phy_page_alloc(vm, KVM_GUEST_PAGE_TABLE_MIN_PADDR, pgd_memslot);
			*ptep |= 3;
		पूर्ण
		/* fall through */
	हाल 2:
		ptep = addr_gpa2hva(vm, pte_addr(vm, *ptep)) + pte_index(vm, vaddr) * 8;
		अवरोध;
	शेष:
		TEST_FAIL("Page table levels must be 2, 3, or 4");
	पूर्ण

	*ptep = paddr | 3;
	*ptep |= (attr_idx << 2) | (1 << 10) /* Access Flag */;
पूर्ण

व्योम virt_pg_map(काष्ठा kvm_vm *vm, uपूर्णांक64_t vaddr, uपूर्णांक64_t paddr,
		 uपूर्णांक32_t pgd_memslot)
अणु
	uपूर्णांक64_t attr_idx = 4; /* NORMAL (See DEFAULT_MAIR_EL1) */

	_virt_pg_map(vm, vaddr, paddr, pgd_memslot, attr_idx);
पूर्ण

vm_paddr_t addr_gva2gpa(काष्ठा kvm_vm *vm, vm_vaddr_t gva)
अणु
	uपूर्णांक64_t *ptep;

	अगर (!vm->pgd_created)
		जाओ unmapped_gva;

	ptep = addr_gpa2hva(vm, vm->pgd) + pgd_index(vm, gva) * 8;
	अगर (!ptep)
		जाओ unmapped_gva;

	चयन (vm->pgtable_levels) अणु
	हाल 4:
		ptep = addr_gpa2hva(vm, pte_addr(vm, *ptep)) + pud_index(vm, gva) * 8;
		अगर (!ptep)
			जाओ unmapped_gva;
		/* fall through */
	हाल 3:
		ptep = addr_gpa2hva(vm, pte_addr(vm, *ptep)) + pmd_index(vm, gva) * 8;
		अगर (!ptep)
			जाओ unmapped_gva;
		/* fall through */
	हाल 2:
		ptep = addr_gpa2hva(vm, pte_addr(vm, *ptep)) + pte_index(vm, gva) * 8;
		अगर (!ptep)
			जाओ unmapped_gva;
		अवरोध;
	शेष:
		TEST_FAIL("Page table levels must be 2, 3, or 4");
	पूर्ण

	वापस pte_addr(vm, *ptep) + (gva & (vm->page_size - 1));

unmapped_gva:
	TEST_FAIL("No mapping for vm virtual address, gva: 0x%lx", gva);
	निकास(1);
पूर्ण

अटल व्योम pte_dump(खाता *stream, काष्ठा kvm_vm *vm, uपूर्णांक8_t indent, uपूर्णांक64_t page, पूर्णांक level)
अणु
#अगर_घोषित DEBUG
	अटल स्थिर अक्षर * स्थिर type[] = अणु "", "pud", "pmd", "pte" पूर्ण;
	uपूर्णांक64_t pte, *ptep;

	अगर (level == 4)
		वापस;

	क्रम (pte = page; pte < page + ptrs_per_pte(vm) * 8; pte += 8) अणु
		ptep = addr_gpa2hva(vm, pte);
		अगर (!*ptep)
			जारी;
		ख_लिखो(stream, "%*s%s: %lx: %lx at %p\n", indent, "", type[level], pte, *ptep, ptep);
		pte_dump(stream, vm, indent + 1, pte_addr(vm, *ptep), level + 1);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम virt_dump(खाता *stream, काष्ठा kvm_vm *vm, uपूर्णांक8_t indent)
अणु
	पूर्णांक level = 4 - (vm->pgtable_levels - 1);
	uपूर्णांक64_t pgd, *ptep;

	अगर (!vm->pgd_created)
		वापस;

	क्रम (pgd = vm->pgd; pgd < vm->pgd + ptrs_per_pgd(vm) * 8; pgd += 8) अणु
		ptep = addr_gpa2hva(vm, pgd);
		अगर (!*ptep)
			जारी;
		ख_लिखो(stream, "%*spgd: %lx: %lx at %p\n", indent, "", pgd, *ptep, ptep);
		pte_dump(stream, vm, indent + 1, pte_addr(vm, *ptep), level);
	पूर्ण
पूर्ण

व्योम aarch64_vcpu_setup(काष्ठा kvm_vm *vm, पूर्णांक vcpuid, काष्ठा kvm_vcpu_init *init)
अणु
	काष्ठा kvm_vcpu_init शेष_init = अणु .target = -1, पूर्ण;
	uपूर्णांक64_t sctlr_el1, tcr_el1;

	अगर (!init)
		init = &शेष_init;

	अगर (init->target == -1) अणु
		काष्ठा kvm_vcpu_init preferred;
		vm_ioctl(vm, KVM_ARM_PREFERRED_TARGET, &preferred);
		init->target = preferred.target;
	पूर्ण

	vcpu_ioctl(vm, vcpuid, KVM_ARM_VCPU_INIT, init);

	/*
	 * Enable FP/ASIMD to aव्योम trapping when accessing Q0-Q15
	 * रेजिस्टरs, which the variable argument list macros करो.
	 */
	set_reg(vm, vcpuid, ARM64_SYS_REG(CPACR_EL1), 3 << 20);

	get_reg(vm, vcpuid, ARM64_SYS_REG(SCTLR_EL1), &sctlr_el1);
	get_reg(vm, vcpuid, ARM64_SYS_REG(TCR_EL1), &tcr_el1);

	चयन (vm->mode) अणु
	हाल VM_MODE_P52V48_4K:
		TEST_FAIL("AArch64 does not support 4K sized pages "
			  "with 52-bit physical address ranges");
	हाल VM_MODE_PXXV48_4K:
		TEST_FAIL("AArch64 does not support 4K sized pages "
			  "with ANY-bit physical address ranges");
	हाल VM_MODE_P52V48_64K:
		tcr_el1 |= 1ul << 14; /* TG0 = 64KB */
		tcr_el1 |= 6ul << 32; /* IPS = 52 bits */
		अवरोध;
	हाल VM_MODE_P48V48_4K:
		tcr_el1 |= 0ul << 14; /* TG0 = 4KB */
		tcr_el1 |= 5ul << 32; /* IPS = 48 bits */
		अवरोध;
	हाल VM_MODE_P48V48_64K:
		tcr_el1 |= 1ul << 14; /* TG0 = 64KB */
		tcr_el1 |= 5ul << 32; /* IPS = 48 bits */
		अवरोध;
	हाल VM_MODE_P40V48_4K:
		tcr_el1 |= 0ul << 14; /* TG0 = 4KB */
		tcr_el1 |= 2ul << 32; /* IPS = 40 bits */
		अवरोध;
	हाल VM_MODE_P40V48_64K:
		tcr_el1 |= 1ul << 14; /* TG0 = 64KB */
		tcr_el1 |= 2ul << 32; /* IPS = 40 bits */
		अवरोध;
	शेष:
		TEST_FAIL("Unknown guest mode, mode: 0x%x", vm->mode);
	पूर्ण

	sctlr_el1 |= (1 << 0) | (1 << 2) | (1 << 12) /* M | C | I */;
	/* TCR_EL1 |= IRGN0:WBWA | ORGN0:WBWA | SH0:Inner-Shareable */;
	tcr_el1 |= (1 << 8) | (1 << 10) | (3 << 12);
	tcr_el1 |= (64 - vm->va_bits) /* T0SZ */;

	set_reg(vm, vcpuid, ARM64_SYS_REG(SCTLR_EL1), sctlr_el1);
	set_reg(vm, vcpuid, ARM64_SYS_REG(TCR_EL1), tcr_el1);
	set_reg(vm, vcpuid, ARM64_SYS_REG(MAIR_EL1), DEFAULT_MAIR_EL1);
	set_reg(vm, vcpuid, ARM64_SYS_REG(TTBR0_EL1), vm->pgd);
पूर्ण

व्योम vcpu_dump(खाता *stream, काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, uपूर्णांक8_t indent)
अणु
	uपूर्णांक64_t pstate, pc;

	get_reg(vm, vcpuid, ARM64_CORE_REG(regs.pstate), &pstate);
	get_reg(vm, vcpuid, ARM64_CORE_REG(regs.pc), &pc);

	ख_लिखो(stream, "%*spstate: 0x%.16lx pc: 0x%.16lx\n",
		indent, "", pstate, pc);
पूर्ण

व्योम aarch64_vcpu_add_शेष(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
			      काष्ठा kvm_vcpu_init *init, व्योम *guest_code)
अणु
	माप_प्रकार stack_size = vm->page_size == 4096 ?
					DEFAULT_STACK_PGS * vm->page_size :
					vm->page_size;
	uपूर्णांक64_t stack_vaddr = vm_vaddr_alloc(vm, stack_size,
					DEFAULT_ARM64_GUEST_STACK_VADDR_MIN, 0, 0);

	vm_vcpu_add(vm, vcpuid);
	aarch64_vcpu_setup(vm, vcpuid, init);

	set_reg(vm, vcpuid, ARM64_CORE_REG(sp_el1), stack_vaddr + stack_size);
	set_reg(vm, vcpuid, ARM64_CORE_REG(regs.pc), (uपूर्णांक64_t)guest_code);
पूर्ण

व्योम vm_vcpu_add_शेष(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, व्योम *guest_code)
अणु
	aarch64_vcpu_add_शेष(vm, vcpuid, शून्य, guest_code);
पूर्ण

व्योम vcpu_args_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, अचिन्हित पूर्णांक num, ...)
अणु
	बहु_सूची ap;
	पूर्णांक i;

	TEST_ASSERT(num >= 1 && num <= 8, "Unsupported number of args,\n"
		    "  num: %u\n", num);

	बहु_शुरू(ap, num);

	क्रम (i = 0; i < num; i++) अणु
		set_reg(vm, vcpuid, ARM64_CORE_REG(regs.regs[i]),
			बहु_तर्क(ap, uपूर्णांक64_t));
	पूर्ण

	बहु_पूर्ण(ap);
पूर्ण

व्योम निश्चित_on_unhandled_exception(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
पूर्ण
