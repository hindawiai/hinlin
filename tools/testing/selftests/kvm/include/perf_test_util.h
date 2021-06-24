<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * tools/testing/selftests/kvm/include/perf_test_util.h
 *
 * Copyright (C) 2020, Google LLC.
 */

#अगर_अघोषित SELFTEST_KVM_PERF_TEST_UTIL_H
#घोषणा SELFTEST_KVM_PERF_TEST_UTIL_H

#समावेश "kvm_util.h"

/* Default guest test भव memory offset */
#घोषणा DEFAULT_GUEST_TEST_MEM		0xc0000000

#घोषणा DEFAULT_PER_VCPU_MEM_SIZE	(1 << 30) /* 1G */

#घोषणा PERF_TEST_MEM_SLOT_INDEX	1

काष्ठा perf_test_vcpu_args अणु
	uपूर्णांक64_t gva;
	uपूर्णांक64_t pages;

	/* Only used by the host userspace part of the vCPU thपढ़ो */
	पूर्णांक vcpu_id;
पूर्ण;

काष्ठा perf_test_args अणु
	काष्ठा kvm_vm *vm;
	uपूर्णांक64_t host_page_size;
	uपूर्णांक64_t guest_page_size;
	पूर्णांक wr_fract;

	काष्ठा perf_test_vcpu_args vcpu_args[KVM_MAX_VCPUS];
पूर्ण;

बाह्य काष्ठा perf_test_args perf_test_args;

/*
 * Guest physical memory offset of the testing memory slot.
 * This will be set to the topmost valid physical address minus
 * the test memory size.
 */
बाह्य uपूर्णांक64_t guest_test_phys_mem;

काष्ठा kvm_vm *perf_test_create_vm(क्रमागत vm_guest_mode mode, पूर्णांक vcpus,
				   uपूर्णांक64_t vcpu_memory_bytes,
				   क्रमागत vm_mem_backing_src_type backing_src);
व्योम perf_test_destroy_vm(काष्ठा kvm_vm *vm);
व्योम perf_test_setup_vcpus(काष्ठा kvm_vm *vm, पूर्णांक vcpus,
			   uपूर्णांक64_t vcpu_memory_bytes,
			   bool partition_vcpu_memory_access);

#पूर्ण_अगर /* SELFTEST_KVM_PERF_TEST_UTIL_H */
