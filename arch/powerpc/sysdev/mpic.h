<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _POWERPC_SYSDEV_MPIC_H
#घोषणा _POWERPC_SYSDEV_MPIC_H

/*
 * Copyright 2006-2007, Michael Ellerman, IBM Corporation.
 */

#अगर_घोषित CONFIG_PCI_MSI
बाह्य व्योम mpic_msi_reserve_hwirq(काष्ठा mpic *mpic, irq_hw_number_t hwirq);
बाह्य पूर्णांक mpic_msi_init_allocator(काष्ठा mpic *mpic);
बाह्य पूर्णांक mpic_u3msi_init(काष्ठा mpic *mpic);
#अन्यथा
अटल अंतरभूत व्योम mpic_msi_reserve_hwirq(काष्ठा mpic *mpic,
					  irq_hw_number_t hwirq)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक mpic_u3msi_init(काष्ठा mpic *mpic)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PCI_MSI) && defined(CONFIG_PPC_PASEMI)
पूर्णांक mpic_pasemi_msi_init(काष्ठा mpic *mpic);
#अन्यथा
अटल अंतरभूत पूर्णांक mpic_pasemi_msi_init(काष्ठा mpic *mpic) अणु वापस -1; पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक mpic_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type);
बाह्य व्योम mpic_set_vector(अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक vector);
बाह्य पूर्णांक mpic_set_affinity(काष्ठा irq_data *d,
			     स्थिर काष्ठा cpumask *cpumask, bool क्रमce);
बाह्य व्योम mpic_reset_core(पूर्णांक cpu);

#अगर_घोषित CONFIG_FSL_SOC
बाह्य पूर्णांक mpic_map_error_पूर्णांक(काष्ठा mpic *mpic, अचिन्हित पूर्णांक virq, irq_hw_number_t  hw);
बाह्य व्योम mpic_err_पूर्णांक_init(काष्ठा mpic *mpic, irq_hw_number_t irqnum);
बाह्य पूर्णांक mpic_setup_error_पूर्णांक(काष्ठा mpic *mpic, पूर्णांक पूर्णांकvec);
#अन्यथा
अटल अंतरभूत पूर्णांक mpic_map_error_पूर्णांक(काष्ठा mpic *mpic, अचिन्हित पूर्णांक virq, irq_hw_number_t  hw)
अणु
	वापस 0;
पूर्ण


अटल अंतरभूत व्योम mpic_err_पूर्णांक_init(काष्ठा mpic *mpic, irq_hw_number_t irqnum)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक mpic_setup_error_पूर्णांक(काष्ठा mpic *mpic, पूर्णांक पूर्णांकvec)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _POWERPC_SYSDEV_MPIC_H */
