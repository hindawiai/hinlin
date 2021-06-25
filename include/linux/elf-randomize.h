<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ELF_RANDOMIZE_H
#घोषणा _ELF_RANDOMIZE_H

काष्ठा mm_काष्ठा;

#अगर_अघोषित CONFIG_ARCH_HAS_ELF_RANDOMIZE
अटल अंतरभूत अचिन्हित दीर्घ arch_mmap_rnd(व्योम) अणु वापस 0; पूर्ण
# अगर defined(arch_अक्रमomize_brk) && defined(CONFIG_COMPAT_BRK)
#  define compat_brk_अक्रमomized
# endअगर
# अगरndef arch_अक्रमomize_brk
#  define arch_अक्रमomize_brk(mm)	(mm->brk)
# endअगर
#अन्यथा
बाह्य अचिन्हित दीर्घ arch_mmap_rnd(व्योम);
बाह्य अचिन्हित दीर्घ arch_अक्रमomize_brk(काष्ठा mm_काष्ठा *mm);
# अगरdef CONFIG_COMPAT_BRK
#  define compat_brk_अक्रमomized
# endअगर
#पूर्ण_अगर

#पूर्ण_अगर
