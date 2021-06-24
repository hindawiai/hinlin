<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KVM dirty page logging test
 *
 * Copyright (C) 2018, Red Hat, Inc.
 */

#घोषणा _GNU_SOURCE /* क्रम program_invocation_name */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"
#समावेश "vmx.h"

#घोषणा VCPU_ID				1

/* The memory slot index to track dirty pages */
#घोषणा TEST_MEM_SLOT_INDEX		1
#घोषणा TEST_MEM_PAGES			3

/* L1 guest test भव memory offset */
#घोषणा GUEST_TEST_MEM			0xc0000000

/* L2 guest test भव memory offset */
#घोषणा NESTED_TEST_MEM1		0xc0001000
#घोषणा NESTED_TEST_MEM2		0xc0002000

अटल व्योम l2_guest_code(व्योम)
अणु
	*(अस्थिर uपूर्णांक64_t *)NESTED_TEST_MEM1;
	*(अस्थिर uपूर्णांक64_t *)NESTED_TEST_MEM1 = 1;
	GUEST_SYNC(true);
	GUEST_SYNC(false);

	*(अस्थिर uपूर्णांक64_t *)NESTED_TEST_MEM2 = 1;
	GUEST_SYNC(true);
	*(अस्थिर uपूर्णांक64_t *)NESTED_TEST_MEM2 = 1;
	GUEST_SYNC(true);
	GUEST_SYNC(false);

	/* Exit to L1 and never come back.  */
	vmcall();
पूर्ण

व्योम l1_guest_code(काष्ठा vmx_pages *vmx)
अणु
#घोषणा L2_GUEST_STACK_SIZE 64
	अचिन्हित दीर्घ l2_guest_stack[L2_GUEST_STACK_SIZE];

	GUEST_ASSERT(vmx->vmcs_gpa);
	GUEST_ASSERT(prepare_क्रम_vmx_operation(vmx));
	GUEST_ASSERT(load_vmcs(vmx));

	prepare_vmcs(vmx, l2_guest_code,
		     &l2_guest_stack[L2_GUEST_STACK_SIZE]);

	GUEST_SYNC(false);
	GUEST_ASSERT(!vmlaunch());
	GUEST_SYNC(false);
	GUEST_ASSERT(vmपढ़ोz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);
	GUEST_DONE();
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	vm_vaddr_t vmx_pages_gva = 0;
	काष्ठा vmx_pages *vmx;
	अचिन्हित दीर्घ *bmap;
	uपूर्णांक64_t *host_test_mem;

	काष्ठा kvm_vm *vm;
	काष्ठा kvm_run *run;
	काष्ठा ucall uc;
	bool करोne = false;

	nested_vmx_check_supported();

	/* Create VM */
	vm = vm_create_शेष(VCPU_ID, 0, l1_guest_code);
	vmx = vcpu_alloc_vmx(vm, &vmx_pages_gva);
	vcpu_args_set(vm, VCPU_ID, 1, vmx_pages_gva);
	run = vcpu_state(vm, VCPU_ID);

	/* Add an extra memory slot क्रम testing dirty logging */
	vm_userspace_mem_region_add(vm, VM_MEM_SRC_ANONYMOUS,
				    GUEST_TEST_MEM,
				    TEST_MEM_SLOT_INDEX,
				    TEST_MEM_PAGES,
				    KVM_MEM_LOG_सूचीTY_PAGES);

	/*
	 * Add an identity map क्रम GVA range [0xc0000000, 0xc0002000).  This
	 * affects both L1 and L2.  However...
	 */
	virt_map(vm, GUEST_TEST_MEM, GUEST_TEST_MEM, TEST_MEM_PAGES, 0);

	/*
	 * ... pages in the L2 GPA range [0xc0001000, 0xc0003000) will map to
	 * 0xc0000000.
	 *
	 * Note that prepare_eptp should be called only L1's GPA map is करोne,
	 * meaning after the last call to virt_map.
	 */
	prepare_eptp(vmx, vm, 0);
	nested_map_memslot(vmx, vm, 0, 0);
	nested_map(vmx, vm, NESTED_TEST_MEM1, GUEST_TEST_MEM, 4096, 0);
	nested_map(vmx, vm, NESTED_TEST_MEM2, GUEST_TEST_MEM, 4096, 0);

	bmap = biपंचांगap_alloc(TEST_MEM_PAGES);
	host_test_mem = addr_gpa2hva(vm, GUEST_TEST_MEM);

	जबतक (!करोne) अणु
		स_रखो(host_test_mem, 0xaa, TEST_MEM_PAGES * 4096);
		_vcpu_run(vm, VCPU_ID);
		TEST_ASSERT(run->निकास_reason == KVM_EXIT_IO,
			    "Unexpected exit reason: %u (%s),\n",
			    run->निकास_reason,
			    निकास_reason_str(run->निकास_reason));

		चयन (get_ucall(vm, VCPU_ID, &uc)) अणु
		हाल UCALL_ABORT:
			TEST_FAIL("%s at %s:%ld", (स्थिर अक्षर *)uc.args[0],
			       	  __खाता__, uc.args[1]);
			/* NOT REACHED */
		हाल UCALL_SYNC:
			/*
			 * The nested guest wrote at offset 0x1000 in the memslot, but the
			 * dirty biपंचांगap must be filled in according to L1 GPA, not L2.
			 */
			kvm_vm_get_dirty_log(vm, TEST_MEM_SLOT_INDEX, bmap);
			अगर (uc.args[1]) अणु
				TEST_ASSERT(test_bit(0, bmap), "Page 0 incorrectly reported clean\n");
				TEST_ASSERT(host_test_mem[0] == 1, "Page 0 not written by guest\n");
			पूर्ण अन्यथा अणु
				TEST_ASSERT(!test_bit(0, bmap), "Page 0 incorrectly reported dirty\n");
				TEST_ASSERT(host_test_mem[0] == 0xaaaaaaaaaaaaaaaaULL, "Page 0 written by guest\n");
			पूर्ण

			TEST_ASSERT(!test_bit(1, bmap), "Page 1 incorrectly reported dirty\n");
			TEST_ASSERT(host_test_mem[4096 / 8] == 0xaaaaaaaaaaaaaaaaULL, "Page 1 written by guest\n");
			TEST_ASSERT(!test_bit(2, bmap), "Page 2 incorrectly reported dirty\n");
			TEST_ASSERT(host_test_mem[8192 / 8] == 0xaaaaaaaaaaaaaaaaULL, "Page 2 written by guest\n");
			अवरोध;
		हाल UCALL_DONE:
			करोne = true;
			अवरोध;
		शेष:
			TEST_FAIL("Unknown ucall %lu", uc.cmd);
		पूर्ण
	पूर्ण
पूर्ण
