<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2020, Jiaxun Yang <jiaxun.yang@flygoat.com>
 *  Loongson Local IO Interrupt Controller support
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/smp.h>
#समावेश <linux/irqchip/chained_irq.h>

#समावेश <loongson.h>

#घोषणा LIOINTC_CHIP_IRQ	32
#घोषणा LIOINTC_NUM_PARENT 4
#घोषणा LIOINTC_NUM_CORES	4

#घोषणा LIOINTC_INTC_CHIP_START	0x20

#घोषणा LIOINTC_REG_INTC_STATUS	(LIOINTC_INTC_CHIP_START + 0x20)
#घोषणा LIOINTC_REG_INTC_EN_STATUS	(LIOINTC_INTC_CHIP_START + 0x04)
#घोषणा LIOINTC_REG_INTC_ENABLE	(LIOINTC_INTC_CHIP_START + 0x08)
#घोषणा LIOINTC_REG_INTC_DISABLE	(LIOINTC_INTC_CHIP_START + 0x0c)
#घोषणा LIOINTC_REG_INTC_POL	(LIOINTC_INTC_CHIP_START + 0x10)
#घोषणा LIOINTC_REG_INTC_EDGE	(LIOINTC_INTC_CHIP_START + 0x14)

#घोषणा LIOINTC_SHIFT_INTx	4

#घोषणा LIOINTC_ERRATA_IRQ	10

काष्ठा lioपूर्णांकc_handler_data अणु
	काष्ठा lioपूर्णांकc_priv	*priv;
	u32			parent_पूर्णांक_map;
पूर्ण;

काष्ठा lioपूर्णांकc_priv अणु
	काष्ठा irq_chip_generic		*gc;
	काष्ठा lioपूर्णांकc_handler_data	handler[LIOINTC_NUM_PARENT];
	व्योम __iomem			*core_isr[LIOINTC_NUM_CORES];
	u8				map_cache[LIOINTC_CHIP_IRQ];
	bool				has_lpc_irq_errata;
पूर्ण;

अटल व्योम lioपूर्णांकc_chained_handle_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा lioपूर्णांकc_handler_data *handler = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा irq_chip_generic *gc = handler->priv->gc;
	पूर्णांक core = get_ebase_cpunum() % LIOINTC_NUM_CORES;
	u32 pending;

	chained_irq_enter(chip, desc);

	pending = पढ़ोl(handler->priv->core_isr[core]);

	अगर (!pending) अणु
		/* Always blame LPC IRQ अगर we have that bug */
		अगर (handler->priv->has_lpc_irq_errata &&
			(handler->parent_पूर्णांक_map & gc->mask_cache &
			BIT(LIOINTC_ERRATA_IRQ)))
			pending = BIT(LIOINTC_ERRATA_IRQ);
		अन्यथा
			spurious_पूर्णांकerrupt();
	पूर्ण

	जबतक (pending) अणु
		पूर्णांक bit = __ffs(pending);

		generic_handle_irq(irq_find_mapping(gc->करोमुख्य, bit));
		pending &= ~BIT(bit);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम lioपूर्णांकc_set_bit(काष्ठा irq_chip_generic *gc,
				अचिन्हित पूर्णांक offset,
				u32 mask, bool set)
अणु
	अगर (set)
		ग_लिखोl(पढ़ोl(gc->reg_base + offset) | mask,
				gc->reg_base + offset);
	अन्यथा
		ग_लिखोl(पढ़ोl(gc->reg_base + offset) & ~mask,
				gc->reg_base + offset);
पूर्ण

अटल पूर्णांक lioपूर्णांकc_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(data);
	u32 mask = data->mask;
	अचिन्हित दीर्घ flags;

	irq_gc_lock_irqsave(gc, flags);
	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		lioपूर्णांकc_set_bit(gc, LIOINTC_REG_INTC_EDGE, mask, false);
		lioपूर्णांकc_set_bit(gc, LIOINTC_REG_INTC_POL, mask, true);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		lioपूर्णांकc_set_bit(gc, LIOINTC_REG_INTC_EDGE, mask, false);
		lioपूर्णांकc_set_bit(gc, LIOINTC_REG_INTC_POL, mask, false);
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		lioपूर्णांकc_set_bit(gc, LIOINTC_REG_INTC_EDGE, mask, true);
		lioपूर्णांकc_set_bit(gc, LIOINTC_REG_INTC_POL, mask, true);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		lioपूर्णांकc_set_bit(gc, LIOINTC_REG_INTC_EDGE, mask, true);
		lioपूर्णांकc_set_bit(gc, LIOINTC_REG_INTC_POL, mask, false);
		अवरोध;
	शेष:
		irq_gc_unlock_irqrestore(gc, flags);
		वापस -EINVAL;
	पूर्ण
	irq_gc_unlock_irqrestore(gc, flags);

	irqd_set_trigger_type(data, type);
	वापस 0;
पूर्ण

अटल व्योम lioपूर्णांकc_resume(काष्ठा irq_chip_generic *gc)
अणु
	काष्ठा lioपूर्णांकc_priv *priv = gc->निजी;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	irq_gc_lock_irqsave(gc, flags);
	/* Disable all at first */
	ग_लिखोl(0xffffffff, gc->reg_base + LIOINTC_REG_INTC_DISABLE);
	/* Restore map cache */
	क्रम (i = 0; i < LIOINTC_CHIP_IRQ; i++)
		ग_लिखोb(priv->map_cache[i], gc->reg_base + i);
	/* Restore mask cache */
	ग_लिखोl(gc->mask_cache, gc->reg_base + LIOINTC_REG_INTC_ENABLE);
	irq_gc_unlock_irqrestore(gc, flags);
पूर्ण

अटल स्थिर अक्षर * स्थिर parent_names[] = अणु"int0", "int1", "int2", "int3"पूर्ण;
अटल स्थिर अक्षर * स्थिर core_reg_names[] = अणु"isr0", "isr1", "isr2", "isr3"पूर्ण;

अटल व्योम __iomem *lioपूर्णांकc_get_reg_byname(काष्ठा device_node *node,
						स्थिर अक्षर *name)
अणु
	पूर्णांक index = of_property_match_string(node, "reg-names", name);

	अगर (index < 0)
		वापस शून्य;

	वापस of_iomap(node, index);
पूर्ण

अटल पूर्णांक __init lioपूर्णांकc_of_init(काष्ठा device_node *node,
				  काष्ठा device_node *parent)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा irq_chip_type *ct;
	काष्ठा lioपूर्णांकc_priv *priv;
	व्योम __iomem *base;
	u32 of_parent_पूर्णांक_map[LIOINTC_NUM_PARENT];
	पूर्णांक parent_irq[LIOINTC_NUM_PARENT];
	bool have_parent = FALSE;
	पूर्णांक sz, i, err = 0;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (of_device_is_compatible(node, "loongson,liointc-2.0")) अणु
		base = lioपूर्णांकc_get_reg_byname(node, "main");
		अगर (!base) अणु
			err = -ENODEV;
			जाओ out_मुक्त_priv;
		पूर्ण

		क्रम (i = 0; i < LIOINTC_NUM_CORES; i++)
			priv->core_isr[i] = lioपूर्णांकc_get_reg_byname(node, core_reg_names[i]);
		अगर (!priv->core_isr[0]) अणु
			err = -ENODEV;
			जाओ out_iounmap_base;
		पूर्ण
	पूर्ण अन्यथा अणु
		base = of_iomap(node, 0);
		अगर (!base) अणु
			err = -ENODEV;
			जाओ out_मुक्त_priv;
		पूर्ण

		क्रम (i = 0; i < LIOINTC_NUM_CORES; i++)
			priv->core_isr[i] = base + LIOINTC_REG_INTC_STATUS;
	पूर्ण

	क्रम (i = 0; i < LIOINTC_NUM_PARENT; i++) अणु
		parent_irq[i] = of_irq_get_byname(node, parent_names[i]);
		अगर (parent_irq[i] > 0)
			have_parent = TRUE;
	पूर्ण
	अगर (!have_parent) अणु
		err = -ENODEV;
		जाओ out_iounmap_isr;
	पूर्ण

	sz = of_property_पढ़ो_variable_u32_array(node,
						"loongson,parent_int_map",
						&of_parent_पूर्णांक_map[0],
						LIOINTC_NUM_PARENT,
						LIOINTC_NUM_PARENT);
	अगर (sz < 4) अणु
		pr_err("loongson-liointc: No parent_int_map\n");
		err = -ENODEV;
		जाओ out_iounmap_isr;
	पूर्ण

	क्रम (i = 0; i < LIOINTC_NUM_PARENT; i++)
		priv->handler[i].parent_पूर्णांक_map = of_parent_पूर्णांक_map[i];

	/* Setup IRQ करोमुख्य */
	करोमुख्य = irq_करोमुख्य_add_linear(node, 32,
					&irq_generic_chip_ops, priv);
	अगर (!करोमुख्य) अणु
		pr_err("loongson-liointc: cannot add IRQ domain\n");
		err = -EINVAL;
		जाओ out_iounmap_isr;
	पूर्ण

	err = irq_alloc_करोमुख्य_generic_chips(करोमुख्य, 32, 1,
					node->full_name, handle_level_irq,
					IRQ_NOPROBE, 0, 0);
	अगर (err) अणु
		pr_err("loongson-liointc: unable to register IRQ domain\n");
		जाओ out_मुक्त_करोमुख्य;
	पूर्ण


	/* Disable all IRQs */
	ग_लिखोl(0xffffffff, base + LIOINTC_REG_INTC_DISABLE);
	/* Set to level triggered */
	ग_लिखोl(0x0, base + LIOINTC_REG_INTC_EDGE);

	/* Generate parent INT part of map cache */
	क्रम (i = 0; i < LIOINTC_NUM_PARENT; i++) अणु
		u32 pending = priv->handler[i].parent_पूर्णांक_map;

		जबतक (pending) अणु
			पूर्णांक bit = __ffs(pending);

			priv->map_cache[bit] = BIT(i) << LIOINTC_SHIFT_INTx;
			pending &= ~BIT(bit);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < LIOINTC_CHIP_IRQ; i++) अणु
		/* Generate core part of map cache */
		priv->map_cache[i] |= BIT(loongson_sysconf.boot_cpu_id);
		ग_लिखोb(priv->map_cache[i], base + i);
	पूर्ण

	gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	gc->निजी = priv;
	gc->reg_base = base;
	gc->करोमुख्य = करोमुख्य;
	gc->resume = lioपूर्णांकc_resume;

	ct = gc->chip_types;
	ct->regs.enable = LIOINTC_REG_INTC_ENABLE;
	ct->regs.disable = LIOINTC_REG_INTC_DISABLE;
	ct->chip.irq_unmask = irq_gc_unmask_enable_reg;
	ct->chip.irq_mask = irq_gc_mask_disable_reg;
	ct->chip.irq_mask_ack = irq_gc_mask_disable_reg;
	ct->chip.irq_set_type = lioपूर्णांकc_set_type;

	gc->mask_cache = 0;
	priv->gc = gc;

	क्रम (i = 0; i < LIOINTC_NUM_PARENT; i++) अणु
		अगर (parent_irq[i] <= 0)
			जारी;

		priv->handler[i].priv = priv;
		irq_set_chained_handler_and_data(parent_irq[i],
				lioपूर्णांकc_chained_handle_irq, &priv->handler[i]);
	पूर्ण

	वापस 0;

out_मुक्त_करोमुख्य:
	irq_करोमुख्य_हटाओ(करोमुख्य);
out_iounmap_isr:
	क्रम (i = 0; i < LIOINTC_NUM_CORES; i++) अणु
		अगर (!priv->core_isr[i])
			जारी;
		iounmap(priv->core_isr[i]);
	पूर्ण
out_iounmap_base:
	iounmap(base);
out_मुक्त_priv:
	kमुक्त(priv);

	वापस err;
पूर्ण

IRQCHIP_DECLARE(loongson_lioपूर्णांकc_1_0, "loongson,liointc-1.0", lioपूर्णांकc_of_init);
IRQCHIP_DECLARE(loongson_lioपूर्णांकc_1_0a, "loongson,liointc-1.0a", lioपूर्णांकc_of_init);
IRQCHIP_DECLARE(loongson_lioपूर्णांकc_2_0, "loongson,liointc-2.0", lioपूर्णांकc_of_init);
