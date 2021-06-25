<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __KVM_HOST_H
#घोषणा __KVM_HOST_H


#समावेश <linux/types.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/bug.h>
#समावेश <linux/minmax.h>
#समावेश <linux/mm.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/preempt.h>
#समावेश <linux/msi.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/err.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/irqbypass.h>
#समावेश <linux/rcuरुको.h>
#समावेश <linux/refcount.h>
#समावेश <linux/nospec.h>
#समावेश <यंत्र/संकेत.स>

#समावेश <linux/kvm.h>
#समावेश <linux/kvm_para.h>

#समावेश <linux/kvm_types.h>

#समावेश <यंत्र/kvm_host.h>
#समावेश <linux/kvm_dirty_ring.h>

#अगर_अघोषित KVM_MAX_VCPU_ID
#घोषणा KVM_MAX_VCPU_ID KVM_MAX_VCPUS
#पूर्ण_अगर

/*
 * The bit 16 ~ bit 31 of kvm_memory_region::flags are पूर्णांकernally used
 * in kvm, other bits are visible क्रम userspace which are defined in
 * include/linux/kvm_h.
 */
#घोषणा KVM_MEMSLOT_INVALID	(1UL << 16)

/*
 * Bit 63 of the memslot generation number is an "update in-progress flag",
 * e.g. is temporarily set क्रम the duration of install_new_memslots().
 * This flag effectively creates a unique generation number that is used to
 * mark cached memslot data, e.g. MMIO accesses, as potentially being stale,
 * i.e. may (or may not) have come from the previous memslots generation.
 *
 * This is necessary because the actual memslots update is not atomic with
 * respect to the generation number update.  Updating the generation number
 * first would allow a vCPU to cache a spte from the old memslots using the
 * new generation number, and updating the generation number after चयनing
 * to the new memslots would allow cache hits using the old generation number
 * to reference the defunct memslots.
 *
 * This mechanism is used to prevent getting hits in KVM's caches जबतक a
 * memslot update is in-progress, and to prevent cache hits *after* updating
 * the actual generation number against accesses that were inserted पूर्णांकo the
 * cache *beक्रमe* the memslots were updated.
 */
#घोषणा KVM_MEMSLOT_GEN_UPDATE_IN_PROGRESS	BIT_ULL(63)

/* Two fragments क्रम cross MMIO pages. */
#घोषणा KVM_MAX_MMIO_FRAGMENTS	2

#अगर_अघोषित KVM_ADDRESS_SPACE_NUM
#घोषणा KVM_ADDRESS_SPACE_NUM	1
#पूर्ण_अगर

/*
 * For the normal pfn, the highest 12 bits should be zero,
 * so we can mask bit 62 ~ bit 52  to indicate the error pfn,
 * mask bit 63 to indicate the noslot pfn.
 */
#घोषणा KVM_PFN_ERR_MASK	(0x7ffULL << 52)
#घोषणा KVM_PFN_ERR_NOSLOT_MASK	(0xfffULL << 52)
#घोषणा KVM_PFN_NOSLOT		(0x1ULL << 63)

#घोषणा KVM_PFN_ERR_FAULT	(KVM_PFN_ERR_MASK)
#घोषणा KVM_PFN_ERR_HWPOISON	(KVM_PFN_ERR_MASK + 1)
#घोषणा KVM_PFN_ERR_RO_FAULT	(KVM_PFN_ERR_MASK + 2)

/*
 * error pfns indicate that the gfn is in slot but faild to
 * translate it to pfn on host.
 */
अटल अंतरभूत bool is_error_pfn(kvm_pfn_t pfn)
अणु
	वापस !!(pfn & KVM_PFN_ERR_MASK);
पूर्ण

/*
 * error_noslot pfns indicate that the gfn can not be
 * translated to pfn - it is not in slot or failed to
 * translate it to pfn.
 */
अटल अंतरभूत bool is_error_noslot_pfn(kvm_pfn_t pfn)
अणु
	वापस !!(pfn & KVM_PFN_ERR_NOSLOT_MASK);
पूर्ण

/* noslot pfn indicates that the gfn is not in slot. */
अटल अंतरभूत bool is_noslot_pfn(kvm_pfn_t pfn)
अणु
	वापस pfn == KVM_PFN_NOSLOT;
पूर्ण

/*
 * architectures with KVM_HVA_ERR_BAD other than PAGE_OFFSET (e.g. s390)
 * provide own defines and kvm_is_error_hva
 */
#अगर_अघोषित KVM_HVA_ERR_BAD

#घोषणा KVM_HVA_ERR_BAD		(PAGE_OFFSET)
#घोषणा KVM_HVA_ERR_RO_BAD	(PAGE_OFFSET + PAGE_SIZE)

अटल अंतरभूत bool kvm_is_error_hva(अचिन्हित दीर्घ addr)
अणु
	वापस addr >= PAGE_OFFSET;
पूर्ण

#पूर्ण_अगर

#घोषणा KVM_ERR_PTR_BAD_PAGE	(ERR_PTR(-ENOENT))

अटल अंतरभूत bool is_error_page(काष्ठा page *page)
अणु
	वापस IS_ERR(page);
पूर्ण

#घोषणा KVM_REQUEST_MASK           GENMASK(7,0)
#घोषणा KVM_REQUEST_NO_WAKEUP      BIT(8)
#घोषणा KVM_REQUEST_WAIT           BIT(9)
/*
 * Architecture-independent vcpu->requests bit members
 * Bits 4-7 are reserved क्रम more arch-independent bits.
 */
#घोषणा KVM_REQ_TLB_FLUSH         (0 | KVM_REQUEST_WAIT | KVM_REQUEST_NO_WAKEUP)
#घोषणा KVM_REQ_MMU_RELOAD        (1 | KVM_REQUEST_WAIT | KVM_REQUEST_NO_WAKEUP)
#घोषणा KVM_REQ_UNBLOCK           2
#घोषणा KVM_REQ_UNHALT            3
#घोषणा KVM_REQUEST_ARCH_BASE     8

#घोषणा KVM_ARCH_REQ_FLAGS(nr, flags) (अणु \
	BUILD_BUG_ON((अचिन्हित)(nr) >= (माप_field(काष्ठा kvm_vcpu, requests) * 8) - KVM_REQUEST_ARCH_BASE); \
	(अचिन्हित)(((nr) + KVM_REQUEST_ARCH_BASE) | (flags)); \
पूर्ण)
#घोषणा KVM_ARCH_REQ(nr)           KVM_ARCH_REQ_FLAGS(nr, 0)

#घोषणा KVM_USERSPACE_IRQ_SOURCE_ID		0
#घोषणा KVM_IRQFD_RESAMPLE_IRQ_SOURCE_ID	1

बाह्य काष्ठा mutex kvm_lock;
बाह्य काष्ठा list_head vm_list;

काष्ठा kvm_io_range अणु
	gpa_t addr;
	पूर्णांक len;
	काष्ठा kvm_io_device *dev;
पूर्ण;

#घोषणा NR_IOBUS_DEVS 1000

काष्ठा kvm_io_bus अणु
	पूर्णांक dev_count;
	पूर्णांक ioeventfd_count;
	काष्ठा kvm_io_range range[];
पूर्ण;

क्रमागत kvm_bus अणु
	KVM_MMIO_BUS,
	KVM_PIO_BUS,
	KVM_VIRTIO_CCW_NOTIFY_BUS,
	KVM_FAST_MMIO_BUS,
	KVM_NR_BUSES
पूर्ण;

पूर्णांक kvm_io_bus_ग_लिखो(काष्ठा kvm_vcpu *vcpu, क्रमागत kvm_bus bus_idx, gpa_t addr,
		     पूर्णांक len, स्थिर व्योम *val);
पूर्णांक kvm_io_bus_ग_लिखो_cookie(काष्ठा kvm_vcpu *vcpu, क्रमागत kvm_bus bus_idx,
			    gpa_t addr, पूर्णांक len, स्थिर व्योम *val, दीर्घ cookie);
पूर्णांक kvm_io_bus_पढ़ो(काष्ठा kvm_vcpu *vcpu, क्रमागत kvm_bus bus_idx, gpa_t addr,
		    पूर्णांक len, व्योम *val);
पूर्णांक kvm_io_bus_रेजिस्टर_dev(काष्ठा kvm *kvm, क्रमागत kvm_bus bus_idx, gpa_t addr,
			    पूर्णांक len, काष्ठा kvm_io_device *dev);
पूर्णांक kvm_io_bus_unरेजिस्टर_dev(काष्ठा kvm *kvm, क्रमागत kvm_bus bus_idx,
			      काष्ठा kvm_io_device *dev);
काष्ठा kvm_io_device *kvm_io_bus_get_dev(काष्ठा kvm *kvm, क्रमागत kvm_bus bus_idx,
					 gpa_t addr);

#अगर_घोषित CONFIG_KVM_ASYNC_PF
काष्ठा kvm_async_pf अणु
	काष्ठा work_काष्ठा work;
	काष्ठा list_head link;
	काष्ठा list_head queue;
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा mm_काष्ठा *mm;
	gpa_t cr2_or_gpa;
	अचिन्हित दीर्घ addr;
	काष्ठा kvm_arch_async_pf arch;
	bool   wakeup_all;
	bool notpresent_injected;
पूर्ण;

व्योम kvm_clear_async_pf_completion_queue(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_check_async_pf_completion(काष्ठा kvm_vcpu *vcpu);
bool kvm_setup_async_pf(काष्ठा kvm_vcpu *vcpu, gpa_t cr2_or_gpa,
			अचिन्हित दीर्घ hva, काष्ठा kvm_arch_async_pf *arch);
पूर्णांक kvm_async_pf_wakeup_all(काष्ठा kvm_vcpu *vcpu);
#पूर्ण_अगर

#अगर_घोषित KVM_ARCH_WANT_MMU_NOTIFIER
काष्ठा kvm_gfn_range अणु
	काष्ठा kvm_memory_slot *slot;
	gfn_t start;
	gfn_t end;
	pte_t pte;
	bool may_block;
पूर्ण;
bool kvm_unmap_gfn_range(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);
bool kvm_age_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);
bool kvm_test_age_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);
bool kvm_set_spte_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);
#पूर्ण_अगर

क्रमागत अणु
	OUTSIDE_GUEST_MODE,
	IN_GUEST_MODE,
	EXITING_GUEST_MODE,
	READING_SHADOW_PAGE_TABLES,
पूर्ण;

#घोषणा KVM_UNMAPPED_PAGE	((व्योम *) 0x500 + POISON_POINTER_DELTA)

काष्ठा kvm_host_map अणु
	/*
	 * Only valid अगर the 'pfn' is managed by the host kernel (i.e. There is
	 * a 'struct page' क्रम it. When using mem= kernel parameter some memory
	 * can be used as guest memory but they are not managed by host
	 * kernel).
	 * If 'pfn' is not managed by the host kernel, this field is
	 * initialized to KVM_UNMAPPED_PAGE.
	 */
	काष्ठा page *page;
	व्योम *hva;
	kvm_pfn_t pfn;
	kvm_pfn_t gfn;
पूर्ण;

/*
 * Used to check अगर the mapping is valid or not. Never use 'kvm_host_map'
 * directly to check क्रम that.
 */
अटल अंतरभूत bool kvm_vcpu_mapped(काष्ठा kvm_host_map *map)
अणु
	वापस !!map->hva;
पूर्ण

अटल अंतरभूत bool kvm_vcpu_can_poll(kसमय_प्रकार cur, kसमय_प्रकार stop)
अणु
	वापस single_task_running() && !need_resched() && kसमय_beक्रमe(cur, stop);
पूर्ण

/*
 * Someबार a large or cross-page mmio needs to be broken up पूर्णांकo separate
 * निकासs क्रम userspace servicing.
 */
काष्ठा kvm_mmio_fragment अणु
	gpa_t gpa;
	व्योम *data;
	अचिन्हित len;
पूर्ण;

काष्ठा kvm_vcpu अणु
	काष्ठा kvm *kvm;
#अगर_घोषित CONFIG_PREEMPT_NOTIFIERS
	काष्ठा preempt_notअगरier preempt_notअगरier;
#पूर्ण_अगर
	पूर्णांक cpu;
	पूर्णांक vcpu_id; /* id given by userspace at creation */
	पूर्णांक vcpu_idx; /* index in kvm->vcpus array */
	पूर्णांक srcu_idx;
	पूर्णांक mode;
	u64 requests;
	अचिन्हित दीर्घ guest_debug;

	पूर्णांक pre_pcpu;
	काष्ठा list_head blocked_vcpu_list;

	काष्ठा mutex mutex;
	काष्ठा kvm_run *run;

	काष्ठा rcuरुको रुको;
	काष्ठा pid __rcu *pid;
	पूर्णांक sigset_active;
	sigset_t sigset;
	काष्ठा kvm_vcpu_stat stat;
	अचिन्हित पूर्णांक halt_poll_ns;
	bool valid_wakeup;

#अगर_घोषित CONFIG_HAS_IOMEM
	पूर्णांक mmio_needed;
	पूर्णांक mmio_पढ़ो_completed;
	पूर्णांक mmio_is_ग_लिखो;
	पूर्णांक mmio_cur_fragment;
	पूर्णांक mmio_nr_fragments;
	काष्ठा kvm_mmio_fragment mmio_fragments[KVM_MAX_MMIO_FRAGMENTS];
#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_ASYNC_PF
	काष्ठा अणु
		u32 queued;
		काष्ठा list_head queue;
		काष्ठा list_head करोne;
		spinlock_t lock;
	पूर्ण async_pf;
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_KVM_CPU_RELAX_INTERCEPT
	/*
	 * Cpu relax पूर्णांकercept or छोड़ो loop निकास optimization
	 * in_spin_loop: set when a vcpu करोes a छोड़ो loop निकास
	 *  or cpu relax पूर्णांकercepted.
	 * dy_eligible: indicates whether vcpu is eligible क्रम directed yield.
	 */
	काष्ठा अणु
		bool in_spin_loop;
		bool dy_eligible;
	पूर्ण spin_loop;
#पूर्ण_अगर
	bool preempted;
	bool पढ़ोy;
	काष्ठा kvm_vcpu_arch arch;
	काष्ठा kvm_dirty_ring dirty_ring;
पूर्ण;

/* must be called with irqs disabled */
अटल __always_अंतरभूत व्योम guest_enter_irqoff(व्योम)
अणु
	/*
	 * This is running in ioctl context so its safe to assume that it's the
	 * sसमय pending cpuसमय to flush.
	 */
	instrumentation_begin();
	vसमय_account_guest_enter();
	instrumentation_end();

	/*
	 * KVM करोes not hold any references to rcu रक्षित data when it
	 * चयनes CPU पूर्णांकo a guest mode. In fact चयनing to a guest mode
	 * is very similar to निकासing to userspace from rcu poपूर्णांक of view. In
	 * addition CPU may stay in a guest mode क्रम quite a दीर्घ समय (up to
	 * one समय slice). Lets treat guest mode as quiescent state, just like
	 * we करो with user-mode execution.
	 */
	अगर (!context_tracking_guest_enter()) अणु
		instrumentation_begin();
		rcu_virt_note_context_चयन(smp_processor_id());
		instrumentation_end();
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम guest_निकास_irqoff(व्योम)
अणु
	context_tracking_guest_निकास();

	instrumentation_begin();
	/* Flush the guest cpuसमय we spent on the guest */
	vसमय_account_guest_निकास();
	instrumentation_end();
पूर्ण

अटल अंतरभूत व्योम guest_निकास(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	guest_निकास_irqoff();
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत पूर्णांक kvm_vcpu_निकासing_guest_mode(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * The memory barrier ensures a previous ग_लिखो to vcpu->requests cannot
	 * be reordered with the पढ़ो of vcpu->mode.  It pairs with the general
	 * memory barrier following the ग_लिखो of vcpu->mode in VCPU RUN.
	 */
	smp_mb__beक्रमe_atomic();
	वापस cmpxchg(&vcpu->mode, IN_GUEST_MODE, EXITING_GUEST_MODE);
पूर्ण

/*
 * Some of the bitops functions करो not support too दीर्घ biपंचांगaps.
 * This number must be determined not to exceed such limits.
 */
#घोषणा KVM_MEM_MAX_NR_PAGES ((1UL << 31) - 1)

काष्ठा kvm_memory_slot अणु
	gfn_t base_gfn;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ *dirty_biपंचांगap;
	काष्ठा kvm_arch_memory_slot arch;
	अचिन्हित दीर्घ userspace_addr;
	u32 flags;
	लघु id;
	u16 as_id;
पूर्ण;

अटल अंतरभूत bool kvm_slot_dirty_track_enabled(काष्ठा kvm_memory_slot *slot)
अणु
	वापस slot->flags & KVM_MEM_LOG_सूचीTY_PAGES;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kvm_dirty_biपंचांगap_bytes(काष्ठा kvm_memory_slot *memslot)
अणु
	वापस ALIGN(memslot->npages, BITS_PER_LONG) / 8;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *kvm_second_dirty_biपंचांगap(काष्ठा kvm_memory_slot *memslot)
अणु
	अचिन्हित दीर्घ len = kvm_dirty_biपंचांगap_bytes(memslot);

	वापस memslot->dirty_biपंचांगap + len / माप(*memslot->dirty_biपंचांगap);
पूर्ण

#अगर_अघोषित KVM_सूचीTY_LOG_MANUAL_CAPS
#घोषणा KVM_सूचीTY_LOG_MANUAL_CAPS KVM_सूचीTY_LOG_MANUAL_PROTECT_ENABLE
#पूर्ण_अगर

काष्ठा kvm_s390_adapter_पूर्णांक अणु
	u64 ind_addr;
	u64 summary_addr;
	u64 ind_offset;
	u32 summary_offset;
	u32 adapter_id;
पूर्ण;

काष्ठा kvm_hv_sपूर्णांक अणु
	u32 vcpu;
	u32 sपूर्णांक;
पूर्ण;

काष्ठा kvm_kernel_irq_routing_entry अणु
	u32 gsi;
	u32 type;
	पूर्णांक (*set)(काष्ठा kvm_kernel_irq_routing_entry *e,
		   काष्ठा kvm *kvm, पूर्णांक irq_source_id, पूर्णांक level,
		   bool line_status);
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित irqchip;
			अचिन्हित pin;
		पूर्ण irqchip;
		काष्ठा अणु
			u32 address_lo;
			u32 address_hi;
			u32 data;
			u32 flags;
			u32 devid;
		पूर्ण msi;
		काष्ठा kvm_s390_adapter_पूर्णांक adapter;
		काष्ठा kvm_hv_sपूर्णांक hv_sपूर्णांक;
	पूर्ण;
	काष्ठा hlist_node link;
पूर्ण;

#अगर_घोषित CONFIG_HAVE_KVM_IRQ_ROUTING
काष्ठा kvm_irq_routing_table अणु
	पूर्णांक chip[KVM_NR_IRQCHIPS][KVM_IRQCHIP_NUM_PINS];
	u32 nr_rt_entries;
	/*
	 * Array indexed by gsi. Each entry contains list of irq chips
	 * the gsi is connected to.
	 */
	काष्ठा hlist_head map[];
पूर्ण;
#पूर्ण_अगर

#अगर_अघोषित KVM_PRIVATE_MEM_SLOTS
#घोषणा KVM_PRIVATE_MEM_SLOTS 0
#पूर्ण_अगर

#घोषणा KVM_MEM_SLOTS_NUM लघु_उच्च
#घोषणा KVM_USER_MEM_SLOTS (KVM_MEM_SLOTS_NUM - KVM_PRIVATE_MEM_SLOTS)

#अगर_अघोषित __KVM_VCPU_MULTIPLE_ADDRESS_SPACE
अटल अंतरभूत पूर्णांक kvm_arch_vcpu_memslots_id(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Note:
 * memslots are not sorted by id anymore, please use id_to_memslot()
 * to get the memslot by its id.
 */
काष्ठा kvm_memslots अणु
	u64 generation;
	/* The mapping table from slot id to the index in memslots[]. */
	लघु id_to_index[KVM_MEM_SLOTS_NUM];
	atomic_t lru_slot;
	पूर्णांक used_slots;
	काष्ठा kvm_memory_slot memslots[];
पूर्ण;

काष्ठा kvm अणु
#अगर_घोषित KVM_HAVE_MMU_RWLOCK
	rwlock_t mmu_lock;
#अन्यथा
	spinlock_t mmu_lock;
#पूर्ण_अगर /* KVM_HAVE_MMU_RWLOCK */

	काष्ठा mutex slots_lock;
	काष्ठा mm_काष्ठा *mm; /* userspace tied to this vm */
	काष्ठा kvm_memslots __rcu *memslots[KVM_ADDRESS_SPACE_NUM];
	काष्ठा kvm_vcpu *vcpus[KVM_MAX_VCPUS];

	/*
	 * created_vcpus is रक्षित by kvm->lock, and is incremented
	 * at the beginning of KVM_CREATE_VCPU.  online_vcpus is only
	 * incremented after storing the kvm_vcpu poपूर्णांकer in vcpus,
	 * and is accessed atomically.
	 */
	atomic_t online_vcpus;
	पूर्णांक created_vcpus;
	पूर्णांक last_boosted_vcpu;
	काष्ठा list_head vm_list;
	काष्ठा mutex lock;
	काष्ठा kvm_io_bus __rcu *buses[KVM_NR_BUSES];
#अगर_घोषित CONFIG_HAVE_KVM_EVENTFD
	काष्ठा अणु
		spinlock_t        lock;
		काष्ठा list_head  items;
		काष्ठा list_head  resampler_list;
		काष्ठा mutex      resampler_lock;
	पूर्ण irqfds;
	काष्ठा list_head ioeventfds;
#पूर्ण_अगर
	काष्ठा kvm_vm_stat stat;
	काष्ठा kvm_arch arch;
	refcount_t users_count;
#अगर_घोषित CONFIG_KVM_MMIO
	काष्ठा kvm_coalesced_mmio_ring *coalesced_mmio_ring;
	spinlock_t ring_lock;
	काष्ठा list_head coalesced_zones;
#पूर्ण_अगर

	काष्ठा mutex irq_lock;
#अगर_घोषित CONFIG_HAVE_KVM_IRQCHIP
	/*
	 * Update side is रक्षित by irq_lock.
	 */
	काष्ठा kvm_irq_routing_table __rcu *irq_routing;
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAVE_KVM_IRQFD
	काष्ठा hlist_head irq_ack_notअगरier_list;
#पूर्ण_अगर

#अगर defined(CONFIG_MMU_NOTIFIER) && defined(KVM_ARCH_WANT_MMU_NOTIFIER)
	काष्ठा mmu_notअगरier mmu_notअगरier;
	अचिन्हित दीर्घ mmu_notअगरier_seq;
	दीर्घ mmu_notअगरier_count;
	अचिन्हित दीर्घ mmu_notअगरier_range_start;
	अचिन्हित दीर्घ mmu_notअगरier_range_end;
#पूर्ण_अगर
	दीर्घ tlbs_dirty;
	काष्ठा list_head devices;
	u64 manual_dirty_log_protect;
	काष्ठा dentry *debugfs_dentry;
	काष्ठा kvm_stat_data **debugfs_stat_data;
	काष्ठा srcu_काष्ठा srcu;
	काष्ठा srcu_काष्ठा irq_srcu;
	pid_t userspace_pid;
	अचिन्हित पूर्णांक max_halt_poll_ns;
	u32 dirty_ring_size;
पूर्ण;

#घोषणा kvm_err(fmt, ...) \
	pr_err("kvm [%i]: " fmt, task_pid_nr(current), ## __VA_ARGS__)
#घोषणा kvm_info(fmt, ...) \
	pr_info("kvm [%i]: " fmt, task_pid_nr(current), ## __VA_ARGS__)
#घोषणा kvm_debug(fmt, ...) \
	pr_debug("kvm [%i]: " fmt, task_pid_nr(current), ## __VA_ARGS__)
#घोषणा kvm_debug_ratelimited(fmt, ...) \
	pr_debug_ratelimited("kvm [%i]: " fmt, task_pid_nr(current), \
			     ## __VA_ARGS__)
#घोषणा kvm_pr_unimpl(fmt, ...) \
	pr_err_ratelimited("kvm [%i]: " fmt, \
			   task_tgid_nr(current), ## __VA_ARGS__)

/* The guest did something we करोn't support. */
#घोषणा vcpu_unimpl(vcpu, fmt, ...)					\
	kvm_pr_unimpl("vcpu%i, guest rIP: 0x%lx " fmt,			\
			(vcpu)->vcpu_id, kvm_rip_पढ़ो(vcpu), ## __VA_ARGS__)

#घोषणा vcpu_debug(vcpu, fmt, ...)					\
	kvm_debug("vcpu%i " fmt, (vcpu)->vcpu_id, ## __VA_ARGS__)
#घोषणा vcpu_debug_ratelimited(vcpu, fmt, ...)				\
	kvm_debug_ratelimited("vcpu%i " fmt, (vcpu)->vcpu_id,           \
			      ## __VA_ARGS__)
#घोषणा vcpu_err(vcpu, fmt, ...)					\
	kvm_err("vcpu%i " fmt, (vcpu)->vcpu_id, ## __VA_ARGS__)

अटल अंतरभूत bool kvm_dirty_log_manual_protect_and_init_set(काष्ठा kvm *kvm)
अणु
	वापस !!(kvm->manual_dirty_log_protect & KVM_सूचीTY_LOG_INITIALLY_SET);
पूर्ण

अटल अंतरभूत काष्ठा kvm_io_bus *kvm_get_bus(काष्ठा kvm *kvm, क्रमागत kvm_bus idx)
अणु
	वापस srcu_dereference_check(kvm->buses[idx], &kvm->srcu,
				      lockdep_is_held(&kvm->slots_lock) ||
				      !refcount_पढ़ो(&kvm->users_count));
पूर्ण

अटल अंतरभूत काष्ठा kvm_vcpu *kvm_get_vcpu(काष्ठा kvm *kvm, पूर्णांक i)
अणु
	पूर्णांक num_vcpus = atomic_पढ़ो(&kvm->online_vcpus);
	i = array_index_nospec(i, num_vcpus);

	/* Pairs with smp_wmb() in kvm_vm_ioctl_create_vcpu.  */
	smp_rmb();
	वापस kvm->vcpus[i];
पूर्ण

#घोषणा kvm_क्रम_each_vcpu(idx, vcpup, kvm) \
	क्रम (idx = 0; \
	     idx < atomic_पढ़ो(&kvm->online_vcpus) && \
	     (vcpup = kvm_get_vcpu(kvm, idx)) != शून्य; \
	     idx++)

अटल अंतरभूत काष्ठा kvm_vcpu *kvm_get_vcpu_by_id(काष्ठा kvm *kvm, पूर्णांक id)
अणु
	काष्ठा kvm_vcpu *vcpu = शून्य;
	पूर्णांक i;

	अगर (id < 0)
		वापस शून्य;
	अगर (id < KVM_MAX_VCPUS)
		vcpu = kvm_get_vcpu(kvm, id);
	अगर (vcpu && vcpu->vcpu_id == id)
		वापस vcpu;
	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		अगर (vcpu->vcpu_id == id)
			वापस vcpu;
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक kvm_vcpu_get_idx(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->vcpu_idx;
पूर्ण

#घोषणा kvm_क्रम_each_memslot(memslot, slots)				\
	क्रम (memslot = &slots->memslots[0];				\
	     memslot < slots->memslots + slots->used_slots; memslot++)	\
		अगर (WARN_ON_ONCE(!memslot->npages)) अणु			\
		पूर्ण अन्यथा

व्योम kvm_vcpu_destroy(काष्ठा kvm_vcpu *vcpu);

व्योम vcpu_load(काष्ठा kvm_vcpu *vcpu);
व्योम vcpu_put(काष्ठा kvm_vcpu *vcpu);

#अगर_घोषित __KVM_HAVE_IOAPIC
व्योम kvm_arch_post_irq_ack_notअगरier_list_update(काष्ठा kvm *kvm);
व्योम kvm_arch_post_irq_routing_update(काष्ठा kvm *kvm);
#अन्यथा
अटल अंतरभूत व्योम kvm_arch_post_irq_ack_notअगरier_list_update(काष्ठा kvm *kvm)
अणु
पूर्ण
अटल अंतरभूत व्योम kvm_arch_post_irq_routing_update(काष्ठा kvm *kvm)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_KVM_IRQFD
पूर्णांक kvm_irqfd_init(व्योम);
व्योम kvm_irqfd_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक kvm_irqfd_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम kvm_irqfd_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर
पूर्णांक kvm_init(व्योम *opaque, अचिन्हित vcpu_size, अचिन्हित vcpu_align,
		  काष्ठा module *module);
व्योम kvm_निकास(व्योम);

व्योम kvm_get_kvm(काष्ठा kvm *kvm);
व्योम kvm_put_kvm(काष्ठा kvm *kvm);
bool file_is_kvm(काष्ठा file *file);
व्योम kvm_put_kvm_no_destroy(काष्ठा kvm *kvm);

अटल अंतरभूत काष्ठा kvm_memslots *__kvm_memslots(काष्ठा kvm *kvm, पूर्णांक as_id)
अणु
	as_id = array_index_nospec(as_id, KVM_ADDRESS_SPACE_NUM);
	वापस srcu_dereference_check(kvm->memslots[as_id], &kvm->srcu,
			lockdep_is_held(&kvm->slots_lock) ||
			!refcount_पढ़ो(&kvm->users_count));
पूर्ण

अटल अंतरभूत काष्ठा kvm_memslots *kvm_memslots(काष्ठा kvm *kvm)
अणु
	वापस __kvm_memslots(kvm, 0);
पूर्ण

अटल अंतरभूत काष्ठा kvm_memslots *kvm_vcpu_memslots(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक as_id = kvm_arch_vcpu_memslots_id(vcpu);

	वापस __kvm_memslots(vcpu->kvm, as_id);
पूर्ण

अटल अंतरभूत
काष्ठा kvm_memory_slot *id_to_memslot(काष्ठा kvm_memslots *slots, पूर्णांक id)
अणु
	पूर्णांक index = slots->id_to_index[id];
	काष्ठा kvm_memory_slot *slot;

	अगर (index < 0)
		वापस शून्य;

	slot = &slots->memslots[index];

	WARN_ON(slot->id != id);
	वापस slot;
पूर्ण

/*
 * KVM_SET_USER_MEMORY_REGION ioctl allows the following operations:
 * - create a new memory slot
 * - delete an existing memory slot
 * - modअगरy an existing memory slot
 *   -- move it in the guest physical memory space
 *   -- just change its flags
 *
 * Since flags can be changed by some of these operations, the following
 * dअगरferentiation is the best we can करो क्रम __kvm_set_memory_region():
 */
क्रमागत kvm_mr_change अणु
	KVM_MR_CREATE,
	KVM_MR_DELETE,
	KVM_MR_MOVE,
	KVM_MR_FLAGS_ONLY,
पूर्ण;

पूर्णांक kvm_set_memory_region(काष्ठा kvm *kvm,
			  स्थिर काष्ठा kvm_userspace_memory_region *mem);
पूर्णांक __kvm_set_memory_region(काष्ठा kvm *kvm,
			    स्थिर काष्ठा kvm_userspace_memory_region *mem);
व्योम kvm_arch_मुक्त_memslot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *slot);
व्योम kvm_arch_memslots_updated(काष्ठा kvm *kvm, u64 gen);
पूर्णांक kvm_arch_prepare_memory_region(काष्ठा kvm *kvm,
				काष्ठा kvm_memory_slot *memslot,
				स्थिर काष्ठा kvm_userspace_memory_region *mem,
				क्रमागत kvm_mr_change change);
व्योम kvm_arch_commit_memory_region(काष्ठा kvm *kvm,
				स्थिर काष्ठा kvm_userspace_memory_region *mem,
				काष्ठा kvm_memory_slot *old,
				स्थिर काष्ठा kvm_memory_slot *new,
				क्रमागत kvm_mr_change change);
/* flush all memory translations */
व्योम kvm_arch_flush_shaकरोw_all(काष्ठा kvm *kvm);
/* flush memory translations poपूर्णांकing to 'slot' */
व्योम kvm_arch_flush_shaकरोw_memslot(काष्ठा kvm *kvm,
				   काष्ठा kvm_memory_slot *slot);

पूर्णांक gfn_to_page_many_atomic(काष्ठा kvm_memory_slot *slot, gfn_t gfn,
			    काष्ठा page **pages, पूर्णांक nr_pages);

काष्ठा page *gfn_to_page(काष्ठा kvm *kvm, gfn_t gfn);
अचिन्हित दीर्घ gfn_to_hva(काष्ठा kvm *kvm, gfn_t gfn);
अचिन्हित दीर्घ gfn_to_hva_prot(काष्ठा kvm *kvm, gfn_t gfn, bool *writable);
अचिन्हित दीर्घ gfn_to_hva_memslot(काष्ठा kvm_memory_slot *slot, gfn_t gfn);
अचिन्हित दीर्घ gfn_to_hva_memslot_prot(काष्ठा kvm_memory_slot *slot, gfn_t gfn,
				      bool *writable);
व्योम kvm_release_page_clean(काष्ठा page *page);
व्योम kvm_release_page_dirty(काष्ठा page *page);
व्योम kvm_set_page_accessed(काष्ठा page *page);

kvm_pfn_t gfn_to_pfn(काष्ठा kvm *kvm, gfn_t gfn);
kvm_pfn_t gfn_to_pfn_prot(काष्ठा kvm *kvm, gfn_t gfn, bool ग_लिखो_fault,
		      bool *writable);
kvm_pfn_t gfn_to_pfn_memslot(काष्ठा kvm_memory_slot *slot, gfn_t gfn);
kvm_pfn_t gfn_to_pfn_memslot_atomic(काष्ठा kvm_memory_slot *slot, gfn_t gfn);
kvm_pfn_t __gfn_to_pfn_memslot(काष्ठा kvm_memory_slot *slot, gfn_t gfn,
			       bool atomic, bool *async, bool ग_लिखो_fault,
			       bool *writable, hva_t *hva);

व्योम kvm_release_pfn_clean(kvm_pfn_t pfn);
व्योम kvm_release_pfn_dirty(kvm_pfn_t pfn);
व्योम kvm_set_pfn_dirty(kvm_pfn_t pfn);
व्योम kvm_set_pfn_accessed(kvm_pfn_t pfn);
व्योम kvm_get_pfn(kvm_pfn_t pfn);

व्योम kvm_release_pfn(kvm_pfn_t pfn, bool dirty, काष्ठा gfn_to_pfn_cache *cache);
पूर्णांक kvm_पढ़ो_guest_page(काष्ठा kvm *kvm, gfn_t gfn, व्योम *data, पूर्णांक offset,
			पूर्णांक len);
पूर्णांक kvm_पढ़ो_guest(काष्ठा kvm *kvm, gpa_t gpa, व्योम *data, अचिन्हित दीर्घ len);
पूर्णांक kvm_पढ़ो_guest_cached(काष्ठा kvm *kvm, काष्ठा gfn_to_hva_cache *ghc,
			   व्योम *data, अचिन्हित दीर्घ len);
पूर्णांक kvm_पढ़ो_guest_offset_cached(काष्ठा kvm *kvm, काष्ठा gfn_to_hva_cache *ghc,
				 व्योम *data, अचिन्हित पूर्णांक offset,
				 अचिन्हित दीर्घ len);
पूर्णांक kvm_ग_लिखो_guest_page(काष्ठा kvm *kvm, gfn_t gfn, स्थिर व्योम *data,
			 पूर्णांक offset, पूर्णांक len);
पूर्णांक kvm_ग_लिखो_guest(काष्ठा kvm *kvm, gpa_t gpa, स्थिर व्योम *data,
		    अचिन्हित दीर्घ len);
पूर्णांक kvm_ग_लिखो_guest_cached(काष्ठा kvm *kvm, काष्ठा gfn_to_hva_cache *ghc,
			   व्योम *data, अचिन्हित दीर्घ len);
पूर्णांक kvm_ग_लिखो_guest_offset_cached(काष्ठा kvm *kvm, काष्ठा gfn_to_hva_cache *ghc,
				  व्योम *data, अचिन्हित पूर्णांक offset,
				  अचिन्हित दीर्घ len);
पूर्णांक kvm_gfn_to_hva_cache_init(काष्ठा kvm *kvm, काष्ठा gfn_to_hva_cache *ghc,
			      gpa_t gpa, अचिन्हित दीर्घ len);

#घोषणा __kvm_get_guest(kvm, gfn, offset, v)				\
(अणु									\
	अचिन्हित दीर्घ __addr = gfn_to_hva(kvm, gfn);			\
	typeof(v) __user *__uaddr = (typeof(__uaddr))(__addr + offset);	\
	पूर्णांक __ret = -EFAULT;						\
									\
	अगर (!kvm_is_error_hva(__addr))					\
		__ret = get_user(v, __uaddr);				\
	__ret;								\
पूर्ण)

#घोषणा kvm_get_guest(kvm, gpa, v)					\
(अणु									\
	gpa_t __gpa = gpa;						\
	काष्ठा kvm *__kvm = kvm;					\
									\
	__kvm_get_guest(__kvm, __gpa >> PAGE_SHIFT,			\
			offset_in_page(__gpa), v);			\
पूर्ण)

#घोषणा __kvm_put_guest(kvm, gfn, offset, v)				\
(अणु									\
	अचिन्हित दीर्घ __addr = gfn_to_hva(kvm, gfn);			\
	typeof(v) __user *__uaddr = (typeof(__uaddr))(__addr + offset);	\
	पूर्णांक __ret = -EFAULT;						\
									\
	अगर (!kvm_is_error_hva(__addr))					\
		__ret = put_user(v, __uaddr);				\
	अगर (!__ret)							\
		mark_page_dirty(kvm, gfn);				\
	__ret;								\
पूर्ण)

#घोषणा kvm_put_guest(kvm, gpa, v)					\
(अणु									\
	gpa_t __gpa = gpa;						\
	काष्ठा kvm *__kvm = kvm;					\
									\
	__kvm_put_guest(__kvm, __gpa >> PAGE_SHIFT,			\
			offset_in_page(__gpa), v);			\
पूर्ण)

पूर्णांक kvm_clear_guest(काष्ठा kvm *kvm, gpa_t gpa, अचिन्हित दीर्घ len);
काष्ठा kvm_memory_slot *gfn_to_memslot(काष्ठा kvm *kvm, gfn_t gfn);
bool kvm_is_visible_gfn(काष्ठा kvm *kvm, gfn_t gfn);
bool kvm_vcpu_is_visible_gfn(काष्ठा kvm_vcpu *vcpu, gfn_t gfn);
अचिन्हित दीर्घ kvm_host_page_size(काष्ठा kvm_vcpu *vcpu, gfn_t gfn);
व्योम mark_page_dirty_in_slot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot, gfn_t gfn);
व्योम mark_page_dirty(काष्ठा kvm *kvm, gfn_t gfn);

काष्ठा kvm_memslots *kvm_vcpu_memslots(काष्ठा kvm_vcpu *vcpu);
काष्ठा kvm_memory_slot *kvm_vcpu_gfn_to_memslot(काष्ठा kvm_vcpu *vcpu, gfn_t gfn);
kvm_pfn_t kvm_vcpu_gfn_to_pfn_atomic(काष्ठा kvm_vcpu *vcpu, gfn_t gfn);
kvm_pfn_t kvm_vcpu_gfn_to_pfn(काष्ठा kvm_vcpu *vcpu, gfn_t gfn);
पूर्णांक kvm_vcpu_map(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, काष्ठा kvm_host_map *map);
पूर्णांक kvm_map_gfn(काष्ठा kvm_vcpu *vcpu, gfn_t gfn, काष्ठा kvm_host_map *map,
		काष्ठा gfn_to_pfn_cache *cache, bool atomic);
काष्ठा page *kvm_vcpu_gfn_to_page(काष्ठा kvm_vcpu *vcpu, gfn_t gfn);
व्योम kvm_vcpu_unmap(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_host_map *map, bool dirty);
पूर्णांक kvm_unmap_gfn(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_host_map *map,
		  काष्ठा gfn_to_pfn_cache *cache, bool dirty, bool atomic);
अचिन्हित दीर्घ kvm_vcpu_gfn_to_hva(काष्ठा kvm_vcpu *vcpu, gfn_t gfn);
अचिन्हित दीर्घ kvm_vcpu_gfn_to_hva_prot(काष्ठा kvm_vcpu *vcpu, gfn_t gfn, bool *writable);
पूर्णांक kvm_vcpu_पढ़ो_guest_page(काष्ठा kvm_vcpu *vcpu, gfn_t gfn, व्योम *data, पूर्णांक offset,
			     पूर्णांक len);
पूर्णांक kvm_vcpu_पढ़ो_guest_atomic(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, व्योम *data,
			       अचिन्हित दीर्घ len);
पूर्णांक kvm_vcpu_पढ़ो_guest(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, व्योम *data,
			अचिन्हित दीर्घ len);
पूर्णांक kvm_vcpu_ग_लिखो_guest_page(काष्ठा kvm_vcpu *vcpu, gfn_t gfn, स्थिर व्योम *data,
			      पूर्णांक offset, पूर्णांक len);
पूर्णांक kvm_vcpu_ग_लिखो_guest(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, स्थिर व्योम *data,
			 अचिन्हित दीर्घ len);
व्योम kvm_vcpu_mark_page_dirty(काष्ठा kvm_vcpu *vcpu, gfn_t gfn);

व्योम kvm_sigset_activate(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_sigset_deactivate(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_vcpu_block(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_arch_vcpu_blocking(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_arch_vcpu_unblocking(काष्ठा kvm_vcpu *vcpu);
bool kvm_vcpu_wake_up(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_vcpu_kick(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_vcpu_yield_to(काष्ठा kvm_vcpu *target);
व्योम kvm_vcpu_on_spin(काष्ठा kvm_vcpu *vcpu, bool usermode_vcpu_not_eligible);

व्योम kvm_flush_remote_tlbs(काष्ठा kvm *kvm);
व्योम kvm_reload_remote_mmus(काष्ठा kvm *kvm);

#अगर_घोषित KVM_ARCH_NR_OBJS_PER_MEMORY_CACHE
पूर्णांक kvm_mmu_topup_memory_cache(काष्ठा kvm_mmu_memory_cache *mc, पूर्णांक min);
पूर्णांक kvm_mmu_memory_cache_nr_मुक्त_objects(काष्ठा kvm_mmu_memory_cache *mc);
व्योम kvm_mmu_मुक्त_memory_cache(काष्ठा kvm_mmu_memory_cache *mc);
व्योम *kvm_mmu_memory_cache_alloc(काष्ठा kvm_mmu_memory_cache *mc);
#पूर्ण_अगर

bool kvm_make_vcpus_request_mask(काष्ठा kvm *kvm, अचिन्हित पूर्णांक req,
				 काष्ठा kvm_vcpu *except,
				 अचिन्हित दीर्घ *vcpu_biपंचांगap, cpumask_var_t पंचांगp);
bool kvm_make_all_cpus_request(काष्ठा kvm *kvm, अचिन्हित पूर्णांक req);
bool kvm_make_all_cpus_request_except(काष्ठा kvm *kvm, अचिन्हित पूर्णांक req,
				      काष्ठा kvm_vcpu *except);
bool kvm_make_cpus_request_mask(काष्ठा kvm *kvm, अचिन्हित पूर्णांक req,
				अचिन्हित दीर्घ *vcpu_biपंचांगap);

दीर्घ kvm_arch_dev_ioctl(काष्ठा file *filp,
			अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg);
दीर्घ kvm_arch_vcpu_ioctl(काष्ठा file *filp,
			 अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg);
vm_fault_t kvm_arch_vcpu_fault(काष्ठा kvm_vcpu *vcpu, काष्ठा vm_fault *vmf);

पूर्णांक kvm_vm_ioctl_check_extension(काष्ठा kvm *kvm, दीर्घ ext);

व्योम kvm_arch_mmu_enable_log_dirty_pt_masked(काष्ठा kvm *kvm,
					काष्ठा kvm_memory_slot *slot,
					gfn_t gfn_offset,
					अचिन्हित दीर्घ mask);
व्योम kvm_arch_sync_dirty_log(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot);

#अगर_घोषित CONFIG_KVM_GENERIC_सूचीTYLOG_READ_PROTECT
व्योम kvm_arch_flush_remote_tlbs_memslot(काष्ठा kvm *kvm,
					स्थिर काष्ठा kvm_memory_slot *memslot);
#अन्यथा /* !CONFIG_KVM_GENERIC_सूचीTYLOG_READ_PROTECT */
पूर्णांक kvm_vm_ioctl_get_dirty_log(काष्ठा kvm *kvm, काष्ठा kvm_dirty_log *log);
पूर्णांक kvm_get_dirty_log(काष्ठा kvm *kvm, काष्ठा kvm_dirty_log *log,
		      पूर्णांक *is_dirty, काष्ठा kvm_memory_slot **memslot);
#पूर्ण_अगर

पूर्णांक kvm_vm_ioctl_irq_line(काष्ठा kvm *kvm, काष्ठा kvm_irq_level *irq_level,
			bool line_status);
पूर्णांक kvm_vm_ioctl_enable_cap(काष्ठा kvm *kvm,
			    काष्ठा kvm_enable_cap *cap);
दीर्घ kvm_arch_vm_ioctl(काष्ठा file *filp,
		       अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg);

पूर्णांक kvm_arch_vcpu_ioctl_get_fpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_fpu *fpu);
पूर्णांक kvm_arch_vcpu_ioctl_set_fpu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_fpu *fpu);

पूर्णांक kvm_arch_vcpu_ioctl_translate(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_translation *tr);

पूर्णांक kvm_arch_vcpu_ioctl_get_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs);
पूर्णांक kvm_arch_vcpu_ioctl_set_regs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_regs *regs);
पूर्णांक kvm_arch_vcpu_ioctl_get_sregs(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_sregs *sregs);
पूर्णांक kvm_arch_vcpu_ioctl_set_sregs(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_sregs *sregs);
पूर्णांक kvm_arch_vcpu_ioctl_get_mpstate(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_mp_state *mp_state);
पूर्णांक kvm_arch_vcpu_ioctl_set_mpstate(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_mp_state *mp_state);
पूर्णांक kvm_arch_vcpu_ioctl_set_guest_debug(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_guest_debug *dbg);
पूर्णांक kvm_arch_vcpu_ioctl_run(काष्ठा kvm_vcpu *vcpu);

पूर्णांक kvm_arch_init(व्योम *opaque);
व्योम kvm_arch_निकास(व्योम);

व्योम kvm_arch_sched_in(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu);

व्योम kvm_arch_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu);
व्योम kvm_arch_vcpu_put(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_arch_vcpu_precreate(काष्ठा kvm *kvm, अचिन्हित पूर्णांक id);
पूर्णांक kvm_arch_vcpu_create(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_arch_vcpu_postcreate(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_arch_vcpu_destroy(काष्ठा kvm_vcpu *vcpu);

#अगर_घोषित __KVM_HAVE_ARCH_VCPU_DEBUGFS
व्योम kvm_arch_create_vcpu_debugfs(काष्ठा kvm_vcpu *vcpu, काष्ठा dentry *debugfs_dentry);
#पूर्ण_अगर

पूर्णांक kvm_arch_hardware_enable(व्योम);
व्योम kvm_arch_hardware_disable(व्योम);
पूर्णांक kvm_arch_hardware_setup(व्योम *opaque);
व्योम kvm_arch_hardware_unsetup(व्योम);
पूर्णांक kvm_arch_check_processor_compat(व्योम *opaque);
पूर्णांक kvm_arch_vcpu_runnable(काष्ठा kvm_vcpu *vcpu);
bool kvm_arch_vcpu_in_kernel(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_arch_vcpu_should_kick(काष्ठा kvm_vcpu *vcpu);
bool kvm_arch_dy_runnable(काष्ठा kvm_vcpu *vcpu);
bool kvm_arch_dy_has_pending_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_arch_post_init_vm(काष्ठा kvm *kvm);
व्योम kvm_arch_pre_destroy_vm(काष्ठा kvm *kvm);

#अगर_अघोषित __KVM_HAVE_ARCH_VM_ALLOC
/*
 * All architectures that want to use vzalloc currently also
 * need their own kvm_arch_alloc_vm implementation.
 */
अटल अंतरभूत काष्ठा kvm *kvm_arch_alloc_vm(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा kvm), GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम kvm_arch_मुक्त_vm(काष्ठा kvm *kvm)
अणु
	kमुक्त(kvm);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __KVM_HAVE_ARCH_FLUSH_REMOTE_TLB
अटल अंतरभूत पूर्णांक kvm_arch_flush_remote_tlb(काष्ठा kvm *kvm)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __KVM_HAVE_ARCH_NONCOHERENT_DMA
व्योम kvm_arch_रेजिस्टर_noncoherent_dma(काष्ठा kvm *kvm);
व्योम kvm_arch_unरेजिस्टर_noncoherent_dma(काष्ठा kvm *kvm);
bool kvm_arch_has_noncoherent_dma(काष्ठा kvm *kvm);
#अन्यथा
अटल अंतरभूत व्योम kvm_arch_रेजिस्टर_noncoherent_dma(काष्ठा kvm *kvm)
अणु
पूर्ण

अटल अंतरभूत व्योम kvm_arch_unरेजिस्टर_noncoherent_dma(काष्ठा kvm *kvm)
अणु
पूर्ण

अटल अंतरभूत bool kvm_arch_has_noncoherent_dma(काष्ठा kvm *kvm)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर
#अगर_घोषित __KVM_HAVE_ARCH_ASSIGNED_DEVICE
व्योम kvm_arch_start_assignment(काष्ठा kvm *kvm);
व्योम kvm_arch_end_assignment(काष्ठा kvm *kvm);
bool kvm_arch_has_asचिन्हित_device(काष्ठा kvm *kvm);
#अन्यथा
अटल अंतरभूत व्योम kvm_arch_start_assignment(काष्ठा kvm *kvm)
अणु
पूर्ण

अटल अंतरभूत व्योम kvm_arch_end_assignment(काष्ठा kvm *kvm)
अणु
पूर्ण

अटल अंतरभूत bool kvm_arch_has_asचिन्हित_device(काष्ठा kvm *kvm)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा rcuरुको *kvm_arch_vcpu_get_रुको(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित __KVM_HAVE_ARCH_WQP
	वापस vcpu->arch.रुकोp;
#अन्यथा
	वापस &vcpu->रुको;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित __KVM_HAVE_ARCH_INTC_INITIALIZED
/*
 * वापसs true अगर the भव पूर्णांकerrupt controller is initialized and
 * पढ़ोy to accept भव IRQ. On some architectures the भव पूर्णांकerrupt
 * controller is dynamically instantiated and this is not always true.
 */
bool kvm_arch_पूर्णांकc_initialized(काष्ठा kvm *kvm);
#अन्यथा
अटल अंतरभूत bool kvm_arch_पूर्णांकc_initialized(काष्ठा kvm *kvm)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

पूर्णांक kvm_arch_init_vm(काष्ठा kvm *kvm, अचिन्हित दीर्घ type);
व्योम kvm_arch_destroy_vm(काष्ठा kvm *kvm);
व्योम kvm_arch_sync_events(काष्ठा kvm *kvm);

पूर्णांक kvm_cpu_has_pending_समयr(काष्ठा kvm_vcpu *vcpu);

bool kvm_is_reserved_pfn(kvm_pfn_t pfn);
bool kvm_is_zone_device_pfn(kvm_pfn_t pfn);
bool kvm_is_transparent_hugepage(kvm_pfn_t pfn);

काष्ठा kvm_irq_ack_notअगरier अणु
	काष्ठा hlist_node link;
	अचिन्हित gsi;
	व्योम (*irq_acked)(काष्ठा kvm_irq_ack_notअगरier *kian);
पूर्ण;

पूर्णांक kvm_irq_map_gsi(काष्ठा kvm *kvm,
		    काष्ठा kvm_kernel_irq_routing_entry *entries, पूर्णांक gsi);
पूर्णांक kvm_irq_map_chip_pin(काष्ठा kvm *kvm, अचिन्हित irqchip, अचिन्हित pin);

पूर्णांक kvm_set_irq(काष्ठा kvm *kvm, पूर्णांक irq_source_id, u32 irq, पूर्णांक level,
		bool line_status);
पूर्णांक kvm_set_msi(काष्ठा kvm_kernel_irq_routing_entry *irq_entry, काष्ठा kvm *kvm,
		पूर्णांक irq_source_id, पूर्णांक level, bool line_status);
पूर्णांक kvm_arch_set_irq_inatomic(काष्ठा kvm_kernel_irq_routing_entry *e,
			       काष्ठा kvm *kvm, पूर्णांक irq_source_id,
			       पूर्णांक level, bool line_status);
bool kvm_irq_has_notअगरier(काष्ठा kvm *kvm, अचिन्हित irqchip, अचिन्हित pin);
व्योम kvm_notअगरy_acked_gsi(काष्ठा kvm *kvm, पूर्णांक gsi);
व्योम kvm_notअगरy_acked_irq(काष्ठा kvm *kvm, अचिन्हित irqchip, अचिन्हित pin);
व्योम kvm_रेजिस्टर_irq_ack_notअगरier(काष्ठा kvm *kvm,
				   काष्ठा kvm_irq_ack_notअगरier *kian);
व्योम kvm_unरेजिस्टर_irq_ack_notअगरier(काष्ठा kvm *kvm,
				   काष्ठा kvm_irq_ack_notअगरier *kian);
पूर्णांक kvm_request_irq_source_id(काष्ठा kvm *kvm);
व्योम kvm_मुक्त_irq_source_id(काष्ठा kvm *kvm, पूर्णांक irq_source_id);
bool kvm_arch_irqfd_allowed(काष्ठा kvm *kvm, काष्ठा kvm_irqfd *args);

/*
 * search_memslots() and __gfn_to_memslot() are here because they are
 * used in non-modular code in arch/घातerpc/kvm/book3s_hv_rm_mmu.c.
 * gfn_to_memslot() itself isn't here as an अंतरभूत because that would
 * bloat other code too much.
 *
 * IMPORTANT: Slots are sorted from highest GFN to lowest GFN!
 */
अटल अंतरभूत काष्ठा kvm_memory_slot *
search_memslots(काष्ठा kvm_memslots *slots, gfn_t gfn)
अणु
	पूर्णांक start = 0, end = slots->used_slots;
	पूर्णांक slot = atomic_पढ़ो(&slots->lru_slot);
	काष्ठा kvm_memory_slot *memslots = slots->memslots;

	अगर (unlikely(!slots->used_slots))
		वापस शून्य;

	अगर (gfn >= memslots[slot].base_gfn &&
	    gfn < memslots[slot].base_gfn + memslots[slot].npages)
		वापस &memslots[slot];

	जबतक (start < end) अणु
		slot = start + (end - start) / 2;

		अगर (gfn >= memslots[slot].base_gfn)
			end = slot;
		अन्यथा
			start = slot + 1;
	पूर्ण

	अगर (start < slots->used_slots && gfn >= memslots[start].base_gfn &&
	    gfn < memslots[start].base_gfn + memslots[start].npages) अणु
		atomic_set(&slots->lru_slot, start);
		वापस &memslots[start];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा kvm_memory_slot *
__gfn_to_memslot(काष्ठा kvm_memslots *slots, gfn_t gfn)
अणु
	वापस search_memslots(slots, gfn);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
__gfn_to_hva_memslot(स्थिर काष्ठा kvm_memory_slot *slot, gfn_t gfn)
अणु
	/*
	 * The index was checked originally in search_memslots.  To aव्योम
	 * that a malicious guest builds a Spectre gadget out of e.g. page
	 * table walks, करो not let the processor speculate loads outside
	 * the guest's रेजिस्टरed memslots.
	 */
	अचिन्हित दीर्घ offset = gfn - slot->base_gfn;
	offset = array_index_nospec(offset, slot->npages);
	वापस slot->userspace_addr + offset * PAGE_SIZE;
पूर्ण

अटल अंतरभूत पूर्णांक memslot_id(काष्ठा kvm *kvm, gfn_t gfn)
अणु
	वापस gfn_to_memslot(kvm, gfn)->id;
पूर्ण

अटल अंतरभूत gfn_t
hva_to_gfn_memslot(अचिन्हित दीर्घ hva, काष्ठा kvm_memory_slot *slot)
अणु
	gfn_t gfn_offset = (hva - slot->userspace_addr) >> PAGE_SHIFT;

	वापस slot->base_gfn + gfn_offset;
पूर्ण

अटल अंतरभूत gpa_t gfn_to_gpa(gfn_t gfn)
अणु
	वापस (gpa_t)gfn << PAGE_SHIFT;
पूर्ण

अटल अंतरभूत gfn_t gpa_to_gfn(gpa_t gpa)
अणु
	वापस (gfn_t)(gpa >> PAGE_SHIFT);
पूर्ण

अटल अंतरभूत hpa_t pfn_to_hpa(kvm_pfn_t pfn)
अणु
	वापस (hpa_t)pfn << PAGE_SHIFT;
पूर्ण

अटल अंतरभूत काष्ठा page *kvm_vcpu_gpa_to_page(काष्ठा kvm_vcpu *vcpu,
						gpa_t gpa)
अणु
	वापस kvm_vcpu_gfn_to_page(vcpu, gpa_to_gfn(gpa));
पूर्ण

अटल अंतरभूत bool kvm_is_error_gpa(काष्ठा kvm *kvm, gpa_t gpa)
अणु
	अचिन्हित दीर्घ hva = gfn_to_hva(kvm, gpa_to_gfn(gpa));

	वापस kvm_is_error_hva(hva);
पूर्ण

क्रमागत kvm_stat_kind अणु
	KVM_STAT_VM,
	KVM_STAT_VCPU,
पूर्ण;

काष्ठा kvm_stat_data अणु
	काष्ठा kvm *kvm;
	काष्ठा kvm_stats_debugfs_item *dbgfs_item;
पूर्ण;

काष्ठा kvm_stats_debugfs_item अणु
	स्थिर अक्षर *name;
	पूर्णांक offset;
	क्रमागत kvm_stat_kind kind;
	पूर्णांक mode;
पूर्ण;

#घोषणा KVM_DBGFS_GET_MODE(dbgfs_item)                                         \
	((dbgfs_item)->mode ? (dbgfs_item)->mode : 0644)

#घोषणा VM_STAT(n, x, ...) 							\
	अणु n, दुरत्व(काष्ठा kvm, stat.x), KVM_STAT_VM, ## __VA_ARGS__ पूर्ण
#घोषणा VCPU_STAT(n, x, ...)							\
	अणु n, दुरत्व(काष्ठा kvm_vcpu, stat.x), KVM_STAT_VCPU, ## __VA_ARGS__ पूर्ण

बाह्य काष्ठा kvm_stats_debugfs_item debugfs_entries[];
बाह्य काष्ठा dentry *kvm_debugfs_dir;

#अगर defined(CONFIG_MMU_NOTIFIER) && defined(KVM_ARCH_WANT_MMU_NOTIFIER)
अटल अंतरभूत पूर्णांक mmu_notअगरier_retry(काष्ठा kvm *kvm, अचिन्हित दीर्घ mmu_seq)
अणु
	अगर (unlikely(kvm->mmu_notअगरier_count))
		वापस 1;
	/*
	 * Ensure the पढ़ो of mmu_notअगरier_count happens beक्रमe the पढ़ो
	 * of mmu_notअगरier_seq.  This पूर्णांकeracts with the smp_wmb() in
	 * mmu_notअगरier_invalidate_range_end to make sure that the caller
	 * either sees the old (non-zero) value of mmu_notअगरier_count or
	 * the new (incremented) value of mmu_notअगरier_seq.
	 * PowerPC Book3s HV KVM calls this under a per-page lock
	 * rather than under kvm->mmu_lock, क्रम scalability, so
	 * can't rely on kvm->mmu_lock to keep things ordered.
	 */
	smp_rmb();
	अगर (kvm->mmu_notअगरier_seq != mmu_seq)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mmu_notअगरier_retry_hva(काष्ठा kvm *kvm,
					 अचिन्हित दीर्घ mmu_seq,
					 अचिन्हित दीर्घ hva)
अणु
	lockdep_निश्चित_held(&kvm->mmu_lock);
	/*
	 * If mmu_notअगरier_count is non-zero, then the range मुख्यtained by
	 * kvm_mmu_notअगरier_invalidate_range_start contains all addresses that
	 * might be being invalidated. Note that it may include some false
	 * positives, due to लघुcuts when handing concurrent invalidations.
	 */
	अगर (unlikely(kvm->mmu_notअगरier_count) &&
	    hva >= kvm->mmu_notअगरier_range_start &&
	    hva < kvm->mmu_notअगरier_range_end)
		वापस 1;
	अगर (kvm->mmu_notअगरier_seq != mmu_seq)
		वापस 1;
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_KVM_IRQ_ROUTING

#घोषणा KVM_MAX_IRQ_ROUTES 4096 /* might need extension/rework in the future */

bool kvm_arch_can_set_irq_routing(काष्ठा kvm *kvm);
पूर्णांक kvm_set_irq_routing(काष्ठा kvm *kvm,
			स्थिर काष्ठा kvm_irq_routing_entry *entries,
			अचिन्हित nr,
			अचिन्हित flags);
पूर्णांक kvm_set_routing_entry(काष्ठा kvm *kvm,
			  काष्ठा kvm_kernel_irq_routing_entry *e,
			  स्थिर काष्ठा kvm_irq_routing_entry *ue);
व्योम kvm_मुक्त_irq_routing(काष्ठा kvm *kvm);

#अन्यथा

अटल अंतरभूत व्योम kvm_मुक्त_irq_routing(काष्ठा kvm *kvm) अणुपूर्ण

#पूर्ण_अगर

पूर्णांक kvm_send_userspace_msi(काष्ठा kvm *kvm, काष्ठा kvm_msi *msi);

#अगर_घोषित CONFIG_HAVE_KVM_EVENTFD

व्योम kvm_eventfd_init(काष्ठा kvm *kvm);
पूर्णांक kvm_ioeventfd(काष्ठा kvm *kvm, काष्ठा kvm_ioeventfd *args);

#अगर_घोषित CONFIG_HAVE_KVM_IRQFD
पूर्णांक kvm_irqfd(काष्ठा kvm *kvm, काष्ठा kvm_irqfd *args);
व्योम kvm_irqfd_release(काष्ठा kvm *kvm);
व्योम kvm_irq_routing_update(काष्ठा kvm *);
#अन्यथा
अटल अंतरभूत पूर्णांक kvm_irqfd(काष्ठा kvm *kvm, काष्ठा kvm_irqfd *args)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम kvm_irqfd_release(काष्ठा kvm *kvm) अणुपूर्ण
#पूर्ण_अगर

#अन्यथा

अटल अंतरभूत व्योम kvm_eventfd_init(काष्ठा kvm *kvm) अणुपूर्ण

अटल अंतरभूत पूर्णांक kvm_irqfd(काष्ठा kvm *kvm, काष्ठा kvm_irqfd *args)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम kvm_irqfd_release(काष्ठा kvm *kvm) अणुपूर्ण

#अगर_घोषित CONFIG_HAVE_KVM_IRQCHIP
अटल अंतरभूत व्योम kvm_irq_routing_update(काष्ठा kvm *kvm)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक kvm_ioeventfd(काष्ठा kvm *kvm, काष्ठा kvm_ioeventfd *args)
अणु
	वापस -ENOSYS;
पूर्ण

#पूर्ण_अगर /* CONFIG_HAVE_KVM_EVENTFD */

व्योम kvm_arch_irq_routing_update(काष्ठा kvm *kvm);

अटल अंतरभूत व्योम kvm_make_request(पूर्णांक req, काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * Ensure the rest of the request is published to kvm_check_request's
	 * caller.  Paired with the smp_mb__after_atomic in kvm_check_request.
	 */
	smp_wmb();
	set_bit(req & KVM_REQUEST_MASK, (व्योम *)&vcpu->requests);
पूर्ण

अटल अंतरभूत bool kvm_request_pending(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस READ_ONCE(vcpu->requests);
पूर्ण

अटल अंतरभूत bool kvm_test_request(पूर्णांक req, काष्ठा kvm_vcpu *vcpu)
अणु
	वापस test_bit(req & KVM_REQUEST_MASK, (व्योम *)&vcpu->requests);
पूर्ण

अटल अंतरभूत व्योम kvm_clear_request(पूर्णांक req, काष्ठा kvm_vcpu *vcpu)
अणु
	clear_bit(req & KVM_REQUEST_MASK, (व्योम *)&vcpu->requests);
पूर्ण

अटल अंतरभूत bool kvm_check_request(पूर्णांक req, काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (kvm_test_request(req, vcpu)) अणु
		kvm_clear_request(req, vcpu);

		/*
		 * Ensure the rest of the request is visible to kvm_check_request's
		 * caller.  Paired with the smp_wmb in kvm_make_request.
		 */
		smp_mb__after_atomic();
		वापस true;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
पूर्ण

बाह्य bool kvm_rebooting;

बाह्य अचिन्हित पूर्णांक halt_poll_ns;
बाह्य अचिन्हित पूर्णांक halt_poll_ns_grow;
बाह्य अचिन्हित पूर्णांक halt_poll_ns_grow_start;
बाह्य अचिन्हित पूर्णांक halt_poll_ns_shrink;

काष्ठा kvm_device अणु
	स्थिर काष्ठा kvm_device_ops *ops;
	काष्ठा kvm *kvm;
	व्योम *निजी;
	काष्ठा list_head vm_node;
पूर्ण;

/* create, destroy, and name are mandatory */
काष्ठा kvm_device_ops अणु
	स्थिर अक्षर *name;

	/*
	 * create is called holding kvm->lock and any operations not suitable
	 * to करो जबतक holding the lock should be deferred to init (see
	 * below).
	 */
	पूर्णांक (*create)(काष्ठा kvm_device *dev, u32 type);

	/*
	 * init is called after create अगर create is successful and is called
	 * outside of holding kvm->lock.
	 */
	व्योम (*init)(काष्ठा kvm_device *dev);

	/*
	 * Destroy is responsible क्रम मुक्तing dev.
	 *
	 * Destroy may be called beक्रमe or after deकाष्ठाors are called
	 * on emulated I/O regions, depending on whether a reference is
	 * held by a vcpu or other kvm component that माला_लो destroyed
	 * after the emulated I/O.
	 */
	व्योम (*destroy)(काष्ठा kvm_device *dev);

	/*
	 * Release is an alternative method to मुक्त the device. It is
	 * called when the device file descriptor is बंदd. Once
	 * release is called, the destroy method will not be called
	 * anymore as the device is हटाओd from the device list of
	 * the VM. kvm->lock is held.
	 */
	व्योम (*release)(काष्ठा kvm_device *dev);

	पूर्णांक (*set_attr)(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr);
	पूर्णांक (*get_attr)(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr);
	पूर्णांक (*has_attr)(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr);
	दीर्घ (*ioctl)(काष्ठा kvm_device *dev, अचिन्हित पूर्णांक ioctl,
		      अचिन्हित दीर्घ arg);
	पूर्णांक (*mmap)(काष्ठा kvm_device *dev, काष्ठा vm_area_काष्ठा *vma);
पूर्ण;

व्योम kvm_device_get(काष्ठा kvm_device *dev);
व्योम kvm_device_put(काष्ठा kvm_device *dev);
काष्ठा kvm_device *kvm_device_from_filp(काष्ठा file *filp);
पूर्णांक kvm_रेजिस्टर_device_ops(स्थिर काष्ठा kvm_device_ops *ops, u32 type);
व्योम kvm_unरेजिस्टर_device_ops(u32 type);

बाह्य काष्ठा kvm_device_ops kvm_mpic_ops;
बाह्य काष्ठा kvm_device_ops kvm_arm_vgic_v2_ops;
बाह्य काष्ठा kvm_device_ops kvm_arm_vgic_v3_ops;

#अगर_घोषित CONFIG_HAVE_KVM_CPU_RELAX_INTERCEPT

अटल अंतरभूत व्योम kvm_vcpu_set_in_spin_loop(काष्ठा kvm_vcpu *vcpu, bool val)
अणु
	vcpu->spin_loop.in_spin_loop = val;
पूर्ण
अटल अंतरभूत व्योम kvm_vcpu_set_dy_eligible(काष्ठा kvm_vcpu *vcpu, bool val)
अणु
	vcpu->spin_loop.dy_eligible = val;
पूर्ण

#अन्यथा /* !CONFIG_HAVE_KVM_CPU_RELAX_INTERCEPT */

अटल अंतरभूत व्योम kvm_vcpu_set_in_spin_loop(काष्ठा kvm_vcpu *vcpu, bool val)
अणु
पूर्ण

अटल अंतरभूत व्योम kvm_vcpu_set_dy_eligible(काष्ठा kvm_vcpu *vcpu, bool val)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_KVM_CPU_RELAX_INTERCEPT */

अटल अंतरभूत bool kvm_is_visible_memslot(काष्ठा kvm_memory_slot *memslot)
अणु
	वापस (memslot && memslot->id < KVM_USER_MEM_SLOTS &&
		!(memslot->flags & KVM_MEMSLOT_INVALID));
पूर्ण

काष्ठा kvm_vcpu *kvm_get_running_vcpu(व्योम);
काष्ठा kvm_vcpu * __percpu *kvm_get_running_vcpus(व्योम);

#अगर_घोषित CONFIG_HAVE_KVM_IRQ_BYPASS
bool kvm_arch_has_irq_bypass(व्योम);
पूर्णांक kvm_arch_irq_bypass_add_producer(काष्ठा irq_bypass_consumer *,
			   काष्ठा irq_bypass_producer *);
व्योम kvm_arch_irq_bypass_del_producer(काष्ठा irq_bypass_consumer *,
			   काष्ठा irq_bypass_producer *);
व्योम kvm_arch_irq_bypass_stop(काष्ठा irq_bypass_consumer *);
व्योम kvm_arch_irq_bypass_start(काष्ठा irq_bypass_consumer *);
पूर्णांक kvm_arch_update_irqfd_routing(काष्ठा kvm *kvm, अचिन्हित पूर्णांक host_irq,
				  uपूर्णांक32_t guest_irq, bool set);
#पूर्ण_अगर /* CONFIG_HAVE_KVM_IRQ_BYPASS */

#अगर_घोषित CONFIG_HAVE_KVM_INVALID_WAKEUPS
/* If we wakeup during the poll समय, was it a sucessful poll? */
अटल अंतरभूत bool vcpu_valid_wakeup(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->valid_wakeup;
पूर्ण

#अन्यथा
अटल अंतरभूत bool vcpu_valid_wakeup(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_KVM_INVALID_WAKEUPS */

#अगर_घोषित CONFIG_HAVE_KVM_NO_POLL
/* Callback that tells अगर we must not poll */
bool kvm_arch_no_poll(काष्ठा kvm_vcpu *vcpu);
#अन्यथा
अटल अंतरभूत bool kvm_arch_no_poll(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_KVM_NO_POLL */

#अगर_घोषित CONFIG_HAVE_KVM_VCPU_ASYNC_IOCTL
दीर्घ kvm_arch_vcpu_async_ioctl(काष्ठा file *filp,
			       अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg);
#अन्यथा
अटल अंतरभूत दीर्घ kvm_arch_vcpu_async_ioctl(काष्ठा file *filp,
					     अचिन्हित पूर्णांक ioctl,
					     अचिन्हित दीर्घ arg)
अणु
	वापस -ENOIOCTLCMD;
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_KVM_VCPU_ASYNC_IOCTL */

व्योम kvm_arch_mmu_notअगरier_invalidate_range(काष्ठा kvm *kvm,
					    अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

#अगर_घोषित CONFIG_HAVE_KVM_VCPU_RUN_PID_CHANGE
पूर्णांक kvm_arch_vcpu_run_pid_change(काष्ठा kvm_vcpu *vcpu);
#अन्यथा
अटल अंतरभूत पूर्णांक kvm_arch_vcpu_run_pid_change(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_KVM_VCPU_RUN_PID_CHANGE */

प्रकार पूर्णांक (*kvm_vm_thपढ़ो_fn_t)(काष्ठा kvm *kvm, uपूर्णांकptr_t data);

पूर्णांक kvm_vm_create_worker_thपढ़ो(काष्ठा kvm *kvm, kvm_vm_thपढ़ो_fn_t thपढ़ो_fn,
				uपूर्णांकptr_t data, स्थिर अक्षर *name,
				काष्ठा task_काष्ठा **thपढ़ो_ptr);

#अगर_घोषित CONFIG_KVM_XFER_TO_GUEST_WORK
अटल अंतरभूत व्योम kvm_handle_संकेत_निकास(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->run->निकास_reason = KVM_EXIT_INTR;
	vcpu->stat.संकेत_निकासs++;
पूर्ण
#पूर्ण_अगर /* CONFIG_KVM_XFER_TO_GUEST_WORK */

/*
 * This defines how many reserved entries we want to keep beक्रमe we
 * kick the vcpu to the userspace to aव्योम dirty ring full.  This
 * value can be tuned to higher अगर e.g. PML is enabled on the host.
 */
#घोषणा  KVM_सूचीTY_RING_RSVD_ENTRIES  64

/* Max number of entries allowed क्रम each kvm dirty ring */
#घोषणा  KVM_सूचीTY_RING_MAX_ENTRIES  65536

#पूर्ण_अगर
