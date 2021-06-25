<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Digital I/O driver क्रम Technologic Systems TS-5500
 *
 * Copyright (c) 2012 Savoir-faire Linux Inc.
 *	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 *
 * Technologic Systems platक्रमms have pin blocks, exposing several Digital
 * Input/Output lines (DIO). This driver aims to support single pin blocks.
 * In that sense, the support is not limited to the TS-5500 blocks.
 * Actually, the following platक्रमms have DIO support:
 *
 * TS-5500:
 *   Documentation: http://wiki.embeddedarm.com/wiki/TS-5500
 *   Blocks: DIO1, DIO2 and LCD port.
 *
 * TS-5600:
 *   Documentation: http://wiki.embeddedarm.com/wiki/TS-5600
 *   Blocks: LCD port (identical to TS-5500 LCD).
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/* List of supported Technologic Systems platक्रमms DIO blocks */
क्रमागत ts5500_blocks अणु TS5500_DIO1, TS5500_DIO2, TS5500_LCD, TS5600_LCD पूर्ण;

काष्ठा ts5500_priv अणु
	स्थिर काष्ठा ts5500_dio *pinout;
	काष्ठा gpio_chip gpio_chip;
	spinlock_t lock;
	bool strap;
	u8 hwirq;
पूर्ण;

/*
 * Hex 7D is used to control several blocks (e.g. DIO2 and LCD port).
 * This flag ensures that the region has been requested by this driver.
 */
अटल bool hex7d_reserved;

/*
 * This काष्ठाure is used to describe capabilities of DIO lines,
 * such as available directions and connected पूर्णांकerrupt (अगर any).
 */
काष्ठा ts5500_dio अणु
	स्थिर u8 value_addr;
	स्थिर u8 value_mask;
	स्थिर u8 control_addr;
	स्थिर u8 control_mask;
	स्थिर bool no_input;
	स्थिर bool no_output;
	स्थिर u8 irq;
पूर्ण;

#घोषणा TS5500_DIO_IN_OUT(vaddr, vbit, caddr, cbit)	\
	अणु						\
		.value_addr = vaddr,			\
		.value_mask = BIT(vbit),		\
		.control_addr = caddr,			\
		.control_mask = BIT(cbit),		\
	पूर्ण

#घोषणा TS5500_DIO_IN(addr, bit)		\
	अणु					\
		.value_addr = addr,		\
		.value_mask = BIT(bit),		\
		.no_output = true,		\
	पूर्ण

#घोषणा TS5500_DIO_IN_IRQ(addr, bit, _irq)	\
	अणु					\
		.value_addr = addr,		\
		.value_mask = BIT(bit),		\
		.no_output = true,		\
		.irq = _irq,			\
	पूर्ण

#घोषणा TS5500_DIO_OUT(addr, bit)		\
	अणु					\
		.value_addr = addr,		\
		.value_mask = BIT(bit),		\
		.no_input = true,		\
	पूर्ण

/*
 * Input/Output DIO lines are programmed in groups of 4. Their values are
 * available through 4 consecutive bits in a value port, whereas the direction
 * of these 4 lines is driven by only 1 bit in a control port.
 */
#घोषणा TS5500_DIO_GROUP(vaddr, vbitfrom, caddr, cbit)		\
	TS5500_DIO_IN_OUT(vaddr, vbitfrom + 0, caddr, cbit),	\
	TS5500_DIO_IN_OUT(vaddr, vbitfrom + 1, caddr, cbit),	\
	TS5500_DIO_IN_OUT(vaddr, vbitfrom + 2, caddr, cbit),	\
	TS5500_DIO_IN_OUT(vaddr, vbitfrom + 3, caddr, cbit)

/*
 * TS-5500 DIO1 block
 *
 *  value    control  dir    hw
 *  addr bit addr bit in out irq name     pin offset
 *
 *  0x7b  0  0x7a  0  x   x      DIO1_0   1   0
 *  0x7b  1  0x7a  0  x   x      DIO1_1   3   1
 *  0x7b  2  0x7a  0  x   x      DIO1_2   5   2
 *  0x7b  3  0x7a  0  x   x      DIO1_3   7   3
 *  0x7b  4  0x7a  1  x   x      DIO1_4   9   4
 *  0x7b  5  0x7a  1  x   x      DIO1_5   11  5
 *  0x7b  6  0x7a  1  x   x      DIO1_6   13  6
 *  0x7b  7  0x7a  1  x   x      DIO1_7   15  7
 *  0x7c  0  0x7a  5  x   x      DIO1_8   4   8
 *  0x7c  1  0x7a  5  x   x      DIO1_9   6   9
 *  0x7c  2  0x7a  5  x   x      DIO1_10  8   10
 *  0x7c  3  0x7a  5  x   x      DIO1_11  10  11
 *  0x7c  4           x          DIO1_12  12  12
 *  0x7c  5           x      7   DIO1_13  14  13
 */
अटल स्थिर काष्ठा ts5500_dio ts5500_dio1[] = अणु
	TS5500_DIO_GROUP(0x7b, 0, 0x7a, 0),
	TS5500_DIO_GROUP(0x7b, 4, 0x7a, 1),
	TS5500_DIO_GROUP(0x7c, 0, 0x7a, 5),
	TS5500_DIO_IN(0x7c, 4),
	TS5500_DIO_IN_IRQ(0x7c, 5, 7),
पूर्ण;

/*
 * TS-5500 DIO2 block
 *
 *  value    control  dir    hw
 *  addr bit addr bit in out irq name     pin offset
 *
 *  0x7e  0  0x7d  0  x   x      DIO2_0   1   0
 *  0x7e  1  0x7d  0  x   x      DIO2_1   3   1
 *  0x7e  2  0x7d  0  x   x      DIO2_2   5   2
 *  0x7e  3  0x7d  0  x   x      DIO2_3   7   3
 *  0x7e  4  0x7d  1  x   x      DIO2_4   9   4
 *  0x7e  5  0x7d  1  x   x      DIO2_5   11  5
 *  0x7e  6  0x7d  1  x   x      DIO2_6   13  6
 *  0x7e  7  0x7d  1  x   x      DIO2_7   15  7
 *  0x7f  0  0x7d  5  x   x      DIO2_8   4   8
 *  0x7f  1  0x7d  5  x   x      DIO2_9   6   9
 *  0x7f  2  0x7d  5  x   x      DIO2_10  8   10
 *  0x7f  3  0x7d  5  x   x      DIO2_11  10  11
 *  0x7f  4           x      6   DIO2_13  14  12
 */
अटल स्थिर काष्ठा ts5500_dio ts5500_dio2[] = अणु
	TS5500_DIO_GROUP(0x7e, 0, 0x7d, 0),
	TS5500_DIO_GROUP(0x7e, 4, 0x7d, 1),
	TS5500_DIO_GROUP(0x7f, 0, 0x7d, 5),
	TS5500_DIO_IN_IRQ(0x7f, 4, 6),
पूर्ण;

/*
 * TS-5500 LCD port used as DIO block
 * TS-5600 LCD port is identical
 *
 *  value    control  dir    hw
 *  addr bit addr bit in out irq name    pin offset
 *
 *  0x72  0  0x7d  2  x   x      LCD_0   8   0
 *  0x72  1  0x7d  2  x   x      LCD_1   7   1
 *  0x72  2  0x7d  2  x   x      LCD_2   10  2
 *  0x72  3  0x7d  2  x   x      LCD_3   9   3
 *  0x72  4  0x7d  3  x   x      LCD_4   12  4
 *  0x72  5  0x7d  3  x   x      LCD_5   11  5
 *  0x72  6  0x7d  3  x   x      LCD_6   14  6
 *  0x72  7  0x7d  3  x   x      LCD_7   13  7
 *  0x73  0               x      LCD_EN  5   8
 *  0x73  6           x          LCD_WR  6   9
 *  0x73  7           x      1   LCD_RS  3   10
 */
अटल स्थिर काष्ठा ts5500_dio ts5500_lcd[] = अणु
	TS5500_DIO_GROUP(0x72, 0, 0x7d, 2),
	TS5500_DIO_GROUP(0x72, 4, 0x7d, 3),
	TS5500_DIO_OUT(0x73, 0),
	TS5500_DIO_IN(0x73, 6),
	TS5500_DIO_IN_IRQ(0x73, 7, 1),
पूर्ण;

अटल अंतरभूत व्योम ts5500_set_mask(u8 mask, u8 addr)
अणु
	u8 val = inb(addr);
	val |= mask;
	outb(val, addr);
पूर्ण

अटल अंतरभूत व्योम ts5500_clear_mask(u8 mask, u8 addr)
अणु
	u8 val = inb(addr);
	val &= ~mask;
	outb(val, addr);
पूर्ण

अटल पूर्णांक ts5500_gpio_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा ts5500_priv *priv = gpiochip_get_data(chip);
	स्थिर काष्ठा ts5500_dio line = priv->pinout[offset];
	अचिन्हित दीर्घ flags;

	अगर (line.no_input)
		वापस -ENXIO;

	अगर (line.no_output)
		वापस 0;

	spin_lock_irqsave(&priv->lock, flags);
	ts5500_clear_mask(line.control_mask, line.control_addr);
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ts5500_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा ts5500_priv *priv = gpiochip_get_data(chip);
	स्थिर काष्ठा ts5500_dio line = priv->pinout[offset];

	वापस !!(inb(line.value_addr) & line.value_mask);
पूर्ण

अटल पूर्णांक ts5500_gpio_output(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा ts5500_priv *priv = gpiochip_get_data(chip);
	स्थिर काष्ठा ts5500_dio line = priv->pinout[offset];
	अचिन्हित दीर्घ flags;

	अगर (line.no_output)
		वापस -ENXIO;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (!line.no_input)
		ts5500_set_mask(line.control_mask, line.control_addr);

	अगर (val)
		ts5500_set_mask(line.value_mask, line.value_addr);
	अन्यथा
		ts5500_clear_mask(line.value_mask, line.value_addr);
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम ts5500_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा ts5500_priv *priv = gpiochip_get_data(chip);
	स्थिर काष्ठा ts5500_dio line = priv->pinout[offset];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (val)
		ts5500_set_mask(line.value_mask, line.value_addr);
	अन्यथा
		ts5500_clear_mask(line.value_mask, line.value_addr);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल पूर्णांक ts5500_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा ts5500_priv *priv = gpiochip_get_data(chip);
	स्थिर काष्ठा ts5500_dio *block = priv->pinout;
	स्थिर काष्ठा ts5500_dio line = block[offset];

	/* Only one pin is connected to an पूर्णांकerrupt */
	अगर (line.irq)
		वापस line.irq;

	/* As this pin is input-only, we may strap it to another in/out pin */
	अगर (priv->strap)
		वापस priv->hwirq;

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक ts5500_enable_irq(काष्ठा ts5500_priv *priv)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->hwirq == 7)
		ts5500_set_mask(BIT(7), 0x7a); /* DIO1_13 on IRQ7 */
	अन्यथा अगर (priv->hwirq == 6)
		ts5500_set_mask(BIT(7), 0x7d); /* DIO2_13 on IRQ6 */
	अन्यथा अगर (priv->hwirq == 1)
		ts5500_set_mask(BIT(6), 0x7d); /* LCD_RS on IRQ1 */
	अन्यथा
		ret = -EINVAL;
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम ts5500_disable_irq(काष्ठा ts5500_priv *priv)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->hwirq == 7)
		ts5500_clear_mask(BIT(7), 0x7a); /* DIO1_13 on IRQ7 */
	अन्यथा अगर (priv->hwirq == 6)
		ts5500_clear_mask(BIT(7), 0x7d); /* DIO2_13 on IRQ6 */
	अन्यथा अगर (priv->hwirq == 1)
		ts5500_clear_mask(BIT(6), 0x7d); /* LCD_RS on IRQ1 */
	अन्यथा
		dev_err(priv->gpio_chip.parent, "invalid hwirq %d\n",
			priv->hwirq);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल पूर्णांक ts5500_dio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	क्रमागत ts5500_blocks block = platक्रमm_get_device_id(pdev)->driver_data;
	काष्ठा device *dev = &pdev->dev;
	स्थिर अक्षर *name = dev_name(dev);
	काष्ठा ts5500_priv *priv;
	काष्ठा resource *res;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(dev, "missing IRQ resource\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(dev, माप(काष्ठा ts5500_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);
	priv->hwirq = res->start;
	spin_lock_init(&priv->lock);

	priv->gpio_chip.owner = THIS_MODULE;
	priv->gpio_chip.label = name;
	priv->gpio_chip.parent = dev;
	priv->gpio_chip.direction_input = ts5500_gpio_input;
	priv->gpio_chip.direction_output = ts5500_gpio_output;
	priv->gpio_chip.get = ts5500_gpio_get;
	priv->gpio_chip.set = ts5500_gpio_set;
	priv->gpio_chip.to_irq = ts5500_gpio_to_irq;
	priv->gpio_chip.base = -1;

	चयन (block) अणु
	हाल TS5500_DIO1:
		priv->pinout = ts5500_dio1;
		priv->gpio_chip.ngpio = ARRAY_SIZE(ts5500_dio1);

		अगर (!devm_request_region(dev, 0x7a, 3, name)) अणु
			dev_err(dev, "failed to request %s ports\n", name);
			वापस -EBUSY;
		पूर्ण
		अवरोध;
	हाल TS5500_DIO2:
		priv->pinout = ts5500_dio2;
		priv->gpio_chip.ngpio = ARRAY_SIZE(ts5500_dio2);

		अगर (!devm_request_region(dev, 0x7e, 2, name)) अणु
			dev_err(dev, "failed to request %s ports\n", name);
			वापस -EBUSY;
		पूर्ण

		अगर (hex7d_reserved)
			अवरोध;

		अगर (!devm_request_region(dev, 0x7d, 1, name)) अणु
			dev_err(dev, "failed to request %s 7D\n", name);
			वापस -EBUSY;
		पूर्ण

		hex7d_reserved = true;
		अवरोध;
	हाल TS5500_LCD:
	हाल TS5600_LCD:
		priv->pinout = ts5500_lcd;
		priv->gpio_chip.ngpio = ARRAY_SIZE(ts5500_lcd);

		अगर (!devm_request_region(dev, 0x72, 2, name)) अणु
			dev_err(dev, "failed to request %s ports\n", name);
			वापस -EBUSY;
		पूर्ण

		अगर (!hex7d_reserved) अणु
			अगर (!devm_request_region(dev, 0x7d, 1, name)) अणु
				dev_err(dev, "failed to request %s 7D\n", name);
				वापस -EBUSY;
			पूर्ण

			hex7d_reserved = true;
		पूर्ण

		/* Ensure usage of LCD port as DIO */
		spin_lock_irqsave(&priv->lock, flags);
		ts5500_clear_mask(BIT(4), 0x7d);
		spin_unlock_irqrestore(&priv->lock, flags);
		अवरोध;
	पूर्ण

	ret = devm_gpiochip_add_data(dev, &priv->gpio_chip, priv);
	अगर (ret) अणु
		dev_err(dev, "failed to register the gpio chip\n");
		वापस ret;
	पूर्ण

	ret = ts5500_enable_irq(priv);
	अगर (ret) अणु
		dev_err(dev, "invalid interrupt %d\n", priv->hwirq);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ts5500_dio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ts5500_priv *priv = platक्रमm_get_drvdata(pdev);

	ts5500_disable_irq(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id ts5500_dio_ids[] = अणु
	अणु "ts5500-dio1", TS5500_DIO1 पूर्ण,
	अणु "ts5500-dio2", TS5500_DIO2 पूर्ण,
	अणु "ts5500-dio-lcd", TS5500_LCD पूर्ण,
	अणु "ts5600-dio-lcd", TS5600_LCD पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, ts5500_dio_ids);

अटल काष्ठा platक्रमm_driver ts5500_dio_driver = अणु
	.driver = अणु
		.name = "ts5500-dio",
	पूर्ण,
	.probe = ts5500_dio_probe,
	.हटाओ = ts5500_dio_हटाओ,
	.id_table = ts5500_dio_ids,
पूर्ण;

module_platक्रमm_driver(ts5500_dio_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Savoir-faire Linux Inc. <kernel@savoirfairelinux.com>");
MODULE_DESCRIPTION("Technologic Systems TS-5500 Digital I/O driver");
