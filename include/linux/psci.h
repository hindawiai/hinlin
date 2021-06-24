<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (C) 2015 ARM Limited
 */

#अगर_अघोषित __LINUX_PSCI_H
#घोषणा __LINUX_PSCI_H

#समावेश <linux/arm-smccc.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>

#घोषणा PSCI_POWER_STATE_TYPE_STANDBY		0
#घोषणा PSCI_POWER_STATE_TYPE_POWER_DOWN	1

bool psci_tos_resident_on(पूर्णांक cpu);

पूर्णांक psci_cpu_suspend_enter(u32 state);
bool psci_घातer_state_is_valid(u32 state);
पूर्णांक psci_set_osi_mode(bool enable);
bool psci_has_osi_support(व्योम);

काष्ठा psci_operations अणु
	u32 (*get_version)(व्योम);
	पूर्णांक (*cpu_suspend)(u32 state, अचिन्हित दीर्घ entry_poपूर्णांक);
	पूर्णांक (*cpu_off)(u32 state);
	पूर्णांक (*cpu_on)(अचिन्हित दीर्घ cpuid, अचिन्हित दीर्घ entry_poपूर्णांक);
	पूर्णांक (*migrate)(अचिन्हित दीर्घ cpuid);
	पूर्णांक (*affinity_info)(अचिन्हित दीर्घ target_affinity,
			अचिन्हित दीर्घ lowest_affinity_level);
	पूर्णांक (*migrate_info_type)(व्योम);
पूर्ण;

बाह्य काष्ठा psci_operations psci_ops;

काष्ठा psci_0_1_function_ids अणु
	u32 cpu_suspend;
	u32 cpu_on;
	u32 cpu_off;
	u32 migrate;
पूर्ण;

काष्ठा psci_0_1_function_ids get_psci_0_1_function_ids(व्योम);

#अगर defined(CONFIG_ARM_PSCI_FW)
पूर्णांक __init psci_dt_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक psci_dt_init(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ARM_PSCI_FW) && defined(CONFIG_ACPI)
पूर्णांक __init psci_acpi_init(व्योम);
bool __init acpi_psci_present(व्योम);
bool acpi_psci_use_hvc(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक psci_acpi_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत bool acpi_psci_present(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool acpi_psci_use_hvc(व्योम) अणुवापस false; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_PSCI_H */
