<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 *
 * Copyright (C) 2000 - 2001 by Kanoj Sarcar (kanoj@sgi.com)
 * Copyright (C) 2000 - 2001 by Silicon Graphics, Inc.
 * Copyright (C) 2000, 2001, 2002 Ralf Baechle
 * Copyright (C) 2000, 2001 Broadcom Corporation
 */
#अगर_अघोषित __ASM_SMP_OPS_H
#घोषणा __ASM_SMP_OPS_H

#समावेश <linux/त्रुटिसं.स>

#समावेश <यंत्र/mips-cps.h>

#अगर_घोषित CONFIG_SMP

#समावेश <linux/cpumask.h>

काष्ठा task_काष्ठा;

काष्ठा plat_smp_ops अणु
	व्योम (*send_ipi_single)(पूर्णांक cpu, अचिन्हित पूर्णांक action);
	व्योम (*send_ipi_mask)(स्थिर काष्ठा cpumask *mask, अचिन्हित पूर्णांक action);
	व्योम (*init_secondary)(व्योम);
	व्योम (*smp_finish)(व्योम);
	पूर्णांक (*boot_secondary)(पूर्णांक cpu, काष्ठा task_काष्ठा *idle);
	व्योम (*smp_setup)(व्योम);
	व्योम (*prepare_cpus)(अचिन्हित पूर्णांक max_cpus);
	व्योम (*prepare_boot_cpu)(व्योम);
#अगर_घोषित CONFIG_HOTPLUG_CPU
	पूर्णांक (*cpu_disable)(व्योम);
	व्योम (*cpu_die)(अचिन्हित पूर्णांक cpu);
#पूर्ण_अगर
#अगर_घोषित CONFIG_KEXEC
	व्योम (*kexec_nonboot_cpu)(व्योम);
#पूर्ण_अगर
पूर्ण;

बाह्य व्योम रेजिस्टर_smp_ops(स्थिर काष्ठा plat_smp_ops *ops);

अटल अंतरभूत व्योम plat_smp_setup(व्योम)
अणु
	बाह्य स्थिर काष्ठा plat_smp_ops *mp_ops;	/* निजी */

	mp_ops->smp_setup();
पूर्ण

बाह्य व्योम mips_smp_send_ipi_single(पूर्णांक cpu, अचिन्हित पूर्णांक action);
बाह्य व्योम mips_smp_send_ipi_mask(स्थिर काष्ठा cpumask *mask,
				      अचिन्हित पूर्णांक action);

#अन्यथा /* !CONFIG_SMP */

काष्ठा plat_smp_ops;

अटल अंतरभूत व्योम plat_smp_setup(व्योम)
अणु
	/* UP, nothing to करो ...  */
पूर्ण

अटल अंतरभूत व्योम रेजिस्टर_smp_ops(स्थिर काष्ठा plat_smp_ops *ops)
अणु
पूर्ण

#पूर्ण_अगर /* !CONFIG_SMP */

अटल अंतरभूत पूर्णांक रेजिस्टर_up_smp_ops(व्योम)
अणु
#अगर_घोषित CONFIG_SMP_UP
	बाह्य स्थिर काष्ठा plat_smp_ops up_smp_ops;

	रेजिस्टर_smp_ops(&up_smp_ops);

	वापस 0;
#अन्यथा
	वापस -ENODEV;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक रेजिस्टर_cmp_smp_ops(व्योम)
अणु
#अगर_घोषित CONFIG_MIPS_CMP
	बाह्य स्थिर काष्ठा plat_smp_ops cmp_smp_ops;

	अगर (!mips_cm_present())
		वापस -ENODEV;

	रेजिस्टर_smp_ops(&cmp_smp_ops);

	वापस 0;
#अन्यथा
	वापस -ENODEV;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक रेजिस्टर_vsmp_smp_ops(व्योम)
अणु
#अगर_घोषित CONFIG_MIPS_MT_SMP
	बाह्य स्थिर काष्ठा plat_smp_ops vsmp_smp_ops;

	रेजिस्टर_smp_ops(&vsmp_smp_ops);

	वापस 0;
#अन्यथा
	वापस -ENODEV;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_MIPS_CPS
बाह्य पूर्णांक रेजिस्टर_cps_smp_ops(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक रेजिस्टर_cps_smp_ops(व्योम)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SMP_OPS_H */
