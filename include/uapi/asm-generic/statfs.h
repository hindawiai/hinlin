<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_GENERIC_STATFS_H
#घोषणा _UAPI_GENERIC_STATFS_H

#समावेश <linux/types.h>


/*
 * Most 64-bit platक्रमms use 'long', while most 32-bit platforms use '__u32'.
 * Yes, they dअगरfer in चिन्हितness as well as size.
 * Special हालs can override it क्रम themselves -- except क्रम S390x, which
 * is just a little too special क्रम us. And MIPS, which I'm not touching
 * with a 10' pole.
 */
#अगर_अघोषित __statfs_word
#अगर __BITS_PER_LONG == 64
#घोषणा __statfs_word __kernel_दीर्घ_t
#अन्यथा
#घोषणा __statfs_word __u32
#पूर्ण_अगर
#पूर्ण_अगर

काष्ठा statfs अणु
	__statfs_word f_type;
	__statfs_word f_bsize;
	__statfs_word f_blocks;
	__statfs_word f_bमुक्त;
	__statfs_word f_bavail;
	__statfs_word f_files;
	__statfs_word f_fमुक्त;
	__kernel_fsid_t f_fsid;
	__statfs_word f_namelen;
	__statfs_word f_frsize;
	__statfs_word f_flags;
	__statfs_word f_spare[4];
पूर्ण;

/*
 * ARM needs to aव्योम the 32-bit padding at the end, क्रम consistency
 * between EABI and OABI 
 */
#अगर_अघोषित ARCH_PACK_STATFS64
#घोषणा ARCH_PACK_STATFS64
#पूर्ण_अगर

काष्ठा statfs64 अणु
	__statfs_word f_type;
	__statfs_word f_bsize;
	__u64 f_blocks;
	__u64 f_bमुक्त;
	__u64 f_bavail;
	__u64 f_files;
	__u64 f_fमुक्त;
	__kernel_fsid_t f_fsid;
	__statfs_word f_namelen;
	__statfs_word f_frsize;
	__statfs_word f_flags;
	__statfs_word f_spare[4];
पूर्ण ARCH_PACK_STATFS64;

/* 
 * IA64 and x86_64 need to aव्योम the 32-bit padding at the end,
 * to be compatible with the i386 ABI
 */
#अगर_अघोषित ARCH_PACK_COMPAT_STATFS64
#घोषणा ARCH_PACK_COMPAT_STATFS64
#पूर्ण_अगर

काष्ठा compat_statfs64 अणु
	__u32 f_type;
	__u32 f_bsize;
	__u64 f_blocks;
	__u64 f_bमुक्त;
	__u64 f_bavail;
	__u64 f_files;
	__u64 f_fमुक्त;
	__kernel_fsid_t f_fsid;
	__u32 f_namelen;
	__u32 f_frsize;
	__u32 f_flags;
	__u32 f_spare[4];
पूर्ण ARCH_PACK_COMPAT_STATFS64;

#पूर्ण_अगर /* _UAPI_GENERIC_STATFS_H */
