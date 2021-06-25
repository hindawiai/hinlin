<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IRQDESC_H
#घोषणा _LINUX_IRQDESC_H

#समावेश <linux/rcupdate.h>
#समावेश <linux/kobject.h>
#समावेश <linux/mutex.h>

/*
 * Core पूर्णांकernal functions to deal with irq descriptors
 */

काष्ठा irq_affinity_notअगरy;
काष्ठा proc_dir_entry;
काष्ठा module;
काष्ठा irq_desc;
काष्ठा irq_करोमुख्य;
काष्ठा pt_regs;

/**
 * काष्ठा irq_desc - पूर्णांकerrupt descriptor
 * @irq_common_data:	per irq and chip data passed करोwn to chip functions
 * @kstat_irqs:		irq stats per cpu
 * @handle_irq:		highlevel irq-events handler
 * @action:		the irq action chain
 * @status_use_accessors: status inक्रमmation
 * @core_पूर्णांकernal_state__करो_not_mess_with_it: core पूर्णांकernal status inक्रमmation
 * @depth:		disable-depth, क्रम nested irq_disable() calls
 * @wake_depth:		enable depth, क्रम multiple irq_set_irq_wake() callers
 * @tot_count:		stats field क्रम non-percpu irqs
 * @irq_count:		stats field to detect stalled irqs
 * @last_unhandled:	aging समयr क्रम unhandled count
 * @irqs_unhandled:	stats field क्रम spurious unhandled पूर्णांकerrupts
 * @thपढ़ोs_handled:	stats field क्रम deferred spurious detection of thपढ़ोed handlers
 * @thपढ़ोs_handled_last: comparator field क्रम deferred spurious detection of thपढ़ोed handlers
 * @lock:		locking क्रम SMP
 * @affinity_hपूर्णांक:	hपूर्णांक to user space क्रम preferred irq affinity
 * @affinity_notअगरy:	context क्रम notअगरication of affinity changes
 * @pending_mask:	pending rebalanced पूर्णांकerrupts
 * @thपढ़ोs_oneshot:	bitfield to handle shared oneshot thपढ़ोs
 * @thपढ़ोs_active:	number of irqaction thपढ़ोs currently running
 * @रुको_क्रम_thपढ़ोs:	रुको queue क्रम sync_irq to रुको क्रम thपढ़ोed handlers
 * @nr_actions:		number of installed actions on this descriptor
 * @no_suspend_depth:	number of irqactions on a irq descriptor with
 *			IRQF_NO_SUSPEND set
 * @क्रमce_resume_depth:	number of irqactions on a irq descriptor with
 *			IRQF_FORCE_RESUME set
 * @rcu:		rcu head क्रम delayed मुक्त
 * @kobj:		kobject used to represent this काष्ठा in sysfs
 * @request_mutex:	mutex to protect request/मुक्त beक्रमe locking desc->lock
 * @dir:		/proc/irq/ procfs entry
 * @debugfs_file:	dentry क्रम the debugfs file
 * @name:		flow handler name क्रम /proc/पूर्णांकerrupts output
 */
काष्ठा irq_desc अणु
	काष्ठा irq_common_data	irq_common_data;
	काष्ठा irq_data		irq_data;
	अचिन्हित पूर्णांक __percpu	*kstat_irqs;
	irq_flow_handler_t	handle_irq;
	काष्ठा irqaction	*action;	/* IRQ action list */
	अचिन्हित पूर्णांक		status_use_accessors;
	अचिन्हित पूर्णांक		core_पूर्णांकernal_state__करो_not_mess_with_it;
	अचिन्हित पूर्णांक		depth;		/* nested irq disables */
	अचिन्हित पूर्णांक		wake_depth;	/* nested wake enables */
	अचिन्हित पूर्णांक		tot_count;
	अचिन्हित पूर्णांक		irq_count;	/* For detecting broken IRQs */
	अचिन्हित दीर्घ		last_unhandled;	/* Aging समयr क्रम unhandled count */
	अचिन्हित पूर्णांक		irqs_unhandled;
	atomic_t		thपढ़ोs_handled;
	पूर्णांक			thपढ़ोs_handled_last;
	raw_spinlock_t		lock;
	काष्ठा cpumask		*percpu_enabled;
	स्थिर काष्ठा cpumask	*percpu_affinity;
#अगर_घोषित CONFIG_SMP
	स्थिर काष्ठा cpumask	*affinity_hपूर्णांक;
	काष्ठा irq_affinity_notअगरy *affinity_notअगरy;
#अगर_घोषित CONFIG_GENERIC_PENDING_IRQ
	cpumask_var_t		pending_mask;
#पूर्ण_अगर
#पूर्ण_अगर
	अचिन्हित दीर्घ		thपढ़ोs_oneshot;
	atomic_t		thपढ़ोs_active;
	रुको_queue_head_t       रुको_क्रम_thपढ़ोs;
#अगर_घोषित CONFIG_PM_SLEEP
	अचिन्हित पूर्णांक		nr_actions;
	अचिन्हित पूर्णांक		no_suspend_depth;
	अचिन्हित पूर्णांक		cond_suspend_depth;
	अचिन्हित पूर्णांक		क्रमce_resume_depth;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry	*dir;
#पूर्ण_अगर
#अगर_घोषित CONFIG_GENERIC_IRQ_DEBUGFS
	काष्ठा dentry		*debugfs_file;
	स्थिर अक्षर		*dev_name;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SPARSE_IRQ
	काष्ठा rcu_head		rcu;
	काष्ठा kobject		kobj;
#पूर्ण_अगर
	काष्ठा mutex		request_mutex;
	पूर्णांक			parent_irq;
	काष्ठा module		*owner;
	स्थिर अक्षर		*name;
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

#अगर_घोषित CONFIG_SPARSE_IRQ
बाह्य व्योम irq_lock_sparse(व्योम);
बाह्य व्योम irq_unlock_sparse(व्योम);
#अन्यथा
अटल अंतरभूत व्योम irq_lock_sparse(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम irq_unlock_sparse(व्योम) अणु पूर्ण
बाह्य काष्ठा irq_desc irq_desc[NR_IRQS];
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक irq_desc_kstat_cpu(काष्ठा irq_desc *desc,
					      अचिन्हित पूर्णांक cpu)
अणु
	वापस desc->kstat_irqs ? *per_cpu_ptr(desc->kstat_irqs, cpu) : 0;
पूर्ण

अटल अंतरभूत काष्ठा irq_desc *irq_data_to_desc(काष्ठा irq_data *data)
अणु
	वापस container_of(data->common, काष्ठा irq_desc, irq_common_data);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक irq_desc_get_irq(काष्ठा irq_desc *desc)
अणु
	वापस desc->irq_data.irq;
पूर्ण

अटल अंतरभूत काष्ठा irq_data *irq_desc_get_irq_data(काष्ठा irq_desc *desc)
अणु
	वापस &desc->irq_data;
पूर्ण

अटल अंतरभूत काष्ठा irq_chip *irq_desc_get_chip(काष्ठा irq_desc *desc)
अणु
	वापस desc->irq_data.chip;
पूर्ण

अटल अंतरभूत व्योम *irq_desc_get_chip_data(काष्ठा irq_desc *desc)
अणु
	वापस desc->irq_data.chip_data;
पूर्ण

अटल अंतरभूत व्योम *irq_desc_get_handler_data(काष्ठा irq_desc *desc)
अणु
	वापस desc->irq_common_data.handler_data;
पूर्ण

/*
 * Architectures call this to let the generic IRQ layer
 * handle an पूर्णांकerrupt.
 */
अटल अंतरभूत व्योम generic_handle_irq_desc(काष्ठा irq_desc *desc)
अणु
	desc->handle_irq(desc);
पूर्ण

पूर्णांक generic_handle_irq(अचिन्हित पूर्णांक irq);

#अगर_घोषित CONFIG_HANDLE_DOMAIN_IRQ
/*
 * Convert a HW पूर्णांकerrupt number to a logical one using a IRQ करोमुख्य,
 * and handle the result पूर्णांकerrupt number. Return -EINVAL अगर
 * conversion failed. Providing a शून्य करोमुख्य indicates that the
 * conversion has alपढ़ोy been करोne.
 */
पूर्णांक __handle_करोमुख्य_irq(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक hwirq,
			bool lookup, काष्ठा pt_regs *regs);

अटल अंतरभूत पूर्णांक handle_करोमुख्य_irq(काष्ठा irq_करोमुख्य *करोमुख्य,
				    अचिन्हित पूर्णांक hwirq, काष्ठा pt_regs *regs)
अणु
	वापस __handle_करोमुख्य_irq(करोमुख्य, hwirq, true, regs);
पूर्ण

#अगर_घोषित CONFIG_IRQ_DOMAIN
पूर्णांक handle_करोमुख्य_nmi(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक hwirq,
		      काष्ठा pt_regs *regs);
#पूर्ण_अगर
#पूर्ण_अगर

/* Test to see अगर a driver has successfully requested an irq */
अटल अंतरभूत पूर्णांक irq_desc_has_action(काष्ठा irq_desc *desc)
अणु
	वापस desc && desc->action != शून्य;
पूर्ण

/**
 * irq_set_handler_locked - Set irq handler from a locked region
 * @data:	Poपूर्णांकer to the irq_data काष्ठाure which identअगरies the irq
 * @handler:	Flow control handler function क्रम this पूर्णांकerrupt
 *
 * Sets the handler in the irq descriptor associated to @data.
 *
 * Must be called with irq_desc locked and valid parameters. Typical
 * call site is the irq_set_type() callback.
 */
अटल अंतरभूत व्योम irq_set_handler_locked(काष्ठा irq_data *data,
					  irq_flow_handler_t handler)
अणु
	काष्ठा irq_desc *desc = irq_data_to_desc(data);

	desc->handle_irq = handler;
पूर्ण

/**
 * irq_set_chip_handler_name_locked - Set chip, handler and name from a locked region
 * @data:	Poपूर्णांकer to the irq_data काष्ठाure क्रम which the chip is set
 * @chip:	Poपूर्णांकer to the new irq chip
 * @handler:	Flow control handler function क्रम this पूर्णांकerrupt
 * @name:	Name of the पूर्णांकerrupt
 *
 * Replace the irq chip at the proper hierarchy level in @data and
 * sets the handler and name in the associated irq descriptor.
 *
 * Must be called with irq_desc locked and valid parameters.
 */
अटल अंतरभूत व्योम
irq_set_chip_handler_name_locked(काष्ठा irq_data *data, काष्ठा irq_chip *chip,
				 irq_flow_handler_t handler, स्थिर अक्षर *name)
अणु
	काष्ठा irq_desc *desc = irq_data_to_desc(data);

	desc->handle_irq = handler;
	desc->name = name;
	data->chip = chip;
पूर्ण

bool irq_check_status_bit(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक biपंचांगask);

अटल अंतरभूत bool irq_balancing_disabled(अचिन्हित पूर्णांक irq)
अणु
	वापस irq_check_status_bit(irq, IRQ_NO_BALANCING_MASK);
पूर्ण

अटल अंतरभूत bool irq_is_percpu(अचिन्हित पूर्णांक irq)
अणु
	वापस irq_check_status_bit(irq, IRQ_PER_CPU);
पूर्ण

अटल अंतरभूत bool irq_is_percpu_devid(अचिन्हित पूर्णांक irq)
अणु
	वापस irq_check_status_bit(irq, IRQ_PER_CPU_DEVID);
पूर्ण

व्योम __irq_set_lockdep_class(अचिन्हित पूर्णांक irq, काष्ठा lock_class_key *lock_class,
			     काष्ठा lock_class_key *request_class);
अटल अंतरभूत व्योम
irq_set_lockdep_class(अचिन्हित पूर्णांक irq, काष्ठा lock_class_key *lock_class,
		      काष्ठा lock_class_key *request_class)
अणु
	अगर (IS_ENABLED(CONFIG_LOCKDEP))
		__irq_set_lockdep_class(irq, lock_class, request_class);
पूर्ण

#पूर्ण_अगर
