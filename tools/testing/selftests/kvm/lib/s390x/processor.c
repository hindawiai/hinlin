<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * KVM selftest s390x library code - CPU-related functions (page tables...)
 *
 * Copyright (C) 2019, Red Hat, Inc.
 */

#समावेश "processor.h"
#समावेश "kvm_util.h"
#समावेश "../kvm_util_internal.h"

#घोषणा KVM_GUEST_PAGE_TABLE_MIN_PADDR		0x180000

#घोषणा PAGES_PER_REGION 4

व्योम virt_pgd_alloc(काष्ठा kvm_vm *vm, uपूर्णांक32_t memslot)
अणु
	vm_paddr_t paddr;

	TEST_ASSERT(vm->page_size == 4096, "Unsupported page size: 0x%x",
		    vm->page_size);

	अगर (vm->pgd_created)
		वापस;

	paddr = vm_phy_pages_alloc(vm, PAGES_PER_REGION,
				   KVM_GUEST_PAGE_TABLE_MIN_PADDR, memslot);
	स_रखो(addr_gpa2hva(vm, paddr), 0xff, PAGES_PER_REGION * vm->page_size);

	vm->pgd = paddr;
	vm->pgd_created = true;
पूर्ण

/*
 * Allocate 4 pages क्रम a region/segment table (ri < 4), or one page क्रम
 * a page table (ri == 4). Returns a suitable region/segment table entry
 * which poपूर्णांकs to the freshly allocated pages.
 */
अटल uपूर्णांक64_t virt_alloc_region(काष्ठा kvm_vm *vm, पूर्णांक ri, uपूर्णांक32_t memslot)
अणु
	uपूर्णांक64_t taddr;

	taddr = vm_phy_pages_alloc(vm,  ri < 4 ? PAGES_PER_REGION : 1,
				   KVM_GUEST_PAGE_TABLE_MIN_PADDR, memslot);
	स_रखो(addr_gpa2hva(vm, taddr), 0xff, PAGES_PER_REGION * vm->page_size);

	वापस (taddr & REGION_ENTRY_ORIGIN)
		| (((4 - ri) << 2) & REGION_ENTRY_TYPE)
		| ((ri < 4 ? (PAGES_PER_REGION - 1) : 0) & REGION_ENTRY_LENGTH);
पूर्ण

व्योम virt_pg_map(काष्ठा kvm_vm *vm, uपूर्णांक64_t gva, uपूर्णांक64_t gpa,
		 uपूर्णांक32_t memslot)
अणु
	पूर्णांक ri, idx;
	uपूर्णांक64_t *entry;

	TEST_ASSERT((gva % vm->page_size) == 0,
		"Virtual address not on page boundary,\n"
		"  vaddr: 0x%lx vm->page_size: 0x%x",
		gva, vm->page_size);
	TEST_ASSERT(sparsebit_is_set(vm->vpages_valid,
		(gva >> vm->page_shअगरt)),
		"Invalid virtual address, vaddr: 0x%lx",
		gva);
	TEST_ASSERT((gpa % vm->page_size) == 0,
		"Physical address not on page boundary,\n"
		"  paddr: 0x%lx vm->page_size: 0x%x",
		gva, vm->page_size);
	TEST_ASSERT((gpa >> vm->page_shअगरt) <= vm->max_gfn,
		"Physical address beyond beyond maximum supported,\n"
		"  paddr: 0x%lx vm->max_gfn: 0x%lx vm->page_size: 0x%x",
		gva, vm->max_gfn, vm->page_size);

	/* Walk through region and segment tables */
	entry = addr_gpa2hva(vm, vm->pgd);
	क्रम (ri = 1; ri <= 4; ri++) अणु
		idx = (gva >> (64 - 11 * ri)) & 0x7ffu;
		अगर (entry[idx] & REGION_ENTRY_INVALID)
			entry[idx] = virt_alloc_region(vm, ri, memslot);
		entry = addr_gpa2hva(vm, entry[idx] & REGION_ENTRY_ORIGIN);
	पूर्ण

	/* Fill in page table entry */
	idx = (gva >> 12) & 0x0ffu;		/* page index */
	अगर (!(entry[idx] & PAGE_INVALID))
		ख_लिखो(मानक_त्रुटि,
			"WARNING: PTE for gpa=0x%"PRIx64" already set!\n", gpa);
	entry[idx] = gpa;
पूर्ण

vm_paddr_t addr_gva2gpa(काष्ठा kvm_vm *vm, vm_vaddr_t gva)
अणु
	पूर्णांक ri, idx;
	uपूर्णांक64_t *entry;

	TEST_ASSERT(vm->page_size == 4096, "Unsupported page size: 0x%x",
		    vm->page_size);

	entry = addr_gpa2hva(vm, vm->pgd);
	क्रम (ri = 1; ri <= 4; ri++) अणु
		idx = (gva >> (64 - 11 * ri)) & 0x7ffu;
		TEST_ASSERT(!(entry[idx] & REGION_ENTRY_INVALID),
			    "No region mapping for vm virtual address 0x%lx",
			    gva);
		entry = addr_gpa2hva(vm, entry[idx] & REGION_ENTRY_ORIGIN);
	पूर्ण

	idx = (gva >> 12) & 0x0ffu;		/* page index */

	TEST_ASSERT(!(entry[idx] & PAGE_INVALID),
		    "No page mapping for vm virtual address 0x%lx", gva);

	वापस (entry[idx] & ~0xffful) + (gva & 0xffful);
पूर्ण

अटल व्योम virt_dump_ptes(खाता *stream, काष्ठा kvm_vm *vm, uपूर्णांक8_t indent,
			   uपूर्णांक64_t ptea_start)
अणु
	uपूर्णांक64_t *pte, ptea;

	क्रम (ptea = ptea_start; ptea < ptea_start + 0x100 * 8; ptea += 8) अणु
		pte = addr_gpa2hva(vm, ptea);
		अगर (*pte & PAGE_INVALID)
			जारी;
		ख_लिखो(stream, "%*spte @ 0x%lx: 0x%016lx\n",
			indent, "", ptea, *pte);
	पूर्ण
पूर्ण

अटल व्योम virt_dump_region(खाता *stream, काष्ठा kvm_vm *vm, uपूर्णांक8_t indent,
			     uपूर्णांक64_t reg_tab_addr)
अणु
	uपूर्णांक64_t addr, *entry;

	क्रम (addr = reg_tab_addr; addr < reg_tab_addr + 0x400 * 8; addr += 8) अणु
		entry = addr_gpa2hva(vm, addr);
		अगर (*entry & REGION_ENTRY_INVALID)
			जारी;
		ख_लिखो(stream, "%*srt%lde @ 0x%lx: 0x%016lx\n",
			indent, "", 4 - ((*entry & REGION_ENTRY_TYPE) >> 2),
			addr, *entry);
		अगर (*entry & REGION_ENTRY_TYPE) अणु
			virt_dump_region(stream, vm, indent + 2,
					 *entry & REGION_ENTRY_ORIGIN);
		पूर्ण अन्यथा अणु
			virt_dump_ptes(stream, vm, indent + 2,
				       *entry & REGION_ENTRY_ORIGIN);
		पूर्ण
	पूर्ण
पूर्ण

व्योम virt_dump(खाता *stream, काष्ठा kvm_vm *vm, uपूर्णांक8_t indent)
अणु
	अगर (!vm->pgd_created)
		वापस;

	virt_dump_region(stream, vm, indent, vm->pgd);
पूर्ण

व्योम vm_vcpu_add_शेष(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, व्योम *guest_code)
अणु
	माप_प्रकार stack_size =  DEFAULT_STACK_PGS * getpagesize();
	uपूर्णांक64_t stack_vaddr;
	काष्ठा kvm_regs regs;
	काष्ठा kvm_sregs sregs;
	काष्ठा kvm_run *run;

	TEST_ASSERT(vm->page_size == 4096, "Unsupported page size: 0x%x",
		    vm->page_size);

	stack_vaddr = vm_vaddr_alloc(vm, stack_size,
				     DEFAULT_GUEST_STACK_VADDR_MIN, 0, 0);

	vm_vcpu_add(vm, vcpuid);

	/* Setup guest रेजिस्टरs */
	vcpu_regs_get(vm, vcpuid, &regs);
	regs.gprs[15] = stack_vaddr + (DEFAULT_STACK_PGS * getpagesize()) - 160;
	vcpu_regs_set(vm, vcpuid, &regs);

	vcpu_sregs_get(vm, vcpuid, &sregs);
	sregs.crs[0] |= 0x00040000;		/* Enable भग्नing poपूर्णांक regs */
	sregs.crs[1] = vm->pgd | 0xf;		/* Primary region table */
	vcpu_sregs_set(vm, vcpuid, &sregs);

	run = vcpu_state(vm, vcpuid);
	run->psw_mask = 0x0400000180000000ULL;  /* DAT enabled + 64 bit mode */
	run->psw_addr = (uपूर्णांकptr_t)guest_code;
पूर्ण

व्योम vcpu_args_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, अचिन्हित पूर्णांक num, ...)
अणु
	बहु_सूची ap;
	काष्ठा kvm_regs regs;
	पूर्णांक i;

	TEST_ASSERT(num >= 1 && num <= 5, "Unsupported number of args,\n"
		    "  num: %u\n",
		    num);

	बहु_शुरू(ap, num);
	vcpu_regs_get(vm, vcpuid, &regs);

	क्रम (i = 0; i < num; i++)
		regs.gprs[i + 2] = बहु_तर्क(ap, uपूर्णांक64_t);

	vcpu_regs_set(vm, vcpuid, &regs);
	बहु_पूर्ण(ap);
पूर्ण

व्योम vcpu_dump(खाता *stream, काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, uपूर्णांक8_t indent)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);

	अगर (!vcpu)
		वापस;

	ख_लिखो(stream, "%*spstate: psw: 0x%.16llx:0x%.16llx\n",
		indent, "", vcpu->state->psw_mask, vcpu->state->psw_addr);
पूर्ण

व्योम निश्चित_on_unhandled_exception(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
पूर्ण
