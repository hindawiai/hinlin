<शैली गुरु>
/*
 * Shared पूर्णांकerrupt handling code क्रम IPR and INTC2 types of IRQs.
 *
 * Copyright (C) 2007, 2008 Magnus Damm
 * Copyright (C) 2009 - 2012 Paul Mundt
 *
 * Based on पूर्णांकc2.c and ipr.c
 *
 * Copyright (C) 1999  Niibe Yutaka & Takeshi Yaegashi
 * Copyright (C) 2000  Kazumoto Kojima
 * Copyright (C) 2001  David J. Mckay (david.mckay@st.com)
 * Copyright (C) 2003  Takashi Kusuda <kusuda-takashi@hitachi-ul.co.jp>
 * Copyright (C) 2005, 2006  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#घोषणा pr_fmt(fmt) "intc: " fmt

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/export.h>
#समावेश <linux/sort.h>
#समावेश "internals.h"

LIST_HEAD(पूर्णांकc_list);
DEFINE_RAW_SPINLOCK(पूर्णांकc_big_lock);
अटल अचिन्हित पूर्णांक nr_पूर्णांकc_controllers;

/*
 * Default priority level
 * - this needs to be at least 2 क्रम 5-bit priorities on 7780
 */
अटल अचिन्हित पूर्णांक शेष_prio_level = 2;	/* 2 - 16 */
अटल अचिन्हित पूर्णांक पूर्णांकc_prio_level[INTC_NR_IRQS];	/* क्रम now */

अचिन्हित पूर्णांक पूर्णांकc_get_dfl_prio_level(व्योम)
अणु
	वापस शेष_prio_level;
पूर्ण

अचिन्हित पूर्णांक पूर्णांकc_get_prio_level(अचिन्हित पूर्णांक irq)
अणु
	वापस पूर्णांकc_prio_level[irq];
पूर्ण

व्योम पूर्णांकc_set_prio_level(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक level)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&पूर्णांकc_big_lock, flags);
	पूर्णांकc_prio_level[irq] = level;
	raw_spin_unlock_irqrestore(&पूर्णांकc_big_lock, flags);
पूर्ण

अटल व्योम पूर्णांकc_redirect_irq(काष्ठा irq_desc *desc)
अणु
	generic_handle_irq((अचिन्हित पूर्णांक)irq_desc_get_handler_data(desc));
पूर्ण

अटल व्योम __init पूर्णांकc_रेजिस्टर_irq(काष्ठा पूर्णांकc_desc *desc,
				     काष्ठा पूर्णांकc_desc_पूर्णांक *d,
				     पूर्णांकc_क्रमागत क्रमागत_id,
				     अचिन्हित पूर्णांक irq)
अणु
	काष्ठा पूर्णांकc_handle_पूर्णांक *hp;
	काष्ठा irq_data *irq_data;
	अचिन्हित पूर्णांक data[2], primary;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&पूर्णांकc_big_lock, flags);
	radix_tree_insert(&d->tree, क्रमागत_id, पूर्णांकc_irq_xlate_get(irq));
	raw_spin_unlock_irqrestore(&पूर्णांकc_big_lock, flags);

	/*
	 * Prefer single पूर्णांकerrupt source biपंचांगap over other combinations:
	 *
	 * 1. biपंचांगap, single पूर्णांकerrupt source
	 * 2. priority, single पूर्णांकerrupt source
	 * 3. biपंचांगap, multiple पूर्णांकerrupt sources (groups)
	 * 4. priority, multiple पूर्णांकerrupt sources (groups)
	 */
	data[0] = पूर्णांकc_get_mask_handle(desc, d, क्रमागत_id, 0);
	data[1] = पूर्णांकc_get_prio_handle(desc, d, क्रमागत_id, 0);

	primary = 0;
	अगर (!data[0] && data[1])
		primary = 1;

	अगर (!data[0] && !data[1])
		pr_warn("missing unique irq mask for irq %d (vect 0x%04x)\n",
			irq, irq2evt(irq));

	data[0] = data[0] ? data[0] : पूर्णांकc_get_mask_handle(desc, d, क्रमागत_id, 1);
	data[1] = data[1] ? data[1] : पूर्णांकc_get_prio_handle(desc, d, क्रमागत_id, 1);

	अगर (!data[primary])
		primary ^= 1;

	BUG_ON(!data[primary]); /* must have primary masking method */

	irq_data = irq_get_irq_data(irq);

	disable_irq_nosync(irq);
	irq_set_chip_and_handler_name(irq, &d->chip, handle_level_irq,
				      "level");
	irq_set_chip_data(irq, (व्योम *)data[primary]);

	/*
	 * set priority level
	 */
	पूर्णांकc_set_prio_level(irq, पूर्णांकc_get_dfl_prio_level());

	/* enable secondary masking method अगर present */
	अगर (data[!primary])
		_पूर्णांकc_enable(irq_data, data[!primary]);

	/* add irq to d->prio list अगर priority is available */
	अगर (data[1]) अणु
		hp = d->prio + d->nr_prio;
		hp->irq = irq;
		hp->handle = data[1];

		अगर (primary) अणु
			/*
			 * only secondary priority should access रेजिस्टरs, so
			 * set _INTC_FN(h) = REG_FN_ERR क्रम पूर्णांकc_set_priority()
			 */
			hp->handle &= ~_INTC_MK(0x0f, 0, 0, 0, 0, 0);
			hp->handle |= _INTC_MK(REG_FN_ERR, 0, 0, 0, 0, 0);
		पूर्ण
		d->nr_prio++;
	पूर्ण

	/* add irq to d->sense list अगर sense is available */
	data[0] = पूर्णांकc_get_sense_handle(desc, d, क्रमागत_id);
	अगर (data[0]) अणु
		(d->sense + d->nr_sense)->irq = irq;
		(d->sense + d->nr_sense)->handle = data[0];
		d->nr_sense++;
	पूर्ण

	/* irq should be disabled by शेष */
	d->chip.irq_mask(irq_data);

	पूर्णांकc_set_ack_handle(irq, desc, d, क्रमागत_id);
	पूर्णांकc_set_dist_handle(irq, desc, d, क्रमागत_id);

	activate_irq(irq);
पूर्ण

अटल अचिन्हित पूर्णांक __init save_reg(काष्ठा पूर्णांकc_desc_पूर्णांक *d,
				    अचिन्हित पूर्णांक cnt,
				    अचिन्हित दीर्घ value,
				    अचिन्हित पूर्णांक smp)
अणु
	अगर (value) अणु
		value = पूर्णांकc_phys_to_virt(d, value);

		d->reg[cnt] = value;
#अगर_घोषित CONFIG_SMP
		d->smp[cnt] = smp;
#पूर्ण_अगर
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool __init पूर्णांकc_map(काष्ठा irq_करोमुख्य *करोमुख्य, पूर्णांक irq)
अणु
	अगर (!irq_to_desc(irq) && irq_alloc_desc_at(irq, NUMA_NO_NODE) != irq) अणु
		pr_err("uname to allocate IRQ %d\n", irq);
		वापस false;
	पूर्ण

	अगर (irq_करोमुख्य_associate(करोमुख्य, irq, irq)) अणु
		pr_err("domain association failure\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक __init रेजिस्टर_पूर्णांकc_controller(काष्ठा पूर्णांकc_desc *desc)
अणु
	अचिन्हित पूर्णांक i, k, smp;
	काष्ठा पूर्णांकc_hw_desc *hw = &desc->hw;
	काष्ठा पूर्णांकc_desc_पूर्णांक *d;
	काष्ठा resource *res;

	pr_info("Registered controller '%s' with %u IRQs\n",
		desc->name, hw->nr_vectors);

	d = kzalloc(माप(*d), GFP_NOWAIT);
	अगर (!d)
		जाओ err0;

	INIT_LIST_HEAD(&d->list);
	list_add_tail(&d->list, &पूर्णांकc_list);

	raw_spin_lock_init(&d->lock);
	INIT_RADIX_TREE(&d->tree, GFP_ATOMIC);

	d->index = nr_पूर्णांकc_controllers;

	अगर (desc->num_resources) अणु
		d->nr_winकरोws = desc->num_resources;
		d->winकरोw = kसुस्मृति(d->nr_winकरोws, माप(*d->winकरोw),
				    GFP_NOWAIT);
		अगर (!d->winकरोw)
			जाओ err1;

		क्रम (k = 0; k < d->nr_winकरोws; k++) अणु
			res = desc->resource + k;
			WARN_ON(resource_type(res) != IORESOURCE_MEM);
			d->winकरोw[k].phys = res->start;
			d->winकरोw[k].size = resource_size(res);
			d->winकरोw[k].virt = ioremap(res->start,
						    resource_size(res));
			अगर (!d->winकरोw[k].virt)
				जाओ err2;
		पूर्ण
	पूर्ण

	d->nr_reg = hw->mask_regs ? hw->nr_mask_regs * 2 : 0;
#अगर_घोषित CONFIG_INTC_BALANCING
	अगर (d->nr_reg)
		d->nr_reg += hw->nr_mask_regs;
#पूर्ण_अगर
	d->nr_reg += hw->prio_regs ? hw->nr_prio_regs * 2 : 0;
	d->nr_reg += hw->sense_regs ? hw->nr_sense_regs : 0;
	d->nr_reg += hw->ack_regs ? hw->nr_ack_regs : 0;
	d->nr_reg += hw->subgroups ? hw->nr_subgroups : 0;

	d->reg = kसुस्मृति(d->nr_reg, माप(*d->reg), GFP_NOWAIT);
	अगर (!d->reg)
		जाओ err2;

#अगर_घोषित CONFIG_SMP
	d->smp = kसुस्मृति(d->nr_reg, माप(*d->smp), GFP_NOWAIT);
	अगर (!d->smp)
		जाओ err3;
#पूर्ण_अगर
	k = 0;

	अगर (hw->mask_regs) अणु
		क्रम (i = 0; i < hw->nr_mask_regs; i++) अणु
			smp = IS_SMP(hw->mask_regs[i]);
			k += save_reg(d, k, hw->mask_regs[i].set_reg, smp);
			k += save_reg(d, k, hw->mask_regs[i].clr_reg, smp);
#अगर_घोषित CONFIG_INTC_BALANCING
			k += save_reg(d, k, hw->mask_regs[i].dist_reg, 0);
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	अगर (hw->prio_regs) अणु
		d->prio = kसुस्मृति(hw->nr_vectors, माप(*d->prio),
				  GFP_NOWAIT);
		अगर (!d->prio)
			जाओ err4;

		क्रम (i = 0; i < hw->nr_prio_regs; i++) अणु
			smp = IS_SMP(hw->prio_regs[i]);
			k += save_reg(d, k, hw->prio_regs[i].set_reg, smp);
			k += save_reg(d, k, hw->prio_regs[i].clr_reg, smp);
		पूर्ण

		sort(d->prio, hw->nr_prio_regs, माप(*d->prio),
		     पूर्णांकc_handle_पूर्णांक_cmp, शून्य);
	पूर्ण

	अगर (hw->sense_regs) अणु
		d->sense = kसुस्मृति(hw->nr_vectors, माप(*d->sense),
				   GFP_NOWAIT);
		अगर (!d->sense)
			जाओ err5;

		क्रम (i = 0; i < hw->nr_sense_regs; i++)
			k += save_reg(d, k, hw->sense_regs[i].reg, 0);

		sort(d->sense, hw->nr_sense_regs, माप(*d->sense),
		     पूर्णांकc_handle_पूर्णांक_cmp, शून्य);
	पूर्ण

	अगर (hw->subgroups)
		क्रम (i = 0; i < hw->nr_subgroups; i++)
			अगर (hw->subgroups[i].reg)
				k+= save_reg(d, k, hw->subgroups[i].reg, 0);

	स_नकल(&d->chip, &पूर्णांकc_irq_chip, माप(काष्ठा irq_chip));
	d->chip.name = desc->name;

	अगर (hw->ack_regs)
		क्रम (i = 0; i < hw->nr_ack_regs; i++)
			k += save_reg(d, k, hw->ack_regs[i].set_reg, 0);
	अन्यथा
		d->chip.irq_mask_ack = d->chip.irq_disable;

	/* disable bits matching क्रमce_disable beक्रमe रेजिस्टरing irqs */
	अगर (desc->क्रमce_disable)
		पूर्णांकc_enable_disable_क्रमागत(desc, d, desc->क्रमce_disable, 0);

	/* disable bits matching क्रमce_enable beक्रमe रेजिस्टरing irqs */
	अगर (desc->क्रमce_enable)
		पूर्णांकc_enable_disable_क्रमागत(desc, d, desc->क्रमce_enable, 0);

	BUG_ON(k > 256); /* _INTC_ADDR_E() and _INTC_ADDR_D() are 8 bits */

	पूर्णांकc_irq_करोमुख्य_init(d, hw);

	/* रेजिस्टर the vectors one by one */
	क्रम (i = 0; i < hw->nr_vectors; i++) अणु
		काष्ठा पूर्णांकc_vect *vect = hw->vectors + i;
		अचिन्हित पूर्णांक irq = evt2irq(vect->vect);

		अगर (!vect->क्रमागत_id)
			जारी;

		अगर (!पूर्णांकc_map(d->करोमुख्य, irq))
			जारी;

		पूर्णांकc_irq_xlate_set(irq, vect->क्रमागत_id, d);
		पूर्णांकc_रेजिस्टर_irq(desc, d, vect->क्रमागत_id, irq);

		क्रम (k = i + 1; k < hw->nr_vectors; k++) अणु
			काष्ठा पूर्णांकc_vect *vect2 = hw->vectors + k;
			अचिन्हित पूर्णांक irq2 = evt2irq(vect2->vect);

			अगर (vect->क्रमागत_id != vect2->क्रमागत_id)
				जारी;

			/*
			 * In the हाल of multi-evt handling and sparse
			 * IRQ support, each vector still needs to have
			 * its own backing irq_desc.
			 */
			अगर (!पूर्णांकc_map(d->करोमुख्य, irq2))
				जारी;

			vect2->क्रमागत_id = 0;

			/* redirect this पूर्णांकerrupts to the first one */
			irq_set_chip(irq2, &dummy_irq_chip);
			irq_set_chained_handler_and_data(irq2,
							 पूर्णांकc_redirect_irq,
							 (व्योम *)irq);
		पूर्ण
	पूर्ण

	पूर्णांकc_subgroup_init(desc, d);

	/* enable bits matching क्रमce_enable after रेजिस्टरing irqs */
	अगर (desc->क्रमce_enable)
		पूर्णांकc_enable_disable_क्रमागत(desc, d, desc->क्रमce_enable, 1);

	d->skip_suspend = desc->skip_syscore_suspend;

	nr_पूर्णांकc_controllers++;

	वापस 0;
err5:
	kमुक्त(d->prio);
err4:
#अगर_घोषित CONFIG_SMP
	kमुक्त(d->smp);
err3:
#पूर्ण_अगर
	kमुक्त(d->reg);
err2:
	क्रम (k = 0; k < d->nr_winकरोws; k++)
		अगर (d->winकरोw[k].virt)
			iounmap(d->winकरोw[k].virt);

	kमुक्त(d->winकरोw);
err1:
	kमुक्त(d);
err0:
	pr_err("unable to allocate INTC memory\n");

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक पूर्णांकc_suspend(व्योम)
अणु
	काष्ठा पूर्णांकc_desc_पूर्णांक *d;

	list_क्रम_each_entry(d, &पूर्णांकc_list, list) अणु
		पूर्णांक irq;

		अगर (d->skip_suspend)
			जारी;

		/* enable wakeup irqs beदीर्घing to this पूर्णांकc controller */
		क्रम_each_active_irq(irq) अणु
			काष्ठा irq_data *data;
			काष्ठा irq_chip *chip;

			data = irq_get_irq_data(irq);
			chip = irq_data_get_irq_chip(data);
			अगर (chip != &d->chip)
				जारी;
			अगर (irqd_is_wakeup_set(data))
				chip->irq_enable(data);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकc_resume(व्योम)
अणु
	काष्ठा पूर्णांकc_desc_पूर्णांक *d;

	list_क्रम_each_entry(d, &पूर्णांकc_list, list) अणु
		पूर्णांक irq;

		अगर (d->skip_suspend)
			जारी;

		क्रम_each_active_irq(irq) अणु
			काष्ठा irq_data *data;
			काष्ठा irq_chip *chip;

			data = irq_get_irq_data(irq);
			chip = irq_data_get_irq_chip(data);
			/*
			 * This will catch the redirect and VIRQ हालs
			 * due to the dummy_irq_chip being inserted.
			 */
			अगर (chip != &d->chip)
				जारी;
			अगर (irqd_irq_disabled(data))
				chip->irq_disable(data);
			अन्यथा
				chip->irq_enable(data);
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा syscore_ops पूर्णांकc_syscore_ops = अणु
	.suspend	= पूर्णांकc_suspend,
	.resume		= पूर्णांकc_resume,
पूर्ण;

काष्ठा bus_type पूर्णांकc_subsys = अणु
	.name		= "intc",
	.dev_name	= "intc",
पूर्ण;

अटल sमाप_प्रकार
show_पूर्णांकc_name(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकc_desc_पूर्णांक *d;

	d = container_of(dev, काष्ठा पूर्णांकc_desc_पूर्णांक, dev);

	वापस प्र_लिखो(buf, "%s\n", d->chip.name);
पूर्ण

अटल DEVICE_ATTR(name, S_IRUGO, show_पूर्णांकc_name, शून्य);

अटल पूर्णांक __init रेजिस्टर_पूर्णांकc_devs(व्योम)
अणु
	काष्ठा पूर्णांकc_desc_पूर्णांक *d;
	पूर्णांक error;

	रेजिस्टर_syscore_ops(&पूर्णांकc_syscore_ops);

	error = subsys_प्रणाली_रेजिस्टर(&पूर्णांकc_subsys, शून्य);
	अगर (!error) अणु
		list_क्रम_each_entry(d, &पूर्णांकc_list, list) अणु
			d->dev.id = d->index;
			d->dev.bus = &पूर्णांकc_subsys;
			error = device_रेजिस्टर(&d->dev);
			अगर (error == 0)
				error = device_create_file(&d->dev,
							   &dev_attr_name);
			अगर (error)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (error)
		pr_err("device registration error\n");

	वापस error;
पूर्ण
device_initcall(रेजिस्टर_पूर्णांकc_devs);
