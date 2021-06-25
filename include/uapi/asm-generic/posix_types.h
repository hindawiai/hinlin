<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_GENERIC_POSIX_TYPES_H
#घोषणा __ASM_GENERIC_POSIX_TYPES_H

#समावेश <यंत्र/bitsperदीर्घ.h>
/*
 * This file is generally used by user-level software, so you need to
 * be a little careful about namespace pollution etc.
 *
 * First the types that are often defined in dअगरferent ways across
 * architectures, so that you can override them.
 */

#अगर_अघोषित __kernel_दीर्घ_t
प्रकार दीर्घ		__kernel_दीर्घ_t;
प्रकार अचिन्हित दीर्घ	__kernel_uदीर्घ_t;
#पूर्ण_अगर

#अगर_अघोषित __kernel_ino_t
प्रकार __kernel_uदीर्घ_t __kernel_ino_t;
#पूर्ण_अगर

#अगर_अघोषित __kernel_mode_t
प्रकार अचिन्हित पूर्णांक	__kernel_mode_t;
#पूर्ण_अगर

#अगर_अघोषित __kernel_pid_t
प्रकार पूर्णांक		__kernel_pid_t;
#पूर्ण_अगर

#अगर_अघोषित __kernel_ipc_pid_t
प्रकार पूर्णांक		__kernel_ipc_pid_t;
#पूर्ण_अगर

#अगर_अघोषित __kernel_uid_t
प्रकार अचिन्हित पूर्णांक	__kernel_uid_t;
प्रकार अचिन्हित पूर्णांक	__kernel_gid_t;
#पूर्ण_अगर

#अगर_अघोषित __kernel_suseconds_t
प्रकार __kernel_दीर्घ_t		__kernel_suseconds_t;
#पूर्ण_अगर

#अगर_अघोषित __kernel_daddr_t
प्रकार पूर्णांक		__kernel_daddr_t;
#पूर्ण_अगर

#अगर_अघोषित __kernel_uid32_t
प्रकार अचिन्हित पूर्णांक	__kernel_uid32_t;
प्रकार अचिन्हित पूर्णांक	__kernel_gid32_t;
#पूर्ण_अगर

#अगर_अघोषित __kernel_old_uid_t
प्रकार __kernel_uid_t	__kernel_old_uid_t;
प्रकार __kernel_gid_t	__kernel_old_gid_t;
#पूर्ण_अगर

#अगर_अघोषित __kernel_old_dev_t
प्रकार अचिन्हित पूर्णांक	__kernel_old_dev_t;
#पूर्ण_अगर

/*
 * Most 32 bit architectures use "unsigned int" माप_प्रकार,
 * and all 64 bit architectures use "unsigned long" माप_प्रकार.
 */
#अगर_अघोषित __kernel_माप_प्रकार
#अगर __BITS_PER_LONG != 64
प्रकार अचिन्हित पूर्णांक	__kernel_माप_प्रकार;
प्रकार पूर्णांक		__kernel_sमाप_प्रकार;
प्रकार पूर्णांक		__kernel_सूचक_भेद_प्रकार;
#अन्यथा
प्रकार __kernel_uदीर्घ_t __kernel_माप_प्रकार;
प्रकार __kernel_दीर्घ_t	__kernel_sमाप_प्रकार;
प्रकार __kernel_दीर्घ_t	__kernel_सूचक_भेद_प्रकार;
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित __kernel_fsid_t
प्रकार काष्ठा अणु
	पूर्णांक	val[2];
पूर्ण __kernel_fsid_t;
#पूर्ण_अगर

/*
 * anything below here should be completely generic
 */
प्रकार __kernel_दीर्घ_t	__kernel_off_t;
प्रकार दीर्घ दीर्घ	__kernel_loff_t;
प्रकार __kernel_दीर्घ_t	__kernel_old_समय_प्रकार;
#अगर_अघोषित __KERNEL__
प्रकार __kernel_दीर्घ_t	__kernel_समय_प्रकार;
#पूर्ण_अगर
प्रकार दीर्घ दीर्घ __kernel_समय64_t;
प्रकार __kernel_दीर्घ_t	__kernel_घड़ी_प्रकार;
प्रकार पूर्णांक		__kernel_समयr_t;
प्रकार पूर्णांक		__kernel_घड़ीid_t;
प्रकार अक्षर *		__kernel_caddr_t;
प्रकार अचिन्हित लघु	__kernel_uid16_t;
प्रकार अचिन्हित लघु	__kernel_gid16_t;

#पूर्ण_अगर /* __ASM_GENERIC_POSIX_TYPES_H */
