<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * A gpio chip driver क्रम TXx9 SoCs
 *
 * Copyright (C) 2008 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 */

#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <यंत्र/txx9pपन.स>

अटल DEFINE_SPINLOCK(txx9_gpio_lock);

अटल काष्ठा txx9_pio_reg __iomem *txx9_pioptr;

अटल पूर्णांक txx9_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	वापस !!(__raw_पढ़ोl(&txx9_pioptr->din) & (1 << offset));
पूर्ण

अटल व्योम txx9_gpio_set_raw(अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	u32 val;
	val = __raw_पढ़ोl(&txx9_pioptr->करोut);
	अगर (value)
		val |= 1 << offset;
	अन्यथा
		val &= ~(1 << offset);
	__raw_ग_लिखोl(val, &txx9_pioptr->करोut);
पूर्ण

अटल व्योम txx9_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			  पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&txx9_gpio_lock, flags);
	txx9_gpio_set_raw(offset, value);
	mmiowb();
	spin_unlock_irqrestore(&txx9_gpio_lock, flags);
पूर्ण

अटल पूर्णांक txx9_gpio_dir_in(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&txx9_gpio_lock, flags);
	__raw_ग_लिखोl(__raw_पढ़ोl(&txx9_pioptr->dir) & ~(1 << offset),
		     &txx9_pioptr->dir);
	mmiowb();
	spin_unlock_irqrestore(&txx9_gpio_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक txx9_gpio_dir_out(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			     पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&txx9_gpio_lock, flags);
	txx9_gpio_set_raw(offset, value);
	__raw_ग_लिखोl(__raw_पढ़ोl(&txx9_pioptr->dir) | (1 << offset),
		     &txx9_pioptr->dir);
	mmiowb();
	spin_unlock_irqrestore(&txx9_gpio_lock, flags);
	वापस 0;
पूर्ण

अटल काष्ठा gpio_chip txx9_gpio_chip = अणु
	.get = txx9_gpio_get,
	.set = txx9_gpio_set,
	.direction_input = txx9_gpio_dir_in,
	.direction_output = txx9_gpio_dir_out,
	.label = "TXx9",
पूर्ण;

पूर्णांक __init txx9_gpio_init(अचिन्हित दीर्घ baseaddr,
			  अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक num)
अणु
	txx9_pioptr = ioremap(baseaddr, माप(काष्ठा txx9_pio_reg));
	अगर (!txx9_pioptr)
		वापस -ENODEV;
	txx9_gpio_chip.base = base;
	txx9_gpio_chip.ngpio = num;
	वापस gpiochip_add_data(&txx9_gpio_chip, शून्य);
पूर्ण
