<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is generally used by user-level software, so you need to
 * be a little careful about namespace pollution etc.  Also, we cannot
 * assume GCC is being used.
 */

#अगर_अघोषित __SPARC_POSIX_TYPES_H
#घोषणा __SPARC_POSIX_TYPES_H

#अगर defined(__sparc__) && defined(__arch64__)
/* sparc 64 bit */

प्रकार अचिन्हित लघु 	       __kernel_old_uid_t;
प्रकार अचिन्हित लघु         __kernel_old_gid_t;
#घोषणा __kernel_old_uid_t __kernel_old_uid_t

/* Note this piece of asymmetry from the v9 ABI.  */
प्रकार पूर्णांक		       __kernel_suseconds_t;
#घोषणा __kernel_suseconds_t __kernel_suseconds_t

प्रकार दीर्घ		__kernel_दीर्घ_t;
प्रकार अचिन्हित दीर्घ	__kernel_uदीर्घ_t;
#घोषणा __kernel_दीर्घ_t __kernel_दीर्घ_t

काष्ठा __kernel_old_समयval अणु
	__kernel_दीर्घ_t tv_sec;
	__kernel_suseconds_t tv_usec;
पूर्ण;
#घोषणा __kernel_old_समयval __kernel_old_समयval

#अन्यथा
/* sparc 32 bit */

प्रकार अचिन्हित पूर्णांक           __kernel_माप_प्रकार;
प्रकार पूर्णांक                    __kernel_sमाप_प्रकार;
प्रकार दीर्घ पूर्णांक               __kernel_सूचक_भेद_प्रकार;
#घोषणा __kernel_माप_प्रकार __kernel_माप_प्रकार

प्रकार अचिन्हित लघु         __kernel_ipc_pid_t;
#घोषणा __kernel_ipc_pid_t __kernel_ipc_pid_t

प्रकार अचिन्हित लघु         __kernel_uid_t;
प्रकार अचिन्हित लघु         __kernel_gid_t;
#घोषणा __kernel_uid_t __kernel_uid_t

प्रकार अचिन्हित लघु         __kernel_mode_t;
#घोषणा __kernel_mode_t __kernel_mode_t

प्रकार दीर्घ                   __kernel_daddr_t;
#घोषणा __kernel_daddr_t __kernel_daddr_t

प्रकार अचिन्हित लघु	       __kernel_old_dev_t;
#घोषणा __kernel_old_dev_t __kernel_old_dev_t

#पूर्ण_अगर /* defined(__sparc__) && defined(__arch64__) */

#समावेश <यंत्र-generic/posix_types.h>

#पूर्ण_अगर /* __SPARC_POSIX_TYPES_H */
