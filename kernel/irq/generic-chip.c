<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Library implementing the most common irq chip callback functions
 *
 * Copyright (C) 2011, Thomas Gleixner
 */
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/syscore_ops.h>

#समावेश "internals.h"

अटल LIST_HEAD(gc_list);
अटल DEFINE_RAW_SPINLOCK(gc_lock);

/**
 * irq_gc_noop - NOOP function
 * @d: irq_data
 */
व्योम irq_gc_noop(काष्ठा irq_data *d)
अणु
पूर्ण

/**
 * irq_gc_mask_disable_reg - Mask chip via disable रेजिस्टर
 * @d: irq_data
 *
 * Chip has separate enable/disable रेजिस्टरs instead of a single mask
 * रेजिस्टर.
 */
व्योम irq_gc_mask_disable_reg(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 mask = d->mask;

	irq_gc_lock(gc);
	irq_reg_ग_लिखोl(gc, mask, ct->regs.disable);
	*ct->mask_cache &= ~mask;
	irq_gc_unlock(gc);
पूर्ण

/**
 * irq_gc_mask_set_bit - Mask chip via setting bit in mask रेजिस्टर
 * @d: irq_data
 *
 * Chip has a single mask रेजिस्टर. Values of this रेजिस्टर are cached
 * and रक्षित by gc->lock
 */
व्योम irq_gc_mask_set_bit(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 mask = d->mask;

	irq_gc_lock(gc);
	*ct->mask_cache |= mask;
	irq_reg_ग_लिखोl(gc, *ct->mask_cache, ct->regs.mask);
	irq_gc_unlock(gc);
पूर्ण
EXPORT_SYMBOL_GPL(irq_gc_mask_set_bit);

/**
 * irq_gc_mask_clr_bit - Mask chip via clearing bit in mask रेजिस्टर
 * @d: irq_data
 *
 * Chip has a single mask रेजिस्टर. Values of this रेजिस्टर are cached
 * and रक्षित by gc->lock
 */
व्योम irq_gc_mask_clr_bit(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 mask = d->mask;

	irq_gc_lock(gc);
	*ct->mask_cache &= ~mask;
	irq_reg_ग_लिखोl(gc, *ct->mask_cache, ct->regs.mask);
	irq_gc_unlock(gc);
पूर्ण
EXPORT_SYMBOL_GPL(irq_gc_mask_clr_bit);

/**
 * irq_gc_unmask_enable_reg - Unmask chip via enable रेजिस्टर
 * @d: irq_data
 *
 * Chip has separate enable/disable रेजिस्टरs instead of a single mask
 * रेजिस्टर.
 */
व्योम irq_gc_unmask_enable_reg(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 mask = d->mask;

	irq_gc_lock(gc);
	irq_reg_ग_लिखोl(gc, mask, ct->regs.enable);
	*ct->mask_cache |= mask;
	irq_gc_unlock(gc);
पूर्ण

/**
 * irq_gc_ack_set_bit - Ack pending पूर्णांकerrupt via setting bit
 * @d: irq_data
 */
व्योम irq_gc_ack_set_bit(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 mask = d->mask;

	irq_gc_lock(gc);
	irq_reg_ग_लिखोl(gc, mask, ct->regs.ack);
	irq_gc_unlock(gc);
पूर्ण
EXPORT_SYMBOL_GPL(irq_gc_ack_set_bit);

/**
 * irq_gc_ack_clr_bit - Ack pending पूर्णांकerrupt via clearing bit
 * @d: irq_data
 */
व्योम irq_gc_ack_clr_bit(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 mask = ~d->mask;

	irq_gc_lock(gc);
	irq_reg_ग_लिखोl(gc, mask, ct->regs.ack);
	irq_gc_unlock(gc);
पूर्ण

/**
 * irq_gc_mask_disable_and_ack_set - Mask and ack pending पूर्णांकerrupt
 * @d: irq_data
 *
 * This generic implementation of the irq_mask_ack method is क्रम chips
 * with separate enable/disable रेजिस्टरs instead of a single mask
 * रेजिस्टर and where a pending पूर्णांकerrupt is acknowledged by setting a
 * bit.
 *
 * Note: This is the only permutation currently used.  Similar generic
 * functions should be added here अगर other permutations are required.
 */
व्योम irq_gc_mask_disable_and_ack_set(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 mask = d->mask;

	irq_gc_lock(gc);
	irq_reg_ग_लिखोl(gc, mask, ct->regs.disable);
	*ct->mask_cache &= ~mask;
	irq_reg_ग_लिखोl(gc, mask, ct->regs.ack);
	irq_gc_unlock(gc);
पूर्ण

/**
 * irq_gc_eoi - EOI पूर्णांकerrupt
 * @d: irq_data
 */
व्योम irq_gc_eoi(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 mask = d->mask;

	irq_gc_lock(gc);
	irq_reg_ग_लिखोl(gc, mask, ct->regs.eoi);
	irq_gc_unlock(gc);
पूर्ण

/**
 * irq_gc_set_wake - Set/clr wake bit क्रम an पूर्णांकerrupt
 * @d:  irq_data
 * @on: Indicates whether the wake bit should be set or cleared
 *
 * For chips where the wake from suspend functionality is not
 * configured in a separate रेजिस्टर and the wakeup active state is
 * just stored in a biपंचांगask.
 */
पूर्णांक irq_gc_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	u32 mask = d->mask;

	अगर (!(mask & gc->wake_enabled))
		वापस -EINVAL;

	irq_gc_lock(gc);
	अगर (on)
		gc->wake_active |= mask;
	अन्यथा
		gc->wake_active &= ~mask;
	irq_gc_unlock(gc);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(irq_gc_set_wake);

अटल u32 irq_पढ़ोl_be(व्योम __iomem *addr)
अणु
	वापस ioपढ़ो32be(addr);
पूर्ण

अटल व्योम irq_ग_लिखोl_be(u32 val, व्योम __iomem *addr)
अणु
	ioग_लिखो32be(val, addr);
पूर्ण

व्योम irq_init_generic_chip(काष्ठा irq_chip_generic *gc, स्थिर अक्षर *name,
			   पूर्णांक num_ct, अचिन्हित पूर्णांक irq_base,
			   व्योम __iomem *reg_base, irq_flow_handler_t handler)
अणु
	raw_spin_lock_init(&gc->lock);
	gc->num_ct = num_ct;
	gc->irq_base = irq_base;
	gc->reg_base = reg_base;
	gc->chip_types->chip.name = name;
	gc->chip_types->handler = handler;
पूर्ण

/**
 * irq_alloc_generic_chip - Allocate a generic chip and initialize it
 * @name:	Name of the irq chip
 * @num_ct:	Number of irq_chip_type instances associated with this
 * @irq_base:	Interrupt base nr क्रम this chip
 * @reg_base:	Register base address (भव)
 * @handler:	Default flow handler associated with this chip
 *
 * Returns an initialized irq_chip_generic काष्ठाure. The chip शेषs
 * to the primary (index 0) irq_chip_type and @handler
 */
काष्ठा irq_chip_generic *
irq_alloc_generic_chip(स्थिर अक्षर *name, पूर्णांक num_ct, अचिन्हित पूर्णांक irq_base,
		       व्योम __iomem *reg_base, irq_flow_handler_t handler)
अणु
	काष्ठा irq_chip_generic *gc;
	अचिन्हित दीर्घ sz = माप(*gc) + num_ct * माप(काष्ठा irq_chip_type);

	gc = kzalloc(sz, GFP_KERNEL);
	अगर (gc) अणु
		irq_init_generic_chip(gc, name, num_ct, irq_base, reg_base,
				      handler);
	पूर्ण
	वापस gc;
पूर्ण
EXPORT_SYMBOL_GPL(irq_alloc_generic_chip);

अटल व्योम
irq_gc_init_mask_cache(काष्ठा irq_chip_generic *gc, क्रमागत irq_gc_flags flags)
अणु
	काष्ठा irq_chip_type *ct = gc->chip_types;
	u32 *mskptr = &gc->mask_cache, mskreg = ct->regs.mask;
	पूर्णांक i;

	क्रम (i = 0; i < gc->num_ct; i++) अणु
		अगर (flags & IRQ_GC_MASK_CACHE_PER_TYPE) अणु
			mskptr = &ct[i].mask_cache_priv;
			mskreg = ct[i].regs.mask;
		पूर्ण
		ct[i].mask_cache = mskptr;
		अगर (flags & IRQ_GC_INIT_MASK_CACHE)
			*mskptr = irq_reg_पढ़ोl(gc, mskreg);
	पूर्ण
पूर्ण

/**
 * __irq_alloc_करोमुख्य_generic_chips - Allocate generic chips क्रम an irq करोमुख्य
 * @d:			irq करोमुख्य क्रम which to allocate chips
 * @irqs_per_chip:	Number of पूर्णांकerrupts each chip handles (max 32)
 * @num_ct:		Number of irq_chip_type instances associated with this
 * @name:		Name of the irq chip
 * @handler:		Default flow handler associated with these chips
 * @clr:		IRQ_* bits to clear in the mapping function
 * @set:		IRQ_* bits to set in the mapping function
 * @gcflags:		Generic chip specअगरic setup flags
 */
पूर्णांक __irq_alloc_करोमुख्य_generic_chips(काष्ठा irq_करोमुख्य *d, पूर्णांक irqs_per_chip,
				     पूर्णांक num_ct, स्थिर अक्षर *name,
				     irq_flow_handler_t handler,
				     अचिन्हित पूर्णांक clr, अचिन्हित पूर्णांक set,
				     क्रमागत irq_gc_flags gcflags)
अणु
	काष्ठा irq_करोमुख्य_chip_generic *dgc;
	काष्ठा irq_chip_generic *gc;
	पूर्णांक numchips, sz, i;
	अचिन्हित दीर्घ flags;
	व्योम *पंचांगp;

	अगर (d->gc)
		वापस -EBUSY;

	numchips = DIV_ROUND_UP(d->revmap_size, irqs_per_chip);
	अगर (!numchips)
		वापस -EINVAL;

	/* Allocate a poपूर्णांकer, generic chip and chiptypes क्रम each chip */
	sz = माप(*dgc) + numchips * माप(gc);
	sz += numchips * (माप(*gc) + num_ct * माप(काष्ठा irq_chip_type));

	पंचांगp = dgc = kzalloc(sz, GFP_KERNEL);
	अगर (!dgc)
		वापस -ENOMEM;
	dgc->irqs_per_chip = irqs_per_chip;
	dgc->num_chips = numchips;
	dgc->irq_flags_to_set = set;
	dgc->irq_flags_to_clear = clr;
	dgc->gc_flags = gcflags;
	d->gc = dgc;

	/* Calc poपूर्णांकer to the first generic chip */
	पंचांगp += माप(*dgc) + numchips * माप(gc);
	क्रम (i = 0; i < numchips; i++) अणु
		/* Store the poपूर्णांकer to the generic chip */
		dgc->gc[i] = gc = पंचांगp;
		irq_init_generic_chip(gc, name, num_ct, i * irqs_per_chip,
				      शून्य, handler);

		gc->करोमुख्य = d;
		अगर (gcflags & IRQ_GC_BE_IO) अणु
			gc->reg_पढ़ोl = &irq_पढ़ोl_be;
			gc->reg_ग_लिखोl = &irq_ग_लिखोl_be;
		पूर्ण

		raw_spin_lock_irqsave(&gc_lock, flags);
		list_add_tail(&gc->list, &gc_list);
		raw_spin_unlock_irqrestore(&gc_lock, flags);
		/* Calc poपूर्णांकer to the next generic chip */
		पंचांगp += माप(*gc) + num_ct * माप(काष्ठा irq_chip_type);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__irq_alloc_करोमुख्य_generic_chips);

अटल काष्ठा irq_chip_generic *
__irq_get_करोमुख्य_generic_chip(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक hw_irq)
अणु
	काष्ठा irq_करोमुख्य_chip_generic *dgc = d->gc;
	पूर्णांक idx;

	अगर (!dgc)
		वापस ERR_PTR(-ENODEV);
	idx = hw_irq / dgc->irqs_per_chip;
	अगर (idx >= dgc->num_chips)
		वापस ERR_PTR(-EINVAL);
	वापस dgc->gc[idx];
पूर्ण

/**
 * irq_get_करोमुख्य_generic_chip - Get a poपूर्णांकer to the generic chip of a hw_irq
 * @d:			irq करोमुख्य poपूर्णांकer
 * @hw_irq:		Hardware पूर्णांकerrupt number
 */
काष्ठा irq_chip_generic *
irq_get_करोमुख्य_generic_chip(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक hw_irq)
अणु
	काष्ठा irq_chip_generic *gc = __irq_get_करोमुख्य_generic_chip(d, hw_irq);

	वापस !IS_ERR(gc) ? gc : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(irq_get_करोमुख्य_generic_chip);

/*
 * Separate lockdep classes क्रम पूर्णांकerrupt chip which can nest irq_desc
 * lock and request mutex.
 */
अटल काष्ठा lock_class_key irq_nested_lock_class;
अटल काष्ठा lock_class_key irq_nested_request_class;

/*
 * irq_map_generic_chip - Map a generic chip क्रम an irq करोमुख्य
 */
पूर्णांक irq_map_generic_chip(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hw_irq)
अणु
	काष्ठा irq_data *data = irq_करोमुख्य_get_irq_data(d, virq);
	काष्ठा irq_करोमुख्य_chip_generic *dgc = d->gc;
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	काष्ठा irq_chip *chip;
	अचिन्हित दीर्घ flags;
	पूर्णांक idx;

	gc = __irq_get_करोमुख्य_generic_chip(d, hw_irq);
	अगर (IS_ERR(gc))
		वापस PTR_ERR(gc);

	idx = hw_irq % dgc->irqs_per_chip;

	अगर (test_bit(idx, &gc->unused))
		वापस -ENOTSUPP;

	अगर (test_bit(idx, &gc->installed))
		वापस -EBUSY;

	ct = gc->chip_types;
	chip = &ct->chip;

	/* We only init the cache क्रम the first mapping of a generic chip */
	अगर (!gc->installed) अणु
		raw_spin_lock_irqsave(&gc->lock, flags);
		irq_gc_init_mask_cache(gc, dgc->gc_flags);
		raw_spin_unlock_irqrestore(&gc->lock, flags);
	पूर्ण

	/* Mark the पूर्णांकerrupt as installed */
	set_bit(idx, &gc->installed);

	अगर (dgc->gc_flags & IRQ_GC_INIT_NESTED_LOCK)
		irq_set_lockdep_class(virq, &irq_nested_lock_class,
				      &irq_nested_request_class);

	अगर (chip->irq_calc_mask)
		chip->irq_calc_mask(data);
	अन्यथा
		data->mask = 1 << idx;

	irq_करोमुख्य_set_info(d, virq, hw_irq, chip, gc, ct->handler, शून्य, शून्य);
	irq_modअगरy_status(virq, dgc->irq_flags_to_clear, dgc->irq_flags_to_set);
	वापस 0;
पूर्ण

अटल व्योम irq_unmap_generic_chip(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq)
अणु
	काष्ठा irq_data *data = irq_करोमुख्य_get_irq_data(d, virq);
	काष्ठा irq_करोमुख्य_chip_generic *dgc = d->gc;
	अचिन्हित पूर्णांक hw_irq = data->hwirq;
	काष्ठा irq_chip_generic *gc;
	पूर्णांक irq_idx;

	gc = irq_get_करोमुख्य_generic_chip(d, hw_irq);
	अगर (!gc)
		वापस;

	irq_idx = hw_irq % dgc->irqs_per_chip;

	clear_bit(irq_idx, &gc->installed);
	irq_करोमुख्य_set_info(d, virq, hw_irq, &no_irq_chip, शून्य, शून्य, शून्य,
			    शून्य);

पूर्ण

काष्ठा irq_करोमुख्य_ops irq_generic_chip_ops = अणु
	.map	= irq_map_generic_chip,
	.unmap  = irq_unmap_generic_chip,
	.xlate	= irq_करोमुख्य_xlate_onetwocell,
पूर्ण;
EXPORT_SYMBOL_GPL(irq_generic_chip_ops);

/**
 * irq_setup_generic_chip - Setup a range of पूर्णांकerrupts with a generic chip
 * @gc:		Generic irq chip holding all data
 * @msk:	Biपंचांगask holding the irqs to initialize relative to gc->irq_base
 * @flags:	Flags क्रम initialization
 * @clr:	IRQ_* bits to clear
 * @set:	IRQ_* bits to set
 *
 * Set up max. 32 पूर्णांकerrupts starting from gc->irq_base. Note, this
 * initializes all पूर्णांकerrupts to the primary irq_chip_type and its
 * associated handler.
 */
व्योम irq_setup_generic_chip(काष्ठा irq_chip_generic *gc, u32 msk,
			    क्रमागत irq_gc_flags flags, अचिन्हित पूर्णांक clr,
			    अचिन्हित पूर्णांक set)
अणु
	काष्ठा irq_chip_type *ct = gc->chip_types;
	काष्ठा irq_chip *chip = &ct->chip;
	अचिन्हित पूर्णांक i;

	raw_spin_lock(&gc_lock);
	list_add_tail(&gc->list, &gc_list);
	raw_spin_unlock(&gc_lock);

	irq_gc_init_mask_cache(gc, flags);

	क्रम (i = gc->irq_base; msk; msk >>= 1, i++) अणु
		अगर (!(msk & 0x01))
			जारी;

		अगर (flags & IRQ_GC_INIT_NESTED_LOCK)
			irq_set_lockdep_class(i, &irq_nested_lock_class,
					      &irq_nested_request_class);

		अगर (!(flags & IRQ_GC_NO_MASK)) अणु
			काष्ठा irq_data *d = irq_get_irq_data(i);

			अगर (chip->irq_calc_mask)
				chip->irq_calc_mask(d);
			अन्यथा
				d->mask = 1 << (i - gc->irq_base);
		पूर्ण
		irq_set_chip_and_handler(i, chip, ct->handler);
		irq_set_chip_data(i, gc);
		irq_modअगरy_status(i, clr, set);
	पूर्ण
	gc->irq_cnt = i - gc->irq_base;
पूर्ण
EXPORT_SYMBOL_GPL(irq_setup_generic_chip);

/**
 * irq_setup_alt_chip - Switch to alternative chip
 * @d:		irq_data क्रम this पूर्णांकerrupt
 * @type:	Flow type to be initialized
 *
 * Only to be called from chip->irq_set_type() callbacks.
 */
पूर्णांक irq_setup_alt_chip(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = gc->chip_types;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < gc->num_ct; i++, ct++) अणु
		अगर (ct->type & type) अणु
			d->chip = &ct->chip;
			irq_data_to_desc(d)->handle_irq = ct->handler;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(irq_setup_alt_chip);

/**
 * irq_हटाओ_generic_chip - Remove a chip
 * @gc:		Generic irq chip holding all data
 * @msk:	Biपंचांगask holding the irqs to initialize relative to gc->irq_base
 * @clr:	IRQ_* bits to clear
 * @set:	IRQ_* bits to set
 *
 * Remove up to 32 पूर्णांकerrupts starting from gc->irq_base.
 */
व्योम irq_हटाओ_generic_chip(काष्ठा irq_chip_generic *gc, u32 msk,
			     अचिन्हित पूर्णांक clr, अचिन्हित पूर्णांक set)
अणु
	अचिन्हित पूर्णांक i = gc->irq_base;

	raw_spin_lock(&gc_lock);
	list_del(&gc->list);
	raw_spin_unlock(&gc_lock);

	क्रम (; msk; msk >>= 1, i++) अणु
		अगर (!(msk & 0x01))
			जारी;

		/* Remove handler first. That will mask the irq line */
		irq_set_handler(i, शून्य);
		irq_set_chip(i, &no_irq_chip);
		irq_set_chip_data(i, शून्य);
		irq_modअगरy_status(i, clr, set);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(irq_हटाओ_generic_chip);

अटल काष्ठा irq_data *irq_gc_get_irq_data(काष्ठा irq_chip_generic *gc)
अणु
	अचिन्हित पूर्णांक virq;

	अगर (!gc->करोमुख्य)
		वापस irq_get_irq_data(gc->irq_base);

	/*
	 * We करोn't know which of the irqs has been actually
	 * installed. Use the first one.
	 */
	अगर (!gc->installed)
		वापस शून्य;

	virq = irq_find_mapping(gc->करोमुख्य, gc->irq_base + __ffs(gc->installed));
	वापस virq ? irq_get_irq_data(virq) : शून्य;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक irq_gc_suspend(व्योम)
अणु
	काष्ठा irq_chip_generic *gc;

	list_क्रम_each_entry(gc, &gc_list, list) अणु
		काष्ठा irq_chip_type *ct = gc->chip_types;

		अगर (ct->chip.irq_suspend) अणु
			काष्ठा irq_data *data = irq_gc_get_irq_data(gc);

			अगर (data)
				ct->chip.irq_suspend(data);
		पूर्ण

		अगर (gc->suspend)
			gc->suspend(gc);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम irq_gc_resume(व्योम)
अणु
	काष्ठा irq_chip_generic *gc;

	list_क्रम_each_entry(gc, &gc_list, list) अणु
		काष्ठा irq_chip_type *ct = gc->chip_types;

		अगर (gc->resume)
			gc->resume(gc);

		अगर (ct->chip.irq_resume) अणु
			काष्ठा irq_data *data = irq_gc_get_irq_data(gc);

			अगर (data)
				ct->chip.irq_resume(data);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा irq_gc_suspend शून्य
#घोषणा irq_gc_resume शून्य
#पूर्ण_अगर

अटल व्योम irq_gc_shutकरोwn(व्योम)
अणु
	काष्ठा irq_chip_generic *gc;

	list_क्रम_each_entry(gc, &gc_list, list) अणु
		काष्ठा irq_chip_type *ct = gc->chip_types;

		अगर (ct->chip.irq_pm_shutकरोwn) अणु
			काष्ठा irq_data *data = irq_gc_get_irq_data(gc);

			अगर (data)
				ct->chip.irq_pm_shutकरोwn(data);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा syscore_ops irq_gc_syscore_ops = अणु
	.suspend = irq_gc_suspend,
	.resume = irq_gc_resume,
	.shutकरोwn = irq_gc_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init irq_gc_init_ops(व्योम)
अणु
	रेजिस्टर_syscore_ops(&irq_gc_syscore_ops);
	वापस 0;
पूर्ण
device_initcall(irq_gc_init_ops);
