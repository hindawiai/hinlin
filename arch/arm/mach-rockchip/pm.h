<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014, Fuzhou Rockchip Electronics Co., Ltd
 * Author: Tony Xie <tony.xie@rock-chips.com>
 */

#अगर_अघोषित __MACH_ROCKCHIP_PM_H
#घोषणा __MACH_ROCKCHIP_PM_H

बाह्य अचिन्हित दीर्घ rkpm_bootdata_cpusp;
बाह्य अचिन्हित दीर्घ rkpm_bootdata_cpu_code;
बाह्य अचिन्हित दीर्घ rkpm_bootdata_l2ctlr_f;
बाह्य अचिन्हित दीर्घ rkpm_bootdata_l2ctlr;
बाह्य अचिन्हित दीर्घ rkpm_bootdata_ddr_code;
बाह्य अचिन्हित दीर्घ rkpm_bootdata_ddr_data;
बाह्य अचिन्हित दीर्घ rk3288_bootram_sz;

व्योम rockchip_slp_cpu_resume(व्योम);
#अगर_घोषित CONFIG_PM_SLEEP
व्योम __init rockchip_suspend_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम rockchip_suspend_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

/****** following is rk3288 defined **********/
#घोषणा RK3288_PMU_WAKEUP_CFG0		0x00
#घोषणा RK3288_PMU_WAKEUP_CFG1		0x04
#घोषणा RK3288_PMU_PWRMODE_CON		0x18
#घोषणा RK3288_PMU_OSC_CNT		0x20
#घोषणा RK3288_PMU_PLL_CNT		0x24
#घोषणा RK3288_PMU_STABL_CNT		0x28
#घोषणा RK3288_PMU_DDR0IO_PWRON_CNT	0x2c
#घोषणा RK3288_PMU_DDR1IO_PWRON_CNT	0x30
#घोषणा RK3288_PMU_CORE_PWRDWN_CNT	0x34
#घोषणा RK3288_PMU_CORE_PWRUP_CNT	0x38
#घोषणा RK3288_PMU_GPU_PWRDWN_CNT	0x3c
#घोषणा RK3288_PMU_GPU_PWRUP_CNT	0x40
#घोषणा RK3288_PMU_WAKEUP_RST_CLR_CNT	0x44
#घोषणा RK3288_PMU_PWRMODE_CON1		0x90

#घोषणा RK3288_SGRF_SOC_CON0		(0x0000)
#घोषणा RK3288_SGRF_FAST_BOOT_ADDR	(0x0120)
#घोषणा SGRF_PCLK_WDT_GATE		BIT(6)
#घोषणा SGRF_PCLK_WDT_GATE_WRITE	BIT(22)
#घोषणा SGRF_FAST_BOOT_EN		BIT(8)
#घोषणा SGRF_FAST_BOOT_EN_WRITE		BIT(24)

#घोषणा RK3288_SGRF_CPU_CON0		(0x40)
#घोषणा SGRF_DAPDEVICEEN		BIT(0)
#घोषणा SGRF_DAPDEVICEEN_WRITE		BIT(16)

/* PMU_WAKEUP_CFG1 bits */
#घोषणा PMU_ARMINT_WAKEUP_EN		BIT(0)
#घोषणा PMU_GPIOINT_WAKEUP_EN		BIT(3)

क्रमागत rk3288_pwr_mode_con अणु
	PMU_PWR_MODE_EN = 0,
	PMU_CLK_CORE_SRC_GATE_EN,
	PMU_GLOBAL_INT_DISABLE,
	PMU_L2FLUSH_EN,
	PMU_BUS_PD_EN,
	PMU_A12_0_PD_EN,
	PMU_SCU_EN,
	PMU_PLL_PD_EN,
	PMU_CHIP_PD_EN, /* POWER OFF PIN ENABLE */
	PMU_PWROFF_COMB,
	PMU_ALIVE_USE_LF,
	PMU_PMU_USE_LF,
	PMU_OSC_24M_DIS,
	PMU_INPUT_CLAMP_EN,
	PMU_WAKEUP_RESET_EN,
	PMU_SREF0_ENTER_EN,
	PMU_SREF1_ENTER_EN,
	PMU_DDR0IO_RET_EN,
	PMU_DDR1IO_RET_EN,
	PMU_DDR0_GATING_EN,
	PMU_DDR1_GATING_EN,
	PMU_DDR0IO_RET_DE_REQ,
	PMU_DDR1IO_RET_DE_REQ
पूर्ण;

क्रमागत rk3288_pwr_mode_con1 अणु
	PMU_CLR_BUS = 0,
	PMU_CLR_CORE,
	PMU_CLR_CPUP,
	PMU_CLR_ALIVE,
	PMU_CLR_DMA,
	PMU_CLR_PERI,
	PMU_CLR_GPU,
	PMU_CLR_VIDEO,
	PMU_CLR_HEVC,
	PMU_CLR_VIO,
पूर्ण;

#पूर्ण_अगर /* __MACH_ROCKCHIP_PM_H */
