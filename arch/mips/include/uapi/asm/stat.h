<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 1999, 2000 Ralf Baechle
 * Copyright (C) 2000 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_STAT_H
#घोषणा _ASM_STAT_H

#समावेश <linux/types.h>

#समावेश <यंत्र/sgidefs.h>

#अगर (_MIPS_SIM == _MIPS_SIM_ABI32) || (_MIPS_SIM == _MIPS_SIM_NABI32)

काष्ठा stat अणु
	अचिन्हित	st_dev;
	दीर्घ		st_pad1[3];		/* Reserved क्रम network id */
	ino_t		st_ino;
	mode_t		st_mode;
	__u32		st_nlink;
	uid_t		st_uid;
	gid_t		st_gid;
	अचिन्हित	st_rdev;
	दीर्घ		st_pad2[2];
	दीर्घ		st_size;
	दीर्घ		st_pad3;
	/*
	 * Actually this should be बारtruc_t st_aसमय, st_mसमय and st_स_समय
	 * but we करोn't have it under Linux.
	 */
	दीर्घ		st_aसमय;
	दीर्घ		st_aसमय_nsec;
	दीर्घ		st_mसमय;
	दीर्घ		st_mसमय_nsec;
	दीर्घ		st_स_समय;
	दीर्घ		st_स_समय_nsec;
	दीर्घ		st_blksize;
	दीर्घ		st_blocks;
	दीर्घ		st_pad4[14];
पूर्ण;

/*
 * This matches काष्ठा stat64 in glibc2.1, hence the असलolutely insane
 * amounts of padding around dev_t's.  The memory layout is the same as of
 * काष्ठा stat of the 64-bit kernel.
 */

काष्ठा stat64 अणु
	अचिन्हित दीर्घ	st_dev;
	अचिन्हित दीर्घ	st_pad0[3];	/* Reserved क्रम st_dev expansion  */

	अचिन्हित दीर्घ दीर्घ	st_ino;

	mode_t		st_mode;
	__u32		st_nlink;

	uid_t		st_uid;
	gid_t		st_gid;

	अचिन्हित दीर्घ	st_rdev;
	अचिन्हित दीर्घ	st_pad1[3];	/* Reserved क्रम st_rdev expansion  */

	दीर्घ दीर्घ	st_size;

	/*
	 * Actually this should be बारtruc_t st_aसमय, st_mसमय and st_स_समय
	 * but we करोn't have it under Linux.
	 */
	दीर्घ		st_aसमय;
	अचिन्हित दीर्घ	st_aसमय_nsec;	/* Reserved क्रम st_aसमय expansion  */

	दीर्घ		st_mसमय;
	अचिन्हित दीर्घ	st_mसमय_nsec;	/* Reserved क्रम st_mसमय expansion  */

	दीर्घ		st_स_समय;
	अचिन्हित दीर्घ	st_स_समय_nsec;	/* Reserved क्रम st_स_समय expansion  */

	अचिन्हित दीर्घ	st_blksize;
	अचिन्हित दीर्घ	st_pad2;

	दीर्घ दीर्घ	st_blocks;
पूर्ण;

#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#अगर _MIPS_SIM == _MIPS_SIM_ABI64

/* The memory layout is the same as of काष्ठा stat64 of the 32-bit kernel.  */
काष्ठा stat अणु
	अचिन्हित पूर्णांक		st_dev;
	अचिन्हित पूर्णांक		st_pad0[3]; /* Reserved क्रम st_dev expansion */

	अचिन्हित दीर्घ		st_ino;

	mode_t			st_mode;
	__u32			st_nlink;

	uid_t			st_uid;
	gid_t			st_gid;

	अचिन्हित पूर्णांक		st_rdev;
	अचिन्हित पूर्णांक		st_pad1[3]; /* Reserved क्रम st_rdev expansion */

	दीर्घ			st_size;

	/*
	 * Actually this should be बारtruc_t st_aसमय, st_mसमय and st_स_समय
	 * but we करोn't have it under Linux.
	 */
	अचिन्हित पूर्णांक		st_aसमय;
	अचिन्हित पूर्णांक		st_aसमय_nsec;

	अचिन्हित पूर्णांक		st_mसमय;
	अचिन्हित पूर्णांक		st_mसमय_nsec;

	अचिन्हित पूर्णांक		st_स_समय;
	अचिन्हित पूर्णांक		st_स_समय_nsec;

	अचिन्हित पूर्णांक		st_blksize;
	अचिन्हित पूर्णांक		st_pad2;

	अचिन्हित दीर्घ		st_blocks;
पूर्ण;

#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI64 */

#घोषणा STAT_HAVE_NSEC 1

#पूर्ण_अगर /* _ASM_STAT_H */
