<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __CPUIDLE_PSCI_H
#घोषणा __CPUIDLE_PSCI_H

काष्ठा device;
काष्ठा device_node;

व्योम psci_set_करोमुख्य_state(u32 state);
पूर्णांक psci_dt_parse_state_node(काष्ठा device_node *np, u32 *state);

#अगर_घोषित CONFIG_ARM_PSCI_CPUIDLE_DOMAIN
काष्ठा device *psci_dt_attach_cpu(पूर्णांक cpu);
व्योम psci_dt_detach_cpu(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत काष्ठा device *psci_dt_attach_cpu(पूर्णांक cpu) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम psci_dt_detach_cpu(काष्ठा device *dev) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __CPUIDLE_PSCI_H */
