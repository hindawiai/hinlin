<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_KASLR_H_
#घोषणा _ASM_KASLR_H_

अचिन्हित दीर्घ kaslr_get_अक्रमom_दीर्घ(स्थिर अक्षर *purpose);

#अगर_घोषित CONFIG_RANDOMIZE_MEMORY
व्योम kernel_अक्रमomize_memory(व्योम);
व्योम init_trampoline_kaslr(व्योम);
#अन्यथा
अटल अंतरभूत व्योम kernel_अक्रमomize_memory(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम init_trampoline_kaslr(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_RANDOMIZE_MEMORY */

#पूर्ण_अगर
