<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2020, Jiaxun Yang <jiaxun.yang@flygoat.com>
 *  Loongson HyperTransport Interrupt Vector support
 */

#घोषणा pr_fmt(fmt) "htvec: " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

/* Registers */
#घोषणा HTVEC_EN_OFF		0x20
#घोषणा HTVEC_MAX_PARENT_IRQ	8

#घोषणा VEC_COUNT_PER_REG	32
#घोषणा VEC_REG_IDX(irq_id)	((irq_id) / VEC_COUNT_PER_REG)
#घोषणा VEC_REG_BIT(irq_id)	((irq_id) % VEC_COUNT_PER_REG)

काष्ठा htvec अणु
	पूर्णांक			num_parents;
	व्योम __iomem		*base;
	काष्ठा irq_करोमुख्य	*htvec_करोमुख्य;
	raw_spinlock_t		htvec_lock;
पूर्ण;

अटल व्योम htvec_irq_dispatch(काष्ठा irq_desc *desc)
अणु
	पूर्णांक i;
	u32 pending;
	bool handled = false;
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा htvec *priv = irq_desc_get_handler_data(desc);

	chained_irq_enter(chip, desc);

	क्रम (i = 0; i < priv->num_parents; i++) अणु
		pending = पढ़ोl(priv->base + 4 * i);
		जबतक (pending) अणु
			पूर्णांक bit = __ffs(pending);

			generic_handle_irq(irq_linear_revmap(priv->htvec_करोमुख्य, bit +
							     VEC_COUNT_PER_REG * i));
			pending &= ~BIT(bit);
			handled = true;
		पूर्ण
	पूर्ण

	अगर (!handled)
		spurious_पूर्णांकerrupt();

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम htvec_ack_irq(काष्ठा irq_data *d)
अणु
	काष्ठा htvec *priv = irq_data_get_irq_chip_data(d);

	ग_लिखोl(BIT(VEC_REG_BIT(d->hwirq)),
	       priv->base + VEC_REG_IDX(d->hwirq) * 4);
पूर्ण

अटल व्योम htvec_mask_irq(काष्ठा irq_data *d)
अणु
	u32 reg;
	व्योम __iomem *addr;
	काष्ठा htvec *priv = irq_data_get_irq_chip_data(d);

	raw_spin_lock(&priv->htvec_lock);
	addr = priv->base + HTVEC_EN_OFF;
	addr += VEC_REG_IDX(d->hwirq) * 4;
	reg = पढ़ोl(addr);
	reg &= ~BIT(VEC_REG_BIT(d->hwirq));
	ग_लिखोl(reg, addr);
	raw_spin_unlock(&priv->htvec_lock);
पूर्ण

अटल व्योम htvec_unmask_irq(काष्ठा irq_data *d)
अणु
	u32 reg;
	व्योम __iomem *addr;
	काष्ठा htvec *priv = irq_data_get_irq_chip_data(d);

	raw_spin_lock(&priv->htvec_lock);
	addr = priv->base + HTVEC_EN_OFF;
	addr += VEC_REG_IDX(d->hwirq) * 4;
	reg = पढ़ोl(addr);
	reg |= BIT(VEC_REG_BIT(d->hwirq));
	ग_लिखोl(reg, addr);
	raw_spin_unlock(&priv->htvec_lock);
पूर्ण

अटल काष्ठा irq_chip htvec_irq_chip = अणु
	.name			= "LOONGSON_HTVEC",
	.irq_mask		= htvec_mask_irq,
	.irq_unmask		= htvec_unmask_irq,
	.irq_ack		= htvec_ack_irq,
पूर्ण;

अटल पूर्णांक htvec_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			      अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ hwirq;
	अचिन्हित पूर्णांक type, i;
	काष्ठा htvec *priv = करोमुख्य->host_data;

	ret = irq_करोमुख्य_translate_onecell(करोमुख्य, arg, &hwirq, &type);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_करोमुख्य_set_info(करोमुख्य, virq + i, hwirq + i, &htvec_irq_chip,
				    priv, handle_edge_irq, शून्य, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम htvec_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				  अचिन्हित पूर्णांक nr_irqs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq + i);

		irq_set_handler(virq + i, शून्य);
		irq_करोमुख्य_reset_irq_data(d);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops htvec_करोमुख्य_ops = अणु
	.translate	= irq_करोमुख्य_translate_onecell,
	.alloc		= htvec_करोमुख्य_alloc,
	.मुक्त		= htvec_करोमुख्य_मुक्त,
पूर्ण;

अटल व्योम htvec_reset(काष्ठा htvec *priv)
अणु
	u32 idx;

	/* Clear IRQ cause रेजिस्टरs, mask all पूर्णांकerrupts */
	क्रम (idx = 0; idx < priv->num_parents; idx++) अणु
		ग_लिखोl_relaxed(0x0, priv->base + HTVEC_EN_OFF + 4 * idx);
		ग_लिखोl_relaxed(0xFFFFFFFF, priv->base + 4 * idx);
	पूर्ण
पूर्ण

अटल पूर्णांक htvec_of_init(काष्ठा device_node *node,
				काष्ठा device_node *parent)
अणु
	काष्ठा htvec *priv;
	पूर्णांक err, parent_irq[8], i;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	raw_spin_lock_init(&priv->htvec_lock);
	priv->base = of_iomap(node, 0);
	अगर (!priv->base) अणु
		err = -ENOMEM;
		जाओ मुक्त_priv;
	पूर्ण

	/* Interrupt may come from any of the 8 पूर्णांकerrupt lines */
	क्रम (i = 0; i < HTVEC_MAX_PARENT_IRQ; i++) अणु
		parent_irq[i] = irq_of_parse_and_map(node, i);
		अगर (parent_irq[i] <= 0)
			अवरोध;

		priv->num_parents++;
	पूर्ण

	अगर (!priv->num_parents) अणु
		pr_err("Failed to get parent irqs\n");
		err = -ENODEV;
		जाओ iounmap_base;
	पूर्ण

	priv->htvec_करोमुख्य = irq_करोमुख्य_create_linear(of_node_to_fwnode(node),
					(VEC_COUNT_PER_REG * priv->num_parents),
					&htvec_करोमुख्य_ops, priv);
	अगर (!priv->htvec_करोमुख्य) अणु
		pr_err("Failed to create IRQ domain\n");
		err = -ENOMEM;
		जाओ irq_dispose;
	पूर्ण

	htvec_reset(priv);

	क्रम (i = 0; i < priv->num_parents; i++)
		irq_set_chained_handler_and_data(parent_irq[i],
						 htvec_irq_dispatch, priv);

	वापस 0;

irq_dispose:
	क्रम (; i > 0; i--)
		irq_dispose_mapping(parent_irq[i - 1]);
iounmap_base:
	iounmap(priv->base);
मुक्त_priv:
	kमुक्त(priv);

	वापस err;
पूर्ण

IRQCHIP_DECLARE(htvec, "loongson,htvec-1.0", htvec_of_init);
