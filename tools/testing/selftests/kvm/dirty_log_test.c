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
#समावेश <pthपढ़ो.h>
#समावेश <semaphore.h>
#समावेश <sys/types.h>
#समावेश <संकेत.स>
#समावेश <त्रुटिसं.स>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/barrier.h>
#समावेश <linux/atomic.h>

#समावेश "kvm_util.h"
#समावेश "test_util.h"
#समावेश "guest_modes.h"
#समावेश "processor.h"

#घोषणा VCPU_ID				1

/* The memory slot index to track dirty pages */
#घोषणा TEST_MEM_SLOT_INDEX		1

/* Default guest test भव memory offset */
#घोषणा DEFAULT_GUEST_TEST_MEM		0xc0000000

/* How many pages to dirty क्रम each guest loop */
#घोषणा TEST_PAGES_PER_LOOP		1024

/* How many host loops to run (one KVM_GET_सूचीTY_LOG क्रम each loop) */
#घोषणा TEST_HOST_LOOP_N		32UL

/* Interval क्रम each host loop (ms) */
#घोषणा TEST_HOST_LOOP_INTERVAL		10UL

/* Dirty biपंचांगaps are always little endian, so we need to swap on big endian */
#अगर defined(__s390x__)
# define BITOP_LE_SWIZZLE	((BITS_PER_LONG-1) & ~0x7)
# define test_bit_le(nr, addr) \
	test_bit((nr) ^ BITOP_LE_SWIZZLE, addr)
# define set_bit_le(nr, addr) \
	set_bit((nr) ^ BITOP_LE_SWIZZLE, addr)
# define clear_bit_le(nr, addr) \
	clear_bit((nr) ^ BITOP_LE_SWIZZLE, addr)
# define test_and_set_bit_le(nr, addr) \
	test_and_set_bit((nr) ^ BITOP_LE_SWIZZLE, addr)
# define test_and_clear_bit_le(nr, addr) \
	test_and_clear_bit((nr) ^ BITOP_LE_SWIZZLE, addr)
#अन्यथा
# define test_bit_le		test_bit
# define set_bit_le		set_bit
# define clear_bit_le		clear_bit
# define test_and_set_bit_le	test_and_set_bit
# define test_and_clear_bit_le	test_and_clear_bit
#पूर्ण_अगर

#घोषणा TEST_सूचीTY_RING_COUNT		65536

#घोषणा SIG_IPI SIGUSR1

/*
 * Guest/Host shared variables. Ensure addr_gva2hva() and/or
 * sync_global_to/from_guest() are used when accessing from
 * the host. READ/WRITE_ONCE() should also be used with anything
 * that may change.
 */
अटल uपूर्णांक64_t host_page_size;
अटल uपूर्णांक64_t guest_page_size;
अटल uपूर्णांक64_t guest_num_pages;
अटल uपूर्णांक64_t अक्रमom_array[TEST_PAGES_PER_LOOP];
अटल uपूर्णांक64_t iteration;

/*
 * Guest physical memory offset of the testing memory slot.
 * This will be set to the topmost valid physical address minus
 * the test memory size.
 */
अटल uपूर्णांक64_t guest_test_phys_mem;

/*
 * Guest भव memory offset of the testing memory slot.
 * Must not conflict with identity mapped test code.
 */
अटल uपूर्णांक64_t guest_test_virt_mem = DEFAULT_GUEST_TEST_MEM;

/*
 * Continuously ग_लिखो to the first 8 bytes of a अक्रमom pages within
 * the testing memory region.
 */
अटल व्योम guest_code(व्योम)
अणु
	uपूर्णांक64_t addr;
	पूर्णांक i;

	/*
	 * On s390x, all pages of a 1M segment are initially marked as dirty
	 * when a page of the segment is written to क्रम the very first समय.
	 * To compensate this specialty in this test, we need to touch all
	 * pages during the first iteration.
	 */
	क्रम (i = 0; i < guest_num_pages; i++) अणु
		addr = guest_test_virt_mem + i * guest_page_size;
		*(uपूर्णांक64_t *)addr = READ_ONCE(iteration);
	पूर्ण

	जबतक (true) अणु
		क्रम (i = 0; i < TEST_PAGES_PER_LOOP; i++) अणु
			addr = guest_test_virt_mem;
			addr += (READ_ONCE(अक्रमom_array[i]) % guest_num_pages)
				* guest_page_size;
			addr &= ~(host_page_size - 1);
			*(uपूर्णांक64_t *)addr = READ_ONCE(iteration);
		पूर्ण

		/* Tell the host that we need more अक्रमom numbers */
		GUEST_SYNC(1);
	पूर्ण
पूर्ण

/* Host variables */
अटल bool host_quit;

/* Poपूर्णांकs to the test VM memory region on which we track dirty logs */
अटल व्योम *host_test_mem;
अटल uपूर्णांक64_t host_num_pages;

/* For statistics only */
अटल uपूर्णांक64_t host_dirty_count;
अटल uपूर्णांक64_t host_clear_count;
अटल uपूर्णांक64_t host_track_next_count;

/* Whether dirty ring reset is requested, or finished */
अटल sem_t sem_vcpu_stop;
अटल sem_t sem_vcpu_cont;
/*
 * This is only set by मुख्य thपढ़ो, and only cleared by vcpu thपढ़ो.  It is
 * used to request vcpu thपढ़ो to stop at the next GUEST_SYNC, since GUEST_SYNC
 * is the only place that we'll guarantee both "dirty bit" and "dirty data"
 * will match.  E.g., SIG_IPI won't guarantee that अगर the vcpu is पूर्णांकerrupted
 * after setting dirty bit but beक्रमe the data is written.
 */
अटल atomic_t vcpu_sync_stop_requested;
/*
 * This is updated by the vcpu thपढ़ो to tell the host whether it's a
 * ring-full event.  It should only be पढ़ो until a sem_रुको() of
 * sem_vcpu_stop and beक्रमe vcpu जारीs to run.
 */
अटल bool dirty_ring_vcpu_ring_full;
/*
 * This is only used क्रम verअगरying the dirty pages.  Dirty ring has a very
 * tricky हाल when the ring just got full, kvm will करो userspace निकास due to
 * ring full.  When that happens, the very last PFN is set but actually the
 * data is not changed (the guest WRITE is not really applied yet), because
 * we found that the dirty ring is full, refused to जारी the vcpu, and
 * recorded the dirty gfn with the old contents.
 *
 * For this specअगरic हाल, it's safe to skip checking this pfn क्रम this
 * bit, because it's a redundant bit, and when the ग_लिखो happens later the bit
 * will be set again.  We use this variable to always keep track of the latest
 * dirty gfn we've collected, so that अगर a mismatch of data found later in the
 * verअगरying process, we let it pass.
 */
अटल uपूर्णांक64_t dirty_ring_last_page;

क्रमागत log_mode_t अणु
	/* Only use KVM_GET_सूचीTY_LOG क्रम logging */
	LOG_MODE_सूचीTY_LOG = 0,

	/* Use both KVM_[GET|CLEAR]_सूचीTY_LOG क्रम logging */
	LOG_MODE_CLEAR_LOG = 1,

	/* Use dirty ring क्रम logging */
	LOG_MODE_सूचीTY_RING = 2,

	LOG_MODE_NUM,

	/* Run all supported modes */
	LOG_MODE_ALL = LOG_MODE_NUM,
पूर्ण;

/* Mode of logging to test.  Default is to run all supported modes */
अटल क्रमागत log_mode_t host_log_mode_option = LOG_MODE_ALL;
/* Logging mode क्रम current run */
अटल क्रमागत log_mode_t host_log_mode;
अटल pthपढ़ो_t vcpu_thपढ़ो;
अटल uपूर्णांक32_t test_dirty_ring_count = TEST_सूचीTY_RING_COUNT;

अटल व्योम vcpu_kick(व्योम)
अणु
	pthपढ़ो_समाप्त(vcpu_thपढ़ो, SIG_IPI);
पूर्ण

/*
 * In our test we करो संकेत tricks, let's use a better version of
 * sem_रुको to aव्योम संकेत पूर्णांकerrupts
 */
अटल व्योम sem_रुको_until(sem_t *sem)
अणु
	पूर्णांक ret;

	करो
		ret = sem_रुको(sem);
	जबतक (ret == -1 && त्रुटि_सं == EINTR);
पूर्ण

अटल bool clear_log_supported(व्योम)
अणु
	वापस kvm_check_cap(KVM_CAP_MANUAL_सूचीTY_LOG_PROTECT2);
पूर्ण

अटल व्योम clear_log_create_vm_करोne(काष्ठा kvm_vm *vm)
अणु
	काष्ठा kvm_enable_cap cap = अणुपूर्ण;
	u64 manual_caps;

	manual_caps = kvm_check_cap(KVM_CAP_MANUAL_सूचीTY_LOG_PROTECT2);
	TEST_ASSERT(manual_caps, "MANUAL_CAPS is zero!");
	manual_caps &= (KVM_सूचीTY_LOG_MANUAL_PROTECT_ENABLE |
			KVM_सूचीTY_LOG_INITIALLY_SET);
	cap.cap = KVM_CAP_MANUAL_सूचीTY_LOG_PROTECT2;
	cap.args[0] = manual_caps;
	vm_enable_cap(vm, &cap);
पूर्ण

अटल व्योम dirty_log_collect_dirty_pages(काष्ठा kvm_vm *vm, पूर्णांक slot,
					  व्योम *biपंचांगap, uपूर्णांक32_t num_pages)
अणु
	kvm_vm_get_dirty_log(vm, slot, biपंचांगap);
पूर्ण

अटल व्योम clear_log_collect_dirty_pages(काष्ठा kvm_vm *vm, पूर्णांक slot,
					  व्योम *biपंचांगap, uपूर्णांक32_t num_pages)
अणु
	kvm_vm_get_dirty_log(vm, slot, biपंचांगap);
	kvm_vm_clear_dirty_log(vm, slot, biपंचांगap, 0, num_pages);
पूर्ण

/* Should only be called after a GUEST_SYNC */
अटल व्योम vcpu_handle_sync_stop(व्योम)
अणु
	अगर (atomic_पढ़ो(&vcpu_sync_stop_requested)) अणु
		/* It means मुख्य thपढ़ो is sleeping रुकोing */
		atomic_set(&vcpu_sync_stop_requested, false);
		sem_post(&sem_vcpu_stop);
		sem_रुको_until(&sem_vcpu_cont);
	पूर्ण
पूर्ण

अटल व्योम शेष_after_vcpu_run(काष्ठा kvm_vm *vm, पूर्णांक ret, पूर्णांक err)
अणु
	काष्ठा kvm_run *run = vcpu_state(vm, VCPU_ID);

	TEST_ASSERT(ret == 0 || (ret == -1 && err == EINTR),
		    "vcpu run failed: errno=%d", err);

	TEST_ASSERT(get_ucall(vm, VCPU_ID, शून्य) == UCALL_SYNC,
		    "Invalid guest sync status: exit_reason=%s\n",
		    निकास_reason_str(run->निकास_reason));

	vcpu_handle_sync_stop();
पूर्ण

अटल bool dirty_ring_supported(व्योम)
अणु
	वापस kvm_check_cap(KVM_CAP_सूचीTY_LOG_RING);
पूर्ण

अटल व्योम dirty_ring_create_vm_करोne(काष्ठा kvm_vm *vm)
अणु
	/*
	 * Switch to dirty ring mode after VM creation but beक्रमe any
	 * of the vcpu creation.
	 */
	vm_enable_dirty_ring(vm, test_dirty_ring_count *
			     माप(काष्ठा kvm_dirty_gfn));
पूर्ण

अटल अंतरभूत bool dirty_gfn_is_dirtied(काष्ठा kvm_dirty_gfn *gfn)
अणु
	वापस gfn->flags == KVM_सूचीTY_GFN_F_सूचीTY;
पूर्ण

अटल अंतरभूत व्योम dirty_gfn_set_collected(काष्ठा kvm_dirty_gfn *gfn)
अणु
	gfn->flags = KVM_सूचीTY_GFN_F_RESET;
पूर्ण

अटल uपूर्णांक32_t dirty_ring_collect_one(काष्ठा kvm_dirty_gfn *dirty_gfns,
				       पूर्णांक slot, व्योम *biपंचांगap,
				       uपूर्णांक32_t num_pages, uपूर्णांक32_t *fetch_index)
अणु
	काष्ठा kvm_dirty_gfn *cur;
	uपूर्णांक32_t count = 0;

	जबतक (true) अणु
		cur = &dirty_gfns[*fetch_index % test_dirty_ring_count];
		अगर (!dirty_gfn_is_dirtied(cur))
			अवरोध;
		TEST_ASSERT(cur->slot == slot, "Slot number didn't match: "
			    "%u != %u", cur->slot, slot);
		TEST_ASSERT(cur->offset < num_pages, "Offset overflow: "
			    "0x%llx >= 0x%x", cur->offset, num_pages);
		//pr_info("fetch 0x%x page %llu\n", *fetch_index, cur->offset);
		set_bit_le(cur->offset, biपंचांगap);
		dirty_ring_last_page = cur->offset;
		dirty_gfn_set_collected(cur);
		(*fetch_index)++;
		count++;
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम dirty_ring_रुको_vcpu(व्योम)
अणु
	/* This makes sure that hardware PML cache flushed */
	vcpu_kick();
	sem_रुको_until(&sem_vcpu_stop);
पूर्ण

अटल व्योम dirty_ring_जारी_vcpu(व्योम)
अणु
	pr_info("Notifying vcpu to continue\n");
	sem_post(&sem_vcpu_cont);
पूर्ण

अटल व्योम dirty_ring_collect_dirty_pages(काष्ठा kvm_vm *vm, पूर्णांक slot,
					   व्योम *biपंचांगap, uपूर्णांक32_t num_pages)
अणु
	/* We only have one vcpu */
	अटल uपूर्णांक32_t fetch_index = 0;
	uपूर्णांक32_t count = 0, cleared;
	bool जारीd_vcpu = false;

	dirty_ring_रुको_vcpu();

	अगर (!dirty_ring_vcpu_ring_full) अणु
		/*
		 * This is not a ring-full event, it's safe to allow
		 * vcpu to जारी
		 */
		dirty_ring_जारी_vcpu();
		जारीd_vcpu = true;
	पूर्ण

	/* Only have one vcpu */
	count = dirty_ring_collect_one(vcpu_map_dirty_ring(vm, VCPU_ID),
				       slot, biपंचांगap, num_pages, &fetch_index);

	cleared = kvm_vm_reset_dirty_ring(vm);

	/* Cleared pages should be the same as collected */
	TEST_ASSERT(cleared == count, "Reset dirty pages (%u) mismatch "
		    "with collected (%u)", cleared, count);

	अगर (!जारीd_vcpu) अणु
		TEST_ASSERT(dirty_ring_vcpu_ring_full,
			    "Didn't continue vcpu even without ring full");
		dirty_ring_जारी_vcpu();
	पूर्ण

	pr_info("Iteration %ld collected %u pages\n", iteration, count);
पूर्ण

अटल व्योम dirty_ring_after_vcpu_run(काष्ठा kvm_vm *vm, पूर्णांक ret, पूर्णांक err)
अणु
	काष्ठा kvm_run *run = vcpu_state(vm, VCPU_ID);

	/* A ucall-sync or ring-full event is allowed */
	अगर (get_ucall(vm, VCPU_ID, शून्य) == UCALL_SYNC) अणु
		/* We should allow this to जारी */
		;
	पूर्ण अन्यथा अगर (run->निकास_reason == KVM_EXIT_सूचीTY_RING_FULL ||
		   (ret == -1 && err == EINTR)) अणु
		/* Update the flag first beक्रमe छोड़ो */
		WRITE_ONCE(dirty_ring_vcpu_ring_full,
			   run->निकास_reason == KVM_EXIT_सूचीTY_RING_FULL);
		sem_post(&sem_vcpu_stop);
		pr_info("vcpu stops because %s...\n",
			dirty_ring_vcpu_ring_full ?
			"dirty ring is full" : "vcpu is kicked out");
		sem_रुको_until(&sem_vcpu_cont);
		pr_info("vcpu continues now.\n");
	पूर्ण अन्यथा अणु
		TEST_ASSERT(false, "Invalid guest sync status: "
			    "exit_reason=%s\n",
			    निकास_reason_str(run->निकास_reason));
	पूर्ण
पूर्ण

अटल व्योम dirty_ring_beक्रमe_vcpu_join(व्योम)
अणु
	/* Kick another round of vcpu just to make sure it will quit */
	sem_post(&sem_vcpu_cont);
पूर्ण

काष्ठा log_mode अणु
	स्थिर अक्षर *name;
	/* Return true अगर this mode is supported, otherwise false */
	bool (*supported)(व्योम);
	/* Hook when the vm creation is करोne (beक्रमe vcpu creation) */
	व्योम (*create_vm_करोne)(काष्ठा kvm_vm *vm);
	/* Hook to collect the dirty pages पूर्णांकo the biपंचांगap provided */
	व्योम (*collect_dirty_pages) (काष्ठा kvm_vm *vm, पूर्णांक slot,
				     व्योम *biपंचांगap, uपूर्णांक32_t num_pages);
	/* Hook to call when after each vcpu run */
	व्योम (*after_vcpu_run)(काष्ठा kvm_vm *vm, पूर्णांक ret, पूर्णांक err);
	व्योम (*beक्रमe_vcpu_join) (व्योम);
पूर्ण log_modes[LOG_MODE_NUM] = अणु
	अणु
		.name = "dirty-log",
		.collect_dirty_pages = dirty_log_collect_dirty_pages,
		.after_vcpu_run = शेष_after_vcpu_run,
	पूर्ण,
	अणु
		.name = "clear-log",
		.supported = clear_log_supported,
		.create_vm_करोne = clear_log_create_vm_करोne,
		.collect_dirty_pages = clear_log_collect_dirty_pages,
		.after_vcpu_run = शेष_after_vcpu_run,
	पूर्ण,
	अणु
		.name = "dirty-ring",
		.supported = dirty_ring_supported,
		.create_vm_करोne = dirty_ring_create_vm_करोne,
		.collect_dirty_pages = dirty_ring_collect_dirty_pages,
		.beक्रमe_vcpu_join = dirty_ring_beक्रमe_vcpu_join,
		.after_vcpu_run = dirty_ring_after_vcpu_run,
	पूर्ण,
पूर्ण;

/*
 * We use this biपंचांगap to track some pages that should have its dirty
 * bit set in the _next_ iteration.  For example, अगर we detected the
 * page value changed to current iteration but at the same समय the
 * page bit is cleared in the latest biपंचांगap, then the प्रणाली must
 * report that ग_लिखो in the next get dirty log call.
 */
अटल अचिन्हित दीर्घ *host_bmap_track;

अटल व्योम log_modes_dump(व्योम)
अणु
	पूर्णांक i;

	म_लिखो("all");
	क्रम (i = 0; i < LOG_MODE_NUM; i++)
		म_लिखो(", %s", log_modes[i].name);
	म_लिखो("\n");
पूर्ण

अटल bool log_mode_supported(व्योम)
अणु
	काष्ठा log_mode *mode = &log_modes[host_log_mode];

	अगर (mode->supported)
		वापस mode->supported();

	वापस true;
पूर्ण

अटल व्योम log_mode_create_vm_करोne(काष्ठा kvm_vm *vm)
अणु
	काष्ठा log_mode *mode = &log_modes[host_log_mode];

	अगर (mode->create_vm_करोne)
		mode->create_vm_करोne(vm);
पूर्ण

अटल व्योम log_mode_collect_dirty_pages(काष्ठा kvm_vm *vm, पूर्णांक slot,
					 व्योम *biपंचांगap, uपूर्णांक32_t num_pages)
अणु
	काष्ठा log_mode *mode = &log_modes[host_log_mode];

	TEST_ASSERT(mode->collect_dirty_pages != शून्य,
		    "collect_dirty_pages() is required for any log mode!");
	mode->collect_dirty_pages(vm, slot, biपंचांगap, num_pages);
पूर्ण

अटल व्योम log_mode_after_vcpu_run(काष्ठा kvm_vm *vm, पूर्णांक ret, पूर्णांक err)
अणु
	काष्ठा log_mode *mode = &log_modes[host_log_mode];

	अगर (mode->after_vcpu_run)
		mode->after_vcpu_run(vm, ret, err);
पूर्ण

अटल व्योम log_mode_beक्रमe_vcpu_join(व्योम)
अणु
	काष्ठा log_mode *mode = &log_modes[host_log_mode];

	अगर (mode->beक्रमe_vcpu_join)
		mode->beक्रमe_vcpu_join();
पूर्ण

अटल व्योम generate_अक्रमom_array(uपूर्णांक64_t *guest_array, uपूर्णांक64_t size)
अणु
	uपूर्णांक64_t i;

	क्रम (i = 0; i < size; i++)
		guest_array[i] = अक्रमom();
पूर्ण

अटल व्योम *vcpu_worker(व्योम *data)
अणु
	पूर्णांक ret, vcpu_fd;
	काष्ठा kvm_vm *vm = data;
	uपूर्णांक64_t *guest_array;
	uपूर्णांक64_t pages_count = 0;
	काष्ठा kvm_संकेत_mask *sigmask = alloca(दुरत्व(काष्ठा kvm_संकेत_mask, sigset)
						 + माप(sigset_t));
	sigset_t *sigset = (sigset_t *) &sigmask->sigset;

	vcpu_fd = vcpu_get_fd(vm, VCPU_ID);

	/*
	 * SIG_IPI is unblocked atomically जबतक in KVM_RUN.  It causes the
	 * ioctl to वापस with -EINTR, but it is still pending and we need
	 * to accept it with the sigरुको.
	 */
	sigmask->len = 8;
	pthपढ़ो_sigmask(0, शून्य, sigset);
	sigdअन्यथाt(sigset, SIG_IPI);
	vcpu_ioctl(vm, VCPU_ID, KVM_SET_SIGNAL_MASK, sigmask);

	sigemptyset(sigset);
	sigaddset(sigset, SIG_IPI);

	guest_array = addr_gva2hva(vm, (vm_vaddr_t)अक्रमom_array);

	जबतक (!READ_ONCE(host_quit)) अणु
		/* Clear any existing kick संकेतs */
		generate_अक्रमom_array(guest_array, TEST_PAGES_PER_LOOP);
		pages_count += TEST_PAGES_PER_LOOP;
		/* Let the guest dirty the अक्रमom pages */
		ret = ioctl(vcpu_fd, KVM_RUN, शून्य);
		अगर (ret == -1 && त्रुटि_सं == EINTR) अणु
			पूर्णांक sig = -1;
			sigरुको(sigset, &sig);
			निश्चित(sig == SIG_IPI);
		पूर्ण
		log_mode_after_vcpu_run(vm, ret, त्रुटि_सं);
	पूर्ण

	pr_info("Dirtied %"PRIu64" pages\n", pages_count);

	वापस शून्य;
पूर्ण

अटल व्योम vm_dirty_log_verअगरy(क्रमागत vm_guest_mode mode, अचिन्हित दीर्घ *bmap)
अणु
	uपूर्णांक64_t step = vm_num_host_pages(mode, 1);
	uपूर्णांक64_t page;
	uपूर्णांक64_t *value_ptr;
	uपूर्णांक64_t min_iter = 0;

	क्रम (page = 0; page < host_num_pages; page += step) अणु
		value_ptr = host_test_mem + page * host_page_size;

		/* If this is a special page that we were tracking... */
		अगर (test_and_clear_bit_le(page, host_bmap_track)) अणु
			host_track_next_count++;
			TEST_ASSERT(test_bit_le(page, bmap),
				    "Page %"PRIu64" should have its dirty bit "
				    "set in this iteration but it is missing",
				    page);
		पूर्ण

		अगर (test_and_clear_bit_le(page, bmap)) अणु
			bool matched;

			host_dirty_count++;

			/*
			 * If the bit is set, the value written onto
			 * the corresponding page should be either the
			 * previous iteration number or the current one.
			 */
			matched = (*value_ptr == iteration ||
				   *value_ptr == iteration - 1);

			अगर (host_log_mode == LOG_MODE_सूचीTY_RING && !matched) अणु
				अगर (*value_ptr == iteration - 2 && min_iter <= iteration - 2) अणु
					/*
					 * Short answer: this हाल is special
					 * only क्रम dirty ring test where the
					 * page is the last page beक्रमe a kvm
					 * dirty ring full in iteration N-2.
					 *
					 * Long answer: Assuming ring size R,
					 * one possible condition is:
					 *
					 *      मुख्य thr       vcpu thr
					 *      --------       --------
					 *    iter=1
					 *                   ग_लिखो 1 to page 0~(R-1)
					 *                   full, vmनिकास
					 *    collect 0~(R-1)
					 *    kick vcpu
					 *                   ग_लिखो 1 to (R-1)~(2R-2)
					 *                   full, vmनिकास
					 *    iter=2
					 *    collect (R-1)~(2R-2)
					 *    kick vcpu
					 *                   ग_लिखो 1 to (2R-2)
					 *                   (NOTE!!! "1" cached in cpu reg)
					 *                   ग_लिखो 2 to (2R-1)~(3R-3)
					 *                   full, vmनिकास
					 *    iter=3
					 *    collect (2R-2)~(3R-3)
					 *    (here अगर we पढ़ो value on page
					 *     "2R-2" is 1, जबतक iter=3!!!)
					 *
					 * This however can only happen once per iteration.
					 */
					min_iter = iteration - 1;
					जारी;
				पूर्ण अन्यथा अगर (page == dirty_ring_last_page) अणु
					/*
					 * Please refer to comments in
					 * dirty_ring_last_page.
					 */
					जारी;
				पूर्ण
			पूर्ण

			TEST_ASSERT(matched,
				    "Set page %"PRIu64" value %"PRIu64
				    " incorrect (iteration=%"PRIu64")",
				    page, *value_ptr, iteration);
		पूर्ण अन्यथा अणु
			host_clear_count++;
			/*
			 * If cleared, the value written can be any
			 * value smaller or equals to the iteration
			 * number.  Note that the value can be exactly
			 * (iteration-1) अगर that ग_लिखो can happen
			 * like this:
			 *
			 * (1) increase loop count to "iteration-1"
			 * (2) ग_लिखो to page P happens (with value
			 *     "iteration-1")
			 * (3) get dirty log क्रम "iteration-1"; we'll
			 *     see that page P bit is set (dirtied),
			 *     and not set the bit in host_bmap_track
			 * (4) increase loop count to "iteration"
			 *     (which is current iteration)
			 * (5) get dirty log क्रम current iteration,
			 *     we'll see that page P is cleared, with
			 *     value "iteration-1".
			 */
			TEST_ASSERT(*value_ptr <= iteration,
				    "Clear page %"PRIu64" value %"PRIu64
				    " incorrect (iteration=%"PRIu64")",
				    page, *value_ptr, iteration);
			अगर (*value_ptr == iteration) अणु
				/*
				 * This page is _just_ modअगरied; it
				 * should report its dirtyness in the
				 * next run
				 */
				set_bit_le(page, host_bmap_track);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा kvm_vm *create_vm(क्रमागत vm_guest_mode mode, uपूर्णांक32_t vcpuid,
				uपूर्णांक64_t extra_mem_pages, व्योम *guest_code)
अणु
	काष्ठा kvm_vm *vm;
	uपूर्णांक64_t extra_pg_pages = extra_mem_pages / 512 * 2;

	pr_info("Testing guest mode: %s\n", vm_guest_mode_string(mode));

	vm = vm_create(mode, DEFAULT_GUEST_PHY_PAGES + extra_pg_pages, O_RDWR);
	kvm_vm_elf_load(vm, program_invocation_name, 0, 0);
#अगर_घोषित __x86_64__
	vm_create_irqchip(vm);
#पूर्ण_अगर
	log_mode_create_vm_करोne(vm);
	vm_vcpu_add_शेष(vm, vcpuid, guest_code);
	वापस vm;
पूर्ण

#घोषणा सूचीTY_MEM_BITS 30 /* 1G */
#घोषणा PAGE_SHIFT_4K  12

काष्ठा test_params अणु
	अचिन्हित दीर्घ iterations;
	अचिन्हित दीर्घ पूर्णांकerval;
	uपूर्णांक64_t phys_offset;
पूर्ण;

अटल व्योम run_test(क्रमागत vm_guest_mode mode, व्योम *arg)
अणु
	काष्ठा test_params *p = arg;
	काष्ठा kvm_vm *vm;
	अचिन्हित दीर्घ *bmap;

	अगर (!log_mode_supported()) अणु
		prपूर्णांक_skip("Log mode '%s' not supported",
			   log_modes[host_log_mode].name);
		वापस;
	पूर्ण

	/*
	 * We reserve page table क्रम 2 बार of extra dirty mem which
	 * will definitely cover the original (1G+) test range.  Here
	 * we करो the calculation with 4K page size which is the
	 * smallest so the page number will be enough क्रम all archs
	 * (e.g., 64K page size guest will need even less memory क्रम
	 * page tables).
	 */
	vm = create_vm(mode, VCPU_ID,
		       2ul << (सूचीTY_MEM_BITS - PAGE_SHIFT_4K),
		       guest_code);

	guest_page_size = vm_get_page_size(vm);
	/*
	 * A little more than 1G of guest page sized pages.  Cover the
	 * हाल where the size is not aligned to 64 pages.
	 */
	guest_num_pages = (1ul << (सूचीTY_MEM_BITS -
				   vm_get_page_shअगरt(vm))) + 3;
	guest_num_pages = vm_adjust_num_guest_pages(mode, guest_num_pages);

	host_page_size = getpagesize();
	host_num_pages = vm_num_host_pages(mode, guest_num_pages);

	अगर (!p->phys_offset) अणु
		guest_test_phys_mem = (vm_get_max_gfn(vm) -
				       guest_num_pages) * guest_page_size;
		guest_test_phys_mem &= ~(host_page_size - 1);
	पूर्ण अन्यथा अणु
		guest_test_phys_mem = p->phys_offset;
	पूर्ण

#अगर_घोषित __s390x__
	/* Align to 1M (segment size) */
	guest_test_phys_mem &= ~((1 << 20) - 1);
#पूर्ण_अगर

	pr_info("guest physical test memory offset: 0x%lx\n", guest_test_phys_mem);

	bmap = biपंचांगap_alloc(host_num_pages);
	host_bmap_track = biपंचांगap_alloc(host_num_pages);

	/* Add an extra memory slot क्रम testing dirty logging */
	vm_userspace_mem_region_add(vm, VM_MEM_SRC_ANONYMOUS,
				    guest_test_phys_mem,
				    TEST_MEM_SLOT_INDEX,
				    guest_num_pages,
				    KVM_MEM_LOG_सूचीTY_PAGES);

	/* Do mapping क्रम the dirty track memory slot */
	virt_map(vm, guest_test_virt_mem, guest_test_phys_mem, guest_num_pages, 0);

	/* Cache the HVA poपूर्णांकer of the region */
	host_test_mem = addr_gpa2hva(vm, (vm_paddr_t)guest_test_phys_mem);

	ucall_init(vm, शून्य);

	/* Export the shared variables to the guest */
	sync_global_to_guest(vm, host_page_size);
	sync_global_to_guest(vm, guest_page_size);
	sync_global_to_guest(vm, guest_test_virt_mem);
	sync_global_to_guest(vm, guest_num_pages);

	/* Start the iterations */
	iteration = 1;
	sync_global_to_guest(vm, iteration);
	host_quit = false;
	host_dirty_count = 0;
	host_clear_count = 0;
	host_track_next_count = 0;

	pthपढ़ो_create(&vcpu_thपढ़ो, शून्य, vcpu_worker, vm);

	जबतक (iteration < p->iterations) अणु
		/* Give the vcpu thपढ़ो some समय to dirty some pages */
		usleep(p->पूर्णांकerval * 1000);
		log_mode_collect_dirty_pages(vm, TEST_MEM_SLOT_INDEX,
					     bmap, host_num_pages);

		/*
		 * See vcpu_sync_stop_requested definition क्रम details on why
		 * we need to stop vcpu when verअगरy data.
		 */
		atomic_set(&vcpu_sync_stop_requested, true);
		sem_रुको_until(&sem_vcpu_stop);
		/*
		 * NOTE: क्रम dirty ring, it's possible that we didn't stop at
		 * GUEST_SYNC but instead we stopped because ring is full;
		 * that's okay too because ring full means we're only missing
		 * the flush of the last page, and since we handle the last
		 * page specially verअगरication will succeed anyway.
		 */
		निश्चित(host_log_mode == LOG_MODE_सूचीTY_RING ||
		       atomic_पढ़ो(&vcpu_sync_stop_requested) == false);
		vm_dirty_log_verअगरy(mode, bmap);
		sem_post(&sem_vcpu_cont);

		iteration++;
		sync_global_to_guest(vm, iteration);
	पूर्ण

	/* Tell the vcpu thपढ़ो to quit */
	host_quit = true;
	log_mode_beक्रमe_vcpu_join();
	pthपढ़ो_join(vcpu_thपढ़ो, शून्य);

	pr_info("Total bits checked: dirty (%"PRIu64"), clear (%"PRIu64"), "
		"track_next (%"PRIu64")\n", host_dirty_count, host_clear_count,
		host_track_next_count);

	मुक्त(bmap);
	मुक्त(host_bmap_track);
	ucall_uninit(vm);
	kvm_vm_मुक्त(vm);
पूर्ण

अटल व्योम help(अक्षर *name)
अणु
	माला_दो("");
	म_लिखो("usage: %s [-h] [-i iterations] [-I interval] "
	       "[-p offset] [-m mode]\n", name);
	माला_दो("");
	म_लिखो(" -c: specify dirty ring size, in number of entries\n");
	म_लिखो("     (only useful for dirty-ring test; default: %"PRIu32")\n",
	       TEST_सूचीTY_RING_COUNT);
	म_लिखो(" -i: specify iteration counts (default: %"PRIu64")\n",
	       TEST_HOST_LOOP_N);
	म_लिखो(" -I: specify interval in ms (default: %"PRIu64" ms)\n",
	       TEST_HOST_LOOP_INTERVAL);
	म_लिखो(" -p: specify guest physical test memory offset\n"
	       "     Warning: a low offset can conflict with the loaded test code.\n");
	म_लिखो(" -M: specify the host logging mode "
	       "(default: run all log modes).  Supported modes: \n\t");
	log_modes_dump();
	guest_modes_help();
	माला_दो("");
	निकास(0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा test_params p = अणु
		.iterations = TEST_HOST_LOOP_N,
		.पूर्णांकerval = TEST_HOST_LOOP_INTERVAL,
	पूर्ण;
	पूर्णांक opt, i;
	sigset_t sigset;

	sem_init(&sem_vcpu_stop, 0, 0);
	sem_init(&sem_vcpu_cont, 0, 0);

	guest_modes_append_शेष();

	जबतक ((opt = getopt(argc, argv, "c:hi:I:p:m:M:")) != -1) अणु
		चयन (opt) अणु
		हाल 'c':
			test_dirty_ring_count = म_से_दीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'i':
			p.iterations = म_से_दीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'I':
			p.पूर्णांकerval = म_से_दीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'p':
			p.phys_offset = म_से_अदीर्घl(optarg, शून्य, 0);
			अवरोध;
		हाल 'm':
			guest_modes_cmdline(optarg);
			अवरोध;
		हाल 'M':
			अगर (!म_भेद(optarg, "all")) अणु
				host_log_mode_option = LOG_MODE_ALL;
				अवरोध;
			पूर्ण
			क्रम (i = 0; i < LOG_MODE_NUM; i++) अणु
				अगर (!म_भेद(optarg, log_modes[i].name)) अणु
					pr_info("Setting log mode to: '%s'\n",
						optarg);
					host_log_mode_option = i;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (i == LOG_MODE_NUM) अणु
				म_लिखो("Log mode '%s' invalid. Please choose "
				       "from: ", optarg);
				log_modes_dump();
				निकास(1);
			पूर्ण
			अवरोध;
		हाल 'h':
		शेष:
			help(argv[0]);
			अवरोध;
		पूर्ण
	पूर्ण

	TEST_ASSERT(p.iterations > 2, "Iterations must be greater than two");
	TEST_ASSERT(p.पूर्णांकerval > 0, "Interval must be greater than zero");

	pr_info("Test iterations: %"PRIu64", interval: %"PRIu64" (ms)\n",
		p.iterations, p.पूर्णांकerval);

	बेक्रमom(समय(0));

	/* Ensure that vCPU thपढ़ोs start with SIG_IPI blocked.  */
	sigemptyset(&sigset);
	sigaddset(&sigset, SIG_IPI);
	pthपढ़ो_sigmask(SIG_BLOCK, &sigset, शून्य);

	अगर (host_log_mode_option == LOG_MODE_ALL) अणु
		/* Run each log mode */
		क्रम (i = 0; i < LOG_MODE_NUM; i++) अणु
			pr_info("Testing Log Mode '%s'\n", log_modes[i].name);
			host_log_mode = i;
			क्रम_each_guest_mode(run_test, &p);
		पूर्ण
	पूर्ण अन्यथा अणु
		host_log_mode = host_log_mode_option;
		क्रम_each_guest_mode(run_test, &p);
	पूर्ण

	वापस 0;
पूर्ण
