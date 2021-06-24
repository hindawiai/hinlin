<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * syscalls.h - Linux syscall पूर्णांकerfaces (non-arch-specअगरic)
 *
 * Copyright (c) 2004 Randy Dunlap
 * Copyright (c) 2004 Open Source Development Lअसल
 */

#अगर_अघोषित _LINUX_SYSCALLS_H
#घोषणा _LINUX_SYSCALLS_H

काष्ठा __aio_sigset;
काष्ठा epoll_event;
काष्ठा iattr;
काष्ठा inode;
काष्ठा iocb;
काष्ठा io_event;
काष्ठा iovec;
काष्ठा __kernel_old_iसमयrval;
काष्ठा kexec_segment;
काष्ठा linux_dirent;
काष्ठा linux_dirent64;
काष्ठा list_head;
काष्ठा mmap_arg_काष्ठा;
काष्ठा msgbuf;
काष्ठा user_msghdr;
काष्ठा mmsghdr;
काष्ठा msqid_ds;
काष्ठा new_utsname;
काष्ठा nfsctl_arg;
काष्ठा __old_kernel_stat;
काष्ठा olकरोld_utsname;
काष्ठा old_utsname;
काष्ठा pollfd;
काष्ठा rlimit;
काष्ठा rlimit64;
काष्ठा rusage;
काष्ठा sched_param;
काष्ठा sched_attr;
काष्ठा sel_arg_काष्ठा;
काष्ठा semaphore;
काष्ठा sembuf;
काष्ठा shmid_ds;
काष्ठा sockaddr;
काष्ठा stat;
काष्ठा stat64;
काष्ठा statfs;
काष्ठा statfs64;
काष्ठा statx;
काष्ठा sysinfo;
काष्ठा बारpec;
काष्ठा __kernel_old_समयval;
काष्ठा __kernel_समयx;
काष्ठा समयzone;
काष्ठा पंचांगs;
काष्ठा utimbuf;
काष्ठा mq_attr;
काष्ठा compat_stat;
काष्ठा old_समयval32;
काष्ठा robust_list_head;
काष्ठा अ_लोpu_cache;
काष्ठा old_linux_dirent;
काष्ठा perf_event_attr;
काष्ठा file_handle;
काष्ठा sigaltstack;
काष्ठा rseq;
जोड़ bpf_attr;
काष्ठा io_uring_params;
काष्ठा clone_args;
काष्ठा खोलो_how;
काष्ठा mount_attr;
काष्ठा landlock_ruleset_attr;
क्रमागत landlock_rule_type;

#समावेश <linux/types.h>
#समावेश <linux/aio_abi.h>
#समावेश <linux/capability.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/list.h>
#समावेश <linux/bug.h>
#समावेश <linux/sem.h>
#समावेश <यंत्र/siginfo.h>
#समावेश <linux/unistd.h>
#समावेश <linux/quota.h>
#समावेश <linux/key.h>
#समावेश <linux/personality.h>
#समावेश <trace/syscall.h>

#अगर_घोषित CONFIG_ARCH_HAS_SYSCALL_WRAPPER
/*
 * It may be useful क्रम an architecture to override the definitions of the
 * SYSCALL_DEFINE0() and __SYSCALL_DEFINEx() macros, in particular to use a
 * dअगरferent calling convention क्रम syscalls. To allow क्रम that, the prototypes
 * क्रम the sys_*() functions below will *not* be included अगर
 * CONFIG_ARCH_HAS_SYSCALL_WRAPPER is enabled.
 */
#समावेश <यंत्र/syscall_wrapper.h>
#पूर्ण_अगर /* CONFIG_ARCH_HAS_SYSCALL_WRAPPER */

/*
 * __MAP - apply a macro to syscall arguments
 * __MAP(n, m, t1, a1, t2, a2, ..., tn, an) will expand to
 *    m(t1, a1), m(t2, a2), ..., m(tn, an)
 * The first argument must be equal to the amount of type/name
 * pairs given.  Note that this list of pairs (i.e. the arguments
 * of __MAP starting at the third one) is in the same क्रमmat as
 * क्रम SYSCALL_DEFINE<n>/COMPAT_SYSCALL_DEFINE<n>
 */
#घोषणा __MAP0(m,...)
#घोषणा __MAP1(m,t,a,...) m(t,a)
#घोषणा __MAP2(m,t,a,...) m(t,a), __MAP1(m,__VA_ARGS__)
#घोषणा __MAP3(m,t,a,...) m(t,a), __MAP2(m,__VA_ARGS__)
#घोषणा __MAP4(m,t,a,...) m(t,a), __MAP3(m,__VA_ARGS__)
#घोषणा __MAP5(m,t,a,...) m(t,a), __MAP4(m,__VA_ARGS__)
#घोषणा __MAP6(m,t,a,...) m(t,a), __MAP5(m,__VA_ARGS__)
#घोषणा __MAP(n,...) __MAP##n(__VA_ARGS__)

#घोषणा __SC_DECL(t, a)	t a
#घोषणा __TYPE_AS(t, v)	__same_type((__क्रमce t)0, v)
#घोषणा __TYPE_IS_L(t)	(__TYPE_AS(t, 0L))
#घोषणा __TYPE_IS_UL(t)	(__TYPE_AS(t, 0UL))
#घोषणा __TYPE_IS_LL(t) (__TYPE_AS(t, 0LL) || __TYPE_AS(t, 0ULL))
#घोषणा __SC_LONG(t, a) __typeof(__builtin_choose_expr(__TYPE_IS_LL(t), 0LL, 0L)) a
#घोषणा __SC_CAST(t, a)	(__क्रमce t) a
#घोषणा __SC_ARGS(t, a)	a
#घोषणा __SC_TEST(t, a) (व्योम)BUILD_BUG_ON_ZERO(!__TYPE_IS_LL(t) && माप(t) > माप(दीर्घ))

#अगर_घोषित CONFIG_FTRACE_SYSCALLS
#घोषणा __SC_STR_ADECL(t, a)	#a
#घोषणा __SC_STR_TDECL(t, a)	#t

बाह्य काष्ठा trace_event_class event_class_syscall_enter;
बाह्य काष्ठा trace_event_class event_class_syscall_निकास;
बाह्य काष्ठा trace_event_functions enter_syscall_prपूर्णांक_funcs;
बाह्य काष्ठा trace_event_functions निकास_syscall_prपूर्णांक_funcs;

#घोषणा SYSCALL_TRACE_ENTER_EVENT(sname)				\
	अटल काष्ठा syscall_metadata __syscall_meta_##sname;		\
	अटल काष्ठा trace_event_call __used				\
	  event_enter_##sname = अणु					\
		.class			= &event_class_syscall_enter,	\
		अणु							\
			.name                   = "sys_enter"#sname,	\
		पूर्ण,							\
		.event.funcs            = &enter_syscall_prपूर्णांक_funcs,	\
		.data			= (व्योम *)&__syscall_meta_##sname,\
		.flags                  = TRACE_EVENT_FL_CAP_ANY,	\
	पूर्ण;								\
	अटल काष्ठा trace_event_call __used				\
	  __section("_ftrace_events")					\
	 *__event_enter_##sname = &event_enter_##sname;

#घोषणा SYSCALL_TRACE_EXIT_EVENT(sname)					\
	अटल काष्ठा syscall_metadata __syscall_meta_##sname;		\
	अटल काष्ठा trace_event_call __used				\
	  event_निकास_##sname = अणु					\
		.class			= &event_class_syscall_निकास,	\
		अणु							\
			.name                   = "sys_exit"#sname,	\
		पूर्ण,							\
		.event.funcs		= &निकास_syscall_prपूर्णांक_funcs,	\
		.data			= (व्योम *)&__syscall_meta_##sname,\
		.flags                  = TRACE_EVENT_FL_CAP_ANY,	\
	पूर्ण;								\
	अटल काष्ठा trace_event_call __used				\
	  __section("_ftrace_events")					\
	*__event_निकास_##sname = &event_निकास_##sname;

#घोषणा SYSCALL_METADATA(sname, nb, ...)			\
	अटल स्थिर अक्षर *types_##sname[] = अणु			\
		__MAP(nb,__SC_STR_TDECL,__VA_ARGS__)		\
	पूर्ण;							\
	अटल स्थिर अक्षर *args_##sname[] = अणु			\
		__MAP(nb,__SC_STR_ADECL,__VA_ARGS__)		\
	पूर्ण;							\
	SYSCALL_TRACE_ENTER_EVENT(sname);			\
	SYSCALL_TRACE_EXIT_EVENT(sname);			\
	अटल काष्ठा syscall_metadata __used			\
	  __syscall_meta_##sname = अणु				\
		.name 		= "sys"#sname,			\
		.syscall_nr	= -1,	/* Filled in at boot */	\
		.nb_args 	= nb,				\
		.types		= nb ? types_##sname : शून्य,	\
		.args		= nb ? args_##sname : शून्य,	\
		.enter_event	= &event_enter_##sname,		\
		.निकास_event	= &event_निकास_##sname,		\
		.enter_fields	= LIST_HEAD_INIT(__syscall_meta_##sname.enter_fields), \
	पूर्ण;							\
	अटल काष्ठा syscall_metadata __used			\
	  __section("__syscalls_metadata")			\
	 *__p_syscall_meta_##sname = &__syscall_meta_##sname;

अटल अंतरभूत पूर्णांक is_syscall_trace_event(काष्ठा trace_event_call *tp_event)
अणु
	वापस tp_event->class == &event_class_syscall_enter ||
	       tp_event->class == &event_class_syscall_निकास;
पूर्ण

#अन्यथा
#घोषणा SYSCALL_METADATA(sname, nb, ...)

अटल अंतरभूत पूर्णांक is_syscall_trace_event(काष्ठा trace_event_call *tp_event)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित SYSCALL_DEFINE0
#घोषणा SYSCALL_DEFINE0(sname)					\
	SYSCALL_METADATA(_##sname, 0);				\
	यंत्रlinkage दीर्घ sys_##sname(व्योम);			\
	ALLOW_ERROR_INJECTION(sys_##sname, ERRNO);		\
	यंत्रlinkage दीर्घ sys_##sname(व्योम)
#पूर्ण_अगर /* SYSCALL_DEFINE0 */

#घोषणा SYSCALL_DEFINE1(name, ...) SYSCALL_DEFINEx(1, _##name, __VA_ARGS__)
#घोषणा SYSCALL_DEFINE2(name, ...) SYSCALL_DEFINEx(2, _##name, __VA_ARGS__)
#घोषणा SYSCALL_DEFINE3(name, ...) SYSCALL_DEFINEx(3, _##name, __VA_ARGS__)
#घोषणा SYSCALL_DEFINE4(name, ...) SYSCALL_DEFINEx(4, _##name, __VA_ARGS__)
#घोषणा SYSCALL_DEFINE5(name, ...) SYSCALL_DEFINEx(5, _##name, __VA_ARGS__)
#घोषणा SYSCALL_DEFINE6(name, ...) SYSCALL_DEFINEx(6, _##name, __VA_ARGS__)

#घोषणा SYSCALL_DEFINE_MAXARGS	6

#घोषणा SYSCALL_DEFINEx(x, sname, ...)				\
	SYSCALL_METADATA(sname, x, __VA_ARGS__)			\
	__SYSCALL_DEFINEx(x, sname, __VA_ARGS__)

#घोषणा __PROTECT(...) यंत्रlinkage_protect(__VA_ARGS__)

/*
 * The यंत्रlinkage stub is aliased to a function named __se_sys_*() which
 * sign-extends 32-bit पूर्णांकs to दीर्घs whenever needed. The actual work is
 * करोne within __करो_sys_*().
 */
#अगर_अघोषित __SYSCALL_DEFINEx
#घोषणा __SYSCALL_DEFINEx(x, name, ...)					\
	__diag_push();							\
	__diag_ignore(GCC, 8, "-Wattribute-alias",			\
		      "Type aliasing is used to sanitize syscall arguments");\
	यंत्रlinkage दीर्घ sys##name(__MAP(x,__SC_DECL,__VA_ARGS__))	\
		__attribute__((alias(__stringअगरy(__se_sys##name))));	\
	ALLOW_ERROR_INJECTION(sys##name, ERRNO);			\
	अटल अंतरभूत दीर्घ __करो_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__));\
	यंत्रlinkage दीर्घ __se_sys##name(__MAP(x,__SC_LONG,__VA_ARGS__));	\
	यंत्रlinkage दीर्घ __se_sys##name(__MAP(x,__SC_LONG,__VA_ARGS__))	\
	अणु								\
		दीर्घ ret = __करो_sys##name(__MAP(x,__SC_CAST,__VA_ARGS__));\
		__MAP(x,__SC_TEST,__VA_ARGS__);				\
		__PROTECT(x, ret,__MAP(x,__SC_ARGS,__VA_ARGS__));	\
		वापस ret;						\
	पूर्ण								\
	__diag_pop();							\
	अटल अंतरभूत दीर्घ __करो_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__))
#पूर्ण_अगर /* __SYSCALL_DEFINEx */

/* For split 64-bit arguments on 32-bit architectures */
#अगर_घोषित __LITTLE_ENDIAN
#घोषणा SC_ARG64(name) u32, name##_lo, u32, name##_hi
#अन्यथा
#घोषणा SC_ARG64(name) u32, name##_hi, u32, name##_lo
#पूर्ण_अगर
#घोषणा SC_VAL64(type, name) ((type) name##_hi << 32 | name##_lo)

#अगर_घोषित CONFIG_COMPAT
#घोषणा SYSCALL32_DEFINE1 COMPAT_SYSCALL_DEFINE1
#घोषणा SYSCALL32_DEFINE2 COMPAT_SYSCALL_DEFINE2
#घोषणा SYSCALL32_DEFINE3 COMPAT_SYSCALL_DEFINE3
#घोषणा SYSCALL32_DEFINE4 COMPAT_SYSCALL_DEFINE4
#घोषणा SYSCALL32_DEFINE5 COMPAT_SYSCALL_DEFINE5
#घोषणा SYSCALL32_DEFINE6 COMPAT_SYSCALL_DEFINE6
#अन्यथा
#घोषणा SYSCALL32_DEFINE1 SYSCALL_DEFINE1
#घोषणा SYSCALL32_DEFINE2 SYSCALL_DEFINE2
#घोषणा SYSCALL32_DEFINE3 SYSCALL_DEFINE3
#घोषणा SYSCALL32_DEFINE4 SYSCALL_DEFINE4
#घोषणा SYSCALL32_DEFINE5 SYSCALL_DEFINE5
#घोषणा SYSCALL32_DEFINE6 SYSCALL_DEFINE6
#पूर्ण_अगर

/*
 * Called beक्रमe coming back to user-mode. Returning to user-mode with an
 * address limit dअगरferent than USER_DS can allow to overग_लिखो kernel memory.
 */
अटल अंतरभूत व्योम addr_limit_user_check(व्योम)
अणु
#अगर_घोषित TIF_FSCHECK
	अगर (!test_thपढ़ो_flag(TIF_FSCHECK))
		वापस;
#पूर्ण_अगर

	अगर (CHECK_DATA_CORRUPTION(uaccess_kernel(),
				  "Invalid address limit on user-mode return"))
		क्रमce_sig(SIGKILL);

#अगर_घोषित TIF_FSCHECK
	clear_thपढ़ो_flag(TIF_FSCHECK);
#पूर्ण_अगर
पूर्ण

/*
 * These syscall function prototypes are kept in the same order as
 * include/uapi/यंत्र-generic/unistd.h. Architecture specअगरic entries go below,
 * followed by deprecated or obsolete प्रणाली calls.
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
यंत्रlinkage दीर्घ sys_io_setup(अचिन्हित nr_reqs, aio_context_t __user *ctx);
यंत्रlinkage दीर्घ sys_io_destroy(aio_context_t ctx);
यंत्रlinkage दीर्घ sys_io_submit(aio_context_t, दीर्घ,
			काष्ठा iocb __user * __user *);
यंत्रlinkage दीर्घ sys_io_cancel(aio_context_t ctx_id, काष्ठा iocb __user *iocb,
			      काष्ठा io_event __user *result);
यंत्रlinkage दीर्घ sys_io_getevents(aio_context_t ctx_id,
				दीर्घ min_nr,
				दीर्घ nr,
				काष्ठा io_event __user *events,
				काष्ठा __kernel_बारpec __user *समयout);
यंत्रlinkage दीर्घ sys_io_getevents_समय32(__u32 ctx_id,
				__s32 min_nr,
				__s32 nr,
				काष्ठा io_event __user *events,
				काष्ठा old_बारpec32 __user *समयout);
यंत्रlinkage दीर्घ sys_io_pgetevents(aio_context_t ctx_id,
				दीर्घ min_nr,
				दीर्घ nr,
				काष्ठा io_event __user *events,
				काष्ठा __kernel_बारpec __user *समयout,
				स्थिर काष्ठा __aio_sigset *sig);
यंत्रlinkage दीर्घ sys_io_pgetevents_समय32(aio_context_t ctx_id,
				दीर्घ min_nr,
				दीर्घ nr,
				काष्ठा io_event __user *events,
				काष्ठा old_बारpec32 __user *समयout,
				स्थिर काष्ठा __aio_sigset *sig);
यंत्रlinkage दीर्घ sys_io_uring_setup(u32 entries,
				काष्ठा io_uring_params __user *p);
यंत्रlinkage दीर्घ sys_io_uring_enter(अचिन्हित पूर्णांक fd, u32 to_submit,
				u32 min_complete, u32 flags,
				स्थिर व्योम __user *argp, माप_प्रकार argsz);
यंत्रlinkage दीर्घ sys_io_uring_रेजिस्टर(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक op,
				व्योम __user *arg, अचिन्हित पूर्णांक nr_args);

/* fs/xattr.c */
यंत्रlinkage दीर्घ sys_setxattr(स्थिर अक्षर __user *path, स्थिर अक्षर __user *name,
			     स्थिर व्योम __user *value, माप_प्रकार size, पूर्णांक flags);
यंत्रlinkage दीर्घ sys_lsetxattr(स्थिर अक्षर __user *path, स्थिर अक्षर __user *name,
			      स्थिर व्योम __user *value, माप_प्रकार size, पूर्णांक flags);
यंत्रlinkage दीर्घ sys_fsetxattr(पूर्णांक fd, स्थिर अक्षर __user *name,
			      स्थिर व्योम __user *value, माप_प्रकार size, पूर्णांक flags);
यंत्रlinkage दीर्घ sys_getxattr(स्थिर अक्षर __user *path, स्थिर अक्षर __user *name,
			     व्योम __user *value, माप_प्रकार size);
यंत्रlinkage दीर्घ sys_lgetxattr(स्थिर अक्षर __user *path, स्थिर अक्षर __user *name,
			      व्योम __user *value, माप_प्रकार size);
यंत्रlinkage दीर्घ sys_fgetxattr(पूर्णांक fd, स्थिर अक्षर __user *name,
			      व्योम __user *value, माप_प्रकार size);
यंत्रlinkage दीर्घ sys_listxattr(स्थिर अक्षर __user *path, अक्षर __user *list,
			      माप_प्रकार size);
यंत्रlinkage दीर्घ sys_llistxattr(स्थिर अक्षर __user *path, अक्षर __user *list,
			       माप_प्रकार size);
यंत्रlinkage दीर्घ sys_flistxattr(पूर्णांक fd, अक्षर __user *list, माप_प्रकार size);
यंत्रlinkage दीर्घ sys_हटाओxattr(स्थिर अक्षर __user *path,
				स्थिर अक्षर __user *name);
यंत्रlinkage दीर्घ sys_lहटाओxattr(स्थिर अक्षर __user *path,
				 स्थिर अक्षर __user *name);
यंत्रlinkage दीर्घ sys_fहटाओxattr(पूर्णांक fd, स्थिर अक्षर __user *name);

/* fs/dcache.c */
यंत्रlinkage दीर्घ sys_अ_लोwd(अक्षर __user *buf, अचिन्हित दीर्घ size);

/* fs/cookies.c */
यंत्रlinkage दीर्घ sys_lookup_dcookie(u64 cookie64, अक्षर __user *buf, माप_प्रकार len);

/* fs/eventfd.c */
यंत्रlinkage दीर्घ sys_eventfd2(अचिन्हित पूर्णांक count, पूर्णांक flags);

/* fs/eventpoll.c */
यंत्रlinkage दीर्घ sys_epoll_create1(पूर्णांक flags);
यंत्रlinkage दीर्घ sys_epoll_ctl(पूर्णांक epfd, पूर्णांक op, पूर्णांक fd,
				काष्ठा epoll_event __user *event);
यंत्रlinkage दीर्घ sys_epoll_pरुको(पूर्णांक epfd, काष्ठा epoll_event __user *events,
				पूर्णांक maxevents, पूर्णांक समयout,
				स्थिर sigset_t __user *sigmask,
				माप_प्रकार sigsetsize);
यंत्रlinkage दीर्घ sys_epoll_pरुको2(पूर्णांक epfd, काष्ठा epoll_event __user *events,
				 पूर्णांक maxevents,
				 स्थिर काष्ठा __kernel_बारpec __user *समयout,
				 स्थिर sigset_t __user *sigmask,
				 माप_प्रकार sigsetsize);

/* fs/fcntl.c */
यंत्रlinkage दीर्घ sys_dup(अचिन्हित पूर्णांक fildes);
यंत्रlinkage दीर्घ sys_dup3(अचिन्हित पूर्णांक oldfd, अचिन्हित पूर्णांक newfd, पूर्णांक flags);
यंत्रlinkage दीर्घ sys_fcntl(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
#अगर BITS_PER_LONG == 32
यंत्रlinkage दीर्घ sys_fcntl64(अचिन्हित पूर्णांक fd,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
#पूर्ण_अगर

/* fs/inotअगरy_user.c */
यंत्रlinkage दीर्घ sys_inotअगरy_init1(पूर्णांक flags);
यंत्रlinkage दीर्घ sys_inotअगरy_add_watch(पूर्णांक fd, स्थिर अक्षर __user *path,
					u32 mask);
यंत्रlinkage दीर्घ sys_inotअगरy_rm_watch(पूर्णांक fd, __s32 wd);

/* fs/ioctl.c */
यंत्रlinkage दीर्घ sys_ioctl(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg);

/* fs/ioprio.c */
यंत्रlinkage दीर्घ sys_ioprio_set(पूर्णांक which, पूर्णांक who, पूर्णांक ioprio);
यंत्रlinkage दीर्घ sys_ioprio_get(पूर्णांक which, पूर्णांक who);

/* fs/locks.c */
यंत्रlinkage दीर्घ sys_flock(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक cmd);

/* fs/namei.c */
यंत्रlinkage दीर्घ sys_mknodat(पूर्णांक dfd, स्थिर अक्षर __user * filename, umode_t mode,
			    अचिन्हित dev);
यंत्रlinkage दीर्घ sys_सूची_गढ़ोat(पूर्णांक dfd, स्थिर अक्षर __user * pathname, umode_t mode);
यंत्रlinkage दीर्घ sys_unlinkat(पूर्णांक dfd, स्थिर अक्षर __user * pathname, पूर्णांक flag);
यंत्रlinkage दीर्घ sys_symlinkat(स्थिर अक्षर __user * oldname,
			      पूर्णांक newdfd, स्थिर अक्षर __user * newname);
यंत्रlinkage दीर्घ sys_linkat(पूर्णांक olddfd, स्थिर अक्षर __user *oldname,
			   पूर्णांक newdfd, स्थिर अक्षर __user *newname, पूर्णांक flags);
यंत्रlinkage दीर्घ sys_नामat(पूर्णांक olddfd, स्थिर अक्षर __user * oldname,
			     पूर्णांक newdfd, स्थिर अक्षर __user * newname);

/* fs/namespace.c */
यंत्रlinkage दीर्घ sys_umount(अक्षर __user *name, पूर्णांक flags);
यंत्रlinkage दीर्घ sys_mount(अक्षर __user *dev_name, अक्षर __user *dir_name,
				अक्षर __user *type, अचिन्हित दीर्घ flags,
				व्योम __user *data);
यंत्रlinkage दीर्घ sys_pivot_root(स्थिर अक्षर __user *new_root,
				स्थिर अक्षर __user *put_old);

/* fs/nfsctl.c */

/* fs/खोलो.c */
यंत्रlinkage दीर्घ sys_statfs(स्थिर अक्षर __user * path,
				काष्ठा statfs __user *buf);
यंत्रlinkage दीर्घ sys_statfs64(स्थिर अक्षर __user *path, माप_प्रकार sz,
				काष्ठा statfs64 __user *buf);
यंत्रlinkage दीर्घ sys_ख_स्थितिfs(अचिन्हित पूर्णांक fd, काष्ठा statfs __user *buf);
यंत्रlinkage दीर्घ sys_ख_स्थितिfs64(अचिन्हित पूर्णांक fd, माप_प्रकार sz,
				काष्ठा statfs64 __user *buf);
यंत्रlinkage दीर्घ sys_truncate(स्थिर अक्षर __user *path, दीर्घ length);
यंत्रlinkage दीर्घ sys_ftruncate(अचिन्हित पूर्णांक fd, अचिन्हित दीर्घ length);
#अगर BITS_PER_LONG == 32
यंत्रlinkage दीर्घ sys_truncate64(स्थिर अक्षर __user *path, loff_t length);
यंत्रlinkage दीर्घ sys_ftruncate64(अचिन्हित पूर्णांक fd, loff_t length);
#पूर्ण_अगर
यंत्रlinkage दीर्घ sys_fallocate(पूर्णांक fd, पूर्णांक mode, loff_t offset, loff_t len);
यंत्रlinkage दीर्घ sys_faccessat(पूर्णांक dfd, स्थिर अक्षर __user *filename, पूर्णांक mode);
यंत्रlinkage दीर्घ sys_faccessat2(पूर्णांक dfd, स्थिर अक्षर __user *filename, पूर्णांक mode,
			       पूर्णांक flags);
यंत्रlinkage दीर्घ sys_स_बदलो(स्थिर अक्षर __user *filename);
यंत्रlinkage दीर्घ sys_fस_बदलो(अचिन्हित पूर्णांक fd);
यंत्रlinkage दीर्घ sys_chroot(स्थिर अक्षर __user *filename);
यंत्रlinkage दीर्घ sys_fchmod(अचिन्हित पूर्णांक fd, umode_t mode);
यंत्रlinkage दीर्घ sys_fchmodat(पूर्णांक dfd, स्थिर अक्षर __user * filename,
			     umode_t mode);
यंत्रlinkage दीर्घ sys_fchownat(पूर्णांक dfd, स्थिर अक्षर __user *filename, uid_t user,
			     gid_t group, पूर्णांक flag);
यंत्रlinkage दीर्घ sys_fchown(अचिन्हित पूर्णांक fd, uid_t user, gid_t group);
यंत्रlinkage दीर्घ sys_खोलोat(पूर्णांक dfd, स्थिर अक्षर __user *filename, पूर्णांक flags,
			   umode_t mode);
यंत्रlinkage दीर्घ sys_खोलोat2(पूर्णांक dfd, स्थिर अक्षर __user *filename,
			    काष्ठा खोलो_how *how, माप_प्रकार size);
यंत्रlinkage दीर्घ sys_बंद(अचिन्हित पूर्णांक fd);
यंत्रlinkage दीर्घ sys_बंद_range(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक max_fd,
				अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_vhangup(व्योम);

/* fs/pipe.c */
यंत्रlinkage दीर्घ sys_pipe2(पूर्णांक __user *fildes, पूर्णांक flags);

/* fs/quota.c */
यंत्रlinkage दीर्घ sys_quotactl(अचिन्हित पूर्णांक cmd, स्थिर अक्षर __user *special,
				qid_t id, व्योम __user *addr);
यंत्रlinkage दीर्घ sys_quotactl_path(अचिन्हित पूर्णांक cmd, स्थिर अक्षर __user *mountpoपूर्णांक,
				  qid_t id, व्योम __user *addr);

/* fs/सूची_पढ़ो.c */
यंत्रlinkage दीर्घ sys_getdents64(अचिन्हित पूर्णांक fd,
				काष्ठा linux_dirent64 __user *dirent,
				अचिन्हित पूर्णांक count);

/* fs/पढ़ो_ग_लिखो.c */
यंत्रlinkage दीर्घ sys_llseek(अचिन्हित पूर्णांक fd, अचिन्हित दीर्घ offset_high,
			अचिन्हित दीर्घ offset_low, loff_t __user *result,
			अचिन्हित पूर्णांक whence);
यंत्रlinkage दीर्घ sys_lseek(अचिन्हित पूर्णांक fd, off_t offset,
			  अचिन्हित पूर्णांक whence);
यंत्रlinkage दीर्घ sys_पढ़ो(अचिन्हित पूर्णांक fd, अक्षर __user *buf, माप_प्रकार count);
यंत्रlinkage दीर्घ sys_ग_लिखो(अचिन्हित पूर्णांक fd, स्थिर अक्षर __user *buf,
			  माप_प्रकार count);
यंत्रlinkage दीर्घ sys_पढ़ोv(अचिन्हित दीर्घ fd,
			  स्थिर काष्ठा iovec __user *vec,
			  अचिन्हित दीर्घ vlen);
यंत्रlinkage दीर्घ sys_ग_लिखोv(अचिन्हित दीर्घ fd,
			   स्थिर काष्ठा iovec __user *vec,
			   अचिन्हित दीर्घ vlen);
यंत्रlinkage दीर्घ sys_pपढ़ो64(अचिन्हित पूर्णांक fd, अक्षर __user *buf,
			    माप_प्रकार count, loff_t pos);
यंत्रlinkage दीर्घ sys_pग_लिखो64(अचिन्हित पूर्णांक fd, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t pos);
यंत्रlinkage दीर्घ sys_pपढ़ोv(अचिन्हित दीर्घ fd, स्थिर काष्ठा iovec __user *vec,
			   अचिन्हित दीर्घ vlen, अचिन्हित दीर्घ pos_l, अचिन्हित दीर्घ pos_h);
यंत्रlinkage दीर्घ sys_pग_लिखोv(अचिन्हित दीर्घ fd, स्थिर काष्ठा iovec __user *vec,
			    अचिन्हित दीर्घ vlen, अचिन्हित दीर्घ pos_l, अचिन्हित दीर्घ pos_h);

/* fs/sendfile.c */
यंत्रlinkage दीर्घ sys_sendfile64(पूर्णांक out_fd, पूर्णांक in_fd,
			       loff_t __user *offset, माप_प्रकार count);

/* fs/select.c */
यंत्रlinkage दीर्घ sys_pselect6(पूर्णांक, fd_set __user *, fd_set __user *,
			     fd_set __user *, काष्ठा __kernel_बारpec __user *,
			     व्योम __user *);
यंत्रlinkage दीर्घ sys_pselect6_समय32(पूर्णांक, fd_set __user *, fd_set __user *,
			     fd_set __user *, काष्ठा old_बारpec32 __user *,
			     व्योम __user *);
यंत्रlinkage दीर्घ sys_ppoll(काष्ठा pollfd __user *, अचिन्हित पूर्णांक,
			  काष्ठा __kernel_बारpec __user *, स्थिर sigset_t __user *,
			  माप_प्रकार);
यंत्रlinkage दीर्घ sys_ppoll_समय32(काष्ठा pollfd __user *, अचिन्हित पूर्णांक,
			  काष्ठा old_बारpec32 __user *, स्थिर sigset_t __user *,
			  माप_प्रकार);

/* fs/संकेतfd.c */
यंत्रlinkage दीर्घ sys_संकेतfd4(पूर्णांक ufd, sigset_t __user *user_mask, माप_प्रकार sizemask, पूर्णांक flags);

/* fs/splice.c */
यंत्रlinkage दीर्घ sys_vmsplice(पूर्णांक fd, स्थिर काष्ठा iovec __user *iov,
			     अचिन्हित दीर्घ nr_segs, अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_splice(पूर्णांक fd_in, loff_t __user *off_in,
			   पूर्णांक fd_out, loff_t __user *off_out,
			   माप_प्रकार len, अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_tee(पूर्णांक fdin, पूर्णांक fकरोut, माप_प्रकार len, अचिन्हित पूर्णांक flags);

/* fs/stat.c */
यंत्रlinkage दीर्घ sys_पढ़ोlinkat(पूर्णांक dfd, स्थिर अक्षर __user *path, अक्षर __user *buf,
			       पूर्णांक bufsiz);
यंत्रlinkage दीर्घ sys_newख_स्थितिat(पूर्णांक dfd, स्थिर अक्षर __user *filename,
			       काष्ठा stat __user *statbuf, पूर्णांक flag);
यंत्रlinkage दीर्घ sys_newख_स्थिति(अचिन्हित पूर्णांक fd, काष्ठा stat __user *statbuf);
#अगर defined(__ARCH_WANT_STAT64) || defined(__ARCH_WANT_COMPAT_STAT64)
यंत्रlinkage दीर्घ sys_ख_स्थिति64(अचिन्हित दीर्घ fd, काष्ठा stat64 __user *statbuf);
यंत्रlinkage दीर्घ sys_ख_स्थितिat64(पूर्णांक dfd, स्थिर अक्षर __user *filename,
			       काष्ठा stat64 __user *statbuf, पूर्णांक flag);
#पूर्ण_अगर

/* fs/sync.c */
यंत्रlinkage दीर्घ sys_sync(व्योम);
यंत्रlinkage दीर्घ sys_fsync(अचिन्हित पूर्णांक fd);
यंत्रlinkage दीर्घ sys_fdatasync(अचिन्हित पूर्णांक fd);
यंत्रlinkage दीर्घ sys_sync_file_range2(पूर्णांक fd, अचिन्हित पूर्णांक flags,
				     loff_t offset, loff_t nbytes);
यंत्रlinkage दीर्घ sys_sync_file_range(पूर्णांक fd, loff_t offset, loff_t nbytes,
					अचिन्हित पूर्णांक flags);

/* fs/समयrfd.c */
यंत्रlinkage दीर्घ sys_समयrfd_create(पूर्णांक घड़ीid, पूर्णांक flags);
यंत्रlinkage दीर्घ sys_समयrfd_समय_रखो(पूर्णांक ufd, पूर्णांक flags,
				    स्थिर काष्ठा __kernel_iसमयrspec __user *uपंचांगr,
				    काष्ठा __kernel_iसमयrspec __user *oपंचांगr);
यंत्रlinkage दीर्घ sys_समयrfd_समय_लो(पूर्णांक ufd, काष्ठा __kernel_iसमयrspec __user *oपंचांगr);
यंत्रlinkage दीर्घ sys_समयrfd_समय_लो32(पूर्णांक ufd,
				   काष्ठा old_iसमयrspec32 __user *oपंचांगr);
यंत्रlinkage दीर्घ sys_समयrfd_समय_रखो32(पूर्णांक ufd, पूर्णांक flags,
				   स्थिर काष्ठा old_iसमयrspec32 __user *uपंचांगr,
				   काष्ठा old_iसमयrspec32 __user *oपंचांगr);

/* fs/uबार.c */
यंत्रlinkage दीर्घ sys_uसमयnsat(पूर्णांक dfd, स्थिर अक्षर __user *filename,
				काष्ठा __kernel_बारpec __user *uबार,
				पूर्णांक flags);
यंत्रlinkage दीर्घ sys_uसमयnsat_समय32(अचिन्हित पूर्णांक dfd,
				स्थिर अक्षर __user *filename,
				काष्ठा old_बारpec32 __user *t, पूर्णांक flags);

/* kernel/acct.c */
यंत्रlinkage दीर्घ sys_acct(स्थिर अक्षर __user *name);

/* kernel/capability.c */
यंत्रlinkage दीर्घ sys_capget(cap_user_header_t header,
				cap_user_data_t dataptr);
यंत्रlinkage दीर्घ sys_capset(cap_user_header_t header,
				स्थिर cap_user_data_t data);

/* kernel/exec_करोमुख्य.c */
यंत्रlinkage दीर्घ sys_personality(अचिन्हित पूर्णांक personality);

/* kernel/निकास.c */
यंत्रlinkage दीर्घ sys_निकास(पूर्णांक error_code);
यंत्रlinkage दीर्घ sys_निकास_group(पूर्णांक error_code);
यंत्रlinkage दीर्घ sys_रुकोid(पूर्णांक which, pid_t pid,
			   काष्ठा siginfo __user *infop,
			   पूर्णांक options, काष्ठा rusage __user *ru);

/* kernel/विभाजन.c */
यंत्रlinkage दीर्घ sys_set_tid_address(पूर्णांक __user *tidptr);
यंत्रlinkage दीर्घ sys_unshare(अचिन्हित दीर्घ unshare_flags);

/* kernel/futex.c */
यंत्रlinkage दीर्घ sys_futex(u32 __user *uaddr, पूर्णांक op, u32 val,
			  स्थिर काष्ठा __kernel_बारpec __user *uसमय,
			  u32 __user *uaddr2, u32 val3);
यंत्रlinkage दीर्घ sys_futex_समय32(u32 __user *uaddr, पूर्णांक op, u32 val,
				 स्थिर काष्ठा old_बारpec32 __user *uसमय,
				 u32 __user *uaddr2, u32 val3);
यंत्रlinkage दीर्घ sys_get_robust_list(पूर्णांक pid,
				    काष्ठा robust_list_head __user * __user *head_ptr,
				    माप_प्रकार __user *len_ptr);
यंत्रlinkage दीर्घ sys_set_robust_list(काष्ठा robust_list_head __user *head,
				    माप_प्रकार len);

/* kernel/hrसमयr.c */
यंत्रlinkage दीर्घ sys_nanosleep(काष्ठा __kernel_बारpec __user *rqtp,
			      काष्ठा __kernel_बारpec __user *rmtp);
यंत्रlinkage दीर्घ sys_nanosleep_समय32(काष्ठा old_बारpec32 __user *rqtp,
				     काष्ठा old_बारpec32 __user *rmtp);

/* kernel/iसमयr.c */
यंत्रlinkage दीर्घ sys_getiसमयr(पूर्णांक which, काष्ठा __kernel_old_iसमयrval __user *value);
यंत्रlinkage दीर्घ sys_setiसमयr(पूर्णांक which,
				काष्ठा __kernel_old_iसमयrval __user *value,
				काष्ठा __kernel_old_iसमयrval __user *ovalue);

/* kernel/kexec.c */
यंत्रlinkage दीर्घ sys_kexec_load(अचिन्हित दीर्घ entry, अचिन्हित दीर्घ nr_segments,
				काष्ठा kexec_segment __user *segments,
				अचिन्हित दीर्घ flags);

/* kernel/module.c */
यंत्रlinkage दीर्घ sys_init_module(व्योम __user *umod, अचिन्हित दीर्घ len,
				स्थिर अक्षर __user *uargs);
यंत्रlinkage दीर्घ sys_delete_module(स्थिर अक्षर __user *name_user,
				अचिन्हित पूर्णांक flags);

/* kernel/posix-समयrs.c */
यंत्रlinkage दीर्घ sys_समयr_create(घड़ीid_t which_घड़ी,
				 काष्ठा sigevent __user *समयr_event_spec,
				 समयr_t __user * created_समयr_id);
यंत्रlinkage दीर्घ sys_समयr_समय_लो(समयr_t समयr_id,
				काष्ठा __kernel_iसमयrspec __user *setting);
यंत्रlinkage दीर्घ sys_समयr_getoverrun(समयr_t समयr_id);
यंत्रlinkage दीर्घ sys_समयr_समय_रखो(समयr_t समयr_id, पूर्णांक flags,
				स्थिर काष्ठा __kernel_iसमयrspec __user *new_setting,
				काष्ठा __kernel_iसमयrspec __user *old_setting);
यंत्रlinkage दीर्घ sys_समयr_delete(समयr_t समयr_id);
यंत्रlinkage दीर्घ sys_घड़ी_समय_रखो(घड़ीid_t which_घड़ी,
				स्थिर काष्ठा __kernel_बारpec __user *tp);
यंत्रlinkage दीर्घ sys_घड़ी_समय_लो(घड़ीid_t which_घड़ी,
				काष्ठा __kernel_बारpec __user *tp);
यंत्रlinkage दीर्घ sys_घड़ी_getres(घड़ीid_t which_घड़ी,
				काष्ठा __kernel_बारpec __user *tp);
यंत्रlinkage दीर्घ sys_घड़ी_nanosleep(घड़ीid_t which_घड़ी, पूर्णांक flags,
				स्थिर काष्ठा __kernel_बारpec __user *rqtp,
				काष्ठा __kernel_बारpec __user *rmtp);
यंत्रlinkage दीर्घ sys_समयr_समय_लो32(समयr_t समयr_id,
				 काष्ठा old_iसमयrspec32 __user *setting);
यंत्रlinkage दीर्घ sys_समयr_समय_रखो32(समयr_t समयr_id, पूर्णांक flags,
					 काष्ठा old_iसमयrspec32 __user *new,
					 काष्ठा old_iसमयrspec32 __user *old);
यंत्रlinkage दीर्घ sys_घड़ी_समय_रखो32(घड़ीid_t which_घड़ी,
				काष्ठा old_बारpec32 __user *tp);
यंत्रlinkage दीर्घ sys_घड़ी_समय_लो32(घड़ीid_t which_घड़ी,
				काष्ठा old_बारpec32 __user *tp);
यंत्रlinkage दीर्घ sys_घड़ी_getres_समय32(घड़ीid_t which_घड़ी,
				काष्ठा old_बारpec32 __user *tp);
यंत्रlinkage दीर्घ sys_घड़ी_nanosleep_समय32(घड़ीid_t which_घड़ी, पूर्णांक flags,
				काष्ठा old_बारpec32 __user *rqtp,
				काष्ठा old_बारpec32 __user *rmtp);

/* kernel/prपूर्णांकk.c */
यंत्रlinkage दीर्घ sys_syslog(पूर्णांक type, अक्षर __user *buf, पूर्णांक len);

/* kernel/ptrace.c */
यंत्रlinkage दीर्घ sys_ptrace(दीर्घ request, दीर्घ pid, अचिन्हित दीर्घ addr,
			   अचिन्हित दीर्घ data);
/* kernel/sched/core.c */

यंत्रlinkage दीर्घ sys_sched_setparam(pid_t pid,
					काष्ठा sched_param __user *param);
यंत्रlinkage दीर्घ sys_sched_setscheduler(pid_t pid, पूर्णांक policy,
					काष्ठा sched_param __user *param);
यंत्रlinkage दीर्घ sys_sched_माला_लोcheduler(pid_t pid);
यंत्रlinkage दीर्घ sys_sched_getparam(pid_t pid,
					काष्ठा sched_param __user *param);
यंत्रlinkage दीर्घ sys_sched_setaffinity(pid_t pid, अचिन्हित पूर्णांक len,
					अचिन्हित दीर्घ __user *user_mask_ptr);
यंत्रlinkage दीर्घ sys_sched_getaffinity(pid_t pid, अचिन्हित पूर्णांक len,
					अचिन्हित दीर्घ __user *user_mask_ptr);
यंत्रlinkage दीर्घ sys_sched_yield(व्योम);
यंत्रlinkage दीर्घ sys_sched_get_priority_max(पूर्णांक policy);
यंत्रlinkage दीर्घ sys_sched_get_priority_min(पूर्णांक policy);
यंत्रlinkage दीर्घ sys_sched_rr_get_पूर्णांकerval(pid_t pid,
				काष्ठा __kernel_बारpec __user *पूर्णांकerval);
यंत्रlinkage दीर्घ sys_sched_rr_get_पूर्णांकerval_समय32(pid_t pid,
						 काष्ठा old_बारpec32 __user *पूर्णांकerval);

/* kernel/संकेत.c */
यंत्रlinkage दीर्घ sys_restart_syscall(व्योम);
यंत्रlinkage दीर्घ sys_समाप्त(pid_t pid, पूर्णांक sig);
यंत्रlinkage दीर्घ sys_tसमाप्त(pid_t pid, पूर्णांक sig);
यंत्रlinkage दीर्घ sys_tgसमाप्त(pid_t tgid, pid_t pid, पूर्णांक sig);
यंत्रlinkage दीर्घ sys_sigaltstack(स्थिर काष्ठा sigaltstack __user *uss,
				काष्ठा sigaltstack __user *uoss);
यंत्रlinkage दीर्घ sys_rt_संक_रोको(sigset_t __user *unewset, माप_प्रकार sigsetsize);
#अगर_अघोषित CONFIG_ODD_RT_SIGACTION
यंत्रlinkage दीर्घ sys_rt_sigaction(पूर्णांक,
				 स्थिर काष्ठा sigaction __user *,
				 काष्ठा sigaction __user *,
				 माप_प्रकार);
#पूर्ण_अगर
यंत्रlinkage दीर्घ sys_rt_sigprocmask(पूर्णांक how, sigset_t __user *set,
				sigset_t __user *oset, माप_प्रकार sigsetsize);
यंत्रlinkage दीर्घ sys_rt_संक_बाकी(sigset_t __user *set, माप_प्रकार sigsetsize);
यंत्रlinkage दीर्घ sys_rt_sigसमयdरुको(स्थिर sigset_t __user *uthese,
				siginfo_t __user *uinfo,
				स्थिर काष्ठा __kernel_बारpec __user *uts,
				माप_प्रकार sigsetsize);
यंत्रlinkage दीर्घ sys_rt_sigसमयdरुको_समय32(स्थिर sigset_t __user *uthese,
				siginfo_t __user *uinfo,
				स्थिर काष्ठा old_बारpec32 __user *uts,
				माप_प्रकार sigsetsize);
यंत्रlinkage दीर्घ sys_rt_sigqueueinfo(pid_t pid, पूर्णांक sig, siginfo_t __user *uinfo);

/* kernel/sys.c */
यंत्रlinkage दीर्घ sys_setpriority(पूर्णांक which, पूर्णांक who, पूर्णांक niceval);
यंत्रlinkage दीर्घ sys_getpriority(पूर्णांक which, पूर्णांक who);
यंत्रlinkage दीर्घ sys_reboot(पूर्णांक magic1, पूर्णांक magic2, अचिन्हित पूर्णांक cmd,
				व्योम __user *arg);
यंत्रlinkage दीर्घ sys_setregid(gid_t rgid, gid_t egid);
यंत्रlinkage दीर्घ sys_setgid(gid_t gid);
यंत्रlinkage दीर्घ sys_setreuid(uid_t ruid, uid_t euid);
यंत्रlinkage दीर्घ sys_setuid(uid_t uid);
यंत्रlinkage दीर्घ sys_setresuid(uid_t ruid, uid_t euid, uid_t suid);
यंत्रlinkage दीर्घ sys_getresuid(uid_t __user *ruid, uid_t __user *euid, uid_t __user *suid);
यंत्रlinkage दीर्घ sys_setresgid(gid_t rgid, gid_t egid, gid_t sgid);
यंत्रlinkage दीर्घ sys_getresgid(gid_t __user *rgid, gid_t __user *egid, gid_t __user *sgid);
यंत्रlinkage दीर्घ sys_setfsuid(uid_t uid);
यंत्रlinkage दीर्घ sys_setfsgid(gid_t gid);
यंत्रlinkage दीर्घ sys_बार(काष्ठा पंचांगs __user *tbuf);
यंत्रlinkage दीर्घ sys_setpgid(pid_t pid, pid_t pgid);
यंत्रlinkage दीर्घ sys_getpgid(pid_t pid);
यंत्रlinkage दीर्घ sys_माला_लोid(pid_t pid);
यंत्रlinkage दीर्घ sys_setsid(व्योम);
यंत्रlinkage दीर्घ sys_getgroups(पूर्णांक gidsetsize, gid_t __user *grouplist);
यंत्रlinkage दीर्घ sys_setgroups(पूर्णांक gidsetsize, gid_t __user *grouplist);
यंत्रlinkage दीर्घ sys_newuname(काष्ठा new_utsname __user *name);
यंत्रlinkage दीर्घ sys_sethostname(अक्षर __user *name, पूर्णांक len);
यंत्रlinkage दीर्घ sys_setकरोमुख्यname(अक्षर __user *name, पूर्णांक len);
यंत्रlinkage दीर्घ sys_getrlimit(अचिन्हित पूर्णांक resource,
				काष्ठा rlimit __user *rlim);
यंत्रlinkage दीर्घ sys_setrlimit(अचिन्हित पूर्णांक resource,
				काष्ठा rlimit __user *rlim);
यंत्रlinkage दीर्घ sys_getrusage(पूर्णांक who, काष्ठा rusage __user *ru);
यंत्रlinkage दीर्घ sys_umask(पूर्णांक mask);
यंत्रlinkage दीर्घ sys_prctl(पूर्णांक option, अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ arg3,
			अचिन्हित दीर्घ arg4, अचिन्हित दीर्घ arg5);
यंत्रlinkage दीर्घ sys_अ_लोpu(अचिन्हित __user *cpu, अचिन्हित __user *node, काष्ठा अ_लोpu_cache __user *cache);

/* kernel/समय.c */
यंत्रlinkage दीर्घ sys_समय_लोofday(काष्ठा __kernel_old_समयval __user *tv,
				काष्ठा समयzone __user *tz);
यंत्रlinkage दीर्घ sys_समय_रखोofday(काष्ठा __kernel_old_समयval __user *tv,
				काष्ठा समयzone __user *tz);
यंत्रlinkage दीर्घ sys_adjसमयx(काष्ठा __kernel_समयx __user *txc_p);
यंत्रlinkage दीर्घ sys_adjसमयx_समय32(काष्ठा old_समयx32 __user *txc_p);

/* kernel/sys.c */
यंत्रlinkage दीर्घ sys_getpid(व्योम);
यंत्रlinkage दीर्घ sys_getppid(व्योम);
यंत्रlinkage दीर्घ sys_getuid(व्योम);
यंत्रlinkage दीर्घ sys_geteuid(व्योम);
यंत्रlinkage दीर्घ sys_getgid(व्योम);
यंत्रlinkage दीर्घ sys_getegid(व्योम);
यंत्रlinkage दीर्घ sys_gettid(व्योम);
यंत्रlinkage दीर्घ sys_sysinfo(काष्ठा sysinfo __user *info);

/* ipc/mqueue.c */
यंत्रlinkage दीर्घ sys_mq_खोलो(स्थिर अक्षर __user *name, पूर्णांक oflag, umode_t mode, काष्ठा mq_attr __user *attr);
यंत्रlinkage दीर्घ sys_mq_unlink(स्थिर अक्षर __user *name);
यंत्रlinkage दीर्घ sys_mq_समयdsend(mqd_t mqdes, स्थिर अक्षर __user *msg_ptr, माप_प्रकार msg_len, अचिन्हित पूर्णांक msg_prio, स्थिर काष्ठा __kernel_बारpec __user *असल_समयout);
यंत्रlinkage दीर्घ sys_mq_समयdreceive(mqd_t mqdes, अक्षर __user *msg_ptr, माप_प्रकार msg_len, अचिन्हित पूर्णांक __user *msg_prio, स्थिर काष्ठा __kernel_बारpec __user *असल_समयout);
यंत्रlinkage दीर्घ sys_mq_notअगरy(mqd_t mqdes, स्थिर काष्ठा sigevent __user *notअगरication);
यंत्रlinkage दीर्घ sys_mq_माला_लोetattr(mqd_t mqdes, स्थिर काष्ठा mq_attr __user *mqstat, काष्ठा mq_attr __user *omqstat);
यंत्रlinkage दीर्घ sys_mq_समयdreceive_समय32(mqd_t mqdes,
			अक्षर __user *u_msg_ptr,
			अचिन्हित पूर्णांक msg_len, अचिन्हित पूर्णांक __user *u_msg_prio,
			स्थिर काष्ठा old_बारpec32 __user *u_असल_समयout);
यंत्रlinkage दीर्घ sys_mq_समयdsend_समय32(mqd_t mqdes,
			स्थिर अक्षर __user *u_msg_ptr,
			अचिन्हित पूर्णांक msg_len, अचिन्हित पूर्णांक msg_prio,
			स्थिर काष्ठा old_बारpec32 __user *u_असल_समयout);

/* ipc/msg.c */
यंत्रlinkage दीर्घ sys_msgget(key_t key, पूर्णांक msgflg);
यंत्रlinkage दीर्घ sys_old_msgctl(पूर्णांक msqid, पूर्णांक cmd, काष्ठा msqid_ds __user *buf);
यंत्रlinkage दीर्घ sys_msgctl(पूर्णांक msqid, पूर्णांक cmd, काष्ठा msqid_ds __user *buf);
यंत्रlinkage दीर्घ sys_msgrcv(पूर्णांक msqid, काष्ठा msgbuf __user *msgp,
				माप_प्रकार msgsz, दीर्घ msgtyp, पूर्णांक msgflg);
यंत्रlinkage दीर्घ sys_msgsnd(पूर्णांक msqid, काष्ठा msgbuf __user *msgp,
				माप_प्रकार msgsz, पूर्णांक msgflg);

/* ipc/sem.c */
यंत्रlinkage दीर्घ sys_semget(key_t key, पूर्णांक nsems, पूर्णांक semflg);
यंत्रlinkage दीर्घ sys_semctl(पूर्णांक semid, पूर्णांक semnum, पूर्णांक cmd, अचिन्हित दीर्घ arg);
यंत्रlinkage दीर्घ sys_old_semctl(पूर्णांक semid, पूर्णांक semnum, पूर्णांक cmd, अचिन्हित दीर्घ arg);
यंत्रlinkage दीर्घ sys_semसमयकरोp(पूर्णांक semid, काष्ठा sembuf __user *sops,
				अचिन्हित nsops,
				स्थिर काष्ठा __kernel_बारpec __user *समयout);
यंत्रlinkage दीर्घ sys_semसमयकरोp_समय32(पूर्णांक semid, काष्ठा sembuf __user *sops,
				अचिन्हित nsops,
				स्थिर काष्ठा old_बारpec32 __user *समयout);
यंत्रlinkage दीर्घ sys_semop(पूर्णांक semid, काष्ठा sembuf __user *sops,
				अचिन्हित nsops);

/* ipc/shm.c */
यंत्रlinkage दीर्घ sys_shmget(key_t key, माप_प्रकार size, पूर्णांक flag);
यंत्रlinkage दीर्घ sys_old_shmctl(पूर्णांक shmid, पूर्णांक cmd, काष्ठा shmid_ds __user *buf);
यंत्रlinkage दीर्घ sys_shmctl(पूर्णांक shmid, पूर्णांक cmd, काष्ठा shmid_ds __user *buf);
यंत्रlinkage दीर्घ sys_shmat(पूर्णांक shmid, अक्षर __user *shmaddr, पूर्णांक shmflg);
यंत्रlinkage दीर्घ sys_shmdt(अक्षर __user *shmaddr);

/* net/socket.c */
यंत्रlinkage दीर्घ sys_socket(पूर्णांक, पूर्णांक, पूर्णांक);
यंत्रlinkage दीर्घ sys_socketpair(पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक __user *);
यंत्रlinkage दीर्घ sys_bind(पूर्णांक, काष्ठा sockaddr __user *, पूर्णांक);
यंत्रlinkage दीर्घ sys_listen(पूर्णांक, पूर्णांक);
यंत्रlinkage दीर्घ sys_accept(पूर्णांक, काष्ठा sockaddr __user *, पूर्णांक __user *);
यंत्रlinkage दीर्घ sys_connect(पूर्णांक, काष्ठा sockaddr __user *, पूर्णांक);
यंत्रlinkage दीर्घ sys_माला_लोockname(पूर्णांक, काष्ठा sockaddr __user *, पूर्णांक __user *);
यंत्रlinkage दीर्घ sys_getpeername(पूर्णांक, काष्ठा sockaddr __user *, पूर्णांक __user *);
यंत्रlinkage दीर्घ sys_sendto(पूर्णांक, व्योम __user *, माप_प्रकार, अचिन्हित,
				काष्ठा sockaddr __user *, पूर्णांक);
यंत्रlinkage दीर्घ sys_recvfrom(पूर्णांक, व्योम __user *, माप_प्रकार, अचिन्हित,
				काष्ठा sockaddr __user *, पूर्णांक __user *);
यंत्रlinkage दीर्घ sys_setsockopt(पूर्णांक fd, पूर्णांक level, पूर्णांक optname,
				अक्षर __user *optval, पूर्णांक optlen);
यंत्रlinkage दीर्घ sys_माला_लोockopt(पूर्णांक fd, पूर्णांक level, पूर्णांक optname,
				अक्षर __user *optval, पूर्णांक __user *optlen);
यंत्रlinkage दीर्घ sys_shutकरोwn(पूर्णांक, पूर्णांक);
यंत्रlinkage दीर्घ sys_sendmsg(पूर्णांक fd, काष्ठा user_msghdr __user *msg, अचिन्हित flags);
यंत्रlinkage दीर्घ sys_recvmsg(पूर्णांक fd, काष्ठा user_msghdr __user *msg, अचिन्हित flags);

/* mm/filemap.c */
यंत्रlinkage दीर्घ sys_पढ़ोahead(पूर्णांक fd, loff_t offset, माप_प्रकार count);

/* mm/nommu.c, also with MMU */
यंत्रlinkage दीर्घ sys_brk(अचिन्हित दीर्घ brk);
यंत्रlinkage दीर्घ sys_munmap(अचिन्हित दीर्घ addr, माप_प्रकार len);
यंत्रlinkage दीर्घ sys_mremap(अचिन्हित दीर्घ addr,
			   अचिन्हित दीर्घ old_len, अचिन्हित दीर्घ new_len,
			   अचिन्हित दीर्घ flags, अचिन्हित दीर्घ new_addr);

/* security/keys/keyctl.c */
यंत्रlinkage दीर्घ sys_add_key(स्थिर अक्षर __user *_type,
			    स्थिर अक्षर __user *_description,
			    स्थिर व्योम __user *_payload,
			    माप_प्रकार plen,
			    key_serial_t destringid);
यंत्रlinkage दीर्घ sys_request_key(स्थिर अक्षर __user *_type,
				स्थिर अक्षर __user *_description,
				स्थिर अक्षर __user *_callout_info,
				key_serial_t destringid);
यंत्रlinkage दीर्घ sys_keyctl(पूर्णांक cmd, अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ arg3,
			   अचिन्हित दीर्घ arg4, अचिन्हित दीर्घ arg5);

/* arch/example/kernel/sys_example.c */
#अगर_घोषित CONFIG_CLONE_BACKWARDS
यंत्रlinkage दीर्घ sys_clone(अचिन्हित दीर्घ, अचिन्हित दीर्घ, पूर्णांक __user *, अचिन्हित दीर्घ,
	       पूर्णांक __user *);
#अन्यथा
#अगर_घोषित CONFIG_CLONE_BACKWARDS3
यंत्रlinkage दीर्घ sys_clone(अचिन्हित दीर्घ, अचिन्हित दीर्घ, पूर्णांक, पूर्णांक __user *,
			  पूर्णांक __user *, अचिन्हित दीर्घ);
#अन्यथा
यंत्रlinkage दीर्घ sys_clone(अचिन्हित दीर्घ, अचिन्हित दीर्घ, पूर्णांक __user *,
	       पूर्णांक __user *, अचिन्हित दीर्घ);
#पूर्ण_अगर
#पूर्ण_अगर

यंत्रlinkage दीर्घ sys_clone3(काष्ठा clone_args __user *uargs, माप_प्रकार size);

यंत्रlinkage दीर्घ sys_execve(स्थिर अक्षर __user *filename,
		स्थिर अक्षर __user *स्थिर __user *argv,
		स्थिर अक्षर __user *स्थिर __user *envp);

/* mm/fadvise.c */
यंत्रlinkage दीर्घ sys_fadvise64_64(पूर्णांक fd, loff_t offset, loff_t len, पूर्णांक advice);

/* mm/, CONFIG_MMU only */
यंत्रlinkage दीर्घ sys_swapon(स्थिर अक्षर __user *specialfile, पूर्णांक swap_flags);
यंत्रlinkage दीर्घ sys_swapoff(स्थिर अक्षर __user *specialfile);
यंत्रlinkage दीर्घ sys_mprotect(अचिन्हित दीर्घ start, माप_प्रकार len,
				अचिन्हित दीर्घ prot);
यंत्रlinkage दीर्घ sys_msync(अचिन्हित दीर्घ start, माप_प्रकार len, पूर्णांक flags);
यंत्रlinkage दीर्घ sys_mlock(अचिन्हित दीर्घ start, माप_प्रकार len);
यंत्रlinkage दीर्घ sys_munlock(अचिन्हित दीर्घ start, माप_प्रकार len);
यंत्रlinkage दीर्घ sys_mlockall(पूर्णांक flags);
यंत्रlinkage दीर्घ sys_munlockall(व्योम);
यंत्रlinkage दीर्घ sys_mincore(अचिन्हित दीर्घ start, माप_प्रकार len,
				अचिन्हित अक्षर __user * vec);
यंत्रlinkage दीर्घ sys_madvise(अचिन्हित दीर्घ start, माप_प्रकार len, पूर्णांक behavior);
यंत्रlinkage दीर्घ sys_process_madvise(पूर्णांक pidfd, स्थिर काष्ठा iovec __user *vec,
			माप_प्रकार vlen, पूर्णांक behavior, अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_remap_file_pages(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
			अचिन्हित दीर्घ prot, अचिन्हित दीर्घ pgoff,
			अचिन्हित दीर्घ flags);
यंत्रlinkage दीर्घ sys_mbind(अचिन्हित दीर्घ start, अचिन्हित दीर्घ len,
				अचिन्हित दीर्घ mode,
				स्थिर अचिन्हित दीर्घ __user *nmask,
				अचिन्हित दीर्घ maxnode,
				अचिन्हित flags);
यंत्रlinkage दीर्घ sys_get_mempolicy(पूर्णांक __user *policy,
				अचिन्हित दीर्घ __user *nmask,
				अचिन्हित दीर्घ maxnode,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ flags);
यंत्रlinkage दीर्घ sys_set_mempolicy(पूर्णांक mode, स्थिर अचिन्हित दीर्घ __user *nmask,
				अचिन्हित दीर्घ maxnode);
यंत्रlinkage दीर्घ sys_migrate_pages(pid_t pid, अचिन्हित दीर्घ maxnode,
				स्थिर अचिन्हित दीर्घ __user *from,
				स्थिर अचिन्हित दीर्घ __user *to);
यंत्रlinkage दीर्घ sys_move_pages(pid_t pid, अचिन्हित दीर्घ nr_pages,
				स्थिर व्योम __user * __user *pages,
				स्थिर पूर्णांक __user *nodes,
				पूर्णांक __user *status,
				पूर्णांक flags);

यंत्रlinkage दीर्घ sys_rt_tgsigqueueinfo(pid_t tgid, pid_t  pid, पूर्णांक sig,
		siginfo_t __user *uinfo);
यंत्रlinkage दीर्घ sys_perf_event_खोलो(
		काष्ठा perf_event_attr __user *attr_uptr,
		pid_t pid, पूर्णांक cpu, पूर्णांक group_fd, अचिन्हित दीर्घ flags);
यंत्रlinkage दीर्घ sys_accept4(पूर्णांक, काष्ठा sockaddr __user *, पूर्णांक __user *, पूर्णांक);
यंत्रlinkage दीर्घ sys_recvmmsg(पूर्णांक fd, काष्ठा mmsghdr __user *msg,
			     अचिन्हित पूर्णांक vlen, अचिन्हित flags,
			     काष्ठा __kernel_बारpec __user *समयout);
यंत्रlinkage दीर्घ sys_recvmmsg_समय32(पूर्णांक fd, काष्ठा mmsghdr __user *msg,
			     अचिन्हित पूर्णांक vlen, अचिन्हित flags,
			     काष्ठा old_बारpec32 __user *समयout);

यंत्रlinkage दीर्घ sys_रुको4(pid_t pid, पूर्णांक __user *stat_addr,
				पूर्णांक options, काष्ठा rusage __user *ru);
यंत्रlinkage दीर्घ sys_prlimit64(pid_t pid, अचिन्हित पूर्णांक resource,
				स्थिर काष्ठा rlimit64 __user *new_rlim,
				काष्ठा rlimit64 __user *old_rlim);
यंत्रlinkage दीर्घ sys_fanotअगरy_init(अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक event_f_flags);
यंत्रlinkage दीर्घ sys_fanotअगरy_mark(पूर्णांक fanotअगरy_fd, अचिन्हित पूर्णांक flags,
				  u64 mask, पूर्णांक fd,
				  स्थिर अक्षर  __user *pathname);
यंत्रlinkage दीर्घ sys_name_to_handle_at(पूर्णांक dfd, स्थिर अक्षर __user *name,
				      काष्ठा file_handle __user *handle,
				      पूर्णांक __user *mnt_id, पूर्णांक flag);
यंत्रlinkage दीर्घ sys_खोलो_by_handle_at(पूर्णांक mountdirfd,
				      काष्ठा file_handle __user *handle,
				      पूर्णांक flags);
यंत्रlinkage दीर्घ sys_घड़ी_adjसमय(घड़ीid_t which_घड़ी,
				काष्ठा __kernel_समयx __user *tx);
यंत्रlinkage दीर्घ sys_घड़ी_adjसमय32(घड़ीid_t which_घड़ी,
				काष्ठा old_समयx32 __user *tx);
यंत्रlinkage दीर्घ sys_syncfs(पूर्णांक fd);
यंत्रlinkage दीर्घ sys_setns(पूर्णांक fd, पूर्णांक nstype);
यंत्रlinkage दीर्घ sys_pidfd_खोलो(pid_t pid, अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_sendmmsg(पूर्णांक fd, काष्ठा mmsghdr __user *msg,
			     अचिन्हित पूर्णांक vlen, अचिन्हित flags);
यंत्रlinkage दीर्घ sys_process_vm_पढ़ोv(pid_t pid,
				     स्थिर काष्ठा iovec __user *lvec,
				     अचिन्हित दीर्घ liovcnt,
				     स्थिर काष्ठा iovec __user *rvec,
				     अचिन्हित दीर्घ riovcnt,
				     अचिन्हित दीर्घ flags);
यंत्रlinkage दीर्घ sys_process_vm_ग_लिखोv(pid_t pid,
				      स्थिर काष्ठा iovec __user *lvec,
				      अचिन्हित दीर्घ liovcnt,
				      स्थिर काष्ठा iovec __user *rvec,
				      अचिन्हित दीर्घ riovcnt,
				      अचिन्हित दीर्घ flags);
यंत्रlinkage दीर्घ sys_kcmp(pid_t pid1, pid_t pid2, पूर्णांक type,
			 अचिन्हित दीर्घ idx1, अचिन्हित दीर्घ idx2);
यंत्रlinkage दीर्घ sys_finit_module(पूर्णांक fd, स्थिर अक्षर __user *uargs, पूर्णांक flags);
यंत्रlinkage दीर्घ sys_sched_setattr(pid_t pid,
					काष्ठा sched_attr __user *attr,
					अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_sched_getattr(pid_t pid,
					काष्ठा sched_attr __user *attr,
					अचिन्हित पूर्णांक size,
					अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_नामat2(पूर्णांक olddfd, स्थिर अक्षर __user *oldname,
			      पूर्णांक newdfd, स्थिर अक्षर __user *newname,
			      अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_seccomp(अचिन्हित पूर्णांक op, अचिन्हित पूर्णांक flags,
			    व्योम __user *uargs);
यंत्रlinkage दीर्घ sys_getअक्रमom(अक्षर __user *buf, माप_प्रकार count,
			      अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_memfd_create(स्थिर अक्षर __user *uname_ptr, अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_bpf(पूर्णांक cmd, जोड़ bpf_attr *attr, अचिन्हित पूर्णांक size);
यंत्रlinkage दीर्घ sys_execveat(पूर्णांक dfd, स्थिर अक्षर __user *filename,
			स्थिर अक्षर __user *स्थिर __user *argv,
			स्थिर अक्षर __user *स्थिर __user *envp, पूर्णांक flags);
यंत्रlinkage दीर्घ sys_userfaultfd(पूर्णांक flags);
यंत्रlinkage दीर्घ sys_membarrier(पूर्णांक cmd, अचिन्हित पूर्णांक flags, पूर्णांक cpu_id);
यंत्रlinkage दीर्घ sys_mlock2(अचिन्हित दीर्घ start, माप_प्रकार len, पूर्णांक flags);
यंत्रlinkage दीर्घ sys_copy_file_range(पूर्णांक fd_in, loff_t __user *off_in,
				    पूर्णांक fd_out, loff_t __user *off_out,
				    माप_प्रकार len, अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_pपढ़ोv2(अचिन्हित दीर्घ fd, स्थिर काष्ठा iovec __user *vec,
			    अचिन्हित दीर्घ vlen, अचिन्हित दीर्घ pos_l, अचिन्हित दीर्घ pos_h,
			    rwf_t flags);
यंत्रlinkage दीर्घ sys_pग_लिखोv2(अचिन्हित दीर्घ fd, स्थिर काष्ठा iovec __user *vec,
			    अचिन्हित दीर्घ vlen, अचिन्हित दीर्घ pos_l, अचिन्हित दीर्घ pos_h,
			    rwf_t flags);
यंत्रlinkage दीर्घ sys_pkey_mprotect(अचिन्हित दीर्घ start, माप_प्रकार len,
				  अचिन्हित दीर्घ prot, पूर्णांक pkey);
यंत्रlinkage दीर्घ sys_pkey_alloc(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ init_val);
यंत्रlinkage दीर्घ sys_pkey_मुक्त(पूर्णांक pkey);
यंत्रlinkage दीर्घ sys_statx(पूर्णांक dfd, स्थिर अक्षर __user *path, अचिन्हित flags,
			  अचिन्हित mask, काष्ठा statx __user *buffer);
यंत्रlinkage दीर्घ sys_rseq(काष्ठा rseq __user *rseq, uपूर्णांक32_t rseq_len,
			 पूर्णांक flags, uपूर्णांक32_t sig);
यंत्रlinkage दीर्घ sys_खोलो_tree(पूर्णांक dfd, स्थिर अक्षर __user *path, अचिन्हित flags);
यंत्रlinkage दीर्घ sys_move_mount(पूर्णांक from_dfd, स्थिर अक्षर __user *from_path,
			       पूर्णांक to_dfd, स्थिर अक्षर __user *to_path,
			       अचिन्हित पूर्णांक ms_flags);
यंत्रlinkage दीर्घ sys_mount_setattr(पूर्णांक dfd, स्थिर अक्षर __user *path,
				  अचिन्हित पूर्णांक flags,
				  काष्ठा mount_attr __user *uattr, माप_प्रकार usize);
यंत्रlinkage दीर्घ sys_fsखोलो(स्थिर अक्षर __user *fs_name, अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_fsconfig(पूर्णांक fs_fd, अचिन्हित पूर्णांक cmd, स्थिर अक्षर __user *key,
			     स्थिर व्योम __user *value, पूर्णांक aux);
यंत्रlinkage दीर्घ sys_fsmount(पूर्णांक fs_fd, अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक ms_flags);
यंत्रlinkage दीर्घ sys_fspick(पूर्णांक dfd, स्थिर अक्षर __user *path, अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_pidfd_send_संकेत(पूर्णांक pidfd, पूर्णांक sig,
				       siginfo_t __user *info,
				       अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_pidfd_getfd(पूर्णांक pidfd, पूर्णांक fd, अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ sys_landlock_create_ruleset(स्थिर काष्ठा landlock_ruleset_attr __user *attr,
		माप_प्रकार size, __u32 flags);
यंत्रlinkage दीर्घ sys_landlock_add_rule(पूर्णांक ruleset_fd, क्रमागत landlock_rule_type rule_type,
		स्थिर व्योम __user *rule_attr, __u32 flags);
यंत्रlinkage दीर्घ sys_landlock_restrict_self(पूर्णांक ruleset_fd, __u32 flags);

/*
 * Architecture-specअगरic प्रणाली calls
 */

/* arch/x86/kernel/ioport.c */
यंत्रlinkage दीर्घ sys_ioperm(अचिन्हित दीर्घ from, अचिन्हित दीर्घ num, पूर्णांक on);

/* pciconfig: alpha, arm, arm64, ia64, sparc */
यंत्रlinkage दीर्घ sys_pciconfig_पढ़ो(अचिन्हित दीर्घ bus, अचिन्हित दीर्घ dfn,
				अचिन्हित दीर्घ off, अचिन्हित दीर्घ len,
				व्योम __user *buf);
यंत्रlinkage दीर्घ sys_pciconfig_ग_लिखो(अचिन्हित दीर्घ bus, अचिन्हित दीर्घ dfn,
				अचिन्हित दीर्घ off, अचिन्हित दीर्घ len,
				व्योम __user *buf);
यंत्रlinkage दीर्घ sys_pciconfig_iobase(दीर्घ which, अचिन्हित दीर्घ bus, अचिन्हित दीर्घ devfn);

/* घातerpc */
यंत्रlinkage दीर्घ sys_spu_run(पूर्णांक fd, __u32 __user *unpc,
				 __u32 __user *ustatus);
यंत्रlinkage दीर्घ sys_spu_create(स्थिर अक्षर __user *name,
		अचिन्हित पूर्णांक flags, umode_t mode, पूर्णांक fd);


/*
 * Deprecated प्रणाली calls which are still defined in
 * include/uapi/यंत्र-generic/unistd.h and wanted by >= 1 arch
 */

/* __ARCH_WANT_SYSCALL_NO_AT */
यंत्रlinkage दीर्घ sys_खोलो(स्थिर अक्षर __user *filename,
				पूर्णांक flags, umode_t mode);
यंत्रlinkage दीर्घ sys_link(स्थिर अक्षर __user *oldname,
				स्थिर अक्षर __user *newname);
यंत्रlinkage दीर्घ sys_unlink(स्थिर अक्षर __user *pathname);
यंत्रlinkage दीर्घ sys_mknod(स्थिर अक्षर __user *filename, umode_t mode,
				अचिन्हित dev);
यंत्रlinkage दीर्घ sys_chmod(स्थिर अक्षर __user *filename, umode_t mode);
यंत्रlinkage दीर्घ sys_chown(स्थिर अक्षर __user *filename,
				uid_t user, gid_t group);
यंत्रlinkage दीर्घ sys_सूची_गढ़ो(स्थिर अक्षर __user *pathname, umode_t mode);
यंत्रlinkage दीर्घ sys_सूची_हटाओ(स्थिर अक्षर __user *pathname);
यंत्रlinkage दीर्घ sys_lchown(स्थिर अक्षर __user *filename,
				uid_t user, gid_t group);
यंत्रlinkage दीर्घ sys_access(स्थिर अक्षर __user *filename, पूर्णांक mode);
यंत्रlinkage दीर्घ sys_नाम(स्थिर अक्षर __user *oldname,
				स्थिर अक्षर __user *newname);
यंत्रlinkage दीर्घ sys_symlink(स्थिर अक्षर __user *old, स्थिर अक्षर __user *new);
#अगर defined(__ARCH_WANT_STAT64) || defined(__ARCH_WANT_COMPAT_STAT64)
यंत्रlinkage दीर्घ sys_stat64(स्थिर अक्षर __user *filename,
				काष्ठा stat64 __user *statbuf);
यंत्रlinkage दीर्घ sys_lstat64(स्थिर अक्षर __user *filename,
				काष्ठा stat64 __user *statbuf);
#पूर्ण_अगर

/* __ARCH_WANT_SYSCALL_NO_FLAGS */
यंत्रlinkage दीर्घ sys_pipe(पूर्णांक __user *fildes);
यंत्रlinkage दीर्घ sys_dup2(अचिन्हित पूर्णांक oldfd, अचिन्हित पूर्णांक newfd);
यंत्रlinkage दीर्घ sys_epoll_create(पूर्णांक size);
यंत्रlinkage दीर्घ sys_inotअगरy_init(व्योम);
यंत्रlinkage दीर्घ sys_eventfd(अचिन्हित पूर्णांक count);
यंत्रlinkage दीर्घ sys_संकेतfd(पूर्णांक ufd, sigset_t __user *user_mask, माप_प्रकार sizemask);

/* __ARCH_WANT_SYSCALL_OFF_T */
यंत्रlinkage दीर्घ sys_sendfile(पूर्णांक out_fd, पूर्णांक in_fd,
			     off_t __user *offset, माप_प्रकार count);
यंत्रlinkage दीर्घ sys_newstat(स्थिर अक्षर __user *filename,
				काष्ठा stat __user *statbuf);
यंत्रlinkage दीर्घ sys_newlstat(स्थिर अक्षर __user *filename,
				काष्ठा stat __user *statbuf);
यंत्रlinkage दीर्घ sys_fadvise64(पूर्णांक fd, loff_t offset, माप_प्रकार len, पूर्णांक advice);

/* __ARCH_WANT_SYSCALL_DEPRECATED */
यंत्रlinkage दीर्घ sys_alarm(अचिन्हित पूर्णांक seconds);
यंत्रlinkage दीर्घ sys_getpgrp(व्योम);
यंत्रlinkage दीर्घ sys_छोड़ो(व्योम);
यंत्रlinkage दीर्घ sys_समय(__kernel_old_समय_प्रकार __user *tloc);
यंत्रlinkage दीर्घ sys_समय32(old_समय32_t __user *tloc);
#अगर_घोषित __ARCH_WANT_SYS_UTIME
यंत्रlinkage दीर्घ sys_uसमय(अक्षर __user *filename,
				काष्ठा utimbuf __user *बार);
यंत्रlinkage दीर्घ sys_uबार(अक्षर __user *filename,
				काष्ठा __kernel_old_समयval __user *uबार);
यंत्रlinkage दीर्घ sys_fuबारat(पूर्णांक dfd, स्थिर अक्षर __user *filename,
			      काष्ठा __kernel_old_समयval __user *uबार);
#पूर्ण_अगर
यंत्रlinkage दीर्घ sys_fuबारat_समय32(अचिन्हित पूर्णांक dfd,
				     स्थिर अक्षर __user *filename,
				     काष्ठा old_समयval32 __user *t);
यंत्रlinkage दीर्घ sys_uसमय32(स्थिर अक्षर __user *filename,
				 काष्ठा old_utimbuf32 __user *t);
यंत्रlinkage दीर्घ sys_uबार_समय32(स्थिर अक्षर __user *filename,
				  काष्ठा old_समयval32 __user *t);
यंत्रlinkage दीर्घ sys_creat(स्थिर अक्षर __user *pathname, umode_t mode);
यंत्रlinkage दीर्घ sys_getdents(अचिन्हित पूर्णांक fd,
				काष्ठा linux_dirent __user *dirent,
				अचिन्हित पूर्णांक count);
यंत्रlinkage दीर्घ sys_select(पूर्णांक n, fd_set __user *inp, fd_set __user *outp,
			fd_set __user *exp, काष्ठा __kernel_old_समयval __user *tvp);
यंत्रlinkage दीर्घ sys_poll(काष्ठा pollfd __user *ufds, अचिन्हित पूर्णांक nfds,
				पूर्णांक समयout);
यंत्रlinkage दीर्घ sys_epoll_रुको(पूर्णांक epfd, काष्ठा epoll_event __user *events,
				पूर्णांक maxevents, पूर्णांक समयout);
यंत्रlinkage दीर्घ sys_ustat(अचिन्हित dev, काष्ठा ustat __user *ubuf);
यंत्रlinkage दीर्घ sys_vविभाजन(व्योम);
यंत्रlinkage दीर्घ sys_recv(पूर्णांक, व्योम __user *, माप_प्रकार, अचिन्हित);
यंत्रlinkage दीर्घ sys_send(पूर्णांक, व्योम __user *, माप_प्रकार, अचिन्हित);
यंत्रlinkage दीर्घ sys_bdflush(पूर्णांक func, दीर्घ data);
यंत्रlinkage दीर्घ sys_oldumount(अक्षर __user *name);
यंत्रlinkage दीर्घ sys_uselib(स्थिर अक्षर __user *library);
यंत्रlinkage दीर्घ sys_sysfs(पूर्णांक option,
				अचिन्हित दीर्घ arg1, अचिन्हित दीर्घ arg2);
यंत्रlinkage दीर्घ sys_विभाजन(व्योम);

/* obsolete: kernel/समय/समय.c */
यंत्रlinkage दीर्घ sys_sसमय(__kernel_old_समय_प्रकार __user *tptr);
यंत्रlinkage दीर्घ sys_sसमय32(old_समय32_t __user *tptr);

/* obsolete: kernel/संकेत.c */
यंत्रlinkage दीर्घ sys_संक_बाकी(old_sigset_t __user *uset);
यंत्रlinkage दीर्घ sys_sigprocmask(पूर्णांक how, old_sigset_t __user *set,
				old_sigset_t __user *oset);
#अगर_घोषित CONFIG_OLD_SIGSUSPEND
यंत्रlinkage दीर्घ sys_संक_रोको(old_sigset_t mask);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OLD_SIGSUSPEND3
यंत्रlinkage दीर्घ sys_संक_रोको(पूर्णांक unused1, पूर्णांक unused2, old_sigset_t mask);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OLD_SIGACTION
यंत्रlinkage दीर्घ sys_sigaction(पूर्णांक, स्थिर काष्ठा old_sigaction __user *,
				काष्ठा old_sigaction __user *);
#पूर्ण_अगर
यंत्रlinkage दीर्घ sys_sgeपंचांगask(व्योम);
यंत्रlinkage दीर्घ sys_sseपंचांगask(पूर्णांक newmask);
यंत्रlinkage दीर्घ sys_संकेत(पूर्णांक sig, __sighandler_t handler);

/* obsolete: kernel/sched/core.c */
यंत्रlinkage दीर्घ sys_nice(पूर्णांक increment);

/* obsolete: kernel/kexec_file.c */
यंत्रlinkage दीर्घ sys_kexec_file_load(पूर्णांक kernel_fd, पूर्णांक initrd_fd,
				    अचिन्हित दीर्घ cmdline_len,
				    स्थिर अक्षर __user *cmdline_ptr,
				    अचिन्हित दीर्घ flags);

/* obsolete: kernel/निकास.c */
यंत्रlinkage दीर्घ sys_रुकोpid(pid_t pid, पूर्णांक __user *stat_addr, पूर्णांक options);

/* obsolete: kernel/uid16.c */
#अगर_घोषित CONFIG_HAVE_UID16
यंत्रlinkage दीर्घ sys_chown16(स्थिर अक्षर __user *filename,
				old_uid_t user, old_gid_t group);
यंत्रlinkage दीर्घ sys_lchown16(स्थिर अक्षर __user *filename,
				old_uid_t user, old_gid_t group);
यंत्रlinkage दीर्घ sys_fchown16(अचिन्हित पूर्णांक fd, old_uid_t user, old_gid_t group);
यंत्रlinkage दीर्घ sys_setregid16(old_gid_t rgid, old_gid_t egid);
यंत्रlinkage दीर्घ sys_setgid16(old_gid_t gid);
यंत्रlinkage दीर्घ sys_setreuid16(old_uid_t ruid, old_uid_t euid);
यंत्रlinkage दीर्घ sys_setuid16(old_uid_t uid);
यंत्रlinkage दीर्घ sys_setresuid16(old_uid_t ruid, old_uid_t euid, old_uid_t suid);
यंत्रlinkage दीर्घ sys_getresuid16(old_uid_t __user *ruid,
				old_uid_t __user *euid, old_uid_t __user *suid);
यंत्रlinkage दीर्घ sys_setresgid16(old_gid_t rgid, old_gid_t egid, old_gid_t sgid);
यंत्रlinkage दीर्घ sys_getresgid16(old_gid_t __user *rgid,
				old_gid_t __user *egid, old_gid_t __user *sgid);
यंत्रlinkage दीर्घ sys_setfsuid16(old_uid_t uid);
यंत्रlinkage दीर्घ sys_setfsgid16(old_gid_t gid);
यंत्रlinkage दीर्घ sys_getgroups16(पूर्णांक gidsetsize, old_gid_t __user *grouplist);
यंत्रlinkage दीर्घ sys_setgroups16(पूर्णांक gidsetsize, old_gid_t __user *grouplist);
यंत्रlinkage दीर्घ sys_getuid16(व्योम);
यंत्रlinkage दीर्घ sys_geteuid16(व्योम);
यंत्रlinkage दीर्घ sys_getgid16(व्योम);
यंत्रlinkage दीर्घ sys_getegid16(व्योम);
#पूर्ण_अगर

/* obsolete: net/socket.c */
यंत्रlinkage दीर्घ sys_socketcall(पूर्णांक call, अचिन्हित दीर्घ __user *args);

/* obsolete: fs/stat.c */
यंत्रlinkage दीर्घ sys_stat(स्थिर अक्षर __user *filename,
			काष्ठा __old_kernel_stat __user *statbuf);
यंत्रlinkage दीर्घ sys_lstat(स्थिर अक्षर __user *filename,
			काष्ठा __old_kernel_stat __user *statbuf);
यंत्रlinkage दीर्घ sys_ख_स्थिति(अचिन्हित पूर्णांक fd,
			काष्ठा __old_kernel_stat __user *statbuf);
यंत्रlinkage दीर्घ sys_पढ़ोlink(स्थिर अक्षर __user *path,
				अक्षर __user *buf, पूर्णांक bufsiz);

/* obsolete: fs/select.c */
यंत्रlinkage दीर्घ sys_old_select(काष्ठा sel_arg_काष्ठा __user *arg);

/* obsolete: fs/सूची_पढ़ो.c */
यंत्रlinkage दीर्घ sys_old_सूची_पढ़ो(अचिन्हित पूर्णांक, काष्ठा old_linux_dirent __user *, अचिन्हित पूर्णांक);

/* obsolete: kernel/sys.c */
यंत्रlinkage दीर्घ sys_gethostname(अक्षर __user *name, पूर्णांक len);
यंत्रlinkage दीर्घ sys_uname(काष्ठा old_utsname __user *);
यंत्रlinkage दीर्घ sys_olduname(काष्ठा olकरोld_utsname __user *);
#अगर_घोषित __ARCH_WANT_SYS_OLD_GETRLIMIT
यंत्रlinkage दीर्घ sys_old_getrlimit(अचिन्हित पूर्णांक resource, काष्ठा rlimit __user *rlim);
#पूर्ण_अगर

/* obsolete: ipc */
यंत्रlinkage दीर्घ sys_ipc(अचिन्हित पूर्णांक call, पूर्णांक first, अचिन्हित दीर्घ second,
		अचिन्हित दीर्घ third, व्योम __user *ptr, दीर्घ fअगरth);

/* obsolete: mm/ */
यंत्रlinkage दीर्घ sys_mmap_pgoff(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
			अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
			अचिन्हित दीर्घ fd, अचिन्हित दीर्घ pgoff);
यंत्रlinkage दीर्घ sys_old_mmap(काष्ठा mmap_arg_काष्ठा __user *arg);


/*
 * Not a real प्रणाली call, but a placeholder क्रम syscalls which are
 * not implemented -- see kernel/sys_ni.c
 */
यंत्रlinkage दीर्घ sys_ni_syscall(व्योम);

#पूर्ण_अगर /* CONFIG_ARCH_HAS_SYSCALL_WRAPPER */


/*
 * Kernel code should not call syscalls (i.e., sys_xyzyyz()) directly.
 * Instead, use one of the functions which work equivalently, such as
 * the ksys_xyzyyz() functions prototyped below.
 */
sमाप_प्रकार ksys_ग_लिखो(अचिन्हित पूर्णांक fd, स्थिर अक्षर __user *buf, माप_प्रकार count);
पूर्णांक ksys_fchown(अचिन्हित पूर्णांक fd, uid_t user, gid_t group);
sमाप_प्रकार ksys_पढ़ो(अचिन्हित पूर्णांक fd, अक्षर __user *buf, माप_प्रकार count);
व्योम ksys_sync(व्योम);
पूर्णांक ksys_unshare(अचिन्हित दीर्घ unshare_flags);
पूर्णांक ksys_setsid(व्योम);
पूर्णांक ksys_sync_file_range(पूर्णांक fd, loff_t offset, loff_t nbytes,
			 अचिन्हित पूर्णांक flags);
sमाप_प्रकार ksys_pपढ़ो64(अचिन्हित पूर्णांक fd, अक्षर __user *buf, माप_प्रकार count,
		     loff_t pos);
sमाप_प्रकार ksys_pग_लिखो64(अचिन्हित पूर्णांक fd, स्थिर अक्षर __user *buf,
		      माप_प्रकार count, loff_t pos);
पूर्णांक ksys_fallocate(पूर्णांक fd, पूर्णांक mode, loff_t offset, loff_t len);
#अगर_घोषित CONFIG_ADVISE_SYSCALLS
पूर्णांक ksys_fadvise64_64(पूर्णांक fd, loff_t offset, loff_t len, पूर्णांक advice);
#अन्यथा
अटल अंतरभूत पूर्णांक ksys_fadvise64_64(पूर्णांक fd, loff_t offset, loff_t len,
				    पूर्णांक advice)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर
अचिन्हित दीर्घ ksys_mmap_pgoff(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
			      अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
			      अचिन्हित दीर्घ fd, अचिन्हित दीर्घ pgoff);
sमाप_प्रकार ksys_पढ़ोahead(पूर्णांक fd, loff_t offset, माप_प्रकार count);
पूर्णांक ksys_ipc(अचिन्हित पूर्णांक call, पूर्णांक first, अचिन्हित दीर्घ second,
	अचिन्हित दीर्घ third, व्योम __user * ptr, दीर्घ fअगरth);
पूर्णांक compat_ksys_ipc(u32 call, पूर्णांक first, पूर्णांक second,
	u32 third, u32 ptr, u32 fअगरth);

/*
 * The following kernel syscall equivalents are just wrappers to fs-पूर्णांकernal
 * functions. Thereक्रमe, provide stubs to be अंतरभूतd at the callsites.
 */
बाह्य पूर्णांक करो_fchownat(पूर्णांक dfd, स्थिर अक्षर __user *filename, uid_t user,
		       gid_t group, पूर्णांक flag);

अटल अंतरभूत दीर्घ ksys_chown(स्थिर अक्षर __user *filename, uid_t user,
			      gid_t group)
अणु
	वापस करो_fchownat(AT_FDCWD, filename, user, group, 0);
पूर्ण

अटल अंतरभूत दीर्घ ksys_lchown(स्थिर अक्षर __user *filename, uid_t user,
			       gid_t group)
अणु
	वापस करो_fchownat(AT_FDCWD, filename, user, group,
			     AT_SYMLINK_NOFOLLOW);
पूर्ण

बाह्य दीर्घ करो_sys_ftruncate(अचिन्हित पूर्णांक fd, loff_t length, पूर्णांक small);

अटल अंतरभूत दीर्घ ksys_ftruncate(अचिन्हित पूर्णांक fd, loff_t length)
अणु
	वापस करो_sys_ftruncate(fd, length, 1);
पूर्ण

बाह्य दीर्घ करो_sys_truncate(स्थिर अक्षर __user *pathname, loff_t length);

अटल अंतरभूत दीर्घ ksys_truncate(स्थिर अक्षर __user *pathname, loff_t length)
अणु
	वापस करो_sys_truncate(pathname, length);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ksys_personality(अचिन्हित पूर्णांक personality)
अणु
	अचिन्हित पूर्णांक old = current->personality;

	अगर (personality != 0xffffffff)
		set_personality(personality);

	वापस old;
पूर्ण

/* क्रम __ARCH_WANT_SYS_IPC */
दीर्घ ksys_semसमयकरोp(पूर्णांक semid, काष्ठा sembuf __user *tsops,
		     अचिन्हित पूर्णांक nsops,
		     स्थिर काष्ठा __kernel_बारpec __user *समयout);
दीर्घ ksys_semget(key_t key, पूर्णांक nsems, पूर्णांक semflg);
दीर्घ ksys_old_semctl(पूर्णांक semid, पूर्णांक semnum, पूर्णांक cmd, अचिन्हित दीर्घ arg);
दीर्घ ksys_msgget(key_t key, पूर्णांक msgflg);
दीर्घ ksys_old_msgctl(पूर्णांक msqid, पूर्णांक cmd, काष्ठा msqid_ds __user *buf);
दीर्घ ksys_msgrcv(पूर्णांक msqid, काष्ठा msgbuf __user *msgp, माप_प्रकार msgsz,
		 दीर्घ msgtyp, पूर्णांक msgflg);
दीर्घ ksys_msgsnd(पूर्णांक msqid, काष्ठा msgbuf __user *msgp, माप_प्रकार msgsz,
		 पूर्णांक msgflg);
दीर्घ ksys_shmget(key_t key, माप_प्रकार size, पूर्णांक shmflg);
दीर्घ ksys_shmdt(अक्षर __user *shmaddr);
दीर्घ ksys_old_shmctl(पूर्णांक shmid, पूर्णांक cmd, काष्ठा shmid_ds __user *buf);
दीर्घ compat_ksys_semसमयकरोp(पूर्णांक semid, काष्ठा sembuf __user *tsems,
			    अचिन्हित पूर्णांक nsops,
			    स्थिर काष्ठा old_बारpec32 __user *समयout);

पूर्णांक __sys_माला_लोockopt(पूर्णांक fd, पूर्णांक level, पूर्णांक optname, अक्षर __user *optval,
		पूर्णांक __user *optlen);
पूर्णांक __sys_setsockopt(पूर्णांक fd, पूर्णांक level, पूर्णांक optname, अक्षर __user *optval,
		पूर्णांक optlen);
#पूर्ण_अगर
