<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_SMP_OPS_H
#घोषणा __ASM_SH_SMP_OPS_H

काष्ठा plat_smp_ops अणु
	व्योम (*smp_setup)(व्योम);
	अचिन्हित पूर्णांक (*smp_processor_id)(व्योम);
	व्योम (*prepare_cpus)(अचिन्हित पूर्णांक max_cpus);
	व्योम (*start_cpu)(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ entry_poपूर्णांक);
	व्योम (*send_ipi)(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक message);
	पूर्णांक (*cpu_disable)(अचिन्हित पूर्णांक cpu);
	व्योम (*cpu_die)(अचिन्हित पूर्णांक cpu);
	व्योम (*play_dead)(व्योम);
पूर्ण;

बाह्य काष्ठा plat_smp_ops *mp_ops;
बाह्य काष्ठा plat_smp_ops shx3_smp_ops;

#अगर_घोषित CONFIG_SMP

अटल अंतरभूत व्योम plat_smp_setup(व्योम)
अणु
	BUG_ON(!mp_ops);
	mp_ops->smp_setup();
पूर्ण

अटल अंतरभूत व्योम play_dead(व्योम)
अणु
	mp_ops->play_dead();
पूर्ण

बाह्य व्योम रेजिस्टर_smp_ops(काष्ठा plat_smp_ops *ops);

#अन्यथा

अटल अंतरभूत व्योम plat_smp_setup(व्योम)
अणु
	/* UP, nothing to करो ... */
पूर्ण

अटल अंतरभूत व्योम रेजिस्टर_smp_ops(काष्ठा plat_smp_ops *ops)
अणु
पूर्ण

अटल अंतरभूत व्योम play_dead(व्योम)
अणु
	BUG();
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

#पूर्ण_अगर /* __ASM_SH_SMP_OPS_H */
