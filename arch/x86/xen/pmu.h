<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __XEN_PMU_H
#घोषणा __XEN_PMU_H

#समावेश <xen/पूर्णांकerface/xenpmu.h>

irqवापस_t xen_pmu_irq_handler(पूर्णांक irq, व्योम *dev_id);
#अगर_घोषित CONFIG_XEN_HAVE_VPMU
व्योम xen_pmu_init(पूर्णांक cpu);
व्योम xen_pmu_finish(पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत व्योम xen_pmu_init(पूर्णांक cpu) अणुपूर्ण
अटल अंतरभूत व्योम xen_pmu_finish(पूर्णांक cpu) अणुपूर्ण
#पूर्ण_अगर
bool is_xen_pmu(पूर्णांक cpu);
bool pmu_msr_पढ़ो(अचिन्हित पूर्णांक msr, uपूर्णांक64_t *val, पूर्णांक *err);
bool pmu_msr_ग_लिखो(अचिन्हित पूर्णांक msr, uपूर्णांक32_t low, uपूर्णांक32_t high, पूर्णांक *err);
पूर्णांक pmu_apic_update(uपूर्णांक32_t reg);
अचिन्हित दीर्घ दीर्घ xen_पढ़ो_pmc(पूर्णांक counter);

#पूर्ण_अगर /* __XEN_PMU_H */
