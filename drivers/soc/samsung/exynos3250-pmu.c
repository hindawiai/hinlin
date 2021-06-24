<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2011-2015 Samsung Electronics Co., Ltd.
//		http://www.samsung.com/
//
// Exynos3250 - CPU PMU (Power Management Unit) support

#समावेश <linux/soc/samsung/exynos-regs-pmu.h>
#समावेश <linux/soc/samsung/exynos-pmu.h>

#समावेश "exynos-pmu.h"

अटल स्थिर काष्ठा exynos_pmu_conf exynos3250_pmu_config[] = अणु
	/* अणु .offset = offset, .val = अणु AFTR, W-AFTR, SLEEP पूर्ण */
	अणु EXYNOS3_ARM_CORE0_SYS_PWR_REG,		अणु 0x0, 0x0, 0x2पूर्ण पूर्ण,
	अणु EXYNOS3_DIS_IRQ_ARM_CORE0_LOCAL_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_DIS_IRQ_ARM_CORE0_CENTRAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_ARM_CORE1_SYS_PWR_REG,		अणु 0x0, 0x0, 0x2पूर्ण पूर्ण,
	अणु EXYNOS3_DIS_IRQ_ARM_CORE1_LOCAL_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_DIS_IRQ_ARM_CORE1_CENTRAL_SYS_PWR_REG, अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_ISP_ARM_SYS_PWR_REG,			अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_DIS_IRQ_ISP_ARM_LOCAL_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_DIS_IRQ_ISP_ARM_CENTRAL_SYS_PWR_REG,	अणु 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_ARM_COMMON_SYS_PWR_REG,		अणु 0x0, 0x0, 0x2पूर्ण पूर्ण,
	अणु EXYNOS3_ARM_L2_SYS_PWR_REG,			अणु 0x0, 0x0, 0x3पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_ACLKSTOP_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_SCLKSTOP_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_RESET_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_DRAM_FREQ_DOWN_SYS_PWR_REG,		अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS3_DDRPHY_DLLOFF_SYS_PWR_REG,		अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS3_LPDDR_PHY_DLL_LOCK_SYS_PWR_REG,	अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_ACLKSTOP_COREBLK_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_SCLKSTOP_COREBLK_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_RESET_COREBLK_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_APLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_MPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_BPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_VPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_EPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_UPLL_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS3_EPLLUSER_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_MPLLUSER_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_BPLLUSER_SYSCLK_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_CLKSTOP_CAM_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_CLKSTOP_MFC_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_CLKSTOP_G3D_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_CLKSTOP_LCD0_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_CLKSTOP_ISP_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_CLKSTOP_MAUDIO_SYS_PWR_REG,	अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_RESET_CAM_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_RESET_MFC_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_RESET_G3D_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_RESET_LCD0_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_RESET_ISP_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_RESET_MAUDIO_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_TOP_BUS_SYS_PWR_REG,			अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_TOP_RETENTION_SYS_PWR_REG,		अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS3_TOP_PWR_SYS_PWR_REG,			अणु 0x3, 0x3, 0x3पूर्ण पूर्ण,
	अणु EXYNOS3_TOP_BUS_COREBLK_SYS_PWR_REG,		अणु 0x3, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_TOP_RETENTION_COREBLK_SYS_PWR_REG,	अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS3_TOP_PWR_COREBLK_SYS_PWR_REG,		अणु 0x3, 0x3, 0x3पूर्ण पूर्ण,
	अणु EXYNOS3_LOGIC_RESET_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_OSCCLK_GATE_SYS_PWR_REG,		अणु 0x1, 0x1, 0x1पूर्ण पूर्ण,
	अणु EXYNOS3_LOGIC_RESET_COREBLK_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_OSCCLK_GATE_COREBLK_SYS_PWR_REG,	अणु 0x1, 0x0, 0x1पूर्ण पूर्ण,
	अणु EXYNOS3_PAD_RETENTION_DRAM_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_PAD_RETENTION_MAUDIO_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_PAD_RETENTION_GPIO_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_PAD_RETENTION_UART_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_PAD_RETENTION_MMC0_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_PAD_RETENTION_MMC1_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_PAD_RETENTION_MMC2_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_PAD_RETENTION_SPI_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_PAD_RETENTION_EBIA_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_PAD_RETENTION_EBIB_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_PAD_RETENTION_JTAG_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_PAD_ISOLATION_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_PAD_ALV_SEL_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_XUSBXTI_SYS_PWR_REG,			अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_XXTI_SYS_PWR_REG,			अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_EXT_REGULATOR_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_EXT_REGULATOR_COREBLK_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_GPIO_MODE_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_GPIO_MODE_MAUDIO_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_TOP_ASB_RESET_SYS_PWR_REG,		अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_TOP_ASB_ISOLATION_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_TOP_ASB_RESET_COREBLK_SYS_PWR_REG,	अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_TOP_ASB_ISOLATION_COREBLK_SYS_PWR_REG, अणु 0x1, 0x1, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CAM_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_MFC_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_G3D_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_LCD0_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_ISP_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_MAUDIO_SYS_PWR_REG,			अणु 0x7, 0x0, 0x0पूर्ण पूर्ण,
	अणु EXYNOS3_CMU_SYSCLK_ISP_SYS_PWR_REG,		अणु 0x1, 0x0, 0x0पूर्ण पूर्ण,
	अणु PMU_TABLE_END,पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक स्थिर exynos3250_list_feed[] = अणु
	EXYNOS3_ARM_CORE_OPTION(0),
	EXYNOS3_ARM_CORE_OPTION(1),
	EXYNOS3_ARM_CORE_OPTION(2),
	EXYNOS3_ARM_CORE_OPTION(3),
	EXYNOS3_ARM_COMMON_OPTION,
	EXYNOS3_TOP_PWR_OPTION,
	EXYNOS3_CORE_TOP_PWR_OPTION,
	S5P_CAM_OPTION,
	S5P_MFC_OPTION,
	S5P_G3D_OPTION,
	S5P_LCD0_OPTION,
	S5P_ISP_OPTION,
पूर्ण;

अटल व्योम exynos3250_घातerकरोwn_conf_extra(क्रमागत sys_घातerकरोwn mode)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक पंचांगp;

	/* Enable only SC_FEEDBACK */
	क्रम (i = 0; i < ARRAY_SIZE(exynos3250_list_feed); i++) अणु
		पंचांगp = pmu_raw_पढ़ोl(exynos3250_list_feed[i]);
		पंचांगp &= ~(EXYNOS3_OPTION_USE_SC_COUNTER);
		पंचांगp |= EXYNOS3_OPTION_USE_SC_FEEDBACK;
		pmu_raw_ग_लिखोl(पंचांगp, exynos3250_list_feed[i]);
	पूर्ण

	अगर (mode != SYS_SLEEP)
		वापस;

	pmu_raw_ग_लिखोl(XUSBXTI_DURATION, EXYNOS3_XUSBXTI_DURATION);
	pmu_raw_ग_लिखोl(XXTI_DURATION, EXYNOS3_XXTI_DURATION);
	pmu_raw_ग_लिखोl(EXT_REGULATOR_DURATION, EXYNOS3_EXT_REGULATOR_DURATION);
	pmu_raw_ग_लिखोl(EXT_REGULATOR_COREBLK_DURATION,
		       EXYNOS3_EXT_REGULATOR_COREBLK_DURATION);
पूर्ण

अटल व्योम exynos3250_pmu_init(व्योम)
अणु
	अचिन्हित पूर्णांक value;

	/*
	 * To prevent from issuing new bus request क्रमm L2 memory प्रणाली
	 * If core status is घातer करोwn, should be set '1' to L2 घातer करोwn
	 */
	value = pmu_raw_पढ़ोl(EXYNOS3_ARM_COMMON_OPTION);
	value |= EXYNOS3_OPTION_SKIP_DEACTIVATE_ACEACP_IN_PWDN;
	pmu_raw_ग_लिखोl(value, EXYNOS3_ARM_COMMON_OPTION);

	/* Enable USE_STANDBY_WFI क्रम all CORE */
	pmu_raw_ग_लिखोl(S5P_USE_STANDBY_WFI_ALL, S5P_CENTRAL_SEQ_OPTION);

	/*
	 * Set PSHOLD port क्रम output high
	 */
	value = pmu_raw_पढ़ोl(S5P_PS_HOLD_CONTROL);
	value |= S5P_PS_HOLD_OUTPUT_HIGH;
	pmu_raw_ग_लिखोl(value, S5P_PS_HOLD_CONTROL);

	/*
	 * Enable संकेत क्रम PSHOLD port
	 */
	value = pmu_raw_पढ़ोl(S5P_PS_HOLD_CONTROL);
	value |= S5P_PS_HOLD_EN;
	pmu_raw_ग_लिखोl(value, S5P_PS_HOLD_CONTROL);
पूर्ण

स्थिर काष्ठा exynos_pmu_data exynos3250_pmu_data = अणु
	.pmu_config	= exynos3250_pmu_config,
	.pmu_init	= exynos3250_pmu_init,
	.घातerकरोwn_conf_extra	= exynos3250_घातerकरोwn_conf_extra,
पूर्ण;
