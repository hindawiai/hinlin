<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_HUGETLB_INLINE_H
#घोषणा _LINUX_HUGETLB_INLINE_H

#अगर_घोषित CONFIG_HUGETLB_PAGE

#समावेश <linux/mm.h>

अटल अंतरभूत bool is_vm_hugetlb_page(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस !!(vma->vm_flags & VM_HUGETLB);
पूर्ण

#अन्यथा

अटल अंतरभूत bool is_vm_hugetlb_page(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
