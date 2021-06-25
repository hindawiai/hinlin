<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __ASM_POWERPC_XMON_H
#घोषणा __ASM_POWERPC_XMON_H

/*
 * Copyrignt (C) 2006 IBM Corp
 */

#अगर_घोषित __KERNEL__

#समावेश <linux/irqवापस.h>

#अगर_घोषित CONFIG_XMON
बाह्य व्योम xmon_setup(व्योम);
बाह्य व्योम xmon_रेजिस्टर_spus(काष्ठा list_head *list);
काष्ठा pt_regs;
बाह्य पूर्णांक xmon(काष्ठा pt_regs *excp);
बाह्य irqवापस_t xmon_irq(पूर्णांक, व्योम *);
#अन्यथा
अटल अंतरभूत व्योम xmon_setup(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम xmon_रेजिस्टर_spus(काष्ठा list_head *list) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_XMON) && defined(CONFIG_SMP)
बाह्य पूर्णांक cpus_are_in_xmon(व्योम);
#पूर्ण_अगर

बाह्य __म_लिखो(1, 2) व्योम xmon_म_लिखो(स्थिर अक्षर *क्रमmat, ...);

#पूर्ण_अगर /* __KERNEL __ */
#पूर्ण_अगर /* __ASM_POWERPC_XMON_H */
