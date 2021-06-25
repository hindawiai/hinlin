<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARCH_MACH_COMMON_H
#घोषणा __ARCH_MACH_COMMON_H

बाह्य व्योम shmobile_init_delay(व्योम);
बाह्य व्योम shmobile_boot_vector(व्योम);
बाह्य अचिन्हित दीर्घ shmobile_boot_fn;
बाह्य अचिन्हित दीर्घ shmobile_boot_size;
बाह्य व्योम shmobile_boot_vector_gen2(व्योम);
बाह्य अचिन्हित दीर्घ shmobile_boot_fn_gen2;
बाह्य अचिन्हित दीर्घ shmobile_boot_cpu_gen2;
बाह्य अचिन्हित दीर्घ shmobile_boot_size_gen2;
बाह्य व्योम shmobile_smp_boot(व्योम);
बाह्य व्योम shmobile_smp_sleep(व्योम);
बाह्य व्योम shmobile_smp_hook(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ fn,
			      अचिन्हित दीर्घ arg);
बाह्य bool shmobile_smp_cpu_can_disable(अचिन्हित पूर्णांक cpu);
बाह्य व्योम shmobile_boot_apmu(व्योम);
बाह्य व्योम shmobile_boot_scu(व्योम);
बाह्य व्योम shmobile_smp_scu_prepare_cpus(phys_addr_t scu_base_phys,
					  अचिन्हित पूर्णांक max_cpus);
बाह्य व्योम shmobile_smp_scu_cpu_die(अचिन्हित पूर्णांक cpu);
बाह्य पूर्णांक shmobile_smp_scu_cpu_समाप्त(अचिन्हित पूर्णांक cpu);
बाह्य काष्ठा platक्रमm_suspend_ops shmobile_suspend_ops;

#अगर_घोषित CONFIG_SUSPEND
पूर्णांक shmobile_suspend_init(व्योम);
व्योम shmobile_smp_apmu_suspend_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक shmobile_suspend_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम shmobile_smp_apmu_suspend_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम __init shmobile_init_late(व्योम)
अणु
	shmobile_suspend_init();
पूर्ण

#पूर्ण_अगर /* __ARCH_MACH_COMMON_H */
