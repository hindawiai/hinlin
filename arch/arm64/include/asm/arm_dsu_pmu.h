<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ARM DynamIQ Shared Unit (DSU) PMU Low level रेजिस्टर access routines.
 *
 * Copyright (C) ARM Limited, 2017.
 *
 * Author: Suzuki K Poulose <suzuki.poulose@arm.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/build_bug.h>
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/sysreg.h>


#घोषणा CLUSTERPMCR_EL1			sys_reg(3, 0, 15, 5, 0)
#घोषणा CLUSTERPMCNTENSET_EL1		sys_reg(3, 0, 15, 5, 1)
#घोषणा CLUSTERPMCNTENCLR_EL1		sys_reg(3, 0, 15, 5, 2)
#घोषणा CLUSTERPMOVSSET_EL1		sys_reg(3, 0, 15, 5, 3)
#घोषणा CLUSTERPMOVSCLR_EL1		sys_reg(3, 0, 15, 5, 4)
#घोषणा CLUSTERPMSELR_EL1		sys_reg(3, 0, 15, 5, 5)
#घोषणा CLUSTERPMINTENSET_EL1		sys_reg(3, 0, 15, 5, 6)
#घोषणा CLUSTERPMINTENCLR_EL1		sys_reg(3, 0, 15, 5, 7)
#घोषणा CLUSTERPMCCNTR_EL1		sys_reg(3, 0, 15, 6, 0)
#घोषणा CLUSTERPMXEVTYPER_EL1		sys_reg(3, 0, 15, 6, 1)
#घोषणा CLUSTERPMXEVCNTR_EL1		sys_reg(3, 0, 15, 6, 2)
#घोषणा CLUSTERPMMDCR_EL1		sys_reg(3, 0, 15, 6, 3)
#घोषणा CLUSTERPMCEID0_EL1		sys_reg(3, 0, 15, 6, 4)
#घोषणा CLUSTERPMCEID1_EL1		sys_reg(3, 0, 15, 6, 5)

अटल अंतरभूत u32 __dsu_pmu_पढ़ो_pmcr(व्योम)
अणु
	वापस पढ़ो_sysreg_s(CLUSTERPMCR_EL1);
पूर्ण

अटल अंतरभूत व्योम __dsu_pmu_ग_लिखो_pmcr(u32 val)
अणु
	ग_लिखो_sysreg_s(val, CLUSTERPMCR_EL1);
	isb();
पूर्ण

अटल अंतरभूत u32 __dsu_pmu_get_reset_overflow(व्योम)
अणु
	u32 val = पढ़ो_sysreg_s(CLUSTERPMOVSCLR_EL1);
	/* Clear the bit */
	ग_लिखो_sysreg_s(val, CLUSTERPMOVSCLR_EL1);
	isb();
	वापस val;
पूर्ण

अटल अंतरभूत व्योम __dsu_pmu_select_counter(पूर्णांक counter)
अणु
	ग_लिखो_sysreg_s(counter, CLUSTERPMSELR_EL1);
	isb();
पूर्ण

अटल अंतरभूत u64 __dsu_pmu_पढ़ो_counter(पूर्णांक counter)
अणु
	__dsu_pmu_select_counter(counter);
	वापस पढ़ो_sysreg_s(CLUSTERPMXEVCNTR_EL1);
पूर्ण

अटल अंतरभूत व्योम __dsu_pmu_ग_लिखो_counter(पूर्णांक counter, u64 val)
अणु
	__dsu_pmu_select_counter(counter);
	ग_लिखो_sysreg_s(val, CLUSTERPMXEVCNTR_EL1);
	isb();
पूर्ण

अटल अंतरभूत व्योम __dsu_pmu_set_event(पूर्णांक counter, u32 event)
अणु
	__dsu_pmu_select_counter(counter);
	ग_लिखो_sysreg_s(event, CLUSTERPMXEVTYPER_EL1);
	isb();
पूर्ण

अटल अंतरभूत u64 __dsu_pmu_पढ़ो_pmccntr(व्योम)
अणु
	वापस पढ़ो_sysreg_s(CLUSTERPMCCNTR_EL1);
पूर्ण

अटल अंतरभूत व्योम __dsu_pmu_ग_लिखो_pmccntr(u64 val)
अणु
	ग_लिखो_sysreg_s(val, CLUSTERPMCCNTR_EL1);
	isb();
पूर्ण

अटल अंतरभूत व्योम __dsu_pmu_disable_counter(पूर्णांक counter)
अणु
	ग_लिखो_sysreg_s(BIT(counter), CLUSTERPMCNTENCLR_EL1);
	isb();
पूर्ण

अटल अंतरभूत व्योम __dsu_pmu_enable_counter(पूर्णांक counter)
अणु
	ग_लिखो_sysreg_s(BIT(counter), CLUSTERPMCNTENSET_EL1);
	isb();
पूर्ण

अटल अंतरभूत व्योम __dsu_pmu_counter_पूर्णांकerrupt_enable(पूर्णांक counter)
अणु
	ग_लिखो_sysreg_s(BIT(counter), CLUSTERPMINTENSET_EL1);
	isb();
पूर्ण

अटल अंतरभूत व्योम __dsu_pmu_counter_पूर्णांकerrupt_disable(पूर्णांक counter)
अणु
	ग_लिखो_sysreg_s(BIT(counter), CLUSTERPMINTENCLR_EL1);
	isb();
पूर्ण


अटल अंतरभूत u32 __dsu_pmu_पढ़ो_pmceid(पूर्णांक n)
अणु
	चयन (n) अणु
	हाल 0:
		वापस पढ़ो_sysreg_s(CLUSTERPMCEID0_EL1);
	हाल 1:
		वापस पढ़ो_sysreg_s(CLUSTERPMCEID1_EL1);
	शेष:
		BUILD_BUG();
		वापस 0;
	पूर्ण
पूर्ण
