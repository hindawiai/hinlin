<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2020, Jiaxun Yang <jiaxun.yang@flygoat.com>
 *  Loongson PCH PIC support
 */

#घोषणा pr_fmt(fmt) "pch-pic: " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

/* Registers */
#घोषणा PCH_PIC_MASK		0x20
#घोषणा PCH_PIC_HTMSI_EN	0x40
#घोषणा PCH_PIC_EDGE		0x60
#घोषणा PCH_PIC_CLR		0x80
#घोषणा PCH_PIC_AUTO0		0xc0
#घोषणा PCH_PIC_AUTO1		0xe0
#घोषणा PCH_INT_ROUTE(irq)	(0x100 + irq)
#घोषणा PCH_INT_HTVEC(irq)	(0x200 + irq)
#घोषणा PCH_PIC_POL		0x3e0

#घोषणा PIC_COUNT_PER_REG	32
#घोषणा PIC_REG_COUNT		2
#घोषणा PIC_COUNT		(PIC_COUNT_PER_REG * PIC_REG_COUNT)
#घोषणा PIC_REG_IDX(irq_id)	((irq_id) / PIC_COUNT_PER_REG)
#घोषणा PIC_REG_BIT(irq_id)	((irq_id) % PIC_COUNT_PER_REG)

काष्ठा pch_pic अणु
	व्योम __iomem		*base;
	काष्ठा irq_करोमुख्य	*pic_करोमुख्य;
	u32			ht_vec_base;
	raw_spinlock_t		pic_lock;
पूर्ण;

अटल व्योम pch_pic_bitset(काष्ठा pch_pic *priv, पूर्णांक offset, पूर्णांक bit)
अणु
	u32 reg;
	व्योम __iomem *addr = priv->base + offset + PIC_REG_IDX(bit) * 4;

	raw_spin_lock(&priv->pic_lock);
	reg = पढ़ोl(addr);
	reg |= BIT(PIC_REG_BIT(bit));
	ग_लिखोl(reg, addr);
	raw_spin_unlock(&priv->pic_lock);
पूर्ण

अटल व्योम pch_pic_bitclr(काष्ठा pch_pic *priv, पूर्णांक offset, पूर्णांक bit)
अणु
	u32 reg;
	व्योम __iomem *addr = priv->base + offset + PIC_REG_IDX(bit) * 4;

	raw_spin_lock(&priv->pic_lock);
	reg = पढ़ोl(addr);
	reg &= ~BIT(PIC_REG_BIT(bit));
	ग_लिखोl(reg, addr);
	raw_spin_unlock(&priv->pic_lock);
पूर्ण

अटल व्योम pch_pic_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा pch_pic *priv = irq_data_get_irq_chip_data(d);

	pch_pic_bitset(priv, PCH_PIC_MASK, d->hwirq);
	irq_chip_mask_parent(d);
पूर्ण

अटल व्योम pch_pic_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा pch_pic *priv = irq_data_get_irq_chip_data(d);

	ग_लिखोl(BIT(PIC_REG_BIT(d->hwirq)),
			priv->base + PCH_PIC_CLR + PIC_REG_IDX(d->hwirq) * 4);

	irq_chip_unmask_parent(d);
	pch_pic_bitclr(priv, PCH_PIC_MASK, d->hwirq);
पूर्ण

अटल पूर्णांक pch_pic_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा pch_pic *priv = irq_data_get_irq_chip_data(d);
	पूर्णांक ret = 0;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		pch_pic_bitset(priv, PCH_PIC_EDGE, d->hwirq);
		pch_pic_bitclr(priv, PCH_PIC_POL, d->hwirq);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		pch_pic_bitset(priv, PCH_PIC_EDGE, d->hwirq);
		pch_pic_bitset(priv, PCH_PIC_POL, d->hwirq);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		pch_pic_bitclr(priv, PCH_PIC_EDGE, d->hwirq);
		pch_pic_bitclr(priv, PCH_PIC_POL, d->hwirq);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		pch_pic_bitclr(priv, PCH_PIC_EDGE, d->hwirq);
		pch_pic_bitset(priv, PCH_PIC_POL, d->hwirq);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा irq_chip pch_pic_irq_chip = अणु
	.name			= "PCH PIC",
	.irq_mask		= pch_pic_mask_irq,
	.irq_unmask		= pch_pic_unmask_irq,
	.irq_ack		= irq_chip_ack_parent,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
	.irq_set_type		= pch_pic_set_type,
पूर्ण;

अटल पूर्णांक pch_pic_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			      अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक type;
	अचिन्हित दीर्घ hwirq;
	काष्ठा irq_fwspec *fwspec = arg;
	काष्ठा irq_fwspec parent_fwspec;
	काष्ठा pch_pic *priv = करोमुख्य->host_data;

	err = irq_करोमुख्य_translate_twocell(करोमुख्य, fwspec, &hwirq, &type);
	अगर (err)
		वापस err;

	parent_fwspec.fwnode = करोमुख्य->parent->fwnode;
	parent_fwspec.param_count = 1;
	parent_fwspec.param[0] = hwirq + priv->ht_vec_base;

	err = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &parent_fwspec);
	अगर (err)
		वापस err;

	irq_करोमुख्य_set_info(करोमुख्य, virq, hwirq,
			    &pch_pic_irq_chip, priv,
			    handle_level_irq, शून्य, शून्य);
	irq_set_probe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops pch_pic_करोमुख्य_ops = अणु
	.translate	= irq_करोमुख्य_translate_twocell,
	.alloc		= pch_pic_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_parent,
पूर्ण;

अटल व्योम pch_pic_reset(काष्ठा pch_pic *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PIC_COUNT; i++) अणु
		/* Write vectored ID */
		ग_लिखोb(priv->ht_vec_base + i, priv->base + PCH_INT_HTVEC(i));
		/* Hardcode route to HT0 Lo */
		ग_लिखोb(1, priv->base + PCH_INT_ROUTE(i));
	पूर्ण

	क्रम (i = 0; i < PIC_REG_COUNT; i++) अणु
		/* Clear IRQ cause रेजिस्टरs, mask all पूर्णांकerrupts */
		ग_लिखोl_relaxed(0xFFFFFFFF, priv->base + PCH_PIC_MASK + 4 * i);
		ग_लिखोl_relaxed(0xFFFFFFFF, priv->base + PCH_PIC_CLR + 4 * i);
		/* Clear स्वतः bounce, we करोn't need that */
		ग_लिखोl_relaxed(0, priv->base + PCH_PIC_AUTO0 + 4 * i);
		ग_लिखोl_relaxed(0, priv->base + PCH_PIC_AUTO1 + 4 * i);
		/* Enable HTMSI transक्रमmer */
		ग_लिखोl_relaxed(0xFFFFFFFF, priv->base + PCH_PIC_HTMSI_EN + 4 * i);
	पूर्ण
पूर्ण

अटल पूर्णांक pch_pic_of_init(काष्ठा device_node *node,
				काष्ठा device_node *parent)
अणु
	काष्ठा pch_pic *priv;
	काष्ठा irq_करोमुख्य *parent_करोमुख्य;
	पूर्णांक err;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	raw_spin_lock_init(&priv->pic_lock);
	priv->base = of_iomap(node, 0);
	अगर (!priv->base) अणु
		err = -ENOMEM;
		जाओ मुक्त_priv;
	पूर्ण

	parent_करोमुख्य = irq_find_host(parent);
	अगर (!parent_करोमुख्य) अणु
		pr_err("Failed to find the parent domain\n");
		err = -ENXIO;
		जाओ iounmap_base;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "loongson,pic-base-vec",
				&priv->ht_vec_base)) अणु
		pr_err("Failed to determine pic-base-vec\n");
		err = -EINVAL;
		जाओ iounmap_base;
	पूर्ण

	priv->pic_करोमुख्य = irq_करोमुख्य_create_hierarchy(parent_करोमुख्य, 0,
						       PIC_COUNT,
						       of_node_to_fwnode(node),
						       &pch_pic_करोमुख्य_ops,
						       priv);
	अगर (!priv->pic_करोमुख्य) अणु
		pr_err("Failed to create IRQ domain\n");
		err = -ENOMEM;
		जाओ iounmap_base;
	पूर्ण

	pch_pic_reset(priv);

	वापस 0;

iounmap_base:
	iounmap(priv->base);
मुक्त_priv:
	kमुक्त(priv);

	वापस err;
पूर्ण

IRQCHIP_DECLARE(pch_pic, "loongson,pch-pic-1.0", pch_pic_of_init);
