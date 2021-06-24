<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_TIME_TYPES_H
#घोषणा _UAPI_LINUX_TIME_TYPES_H

#समावेश <linux/types.h>

काष्ठा __kernel_बारpec अणु
	__kernel_समय64_t       tv_sec;                 /* seconds */
	दीर्घ दीर्घ               tv_nsec;                /* nanoseconds */
पूर्ण;

काष्ठा __kernel_iसमयrspec अणु
	काष्ठा __kernel_बारpec it_पूर्णांकerval;    /* समयr period */
	काष्ठा __kernel_बारpec it_value;       /* समयr expiration */
पूर्ण;

/*
 * legacy समयval काष्ठाure, only embedded in काष्ठाures that
 * traditionally used 'timeval' to pass समय पूर्णांकervals (not असलolute
 * बार). Do not add new users. If user space fails to compile
 * here, this is probably because it is not y2038 safe and needs to
 * be changed to use another पूर्णांकerface.
 */
#अगर_अघोषित __kernel_old_समयval
काष्ठा __kernel_old_समयval अणु
	__kernel_दीर्घ_t tv_sec;
	__kernel_दीर्घ_t tv_usec;
पूर्ण;
#पूर्ण_अगर

काष्ठा __kernel_old_बारpec अणु
	__kernel_old_समय_प्रकार	tv_sec;		/* seconds */
	दीर्घ			tv_nsec;	/* nanoseconds */
पूर्ण;

काष्ठा __kernel_old_iसमयrval अणु
	काष्ठा __kernel_old_समयval it_पूर्णांकerval;/* समयr पूर्णांकerval */
	काष्ठा __kernel_old_समयval it_value;	/* current value */
पूर्ण;

काष्ठा __kernel_sock_समयval अणु
	__s64 tv_sec;
	__s64 tv_usec;
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_TIME_TYPES_H */
