<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ARM_XEN_HYPERVISOR_H
#घोषणा _ASM_ARM_XEN_HYPERVISOR_H

#समावेश <linux/init.h>

बाह्य काष्ठा shared_info *HYPERVISOR_shared_info;
बाह्य काष्ठा start_info *xen_start_info;

/* Lazy mode क्रम batching updates / context चयन */
क्रमागत paravirt_lazy_mode अणु
	PARAVIRT_LAZY_NONE,
	PARAVIRT_LAZY_MMU,
	PARAVIRT_LAZY_CPU,
पूर्ण;

अटल अंतरभूत क्रमागत paravirt_lazy_mode paravirt_get_lazy_mode(व्योम)
अणु
	वापस PARAVIRT_LAZY_NONE;
पूर्ण

#अगर_घोषित CONFIG_XEN
व्योम __init xen_early_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम xen_early_init(व्योम) अणु वापस; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल अंतरभूत व्योम xen_arch_रेजिस्टर_cpu(पूर्णांक num)
अणु
पूर्ण

अटल अंतरभूत व्योम xen_arch_unरेजिस्टर_cpu(पूर्णांक num)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_ARM_XEN_HYPERVISOR_H */
