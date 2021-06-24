<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2009-2011 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (C) 2013 John Crispin <blogic@खोलोwrt.org>
 */

#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#घोषणा MTK_BANK_CNT	3
#घोषणा MTK_BANK_WIDTH	32

#घोषणा GPIO_BANK_STRIDE	0x04
#घोषणा GPIO_REG_CTRL		0x00
#घोषणा GPIO_REG_POL		0x10
#घोषणा GPIO_REG_DATA		0x20
#घोषणा GPIO_REG_DSET		0x30
#घोषणा GPIO_REG_DCLR		0x40
#घोषणा GPIO_REG_REDGE		0x50
#घोषणा GPIO_REG_FEDGE		0x60
#घोषणा GPIO_REG_HLVL		0x70
#घोषणा GPIO_REG_LLVL		0x80
#घोषणा GPIO_REG_STAT		0x90
#घोषणा GPIO_REG_EDGE		0xA0

काष्ठा mtk_gc अणु
	काष्ठा irq_chip irq_chip;
	काष्ठा gpio_chip chip;
	spinlock_t lock;
	पूर्णांक bank;
	u32 rising;
	u32 falling;
	u32 hlevel;
	u32 llevel;
पूर्ण;

/**
 * काष्ठा mtk - state container क्रम
 * data of the platक्रमm driver. It is 3
 * separate gpio-chip each one with its
 * own irq_chip.
 * @dev: device instance
 * @base: memory base address
 * @gpio_irq: irq number from the device tree
 * @gc_map: array of the gpio chips
 */
काष्ठा mtk अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	पूर्णांक gpio_irq;
	काष्ठा mtk_gc gc_map[MTK_BANK_CNT];
पूर्ण;

अटल अंतरभूत काष्ठा mtk_gc *
to_mediatek_gpio(काष्ठा gpio_chip *chip)
अणु
	वापस container_of(chip, काष्ठा mtk_gc, chip);
पूर्ण

अटल अंतरभूत व्योम
mtk_gpio_w32(काष्ठा mtk_gc *rg, u32 offset, u32 val)
अणु
	काष्ठा gpio_chip *gc = &rg->chip;
	काष्ठा mtk *mtk = gpiochip_get_data(gc);

	offset = (rg->bank * GPIO_BANK_STRIDE) + offset;
	gc->ग_लिखो_reg(mtk->base + offset, val);
पूर्ण

अटल अंतरभूत u32
mtk_gpio_r32(काष्ठा mtk_gc *rg, u32 offset)
अणु
	काष्ठा gpio_chip *gc = &rg->chip;
	काष्ठा mtk *mtk = gpiochip_get_data(gc);

	offset = (rg->bank * GPIO_BANK_STRIDE) + offset;
	वापस gc->पढ़ो_reg(mtk->base + offset);
पूर्ण

अटल irqवापस_t
mediatek_gpio_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा gpio_chip *gc = data;
	काष्ठा mtk_gc *rg = to_mediatek_gpio(gc);
	irqवापस_t ret = IRQ_NONE;
	अचिन्हित दीर्घ pending;
	पूर्णांक bit;

	pending = mtk_gpio_r32(rg, GPIO_REG_STAT);

	क्रम_each_set_bit(bit, &pending, MTK_BANK_WIDTH) अणु
		u32 map = irq_find_mapping(gc->irq.करोमुख्य, bit);

		generic_handle_irq(map);
		mtk_gpio_w32(rg, GPIO_REG_STAT, BIT(bit));
		ret |= IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
mediatek_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा mtk_gc *rg = to_mediatek_gpio(gc);
	पूर्णांक pin = d->hwirq;
	अचिन्हित दीर्घ flags;
	u32 rise, fall, high, low;

	spin_lock_irqsave(&rg->lock, flags);
	rise = mtk_gpio_r32(rg, GPIO_REG_REDGE);
	fall = mtk_gpio_r32(rg, GPIO_REG_FEDGE);
	high = mtk_gpio_r32(rg, GPIO_REG_HLVL);
	low = mtk_gpio_r32(rg, GPIO_REG_LLVL);
	mtk_gpio_w32(rg, GPIO_REG_REDGE, rise | (BIT(pin) & rg->rising));
	mtk_gpio_w32(rg, GPIO_REG_FEDGE, fall | (BIT(pin) & rg->falling));
	mtk_gpio_w32(rg, GPIO_REG_HLVL, high | (BIT(pin) & rg->hlevel));
	mtk_gpio_w32(rg, GPIO_REG_LLVL, low | (BIT(pin) & rg->llevel));
	spin_unlock_irqrestore(&rg->lock, flags);
पूर्ण

अटल व्योम
mediatek_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा mtk_gc *rg = to_mediatek_gpio(gc);
	पूर्णांक pin = d->hwirq;
	अचिन्हित दीर्घ flags;
	u32 rise, fall, high, low;

	spin_lock_irqsave(&rg->lock, flags);
	rise = mtk_gpio_r32(rg, GPIO_REG_REDGE);
	fall = mtk_gpio_r32(rg, GPIO_REG_FEDGE);
	high = mtk_gpio_r32(rg, GPIO_REG_HLVL);
	low = mtk_gpio_r32(rg, GPIO_REG_LLVL);
	mtk_gpio_w32(rg, GPIO_REG_FEDGE, fall & ~BIT(pin));
	mtk_gpio_w32(rg, GPIO_REG_REDGE, rise & ~BIT(pin));
	mtk_gpio_w32(rg, GPIO_REG_HLVL, high & ~BIT(pin));
	mtk_gpio_w32(rg, GPIO_REG_LLVL, low & ~BIT(pin));
	spin_unlock_irqrestore(&rg->lock, flags);
पूर्ण

अटल पूर्णांक
mediatek_gpio_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा mtk_gc *rg = to_mediatek_gpio(gc);
	पूर्णांक pin = d->hwirq;
	u32 mask = BIT(pin);

	अगर (type == IRQ_TYPE_PROBE) अणु
		अगर ((rg->rising | rg->falling |
		     rg->hlevel | rg->llevel) & mask)
			वापस 0;

		type = IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING;
	पूर्ण

	rg->rising &= ~mask;
	rg->falling &= ~mask;
	rg->hlevel &= ~mask;
	rg->llevel &= ~mask;

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		rg->rising |= mask;
		rg->falling |= mask;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		rg->rising |= mask;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		rg->falling |= mask;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		rg->hlevel |= mask;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		rg->llevel |= mask;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mediatek_gpio_xlate(काष्ठा gpio_chip *chip,
		    स्थिर काष्ठा of_phandle_args *spec, u32 *flags)
अणु
	पूर्णांक gpio = spec->args[0];
	काष्ठा mtk_gc *rg = to_mediatek_gpio(chip);

	अगर (rg->bank != gpio / MTK_BANK_WIDTH)
		वापस -EINVAL;

	अगर (flags)
		*flags = spec->args[1];

	वापस gpio % MTK_BANK_WIDTH;
पूर्ण

अटल पूर्णांक
mediatek_gpio_bank_probe(काष्ठा device *dev,
			 काष्ठा device_node *node, पूर्णांक bank)
अणु
	काष्ठा mtk *mtk = dev_get_drvdata(dev);
	काष्ठा mtk_gc *rg;
	व्योम __iomem *dat, *set, *ctrl, *diro;
	पूर्णांक ret;

	rg = &mtk->gc_map[bank];
	स_रखो(rg, 0, माप(*rg));

	spin_lock_init(&rg->lock);
	rg->chip.of_node = node;
	rg->bank = bank;

	dat = mtk->base + GPIO_REG_DATA + (rg->bank * GPIO_BANK_STRIDE);
	set = mtk->base + GPIO_REG_DSET + (rg->bank * GPIO_BANK_STRIDE);
	ctrl = mtk->base + GPIO_REG_DCLR + (rg->bank * GPIO_BANK_STRIDE);
	diro = mtk->base + GPIO_REG_CTRL + (rg->bank * GPIO_BANK_STRIDE);

	ret = bgpio_init(&rg->chip, dev, 4, dat, set, ctrl, diro, शून्य,
			 BGPIOF_NO_SET_ON_INPUT);
	अगर (ret) अणु
		dev_err(dev, "bgpio_init() failed\n");
		वापस ret;
	पूर्ण

	rg->chip.of_gpio_n_cells = 2;
	rg->chip.of_xlate = mediatek_gpio_xlate;
	rg->chip.label = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s-bank%d",
					dev_name(dev), bank);
	अगर (!rg->chip.label)
		वापस -ENOMEM;

	rg->irq_chip.name = dev_name(dev);
	rg->irq_chip.parent_device = dev;
	rg->irq_chip.irq_unmask = mediatek_gpio_irq_unmask;
	rg->irq_chip.irq_mask = mediatek_gpio_irq_mask;
	rg->irq_chip.irq_mask_ack = mediatek_gpio_irq_mask;
	rg->irq_chip.irq_set_type = mediatek_gpio_irq_type;

	अगर (mtk->gpio_irq) अणु
		काष्ठा gpio_irq_chip *girq;

		/*
		 * Directly request the irq here instead of passing
		 * a flow-handler because the irq is shared.
		 */
		ret = devm_request_irq(dev, mtk->gpio_irq,
				       mediatek_gpio_irq_handler, IRQF_SHARED,
				       rg->chip.label, &rg->chip);

		अगर (ret) अणु
			dev_err(dev, "Error requesting IRQ %d: %d\n",
				mtk->gpio_irq, ret);
			वापस ret;
		पूर्ण

		girq = &rg->chip.irq;
		girq->chip = &rg->irq_chip;
		/* This will let us handle the parent IRQ in the driver */
		girq->parent_handler = शून्य;
		girq->num_parents = 0;
		girq->parents = शून्य;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_simple_irq;
	पूर्ण

	ret = devm_gpiochip_add_data(dev, &rg->chip, mtk);
	अगर (ret < 0) अणु
		dev_err(dev, "Could not register gpio %d, ret=%d\n",
			rg->chip.ngpio, ret);
		वापस ret;
	पूर्ण

	/* set polarity to low क्रम all gpios */
	mtk_gpio_w32(rg, GPIO_REG_POL, 0);

	dev_info(dev, "registering %d gpios\n", rg->chip.ngpio);

	वापस 0;
पूर्ण

अटल पूर्णांक
mediatek_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा mtk *mtk;
	पूर्णांक i;
	पूर्णांक ret;

	mtk = devm_kzalloc(dev, माप(*mtk), GFP_KERNEL);
	अगर (!mtk)
		वापस -ENOMEM;

	mtk->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mtk->base))
		वापस PTR_ERR(mtk->base);

	mtk->gpio_irq = irq_of_parse_and_map(np, 0);
	mtk->dev = dev;
	platक्रमm_set_drvdata(pdev, mtk);

	क्रम (i = 0; i < MTK_BANK_CNT; i++) अणु
		ret = mediatek_gpio_bank_probe(dev, np, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mediatek_gpio_match[] = अणु
	अणु .compatible = "mediatek,mt7621-gpio" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mediatek_gpio_match);

अटल काष्ठा platक्रमm_driver mediatek_gpio_driver = अणु
	.probe = mediatek_gpio_probe,
	.driver = अणु
		.name = "mt7621_gpio",
		.of_match_table = mediatek_gpio_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(mediatek_gpio_driver);
