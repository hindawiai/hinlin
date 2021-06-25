<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  include/linux/userfaultfd_k.h
 *
 *  Copyright (C) 2015  Red Hat, Inc.
 *
 */

#अगर_अघोषित _LINUX_USERFAULTFD_K_H
#घोषणा _LINUX_USERFAULTFD_K_H

#अगर_घोषित CONFIG_USERFAULTFD

#समावेश <linux/userfaultfd.h> /* linux/include/uapi/linux/userfaultfd.h */

#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र-generic/pgtable_uffd.h>

/* The set of all possible UFFD-related VM flags. */
#घोषणा __VM_UFFD_FLAGS (VM_UFFD_MISSING | VM_UFFD_WP | VM_UFFD_MINOR)

/*
 * CAREFUL: Check include/uapi/यंत्र-generic/fcntl.h when defining
 * new flags, since they might collide with O_* ones. We want
 * to re-use O_* flags that couldn't possibly have a meaning
 * from userfaultfd, in order to leave a मुक्त define-space क्रम
 * shared O_* flags.
 */
#घोषणा UFFD_CLOEXEC O_CLOEXEC
#घोषणा UFFD_NONBLOCK O_NONBLOCK

#घोषणा UFFD_SHARED_FCNTL_FLAGS (O_CLOEXEC | O_NONBLOCK)
#घोषणा UFFD_FLAGS_SET (EFD_SHARED_FCNTL_FLAGS)

बाह्य पूर्णांक sysctl_unprivileged_userfaultfd;

बाह्य vm_fault_t handle_userfault(काष्ठा vm_fault *vmf, अचिन्हित दीर्घ reason);

/*
 * The mode of operation क्रम __mcopy_atomic and its helpers.
 *
 * This is almost an implementation detail (mcopy_atomic below करोesn't take this
 * as a parameter), but it's exposed here because memory-kind-specअगरic
 * implementations (e.g. hugetlbfs) need to know the mode of operation.
 */
क्रमागत mcopy_atomic_mode अणु
	/* A normal copy_from_user पूर्णांकo the destination range. */
	MCOPY_ATOMIC_NORMAL,
	/* Don't copy; map the destination range to the zero page. */
	MCOPY_ATOMIC_ZEROPAGE,
	/* Just install pte(s) with the existing page(s) in the page cache. */
	MCOPY_ATOMIC_CONTINUE,
पूर्ण;

बाह्य sमाप_प्रकार mcopy_atomic(काष्ठा mm_काष्ठा *dst_mm, अचिन्हित दीर्घ dst_start,
			    अचिन्हित दीर्घ src_start, अचिन्हित दीर्घ len,
			    bool *mmap_changing, __u64 mode);
बाह्य sमाप_प्रकार mfill_zeropage(काष्ठा mm_काष्ठा *dst_mm,
			      अचिन्हित दीर्घ dst_start,
			      अचिन्हित दीर्घ len,
			      bool *mmap_changing);
बाह्य sमाप_प्रकार mcopy_जारी(काष्ठा mm_काष्ठा *dst_mm, अचिन्हित दीर्घ dst_start,
			      अचिन्हित दीर्घ len, bool *mmap_changing);
बाह्य पूर्णांक mग_लिखोprotect_range(काष्ठा mm_काष्ठा *dst_mm,
			       अचिन्हित दीर्घ start, अचिन्हित दीर्घ len,
			       bool enable_wp, bool *mmap_changing);

/* mm helpers */
अटल अंतरभूत bool is_mergeable_vm_userfaultfd_ctx(काष्ठा vm_area_काष्ठा *vma,
					काष्ठा vm_userfaultfd_ctx vm_ctx)
अणु
	वापस vma->vm_userfaultfd_ctx.ctx == vm_ctx.ctx;
पूर्ण

/*
 * Never enable huge pmd sharing on some uffd रेजिस्टरed vmas:
 *
 * - VM_UFFD_WP VMAs, because ग_लिखो protect inक्रमmation is per pgtable entry.
 *
 * - VM_UFFD_MINOR VMAs, because otherwise we would never get minor faults क्रम
 *   VMAs which share huge pmds. (If you have two mappings to the same
 *   underlying pages, and fault in the non-UFFD-रेजिस्टरed one with a ग_लिखो,
 *   with huge pmd sharing this would *also* setup the second UFFD-रेजिस्टरed
 *   mapping, and we'd not get minor faults.)
 */
अटल अंतरभूत bool uffd_disable_huge_pmd_share(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma->vm_flags & (VM_UFFD_WP | VM_UFFD_MINOR);
पूर्ण

अटल अंतरभूत bool userfaultfd_missing(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma->vm_flags & VM_UFFD_MISSING;
पूर्ण

अटल अंतरभूत bool userfaultfd_wp(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma->vm_flags & VM_UFFD_WP;
पूर्ण

अटल अंतरभूत bool userfaultfd_minor(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma->vm_flags & VM_UFFD_MINOR;
पूर्ण

अटल अंतरभूत bool userfaultfd_pte_wp(काष्ठा vm_area_काष्ठा *vma,
				      pte_t pte)
अणु
	वापस userfaultfd_wp(vma) && pte_uffd_wp(pte);
पूर्ण

अटल अंतरभूत bool userfaultfd_huge_pmd_wp(काष्ठा vm_area_काष्ठा *vma,
					   pmd_t pmd)
अणु
	वापस userfaultfd_wp(vma) && pmd_uffd_wp(pmd);
पूर्ण

अटल अंतरभूत bool userfaultfd_armed(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma->vm_flags & __VM_UFFD_FLAGS;
पूर्ण

बाह्य पूर्णांक dup_userfaultfd(काष्ठा vm_area_काष्ठा *, काष्ठा list_head *);
बाह्य व्योम dup_userfaultfd_complete(काष्ठा list_head *);

बाह्य व्योम mremap_userfaultfd_prep(काष्ठा vm_area_काष्ठा *,
				    काष्ठा vm_userfaultfd_ctx *);
बाह्य व्योम mremap_userfaultfd_complete(काष्ठा vm_userfaultfd_ctx *,
					अचिन्हित दीर्घ from, अचिन्हित दीर्घ to,
					अचिन्हित दीर्घ len);

बाह्य bool userfaultfd_हटाओ(काष्ठा vm_area_काष्ठा *vma,
			       अचिन्हित दीर्घ start,
			       अचिन्हित दीर्घ end);

बाह्य पूर्णांक userfaultfd_unmap_prep(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				  काष्ठा list_head *uf);
बाह्य व्योम userfaultfd_unmap_complete(काष्ठा mm_काष्ठा *mm,
				       काष्ठा list_head *uf);

#अन्यथा /* CONFIG_USERFAULTFD */

/* mm helpers */
अटल अंतरभूत vm_fault_t handle_userfault(काष्ठा vm_fault *vmf,
				अचिन्हित दीर्घ reason)
अणु
	वापस VM_FAULT_SIGBUS;
पूर्ण

अटल अंतरभूत bool is_mergeable_vm_userfaultfd_ctx(काष्ठा vm_area_काष्ठा *vma,
					काष्ठा vm_userfaultfd_ctx vm_ctx)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool userfaultfd_missing(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool userfaultfd_wp(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool userfaultfd_minor(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool userfaultfd_pte_wp(काष्ठा vm_area_काष्ठा *vma,
				      pte_t pte)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool userfaultfd_huge_pmd_wp(काष्ठा vm_area_काष्ठा *vma,
					   pmd_t pmd)
अणु
	वापस false;
पूर्ण


अटल अंतरभूत bool userfaultfd_armed(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक dup_userfaultfd(काष्ठा vm_area_काष्ठा *vma,
				  काष्ठा list_head *l)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dup_userfaultfd_complete(काष्ठा list_head *l)
अणु
पूर्ण

अटल अंतरभूत व्योम mremap_userfaultfd_prep(काष्ठा vm_area_काष्ठा *vma,
					   काष्ठा vm_userfaultfd_ctx *ctx)
अणु
पूर्ण

अटल अंतरभूत व्योम mremap_userfaultfd_complete(काष्ठा vm_userfaultfd_ctx *ctx,
					       अचिन्हित दीर्घ from,
					       अचिन्हित दीर्घ to,
					       अचिन्हित दीर्घ len)
अणु
पूर्ण

अटल अंतरभूत bool userfaultfd_हटाओ(काष्ठा vm_area_काष्ठा *vma,
				      अचिन्हित दीर्घ start,
				      अचिन्हित दीर्घ end)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक userfaultfd_unmap_prep(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
					 काष्ठा list_head *uf)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम userfaultfd_unmap_complete(काष्ठा mm_काष्ठा *mm,
					      काष्ठा list_head *uf)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_USERFAULTFD */

#पूर्ण_अगर /* _LINUX_USERFAULTFD_K_H */
