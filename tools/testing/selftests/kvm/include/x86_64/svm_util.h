<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tools/testing/selftests/kvm/include/x86_64/svm_utils.h
 * Header क्रम nested SVM testing
 *
 * Copyright (C) 2020, Red Hat, Inc.
 */

#अगर_अघोषित SELFTEST_KVM_SVM_UTILS_H
#घोषणा SELFTEST_KVM_SVM_UTILS_H

#समावेश <मानक_निवेशt.h>
#समावेश "svm.h"
#समावेश "processor.h"

#घोषणा CPUID_SVM_BIT		2
#घोषणा CPUID_SVM		BIT_ULL(CPUID_SVM_BIT)

#घोषणा SVM_EXIT_VMMCALL	0x081

काष्ठा svm_test_data अणु
	/* VMCB */
	काष्ठा vmcb *vmcb; /* gva */
	व्योम *vmcb_hva;
	uपूर्णांक64_t vmcb_gpa;

	/* host state-save area */
	काष्ठा vmcb_save_area *save_area; /* gva */
	व्योम *save_area_hva;
	uपूर्णांक64_t save_area_gpa;
पूर्ण;

काष्ठा svm_test_data *vcpu_alloc_svm(काष्ठा kvm_vm *vm, vm_vaddr_t *p_svm_gva);
व्योम generic_svm_setup(काष्ठा svm_test_data *svm, व्योम *guest_rip, व्योम *guest_rsp);
व्योम run_guest(काष्ठा vmcb *vmcb, uपूर्णांक64_t vmcb_gpa);
bool nested_svm_supported(व्योम);
व्योम nested_svm_check_supported(व्योम);

अटल अंतरभूत bool cpu_has_svm(व्योम)
अणु
	u32 eax = 0x80000001, ecx;

	यंत्र("cpuid" :
	    "=a" (eax), "=c" (ecx) : "0" (eax) : "ebx", "edx");

	वापस ecx & CPUID_SVM;
पूर्ण

#पूर्ण_अगर /* SELFTEST_KVM_SVM_UTILS_H */
