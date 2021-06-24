<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _XEN_SMP_H

#अगर_घोषित CONFIG_SMP
बाह्य व्योम xen_send_IPI_mask(स्थिर काष्ठा cpumask *mask,
			      पूर्णांक vector);
बाह्य व्योम xen_send_IPI_mask_allbutself(स्थिर काष्ठा cpumask *mask,
				पूर्णांक vector);
बाह्य व्योम xen_send_IPI_allbutself(पूर्णांक vector);
बाह्य व्योम xen_send_IPI_all(पूर्णांक vector);
बाह्य व्योम xen_send_IPI_self(पूर्णांक vector);

बाह्य पूर्णांक xen_smp_पूर्णांकr_init(अचिन्हित पूर्णांक cpu);
बाह्य व्योम xen_smp_पूर्णांकr_मुक्त(अचिन्हित पूर्णांक cpu);
पूर्णांक xen_smp_पूर्णांकr_init_pv(अचिन्हित पूर्णांक cpu);
व्योम xen_smp_पूर्णांकr_मुक्त_pv(अचिन्हित पूर्णांक cpu);

व्योम xen_smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus);

व्योम xen_smp_send_reschedule(पूर्णांक cpu);
व्योम xen_smp_send_call_function_ipi(स्थिर काष्ठा cpumask *mask);
व्योम xen_smp_send_call_function_single_ipi(पूर्णांक cpu);

काष्ठा xen_common_irq अणु
	पूर्णांक irq;
	अक्षर *name;
पूर्ण;
#अन्यथा /* CONFIG_SMP */

अटल अंतरभूत पूर्णांक xen_smp_पूर्णांकr_init(अचिन्हित पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम xen_smp_पूर्णांकr_मुक्त(अचिन्हित पूर्णांक cpu) अणुपूर्ण

अटल अंतरभूत पूर्णांक xen_smp_पूर्णांकr_init_pv(अचिन्हित पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम xen_smp_पूर्णांकr_मुक्त_pv(अचिन्हित पूर्णांक cpu) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

#पूर्ण_अगर
