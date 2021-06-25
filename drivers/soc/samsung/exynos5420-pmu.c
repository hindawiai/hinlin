<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2011-2015 Samsung Electronics Co., Ltd.
//		http://www.samsung.com/
//
// Exynos5420 - CPU PMU (Power Management Unit) support

#समावेश <linux/pm.h>
#समावेश <linux/soc/samsung/exynos-regs-pmu.h>
#समावेश <linux/soc/samsung/exynos-pmu.h>

#समावेश <यंत्र/cputype.h>

#समावेश "exynos-pmu.h"

अटल स्थिर काष्ठा exynos_pmu_conf exynos5420_pmu_config[] = अणु
	/* अणु .offset = offset, .val = अणु AFTR, LPA, SLEEP पूर्ण */
	अणु EXYNOS5_ARM_CORE0_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_DIS_IRQ_ARM_CORE0_LOCAL_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_DIS_IRQ_ARM_CORE0_CENTRAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_ARM_CORE1_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_DIS_IRQ_ARM_CORE1_LOCAL_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_DIS_IRQ_ARM_CORE1_CENTRAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_ARM_CORE2_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_DIS_IRQ_ARM_CORE2_LOCAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_DIS_IRQ_ARM_CORE2_CENTRAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_ARM_CORE3_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_DIS_IRQ_ARM_CORE3_LOCAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_DIS_IRQ_ARM_CORE3_CENTRAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_KFC_CORE0_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_DIS_IRQ_KFC_CORE0_LOCAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_DIS_IRQ_KFC_CORE0_CENTRAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_KFC_CORE1_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_DIS_IRQ_KFC_CORE1_LOCAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_DIS_IRQ_KFC_CORE1_CENTRAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_KFC_CORE2_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_DIS_IRQ_KFC_CORE2_LOCAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_DIS_IRQ_KFC_CORE2_CENTRAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_KFC_CORE3_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_DIS_IRQ_KFC_CORE3_LOCAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_DIS_IRQ_KFC_CORE3_CENTRAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_ISP_ARM_SYS_PWR_REG,			अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_DIS_IRQ_ISP_ARM_LOCAL_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_DIS_IRQ_ISP_ARM_CENTRAL_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_ARM_COMMON_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_KFC_COMMON_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_ARM_L2_SYS_PWR_REG,			अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_KFC_L2_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_ACLKSTOP_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_SCLKSTOP_SYS_PWR_REG,		अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_RESET_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_ACLKSTOP_SYSMEM_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_SCLKSTOP_SYSMEM_SYS_PWR_REG,	अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_RESET_SYSMEM_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_DRAM_FREQ_DOWN_SYS_PWR_REG,		अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_DDRPHY_DLLOFF_SYS_PWR_REG,		अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_DDRPHY_DLLLOCK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_APLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_MPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_VPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_EPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_BPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_DPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_IPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_KPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_MPLLUSER_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_BPLLUSER_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_RPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_SPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_BUS_SYS_PWR_REG,			अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_RETENTION_SYS_PWR_REG,		अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_PWR_SYS_PWR_REG,			अणु 0x3, 0x3, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_BUS_SYSMEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_RETENTION_SYSMEM_SYS_PWR_REG,	अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_PWR_SYSMEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_LOGIC_RESET_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_OSCCLK_GATE_SYS_PWR_REG,		अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_LOGIC_RESET_SYSMEM_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_OSCCLK_GATE_SYSMEM_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_INTRAM_MEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x3पूर्ण पूर्ण,
	अणु EXYNOS5420_INTROM_MEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x3पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_RETENTION_DRAM_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_RETENTION_MAU_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_PAD_RETENTION_JTAG_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_PAD_RETENTION_DRAM_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_PAD_RETENTION_UART_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_PAD_RETENTION_MMC0_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_PAD_RETENTION_MMC1_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_PAD_RETENTION_MMC2_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_PAD_RETENTION_HSI_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_PAD_RETENTION_EBIA_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_PAD_RETENTION_EBIB_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_PAD_RETENTION_SPI_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_PAD_RETENTION_DRAM_COREBLK_SYS_PWR_REG, अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_ISOLATION_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_ISOLATION_SYSMEM_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_ALV_SEL_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_XUSBXTI_SYS_PWR_REG,			अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_XXTI_SYS_PWR_REG,			अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_EXT_REGULATOR_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_GPIO_MODE_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_GPIO_MODE_SYSMEM_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_GPIO_MODE_MAU_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_ASB_RESET_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_ASB_ISOLATION_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_GSCL_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_ISP_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_MFC_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_G3D_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_DISP1_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_MAU_SYS_PWR_REG,			अणु 0x7, 0x7, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_G2D_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_MSC_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_FSYS_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_FSYS2_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_PSGEN_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_PERIC_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_WCORE_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_CLKSTOP_GSCL_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_CLKSTOP_ISP_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_CLKSTOP_MFC_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_CLKSTOP_G3D_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_CLKSTOP_DISP1_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_CLKSTOP_MAU_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_CLKSTOP_G2D_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_CLKSTOP_MSC_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_CLKSTOP_FSYS_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_CLKSTOP_PSGEN_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_CLKSTOP_PERIC_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_CLKSTOP_WCORE_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_SYSCLK_GSCL_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_SYSCLK_ISP_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_SYSCLK_MFC_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_SYSCLK_G3D_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_SYSCLK_DISP1_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_SYSCLK_MAU_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_SYSCLK_G2D_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_SYSCLK_MSC_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_SYSCLK_FSYS_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_SYSCLK_FSYS2_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_SYSCLK_PSGEN_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_SYSCLK_PERIC_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_SYSCLK_WCORE_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_RESET_FSYS2_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_RESET_PSGEN_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_RESET_PERIC_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_RESET_WCORE_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_RESET_GSCL_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_RESET_ISP_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_RESET_MFC_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_RESET_G3D_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_RESET_DISP1_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_RESET_MAU_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_RESET_G2D_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_RESET_MSC_SYS_PWR_REG,		अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5420_CMU_RESET_FSYS_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु PMU_TABLE_END,पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक स्थिर exynos5420_list_disable_pmu_reg[] = अणु
	EXYNOS5_CMU_CLKSTOP_GSCL_SYS_PWR_REG,
	EXYNOS5_CMU_CLKSTOP_ISP_SYS_PWR_REG,
	EXYNOS5_CMU_CLKSTOP_G3D_SYS_PWR_REG,
	EXYNOS5420_CMU_CLKSTOP_DISP1_SYS_PWR_REG,
	EXYNOS5420_CMU_CLKSTOP_MAU_SYS_PWR_REG,
	EXYNOS5420_CMU_CLKSTOP_G2D_SYS_PWR_REG,
	EXYNOS5420_CMU_CLKSTOP_MSC_SYS_PWR_REG,
	EXYNOS5420_CMU_CLKSTOP_FSYS_SYS_PWR_REG,
	EXYNOS5420_CMU_CLKSTOP_PSGEN_SYS_PWR_REG,
	EXYNOS5420_CMU_CLKSTOP_PERIC_SYS_PWR_REG,
	EXYNOS5420_CMU_CLKSTOP_WCORE_SYS_PWR_REG,
	EXYNOS5_CMU_SYSCLK_GSCL_SYS_PWR_REG,
	EXYNOS5_CMU_SYSCLK_ISP_SYS_PWR_REG,
	EXYNOS5_CMU_SYSCLK_G3D_SYS_PWR_REG,
	EXYNOS5420_CMU_SYSCLK_DISP1_SYS_PWR_REG,
	EXYNOS5420_CMU_SYSCLK_MAU_SYS_PWR_REG,
	EXYNOS5420_CMU_SYSCLK_G2D_SYS_PWR_REG,
	EXYNOS5420_CMU_SYSCLK_MSC_SYS_PWR_REG,
	EXYNOS5420_CMU_SYSCLK_FSYS_SYS_PWR_REG,
	EXYNOS5420_CMU_SYSCLK_FSYS2_SYS_PWR_REG,
	EXYNOS5420_CMU_SYSCLK_PSGEN_SYS_PWR_REG,
	EXYNOS5420_CMU_SYSCLK_PERIC_SYS_PWR_REG,
	EXYNOS5420_CMU_SYSCLK_WCORE_SYS_PWR_REG,
	EXYNOS5420_CMU_RESET_FSYS2_SYS_PWR_REG,
	EXYNOS5420_CMU_RESET_PSGEN_SYS_PWR_REG,
	EXYNOS5420_CMU_RESET_PERIC_SYS_PWR_REG,
	EXYNOS5420_CMU_RESET_WCORE_SYS_PWR_REG,
	EXYNOS5_CMU_RESET_GSCL_SYS_PWR_REG,
	EXYNOS5_CMU_RESET_ISP_SYS_PWR_REG,
	EXYNOS5_CMU_RESET_G3D_SYS_PWR_REG,
	EXYNOS5420_CMU_RESET_DISP1_SYS_PWR_REG,
	EXYNOS5420_CMU_RESET_MAU_SYS_PWR_REG,
	EXYNOS5420_CMU_RESET_G2D_SYS_PWR_REG,
	EXYNOS5420_CMU_RESET_MSC_SYS_PWR_REG,
	EXYNOS5420_CMU_RESET_FSYS_SYS_PWR_REG,
पूर्ण;

अटल व्योम exynos5420_घातerकरोwn_conf(क्रमागत sys_घातerकरोwn mode)
अणु
	u32 this_cluster;

	this_cluster = MPIDR_AFFINITY_LEVEL(पढ़ो_cpuid_mpidr(), 1);

	/*
	 * set the cluster id to IROM रेजिस्टर to ensure that we wake
	 * up with the current cluster.
	 */
	pmu_raw_ग_लिखोl(this_cluster, EXYNOS_IROM_DATA2);
पूर्ण

अटल व्योम exynos5420_pmu_init(व्योम)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक i;

	/*
	 * Set the CMU_RESET, CMU_SYSCLK and CMU_CLKSTOP रेजिस्टरs
	 * क्रम local घातer blocks to Low initially as per Table 8-4:
	 * "System-Level Power-Down Configuration Registers".
	 */
	क्रम (i = 0; i < ARRAY_SIZE(exynos5420_list_disable_pmu_reg); i++)
		pmu_raw_ग_लिखोl(0, exynos5420_list_disable_pmu_reg[i]);

	/* Enable USE_STANDBY_WFI क्रम all CORE */
	pmu_raw_ग_लिखोl(EXYNOS5420_USE_STANDBY_WFI_ALL, S5P_CENTRAL_SEQ_OPTION);

	value  = pmu_raw_पढ़ोl(EXYNOS_L2_OPTION(0));
	value &= ~EXYNOS_L2_USE_RETENTION;
	pmu_raw_ग_लिखोl(value, EXYNOS_L2_OPTION(0));

	value = pmu_raw_पढ़ोl(EXYNOS_L2_OPTION(1));
	value &= ~EXYNOS_L2_USE_RETENTION;
	pmu_raw_ग_लिखोl(value, EXYNOS_L2_OPTION(1));

	/*
	 * If L2_COMMON is turned off, घड़ीs related to ATB async
	 * bridge are gated. Thus, when ISP घातer is gated, LPI
	 * may get stuck.
	 */
	value = pmu_raw_पढ़ोl(EXYNOS5420_LPI_MASK);
	value |= EXYNOS5420_ATB_ISP_ARM;
	pmu_raw_ग_लिखोl(value, EXYNOS5420_LPI_MASK);

	value  = pmu_raw_पढ़ोl(EXYNOS5420_LPI_MASK1);
	value |= EXYNOS5420_ATB_KFC;
	pmu_raw_ग_लिखोl(value, EXYNOS5420_LPI_MASK1);

	/* Prevent issue of new bus request from L2 memory */
	value = pmu_raw_पढ़ोl(EXYNOS5420_ARM_COMMON_OPTION);
	value |= EXYNOS5_SKIP_DEACTIVATE_ACEACP_IN_PWDN;
	pmu_raw_ग_लिखोl(value, EXYNOS5420_ARM_COMMON_OPTION);

	value = pmu_raw_पढ़ोl(EXYNOS5420_KFC_COMMON_OPTION);
	value |= EXYNOS5_SKIP_DEACTIVATE_ACEACP_IN_PWDN;
	pmu_raw_ग_लिखोl(value, EXYNOS5420_KFC_COMMON_OPTION);

	/* This setting is to reduce suspend/resume समय */
	pmu_raw_ग_लिखोl(DUR_WAIT_RESET, EXYNOS5420_LOGIC_RESET_DURATION3);

	/* Serialized CPU wakeup of Eagle */
	pmu_raw_ग_लिखोl(SPREAD_ENABLE, EXYNOS5420_ARM_INTR_SPREAD_ENABLE);

	pmu_raw_ग_लिखोl(SPREAD_USE_STANDWFI,
			EXYNOS5420_ARM_INTR_SPREAD_USE_STANDBYWFI);

	pmu_raw_ग_लिखोl(0x1, EXYNOS5420_UP_SCHEDULER);

	pr_info("EXYNOS5420 PMU initialized\n");
पूर्ण

स्थिर काष्ठा exynos_pmu_data exynos5420_pmu_data = अणु
	.pmu_config	= exynos5420_pmu_config,
	.pmu_init	= exynos5420_pmu_init,
	.घातerकरोwn_conf	= exynos5420_घातerकरोwn_conf,
पूर्ण;
