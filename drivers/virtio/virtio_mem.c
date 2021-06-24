<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Virtio-mem device driver.
 *
 * Copyright Red Hat, Inc. 2020
 *
 * Author(s): David Hildenbअक्रम <david@redhat.com>
 */

#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_स्मृति.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/memory.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/mutex.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/lockdep.h>

#समावेश <acpi/acpi_numa.h>

अटल bool unplug_online = true;
module_param(unplug_online, bool, 0644);
MODULE_PARM_DESC(unplug_online, "Try to unplug online memory");

अटल bool क्रमce_bbm;
module_param(क्रमce_bbm, bool, 0444);
MODULE_PARM_DESC(क्रमce_bbm,
		"Force Big Block Mode. Default is 0 (auto-selection)");

अटल अचिन्हित दीर्घ bbm_block_size;
module_param(bbm_block_size, uदीर्घ, 0444);
MODULE_PARM_DESC(bbm_block_size,
		 "Big Block size in bytes. Default is 0 (auto-detection).");

अटल bool bbm_safe_unplug = true;
module_param(bbm_safe_unplug, bool, 0444);
MODULE_PARM_DESC(bbm_safe_unplug,
	     "Use a safe unplug mechanism in BBM, avoiding long/endless loops");

/*
 * virtio-mem currently supports the following modes of operation:
 *
 * * Sub Block Mode (SBM): A Linux memory block spans 2..X subblocks (SB). The
 *   size of a Sub Block (SB) is determined based on the device block size, the
 *   pageblock size, and the maximum allocation granularity of the buddy.
 *   Subblocks within a Linux memory block might either be plugged or unplugged.
 *   Memory is added/हटाओd to Linux MM in Linux memory block granularity.
 *
 * * Big Block Mode (BBM): A Big Block (BB) spans 1..X Linux memory blocks.
 *   Memory is added/हटाओd to Linux MM in Big Block granularity.
 *
 * The mode is determined स्वतःmatically based on the Linux memory block size
 * and the device block size.
 *
 * User space / core MM (स्वतः onlining) is responsible क्रम onlining added
 * Linux memory blocks - and क्रम selecting a zone. Linux Memory Blocks are
 * always onlined separately, and all memory within a Linux memory block is
 * onlined to the same zone - virtio-mem relies on this behavior.
 */

/*
 * State of a Linux memory block in SBM.
 */
क्रमागत virtio_mem_sbm_mb_state अणु
	/* Unplugged, not added to Linux. Can be reused later. */
	VIRTIO_MEM_SBM_MB_UNUSED = 0,
	/* (Partially) plugged, not added to Linux. Error on add_memory(). */
	VIRTIO_MEM_SBM_MB_PLUGGED,
	/* Fully plugged, fully added to Linux, offline. */
	VIRTIO_MEM_SBM_MB_OFFLINE,
	/* Partially plugged, fully added to Linux, offline. */
	VIRTIO_MEM_SBM_MB_OFFLINE_PARTIAL,
	/* Fully plugged, fully added to Linux, online. */
	VIRTIO_MEM_SBM_MB_ONLINE,
	/* Partially plugged, fully added to Linux, online. */
	VIRTIO_MEM_SBM_MB_ONLINE_PARTIAL,
	VIRTIO_MEM_SBM_MB_COUNT
पूर्ण;

/*
 * State of a Big Block (BB) in BBM, covering 1..X Linux memory blocks.
 */
क्रमागत virtio_mem_bbm_bb_state अणु
	/* Unplugged, not added to Linux. Can be reused later. */
	VIRTIO_MEM_BBM_BB_UNUSED = 0,
	/* Plugged, not added to Linux. Error on add_memory(). */
	VIRTIO_MEM_BBM_BB_PLUGGED,
	/* Plugged and added to Linux. */
	VIRTIO_MEM_BBM_BB_ADDED,
	/* All online parts are fake-offline, पढ़ोy to हटाओ. */
	VIRTIO_MEM_BBM_BB_FAKE_OFFLINE,
	VIRTIO_MEM_BBM_BB_COUNT
पूर्ण;

काष्ठा virtio_mem अणु
	काष्ठा virtio_device *vdev;

	/* We might first have to unplug all memory when starting up. */
	bool unplug_all_required;

	/* Workqueue that processes the plug/unplug requests. */
	काष्ठा work_काष्ठा wq;
	atomic_t wq_active;
	atomic_t config_changed;

	/* Virtqueue क्रम guest->host requests. */
	काष्ठा virtqueue *vq;

	/* Wait क्रम a host response to a guest request. */
	रुको_queue_head_t host_resp;

	/* Space क्रम one guest request and the host response. */
	काष्ठा virtio_mem_req req;
	काष्ठा virtio_mem_resp resp;

	/* The current size of the device. */
	uपूर्णांक64_t plugged_size;
	/* The requested size of the device. */
	uपूर्णांक64_t requested_size;

	/* The device block size (क्रम communicating with the device). */
	uपूर्णांक64_t device_block_size;
	/* The determined node id क्रम all memory of the device. */
	पूर्णांक nid;
	/* Physical start address of the memory region. */
	uपूर्णांक64_t addr;
	/* Maximum region size in bytes. */
	uपूर्णांक64_t region_size;

	/* The parent resource क्रम all memory added via this device. */
	काष्ठा resource *parent_resource;
	/*
	 * Copy of "System RAM (virtio_mem)" to be used क्रम
	 * add_memory_driver_managed().
	 */
	स्थिर अक्षर *resource_name;

	/*
	 * We करोn't want to add too much memory if it's not getting onlined,
	 * to aव्योम running OOM. Besides this threshold, we allow to have at
	 * least two offline blocks at a समय (whatever is bigger).
	 */
#घोषणा VIRTIO_MEM_DEFAULT_OFFLINE_THRESHOLD		(1024 * 1024 * 1024)
	atomic64_t offline_size;
	uपूर्णांक64_t offline_threshold;

	/* If set, the driver is in SBM, otherwise in BBM. */
	bool in_sbm;

	जोड़ अणु
		काष्ठा अणु
			/* Id of the first memory block of this device. */
			अचिन्हित दीर्घ first_mb_id;
			/* Id of the last usable memory block of this device. */
			अचिन्हित दीर्घ last_usable_mb_id;
			/* Id of the next memory bock to prepare when needed. */
			अचिन्हित दीर्घ next_mb_id;

			/* The subblock size. */
			uपूर्णांक64_t sb_size;
			/* The number of subblocks per Linux memory block. */
			uपूर्णांक32_t sbs_per_mb;

			/* Summary of all memory block states. */
			अचिन्हित दीर्घ mb_count[VIRTIO_MEM_SBM_MB_COUNT];

			/*
			 * One byte state per memory block. Allocated via
			 * vदो_स्मृति(). Resized (alloc+copy+मुक्त) on demand.
			 *
			 * With 128 MiB memory blocks, we have states क्रम 512
			 * GiB of memory in one 4 KiB page.
			 */
			uपूर्णांक8_t *mb_states;

			/*
			 * Biपंचांगap: one bit per subblock. Allocated similar to
			 * sbm.mb_states.
			 *
			 * A set bit means the corresponding subblock is
			 * plugged, otherwise it's unblocked.
			 *
			 * With 4 MiB subblocks, we manage 128 GiB of memory
			 * in one 4 KiB page.
			 */
			अचिन्हित दीर्घ *sb_states;
		पूर्ण sbm;

		काष्ठा अणु
			/* Id of the first big block of this device. */
			अचिन्हित दीर्घ first_bb_id;
			/* Id of the last usable big block of this device. */
			अचिन्हित दीर्घ last_usable_bb_id;
			/* Id of the next device bock to prepare when needed. */
			अचिन्हित दीर्घ next_bb_id;

			/* Summary of all big block states. */
			अचिन्हित दीर्घ bb_count[VIRTIO_MEM_BBM_BB_COUNT];

			/* One byte state per big block. See sbm.mb_states. */
			uपूर्णांक8_t *bb_states;

			/* The block size used क्रम plugging/adding/removing. */
			uपूर्णांक64_t bb_size;
		पूर्ण bbm;
	पूर्ण;

	/*
	 * Mutex that protects the sbm.mb_count, sbm.mb_states,
	 * sbm.sb_states, bbm.bb_count, and bbm.bb_states
	 *
	 * When this lock is held the poपूर्णांकers can't change, ONLINE and
	 * OFFLINE blocks can't change the state and no subblocks will get
	 * plugged/unplugged.
	 */
	काष्ठा mutex hotplug_mutex;
	bool hotplug_active;

	/* An error occurred we cannot handle - stop processing requests. */
	bool broken;

	/* The driver is being हटाओd. */
	spinlock_t removal_lock;
	bool removing;

	/* Timer क्रम retrying to plug/unplug memory. */
	काष्ठा hrसमयr retry_समयr;
	अचिन्हित पूर्णांक retry_समयr_ms;
#घोषणा VIRTIO_MEM_RETRY_TIMER_MIN_MS		50000
#घोषणा VIRTIO_MEM_RETRY_TIMER_MAX_MS		300000

	/* Memory notअगरier (online/offline events). */
	काष्ठा notअगरier_block memory_notअगरier;

	/* Next device in the list of virtio-mem devices. */
	काष्ठा list_head next;
पूर्ण;

/*
 * We have to share a single online_page callback among all virtio-mem
 * devices. We use RCU to iterate the list in the callback.
 */
अटल DEFINE_MUTEX(virtio_mem_mutex);
अटल LIST_HEAD(virtio_mem_devices);

अटल व्योम virtio_mem_online_page_cb(काष्ठा page *page, अचिन्हित पूर्णांक order);
अटल व्योम virtio_mem_fake_offline_going_offline(अचिन्हित दीर्घ pfn,
						  अचिन्हित दीर्घ nr_pages);
अटल व्योम virtio_mem_fake_offline_cancel_offline(अचिन्हित दीर्घ pfn,
						   अचिन्हित दीर्घ nr_pages);
अटल व्योम virtio_mem_retry(काष्ठा virtio_mem *vm);

/*
 * Register a virtio-mem device so it will be considered क्रम the online_page
 * callback.
 */
अटल पूर्णांक रेजिस्टर_virtio_mem_device(काष्ठा virtio_mem *vm)
अणु
	पूर्णांक rc = 0;

	/* First device रेजिस्टरs the callback. */
	mutex_lock(&virtio_mem_mutex);
	अगर (list_empty(&virtio_mem_devices))
		rc = set_online_page_callback(&virtio_mem_online_page_cb);
	अगर (!rc)
		list_add_rcu(&vm->next, &virtio_mem_devices);
	mutex_unlock(&virtio_mem_mutex);

	वापस rc;
पूर्ण

/*
 * Unरेजिस्टर a virtio-mem device so it will no दीर्घer be considered क्रम the
 * online_page callback.
 */
अटल व्योम unरेजिस्टर_virtio_mem_device(काष्ठा virtio_mem *vm)
अणु
	/* Last device unरेजिस्टरs the callback. */
	mutex_lock(&virtio_mem_mutex);
	list_del_rcu(&vm->next);
	अगर (list_empty(&virtio_mem_devices))
		restore_online_page_callback(&virtio_mem_online_page_cb);
	mutex_unlock(&virtio_mem_mutex);

	synchronize_rcu();
पूर्ण

/*
 * Calculate the memory block id of a given address.
 */
अटल अचिन्हित दीर्घ virtio_mem_phys_to_mb_id(अचिन्हित दीर्घ addr)
अणु
	वापस addr / memory_block_size_bytes();
पूर्ण

/*
 * Calculate the physical start address of a given memory block id.
 */
अटल अचिन्हित दीर्घ virtio_mem_mb_id_to_phys(अचिन्हित दीर्घ mb_id)
अणु
	वापस mb_id * memory_block_size_bytes();
पूर्ण

/*
 * Calculate the big block id of a given address.
 */
अटल अचिन्हित दीर्घ virtio_mem_phys_to_bb_id(काष्ठा virtio_mem *vm,
					      uपूर्णांक64_t addr)
अणु
	वापस addr / vm->bbm.bb_size;
पूर्ण

/*
 * Calculate the physical start address of a given big block id.
 */
अटल uपूर्णांक64_t virtio_mem_bb_id_to_phys(काष्ठा virtio_mem *vm,
					 अचिन्हित दीर्घ bb_id)
अणु
	वापस bb_id * vm->bbm.bb_size;
पूर्ण

/*
 * Calculate the subblock id of a given address.
 */
अटल अचिन्हित दीर्घ virtio_mem_phys_to_sb_id(काष्ठा virtio_mem *vm,
					      अचिन्हित दीर्घ addr)
अणु
	स्थिर अचिन्हित दीर्घ mb_id = virtio_mem_phys_to_mb_id(addr);
	स्थिर अचिन्हित दीर्घ mb_addr = virtio_mem_mb_id_to_phys(mb_id);

	वापस (addr - mb_addr) / vm->sbm.sb_size;
पूर्ण

/*
 * Set the state of a big block, taking care of the state counter.
 */
अटल व्योम virtio_mem_bbm_set_bb_state(काष्ठा virtio_mem *vm,
					अचिन्हित दीर्घ bb_id,
					क्रमागत virtio_mem_bbm_bb_state state)
अणु
	स्थिर अचिन्हित दीर्घ idx = bb_id - vm->bbm.first_bb_id;
	क्रमागत virtio_mem_bbm_bb_state old_state;

	old_state = vm->bbm.bb_states[idx];
	vm->bbm.bb_states[idx] = state;

	BUG_ON(vm->bbm.bb_count[old_state] == 0);
	vm->bbm.bb_count[old_state]--;
	vm->bbm.bb_count[state]++;
पूर्ण

/*
 * Get the state of a big block.
 */
अटल क्रमागत virtio_mem_bbm_bb_state virtio_mem_bbm_get_bb_state(काष्ठा virtio_mem *vm,
								अचिन्हित दीर्घ bb_id)
अणु
	वापस vm->bbm.bb_states[bb_id - vm->bbm.first_bb_id];
पूर्ण

/*
 * Prepare the big block state array क्रम the next big block.
 */
अटल पूर्णांक virtio_mem_bbm_bb_states_prepare_next_bb(काष्ठा virtio_mem *vm)
अणु
	अचिन्हित दीर्घ old_bytes = vm->bbm.next_bb_id - vm->bbm.first_bb_id;
	अचिन्हित दीर्घ new_bytes = old_bytes + 1;
	पूर्णांक old_pages = PFN_UP(old_bytes);
	पूर्णांक new_pages = PFN_UP(new_bytes);
	uपूर्णांक8_t *new_array;

	अगर (vm->bbm.bb_states && old_pages == new_pages)
		वापस 0;

	new_array = vzalloc(new_pages * PAGE_SIZE);
	अगर (!new_array)
		वापस -ENOMEM;

	mutex_lock(&vm->hotplug_mutex);
	अगर (vm->bbm.bb_states)
		स_नकल(new_array, vm->bbm.bb_states, old_pages * PAGE_SIZE);
	vमुक्त(vm->bbm.bb_states);
	vm->bbm.bb_states = new_array;
	mutex_unlock(&vm->hotplug_mutex);

	वापस 0;
पूर्ण

#घोषणा virtio_mem_bbm_क्रम_each_bb(_vm, _bb_id, _state) \
	क्रम (_bb_id = vm->bbm.first_bb_id; \
	     _bb_id < vm->bbm.next_bb_id && _vm->bbm.bb_count[_state]; \
	     _bb_id++) \
		अगर (virtio_mem_bbm_get_bb_state(_vm, _bb_id) == _state)

#घोषणा virtio_mem_bbm_क्रम_each_bb_rev(_vm, _bb_id, _state) \
	क्रम (_bb_id = vm->bbm.next_bb_id - 1; \
	     _bb_id >= vm->bbm.first_bb_id && _vm->bbm.bb_count[_state]; \
	     _bb_id--) \
		अगर (virtio_mem_bbm_get_bb_state(_vm, _bb_id) == _state)

/*
 * Set the state of a memory block, taking care of the state counter.
 */
अटल व्योम virtio_mem_sbm_set_mb_state(काष्ठा virtio_mem *vm,
					अचिन्हित दीर्घ mb_id, uपूर्णांक8_t state)
अणु
	स्थिर अचिन्हित दीर्घ idx = mb_id - vm->sbm.first_mb_id;
	uपूर्णांक8_t old_state;

	old_state = vm->sbm.mb_states[idx];
	vm->sbm.mb_states[idx] = state;

	BUG_ON(vm->sbm.mb_count[old_state] == 0);
	vm->sbm.mb_count[old_state]--;
	vm->sbm.mb_count[state]++;
पूर्ण

/*
 * Get the state of a memory block.
 */
अटल uपूर्णांक8_t virtio_mem_sbm_get_mb_state(काष्ठा virtio_mem *vm,
					   अचिन्हित दीर्घ mb_id)
अणु
	स्थिर अचिन्हित दीर्घ idx = mb_id - vm->sbm.first_mb_id;

	वापस vm->sbm.mb_states[idx];
पूर्ण

/*
 * Prepare the state array क्रम the next memory block.
 */
अटल पूर्णांक virtio_mem_sbm_mb_states_prepare_next_mb(काष्ठा virtio_mem *vm)
अणु
	पूर्णांक old_pages = PFN_UP(vm->sbm.next_mb_id - vm->sbm.first_mb_id);
	पूर्णांक new_pages = PFN_UP(vm->sbm.next_mb_id - vm->sbm.first_mb_id + 1);
	uपूर्णांक8_t *new_array;

	अगर (vm->sbm.mb_states && old_pages == new_pages)
		वापस 0;

	new_array = vzalloc(new_pages * PAGE_SIZE);
	अगर (!new_array)
		वापस -ENOMEM;

	mutex_lock(&vm->hotplug_mutex);
	अगर (vm->sbm.mb_states)
		स_नकल(new_array, vm->sbm.mb_states, old_pages * PAGE_SIZE);
	vमुक्त(vm->sbm.mb_states);
	vm->sbm.mb_states = new_array;
	mutex_unlock(&vm->hotplug_mutex);

	वापस 0;
पूर्ण

#घोषणा virtio_mem_sbm_क्रम_each_mb(_vm, _mb_id, _state) \
	क्रम (_mb_id = _vm->sbm.first_mb_id; \
	     _mb_id < _vm->sbm.next_mb_id && _vm->sbm.mb_count[_state]; \
	     _mb_id++) \
		अगर (virtio_mem_sbm_get_mb_state(_vm, _mb_id) == _state)

#घोषणा virtio_mem_sbm_क्रम_each_mb_rev(_vm, _mb_id, _state) \
	क्रम (_mb_id = _vm->sbm.next_mb_id - 1; \
	     _mb_id >= _vm->sbm.first_mb_id && _vm->sbm.mb_count[_state]; \
	     _mb_id--) \
		अगर (virtio_mem_sbm_get_mb_state(_vm, _mb_id) == _state)

/*
 * Calculate the bit number in the subblock biपंचांगap क्रम the given subblock
 * inside the given memory block.
 */
अटल पूर्णांक virtio_mem_sbm_sb_state_bit_nr(काष्ठा virtio_mem *vm,
					  अचिन्हित दीर्घ mb_id, पूर्णांक sb_id)
अणु
	वापस (mb_id - vm->sbm.first_mb_id) * vm->sbm.sbs_per_mb + sb_id;
पूर्ण

/*
 * Mark all selected subblocks plugged.
 *
 * Will not modअगरy the state of the memory block.
 */
अटल व्योम virtio_mem_sbm_set_sb_plugged(काष्ठा virtio_mem *vm,
					  अचिन्हित दीर्घ mb_id, पूर्णांक sb_id,
					  पूर्णांक count)
अणु
	स्थिर पूर्णांक bit = virtio_mem_sbm_sb_state_bit_nr(vm, mb_id, sb_id);

	__biपंचांगap_set(vm->sbm.sb_states, bit, count);
पूर्ण

/*
 * Mark all selected subblocks unplugged.
 *
 * Will not modअगरy the state of the memory block.
 */
अटल व्योम virtio_mem_sbm_set_sb_unplugged(काष्ठा virtio_mem *vm,
					    अचिन्हित दीर्घ mb_id, पूर्णांक sb_id,
					    पूर्णांक count)
अणु
	स्थिर पूर्णांक bit = virtio_mem_sbm_sb_state_bit_nr(vm, mb_id, sb_id);

	__biपंचांगap_clear(vm->sbm.sb_states, bit, count);
पूर्ण

/*
 * Test अगर all selected subblocks are plugged.
 */
अटल bool virtio_mem_sbm_test_sb_plugged(काष्ठा virtio_mem *vm,
					   अचिन्हित दीर्घ mb_id, पूर्णांक sb_id,
					   पूर्णांक count)
अणु
	स्थिर पूर्णांक bit = virtio_mem_sbm_sb_state_bit_nr(vm, mb_id, sb_id);

	अगर (count == 1)
		वापस test_bit(bit, vm->sbm.sb_states);

	/* TODO: Helper similar to biपंचांगap_set() */
	वापस find_next_zero_bit(vm->sbm.sb_states, bit + count, bit) >=
	       bit + count;
पूर्ण

/*
 * Test अगर all selected subblocks are unplugged.
 */
अटल bool virtio_mem_sbm_test_sb_unplugged(काष्ठा virtio_mem *vm,
					     अचिन्हित दीर्घ mb_id, पूर्णांक sb_id,
					     पूर्णांक count)
अणु
	स्थिर पूर्णांक bit = virtio_mem_sbm_sb_state_bit_nr(vm, mb_id, sb_id);

	/* TODO: Helper similar to biपंचांगap_set() */
	वापस find_next_bit(vm->sbm.sb_states, bit + count, bit) >=
	       bit + count;
पूर्ण

/*
 * Find the first unplugged subblock. Returns vm->sbm.sbs_per_mb in हाल there is
 * none.
 */
अटल पूर्णांक virtio_mem_sbm_first_unplugged_sb(काष्ठा virtio_mem *vm,
					    अचिन्हित दीर्घ mb_id)
अणु
	स्थिर पूर्णांक bit = virtio_mem_sbm_sb_state_bit_nr(vm, mb_id, 0);

	वापस find_next_zero_bit(vm->sbm.sb_states,
				  bit + vm->sbm.sbs_per_mb, bit) - bit;
पूर्ण

/*
 * Prepare the subblock biपंचांगap क्रम the next memory block.
 */
अटल पूर्णांक virtio_mem_sbm_sb_states_prepare_next_mb(काष्ठा virtio_mem *vm)
अणु
	स्थिर अचिन्हित दीर्घ old_nb_mb = vm->sbm.next_mb_id - vm->sbm.first_mb_id;
	स्थिर अचिन्हित दीर्घ old_nb_bits = old_nb_mb * vm->sbm.sbs_per_mb;
	स्थिर अचिन्हित दीर्घ new_nb_bits = (old_nb_mb + 1) * vm->sbm.sbs_per_mb;
	पूर्णांक old_pages = PFN_UP(BITS_TO_LONGS(old_nb_bits) * माप(दीर्घ));
	पूर्णांक new_pages = PFN_UP(BITS_TO_LONGS(new_nb_bits) * माप(दीर्घ));
	अचिन्हित दीर्घ *new_biपंचांगap, *old_biपंचांगap;

	अगर (vm->sbm.sb_states && old_pages == new_pages)
		वापस 0;

	new_biपंचांगap = vzalloc(new_pages * PAGE_SIZE);
	अगर (!new_biपंचांगap)
		वापस -ENOMEM;

	mutex_lock(&vm->hotplug_mutex);
	अगर (new_biपंचांगap)
		स_नकल(new_biपंचांगap, vm->sbm.sb_states, old_pages * PAGE_SIZE);

	old_biपंचांगap = vm->sbm.sb_states;
	vm->sbm.sb_states = new_biपंचांगap;
	mutex_unlock(&vm->hotplug_mutex);

	vमुक्त(old_biपंचांगap);
	वापस 0;
पूर्ण

/*
 * Test अगर we could add memory without creating too much offline memory -
 * to aव्योम running OOM अगर memory is getting onlined deferred.
 */
अटल bool virtio_mem_could_add_memory(काष्ठा virtio_mem *vm, uपूर्णांक64_t size)
अणु
	अगर (WARN_ON_ONCE(size > vm->offline_threshold))
		वापस false;

	वापस atomic64_पढ़ो(&vm->offline_size) + size <= vm->offline_threshold;
पूर्ण

/*
 * Try adding memory to Linux. Will usually only fail अगर out of memory.
 *
 * Must not be called with the vm->hotplug_mutex held (possible deadlock with
 * onlining code).
 *
 * Will not modअगरy the state of memory blocks in virtio-mem.
 */
अटल पूर्णांक virtio_mem_add_memory(काष्ठा virtio_mem *vm, uपूर्णांक64_t addr,
				 uपूर्णांक64_t size)
अणु
	पूर्णांक rc;

	/*
	 * When क्रमce-unloading the driver and we still have memory added to
	 * Linux, the resource name has to stay.
	 */
	अगर (!vm->resource_name) अणु
		vm->resource_name = kstrdup_स्थिर("System RAM (virtio_mem)",
						  GFP_KERNEL);
		अगर (!vm->resource_name)
			वापस -ENOMEM;
	पूर्ण

	dev_dbg(&vm->vdev->dev, "adding memory: 0x%llx - 0x%llx\n", addr,
		addr + size - 1);
	/* Memory might get onlined immediately. */
	atomic64_add(size, &vm->offline_size);
	rc = add_memory_driver_managed(vm->nid, addr, size, vm->resource_name,
				       MHP_MERGE_RESOURCE);
	अगर (rc) अणु
		atomic64_sub(size, &vm->offline_size);
		dev_warn(&vm->vdev->dev, "adding memory failed: %d\n", rc);
		/*
		 * TODO: Linux MM करोes not properly clean up yet in all हालs
		 * where adding of memory failed - especially on -ENOMEM.
		 */
	पूर्ण
	वापस rc;
पूर्ण

/*
 * See virtio_mem_add_memory(): Try adding a single Linux memory block.
 */
अटल पूर्णांक virtio_mem_sbm_add_mb(काष्ठा virtio_mem *vm, अचिन्हित दीर्घ mb_id)
अणु
	स्थिर uपूर्णांक64_t addr = virtio_mem_mb_id_to_phys(mb_id);
	स्थिर uपूर्णांक64_t size = memory_block_size_bytes();

	वापस virtio_mem_add_memory(vm, addr, size);
पूर्ण

/*
 * See virtio_mem_add_memory(): Try adding a big block.
 */
अटल पूर्णांक virtio_mem_bbm_add_bb(काष्ठा virtio_mem *vm, अचिन्हित दीर्घ bb_id)
अणु
	स्थिर uपूर्णांक64_t addr = virtio_mem_bb_id_to_phys(vm, bb_id);
	स्थिर uपूर्णांक64_t size = vm->bbm.bb_size;

	वापस virtio_mem_add_memory(vm, addr, size);
पूर्ण

/*
 * Try removing memory from Linux. Will only fail अगर memory blocks aren't
 * offline.
 *
 * Must not be called with the vm->hotplug_mutex held (possible deadlock with
 * onlining code).
 *
 * Will not modअगरy the state of memory blocks in virtio-mem.
 */
अटल पूर्णांक virtio_mem_हटाओ_memory(काष्ठा virtio_mem *vm, uपूर्णांक64_t addr,
				    uपूर्णांक64_t size)
अणु
	पूर्णांक rc;

	dev_dbg(&vm->vdev->dev, "removing memory: 0x%llx - 0x%llx\n", addr,
		addr + size - 1);
	rc = हटाओ_memory(vm->nid, addr, size);
	अगर (!rc) अणु
		atomic64_sub(size, &vm->offline_size);
		/*
		 * We might have मुक्तd up memory we can now unplug, retry
		 * immediately instead of रुकोing.
		 */
		virtio_mem_retry(vm);
	पूर्ण अन्यथा अणु
		dev_dbg(&vm->vdev->dev, "removing memory failed: %d\n", rc);
	पूर्ण
	वापस rc;
पूर्ण

/*
 * See virtio_mem_हटाओ_memory(): Try removing a single Linux memory block.
 */
अटल पूर्णांक virtio_mem_sbm_हटाओ_mb(काष्ठा virtio_mem *vm, अचिन्हित दीर्घ mb_id)
अणु
	स्थिर uपूर्णांक64_t addr = virtio_mem_mb_id_to_phys(mb_id);
	स्थिर uपूर्णांक64_t size = memory_block_size_bytes();

	वापस virtio_mem_हटाओ_memory(vm, addr, size);
पूर्ण

/*
 * See virtio_mem_हटाओ_memory(): Try to हटाओ all Linux memory blocks covered
 * by the big block.
 */
अटल पूर्णांक virtio_mem_bbm_हटाओ_bb(काष्ठा virtio_mem *vm, अचिन्हित दीर्घ bb_id)
अणु
	स्थिर uपूर्णांक64_t addr = virtio_mem_bb_id_to_phys(vm, bb_id);
	स्थिर uपूर्णांक64_t size = vm->bbm.bb_size;

	वापस virtio_mem_हटाओ_memory(vm, addr, size);
पूर्ण

/*
 * Try offlining and removing memory from Linux.
 *
 * Must not be called with the vm->hotplug_mutex held (possible deadlock with
 * onlining code).
 *
 * Will not modअगरy the state of memory blocks in virtio-mem.
 */
अटल पूर्णांक virtio_mem_offline_and_हटाओ_memory(काष्ठा virtio_mem *vm,
						uपूर्णांक64_t addr,
						uपूर्णांक64_t size)
अणु
	पूर्णांक rc;

	dev_dbg(&vm->vdev->dev,
		"offlining and removing memory: 0x%llx - 0x%llx\n", addr,
		addr + size - 1);

	rc = offline_and_हटाओ_memory(vm->nid, addr, size);
	अगर (!rc) अणु
		atomic64_sub(size, &vm->offline_size);
		/*
		 * We might have मुक्तd up memory we can now unplug, retry
		 * immediately instead of रुकोing.
		 */
		virtio_mem_retry(vm);
	पूर्ण अन्यथा अणु
		dev_dbg(&vm->vdev->dev,
			"offlining and removing memory failed: %d\n", rc);
	पूर्ण
	वापस rc;
पूर्ण

/*
 * See virtio_mem_offline_and_हटाओ_memory(): Try offlining and removing
 * a single Linux memory block.
 */
अटल पूर्णांक virtio_mem_sbm_offline_and_हटाओ_mb(काष्ठा virtio_mem *vm,
						अचिन्हित दीर्घ mb_id)
अणु
	स्थिर uपूर्णांक64_t addr = virtio_mem_mb_id_to_phys(mb_id);
	स्थिर uपूर्णांक64_t size = memory_block_size_bytes();

	वापस virtio_mem_offline_and_हटाओ_memory(vm, addr, size);
पूर्ण

/*
 * See virtio_mem_offline_and_हटाओ_memory(): Try to offline and हटाओ a
 * all Linux memory blocks covered by the big block.
 */
अटल पूर्णांक virtio_mem_bbm_offline_and_हटाओ_bb(काष्ठा virtio_mem *vm,
						अचिन्हित दीर्घ bb_id)
अणु
	स्थिर uपूर्णांक64_t addr = virtio_mem_bb_id_to_phys(vm, bb_id);
	स्थिर uपूर्णांक64_t size = vm->bbm.bb_size;

	वापस virtio_mem_offline_and_हटाओ_memory(vm, addr, size);
पूर्ण

/*
 * Trigger the workqueue so the device can perक्रमm its magic.
 */
अटल व्योम virtio_mem_retry(काष्ठा virtio_mem *vm)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vm->removal_lock, flags);
	अगर (!vm->removing)
		queue_work(प्रणाली_मुक्तzable_wq, &vm->wq);
	spin_unlock_irqrestore(&vm->removal_lock, flags);
पूर्ण

अटल पूर्णांक virtio_mem_translate_node_id(काष्ठा virtio_mem *vm, uपूर्णांक16_t node_id)
अणु
	पूर्णांक node = NUMA_NO_NODE;

#अगर defined(CONFIG_ACPI_NUMA)
	अगर (virtio_has_feature(vm->vdev, VIRTIO_MEM_F_ACPI_PXM))
		node = pxm_to_node(node_id);
#पूर्ण_अगर
	वापस node;
पूर्ण

/*
 * Test अगर a virtio-mem device overlaps with the given range. Can be called
 * from (notअगरier) callbacks lockless.
 */
अटल bool virtio_mem_overlaps_range(काष्ठा virtio_mem *vm, uपूर्णांक64_t start,
				      uपूर्णांक64_t size)
अणु
	वापस start < vm->addr + vm->region_size && vm->addr < start + size;
पूर्ण

/*
 * Test अगर a virtio-mem device contains a given range. Can be called from
 * (notअगरier) callbacks lockless.
 */
अटल bool virtio_mem_contains_range(काष्ठा virtio_mem *vm, uपूर्णांक64_t start,
				      uपूर्णांक64_t size)
अणु
	वापस start >= vm->addr && start + size <= vm->addr + vm->region_size;
पूर्ण

अटल पूर्णांक virtio_mem_sbm_notअगरy_going_online(काष्ठा virtio_mem *vm,
					      अचिन्हित दीर्घ mb_id)
अणु
	चयन (virtio_mem_sbm_get_mb_state(vm, mb_id)) अणु
	हाल VIRTIO_MEM_SBM_MB_OFFLINE_PARTIAL:
	हाल VIRTIO_MEM_SBM_MB_OFFLINE:
		वापस NOTIFY_OK;
	शेष:
		अवरोध;
	पूर्ण
	dev_warn_ratelimited(&vm->vdev->dev,
			     "memory block onlining denied\n");
	वापस NOTIFY_BAD;
पूर्ण

अटल व्योम virtio_mem_sbm_notअगरy_offline(काष्ठा virtio_mem *vm,
					  अचिन्हित दीर्घ mb_id)
अणु
	चयन (virtio_mem_sbm_get_mb_state(vm, mb_id)) अणु
	हाल VIRTIO_MEM_SBM_MB_ONLINE_PARTIAL:
		virtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIRTIO_MEM_SBM_MB_OFFLINE_PARTIAL);
		अवरोध;
	हाल VIRTIO_MEM_SBM_MB_ONLINE:
		virtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIRTIO_MEM_SBM_MB_OFFLINE);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम virtio_mem_sbm_notअगरy_online(काष्ठा virtio_mem *vm,
					 अचिन्हित दीर्घ mb_id)
अणु
	चयन (virtio_mem_sbm_get_mb_state(vm, mb_id)) अणु
	हाल VIRTIO_MEM_SBM_MB_OFFLINE_PARTIAL:
		virtio_mem_sbm_set_mb_state(vm, mb_id,
					VIRTIO_MEM_SBM_MB_ONLINE_PARTIAL);
		अवरोध;
	हाल VIRTIO_MEM_SBM_MB_OFFLINE:
		virtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIRTIO_MEM_SBM_MB_ONLINE);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम virtio_mem_sbm_notअगरy_going_offline(काष्ठा virtio_mem *vm,
						अचिन्हित दीर्घ mb_id)
अणु
	स्थिर अचिन्हित दीर्घ nr_pages = PFN_DOWN(vm->sbm.sb_size);
	अचिन्हित दीर्घ pfn;
	पूर्णांक sb_id;

	क्रम (sb_id = 0; sb_id < vm->sbm.sbs_per_mb; sb_id++) अणु
		अगर (virtio_mem_sbm_test_sb_plugged(vm, mb_id, sb_id, 1))
			जारी;
		pfn = PFN_DOWN(virtio_mem_mb_id_to_phys(mb_id) +
			       sb_id * vm->sbm.sb_size);
		virtio_mem_fake_offline_going_offline(pfn, nr_pages);
	पूर्ण
पूर्ण

अटल व्योम virtio_mem_sbm_notअगरy_cancel_offline(काष्ठा virtio_mem *vm,
						 अचिन्हित दीर्घ mb_id)
अणु
	स्थिर अचिन्हित दीर्घ nr_pages = PFN_DOWN(vm->sbm.sb_size);
	अचिन्हित दीर्घ pfn;
	पूर्णांक sb_id;

	क्रम (sb_id = 0; sb_id < vm->sbm.sbs_per_mb; sb_id++) अणु
		अगर (virtio_mem_sbm_test_sb_plugged(vm, mb_id, sb_id, 1))
			जारी;
		pfn = PFN_DOWN(virtio_mem_mb_id_to_phys(mb_id) +
			       sb_id * vm->sbm.sb_size);
		virtio_mem_fake_offline_cancel_offline(pfn, nr_pages);
	पूर्ण
पूर्ण

अटल व्योम virtio_mem_bbm_notअगरy_going_offline(काष्ठा virtio_mem *vm,
						अचिन्हित दीर्घ bb_id,
						अचिन्हित दीर्घ pfn,
						अचिन्हित दीर्घ nr_pages)
अणु
	/*
	 * When marked as "fake-offline", all online memory of this device block
	 * is allocated by us. Otherwise, we करोn't have any memory allocated.
	 */
	अगर (virtio_mem_bbm_get_bb_state(vm, bb_id) !=
	    VIRTIO_MEM_BBM_BB_FAKE_OFFLINE)
		वापस;
	virtio_mem_fake_offline_going_offline(pfn, nr_pages);
पूर्ण

अटल व्योम virtio_mem_bbm_notअगरy_cancel_offline(काष्ठा virtio_mem *vm,
						 अचिन्हित दीर्घ bb_id,
						 अचिन्हित दीर्घ pfn,
						 अचिन्हित दीर्घ nr_pages)
अणु
	अगर (virtio_mem_bbm_get_bb_state(vm, bb_id) !=
	    VIRTIO_MEM_BBM_BB_FAKE_OFFLINE)
		वापस;
	virtio_mem_fake_offline_cancel_offline(pfn, nr_pages);
पूर्ण

/*
 * This callback will either be called synchronously from add_memory() or
 * asynchronously (e.g., triggered via user space). We have to be careful
 * with locking when calling add_memory().
 */
अटल पूर्णांक virtio_mem_memory_notअगरier_cb(काष्ठा notअगरier_block *nb,
					 अचिन्हित दीर्घ action, व्योम *arg)
अणु
	काष्ठा virtio_mem *vm = container_of(nb, काष्ठा virtio_mem,
					     memory_notअगरier);
	काष्ठा memory_notअगरy *mhp = arg;
	स्थिर अचिन्हित दीर्घ start = PFN_PHYS(mhp->start_pfn);
	स्थिर अचिन्हित दीर्घ size = PFN_PHYS(mhp->nr_pages);
	पूर्णांक rc = NOTIFY_OK;
	अचिन्हित दीर्घ id;

	अगर (!virtio_mem_overlaps_range(vm, start, size))
		वापस NOTIFY_DONE;

	अगर (vm->in_sbm) अणु
		id = virtio_mem_phys_to_mb_id(start);
		/*
		 * In SBM, we add memory in separate memory blocks - we expect
		 * it to be onlined/offlined in the same granularity. Bail out
		 * अगर this ever changes.
		 */
		अगर (WARN_ON_ONCE(size != memory_block_size_bytes() ||
				 !IS_ALIGNED(start, memory_block_size_bytes())))
			वापस NOTIFY_BAD;
	पूर्ण अन्यथा अणु
		id = virtio_mem_phys_to_bb_id(vm, start);
		/*
		 * In BBM, we only care about onlining/offlining happening
		 * within a single big block, we करोn't care about the
		 * actual granularity as we करोn't track inभागidual Linux
		 * memory blocks.
		 */
		अगर (WARN_ON_ONCE(id != virtio_mem_phys_to_bb_id(vm, start + size - 1)))
			वापस NOTIFY_BAD;
	पूर्ण

	/*
	 * Aव्योम circular locking lockdep warnings. We lock the mutex
	 * e.g., in MEM_GOING_ONLINE and unlock it in MEM_ONLINE. The
	 * blocking_notअगरier_call_chain() has it's own lock, which माला_लो unlocked
	 * between both notअगरier calls and will bail out. False positive.
	 */
	lockdep_off();

	चयन (action) अणु
	हाल MEM_GOING_OFFLINE:
		mutex_lock(&vm->hotplug_mutex);
		अगर (vm->removing) अणु
			rc = notअगरier_from_त्रुटि_सं(-EBUSY);
			mutex_unlock(&vm->hotplug_mutex);
			अवरोध;
		पूर्ण
		vm->hotplug_active = true;
		अगर (vm->in_sbm)
			virtio_mem_sbm_notअगरy_going_offline(vm, id);
		अन्यथा
			virtio_mem_bbm_notअगरy_going_offline(vm, id,
							    mhp->start_pfn,
							    mhp->nr_pages);
		अवरोध;
	हाल MEM_GOING_ONLINE:
		mutex_lock(&vm->hotplug_mutex);
		अगर (vm->removing) अणु
			rc = notअगरier_from_त्रुटि_सं(-EBUSY);
			mutex_unlock(&vm->hotplug_mutex);
			अवरोध;
		पूर्ण
		vm->hotplug_active = true;
		अगर (vm->in_sbm)
			rc = virtio_mem_sbm_notअगरy_going_online(vm, id);
		अवरोध;
	हाल MEM_OFFLINE:
		अगर (vm->in_sbm)
			virtio_mem_sbm_notअगरy_offline(vm, id);

		atomic64_add(size, &vm->offline_size);
		/*
		 * Trigger the workqueue. Now that we have some offline memory,
		 * maybe we can handle pending unplug requests.
		 */
		अगर (!unplug_online)
			virtio_mem_retry(vm);

		vm->hotplug_active = false;
		mutex_unlock(&vm->hotplug_mutex);
		अवरोध;
	हाल MEM_ONLINE:
		अगर (vm->in_sbm)
			virtio_mem_sbm_notअगरy_online(vm, id);

		atomic64_sub(size, &vm->offline_size);
		/*
		 * Start adding more memory once we onlined half of our
		 * threshold. Don't trigger if it's possibly due to our actipn
		 * (e.g., us adding memory which माला_लो onlined immediately from
		 * the core).
		 */
		अगर (!atomic_पढ़ो(&vm->wq_active) &&
		    virtio_mem_could_add_memory(vm, vm->offline_threshold / 2))
			virtio_mem_retry(vm);

		vm->hotplug_active = false;
		mutex_unlock(&vm->hotplug_mutex);
		अवरोध;
	हाल MEM_CANCEL_OFFLINE:
		अगर (!vm->hotplug_active)
			अवरोध;
		अगर (vm->in_sbm)
			virtio_mem_sbm_notअगरy_cancel_offline(vm, id);
		अन्यथा
			virtio_mem_bbm_notअगरy_cancel_offline(vm, id,
							     mhp->start_pfn,
							     mhp->nr_pages);
		vm->hotplug_active = false;
		mutex_unlock(&vm->hotplug_mutex);
		अवरोध;
	हाल MEM_CANCEL_ONLINE:
		अगर (!vm->hotplug_active)
			अवरोध;
		vm->hotplug_active = false;
		mutex_unlock(&vm->hotplug_mutex);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	lockdep_on();

	वापस rc;
पूर्ण

/*
 * Set a range of pages PG_offline. Remember pages that were never onlined
 * (via generic_online_page()) using PageDirty().
 */
अटल व्योम virtio_mem_set_fake_offline(अचिन्हित दीर्घ pfn,
					अचिन्हित दीर्घ nr_pages, bool onlined)
अणु
	क्रम (; nr_pages--; pfn++) अणु
		काष्ठा page *page = pfn_to_page(pfn);

		__SetPageOffline(page);
		अगर (!onlined) अणु
			SetPageDirty(page);
			/* FIXME: हटाओ after cleanups */
			ClearPageReserved(page);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Clear PG_offline from a range of pages. If the pages were never onlined,
 * (via generic_online_page()), clear PageDirty().
 */
अटल व्योम virtio_mem_clear_fake_offline(अचिन्हित दीर्घ pfn,
					  अचिन्हित दीर्घ nr_pages, bool onlined)
अणु
	क्रम (; nr_pages--; pfn++) अणु
		काष्ठा page *page = pfn_to_page(pfn);

		__ClearPageOffline(page);
		अगर (!onlined)
			ClearPageDirty(page);
	पूर्ण
पूर्ण

/*
 * Release a range of fake-offline pages to the buddy, effectively
 * fake-onlining them.
 */
अटल व्योम virtio_mem_fake_online(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages)
अणु
	स्थिर अचिन्हित दीर्घ max_nr_pages = MAX_ORDER_NR_PAGES;
	अचिन्हित दीर्घ i;

	/*
	 * We are always called at least with MAX_ORDER_NR_PAGES
	 * granularity/alignment (e.g., the way subblocks work). All pages
	 * inside such a block are alike.
	 */
	क्रम (i = 0; i < nr_pages; i += max_nr_pages) अणु
		काष्ठा page *page = pfn_to_page(pfn + i);

		/*
		 * If the page is PageDirty(), it was kept fake-offline when
		 * onlining the memory block. Otherwise, it was allocated
		 * using alloc_contig_range(). All pages in a subblock are
		 * alike.
		 */
		अगर (PageDirty(page)) अणु
			virtio_mem_clear_fake_offline(pfn + i, max_nr_pages,
						      false);
			generic_online_page(page, MAX_ORDER - 1);
		पूर्ण अन्यथा अणु
			virtio_mem_clear_fake_offline(pfn + i, max_nr_pages,
						      true);
			मुक्त_contig_range(pfn + i, max_nr_pages);
			adjust_managed_page_count(page, max_nr_pages);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Try to allocate a range, marking pages fake-offline, effectively
 * fake-offlining them.
 */
अटल पूर्णांक virtio_mem_fake_offline(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages)
अणु
	स्थिर bool is_movable = zone_idx(page_zone(pfn_to_page(pfn))) ==
				ZONE_MOVABLE;
	पूर्णांक rc, retry_count;

	/*
	 * TODO: We want an alloc_contig_range() mode that tries to allocate
	 * harder (e.g., dealing with temporarily pinned pages, PCP), especially
	 * with ZONE_MOVABLE. So क्रम now, retry a couple of बार with
	 * ZONE_MOVABLE beक्रमe giving up - because that zone is supposed to give
	 * some guarantees.
	 */
	क्रम (retry_count = 0; retry_count < 5; retry_count++) अणु
		rc = alloc_contig_range(pfn, pfn + nr_pages, MIGRATE_MOVABLE,
					GFP_KERNEL);
		अगर (rc == -ENOMEM)
			/* whoops, out of memory */
			वापस rc;
		अन्यथा अगर (rc && !is_movable)
			अवरोध;
		अन्यथा अगर (rc)
			जारी;

		virtio_mem_set_fake_offline(pfn, nr_pages, true);
		adjust_managed_page_count(pfn_to_page(pfn), -nr_pages);
		वापस 0;
	पूर्ण

	वापस -EBUSY;
पूर्ण

/*
 * Handle fake-offline pages when memory is going offline - such that the
 * pages can be skipped by mm-core when offlining.
 */
अटल व्योम virtio_mem_fake_offline_going_offline(अचिन्हित दीर्घ pfn,
						  अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ i;

	/*
	 * Drop our reference to the pages so the memory can get offlined
	 * and add the unplugged pages to the managed page counters (so
	 * offlining code can correctly subtract them again).
	 */
	adjust_managed_page_count(pfn_to_page(pfn), nr_pages);
	/* Drop our reference to the pages so the memory can get offlined. */
	क्रम (i = 0; i < nr_pages; i++) अणु
		page = pfn_to_page(pfn + i);
		अगर (WARN_ON(!page_ref_dec_and_test(page)))
			dump_page(page, "fake-offline page referenced");
	पूर्ण
पूर्ण

/*
 * Handle fake-offline pages when memory offlining is canceled - to unकरो
 * what we did in virtio_mem_fake_offline_going_offline().
 */
अटल व्योम virtio_mem_fake_offline_cancel_offline(अचिन्हित दीर्घ pfn,
						   अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ i;

	/*
	 * Get the reference we dropped when going offline and subtract the
	 * unplugged pages from the managed page counters.
	 */
	adjust_managed_page_count(pfn_to_page(pfn), -nr_pages);
	क्रम (i = 0; i < nr_pages; i++)
		page_ref_inc(pfn_to_page(pfn + i));
पूर्ण

अटल व्योम virtio_mem_online_page_cb(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	स्थिर अचिन्हित दीर्घ addr = page_to_phys(page);
	अचिन्हित दीर्घ id, sb_id;
	काष्ठा virtio_mem *vm;
	bool करो_online;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(vm, &virtio_mem_devices, next) अणु
		अगर (!virtio_mem_contains_range(vm, addr, PFN_PHYS(1 << order)))
			जारी;

		अगर (vm->in_sbm) अणु
			/*
			 * We exploit here that subblocks have at least
			 * MAX_ORDER_NR_PAGES size/alignment - so we cannot
			 * cross subblocks within one call.
			 */
			id = virtio_mem_phys_to_mb_id(addr);
			sb_id = virtio_mem_phys_to_sb_id(vm, addr);
			करो_online = virtio_mem_sbm_test_sb_plugged(vm, id,
								   sb_id, 1);
		पूर्ण अन्यथा अणु
			/*
			 * If the whole block is marked fake offline, keep
			 * everything that way.
			 */
			id = virtio_mem_phys_to_bb_id(vm, addr);
			करो_online = virtio_mem_bbm_get_bb_state(vm, id) !=
				    VIRTIO_MEM_BBM_BB_FAKE_OFFLINE;
		पूर्ण
		अगर (करो_online)
			generic_online_page(page, order);
		अन्यथा
			virtio_mem_set_fake_offline(PFN_DOWN(addr), 1 << order,
						    false);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	rcu_पढ़ो_unlock();

	/* not virtio-mem memory, but e.g., a DIMM. online it */
	generic_online_page(page, order);
पूर्ण

अटल uपूर्णांक64_t virtio_mem_send_request(काष्ठा virtio_mem *vm,
					स्थिर काष्ठा virtio_mem_req *req)
अणु
	काष्ठा scatterlist *sgs[2], sg_req, sg_resp;
	अचिन्हित पूर्णांक len;
	पूर्णांक rc;

	/* करोn't use the request residing on the stack (vaddr) */
	vm->req = *req;

	/* out: buffer क्रम request */
	sg_init_one(&sg_req, &vm->req, माप(vm->req));
	sgs[0] = &sg_req;

	/* in: buffer क्रम response */
	sg_init_one(&sg_resp, &vm->resp, माप(vm->resp));
	sgs[1] = &sg_resp;

	rc = virtqueue_add_sgs(vm->vq, sgs, 1, 1, vm, GFP_KERNEL);
	अगर (rc < 0)
		वापस rc;

	virtqueue_kick(vm->vq);

	/* रुको क्रम a response */
	रुको_event(vm->host_resp, virtqueue_get_buf(vm->vq, &len));

	वापस virtio16_to_cpu(vm->vdev, vm->resp.type);
पूर्ण

अटल पूर्णांक virtio_mem_send_plug_request(काष्ठा virtio_mem *vm, uपूर्णांक64_t addr,
					uपूर्णांक64_t size)
अणु
	स्थिर uपूर्णांक64_t nb_vm_blocks = size / vm->device_block_size;
	स्थिर काष्ठा virtio_mem_req req = अणु
		.type = cpu_to_virtio16(vm->vdev, VIRTIO_MEM_REQ_PLUG),
		.u.plug.addr = cpu_to_virtio64(vm->vdev, addr),
		.u.plug.nb_blocks = cpu_to_virtio16(vm->vdev, nb_vm_blocks),
	पूर्ण;
	पूर्णांक rc = -ENOMEM;

	अगर (atomic_पढ़ो(&vm->config_changed))
		वापस -EAGAIN;

	dev_dbg(&vm->vdev->dev, "plugging memory: 0x%llx - 0x%llx\n", addr,
		addr + size - 1);

	चयन (virtio_mem_send_request(vm, &req)) अणु
	हाल VIRTIO_MEM_RESP_ACK:
		vm->plugged_size += size;
		वापस 0;
	हाल VIRTIO_MEM_RESP_NACK:
		rc = -EAGAIN;
		अवरोध;
	हाल VIRTIO_MEM_RESP_BUSY:
		rc = -ETXTBSY;
		अवरोध;
	हाल VIRTIO_MEM_RESP_ERROR:
		rc = -EINVAL;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dev_dbg(&vm->vdev->dev, "plugging memory failed: %d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक virtio_mem_send_unplug_request(काष्ठा virtio_mem *vm, uपूर्णांक64_t addr,
					  uपूर्णांक64_t size)
अणु
	स्थिर uपूर्णांक64_t nb_vm_blocks = size / vm->device_block_size;
	स्थिर काष्ठा virtio_mem_req req = अणु
		.type = cpu_to_virtio16(vm->vdev, VIRTIO_MEM_REQ_UNPLUG),
		.u.unplug.addr = cpu_to_virtio64(vm->vdev, addr),
		.u.unplug.nb_blocks = cpu_to_virtio16(vm->vdev, nb_vm_blocks),
	पूर्ण;
	पूर्णांक rc = -ENOMEM;

	अगर (atomic_पढ़ो(&vm->config_changed))
		वापस -EAGAIN;

	dev_dbg(&vm->vdev->dev, "unplugging memory: 0x%llx - 0x%llx\n", addr,
		addr + size - 1);

	चयन (virtio_mem_send_request(vm, &req)) अणु
	हाल VIRTIO_MEM_RESP_ACK:
		vm->plugged_size -= size;
		वापस 0;
	हाल VIRTIO_MEM_RESP_BUSY:
		rc = -ETXTBSY;
		अवरोध;
	हाल VIRTIO_MEM_RESP_ERROR:
		rc = -EINVAL;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dev_dbg(&vm->vdev->dev, "unplugging memory failed: %d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक virtio_mem_send_unplug_all_request(काष्ठा virtio_mem *vm)
अणु
	स्थिर काष्ठा virtio_mem_req req = अणु
		.type = cpu_to_virtio16(vm->vdev, VIRTIO_MEM_REQ_UNPLUG_ALL),
	पूर्ण;
	पूर्णांक rc = -ENOMEM;

	dev_dbg(&vm->vdev->dev, "unplugging all memory");

	चयन (virtio_mem_send_request(vm, &req)) अणु
	हाल VIRTIO_MEM_RESP_ACK:
		vm->unplug_all_required = false;
		vm->plugged_size = 0;
		/* usable region might have shrunk */
		atomic_set(&vm->config_changed, 1);
		वापस 0;
	हाल VIRTIO_MEM_RESP_BUSY:
		rc = -ETXTBSY;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dev_dbg(&vm->vdev->dev, "unplugging all memory failed: %d\n", rc);
	वापस rc;
पूर्ण

/*
 * Plug selected subblocks. Updates the plugged state, but not the state
 * of the memory block.
 */
अटल पूर्णांक virtio_mem_sbm_plug_sb(काष्ठा virtio_mem *vm, अचिन्हित दीर्घ mb_id,
				  पूर्णांक sb_id, पूर्णांक count)
अणु
	स्थिर uपूर्णांक64_t addr = virtio_mem_mb_id_to_phys(mb_id) +
			      sb_id * vm->sbm.sb_size;
	स्थिर uपूर्णांक64_t size = count * vm->sbm.sb_size;
	पूर्णांक rc;

	rc = virtio_mem_send_plug_request(vm, addr, size);
	अगर (!rc)
		virtio_mem_sbm_set_sb_plugged(vm, mb_id, sb_id, count);
	वापस rc;
पूर्ण

/*
 * Unplug selected subblocks. Updates the plugged state, but not the state
 * of the memory block.
 */
अटल पूर्णांक virtio_mem_sbm_unplug_sb(काष्ठा virtio_mem *vm, अचिन्हित दीर्घ mb_id,
				    पूर्णांक sb_id, पूर्णांक count)
अणु
	स्थिर uपूर्णांक64_t addr = virtio_mem_mb_id_to_phys(mb_id) +
			      sb_id * vm->sbm.sb_size;
	स्थिर uपूर्णांक64_t size = count * vm->sbm.sb_size;
	पूर्णांक rc;

	rc = virtio_mem_send_unplug_request(vm, addr, size);
	अगर (!rc)
		virtio_mem_sbm_set_sb_unplugged(vm, mb_id, sb_id, count);
	वापस rc;
पूर्ण

/*
 * Request to unplug a big block.
 *
 * Will not modअगरy the state of the big block.
 */
अटल पूर्णांक virtio_mem_bbm_unplug_bb(काष्ठा virtio_mem *vm, अचिन्हित दीर्घ bb_id)
अणु
	स्थिर uपूर्णांक64_t addr = virtio_mem_bb_id_to_phys(vm, bb_id);
	स्थिर uपूर्णांक64_t size = vm->bbm.bb_size;

	वापस virtio_mem_send_unplug_request(vm, addr, size);
पूर्ण

/*
 * Request to plug a big block.
 *
 * Will not modअगरy the state of the big block.
 */
अटल पूर्णांक virtio_mem_bbm_plug_bb(काष्ठा virtio_mem *vm, अचिन्हित दीर्घ bb_id)
अणु
	स्थिर uपूर्णांक64_t addr = virtio_mem_bb_id_to_phys(vm, bb_id);
	स्थिर uपूर्णांक64_t size = vm->bbm.bb_size;

	वापस virtio_mem_send_plug_request(vm, addr, size);
पूर्ण

/*
 * Unplug the desired number of plugged subblocks of a offline or not-added
 * memory block. Will fail अगर any subblock cannot get unplugged (instead of
 * skipping it).
 *
 * Will not modअगरy the state of the memory block.
 *
 * Note: can fail after some subblocks were unplugged.
 */
अटल पूर्णांक virtio_mem_sbm_unplug_any_sb(काष्ठा virtio_mem *vm,
					अचिन्हित दीर्घ mb_id, uपूर्णांक64_t *nb_sb)
अणु
	पूर्णांक sb_id, count;
	पूर्णांक rc;

	sb_id = vm->sbm.sbs_per_mb - 1;
	जबतक (*nb_sb) अणु
		/* Find the next candidate subblock */
		जबतक (sb_id >= 0 &&
		       virtio_mem_sbm_test_sb_unplugged(vm, mb_id, sb_id, 1))
			sb_id--;
		अगर (sb_id < 0)
			अवरोध;
		/* Try to unplug multiple subblocks at a समय */
		count = 1;
		जबतक (count < *nb_sb && sb_id > 0 &&
		       virtio_mem_sbm_test_sb_plugged(vm, mb_id, sb_id - 1, 1)) अणु
			count++;
			sb_id--;
		पूर्ण

		rc = virtio_mem_sbm_unplug_sb(vm, mb_id, sb_id, count);
		अगर (rc)
			वापस rc;
		*nb_sb -= count;
		sb_id--;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Unplug all plugged subblocks of an offline or not-added memory block.
 *
 * Will not modअगरy the state of the memory block.
 *
 * Note: can fail after some subblocks were unplugged.
 */
अटल पूर्णांक virtio_mem_sbm_unplug_mb(काष्ठा virtio_mem *vm, अचिन्हित दीर्घ mb_id)
अणु
	uपूर्णांक64_t nb_sb = vm->sbm.sbs_per_mb;

	वापस virtio_mem_sbm_unplug_any_sb(vm, mb_id, &nb_sb);
पूर्ण

/*
 * Prepare tracking data क्रम the next memory block.
 */
अटल पूर्णांक virtio_mem_sbm_prepare_next_mb(काष्ठा virtio_mem *vm,
					  अचिन्हित दीर्घ *mb_id)
अणु
	पूर्णांक rc;

	अगर (vm->sbm.next_mb_id > vm->sbm.last_usable_mb_id)
		वापस -ENOSPC;

	/* Resize the state array अगर required. */
	rc = virtio_mem_sbm_mb_states_prepare_next_mb(vm);
	अगर (rc)
		वापस rc;

	/* Resize the subblock biपंचांगap अगर required. */
	rc = virtio_mem_sbm_sb_states_prepare_next_mb(vm);
	अगर (rc)
		वापस rc;

	vm->sbm.mb_count[VIRTIO_MEM_SBM_MB_UNUSED]++;
	*mb_id = vm->sbm.next_mb_id++;
	वापस 0;
पूर्ण

/*
 * Try to plug the desired number of subblocks and add the memory block
 * to Linux.
 *
 * Will modअगरy the state of the memory block.
 */
अटल पूर्णांक virtio_mem_sbm_plug_and_add_mb(काष्ठा virtio_mem *vm,
					  अचिन्हित दीर्घ mb_id, uपूर्णांक64_t *nb_sb)
अणु
	स्थिर पूर्णांक count = min_t(पूर्णांक, *nb_sb, vm->sbm.sbs_per_mb);
	पूर्णांक rc;

	अगर (WARN_ON_ONCE(!count))
		वापस -EINVAL;

	/*
	 * Plug the requested number of subblocks beक्रमe adding it to linux,
	 * so that onlining will directly online all plugged subblocks.
	 */
	rc = virtio_mem_sbm_plug_sb(vm, mb_id, 0, count);
	अगर (rc)
		वापस rc;

	/*
	 * Mark the block properly offline beक्रमe adding it to Linux,
	 * so the memory notअगरiers will find the block in the right state.
	 */
	अगर (count == vm->sbm.sbs_per_mb)
		virtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIRTIO_MEM_SBM_MB_OFFLINE);
	अन्यथा
		virtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIRTIO_MEM_SBM_MB_OFFLINE_PARTIAL);

	/* Add the memory block to linux - अगर that fails, try to unplug. */
	rc = virtio_mem_sbm_add_mb(vm, mb_id);
	अगर (rc) अणु
		पूर्णांक new_state = VIRTIO_MEM_SBM_MB_UNUSED;

		अगर (virtio_mem_sbm_unplug_sb(vm, mb_id, 0, count))
			new_state = VIRTIO_MEM_SBM_MB_PLUGGED;
		virtio_mem_sbm_set_mb_state(vm, mb_id, new_state);
		वापस rc;
	पूर्ण

	*nb_sb -= count;
	वापस 0;
पूर्ण

/*
 * Try to plug the desired number of subblocks of a memory block that
 * is alपढ़ोy added to Linux.
 *
 * Will modअगरy the state of the memory block.
 *
 * Note: Can fail after some subblocks were successfully plugged.
 */
अटल पूर्णांक virtio_mem_sbm_plug_any_sb(काष्ठा virtio_mem *vm,
				      अचिन्हित दीर्घ mb_id, uपूर्णांक64_t *nb_sb,
				      bool online)
अणु
	अचिन्हित दीर्घ pfn, nr_pages;
	पूर्णांक sb_id, count;
	पूर्णांक rc;

	अगर (WARN_ON_ONCE(!*nb_sb))
		वापस -EINVAL;

	जबतक (*nb_sb) अणु
		sb_id = virtio_mem_sbm_first_unplugged_sb(vm, mb_id);
		अगर (sb_id >= vm->sbm.sbs_per_mb)
			अवरोध;
		count = 1;
		जबतक (count < *nb_sb &&
		       sb_id + count < vm->sbm.sbs_per_mb &&
		       !virtio_mem_sbm_test_sb_plugged(vm, mb_id, sb_id + count, 1))
			count++;

		rc = virtio_mem_sbm_plug_sb(vm, mb_id, sb_id, count);
		अगर (rc)
			वापस rc;
		*nb_sb -= count;
		अगर (!online)
			जारी;

		/* fake-online the pages अगर the memory block is online */
		pfn = PFN_DOWN(virtio_mem_mb_id_to_phys(mb_id) +
			       sb_id * vm->sbm.sb_size);
		nr_pages = PFN_DOWN(count * vm->sbm.sb_size);
		virtio_mem_fake_online(pfn, nr_pages);
	पूर्ण

	अगर (virtio_mem_sbm_test_sb_plugged(vm, mb_id, 0, vm->sbm.sbs_per_mb)) अणु
		अगर (online)
			virtio_mem_sbm_set_mb_state(vm, mb_id,
						    VIRTIO_MEM_SBM_MB_ONLINE);
		अन्यथा
			virtio_mem_sbm_set_mb_state(vm, mb_id,
						    VIRTIO_MEM_SBM_MB_OFFLINE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक virtio_mem_sbm_plug_request(काष्ठा virtio_mem *vm, uपूर्णांक64_t dअगरf)
अणु
	uपूर्णांक64_t nb_sb = dअगरf / vm->sbm.sb_size;
	अचिन्हित दीर्घ mb_id;
	पूर्णांक rc;

	अगर (!nb_sb)
		वापस 0;

	/* Don't race with onlining/offlining */
	mutex_lock(&vm->hotplug_mutex);

	/* Try to plug subblocks of partially plugged online blocks. */
	virtio_mem_sbm_क्रम_each_mb(vm, mb_id,
				   VIRTIO_MEM_SBM_MB_ONLINE_PARTIAL) अणु
		rc = virtio_mem_sbm_plug_any_sb(vm, mb_id, &nb_sb, true);
		अगर (rc || !nb_sb)
			जाओ out_unlock;
		cond_resched();
	पूर्ण

	/* Try to plug subblocks of partially plugged offline blocks. */
	virtio_mem_sbm_क्रम_each_mb(vm, mb_id,
				   VIRTIO_MEM_SBM_MB_OFFLINE_PARTIAL) अणु
		rc = virtio_mem_sbm_plug_any_sb(vm, mb_id, &nb_sb, false);
		अगर (rc || !nb_sb)
			जाओ out_unlock;
		cond_resched();
	पूर्ण

	/*
	 * We won't be working on online/offline memory blocks from this poपूर्णांक,
	 * so we can't race with memory onlining/offlining. Drop the mutex.
	 */
	mutex_unlock(&vm->hotplug_mutex);

	/* Try to plug and add unused blocks */
	virtio_mem_sbm_क्रम_each_mb(vm, mb_id, VIRTIO_MEM_SBM_MB_UNUSED) अणु
		अगर (!virtio_mem_could_add_memory(vm, memory_block_size_bytes()))
			वापस -ENOSPC;

		rc = virtio_mem_sbm_plug_and_add_mb(vm, mb_id, &nb_sb);
		अगर (rc || !nb_sb)
			वापस rc;
		cond_resched();
	पूर्ण

	/* Try to prepare, plug and add new blocks */
	जबतक (nb_sb) अणु
		अगर (!virtio_mem_could_add_memory(vm, memory_block_size_bytes()))
			वापस -ENOSPC;

		rc = virtio_mem_sbm_prepare_next_mb(vm, &mb_id);
		अगर (rc)
			वापस rc;
		rc = virtio_mem_sbm_plug_and_add_mb(vm, mb_id, &nb_sb);
		अगर (rc)
			वापस rc;
		cond_resched();
	पूर्ण

	वापस 0;
out_unlock:
	mutex_unlock(&vm->hotplug_mutex);
	वापस rc;
पूर्ण

/*
 * Plug a big block and add it to Linux.
 *
 * Will modअगरy the state of the big block.
 */
अटल पूर्णांक virtio_mem_bbm_plug_and_add_bb(काष्ठा virtio_mem *vm,
					  अचिन्हित दीर्घ bb_id)
अणु
	पूर्णांक rc;

	अगर (WARN_ON_ONCE(virtio_mem_bbm_get_bb_state(vm, bb_id) !=
			 VIRTIO_MEM_BBM_BB_UNUSED))
		वापस -EINVAL;

	rc = virtio_mem_bbm_plug_bb(vm, bb_id);
	अगर (rc)
		वापस rc;
	virtio_mem_bbm_set_bb_state(vm, bb_id, VIRTIO_MEM_BBM_BB_ADDED);

	rc = virtio_mem_bbm_add_bb(vm, bb_id);
	अगर (rc) अणु
		अगर (!virtio_mem_bbm_unplug_bb(vm, bb_id))
			virtio_mem_bbm_set_bb_state(vm, bb_id,
						    VIRTIO_MEM_BBM_BB_UNUSED);
		अन्यथा
			/* Retry from the मुख्य loop. */
			virtio_mem_bbm_set_bb_state(vm, bb_id,
						    VIRTIO_MEM_BBM_BB_PLUGGED);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Prepare tracking data क्रम the next big block.
 */
अटल पूर्णांक virtio_mem_bbm_prepare_next_bb(काष्ठा virtio_mem *vm,
					  अचिन्हित दीर्घ *bb_id)
अणु
	पूर्णांक rc;

	अगर (vm->bbm.next_bb_id > vm->bbm.last_usable_bb_id)
		वापस -ENOSPC;

	/* Resize the big block state array अगर required. */
	rc = virtio_mem_bbm_bb_states_prepare_next_bb(vm);
	अगर (rc)
		वापस rc;

	vm->bbm.bb_count[VIRTIO_MEM_BBM_BB_UNUSED]++;
	*bb_id = vm->bbm.next_bb_id;
	vm->bbm.next_bb_id++;
	वापस 0;
पूर्ण

अटल पूर्णांक virtio_mem_bbm_plug_request(काष्ठा virtio_mem *vm, uपूर्णांक64_t dअगरf)
अणु
	uपूर्णांक64_t nb_bb = dअगरf / vm->bbm.bb_size;
	अचिन्हित दीर्घ bb_id;
	पूर्णांक rc;

	अगर (!nb_bb)
		वापस 0;

	/* Try to plug and add unused big blocks */
	virtio_mem_bbm_क्रम_each_bb(vm, bb_id, VIRTIO_MEM_BBM_BB_UNUSED) अणु
		अगर (!virtio_mem_could_add_memory(vm, vm->bbm.bb_size))
			वापस -ENOSPC;

		rc = virtio_mem_bbm_plug_and_add_bb(vm, bb_id);
		अगर (!rc)
			nb_bb--;
		अगर (rc || !nb_bb)
			वापस rc;
		cond_resched();
	पूर्ण

	/* Try to prepare, plug and add new big blocks */
	जबतक (nb_bb) अणु
		अगर (!virtio_mem_could_add_memory(vm, vm->bbm.bb_size))
			वापस -ENOSPC;

		rc = virtio_mem_bbm_prepare_next_bb(vm, &bb_id);
		अगर (rc)
			वापस rc;
		rc = virtio_mem_bbm_plug_and_add_bb(vm, bb_id);
		अगर (!rc)
			nb_bb--;
		अगर (rc)
			वापस rc;
		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Try to plug the requested amount of memory.
 */
अटल पूर्णांक virtio_mem_plug_request(काष्ठा virtio_mem *vm, uपूर्णांक64_t dअगरf)
अणु
	अगर (vm->in_sbm)
		वापस virtio_mem_sbm_plug_request(vm, dअगरf);
	वापस virtio_mem_bbm_plug_request(vm, dअगरf);
पूर्ण

/*
 * Unplug the desired number of plugged subblocks of an offline memory block.
 * Will fail अगर any subblock cannot get unplugged (instead of skipping it).
 *
 * Will modअगरy the state of the memory block. Might temporarily drop the
 * hotplug_mutex.
 *
 * Note: Can fail after some subblocks were successfully unplugged.
 */
अटल पूर्णांक virtio_mem_sbm_unplug_any_sb_offline(काष्ठा virtio_mem *vm,
						अचिन्हित दीर्घ mb_id,
						uपूर्णांक64_t *nb_sb)
अणु
	पूर्णांक rc;

	rc = virtio_mem_sbm_unplug_any_sb(vm, mb_id, nb_sb);

	/* some subblocks might have been unplugged even on failure */
	अगर (!virtio_mem_sbm_test_sb_plugged(vm, mb_id, 0, vm->sbm.sbs_per_mb))
		virtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIRTIO_MEM_SBM_MB_OFFLINE_PARTIAL);
	अगर (rc)
		वापस rc;

	अगर (virtio_mem_sbm_test_sb_unplugged(vm, mb_id, 0, vm->sbm.sbs_per_mb)) अणु
		/*
		 * Remove the block from Linux - this should never fail.
		 * Hinder the block from getting onlined by marking it
		 * unplugged. Temporarily drop the mutex, so
		 * any pending GOING_ONLINE requests can be serviced/rejected.
		 */
		virtio_mem_sbm_set_mb_state(vm, mb_id,
					    VIRTIO_MEM_SBM_MB_UNUSED);

		mutex_unlock(&vm->hotplug_mutex);
		rc = virtio_mem_sbm_हटाओ_mb(vm, mb_id);
		BUG_ON(rc);
		mutex_lock(&vm->hotplug_mutex);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Unplug the given plugged subblocks of an online memory block.
 *
 * Will modअगरy the state of the memory block.
 */
अटल पूर्णांक virtio_mem_sbm_unplug_sb_online(काष्ठा virtio_mem *vm,
					   अचिन्हित दीर्घ mb_id, पूर्णांक sb_id,
					   पूर्णांक count)
अणु
	स्थिर अचिन्हित दीर्घ nr_pages = PFN_DOWN(vm->sbm.sb_size) * count;
	अचिन्हित दीर्घ start_pfn;
	पूर्णांक rc;

	start_pfn = PFN_DOWN(virtio_mem_mb_id_to_phys(mb_id) +
			     sb_id * vm->sbm.sb_size);

	rc = virtio_mem_fake_offline(start_pfn, nr_pages);
	अगर (rc)
		वापस rc;

	/* Try to unplug the allocated memory */
	rc = virtio_mem_sbm_unplug_sb(vm, mb_id, sb_id, count);
	अगर (rc) अणु
		/* Return the memory to the buddy. */
		virtio_mem_fake_online(start_pfn, nr_pages);
		वापस rc;
	पूर्ण

	virtio_mem_sbm_set_mb_state(vm, mb_id,
				    VIRTIO_MEM_SBM_MB_ONLINE_PARTIAL);
	वापस 0;
पूर्ण

/*
 * Unplug the desired number of plugged subblocks of an online memory block.
 * Will skip subblock that are busy.
 *
 * Will modअगरy the state of the memory block. Might temporarily drop the
 * hotplug_mutex.
 *
 * Note: Can fail after some subblocks were successfully unplugged. Can
 *       वापस 0 even अगर subblocks were busy and could not get unplugged.
 */
अटल पूर्णांक virtio_mem_sbm_unplug_any_sb_online(काष्ठा virtio_mem *vm,
					       अचिन्हित दीर्घ mb_id,
					       uपूर्णांक64_t *nb_sb)
अणु
	पूर्णांक rc, sb_id;

	/* If possible, try to unplug the complete block in one shot. */
	अगर (*nb_sb >= vm->sbm.sbs_per_mb &&
	    virtio_mem_sbm_test_sb_plugged(vm, mb_id, 0, vm->sbm.sbs_per_mb)) अणु
		rc = virtio_mem_sbm_unplug_sb_online(vm, mb_id, 0,
						     vm->sbm.sbs_per_mb);
		अगर (!rc) अणु
			*nb_sb -= vm->sbm.sbs_per_mb;
			जाओ unplugged;
		पूर्ण अन्यथा अगर (rc != -EBUSY)
			वापस rc;
	पूर्ण

	/* Fallback to single subblocks. */
	क्रम (sb_id = vm->sbm.sbs_per_mb - 1; sb_id >= 0 && *nb_sb; sb_id--) अणु
		/* Find the next candidate subblock */
		जबतक (sb_id >= 0 &&
		       !virtio_mem_sbm_test_sb_plugged(vm, mb_id, sb_id, 1))
			sb_id--;
		अगर (sb_id < 0)
			अवरोध;

		rc = virtio_mem_sbm_unplug_sb_online(vm, mb_id, sb_id, 1);
		अगर (rc == -EBUSY)
			जारी;
		अन्यथा अगर (rc)
			वापस rc;
		*nb_sb -= 1;
	पूर्ण

unplugged:
	/*
	 * Once all subblocks of a memory block were unplugged, offline and
	 * हटाओ it. This will usually not fail, as no memory is in use
	 * anymore - however some other notअगरiers might NACK the request.
	 */
	अगर (virtio_mem_sbm_test_sb_unplugged(vm, mb_id, 0, vm->sbm.sbs_per_mb)) अणु
		mutex_unlock(&vm->hotplug_mutex);
		rc = virtio_mem_sbm_offline_and_हटाओ_mb(vm, mb_id);
		mutex_lock(&vm->hotplug_mutex);
		अगर (!rc)
			virtio_mem_sbm_set_mb_state(vm, mb_id,
						    VIRTIO_MEM_SBM_MB_UNUSED);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक virtio_mem_sbm_unplug_request(काष्ठा virtio_mem *vm, uपूर्णांक64_t dअगरf)
अणु
	uपूर्णांक64_t nb_sb = dअगरf / vm->sbm.sb_size;
	अचिन्हित दीर्घ mb_id;
	पूर्णांक rc;

	अगर (!nb_sb)
		वापस 0;

	/*
	 * We'll drop the mutex a couple of बार when it is safe to करो so.
	 * This might result in some blocks चयनing the state (online/offline)
	 * and we could miss them in this run - we will retry again later.
	 */
	mutex_lock(&vm->hotplug_mutex);

	/* Try to unplug subblocks of partially plugged offline blocks. */
	virtio_mem_sbm_क्रम_each_mb_rev(vm, mb_id,
				       VIRTIO_MEM_SBM_MB_OFFLINE_PARTIAL) अणु
		rc = virtio_mem_sbm_unplug_any_sb_offline(vm, mb_id, &nb_sb);
		अगर (rc || !nb_sb)
			जाओ out_unlock;
		cond_resched();
	पूर्ण

	/* Try to unplug subblocks of plugged offline blocks. */
	virtio_mem_sbm_क्रम_each_mb_rev(vm, mb_id, VIRTIO_MEM_SBM_MB_OFFLINE) अणु
		rc = virtio_mem_sbm_unplug_any_sb_offline(vm, mb_id, &nb_sb);
		अगर (rc || !nb_sb)
			जाओ out_unlock;
		cond_resched();
	पूर्ण

	अगर (!unplug_online) अणु
		mutex_unlock(&vm->hotplug_mutex);
		वापस 0;
	पूर्ण

	/* Try to unplug subblocks of partially plugged online blocks. */
	virtio_mem_sbm_क्रम_each_mb_rev(vm, mb_id,
				       VIRTIO_MEM_SBM_MB_ONLINE_PARTIAL) अणु
		rc = virtio_mem_sbm_unplug_any_sb_online(vm, mb_id, &nb_sb);
		अगर (rc || !nb_sb)
			जाओ out_unlock;
		mutex_unlock(&vm->hotplug_mutex);
		cond_resched();
		mutex_lock(&vm->hotplug_mutex);
	पूर्ण

	/* Try to unplug subblocks of plugged online blocks. */
	virtio_mem_sbm_क्रम_each_mb_rev(vm, mb_id, VIRTIO_MEM_SBM_MB_ONLINE) अणु
		rc = virtio_mem_sbm_unplug_any_sb_online(vm, mb_id, &nb_sb);
		अगर (rc || !nb_sb)
			जाओ out_unlock;
		mutex_unlock(&vm->hotplug_mutex);
		cond_resched();
		mutex_lock(&vm->hotplug_mutex);
	पूर्ण

	mutex_unlock(&vm->hotplug_mutex);
	वापस nb_sb ? -EBUSY : 0;
out_unlock:
	mutex_unlock(&vm->hotplug_mutex);
	वापस rc;
पूर्ण

/*
 * Try to offline and हटाओ a big block from Linux and unplug it. Will fail
 * with -EBUSY अगर some memory is busy and cannot get unplugged.
 *
 * Will modअगरy the state of the memory block. Might temporarily drop the
 * hotplug_mutex.
 */
अटल पूर्णांक virtio_mem_bbm_offline_हटाओ_and_unplug_bb(काष्ठा virtio_mem *vm,
						       अचिन्हित दीर्घ bb_id)
अणु
	स्थिर अचिन्हित दीर्घ start_pfn = PFN_DOWN(virtio_mem_bb_id_to_phys(vm, bb_id));
	स्थिर अचिन्हित दीर्घ nr_pages = PFN_DOWN(vm->bbm.bb_size);
	अचिन्हित दीर्घ end_pfn = start_pfn + nr_pages;
	अचिन्हित दीर्घ pfn;
	काष्ठा page *page;
	पूर्णांक rc;

	अगर (WARN_ON_ONCE(virtio_mem_bbm_get_bb_state(vm, bb_id) !=
			 VIRTIO_MEM_BBM_BB_ADDED))
		वापस -EINVAL;

	अगर (bbm_safe_unplug) अणु
		/*
		 * Start by fake-offlining all memory. Once we marked the device
		 * block as fake-offline, all newly onlined memory will
		 * स्वतःmatically be kept fake-offline. Protect from concurrent
		 * onlining/offlining until we have a consistent state.
		 */
		mutex_lock(&vm->hotplug_mutex);
		virtio_mem_bbm_set_bb_state(vm, bb_id,
					    VIRTIO_MEM_BBM_BB_FAKE_OFFLINE);

		क्रम (pfn = start_pfn; pfn < end_pfn; pfn += PAGES_PER_SECTION) अणु
			page = pfn_to_online_page(pfn);
			अगर (!page)
				जारी;

			rc = virtio_mem_fake_offline(pfn, PAGES_PER_SECTION);
			अगर (rc) अणु
				end_pfn = pfn;
				जाओ rollback_safe_unplug;
			पूर्ण
		पूर्ण
		mutex_unlock(&vm->hotplug_mutex);
	पूर्ण

	rc = virtio_mem_bbm_offline_and_हटाओ_bb(vm, bb_id);
	अगर (rc) अणु
		अगर (bbm_safe_unplug) अणु
			mutex_lock(&vm->hotplug_mutex);
			जाओ rollback_safe_unplug;
		पूर्ण
		वापस rc;
	पूर्ण

	rc = virtio_mem_bbm_unplug_bb(vm, bb_id);
	अगर (rc)
		virtio_mem_bbm_set_bb_state(vm, bb_id,
					    VIRTIO_MEM_BBM_BB_PLUGGED);
	अन्यथा
		virtio_mem_bbm_set_bb_state(vm, bb_id,
					    VIRTIO_MEM_BBM_BB_UNUSED);
	वापस rc;

rollback_safe_unplug:
	क्रम (pfn = start_pfn; pfn < end_pfn; pfn += PAGES_PER_SECTION) अणु
		page = pfn_to_online_page(pfn);
		अगर (!page)
			जारी;
		virtio_mem_fake_online(pfn, PAGES_PER_SECTION);
	पूर्ण
	virtio_mem_bbm_set_bb_state(vm, bb_id, VIRTIO_MEM_BBM_BB_ADDED);
	mutex_unlock(&vm->hotplug_mutex);
	वापस rc;
पूर्ण

/*
 * Try to हटाओ a big block from Linux and unplug it. Will fail with
 * -EBUSY अगर some memory is online.
 *
 * Will modअगरy the state of the memory block.
 */
अटल पूर्णांक virtio_mem_bbm_हटाओ_and_unplug_bb(काष्ठा virtio_mem *vm,
					       अचिन्हित दीर्घ bb_id)
अणु
	पूर्णांक rc;

	अगर (WARN_ON_ONCE(virtio_mem_bbm_get_bb_state(vm, bb_id) !=
			 VIRTIO_MEM_BBM_BB_ADDED))
		वापस -EINVAL;

	rc = virtio_mem_bbm_हटाओ_bb(vm, bb_id);
	अगर (rc)
		वापस -EBUSY;

	rc = virtio_mem_bbm_unplug_bb(vm, bb_id);
	अगर (rc)
		virtio_mem_bbm_set_bb_state(vm, bb_id,
					    VIRTIO_MEM_BBM_BB_PLUGGED);
	अन्यथा
		virtio_mem_bbm_set_bb_state(vm, bb_id,
					    VIRTIO_MEM_BBM_BB_UNUSED);
	वापस rc;
पूर्ण

/*
 * Test अगर a big block is completely offline.
 */
अटल bool virtio_mem_bbm_bb_is_offline(काष्ठा virtio_mem *vm,
					 अचिन्हित दीर्घ bb_id)
अणु
	स्थिर अचिन्हित दीर्घ start_pfn = PFN_DOWN(virtio_mem_bb_id_to_phys(vm, bb_id));
	स्थिर अचिन्हित दीर्घ nr_pages = PFN_DOWN(vm->bbm.bb_size);
	अचिन्हित दीर्घ pfn;

	क्रम (pfn = start_pfn; pfn < start_pfn + nr_pages;
	     pfn += PAGES_PER_SECTION) अणु
		अगर (pfn_to_online_page(pfn))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक virtio_mem_bbm_unplug_request(काष्ठा virtio_mem *vm, uपूर्णांक64_t dअगरf)
अणु
	uपूर्णांक64_t nb_bb = dअगरf / vm->bbm.bb_size;
	uपूर्णांक64_t bb_id;
	पूर्णांक rc;

	अगर (!nb_bb)
		वापस 0;

	/* Try to unplug completely offline big blocks first. */
	virtio_mem_bbm_क्रम_each_bb_rev(vm, bb_id, VIRTIO_MEM_BBM_BB_ADDED) अणु
		cond_resched();
		/*
		 * As we're holding no locks, this check is racy as memory
		 * can get onlined in the meanसमय - but we'll fail gracefully.
		 */
		अगर (!virtio_mem_bbm_bb_is_offline(vm, bb_id))
			जारी;
		rc = virtio_mem_bbm_हटाओ_and_unplug_bb(vm, bb_id);
		अगर (rc == -EBUSY)
			जारी;
		अगर (!rc)
			nb_bb--;
		अगर (rc || !nb_bb)
			वापस rc;
	पूर्ण

	अगर (!unplug_online)
		वापस 0;

	/* Try to unplug any big blocks. */
	virtio_mem_bbm_क्रम_each_bb_rev(vm, bb_id, VIRTIO_MEM_BBM_BB_ADDED) अणु
		cond_resched();
		rc = virtio_mem_bbm_offline_हटाओ_and_unplug_bb(vm, bb_id);
		अगर (rc == -EBUSY)
			जारी;
		अगर (!rc)
			nb_bb--;
		अगर (rc || !nb_bb)
			वापस rc;
	पूर्ण

	वापस nb_bb ? -EBUSY : 0;
पूर्ण

/*
 * Try to unplug the requested amount of memory.
 */
अटल पूर्णांक virtio_mem_unplug_request(काष्ठा virtio_mem *vm, uपूर्णांक64_t dअगरf)
अणु
	अगर (vm->in_sbm)
		वापस virtio_mem_sbm_unplug_request(vm, dअगरf);
	वापस virtio_mem_bbm_unplug_request(vm, dअगरf);
पूर्ण

/*
 * Try to unplug all blocks that couldn't be unplugged beक्रमe, क्रम example,
 * because the hypervisor was busy.
 */
अटल पूर्णांक virtio_mem_unplug_pending_mb(काष्ठा virtio_mem *vm)
अणु
	अचिन्हित दीर्घ id;
	पूर्णांक rc;

	अगर (!vm->in_sbm) अणु
		virtio_mem_bbm_क्रम_each_bb(vm, id,
					   VIRTIO_MEM_BBM_BB_PLUGGED) अणु
			rc = virtio_mem_bbm_unplug_bb(vm, id);
			अगर (rc)
				वापस rc;
			virtio_mem_bbm_set_bb_state(vm, id,
						    VIRTIO_MEM_BBM_BB_UNUSED);
		पूर्ण
		वापस 0;
	पूर्ण

	virtio_mem_sbm_क्रम_each_mb(vm, id, VIRTIO_MEM_SBM_MB_PLUGGED) अणु
		rc = virtio_mem_sbm_unplug_mb(vm, id);
		अगर (rc)
			वापस rc;
		virtio_mem_sbm_set_mb_state(vm, id,
					    VIRTIO_MEM_SBM_MB_UNUSED);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Update all parts of the config that could have changed.
 */
अटल व्योम virtio_mem_refresh_config(काष्ठा virtio_mem *vm)
अणु
	स्थिर काष्ठा range pluggable_range = mhp_get_pluggable_range(true);
	uपूर्णांक64_t new_plugged_size, usable_region_size, end_addr;

	/* the plugged_size is just a reflection of what _we_ did previously */
	virtio_cपढ़ो_le(vm->vdev, काष्ठा virtio_mem_config, plugged_size,
			&new_plugged_size);
	अगर (WARN_ON_ONCE(new_plugged_size != vm->plugged_size))
		vm->plugged_size = new_plugged_size;

	/* calculate the last usable memory block id */
	virtio_cपढ़ो_le(vm->vdev, काष्ठा virtio_mem_config,
			usable_region_size, &usable_region_size);
	end_addr = min(vm->addr + usable_region_size - 1,
		       pluggable_range.end);

	अगर (vm->in_sbm) अणु
		vm->sbm.last_usable_mb_id = virtio_mem_phys_to_mb_id(end_addr);
		अगर (!IS_ALIGNED(end_addr + 1, memory_block_size_bytes()))
			vm->sbm.last_usable_mb_id--;
	पूर्ण अन्यथा अणु
		vm->bbm.last_usable_bb_id = virtio_mem_phys_to_bb_id(vm,
								     end_addr);
		अगर (!IS_ALIGNED(end_addr + 1, vm->bbm.bb_size))
			vm->bbm.last_usable_bb_id--;
	पूर्ण
	/*
	 * If we cannot plug any of our device memory (e.g., nothing in the
	 * usable region is addressable), the last usable memory block id will
	 * be smaller than the first usable memory block id. We'll stop
	 * attempting to add memory with -ENOSPC from our मुख्य loop.
	 */

	/* see अगर there is a request to change the size */
	virtio_cपढ़ो_le(vm->vdev, काष्ठा virtio_mem_config, requested_size,
			&vm->requested_size);

	dev_info(&vm->vdev->dev, "plugged size: 0x%llx", vm->plugged_size);
	dev_info(&vm->vdev->dev, "requested size: 0x%llx", vm->requested_size);
पूर्ण

/*
 * Workqueue function क्रम handling plug/unplug requests and config updates.
 */
अटल व्योम virtio_mem_run_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_mem *vm = container_of(work, काष्ठा virtio_mem, wq);
	uपूर्णांक64_t dअगरf;
	पूर्णांक rc;

	hrसमयr_cancel(&vm->retry_समयr);

	अगर (vm->broken)
		वापस;

	atomic_set(&vm->wq_active, 1);
retry:
	rc = 0;

	/* Make sure we start with a clean state अगर there are leftovers. */
	अगर (unlikely(vm->unplug_all_required))
		rc = virtio_mem_send_unplug_all_request(vm);

	अगर (atomic_पढ़ो(&vm->config_changed)) अणु
		atomic_set(&vm->config_changed, 0);
		virtio_mem_refresh_config(vm);
	पूर्ण

	/* Unplug any leftovers from previous runs */
	अगर (!rc)
		rc = virtio_mem_unplug_pending_mb(vm);

	अगर (!rc && vm->requested_size != vm->plugged_size) अणु
		अगर (vm->requested_size > vm->plugged_size) अणु
			dअगरf = vm->requested_size - vm->plugged_size;
			rc = virtio_mem_plug_request(vm, dअगरf);
		पूर्ण अन्यथा अणु
			dअगरf = vm->plugged_size - vm->requested_size;
			rc = virtio_mem_unplug_request(vm, dअगरf);
		पूर्ण
	पूर्ण

	चयन (rc) अणु
	हाल 0:
		vm->retry_समयr_ms = VIRTIO_MEM_RETRY_TIMER_MIN_MS;
		अवरोध;
	हाल -ENOSPC:
		/*
		 * We cannot add any more memory (alignment, physical limit)
		 * or we have too many offline memory blocks.
		 */
		अवरोध;
	हाल -ETXTBSY:
		/*
		 * The hypervisor cannot process our request right now
		 * (e.g., out of memory, migrating);
		 */
	हाल -EBUSY:
		/*
		 * We cannot मुक्त up any memory to unplug it (all plugged memory
		 * is busy).
		 */
	हाल -ENOMEM:
		/* Out of memory, try again later. */
		hrसमयr_start(&vm->retry_समयr, ms_to_kसमय(vm->retry_समयr_ms),
			      HRTIMER_MODE_REL);
		अवरोध;
	हाल -EAGAIN:
		/* Retry immediately (e.g., the config changed). */
		जाओ retry;
	शेष:
		/* Unknown error, mark as broken */
		dev_err(&vm->vdev->dev,
			"unknown error, marking device broken: %d\n", rc);
		vm->broken = true;
	पूर्ण

	atomic_set(&vm->wq_active, 0);
पूर्ण

अटल क्रमागत hrसमयr_restart virtio_mem_समयr_expired(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा virtio_mem *vm = container_of(समयr, काष्ठा virtio_mem,
					     retry_समयr);

	virtio_mem_retry(vm);
	vm->retry_समयr_ms = min_t(अचिन्हित पूर्णांक, vm->retry_समयr_ms * 2,
				   VIRTIO_MEM_RETRY_TIMER_MAX_MS);
	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम virtio_mem_handle_response(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_mem *vm = vq->vdev->priv;

	wake_up(&vm->host_resp);
पूर्ण

अटल पूर्णांक virtio_mem_init_vq(काष्ठा virtio_mem *vm)
अणु
	काष्ठा virtqueue *vq;

	vq = virtio_find_single_vq(vm->vdev, virtio_mem_handle_response,
				   "guest-request");
	अगर (IS_ERR(vq))
		वापस PTR_ERR(vq);
	vm->vq = vq;

	वापस 0;
पूर्ण

अटल पूर्णांक virtio_mem_init(काष्ठा virtio_mem *vm)
अणु
	स्थिर काष्ठा range pluggable_range = mhp_get_pluggable_range(true);
	uपूर्णांक64_t sb_size, addr;
	uपूर्णांक16_t node_id;

	अगर (!vm->vdev->config->get) अणु
		dev_err(&vm->vdev->dev, "config access disabled\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * We करोn't want to (un)plug or reuse any memory when in kdump. The
	 * memory is still accessible (but not mapped).
	 */
	अगर (is_kdump_kernel()) अणु
		dev_warn(&vm->vdev->dev, "disabled in kdump kernel\n");
		वापस -EBUSY;
	पूर्ण

	/* Fetch all properties that can't change. */
	virtio_cपढ़ो_le(vm->vdev, काष्ठा virtio_mem_config, plugged_size,
			&vm->plugged_size);
	virtio_cपढ़ो_le(vm->vdev, काष्ठा virtio_mem_config, block_size,
			&vm->device_block_size);
	virtio_cपढ़ो_le(vm->vdev, काष्ठा virtio_mem_config, node_id,
			&node_id);
	vm->nid = virtio_mem_translate_node_id(vm, node_id);
	virtio_cपढ़ो_le(vm->vdev, काष्ठा virtio_mem_config, addr, &vm->addr);
	virtio_cपढ़ो_le(vm->vdev, काष्ठा virtio_mem_config, region_size,
			&vm->region_size);

	/* Determine the nid क्रम the device based on the lowest address. */
	अगर (vm->nid == NUMA_NO_NODE)
		vm->nid = memory_add_physaddr_to_nid(vm->addr);

	/* bad device setup - warn only */
	अगर (!IS_ALIGNED(vm->addr, memory_block_size_bytes()))
		dev_warn(&vm->vdev->dev,
			 "The alignment of the physical start address can make some memory unusable.\n");
	अगर (!IS_ALIGNED(vm->addr + vm->region_size, memory_block_size_bytes()))
		dev_warn(&vm->vdev->dev,
			 "The alignment of the physical end address can make some memory unusable.\n");
	अगर (vm->addr < pluggable_range.start ||
	    vm->addr + vm->region_size - 1 > pluggable_range.end)
		dev_warn(&vm->vdev->dev,
			 "Some device memory is not addressable/pluggable. This can make some memory unusable.\n");

	/*
	 * We want subblocks to span at least MAX_ORDER_NR_PAGES and
	 * pageblock_nr_pages pages. This:
	 * - Simplअगरies our page onlining code (virtio_mem_online_page_cb)
	 *   and fake page onlining code (virtio_mem_fake_online).
	 * - Is required क्रम now क्रम alloc_contig_range() to work reliably -
	 *   it करोesn't properly handle smaller granularity on ZONE_NORMAL.
	 */
	sb_size = max_t(uपूर्णांक64_t, MAX_ORDER_NR_PAGES,
			pageblock_nr_pages) * PAGE_SIZE;
	sb_size = max_t(uपूर्णांक64_t, vm->device_block_size, sb_size);

	अगर (sb_size < memory_block_size_bytes() && !क्रमce_bbm) अणु
		/* SBM: At least two subblocks per Linux memory block. */
		vm->in_sbm = true;
		vm->sbm.sb_size = sb_size;
		vm->sbm.sbs_per_mb = memory_block_size_bytes() /
				     vm->sbm.sb_size;

		/* Round up to the next full memory block */
		addr = max_t(uपूर्णांक64_t, vm->addr, pluggable_range.start) +
		       memory_block_size_bytes() - 1;
		vm->sbm.first_mb_id = virtio_mem_phys_to_mb_id(addr);
		vm->sbm.next_mb_id = vm->sbm.first_mb_id;
	पूर्ण अन्यथा अणु
		/* BBM: At least one Linux memory block. */
		vm->bbm.bb_size = max_t(uपूर्णांक64_t, vm->device_block_size,
					memory_block_size_bytes());

		अगर (bbm_block_size) अणु
			अगर (!is_घातer_of_2(bbm_block_size)) अणु
				dev_warn(&vm->vdev->dev,
					 "bbm_block_size is not a power of 2");
			पूर्ण अन्यथा अगर (bbm_block_size < vm->bbm.bb_size) अणु
				dev_warn(&vm->vdev->dev,
					 "bbm_block_size is too small");
			पूर्ण अन्यथा अणु
				vm->bbm.bb_size = bbm_block_size;
			पूर्ण
		पूर्ण

		/* Round up to the next aligned big block */
		addr = max_t(uपूर्णांक64_t, vm->addr, pluggable_range.start) +
		       vm->bbm.bb_size - 1;
		vm->bbm.first_bb_id = virtio_mem_phys_to_bb_id(vm, addr);
		vm->bbm.next_bb_id = vm->bbm.first_bb_id;
	पूर्ण

	/* Prepare the offline threshold - make sure we can add two blocks. */
	vm->offline_threshold = max_t(uपूर्णांक64_t, 2 * memory_block_size_bytes(),
				      VIRTIO_MEM_DEFAULT_OFFLINE_THRESHOLD);
	/* In BBM, we also want at least two big blocks. */
	vm->offline_threshold = max_t(uपूर्णांक64_t, 2 * vm->bbm.bb_size,
				      vm->offline_threshold);

	dev_info(&vm->vdev->dev, "start address: 0x%llx", vm->addr);
	dev_info(&vm->vdev->dev, "region size: 0x%llx", vm->region_size);
	dev_info(&vm->vdev->dev, "device block size: 0x%llx",
		 (अचिन्हित दीर्घ दीर्घ)vm->device_block_size);
	dev_info(&vm->vdev->dev, "memory block size: 0x%lx",
		 memory_block_size_bytes());
	अगर (vm->in_sbm)
		dev_info(&vm->vdev->dev, "subblock size: 0x%llx",
			 (अचिन्हित दीर्घ दीर्घ)vm->sbm.sb_size);
	अन्यथा
		dev_info(&vm->vdev->dev, "big block size: 0x%llx",
			 (अचिन्हित दीर्घ दीर्घ)vm->bbm.bb_size);
	अगर (vm->nid != NUMA_NO_NODE && IS_ENABLED(CONFIG_NUMA))
		dev_info(&vm->vdev->dev, "nid: %d", vm->nid);

	वापस 0;
पूर्ण

अटल पूर्णांक virtio_mem_create_resource(काष्ठा virtio_mem *vm)
अणु
	/*
	 * When क्रमce-unloading the driver and removing the device, we
	 * could have a garbage poपूर्णांकer. Duplicate the string.
	 */
	स्थिर अक्षर *name = kstrdup(dev_name(&vm->vdev->dev), GFP_KERNEL);

	अगर (!name)
		वापस -ENOMEM;

	vm->parent_resource = __request_mem_region(vm->addr, vm->region_size,
						   name, IORESOURCE_SYSTEM_RAM);
	अगर (!vm->parent_resource) अणु
		kमुक्त(name);
		dev_warn(&vm->vdev->dev, "could not reserve device region\n");
		dev_info(&vm->vdev->dev,
			 "reloading the driver is not supported\n");
		वापस -EBUSY;
	पूर्ण

	/* The memory is not actually busy - make add_memory() work. */
	vm->parent_resource->flags &= ~IORESOURCE_BUSY;
	वापस 0;
पूर्ण

अटल व्योम virtio_mem_delete_resource(काष्ठा virtio_mem *vm)
अणु
	स्थिर अक्षर *name;

	अगर (!vm->parent_resource)
		वापस;

	name = vm->parent_resource->name;
	release_resource(vm->parent_resource);
	kमुक्त(vm->parent_resource);
	kमुक्त(name);
	vm->parent_resource = शून्य;
पूर्ण

अटल पूर्णांक virtio_mem_range_has_प्रणाली_ram(काष्ठा resource *res, व्योम *arg)
अणु
	वापस 1;
पूर्ण

अटल bool virtio_mem_has_memory_added(काष्ठा virtio_mem *vm)
अणु
	स्थिर अचिन्हित दीर्घ flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;

	वापस walk_iomem_res_desc(IORES_DESC_NONE, flags, vm->addr,
				   vm->addr + vm->region_size, शून्य,
				   virtio_mem_range_has_प्रणाली_ram) == 1;
पूर्ण

अटल पूर्णांक virtio_mem_probe(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_mem *vm;
	पूर्णांक rc;

	BUILD_BUG_ON(माप(काष्ठा virtio_mem_req) != 24);
	BUILD_BUG_ON(माप(काष्ठा virtio_mem_resp) != 10);

	vdev->priv = vm = kzalloc(माप(*vm), GFP_KERNEL);
	अगर (!vm)
		वापस -ENOMEM;

	init_रुकोqueue_head(&vm->host_resp);
	vm->vdev = vdev;
	INIT_WORK(&vm->wq, virtio_mem_run_wq);
	mutex_init(&vm->hotplug_mutex);
	INIT_LIST_HEAD(&vm->next);
	spin_lock_init(&vm->removal_lock);
	hrसमयr_init(&vm->retry_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	vm->retry_समयr.function = virtio_mem_समयr_expired;
	vm->retry_समयr_ms = VIRTIO_MEM_RETRY_TIMER_MIN_MS;

	/* रेजिस्टर the virtqueue */
	rc = virtio_mem_init_vq(vm);
	अगर (rc)
		जाओ out_मुक्त_vm;

	/* initialize the device by querying the config */
	rc = virtio_mem_init(vm);
	अगर (rc)
		जाओ out_del_vq;

	/* create the parent resource क्रम all memory */
	rc = virtio_mem_create_resource(vm);
	अगर (rc)
		जाओ out_del_vq;

	/*
	 * If we still have memory plugged, we have to unplug all memory first.
	 * Registering our parent resource makes sure that this memory isn't
	 * actually in use (e.g., trying to reload the driver).
	 */
	अगर (vm->plugged_size) अणु
		vm->unplug_all_required = true;
		dev_info(&vm->vdev->dev, "unplugging all memory is required\n");
	पूर्ण

	/* रेजिस्टर callbacks */
	vm->memory_notअगरier.notअगरier_call = virtio_mem_memory_notअगरier_cb;
	rc = रेजिस्टर_memory_notअगरier(&vm->memory_notअगरier);
	अगर (rc)
		जाओ out_del_resource;
	rc = रेजिस्टर_virtio_mem_device(vm);
	अगर (rc)
		जाओ out_unreg_mem;

	virtio_device_पढ़ोy(vdev);

	/* trigger a config update to start processing the requested_size */
	atomic_set(&vm->config_changed, 1);
	queue_work(प्रणाली_मुक्तzable_wq, &vm->wq);

	वापस 0;
out_unreg_mem:
	unरेजिस्टर_memory_notअगरier(&vm->memory_notअगरier);
out_del_resource:
	virtio_mem_delete_resource(vm);
out_del_vq:
	vdev->config->del_vqs(vdev);
out_मुक्त_vm:
	kमुक्त(vm);
	vdev->priv = शून्य;

	वापस rc;
पूर्ण

अटल व्योम virtio_mem_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_mem *vm = vdev->priv;
	अचिन्हित दीर्घ mb_id;
	पूर्णांक rc;

	/*
	 * Make sure the workqueue won't be triggered anymore and no memory
	 * blocks can be onlined/offlined until we're finished here.
	 */
	mutex_lock(&vm->hotplug_mutex);
	spin_lock_irq(&vm->removal_lock);
	vm->removing = true;
	spin_unlock_irq(&vm->removal_lock);
	mutex_unlock(&vm->hotplug_mutex);

	/* रुको until the workqueue stopped */
	cancel_work_sync(&vm->wq);
	hrसमयr_cancel(&vm->retry_समयr);

	अगर (vm->in_sbm) अणु
		/*
		 * After we unरेजिस्टरed our callbacks, user space can online
		 * partially plugged offline blocks. Make sure to हटाओ them.
		 */
		virtio_mem_sbm_क्रम_each_mb(vm, mb_id,
					   VIRTIO_MEM_SBM_MB_OFFLINE_PARTIAL) अणु
			rc = virtio_mem_sbm_हटाओ_mb(vm, mb_id);
			BUG_ON(rc);
			virtio_mem_sbm_set_mb_state(vm, mb_id,
						    VIRTIO_MEM_SBM_MB_UNUSED);
		पूर्ण
		/*
		 * After we unरेजिस्टरed our callbacks, user space can no दीर्घer
		 * offline partially plugged online memory blocks. No need to
		 * worry about them.
		 */
	पूर्ण

	/* unरेजिस्टर callbacks */
	unरेजिस्टर_virtio_mem_device(vm);
	unरेजिस्टर_memory_notअगरier(&vm->memory_notअगरier);

	/*
	 * There is no way we could reliably हटाओ all memory we have added to
	 * the प्रणाली. And there is no way to stop the driver/device from going
	 * away. Warn at least.
	 */
	अगर (virtio_mem_has_memory_added(vm)) अणु
		dev_warn(&vdev->dev, "device still has system memory added\n");
	पूर्ण अन्यथा अणु
		virtio_mem_delete_resource(vm);
		kमुक्त_स्थिर(vm->resource_name);
	पूर्ण

	/* हटाओ all tracking data - no locking needed */
	अगर (vm->in_sbm) अणु
		vमुक्त(vm->sbm.mb_states);
		vमुक्त(vm->sbm.sb_states);
	पूर्ण अन्यथा अणु
		vमुक्त(vm->bbm.bb_states);
	पूर्ण

	/* reset the device and cleanup the queues */
	vdev->config->reset(vdev);
	vdev->config->del_vqs(vdev);

	kमुक्त(vm);
	vdev->priv = शून्य;
पूर्ण

अटल व्योम virtio_mem_config_changed(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_mem *vm = vdev->priv;

	atomic_set(&vm->config_changed, 1);
	virtio_mem_retry(vm);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक virtio_mem_मुक्तze(काष्ठा virtio_device *vdev)
अणु
	/*
	 * When restarting the VM, all memory is usually unplugged. Don't
	 * allow to suspend/hibernate.
	 */
	dev_err(&vdev->dev, "save/restore not supported.\n");
	वापस -EPERM;
पूर्ण

अटल पूर्णांक virtio_mem_restore(काष्ठा virtio_device *vdev)
अणु
	वापस -EPERM;
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक virtio_mem_features[] = अणु
#अगर defined(CONFIG_NUMA) && defined(CONFIG_ACPI_NUMA)
	VIRTIO_MEM_F_ACPI_PXM,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा virtio_device_id virtio_mem_id_table[] = अणु
	अणु VIRTIO_ID_MEM, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा virtio_driver virtio_mem_driver = अणु
	.feature_table = virtio_mem_features,
	.feature_table_size = ARRAY_SIZE(virtio_mem_features),
	.driver.name = KBUILD_MODNAME,
	.driver.owner = THIS_MODULE,
	.id_table = virtio_mem_id_table,
	.probe = virtio_mem_probe,
	.हटाओ = virtio_mem_हटाओ,
	.config_changed = virtio_mem_config_changed,
#अगर_घोषित CONFIG_PM_SLEEP
	.मुक्तze	=	virtio_mem_मुक्तze,
	.restore =	virtio_mem_restore,
#पूर्ण_अगर
पूर्ण;

module_virtio_driver(virtio_mem_driver);
MODULE_DEVICE_TABLE(virtio, virtio_mem_id_table);
MODULE_AUTHOR("David Hildenbrand <david@redhat.com>");
MODULE_DESCRIPTION("Virtio-mem driver");
MODULE_LICENSE("GPL");
