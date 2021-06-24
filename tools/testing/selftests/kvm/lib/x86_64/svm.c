<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tools/testing/selftests/kvm/lib/x86_64/svm.c
 * Helpers used क्रम nested SVM testing
 * Largely inspired from KVM unit test svm.c
 *
 * Copyright (C) 2020, Red Hat, Inc.
 */

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "../kvm_util_internal.h"
#समावेश "processor.h"
#समावेश "svm_util.h"

काष्ठा gpr64_regs guest_regs;
u64 rflags;

/* Allocate memory regions क्रम nested SVM tests.
 *
 * Input Args:
 *   vm - The VM to allocate guest-भव addresses in.
 *
 * Output Args:
 *   p_svm_gva - The guest भव address क्रम the काष्ठा svm_test_data.
 *
 * Return:
 *   Poपूर्णांकer to काष्ठाure with the addresses of the SVM areas.
 */
काष्ठा svm_test_data *
vcpu_alloc_svm(काष्ठा kvm_vm *vm, vm_vaddr_t *p_svm_gva)
अणु
	vm_vaddr_t svm_gva = vm_vaddr_alloc(vm, getpagesize(),
					    0x10000, 0, 0);
	काष्ठा svm_test_data *svm = addr_gva2hva(vm, svm_gva);

	svm->vmcb = (व्योम *)vm_vaddr_alloc(vm, getpagesize(),
					   0x10000, 0, 0);
	svm->vmcb_hva = addr_gva2hva(vm, (uपूर्णांकptr_t)svm->vmcb);
	svm->vmcb_gpa = addr_gva2gpa(vm, (uपूर्णांकptr_t)svm->vmcb);

	svm->save_area = (व्योम *)vm_vaddr_alloc(vm, getpagesize(),
						0x10000, 0, 0);
	svm->save_area_hva = addr_gva2hva(vm, (uपूर्णांकptr_t)svm->save_area);
	svm->save_area_gpa = addr_gva2gpa(vm, (uपूर्णांकptr_t)svm->save_area);

	*p_svm_gva = svm_gva;
	वापस svm;
पूर्ण

अटल व्योम vmcb_set_seg(काष्ठा vmcb_seg *seg, u16 selector,
			 u64 base, u32 limit, u32 attr)
अणु
	seg->selector = selector;
	seg->attrib = attr;
	seg->limit = limit;
	seg->base = base;
पूर्ण

व्योम generic_svm_setup(काष्ठा svm_test_data *svm, व्योम *guest_rip, व्योम *guest_rsp)
अणु
	काष्ठा vmcb *vmcb = svm->vmcb;
	uपूर्णांक64_t vmcb_gpa = svm->vmcb_gpa;
	काष्ठा vmcb_save_area *save = &vmcb->save;
	काष्ठा vmcb_control_area *ctrl = &vmcb->control;
	u32 data_seg_attr = 3 | SVM_SELECTOR_S_MASK | SVM_SELECTOR_P_MASK
	      | SVM_SELECTOR_DB_MASK | SVM_SELECTOR_G_MASK;
	u32 code_seg_attr = 9 | SVM_SELECTOR_S_MASK | SVM_SELECTOR_P_MASK
		| SVM_SELECTOR_L_MASK | SVM_SELECTOR_G_MASK;
	uपूर्णांक64_t efer;

	efer = rdmsr(MSR_EFER);
	wrmsr(MSR_EFER, efer | EFER_SVME);
	wrmsr(MSR_VM_HSAVE_PA, svm->save_area_gpa);

	स_रखो(vmcb, 0, माप(*vmcb));
	यंत्र अस्थिर ("vmsave %0\n\t" : : "a" (vmcb_gpa) : "memory");
	vmcb_set_seg(&save->es, get_es(), 0, -1U, data_seg_attr);
	vmcb_set_seg(&save->cs, get_cs(), 0, -1U, code_seg_attr);
	vmcb_set_seg(&save->ss, get_ss(), 0, -1U, data_seg_attr);
	vmcb_set_seg(&save->ds, get_ds(), 0, -1U, data_seg_attr);
	vmcb_set_seg(&save->gdtr, 0, get_gdt().address, get_gdt().size, 0);
	vmcb_set_seg(&save->idtr, 0, get_idt().address, get_idt().size, 0);

	ctrl->asid = 1;
	save->cpl = 0;
	save->efer = rdmsr(MSR_EFER);
	यंत्र अस्थिर ("mov %%cr4, %0" : "=r"(save->cr4) : : "memory");
	यंत्र अस्थिर ("mov %%cr3, %0" : "=r"(save->cr3) : : "memory");
	यंत्र अस्थिर ("mov %%cr0, %0" : "=r"(save->cr0) : : "memory");
	यंत्र अस्थिर ("mov %%dr7, %0" : "=r"(save->dr7) : : "memory");
	यंत्र अस्थिर ("mov %%dr6, %0" : "=r"(save->dr6) : : "memory");
	यंत्र अस्थिर ("mov %%cr2, %0" : "=r"(save->cr2) : : "memory");
	save->g_pat = rdmsr(MSR_IA32_CR_PAT);
	save->dbgctl = rdmsr(MSR_IA32_DEBUGCTLMSR);
	ctrl->पूर्णांकercept = (1ULL << INTERCEPT_VMRUN) |
				(1ULL << INTERCEPT_VMMCALL);

	vmcb->save.rip = (u64)guest_rip;
	vmcb->save.rsp = (u64)guest_rsp;
	guest_regs.rdi = (u64)svm;
पूर्ण

/*
 * save/restore 64-bit general रेजिस्टरs except rax, rip, rsp
 * which are directly handed through the VMCB guest processor state
 */
#घोषणा SAVE_GPR_C				\
	"xchg %%rbx, guest_regs+0x20\n\t"	\
	"xchg %%rcx, guest_regs+0x10\n\t"	\
	"xchg %%rdx, guest_regs+0x18\n\t"	\
	"xchg %%rbp, guest_regs+0x30\n\t"	\
	"xchg %%rsi, guest_regs+0x38\n\t"	\
	"xchg %%rdi, guest_regs+0x40\n\t"	\
	"xchg %%r8,  guest_regs+0x48\n\t"	\
	"xchg %%r9,  guest_regs+0x50\n\t"	\
	"xchg %%r10, guest_regs+0x58\n\t"	\
	"xchg %%r11, guest_regs+0x60\n\t"	\
	"xchg %%r12, guest_regs+0x68\n\t"	\
	"xchg %%r13, guest_regs+0x70\n\t"	\
	"xchg %%r14, guest_regs+0x78\n\t"	\
	"xchg %%r15, guest_regs+0x80\n\t"

#घोषणा LOAD_GPR_C      SAVE_GPR_C

/*
 * selftests करो not use पूर्णांकerrupts so we dropped clgi/sti/cli/stgi
 * क्रम now. रेजिस्टरs involved in LOAD/SAVE_GPR_C are eventually
 * unmodअगरied so they करो not need to be in the clobber list.
 */
व्योम run_guest(काष्ठा vmcb *vmcb, uपूर्णांक64_t vmcb_gpa)
अणु
	यंत्र अस्थिर (
		"vmload %[vmcb_gpa]\n\t"
		"mov rflags, %%r15\n\t"	// rflags
		"mov %%r15, 0x170(%[vmcb])\n\t"
		"mov guest_regs, %%r15\n\t"	// rax
		"mov %%r15, 0x1f8(%[vmcb])\n\t"
		LOAD_GPR_C
		"vmrun %[vmcb_gpa]\n\t"
		SAVE_GPR_C
		"mov 0x170(%[vmcb]), %%r15\n\t"	// rflags
		"mov %%r15, rflags\n\t"
		"mov 0x1f8(%[vmcb]), %%r15\n\t"	// rax
		"mov %%r15, guest_regs\n\t"
		"vmsave %[vmcb_gpa]\n\t"
		: : [vmcb] "r" (vmcb), [vmcb_gpa] "a" (vmcb_gpa)
		: "r15", "memory");
पूर्ण

bool nested_svm_supported(व्योम)
अणु
	काष्ठा kvm_cpuid_entry2 *entry =
		kvm_get_supported_cpuid_entry(0x80000001);

	वापस entry->ecx & CPUID_SVM;
पूर्ण

व्योम nested_svm_check_supported(व्योम)
अणु
	अगर (!nested_svm_supported()) अणु
		prपूर्णांक_skip("nested SVM not enabled");
		निकास(KSFT_SKIP);
	पूर्ण
पूर्ण
