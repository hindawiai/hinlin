<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright 2017 Thomas Gleixner <tglx@linutronix.de>

#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/uaccess.h>

#समावेश "internals.h"

अटल काष्ठा dentry *irq_dir;

काष्ठा irq_bit_descr अणु
	अचिन्हित पूर्णांक	mask;
	अक्षर		*name;
पूर्ण;
#घोषणा BIT_MASK_DESCR(m)	अणु .mask = m, .name = #m पूर्ण

अटल व्योम irq_debug_show_bits(काष्ठा seq_file *m, पूर्णांक ind, अचिन्हित पूर्णांक state,
				स्थिर काष्ठा irq_bit_descr *sd, पूर्णांक size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++, sd++) अणु
		अगर (state & sd->mask)
			seq_म_लिखो(m, "%*s%s\n", ind + 12, "", sd->name);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम irq_debug_show_masks(काष्ठा seq_file *m, काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
	काष्ठा cpumask *msk;

	msk = irq_data_get_affinity_mask(data);
	seq_म_लिखो(m, "affinity: %*pbl\n", cpumask_pr_args(msk));
#अगर_घोषित CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK
	msk = irq_data_get_effective_affinity_mask(data);
	seq_म_लिखो(m, "effectiv: %*pbl\n", cpumask_pr_args(msk));
#पूर्ण_अगर
#अगर_घोषित CONFIG_GENERIC_PENDING_IRQ
	msk = desc->pending_mask;
	seq_म_लिखो(m, "pending:  %*pbl\n", cpumask_pr_args(msk));
#पूर्ण_अगर
पूर्ण
#अन्यथा
अटल व्योम irq_debug_show_masks(काष्ठा seq_file *m, काष्ठा irq_desc *desc) अणु पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा irq_bit_descr irqchip_flags[] = अणु
	BIT_MASK_DESCR(IRQCHIP_SET_TYPE_MASKED),
	BIT_MASK_DESCR(IRQCHIP_EOI_IF_HANDLED),
	BIT_MASK_DESCR(IRQCHIP_MASK_ON_SUSPEND),
	BIT_MASK_DESCR(IRQCHIP_ONOFFLINE_ENABLED),
	BIT_MASK_DESCR(IRQCHIP_SKIP_SET_WAKE),
	BIT_MASK_DESCR(IRQCHIP_ONESHOT_SAFE),
	BIT_MASK_DESCR(IRQCHIP_EOI_THREADED),
	BIT_MASK_DESCR(IRQCHIP_SUPPORTS_LEVEL_MSI),
	BIT_MASK_DESCR(IRQCHIP_SUPPORTS_NMI),
	BIT_MASK_DESCR(IRQCHIP_ENABLE_WAKEUP_ON_SUSPEND),
पूर्ण;

अटल व्योम
irq_debug_show_chip(काष्ठा seq_file *m, काष्ठा irq_data *data, पूर्णांक ind)
अणु
	काष्ठा irq_chip *chip = data->chip;

	अगर (!chip) अणु
		seq_म_लिखो(m, "chip: None\n");
		वापस;
	पूर्ण
	seq_म_लिखो(m, "%*schip:    %s\n", ind, "", chip->name);
	seq_म_लिखो(m, "%*sflags:   0x%lx\n", ind + 1, "", chip->flags);
	irq_debug_show_bits(m, ind, chip->flags, irqchip_flags,
			    ARRAY_SIZE(irqchip_flags));
पूर्ण

अटल व्योम
irq_debug_show_data(काष्ठा seq_file *m, काष्ठा irq_data *data, पूर्णांक ind)
अणु
	seq_म_लिखो(m, "%*sdomain:  %s\n", ind, "",
		   data->करोमुख्य ? data->करोमुख्य->name : "");
	seq_म_लिखो(m, "%*shwirq:   0x%lx\n", ind + 1, "", data->hwirq);
	irq_debug_show_chip(m, data, ind + 1);
	अगर (data->करोमुख्य && data->करोमुख्य->ops && data->करोमुख्य->ops->debug_show)
		data->करोमुख्य->ops->debug_show(m, शून्य, data, ind + 1);
#अगर_घोषित	CONFIG_IRQ_DOMAIN_HIERARCHY
	अगर (!data->parent_data)
		वापस;
	seq_म_लिखो(m, "%*sparent:\n", ind + 1, "");
	irq_debug_show_data(m, data->parent_data, ind + 4);
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा irq_bit_descr irqdata_states[] = अणु
	BIT_MASK_DESCR(IRQ_TYPE_EDGE_RISING),
	BIT_MASK_DESCR(IRQ_TYPE_EDGE_FALLING),
	BIT_MASK_DESCR(IRQ_TYPE_LEVEL_HIGH),
	BIT_MASK_DESCR(IRQ_TYPE_LEVEL_LOW),
	BIT_MASK_DESCR(IRQD_LEVEL),

	BIT_MASK_DESCR(IRQD_ACTIVATED),
	BIT_MASK_DESCR(IRQD_IRQ_STARTED),
	BIT_MASK_DESCR(IRQD_IRQ_DISABLED),
	BIT_MASK_DESCR(IRQD_IRQ_MASKED),
	BIT_MASK_DESCR(IRQD_IRQ_INPROGRESS),

	BIT_MASK_DESCR(IRQD_PER_CPU),
	BIT_MASK_DESCR(IRQD_NO_BALANCING),

	BIT_MASK_DESCR(IRQD_SINGLE_TARGET),
	BIT_MASK_DESCR(IRQD_MOVE_PCNTXT),
	BIT_MASK_DESCR(IRQD_AFFINITY_SET),
	BIT_MASK_DESCR(IRQD_SETAFFINITY_PENDING),
	BIT_MASK_DESCR(IRQD_AFFINITY_MANAGED),
	BIT_MASK_DESCR(IRQD_AFFINITY_ON_ACTIVATE),
	BIT_MASK_DESCR(IRQD_MANAGED_SHUTDOWN),
	BIT_MASK_DESCR(IRQD_CAN_RESERVE),
	BIT_MASK_DESCR(IRQD_MSI_NOMASK_QUIRK),

	BIT_MASK_DESCR(IRQD_FORWARDED_TO_VCPU),

	BIT_MASK_DESCR(IRQD_WAKEUP_STATE),
	BIT_MASK_DESCR(IRQD_WAKEUP_ARMED),

	BIT_MASK_DESCR(IRQD_DEFAULT_TRIGGER_SET),

	BIT_MASK_DESCR(IRQD_HANDLE_ENFORCE_IRQCTX),

	BIT_MASK_DESCR(IRQD_IRQ_ENABLED_ON_SUSPEND),
पूर्ण;

अटल स्थिर काष्ठा irq_bit_descr irqdesc_states[] = अणु
	BIT_MASK_DESCR(_IRQ_NOPROBE),
	BIT_MASK_DESCR(_IRQ_NOREQUEST),
	BIT_MASK_DESCR(_IRQ_NOTHREAD),
	BIT_MASK_DESCR(_IRQ_NOAUTOEN),
	BIT_MASK_DESCR(_IRQ_NESTED_THREAD),
	BIT_MASK_DESCR(_IRQ_PER_CPU_DEVID),
	BIT_MASK_DESCR(_IRQ_IS_POLLED),
	BIT_MASK_DESCR(_IRQ_DISABLE_UNLAZY),
	BIT_MASK_DESCR(_IRQ_HIDDEN),
पूर्ण;

अटल स्थिर काष्ठा irq_bit_descr irqdesc_istates[] = अणु
	BIT_MASK_DESCR(IRQS_AUTODETECT),
	BIT_MASK_DESCR(IRQS_SPURIOUS_DISABLED),
	BIT_MASK_DESCR(IRQS_POLL_INPROGRESS),
	BIT_MASK_DESCR(IRQS_ONESHOT),
	BIT_MASK_DESCR(IRQS_REPLAY),
	BIT_MASK_DESCR(IRQS_WAITING),
	BIT_MASK_DESCR(IRQS_PENDING),
	BIT_MASK_DESCR(IRQS_SUSPENDED),
	BIT_MASK_DESCR(IRQS_NMI),
पूर्ण;


अटल पूर्णांक irq_debug_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा irq_desc *desc = m->निजी;
	काष्ठा irq_data *data;

	raw_spin_lock_irq(&desc->lock);
	data = irq_desc_get_irq_data(desc);
	seq_म_लिखो(m, "handler:  %ps\n", desc->handle_irq);
	seq_म_लिखो(m, "device:   %s\n", desc->dev_name);
	seq_म_लिखो(m, "status:   0x%08x\n", desc->status_use_accessors);
	irq_debug_show_bits(m, 0, desc->status_use_accessors, irqdesc_states,
			    ARRAY_SIZE(irqdesc_states));
	seq_म_लिखो(m, "istate:   0x%08x\n", desc->istate);
	irq_debug_show_bits(m, 0, desc->istate, irqdesc_istates,
			    ARRAY_SIZE(irqdesc_istates));
	seq_म_लिखो(m, "ddepth:   %u\n", desc->depth);
	seq_म_लिखो(m, "wdepth:   %u\n", desc->wake_depth);
	seq_म_लिखो(m, "dstate:   0x%08x\n", irqd_get(data));
	irq_debug_show_bits(m, 0, irqd_get(data), irqdata_states,
			    ARRAY_SIZE(irqdata_states));
	seq_म_लिखो(m, "node:     %d\n", irq_data_get_node(data));
	irq_debug_show_masks(m, desc);
	irq_debug_show_data(m, data, 0);
	raw_spin_unlock_irq(&desc->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक irq_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, irq_debug_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार irq_debug_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा irq_desc *desc = file_inode(file)->i_निजी;
	अक्षर buf[8] = अणु 0, पूर्ण;
	माप_प्रकार size;

	size = min(माप(buf) - 1, count);
	अगर (copy_from_user(buf, user_buf, size))
		वापस -EFAULT;

	अगर (!म_भेदन(buf, "trigger", size)) अणु
		पूर्णांक err = irq_inject_पूर्णांकerrupt(irq_desc_get_irq(desc));

		वापस err ? err : count;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations dfs_irq_ops = अणु
	.खोलो		= irq_debug_खोलो,
	.ग_लिखो		= irq_debug_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

व्योम irq_debugfs_copy_devname(पूर्णांक irq, काष्ठा device *dev)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	स्थिर अक्षर *name = dev_name(dev);

	अगर (name)
		desc->dev_name = kstrdup(name, GFP_KERNEL);
पूर्ण

व्योम irq_add_debugfs_entry(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *desc)
अणु
	अक्षर name [10];

	अगर (!irq_dir || !desc || desc->debugfs_file)
		वापस;

	प्र_लिखो(name, "%d", irq);
	desc->debugfs_file = debugfs_create_file(name, 0644, irq_dir, desc,
						 &dfs_irq_ops);
पूर्ण

अटल पूर्णांक __init irq_debugfs_init(व्योम)
अणु
	काष्ठा dentry *root_dir;
	पूर्णांक irq;

	root_dir = debugfs_create_dir("irq", शून्य);

	irq_करोमुख्य_debugfs_init(root_dir);

	irq_dir = debugfs_create_dir("irqs", root_dir);

	irq_lock_sparse();
	क्रम_each_active_irq(irq)
		irq_add_debugfs_entry(irq, irq_to_desc(irq));
	irq_unlock_sparse();

	वापस 0;
पूर्ण
__initcall(irq_debugfs_init);
