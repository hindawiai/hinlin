<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

/*
 * Driver क्रम पूर्णांकerrupt combiners in the Top-level Control and Status
 * Registers (TCSR) hardware block in Qualcomm Technologies chips.
 * An पूर्णांकerrupt combiner in this block combines a set of पूर्णांकerrupts by
 * OR'ing the inभागidual पूर्णांकerrupt संकेतs पूर्णांकo a summary पूर्णांकerrupt
 * संकेत routed to a parent पूर्णांकerrupt controller, and provides पढ़ो-
 * only, 32-bit रेजिस्टरs to query the status of inभागidual पूर्णांकerrupts.
 * The status bit क्रम IRQ n is bit (n % 32) within रेजिस्टर (n / 32)
 * of the given combiner. Thus, each combiner can be described as a set
 * of रेजिस्टर offsets and the number of IRQs managed.
 */

#घोषणा pr_fmt(fmt) "QCOM80B1:" fmt

#समावेश <linux/acpi.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा REG_SIZE 32

काष्ठा combiner_reg अणु
	व्योम __iomem *addr;
	अचिन्हित दीर्घ enabled;
पूर्ण;

काष्ठा combiner अणु
	काष्ठा irq_करोमुख्य   *करोमुख्य;
	पूर्णांक                 parent_irq;
	u32                 nirqs;
	u32                 nregs;
	काष्ठा combiner_reg regs[];
पूर्ण;

अटल अंतरभूत पूर्णांक irq_nr(u32 reg, u32 bit)
अणु
	वापस reg * REG_SIZE + bit;
पूर्ण

/*
 * Handler क्रम the cascaded IRQ.
 */
अटल व्योम combiner_handle_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा combiner *combiner = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	u32 reg;

	chained_irq_enter(chip, desc);

	क्रम (reg = 0; reg < combiner->nregs; reg++) अणु
		पूर्णांक virq;
		पूर्णांक hwirq;
		u32 bit;
		u32 status;

		bit = पढ़ोl_relaxed(combiner->regs[reg].addr);
		status = bit & combiner->regs[reg].enabled;
		अगर (bit && !status)
			pr_warn_ratelimited("Unexpected IRQ on CPU%d: (%08x %08lx %p)\n",
					    smp_processor_id(), bit,
					    combiner->regs[reg].enabled,
					    combiner->regs[reg].addr);

		जबतक (status) अणु
			bit = __ffs(status);
			status &= ~(1 << bit);
			hwirq = irq_nr(reg, bit);
			virq = irq_find_mapping(combiner->करोमुख्य, hwirq);
			अगर (virq > 0)
				generic_handle_irq(virq);

		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम combiner_irq_chip_mask_irq(काष्ठा irq_data *data)
अणु
	काष्ठा combiner *combiner = irq_data_get_irq_chip_data(data);
	काष्ठा combiner_reg *reg = combiner->regs + data->hwirq / REG_SIZE;

	clear_bit(data->hwirq % REG_SIZE, &reg->enabled);
पूर्ण

अटल व्योम combiner_irq_chip_unmask_irq(काष्ठा irq_data *data)
अणु
	काष्ठा combiner *combiner = irq_data_get_irq_chip_data(data);
	काष्ठा combiner_reg *reg = combiner->regs + data->hwirq / REG_SIZE;

	set_bit(data->hwirq % REG_SIZE, &reg->enabled);
पूर्ण

अटल काष्ठा irq_chip irq_chip = अणु
	.irq_mask = combiner_irq_chip_mask_irq,
	.irq_unmask = combiner_irq_chip_unmask_irq,
	.name = "qcom-irq-combiner"
पूर्ण;

अटल पूर्णांक combiner_irq_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
				   irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &irq_chip, handle_level_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);
	irq_set_noprobe(irq);
	वापस 0;
पूर्ण

अटल व्योम combiner_irq_unmap(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq)
अणु
	irq_करोमुख्य_reset_irq_data(irq_get_irq_data(irq));
पूर्ण

अटल पूर्णांक combiner_irq_translate(काष्ठा irq_करोमुख्य *d, काष्ठा irq_fwspec *fws,
				  अचिन्हित दीर्घ *hwirq, अचिन्हित पूर्णांक *type)
अणु
	काष्ठा combiner *combiner = d->host_data;

	अगर (is_acpi_node(fws->fwnode)) अणु
		अगर (WARN_ON((fws->param_count != 2) ||
			    (fws->param[0] >= combiner->nirqs) ||
			    (fws->param[1] & IORESOURCE_IRQ_LOWEDGE) ||
			    (fws->param[1] & IORESOURCE_IRQ_HIGHEDGE)))
			वापस -EINVAL;

		*hwirq = fws->param[0];
		*type = fws->param[1];
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops करोमुख्य_ops = अणु
	.map = combiner_irq_map,
	.unmap = combiner_irq_unmap,
	.translate = combiner_irq_translate
पूर्ण;

अटल acpi_status count_रेजिस्टरs_cb(काष्ठा acpi_resource *ares, व्योम *context)
अणु
	पूर्णांक *count = context;

	अगर (ares->type == ACPI_RESOURCE_TYPE_GENERIC_REGISTER)
		++(*count);
	वापस AE_OK;
पूर्ण

अटल पूर्णांक count_रेजिस्टरs(काष्ठा platक्रमm_device *pdev)
अणु
	acpi_handle ahandle = ACPI_HANDLE(&pdev->dev);
	acpi_status status;
	पूर्णांक count = 0;

	अगर (!acpi_has_method(ahandle, METHOD_NAME__CRS))
		वापस -EINVAL;

	status = acpi_walk_resources(ahandle, METHOD_NAME__CRS,
				     count_रेजिस्टरs_cb, &count);
	अगर (ACPI_FAILURE(status))
		वापस -EINVAL;
	वापस count;
पूर्ण

काष्ठा get_रेजिस्टरs_context अणु
	काष्ठा device *dev;
	काष्ठा combiner *combiner;
	पूर्णांक err;
पूर्ण;

अटल acpi_status get_रेजिस्टरs_cb(काष्ठा acpi_resource *ares, व्योम *context)
अणु
	काष्ठा get_रेजिस्टरs_context *ctx = context;
	काष्ठा acpi_resource_generic_रेजिस्टर *reg;
	phys_addr_t paddr;
	व्योम __iomem *vaddr;

	अगर (ares->type != ACPI_RESOURCE_TYPE_GENERIC_REGISTER)
		वापस AE_OK;

	reg = &ares->data.generic_reg;
	paddr = reg->address;
	अगर ((reg->space_id != ACPI_SPACE_MEM) ||
	    (reg->bit_offset != 0) ||
	    (reg->bit_width > REG_SIZE)) अणु
		dev_err(ctx->dev, "Bad register resource @%pa\n", &paddr);
		ctx->err = -EINVAL;
		वापस AE_ERROR;
	पूर्ण

	vaddr = devm_ioremap(ctx->dev, reg->address, REG_SIZE);
	अगर (!vaddr) अणु
		dev_err(ctx->dev, "Can't map register @%pa\n", &paddr);
		ctx->err = -ENOMEM;
		वापस AE_ERROR;
	पूर्ण

	ctx->combiner->regs[ctx->combiner->nregs].addr = vaddr;
	ctx->combiner->nirqs += reg->bit_width;
	ctx->combiner->nregs++;
	वापस AE_OK;
पूर्ण

अटल पूर्णांक get_रेजिस्टरs(काष्ठा platक्रमm_device *pdev, काष्ठा combiner *comb)
अणु
	acpi_handle ahandle = ACPI_HANDLE(&pdev->dev);
	acpi_status status;
	काष्ठा get_रेजिस्टरs_context ctx;

	अगर (!acpi_has_method(ahandle, METHOD_NAME__CRS))
		वापस -EINVAL;

	ctx.dev = &pdev->dev;
	ctx.combiner = comb;
	ctx.err = 0;

	status = acpi_walk_resources(ahandle, METHOD_NAME__CRS,
				     get_रेजिस्टरs_cb, &ctx);
	अगर (ACPI_FAILURE(status))
		वापस ctx.err;
	वापस 0;
पूर्ण

अटल पूर्णांक __init combiner_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा combiner *combiner;
	पूर्णांक nregs;
	पूर्णांक err;

	nregs = count_रेजिस्टरs(pdev);
	अगर (nregs <= 0) अणु
		dev_err(&pdev->dev, "Error reading register resources\n");
		वापस -EINVAL;
	पूर्ण

	combiner = devm_kzalloc(&pdev->dev, काष्ठा_size(combiner, regs, nregs),
				GFP_KERNEL);
	अगर (!combiner)
		वापस -ENOMEM;

	err = get_रेजिस्टरs(pdev, combiner);
	अगर (err < 0)
		वापस err;

	combiner->parent_irq = platक्रमm_get_irq(pdev, 0);
	अगर (combiner->parent_irq <= 0)
		वापस -EPROBE_DEFER;

	combiner->करोमुख्य = irq_करोमुख्य_create_linear(pdev->dev.fwnode, combiner->nirqs,
						    &करोमुख्य_ops, combiner);
	अगर (!combiner->करोमुख्य)
		/* Errors prपूर्णांकed by irq_करोमुख्य_create_linear */
		वापस -ENODEV;

	irq_set_chained_handler_and_data(combiner->parent_irq,
					 combiner_handle_irq, combiner);

	dev_info(&pdev->dev, "Initialized with [p=%d,n=%d,r=%p]\n",
		 combiner->parent_irq, combiner->nirqs, combiner->regs[0].addr);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id qcom_irq_combiner_ids[] = अणु
	अणु "QCOM80B1", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver qcom_irq_combiner_probe = अणु
	.driver = अणु
		.name = "qcom-irq-combiner",
		.acpi_match_table = ACPI_PTR(qcom_irq_combiner_ids),
	पूर्ण,
	.probe = combiner_probe,
पूर्ण;
builtin_platक्रमm_driver(qcom_irq_combiner_probe);
