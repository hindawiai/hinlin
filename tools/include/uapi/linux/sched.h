<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_SCHED_H
#घोषणा _UAPI_LINUX_SCHED_H

#समावेश <linux/types.h>

/*
 * cloning flags:
 */
#घोषणा CSIGNAL		0x000000ff	/* संकेत mask to be sent at निकास */
#घोषणा CLONE_VM	0x00000100	/* set अगर VM shared between processes */
#घोषणा CLONE_FS	0x00000200	/* set अगर fs info shared between processes */
#घोषणा CLONE_खाताS	0x00000400	/* set अगर खोलो files shared between processes */
#घोषणा CLONE_SIGHAND	0x00000800	/* set अगर संकेत handlers and blocked संकेतs shared */
#घोषणा CLONE_PIDFD	0x00001000	/* set अगर a pidfd should be placed in parent */
#घोषणा CLONE_PTRACE	0x00002000	/* set अगर we want to let tracing जारी on the child too */
#घोषणा CLONE_VFORK	0x00004000	/* set अगर the parent wants the child to wake it up on mm_release */
#घोषणा CLONE_PARENT	0x00008000	/* set अगर we want to have the same parent as the cloner */
#घोषणा CLONE_THREAD	0x00010000	/* Same thपढ़ो group? */
#घोषणा CLONE_NEWNS	0x00020000	/* New mount namespace group */
#घोषणा CLONE_SYSVSEM	0x00040000	/* share प्रणाली V SEM_UNDO semantics */
#घोषणा CLONE_SETTLS	0x00080000	/* create a new TLS क्रम the child */
#घोषणा CLONE_PARENT_SETTID	0x00100000	/* set the TID in the parent */
#घोषणा CLONE_CHILD_CLEARTID	0x00200000	/* clear the TID in the child */
#घोषणा CLONE_DETACHED		0x00400000	/* Unused, ignored */
#घोषणा CLONE_UNTRACED		0x00800000	/* set अगर the tracing process can't क्रमce CLONE_PTRACE on this clone */
#घोषणा CLONE_CHILD_SETTID	0x01000000	/* set the TID in the child */
#घोषणा CLONE_NEWCGROUP		0x02000000	/* New cgroup namespace */
#घोषणा CLONE_NEWUTS		0x04000000	/* New utsname namespace */
#घोषणा CLONE_NEWIPC		0x08000000	/* New ipc namespace */
#घोषणा CLONE_NEWUSER		0x10000000	/* New user namespace */
#घोषणा CLONE_NEWPID		0x20000000	/* New pid namespace */
#घोषणा CLONE_NEWNET		0x40000000	/* New network namespace */
#घोषणा CLONE_IO		0x80000000	/* Clone io context */

/* Flags क्रम the clone3() syscall. */
#घोषणा CLONE_CLEAR_SIGHAND 0x100000000ULL /* Clear any संकेत handler and reset to संक_पूर्व. */
#घोषणा CLONE_INTO_CGROUP 0x200000000ULL /* Clone पूर्णांकo a specअगरic cgroup given the right permissions. */

/*
 * cloning flags पूर्णांकersect with CSIGNAL so can be used with unshare and clone3
 * syscalls only:
 */
#घोषणा CLONE_NEWTIME	0x00000080	/* New समय namespace */

#अगर_अघोषित __ASSEMBLY__
/**
 * काष्ठा clone_args - arguments क्रम the clone3 syscall
 * @flags:        Flags क्रम the new process as listed above.
 *                All flags are valid except क्रम CSIGNAL and
 *                CLONE_DETACHED.
 * @pidfd:        If CLONE_PIDFD is set, a pidfd will be
 *                वापसed in this argument.
 * @child_tid:    If CLONE_CHILD_SETTID is set, the TID of the
 *                child process will be वापसed in the child's
 *                memory.
 * @parent_tid:   If CLONE_PARENT_SETTID is set, the TID of
 *                the child process will be वापसed in the
 *                parent's memory.
 * @निकास_संकेत:  The निकास_संकेत the parent process will be
 *                sent when the child निकासs.
 * @stack:        Specअगरy the location of the stack क्रम the
 *                child process.
 *                Note, @stack is expected to poपूर्णांक to the
 *                lowest address. The stack direction will be
 *                determined by the kernel and set up
 *                appropriately based on @stack_size.
 * @stack_size:   The size of the stack क्रम the child process.
 * @tls:          If CLONE_SETTLS is set, the tls descriptor
 *                is set to tls.
 * @set_tid:      Poपूर्णांकer to an array of type *pid_t. The size
 *                of the array is defined using @set_tid_size.
 *                This array is used to select PIDs/TIDs क्रम
 *                newly created processes. The first element in
 *                this defines the PID in the most nested PID
 *                namespace. Each additional element in the array
 *                defines the PID in the parent PID namespace of
 *                the original PID namespace. If the array has
 *                less entries than the number of currently
 *                nested PID namespaces only the PIDs in the
 *                corresponding namespaces are set.
 * @set_tid_size: This defines the size of the array referenced
 *                in @set_tid. This cannot be larger than the
 *                kernel's limit of nested PID namespaces.
 * @cgroup:       If CLONE_INTO_CGROUP is specअगरied set this to
 *                a file descriptor क्रम the cgroup.
 *
 * The काष्ठाure is versioned by size and thus extensible.
 * New काष्ठा members must go at the end of the काष्ठा and
 * must be properly 64bit aligned.
 */
काष्ठा clone_args अणु
	__aligned_u64 flags;
	__aligned_u64 pidfd;
	__aligned_u64 child_tid;
	__aligned_u64 parent_tid;
	__aligned_u64 निकास_संकेत;
	__aligned_u64 stack;
	__aligned_u64 stack_size;
	__aligned_u64 tls;
	__aligned_u64 set_tid;
	__aligned_u64 set_tid_size;
	__aligned_u64 cgroup;
पूर्ण;
#पूर्ण_अगर

#घोषणा CLONE_ARGS_SIZE_VER0 64 /* माप first published काष्ठा */
#घोषणा CLONE_ARGS_SIZE_VER1 80 /* माप second published काष्ठा */
#घोषणा CLONE_ARGS_SIZE_VER2 88 /* माप third published काष्ठा */

/*
 * Scheduling policies
 */
#घोषणा SCHED_NORMAL		0
#घोषणा SCHED_FIFO		1
#घोषणा SCHED_RR		2
#घोषणा SCHED_BATCH		3
/* SCHED_ISO: reserved but not implemented yet */
#घोषणा SCHED_IDLE		5
#घोषणा SCHED_DEADLINE		6

/* Can be ORed in to make sure the process is reverted back to SCHED_NORMAL on विभाजन */
#घोषणा SCHED_RESET_ON_FORK     0x40000000

/*
 * For the sched_अणुset,getपूर्णattr() calls
 */
#घोषणा SCHED_FLAG_RESET_ON_FORK	0x01
#घोषणा SCHED_FLAG_RECLAIM		0x02
#घोषणा SCHED_FLAG_DL_OVERRUN		0x04
#घोषणा SCHED_FLAG_KEEP_POLICY		0x08
#घोषणा SCHED_FLAG_KEEP_PARAMS		0x10
#घोषणा SCHED_FLAG_UTIL_CLAMP_MIN	0x20
#घोषणा SCHED_FLAG_UTIL_CLAMP_MAX	0x40

#घोषणा SCHED_FLAG_KEEP_ALL	(SCHED_FLAG_KEEP_POLICY | \
				 SCHED_FLAG_KEEP_PARAMS)

#घोषणा SCHED_FLAG_UTIL_CLAMP	(SCHED_FLAG_UTIL_CLAMP_MIN | \
				 SCHED_FLAG_UTIL_CLAMP_MAX)

#घोषणा SCHED_FLAG_ALL	(SCHED_FLAG_RESET_ON_FORK	| \
			 SCHED_FLAG_RECLAIM		| \
			 SCHED_FLAG_DL_OVERRUN		| \
			 SCHED_FLAG_KEEP_ALL		| \
			 SCHED_FLAG_UTIL_CLAMP)

#पूर्ण_अगर /* _UAPI_LINUX_SCHED_H */
