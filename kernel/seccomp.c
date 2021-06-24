<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/kernel/seccomp.c
 *
 * Copyright 2004-2005  Andrea Arcangeli <andrea@cpushare.com>
 *
 * Copyright (C) 2012 Google, Inc.
 * Will Drewry <wad@chromium.org>
 *
 * This defines a simple but solid secure-computing facility.
 *
 * Mode 1 uses a fixed list of allowed प्रणाली calls.
 * Mode 2 allows user-defined प्रणाली call filters in the क्रमm
 *        of Berkeley Packet Filters/Linux Socket Filters.
 */
#घोषणा pr_fmt(fmt) "seccomp: " fmt

#समावेश <linux/refcount.h>
#समावेश <linux/audit.h>
#समावेश <linux/compat.h>
#समावेश <linux/coredump.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/nospec.h>
#समावेश <linux/prctl.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/sysctl.h>

#अगर_घोषित CONFIG_HAVE_ARCH_SECCOMP_FILTER
#समावेश <यंत्र/syscall.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECCOMP_FILTER
#समावेश <linux/file.h>
#समावेश <linux/filter.h>
#समावेश <linux/pid.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/capability.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/lockdep.h>

/*
 * When SECCOMP_IOCTL_NOTIF_ID_VALID was first पूर्णांकroduced, it had the
 * wrong direction flag in the ioctl number. This is the broken one,
 * which the kernel needs to keep supporting until all userspaces stop
 * using the wrong command number.
 */
#घोषणा SECCOMP_IOCTL_NOTIF_ID_VALID_WRONG_सूची	SECCOMP_IOR(2, __u64)

क्रमागत notअगरy_state अणु
	SECCOMP_NOTIFY_INIT,
	SECCOMP_NOTIFY_SENT,
	SECCOMP_NOTIFY_REPLIED,
पूर्ण;

काष्ठा seccomp_knotअगर अणु
	/* The काष्ठा pid of the task whose filter triggered the notअगरication */
	काष्ठा task_काष्ठा *task;

	/* The "cookie" क्रम this request; this is unique क्रम this filter. */
	u64 id;

	/*
	 * The seccomp data. This poपूर्णांकer is valid the entire समय this
	 * notअगरication is active, since it comes from __seccomp_filter which
	 * eclipses the entire lअगरecycle here.
	 */
	स्थिर काष्ठा seccomp_data *data;

	/*
	 * Notअगरication states. When SECCOMP_RET_USER_NOTIF is वापसed, a
	 * काष्ठा seccomp_knotअगर is created and starts out in INIT. Once the
	 * handler पढ़ोs the notअगरication off of an FD, it transitions to SENT.
	 * If a संकेत is received the state transitions back to INIT and
	 * another message is sent. When the userspace handler replies, state
	 * transitions to REPLIED.
	 */
	क्रमागत notअगरy_state state;

	/* The वापस values, only valid when in SECCOMP_NOTIFY_REPLIED */
	पूर्णांक error;
	दीर्घ val;
	u32 flags;

	/*
	 * Signals when this has changed states, such as the listener
	 * dying, a new seccomp addfd message, or changing to REPLIED
	 */
	काष्ठा completion पढ़ोy;

	काष्ठा list_head list;

	/* outstanding addfd requests */
	काष्ठा list_head addfd;
पूर्ण;

/**
 * काष्ठा seccomp_kaddfd - container क्रम seccomp_addfd ioctl messages
 *
 * @file: A reference to the file to install in the other task
 * @fd: The fd number to install it at. If the fd number is -1, it means the
 *      installing process should allocate the fd as normal.
 * @flags: The flags क्रम the new file descriptor. At the moment, only O_CLOEXEC
 *         is allowed.
 * @ret: The वापस value of the installing process. It is set to the fd num
 *       upon success (>= 0).
 * @completion: Indicates that the installing process has completed fd
 *              installation, or gone away (either due to successful
 *              reply, or संकेत)
 *
 */
काष्ठा seccomp_kaddfd अणु
	काष्ठा file *file;
	पूर्णांक fd;
	अचिन्हित पूर्णांक flags;

	जोड़ अणु
		bool setfd;
		/* To only be set on reply */
		पूर्णांक ret;
	पूर्ण;
	काष्ठा completion completion;
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा notअगरication - container क्रम seccomp userspace notअगरications. Since
 * most seccomp filters will not have notअगरication listeners attached and this
 * काष्ठाure is fairly large, we store the notअगरication-specअगरic stuff in a
 * separate काष्ठाure.
 *
 * @request: A semaphore that users of this notअगरication can रुको on क्रम
 *           changes. Actual पढ़ोs and ग_लिखोs are still controlled with
 *           filter->notअगरy_lock.
 * @next_id: The id of the next request.
 * @notअगरications: A list of काष्ठा seccomp_knotअगर elements.
 */
काष्ठा notअगरication अणु
	काष्ठा semaphore request;
	u64 next_id;
	काष्ठा list_head notअगरications;
पूर्ण;

#अगर_घोषित SECCOMP_ARCH_NATIVE
/**
 * काष्ठा action_cache - per-filter cache of seccomp actions per
 * arch/syscall pair
 *
 * @allow_native: A biपंचांगap where each bit represents whether the
 *		  filter will always allow the syscall, क्रम the
 *		  native architecture.
 * @allow_compat: A biपंचांगap where each bit represents whether the
 *		  filter will always allow the syscall, क्रम the
 *		  compat architecture.
 */
काष्ठा action_cache अणु
	DECLARE_BITMAP(allow_native, SECCOMP_ARCH_NATIVE_NR);
#अगर_घोषित SECCOMP_ARCH_COMPAT
	DECLARE_BITMAP(allow_compat, SECCOMP_ARCH_COMPAT_NR);
#पूर्ण_अगर
पूर्ण;
#अन्यथा
काष्ठा action_cache अणु पूर्ण;

अटल अंतरभूत bool seccomp_cache_check_allow(स्थिर काष्ठा seccomp_filter *sfilter,
					     स्थिर काष्ठा seccomp_data *sd)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम seccomp_cache_prepare(काष्ठा seccomp_filter *sfilter)
अणु
पूर्ण
#पूर्ण_अगर /* SECCOMP_ARCH_NATIVE */

/**
 * काष्ठा seccomp_filter - container क्रम seccomp BPF programs
 *
 * @refs: Reference count to manage the object lअगरeसमय.
 *	  A filter's reference count is incremented क्रम each directly
 *	  attached task, once क्रम the dependent filter, and अगर
 *	  requested क्रम the user notअगरier. When @refs reaches zero,
 *	  the filter can be मुक्तd.
 * @users: A filter's @users count is incremented क्रम each directly
 *         attached task (filter installation, विभाजन(), thपढ़ो_sync),
 *	   and once क्रम the dependent filter (tracked in filter->prev).
 *	   When it reaches zero it indicates that no direct or indirect
 *	   users of that filter exist. No new tasks can get associated with
 *	   this filter after reaching 0. The @users count is always smaller
 *	   or equal to @refs. Hence, reaching 0 क्रम @users करोes not mean
 *	   the filter can be मुक्तd.
 * @cache: cache of arch/syscall mappings to actions
 * @log: true अगर all actions except क्रम SECCOMP_RET_ALLOW should be logged
 * @prev: poपूर्णांकs to a previously installed, or inherited, filter
 * @prog: the BPF program to evaluate
 * @notअगर: the काष्ठा that holds all notअगरication related inक्रमmation
 * @notअगरy_lock: A lock क्रम all notअगरication-related accesses.
 * @wqh: A रुको queue क्रम poll अगर a notअगरier is in use.
 *
 * seccomp_filter objects are organized in a tree linked via the @prev
 * poपूर्णांकer.  For any task, it appears to be a singly-linked list starting
 * with current->seccomp.filter, the most recently attached or inherited filter.
 * However, multiple filters may share a @prev node, by way of विभाजन(), which
 * results in a unidirectional tree existing in memory.  This is similar to
 * how namespaces work.
 *
 * seccomp_filter objects should never be modअगरied after being attached
 * to a task_काष्ठा (other than @refs).
 */
काष्ठा seccomp_filter अणु
	refcount_t refs;
	refcount_t users;
	bool log;
	काष्ठा action_cache cache;
	काष्ठा seccomp_filter *prev;
	काष्ठा bpf_prog *prog;
	काष्ठा notअगरication *notअगर;
	काष्ठा mutex notअगरy_lock;
	रुको_queue_head_t wqh;
पूर्ण;

/* Limit any path through the tree to 256KB worth of inकाष्ठाions. */
#घोषणा MAX_INSNS_PER_PATH ((1 << 18) / माप(काष्ठा sock_filter))

/*
 * Endianness is explicitly ignored and left क्रम BPF program authors to manage
 * as per the specअगरic architecture.
 */
अटल व्योम populate_seccomp_data(काष्ठा seccomp_data *sd)
अणु
	/*
	 * Instead of using current_pt_reg(), we're alपढ़ोy करोing the work
	 * to safely fetch "current", so just use "task" everywhere below.
	 */
	काष्ठा task_काष्ठा *task = current;
	काष्ठा pt_regs *regs = task_pt_regs(task);
	अचिन्हित दीर्घ args[6];

	sd->nr = syscall_get_nr(task, regs);
	sd->arch = syscall_get_arch(task);
	syscall_get_arguments(task, regs, args);
	sd->args[0] = args[0];
	sd->args[1] = args[1];
	sd->args[2] = args[2];
	sd->args[3] = args[3];
	sd->args[4] = args[4];
	sd->args[5] = args[5];
	sd->inकाष्ठाion_poपूर्णांकer = KSTK_EIP(task);
पूर्ण

/**
 *	seccomp_check_filter - verअगरy seccomp filter code
 *	@filter: filter to verअगरy
 *	@flen: length of filter
 *
 * Takes a previously checked filter (by bpf_check_classic) and
 * redirects all filter code that loads काष्ठा sk_buff data
 * and related data through seccomp_bpf_load.  It also
 * enक्रमces length and alignment checking of those loads.
 *
 * Returns 0 अगर the rule set is legal or -EINVAL अगर not.
 */
अटल पूर्णांक seccomp_check_filter(काष्ठा sock_filter *filter, अचिन्हित पूर्णांक flen)
अणु
	पूर्णांक pc;
	क्रम (pc = 0; pc < flen; pc++) अणु
		काष्ठा sock_filter *ftest = &filter[pc];
		u16 code = ftest->code;
		u32 k = ftest->k;

		चयन (code) अणु
		हाल BPF_LD | BPF_W | BPF_ABS:
			ftest->code = BPF_LDX | BPF_W | BPF_ABS;
			/* 32-bit aligned and not out of bounds. */
			अगर (k >= माप(काष्ठा seccomp_data) || k & 3)
				वापस -EINVAL;
			जारी;
		हाल BPF_LD | BPF_W | BPF_LEN:
			ftest->code = BPF_LD | BPF_IMM;
			ftest->k = माप(काष्ठा seccomp_data);
			जारी;
		हाल BPF_LDX | BPF_W | BPF_LEN:
			ftest->code = BPF_LDX | BPF_IMM;
			ftest->k = माप(काष्ठा seccomp_data);
			जारी;
		/* Explicitly include allowed calls. */
		हाल BPF_RET | BPF_K:
		हाल BPF_RET | BPF_A:
		हाल BPF_ALU | BPF_ADD | BPF_K:
		हाल BPF_ALU | BPF_ADD | BPF_X:
		हाल BPF_ALU | BPF_SUB | BPF_K:
		हाल BPF_ALU | BPF_SUB | BPF_X:
		हाल BPF_ALU | BPF_MUL | BPF_K:
		हाल BPF_ALU | BPF_MUL | BPF_X:
		हाल BPF_ALU | BPF_DIV | BPF_K:
		हाल BPF_ALU | BPF_DIV | BPF_X:
		हाल BPF_ALU | BPF_AND | BPF_K:
		हाल BPF_ALU | BPF_AND | BPF_X:
		हाल BPF_ALU | BPF_OR | BPF_K:
		हाल BPF_ALU | BPF_OR | BPF_X:
		हाल BPF_ALU | BPF_XOR | BPF_K:
		हाल BPF_ALU | BPF_XOR | BPF_X:
		हाल BPF_ALU | BPF_LSH | BPF_K:
		हाल BPF_ALU | BPF_LSH | BPF_X:
		हाल BPF_ALU | BPF_RSH | BPF_K:
		हाल BPF_ALU | BPF_RSH | BPF_X:
		हाल BPF_ALU | BPF_NEG:
		हाल BPF_LD | BPF_IMM:
		हाल BPF_LDX | BPF_IMM:
		हाल BPF_MISC | BPF_TAX:
		हाल BPF_MISC | BPF_TXA:
		हाल BPF_LD | BPF_MEM:
		हाल BPF_LDX | BPF_MEM:
		हाल BPF_ST:
		हाल BPF_STX:
		हाल BPF_JMP | BPF_JA:
		हाल BPF_JMP | BPF_JEQ | BPF_K:
		हाल BPF_JMP | BPF_JEQ | BPF_X:
		हाल BPF_JMP | BPF_JGE | BPF_K:
		हाल BPF_JMP | BPF_JGE | BPF_X:
		हाल BPF_JMP | BPF_JGT | BPF_K:
		हाल BPF_JMP | BPF_JGT | BPF_X:
		हाल BPF_JMP | BPF_JSET | BPF_K:
		हाल BPF_JMP | BPF_JSET | BPF_X:
			जारी;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित SECCOMP_ARCH_NATIVE
अटल अंतरभूत bool seccomp_cache_check_allow_biपंचांगap(स्थिर व्योम *biपंचांगap,
						    माप_प्रकार biपंचांगap_size,
						    पूर्णांक syscall_nr)
अणु
	अगर (unlikely(syscall_nr < 0 || syscall_nr >= biपंचांगap_size))
		वापस false;
	syscall_nr = array_index_nospec(syscall_nr, biपंचांगap_size);

	वापस test_bit(syscall_nr, biपंचांगap);
पूर्ण

/**
 * seccomp_cache_check_allow - lookup seccomp cache
 * @sfilter: The seccomp filter
 * @sd: The seccomp data to lookup the cache with
 *
 * Returns true अगर the seccomp_data is cached and allowed.
 */
अटल अंतरभूत bool seccomp_cache_check_allow(स्थिर काष्ठा seccomp_filter *sfilter,
					     स्थिर काष्ठा seccomp_data *sd)
अणु
	पूर्णांक syscall_nr = sd->nr;
	स्थिर काष्ठा action_cache *cache = &sfilter->cache;

#अगर_अघोषित SECCOMP_ARCH_COMPAT
	/* A native-only architecture करोesn't need to check sd->arch. */
	वापस seccomp_cache_check_allow_biपंचांगap(cache->allow_native,
						SECCOMP_ARCH_NATIVE_NR,
						syscall_nr);
#अन्यथा
	अगर (likely(sd->arch == SECCOMP_ARCH_NATIVE))
		वापस seccomp_cache_check_allow_biपंचांगap(cache->allow_native,
							SECCOMP_ARCH_NATIVE_NR,
							syscall_nr);
	अगर (likely(sd->arch == SECCOMP_ARCH_COMPAT))
		वापस seccomp_cache_check_allow_biपंचांगap(cache->allow_compat,
							SECCOMP_ARCH_COMPAT_NR,
							syscall_nr);
#पूर्ण_अगर /* SECCOMP_ARCH_COMPAT */

	WARN_ON_ONCE(true);
	वापस false;
पूर्ण
#पूर्ण_अगर /* SECCOMP_ARCH_NATIVE */

/**
 * seccomp_run_filters - evaluates all seccomp filters against @sd
 * @sd: optional seccomp data to be passed to filters
 * @match: stores काष्ठा seccomp_filter that resulted in the वापस value,
 *         unless filter वापसed SECCOMP_RET_ALLOW, in which हाल it will
 *         be unchanged.
 *
 * Returns valid seccomp BPF response codes.
 */
#घोषणा ACTION_ONLY(ret) ((s32)((ret) & (SECCOMP_RET_ACTION_FULL)))
अटल u32 seccomp_run_filters(स्थिर काष्ठा seccomp_data *sd,
			       काष्ठा seccomp_filter **match)
अणु
	u32 ret = SECCOMP_RET_ALLOW;
	/* Make sure cross-thपढ़ो synced filter poपूर्णांकs somewhere sane. */
	काष्ठा seccomp_filter *f =
			READ_ONCE(current->seccomp.filter);

	/* Ensure unexpected behavior करोesn't result in failing खोलो. */
	अगर (WARN_ON(f == शून्य))
		वापस SECCOMP_RET_KILL_PROCESS;

	अगर (seccomp_cache_check_allow(f, sd))
		वापस SECCOMP_RET_ALLOW;

	/*
	 * All filters in the list are evaluated and the lowest BPF वापस
	 * value always takes priority (ignoring the DATA).
	 */
	क्रम (; f; f = f->prev) अणु
		u32 cur_ret = bpf_prog_run_pin_on_cpu(f->prog, sd);

		अगर (ACTION_ONLY(cur_ret) < ACTION_ONLY(ret)) अणु
			ret = cur_ret;
			*match = f;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_SECCOMP_FILTER */

अटल अंतरभूत bool seccomp_may_assign_mode(अचिन्हित दीर्घ seccomp_mode)
अणु
	निश्चित_spin_locked(&current->sighand->siglock);

	अगर (current->seccomp.mode && current->seccomp.mode != seccomp_mode)
		वापस false;

	वापस true;
पूर्ण

व्योम __weak arch_seccomp_spec_mitigate(काष्ठा task_काष्ठा *task) अणु पूर्ण

अटल अंतरभूत व्योम seccomp_assign_mode(काष्ठा task_काष्ठा *task,
				       अचिन्हित दीर्घ seccomp_mode,
				       अचिन्हित दीर्घ flags)
अणु
	निश्चित_spin_locked(&task->sighand->siglock);

	task->seccomp.mode = seccomp_mode;
	/*
	 * Make sure SYSCALL_WORK_SECCOMP cannot be set beक्रमe the mode (and
	 * filter) is set.
	 */
	smp_mb__beक्रमe_atomic();
	/* Assume शेष seccomp processes want spec flaw mitigation. */
	अगर ((flags & SECCOMP_FILTER_FLAG_SPEC_ALLOW) == 0)
		arch_seccomp_spec_mitigate(task);
	set_task_syscall_work(task, SECCOMP);
पूर्ण

#अगर_घोषित CONFIG_SECCOMP_FILTER
/* Returns 1 अगर the parent is an ancestor of the child. */
अटल पूर्णांक is_ancestor(काष्ठा seccomp_filter *parent,
		       काष्ठा seccomp_filter *child)
अणु
	/* शून्य is the root ancestor. */
	अगर (parent == शून्य)
		वापस 1;
	क्रम (; child; child = child->prev)
		अगर (child == parent)
			वापस 1;
	वापस 0;
पूर्ण

/**
 * seccomp_can_sync_thपढ़ोs: checks अगर all thपढ़ोs can be synchronized
 *
 * Expects sighand and cred_guard_mutex locks to be held.
 *
 * Returns 0 on success, -ve on error, or the pid of a thपढ़ो which was
 * either not in the correct seccomp mode or did not have an ancestral
 * seccomp filter.
 */
अटल अंतरभूत pid_t seccomp_can_sync_thपढ़ोs(व्योम)
अणु
	काष्ठा task_काष्ठा *thपढ़ो, *caller;

	BUG_ON(!mutex_is_locked(&current->संकेत->cred_guard_mutex));
	निश्चित_spin_locked(&current->sighand->siglock);

	/* Validate all thपढ़ोs being eligible क्रम synchronization. */
	caller = current;
	क्रम_each_thपढ़ो(caller, thपढ़ो) अणु
		pid_t failed;

		/* Skip current, since it is initiating the sync. */
		अगर (thपढ़ो == caller)
			जारी;

		अगर (thपढ़ो->seccomp.mode == SECCOMP_MODE_DISABLED ||
		    (thपढ़ो->seccomp.mode == SECCOMP_MODE_FILTER &&
		     is_ancestor(thपढ़ो->seccomp.filter,
				 caller->seccomp.filter)))
			जारी;

		/* Return the first thपढ़ो that cannot be synchronized. */
		failed = task_pid_vnr(thपढ़ो);
		/* If the pid cannot be resolved, then वापस -ESRCH */
		अगर (WARN_ON(failed == 0))
			failed = -ESRCH;
		वापस failed;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम seccomp_filter_मुक्त(काष्ठा seccomp_filter *filter)
अणु
	अगर (filter) अणु
		bpf_prog_destroy(filter->prog);
		kमुक्त(filter);
	पूर्ण
पूर्ण

अटल व्योम __seccomp_filter_orphan(काष्ठा seccomp_filter *orig)
अणु
	जबतक (orig && refcount_dec_and_test(&orig->users)) अणु
		अगर (रुकोqueue_active(&orig->wqh))
			wake_up_poll(&orig->wqh, EPOLLHUP);
		orig = orig->prev;
	पूर्ण
पूर्ण

अटल व्योम __put_seccomp_filter(काष्ठा seccomp_filter *orig)
अणु
	/* Clean up single-reference branches iteratively. */
	जबतक (orig && refcount_dec_and_test(&orig->refs)) अणु
		काष्ठा seccomp_filter *मुक्तme = orig;
		orig = orig->prev;
		seccomp_filter_मुक्त(मुक्तme);
	पूर्ण
पूर्ण

अटल व्योम __seccomp_filter_release(काष्ठा seccomp_filter *orig)
अणु
	/* Notअगरy about any unused filters in the task's क्रमmer filter tree. */
	__seccomp_filter_orphan(orig);
	/* Finally drop all references to the task's क्रमmer tree. */
	__put_seccomp_filter(orig);
पूर्ण

/**
 * seccomp_filter_release - Detach the task from its filter tree,
 *			    drop its reference count, and notअगरy
 *			    about unused filters
 *
 * This function should only be called when the task is निकासing as
 * it detaches it from its filter tree. As such, READ_ONCE() and
 * barriers are not needed here, as would normally be needed.
 */
व्योम seccomp_filter_release(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा seccomp_filter *orig = tsk->seccomp.filter;

	/* We are effectively holding the siglock by not having any sighand. */
	WARN_ON(tsk->sighand != शून्य);

	/* Detach task from its filter tree. */
	tsk->seccomp.filter = शून्य;
	__seccomp_filter_release(orig);
पूर्ण

/**
 * seccomp_sync_thपढ़ोs: sets all thपढ़ोs to use current's filter
 *
 * Expects sighand and cred_guard_mutex locks to be held, and क्रम
 * seccomp_can_sync_thपढ़ोs() to have वापसed success alपढ़ोy
 * without dropping the locks.
 *
 */
अटल अंतरभूत व्योम seccomp_sync_thपढ़ोs(अचिन्हित दीर्घ flags)
अणु
	काष्ठा task_काष्ठा *thपढ़ो, *caller;

	BUG_ON(!mutex_is_locked(&current->संकेत->cred_guard_mutex));
	निश्चित_spin_locked(&current->sighand->siglock);

	/* Synchronize all thपढ़ोs. */
	caller = current;
	क्रम_each_thपढ़ो(caller, thपढ़ो) अणु
		/* Skip current, since it needs no changes. */
		अगर (thपढ़ो == caller)
			जारी;

		/* Get a task reference क्रम the new leaf node. */
		get_seccomp_filter(caller);

		/*
		 * Drop the task reference to the shared ancestor since
		 * current's path will hold a reference.  (This also
		 * allows a put beक्रमe the assignment.)
		 */
		__seccomp_filter_release(thपढ़ो->seccomp.filter);

		/* Make our new filter tree visible. */
		smp_store_release(&thपढ़ो->seccomp.filter,
				  caller->seccomp.filter);
		atomic_set(&thपढ़ो->seccomp.filter_count,
			   atomic_पढ़ो(&thपढ़ो->seccomp.filter_count));

		/*
		 * Don't let an unprivileged task work around
		 * the no_new_privs restriction by creating
		 * a thपढ़ो that sets it up, enters seccomp,
		 * then dies.
		 */
		अगर (task_no_new_privs(caller))
			task_set_no_new_privs(thपढ़ो);

		/*
		 * Opt the other thपढ़ो पूर्णांकo seccomp अगर needed.
		 * As thपढ़ोs are considered to be trust-realm
		 * equivalent (see ptrace_may_access), it is safe to
		 * allow one thपढ़ो to transition the other.
		 */
		अगर (thपढ़ो->seccomp.mode == SECCOMP_MODE_DISABLED)
			seccomp_assign_mode(thपढ़ो, SECCOMP_MODE_FILTER,
					    flags);
	पूर्ण
पूर्ण

/**
 * seccomp_prepare_filter: Prepares a seccomp filter क्रम use.
 * @fprog: BPF program to install
 *
 * Returns filter on success or an ERR_PTR on failure.
 */
अटल काष्ठा seccomp_filter *seccomp_prepare_filter(काष्ठा sock_fprog *fprog)
अणु
	काष्ठा seccomp_filter *sfilter;
	पूर्णांक ret;
	स्थिर bool save_orig =
#अगर defined(CONFIG_CHECKPOINT_RESTORE) || defined(SECCOMP_ARCH_NATIVE)
		true;
#अन्यथा
		false;
#पूर्ण_अगर

	अगर (fprog->len == 0 || fprog->len > BPF_MAXINSNS)
		वापस ERR_PTR(-EINVAL);

	BUG_ON(पूर्णांक_उच्च / fprog->len < माप(काष्ठा sock_filter));

	/*
	 * Installing a seccomp filter requires that the task has
	 * CAP_SYS_ADMIN in its namespace or be running with no_new_privs.
	 * This aव्योमs scenarios where unprivileged tasks can affect the
	 * behavior of privileged children.
	 */
	अगर (!task_no_new_privs(current) &&
			!ns_capable_noaudit(current_user_ns(), CAP_SYS_ADMIN))
		वापस ERR_PTR(-EACCES);

	/* Allocate a new seccomp_filter */
	sfilter = kzalloc(माप(*sfilter), GFP_KERNEL | __GFP_NOWARN);
	अगर (!sfilter)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&sfilter->notअगरy_lock);
	ret = bpf_prog_create_from_user(&sfilter->prog, fprog,
					seccomp_check_filter, save_orig);
	अगर (ret < 0) अणु
		kमुक्त(sfilter);
		वापस ERR_PTR(ret);
	पूर्ण

	refcount_set(&sfilter->refs, 1);
	refcount_set(&sfilter->users, 1);
	init_रुकोqueue_head(&sfilter->wqh);

	वापस sfilter;
पूर्ण

/**
 * seccomp_prepare_user_filter - prepares a user-supplied sock_fprog
 * @user_filter: poपूर्णांकer to the user data containing a sock_fprog.
 *
 * Returns 0 on success and non-zero otherwise.
 */
अटल काष्ठा seccomp_filter *
seccomp_prepare_user_filter(स्थिर अक्षर __user *user_filter)
अणु
	काष्ठा sock_fprog fprog;
	काष्ठा seccomp_filter *filter = ERR_PTR(-EFAULT);

#अगर_घोषित CONFIG_COMPAT
	अगर (in_compat_syscall()) अणु
		काष्ठा compat_sock_fprog fprog32;
		अगर (copy_from_user(&fprog32, user_filter, माप(fprog32)))
			जाओ out;
		fprog.len = fprog32.len;
		fprog.filter = compat_ptr(fprog32.filter);
	पूर्ण अन्यथा /* falls through to the अगर below. */
#पूर्ण_अगर
	अगर (copy_from_user(&fprog, user_filter, माप(fprog)))
		जाओ out;
	filter = seccomp_prepare_filter(&fprog);
out:
	वापस filter;
पूर्ण

#अगर_घोषित SECCOMP_ARCH_NATIVE
/**
 * seccomp_is_स्थिर_allow - check अगर filter is स्थिरant allow with given data
 * @fprog: The BPF programs
 * @sd: The seccomp data to check against, only syscall number and arch
 *      number are considered स्थिरant.
 */
अटल bool seccomp_is_स्थिर_allow(काष्ठा sock_fprog_kern *fprog,
				   काष्ठा seccomp_data *sd)
अणु
	अचिन्हित पूर्णांक reg_value = 0;
	अचिन्हित पूर्णांक pc;
	bool op_res;

	अगर (WARN_ON_ONCE(!fprog))
		वापस false;

	क्रम (pc = 0; pc < fprog->len; pc++) अणु
		काष्ठा sock_filter *insn = &fprog->filter[pc];
		u16 code = insn->code;
		u32 k = insn->k;

		चयन (code) अणु
		हाल BPF_LD | BPF_W | BPF_ABS:
			चयन (k) अणु
			हाल दुरत्व(काष्ठा seccomp_data, nr):
				reg_value = sd->nr;
				अवरोध;
			हाल दुरत्व(काष्ठा seccomp_data, arch):
				reg_value = sd->arch;
				अवरोध;
			शेष:
				/* can't optimize (non-स्थिरant value load) */
				वापस false;
			पूर्ण
			अवरोध;
		हाल BPF_RET | BPF_K:
			/* reached वापस with स्थिरant values only, check allow */
			वापस k == SECCOMP_RET_ALLOW;
		हाल BPF_JMP | BPF_JA:
			pc += insn->k;
			अवरोध;
		हाल BPF_JMP | BPF_JEQ | BPF_K:
		हाल BPF_JMP | BPF_JGE | BPF_K:
		हाल BPF_JMP | BPF_JGT | BPF_K:
		हाल BPF_JMP | BPF_JSET | BPF_K:
			चयन (BPF_OP(code)) अणु
			हाल BPF_JEQ:
				op_res = reg_value == k;
				अवरोध;
			हाल BPF_JGE:
				op_res = reg_value >= k;
				अवरोध;
			हाल BPF_JGT:
				op_res = reg_value > k;
				अवरोध;
			हाल BPF_JSET:
				op_res = !!(reg_value & k);
				अवरोध;
			शेष:
				/* can't optimize (unknown jump) */
				वापस false;
			पूर्ण

			pc += op_res ? insn->jt : insn->jf;
			अवरोध;
		हाल BPF_ALU | BPF_AND | BPF_K:
			reg_value &= k;
			अवरोध;
		शेष:
			/* can't optimize (unknown insn) */
			वापस false;
		पूर्ण
	पूर्ण

	/* ran off the end of the filter?! */
	WARN_ON(1);
	वापस false;
पूर्ण

अटल व्योम seccomp_cache_prepare_biपंचांगap(काष्ठा seccomp_filter *sfilter,
					 व्योम *biपंचांगap, स्थिर व्योम *biपंचांगap_prev,
					 माप_प्रकार biपंचांगap_size, पूर्णांक arch)
अणु
	काष्ठा sock_fprog_kern *fprog = sfilter->prog->orig_prog;
	काष्ठा seccomp_data sd;
	पूर्णांक nr;

	अगर (biपंचांगap_prev) अणु
		/* The new filter must be as restrictive as the last. */
		biपंचांगap_copy(biपंचांगap, biपंचांगap_prev, biपंचांगap_size);
	पूर्ण अन्यथा अणु
		/* Beक्रमe any filters, all syscalls are always allowed. */
		biपंचांगap_fill(biपंचांगap, biपंचांगap_size);
	पूर्ण

	क्रम (nr = 0; nr < biपंचांगap_size; nr++) अणु
		/* No biपंचांगap change: not a cacheable action. */
		अगर (!test_bit(nr, biपंचांगap))
			जारी;

		sd.nr = nr;
		sd.arch = arch;

		/* No biपंचांगap change: जारी to always allow. */
		अगर (seccomp_is_स्थिर_allow(fprog, &sd))
			जारी;

		/*
		 * Not a cacheable action: always run filters.
		 * atomic clear_bit() not needed, filter not visible yet.
		 */
		__clear_bit(nr, biपंचांगap);
	पूर्ण
पूर्ण

/**
 * seccomp_cache_prepare - emulate the filter to find cacheable syscalls
 * @sfilter: The seccomp filter
 *
 * Returns 0 अगर successful or -त्रुटि_सं अगर error occurred.
 */
अटल व्योम seccomp_cache_prepare(काष्ठा seccomp_filter *sfilter)
अणु
	काष्ठा action_cache *cache = &sfilter->cache;
	स्थिर काष्ठा action_cache *cache_prev =
		sfilter->prev ? &sfilter->prev->cache : शून्य;

	seccomp_cache_prepare_biपंचांगap(sfilter, cache->allow_native,
				     cache_prev ? cache_prev->allow_native : शून्य,
				     SECCOMP_ARCH_NATIVE_NR,
				     SECCOMP_ARCH_NATIVE);

#अगर_घोषित SECCOMP_ARCH_COMPAT
	seccomp_cache_prepare_biपंचांगap(sfilter, cache->allow_compat,
				     cache_prev ? cache_prev->allow_compat : शून्य,
				     SECCOMP_ARCH_COMPAT_NR,
				     SECCOMP_ARCH_COMPAT);
#पूर्ण_अगर /* SECCOMP_ARCH_COMPAT */
पूर्ण
#पूर्ण_अगर /* SECCOMP_ARCH_NATIVE */

/**
 * seccomp_attach_filter: validate and attach filter
 * @flags:  flags to change filter behavior
 * @filter: seccomp filter to add to the current process
 *
 * Caller must be holding current->sighand->siglock lock.
 *
 * Returns 0 on success, -ve on error, or
 *   - in TSYNC mode: the pid of a thपढ़ो which was either not in the correct
 *     seccomp mode or did not have an ancestral seccomp filter
 *   - in NEW_LISTENER mode: the fd of the new listener
 */
अटल दीर्घ seccomp_attach_filter(अचिन्हित पूर्णांक flags,
				  काष्ठा seccomp_filter *filter)
अणु
	अचिन्हित दीर्घ total_insns;
	काष्ठा seccomp_filter *walker;

	निश्चित_spin_locked(&current->sighand->siglock);

	/* Validate resulting filter length. */
	total_insns = filter->prog->len;
	क्रम (walker = current->seccomp.filter; walker; walker = walker->prev)
		total_insns += walker->prog->len + 4;  /* 4 instr penalty */
	अगर (total_insns > MAX_INSNS_PER_PATH)
		वापस -ENOMEM;

	/* If thपढ़ो sync has been requested, check that it is possible. */
	अगर (flags & SECCOMP_FILTER_FLAG_TSYNC) अणु
		पूर्णांक ret;

		ret = seccomp_can_sync_thपढ़ोs();
		अगर (ret) अणु
			अगर (flags & SECCOMP_FILTER_FLAG_TSYNC_ESRCH)
				वापस -ESRCH;
			अन्यथा
				वापस ret;
		पूर्ण
	पूर्ण

	/* Set log flag, अगर present. */
	अगर (flags & SECCOMP_FILTER_FLAG_LOG)
		filter->log = true;

	/*
	 * If there is an existing filter, make it the prev and करोn't drop its
	 * task reference.
	 */
	filter->prev = current->seccomp.filter;
	seccomp_cache_prepare(filter);
	current->seccomp.filter = filter;
	atomic_inc(&current->seccomp.filter_count);

	/* Now that the new filter is in place, synchronize to all thपढ़ोs. */
	अगर (flags & SECCOMP_FILTER_FLAG_TSYNC)
		seccomp_sync_thपढ़ोs(flags);

	वापस 0;
पूर्ण

अटल व्योम __get_seccomp_filter(काष्ठा seccomp_filter *filter)
अणु
	refcount_inc(&filter->refs);
पूर्ण

/* get_seccomp_filter - increments the reference count of the filter on @tsk */
व्योम get_seccomp_filter(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा seccomp_filter *orig = tsk->seccomp.filter;
	अगर (!orig)
		वापस;
	__get_seccomp_filter(orig);
	refcount_inc(&orig->users);
पूर्ण

अटल व्योम seccomp_init_siginfo(kernel_siginfo_t *info, पूर्णांक syscall, पूर्णांक reason)
अणु
	clear_siginfo(info);
	info->si_signo = SIGSYS;
	info->si_code = SYS_SECCOMP;
	info->si_call_addr = (व्योम __user *)KSTK_EIP(current);
	info->si_त्रुटि_सं = reason;
	info->si_arch = syscall_get_arch(current);
	info->si_syscall = syscall;
पूर्ण

/**
 * seccomp_send_sigsys - संकेतs the task to allow in-process syscall emulation
 * @syscall: syscall number to send to userland
 * @reason: filter-supplied reason code to send to userland (via si_त्रुटि_सं)
 *
 * Forces a SIGSYS with a code of SYS_SECCOMP and related sigsys info.
 */
अटल व्योम seccomp_send_sigsys(पूर्णांक syscall, पूर्णांक reason)
अणु
	काष्ठा kernel_siginfo info;
	seccomp_init_siginfo(&info, syscall, reason);
	क्रमce_sig_info(&info);
पूर्ण
#पूर्ण_अगर	/* CONFIG_SECCOMP_FILTER */

/* For use with seccomp_actions_logged */
#घोषणा SECCOMP_LOG_KILL_PROCESS	(1 << 0)
#घोषणा SECCOMP_LOG_KILL_THREAD		(1 << 1)
#घोषणा SECCOMP_LOG_TRAP		(1 << 2)
#घोषणा SECCOMP_LOG_ERRNO		(1 << 3)
#घोषणा SECCOMP_LOG_TRACE		(1 << 4)
#घोषणा SECCOMP_LOG_LOG			(1 << 5)
#घोषणा SECCOMP_LOG_ALLOW		(1 << 6)
#घोषणा SECCOMP_LOG_USER_NOTIF		(1 << 7)

अटल u32 seccomp_actions_logged = SECCOMP_LOG_KILL_PROCESS |
				    SECCOMP_LOG_KILL_THREAD  |
				    SECCOMP_LOG_TRAP  |
				    SECCOMP_LOG_ERRNO |
				    SECCOMP_LOG_USER_NOTIF |
				    SECCOMP_LOG_TRACE |
				    SECCOMP_LOG_LOG;

अटल अंतरभूत व्योम seccomp_log(अचिन्हित दीर्घ syscall, दीर्घ signr, u32 action,
			       bool requested)
अणु
	bool log = false;

	चयन (action) अणु
	हाल SECCOMP_RET_ALLOW:
		अवरोध;
	हाल SECCOMP_RET_TRAP:
		log = requested && seccomp_actions_logged & SECCOMP_LOG_TRAP;
		अवरोध;
	हाल SECCOMP_RET_ERRNO:
		log = requested && seccomp_actions_logged & SECCOMP_LOG_ERRNO;
		अवरोध;
	हाल SECCOMP_RET_TRACE:
		log = requested && seccomp_actions_logged & SECCOMP_LOG_TRACE;
		अवरोध;
	हाल SECCOMP_RET_USER_NOTIF:
		log = requested && seccomp_actions_logged & SECCOMP_LOG_USER_NOTIF;
		अवरोध;
	हाल SECCOMP_RET_LOG:
		log = seccomp_actions_logged & SECCOMP_LOG_LOG;
		अवरोध;
	हाल SECCOMP_RET_KILL_THREAD:
		log = seccomp_actions_logged & SECCOMP_LOG_KILL_THREAD;
		अवरोध;
	हाल SECCOMP_RET_KILL_PROCESS:
	शेष:
		log = seccomp_actions_logged & SECCOMP_LOG_KILL_PROCESS;
	पूर्ण

	/*
	 * Emit an audit message when the action is RET_KILL_*, RET_LOG, or the
	 * FILTER_FLAG_LOG bit was set. The admin has the ability to silence
	 * any action from being logged by removing the action name from the
	 * seccomp_actions_logged sysctl.
	 */
	अगर (!log)
		वापस;

	audit_seccomp(syscall, signr, action);
पूर्ण

/*
 * Secure computing mode 1 allows only पढ़ो/ग_लिखो/निकास/sigवापस.
 * To be fully secure this must be combined with rlimit
 * to limit the stack allocations too.
 */
अटल स्थिर पूर्णांक mode1_syscalls[] = अणु
	__NR_seccomp_पढ़ो, __NR_seccomp_ग_लिखो, __NR_seccomp_निकास, __NR_seccomp_sigवापस,
	-1, /* negative terminated */
पूर्ण;

अटल व्योम __secure_computing_strict(पूर्णांक this_syscall)
अणु
	स्थिर पूर्णांक *allowed_syscalls = mode1_syscalls;
#अगर_घोषित CONFIG_COMPAT
	अगर (in_compat_syscall())
		allowed_syscalls = get_compat_mode1_syscalls();
#पूर्ण_अगर
	करो अणु
		अगर (*allowed_syscalls == this_syscall)
			वापस;
	पूर्ण जबतक (*++allowed_syscalls != -1);

#अगर_घोषित SECCOMP_DEBUG
	dump_stack();
#पूर्ण_अगर
	seccomp_log(this_syscall, SIGKILL, SECCOMP_RET_KILL_THREAD, true);
	करो_निकास(SIGKILL);
पूर्ण

#अगर_अघोषित CONFIG_HAVE_ARCH_SECCOMP_FILTER
व्योम secure_computing_strict(पूर्णांक this_syscall)
अणु
	पूर्णांक mode = current->seccomp.mode;

	अगर (IS_ENABLED(CONFIG_CHECKPOINT_RESTORE) &&
	    unlikely(current->ptrace & PT_SUSPEND_SECCOMP))
		वापस;

	अगर (mode == SECCOMP_MODE_DISABLED)
		वापस;
	अन्यथा अगर (mode == SECCOMP_MODE_STRICT)
		__secure_computing_strict(this_syscall);
	अन्यथा
		BUG();
पूर्ण
#अन्यथा

#अगर_घोषित CONFIG_SECCOMP_FILTER
अटल u64 seccomp_next_notअगरy_id(काष्ठा seccomp_filter *filter)
अणु
	/*
	 * Note: overflow is ok here, the id just needs to be unique per
	 * filter.
	 */
	lockdep_निश्चित_held(&filter->notअगरy_lock);
	वापस filter->notअगर->next_id++;
पूर्ण

अटल व्योम seccomp_handle_addfd(काष्ठा seccomp_kaddfd *addfd)
अणु
	/*
	 * Remove the notअगरication, and reset the list poपूर्णांकers, indicating
	 * that it has been handled.
	 */
	list_del_init(&addfd->list);
	अगर (!addfd->setfd)
		addfd->ret = receive_fd(addfd->file, addfd->flags);
	अन्यथा
		addfd->ret = receive_fd_replace(addfd->fd, addfd->file,
						addfd->flags);
	complete(&addfd->completion);
पूर्ण

अटल पूर्णांक seccomp_करो_user_notअगरication(पूर्णांक this_syscall,
					काष्ठा seccomp_filter *match,
					स्थिर काष्ठा seccomp_data *sd)
अणु
	पूर्णांक err;
	u32 flags = 0;
	दीर्घ ret = 0;
	काष्ठा seccomp_knotअगर n = अणुपूर्ण;
	काष्ठा seccomp_kaddfd *addfd, *पंचांगp;

	mutex_lock(&match->notअगरy_lock);
	err = -ENOSYS;
	अगर (!match->notअगर)
		जाओ out;

	n.task = current;
	n.state = SECCOMP_NOTIFY_INIT;
	n.data = sd;
	n.id = seccomp_next_notअगरy_id(match);
	init_completion(&n.पढ़ोy);
	list_add(&n.list, &match->notअगर->notअगरications);
	INIT_LIST_HEAD(&n.addfd);

	up(&match->notअगर->request);
	wake_up_poll(&match->wqh, EPOLLIN | EPOLLRDNORM);

	/*
	 * This is where we रुको क्रम a reply from userspace.
	 */
	करो अणु
		mutex_unlock(&match->notअगरy_lock);
		err = रुको_क्रम_completion_पूर्णांकerruptible(&n.पढ़ोy);
		mutex_lock(&match->notअगरy_lock);
		अगर (err != 0)
			जाओ पूर्णांकerrupted;

		addfd = list_first_entry_or_null(&n.addfd,
						 काष्ठा seccomp_kaddfd, list);
		/* Check अगर we were woken up by a addfd message */
		अगर (addfd)
			seccomp_handle_addfd(addfd);

	पूर्ण  जबतक (n.state != SECCOMP_NOTIFY_REPLIED);

	ret = n.val;
	err = n.error;
	flags = n.flags;

पूर्णांकerrupted:
	/* If there were any pending addfd calls, clear them out */
	list_क्रम_each_entry_safe(addfd, पंचांगp, &n.addfd, list) अणु
		/* The process went away beक्रमe we got a chance to handle it */
		addfd->ret = -ESRCH;
		list_del_init(&addfd->list);
		complete(&addfd->completion);
	पूर्ण

	/*
	 * Note that it's possible the listener died in between the समय when
	 * we were notअगरied of a response (or a संकेत) and when we were able to
	 * re-acquire the lock, so only delete from the list अगर the
	 * notअगरication actually exists.
	 *
	 * Also note that this test is only valid because there's no way to
	 * *reattach* to a notअगरier right now. If one is added, we'll need to
	 * keep track of the notअगर itself and make sure they match here.
	 */
	अगर (match->notअगर)
		list_del(&n.list);
out:
	mutex_unlock(&match->notअगरy_lock);

	/* Userspace requests to जारी the syscall. */
	अगर (flags & SECCOMP_USER_NOTIF_FLAG_CONTINUE)
		वापस 0;

	syscall_set_वापस_value(current, current_pt_regs(),
				 err, ret);
	वापस -1;
पूर्ण

अटल पूर्णांक __seccomp_filter(पूर्णांक this_syscall, स्थिर काष्ठा seccomp_data *sd,
			    स्थिर bool recheck_after_trace)
अणु
	u32 filter_ret, action;
	काष्ठा seccomp_filter *match = शून्य;
	पूर्णांक data;
	काष्ठा seccomp_data sd_local;

	/*
	 * Make sure that any changes to mode from another thपढ़ो have
	 * been seen after SYSCALL_WORK_SECCOMP was seen.
	 */
	smp_rmb();

	अगर (!sd) अणु
		populate_seccomp_data(&sd_local);
		sd = &sd_local;
	पूर्ण

	filter_ret = seccomp_run_filters(sd, &match);
	data = filter_ret & SECCOMP_RET_DATA;
	action = filter_ret & SECCOMP_RET_ACTION_FULL;

	चयन (action) अणु
	हाल SECCOMP_RET_ERRNO:
		/* Set low-order bits as an त्रुटि_सं, capped at MAX_ERRNO. */
		अगर (data > MAX_ERRNO)
			data = MAX_ERRNO;
		syscall_set_वापस_value(current, current_pt_regs(),
					 -data, 0);
		जाओ skip;

	हाल SECCOMP_RET_TRAP:
		/* Show the handler the original रेजिस्टरs. */
		syscall_rollback(current, current_pt_regs());
		/* Let the filter pass back 16 bits of data. */
		seccomp_send_sigsys(this_syscall, data);
		जाओ skip;

	हाल SECCOMP_RET_TRACE:
		/* We've been put in this state by the ptracer alपढ़ोy. */
		अगर (recheck_after_trace)
			वापस 0;

		/* ENOSYS these calls अगर there is no tracer attached. */
		अगर (!ptrace_event_enabled(current, PTRACE_EVENT_SECCOMP)) अणु
			syscall_set_वापस_value(current,
						 current_pt_regs(),
						 -ENOSYS, 0);
			जाओ skip;
		पूर्ण

		/* Allow the BPF to provide the event message */
		ptrace_event(PTRACE_EVENT_SECCOMP, data);
		/*
		 * The delivery of a fatal संकेत during event
		 * notअगरication may silently skip tracer notअगरication,
		 * which could leave us with a potentially unmodअगरied
		 * syscall that the tracer would have liked to have
		 * changed. Since the process is about to die, we just
		 * क्रमce the syscall to be skipped and let the संकेत
		 * समाप्त the process and correctly handle any tracer निकास
		 * notअगरications.
		 */
		अगर (fatal_संकेत_pending(current))
			जाओ skip;
		/* Check अगर the tracer क्रमced the syscall to be skipped. */
		this_syscall = syscall_get_nr(current, current_pt_regs());
		अगर (this_syscall < 0)
			जाओ skip;

		/*
		 * Recheck the syscall, since it may have changed. This
		 * पूर्णांकentionally uses a शून्य काष्ठा seccomp_data to क्रमce
		 * a reload of all रेजिस्टरs. This करोes not जाओ skip since
		 * a skip would have alपढ़ोy been reported.
		 */
		अगर (__seccomp_filter(this_syscall, शून्य, true))
			वापस -1;

		वापस 0;

	हाल SECCOMP_RET_USER_NOTIF:
		अगर (seccomp_करो_user_notअगरication(this_syscall, match, sd))
			जाओ skip;

		वापस 0;

	हाल SECCOMP_RET_LOG:
		seccomp_log(this_syscall, 0, action, true);
		वापस 0;

	हाल SECCOMP_RET_ALLOW:
		/*
		 * Note that the "match" filter will always be शून्य क्रम
		 * this action since SECCOMP_RET_ALLOW is the starting
		 * state in seccomp_run_filters().
		 */
		वापस 0;

	हाल SECCOMP_RET_KILL_THREAD:
	हाल SECCOMP_RET_KILL_PROCESS:
	शेष:
		seccomp_log(this_syscall, SIGSYS, action, true);
		/* Dump core only अगर this is the last reमुख्यing thपढ़ो. */
		अगर (action != SECCOMP_RET_KILL_THREAD ||
		    get_nr_thपढ़ोs(current) == 1) अणु
			kernel_siginfo_t info;

			/* Show the original रेजिस्टरs in the dump. */
			syscall_rollback(current, current_pt_regs());
			/* Trigger a manual coredump since करो_निकास skips it. */
			seccomp_init_siginfo(&info, this_syscall, data);
			करो_coredump(&info);
		पूर्ण
		अगर (action == SECCOMP_RET_KILL_THREAD)
			करो_निकास(SIGSYS);
		अन्यथा
			करो_group_निकास(SIGSYS);
	पूर्ण

	unreachable();

skip:
	seccomp_log(this_syscall, 0, action, match ? match->log : false);
	वापस -1;
पूर्ण
#अन्यथा
अटल पूर्णांक __seccomp_filter(पूर्णांक this_syscall, स्थिर काष्ठा seccomp_data *sd,
			    स्थिर bool recheck_after_trace)
अणु
	BUG();

	वापस -1;
पूर्ण
#पूर्ण_अगर

पूर्णांक __secure_computing(स्थिर काष्ठा seccomp_data *sd)
अणु
	पूर्णांक mode = current->seccomp.mode;
	पूर्णांक this_syscall;

	अगर (IS_ENABLED(CONFIG_CHECKPOINT_RESTORE) &&
	    unlikely(current->ptrace & PT_SUSPEND_SECCOMP))
		वापस 0;

	this_syscall = sd ? sd->nr :
		syscall_get_nr(current, current_pt_regs());

	चयन (mode) अणु
	हाल SECCOMP_MODE_STRICT:
		__secure_computing_strict(this_syscall);  /* may call करो_निकास */
		वापस 0;
	हाल SECCOMP_MODE_FILTER:
		वापस __seccomp_filter(this_syscall, sd, false);
	शेष:
		BUG();
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_SECCOMP_FILTER */

दीर्घ prctl_get_seccomp(व्योम)
अणु
	वापस current->seccomp.mode;
पूर्ण

/**
 * seccomp_set_mode_strict: पूर्णांकernal function क्रम setting strict seccomp
 *
 * Once current->seccomp.mode is non-zero, it may not be changed.
 *
 * Returns 0 on success or -EINVAL on failure.
 */
अटल दीर्घ seccomp_set_mode_strict(व्योम)
अणु
	स्थिर अचिन्हित दीर्घ seccomp_mode = SECCOMP_MODE_STRICT;
	दीर्घ ret = -EINVAL;

	spin_lock_irq(&current->sighand->siglock);

	अगर (!seccomp_may_assign_mode(seccomp_mode))
		जाओ out;

#अगर_घोषित TIF_NOTSC
	disable_TSC();
#पूर्ण_अगर
	seccomp_assign_mode(current, seccomp_mode, 0);
	ret = 0;

out:
	spin_unlock_irq(&current->sighand->siglock);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SECCOMP_FILTER
अटल व्योम seccomp_notअगरy_मुक्त(काष्ठा seccomp_filter *filter)
अणु
	kमुक्त(filter->notअगर);
	filter->notअगर = शून्य;
पूर्ण

अटल व्योम seccomp_notअगरy_detach(काष्ठा seccomp_filter *filter)
अणु
	काष्ठा seccomp_knotअगर *knotअगर;

	अगर (!filter)
		वापस;

	mutex_lock(&filter->notअगरy_lock);

	/*
	 * If this file is being बंदd because e.g. the task who owned it
	 * died, let's wake everyone up who was रुकोing on us.
	 */
	list_क्रम_each_entry(knotअगर, &filter->notअगर->notअगरications, list) अणु
		अगर (knotअगर->state == SECCOMP_NOTIFY_REPLIED)
			जारी;

		knotअगर->state = SECCOMP_NOTIFY_REPLIED;
		knotअगर->error = -ENOSYS;
		knotअगर->val = 0;

		/*
		 * We करो not need to wake up any pending addfd messages, as
		 * the notअगरier will करो that क्रम us, as this just looks
		 * like a standard reply.
		 */
		complete(&knotअगर->पढ़ोy);
	पूर्ण

	seccomp_notअगरy_मुक्त(filter);
	mutex_unlock(&filter->notअगरy_lock);
पूर्ण

अटल पूर्णांक seccomp_notअगरy_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seccomp_filter *filter = file->निजी_data;

	seccomp_notअगरy_detach(filter);
	__put_seccomp_filter(filter);
	वापस 0;
पूर्ण

/* must be called with notअगर_lock held */
अटल अंतरभूत काष्ठा seccomp_knotअगर *
find_notअगरication(काष्ठा seccomp_filter *filter, u64 id)
अणु
	काष्ठा seccomp_knotअगर *cur;

	lockdep_निश्चित_held(&filter->notअगरy_lock);

	list_क्रम_each_entry(cur, &filter->notअगर->notअगरications, list) अणु
		अगर (cur->id == id)
			वापस cur;
	पूर्ण

	वापस शून्य;
पूर्ण


अटल दीर्घ seccomp_notअगरy_recv(काष्ठा seccomp_filter *filter,
				व्योम __user *buf)
अणु
	काष्ठा seccomp_knotअगर *knotअगर = शून्य, *cur;
	काष्ठा seccomp_notअगर unotअगर;
	sमाप_प्रकार ret;

	/* Verअगरy that we're not given garbage to keep काष्ठा extensible. */
	ret = check_zeroed_user(buf, माप(unotअगर));
	अगर (ret < 0)
		वापस ret;
	अगर (!ret)
		वापस -EINVAL;

	स_रखो(&unotअगर, 0, माप(unotअगर));

	ret = करोwn_पूर्णांकerruptible(&filter->notअगर->request);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&filter->notअगरy_lock);
	list_क्रम_each_entry(cur, &filter->notअगर->notअगरications, list) अणु
		अगर (cur->state == SECCOMP_NOTIFY_INIT) अणु
			knotअगर = cur;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If we didn't find a notअगरication, it could be that the task was
	 * पूर्णांकerrupted by a fatal संकेत between the समय we were woken and
	 * when we were able to acquire the rw lock.
	 */
	अगर (!knotअगर) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	unotअगर.id = knotअगर->id;
	unotअगर.pid = task_pid_vnr(knotअगर->task);
	unotअगर.data = *(knotअगर->data);

	knotअगर->state = SECCOMP_NOTIFY_SENT;
	wake_up_poll(&filter->wqh, EPOLLOUT | EPOLLWRNORM);
	ret = 0;
out:
	mutex_unlock(&filter->notअगरy_lock);

	अगर (ret == 0 && copy_to_user(buf, &unotअगर, माप(unotअगर))) अणु
		ret = -EFAULT;

		/*
		 * Userspace screwed up. To make sure that we keep this
		 * notअगरication alive, let's reset it back to INIT. It
		 * may have died when we released the lock, so we need to make
		 * sure it's still around.
		 */
		mutex_lock(&filter->notअगरy_lock);
		knotअगर = find_notअगरication(filter, unotअगर.id);
		अगर (knotअगर) अणु
			knotअगर->state = SECCOMP_NOTIFY_INIT;
			up(&filter->notअगर->request);
		पूर्ण
		mutex_unlock(&filter->notअगरy_lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल दीर्घ seccomp_notअगरy_send(काष्ठा seccomp_filter *filter,
				व्योम __user *buf)
अणु
	काष्ठा seccomp_notअगर_resp resp = अणुपूर्ण;
	काष्ठा seccomp_knotअगर *knotअगर;
	दीर्घ ret;

	अगर (copy_from_user(&resp, buf, माप(resp)))
		वापस -EFAULT;

	अगर (resp.flags & ~SECCOMP_USER_NOTIF_FLAG_CONTINUE)
		वापस -EINVAL;

	अगर ((resp.flags & SECCOMP_USER_NOTIF_FLAG_CONTINUE) &&
	    (resp.error || resp.val))
		वापस -EINVAL;

	ret = mutex_lock_पूर्णांकerruptible(&filter->notअगरy_lock);
	अगर (ret < 0)
		वापस ret;

	knotअगर = find_notअगरication(filter, resp.id);
	अगर (!knotअगर) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	/* Allow exactly one reply. */
	अगर (knotअगर->state != SECCOMP_NOTIFY_SENT) अणु
		ret = -EINPROGRESS;
		जाओ out;
	पूर्ण

	ret = 0;
	knotअगर->state = SECCOMP_NOTIFY_REPLIED;
	knotअगर->error = resp.error;
	knotअगर->val = resp.val;
	knotअगर->flags = resp.flags;
	complete(&knotअगर->पढ़ोy);
out:
	mutex_unlock(&filter->notअगरy_lock);
	वापस ret;
पूर्ण

अटल दीर्घ seccomp_notअगरy_id_valid(काष्ठा seccomp_filter *filter,
				    व्योम __user *buf)
अणु
	काष्ठा seccomp_knotअगर *knotअगर;
	u64 id;
	दीर्घ ret;

	अगर (copy_from_user(&id, buf, माप(id)))
		वापस -EFAULT;

	ret = mutex_lock_पूर्णांकerruptible(&filter->notअगरy_lock);
	अगर (ret < 0)
		वापस ret;

	knotअगर = find_notअगरication(filter, id);
	अगर (knotअगर && knotअगर->state == SECCOMP_NOTIFY_SENT)
		ret = 0;
	अन्यथा
		ret = -ENOENT;

	mutex_unlock(&filter->notअगरy_lock);
	वापस ret;
पूर्ण

अटल दीर्घ seccomp_notअगरy_addfd(काष्ठा seccomp_filter *filter,
				 काष्ठा seccomp_notअगर_addfd __user *uaddfd,
				 अचिन्हित पूर्णांक size)
अणु
	काष्ठा seccomp_notअगर_addfd addfd;
	काष्ठा seccomp_knotअगर *knotअगर;
	काष्ठा seccomp_kaddfd kaddfd;
	पूर्णांक ret;

	BUILD_BUG_ON(माप(addfd) < SECCOMP_NOTIFY_ADDFD_SIZE_VER0);
	BUILD_BUG_ON(माप(addfd) != SECCOMP_NOTIFY_ADDFD_SIZE_LATEST);

	अगर (size < SECCOMP_NOTIFY_ADDFD_SIZE_VER0 || size >= PAGE_SIZE)
		वापस -EINVAL;

	ret = copy_काष्ठा_from_user(&addfd, माप(addfd), uaddfd, size);
	अगर (ret)
		वापस ret;

	अगर (addfd.newfd_flags & ~O_CLOEXEC)
		वापस -EINVAL;

	अगर (addfd.flags & ~SECCOMP_ADDFD_FLAG_SETFD)
		वापस -EINVAL;

	अगर (addfd.newfd && !(addfd.flags & SECCOMP_ADDFD_FLAG_SETFD))
		वापस -EINVAL;

	kaddfd.file = fget(addfd.srcfd);
	अगर (!kaddfd.file)
		वापस -EBADF;

	kaddfd.flags = addfd.newfd_flags;
	kaddfd.setfd = addfd.flags & SECCOMP_ADDFD_FLAG_SETFD;
	kaddfd.fd = addfd.newfd;
	init_completion(&kaddfd.completion);

	ret = mutex_lock_पूर्णांकerruptible(&filter->notअगरy_lock);
	अगर (ret < 0)
		जाओ out;

	knotअगर = find_notअगरication(filter, addfd.id);
	अगर (!knotअगर) अणु
		ret = -ENOENT;
		जाओ out_unlock;
	पूर्ण

	/*
	 * We करो not want to allow क्रम FD injection to occur beक्रमe the
	 * notअगरication has been picked up by a userspace handler, or after
	 * the notअगरication has been replied to.
	 */
	अगर (knotअगर->state != SECCOMP_NOTIFY_SENT) अणु
		ret = -EINPROGRESS;
		जाओ out_unlock;
	पूर्ण

	list_add(&kaddfd.list, &knotअगर->addfd);
	complete(&knotअगर->पढ़ोy);
	mutex_unlock(&filter->notअगरy_lock);

	/* Now we रुको क्रम it to be processed or be पूर्णांकerrupted */
	ret = रुको_क्रम_completion_पूर्णांकerruptible(&kaddfd.completion);
	अगर (ret == 0) अणु
		/*
		 * We had a successful completion. The other side has alपढ़ोy
		 * हटाओd us from the addfd queue, and
		 * रुको_क्रम_completion_पूर्णांकerruptible has a memory barrier upon
		 * success that lets us पढ़ो this value directly without
		 * locking.
		 */
		ret = kaddfd.ret;
		जाओ out;
	पूर्ण

	mutex_lock(&filter->notअगरy_lock);
	/*
	 * Even though we were woken up by a संकेत and not a successful
	 * completion, a completion may have happened in the mean समय.
	 *
	 * We need to check again अगर the addfd request has been handled,
	 * and अगर not, we will हटाओ it from the queue.
	 */
	अगर (list_empty(&kaddfd.list))
		ret = kaddfd.ret;
	अन्यथा
		list_del(&kaddfd.list);

out_unlock:
	mutex_unlock(&filter->notअगरy_lock);
out:
	fput(kaddfd.file);

	वापस ret;
पूर्ण

अटल दीर्घ seccomp_notअगरy_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg)
अणु
	काष्ठा seccomp_filter *filter = file->निजी_data;
	व्योम __user *buf = (व्योम __user *)arg;

	/* Fixed-size ioctls */
	चयन (cmd) अणु
	हाल SECCOMP_IOCTL_NOTIF_RECV:
		वापस seccomp_notअगरy_recv(filter, buf);
	हाल SECCOMP_IOCTL_NOTIF_SEND:
		वापस seccomp_notअगरy_send(filter, buf);
	हाल SECCOMP_IOCTL_NOTIF_ID_VALID_WRONG_सूची:
	हाल SECCOMP_IOCTL_NOTIF_ID_VALID:
		वापस seccomp_notअगरy_id_valid(filter, buf);
	पूर्ण

	/* Extensible Argument ioctls */
#घोषणा EA_IOCTL(cmd)	((cmd) & ~(IOC_INOUT | IOCSIZE_MASK))
	चयन (EA_IOCTL(cmd)) अणु
	हाल EA_IOCTL(SECCOMP_IOCTL_NOTIF_ADDFD):
		वापस seccomp_notअगरy_addfd(filter, buf, _IOC_SIZE(cmd));
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल __poll_t seccomp_notअगरy_poll(काष्ठा file *file,
				    काष्ठा poll_table_काष्ठा *poll_tab)
अणु
	काष्ठा seccomp_filter *filter = file->निजी_data;
	__poll_t ret = 0;
	काष्ठा seccomp_knotअगर *cur;

	poll_रुको(file, &filter->wqh, poll_tab);

	अगर (mutex_lock_पूर्णांकerruptible(&filter->notअगरy_lock) < 0)
		वापस EPOLLERR;

	list_क्रम_each_entry(cur, &filter->notअगर->notअगरications, list) अणु
		अगर (cur->state == SECCOMP_NOTIFY_INIT)
			ret |= EPOLLIN | EPOLLRDNORM;
		अगर (cur->state == SECCOMP_NOTIFY_SENT)
			ret |= EPOLLOUT | EPOLLWRNORM;
		अगर ((ret & EPOLLIN) && (ret & EPOLLOUT))
			अवरोध;
	पूर्ण

	mutex_unlock(&filter->notअगरy_lock);

	अगर (refcount_पढ़ो(&filter->users) == 0)
		ret |= EPOLLHUP;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations seccomp_notअगरy_ops = अणु
	.poll = seccomp_notअगरy_poll,
	.release = seccomp_notअगरy_release,
	.unlocked_ioctl = seccomp_notअगरy_ioctl,
	.compat_ioctl = seccomp_notअगरy_ioctl,
पूर्ण;

अटल काष्ठा file *init_listener(काष्ठा seccomp_filter *filter)
अणु
	काष्ठा file *ret;

	ret = ERR_PTR(-ENOMEM);
	filter->notअगर = kzalloc(माप(*(filter->notअगर)), GFP_KERNEL);
	अगर (!filter->notअगर)
		जाओ out;

	sema_init(&filter->notअगर->request, 0);
	filter->notअगर->next_id = get_अक्रमom_u64();
	INIT_LIST_HEAD(&filter->notअगर->notअगरications);

	ret = anon_inode_getfile("seccomp notify", &seccomp_notअगरy_ops,
				 filter, O_RDWR);
	अगर (IS_ERR(ret))
		जाओ out_notअगर;

	/* The file has a reference to it now */
	__get_seccomp_filter(filter);

out_notअगर:
	अगर (IS_ERR(ret))
		seccomp_notअगरy_मुक्त(filter);
out:
	वापस ret;
पूर्ण

/*
 * Does @new_child have a listener जबतक an ancestor also has a listener?
 * If so, we'll want to reject this filter.
 * This only has to be tested क्रम the current process, even in the TSYNC हाल,
 * because TSYNC installs @child with the same parent on all thपढ़ोs.
 * Note that @new_child is not hooked up to its parent at this poपूर्णांक yet, so
 * we use current->seccomp.filter.
 */
अटल bool has_duplicate_listener(काष्ठा seccomp_filter *new_child)
अणु
	काष्ठा seccomp_filter *cur;

	/* must be रक्षित against concurrent TSYNC */
	lockdep_निश्चित_held(&current->sighand->siglock);

	अगर (!new_child->notअगर)
		वापस false;
	क्रम (cur = current->seccomp.filter; cur; cur = cur->prev) अणु
		अगर (cur->notअगर)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * seccomp_set_mode_filter: पूर्णांकernal function क्रम setting seccomp filter
 * @flags:  flags to change filter behavior
 * @filter: काष्ठा sock_fprog containing filter
 *
 * This function may be called repeatedly to install additional filters.
 * Every filter successfully installed will be evaluated (in reverse order)
 * क्रम each प्रणाली call the task makes.
 *
 * Once current->seccomp.mode is non-zero, it may not be changed.
 *
 * Returns 0 on success or -EINVAL on failure.
 */
अटल दीर्घ seccomp_set_mode_filter(अचिन्हित पूर्णांक flags,
				    स्थिर अक्षर __user *filter)
अणु
	स्थिर अचिन्हित दीर्घ seccomp_mode = SECCOMP_MODE_FILTER;
	काष्ठा seccomp_filter *prepared = शून्य;
	दीर्घ ret = -EINVAL;
	पूर्णांक listener = -1;
	काष्ठा file *listener_f = शून्य;

	/* Validate flags. */
	अगर (flags & ~SECCOMP_FILTER_FLAG_MASK)
		वापस -EINVAL;

	/*
	 * In the successful हाल, NEW_LISTENER वापसs the new listener fd.
	 * But in the failure हाल, TSYNC वापसs the thपढ़ो that died. If you
	 * combine these two flags, there's no way to tell whether something
	 * succeeded or failed. So, let's disallow this combination अगर the user
	 * has not explicitly requested no errors from TSYNC.
	 */
	अगर ((flags & SECCOMP_FILTER_FLAG_TSYNC) &&
	    (flags & SECCOMP_FILTER_FLAG_NEW_LISTENER) &&
	    ((flags & SECCOMP_FILTER_FLAG_TSYNC_ESRCH) == 0))
		वापस -EINVAL;

	/* Prepare the new filter beक्रमe holding any locks. */
	prepared = seccomp_prepare_user_filter(filter);
	अगर (IS_ERR(prepared))
		वापस PTR_ERR(prepared);

	अगर (flags & SECCOMP_FILTER_FLAG_NEW_LISTENER) अणु
		listener = get_unused_fd_flags(O_CLOEXEC);
		अगर (listener < 0) अणु
			ret = listener;
			जाओ out_मुक्त;
		पूर्ण

		listener_f = init_listener(prepared);
		अगर (IS_ERR(listener_f)) अणु
			put_unused_fd(listener);
			ret = PTR_ERR(listener_f);
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	/*
	 * Make sure we cannot change seccomp or nnp state via TSYNC
	 * जबतक another thपढ़ो is in the middle of calling exec.
	 */
	अगर (flags & SECCOMP_FILTER_FLAG_TSYNC &&
	    mutex_lock_समाप्तable(&current->संकेत->cred_guard_mutex))
		जाओ out_put_fd;

	spin_lock_irq(&current->sighand->siglock);

	अगर (!seccomp_may_assign_mode(seccomp_mode))
		जाओ out;

	अगर (has_duplicate_listener(prepared)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = seccomp_attach_filter(flags, prepared);
	अगर (ret)
		जाओ out;
	/* Do not मुक्त the successfully attached filter. */
	prepared = शून्य;

	seccomp_assign_mode(current, seccomp_mode, flags);
out:
	spin_unlock_irq(&current->sighand->siglock);
	अगर (flags & SECCOMP_FILTER_FLAG_TSYNC)
		mutex_unlock(&current->संकेत->cred_guard_mutex);
out_put_fd:
	अगर (flags & SECCOMP_FILTER_FLAG_NEW_LISTENER) अणु
		अगर (ret) अणु
			listener_f->निजी_data = शून्य;
			fput(listener_f);
			put_unused_fd(listener);
			seccomp_notअगरy_detach(prepared);
		पूर्ण अन्यथा अणु
			fd_install(listener, listener_f);
			ret = listener;
		पूर्ण
	पूर्ण
out_मुक्त:
	seccomp_filter_मुक्त(prepared);
	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत दीर्घ seccomp_set_mode_filter(अचिन्हित पूर्णांक flags,
					   स्थिर अक्षर __user *filter)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल दीर्घ seccomp_get_action_avail(स्थिर अक्षर __user *uaction)
अणु
	u32 action;

	अगर (copy_from_user(&action, uaction, माप(action)))
		वापस -EFAULT;

	चयन (action) अणु
	हाल SECCOMP_RET_KILL_PROCESS:
	हाल SECCOMP_RET_KILL_THREAD:
	हाल SECCOMP_RET_TRAP:
	हाल SECCOMP_RET_ERRNO:
	हाल SECCOMP_RET_USER_NOTIF:
	हाल SECCOMP_RET_TRACE:
	हाल SECCOMP_RET_LOG:
	हाल SECCOMP_RET_ALLOW:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ seccomp_get_notअगर_sizes(व्योम __user *usizes)
अणु
	काष्ठा seccomp_notअगर_sizes sizes = अणु
		.seccomp_notअगर = माप(काष्ठा seccomp_notअगर),
		.seccomp_notअगर_resp = माप(काष्ठा seccomp_notअगर_resp),
		.seccomp_data = माप(काष्ठा seccomp_data),
	पूर्ण;

	अगर (copy_to_user(usizes, &sizes, माप(sizes)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/* Common entry poपूर्णांक क्रम both prctl and syscall. */
अटल दीर्घ करो_seccomp(अचिन्हित पूर्णांक op, अचिन्हित पूर्णांक flags,
		       व्योम __user *uargs)
अणु
	चयन (op) अणु
	हाल SECCOMP_SET_MODE_STRICT:
		अगर (flags != 0 || uargs != शून्य)
			वापस -EINVAL;
		वापस seccomp_set_mode_strict();
	हाल SECCOMP_SET_MODE_FILTER:
		वापस seccomp_set_mode_filter(flags, uargs);
	हाल SECCOMP_GET_ACTION_AVAIL:
		अगर (flags != 0)
			वापस -EINVAL;

		वापस seccomp_get_action_avail(uargs);
	हाल SECCOMP_GET_NOTIF_SIZES:
		अगर (flags != 0)
			वापस -EINVAL;

		वापस seccomp_get_notअगर_sizes(uargs);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

SYSCALL_DEFINE3(seccomp, अचिन्हित पूर्णांक, op, अचिन्हित पूर्णांक, flags,
			 व्योम __user *, uargs)
अणु
	वापस करो_seccomp(op, flags, uargs);
पूर्ण

/**
 * prctl_set_seccomp: configures current->seccomp.mode
 * @seccomp_mode: requested mode to use
 * @filter: optional काष्ठा sock_fprog क्रम use with SECCOMP_MODE_FILTER
 *
 * Returns 0 on success or -EINVAL on failure.
 */
दीर्घ prctl_set_seccomp(अचिन्हित दीर्घ seccomp_mode, व्योम __user *filter)
अणु
	अचिन्हित पूर्णांक op;
	व्योम __user *uargs;

	चयन (seccomp_mode) अणु
	हाल SECCOMP_MODE_STRICT:
		op = SECCOMP_SET_MODE_STRICT;
		/*
		 * Setting strict mode through prctl always ignored filter,
		 * so make sure it is always शून्य here to pass the पूर्णांकernal
		 * check in करो_seccomp().
		 */
		uargs = शून्य;
		अवरोध;
	हाल SECCOMP_MODE_FILTER:
		op = SECCOMP_SET_MODE_FILTER;
		uargs = filter;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* prctl पूर्णांकerface करोesn't have flags, so they are always zero. */
	वापस करो_seccomp(op, 0, uargs);
पूर्ण

#अगर defined(CONFIG_SECCOMP_FILTER) && defined(CONFIG_CHECKPOINT_RESTORE)
अटल काष्ठा seccomp_filter *get_nth_filter(काष्ठा task_काष्ठा *task,
					     अचिन्हित दीर्घ filter_off)
अणु
	काष्ठा seccomp_filter *orig, *filter;
	अचिन्हित दीर्घ count;

	/*
	 * Note: this is only correct because the caller should be the (ptrace)
	 * tracer of the task, otherwise lock_task_sighand is needed.
	 */
	spin_lock_irq(&task->sighand->siglock);

	अगर (task->seccomp.mode != SECCOMP_MODE_FILTER) अणु
		spin_unlock_irq(&task->sighand->siglock);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	orig = task->seccomp.filter;
	__get_seccomp_filter(orig);
	spin_unlock_irq(&task->sighand->siglock);

	count = 0;
	क्रम (filter = orig; filter; filter = filter->prev)
		count++;

	अगर (filter_off >= count) अणु
		filter = ERR_PTR(-ENOENT);
		जाओ out;
	पूर्ण

	count -= filter_off;
	क्रम (filter = orig; filter && count > 1; filter = filter->prev)
		count--;

	अगर (WARN_ON(count != 1 || !filter)) अणु
		filter = ERR_PTR(-ENOENT);
		जाओ out;
	पूर्ण

	__get_seccomp_filter(filter);

out:
	__put_seccomp_filter(orig);
	वापस filter;
पूर्ण

दीर्घ seccomp_get_filter(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ filter_off,
			व्योम __user *data)
अणु
	काष्ठा seccomp_filter *filter;
	काष्ठा sock_fprog_kern *fprog;
	दीर्घ ret;

	अगर (!capable(CAP_SYS_ADMIN) ||
	    current->seccomp.mode != SECCOMP_MODE_DISABLED) अणु
		वापस -EACCES;
	पूर्ण

	filter = get_nth_filter(task, filter_off);
	अगर (IS_ERR(filter))
		वापस PTR_ERR(filter);

	fprog = filter->prog->orig_prog;
	अगर (!fprog) अणु
		/* This must be a new non-cBPF filter, since we save
		 * every cBPF filter's orig_prog above when
		 * CONFIG_CHECKPOINT_RESTORE is enabled.
		 */
		ret = -EMEDIUMTYPE;
		जाओ out;
	पूर्ण

	ret = fprog->len;
	अगर (!data)
		जाओ out;

	अगर (copy_to_user(data, fprog->filter, bpf_classic_proglen(fprog)))
		ret = -EFAULT;

out:
	__put_seccomp_filter(filter);
	वापस ret;
पूर्ण

दीर्घ seccomp_get_metadata(काष्ठा task_काष्ठा *task,
			  अचिन्हित दीर्घ size, व्योम __user *data)
अणु
	दीर्घ ret;
	काष्ठा seccomp_filter *filter;
	काष्ठा seccomp_metadata kmd = अणुपूर्ण;

	अगर (!capable(CAP_SYS_ADMIN) ||
	    current->seccomp.mode != SECCOMP_MODE_DISABLED) अणु
		वापस -EACCES;
	पूर्ण

	size = min_t(अचिन्हित दीर्घ, size, माप(kmd));

	अगर (size < माप(kmd.filter_off))
		वापस -EINVAL;

	अगर (copy_from_user(&kmd.filter_off, data, माप(kmd.filter_off)))
		वापस -EFAULT;

	filter = get_nth_filter(task, kmd.filter_off);
	अगर (IS_ERR(filter))
		वापस PTR_ERR(filter);

	अगर (filter->log)
		kmd.flags |= SECCOMP_FILTER_FLAG_LOG;

	ret = size;
	अगर (copy_to_user(data, &kmd, size))
		ret = -EFAULT;

	__put_seccomp_filter(filter);
	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYSCTL

/* Human पढ़ोable action names क्रम मित्रly sysctl पूर्णांकeraction */
#घोषणा SECCOMP_RET_KILL_PROCESS_NAME	"kill_process"
#घोषणा SECCOMP_RET_KILL_THREAD_NAME	"kill_thread"
#घोषणा SECCOMP_RET_TRAP_NAME		"trap"
#घोषणा SECCOMP_RET_ERRNO_NAME		"errno"
#घोषणा SECCOMP_RET_USER_NOTIF_NAME	"user_notif"
#घोषणा SECCOMP_RET_TRACE_NAME		"trace"
#घोषणा SECCOMP_RET_LOG_NAME		"log"
#घोषणा SECCOMP_RET_ALLOW_NAME		"allow"

अटल स्थिर अक्षर seccomp_actions_avail[] =
				SECCOMP_RET_KILL_PROCESS_NAME	" "
				SECCOMP_RET_KILL_THREAD_NAME	" "
				SECCOMP_RET_TRAP_NAME		" "
				SECCOMP_RET_ERRNO_NAME		" "
				SECCOMP_RET_USER_NOTIF_NAME     " "
				SECCOMP_RET_TRACE_NAME		" "
				SECCOMP_RET_LOG_NAME		" "
				SECCOMP_RET_ALLOW_NAME;

काष्ठा seccomp_log_name अणु
	u32		log;
	स्थिर अक्षर	*name;
पूर्ण;

अटल स्थिर काष्ठा seccomp_log_name seccomp_log_names[] = अणु
	अणु SECCOMP_LOG_KILL_PROCESS, SECCOMP_RET_KILL_PROCESS_NAME पूर्ण,
	अणु SECCOMP_LOG_KILL_THREAD, SECCOMP_RET_KILL_THREAD_NAME पूर्ण,
	अणु SECCOMP_LOG_TRAP, SECCOMP_RET_TRAP_NAME पूर्ण,
	अणु SECCOMP_LOG_ERRNO, SECCOMP_RET_ERRNO_NAME पूर्ण,
	अणु SECCOMP_LOG_USER_NOTIF, SECCOMP_RET_USER_NOTIF_NAME पूर्ण,
	अणु SECCOMP_LOG_TRACE, SECCOMP_RET_TRACE_NAME पूर्ण,
	अणु SECCOMP_LOG_LOG, SECCOMP_RET_LOG_NAME पूर्ण,
	अणु SECCOMP_LOG_ALLOW, SECCOMP_RET_ALLOW_NAME पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल bool seccomp_names_from_actions_logged(अक्षर *names, माप_प्रकार size,
					      u32 actions_logged,
					      स्थिर अक्षर *sep)
अणु
	स्थिर काष्ठा seccomp_log_name *cur;
	bool append_sep = false;

	क्रम (cur = seccomp_log_names; cur->name && size; cur++) अणु
		sमाप_प्रकार ret;

		अगर (!(actions_logged & cur->log))
			जारी;

		अगर (append_sep) अणु
			ret = strscpy(names, sep, size);
			अगर (ret < 0)
				वापस false;

			names += ret;
			size -= ret;
		पूर्ण अन्यथा
			append_sep = true;

		ret = strscpy(names, cur->name, size);
		अगर (ret < 0)
			वापस false;

		names += ret;
		size -= ret;
	पूर्ण

	वापस true;
पूर्ण

अटल bool seccomp_action_logged_from_name(u32 *action_logged,
					    स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा seccomp_log_name *cur;

	क्रम (cur = seccomp_log_names; cur->name; cur++) अणु
		अगर (!म_भेद(cur->name, name)) अणु
			*action_logged = cur->log;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool seccomp_actions_logged_from_names(u32 *actions_logged, अक्षर *names)
अणु
	अक्षर *name;

	*actions_logged = 0;
	जबतक ((name = strsep(&names, " ")) && *name) अणु
		u32 action_logged = 0;

		अगर (!seccomp_action_logged_from_name(&action_logged, name))
			वापस false;

		*actions_logged |= action_logged;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक पढ़ो_actions_logged(काष्ठा ctl_table *ro_table, व्योम *buffer,
			       माप_प्रकार *lenp, loff_t *ppos)
अणु
	अक्षर names[माप(seccomp_actions_avail)];
	काष्ठा ctl_table table;

	स_रखो(names, 0, माप(names));

	अगर (!seccomp_names_from_actions_logged(names, माप(names),
					       seccomp_actions_logged, " "))
		वापस -EINVAL;

	table = *ro_table;
	table.data = names;
	table.maxlen = माप(names);
	वापस proc_करोstring(&table, 0, buffer, lenp, ppos);
पूर्ण

अटल पूर्णांक ग_लिखो_actions_logged(काष्ठा ctl_table *ro_table, व्योम *buffer,
				माप_प्रकार *lenp, loff_t *ppos, u32 *actions_logged)
अणु
	अक्षर names[माप(seccomp_actions_avail)];
	काष्ठा ctl_table table;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	स_रखो(names, 0, माप(names));

	table = *ro_table;
	table.data = names;
	table.maxlen = माप(names);
	ret = proc_करोstring(&table, 1, buffer, lenp, ppos);
	अगर (ret)
		वापस ret;

	अगर (!seccomp_actions_logged_from_names(actions_logged, table.data))
		वापस -EINVAL;

	अगर (*actions_logged & SECCOMP_LOG_ALLOW)
		वापस -EINVAL;

	seccomp_actions_logged = *actions_logged;
	वापस 0;
पूर्ण

अटल व्योम audit_actions_logged(u32 actions_logged, u32 old_actions_logged,
				 पूर्णांक ret)
अणु
	अक्षर names[माप(seccomp_actions_avail)];
	अक्षर old_names[माप(seccomp_actions_avail)];
	स्थिर अक्षर *new = names;
	स्थिर अक्षर *old = old_names;

	अगर (!audit_enabled)
		वापस;

	स_रखो(names, 0, माप(names));
	स_रखो(old_names, 0, माप(old_names));

	अगर (ret)
		new = "?";
	अन्यथा अगर (!actions_logged)
		new = "(none)";
	अन्यथा अगर (!seccomp_names_from_actions_logged(names, माप(names),
						    actions_logged, ","))
		new = "?";

	अगर (!old_actions_logged)
		old = "(none)";
	अन्यथा अगर (!seccomp_names_from_actions_logged(old_names,
						    माप(old_names),
						    old_actions_logged, ","))
		old = "?";

	वापस audit_seccomp_actions_logged(new, old, !ret);
पूर्ण

अटल पूर्णांक seccomp_actions_logged_handler(काष्ठा ctl_table *ro_table, पूर्णांक ग_लिखो,
					  व्योम *buffer, माप_प्रकार *lenp,
					  loff_t *ppos)
अणु
	पूर्णांक ret;

	अगर (ग_लिखो) अणु
		u32 actions_logged = 0;
		u32 old_actions_logged = seccomp_actions_logged;

		ret = ग_लिखो_actions_logged(ro_table, buffer, lenp, ppos,
					   &actions_logged);
		audit_actions_logged(actions_logged, old_actions_logged, ret);
	पूर्ण अन्यथा
		ret = पढ़ो_actions_logged(ro_table, buffer, lenp, ppos);

	वापस ret;
पूर्ण

अटल काष्ठा ctl_path seccomp_sysctl_path[] = अणु
	अणु .procname = "kernel", पूर्ण,
	अणु .procname = "seccomp", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table seccomp_sysctl_table[] = अणु
	अणु
		.procname	= "actions_avail",
		.data		= (व्योम *) &seccomp_actions_avail,
		.maxlen		= माप(seccomp_actions_avail),
		.mode		= 0444,
		.proc_handler	= proc_करोstring,
	पूर्ण,
	अणु
		.procname	= "actions_logged",
		.mode		= 0644,
		.proc_handler	= seccomp_actions_logged_handler,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init seccomp_sysctl_init(व्योम)
अणु
	काष्ठा ctl_table_header *hdr;

	hdr = रेजिस्टर_sysctl_paths(seccomp_sysctl_path, seccomp_sysctl_table);
	अगर (!hdr)
		pr_warn("sysctl registration failed\n");
	अन्यथा
		kmemleak_not_leak(hdr);

	वापस 0;
पूर्ण

device_initcall(seccomp_sysctl_init)

#पूर्ण_अगर /* CONFIG_SYSCTL */

#अगर_घोषित CONFIG_SECCOMP_CACHE_DEBUG
/* Currently CONFIG_SECCOMP_CACHE_DEBUG implies SECCOMP_ARCH_NATIVE */
अटल व्योम proc_pid_seccomp_cache_arch(काष्ठा seq_file *m, स्थिर अक्षर *name,
					स्थिर व्योम *biपंचांगap, माप_प्रकार biपंचांगap_size)
अणु
	पूर्णांक nr;

	क्रम (nr = 0; nr < biपंचांगap_size; nr++) अणु
		bool cached = test_bit(nr, biपंचांगap);
		अक्षर *status = cached ? "ALLOW" : "FILTER";

		seq_म_लिखो(m, "%s %d %s\n", name, nr, status);
	पूर्ण
पूर्ण

पूर्णांक proc_pid_seccomp_cache(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			   काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा seccomp_filter *f;
	अचिन्हित दीर्घ flags;

	/*
	 * We करोn't want some sandboxed process to know what their seccomp
	 * filters consist of.
	 */
	अगर (!file_ns_capable(m->file, &init_user_ns, CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (!lock_task_sighand(task, &flags))
		वापस -ESRCH;

	f = READ_ONCE(task->seccomp.filter);
	अगर (!f) अणु
		unlock_task_sighand(task, &flags);
		वापस 0;
	पूर्ण

	/* prevent filter from being मुक्तd जबतक we are prपूर्णांकing it */
	__get_seccomp_filter(f);
	unlock_task_sighand(task, &flags);

	proc_pid_seccomp_cache_arch(m, SECCOMP_ARCH_NATIVE_NAME,
				    f->cache.allow_native,
				    SECCOMP_ARCH_NATIVE_NR);

#अगर_घोषित SECCOMP_ARCH_COMPAT
	proc_pid_seccomp_cache_arch(m, SECCOMP_ARCH_COMPAT_NAME,
				    f->cache.allow_compat,
				    SECCOMP_ARCH_COMPAT_NR);
#पूर्ण_अगर /* SECCOMP_ARCH_COMPAT */

	__put_seccomp_filter(f);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SECCOMP_CACHE_DEBUG */
