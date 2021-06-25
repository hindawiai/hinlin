<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Interrupt controller support क्रम MAX8998
//
// Copyright (C) 2010 Samsung Electronics Co.Ltd
// Author: Joonyoung Shim <jy0922.shim@samsung.com>

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mfd/max8998-निजी.h>

काष्ठा max8998_irq_data अणु
	पूर्णांक reg;
	पूर्णांक mask;
पूर्ण;

अटल काष्ठा max8998_irq_data max8998_irqs[] = अणु
	[MAX8998_IRQ_DCINF] = अणु
		.reg = 1,
		.mask = MAX8998_IRQ_DCINF_MASK,
	पूर्ण,
	[MAX8998_IRQ_DCINR] = अणु
		.reg = 1,
		.mask = MAX8998_IRQ_DCINR_MASK,
	पूर्ण,
	[MAX8998_IRQ_JIGF] = अणु
		.reg = 1,
		.mask = MAX8998_IRQ_JIGF_MASK,
	पूर्ण,
	[MAX8998_IRQ_JIGR] = अणु
		.reg = 1,
		.mask = MAX8998_IRQ_JIGR_MASK,
	पूर्ण,
	[MAX8998_IRQ_PWRONF] = अणु
		.reg = 1,
		.mask = MAX8998_IRQ_PWRONF_MASK,
	पूर्ण,
	[MAX8998_IRQ_PWRONR] = अणु
		.reg = 1,
		.mask = MAX8998_IRQ_PWRONR_MASK,
	पूर्ण,
	[MAX8998_IRQ_WTSREVNT] = अणु
		.reg = 2,
		.mask = MAX8998_IRQ_WTSREVNT_MASK,
	पूर्ण,
	[MAX8998_IRQ_SMPLEVNT] = अणु
		.reg = 2,
		.mask = MAX8998_IRQ_SMPLEVNT_MASK,
	पूर्ण,
	[MAX8998_IRQ_ALARM1] = अणु
		.reg = 2,
		.mask = MAX8998_IRQ_ALARM1_MASK,
	पूर्ण,
	[MAX8998_IRQ_ALARM0] = अणु
		.reg = 2,
		.mask = MAX8998_IRQ_ALARM0_MASK,
	पूर्ण,
	[MAX8998_IRQ_ONKEY1S] = अणु
		.reg = 3,
		.mask = MAX8998_IRQ_ONKEY1S_MASK,
	पूर्ण,
	[MAX8998_IRQ_TOPOFFR] = अणु
		.reg = 3,
		.mask = MAX8998_IRQ_TOPOFFR_MASK,
	पूर्ण,
	[MAX8998_IRQ_DCINOVPR] = अणु
		.reg = 3,
		.mask = MAX8998_IRQ_DCINOVPR_MASK,
	पूर्ण,
	[MAX8998_IRQ_CHGRSTF] = अणु
		.reg = 3,
		.mask = MAX8998_IRQ_CHGRSTF_MASK,
	पूर्ण,
	[MAX8998_IRQ_DONER] = अणु
		.reg = 3,
		.mask = MAX8998_IRQ_DONER_MASK,
	पूर्ण,
	[MAX8998_IRQ_CHGFAULT] = अणु
		.reg = 3,
		.mask = MAX8998_IRQ_CHGFAULT_MASK,
	पूर्ण,
	[MAX8998_IRQ_LOBAT1] = अणु
		.reg = 4,
		.mask = MAX8998_IRQ_LOBAT1_MASK,
	पूर्ण,
	[MAX8998_IRQ_LOBAT2] = अणु
		.reg = 4,
		.mask = MAX8998_IRQ_LOBAT2_MASK,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा max8998_irq_data *
irq_to_max8998_irq(काष्ठा max8998_dev *max8998, काष्ठा irq_data *data)
अणु
	वापस &max8998_irqs[data->hwirq];
पूर्ण

अटल व्योम max8998_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा max8998_dev *max8998 = irq_data_get_irq_chip_data(data);

	mutex_lock(&max8998->irqlock);
पूर्ण

अटल व्योम max8998_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा max8998_dev *max8998 = irq_data_get_irq_chip_data(data);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(max8998->irq_masks_cur); i++) अणु
		/*
		 * If there's been a change in the mask ग_लिखो it back
		 * to the hardware.
		 */
		अगर (max8998->irq_masks_cur[i] != max8998->irq_masks_cache[i]) अणु
			max8998->irq_masks_cache[i] = max8998->irq_masks_cur[i];
			max8998_ग_लिखो_reg(max8998->i2c, MAX8998_REG_IRQM1 + i,
					max8998->irq_masks_cur[i]);
		पूर्ण
	पूर्ण

	mutex_unlock(&max8998->irqlock);
पूर्ण

अटल व्योम max8998_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा max8998_dev *max8998 = irq_data_get_irq_chip_data(data);
	काष्ठा max8998_irq_data *irq_data = irq_to_max8998_irq(max8998, data);

	max8998->irq_masks_cur[irq_data->reg - 1] &= ~irq_data->mask;
पूर्ण

अटल व्योम max8998_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा max8998_dev *max8998 = irq_data_get_irq_chip_data(data);
	काष्ठा max8998_irq_data *irq_data = irq_to_max8998_irq(max8998, data);

	max8998->irq_masks_cur[irq_data->reg - 1] |= irq_data->mask;
पूर्ण

अटल काष्ठा irq_chip max8998_irq_chip = अणु
	.name = "max8998",
	.irq_bus_lock = max8998_irq_lock,
	.irq_bus_sync_unlock = max8998_irq_sync_unlock,
	.irq_mask = max8998_irq_mask,
	.irq_unmask = max8998_irq_unmask,
पूर्ण;

अटल irqवापस_t max8998_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max8998_dev *max8998 = data;
	u8 irq_reg[MAX8998_NUM_IRQ_REGS];
	पूर्णांक ret;
	पूर्णांक i;

	ret = max8998_bulk_पढ़ो(max8998->i2c, MAX8998_REG_IRQ1,
			MAX8998_NUM_IRQ_REGS, irq_reg);
	अगर (ret < 0) अणु
		dev_err(max8998->dev, "Failed to read interrupt register: %d\n",
				ret);
		वापस IRQ_NONE;
	पूर्ण

	/* Apply masking */
	क्रम (i = 0; i < MAX8998_NUM_IRQ_REGS; i++)
		irq_reg[i] &= ~max8998->irq_masks_cur[i];

	/* Report */
	क्रम (i = 0; i < MAX8998_IRQ_NR; i++) अणु
		अगर (irq_reg[max8998_irqs[i].reg - 1] & max8998_irqs[i].mask) अणु
			irq = irq_find_mapping(max8998->irq_करोमुख्य, i);
			अगर (WARN_ON(!irq)) अणु
				disable_irq_nosync(max8998->irq);
				वापस IRQ_NONE;
			पूर्ण
			handle_nested_irq(irq);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक max8998_irq_resume(काष्ठा max8998_dev *max8998)
अणु
	अगर (max8998->irq && max8998->irq_करोमुख्य)
		max8998_irq_thपढ़ो(max8998->irq, max8998);
	वापस 0;
पूर्ण

अटल पूर्णांक max8998_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
					irq_hw_number_t hw)
अणु
	काष्ठा max8997_dev *max8998 = d->host_data;

	irq_set_chip_data(irq, max8998);
	irq_set_chip_and_handler(irq, &max8998_irq_chip, handle_edge_irq);
	irq_set_nested_thपढ़ो(irq, 1);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops max8998_irq_करोमुख्य_ops = अणु
	.map = max8998_irq_करोमुख्य_map,
पूर्ण;

पूर्णांक max8998_irq_init(काष्ठा max8998_dev *max8998)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा irq_करोमुख्य *करोमुख्य;

	अगर (!max8998->irq) अणु
		dev_warn(max8998->dev,
			 "No interrupt specified, no interrupts\n");
		वापस 0;
	पूर्ण

	mutex_init(&max8998->irqlock);

	/* Mask the inभागidual पूर्णांकerrupt sources */
	क्रम (i = 0; i < MAX8998_NUM_IRQ_REGS; i++) अणु
		max8998->irq_masks_cur[i] = 0xff;
		max8998->irq_masks_cache[i] = 0xff;
		max8998_ग_लिखो_reg(max8998->i2c, MAX8998_REG_IRQM1 + i, 0xff);
	पूर्ण

	max8998_ग_लिखो_reg(max8998->i2c, MAX8998_REG_STATUSM1, 0xff);
	max8998_ग_लिखो_reg(max8998->i2c, MAX8998_REG_STATUSM2, 0xff);

	करोमुख्य = irq_करोमुख्य_add_simple(शून्य, MAX8998_IRQ_NR,
			max8998->irq_base, &max8998_irq_करोमुख्य_ops, max8998);
	अगर (!करोमुख्य) अणु
		dev_err(max8998->dev, "could not create irq domain\n");
		वापस -ENODEV;
	पूर्ण
	max8998->irq_करोमुख्य = करोमुख्य;

	ret = request_thपढ़ोed_irq(max8998->irq, शून्य, max8998_irq_thपढ़ो,
				   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				   "max8998-irq", max8998);
	अगर (ret) अणु
		dev_err(max8998->dev, "Failed to request IRQ %d: %d\n",
			max8998->irq, ret);
		वापस ret;
	पूर्ण

	अगर (!max8998->ono)
		वापस 0;

	ret = request_thपढ़ोed_irq(max8998->ono, शून्य, max8998_irq_thपढ़ो,
				   IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING |
				   IRQF_ONESHOT, "max8998-ono", max8998);
	अगर (ret)
		dev_err(max8998->dev, "Failed to request IRQ %d: %d\n",
			max8998->ono, ret);

	वापस 0;
पूर्ण

व्योम max8998_irq_निकास(काष्ठा max8998_dev *max8998)
अणु
	अगर (max8998->ono)
		मुक्त_irq(max8998->ono, max8998);

	अगर (max8998->irq)
		मुक्त_irq(max8998->irq, max8998);
पूर्ण
