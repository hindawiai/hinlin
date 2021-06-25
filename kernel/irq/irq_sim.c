<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017-2018 Bartosz Golaszewski <brgl@bgdev.pl>
 * Copyright (C) 2020 Bartosz Golaszewski <bgolaszewski@baylibre.com>
 */

#समावेश <linux/irq.h>
#समावेश <linux/irq_sim.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

काष्ठा irq_sim_work_ctx अणु
	काष्ठा irq_work		work;
	पूर्णांक			irq_base;
	अचिन्हित पूर्णांक		irq_count;
	अचिन्हित दीर्घ		*pending;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
पूर्ण;

काष्ठा irq_sim_irq_ctx अणु
	पूर्णांक			irqnum;
	bool			enabled;
	काष्ठा irq_sim_work_ctx	*work_ctx;
पूर्ण;

अटल व्योम irq_sim_irqmask(काष्ठा irq_data *data)
अणु
	काष्ठा irq_sim_irq_ctx *irq_ctx = irq_data_get_irq_chip_data(data);

	irq_ctx->enabled = false;
पूर्ण

अटल व्योम irq_sim_irqunmask(काष्ठा irq_data *data)
अणु
	काष्ठा irq_sim_irq_ctx *irq_ctx = irq_data_get_irq_chip_data(data);

	irq_ctx->enabled = true;
पूर्ण

अटल पूर्णांक irq_sim_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	/* We only support rising and falling edge trigger types. */
	अगर (type & ~IRQ_TYPE_EDGE_BOTH)
		वापस -EINVAL;

	irqd_set_trigger_type(data, type);

	वापस 0;
पूर्ण

अटल पूर्णांक irq_sim_get_irqchip_state(काष्ठा irq_data *data,
				     क्रमागत irqchip_irq_state which, bool *state)
अणु
	काष्ठा irq_sim_irq_ctx *irq_ctx = irq_data_get_irq_chip_data(data);
	irq_hw_number_t hwirq = irqd_to_hwirq(data);

	चयन (which) अणु
	हाल IRQCHIP_STATE_PENDING:
		अगर (irq_ctx->enabled)
			*state = test_bit(hwirq, irq_ctx->work_ctx->pending);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक irq_sim_set_irqchip_state(काष्ठा irq_data *data,
				     क्रमागत irqchip_irq_state which, bool state)
अणु
	काष्ठा irq_sim_irq_ctx *irq_ctx = irq_data_get_irq_chip_data(data);
	irq_hw_number_t hwirq = irqd_to_hwirq(data);

	चयन (which) अणु
	हाल IRQCHIP_STATE_PENDING:
		अगर (irq_ctx->enabled) अणु
			assign_bit(hwirq, irq_ctx->work_ctx->pending, state);
			अगर (state)
				irq_work_queue(&irq_ctx->work_ctx->work);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip irq_sim_irqchip = अणु
	.name			= "irq_sim",
	.irq_mask		= irq_sim_irqmask,
	.irq_unmask		= irq_sim_irqunmask,
	.irq_set_type		= irq_sim_set_type,
	.irq_get_irqchip_state	= irq_sim_get_irqchip_state,
	.irq_set_irqchip_state	= irq_sim_set_irqchip_state,
पूर्ण;

अटल व्योम irq_sim_handle_irq(काष्ठा irq_work *work)
अणु
	काष्ठा irq_sim_work_ctx *work_ctx;
	अचिन्हित पूर्णांक offset = 0;
	पूर्णांक irqnum;

	work_ctx = container_of(work, काष्ठा irq_sim_work_ctx, work);

	जबतक (!biपंचांगap_empty(work_ctx->pending, work_ctx->irq_count)) अणु
		offset = find_next_bit(work_ctx->pending,
				       work_ctx->irq_count, offset);
		clear_bit(offset, work_ctx->pending);
		irqnum = irq_find_mapping(work_ctx->करोमुख्य, offset);
		handle_simple_irq(irq_to_desc(irqnum));
	पूर्ण
पूर्ण

अटल पूर्णांक irq_sim_करोमुख्य_map(काष्ठा irq_करोमुख्य *करोमुख्य,
			      अचिन्हित पूर्णांक virq, irq_hw_number_t hw)
अणु
	काष्ठा irq_sim_work_ctx *work_ctx = करोमुख्य->host_data;
	काष्ठा irq_sim_irq_ctx *irq_ctx;

	irq_ctx = kzalloc(माप(*irq_ctx), GFP_KERNEL);
	अगर (!irq_ctx)
		वापस -ENOMEM;

	irq_set_chip(virq, &irq_sim_irqchip);
	irq_set_chip_data(virq, irq_ctx);
	irq_set_handler(virq, handle_simple_irq);
	irq_modअगरy_status(virq, IRQ_NOREQUEST | IRQ_NOAUTOEN, IRQ_NOPROBE);
	irq_ctx->work_ctx = work_ctx;

	वापस 0;
पूर्ण

अटल व्योम irq_sim_करोमुख्य_unmap(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq)
अणु
	काष्ठा irq_sim_irq_ctx *irq_ctx;
	काष्ठा irq_data *irqd;

	irqd = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	irq_ctx = irq_data_get_irq_chip_data(irqd);

	irq_set_handler(virq, शून्य);
	irq_करोमुख्य_reset_irq_data(irqd);
	kमुक्त(irq_ctx);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops irq_sim_करोमुख्य_ops = अणु
	.map		= irq_sim_करोमुख्य_map,
	.unmap		= irq_sim_करोमुख्य_unmap,
पूर्ण;

/**
 * irq_करोमुख्य_create_sim - Create a new पूर्णांकerrupt simulator irq_करोमुख्य and
 *                         allocate a range of dummy पूर्णांकerrupts.
 *
 * @fwnode:     काष्ठा fwnode_handle to be associated with this करोमुख्य.
 * @num_irqs:   Number of पूर्णांकerrupts to allocate.
 *
 * On success: वापस a new irq_करोमुख्य object.
 * On failure: a negative त्रुटि_सं wrapped with ERR_PTR().
 */
काष्ठा irq_करोमुख्य *irq_करोमुख्य_create_sim(काष्ठा fwnode_handle *fwnode,
					 अचिन्हित पूर्णांक num_irqs)
अणु
	काष्ठा irq_sim_work_ctx *work_ctx;

	work_ctx = kदो_स्मृति(माप(*work_ctx), GFP_KERNEL);
	अगर (!work_ctx)
		जाओ err_out;

	work_ctx->pending = biपंचांगap_zalloc(num_irqs, GFP_KERNEL);
	अगर (!work_ctx->pending)
		जाओ err_मुक्त_work_ctx;

	work_ctx->करोमुख्य = irq_करोमुख्य_create_linear(fwnode, num_irqs,
						    &irq_sim_करोमुख्य_ops,
						    work_ctx);
	अगर (!work_ctx->करोमुख्य)
		जाओ err_मुक्त_biपंचांगap;

	work_ctx->irq_count = num_irqs;
	init_irq_work(&work_ctx->work, irq_sim_handle_irq);

	वापस work_ctx->करोमुख्य;

err_मुक्त_biपंचांगap:
	biपंचांगap_मुक्त(work_ctx->pending);
err_मुक्त_work_ctx:
	kमुक्त(work_ctx);
err_out:
	वापस ERR_PTR(-ENOMEM);
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_create_sim);

/**
 * irq_करोमुख्य_हटाओ_sim - Deinitialize the पूर्णांकerrupt simulator करोमुख्य: मुक्त
 *                         the पूर्णांकerrupt descriptors and allocated memory.
 *
 * @करोमुख्य:     The पूर्णांकerrupt simulator करोमुख्य to tear करोwn.
 */
व्योम irq_करोमुख्य_हटाओ_sim(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	काष्ठा irq_sim_work_ctx *work_ctx = करोमुख्य->host_data;

	irq_work_sync(&work_ctx->work);
	biपंचांगap_मुक्त(work_ctx->pending);
	kमुक्त(work_ctx);

	irq_करोमुख्य_हटाओ(करोमुख्य);
पूर्ण
EXPORT_SYMBOL_GPL(irq_करोमुख्य_हटाओ_sim);

अटल व्योम devm_irq_करोमुख्य_हटाओ_sim(व्योम *data)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = data;

	irq_करोमुख्य_हटाओ_sim(करोमुख्य);
पूर्ण

/**
 * devm_irq_करोमुख्य_create_sim - Create a new पूर्णांकerrupt simulator क्रम
 *                              a managed device.
 *
 * @dev:        Device to initialize the simulator object क्रम.
 * @fwnode:     काष्ठा fwnode_handle to be associated with this करोमुख्य.
 * @num_irqs:   Number of पूर्णांकerrupts to allocate
 *
 * On success: वापस a new irq_करोमुख्य object.
 * On failure: a negative त्रुटि_सं wrapped with ERR_PTR().
 */
काष्ठा irq_करोमुख्य *devm_irq_करोमुख्य_create_sim(काष्ठा device *dev,
					      काष्ठा fwnode_handle *fwnode,
					      अचिन्हित पूर्णांक num_irqs)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक ret;

	करोमुख्य = irq_करोमुख्य_create_sim(fwnode, num_irqs);
	अगर (IS_ERR(करोमुख्य))
		वापस करोमुख्य;

	ret = devm_add_action_or_reset(dev, devm_irq_करोमुख्य_हटाओ_sim, करोमुख्य);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस करोमुख्य;
पूर्ण
EXPORT_SYMBOL_GPL(devm_irq_करोमुख्य_create_sim);
