<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_TYPES_H
#घोषणा _UAPI_LINUX_TYPES_H

#समावेश <यंत्र/types.h>

#अगर_अघोषित __ASSEMBLY__
#अगर_अघोषित	__KERNEL__
#अगर_अघोषित __EXPORTED_HEADERS__
#warning "Attempt to use kernel headers from user space, see https://kernelnewbies.org/KernelHeaders"
#पूर्ण_अगर /* __EXPORTED_HEADERS__ */
#पूर्ण_अगर

#समावेश <linux/posix_types.h>


/*
 * Below are truly Linux-specअगरic types that should never collide with
 * any application/library that wants linux/types.h.
 */

#अगर_घोषित __CHECKER__
#घोषणा __bitwise__ __attribute__((bitwise))
#अन्यथा
#घोषणा __bitwise__
#पूर्ण_अगर
#घोषणा __bitwise __bitwise__

प्रकार __u16 __bitwise __le16;
प्रकार __u16 __bitwise __be16;
प्रकार __u32 __bitwise __le32;
प्रकार __u32 __bitwise __be32;
प्रकार __u64 __bitwise __le64;
प्रकार __u64 __bitwise __be64;

प्रकार __u16 __bitwise __sum16;
प्रकार __u32 __bitwise __wsum;

/*
 * aligned_u64 should be used in defining kernel<->userspace ABIs to aव्योम
 * common 32/64-bit compat problems.
 * 64-bit values align to 4-byte boundaries on x86_32 (and possibly other
 * architectures) and to 8-byte boundaries on 64-bit architectures.  The new
 * aligned_64 type enक्रमces 8-byte alignment so that काष्ठाs containing
 * aligned_64 values have the same alignment on 32-bit and 64-bit architectures.
 * No conversions are necessary between 32-bit user-space and a 64-bit kernel.
 */
#घोषणा __aligned_u64 __u64 __attribute__((aligned(8)))
#घोषणा __aligned_be64 __be64 __attribute__((aligned(8)))
#घोषणा __aligned_le64 __le64 __attribute__((aligned(8)))

प्रकार अचिन्हित __bitwise __poll_t;

#पूर्ण_अगर /*  __ASSEMBLY__ */
#पूर्ण_अगर /* _UAPI_LINUX_TYPES_H */
