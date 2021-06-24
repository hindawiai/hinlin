<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI LP8788 MFD - पूर्णांकerrupt handler
 *
 * Copyright 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/device.h>
#समावेश <linux/mfd/lp8788.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

/* रेजिस्टर address */
#घोषणा LP8788_INT_1			0x00
#घोषणा LP8788_INTEN_1			0x03

#घोषणा BASE_INTEN_ADDR			LP8788_INTEN_1
#घोषणा SIZE_REG			8
#घोषणा NUM_REGS			3

/*
 * काष्ठा lp8788_irq_data
 * @lp               : used क्रम accessing to lp8788 रेजिस्टरs
 * @irq_lock         : mutex क्रम enabling/disabling the पूर्णांकerrupt
 * @करोमुख्य           : IRQ करोमुख्य क्रम handling nested पूर्णांकerrupt
 * @enabled          : status of enabled पूर्णांकerrupt
 */
काष्ठा lp8788_irq_data अणु
	काष्ठा lp8788 *lp;
	काष्ठा mutex irq_lock;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक enabled[LP8788_पूर्णांक_उच्च];
पूर्ण;

अटल अंतरभूत u8 _irq_to_addr(क्रमागत lp8788_पूर्णांक_id id)
अणु
	वापस id / SIZE_REG;
पूर्ण

अटल अंतरभूत u8 _irq_to_enable_addr(क्रमागत lp8788_पूर्णांक_id id)
अणु
	वापस _irq_to_addr(id) + BASE_INTEN_ADDR;
पूर्ण

अटल अंतरभूत u8 _irq_to_mask(क्रमागत lp8788_पूर्णांक_id id)
अणु
	वापस 1 << (id % SIZE_REG);
पूर्ण

अटल अंतरभूत u8 _irq_to_val(क्रमागत lp8788_पूर्णांक_id id, पूर्णांक enable)
अणु
	वापस enable << (id % SIZE_REG);
पूर्ण

अटल व्योम lp8788_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा lp8788_irq_data *irqd = irq_data_get_irq_chip_data(data);

	irqd->enabled[data->hwirq] = 1;
पूर्ण

अटल व्योम lp8788_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा lp8788_irq_data *irqd = irq_data_get_irq_chip_data(data);

	irqd->enabled[data->hwirq] = 0;
पूर्ण

अटल व्योम lp8788_irq_bus_lock(काष्ठा irq_data *data)
अणु
	काष्ठा lp8788_irq_data *irqd = irq_data_get_irq_chip_data(data);

	mutex_lock(&irqd->irq_lock);
पूर्ण

अटल व्योम lp8788_irq_bus_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा lp8788_irq_data *irqd = irq_data_get_irq_chip_data(data);
	क्रमागत lp8788_पूर्णांक_id irq = data->hwirq;
	u8 addr, mask, val;

	addr = _irq_to_enable_addr(irq);
	mask = _irq_to_mask(irq);
	val = _irq_to_val(irq, irqd->enabled[irq]);

	lp8788_update_bits(irqd->lp, addr, mask, val);

	mutex_unlock(&irqd->irq_lock);
पूर्ण

अटल काष्ठा irq_chip lp8788_irq_chip = अणु
	.name			= "lp8788",
	.irq_enable		= lp8788_irq_enable,
	.irq_disable		= lp8788_irq_disable,
	.irq_bus_lock		= lp8788_irq_bus_lock,
	.irq_bus_sync_unlock	= lp8788_irq_bus_sync_unlock,
पूर्ण;

अटल irqवापस_t lp8788_irq_handler(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा lp8788_irq_data *irqd = ptr;
	काष्ठा lp8788 *lp = irqd->lp;
	u8 status[NUM_REGS], addr, mask;
	bool handled = false;
	पूर्णांक i;

	अगर (lp8788_पढ़ो_multi_bytes(lp, LP8788_INT_1, status, NUM_REGS))
		वापस IRQ_NONE;

	क्रम (i = 0 ; i < LP8788_पूर्णांक_उच्च ; i++) अणु
		addr = _irq_to_addr(i);
		mask = _irq_to_mask(i);

		/* reporting only अगर the irq is enabled */
		अगर (status[addr] & mask) अणु
			handle_nested_irq(irq_find_mapping(irqd->करोमुख्य, i));
			handled = true;
		पूर्ण
	पूर्ण

	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक lp8788_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			irq_hw_number_t hwirq)
अणु
	काष्ठा lp8788_irq_data *irqd = d->host_data;
	काष्ठा irq_chip *chip = &lp8788_irq_chip;

	irq_set_chip_data(virq, irqd);
	irq_set_chip_and_handler(virq, chip, handle_edge_irq);
	irq_set_nested_thपढ़ो(virq, 1);
	irq_set_noprobe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops lp8788_करोमुख्य_ops = अणु
	.map = lp8788_irq_map,
पूर्ण;

पूर्णांक lp8788_irq_init(काष्ठा lp8788 *lp, पूर्णांक irq)
अणु
	काष्ठा lp8788_irq_data *irqd;
	पूर्णांक ret;

	अगर (irq <= 0) अणु
		dev_warn(lp->dev, "invalid irq number: %d\n", irq);
		वापस 0;
	पूर्ण

	irqd = devm_kzalloc(lp->dev, माप(*irqd), GFP_KERNEL);
	अगर (!irqd)
		वापस -ENOMEM;

	irqd->lp = lp;
	irqd->करोमुख्य = irq_करोमुख्य_add_linear(lp->dev->of_node, LP8788_पूर्णांक_उच्च,
					&lp8788_करोमुख्य_ops, irqd);
	अगर (!irqd->करोमुख्य) अणु
		dev_err(lp->dev, "failed to add irq domain err\n");
		वापस -EINVAL;
	पूर्ण

	lp->irqdm = irqd->करोमुख्य;
	mutex_init(&irqd->irq_lock);

	ret = request_thपढ़ोed_irq(irq, शून्य, lp8788_irq_handler,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				"lp8788-irq", irqd);
	अगर (ret) अणु
		dev_err(lp->dev, "failed to create a thread for IRQ_N\n");
		वापस ret;
	पूर्ण

	lp->irq = irq;

	वापस 0;
पूर्ण

व्योम lp8788_irq_निकास(काष्ठा lp8788 *lp)
अणु
	अगर (lp->irq)
		मुक्त_irq(lp->irq, lp->irqdm);
पूर्ण
