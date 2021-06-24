<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE /* क्रम program_invocation_लघु_name */
#समावेश <fcntl.h>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <semaphore.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>

#समावेश <linux/compiler.h>

#समावेश <test_util.h>
#समावेश <kvm_util.h>
#समावेश <processor.h>

#घोषणा VCPU_ID 0

/*
 * s390x needs at least 1MB alignment, and the x86_64 MOVE/DELETE tests need a
 * 2MB sized and aligned region so that the initial region corresponds to
 * exactly one large page.
 */
#घोषणा MEM_REGION_SIZE		0x200000

#अगर_घोषित __x86_64__
/*
 * Somewhat arbitrary location and slot, पूर्णांकended to not overlap anything.
 */
#घोषणा MEM_REGION_GPA		0xc0000000
#घोषणा MEM_REGION_SLOT		10

अटल स्थिर uपूर्णांक64_t MMIO_VAL = 0xbeefull;

बाह्य स्थिर uपूर्णांक64_t final_rip_start;
बाह्य स्थिर uपूर्णांक64_t final_rip_end;

अटल sem_t vcpu_पढ़ोy;

अटल अंतरभूत uपूर्णांक64_t guest_spin_on_val(uपूर्णांक64_t spin_val)
अणु
	uपूर्णांक64_t val;

	करो अणु
		val = READ_ONCE(*((uपूर्णांक64_t *)MEM_REGION_GPA));
	पूर्ण जबतक (val == spin_val);

	GUEST_SYNC(0);
	वापस val;
पूर्ण

अटल व्योम *vcpu_worker(व्योम *data)
अणु
	काष्ठा kvm_vm *vm = data;
	काष्ठा kvm_run *run;
	काष्ठा ucall uc;
	uपूर्णांक64_t cmd;

	/*
	 * Loop until the guest is करोne.  Re-enter the guest on all MMIO निकासs,
	 * which will occur अगर the guest attempts to access a memslot after it
	 * has been deleted or जबतक it is being moved .
	 */
	run = vcpu_state(vm, VCPU_ID);

	जबतक (1) अणु
		vcpu_run(vm, VCPU_ID);

		अगर (run->निकास_reason == KVM_EXIT_IO) अणु
			cmd = get_ucall(vm, VCPU_ID, &uc);
			अगर (cmd != UCALL_SYNC)
				अवरोध;

			sem_post(&vcpu_पढ़ोy);
			जारी;
		पूर्ण

		अगर (run->निकास_reason != KVM_EXIT_MMIO)
			अवरोध;

		TEST_ASSERT(!run->mmio.is_ग_लिखो, "Unexpected exit mmio write");
		TEST_ASSERT(run->mmio.len == 8,
			    "Unexpected exit mmio size = %u", run->mmio.len);

		TEST_ASSERT(run->mmio.phys_addr == MEM_REGION_GPA,
			    "Unexpected exit mmio address = 0x%llx",
			    run->mmio.phys_addr);
		स_नकल(run->mmio.data, &MMIO_VAL, 8);
	पूर्ण

	अगर (run->निकास_reason == KVM_EXIT_IO && cmd == UCALL_ABORT)
		TEST_FAIL("%s at %s:%ld, val = %lu", (स्थिर अक्षर *)uc.args[0],
			  __खाता__, uc.args[1], uc.args[2]);

	वापस शून्य;
पूर्ण

अटल व्योम रुको_क्रम_vcpu(व्योम)
अणु
	काष्ठा बारpec ts;

	TEST_ASSERT(!घड़ी_समय_लो(CLOCK_REALTIME, &ts),
		    "clock_gettime() failed: %d\n", त्रुटि_सं);

	ts.tv_sec += 2;
	TEST_ASSERT(!sem_समयdरुको(&vcpu_पढ़ोy, &ts),
		    "sem_timedwait() failed: %d\n", त्रुटि_सं);

	/* Wait क्रम the vCPU thपढ़ो to reenter the guest. */
	usleep(100000);
पूर्ण

अटल काष्ठा kvm_vm *spawn_vm(pthपढ़ो_t *vcpu_thपढ़ो, व्योम *guest_code)
अणु
	काष्ठा kvm_vm *vm;
	uपूर्णांक64_t *hva;
	uपूर्णांक64_t gpa;

	vm = vm_create_शेष(VCPU_ID, 0, guest_code);

	vm_userspace_mem_region_add(vm, VM_MEM_SRC_ANONYMOUS_THP,
				    MEM_REGION_GPA, MEM_REGION_SLOT,
				    MEM_REGION_SIZE / getpagesize(), 0);

	/*
	 * Allocate and map two pages so that the GPA accessed by guest_code()
	 * stays valid across the memslot move.
	 */
	gpa = vm_phy_pages_alloc(vm, 2, MEM_REGION_GPA, MEM_REGION_SLOT);
	TEST_ASSERT(gpa == MEM_REGION_GPA, "Failed vm_phy_pages_alloc\n");

	virt_map(vm, MEM_REGION_GPA, MEM_REGION_GPA, 2, 0);

	/* Ditto क्रम the host mapping so that both pages can be zeroed. */
	hva = addr_gpa2hva(vm, MEM_REGION_GPA);
	स_रखो(hva, 0, 2 * 4096);

	pthपढ़ो_create(vcpu_thपढ़ो, शून्य, vcpu_worker, vm);

	/* Ensure the guest thपढ़ो is spun up. */
	रुको_क्रम_vcpu();

	वापस vm;
पूर्ण


अटल व्योम guest_code_move_memory_region(व्योम)
अणु
	uपूर्णांक64_t val;

	GUEST_SYNC(0);

	/*
	 * Spin until the memory region starts getting moved to a
	 * misaligned address.
	 * Every region move may or may not trigger MMIO, as the
	 * winकरोw where the memslot is invalid is usually quite small.
	 */
	val = guest_spin_on_val(0);
	GUEST_ASSERT_1(val == 1 || val == MMIO_VAL, val);

	/* Spin until the misaligning memory region move completes. */
	val = guest_spin_on_val(MMIO_VAL);
	GUEST_ASSERT_1(val == 1 || val == 0, val);

	/* Spin until the memory region starts to get re-aligned. */
	val = guest_spin_on_val(0);
	GUEST_ASSERT_1(val == 1 || val == MMIO_VAL, val);

	/* Spin until the re-aligning memory region move completes. */
	val = guest_spin_on_val(MMIO_VAL);
	GUEST_ASSERT_1(val == 1, val);

	GUEST_DONE();
पूर्ण

अटल व्योम test_move_memory_region(व्योम)
अणु
	pthपढ़ो_t vcpu_thपढ़ो;
	काष्ठा kvm_vm *vm;
	uपूर्णांक64_t *hva;

	vm = spawn_vm(&vcpu_thपढ़ो, guest_code_move_memory_region);

	hva = addr_gpa2hva(vm, MEM_REGION_GPA);

	/*
	 * Shअगरt the region's base GPA.  The guest should not see "2" as the
	 * hva->gpa translation is misaligned, i.e. the guest is accessing a
	 * dअगरferent host pfn.
	 */
	vm_mem_region_move(vm, MEM_REGION_SLOT, MEM_REGION_GPA - 4096);
	WRITE_ONCE(*hva, 2);

	/*
	 * The guest _might_ see an invalid memslot and trigger MMIO, but it's
	 * a tiny winकरोw.  Spin and defer the sync until the memslot is
	 * restored and guest behavior is once again deterministic.
	 */
	usleep(100000);

	/*
	 * Note, value in memory needs to be changed *beक्रमe* restoring the
	 * memslot, अन्यथा the guest could race the update and see "2".
	 */
	WRITE_ONCE(*hva, 1);

	/* Restore the original base, the guest should see "1". */
	vm_mem_region_move(vm, MEM_REGION_SLOT, MEM_REGION_GPA);
	रुको_क्रम_vcpu();
	/* Defered sync from when the memslot was misaligned (above). */
	रुको_क्रम_vcpu();

	pthपढ़ो_join(vcpu_thपढ़ो, शून्य);

	kvm_vm_मुक्त(vm);
पूर्ण

अटल व्योम guest_code_delete_memory_region(व्योम)
अणु
	uपूर्णांक64_t val;

	GUEST_SYNC(0);

	/* Spin until the memory region is deleted. */
	val = guest_spin_on_val(0);
	GUEST_ASSERT_1(val == MMIO_VAL, val);

	/* Spin until the memory region is recreated. */
	val = guest_spin_on_val(MMIO_VAL);
	GUEST_ASSERT_1(val == 0, val);

	/* Spin until the memory region is deleted. */
	val = guest_spin_on_val(0);
	GUEST_ASSERT_1(val == MMIO_VAL, val);

	यंत्र("1:\n\t"
	    ".pushsection .rodata\n\t"
	    ".global final_rip_start\n\t"
	    "final_rip_start: .quad 1b\n\t"
	    ".popsection");

	/* Spin indefinitely (until the code memslot is deleted). */
	guest_spin_on_val(MMIO_VAL);

	यंत्र("1:\n\t"
	    ".pushsection .rodata\n\t"
	    ".global final_rip_end\n\t"
	    "final_rip_end: .quad 1b\n\t"
	    ".popsection");

	GUEST_ASSERT_1(0, 0);
पूर्ण

अटल व्योम test_delete_memory_region(व्योम)
अणु
	pthपढ़ो_t vcpu_thपढ़ो;
	काष्ठा kvm_regs regs;
	काष्ठा kvm_run *run;
	काष्ठा kvm_vm *vm;

	vm = spawn_vm(&vcpu_thपढ़ो, guest_code_delete_memory_region);

	/* Delete the memory region, the guest should not die. */
	vm_mem_region_delete(vm, MEM_REGION_SLOT);
	रुको_क्रम_vcpu();

	/* Recreate the memory region.  The guest should see "0". */
	vm_userspace_mem_region_add(vm, VM_MEM_SRC_ANONYMOUS_THP,
				    MEM_REGION_GPA, MEM_REGION_SLOT,
				    MEM_REGION_SIZE / getpagesize(), 0);
	रुको_क्रम_vcpu();

	/* Delete the region again so that there's only one memslot left. */
	vm_mem_region_delete(vm, MEM_REGION_SLOT);
	रुको_क्रम_vcpu();

	/*
	 * Delete the primary memslot.  This should cause an emulation error or
	 * shutकरोwn due to the page tables getting nuked.
	 */
	vm_mem_region_delete(vm, 0);

	pthपढ़ो_join(vcpu_thपढ़ो, शून्य);

	run = vcpu_state(vm, VCPU_ID);

	TEST_ASSERT(run->निकास_reason == KVM_EXIT_SHUTDOWN ||
		    run->निकास_reason == KVM_EXIT_INTERNAL_ERROR,
		    "Unexpected exit reason = %d", run->निकास_reason);

	vcpu_regs_get(vm, VCPU_ID, &regs);

	/*
	 * On AMD, after KVM_EXIT_SHUTDOWN the VMCB has been reinitialized alपढ़ोy,
	 * so the inकाष्ठाion poपूर्णांकer would poपूर्णांक to the reset vector.
	 */
	अगर (run->निकास_reason == KVM_EXIT_INTERNAL_ERROR)
		TEST_ASSERT(regs.rip >= final_rip_start &&
			    regs.rip < final_rip_end,
			    "Bad rip, expected 0x%lx - 0x%lx, got 0x%llx\n",
			    final_rip_start, final_rip_end, regs.rip);

	kvm_vm_मुक्त(vm);
पूर्ण

अटल व्योम test_zero_memory_regions(व्योम)
अणु
	काष्ठा kvm_run *run;
	काष्ठा kvm_vm *vm;

	pr_info("Testing KVM_RUN with zero added memory regions\n");

	vm = vm_create(VM_MODE_DEFAULT, 0, O_RDWR);
	vm_vcpu_add(vm, VCPU_ID);

	TEST_ASSERT(!ioctl(vm_get_fd(vm), KVM_SET_NR_MMU_PAGES, 64),
		    "KVM_SET_NR_MMU_PAGES failed, errno = %d\n", त्रुटि_सं);
	vcpu_run(vm, VCPU_ID);

	run = vcpu_state(vm, VCPU_ID);
	TEST_ASSERT(run->निकास_reason == KVM_EXIT_INTERNAL_ERROR,
		    "Unexpected exit_reason = %u\n", run->निकास_reason);

	kvm_vm_मुक्त(vm);
पूर्ण
#पूर्ण_अगर /* __x86_64__ */

अटल पूर्णांक test_memory_region_add(काष्ठा kvm_vm *vm, व्योम *mem, uपूर्णांक32_t slot,
				   uपूर्णांक32_t size, uपूर्णांक64_t guest_addr)
अणु
	काष्ठा kvm_userspace_memory_region region;
	पूर्णांक ret;

	region.slot = slot;
	region.flags = 0;
	region.guest_phys_addr = guest_addr;
	region.memory_size = size;
	region.userspace_addr = (uपूर्णांकptr_t) mem;
	ret = ioctl(vm_get_fd(vm), KVM_SET_USER_MEMORY_REGION, &region);

	वापस ret;
पूर्ण

/*
 * Test it can be added memory slots up to KVM_CAP_NR_MEMSLOTS, then any
 * tentative to add further slots should fail.
 */
अटल व्योम test_add_max_memory_regions(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा kvm_vm *vm;
	uपूर्णांक32_t max_mem_slots;
	uपूर्णांक32_t slot;
	व्योम *mem, *mem_aligned, *mem_extra;
	माप_प्रकार alignment;

#अगर_घोषित __s390x__
	/* On s390x, the host address must be aligned to 1M (due to PGSTEs) */
	alignment = 0x100000;
#अन्यथा
	alignment = 1;
#पूर्ण_अगर

	max_mem_slots = kvm_check_cap(KVM_CAP_NR_MEMSLOTS);
	TEST_ASSERT(max_mem_slots > 0,
		    "KVM_CAP_NR_MEMSLOTS should be greater than 0");
	pr_info("Allowed number of memory slots: %i\n", max_mem_slots);

	vm = vm_create(VM_MODE_DEFAULT, 0, O_RDWR);

	/* Check it can be added memory slots up to the maximum allowed */
	pr_info("Adding slots 0..%i, each memory region with %dK size\n",
		(max_mem_slots - 1), MEM_REGION_SIZE >> 10);

	mem = mmap(शून्य, MEM_REGION_SIZE * max_mem_slots + alignment,
		   PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	TEST_ASSERT(mem != MAP_FAILED, "Failed to mmap() host");
	mem_aligned = (व्योम *)(((माप_प्रकार) mem + alignment - 1) & ~(alignment - 1));

	क्रम (slot = 0; slot < max_mem_slots; slot++) अणु
		ret = test_memory_region_add(vm, mem_aligned +
					     ((uपूर्णांक64_t)slot * MEM_REGION_SIZE),
					     slot, MEM_REGION_SIZE,
					     (uपूर्णांक64_t)slot * MEM_REGION_SIZE);
		TEST_ASSERT(ret == 0, "KVM_SET_USER_MEMORY_REGION IOCTL failed,\n"
			    "  rc: %i errno: %i slot: %i\n",
			    ret, त्रुटि_सं, slot);
	पूर्ण

	/* Check it cannot be added memory slots beyond the limit */
	mem_extra = mmap(शून्य, MEM_REGION_SIZE, PROT_READ | PROT_WRITE,
			 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	TEST_ASSERT(mem_extra != MAP_FAILED, "Failed to mmap() host");

	ret = test_memory_region_add(vm, mem_extra, max_mem_slots, MEM_REGION_SIZE,
				     (uपूर्णांक64_t)max_mem_slots * MEM_REGION_SIZE);
	TEST_ASSERT(ret == -1 && त्रुटि_सं == EINVAL,
		    "Adding one more memory slot should fail with EINVAL");

	munmap(mem, MEM_REGION_SIZE * max_mem_slots + alignment);
	munmap(mem_extra, MEM_REGION_SIZE);
	kvm_vm_मुक्त(vm);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
#अगर_घोषित __x86_64__
	पूर्णांक i, loops;
#पूर्ण_अगर

	/* Tell मानक_निकास not to buffer its content */
	रखो_बफ(मानक_निकास, शून्य);

#अगर_घोषित __x86_64__
	/*
	 * FIXME: the zero-memslot test fails on aarch64 and s390x because
	 * KVM_RUN fails with ENOEXEC or EFAULT.
	 */
	test_zero_memory_regions();
#पूर्ण_अगर

	test_add_max_memory_regions();

#अगर_घोषित __x86_64__
	अगर (argc > 1)
		loops = म_से_प(argv[1]);
	अन्यथा
		loops = 10;

	pr_info("Testing MOVE of in-use region, %d loops\n", loops);
	क्रम (i = 0; i < loops; i++)
		test_move_memory_region();

	pr_info("Testing DELETE of in-use region, %d loops\n", loops);
	क्रम (i = 0; i < loops; i++)
		test_delete_memory_region();
#पूर्ण_अगर

	वापस 0;
पूर्ण
