<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2006 IBM Corporation.
 */

#अगर_अघोषित _PSERIES_PSERIES_H
#घोषणा _PSERIES_PSERIES_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/rtas.h>

काष्ठा device_node;

बाह्य व्योम request_event_sources_irqs(काष्ठा device_node *np,
				       irq_handler_t handler, स्थिर अक्षर *name);

#समावेश <linux/of.h>

काष्ठा pt_regs;

बाह्य पूर्णांक pSeries_प्रणाली_reset_exception(काष्ठा pt_regs *regs);
बाह्य पूर्णांक pSeries_machine_check_exception(काष्ठा pt_regs *regs);
बाह्य दीर्घ pseries_machine_check_realmode(काष्ठा pt_regs *regs);

#अगर_घोषित CONFIG_SMP
बाह्य व्योम smp_init_pseries(व्योम);

/* Get state of physical CPU from query_cpu_stopped */
पूर्णांक smp_query_cpu_stopped(अचिन्हित पूर्णांक pcpu);
#घोषणा QCSS_STOPPED 0
#घोषणा QCSS_STOPPING 1
#घोषणा QCSS_NOT_STOPPED 2
#घोषणा QCSS_HARDWARE_ERROR -1
#घोषणा QCSS_HARDWARE_BUSY -2
#अन्यथा
अटल अंतरभूत व्योम smp_init_pseries(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम pseries_kexec_cpu_करोwn(पूर्णांक crash_shutकरोwn, पूर्णांक secondary);

बाह्य व्योम pSeries_final_fixup(व्योम);

/* Poweron flag used क्रम enabling स्वतः ups restart */
बाह्य अचिन्हित दीर्घ rtas_घातeron_स्वतः;

/* Dynamic logical Partitioning/Mobility */
बाह्य व्योम dlpar_मुक्त_cc_nodes(काष्ठा device_node *);
बाह्य व्योम dlpar_मुक्त_cc_property(काष्ठा property *);
बाह्य काष्ठा device_node *dlpar_configure_connector(__be32,
						काष्ठा device_node *);
बाह्य पूर्णांक dlpar_attach_node(काष्ठा device_node *, काष्ठा device_node *);
बाह्य पूर्णांक dlpar_detach_node(काष्ठा device_node *);
बाह्य पूर्णांक dlpar_acquire_drc(u32 drc_index);
बाह्य पूर्णांक dlpar_release_drc(u32 drc_index);
बाह्य पूर्णांक dlpar_unisolate_drc(u32 drc_index);

व्योम queue_hotplug_event(काष्ठा pseries_hp_errorlog *hp_errlog);
पूर्णांक handle_dlpar_errorlog(काष्ठा pseries_hp_errorlog *hp_errlog);

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
पूर्णांक dlpar_memory(काष्ठा pseries_hp_errorlog *hp_elog);
पूर्णांक dlpar_hp_pmem(काष्ठा pseries_hp_errorlog *hp_elog);
#अन्यथा
अटल अंतरभूत पूर्णांक dlpar_memory(काष्ठा pseries_hp_errorlog *hp_elog)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक dlpar_hp_pmem(काष्ठा pseries_hp_errorlog *hp_elog)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HOTPLUG_CPU
पूर्णांक dlpar_cpu(काष्ठा pseries_hp_errorlog *hp_elog);
#अन्यथा
अटल अंतरभूत पूर्णांक dlpar_cpu(काष्ठा pseries_hp_errorlog *hp_elog)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

/* PCI root bridge prepare function override क्रम pseries */
काष्ठा pci_host_bridge;
पूर्णांक pseries_root_bridge_prepare(काष्ठा pci_host_bridge *bridge);

बाह्य काष्ठा pci_controller_ops pseries_pci_controller_ops;

अचिन्हित दीर्घ pseries_memory_block_size(व्योम);

बाह्य पूर्णांक CMO_PrPSP;
बाह्य पूर्णांक CMO_SecPSP;
बाह्य अचिन्हित दीर्घ CMO_PageSize;

अटल अंतरभूत पूर्णांक cmo_get_primary_psp(व्योम)
अणु
	वापस CMO_PrPSP;
पूर्ण

अटल अंतरभूत पूर्णांक cmo_get_secondary_psp(व्योम)
अणु
	वापस CMO_SecPSP;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cmo_get_page_size(व्योम)
अणु
	वापस CMO_PageSize;
पूर्ण

पूर्णांक dlpar_workqueue_init(व्योम);

बाह्य u32 pseries_security_flavor;
व्योम pseries_setup_security_mitigations(व्योम);
व्योम pseries_lpar_पढ़ो_hblkrm_अक्षरacteristics(व्योम);

#पूर्ण_अगर /* _PSERIES_PSERIES_H */
