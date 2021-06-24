<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2020 MediaTek Inc.

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/mt6358/core.h>
#समावेश <linux/mfd/mt6358/रेजिस्टरs.h>
#समावेश <linux/mfd/mt6397/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

अटल काष्ठा irq_top_t mt6358_पूर्णांकs[] = अणु
	MT6358_TOP_GEN(BUCK),
	MT6358_TOP_GEN(LDO),
	MT6358_TOP_GEN(PSC),
	MT6358_TOP_GEN(SCK),
	MT6358_TOP_GEN(BM),
	MT6358_TOP_GEN(HK),
	MT6358_TOP_GEN(AUD),
	MT6358_TOP_GEN(MISC),
पूर्ण;

अटल व्योम pmic_irq_enable(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक hwirq = irqd_to_hwirq(data);
	काष्ठा mt6397_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा pmic_irq_data *irqd = chip->irq_data;

	irqd->enable_hwirq[hwirq] = true;
पूर्ण

अटल व्योम pmic_irq_disable(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक hwirq = irqd_to_hwirq(data);
	काष्ठा mt6397_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा pmic_irq_data *irqd = chip->irq_data;

	irqd->enable_hwirq[hwirq] = false;
पूर्ण

अटल व्योम pmic_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा mt6397_chip *chip = irq_data_get_irq_chip_data(data);

	mutex_lock(&chip->irqlock);
पूर्ण

अटल व्योम pmic_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक i, top_gp, gp_offset, en_reg, पूर्णांक_regs, shअगरt;
	काष्ठा mt6397_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा pmic_irq_data *irqd = chip->irq_data;

	क्रम (i = 0; i < irqd->num_pmic_irqs; i++) अणु
		अगर (irqd->enable_hwirq[i] == irqd->cache_hwirq[i])
			जारी;

		/* Find out the IRQ group */
		top_gp = 0;
		जबतक ((top_gp + 1) < irqd->num_top &&
		       i >= mt6358_पूर्णांकs[top_gp + 1].hwirq_base)
			top_gp++;

		/* Find the IRQ रेजिस्टरs */
		gp_offset = i - mt6358_पूर्णांकs[top_gp].hwirq_base;
		पूर्णांक_regs = gp_offset / MT6358_REG_WIDTH;
		shअगरt = gp_offset % MT6358_REG_WIDTH;
		en_reg = mt6358_पूर्णांकs[top_gp].en_reg +
			 (mt6358_पूर्णांकs[top_gp].en_reg_shअगरt * पूर्णांक_regs);

		regmap_update_bits(chip->regmap, en_reg, BIT(shअगरt),
				   irqd->enable_hwirq[i] << shअगरt);

		irqd->cache_hwirq[i] = irqd->enable_hwirq[i];
	पूर्ण
	mutex_unlock(&chip->irqlock);
पूर्ण

अटल काष्ठा irq_chip mt6358_irq_chip = अणु
	.name = "mt6358-irq",
	.flags = IRQCHIP_SKIP_SET_WAKE,
	.irq_enable = pmic_irq_enable,
	.irq_disable = pmic_irq_disable,
	.irq_bus_lock = pmic_irq_lock,
	.irq_bus_sync_unlock = pmic_irq_sync_unlock,
पूर्ण;

अटल व्योम mt6358_irq_sp_handler(काष्ठा mt6397_chip *chip,
				  अचिन्हित पूर्णांक top_gp)
अणु
	अचिन्हित पूर्णांक irq_status, sta_reg, status;
	अचिन्हित पूर्णांक hwirq, virq;
	पूर्णांक i, j, ret;

	क्रम (i = 0; i < mt6358_पूर्णांकs[top_gp].num_पूर्णांक_regs; i++) अणु
		sta_reg = mt6358_पूर्णांकs[top_gp].sta_reg +
			mt6358_पूर्णांकs[top_gp].sta_reg_shअगरt * i;

		ret = regmap_पढ़ो(chip->regmap, sta_reg, &irq_status);
		अगर (ret) अणु
			dev_err(chip->dev,
				"Failed to read IRQ status, ret=%d\n", ret);
			वापस;
		पूर्ण

		अगर (!irq_status)
			जारी;

		status = irq_status;
		करो अणु
			j = __ffs(status);

			hwirq = mt6358_पूर्णांकs[top_gp].hwirq_base +
				MT6358_REG_WIDTH * i + j;

			virq = irq_find_mapping(chip->irq_करोमुख्य, hwirq);
			अगर (virq)
				handle_nested_irq(virq);

			status &= ~BIT(j);
		पूर्ण जबतक (status);

		regmap_ग_लिखो(chip->regmap, sta_reg, irq_status);
	पूर्ण
पूर्ण

अटल irqवापस_t mt6358_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mt6397_chip *chip = data;
	काष्ठा pmic_irq_data *mt6358_irq_data = chip->irq_data;
	अचिन्हित पूर्णांक bit, i, top_irq_status = 0;
	पूर्णांक ret;

	ret = regmap_पढ़ो(chip->regmap,
			  mt6358_irq_data->top_पूर्णांक_status_reg,
			  &top_irq_status);
	अगर (ret) अणु
		dev_err(chip->dev,
			"Failed to read status from the device, ret=%d\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	क्रम (i = 0; i < mt6358_irq_data->num_top; i++) अणु
		bit = BIT(mt6358_पूर्णांकs[i].top_offset);
		अगर (top_irq_status & bit) अणु
			mt6358_irq_sp_handler(chip, i);
			top_irq_status &= ~bit;
			अगर (!top_irq_status)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pmic_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			       irq_hw_number_t hw)
अणु
	काष्ठा mt6397_chip *mt6397 = d->host_data;

	irq_set_chip_data(irq, mt6397);
	irq_set_chip_and_handler(irq, &mt6358_irq_chip, handle_level_irq);
	irq_set_nested_thपढ़ो(irq, 1);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mt6358_irq_करोमुख्य_ops = अणु
	.map = pmic_irq_करोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_twocell,
पूर्ण;

पूर्णांक mt6358_irq_init(काष्ठा mt6397_chip *chip)
अणु
	पूर्णांक i, j, ret;
	काष्ठा pmic_irq_data *irqd;

	irqd = devm_kzalloc(chip->dev, माप(*irqd), GFP_KERNEL);
	अगर (!irqd)
		वापस -ENOMEM;

	chip->irq_data = irqd;

	mutex_init(&chip->irqlock);
	irqd->top_पूर्णांक_status_reg = MT6358_TOP_INT_STATUS0;
	irqd->num_pmic_irqs = MT6358_IRQ_NR;
	irqd->num_top = ARRAY_SIZE(mt6358_पूर्णांकs);

	irqd->enable_hwirq = devm_kसुस्मृति(chip->dev,
					  irqd->num_pmic_irqs,
					  माप(*irqd->enable_hwirq),
					  GFP_KERNEL);
	अगर (!irqd->enable_hwirq)
		वापस -ENOMEM;

	irqd->cache_hwirq = devm_kसुस्मृति(chip->dev,
					 irqd->num_pmic_irqs,
					 माप(*irqd->cache_hwirq),
					 GFP_KERNEL);
	अगर (!irqd->cache_hwirq)
		वापस -ENOMEM;

	/* Disable all पूर्णांकerrupts क्रम initializing */
	क्रम (i = 0; i < irqd->num_top; i++) अणु
		क्रम (j = 0; j < mt6358_पूर्णांकs[i].num_पूर्णांक_regs; j++)
			regmap_ग_लिखो(chip->regmap,
				     mt6358_पूर्णांकs[i].en_reg +
				     mt6358_पूर्णांकs[i].en_reg_shअगरt * j, 0);
	पूर्ण

	chip->irq_करोमुख्य = irq_करोमुख्य_add_linear(chip->dev->of_node,
						 irqd->num_pmic_irqs,
						 &mt6358_irq_करोमुख्य_ops, chip);
	अगर (!chip->irq_करोमुख्य) अणु
		dev_err(chip->dev, "Could not create IRQ domain\n");
		वापस -ENODEV;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(chip->dev, chip->irq, शून्य,
					mt6358_irq_handler, IRQF_ONESHOT,
					mt6358_irq_chip.name, chip);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to register IRQ=%d, ret=%d\n",
			chip->irq, ret);
		वापस ret;
	पूर्ण

	enable_irq_wake(chip->irq);
	वापस ret;
पूर्ण
