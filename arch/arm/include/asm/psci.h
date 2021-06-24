<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (C) 2012 ARM Limited
 */

#अगर_अघोषित __ASM_ARM_PSCI_H
#घोषणा __ASM_ARM_PSCI_H

बाह्य स्थिर काष्ठा smp_operations psci_smp_ops;

#अगर defined(CONFIG_SMP) && defined(CONFIG_ARM_PSCI)
bool psci_smp_available(व्योम);
#अन्यथा
अटल अंतरभूत bool psci_smp_available(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_ARM_PSCI_H */
