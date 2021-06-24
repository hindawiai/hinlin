<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ALPHA_MMAN_H__
#घोषणा __ALPHA_MMAN_H__

#घोषणा PROT_READ	0x1		/* page can be पढ़ो */
#घोषणा PROT_WRITE	0x2		/* page can be written */
#घोषणा PROT_EXEC	0x4		/* page can be executed */
#घोषणा PROT_SEM	0x8		/* page may be used क्रम atomic ops */
#घोषणा PROT_NONE	0x0		/* page can not be accessed */
#घोषणा PROT_GROWSDOWN	0x01000000	/* mprotect flag: extend change to start of growsकरोwn vma */
#घोषणा PROT_GROWSUP	0x02000000	/* mprotect flag: extend change to end of growsup vma */

/* 0x01 - 0x03 are defined in linux/mman.h */
#घोषणा MAP_TYPE	0x0f		/* Mask क्रम type of mapping (OSF/1 is _wrong_) */
#घोषणा MAP_FIXED	0x100		/* Interpret addr exactly */
#घोषणा MAP_ANONYMOUS	0x10		/* करोn't use a file */

/* not used by linux, but here to make sure we करोn't clash with OSF/1 defines */
#घोषणा _MAP_HASSEMAPHORE 0x0200
#घोषणा _MAP_INHERIT	0x0400
#घोषणा _MAP_UNALIGNED	0x0800

/* These are linux-specअगरic */
#घोषणा MAP_GROWSDOWN	0x01000		/* stack-like segment */
#घोषणा MAP_DENYWRITE	0x02000		/* ETXTBSY */
#घोषणा MAP_EXECUTABLE	0x04000		/* mark it as an executable */
#घोषणा MAP_LOCKED	0x08000		/* lock the mapping */
#घोषणा MAP_NORESERVE	0x10000		/* करोn't check क्रम reservations */
#घोषणा MAP_POPULATE	0x20000		/* populate (prefault) pagetables */
#घोषणा MAP_NONBLOCK	0x40000		/* करो not block on IO */
#घोषणा MAP_STACK	0x80000		/* give out an address that is best suited क्रम process/thपढ़ो stacks */
#घोषणा MAP_HUGETLB	0x100000	/* create a huge page mapping */
#घोषणा MAP_FIXED_NOREPLACE	0x200000/* MAP_FIXED which करोesn't unmap underlying mapping */

#घोषणा MS_ASYNC	1		/* sync memory asynchronously */
#घोषणा MS_SYNC		2		/* synchronous memory sync */
#घोषणा MS_INVALIDATE	4		/* invalidate the caches */

#घोषणा MCL_CURRENT	 8192		/* lock all currently mapped pages */
#घोषणा MCL_FUTURE	16384		/* lock all additions to address space */
#घोषणा MCL_ONFAULT	32768		/* lock all pages that are faulted in */

#घोषणा MLOCK_ONFAULT	0x01		/* Lock pages in range after they are faulted in, करो not prefault */

#घोषणा MADV_NORMAL	0		/* no further special treaपंचांगent */
#घोषणा MADV_RANDOM	1		/* expect अक्रमom page references */
#घोषणा MADV_SEQUENTIAL	2		/* expect sequential page references */
#घोषणा MADV_WILLNEED	3		/* will need these pages */
#घोषणा	MADV_SPACEAVAIL	5		/* ensure resources are available */
#घोषणा MADV_DONTNEED	6		/* करोn't need these pages */

/* common/generic parameters */
#घोषणा MADV_FREE	8		/* मुक्त pages only अगर memory pressure */
#घोषणा MADV_REMOVE	9		/* हटाओ these pages & resources */
#घोषणा MADV_DONTFORK	10		/* करोn't inherit across विभाजन */
#घोषणा MADV_DOFORK	11		/* करो inherit across विभाजन */

#घोषणा MADV_MERGEABLE   12		/* KSM may merge identical pages */
#घोषणा MADV_UNMERGEABLE 13		/* KSM may not merge identical pages */

#घोषणा MADV_HUGEPAGE	14		/* Worth backing with hugepages */
#घोषणा MADV_NOHUGEPAGE	15		/* Not worth backing with hugepages */

#घोषणा MADV_DONTDUMP   16		/* Explicity exclude from the core dump,
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

#पूर्ण_अगर /* __ALPHA_MMAN_H__ */
