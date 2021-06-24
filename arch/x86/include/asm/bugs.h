<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_BUGS_H
#घोषणा _ASM_X86_BUGS_H

#समावेश <यंत्र/processor.h>

बाह्य व्योम check_bugs(व्योम);

#अगर defined(CONFIG_CPU_SUP_INTEL) && defined(CONFIG_X86_32)
पूर्णांक ppro_with_ram_bug(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक ppro_with_ram_bug(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

बाह्य व्योम cpu_bugs_smt_update(व्योम);

#पूर्ण_अगर /* _ASM_X86_BUGS_H */
