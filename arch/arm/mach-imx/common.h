<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2004-2014 Freescale Semiconductor, Inc. All Rights Reserved.
 */


#अगर_अघोषित __ASM_ARCH_MXC_COMMON_H__
#घोषणा __ASM_ARCH_MXC_COMMON_H__

#समावेश <linux/reboot.h>

काष्ठा irq_data;
काष्ठा platक्रमm_device;
काष्ठा pt_regs;
काष्ठा clk;
काष्ठा device_node;
क्रमागत mxc_cpu_pwr_mode;
काष्ठा of_device_id;

व्योम mx31_map_io(व्योम);
व्योम mx35_map_io(व्योम);
व्योम imx21_init_early(व्योम);
व्योम imx31_init_early(व्योम);
व्योम imx35_init_early(व्योम);
व्योम mx31_init_irq(व्योम);
व्योम mx35_init_irq(व्योम);
व्योम mxc_set_cpu_type(अचिन्हित पूर्णांक type);
व्योम mxc_restart(क्रमागत reboot_mode, स्थिर अक्षर *);
व्योम mxc_arch_reset_init(व्योम __iomem *);
व्योम imx1_reset_init(व्योम __iomem *);
व्योम imx_set_aips(व्योम __iomem *);
व्योम imx_aips_allow_unprivileged_access(स्थिर अक्षर *compat);
पूर्णांक mxc_device_init(व्योम);
व्योम imx_set_soc_revision(अचिन्हित पूर्णांक rev);
व्योम imx_init_revision_from_anatop(व्योम);
व्योम imx6_enable_rbc(bool enable);
व्योम imx_gpc_check_dt(व्योम);
व्योम imx_gpc_set_arm_घातer_in_lpm(bool घातer_off);
व्योम imx_gpc_set_l2_mem_घातer_in_lpm(bool घातer_off);
व्योम imx_gpc_set_arm_घातer_up_timing(u32 sw2iso, u32 sw);
व्योम imx_gpc_set_arm_घातer_करोwn_timing(u32 sw2iso, u32 sw);
व्योम imx25_pm_init(व्योम);
व्योम imx27_pm_init(व्योम);
व्योम imx5_pmu_init(व्योम);

क्रमागत mxc_cpu_pwr_mode अणु
	WAIT_CLOCKED,		/* wfi only */
	WAIT_UNCLOCKED,		/* WAIT */
	WAIT_UNCLOCKED_POWER_OFF,	/* WAIT + SRPG */
	STOP_POWER_ON,		/* just STOP */
	STOP_POWER_OFF,		/* STOP + SRPG */
पूर्ण;

क्रमागत ulp_cpu_pwr_mode अणु
	ULP_PM_HSRUN,    /* High speed run mode */
	ULP_PM_RUN,      /* Run mode */
	ULP_PM_WAIT,     /* Wait mode */
	ULP_PM_STOP,     /* Stop mode */
	ULP_PM_VLPS,     /* Very low घातer stop mode */
	ULP_PM_VLLS,     /* very low leakage stop mode */
पूर्ण;

व्योम imx_enable_cpu(पूर्णांक cpu, bool enable);
व्योम imx_set_cpu_jump(पूर्णांक cpu, व्योम *jump_addr);
u32 imx_get_cpu_arg(पूर्णांक cpu);
व्योम imx_set_cpu_arg(पूर्णांक cpu, u32 arg);
#अगर_घोषित CONFIG_SMP
व्योम v7_secondary_startup(व्योम);
व्योम imx_scu_map_io(व्योम);
व्योम imx_smp_prepare(व्योम);
#अन्यथा
अटल अंतरभूत व्योम imx_scu_map_io(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम imx_smp_prepare(व्योम) अणुपूर्ण
#पूर्ण_अगर
व्योम imx_src_init(व्योम);
व्योम imx_gpc_pre_suspend(bool arm_घातer_off);
व्योम imx_gpc_post_resume(व्योम);
व्योम imx_gpc_mask_all(व्योम);
व्योम imx_gpc_restore_all(व्योम);
व्योम imx_gpc_hwirq_mask(अचिन्हित पूर्णांक hwirq);
व्योम imx_gpc_hwirq_unmask(अचिन्हित पूर्णांक hwirq);
व्योम imx_anatop_init(व्योम);
व्योम imx_anatop_pre_suspend(व्योम);
व्योम imx_anatop_post_resume(व्योम);
पूर्णांक imx6_set_lpm(क्रमागत mxc_cpu_pwr_mode mode);
व्योम imx6_set_पूर्णांक_mem_clk_lpm(bool enable);
पूर्णांक imx_mmdc_get_ddr_type(व्योम);
पूर्णांक imx7ulp_set_lpm(क्रमागत ulp_cpu_pwr_mode mode);

व्योम imx_cpu_die(अचिन्हित पूर्णांक cpu);
पूर्णांक imx_cpu_समाप्त(अचिन्हित पूर्णांक cpu);

#अगर_घोषित CONFIG_SUSPEND
व्योम imx53_suspend(व्योम __iomem *ocram_vbase);
बाह्य स्थिर u32 imx53_suspend_sz;
व्योम imx6_suspend(व्योम __iomem *ocram_vbase);
#अन्यथा
अटल अंतरभूत व्योम imx53_suspend(व्योम __iomem *ocram_vbase) अणुपूर्ण
अटल स्थिर u32 imx53_suspend_sz;
अटल अंतरभूत व्योम imx6_suspend(व्योम __iomem *ocram_vbase) अणुपूर्ण
#पूर्ण_अगर

व्योम v7_cpu_resume(व्योम);

व्योम imx6_pm_ccm_init(स्थिर अक्षर *ccm_compat);
व्योम imx6q_pm_init(व्योम);
व्योम imx6dl_pm_init(व्योम);
व्योम imx6sl_pm_init(व्योम);
व्योम imx6sx_pm_init(व्योम);
व्योम imx6ul_pm_init(व्योम);
व्योम imx7ulp_pm_init(व्योम);

#अगर_घोषित CONFIG_PM
व्योम imx51_pm_init(व्योम);
व्योम imx53_pm_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम imx51_pm_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम imx53_pm_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NEON
पूर्णांक mx51_neon_fixup(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक mx51_neon_fixup(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CACHE_L2X0
व्योम imx_init_l2cache(व्योम);
#अन्यथा
अटल अंतरभूत व्योम imx_init_l2cache(व्योम) अणुपूर्ण
#पूर्ण_अगर

बाह्य स्थिर काष्ठा smp_operations imx_smp_ops;
बाह्य स्थिर काष्ठा smp_operations ls1021a_smp_ops;

#पूर्ण_अगर
