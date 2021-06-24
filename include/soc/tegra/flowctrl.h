<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Functions and macros to control the flowcontroller
 *
 * Copyright (c) 2010-2012, NVIDIA Corporation. All rights reserved.
 */

#अगर_अघोषित __SOC_TEGRA_FLOWCTRL_H__
#घोषणा __SOC_TEGRA_FLOWCTRL_H__

#घोषणा FLOW_CTRL_HALT_CPU0_EVENTS	0x0
#घोषणा FLOW_CTRL_WAITEVENT		(2 << 29)
#घोषणा FLOW_CTRL_WAIT_FOR_INTERRUPT	(4 << 29)
#घोषणा FLOW_CTRL_JTAG_RESUME		(1 << 28)
#घोषणा FLOW_CTRL_SCLK_RESUME		(1 << 27)
#घोषणा FLOW_CTRL_HALT_CPU_IRQ		(1 << 10)
#घोषणा	FLOW_CTRL_HALT_CPU_FIQ		(1 << 8)
#घोषणा FLOW_CTRL_HALT_LIC_IRQ		(1 << 11)
#घोषणा FLOW_CTRL_HALT_LIC_FIQ		(1 << 10)
#घोषणा FLOW_CTRL_HALT_GIC_IRQ		(1 << 9)
#घोषणा FLOW_CTRL_HALT_GIC_FIQ		(1 << 8)
#घोषणा FLOW_CTRL_CPU0_CSR		0x8
#घोषणा	FLOW_CTRL_CSR_INTR_FLAG		(1 << 15)
#घोषणा FLOW_CTRL_CSR_EVENT_FLAG	(1 << 14)
#घोषणा FLOW_CTRL_CSR_ENABLE_EXT_CRAIL	(1 << 13)
#घोषणा FLOW_CTRL_CSR_ENABLE_EXT_NCPU	(1 << 12)
#घोषणा FLOW_CTRL_CSR_ENABLE_EXT_MASK ( \
		FLOW_CTRL_CSR_ENABLE_EXT_NCPU | \
		FLOW_CTRL_CSR_ENABLE_EXT_CRAIL)
#घोषणा FLOW_CTRL_CSR_ENABLE		(1 << 0)
#घोषणा FLOW_CTRL_HALT_CPU1_EVENTS	0x14
#घोषणा FLOW_CTRL_CPU1_CSR		0x18

#घोषणा TEGRA20_FLOW_CTRL_CSR_WFE_CPU0		(1 << 4)
#घोषणा TEGRA20_FLOW_CTRL_CSR_WFE_BITMAP	(3 << 4)
#घोषणा TEGRA20_FLOW_CTRL_CSR_WFI_BITMAP	0

#घोषणा TEGRA30_FLOW_CTRL_CSR_WFI_CPU0		(1 << 8)
#घोषणा TEGRA30_FLOW_CTRL_CSR_WFE_BITMAP	(0xF << 4)
#घोषणा TEGRA30_FLOW_CTRL_CSR_WFI_BITMAP	(0xF << 8)

#अगर_अघोषित __ASSEMBLY__
#अगर_घोषित CONFIG_SOC_TEGRA_FLOWCTRL
u32 flowctrl_पढ़ो_cpu_csr(अचिन्हित पूर्णांक cpuid);
व्योम flowctrl_ग_लिखो_cpu_csr(अचिन्हित पूर्णांक cpuid, u32 value);
व्योम flowctrl_ग_लिखो_cpu_halt(अचिन्हित पूर्णांक cpuid, u32 value);

व्योम flowctrl_cpu_suspend_enter(अचिन्हित पूर्णांक cpuid);
व्योम flowctrl_cpu_suspend_निकास(अचिन्हित पूर्णांक cpuid);
#अन्यथा
अटल अंतरभूत u32 flowctrl_पढ़ो_cpu_csr(अचिन्हित पूर्णांक cpuid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम flowctrl_ग_लिखो_cpu_csr(अचिन्हित पूर्णांक cpuid, u32 value)
अणु
पूर्ण

अटल अंतरभूत व्योम flowctrl_ग_लिखो_cpu_halt(अचिन्हित पूर्णांक cpuid, u32 value) अणुपूर्ण

अटल अंतरभूत व्योम flowctrl_cpu_suspend_enter(अचिन्हित पूर्णांक cpuid)
अणु
पूर्ण

अटल अंतरभूत व्योम flowctrl_cpu_suspend_निकास(अचिन्हित पूर्णांक cpuid)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SOC_TEGRA_FLOWCTRL */
#पूर्ण_अगर /* __ASSEMBLY */
#पूर्ण_अगर /* __SOC_TEGRA_FLOWCTRL_H__ */
