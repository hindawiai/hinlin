<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core driver क्रम TI TPS6586x PMIC family
 *
 * Copyright (c) 2010 CompuLab Ltd.
 * Mike Rapoport <mike@compulab.co.il>
 *
 * Based on da903x.c.
 * Copyright (C) 2008 Compulab, Ltd.
 * Mike Rapoport <mike@compulab.co.il>
 * Copyright (C) 2006-2008 Marvell International Ltd.
 * Eric Miao <eric.miao@marvell.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>

#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/tps6586x.h>

#घोषणा TPS6586X_SUPPLYENE	0x14
#घोषणा EXITSLREQ_BIT		BIT(1)
#घोषणा SLEEP_MODE_BIT		BIT(3)

/* पूर्णांकerrupt control रेजिस्टरs */
#घोषणा TPS6586X_INT_ACK1	0xb5
#घोषणा TPS6586X_INT_ACK2	0xb6
#घोषणा TPS6586X_INT_ACK3	0xb7
#घोषणा TPS6586X_INT_ACK4	0xb8

/* पूर्णांकerrupt mask रेजिस्टरs */
#घोषणा TPS6586X_INT_MASK1	0xb0
#घोषणा TPS6586X_INT_MASK2	0xb1
#घोषणा TPS6586X_INT_MASK3	0xb2
#घोषणा TPS6586X_INT_MASK4	0xb3
#घोषणा TPS6586X_INT_MASK5	0xb4

/* device id */
#घोषणा TPS6586X_VERSIONCRC	0xcd

/* Maximum रेजिस्टर */
#घोषणा TPS6586X_MAX_REGISTER	TPS6586X_VERSIONCRC

काष्ठा tps6586x_irq_data अणु
	u8	mask_reg;
	u8	mask_mask;
पूर्ण;

#घोषणा TPS6586X_IRQ(_reg, _mask)				\
	अणु							\
		.mask_reg = (_reg) - TPS6586X_INT_MASK1,	\
		.mask_mask = (_mask),				\
	पूर्ण

अटल स्थिर काष्ठा tps6586x_irq_data tps6586x_irqs[] = अणु
	[TPS6586X_INT_PLDO_0]	= TPS6586X_IRQ(TPS6586X_INT_MASK1, 1 << 0),
	[TPS6586X_INT_PLDO_1]	= TPS6586X_IRQ(TPS6586X_INT_MASK1, 1 << 1),
	[TPS6586X_INT_PLDO_2]	= TPS6586X_IRQ(TPS6586X_INT_MASK1, 1 << 2),
	[TPS6586X_INT_PLDO_3]	= TPS6586X_IRQ(TPS6586X_INT_MASK1, 1 << 3),
	[TPS6586X_INT_PLDO_4]	= TPS6586X_IRQ(TPS6586X_INT_MASK1, 1 << 4),
	[TPS6586X_INT_PLDO_5]	= TPS6586X_IRQ(TPS6586X_INT_MASK1, 1 << 5),
	[TPS6586X_INT_PLDO_6]	= TPS6586X_IRQ(TPS6586X_INT_MASK1, 1 << 6),
	[TPS6586X_INT_PLDO_7]	= TPS6586X_IRQ(TPS6586X_INT_MASK1, 1 << 7),
	[TPS6586X_INT_COMP_DET]	= TPS6586X_IRQ(TPS6586X_INT_MASK4, 1 << 0),
	[TPS6586X_INT_ADC]	= TPS6586X_IRQ(TPS6586X_INT_MASK2, 1 << 1),
	[TPS6586X_INT_PLDO_8]	= TPS6586X_IRQ(TPS6586X_INT_MASK2, 1 << 2),
	[TPS6586X_INT_PLDO_9]	= TPS6586X_IRQ(TPS6586X_INT_MASK2, 1 << 3),
	[TPS6586X_INT_PSM_0]	= TPS6586X_IRQ(TPS6586X_INT_MASK2, 1 << 4),
	[TPS6586X_INT_PSM_1]	= TPS6586X_IRQ(TPS6586X_INT_MASK2, 1 << 5),
	[TPS6586X_INT_PSM_2]	= TPS6586X_IRQ(TPS6586X_INT_MASK2, 1 << 6),
	[TPS6586X_INT_PSM_3]	= TPS6586X_IRQ(TPS6586X_INT_MASK2, 1 << 7),
	[TPS6586X_INT_RTC_ALM1]	= TPS6586X_IRQ(TPS6586X_INT_MASK5, 1 << 4),
	[TPS6586X_INT_ACUSB_OVP] = TPS6586X_IRQ(TPS6586X_INT_MASK5, 0x03),
	[TPS6586X_INT_USB_DET]	= TPS6586X_IRQ(TPS6586X_INT_MASK5, 1 << 2),
	[TPS6586X_INT_AC_DET]	= TPS6586X_IRQ(TPS6586X_INT_MASK5, 1 << 3),
	[TPS6586X_INT_BAT_DET]	= TPS6586X_IRQ(TPS6586X_INT_MASK3, 1 << 0),
	[TPS6586X_INT_CHG_STAT]	= TPS6586X_IRQ(TPS6586X_INT_MASK4, 0xfc),
	[TPS6586X_INT_CHG_TEMP]	= TPS6586X_IRQ(TPS6586X_INT_MASK3, 0x06),
	[TPS6586X_INT_PP]	= TPS6586X_IRQ(TPS6586X_INT_MASK3, 0xf0),
	[TPS6586X_INT_RESUME]	= TPS6586X_IRQ(TPS6586X_INT_MASK5, 1 << 5),
	[TPS6586X_INT_LOW_SYS]	= TPS6586X_IRQ(TPS6586X_INT_MASK5, 1 << 6),
	[TPS6586X_INT_RTC_ALM2] = TPS6586X_IRQ(TPS6586X_INT_MASK4, 1 << 1),
पूर्ण;

अटल स्थिर काष्ठा resource tps6586x_rtc_resources[] = अणु
	अणु
		.start  = TPS6586X_INT_RTC_ALM1,
		.end	= TPS6586X_INT_RTC_ALM1,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell tps6586x_cell[] = अणु
	अणु
		.name = "tps6586x-gpio",
	पूर्ण,
	अणु
		.name = "tps6586x-regulator",
	पूर्ण,
	अणु
		.name = "tps6586x-rtc",
		.num_resources = ARRAY_SIZE(tps6586x_rtc_resources),
		.resources = &tps6586x_rtc_resources[0],
	पूर्ण,
	अणु
		.name = "tps6586x-onkey",
	पूर्ण,
पूर्ण;

काष्ठा tps6586x अणु
	काष्ठा device		*dev;
	काष्ठा i2c_client	*client;
	काष्ठा regmap		*regmap;
	पूर्णांक			version;

	पूर्णांक			irq;
	काष्ठा irq_chip		irq_chip;
	काष्ठा mutex		irq_lock;
	पूर्णांक			irq_base;
	u32			irq_en;
	u8			mask_reg[5];
	काष्ठा irq_करोमुख्य	*irq_करोमुख्य;
पूर्ण;

अटल अंतरभूत काष्ठा tps6586x *dev_to_tps6586x(काष्ठा device *dev)
अणु
	वापस i2c_get_clientdata(to_i2c_client(dev));
पूर्ण

पूर्णांक tps6586x_ग_लिखो(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t val)
अणु
	काष्ठा tps6586x *tps6586x = dev_to_tps6586x(dev);

	वापस regmap_ग_लिखो(tps6586x->regmap, reg, val);
पूर्ण
EXPORT_SYMBOL_GPL(tps6586x_ग_लिखो);

पूर्णांक tps6586x_ग_लिखोs(काष्ठा device *dev, पूर्णांक reg, पूर्णांक len, uपूर्णांक8_t *val)
अणु
	काष्ठा tps6586x *tps6586x = dev_to_tps6586x(dev);

	वापस regmap_bulk_ग_लिखो(tps6586x->regmap, reg, val, len);
पूर्ण
EXPORT_SYMBOL_GPL(tps6586x_ग_लिखोs);

पूर्णांक tps6586x_पढ़ो(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t *val)
अणु
	काष्ठा tps6586x *tps6586x = dev_to_tps6586x(dev);
	अचिन्हित पूर्णांक rval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tps6586x->regmap, reg, &rval);
	अगर (!ret)
		*val = rval;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tps6586x_पढ़ो);

पूर्णांक tps6586x_पढ़ोs(काष्ठा device *dev, पूर्णांक reg, पूर्णांक len, uपूर्णांक8_t *val)
अणु
	काष्ठा tps6586x *tps6586x = dev_to_tps6586x(dev);

	वापस regmap_bulk_पढ़ो(tps6586x->regmap, reg, val, len);
पूर्ण
EXPORT_SYMBOL_GPL(tps6586x_पढ़ोs);

पूर्णांक tps6586x_set_bits(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t bit_mask)
अणु
	काष्ठा tps6586x *tps6586x = dev_to_tps6586x(dev);

	वापस regmap_update_bits(tps6586x->regmap, reg, bit_mask, bit_mask);
पूर्ण
EXPORT_SYMBOL_GPL(tps6586x_set_bits);

पूर्णांक tps6586x_clr_bits(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t bit_mask)
अणु
	काष्ठा tps6586x *tps6586x = dev_to_tps6586x(dev);

	वापस regmap_update_bits(tps6586x->regmap, reg, bit_mask, 0);
पूर्ण
EXPORT_SYMBOL_GPL(tps6586x_clr_bits);

पूर्णांक tps6586x_update(काष्ठा device *dev, पूर्णांक reg, uपूर्णांक8_t val, uपूर्णांक8_t mask)
अणु
	काष्ठा tps6586x *tps6586x = dev_to_tps6586x(dev);

	वापस regmap_update_bits(tps6586x->regmap, reg, mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(tps6586x_update);

पूर्णांक tps6586x_irq_get_virq(काष्ठा device *dev, पूर्णांक irq)
अणु
	काष्ठा tps6586x *tps6586x = dev_to_tps6586x(dev);

	वापस irq_create_mapping(tps6586x->irq_करोमुख्य, irq);
पूर्ण
EXPORT_SYMBOL_GPL(tps6586x_irq_get_virq);

पूर्णांक tps6586x_get_version(काष्ठा device *dev)
अणु
	काष्ठा tps6586x *tps6586x = dev_get_drvdata(dev);

	वापस tps6586x->version;
पूर्ण
EXPORT_SYMBOL_GPL(tps6586x_get_version);

अटल पूर्णांक __हटाओ_subdev(काष्ठा device *dev, व्योम *unused)
अणु
	platक्रमm_device_unरेजिस्टर(to_platक्रमm_device(dev));
	वापस 0;
पूर्ण

अटल पूर्णांक tps6586x_हटाओ_subdevs(काष्ठा tps6586x *tps6586x)
अणु
	वापस device_क्रम_each_child(tps6586x->dev, शून्य, __हटाओ_subdev);
पूर्ण

अटल व्योम tps6586x_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा tps6586x *tps6586x = irq_data_get_irq_chip_data(data);

	mutex_lock(&tps6586x->irq_lock);
पूर्ण

अटल व्योम tps6586x_irq_enable(काष्ठा irq_data *irq_data)
अणु
	काष्ठा tps6586x *tps6586x = irq_data_get_irq_chip_data(irq_data);
	अचिन्हित पूर्णांक __irq = irq_data->hwirq;
	स्थिर काष्ठा tps6586x_irq_data *data = &tps6586x_irqs[__irq];

	tps6586x->mask_reg[data->mask_reg] &= ~data->mask_mask;
	tps6586x->irq_en |= (1 << __irq);
पूर्ण

अटल व्योम tps6586x_irq_disable(काष्ठा irq_data *irq_data)
अणु
	काष्ठा tps6586x *tps6586x = irq_data_get_irq_chip_data(irq_data);

	अचिन्हित पूर्णांक __irq = irq_data->hwirq;
	स्थिर काष्ठा tps6586x_irq_data *data = &tps6586x_irqs[__irq];

	tps6586x->mask_reg[data->mask_reg] |= data->mask_mask;
	tps6586x->irq_en &= ~(1 << __irq);
पूर्ण

अटल व्योम tps6586x_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा tps6586x *tps6586x = irq_data_get_irq_chip_data(data);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tps6586x->mask_reg); i++) अणु
		पूर्णांक ret;
		ret = tps6586x_ग_लिखो(tps6586x->dev,
					    TPS6586X_INT_MASK1 + i,
					    tps6586x->mask_reg[i]);
		WARN_ON(ret);
	पूर्ण

	mutex_unlock(&tps6586x->irq_lock);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tps6586x_irq_set_wake(काष्ठा irq_data *irq_data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा tps6586x *tps6586x = irq_data_get_irq_chip_data(irq_data);
	वापस irq_set_irq_wake(tps6586x->irq, on);
पूर्ण
#अन्यथा
#घोषणा tps6586x_irq_set_wake शून्य
#पूर्ण_अगर

अटल काष्ठा irq_chip tps6586x_irq_chip = अणु
	.name = "tps6586x",
	.irq_bus_lock = tps6586x_irq_lock,
	.irq_bus_sync_unlock = tps6586x_irq_sync_unlock,
	.irq_disable = tps6586x_irq_disable,
	.irq_enable = tps6586x_irq_enable,
	.irq_set_wake = tps6586x_irq_set_wake,
पूर्ण;

अटल पूर्णांक tps6586x_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
				irq_hw_number_t hw)
अणु
	काष्ठा tps6586x *tps6586x = h->host_data;

	irq_set_chip_data(virq, tps6586x);
	irq_set_chip_and_handler(virq, &tps6586x_irq_chip, handle_simple_irq);
	irq_set_nested_thपढ़ो(virq, 1);
	irq_set_noprobe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops tps6586x_करोमुख्य_ops = अणु
	.map    = tps6586x_irq_map,
	.xlate  = irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल irqवापस_t tps6586x_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tps6586x *tps6586x = data;
	uपूर्णांक32_t acks;
	__le32 val;
	पूर्णांक ret = 0;

	ret = tps6586x_पढ़ोs(tps6586x->dev, TPS6586X_INT_ACK1,
			     माप(acks), (uपूर्णांक8_t *)&val);

	अगर (ret < 0) अणु
		dev_err(tps6586x->dev, "failed to read interrupt status\n");
		वापस IRQ_NONE;
	पूर्ण

	acks = le32_to_cpu(val);

	जबतक (acks) अणु
		पूर्णांक i = __ffs(acks);

		अगर (tps6586x->irq_en & (1 << i))
			handle_nested_irq(
				irq_find_mapping(tps6586x->irq_करोमुख्य, i));

		acks &= ~(1 << i);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tps6586x_irq_init(काष्ठा tps6586x *tps6586x, पूर्णांक irq,
				       पूर्णांक irq_base)
अणु
	पूर्णांक i, ret;
	u8 पंचांगp[4];
	पूर्णांक new_irq_base;
	पूर्णांक irq_num = ARRAY_SIZE(tps6586x_irqs);

	tps6586x->irq = irq;

	mutex_init(&tps6586x->irq_lock);
	क्रम (i = 0; i < 5; i++) अणु
		tps6586x->mask_reg[i] = 0xff;
		tps6586x_ग_लिखो(tps6586x->dev, TPS6586X_INT_MASK1 + i, 0xff);
	पूर्ण

	tps6586x_पढ़ोs(tps6586x->dev, TPS6586X_INT_ACK1, माप(पंचांगp), पंचांगp);

	अगर  (irq_base > 0) अणु
		new_irq_base = irq_alloc_descs(irq_base, 0, irq_num, -1);
		अगर (new_irq_base < 0) अणु
			dev_err(tps6586x->dev,
				"Failed to alloc IRQs: %d\n", new_irq_base);
			वापस new_irq_base;
		पूर्ण
	पूर्ण अन्यथा अणु
		new_irq_base = 0;
	पूर्ण

	tps6586x->irq_करोमुख्य = irq_करोमुख्य_add_simple(tps6586x->dev->of_node,
				irq_num, new_irq_base, &tps6586x_करोमुख्य_ops,
				tps6586x);
	अगर (!tps6586x->irq_करोमुख्य) अणु
		dev_err(tps6586x->dev, "Failed to create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण
	ret = request_thपढ़ोed_irq(irq, शून्य, tps6586x_irq, IRQF_ONESHOT,
				   "tps6586x", tps6586x);

	अगर (!ret)
		device_init_wakeup(tps6586x->dev, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक tps6586x_add_subdevs(काष्ठा tps6586x *tps6586x,
					  काष्ठा tps6586x_platक्रमm_data *pdata)
अणु
	काष्ठा tps6586x_subdev_info *subdev;
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < pdata->num_subdevs; i++) अणु
		subdev = &pdata->subdevs[i];

		pdev = platक्रमm_device_alloc(subdev->name, subdev->id);
		अगर (!pdev) अणु
			ret = -ENOMEM;
			जाओ failed;
		पूर्ण

		pdev->dev.parent = tps6586x->dev;
		pdev->dev.platक्रमm_data = subdev->platक्रमm_data;
		pdev->dev.of_node = subdev->of_node;

		ret = platक्रमm_device_add(pdev);
		अगर (ret) अणु
			platक्रमm_device_put(pdev);
			जाओ failed;
		पूर्ण
	पूर्ण
	वापस 0;

failed:
	tps6586x_हटाओ_subdevs(tps6586x);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा tps6586x_platक्रमm_data *tps6586x_parse_dt(काष्ठा i2c_client *client)
अणु
	काष्ठा device_node *np = client->dev.of_node;
	काष्ठा tps6586x_platक्रमm_data *pdata;

	pdata = devm_kzalloc(&client->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	pdata->num_subdevs = 0;
	pdata->subdevs = शून्य;
	pdata->gpio_base = -1;
	pdata->irq_base = -1;
	pdata->pm_off = of_property_पढ़ो_bool(np, "ti,system-power-controller");

	वापस pdata;
पूर्ण

अटल स्थिर काष्ठा of_device_id tps6586x_of_match[] = अणु
	अणु .compatible = "ti,tps6586x", पूर्ण,
	अणु पूर्ण,
पूर्ण;
#अन्यथा
अटल काष्ठा tps6586x_platक्रमm_data *tps6586x_parse_dt(काष्ठा i2c_client *client)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल bool is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* Cache all पूर्णांकerrupt mask रेजिस्टर */
	अगर ((reg >= TPS6586X_INT_MASK1) && (reg <= TPS6586X_INT_MASK5))
		वापस false;

	वापस true;
पूर्ण

अटल स्थिर काष्ठा regmap_config tps6586x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = TPS6586X_MAX_REGISTER,
	.अस्थिर_reg = is_अस्थिर_reg,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल काष्ठा device *tps6586x_dev;
अटल व्योम tps6586x_घातer_off(व्योम)
अणु
	अगर (tps6586x_clr_bits(tps6586x_dev, TPS6586X_SUPPLYENE, EXITSLREQ_BIT))
		वापस;

	tps6586x_set_bits(tps6586x_dev, TPS6586X_SUPPLYENE, SLEEP_MODE_BIT);
पूर्ण

अटल व्योम tps6586x_prपूर्णांक_version(काष्ठा i2c_client *client, पूर्णांक version)
अणु
	स्थिर अक्षर *name;

	चयन (version) अणु
	हाल TPS658621A:
		name = "TPS658621A";
		अवरोध;
	हाल TPS658621CD:
		name = "TPS658621C/D";
		अवरोध;
	हाल TPS658623:
		name = "TPS658623";
		अवरोध;
	हाल TPS658640:
	हाल TPS658640v2:
		name = "TPS658640";
		अवरोध;
	हाल TPS658643:
		name = "TPS658643";
		अवरोध;
	शेष:
		name = "TPS6586X";
		अवरोध;
	पूर्ण

	dev_info(&client->dev, "Found %s, VERSIONCRC is %02x\n", name, version);
पूर्ण

अटल पूर्णांक tps6586x_i2c_probe(काष्ठा i2c_client *client,
					स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tps6586x_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा tps6586x *tps6586x;
	पूर्णांक ret;
	पूर्णांक version;

	अगर (!pdata && client->dev.of_node)
		pdata = tps6586x_parse_dt(client);

	अगर (!pdata) अणु
		dev_err(&client->dev, "tps6586x requires platform data\n");
		वापस -ENOTSUPP;
	पूर्ण

	version = i2c_smbus_पढ़ो_byte_data(client, TPS6586X_VERSIONCRC);
	अगर (version < 0) अणु
		dev_err(&client->dev, "Chip ID read failed: %d\n", version);
		वापस -EIO;
	पूर्ण

	tps6586x = devm_kzalloc(&client->dev, माप(*tps6586x), GFP_KERNEL);
	अगर (!tps6586x)
		वापस -ENOMEM;

	tps6586x->version = version;
	tps6586x_prपूर्णांक_version(client, tps6586x->version);

	tps6586x->client = client;
	tps6586x->dev = &client->dev;
	i2c_set_clientdata(client, tps6586x);

	tps6586x->regmap = devm_regmap_init_i2c(client,
					&tps6586x_regmap_config);
	अगर (IS_ERR(tps6586x->regmap)) अणु
		ret = PTR_ERR(tps6586x->regmap);
		dev_err(&client->dev, "regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण


	अगर (client->irq) अणु
		ret = tps6586x_irq_init(tps6586x, client->irq,
					pdata->irq_base);
		अगर (ret) अणु
			dev_err(&client->dev, "IRQ init failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = mfd_add_devices(tps6586x->dev, -1,
			      tps6586x_cell, ARRAY_SIZE(tps6586x_cell),
			      शून्य, 0, tps6586x->irq_करोमुख्य);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "mfd_add_devices failed: %d\n", ret);
		जाओ err_mfd_add;
	पूर्ण

	ret = tps6586x_add_subdevs(tps6586x, pdata);
	अगर (ret) अणु
		dev_err(&client->dev, "add devices failed: %d\n", ret);
		जाओ err_add_devs;
	पूर्ण

	अगर (pdata->pm_off && !pm_घातer_off) अणु
		tps6586x_dev = &client->dev;
		pm_घातer_off = tps6586x_घातer_off;
	पूर्ण

	वापस 0;

err_add_devs:
	mfd_हटाओ_devices(tps6586x->dev);
err_mfd_add:
	अगर (client->irq)
		मुक्त_irq(client->irq, tps6586x);
	वापस ret;
पूर्ण

अटल पूर्णांक tps6586x_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tps6586x *tps6586x = i2c_get_clientdata(client);

	tps6586x_हटाओ_subdevs(tps6586x);
	mfd_हटाओ_devices(tps6586x->dev);
	अगर (client->irq)
		मुक्त_irq(client->irq, tps6586x);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tps6586x_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा tps6586x *tps6586x = dev_get_drvdata(dev);

	अगर (tps6586x->client->irq)
		disable_irq(tps6586x->client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tps6586x_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा tps6586x *tps6586x = dev_get_drvdata(dev);

	अगर (tps6586x->client->irq)
		enable_irq(tps6586x->client->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tps6586x_pm_ops, tps6586x_i2c_suspend,
			 tps6586x_i2c_resume);

अटल स्थिर काष्ठा i2c_device_id tps6586x_id_table[] = अणु
	अणु "tps6586x", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tps6586x_id_table);

अटल काष्ठा i2c_driver tps6586x_driver = अणु
	.driver	= अणु
		.name	= "tps6586x",
		.of_match_table = of_match_ptr(tps6586x_of_match),
		.pm	= &tps6586x_pm_ops,
	पूर्ण,
	.probe		= tps6586x_i2c_probe,
	.हटाओ		= tps6586x_i2c_हटाओ,
	.id_table	= tps6586x_id_table,
पूर्ण;

अटल पूर्णांक __init tps6586x_init(व्योम)
अणु
	वापस i2c_add_driver(&tps6586x_driver);
पूर्ण
subsys_initcall(tps6586x_init);

अटल व्योम __निकास tps6586x_निकास(व्योम)
अणु
	i2c_del_driver(&tps6586x_driver);
पूर्ण
module_निकास(tps6586x_निकास);

MODULE_DESCRIPTION("TPS6586X core driver");
MODULE_AUTHOR("Mike Rapoport <mike@compulab.co.il>");
MODULE_LICENSE("GPL");
