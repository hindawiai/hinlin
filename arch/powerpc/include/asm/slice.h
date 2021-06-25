<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_SLICE_H
#घोषणा _ASM_POWERPC_SLICE_H

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#समावेश <यंत्र/book3s/64/slice.h>
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

काष्ठा mm_काष्ठा;

#अगर_घोषित CONFIG_PPC_MM_SLICES

#अगर_घोषित CONFIG_HUGETLB_PAGE
#घोषणा HAVE_ARCH_HUGETLB_UNMAPPED_AREA
#पूर्ण_अगर
#घोषणा HAVE_ARCH_UNMAPPED_AREA
#घोषणा HAVE_ARCH_UNMAPPED_AREA_TOPDOWN

अचिन्हित दीर्घ slice_get_unmapped_area(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
				      अचिन्हित दीर्घ flags, अचिन्हित पूर्णांक psize,
				      पूर्णांक topकरोwn);

अचिन्हित पूर्णांक get_slice_psize(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);

व्योम slice_set_range_psize(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ len, अचिन्हित पूर्णांक psize);

व्योम slice_init_new_context_exec(काष्ठा mm_काष्ठा *mm);
व्योम slice_setup_new_exec(व्योम);

#अन्यथा /* CONFIG_PPC_MM_SLICES */

अटल अंतरभूत व्योम slice_init_new_context_exec(काष्ठा mm_काष्ठा *mm) अणुपूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_slice_psize(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_MM_SLICES */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_SLICE_H */
