<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) Maxime Coquelin 2015
 * Copyright (C) STMicroelectronics 2017
 * Author:  Maxime Coquelin <mcoquelin.sपंचांग32@gmail.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/hwspinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/syscore_ops.h>

#समावेश <dt-bindings/पूर्णांकerrupt-controller/arm-gic.h>

#घोषणा IRQS_PER_BANK 32

#घोषणा HWSPNLCK_TIMEOUT	1000 /* usec */

काष्ठा sपंचांग32_exti_bank अणु
	u32 imr_ofst;
	u32 emr_ofst;
	u32 rtsr_ofst;
	u32 ftsr_ofst;
	u32 swier_ofst;
	u32 rpr_ofst;
	u32 fpr_ofst;
पूर्ण;

#घोषणा UNDEF_REG ~0

काष्ठा sपंचांग32_desc_irq अणु
	u32 exti;
	u32 irq_parent;
	काष्ठा irq_chip *chip;
पूर्ण;

काष्ठा sपंचांग32_exti_drv_data अणु
	स्थिर काष्ठा sपंचांग32_exti_bank **exti_banks;
	स्थिर काष्ठा sपंचांग32_desc_irq *desc_irqs;
	u32 bank_nr;
	u32 irq_nr;
पूर्ण;

काष्ठा sपंचांग32_exti_chip_data अणु
	काष्ठा sपंचांग32_exti_host_data *host_data;
	स्थिर काष्ठा sपंचांग32_exti_bank *reg_bank;
	काष्ठा raw_spinlock rlock;
	u32 wake_active;
	u32 mask_cache;
	u32 rtsr_cache;
	u32 ftsr_cache;
पूर्ण;

काष्ठा sपंचांग32_exti_host_data अणु
	व्योम __iomem *base;
	काष्ठा sपंचांग32_exti_chip_data *chips_data;
	स्थिर काष्ठा sपंचांग32_exti_drv_data *drv_data;
	काष्ठा hwspinlock *hwlock;
पूर्ण;

अटल काष्ठा sपंचांग32_exti_host_data *sपंचांग32_host_data;

अटल स्थिर काष्ठा sपंचांग32_exti_bank sपंचांग32f4xx_exti_b1 = अणु
	.imr_ofst	= 0x00,
	.emr_ofst	= 0x04,
	.rtsr_ofst	= 0x08,
	.ftsr_ofst	= 0x0C,
	.swier_ofst	= 0x10,
	.rpr_ofst	= 0x14,
	.fpr_ofst	= UNDEF_REG,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32f4xx_exti_banks[] = अणु
	&sपंचांग32f4xx_exti_b1,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_exti_drv_data sपंचांग32f4xx_drv_data = अणु
	.exti_banks = sपंचांग32f4xx_exti_banks,
	.bank_nr = ARRAY_SIZE(sपंचांग32f4xx_exti_banks),
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_exti_bank sपंचांग32h7xx_exti_b1 = अणु
	.imr_ofst	= 0x80,
	.emr_ofst	= 0x84,
	.rtsr_ofst	= 0x00,
	.ftsr_ofst	= 0x04,
	.swier_ofst	= 0x08,
	.rpr_ofst	= 0x88,
	.fpr_ofst	= UNDEF_REG,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_exti_bank sपंचांग32h7xx_exti_b2 = अणु
	.imr_ofst	= 0x90,
	.emr_ofst	= 0x94,
	.rtsr_ofst	= 0x20,
	.ftsr_ofst	= 0x24,
	.swier_ofst	= 0x28,
	.rpr_ofst	= 0x98,
	.fpr_ofst	= UNDEF_REG,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_exti_bank sपंचांग32h7xx_exti_b3 = अणु
	.imr_ofst	= 0xA0,
	.emr_ofst	= 0xA4,
	.rtsr_ofst	= 0x40,
	.ftsr_ofst	= 0x44,
	.swier_ofst	= 0x48,
	.rpr_ofst	= 0xA8,
	.fpr_ofst	= UNDEF_REG,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32h7xx_exti_banks[] = अणु
	&sपंचांग32h7xx_exti_b1,
	&sपंचांग32h7xx_exti_b2,
	&sपंचांग32h7xx_exti_b3,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_exti_drv_data sपंचांग32h7xx_drv_data = अणु
	.exti_banks = sपंचांग32h7xx_exti_banks,
	.bank_nr = ARRAY_SIZE(sपंचांग32h7xx_exti_banks),
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_exti_bank sपंचांग32mp1_exti_b1 = अणु
	.imr_ofst	= 0x80,
	.emr_ofst	= 0x84,
	.rtsr_ofst	= 0x00,
	.ftsr_ofst	= 0x04,
	.swier_ofst	= 0x08,
	.rpr_ofst	= 0x0C,
	.fpr_ofst	= 0x10,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_exti_bank sपंचांग32mp1_exti_b2 = अणु
	.imr_ofst	= 0x90,
	.emr_ofst	= 0x94,
	.rtsr_ofst	= 0x20,
	.ftsr_ofst	= 0x24,
	.swier_ofst	= 0x28,
	.rpr_ofst	= 0x2C,
	.fpr_ofst	= 0x30,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_exti_bank sपंचांग32mp1_exti_b3 = अणु
	.imr_ofst	= 0xA0,
	.emr_ofst	= 0xA4,
	.rtsr_ofst	= 0x40,
	.ftsr_ofst	= 0x44,
	.swier_ofst	= 0x48,
	.rpr_ofst	= 0x4C,
	.fpr_ofst	= 0x50,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32mp1_exti_banks[] = अणु
	&sपंचांग32mp1_exti_b1,
	&sपंचांग32mp1_exti_b2,
	&sपंचांग32mp1_exti_b3,
पूर्ण;

अटल काष्ठा irq_chip sपंचांग32_exti_h_chip;
अटल काष्ठा irq_chip sपंचांग32_exti_h_chip_direct;

अटल स्थिर काष्ठा sपंचांग32_desc_irq sपंचांग32mp1_desc_irq[] = अणु
	अणु .exti = 0, .irq_parent = 6, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 1, .irq_parent = 7, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 2, .irq_parent = 8, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 3, .irq_parent = 9, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 4, .irq_parent = 10, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 5, .irq_parent = 23, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 6, .irq_parent = 64, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 7, .irq_parent = 65, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 8, .irq_parent = 66, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 9, .irq_parent = 67, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 10, .irq_parent = 40, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 11, .irq_parent = 42, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 12, .irq_parent = 76, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 13, .irq_parent = 77, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 14, .irq_parent = 121, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 15, .irq_parent = 127, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 16, .irq_parent = 1, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 19, .irq_parent = 3, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 21, .irq_parent = 31, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 22, .irq_parent = 33, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 23, .irq_parent = 72, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 24, .irq_parent = 95, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 25, .irq_parent = 107, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 26, .irq_parent = 37, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 27, .irq_parent = 38, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 28, .irq_parent = 39, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 29, .irq_parent = 71, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 30, .irq_parent = 52, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 31, .irq_parent = 53, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 32, .irq_parent = 82, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 33, .irq_parent = 83, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 47, .irq_parent = 93, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 48, .irq_parent = 138, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 50, .irq_parent = 139, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 52, .irq_parent = 140, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 53, .irq_parent = 141, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 54, .irq_parent = 135, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 61, .irq_parent = 100, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 65, .irq_parent = 144, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 68, .irq_parent = 143, .chip = &sपंचांग32_exti_h_chip पूर्ण,
	अणु .exti = 70, .irq_parent = 62, .chip = &sपंचांग32_exti_h_chip_direct पूर्ण,
	अणु .exti = 73, .irq_parent = 129, .chip = &sपंचांग32_exti_h_chip पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_exti_drv_data sपंचांग32mp1_drv_data = अणु
	.exti_banks = sपंचांग32mp1_exti_banks,
	.bank_nr = ARRAY_SIZE(sपंचांग32mp1_exti_banks),
	.desc_irqs = sपंचांग32mp1_desc_irq,
	.irq_nr = ARRAY_SIZE(sपंचांग32mp1_desc_irq),
पूर्ण;

अटल स्थिर काष्ठा
sपंचांग32_desc_irq *sपंचांग32_exti_get_desc(स्थिर काष्ठा sपंचांग32_exti_drv_data *drv_data,
				    irq_hw_number_t hwirq)
अणु
	स्थिर काष्ठा sपंचांग32_desc_irq *desc = शून्य;
	पूर्णांक i;

	अगर (!drv_data->desc_irqs)
		वापस शून्य;

	क्रम (i = 0; i < drv_data->irq_nr; i++) अणु
		desc = &drv_data->desc_irqs[i];
		अगर (desc->exti == hwirq)
			अवरोध;
	पूर्ण

	वापस desc;
पूर्ण

अटल अचिन्हित दीर्घ sपंचांग32_exti_pending(काष्ठा irq_chip_generic *gc)
अणु
	काष्ठा sपंचांग32_exti_chip_data *chip_data = gc->निजी;
	स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32_bank = chip_data->reg_bank;
	अचिन्हित दीर्घ pending;

	pending = irq_reg_पढ़ोl(gc, sपंचांग32_bank->rpr_ofst);
	अगर (sपंचांग32_bank->fpr_ofst != UNDEF_REG)
		pending |= irq_reg_पढ़ोl(gc, sपंचांग32_bank->fpr_ofst);

	वापस pending;
पूर्ण

अटल व्योम sपंचांग32_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक virq, nbanks = करोमुख्य->gc->num_chips;
	काष्ठा irq_chip_generic *gc;
	अचिन्हित दीर्घ pending;
	पूर्णांक n, i, irq_base = 0;

	chained_irq_enter(chip, desc);

	क्रम (i = 0; i < nbanks; i++, irq_base += IRQS_PER_BANK) अणु
		gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, irq_base);

		जबतक ((pending = sपंचांग32_exti_pending(gc))) अणु
			क्रम_each_set_bit(n, &pending, IRQS_PER_BANK) अणु
				virq = irq_find_mapping(करोमुख्य, irq_base + n);
				generic_handle_irq(virq);
			पूर्ण
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक sपंचांग32_exti_set_type(काष्ठा irq_data *d,
			       अचिन्हित पूर्णांक type, u32 *rtsr, u32 *ftsr)
अणु
	u32 mask = BIT(d->hwirq % IRQS_PER_BANK);

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		*rtsr |= mask;
		*ftsr &= ~mask;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		*rtsr &= ~mask;
		*ftsr |= mask;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		*rtsr |= mask;
		*ftsr |= mask;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sपंचांग32_exti_chip_data *chip_data = gc->निजी;
	स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32_bank = chip_data->reg_bank;
	काष्ठा hwspinlock *hwlock = chip_data->host_data->hwlock;
	u32 rtsr, ftsr;
	पूर्णांक err;

	irq_gc_lock(gc);

	अगर (hwlock) अणु
		err = hwspin_lock_समयout_in_atomic(hwlock, HWSPNLCK_TIMEOUT);
		अगर (err) अणु
			pr_err("%s can't get hwspinlock (%d)\n", __func__, err);
			जाओ unlock;
		पूर्ण
	पूर्ण

	rtsr = irq_reg_पढ़ोl(gc, sपंचांग32_bank->rtsr_ofst);
	ftsr = irq_reg_पढ़ोl(gc, sपंचांग32_bank->ftsr_ofst);

	err = sपंचांग32_exti_set_type(d, type, &rtsr, &ftsr);
	अगर (err)
		जाओ unspinlock;

	irq_reg_ग_लिखोl(gc, rtsr, sपंचांग32_bank->rtsr_ofst);
	irq_reg_ग_लिखोl(gc, ftsr, sपंचांग32_bank->ftsr_ofst);

unspinlock:
	अगर (hwlock)
		hwspin_unlock_in_atomic(hwlock);
unlock:
	irq_gc_unlock(gc);

	वापस err;
पूर्ण

अटल व्योम sपंचांग32_chip_suspend(काष्ठा sपंचांग32_exti_chip_data *chip_data,
			       u32 wake_active)
अणु
	स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32_bank = chip_data->reg_bank;
	व्योम __iomem *base = chip_data->host_data->base;

	/* save rtsr, ftsr रेजिस्टरs */
	chip_data->rtsr_cache = पढ़ोl_relaxed(base + sपंचांग32_bank->rtsr_ofst);
	chip_data->ftsr_cache = पढ़ोl_relaxed(base + sपंचांग32_bank->ftsr_ofst);

	ग_लिखोl_relaxed(wake_active, base + sपंचांग32_bank->imr_ofst);
पूर्ण

अटल व्योम sपंचांग32_chip_resume(काष्ठा sपंचांग32_exti_chip_data *chip_data,
			      u32 mask_cache)
अणु
	स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32_bank = chip_data->reg_bank;
	व्योम __iomem *base = chip_data->host_data->base;

	/* restore rtsr, ftsr, रेजिस्टरs */
	ग_लिखोl_relaxed(chip_data->rtsr_cache, base + sपंचांग32_bank->rtsr_ofst);
	ग_लिखोl_relaxed(chip_data->ftsr_cache, base + sपंचांग32_bank->ftsr_ofst);

	ग_लिखोl_relaxed(mask_cache, base + sपंचांग32_bank->imr_ofst);
पूर्ण

अटल व्योम sपंचांग32_irq_suspend(काष्ठा irq_chip_generic *gc)
अणु
	काष्ठा sपंचांग32_exti_chip_data *chip_data = gc->निजी;

	irq_gc_lock(gc);
	sपंचांग32_chip_suspend(chip_data, gc->wake_active);
	irq_gc_unlock(gc);
पूर्ण

अटल व्योम sपंचांग32_irq_resume(काष्ठा irq_chip_generic *gc)
अणु
	काष्ठा sपंचांग32_exti_chip_data *chip_data = gc->निजी;

	irq_gc_lock(gc);
	sपंचांग32_chip_resume(chip_data, gc->mask_cache);
	irq_gc_unlock(gc);
पूर्ण

अटल पूर्णांक sपंचांग32_exti_alloc(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			    अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा irq_fwspec *fwspec = data;
	irq_hw_number_t hwirq;

	hwirq = fwspec->param[0];

	irq_map_generic_chip(d, virq, hwirq);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_exti_मुक्त(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			    अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *data = irq_करोमुख्य_get_irq_data(d, virq);

	irq_करोमुख्य_reset_irq_data(data);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops irq_exti_करोमुख्य_ops = अणु
	.map	= irq_map_generic_chip,
	.alloc  = sपंचांग32_exti_alloc,
	.मुक्त	= sपंचांग32_exti_मुक्त,
पूर्ण;

अटल व्योम sपंचांग32_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा sपंचांग32_exti_chip_data *chip_data = gc->निजी;
	स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32_bank = chip_data->reg_bank;

	irq_gc_lock(gc);

	irq_reg_ग_लिखोl(gc, d->mask, sपंचांग32_bank->rpr_ofst);
	अगर (sपंचांग32_bank->fpr_ofst != UNDEF_REG)
		irq_reg_ग_लिखोl(gc, d->mask, sपंचांग32_bank->fpr_ofst);

	irq_gc_unlock(gc);
पूर्ण

/* directly set the target bit without पढ़ोing first. */
अटल अंतरभूत व्योम sपंचांग32_exti_ग_लिखो_bit(काष्ठा irq_data *d, u32 reg)
अणु
	काष्ठा sपंचांग32_exti_chip_data *chip_data = irq_data_get_irq_chip_data(d);
	व्योम __iomem *base = chip_data->host_data->base;
	u32 val = BIT(d->hwirq % IRQS_PER_BANK);

	ग_लिखोl_relaxed(val, base + reg);
पूर्ण

अटल अंतरभूत u32 sपंचांग32_exti_set_bit(काष्ठा irq_data *d, u32 reg)
अणु
	काष्ठा sपंचांग32_exti_chip_data *chip_data = irq_data_get_irq_chip_data(d);
	व्योम __iomem *base = chip_data->host_data->base;
	u32 val;

	val = पढ़ोl_relaxed(base + reg);
	val |= BIT(d->hwirq % IRQS_PER_BANK);
	ग_लिखोl_relaxed(val, base + reg);

	वापस val;
पूर्ण

अटल अंतरभूत u32 sपंचांग32_exti_clr_bit(काष्ठा irq_data *d, u32 reg)
अणु
	काष्ठा sपंचांग32_exti_chip_data *chip_data = irq_data_get_irq_chip_data(d);
	व्योम __iomem *base = chip_data->host_data->base;
	u32 val;

	val = पढ़ोl_relaxed(base + reg);
	val &= ~BIT(d->hwirq % IRQS_PER_BANK);
	ग_लिखोl_relaxed(val, base + reg);

	वापस val;
पूर्ण

अटल व्योम sपंचांग32_exti_h_eoi(काष्ठा irq_data *d)
अणु
	काष्ठा sपंचांग32_exti_chip_data *chip_data = irq_data_get_irq_chip_data(d);
	स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32_bank = chip_data->reg_bank;

	raw_spin_lock(&chip_data->rlock);

	sपंचांग32_exti_ग_लिखो_bit(d, sपंचांग32_bank->rpr_ofst);
	अगर (sपंचांग32_bank->fpr_ofst != UNDEF_REG)
		sपंचांग32_exti_ग_लिखो_bit(d, sपंचांग32_bank->fpr_ofst);

	raw_spin_unlock(&chip_data->rlock);

	अगर (d->parent_data->chip)
		irq_chip_eoi_parent(d);
पूर्ण

अटल व्योम sपंचांग32_exti_h_mask(काष्ठा irq_data *d)
अणु
	काष्ठा sपंचांग32_exti_chip_data *chip_data = irq_data_get_irq_chip_data(d);
	स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32_bank = chip_data->reg_bank;

	raw_spin_lock(&chip_data->rlock);
	chip_data->mask_cache = sपंचांग32_exti_clr_bit(d, sपंचांग32_bank->imr_ofst);
	raw_spin_unlock(&chip_data->rlock);

	अगर (d->parent_data->chip)
		irq_chip_mask_parent(d);
पूर्ण

अटल व्योम sपंचांग32_exti_h_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा sपंचांग32_exti_chip_data *chip_data = irq_data_get_irq_chip_data(d);
	स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32_bank = chip_data->reg_bank;

	raw_spin_lock(&chip_data->rlock);
	chip_data->mask_cache = sपंचांग32_exti_set_bit(d, sपंचांग32_bank->imr_ofst);
	raw_spin_unlock(&chip_data->rlock);

	अगर (d->parent_data->chip)
		irq_chip_unmask_parent(d);
पूर्ण

अटल पूर्णांक sपंचांग32_exti_h_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा sपंचांग32_exti_chip_data *chip_data = irq_data_get_irq_chip_data(d);
	स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32_bank = chip_data->reg_bank;
	काष्ठा hwspinlock *hwlock = chip_data->host_data->hwlock;
	व्योम __iomem *base = chip_data->host_data->base;
	u32 rtsr, ftsr;
	पूर्णांक err;

	raw_spin_lock(&chip_data->rlock);

	अगर (hwlock) अणु
		err = hwspin_lock_समयout_in_atomic(hwlock, HWSPNLCK_TIMEOUT);
		अगर (err) अणु
			pr_err("%s can't get hwspinlock (%d)\n", __func__, err);
			जाओ unlock;
		पूर्ण
	पूर्ण

	rtsr = पढ़ोl_relaxed(base + sपंचांग32_bank->rtsr_ofst);
	ftsr = पढ़ोl_relaxed(base + sपंचांग32_bank->ftsr_ofst);

	err = sपंचांग32_exti_set_type(d, type, &rtsr, &ftsr);
	अगर (err)
		जाओ unspinlock;

	ग_लिखोl_relaxed(rtsr, base + sपंचांग32_bank->rtsr_ofst);
	ग_लिखोl_relaxed(ftsr, base + sपंचांग32_bank->ftsr_ofst);

unspinlock:
	अगर (hwlock)
		hwspin_unlock_in_atomic(hwlock);
unlock:
	raw_spin_unlock(&chip_data->rlock);

	वापस err;
पूर्ण

अटल पूर्णांक sपंचांग32_exti_h_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा sपंचांग32_exti_chip_data *chip_data = irq_data_get_irq_chip_data(d);
	u32 mask = BIT(d->hwirq % IRQS_PER_BANK);

	raw_spin_lock(&chip_data->rlock);

	अगर (on)
		chip_data->wake_active |= mask;
	अन्यथा
		chip_data->wake_active &= ~mask;

	raw_spin_unlock(&chip_data->rlock);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_exti_h_set_affinity(काष्ठा irq_data *d,
				     स्थिर काष्ठा cpumask *dest, bool क्रमce)
अणु
	अगर (d->parent_data->chip)
		वापस irq_chip_set_affinity_parent(d, dest, क्रमce);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_exti_h_suspend(व्योम)
अणु
	काष्ठा sपंचांग32_exti_chip_data *chip_data;
	पूर्णांक i;

	क्रम (i = 0; i < sपंचांग32_host_data->drv_data->bank_nr; i++) अणु
		chip_data = &sपंचांग32_host_data->chips_data[i];
		raw_spin_lock(&chip_data->rlock);
		sपंचांग32_chip_suspend(chip_data, chip_data->wake_active);
		raw_spin_unlock(&chip_data->rlock);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __maybe_unused sपंचांग32_exti_h_resume(व्योम)
अणु
	काष्ठा sपंचांग32_exti_chip_data *chip_data;
	पूर्णांक i;

	क्रम (i = 0; i < sपंचांग32_host_data->drv_data->bank_nr; i++) अणु
		chip_data = &sपंचांग32_host_data->chips_data[i];
		raw_spin_lock(&chip_data->rlock);
		sपंचांग32_chip_resume(chip_data, chip_data->mask_cache);
		raw_spin_unlock(&chip_data->rlock);
	पूर्ण
पूर्ण

अटल काष्ठा syscore_ops sपंचांग32_exti_h_syscore_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= sपंचांग32_exti_h_suspend,
	.resume		= sपंचांग32_exti_h_resume,
#पूर्ण_अगर
पूर्ण;

अटल व्योम sपंचांग32_exti_h_syscore_init(काष्ठा sपंचांग32_exti_host_data *host_data)
अणु
	sपंचांग32_host_data = host_data;
	रेजिस्टर_syscore_ops(&sपंचांग32_exti_h_syscore_ops);
पूर्ण

अटल व्योम sपंचांग32_exti_h_syscore_deinit(व्योम)
अणु
	unरेजिस्टर_syscore_ops(&sपंचांग32_exti_h_syscore_ops);
पूर्ण

अटल पूर्णांक sपंचांग32_exti_h_retrigger(काष्ठा irq_data *d)
अणु
	काष्ठा sपंचांग32_exti_chip_data *chip_data = irq_data_get_irq_chip_data(d);
	स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32_bank = chip_data->reg_bank;
	व्योम __iomem *base = chip_data->host_data->base;
	u32 mask = BIT(d->hwirq % IRQS_PER_BANK);

	ग_लिखोl_relaxed(mask, base + sपंचांग32_bank->swier_ofst);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip sपंचांग32_exti_h_chip = अणु
	.name			= "stm32-exti-h",
	.irq_eoi		= sपंचांग32_exti_h_eoi,
	.irq_mask		= sपंचांग32_exti_h_mask,
	.irq_unmask		= sपंचांग32_exti_h_unmask,
	.irq_retrigger		= sपंचांग32_exti_h_retrigger,
	.irq_set_type		= sपंचांग32_exti_h_set_type,
	.irq_set_wake		= sपंचांग32_exti_h_set_wake,
	.flags			= IRQCHIP_MASK_ON_SUSPEND,
	.irq_set_affinity	= IS_ENABLED(CONFIG_SMP) ? sपंचांग32_exti_h_set_affinity : शून्य,
पूर्ण;

अटल काष्ठा irq_chip sपंचांग32_exti_h_chip_direct = अणु
	.name			= "stm32-exti-h-direct",
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_ack		= irq_chip_ack_parent,
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_set_type		= irq_chip_set_type_parent,
	.irq_set_wake		= sपंचांग32_exti_h_set_wake,
	.flags			= IRQCHIP_MASK_ON_SUSPEND,
	.irq_set_affinity	= IS_ENABLED(CONFIG_SMP) ? irq_chip_set_affinity_parent : शून्य,
पूर्ण;

अटल पूर्णांक sपंचांग32_exti_h_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *dm,
				     अचिन्हित पूर्णांक virq,
				     अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा sपंचांग32_exti_host_data *host_data = dm->host_data;
	काष्ठा sपंचांग32_exti_chip_data *chip_data;
	स्थिर काष्ठा sपंचांग32_desc_irq *desc;
	काष्ठा irq_fwspec *fwspec = data;
	काष्ठा irq_fwspec p_fwspec;
	irq_hw_number_t hwirq;
	पूर्णांक bank;

	hwirq = fwspec->param[0];
	bank  = hwirq / IRQS_PER_BANK;
	chip_data = &host_data->chips_data[bank];


	desc = sपंचांग32_exti_get_desc(host_data->drv_data, hwirq);
	अगर (!desc)
		वापस -EINVAL;

	irq_करोमुख्य_set_hwirq_and_chip(dm, virq, hwirq, desc->chip,
				      chip_data);
	अगर (desc->irq_parent) अणु
		p_fwspec.fwnode = dm->parent->fwnode;
		p_fwspec.param_count = 3;
		p_fwspec.param[0] = GIC_SPI;
		p_fwspec.param[1] = desc->irq_parent;
		p_fwspec.param[2] = IRQ_TYPE_LEVEL_HIGH;

		वापस irq_करोमुख्य_alloc_irqs_parent(dm, virq, 1, &p_fwspec);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा
sपंचांग32_exti_host_data *sपंचांग32_exti_host_init(स्थिर काष्ठा sपंचांग32_exti_drv_data *dd,
					   काष्ठा device_node *node)
अणु
	काष्ठा sपंचांग32_exti_host_data *host_data;

	host_data = kzalloc(माप(*host_data), GFP_KERNEL);
	अगर (!host_data)
		वापस शून्य;

	host_data->drv_data = dd;
	host_data->chips_data = kसुस्मृति(dd->bank_nr,
					माप(काष्ठा sपंचांग32_exti_chip_data),
					GFP_KERNEL);
	अगर (!host_data->chips_data)
		जाओ मुक्त_host_data;

	host_data->base = of_iomap(node, 0);
	अगर (!host_data->base) अणु
		pr_err("%pOF: Unable to map registers\n", node);
		जाओ मुक्त_chips_data;
	पूर्ण

	sपंचांग32_host_data = host_data;

	वापस host_data;

मुक्त_chips_data:
	kमुक्त(host_data->chips_data);
मुक्त_host_data:
	kमुक्त(host_data);

	वापस शून्य;
पूर्ण

अटल काष्ठा
sपंचांग32_exti_chip_data *sपंचांग32_exti_chip_init(काष्ठा sपंचांग32_exti_host_data *h_data,
					   u32 bank_idx,
					   काष्ठा device_node *node)
अणु
	स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32_bank;
	काष्ठा sपंचांग32_exti_chip_data *chip_data;
	व्योम __iomem *base = h_data->base;

	sपंचांग32_bank = h_data->drv_data->exti_banks[bank_idx];
	chip_data = &h_data->chips_data[bank_idx];
	chip_data->host_data = h_data;
	chip_data->reg_bank = sपंचांग32_bank;

	raw_spin_lock_init(&chip_data->rlock);

	/*
	 * This IP has no reset, so after hot reboot we should
	 * clear रेजिस्टरs to aव्योम residue
	 */
	ग_लिखोl_relaxed(0, base + sपंचांग32_bank->imr_ofst);
	ग_लिखोl_relaxed(0, base + sपंचांग32_bank->emr_ofst);

	pr_info("%pOF: bank%d\n", node, bank_idx);

	वापस chip_data;
पूर्ण

अटल पूर्णांक __init sपंचांग32_exti_init(स्थिर काष्ठा sपंचांग32_exti_drv_data *drv_data,
				  काष्ठा device_node *node)
अणु
	काष्ठा sपंचांग32_exti_host_data *host_data;
	अचिन्हित पूर्णांक clr = IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN;
	पूर्णांक nr_irqs, ret, i;
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_करोमुख्य *करोमुख्य;

	host_data = sपंचांग32_exti_host_init(drv_data, node);
	अगर (!host_data)
		वापस -ENOMEM;

	करोमुख्य = irq_करोमुख्य_add_linear(node, drv_data->bank_nr * IRQS_PER_BANK,
				       &irq_exti_करोमुख्य_ops, शून्य);
	अगर (!करोमुख्य) अणु
		pr_err("%pOFn: Could not register interrupt domain.\n",
		       node);
		ret = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(करोमुख्य, IRQS_PER_BANK, 1, "exti",
					     handle_edge_irq, clr, 0, 0);
	अगर (ret) अणु
		pr_err("%pOF: Could not allocate generic interrupt chip.\n",
		       node);
		जाओ out_मुक्त_करोमुख्य;
	पूर्ण

	क्रम (i = 0; i < drv_data->bank_nr; i++) अणु
		स्थिर काष्ठा sपंचांग32_exti_bank *sपंचांग32_bank;
		काष्ठा sपंचांग32_exti_chip_data *chip_data;

		sपंचांग32_bank = drv_data->exti_banks[i];
		chip_data = sपंचांग32_exti_chip_init(host_data, i, node);

		gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, i * IRQS_PER_BANK);

		gc->reg_base = host_data->base;
		gc->chip_types->type = IRQ_TYPE_EDGE_BOTH;
		gc->chip_types->chip.irq_ack = sपंचांग32_irq_ack;
		gc->chip_types->chip.irq_mask = irq_gc_mask_clr_bit;
		gc->chip_types->chip.irq_unmask = irq_gc_mask_set_bit;
		gc->chip_types->chip.irq_set_type = sपंचांग32_irq_set_type;
		gc->chip_types->chip.irq_set_wake = irq_gc_set_wake;
		gc->suspend = sपंचांग32_irq_suspend;
		gc->resume = sपंचांग32_irq_resume;
		gc->wake_enabled = IRQ_MSK(IRQS_PER_BANK);

		gc->chip_types->regs.mask = sपंचांग32_bank->imr_ofst;
		gc->निजी = (व्योम *)chip_data;
	पूर्ण

	nr_irqs = of_irq_count(node);
	क्रम (i = 0; i < nr_irqs; i++) अणु
		अचिन्हित पूर्णांक irq = irq_of_parse_and_map(node, i);

		irq_set_handler_data(irq, करोमुख्य);
		irq_set_chained_handler(irq, sपंचांग32_irq_handler);
	पूर्ण

	वापस 0;

out_मुक्त_करोमुख्य:
	irq_करोमुख्य_हटाओ(करोमुख्य);
out_unmap:
	iounmap(host_data->base);
	kमुक्त(host_data->chips_data);
	kमुक्त(host_data);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops sपंचांग32_exti_h_करोमुख्य_ops = अणु
	.alloc	= sपंचांग32_exti_h_करोमुख्य_alloc,
	.मुक्त	= irq_करोमुख्य_मुक्त_irqs_common,
	.xlate = irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल व्योम sपंचांग32_exti_हटाओ_irq(व्योम *data)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = data;

	irq_करोमुख्य_हटाओ(करोमुख्य);
पूर्ण

अटल पूर्णांक sपंचांग32_exti_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	sपंचांग32_exti_h_syscore_deinit();
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_exti_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, i;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा irq_करोमुख्य *parent_करोमुख्य, *करोमुख्य;
	काष्ठा sपंचांग32_exti_host_data *host_data;
	स्थिर काष्ठा sपंचांग32_exti_drv_data *drv_data;
	काष्ठा resource *res;

	host_data = devm_kzalloc(dev, माप(*host_data), GFP_KERNEL);
	अगर (!host_data)
		वापस -ENOMEM;

	/* check क्रम optional hwspinlock which may be not available yet */
	ret = of_hwspin_lock_get_id(np, 0);
	अगर (ret == -EPROBE_DEFER)
		/* hwspinlock framework not yet पढ़ोy */
		वापस ret;

	अगर (ret >= 0) अणु
		host_data->hwlock = devm_hwspin_lock_request_specअगरic(dev, ret);
		अगर (!host_data->hwlock) अणु
			dev_err(dev, "Failed to request hwspinlock\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (ret != -ENOENT) अणु
		/* note: ENOENT is a valid हाल (means 'no hwspinlock') */
		dev_err(dev, "Failed to get hwspinlock\n");
		वापस ret;
	पूर्ण

	/* initialize host_data */
	drv_data = of_device_get_match_data(dev);
	अगर (!drv_data) अणु
		dev_err(dev, "no of match data\n");
		वापस -ENODEV;
	पूर्ण
	host_data->drv_data = drv_data;

	host_data->chips_data = devm_kसुस्मृति(dev, drv_data->bank_nr,
					     माप(*host_data->chips_data),
					     GFP_KERNEL);
	अगर (!host_data->chips_data)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	host_data->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(host_data->base))
		वापस PTR_ERR(host_data->base);

	क्रम (i = 0; i < drv_data->bank_nr; i++)
		sपंचांग32_exti_chip_init(host_data, i, np);

	parent_करोमुख्य = irq_find_host(of_irq_find_parent(np));
	अगर (!parent_करोमुख्य) अणु
		dev_err(dev, "GIC interrupt-parent not found\n");
		वापस -EINVAL;
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_hierarchy(parent_करोमुख्य, 0,
					  drv_data->bank_nr * IRQS_PER_BANK,
					  np, &sपंचांग32_exti_h_करोमुख्य_ops,
					  host_data);

	अगर (!करोमुख्य) अणु
		dev_err(dev, "Could not register exti domain\n");
		वापस -ENOMEM;
	पूर्ण

	ret = devm_add_action_or_reset(dev, sपंचांग32_exti_हटाओ_irq, करोमुख्य);
	अगर (ret)
		वापस ret;

	sपंचांग32_exti_h_syscore_init(host_data);

	वापस 0;
पूर्ण

/* platक्रमm driver only क्रम MP1 */
अटल स्थिर काष्ठा of_device_id sपंचांग32_exti_ids[] = अणु
	अणु .compatible = "st,stm32mp1-exti", .data = &sपंचांग32mp1_drv_dataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_exti_ids);

अटल काष्ठा platक्रमm_driver sपंचांग32_exti_driver = अणु
	.probe		= sपंचांग32_exti_probe,
	.हटाओ		= sपंचांग32_exti_हटाओ,
	.driver		= अणु
		.name	= "stm32_exti",
		.of_match_table = sपंचांग32_exti_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sपंचांग32_exti_arch_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sपंचांग32_exti_driver);
पूर्ण

अटल व्योम __निकास sपंचांग32_exti_arch_निकास(व्योम)
अणु
	वापस platक्रमm_driver_unरेजिस्टर(&sपंचांग32_exti_driver);
पूर्ण

arch_initcall(sपंचांग32_exti_arch_init);
module_निकास(sपंचांग32_exti_arch_निकास);

/* no platक्रमm driver क्रम F4 and H7 */
अटल पूर्णांक __init sपंचांग32f4_exti_of_init(काष्ठा device_node *np,
				       काष्ठा device_node *parent)
अणु
	वापस sपंचांग32_exti_init(&sपंचांग32f4xx_drv_data, np);
पूर्ण

IRQCHIP_DECLARE(sपंचांग32f4_exti, "st,stm32-exti", sपंचांग32f4_exti_of_init);

अटल पूर्णांक __init sपंचांग32h7_exti_of_init(काष्ठा device_node *np,
				       काष्ठा device_node *parent)
अणु
	वापस sपंचांग32_exti_init(&sपंचांग32h7xx_drv_data, np);
पूर्ण

IRQCHIP_DECLARE(sपंचांग32h7_exti, "st,stm32h7-exti", sपंचांग32h7_exti_of_init);
