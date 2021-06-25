<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_KHUGEPAGED_H
#घोषणा _LINUX_KHUGEPAGED_H

#समावेश <linux/sched/coredump.h> /* MMF_VM_HUGEPAGE */
#समावेश <linux/shmem_fs.h>


#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
बाह्य काष्ठा attribute_group khugepaged_attr_group;

बाह्य पूर्णांक khugepaged_init(व्योम);
बाह्य व्योम khugepaged_destroy(व्योम);
बाह्य पूर्णांक start_stop_khugepaged(व्योम);
बाह्य पूर्णांक __khugepaged_enter(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम __khugepaged_निकास(काष्ठा mm_काष्ठा *mm);
बाह्य पूर्णांक khugepaged_enter_vma_merge(काष्ठा vm_area_काष्ठा *vma,
				      अचिन्हित दीर्घ vm_flags);
बाह्य व्योम khugepaged_min_मुक्त_kbytes_update(व्योम);
#अगर_घोषित CONFIG_SHMEM
बाह्य व्योम collapse_pte_mapped_thp(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);
#अन्यथा
अटल अंतरभूत व्योम collapse_pte_mapped_thp(काष्ठा mm_काष्ठा *mm,
					   अचिन्हित दीर्घ addr)
अणु
पूर्ण
#पूर्ण_अगर

#घोषणा khugepaged_enabled()					       \
	(transparent_hugepage_flags &				       \
	 ((1<<TRANSPARENT_HUGEPAGE_FLAG) |		       \
	  (1<<TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG)))
#घोषणा khugepaged_always()				\
	(transparent_hugepage_flags &			\
	 (1<<TRANSPARENT_HUGEPAGE_FLAG))
#घोषणा khugepaged_req_madv()					\
	(transparent_hugepage_flags &				\
	 (1<<TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG))
#घोषणा khugepaged_defrag()					\
	(transparent_hugepage_flags &				\
	 (1<<TRANSPARENT_HUGEPAGE_DEFRAG_KHUGEPAGED_FLAG))

अटल अंतरभूत पूर्णांक khugepaged_विभाजन(काष्ठा mm_काष्ठा *mm, काष्ठा mm_काष्ठा *oldmm)
अणु
	अगर (test_bit(MMF_VM_HUGEPAGE, &oldmm->flags))
		वापस __khugepaged_enter(mm);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम khugepaged_निकास(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (test_bit(MMF_VM_HUGEPAGE, &mm->flags))
		__khugepaged_निकास(mm);
पूर्ण

अटल अंतरभूत पूर्णांक khugepaged_enter(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ vm_flags)
अणु
	अगर (!test_bit(MMF_VM_HUGEPAGE, &vma->vm_mm->flags))
		अगर ((khugepaged_always() ||
		     (shmem_file(vma->vm_file) && shmem_huge_enabled(vma)) ||
		     (khugepaged_req_madv() && (vm_flags & VM_HUGEPAGE))) &&
		    !(vm_flags & VM_NOHUGEPAGE) &&
		    !test_bit(MMF_DISABLE_THP, &vma->vm_mm->flags))
			अगर (__khugepaged_enter(vma->vm_mm))
				वापस -ENOMEM;
	वापस 0;
पूर्ण
#अन्यथा /* CONFIG_TRANSPARENT_HUGEPAGE */
अटल अंतरभूत पूर्णांक khugepaged_विभाजन(काष्ठा mm_काष्ठा *mm, काष्ठा mm_काष्ठा *oldmm)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम khugepaged_निकास(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक khugepaged_enter(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ vm_flags)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक khugepaged_enter_vma_merge(काष्ठा vm_area_काष्ठा *vma,
					     अचिन्हित दीर्घ vm_flags)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम collapse_pte_mapped_thp(काष्ठा mm_काष्ठा *mm,
					   अचिन्हित दीर्घ addr)
अणु
पूर्ण

अटल अंतरभूत व्योम khugepaged_min_मुक्त_kbytes_update(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

#पूर्ण_अगर /* _LINUX_KHUGEPAGED_H */
