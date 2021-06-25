<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1992, 1998-2004 Linus Torvalds, Ingo Molnar
 *
 * This file contains the /proc/irq/ handling code.
 */

#समावेश <linux/irq.h>
#समावेश <linux/gfp.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/mutex.h>

#समावेश "internals.h"

/*
 * Access rules:
 *
 * procfs protects पढ़ो/ग_लिखो of /proc/irq/N/ files against a
 * concurrent मुक्त of the पूर्णांकerrupt descriptor. हटाओ_proc_entry()
 * immediately prevents new पढ़ो/ग_लिखोs to happen and रुकोs क्रम
 * alपढ़ोy running पढ़ो/ग_लिखो functions to complete.
 *
 * We हटाओ the proc entries first and then delete the पूर्णांकerrupt
 * descriptor from the radix tree and मुक्त it. So it is guaranteed
 * that irq_to_desc(N) is valid as दीर्घ as the पढ़ो/ग_लिखोs are
 * permitted by procfs.
 *
 * The पढ़ो from /proc/पूर्णांकerrupts is a dअगरferent problem because there
 * is no protection. So the lookup and the access to irqdesc
 * inक्रमmation must be रक्षित by sparse_irq_lock.
 */
अटल काष्ठा proc_dir_entry *root_irq_dir;

#अगर_घोषित CONFIG_SMP

क्रमागत अणु
	AFFINITY,
	AFFINITY_LIST,
	EFFECTIVE,
	EFFECTIVE_LIST,
पूर्ण;

अटल पूर्णांक show_irq_affinity(पूर्णांक type, काष्ठा seq_file *m)
अणु
	काष्ठा irq_desc *desc = irq_to_desc((दीर्घ)m->निजी);
	स्थिर काष्ठा cpumask *mask;

	चयन (type) अणु
	हाल AFFINITY:
	हाल AFFINITY_LIST:
		mask = desc->irq_common_data.affinity;
#अगर_घोषित CONFIG_GENERIC_PENDING_IRQ
		अगर (irqd_is_setaffinity_pending(&desc->irq_data))
			mask = desc->pending_mask;
#पूर्ण_अगर
		अवरोध;
	हाल EFFECTIVE:
	हाल EFFECTIVE_LIST:
#अगर_घोषित CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK
		mask = irq_data_get_effective_affinity_mask(&desc->irq_data);
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (type) अणु
	हाल AFFINITY_LIST:
	हाल EFFECTIVE_LIST:
		seq_म_लिखो(m, "%*pbl\n", cpumask_pr_args(mask));
		अवरोध;
	हाल AFFINITY:
	हाल EFFECTIVE:
		seq_म_लिखो(m, "%*pb\n", cpumask_pr_args(mask));
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक irq_affinity_hपूर्णांक_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा irq_desc *desc = irq_to_desc((दीर्घ)m->निजी);
	अचिन्हित दीर्घ flags;
	cpumask_var_t mask;

	अगर (!zalloc_cpumask_var(&mask, GFP_KERNEL))
		वापस -ENOMEM;

	raw_spin_lock_irqsave(&desc->lock, flags);
	अगर (desc->affinity_hपूर्णांक)
		cpumask_copy(mask, desc->affinity_hपूर्णांक);
	raw_spin_unlock_irqrestore(&desc->lock, flags);

	seq_म_लिखो(m, "%*pb\n", cpumask_pr_args(mask));
	मुक्त_cpumask_var(mask);

	वापस 0;
पूर्ण

पूर्णांक no_irq_affinity;
अटल पूर्णांक irq_affinity_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस show_irq_affinity(AFFINITY, m);
पूर्ण

अटल पूर्णांक irq_affinity_list_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस show_irq_affinity(AFFINITY_LIST, m);
पूर्ण

#अगर_अघोषित CONFIG_AUTO_IRQ_AFFINITY
अटल अंतरभूत पूर्णांक irq_select_affinity_usr(अचिन्हित पूर्णांक irq)
अणु
	/*
	 * If the पूर्णांकerrupt is started up alपढ़ोy then this fails. The
	 * पूर्णांकerrupt is asचिन्हित to an online CPU alपढ़ोy. There is no
	 * poपूर्णांक to move it around अक्रमomly. Tell user space that the
	 * selected mask is bogus.
	 *
	 * If not then any change to the affinity is poपूर्णांकless because the
	 * startup code invokes irq_setup_affinity() which will select
	 * a online CPU anyway.
	 */
	वापस -EINVAL;
पूर्ण
#अन्यथा
/* ALPHA magic affinity स्वतः selector. Keep it क्रम historical reasons. */
अटल अंतरभूत पूर्णांक irq_select_affinity_usr(अचिन्हित पूर्णांक irq)
अणु
	वापस irq_select_affinity(irq);
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार ग_लिखो_irq_affinity(पूर्णांक type, काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	अचिन्हित पूर्णांक irq = (पूर्णांक)(दीर्घ)PDE_DATA(file_inode(file));
	cpumask_var_t new_value;
	पूर्णांक err;

	अगर (!irq_can_set_affinity_usr(irq) || no_irq_affinity)
		वापस -EIO;

	अगर (!zalloc_cpumask_var(&new_value, GFP_KERNEL))
		वापस -ENOMEM;

	अगर (type)
		err = cpumask_parselist_user(buffer, count, new_value);
	अन्यथा
		err = cpumask_parse_user(buffer, count, new_value);
	अगर (err)
		जाओ मुक्त_cpumask;

	/*
	 * Do not allow disabling IRQs completely - it's a too easy
	 * way to make the प्रणाली unusable accidentally :-) At least
	 * one online CPU still has to be targeted.
	 */
	अगर (!cpumask_पूर्णांकersects(new_value, cpu_online_mask)) अणु
		/*
		 * Special हाल क्रम empty set - allow the architecture code
		 * to set शेष SMP affinity.
		 */
		err = irq_select_affinity_usr(irq) ? -EINVAL : count;
	पूर्ण अन्यथा अणु
		err = irq_set_affinity(irq, new_value);
		अगर (!err)
			err = count;
	पूर्ण

मुक्त_cpumask:
	मुक्त_cpumask_var(new_value);
	वापस err;
पूर्ण

अटल sमाप_प्रकार irq_affinity_proc_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	वापस ग_लिखो_irq_affinity(0, file, buffer, count, pos);
पूर्ण

अटल sमाप_प्रकार irq_affinity_list_proc_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	वापस ग_लिखो_irq_affinity(1, file, buffer, count, pos);
पूर्ण

अटल पूर्णांक irq_affinity_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, irq_affinity_proc_show, PDE_DATA(inode));
पूर्ण

अटल पूर्णांक irq_affinity_list_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, irq_affinity_list_proc_show, PDE_DATA(inode));
पूर्ण

अटल स्थिर काष्ठा proc_ops irq_affinity_proc_ops = अणु
	.proc_खोलो	= irq_affinity_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= irq_affinity_proc_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा proc_ops irq_affinity_list_proc_ops = अणु
	.proc_खोलो	= irq_affinity_list_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= irq_affinity_list_proc_ग_लिखो,
पूर्ण;

#अगर_घोषित CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK
अटल पूर्णांक irq_effective_aff_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस show_irq_affinity(EFFECTIVE, m);
पूर्ण

अटल पूर्णांक irq_effective_aff_list_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस show_irq_affinity(EFFECTIVE_LIST, m);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक शेष_affinity_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%*pb\n", cpumask_pr_args(irq_शेष_affinity));
	वापस 0;
पूर्ण

अटल sमाप_प्रकार शेष_affinity_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	cpumask_var_t new_value;
	पूर्णांक err;

	अगर (!zalloc_cpumask_var(&new_value, GFP_KERNEL))
		वापस -ENOMEM;

	err = cpumask_parse_user(buffer, count, new_value);
	अगर (err)
		जाओ out;

	/*
	 * Do not allow disabling IRQs completely - it's a too easy
	 * way to make the प्रणाली unusable accidentally :-) At least
	 * one online CPU still has to be targeted.
	 */
	अगर (!cpumask_पूर्णांकersects(new_value, cpu_online_mask)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	cpumask_copy(irq_शेष_affinity, new_value);
	err = count;

out:
	मुक्त_cpumask_var(new_value);
	वापस err;
पूर्ण

अटल पूर्णांक शेष_affinity_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, शेष_affinity_show, PDE_DATA(inode));
पूर्ण

अटल स्थिर काष्ठा proc_ops शेष_affinity_proc_ops = अणु
	.proc_खोलो	= शेष_affinity_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= शेष_affinity_ग_लिखो,
पूर्ण;

अटल पूर्णांक irq_node_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा irq_desc *desc = irq_to_desc((दीर्घ) m->निजी);

	seq_म_लिखो(m, "%d\n", irq_desc_get_node(desc));
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक irq_spurious_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा irq_desc *desc = irq_to_desc((दीर्घ) m->निजी);

	seq_म_लिखो(m, "count %u\n" "unhandled %u\n" "last_unhandled %u ms\n",
		   desc->irq_count, desc->irqs_unhandled,
		   jअगरfies_to_msecs(desc->last_unhandled));
	वापस 0;
पूर्ण

#घोषणा MAX_NAMELEN 128

अटल पूर्णांक name_unique(अचिन्हित पूर्णांक irq, काष्ठा irqaction *new_action)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	काष्ठा irqaction *action;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 1;

	raw_spin_lock_irqsave(&desc->lock, flags);
	क्रम_each_action_of_desc(desc, action) अणु
		अगर ((action != new_action) && action->name &&
				!म_भेद(new_action->name, action->name)) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&desc->lock, flags);
	वापस ret;
पूर्ण

व्योम रेजिस्टर_handler_proc(अचिन्हित पूर्णांक irq, काष्ठा irqaction *action)
अणु
	अक्षर name [MAX_NAMELEN];
	काष्ठा irq_desc *desc = irq_to_desc(irq);

	अगर (!desc->dir || action->dir || !action->name ||
					!name_unique(irq, action))
		वापस;

	snम_लिखो(name, MAX_NAMELEN, "%s", action->name);

	/* create /proc/irq/1234/handler/ */
	action->dir = proc_सूची_गढ़ो(name, desc->dir);
पूर्ण

#अघोषित MAX_NAMELEN

#घोषणा MAX_NAMELEN 10

व्योम रेजिस्टर_irq_proc(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *desc)
अणु
	अटल DEFINE_MUTEX(रेजिस्टर_lock);
	व्योम __maybe_unused *irqp = (व्योम *)(अचिन्हित दीर्घ) irq;
	अक्षर name [MAX_NAMELEN];

	अगर (!root_irq_dir || (desc->irq_data.chip == &no_irq_chip))
		वापस;

	/*
	 * irq directories are रेजिस्टरed only when a handler is
	 * added, not when the descriptor is created, so multiple
	 * tasks might try to रेजिस्टर at the same समय.
	 */
	mutex_lock(&रेजिस्टर_lock);

	अगर (desc->dir)
		जाओ out_unlock;

	प्र_लिखो(name, "%d", irq);

	/* create /proc/irq/1234 */
	desc->dir = proc_सूची_गढ़ो(name, root_irq_dir);
	अगर (!desc->dir)
		जाओ out_unlock;

#अगर_घोषित CONFIG_SMP
	/* create /proc/irq/<irq>/smp_affinity */
	proc_create_data("smp_affinity", 0644, desc->dir,
			 &irq_affinity_proc_ops, irqp);

	/* create /proc/irq/<irq>/affinity_hपूर्णांक */
	proc_create_single_data("affinity_hint", 0444, desc->dir,
			irq_affinity_hपूर्णांक_proc_show, irqp);

	/* create /proc/irq/<irq>/smp_affinity_list */
	proc_create_data("smp_affinity_list", 0644, desc->dir,
			 &irq_affinity_list_proc_ops, irqp);

	proc_create_single_data("node", 0444, desc->dir, irq_node_proc_show,
			irqp);
# अगरdef CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK
	proc_create_single_data("effective_affinity", 0444, desc->dir,
			irq_effective_aff_proc_show, irqp);
	proc_create_single_data("effective_affinity_list", 0444, desc->dir,
			irq_effective_aff_list_proc_show, irqp);
# endअगर
#पूर्ण_अगर
	proc_create_single_data("spurious", 0444, desc->dir,
			irq_spurious_proc_show, (व्योम *)(दीर्घ)irq);

out_unlock:
	mutex_unlock(&रेजिस्टर_lock);
पूर्ण

व्योम unरेजिस्टर_irq_proc(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *desc)
अणु
	अक्षर name [MAX_NAMELEN];

	अगर (!root_irq_dir || !desc->dir)
		वापस;
#अगर_घोषित CONFIG_SMP
	हटाओ_proc_entry("smp_affinity", desc->dir);
	हटाओ_proc_entry("affinity_hint", desc->dir);
	हटाओ_proc_entry("smp_affinity_list", desc->dir);
	हटाओ_proc_entry("node", desc->dir);
# अगरdef CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK
	हटाओ_proc_entry("effective_affinity", desc->dir);
	हटाओ_proc_entry("effective_affinity_list", desc->dir);
# endअगर
#पूर्ण_अगर
	हटाओ_proc_entry("spurious", desc->dir);

	प्र_लिखो(name, "%u", irq);
	हटाओ_proc_entry(name, root_irq_dir);
पूर्ण

#अघोषित MAX_NAMELEN

व्योम unरेजिस्टर_handler_proc(अचिन्हित पूर्णांक irq, काष्ठा irqaction *action)
अणु
	proc_हटाओ(action->dir);
पूर्ण

अटल व्योम रेजिस्टर_शेष_affinity_proc(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	proc_create("irq/default_smp_affinity", 0644, शून्य,
		    &शेष_affinity_proc_ops);
#पूर्ण_अगर
पूर्ण

व्योम init_irq_proc(व्योम)
अणु
	अचिन्हित पूर्णांक irq;
	काष्ठा irq_desc *desc;

	/* create /proc/irq */
	root_irq_dir = proc_सूची_गढ़ो("irq", शून्य);
	अगर (!root_irq_dir)
		वापस;

	रेजिस्टर_शेष_affinity_proc();

	/*
	 * Create entries क्रम all existing IRQs.
	 */
	क्रम_each_irq_desc(irq, desc)
		रेजिस्टर_irq_proc(irq, desc);
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IRQ_SHOW

पूर्णांक __weak arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	वापस 0;
पूर्ण

#अगर_अघोषित ACTUAL_NR_IRQS
# define ACTUAL_NR_IRQS nr_irqs
#पूर्ण_अगर

पूर्णांक show_पूर्णांकerrupts(काष्ठा seq_file *p, व्योम *v)
अणु
	अटल पूर्णांक prec;

	अचिन्हित दीर्घ flags, any_count = 0;
	पूर्णांक i = *(loff_t *) v, j;
	काष्ठा irqaction *action;
	काष्ठा irq_desc *desc;

	अगर (i > ACTUAL_NR_IRQS)
		वापस 0;

	अगर (i == ACTUAL_NR_IRQS)
		वापस arch_show_पूर्णांकerrupts(p, prec);

	/* prपूर्णांक header and calculate the width of the first column */
	अगर (i == 0) अणु
		क्रम (prec = 3, j = 1000; prec < 10 && j <= nr_irqs; ++prec)
			j *= 10;

		seq_म_लिखो(p, "%*s", prec + 8, "");
		क्रम_each_online_cpu(j)
			seq_म_लिखो(p, "CPU%-8d", j);
		seq_अ_दो(p, '\n');
	पूर्ण

	rcu_पढ़ो_lock();
	desc = irq_to_desc(i);
	अगर (!desc || irq_settings_is_hidden(desc))
		जाओ outsparse;

	अगर (desc->kstat_irqs) अणु
		क्रम_each_online_cpu(j)
			any_count |= data_race(*per_cpu_ptr(desc->kstat_irqs, j));
	पूर्ण

	अगर ((!desc->action || irq_desc_is_chained(desc)) && !any_count)
		जाओ outsparse;

	seq_म_लिखो(p, "%*d: ", prec, i);
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", desc->kstat_irqs ?
					*per_cpu_ptr(desc->kstat_irqs, j) : 0);

	raw_spin_lock_irqsave(&desc->lock, flags);
	अगर (desc->irq_data.chip) अणु
		अगर (desc->irq_data.chip->irq_prपूर्णांक_chip)
			desc->irq_data.chip->irq_prपूर्णांक_chip(&desc->irq_data, p);
		अन्यथा अगर (desc->irq_data.chip->name)
			seq_म_लिखो(p, " %8s", desc->irq_data.chip->name);
		अन्यथा
			seq_म_लिखो(p, " %8s", "-");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(p, " %8s", "None");
	पूर्ण
	अगर (desc->irq_data.करोमुख्य)
		seq_म_लिखो(p, " %*d", prec, (पूर्णांक) desc->irq_data.hwirq);
	अन्यथा
		seq_म_लिखो(p, " %*s", prec, "");
#अगर_घोषित CONFIG_GENERIC_IRQ_SHOW_LEVEL
	seq_म_लिखो(p, " %-8s", irqd_is_level_type(&desc->irq_data) ? "Level" : "Edge");
#पूर्ण_अगर
	अगर (desc->name)
		seq_म_लिखो(p, "-%-8s", desc->name);

	action = desc->action;
	अगर (action) अणु
		seq_म_लिखो(p, "  %s", action->name);
		जबतक ((action = action->next) != शून्य)
			seq_म_लिखो(p, ", %s", action->name);
	पूर्ण

	seq_अ_दो(p, '\n');
	raw_spin_unlock_irqrestore(&desc->lock, flags);
outsparse:
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण
#पूर्ण_अगर
