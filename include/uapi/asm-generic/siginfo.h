<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_GENERIC_SIGINFO_H
#घोषणा _UAPI_ASM_GENERIC_SIGINFO_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

प्रकार जोड़ sigval अणु
	पूर्णांक sival_पूर्णांक;
	व्योम __user *sival_ptr;
पूर्ण sigval_t;

#घोषणा SI_MAX_SIZE	128

/*
 * The शेष "si_band" type is "long", as specअगरied by POSIX.
 * However, some architectures want to override this to "int"
 * क्रम historical compatibility reasons, so we allow that.
 */
#अगर_अघोषित __ARCH_SI_BAND_T
#घोषणा __ARCH_SI_BAND_T दीर्घ
#पूर्ण_अगर

#अगर_अघोषित __ARCH_SI_CLOCK_T
#घोषणा __ARCH_SI_CLOCK_T __kernel_घड़ी_प्रकार
#पूर्ण_अगर

#अगर_अघोषित __ARCH_SI_ATTRIBUTES
#घोषणा __ARCH_SI_ATTRIBUTES
#पूर्ण_अगर

जोड़ __sअगरields अणु
	/* समाप्त() */
	काष्ठा अणु
		__kernel_pid_t _pid;	/* sender's pid */
		__kernel_uid32_t _uid;	/* sender's uid */
	पूर्ण _समाप्त;

	/* POSIX.1b समयrs */
	काष्ठा अणु
		__kernel_समयr_t _tid;	/* समयr id */
		पूर्णांक _overrun;		/* overrun count */
		sigval_t _sigval;	/* same as below */
		पूर्णांक _sys_निजी;       /* not to be passed to user */
	पूर्ण _समयr;

	/* POSIX.1b संकेतs */
	काष्ठा अणु
		__kernel_pid_t _pid;	/* sender's pid */
		__kernel_uid32_t _uid;	/* sender's uid */
		sigval_t _sigval;
	पूर्ण _rt;

	/* SIGCHLD */
	काष्ठा अणु
		__kernel_pid_t _pid;	/* which child */
		__kernel_uid32_t _uid;	/* sender's uid */
		पूर्णांक _status;		/* निकास code */
		__ARCH_SI_CLOCK_T _uसमय;
		__ARCH_SI_CLOCK_T _sसमय;
	पूर्ण _sigchld;

	/* संक_अवैध, संक_भ_त्रुटि, संक_अंश, SIGBUS, SIGTRAP, SIGEMT */
	काष्ठा अणु
		व्योम __user *_addr; /* faulting insn/memory ref. */
#अगर_घोषित __ia64__
		पूर्णांक _imm;		/* immediate value क्रम "break" */
		अचिन्हित पूर्णांक _flags;	/* see ia64 si_flags */
		अचिन्हित दीर्घ _isr;	/* isr */
#पूर्ण_अगर

#घोषणा __ADDR_BND_PKEY_PAD  (__alignof__(व्योम *) < माप(लघु) ? \
			      माप(लघु) : __alignof__(व्योम *))
		जोड़ अणु
			/* used on alpha and sparc */
			पूर्णांक _trapno;	/* TRAP # which caused the संकेत */
			/*
			 * used when si_code=BUS_MCEERR_AR or
			 * used when si_code=BUS_MCEERR_AO
			 */
			लघु _addr_lsb; /* LSB of the reported address */
			/* used when si_code=SEGV_BNDERR */
			काष्ठा अणु
				अक्षर _dummy_bnd[__ADDR_BND_PKEY_PAD];
				व्योम __user *_lower;
				व्योम __user *_upper;
			पूर्ण _addr_bnd;
			/* used when si_code=SEGV_PKUERR */
			काष्ठा अणु
				अक्षर _dummy_pkey[__ADDR_BND_PKEY_PAD];
				__u32 _pkey;
			पूर्ण _addr_pkey;
			/* used when si_code=TRAP_PERF */
			काष्ठा अणु
				अचिन्हित दीर्घ _data;
				__u32 _type;
			पूर्ण _perf;
		पूर्ण;
	पूर्ण _sigfault;

	/* SIGPOLL */
	काष्ठा अणु
		__ARCH_SI_BAND_T _band;	/* POLL_IN, POLL_OUT, POLL_MSG */
		पूर्णांक _fd;
	पूर्ण _sigpoll;

	/* SIGSYS */
	काष्ठा अणु
		व्योम __user *_call_addr; /* calling user insn */
		पूर्णांक _syscall;	/* triggering प्रणाली call number */
		अचिन्हित पूर्णांक _arch;	/* AUDIT_ARCH_* of syscall */
	पूर्ण _sigsys;
पूर्ण;

#अगर_अघोषित __ARCH_HAS_SWAPPED_SIGINFO
#घोषणा __SIGINFO 			\
काष्ठा अणु				\
	पूर्णांक si_signo;			\
	पूर्णांक si_त्रुटि_सं;			\
	पूर्णांक si_code;			\
	जोड़ __sअगरields _sअगरields;	\
पूर्ण
#अन्यथा
#घोषणा __SIGINFO 			\
काष्ठा अणु				\
	पूर्णांक si_signo;			\
	पूर्णांक si_code;			\
	पूर्णांक si_त्रुटि_सं;			\
	जोड़ __sअगरields _sअगरields;	\
पूर्ण
#पूर्ण_अगर /* __ARCH_HAS_SWAPPED_SIGINFO */

प्रकार काष्ठा siginfo अणु
	जोड़ अणु
		__SIGINFO;
		पूर्णांक _si_pad[SI_MAX_SIZE/माप(पूर्णांक)];
	पूर्ण;
पूर्ण __ARCH_SI_ATTRIBUTES siginfo_t;

/*
 * How these fields are to be accessed.
 */
#घोषणा si_pid		_sअगरields._समाप्त._pid
#घोषणा si_uid		_sअगरields._समाप्त._uid
#घोषणा si_tid		_sअगरields._समयr._tid
#घोषणा si_overrun	_sअगरields._समयr._overrun
#घोषणा si_sys_निजी  _sअगरields._समयr._sys_निजी
#घोषणा si_status	_sअगरields._sigchld._status
#घोषणा si_uसमय	_sअगरields._sigchld._uसमय
#घोषणा si_sसमय	_sअगरields._sigchld._sसमय
#घोषणा si_value	_sअगरields._rt._sigval
#घोषणा si_पूर्णांक		_sअगरields._rt._sigval.sival_पूर्णांक
#घोषणा si_ptr		_sअगरields._rt._sigval.sival_ptr
#घोषणा si_addr		_sअगरields._sigfault._addr
#घोषणा si_trapno	_sअगरields._sigfault._trapno
#घोषणा si_addr_lsb	_sअगरields._sigfault._addr_lsb
#घोषणा si_lower	_sअगरields._sigfault._addr_bnd._lower
#घोषणा si_upper	_sअगरields._sigfault._addr_bnd._upper
#घोषणा si_pkey		_sअगरields._sigfault._addr_pkey._pkey
#घोषणा si_perf_data	_sअगरields._sigfault._perf._data
#घोषणा si_perf_type	_sअगरields._sigfault._perf._type
#घोषणा si_band		_sअगरields._sigpoll._band
#घोषणा si_fd		_sअगरields._sigpoll._fd
#घोषणा si_call_addr	_sअगरields._sigsys._call_addr
#घोषणा si_syscall	_sअगरields._sigsys._syscall
#घोषणा si_arch		_sअगरields._sigsys._arch

/*
 * si_code values
 * Digital reserves positive values क्रम kernel-generated संकेतs.
 */
#घोषणा SI_USER		0		/* sent by समाप्त, sigsend, उठाओ */
#घोषणा SI_KERNEL	0x80		/* sent by the kernel from somewhere */
#घोषणा SI_QUEUE	-1		/* sent by sigqueue */
#घोषणा SI_TIMER	-2		/* sent by समयr expiration */
#घोषणा SI_MESGQ	-3		/* sent by real समय mesq state change */
#घोषणा SI_ASYNCIO	-4		/* sent by AIO completion */
#घोषणा SI_SIGIO	-5		/* sent by queued SIGIO */
#घोषणा SI_TKILL	-6		/* sent by tसमाप्त प्रणाली call */
#घोषणा SI_DETHREAD	-7		/* sent by execve() समाप्तing subsidiary thपढ़ोs */
#घोषणा SI_ASYNCNL	-60		/* sent by glibc async name lookup completion */

#घोषणा SI_FROMUSER(siptr)	((siptr)->si_code <= 0)
#घोषणा SI_FROMKERNEL(siptr)	((siptr)->si_code > 0)

/*
 * संक_अवैध si_codes
 */
#घोषणा ILL_ILLOPC	1	/* illegal opcode */
#घोषणा ILL_ILLOPN	2	/* illegal opeअक्रम */
#घोषणा ILL_ILLADR	3	/* illegal addressing mode */
#घोषणा ILL_ILLTRP	4	/* illegal trap */
#घोषणा ILL_PRVOPC	5	/* privileged opcode */
#घोषणा ILL_PRVREG	6	/* privileged रेजिस्टर */
#घोषणा ILL_COPROC	7	/* coprocessor error */
#घोषणा ILL_BADSTK	8	/* पूर्णांकernal stack error */
#घोषणा ILL_BADIADDR	9	/* unimplemented inकाष्ठाion address */
#घोषणा __ILL_BREAK	10	/* illegal अवरोध */
#घोषणा __ILL_BNDMOD	11	/* bundle-update (modअगरication) in progress */
#घोषणा Nसंक_अवैध		11

/*
 * संक_भ_त्रुटि si_codes
 */
#घोषणा FPE_INTDIV	1	/* पूर्णांकeger भागide by zero */
#घोषणा FPE_INTOVF	2	/* पूर्णांकeger overflow */
#घोषणा FPE_FLTDIV	3	/* भग्नing poपूर्णांक भागide by zero */
#घोषणा FPE_FLTOVF	4	/* भग्नing poपूर्णांक overflow */
#घोषणा FPE_FLTUND	5	/* भग्नing poपूर्णांक underflow */
#घोषणा FPE_FLTRES	6	/* भग्नing poपूर्णांक inexact result */
#घोषणा FPE_FLTINV	7	/* भग्नing poपूर्णांक invalid operation */
#घोषणा FPE_FLTSUB	8	/* subscript out of range */
#घोषणा __FPE_DECOVF	9	/* decimal overflow */
#घोषणा __FPE_DECDIV	10	/* decimal भागision by zero */
#घोषणा __FPE_DECERR	11	/* packed decimal error */
#घोषणा __FPE_INVASC	12	/* invalid ASCII digit */
#घोषणा __FPE_INVDEC	13	/* invalid decimal digit */
#घोषणा FPE_FLTUNK	14	/* undiagnosed भग्नing-poपूर्णांक exception */
#घोषणा FPE_CONDTRAP	15	/* trap on condition */
#घोषणा Nसंक_भ_त्रुटि		15

/*
 * संक_अंश si_codes
 */
#घोषणा SEGV_MAPERR	1	/* address not mapped to object */
#घोषणा SEGV_ACCERR	2	/* invalid permissions क्रम mapped object */
#घोषणा SEGV_BNDERR	3	/* failed address bound checks */
#अगर_घोषित __ia64__
# define __SEGV_PSTKOVF	4	/* paragraph stack overflow */
#अन्यथा
# define SEGV_PKUERR	4	/* failed protection key checks */
#पूर्ण_अगर
#घोषणा SEGV_ACCADI	5	/* ADI not enabled क्रम mapped object */
#घोषणा SEGV_ADIDERR	6	/* Disrupting MCD error */
#घोषणा SEGV_ADIPERR	7	/* Precise MCD exception */
#घोषणा SEGV_MTEAERR	8	/* Asynchronous ARM MTE error */
#घोषणा SEGV_MTESERR	9	/* Synchronous ARM MTE exception */
#घोषणा Nसंक_अंश	9

/*
 * SIGBUS si_codes
 */
#घोषणा BUS_ADRALN	1	/* invalid address alignment */
#घोषणा BUS_ADRERR	2	/* non-existent physical address */
#घोषणा BUS_OBJERR	3	/* object specअगरic hardware error */
/* hardware memory error consumed on a machine check: action required */
#घोषणा BUS_MCEERR_AR	4
/* hardware memory error detected in process but not consumed: action optional*/
#घोषणा BUS_MCEERR_AO	5
#घोषणा NSIGBUS		5

/*
 * SIGTRAP si_codes
 */
#घोषणा TRAP_BRKPT	1	/* process अवरोधpoपूर्णांक */
#घोषणा TRAP_TRACE	2	/* process trace trap */
#घोषणा TRAP_BRANCH     3	/* process taken branch trap */
#घोषणा TRAP_HWBKPT     4	/* hardware अवरोधpoपूर्णांक/watchpoपूर्णांक */
#घोषणा TRAP_UNK	5	/* undiagnosed trap */
#घोषणा TRAP_PERF	6	/* perf event with sigtrap=1 */
#घोषणा NSIGTRAP	6

/*
 * There is an additional set of SIGTRAP si_codes used by ptrace
 * that are of the क्रमm: ((PTRACE_EVENT_XXX << 8) | SIGTRAP)
 */

/*
 * SIGCHLD si_codes
 */
#घोषणा CLD_EXITED	1	/* child has निकासed */
#घोषणा CLD_KILLED	2	/* child was समाप्तed */
#घोषणा CLD_DUMPED	3	/* child terminated abnormally */
#घोषणा CLD_TRAPPED	4	/* traced child has trapped */
#घोषणा CLD_STOPPED	5	/* child has stopped */
#घोषणा CLD_CONTINUED	6	/* stopped child has जारीd */
#घोषणा NSIGCHLD	6

/*
 * SIGPOLL (or any other संकेत without संकेत specअगरic si_codes) si_codes
 */
#घोषणा POLL_IN		1	/* data input available */
#घोषणा POLL_OUT	2	/* output buffers available */
#घोषणा POLL_MSG	3	/* input message available */
#घोषणा POLL_ERR	4	/* i/o error */
#घोषणा POLL_PRI	5	/* high priority input available */
#घोषणा POLL_HUP	6	/* device disconnected */
#घोषणा NSIGPOLL	6

/*
 * SIGSYS si_codes
 */
#घोषणा SYS_SECCOMP	1	/* seccomp triggered */
#घोषणा SYS_USER_DISPATCH 2	/* syscall user dispatch triggered */
#घोषणा NSIGSYS		2

/*
 * SIGEMT si_codes
 */
#घोषणा EMT_TAGOVF	1	/* tag overflow */
#घोषणा NSIGEMT		1

/*
 * sigevent definitions
 * 
 * It seems likely that SIGEV_THREAD will have to be handled from 
 * userspace, libpthपढ़ो transmuting it to SIGEV_SIGNAL, which the
 * thपढ़ो manager then catches and करोes the appropriate nonsense.
 * However, everything is written out here so as to not get lost.
 */
#घोषणा SIGEV_SIGNAL	0	/* notअगरy via संकेत */
#घोषणा SIGEV_NONE	1	/* other notअगरication: meaningless */
#घोषणा SIGEV_THREAD	2	/* deliver via thपढ़ो creation */
#घोषणा SIGEV_THREAD_ID 4	/* deliver to thपढ़ो */

/*
 * This works because the alignment is ok on all current architectures
 * but we leave खोलो this being overridden in the future
 */
#अगर_अघोषित __ARCH_SIGEV_PREAMBLE_SIZE
#घोषणा __ARCH_SIGEV_PREAMBLE_SIZE	(माप(पूर्णांक) * 2 + माप(sigval_t))
#पूर्ण_अगर

#घोषणा SIGEV_MAX_SIZE	64
#घोषणा SIGEV_PAD_SIZE	((SIGEV_MAX_SIZE - __ARCH_SIGEV_PREAMBLE_SIZE) \
		/ माप(पूर्णांक))

प्रकार काष्ठा sigevent अणु
	sigval_t sigev_value;
	पूर्णांक sigev_signo;
	पूर्णांक sigev_notअगरy;
	जोड़ अणु
		पूर्णांक _pad[SIGEV_PAD_SIZE];
		 पूर्णांक _tid;

		काष्ठा अणु
			व्योम (*_function)(sigval_t);
			व्योम *_attribute;	/* really pthपढ़ो_attr_t */
		पूर्ण _sigev_thपढ़ो;
	पूर्ण _sigev_un;
पूर्ण sigevent_t;

#घोषणा sigev_notअगरy_function	_sigev_un._sigev_thपढ़ो._function
#घोषणा sigev_notअगरy_attributes	_sigev_un._sigev_thपढ़ो._attribute
#घोषणा sigev_notअगरy_thपढ़ो_id	 _sigev_un._tid


#पूर्ण_अगर /* _UAPI_ASM_GENERIC_SIGINFO_H */
