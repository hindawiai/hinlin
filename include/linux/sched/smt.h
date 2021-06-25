<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_SMT_H
#घोषणा _LINUX_SCHED_SMT_H

#समावेश <linux/अटल_key.h>

#अगर_घोषित CONFIG_SCHED_SMT
बाह्य काष्ठा अटल_key_false sched_smt_present;

अटल __always_अंतरभूत bool sched_smt_active(व्योम)
अणु
	वापस अटल_branch_likely(&sched_smt_present);
पूर्ण
#अन्यथा
अटल अंतरभूत bool sched_smt_active(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

व्योम arch_smt_update(व्योम);

#पूर्ण_अगर
