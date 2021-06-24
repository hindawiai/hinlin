<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008
 * Guennadi Liakhovetski, DENX Software Engineering, <lg@denx.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/dma/ipu-dma.h>

#समावेश "ipu_intern.h"

/*
 * Register पढ़ो / ग_लिखो - shall be अंतरभूतd by the compiler
 */
अटल u32 ipu_पढ़ो_reg(काष्ठा ipu *ipu, अचिन्हित दीर्घ reg)
अणु
	वापस __raw_पढ़ोl(ipu->reg_ipu + reg);
पूर्ण

अटल व्योम ipu_ग_लिखो_reg(काष्ठा ipu *ipu, u32 value, अचिन्हित दीर्घ reg)
अणु
	__raw_ग_लिखोl(value, ipu->reg_ipu + reg);
पूर्ण


/*
 * IPU IRQ chip driver
 */

#घोषणा IPU_IRQ_NR_FN_BANKS 3
#घोषणा IPU_IRQ_NR_ERR_BANKS 2
#घोषणा IPU_IRQ_NR_BANKS (IPU_IRQ_NR_FN_BANKS + IPU_IRQ_NR_ERR_BANKS)

काष्ठा ipu_irq_bank अणु
	अचिन्हित पूर्णांक	control;
	अचिन्हित पूर्णांक	status;
	काष्ठा ipu	*ipu;
पूर्ण;

अटल काष्ठा ipu_irq_bank irq_bank[IPU_IRQ_NR_BANKS] = अणु
	/* 3 groups of functional पूर्णांकerrupts */
	अणु
		.control	= IPU_INT_CTRL_1,
		.status		= IPU_INT_STAT_1,
	पूर्ण, अणु
		.control	= IPU_INT_CTRL_2,
		.status		= IPU_INT_STAT_2,
	पूर्ण, अणु
		.control	= IPU_INT_CTRL_3,
		.status		= IPU_INT_STAT_3,
	पूर्ण,
	/* 2 groups of error पूर्णांकerrupts */
	अणु
		.control	= IPU_INT_CTRL_4,
		.status		= IPU_INT_STAT_4,
	पूर्ण, अणु
		.control	= IPU_INT_CTRL_5,
		.status		= IPU_INT_STAT_5,
	पूर्ण,
पूर्ण;

काष्ठा ipu_irq_map अणु
	अचिन्हित पूर्णांक		irq;
	पूर्णांक			source;
	काष्ठा ipu_irq_bank	*bank;
	काष्ठा ipu		*ipu;
पूर्ण;

अटल काष्ठा ipu_irq_map irq_map[CONFIG_MX3_IPU_IRQS];
/* Protects allocations from the above array of maps */
अटल DEFINE_MUTEX(map_lock);
/* Protects रेजिस्टर accesses and inभागidual mappings */
अटल DEFINE_RAW_SPINLOCK(bank_lock);

अटल काष्ठा ipu_irq_map *src2map(अचिन्हित पूर्णांक src)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CONFIG_MX3_IPU_IRQS; i++)
		अगर (irq_map[i].source == src)
			वापस irq_map + i;

	वापस शून्य;
पूर्ण

अटल व्योम ipu_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा ipu_irq_map *map = irq_data_get_irq_chip_data(d);
	काष्ठा ipu_irq_bank *bank;
	uपूर्णांक32_t reg;
	अचिन्हित दीर्घ lock_flags;

	raw_spin_lock_irqsave(&bank_lock, lock_flags);

	bank = map->bank;
	अगर (!bank) अणु
		raw_spin_unlock_irqrestore(&bank_lock, lock_flags);
		pr_err("IPU: %s(%u) - unmapped!\n", __func__, d->irq);
		वापस;
	पूर्ण

	reg = ipu_पढ़ो_reg(bank->ipu, bank->control);
	reg |= (1UL << (map->source & 31));
	ipu_ग_लिखो_reg(bank->ipu, reg, bank->control);

	raw_spin_unlock_irqrestore(&bank_lock, lock_flags);
पूर्ण

अटल व्योम ipu_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा ipu_irq_map *map = irq_data_get_irq_chip_data(d);
	काष्ठा ipu_irq_bank *bank;
	uपूर्णांक32_t reg;
	अचिन्हित दीर्घ lock_flags;

	raw_spin_lock_irqsave(&bank_lock, lock_flags);

	bank = map->bank;
	अगर (!bank) अणु
		raw_spin_unlock_irqrestore(&bank_lock, lock_flags);
		pr_err("IPU: %s(%u) - unmapped!\n", __func__, d->irq);
		वापस;
	पूर्ण

	reg = ipu_पढ़ो_reg(bank->ipu, bank->control);
	reg &= ~(1UL << (map->source & 31));
	ipu_ग_लिखो_reg(bank->ipu, reg, bank->control);

	raw_spin_unlock_irqrestore(&bank_lock, lock_flags);
पूर्ण

अटल व्योम ipu_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा ipu_irq_map *map = irq_data_get_irq_chip_data(d);
	काष्ठा ipu_irq_bank *bank;
	अचिन्हित दीर्घ lock_flags;

	raw_spin_lock_irqsave(&bank_lock, lock_flags);

	bank = map->bank;
	अगर (!bank) अणु
		raw_spin_unlock_irqrestore(&bank_lock, lock_flags);
		pr_err("IPU: %s(%u) - unmapped!\n", __func__, d->irq);
		वापस;
	पूर्ण

	ipu_ग_लिखो_reg(bank->ipu, 1UL << (map->source & 31), bank->status);
	raw_spin_unlock_irqrestore(&bank_lock, lock_flags);
पूर्ण

/**
 * ipu_irq_status() - वापसs the current पूर्णांकerrupt status of the specअगरied IRQ.
 * @irq:	पूर्णांकerrupt line to get status क्रम.
 * @वापस:	true अगर the पूर्णांकerrupt is pending/निश्चितed or false अगर the
 *		पूर्णांकerrupt is not pending.
 */
bool ipu_irq_status(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा ipu_irq_map *map = irq_get_chip_data(irq);
	काष्ठा ipu_irq_bank *bank;
	अचिन्हित दीर्घ lock_flags;
	bool ret;

	raw_spin_lock_irqsave(&bank_lock, lock_flags);
	bank = map->bank;
	ret = bank && ipu_पढ़ो_reg(bank->ipu, bank->status) &
		(1UL << (map->source & 31));
	raw_spin_unlock_irqrestore(&bank_lock, lock_flags);

	वापस ret;
पूर्ण

/**
 * ipu_irq_map() - map an IPU पूर्णांकerrupt source to an IRQ number
 * @source:	पूर्णांकerrupt source bit position (see below)
 * @वापस:	mapped IRQ number or negative error code
 *
 * The source parameter has to be explained further. On i.MX31 IPU has 137 IRQ
 * sources, they are broken करोwn in 5 32-bit रेजिस्टरs, like 32, 32, 24, 32, 17.
 * However, the source argument of this function is not the sequence number of
 * the possible IRQ, but rather its bit position. So, first पूर्णांकerrupt in fourth
 * रेजिस्टर has source number 96, and not 88. This makes calculations easier,
 * and also provides क्रमward compatibility with any future IPU implementations
 * with any पूर्णांकerrupt bit assignments.
 */
पूर्णांक ipu_irq_map(अचिन्हित पूर्णांक source)
अणु
	पूर्णांक i, ret = -ENOMEM;
	काष्ठा ipu_irq_map *map;

	might_sleep();

	mutex_lock(&map_lock);
	map = src2map(source);
	अगर (map) अणु
		pr_err("IPU: Source %u already mapped to IRQ %u\n", source, map->irq);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < CONFIG_MX3_IPU_IRQS; i++) अणु
		अगर (irq_map[i].source < 0) अणु
			अचिन्हित दीर्घ lock_flags;

			raw_spin_lock_irqsave(&bank_lock, lock_flags);
			irq_map[i].source = source;
			irq_map[i].bank = irq_bank + source / 32;
			raw_spin_unlock_irqrestore(&bank_lock, lock_flags);

			ret = irq_map[i].irq;
			pr_debug("IPU: mapped source %u to IRQ %u\n",
				 source, ret);
			अवरोध;
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&map_lock);

	अगर (ret < 0)
		pr_err("IPU: couldn't map source %u: %d\n", source, ret);

	वापस ret;
पूर्ण

/**
 * ipu_irq_unmap() - unmap an IPU पूर्णांकerrupt source
 * @source:	पूर्णांकerrupt source bit position (see ipu_irq_map())
 * @वापस:	0 or negative error code
 */
पूर्णांक ipu_irq_unmap(अचिन्हित पूर्णांक source)
अणु
	पूर्णांक i, ret = -EINVAL;

	might_sleep();

	mutex_lock(&map_lock);
	क्रम (i = 0; i < CONFIG_MX3_IPU_IRQS; i++) अणु
		अगर (irq_map[i].source == source) अणु
			अचिन्हित दीर्घ lock_flags;

			pr_debug("IPU: unmapped source %u from IRQ %u\n",
				 source, irq_map[i].irq);

			raw_spin_lock_irqsave(&bank_lock, lock_flags);
			irq_map[i].source = -EINVAL;
			irq_map[i].bank = शून्य;
			raw_spin_unlock_irqrestore(&bank_lock, lock_flags);

			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&map_lock);

	वापस ret;
पूर्ण

/* Chained IRQ handler क्रम IPU function and error पूर्णांकerrupt */
अटल व्योम ipu_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा ipu *ipu = irq_desc_get_handler_data(desc);
	u32 status;
	पूर्णांक i, line;

	क्रम (i = 0; i < IPU_IRQ_NR_BANKS; i++) अणु
		काष्ठा ipu_irq_bank *bank = irq_bank + i;

		raw_spin_lock(&bank_lock);
		status = ipu_पढ़ो_reg(ipu, bank->status);
		/*
		 * Don't think we have to clear all पूर्णांकerrupts here, they will
		 * be acked by ->handle_irq() (handle_level_irq). However, we
		 * might want to clear unhandled पूर्णांकerrupts after the loop...
		 */
		status &= ipu_पढ़ो_reg(ipu, bank->control);
		raw_spin_unlock(&bank_lock);
		जबतक ((line = ffs(status))) अणु
			काष्ठा ipu_irq_map *map;
			अचिन्हित पूर्णांक irq;

			line--;
			status &= ~(1UL << line);

			raw_spin_lock(&bank_lock);
			map = src2map(32 * i + line);
			अगर (!map) अणु
				raw_spin_unlock(&bank_lock);
				pr_err("IPU: Interrupt on unmapped source %u bank %d\n",
				       line, i);
				जारी;
			पूर्ण
			irq = map->irq;
			raw_spin_unlock(&bank_lock);
			generic_handle_irq(irq);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip ipu_irq_chip = अणु
	.name		= "ipu_irq",
	.irq_ack	= ipu_irq_ack,
	.irq_mask	= ipu_irq_mask,
	.irq_unmask	= ipu_irq_unmask,
पूर्ण;

/* Install the IRQ handler */
पूर्णांक __init ipu_irq_attach_irq(काष्ठा ipu *ipu, काष्ठा platक्रमm_device *dev)
अणु
	अचिन्हित पूर्णांक irq, i;
	पूर्णांक irq_base = irq_alloc_descs(-1, 0, CONFIG_MX3_IPU_IRQS,
				       numa_node_id());

	अगर (irq_base < 0)
		वापस irq_base;

	क्रम (i = 0; i < IPU_IRQ_NR_BANKS; i++)
		irq_bank[i].ipu = ipu;

	क्रम (i = 0; i < CONFIG_MX3_IPU_IRQS; i++) अणु
		पूर्णांक ret;

		irq = irq_base + i;
		ret = irq_set_chip(irq, &ipu_irq_chip);
		अगर (ret < 0)
			वापस ret;
		ret = irq_set_chip_data(irq, irq_map + i);
		अगर (ret < 0)
			वापस ret;
		irq_map[i].ipu = ipu;
		irq_map[i].irq = irq;
		irq_map[i].source = -EINVAL;
		irq_set_handler(irq, handle_level_irq);
		irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण

	irq_set_chained_handler_and_data(ipu->irq_fn, ipu_irq_handler, ipu);

	irq_set_chained_handler_and_data(ipu->irq_err, ipu_irq_handler, ipu);

	ipu->irq_base = irq_base;

	वापस 0;
पूर्ण

व्योम ipu_irq_detach_irq(काष्ठा ipu *ipu, काष्ठा platक्रमm_device *dev)
अणु
	अचिन्हित पूर्णांक irq, irq_base;

	irq_base = ipu->irq_base;

	irq_set_chained_handler_and_data(ipu->irq_fn, शून्य, शून्य);

	irq_set_chained_handler_and_data(ipu->irq_err, शून्य, शून्य);

	क्रम (irq = irq_base; irq < irq_base + CONFIG_MX3_IPU_IRQS; irq++) अणु
		irq_set_status_flags(irq, IRQ_NOREQUEST);
		irq_set_chip(irq, शून्य);
		irq_set_chip_data(irq, शून्य);
	पूर्ण
पूर्ण
