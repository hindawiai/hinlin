<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _POWERNV_H
#घोषणा _POWERNV_H

/*
 * There's various hacks scattered throughout the generic घातerpc arch code
 * that needs to call पूर्णांकo घातernv platक्रमm stuff. The prototypes क्रम those
 * functions are in यंत्र/घातernv.h
 */
#समावेश <यंत्र/घातernv.h>

#अगर_घोषित CONFIG_SMP
बाह्य व्योम pnv_smp_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम pnv_smp_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम pnv_platक्रमm_error_reboot(काष्ठा pt_regs *regs, स्थिर अक्षर *msg) __noवापस;

काष्ठा pci_dev;

#अगर_घोषित CONFIG_PCI
बाह्य व्योम pnv_pci_init(व्योम);
बाह्य व्योम pnv_pci_shutकरोwn(व्योम);
#अन्यथा
अटल अंतरभूत व्योम pnv_pci_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम pnv_pci_shutकरोwn(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य u32 pnv_get_supported_cpuidle_states(व्योम);

बाह्य व्योम pnv_lpc_init(व्योम);

बाह्य व्योम opal_handle_events(व्योम);
बाह्य bool opal_have_pending_events(व्योम);
बाह्य व्योम opal_event_shutकरोwn(व्योम);

bool cpu_core_split_required(व्योम);

काष्ठा memcons;
sमाप_प्रकार memcons_copy(काष्ठा memcons *mc, अक्षर *to, loff_t pos, माप_प्रकार count);
u32 memcons_get_size(काष्ठा memcons *mc);
काष्ठा memcons *memcons_init(काष्ठा device_node *node, स्थिर अक्षर *mc_prop_name);

#पूर्ण_अगर /* _POWERNV_H */
