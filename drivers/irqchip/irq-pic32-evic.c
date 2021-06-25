<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cristian Birsan <cristian.birsan@microchip.com>
 * Joshua Henderson <joshua.henderson@microchip.com>
 * Copyright (C) 2016 Microchip Technology Inc.  All rights reserved.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/mach-pic32/pic32.h>

#घोषणा REG_INTCON	0x0000
#घोषणा REG_INTSTAT	0x0020
#घोषणा REG_IFS_OFFSET	0x0040
#घोषणा REG_IEC_OFFSET	0x00C0
#घोषणा REG_IPC_OFFSET	0x0140
#घोषणा REG_OFF_OFFSET	0x0540

#घोषणा MAJPRI_MASK	0x07
#घोषणा SUBPRI_MASK	0x03
#घोषणा PRIORITY_MASK	0x1F

#घोषणा PIC32_INT_PRI(pri, subpri)				\
	((((pri) & MAJPRI_MASK) << 2) | ((subpri) & SUBPRI_MASK))

काष्ठा evic_chip_data अणु
	u32 irq_types[NR_IRQS];
	u32 ext_irqs[8];
पूर्ण;

अटल काष्ठा irq_करोमुख्य *evic_irq_करोमुख्य;
अटल व्योम __iomem *evic_base;

यंत्रlinkage व्योम __weak plat_irq_dispatch(व्योम)
अणु
	अचिन्हित पूर्णांक irq, hwirq;

	hwirq = पढ़ोl(evic_base + REG_INTSTAT) & 0xFF;
	irq = irq_linear_revmap(evic_irq_करोमुख्य, hwirq);
	करो_IRQ(irq);
पूर्ण

अटल काष्ठा evic_chip_data *irqd_to_priv(काष्ठा irq_data *data)
अणु
	वापस (काष्ठा evic_chip_data *)data->करोमुख्य->host_data;
पूर्ण

अटल पूर्णांक pic32_set_ext_polarity(पूर्णांक bit, u32 type)
अणु
	/*
	 * External पूर्णांकerrupts can be either edge rising or edge falling,
	 * but not both.
	 */
	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		ग_लिखोl(BIT(bit), evic_base + PIC32_SET(REG_INTCON));
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		ग_लिखोl(BIT(bit), evic_base + PIC32_CLR(REG_INTCON));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pic32_set_type_edge(काष्ठा irq_data *data,
			       अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा evic_chip_data *priv = irqd_to_priv(data);
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!(flow_type & IRQ_TYPE_EDGE_BOTH))
		वापस -EBADR;

	/* set polarity क्रम बाह्यal पूर्णांकerrupts only */
	क्रम (i = 0; i < ARRAY_SIZE(priv->ext_irqs); i++) अणु
		अगर (priv->ext_irqs[i] == data->hwirq) अणु
			ret = pic32_set_ext_polarity(i, flow_type);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	irqd_set_trigger_type(data, flow_type);

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल व्योम pic32_bind_evic_पूर्णांकerrupt(पूर्णांक irq, पूर्णांक set)
अणु
	ग_लिखोl(set, evic_base + REG_OFF_OFFSET + irq * 4);
पूर्ण

अटल व्योम pic32_set_irq_priority(पूर्णांक irq, पूर्णांक priority)
अणु
	u32 reg, shअगरt;

	reg = irq / 4;
	shअगरt = (irq % 4) * 8;

	ग_लिखोl(PRIORITY_MASK << shअगरt,
		evic_base + PIC32_CLR(REG_IPC_OFFSET + reg * 0x10));
	ग_लिखोl(priority << shअगरt,
		evic_base + PIC32_SET(REG_IPC_OFFSET + reg * 0x10));
पूर्ण

#घोषणा IRQ_REG_MASK(_hwirq, _reg, _mask)		       \
	करो अणु						       \
		_reg = _hwirq / 32;			       \
		_mask = 1 << (_hwirq % 32);		       \
	पूर्ण जबतक (0)

अटल पूर्णांक pic32_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
				irq_hw_number_t hw)
अणु
	काष्ठा evic_chip_data *priv = d->host_data;
	काष्ठा irq_data *data;
	पूर्णांक ret;
	u32 iecclr, अगरsclr;
	u32 reg, mask;

	ret = irq_map_generic_chip(d, virq, hw);
	अगर (ret)
		वापस ret;

	/*
	 * Piggyback on xlate function to move to an alternate chip as necessary
	 * at समय of mapping instead of allowing the flow handler/chip to be
	 * changed later. This requires all पूर्णांकerrupts to be configured through
	 * DT.
	 */
	अगर (priv->irq_types[hw] & IRQ_TYPE_SENSE_MASK) अणु
		data = irq_करोमुख्य_get_irq_data(d, virq);
		irqd_set_trigger_type(data, priv->irq_types[hw]);
		irq_setup_alt_chip(data, priv->irq_types[hw]);
	पूर्ण

	IRQ_REG_MASK(hw, reg, mask);

	iecclr = PIC32_CLR(REG_IEC_OFFSET + reg * 0x10);
	अगरsclr = PIC32_CLR(REG_IFS_OFFSET + reg * 0x10);

	/* mask and clear flag */
	ग_लिखोl(mask, evic_base + iecclr);
	ग_लिखोl(mask, evic_base + अगरsclr);

	/* शेष priority is required */
	pic32_set_irq_priority(hw, PIC32_INT_PRI(2, 0));

	वापस ret;
पूर्ण

पूर्णांक pic32_irq_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *ctrlr,
			   स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			   irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_type)
अणु
	काष्ठा evic_chip_data *priv = d->host_data;

	अगर (WARN_ON(पूर्णांकsize < 2))
		वापस -EINVAL;

	अगर (WARN_ON(पूर्णांकspec[0] >= NR_IRQS))
		वापस -EINVAL;

	*out_hwirq = पूर्णांकspec[0];
	*out_type = पूर्णांकspec[1] & IRQ_TYPE_SENSE_MASK;

	priv->irq_types[पूर्णांकspec[0]] = पूर्णांकspec[1] & IRQ_TYPE_SENSE_MASK;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops pic32_irq_करोमुख्य_ops = अणु
	.map	= pic32_irq_करोमुख्य_map,
	.xlate	= pic32_irq_करोमुख्य_xlate,
पूर्ण;

अटल व्योम __init pic32_ext_irq_of_init(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	काष्ठा device_node *node = irq_करोमुख्य_get_of_node(करोमुख्य);
	काष्ठा evic_chip_data *priv = करोमुख्य->host_data;
	काष्ठा property *prop;
	स्थिर __le32 *p;
	u32 hwirq;
	पूर्णांक i = 0;
	स्थिर अक्षर *pname = "microchip,external-irqs";

	of_property_क्रम_each_u32(node, pname, prop, p, hwirq) अणु
		अगर (i >= ARRAY_SIZE(priv->ext_irqs)) अणु
			pr_warn("More than %d external irq, skip rest\n",
				ARRAY_SIZE(priv->ext_irqs));
			अवरोध;
		पूर्ण

		priv->ext_irqs[i] = hwirq;
		i++;
	पूर्ण
पूर्ण

अटल पूर्णांक __init pic32_of_init(काष्ठा device_node *node,
				काष्ठा device_node *parent)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा evic_chip_data *priv;
	अचिन्हित पूर्णांक clr = IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN;
	पूर्णांक nchips, ret;
	पूर्णांक i;

	nchips = DIV_ROUND_UP(NR_IRQS, 32);

	evic_base = of_iomap(node, 0);
	अगर (!evic_base)
		वापस -ENOMEM;

	priv = kसुस्मृति(nchips, माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		ret = -ENOMEM;
		जाओ err_iounmap;
	पूर्ण

	evic_irq_करोमुख्य = irq_करोमुख्य_add_linear(node, nchips * 32,
						&pic32_irq_करोमुख्य_ops,
						priv);
	अगर (!evic_irq_करोमुख्य) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_priv;
	पूर्ण

	/*
	 * The PIC32 EVIC has a linear list of irqs and the type of each
	 * irq is determined by the hardware peripheral the EVIC is arbitrating.
	 * These irq types are defined in the datasheet as "persistent" and
	 * "non-persistent" which are mapped here to level and edge
	 * respectively. To manage the dअगरferent flow handler requirements of
	 * each irq type, dअगरferent chip_types are used.
	 */
	ret = irq_alloc_करोमुख्य_generic_chips(evic_irq_करोमुख्य, 32, 2,
					     "evic-level", handle_level_irq,
					     clr, 0, 0);
	अगर (ret)
		जाओ err_करोमुख्य_हटाओ;

	board_bind_eic_पूर्णांकerrupt = &pic32_bind_evic_पूर्णांकerrupt;

	क्रम (i = 0; i < nchips; i++) अणु
		u32 अगरsclr = PIC32_CLR(REG_IFS_OFFSET + (i * 0x10));
		u32 iec = REG_IEC_OFFSET + (i * 0x10);

		gc = irq_get_करोमुख्य_generic_chip(evic_irq_करोमुख्य, i * 32);

		gc->reg_base = evic_base;
		gc->unused = 0;

		/*
		 * Level/persistent पूर्णांकerrupts have a special requirement that
		 * the condition generating the पूर्णांकerrupt be cleared beक्रमe the
		 * पूर्णांकerrupt flag (अगरs) can be cleared. chip.irq_eoi is used to
		 * complete the पूर्णांकerrupt with an ack.
		 */
		gc->chip_types[0].type			= IRQ_TYPE_LEVEL_MASK;
		gc->chip_types[0].handler		= handle_fasteoi_irq;
		gc->chip_types[0].regs.ack		= अगरsclr;
		gc->chip_types[0].regs.mask		= iec;
		gc->chip_types[0].chip.name		= "evic-level";
		gc->chip_types[0].chip.irq_eoi		= irq_gc_ack_set_bit;
		gc->chip_types[0].chip.irq_mask		= irq_gc_mask_clr_bit;
		gc->chip_types[0].chip.irq_unmask	= irq_gc_mask_set_bit;
		gc->chip_types[0].chip.flags		= IRQCHIP_SKIP_SET_WAKE;

		/* Edge पूर्णांकerrupts */
		gc->chip_types[1].type			= IRQ_TYPE_EDGE_BOTH;
		gc->chip_types[1].handler		= handle_edge_irq;
		gc->chip_types[1].regs.ack		= अगरsclr;
		gc->chip_types[1].regs.mask		= iec;
		gc->chip_types[1].chip.name		= "evic-edge";
		gc->chip_types[1].chip.irq_ack		= irq_gc_ack_set_bit;
		gc->chip_types[1].chip.irq_mask		= irq_gc_mask_clr_bit;
		gc->chip_types[1].chip.irq_unmask	= irq_gc_mask_set_bit;
		gc->chip_types[1].chip.irq_set_type	= pic32_set_type_edge;
		gc->chip_types[1].chip.flags		= IRQCHIP_SKIP_SET_WAKE;

		gc->निजी = &priv[i];
	पूर्ण

	irq_set_शेष_host(evic_irq_करोमुख्य);

	/*
	 * External पूर्णांकerrupts have software configurable edge polarity. These
	 * पूर्णांकerrupts are defined in DT allowing polarity to be configured only
	 * क्रम these पूर्णांकerrupts when requested.
	 */
	pic32_ext_irq_of_init(evic_irq_करोमुख्य);

	वापस 0;

err_करोमुख्य_हटाओ:
	irq_करोमुख्य_हटाओ(evic_irq_करोमुख्य);

err_मुक्त_priv:
	kमुक्त(priv);

err_iounmap:
	iounmap(evic_base);

	वापस ret;
पूर्ण

IRQCHIP_DECLARE(pic32_evic, "microchip,pic32mzda-evic", pic32_of_init);
