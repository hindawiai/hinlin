<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Common Header क्रम Exynos machines
 */

#अगर_अघोषित __ARCH_ARM_MACH_EXYNOS_COMMON_H
#घोषणा __ARCH_ARM_MACH_EXYNOS_COMMON_H

#समावेश <linux/platक्रमm_data/cpuidle-exynos.h>

#घोषणा EXYNOS3250_SOC_ID	0xE3472000
#घोषणा EXYNOS3_SOC_MASK	0xFFFFF000

#घोषणा EXYNOS4210_CPU_ID	0x43210000
#घोषणा EXYNOS4412_CPU_ID	0xE4412200
#घोषणा EXYNOS4_CPU_MASK	0xFFFE0000

#घोषणा EXYNOS5250_SOC_ID	0x43520000
#घोषणा EXYNOS5410_SOC_ID	0xE5410000
#घोषणा EXYNOS5420_SOC_ID	0xE5420000
#घोषणा EXYNOS5800_SOC_ID	0xE5422000
#घोषणा EXYNOS5_SOC_MASK	0xFFFFF000

बाह्य अचिन्हित दीर्घ exynos_cpu_id;

#घोषणा IS_SAMSUNG_CPU(name, id, mask)		\
अटल अंतरभूत पूर्णांक is_samsung_##name(व्योम)	\
अणु						\
	वापस ((exynos_cpu_id & mask) == (id & mask));	\
पूर्ण

IS_SAMSUNG_CPU(exynos3250, EXYNOS3250_SOC_ID, EXYNOS3_SOC_MASK)
IS_SAMSUNG_CPU(exynos4210, EXYNOS4210_CPU_ID, EXYNOS4_CPU_MASK)
IS_SAMSUNG_CPU(exynos4412, EXYNOS4412_CPU_ID, EXYNOS4_CPU_MASK)
IS_SAMSUNG_CPU(exynos5250, EXYNOS5250_SOC_ID, EXYNOS5_SOC_MASK)
IS_SAMSUNG_CPU(exynos5410, EXYNOS5410_SOC_ID, EXYNOS5_SOC_MASK)
IS_SAMSUNG_CPU(exynos5420, EXYNOS5420_SOC_ID, EXYNOS5_SOC_MASK)
IS_SAMSUNG_CPU(exynos5800, EXYNOS5800_SOC_ID, EXYNOS5_SOC_MASK)

#अगर defined(CONFIG_SOC_EXYNOS3250)
# define soc_is_exynos3250()	is_samsung_exynos3250()
#अन्यथा
# define soc_is_exynos3250()	0
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_EXYNOS4210)
# define soc_is_exynos4210()	is_samsung_exynos4210()
#अन्यथा
# define soc_is_exynos4210()	0
#पूर्ण_अगर

#अगर defined(CONFIG_SOC_EXYNOS4412)
# define soc_is_exynos4412()	is_samsung_exynos4412()
#अन्यथा
# define soc_is_exynos4412()	0
#पूर्ण_अगर

#घोषणा EXYNOS4210_REV_0	(0x0)
#घोषणा EXYNOS4210_REV_1_0	(0x10)
#घोषणा EXYNOS4210_REV_1_1	(0x11)

#अगर defined(CONFIG_SOC_EXYNOS5250)
# define soc_is_exynos5250()	is_samsung_exynos5250()
#अन्यथा
# define soc_is_exynos5250()	0
#पूर्ण_अगर

#अगर defined(CONFIG_SOC_EXYNOS5410)
# define soc_is_exynos5410()	is_samsung_exynos5410()
#अन्यथा
# define soc_is_exynos5410()	0
#पूर्ण_अगर

#अगर defined(CONFIG_SOC_EXYNOS5420)
# define soc_is_exynos5420()	is_samsung_exynos5420()
#अन्यथा
# define soc_is_exynos5420()	0
#पूर्ण_अगर

#अगर defined(CONFIG_SOC_EXYNOS5800)
# define soc_is_exynos5800()	is_samsung_exynos5800()
#अन्यथा
# define soc_is_exynos5800()	0
#पूर्ण_अगर

बाह्य u32 cp15_save_diag;
बाह्य u32 cp15_save_घातer;

बाह्य व्योम __iomem *sysram_ns_base_addr;
बाह्य व्योम __iomem *sysram_base_addr;
बाह्य phys_addr_t sysram_base_phys;
बाह्य व्योम __iomem *pmu_base_addr;
व्योम exynos_sysram_init(व्योम);

क्रमागत अणु
	FW_DO_IDLE_SLEEP,
	FW_DO_IDLE_AFTR,
पूर्ण;

व्योम exynos_firmware_init(व्योम);

/* CPU BOOT mode flag क्रम Exynos3250 SoC bootloader */
#घोषणा C2_STATE	(1 << 3)
/*
 * Magic values क्रम bootloader indicating chosen low घातer mode.
 * See also Documentation/arm/samsung/bootloader-पूर्णांकerface.rst
 */
#घोषणा EXYNOS_SLEEP_MAGIC	0x00000bad
#घोषणा EXYNOS_AFTR_MAGIC	0xfcba0d10

bool __init exynos_secure_firmware_available(व्योम);
व्योम exynos_set_boot_flag(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक mode);
व्योम exynos_clear_boot_flag(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक mode);

#अगर_घोषित CONFIG_PM_SLEEP
बाह्य व्योम __init exynos_pm_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम exynos_pm_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

बाह्य व्योम exynos_cpu_resume(व्योम);
बाह्य व्योम exynos_cpu_resume_ns(व्योम);

बाह्य स्थिर काष्ठा smp_operations exynos_smp_ops;

बाह्य व्योम exynos_cpu_घातer_करोwn(पूर्णांक cpu);
बाह्य व्योम exynos_cpu_घातer_up(पूर्णांक cpu);
बाह्य पूर्णांक  exynos_cpu_घातer_state(पूर्णांक cpu);
बाह्य व्योम exynos_cluster_घातer_करोwn(पूर्णांक cluster);
बाह्य व्योम exynos_cluster_घातer_up(पूर्णांक cluster);
बाह्य पूर्णांक  exynos_cluster_घातer_state(पूर्णांक cluster);
बाह्य व्योम exynos_cpu_save_रेजिस्टर(व्योम);
बाह्य व्योम exynos_cpu_restore_रेजिस्टर(व्योम);
बाह्य व्योम exynos_pm_central_suspend(व्योम);
बाह्य पूर्णांक exynos_pm_central_resume(व्योम);
बाह्य व्योम exynos_enter_aftr(व्योम);
#अगर_घोषित CONFIG_SMP
बाह्य व्योम exynos_scu_enable(व्योम);
#अन्यथा
अटल अंतरभूत व्योम exynos_scu_enable(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य काष्ठा cpuidle_exynos_data cpuidle_coupled_exynos_data;

बाह्य व्योम exynos_set_delayed_reset_निश्चितion(bool enable);

बाह्य अचिन्हित पूर्णांक exynos_rev(व्योम);
बाह्य व्योम exynos_core_restart(u32 core_id);
बाह्य पूर्णांक exynos_set_boot_addr(u32 core_id, अचिन्हित दीर्घ boot_addr);
बाह्य पूर्णांक exynos_get_boot_addr(u32 core_id, अचिन्हित दीर्घ *boot_addr);

अटल अंतरभूत व्योम pmu_raw_ग_लिखोl(u32 val, u32 offset)
अणु
	ग_लिखोl_relaxed(val, pmu_base_addr + offset);
पूर्ण

अटल अंतरभूत u32 pmu_raw_पढ़ोl(u32 offset)
अणु
	वापस पढ़ोl_relaxed(pmu_base_addr + offset);
पूर्ण

#पूर्ण_अगर /* __ARCH_ARM_MACH_EXYNOS_COMMON_H */
