<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __PARISC_MMAN_H__
#घोषणा __PARISC_MMAN_H__

#घोषणा PROT_READ	0x1		/* page can be पढ़ो */
#घोषणा PROT_WRITE	0x2		/* page can be written */
#घोषणा PROT_EXEC	0x4		/* page can be executed */
#घोषणा PROT_SEM	0x8		/* page may be used क्रम atomic ops */
#घोषणा PROT_NONE	0x0		/* page can not be accessed */
#घोषणा PROT_GROWSDOWN	0x01000000	/* mprotect flag: extend change to start of growsकरोwn vma */
#घोषणा PROT_GROWSUP	0x02000000	/* mprotect flag: extend change to end of growsup vma */

/* 0x01 - 0x03 are defined in linux/mman.h */
#घोषणा MAP_TYPE	0x2b		/* Mask क्रम type of mapping, includes bits 0x08 and 0x20 */
#घोषणा MAP_FIXED	0x04		/* Interpret addr exactly */
#घोषणा MAP_ANONYMOUS	0x10		/* करोn't use a file */

#घोषणा MAP_DENYWRITE	0x0800		/* ETXTBSY */
#घोषणा MAP_EXECUTABLE	0x1000		/* mark it as an executable */
#घोषणा MAP_LOCKED	0x2000		/* pages are locked */
#घोषणा MAP_NORESERVE	0x4000		/* करोn't check क्रम reservations */
#घोषणा MAP_GROWSDOWN	0x8000		/* stack-like segment */
#घोषणा MAP_POPULATE	0x10000		/* populate (prefault) pagetables */
#घोषणा MAP_NONBLOCK	0x20000		/* करो not block on IO */
#घोषणा MAP_STACK	0x40000		/* give out an address that is best suited क्रम process/thपढ़ो stacks */
#घोषणा MAP_HUGETLB	0x80000		/* create a huge page mapping */
#घोषणा MAP_FIXED_NOREPLACE 0x100000	/* MAP_FIXED which करोesn't unmap underlying mapping */
#घोषणा MAP_UNINITIALIZED 0		/* uninitialized anonymous mmap */

#घोषणा MS_SYNC		1		/* synchronous memory sync */
#घोषणा MS_ASYNC	2		/* sync memory asynchronously */
#घोषणा MS_INVALIDATE	4		/* invalidate the caches */

#घोषणा MCL_CURRENT	1		/* lock all current mappings */
#घोषणा MCL_FUTURE	2		/* lock all future mappings */
#घोषणा MCL_ONFAULT	4		/* lock all pages that are faulted in */

#घोषणा MLOCK_ONFAULT	0x01		/* Lock pages in range after they are faulted in, करो not prefault */

#घोषणा MADV_NORMAL     0               /* no further special treaपंचांगent */
#घोषणा MADV_RANDOM     1               /* expect अक्रमom page references */
#घोषणा MADV_SEQUENTIAL 2               /* expect sequential page references */
#घोषणा MADV_WILLNEED   3               /* will need these pages */
#घोषणा MADV_DONTNEED   4               /* करोn't need these pages */

/* common/generic parameters */
#घोषणा MADV_FREE	8		/* मुक्त pages only अगर memory pressure */
#घोषणा MADV_REMOVE	9		/* हटाओ these pages & resources */
#घोषणा MADV_DONTFORK	10		/* करोn't inherit across विभाजन */
#घोषणा MADV_DOFORK	11		/* करो inherit across विभाजन */

#घोषणा MADV_COLD	20		/* deactivate these pages */
#घोषणा MADV_PAGEOUT	21		/* reclaim these pages */

#घोषणा MADV_MERGEABLE   65		/* KSM may merge identical pages */
#घोषणा MADV_UNMERGEABLE 66		/* KSM may not merge identical pages */

#घोषणा MADV_HUGEPAGE	67		/* Worth backing with hugepages */
#घोषणा MADV_NOHUGEPAGE	68		/* Not worth backing with hugepages */

#घोषणा MADV_DONTDUMP   69		/* Explicity exclude from the core dump,
					   overrides the coredump filter bits */
#घोषणा MADV_DODUMP	70		/* Clear the MADV_NODUMP flag */

#घोषणा MADV_WIPEONFORK 71		/* Zero memory on विभाजन, child only */
#घोषणा MADV_KEEPONFORK 72		/* Unकरो MADV_WIPEONFORK */

#घोषणा MADV_HWPOISON     100		/* poison a page क्रम testing */
#घोषणा MADV_SOFT_OFFLINE 101		/* soft offline page क्रम testing */

/* compatibility flags */
#घोषणा MAP_खाता	0
#घोषणा MAP_VARIABLE	0

#घोषणा PKEY_DISABLE_ACCESS	0x1
#घोषणा PKEY_DISABLE_WRITE	0x2
#घोषणा PKEY_ACCESS_MASK	(PKEY_DISABLE_ACCESS |\
				 PKEY_DISABLE_WRITE)

#पूर्ण_अगर /* __PARISC_MMAN_H__ */
