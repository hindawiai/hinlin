<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_PRCTL_H
#घोषणा _LINUX_PRCTL_H

#समावेश <linux/types.h>

/* Values to pass as first argument to prctl() */

#घोषणा PR_SET_PDEATHSIG  1  /* Second arg is a संकेत */
#घोषणा PR_GET_PDEATHSIG  2  /* Second arg is a ptr to वापस the संकेत */

/* Get/set current->mm->dumpable */
#घोषणा PR_GET_DUMPABLE   3
#घोषणा PR_SET_DUMPABLE   4

/* Get/set unaligned access control bits (अगर meaningful) */
#घोषणा PR_GET_UNALIGN	  5
#घोषणा PR_SET_UNALIGN	  6
# define PR_UNALIGN_NOPRINT	1	/* silently fix up unaligned user accesses */
# define PR_UNALIGN_SIGBUS	2	/* generate SIGBUS on unaligned user access */

/* Get/set whether or not to drop capabilities on setuid() away from
 * uid 0 (as per security/commoncap.c) */
#घोषणा PR_GET_KEEPCAPS   7
#घोषणा PR_SET_KEEPCAPS   8

/* Get/set भग्नing-poपूर्णांक emulation control bits (अगर meaningful) */
#घोषणा PR_GET_FPEMU  9
#घोषणा PR_SET_FPEMU 10
# define PR_FPEMU_NOPRINT	1	/* silently emulate fp operations accesses */
# define PR_FPEMU_संक_भ_त्रुटि	2	/* करोn't emulate fp operations, send संक_भ_त्रुटि instead */

/* Get/set भग्नing-poपूर्णांक exception mode (अगर meaningful) */
#घोषणा PR_GET_FPEXC	11
#घोषणा PR_SET_FPEXC	12
# define PR_FP_EXC_SW_ENABLE	0x80	/* Use FPEXC क्रम FP exception enables */
# define PR_FP_EXC_DIV		0x010000	/* भग्नing poपूर्णांक भागide by zero */
# define PR_FP_EXC_OVF		0x020000	/* भग्नing poपूर्णांक overflow */
# define PR_FP_EXC_UND		0x040000	/* भग्नing poपूर्णांक underflow */
# define PR_FP_EXC_RES		0x080000	/* भग्नing poपूर्णांक inexact result */
# define PR_FP_EXC_INV		0x100000	/* भग्नing poपूर्णांक invalid operation */
# define PR_FP_EXC_DISABLED	0	/* FP exceptions disabled */
# define PR_FP_EXC_NONRECOV	1	/* async non-recoverable exc. mode */
# define PR_FP_EXC_ASYNC	2	/* async recoverable exception mode */
# define PR_FP_EXC_PRECISE	3	/* precise exception mode */

/* Get/set whether we use statistical process timing or accurate बारtamp
 * based process timing */
#घोषणा PR_GET_TIMING   13
#घोषणा PR_SET_TIMING   14
# define PR_TIMING_STATISTICAL  0       /* Normal, traditional,
                                                   statistical process timing */
# define PR_TIMING_TIMESTAMP    1       /* Accurate बारtamp based
                                                   process timing */

#घोषणा PR_SET_NAME    15		/* Set process name */
#घोषणा PR_GET_NAME    16		/* Get process name */

/* Get/set process endian */
#घोषणा PR_GET_ENDIAN	19
#घोषणा PR_SET_ENDIAN	20
# define PR_ENDIAN_BIG		0
# define PR_ENDIAN_LITTLE	1	/* True little endian mode */
# define PR_ENDIAN_PPC_LITTLE	2	/* "PowerPC" pseuकरो little endian */

/* Get/set process seccomp mode */
#घोषणा PR_GET_SECCOMP	21
#घोषणा PR_SET_SECCOMP	22

/* Get/set the capability bounding set (as per security/commoncap.c) */
#घोषणा PR_CAPBSET_READ 23
#घोषणा PR_CAPBSET_DROP 24

/* Get/set the process' ability to use the बारtamp counter inकाष्ठाion */
#घोषणा PR_GET_TSC 25
#घोषणा PR_SET_TSC 26
# define PR_TSC_ENABLE		1	/* allow the use of the बारtamp counter */
# define PR_TSC_संक_अंश		2	/* throw a संक_अंश instead of पढ़ोing the TSC */

/* Get/set securebits (as per security/commoncap.c) */
#घोषणा PR_GET_SECUREBITS 27
#घोषणा PR_SET_SECUREBITS 28

/*
 * Get/set the समयrslack as used by poll/select/nanosleep
 * A value of 0 means "use default"
 */
#घोषणा PR_SET_TIMERSLACK 29
#घोषणा PR_GET_TIMERSLACK 30

#घोषणा PR_TASK_PERF_EVENTS_DISABLE		31
#घोषणा PR_TASK_PERF_EVENTS_ENABLE		32

/*
 * Set early/late समाप्त mode क्रम hwpoison memory corruption.
 * This influences when the process माला_लो समाप्तed on a memory corruption.
 */
#घोषणा PR_MCE_KILL	33
# define PR_MCE_KILL_CLEAR   0
# define PR_MCE_KILL_SET     1

# define PR_MCE_KILL_LATE    0
# define PR_MCE_KILL_EARLY   1
# define PR_MCE_KILL_DEFAULT 2

#घोषणा PR_MCE_KILL_GET 34

/*
 * Tune up process memory map specअगरics.
 */
#घोषणा PR_SET_MM		35
# define PR_SET_MM_START_CODE		1
# define PR_SET_MM_END_CODE		2
# define PR_SET_MM_START_DATA		3
# define PR_SET_MM_END_DATA		4
# define PR_SET_MM_START_STACK		5
# define PR_SET_MM_START_BRK		6
# define PR_SET_MM_BRK			7
# define PR_SET_MM_ARG_START		8
# define PR_SET_MM_ARG_END		9
# define PR_SET_MM_ENV_START		10
# define PR_SET_MM_ENV_END		11
# define PR_SET_MM_AUXV			12
# define PR_SET_MM_EXE_खाता		13
# define PR_SET_MM_MAP			14
# define PR_SET_MM_MAP_SIZE		15

/*
 * This काष्ठाure provides new memory descriptor
 * map which mostly modअगरies /proc/pid/stat[m]
 * output क्रम a task. This mostly करोne in a
 * sake of checkpoपूर्णांक/restore functionality.
 */
काष्ठा prctl_mm_map अणु
	__u64	start_code;		/* code section bounds */
	__u64	end_code;
	__u64	start_data;		/* data section bounds */
	__u64	end_data;
	__u64	start_brk;		/* heap क्रम brk() syscall */
	__u64	brk;
	__u64	start_stack;		/* stack starts at */
	__u64	arg_start;		/* command line arguments bounds */
	__u64	arg_end;
	__u64	env_start;		/* environment variables bounds */
	__u64	env_end;
	__u64	*auxv;			/* auxiliary vector */
	__u32	auxv_size;		/* vector size */
	__u32	exe_fd;			/* /proc/$pid/exe link file */
पूर्ण;

/*
 * Set specअगरic pid that is allowed to ptrace the current task.
 * A value of 0 mean "no process".
 */
#घोषणा PR_SET_PTRACER 0x59616d61
# define PR_SET_PTRACER_ANY ((अचिन्हित दीर्घ)-1)

#घोषणा PR_SET_CHILD_SUBREAPER	36
#घोषणा PR_GET_CHILD_SUBREAPER	37

/*
 * If no_new_privs is set, then operations that grant new privileges (i.e.
 * execve) will either fail or not grant them.  This affects suid/sgid,
 * file capabilities, and LSMs.
 *
 * Operations that merely manipulate or drop existing privileges (setresuid,
 * capset, etc.) will still work.  Drop those privileges अगर you want them gone.
 *
 * Changing LSM security करोमुख्य is considered a new privilege.  So, क्रम example,
 * asking selinux क्रम a specअगरic new context (e.g. with runcon) will result
 * in execve वापसing -EPERM.
 *
 * See Documentation/userspace-api/no_new_privs.rst क्रम more details.
 */
#घोषणा PR_SET_NO_NEW_PRIVS	38
#घोषणा PR_GET_NO_NEW_PRIVS	39

#घोषणा PR_GET_TID_ADDRESS	40

#घोषणा PR_SET_THP_DISABLE	41
#घोषणा PR_GET_THP_DISABLE	42

/*
 * No दीर्घer implemented, but left here to ensure the numbers stay reserved:
 */
#घोषणा PR_MPX_ENABLE_MANAGEMENT  43
#घोषणा PR_MPX_DISABLE_MANAGEMENT 44

#घोषणा PR_SET_FP_MODE		45
#घोषणा PR_GET_FP_MODE		46
# define PR_FP_MODE_FR		(1 << 0)	/* 64b FP रेजिस्टरs */
# define PR_FP_MODE_FRE		(1 << 1)	/* 32b compatibility */

/* Control the ambient capability set */
#घोषणा PR_CAP_AMBIENT			47
# define PR_CAP_AMBIENT_IS_SET		1
# define PR_CAP_AMBIENT_RAISE		2
# define PR_CAP_AMBIENT_LOWER		3
# define PR_CAP_AMBIENT_CLEAR_ALL	4

/* arm64 Scalable Vector Extension controls */
/* Flag values must be kept in sync with ptrace NT_ARM_SVE पूर्णांकerface */
#घोषणा PR_SVE_SET_VL			50	/* set task vector length */
# define PR_SVE_SET_VL_ONEXEC		(1 << 18) /* defer effect until exec */
#घोषणा PR_SVE_GET_VL			51	/* get task vector length */
/* Bits common to PR_SVE_SET_VL and PR_SVE_GET_VL */
# define PR_SVE_VL_LEN_MASK		0xffff
# define PR_SVE_VL_INHERIT		(1 << 17) /* inherit across exec */

/* Per task speculation control */
#घोषणा PR_GET_SPECULATION_CTRL		52
#घोषणा PR_SET_SPECULATION_CTRL		53
/* Speculation control variants */
# define PR_SPEC_STORE_BYPASS		0
# define PR_SPEC_INसूचीECT_BRANCH	1
/* Return and control values क्रम PR_SET/GET_SPECULATION_CTRL */
# define PR_SPEC_NOT_AFFECTED		0
# define PR_SPEC_PRCTL			(1UL << 0)
# define PR_SPEC_ENABLE			(1UL << 1)
# define PR_SPEC_DISABLE		(1UL << 2)
# define PR_SPEC_FORCE_DISABLE		(1UL << 3)
# define PR_SPEC_DISABLE_NOEXEC		(1UL << 4)

/* Reset arm64 poपूर्णांकer authentication keys */
#घोषणा PR_PAC_RESET_KEYS		54
# define PR_PAC_APIAKEY			(1UL << 0)
# define PR_PAC_APIBKEY			(1UL << 1)
# define PR_PAC_APDAKEY			(1UL << 2)
# define PR_PAC_APDBKEY			(1UL << 3)
# define PR_PAC_APGAKEY			(1UL << 4)

/* Tagged user address controls क्रम arm64 */
#घोषणा PR_SET_TAGGED_ADDR_CTRL		55
#घोषणा PR_GET_TAGGED_ADDR_CTRL		56
# define PR_TAGGED_ADDR_ENABLE		(1UL << 0)
/* MTE tag check fault modes */
# define PR_MTE_TCF_SHIFT		1
# define PR_MTE_TCF_NONE		(0UL << PR_MTE_TCF_SHIFT)
# define PR_MTE_TCF_SYNC		(1UL << PR_MTE_TCF_SHIFT)
# define PR_MTE_TCF_ASYNC		(2UL << PR_MTE_TCF_SHIFT)
# define PR_MTE_TCF_MASK		(3UL << PR_MTE_TCF_SHIFT)
/* MTE tag inclusion mask */
# define PR_MTE_TAG_SHIFT		3
# define PR_MTE_TAG_MASK		(0xffffUL << PR_MTE_TAG_SHIFT)

/* Control reclaim behavior when allocating memory */
#घोषणा PR_SET_IO_FLUSHER		57
#घोषणा PR_GET_IO_FLUSHER		58

/* Dispatch syscalls to a userspace handler */
#घोषणा PR_SET_SYSCALL_USER_DISPATCH	59
# define PR_SYS_DISPATCH_OFF		0
# define PR_SYS_DISPATCH_ON		1
/* The control values क्रम the user space selector when dispatch is enabled */
# define SYSCALL_DISPATCH_FILTER_ALLOW	0
# define SYSCALL_DISPATCH_FILTER_BLOCK	1

/* Set/get enabled arm64 poपूर्णांकer authentication keys */
#घोषणा PR_PAC_SET_ENABLED_KEYS		60
#घोषणा PR_PAC_GET_ENABLED_KEYS		61

#पूर्ण_अगर /* _LINUX_PRCTL_H */
