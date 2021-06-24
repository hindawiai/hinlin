<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ARM_PARAVIRT_H
#घोषणा _ASM_ARM_PARAVIRT_H

#अगर_घोषित CONFIG_PARAVIRT
#समावेश <linux/अटल_call_types.h>

काष्ठा अटल_key;
बाह्य काष्ठा अटल_key paravirt_steal_enabled;
बाह्य काष्ठा अटल_key paravirt_steal_rq_enabled;

u64 dummy_steal_घड़ी(पूर्णांक cpu);

DECLARE_STATIC_CALL(pv_steal_घड़ी, dummy_steal_घड़ी);

अटल अंतरभूत u64 paravirt_steal_घड़ी(पूर्णांक cpu)
अणु
	वापस अटल_call(pv_steal_घड़ी)(cpu);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
