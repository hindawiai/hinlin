<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_KSM_H
#घोषणा __LINUX_KSM_H
/*
 * Memory merging support.
 *
 * This code enables dynamic sharing of identical pages found in dअगरferent
 * memory areas, even अगर they are not shared by विभाजन().
 */

#समावेश <linux/bitops.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/rmap.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/coredump.h>

काष्ठा stable_node;
काष्ठा mem_cgroup;

#अगर_घोषित CONFIG_KSM
पूर्णांक ksm_madvise(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ end, पूर्णांक advice, अचिन्हित दीर्घ *vm_flags);
पूर्णांक __ksm_enter(काष्ठा mm_काष्ठा *mm);
व्योम __ksm_निकास(काष्ठा mm_काष्ठा *mm);

अटल अंतरभूत पूर्णांक ksm_विभाजन(काष्ठा mm_काष्ठा *mm, काष्ठा mm_काष्ठा *oldmm)
अणु
	अगर (test_bit(MMF_VM_MERGEABLE, &oldmm->flags))
		वापस __ksm_enter(mm);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ksm_निकास(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (test_bit(MMF_VM_MERGEABLE, &mm->flags))
		__ksm_निकास(mm);
पूर्ण

/*
 * When करो_swap_page() first faults in from swap what used to be a KSM page,
 * no problem, it will be asचिन्हित to this vma's anon_vma; but thereafter,
 * it might be faulted पूर्णांकo a dअगरferent anon_vma (or perhaps to a dअगरferent
 * offset in the same anon_vma).  करो_swap_page() cannot करो all the locking
 * needed to reस्थिरitute a cross-anon_vma KSM page: क्रम now it has to make
 * a copy, and leave remerging the pages to a later pass of ksmd.
 *
 * We'd like to make this conditional on vma->vm_flags & VM_MERGEABLE,
 * but what अगर the vma was unmerged जबतक the page was swapped out?
 */
काष्ठा page *ksm_might_need_to_copy(काष्ठा page *page,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address);

व्योम rmap_walk_ksm(काष्ठा page *page, काष्ठा rmap_walk_control *rwc);
व्योम ksm_migrate_page(काष्ठा page *newpage, काष्ठा page *oldpage);

#अन्यथा  /* !CONFIG_KSM */

अटल अंतरभूत पूर्णांक ksm_विभाजन(काष्ठा mm_काष्ठा *mm, काष्ठा mm_काष्ठा *oldmm)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ksm_निकास(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण

#अगर_घोषित CONFIG_MMU
अटल अंतरभूत पूर्णांक ksm_madvise(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ end, पूर्णांक advice, अचिन्हित दीर्घ *vm_flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा page *ksm_might_need_to_copy(काष्ठा page *page,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	वापस page;
पूर्ण

अटल अंतरभूत व्योम rmap_walk_ksm(काष्ठा page *page,
			काष्ठा rmap_walk_control *rwc)
अणु
पूर्ण

अटल अंतरभूत व्योम ksm_migrate_page(काष्ठा page *newpage, काष्ठा page *oldpage)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_MMU */
#पूर्ण_अगर /* !CONFIG_KSM */

#पूर्ण_अगर /* __LINUX_KSM_H */
