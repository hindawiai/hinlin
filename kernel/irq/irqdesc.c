<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1992, 1998-2006 Linus Torvalds, Ingo Molnar
 * Copyright (C) 2005-2006, Thomas Gleixner, Russell King
 *
 * This file contains the पूर्णांकerrupt descriptor management code. Detailed
 * inक्रमmation is available in Documentation/core-api/genericirq.rst
 *
 */
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/radix-tree.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/sysfs.h>

#समावेश "internals.h"

/*
 * lockdep: we want to handle all irq_desc locks as a single lock-class:
 */
अटल काष्ठा lock_class_key irq_desc_lock_class;

#अगर defined(CONFIG_SMP)
अटल पूर्णांक __init irq_affinity_setup(अक्षर *str)
अणु
	alloc_booपंचांगem_cpumask_var(&irq_शेष_affinity);
	cpulist_parse(str, irq_शेष_affinity);
	/*
	 * Set at least the boot cpu. We करोn't want to end up with
	 * bugreports caused by अक्रमom commandline masks
	 */
	cpumask_set_cpu(smp_processor_id(), irq_शेष_affinity);
	वापस 1;
पूर्ण
__setup("irqaffinity=", irq_affinity_setup);

अटल व्योम __init init_irq_शेष_affinity(व्योम)
अणु
	अगर (!cpumask_available(irq_शेष_affinity))
		zalloc_cpumask_var(&irq_शेष_affinity, GFP_NOWAIT);
	अगर (cpumask_empty(irq_शेष_affinity))
		cpumask_setall(irq_शेष_affinity);
पूर्ण
#अन्यथा
अटल व्योम __init init_irq_शेष_affinity(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक alloc_masks(काष्ठा irq_desc *desc, पूर्णांक node)
अणु
	अगर (!zalloc_cpumask_var_node(&desc->irq_common_data.affinity,
				     GFP_KERNEL, node))
		वापस -ENOMEM;

#अगर_घोषित CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK
	अगर (!zalloc_cpumask_var_node(&desc->irq_common_data.effective_affinity,
				     GFP_KERNEL, node)) अणु
		मुक्त_cpumask_var(desc->irq_common_data.affinity);
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_GENERIC_PENDING_IRQ
	अगर (!zalloc_cpumask_var_node(&desc->pending_mask, GFP_KERNEL, node)) अणु
#अगर_घोषित CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK
		मुक्त_cpumask_var(desc->irq_common_data.effective_affinity);
#पूर्ण_अगर
		मुक्त_cpumask_var(desc->irq_common_data.affinity);
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम desc_smp_init(काष्ठा irq_desc *desc, पूर्णांक node,
			  स्थिर काष्ठा cpumask *affinity)
अणु
	अगर (!affinity)
		affinity = irq_शेष_affinity;
	cpumask_copy(desc->irq_common_data.affinity, affinity);

#अगर_घोषित CONFIG_GENERIC_PENDING_IRQ
	cpumask_clear(desc->pending_mask);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA
	desc->irq_common_data.node = node;
#पूर्ण_अगर
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक
alloc_masks(काष्ठा irq_desc *desc, पूर्णांक node) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम
desc_smp_init(काष्ठा irq_desc *desc, पूर्णांक node, स्थिर काष्ठा cpumask *affinity) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम desc_set_शेषs(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *desc, पूर्णांक node,
			      स्थिर काष्ठा cpumask *affinity, काष्ठा module *owner)
अणु
	पूर्णांक cpu;

	desc->irq_common_data.handler_data = शून्य;
	desc->irq_common_data.msi_desc = शून्य;

	desc->irq_data.common = &desc->irq_common_data;
	desc->irq_data.irq = irq;
	desc->irq_data.chip = &no_irq_chip;
	desc->irq_data.chip_data = शून्य;
	irq_settings_clr_and_set(desc, ~0, _IRQ_DEFAULT_INIT_FLAGS);
	irqd_set(&desc->irq_data, IRQD_IRQ_DISABLED);
	irqd_set(&desc->irq_data, IRQD_IRQ_MASKED);
	desc->handle_irq = handle_bad_irq;
	desc->depth = 1;
	desc->irq_count = 0;
	desc->irqs_unhandled = 0;
	desc->tot_count = 0;
	desc->name = शून्य;
	desc->owner = owner;
	क्रम_each_possible_cpu(cpu)
		*per_cpu_ptr(desc->kstat_irqs, cpu) = 0;
	desc_smp_init(desc, node, affinity);
पूर्ण

पूर्णांक nr_irqs = NR_IRQS;
EXPORT_SYMBOL_GPL(nr_irqs);

अटल DEFINE_MUTEX(sparse_irq_lock);
अटल DECLARE_BITMAP(allocated_irqs, IRQ_BITMAP_BITS);

#अगर_घोषित CONFIG_SPARSE_IRQ

अटल व्योम irq_kobj_release(काष्ठा kobject *kobj);

#अगर_घोषित CONFIG_SYSFS
अटल काष्ठा kobject *irq_kobj_base;

#घोषणा IRQ_ATTR_RO(_name) \
अटल काष्ठा kobj_attribute _name##_attr = __ATTR_RO(_name)

अटल sमाप_प्रकार per_cpu_count_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा irq_desc *desc = container_of(kobj, काष्ठा irq_desc, kobj);
	sमाप_प्रकार ret = 0;
	अक्षर *p = "";
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		अचिन्हित पूर्णांक c = irq_desc_kstat_cpu(desc, cpu);

		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "%s%u", p, c);
		p = ",";
	पूर्ण

	ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "\n");
	वापस ret;
पूर्ण
IRQ_ATTR_RO(per_cpu_count);

अटल sमाप_प्रकार chip_name_show(काष्ठा kobject *kobj,
			      काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा irq_desc *desc = container_of(kobj, काष्ठा irq_desc, kobj);
	sमाप_प्रकार ret = 0;

	raw_spin_lock_irq(&desc->lock);
	अगर (desc->irq_data.chip && desc->irq_data.chip->name) अणु
		ret = scnम_लिखो(buf, PAGE_SIZE, "%s\n",
				desc->irq_data.chip->name);
	पूर्ण
	raw_spin_unlock_irq(&desc->lock);

	वापस ret;
पूर्ण
IRQ_ATTR_RO(chip_name);

अटल sमाप_प्रकार hwirq_show(काष्ठा kobject *kobj,
			  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा irq_desc *desc = container_of(kobj, काष्ठा irq_desc, kobj);
	sमाप_प्रकार ret = 0;

	raw_spin_lock_irq(&desc->lock);
	अगर (desc->irq_data.करोमुख्य)
		ret = प्र_लिखो(buf, "%d\n", (पूर्णांक)desc->irq_data.hwirq);
	raw_spin_unlock_irq(&desc->lock);

	वापस ret;
पूर्ण
IRQ_ATTR_RO(hwirq);

अटल sमाप_प्रकार type_show(काष्ठा kobject *kobj,
			 काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा irq_desc *desc = container_of(kobj, काष्ठा irq_desc, kobj);
	sमाप_प्रकार ret = 0;

	raw_spin_lock_irq(&desc->lock);
	ret = प्र_लिखो(buf, "%s\n",
		      irqd_is_level_type(&desc->irq_data) ? "level" : "edge");
	raw_spin_unlock_irq(&desc->lock);

	वापस ret;

पूर्ण
IRQ_ATTR_RO(type);

अटल sमाप_प्रकार wakeup_show(काष्ठा kobject *kobj,
			   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा irq_desc *desc = container_of(kobj, काष्ठा irq_desc, kobj);
	sमाप_प्रकार ret = 0;

	raw_spin_lock_irq(&desc->lock);
	ret = प्र_लिखो(buf, "%s\n",
		      irqd_is_wakeup_set(&desc->irq_data) ? "enabled" : "disabled");
	raw_spin_unlock_irq(&desc->lock);

	वापस ret;

पूर्ण
IRQ_ATTR_RO(wakeup);

अटल sमाप_प्रकार name_show(काष्ठा kobject *kobj,
			 काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा irq_desc *desc = container_of(kobj, काष्ठा irq_desc, kobj);
	sमाप_प्रकार ret = 0;

	raw_spin_lock_irq(&desc->lock);
	अगर (desc->name)
		ret = scnम_लिखो(buf, PAGE_SIZE, "%s\n", desc->name);
	raw_spin_unlock_irq(&desc->lock);

	वापस ret;
पूर्ण
IRQ_ATTR_RO(name);

अटल sमाप_प्रकार actions_show(काष्ठा kobject *kobj,
			    काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा irq_desc *desc = container_of(kobj, काष्ठा irq_desc, kobj);
	काष्ठा irqaction *action;
	sमाप_प्रकार ret = 0;
	अक्षर *p = "";

	raw_spin_lock_irq(&desc->lock);
	क्रम (action = desc->action; action != शून्य; action = action->next) अणु
		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "%s%s",
				 p, action->name);
		p = ",";
	पूर्ण
	raw_spin_unlock_irq(&desc->lock);

	अगर (ret)
		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "\n");

	वापस ret;
पूर्ण
IRQ_ATTR_RO(actions);

अटल काष्ठा attribute *irq_attrs[] = अणु
	&per_cpu_count_attr.attr,
	&chip_name_attr.attr,
	&hwirq_attr.attr,
	&type_attr.attr,
	&wakeup_attr.attr,
	&name_attr.attr,
	&actions_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(irq);

अटल काष्ठा kobj_type irq_kobj_type = अणु
	.release	= irq_kobj_release,
	.sysfs_ops	= &kobj_sysfs_ops,
	.शेष_groups = irq_groups,
पूर्ण;

अटल व्योम irq_sysfs_add(पूर्णांक irq, काष्ठा irq_desc *desc)
अणु
	अगर (irq_kobj_base) अणु
		/*
		 * Continue even in हाल of failure as this is nothing
		 * crucial.
		 */
		अगर (kobject_add(&desc->kobj, irq_kobj_base, "%d", irq))
			pr_warn("Failed to add kobject for irq %d\n", irq);
	पूर्ण
पूर्ण

अटल व्योम irq_sysfs_del(काष्ठा irq_desc *desc)
अणु
	/*
	 * If irq_sysfs_init() has not yet been invoked (early boot), then
	 * irq_kobj_base is शून्य and the descriptor was never added.
	 * kobject_del() complains about a object with no parent, so make
	 * it conditional.
	 */
	अगर (irq_kobj_base)
		kobject_del(&desc->kobj);
पूर्ण

अटल पूर्णांक __init irq_sysfs_init(व्योम)
अणु
	काष्ठा irq_desc *desc;
	पूर्णांक irq;

	/* Prevent concurrent irq alloc/मुक्त */
	irq_lock_sparse();

	irq_kobj_base = kobject_create_and_add("irq", kernel_kobj);
	अगर (!irq_kobj_base) अणु
		irq_unlock_sparse();
		वापस -ENOMEM;
	पूर्ण

	/* Add the alपढ़ोy allocated पूर्णांकerrupts */
	क्रम_each_irq_desc(irq, desc)
		irq_sysfs_add(irq, desc);
	irq_unlock_sparse();

	वापस 0;
पूर्ण
postcore_initcall(irq_sysfs_init);

#अन्यथा /* !CONFIG_SYSFS */

अटल काष्ठा kobj_type irq_kobj_type = अणु
	.release	= irq_kobj_release,
पूर्ण;

अटल व्योम irq_sysfs_add(पूर्णांक irq, काष्ठा irq_desc *desc) अणुपूर्ण
अटल व्योम irq_sysfs_del(काष्ठा irq_desc *desc) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_SYSFS */

अटल RADIX_TREE(irq_desc_tree, GFP_KERNEL);

अटल व्योम irq_insert_desc(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *desc)
अणु
	radix_tree_insert(&irq_desc_tree, irq, desc);
पूर्ण

काष्ठा irq_desc *irq_to_desc(अचिन्हित पूर्णांक irq)
अणु
	वापस radix_tree_lookup(&irq_desc_tree, irq);
पूर्ण
#अगर_घोषित CONFIG_KVM_BOOK3S_64_HV_MODULE
EXPORT_SYMBOL_GPL(irq_to_desc);
#पूर्ण_अगर

अटल व्योम delete_irq_desc(अचिन्हित पूर्णांक irq)
अणु
	radix_tree_delete(&irq_desc_tree, irq);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम मुक्त_masks(काष्ठा irq_desc *desc)
अणु
#अगर_घोषित CONFIG_GENERIC_PENDING_IRQ
	मुक्त_cpumask_var(desc->pending_mask);
#पूर्ण_अगर
	मुक्त_cpumask_var(desc->irq_common_data.affinity);
#अगर_घोषित CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK
	मुक्त_cpumask_var(desc->irq_common_data.effective_affinity);
#पूर्ण_अगर
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम मुक्त_masks(काष्ठा irq_desc *desc) अणु पूर्ण
#पूर्ण_अगर

व्योम irq_lock_sparse(व्योम)
अणु
	mutex_lock(&sparse_irq_lock);
पूर्ण

व्योम irq_unlock_sparse(व्योम)
अणु
	mutex_unlock(&sparse_irq_lock);
पूर्ण

अटल काष्ठा irq_desc *alloc_desc(पूर्णांक irq, पूर्णांक node, अचिन्हित पूर्णांक flags,
				   स्थिर काष्ठा cpumask *affinity,
				   काष्ठा module *owner)
अणु
	काष्ठा irq_desc *desc;

	desc = kzalloc_node(माप(*desc), GFP_KERNEL, node);
	अगर (!desc)
		वापस शून्य;
	/* allocate based on nr_cpu_ids */
	desc->kstat_irqs = alloc_percpu(अचिन्हित पूर्णांक);
	अगर (!desc->kstat_irqs)
		जाओ err_desc;

	अगर (alloc_masks(desc, node))
		जाओ err_kstat;

	raw_spin_lock_init(&desc->lock);
	lockdep_set_class(&desc->lock, &irq_desc_lock_class);
	mutex_init(&desc->request_mutex);
	init_rcu_head(&desc->rcu);

	desc_set_शेषs(irq, desc, node, affinity, owner);
	irqd_set(&desc->irq_data, flags);
	kobject_init(&desc->kobj, &irq_kobj_type);

	वापस desc;

err_kstat:
	मुक्त_percpu(desc->kstat_irqs);
err_desc:
	kमुक्त(desc);
	वापस शून्य;
पूर्ण

अटल व्योम irq_kobj_release(काष्ठा kobject *kobj)
अणु
	काष्ठा irq_desc *desc = container_of(kobj, काष्ठा irq_desc, kobj);

	मुक्त_masks(desc);
	मुक्त_percpu(desc->kstat_irqs);
	kमुक्त(desc);
पूर्ण

अटल व्योम delayed_मुक्त_desc(काष्ठा rcu_head *rhp)
अणु
	काष्ठा irq_desc *desc = container_of(rhp, काष्ठा irq_desc, rcu);

	kobject_put(&desc->kobj);
पूर्ण

अटल व्योम मुक्त_desc(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);

	irq_हटाओ_debugfs_entry(desc);
	unरेजिस्टर_irq_proc(irq, desc);

	/*
	 * sparse_irq_lock protects also show_पूर्णांकerrupts() and
	 * kstat_irq_usr(). Once we deleted the descriptor from the
	 * sparse tree we can मुक्त it. Access in proc will fail to
	 * lookup the descriptor.
	 *
	 * The sysfs entry must be serialized against a concurrent
	 * irq_sysfs_init() as well.
	 */
	irq_sysfs_del(desc);
	delete_irq_desc(irq);

	/*
	 * We मुक्त the descriptor, masks and stat fields via RCU. That
	 * allows demultiplex पूर्णांकerrupts to करो rcu based management of
	 * the child पूर्णांकerrupts.
	 * This also allows us to use rcu in kstat_irqs_usr().
	 */
	call_rcu(&desc->rcu, delayed_मुक्त_desc);
पूर्ण

अटल पूर्णांक alloc_descs(अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक cnt, पूर्णांक node,
		       स्थिर काष्ठा irq_affinity_desc *affinity,
		       काष्ठा module *owner)
अणु
	काष्ठा irq_desc *desc;
	पूर्णांक i;

	/* Validate affinity mask(s) */
	अगर (affinity) अणु
		क्रम (i = 0; i < cnt; i++) अणु
			अगर (cpumask_empty(&affinity[i].mask))
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < cnt; i++) अणु
		स्थिर काष्ठा cpumask *mask = शून्य;
		अचिन्हित पूर्णांक flags = 0;

		अगर (affinity) अणु
			अगर (affinity->is_managed) अणु
				flags = IRQD_AFFINITY_MANAGED |
					IRQD_MANAGED_SHUTDOWN;
			पूर्ण
			mask = &affinity->mask;
			node = cpu_to_node(cpumask_first(mask));
			affinity++;
		पूर्ण

		desc = alloc_desc(start + i, node, flags, mask, owner);
		अगर (!desc)
			जाओ err;
		irq_insert_desc(start + i, desc);
		irq_sysfs_add(start + i, desc);
		irq_add_debugfs_entry(start + i, desc);
	पूर्ण
	biपंचांगap_set(allocated_irqs, start, cnt);
	वापस start;

err:
	क्रम (i--; i >= 0; i--)
		मुक्त_desc(start + i);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक irq_expand_nr_irqs(अचिन्हित पूर्णांक nr)
अणु
	अगर (nr > IRQ_BITMAP_BITS)
		वापस -ENOMEM;
	nr_irqs = nr;
	वापस 0;
पूर्ण

पूर्णांक __init early_irq_init(व्योम)
अणु
	पूर्णांक i, initcnt, node = first_online_node;
	काष्ठा irq_desc *desc;

	init_irq_शेष_affinity();

	/* Let arch update nr_irqs and वापस the nr of pपुनः_स्मृतिated irqs */
	initcnt = arch_probe_nr_irqs();
	prपूर्णांकk(KERN_INFO "NR_IRQS: %d, nr_irqs: %d, preallocated irqs: %d\n",
	       NR_IRQS, nr_irqs, initcnt);

	अगर (WARN_ON(nr_irqs > IRQ_BITMAP_BITS))
		nr_irqs = IRQ_BITMAP_BITS;

	अगर (WARN_ON(initcnt > IRQ_BITMAP_BITS))
		initcnt = IRQ_BITMAP_BITS;

	अगर (initcnt > nr_irqs)
		nr_irqs = initcnt;

	क्रम (i = 0; i < initcnt; i++) अणु
		desc = alloc_desc(i, node, 0, शून्य, शून्य);
		set_bit(i, allocated_irqs);
		irq_insert_desc(i, desc);
	पूर्ण
	वापस arch_early_irq_init();
पूर्ण

#अन्यथा /* !CONFIG_SPARSE_IRQ */

काष्ठा irq_desc irq_desc[NR_IRQS] __cacheline_aligned_in_smp = अणु
	[0 ... NR_IRQS-1] = अणु
		.handle_irq	= handle_bad_irq,
		.depth		= 1,
		.lock		= __RAW_SPIN_LOCK_UNLOCKED(irq_desc->lock),
	पूर्ण
पूर्ण;

पूर्णांक __init early_irq_init(व्योम)
अणु
	पूर्णांक count, i, node = first_online_node;
	काष्ठा irq_desc *desc;

	init_irq_शेष_affinity();

	prपूर्णांकk(KERN_INFO "NR_IRQS: %d\n", NR_IRQS);

	desc = irq_desc;
	count = ARRAY_SIZE(irq_desc);

	क्रम (i = 0; i < count; i++) अणु
		desc[i].kstat_irqs = alloc_percpu(अचिन्हित पूर्णांक);
		alloc_masks(&desc[i], node);
		raw_spin_lock_init(&desc[i].lock);
		lockdep_set_class(&desc[i].lock, &irq_desc_lock_class);
		mutex_init(&desc[i].request_mutex);
		desc_set_शेषs(i, &desc[i], node, शून्य, शून्य);
	पूर्ण
	वापस arch_early_irq_init();
पूर्ण

काष्ठा irq_desc *irq_to_desc(अचिन्हित पूर्णांक irq)
अणु
	वापस (irq < NR_IRQS) ? irq_desc + irq : शून्य;
पूर्ण
EXPORT_SYMBOL(irq_to_desc);

अटल व्योम मुक्त_desc(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&desc->lock, flags);
	desc_set_शेषs(irq, desc, irq_desc_get_node(desc), शून्य, शून्य);
	raw_spin_unlock_irqrestore(&desc->lock, flags);
पूर्ण

अटल अंतरभूत पूर्णांक alloc_descs(अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक cnt, पूर्णांक node,
			      स्थिर काष्ठा irq_affinity_desc *affinity,
			      काष्ठा module *owner)
अणु
	u32 i;

	क्रम (i = 0; i < cnt; i++) अणु
		काष्ठा irq_desc *desc = irq_to_desc(start + i);

		desc->owner = owner;
	पूर्ण
	biपंचांगap_set(allocated_irqs, start, cnt);
	वापस start;
पूर्ण

अटल पूर्णांक irq_expand_nr_irqs(अचिन्हित पूर्णांक nr)
अणु
	वापस -ENOMEM;
पूर्ण

व्योम irq_mark_irq(अचिन्हित पूर्णांक irq)
अणु
	mutex_lock(&sparse_irq_lock);
	biपंचांगap_set(allocated_irqs, irq, 1);
	mutex_unlock(&sparse_irq_lock);
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IRQ_LEGACY
व्योम irq_init_desc(अचिन्हित पूर्णांक irq)
अणु
	मुक्त_desc(irq);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* !CONFIG_SPARSE_IRQ */

/**
 * generic_handle_irq - Invoke the handler क्रम a particular irq
 * @irq:	The irq number to handle
 *
 */
पूर्णांक generic_handle_irq(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	काष्ठा irq_data *data;

	अगर (!desc)
		वापस -EINVAL;

	data = irq_desc_get_irq_data(desc);
	अगर (WARN_ON_ONCE(!in_irq() && handle_enक्रमce_irqctx(data)))
		वापस -EPERM;

	generic_handle_irq_desc(desc);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(generic_handle_irq);

#अगर_घोषित CONFIG_HANDLE_DOMAIN_IRQ
/**
 * __handle_करोमुख्य_irq - Invoke the handler क्रम a HW irq beदीर्घing to a करोमुख्य
 * @करोमुख्य:	The करोमुख्य where to perक्रमm the lookup
 * @hwirq:	The HW irq number to convert to a logical one
 * @lookup:	Whether to perक्रमm the करोमुख्य lookup or not
 * @regs:	Register file coming from the low-level handling code
 *
 * Returns:	0 on success, or -EINVAL अगर conversion has failed
 */
पूर्णांक __handle_करोमुख्य_irq(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक hwirq,
			bool lookup, काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);
	अचिन्हित पूर्णांक irq = hwirq;
	पूर्णांक ret = 0;

	irq_enter();

#अगर_घोषित CONFIG_IRQ_DOMAIN
	अगर (lookup)
		irq = irq_find_mapping(करोमुख्य, hwirq);
#पूर्ण_अगर

	/*
	 * Some hardware gives अक्रमomly wrong पूर्णांकerrupts.  Rather
	 * than crashing, करो something sensible.
	 */
	अगर (unlikely(!irq || irq >= nr_irqs)) अणु
		ack_bad_irq(irq);
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		generic_handle_irq(irq);
	पूर्ण

	irq_निकास();
	set_irq_regs(old_regs);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_IRQ_DOMAIN
/**
 * handle_करोमुख्य_nmi - Invoke the handler क्रम a HW irq beदीर्घing to a करोमुख्य
 * @करोमुख्य:	The करोमुख्य where to perक्रमm the lookup
 * @hwirq:	The HW irq number to convert to a logical one
 * @regs:	Register file coming from the low-level handling code
 *
 *		This function must be called from an NMI context.
 *
 * Returns:	0 on success, or -EINVAL अगर conversion has failed
 */
पूर्णांक handle_करोमुख्य_nmi(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक hwirq,
		      काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);
	अचिन्हित पूर्णांक irq;
	पूर्णांक ret = 0;

	/*
	 * NMI context needs to be setup earlier in order to deal with tracing.
	 */
	WARN_ON(!in_nmi());

	irq = irq_find_mapping(करोमुख्य, hwirq);

	/*
	 * ack_bad_irq is not NMI-safe, just report
	 * an invalid पूर्णांकerrupt.
	 */
	अगर (likely(irq))
		generic_handle_irq(irq);
	अन्यथा
		ret = -EINVAL;

	set_irq_regs(old_regs);
	वापस ret;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

/* Dynamic पूर्णांकerrupt handling */

/**
 * irq_मुक्त_descs - मुक्त irq descriptors
 * @from:	Start of descriptor range
 * @cnt:	Number of consecutive irqs to मुक्त
 */
व्योम irq_मुक्त_descs(अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक cnt)
अणु
	पूर्णांक i;

	अगर (from >= nr_irqs || (from + cnt) > nr_irqs)
		वापस;

	mutex_lock(&sparse_irq_lock);
	क्रम (i = 0; i < cnt; i++)
		मुक्त_desc(from + i);

	biपंचांगap_clear(allocated_irqs, from, cnt);
	mutex_unlock(&sparse_irq_lock);
पूर्ण
EXPORT_SYMBOL_GPL(irq_मुक्त_descs);

/**
 * __irq_alloc_descs - allocate and initialize a range of irq descriptors
 * @irq:	Allocate क्रम specअगरic irq number अगर irq >= 0
 * @from:	Start the search from this irq number
 * @cnt:	Number of consecutive irqs to allocate.
 * @node:	Preferred node on which the irq descriptor should be allocated
 * @owner:	Owning module (can be शून्य)
 * @affinity:	Optional poपूर्णांकer to an affinity mask array of size @cnt which
 *		hपूर्णांकs where the irq descriptors should be allocated and which
 *		शेष affinities to use
 *
 * Returns the first irq number or error code
 */
पूर्णांक __ref
__irq_alloc_descs(पूर्णांक irq, अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक cnt, पूर्णांक node,
		  काष्ठा module *owner, स्थिर काष्ठा irq_affinity_desc *affinity)
अणु
	पूर्णांक start, ret;

	अगर (!cnt)
		वापस -EINVAL;

	अगर (irq >= 0) अणु
		अगर (from > irq)
			वापस -EINVAL;
		from = irq;
	पूर्ण अन्यथा अणु
		/*
		 * For पूर्णांकerrupts which are मुक्तly allocated the
		 * architecture can क्रमce a lower bound to the @from
		 * argument. x86 uses this to exclude the GSI space.
		 */
		from = arch_dynirq_lower_bound(from);
	पूर्ण

	mutex_lock(&sparse_irq_lock);

	start = biपंचांगap_find_next_zero_area(allocated_irqs, IRQ_BITMAP_BITS,
					   from, cnt, 0);
	ret = -EEXIST;
	अगर (irq >=0 && start != irq)
		जाओ unlock;

	अगर (start + cnt > nr_irqs) अणु
		ret = irq_expand_nr_irqs(start + cnt);
		अगर (ret)
			जाओ unlock;
	पूर्ण
	ret = alloc_descs(start, cnt, node, affinity, owner);
unlock:
	mutex_unlock(&sparse_irq_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__irq_alloc_descs);

/**
 * irq_get_next_irq - get next allocated irq number
 * @offset:	where to start the search
 *
 * Returns next irq number after offset or nr_irqs अगर none is found.
 */
अचिन्हित पूर्णांक irq_get_next_irq(अचिन्हित पूर्णांक offset)
अणु
	वापस find_next_bit(allocated_irqs, nr_irqs, offset);
पूर्ण

काष्ठा irq_desc *
__irq_get_desc_lock(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ *flags, bool bus,
		    अचिन्हित पूर्णांक check)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);

	अगर (desc) अणु
		अगर (check & _IRQ_DESC_CHECK) अणु
			अगर ((check & _IRQ_DESC_PERCPU) &&
			    !irq_settings_is_per_cpu_devid(desc))
				वापस शून्य;

			अगर (!(check & _IRQ_DESC_PERCPU) &&
			    irq_settings_is_per_cpu_devid(desc))
				वापस शून्य;
		पूर्ण

		अगर (bus)
			chip_bus_lock(desc);
		raw_spin_lock_irqsave(&desc->lock, *flags);
	पूर्ण
	वापस desc;
पूर्ण

व्योम __irq_put_desc_unlock(काष्ठा irq_desc *desc, अचिन्हित दीर्घ flags, bool bus)
	__releases(&desc->lock)
अणु
	raw_spin_unlock_irqrestore(&desc->lock, flags);
	अगर (bus)
		chip_bus_sync_unlock(desc);
पूर्ण

पूर्णांक irq_set_percpu_devid_partition(अचिन्हित पूर्णांक irq,
				   स्थिर काष्ठा cpumask *affinity)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);

	अगर (!desc)
		वापस -EINVAL;

	अगर (desc->percpu_enabled)
		वापस -EINVAL;

	desc->percpu_enabled = kzalloc(माप(*desc->percpu_enabled), GFP_KERNEL);

	अगर (!desc->percpu_enabled)
		वापस -ENOMEM;

	अगर (affinity)
		desc->percpu_affinity = affinity;
	अन्यथा
		desc->percpu_affinity = cpu_possible_mask;

	irq_set_percpu_devid_flags(irq);
	वापस 0;
पूर्ण

पूर्णांक irq_set_percpu_devid(अचिन्हित पूर्णांक irq)
अणु
	वापस irq_set_percpu_devid_partition(irq, शून्य);
पूर्ण

पूर्णांक irq_get_percpu_devid_partition(अचिन्हित पूर्णांक irq, काष्ठा cpumask *affinity)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);

	अगर (!desc || !desc->percpu_enabled)
		वापस -EINVAL;

	अगर (affinity)
		cpumask_copy(affinity, desc->percpu_affinity);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(irq_get_percpu_devid_partition);

व्योम kstat_incr_irq_this_cpu(अचिन्हित पूर्णांक irq)
अणु
	kstat_incr_irqs_this_cpu(irq_to_desc(irq));
पूर्ण

/**
 * kstat_irqs_cpu - Get the statistics क्रम an पूर्णांकerrupt on a cpu
 * @irq:	The पूर्णांकerrupt number
 * @cpu:	The cpu number
 *
 * Returns the sum of पूर्णांकerrupt counts on @cpu since boot क्रम
 * @irq. The caller must ensure that the पूर्णांकerrupt is not हटाओd
 * concurrently.
 */
अचिन्हित पूर्णांक kstat_irqs_cpu(अचिन्हित पूर्णांक irq, पूर्णांक cpu)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);

	वापस desc && desc->kstat_irqs ?
			*per_cpu_ptr(desc->kstat_irqs, cpu) : 0;
पूर्ण

अटल bool irq_is_nmi(काष्ठा irq_desc *desc)
अणु
	वापस desc->istate & IRQS_NMI;
पूर्ण

अटल अचिन्हित पूर्णांक kstat_irqs(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	अचिन्हित पूर्णांक sum = 0;
	पूर्णांक cpu;

	अगर (!desc || !desc->kstat_irqs)
		वापस 0;
	अगर (!irq_settings_is_per_cpu_devid(desc) &&
	    !irq_settings_is_per_cpu(desc) &&
	    !irq_is_nmi(desc))
		वापस data_race(desc->tot_count);

	क्रम_each_possible_cpu(cpu)
		sum += data_race(*per_cpu_ptr(desc->kstat_irqs, cpu));
	वापस sum;
पूर्ण

/**
 * kstat_irqs_usr - Get the statistics क्रम an पूर्णांकerrupt from thपढ़ो context
 * @irq:	The पूर्णांकerrupt number
 *
 * Returns the sum of पूर्णांकerrupt counts on all cpus since boot क्रम @irq.
 *
 * It uses rcu to protect the access since a concurrent removal of an
 * पूर्णांकerrupt descriptor is observing an rcu grace period beक्रमe
 * delayed_मुक्त_desc()/irq_kobj_release().
 */
अचिन्हित पूर्णांक kstat_irqs_usr(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक sum;

	rcu_पढ़ो_lock();
	sum = kstat_irqs(irq);
	rcu_पढ़ो_unlock();
	वापस sum;
पूर्ण

#अगर_घोषित CONFIG_LOCKDEP
व्योम __irq_set_lockdep_class(अचिन्हित पूर्णांक irq, काष्ठा lock_class_key *lock_class,
			     काष्ठा lock_class_key *request_class)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);

	अगर (desc) अणु
		lockdep_set_class(&desc->lock, lock_class);
		lockdep_set_class(&desc->request_mutex, request_class);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__irq_set_lockdep_class);
#पूर्ण_अगर
