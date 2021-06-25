<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common definitions across all variants of ICP and ICS पूर्णांकerrupt
 * controllers.
 */

#अगर_अघोषित _XICS_H
#घोषणा _XICS_H

#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा XICS_IPI		2
#घोषणा XICS_IRQ_SPURIOUS	0

/* Want a priority other than 0.  Various HW issues require this. */
#घोषणा	DEFAULT_PRIORITY	5

/*
 * Mark IPIs as higher priority so we can take them inside पूर्णांकerrupts
 * FIXME: still true now?
 */
#घोषणा IPI_PRIORITY		4

/* The least favored priority */
#घोषणा LOWEST_PRIORITY		0xFF

/* The number of priorities defined above */
#घोषणा MAX_NUM_PRIORITIES	3

/* Native ICP */
#अगर_घोषित CONFIG_PPC_ICP_NATIVE
बाह्य पूर्णांक icp_native_init(व्योम);
बाह्य व्योम icp_native_flush_पूर्णांकerrupt(व्योम);
बाह्य व्योम icp_native_cause_ipi_rm(पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत पूर्णांक icp_native_init(व्योम) अणु वापस -ENODEV; पूर्ण
#पूर्ण_अगर

/* PAPR ICP */
#अगर_घोषित CONFIG_PPC_ICP_HV
बाह्य पूर्णांक icp_hv_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक icp_hv_init(व्योम) अणु वापस -ENODEV; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_POWERNV
बाह्य पूर्णांक icp_opal_init(व्योम);
बाह्य व्योम icp_opal_flush_पूर्णांकerrupt(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक icp_opal_init(व्योम) अणु वापस -ENODEV; पूर्ण
#पूर्ण_अगर

/* ICP ops */
काष्ठा icp_ops अणु
	अचिन्हित पूर्णांक (*get_irq)(व्योम);
	व्योम (*eoi)(काष्ठा irq_data *d);
	व्योम (*set_priority)(अचिन्हित अक्षर prio);
	व्योम (*tearकरोwn_cpu)(व्योम);
	व्योम (*flush_ipi)(व्योम);
#अगर_घोषित CONFIG_SMP
	व्योम (*cause_ipi)(पूर्णांक cpu);
	irq_handler_t ipi_action;
#पूर्ण_अगर
पूर्ण;

बाह्य स्थिर काष्ठा icp_ops *icp_ops;

/* Native ICS */
बाह्य पूर्णांक ics_native_init(व्योम);

/* RTAS ICS */
#अगर_घोषित CONFIG_PPC_ICS_RTAS
बाह्य पूर्णांक ics_rtas_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक ics_rtas_init(व्योम) अणु वापस -ENODEV; पूर्ण
#पूर्ण_अगर

/* HAL ICS */
#अगर_घोषित CONFIG_PPC_POWERNV
बाह्य पूर्णांक ics_opal_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक ics_opal_init(व्योम) अणु वापस -ENODEV; पूर्ण
#पूर्ण_अगर

/* ICS instance, hooked up to chip_data of an irq */
काष्ठा ics अणु
	काष्ठा list_head link;
	पूर्णांक (*map)(काष्ठा ics *ics, अचिन्हित पूर्णांक virq);
	व्योम (*mask_unknown)(काष्ठा ics *ics, अचिन्हित दीर्घ vec);
	दीर्घ (*get_server)(काष्ठा ics *ics, अचिन्हित दीर्घ vec);
	पूर्णांक (*host_match)(काष्ठा ics *ics, काष्ठा device_node *node);
	अक्षर data[];
पूर्ण;

/* Commons */
बाह्य अचिन्हित पूर्णांक xics_शेष_server;
बाह्य अचिन्हित पूर्णांक xics_शेष_distrib_server;
बाह्य अचिन्हित पूर्णांक xics_पूर्णांकerrupt_server_size;
बाह्य काष्ठा irq_करोमुख्य *xics_host;

काष्ठा xics_cppr अणु
	अचिन्हित अक्षर stack[MAX_NUM_PRIORITIES];
	पूर्णांक index;
पूर्ण;

DECLARE_PER_CPU(काष्ठा xics_cppr, xics_cppr);

अटल अंतरभूत व्योम xics_push_cppr(अचिन्हित पूर्णांक vec)
अणु
	काष्ठा xics_cppr *os_cppr = this_cpu_ptr(&xics_cppr);

	अगर (WARN_ON(os_cppr->index >= MAX_NUM_PRIORITIES - 1))
		वापस;

	अगर (vec == XICS_IPI)
		os_cppr->stack[++os_cppr->index] = IPI_PRIORITY;
	अन्यथा
		os_cppr->stack[++os_cppr->index] = DEFAULT_PRIORITY;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर xics_pop_cppr(व्योम)
अणु
	काष्ठा xics_cppr *os_cppr = this_cpu_ptr(&xics_cppr);

	अगर (WARN_ON(os_cppr->index < 1))
		वापस LOWEST_PRIORITY;

	वापस os_cppr->stack[--os_cppr->index];
पूर्ण

अटल अंतरभूत व्योम xics_set_base_cppr(अचिन्हित अक्षर cppr)
अणु
	काष्ठा xics_cppr *os_cppr = this_cpu_ptr(&xics_cppr);

	/* we only really want to set the priority when there's
	 * just one cppr value on the stack
	 */
	WARN_ON(os_cppr->index != 0);

	os_cppr->stack[0] = cppr;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर xics_cppr_top(व्योम)
अणु
	काष्ठा xics_cppr *os_cppr = this_cpu_ptr(&xics_cppr);
	
	वापस os_cppr->stack[os_cppr->index];
पूर्ण

DECLARE_PER_CPU_SHARED_ALIGNED(अचिन्हित दीर्घ, xics_ipi_message);

बाह्य व्योम xics_init(व्योम);
बाह्य व्योम xics_setup_cpu(व्योम);
बाह्य व्योम xics_update_irq_servers(व्योम);
बाह्य व्योम xics_set_cpu_giq(अचिन्हित पूर्णांक gserver, अचिन्हित पूर्णांक join);
बाह्य व्योम xics_mask_unknown_vec(अचिन्हित पूर्णांक vec);
बाह्य irqवापस_t xics_ipi_dispatch(पूर्णांक cpu);
बाह्य व्योम xics_smp_probe(व्योम);
बाह्य व्योम xics_रेजिस्टर_ics(काष्ठा ics *ics);
बाह्य व्योम xics_tearकरोwn_cpu(व्योम);
बाह्य व्योम xics_kexec_tearकरोwn_cpu(पूर्णांक secondary);
बाह्य व्योम xics_migrate_irqs_away(व्योम);
बाह्य व्योम icp_native_eoi(काष्ठा irq_data *d);
बाह्य पूर्णांक xics_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type);
बाह्य पूर्णांक xics_retrigger(काष्ठा irq_data *data);
#अगर_घोषित CONFIG_SMP
बाह्य पूर्णांक xics_get_irq_server(अचिन्हित पूर्णांक virq, स्थिर काष्ठा cpumask *cpumask,
			       अचिन्हित पूर्णांक strict_check);
#अन्यथा
#घोषणा xics_get_irq_server(virq, cpumask, strict_check) (xics_शेष_server)
#पूर्ण_अगर


#पूर्ण_अगर /* _XICS_H */
