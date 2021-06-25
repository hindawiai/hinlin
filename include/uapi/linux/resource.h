<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_RESOURCE_H
#घोषणा _UAPI_LINUX_RESOURCE_H

#समावेश <linux/समय.स>
#समावेश <linux/types.h>

/*
 * Resource control/accounting header file क्रम linux
 */

/*
 * Definition of काष्ठा rusage taken from BSD 4.3 Reno
 * 
 * We करोn't support all of these yet, but we might as well have them....
 * Otherwise, each समय we add new items, programs which depend on this
 * काष्ठाure will lose.  This reduces the chances of that happening.
 */
#घोषणा	RUSAGE_SELF	0
#घोषणा	RUSAGE_CHILDREN	(-1)
#घोषणा RUSAGE_BOTH	(-2)		/* sys_रुको4() uses this */
#घोषणा	RUSAGE_THREAD	1		/* only the calling thपढ़ो */

काष्ठा	rusage अणु
	काष्ठा __kernel_old_समयval ru_uसमय;	/* user समय used */
	काष्ठा __kernel_old_समयval ru_sसमय;	/* प्रणाली समय used */
	__kernel_दीर्घ_t	ru_maxrss;	/* maximum resident set size */
	__kernel_दीर्घ_t	ru_ixrss;	/* पूर्णांकegral shared memory size */
	__kernel_दीर्घ_t	ru_idrss;	/* पूर्णांकegral unshared data size */
	__kernel_दीर्घ_t	ru_isrss;	/* पूर्णांकegral unshared stack size */
	__kernel_दीर्घ_t	ru_minflt;	/* page reclaims */
	__kernel_दीर्घ_t	ru_majflt;	/* page faults */
	__kernel_दीर्घ_t	ru_nswap;	/* swaps */
	__kernel_दीर्घ_t	ru_inblock;	/* block input operations */
	__kernel_दीर्घ_t	ru_oublock;	/* block output operations */
	__kernel_दीर्घ_t	ru_msgsnd;	/* messages sent */
	__kernel_दीर्घ_t	ru_msgrcv;	/* messages received */
	__kernel_दीर्घ_t	ru_nसंकेतs;	/* संकेतs received */
	__kernel_दीर्घ_t	ru_nvcsw;	/* voluntary context चयनes */
	__kernel_दीर्घ_t	ru_nivcsw;	/* involuntary " */
पूर्ण;

काष्ठा rlimit अणु
	__kernel_uदीर्घ_t	rlim_cur;
	__kernel_uदीर्घ_t	rlim_max;
पूर्ण;

#घोषणा RLIM64_अनन्त		(~0ULL)

काष्ठा rlimit64 अणु
	__u64 rlim_cur;
	__u64 rlim_max;
पूर्ण;

#घोषणा	PRIO_MIN	(-20)
#घोषणा	PRIO_MAX	20

#घोषणा	PRIO_PROCESS	0
#घोषणा	PRIO_PGRP	1
#घोषणा	PRIO_USER	2

/*
 * Limit the stack by to some sane शेष: root can always
 * increase this limit अगर needed..  8MB seems reasonable.
 */
#घोषणा _STK_LIM	(8*1024*1024)

/*
 * GPG2 wants 64kB of mlocked memory, to make sure pass phrases
 * and other sensitive inक्रमmation are never written to disk.
 */
#घोषणा MLOCK_LIMIT	((PAGE_SIZE > 64*1024) ? PAGE_SIZE : 64*1024)

/*
 * Due to binary compatibility, the actual resource numbers
 * may be dअगरferent क्रम dअगरferent linux versions..
 */
#समावेश <यंत्र/resource.h>


#पूर्ण_अगर /* _UAPI_LINUX_RESOURCE_H */
