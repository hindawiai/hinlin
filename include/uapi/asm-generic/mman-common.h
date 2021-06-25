<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_GENERIC_MMAN_COMMON_H
#घोषणा __ASM_GENERIC_MMAN_COMMON_H

/*
 Author: Michael S. Tsirkin <mst@mellanox.co.il>, Mellanox Technologies Ltd.
 Based on: यंत्र-xxx/mman.h
*/

#घोषणा PROT_READ	0x1		/* page can be पढ़ो */
#घोषणा PROT_WRITE	0x2		/* page can be written */
#घोषणा PROT_EXEC	0x4		/* page can be executed */
#घोषणा PROT_SEM	0x8		/* page may be used क्रम atomic ops */
/*			0x10		   reserved क्रम arch-specअगरic use */
/*			0x20		   reserved क्रम arch-specअगरic use */
#घोषणा PROT_NONE	0x0		/* page can not be accessed */
#घोषणा PROT_GROWSDOWN	0x01000000	/* mprotect flag: extend change to start of growsकरोwn vma */
#घोषणा PROT_GROWSUP	0x02000000	/* mprotect flag: extend change to end of growsup vma */

/* 0x01 - 0x03 are defined in linux/mman.h */
#घोषणा MAP_TYPE	0x0f		/* Mask क्रम type of mapping */
#घोषणा MAP_FIXED	0x10		/* Interpret addr exactly */
#घोषणा MAP_ANONYMOUS	0x20		/* करोn't use a file */

/* 0x0100 - 0x4000 flags are defined in यंत्र-generic/mman.h */
#घोषणा MAP_POPULATE		0x008000	/* populate (prefault) pagetables */
#घोषणा MAP_NONBLOCK		0x010000	/* करो not block on IO */
#घोषणा MAP_STACK		0x020000	/* give out an address that is best suited क्रम process/thपढ़ो stacks */
#घोषणा MAP_HUGETLB		0x040000	/* create a huge page mapping */
#घोषणा MAP_SYNC		0x080000 /* perक्रमm synchronous page faults क्रम the mapping */
#घोषणा MAP_FIXED_NOREPLACE	0x100000	/* MAP_FIXED which करोesn't unmap underlying mapping */

#घोषणा MAP_UNINITIALIZED 0x4000000	/* For anonymous mmap, memory could be
					 * uninitialized */

/*
 * Flags क्रम mlock
 */
#घोषणा MLOCK_ONFAULT	0x01		/* Lock pages in range after they are faulted in, करो not prefault */

#घोषणा MS_ASYNC	1		/* sync memory asynchronously */
#घोषणा MS_INVALIDATE	2		/* invalidate the caches */
#घोषणा MS_SYNC		4		/* synchronous memory sync */

#घोषणा MADV_NORMAL	0		/* no further special treaपंचांगent */
#घोषणा MADV_RANDOM	1		/* expect अक्रमom page references */
#घोषणा MADV_SEQUENTIAL	2		/* expect sequential page references */
#घोषणा MADV_WILLNEED	3		/* will need these pages */
#घोषणा MADV_DONTNEED	4		/* करोn't need these pages */

/* common parameters: try to keep these consistent across architectures */
#घोषणा MADV_FREE	8		/* मुक्त pages only अगर memory pressure */
#घोषणा MADV_REMOVE	9		/* हटाओ these pages & resources */
#घोषणा MADV_DONTFORK	10		/* करोn't inherit across विभाजन */
#घोषणा MADV_DOFORK	11		/* करो inherit across विभाजन */
#घोषणा MADV_HWPOISON	100		/* poison a page क्रम testing */
#घोषणा MADV_SOFT_OFFLINE 101		/* soft offline page क्रम testing */

#घोषणा MADV_MERGEABLE   12		/* KSM may merge identical pages */
#घोषणा MADV_UNMERGEABLE 13		/* KSM may not merge identical pages */

#घोषणा MADV_HUGEPAGE	14		/* Worth backing with hugepages */
#घोषणा MADV_NOHUGEPAGE	15		/* Not worth backing with hugepages */

#घोषणा MADV_DONTDUMP   16		/* Explicity exclude from the core dump,
					   overrides the coredump filter bits */
#घोषणा MADV_DODUMP	17		/* Clear the MADV_DONTDUMP flag */

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

#पूर्ण_अगर /* __ASM_GENERIC_MMAN_COMMON_H */
