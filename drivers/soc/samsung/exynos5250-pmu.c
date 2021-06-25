<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2011-2015 Samsung Electronics Co., Ltd.
//		http://www.samsung.com/
//
// Exynos5250 - CPU PMU (Power Management Unit) support

#समावेश <linux/soc/samsung/exynos-regs-pmu.h>
#समावेश <linux/soc/samsung/exynos-pmu.h>

#समावेश "exynos-pmu.h"

अटल स्थिर काष्ठा exynos_pmu_conf exynos5250_pmu_config[] = अणु
	/* अणु .offset = offset, .val = अणु AFTR, LPA, SLEEP पूर्ण */
	अणु EXYNOS5_ARM_CORE0_SYS_PWR_REG,		अणु 0x0, 0x0, 0x2पूर्ण पूर्ण,
	अणु EXYNOS5_DIS_IRQ_ARM_CORE0_LOCAL_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_DIS_IRQ_ARM_CORE0_CENTRAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_ARM_CORE1_SYS_PWR_REG,		अणु 0x0, 0x0, 0x2पूर्ण पूर्ण,
	अणु EXYNOS5_DIS_IRQ_ARM_CORE1_LOCAL_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_DIS_IRQ_ARM_CORE1_CENTRAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_FSYS_ARM_SYS_PWR_REG,			अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_DIS_IRQ_FSYS_ARM_CENTRAL_SYS_PWR_REG,	अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_ISP_ARM_SYS_PWR_REG,			अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_DIS_IRQ_ISP_ARM_LOCAL_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_DIS_IRQ_ISP_ARM_CENTRAL_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_ARM_COMMON_SYS_PWR_REG,		अणु 0x0, 0x0, 0x2पूर्ण पूर्ण,
	अणु EXYNOS5_ARM_L2_SYS_PWR_REG,			अणु 0x3, 0x3, 0x3पूर्ण पूर्ण,
	अणु EXYNOS_L2_OPTION(0),				अणु 0x10, 0x10, 0x0 पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_ACLKSTOP_SYS_PWR_REG,		अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_SCLKSTOP_SYS_PWR_REG,		अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_RESET_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_ACLKSTOP_SYSMEM_SYS_PWR_REG,	अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_SCLKSTOP_SYSMEM_SYS_PWR_REG,	अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_RESET_SYSMEM_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_DRAM_FREQ_DOWN_SYS_PWR_REG,		अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_DDRPHY_DLLOFF_SYS_PWR_REG,		अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_DDRPHY_DLLLOCK_SYS_PWR_REG,		अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_APLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_MPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_VPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_EPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_BPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_MPLLUSER_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_BPLLUSER_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_BUS_SYS_PWR_REG,			अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_RETENTION_SYS_PWR_REG,		अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_PWR_SYS_PWR_REG,			अणु 0x3, 0x0, 0x3पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_BUS_SYSMEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_RETENTION_SYSMEM_SYS_PWR_REG,	अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_PWR_SYSMEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x3पूर्ण पूर्ण,
	अणु EXYNOS5_LOGIC_RESET_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_OSCCLK_GATE_SYS_PWR_REG,		अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_LOGIC_RESET_SYSMEM_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_OSCCLK_GATE_SYSMEM_SYS_PWR_REG,	अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_USBOTG_MEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_G2D_MEM_SYS_PWR_REG,			अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_USBDRD_MEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_SDMMC_MEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CSSYS_MEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_SECSS_MEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_ROTATOR_MEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_INTRAM_MEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_INTROM_MEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_JPEG_MEM_SYS_PWR_REG,			अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_JPEG_MEM_OPTION,			अणु 0x10, 0x10, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_HSI_MEM_SYS_PWR_REG,			अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_MCUIOP_MEM_SYS_PWR_REG,		अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_SATA_MEM_SYS_PWR_REG,			अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_RETENTION_DRAM_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_RETENTION_MAU_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_RETENTION_GPIO_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_RETENTION_UART_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_RETENTION_MMCA_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_RETENTION_MMCB_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_RETENTION_EBIA_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_RETENTION_EBIB_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_RETENTION_SPI_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_RETENTION_GPIO_SYSMEM_SYS_PWR_REG, अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_ISOLATION_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_ISOLATION_SYSMEM_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_PAD_ALV_SEL_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_XUSBXTI_SYS_PWR_REG,			अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_XXTI_SYS_PWR_REG,			अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_EXT_REGULATOR_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_GPIO_MODE_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_GPIO_MODE_SYSMEM_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_GPIO_MODE_MAU_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_ASB_RESET_SYS_PWR_REG,		अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_TOP_ASB_ISOLATION_SYS_PWR_REG,	अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS5_GSCL_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_ISP_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_MFC_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_G3D_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_DISP1_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_MAU_SYS_PWR_REG,			अणु 0x7, 0x7, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_CLKSTOP_GSCL_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_CLKSTOP_ISP_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_CLKSTOP_MFC_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_CLKSTOP_G3D_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_CLKSTOP_DISP1_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_CLKSTOP_MAU_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_SYSCLK_GSCL_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_SYSCLK_ISP_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_SYSCLK_MFC_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_SYSCLK_G3D_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_SYSCLK_DISP1_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_SYSCLK_MAU_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_RESET_GSCL_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_RESET_ISP_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_RESET_MFC_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_RESET_G3D_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_RESET_DISP1_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS5_CMU_RESET_MAU_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु PMU_TABLE_END,पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक स्थिर exynos5_list_both_cnt_feed[] = अणु
	EXYNOS5_ARM_CORE0_OPTION,
	EXYNOS5_ARM_CORE1_OPTION,
	EXYNOS5_ARM_COMMON_OPTION,
	EXYNOS5_GSCL_OPTION,
	EXYNOS5_ISP_OPTION,
	EXYNOS5_MFC_OPTION,
	EXYNOS5_G3D_OPTION,
	EXYNOS5_DISP1_OPTION,
	EXYNOS5_MAU_OPTION,
	EXYNOS5_TOP_PWR_OPTION,
	EXYNOS5_TOP_PWR_SYSMEM_OPTION,
पूर्ण;

अटल अचिन्हित पूर्णांक स्थिर exynos5_list_disable_wfi_wfe[] = अणु
	EXYNOS5_ARM_CORE1_OPTION,
	EXYNOS5_FSYS_ARM_OPTION,
	EXYNOS5_ISP_ARM_OPTION,
पूर्ण;

अटल व्योम exynos5250_pmu_init(व्योम)
अणु
	अचिन्हित पूर्णांक value;
	/*
	 * When SYS_WDTRESET is set, watchकरोg समयr reset request
	 * is ignored by घातer management unit.
	 */
	value = pmu_raw_पढ़ोl(EXYNOS5_AUTO_WDTRESET_DISABLE);
	value &= ~EXYNOS5_SYS_WDTRESET;
	pmu_raw_ग_लिखोl(value, EXYNOS5_AUTO_WDTRESET_DISABLE);

	value = pmu_raw_पढ़ोl(EXYNOS5_MASK_WDTRESET_REQUEST);
	value &= ~EXYNOS5_SYS_WDTRESET;
	pmu_raw_ग_लिखोl(value, EXYNOS5_MASK_WDTRESET_REQUEST);
पूर्ण

अटल व्योम exynos5_घातerकरोwn_conf(क्रमागत sys_घातerकरोwn mode)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक पंचांगp;

	/*
	 * Enable both SC_FEEDBACK and SC_COUNTER
	 */
	क्रम (i = 0; i < ARRAY_SIZE(exynos5_list_both_cnt_feed); i++) अणु
		पंचांगp = pmu_raw_पढ़ोl(exynos5_list_both_cnt_feed[i]);
		पंचांगp |= (EXYNOS5_USE_SC_FEEDBACK |
			EXYNOS5_USE_SC_COUNTER);
		pmu_raw_ग_लिखोl(पंचांगp, exynos5_list_both_cnt_feed[i]);
	पूर्ण

	/*
	 * SKIP_DEACTIVATE_ACEACP_IN_PWDN_BITFIELD Enable
	 */
	पंचांगp = pmu_raw_पढ़ोl(EXYNOS5_ARM_COMMON_OPTION);
	पंचांगp |= EXYNOS5_SKIP_DEACTIVATE_ACEACP_IN_PWDN;
	pmu_raw_ग_लिखोl(पंचांगp, EXYNOS5_ARM_COMMON_OPTION);

	/*
	 * Disable WFI/WFE on XXX_OPTION
	 */
	क्रम (i = 0; i < ARRAY_SIZE(exynos5_list_disable_wfi_wfe); i++) अणु
		पंचांगp = pmu_raw_पढ़ोl(exynos5_list_disable_wfi_wfe[i]);
		पंचांगp &= ~(EXYNOS5_OPTION_USE_STANDBYWFE |
			 EXYNOS5_OPTION_USE_STANDBYWFI);
		pmu_raw_ग_लिखोl(पंचांगp, exynos5_list_disable_wfi_wfe[i]);
	पूर्ण
पूर्ण

स्थिर काष्ठा exynos_pmu_data exynos5250_pmu_data = अणु
	.pmu_config	= exynos5250_pmu_config,
	.pmu_init	= exynos5250_pmu_init,
	.घातerकरोwn_conf	= exynos5_घातerकरोwn_conf,
पूर्ण;
