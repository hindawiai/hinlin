<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 1999, 2002 by Ralf Baechle
 */
#अगर_अघोषित _ASM_MMAN_H
#घोषणा _ASM_MMAN_H

/*
 * Protections are chosen from these bits, OR'd together.  The
 * implementation करोes not necessarily support PROT_EXEC or PROT_WRITE
 * without PROT_READ.  The only guarantees are that no writing will be
 * allowed without PROT_WRITE and no access will be allowed क्रम PROT_NONE.
 */
#घोषणा PROT_NONE	0x00		/* page can not be accessed */
#घोषणा PROT_READ	0x01		/* page can be पढ़ो */
#घोषणा PROT_WRITE	0x02		/* page can be written */
#घोषणा PROT_EXEC	0x04		/* page can be executed */
/*			0x08		   reserved क्रम PROT_EXEC_NOFLUSH */
#घोषणा PROT_SEM	0x10		/* page may be used क्रम atomic ops */
#घोषणा PROT_GROWSDOWN	0x01000000	/* mprotect flag: extend change to start of growsकरोwn vma */
#घोषणा PROT_GROWSUP	0x02000000	/* mprotect flag: extend change to end of growsup vma */

/*
 * Flags क्रम mmap
 */
/* 0x01 - 0x03 are defined in linux/mman.h */
#घोषणा MAP_TYPE	0x00f		/* Mask क्रम type of mapping */
#घोषणा MAP_FIXED	0x010		/* Interpret addr exactly */

/* not used by linux, but here to make sure we करोn't clash with ABI defines */
#घोषणा MAP_RENAME	0x020		/* Assign page to file */
#घोषणा MAP_AUTOGROW	0x040		/* File may grow by writing */
#घोषणा MAP_LOCAL	0x080		/* Copy on विभाजन/sproc */
#घोषणा MAP_AUTORSRV	0x100		/* Logical swap reserved on demand */

/* These are linux-specअगरic */
#घोषणा MAP_NORESERVE	0x0400		/* करोn't check क्रम reservations */
#घोषणा MAP_ANONYMOUS	0x0800		/* करोn't use a file */
#घोषणा MAP_GROWSDOWN	0x1000		/* stack-like segment */
#घोषणा MAP_DENYWRITE	0x2000		/* ETXTBSY */
#घोषणा MAP_EXECUTABLE	0x4000		/* mark it as an executable */
#घोषणा MAP_LOCKED	0x8000		/* pages are locked */
#घोषणा MAP_POPULATE	0x10000		/* populate (prefault) pagetables */
#घोषणा MAP_NONBLOCK	0x20000		/* करो not block on IO */
#घोषणा MAP_STACK	0x40000		/* give out an address that is best suited क्रम process/thपढ़ो stacks */
#घोषणा MAP_HUGETLB	0x80000		/* create a huge page mapping */
#घोषणा MAP_FIXED_NOREPLACE 0x100000	/* MAP_FIXED which करोesn't unmap underlying mapping */

/*
 * Flags क्रम msync
 */
#घोषणा MS_ASYNC	0x0001		/* sync memory asynchronously */
#घोषणा MS_INVALIDATE	0x0002		/* invalidate mappings & caches */
#घोषणा MS_SYNC		0x0004		/* synchronous memory sync */

/*
 * Flags क्रम mlockall
 */
#घोषणा MCL_CURRENT	1		/* lock all current mappings */
#घोषणा MCL_FUTURE	2		/* lock all future mappings */
#घोषणा MCL_ONFAULT	4		/* lock all pages that are faulted in */

/*
 * Flags क्रम mlock
 */
#घोषणा MLOCK_ONFAULT	0x01		/* Lock pages in range after they are faulted in, करो not prefault */

#घोषणा MADV_NORMAL	0		/* no further special treaपंचांगent */
#घोषणा MADV_RANDOM	1		/* expect अक्रमom page references */
#घोषणा MADV_SEQUENTIAL 2		/* expect sequential page references */
#घोषणा MADV_WILLNEED	3		/* will need these pages */
#घोषणा MADV_DONTNEED	4		/* करोn't need these pages */

/* common parameters: try to keep these consistent across architectures */
#घोषणा MADV_FREE	8		/* मुक्त pages only अगर memory pressure */
#घोषणा MADV_REMOVE	9		/* हटाओ these pages & resources */
#घोषणा MADV_DONTFORK	10		/* करोn't inherit across विभाजन */
#घोषणा MADV_DOFORK	11		/* करो inherit across विभाजन */

#घोषणा MADV_MERGEABLE	 12		/* KSM may merge identical pages */
#घोषणा MADV_UNMERGEABLE 13		/* KSM may not merge identical pages */
#घोषणा MADV_HWPOISON	 100		/* poison a page क्रम testing */

#घोषणा MADV_HUGEPAGE	14		/* Worth backing with hugepages */
#घोषणा MADV_NOHUGEPAGE 15		/* Not worth backing with hugepages */

#घोषणा MADV_DONTDUMP	16		/* Explicity exclude from the core dump,
					   overrides the coredump filter bits */
#घोषणा MADV_DODUMP	17		/* Clear the MADV_NODUMP flag */

#घोषणा MADV_WIPEONFORK 18		/* Zero memory on विभाजन, child only */
#घोषणा MADV_KEEPONFORK 19		/* Unकरो MADV_WIPEONFORK */

#घोषणा MADV_COLD	20		/* deactivate these pages */
#घोषणा MADV_PAGEOUT	21		/* reclaim these pages */

/* compatibility flags */
#घोषणा MAP_खाता	0

#घोषणा PKEY_DISABLE_ACCESS	0x1
#घोषणा PKEY_DISABLE_WRITE	0x2
#घोषणा PKEY_ACCESS_MASK	(PKEY_DISABLE_ACCESS |\
				 PKEY_DISABLE_WRITE)

#पूर्ण_अगर /* _ASM_MMAN_H */
