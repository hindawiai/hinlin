<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * gpio-reg: single रेजिस्टर inभागidually fixed-direction GPIOs
 *
 * Copyright (C) 2016 Russell King
 */
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/gpio-reg.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

काष्ठा gpio_reg अणु
	काष्ठा gpio_chip gc;
	spinlock_t lock;
	u32 direction;
	u32 out;
	व्योम __iomem *reg;
	काष्ठा irq_करोमुख्य *irqकरोमुख्य;
	स्थिर पूर्णांक *irqs;
पूर्ण;

#घोषणा to_gpio_reg(x) container_of(x, काष्ठा gpio_reg, gc)

अटल पूर्णांक gpio_reg_get_direction(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा gpio_reg *r = to_gpio_reg(gc);

	वापस r->direction & BIT(offset) ? GPIO_LINE_सूचीECTION_IN :
					    GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक gpio_reg_direction_output(काष्ठा gpio_chip *gc, अचिन्हित offset,
	पूर्णांक value)
अणु
	काष्ठा gpio_reg *r = to_gpio_reg(gc);

	अगर (r->direction & BIT(offset))
		वापस -ENOTSUPP;

	gc->set(gc, offset, value);
	वापस 0;
पूर्ण

अटल पूर्णांक gpio_reg_direction_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा gpio_reg *r = to_gpio_reg(gc);

	वापस r->direction & BIT(offset) ? 0 : -ENOTSUPP;
पूर्ण

अटल व्योम gpio_reg_set(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा gpio_reg *r = to_gpio_reg(gc);
	अचिन्हित दीर्घ flags;
	u32 val, mask = BIT(offset);

	spin_lock_irqsave(&r->lock, flags);
	val = r->out;
	अगर (value)
		val |= mask;
	अन्यथा
		val &= ~mask;
	r->out = val;
	ग_लिखोl_relaxed(val, r->reg);
	spin_unlock_irqrestore(&r->lock, flags);
पूर्ण

अटल पूर्णांक gpio_reg_get(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा gpio_reg *r = to_gpio_reg(gc);
	u32 val, mask = BIT(offset);

	अगर (r->direction & mask) अणु
		/*
		 * द्विगुन-पढ़ो the value, some रेजिस्टरs latch after the
		 * first पढ़ो.
		 */
		पढ़ोl_relaxed(r->reg);
		val = पढ़ोl_relaxed(r->reg);
	पूर्ण अन्यथा अणु
		val = r->out;
	पूर्ण
	वापस !!(val & mask);
पूर्ण

अटल व्योम gpio_reg_set_multiple(काष्ठा gpio_chip *gc, अचिन्हित दीर्घ *mask,
	अचिन्हित दीर्घ *bits)
अणु
	काष्ठा gpio_reg *r = to_gpio_reg(gc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&r->lock, flags);
	r->out = (r->out & ~*mask) | (*bits & *mask);
	ग_लिखोl_relaxed(r->out, r->reg);
	spin_unlock_irqrestore(&r->lock, flags);
पूर्ण

अटल पूर्णांक gpio_reg_to_irq(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा gpio_reg *r = to_gpio_reg(gc);
	पूर्णांक irq = r->irqs[offset];

	अगर (irq >= 0 && r->irqकरोमुख्य)
		irq = irq_find_mapping(r->irqकरोमुख्य, irq);

	वापस irq;
पूर्ण

/**
 * gpio_reg_init - add a fixed in/out रेजिस्टर as gpio
 * @dev: optional काष्ठा device associated with this रेजिस्टर
 * @base: start gpio number, or -1 to allocate
 * @num: number of GPIOs, maximum 32
 * @label: GPIO chip label
 * @direction: biपंचांगask of fixed direction, one per GPIO संकेत, 1 = in
 * @def_out: initial GPIO output value
 * @names: array of %num strings describing each GPIO संकेत or %शून्य
 * @irqकरोm: irq करोमुख्य or %शून्य
 * @irqs: array of %num पूर्णांकs describing the पूर्णांकerrupt mapping क्रम each
 *        GPIO संकेत, or %शून्य.  If @irqकरोm is %शून्य, then this
 *        describes the Linux पूर्णांकerrupt number, otherwise it describes
 *        the hardware पूर्णांकerrupt number in the specअगरied irq करोमुख्य.
 *
 * Add a single-रेजिस्टर GPIO device containing up to 32 GPIO संकेतs,
 * where each GPIO has a fixed input or output configuration.  Only
 * input GPIOs are assumed to be पढ़ोable from the रेजिस्टर, and only
 * then after a द्विगुन-पढ़ो.  Output values are assumed not to be
 * पढ़ोable.
 */
काष्ठा gpio_chip *gpio_reg_init(काष्ठा device *dev, व्योम __iomem *reg,
	पूर्णांक base, पूर्णांक num, स्थिर अक्षर *label, u32 direction, u32 def_out,
	स्थिर अक्षर *स्थिर *names, काष्ठा irq_करोमुख्य *irqकरोm, स्थिर पूर्णांक *irqs)
अणु
	काष्ठा gpio_reg *r;
	पूर्णांक ret;

	अगर (dev)
		r = devm_kzalloc(dev, माप(*r), GFP_KERNEL);
	अन्यथा
		r = kzalloc(माप(*r), GFP_KERNEL);

	अगर (!r)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&r->lock);

	r->gc.label = label;
	r->gc.get_direction = gpio_reg_get_direction;
	r->gc.direction_input = gpio_reg_direction_input;
	r->gc.direction_output = gpio_reg_direction_output;
	r->gc.set = gpio_reg_set;
	r->gc.get = gpio_reg_get;
	r->gc.set_multiple = gpio_reg_set_multiple;
	अगर (irqs)
		r->gc.to_irq = gpio_reg_to_irq;
	r->gc.base = base;
	r->gc.ngpio = num;
	r->gc.names = names;
	r->direction = direction;
	r->out = def_out;
	r->reg = reg;
	r->irqs = irqs;

	अगर (dev)
		ret = devm_gpiochip_add_data(dev, &r->gc, r);
	अन्यथा
		ret = gpiochip_add_data(&r->gc, r);

	वापस ret ? ERR_PTR(ret) : &r->gc;
पूर्ण

पूर्णांक gpio_reg_resume(काष्ठा gpio_chip *gc)
अणु
	काष्ठा gpio_reg *r = to_gpio_reg(gc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&r->lock, flags);
	ग_लिखोl_relaxed(r->out, r->reg);
	spin_unlock_irqrestore(&r->lock, flags);

	वापस 0;
पूर्ण
