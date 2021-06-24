<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_COMPAT_H
#घोषणा _LINUX_COMPAT_H
/*
 * These are the type definitions क्रम the architecture specअगरic
 * syscall compatibility layer.
 */

#समावेश <linux/types.h>
#समावेश <linux/समय.स>

#समावेश <linux/स्थिति.स>
#समावेश <linux/param.h>	/* क्रम HZ */
#समावेश <linux/sem.h>
#समावेश <linux/socket.h>
#समावेश <linux/अगर.h>
#समावेश <linux/fs.h>
#समावेश <linux/aio_abi.h>	/* क्रम aio_context_t */
#समावेश <linux/uaccess.h>
#समावेश <linux/unistd.h>

#समावेश <यंत्र/compat.h>

#अगर_घोषित CONFIG_COMPAT
#समावेश <यंत्र/siginfo.h>
#समावेश <यंत्र/संकेत.स>
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_HAS_SYSCALL_WRAPPER
/*
 * It may be useful क्रम an architecture to override the definitions of the
 * COMPAT_SYSCALL_DEFINE0 and COMPAT_SYSCALL_DEFINEx() macros, in particular
 * to use a dअगरferent calling convention क्रम syscalls. To allow क्रम that,
 + the prototypes क्रम the compat_sys_*() functions below will *not* be included
 * अगर CONFIG_ARCH_HAS_SYSCALL_WRAPPER is enabled.
 */
#समावेश <यंत्र/syscall_wrapper.h>
#पूर्ण_अगर /* CONFIG_ARCH_HAS_SYSCALL_WRAPPER */

#अगर_अघोषित COMPAT_USE_64BIT_TIME
#घोषणा COMPAT_USE_64BIT_TIME 0
#पूर्ण_अगर

#अगर_अघोषित __SC_DELOUSE
#घोषणा __SC_DELOUSE(t,v) ((__क्रमce t)(अचिन्हित दीर्घ)(v))
#पूर्ण_अगर

#अगर_अघोषित COMPAT_SYSCALL_DEFINE0
#घोषणा COMPAT_SYSCALL_DEFINE0(name) \
	यंत्रlinkage दीर्घ compat_sys_##name(व्योम); \
	ALLOW_ERROR_INJECTION(compat_sys_##name, ERRNO); \
	यंत्रlinkage दीर्घ compat_sys_##name(व्योम)
#पूर्ण_अगर /* COMPAT_SYSCALL_DEFINE0 */

#घोषणा COMPAT_SYSCALL_DEFINE1(name, ...) \
        COMPAT_SYSCALL_DEFINEx(1, _##name, __VA_ARGS__)
#घोषणा COMPAT_SYSCALL_DEFINE2(name, ...) \
	COMPAT_SYSCALL_DEFINEx(2, _##name, __VA_ARGS__)
#घोषणा COMPAT_SYSCALL_DEFINE3(name, ...) \
	COMPAT_SYSCALL_DEFINEx(3, _##name, __VA_ARGS__)
#घोषणा COMPAT_SYSCALL_DEFINE4(name, ...) \
	COMPAT_SYSCALL_DEFINEx(4, _##name, __VA_ARGS__)
#घोषणा COMPAT_SYSCALL_DEFINE5(name, ...) \
	COMPAT_SYSCALL_DEFINEx(5, _##name, __VA_ARGS__)
#घोषणा COMPAT_SYSCALL_DEFINE6(name, ...) \
	COMPAT_SYSCALL_DEFINEx(6, _##name, __VA_ARGS__)

/*
 * The यंत्रlinkage stub is aliased to a function named __se_compat_sys_*() which
 * sign-extends 32-bit पूर्णांकs to दीर्घs whenever needed. The actual work is
 * करोne within __करो_compat_sys_*().
 */
#अगर_अघोषित COMPAT_SYSCALL_DEFINEx
#घोषणा COMPAT_SYSCALL_DEFINEx(x, name, ...)					\
	__diag_push();								\
	__diag_ignore(GCC, 8, "-Wattribute-alias",				\
		      "Type aliasing is used to sanitize syscall arguments");\
	यंत्रlinkage दीर्घ compat_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__))	\
		__attribute__((alias(__stringअगरy(__se_compat_sys##name))));	\
	ALLOW_ERROR_INJECTION(compat_sys##name, ERRNO);				\
	अटल अंतरभूत दीर्घ __करो_compat_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__));\
	यंत्रlinkage दीर्घ __se_compat_sys##name(__MAP(x,__SC_LONG,__VA_ARGS__));	\
	यंत्रlinkage दीर्घ __se_compat_sys##name(__MAP(x,__SC_LONG,__VA_ARGS__))	\
	अणु									\
		दीर्घ ret = __करो_compat_sys##name(__MAP(x,__SC_DELOUSE,__VA_ARGS__));\
		__MAP(x,__SC_TEST,__VA_ARGS__);					\
		वापस ret;							\
	पूर्ण									\
	__diag_pop();								\
	अटल अंतरभूत दीर्घ __करो_compat_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__))
#पूर्ण_अगर /* COMPAT_SYSCALL_DEFINEx */

काष्ठा compat_iovec अणु
	compat_uptr_t	iov_base;
	compat_माप_प्रकार	iov_len;
पूर्ण;

#अगर_घोषित CONFIG_COMPAT

#अगर_अघोषित compat_user_stack_poपूर्णांकer
#घोषणा compat_user_stack_poपूर्णांकer() current_user_stack_poपूर्णांकer()
#पूर्ण_अगर
#अगर_अघोषित compat_sigaltstack	/* we'll need that क्रम MIPS */
प्रकार काष्ठा compat_sigaltstack अणु
	compat_uptr_t			ss_sp;
	पूर्णांक				ss_flags;
	compat_माप_प्रकार			ss_size;
पूर्ण compat_stack_t;
#पूर्ण_अगर
#अगर_अघोषित COMPAT_MINSIGSTKSZ
#घोषणा COMPAT_MINSIGSTKSZ	MINSIGSTKSZ
#पूर्ण_अगर

#घोषणा compat_jअगरfies_to_घड़ी_प्रकार(x)	\
		(((अचिन्हित दीर्घ)(x) * COMPAT_USER_HZ) / HZ)

प्रकार __compat_uid32_t	compat_uid_t;
प्रकार __compat_gid32_t	compat_gid_t;

काष्ठा compat_sel_arg_काष्ठा;
काष्ठा rusage;

काष्ठा old_iसमयrval32;

काष्ठा compat_पंचांगs अणु
	compat_घड़ी_प्रकार		पंचांगs_uसमय;
	compat_घड़ी_प्रकार		पंचांगs_sसमय;
	compat_घड़ी_प्रकार		पंचांगs_cuसमय;
	compat_घड़ी_प्रकार		पंचांगs_csसमय;
पूर्ण;

#घोषणा _COMPAT_NSIG_WORDS	(_COMPAT_NSIG / _COMPAT_NSIG_BPW)

प्रकार काष्ठा अणु
	compat_sigset_word	sig[_COMPAT_NSIG_WORDS];
पूर्ण compat_sigset_t;

पूर्णांक set_compat_user_sigmask(स्थिर compat_sigset_t __user *umask,
			    माप_प्रकार sigsetsize);

काष्ठा compat_sigaction अणु
#अगर_अघोषित __ARCH_HAS_IRIX_SIGACTION
	compat_uptr_t			sa_handler;
	compat_uदीर्घ_t			sa_flags;
#अन्यथा
	compat_uपूर्णांक_t			sa_flags;
	compat_uptr_t			sa_handler;
#पूर्ण_अगर
#अगर_घोषित __ARCH_HAS_SA_RESTORER
	compat_uptr_t			sa_restorer;
#पूर्ण_अगर
	compat_sigset_t			sa_mask __packed;
पूर्ण;

प्रकार जोड़ compat_sigval अणु
	compat_पूर्णांक_t	sival_पूर्णांक;
	compat_uptr_t	sival_ptr;
पूर्ण compat_sigval_t;

प्रकार काष्ठा compat_siginfo अणु
	पूर्णांक si_signo;
#अगर_अघोषित __ARCH_HAS_SWAPPED_SIGINFO
	पूर्णांक si_त्रुटि_सं;
	पूर्णांक si_code;
#अन्यथा
	पूर्णांक si_code;
	पूर्णांक si_त्रुटि_सं;
#पूर्ण_अगर

	जोड़ अणु
		पूर्णांक _pad[128/माप(पूर्णांक) - 3];

		/* समाप्त() */
		काष्ठा अणु
			compat_pid_t _pid;	/* sender's pid */
			__compat_uid32_t _uid;	/* sender's uid */
		पूर्ण _समाप्त;

		/* POSIX.1b समयrs */
		काष्ठा अणु
			compat_समयr_t _tid;	/* समयr id */
			पूर्णांक _overrun;		/* overrun count */
			compat_sigval_t _sigval;	/* same as below */
		पूर्ण _समयr;

		/* POSIX.1b संकेतs */
		काष्ठा अणु
			compat_pid_t _pid;	/* sender's pid */
			__compat_uid32_t _uid;	/* sender's uid */
			compat_sigval_t _sigval;
		पूर्ण _rt;

		/* SIGCHLD */
		काष्ठा अणु
			compat_pid_t _pid;	/* which child */
			__compat_uid32_t _uid;	/* sender's uid */
			पूर्णांक _status;		/* निकास code */
			compat_घड़ी_प्रकार _uसमय;
			compat_घड़ी_प्रकार _sसमय;
		पूर्ण _sigchld;

#अगर_घोषित CONFIG_X86_X32_ABI
		/* SIGCHLD (x32 version) */
		काष्ठा अणु
			compat_pid_t _pid;	/* which child */
			__compat_uid32_t _uid;	/* sender's uid */
			पूर्णांक _status;		/* निकास code */
			compat_s64 _uसमय;
			compat_s64 _sसमय;
		पूर्ण _sigchld_x32;
#पूर्ण_अगर

		/* संक_अवैध, संक_भ_त्रुटि, संक_अंश, SIGBUS, SIGTRAP, SIGEMT */
		काष्ठा अणु
			compat_uptr_t _addr;	/* faulting insn/memory ref. */
#घोषणा __COMPAT_ADDR_BND_PKEY_PAD  (__alignof__(compat_uptr_t) < माप(लघु) ? \
				     माप(लघु) : __alignof__(compat_uptr_t))
			जोड़ अणु
				/* used on alpha and sparc */
				पूर्णांक _trapno;	/* TRAP # which caused the संकेत */
				/*
				 * used when si_code=BUS_MCEERR_AR or
				 * used when si_code=BUS_MCEERR_AO
				 */
				लघु पूर्णांक _addr_lsb;	/* Valid LSB of the reported address. */
				/* used when si_code=SEGV_BNDERR */
				काष्ठा अणु
					अक्षर _dummy_bnd[__COMPAT_ADDR_BND_PKEY_PAD];
					compat_uptr_t _lower;
					compat_uptr_t _upper;
				पूर्ण _addr_bnd;
				/* used when si_code=SEGV_PKUERR */
				काष्ठा अणु
					अक्षर _dummy_pkey[__COMPAT_ADDR_BND_PKEY_PAD];
					u32 _pkey;
				पूर्ण _addr_pkey;
				/* used when si_code=TRAP_PERF */
				काष्ठा अणु
					compat_uदीर्घ_t _data;
					u32 _type;
				पूर्ण _perf;
			पूर्ण;
		पूर्ण _sigfault;

		/* SIGPOLL */
		काष्ठा अणु
			compat_दीर्घ_t _band;	/* POLL_IN, POLL_OUT, POLL_MSG */
			पूर्णांक _fd;
		पूर्ण _sigpoll;

		काष्ठा अणु
			compat_uptr_t _call_addr; /* calling user insn */
			पूर्णांक _syscall;	/* triggering प्रणाली call number */
			अचिन्हित पूर्णांक _arch;	/* AUDIT_ARCH_* of syscall */
		पूर्ण _sigsys;
	पूर्ण _sअगरields;
पूर्ण compat_siginfo_t;

काष्ठा compat_rlimit अणु
	compat_uदीर्घ_t	rlim_cur;
	compat_uदीर्घ_t	rlim_max;
पूर्ण;

काष्ठा compat_rusage अणु
	काष्ठा old_समयval32 ru_uसमय;
	काष्ठा old_समयval32 ru_sसमय;
	compat_दीर्घ_t	ru_maxrss;
	compat_दीर्घ_t	ru_ixrss;
	compat_दीर्घ_t	ru_idrss;
	compat_दीर्घ_t	ru_isrss;
	compat_दीर्घ_t	ru_minflt;
	compat_दीर्घ_t	ru_majflt;
	compat_दीर्घ_t	ru_nswap;
	compat_दीर्घ_t	ru_inblock;
	compat_दीर्घ_t	ru_oublock;
	compat_दीर्घ_t	ru_msgsnd;
	compat_दीर्घ_t	ru_msgrcv;
	compat_दीर्घ_t	ru_nसंकेतs;
	compat_दीर्घ_t	ru_nvcsw;
	compat_दीर्घ_t	ru_nivcsw;
पूर्ण;

बाह्य पूर्णांक put_compat_rusage(स्थिर काष्ठा rusage *,
			     काष्ठा compat_rusage __user *);

काष्ठा compat_siginfo;
काष्ठा __compat_aio_sigset;

काष्ठा compat_dirent अणु
	u32		d_ino;
	compat_off_t	d_off;
	u16		d_reclen;
	अक्षर		d_name[256];
पूर्ण;

काष्ठा compat_ustat अणु
	compat_daddr_t		f_tमुक्त;
	compat_ino_t		f_tinode;
	अक्षर			f_fname[6];
	अक्षर			f_fpack[6];
पूर्ण;

#घोषणा COMPAT_SIGEV_PAD_SIZE	((SIGEV_MAX_SIZE/माप(पूर्णांक)) - 3)

प्रकार काष्ठा compat_sigevent अणु
	compat_sigval_t sigev_value;
	compat_पूर्णांक_t sigev_signo;
	compat_पूर्णांक_t sigev_notअगरy;
	जोड़ अणु
		compat_पूर्णांक_t _pad[COMPAT_SIGEV_PAD_SIZE];
		compat_पूर्णांक_t _tid;

		काष्ठा अणु
			compat_uptr_t _function;
			compat_uptr_t _attribute;
		पूर्ण _sigev_thपढ़ो;
	पूर्ण _sigev_un;
पूर्ण compat_sigevent_t;

काष्ठा compat_अगरmap अणु
	compat_uदीर्घ_t mem_start;
	compat_uदीर्घ_t mem_end;
	अचिन्हित लघु base_addr;
	अचिन्हित अक्षर irq;
	अचिन्हित अक्षर dma;
	अचिन्हित अक्षर port;
पूर्ण;

काष्ठा compat_अगर_settings अणु
	अचिन्हित पूर्णांक type;	/* Type of physical device or protocol */
	अचिन्हित पूर्णांक size;	/* Size of the data allocated by the caller */
	compat_uptr_t अगरs_अगरsu;	/* जोड़ of poपूर्णांकers */
पूर्ण;

काष्ठा compat_अगरreq अणु
	जोड़ अणु
		अक्षर	अगरrn_name[IFNAMSIZ];    /* अगर name, e.g. "en0" */
	पूर्ण अगरr_अगरrn;
	जोड़ अणु
		काष्ठा	sockaddr अगरru_addr;
		काष्ठा	sockaddr अगरru_dstaddr;
		काष्ठा	sockaddr अगरru_broadaddr;
		काष्ठा	sockaddr अगरru_neपंचांगask;
		काष्ठा	sockaddr अगरru_hwaddr;
		लघु	अगरru_flags;
		compat_पूर्णांक_t	अगरru_ivalue;
		compat_पूर्णांक_t	अगरru_mtu;
		काष्ठा	compat_अगरmap अगरru_map;
		अक्षर	अगरru_slave[IFNAMSIZ];   /* Just fits the size */
		अक्षर	अगरru_newname[IFNAMSIZ];
		compat_caddr_t	अगरru_data;
		काष्ठा	compat_अगर_settings अगरru_settings;
	पूर्ण अगरr_अगरru;
पूर्ण;

काष्ठा compat_अगरconf अणु
	compat_पूर्णांक_t	अगरc_len;                /* size of buffer */
	compat_caddr_t  अगरcbuf;
पूर्ण;

काष्ठा compat_robust_list अणु
	compat_uptr_t			next;
पूर्ण;

काष्ठा compat_robust_list_head अणु
	काष्ठा compat_robust_list	list;
	compat_दीर्घ_t			futex_offset;
	compat_uptr_t			list_op_pending;
पूर्ण;

#अगर_घोषित CONFIG_COMPAT_OLD_SIGACTION
काष्ठा compat_old_sigaction अणु
	compat_uptr_t			sa_handler;
	compat_old_sigset_t		sa_mask;
	compat_uदीर्घ_t			sa_flags;
	compat_uptr_t			sa_restorer;
पूर्ण;
#पूर्ण_अगर

काष्ठा compat_keyctl_kdf_params अणु
	compat_uptr_t hashname;
	compat_uptr_t otherinfo;
	__u32 otherinfolen;
	__u32 __spare[8];
पूर्ण;

काष्ठा compat_statfs;
काष्ठा compat_statfs64;
काष्ठा compat_old_linux_dirent;
काष्ठा compat_linux_dirent;
काष्ठा linux_dirent64;
काष्ठा compat_msghdr;
काष्ठा compat_mmsghdr;
काष्ठा compat_sysinfo;
काष्ठा compat_sysctl_args;
काष्ठा compat_kexec_segment;
काष्ठा compat_mq_attr;
काष्ठा compat_msgbuf;

#घोषणा BITS_PER_COMPAT_LONG    (8*माप(compat_दीर्घ_t))

#घोषणा BITS_TO_COMPAT_LONGS(bits) DIV_ROUND_UP(bits, BITS_PER_COMPAT_LONG)

दीर्घ compat_get_biपंचांगap(अचिन्हित दीर्घ *mask, स्थिर compat_uदीर्घ_t __user *umask,
		       अचिन्हित दीर्घ biपंचांगap_size);
दीर्घ compat_put_biपंचांगap(compat_uदीर्घ_t __user *umask, अचिन्हित दीर्घ *mask,
		       अचिन्हित दीर्घ biपंचांगap_size);
व्योम copy_siginfo_to_बाह्यal32(काष्ठा compat_siginfo *to,
		स्थिर काष्ठा kernel_siginfo *from);
पूर्णांक copy_siginfo_from_user32(kernel_siginfo_t *to,
		स्थिर काष्ठा compat_siginfo __user *from);
पूर्णांक __copy_siginfo_to_user32(काष्ठा compat_siginfo __user *to,
		स्थिर kernel_siginfo_t *from);
#अगर_अघोषित copy_siginfo_to_user32
#घोषणा copy_siginfo_to_user32 __copy_siginfo_to_user32
#पूर्ण_अगर
पूर्णांक get_compat_sigevent(काष्ठा sigevent *event,
		स्थिर काष्ठा compat_sigevent __user *u_event);

बाह्य पूर्णांक get_compat_sigset(sigset_t *set, स्थिर compat_sigset_t __user *compat);

/*
 * Defined अंतरभूत such that size can be compile समय स्थिरant, which aव्योमs
 * CONFIG_HARDENED_USERCOPY complaining about copies from task_काष्ठा
 */
अटल अंतरभूत पूर्णांक
put_compat_sigset(compat_sigset_t __user *compat, स्थिर sigset_t *set,
		  अचिन्हित पूर्णांक size)
अणु
	/* size <= माप(compat_sigset_t) <= माप(sigset_t) */
#अगर_घोषित __BIG_ENDIAN
	compat_sigset_t v;
	चयन (_NSIG_WORDS) अणु
	हाल 4: v.sig[7] = (set->sig[3] >> 32); v.sig[6] = set->sig[3];
		fallthrough;
	हाल 3: v.sig[5] = (set->sig[2] >> 32); v.sig[4] = set->sig[2];
		fallthrough;
	हाल 2: v.sig[3] = (set->sig[1] >> 32); v.sig[2] = set->sig[1];
		fallthrough;
	हाल 1: v.sig[1] = (set->sig[0] >> 32); v.sig[0] = set->sig[0];
	पूर्ण
	वापस copy_to_user(compat, &v, size) ? -EFAULT : 0;
#अन्यथा
	वापस copy_to_user(compat, set, size) ? -EFAULT : 0;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#घोषणा unsafe_put_compat_sigset(compat, set, label) करो अणु		\
	compat_sigset_t __user *__c = compat;				\
	स्थिर sigset_t *__s = set;					\
									\
	चयन (_NSIG_WORDS) अणु						\
	हाल 4:								\
		unsafe_put_user(__s->sig[3] >> 32, &__c->sig[7], label);	\
		unsafe_put_user(__s->sig[3], &__c->sig[6], label);	\
		fallthrough;						\
	हाल 3:								\
		unsafe_put_user(__s->sig[2] >> 32, &__c->sig[5], label);	\
		unsafe_put_user(__s->sig[2], &__c->sig[4], label);	\
		fallthrough;						\
	हाल 2:								\
		unsafe_put_user(__s->sig[1] >> 32, &__c->sig[3], label);	\
		unsafe_put_user(__s->sig[1], &__c->sig[2], label);	\
		fallthrough;						\
	हाल 1:								\
		unsafe_put_user(__s->sig[0] >> 32, &__c->sig[1], label);	\
		unsafe_put_user(__s->sig[0], &__c->sig[0], label);	\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा unsafe_get_compat_sigset(set, compat, label) करो अणु		\
	स्थिर compat_sigset_t __user *__c = compat;			\
	compat_sigset_word hi, lo;					\
	sigset_t *__s = set;						\
									\
	चयन (_NSIG_WORDS) अणु						\
	हाल 4:								\
		unsafe_get_user(lo, &__c->sig[7], label);		\
		unsafe_get_user(hi, &__c->sig[6], label);		\
		__s->sig[3] = hi | (((दीर्घ)lo) << 32);			\
		fallthrough;						\
	हाल 3:								\
		unsafe_get_user(lo, &__c->sig[5], label);		\
		unsafe_get_user(hi, &__c->sig[4], label);		\
		__s->sig[2] = hi | (((दीर्घ)lo) << 32);			\
		fallthrough;						\
	हाल 2:								\
		unsafe_get_user(lo, &__c->sig[3], label);		\
		unsafe_get_user(hi, &__c->sig[2], label);		\
		__s->sig[1] = hi | (((दीर्घ)lo) << 32);			\
		fallthrough;						\
	हाल 1:								\
		unsafe_get_user(lo, &__c->sig[1], label);		\
		unsafe_get_user(hi, &__c->sig[0], label);		\
		__s->sig[0] = hi | (((दीर्घ)lo) << 32);			\
	पूर्ण								\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा unsafe_put_compat_sigset(compat, set, label) करो अणु		\
	compat_sigset_t __user *__c = compat;				\
	स्थिर sigset_t *__s = set;					\
									\
	unsafe_copy_to_user(__c, __s, माप(*__c), label);		\
पूर्ण जबतक (0)

#घोषणा unsafe_get_compat_sigset(set, compat, label) करो अणु		\
	स्थिर compat_sigset_t __user *__c = compat;			\
	sigset_t *__s = set;						\
									\
	unsafe_copy_from_user(__s, __c, माप(*__c), label);		\
पूर्ण जबतक (0)
#पूर्ण_अगर

बाह्य पूर्णांक compat_ptrace_request(काष्ठा task_काष्ठा *child,
				 compat_दीर्घ_t request,
				 compat_uदीर्घ_t addr, compat_uदीर्घ_t data);

बाह्य दीर्घ compat_arch_ptrace(काष्ठा task_काष्ठा *child, compat_दीर्घ_t request,
			       compat_uदीर्घ_t addr, compat_uदीर्घ_t data);

काष्ठा epoll_event;	/* क्रमtunately, this one is fixed-layout */

बाह्य व्योम __user *compat_alloc_user_space(अचिन्हित दीर्घ len);

पूर्णांक compat_restore_altstack(स्थिर compat_stack_t __user *uss);
पूर्णांक __compat_save_altstack(compat_stack_t __user *, अचिन्हित दीर्घ);
#घोषणा unsafe_compat_save_altstack(uss, sp, label) करो अणु \
	compat_stack_t __user *__uss = uss; \
	काष्ठा task_काष्ठा *t = current; \
	unsafe_put_user(ptr_to_compat((व्योम __user *)t->sas_ss_sp), \
			&__uss->ss_sp, label); \
	unsafe_put_user(t->sas_ss_flags, &__uss->ss_flags, label); \
	unsafe_put_user(t->sas_ss_size, &__uss->ss_size, label); \
	अगर (t->sas_ss_flags & SS_AUTODISARM) \
		sas_ss_reset(t); \
पूर्ण जबतक (0);

/*
 * These syscall function prototypes are kept in the same order as
 * include/uapi/यंत्र-generic/unistd.h. Deprecated or obsolete प्रणाली calls
 * go below.
 *
 * Please note that these prototypes here are only provided क्रम inक्रमmation
 * purposes, क्रम अटल analysis, and क्रम linking from the syscall table.
 * These functions should not be called अन्यथाwhere from kernel code.
 *
 * As the syscall calling convention may be dअगरferent from the शेष
 * क्रम architectures overriding the syscall calling convention, करो not
 * include the prototypes अगर CONFIG_ARCH_HAS_SYSCALL_WRAPPER is enabled.
 */
#अगर_अघोषित CONFIG_ARCH_HAS_SYSCALL_WRAPPER
यंत्रlinkage दीर्घ compat_sys_io_setup(अचिन्हित nr_reqs, u32 __user *ctx32p);
यंत्रlinkage दीर्घ compat_sys_io_submit(compat_aio_context_t ctx_id, पूर्णांक nr,
				     u32 __user *iocb);
यंत्रlinkage दीर्घ compat_sys_io_pgetevents(compat_aio_context_t ctx_id,
					compat_दीर्घ_t min_nr,
					compat_दीर्घ_t nr,
					काष्ठा io_event __user *events,
					काष्ठा old_बारpec32 __user *समयout,
					स्थिर काष्ठा __compat_aio_sigset __user *usig);
यंत्रlinkage दीर्घ compat_sys_io_pgetevents_समय64(compat_aio_context_t ctx_id,
					compat_दीर्घ_t min_nr,
					compat_दीर्घ_t nr,
					काष्ठा io_event __user *events,
					काष्ठा __kernel_बारpec __user *समयout,
					स्थिर काष्ठा __compat_aio_sigset __user *usig);

/* fs/cookies.c */
यंत्रlinkage दीर्घ compat_sys_lookup_dcookie(u32, u32, अक्षर __user *, compat_माप_प्रकार);

/* fs/eventpoll.c */
यंत्रlinkage दीर्घ compat_sys_epoll_pरुको(पूर्णांक epfd,
			काष्ठा epoll_event __user *events,
			पूर्णांक maxevents, पूर्णांक समयout,
			स्थिर compat_sigset_t __user *sigmask,
			compat_माप_प्रकार sigsetsize);
यंत्रlinkage दीर्घ compat_sys_epoll_pरुको2(पूर्णांक epfd,
			काष्ठा epoll_event __user *events,
			पूर्णांक maxevents,
			स्थिर काष्ठा __kernel_बारpec __user *समयout,
			स्थिर compat_sigset_t __user *sigmask,
			compat_माप_प्रकार sigsetsize);

/* fs/fcntl.c */
यंत्रlinkage दीर्घ compat_sys_fcntl(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक cmd,
				 compat_uदीर्घ_t arg);
यंत्रlinkage दीर्घ compat_sys_fcntl64(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक cmd,
				   compat_uदीर्घ_t arg);

/* fs/ioctl.c */
यंत्रlinkage दीर्घ compat_sys_ioctl(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक cmd,
				 compat_uदीर्घ_t arg);

/* fs/खोलो.c */
यंत्रlinkage दीर्घ compat_sys_statfs(स्थिर अक्षर __user *pathname,
				  काष्ठा compat_statfs __user *buf);
यंत्रlinkage दीर्घ compat_sys_statfs64(स्थिर अक्षर __user *pathname,
				    compat_माप_प्रकार sz,
				    काष्ठा compat_statfs64 __user *buf);
यंत्रlinkage दीर्घ compat_sys_ख_स्थितिfs(अचिन्हित पूर्णांक fd,
				   काष्ठा compat_statfs __user *buf);
यंत्रlinkage दीर्घ compat_sys_ख_स्थितिfs64(अचिन्हित पूर्णांक fd, compat_माप_प्रकार sz,
				     काष्ठा compat_statfs64 __user *buf);
यंत्रlinkage दीर्घ compat_sys_truncate(स्थिर अक्षर __user *, compat_off_t);
यंत्रlinkage दीर्घ compat_sys_ftruncate(अचिन्हित पूर्णांक, compat_uदीर्घ_t);
/* No generic prototype क्रम truncate64, ftruncate64, fallocate */
यंत्रlinkage दीर्घ compat_sys_खोलोat(पूर्णांक dfd, स्थिर अक्षर __user *filename,
				  पूर्णांक flags, umode_t mode);

/* fs/सूची_पढ़ो.c */
यंत्रlinkage दीर्घ compat_sys_getdents(अचिन्हित पूर्णांक fd,
				    काष्ठा compat_linux_dirent __user *dirent,
				    अचिन्हित पूर्णांक count);

/* fs/पढ़ो_ग_लिखो.c */
यंत्रlinkage दीर्घ compat_sys_lseek(अचिन्हित पूर्णांक, compat_off_t, अचिन्हित पूर्णांक);
/* No generic prototype क्रम pपढ़ो64 and pग_लिखो64 */
यंत्रlinkage sमाप_प्रकार compat_sys_pपढ़ोv(compat_uदीर्घ_t fd,
		स्थिर काष्ठा iovec __user *vec,
		compat_uदीर्घ_t vlen, u32 pos_low, u32 pos_high);
यंत्रlinkage sमाप_प्रकार compat_sys_pग_लिखोv(compat_uदीर्घ_t fd,
		स्थिर काष्ठा iovec __user *vec,
		compat_uदीर्घ_t vlen, u32 pos_low, u32 pos_high);
#अगर_घोषित __ARCH_WANT_COMPAT_SYS_PREADV64
यंत्रlinkage दीर्घ compat_sys_pपढ़ोv64(अचिन्हित दीर्घ fd,
		स्थिर काष्ठा iovec __user *vec,
		अचिन्हित दीर्घ vlen, loff_t pos);
#पूर्ण_अगर

#अगर_घोषित __ARCH_WANT_COMPAT_SYS_PWRITEV64
यंत्रlinkage दीर्घ compat_sys_pग_लिखोv64(अचिन्हित दीर्घ fd,
		स्थिर काष्ठा iovec __user *vec,
		अचिन्हित दीर्घ vlen, loff_t pos);
#पूर्ण_अगर

/* fs/sendfile.c */
यंत्रlinkage दीर्घ compat_sys_sendfile(पूर्णांक out_fd, पूर्णांक in_fd,
				    compat_off_t __user *offset, compat_माप_प्रकार count);
यंत्रlinkage दीर्घ compat_sys_sendfile64(पूर्णांक out_fd, पूर्णांक in_fd,
				    compat_loff_t __user *offset, compat_माप_प्रकार count);

/* fs/select.c */
यंत्रlinkage दीर्घ compat_sys_pselect6_समय32(पूर्णांक n, compat_uदीर्घ_t __user *inp,
				    compat_uदीर्घ_t __user *outp,
				    compat_uदीर्घ_t __user *exp,
				    काष्ठा old_बारpec32 __user *tsp,
				    व्योम __user *sig);
यंत्रlinkage दीर्घ compat_sys_pselect6_समय64(पूर्णांक n, compat_uदीर्घ_t __user *inp,
				    compat_uदीर्घ_t __user *outp,
				    compat_uदीर्घ_t __user *exp,
				    काष्ठा __kernel_बारpec __user *tsp,
				    व्योम __user *sig);
यंत्रlinkage दीर्घ compat_sys_ppoll_समय32(काष्ठा pollfd __user *ufds,
				 अचिन्हित पूर्णांक nfds,
				 काष्ठा old_बारpec32 __user *tsp,
				 स्थिर compat_sigset_t __user *sigmask,
				 compat_माप_प्रकार sigsetsize);
यंत्रlinkage दीर्घ compat_sys_ppoll_समय64(काष्ठा pollfd __user *ufds,
				 अचिन्हित पूर्णांक nfds,
				 काष्ठा __kernel_बारpec __user *tsp,
				 स्थिर compat_sigset_t __user *sigmask,
				 compat_माप_प्रकार sigsetsize);

/* fs/संकेतfd.c */
यंत्रlinkage दीर्घ compat_sys_संकेतfd4(पूर्णांक ufd,
				     स्थिर compat_sigset_t __user *sigmask,
				     compat_माप_प्रकार sigsetsize, पूर्णांक flags);

/* fs/stat.c */
यंत्रlinkage दीर्घ compat_sys_newख_स्थितिat(अचिन्हित पूर्णांक dfd,
				      स्थिर अक्षर __user *filename,
				      काष्ठा compat_stat __user *statbuf,
				      पूर्णांक flag);
यंत्रlinkage दीर्घ compat_sys_newख_स्थिति(अचिन्हित पूर्णांक fd,
				    काष्ठा compat_stat __user *statbuf);

/* fs/sync.c: No generic prototype क्रम sync_file_range and sync_file_range2 */

/* kernel/निकास.c */
यंत्रlinkage दीर्घ compat_sys_रुकोid(पूर्णांक, compat_pid_t,
		काष्ठा compat_siginfo __user *, पूर्णांक,
		काष्ठा compat_rusage __user *);



/* kernel/futex.c */
यंत्रlinkage दीर्घ
compat_sys_set_robust_list(काष्ठा compat_robust_list_head __user *head,
			   compat_माप_प्रकार len);
यंत्रlinkage दीर्घ
compat_sys_get_robust_list(पूर्णांक pid, compat_uptr_t __user *head_ptr,
			   compat_माप_प्रकार __user *len_ptr);

/* kernel/iसमयr.c */
यंत्रlinkage दीर्घ compat_sys_getiसमयr(पूर्णांक which,
				     काष्ठा old_iसमयrval32 __user *it);
यंत्रlinkage दीर्घ compat_sys_setiसमयr(पूर्णांक which,
				     काष्ठा old_iसमयrval32 __user *in,
				     काष्ठा old_iसमयrval32 __user *out);

/* kernel/kexec.c */
यंत्रlinkage दीर्घ compat_sys_kexec_load(compat_uदीर्घ_t entry,
				      compat_uदीर्घ_t nr_segments,
				      काष्ठा compat_kexec_segment __user *,
				      compat_uदीर्घ_t flags);

/* kernel/posix-समयrs.c */
यंत्रlinkage दीर्घ compat_sys_समयr_create(घड़ीid_t which_घड़ी,
			काष्ठा compat_sigevent __user *समयr_event_spec,
			समयr_t __user *created_समयr_id);

/* kernel/ptrace.c */
यंत्रlinkage दीर्घ compat_sys_ptrace(compat_दीर्घ_t request, compat_दीर्घ_t pid,
				  compat_दीर्घ_t addr, compat_दीर्घ_t data);

/* kernel/sched/core.c */
यंत्रlinkage दीर्घ compat_sys_sched_setaffinity(compat_pid_t pid,
				     अचिन्हित पूर्णांक len,
				     compat_uदीर्घ_t __user *user_mask_ptr);
यंत्रlinkage दीर्घ compat_sys_sched_getaffinity(compat_pid_t pid,
				     अचिन्हित पूर्णांक len,
				     compat_uदीर्घ_t __user *user_mask_ptr);

/* kernel/संकेत.c */
यंत्रlinkage दीर्घ compat_sys_sigaltstack(स्थिर compat_stack_t __user *uss_ptr,
				       compat_stack_t __user *uoss_ptr);
यंत्रlinkage दीर्घ compat_sys_rt_संक_रोको(compat_sigset_t __user *unewset,
					 compat_माप_प्रकार sigsetsize);
#अगर_अघोषित CONFIG_ODD_RT_SIGACTION
यंत्रlinkage दीर्घ compat_sys_rt_sigaction(पूर्णांक,
				 स्थिर काष्ठा compat_sigaction __user *,
				 काष्ठा compat_sigaction __user *,
				 compat_माप_प्रकार);
#पूर्ण_अगर
यंत्रlinkage दीर्घ compat_sys_rt_sigprocmask(पूर्णांक how, compat_sigset_t __user *set,
					  compat_sigset_t __user *oset,
					  compat_माप_प्रकार sigsetsize);
यंत्रlinkage दीर्घ compat_sys_rt_संक_बाकी(compat_sigset_t __user *uset,
					 compat_माप_प्रकार sigsetsize);
यंत्रlinkage दीर्घ compat_sys_rt_sigसमयdरुको_समय32(compat_sigset_t __user *uthese,
		काष्ठा compat_siginfo __user *uinfo,
		काष्ठा old_बारpec32 __user *uts, compat_माप_प्रकार sigsetsize);
यंत्रlinkage दीर्घ compat_sys_rt_sigसमयdरुको_समय64(compat_sigset_t __user *uthese,
		काष्ठा compat_siginfo __user *uinfo,
		काष्ठा __kernel_बारpec __user *uts, compat_माप_प्रकार sigsetsize);
यंत्रlinkage दीर्घ compat_sys_rt_sigqueueinfo(compat_pid_t pid, पूर्णांक sig,
				काष्ठा compat_siginfo __user *uinfo);
/* No generic prototype क्रम rt_sigवापस */

/* kernel/sys.c */
यंत्रlinkage दीर्घ compat_sys_बार(काष्ठा compat_पंचांगs __user *tbuf);
यंत्रlinkage दीर्घ compat_sys_getrlimit(अचिन्हित पूर्णांक resource,
				     काष्ठा compat_rlimit __user *rlim);
यंत्रlinkage दीर्घ compat_sys_setrlimit(अचिन्हित पूर्णांक resource,
				     काष्ठा compat_rlimit __user *rlim);
यंत्रlinkage दीर्घ compat_sys_getrusage(पूर्णांक who, काष्ठा compat_rusage __user *ru);

/* kernel/समय.c */
यंत्रlinkage दीर्घ compat_sys_समय_लोofday(काष्ठा old_समयval32 __user *tv,
		काष्ठा समयzone __user *tz);
यंत्रlinkage दीर्घ compat_sys_समय_रखोofday(काष्ठा old_समयval32 __user *tv,
		काष्ठा समयzone __user *tz);

/* kernel/समयr.c */
यंत्रlinkage दीर्घ compat_sys_sysinfo(काष्ठा compat_sysinfo __user *info);

/* ipc/mqueue.c */
यंत्रlinkage दीर्घ compat_sys_mq_खोलो(स्थिर अक्षर __user *u_name,
			पूर्णांक oflag, compat_mode_t mode,
			काष्ठा compat_mq_attr __user *u_attr);
यंत्रlinkage दीर्घ compat_sys_mq_notअगरy(mqd_t mqdes,
			स्थिर काष्ठा compat_sigevent __user *u_notअगरication);
यंत्रlinkage दीर्घ compat_sys_mq_माला_लोetattr(mqd_t mqdes,
			स्थिर काष्ठा compat_mq_attr __user *u_mqstat,
			काष्ठा compat_mq_attr __user *u_omqstat);

/* ipc/msg.c */
यंत्रlinkage दीर्घ compat_sys_msgctl(पूर्णांक first, पूर्णांक second, व्योम __user *uptr);
यंत्रlinkage दीर्घ compat_sys_msgrcv(पूर्णांक msqid, compat_uptr_t msgp,
		compat_sमाप_प्रकार msgsz, compat_दीर्घ_t msgtyp, पूर्णांक msgflg);
यंत्रlinkage दीर्घ compat_sys_msgsnd(पूर्णांक msqid, compat_uptr_t msgp,
		compat_sमाप_प्रकार msgsz, पूर्णांक msgflg);

/* ipc/sem.c */
यंत्रlinkage दीर्घ compat_sys_semctl(पूर्णांक semid, पूर्णांक semnum, पूर्णांक cmd, पूर्णांक arg);

/* ipc/shm.c */
यंत्रlinkage दीर्घ compat_sys_shmctl(पूर्णांक first, पूर्णांक second, व्योम __user *uptr);
यंत्रlinkage दीर्घ compat_sys_shmat(पूर्णांक shmid, compat_uptr_t shmaddr, पूर्णांक shmflg);

/* net/socket.c */
यंत्रlinkage दीर्घ compat_sys_recvfrom(पूर्णांक fd, व्योम __user *buf, compat_माप_प्रकार len,
			    अचिन्हित flags, काष्ठा sockaddr __user *addr,
			    पूर्णांक __user *addrlen);
यंत्रlinkage दीर्घ compat_sys_sendmsg(पूर्णांक fd, काष्ठा compat_msghdr __user *msg,
				   अचिन्हित flags);
यंत्रlinkage दीर्घ compat_sys_recvmsg(पूर्णांक fd, काष्ठा compat_msghdr __user *msg,
				   अचिन्हित पूर्णांक flags);

/* mm/filemap.c: No generic prototype क्रम पढ़ोahead */

/* security/keys/keyctl.c */
यंत्रlinkage दीर्घ compat_sys_keyctl(u32 option,
			      u32 arg2, u32 arg3, u32 arg4, u32 arg5);

/* arch/example/kernel/sys_example.c */
यंत्रlinkage दीर्घ compat_sys_execve(स्थिर अक्षर __user *filename, स्थिर compat_uptr_t __user *argv,
		     स्थिर compat_uptr_t __user *envp);

/* mm/fadvise.c: No generic prototype क्रम fadvise64_64 */

/* mm/, CONFIG_MMU only */
यंत्रlinkage दीर्घ compat_sys_mbind(compat_uदीर्घ_t start, compat_uदीर्घ_t len,
				 compat_uदीर्घ_t mode,
				 compat_uदीर्घ_t __user *nmask,
				 compat_uदीर्घ_t maxnode, compat_uदीर्घ_t flags);
यंत्रlinkage दीर्घ compat_sys_get_mempolicy(पूर्णांक __user *policy,
					 compat_uदीर्घ_t __user *nmask,
					 compat_uदीर्घ_t maxnode,
					 compat_uदीर्घ_t addr,
					 compat_uदीर्घ_t flags);
यंत्रlinkage दीर्घ compat_sys_set_mempolicy(पूर्णांक mode, compat_uदीर्घ_t __user *nmask,
					 compat_uदीर्घ_t maxnode);
यंत्रlinkage दीर्घ compat_sys_migrate_pages(compat_pid_t pid,
		compat_uदीर्घ_t maxnode, स्थिर compat_uदीर्घ_t __user *old_nodes,
		स्थिर compat_uदीर्घ_t __user *new_nodes);
यंत्रlinkage दीर्घ compat_sys_move_pages(pid_t pid, compat_uदीर्घ_t nr_pages,
				      __u32 __user *pages,
				      स्थिर पूर्णांक __user *nodes,
				      पूर्णांक __user *status,
				      पूर्णांक flags);

यंत्रlinkage दीर्घ compat_sys_rt_tgsigqueueinfo(compat_pid_t tgid,
					compat_pid_t pid, पूर्णांक sig,
					काष्ठा compat_siginfo __user *uinfo);
यंत्रlinkage दीर्घ compat_sys_recvmmsg_समय64(पूर्णांक fd, काष्ठा compat_mmsghdr __user *mmsg,
				    अचिन्हित vlen, अचिन्हित पूर्णांक flags,
				    काष्ठा __kernel_बारpec __user *समयout);
यंत्रlinkage दीर्घ compat_sys_recvmmsg_समय32(पूर्णांक fd, काष्ठा compat_mmsghdr __user *mmsg,
				    अचिन्हित vlen, अचिन्हित पूर्णांक flags,
				    काष्ठा old_बारpec32 __user *समयout);
यंत्रlinkage दीर्घ compat_sys_रुको4(compat_pid_t pid,
				 compat_uपूर्णांक_t __user *stat_addr, पूर्णांक options,
				 काष्ठा compat_rusage __user *ru);
यंत्रlinkage दीर्घ compat_sys_fanotअगरy_mark(पूर्णांक, अचिन्हित पूर्णांक, __u32, __u32,
					    पूर्णांक, स्थिर अक्षर __user *);
यंत्रlinkage दीर्घ compat_sys_खोलो_by_handle_at(पूर्णांक mountdirfd,
					     काष्ठा file_handle __user *handle,
					     पूर्णांक flags);
यंत्रlinkage दीर्घ compat_sys_sendmmsg(पूर्णांक fd, काष्ठा compat_mmsghdr __user *mmsg,
				    अचिन्हित vlen, अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ compat_sys_execveat(पूर्णांक dfd, स्थिर अक्षर __user *filename,
		     स्थिर compat_uptr_t __user *argv,
		     स्थिर compat_uptr_t __user *envp, पूर्णांक flags);
यंत्रlinkage sमाप_प्रकार compat_sys_pपढ़ोv2(compat_uदीर्घ_t fd,
		स्थिर काष्ठा iovec __user *vec,
		compat_uदीर्घ_t vlen, u32 pos_low, u32 pos_high, rwf_t flags);
यंत्रlinkage sमाप_प्रकार compat_sys_pग_लिखोv2(compat_uदीर्घ_t fd,
		स्थिर काष्ठा iovec __user *vec,
		compat_uदीर्घ_t vlen, u32 pos_low, u32 pos_high, rwf_t flags);
#अगर_घोषित __ARCH_WANT_COMPAT_SYS_PREADV64V2
यंत्रlinkage दीर्घ  compat_sys_pपढ़ोv64v2(अचिन्हित दीर्घ fd,
		स्थिर काष्ठा iovec __user *vec,
		अचिन्हित दीर्घ vlen, loff_t pos, rwf_t flags);
#पूर्ण_अगर

#अगर_घोषित __ARCH_WANT_COMPAT_SYS_PWRITEV64V2
यंत्रlinkage दीर्घ compat_sys_pग_लिखोv64v2(अचिन्हित दीर्घ fd,
		स्थिर काष्ठा iovec __user *vec,
		अचिन्हित दीर्घ vlen, loff_t pos, rwf_t flags);
#पूर्ण_अगर


/*
 * Deprecated प्रणाली calls which are still defined in
 * include/uapi/यंत्र-generic/unistd.h and wanted by >= 1 arch
 */

/* __ARCH_WANT_SYSCALL_NO_AT */
यंत्रlinkage दीर्घ compat_sys_खोलो(स्थिर अक्षर __user *filename, पूर्णांक flags,
				umode_t mode);

/* __ARCH_WANT_SYSCALL_NO_FLAGS */
यंत्रlinkage दीर्घ compat_sys_संकेतfd(पूर्णांक ufd,
				    स्थिर compat_sigset_t __user *sigmask,
				    compat_माप_प्रकार sigsetsize);

/* __ARCH_WANT_SYSCALL_OFF_T */
यंत्रlinkage दीर्घ compat_sys_newstat(स्थिर अक्षर __user *filename,
				   काष्ठा compat_stat __user *statbuf);
यंत्रlinkage दीर्घ compat_sys_newlstat(स्थिर अक्षर __user *filename,
				    काष्ठा compat_stat __user *statbuf);

/* __ARCH_WANT_SYSCALL_DEPRECATED */
यंत्रlinkage दीर्घ compat_sys_select(पूर्णांक n, compat_uदीर्घ_t __user *inp,
		compat_uदीर्घ_t __user *outp, compat_uदीर्घ_t __user *exp,
		काष्ठा old_समयval32 __user *tvp);
यंत्रlinkage दीर्घ compat_sys_ustat(अचिन्हित dev, काष्ठा compat_ustat __user *u32);
यंत्रlinkage दीर्घ compat_sys_recv(पूर्णांक fd, व्योम __user *buf, compat_माप_प्रकार len,
				अचिन्हित flags);

/* obsolete: fs/सूची_पढ़ो.c */
यंत्रlinkage दीर्घ compat_sys_old_सूची_पढ़ो(अचिन्हित पूर्णांक fd,
				       काष्ठा compat_old_linux_dirent __user *,
				       अचिन्हित पूर्णांक count);

/* obsolete: fs/select.c */
यंत्रlinkage दीर्घ compat_sys_old_select(काष्ठा compat_sel_arg_काष्ठा __user *arg);

/* obsolete: ipc */
यंत्रlinkage दीर्घ compat_sys_ipc(u32, पूर्णांक, पूर्णांक, u32, compat_uptr_t, u32);

/* obsolete: kernel/संकेत.c */
#अगर_घोषित __ARCH_WANT_SYS_SIGPENDING
यंत्रlinkage दीर्घ compat_sys_संक_बाकी(compat_old_sigset_t __user *set);
#पूर्ण_अगर

#अगर_घोषित __ARCH_WANT_SYS_SIGPROCMASK
यंत्रlinkage दीर्घ compat_sys_sigprocmask(पूर्णांक how, compat_old_sigset_t __user *nset,
				       compat_old_sigset_t __user *oset);
#पूर्ण_अगर
#अगर_घोषित CONFIG_COMPAT_OLD_SIGACTION
यंत्रlinkage दीर्घ compat_sys_sigaction(पूर्णांक sig,
                                   स्थिर काष्ठा compat_old_sigaction __user *act,
                                   काष्ठा compat_old_sigaction __user *oact);
#पूर्ण_अगर

/* obsolete: net/socket.c */
यंत्रlinkage दीर्घ compat_sys_socketcall(पूर्णांक call, u32 __user *args);

#पूर्ण_अगर /* CONFIG_ARCH_HAS_SYSCALL_WRAPPER */


/*
 * For most but not all architectures, "am I in a compat syscall?" and
 * "am I a compat task?" are the same question.  For architectures on which
 * they aren't the same question, arch code can override in_compat_syscall.
 */

#अगर_अघोषित in_compat_syscall
अटल अंतरभूत bool in_compat_syscall(व्योम) अणु वापस is_compat_task(); पूर्ण
#पूर्ण_अगर

/**
 * ns_to_old_समयval32 - Compat version of ns_to_समयval
 * @nsec:	the nanoseconds value to be converted
 *
 * Returns the old_समयval32 representation of the nsec parameter.
 */
अटल अंतरभूत काष्ठा old_समयval32 ns_to_old_समयval32(s64 nsec)
अणु
	काष्ठा __kernel_old_समयval tv;
	काष्ठा old_समयval32 ctv;

	tv = ns_to_kernel_old_समयval(nsec);
	ctv.tv_sec = tv.tv_sec;
	ctv.tv_usec = tv.tv_usec;

	वापस ctv;
पूर्ण

/*
 * Kernel code should not call compat syscalls (i.e., compat_sys_xyzyyz())
 * directly.  Instead, use one of the functions which work equivalently, such
 * as the kcompat_sys_xyzyyz() functions prototyped below.
 */

पूर्णांक kcompat_sys_statfs64(स्थिर अक्षर __user * pathname, compat_माप_प्रकार sz,
		     काष्ठा compat_statfs64 __user * buf);
पूर्णांक kcompat_sys_ख_स्थितिfs64(अचिन्हित पूर्णांक fd, compat_माप_प्रकार sz,
			  काष्ठा compat_statfs64 __user * buf);

#अन्यथा /* !CONFIG_COMPAT */

#घोषणा is_compat_task() (0)
/* Ensure no one redefines in_compat_syscall() under !CONFIG_COMPAT */
#घोषणा in_compat_syscall in_compat_syscall
अटल अंतरभूत bool in_compat_syscall(व्योम) अणु वापस false; पूर्ण

#पूर्ण_अगर /* CONFIG_COMPAT */

/*
 * Some legacy ABIs like the i386 one use less than natural alignment क्रम 64-bit
 * types, and will need special compat treaपंचांगent क्रम that.  Most architectures
 * करोn't need that special handling even क्रम compat syscalls.
 */
#अगर_अघोषित compat_need_64bit_alignment_fixup
#घोषणा compat_need_64bit_alignment_fixup()		false
#पूर्ण_अगर

/*
 * A poपूर्णांकer passed in from user mode. This should not
 * be used क्रम syscall parameters, just declare them
 * as poपूर्णांकers because the syscall entry code will have
 * appropriately converted them alपढ़ोy.
 */
#अगर_अघोषित compat_ptr
अटल अंतरभूत व्योम __user *compat_ptr(compat_uptr_t uptr)
अणु
	वापस (व्योम __user *)(अचिन्हित दीर्घ)uptr;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत compat_uptr_t ptr_to_compat(व्योम __user *uptr)
अणु
	वापस (u32)(अचिन्हित दीर्घ)uptr;
पूर्ण

#पूर्ण_अगर /* _LINUX_COMPAT_H */
