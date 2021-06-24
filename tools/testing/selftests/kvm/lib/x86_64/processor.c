<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tools/testing/selftests/kvm/lib/x86_64/processor.c
 *
 * Copyright (C) 2018, Google LLC.
 */

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "../kvm_util_internal.h"
#समावेश "processor.h"

#अगर_अघोषित NUM_INTERRUPTS
#घोषणा NUM_INTERRUPTS 256
#पूर्ण_अगर

#घोषणा DEFAULT_CODE_SELECTOR 0x8
#घोषणा DEFAULT_DATA_SELECTOR 0x10

/* Minimum physical address used क्रम भव translation tables. */
#घोषणा KVM_GUEST_PAGE_TABLE_MIN_PADDR 0x180000

vm_vaddr_t exception_handlers;

/* Virtual translation table काष्ठाure declarations */
काष्ठा pageMapL4Entry अणु
	uपूर्णांक64_t present:1;
	uपूर्णांक64_t writable:1;
	uपूर्णांक64_t user:1;
	uपूर्णांक64_t ग_लिखो_through:1;
	uपूर्णांक64_t cache_disable:1;
	uपूर्णांक64_t accessed:1;
	uपूर्णांक64_t ignored_06:1;
	uपूर्णांक64_t page_size:1;
	uपूर्णांक64_t ignored_11_08:4;
	uपूर्णांक64_t address:40;
	uपूर्णांक64_t ignored_62_52:11;
	uपूर्णांक64_t execute_disable:1;
पूर्ण;

काष्ठा pageDirectoryPoपूर्णांकerEntry अणु
	uपूर्णांक64_t present:1;
	uपूर्णांक64_t writable:1;
	uपूर्णांक64_t user:1;
	uपूर्णांक64_t ग_लिखो_through:1;
	uपूर्णांक64_t cache_disable:1;
	uपूर्णांक64_t accessed:1;
	uपूर्णांक64_t ignored_06:1;
	uपूर्णांक64_t page_size:1;
	uपूर्णांक64_t ignored_11_08:4;
	uपूर्णांक64_t address:40;
	uपूर्णांक64_t ignored_62_52:11;
	uपूर्णांक64_t execute_disable:1;
पूर्ण;

काष्ठा pageDirectoryEntry अणु
	uपूर्णांक64_t present:1;
	uपूर्णांक64_t writable:1;
	uपूर्णांक64_t user:1;
	uपूर्णांक64_t ग_लिखो_through:1;
	uपूर्णांक64_t cache_disable:1;
	uपूर्णांक64_t accessed:1;
	uपूर्णांक64_t ignored_06:1;
	uपूर्णांक64_t page_size:1;
	uपूर्णांक64_t ignored_11_08:4;
	uपूर्णांक64_t address:40;
	uपूर्णांक64_t ignored_62_52:11;
	uपूर्णांक64_t execute_disable:1;
पूर्ण;

काष्ठा pageTableEntry अणु
	uपूर्णांक64_t present:1;
	uपूर्णांक64_t writable:1;
	uपूर्णांक64_t user:1;
	uपूर्णांक64_t ग_लिखो_through:1;
	uपूर्णांक64_t cache_disable:1;
	uपूर्णांक64_t accessed:1;
	uपूर्णांक64_t dirty:1;
	uपूर्णांक64_t reserved_07:1;
	uपूर्णांक64_t global:1;
	uपूर्णांक64_t ignored_11_09:3;
	uपूर्णांक64_t address:40;
	uपूर्णांक64_t ignored_62_52:11;
	uपूर्णांक64_t execute_disable:1;
पूर्ण;

व्योम regs_dump(खाता *stream, काष्ठा kvm_regs *regs,
	       uपूर्णांक8_t indent)
अणु
	ख_लिखो(stream, "%*srax: 0x%.16llx rbx: 0x%.16llx "
		"rcx: 0x%.16llx rdx: 0x%.16llx\n",
		indent, "",
		regs->rax, regs->rbx, regs->rcx, regs->rdx);
	ख_लिखो(stream, "%*srsi: 0x%.16llx rdi: 0x%.16llx "
		"rsp: 0x%.16llx rbp: 0x%.16llx\n",
		indent, "",
		regs->rsi, regs->rdi, regs->rsp, regs->rbp);
	ख_लिखो(stream, "%*sr8:  0x%.16llx r9:  0x%.16llx "
		"r10: 0x%.16llx r11: 0x%.16llx\n",
		indent, "",
		regs->r8, regs->r9, regs->r10, regs->r11);
	ख_लिखो(stream, "%*sr12: 0x%.16llx r13: 0x%.16llx "
		"r14: 0x%.16llx r15: 0x%.16llx\n",
		indent, "",
		regs->r12, regs->r13, regs->r14, regs->r15);
	ख_लिखो(stream, "%*srip: 0x%.16llx rfl: 0x%.16llx\n",
		indent, "",
		regs->rip, regs->rflags);
पूर्ण

/*
 * Segment Dump
 *
 * Input Args:
 *   stream  - Output खाता stream
 *   segment - KVM segment
 *   indent  - Left margin indent amount
 *
 * Output Args: None
 *
 * Return: None
 *
 * Dumps the state of the KVM segment given by @segment, to the खाता stream
 * given by @stream.
 */
अटल व्योम segment_dump(खाता *stream, काष्ठा kvm_segment *segment,
			 uपूर्णांक8_t indent)
अणु
	ख_लिखो(stream, "%*sbase: 0x%.16llx limit: 0x%.8x "
		"selector: 0x%.4x type: 0x%.2x\n",
		indent, "", segment->base, segment->limit,
		segment->selector, segment->type);
	ख_लिखो(stream, "%*spresent: 0x%.2x dpl: 0x%.2x "
		"db: 0x%.2x s: 0x%.2x l: 0x%.2x\n",
		indent, "", segment->present, segment->dpl,
		segment->db, segment->s, segment->l);
	ख_लिखो(stream, "%*sg: 0x%.2x avl: 0x%.2x "
		"unusable: 0x%.2x padding: 0x%.2x\n",
		indent, "", segment->g, segment->avl,
		segment->unusable, segment->padding);
पूर्ण

/*
 * dtable Dump
 *
 * Input Args:
 *   stream - Output खाता stream
 *   dtable - KVM dtable
 *   indent - Left margin indent amount
 *
 * Output Args: None
 *
 * Return: None
 *
 * Dumps the state of the KVM dtable given by @dtable, to the खाता stream
 * given by @stream.
 */
अटल व्योम dtable_dump(खाता *stream, काष्ठा kvm_dtable *dtable,
			uपूर्णांक8_t indent)
अणु
	ख_लिखो(stream, "%*sbase: 0x%.16llx limit: 0x%.4x "
		"padding: 0x%.4x 0x%.4x 0x%.4x\n",
		indent, "", dtable->base, dtable->limit,
		dtable->padding[0], dtable->padding[1], dtable->padding[2]);
पूर्ण

व्योम sregs_dump(खाता *stream, काष्ठा kvm_sregs *sregs,
		uपूर्णांक8_t indent)
अणु
	अचिन्हित पूर्णांक i;

	ख_लिखो(stream, "%*scs:\n", indent, "");
	segment_dump(stream, &sregs->cs, indent + 2);
	ख_लिखो(stream, "%*sds:\n", indent, "");
	segment_dump(stream, &sregs->ds, indent + 2);
	ख_लिखो(stream, "%*ses:\n", indent, "");
	segment_dump(stream, &sregs->es, indent + 2);
	ख_लिखो(stream, "%*sfs:\n", indent, "");
	segment_dump(stream, &sregs->fs, indent + 2);
	ख_लिखो(stream, "%*sgs:\n", indent, "");
	segment_dump(stream, &sregs->gs, indent + 2);
	ख_लिखो(stream, "%*sss:\n", indent, "");
	segment_dump(stream, &sregs->ss, indent + 2);
	ख_लिखो(stream, "%*str:\n", indent, "");
	segment_dump(stream, &sregs->tr, indent + 2);
	ख_लिखो(stream, "%*sldt:\n", indent, "");
	segment_dump(stream, &sregs->ldt, indent + 2);

	ख_लिखो(stream, "%*sgdt:\n", indent, "");
	dtable_dump(stream, &sregs->gdt, indent + 2);
	ख_लिखो(stream, "%*sidt:\n", indent, "");
	dtable_dump(stream, &sregs->idt, indent + 2);

	ख_लिखो(stream, "%*scr0: 0x%.16llx cr2: 0x%.16llx "
		"cr3: 0x%.16llx cr4: 0x%.16llx\n",
		indent, "",
		sregs->cr0, sregs->cr2, sregs->cr3, sregs->cr4);
	ख_लिखो(stream, "%*scr8: 0x%.16llx efer: 0x%.16llx "
		"apic_base: 0x%.16llx\n",
		indent, "",
		sregs->cr8, sregs->efer, sregs->apic_base);

	ख_लिखो(stream, "%*sinterrupt_bitmap:\n", indent, "");
	क्रम (i = 0; i < (KVM_NR_INTERRUPTS + 63) / 64; i++) अणु
		ख_लिखो(stream, "%*s%.16llx\n", indent + 2, "",
			sregs->पूर्णांकerrupt_biपंचांगap[i]);
	पूर्ण
पूर्ण

व्योम virt_pgd_alloc(काष्ठा kvm_vm *vm, uपूर्णांक32_t pgd_memslot)
अणु
	TEST_ASSERT(vm->mode == VM_MODE_PXXV48_4K, "Attempt to use "
		"unknown or unsupported guest mode, mode: 0x%x", vm->mode);

	/* If needed, create page map l4 table. */
	अगर (!vm->pgd_created) अणु
		vm_paddr_t paddr = vm_phy_page_alloc(vm,
			KVM_GUEST_PAGE_TABLE_MIN_PADDR, pgd_memslot);
		vm->pgd = paddr;
		vm->pgd_created = true;
	पूर्ण
पूर्ण

व्योम virt_pg_map(काष्ठा kvm_vm *vm, uपूर्णांक64_t vaddr, uपूर्णांक64_t paddr,
	uपूर्णांक32_t pgd_memslot)
अणु
	uपूर्णांक16_t index[4];
	काष्ठा pageMapL4Entry *pml4e;

	TEST_ASSERT(vm->mode == VM_MODE_PXXV48_4K, "Attempt to use "
		"unknown or unsupported guest mode, mode: 0x%x", vm->mode);

	TEST_ASSERT((vaddr % vm->page_size) == 0,
		"Virtual address not on page boundary,\n"
		"  vaddr: 0x%lx vm->page_size: 0x%x",
		vaddr, vm->page_size);
	TEST_ASSERT(sparsebit_is_set(vm->vpages_valid,
		(vaddr >> vm->page_shअगरt)),
		"Invalid virtual address, vaddr: 0x%lx",
		vaddr);
	TEST_ASSERT((paddr % vm->page_size) == 0,
		"Physical address not on page boundary,\n"
		"  paddr: 0x%lx vm->page_size: 0x%x",
		paddr, vm->page_size);
	TEST_ASSERT((paddr >> vm->page_shअगरt) <= vm->max_gfn,
		"Physical address beyond beyond maximum supported,\n"
		"  paddr: 0x%lx vm->max_gfn: 0x%lx vm->page_size: 0x%x",
		paddr, vm->max_gfn, vm->page_size);

	index[0] = (vaddr >> 12) & 0x1ffu;
	index[1] = (vaddr >> 21) & 0x1ffu;
	index[2] = (vaddr >> 30) & 0x1ffu;
	index[3] = (vaddr >> 39) & 0x1ffu;

	/* Allocate page directory poपूर्णांकer table अगर not present. */
	pml4e = addr_gpa2hva(vm, vm->pgd);
	अगर (!pml4e[index[3]].present) अणु
		pml4e[index[3]].address = vm_phy_page_alloc(vm,
			KVM_GUEST_PAGE_TABLE_MIN_PADDR, pgd_memslot)
			>> vm->page_shअगरt;
		pml4e[index[3]].writable = true;
		pml4e[index[3]].present = true;
	पूर्ण

	/* Allocate page directory table अगर not present. */
	काष्ठा pageDirectoryPoपूर्णांकerEntry *pdpe;
	pdpe = addr_gpa2hva(vm, pml4e[index[3]].address * vm->page_size);
	अगर (!pdpe[index[2]].present) अणु
		pdpe[index[2]].address = vm_phy_page_alloc(vm,
			KVM_GUEST_PAGE_TABLE_MIN_PADDR, pgd_memslot)
			>> vm->page_shअगरt;
		pdpe[index[2]].writable = true;
		pdpe[index[2]].present = true;
	पूर्ण

	/* Allocate page table अगर not present. */
	काष्ठा pageDirectoryEntry *pde;
	pde = addr_gpa2hva(vm, pdpe[index[2]].address * vm->page_size);
	अगर (!pde[index[1]].present) अणु
		pde[index[1]].address = vm_phy_page_alloc(vm,
			KVM_GUEST_PAGE_TABLE_MIN_PADDR, pgd_memslot)
			>> vm->page_shअगरt;
		pde[index[1]].writable = true;
		pde[index[1]].present = true;
	पूर्ण

	/* Fill in page table entry. */
	काष्ठा pageTableEntry *pte;
	pte = addr_gpa2hva(vm, pde[index[1]].address * vm->page_size);
	pte[index[0]].address = paddr >> vm->page_shअगरt;
	pte[index[0]].writable = true;
	pte[index[0]].present = 1;
पूर्ण

व्योम virt_dump(खाता *stream, काष्ठा kvm_vm *vm, uपूर्णांक8_t indent)
अणु
	काष्ठा pageMapL4Entry *pml4e, *pml4e_start;
	काष्ठा pageDirectoryPoपूर्णांकerEntry *pdpe, *pdpe_start;
	काष्ठा pageDirectoryEntry *pde, *pde_start;
	काष्ठा pageTableEntry *pte, *pte_start;

	अगर (!vm->pgd_created)
		वापस;

	ख_लिखो(stream, "%*s                                          "
		"                no\n", indent, "");
	ख_लिखो(stream, "%*s      index hvaddr         gpaddr         "
		"addr         w exec dirty\n",
		indent, "");
	pml4e_start = (काष्ठा pageMapL4Entry *) addr_gpa2hva(vm,
		vm->pgd);
	क्रम (uपूर्णांक16_t n1 = 0; n1 <= 0x1ffu; n1++) अणु
		pml4e = &pml4e_start[n1];
		अगर (!pml4e->present)
			जारी;
		ख_लिखो(stream, "%*spml4e 0x%-3zx %p 0x%-12lx 0x%-10lx %u "
			" %u\n",
			indent, "",
			pml4e - pml4e_start, pml4e,
			addr_hva2gpa(vm, pml4e), (uपूर्णांक64_t) pml4e->address,
			pml4e->writable, pml4e->execute_disable);

		pdpe_start = addr_gpa2hva(vm, pml4e->address
			* vm->page_size);
		क्रम (uपूर्णांक16_t n2 = 0; n2 <= 0x1ffu; n2++) अणु
			pdpe = &pdpe_start[n2];
			अगर (!pdpe->present)
				जारी;
			ख_लिखो(stream, "%*spdpe  0x%-3zx %p 0x%-12lx 0x%-10lx "
				"%u  %u\n",
				indent, "",
				pdpe - pdpe_start, pdpe,
				addr_hva2gpa(vm, pdpe),
				(uपूर्णांक64_t) pdpe->address, pdpe->writable,
				pdpe->execute_disable);

			pde_start = addr_gpa2hva(vm,
				pdpe->address * vm->page_size);
			क्रम (uपूर्णांक16_t n3 = 0; n3 <= 0x1ffu; n3++) अणु
				pde = &pde_start[n3];
				अगर (!pde->present)
					जारी;
				ख_लिखो(stream, "%*spde   0x%-3zx %p "
					"0x%-12lx 0x%-10lx %u  %u\n",
					indent, "", pde - pde_start, pde,
					addr_hva2gpa(vm, pde),
					(uपूर्णांक64_t) pde->address, pde->writable,
					pde->execute_disable);

				pte_start = addr_gpa2hva(vm,
					pde->address * vm->page_size);
				क्रम (uपूर्णांक16_t n4 = 0; n4 <= 0x1ffu; n4++) अणु
					pte = &pte_start[n4];
					अगर (!pte->present)
						जारी;
					ख_लिखो(stream, "%*spte   0x%-3zx %p "
						"0x%-12lx 0x%-10lx %u  %u "
						"    %u    0x%-10lx\n",
						indent, "",
						pte - pte_start, pte,
						addr_hva2gpa(vm, pte),
						(uपूर्णांक64_t) pte->address,
						pte->writable,
						pte->execute_disable,
						pte->dirty,
						((uपूर्णांक64_t) n1 << 27)
							| ((uपूर्णांक64_t) n2 << 18)
							| ((uपूर्णांक64_t) n3 << 9)
							| ((uपूर्णांक64_t) n4));
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Set Unusable Segment
 *
 * Input Args: None
 *
 * Output Args:
 *   segp - Poपूर्णांकer to segment रेजिस्टर
 *
 * Return: None
 *
 * Sets the segment रेजिस्टर poपूर्णांकed to by @segp to an unusable state.
 */
अटल व्योम kvm_seg_set_unusable(काष्ठा kvm_segment *segp)
अणु
	स_रखो(segp, 0, माप(*segp));
	segp->unusable = true;
पूर्ण

अटल व्योम kvm_seg_fill_gdt_64bit(काष्ठा kvm_vm *vm, काष्ठा kvm_segment *segp)
अणु
	व्योम *gdt = addr_gva2hva(vm, vm->gdt);
	काष्ठा desc64 *desc = gdt + (segp->selector >> 3) * 8;

	desc->limit0 = segp->limit & 0xFFFF;
	desc->base0 = segp->base & 0xFFFF;
	desc->base1 = segp->base >> 16;
	desc->type = segp->type;
	desc->s = segp->s;
	desc->dpl = segp->dpl;
	desc->p = segp->present;
	desc->limit1 = segp->limit >> 16;
	desc->avl = segp->avl;
	desc->l = segp->l;
	desc->db = segp->db;
	desc->g = segp->g;
	desc->base2 = segp->base >> 24;
	अगर (!segp->s)
		desc->base3 = segp->base >> 32;
पूर्ण


/*
 * Set Long Mode Flat Kernel Code Segment
 *
 * Input Args:
 *   vm - VM whose GDT is being filled, or शून्य to only ग_लिखो segp
 *   selector - selector value
 *
 * Output Args:
 *   segp - Poपूर्णांकer to KVM segment
 *
 * Return: None
 *
 * Sets up the KVM segment poपूर्णांकed to by @segp, to be a code segment
 * with the selector value given by @selector.
 */
अटल व्योम kvm_seg_set_kernel_code_64bit(काष्ठा kvm_vm *vm, uपूर्णांक16_t selector,
	काष्ठा kvm_segment *segp)
अणु
	स_रखो(segp, 0, माप(*segp));
	segp->selector = selector;
	segp->limit = 0xFFFFFFFFu;
	segp->s = 0x1; /* kTypeCodeData */
	segp->type = 0x08 | 0x01 | 0x02; /* kFlagCode | kFlagCodeAccessed
					  * | kFlagCodeReadable
					  */
	segp->g = true;
	segp->l = true;
	segp->present = 1;
	अगर (vm)
		kvm_seg_fill_gdt_64bit(vm, segp);
पूर्ण

/*
 * Set Long Mode Flat Kernel Data Segment
 *
 * Input Args:
 *   vm - VM whose GDT is being filled, or शून्य to only ग_लिखो segp
 *   selector - selector value
 *
 * Output Args:
 *   segp - Poपूर्णांकer to KVM segment
 *
 * Return: None
 *
 * Sets up the KVM segment poपूर्णांकed to by @segp, to be a data segment
 * with the selector value given by @selector.
 */
अटल व्योम kvm_seg_set_kernel_data_64bit(काष्ठा kvm_vm *vm, uपूर्णांक16_t selector,
	काष्ठा kvm_segment *segp)
अणु
	स_रखो(segp, 0, माप(*segp));
	segp->selector = selector;
	segp->limit = 0xFFFFFFFFu;
	segp->s = 0x1; /* kTypeCodeData */
	segp->type = 0x00 | 0x01 | 0x02; /* kFlagData | kFlagDataAccessed
					  * | kFlagDataWritable
					  */
	segp->g = true;
	segp->present = true;
	अगर (vm)
		kvm_seg_fill_gdt_64bit(vm, segp);
पूर्ण

vm_paddr_t addr_gva2gpa(काष्ठा kvm_vm *vm, vm_vaddr_t gva)
अणु
	uपूर्णांक16_t index[4];
	काष्ठा pageMapL4Entry *pml4e;
	काष्ठा pageDirectoryPoपूर्णांकerEntry *pdpe;
	काष्ठा pageDirectoryEntry *pde;
	काष्ठा pageTableEntry *pte;

	TEST_ASSERT(vm->mode == VM_MODE_PXXV48_4K, "Attempt to use "
		"unknown or unsupported guest mode, mode: 0x%x", vm->mode);

	index[0] = (gva >> 12) & 0x1ffu;
	index[1] = (gva >> 21) & 0x1ffu;
	index[2] = (gva >> 30) & 0x1ffu;
	index[3] = (gva >> 39) & 0x1ffu;

	अगर (!vm->pgd_created)
		जाओ unmapped_gva;
	pml4e = addr_gpa2hva(vm, vm->pgd);
	अगर (!pml4e[index[3]].present)
		जाओ unmapped_gva;

	pdpe = addr_gpa2hva(vm, pml4e[index[3]].address * vm->page_size);
	अगर (!pdpe[index[2]].present)
		जाओ unmapped_gva;

	pde = addr_gpa2hva(vm, pdpe[index[2]].address * vm->page_size);
	अगर (!pde[index[1]].present)
		जाओ unmapped_gva;

	pte = addr_gpa2hva(vm, pde[index[1]].address * vm->page_size);
	अगर (!pte[index[0]].present)
		जाओ unmapped_gva;

	वापस (pte[index[0]].address * vm->page_size) + (gva & 0xfffu);

unmapped_gva:
	TEST_FAIL("No mapping for vm virtual address, gva: 0x%lx", gva);
	निकास(निकास_त्रुटि);
पूर्ण

अटल व्योम kvm_setup_gdt(काष्ठा kvm_vm *vm, काष्ठा kvm_dtable *dt, पूर्णांक gdt_memslot,
			  पूर्णांक pgd_memslot)
अणु
	अगर (!vm->gdt)
		vm->gdt = vm_vaddr_alloc(vm, getpagesize(),
			KVM_UTIL_MIN_VADDR, gdt_memslot, pgd_memslot);

	dt->base = vm->gdt;
	dt->limit = getpagesize();
पूर्ण

अटल व्योम kvm_setup_tss_64bit(काष्ठा kvm_vm *vm, काष्ठा kvm_segment *segp,
				पूर्णांक selector, पूर्णांक gdt_memslot,
				पूर्णांक pgd_memslot)
अणु
	अगर (!vm->tss)
		vm->tss = vm_vaddr_alloc(vm, getpagesize(),
			KVM_UTIL_MIN_VADDR, gdt_memslot, pgd_memslot);

	स_रखो(segp, 0, माप(*segp));
	segp->base = vm->tss;
	segp->limit = 0x67;
	segp->selector = selector;
	segp->type = 0xb;
	segp->present = 1;
	kvm_seg_fill_gdt_64bit(vm, segp);
पूर्ण

अटल व्योम vcpu_setup(काष्ठा kvm_vm *vm, पूर्णांक vcpuid, पूर्णांक pgd_memslot, पूर्णांक gdt_memslot)
अणु
	काष्ठा kvm_sregs sregs;

	/* Set mode specअगरic प्रणाली रेजिस्टर values. */
	vcpu_sregs_get(vm, vcpuid, &sregs);

	sregs.idt.limit = 0;

	kvm_setup_gdt(vm, &sregs.gdt, gdt_memslot, pgd_memslot);

	चयन (vm->mode) अणु
	हाल VM_MODE_PXXV48_4K:
		sregs.cr0 = X86_CR0_PE | X86_CR0_NE | X86_CR0_PG;
		sregs.cr4 |= X86_CR4_PAE | X86_CR4_OSFXSR;
		sregs.efer |= (EFER_LME | EFER_LMA | EFER_NX);

		kvm_seg_set_unusable(&sregs.ldt);
		kvm_seg_set_kernel_code_64bit(vm, DEFAULT_CODE_SELECTOR, &sregs.cs);
		kvm_seg_set_kernel_data_64bit(vm, DEFAULT_DATA_SELECTOR, &sregs.ds);
		kvm_seg_set_kernel_data_64bit(vm, DEFAULT_DATA_SELECTOR, &sregs.es);
		kvm_setup_tss_64bit(vm, &sregs.tr, 0x18, gdt_memslot, pgd_memslot);
		अवरोध;

	शेष:
		TEST_FAIL("Unknown guest mode, mode: 0x%x", vm->mode);
	पूर्ण

	sregs.cr3 = vm->pgd;
	vcpu_sregs_set(vm, vcpuid, &sregs);
पूर्ण

व्योम vm_vcpu_add_शेष(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, व्योम *guest_code)
अणु
	काष्ठा kvm_mp_state mp_state;
	काष्ठा kvm_regs regs;
	vm_vaddr_t stack_vaddr;
	stack_vaddr = vm_vaddr_alloc(vm, DEFAULT_STACK_PGS * getpagesize(),
				     DEFAULT_GUEST_STACK_VADDR_MIN, 0, 0);

	/* Create VCPU */
	vm_vcpu_add(vm, vcpuid);
	vcpu_setup(vm, vcpuid, 0, 0);

	/* Setup guest general purpose रेजिस्टरs */
	vcpu_regs_get(vm, vcpuid, &regs);
	regs.rflags = regs.rflags | 0x2;
	regs.rsp = stack_vaddr + (DEFAULT_STACK_PGS * getpagesize());
	regs.rip = (अचिन्हित दीर्घ) guest_code;
	vcpu_regs_set(vm, vcpuid, &regs);

	/* Setup the MP state */
	mp_state.mp_state = 0;
	vcpu_set_mp_state(vm, vcpuid, &mp_state);
पूर्ण

/*
 * Allocate an instance of काष्ठा kvm_cpuid2
 *
 * Input Args: None
 *
 * Output Args: None
 *
 * Return: A poपूर्णांकer to the allocated काष्ठा. The caller is responsible
 * क्रम मुक्तing this काष्ठा.
 *
 * Since kvm_cpuid2 uses a 0-length array to allow a the size of the
 * array to be decided at allocation समय, allocation is slightly
 * complicated. This function uses a reasonable शेष length क्रम
 * the array and perक्रमms the appropriate allocation.
 */
अटल काष्ठा kvm_cpuid2 *allocate_kvm_cpuid2(व्योम)
अणु
	काष्ठा kvm_cpuid2 *cpuid;
	पूर्णांक nent = 100;
	माप_प्रकार size;

	size = माप(*cpuid);
	size += nent * माप(काष्ठा kvm_cpuid_entry2);
	cpuid = दो_स्मृति(size);
	अगर (!cpuid) अणु
		लिखो_त्रुटि("malloc");
		पात();
	पूर्ण

	cpuid->nent = nent;

	वापस cpuid;
पूर्ण

/*
 * KVM Supported CPUID Get
 *
 * Input Args: None
 *
 * Output Args:
 *
 * Return: The supported KVM CPUID
 *
 * Get the guest CPUID supported by KVM.
 */
काष्ठा kvm_cpuid2 *kvm_get_supported_cpuid(व्योम)
अणु
	अटल काष्ठा kvm_cpuid2 *cpuid;
	पूर्णांक ret;
	पूर्णांक kvm_fd;

	अगर (cpuid)
		वापस cpuid;

	cpuid = allocate_kvm_cpuid2();
	kvm_fd = खोलो_kvm_dev_path_or_निकास();

	ret = ioctl(kvm_fd, KVM_GET_SUPPORTED_CPUID, cpuid);
	TEST_ASSERT(ret == 0, "KVM_GET_SUPPORTED_CPUID failed %d %d\n",
		    ret, त्रुटि_सं);

	बंद(kvm_fd);
	वापस cpuid;
पूर्ण

/*
 * KVM Get MSR
 *
 * Input Args:
 *   msr_index - Index of MSR
 *
 * Output Args: None
 *
 * Return: On success, value of the MSR. On failure a TEST_ASSERT is produced.
 *
 * Get value of MSR क्रम VCPU.
 */
uपूर्णांक64_t kvm_get_feature_msr(uपूर्णांक64_t msr_index)
अणु
	काष्ठा अणु
		काष्ठा kvm_msrs header;
		काष्ठा kvm_msr_entry entry;
	पूर्ण buffer = अणुपूर्ण;
	पूर्णांक r, kvm_fd;

	buffer.header.nmsrs = 1;
	buffer.entry.index = msr_index;
	kvm_fd = खोलो_kvm_dev_path_or_निकास();

	r = ioctl(kvm_fd, KVM_GET_MSRS, &buffer.header);
	TEST_ASSERT(r == 1, "KVM_GET_MSRS IOCTL failed,\n"
		"  rc: %i errno: %i", r, त्रुटि_सं);

	बंद(kvm_fd);
	वापस buffer.entry.data;
पूर्ण

/*
 * VM VCPU CPUID Set
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU id
 *
 * Output Args: None
 *
 * Return: KVM CPUID (KVM_GET_CPUID2)
 *
 * Set the VCPU's CPUID.
 */
काष्ठा kvm_cpuid2 *vcpu_get_cpuid(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	काष्ठा kvm_cpuid2 *cpuid;
	पूर्णांक max_ent;
	पूर्णांक rc = -1;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	cpuid = allocate_kvm_cpuid2();
	max_ent = cpuid->nent;

	क्रम (cpuid->nent = 1; cpuid->nent <= max_ent; cpuid->nent++) अणु
		rc = ioctl(vcpu->fd, KVM_GET_CPUID2, cpuid);
		अगर (!rc)
			अवरोध;

		TEST_ASSERT(rc == -1 && त्रुटि_सं == E2BIG,
			    "KVM_GET_CPUID2 should either succeed or give E2BIG: %d %d",
			    rc, त्रुटि_सं);
	पूर्ण

	TEST_ASSERT(rc == 0, "KVM_GET_CPUID2 failed, rc: %i errno: %i",
		    rc, त्रुटि_सं);

	वापस cpuid;
पूर्ण



/*
 * Locate a cpuid entry.
 *
 * Input Args:
 *   function: The function of the cpuid entry to find.
 *   index: The index of the cpuid entry.
 *
 * Output Args: None
 *
 * Return: A poपूर्णांकer to the cpuid entry. Never वापसs शून्य.
 */
काष्ठा kvm_cpuid_entry2 *
kvm_get_supported_cpuid_index(uपूर्णांक32_t function, uपूर्णांक32_t index)
अणु
	काष्ठा kvm_cpuid2 *cpuid;
	काष्ठा kvm_cpuid_entry2 *entry = शून्य;
	पूर्णांक i;

	cpuid = kvm_get_supported_cpuid();
	क्रम (i = 0; i < cpuid->nent; i++) अणु
		अगर (cpuid->entries[i].function == function &&
		    cpuid->entries[i].index == index) अणु
			entry = &cpuid->entries[i];
			अवरोध;
		पूर्ण
	पूर्ण

	TEST_ASSERT(entry, "Guest CPUID entry not found: (EAX=%x, ECX=%x).",
		    function, index);
	वापस entry;
पूर्ण

/*
 * VM VCPU CPUID Set
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU id
 *   cpuid - The CPUID values to set.
 *
 * Output Args: None
 *
 * Return: व्योम
 *
 * Set the VCPU's CPUID.
 */
व्योम vcpu_set_cpuid(काष्ठा kvm_vm *vm,
		uपूर्णांक32_t vcpuid, काष्ठा kvm_cpuid2 *cpuid)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	पूर्णांक rc;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	rc = ioctl(vcpu->fd, KVM_SET_CPUID2, cpuid);
	TEST_ASSERT(rc == 0, "KVM_SET_CPUID2 failed, rc: %i errno: %i",
		    rc, त्रुटि_सं);

पूर्ण

/*
 * VCPU Get MSR
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *   msr_index - Index of MSR
 *
 * Output Args: None
 *
 * Return: On success, value of the MSR. On failure a TEST_ASSERT is produced.
 *
 * Get value of MSR क्रम VCPU.
 */
uपूर्णांक64_t vcpu_get_msr(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, uपूर्णांक64_t msr_index)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	काष्ठा अणु
		काष्ठा kvm_msrs header;
		काष्ठा kvm_msr_entry entry;
	पूर्ण buffer = अणुपूर्ण;
	पूर्णांक r;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);
	buffer.header.nmsrs = 1;
	buffer.entry.index = msr_index;
	r = ioctl(vcpu->fd, KVM_GET_MSRS, &buffer.header);
	TEST_ASSERT(r == 1, "KVM_GET_MSRS IOCTL failed,\n"
		"  rc: %i errno: %i", r, त्रुटि_सं);

	वापस buffer.entry.data;
पूर्ण

/*
 * _VCPU Set MSR
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *   msr_index - Index of MSR
 *   msr_value - New value of MSR
 *
 * Output Args: None
 *
 * Return: The result of KVM_SET_MSRS.
 *
 * Sets the value of an MSR क्रम the given VCPU.
 */
पूर्णांक _vcpu_set_msr(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, uपूर्णांक64_t msr_index,
		  uपूर्णांक64_t msr_value)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	काष्ठा अणु
		काष्ठा kvm_msrs header;
		काष्ठा kvm_msr_entry entry;
	पूर्ण buffer = अणुपूर्ण;
	पूर्णांक r;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);
	स_रखो(&buffer, 0, माप(buffer));
	buffer.header.nmsrs = 1;
	buffer.entry.index = msr_index;
	buffer.entry.data = msr_value;
	r = ioctl(vcpu->fd, KVM_SET_MSRS, &buffer.header);
	वापस r;
पूर्ण

/*
 * VCPU Set MSR
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *   msr_index - Index of MSR
 *   msr_value - New value of MSR
 *
 * Output Args: None
 *
 * Return: On success, nothing. On failure a TEST_ASSERT is produced.
 *
 * Set value of MSR क्रम VCPU.
 */
व्योम vcpu_set_msr(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, uपूर्णांक64_t msr_index,
	uपूर्णांक64_t msr_value)
अणु
	पूर्णांक r;

	r = _vcpu_set_msr(vm, vcpuid, msr_index, msr_value);
	TEST_ASSERT(r == 1, "KVM_SET_MSRS IOCTL failed,\n"
		"  rc: %i errno: %i", r, त्रुटि_सं);
पूर्ण

व्योम vcpu_args_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, अचिन्हित पूर्णांक num, ...)
अणु
	बहु_सूची ap;
	काष्ठा kvm_regs regs;

	TEST_ASSERT(num >= 1 && num <= 6, "Unsupported number of args,\n"
		    "  num: %u\n",
		    num);

	बहु_शुरू(ap, num);
	vcpu_regs_get(vm, vcpuid, &regs);

	अगर (num >= 1)
		regs.rdi = बहु_तर्क(ap, uपूर्णांक64_t);

	अगर (num >= 2)
		regs.rsi = बहु_तर्क(ap, uपूर्णांक64_t);

	अगर (num >= 3)
		regs.rdx = बहु_तर्क(ap, uपूर्णांक64_t);

	अगर (num >= 4)
		regs.rcx = बहु_तर्क(ap, uपूर्णांक64_t);

	अगर (num >= 5)
		regs.r8 = बहु_तर्क(ap, uपूर्णांक64_t);

	अगर (num >= 6)
		regs.r9 = बहु_तर्क(ap, uपूर्णांक64_t);

	vcpu_regs_set(vm, vcpuid, &regs);
	बहु_पूर्ण(ap);
पूर्ण

व्योम vcpu_dump(खाता *stream, काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, uपूर्णांक8_t indent)
अणु
	काष्ठा kvm_regs regs;
	काष्ठा kvm_sregs sregs;

	ख_लिखो(stream, "%*scpuid: %u\n", indent, "", vcpuid);

	ख_लिखो(stream, "%*sregs:\n", indent + 2, "");
	vcpu_regs_get(vm, vcpuid, &regs);
	regs_dump(stream, &regs, indent + 4);

	ख_लिखो(stream, "%*ssregs:\n", indent + 2, "");
	vcpu_sregs_get(vm, vcpuid, &sregs);
	sregs_dump(stream, &sregs, indent + 4);
पूर्ण

काष्ठा kvm_x86_state अणु
	काष्ठा kvm_vcpu_events events;
	काष्ठा kvm_mp_state mp_state;
	काष्ठा kvm_regs regs;
	काष्ठा kvm_xsave xsave;
	काष्ठा kvm_xcrs xcrs;
	काष्ठा kvm_sregs sregs;
	काष्ठा kvm_debugregs debugregs;
	जोड़ अणु
		काष्ठा kvm_nested_state nested;
		अक्षर nested_[16384];
	पूर्ण;
	काष्ठा kvm_msrs msrs;
पूर्ण;

अटल पूर्णांक kvm_get_num_msrs_fd(पूर्णांक kvm_fd)
अणु
	काष्ठा kvm_msr_list nmsrs;
	पूर्णांक r;

	nmsrs.nmsrs = 0;
	r = ioctl(kvm_fd, KVM_GET_MSR_INDEX_LIST, &nmsrs);
	TEST_ASSERT(r == -1 && त्रुटि_सं == E2BIG, "Unexpected result from KVM_GET_MSR_INDEX_LIST probe, r: %i",
		r);

	वापस nmsrs.nmsrs;
पूर्ण

अटल पूर्णांक kvm_get_num_msrs(काष्ठा kvm_vm *vm)
अणु
	वापस kvm_get_num_msrs_fd(vm->kvm_fd);
पूर्ण

काष्ठा kvm_msr_list *kvm_get_msr_index_list(व्योम)
अणु
	काष्ठा kvm_msr_list *list;
	पूर्णांक nmsrs, r, kvm_fd;

	kvm_fd = खोलो_kvm_dev_path_or_निकास();

	nmsrs = kvm_get_num_msrs_fd(kvm_fd);
	list = दो_स्मृति(माप(*list) + nmsrs * माप(list->indices[0]));
	list->nmsrs = nmsrs;
	r = ioctl(kvm_fd, KVM_GET_MSR_INDEX_LIST, list);
	बंद(kvm_fd);

	TEST_ASSERT(r == 0, "Unexpected result from KVM_GET_MSR_INDEX_LIST, r: %i",
		r);

	वापस list;
पूर्ण

काष्ठा kvm_x86_state *vcpu_save_state(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	काष्ठा kvm_msr_list *list;
	काष्ठा kvm_x86_state *state;
	पूर्णांक nmsrs, r, i;
	अटल पूर्णांक nested_size = -1;

	अगर (nested_size == -1) अणु
		nested_size = kvm_check_cap(KVM_CAP_NESTED_STATE);
		TEST_ASSERT(nested_size <= माप(state->nested_),
			    "Nested state size too big, %i > %zi",
			    nested_size, माप(state->nested_));
	पूर्ण

	/*
	 * When KVM निकासs to userspace with KVM_EXIT_IO, KVM guarantees
	 * guest state is consistent only after userspace re-enters the
	 * kernel with KVM_RUN.  Complete IO prior to migrating state
	 * to a new VM.
	 */
	vcpu_run_complete_io(vm, vcpuid);

	nmsrs = kvm_get_num_msrs(vm);
	list = दो_स्मृति(माप(*list) + nmsrs * माप(list->indices[0]));
	list->nmsrs = nmsrs;
	r = ioctl(vm->kvm_fd, KVM_GET_MSR_INDEX_LIST, list);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_GET_MSR_INDEX_LIST, r: %i",
                r);

	state = दो_स्मृति(माप(*state) + nmsrs * माप(state->msrs.entries[0]));
	r = ioctl(vcpu->fd, KVM_GET_VCPU_EVENTS, &state->events);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_GET_VCPU_EVENTS, r: %i",
                r);

	r = ioctl(vcpu->fd, KVM_GET_MP_STATE, &state->mp_state);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_GET_MP_STATE, r: %i",
                r);

	r = ioctl(vcpu->fd, KVM_GET_REGS, &state->regs);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_GET_REGS, r: %i",
                r);

	r = ioctl(vcpu->fd, KVM_GET_XSAVE, &state->xsave);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_GET_XSAVE, r: %i",
                r);

	अगर (kvm_check_cap(KVM_CAP_XCRS)) अणु
		r = ioctl(vcpu->fd, KVM_GET_XCRS, &state->xcrs);
		TEST_ASSERT(r == 0, "Unexpected result from KVM_GET_XCRS, r: %i",
			    r);
	पूर्ण

	r = ioctl(vcpu->fd, KVM_GET_SREGS, &state->sregs);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_GET_SREGS, r: %i",
                r);

	अगर (nested_size) अणु
		state->nested.size = माप(state->nested_);
		r = ioctl(vcpu->fd, KVM_GET_NESTED_STATE, &state->nested);
		TEST_ASSERT(r == 0, "Unexpected result from KVM_GET_NESTED_STATE, r: %i",
			r);
		TEST_ASSERT(state->nested.size <= nested_size,
			"Nested state size too big, %i (KVM_CHECK_CAP gave %i)",
			state->nested.size, nested_size);
	पूर्ण अन्यथा
		state->nested.size = 0;

	state->msrs.nmsrs = nmsrs;
	क्रम (i = 0; i < nmsrs; i++)
		state->msrs.entries[i].index = list->indices[i];
	r = ioctl(vcpu->fd, KVM_GET_MSRS, &state->msrs);
        TEST_ASSERT(r == nmsrs, "Unexpected result from KVM_GET_MSRS, r: %i (failed MSR was 0x%x)",
                r, r == nmsrs ? -1 : list->indices[r]);

	r = ioctl(vcpu->fd, KVM_GET_DEBUGREGS, &state->debugregs);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_GET_DEBUGREGS, r: %i",
                r);

	मुक्त(list);
	वापस state;
पूर्ण

व्योम vcpu_load_state(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, काष्ठा kvm_x86_state *state)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	पूर्णांक r;

	r = ioctl(vcpu->fd, KVM_SET_XSAVE, &state->xsave);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_XSAVE, r: %i",
                r);

	अगर (kvm_check_cap(KVM_CAP_XCRS)) अणु
		r = ioctl(vcpu->fd, KVM_SET_XCRS, &state->xcrs);
		TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_XCRS, r: %i",
			    r);
	पूर्ण

	r = ioctl(vcpu->fd, KVM_SET_SREGS, &state->sregs);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_SREGS, r: %i",
                r);

	r = ioctl(vcpu->fd, KVM_SET_MSRS, &state->msrs);
        TEST_ASSERT(r == state->msrs.nmsrs, "Unexpected result from KVM_SET_MSRS, r: %i (failed at %x)",
                r, r == state->msrs.nmsrs ? -1 : state->msrs.entries[r].index);

	r = ioctl(vcpu->fd, KVM_SET_VCPU_EVENTS, &state->events);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_VCPU_EVENTS, r: %i",
                r);

	r = ioctl(vcpu->fd, KVM_SET_MP_STATE, &state->mp_state);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_MP_STATE, r: %i",
                r);

	r = ioctl(vcpu->fd, KVM_SET_DEBUGREGS, &state->debugregs);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_DEBUGREGS, r: %i",
                r);

	r = ioctl(vcpu->fd, KVM_SET_REGS, &state->regs);
        TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_REGS, r: %i",
                r);

	अगर (state->nested.size) अणु
		r = ioctl(vcpu->fd, KVM_SET_NESTED_STATE, &state->nested);
		TEST_ASSERT(r == 0, "Unexpected result from KVM_SET_NESTED_STATE, r: %i",
			r);
	पूर्ण
पूर्ण

bool is_पूर्णांकel_cpu(व्योम)
अणु
	पूर्णांक eax, ebx, ecx, edx;
	स्थिर uपूर्णांक32_t *chunk;
	स्थिर पूर्णांक leaf = 0;

	__यंत्र__ __अस्थिर__(
		"cpuid"
		: /* output */ "=a"(eax), "=b"(ebx),
		  "=c"(ecx), "=d"(edx)
		: /* input */ "0"(leaf), "2"(0));

	chunk = (स्थिर uपूर्णांक32_t *)("GenuineIntel");
	वापस (ebx == chunk[0] && edx == chunk[1] && ecx == chunk[2]);
पूर्ण

uपूर्णांक32_t kvm_get_cpuid_max_basic(व्योम)
अणु
	वापस kvm_get_supported_cpuid_entry(0)->eax;
पूर्ण

uपूर्णांक32_t kvm_get_cpuid_max_extended(व्योम)
अणु
	वापस kvm_get_supported_cpuid_entry(0x80000000)->eax;
पूर्ण

व्योम kvm_get_cpu_address_width(अचिन्हित पूर्णांक *pa_bits, अचिन्हित पूर्णांक *va_bits)
अणु
	काष्ठा kvm_cpuid_entry2 *entry;
	bool pae;

	/* SDM 4.1.4 */
	अगर (kvm_get_cpuid_max_extended() < 0x80000008) अणु
		pae = kvm_get_supported_cpuid_entry(1)->edx & (1 << 6);
		*pa_bits = pae ? 36 : 32;
		*va_bits = 32;
	पूर्ण अन्यथा अणु
		entry = kvm_get_supported_cpuid_entry(0x80000008);
		*pa_bits = entry->eax & 0xff;
		*va_bits = (entry->eax >> 8) & 0xff;
	पूर्ण
पूर्ण

काष्ठा idt_entry अणु
	uपूर्णांक16_t offset0;
	uपूर्णांक16_t selector;
	uपूर्णांक16_t ist : 3;
	uपूर्णांक16_t : 5;
	uपूर्णांक16_t type : 4;
	uपूर्णांक16_t : 1;
	uपूर्णांक16_t dpl : 2;
	uपूर्णांक16_t p : 1;
	uपूर्णांक16_t offset1;
	uपूर्णांक32_t offset2; uपूर्णांक32_t reserved;
पूर्ण;

अटल व्योम set_idt_entry(काष्ठा kvm_vm *vm, पूर्णांक vector, अचिन्हित दीर्घ addr,
			  पूर्णांक dpl, अचिन्हित लघु selector)
अणु
	काष्ठा idt_entry *base =
		(काष्ठा idt_entry *)addr_gva2hva(vm, vm->idt);
	काष्ठा idt_entry *e = &base[vector];

	स_रखो(e, 0, माप(*e));
	e->offset0 = addr;
	e->selector = selector;
	e->ist = 0;
	e->type = 14;
	e->dpl = dpl;
	e->p = 1;
	e->offset1 = addr >> 16;
	e->offset2 = addr >> 32;
पूर्ण

व्योम kvm_निकास_unexpected_vector(uपूर्णांक32_t value)
अणु
	outl(UNEXPECTED_VECTOR_PORT, value);
पूर्ण

व्योम route_exception(काष्ठा ex_regs *regs)
अणु
	प्रकार व्योम(*handler)(काष्ठा ex_regs *);
	handler *handlers = (handler *)exception_handlers;

	अगर (handlers && handlers[regs->vector]) अणु
		handlers[regs->vector](regs);
		वापस;
	पूर्ण

	kvm_निकास_unexpected_vector(regs->vector);
पूर्ण

व्योम vm_init_descriptor_tables(काष्ठा kvm_vm *vm)
अणु
	बाह्य व्योम *idt_handlers;
	पूर्णांक i;

	vm->idt = vm_vaddr_alloc(vm, getpagesize(), 0x2000, 0, 0);
	vm->handlers = vm_vaddr_alloc(vm, 256 * माप(व्योम *), 0x2000, 0, 0);
	/* Handlers have the same address in both address spaces.*/
	क्रम (i = 0; i < NUM_INTERRUPTS; i++)
		set_idt_entry(vm, i, (अचिन्हित दीर्घ)(&idt_handlers)[i], 0,
			DEFAULT_CODE_SELECTOR);
पूर्ण

व्योम vcpu_init_descriptor_tables(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा kvm_sregs sregs;

	vcpu_sregs_get(vm, vcpuid, &sregs);
	sregs.idt.base = vm->idt;
	sregs.idt.limit = NUM_INTERRUPTS * माप(काष्ठा idt_entry) - 1;
	sregs.gdt.base = vm->gdt;
	sregs.gdt.limit = getpagesize() - 1;
	kvm_seg_set_kernel_data_64bit(शून्य, DEFAULT_DATA_SELECTOR, &sregs.gs);
	vcpu_sregs_set(vm, vcpuid, &sregs);
	*(vm_vaddr_t *)addr_gva2hva(vm, (vm_vaddr_t)(&exception_handlers)) = vm->handlers;
पूर्ण

व्योम vm_handle_exception(काष्ठा kvm_vm *vm, पूर्णांक vector,
			 व्योम (*handler)(काष्ठा ex_regs *))
अणु
	vm_vaddr_t *handlers = (vm_vaddr_t *)addr_gva2hva(vm, vm->handlers);

	handlers[vector] = (vm_vaddr_t)handler;
पूर्ण

व्योम निश्चित_on_unhandled_exception(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	अगर (vcpu_state(vm, vcpuid)->निकास_reason == KVM_EXIT_IO
		&& vcpu_state(vm, vcpuid)->io.port == UNEXPECTED_VECTOR_PORT
		&& vcpu_state(vm, vcpuid)->io.size == 4) अणु
		/* Grab poपूर्णांकer to io data */
		uपूर्णांक32_t *data = (व्योम *)vcpu_state(vm, vcpuid)
			+ vcpu_state(vm, vcpuid)->io.data_offset;

		TEST_ASSERT(false,
			    "Unexpected vectored event in guest (vector:0x%x)",
			    *data);
	पूर्ण
पूर्ण

bool set_cpuid(काष्ठा kvm_cpuid2 *cpuid,
	       काष्ठा kvm_cpuid_entry2 *ent)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cpuid->nent; i++) अणु
		काष्ठा kvm_cpuid_entry2 *cur = &cpuid->entries[i];

		अगर (cur->function != ent->function || cur->index != ent->index)
			जारी;

		स_नकल(cur, ent, माप(काष्ठा kvm_cpuid_entry2));
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

uपूर्णांक64_t kvm_hypercall(uपूर्णांक64_t nr, uपूर्णांक64_t a0, uपूर्णांक64_t a1, uपूर्णांक64_t a2,
		       uपूर्णांक64_t a3)
अणु
	uपूर्णांक64_t r;

	यंत्र अस्थिर("vmcall"
		     : "=a"(r)
		     : "b"(a0), "c"(a1), "d"(a2), "S"(a3));
	वापस r;
पूर्ण

काष्ठा kvm_cpuid2 *kvm_get_supported_hv_cpuid(व्योम)
अणु
	अटल काष्ठा kvm_cpuid2 *cpuid;
	पूर्णांक ret;
	पूर्णांक kvm_fd;

	अगर (cpuid)
		वापस cpuid;

	cpuid = allocate_kvm_cpuid2();
	kvm_fd = खोलो_kvm_dev_path_or_निकास();

	ret = ioctl(kvm_fd, KVM_GET_SUPPORTED_HV_CPUID, cpuid);
	TEST_ASSERT(ret == 0, "KVM_GET_SUPPORTED_HV_CPUID failed %d %d\n",
		    ret, त्रुटि_सं);

	बंद(kvm_fd);
	वापस cpuid;
पूर्ण

व्योम vcpu_set_hv_cpuid(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	अटल काष्ठा kvm_cpuid2 *cpuid_full;
	काष्ठा kvm_cpuid2 *cpuid_sys, *cpuid_hv;
	पूर्णांक i, nent = 0;

	अगर (!cpuid_full) अणु
		cpuid_sys = kvm_get_supported_cpuid();
		cpuid_hv = kvm_get_supported_hv_cpuid();

		cpuid_full = दो_स्मृति(माप(*cpuid_full) +
				    (cpuid_sys->nent + cpuid_hv->nent) *
				    माप(काष्ठा kvm_cpuid_entry2));
		अगर (!cpuid_full) अणु
			लिखो_त्रुटि("malloc");
			पात();
		पूर्ण

		/* Need to skip KVM CPUID leaves 0x400000xx */
		क्रम (i = 0; i < cpuid_sys->nent; i++) अणु
			अगर (cpuid_sys->entries[i].function >= 0x40000000 &&
			    cpuid_sys->entries[i].function < 0x40000100)
				जारी;
			cpuid_full->entries[nent] = cpuid_sys->entries[i];
			nent++;
		पूर्ण

		स_नकल(&cpuid_full->entries[nent], cpuid_hv->entries,
		       cpuid_hv->nent * माप(काष्ठा kvm_cpuid_entry2));
		cpuid_full->nent = nent + cpuid_hv->nent;
	पूर्ण

	vcpu_set_cpuid(vm, vcpuid, cpuid_full);
पूर्ण

काष्ठा kvm_cpuid2 *vcpu_get_supported_hv_cpuid(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	अटल काष्ठा kvm_cpuid2 *cpuid;

	cpuid = allocate_kvm_cpuid2();

	vcpu_ioctl(vm, vcpuid, KVM_GET_SUPPORTED_HV_CPUID, cpuid);

	वापस cpuid;
पूर्ण
