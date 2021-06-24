<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __HIGHBANK_CORE_H
#घोषणा __HIGHBANK_CORE_H

#समावेश <linux/reboot.h>

बाह्य व्योम highbank_restart(क्रमागत reboot_mode, स्थिर अक्षर *);
बाह्य व्योम __iomem *scu_base_addr;

#अगर_घोषित CONFIG_PM_SLEEP
बाह्य व्योम highbank_pm_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम highbank_pm_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

बाह्य व्योम highbank_smc1(पूर्णांक fn, पूर्णांक arg);

#पूर्ण_अगर
