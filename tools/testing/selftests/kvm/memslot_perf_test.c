<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * A memslot-related perक्रमmance benchmark.
 *
 * Copyright (C) 2021 Oracle and/or its affiliates.
 *
 * Basic guest setup / host vCPU thपढ़ो code lअगरted from set_memory_region_test.
 */
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <semaphore.h>
#समावेश <stdatomic.h>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <समय.स>
#समावेश <unistd.h>

#समावेश <linux/compiler.h>

#समावेश <test_util.h>
#समावेश <kvm_util.h>
#समावेश <processor.h>

#घोषणा VCPU_ID 0

#घोषणा MEM_SIZE		((512U << 20) + 4096)
#घोषणा MEM_SIZE_PAGES		(MEM_SIZE / 4096)
#घोषणा MEM_GPA		0x10000000UL
#घोषणा MEM_AUX_GPA		MEM_GPA
#घोषणा MEM_SYNC_GPA		MEM_AUX_GPA
#घोषणा MEM_TEST_GPA		(MEM_AUX_GPA + 4096)
#घोषणा MEM_TEST_SIZE		(MEM_SIZE - 4096)
अटल_निश्चित(MEM_SIZE % 4096 == 0, "invalid mem size");
अटल_निश्चित(MEM_TEST_SIZE % 4096 == 0, "invalid mem test size");

/*
 * 32 MiB is max size that माला_लो well over 100 iterations on 509 slots.
 * Considering that each slot needs to have at least one page up to
 * 8194 slots in use can then be tested (although with slightly
 * limited resolution).
 */
#घोषणा MEM_SIZE_MAP		((32U << 20) + 4096)
#घोषणा MEM_SIZE_MAP_PAGES	(MEM_SIZE_MAP / 4096)
#घोषणा MEM_TEST_MAP_SIZE	(MEM_SIZE_MAP - 4096)
#घोषणा MEM_TEST_MAP_SIZE_PAGES (MEM_TEST_MAP_SIZE / 4096)
अटल_निश्चित(MEM_SIZE_MAP % 4096 == 0, "invalid map test region size");
अटल_निश्चित(MEM_TEST_MAP_SIZE % 4096 == 0, "invalid map test region size");
अटल_निश्चित(MEM_TEST_MAP_SIZE_PAGES % 2 == 0, "invalid map test region size");
अटल_निश्चित(MEM_TEST_MAP_SIZE_PAGES > 2, "invalid map test region size");

/*
 * 128 MiB is min size that fills 32k slots with at least one page in each
 * जबतक at the same समय माला_लो 100+ iterations in such test
 */
#घोषणा MEM_TEST_UNMAP_SIZE		(128U << 20)
#घोषणा MEM_TEST_UNMAP_SIZE_PAGES	(MEM_TEST_UNMAP_SIZE / 4096)
/* 2 MiB chunk size like a typical huge page */
#घोषणा MEM_TEST_UNMAP_CHUNK_PAGES	(2U << (20 - 12))
अटल_निश्चित(MEM_TEST_UNMAP_SIZE <= MEM_TEST_SIZE,
	      "invalid unmap test region size");
अटल_निश्चित(MEM_TEST_UNMAP_SIZE % 4096 == 0,
	      "invalid unmap test region size");
अटल_निश्चित(MEM_TEST_UNMAP_SIZE_PAGES %
	      (2 * MEM_TEST_UNMAP_CHUNK_PAGES) == 0,
	      "invalid unmap test region size");

/*
 * For the move active test the middle of the test area is placed on
 * a memslot boundary: half lies in the memslot being moved, half in
 * other memslot(s).
 *
 * When running this test with 32k memslots (32764, really) each memslot
 * contains 4 pages.
 * The last one additionally contains the reमुख्यing 21 pages of memory,
 * क्रम the total size of 25 pages.
 * Hence, the maximum size here is 50 pages.
 */
#घोषणा MEM_TEST_MOVE_SIZE_PAGES	(50)
#घोषणा MEM_TEST_MOVE_SIZE		(MEM_TEST_MOVE_SIZE_PAGES * 4096)
#घोषणा MEM_TEST_MOVE_GPA_DEST		(MEM_GPA + MEM_SIZE)
अटल_निश्चित(MEM_TEST_MOVE_SIZE <= MEM_TEST_SIZE,
	      "invalid move test region size");

#घोषणा MEM_TEST_VAL_1 0x1122334455667788
#घोषणा MEM_TEST_VAL_2 0x99AABBCCDDEEFF00

काष्ठा vm_data अणु
	काष्ठा kvm_vm *vm;
	pthपढ़ो_t vcpu_thपढ़ो;
	uपूर्णांक32_t nslots;
	uपूर्णांक64_t npages;
	uपूर्णांक64_t pages_per_slot;
	व्योम **hva_slots;
	bool mmio_ok;
	uपूर्णांक64_t mmio_gpa_min;
	uपूर्णांक64_t mmio_gpa_max;
पूर्ण;

काष्ठा sync_area अणु
	atomic_bool start_flag;
	atomic_bool निकास_flag;
	atomic_bool sync_flag;
	व्योम *move_area_ptr;
पूर्ण;

/*
 * Technically, we need also क्रम the atomic bool to be address-मुक्त, which
 * is recommended, but not strictly required, by C11 क्रम lockless
 * implementations.
 * However, in practice both GCC and Clang fulfill this requirement on
 * all KVM-supported platक्रमms.
 */
अटल_निश्चित(ATOMIC_BOOL_LOCK_FREE == 2, "atomic bool is not lockless");

अटल sem_t vcpu_पढ़ोy;

अटल bool map_unmap_verअगरy;

अटल bool verbose;
#घोषणा pr_info_v(...)				\
	करो अणु					\
		अगर (verbose)			\
			pr_info(__VA_ARGS__);	\
	पूर्ण जबतक (0)

अटल व्योम *vcpu_worker(व्योम *data)
अणु
	काष्ठा vm_data *vm = data;
	काष्ठा kvm_run *run;
	काष्ठा ucall uc;
	uपूर्णांक64_t cmd;

	run = vcpu_state(vm->vm, VCPU_ID);
	जबतक (1) अणु
		vcpu_run(vm->vm, VCPU_ID);

		अगर (run->निकास_reason == KVM_EXIT_IO) अणु
			cmd = get_ucall(vm->vm, VCPU_ID, &uc);
			अगर (cmd != UCALL_SYNC)
				अवरोध;

			sem_post(&vcpu_पढ़ोy);
			जारी;
		पूर्ण

		अगर (run->निकास_reason != KVM_EXIT_MMIO)
			अवरोध;

		TEST_ASSERT(vm->mmio_ok, "Unexpected mmio exit");
		TEST_ASSERT(run->mmio.is_ग_लिखो, "Unexpected mmio read");
		TEST_ASSERT(run->mmio.len == 8,
			    "Unexpected exit mmio size = %u", run->mmio.len);
		TEST_ASSERT(run->mmio.phys_addr >= vm->mmio_gpa_min &&
			    run->mmio.phys_addr <= vm->mmio_gpa_max,
			    "Unexpected exit mmio address = 0x%llx",
			    run->mmio.phys_addr);
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
पूर्ण

अटल व्योम *vm_gpa2hva(काष्ठा vm_data *data, uपूर्णांक64_t gpa, uपूर्णांक64_t *rempages)
अणु
	uपूर्णांक64_t gpage, pgoffs;
	uपूर्णांक32_t slot, slotoffs;
	व्योम *base;

	TEST_ASSERT(gpa >= MEM_GPA, "Too low gpa to translate");
	TEST_ASSERT(gpa < MEM_GPA + data->npages * 4096,
		    "Too high gpa to translate");
	gpa -= MEM_GPA;

	gpage = gpa / 4096;
	pgoffs = gpa % 4096;
	slot = min(gpage / data->pages_per_slot, (uपूर्णांक64_t)data->nslots - 1);
	slotoffs = gpage - (slot * data->pages_per_slot);

	अगर (rempages) अणु
		uपूर्णांक64_t slotpages;

		अगर (slot == data->nslots - 1)
			slotpages = data->npages - slot * data->pages_per_slot;
		अन्यथा
			slotpages = data->pages_per_slot;

		TEST_ASSERT(!pgoffs,
			    "Asking for remaining pages in slot but gpa not page aligned");
		*rempages = slotpages - slotoffs;
	पूर्ण

	base = data->hva_slots[slot];
	वापस (uपूर्णांक8_t *)base + slotoffs * 4096 + pgoffs;
पूर्ण

अटल uपूर्णांक64_t vm_slot2gpa(काष्ठा vm_data *data, uपूर्णांक32_t slot)
अणु
	TEST_ASSERT(slot < data->nslots, "Too high slot number");

	वापस MEM_GPA + slot * data->pages_per_slot * 4096;
पूर्ण

अटल काष्ठा vm_data *alloc_vm(व्योम)
अणु
	काष्ठा vm_data *data;

	data = दो_स्मृति(माप(*data));
	TEST_ASSERT(data, "malloc(vmdata) failed");

	data->vm = शून्य;
	data->hva_slots = शून्य;

	वापस data;
पूर्ण

अटल bool prepare_vm(काष्ठा vm_data *data, पूर्णांक nslots, uपूर्णांक64_t *maxslots,
		       व्योम *guest_code, uपूर्णांक64_t mempages,
		       काष्ठा बारpec *slot_runसमय)
अणु
	uपूर्णांक32_t max_mem_slots;
	uपूर्णांक64_t rempages;
	uपूर्णांक64_t guest_addr;
	uपूर्णांक32_t slot;
	काष्ठा बारpec tstart;
	काष्ठा sync_area *sync;

	max_mem_slots = kvm_check_cap(KVM_CAP_NR_MEMSLOTS);
	TEST_ASSERT(max_mem_slots > 1,
		    "KVM_CAP_NR_MEMSLOTS should be greater than 1");
	TEST_ASSERT(nslots > 1 || nslots == -1,
		    "Slot count cap should be greater than 1");
	अगर (nslots != -1)
		max_mem_slots = min(max_mem_slots, (uपूर्णांक32_t)nslots);
	pr_info_v("Allowed number of memory slots: %"PRIu32"\n", max_mem_slots);

	TEST_ASSERT(mempages > 1,
		    "Can't test without any memory");

	data->npages = mempages;
	data->nslots = max_mem_slots - 1;
	data->pages_per_slot = mempages / data->nslots;
	अगर (!data->pages_per_slot) अणु
		*maxslots = mempages + 1;
		वापस false;
	पूर्ण

	rempages = mempages % data->nslots;
	data->hva_slots = दो_स्मृति(माप(*data->hva_slots) * data->nslots);
	TEST_ASSERT(data->hva_slots, "malloc() fail");

	data->vm = vm_create_शेष(VCPU_ID, mempages, guest_code);

	pr_info_v("Adding slots 1..%i, each slot with %"PRIu64" pages + %"PRIu64" extra pages last\n",
		max_mem_slots - 1, data->pages_per_slot, rempages);

	घड़ी_समय_लो(CLOCK_MONOTONIC, &tstart);
	क्रम (slot = 1, guest_addr = MEM_GPA; slot < max_mem_slots; slot++) अणु
		uपूर्णांक64_t npages;

		npages = data->pages_per_slot;
		अगर (slot == max_mem_slots - 1)
			npages += rempages;

		vm_userspace_mem_region_add(data->vm, VM_MEM_SRC_ANONYMOUS,
					    guest_addr, slot, npages,
					    0);
		guest_addr += npages * 4096;
	पूर्ण
	*slot_runसमय = बारpec_elapsed(tstart);

	क्रम (slot = 0, guest_addr = MEM_GPA; slot < max_mem_slots - 1; slot++) अणु
		uपूर्णांक64_t npages;
		uपूर्णांक64_t gpa;

		npages = data->pages_per_slot;
		अगर (slot == max_mem_slots - 2)
			npages += rempages;

		gpa = vm_phy_pages_alloc(data->vm, npages, guest_addr,
					 slot + 1);
		TEST_ASSERT(gpa == guest_addr,
			    "vm_phy_pages_alloc() failed\n");

		data->hva_slots[slot] = addr_gpa2hva(data->vm, guest_addr);
		स_रखो(data->hva_slots[slot], 0, npages * 4096);

		guest_addr += npages * 4096;
	पूर्ण

	virt_map(data->vm, MEM_GPA, MEM_GPA, mempages, 0);

	sync = (typeof(sync))vm_gpa2hva(data, MEM_SYNC_GPA, शून्य);
	atomic_init(&sync->start_flag, false);
	atomic_init(&sync->निकास_flag, false);
	atomic_init(&sync->sync_flag, false);

	data->mmio_ok = false;

	वापस true;
पूर्ण

अटल व्योम launch_vm(काष्ठा vm_data *data)
अणु
	pr_info_v("Launching the test VM\n");

	pthपढ़ो_create(&data->vcpu_thपढ़ो, शून्य, vcpu_worker, data);

	/* Ensure the guest thपढ़ो is spun up. */
	रुको_क्रम_vcpu();
पूर्ण

अटल व्योम मुक्त_vm(काष्ठा vm_data *data)
अणु
	kvm_vm_मुक्त(data->vm);
	मुक्त(data->hva_slots);
	मुक्त(data);
पूर्ण

अटल व्योम रुको_guest_निकास(काष्ठा vm_data *data)
अणु
	pthपढ़ो_join(data->vcpu_thपढ़ो, शून्य);
पूर्ण

अटल व्योम let_guest_run(काष्ठा sync_area *sync)
अणु
	atomic_store_explicit(&sync->start_flag, true, memory_order_release);
पूर्ण

अटल व्योम guest_spin_until_start(व्योम)
अणु
	काष्ठा sync_area *sync = (typeof(sync))MEM_SYNC_GPA;

	जबतक (!atomic_load_explicit(&sync->start_flag, memory_order_acquire))
		;
पूर्ण

अटल व्योम make_guest_निकास(काष्ठा sync_area *sync)
अणु
	atomic_store_explicit(&sync->निकास_flag, true, memory_order_release);
पूर्ण

अटल bool _guest_should_निकास(व्योम)
अणु
	काष्ठा sync_area *sync = (typeof(sync))MEM_SYNC_GPA;

	वापस atomic_load_explicit(&sync->निकास_flag, memory_order_acquire);
पूर्ण

#घोषणा guest_should_निकास() unlikely(_guest_should_निकास())

/*
 * noअंतरभूत so we can easily see how much समय the host spends रुकोing
 * क्रम the guest.
 * For the same reason use alarm() instead of polling घड़ी_समय_लो()
 * to implement a रुको समयout.
 */
अटल noअंतरभूत व्योम host_perक्रमm_sync(काष्ठा sync_area *sync)
अणु
	alarm(2);

	atomic_store_explicit(&sync->sync_flag, true, memory_order_release);
	जबतक (atomic_load_explicit(&sync->sync_flag, memory_order_acquire))
		;

	alarm(0);
पूर्ण

अटल bool guest_perक्रमm_sync(व्योम)
अणु
	काष्ठा sync_area *sync = (typeof(sync))MEM_SYNC_GPA;
	bool expected;

	करो अणु
		अगर (guest_should_निकास())
			वापस false;

		expected = true;
	पूर्ण जबतक (!atomic_compare_exchange_weak_explicit(&sync->sync_flag,
							&expected, false,
							memory_order_acq_rel,
							memory_order_relaxed));

	वापस true;
पूर्ण

अटल व्योम guest_code_test_memslot_move(व्योम)
अणु
	काष्ठा sync_area *sync = (typeof(sync))MEM_SYNC_GPA;
	uपूर्णांकptr_t base = (typeof(base))READ_ONCE(sync->move_area_ptr);

	GUEST_SYNC(0);

	guest_spin_until_start();

	जबतक (!guest_should_निकास()) अणु
		uपूर्णांकptr_t ptr;

		क्रम (ptr = base; ptr < base + MEM_TEST_MOVE_SIZE;
		     ptr += 4096)
			*(uपूर्णांक64_t *)ptr = MEM_TEST_VAL_1;

		/*
		 * No host sync here since the MMIO निकासs are so expensive
		 * that the host would spend most of its समय रुकोing क्रम
		 * the guest and so instead of measuring memslot move
		 * perक्रमmance we would measure the perक्रमmance and
		 * likelihood of MMIO निकासs
		 */
	पूर्ण

	GUEST_DONE();
पूर्ण

अटल व्योम guest_code_test_memslot_map(व्योम)
अणु
	काष्ठा sync_area *sync = (typeof(sync))MEM_SYNC_GPA;

	GUEST_SYNC(0);

	guest_spin_until_start();

	जबतक (1) अणु
		uपूर्णांकptr_t ptr;

		क्रम (ptr = MEM_TEST_GPA;
		     ptr < MEM_TEST_GPA + MEM_TEST_MAP_SIZE / 2; ptr += 4096)
			*(uपूर्णांक64_t *)ptr = MEM_TEST_VAL_1;

		अगर (!guest_perक्रमm_sync())
			अवरोध;

		क्रम (ptr = MEM_TEST_GPA + MEM_TEST_MAP_SIZE / 2;
		     ptr < MEM_TEST_GPA + MEM_TEST_MAP_SIZE; ptr += 4096)
			*(uपूर्णांक64_t *)ptr = MEM_TEST_VAL_2;

		अगर (!guest_perक्रमm_sync())
			अवरोध;
	पूर्ण

	GUEST_DONE();
पूर्ण

अटल व्योम guest_code_test_memslot_unmap(व्योम)
अणु
	काष्ठा sync_area *sync = (typeof(sync))MEM_SYNC_GPA;

	GUEST_SYNC(0);

	guest_spin_until_start();

	जबतक (1) अणु
		uपूर्णांकptr_t ptr = MEM_TEST_GPA;

		/*
		 * We can afक्रमd to access (map) just a small number of pages
		 * per host sync as otherwise the host will spend
		 * a signअगरicant amount of its समय रुकोing क्रम the guest
		 * (instead of करोing unmap operations), so this will
		 * effectively turn this test पूर्णांकo a map perक्रमmance test.
		 *
		 * Just access a single page to be on the safe side.
		 */
		*(uपूर्णांक64_t *)ptr = MEM_TEST_VAL_1;

		अगर (!guest_perक्रमm_sync())
			अवरोध;

		ptr += MEM_TEST_UNMAP_SIZE / 2;
		*(uपूर्णांक64_t *)ptr = MEM_TEST_VAL_2;

		अगर (!guest_perक्रमm_sync())
			अवरोध;
	पूर्ण

	GUEST_DONE();
पूर्ण

अटल व्योम guest_code_test_memslot_rw(व्योम)
अणु
	GUEST_SYNC(0);

	guest_spin_until_start();

	जबतक (1) अणु
		uपूर्णांकptr_t ptr;

		क्रम (ptr = MEM_TEST_GPA;
		     ptr < MEM_TEST_GPA + MEM_TEST_SIZE; ptr += 4096)
			*(uपूर्णांक64_t *)ptr = MEM_TEST_VAL_1;

		अगर (!guest_perक्रमm_sync())
			अवरोध;

		क्रम (ptr = MEM_TEST_GPA + 4096 / 2;
		     ptr < MEM_TEST_GPA + MEM_TEST_SIZE; ptr += 4096) अणु
			uपूर्णांक64_t val = *(uपूर्णांक64_t *)ptr;

			GUEST_ASSERT_1(val == MEM_TEST_VAL_2, val);
			*(uपूर्णांक64_t *)ptr = 0;
		पूर्ण

		अगर (!guest_perक्रमm_sync())
			अवरोध;
	पूर्ण

	GUEST_DONE();
पूर्ण

अटल bool test_memslot_move_prepare(काष्ठा vm_data *data,
				      काष्ठा sync_area *sync,
				      uपूर्णांक64_t *maxslots, bool isactive)
अणु
	uपूर्णांक64_t movesrcgpa, movetestgpa;

	movesrcgpa = vm_slot2gpa(data, data->nslots - 1);

	अगर (isactive) अणु
		uपूर्णांक64_t lastpages;

		vm_gpa2hva(data, movesrcgpa, &lastpages);
		अगर (lastpages < MEM_TEST_MOVE_SIZE_PAGES / 2) अणु
			*maxslots = 0;
			वापस false;
		पूर्ण
	पूर्ण

	movetestgpa = movesrcgpa - (MEM_TEST_MOVE_SIZE / (isactive ? 2 : 1));
	sync->move_area_ptr = (व्योम *)movetestgpa;

	अगर (isactive) अणु
		data->mmio_ok = true;
		data->mmio_gpa_min = movesrcgpa;
		data->mmio_gpa_max = movesrcgpa + MEM_TEST_MOVE_SIZE / 2 - 1;
	पूर्ण

	वापस true;
पूर्ण

अटल bool test_memslot_move_prepare_active(काष्ठा vm_data *data,
					     काष्ठा sync_area *sync,
					     uपूर्णांक64_t *maxslots)
अणु
	वापस test_memslot_move_prepare(data, sync, maxslots, true);
पूर्ण

अटल bool test_memslot_move_prepare_inactive(काष्ठा vm_data *data,
					       काष्ठा sync_area *sync,
					       uपूर्णांक64_t *maxslots)
अणु
	वापस test_memslot_move_prepare(data, sync, maxslots, false);
पूर्ण

अटल व्योम test_memslot_move_loop(काष्ठा vm_data *data, काष्ठा sync_area *sync)
अणु
	uपूर्णांक64_t movesrcgpa;

	movesrcgpa = vm_slot2gpa(data, data->nslots - 1);
	vm_mem_region_move(data->vm, data->nslots - 1 + 1,
			   MEM_TEST_MOVE_GPA_DEST);
	vm_mem_region_move(data->vm, data->nslots - 1 + 1, movesrcgpa);
पूर्ण

अटल व्योम test_memslot_करो_unmap(काष्ठा vm_data *data,
				  uपूर्णांक64_t offsp, uपूर्णांक64_t count)
अणु
	uपूर्णांक64_t gpa, ctr;

	क्रम (gpa = MEM_TEST_GPA + offsp * 4096, ctr = 0; ctr < count; ) अणु
		uपूर्णांक64_t npages;
		व्योम *hva;
		पूर्णांक ret;

		hva = vm_gpa2hva(data, gpa, &npages);
		TEST_ASSERT(npages, "Empty memory slot at gptr 0x%"PRIx64, gpa);
		npages = min(npages, count - ctr);
		ret = madvise(hva, npages * 4096, MADV_DONTNEED);
		TEST_ASSERT(!ret,
			    "madvise(%p, MADV_DONTNEED) on VM memory should not fail for gptr 0x%"PRIx64,
			    hva, gpa);
		ctr += npages;
		gpa += npages * 4096;
	पूर्ण
	TEST_ASSERT(ctr == count,
		    "madvise(MADV_DONTNEED) should exactly cover all of the requested area");
पूर्ण

अटल व्योम test_memslot_map_unmap_check(काष्ठा vm_data *data,
					 uपूर्णांक64_t offsp, uपूर्णांक64_t valexp)
अणु
	uपूर्णांक64_t gpa;
	uपूर्णांक64_t *val;

	अगर (!map_unmap_verअगरy)
		वापस;

	gpa = MEM_TEST_GPA + offsp * 4096;
	val = (typeof(val))vm_gpa2hva(data, gpa, शून्य);
	TEST_ASSERT(*val == valexp,
		    "Guest written values should read back correctly before unmap (%"PRIu64" vs %"PRIu64" @ %"PRIx64")",
		    *val, valexp, gpa);
	*val = 0;
पूर्ण

अटल व्योम test_memslot_map_loop(काष्ठा vm_data *data, काष्ठा sync_area *sync)
अणु
	/*
	 * Unmap the second half of the test area जबतक guest ग_लिखोs to (maps)
	 * the first half.
	 */
	test_memslot_करो_unmap(data, MEM_TEST_MAP_SIZE_PAGES / 2,
			      MEM_TEST_MAP_SIZE_PAGES / 2);

	/*
	 * Wait क्रम the guest to finish writing the first half of the test
	 * area, verअगरy the written value on the first and the last page of
	 * this area and then unmap it.
	 * Meanजबतक, the guest is writing to (mapping) the second half of
	 * the test area.
	 */
	host_perक्रमm_sync(sync);
	test_memslot_map_unmap_check(data, 0, MEM_TEST_VAL_1);
	test_memslot_map_unmap_check(data,
				     MEM_TEST_MAP_SIZE_PAGES / 2 - 1,
				     MEM_TEST_VAL_1);
	test_memslot_करो_unmap(data, 0, MEM_TEST_MAP_SIZE_PAGES / 2);


	/*
	 * Wait क्रम the guest to finish writing the second half of the test
	 * area and verअगरy the written value on the first and the last page
	 * of this area.
	 * The area will be unmapped at the beginning of the next loop
	 * iteration.
	 * Meanजबतक, the guest is writing to (mapping) the first half of
	 * the test area.
	 */
	host_perक्रमm_sync(sync);
	test_memslot_map_unmap_check(data, MEM_TEST_MAP_SIZE_PAGES / 2,
				     MEM_TEST_VAL_2);
	test_memslot_map_unmap_check(data, MEM_TEST_MAP_SIZE_PAGES - 1,
				     MEM_TEST_VAL_2);
पूर्ण

अटल व्योम test_memslot_unmap_loop_common(काष्ठा vm_data *data,
					   काष्ठा sync_area *sync,
					   uपूर्णांक64_t chunk)
अणु
	uपूर्णांक64_t ctr;

	/*
	 * Wait क्रम the guest to finish mapping page(s) in the first half
	 * of the test area, verअगरy the written value and then perक्रमm unmap
	 * of this area.
	 * Meanजबतक, the guest is writing to (mapping) page(s) in the second
	 * half of the test area.
	 */
	host_perक्रमm_sync(sync);
	test_memslot_map_unmap_check(data, 0, MEM_TEST_VAL_1);
	क्रम (ctr = 0; ctr < MEM_TEST_UNMAP_SIZE_PAGES / 2; ctr += chunk)
		test_memslot_करो_unmap(data, ctr, chunk);

	/* Likewise, but क्रम the opposite host / guest areas */
	host_perक्रमm_sync(sync);
	test_memslot_map_unmap_check(data, MEM_TEST_UNMAP_SIZE_PAGES / 2,
				     MEM_TEST_VAL_2);
	क्रम (ctr = MEM_TEST_UNMAP_SIZE_PAGES / 2;
	     ctr < MEM_TEST_UNMAP_SIZE_PAGES; ctr += chunk)
		test_memslot_करो_unmap(data, ctr, chunk);
पूर्ण

अटल व्योम test_memslot_unmap_loop(काष्ठा vm_data *data,
				    काष्ठा sync_area *sync)
अणु
	test_memslot_unmap_loop_common(data, sync, 1);
पूर्ण

अटल व्योम test_memslot_unmap_loop_chunked(काष्ठा vm_data *data,
					    काष्ठा sync_area *sync)
अणु
	test_memslot_unmap_loop_common(data, sync, MEM_TEST_UNMAP_CHUNK_PAGES);
पूर्ण

अटल व्योम test_memslot_rw_loop(काष्ठा vm_data *data, काष्ठा sync_area *sync)
अणु
	uपूर्णांक64_t gptr;

	क्रम (gptr = MEM_TEST_GPA + 4096 / 2;
	     gptr < MEM_TEST_GPA + MEM_TEST_SIZE; gptr += 4096)
		*(uपूर्णांक64_t *)vm_gpa2hva(data, gptr, शून्य) = MEM_TEST_VAL_2;

	host_perक्रमm_sync(sync);

	क्रम (gptr = MEM_TEST_GPA;
	     gptr < MEM_TEST_GPA + MEM_TEST_SIZE; gptr += 4096) अणु
		uपूर्णांक64_t *vptr = (typeof(vptr))vm_gpa2hva(data, gptr, शून्य);
		uपूर्णांक64_t val = *vptr;

		TEST_ASSERT(val == MEM_TEST_VAL_1,
			    "Guest written values should read back correctly (is %"PRIu64" @ %"PRIx64")",
			    val, gptr);
		*vptr = 0;
	पूर्ण

	host_perक्रमm_sync(sync);
पूर्ण

काष्ठा test_data अणु
	स्थिर अक्षर *name;
	uपूर्णांक64_t mem_size;
	व्योम (*guest_code)(व्योम);
	bool (*prepare)(काष्ठा vm_data *data, काष्ठा sync_area *sync,
			uपूर्णांक64_t *maxslots);
	व्योम (*loop)(काष्ठा vm_data *data, काष्ठा sync_area *sync);
पूर्ण;

अटल bool test_execute(पूर्णांक nslots, uपूर्णांक64_t *maxslots,
			 अचिन्हित पूर्णांक maxसमय,
			 स्थिर काष्ठा test_data *tdata,
			 uपूर्णांक64_t *nloops,
			 काष्ठा बारpec *slot_runसमय,
			 काष्ठा बारpec *guest_runसमय)
अणु
	uपूर्णांक64_t mem_size = tdata->mem_size ? : MEM_SIZE_PAGES;
	काष्ठा vm_data *data;
	काष्ठा sync_area *sync;
	काष्ठा बारpec tstart;
	bool ret = true;

	data = alloc_vm();
	अगर (!prepare_vm(data, nslots, maxslots, tdata->guest_code,
			mem_size, slot_runसमय)) अणु
		ret = false;
		जाओ निकास_मुक्त;
	पूर्ण

	sync = (typeof(sync))vm_gpa2hva(data, MEM_SYNC_GPA, शून्य);

	अगर (tdata->prepare &&
	    !tdata->prepare(data, sync, maxslots)) अणु
		ret = false;
		जाओ निकास_मुक्त;
	पूर्ण

	launch_vm(data);

	घड़ी_समय_लो(CLOCK_MONOTONIC, &tstart);
	let_guest_run(sync);

	जबतक (1) अणु
		*guest_runसमय = बारpec_elapsed(tstart);
		अगर (guest_runसमय->tv_sec >= maxसमय)
			अवरोध;

		tdata->loop(data, sync);

		(*nloops)++;
	पूर्ण

	make_guest_निकास(sync);
	रुको_guest_निकास(data);

निकास_मुक्त:
	मुक्त_vm(data);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा test_data tests[] = अणु
	अणु
		.name = "map",
		.mem_size = MEM_SIZE_MAP_PAGES,
		.guest_code = guest_code_test_memslot_map,
		.loop = test_memslot_map_loop,
	पूर्ण,
	अणु
		.name = "unmap",
		.mem_size = MEM_TEST_UNMAP_SIZE_PAGES + 1,
		.guest_code = guest_code_test_memslot_unmap,
		.loop = test_memslot_unmap_loop,
	पूर्ण,
	अणु
		.name = "unmap chunked",
		.mem_size = MEM_TEST_UNMAP_SIZE_PAGES + 1,
		.guest_code = guest_code_test_memslot_unmap,
		.loop = test_memslot_unmap_loop_chunked,
	पूर्ण,
	अणु
		.name = "move active area",
		.guest_code = guest_code_test_memslot_move,
		.prepare = test_memslot_move_prepare_active,
		.loop = test_memslot_move_loop,
	पूर्ण,
	अणु
		.name = "move inactive area",
		.guest_code = guest_code_test_memslot_move,
		.prepare = test_memslot_move_prepare_inactive,
		.loop = test_memslot_move_loop,
	पूर्ण,
	अणु
		.name = "RW",
		.guest_code = guest_code_test_memslot_rw,
		.loop = test_memslot_rw_loop
	पूर्ण,
पूर्ण;

#घोषणा NTESTS ARRAY_SIZE(tests)

काष्ठा test_args अणु
	पूर्णांक tfirst;
	पूर्णांक tlast;
	पूर्णांक nslots;
	पूर्णांक seconds;
	पूर्णांक runs;
पूर्ण;

अटल व्योम help(अक्षर *name, काष्ठा test_args *targs)
अणु
	पूर्णांक ctr;

	pr_info("usage: %s [-h] [-v] [-d] [-s slots] [-f first_test] [-e last_test] [-l test_length] [-r run_count]\n",
		name);
	pr_info(" -h: print this help screen.\n");
	pr_info(" -v: enable verbose mode (not for benchmarking).\n");
	pr_info(" -d: enable extra debug checks.\n");
	pr_info(" -s: specify memslot count cap (-1 means no cap; currently: %i)\n",
		targs->nslots);
	pr_info(" -f: specify the first test to run (currently: %i; max %zu)\n",
		targs->tfirst, NTESTS - 1);
	pr_info(" -e: specify the last test to run (currently: %i; max %zu)\n",
		targs->tlast, NTESTS - 1);
	pr_info(" -l: specify the test length in seconds (currently: %i)\n",
		targs->seconds);
	pr_info(" -r: specify the number of runs per test (currently: %i)\n",
		targs->runs);

	pr_info("\nAvailable tests:\n");
	क्रम (ctr = 0; ctr < NTESTS; ctr++)
		pr_info("%d: %s\n", ctr, tests[ctr].name);
पूर्ण

अटल bool parse_args(पूर्णांक argc, अक्षर *argv[],
		       काष्ठा test_args *targs)
अणु
	पूर्णांक opt;

	जबतक ((opt = getopt(argc, argv, "hvds:f:e:l:r:")) != -1) अणु
		चयन (opt) अणु
		हाल 'h':
		शेष:
			help(argv[0], targs);
			वापस false;
		हाल 'v':
			verbose = true;
			अवरोध;
		हाल 'd':
			map_unmap_verअगरy = true;
			अवरोध;
		हाल 's':
			targs->nslots = म_से_प(optarg);
			अगर (targs->nslots <= 0 && targs->nslots != -1) अणु
				pr_info("Slot count cap has to be positive or -1 for no cap\n");
				वापस false;
			पूर्ण
			अवरोध;
		हाल 'f':
			targs->tfirst = म_से_प(optarg);
			अगर (targs->tfirst < 0) अणु
				pr_info("First test to run has to be non-negative\n");
				वापस false;
			पूर्ण
			अवरोध;
		हाल 'e':
			targs->tlast = म_से_प(optarg);
			अगर (targs->tlast < 0 || targs->tlast >= NTESTS) अणु
				pr_info("Last test to run has to be non-negative and less than %zu\n",
					NTESTS);
				वापस false;
			पूर्ण
			अवरोध;
		हाल 'l':
			targs->seconds = म_से_प(optarg);
			अगर (targs->seconds < 0) अणु
				pr_info("Test length in seconds has to be non-negative\n");
				वापस false;
			पूर्ण
			अवरोध;
		हाल 'r':
			targs->runs = म_से_प(optarg);
			अगर (targs->runs <= 0) अणु
				pr_info("Runs per test has to be positive\n");
				वापस false;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (optind < argc) अणु
		help(argv[0], targs);
		वापस false;
	पूर्ण

	अगर (targs->tfirst > targs->tlast) अणु
		pr_info("First test to run cannot be greater than the last test to run\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

काष्ठा test_result अणु
	काष्ठा बारpec slot_runसमय, guest_runसमय, iter_runसमय;
	पूर्णांक64_t slotसमयns, runसमयns;
	uपूर्णांक64_t nloops;
पूर्ण;

अटल bool test_loop(स्थिर काष्ठा test_data *data,
		      स्थिर काष्ठा test_args *targs,
		      काष्ठा test_result *rbestslotसमय,
		      काष्ठा test_result *rbestrunसमय)
अणु
	uपूर्णांक64_t maxslots;
	काष्ठा test_result result;

	result.nloops = 0;
	अगर (!test_execute(targs->nslots, &maxslots, targs->seconds, data,
			  &result.nloops,
			  &result.slot_runसमय, &result.guest_runसमय)) अणु
		अगर (maxslots)
			pr_info("Memslot count too high for this test, decrease the cap (max is %"PRIu64")\n",
				maxslots);
		अन्यथा
			pr_info("Memslot count may be too high for this test, try adjusting the cap\n");

		वापस false;
	पूर्ण

	pr_info("Test took %ld.%.9lds for slot setup + %ld.%.9lds all iterations\n",
		result.slot_runसमय.tv_sec, result.slot_runसमय.tv_nsec,
		result.guest_runसमय.tv_sec, result.guest_runसमय.tv_nsec);
	अगर (!result.nloops) अणु
		pr_info("No full loops done - too short test time or system too loaded?\n");
		वापस true;
	पूर्ण

	result.iter_runसमय = बारpec_भाग(result.guest_runसमय,
					   result.nloops);
	pr_info("Done %"PRIu64" iterations, avg %ld.%.9lds each\n",
		result.nloops,
		result.iter_runसमय.tv_sec,
		result.iter_runसमय.tv_nsec);
	result.slotसमयns = बारpec_to_ns(result.slot_runसमय);
	result.runसमयns = बारpec_to_ns(result.iter_runसमय);

	/*
	 * Only rank the slot setup समय क्रम tests using the whole test memory
	 * area so they are comparable
	 */
	अगर (!data->mem_size &&
	    (!rbestslotसमय->slotसमयns ||
	     result.slotसमयns < rbestslotसमय->slotसमयns))
		*rbestslotसमय = result;
	अगर (!rbestrunसमय->runसमयns ||
	    result.runसमयns < rbestrunसमय->runसमयns)
		*rbestrunसमय = result;

	वापस true;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा test_args targs = अणु
		.tfirst = 0,
		.tlast = NTESTS - 1,
		.nslots = -1,
		.seconds = 5,
		.runs = 1,
	पूर्ण;
	काष्ठा test_result rbestslotसमय;
	पूर्णांक tctr;

	/* Tell मानक_निकास not to buffer its content */
	रखो_बफ(मानक_निकास, शून्य);

	अगर (!parse_args(argc, argv, &targs))
		वापस -1;

	rbestslotसमय.slotसमयns = 0;
	क्रम (tctr = targs.tfirst; tctr <= targs.tlast; tctr++) अणु
		स्थिर काष्ठा test_data *data = &tests[tctr];
		अचिन्हित पूर्णांक runctr;
		काष्ठा test_result rbestrunसमय;

		अगर (tctr > targs.tfirst)
			pr_info("\n");

		pr_info("Testing %s performance with %i runs, %d seconds each\n",
			data->name, targs.runs, targs.seconds);

		rbestrunसमय.runसमयns = 0;
		क्रम (runctr = 0; runctr < targs.runs; runctr++)
			अगर (!test_loop(data, &targs,
				       &rbestslotसमय, &rbestrunसमय))
				अवरोध;

		अगर (rbestrunसमय.runसमयns)
			pr_info("Best runtime result was %ld.%.9lds per iteration (with %"PRIu64" iterations)\n",
				rbestrunसमय.iter_runसमय.tv_sec,
				rbestrunसमय.iter_runसमय.tv_nsec,
				rbestrunसमय.nloops);
	पूर्ण

	अगर (rbestslotसमय.slotसमयns)
		pr_info("Best slot setup time for the whole test area was %ld.%.9lds\n",
			rbestslotसमय.slot_runसमय.tv_sec,
			rbestslotसमय.slot_runसमय.tv_nsec);

	वापस 0;
पूर्ण
