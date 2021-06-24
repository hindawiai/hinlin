<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_PTRACE_H
#घोषणा _UAPI_LINUX_PTRACE_H
/* ptrace.h */
/* काष्ठाs and defines to help the user use the ptrace प्रणाली call. */

/* has the defines to get at the रेजिस्टरs. */

#समावेश <linux/types.h>

#घोषणा PTRACE_TRACEME		   0
#घोषणा PTRACE_PEEKTEXT		   1
#घोषणा PTRACE_PEEKDATA		   2
#घोषणा PTRACE_PEEKUSR		   3
#घोषणा PTRACE_POKETEXT		   4
#घोषणा PTRACE_POKEDATA		   5
#घोषणा PTRACE_POKEUSR		   6
#घोषणा PTRACE_CONT		   7
#घोषणा PTRACE_KILL		   8
#घोषणा PTRACE_SINGLESTEP	   9

#घोषणा PTRACE_ATTACH		  16
#घोषणा PTRACE_DETACH		  17

#घोषणा PTRACE_SYSCALL		  24

/* 0x4200-0x4300 are reserved क्रम architecture-independent additions.  */
#घोषणा PTRACE_SETOPTIONS	0x4200
#घोषणा PTRACE_GETEVENTMSG	0x4201
#घोषणा PTRACE_GETSIGINFO	0x4202
#घोषणा PTRACE_SETSIGINFO	0x4203

/*
 * Generic ptrace पूर्णांकerface that exports the architecture specअगरic regsets
 * using the corresponding NT_* types (which are also used in the core dump).
 * Please note that the NT_PRSTATUS note type in a core dump contains a full
 * 'struct elf_prstatus'. But the user_regset क्रम NT_PRSTATUS contains just the
 * elf_gregset_t that is the pr_reg field of 'struct elf_prstatus'. For all the
 * other user_regset flavors, the user_regset layout and the ELF core dump note
 * payload are exactly the same layout.
 *
 * This पूर्णांकerface usage is as follows:
 *	काष्ठा iovec iov = अणु buf, lenपूर्ण;
 *
 *	ret = ptrace(PTRACE_GETREGSET/PTRACE_SETREGSET, pid, NT_XXX_TYPE, &iov);
 *
 * On the successful completion, iov.len will be updated by the kernel,
 * specअगरying how much the kernel has written/पढ़ो to/from the user's iov.buf.
 */
#घोषणा PTRACE_GETREGSET	0x4204
#घोषणा PTRACE_SETREGSET	0x4205

#घोषणा PTRACE_SEIZE		0x4206
#घोषणा PTRACE_INTERRUPT	0x4207
#घोषणा PTRACE_LISTEN		0x4208

#घोषणा PTRACE_PEEKSIGINFO	0x4209

काष्ठा ptrace_peeksiginfo_args अणु
	__u64 off;	/* from which siginfo to start */
	__u32 flags;
	__s32 nr;	/* how may siginfos to take */
पूर्ण;

#घोषणा PTRACE_GETSIGMASK	0x420a
#घोषणा PTRACE_SETSIGMASK	0x420b

#घोषणा PTRACE_SECCOMP_GET_FILTER	0x420c
#घोषणा PTRACE_SECCOMP_GET_METADATA	0x420d

काष्ठा seccomp_metadata अणु
	__u64 filter_off;	/* Input: which filter */
	__u64 flags;		/* Output: filter's flags */
पूर्ण;

#घोषणा PTRACE_GET_SYSCALL_INFO		0x420e
#घोषणा PTRACE_SYSCALL_INFO_NONE	0
#घोषणा PTRACE_SYSCALL_INFO_ENTRY	1
#घोषणा PTRACE_SYSCALL_INFO_EXIT	2
#घोषणा PTRACE_SYSCALL_INFO_SECCOMP	3

काष्ठा ptrace_syscall_info अणु
	__u8 op;	/* PTRACE_SYSCALL_INFO_* */
	__u8 pad[3];
	__u32 arch;
	__u64 inकाष्ठाion_poपूर्णांकer;
	__u64 stack_poपूर्णांकer;
	जोड़ अणु
		काष्ठा अणु
			__u64 nr;
			__u64 args[6];
		पूर्ण entry;
		काष्ठा अणु
			__s64 rval;
			__u8 is_error;
		पूर्ण निकास;
		काष्ठा अणु
			__u64 nr;
			__u64 args[6];
			__u32 ret_data;
		पूर्ण seccomp;
	पूर्ण;
पूर्ण;

#घोषणा PTRACE_GET_RSEQ_CONFIGURATION	0x420f

काष्ठा ptrace_rseq_configuration अणु
	__u64 rseq_abi_poपूर्णांकer;
	__u32 rseq_abi_size;
	__u32 signature;
	__u32 flags;
	__u32 pad;
पूर्ण;

/*
 * These values are stored in task->ptrace_message
 * by tracehook_report_syscall_* to describe the current syscall-stop.
 */
#घोषणा PTRACE_EVENTMSG_SYSCALL_ENTRY	1
#घोषणा PTRACE_EVENTMSG_SYSCALL_EXIT	2

/* Read संकेतs from a shared (process wide) queue */
#घोषणा PTRACE_PEEKSIGINFO_SHARED	(1 << 0)

/* Wait extended result codes क्रम the above trace options.  */
#घोषणा PTRACE_EVENT_FORK	1
#घोषणा PTRACE_EVENT_VFORK	2
#घोषणा PTRACE_EVENT_CLONE	3
#घोषणा PTRACE_EVENT_EXEC	4
#घोषणा PTRACE_EVENT_VFORK_DONE	5
#घोषणा PTRACE_EVENT_EXIT	6
#घोषणा PTRACE_EVENT_SECCOMP	7
/* Extended result codes which enabled by means other than options.  */
#घोषणा PTRACE_EVENT_STOP	128

/* Options set using PTRACE_SETOPTIONS or using PTRACE_SEIZE @data param */
#घोषणा PTRACE_O_TRACESYSGOOD	1
#घोषणा PTRACE_O_TRACEFORK	(1 << PTRACE_EVENT_FORK)
#घोषणा PTRACE_O_TRACEVFORK	(1 << PTRACE_EVENT_VFORK)
#घोषणा PTRACE_O_TRACECLONE	(1 << PTRACE_EVENT_CLONE)
#घोषणा PTRACE_O_TRACEEXEC	(1 << PTRACE_EVENT_EXEC)
#घोषणा PTRACE_O_TRACEVFORKDONE	(1 << PTRACE_EVENT_VFORK_DONE)
#घोषणा PTRACE_O_TRACEEXIT	(1 << PTRACE_EVENT_EXIT)
#घोषणा PTRACE_O_TRACESECCOMP	(1 << PTRACE_EVENT_SECCOMP)

/* eventless options */
#घोषणा PTRACE_O_EXITKILL		(1 << 20)
#घोषणा PTRACE_O_SUSPEND_SECCOMP	(1 << 21)

#घोषणा PTRACE_O_MASK		(\
	0x000000ff | PTRACE_O_EXITKILL | PTRACE_O_SUSPEND_SECCOMP)

#समावेश <यंत्र/ptrace.h>


#पूर्ण_अगर /* _UAPI_LINUX_PTRACE_H */
