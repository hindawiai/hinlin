<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SH_INTC_H
#घोषणा __SH_INTC_H

#समावेश <linux/ioport.h>

#अगर_घोषित CONFIG_SUPERH
#घोषणा INTC_NR_IRQS	512
#अन्यथा
#घोषणा INTC_NR_IRQS	1024
#पूर्ण_अगर

/*
 * Convert back and क्रमth between INTEVT and IRQ values.
 */
#अगर_घोषित CONFIG_CPU_HAS_INTEVT
#घोषणा evt2irq(evt)		(((evt) >> 5) - 16)
#घोषणा irq2evt(irq)		(((irq) + 16) << 5)
#अन्यथा
#घोषणा evt2irq(evt)		(evt)
#घोषणा irq2evt(irq)		(irq)
#पूर्ण_अगर

प्रकार अचिन्हित अक्षर पूर्णांकc_क्रमागत;

काष्ठा पूर्णांकc_vect अणु
	पूर्णांकc_क्रमागत क्रमागत_id;
	अचिन्हित लघु vect;
पूर्ण;

#घोषणा INTC_VECT(क्रमागत_id, vect) अणु क्रमागत_id, vect पूर्ण
#घोषणा INTC_IRQ(क्रमागत_id, irq) INTC_VECT(क्रमागत_id, irq2evt(irq))

काष्ठा पूर्णांकc_group अणु
	पूर्णांकc_क्रमागत क्रमागत_id;
	पूर्णांकc_क्रमागत क्रमागत_ids[32];
पूर्ण;

#घोषणा INTC_GROUP(क्रमागत_id, ids...) अणु क्रमागत_id, अणु ids पूर्ण पूर्ण

काष्ठा पूर्णांकc_subgroup अणु
	अचिन्हित दीर्घ reg, reg_width;
	पूर्णांकc_क्रमागत parent_id;
	पूर्णांकc_क्रमागत क्रमागत_ids[32];
पूर्ण;

काष्ठा पूर्णांकc_mask_reg अणु
	अचिन्हित दीर्घ set_reg, clr_reg, reg_width;
	पूर्णांकc_क्रमागत क्रमागत_ids[32];
#अगर_घोषित CONFIG_INTC_BALANCING
	अचिन्हित दीर्घ dist_reg;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
	अचिन्हित दीर्घ smp;
#पूर्ण_अगर
पूर्ण;

काष्ठा पूर्णांकc_prio_reg अणु
	अचिन्हित दीर्घ set_reg, clr_reg, reg_width, field_width;
	पूर्णांकc_क्रमागत क्रमागत_ids[16];
#अगर_घोषित CONFIG_SMP
	अचिन्हित दीर्घ smp;
#पूर्ण_अगर
पूर्ण;

काष्ठा पूर्णांकc_sense_reg अणु
	अचिन्हित दीर्घ reg, reg_width, field_width;
	पूर्णांकc_क्रमागत क्रमागत_ids[16];
पूर्ण;

#अगर_घोषित CONFIG_INTC_BALANCING
#घोषणा INTC_SMP_BALANCING(reg)	.dist_reg = (reg)
#अन्यथा
#घोषणा INTC_SMP_BALANCING(reg)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
#घोषणा INTC_SMP(stride, nr)	.smp = (stride) | ((nr) << 8)
#अन्यथा
#घोषणा INTC_SMP(stride, nr)
#पूर्ण_अगर

काष्ठा पूर्णांकc_hw_desc अणु
	काष्ठा पूर्णांकc_vect *vectors;
	अचिन्हित पूर्णांक nr_vectors;
	काष्ठा पूर्णांकc_group *groups;
	अचिन्हित पूर्णांक nr_groups;
	काष्ठा पूर्णांकc_mask_reg *mask_regs;
	अचिन्हित पूर्णांक nr_mask_regs;
	काष्ठा पूर्णांकc_prio_reg *prio_regs;
	अचिन्हित पूर्णांक nr_prio_regs;
	काष्ठा पूर्णांकc_sense_reg *sense_regs;
	अचिन्हित पूर्णांक nr_sense_regs;
	काष्ठा पूर्णांकc_mask_reg *ack_regs;
	अचिन्हित पूर्णांक nr_ack_regs;
	काष्ठा पूर्णांकc_subgroup *subgroups;
	अचिन्हित पूर्णांक nr_subgroups;
पूर्ण;

#घोषणा _INTC_ARRAY(a) a, __same_type(a, शून्य) ? 0 : माप(a)/माप(*a)

#घोषणा INTC_HW_DESC(vectors, groups, mask_regs,	\
		     prio_regs,	sense_regs, ack_regs)	\
अणु							\
	_INTC_ARRAY(vectors), _INTC_ARRAY(groups),	\
	_INTC_ARRAY(mask_regs), _INTC_ARRAY(prio_regs),	\
	_INTC_ARRAY(sense_regs), _INTC_ARRAY(ack_regs),	\
पूर्ण

काष्ठा पूर्णांकc_desc अणु
	अक्षर *name;
	काष्ठा resource *resource;
	अचिन्हित पूर्णांक num_resources;
	पूर्णांकc_क्रमागत क्रमce_enable;
	पूर्णांकc_क्रमागत क्रमce_disable;
	bool skip_syscore_suspend;
	काष्ठा पूर्णांकc_hw_desc hw;
पूर्ण;

#घोषणा DECLARE_INTC_DESC(symbol, chipname, vectors, groups,		\
	mask_regs, prio_regs, sense_regs)				\
काष्ठा पूर्णांकc_desc symbol __initdata = अणु					\
	.name = chipname,						\
	.hw = INTC_HW_DESC(vectors, groups, mask_regs,			\
			   prio_regs, sense_regs, शून्य),		\
पूर्ण

#घोषणा DECLARE_INTC_DESC_ACK(symbol, chipname, vectors, groups,	\
	mask_regs, prio_regs, sense_regs, ack_regs)			\
काष्ठा पूर्णांकc_desc symbol __initdata = अणु					\
	.name = chipname,						\
	.hw = INTC_HW_DESC(vectors, groups, mask_regs,			\
			   prio_regs, sense_regs, ack_regs),		\
पूर्ण

पूर्णांक रेजिस्टर_पूर्णांकc_controller(काष्ठा पूर्णांकc_desc *desc);
पूर्णांक पूर्णांकc_set_priority(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक prio);
पूर्णांक पूर्णांकc_irq_lookup(स्थिर अक्षर *chipname, पूर्णांकc_क्रमागत क्रमागत_id);
व्योम पूर्णांकc_finalize(व्योम);

#अगर_घोषित CONFIG_INTC_USERIMASK
पूर्णांक रेजिस्टर_पूर्णांकc_userimask(अचिन्हित दीर्घ addr);
#अन्यथा
अटल अंतरभूत पूर्णांक रेजिस्टर_पूर्णांकc_userimask(अचिन्हित दीर्घ addr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __SH_INTC_H */
