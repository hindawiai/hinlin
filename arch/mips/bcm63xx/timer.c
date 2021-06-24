<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_समयr.h>
#समावेश <bcm63xx_regs.h>

अटल DEFINE_RAW_SPINLOCK(समयr_reg_lock);
अटल DEFINE_RAW_SPINLOCK(समयr_data_lock);
अटल काष्ठा clk *periph_clk;

अटल काष्ठा समयr_data अणु
	व्योम	(*cb)(व्योम *);
	व्योम	*data;
पूर्ण समयr_data[BCM63XX_TIMER_COUNT];

अटल irqवापस_t समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 stat;
	पूर्णांक i;

	raw_spin_lock(&समयr_reg_lock);
	stat = bcm_समयr_पढ़ोl(TIMER_IRQSTAT_REG);
	bcm_समयr_ग_लिखोl(stat, TIMER_IRQSTAT_REG);
	raw_spin_unlock(&समयr_reg_lock);

	क्रम (i = 0; i < BCM63XX_TIMER_COUNT; i++) अणु
		अगर (!(stat & TIMER_IRQSTAT_TIMER_CAUSE(i)))
			जारी;

		raw_spin_lock(&समयr_data_lock);
		अगर (!समयr_data[i].cb) अणु
			raw_spin_unlock(&समयr_data_lock);
			जारी;
		पूर्ण

		समयr_data[i].cb(समयr_data[i].data);
		raw_spin_unlock(&समयr_data_lock);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक bcm63xx_समयr_enable(पूर्णांक id)
अणु
	u32 reg;
	अचिन्हित दीर्घ flags;

	अगर (id >= BCM63XX_TIMER_COUNT)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&समयr_reg_lock, flags);

	reg = bcm_समयr_पढ़ोl(TIMER_CTLx_REG(id));
	reg |= TIMER_CTL_ENABLE_MASK;
	bcm_समयr_ग_लिखोl(reg, TIMER_CTLx_REG(id));

	reg = bcm_समयr_पढ़ोl(TIMER_IRQSTAT_REG);
	reg |= TIMER_IRQSTAT_TIMER_IR_EN(id);
	bcm_समयr_ग_लिखोl(reg, TIMER_IRQSTAT_REG);

	raw_spin_unlock_irqrestore(&समयr_reg_lock, flags);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(bcm63xx_समयr_enable);

पूर्णांक bcm63xx_समयr_disable(पूर्णांक id)
अणु
	u32 reg;
	अचिन्हित दीर्घ flags;

	अगर (id >= BCM63XX_TIMER_COUNT)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&समयr_reg_lock, flags);

	reg = bcm_समयr_पढ़ोl(TIMER_CTLx_REG(id));
	reg &= ~TIMER_CTL_ENABLE_MASK;
	bcm_समयr_ग_लिखोl(reg, TIMER_CTLx_REG(id));

	reg = bcm_समयr_पढ़ोl(TIMER_IRQSTAT_REG);
	reg &= ~TIMER_IRQSTAT_TIMER_IR_EN(id);
	bcm_समयr_ग_लिखोl(reg, TIMER_IRQSTAT_REG);

	raw_spin_unlock_irqrestore(&समयr_reg_lock, flags);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(bcm63xx_समयr_disable);

पूर्णांक bcm63xx_समयr_रेजिस्टर(पूर्णांक id, व्योम (*callback)(व्योम *data), व्योम *data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (id >= BCM63XX_TIMER_COUNT || !callback)
		वापस -EINVAL;

	ret = 0;
	raw_spin_lock_irqsave(&समयr_data_lock, flags);
	अगर (समयr_data[id].cb) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	समयr_data[id].cb = callback;
	समयr_data[id].data = data;

out:
	raw_spin_unlock_irqrestore(&समयr_data_lock, flags);
	वापस ret;
पूर्ण

EXPORT_SYMBOL(bcm63xx_समयr_रेजिस्टर);

व्योम bcm63xx_समयr_unरेजिस्टर(पूर्णांक id)
अणु
	अचिन्हित दीर्घ flags;

	अगर (id >= BCM63XX_TIMER_COUNT)
		वापस;

	raw_spin_lock_irqsave(&समयr_data_lock, flags);
	समयr_data[id].cb = शून्य;
	raw_spin_unlock_irqrestore(&समयr_data_lock, flags);
पूर्ण

EXPORT_SYMBOL(bcm63xx_समयr_unरेजिस्टर);

अचिन्हित पूर्णांक bcm63xx_समयr_countकरोwn(अचिन्हित पूर्णांक countकरोwn_us)
अणु
	वापस (clk_get_rate(periph_clk) / (1000 * 1000)) * countकरोwn_us;
पूर्ण

EXPORT_SYMBOL(bcm63xx_समयr_countकरोwn);

पूर्णांक bcm63xx_समयr_set(पूर्णांक id, पूर्णांक monotonic, अचिन्हित पूर्णांक countकरोwn_us)
अणु
	u32 reg, countकरोwn;
	अचिन्हित दीर्घ flags;

	अगर (id >= BCM63XX_TIMER_COUNT)
		वापस -EINVAL;

	countकरोwn = bcm63xx_समयr_countकरोwn(countकरोwn_us);
	अगर (countकरोwn & ~TIMER_CTL_COUNTDOWN_MASK)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&समयr_reg_lock, flags);
	reg = bcm_समयr_पढ़ोl(TIMER_CTLx_REG(id));

	अगर (monotonic)
		reg &= ~TIMER_CTL_MONOTONIC_MASK;
	अन्यथा
		reg |= TIMER_CTL_MONOTONIC_MASK;

	reg &= ~TIMER_CTL_COUNTDOWN_MASK;
	reg |= countकरोwn;
	bcm_समयr_ग_लिखोl(reg, TIMER_CTLx_REG(id));

	raw_spin_unlock_irqrestore(&समयr_reg_lock, flags);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(bcm63xx_समयr_set);

पूर्णांक bcm63xx_समयr_init(व्योम)
अणु
	पूर्णांक ret, irq;
	u32 reg;

	reg = bcm_समयr_पढ़ोl(TIMER_IRQSTAT_REG);
	reg &= ~TIMER_IRQSTAT_TIMER0_IR_EN;
	reg &= ~TIMER_IRQSTAT_TIMER1_IR_EN;
	reg &= ~TIMER_IRQSTAT_TIMER2_IR_EN;
	bcm_समयr_ग_लिखोl(reg, TIMER_IRQSTAT_REG);

	periph_clk = clk_get(शून्य, "periph");
	अगर (IS_ERR(periph_clk))
		वापस -ENODEV;

	irq = bcm63xx_get_irq_number(IRQ_TIMER);
	ret = request_irq(irq, समयr_पूर्णांकerrupt, 0, "bcm63xx_timer", शून्य);
	अगर (ret) अणु
		pr_err("%s: failed to register irq\n", __func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

arch_initcall(bcm63xx_समयr_init);
