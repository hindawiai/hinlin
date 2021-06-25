<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_ESPFIX_H
#घोषणा _ASM_X86_ESPFIX_H

#अगर_घोषित CONFIG_X86_ESPFIX64

#समावेश <यंत्र/percpu.h>

DECLARE_PER_CPU_READ_MOSTLY(अचिन्हित दीर्घ, espfix_stack);
DECLARE_PER_CPU_READ_MOSTLY(अचिन्हित दीर्घ, espfix_waddr);

बाह्य व्योम init_espfix_bsp(व्योम);
बाह्य व्योम init_espfix_ap(पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत व्योम init_espfix_ap(पूर्णांक cpu) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_ESPFIX_H */
