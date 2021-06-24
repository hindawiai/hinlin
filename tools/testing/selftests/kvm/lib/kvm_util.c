<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tools/testing/selftests/kvm/lib/kvm_util.c
 *
 * Copyright (C) 2018, Google LLC.
 */

#घोषणा _GNU_SOURCE /* क्रम program_invocation_name */
#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "kvm_util_internal.h"
#समावेश "processor.h"

#समावेश <निश्चित.स>
#समावेश <sys/mman.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <linux/kernel.h>

#घोषणा KVM_UTIL_MIN_PFN	2

अटल पूर्णांक vcpu_mmap_sz(व्योम);

/* Aligns x up to the next multiple of size. Size must be a घातer of 2. */
अटल व्योम *align(व्योम *x, माप_प्रकार size)
अणु
	माप_प्रकार mask = size - 1;
	TEST_ASSERT(size != 0 && !(size & (size - 1)),
		    "size not a power of 2: %lu", size);
	वापस (व्योम *) (((माप_प्रकार) x + mask) & ~mask);
पूर्ण

/*
 * Open KVM_DEV_PATH अगर available, otherwise निकास the entire program.
 *
 * Input Args:
 *   flags - The flags to pass when खोलोing KVM_DEV_PATH.
 *
 * Return:
 *   The खोलोed file descriptor of /dev/kvm.
 */
अटल पूर्णांक _खोलो_kvm_dev_path_or_निकास(पूर्णांक flags)
अणु
	पूर्णांक fd;

	fd = खोलो(KVM_DEV_PATH, flags);
	अगर (fd < 0) अणु
		prपूर्णांक_skip("%s not available, is KVM loaded? (errno: %d)",
			   KVM_DEV_PATH, त्रुटि_सं);
		निकास(KSFT_SKIP);
	पूर्ण

	वापस fd;
पूर्ण

पूर्णांक खोलो_kvm_dev_path_or_निकास(व्योम)
अणु
	वापस _खोलो_kvm_dev_path_or_निकास(O_RDONLY);
पूर्ण

/*
 * Capability
 *
 * Input Args:
 *   cap - Capability
 *
 * Output Args: None
 *
 * Return:
 *   On success, the Value corresponding to the capability (KVM_CAP_*)
 *   specअगरied by the value of cap.  On failure a TEST_ASSERT failure
 *   is produced.
 *
 * Looks up and वापसs the value corresponding to the capability
 * (KVM_CAP_*) given by cap.
 */
पूर्णांक kvm_check_cap(दीर्घ cap)
अणु
	पूर्णांक ret;
	पूर्णांक kvm_fd;

	kvm_fd = खोलो_kvm_dev_path_or_निकास();
	ret = ioctl(kvm_fd, KVM_CHECK_EXTENSION, cap);
	TEST_ASSERT(ret >= 0, "KVM_CHECK_EXTENSION IOCTL failed,\n"
		"  rc: %i errno: %i", ret, त्रुटि_सं);

	बंद(kvm_fd);

	वापस ret;
पूर्ण

/* VM Enable Capability
 *
 * Input Args:
 *   vm - Virtual Machine
 *   cap - Capability
 *
 * Output Args: None
 *
 * Return: On success, 0. On failure a TEST_ASSERT failure is produced.
 *
 * Enables a capability (KVM_CAP_*) on the VM.
 */
पूर्णांक vm_enable_cap(काष्ठा kvm_vm *vm, काष्ठा kvm_enable_cap *cap)
अणु
	पूर्णांक ret;

	ret = ioctl(vm->fd, KVM_ENABLE_CAP, cap);
	TEST_ASSERT(ret == 0, "KVM_ENABLE_CAP IOCTL failed,\n"
		"  rc: %i errno: %i", ret, त्रुटि_सं);

	वापस ret;
पूर्ण

/* VCPU Enable Capability
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpu_id - VCPU
 *   cap - Capability
 *
 * Output Args: None
 *
 * Return: On success, 0. On failure a TEST_ASSERT failure is produced.
 *
 * Enables a capability (KVM_CAP_*) on the VCPU.
 */
पूर्णांक vcpu_enable_cap(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpu_id,
		    काष्ठा kvm_enable_cap *cap)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpu_id);
	पूर्णांक r;

	TEST_ASSERT(vcpu, "cannot find vcpu %d", vcpu_id);

	r = ioctl(vcpu->fd, KVM_ENABLE_CAP, cap);
	TEST_ASSERT(!r, "KVM_ENABLE_CAP vCPU ioctl failed,\n"
			"  rc: %i, errno: %i", r, त्रुटि_सं);

	वापस r;
पूर्ण

व्योम vm_enable_dirty_ring(काष्ठा kvm_vm *vm, uपूर्णांक32_t ring_size)
अणु
	काष्ठा kvm_enable_cap cap = अणु 0 पूर्ण;

	cap.cap = KVM_CAP_सूचीTY_LOG_RING;
	cap.args[0] = ring_size;
	vm_enable_cap(vm, &cap);
	vm->dirty_ring_size = ring_size;
पूर्ण

अटल व्योम vm_खोलो(काष्ठा kvm_vm *vm, पूर्णांक perm)
अणु
	vm->kvm_fd = _खोलो_kvm_dev_path_or_निकास(perm);

	अगर (!kvm_check_cap(KVM_CAP_IMMEDIATE_EXIT)) अणु
		prपूर्णांक_skip("immediate_exit not available");
		निकास(KSFT_SKIP);
	पूर्ण

	vm->fd = ioctl(vm->kvm_fd, KVM_CREATE_VM, vm->type);
	TEST_ASSERT(vm->fd >= 0, "KVM_CREATE_VM ioctl failed, "
		"rc: %i errno: %i", vm->fd, त्रुटि_सं);
पूर्ण

स्थिर अक्षर *vm_guest_mode_string(uपूर्णांक32_t i)
अणु
	अटल स्थिर अक्षर * स्थिर strings[] = अणु
		[VM_MODE_P52V48_4K]	= "PA-bits:52,  VA-bits:48,  4K pages",
		[VM_MODE_P52V48_64K]	= "PA-bits:52,  VA-bits:48, 64K pages",
		[VM_MODE_P48V48_4K]	= "PA-bits:48,  VA-bits:48,  4K pages",
		[VM_MODE_P48V48_64K]	= "PA-bits:48,  VA-bits:48, 64K pages",
		[VM_MODE_P40V48_4K]	= "PA-bits:40,  VA-bits:48,  4K pages",
		[VM_MODE_P40V48_64K]	= "PA-bits:40,  VA-bits:48, 64K pages",
		[VM_MODE_PXXV48_4K]	= "PA-bits:ANY, VA-bits:48,  4K pages",
		[VM_MODE_P47V64_4K]	= "PA-bits:47,  VA-bits:64,  4K pages",
	पूर्ण;
	_Static_निश्चित(माप(strings)/माप(अक्षर *) == NUM_VM_MODES,
		       "Missing new mode strings?");

	TEST_ASSERT(i < NUM_VM_MODES, "Guest mode ID %d too big", i);

	वापस strings[i];
पूर्ण

स्थिर काष्ठा vm_guest_mode_params vm_guest_mode_params[] = अणु
	अणु 52, 48,  0x1000, 12 पूर्ण,
	अणु 52, 48, 0x10000, 16 पूर्ण,
	अणु 48, 48,  0x1000, 12 पूर्ण,
	अणु 48, 48, 0x10000, 16 पूर्ण,
	अणु 40, 48,  0x1000, 12 पूर्ण,
	अणु 40, 48, 0x10000, 16 पूर्ण,
	अणु  0,  0,  0x1000, 12 पूर्ण,
	अणु 47, 64,  0x1000, 12 पूर्ण,
पूर्ण;
_Static_निश्चित(माप(vm_guest_mode_params)/माप(काष्ठा vm_guest_mode_params) == NUM_VM_MODES,
	       "Missing new mode params?");

/*
 * VM Create
 *
 * Input Args:
 *   mode - VM Mode (e.g. VM_MODE_P52V48_4K)
 *   phy_pages - Physical memory pages
 *   perm - permission
 *
 * Output Args: None
 *
 * Return:
 *   Poपूर्णांकer to opaque काष्ठाure that describes the created VM.
 *
 * Creates a VM with the mode specअगरied by mode (e.g. VM_MODE_P52V48_4K).
 * When phy_pages is non-zero, a memory region of phy_pages physical pages
 * is created and mapped starting at guest physical address 0.  The file
 * descriptor to control the created VM is created with the permissions
 * given by perm (e.g. O_RDWR).
 */
काष्ठा kvm_vm *vm_create(क्रमागत vm_guest_mode mode, uपूर्णांक64_t phy_pages, पूर्णांक perm)
अणु
	काष्ठा kvm_vm *vm;

	pr_debug("%s: mode='%s' pages='%ld' perm='%d'\n", __func__,
		 vm_guest_mode_string(mode), phy_pages, perm);

	vm = सुस्मृति(1, माप(*vm));
	TEST_ASSERT(vm != शून्य, "Insufficient Memory");

	INIT_LIST_HEAD(&vm->vcpus);
	vm->regions.gpa_tree = RB_ROOT;
	vm->regions.hva_tree = RB_ROOT;
	hash_init(vm->regions.slot_hash);

	vm->mode = mode;
	vm->type = 0;

	vm->pa_bits = vm_guest_mode_params[mode].pa_bits;
	vm->va_bits = vm_guest_mode_params[mode].va_bits;
	vm->page_size = vm_guest_mode_params[mode].page_size;
	vm->page_shअगरt = vm_guest_mode_params[mode].page_shअगरt;

	/* Setup mode specअगरic traits. */
	चयन (vm->mode) अणु
	हाल VM_MODE_P52V48_4K:
		vm->pgtable_levels = 4;
		अवरोध;
	हाल VM_MODE_P52V48_64K:
		vm->pgtable_levels = 3;
		अवरोध;
	हाल VM_MODE_P48V48_4K:
		vm->pgtable_levels = 4;
		अवरोध;
	हाल VM_MODE_P48V48_64K:
		vm->pgtable_levels = 3;
		अवरोध;
	हाल VM_MODE_P40V48_4K:
		vm->pgtable_levels = 4;
		अवरोध;
	हाल VM_MODE_P40V48_64K:
		vm->pgtable_levels = 3;
		अवरोध;
	हाल VM_MODE_PXXV48_4K:
#अगर_घोषित __x86_64__
		kvm_get_cpu_address_width(&vm->pa_bits, &vm->va_bits);
		/*
		 * Ignore KVM support क्रम 5-level paging (vm->va_bits == 57),
		 * it करोesn't take effect unless a CR4.LA57 is set, which it
		 * isn't क्रम this VM_MODE.
		 */
		TEST_ASSERT(vm->va_bits == 48 || vm->va_bits == 57,
			    "Linear address width (%d bits) not supported",
			    vm->va_bits);
		pr_debug("Guest physical address width detected: %d\n",
			 vm->pa_bits);
		vm->pgtable_levels = 4;
		vm->va_bits = 48;
#अन्यथा
		TEST_FAIL("VM_MODE_PXXV48_4K not supported on non-x86 platforms");
#पूर्ण_अगर
		अवरोध;
	हाल VM_MODE_P47V64_4K:
		vm->pgtable_levels = 5;
		अवरोध;
	शेष:
		TEST_FAIL("Unknown guest mode, mode: 0x%x", mode);
	पूर्ण

#अगर_घोषित __aarch64__
	अगर (vm->pa_bits != 40)
		vm->type = KVM_VM_TYPE_ARM_IPA_SIZE(vm->pa_bits);
#पूर्ण_अगर

	vm_खोलो(vm, perm);

	/* Limit to VA-bit canonical भव addresses. */
	vm->vpages_valid = sparsebit_alloc();
	sparsebit_set_num(vm->vpages_valid,
		0, (1ULL << (vm->va_bits - 1)) >> vm->page_shअगरt);
	sparsebit_set_num(vm->vpages_valid,
		(~((1ULL << (vm->va_bits - 1)) - 1)) >> vm->page_shअगरt,
		(1ULL << (vm->va_bits - 1)) >> vm->page_shअगरt);

	/* Limit physical addresses to PA-bits. */
	vm->max_gfn = ((1ULL << vm->pa_bits) >> vm->page_shअगरt) - 1;

	/* Allocate and setup memory क्रम guest. */
	vm->vpages_mapped = sparsebit_alloc();
	अगर (phy_pages != 0)
		vm_userspace_mem_region_add(vm, VM_MEM_SRC_ANONYMOUS,
					    0, 0, phy_pages, 0);

	वापस vm;
पूर्ण

/*
 * VM Create with customized parameters
 *
 * Input Args:
 *   mode - VM Mode (e.g. VM_MODE_P52V48_4K)
 *   nr_vcpus - VCPU count
 *   slot0_mem_pages - Slot0 physical memory size
 *   extra_mem_pages - Non-slot0 physical memory total size
 *   num_percpu_pages - Per-cpu physical memory pages
 *   guest_code - Guest entry poपूर्णांक
 *   vcpuids - VCPU IDs
 *
 * Output Args: None
 *
 * Return:
 *   Poपूर्णांकer to opaque काष्ठाure that describes the created VM.
 *
 * Creates a VM with the mode specअगरied by mode (e.g. VM_MODE_P52V48_4K),
 * with customized slot0 memory size, at least 512 pages currently.
 * extra_mem_pages is only used to calculate the maximum page table size,
 * no real memory allocation क्रम non-slot0 memory in this function.
 */
काष्ठा kvm_vm *vm_create_with_vcpus(क्रमागत vm_guest_mode mode, uपूर्णांक32_t nr_vcpus,
				    uपूर्णांक64_t slot0_mem_pages, uपूर्णांक64_t extra_mem_pages,
				    uपूर्णांक32_t num_percpu_pages, व्योम *guest_code,
				    uपूर्णांक32_t vcpuids[])
अणु
	uपूर्णांक64_t vcpu_pages, extra_pg_pages, pages;
	काष्ठा kvm_vm *vm;
	पूर्णांक i;

	/* Force slot0 memory size not small than DEFAULT_GUEST_PHY_PAGES */
	अगर (slot0_mem_pages < DEFAULT_GUEST_PHY_PAGES)
		slot0_mem_pages = DEFAULT_GUEST_PHY_PAGES;

	/* The maximum page table size क्रम a memory region will be when the
	 * smallest pages are used. Considering each page contains x page
	 * table descriptors, the total extra size क्रम page tables (क्रम extra
	 * N pages) will be: N/x+N/x^2+N/x^3+... which is definitely smaller
	 * than N/x*2.
	 */
	vcpu_pages = (DEFAULT_STACK_PGS + num_percpu_pages) * nr_vcpus;
	extra_pg_pages = (slot0_mem_pages + extra_mem_pages + vcpu_pages) / PTES_PER_MIN_PAGE * 2;
	pages = slot0_mem_pages + vcpu_pages + extra_pg_pages;

	TEST_ASSERT(nr_vcpus <= kvm_check_cap(KVM_CAP_MAX_VCPUS),
		    "nr_vcpus = %d too large for host, max-vcpus = %d",
		    nr_vcpus, kvm_check_cap(KVM_CAP_MAX_VCPUS));

	pages = vm_adjust_num_guest_pages(mode, pages);
	vm = vm_create(mode, pages, O_RDWR);

	kvm_vm_elf_load(vm, program_invocation_name, 0, 0);

#अगर_घोषित __x86_64__
	vm_create_irqchip(vm);
#पूर्ण_अगर

	क्रम (i = 0; i < nr_vcpus; ++i) अणु
		uपूर्णांक32_t vcpuid = vcpuids ? vcpuids[i] : i;

		vm_vcpu_add_शेष(vm, vcpuid, guest_code);

#अगर_घोषित __x86_64__
		vcpu_set_cpuid(vm, vcpuid, kvm_get_supported_cpuid());
#पूर्ण_अगर
	पूर्ण

	वापस vm;
पूर्ण

काष्ठा kvm_vm *vm_create_शेष_with_vcpus(uपूर्णांक32_t nr_vcpus, uपूर्णांक64_t extra_mem_pages,
					    uपूर्णांक32_t num_percpu_pages, व्योम *guest_code,
					    uपूर्णांक32_t vcpuids[])
अणु
	वापस vm_create_with_vcpus(VM_MODE_DEFAULT, nr_vcpus, DEFAULT_GUEST_PHY_PAGES,
				    extra_mem_pages, num_percpu_pages, guest_code, vcpuids);
पूर्ण

काष्ठा kvm_vm *vm_create_शेष(uपूर्णांक32_t vcpuid, uपूर्णांक64_t extra_mem_pages,
				 व्योम *guest_code)
अणु
	वापस vm_create_शेष_with_vcpus(1, extra_mem_pages, 0, guest_code,
					    (uपूर्णांक32_t [])अणु vcpuid पूर्ण);
पूर्ण

/*
 * VM Restart
 *
 * Input Args:
 *   vm - VM that has been released beक्रमe
 *   perm - permission
 *
 * Output Args: None
 *
 * Reखोलोs the file descriptors associated to the VM and reinstates the
 * global state, such as the irqchip and the memory regions that are mapped
 * पूर्णांकo the guest.
 */
व्योम kvm_vm_restart(काष्ठा kvm_vm *vmp, पूर्णांक perm)
अणु
	पूर्णांक ctr;
	काष्ठा userspace_mem_region *region;

	vm_खोलो(vmp, perm);
	अगर (vmp->has_irqchip)
		vm_create_irqchip(vmp);

	hash_क्रम_each(vmp->regions.slot_hash, ctr, region, slot_node) अणु
		पूर्णांक ret = ioctl(vmp->fd, KVM_SET_USER_MEMORY_REGION, &region->region);
		TEST_ASSERT(ret == 0, "KVM_SET_USER_MEMORY_REGION IOCTL failed,\n"
			    "  rc: %i errno: %i\n"
			    "  slot: %u flags: 0x%x\n"
			    "  guest_phys_addr: 0x%llx size: 0x%llx",
			    ret, त्रुटि_सं, region->region.slot,
			    region->region.flags,
			    region->region.guest_phys_addr,
			    region->region.memory_size);
	पूर्ण
पूर्ण

व्योम kvm_vm_get_dirty_log(काष्ठा kvm_vm *vm, पूर्णांक slot, व्योम *log)
अणु
	काष्ठा kvm_dirty_log args = अणु .dirty_biपंचांगap = log, .slot = slot पूर्ण;
	पूर्णांक ret;

	ret = ioctl(vm->fd, KVM_GET_सूचीTY_LOG, &args);
	TEST_ASSERT(ret == 0, "%s: KVM_GET_DIRTY_LOG failed: %s",
		    __func__, म_त्रुटि(-ret));
पूर्ण

व्योम kvm_vm_clear_dirty_log(काष्ठा kvm_vm *vm, पूर्णांक slot, व्योम *log,
			    uपूर्णांक64_t first_page, uपूर्णांक32_t num_pages)
अणु
	काष्ठा kvm_clear_dirty_log args = अणु .dirty_biपंचांगap = log, .slot = slot,
		                            .first_page = first_page,
	                                    .num_pages = num_pages पूर्ण;
	पूर्णांक ret;

	ret = ioctl(vm->fd, KVM_CLEAR_सूचीTY_LOG, &args);
	TEST_ASSERT(ret == 0, "%s: KVM_CLEAR_DIRTY_LOG failed: %s",
		    __func__, म_त्रुटि(-ret));
पूर्ण

uपूर्णांक32_t kvm_vm_reset_dirty_ring(काष्ठा kvm_vm *vm)
अणु
	वापस ioctl(vm->fd, KVM_RESET_सूचीTY_RINGS);
पूर्ण

/*
 * Userspace Memory Region Find
 *
 * Input Args:
 *   vm - Virtual Machine
 *   start - Starting VM physical address
 *   end - Ending VM physical address, inclusive.
 *
 * Output Args: None
 *
 * Return:
 *   Poपूर्णांकer to overlapping region, शून्य अगर no such region.
 *
 * Searches क्रम a region with any physical memory that overlaps with
 * any portion of the guest physical addresses from start to end
 * inclusive.  If multiple overlapping regions exist, a poपूर्णांकer to any
 * of the regions is वापसed.  Null is वापसed only when no overlapping
 * region exists.
 */
अटल काष्ठा userspace_mem_region *
userspace_mem_region_find(काष्ठा kvm_vm *vm, uपूर्णांक64_t start, uपूर्णांक64_t end)
अणु
	काष्ठा rb_node *node;

	क्रम (node = vm->regions.gpa_tree.rb_node; node; ) अणु
		काष्ठा userspace_mem_region *region =
			container_of(node, काष्ठा userspace_mem_region, gpa_node);
		uपूर्णांक64_t existing_start = region->region.guest_phys_addr;
		uपूर्णांक64_t existing_end = region->region.guest_phys_addr
			+ region->region.memory_size - 1;
		अगर (start <= existing_end && end >= existing_start)
			वापस region;

		अगर (start < existing_start)
			node = node->rb_left;
		अन्यथा
			node = node->rb_right;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * KVM Userspace Memory Region Find
 *
 * Input Args:
 *   vm - Virtual Machine
 *   start - Starting VM physical address
 *   end - Ending VM physical address, inclusive.
 *
 * Output Args: None
 *
 * Return:
 *   Poपूर्णांकer to overlapping region, शून्य अगर no such region.
 *
 * Public पूर्णांकerface to userspace_mem_region_find. Allows tests to look up
 * the memslot dataकाष्ठाure क्रम a given range of guest physical memory.
 */
काष्ठा kvm_userspace_memory_region *
kvm_userspace_memory_region_find(काष्ठा kvm_vm *vm, uपूर्णांक64_t start,
				 uपूर्णांक64_t end)
अणु
	काष्ठा userspace_mem_region *region;

	region = userspace_mem_region_find(vm, start, end);
	अगर (!region)
		वापस शून्य;

	वापस &region->region;
पूर्ण

/*
 * VCPU Find
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *
 * Output Args: None
 *
 * Return:
 *   Poपूर्णांकer to VCPU काष्ठाure
 *
 * Locates a vcpu काष्ठाure that describes the VCPU specअगरied by vcpuid and
 * वापसs a poपूर्णांकer to it.  Returns शून्य अगर the VM करोesn't contain a VCPU
 * क्रम the specअगरied vcpuid.
 */
काष्ठा vcpu *vcpu_find(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा vcpu *vcpu;

	list_क्रम_each_entry(vcpu, &vm->vcpus, list) अणु
		अगर (vcpu->id == vcpuid)
			वापस vcpu;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * VM VCPU Remove
 *
 * Input Args:
 *   vcpu - VCPU to हटाओ
 *
 * Output Args: None
 *
 * Return: None, TEST_ASSERT failures क्रम all error conditions
 *
 * Removes a vCPU from a VM and मुक्तs its resources.
 */
अटल व्योम vm_vcpu_rm(काष्ठा kvm_vm *vm, काष्ठा vcpu *vcpu)
अणु
	पूर्णांक ret;

	अगर (vcpu->dirty_gfns) अणु
		ret = munmap(vcpu->dirty_gfns, vm->dirty_ring_size);
		TEST_ASSERT(ret == 0, "munmap of VCPU dirty ring failed, "
			    "rc: %i errno: %i", ret, त्रुटि_सं);
		vcpu->dirty_gfns = शून्य;
	पूर्ण

	ret = munmap(vcpu->state, vcpu_mmap_sz());
	TEST_ASSERT(ret == 0, "munmap of VCPU fd failed, rc: %i "
		"errno: %i", ret, त्रुटि_सं);
	ret = बंद(vcpu->fd);
	TEST_ASSERT(ret == 0, "Close of VCPU fd failed, rc: %i "
		"errno: %i", ret, त्रुटि_सं);

	list_del(&vcpu->list);
	मुक्त(vcpu);
पूर्ण

व्योम kvm_vm_release(काष्ठा kvm_vm *vmp)
अणु
	काष्ठा vcpu *vcpu, *पंचांगp;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(vcpu, पंचांगp, &vmp->vcpus, list)
		vm_vcpu_rm(vmp, vcpu);

	ret = बंद(vmp->fd);
	TEST_ASSERT(ret == 0, "Close of vm fd failed,\n"
		"  vmp->fd: %i rc: %i errno: %i", vmp->fd, ret, त्रुटि_सं);

	ret = बंद(vmp->kvm_fd);
	TEST_ASSERT(ret == 0, "Close of /dev/kvm fd failed,\n"
		"  vmp->kvm_fd: %i rc: %i errno: %i", vmp->kvm_fd, ret, त्रुटि_सं);
पूर्ण

अटल व्योम __vm_mem_region_delete(काष्ठा kvm_vm *vm,
				   काष्ठा userspace_mem_region *region,
				   bool unlink)
अणु
	पूर्णांक ret;

	अगर (unlink) अणु
		rb_erase(&region->gpa_node, &vm->regions.gpa_tree);
		rb_erase(&region->hva_node, &vm->regions.hva_tree);
		hash_del(&region->slot_node);
	पूर्ण

	region->region.memory_size = 0;
	ret = ioctl(vm->fd, KVM_SET_USER_MEMORY_REGION, &region->region);
	TEST_ASSERT(ret == 0, "KVM_SET_USER_MEMORY_REGION IOCTL failed, "
		    "rc: %i errno: %i", ret, त्रुटि_सं);

	sparsebit_मुक्त(&region->unused_phy_pages);
	ret = munmap(region->mmap_start, region->mmap_size);
	TEST_ASSERT(ret == 0, "munmap failed, rc: %i errno: %i", ret, त्रुटि_सं);

	मुक्त(region);
पूर्ण

/*
 * Destroys and मुक्तs the VM poपूर्णांकed to by vmp.
 */
व्योम kvm_vm_मुक्त(काष्ठा kvm_vm *vmp)
अणु
	पूर्णांक ctr;
	काष्ठा hlist_node *node;
	काष्ठा userspace_mem_region *region;

	अगर (vmp == शून्य)
		वापस;

	/* Free userspace_mem_regions. */
	hash_क्रम_each_safe(vmp->regions.slot_hash, ctr, node, region, slot_node)
		__vm_mem_region_delete(vmp, region, false);

	/* Free sparsebit arrays. */
	sparsebit_मुक्त(&vmp->vpages_valid);
	sparsebit_मुक्त(&vmp->vpages_mapped);

	kvm_vm_release(vmp);

	/* Free the काष्ठाure describing the VM. */
	मुक्त(vmp);
पूर्ण

/*
 * Memory Compare, host भव to guest भव
 *
 * Input Args:
 *   hva - Starting host भव address
 *   vm - Virtual Machine
 *   gva - Starting guest भव address
 *   len - number of bytes to compare
 *
 * Output Args: None
 *
 * Input/Output Args: None
 *
 * Return:
 *   Returns 0 अगर the bytes starting at hva क्रम a length of len
 *   are equal the guest भव bytes starting at gva.  Returns
 *   a value < 0, अगर bytes at hva are less than those at gva.
 *   Otherwise a value > 0 is वापसed.
 *
 * Compares the bytes starting at the host भव address hva, क्रम
 * a length of len, to the guest bytes starting at the guest भव
 * address given by gva.
 */
पूर्णांक kvm_स_भेद_hva_gva(व्योम *hva, काष्ठा kvm_vm *vm, vm_vaddr_t gva, माप_प्रकार len)
अणु
	माप_प्रकार amt;

	/*
	 * Compare a batch of bytes until either a match is found
	 * or all the bytes have been compared.
	 */
	क्रम (uपूर्णांकptr_t offset = 0; offset < len; offset += amt) अणु
		uपूर्णांकptr_t ptr1 = (uपूर्णांकptr_t)hva + offset;

		/*
		 * Determine host address क्रम guest भव address
		 * at offset.
		 */
		uपूर्णांकptr_t ptr2 = (uपूर्णांकptr_t)addr_gva2hva(vm, gva + offset);

		/*
		 * Determine amount to compare on this pass.
		 * Don't allow the comparsion to cross a page boundary.
		 */
		amt = len - offset;
		अगर ((ptr1 >> vm->page_shअगरt) != ((ptr1 + amt) >> vm->page_shअगरt))
			amt = vm->page_size - (ptr1 % vm->page_size);
		अगर ((ptr2 >> vm->page_shअगरt) != ((ptr2 + amt) >> vm->page_shअगरt))
			amt = vm->page_size - (ptr2 % vm->page_size);

		निश्चित((ptr1 >> vm->page_shअगरt) == ((ptr1 + amt - 1) >> vm->page_shअगरt));
		निश्चित((ptr2 >> vm->page_shअगरt) == ((ptr2 + amt - 1) >> vm->page_shअगरt));

		/*
		 * Perक्रमm the comparison.  If there is a dअगरference
		 * वापस that result to the caller, otherwise need
		 * to जारी on looking क्रम a mismatch.
		 */
		पूर्णांक ret = स_भेद((व्योम *)ptr1, (व्योम *)ptr2, amt);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	/*
	 * No mismatch found.  Let the caller know the two memory
	 * areas are equal.
	 */
	वापस 0;
पूर्ण

अटल व्योम vm_userspace_mem_region_gpa_insert(काष्ठा rb_root *gpa_tree,
					       काष्ठा userspace_mem_region *region)
अणु
	काष्ठा rb_node **cur, *parent;

	क्रम (cur = &gpa_tree->rb_node, parent = शून्य; *cur; ) अणु
		काष्ठा userspace_mem_region *cregion;

		cregion = container_of(*cur, typeof(*cregion), gpa_node);
		parent = *cur;
		अगर (region->region.guest_phys_addr <
		    cregion->region.guest_phys_addr)
			cur = &(*cur)->rb_left;
		अन्यथा अणु
			TEST_ASSERT(region->region.guest_phys_addr !=
				    cregion->region.guest_phys_addr,
				    "Duplicate GPA in region tree");

			cur = &(*cur)->rb_right;
		पूर्ण
	पूर्ण

	rb_link_node(&region->gpa_node, parent, cur);
	rb_insert_color(&region->gpa_node, gpa_tree);
पूर्ण

अटल व्योम vm_userspace_mem_region_hva_insert(काष्ठा rb_root *hva_tree,
					       काष्ठा userspace_mem_region *region)
अणु
	काष्ठा rb_node **cur, *parent;

	क्रम (cur = &hva_tree->rb_node, parent = शून्य; *cur; ) अणु
		काष्ठा userspace_mem_region *cregion;

		cregion = container_of(*cur, typeof(*cregion), hva_node);
		parent = *cur;
		अगर (region->host_mem < cregion->host_mem)
			cur = &(*cur)->rb_left;
		अन्यथा अणु
			TEST_ASSERT(region->host_mem !=
				    cregion->host_mem,
				    "Duplicate HVA in region tree");

			cur = &(*cur)->rb_right;
		पूर्ण
	पूर्ण

	rb_link_node(&region->hva_node, parent, cur);
	rb_insert_color(&region->hva_node, hva_tree);
पूर्ण

/*
 * VM Userspace Memory Region Add
 *
 * Input Args:
 *   vm - Virtual Machine
 *   src_type - Storage source क्रम this region.
 *              शून्य to use anonymous memory.
 *   guest_paddr - Starting guest physical address
 *   slot - KVM region slot
 *   npages - Number of physical pages
 *   flags - KVM memory region flags (e.g. KVM_MEM_LOG_सूचीTY_PAGES)
 *
 * Output Args: None
 *
 * Return: None
 *
 * Allocates a memory area of the number of pages specअगरied by npages
 * and maps it to the VM specअगरied by vm, at a starting physical address
 * given by guest_paddr.  The region is created with a KVM region slot
 * given by slot, which must be unique and < KVM_MEM_SLOTS_NUM.  The
 * region is created with the flags given by flags.
 */
व्योम vm_userspace_mem_region_add(काष्ठा kvm_vm *vm,
	क्रमागत vm_mem_backing_src_type src_type,
	uपूर्णांक64_t guest_paddr, uपूर्णांक32_t slot, uपूर्णांक64_t npages,
	uपूर्णांक32_t flags)
अणु
	पूर्णांक ret;
	काष्ठा userspace_mem_region *region;
	माप_प्रकार backing_src_pagesz = get_backing_src_pagesz(src_type);
	माप_प्रकार alignment;

	TEST_ASSERT(vm_adjust_num_guest_pages(vm->mode, npages) == npages,
		"Number of guest pages is not compatible with the host. "
		"Try npages=%d", vm_adjust_num_guest_pages(vm->mode, npages));

	TEST_ASSERT((guest_paddr % vm->page_size) == 0, "Guest physical "
		"address not on a page boundary.\n"
		"  guest_paddr: 0x%lx vm->page_size: 0x%x",
		guest_paddr, vm->page_size);
	TEST_ASSERT((((guest_paddr >> vm->page_shअगरt) + npages) - 1)
		<= vm->max_gfn, "Physical range beyond maximum "
		"supported physical address,\n"
		"  guest_paddr: 0x%lx npages: 0x%lx\n"
		"  vm->max_gfn: 0x%lx vm->page_size: 0x%x",
		guest_paddr, npages, vm->max_gfn, vm->page_size);

	/*
	 * Confirm a mem region with an overlapping address करोesn't
	 * alपढ़ोy exist.
	 */
	region = (काष्ठा userspace_mem_region *) userspace_mem_region_find(
		vm, guest_paddr, (guest_paddr + npages * vm->page_size) - 1);
	अगर (region != शून्य)
		TEST_FAIL("overlapping userspace_mem_region already "
			"exists\n"
			"  requested guest_paddr: 0x%lx npages: 0x%lx "
			"page_size: 0x%x\n"
			"  existing guest_paddr: 0x%lx size: 0x%lx",
			guest_paddr, npages, vm->page_size,
			(uपूर्णांक64_t) region->region.guest_phys_addr,
			(uपूर्णांक64_t) region->region.memory_size);

	/* Confirm no region with the requested slot alपढ़ोy exists. */
	hash_क्रम_each_possible(vm->regions.slot_hash, region, slot_node,
			       slot) अणु
		अगर (region->region.slot != slot)
			जारी;

		TEST_FAIL("A mem region with the requested slot "
			"already exists.\n"
			"  requested slot: %u paddr: 0x%lx npages: 0x%lx\n"
			"  existing slot: %u paddr: 0x%lx size: 0x%lx",
			slot, guest_paddr, npages,
			region->region.slot,
			(uपूर्णांक64_t) region->region.guest_phys_addr,
			(uपूर्णांक64_t) region->region.memory_size);
	पूर्ण

	/* Allocate and initialize new mem region काष्ठाure. */
	region = सुस्मृति(1, माप(*region));
	TEST_ASSERT(region != शून्य, "Insufficient Memory");
	region->mmap_size = npages * vm->page_size;

#अगर_घोषित __s390x__
	/* On s390x, the host address must be aligned to 1M (due to PGSTEs) */
	alignment = 0x100000;
#अन्यथा
	alignment = 1;
#पूर्ण_अगर

	अगर (src_type == VM_MEM_SRC_ANONYMOUS_THP)
		alignment = max(backing_src_pagesz, alignment);

	/* Add enough memory to align up अगर necessary */
	अगर (alignment > 1)
		region->mmap_size += alignment;

	region->fd = -1;
	अगर (backing_src_is_shared(src_type)) अणु
		पूर्णांक memfd_flags = MFD_CLOEXEC;

		अगर (src_type == VM_MEM_SRC_SHARED_HUGETLB)
			memfd_flags |= MFD_HUGETLB;

		region->fd = memfd_create("kvm_selftest", memfd_flags);
		TEST_ASSERT(region->fd != -1,
			    "memfd_create failed, errno: %i", त्रुटि_सं);

		ret = ftruncate(region->fd, region->mmap_size);
		TEST_ASSERT(ret == 0, "ftruncate failed, errno: %i", त्रुटि_सं);

		ret = fallocate(region->fd,
				FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE, 0,
				region->mmap_size);
		TEST_ASSERT(ret == 0, "fallocate failed, errno: %i", त्रुटि_सं);
	पूर्ण

	region->mmap_start = mmap(शून्य, region->mmap_size,
				  PROT_READ | PROT_WRITE,
				  vm_mem_backing_src_alias(src_type)->flag,
				  region->fd, 0);
	TEST_ASSERT(region->mmap_start != MAP_FAILED,
		    "test_malloc failed, mmap_start: %p errno: %i",
		    region->mmap_start, त्रुटि_सं);

	/* Align host address */
	region->host_mem = align(region->mmap_start, alignment);

	/* As needed perक्रमm madvise */
	अगर ((src_type == VM_MEM_SRC_ANONYMOUS ||
	     src_type == VM_MEM_SRC_ANONYMOUS_THP) && thp_configured()) अणु
		ret = madvise(region->host_mem, npages * vm->page_size,
			      src_type == VM_MEM_SRC_ANONYMOUS ? MADV_NOHUGEPAGE : MADV_HUGEPAGE);
		TEST_ASSERT(ret == 0, "madvise failed, addr: %p length: 0x%lx src_type: %s",
			    region->host_mem, npages * vm->page_size,
			    vm_mem_backing_src_alias(src_type)->name);
	पूर्ण

	region->unused_phy_pages = sparsebit_alloc();
	sparsebit_set_num(region->unused_phy_pages,
		guest_paddr >> vm->page_shअगरt, npages);
	region->region.slot = slot;
	region->region.flags = flags;
	region->region.guest_phys_addr = guest_paddr;
	region->region.memory_size = npages * vm->page_size;
	region->region.userspace_addr = (uपूर्णांकptr_t) region->host_mem;
	ret = ioctl(vm->fd, KVM_SET_USER_MEMORY_REGION, &region->region);
	TEST_ASSERT(ret == 0, "KVM_SET_USER_MEMORY_REGION IOCTL failed,\n"
		"  rc: %i errno: %i\n"
		"  slot: %u flags: 0x%x\n"
		"  guest_phys_addr: 0x%lx size: 0x%lx",
		ret, त्रुटि_सं, slot, flags,
		guest_paddr, (uपूर्णांक64_t) region->region.memory_size);

	/* Add to quick lookup data काष्ठाures */
	vm_userspace_mem_region_gpa_insert(&vm->regions.gpa_tree, region);
	vm_userspace_mem_region_hva_insert(&vm->regions.hva_tree, region);
	hash_add(vm->regions.slot_hash, &region->slot_node, slot);

	/* If shared memory, create an alias. */
	अगर (region->fd >= 0) अणु
		region->mmap_alias = mmap(शून्य, region->mmap_size,
					  PROT_READ | PROT_WRITE,
					  vm_mem_backing_src_alias(src_type)->flag,
					  region->fd, 0);
		TEST_ASSERT(region->mmap_alias != MAP_FAILED,
			    "mmap of alias failed, errno: %i", त्रुटि_सं);

		/* Align host alias address */
		region->host_alias = align(region->mmap_alias, alignment);
	पूर्ण
पूर्ण

/*
 * Memslot to region
 *
 * Input Args:
 *   vm - Virtual Machine
 *   memslot - KVM memory slot ID
 *
 * Output Args: None
 *
 * Return:
 *   Poपूर्णांकer to memory region काष्ठाure that describe memory region
 *   using kvm memory slot ID given by memslot.  TEST_ASSERT failure
 *   on error (e.g. currently no memory region using memslot as a KVM
 *   memory slot ID).
 */
काष्ठा userspace_mem_region *
memslot2region(काष्ठा kvm_vm *vm, uपूर्णांक32_t memslot)
अणु
	काष्ठा userspace_mem_region *region;

	hash_क्रम_each_possible(vm->regions.slot_hash, region, slot_node,
			       memslot)
		अगर (region->region.slot == memslot)
			वापस region;

	ख_लिखो(मानक_त्रुटि, "No mem region with the requested slot found,\n"
		"  requested slot: %u\n", memslot);
	ख_माला_दो("---- vm dump ----\n", मानक_त्रुटि);
	vm_dump(मानक_त्रुटि, vm, 2);
	TEST_FAIL("Mem region not found");
	वापस शून्य;
पूर्ण

/*
 * VM Memory Region Flags Set
 *
 * Input Args:
 *   vm - Virtual Machine
 *   flags - Starting guest physical address
 *
 * Output Args: None
 *
 * Return: None
 *
 * Sets the flags of the memory region specअगरied by the value of slot,
 * to the values given by flags.
 */
व्योम vm_mem_region_set_flags(काष्ठा kvm_vm *vm, uपूर्णांक32_t slot, uपूर्णांक32_t flags)
अणु
	पूर्णांक ret;
	काष्ठा userspace_mem_region *region;

	region = memslot2region(vm, slot);

	region->region.flags = flags;

	ret = ioctl(vm->fd, KVM_SET_USER_MEMORY_REGION, &region->region);

	TEST_ASSERT(ret == 0, "KVM_SET_USER_MEMORY_REGION IOCTL failed,\n"
		"  rc: %i errno: %i slot: %u flags: 0x%x",
		ret, त्रुटि_सं, slot, flags);
पूर्ण

/*
 * VM Memory Region Move
 *
 * Input Args:
 *   vm - Virtual Machine
 *   slot - Slot of the memory region to move
 *   new_gpa - Starting guest physical address
 *
 * Output Args: None
 *
 * Return: None
 *
 * Change the gpa of a memory region.
 */
व्योम vm_mem_region_move(काष्ठा kvm_vm *vm, uपूर्णांक32_t slot, uपूर्णांक64_t new_gpa)
अणु
	काष्ठा userspace_mem_region *region;
	पूर्णांक ret;

	region = memslot2region(vm, slot);

	region->region.guest_phys_addr = new_gpa;

	ret = ioctl(vm->fd, KVM_SET_USER_MEMORY_REGION, &region->region);

	TEST_ASSERT(!ret, "KVM_SET_USER_MEMORY_REGION failed\n"
		    "ret: %i errno: %i slot: %u new_gpa: 0x%lx",
		    ret, त्रुटि_सं, slot, new_gpa);
पूर्ण

/*
 * VM Memory Region Delete
 *
 * Input Args:
 *   vm - Virtual Machine
 *   slot - Slot of the memory region to delete
 *
 * Output Args: None
 *
 * Return: None
 *
 * Delete a memory region.
 */
व्योम vm_mem_region_delete(काष्ठा kvm_vm *vm, uपूर्णांक32_t slot)
अणु
	__vm_mem_region_delete(vm, memslot2region(vm, slot), true);
पूर्ण

/*
 * VCPU mmap Size
 *
 * Input Args: None
 *
 * Output Args: None
 *
 * Return:
 *   Size of VCPU state
 *
 * Returns the size of the काष्ठाure poपूर्णांकed to by the वापस value
 * of vcpu_state().
 */
अटल पूर्णांक vcpu_mmap_sz(व्योम)
अणु
	पूर्णांक dev_fd, ret;

	dev_fd = खोलो_kvm_dev_path_or_निकास();

	ret = ioctl(dev_fd, KVM_GET_VCPU_MMAP_SIZE, शून्य);
	TEST_ASSERT(ret >= माप(काष्ठा kvm_run),
		"%s KVM_GET_VCPU_MMAP_SIZE ioctl failed, rc: %i errno: %i",
		__func__, ret, त्रुटि_सं);

	बंद(dev_fd);

	वापस ret;
पूर्ण

/*
 * VM VCPU Add
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *
 * Output Args: None
 *
 * Return: None
 *
 * Adds a भव CPU to the VM specअगरied by vm with the ID given by vcpuid.
 * No additional VCPU setup is करोne.
 */
व्योम vm_vcpu_add(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा vcpu *vcpu;

	/* Confirm a vcpu with the specअगरied id करोesn't alपढ़ोy exist. */
	vcpu = vcpu_find(vm, vcpuid);
	अगर (vcpu != शून्य)
		TEST_FAIL("vcpu with the specified id "
			"already exists,\n"
			"  requested vcpuid: %u\n"
			"  existing vcpuid: %u state: %p",
			vcpuid, vcpu->id, vcpu->state);

	/* Allocate and initialize new vcpu काष्ठाure. */
	vcpu = सुस्मृति(1, माप(*vcpu));
	TEST_ASSERT(vcpu != शून्य, "Insufficient Memory");
	vcpu->id = vcpuid;
	vcpu->fd = ioctl(vm->fd, KVM_CREATE_VCPU, vcpuid);
	TEST_ASSERT(vcpu->fd >= 0, "KVM_CREATE_VCPU failed, rc: %i errno: %i",
		vcpu->fd, त्रुटि_सं);

	TEST_ASSERT(vcpu_mmap_sz() >= माप(*vcpu->state), "vcpu mmap size "
		"smaller than expected, vcpu_mmap_sz: %i expected_min: %zi",
		vcpu_mmap_sz(), माप(*vcpu->state));
	vcpu->state = (काष्ठा kvm_run *) mmap(शून्य, vcpu_mmap_sz(),
		PROT_READ | PROT_WRITE, MAP_SHARED, vcpu->fd, 0);
	TEST_ASSERT(vcpu->state != MAP_FAILED, "mmap vcpu_state failed, "
		"vcpu id: %u errno: %i", vcpuid, त्रुटि_सं);

	/* Add to linked-list of VCPUs. */
	list_add(&vcpu->list, &vm->vcpus);
पूर्ण

/*
 * VM Virtual Address Unused Gap
 *
 * Input Args:
 *   vm - Virtual Machine
 *   sz - Size (bytes)
 *   vaddr_min - Minimum Virtual Address
 *
 * Output Args: None
 *
 * Return:
 *   Lowest भव address at or below vaddr_min, with at least
 *   sz unused bytes.  TEST_ASSERT failure अगर no area of at least
 *   size sz is available.
 *
 * Within the VM specअगरied by vm, locates the lowest starting भव
 * address >= vaddr_min, that has at least sz unallocated bytes.  A
 * TEST_ASSERT failure occurs क्रम invalid input or no area of at least
 * sz unallocated bytes >= vaddr_min is available.
 */
अटल vm_vaddr_t vm_vaddr_unused_gap(काष्ठा kvm_vm *vm, माप_प्रकार sz,
				      vm_vaddr_t vaddr_min)
अणु
	uपूर्णांक64_t pages = (sz + vm->page_size - 1) >> vm->page_shअगरt;

	/* Determine lowest permitted भव page index. */
	uपूर्णांक64_t pgidx_start = (vaddr_min + vm->page_size - 1) >> vm->page_shअगरt;
	अगर ((pgidx_start * vm->page_size) < vaddr_min)
		जाओ no_va_found;

	/* Loop over section with enough valid भव page indexes. */
	अगर (!sparsebit_is_set_num(vm->vpages_valid,
		pgidx_start, pages))
		pgidx_start = sparsebit_next_set_num(vm->vpages_valid,
			pgidx_start, pages);
	करो अणु
		/*
		 * Are there enough unused भव pages available at
		 * the currently proposed starting भव page index.
		 * If not, adjust proposed starting index to next
		 * possible.
		 */
		अगर (sparsebit_is_clear_num(vm->vpages_mapped,
			pgidx_start, pages))
			जाओ va_found;
		pgidx_start = sparsebit_next_clear_num(vm->vpages_mapped,
			pgidx_start, pages);
		अगर (pgidx_start == 0)
			जाओ no_va_found;

		/*
		 * If needed, adjust proposed starting भव address,
		 * to next range of valid भव addresses.
		 */
		अगर (!sparsebit_is_set_num(vm->vpages_valid,
			pgidx_start, pages)) अणु
			pgidx_start = sparsebit_next_set_num(
				vm->vpages_valid, pgidx_start, pages);
			अगर (pgidx_start == 0)
				जाओ no_va_found;
		पूर्ण
	पूर्ण जबतक (pgidx_start != 0);

no_va_found:
	TEST_FAIL("No vaddr of specified pages available, pages: 0x%lx", pages);

	/* NOT REACHED */
	वापस -1;

va_found:
	TEST_ASSERT(sparsebit_is_set_num(vm->vpages_valid,
		pgidx_start, pages),
		"Unexpected, invalid virtual page index range,\n"
		"  pgidx_start: 0x%lx\n"
		"  pages: 0x%lx",
		pgidx_start, pages);
	TEST_ASSERT(sparsebit_is_clear_num(vm->vpages_mapped,
		pgidx_start, pages),
		"Unexpected, pages already mapped,\n"
		"  pgidx_start: 0x%lx\n"
		"  pages: 0x%lx",
		pgidx_start, pages);

	वापस pgidx_start * vm->page_size;
पूर्ण

/*
 * VM Virtual Address Allocate
 *
 * Input Args:
 *   vm - Virtual Machine
 *   sz - Size in bytes
 *   vaddr_min - Minimum starting भव address
 *   data_memslot - Memory region slot क्रम data pages
 *   pgd_memslot - Memory region slot क्रम new भव translation tables
 *
 * Output Args: None
 *
 * Return:
 *   Starting guest भव address
 *
 * Allocates at least sz bytes within the भव address space of the vm
 * given by vm.  The allocated bytes are mapped to a भव address >=
 * the address given by vaddr_min.  Note that each allocation uses a
 * a unique set of pages, with the minimum real allocation being at least
 * a page.
 */
vm_vaddr_t vm_vaddr_alloc(काष्ठा kvm_vm *vm, माप_प्रकार sz, vm_vaddr_t vaddr_min,
			  uपूर्णांक32_t data_memslot, uपूर्णांक32_t pgd_memslot)
अणु
	uपूर्णांक64_t pages = (sz >> vm->page_shअगरt) + ((sz % vm->page_size) != 0);

	virt_pgd_alloc(vm, pgd_memslot);
	vm_paddr_t paddr = vm_phy_pages_alloc(vm, pages,
					      KVM_UTIL_MIN_PFN * vm->page_size,
					      data_memslot);

	/*
	 * Find an unused range of भव page addresses of at least
	 * pages in length.
	 */
	vm_vaddr_t vaddr_start = vm_vaddr_unused_gap(vm, sz, vaddr_min);

	/* Map the भव pages. */
	क्रम (vm_vaddr_t vaddr = vaddr_start; pages > 0;
		pages--, vaddr += vm->page_size, paddr += vm->page_size) अणु

		virt_pg_map(vm, vaddr, paddr, pgd_memslot);

		sparsebit_set(vm->vpages_mapped,
			vaddr >> vm->page_shअगरt);
	पूर्ण

	वापस vaddr_start;
पूर्ण

/*
 * Map a range of VM भव address to the VM's physical address
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vaddr - Virtuall address to map
 *   paddr - VM Physical Address
 *   npages - The number of pages to map
 *   pgd_memslot - Memory region slot क्रम new भव translation tables
 *
 * Output Args: None
 *
 * Return: None
 *
 * Within the VM given by @vm, creates a भव translation क्रम
 * @npages starting at @vaddr to the page range starting at @paddr.
 */
व्योम virt_map(काष्ठा kvm_vm *vm, uपूर्णांक64_t vaddr, uपूर्णांक64_t paddr,
	      अचिन्हित पूर्णांक npages, uपूर्णांक32_t pgd_memslot)
अणु
	माप_प्रकार page_size = vm->page_size;
	माप_प्रकार size = npages * page_size;

	TEST_ASSERT(vaddr + size > vaddr, "Vaddr overflow");
	TEST_ASSERT(paddr + size > paddr, "Paddr overflow");

	जबतक (npages--) अणु
		virt_pg_map(vm, vaddr, paddr, pgd_memslot);
		vaddr += page_size;
		paddr += page_size;
	पूर्ण
पूर्ण

/*
 * Address VM Physical to Host Virtual
 *
 * Input Args:
 *   vm - Virtual Machine
 *   gpa - VM physical address
 *
 * Output Args: None
 *
 * Return:
 *   Equivalent host भव address
 *
 * Locates the memory region containing the VM physical address given
 * by gpa, within the VM given by vm.  When found, the host भव
 * address providing the memory to the vm physical address is वापसed.
 * A TEST_ASSERT failure occurs अगर no region containing gpa exists.
 */
व्योम *addr_gpa2hva(काष्ठा kvm_vm *vm, vm_paddr_t gpa)
अणु
	काष्ठा userspace_mem_region *region;

	region = userspace_mem_region_find(vm, gpa, gpa);
	अगर (!region) अणु
		TEST_FAIL("No vm physical memory at 0x%lx", gpa);
		वापस शून्य;
	पूर्ण

	वापस (व्योम *)((uपूर्णांकptr_t)region->host_mem
		+ (gpa - region->region.guest_phys_addr));
पूर्ण

/*
 * Address Host Virtual to VM Physical
 *
 * Input Args:
 *   vm - Virtual Machine
 *   hva - Host भव address
 *
 * Output Args: None
 *
 * Return:
 *   Equivalent VM physical address
 *
 * Locates the memory region containing the host भव address given
 * by hva, within the VM given by vm.  When found, the equivalent
 * VM physical address is वापसed. A TEST_ASSERT failure occurs अगर no
 * region containing hva exists.
 */
vm_paddr_t addr_hva2gpa(काष्ठा kvm_vm *vm, व्योम *hva)
अणु
	काष्ठा rb_node *node;

	क्रम (node = vm->regions.hva_tree.rb_node; node; ) अणु
		काष्ठा userspace_mem_region *region =
			container_of(node, काष्ठा userspace_mem_region, hva_node);

		अगर (hva >= region->host_mem) अणु
			अगर (hva <= (region->host_mem
				+ region->region.memory_size - 1))
				वापस (vm_paddr_t)((uपूर्णांकptr_t)
					region->region.guest_phys_addr
					+ (hva - (uपूर्णांकptr_t)region->host_mem));

			node = node->rb_right;
		पूर्ण अन्यथा
			node = node->rb_left;
	पूर्ण

	TEST_FAIL("No mapping to a guest physical address, hva: %p", hva);
	वापस -1;
पूर्ण

/*
 * Address VM physical to Host Virtual *alias*.
 *
 * Input Args:
 *   vm - Virtual Machine
 *   gpa - VM physical address
 *
 * Output Args: None
 *
 * Return:
 *   Equivalent address within the host भव *alias* area, or शून्य
 *   (without failing the test) अगर the guest memory is not shared (so
 *   no alias exists).
 *
 * When vm_create() and related functions are called with a shared memory
 * src_type, we also create a writable, shared alias mapping of the
 * underlying guest memory. This allows the host to manipulate guest memory
 * without mapping that memory in the guest's address space. And, क्रम
 * userfaultfd-based demand paging, we can करो so without triggering userfaults.
 */
व्योम *addr_gpa2alias(काष्ठा kvm_vm *vm, vm_paddr_t gpa)
अणु
	काष्ठा userspace_mem_region *region;
	uपूर्णांकptr_t offset;

	region = userspace_mem_region_find(vm, gpa, gpa);
	अगर (!region)
		वापस शून्य;

	अगर (!region->host_alias)
		वापस शून्य;

	offset = gpa - region->region.guest_phys_addr;
	वापस (व्योम *) ((uपूर्णांकptr_t) region->host_alias + offset);
पूर्ण

/*
 * VM Create IRQ Chip
 *
 * Input Args:
 *   vm - Virtual Machine
 *
 * Output Args: None
 *
 * Return: None
 *
 * Creates an पूर्णांकerrupt controller chip क्रम the VM specअगरied by vm.
 */
व्योम vm_create_irqchip(काष्ठा kvm_vm *vm)
अणु
	पूर्णांक ret;

	ret = ioctl(vm->fd, KVM_CREATE_IRQCHIP, 0);
	TEST_ASSERT(ret == 0, "KVM_CREATE_IRQCHIP IOCTL failed, "
		"rc: %i errno: %i", ret, त्रुटि_सं);

	vm->has_irqchip = true;
पूर्ण

/*
 * VM VCPU State
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *
 * Output Args: None
 *
 * Return:
 *   Poपूर्णांकer to काष्ठाure that describes the state of the VCPU.
 *
 * Locates and वापसs a poपूर्णांकer to a काष्ठाure that describes the
 * state of the VCPU with the given vcpuid.
 */
काष्ठा kvm_run *vcpu_state(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	वापस vcpu->state;
पूर्ण

/*
 * VM VCPU Run
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *
 * Output Args: None
 *
 * Return: None
 *
 * Switch to executing the code क्रम the VCPU given by vcpuid, within the VM
 * given by vm.
 */
व्योम vcpu_run(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	पूर्णांक ret = _vcpu_run(vm, vcpuid);
	TEST_ASSERT(ret == 0, "KVM_RUN IOCTL failed, "
		"rc: %i errno: %i", ret, त्रुटि_सं);
पूर्ण

पूर्णांक _vcpu_run(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	पूर्णांक rc;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);
	करो अणु
		rc = ioctl(vcpu->fd, KVM_RUN, शून्य);
	पूर्ण जबतक (rc == -1 && त्रुटि_सं == EINTR);

	निश्चित_on_unhandled_exception(vm, vcpuid);

	वापस rc;
पूर्ण

पूर्णांक vcpu_get_fd(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	वापस vcpu->fd;
पूर्ण

व्योम vcpu_run_complete_io(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	पूर्णांक ret;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	vcpu->state->immediate_निकास = 1;
	ret = ioctl(vcpu->fd, KVM_RUN, शून्य);
	vcpu->state->immediate_निकास = 0;

	TEST_ASSERT(ret == -1 && त्रुटि_सं == EINTR,
		    "KVM_RUN IOCTL didn't exit immediately, rc: %i, errno: %i",
		    ret, त्रुटि_सं);
पूर्ण

व्योम vcpu_set_guest_debug(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
			  काष्ठा kvm_guest_debug *debug)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	पूर्णांक ret = ioctl(vcpu->fd, KVM_SET_GUEST_DEBUG, debug);

	TEST_ASSERT(ret == 0, "KVM_SET_GUEST_DEBUG failed: %d", ret);
पूर्ण

/*
 * VM VCPU Set MP State
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *   mp_state - mp_state to be set
 *
 * Output Args: None
 *
 * Return: None
 *
 * Sets the MP state of the VCPU given by vcpuid, to the state given
 * by mp_state.
 */
व्योम vcpu_set_mp_state(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		       काष्ठा kvm_mp_state *mp_state)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	पूर्णांक ret;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	ret = ioctl(vcpu->fd, KVM_SET_MP_STATE, mp_state);
	TEST_ASSERT(ret == 0, "KVM_SET_MP_STATE IOCTL failed, "
		"rc: %i errno: %i", ret, त्रुटि_सं);
पूर्ण

/*
 * VM VCPU Get Reg List
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *
 * Output Args:
 *   None
 *
 * Return:
 *   A poपूर्णांकer to an allocated काष्ठा kvm_reg_list
 *
 * Get the list of guest रेजिस्टरs which are supported क्रम
 * KVM_GET_ONE_REG/KVM_SET_ONE_REG calls
 */
काष्ठा kvm_reg_list *vcpu_get_reg_list(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा kvm_reg_list reg_list_n = अणु .n = 0 पूर्ण, *reg_list;
	पूर्णांक ret;

	ret = _vcpu_ioctl(vm, vcpuid, KVM_GET_REG_LIST, &reg_list_n);
	TEST_ASSERT(ret == -1 && त्रुटि_सं == E2BIG, "KVM_GET_REG_LIST n=0");
	reg_list = सुस्मृति(1, माप(*reg_list) + reg_list_n.n * माप(__u64));
	reg_list->n = reg_list_n.n;
	vcpu_ioctl(vm, vcpuid, KVM_GET_REG_LIST, reg_list);
	वापस reg_list;
पूर्ण

/*
 * VM VCPU Regs Get
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *
 * Output Args:
 *   regs - current state of VCPU regs
 *
 * Return: None
 *
 * Obtains the current रेजिस्टर state क्रम the VCPU specअगरied by vcpuid
 * and stores it at the location given by regs.
 */
व्योम vcpu_regs_get(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, काष्ठा kvm_regs *regs)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	पूर्णांक ret;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	ret = ioctl(vcpu->fd, KVM_GET_REGS, regs);
	TEST_ASSERT(ret == 0, "KVM_GET_REGS failed, rc: %i errno: %i",
		ret, त्रुटि_सं);
पूर्ण

/*
 * VM VCPU Regs Set
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *   regs - Values to set VCPU regs to
 *
 * Output Args: None
 *
 * Return: None
 *
 * Sets the regs of the VCPU specअगरied by vcpuid to the values
 * given by regs.
 */
व्योम vcpu_regs_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, काष्ठा kvm_regs *regs)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	पूर्णांक ret;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	ret = ioctl(vcpu->fd, KVM_SET_REGS, regs);
	TEST_ASSERT(ret == 0, "KVM_SET_REGS failed, rc: %i errno: %i",
		ret, त्रुटि_सं);
पूर्ण

#अगर_घोषित __KVM_HAVE_VCPU_EVENTS
व्योम vcpu_events_get(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		     काष्ठा kvm_vcpu_events *events)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	पूर्णांक ret;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	ret = ioctl(vcpu->fd, KVM_GET_VCPU_EVENTS, events);
	TEST_ASSERT(ret == 0, "KVM_GET_VCPU_EVENTS, failed, rc: %i errno: %i",
		ret, त्रुटि_सं);
पूर्ण

व्योम vcpu_events_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		     काष्ठा kvm_vcpu_events *events)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	पूर्णांक ret;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	ret = ioctl(vcpu->fd, KVM_SET_VCPU_EVENTS, events);
	TEST_ASSERT(ret == 0, "KVM_SET_VCPU_EVENTS, failed, rc: %i errno: %i",
		ret, त्रुटि_सं);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __x86_64__
व्योम vcpu_nested_state_get(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
			   काष्ठा kvm_nested_state *state)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	पूर्णांक ret;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	ret = ioctl(vcpu->fd, KVM_GET_NESTED_STATE, state);
	TEST_ASSERT(ret == 0,
		"KVM_SET_NESTED_STATE failed, ret: %i errno: %i",
		ret, त्रुटि_सं);
पूर्ण

पूर्णांक vcpu_nested_state_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
			  काष्ठा kvm_nested_state *state, bool ignore_error)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	पूर्णांक ret;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	ret = ioctl(vcpu->fd, KVM_SET_NESTED_STATE, state);
	अगर (!ignore_error) अणु
		TEST_ASSERT(ret == 0,
			"KVM_SET_NESTED_STATE failed, ret: %i errno: %i",
			ret, त्रुटि_सं);
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

/*
 * VM VCPU System Regs Get
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *
 * Output Args:
 *   sregs - current state of VCPU प्रणाली regs
 *
 * Return: None
 *
 * Obtains the current प्रणाली रेजिस्टर state क्रम the VCPU specअगरied by
 * vcpuid and stores it at the location given by sregs.
 */
व्योम vcpu_sregs_get(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, काष्ठा kvm_sregs *sregs)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	पूर्णांक ret;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	ret = ioctl(vcpu->fd, KVM_GET_SREGS, sregs);
	TEST_ASSERT(ret == 0, "KVM_GET_SREGS failed, rc: %i errno: %i",
		ret, त्रुटि_सं);
पूर्ण

/*
 * VM VCPU System Regs Set
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *   sregs - Values to set VCPU प्रणाली regs to
 *
 * Output Args: None
 *
 * Return: None
 *
 * Sets the प्रणाली regs of the VCPU specअगरied by vcpuid to the values
 * given by sregs.
 */
व्योम vcpu_sregs_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, काष्ठा kvm_sregs *sregs)
अणु
	पूर्णांक ret = _vcpu_sregs_set(vm, vcpuid, sregs);
	TEST_ASSERT(ret == 0, "KVM_RUN IOCTL failed, "
		"rc: %i errno: %i", ret, त्रुटि_सं);
पूर्ण

पूर्णांक _vcpu_sregs_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, काष्ठा kvm_sregs *sregs)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	वापस ioctl(vcpu->fd, KVM_SET_SREGS, sregs);
पूर्ण

व्योम vcpu_fpu_get(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, काष्ठा kvm_fpu *fpu)
अणु
	पूर्णांक ret;

	ret = _vcpu_ioctl(vm, vcpuid, KVM_GET_FPU, fpu);
	TEST_ASSERT(ret == 0, "KVM_GET_FPU failed, rc: %i errno: %i (%s)",
		    ret, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
पूर्ण

व्योम vcpu_fpu_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, काष्ठा kvm_fpu *fpu)
अणु
	पूर्णांक ret;

	ret = _vcpu_ioctl(vm, vcpuid, KVM_SET_FPU, fpu);
	TEST_ASSERT(ret == 0, "KVM_SET_FPU failed, rc: %i errno: %i (%s)",
		    ret, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
पूर्ण

व्योम vcpu_get_reg(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, काष्ठा kvm_one_reg *reg)
अणु
	पूर्णांक ret;

	ret = _vcpu_ioctl(vm, vcpuid, KVM_GET_ONE_REG, reg);
	TEST_ASSERT(ret == 0, "KVM_GET_ONE_REG failed, rc: %i errno: %i (%s)",
		    ret, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
पूर्ण

व्योम vcpu_set_reg(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, काष्ठा kvm_one_reg *reg)
अणु
	पूर्णांक ret;

	ret = _vcpu_ioctl(vm, vcpuid, KVM_SET_ONE_REG, reg);
	TEST_ASSERT(ret == 0, "KVM_SET_ONE_REG failed, rc: %i errno: %i (%s)",
		    ret, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
पूर्ण

/*
 * VCPU Ioctl
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *   cmd - Ioctl number
 *   arg - Argument to pass to the ioctl
 *
 * Return: None
 *
 * Issues an arbitrary ioctl on a VCPU fd.
 */
व्योम vcpu_ioctl(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		अचिन्हित दीर्घ cmd, व्योम *arg)
अणु
	पूर्णांक ret;

	ret = _vcpu_ioctl(vm, vcpuid, cmd, arg);
	TEST_ASSERT(ret == 0, "vcpu ioctl %lu failed, rc: %i errno: %i (%s)",
		cmd, ret, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
पूर्ण

पूर्णांक _vcpu_ioctl(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		अचिन्हित दीर्घ cmd, व्योम *arg)
अणु
	काष्ठा vcpu *vcpu = vcpu_find(vm, vcpuid);
	पूर्णांक ret;

	TEST_ASSERT(vcpu != शून्य, "vcpu not found, vcpuid: %u", vcpuid);

	ret = ioctl(vcpu->fd, cmd, arg);

	वापस ret;
पूर्ण

व्योम *vcpu_map_dirty_ring(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा vcpu *vcpu;
	uपूर्णांक32_t size = vm->dirty_ring_size;

	TEST_ASSERT(size > 0, "Should enable dirty ring first");

	vcpu = vcpu_find(vm, vcpuid);

	TEST_ASSERT(vcpu, "Cannot find vcpu %u", vcpuid);

	अगर (!vcpu->dirty_gfns) अणु
		व्योम *addr;

		addr = mmap(शून्य, size, PROT_READ,
			    MAP_PRIVATE, vcpu->fd,
			    vm->page_size * KVM_सूचीTY_LOG_PAGE_OFFSET);
		TEST_ASSERT(addr == MAP_FAILED, "Dirty ring mapped private");

		addr = mmap(शून्य, size, PROT_READ | PROT_EXEC,
			    MAP_PRIVATE, vcpu->fd,
			    vm->page_size * KVM_सूचीTY_LOG_PAGE_OFFSET);
		TEST_ASSERT(addr == MAP_FAILED, "Dirty ring mapped exec");

		addr = mmap(शून्य, size, PROT_READ | PROT_WRITE,
			    MAP_SHARED, vcpu->fd,
			    vm->page_size * KVM_सूचीTY_LOG_PAGE_OFFSET);
		TEST_ASSERT(addr != MAP_FAILED, "Dirty ring map failed");

		vcpu->dirty_gfns = addr;
		vcpu->dirty_gfns_count = size / माप(काष्ठा kvm_dirty_gfn);
	पूर्ण

	वापस vcpu->dirty_gfns;
पूर्ण

/*
 * VM Ioctl
 *
 * Input Args:
 *   vm - Virtual Machine
 *   cmd - Ioctl number
 *   arg - Argument to pass to the ioctl
 *
 * Return: None
 *
 * Issues an arbitrary ioctl on a VM fd.
 */
व्योम vm_ioctl(काष्ठा kvm_vm *vm, अचिन्हित दीर्घ cmd, व्योम *arg)
अणु
	पूर्णांक ret;

	ret = _vm_ioctl(vm, cmd, arg);
	TEST_ASSERT(ret == 0, "vm ioctl %lu failed, rc: %i errno: %i (%s)",
		cmd, ret, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
पूर्ण

पूर्णांक _vm_ioctl(काष्ठा kvm_vm *vm, अचिन्हित दीर्घ cmd, व्योम *arg)
अणु
	वापस ioctl(vm->fd, cmd, arg);
पूर्ण

/*
 * KVM प्रणाली ioctl
 *
 * Input Args:
 *   vm - Virtual Machine
 *   cmd - Ioctl number
 *   arg - Argument to pass to the ioctl
 *
 * Return: None
 *
 * Issues an arbitrary ioctl on a KVM fd.
 */
व्योम kvm_ioctl(काष्ठा kvm_vm *vm, अचिन्हित दीर्घ cmd, व्योम *arg)
अणु
	पूर्णांक ret;

	ret = ioctl(vm->kvm_fd, cmd, arg);
	TEST_ASSERT(ret == 0, "KVM ioctl %lu failed, rc: %i errno: %i (%s)",
		cmd, ret, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
पूर्ण

पूर्णांक _kvm_ioctl(काष्ठा kvm_vm *vm, अचिन्हित दीर्घ cmd, व्योम *arg)
अणु
	वापस ioctl(vm->kvm_fd, cmd, arg);
पूर्ण

/*
 * Device Ioctl
 */

पूर्णांक _kvm_device_check_attr(पूर्णांक dev_fd, uपूर्णांक32_t group, uपूर्णांक64_t attr)
अणु
	काष्ठा kvm_device_attr attribute = अणु
		.group = group,
		.attr = attr,
		.flags = 0,
	पूर्ण;

	वापस ioctl(dev_fd, KVM_HAS_DEVICE_ATTR, &attribute);
पूर्ण

पूर्णांक kvm_device_check_attr(पूर्णांक dev_fd, uपूर्णांक32_t group, uपूर्णांक64_t attr)
अणु
	पूर्णांक ret = _kvm_device_check_attr(dev_fd, group, attr);

	TEST_ASSERT(ret >= 0, "KVM_HAS_DEVICE_ATTR failed, rc: %i errno: %i", ret, त्रुटि_सं);
	वापस ret;
पूर्ण

पूर्णांक _kvm_create_device(काष्ठा kvm_vm *vm, uपूर्णांक64_t type, bool test, पूर्णांक *fd)
अणु
	काष्ठा kvm_create_device create_dev;
	पूर्णांक ret;

	create_dev.type = type;
	create_dev.fd = -1;
	create_dev.flags = test ? KVM_CREATE_DEVICE_TEST : 0;
	ret = ioctl(vm_get_fd(vm), KVM_CREATE_DEVICE, &create_dev);
	*fd = create_dev.fd;
	वापस ret;
पूर्ण

पूर्णांक kvm_create_device(काष्ठा kvm_vm *vm, uपूर्णांक64_t type, bool test)
अणु
	पूर्णांक fd, ret;

	ret = _kvm_create_device(vm, type, test, &fd);

	अगर (!test) अणु
		TEST_ASSERT(ret >= 0,
			    "KVM_CREATE_DEVICE IOCTL failed, rc: %i errno: %i", ret, त्रुटि_सं);
		वापस fd;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक _kvm_device_access(पूर्णांक dev_fd, uपूर्णांक32_t group, uपूर्णांक64_t attr,
		      व्योम *val, bool ग_लिखो)
अणु
	काष्ठा kvm_device_attr kvmattr = अणु
		.group = group,
		.attr = attr,
		.flags = 0,
		.addr = (uपूर्णांकptr_t)val,
	पूर्ण;
	पूर्णांक ret;

	ret = ioctl(dev_fd, ग_लिखो ? KVM_SET_DEVICE_ATTR : KVM_GET_DEVICE_ATTR,
		    &kvmattr);
	वापस ret;
पूर्ण

पूर्णांक kvm_device_access(पूर्णांक dev_fd, uपूर्णांक32_t group, uपूर्णांक64_t attr,
		      व्योम *val, bool ग_लिखो)
अणु
	पूर्णांक ret = _kvm_device_access(dev_fd, group, attr, val, ग_लिखो);

	TEST_ASSERT(ret >= 0, "KVM_SET|GET_DEVICE_ATTR IOCTL failed, rc: %i errno: %i", ret, त्रुटि_सं);
	वापस ret;
पूर्ण

/*
 * VM Dump
 *
 * Input Args:
 *   vm - Virtual Machine
 *   indent - Left margin indent amount
 *
 * Output Args:
 *   stream - Output खाता stream
 *
 * Return: None
 *
 * Dumps the current state of the VM given by vm, to the खाता stream
 * given by stream.
 */
व्योम vm_dump(खाता *stream, काष्ठा kvm_vm *vm, uपूर्णांक8_t indent)
अणु
	पूर्णांक ctr;
	काष्ठा userspace_mem_region *region;
	काष्ठा vcpu *vcpu;

	ख_लिखो(stream, "%*smode: 0x%x\n", indent, "", vm->mode);
	ख_लिखो(stream, "%*sfd: %i\n", indent, "", vm->fd);
	ख_लिखो(stream, "%*spage_size: 0x%x\n", indent, "", vm->page_size);
	ख_लिखो(stream, "%*sMem Regions:\n", indent, "");
	hash_क्रम_each(vm->regions.slot_hash, ctr, region, slot_node) अणु
		ख_लिखो(stream, "%*sguest_phys: 0x%lx size: 0x%lx "
			"host_virt: %p\n", indent + 2, "",
			(uपूर्णांक64_t) region->region.guest_phys_addr,
			(uपूर्णांक64_t) region->region.memory_size,
			region->host_mem);
		ख_लिखो(stream, "%*sunused_phy_pages: ", indent + 2, "");
		sparsebit_dump(stream, region->unused_phy_pages, 0);
	पूर्ण
	ख_लिखो(stream, "%*sMapped Virtual Pages:\n", indent, "");
	sparsebit_dump(stream, vm->vpages_mapped, indent + 2);
	ख_लिखो(stream, "%*spgd_created: %u\n", indent, "",
		vm->pgd_created);
	अगर (vm->pgd_created) अणु
		ख_लिखो(stream, "%*sVirtual Translation Tables:\n",
			indent + 2, "");
		virt_dump(stream, vm, indent + 4);
	पूर्ण
	ख_लिखो(stream, "%*sVCPUs:\n", indent, "");
	list_क्रम_each_entry(vcpu, &vm->vcpus, list)
		vcpu_dump(stream, vm, vcpu->id, indent + 2);
पूर्ण

/* Known KVM निकास reasons */
अटल काष्ठा निकास_reason अणु
	अचिन्हित पूर्णांक reason;
	स्थिर अक्षर *name;
पूर्ण निकास_reasons_known[] = अणु
	अणुKVM_EXIT_UNKNOWN, "UNKNOWN"पूर्ण,
	अणुKVM_EXIT_EXCEPTION, "EXCEPTION"पूर्ण,
	अणुKVM_EXIT_IO, "IO"पूर्ण,
	अणुKVM_EXIT_HYPERCALL, "HYPERCALL"पूर्ण,
	अणुKVM_EXIT_DEBUG, "DEBUG"पूर्ण,
	अणुKVM_EXIT_HLT, "HLT"पूर्ण,
	अणुKVM_EXIT_MMIO, "MMIO"पूर्ण,
	अणुKVM_EXIT_IRQ_WINDOW_OPEN, "IRQ_WINDOW_OPEN"पूर्ण,
	अणुKVM_EXIT_SHUTDOWN, "SHUTDOWN"पूर्ण,
	अणुKVM_EXIT_FAIL_ENTRY, "FAIL_ENTRY"पूर्ण,
	अणुKVM_EXIT_INTR, "INTR"पूर्ण,
	अणुKVM_EXIT_SET_TPR, "SET_TPR"पूर्ण,
	अणुKVM_EXIT_TPR_ACCESS, "TPR_ACCESS"पूर्ण,
	अणुKVM_EXIT_S390_SIEIC, "S390_SIEIC"पूर्ण,
	अणुKVM_EXIT_S390_RESET, "S390_RESET"पूर्ण,
	अणुKVM_EXIT_DCR, "DCR"पूर्ण,
	अणुKVM_EXIT_NMI, "NMI"पूर्ण,
	अणुKVM_EXIT_INTERNAL_ERROR, "INTERNAL_ERROR"पूर्ण,
	अणुKVM_EXIT_OSI, "OSI"पूर्ण,
	अणुKVM_EXIT_PAPR_HCALL, "PAPR_HCALL"पूर्ण,
	अणुKVM_EXIT_सूचीTY_RING_FULL, "DIRTY_RING_FULL"पूर्ण,
	अणुKVM_EXIT_X86_RDMSR, "RDMSR"पूर्ण,
	अणुKVM_EXIT_X86_WRMSR, "WRMSR"पूर्ण,
	अणुKVM_EXIT_XEN, "XEN"पूर्ण,
#अगर_घोषित KVM_EXIT_MEMORY_NOT_PRESENT
	अणुKVM_EXIT_MEMORY_NOT_PRESENT, "MEMORY_NOT_PRESENT"पूर्ण,
#पूर्ण_अगर
पूर्ण;

/*
 * Exit Reason String
 *
 * Input Args:
 *   निकास_reason - Exit reason
 *
 * Output Args: None
 *
 * Return:
 *   Constant string poपूर्णांकer describing the निकास reason.
 *
 * Locates and वापसs a स्थिरant string that describes the KVM निकास
 * reason given by निकास_reason.  If no such string is found, a स्थिरant
 * string of "Unknown" is वापसed.
 */
स्थिर अक्षर *निकास_reason_str(अचिन्हित पूर्णांक निकास_reason)
अणु
	अचिन्हित पूर्णांक n1;

	क्रम (n1 = 0; n1 < ARRAY_SIZE(निकास_reasons_known); n1++) अणु
		अगर (निकास_reason == निकास_reasons_known[n1].reason)
			वापस निकास_reasons_known[n1].name;
	पूर्ण

	वापस "Unknown";
पूर्ण

/*
 * Physical Contiguous Page Allocator
 *
 * Input Args:
 *   vm - Virtual Machine
 *   num - number of pages
 *   paddr_min - Physical address minimum
 *   memslot - Memory region to allocate page from
 *
 * Output Args: None
 *
 * Return:
 *   Starting physical address
 *
 * Within the VM specअगरied by vm, locates a range of available physical
 * pages at or above paddr_min. If found, the pages are marked as in use
 * and their base address is वापसed. A TEST_ASSERT failure occurs अगर
 * not enough pages are available at or above paddr_min.
 */
vm_paddr_t vm_phy_pages_alloc(काष्ठा kvm_vm *vm, माप_प्रकार num,
			      vm_paddr_t paddr_min, uपूर्णांक32_t memslot)
अणु
	काष्ठा userspace_mem_region *region;
	sparsebit_idx_t pg, base;

	TEST_ASSERT(num > 0, "Must allocate at least one page");

	TEST_ASSERT((paddr_min % vm->page_size) == 0, "Min physical address "
		"not divisible by page size.\n"
		"  paddr_min: 0x%lx page_size: 0x%x",
		paddr_min, vm->page_size);

	region = memslot2region(vm, memslot);
	base = pg = paddr_min >> vm->page_shअगरt;

	करो अणु
		क्रम (; pg < base + num; ++pg) अणु
			अगर (!sparsebit_is_set(region->unused_phy_pages, pg)) अणु
				base = pg = sparsebit_next_set(region->unused_phy_pages, pg);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (pg && pg != base + num);

	अगर (pg == 0) अणु
		ख_लिखो(मानक_त्रुटि, "No guest physical page available, "
			"paddr_min: 0x%lx page_size: 0x%x memslot: %u\n",
			paddr_min, vm->page_size, memslot);
		ख_माला_दो("---- vm dump ----\n", मानक_त्रुटि);
		vm_dump(मानक_त्रुटि, vm, 2);
		पात();
	पूर्ण

	क्रम (pg = base; pg < base + num; ++pg)
		sparsebit_clear(region->unused_phy_pages, pg);

	वापस base * vm->page_size;
पूर्ण

vm_paddr_t vm_phy_page_alloc(काष्ठा kvm_vm *vm, vm_paddr_t paddr_min,
			     uपूर्णांक32_t memslot)
अणु
	वापस vm_phy_pages_alloc(vm, 1, paddr_min, memslot);
पूर्ण

/*
 * Address Guest Virtual to Host Virtual
 *
 * Input Args:
 *   vm - Virtual Machine
 *   gva - VM भव address
 *
 * Output Args: None
 *
 * Return:
 *   Equivalent host भव address
 */
व्योम *addr_gva2hva(काष्ठा kvm_vm *vm, vm_vaddr_t gva)
अणु
	वापस addr_gpa2hva(vm, addr_gva2gpa(vm, gva));
पूर्ण

/*
 * Is Unrestricted Guest
 *
 * Input Args:
 *   vm - Virtual Machine
 *
 * Output Args: None
 *
 * Return: True अगर the unrestricted guest is set to 'Y', otherwise वापस false.
 *
 * Check अगर the unrestricted guest flag is enabled.
 */
bool vm_is_unrestricted_guest(काष्ठा kvm_vm *vm)
अणु
	अक्षर val = 'N';
	माप_प्रकार count;
	खाता *f;

	अगर (vm == शून्य) अणु
		/* Ensure that the KVM venकरोr-specअगरic module is loaded. */
		बंद(खोलो_kvm_dev_path_or_निकास());
	पूर्ण

	f = ख_खोलो("/sys/module/kvm_intel/parameters/unrestricted_guest", "r");
	अगर (f) अणु
		count = ख_पढ़ो(&val, माप(अक्षर), 1, f);
		TEST_ASSERT(count == 1, "Unable to read from param file.");
		ख_बंद(f);
	पूर्ण

	वापस val == 'Y';
पूर्ण

अचिन्हित पूर्णांक vm_get_page_size(काष्ठा kvm_vm *vm)
अणु
	वापस vm->page_size;
पूर्ण

अचिन्हित पूर्णांक vm_get_page_shअगरt(काष्ठा kvm_vm *vm)
अणु
	वापस vm->page_shअगरt;
पूर्ण

uपूर्णांक64_t vm_get_max_gfn(काष्ठा kvm_vm *vm)
अणु
	वापस vm->max_gfn;
पूर्ण

पूर्णांक vm_get_fd(काष्ठा kvm_vm *vm)
अणु
	वापस vm->fd;
पूर्ण

अटल अचिन्हित पूर्णांक vm_calc_num_pages(अचिन्हित पूर्णांक num_pages,
				      अचिन्हित पूर्णांक page_shअगरt,
				      अचिन्हित पूर्णांक new_page_shअगरt,
				      bool उच्चमान)
अणु
	अचिन्हित पूर्णांक n = 1 << (new_page_shअगरt - page_shअगरt);

	अगर (page_shअगरt >= new_page_shअगरt)
		वापस num_pages * (1 << (page_shअगरt - new_page_shअगरt));

	वापस num_pages / n + !!(उच्चमान && num_pages % n);
पूर्ण

अटल अंतरभूत पूर्णांक getpageshअगरt(व्योम)
अणु
	वापस __builtin_ffs(getpagesize()) - 1;
पूर्ण

अचिन्हित पूर्णांक
vm_num_host_pages(क्रमागत vm_guest_mode mode, अचिन्हित पूर्णांक num_guest_pages)
अणु
	वापस vm_calc_num_pages(num_guest_pages,
				 vm_guest_mode_params[mode].page_shअगरt,
				 getpageshअगरt(), true);
पूर्ण

अचिन्हित पूर्णांक
vm_num_guest_pages(क्रमागत vm_guest_mode mode, अचिन्हित पूर्णांक num_host_pages)
अणु
	वापस vm_calc_num_pages(num_host_pages, getpageshअगरt(),
				 vm_guest_mode_params[mode].page_shअगरt, false);
पूर्ण

अचिन्हित पूर्णांक vm_calc_num_guest_pages(क्रमागत vm_guest_mode mode, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक n;
	n = DIV_ROUND_UP(size, vm_guest_mode_params[mode].page_size);
	वापस vm_adjust_num_guest_pages(mode, n);
पूर्ण
