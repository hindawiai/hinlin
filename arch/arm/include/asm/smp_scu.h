<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASMARM_ARCH_SCU_H
#घोषणा __ASMARM_ARCH_SCU_H

#घोषणा SCU_PM_NORMAL	0
#घोषणा SCU_PM_DORMANT	2
#घोषणा SCU_PM_POWEROFF	3

#अगर_अघोषित __ASSEMBLER__

#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/cputype.h>

अटल अंतरभूत bool scu_a9_has_base(व्योम)
अणु
	वापस पढ़ो_cpuid_part() == ARM_CPU_PART_CORTEX_A9;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ scu_a9_get_base(व्योम)
अणु
	अचिन्हित दीर्घ pa;

	यंत्र("mrc p15, 4, %0, c15, c0, 0" : "=r" (pa));

	वापस pa;
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARM_SCU
अचिन्हित पूर्णांक scu_get_core_count(व्योम __iomem *);
पूर्णांक scu_घातer_mode(व्योम __iomem *, अचिन्हित पूर्णांक);
पूर्णांक scu_cpu_घातer_enable(व्योम __iomem *, अचिन्हित पूर्णांक);
पूर्णांक scu_get_cpu_घातer_mode(व्योम __iomem *scu_base, अचिन्हित पूर्णांक logical_cpu);
#अन्यथा
अटल अंतरभूत अचिन्हित पूर्णांक scu_get_core_count(व्योम __iomem *scu_base)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक scu_घातer_mode(व्योम __iomem *scu_base, अचिन्हित पूर्णांक mode)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक scu_cpu_घातer_enable(व्योम __iomem *scu_base,
				       अचिन्हित पूर्णांक mode)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक scu_get_cpu_घातer_mode(व्योम __iomem *scu_base,
					 अचिन्हित पूर्णांक logical_cpu)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SMP) && defined(CONFIG_HAVE_ARM_SCU)
व्योम scu_enable(व्योम __iomem *scu_base);
#अन्यथा
अटल अंतरभूत व्योम scu_enable(व्योम __iomem *scu_base) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर

#पूर्ण_अगर
