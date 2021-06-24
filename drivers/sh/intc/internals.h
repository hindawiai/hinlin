<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/device.h>

#घोषणा _INTC_MK(fn, mode, addr_e, addr_d, width, shअगरt) \
	((shअगरt) | ((width) << 5) | ((fn) << 9) | ((mode) << 13) | \
	 ((addr_e) << 16) | ((addr_d << 24)))

#घोषणा _INTC_SHIFT(h)		(h & 0x1f)
#घोषणा _INTC_WIDTH(h)		((h >> 5) & 0xf)
#घोषणा _INTC_FN(h)		((h >> 9) & 0xf)
#घोषणा _INTC_MODE(h)		((h >> 13) & 0x7)
#घोषणा _INTC_ADDR_E(h)		((h >> 16) & 0xff)
#घोषणा _INTC_ADDR_D(h)		((h >> 24) & 0xff)

#अगर_घोषित CONFIG_SMP
#घोषणा IS_SMP(x)		(x.smp)
#घोषणा INTC_REG(d, x, c)	(d->reg[(x)] + ((d->smp[(x)] & 0xff) * c))
#घोषणा SMP_NR(d, x)		((d->smp[(x)] >> 8) ? (d->smp[(x)] >> 8) : 1)
#अन्यथा
#घोषणा IS_SMP(x)		0
#घोषणा INTC_REG(d, x, c)	(d->reg[(x)])
#घोषणा SMP_NR(d, x)		1
#पूर्ण_अगर

काष्ठा पूर्णांकc_handle_पूर्णांक अणु
	अचिन्हित पूर्णांक irq;
	अचिन्हित दीर्घ handle;
पूर्ण;

काष्ठा पूर्णांकc_winकरोw अणु
	phys_addr_t phys;
	व्योम __iomem *virt;
	अचिन्हित दीर्घ size;
पूर्ण;

काष्ठा पूर्णांकc_map_entry अणु
	पूर्णांकc_क्रमागत क्रमागत_id;
	काष्ठा पूर्णांकc_desc_पूर्णांक *desc;
पूर्ण;

काष्ठा पूर्णांकc_subgroup_entry अणु
	अचिन्हित पूर्णांक pirq;
	पूर्णांकc_क्रमागत क्रमागत_id;
	अचिन्हित दीर्घ handle;
पूर्ण;

काष्ठा पूर्णांकc_desc_पूर्णांक अणु
	काष्ठा list_head list;
	काष्ठा device dev;
	काष्ठा radix_tree_root tree;
	raw_spinlock_t lock;
	अचिन्हित पूर्णांक index;
	अचिन्हित दीर्घ *reg;
#अगर_घोषित CONFIG_SMP
	अचिन्हित दीर्घ *smp;
#पूर्ण_अगर
	अचिन्हित पूर्णांक nr_reg;
	काष्ठा पूर्णांकc_handle_पूर्णांक *prio;
	अचिन्हित पूर्णांक nr_prio;
	काष्ठा पूर्णांकc_handle_पूर्णांक *sense;
	अचिन्हित पूर्णांक nr_sense;
	काष्ठा पूर्णांकc_winकरोw *winकरोw;
	अचिन्हित पूर्णांक nr_winकरोws;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा irq_chip chip;
	bool skip_suspend;
पूर्ण;


क्रमागत अणु
	REG_FN_ERR = 0,
	REG_FN_TEST_BASE = 1,
	REG_FN_WRITE_BASE = 5,
	REG_FN_MODIFY_BASE = 9
पूर्ण;

क्रमागत अणु	MODE_ENABLE_REG = 0, /* Bit(s) set -> पूर्णांकerrupt enabled */
	MODE_MASK_REG,       /* Bit(s) set -> पूर्णांकerrupt disabled */
	MODE_DUAL_REG,       /* Two रेजिस्टरs, set bit to enable / disable */
	MODE_PRIO_REG,       /* Priority value written to enable पूर्णांकerrupt */
	MODE_PCLR_REG,       /* Above plus all bits set to disable पूर्णांकerrupt */
पूर्ण;

अटल अंतरभूत काष्ठा पूर्णांकc_desc_पूर्णांक *get_पूर्णांकc_desc(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_chip *chip = irq_get_chip(irq);

	वापस container_of(chip, काष्ठा पूर्णांकc_desc_पूर्णांक, chip);
पूर्ण

/*
 * Grumble.
 */
अटल अंतरभूत व्योम activate_irq(पूर्णांक irq)
अणु
	irq_modअगरy_status(irq, IRQ_NOREQUEST, IRQ_NOPROBE);
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकc_handle_पूर्णांक_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा पूर्णांकc_handle_पूर्णांक *_a = a;
	स्थिर काष्ठा पूर्णांकc_handle_पूर्णांक *_b = b;

	वापस _a->irq - _b->irq;
पूर्ण

/* access.c */
बाह्य अचिन्हित दीर्घ
(*पूर्णांकc_reg_fns[])(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ h, अचिन्हित दीर्घ data);

बाह्य अचिन्हित दीर्घ
(*पूर्णांकc_enable_fns[])(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ handle,
		     अचिन्हित दीर्घ (*fn)(अचिन्हित दीर्घ,
				अचिन्हित दीर्घ, अचिन्हित दीर्घ),
		     अचिन्हित पूर्णांक irq);
बाह्य अचिन्हित दीर्घ
(*पूर्णांकc_disable_fns[])(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ handle,
		      अचिन्हित दीर्घ (*fn)(अचिन्हित दीर्घ,
				अचिन्हित दीर्घ, अचिन्हित दीर्घ),
		      अचिन्हित पूर्णांक irq);
बाह्य अचिन्हित दीर्घ
(*पूर्णांकc_enable_noprio_fns[])(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ handle,
		            अचिन्हित दीर्घ (*fn)(अचिन्हित दीर्घ,
				अचिन्हित दीर्घ, अचिन्हित दीर्घ),
			    अचिन्हित पूर्णांक irq);

अचिन्हित दीर्घ पूर्णांकc_phys_to_virt(काष्ठा पूर्णांकc_desc_पूर्णांक *d, अचिन्हित दीर्घ address);
अचिन्हित पूर्णांक पूर्णांकc_get_reg(काष्ठा पूर्णांकc_desc_पूर्णांक *d, अचिन्हित दीर्घ address);
अचिन्हित पूर्णांक पूर्णांकc_set_field_from_handle(अचिन्हित पूर्णांक value,
			    अचिन्हित पूर्णांक field_value,
			    अचिन्हित पूर्णांक handle);
अचिन्हित दीर्घ पूर्णांकc_get_field_from_handle(अचिन्हित पूर्णांक value,
					 अचिन्हित पूर्णांक handle);

/* balancing.c */
#अगर_घोषित CONFIG_INTC_BALANCING
व्योम पूर्णांकc_balancing_enable(अचिन्हित पूर्णांक irq);
व्योम पूर्णांकc_balancing_disable(अचिन्हित पूर्णांक irq);
व्योम पूर्णांकc_set_dist_handle(अचिन्हित पूर्णांक irq, काष्ठा पूर्णांकc_desc *desc,
			  काष्ठा पूर्णांकc_desc_पूर्णांक *d, पूर्णांकc_क्रमागत id);
#अन्यथा
अटल अंतरभूत व्योम पूर्णांकc_balancing_enable(अचिन्हित पूर्णांक irq) अणु पूर्ण
अटल अंतरभूत व्योम पूर्णांकc_balancing_disable(अचिन्हित पूर्णांक irq) अणु पूर्ण
अटल अंतरभूत व्योम
पूर्णांकc_set_dist_handle(अचिन्हित पूर्णांक irq, काष्ठा पूर्णांकc_desc *desc,
		     काष्ठा पूर्णांकc_desc_पूर्णांक *d, पूर्णांकc_क्रमागत id) अणु पूर्ण
#पूर्ण_अगर

/* chip.c */
बाह्य काष्ठा irq_chip पूर्णांकc_irq_chip;
व्योम _पूर्णांकc_enable(काष्ठा irq_data *data, अचिन्हित दीर्घ handle);

/* core.c */
बाह्य काष्ठा list_head पूर्णांकc_list;
बाह्य raw_spinlock_t पूर्णांकc_big_lock;
बाह्य काष्ठा bus_type पूर्णांकc_subsys;

अचिन्हित पूर्णांक पूर्णांकc_get_dfl_prio_level(व्योम);
अचिन्हित पूर्णांक पूर्णांकc_get_prio_level(अचिन्हित पूर्णांक irq);
व्योम पूर्णांकc_set_prio_level(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक level);

/* handle.c */
अचिन्हित पूर्णांक पूर्णांकc_get_mask_handle(काष्ठा पूर्णांकc_desc *desc,
				  काष्ठा पूर्णांकc_desc_पूर्णांक *d,
				  पूर्णांकc_क्रमागत क्रमागत_id, पूर्णांक करो_grps);
अचिन्हित पूर्णांक पूर्णांकc_get_prio_handle(काष्ठा पूर्णांकc_desc *desc,
				  काष्ठा पूर्णांकc_desc_पूर्णांक *d,
				  पूर्णांकc_क्रमागत क्रमागत_id, पूर्णांक करो_grps);
अचिन्हित पूर्णांक पूर्णांकc_get_sense_handle(काष्ठा पूर्णांकc_desc *desc,
				   काष्ठा पूर्णांकc_desc_पूर्णांक *d,
				   पूर्णांकc_क्रमागत क्रमागत_id);
व्योम पूर्णांकc_set_ack_handle(अचिन्हित पूर्णांक irq, काष्ठा पूर्णांकc_desc *desc,
			 काष्ठा पूर्णांकc_desc_पूर्णांक *d, पूर्णांकc_क्रमागत id);
अचिन्हित दीर्घ पूर्णांकc_get_ack_handle(अचिन्हित पूर्णांक irq);
व्योम पूर्णांकc_enable_disable_क्रमागत(काष्ठा पूर्णांकc_desc *desc, काष्ठा पूर्णांकc_desc_पूर्णांक *d,
			      पूर्णांकc_क्रमागत क्रमागत_id, पूर्णांक enable);

/* irqकरोमुख्य.c */
व्योम पूर्णांकc_irq_करोमुख्य_init(काष्ठा पूर्णांकc_desc_पूर्णांक *d, काष्ठा पूर्णांकc_hw_desc *hw);

/* virq.c */
व्योम पूर्णांकc_subgroup_init(काष्ठा पूर्णांकc_desc *desc, काष्ठा पूर्णांकc_desc_पूर्णांक *d);
व्योम पूर्णांकc_irq_xlate_set(अचिन्हित पूर्णांक irq, पूर्णांकc_क्रमागत id, काष्ठा पूर्णांकc_desc_पूर्णांक *d);
काष्ठा पूर्णांकc_map_entry *पूर्णांकc_irq_xlate_get(अचिन्हित पूर्णांक irq);
