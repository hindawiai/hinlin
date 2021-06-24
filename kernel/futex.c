<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Fast Userspace Mutexes (which I call "Futexes!").
 *  (C) Rusty Russell, IBM 2002
 *
 *  Generalized futexes, futex requeueing, misc fixes by Ingo Molnar
 *  (C) Copyright 2003 Red Hat Inc, All Rights Reserved
 *
 *  Removed page pinning, fix निजीly mapped COW pages and other cleanups
 *  (C) Copyright 2003, 2004 Jamie Lokier
 *
 *  Robust futex support started by Ingo Molnar
 *  (C) Copyright 2006 Red Hat Inc, All Rights Reserved
 *  Thanks to Thomas Gleixner क्रम suggestions, analysis and fixes.
 *
 *  PI-futex support started by Ingo Molnar and Thomas Gleixner
 *  Copyright (C) 2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *  Copyright (C) 2006 Timesys Corp., Thomas Gleixner <tglx@बारys.com>
 *
 *  PRIVATE futexes by Eric Dumazet
 *  Copyright (C) 2007 Eric Dumazet <dada1@cosmosbay.com>
 *
 *  Requeue-PI support by Darren Hart <dvhltc@us.ibm.com>
 *  Copyright (C) IBM Corporation, 2009
 *  Thanks to Thomas Gleixner क्रम conceptual design and careful reviews.
 *
 *  Thanks to Ben LaHaise क्रम yelling "hashed waitqueues" loudly
 *  enough at me, Linus क्रम the original (flawed) idea, Matthew
 *  Kirkwood क्रम proof-of-concept implementation.
 *
 *  "The futexes are also cursed."
 *  "But they come in a choice of three flavours!"
 */
#समावेश <linux/compat.h>
#समावेश <linux/jhash.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/memblock.h>
#समावेश <linux/fault-inject.h>
#समावेश <linux/समय_namespace.h>

#समावेश <यंत्र/futex.h>

#समावेश "locking/rtmutex_common.h"

/*
 * READ this beक्रमe attempting to hack on futexes!
 *
 * Basic futex operation and ordering guarantees
 * =============================================
 *
 * The रुकोer पढ़ोs the futex value in user space and calls
 * futex_रुको(). This function computes the hash bucket and acquires
 * the hash bucket lock. After that it पढ़ोs the futex user space value
 * again and verअगरies that the data has not changed. If it has not changed
 * it enqueues itself पूर्णांकo the hash bucket, releases the hash bucket lock
 * and schedules.
 *
 * The waker side modअगरies the user space value of the futex and calls
 * futex_wake(). This function computes the hash bucket and acquires the
 * hash bucket lock. Then it looks क्रम रुकोers on that futex in the hash
 * bucket and wakes them.
 *
 * In futex wake up scenarios where no tasks are blocked on a futex, taking
 * the hb spinlock can be aव्योमed and simply वापस. In order क्रम this
 * optimization to work, ordering guarantees must exist so that the रुकोer
 * being added to the list is acknowledged when the list is concurrently being
 * checked by the waker, aव्योमing scenarios like the following:
 *
 * CPU 0                               CPU 1
 * val = *futex;
 * sys_futex(WAIT, futex, val);
 *   futex_रुको(futex, val);
 *   uval = *futex;
 *                                     *futex = newval;
 *                                     sys_futex(WAKE, futex);
 *                                       futex_wake(futex);
 *                                       अगर (queue_empty())
 *                                         वापस;
 *   अगर (uval == val)
 *      lock(hash_bucket(futex));
 *      queue();
 *     unlock(hash_bucket(futex));
 *     schedule();
 *
 * This would cause the रुकोer on CPU 0 to रुको क्रमever because it
 * missed the transition of the user space value from val to newval
 * and the waker did not find the रुकोer in the hash bucket queue.
 *
 * The correct serialization ensures that a रुकोer either observes
 * the changed user space value beक्रमe blocking or is woken by a
 * concurrent waker:
 *
 * CPU 0                                 CPU 1
 * val = *futex;
 * sys_futex(WAIT, futex, val);
 *   futex_रुको(futex, val);
 *
 *   रुकोers++; (a)
 *   smp_mb(); (A) <-- paired with -.
 *                                  |
 *   lock(hash_bucket(futex));      |
 *                                  |
 *   uval = *futex;                 |
 *                                  |        *futex = newval;
 *                                  |        sys_futex(WAKE, futex);
 *                                  |          futex_wake(futex);
 *                                  |
 *                                  `--------> smp_mb(); (B)
 *   अगर (uval == val)
 *     queue();
 *     unlock(hash_bucket(futex));
 *     schedule();                         अगर (रुकोers)
 *                                           lock(hash_bucket(futex));
 *   अन्यथा                                    wake_रुकोers(futex);
 *     रुकोers--; (b)                        unlock(hash_bucket(futex));
 *
 * Where (A) orders the रुकोers increment and the futex value पढ़ो through
 * atomic operations (see hb_रुकोers_inc) and where (B) orders the ग_लिखो
 * to futex and the रुकोers पढ़ो (see hb_रुकोers_pending()).
 *
 * This yields the following हाल (where X:=रुकोers, Y:=futex):
 *
 *	X = Y = 0
 *
 *	w[X]=1		w[Y]=1
 *	MB		MB
 *	r[Y]=y		r[X]=x
 *
 * Which guarantees that x==0 && y==0 is impossible; which translates back पूर्णांकo
 * the guarantee that we cannot both miss the futex variable change and the
 * enqueue.
 *
 * Note that a new रुकोer is accounted क्रम in (a) even when it is possible that
 * the रुको call can वापस error, in which हाल we backtrack from it in (b).
 * Refer to the comment in queue_lock().
 *
 * Similarly, in order to account क्रम रुकोers being requeued on another
 * address we always increment the रुकोers क्रम the destination bucket beक्रमe
 * acquiring the lock. It then decrements them again  after releasing it -
 * the code that actually moves the futex(es) between hash buckets (requeue_futex)
 * will करो the additional required रुकोer count housekeeping. This is करोne क्रम
 * द्विगुन_lock_hb() and द्विगुन_unlock_hb(), respectively.
 */

#अगर_घोषित CONFIG_HAVE_FUTEX_CMPXCHG
#घोषणा futex_cmpxchg_enabled 1
#अन्यथा
अटल पूर्णांक  __पढ़ो_mostly futex_cmpxchg_enabled;
#पूर्ण_अगर

/*
 * Futex flags used to encode options to functions and preserve them across
 * restarts.
 */
#अगर_घोषित CONFIG_MMU
# define FLAGS_SHARED		0x01
#अन्यथा
/*
 * NOMMU करोes not have per process address space. Let the compiler optimize
 * code away.
 */
# define FLAGS_SHARED		0x00
#पूर्ण_अगर
#घोषणा FLAGS_CLOCKRT		0x02
#घोषणा FLAGS_HAS_TIMEOUT	0x04

/*
 * Priority Inheritance state:
 */
काष्ठा futex_pi_state अणु
	/*
	 * list of 'owned' pi_state instances - these have to be
	 * cleaned up in करो_निकास() अगर the task निकासs prematurely:
	 */
	काष्ठा list_head list;

	/*
	 * The PI object:
	 */
	काष्ठा rt_mutex pi_mutex;

	काष्ठा task_काष्ठा *owner;
	refcount_t refcount;

	जोड़ futex_key key;
पूर्ण __अक्रमomize_layout;

/**
 * काष्ठा futex_q - The hashed futex queue entry, one per रुकोing task
 * @list:		priority-sorted list of tasks रुकोing on this futex
 * @task:		the task रुकोing on the futex
 * @lock_ptr:		the hash bucket lock
 * @key:		the key the futex is hashed on
 * @pi_state:		optional priority inheritance state
 * @rt_रुकोer:		rt_रुकोer storage क्रम use with requeue_pi
 * @requeue_pi_key:	the requeue_pi target futex key
 * @bitset:		bitset क्रम the optional biपंचांगasked wakeup
 *
 * We use this hashed रुकोqueue, instead of a normal रुको_queue_entry_t, so
 * we can wake only the relevant ones (hashed queues may be shared).
 *
 * A futex_q has a woken state, just like tasks have TASK_RUNNING.
 * It is considered woken when plist_node_empty(&q->list) || q->lock_ptr == 0.
 * The order of wakeup is always to make the first condition true, then
 * the second.
 *
 * PI futexes are typically woken beक्रमe they are हटाओd from the hash list via
 * the rt_mutex code. See unqueue_me_pi().
 */
काष्ठा futex_q अणु
	काष्ठा plist_node list;

	काष्ठा task_काष्ठा *task;
	spinlock_t *lock_ptr;
	जोड़ futex_key key;
	काष्ठा futex_pi_state *pi_state;
	काष्ठा rt_mutex_रुकोer *rt_रुकोer;
	जोड़ futex_key *requeue_pi_key;
	u32 bitset;
पूर्ण __अक्रमomize_layout;

अटल स्थिर काष्ठा futex_q futex_q_init = अणु
	/* list माला_लो initialized in queue_me()*/
	.key = FUTEX_KEY_INIT,
	.bitset = FUTEX_BITSET_MATCH_ANY
पूर्ण;

/*
 * Hash buckets are shared by all the futex_keys that hash to the same
 * location.  Each key may have multiple futex_q काष्ठाures, one क्रम each task
 * रुकोing on a futex.
 */
काष्ठा futex_hash_bucket अणु
	atomic_t रुकोers;
	spinlock_t lock;
	काष्ठा plist_head chain;
पूर्ण ____cacheline_aligned_in_smp;

/*
 * The base of the bucket array and its size are always used together
 * (after initialization only in hash_futex()), so ensure that they
 * reside in the same cacheline.
 */
अटल काष्ठा अणु
	काष्ठा futex_hash_bucket *queues;
	अचिन्हित दीर्घ            hashsize;
पूर्ण __futex_data __पढ़ो_mostly __aligned(2*माप(दीर्घ));
#घोषणा futex_queues   (__futex_data.queues)
#घोषणा futex_hashsize (__futex_data.hashsize)


/*
 * Fault injections क्रम futexes.
 */
#अगर_घोषित CONFIG_FAIL_FUTEX

अटल काष्ठा अणु
	काष्ठा fault_attr attr;

	bool ignore_निजी;
पूर्ण fail_futex = अणु
	.attr = FAULT_ATTR_INITIALIZER,
	.ignore_निजी = false,
पूर्ण;

अटल पूर्णांक __init setup_fail_futex(अक्षर *str)
अणु
	वापस setup_fault_attr(&fail_futex.attr, str);
पूर्ण
__setup("fail_futex=", setup_fail_futex);

अटल bool should_fail_futex(bool fshared)
अणु
	अगर (fail_futex.ignore_निजी && !fshared)
		वापस false;

	वापस should_fail(&fail_futex.attr, 1);
पूर्ण

#अगर_घोषित CONFIG_FAULT_INJECTION_DEBUG_FS

अटल पूर्णांक __init fail_futex_debugfs(व्योम)
अणु
	umode_t mode = S_IFREG | S_IRUSR | S_IWUSR;
	काष्ठा dentry *dir;

	dir = fault_create_debugfs_attr("fail_futex", शून्य,
					&fail_futex.attr);
	अगर (IS_ERR(dir))
		वापस PTR_ERR(dir);

	debugfs_create_bool("ignore-private", mode, dir,
			    &fail_futex.ignore_निजी);
	वापस 0;
पूर्ण

late_initcall(fail_futex_debugfs);

#पूर्ण_अगर /* CONFIG_FAULT_INJECTION_DEBUG_FS */

#अन्यथा
अटल अंतरभूत bool should_fail_futex(bool fshared)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_FAIL_FUTEX */

#अगर_घोषित CONFIG_COMPAT
अटल व्योम compat_निकास_robust_list(काष्ठा task_काष्ठा *curr);
#पूर्ण_अगर

/*
 * Reflects a new रुकोer being added to the रुकोqueue.
 */
अटल अंतरभूत व्योम hb_रुकोers_inc(काष्ठा futex_hash_bucket *hb)
अणु
#अगर_घोषित CONFIG_SMP
	atomic_inc(&hb->रुकोers);
	/*
	 * Full barrier (A), see the ordering comment above.
	 */
	smp_mb__after_atomic();
#पूर्ण_अगर
पूर्ण

/*
 * Reflects a रुकोer being हटाओd from the रुकोqueue by wakeup
 * paths.
 */
अटल अंतरभूत व्योम hb_रुकोers_dec(काष्ठा futex_hash_bucket *hb)
अणु
#अगर_घोषित CONFIG_SMP
	atomic_dec(&hb->रुकोers);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक hb_रुकोers_pending(काष्ठा futex_hash_bucket *hb)
अणु
#अगर_घोषित CONFIG_SMP
	/*
	 * Full barrier (B), see the ordering comment above.
	 */
	smp_mb();
	वापस atomic_पढ़ो(&hb->रुकोers);
#अन्यथा
	वापस 1;
#पूर्ण_अगर
पूर्ण

/**
 * hash_futex - Return the hash bucket in the global hash
 * @key:	Poपूर्णांकer to the futex key क्रम which the hash is calculated
 *
 * We hash on the keys वापसed from get_futex_key (see below) and वापस the
 * corresponding hash bucket in the global hash.
 */
अटल काष्ठा futex_hash_bucket *hash_futex(जोड़ futex_key *key)
अणु
	u32 hash = jhash2((u32 *)key, दुरत्व(typeof(*key), both.offset) / 4,
			  key->both.offset);

	वापस &futex_queues[hash & (futex_hashsize - 1)];
पूर्ण


/**
 * match_futex - Check whether two futex keys are equal
 * @key1:	Poपूर्णांकer to key1
 * @key2:	Poपूर्णांकer to key2
 *
 * Return 1 अगर two futex_keys are equal, 0 otherwise.
 */
अटल अंतरभूत पूर्णांक match_futex(जोड़ futex_key *key1, जोड़ futex_key *key2)
अणु
	वापस (key1 && key2
		&& key1->both.word == key2->both.word
		&& key1->both.ptr == key2->both.ptr
		&& key1->both.offset == key2->both.offset);
पूर्ण

क्रमागत futex_access अणु
	FUTEX_READ,
	FUTEX_WRITE
पूर्ण;

/**
 * futex_setup_समयr - set up the sleeping hrसमयr.
 * @समय:	ptr to the given समयout value
 * @समयout:	the hrसमयr_sleeper काष्ठाure to be set up
 * @flags:	futex flags
 * @range_ns:	optional range in ns
 *
 * Return: Initialized hrसमयr_sleeper काष्ठाure or शून्य अगर no समयout
 *	   value given
 */
अटल अंतरभूत काष्ठा hrसमयr_sleeper *
futex_setup_समयr(kसमय_प्रकार *समय, काष्ठा hrसमयr_sleeper *समयout,
		  पूर्णांक flags, u64 range_ns)
अणु
	अगर (!समय)
		वापस शून्य;

	hrसमयr_init_sleeper_on_stack(समयout, (flags & FLAGS_CLOCKRT) ?
				      CLOCK_REALTIME : CLOCK_MONOTONIC,
				      HRTIMER_MODE_ABS);
	/*
	 * If range_ns is 0, calling hrसमयr_set_expires_range_ns() is
	 * effectively the same as calling hrसमयr_set_expires().
	 */
	hrसमयr_set_expires_range_ns(&समयout->समयr, *समय, range_ns);

	वापस समयout;
पूर्ण

/*
 * Generate a machine wide unique identअगरier क्रम this inode.
 *
 * This relies on u64 not wrapping in the lअगरe-समय of the machine; which with
 * 1ns resolution means almost 585 years.
 *
 * This further relies on the fact that a well क्रमmed program will not unmap
 * the file जबतक it has a (shared) futex रुकोing on it. This mapping will have
 * a file reference which pins the mount and inode.
 *
 * If क्रम some reason an inode माला_लो evicted and पढ़ो back in again, it will get
 * a new sequence number and will _NOT_ match, even though it is the exact same
 * file.
 *
 * It is important that match_futex() will never have a false-positive, esp.
 * क्रम PI futexes that can mess up the state. The above argues that false-negatives
 * are only possible क्रम malक्रमmed programs.
 */
अटल u64 get_inode_sequence_number(काष्ठा inode *inode)
अणु
	अटल atomic64_t i_seq;
	u64 old;

	/* Does the inode alपढ़ोy have a sequence number? */
	old = atomic64_पढ़ो(&inode->i_sequence);
	अगर (likely(old))
		वापस old;

	क्रम (;;) अणु
		u64 new = atomic64_add_वापस(1, &i_seq);
		अगर (WARN_ON_ONCE(!new))
			जारी;

		old = atomic64_cmpxchg_relaxed(&inode->i_sequence, 0, new);
		अगर (old)
			वापस old;
		वापस new;
	पूर्ण
पूर्ण

/**
 * get_futex_key() - Get parameters which are the keys क्रम a futex
 * @uaddr:	भव address of the futex
 * @fshared:	false क्रम a PROCESS_PRIVATE futex, true क्रम PROCESS_SHARED
 * @key:	address where result is stored.
 * @rw:		mapping needs to be पढ़ो/ग_लिखो (values: FUTEX_READ,
 *              FUTEX_WRITE)
 *
 * Return: a negative error code or 0
 *
 * The key words are stored in @key on success.
 *
 * For shared mappings (when @fshared), the key is:
 *
 *   ( inode->i_sequence, page->index, offset_within_page )
 *
 * [ also see get_inode_sequence_number() ]
 *
 * For निजी mappings (or when !@fshared), the key is:
 *
 *   ( current->mm, address, 0 )
 *
 * This allows (cross process, where applicable) identअगरication of the futex
 * without keeping the page pinned क्रम the duration of the FUTEX_WAIT.
 *
 * lock_page() might sleep, the caller should not hold a spinlock.
 */
अटल पूर्णांक get_futex_key(u32 __user *uaddr, bool fshared, जोड़ futex_key *key,
			 क्रमागत futex_access rw)
अणु
	अचिन्हित दीर्घ address = (अचिन्हित दीर्घ)uaddr;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा page *page, *tail;
	काष्ठा address_space *mapping;
	पूर्णांक err, ro = 0;

	/*
	 * The futex address must be "naturally" aligned.
	 */
	key->both.offset = address % PAGE_SIZE;
	अगर (unlikely((address % माप(u32)) != 0))
		वापस -EINVAL;
	address -= key->both.offset;

	अगर (unlikely(!access_ok(uaddr, माप(u32))))
		वापस -EFAULT;

	अगर (unlikely(should_fail_futex(fshared)))
		वापस -EFAULT;

	/*
	 * PROCESS_PRIVATE futexes are fast.
	 * As the mm cannot disappear under us and the 'key' only needs
	 * भव address, we करोnt even have to find the underlying vma.
	 * Note : We करो have to check 'uaddr' is a valid user address,
	 *        but access_ok() should be faster than find_vma()
	 */
	अगर (!fshared) अणु
		key->निजी.mm = mm;
		key->निजी.address = address;
		वापस 0;
	पूर्ण

again:
	/* Ignore any VERIFY_READ mapping (futex common हाल) */
	अगर (unlikely(should_fail_futex(true)))
		वापस -EFAULT;

	err = get_user_pages_fast(address, 1, FOLL_WRITE, &page);
	/*
	 * If ग_लिखो access is not required (eg. FUTEX_WAIT), try
	 * and get पढ़ो-only access.
	 */
	अगर (err == -EFAULT && rw == FUTEX_READ) अणु
		err = get_user_pages_fast(address, 1, 0, &page);
		ro = 1;
	पूर्ण
	अगर (err < 0)
		वापस err;
	अन्यथा
		err = 0;

	/*
	 * The treaपंचांगent of mapping from this poपूर्णांक on is critical. The page
	 * lock protects many things but in this context the page lock
	 * stabilizes mapping, prevents inode मुक्तing in the shared
	 * file-backed region हाल and guards against movement to swap cache.
	 *
	 * Strictly speaking the page lock is not needed in all हालs being
	 * considered here and page lock क्रमces unnecessarily serialization
	 * From this poपूर्णांक on, mapping will be re-verअगरied अगर necessary and
	 * page lock will be acquired only अगर it is unaव्योमable
	 *
	 * Mapping checks require the head page क्रम any compound page so the
	 * head page and mapping is looked up now. For anonymous pages, it
	 * करोes not matter अगर the page splits in the future as the key is
	 * based on the address. For fileप्रणाली-backed pages, the tail is
	 * required as the index of the page determines the key. For
	 * base pages, there is no tail page and tail == page.
	 */
	tail = page;
	page = compound_head(page);
	mapping = READ_ONCE(page->mapping);

	/*
	 * If page->mapping is शून्य, then it cannot be a PageAnon
	 * page; but it might be the ZERO_PAGE or in the gate area or
	 * in a special mapping (all हालs which we are happy to fail);
	 * or it may have been a good file page when get_user_pages_fast
	 * found it, but truncated or holepunched or subjected to
	 * invalidate_complete_page2 beक्रमe we got the page lock (also
	 * हालs which we are happy to fail).  And we hold a reference,
	 * so refcount care in invalidate_complete_page's हटाओ_mapping
	 * prevents drop_caches from setting mapping to शून्य beneath us.
	 *
	 * The हाल we करो have to guard against is when memory pressure made
	 * shmem_ग_लिखोpage move it from filecache to swapcache beneath us:
	 * an unlikely race, but we करो need to retry क्रम page->mapping.
	 */
	अगर (unlikely(!mapping)) अणु
		पूर्णांक shmem_swizzled;

		/*
		 * Page lock is required to identअगरy which special हाल above
		 * applies. If this is really a shmem page then the page lock
		 * will prevent unexpected transitions.
		 */
		lock_page(page);
		shmem_swizzled = PageSwapCache(page) || page->mapping;
		unlock_page(page);
		put_page(page);

		अगर (shmem_swizzled)
			जाओ again;

		वापस -EFAULT;
	पूर्ण

	/*
	 * Private mappings are handled in a simple way.
	 *
	 * If the futex key is stored on an anonymous page, then the associated
	 * object is the mm which is implicitly pinned by the calling process.
	 *
	 * NOTE: When userspace रुकोs on a MAP_SHARED mapping, even अगर
	 * it's a read-only handle, it's expected that futexes attach to
	 * the object not the particular process.
	 */
	अगर (PageAnon(page)) अणु
		/*
		 * A RO anonymous page will never change and thus करोesn't make
		 * sense क्रम futex operations.
		 */
		अगर (unlikely(should_fail_futex(true)) || ro) अणु
			err = -EFAULT;
			जाओ out;
		पूर्ण

		key->both.offset |= FUT_OFF_MMSHARED; /* ref taken on mm */
		key->निजी.mm = mm;
		key->निजी.address = address;

	पूर्ण अन्यथा अणु
		काष्ठा inode *inode;

		/*
		 * The associated futex object in this हाल is the inode and
		 * the page->mapping must be traversed. Ordinarily this should
		 * be stabilised under page lock but it's not strictly
		 * necessary in this हाल as we just want to pin the inode, not
		 * update the radix tree or anything like that.
		 *
		 * The RCU पढ़ो lock is taken as the inode is finally मुक्तd
		 * under RCU. If the mapping still matches expectations then the
		 * mapping->host can be safely accessed as being a valid inode.
		 */
		rcu_पढ़ो_lock();

		अगर (READ_ONCE(page->mapping) != mapping) अणु
			rcu_पढ़ो_unlock();
			put_page(page);

			जाओ again;
		पूर्ण

		inode = READ_ONCE(mapping->host);
		अगर (!inode) अणु
			rcu_पढ़ो_unlock();
			put_page(page);

			जाओ again;
		पूर्ण

		key->both.offset |= FUT_OFF_INODE; /* inode-based key */
		key->shared.i_seq = get_inode_sequence_number(inode);
		key->shared.pgoff = basepage_index(tail);
		rcu_पढ़ो_unlock();
	पूर्ण

out:
	put_page(page);
	वापस err;
पूर्ण

/**
 * fault_in_user_ग_लिखोable() - Fault in user address and verअगरy RW access
 * @uaddr:	poपूर्णांकer to faulting user space address
 *
 * Slow path to fixup the fault we just took in the atomic ग_लिखो
 * access to @uaddr.
 *
 * We have no generic implementation of a non-deकाष्ठाive ग_लिखो to the
 * user address. We know that we faulted in the atomic pagefault
 * disabled section so we can as well aव्योम the #PF overhead by
 * calling get_user_pages() right away.
 */
अटल पूर्णांक fault_in_user_ग_लिखोable(u32 __user *uaddr)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	पूर्णांक ret;

	mmap_पढ़ो_lock(mm);
	ret = fixup_user_fault(mm, (अचिन्हित दीर्घ)uaddr,
			       FAULT_FLAG_WRITE, शून्य);
	mmap_पढ़ो_unlock(mm);

	वापस ret < 0 ? ret : 0;
पूर्ण

/**
 * futex_top_रुकोer() - Return the highest priority रुकोer on a futex
 * @hb:		the hash bucket the futex_q's reside in
 * @key:	the futex key (to distinguish it from other futex futex_q's)
 *
 * Must be called with the hb lock held.
 */
अटल काष्ठा futex_q *futex_top_रुकोer(काष्ठा futex_hash_bucket *hb,
					जोड़ futex_key *key)
अणु
	काष्ठा futex_q *this;

	plist_क्रम_each_entry(this, &hb->chain, list) अणु
		अगर (match_futex(&this->key, key))
			वापस this;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक cmpxchg_futex_value_locked(u32 *curval, u32 __user *uaddr,
				      u32 uval, u32 newval)
अणु
	पूर्णांक ret;

	pagefault_disable();
	ret = futex_atomic_cmpxchg_inatomic(curval, uaddr, uval, newval);
	pagefault_enable();

	वापस ret;
पूर्ण

अटल पूर्णांक get_futex_value_locked(u32 *dest, u32 __user *from)
अणु
	पूर्णांक ret;

	pagefault_disable();
	ret = __get_user(*dest, from);
	pagefault_enable();

	वापस ret ? -EFAULT : 0;
पूर्ण


/*
 * PI code:
 */
अटल पूर्णांक refill_pi_state_cache(व्योम)
अणु
	काष्ठा futex_pi_state *pi_state;

	अगर (likely(current->pi_state_cache))
		वापस 0;

	pi_state = kzalloc(माप(*pi_state), GFP_KERNEL);

	अगर (!pi_state)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&pi_state->list);
	/* pi_mutex माला_लो initialized later */
	pi_state->owner = शून्य;
	refcount_set(&pi_state->refcount, 1);
	pi_state->key = FUTEX_KEY_INIT;

	current->pi_state_cache = pi_state;

	वापस 0;
पूर्ण

अटल काष्ठा futex_pi_state *alloc_pi_state(व्योम)
अणु
	काष्ठा futex_pi_state *pi_state = current->pi_state_cache;

	WARN_ON(!pi_state);
	current->pi_state_cache = शून्य;

	वापस pi_state;
पूर्ण

अटल व्योम pi_state_update_owner(काष्ठा futex_pi_state *pi_state,
				  काष्ठा task_काष्ठा *new_owner)
अणु
	काष्ठा task_काष्ठा *old_owner = pi_state->owner;

	lockdep_निश्चित_held(&pi_state->pi_mutex.रुको_lock);

	अगर (old_owner) अणु
		raw_spin_lock(&old_owner->pi_lock);
		WARN_ON(list_empty(&pi_state->list));
		list_del_init(&pi_state->list);
		raw_spin_unlock(&old_owner->pi_lock);
	पूर्ण

	अगर (new_owner) अणु
		raw_spin_lock(&new_owner->pi_lock);
		WARN_ON(!list_empty(&pi_state->list));
		list_add(&pi_state->list, &new_owner->pi_state_list);
		pi_state->owner = new_owner;
		raw_spin_unlock(&new_owner->pi_lock);
	पूर्ण
पूर्ण

अटल व्योम get_pi_state(काष्ठा futex_pi_state *pi_state)
अणु
	WARN_ON_ONCE(!refcount_inc_not_zero(&pi_state->refcount));
पूर्ण

/*
 * Drops a reference to the pi_state object and मुक्तs or caches it
 * when the last reference is gone.
 */
अटल व्योम put_pi_state(काष्ठा futex_pi_state *pi_state)
अणु
	अगर (!pi_state)
		वापस;

	अगर (!refcount_dec_and_test(&pi_state->refcount))
		वापस;

	/*
	 * If pi_state->owner is शून्य, the owner is most probably dying
	 * and has cleaned up the pi_state alपढ़ोy
	 */
	अगर (pi_state->owner) अणु
		अचिन्हित दीर्घ flags;

		raw_spin_lock_irqsave(&pi_state->pi_mutex.रुको_lock, flags);
		pi_state_update_owner(pi_state, शून्य);
		rt_mutex_proxy_unlock(&pi_state->pi_mutex);
		raw_spin_unlock_irqrestore(&pi_state->pi_mutex.रुको_lock, flags);
	पूर्ण

	अगर (current->pi_state_cache) अणु
		kमुक्त(pi_state);
	पूर्ण अन्यथा अणु
		/*
		 * pi_state->list is alपढ़ोy empty.
		 * clear pi_state->owner.
		 * refcount is at 0 - put it back to 1.
		 */
		pi_state->owner = शून्य;
		refcount_set(&pi_state->refcount, 1);
		current->pi_state_cache = pi_state;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_FUTEX_PI

/*
 * This task is holding PI mutexes at निकास समय => bad.
 * Kernel cleans up PI-state, but userspace is likely hosed.
 * (Robust-futex cleanup is separate and might save the day क्रम userspace.)
 */
अटल व्योम निकास_pi_state_list(काष्ठा task_काष्ठा *curr)
अणु
	काष्ठा list_head *next, *head = &curr->pi_state_list;
	काष्ठा futex_pi_state *pi_state;
	काष्ठा futex_hash_bucket *hb;
	जोड़ futex_key key = FUTEX_KEY_INIT;

	अगर (!futex_cmpxchg_enabled)
		वापस;
	/*
	 * We are a ZOMBIE and nobody can enqueue itself on
	 * pi_state_list anymore, but we have to be careful
	 * versus रुकोers unqueueing themselves:
	 */
	raw_spin_lock_irq(&curr->pi_lock);
	जबतक (!list_empty(head)) अणु
		next = head->next;
		pi_state = list_entry(next, काष्ठा futex_pi_state, list);
		key = pi_state->key;
		hb = hash_futex(&key);

		/*
		 * We can race against put_pi_state() removing itself from the
		 * list (a रुकोer going away). put_pi_state() will first
		 * decrement the reference count and then modअगरy the list, so
		 * its possible to see the list entry but fail this reference
		 * acquire.
		 *
		 * In that हाल; drop the locks to let put_pi_state() make
		 * progress and retry the loop.
		 */
		अगर (!refcount_inc_not_zero(&pi_state->refcount)) अणु
			raw_spin_unlock_irq(&curr->pi_lock);
			cpu_relax();
			raw_spin_lock_irq(&curr->pi_lock);
			जारी;
		पूर्ण
		raw_spin_unlock_irq(&curr->pi_lock);

		spin_lock(&hb->lock);
		raw_spin_lock_irq(&pi_state->pi_mutex.रुको_lock);
		raw_spin_lock(&curr->pi_lock);
		/*
		 * We dropped the pi-lock, so re-check whether this
		 * task still owns the PI-state:
		 */
		अगर (head->next != next) अणु
			/* retain curr->pi_lock क्रम the loop invariant */
			raw_spin_unlock(&pi_state->pi_mutex.रुको_lock);
			spin_unlock(&hb->lock);
			put_pi_state(pi_state);
			जारी;
		पूर्ण

		WARN_ON(pi_state->owner != curr);
		WARN_ON(list_empty(&pi_state->list));
		list_del_init(&pi_state->list);
		pi_state->owner = शून्य;

		raw_spin_unlock(&curr->pi_lock);
		raw_spin_unlock_irq(&pi_state->pi_mutex.रुको_lock);
		spin_unlock(&hb->lock);

		rt_mutex_futex_unlock(&pi_state->pi_mutex);
		put_pi_state(pi_state);

		raw_spin_lock_irq(&curr->pi_lock);
	पूर्ण
	raw_spin_unlock_irq(&curr->pi_lock);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम निकास_pi_state_list(काष्ठा task_काष्ठा *curr) अणु पूर्ण
#पूर्ण_अगर

/*
 * We need to check the following states:
 *
 *      Waiter | pi_state | pi->owner | uTID      | uODIED | ?
 *
 * [1]  शून्य   | ---      | ---       | 0         | 0/1    | Valid
 * [2]  शून्य   | ---      | ---       | >0        | 0/1    | Valid
 *
 * [3]  Found  | शून्य     | --        | Any       | 0/1    | Invalid
 *
 * [4]  Found  | Found    | शून्य      | 0         | 1      | Valid
 * [5]  Found  | Found    | शून्य      | >0        | 1      | Invalid
 *
 * [6]  Found  | Found    | task      | 0         | 1      | Valid
 *
 * [7]  Found  | Found    | शून्य      | Any       | 0      | Invalid
 *
 * [8]  Found  | Found    | task      | ==taskTID | 0/1    | Valid
 * [9]  Found  | Found    | task      | 0         | 0      | Invalid
 * [10] Found  | Found    | task      | !=taskTID | 0/1    | Invalid
 *
 * [1]	Indicates that the kernel can acquire the futex atomically. We
 *	came here due to a stale FUTEX_WAITERS/FUTEX_OWNER_DIED bit.
 *
 * [2]	Valid, अगर TID करोes not beदीर्घ to a kernel thपढ़ो. If no matching
 *      thपढ़ो is found then it indicates that the owner TID has died.
 *
 * [3]	Invalid. The रुकोer is queued on a non PI futex
 *
 * [4]	Valid state after निकास_robust_list(), which sets the user space
 *	value to FUTEX_WAITERS | FUTEX_OWNER_DIED.
 *
 * [5]	The user space value got manipulated between निकास_robust_list()
 *	and निकास_pi_state_list()
 *
 * [6]	Valid state after निकास_pi_state_list() which sets the new owner in
 *	the pi_state but cannot access the user space value.
 *
 * [7]	pi_state->owner can only be शून्य when the OWNER_DIED bit is set.
 *
 * [8]	Owner and user space value match
 *
 * [9]	There is no transient state which sets the user space TID to 0
 *	except निकास_robust_list(), but this is indicated by the
 *	FUTEX_OWNER_DIED bit. See [4]
 *
 * [10] There is no transient state which leaves owner and user space
 *	TID out of sync. Except one error हाल where the kernel is denied
 *	ग_लिखो access to the user address, see fixup_pi_state_owner().
 *
 *
 * Serialization and lअगरeसमय rules:
 *
 * hb->lock:
 *
 *	hb -> futex_q, relation
 *	futex_q -> pi_state, relation
 *
 *	(cannot be raw because hb can contain arbitrary amount
 *	 of futex_q's)
 *
 * pi_mutex->रुको_lock:
 *
 *	अणुuval, pi_stateपूर्ण
 *
 *	(and pi_mutex 'obviously')
 *
 * p->pi_lock:
 *
 *	p->pi_state_list -> pi_state->list, relation
 *	pi_mutex->owner -> pi_state->owner, relation
 *
 * pi_state->refcount:
 *
 *	pi_state lअगरeसमय
 *
 *
 * Lock order:
 *
 *   hb->lock
 *     pi_mutex->रुको_lock
 *       p->pi_lock
 *
 */

/*
 * Validate that the existing रुकोer has a pi_state and sanity check
 * the pi_state against the user space value. If correct, attach to
 * it.
 */
अटल पूर्णांक attach_to_pi_state(u32 __user *uaddr, u32 uval,
			      काष्ठा futex_pi_state *pi_state,
			      काष्ठा futex_pi_state **ps)
अणु
	pid_t pid = uval & FUTEX_TID_MASK;
	u32 uval2;
	पूर्णांक ret;

	/*
	 * Userspace might have messed up non-PI and PI futexes [3]
	 */
	अगर (unlikely(!pi_state))
		वापस -EINVAL;

	/*
	 * We get here with hb->lock held, and having found a
	 * futex_top_रुकोer(). This means that futex_lock_pi() of said futex_q
	 * has dropped the hb->lock in between queue_me() and unqueue_me_pi(),
	 * which in turn means that futex_lock_pi() still has a reference on
	 * our pi_state.
	 *
	 * The रुकोer holding a reference on @pi_state also protects against
	 * the unlocked put_pi_state() in futex_unlock_pi(), futex_lock_pi()
	 * and futex_रुको_requeue_pi() as it cannot go to 0 and consequently
	 * मुक्त pi_state beक्रमe we can take a reference ourselves.
	 */
	WARN_ON(!refcount_पढ़ो(&pi_state->refcount));

	/*
	 * Now that we have a pi_state, we can acquire रुको_lock
	 * and करो the state validation.
	 */
	raw_spin_lock_irq(&pi_state->pi_mutex.रुको_lock);

	/*
	 * Since अणुuval, pi_stateपूर्ण is serialized by रुको_lock, and our current
	 * uval was पढ़ो without holding it, it can have changed. Verअगरy it
	 * still is what we expect it to be, otherwise retry the entire
	 * operation.
	 */
	अगर (get_futex_value_locked(&uval2, uaddr))
		जाओ out_efault;

	अगर (uval != uval2)
		जाओ out_eagain;

	/*
	 * Handle the owner died हाल:
	 */
	अगर (uval & FUTEX_OWNER_DIED) अणु
		/*
		 * निकास_pi_state_list sets owner to शून्य and wakes the
		 * topmost रुकोer. The task which acquires the
		 * pi_state->rt_mutex will fixup owner.
		 */
		अगर (!pi_state->owner) अणु
			/*
			 * No pi state owner, but the user space TID
			 * is not 0. Inconsistent state. [5]
			 */
			अगर (pid)
				जाओ out_einval;
			/*
			 * Take a ref on the state and वापस success. [4]
			 */
			जाओ out_attach;
		पूर्ण

		/*
		 * If TID is 0, then either the dying owner has not
		 * yet executed निकास_pi_state_list() or some रुकोer
		 * acquired the rपंचांगutex in the pi state, but did not
		 * yet fixup the TID in user space.
		 *
		 * Take a ref on the state and वापस success. [6]
		 */
		अगर (!pid)
			जाओ out_attach;
	पूर्ण अन्यथा अणु
		/*
		 * If the owner died bit is not set, then the pi_state
		 * must have an owner. [7]
		 */
		अगर (!pi_state->owner)
			जाओ out_einval;
	पूर्ण

	/*
	 * Bail out अगर user space manipulated the futex value. If pi
	 * state exists then the owner TID must be the same as the
	 * user space TID. [9/10]
	 */
	अगर (pid != task_pid_vnr(pi_state->owner))
		जाओ out_einval;

out_attach:
	get_pi_state(pi_state);
	raw_spin_unlock_irq(&pi_state->pi_mutex.रुको_lock);
	*ps = pi_state;
	वापस 0;

out_einval:
	ret = -EINVAL;
	जाओ out_error;

out_eagain:
	ret = -EAGAIN;
	जाओ out_error;

out_efault:
	ret = -EFAULT;
	जाओ out_error;

out_error:
	raw_spin_unlock_irq(&pi_state->pi_mutex.रुको_lock);
	वापस ret;
पूर्ण

/**
 * रुको_क्रम_owner_निकासing - Block until the owner has निकासed
 * @ret: owner's current futex lock status
 * @निकासing:	Poपूर्णांकer to the निकासing task
 *
 * Caller must hold a refcount on @निकासing.
 */
अटल व्योम रुको_क्रम_owner_निकासing(पूर्णांक ret, काष्ठा task_काष्ठा *निकासing)
अणु
	अगर (ret != -EBUSY) अणु
		WARN_ON_ONCE(निकासing);
		वापस;
	पूर्ण

	अगर (WARN_ON_ONCE(ret == -EBUSY && !निकासing))
		वापस;

	mutex_lock(&निकासing->futex_निकास_mutex);
	/*
	 * No poपूर्णांक in करोing state checking here. If the रुकोer got here
	 * जबतक the task was in exec()->exec_futex_release() then it can
	 * have any FUTEX_STATE_* value when the रुकोer has acquired the
	 * mutex. OK, अगर running, EXITING or DEAD अगर it reached निकास()
	 * alपढ़ोy. Highly unlikely and not a problem. Just one more round
	 * through the futex maze.
	 */
	mutex_unlock(&निकासing->futex_निकास_mutex);

	put_task_काष्ठा(निकासing);
पूर्ण

अटल पूर्णांक handle_निकास_race(u32 __user *uaddr, u32 uval,
			    काष्ठा task_काष्ठा *tsk)
अणु
	u32 uval2;

	/*
	 * If the futex निकास state is not yet FUTEX_STATE_DEAD, tell the
	 * caller that the alleged owner is busy.
	 */
	अगर (tsk && tsk->futex_state != FUTEX_STATE_DEAD)
		वापस -EBUSY;

	/*
	 * Reपढ़ो the user space value to handle the following situation:
	 *
	 * CPU0				CPU1
	 *
	 * sys_निकास()			sys_futex()
	 *  करो_निकास()			 futex_lock_pi()
	 *                                futex_lock_pi_atomic()
	 *   निकास_संकेतs(tsk)		    No रुकोers:
	 *    tsk->flags |= PF_EXITING;	    *uaddr == 0x00000PID
	 *  mm_release(tsk)		    Set रुकोer bit
	 *   निकास_robust_list(tsk) अणु	    *uaddr = 0x80000PID;
	 *      Set owner died		    attach_to_pi_owner() अणु
	 *    *uaddr = 0xC0000000;	     tsk = get_task(PID);
	 *   पूर्ण				     अगर (!tsk->flags & PF_EXITING) अणु
	 *  ...				       attach();
	 *  tsk->futex_state =               पूर्ण अन्यथा अणु
	 *	FUTEX_STATE_DEAD;              अगर (tsk->futex_state !=
	 *					  FUTEX_STATE_DEAD)
	 *				         वापस -EAGAIN;
	 *				       वापस -ESRCH; <--- FAIL
	 *				     पूर्ण
	 *
	 * Returning ESRCH unconditionally is wrong here because the
	 * user space value has been changed by the निकासing task.
	 *
	 * The same logic applies to the हाल where the निकासing task is
	 * alपढ़ोy gone.
	 */
	अगर (get_futex_value_locked(&uval2, uaddr))
		वापस -EFAULT;

	/* If the user space value has changed, try again. */
	अगर (uval2 != uval)
		वापस -EAGAIN;

	/*
	 * The निकासing task did not have a robust list, the robust list was
	 * corrupted or the user space value in *uaddr is simply bogus.
	 * Give up and tell user space.
	 */
	वापस -ESRCH;
पूर्ण

/*
 * Lookup the task क्रम the TID provided from user space and attach to
 * it after करोing proper sanity checks.
 */
अटल पूर्णांक attach_to_pi_owner(u32 __user *uaddr, u32 uval, जोड़ futex_key *key,
			      काष्ठा futex_pi_state **ps,
			      काष्ठा task_काष्ठा **निकासing)
अणु
	pid_t pid = uval & FUTEX_TID_MASK;
	काष्ठा futex_pi_state *pi_state;
	काष्ठा task_काष्ठा *p;

	/*
	 * We are the first रुकोer - try to look up the real owner and attach
	 * the new pi_state to it, but bail out when TID = 0 [1]
	 *
	 * The !pid check is paranoid. None of the call sites should end up
	 * with pid == 0, but better safe than sorry. Let the caller retry
	 */
	अगर (!pid)
		वापस -EAGAIN;
	p = find_get_task_by_vpid(pid);
	अगर (!p)
		वापस handle_निकास_race(uaddr, uval, शून्य);

	अगर (unlikely(p->flags & PF_KTHREAD)) अणु
		put_task_काष्ठा(p);
		वापस -EPERM;
	पूर्ण

	/*
	 * We need to look at the task state to figure out, whether the
	 * task is निकासing. To protect against the change of the task state
	 * in futex_निकास_release(), we करो this रक्षित by p->pi_lock:
	 */
	raw_spin_lock_irq(&p->pi_lock);
	अगर (unlikely(p->futex_state != FUTEX_STATE_OK)) अणु
		/*
		 * The task is on the way out. When the futex state is
		 * FUTEX_STATE_DEAD, we know that the task has finished
		 * the cleanup:
		 */
		पूर्णांक ret = handle_निकास_race(uaddr, uval, p);

		raw_spin_unlock_irq(&p->pi_lock);
		/*
		 * If the owner task is between FUTEX_STATE_EXITING and
		 * FUTEX_STATE_DEAD then store the task poपूर्णांकer and keep
		 * the reference on the task काष्ठा. The calling code will
		 * drop all locks, रुको क्रम the task to reach
		 * FUTEX_STATE_DEAD and then drop the refcount. This is
		 * required to prevent a live lock when the current task
		 * preempted the निकासing task between the two states.
		 */
		अगर (ret == -EBUSY)
			*निकासing = p;
		अन्यथा
			put_task_काष्ठा(p);
		वापस ret;
	पूर्ण

	/*
	 * No existing pi state. First रुकोer. [2]
	 *
	 * This creates pi_state, we have hb->lock held, this means nothing can
	 * observe this state, रुको_lock is irrelevant.
	 */
	pi_state = alloc_pi_state();

	/*
	 * Initialize the pi_mutex in locked state and make @p
	 * the owner of it:
	 */
	rt_mutex_init_proxy_locked(&pi_state->pi_mutex, p);

	/* Store the key क्रम possible निकास cleanups: */
	pi_state->key = *key;

	WARN_ON(!list_empty(&pi_state->list));
	list_add(&pi_state->list, &p->pi_state_list);
	/*
	 * Assignment without holding pi_state->pi_mutex.रुको_lock is safe
	 * because there is no concurrency as the object is not published yet.
	 */
	pi_state->owner = p;
	raw_spin_unlock_irq(&p->pi_lock);

	put_task_काष्ठा(p);

	*ps = pi_state;

	वापस 0;
पूर्ण

अटल पूर्णांक lookup_pi_state(u32 __user *uaddr, u32 uval,
			   काष्ठा futex_hash_bucket *hb,
			   जोड़ futex_key *key, काष्ठा futex_pi_state **ps,
			   काष्ठा task_काष्ठा **निकासing)
अणु
	काष्ठा futex_q *top_रुकोer = futex_top_रुकोer(hb, key);

	/*
	 * If there is a रुकोer on that futex, validate it and
	 * attach to the pi_state when the validation succeeds.
	 */
	अगर (top_रुकोer)
		वापस attach_to_pi_state(uaddr, uval, top_रुकोer->pi_state, ps);

	/*
	 * We are the first रुकोer - try to look up the owner based on
	 * @uval and attach to it.
	 */
	वापस attach_to_pi_owner(uaddr, uval, key, ps, निकासing);
पूर्ण

अटल पूर्णांक lock_pi_update_atomic(u32 __user *uaddr, u32 uval, u32 newval)
अणु
	पूर्णांक err;
	u32 curval;

	अगर (unlikely(should_fail_futex(true)))
		वापस -EFAULT;

	err = cmpxchg_futex_value_locked(&curval, uaddr, uval, newval);
	अगर (unlikely(err))
		वापस err;

	/* If user space value changed, let the caller retry */
	वापस curval != uval ? -EAGAIN : 0;
पूर्ण

/**
 * futex_lock_pi_atomic() - Atomic work required to acquire a pi aware futex
 * @uaddr:		the pi futex user address
 * @hb:			the pi futex hash bucket
 * @key:		the futex key associated with uaddr and hb
 * @ps:			the pi_state poपूर्णांकer where we store the result of the
 *			lookup
 * @task:		the task to perक्रमm the atomic lock work क्रम.  This will
 *			be "current" except in the हाल of requeue pi.
 * @निकासing:		Poपूर्णांकer to store the task poपूर्णांकer of the owner task
 *			which is in the middle of निकासing
 * @set_रुकोers:	क्रमce setting the FUTEX_WAITERS bit (1) or not (0)
 *
 * Return:
 *  -  0 - पढ़ोy to रुको;
 *  -  1 - acquired the lock;
 *  - <0 - error
 *
 * The hb->lock and futex_key refs shall be held by the caller.
 *
 * @निकासing is only set when the वापस value is -EBUSY. If so, this holds
 * a refcount on the निकासing task on वापस and the caller needs to drop it
 * after रुकोing क्रम the निकास to complete.
 */
अटल पूर्णांक futex_lock_pi_atomic(u32 __user *uaddr, काष्ठा futex_hash_bucket *hb,
				जोड़ futex_key *key,
				काष्ठा futex_pi_state **ps,
				काष्ठा task_काष्ठा *task,
				काष्ठा task_काष्ठा **निकासing,
				पूर्णांक set_रुकोers)
अणु
	u32 uval, newval, vpid = task_pid_vnr(task);
	काष्ठा futex_q *top_रुकोer;
	पूर्णांक ret;

	/*
	 * Read the user space value first so we can validate a few
	 * things beक्रमe proceeding further.
	 */
	अगर (get_futex_value_locked(&uval, uaddr))
		वापस -EFAULT;

	अगर (unlikely(should_fail_futex(true)))
		वापस -EFAULT;

	/*
	 * Detect deadlocks.
	 */
	अगर ((unlikely((uval & FUTEX_TID_MASK) == vpid)))
		वापस -EDEADLK;

	अगर ((unlikely(should_fail_futex(true))))
		वापस -EDEADLK;

	/*
	 * Lookup existing state first. If it exists, try to attach to
	 * its pi_state.
	 */
	top_रुकोer = futex_top_रुकोer(hb, key);
	अगर (top_रुकोer)
		वापस attach_to_pi_state(uaddr, uval, top_रुकोer->pi_state, ps);

	/*
	 * No रुकोer and user TID is 0. We are here because the
	 * रुकोers or the owner died bit is set or called from
	 * requeue_cmp_pi or क्रम whatever reason something took the
	 * syscall.
	 */
	अगर (!(uval & FUTEX_TID_MASK)) अणु
		/*
		 * We take over the futex. No other रुकोers and the user space
		 * TID is 0. We preserve the owner died bit.
		 */
		newval = uval & FUTEX_OWNER_DIED;
		newval |= vpid;

		/* The futex requeue_pi code can enक्रमce the रुकोers bit */
		अगर (set_रुकोers)
			newval |= FUTEX_WAITERS;

		ret = lock_pi_update_atomic(uaddr, uval, newval);
		/* If the take over worked, वापस 1 */
		वापस ret < 0 ? ret : 1;
	पूर्ण

	/*
	 * First रुकोer. Set the रुकोers bit beक्रमe attaching ourself to
	 * the owner. If owner tries to unlock, it will be क्रमced पूर्णांकo
	 * the kernel and blocked on hb->lock.
	 */
	newval = uval | FUTEX_WAITERS;
	ret = lock_pi_update_atomic(uaddr, uval, newval);
	अगर (ret)
		वापस ret;
	/*
	 * If the update of the user space value succeeded, we try to
	 * attach to the owner. If that fails, no harm करोne, we only
	 * set the FUTEX_WAITERS bit in the user space variable.
	 */
	वापस attach_to_pi_owner(uaddr, newval, key, ps, निकासing);
पूर्ण

/**
 * __unqueue_futex() - Remove the futex_q from its futex_hash_bucket
 * @q:	The futex_q to unqueue
 *
 * The q->lock_ptr must not be शून्य and must be held by the caller.
 */
अटल व्योम __unqueue_futex(काष्ठा futex_q *q)
अणु
	काष्ठा futex_hash_bucket *hb;

	अगर (WARN_ON_SMP(!q->lock_ptr) || WARN_ON(plist_node_empty(&q->list)))
		वापस;
	lockdep_निश्चित_held(q->lock_ptr);

	hb = container_of(q->lock_ptr, काष्ठा futex_hash_bucket, lock);
	plist_del(&q->list, &hb->chain);
	hb_रुकोers_dec(hb);
पूर्ण

/*
 * The hash bucket lock must be held when this is called.
 * Afterwards, the futex_q must not be accessed. Callers
 * must ensure to later call wake_up_q() क्रम the actual
 * wakeups to occur.
 */
अटल व्योम mark_wake_futex(काष्ठा wake_q_head *wake_q, काष्ठा futex_q *q)
अणु
	काष्ठा task_काष्ठा *p = q->task;

	अगर (WARN(q->pi_state || q->rt_रुकोer, "refusing to wake PI futex\n"))
		वापस;

	get_task_काष्ठा(p);
	__unqueue_futex(q);
	/*
	 * The रुकोing task can मुक्त the futex_q as soon as q->lock_ptr = शून्य
	 * is written, without taking any locks. This is possible in the event
	 * of a spurious wakeup, क्रम example. A memory barrier is required here
	 * to prevent the following store to lock_ptr from getting ahead of the
	 * plist_del in __unqueue_futex().
	 */
	smp_store_release(&q->lock_ptr, शून्य);

	/*
	 * Queue the task क्रम later wakeup क्रम after we've released
	 * the hb->lock.
	 */
	wake_q_add_safe(wake_q, p);
पूर्ण

/*
 * Caller must hold a reference on @pi_state.
 */
अटल पूर्णांक wake_futex_pi(u32 __user *uaddr, u32 uval, काष्ठा futex_pi_state *pi_state)
अणु
	u32 curval, newval;
	काष्ठा rt_mutex_रुकोer *top_रुकोer;
	काष्ठा task_काष्ठा *new_owner;
	bool postunlock = false;
	DEFINE_WAKE_Q(wake_q);
	पूर्णांक ret = 0;

	top_रुकोer = rt_mutex_top_रुकोer(&pi_state->pi_mutex);
	अगर (WARN_ON_ONCE(!top_रुकोer)) अणु
		/*
		 * As per the comment in futex_unlock_pi() this should not happen.
		 *
		 * When this happens, give up our locks and try again, giving
		 * the futex_lock_pi() instance समय to complete, either by
		 * रुकोing on the rपंचांगutex or removing itself from the futex
		 * queue.
		 */
		ret = -EAGAIN;
		जाओ out_unlock;
	पूर्ण

	new_owner = top_रुकोer->task;

	/*
	 * We pass it to the next owner. The WAITERS bit is always kept
	 * enabled जबतक there is PI state around. We cleanup the owner
	 * died bit, because we are the owner.
	 */
	newval = FUTEX_WAITERS | task_pid_vnr(new_owner);

	अगर (unlikely(should_fail_futex(true))) अणु
		ret = -EFAULT;
		जाओ out_unlock;
	पूर्ण

	ret = cmpxchg_futex_value_locked(&curval, uaddr, uval, newval);
	अगर (!ret && (curval != uval)) अणु
		/*
		 * If a unconditional UNLOCK_PI operation (user space did not
		 * try the TID->0 transition) raced with a रुकोer setting the
		 * FUTEX_WAITERS flag between get_user() and locking the hash
		 * bucket lock, retry the operation.
		 */
		अगर ((FUTEX_TID_MASK & curval) == uval)
			ret = -EAGAIN;
		अन्यथा
			ret = -EINVAL;
	पूर्ण

	अगर (!ret) अणु
		/*
		 * This is a poपूर्णांक of no वापस; once we modअगरied the uval
		 * there is no going back and subsequent operations must
		 * not fail.
		 */
		pi_state_update_owner(pi_state, new_owner);
		postunlock = __rt_mutex_futex_unlock(&pi_state->pi_mutex, &wake_q);
	पूर्ण

out_unlock:
	raw_spin_unlock_irq(&pi_state->pi_mutex.रुको_lock);

	अगर (postunlock)
		rt_mutex_postunlock(&wake_q);

	वापस ret;
पूर्ण

/*
 * Express the locking dependencies क्रम lockdep:
 */
अटल अंतरभूत व्योम
द्विगुन_lock_hb(काष्ठा futex_hash_bucket *hb1, काष्ठा futex_hash_bucket *hb2)
अणु
	अगर (hb1 <= hb2) अणु
		spin_lock(&hb1->lock);
		अगर (hb1 < hb2)
			spin_lock_nested(&hb2->lock, SINGLE_DEPTH_NESTING);
	पूर्ण अन्यथा अणु /* hb1 > hb2 */
		spin_lock(&hb2->lock);
		spin_lock_nested(&hb1->lock, SINGLE_DEPTH_NESTING);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
द्विगुन_unlock_hb(काष्ठा futex_hash_bucket *hb1, काष्ठा futex_hash_bucket *hb2)
अणु
	spin_unlock(&hb1->lock);
	अगर (hb1 != hb2)
		spin_unlock(&hb2->lock);
पूर्ण

/*
 * Wake up रुकोers matching bitset queued on this futex (uaddr).
 */
अटल पूर्णांक
futex_wake(u32 __user *uaddr, अचिन्हित पूर्णांक flags, पूर्णांक nr_wake, u32 bitset)
अणु
	काष्ठा futex_hash_bucket *hb;
	काष्ठा futex_q *this, *next;
	जोड़ futex_key key = FUTEX_KEY_INIT;
	पूर्णांक ret;
	DEFINE_WAKE_Q(wake_q);

	अगर (!bitset)
		वापस -EINVAL;

	ret = get_futex_key(uaddr, flags & FLAGS_SHARED, &key, FUTEX_READ);
	अगर (unlikely(ret != 0))
		वापस ret;

	hb = hash_futex(&key);

	/* Make sure we really have tasks to wakeup */
	अगर (!hb_रुकोers_pending(hb))
		वापस ret;

	spin_lock(&hb->lock);

	plist_क्रम_each_entry_safe(this, next, &hb->chain, list) अणु
		अगर (match_futex (&this->key, &key)) अणु
			अगर (this->pi_state || this->rt_रुकोer) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			/* Check अगर one of the bits is set in both bitsets */
			अगर (!(this->bitset & bitset))
				जारी;

			mark_wake_futex(&wake_q, this);
			अगर (++ret >= nr_wake)
				अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&hb->lock);
	wake_up_q(&wake_q);
	वापस ret;
पूर्ण

अटल पूर्णांक futex_atomic_op_inuser(अचिन्हित पूर्णांक encoded_op, u32 __user *uaddr)
अणु
	अचिन्हित पूर्णांक op =	  (encoded_op & 0x70000000) >> 28;
	अचिन्हित पूर्णांक cmp =	  (encoded_op & 0x0f000000) >> 24;
	पूर्णांक oparg = sign_extend32((encoded_op & 0x00fff000) >> 12, 11);
	पूर्णांक cmparg = sign_extend32(encoded_op & 0x00000fff, 11);
	पूर्णांक oldval, ret;

	अगर (encoded_op & (FUTEX_OP_OPARG_SHIFT << 28)) अणु
		अगर (oparg < 0 || oparg > 31) अणु
			अक्षर comm[माप(current->comm)];
			/*
			 * समाप्त this prपूर्णांक and वापस -EINVAL when userspace
			 * is sane again
			 */
			pr_info_ratelimited("futex_wake_op: %s tries to shift op by %d; fix this program\n",
					get_task_comm(comm, current), oparg);
			oparg &= 31;
		पूर्ण
		oparg = 1 << oparg;
	पूर्ण

	pagefault_disable();
	ret = arch_futex_atomic_op_inuser(op, oparg, &oldval, uaddr);
	pagefault_enable();
	अगर (ret)
		वापस ret;

	चयन (cmp) अणु
	हाल FUTEX_OP_CMP_EQ:
		वापस oldval == cmparg;
	हाल FUTEX_OP_CMP_NE:
		वापस oldval != cmparg;
	हाल FUTEX_OP_CMP_LT:
		वापस oldval < cmparg;
	हाल FUTEX_OP_CMP_GE:
		वापस oldval >= cmparg;
	हाल FUTEX_OP_CMP_LE:
		वापस oldval <= cmparg;
	हाल FUTEX_OP_CMP_GT:
		वापस oldval > cmparg;
	शेष:
		वापस -ENOSYS;
	पूर्ण
पूर्ण

/*
 * Wake up all रुकोers hashed on the physical page that is mapped
 * to this भव address:
 */
अटल पूर्णांक
futex_wake_op(u32 __user *uaddr1, अचिन्हित पूर्णांक flags, u32 __user *uaddr2,
	      पूर्णांक nr_wake, पूर्णांक nr_wake2, पूर्णांक op)
अणु
	जोड़ futex_key key1 = FUTEX_KEY_INIT, key2 = FUTEX_KEY_INIT;
	काष्ठा futex_hash_bucket *hb1, *hb2;
	काष्ठा futex_q *this, *next;
	पूर्णांक ret, op_ret;
	DEFINE_WAKE_Q(wake_q);

retry:
	ret = get_futex_key(uaddr1, flags & FLAGS_SHARED, &key1, FUTEX_READ);
	अगर (unlikely(ret != 0))
		वापस ret;
	ret = get_futex_key(uaddr2, flags & FLAGS_SHARED, &key2, FUTEX_WRITE);
	अगर (unlikely(ret != 0))
		वापस ret;

	hb1 = hash_futex(&key1);
	hb2 = hash_futex(&key2);

retry_निजी:
	द्विगुन_lock_hb(hb1, hb2);
	op_ret = futex_atomic_op_inuser(op, uaddr2);
	अगर (unlikely(op_ret < 0)) अणु
		द्विगुन_unlock_hb(hb1, hb2);

		अगर (!IS_ENABLED(CONFIG_MMU) ||
		    unlikely(op_ret != -EFAULT && op_ret != -EAGAIN)) अणु
			/*
			 * we करोn't get EFAULT from MMU faults if we don't have
			 * an MMU, but we might get them from range checking
			 */
			ret = op_ret;
			वापस ret;
		पूर्ण

		अगर (op_ret == -EFAULT) अणु
			ret = fault_in_user_ग_लिखोable(uaddr2);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (!(flags & FLAGS_SHARED)) अणु
			cond_resched();
			जाओ retry_निजी;
		पूर्ण

		cond_resched();
		जाओ retry;
	पूर्ण

	plist_क्रम_each_entry_safe(this, next, &hb1->chain, list) अणु
		अगर (match_futex (&this->key, &key1)) अणु
			अगर (this->pi_state || this->rt_रुकोer) अणु
				ret = -EINVAL;
				जाओ out_unlock;
			पूर्ण
			mark_wake_futex(&wake_q, this);
			अगर (++ret >= nr_wake)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (op_ret > 0) अणु
		op_ret = 0;
		plist_क्रम_each_entry_safe(this, next, &hb2->chain, list) अणु
			अगर (match_futex (&this->key, &key2)) अणु
				अगर (this->pi_state || this->rt_रुकोer) अणु
					ret = -EINVAL;
					जाओ out_unlock;
				पूर्ण
				mark_wake_futex(&wake_q, this);
				अगर (++op_ret >= nr_wake2)
					अवरोध;
			पूर्ण
		पूर्ण
		ret += op_ret;
	पूर्ण

out_unlock:
	द्विगुन_unlock_hb(hb1, hb2);
	wake_up_q(&wake_q);
	वापस ret;
पूर्ण

/**
 * requeue_futex() - Requeue a futex_q from one hb to another
 * @q:		the futex_q to requeue
 * @hb1:	the source hash_bucket
 * @hb2:	the target hash_bucket
 * @key2:	the new key क्रम the requeued futex_q
 */
अटल अंतरभूत
व्योम requeue_futex(काष्ठा futex_q *q, काष्ठा futex_hash_bucket *hb1,
		   काष्ठा futex_hash_bucket *hb2, जोड़ futex_key *key2)
अणु

	/*
	 * If key1 and key2 hash to the same bucket, no need to
	 * requeue.
	 */
	अगर (likely(&hb1->chain != &hb2->chain)) अणु
		plist_del(&q->list, &hb1->chain);
		hb_रुकोers_dec(hb1);
		hb_रुकोers_inc(hb2);
		plist_add(&q->list, &hb2->chain);
		q->lock_ptr = &hb2->lock;
	पूर्ण
	q->key = *key2;
पूर्ण

/**
 * requeue_pi_wake_futex() - Wake a task that acquired the lock during requeue
 * @q:		the futex_q
 * @key:	the key of the requeue target futex
 * @hb:		the hash_bucket of the requeue target futex
 *
 * During futex_requeue, with requeue_pi=1, it is possible to acquire the
 * target futex अगर it is uncontended or via a lock steal.  Set the futex_q key
 * to the requeue target futex so the रुकोer can detect the wakeup on the right
 * futex, but हटाओ it from the hb and शून्य the rt_रुकोer so it can detect
 * atomic lock acquisition.  Set the q->lock_ptr to the requeue target hb->lock
 * to protect access to the pi_state to fixup the owner later.  Must be called
 * with both q->lock_ptr and hb->lock held.
 */
अटल अंतरभूत
व्योम requeue_pi_wake_futex(काष्ठा futex_q *q, जोड़ futex_key *key,
			   काष्ठा futex_hash_bucket *hb)
अणु
	q->key = *key;

	__unqueue_futex(q);

	WARN_ON(!q->rt_रुकोer);
	q->rt_रुकोer = शून्य;

	q->lock_ptr = &hb->lock;

	wake_up_state(q->task, TASK_NORMAL);
पूर्ण

/**
 * futex_proxy_trylock_atomic() - Attempt an atomic lock क्रम the top रुकोer
 * @pअगरutex:		the user address of the to futex
 * @hb1:		the from futex hash bucket, must be locked by the caller
 * @hb2:		the to futex hash bucket, must be locked by the caller
 * @key1:		the from futex key
 * @key2:		the to futex key
 * @ps:			address to store the pi_state poपूर्णांकer
 * @निकासing:		Poपूर्णांकer to store the task poपूर्णांकer of the owner task
 *			which is in the middle of निकासing
 * @set_रुकोers:	क्रमce setting the FUTEX_WAITERS bit (1) or not (0)
 *
 * Try and get the lock on behalf of the top रुकोer अगर we can करो it atomically.
 * Wake the top रुकोer अगर we succeed.  If the caller specअगरied set_रुकोers,
 * then direct futex_lock_pi_atomic() to क्रमce setting the FUTEX_WAITERS bit.
 * hb1 and hb2 must be held by the caller.
 *
 * @निकासing is only set when the वापस value is -EBUSY. If so, this holds
 * a refcount on the निकासing task on वापस and the caller needs to drop it
 * after रुकोing क्रम the निकास to complete.
 *
 * Return:
 *  -  0 - failed to acquire the lock atomically;
 *  - >0 - acquired the lock, वापस value is vpid of the top_रुकोer
 *  - <0 - error
 */
अटल पूर्णांक
futex_proxy_trylock_atomic(u32 __user *pअगरutex, काष्ठा futex_hash_bucket *hb1,
			   काष्ठा futex_hash_bucket *hb2, जोड़ futex_key *key1,
			   जोड़ futex_key *key2, काष्ठा futex_pi_state **ps,
			   काष्ठा task_काष्ठा **निकासing, पूर्णांक set_रुकोers)
अणु
	काष्ठा futex_q *top_रुकोer = शून्य;
	u32 curval;
	पूर्णांक ret, vpid;

	अगर (get_futex_value_locked(&curval, pअगरutex))
		वापस -EFAULT;

	अगर (unlikely(should_fail_futex(true)))
		वापस -EFAULT;

	/*
	 * Find the top_रुकोer and determine अगर there are additional रुकोers.
	 * If the caller पूर्णांकends to requeue more than 1 रुकोer to pअगरutex,
	 * क्रमce futex_lock_pi_atomic() to set the FUTEX_WAITERS bit now,
	 * as we have means to handle the possible fault.  If not, करोn't set
	 * the bit unecessarily as it will क्रमce the subsequent unlock to enter
	 * the kernel.
	 */
	top_रुकोer = futex_top_रुकोer(hb1, key1);

	/* There are no रुकोers, nothing क्रम us to करो. */
	अगर (!top_रुकोer)
		वापस 0;

	/* Ensure we requeue to the expected futex. */
	अगर (!match_futex(top_रुकोer->requeue_pi_key, key2))
		वापस -EINVAL;

	/*
	 * Try to take the lock क्रम top_रुकोer.  Set the FUTEX_WAITERS bit in
	 * the contended हाल or अगर set_रुकोers is 1.  The pi_state is वापसed
	 * in ps in contended हालs.
	 */
	vpid = task_pid_vnr(top_रुकोer->task);
	ret = futex_lock_pi_atomic(pअगरutex, hb2, key2, ps, top_रुकोer->task,
				   निकासing, set_रुकोers);
	अगर (ret == 1) अणु
		requeue_pi_wake_futex(top_रुकोer, key2, hb2);
		वापस vpid;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * futex_requeue() - Requeue रुकोers from uaddr1 to uaddr2
 * @uaddr1:	source futex user address
 * @flags:	futex flags (FLAGS_SHARED, etc.)
 * @uaddr2:	target futex user address
 * @nr_wake:	number of रुकोers to wake (must be 1 क्रम requeue_pi)
 * @nr_requeue:	number of रुकोers to requeue (0-पूर्णांक_उच्च)
 * @cmpval:	@uaddr1 expected value (or %शून्य)
 * @requeue_pi:	अगर we are attempting to requeue from a non-pi futex to a
 *		pi futex (pi to pi requeue is not supported)
 *
 * Requeue रुकोers on uaddr1 to uaddr2. In the requeue_pi हाल, try to acquire
 * uaddr2 atomically on behalf of the top रुकोer.
 *
 * Return:
 *  - >=0 - on success, the number of tasks requeued or woken;
 *  -  <0 - on error
 */
अटल पूर्णांक futex_requeue(u32 __user *uaddr1, अचिन्हित पूर्णांक flags,
			 u32 __user *uaddr2, पूर्णांक nr_wake, पूर्णांक nr_requeue,
			 u32 *cmpval, पूर्णांक requeue_pi)
अणु
	जोड़ futex_key key1 = FUTEX_KEY_INIT, key2 = FUTEX_KEY_INIT;
	पूर्णांक task_count = 0, ret;
	काष्ठा futex_pi_state *pi_state = शून्य;
	काष्ठा futex_hash_bucket *hb1, *hb2;
	काष्ठा futex_q *this, *next;
	DEFINE_WAKE_Q(wake_q);

	अगर (nr_wake < 0 || nr_requeue < 0)
		वापस -EINVAL;

	/*
	 * When PI not supported: वापस -ENOSYS अगर requeue_pi is true,
	 * consequently the compiler knows requeue_pi is always false past
	 * this poपूर्णांक which will optimize away all the conditional code
	 * further करोwn.
	 */
	अगर (!IS_ENABLED(CONFIG_FUTEX_PI) && requeue_pi)
		वापस -ENOSYS;

	अगर (requeue_pi) अणु
		/*
		 * Requeue PI only works on two distinct uaddrs. This
		 * check is only valid क्रम निजी futexes. See below.
		 */
		अगर (uaddr1 == uaddr2)
			वापस -EINVAL;

		/*
		 * requeue_pi requires a pi_state, try to allocate it now
		 * without any locks in हाल it fails.
		 */
		अगर (refill_pi_state_cache())
			वापस -ENOMEM;
		/*
		 * requeue_pi must wake as many tasks as it can, up to nr_wake
		 * + nr_requeue, since it acquires the rt_mutex prior to
		 * वापसing to userspace, so as to not leave the rt_mutex with
		 * रुकोers and no owner.  However, second and third wake-ups
		 * cannot be predicted as they involve race conditions with the
		 * first wake and a fault जबतक looking up the pi_state.  Both
		 * pthपढ़ो_cond_संकेत() and pthपढ़ो_cond_broadcast() should
		 * use nr_wake=1.
		 */
		अगर (nr_wake != 1)
			वापस -EINVAL;
	पूर्ण

retry:
	ret = get_futex_key(uaddr1, flags & FLAGS_SHARED, &key1, FUTEX_READ);
	अगर (unlikely(ret != 0))
		वापस ret;
	ret = get_futex_key(uaddr2, flags & FLAGS_SHARED, &key2,
			    requeue_pi ? FUTEX_WRITE : FUTEX_READ);
	अगर (unlikely(ret != 0))
		वापस ret;

	/*
	 * The check above which compares uaddrs is not sufficient क्रम
	 * shared futexes. We need to compare the keys:
	 */
	अगर (requeue_pi && match_futex(&key1, &key2))
		वापस -EINVAL;

	hb1 = hash_futex(&key1);
	hb2 = hash_futex(&key2);

retry_निजी:
	hb_रुकोers_inc(hb2);
	द्विगुन_lock_hb(hb1, hb2);

	अगर (likely(cmpval != शून्य)) अणु
		u32 curval;

		ret = get_futex_value_locked(&curval, uaddr1);

		अगर (unlikely(ret)) अणु
			द्विगुन_unlock_hb(hb1, hb2);
			hb_रुकोers_dec(hb2);

			ret = get_user(curval, uaddr1);
			अगर (ret)
				वापस ret;

			अगर (!(flags & FLAGS_SHARED))
				जाओ retry_निजी;

			जाओ retry;
		पूर्ण
		अगर (curval != *cmpval) अणु
			ret = -EAGAIN;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	अगर (requeue_pi && (task_count - nr_wake < nr_requeue)) अणु
		काष्ठा task_काष्ठा *निकासing = शून्य;

		/*
		 * Attempt to acquire uaddr2 and wake the top रुकोer. If we
		 * पूर्णांकend to requeue रुकोers, क्रमce setting the FUTEX_WAITERS
		 * bit.  We क्रमce this here where we are able to easily handle
		 * faults rather in the requeue loop below.
		 */
		ret = futex_proxy_trylock_atomic(uaddr2, hb1, hb2, &key1,
						 &key2, &pi_state,
						 &निकासing, nr_requeue);

		/*
		 * At this poपूर्णांक the top_रुकोer has either taken uaddr2 or is
		 * रुकोing on it.  If the क्रमmer, then the pi_state will not
		 * exist yet, look it up one more समय to ensure we have a
		 * reference to it. If the lock was taken, ret contains the
		 * vpid of the top रुकोer task.
		 * If the lock was not taken, we have pi_state and an initial
		 * refcount on it. In हाल of an error we have nothing.
		 */
		अगर (ret > 0) अणु
			WARN_ON(pi_state);
			task_count++;
			/*
			 * If we acquired the lock, then the user space value
			 * of uaddr2 should be vpid. It cannot be changed by
			 * the top रुकोer as it is blocked on hb2 lock अगर it
			 * tries to करो so. If something fiddled with it behind
			 * our back the pi state lookup might unearth it. So
			 * we rather use the known value than reपढ़ोing and
			 * handing potential crap to lookup_pi_state.
			 *
			 * If that call succeeds then we have pi_state and an
			 * initial refcount on it.
			 */
			ret = lookup_pi_state(uaddr2, ret, hb2, &key2,
					      &pi_state, &निकासing);
		पूर्ण

		चयन (ret) अणु
		हाल 0:
			/* We hold a reference on the pi state. */
			अवरोध;

			/* If the above failed, then pi_state is शून्य */
		हाल -EFAULT:
			द्विगुन_unlock_hb(hb1, hb2);
			hb_रुकोers_dec(hb2);
			ret = fault_in_user_ग_लिखोable(uaddr2);
			अगर (!ret)
				जाओ retry;
			वापस ret;
		हाल -EBUSY:
		हाल -EAGAIN:
			/*
			 * Two reasons क्रम this:
			 * - EBUSY: Owner is निकासing and we just रुको क्रम the
			 *   निकास to complete.
			 * - EAGAIN: The user space value changed.
			 */
			द्विगुन_unlock_hb(hb1, hb2);
			hb_रुकोers_dec(hb2);
			/*
			 * Handle the हाल where the owner is in the middle of
			 * निकासing. Wait क्रम the निकास to complete otherwise
			 * this task might loop क्रमever, aka. live lock.
			 */
			रुको_क्रम_owner_निकासing(ret, निकासing);
			cond_resched();
			जाओ retry;
		शेष:
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	plist_क्रम_each_entry_safe(this, next, &hb1->chain, list) अणु
		अगर (task_count - nr_wake >= nr_requeue)
			अवरोध;

		अगर (!match_futex(&this->key, &key1))
			जारी;

		/*
		 * FUTEX_WAIT_REQEUE_PI and FUTEX_CMP_REQUEUE_PI should always
		 * be paired with each other and no other futex ops.
		 *
		 * We should never be requeueing a futex_q with a pi_state,
		 * which is aरुकोing a futex_unlock_pi().
		 */
		अगर ((requeue_pi && !this->rt_रुकोer) ||
		    (!requeue_pi && this->rt_रुकोer) ||
		    this->pi_state) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/*
		 * Wake nr_wake रुकोers.  For requeue_pi, अगर we acquired the
		 * lock, we alपढ़ोy woke the top_रुकोer.  If not, it will be
		 * woken by futex_unlock_pi().
		 */
		अगर (++task_count <= nr_wake && !requeue_pi) अणु
			mark_wake_futex(&wake_q, this);
			जारी;
		पूर्ण

		/* Ensure we requeue to the expected futex क्रम requeue_pi. */
		अगर (requeue_pi && !match_futex(this->requeue_pi_key, &key2)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/*
		 * Requeue nr_requeue रुकोers and possibly one more in the हाल
		 * of requeue_pi अगर we couldn't acquire the lock atomically.
		 */
		अगर (requeue_pi) अणु
			/*
			 * Prepare the रुकोer to take the rt_mutex. Take a
			 * refcount on the pi_state and store the poपूर्णांकer in
			 * the futex_q object of the रुकोer.
			 */
			get_pi_state(pi_state);
			this->pi_state = pi_state;
			ret = rt_mutex_start_proxy_lock(&pi_state->pi_mutex,
							this->rt_रुकोer,
							this->task);
			अगर (ret == 1) अणु
				/*
				 * We got the lock. We करो neither drop the
				 * refcount on pi_state nor clear
				 * this->pi_state because the रुकोer needs the
				 * pi_state क्रम cleaning up the user space
				 * value. It will drop the refcount after
				 * करोing so.
				 */
				requeue_pi_wake_futex(this, &key2, hb2);
				जारी;
			पूर्ण अन्यथा अगर (ret) अणु
				/*
				 * rt_mutex_start_proxy_lock() detected a
				 * potential deadlock when we tried to queue
				 * that रुकोer. Drop the pi_state reference
				 * which we took above and हटाओ the poपूर्णांकer
				 * to the state from the रुकोers futex_q
				 * object.
				 */
				this->pi_state = शून्य;
				put_pi_state(pi_state);
				/*
				 * We stop queueing more रुकोers and let user
				 * space deal with the mess.
				 */
				अवरोध;
			पूर्ण
		पूर्ण
		requeue_futex(this, hb1, hb2, &key2);
	पूर्ण

	/*
	 * We took an extra initial reference to the pi_state either
	 * in futex_proxy_trylock_atomic() or in lookup_pi_state(). We
	 * need to drop it here again.
	 */
	put_pi_state(pi_state);

out_unlock:
	द्विगुन_unlock_hb(hb1, hb2);
	wake_up_q(&wake_q);
	hb_रुकोers_dec(hb2);
	वापस ret ? ret : task_count;
पूर्ण

/* The key must be alपढ़ोy stored in q->key. */
अटल अंतरभूत काष्ठा futex_hash_bucket *queue_lock(काष्ठा futex_q *q)
	__acquires(&hb->lock)
अणु
	काष्ठा futex_hash_bucket *hb;

	hb = hash_futex(&q->key);

	/*
	 * Increment the counter beक्रमe taking the lock so that
	 * a potential waker won't miss a to-be-slept task that is
	 * रुकोing क्रम the spinlock. This is safe as all queue_lock()
	 * users end up calling queue_me(). Similarly, क्रम housekeeping,
	 * decrement the counter at queue_unlock() when some error has
	 * occurred and we करोn't end up adding the task to the list.
	 */
	hb_रुकोers_inc(hb); /* implies smp_mb(); (A) */

	q->lock_ptr = &hb->lock;

	spin_lock(&hb->lock);
	वापस hb;
पूर्ण

अटल अंतरभूत व्योम
queue_unlock(काष्ठा futex_hash_bucket *hb)
	__releases(&hb->lock)
अणु
	spin_unlock(&hb->lock);
	hb_रुकोers_dec(hb);
पूर्ण

अटल अंतरभूत व्योम __queue_me(काष्ठा futex_q *q, काष्ठा futex_hash_bucket *hb)
अणु
	पूर्णांक prio;

	/*
	 * The priority used to रेजिस्टर this element is
	 * - either the real thपढ़ो-priority क्रम the real-समय thपढ़ोs
	 * (i.e. thपढ़ोs with a priority lower than MAX_RT_PRIO)
	 * - or MAX_RT_PRIO क्रम non-RT thपढ़ोs.
	 * Thus, all RT-thपढ़ोs are woken first in priority order, and
	 * the others are woken last, in FIFO order.
	 */
	prio = min(current->normal_prio, MAX_RT_PRIO);

	plist_node_init(&q->list, prio);
	plist_add(&q->list, &hb->chain);
	q->task = current;
पूर्ण

/**
 * queue_me() - Enqueue the futex_q on the futex_hash_bucket
 * @q:	The futex_q to enqueue
 * @hb:	The destination hash bucket
 *
 * The hb->lock must be held by the caller, and is released here. A call to
 * queue_me() is typically paired with exactly one call to unqueue_me().  The
 * exceptions involve the PI related operations, which may use unqueue_me_pi()
 * or nothing अगर the unqueue is करोne as part of the wake process and the unqueue
 * state is implicit in the state of woken task (see futex_रुको_requeue_pi() क्रम
 * an example).
 */
अटल अंतरभूत व्योम queue_me(काष्ठा futex_q *q, काष्ठा futex_hash_bucket *hb)
	__releases(&hb->lock)
अणु
	__queue_me(q, hb);
	spin_unlock(&hb->lock);
पूर्ण

/**
 * unqueue_me() - Remove the futex_q from its futex_hash_bucket
 * @q:	The futex_q to unqueue
 *
 * The q->lock_ptr must not be held by the caller. A call to unqueue_me() must
 * be paired with exactly one earlier call to queue_me().
 *
 * Return:
 *  - 1 - अगर the futex_q was still queued (and we हटाओd unqueued it);
 *  - 0 - अगर the futex_q was alपढ़ोy हटाओd by the waking thपढ़ो
 */
अटल पूर्णांक unqueue_me(काष्ठा futex_q *q)
अणु
	spinlock_t *lock_ptr;
	पूर्णांक ret = 0;

	/* In the common हाल we करोn't take the spinlock, which is nice. */
retry:
	/*
	 * q->lock_ptr can change between this पढ़ो and the following spin_lock.
	 * Use READ_ONCE to क्रमbid the compiler from reloading q->lock_ptr and
	 * optimizing lock_ptr out of the logic below.
	 */
	lock_ptr = READ_ONCE(q->lock_ptr);
	अगर (lock_ptr != शून्य) अणु
		spin_lock(lock_ptr);
		/*
		 * q->lock_ptr can change between पढ़ोing it and
		 * spin_lock(), causing us to take the wrong lock.  This
		 * corrects the race condition.
		 *
		 * Reasoning goes like this: अगर we have the wrong lock,
		 * q->lock_ptr must have changed (maybe several बार)
		 * between पढ़ोing it and the spin_lock().  It can
		 * change again after the spin_lock() but only अगर it was
		 * alपढ़ोy changed beक्रमe the spin_lock().  It cannot,
		 * however, change back to the original value.  Thereक्रमe
		 * we can detect whether we acquired the correct lock.
		 */
		अगर (unlikely(lock_ptr != q->lock_ptr)) अणु
			spin_unlock(lock_ptr);
			जाओ retry;
		पूर्ण
		__unqueue_futex(q);

		BUG_ON(q->pi_state);

		spin_unlock(lock_ptr);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * PI futexes can not be requeued and must हटाओ themself from the
 * hash bucket. The hash bucket lock (i.e. lock_ptr) is held.
 */
अटल व्योम unqueue_me_pi(काष्ठा futex_q *q)
अणु
	__unqueue_futex(q);

	BUG_ON(!q->pi_state);
	put_pi_state(q->pi_state);
	q->pi_state = शून्य;
पूर्ण

अटल पूर्णांक __fixup_pi_state_owner(u32 __user *uaddr, काष्ठा futex_q *q,
				  काष्ठा task_काष्ठा *argowner)
अणु
	काष्ठा futex_pi_state *pi_state = q->pi_state;
	काष्ठा task_काष्ठा *olकरोwner, *newowner;
	u32 uval, curval, newval, newtid;
	पूर्णांक err = 0;

	olकरोwner = pi_state->owner;

	/*
	 * We are here because either:
	 *
	 *  - we stole the lock and pi_state->owner needs updating to reflect
	 *    that (@argowner == current),
	 *
	 * or:
	 *
	 *  - someone stole our lock and we need to fix things to poपूर्णांक to the
	 *    new owner (@argowner == शून्य).
	 *
	 * Either way, we have to replace the TID in the user space variable.
	 * This must be atomic as we have to preserve the owner died bit here.
	 *
	 * Note: We ग_लिखो the user space value _beक्रमe_ changing the pi_state
	 * because we can fault here. Imagine swapped out pages or a विभाजन
	 * that marked all the anonymous memory पढ़ोonly क्रम cow.
	 *
	 * Modअगरying pi_state _beक्रमe_ the user space value would leave the
	 * pi_state in an inconsistent state when we fault here, because we
	 * need to drop the locks to handle the fault. This might be observed
	 * in the PID check in lookup_pi_state.
	 */
retry:
	अगर (!argowner) अणु
		अगर (olकरोwner != current) अणु
			/*
			 * We raced against a concurrent self; things are
			 * alपढ़ोy fixed up. Nothing to करो.
			 */
			वापस 0;
		पूर्ण

		अगर (__rt_mutex_futex_trylock(&pi_state->pi_mutex)) अणु
			/* We got the lock. pi_state is correct. Tell caller. */
			वापस 1;
		पूर्ण

		/*
		 * The trylock just failed, so either there is an owner or
		 * there is a higher priority रुकोer than this one.
		 */
		newowner = rt_mutex_owner(&pi_state->pi_mutex);
		/*
		 * If the higher priority रुकोer has not yet taken over the
		 * rपंचांगutex then newowner is शून्य. We can't वापस here with
		 * that state because it's inconsistent vs. the user space
		 * state. So drop the locks and try again. It's a valid
		 * situation and not any dअगरferent from the other retry
		 * conditions.
		 */
		अगर (unlikely(!newowner)) अणु
			err = -EAGAIN;
			जाओ handle_err;
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(argowner != current);
		अगर (olकरोwner == current) अणु
			/*
			 * We raced against a concurrent self; things are
			 * alपढ़ोy fixed up. Nothing to करो.
			 */
			वापस 1;
		पूर्ण
		newowner = argowner;
	पूर्ण

	newtid = task_pid_vnr(newowner) | FUTEX_WAITERS;
	/* Owner died? */
	अगर (!pi_state->owner)
		newtid |= FUTEX_OWNER_DIED;

	err = get_futex_value_locked(&uval, uaddr);
	अगर (err)
		जाओ handle_err;

	क्रम (;;) अणु
		newval = (uval & FUTEX_OWNER_DIED) | newtid;

		err = cmpxchg_futex_value_locked(&curval, uaddr, uval, newval);
		अगर (err)
			जाओ handle_err;

		अगर (curval == uval)
			अवरोध;
		uval = curval;
	पूर्ण

	/*
	 * We fixed up user space. Now we need to fix the pi_state
	 * itself.
	 */
	pi_state_update_owner(pi_state, newowner);

	वापस argowner == current;

	/*
	 * In order to reschedule or handle a page fault, we need to drop the
	 * locks here. In the हाल of a fault, this gives the other task
	 * (either the highest priority रुकोer itself or the task which stole
	 * the rपंचांगutex) the chance to try the fixup of the pi_state. So once we
	 * are back from handling the fault we need to check the pi_state after
	 * reacquiring the locks and beक्रमe trying to करो another fixup. When
	 * the fixup has been करोne alपढ़ोy we simply वापस.
	 *
	 * Note: we hold both hb->lock and pi_mutex->रुको_lock. We can safely
	 * drop hb->lock since the caller owns the hb -> futex_q relation.
	 * Dropping the pi_mutex->रुको_lock requires the state revalidate.
	 */
handle_err:
	raw_spin_unlock_irq(&pi_state->pi_mutex.रुको_lock);
	spin_unlock(q->lock_ptr);

	चयन (err) अणु
	हाल -EFAULT:
		err = fault_in_user_ग_लिखोable(uaddr);
		अवरोध;

	हाल -EAGAIN:
		cond_resched();
		err = 0;
		अवरोध;

	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	spin_lock(q->lock_ptr);
	raw_spin_lock_irq(&pi_state->pi_mutex.रुको_lock);

	/*
	 * Check अगर someone अन्यथा fixed it क्रम us:
	 */
	अगर (pi_state->owner != olकरोwner)
		वापस argowner == current;

	/* Retry अगर err was -EAGAIN or the fault in succeeded */
	अगर (!err)
		जाओ retry;

	/*
	 * fault_in_user_ग_लिखोable() failed so user state is immutable. At
	 * best we can make the kernel state consistent but user state will
	 * be most likely hosed and any subsequent unlock operation will be
	 * rejected due to PI futex rule [10].
	 *
	 * Ensure that the rपंचांगutex owner is also the pi_state owner despite
	 * the user space value claiming something dअगरferent. There is no
	 * poपूर्णांक in unlocking the rपंचांगutex अगर current is the owner as it
	 * would need to रुको until the next रुकोer has taken the rपंचांगutex
	 * to guarantee consistent state. Keep it simple. Userspace asked
	 * क्रम this wreckaged state.
	 *
	 * The rपंचांगutex has an owner - either current or some other
	 * task. See the EAGAIN loop above.
	 */
	pi_state_update_owner(pi_state, rt_mutex_owner(&pi_state->pi_mutex));

	वापस err;
पूर्ण

अटल पूर्णांक fixup_pi_state_owner(u32 __user *uaddr, काष्ठा futex_q *q,
				काष्ठा task_काष्ठा *argowner)
अणु
	काष्ठा futex_pi_state *pi_state = q->pi_state;
	पूर्णांक ret;

	lockdep_निश्चित_held(q->lock_ptr);

	raw_spin_lock_irq(&pi_state->pi_mutex.रुको_lock);
	ret = __fixup_pi_state_owner(uaddr, q, argowner);
	raw_spin_unlock_irq(&pi_state->pi_mutex.रुको_lock);
	वापस ret;
पूर्ण

अटल दीर्घ futex_रुको_restart(काष्ठा restart_block *restart);

/**
 * fixup_owner() - Post lock pi_state and corner हाल management
 * @uaddr:	user address of the futex
 * @q:		futex_q (contains pi_state and access to the rt_mutex)
 * @locked:	अगर the attempt to take the rt_mutex succeeded (1) or not (0)
 *
 * After attempting to lock an rt_mutex, this function is called to cleanup
 * the pi_state owner as well as handle race conditions that may allow us to
 * acquire the lock. Must be called with the hb lock held.
 *
 * Return:
 *  -  1 - success, lock taken;
 *  -  0 - success, lock not taken;
 *  - <0 - on error (-EFAULT)
 */
अटल पूर्णांक fixup_owner(u32 __user *uaddr, काष्ठा futex_q *q, पूर्णांक locked)
अणु
	अगर (locked) अणु
		/*
		 * Got the lock. We might not be the anticipated owner अगर we
		 * did a lock-steal - fix up the PI-state in that हाल:
		 *
		 * Speculative pi_state->owner पढ़ो (we करोn't hold रुको_lock);
		 * since we own the lock pi_state->owner == current is the
		 * stable state, anything अन्यथा needs more attention.
		 */
		अगर (q->pi_state->owner != current)
			वापस fixup_pi_state_owner(uaddr, q, current);
		वापस 1;
	पूर्ण

	/*
	 * If we didn't get the lock; check अगर anybody stole it from us. In
	 * that हाल, we need to fix up the uval to poपूर्णांक to them instead of
	 * us, otherwise bad things happen. [10]
	 *
	 * Another speculative पढ़ो; pi_state->owner == current is unstable
	 * but needs our attention.
	 */
	अगर (q->pi_state->owner == current)
		वापस fixup_pi_state_owner(uaddr, q, शून्य);

	/*
	 * Paranoia check. If we did not take the lock, then we should not be
	 * the owner of the rt_mutex. Warn and establish consistent state.
	 */
	अगर (WARN_ON_ONCE(rt_mutex_owner(&q->pi_state->pi_mutex) == current))
		वापस fixup_pi_state_owner(uaddr, q, current);

	वापस 0;
पूर्ण

/**
 * futex_रुको_queue_me() - queue_me() and रुको क्रम wakeup, समयout, or संकेत
 * @hb:		the futex hash bucket, must be locked by the caller
 * @q:		the futex_q to queue up on
 * @समयout:	the prepared hrसमयr_sleeper, or null क्रम no समयout
 */
अटल व्योम futex_रुको_queue_me(काष्ठा futex_hash_bucket *hb, काष्ठा futex_q *q,
				काष्ठा hrसमयr_sleeper *समयout)
अणु
	/*
	 * The task state is guaranteed to be set beक्रमe another task can
	 * wake it. set_current_state() is implemented using smp_store_mb() and
	 * queue_me() calls spin_unlock() upon completion, both serializing
	 * access to the hash list and क्रमcing another memory barrier.
	 */
	set_current_state(TASK_INTERRUPTIBLE);
	queue_me(q, hb);

	/* Arm the समयr */
	अगर (समयout)
		hrसमयr_sleeper_start_expires(समयout, HRTIMER_MODE_ABS);

	/*
	 * If we have been हटाओd from the hash list, then another task
	 * has tried to wake us, and we can skip the call to schedule().
	 */
	अगर (likely(!plist_node_empty(&q->list))) अणु
		/*
		 * If the समयr has alपढ़ोy expired, current will alपढ़ोy be
		 * flagged क्रम rescheduling. Only call schedule अगर there
		 * is no समयout, or अगर it has yet to expire.
		 */
		अगर (!समयout || समयout->task)
			मुक्तzable_schedule();
	पूर्ण
	__set_current_state(TASK_RUNNING);
पूर्ण

/**
 * futex_रुको_setup() - Prepare to रुको on a futex
 * @uaddr:	the futex userspace address
 * @val:	the expected value
 * @flags:	futex flags (FLAGS_SHARED, etc.)
 * @q:		the associated futex_q
 * @hb:		storage क्रम hash_bucket poपूर्णांकer to be वापसed to caller
 *
 * Setup the futex_q and locate the hash_bucket.  Get the futex value and
 * compare it with the expected value.  Handle atomic faults पूर्णांकernally.
 * Return with the hb lock held and a q.key reference on success, and unlocked
 * with no q.key reference on failure.
 *
 * Return:
 *  -  0 - uaddr contains val and hb has been locked;
 *  - <1 - -EFAULT or -EWOULDBLOCK (uaddr करोes not contain val) and hb is unlocked
 */
अटल पूर्णांक futex_रुको_setup(u32 __user *uaddr, u32 val, अचिन्हित पूर्णांक flags,
			   काष्ठा futex_q *q, काष्ठा futex_hash_bucket **hb)
अणु
	u32 uval;
	पूर्णांक ret;

	/*
	 * Access the page AFTER the hash-bucket is locked.
	 * Order is important:
	 *
	 *   Userspace रुकोer: val = var; अगर (cond(val)) futex_रुको(&var, val);
	 *   Userspace waker:  अगर (cond(var)) अणु var = new; futex_wake(&var); पूर्ण
	 *
	 * The basic logical guarantee of a futex is that it blocks ONLY
	 * अगर cond(var) is known to be true at the समय of blocking, क्रम
	 * any cond.  If we locked the hash-bucket after testing *uaddr, that
	 * would खोलो a race condition where we could block indefinitely with
	 * cond(var) false, which would violate the guarantee.
	 *
	 * On the other hand, we insert q and release the hash-bucket only
	 * after testing *uaddr.  This guarantees that futex_रुको() will NOT
	 * असलorb a wakeup अगर *uaddr करोes not match the desired values
	 * जबतक the syscall executes.
	 */
retry:
	ret = get_futex_key(uaddr, flags & FLAGS_SHARED, &q->key, FUTEX_READ);
	अगर (unlikely(ret != 0))
		वापस ret;

retry_निजी:
	*hb = queue_lock(q);

	ret = get_futex_value_locked(&uval, uaddr);

	अगर (ret) अणु
		queue_unlock(*hb);

		ret = get_user(uval, uaddr);
		अगर (ret)
			वापस ret;

		अगर (!(flags & FLAGS_SHARED))
			जाओ retry_निजी;

		जाओ retry;
	पूर्ण

	अगर (uval != val) अणु
		queue_unlock(*hb);
		ret = -EWOULDBLOCK;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक futex_रुको(u32 __user *uaddr, अचिन्हित पूर्णांक flags, u32 val,
		      kसमय_प्रकार *असल_समय, u32 bitset)
अणु
	काष्ठा hrसमयr_sleeper समयout, *to;
	काष्ठा restart_block *restart;
	काष्ठा futex_hash_bucket *hb;
	काष्ठा futex_q q = futex_q_init;
	पूर्णांक ret;

	अगर (!bitset)
		वापस -EINVAL;
	q.bitset = bitset;

	to = futex_setup_समयr(असल_समय, &समयout, flags,
			       current->समयr_slack_ns);
retry:
	/*
	 * Prepare to रुको on uaddr. On success, holds hb lock and increments
	 * q.key refs.
	 */
	ret = futex_रुको_setup(uaddr, val, flags, &q, &hb);
	अगर (ret)
		जाओ out;

	/* queue_me and रुको क्रम wakeup, समयout, or a संकेत. */
	futex_रुको_queue_me(hb, &q, to);

	/* If we were woken (and unqueued), we succeeded, whatever. */
	ret = 0;
	/* unqueue_me() drops q.key ref */
	अगर (!unqueue_me(&q))
		जाओ out;
	ret = -ETIMEDOUT;
	अगर (to && !to->task)
		जाओ out;

	/*
	 * We expect संकेत_pending(current), but we might be the
	 * victim of a spurious wakeup as well.
	 */
	अगर (!संकेत_pending(current))
		जाओ retry;

	ret = -ERESTARTSYS;
	अगर (!असल_समय)
		जाओ out;

	restart = &current->restart_block;
	restart->futex.uaddr = uaddr;
	restart->futex.val = val;
	restart->futex.समय = *असल_समय;
	restart->futex.bitset = bitset;
	restart->futex.flags = flags | FLAGS_HAS_TIMEOUT;

	ret = set_restart_fn(restart, futex_रुको_restart);

out:
	अगर (to) अणु
		hrसमयr_cancel(&to->समयr);
		destroy_hrसमयr_on_stack(&to->समयr);
	पूर्ण
	वापस ret;
पूर्ण


अटल दीर्घ futex_रुको_restart(काष्ठा restart_block *restart)
अणु
	u32 __user *uaddr = restart->futex.uaddr;
	kसमय_प्रकार t, *tp = शून्य;

	अगर (restart->futex.flags & FLAGS_HAS_TIMEOUT) अणु
		t = restart->futex.समय;
		tp = &t;
	पूर्ण
	restart->fn = करो_no_restart_syscall;

	वापस (दीर्घ)futex_रुको(uaddr, restart->futex.flags,
				restart->futex.val, tp, restart->futex.bitset);
पूर्ण


/*
 * Userspace tried a 0 -> TID atomic transition of the futex value
 * and failed. The kernel side here करोes the whole locking operation:
 * अगर there are रुकोers then it will block as a consequence of relying
 * on rt-mutexes, it करोes PI, etc. (Due to races the kernel might see
 * a 0 value of the futex too.).
 *
 * Also serves as futex trylock_pi()'ing, and due semantics.
 */
अटल पूर्णांक futex_lock_pi(u32 __user *uaddr, अचिन्हित पूर्णांक flags,
			 kसमय_प्रकार *समय, पूर्णांक trylock)
अणु
	काष्ठा hrसमयr_sleeper समयout, *to;
	काष्ठा task_काष्ठा *निकासing = शून्य;
	काष्ठा rt_mutex_रुकोer rt_रुकोer;
	काष्ठा futex_hash_bucket *hb;
	काष्ठा futex_q q = futex_q_init;
	पूर्णांक res, ret;

	अगर (!IS_ENABLED(CONFIG_FUTEX_PI))
		वापस -ENOSYS;

	अगर (refill_pi_state_cache())
		वापस -ENOMEM;

	to = futex_setup_समयr(समय, &समयout, FLAGS_CLOCKRT, 0);

retry:
	ret = get_futex_key(uaddr, flags & FLAGS_SHARED, &q.key, FUTEX_WRITE);
	अगर (unlikely(ret != 0))
		जाओ out;

retry_निजी:
	hb = queue_lock(&q);

	ret = futex_lock_pi_atomic(uaddr, hb, &q.key, &q.pi_state, current,
				   &निकासing, 0);
	अगर (unlikely(ret)) अणु
		/*
		 * Atomic work succeeded and we got the lock,
		 * or failed. Either way, we करो _not_ block.
		 */
		चयन (ret) अणु
		हाल 1:
			/* We got the lock. */
			ret = 0;
			जाओ out_unlock_put_key;
		हाल -EFAULT:
			जाओ uaddr_faulted;
		हाल -EBUSY:
		हाल -EAGAIN:
			/*
			 * Two reasons क्रम this:
			 * - EBUSY: Task is निकासing and we just रुको क्रम the
			 *   निकास to complete.
			 * - EAGAIN: The user space value changed.
			 */
			queue_unlock(hb);
			/*
			 * Handle the हाल where the owner is in the middle of
			 * निकासing. Wait क्रम the निकास to complete otherwise
			 * this task might loop क्रमever, aka. live lock.
			 */
			रुको_क्रम_owner_निकासing(ret, निकासing);
			cond_resched();
			जाओ retry;
		शेष:
			जाओ out_unlock_put_key;
		पूर्ण
	पूर्ण

	WARN_ON(!q.pi_state);

	/*
	 * Only actually queue now that the atomic ops are करोne:
	 */
	__queue_me(&q, hb);

	अगर (trylock) अणु
		ret = rt_mutex_futex_trylock(&q.pi_state->pi_mutex);
		/* Fixup the trylock वापस value: */
		ret = ret ? 0 : -EWOULDBLOCK;
		जाओ no_block;
	पूर्ण

	rt_mutex_init_रुकोer(&rt_रुकोer);

	/*
	 * On PREEMPT_RT_FULL, when hb->lock becomes an rt_mutex, we must not
	 * hold it जबतक करोing rt_mutex_start_proxy(), because then it will
	 * include hb->lock in the blocking chain, even through we'll not in
	 * fact hold it जबतक blocking. This will lead it to report -EDEADLK
	 * and BUG when futex_unlock_pi() पूर्णांकerleaves with this.
	 *
	 * Thereक्रमe acquire रुको_lock जबतक holding hb->lock, but drop the
	 * latter beक्रमe calling __rt_mutex_start_proxy_lock(). This
	 * पूर्णांकerleaves with futex_unlock_pi() -- which करोes a similar lock
	 * hanकरोff -- such that the latter can observe the futex_q::pi_state
	 * beक्रमe __rt_mutex_start_proxy_lock() is करोne.
	 */
	raw_spin_lock_irq(&q.pi_state->pi_mutex.रुको_lock);
	spin_unlock(q.lock_ptr);
	/*
	 * __rt_mutex_start_proxy_lock() unconditionally enqueues the @rt_रुकोer
	 * such that futex_unlock_pi() is guaranteed to observe the रुकोer when
	 * it sees the futex_q::pi_state.
	 */
	ret = __rt_mutex_start_proxy_lock(&q.pi_state->pi_mutex, &rt_रुकोer, current);
	raw_spin_unlock_irq(&q.pi_state->pi_mutex.रुको_lock);

	अगर (ret) अणु
		अगर (ret == 1)
			ret = 0;
		जाओ cleanup;
	पूर्ण

	अगर (unlikely(to))
		hrसमयr_sleeper_start_expires(to, HRTIMER_MODE_ABS);

	ret = rt_mutex_रुको_proxy_lock(&q.pi_state->pi_mutex, to, &rt_रुकोer);

cleanup:
	spin_lock(q.lock_ptr);
	/*
	 * If we failed to acquire the lock (deadlock/संकेत/समयout), we must
	 * first acquire the hb->lock beक्रमe removing the lock from the
	 * rt_mutex रुकोqueue, such that we can keep the hb and rt_mutex रुको
	 * lists consistent.
	 *
	 * In particular; it is important that futex_unlock_pi() can not
	 * observe this inconsistency.
	 */
	अगर (ret && !rt_mutex_cleanup_proxy_lock(&q.pi_state->pi_mutex, &rt_रुकोer))
		ret = 0;

no_block:
	/*
	 * Fixup the pi_state owner and possibly acquire the lock अगर we
	 * haven't alपढ़ोy.
	 */
	res = fixup_owner(uaddr, &q, !ret);
	/*
	 * If fixup_owner() वापसed an error, proprogate that.  If it acquired
	 * the lock, clear our -ETIMEDOUT or -EINTR.
	 */
	अगर (res)
		ret = (res < 0) ? res : 0;

	unqueue_me_pi(&q);
	spin_unlock(q.lock_ptr);
	जाओ out;

out_unlock_put_key:
	queue_unlock(hb);

out:
	अगर (to) अणु
		hrसमयr_cancel(&to->समयr);
		destroy_hrसमयr_on_stack(&to->समयr);
	पूर्ण
	वापस ret != -EINTR ? ret : -ERESTARTNOINTR;

uaddr_faulted:
	queue_unlock(hb);

	ret = fault_in_user_ग_लिखोable(uaddr);
	अगर (ret)
		जाओ out;

	अगर (!(flags & FLAGS_SHARED))
		जाओ retry_निजी;

	जाओ retry;
पूर्ण

/*
 * Userspace attempted a TID -> 0 atomic transition, and failed.
 * This is the in-kernel slowpath: we look up the PI state (अगर any),
 * and करो the rt-mutex unlock.
 */
अटल पूर्णांक futex_unlock_pi(u32 __user *uaddr, अचिन्हित पूर्णांक flags)
अणु
	u32 curval, uval, vpid = task_pid_vnr(current);
	जोड़ futex_key key = FUTEX_KEY_INIT;
	काष्ठा futex_hash_bucket *hb;
	काष्ठा futex_q *top_रुकोer;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_FUTEX_PI))
		वापस -ENOSYS;

retry:
	अगर (get_user(uval, uaddr))
		वापस -EFAULT;
	/*
	 * We release only a lock we actually own:
	 */
	अगर ((uval & FUTEX_TID_MASK) != vpid)
		वापस -EPERM;

	ret = get_futex_key(uaddr, flags & FLAGS_SHARED, &key, FUTEX_WRITE);
	अगर (ret)
		वापस ret;

	hb = hash_futex(&key);
	spin_lock(&hb->lock);

	/*
	 * Check रुकोers first. We करो not trust user space values at
	 * all and we at least want to know अगर user space fiddled
	 * with the futex value instead of blindly unlocking.
	 */
	top_रुकोer = futex_top_रुकोer(hb, &key);
	अगर (top_रुकोer) अणु
		काष्ठा futex_pi_state *pi_state = top_रुकोer->pi_state;

		ret = -EINVAL;
		अगर (!pi_state)
			जाओ out_unlock;

		/*
		 * If current करोes not own the pi_state then the futex is
		 * inconsistent and user space fiddled with the futex value.
		 */
		अगर (pi_state->owner != current)
			जाओ out_unlock;

		get_pi_state(pi_state);
		/*
		 * By taking रुको_lock जबतक still holding hb->lock, we ensure
		 * there is no poपूर्णांक where we hold neither; and thereक्रमe
		 * wake_futex_pi() must observe a state consistent with what we
		 * observed.
		 *
		 * In particular; this क्रमces __rt_mutex_start_proxy() to
		 * complete such that we're guaranteed to observe the
		 * rt_रुकोer. Also see the WARN in wake_futex_pi().
		 */
		raw_spin_lock_irq(&pi_state->pi_mutex.रुको_lock);
		spin_unlock(&hb->lock);

		/* drops pi_state->pi_mutex.रुको_lock */
		ret = wake_futex_pi(uaddr, uval, pi_state);

		put_pi_state(pi_state);

		/*
		 * Success, we're करोne! No tricky corner हालs.
		 */
		अगर (!ret)
			वापस ret;
		/*
		 * The atomic access to the futex value generated a
		 * pagefault, so retry the user-access and the wakeup:
		 */
		अगर (ret == -EFAULT)
			जाओ pi_faulted;
		/*
		 * A unconditional UNLOCK_PI op raced against a रुकोer
		 * setting the FUTEX_WAITERS bit. Try again.
		 */
		अगर (ret == -EAGAIN)
			जाओ pi_retry;
		/*
		 * wake_futex_pi has detected invalid state. Tell user
		 * space.
		 */
		वापस ret;
	पूर्ण

	/*
	 * We have no kernel पूर्णांकernal state, i.e. no रुकोers in the
	 * kernel. Waiters which are about to queue themselves are stuck
	 * on hb->lock. So we can safely ignore them. We करो neither
	 * preserve the WAITERS bit not the OWNER_DIED one. We are the
	 * owner.
	 */
	अगर ((ret = cmpxchg_futex_value_locked(&curval, uaddr, uval, 0))) अणु
		spin_unlock(&hb->lock);
		चयन (ret) अणु
		हाल -EFAULT:
			जाओ pi_faulted;

		हाल -EAGAIN:
			जाओ pi_retry;

		शेष:
			WARN_ON_ONCE(1);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * If uval has changed, let user space handle it.
	 */
	ret = (curval == uval) ? 0 : -EAGAIN;

out_unlock:
	spin_unlock(&hb->lock);
	वापस ret;

pi_retry:
	cond_resched();
	जाओ retry;

pi_faulted:

	ret = fault_in_user_ग_लिखोable(uaddr);
	अगर (!ret)
		जाओ retry;

	वापस ret;
पूर्ण

/**
 * handle_early_requeue_pi_wakeup() - Detect early wakeup on the initial futex
 * @hb:		the hash_bucket futex_q was original enqueued on
 * @q:		the futex_q woken जबतक रुकोing to be requeued
 * @key2:	the futex_key of the requeue target futex
 * @समयout:	the समयout associated with the रुको (शून्य अगर none)
 *
 * Detect अगर the task was woken on the initial futex as opposed to the requeue
 * target futex.  If so, determine अगर it was a समयout or a संकेत that caused
 * the wakeup and वापस the appropriate error code to the caller.  Must be
 * called with the hb lock held.
 *
 * Return:
 *  -  0 = no early wakeup detected;
 *  - <0 = -ETIMEDOUT or -ERESTARTNOINTR
 */
अटल अंतरभूत
पूर्णांक handle_early_requeue_pi_wakeup(काष्ठा futex_hash_bucket *hb,
				   काष्ठा futex_q *q, जोड़ futex_key *key2,
				   काष्ठा hrसमयr_sleeper *समयout)
अणु
	पूर्णांक ret = 0;

	/*
	 * With the hb lock held, we aव्योम races जबतक we process the wakeup.
	 * We only need to hold hb (and not hb2) to ensure atomicity as the
	 * wakeup code can't change q.key from uaddr to uaddr2 अगर we hold hb.
	 * It can't be requeued from uaddr2 to something else since we don't
	 * support a PI aware source futex क्रम requeue.
	 */
	अगर (!match_futex(&q->key, key2)) अणु
		WARN_ON(q->lock_ptr && (&hb->lock != q->lock_ptr));
		/*
		 * We were woken prior to requeue by a समयout or a संकेत.
		 * Unqueue the futex_q and determine which it was.
		 */
		plist_del(&q->list, &hb->chain);
		hb_रुकोers_dec(hb);

		/* Handle spurious wakeups gracefully */
		ret = -EWOULDBLOCK;
		अगर (समयout && !समयout->task)
			ret = -ETIMEDOUT;
		अन्यथा अगर (संकेत_pending(current))
			ret = -ERESTARTNOINTR;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * futex_रुको_requeue_pi() - Wait on uaddr and take uaddr2
 * @uaddr:	the futex we initially रुको on (non-pi)
 * @flags:	futex flags (FLAGS_SHARED, FLAGS_CLOCKRT, etc.), they must be
 *		the same type, no requeueing from निजी to shared, etc.
 * @val:	the expected value of uaddr
 * @असल_समय:	असलolute समयout
 * @bitset:	32 bit wakeup bitset set by userspace, शेषs to all
 * @uaddr2:	the pi futex we will take prior to वापसing to user-space
 *
 * The caller will रुको on uaddr and will be requeued by futex_requeue() to
 * uaddr2 which must be PI aware and unique from uaddr.  Normal wakeup will wake
 * on uaddr2 and complete the acquisition of the rt_mutex prior to वापसing to
 * userspace.  This ensures the rt_mutex मुख्यtains an owner when it has रुकोers;
 * without one, the pi logic would not know which task to boost/deboost, अगर
 * there was a need to.
 *
 * We call schedule in futex_रुको_queue_me() when we enqueue and वापस there
 * via the following--
 * 1) wakeup on uaddr2 after an atomic lock acquisition by futex_requeue()
 * 2) wakeup on uaddr2 after a requeue
 * 3) संकेत
 * 4) समयout
 *
 * If 3, cleanup and वापस -ERESTARTNOINTR.
 *
 * If 2, we may then block on trying to take the rt_mutex and वापस via:
 * 5) successful lock
 * 6) संकेत
 * 7) समयout
 * 8) other lock acquisition failure
 *
 * If 6, वापस -EWOULDBLOCK (restarting the syscall would करो the same).
 *
 * If 4 or 7, we cleanup and वापस with -ETIMEDOUT.
 *
 * Return:
 *  -  0 - On success;
 *  - <0 - On error
 */
अटल पूर्णांक futex_रुको_requeue_pi(u32 __user *uaddr, अचिन्हित पूर्णांक flags,
				 u32 val, kसमय_प्रकार *असल_समय, u32 bitset,
				 u32 __user *uaddr2)
अणु
	काष्ठा hrसमयr_sleeper समयout, *to;
	काष्ठा rt_mutex_रुकोer rt_रुकोer;
	काष्ठा futex_hash_bucket *hb;
	जोड़ futex_key key2 = FUTEX_KEY_INIT;
	काष्ठा futex_q q = futex_q_init;
	पूर्णांक res, ret;

	अगर (!IS_ENABLED(CONFIG_FUTEX_PI))
		वापस -ENOSYS;

	अगर (uaddr == uaddr2)
		वापस -EINVAL;

	अगर (!bitset)
		वापस -EINVAL;

	to = futex_setup_समयr(असल_समय, &समयout, flags,
			       current->समयr_slack_ns);

	/*
	 * The रुकोer is allocated on our stack, manipulated by the requeue
	 * code जबतक we sleep on uaddr.
	 */
	rt_mutex_init_रुकोer(&rt_रुकोer);

	ret = get_futex_key(uaddr2, flags & FLAGS_SHARED, &key2, FUTEX_WRITE);
	अगर (unlikely(ret != 0))
		जाओ out;

	q.bitset = bitset;
	q.rt_रुकोer = &rt_रुकोer;
	q.requeue_pi_key = &key2;

	/*
	 * Prepare to रुको on uaddr. On success, increments q.key (key1) ref
	 * count.
	 */
	ret = futex_रुको_setup(uaddr, val, flags, &q, &hb);
	अगर (ret)
		जाओ out;

	/*
	 * The check above which compares uaddrs is not sufficient क्रम
	 * shared futexes. We need to compare the keys:
	 */
	अगर (match_futex(&q.key, &key2)) अणु
		queue_unlock(hb);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Queue the futex_q, drop the hb lock, रुको क्रम wakeup. */
	futex_रुको_queue_me(hb, &q, to);

	spin_lock(&hb->lock);
	ret = handle_early_requeue_pi_wakeup(hb, &q, &key2, to);
	spin_unlock(&hb->lock);
	अगर (ret)
		जाओ out;

	/*
	 * In order क्रम us to be here, we know our q.key == key2, and since
	 * we took the hb->lock above, we also know that futex_requeue() has
	 * completed and we no दीर्घer have to concern ourselves with a wakeup
	 * race with the atomic proxy lock acquisition by the requeue code. The
	 * futex_requeue dropped our key1 reference and incremented our key2
	 * reference count.
	 */

	/*
	 * Check अगर the requeue code acquired the second futex क्रम us and करो
	 * any pertinent fixup.
	 */
	अगर (!q.rt_रुकोer) अणु
		अगर (q.pi_state && (q.pi_state->owner != current)) अणु
			spin_lock(q.lock_ptr);
			ret = fixup_owner(uaddr2, &q, true);
			/*
			 * Drop the reference to the pi state which
			 * the requeue_pi() code acquired क्रम us.
			 */
			put_pi_state(q.pi_state);
			spin_unlock(q.lock_ptr);
			/*
			 * Adjust the वापस value. It's either -EFAULT or
			 * success (1) but the caller expects 0 क्रम success.
			 */
			ret = ret < 0 ? ret : 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा rt_mutex *pi_mutex;

		/*
		 * We have been woken up by futex_unlock_pi(), a समयout, or a
		 * संकेत.  futex_unlock_pi() will not destroy the lock_ptr nor
		 * the pi_state.
		 */
		WARN_ON(!q.pi_state);
		pi_mutex = &q.pi_state->pi_mutex;
		ret = rt_mutex_रुको_proxy_lock(pi_mutex, to, &rt_रुकोer);

		spin_lock(q.lock_ptr);
		अगर (ret && !rt_mutex_cleanup_proxy_lock(pi_mutex, &rt_रुकोer))
			ret = 0;

		debug_rt_mutex_मुक्त_रुकोer(&rt_रुकोer);
		/*
		 * Fixup the pi_state owner and possibly acquire the lock अगर we
		 * haven't alपढ़ोy.
		 */
		res = fixup_owner(uaddr2, &q, !ret);
		/*
		 * If fixup_owner() वापसed an error, proprogate that.  If it
		 * acquired the lock, clear -ETIMEDOUT or -EINTR.
		 */
		अगर (res)
			ret = (res < 0) ? res : 0;

		unqueue_me_pi(&q);
		spin_unlock(q.lock_ptr);
	पूर्ण

	अगर (ret == -EINTR) अणु
		/*
		 * We've alपढ़ोy been requeued, but cannot restart by calling
		 * futex_lock_pi() directly. We could restart this syscall, but
		 * it would detect that the user space "val" changed and वापस
		 * -EWOULDBLOCK.  Save the overhead of the restart and वापस
		 * -EWOULDBLOCK directly.
		 */
		ret = -EWOULDBLOCK;
	पूर्ण

out:
	अगर (to) अणु
		hrसमयr_cancel(&to->समयr);
		destroy_hrसमयr_on_stack(&to->समयr);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Support क्रम robust futexes: the kernel cleans up held futexes at
 * thपढ़ो निकास समय.
 *
 * Implementation: user-space मुख्यtains a per-thपढ़ो list of locks it
 * is holding. Upon करो_निकास(), the kernel carefully walks this list,
 * and marks all locks that are owned by this thपढ़ो with the
 * FUTEX_OWNER_DIED bit, and wakes up a रुकोer (अगर any). The list is
 * always manipulated with the lock held, so the list is निजी and
 * per-thपढ़ो. Userspace also मुख्यtains a per-thपढ़ो 'list_op_pending'
 * field, to allow the kernel to clean up अगर the thपढ़ो dies after
 * acquiring the lock, but just beक्रमe it could have added itself to
 * the list. There can only be one such pending lock.
 */

/**
 * sys_set_robust_list() - Set the robust-futex list head of a task
 * @head:	poपूर्णांकer to the list-head
 * @len:	length of the list-head, as userspace expects
 */
SYSCALL_DEFINE2(set_robust_list, काष्ठा robust_list_head __user *, head,
		माप_प्रकार, len)
अणु
	अगर (!futex_cmpxchg_enabled)
		वापस -ENOSYS;
	/*
	 * The kernel knows only one size क्रम now:
	 */
	अगर (unlikely(len != माप(*head)))
		वापस -EINVAL;

	current->robust_list = head;

	वापस 0;
पूर्ण

/**
 * sys_get_robust_list() - Get the robust-futex list head of a task
 * @pid:	pid of the process [zero क्रम current task]
 * @head_ptr:	poपूर्णांकer to a list-head poपूर्णांकer, the kernel fills it in
 * @len_ptr:	poपूर्णांकer to a length field, the kernel fills in the header size
 */
SYSCALL_DEFINE3(get_robust_list, पूर्णांक, pid,
		काष्ठा robust_list_head __user * __user *, head_ptr,
		माप_प्रकार __user *, len_ptr)
अणु
	काष्ठा robust_list_head __user *head;
	अचिन्हित दीर्घ ret;
	काष्ठा task_काष्ठा *p;

	अगर (!futex_cmpxchg_enabled)
		वापस -ENOSYS;

	rcu_पढ़ो_lock();

	ret = -ESRCH;
	अगर (!pid)
		p = current;
	अन्यथा अणु
		p = find_task_by_vpid(pid);
		अगर (!p)
			जाओ err_unlock;
	पूर्ण

	ret = -EPERM;
	अगर (!ptrace_may_access(p, PTRACE_MODE_READ_REALCREDS))
		जाओ err_unlock;

	head = p->robust_list;
	rcu_पढ़ो_unlock();

	अगर (put_user(माप(*head), len_ptr))
		वापस -EFAULT;
	वापस put_user(head, head_ptr);

err_unlock:
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/* Constants क्रम the pending_op argument of handle_futex_death */
#घोषणा HANDLE_DEATH_PENDING	true
#घोषणा HANDLE_DEATH_LIST	false

/*
 * Process a futex-list entry, check whether it's owned by the
 * dying task, and करो notअगरication अगर so:
 */
अटल पूर्णांक handle_futex_death(u32 __user *uaddr, काष्ठा task_काष्ठा *curr,
			      bool pi, bool pending_op)
अणु
	u32 uval, nval, mval;
	पूर्णांक err;

	/* Futex address must be 32bit aligned */
	अगर ((((अचिन्हित दीर्घ)uaddr) % माप(*uaddr)) != 0)
		वापस -1;

retry:
	अगर (get_user(uval, uaddr))
		वापस -1;

	/*
	 * Special हाल क्रम regular (non PI) futexes. The unlock path in
	 * user space has two race scenarios:
	 *
	 * 1. The unlock path releases the user space futex value and
	 *    beक्रमe it can execute the futex() syscall to wake up
	 *    रुकोers it is समाप्तed.
	 *
	 * 2. A woken up रुकोer is समाप्तed beक्रमe it can acquire the
	 *    futex in user space.
	 *
	 * In both हालs the TID validation below prevents a wakeup of
	 * potential रुकोers which can cause these रुकोers to block
	 * क्रमever.
	 *
	 * In both हालs the following conditions are met:
	 *
	 *	1) task->robust_list->list_op_pending != शून्य
	 *	   @pending_op == true
	 *	2) User space futex value == 0
	 *	3) Regular futex: @pi == false
	 *
	 * If these conditions are met, it is safe to attempt waking up a
	 * potential रुकोer without touching the user space futex value and
	 * trying to set the OWNER_DIED bit. The user space futex value is
	 * uncontended and the rest of the user space mutex state is
	 * consistent, so a woken रुकोer will just take over the
	 * uncontended futex. Setting the OWNER_DIED bit would create
	 * inconsistent state and malfunction of the user space owner died
	 * handling.
	 */
	अगर (pending_op && !pi && !uval) अणु
		futex_wake(uaddr, 1, 1, FUTEX_BITSET_MATCH_ANY);
		वापस 0;
	पूर्ण

	अगर ((uval & FUTEX_TID_MASK) != task_pid_vnr(curr))
		वापस 0;

	/*
	 * Ok, this dying thपढ़ो is truly holding a futex
	 * of पूर्णांकerest. Set the OWNER_DIED bit atomically
	 * via cmpxchg, and अगर the value had FUTEX_WAITERS
	 * set, wake up a रुकोer (अगर any). (We have to करो a
	 * futex_wake() even अगर OWNER_DIED is alपढ़ोy set -
	 * to handle the rare but possible हाल of recursive
	 * thपढ़ो-death.) The rest of the cleanup is करोne in
	 * userspace.
	 */
	mval = (uval & FUTEX_WAITERS) | FUTEX_OWNER_DIED;

	/*
	 * We are not holding a lock here, but we want to have
	 * the pagefault_disable/enable() protection because
	 * we want to handle the fault gracefully. If the
	 * access fails we try to fault in the futex with R/W
	 * verअगरication via get_user_pages. get_user() above
	 * करोes not guarantee R/W access. If that fails we
	 * give up and leave the futex locked.
	 */
	अगर ((err = cmpxchg_futex_value_locked(&nval, uaddr, uval, mval))) अणु
		चयन (err) अणु
		हाल -EFAULT:
			अगर (fault_in_user_ग_लिखोable(uaddr))
				वापस -1;
			जाओ retry;

		हाल -EAGAIN:
			cond_resched();
			जाओ retry;

		शेष:
			WARN_ON_ONCE(1);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (nval != uval)
		जाओ retry;

	/*
	 * Wake robust non-PI futexes here. The wakeup of
	 * PI futexes happens in निकास_pi_state():
	 */
	अगर (!pi && (uval & FUTEX_WAITERS))
		futex_wake(uaddr, 1, 1, FUTEX_BITSET_MATCH_ANY);

	वापस 0;
पूर्ण

/*
 * Fetch a robust-list poपूर्णांकer. Bit 0 संकेतs PI futexes:
 */
अटल अंतरभूत पूर्णांक fetch_robust_entry(काष्ठा robust_list __user **entry,
				     काष्ठा robust_list __user * __user *head,
				     अचिन्हित पूर्णांक *pi)
अणु
	अचिन्हित दीर्घ uentry;

	अगर (get_user(uentry, (अचिन्हित दीर्घ __user *)head))
		वापस -EFAULT;

	*entry = (व्योम __user *)(uentry & ~1UL);
	*pi = uentry & 1;

	वापस 0;
पूर्ण

/*
 * Walk curr->robust_list (very carefully, it's a userspace list!)
 * and mark any locks found there dead, and notअगरy any रुकोers.
 *
 * We silently वापस on any sign of list-walking problem.
 */
अटल व्योम निकास_robust_list(काष्ठा task_काष्ठा *curr)
अणु
	काष्ठा robust_list_head __user *head = curr->robust_list;
	काष्ठा robust_list __user *entry, *next_entry, *pending;
	अचिन्हित पूर्णांक limit = ROBUST_LIST_LIMIT, pi, pip;
	अचिन्हित पूर्णांक next_pi;
	अचिन्हित दीर्घ futex_offset;
	पूर्णांक rc;

	अगर (!futex_cmpxchg_enabled)
		वापस;

	/*
	 * Fetch the list head (which was रेजिस्टरed earlier, via
	 * sys_set_robust_list()):
	 */
	अगर (fetch_robust_entry(&entry, &head->list.next, &pi))
		वापस;
	/*
	 * Fetch the relative futex offset:
	 */
	अगर (get_user(futex_offset, &head->futex_offset))
		वापस;
	/*
	 * Fetch any possibly pending lock-add first, and handle it
	 * अगर it exists:
	 */
	अगर (fetch_robust_entry(&pending, &head->list_op_pending, &pip))
		वापस;

	next_entry = शून्य;	/* aव्योम warning with gcc */
	जबतक (entry != &head->list) अणु
		/*
		 * Fetch the next entry in the list beक्रमe calling
		 * handle_futex_death:
		 */
		rc = fetch_robust_entry(&next_entry, &entry->next, &next_pi);
		/*
		 * A pending lock might alपढ़ोy be on the list, so
		 * करोn't process it twice:
		 */
		अगर (entry != pending) अणु
			अगर (handle_futex_death((व्योम __user *)entry + futex_offset,
						curr, pi, HANDLE_DEATH_LIST))
				वापस;
		पूर्ण
		अगर (rc)
			वापस;
		entry = next_entry;
		pi = next_pi;
		/*
		 * Aव्योम excessively दीर्घ or circular lists:
		 */
		अगर (!--limit)
			अवरोध;

		cond_resched();
	पूर्ण

	अगर (pending) अणु
		handle_futex_death((व्योम __user *)pending + futex_offset,
				   curr, pip, HANDLE_DEATH_PENDING);
	पूर्ण
पूर्ण

अटल व्योम futex_cleanup(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (unlikely(tsk->robust_list)) अणु
		निकास_robust_list(tsk);
		tsk->robust_list = शून्य;
	पूर्ण

#अगर_घोषित CONFIG_COMPAT
	अगर (unlikely(tsk->compat_robust_list)) अणु
		compat_निकास_robust_list(tsk);
		tsk->compat_robust_list = शून्य;
	पूर्ण
#पूर्ण_अगर

	अगर (unlikely(!list_empty(&tsk->pi_state_list)))
		निकास_pi_state_list(tsk);
पूर्ण

/**
 * futex_निकास_recursive - Set the tasks futex state to FUTEX_STATE_DEAD
 * @tsk:	task to set the state on
 *
 * Set the futex निकास state of the task lockless. The futex रुकोer code
 * observes that state when a task is निकासing and loops until the task has
 * actually finished the futex cleanup. The worst हाल क्रम this is that the
 * रुकोer runs through the रुको loop until the state becomes visible.
 *
 * This is called from the recursive fault handling path in करो_निकास().
 *
 * This is best efक्रमt. Either the futex निकास code has run alपढ़ोy or
 * not. If the OWNER_DIED bit has been set on the futex then the रुकोer can
 * take it over. If not, the problem is pushed back to user space. If the
 * futex निकास code did not run yet, then an alपढ़ोy queued रुकोer might
 * block क्रमever, but there is nothing which can be करोne about that.
 */
व्योम futex_निकास_recursive(काष्ठा task_काष्ठा *tsk)
अणु
	/* If the state is FUTEX_STATE_EXITING then futex_निकास_mutex is held */
	अगर (tsk->futex_state == FUTEX_STATE_EXITING)
		mutex_unlock(&tsk->futex_निकास_mutex);
	tsk->futex_state = FUTEX_STATE_DEAD;
पूर्ण

अटल व्योम futex_cleanup_begin(काष्ठा task_काष्ठा *tsk)
अणु
	/*
	 * Prevent various race issues against a concurrent incoming रुकोer
	 * including live locks by क्रमcing the रुकोer to block on
	 * tsk->futex_निकास_mutex when it observes FUTEX_STATE_EXITING in
	 * attach_to_pi_owner().
	 */
	mutex_lock(&tsk->futex_निकास_mutex);

	/*
	 * Switch the state to FUTEX_STATE_EXITING under tsk->pi_lock.
	 *
	 * This ensures that all subsequent checks of tsk->futex_state in
	 * attach_to_pi_owner() must observe FUTEX_STATE_EXITING with
	 * tsk->pi_lock held.
	 *
	 * It guarantees also that a pi_state which was queued right beक्रमe
	 * the state change under tsk->pi_lock by a concurrent रुकोer must
	 * be observed in निकास_pi_state_list().
	 */
	raw_spin_lock_irq(&tsk->pi_lock);
	tsk->futex_state = FUTEX_STATE_EXITING;
	raw_spin_unlock_irq(&tsk->pi_lock);
पूर्ण

अटल व्योम futex_cleanup_end(काष्ठा task_काष्ठा *tsk, पूर्णांक state)
अणु
	/*
	 * Lockless store. The only side effect is that an observer might
	 * take another loop until it becomes visible.
	 */
	tsk->futex_state = state;
	/*
	 * Drop the निकास protection. This unblocks रुकोers which observed
	 * FUTEX_STATE_EXITING to reevaluate the state.
	 */
	mutex_unlock(&tsk->futex_निकास_mutex);
पूर्ण

व्योम futex_exec_release(काष्ठा task_काष्ठा *tsk)
अणु
	/*
	 * The state handling is करोne क्रम consistency, but in the हाल of
	 * exec() there is no way to prevent futher damage as the PID stays
	 * the same. But क्रम the unlikely and arguably buggy हाल that a
	 * futex is held on exec(), this provides at least as much state
	 * consistency protection which is possible.
	 */
	futex_cleanup_begin(tsk);
	futex_cleanup(tsk);
	/*
	 * Reset the state to FUTEX_STATE_OK. The task is alive and about
	 * exec a new binary.
	 */
	futex_cleanup_end(tsk, FUTEX_STATE_OK);
पूर्ण

व्योम futex_निकास_release(काष्ठा task_काष्ठा *tsk)
अणु
	futex_cleanup_begin(tsk);
	futex_cleanup(tsk);
	futex_cleanup_end(tsk, FUTEX_STATE_DEAD);
पूर्ण

दीर्घ करो_futex(u32 __user *uaddr, पूर्णांक op, u32 val, kसमय_प्रकार *समयout,
		u32 __user *uaddr2, u32 val2, u32 val3)
अणु
	पूर्णांक cmd = op & FUTEX_CMD_MASK;
	अचिन्हित पूर्णांक flags = 0;

	अगर (!(op & FUTEX_PRIVATE_FLAG))
		flags |= FLAGS_SHARED;

	अगर (op & FUTEX_CLOCK_REALTIME) अणु
		flags |= FLAGS_CLOCKRT;
		अगर (cmd != FUTEX_WAIT_BITSET &&	cmd != FUTEX_WAIT_REQUEUE_PI)
			वापस -ENOSYS;
	पूर्ण

	चयन (cmd) अणु
	हाल FUTEX_LOCK_PI:
	हाल FUTEX_UNLOCK_PI:
	हाल FUTEX_TRYLOCK_PI:
	हाल FUTEX_WAIT_REQUEUE_PI:
	हाल FUTEX_CMP_REQUEUE_PI:
		अगर (!futex_cmpxchg_enabled)
			वापस -ENOSYS;
	पूर्ण

	चयन (cmd) अणु
	हाल FUTEX_WAIT:
		val3 = FUTEX_BITSET_MATCH_ANY;
		fallthrough;
	हाल FUTEX_WAIT_BITSET:
		वापस futex_रुको(uaddr, flags, val, समयout, val3);
	हाल FUTEX_WAKE:
		val3 = FUTEX_BITSET_MATCH_ANY;
		fallthrough;
	हाल FUTEX_WAKE_BITSET:
		वापस futex_wake(uaddr, flags, val, val3);
	हाल FUTEX_REQUEUE:
		वापस futex_requeue(uaddr, flags, uaddr2, val, val2, शून्य, 0);
	हाल FUTEX_CMP_REQUEUE:
		वापस futex_requeue(uaddr, flags, uaddr2, val, val2, &val3, 0);
	हाल FUTEX_WAKE_OP:
		वापस futex_wake_op(uaddr, flags, uaddr2, val, val2, val3);
	हाल FUTEX_LOCK_PI:
		वापस futex_lock_pi(uaddr, flags, समयout, 0);
	हाल FUTEX_UNLOCK_PI:
		वापस futex_unlock_pi(uaddr, flags);
	हाल FUTEX_TRYLOCK_PI:
		वापस futex_lock_pi(uaddr, flags, शून्य, 1);
	हाल FUTEX_WAIT_REQUEUE_PI:
		val3 = FUTEX_BITSET_MATCH_ANY;
		वापस futex_रुको_requeue_pi(uaddr, flags, val, समयout, val3,
					     uaddr2);
	हाल FUTEX_CMP_REQUEUE_PI:
		वापस futex_requeue(uaddr, flags, uaddr2, val, val2, &val3, 1);
	पूर्ण
	वापस -ENOSYS;
पूर्ण

अटल __always_अंतरभूत bool futex_cmd_has_समयout(u32 cmd)
अणु
	चयन (cmd) अणु
	हाल FUTEX_WAIT:
	हाल FUTEX_LOCK_PI:
	हाल FUTEX_WAIT_BITSET:
	हाल FUTEX_WAIT_REQUEUE_PI:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल __always_अंतरभूत पूर्णांक
futex_init_समयout(u32 cmd, u32 op, काष्ठा बारpec64 *ts, kसमय_प्रकार *t)
अणु
	अगर (!बारpec64_valid(ts))
		वापस -EINVAL;

	*t = बारpec64_to_kसमय(*ts);
	अगर (cmd == FUTEX_WAIT)
		*t = kसमय_add_safe(kसमय_get(), *t);
	अन्यथा अगर (cmd != FUTEX_LOCK_PI && !(op & FUTEX_CLOCK_REALTIME))
		*t = समयns_kसमय_प्रकारo_host(CLOCK_MONOTONIC, *t);
	वापस 0;
पूर्ण

SYSCALL_DEFINE6(futex, u32 __user *, uaddr, पूर्णांक, op, u32, val,
		स्थिर काष्ठा __kernel_बारpec __user *, uसमय,
		u32 __user *, uaddr2, u32, val3)
अणु
	पूर्णांक ret, cmd = op & FUTEX_CMD_MASK;
	kसमय_प्रकार t, *tp = शून्य;
	काष्ठा बारpec64 ts;

	अगर (uसमय && futex_cmd_has_समयout(cmd)) अणु
		अगर (unlikely(should_fail_futex(!(op & FUTEX_PRIVATE_FLAG))))
			वापस -EFAULT;
		अगर (get_बारpec64(&ts, uसमय))
			वापस -EFAULT;
		ret = futex_init_समयout(cmd, op, &ts, &t);
		अगर (ret)
			वापस ret;
		tp = &t;
	पूर्ण

	वापस करो_futex(uaddr, op, val, tp, uaddr2, (अचिन्हित दीर्घ)uसमय, val3);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
/*
 * Fetch a robust-list poपूर्णांकer. Bit 0 संकेतs PI futexes:
 */
अटल अंतरभूत पूर्णांक
compat_fetch_robust_entry(compat_uptr_t *uentry, काष्ठा robust_list __user **entry,
		   compat_uptr_t __user *head, अचिन्हित पूर्णांक *pi)
अणु
	अगर (get_user(*uentry, head))
		वापस -EFAULT;

	*entry = compat_ptr((*uentry) & ~1);
	*pi = (अचिन्हित पूर्णांक)(*uentry) & 1;

	वापस 0;
पूर्ण

अटल व्योम __user *futex_uaddr(काष्ठा robust_list __user *entry,
				compat_दीर्घ_t futex_offset)
अणु
	compat_uptr_t base = ptr_to_compat(entry);
	व्योम __user *uaddr = compat_ptr(base + futex_offset);

	वापस uaddr;
पूर्ण

/*
 * Walk curr->robust_list (very carefully, it's a userspace list!)
 * and mark any locks found there dead, and notअगरy any रुकोers.
 *
 * We silently वापस on any sign of list-walking problem.
 */
अटल व्योम compat_निकास_robust_list(काष्ठा task_काष्ठा *curr)
अणु
	काष्ठा compat_robust_list_head __user *head = curr->compat_robust_list;
	काष्ठा robust_list __user *entry, *next_entry, *pending;
	अचिन्हित पूर्णांक limit = ROBUST_LIST_LIMIT, pi, pip;
	अचिन्हित पूर्णांक next_pi;
	compat_uptr_t uentry, next_uentry, upending;
	compat_दीर्घ_t futex_offset;
	पूर्णांक rc;

	अगर (!futex_cmpxchg_enabled)
		वापस;

	/*
	 * Fetch the list head (which was रेजिस्टरed earlier, via
	 * sys_set_robust_list()):
	 */
	अगर (compat_fetch_robust_entry(&uentry, &entry, &head->list.next, &pi))
		वापस;
	/*
	 * Fetch the relative futex offset:
	 */
	अगर (get_user(futex_offset, &head->futex_offset))
		वापस;
	/*
	 * Fetch any possibly pending lock-add first, and handle it
	 * अगर it exists:
	 */
	अगर (compat_fetch_robust_entry(&upending, &pending,
			       &head->list_op_pending, &pip))
		वापस;

	next_entry = शून्य;	/* aव्योम warning with gcc */
	जबतक (entry != (काष्ठा robust_list __user *) &head->list) अणु
		/*
		 * Fetch the next entry in the list beक्रमe calling
		 * handle_futex_death:
		 */
		rc = compat_fetch_robust_entry(&next_uentry, &next_entry,
			(compat_uptr_t __user *)&entry->next, &next_pi);
		/*
		 * A pending lock might alपढ़ोy be on the list, so
		 * करोnt process it twice:
		 */
		अगर (entry != pending) अणु
			व्योम __user *uaddr = futex_uaddr(entry, futex_offset);

			अगर (handle_futex_death(uaddr, curr, pi,
					       HANDLE_DEATH_LIST))
				वापस;
		पूर्ण
		अगर (rc)
			वापस;
		uentry = next_uentry;
		entry = next_entry;
		pi = next_pi;
		/*
		 * Aव्योम excessively दीर्घ or circular lists:
		 */
		अगर (!--limit)
			अवरोध;

		cond_resched();
	पूर्ण
	अगर (pending) अणु
		व्योम __user *uaddr = futex_uaddr(pending, futex_offset);

		handle_futex_death(uaddr, curr, pip, HANDLE_DEATH_PENDING);
	पूर्ण
पूर्ण

COMPAT_SYSCALL_DEFINE2(set_robust_list,
		काष्ठा compat_robust_list_head __user *, head,
		compat_माप_प्रकार, len)
अणु
	अगर (!futex_cmpxchg_enabled)
		वापस -ENOSYS;

	अगर (unlikely(len != माप(*head)))
		वापस -EINVAL;

	current->compat_robust_list = head;

	वापस 0;
पूर्ण

COMPAT_SYSCALL_DEFINE3(get_robust_list, पूर्णांक, pid,
			compat_uptr_t __user *, head_ptr,
			compat_माप_प्रकार __user *, len_ptr)
अणु
	काष्ठा compat_robust_list_head __user *head;
	अचिन्हित दीर्घ ret;
	काष्ठा task_काष्ठा *p;

	अगर (!futex_cmpxchg_enabled)
		वापस -ENOSYS;

	rcu_पढ़ो_lock();

	ret = -ESRCH;
	अगर (!pid)
		p = current;
	अन्यथा अणु
		p = find_task_by_vpid(pid);
		अगर (!p)
			जाओ err_unlock;
	पूर्ण

	ret = -EPERM;
	अगर (!ptrace_may_access(p, PTRACE_MODE_READ_REALCREDS))
		जाओ err_unlock;

	head = p->compat_robust_list;
	rcu_पढ़ो_unlock();

	अगर (put_user(माप(*head), len_ptr))
		वापस -EFAULT;
	वापस put_user(ptr_to_compat(head), head_ptr);

err_unlock:
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
SYSCALL_DEFINE6(futex_समय32, u32 __user *, uaddr, पूर्णांक, op, u32, val,
		स्थिर काष्ठा old_बारpec32 __user *, uसमय, u32 __user *, uaddr2,
		u32, val3)
अणु
	पूर्णांक ret, cmd = op & FUTEX_CMD_MASK;
	kसमय_प्रकार t, *tp = शून्य;
	काष्ठा बारpec64 ts;

	अगर (uसमय && futex_cmd_has_समयout(cmd)) अणु
		अगर (get_old_बारpec32(&ts, uसमय))
			वापस -EFAULT;
		ret = futex_init_समयout(cmd, op, &ts, &t);
		अगर (ret)
			वापस ret;
		tp = &t;
	पूर्ण

	वापस करो_futex(uaddr, op, val, tp, uaddr2, (अचिन्हित दीर्घ)uसमय, val3);
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT_32BIT_TIME */

अटल व्योम __init futex_detect_cmpxchg(व्योम)
अणु
#अगर_अघोषित CONFIG_HAVE_FUTEX_CMPXCHG
	u32 curval;

	/*
	 * This will fail and we want it. Some arch implementations करो
	 * runसमय detection of the futex_atomic_cmpxchg_inatomic()
	 * functionality. We want to know that beक्रमe we call in any
	 * of the complex code paths. Also we want to prevent
	 * registration of robust lists in that हाल. शून्य is
	 * guaranteed to fault and we get -EFAULT on functional
	 * implementation, the non-functional ones will वापस
	 * -ENOSYS.
	 */
	अगर (cmpxchg_futex_value_locked(&curval, शून्य, 0, 0) == -EFAULT)
		futex_cmpxchg_enabled = 1;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init futex_init(व्योम)
अणु
	अचिन्हित पूर्णांक futex_shअगरt;
	अचिन्हित दीर्घ i;

#अगर CONFIG_BASE_SMALL
	futex_hashsize = 16;
#अन्यथा
	futex_hashsize = roundup_घात_of_two(256 * num_possible_cpus());
#पूर्ण_अगर

	futex_queues = alloc_large_प्रणाली_hash("futex", माप(*futex_queues),
					       futex_hashsize, 0,
					       futex_hashsize < 256 ? HASH_SMALL : 0,
					       &futex_shअगरt, शून्य,
					       futex_hashsize, futex_hashsize);
	futex_hashsize = 1UL << futex_shअगरt;

	futex_detect_cmpxchg();

	क्रम (i = 0; i < futex_hashsize; i++) अणु
		atomic_set(&futex_queues[i].रुकोers, 0);
		plist_head_init(&futex_queues[i].chain);
		spin_lock_init(&futex_queues[i].lock);
	पूर्ण

	वापस 0;
पूर्ण
core_initcall(futex_init);
