<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Emma Mobile GPIO Support - GIO
 *
 *  Copyright (C) 2012 Magnus Damm
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/pinctrl/consumer.h>

काष्ठा em_gio_priv अणु
	व्योम __iomem *base0;
	व्योम __iomem *base1;
	spinlock_t sense_lock;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा gpio_chip gpio_chip;
	काष्ठा irq_chip irq_chip;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
पूर्ण;

#घोषणा GIO_E1 0x00
#घोषणा GIO_E0 0x04
#घोषणा GIO_EM 0x04
#घोषणा GIO_OL 0x08
#घोषणा GIO_OH 0x0c
#घोषणा GIO_I 0x10
#घोषणा GIO_IIA 0x14
#घोषणा GIO_IEN 0x18
#घोषणा GIO_IDS 0x1c
#घोषणा GIO_IIM 0x1c
#घोषणा GIO_RAW 0x20
#घोषणा GIO_MST 0x24
#घोषणा GIO_IIR 0x28

#घोषणा GIO_IDT0 0x40
#घोषणा GIO_IDT1 0x44
#घोषणा GIO_IDT2 0x48
#घोषणा GIO_IDT3 0x4c
#घोषणा GIO_RAWBL 0x50
#घोषणा GIO_RAWBH 0x54
#घोषणा GIO_IRBL 0x58
#घोषणा GIO_IRBH 0x5c

#घोषणा GIO_IDT(n) (GIO_IDT0 + ((n) * 4))

अटल अंतरभूत अचिन्हित दीर्घ em_gio_पढ़ो(काष्ठा em_gio_priv *p, पूर्णांक offs)
अणु
	अगर (offs < GIO_IDT0)
		वापस ioपढ़ो32(p->base0 + offs);
	अन्यथा
		वापस ioपढ़ो32(p->base1 + (offs - GIO_IDT0));
पूर्ण

अटल अंतरभूत व्योम em_gio_ग_लिखो(काष्ठा em_gio_priv *p, पूर्णांक offs,
				अचिन्हित दीर्घ value)
अणु
	अगर (offs < GIO_IDT0)
		ioग_लिखो32(value, p->base0 + offs);
	अन्यथा
		ioग_लिखो32(value, p->base1 + (offs - GIO_IDT0));
पूर्ण

अटल व्योम em_gio_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा em_gio_priv *p = irq_data_get_irq_chip_data(d);

	em_gio_ग_लिखो(p, GIO_IDS, BIT(irqd_to_hwirq(d)));
पूर्ण

अटल व्योम em_gio_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा em_gio_priv *p = irq_data_get_irq_chip_data(d);

	em_gio_ग_लिखो(p, GIO_IEN, BIT(irqd_to_hwirq(d)));
पूर्ण

अटल पूर्णांक em_gio_irq_reqres(काष्ठा irq_data *d)
अणु
	काष्ठा em_gio_priv *p = irq_data_get_irq_chip_data(d);
	पूर्णांक ret;

	ret = gpiochip_lock_as_irq(&p->gpio_chip, irqd_to_hwirq(d));
	अगर (ret) अणु
		dev_err(p->gpio_chip.parent,
			"unable to lock HW IRQ %lu for IRQ\n",
			irqd_to_hwirq(d));
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम em_gio_irq_relres(काष्ठा irq_data *d)
अणु
	काष्ठा em_gio_priv *p = irq_data_get_irq_chip_data(d);

	gpiochip_unlock_as_irq(&p->gpio_chip, irqd_to_hwirq(d));
पूर्ण


#घोषणा GIO_ASYNC(x) (x + 8)

अटल अचिन्हित अक्षर em_gio_sense_table[IRQ_TYPE_SENSE_MASK + 1] = अणु
	[IRQ_TYPE_EDGE_RISING] = GIO_ASYNC(0x00),
	[IRQ_TYPE_EDGE_FALLING] = GIO_ASYNC(0x01),
	[IRQ_TYPE_LEVEL_HIGH] = GIO_ASYNC(0x02),
	[IRQ_TYPE_LEVEL_LOW] = GIO_ASYNC(0x03),
	[IRQ_TYPE_EDGE_BOTH] = GIO_ASYNC(0x04),
पूर्ण;

अटल पूर्णांक em_gio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित अक्षर value = em_gio_sense_table[type & IRQ_TYPE_SENSE_MASK];
	काष्ठा em_gio_priv *p = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक reg, offset, shअगरt;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ पंचांगp;

	अगर (!value)
		वापस -EINVAL;

	offset = irqd_to_hwirq(d);

	pr_debug("gio: sense irq = %d, mode = %d\n", offset, value);

	/* 8 x 4 bit fields in 4 IDT रेजिस्टरs */
	reg = GIO_IDT(offset >> 3);
	shअगरt = (offset & 0x07) << 4;

	spin_lock_irqsave(&p->sense_lock, flags);

	/* disable the पूर्णांकerrupt in IIA */
	पंचांगp = em_gio_पढ़ो(p, GIO_IIA);
	पंचांगp &= ~BIT(offset);
	em_gio_ग_लिखो(p, GIO_IIA, पंचांगp);

	/* change the sense setting in IDT */
	पंचांगp = em_gio_पढ़ो(p, reg);
	पंचांगp &= ~(0xf << shअगरt);
	पंचांगp |= value << shअगरt;
	em_gio_ग_लिखो(p, reg, पंचांगp);

	/* clear pending पूर्णांकerrupts */
	em_gio_ग_लिखो(p, GIO_IIR, BIT(offset));

	/* enable the पूर्णांकerrupt in IIA */
	पंचांगp = em_gio_पढ़ो(p, GIO_IIA);
	पंचांगp |= BIT(offset);
	em_gio_ग_लिखो(p, GIO_IIA, पंचांगp);

	spin_unlock_irqrestore(&p->sense_lock, flags);

	वापस 0;
पूर्ण

अटल irqवापस_t em_gio_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा em_gio_priv *p = dev_id;
	अचिन्हित दीर्घ pending;
	अचिन्हित पूर्णांक offset, irqs_handled = 0;

	जबतक ((pending = em_gio_पढ़ो(p, GIO_MST))) अणु
		offset = __ffs(pending);
		em_gio_ग_लिखो(p, GIO_IIR, BIT(offset));
		generic_handle_irq(irq_find_mapping(p->irq_करोमुख्य, offset));
		irqs_handled++;
	पूर्ण

	वापस irqs_handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल अंतरभूत काष्ठा em_gio_priv *gpio_to_priv(काष्ठा gpio_chip *chip)
अणु
	वापस gpiochip_get_data(chip);
पूर्ण

अटल पूर्णांक em_gio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	em_gio_ग_लिखो(gpio_to_priv(chip), GIO_E0, BIT(offset));
	वापस 0;
पूर्ण

अटल पूर्णांक em_gio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस !!(em_gio_पढ़ो(gpio_to_priv(chip), GIO_I) & BIT(offset));
पूर्ण

अटल व्योम __em_gio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक reg,
			 अचिन्हित shअगरt, पूर्णांक value)
अणु
	/* upper 16 bits contains mask and lower 16 actual value */
	em_gio_ग_लिखो(gpio_to_priv(chip), reg,
		     (BIT(shअगरt + 16)) | (value << shअगरt));
पूर्ण

अटल व्योम em_gio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	/* output is split पूर्णांकo two रेजिस्टरs */
	अगर (offset < 16)
		__em_gio_set(chip, GIO_OL, offset, value);
	अन्यथा
		__em_gio_set(chip, GIO_OH, offset - 16, value);
पूर्ण

अटल पूर्णांक em_gio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
				   पूर्णांक value)
अणु
	/* ग_लिखो GPIO value to output beक्रमe selecting output mode of pin */
	em_gio_set(chip, offset, value);
	em_gio_ग_लिखो(gpio_to_priv(chip), GIO_E1, BIT(offset));
	वापस 0;
पूर्ण

अटल पूर्णांक em_gio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस irq_create_mapping(gpio_to_priv(chip)->irq_करोमुख्य, offset);
पूर्ण

अटल पूर्णांक em_gio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस pinctrl_gpio_request(chip->base + offset);
पूर्ण

अटल व्योम em_gio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	pinctrl_gpio_मुक्त(chip->base + offset);

	/* Set the GPIO as an input to ensure that the next GPIO request won't
	* drive the GPIO pin as an output.
	*/
	em_gio_direction_input(chip, offset);
पूर्ण

अटल पूर्णांक em_gio_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक irq,
				 irq_hw_number_t hwirq)
अणु
	काष्ठा em_gio_priv *p = h->host_data;

	pr_debug("gio: map hw irq = %d, irq = %d\n", (पूर्णांक)hwirq, irq);

	irq_set_chip_data(irq, h->host_data);
	irq_set_chip_and_handler(irq, &p->irq_chip, handle_level_irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops em_gio_irq_करोमुख्य_ops = अणु
	.map	= em_gio_irq_करोमुख्य_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल व्योम em_gio_irq_करोमुख्य_हटाओ(व्योम *data)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = data;

	irq_करोमुख्य_हटाओ(करोमुख्य);
पूर्ण

अटल पूर्णांक em_gio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा em_gio_priv *p;
	काष्ठा gpio_chip *gpio_chip;
	काष्ठा irq_chip *irq_chip;
	काष्ठा device *dev = &pdev->dev;
	स्थिर अक्षर *name = dev_name(dev);
	अचिन्हित पूर्णांक ngpios;
	पूर्णांक irq[2], ret;

	p = devm_kzalloc(dev, माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	p->pdev = pdev;
	platक्रमm_set_drvdata(pdev, p);
	spin_lock_init(&p->sense_lock);

	irq[0] = platक्रमm_get_irq(pdev, 0);
	अगर (irq[0] < 0)
		वापस irq[0];

	irq[1] = platक्रमm_get_irq(pdev, 1);
	अगर (irq[1] < 0)
		वापस irq[1];

	p->base0 = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(p->base0))
		वापस PTR_ERR(p->base0);

	p->base1 = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(p->base1))
		वापस PTR_ERR(p->base1);

	अगर (of_property_पढ़ो_u32(dev->of_node, "ngpios", &ngpios)) अणु
		dev_err(dev, "Missing ngpios OF property\n");
		वापस -EINVAL;
	पूर्ण

	gpio_chip = &p->gpio_chip;
	gpio_chip->of_node = dev->of_node;
	gpio_chip->direction_input = em_gio_direction_input;
	gpio_chip->get = em_gio_get;
	gpio_chip->direction_output = em_gio_direction_output;
	gpio_chip->set = em_gio_set;
	gpio_chip->to_irq = em_gio_to_irq;
	gpio_chip->request = em_gio_request;
	gpio_chip->मुक्त = em_gio_मुक्त;
	gpio_chip->label = name;
	gpio_chip->parent = dev;
	gpio_chip->owner = THIS_MODULE;
	gpio_chip->base = -1;
	gpio_chip->ngpio = ngpios;

	irq_chip = &p->irq_chip;
	irq_chip->name = "gpio-em";
	irq_chip->irq_mask = em_gio_irq_disable;
	irq_chip->irq_unmask = em_gio_irq_enable;
	irq_chip->irq_set_type = em_gio_irq_set_type;
	irq_chip->irq_request_resources = em_gio_irq_reqres;
	irq_chip->irq_release_resources = em_gio_irq_relres;
	irq_chip->flags	= IRQCHIP_SKIP_SET_WAKE | IRQCHIP_MASK_ON_SUSPEND;

	p->irq_करोमुख्य = irq_करोमुख्य_add_simple(dev->of_node, ngpios, 0,
					      &em_gio_irq_करोमुख्य_ops, p);
	अगर (!p->irq_करोमुख्य) अणु
		dev_err(dev, "cannot initialize irq domain\n");
		वापस -ENXIO;
	पूर्ण

	ret = devm_add_action_or_reset(dev, em_gio_irq_करोमुख्य_हटाओ,
				       p->irq_करोमुख्य);
	अगर (ret)
		वापस ret;

	अगर (devm_request_irq(dev, irq[0], em_gio_irq_handler, 0, name, p)) अणु
		dev_err(dev, "failed to request low IRQ\n");
		वापस -ENOENT;
	पूर्ण

	अगर (devm_request_irq(dev, irq[1], em_gio_irq_handler, 0, name, p)) अणु
		dev_err(dev, "failed to request high IRQ\n");
		वापस -ENOENT;
	पूर्ण

	ret = devm_gpiochip_add_data(dev, gpio_chip, p);
	अगर (ret) अणु
		dev_err(dev, "failed to add GPIO controller\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id em_gio_dt_ids[] = अणु
	अणु .compatible = "renesas,em-gio", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, em_gio_dt_ids);

अटल काष्ठा platक्रमm_driver em_gio_device_driver = अणु
	.probe		= em_gio_probe,
	.driver		= अणु
		.name	= "em_gio",
		.of_match_table = em_gio_dt_ids,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init em_gio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&em_gio_device_driver);
पूर्ण
postcore_initcall(em_gio_init);

अटल व्योम __निकास em_gio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&em_gio_device_driver);
पूर्ण
module_निकास(em_gio_निकास);

MODULE_AUTHOR("Magnus Damm");
MODULE_DESCRIPTION("Renesas Emma Mobile GIO Driver");
MODULE_LICENSE("GPL v2");
