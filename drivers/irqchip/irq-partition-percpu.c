<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 ARM Limited, All Rights Reserved.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqchip/irq-partition-percpu.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

काष्ठा partition_desc अणु
	पूर्णांक				nr_parts;
	काष्ठा partition_affinity	*parts;
	काष्ठा irq_करोमुख्य		*करोमुख्य;
	काष्ठा irq_desc			*chained_desc;
	अचिन्हित दीर्घ			*biपंचांगap;
	काष्ठा irq_करोमुख्य_ops		ops;
पूर्ण;

अटल bool partition_check_cpu(काष्ठा partition_desc *part,
				अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक hwirq)
अणु
	वापस cpumask_test_cpu(cpu, &part->parts[hwirq].mask);
पूर्ण

अटल व्योम partition_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा partition_desc *part = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip *chip = irq_desc_get_chip(part->chained_desc);
	काष्ठा irq_data *data = irq_desc_get_irq_data(part->chained_desc);

	अगर (partition_check_cpu(part, smp_processor_id(), d->hwirq) &&
	    chip->irq_mask)
		chip->irq_mask(data);
पूर्ण

अटल व्योम partition_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा partition_desc *part = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip *chip = irq_desc_get_chip(part->chained_desc);
	काष्ठा irq_data *data = irq_desc_get_irq_data(part->chained_desc);

	अगर (partition_check_cpu(part, smp_processor_id(), d->hwirq) &&
	    chip->irq_unmask)
		chip->irq_unmask(data);
पूर्ण

अटल पूर्णांक partition_irq_set_irqchip_state(काष्ठा irq_data *d,
					   क्रमागत irqchip_irq_state which,
					   bool val)
अणु
	काष्ठा partition_desc *part = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip *chip = irq_desc_get_chip(part->chained_desc);
	काष्ठा irq_data *data = irq_desc_get_irq_data(part->chained_desc);

	अगर (partition_check_cpu(part, smp_processor_id(), d->hwirq) &&
	    chip->irq_set_irqchip_state)
		वापस chip->irq_set_irqchip_state(data, which, val);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक partition_irq_get_irqchip_state(काष्ठा irq_data *d,
					   क्रमागत irqchip_irq_state which,
					   bool *val)
अणु
	काष्ठा partition_desc *part = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip *chip = irq_desc_get_chip(part->chained_desc);
	काष्ठा irq_data *data = irq_desc_get_irq_data(part->chained_desc);

	अगर (partition_check_cpu(part, smp_processor_id(), d->hwirq) &&
	    chip->irq_get_irqchip_state)
		वापस chip->irq_get_irqchip_state(data, which, val);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक partition_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा partition_desc *part = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip *chip = irq_desc_get_chip(part->chained_desc);
	काष्ठा irq_data *data = irq_desc_get_irq_data(part->chained_desc);

	अगर (chip->irq_set_type)
		वापस chip->irq_set_type(data, type);

	वापस -EINVAL;
पूर्ण

अटल व्योम partition_irq_prपूर्णांक_chip(काष्ठा irq_data *d, काष्ठा seq_file *p)
अणु
	काष्ठा partition_desc *part = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip *chip = irq_desc_get_chip(part->chained_desc);
	काष्ठा irq_data *data = irq_desc_get_irq_data(part->chained_desc);

	seq_म_लिखो(p, " %5s-%lu", chip->name, data->hwirq);
पूर्ण

अटल काष्ठा irq_chip partition_irq_chip = अणु
	.irq_mask		= partition_irq_mask,
	.irq_unmask		= partition_irq_unmask,
	.irq_set_type		= partition_irq_set_type,
	.irq_get_irqchip_state	= partition_irq_get_irqchip_state,
	.irq_set_irqchip_state	= partition_irq_set_irqchip_state,
	.irq_prपूर्णांक_chip		= partition_irq_prपूर्णांक_chip,
पूर्ण;

अटल व्योम partition_handle_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा partition_desc *part = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक hwirq;

	chained_irq_enter(chip, desc);

	क्रम_each_set_bit(hwirq, part->biपंचांगap, part->nr_parts) अणु
		अगर (partition_check_cpu(part, cpu, hwirq))
			अवरोध;
	पूर्ण

	अगर (unlikely(hwirq == part->nr_parts)) अणु
		handle_bad_irq(desc);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक irq;
		irq = irq_find_mapping(part->करोमुख्य, hwirq);
		generic_handle_irq(irq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक partition_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				  अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	पूर्णांक ret;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type;
	काष्ठा irq_fwspec *fwspec = arg;
	काष्ठा partition_desc *part;

	BUG_ON(nr_irqs != 1);
	ret = करोमुख्य->ops->translate(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	part = करोमुख्य->host_data;

	set_bit(hwirq, part->biपंचांगap);
	irq_set_chained_handler_and_data(irq_desc_get_irq(part->chained_desc),
					 partition_handle_irq, part);
	irq_set_percpu_devid_partition(virq, &part->parts[hwirq].mask);
	irq_करोमुख्य_set_info(करोमुख्य, virq, hwirq, &partition_irq_chip, part,
			    handle_percpu_devid_irq, शून्य, शून्य);
	irq_set_status_flags(virq, IRQ_NOAUTOEN);

	वापस 0;
पूर्ण

अटल व्योम partition_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				  अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d;

	BUG_ON(nr_irqs != 1);

	d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	irq_set_handler(virq, शून्य);
	irq_करोमुख्य_reset_irq_data(d);
पूर्ण

पूर्णांक partition_translate_id(काष्ठा partition_desc *desc, व्योम *partition_id)
अणु
	काष्ठा partition_affinity *part = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < desc->nr_parts; i++) अणु
		अगर (desc->parts[i].partition_id == partition_id) अणु
			part = &desc->parts[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (WARN_ON(!part)) अणु
		pr_err("Failed to find partition\n");
		वापस -EINVAL;
	पूर्ण

	वापस i;
पूर्ण

काष्ठा partition_desc *partition_create_desc(काष्ठा fwnode_handle *fwnode,
					     काष्ठा partition_affinity *parts,
					     पूर्णांक nr_parts,
					     पूर्णांक chained_irq,
					     स्थिर काष्ठा irq_करोमुख्य_ops *ops)
अणु
	काष्ठा partition_desc *desc;
	काष्ठा irq_करोमुख्य *d;

	BUG_ON(!ops->select || !ops->translate);

	desc = kzalloc(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस शून्य;

	desc->ops = *ops;
	desc->ops.मुक्त = partition_करोमुख्य_मुक्त;
	desc->ops.alloc = partition_करोमुख्य_alloc;

	d = irq_करोमुख्य_create_linear(fwnode, nr_parts, &desc->ops, desc);
	अगर (!d)
		जाओ out;
	desc->करोमुख्य = d;

	desc->biपंचांगap = kसुस्मृति(BITS_TO_LONGS(nr_parts), माप(दीर्घ),
			       GFP_KERNEL);
	अगर (WARN_ON(!desc->biपंचांगap))
		जाओ out;

	desc->chained_desc = irq_to_desc(chained_irq);
	desc->nr_parts = nr_parts;
	desc->parts = parts;

	वापस desc;
out:
	अगर (d)
		irq_करोमुख्य_हटाओ(d);
	kमुक्त(desc);

	वापस शून्य;
पूर्ण

काष्ठा irq_करोमुख्य *partition_get_करोमुख्य(काष्ठा partition_desc *dsc)
अणु
	अगर (dsc)
		वापस dsc->करोमुख्य;

	वापस शून्य;
पूर्ण
