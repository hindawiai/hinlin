<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) "kcov: " fmt

#घोषणा DISABLE_BRANCH_PROFILING
#समावेश <linux/atomic.h>
#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/preempt.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kcov.h>
#समावेश <linux/refcount.h>
#समावेश <linux/log2.h>
#समावेश <यंत्र/setup.h>

#घोषणा kcov_debug(fmt, ...) pr_debug("%s: " fmt, __func__, ##__VA_ARGS__)

/* Number of 64-bit words written per one comparison: */
#घोषणा KCOV_WORDS_PER_CMP 4

/*
 * kcov descriptor (one per खोलोed debugfs file).
 * State transitions of the descriptor:
 *  - initial state after खोलो()
 *  - then there must be a single ioctl(KCOV_INIT_TRACE) call
 *  - then, mmap() call (several calls are allowed but not useful)
 *  - then, ioctl(KCOV_ENABLE, arg), where arg is
 *	KCOV_TRACE_PC - to trace only the PCs
 *	or
 *	KCOV_TRACE_CMP - to trace only the comparison opeअक्रमs
 *  - then, ioctl(KCOV_DISABLE) to disable the task.
 * Enabling/disabling ioctls can be repeated (only one task a समय allowed).
 */
काष्ठा kcov अणु
	/*
	 * Reference counter. We keep one क्रम:
	 *  - खोलोed file descriptor
	 *  - task with enabled coverage (we can't unwire it from another task)
	 *  - each code section क्रम remote coverage collection
	 */
	refcount_t		refcount;
	/* The lock protects mode, size, area and t. */
	spinlock_t		lock;
	क्रमागत kcov_mode		mode;
	/* Size of arena (in दीर्घ's). */
	अचिन्हित पूर्णांक		size;
	/* Coverage buffer shared with user space. */
	व्योम			*area;
	/* Task क्रम which we collect coverage, or शून्य. */
	काष्ठा task_काष्ठा	*t;
	/* Collecting coverage from remote (background) thपढ़ोs. */
	bool			remote;
	/* Size of remote area (in दीर्घ's). */
	अचिन्हित पूर्णांक		remote_size;
	/*
	 * Sequence is incremented each समय kcov is reenabled, used by
	 * kcov_remote_stop(), see the comment there.
	 */
	पूर्णांक			sequence;
पूर्ण;

काष्ठा kcov_remote_area अणु
	काष्ठा list_head	list;
	अचिन्हित पूर्णांक		size;
पूर्ण;

काष्ठा kcov_remote अणु
	u64			handle;
	काष्ठा kcov		*kcov;
	काष्ठा hlist_node	hnode;
पूर्ण;

अटल DEFINE_SPINLOCK(kcov_remote_lock);
अटल DEFINE_HASHTABLE(kcov_remote_map, 4);
अटल काष्ठा list_head kcov_remote_areas = LIST_HEAD_INIT(kcov_remote_areas);

काष्ठा kcov_percpu_data अणु
	व्योम			*irq_area;

	अचिन्हित पूर्णांक		saved_mode;
	अचिन्हित पूर्णांक		saved_size;
	व्योम			*saved_area;
	काष्ठा kcov		*saved_kcov;
	पूर्णांक			saved_sequence;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा kcov_percpu_data, kcov_percpu_data);

/* Must be called with kcov_remote_lock locked. */
अटल काष्ठा kcov_remote *kcov_remote_find(u64 handle)
अणु
	काष्ठा kcov_remote *remote;

	hash_क्रम_each_possible(kcov_remote_map, remote, hnode, handle) अणु
		अगर (remote->handle == handle)
			वापस remote;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Must be called with kcov_remote_lock locked. */
अटल काष्ठा kcov_remote *kcov_remote_add(काष्ठा kcov *kcov, u64 handle)
अणु
	काष्ठा kcov_remote *remote;

	अगर (kcov_remote_find(handle))
		वापस ERR_PTR(-EEXIST);
	remote = kदो_स्मृति(माप(*remote), GFP_ATOMIC);
	अगर (!remote)
		वापस ERR_PTR(-ENOMEM);
	remote->handle = handle;
	remote->kcov = kcov;
	hash_add(kcov_remote_map, &remote->hnode, handle);
	वापस remote;
पूर्ण

/* Must be called with kcov_remote_lock locked. */
अटल काष्ठा kcov_remote_area *kcov_remote_area_get(अचिन्हित पूर्णांक size)
अणु
	काष्ठा kcov_remote_area *area;
	काष्ठा list_head *pos;

	list_क्रम_each(pos, &kcov_remote_areas) अणु
		area = list_entry(pos, काष्ठा kcov_remote_area, list);
		अगर (area->size == size) अणु
			list_del(&area->list);
			वापस area;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/* Must be called with kcov_remote_lock locked. */
अटल व्योम kcov_remote_area_put(काष्ठा kcov_remote_area *area,
					अचिन्हित पूर्णांक size)
अणु
	INIT_LIST_HEAD(&area->list);
	area->size = size;
	list_add(&area->list, &kcov_remote_areas);
पूर्ण

अटल notrace bool check_kcov_mode(क्रमागत kcov_mode needed_mode, काष्ठा task_काष्ठा *t)
अणु
	अचिन्हित पूर्णांक mode;

	/*
	 * We are पूर्णांकerested in code coverage as a function of a syscall inमाला_दो,
	 * so we ignore code executed in पूर्णांकerrupts, unless we are in a remote
	 * coverage collection section in a softirq.
	 */
	अगर (!in_task() && !(in_serving_softirq() && t->kcov_softirq))
		वापस false;
	mode = READ_ONCE(t->kcov_mode);
	/*
	 * There is some code that runs in पूर्णांकerrupts but क्रम which
	 * in_पूर्णांकerrupt() वापसs false (e.g. preempt_schedule_irq()).
	 * READ_ONCE()/barrier() effectively provides load-acquire wrt
	 * पूर्णांकerrupts, there are paired barrier()/WRITE_ONCE() in
	 * kcov_start().
	 */
	barrier();
	वापस mode == needed_mode;
पूर्ण

अटल notrace अचिन्हित दीर्घ canonicalize_ip(अचिन्हित दीर्घ ip)
अणु
#अगर_घोषित CONFIG_RANDOMIZE_BASE
	ip -= kaslr_offset();
#पूर्ण_अगर
	वापस ip;
पूर्ण

/*
 * Entry poपूर्णांक from instrumented code.
 * This is called once per basic-block/edge.
 */
व्योम notrace __sanitizer_cov_trace_pc(व्योम)
अणु
	काष्ठा task_काष्ठा *t;
	अचिन्हित दीर्घ *area;
	अचिन्हित दीर्घ ip = canonicalize_ip(_RET_IP_);
	अचिन्हित दीर्घ pos;

	t = current;
	अगर (!check_kcov_mode(KCOV_MODE_TRACE_PC, t))
		वापस;

	area = t->kcov_area;
	/* The first 64-bit word is the number of subsequent PCs. */
	pos = READ_ONCE(area[0]) + 1;
	अगर (likely(pos < t->kcov_size)) अणु
		area[pos] = ip;
		WRITE_ONCE(area[0], pos);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__sanitizer_cov_trace_pc);

#अगर_घोषित CONFIG_KCOV_ENABLE_COMPARISONS
अटल व्योम notrace ग_लिखो_comp_data(u64 type, u64 arg1, u64 arg2, u64 ip)
अणु
	काष्ठा task_काष्ठा *t;
	u64 *area;
	u64 count, start_index, end_pos, max_pos;

	t = current;
	अगर (!check_kcov_mode(KCOV_MODE_TRACE_CMP, t))
		वापस;

	ip = canonicalize_ip(ip);

	/*
	 * We ग_लिखो all comparison arguments and types as u64.
	 * The buffer was allocated क्रम t->kcov_size अचिन्हित दीर्घs.
	 */
	area = (u64 *)t->kcov_area;
	max_pos = t->kcov_size * माप(अचिन्हित दीर्घ);

	count = READ_ONCE(area[0]);

	/* Every record is KCOV_WORDS_PER_CMP 64-bit words. */
	start_index = 1 + count * KCOV_WORDS_PER_CMP;
	end_pos = (start_index + KCOV_WORDS_PER_CMP) * माप(u64);
	अगर (likely(end_pos <= max_pos)) अणु
		area[start_index] = type;
		area[start_index + 1] = arg1;
		area[start_index + 2] = arg2;
		area[start_index + 3] = ip;
		WRITE_ONCE(area[0], count + 1);
	पूर्ण
पूर्ण

व्योम notrace __sanitizer_cov_trace_cmp1(u8 arg1, u8 arg2)
अणु
	ग_लिखो_comp_data(KCOV_CMP_SIZE(0), arg1, arg2, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__sanitizer_cov_trace_cmp1);

व्योम notrace __sanitizer_cov_trace_cmp2(u16 arg1, u16 arg2)
अणु
	ग_लिखो_comp_data(KCOV_CMP_SIZE(1), arg1, arg2, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__sanitizer_cov_trace_cmp2);

व्योम notrace __sanitizer_cov_trace_cmp4(u32 arg1, u32 arg2)
अणु
	ग_लिखो_comp_data(KCOV_CMP_SIZE(2), arg1, arg2, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__sanitizer_cov_trace_cmp4);

व्योम notrace __sanitizer_cov_trace_cmp8(u64 arg1, u64 arg2)
अणु
	ग_लिखो_comp_data(KCOV_CMP_SIZE(3), arg1, arg2, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__sanitizer_cov_trace_cmp8);

व्योम notrace __sanitizer_cov_trace_स्थिर_cmp1(u8 arg1, u8 arg2)
अणु
	ग_लिखो_comp_data(KCOV_CMP_SIZE(0) | KCOV_CMP_CONST, arg1, arg2,
			_RET_IP_);
पूर्ण
EXPORT_SYMBOL(__sanitizer_cov_trace_स्थिर_cmp1);

व्योम notrace __sanitizer_cov_trace_स्थिर_cmp2(u16 arg1, u16 arg2)
अणु
	ग_लिखो_comp_data(KCOV_CMP_SIZE(1) | KCOV_CMP_CONST, arg1, arg2,
			_RET_IP_);
पूर्ण
EXPORT_SYMBOL(__sanitizer_cov_trace_स्थिर_cmp2);

व्योम notrace __sanitizer_cov_trace_स्थिर_cmp4(u32 arg1, u32 arg2)
अणु
	ग_लिखो_comp_data(KCOV_CMP_SIZE(2) | KCOV_CMP_CONST, arg1, arg2,
			_RET_IP_);
पूर्ण
EXPORT_SYMBOL(__sanitizer_cov_trace_स्थिर_cmp4);

व्योम notrace __sanitizer_cov_trace_स्थिर_cmp8(u64 arg1, u64 arg2)
अणु
	ग_लिखो_comp_data(KCOV_CMP_SIZE(3) | KCOV_CMP_CONST, arg1, arg2,
			_RET_IP_);
पूर्ण
EXPORT_SYMBOL(__sanitizer_cov_trace_स्थिर_cmp8);

व्योम notrace __sanitizer_cov_trace_चयन(u64 val, u64 *हालs)
अणु
	u64 i;
	u64 count = हालs[0];
	u64 size = हालs[1];
	u64 type = KCOV_CMP_CONST;

	चयन (size) अणु
	हाल 8:
		type |= KCOV_CMP_SIZE(0);
		अवरोध;
	हाल 16:
		type |= KCOV_CMP_SIZE(1);
		अवरोध;
	हाल 32:
		type |= KCOV_CMP_SIZE(2);
		अवरोध;
	हाल 64:
		type |= KCOV_CMP_SIZE(3);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	क्रम (i = 0; i < count; i++)
		ग_लिखो_comp_data(type, हालs[i + 2], val, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__sanitizer_cov_trace_चयन);
#पूर्ण_अगर /* अगरdef CONFIG_KCOV_ENABLE_COMPARISONS */

अटल व्योम kcov_start(काष्ठा task_काष्ठा *t, काष्ठा kcov *kcov,
			अचिन्हित पूर्णांक size, व्योम *area, क्रमागत kcov_mode mode,
			पूर्णांक sequence)
अणु
	kcov_debug("t = %px, size = %u, area = %px\n", t, size, area);
	t->kcov = kcov;
	/* Cache in task काष्ठा क्रम perक्रमmance. */
	t->kcov_size = size;
	t->kcov_area = area;
	t->kcov_sequence = sequence;
	/* See comment in check_kcov_mode(). */
	barrier();
	WRITE_ONCE(t->kcov_mode, mode);
पूर्ण

अटल व्योम kcov_stop(काष्ठा task_काष्ठा *t)
अणु
	WRITE_ONCE(t->kcov_mode, KCOV_MODE_DISABLED);
	barrier();
	t->kcov = शून्य;
	t->kcov_size = 0;
	t->kcov_area = शून्य;
पूर्ण

अटल व्योम kcov_task_reset(काष्ठा task_काष्ठा *t)
अणु
	kcov_stop(t);
	t->kcov_sequence = 0;
	t->kcov_handle = 0;
पूर्ण

व्योम kcov_task_init(काष्ठा task_काष्ठा *t)
अणु
	kcov_task_reset(t);
	t->kcov_handle = current->kcov_handle;
पूर्ण

अटल व्योम kcov_reset(काष्ठा kcov *kcov)
अणु
	kcov->t = शून्य;
	kcov->mode = KCOV_MODE_INIT;
	kcov->remote = false;
	kcov->remote_size = 0;
	kcov->sequence++;
पूर्ण

अटल व्योम kcov_remote_reset(काष्ठा kcov *kcov)
अणु
	पूर्णांक bkt;
	काष्ठा kcov_remote *remote;
	काष्ठा hlist_node *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kcov_remote_lock, flags);
	hash_क्रम_each_safe(kcov_remote_map, bkt, पंचांगp, remote, hnode) अणु
		अगर (remote->kcov != kcov)
			जारी;
		hash_del(&remote->hnode);
		kमुक्त(remote);
	पूर्ण
	/* Do reset beक्रमe unlock to prevent races with kcov_remote_start(). */
	kcov_reset(kcov);
	spin_unlock_irqrestore(&kcov_remote_lock, flags);
पूर्ण

अटल व्योम kcov_disable(काष्ठा task_काष्ठा *t, काष्ठा kcov *kcov)
अणु
	kcov_task_reset(t);
	अगर (kcov->remote)
		kcov_remote_reset(kcov);
	अन्यथा
		kcov_reset(kcov);
पूर्ण

अटल व्योम kcov_get(काष्ठा kcov *kcov)
अणु
	refcount_inc(&kcov->refcount);
पूर्ण

अटल व्योम kcov_put(काष्ठा kcov *kcov)
अणु
	अगर (refcount_dec_and_test(&kcov->refcount)) अणु
		kcov_remote_reset(kcov);
		vमुक्त(kcov->area);
		kमुक्त(kcov);
	पूर्ण
पूर्ण

व्योम kcov_task_निकास(काष्ठा task_काष्ठा *t)
अणु
	काष्ठा kcov *kcov;
	अचिन्हित दीर्घ flags;

	kcov = t->kcov;
	अगर (kcov == शून्य)
		वापस;

	spin_lock_irqsave(&kcov->lock, flags);
	kcov_debug("t = %px, kcov->t = %px\n", t, kcov->t);
	/*
	 * For KCOV_ENABLE devices we want to make sure that t->kcov->t == t,
	 * which comes करोwn to:
	 *        WARN_ON(!kcov->remote && kcov->t != t);
	 *
	 * For KCOV_REMOTE_ENABLE devices, the निकासing task is either:
	 *
	 * 1. A remote task between kcov_remote_start() and kcov_remote_stop().
	 *    In this हाल we should prपूर्णांक a warning right away, since a task
	 *    shouldn't be exiting when it's in a kcov coverage collection
	 *    section. Here t poपूर्णांकs to the task that is collecting remote
	 *    coverage, and t->kcov->t poपूर्णांकs to the thपढ़ो that created the
	 *    kcov device. Which means that to detect this हाल we need to
	 *    check that t != t->kcov->t, and this gives us the following:
	 *        WARN_ON(kcov->remote && kcov->t != t);
	 *
	 * 2. The task that created kcov निकासing without calling KCOV_DISABLE,
	 *    and then again we make sure that t->kcov->t == t:
	 *        WARN_ON(kcov->remote && kcov->t != t);
	 *
	 * By combining all three checks पूर्णांकo one we get:
	 */
	अगर (WARN_ON(kcov->t != t)) अणु
		spin_unlock_irqrestore(&kcov->lock, flags);
		वापस;
	पूर्ण
	/* Just to not leave dangling references behind. */
	kcov_disable(t, kcov);
	spin_unlock_irqrestore(&kcov->lock, flags);
	kcov_put(kcov);
पूर्ण

अटल पूर्णांक kcov_mmap(काष्ठा file *filep, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक res = 0;
	व्योम *area;
	काष्ठा kcov *kcov = vma->vm_file->निजी_data;
	अचिन्हित दीर्घ size, off;
	काष्ठा page *page;
	अचिन्हित दीर्घ flags;

	area = vदो_स्मृति_user(vma->vm_end - vma->vm_start);
	अगर (!area)
		वापस -ENOMEM;

	spin_lock_irqsave(&kcov->lock, flags);
	size = kcov->size * माप(अचिन्हित दीर्घ);
	अगर (kcov->mode != KCOV_MODE_INIT || vma->vm_pgoff != 0 ||
	    vma->vm_end - vma->vm_start != size) अणु
		res = -EINVAL;
		जाओ निकास;
	पूर्ण
	अगर (!kcov->area) अणु
		kcov->area = area;
		vma->vm_flags |= VM_DONTEXPAND;
		spin_unlock_irqrestore(&kcov->lock, flags);
		क्रम (off = 0; off < size; off += PAGE_SIZE) अणु
			page = vदो_स्मृति_to_page(kcov->area + off);
			अगर (vm_insert_page(vma, vma->vm_start + off, page))
				WARN_ONCE(1, "vm_insert_page() failed");
		पूर्ण
		वापस 0;
	पूर्ण
निकास:
	spin_unlock_irqrestore(&kcov->lock, flags);
	vमुक्त(area);
	वापस res;
पूर्ण

अटल पूर्णांक kcov_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा kcov *kcov;

	kcov = kzalloc(माप(*kcov), GFP_KERNEL);
	अगर (!kcov)
		वापस -ENOMEM;
	kcov->mode = KCOV_MODE_DISABLED;
	kcov->sequence = 1;
	refcount_set(&kcov->refcount, 1);
	spin_lock_init(&kcov->lock);
	filep->निजी_data = kcov;
	वापस nonseekable_खोलो(inode, filep);
पूर्ण

अटल पूर्णांक kcov_बंद(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	kcov_put(filep->निजी_data);
	वापस 0;
पूर्ण

अटल पूर्णांक kcov_get_mode(अचिन्हित दीर्घ arg)
अणु
	अगर (arg == KCOV_TRACE_PC)
		वापस KCOV_MODE_TRACE_PC;
	अन्यथा अगर (arg == KCOV_TRACE_CMP)
#अगर_घोषित CONFIG_KCOV_ENABLE_COMPARISONS
		वापस KCOV_MODE_TRACE_CMP;
#अन्यथा
		वापस -ENOTSUPP;
#पूर्ण_अगर
	अन्यथा
		वापस -EINVAL;
पूर्ण

/*
 * Fault in a lazily-faulted vदो_स्मृति area beक्रमe it can be used by
 * __santizer_cov_trace_pc(), to aव्योम recursion issues अगर any code on the
 * vदो_स्मृति fault handling path is instrumented.
 */
अटल व्योम kcov_fault_in_area(काष्ठा kcov *kcov)
अणु
	अचिन्हित दीर्घ stride = PAGE_SIZE / माप(अचिन्हित दीर्घ);
	अचिन्हित दीर्घ *area = kcov->area;
	अचिन्हित दीर्घ offset;

	क्रम (offset = 0; offset < kcov->size; offset += stride)
		READ_ONCE(area[offset]);
पूर्ण

अटल अंतरभूत bool kcov_check_handle(u64 handle, bool common_valid,
				bool uncommon_valid, bool zero_valid)
अणु
	अगर (handle & ~(KCOV_SUBSYSTEM_MASK | KCOV_INSTANCE_MASK))
		वापस false;
	चयन (handle & KCOV_SUBSYSTEM_MASK) अणु
	हाल KCOV_SUBSYSTEM_COMMON:
		वापस (handle & KCOV_INSTANCE_MASK) ?
			common_valid : zero_valid;
	हाल KCOV_SUBSYSTEM_USB:
		वापस uncommon_valid;
	शेष:
		वापस false;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक kcov_ioctl_locked(काष्ठा kcov *kcov, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	काष्ठा task_काष्ठा *t;
	अचिन्हित दीर्घ size, unused;
	पूर्णांक mode, i;
	काष्ठा kcov_remote_arg *remote_arg;
	काष्ठा kcov_remote *remote;
	अचिन्हित दीर्घ flags;

	चयन (cmd) अणु
	हाल KCOV_INIT_TRACE:
		/*
		 * Enable kcov in trace mode and setup buffer size.
		 * Must happen beक्रमe anything अन्यथा.
		 */
		अगर (kcov->mode != KCOV_MODE_DISABLED)
			वापस -EBUSY;
		/*
		 * Size must be at least 2 to hold current position and one PC.
		 * Later we allocate size * माप(अचिन्हित दीर्घ) memory,
		 * that must not overflow.
		 */
		size = arg;
		अगर (size < 2 || size > पूर्णांक_उच्च / माप(अचिन्हित दीर्घ))
			वापस -EINVAL;
		kcov->size = size;
		kcov->mode = KCOV_MODE_INIT;
		वापस 0;
	हाल KCOV_ENABLE:
		/*
		 * Enable coverage क्रम the current task.
		 * At this poपूर्णांक user must have been enabled trace mode,
		 * and mmapped the file. Coverage collection is disabled only
		 * at task निकास or voluntary by KCOV_DISABLE. After that it can
		 * be enabled क्रम another task.
		 */
		अगर (kcov->mode != KCOV_MODE_INIT || !kcov->area)
			वापस -EINVAL;
		t = current;
		अगर (kcov->t != शून्य || t->kcov != शून्य)
			वापस -EBUSY;
		mode = kcov_get_mode(arg);
		अगर (mode < 0)
			वापस mode;
		kcov_fault_in_area(kcov);
		kcov->mode = mode;
		kcov_start(t, kcov, kcov->size, kcov->area, kcov->mode,
				kcov->sequence);
		kcov->t = t;
		/* Put either in kcov_task_निकास() or in KCOV_DISABLE. */
		kcov_get(kcov);
		वापस 0;
	हाल KCOV_DISABLE:
		/* Disable coverage क्रम the current task. */
		unused = arg;
		अगर (unused != 0 || current->kcov != kcov)
			वापस -EINVAL;
		t = current;
		अगर (WARN_ON(kcov->t != t))
			वापस -EINVAL;
		kcov_disable(t, kcov);
		kcov_put(kcov);
		वापस 0;
	हाल KCOV_REMOTE_ENABLE:
		अगर (kcov->mode != KCOV_MODE_INIT || !kcov->area)
			वापस -EINVAL;
		t = current;
		अगर (kcov->t != शून्य || t->kcov != शून्य)
			वापस -EBUSY;
		remote_arg = (काष्ठा kcov_remote_arg *)arg;
		mode = kcov_get_mode(remote_arg->trace_mode);
		अगर (mode < 0)
			वापस mode;
		अगर (remote_arg->area_size > दीर्घ_उच्च / माप(अचिन्हित दीर्घ))
			वापस -EINVAL;
		kcov->mode = mode;
		t->kcov = kcov;
		kcov->t = t;
		kcov->remote = true;
		kcov->remote_size = remote_arg->area_size;
		spin_lock_irqsave(&kcov_remote_lock, flags);
		क्रम (i = 0; i < remote_arg->num_handles; i++) अणु
			अगर (!kcov_check_handle(remote_arg->handles[i],
						false, true, false)) अणु
				spin_unlock_irqrestore(&kcov_remote_lock,
							flags);
				kcov_disable(t, kcov);
				वापस -EINVAL;
			पूर्ण
			remote = kcov_remote_add(kcov, remote_arg->handles[i]);
			अगर (IS_ERR(remote)) अणु
				spin_unlock_irqrestore(&kcov_remote_lock,
							flags);
				kcov_disable(t, kcov);
				वापस PTR_ERR(remote);
			पूर्ण
		पूर्ण
		अगर (remote_arg->common_handle) अणु
			अगर (!kcov_check_handle(remote_arg->common_handle,
						true, false, false)) अणु
				spin_unlock_irqrestore(&kcov_remote_lock,
							flags);
				kcov_disable(t, kcov);
				वापस -EINVAL;
			पूर्ण
			remote = kcov_remote_add(kcov,
					remote_arg->common_handle);
			अगर (IS_ERR(remote)) अणु
				spin_unlock_irqrestore(&kcov_remote_lock,
							flags);
				kcov_disable(t, kcov);
				वापस PTR_ERR(remote);
			पूर्ण
			t->kcov_handle = remote_arg->common_handle;
		पूर्ण
		spin_unlock_irqrestore(&kcov_remote_lock, flags);
		/* Put either in kcov_task_निकास() or in KCOV_DISABLE. */
		kcov_get(kcov);
		वापस 0;
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल दीर्घ kcov_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kcov *kcov;
	पूर्णांक res;
	काष्ठा kcov_remote_arg *remote_arg = शून्य;
	अचिन्हित पूर्णांक remote_num_handles;
	अचिन्हित दीर्घ remote_arg_size;
	अचिन्हित दीर्घ flags;

	अगर (cmd == KCOV_REMOTE_ENABLE) अणु
		अगर (get_user(remote_num_handles, (अचिन्हित __user *)(arg +
				दुरत्व(काष्ठा kcov_remote_arg, num_handles))))
			वापस -EFAULT;
		अगर (remote_num_handles > KCOV_REMOTE_MAX_HANDLES)
			वापस -EINVAL;
		remote_arg_size = काष्ठा_size(remote_arg, handles,
					remote_num_handles);
		remote_arg = memdup_user((व्योम __user *)arg, remote_arg_size);
		अगर (IS_ERR(remote_arg))
			वापस PTR_ERR(remote_arg);
		अगर (remote_arg->num_handles != remote_num_handles) अणु
			kमुक्त(remote_arg);
			वापस -EINVAL;
		पूर्ण
		arg = (अचिन्हित दीर्घ)remote_arg;
	पूर्ण

	kcov = filep->निजी_data;
	spin_lock_irqsave(&kcov->lock, flags);
	res = kcov_ioctl_locked(kcov, cmd, arg);
	spin_unlock_irqrestore(&kcov->lock, flags);

	kमुक्त(remote_arg);

	वापस res;
पूर्ण

अटल स्थिर काष्ठा file_operations kcov_fops = अणु
	.खोलो		= kcov_खोलो,
	.unlocked_ioctl	= kcov_ioctl,
	.compat_ioctl	= kcov_ioctl,
	.mmap		= kcov_mmap,
	.release        = kcov_बंद,
पूर्ण;

/*
 * kcov_remote_start() and kcov_remote_stop() can be used to annotate a section
 * of code in a kernel background thपढ़ो or in a softirq to allow kcov to be
 * used to collect coverage from that part of code.
 *
 * The handle argument of kcov_remote_start() identअगरies a code section that is
 * used क्रम coverage collection. A userspace process passes this handle to
 * KCOV_REMOTE_ENABLE ioctl to make the used kcov device start collecting
 * coverage क्रम the code section identअगरied by this handle.
 *
 * The usage of these annotations in the kernel code is dअगरferent depending on
 * the type of the kernel thपढ़ो whose code is being annotated.
 *
 * For global kernel thपढ़ोs that are spawned in a limited number of instances
 * (e.g. one USB hub_event() worker thपढ़ो is spawned per USB HCD) and क्रम
 * softirqs, each instance must be asचिन्हित a unique 4-byte instance id. The
 * instance id is then combined with a 1-byte subप्रणाली id to get a handle via
 * kcov_remote_handle(subप्रणाली_id, instance_id).
 *
 * For local kernel thपढ़ोs that are spawned from प्रणाली calls handler when a
 * user पूर्णांकeracts with some kernel पूर्णांकerface (e.g. vhost workers), a handle is
 * passed from a userspace process as the common_handle field of the
 * kcov_remote_arg काष्ठा (note, that the user must generate a handle by using
 * kcov_remote_handle() with KCOV_SUBSYSTEM_COMMON as the subप्रणाली id and an
 * arbitrary 4-byte non-zero number as the instance id). This common handle
 * then माला_लो saved पूर्णांकo the task_काष्ठा of the process that issued the
 * KCOV_REMOTE_ENABLE ioctl. When this process issues प्रणाली calls that spawn
 * kernel thपढ़ोs, the common handle must be retrieved via kcov_common_handle()
 * and passed to the spawned thपढ़ोs via custom annotations. Those kernel
 * thपढ़ोs must in turn be annotated with kcov_remote_start(common_handle) and
 * kcov_remote_stop(). All of the thपढ़ोs that are spawned by the same process
 * obtain the same handle, hence the name "common".
 *
 * See Documentation/dev-tools/kcov.rst क्रम more details.
 *
 * Internally, kcov_remote_start() looks up the kcov device associated with the
 * provided handle, allocates an area क्रम coverage collection, and saves the
 * poपूर्णांकers to kcov and area पूर्णांकo the current task_काष्ठा to allow coverage to
 * be collected via __sanitizer_cov_trace_pc().
 * In turns kcov_remote_stop() clears those poपूर्णांकers from task_काष्ठा to stop
 * collecting coverage and copies all collected coverage पूर्णांकo the kcov area.
 */

अटल अंतरभूत bool kcov_mode_enabled(अचिन्हित पूर्णांक mode)
अणु
	वापस (mode & ~KCOV_IN_CTXSW) != KCOV_MODE_DISABLED;
पूर्ण

अटल व्योम kcov_remote_softirq_start(काष्ठा task_काष्ठा *t)
अणु
	काष्ठा kcov_percpu_data *data = this_cpu_ptr(&kcov_percpu_data);
	अचिन्हित पूर्णांक mode;

	mode = READ_ONCE(t->kcov_mode);
	barrier();
	अगर (kcov_mode_enabled(mode)) अणु
		data->saved_mode = mode;
		data->saved_size = t->kcov_size;
		data->saved_area = t->kcov_area;
		data->saved_sequence = t->kcov_sequence;
		data->saved_kcov = t->kcov;
		kcov_stop(t);
	पूर्ण
पूर्ण

अटल व्योम kcov_remote_softirq_stop(काष्ठा task_काष्ठा *t)
अणु
	काष्ठा kcov_percpu_data *data = this_cpu_ptr(&kcov_percpu_data);

	अगर (data->saved_kcov) अणु
		kcov_start(t, data->saved_kcov, data->saved_size,
				data->saved_area, data->saved_mode,
				data->saved_sequence);
		data->saved_mode = 0;
		data->saved_size = 0;
		data->saved_area = शून्य;
		data->saved_sequence = 0;
		data->saved_kcov = शून्य;
	पूर्ण
पूर्ण

व्योम kcov_remote_start(u64 handle)
अणु
	काष्ठा task_काष्ठा *t = current;
	काष्ठा kcov_remote *remote;
	काष्ठा kcov *kcov;
	अचिन्हित पूर्णांक mode;
	व्योम *area;
	अचिन्हित पूर्णांक size;
	पूर्णांक sequence;
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(!kcov_check_handle(handle, true, true, true)))
		वापस;
	अगर (!in_task() && !in_serving_softirq())
		वापस;

	local_irq_save(flags);

	/*
	 * Check that kcov_remote_start() is not called twice in background
	 * thपढ़ोs nor called by user tasks (with enabled kcov).
	 */
	mode = READ_ONCE(t->kcov_mode);
	अगर (WARN_ON(in_task() && kcov_mode_enabled(mode))) अणु
		local_irq_restore(flags);
		वापस;
	पूर्ण
	/*
	 * Check that kcov_remote_start() is not called twice in softirqs.
	 * Note, that kcov_remote_start() can be called from a softirq that
	 * happened जबतक collecting coverage from a background thपढ़ो.
	 */
	अगर (WARN_ON(in_serving_softirq() && t->kcov_softirq)) अणु
		local_irq_restore(flags);
		वापस;
	पूर्ण

	spin_lock(&kcov_remote_lock);
	remote = kcov_remote_find(handle);
	अगर (!remote) अणु
		spin_unlock_irqrestore(&kcov_remote_lock, flags);
		वापस;
	पूर्ण
	kcov_debug("handle = %llx, context: %s\n", handle,
			in_task() ? "task" : "softirq");
	kcov = remote->kcov;
	/* Put in kcov_remote_stop(). */
	kcov_get(kcov);
	/*
	 * Read kcov fields beक्रमe unlock to prevent races with
	 * KCOV_DISABLE / kcov_remote_reset().
	 */
	mode = kcov->mode;
	sequence = kcov->sequence;
	अगर (in_task()) अणु
		size = kcov->remote_size;
		area = kcov_remote_area_get(size);
	पूर्ण अन्यथा अणु
		size = CONFIG_KCOV_IRQ_AREA_SIZE;
		area = this_cpu_ptr(&kcov_percpu_data)->irq_area;
	पूर्ण
	spin_unlock_irqrestore(&kcov_remote_lock, flags);

	/* Can only happen when in_task(). */
	अगर (!area) अणु
		area = vदो_स्मृति(size * माप(अचिन्हित दीर्घ));
		अगर (!area) अणु
			kcov_put(kcov);
			वापस;
		पूर्ण
	पूर्ण

	local_irq_save(flags);

	/* Reset coverage size. */
	*(u64 *)area = 0;

	अगर (in_serving_softirq()) अणु
		kcov_remote_softirq_start(t);
		t->kcov_softirq = 1;
	पूर्ण
	kcov_start(t, kcov, size, area, mode, sequence);

	local_irq_restore(flags);

पूर्ण
EXPORT_SYMBOL(kcov_remote_start);

अटल व्योम kcov_move_area(क्रमागत kcov_mode mode, व्योम *dst_area,
				अचिन्हित पूर्णांक dst_area_size, व्योम *src_area)
अणु
	u64 word_size = माप(अचिन्हित दीर्घ);
	u64 count_size, entry_size_log;
	u64 dst_len, src_len;
	व्योम *dst_entries, *src_entries;
	u64 dst_occupied, dst_मुक्त, bytes_to_move, entries_moved;

	kcov_debug("%px %u <= %px %lu\n",
		dst_area, dst_area_size, src_area, *(अचिन्हित दीर्घ *)src_area);

	चयन (mode) अणु
	हाल KCOV_MODE_TRACE_PC:
		dst_len = READ_ONCE(*(अचिन्हित दीर्घ *)dst_area);
		src_len = *(अचिन्हित दीर्घ *)src_area;
		count_size = माप(अचिन्हित दीर्घ);
		entry_size_log = __ilog2_u64(माप(अचिन्हित दीर्घ));
		अवरोध;
	हाल KCOV_MODE_TRACE_CMP:
		dst_len = READ_ONCE(*(u64 *)dst_area);
		src_len = *(u64 *)src_area;
		count_size = माप(u64);
		BUILD_BUG_ON(!is_घातer_of_2(KCOV_WORDS_PER_CMP));
		entry_size_log = __ilog2_u64(माप(u64) * KCOV_WORDS_PER_CMP);
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	/* As arm can't भागide u64 पूर्णांकegers use log of entry size. */
	अगर (dst_len > ((dst_area_size * word_size - count_size) >>
				entry_size_log))
		वापस;
	dst_occupied = count_size + (dst_len << entry_size_log);
	dst_मुक्त = dst_area_size * word_size - dst_occupied;
	bytes_to_move = min(dst_मुक्त, src_len << entry_size_log);
	dst_entries = dst_area + dst_occupied;
	src_entries = src_area + count_size;
	स_नकल(dst_entries, src_entries, bytes_to_move);
	entries_moved = bytes_to_move >> entry_size_log;

	चयन (mode) अणु
	हाल KCOV_MODE_TRACE_PC:
		WRITE_ONCE(*(अचिन्हित दीर्घ *)dst_area, dst_len + entries_moved);
		अवरोध;
	हाल KCOV_MODE_TRACE_CMP:
		WRITE_ONCE(*(u64 *)dst_area, dst_len + entries_moved);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/* See the comment beक्रमe kcov_remote_start() क्रम usage details. */
व्योम kcov_remote_stop(व्योम)
अणु
	काष्ठा task_काष्ठा *t = current;
	काष्ठा kcov *kcov;
	अचिन्हित पूर्णांक mode;
	व्योम *area;
	अचिन्हित पूर्णांक size;
	पूर्णांक sequence;
	अचिन्हित दीर्घ flags;

	अगर (!in_task() && !in_serving_softirq())
		वापस;

	local_irq_save(flags);

	mode = READ_ONCE(t->kcov_mode);
	barrier();
	अगर (!kcov_mode_enabled(mode)) अणु
		local_irq_restore(flags);
		वापस;
	पूर्ण
	/*
	 * When in softirq, check अगर the corresponding kcov_remote_start()
	 * actually found the remote handle and started collecting coverage.
	 */
	अगर (in_serving_softirq() && !t->kcov_softirq) अणु
		local_irq_restore(flags);
		वापस;
	पूर्ण
	/* Make sure that kcov_softirq is only set when in softirq. */
	अगर (WARN_ON(!in_serving_softirq() && t->kcov_softirq)) अणु
		local_irq_restore(flags);
		वापस;
	पूर्ण

	kcov = t->kcov;
	area = t->kcov_area;
	size = t->kcov_size;
	sequence = t->kcov_sequence;

	kcov_stop(t);
	अगर (in_serving_softirq()) अणु
		t->kcov_softirq = 0;
		kcov_remote_softirq_stop(t);
	पूर्ण

	spin_lock(&kcov->lock);
	/*
	 * KCOV_DISABLE could have been called between kcov_remote_start()
	 * and kcov_remote_stop(), hence the sequence check.
	 */
	अगर (sequence == kcov->sequence && kcov->remote)
		kcov_move_area(kcov->mode, kcov->area, kcov->size, area);
	spin_unlock(&kcov->lock);

	अगर (in_task()) अणु
		spin_lock(&kcov_remote_lock);
		kcov_remote_area_put(area, size);
		spin_unlock(&kcov_remote_lock);
	पूर्ण

	local_irq_restore(flags);

	/* Get in kcov_remote_start(). */
	kcov_put(kcov);
पूर्ण
EXPORT_SYMBOL(kcov_remote_stop);

/* See the comment beक्रमe kcov_remote_start() क्रम usage details. */
u64 kcov_common_handle(व्योम)
अणु
	अगर (!in_task())
		वापस 0;
	वापस current->kcov_handle;
पूर्ण
EXPORT_SYMBOL(kcov_common_handle);

अटल पूर्णांक __init kcov_init(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		व्योम *area = vदो_स्मृति(CONFIG_KCOV_IRQ_AREA_SIZE *
				माप(अचिन्हित दीर्घ));
		अगर (!area)
			वापस -ENOMEM;
		per_cpu_ptr(&kcov_percpu_data, cpu)->irq_area = area;
	पूर्ण

	/*
	 * The kcov debugfs file won't ever get हटाओd and thus,
	 * there is no need to protect it against removal races. The
	 * use of debugfs_create_file_unsafe() is actually safe here.
	 */
	debugfs_create_file_unsafe("kcov", 0600, शून्य, शून्य, &kcov_fops);

	वापस 0;
पूर्ण

device_initcall(kcov_init);
