<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_CPUIDLE_H
#घोषणा __ASM_CPUIDLE_H

#समावेश <यंत्र/proc-fns.h>

#अगर_घोषित CONFIG_CPU_IDLE
बाह्य पूर्णांक arm_cpuidle_init(अचिन्हित पूर्णांक cpu);
बाह्य पूर्णांक arm_cpuidle_suspend(पूर्णांक index);
#अन्यथा
अटल अंतरभूत पूर्णांक arm_cpuidle_init(अचिन्हित पूर्णांक cpu)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक arm_cpuidle_suspend(पूर्णांक index)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
