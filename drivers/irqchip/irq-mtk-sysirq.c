<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Joe.C <yingjoe.chen@mediatek.com>
 */

#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

काष्ठा mtk_sysirq_chip_data अणु
	raw_spinlock_t lock;
	u32 nr_पूर्णांकpol_bases;
	व्योम __iomem **पूर्णांकpol_bases;
	u32 *पूर्णांकpol_words;
	u8 *पूर्णांकpol_idx;
	u16 *which_word;
पूर्ण;

अटल पूर्णांक mtk_sysirq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	irq_hw_number_t hwirq = data->hwirq;
	काष्ठा mtk_sysirq_chip_data *chip_data = data->chip_data;
	u8 पूर्णांकpol_idx = chip_data->पूर्णांकpol_idx[hwirq];
	व्योम __iomem *base;
	u32 offset, reg_index, value;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	base = chip_data->पूर्णांकpol_bases[पूर्णांकpol_idx];
	reg_index = chip_data->which_word[hwirq];
	offset = hwirq & 0x1f;

	raw_spin_lock_irqsave(&chip_data->lock, flags);
	value = पढ़ोl_relaxed(base + reg_index * 4);
	अगर (type == IRQ_TYPE_LEVEL_LOW || type == IRQ_TYPE_EDGE_FALLING) अणु
		अगर (type == IRQ_TYPE_LEVEL_LOW)
			type = IRQ_TYPE_LEVEL_HIGH;
		अन्यथा
			type = IRQ_TYPE_EDGE_RISING;
		value |= (1 << offset);
	पूर्ण अन्यथा अणु
		value &= ~(1 << offset);
	पूर्ण

	ग_लिखोl_relaxed(value, base + reg_index * 4);

	data = data->parent_data;
	ret = data->chip->irq_set_type(data, type);
	raw_spin_unlock_irqrestore(&chip_data->lock, flags);
	वापस ret;
पूर्ण

अटल काष्ठा irq_chip mtk_sysirq_chip = अणु
	.name			= "MT_SYSIRQ",
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_type		= mtk_sysirq_set_type,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
पूर्ण;

अटल पूर्णांक mtk_sysirq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
				       काष्ठा irq_fwspec *fwspec,
				       अचिन्हित दीर्घ *hwirq,
				       अचिन्हित पूर्णांक *type)
अणु
	अगर (is_of_node(fwspec->fwnode)) अणु
		अगर (fwspec->param_count != 3)
			वापस -EINVAL;

		/* No PPI should poपूर्णांक to this करोमुख्य */
		अगर (fwspec->param[0] != 0)
			वापस -EINVAL;

		*hwirq = fwspec->param[1];
		*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mtk_sysirq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				   अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	पूर्णांक i;
	irq_hw_number_t hwirq;
	काष्ठा irq_fwspec *fwspec = arg;
	काष्ठा irq_fwspec gic_fwspec = *fwspec;

	अगर (fwspec->param_count != 3)
		वापस -EINVAL;

	/* sysirq करोesn't support PPI */
	अगर (fwspec->param[0])
		वापस -EINVAL;

	hwirq = fwspec->param[1];
	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, hwirq + i,
					      &mtk_sysirq_chip,
					      करोमुख्य->host_data);

	gic_fwspec.fwnode = करोमुख्य->parent->fwnode;
	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs, &gic_fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops sysirq_करोमुख्य_ops = अणु
	.translate	= mtk_sysirq_करोमुख्य_translate,
	.alloc		= mtk_sysirq_करोमुख्य_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

अटल पूर्णांक __init mtk_sysirq_of_init(काष्ठा device_node *node,
				     काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य, *करोमुख्य_parent;
	काष्ठा mtk_sysirq_chip_data *chip_data;
	पूर्णांक ret, size, पूर्णांकpol_num = 0, nr_पूर्णांकpol_bases = 0, i = 0;

	करोमुख्य_parent = irq_find_host(parent);
	अगर (!करोमुख्य_parent) अणु
		pr_err("mtk_sysirq: interrupt-parent not found\n");
		वापस -EINVAL;
	पूर्ण

	chip_data = kzalloc(माप(*chip_data), GFP_KERNEL);
	अगर (!chip_data)
		वापस -ENOMEM;

	जबतक (of_get_address(node, i++, शून्य, शून्य))
		nr_पूर्णांकpol_bases++;

	अगर (nr_पूर्णांकpol_bases == 0) अणु
		pr_err("mtk_sysirq: base address not specified\n");
		ret = -EINVAL;
		जाओ out_मुक्त_chip;
	पूर्ण

	chip_data->पूर्णांकpol_words = kसुस्मृति(nr_पूर्णांकpol_bases,
					  माप(*chip_data->पूर्णांकpol_words),
					  GFP_KERNEL);
	अगर (!chip_data->पूर्णांकpol_words) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_chip;
	पूर्ण

	chip_data->पूर्णांकpol_bases = kसुस्मृति(nr_पूर्णांकpol_bases,
					  माप(*chip_data->पूर्णांकpol_bases),
					  GFP_KERNEL);
	अगर (!chip_data->पूर्णांकpol_bases) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_पूर्णांकpol_words;
	पूर्ण

	क्रम (i = 0; i < nr_पूर्णांकpol_bases; i++) अणु
		काष्ठा resource res;

		ret = of_address_to_resource(node, i, &res);
		size = resource_size(&res);
		पूर्णांकpol_num += size * 8;
		chip_data->पूर्णांकpol_words[i] = size / 4;
		chip_data->पूर्णांकpol_bases[i] = of_iomap(node, i);
		अगर (ret || !chip_data->पूर्णांकpol_bases[i]) अणु
			pr_err("%pOF: couldn't map region %d\n", node, i);
			ret = -ENODEV;
			जाओ out_मुक्त_पूर्णांकpol;
		पूर्ण
	पूर्ण

	chip_data->पूर्णांकpol_idx = kसुस्मृति(पूर्णांकpol_num,
					माप(*chip_data->पूर्णांकpol_idx),
					GFP_KERNEL);
	अगर (!chip_data->पूर्णांकpol_idx) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_पूर्णांकpol;
	पूर्ण

	chip_data->which_word = kसुस्मृति(पूर्णांकpol_num,
					माप(*chip_data->which_word),
					GFP_KERNEL);
	अगर (!chip_data->which_word) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_पूर्णांकpol_idx;
	पूर्ण

	/*
	 * assign an index of the पूर्णांकpol_bases क्रम each irq
	 * to set it fast later
	 */
	क्रम (i = 0; i < पूर्णांकpol_num ; i++) अणु
		u32 word = i / 32, j;

		क्रम (j = 0; word >= chip_data->पूर्णांकpol_words[j] ; j++)
			word -= chip_data->पूर्णांकpol_words[j];

		chip_data->पूर्णांकpol_idx[i] = j;
		chip_data->which_word[i] = word;
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_hierarchy(करोमुख्य_parent, 0, पूर्णांकpol_num, node,
					  &sysirq_करोमुख्य_ops, chip_data);
	अगर (!करोमुख्य) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_which_word;
	पूर्ण
	raw_spin_lock_init(&chip_data->lock);

	वापस 0;

out_मुक्त_which_word:
	kमुक्त(chip_data->which_word);
out_मुक्त_पूर्णांकpol_idx:
	kमुक्त(chip_data->पूर्णांकpol_idx);
out_मुक्त_पूर्णांकpol:
	क्रम (i = 0; i < nr_पूर्णांकpol_bases; i++)
		अगर (chip_data->पूर्णांकpol_bases[i])
			iounmap(chip_data->पूर्णांकpol_bases[i]);
	kमुक्त(chip_data->पूर्णांकpol_bases);
out_मुक्त_पूर्णांकpol_words:
	kमुक्त(chip_data->पूर्णांकpol_words);
out_मुक्त_chip:
	kमुक्त(chip_data);
	वापस ret;
पूर्ण
IRQCHIP_DECLARE(mtk_sysirq, "mediatek,mt6577-sysirq", mtk_sysirq_of_init);
