<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 1999 by Ralf Baechle
 */
#अगर_अघोषित _ASM_STATFS_H
#घोषणा _ASM_STATFS_H

#समावेश <linux/posix_types.h>
#समावेश <यंत्र/sgidefs.h>

#अगर_अघोषित __KERNEL_STRICT_NAMES

#समावेश <linux/types.h>

प्रकार __kernel_fsid_t	       fsid_t;

#पूर्ण_अगर

काष्ठा statfs अणु
	दीर्घ		f_type;
#घोषणा f_fstyp f_type
	दीर्घ		f_bsize;
	दीर्घ		f_frsize;	/* Fragment size - unsupported */
	दीर्घ		f_blocks;
	दीर्घ		f_bमुक्त;
	दीर्घ		f_files;
	दीर्घ		f_fमुक्त;
	दीर्घ		f_bavail;

	/* Linux specials */
	__kernel_fsid_t f_fsid;
	दीर्घ		f_namelen;
	दीर्घ		f_flags;
	दीर्घ		f_spare[5];
पूर्ण;

#अगर (_MIPS_SIM == _MIPS_SIM_ABI32) || (_MIPS_SIM == _MIPS_SIM_NABI32)

/*
 * Unlike the traditional version the LFAPI version has none of the ABI junk
 */
काष्ठा statfs64 अणु
	__u32	f_type;
	__u32	f_bsize;
	__u32	f_frsize;	/* Fragment size - unsupported */
	__u32	__pad;
	__u64	f_blocks;
	__u64	f_bमुक्त;
	__u64	f_files;
	__u64	f_fमुक्त;
	__u64	f_bavail;
	__kernel_fsid_t f_fsid;
	__u32	f_namelen;
	__u32	f_flags;
	__u32	f_spare[5];
पूर्ण;

#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#अगर _MIPS_SIM == _MIPS_SIM_ABI64

काष्ठा statfs64 अणु			/* Same as काष्ठा statfs */
	दीर्घ		f_type;
	दीर्घ		f_bsize;
	दीर्घ		f_frsize;	/* Fragment size - unsupported */
	दीर्घ		f_blocks;
	दीर्घ		f_bमुक्त;
	दीर्घ		f_files;
	दीर्घ		f_fमुक्त;
	दीर्घ		f_bavail;

	/* Linux specials */
	__kernel_fsid_t f_fsid;
	दीर्घ		f_namelen;
	दीर्घ		f_flags;
	दीर्घ		f_spare[5];
पूर्ण;

काष्ठा compat_statfs64 अणु
	__u32	f_type;
	__u32	f_bsize;
	__u32	f_frsize;	/* Fragment size - unsupported */
	__u32	__pad;
	__u64	f_blocks;
	__u64	f_bमुक्त;
	__u64	f_files;
	__u64	f_fमुक्त;
	__u64	f_bavail;
	__kernel_fsid_t f_fsid;
	__u32	f_namelen;
	__u32	f_flags;
	__u32	f_spare[5];
पूर्ण;

#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI64 */

#पूर्ण_अगर /* _ASM_STATFS_H */
