<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_SECCOMP_H
#घोषणा _UAPI_LINUX_SECCOMP_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>


/* Valid values क्रम seccomp.mode and prctl(PR_SET_SECCOMP, <mode>) */
#घोषणा SECCOMP_MODE_DISABLED	0 /* seccomp is not in use. */
#घोषणा SECCOMP_MODE_STRICT	1 /* uses hard-coded filter. */
#घोषणा SECCOMP_MODE_FILTER	2 /* uses user-supplied filter. */

/* Valid operations क्रम seccomp syscall. */
#घोषणा SECCOMP_SET_MODE_STRICT		0
#घोषणा SECCOMP_SET_MODE_FILTER		1
#घोषणा SECCOMP_GET_ACTION_AVAIL	2
#घोषणा SECCOMP_GET_NOTIF_SIZES		3

/* Valid flags क्रम SECCOMP_SET_MODE_FILTER */
#घोषणा SECCOMP_FILTER_FLAG_TSYNC		(1UL << 0)
#घोषणा SECCOMP_FILTER_FLAG_LOG			(1UL << 1)
#घोषणा SECCOMP_FILTER_FLAG_SPEC_ALLOW		(1UL << 2)
#घोषणा SECCOMP_FILTER_FLAG_NEW_LISTENER	(1UL << 3)
#घोषणा SECCOMP_FILTER_FLAG_TSYNC_ESRCH		(1UL << 4)

/*
 * All BPF programs must वापस a 32-bit value.
 * The bottom 16-bits are क्रम optional वापस data.
 * The upper 16-bits are ordered from least permissive values to most,
 * as a चिन्हित value (so 0x8000000 is negative).
 *
 * The ordering ensures that a min_t() over composed वापस values always
 * selects the least permissive choice.
 */
#घोषणा SECCOMP_RET_KILL_PROCESS 0x80000000U /* समाप्त the process */
#घोषणा SECCOMP_RET_KILL_THREAD	 0x00000000U /* समाप्त the thपढ़ो */
#घोषणा SECCOMP_RET_KILL	 SECCOMP_RET_KILL_THREAD
#घोषणा SECCOMP_RET_TRAP	 0x00030000U /* disallow and क्रमce a SIGSYS */
#घोषणा SECCOMP_RET_ERRNO	 0x00050000U /* वापसs an त्रुटि_सं */
#घोषणा SECCOMP_RET_USER_NOTIF	 0x7fc00000U /* notअगरies userspace */
#घोषणा SECCOMP_RET_TRACE	 0x7ff00000U /* pass to a tracer or disallow */
#घोषणा SECCOMP_RET_LOG		 0x7ffc0000U /* allow after logging */
#घोषणा SECCOMP_RET_ALLOW	 0x7fff0000U /* allow */

/* Masks क्रम the वापस value sections. */
#घोषणा SECCOMP_RET_ACTION_FULL	0xffff0000U
#घोषणा SECCOMP_RET_ACTION	0x7fff0000U
#घोषणा SECCOMP_RET_DATA	0x0000ffffU

/**
 * काष्ठा seccomp_data - the क्रमmat the BPF program executes over.
 * @nr: the प्रणाली call number
 * @arch: indicates प्रणाली call convention as an AUDIT_ARCH_* value
 *        as defined in <linux/audit.h>.
 * @inकाष्ठाion_poपूर्णांकer: at the समय of the प्रणाली call.
 * @args: up to 6 प्रणाली call arguments always stored as 64-bit values
 *        regardless of the architecture.
 */
काष्ठा seccomp_data अणु
	पूर्णांक nr;
	__u32 arch;
	__u64 inकाष्ठाion_poपूर्णांकer;
	__u64 args[6];
पूर्ण;

काष्ठा seccomp_notअगर_sizes अणु
	__u16 seccomp_notअगर;
	__u16 seccomp_notअगर_resp;
	__u16 seccomp_data;
पूर्ण;

काष्ठा seccomp_notअगर अणु
	__u64 id;
	__u32 pid;
	__u32 flags;
	काष्ठा seccomp_data data;
पूर्ण;

/*
 * Valid flags क्रम काष्ठा seccomp_notअगर_resp
 *
 * Note, the SECCOMP_USER_NOTIF_FLAG_CONTINUE flag must be used with caution!
 * If set by the process supervising the syscalls of another process the
 * syscall will जारी. This is problematic because of an inherent TOCTOU.
 * An attacker can exploit the समय जबतक the supervised process is रुकोing on
 * a response from the supervising process to reग_लिखो syscall arguments which
 * are passed as poपूर्णांकers of the पूर्णांकercepted syscall.
 * It should be असलolutely clear that this means that the seccomp notअगरier
 * _cannot_ be used to implement a security policy! It should only ever be used
 * in scenarios where a more privileged process supervises the syscalls of a
 * lesser privileged process to get around kernel-enक्रमced security
 * restrictions when the privileged process deems this safe. In other words,
 * in order to जारी a syscall the supervising process should be sure that
 * another security mechanism or the kernel itself will sufficiently block
 * syscalls अगर arguments are rewritten to something unsafe.
 *
 * Similar precautions should be applied when stacking SECCOMP_RET_USER_NOTIF
 * or SECCOMP_RET_TRACE. For SECCOMP_RET_USER_NOTIF filters acting on the
 * same syscall, the most recently added filter takes precedence. This means
 * that the new SECCOMP_RET_USER_NOTIF filter can override any
 * SECCOMP_IOCTL_NOTIF_SEND from earlier filters, essentially allowing all
 * such filtered syscalls to be executed by sending the response
 * SECCOMP_USER_NOTIF_FLAG_CONTINUE. Note that SECCOMP_RET_TRACE can equally
 * be overriden by SECCOMP_USER_NOTIF_FLAG_CONTINUE.
 */
#घोषणा SECCOMP_USER_NOTIF_FLAG_CONTINUE (1UL << 0)

काष्ठा seccomp_notअगर_resp अणु
	__u64 id;
	__s64 val;
	__s32 error;
	__u32 flags;
पूर्ण;

/* valid flags क्रम seccomp_notअगर_addfd */
#घोषणा SECCOMP_ADDFD_FLAG_SETFD	(1UL << 0) /* Specअगरy remote fd */

/**
 * काष्ठा seccomp_notअगर_addfd
 * @id: The ID of the seccomp notअगरication
 * @flags: SECCOMP_ADDFD_FLAG_*
 * @srcfd: The local fd number
 * @newfd: Optional remote FD number अगर SETFD option is set, otherwise 0.
 * @newfd_flags: The O_* flags the remote FD should have applied
 */
काष्ठा seccomp_notअगर_addfd अणु
	__u64 id;
	__u32 flags;
	__u32 srcfd;
	__u32 newfd;
	__u32 newfd_flags;
पूर्ण;

#घोषणा SECCOMP_IOC_MAGIC		'!'
#घोषणा SECCOMP_IO(nr)			_IO(SECCOMP_IOC_MAGIC, nr)
#घोषणा SECCOMP_IOR(nr, type)		_IOR(SECCOMP_IOC_MAGIC, nr, type)
#घोषणा SECCOMP_IOW(nr, type)		_IOW(SECCOMP_IOC_MAGIC, nr, type)
#घोषणा SECCOMP_IOWR(nr, type)		_IOWR(SECCOMP_IOC_MAGIC, nr, type)

/* Flags क्रम seccomp notअगरication fd ioctl. */
#घोषणा SECCOMP_IOCTL_NOTIF_RECV	SECCOMP_IOWR(0, काष्ठा seccomp_notअगर)
#घोषणा SECCOMP_IOCTL_NOTIF_SEND	SECCOMP_IOWR(1,	\
						काष्ठा seccomp_notअगर_resp)
#घोषणा SECCOMP_IOCTL_NOTIF_ID_VALID	SECCOMP_IOW(2, __u64)
/* On success, the वापस value is the remote process's added fd number */
#घोषणा SECCOMP_IOCTL_NOTIF_ADDFD	SECCOMP_IOW(3, \
						काष्ठा seccomp_notअगर_addfd)

#पूर्ण_अगर /* _UAPI_LINUX_SECCOMP_H */
