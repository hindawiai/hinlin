<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Combiner irqchip क्रम EXYNOS
 */
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#घोषणा COMBINER_ENABLE_SET	0x0
#घोषणा COMBINER_ENABLE_CLEAR	0x4
#घोषणा COMBINER_INT_STATUS	0xC

#घोषणा IRQ_IN_COMBINER		8

अटल DEFINE_SPINLOCK(irq_controller_lock);

काष्ठा combiner_chip_data अणु
	अचिन्हित पूर्णांक hwirq_offset;
	अचिन्हित पूर्णांक irq_mask;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक parent_irq;
#अगर_घोषित CONFIG_PM
	u32 pm_save;
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा combiner_chip_data *combiner_data;
अटल काष्ठा irq_करोमुख्य *combiner_irq_करोमुख्य;
अटल अचिन्हित पूर्णांक max_nr = 20;

अटल अंतरभूत व्योम __iomem *combiner_base(काष्ठा irq_data *data)
अणु
	काष्ठा combiner_chip_data *combiner_data =
		irq_data_get_irq_chip_data(data);

	वापस combiner_data->base;
पूर्ण

अटल व्योम combiner_mask_irq(काष्ठा irq_data *data)
अणु
	u32 mask = 1 << (data->hwirq % 32);

	ग_लिखोl_relaxed(mask, combiner_base(data) + COMBINER_ENABLE_CLEAR);
पूर्ण

अटल व्योम combiner_unmask_irq(काष्ठा irq_data *data)
अणु
	u32 mask = 1 << (data->hwirq % 32);

	ग_लिखोl_relaxed(mask, combiner_base(data) + COMBINER_ENABLE_SET);
पूर्ण

अटल व्योम combiner_handle_cascade_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा combiner_chip_data *chip_data = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक cascade_irq, combiner_irq;
	अचिन्हित दीर्घ status;

	chained_irq_enter(chip, desc);

	spin_lock(&irq_controller_lock);
	status = पढ़ोl_relaxed(chip_data->base + COMBINER_INT_STATUS);
	spin_unlock(&irq_controller_lock);
	status &= chip_data->irq_mask;

	अगर (status == 0)
		जाओ out;

	combiner_irq = chip_data->hwirq_offset + __ffs(status);
	cascade_irq = irq_find_mapping(combiner_irq_करोमुख्य, combiner_irq);

	अगर (unlikely(!cascade_irq))
		handle_bad_irq(desc);
	अन्यथा
		generic_handle_irq(cascade_irq);

 out:
	chained_irq_निकास(chip, desc);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक combiner_set_affinity(काष्ठा irq_data *d,
				 स्थिर काष्ठा cpumask *mask_val, bool क्रमce)
अणु
	काष्ठा combiner_chip_data *chip_data = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip *chip = irq_get_chip(chip_data->parent_irq);
	काष्ठा irq_data *data = irq_get_irq_data(chip_data->parent_irq);

	अगर (chip && chip->irq_set_affinity)
		वापस chip->irq_set_affinity(data, mask_val, क्रमce);
	अन्यथा
		वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा irq_chip combiner_chip = अणु
	.name			= "COMBINER",
	.irq_mask		= combiner_mask_irq,
	.irq_unmask		= combiner_unmask_irq,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	= combiner_set_affinity,
#पूर्ण_अगर
पूर्ण;

अटल व्योम __init combiner_cascade_irq(काष्ठा combiner_chip_data *combiner_data,
					अचिन्हित पूर्णांक irq)
अणु
	irq_set_chained_handler_and_data(irq, combiner_handle_cascade_irq,
					 combiner_data);
पूर्ण

अटल व्योम __init combiner_init_one(काष्ठा combiner_chip_data *combiner_data,
				     अचिन्हित पूर्णांक combiner_nr,
				     व्योम __iomem *base, अचिन्हित पूर्णांक irq)
अणु
	combiner_data->base = base;
	combiner_data->hwirq_offset = (combiner_nr & ~3) * IRQ_IN_COMBINER;
	combiner_data->irq_mask = 0xff << ((combiner_nr % 4) << 3);
	combiner_data->parent_irq = irq;

	/* Disable all पूर्णांकerrupts */
	ग_लिखोl_relaxed(combiner_data->irq_mask, base + COMBINER_ENABLE_CLEAR);
पूर्ण

अटल पूर्णांक combiner_irq_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d,
				     काष्ठा device_node *controller,
				     स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
				     अचिन्हित दीर्घ *out_hwirq,
				     अचिन्हित पूर्णांक *out_type)
अणु
	अगर (irq_करोमुख्य_get_of_node(d) != controller)
		वापस -EINVAL;

	अगर (पूर्णांकsize < 2)
		वापस -EINVAL;

	*out_hwirq = पूर्णांकspec[0] * IRQ_IN_COMBINER + पूर्णांकspec[1];
	*out_type = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक combiner_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				   irq_hw_number_t hw)
अणु
	काष्ठा combiner_chip_data *combiner_data = d->host_data;

	irq_set_chip_and_handler(irq, &combiner_chip, handle_level_irq);
	irq_set_chip_data(irq, &combiner_data[hw >> 3]);
	irq_set_probe(irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops combiner_irq_करोमुख्य_ops = अणु
	.xlate	= combiner_irq_करोमुख्य_xlate,
	.map	= combiner_irq_करोमुख्य_map,
पूर्ण;

अटल व्योम __init combiner_init(व्योम __iomem *combiner_base,
				 काष्ठा device_node *np)
अणु
	पूर्णांक i, irq;
	अचिन्हित पूर्णांक nr_irq;

	nr_irq = max_nr * IRQ_IN_COMBINER;

	combiner_data = kसुस्मृति(max_nr, माप (*combiner_data), GFP_KERNEL);
	अगर (!combiner_data) अणु
		pr_warn("%s: could not allocate combiner data\n", __func__);
		वापस;
	पूर्ण

	combiner_irq_करोमुख्य = irq_करोमुख्य_add_linear(np, nr_irq,
				&combiner_irq_करोमुख्य_ops, combiner_data);
	अगर (WARN_ON(!combiner_irq_करोमुख्य)) अणु
		pr_warn("%s: irq domain init failed\n", __func__);
		वापस;
	पूर्ण

	क्रम (i = 0; i < max_nr; i++) अणु
		irq = irq_of_parse_and_map(np, i);

		combiner_init_one(&combiner_data[i], i,
				  combiner_base + (i >> 2) * 0x10, irq);
		combiner_cascade_irq(&combiner_data[i], irq);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM

/**
 * combiner_suspend - save पूर्णांकerrupt combiner state beक्रमe suspend
 *
 * Save the पूर्णांकerrupt enable set रेजिस्टर क्रम all combiner groups since
 * the state is lost when the प्रणाली enters पूर्णांकo a sleep state.
 *
 */
अटल पूर्णांक combiner_suspend(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < max_nr; i++)
		combiner_data[i].pm_save =
			पढ़ोl_relaxed(combiner_data[i].base + COMBINER_ENABLE_SET);

	वापस 0;
पूर्ण

/**
 * combiner_resume - restore पूर्णांकerrupt combiner state after resume
 *
 * Restore the पूर्णांकerrupt enable set रेजिस्टर क्रम all combiner groups since
 * the state is lost when the प्रणाली enters पूर्णांकo a sleep state on suspend.
 *
 */
अटल व्योम combiner_resume(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < max_nr; i++) अणु
		ग_लिखोl_relaxed(combiner_data[i].irq_mask,
			     combiner_data[i].base + COMBINER_ENABLE_CLEAR);
		ग_लिखोl_relaxed(combiner_data[i].pm_save,
			     combiner_data[i].base + COMBINER_ENABLE_SET);
	पूर्ण
पूर्ण

#अन्यथा
#घोषणा combiner_suspend	शून्य
#घोषणा combiner_resume		शून्य
#पूर्ण_अगर

अटल काष्ठा syscore_ops combiner_syscore_ops = अणु
	.suspend	= combiner_suspend,
	.resume		= combiner_resume,
पूर्ण;

अटल पूर्णांक __init combiner_of_init(काष्ठा device_node *np,
				   काष्ठा device_node *parent)
अणु
	व्योम __iomem *combiner_base;

	combiner_base = of_iomap(np, 0);
	अगर (!combiner_base) अणु
		pr_err("%s: failed to map combiner registers\n", __func__);
		वापस -ENXIO;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "samsung,combiner-nr", &max_nr)) अणु
		pr_info("%s: number of combiners not specified, "
			"setting default as %d.\n",
			__func__, max_nr);
	पूर्ण

	combiner_init(combiner_base, np);

	रेजिस्टर_syscore_ops(&combiner_syscore_ops);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(exynos4210_combiner, "samsung,exynos4210-combiner",
		combiner_of_init);
