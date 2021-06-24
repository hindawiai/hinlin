<शैली गुरु>
/*
 * Support क्रम भव IRQ subgroups.
 *
 * Copyright (C) 2010  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#घोषणा pr_fmt(fmt) "intc: " fmt

#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/list.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश "internals.h"

अटल काष्ठा पूर्णांकc_map_entry पूर्णांकc_irq_xlate[INTC_NR_IRQS];

काष्ठा पूर्णांकc_virq_list अणु
	अचिन्हित पूर्णांक irq;
	काष्ठा पूर्णांकc_virq_list *next;
पूर्ण;

#घोषणा क्रम_each_virq(entry, head) \
	क्रम (entry = head; entry; entry = entry->next)

/*
 * Tags क्रम the radix tree
 */
#घोषणा INTC_TAG_VIRQ_NEEDS_ALLOC	0

व्योम पूर्णांकc_irq_xlate_set(अचिन्हित पूर्णांक irq, पूर्णांकc_क्रमागत id, काष्ठा पूर्णांकc_desc_पूर्णांक *d)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&पूर्णांकc_big_lock, flags);
	पूर्णांकc_irq_xlate[irq].क्रमागत_id = id;
	पूर्णांकc_irq_xlate[irq].desc = d;
	raw_spin_unlock_irqrestore(&पूर्णांकc_big_lock, flags);
पूर्ण

काष्ठा पूर्णांकc_map_entry *पूर्णांकc_irq_xlate_get(अचिन्हित पूर्णांक irq)
अणु
	वापस पूर्णांकc_irq_xlate + irq;
पूर्ण

पूर्णांक पूर्णांकc_irq_lookup(स्थिर अक्षर *chipname, पूर्णांकc_क्रमागत क्रमागत_id)
अणु
	काष्ठा पूर्णांकc_map_entry *ptr;
	काष्ठा पूर्णांकc_desc_पूर्णांक *d;
	पूर्णांक irq = -1;

	list_क्रम_each_entry(d, &पूर्णांकc_list, list) अणु
		पूर्णांक tagged;

		अगर (म_भेद(d->chip.name, chipname) != 0)
			जारी;

		/*
		 * Catch early lookups क्रम subgroup VIRQs that have not
		 * yet been allocated an IRQ. This alपढ़ोy includes a
		 * fast-path out अगर the tree is untagged, so there is no
		 * need to explicitly test the root tree.
		 */
		tagged = radix_tree_tag_get(&d->tree, क्रमागत_id,
					    INTC_TAG_VIRQ_NEEDS_ALLOC);
		अगर (unlikely(tagged))
			अवरोध;

		ptr = radix_tree_lookup(&d->tree, क्रमागत_id);
		अगर (ptr) अणु
			irq = ptr - पूर्णांकc_irq_xlate;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस irq;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकc_irq_lookup);

अटल पूर्णांक add_virq_to_pirq(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक virq)
अणु
	काष्ठा पूर्णांकc_virq_list *entry;
	काष्ठा पूर्णांकc_virq_list **last = शून्य;

	/* scan क्रम duplicates */
	क्रम_each_virq(entry, irq_get_handler_data(irq)) अणु
		अगर (entry->irq == virq)
			वापस 0;
		last = &entry->next;
	पूर्ण

	entry = kzalloc(माप(काष्ठा पूर्णांकc_virq_list), GFP_ATOMIC);
	अगर (!entry)
		वापस -ENOMEM;

	entry->irq = virq;

	अगर (last)
		*last = entry;
	अन्यथा
		irq_set_handler_data(irq, entry);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकc_virq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(data);
	काष्ठा पूर्णांकc_virq_list *entry, *vlist = irq_data_get_irq_handler_data(data);
	काष्ठा पूर्णांकc_desc_पूर्णांक *d = get_पूर्णांकc_desc(irq);

	chip->irq_mask_ack(data);

	क्रम_each_virq(entry, vlist) अणु
		अचिन्हित दीर्घ addr, handle;
		काष्ठा irq_desc *vdesc = irq_to_desc(entry->irq);

		अगर (vdesc) अणु
			handle = (अचिन्हित दीर्घ)irq_desc_get_handler_data(vdesc);
			addr = INTC_REG(d, _INTC_ADDR_E(handle), 0);
			अगर (पूर्णांकc_reg_fns[_INTC_FN(handle)](addr, handle, 0))
				generic_handle_irq_desc(vdesc);
		पूर्ण
	पूर्ण

	chip->irq_unmask(data);
पूर्ण

अटल अचिन्हित दीर्घ __init पूर्णांकc_subgroup_data(काष्ठा पूर्णांकc_subgroup *subgroup,
					       काष्ठा पूर्णांकc_desc_पूर्णांक *d,
					       अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक fn = REG_FN_TEST_BASE + (subgroup->reg_width >> 3) - 1;

	वापस _INTC_MK(fn, MODE_ENABLE_REG, पूर्णांकc_get_reg(d, subgroup->reg),
			0, 1, (subgroup->reg_width - 1) - index);
पूर्ण

अटल व्योम __init पूर्णांकc_subgroup_init_one(काष्ठा पूर्णांकc_desc *desc,
					  काष्ठा पूर्णांकc_desc_पूर्णांक *d,
					  काष्ठा पूर्णांकc_subgroup *subgroup)
अणु
	काष्ठा पूर्णांकc_map_entry *mapped;
	अचिन्हित पूर्णांक pirq;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	mapped = radix_tree_lookup(&d->tree, subgroup->parent_id);
	अगर (!mapped) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	pirq = mapped - पूर्णांकc_irq_xlate;

	raw_spin_lock_irqsave(&d->lock, flags);

	क्रम (i = 0; i < ARRAY_SIZE(subgroup->क्रमागत_ids); i++) अणु
		काष्ठा पूर्णांकc_subgroup_entry *entry;
		पूर्णांक err;

		अगर (!subgroup->क्रमागत_ids[i])
			जारी;

		entry = kदो_स्मृति(माप(*entry), GFP_NOWAIT);
		अगर (!entry)
			अवरोध;

		entry->pirq = pirq;
		entry->क्रमागत_id = subgroup->क्रमागत_ids[i];
		entry->handle = पूर्णांकc_subgroup_data(subgroup, d, i);

		err = radix_tree_insert(&d->tree, entry->क्रमागत_id, entry);
		अगर (unlikely(err < 0))
			अवरोध;

		radix_tree_tag_set(&d->tree, entry->क्रमागत_id,
				   INTC_TAG_VIRQ_NEEDS_ALLOC);
	पूर्ण

	raw_spin_unlock_irqrestore(&d->lock, flags);
पूर्ण

व्योम __init पूर्णांकc_subgroup_init(काष्ठा पूर्णांकc_desc *desc, काष्ठा पूर्णांकc_desc_पूर्णांक *d)
अणु
	पूर्णांक i;

	अगर (!desc->hw.subgroups)
		वापस;

	क्रम (i = 0; i < desc->hw.nr_subgroups; i++)
		पूर्णांकc_subgroup_init_one(desc, d, desc->hw.subgroups + i);
पूर्ण

अटल व्योम __init पूर्णांकc_subgroup_map(काष्ठा पूर्णांकc_desc_पूर्णांक *d)
अणु
	काष्ठा पूर्णांकc_subgroup_entry *entries[32];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक nr_found;
	पूर्णांक i;

	raw_spin_lock_irqsave(&d->lock, flags);

restart:
	nr_found = radix_tree_gang_lookup_tag_slot(&d->tree,
			(व्योम ***)entries, 0, ARRAY_SIZE(entries),
			INTC_TAG_VIRQ_NEEDS_ALLOC);

	क्रम (i = 0; i < nr_found; i++) अणु
		काष्ठा पूर्णांकc_subgroup_entry *entry;
		पूर्णांक irq;

		entry = radix_tree_deref_slot((व्योम **)entries[i]);
		अगर (unlikely(!entry))
			जारी;
		अगर (radix_tree_deref_retry(entry))
			जाओ restart;

		irq = irq_alloc_desc(numa_node_id());
		अगर (unlikely(irq < 0)) अणु
			pr_err("no more free IRQs, bailing..\n");
			अवरोध;
		पूर्ण

		activate_irq(irq);

		pr_info("Setting up a chained VIRQ from %d -> %d\n",
			irq, entry->pirq);

		पूर्णांकc_irq_xlate_set(irq, entry->क्रमागत_id, d);

		irq_set_chip_and_handler_name(irq, irq_get_chip(entry->pirq),
					      handle_simple_irq, "virq");
		irq_set_chip_data(irq, irq_get_chip_data(entry->pirq));

		irq_set_handler_data(irq, (व्योम *)entry->handle);

		/*
		 * Set the भव IRQ as non-thपढ़ोable.
		 */
		irq_set_nothपढ़ो(irq);

		/* Set handler data beक्रमe installing the handler */
		add_virq_to_pirq(entry->pirq, irq);
		irq_set_chained_handler(entry->pirq, पूर्णांकc_virq_handler);

		radix_tree_tag_clear(&d->tree, entry->क्रमागत_id,
				     INTC_TAG_VIRQ_NEEDS_ALLOC);
		radix_tree_replace_slot(&d->tree, (व्योम **)entries[i],
					&पूर्णांकc_irq_xlate[irq]);
	पूर्ण

	raw_spin_unlock_irqrestore(&d->lock, flags);
पूर्ण

व्योम __init पूर्णांकc_finalize(व्योम)
अणु
	काष्ठा पूर्णांकc_desc_पूर्णांक *d;

	list_क्रम_each_entry(d, &पूर्णांकc_list, list)
		अगर (radix_tree_tagged(&d->tree, INTC_TAG_VIRQ_NEEDS_ALLOC))
			पूर्णांकc_subgroup_map(d);
पूर्ण
