<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tools/testing/selftests/kvm/include/kvm_util.h
 *
 * Copyright (C) 2018, Google LLC.
 */
#अगर_अघोषित SELFTEST_KVM_UTIL_H
#घोषणा SELFTEST_KVM_UTIL_H

#समावेश "test_util.h"

#समावेश "asm/kvm.h"
#समावेश "linux/list.h"
#समावेश "linux/kvm.h"
#समावेश <sys/ioctl.h>

#समावेश "sparsebit.h"

#घोषणा KVM_DEV_PATH "/dev/kvm"
#घोषणा KVM_MAX_VCPUS 512

/*
 * Callers of kvm_util only have an incomplete/opaque description of the
 * काष्ठाure kvm_util is using to मुख्यtain the state of a VM.
 */
काष्ठा kvm_vm;

प्रकार uपूर्णांक64_t vm_paddr_t; /* Virtual Machine (Guest) physical address */
प्रकार uपूर्णांक64_t vm_vaddr_t; /* Virtual Machine (Guest) भव address */

/* Minimum allocated guest भव and physical addresses */
#घोषणा KVM_UTIL_MIN_VADDR		0x2000

#घोषणा DEFAULT_GUEST_PHY_PAGES		512
#घोषणा DEFAULT_GUEST_STACK_VADDR_MIN	0xab6000
#घोषणा DEFAULT_STACK_PGS		5

क्रमागत vm_guest_mode अणु
	VM_MODE_P52V48_4K,
	VM_MODE_P52V48_64K,
	VM_MODE_P48V48_4K,
	VM_MODE_P48V48_64K,
	VM_MODE_P40V48_4K,
	VM_MODE_P40V48_64K,
	VM_MODE_PXXV48_4K,	/* For 48bits VA but ANY bits PA */
	VM_MODE_P47V64_4K,
	NUM_VM_MODES,
पूर्ण;

#अगर defined(__aarch64__)

#घोषणा VM_MODE_DEFAULT			VM_MODE_P40V48_4K
#घोषणा MIN_PAGE_SHIFT			12U
#घोषणा ptes_per_page(page_size)	((page_size) / 8)

#या_अगर defined(__x86_64__)

#घोषणा VM_MODE_DEFAULT			VM_MODE_PXXV48_4K
#घोषणा MIN_PAGE_SHIFT			12U
#घोषणा ptes_per_page(page_size)	((page_size) / 8)

#या_अगर defined(__s390x__)

#घोषणा VM_MODE_DEFAULT			VM_MODE_P47V64_4K
#घोषणा MIN_PAGE_SHIFT			12U
#घोषणा ptes_per_page(page_size)	((page_size) / 16)

#पूर्ण_अगर

#घोषणा MIN_PAGE_SIZE		(1U << MIN_PAGE_SHIFT)
#घोषणा PTES_PER_MIN_PAGE	ptes_per_page(MIN_PAGE_SIZE)

काष्ठा vm_guest_mode_params अणु
	अचिन्हित पूर्णांक pa_bits;
	अचिन्हित पूर्णांक va_bits;
	अचिन्हित पूर्णांक page_size;
	अचिन्हित पूर्णांक page_shअगरt;
पूर्ण;
बाह्य स्थिर काष्ठा vm_guest_mode_params vm_guest_mode_params[];

पूर्णांक खोलो_kvm_dev_path_or_निकास(व्योम);
पूर्णांक kvm_check_cap(दीर्घ cap);
पूर्णांक vm_enable_cap(काष्ठा kvm_vm *vm, काष्ठा kvm_enable_cap *cap);
पूर्णांक vcpu_enable_cap(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpu_id,
		    काष्ठा kvm_enable_cap *cap);
व्योम vm_enable_dirty_ring(काष्ठा kvm_vm *vm, uपूर्णांक32_t ring_size);
स्थिर अक्षर *vm_guest_mode_string(uपूर्णांक32_t i);

काष्ठा kvm_vm *vm_create(क्रमागत vm_guest_mode mode, uपूर्णांक64_t phy_pages, पूर्णांक perm);
व्योम kvm_vm_मुक्त(काष्ठा kvm_vm *vmp);
व्योम kvm_vm_restart(काष्ठा kvm_vm *vmp, पूर्णांक perm);
व्योम kvm_vm_release(काष्ठा kvm_vm *vmp);
व्योम kvm_vm_get_dirty_log(काष्ठा kvm_vm *vm, पूर्णांक slot, व्योम *log);
व्योम kvm_vm_clear_dirty_log(काष्ठा kvm_vm *vm, पूर्णांक slot, व्योम *log,
			    uपूर्णांक64_t first_page, uपूर्णांक32_t num_pages);
uपूर्णांक32_t kvm_vm_reset_dirty_ring(काष्ठा kvm_vm *vm);

पूर्णांक kvm_स_भेद_hva_gva(व्योम *hva, काष्ठा kvm_vm *vm, स्थिर vm_vaddr_t gva,
		       माप_प्रकार len);

व्योम kvm_vm_elf_load(काष्ठा kvm_vm *vm, स्थिर अक्षर *filename,
		     uपूर्णांक32_t data_memslot, uपूर्णांक32_t pgd_memslot);

व्योम vm_dump(खाता *stream, काष्ठा kvm_vm *vm, uपूर्णांक8_t indent);

/*
 * VM VCPU Dump
 *
 * Input Args:
 *   stream - Output खाता stream
 *   vm     - Virtual Machine
 *   vcpuid - VCPU ID
 *   indent - Left margin indent amount
 *
 * Output Args: None
 *
 * Return: None
 *
 * Dumps the current state of the VCPU specअगरied by @vcpuid, within the VM
 * given by @vm, to the खाता stream given by @stream.
 */
व्योम vcpu_dump(खाता *stream, काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
	       uपूर्णांक8_t indent);

व्योम vm_create_irqchip(काष्ठा kvm_vm *vm);

व्योम vm_userspace_mem_region_add(काष्ठा kvm_vm *vm,
	क्रमागत vm_mem_backing_src_type src_type,
	uपूर्णांक64_t guest_paddr, uपूर्णांक32_t slot, uपूर्णांक64_t npages,
	uपूर्णांक32_t flags);

व्योम vcpu_ioctl(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, अचिन्हित दीर्घ ioctl,
		व्योम *arg);
पूर्णांक _vcpu_ioctl(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, अचिन्हित दीर्घ ioctl,
		व्योम *arg);
व्योम vm_ioctl(काष्ठा kvm_vm *vm, अचिन्हित दीर्घ ioctl, व्योम *arg);
पूर्णांक _vm_ioctl(काष्ठा kvm_vm *vm, अचिन्हित दीर्घ cmd, व्योम *arg);
व्योम kvm_ioctl(काष्ठा kvm_vm *vm, अचिन्हित दीर्घ ioctl, व्योम *arg);
पूर्णांक _kvm_ioctl(काष्ठा kvm_vm *vm, अचिन्हित दीर्घ ioctl, व्योम *arg);
व्योम vm_mem_region_set_flags(काष्ठा kvm_vm *vm, uपूर्णांक32_t slot, uपूर्णांक32_t flags);
व्योम vm_mem_region_move(काष्ठा kvm_vm *vm, uपूर्णांक32_t slot, uपूर्णांक64_t new_gpa);
व्योम vm_mem_region_delete(काष्ठा kvm_vm *vm, uपूर्णांक32_t slot);
व्योम vm_vcpu_add(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);
vm_vaddr_t vm_vaddr_alloc(काष्ठा kvm_vm *vm, माप_प्रकार sz, vm_vaddr_t vaddr_min,
			  uपूर्णांक32_t data_memslot, uपूर्णांक32_t pgd_memslot);
व्योम virt_map(काष्ठा kvm_vm *vm, uपूर्णांक64_t vaddr, uपूर्णांक64_t paddr,
	      अचिन्हित पूर्णांक npages, uपूर्णांक32_t pgd_memslot);
व्योम *addr_gpa2hva(काष्ठा kvm_vm *vm, vm_paddr_t gpa);
व्योम *addr_gva2hva(काष्ठा kvm_vm *vm, vm_vaddr_t gva);
vm_paddr_t addr_hva2gpa(काष्ठा kvm_vm *vm, व्योम *hva);
व्योम *addr_gpa2alias(काष्ठा kvm_vm *vm, vm_paddr_t gpa);

/*
 * Address Guest Virtual to Guest Physical
 *
 * Input Args:
 *   vm - Virtual Machine
 *   gva - VM भव address
 *
 * Output Args: None
 *
 * Return:
 *   Equivalent VM physical address
 *
 * Returns the VM physical address of the translated VM भव
 * address given by @gva.
 */
vm_paddr_t addr_gva2gpa(काष्ठा kvm_vm *vm, vm_vaddr_t gva);

काष्ठा kvm_run *vcpu_state(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);
व्योम vcpu_run(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);
पूर्णांक _vcpu_run(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);
पूर्णांक vcpu_get_fd(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);
व्योम vcpu_run_complete_io(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);
व्योम vcpu_set_guest_debug(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
			  काष्ठा kvm_guest_debug *debug);
व्योम vcpu_set_mp_state(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		       काष्ठा kvm_mp_state *mp_state);
काष्ठा kvm_reg_list *vcpu_get_reg_list(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);
व्योम vcpu_regs_get(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, काष्ठा kvm_regs *regs);
व्योम vcpu_regs_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, काष्ठा kvm_regs *regs);

/*
 * VM VCPU Args Set
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - VCPU ID
 *   num - number of arguments
 *   ... - arguments, each of type uपूर्णांक64_t
 *
 * Output Args: None
 *
 * Return: None
 *
 * Sets the first @num function input रेजिस्टरs of the VCPU with @vcpuid,
 * per the C calling convention of the architecture, to the values given
 * as variable args. Each of the variable args is expected to be of type
 * uपूर्णांक64_t. The maximum @num can be is specअगरic to the architecture.
 */
व्योम vcpu_args_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, अचिन्हित पूर्णांक num, ...);

व्योम vcpu_sregs_get(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		    काष्ठा kvm_sregs *sregs);
व्योम vcpu_sregs_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		    काष्ठा kvm_sregs *sregs);
पूर्णांक _vcpu_sregs_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		    काष्ठा kvm_sregs *sregs);
व्योम vcpu_fpu_get(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		  काष्ठा kvm_fpu *fpu);
व्योम vcpu_fpu_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		  काष्ठा kvm_fpu *fpu);
व्योम vcpu_get_reg(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, काष्ठा kvm_one_reg *reg);
व्योम vcpu_set_reg(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, काष्ठा kvm_one_reg *reg);
#अगर_घोषित __KVM_HAVE_VCPU_EVENTS
व्योम vcpu_events_get(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		     काष्ठा kvm_vcpu_events *events);
व्योम vcpu_events_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
		     काष्ठा kvm_vcpu_events *events);
#पूर्ण_अगर
#अगर_घोषित __x86_64__
व्योम vcpu_nested_state_get(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
			   काष्ठा kvm_nested_state *state);
पूर्णांक vcpu_nested_state_set(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
			  काष्ठा kvm_nested_state *state, bool ignore_error);
#पूर्ण_अगर
व्योम *vcpu_map_dirty_ring(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);

पूर्णांक _kvm_device_check_attr(पूर्णांक dev_fd, uपूर्णांक32_t group, uपूर्णांक64_t attr);
पूर्णांक kvm_device_check_attr(पूर्णांक dev_fd, uपूर्णांक32_t group, uपूर्णांक64_t attr);
पूर्णांक _kvm_create_device(काष्ठा kvm_vm *vm, uपूर्णांक64_t type, bool test, पूर्णांक *fd);
पूर्णांक kvm_create_device(काष्ठा kvm_vm *vm, uपूर्णांक64_t type, bool test);
पूर्णांक _kvm_device_access(पूर्णांक dev_fd, uपूर्णांक32_t group, uपूर्णांक64_t attr,
		       व्योम *val, bool ग_लिखो);
पूर्णांक kvm_device_access(पूर्णांक dev_fd, uपूर्णांक32_t group, uपूर्णांक64_t attr,
		      व्योम *val, bool ग_लिखो);

स्थिर अक्षर *निकास_reason_str(अचिन्हित पूर्णांक निकास_reason);

व्योम virt_pgd_alloc(काष्ठा kvm_vm *vm, uपूर्णांक32_t pgd_memslot);

/*
 * VM Virtual Page Map
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vaddr - VM Virtual Address
 *   paddr - VM Physical Address
 *   memslot - Memory region slot क्रम new भव translation tables
 *
 * Output Args: None
 *
 * Return: None
 *
 * Within @vm, creates a भव translation क्रम the page starting
 * at @vaddr to the page starting at @paddr.
 */
व्योम virt_pg_map(काष्ठा kvm_vm *vm, uपूर्णांक64_t vaddr, uपूर्णांक64_t paddr,
		 uपूर्णांक32_t memslot);

vm_paddr_t vm_phy_page_alloc(काष्ठा kvm_vm *vm, vm_paddr_t paddr_min,
			     uपूर्णांक32_t memslot);
vm_paddr_t vm_phy_pages_alloc(काष्ठा kvm_vm *vm, माप_प्रकार num,
			      vm_paddr_t paddr_min, uपूर्णांक32_t memslot);

/*
 * Create a VM with reasonable शेषs
 *
 * Input Args:
 *   vcpuid - The id of the single VCPU to add to the VM.
 *   extra_mem_pages - The number of extra pages to add (this will
 *                     decide how much extra space we will need to
 *                     setup the page tables using memslot 0)
 *   guest_code - The vCPU's entry poपूर्णांक
 *
 * Output Args: None
 *
 * Return:
 *   Poपूर्णांकer to opaque काष्ठाure that describes the created VM.
 */
काष्ठा kvm_vm *vm_create_शेष(uपूर्णांक32_t vcpuid, uपूर्णांक64_t extra_mem_pages,
				 व्योम *guest_code);

/* Same as vm_create_शेष, but can be used क्रम more than one vcpu */
काष्ठा kvm_vm *vm_create_शेष_with_vcpus(uपूर्णांक32_t nr_vcpus, uपूर्णांक64_t extra_mem_pages,
					    uपूर्णांक32_t num_percpu_pages, व्योम *guest_code,
					    uपूर्णांक32_t vcpuids[]);

/* Like vm_create_शेष_with_vcpus, but accepts mode and slot0 memory as a parameter */
काष्ठा kvm_vm *vm_create_with_vcpus(क्रमागत vm_guest_mode mode, uपूर्णांक32_t nr_vcpus,
				    uपूर्णांक64_t slot0_mem_pages, uपूर्णांक64_t extra_mem_pages,
				    uपूर्णांक32_t num_percpu_pages, व्योम *guest_code,
				    uपूर्णांक32_t vcpuids[]);

/*
 * Adds a vCPU with reasonable शेषs (e.g. a stack)
 *
 * Input Args:
 *   vm - Virtual Machine
 *   vcpuid - The id of the VCPU to add to the VM.
 *   guest_code - The vCPU's entry poपूर्णांक
 */
व्योम vm_vcpu_add_शेष(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, व्योम *guest_code);

bool vm_is_unrestricted_guest(काष्ठा kvm_vm *vm);

अचिन्हित पूर्णांक vm_get_page_size(काष्ठा kvm_vm *vm);
अचिन्हित पूर्णांक vm_get_page_shअगरt(काष्ठा kvm_vm *vm);
uपूर्णांक64_t vm_get_max_gfn(काष्ठा kvm_vm *vm);
पूर्णांक vm_get_fd(काष्ठा kvm_vm *vm);

अचिन्हित पूर्णांक vm_calc_num_guest_pages(क्रमागत vm_guest_mode mode, माप_प्रकार size);
अचिन्हित पूर्णांक vm_num_host_pages(क्रमागत vm_guest_mode mode, अचिन्हित पूर्णांक num_guest_pages);
अचिन्हित पूर्णांक vm_num_guest_pages(क्रमागत vm_guest_mode mode, अचिन्हित पूर्णांक num_host_pages);
अटल अंतरभूत अचिन्हित पूर्णांक
vm_adjust_num_guest_pages(क्रमागत vm_guest_mode mode, अचिन्हित पूर्णांक num_guest_pages)
अणु
	अचिन्हित पूर्णांक n;
	n = vm_num_guest_pages(mode, vm_num_host_pages(mode, num_guest_pages));
#अगर_घोषित __s390x__
	/* s390 requires 1M aligned guest sizes */
	n = (n + 255) & ~255;
#पूर्ण_अगर
	वापस n;
पूर्ण

काष्ठा kvm_userspace_memory_region *
kvm_userspace_memory_region_find(काष्ठा kvm_vm *vm, uपूर्णांक64_t start,
				 uपूर्णांक64_t end);

काष्ठा kvm_dirty_log *
allocate_kvm_dirty_log(काष्ठा kvm_userspace_memory_region *region);

पूर्णांक vm_create_device(काष्ठा kvm_vm *vm, काष्ठा kvm_create_device *cd);

#घोषणा sync_global_to_guest(vm, g) (अणु				\
	typeof(g) *_p = addr_gva2hva(vm, (vm_vaddr_t)&(g));	\
	स_नकल(_p, &(g), माप(g));				\
पूर्ण)

#घोषणा sync_global_from_guest(vm, g) (अणु			\
	typeof(g) *_p = addr_gva2hva(vm, (vm_vaddr_t)&(g));	\
	स_नकल(&(g), _p, माप(g));				\
पूर्ण)

व्योम निश्चित_on_unhandled_exception(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);

/* Common ucalls */
क्रमागत अणु
	UCALL_NONE,
	UCALL_SYNC,
	UCALL_ABORT,
	UCALL_DONE,
पूर्ण;

#घोषणा UCALL_MAX_ARGS 6

काष्ठा ucall अणु
	uपूर्णांक64_t cmd;
	uपूर्णांक64_t args[UCALL_MAX_ARGS];
पूर्ण;

व्योम ucall_init(काष्ठा kvm_vm *vm, व्योम *arg);
व्योम ucall_uninit(काष्ठा kvm_vm *vm);
व्योम ucall(uपूर्णांक64_t cmd, पूर्णांक nargs, ...);
uपूर्णांक64_t get_ucall(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpu_id, काष्ठा ucall *uc);

#घोषणा GUEST_SYNC_ARGS(stage, arg1, arg2, arg3, arg4)	\
				ucall(UCALL_SYNC, 6, "hello", stage, arg1, arg2, arg3, arg4)
#घोषणा GUEST_SYNC(stage)	ucall(UCALL_SYNC, 2, "hello", stage)
#घोषणा GUEST_DONE()		ucall(UCALL_DONE, 0)
#घोषणा __GUEST_ASSERT(_condition, _nargs, _args...) करो अणु	\
	अगर (!(_condition))					\
		ucall(UCALL_ABORT, 2 + _nargs,			\
			"Failed guest assert: "			\
			#_condition, __LINE__, _args);		\
पूर्ण जबतक (0)

#घोषणा GUEST_ASSERT(_condition) \
	__GUEST_ASSERT((_condition), 0, 0)

#घोषणा GUEST_ASSERT_1(_condition, arg1) \
	__GUEST_ASSERT((_condition), 1, (arg1))

#घोषणा GUEST_ASSERT_2(_condition, arg1, arg2) \
	__GUEST_ASSERT((_condition), 2, (arg1), (arg2))

#घोषणा GUEST_ASSERT_3(_condition, arg1, arg2, arg3) \
	__GUEST_ASSERT((_condition), 3, (arg1), (arg2), (arg3))

#घोषणा GUEST_ASSERT_4(_condition, arg1, arg2, arg3, arg4) \
	__GUEST_ASSERT((_condition), 4, (arg1), (arg2), (arg3), (arg4))

#पूर्ण_अगर /* SELFTEST_KVM_UTIL_H */
