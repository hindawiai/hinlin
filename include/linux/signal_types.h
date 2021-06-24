<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SIGNAL_TYPES_H
#घोषणा _LINUX_SIGNAL_TYPES_H

/*
 * Basic संकेत handling related data type definitions:
 */

#समावेश <linux/list.h>
#समावेश <uapi/linux/संकेत.स>

प्रकार काष्ठा kernel_siginfo अणु
	__SIGINFO;
पूर्ण kernel_siginfo_t;

/*
 * Real Time संकेतs may be queued.
 */

काष्ठा sigqueue अणु
	काष्ठा list_head list;
	पूर्णांक flags;
	kernel_siginfo_t info;
	काष्ठा user_काष्ठा *user;
पूर्ण;

/* flags values. */
#घोषणा SIGQUEUE_PREALLOC	1

काष्ठा संक_बाकी अणु
	काष्ठा list_head list;
	sigset_t संकेत;
पूर्ण;

काष्ठा sigaction अणु
#अगर_अघोषित __ARCH_HAS_IRIX_SIGACTION
	__sighandler_t	sa_handler;
	अचिन्हित दीर्घ	sa_flags;
#अन्यथा
	अचिन्हित पूर्णांक	sa_flags;
	__sighandler_t	sa_handler;
#पूर्ण_अगर
#अगर_घोषित __ARCH_HAS_SA_RESTORER
	__sigrestore_t sa_restorer;
#पूर्ण_अगर
	sigset_t	sa_mask;	/* mask last क्रम extensibility */
पूर्ण;

काष्ठा k_sigaction अणु
	काष्ठा sigaction sa;
#अगर_घोषित __ARCH_HAS_KA_RESTORER
	__sigrestore_t ka_restorer;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_OLD_SIGACTION
काष्ठा old_sigaction अणु
	__sighandler_t sa_handler;
	old_sigset_t sa_mask;
	अचिन्हित दीर्घ sa_flags;
	__sigrestore_t sa_restorer;
पूर्ण;
#पूर्ण_अगर

काष्ठा kसंकेत अणु
	काष्ठा k_sigaction ka;
	kernel_siginfo_t info;
	पूर्णांक sig;
पूर्ण;

#अगर_अघोषित __ARCH_UAPI_SA_FLAGS
#अगर_घोषित SA_RESTORER
#घोषणा __ARCH_UAPI_SA_FLAGS	SA_RESTORER
#अन्यथा
#घोषणा __ARCH_UAPI_SA_FLAGS	0
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा UAPI_SA_FLAGS                                                          \
	(SA_NOCLDSTOP | SA_NOCLDWAIT | SA_SIGINFO | SA_ONSTACK | SA_RESTART |  \
	 SA_NODEFER | SA_RESETHAND | SA_EXPOSE_TAGBITS | __ARCH_UAPI_SA_FLAGS)

#पूर्ण_अगर /* _LINUX_SIGNAL_TYPES_H */
