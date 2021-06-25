<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* पूर्णांकerrupt.h */
#अगर_अघोषित _LINUX_INTERRUPT_H
#घोषणा _LINUX_INTERRUPT_H

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/irqnr.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/kref.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/sections.h>

/*
 * These correspond to the IORESOURCE_IRQ_* defines in
 * linux/ioport.h to select the पूर्णांकerrupt line behaviour.  When
 * requesting an पूर्णांकerrupt without specअगरying a IRQF_TRIGGER, the
 * setting should be assumed to be "as already configured", which
 * may be as per machine or firmware initialisation.
 */
#घोषणा IRQF_TRIGGER_NONE	0x00000000
#घोषणा IRQF_TRIGGER_RISING	0x00000001
#घोषणा IRQF_TRIGGER_FALLING	0x00000002
#घोषणा IRQF_TRIGGER_HIGH	0x00000004
#घोषणा IRQF_TRIGGER_LOW	0x00000008
#घोषणा IRQF_TRIGGER_MASK	(IRQF_TRIGGER_HIGH | IRQF_TRIGGER_LOW | \
				 IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING)
#घोषणा IRQF_TRIGGER_PROBE	0x00000010

/*
 * These flags used only by the kernel as part of the
 * irq handling routines.
 *
 * IRQF_SHARED - allow sharing the irq among several devices
 * IRQF_PROBE_SHARED - set by callers when they expect sharing mismatches to occur
 * IRQF_TIMER - Flag to mark this पूर्णांकerrupt as समयr पूर्णांकerrupt
 * IRQF_PERCPU - Interrupt is per cpu
 * IRQF_NOBALANCING - Flag to exclude this पूर्णांकerrupt from irq balancing
 * IRQF_IRQPOLL - Interrupt is used क्रम polling (only the पूर्णांकerrupt that is
 *                रेजिस्टरed first in a shared पूर्णांकerrupt is considered क्रम
 *                perक्रमmance reasons)
 * IRQF_ONESHOT - Interrupt is not reenabled after the hardirq handler finished.
 *                Used by thपढ़ोed पूर्णांकerrupts which need to keep the
 *                irq line disabled until the thपढ़ोed handler has been run.
 * IRQF_NO_SUSPEND - Do not disable this IRQ during suspend.  Does not guarantee
 *                   that this पूर्णांकerrupt will wake the प्रणाली from a suspended
 *                   state.  See Documentation/घातer/suspend-and-पूर्णांकerrupts.rst
 * IRQF_FORCE_RESUME - Force enable it on resume even अगर IRQF_NO_SUSPEND is set
 * IRQF_NO_THREAD - Interrupt cannot be thपढ़ोed
 * IRQF_EARLY_RESUME - Resume IRQ early during syscore instead of at device
 *                resume समय.
 * IRQF_COND_SUSPEND - If the IRQ is shared with a NO_SUSPEND user, execute this
 *                पूर्णांकerrupt handler after suspending पूर्णांकerrupts. For प्रणाली
 *                wakeup devices users need to implement wakeup detection in
 *                their पूर्णांकerrupt handlers.
 * IRQF_NO_AUTOEN - Don't enable IRQ or NMI स्वतःmatically when users request it.
 *                Users will enable it explicitly by enable_irq() or enable_nmi()
 *                later.
 */
#घोषणा IRQF_SHARED		0x00000080
#घोषणा IRQF_PROBE_SHARED	0x00000100
#घोषणा __IRQF_TIMER		0x00000200
#घोषणा IRQF_PERCPU		0x00000400
#घोषणा IRQF_NOBALANCING	0x00000800
#घोषणा IRQF_IRQPOLL		0x00001000
#घोषणा IRQF_ONESHOT		0x00002000
#घोषणा IRQF_NO_SUSPEND		0x00004000
#घोषणा IRQF_FORCE_RESUME	0x00008000
#घोषणा IRQF_NO_THREAD		0x00010000
#घोषणा IRQF_EARLY_RESUME	0x00020000
#घोषणा IRQF_COND_SUSPEND	0x00040000
#घोषणा IRQF_NO_AUTOEN		0x00080000

#घोषणा IRQF_TIMER		(__IRQF_TIMER | IRQF_NO_SUSPEND | IRQF_NO_THREAD)

/*
 * These values can be वापसed by request_any_context_irq() and
 * describe the context the पूर्णांकerrupt will be run in.
 *
 * IRQC_IS_HARसूचीQ - पूर्णांकerrupt runs in hardirq context
 * IRQC_IS_NESTED - पूर्णांकerrupt runs in a nested thपढ़ोed context
 */
क्रमागत अणु
	IRQC_IS_HARसूचीQ	= 0,
	IRQC_IS_NESTED,
पूर्ण;

प्रकार irqवापस_t (*irq_handler_t)(पूर्णांक, व्योम *);

/**
 * काष्ठा irqaction - per पूर्णांकerrupt action descriptor
 * @handler:	पूर्णांकerrupt handler function
 * @name:	name of the device
 * @dev_id:	cookie to identअगरy the device
 * @percpu_dev_id:	cookie to identअगरy the device
 * @next:	poपूर्णांकer to the next irqaction क्रम shared पूर्णांकerrupts
 * @irq:	पूर्णांकerrupt number
 * @flags:	flags (see IRQF_* above)
 * @thपढ़ो_fn:	पूर्णांकerrupt handler function क्रम thपढ़ोed पूर्णांकerrupts
 * @thपढ़ो:	thपढ़ो poपूर्णांकer क्रम thपढ़ोed पूर्णांकerrupts
 * @secondary:	poपूर्णांकer to secondary irqaction (क्रमce thपढ़ोing)
 * @thपढ़ो_flags:	flags related to @thपढ़ो
 * @thपढ़ो_mask:	biपंचांगask क्रम keeping track of @thपढ़ो activity
 * @dir:	poपूर्णांकer to the proc/irq/NN/name entry
 */
काष्ठा irqaction अणु
	irq_handler_t		handler;
	व्योम			*dev_id;
	व्योम __percpu		*percpu_dev_id;
	काष्ठा irqaction	*next;
	irq_handler_t		thपढ़ो_fn;
	काष्ठा task_काष्ठा	*thपढ़ो;
	काष्ठा irqaction	*secondary;
	अचिन्हित पूर्णांक		irq;
	अचिन्हित पूर्णांक		flags;
	अचिन्हित दीर्घ		thपढ़ो_flags;
	अचिन्हित दीर्घ		thपढ़ो_mask;
	स्थिर अक्षर		*name;
	काष्ठा proc_dir_entry	*dir;
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

बाह्य irqवापस_t no_action(पूर्णांक cpl, व्योम *dev_id);

/*
 * If a (PCI) device पूर्णांकerrupt is not connected we set dev->irq to
 * IRQ_NOTCONNECTED. This causes request_irq() to fail with -ENOTCONN, so we
 * can distingiush that हाल from other error वापसs.
 *
 * 0x80000000 is guaranteed to be outside the available range of पूर्णांकerrupts
 * and easy to distinguish from other possible incorrect values.
 */
#घोषणा IRQ_NOTCONNECTED	(1U << 31)

बाह्य पूर्णांक __must_check
request_thपढ़ोed_irq(अचिन्हित पूर्णांक irq, irq_handler_t handler,
		     irq_handler_t thपढ़ो_fn,
		     अचिन्हित दीर्घ flags, स्थिर अक्षर *name, व्योम *dev);

/**
 * request_irq - Add a handler क्रम an पूर्णांकerrupt line
 * @irq:	The पूर्णांकerrupt line to allocate
 * @handler:	Function to be called when the IRQ occurs.
 *		Primary handler क्रम thपढ़ोed पूर्णांकerrupts
 *		If शून्य, the शेष primary handler is installed
 * @flags:	Handling flags
 * @name:	Name of the device generating this पूर्णांकerrupt
 * @dev:	A cookie passed to the handler function
 *
 * This call allocates an पूर्णांकerrupt and establishes a handler; see
 * the करोcumentation क्रम request_thपढ़ोed_irq() क्रम details.
 */
अटल अंतरभूत पूर्णांक __must_check
request_irq(अचिन्हित पूर्णांक irq, irq_handler_t handler, अचिन्हित दीर्घ flags,
	    स्थिर अक्षर *name, व्योम *dev)
अणु
	वापस request_thपढ़ोed_irq(irq, handler, शून्य, flags, name, dev);
पूर्ण

बाह्य पूर्णांक __must_check
request_any_context_irq(अचिन्हित पूर्णांक irq, irq_handler_t handler,
			अचिन्हित दीर्घ flags, स्थिर अक्षर *name, व्योम *dev_id);

बाह्य पूर्णांक __must_check
__request_percpu_irq(अचिन्हित पूर्णांक irq, irq_handler_t handler,
		     अचिन्हित दीर्घ flags, स्थिर अक्षर *devname,
		     व्योम __percpu *percpu_dev_id);

बाह्य पूर्णांक __must_check
request_nmi(अचिन्हित पूर्णांक irq, irq_handler_t handler, अचिन्हित दीर्घ flags,
	    स्थिर अक्षर *name, व्योम *dev);

अटल अंतरभूत पूर्णांक __must_check
request_percpu_irq(अचिन्हित पूर्णांक irq, irq_handler_t handler,
		   स्थिर अक्षर *devname, व्योम __percpu *percpu_dev_id)
अणु
	वापस __request_percpu_irq(irq, handler, 0,
				    devname, percpu_dev_id);
पूर्ण

बाह्य पूर्णांक __must_check
request_percpu_nmi(अचिन्हित पूर्णांक irq, irq_handler_t handler,
		   स्थिर अक्षर *devname, व्योम __percpu *dev);

बाह्य स्थिर व्योम *मुक्त_irq(अचिन्हित पूर्णांक, व्योम *);
बाह्य व्योम मुक्त_percpu_irq(अचिन्हित पूर्णांक, व्योम __percpu *);

बाह्य स्थिर व्योम *मुक्त_nmi(अचिन्हित पूर्णांक irq, व्योम *dev_id);
बाह्य व्योम मुक्त_percpu_nmi(अचिन्हित पूर्णांक irq, व्योम __percpu *percpu_dev_id);

काष्ठा device;

बाह्य पूर्णांक __must_check
devm_request_thपढ़ोed_irq(काष्ठा device *dev, अचिन्हित पूर्णांक irq,
			  irq_handler_t handler, irq_handler_t thपढ़ो_fn,
			  अचिन्हित दीर्घ irqflags, स्थिर अक्षर *devname,
			  व्योम *dev_id);

अटल अंतरभूत पूर्णांक __must_check
devm_request_irq(काष्ठा device *dev, अचिन्हित पूर्णांक irq, irq_handler_t handler,
		 अचिन्हित दीर्घ irqflags, स्थिर अक्षर *devname, व्योम *dev_id)
अणु
	वापस devm_request_thपढ़ोed_irq(dev, irq, handler, शून्य, irqflags,
					 devname, dev_id);
पूर्ण

बाह्य पूर्णांक __must_check
devm_request_any_context_irq(काष्ठा device *dev, अचिन्हित पूर्णांक irq,
		 irq_handler_t handler, अचिन्हित दीर्घ irqflags,
		 स्थिर अक्षर *devname, व्योम *dev_id);

बाह्य व्योम devm_मुक्त_irq(काष्ठा device *dev, अचिन्हित पूर्णांक irq, व्योम *dev_id);

/*
 * On lockdep we करोnt want to enable hardirqs in hardirq
 * context. Use local_irq_enable_in_hardirq() to annotate
 * kernel code that has to करो this nevertheless (pretty much
 * the only valid हाल is क्रम old/broken hardware that is
 * insanely slow).
 *
 * NOTE: in theory this might अवरोध fragile code that relies
 * on hardirq delivery - in practice we करोnt seem to have such
 * places left. So the only effect should be slightly increased
 * irqs-off latencies.
 */
#अगर_घोषित CONFIG_LOCKDEP
# define local_irq_enable_in_hardirq()	करो अणु पूर्ण जबतक (0)
#अन्यथा
# define local_irq_enable_in_hardirq()	local_irq_enable()
#पूर्ण_अगर

bool irq_has_action(अचिन्हित पूर्णांक irq);
बाह्य व्योम disable_irq_nosync(अचिन्हित पूर्णांक irq);
बाह्य bool disable_hardirq(अचिन्हित पूर्णांक irq);
बाह्य व्योम disable_irq(अचिन्हित पूर्णांक irq);
बाह्य व्योम disable_percpu_irq(अचिन्हित पूर्णांक irq);
बाह्य व्योम enable_irq(अचिन्हित पूर्णांक irq);
बाह्य व्योम enable_percpu_irq(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक type);
बाह्य bool irq_percpu_is_enabled(अचिन्हित पूर्णांक irq);
बाह्य व्योम irq_wake_thपढ़ो(अचिन्हित पूर्णांक irq, व्योम *dev_id);

बाह्य व्योम disable_nmi_nosync(अचिन्हित पूर्णांक irq);
बाह्य व्योम disable_percpu_nmi(अचिन्हित पूर्णांक irq);
बाह्य व्योम enable_nmi(अचिन्हित पूर्णांक irq);
बाह्य व्योम enable_percpu_nmi(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक type);
बाह्य पूर्णांक prepare_percpu_nmi(अचिन्हित पूर्णांक irq);
बाह्य व्योम tearकरोwn_percpu_nmi(अचिन्हित पूर्णांक irq);

बाह्य पूर्णांक irq_inject_पूर्णांकerrupt(अचिन्हित पूर्णांक irq);

/* The following three functions are क्रम the core kernel use only. */
बाह्य व्योम suspend_device_irqs(व्योम);
बाह्य व्योम resume_device_irqs(व्योम);
बाह्य व्योम rearm_wake_irq(अचिन्हित पूर्णांक irq);

/**
 * काष्ठा irq_affinity_notअगरy - context क्रम notअगरication of IRQ affinity changes
 * @irq:		Interrupt to which notअगरication applies
 * @kref:		Reference count, क्रम पूर्णांकernal use
 * @work:		Work item, क्रम पूर्णांकernal use
 * @notअगरy:		Function to be called on change.  This will be
 *			called in process context.
 * @release:		Function to be called on release.  This will be
 *			called in process context.  Once रेजिस्टरed, the
 *			काष्ठाure must only be मुक्तd when this function is
 *			called or later.
 */
काष्ठा irq_affinity_notअगरy अणु
	अचिन्हित पूर्णांक irq;
	काष्ठा kref kref;
	काष्ठा work_काष्ठा work;
	व्योम (*notअगरy)(काष्ठा irq_affinity_notअगरy *, स्थिर cpumask_t *mask);
	व्योम (*release)(काष्ठा kref *ref);
पूर्ण;

#घोषणा	IRQ_AFFINITY_MAX_SETS  4

/**
 * काष्ठा irq_affinity - Description क्रम स्वतःmatic irq affinity assignements
 * @pre_vectors:	Don't apply affinity to @pre_vectors at beginning of
 *			the MSI(-X) vector space
 * @post_vectors:	Don't apply affinity to @post_vectors at end of
 *			the MSI(-X) vector space
 * @nr_sets:		The number of पूर्णांकerrupt sets क्रम which affinity
 *			spपढ़ोing is required
 * @set_size:		Array holding the size of each पूर्णांकerrupt set
 * @calc_sets:		Callback क्रम calculating the number and size
 *			of पूर्णांकerrupt sets
 * @priv:		Private data क्रम usage by @calc_sets, usually a
 *			poपूर्णांकer to driver/device specअगरic data.
 */
काष्ठा irq_affinity अणु
	अचिन्हित पूर्णांक	pre_vectors;
	अचिन्हित पूर्णांक	post_vectors;
	अचिन्हित पूर्णांक	nr_sets;
	अचिन्हित पूर्णांक	set_size[IRQ_AFFINITY_MAX_SETS];
	व्योम		(*calc_sets)(काष्ठा irq_affinity *, अचिन्हित पूर्णांक nvecs);
	व्योम		*priv;
पूर्ण;

/**
 * काष्ठा irq_affinity_desc - Interrupt affinity descriptor
 * @mask:	cpumask to hold the affinity assignment
 * @is_managed: 1 अगर the पूर्णांकerrupt is managed पूर्णांकernally
 */
काष्ठा irq_affinity_desc अणु
	काष्ठा cpumask	mask;
	अचिन्हित पूर्णांक	is_managed : 1;
पूर्ण;

#अगर defined(CONFIG_SMP)

बाह्य cpumask_var_t irq_शेष_affinity;

/* Internal implementation. Use the helpers below */
बाह्य पूर्णांक __irq_set_affinity(अचिन्हित पूर्णांक irq, स्थिर काष्ठा cpumask *cpumask,
			      bool क्रमce);

/**
 * irq_set_affinity - Set the irq affinity of a given irq
 * @irq:	Interrupt to set affinity
 * @cpumask:	cpumask
 *
 * Fails अगर cpumask करोes not contain an online CPU
 */
अटल अंतरभूत पूर्णांक
irq_set_affinity(अचिन्हित पूर्णांक irq, स्थिर काष्ठा cpumask *cpumask)
अणु
	वापस __irq_set_affinity(irq, cpumask, false);
पूर्ण

/**
 * irq_क्रमce_affinity - Force the irq affinity of a given irq
 * @irq:	Interrupt to set affinity
 * @cpumask:	cpumask
 *
 * Same as irq_set_affinity, but without checking the mask against
 * online cpus.
 *
 * Solely क्रम low level cpu hotplug code, where we need to make per
 * cpu पूर्णांकerrupts affine beक्रमe the cpu becomes online.
 */
अटल अंतरभूत पूर्णांक
irq_क्रमce_affinity(अचिन्हित पूर्णांक irq, स्थिर काष्ठा cpumask *cpumask)
अणु
	वापस __irq_set_affinity(irq, cpumask, true);
पूर्ण

बाह्य पूर्णांक irq_can_set_affinity(अचिन्हित पूर्णांक irq);
बाह्य पूर्णांक irq_select_affinity(अचिन्हित पूर्णांक irq);

बाह्य पूर्णांक irq_set_affinity_hपूर्णांक(अचिन्हित पूर्णांक irq, स्थिर काष्ठा cpumask *m);
बाह्य पूर्णांक irq_update_affinity_desc(अचिन्हित पूर्णांक irq,
				    काष्ठा irq_affinity_desc *affinity);

बाह्य पूर्णांक
irq_set_affinity_notअगरier(अचिन्हित पूर्णांक irq, काष्ठा irq_affinity_notअगरy *notअगरy);

काष्ठा irq_affinity_desc *
irq_create_affinity_masks(अचिन्हित पूर्णांक nvec, काष्ठा irq_affinity *affd);

अचिन्हित पूर्णांक irq_calc_affinity_vectors(अचिन्हित पूर्णांक minvec, अचिन्हित पूर्णांक maxvec,
				       स्थिर काष्ठा irq_affinity *affd);

#अन्यथा /* CONFIG_SMP */

अटल अंतरभूत पूर्णांक irq_set_affinity(अचिन्हित पूर्णांक irq, स्थिर काष्ठा cpumask *m)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक irq_क्रमce_affinity(अचिन्हित पूर्णांक irq, स्थिर काष्ठा cpumask *cpumask)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक irq_can_set_affinity(अचिन्हित पूर्णांक irq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक irq_select_affinity(अचिन्हित पूर्णांक irq)  अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक irq_set_affinity_hपूर्णांक(अचिन्हित पूर्णांक irq,
					स्थिर काष्ठा cpumask *m)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक irq_update_affinity_desc(अचिन्हित पूर्णांक irq,
					   काष्ठा irq_affinity_desc *affinity)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक
irq_set_affinity_notअगरier(अचिन्हित पूर्णांक irq, काष्ठा irq_affinity_notअगरy *notअगरy)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा irq_affinity_desc *
irq_create_affinity_masks(अचिन्हित पूर्णांक nvec, काष्ठा irq_affinity *affd)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
irq_calc_affinity_vectors(अचिन्हित पूर्णांक minvec, अचिन्हित पूर्णांक maxvec,
			  स्थिर काष्ठा irq_affinity *affd)
अणु
	वापस maxvec;
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

/*
 * Special lockdep variants of irq disabling/enabling.
 * These should be used क्रम locking स्थिरructs that
 * know that a particular irq context which is disabled,
 * and which is the only irq-context user of a lock,
 * that it's safe to take the lock in the irq-disabled
 * section without disabling hardirqs.
 *
 * On !CONFIG_LOCKDEP they are equivalent to the normal
 * irq disable/enable methods.
 */
अटल अंतरभूत व्योम disable_irq_nosync_lockdep(अचिन्हित पूर्णांक irq)
अणु
	disable_irq_nosync(irq);
#अगर_घोषित CONFIG_LOCKDEP
	local_irq_disable();
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम disable_irq_nosync_lockdep_irqsave(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ *flags)
अणु
	disable_irq_nosync(irq);
#अगर_घोषित CONFIG_LOCKDEP
	local_irq_save(*flags);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम disable_irq_lockdep(अचिन्हित पूर्णांक irq)
अणु
	disable_irq(irq);
#अगर_घोषित CONFIG_LOCKDEP
	local_irq_disable();
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम enable_irq_lockdep(अचिन्हित पूर्णांक irq)
अणु
#अगर_घोषित CONFIG_LOCKDEP
	local_irq_enable();
#पूर्ण_अगर
	enable_irq(irq);
पूर्ण

अटल अंतरभूत व्योम enable_irq_lockdep_irqrestore(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ *flags)
अणु
#अगर_घोषित CONFIG_LOCKDEP
	local_irq_restore(*flags);
#पूर्ण_अगर
	enable_irq(irq);
पूर्ण

/* IRQ wakeup (PM) control: */
बाह्य पूर्णांक irq_set_irq_wake(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक on);

अटल अंतरभूत पूर्णांक enable_irq_wake(अचिन्हित पूर्णांक irq)
अणु
	वापस irq_set_irq_wake(irq, 1);
पूर्ण

अटल अंतरभूत पूर्णांक disable_irq_wake(अचिन्हित पूर्णांक irq)
अणु
	वापस irq_set_irq_wake(irq, 0);
पूर्ण

/*
 * irq_get_irqchip_state/irq_set_irqchip_state specअगरic flags
 */
क्रमागत irqchip_irq_state अणु
	IRQCHIP_STATE_PENDING,		/* Is पूर्णांकerrupt pending? */
	IRQCHIP_STATE_ACTIVE,		/* Is पूर्णांकerrupt in progress? */
	IRQCHIP_STATE_MASKED,		/* Is पूर्णांकerrupt masked? */
	IRQCHIP_STATE_LINE_LEVEL,	/* Is IRQ line high? */
पूर्ण;

बाह्य पूर्णांक irq_get_irqchip_state(अचिन्हित पूर्णांक irq, क्रमागत irqchip_irq_state which,
				 bool *state);
बाह्य पूर्णांक irq_set_irqchip_state(अचिन्हित पूर्णांक irq, क्रमागत irqchip_irq_state which,
				 bool state);

#अगर_घोषित CONFIG_IRQ_FORCED_THREADING
# अगरdef CONFIG_PREEMPT_RT
#  define क्रमce_irqthपढ़ोs	(true)
# अन्यथा
बाह्य bool क्रमce_irqthपढ़ोs;
# endअगर
#अन्यथा
#घोषणा क्रमce_irqthपढ़ोs	(0)
#पूर्ण_अगर

#अगर_अघोषित local_softirq_pending

#अगर_अघोषित local_softirq_pending_ref
#घोषणा local_softirq_pending_ref irq_stat.__softirq_pending
#पूर्ण_अगर

#घोषणा local_softirq_pending()	(__this_cpu_पढ़ो(local_softirq_pending_ref))
#घोषणा set_softirq_pending(x)	(__this_cpu_ग_लिखो(local_softirq_pending_ref, (x)))
#घोषणा or_softirq_pending(x)	(__this_cpu_or(local_softirq_pending_ref, (x)))

#पूर्ण_अगर /* local_softirq_pending */

/* Some architectures might implement lazy enabling/disabling of
 * पूर्णांकerrupts. In some हालs, such as stop_machine, we might want
 * to ensure that after a local_irq_disable(), पूर्णांकerrupts have
 * really been disabled in hardware. Such architectures need to
 * implement the following hook.
 */
#अगर_अघोषित hard_irq_disable
#घोषणा hard_irq_disable()	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

/* PLEASE, aव्योम to allocate new softirqs, अगर you need not _really_ high
   frequency thपढ़ोed job scheduling. For almost all the purposes
   tasklets are more than enough. F.e. all serial device BHs et
   al. should be converted to tasklets, not to softirqs.
 */

क्रमागत
अणु
	HI_SOFTIRQ=0,
	TIMER_SOFTIRQ,
	NET_TX_SOFTIRQ,
	NET_RX_SOFTIRQ,
	BLOCK_SOFTIRQ,
	IRQ_POLL_SOFTIRQ,
	TASKLET_SOFTIRQ,
	SCHED_SOFTIRQ,
	HRTIMER_SOFTIRQ,
	RCU_SOFTIRQ,    /* Preferable RCU should always be the last softirq */

	NR_SOFTIRQS
पूर्ण;

#घोषणा SOFTIRQ_STOP_IDLE_MASK (~(1 << RCU_SOFTIRQ))

/* map softirq index to softirq name. update 'softirq_to_name' in
 * kernel/softirq.c when adding a new softirq.
 */
बाह्य स्थिर अक्षर * स्थिर softirq_to_name[NR_SOFTIRQS];

/* softirq mask and active fields moved to irq_cpustat_t in
 * यंत्र/hardirq.h to get better cache usage.  KAO
 */

काष्ठा softirq_action
अणु
	व्योम	(*action)(काष्ठा softirq_action *);
पूर्ण;

यंत्रlinkage व्योम करो_softirq(व्योम);
यंत्रlinkage व्योम __करो_softirq(व्योम);

बाह्य व्योम खोलो_softirq(पूर्णांक nr, व्योम (*action)(काष्ठा softirq_action *));
बाह्य व्योम softirq_init(व्योम);
बाह्य व्योम __उठाओ_softirq_irqoff(अचिन्हित पूर्णांक nr);

बाह्य व्योम उठाओ_softirq_irqoff(अचिन्हित पूर्णांक nr);
बाह्य व्योम उठाओ_softirq(अचिन्हित पूर्णांक nr);

DECLARE_PER_CPU(काष्ठा task_काष्ठा *, ksoftirqd);

अटल अंतरभूत काष्ठा task_काष्ठा *this_cpu_ksoftirqd(व्योम)
अणु
	वापस this_cpu_पढ़ो(ksoftirqd);
पूर्ण

/* Tasklets --- multithपढ़ोed analogue of BHs.

   This API is deprecated. Please consider using thपढ़ोed IRQs instead:
   https://lore.kernel.org/lkml/20200716081538.2sivhkj4hcyrusem@linutronix.de

   Main feature dअगरfering them of generic softirqs: tasklet
   is running only on one CPU simultaneously.

   Main feature dअगरfering them of BHs: dअगरferent tasklets
   may be run simultaneously on dअगरferent CPUs.

   Properties:
   * If tasklet_schedule() is called, then tasklet is guaranteed
     to be executed on some cpu at least once after this.
   * If the tasklet is alपढ़ोy scheduled, but its execution is still not
     started, it will be executed only once.
   * If this tasklet is alपढ़ोy running on another CPU (or schedule is called
     from tasklet itself), it is rescheduled क्रम later.
   * Tasklet is strictly serialized wrt itself, but not
     wrt another tasklets. If client needs some पूर्णांकertask synchronization,
     he makes it with spinlocks.
 */

काष्ठा tasklet_काष्ठा
अणु
	काष्ठा tasklet_काष्ठा *next;
	अचिन्हित दीर्घ state;
	atomic_t count;
	bool use_callback;
	जोड़ अणु
		व्योम (*func)(अचिन्हित दीर्घ data);
		व्योम (*callback)(काष्ठा tasklet_काष्ठा *t);
	पूर्ण;
	अचिन्हित दीर्घ data;
पूर्ण;

#घोषणा DECLARE_TASKLET(name, _callback)		\
काष्ठा tasklet_काष्ठा name = अणु				\
	.count = ATOMIC_INIT(0),			\
	.callback = _callback,				\
	.use_callback = true,				\
पूर्ण

#घोषणा DECLARE_TASKLET_DISABLED(name, _callback)	\
काष्ठा tasklet_काष्ठा name = अणु				\
	.count = ATOMIC_INIT(1),			\
	.callback = _callback,				\
	.use_callback = true,				\
पूर्ण

#घोषणा from_tasklet(var, callback_tasklet, tasklet_fieldname)	\
	container_of(callback_tasklet, typeof(*var), tasklet_fieldname)

#घोषणा DECLARE_TASKLET_OLD(name, _func)		\
काष्ठा tasklet_काष्ठा name = अणु				\
	.count = ATOMIC_INIT(0),			\
	.func = _func,					\
पूर्ण

#घोषणा DECLARE_TASKLET_DISABLED_OLD(name, _func)	\
काष्ठा tasklet_काष्ठा name = अणु				\
	.count = ATOMIC_INIT(1),			\
	.func = _func,					\
पूर्ण

क्रमागत
अणु
	TASKLET_STATE_SCHED,	/* Tasklet is scheduled क्रम execution */
	TASKLET_STATE_RUN	/* Tasklet is running (SMP only) */
पूर्ण;

#अगर defined(CONFIG_SMP) || defined(CONFIG_PREEMPT_RT)
अटल अंतरभूत पूर्णांक tasklet_trylock(काष्ठा tasklet_काष्ठा *t)
अणु
	वापस !test_and_set_bit(TASKLET_STATE_RUN, &(t)->state);
पूर्ण

व्योम tasklet_unlock(काष्ठा tasklet_काष्ठा *t);
व्योम tasklet_unlock_रुको(काष्ठा tasklet_काष्ठा *t);
व्योम tasklet_unlock_spin_रुको(काष्ठा tasklet_काष्ठा *t);

#अन्यथा
अटल अंतरभूत पूर्णांक tasklet_trylock(काष्ठा tasklet_काष्ठा *t) अणु वापस 1; पूर्ण
अटल अंतरभूत व्योम tasklet_unlock(काष्ठा tasklet_काष्ठा *t) अणु पूर्ण
अटल अंतरभूत व्योम tasklet_unlock_रुको(काष्ठा tasklet_काष्ठा *t) अणु पूर्ण
अटल अंतरभूत व्योम tasklet_unlock_spin_रुको(काष्ठा tasklet_काष्ठा *t) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम __tasklet_schedule(काष्ठा tasklet_काष्ठा *t);

अटल अंतरभूत व्योम tasklet_schedule(काष्ठा tasklet_काष्ठा *t)
अणु
	अगर (!test_and_set_bit(TASKLET_STATE_SCHED, &t->state))
		__tasklet_schedule(t);
पूर्ण

बाह्य व्योम __tasklet_hi_schedule(काष्ठा tasklet_काष्ठा *t);

अटल अंतरभूत व्योम tasklet_hi_schedule(काष्ठा tasklet_काष्ठा *t)
अणु
	अगर (!test_and_set_bit(TASKLET_STATE_SCHED, &t->state))
		__tasklet_hi_schedule(t);
पूर्ण

अटल अंतरभूत व्योम tasklet_disable_nosync(काष्ठा tasklet_काष्ठा *t)
अणु
	atomic_inc(&t->count);
	smp_mb__after_atomic();
पूर्ण

/*
 * Do not use in new code. Disabling tasklets from atomic contexts is
 * error prone and should be aव्योमed.
 */
अटल अंतरभूत व्योम tasklet_disable_in_atomic(काष्ठा tasklet_काष्ठा *t)
अणु
	tasklet_disable_nosync(t);
	tasklet_unlock_spin_रुको(t);
	smp_mb();
पूर्ण

अटल अंतरभूत व्योम tasklet_disable(काष्ठा tasklet_काष्ठा *t)
अणु
	tasklet_disable_nosync(t);
	tasklet_unlock_रुको(t);
	smp_mb();
पूर्ण

अटल अंतरभूत व्योम tasklet_enable(काष्ठा tasklet_काष्ठा *t)
अणु
	smp_mb__beक्रमe_atomic();
	atomic_dec(&t->count);
पूर्ण

बाह्य व्योम tasklet_समाप्त(काष्ठा tasklet_काष्ठा *t);
बाह्य व्योम tasklet_init(काष्ठा tasklet_काष्ठा *t,
			 व्योम (*func)(अचिन्हित दीर्घ), अचिन्हित दीर्घ data);
बाह्य व्योम tasklet_setup(काष्ठा tasklet_काष्ठा *t,
			  व्योम (*callback)(काष्ठा tasklet_काष्ठा *));

/*
 * Autoprobing क्रम irqs:
 *
 * probe_irq_on() and probe_irq_off() provide robust primitives
 * क्रम accurate IRQ probing during kernel initialization.  They are
 * reasonably simple to use, are not "fooled" by spurious पूर्णांकerrupts,
 * and, unlike other attempts at IRQ probing, they करो not get hung on
 * stuck पूर्णांकerrupts (such as unused PS2 mouse पूर्णांकerfaces on ASUS boards).
 *
 * For reasonably foolproof probing, use them as follows:
 *
 * 1. clear and/or mask the device's पूर्णांकernal पूर्णांकerrupt.
 * 2. sti();
 * 3. irqs = probe_irq_on();      // "take over" all unasचिन्हित idle IRQs
 * 4. enable the device and cause it to trigger an पूर्णांकerrupt.
 * 5. रुको क्रम the device to पूर्णांकerrupt, using non-पूर्णांकrusive polling or a delay.
 * 6. irq = probe_irq_off(irqs);  // get IRQ number, 0=none, negative=multiple
 * 7. service the device to clear its pending पूर्णांकerrupt.
 * 8. loop again अगर paranoia is required.
 *
 * probe_irq_on() वापसs a mask of allocated irq's.
 *
 * probe_irq_off() takes the mask as a parameter,
 * and वापसs the irq number which occurred,
 * or zero अगर none occurred, or a negative irq number
 * अगर more than one irq occurred.
 */

#अगर !defined(CONFIG_GENERIC_IRQ_PROBE) 
अटल अंतरभूत अचिन्हित दीर्घ probe_irq_on(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक probe_irq_off(अचिन्हित दीर्घ val)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक probe_irq_mask(अचिन्हित दीर्घ val)
अणु
	वापस 0;
पूर्ण
#अन्यथा
बाह्य अचिन्हित दीर्घ probe_irq_on(व्योम);	/* वापसs 0 on failure */
बाह्य पूर्णांक probe_irq_off(अचिन्हित दीर्घ);	/* वापसs 0 or negative on failure */
बाह्य अचिन्हित पूर्णांक probe_irq_mask(अचिन्हित दीर्घ);	/* वापसs mask of ISA पूर्णांकerrupts */
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_FS
/* Initialize /proc/irq/ */
बाह्य व्योम init_irq_proc(व्योम);
#अन्यथा
अटल अंतरभूत व्योम init_irq_proc(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IRQ_TIMINGS
व्योम irq_timings_enable(व्योम);
व्योम irq_timings_disable(व्योम);
u64 irq_timings_next_event(u64 now);
#पूर्ण_अगर

काष्ठा seq_file;
पूर्णांक show_पूर्णांकerrupts(काष्ठा seq_file *p, व्योम *v);
पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec);

बाह्य पूर्णांक early_irq_init(व्योम);
बाह्य पूर्णांक arch_probe_nr_irqs(व्योम);
बाह्य पूर्णांक arch_early_irq_init(व्योम);

/*
 * We want to know which function is an entrypoपूर्णांक of a hardirq or a softirq.
 */
#अगर_अघोषित __irq_entry
# define __irq_entry	 __section(".irqentry.text")
#पूर्ण_अगर

#घोषणा __softirq_entry  __section(".softirqentry.text")

#पूर्ण_अगर
