<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  S390 version
 *
 */

#अगर_अघोषित __ARCH_S390_POSIX_TYPES_H
#घोषणा __ARCH_S390_POSIX_TYPES_H

/*
 * This file is generally used by user-level software, so you need to
 * be a little careful about namespace pollution etc.  Also, we cannot
 * assume GCC is being used.
 */

प्रकार अचिन्हित दीर्घ   __kernel_माप_प्रकार;
प्रकार दीर्घ            __kernel_sमाप_प्रकार;
#घोषणा __kernel_माप_प्रकार __kernel_माप_प्रकार

प्रकार अचिन्हित लघु	__kernel_old_dev_t;
#घोषणा __kernel_old_dev_t __kernel_old_dev_t

#अगर_घोषित __KERNEL__
प्रकार अचिन्हित लघु __kernel_old_uid_t;
प्रकार अचिन्हित लघु __kernel_old_gid_t;
#घोषणा __kernel_old_uid_t __kernel_old_uid_t
#पूर्ण_अगर

#अगर_अघोषित __s390x__

प्रकार अचिन्हित दीर्घ   __kernel_ino_t;
प्रकार अचिन्हित लघु  __kernel_mode_t;
प्रकार अचिन्हित लघु  __kernel_ipc_pid_t;
प्रकार अचिन्हित लघु  __kernel_uid_t;
प्रकार अचिन्हित लघु  __kernel_gid_t;
प्रकार पूर्णांक             __kernel_सूचक_भेद_प्रकार;

#अन्यथा /* __s390x__ */

प्रकार अचिन्हित पूर्णांक    __kernel_ino_t;
प्रकार अचिन्हित पूर्णांक    __kernel_mode_t;
प्रकार पूर्णांक             __kernel_ipc_pid_t;
प्रकार अचिन्हित पूर्णांक    __kernel_uid_t;
प्रकार अचिन्हित पूर्णांक    __kernel_gid_t;
प्रकार दीर्घ            __kernel_सूचक_भेद_प्रकार;
प्रकार अचिन्हित दीर्घ   __kernel_sigset_t;      /* at least 32 bits */

#पूर्ण_अगर /* __s390x__ */

#घोषणा __kernel_ino_t  __kernel_ino_t
#घोषणा __kernel_mode_t __kernel_mode_t
#घोषणा __kernel_ipc_pid_t __kernel_ipc_pid_t
#घोषणा __kernel_uid_t __kernel_uid_t
#घोषणा __kernel_gid_t __kernel_gid_t

#समावेश <यंत्र-generic/posix_types.h>

#पूर्ण_अगर
