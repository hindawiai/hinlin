<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2019 MediaTek Inc.

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/suspend.h>
#समावेश <linux/mfd/mt6323/core.h>
#समावेश <linux/mfd/mt6323/रेजिस्टरs.h>
#समावेश <linux/mfd/mt6397/core.h>
#समावेश <linux/mfd/mt6397/रेजिस्टरs.h>

अटल व्योम mt6397_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा mt6397_chip *mt6397 = irq_data_get_irq_chip_data(data);

	mutex_lock(&mt6397->irqlock);
पूर्ण

अटल व्योम mt6397_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा mt6397_chip *mt6397 = irq_data_get_irq_chip_data(data);

	regmap_ग_लिखो(mt6397->regmap, mt6397->पूर्णांक_con[0],
		     mt6397->irq_masks_cur[0]);
	regmap_ग_लिखो(mt6397->regmap, mt6397->पूर्णांक_con[1],
		     mt6397->irq_masks_cur[1]);

	mutex_unlock(&mt6397->irqlock);
पूर्ण

अटल व्योम mt6397_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा mt6397_chip *mt6397 = irq_data_get_irq_chip_data(data);
	पूर्णांक shअगरt = data->hwirq & 0xf;
	पूर्णांक reg = data->hwirq >> 4;

	mt6397->irq_masks_cur[reg] &= ~BIT(shअगरt);
पूर्ण

अटल व्योम mt6397_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा mt6397_chip *mt6397 = irq_data_get_irq_chip_data(data);
	पूर्णांक shअगरt = data->hwirq & 0xf;
	पूर्णांक reg = data->hwirq >> 4;

	mt6397->irq_masks_cur[reg] |= BIT(shअगरt);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mt6397_irq_set_wake(काष्ठा irq_data *irq_data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा mt6397_chip *mt6397 = irq_data_get_irq_chip_data(irq_data);
	पूर्णांक shअगरt = irq_data->hwirq & 0xf;
	पूर्णांक reg = irq_data->hwirq >> 4;

	अगर (on)
		mt6397->wake_mask[reg] |= BIT(shअगरt);
	अन्यथा
		mt6397->wake_mask[reg] &= ~BIT(shअगरt);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा mt6397_irq_set_wake शून्य
#पूर्ण_अगर

अटल काष्ठा irq_chip mt6397_irq_chip = अणु
	.name = "mt6397-irq",
	.irq_bus_lock = mt6397_irq_lock,
	.irq_bus_sync_unlock = mt6397_irq_sync_unlock,
	.irq_enable = mt6397_irq_enable,
	.irq_disable = mt6397_irq_disable,
	.irq_set_wake = mt6397_irq_set_wake,
पूर्ण;

अटल व्योम mt6397_irq_handle_reg(काष्ठा mt6397_chip *mt6397, पूर्णांक reg,
				  पूर्णांक irqbase)
अणु
	अचिन्हित पूर्णांक status = 0;
	पूर्णांक i, irq, ret;

	ret = regmap_पढ़ो(mt6397->regmap, reg, &status);
	अगर (ret) अणु
		dev_err(mt6397->dev, "Failed to read irq status: %d\n", ret);
		वापस;
	पूर्ण

	क्रम (i = 0; i < 16; i++) अणु
		अगर (status & BIT(i)) अणु
			irq = irq_find_mapping(mt6397->irq_करोमुख्य, irqbase + i);
			अगर (irq)
				handle_nested_irq(irq);
		पूर्ण
	पूर्ण

	regmap_ग_लिखो(mt6397->regmap, reg, status);
पूर्ण

अटल irqवापस_t mt6397_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mt6397_chip *mt6397 = data;

	mt6397_irq_handle_reg(mt6397, mt6397->पूर्णांक_status[0], 0);
	mt6397_irq_handle_reg(mt6397, mt6397->पूर्णांक_status[1], 16);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mt6397_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				 irq_hw_number_t hw)
अणु
	काष्ठा mt6397_chip *mt6397 = d->host_data;

	irq_set_chip_data(irq, mt6397);
	irq_set_chip_and_handler(irq, &mt6397_irq_chip, handle_level_irq);
	irq_set_nested_thपढ़ो(irq, 1);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mt6397_irq_करोमुख्य_ops = अणु
	.map = mt6397_irq_करोमुख्य_map,
पूर्ण;

अटल पूर्णांक mt6397_irq_pm_notअगरier(काष्ठा notअगरier_block *notअगरier,
				  अचिन्हित दीर्घ pm_event, व्योम *unused)
अणु
	काष्ठा mt6397_chip *chip =
		container_of(notअगरier, काष्ठा mt6397_chip, pm_nb);

	चयन (pm_event) अणु
	हाल PM_SUSPEND_PREPARE:
		regmap_ग_लिखो(chip->regmap,
			     chip->पूर्णांक_con[0], chip->wake_mask[0]);
		regmap_ग_लिखो(chip->regmap,
			     chip->पूर्णांक_con[1], chip->wake_mask[1]);
		enable_irq_wake(chip->irq);
		अवरोध;

	हाल PM_POST_SUSPEND:
		regmap_ग_लिखो(chip->regmap,
			     chip->पूर्णांक_con[0], chip->irq_masks_cur[0]);
		regmap_ग_लिखो(chip->regmap,
			     chip->पूर्णांक_con[1], chip->irq_masks_cur[1]);
		disable_irq_wake(chip->irq);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

पूर्णांक mt6397_irq_init(काष्ठा mt6397_chip *chip)
अणु
	पूर्णांक ret;

	mutex_init(&chip->irqlock);

	चयन (chip->chip_id) अणु
	हाल MT6323_CHIP_ID:
		chip->पूर्णांक_con[0] = MT6323_INT_CON0;
		chip->पूर्णांक_con[1] = MT6323_INT_CON1;
		chip->पूर्णांक_status[0] = MT6323_INT_STATUS0;
		chip->पूर्णांक_status[1] = MT6323_INT_STATUS1;
		अवरोध;

	हाल MT6391_CHIP_ID:
	हाल MT6397_CHIP_ID:
		chip->पूर्णांक_con[0] = MT6397_INT_CON0;
		chip->पूर्णांक_con[1] = MT6397_INT_CON1;
		chip->पूर्णांक_status[0] = MT6397_INT_STATUS0;
		chip->पूर्णांक_status[1] = MT6397_INT_STATUS1;
		अवरोध;

	शेष:
		dev_err(chip->dev, "unsupported chip: 0x%x\n", chip->chip_id);
		वापस -ENODEV;
	पूर्ण

	/* Mask all पूर्णांकerrupt sources */
	regmap_ग_लिखो(chip->regmap, chip->पूर्णांक_con[0], 0x0);
	regmap_ग_लिखो(chip->regmap, chip->पूर्णांक_con[1], 0x0);

	chip->pm_nb.notअगरier_call = mt6397_irq_pm_notअगरier;
	chip->irq_करोमुख्य = irq_करोमुख्य_add_linear(chip->dev->of_node,
						 MT6397_IRQ_NR,
						 &mt6397_irq_करोमुख्य_ops,
						 chip);
	अगर (!chip->irq_करोमुख्य) अणु
		dev_err(chip->dev, "could not create irq domain\n");
		वापस -ENOMEM;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(chip->dev, chip->irq, शून्य,
					mt6397_irq_thपढ़ो, IRQF_ONESHOT,
					"mt6397-pmic", chip);
	अगर (ret) अणु
		dev_err(chip->dev, "failed to register irq=%d; err: %d\n",
			chip->irq, ret);
		वापस ret;
	पूर्ण

	रेजिस्टर_pm_notअगरier(&chip->pm_nb);
	वापस 0;
पूर्ण
