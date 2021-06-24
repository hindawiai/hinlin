<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1992, 1998-2006 Linus Torvalds, Ingo Molnar
 * Copyright (C) 2005-2006 Thomas Gleixner
 *
 * This file contains driver APIs to the irq subप्रणाली.
 */

#घोषणा pr_fmt(fmt) "genirq: " fmt

#समावेश <linux/irq.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/rt.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/isolation.h>
#समावेश <uapi/linux/sched/types.h>
#समावेश <linux/task_work.h>

#समावेश "internals.h"

#अगर defined(CONFIG_IRQ_FORCED_THREADING) && !defined(CONFIG_PREEMPT_RT)
__पढ़ो_mostly bool क्रमce_irqthपढ़ोs;
EXPORT_SYMBOL_GPL(क्रमce_irqthपढ़ोs);

अटल पूर्णांक __init setup_क्रमced_irqthपढ़ोs(अक्षर *arg)
अणु
	क्रमce_irqthपढ़ोs = true;
	वापस 0;
पूर्ण
early_param("threadirqs", setup_क्रमced_irqthपढ़ोs);
#पूर्ण_अगर

अटल व्योम __synchronize_hardirq(काष्ठा irq_desc *desc, bool sync_chip)
अणु
	काष्ठा irq_data *irqd = irq_desc_get_irq_data(desc);
	bool inprogress;

	करो अणु
		अचिन्हित दीर्घ flags;

		/*
		 * Wait until we're out of the critical section.  This might
		 * give the wrong answer due to the lack of memory barriers.
		 */
		जबतक (irqd_irq_inprogress(&desc->irq_data))
			cpu_relax();

		/* Ok, that indicated we're करोne: द्विगुन-check carefully. */
		raw_spin_lock_irqsave(&desc->lock, flags);
		inprogress = irqd_irq_inprogress(&desc->irq_data);

		/*
		 * If requested and supported, check at the chip whether it
		 * is in flight at the hardware level, i.e. alपढ़ोy pending
		 * in a CPU and रुकोing क्रम service and acknowledge.
		 */
		अगर (!inprogress && sync_chip) अणु
			/*
			 * Ignore the वापस code. inprogress is only updated
			 * when the chip supports it.
			 */
			__irq_get_irqchip_state(irqd, IRQCHIP_STATE_ACTIVE,
						&inprogress);
		पूर्ण
		raw_spin_unlock_irqrestore(&desc->lock, flags);

		/* Oops, that failed? */
	पूर्ण जबतक (inprogress);
पूर्ण

/**
 *	synchronize_hardirq - रुको क्रम pending hard IRQ handlers (on other CPUs)
 *	@irq: पूर्णांकerrupt number to रुको क्रम
 *
 *	This function रुकोs क्रम any pending hard IRQ handlers क्रम this
 *	पूर्णांकerrupt to complete beक्रमe वापसing. If you use this
 *	function जबतक holding a resource the IRQ handler may need you
 *	will deadlock. It करोes not take associated thपढ़ोed handlers
 *	पूर्णांकo account.
 *
 *	Do not use this क्रम shutकरोwn scenarios where you must be sure
 *	that all parts (hardirq and thपढ़ोed handler) have completed.
 *
 *	Returns: false अगर a thपढ़ोed handler is active.
 *
 *	This function may be called - with care - from IRQ context.
 *
 *	It करोes not check whether there is an पूर्णांकerrupt in flight at the
 *	hardware level, but not serviced yet, as this might deadlock when
 *	called with पूर्णांकerrupts disabled and the target CPU of the पूर्णांकerrupt
 *	is the current CPU.
 */
bool synchronize_hardirq(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);

	अगर (desc) अणु
		__synchronize_hardirq(desc, false);
		वापस !atomic_पढ़ो(&desc->thपढ़ोs_active);
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(synchronize_hardirq);

/**
 *	synchronize_irq - रुको क्रम pending IRQ handlers (on other CPUs)
 *	@irq: पूर्णांकerrupt number to रुको क्रम
 *
 *	This function रुकोs क्रम any pending IRQ handlers क्रम this पूर्णांकerrupt
 *	to complete beक्रमe वापसing. If you use this function जबतक
 *	holding a resource the IRQ handler may need you will deadlock.
 *
 *	Can only be called from preemptible code as it might sleep when
 *	an पूर्णांकerrupt thपढ़ो is associated to @irq.
 *
 *	It optionally makes sure (when the irq chip supports that method)
 *	that the पूर्णांकerrupt is not pending in any CPU and रुकोing क्रम
 *	service.
 */
व्योम synchronize_irq(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);

	अगर (desc) अणु
		__synchronize_hardirq(desc, true);
		/*
		 * We made sure that no hardirq handler is
		 * running. Now verअगरy that no thपढ़ोed handlers are
		 * active.
		 */
		रुको_event(desc->रुको_क्रम_thपढ़ोs,
			   !atomic_पढ़ो(&desc->thपढ़ोs_active));
	पूर्ण
पूर्ण
EXPORT_SYMBOL(synchronize_irq);

#अगर_घोषित CONFIG_SMP
cpumask_var_t irq_शेष_affinity;

अटल bool __irq_can_set_affinity(काष्ठा irq_desc *desc)
अणु
	अगर (!desc || !irqd_can_balance(&desc->irq_data) ||
	    !desc->irq_data.chip || !desc->irq_data.chip->irq_set_affinity)
		वापस false;
	वापस true;
पूर्ण

/**
 *	irq_can_set_affinity - Check अगर the affinity of a given irq can be set
 *	@irq:		Interrupt to check
 *
 */
पूर्णांक irq_can_set_affinity(अचिन्हित पूर्णांक irq)
अणु
	वापस __irq_can_set_affinity(irq_to_desc(irq));
पूर्ण

/**
 * irq_can_set_affinity_usr - Check अगर affinity of a irq can be set from user space
 * @irq:	Interrupt to check
 *
 * Like irq_can_set_affinity() above, but additionally checks क्रम the
 * AFFINITY_MANAGED flag.
 */
bool irq_can_set_affinity_usr(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);

	वापस __irq_can_set_affinity(desc) &&
		!irqd_affinity_is_managed(&desc->irq_data);
पूर्ण

/**
 *	irq_set_thपढ़ो_affinity - Notअगरy irq thपढ़ोs to adjust affinity
 *	@desc:		irq descriptor which has affinity changed
 *
 *	We just set IRQTF_AFFINITY and delegate the affinity setting
 *	to the पूर्णांकerrupt thपढ़ो itself. We can not call
 *	set_cpus_allowed_ptr() here as we hold desc->lock and this
 *	code can be called from hard पूर्णांकerrupt context.
 */
व्योम irq_set_thपढ़ो_affinity(काष्ठा irq_desc *desc)
अणु
	काष्ठा irqaction *action;

	क्रम_each_action_of_desc(desc, action)
		अगर (action->thपढ़ो)
			set_bit(IRQTF_AFFINITY, &action->thपढ़ो_flags);
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK
अटल व्योम irq_validate_effective_affinity(काष्ठा irq_data *data)
अणु
	स्थिर काष्ठा cpumask *m = irq_data_get_effective_affinity_mask(data);
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(data);

	अगर (!cpumask_empty(m))
		वापस;
	pr_warn_once("irq_chip %s did not update eff. affinity mask of irq %u\n",
		     chip->name, data->irq);
पूर्ण

अटल अंतरभूत व्योम irq_init_effective_affinity(काष्ठा irq_data *data,
					       स्थिर काष्ठा cpumask *mask)
अणु
	cpumask_copy(irq_data_get_effective_affinity_mask(data), mask);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम irq_validate_effective_affinity(काष्ठा irq_data *data) अणु पूर्ण
अटल अंतरभूत व्योम irq_init_effective_affinity(काष्ठा irq_data *data,
					       स्थिर काष्ठा cpumask *mask) अणु पूर्ण
#पूर्ण_अगर

पूर्णांक irq_करो_set_affinity(काष्ठा irq_data *data, स्थिर काष्ठा cpumask *mask,
			bool क्रमce)
अणु
	काष्ठा irq_desc *desc = irq_data_to_desc(data);
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(data);
	पूर्णांक ret;

	अगर (!chip || !chip->irq_set_affinity)
		वापस -EINVAL;

	/*
	 * If this is a managed पूर्णांकerrupt and housekeeping is enabled on
	 * it check whether the requested affinity mask पूर्णांकersects with
	 * a housekeeping CPU. If so, then हटाओ the isolated CPUs from
	 * the mask and just keep the housekeeping CPU(s). This prevents
	 * the affinity setter from routing the पूर्णांकerrupt to an isolated
	 * CPU to aव्योम that I/O submitted from a housekeeping CPU causes
	 * पूर्णांकerrupts on an isolated one.
	 *
	 * If the masks करो not पूर्णांकersect or include online CPU(s) then
	 * keep the requested mask. The isolated target CPUs are only
	 * receiving पूर्णांकerrupts when the I/O operation was submitted
	 * directly from them.
	 *
	 * If all housekeeping CPUs in the affinity mask are offline, the
	 * पूर्णांकerrupt will be migrated by the CPU hotplug code once a
	 * housekeeping CPU which beदीर्घs to the affinity mask comes
	 * online.
	 */
	अगर (irqd_affinity_is_managed(data) &&
	    housekeeping_enabled(HK_FLAG_MANAGED_IRQ)) अणु
		स्थिर काष्ठा cpumask *hk_mask, *prog_mask;

		अटल DEFINE_RAW_SPINLOCK(पंचांगp_mask_lock);
		अटल काष्ठा cpumask पंचांगp_mask;

		hk_mask = housekeeping_cpumask(HK_FLAG_MANAGED_IRQ);

		raw_spin_lock(&पंचांगp_mask_lock);
		cpumask_and(&पंचांगp_mask, mask, hk_mask);
		अगर (!cpumask_पूर्णांकersects(&पंचांगp_mask, cpu_online_mask))
			prog_mask = mask;
		अन्यथा
			prog_mask = &पंचांगp_mask;
		ret = chip->irq_set_affinity(data, prog_mask, क्रमce);
		raw_spin_unlock(&पंचांगp_mask_lock);
	पूर्ण अन्यथा अणु
		ret = chip->irq_set_affinity(data, mask, क्रमce);
	पूर्ण
	चयन (ret) अणु
	हाल IRQ_SET_MASK_OK:
	हाल IRQ_SET_MASK_OK_DONE:
		cpumask_copy(desc->irq_common_data.affinity, mask);
		fallthrough;
	हाल IRQ_SET_MASK_OK_NOCOPY:
		irq_validate_effective_affinity(data);
		irq_set_thपढ़ो_affinity(desc);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_GENERIC_PENDING_IRQ
अटल अंतरभूत पूर्णांक irq_set_affinity_pending(काष्ठा irq_data *data,
					   स्थिर काष्ठा cpumask *dest)
अणु
	काष्ठा irq_desc *desc = irq_data_to_desc(data);

	irqd_set_move_pending(data);
	irq_copy_pending(desc, dest);
	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक irq_set_affinity_pending(काष्ठा irq_data *data,
					   स्थिर काष्ठा cpumask *dest)
अणु
	वापस -EBUSY;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक irq_try_set_affinity(काष्ठा irq_data *data,
				स्थिर काष्ठा cpumask *dest, bool क्रमce)
अणु
	पूर्णांक ret = irq_करो_set_affinity(data, dest, क्रमce);

	/*
	 * In हाल that the underlying vector management is busy and the
	 * architecture supports the generic pending mechanism then utilize
	 * this to aव्योम वापसing an error to user space.
	 */
	अगर (ret == -EBUSY && !क्रमce)
		ret = irq_set_affinity_pending(data, dest);
	वापस ret;
पूर्ण

अटल bool irq_set_affinity_deactivated(काष्ठा irq_data *data,
					 स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	काष्ठा irq_desc *desc = irq_data_to_desc(data);

	/*
	 * Handle irq chips which can handle affinity only in activated
	 * state correctly
	 *
	 * If the पूर्णांकerrupt is not yet activated, just store the affinity
	 * mask and करो not call the chip driver at all. On activation the
	 * driver has to make sure anyway that the पूर्णांकerrupt is in a
	 * usable state so startup works.
	 */
	अगर (!IS_ENABLED(CONFIG_IRQ_DOMAIN_HIERARCHY) ||
	    irqd_is_activated(data) || !irqd_affinity_on_activate(data))
		वापस false;

	cpumask_copy(desc->irq_common_data.affinity, mask);
	irq_init_effective_affinity(data, mask);
	irqd_set(data, IRQD_AFFINITY_SET);
	वापस true;
पूर्ण

पूर्णांक irq_set_affinity_locked(काष्ठा irq_data *data, स्थिर काष्ठा cpumask *mask,
			    bool क्रमce)
अणु
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(data);
	काष्ठा irq_desc *desc = irq_data_to_desc(data);
	पूर्णांक ret = 0;

	अगर (!chip || !chip->irq_set_affinity)
		वापस -EINVAL;

	अगर (irq_set_affinity_deactivated(data, mask, क्रमce))
		वापस 0;

	अगर (irq_can_move_pcntxt(data) && !irqd_is_setaffinity_pending(data)) अणु
		ret = irq_try_set_affinity(data, mask, क्रमce);
	पूर्ण अन्यथा अणु
		irqd_set_move_pending(data);
		irq_copy_pending(desc, mask);
	पूर्ण

	अगर (desc->affinity_notअगरy) अणु
		kref_get(&desc->affinity_notअगरy->kref);
		अगर (!schedule_work(&desc->affinity_notअगरy->work)) अणु
			/* Work was alपढ़ोy scheduled, drop our extra ref */
			kref_put(&desc->affinity_notअगरy->kref,
				 desc->affinity_notअगरy->release);
		पूर्ण
	पूर्ण
	irqd_set(data, IRQD_AFFINITY_SET);

	वापस ret;
पूर्ण

/**
 * irq_update_affinity_desc - Update affinity management क्रम an पूर्णांकerrupt
 * @irq:	The पूर्णांकerrupt number to update
 * @affinity:	Poपूर्णांकer to the affinity descriptor
 *
 * This पूर्णांकerface can be used to configure the affinity management of
 * पूर्णांकerrupts which have been allocated alपढ़ोy.
 *
 * There are certain limitations on when it may be used - attempts to use it
 * क्रम when the kernel is configured क्रम generic IRQ reservation mode (in
 * config GENERIC_IRQ_RESERVATION_MODE) will fail, as it may conflict with
 * managed/non-managed पूर्णांकerrupt accounting. In addition, attempts to use it on
 * an पूर्णांकerrupt which is alपढ़ोy started or which has alपढ़ोy been configured
 * as managed will also fail, as these mean invalid init state or द्विगुन init.
 */
पूर्णांक irq_update_affinity_desc(अचिन्हित पूर्णांक irq,
			     काष्ठा irq_affinity_desc *affinity)
अणु
	काष्ठा irq_desc *desc;
	अचिन्हित दीर्घ flags;
	bool activated;
	पूर्णांक ret = 0;

	/*
	 * Supporting this with the reservation scheme used by x86 needs
	 * some more thought. Fail it क्रम now.
	 */
	अगर (IS_ENABLED(CONFIG_GENERIC_IRQ_RESERVATION_MODE))
		वापस -EOPNOTSUPP;

	desc = irq_get_desc_buslock(irq, &flags, 0);
	अगर (!desc)
		वापस -EINVAL;

	/* Requires the पूर्णांकerrupt to be shut करोwn */
	अगर (irqd_is_started(&desc->irq_data)) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	/* Interrupts which are alपढ़ोy managed cannot be modअगरied */
	अगर (irqd_affinity_is_managed(&desc->irq_data)) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	/*
	 * Deactivate the पूर्णांकerrupt. That's required to unकरो
	 * anything an earlier activation has established.
	 */
	activated = irqd_is_activated(&desc->irq_data);
	अगर (activated)
		irq_करोमुख्य_deactivate_irq(&desc->irq_data);

	अगर (affinity->is_managed) अणु
		irqd_set(&desc->irq_data, IRQD_AFFINITY_MANAGED);
		irqd_set(&desc->irq_data, IRQD_MANAGED_SHUTDOWN);
	पूर्ण

	cpumask_copy(desc->irq_common_data.affinity, &affinity->mask);

	/* Restore the activation state */
	अगर (activated)
		irq_करोमुख्य_activate_irq(&desc->irq_data, false);

out_unlock:
	irq_put_desc_busunlock(desc, flags);
	वापस ret;
पूर्ण

पूर्णांक __irq_set_affinity(अचिन्हित पूर्णांक irq, स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!desc)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&desc->lock, flags);
	ret = irq_set_affinity_locked(irq_desc_get_irq_data(desc), mask, क्रमce);
	raw_spin_unlock_irqrestore(&desc->lock, flags);
	वापस ret;
पूर्ण

पूर्णांक irq_set_affinity_hपूर्णांक(अचिन्हित पूर्णांक irq, स्थिर काष्ठा cpumask *m)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_lock(irq, &flags, IRQ_GET_DESC_CHECK_GLOBAL);

	अगर (!desc)
		वापस -EINVAL;
	desc->affinity_hपूर्णांक = m;
	irq_put_desc_unlock(desc, flags);
	/* set the initial affinity to prevent every पूर्णांकerrupt being on CPU0 */
	अगर (m)
		__irq_set_affinity(irq, m, false);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(irq_set_affinity_hपूर्णांक);

अटल व्योम irq_affinity_notअगरy(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा irq_affinity_notअगरy *notअगरy =
		container_of(work, काष्ठा irq_affinity_notअगरy, work);
	काष्ठा irq_desc *desc = irq_to_desc(notअगरy->irq);
	cpumask_var_t cpumask;
	अचिन्हित दीर्घ flags;

	अगर (!desc || !alloc_cpumask_var(&cpumask, GFP_KERNEL))
		जाओ out;

	raw_spin_lock_irqsave(&desc->lock, flags);
	अगर (irq_move_pending(&desc->irq_data))
		irq_get_pending(cpumask, desc);
	अन्यथा
		cpumask_copy(cpumask, desc->irq_common_data.affinity);
	raw_spin_unlock_irqrestore(&desc->lock, flags);

	notअगरy->notअगरy(notअगरy, cpumask);

	मुक्त_cpumask_var(cpumask);
out:
	kref_put(&notअगरy->kref, notअगरy->release);
पूर्ण

/**
 *	irq_set_affinity_notअगरier - control notअगरication of IRQ affinity changes
 *	@irq:		Interrupt क्रम which to enable/disable notअगरication
 *	@notअगरy:	Context क्रम notअगरication, or %शून्य to disable
 *			notअगरication.  Function poपूर्णांकers must be initialised;
 *			the other fields will be initialised by this function.
 *
 *	Must be called in process context.  Notअगरication may only be enabled
 *	after the IRQ is allocated and must be disabled beक्रमe the IRQ is
 *	मुक्तd using मुक्त_irq().
 */
पूर्णांक
irq_set_affinity_notअगरier(अचिन्हित पूर्णांक irq, काष्ठा irq_affinity_notअगरy *notअगरy)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	काष्ठा irq_affinity_notअगरy *old_notअगरy;
	अचिन्हित दीर्घ flags;

	/* The release function is promised process context */
	might_sleep();

	अगर (!desc || desc->istate & IRQS_NMI)
		वापस -EINVAL;

	/* Complete initialisation of *notअगरy */
	अगर (notअगरy) अणु
		notअगरy->irq = irq;
		kref_init(&notअगरy->kref);
		INIT_WORK(&notअगरy->work, irq_affinity_notअगरy);
	पूर्ण

	raw_spin_lock_irqsave(&desc->lock, flags);
	old_notअगरy = desc->affinity_notअगरy;
	desc->affinity_notअगरy = notअगरy;
	raw_spin_unlock_irqrestore(&desc->lock, flags);

	अगर (old_notअगरy) अणु
		अगर (cancel_work_sync(&old_notअगरy->work)) अणु
			/* Pending work had a ref, put that one too */
			kref_put(&old_notअगरy->kref, old_notअगरy->release);
		पूर्ण
		kref_put(&old_notअगरy->kref, old_notअगरy->release);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(irq_set_affinity_notअगरier);

#अगर_अघोषित CONFIG_AUTO_IRQ_AFFINITY
/*
 * Generic version of the affinity स्वतःselector.
 */
पूर्णांक irq_setup_affinity(काष्ठा irq_desc *desc)
अणु
	काष्ठा cpumask *set = irq_शेष_affinity;
	पूर्णांक ret, node = irq_desc_get_node(desc);
	अटल DEFINE_RAW_SPINLOCK(mask_lock);
	अटल काष्ठा cpumask mask;

	/* Excludes PER_CPU and NO_BALANCE पूर्णांकerrupts */
	अगर (!__irq_can_set_affinity(desc))
		वापस 0;

	raw_spin_lock(&mask_lock);
	/*
	 * Preserve the managed affinity setting and a userspace affinity
	 * setup, but make sure that one of the tarमाला_लो is online.
	 */
	अगर (irqd_affinity_is_managed(&desc->irq_data) ||
	    irqd_has_set(&desc->irq_data, IRQD_AFFINITY_SET)) अणु
		अगर (cpumask_पूर्णांकersects(desc->irq_common_data.affinity,
				       cpu_online_mask))
			set = desc->irq_common_data.affinity;
		अन्यथा
			irqd_clear(&desc->irq_data, IRQD_AFFINITY_SET);
	पूर्ण

	cpumask_and(&mask, cpu_online_mask, set);
	अगर (cpumask_empty(&mask))
		cpumask_copy(&mask, cpu_online_mask);

	अगर (node != NUMA_NO_NODE) अणु
		स्थिर काष्ठा cpumask *nodemask = cpumask_of_node(node);

		/* make sure at least one of the cpus in nodemask is online */
		अगर (cpumask_पूर्णांकersects(&mask, nodemask))
			cpumask_and(&mask, &mask, nodemask);
	पूर्ण
	ret = irq_करो_set_affinity(&desc->irq_data, &mask, false);
	raw_spin_unlock(&mask_lock);
	वापस ret;
पूर्ण
#अन्यथा
/* Wrapper क्रम ALPHA specअगरic affinity selector magic */
पूर्णांक irq_setup_affinity(काष्ठा irq_desc *desc)
अणु
	वापस irq_select_affinity(irq_desc_get_irq(desc));
पूर्ण
#पूर्ण_अगर /* CONFIG_AUTO_IRQ_AFFINITY */
#पूर्ण_अगर /* CONFIG_SMP */


/**
 *	irq_set_vcpu_affinity - Set vcpu affinity क्रम the पूर्णांकerrupt
 *	@irq: पूर्णांकerrupt number to set affinity
 *	@vcpu_info: vCPU specअगरic data or poपूर्णांकer to a percpu array of vCPU
 *	            specअगरic data क्रम percpu_devid पूर्णांकerrupts
 *
 *	This function uses the vCPU specअगरic data to set the vCPU
 *	affinity क्रम an irq. The vCPU specअगरic data is passed from
 *	outside, such as KVM. One example code path is as below:
 *	KVM -> IOMMU -> irq_set_vcpu_affinity().
 */
पूर्णांक irq_set_vcpu_affinity(अचिन्हित पूर्णांक irq, व्योम *vcpu_info)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_lock(irq, &flags, 0);
	काष्ठा irq_data *data;
	काष्ठा irq_chip *chip;
	पूर्णांक ret = -ENOSYS;

	अगर (!desc)
		वापस -EINVAL;

	data = irq_desc_get_irq_data(desc);
	करो अणु
		chip = irq_data_get_irq_chip(data);
		अगर (chip && chip->irq_set_vcpu_affinity)
			अवरोध;
#अगर_घोषित CONFIG_IRQ_DOMAIN_HIERARCHY
		data = data->parent_data;
#अन्यथा
		data = शून्य;
#पूर्ण_अगर
	पूर्ण जबतक (data);

	अगर (data)
		ret = chip->irq_set_vcpu_affinity(data, vcpu_info);
	irq_put_desc_unlock(desc, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(irq_set_vcpu_affinity);

व्योम __disable_irq(काष्ठा irq_desc *desc)
अणु
	अगर (!desc->depth++)
		irq_disable(desc);
पूर्ण

अटल पूर्णांक __disable_irq_nosync(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_buslock(irq, &flags, IRQ_GET_DESC_CHECK_GLOBAL);

	अगर (!desc)
		वापस -EINVAL;
	__disable_irq(desc);
	irq_put_desc_busunlock(desc, flags);
	वापस 0;
पूर्ण

/**
 *	disable_irq_nosync - disable an irq without रुकोing
 *	@irq: Interrupt to disable
 *
 *	Disable the selected पूर्णांकerrupt line.  Disables and Enables are
 *	nested.
 *	Unlike disable_irq(), this function करोes not ensure existing
 *	instances of the IRQ handler have completed beक्रमe वापसing.
 *
 *	This function may be called from IRQ context.
 */
व्योम disable_irq_nosync(अचिन्हित पूर्णांक irq)
अणु
	__disable_irq_nosync(irq);
पूर्ण
EXPORT_SYMBOL(disable_irq_nosync);

/**
 *	disable_irq - disable an irq and रुको क्रम completion
 *	@irq: Interrupt to disable
 *
 *	Disable the selected पूर्णांकerrupt line.  Enables and Disables are
 *	nested.
 *	This function रुकोs क्रम any pending IRQ handlers क्रम this पूर्णांकerrupt
 *	to complete beक्रमe वापसing. If you use this function जबतक
 *	holding a resource the IRQ handler may need you will deadlock.
 *
 *	This function may be called - with care - from IRQ context.
 */
व्योम disable_irq(अचिन्हित पूर्णांक irq)
अणु
	अगर (!__disable_irq_nosync(irq))
		synchronize_irq(irq);
पूर्ण
EXPORT_SYMBOL(disable_irq);

/**
 *	disable_hardirq - disables an irq and रुकोs क्रम hardirq completion
 *	@irq: Interrupt to disable
 *
 *	Disable the selected पूर्णांकerrupt line.  Enables and Disables are
 *	nested.
 *	This function रुकोs क्रम any pending hard IRQ handlers क्रम this
 *	पूर्णांकerrupt to complete beक्रमe वापसing. If you use this function जबतक
 *	holding a resource the hard IRQ handler may need you will deadlock.
 *
 *	When used to optimistically disable an पूर्णांकerrupt from atomic context
 *	the वापस value must be checked.
 *
 *	Returns: false अगर a thपढ़ोed handler is active.
 *
 *	This function may be called - with care - from IRQ context.
 */
bool disable_hardirq(अचिन्हित पूर्णांक irq)
अणु
	अगर (!__disable_irq_nosync(irq))
		वापस synchronize_hardirq(irq);

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(disable_hardirq);

/**
 *	disable_nmi_nosync - disable an nmi without रुकोing
 *	@irq: Interrupt to disable
 *
 *	Disable the selected पूर्णांकerrupt line. Disables and enables are
 *	nested.
 *	The पूर्णांकerrupt to disable must have been requested through request_nmi.
 *	Unlike disable_nmi(), this function करोes not ensure existing
 *	instances of the IRQ handler have completed beक्रमe वापसing.
 */
व्योम disable_nmi_nosync(अचिन्हित पूर्णांक irq)
अणु
	disable_irq_nosync(irq);
पूर्ण

व्योम __enable_irq(काष्ठा irq_desc *desc)
अणु
	चयन (desc->depth) अणु
	हाल 0:
 err_out:
		WARN(1, KERN_WARNING "Unbalanced enable for IRQ %d\n",
		     irq_desc_get_irq(desc));
		अवरोध;
	हाल 1: अणु
		अगर (desc->istate & IRQS_SUSPENDED)
			जाओ err_out;
		/* Prevent probing on this irq: */
		irq_settings_set_noprobe(desc);
		/*
		 * Call irq_startup() not irq_enable() here because the
		 * पूर्णांकerrupt might be marked NOAUTOEN. So irq_startup()
		 * needs to be invoked when it माला_लो enabled the first
		 * समय. If it was alपढ़ोy started up, then irq_startup()
		 * will invoke irq_enable() under the hood.
		 */
		irq_startup(desc, IRQ_RESEND, IRQ_START_FORCE);
		अवरोध;
	पूर्ण
	शेष:
		desc->depth--;
	पूर्ण
पूर्ण

/**
 *	enable_irq - enable handling of an irq
 *	@irq: Interrupt to enable
 *
 *	Unकरोes the effect of one call to disable_irq().  If this
 *	matches the last disable, processing of पूर्णांकerrupts on this
 *	IRQ line is re-enabled.
 *
 *	This function may be called from IRQ context only when
 *	desc->irq_data.chip->bus_lock and desc->chip->bus_sync_unlock are शून्य !
 */
व्योम enable_irq(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_buslock(irq, &flags, IRQ_GET_DESC_CHECK_GLOBAL);

	अगर (!desc)
		वापस;
	अगर (WARN(!desc->irq_data.chip,
		 KERN_ERR "enable_irq before setup/request_irq: irq %u\n", irq))
		जाओ out;

	__enable_irq(desc);
out:
	irq_put_desc_busunlock(desc, flags);
पूर्ण
EXPORT_SYMBOL(enable_irq);

/**
 *	enable_nmi - enable handling of an nmi
 *	@irq: Interrupt to enable
 *
 *	The पूर्णांकerrupt to enable must have been requested through request_nmi.
 *	Unकरोes the effect of one call to disable_nmi(). If this
 *	matches the last disable, processing of पूर्णांकerrupts on this
 *	IRQ line is re-enabled.
 */
व्योम enable_nmi(अचिन्हित पूर्णांक irq)
अणु
	enable_irq(irq);
पूर्ण

अटल पूर्णांक set_irq_wake_real(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक on)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	पूर्णांक ret = -ENXIO;

	अगर (irq_desc_get_chip(desc)->flags &  IRQCHIP_SKIP_SET_WAKE)
		वापस 0;

	अगर (desc->irq_data.chip->irq_set_wake)
		ret = desc->irq_data.chip->irq_set_wake(&desc->irq_data, on);

	वापस ret;
पूर्ण

/**
 *	irq_set_irq_wake - control irq घातer management wakeup
 *	@irq:	पूर्णांकerrupt to control
 *	@on:	enable/disable घातer management wakeup
 *
 *	Enable/disable घातer management wakeup mode, which is
 *	disabled by शेष.  Enables and disables must match,
 *	just as they match क्रम non-wakeup mode support.
 *
 *	Wakeup mode lets this IRQ wake the प्रणाली from sleep
 *	states like "suspend to RAM".
 *
 *	Note: irq enable/disable state is completely orthogonal
 *	to the enable/disable state of irq wake. An irq can be
 *	disabled with disable_irq() and still wake the प्रणाली as
 *	दीर्घ as the irq has wake enabled. If this करोes not hold,
 *	then the underlying irq chip and the related driver need
 *	to be investigated.
 */
पूर्णांक irq_set_irq_wake(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक on)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_buslock(irq, &flags, IRQ_GET_DESC_CHECK_GLOBAL);
	पूर्णांक ret = 0;

	अगर (!desc)
		वापस -EINVAL;

	/* Don't use NMIs as wake up पूर्णांकerrupts please */
	अगर (desc->istate & IRQS_NMI) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	/* wakeup-capable irqs can be shared between drivers that
	 * करोn't need to have the same sleep mode behaviors.
	 */
	अगर (on) अणु
		अगर (desc->wake_depth++ == 0) अणु
			ret = set_irq_wake_real(irq, on);
			अगर (ret)
				desc->wake_depth = 0;
			अन्यथा
				irqd_set(&desc->irq_data, IRQD_WAKEUP_STATE);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (desc->wake_depth == 0) अणु
			WARN(1, "Unbalanced IRQ %d wake disable\n", irq);
		पूर्ण अन्यथा अगर (--desc->wake_depth == 0) अणु
			ret = set_irq_wake_real(irq, on);
			अगर (ret)
				desc->wake_depth = 1;
			अन्यथा
				irqd_clear(&desc->irq_data, IRQD_WAKEUP_STATE);
		पूर्ण
	पूर्ण

out_unlock:
	irq_put_desc_busunlock(desc, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(irq_set_irq_wake);

/*
 * Internal function that tells the architecture code whether a
 * particular irq has been exclusively allocated or is available
 * क्रम driver use.
 */
पूर्णांक can_request_irq(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ irqflags)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_lock(irq, &flags, 0);
	पूर्णांक canrequest = 0;

	अगर (!desc)
		वापस 0;

	अगर (irq_settings_can_request(desc)) अणु
		अगर (!desc->action ||
		    irqflags & desc->action->flags & IRQF_SHARED)
			canrequest = 1;
	पूर्ण
	irq_put_desc_unlock(desc, flags);
	वापस canrequest;
पूर्ण

पूर्णांक __irq_set_trigger(काष्ठा irq_desc *desc, अचिन्हित दीर्घ flags)
अणु
	काष्ठा irq_chip *chip = desc->irq_data.chip;
	पूर्णांक ret, unmask = 0;

	अगर (!chip || !chip->irq_set_type) अणु
		/*
		 * IRQF_TRIGGER_* but the PIC करोes not support multiple
		 * flow-types?
		 */
		pr_debug("No set_type function for IRQ %d (%s)\n",
			 irq_desc_get_irq(desc),
			 chip ? (chip->name ? : "unknown") : "unknown");
		वापस 0;
	पूर्ण

	अगर (chip->flags & IRQCHIP_SET_TYPE_MASKED) अणु
		अगर (!irqd_irq_masked(&desc->irq_data))
			mask_irq(desc);
		अगर (!irqd_irq_disabled(&desc->irq_data))
			unmask = 1;
	पूर्ण

	/* Mask all flags except trigger mode */
	flags &= IRQ_TYPE_SENSE_MASK;
	ret = chip->irq_set_type(&desc->irq_data, flags);

	चयन (ret) अणु
	हाल IRQ_SET_MASK_OK:
	हाल IRQ_SET_MASK_OK_DONE:
		irqd_clear(&desc->irq_data, IRQD_TRIGGER_MASK);
		irqd_set(&desc->irq_data, flags);
		fallthrough;

	हाल IRQ_SET_MASK_OK_NOCOPY:
		flags = irqd_get_trigger_type(&desc->irq_data);
		irq_settings_set_trigger_mask(desc, flags);
		irqd_clear(&desc->irq_data, IRQD_LEVEL);
		irq_settings_clr_level(desc);
		अगर (flags & IRQ_TYPE_LEVEL_MASK) अणु
			irq_settings_set_level(desc);
			irqd_set(&desc->irq_data, IRQD_LEVEL);
		पूर्ण

		ret = 0;
		अवरोध;
	शेष:
		pr_err("Setting trigger mode %lu for irq %u failed (%pS)\n",
		       flags, irq_desc_get_irq(desc), chip->irq_set_type);
	पूर्ण
	अगर (unmask)
		unmask_irq(desc);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_HARसूचीQS_SW_RESEND
पूर्णांक irq_set_parent(पूर्णांक irq, पूर्णांक parent_irq)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_lock(irq, &flags, 0);

	अगर (!desc)
		वापस -EINVAL;

	desc->parent_irq = parent_irq;

	irq_put_desc_unlock(desc, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(irq_set_parent);
#पूर्ण_अगर

/*
 * Default primary पूर्णांकerrupt handler क्रम thपढ़ोed पूर्णांकerrupts. Is
 * asचिन्हित as primary handler when request_thपढ़ोed_irq is called
 * with handler == शून्य. Useful क्रम oneshot पूर्णांकerrupts.
 */
अटल irqवापस_t irq_शेष_primary_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस IRQ_WAKE_THREAD;
पूर्ण

/*
 * Primary handler क्रम nested thपढ़ोed पूर्णांकerrupts. Should never be
 * called.
 */
अटल irqवापस_t irq_nested_primary_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	WARN(1, "Primary handler called for nested irq %d\n", irq);
	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t irq_क्रमced_secondary_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	WARN(1, "Secondary action handler called for irq %d\n", irq);
	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक irq_रुको_क्रम_पूर्णांकerrupt(काष्ठा irqaction *action)
अणु
	क्रम (;;) अणु
		set_current_state(TASK_INTERRUPTIBLE);

		अगर (kthपढ़ो_should_stop()) अणु
			/* may need to run one last समय */
			अगर (test_and_clear_bit(IRQTF_RUNTHREAD,
					       &action->thपढ़ो_flags)) अणु
				__set_current_state(TASK_RUNNING);
				वापस 0;
			पूर्ण
			__set_current_state(TASK_RUNNING);
			वापस -1;
		पूर्ण

		अगर (test_and_clear_bit(IRQTF_RUNTHREAD,
				       &action->thपढ़ो_flags)) अणु
			__set_current_state(TASK_RUNNING);
			वापस 0;
		पूर्ण
		schedule();
	पूर्ण
पूर्ण

/*
 * Oneshot पूर्णांकerrupts keep the irq line masked until the thपढ़ोed
 * handler finished. unmask अगर the पूर्णांकerrupt has not been disabled and
 * is marked MASKED.
 */
अटल व्योम irq_finalize_oneshot(काष्ठा irq_desc *desc,
				 काष्ठा irqaction *action)
अणु
	अगर (!(desc->istate & IRQS_ONESHOT) ||
	    action->handler == irq_क्रमced_secondary_handler)
		वापस;
again:
	chip_bus_lock(desc);
	raw_spin_lock_irq(&desc->lock);

	/*
	 * Implausible though it may be we need to protect us against
	 * the following scenario:
	 *
	 * The thपढ़ो is faster करोne than the hard पूर्णांकerrupt handler
	 * on the other CPU. If we unmask the irq line then the
	 * पूर्णांकerrupt can come in again and masks the line, leaves due
	 * to IRQS_INPROGRESS and the irq line is masked क्रमever.
	 *
	 * This also serializes the state of shared oneshot handlers
	 * versus "desc->threads_oneshot |= action->thread_mask;" in
	 * irq_wake_thपढ़ो(). See the comment there which explains the
	 * serialization.
	 */
	अगर (unlikely(irqd_irq_inprogress(&desc->irq_data))) अणु
		raw_spin_unlock_irq(&desc->lock);
		chip_bus_sync_unlock(desc);
		cpu_relax();
		जाओ again;
	पूर्ण

	/*
	 * Now check again, whether the thपढ़ो should run. Otherwise
	 * we would clear the thपढ़ोs_oneshot bit of this thपढ़ो which
	 * was just set.
	 */
	अगर (test_bit(IRQTF_RUNTHREAD, &action->thपढ़ो_flags))
		जाओ out_unlock;

	desc->thपढ़ोs_oneshot &= ~action->thपढ़ो_mask;

	अगर (!desc->thपढ़ोs_oneshot && !irqd_irq_disabled(&desc->irq_data) &&
	    irqd_irq_masked(&desc->irq_data))
		unmask_thपढ़ोed_irq(desc);

out_unlock:
	raw_spin_unlock_irq(&desc->lock);
	chip_bus_sync_unlock(desc);
पूर्ण

#अगर_घोषित CONFIG_SMP
/*
 * Check whether we need to change the affinity of the पूर्णांकerrupt thपढ़ो.
 */
अटल व्योम
irq_thपढ़ो_check_affinity(काष्ठा irq_desc *desc, काष्ठा irqaction *action)
अणु
	cpumask_var_t mask;
	bool valid = true;

	अगर (!test_and_clear_bit(IRQTF_AFFINITY, &action->thपढ़ो_flags))
		वापस;

	/*
	 * In हाल we are out of memory we set IRQTF_AFFINITY again and
	 * try again next समय
	 */
	अगर (!alloc_cpumask_var(&mask, GFP_KERNEL)) अणु
		set_bit(IRQTF_AFFINITY, &action->thपढ़ो_flags);
		वापस;
	पूर्ण

	raw_spin_lock_irq(&desc->lock);
	/*
	 * This code is triggered unconditionally. Check the affinity
	 * mask poपूर्णांकer. For CPU_MASK_OFFSTACK=n this is optimized out.
	 */
	अगर (cpumask_available(desc->irq_common_data.affinity)) अणु
		स्थिर काष्ठा cpumask *m;

		m = irq_data_get_effective_affinity_mask(&desc->irq_data);
		cpumask_copy(mask, m);
	पूर्ण अन्यथा अणु
		valid = false;
	पूर्ण
	raw_spin_unlock_irq(&desc->lock);

	अगर (valid)
		set_cpus_allowed_ptr(current, mask);
	मुक्त_cpumask_var(mask);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
irq_thपढ़ो_check_affinity(काष्ठा irq_desc *desc, काष्ठा irqaction *action) अणु पूर्ण
#पूर्ण_अगर

/*
 * Interrupts which are not explicitly requested as thपढ़ोed
 * पूर्णांकerrupts rely on the implicit bh/preempt disable of the hard irq
 * context. So we need to disable bh here to aव्योम deadlocks and other
 * side effects.
 */
अटल irqवापस_t
irq_क्रमced_thपढ़ो_fn(काष्ठा irq_desc *desc, काष्ठा irqaction *action)
अणु
	irqवापस_t ret;

	local_bh_disable();
	अगर (!IS_ENABLED(CONFIG_PREEMPT_RT))
		local_irq_disable();
	ret = action->thपढ़ो_fn(action->irq, action->dev_id);
	अगर (ret == IRQ_HANDLED)
		atomic_inc(&desc->thपढ़ोs_handled);

	irq_finalize_oneshot(desc, action);
	अगर (!IS_ENABLED(CONFIG_PREEMPT_RT))
		local_irq_enable();
	local_bh_enable();
	वापस ret;
पूर्ण

/*
 * Interrupts explicitly requested as thपढ़ोed पूर्णांकerrupts want to be
 * preemptible - many of them need to sleep and रुको क्रम slow busses to
 * complete.
 */
अटल irqवापस_t irq_thपढ़ो_fn(काष्ठा irq_desc *desc,
		काष्ठा irqaction *action)
अणु
	irqवापस_t ret;

	ret = action->thपढ़ो_fn(action->irq, action->dev_id);
	अगर (ret == IRQ_HANDLED)
		atomic_inc(&desc->thपढ़ोs_handled);

	irq_finalize_oneshot(desc, action);
	वापस ret;
पूर्ण

अटल व्योम wake_thपढ़ोs_रुकोq(काष्ठा irq_desc *desc)
अणु
	अगर (atomic_dec_and_test(&desc->thपढ़ोs_active))
		wake_up(&desc->रुको_क्रम_thपढ़ोs);
पूर्ण

अटल व्योम irq_thपढ़ो_dtor(काष्ठा callback_head *unused)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा irq_desc *desc;
	काष्ठा irqaction *action;

	अगर (WARN_ON_ONCE(!(current->flags & PF_EXITING)))
		वापस;

	action = kthपढ़ो_data(tsk);

	pr_err("exiting task \"%s\" (%d) is an active IRQ thread (irq %d)\n",
	       tsk->comm, tsk->pid, action->irq);


	desc = irq_to_desc(action->irq);
	/*
	 * If IRQTF_RUNTHREAD is set, we need to decrement
	 * desc->thपढ़ोs_active and wake possible रुकोers.
	 */
	अगर (test_and_clear_bit(IRQTF_RUNTHREAD, &action->thपढ़ो_flags))
		wake_thपढ़ोs_रुकोq(desc);

	/* Prevent a stale desc->thपढ़ोs_oneshot */
	irq_finalize_oneshot(desc, action);
पूर्ण

अटल व्योम irq_wake_secondary(काष्ठा irq_desc *desc, काष्ठा irqaction *action)
अणु
	काष्ठा irqaction *secondary = action->secondary;

	अगर (WARN_ON_ONCE(!secondary))
		वापस;

	raw_spin_lock_irq(&desc->lock);
	__irq_wake_thपढ़ो(desc, secondary);
	raw_spin_unlock_irq(&desc->lock);
पूर्ण

/*
 * Interrupt handler thपढ़ो
 */
अटल पूर्णांक irq_thपढ़ो(व्योम *data)
अणु
	काष्ठा callback_head on_निकास_work;
	काष्ठा irqaction *action = data;
	काष्ठा irq_desc *desc = irq_to_desc(action->irq);
	irqवापस_t (*handler_fn)(काष्ठा irq_desc *desc,
			काष्ठा irqaction *action);

	अगर (क्रमce_irqthपढ़ोs && test_bit(IRQTF_FORCED_THREAD,
					&action->thपढ़ो_flags))
		handler_fn = irq_क्रमced_thपढ़ो_fn;
	अन्यथा
		handler_fn = irq_thपढ़ो_fn;

	init_task_work(&on_निकास_work, irq_thपढ़ो_dtor);
	task_work_add(current, &on_निकास_work, TWA_NONE);

	irq_thपढ़ो_check_affinity(desc, action);

	जबतक (!irq_रुको_क्रम_पूर्णांकerrupt(action)) अणु
		irqवापस_t action_ret;

		irq_thपढ़ो_check_affinity(desc, action);

		action_ret = handler_fn(desc, action);
		अगर (action_ret == IRQ_WAKE_THREAD)
			irq_wake_secondary(desc, action);

		wake_thपढ़ोs_रुकोq(desc);
	पूर्ण

	/*
	 * This is the regular निकास path. __मुक्त_irq() is stopping the
	 * thपढ़ो via kthपढ़ो_stop() after calling
	 * synchronize_hardirq(). So neither IRQTF_RUNTHREAD nor the
	 * oneshot mask bit can be set.
	 */
	task_work_cancel(current, irq_thपढ़ो_dtor);
	वापस 0;
पूर्ण

/**
 *	irq_wake_thपढ़ो - wake the irq thपढ़ो क्रम the action identअगरied by dev_id
 *	@irq:		Interrupt line
 *	@dev_id:	Device identity क्रम which the thपढ़ो should be woken
 *
 */
व्योम irq_wake_thपढ़ो(अचिन्हित पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	काष्ठा irqaction *action;
	अचिन्हित दीर्घ flags;

	अगर (!desc || WARN_ON(irq_settings_is_per_cpu_devid(desc)))
		वापस;

	raw_spin_lock_irqsave(&desc->lock, flags);
	क्रम_each_action_of_desc(desc, action) अणु
		अगर (action->dev_id == dev_id) अणु
			अगर (action->thपढ़ो)
				__irq_wake_thपढ़ो(desc, action);
			अवरोध;
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&desc->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(irq_wake_thपढ़ो);

अटल पूर्णांक irq_setup_क्रमced_thपढ़ोing(काष्ठा irqaction *new)
अणु
	अगर (!क्रमce_irqthपढ़ोs)
		वापस 0;
	अगर (new->flags & (IRQF_NO_THREAD | IRQF_PERCPU | IRQF_ONESHOT))
		वापस 0;

	/*
	 * No further action required क्रम पूर्णांकerrupts which are requested as
	 * thपढ़ोed पूर्णांकerrupts alपढ़ोy
	 */
	अगर (new->handler == irq_शेष_primary_handler)
		वापस 0;

	new->flags |= IRQF_ONESHOT;

	/*
	 * Handle the हाल where we have a real primary handler and a
	 * thपढ़ो handler. We क्रमce thपढ़ो them as well by creating a
	 * secondary action.
	 */
	अगर (new->handler && new->thपढ़ो_fn) अणु
		/* Allocate the secondary action */
		new->secondary = kzalloc(माप(काष्ठा irqaction), GFP_KERNEL);
		अगर (!new->secondary)
			वापस -ENOMEM;
		new->secondary->handler = irq_क्रमced_secondary_handler;
		new->secondary->thपढ़ो_fn = new->thपढ़ो_fn;
		new->secondary->dev_id = new->dev_id;
		new->secondary->irq = new->irq;
		new->secondary->name = new->name;
	पूर्ण
	/* Deal with the primary handler */
	set_bit(IRQTF_FORCED_THREAD, &new->thपढ़ो_flags);
	new->thपढ़ो_fn = new->handler;
	new->handler = irq_शेष_primary_handler;
	वापस 0;
पूर्ण

अटल पूर्णांक irq_request_resources(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *d = &desc->irq_data;
	काष्ठा irq_chip *c = d->chip;

	वापस c->irq_request_resources ? c->irq_request_resources(d) : 0;
पूर्ण

अटल व्योम irq_release_resources(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *d = &desc->irq_data;
	काष्ठा irq_chip *c = d->chip;

	अगर (c->irq_release_resources)
		c->irq_release_resources(d);
पूर्ण

अटल bool irq_supports_nmi(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *d = irq_desc_get_irq_data(desc);

#अगर_घोषित CONFIG_IRQ_DOMAIN_HIERARCHY
	/* Only IRQs directly managed by the root irqchip can be set as NMI */
	अगर (d->parent_data)
		वापस false;
#पूर्ण_अगर
	/* Don't support NMIs क्रम chips behind a slow bus */
	अगर (d->chip->irq_bus_lock || d->chip->irq_bus_sync_unlock)
		वापस false;

	वापस d->chip->flags & IRQCHIP_SUPPORTS_NMI;
पूर्ण

अटल पूर्णांक irq_nmi_setup(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *d = irq_desc_get_irq_data(desc);
	काष्ठा irq_chip *c = d->chip;

	वापस c->irq_nmi_setup ? c->irq_nmi_setup(d) : -EINVAL;
पूर्ण

अटल व्योम irq_nmi_tearकरोwn(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *d = irq_desc_get_irq_data(desc);
	काष्ठा irq_chip *c = d->chip;

	अगर (c->irq_nmi_tearकरोwn)
		c->irq_nmi_tearकरोwn(d);
पूर्ण

अटल पूर्णांक
setup_irq_thपढ़ो(काष्ठा irqaction *new, अचिन्हित पूर्णांक irq, bool secondary)
अणु
	काष्ठा task_काष्ठा *t;

	अगर (!secondary) अणु
		t = kthपढ़ो_create(irq_thपढ़ो, new, "irq/%d-%s", irq,
				   new->name);
	पूर्ण अन्यथा अणु
		t = kthपढ़ो_create(irq_thपढ़ो, new, "irq/%d-s-%s", irq,
				   new->name);
	पूर्ण

	अगर (IS_ERR(t))
		वापस PTR_ERR(t);

	sched_set_fअगरo(t);

	/*
	 * We keep the reference to the task काष्ठा even अगर
	 * the thपढ़ो dies to aव्योम that the पूर्णांकerrupt code
	 * references an alपढ़ोy मुक्तd task_काष्ठा.
	 */
	new->thपढ़ो = get_task_काष्ठा(t);
	/*
	 * Tell the thपढ़ो to set its affinity. This is
	 * important क्रम shared पूर्णांकerrupt handlers as we करो
	 * not invoke setup_affinity() क्रम the secondary
	 * handlers as everything is alपढ़ोy set up. Even क्रम
	 * पूर्णांकerrupts marked with IRQF_NO_BALANCE this is
	 * correct as we want the thपढ़ो to move to the cpu(s)
	 * on which the requesting code placed the पूर्णांकerrupt.
	 */
	set_bit(IRQTF_AFFINITY, &new->thपढ़ो_flags);
	वापस 0;
पूर्ण

/*
 * Internal function to रेजिस्टर an irqaction - typically used to
 * allocate special पूर्णांकerrupts that are part of the architecture.
 *
 * Locking rules:
 *
 * desc->request_mutex	Provides serialization against a concurrent मुक्त_irq()
 *   chip_bus_lock	Provides serialization क्रम slow bus operations
 *     desc->lock	Provides serialization against hard पूर्णांकerrupts
 *
 * chip_bus_lock and desc->lock are sufficient क्रम all other management and
 * पूर्णांकerrupt related functions. desc->request_mutex solely serializes
 * request/मुक्त_irq().
 */
अटल पूर्णांक
__setup_irq(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *desc, काष्ठा irqaction *new)
अणु
	काष्ठा irqaction *old, **old_ptr;
	अचिन्हित दीर्घ flags, thपढ़ो_mask = 0;
	पूर्णांक ret, nested, shared = 0;

	अगर (!desc)
		वापस -EINVAL;

	अगर (desc->irq_data.chip == &no_irq_chip)
		वापस -ENOSYS;
	अगर (!try_module_get(desc->owner))
		वापस -ENODEV;

	new->irq = irq;

	/*
	 * If the trigger type is not specअगरied by the caller,
	 * then use the शेष क्रम this पूर्णांकerrupt.
	 */
	अगर (!(new->flags & IRQF_TRIGGER_MASK))
		new->flags |= irqd_get_trigger_type(&desc->irq_data);

	/*
	 * Check whether the पूर्णांकerrupt nests पूर्णांकo another पूर्णांकerrupt
	 * thपढ़ो.
	 */
	nested = irq_settings_is_nested_thपढ़ो(desc);
	अगर (nested) अणु
		अगर (!new->thपढ़ो_fn) अणु
			ret = -EINVAL;
			जाओ out_mput;
		पूर्ण
		/*
		 * Replace the primary handler which was provided from
		 * the driver क्रम non nested पूर्णांकerrupt handling by the
		 * dummy function which warns when called.
		 */
		new->handler = irq_nested_primary_handler;
	पूर्ण अन्यथा अणु
		अगर (irq_settings_can_thपढ़ो(desc)) अणु
			ret = irq_setup_क्रमced_thपढ़ोing(new);
			अगर (ret)
				जाओ out_mput;
		पूर्ण
	पूर्ण

	/*
	 * Create a handler thपढ़ो when a thपढ़ो function is supplied
	 * and the पूर्णांकerrupt करोes not nest पूर्णांकo another पूर्णांकerrupt
	 * thपढ़ो.
	 */
	अगर (new->thपढ़ो_fn && !nested) अणु
		ret = setup_irq_thपढ़ो(new, irq, false);
		अगर (ret)
			जाओ out_mput;
		अगर (new->secondary) अणु
			ret = setup_irq_thपढ़ो(new->secondary, irq, true);
			अगर (ret)
				जाओ out_thपढ़ो;
		पूर्ण
	पूर्ण

	/*
	 * Drivers are often written to work w/o knowledge about the
	 * underlying irq chip implementation, so a request क्रम a
	 * thपढ़ोed irq without a primary hard irq context handler
	 * requires the ONESHOT flag to be set. Some irq chips like
	 * MSI based पूर्णांकerrupts are per se one shot safe. Check the
	 * chip flags, so we can aव्योम the unmask dance at the end of
	 * the thपढ़ोed handler क्रम those.
	 */
	अगर (desc->irq_data.chip->flags & IRQCHIP_ONESHOT_SAFE)
		new->flags &= ~IRQF_ONESHOT;

	/*
	 * Protects against a concurrent __मुक्त_irq() call which might रुको
	 * क्रम synchronize_hardirq() to complete without holding the optional
	 * chip bus lock and desc->lock. Also protects against handing out
	 * a recycled oneshot thपढ़ो_mask bit जबतक it's still in use by
	 * its previous owner.
	 */
	mutex_lock(&desc->request_mutex);

	/*
	 * Acquire bus lock as the irq_request_resources() callback below
	 * might rely on the serialization or the magic घातer management
	 * functions which are abusing the irq_bus_lock() callback,
	 */
	chip_bus_lock(desc);

	/* First installed action requests resources. */
	अगर (!desc->action) अणु
		ret = irq_request_resources(desc);
		अगर (ret) अणु
			pr_err("Failed to request resources for %s (irq %d) on irqchip %s\n",
			       new->name, irq, desc->irq_data.chip->name);
			जाओ out_bus_unlock;
		पूर्ण
	पूर्ण

	/*
	 * The following block of code has to be executed atomically
	 * रक्षित against a concurrent पूर्णांकerrupt and any of the other
	 * management calls which are not serialized via
	 * desc->request_mutex or the optional bus lock.
	 */
	raw_spin_lock_irqsave(&desc->lock, flags);
	old_ptr = &desc->action;
	old = *old_ptr;
	अगर (old) अणु
		/*
		 * Can't share पूर्णांकerrupts unless both agree to and are
		 * the same type (level, edge, polarity). So both flag
		 * fields must have IRQF_SHARED set and the bits which
		 * set the trigger type must match. Also all must
		 * agree on ONESHOT.
		 * Interrupt lines used क्रम NMIs cannot be shared.
		 */
		अचिन्हित पूर्णांक oldtype;

		अगर (desc->istate & IRQS_NMI) अणु
			pr_err("Invalid attempt to share NMI for %s (irq %d) on irqchip %s.\n",
				new->name, irq, desc->irq_data.chip->name);
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		/*
		 * If nobody did set the configuration beक्रमe, inherit
		 * the one provided by the requester.
		 */
		अगर (irqd_trigger_type_was_set(&desc->irq_data)) अणु
			oldtype = irqd_get_trigger_type(&desc->irq_data);
		पूर्ण अन्यथा अणु
			oldtype = new->flags & IRQF_TRIGGER_MASK;
			irqd_set_trigger_type(&desc->irq_data, oldtype);
		पूर्ण

		अगर (!((old->flags & new->flags) & IRQF_SHARED) ||
		    (oldtype != (new->flags & IRQF_TRIGGER_MASK)) ||
		    ((old->flags ^ new->flags) & IRQF_ONESHOT))
			जाओ mismatch;

		/* All handlers must agree on per-cpuness */
		अगर ((old->flags & IRQF_PERCPU) !=
		    (new->flags & IRQF_PERCPU))
			जाओ mismatch;

		/* add new पूर्णांकerrupt at end of irq queue */
		करो अणु
			/*
			 * Or all existing action->thपढ़ो_mask bits,
			 * so we can find the next zero bit क्रम this
			 * new action.
			 */
			thपढ़ो_mask |= old->thपढ़ो_mask;
			old_ptr = &old->next;
			old = *old_ptr;
		पूर्ण जबतक (old);
		shared = 1;
	पूर्ण

	/*
	 * Setup the thपढ़ो mask क्रम this irqaction क्रम ONESHOT. For
	 * !ONESHOT irqs the thपढ़ो mask is 0 so we can aव्योम a
	 * conditional in irq_wake_thपढ़ो().
	 */
	अगर (new->flags & IRQF_ONESHOT) अणु
		/*
		 * Unlikely to have 32 resp 64 irqs sharing one line,
		 * but who knows.
		 */
		अगर (thपढ़ो_mask == ~0UL) अणु
			ret = -EBUSY;
			जाओ out_unlock;
		पूर्ण
		/*
		 * The thपढ़ो_mask क्रम the action is or'ed to
		 * desc->thपढ़ो_active to indicate that the
		 * IRQF_ONESHOT thपढ़ो handler has been woken, but not
		 * yet finished. The bit is cleared when a thपढ़ो
		 * completes. When all thपढ़ोs of a shared पूर्णांकerrupt
		 * line have completed desc->thपढ़ोs_active becomes
		 * zero and the पूर्णांकerrupt line is unmasked. See
		 * handle.c:irq_wake_thपढ़ो() क्रम further inक्रमmation.
		 *
		 * If no thपढ़ो is woken by primary (hard irq context)
		 * पूर्णांकerrupt handlers, then desc->thपढ़ोs_active is
		 * also checked क्रम zero to unmask the irq line in the
		 * affected hard irq flow handlers
		 * (handle_[fasteoi|level]_irq).
		 *
		 * The new action माला_लो the first zero bit of
		 * thपढ़ो_mask asचिन्हित. See the loop above which or's
		 * all existing action->thपढ़ो_mask bits.
		 */
		new->thपढ़ो_mask = 1UL << ffz(thपढ़ो_mask);

	पूर्ण अन्यथा अगर (new->handler == irq_शेष_primary_handler &&
		   !(desc->irq_data.chip->flags & IRQCHIP_ONESHOT_SAFE)) अणु
		/*
		 * The पूर्णांकerrupt was requested with handler = शून्य, so
		 * we use the शेष primary handler क्रम it. But it
		 * करोes not have the oneshot flag set. In combination
		 * with level पूर्णांकerrupts this is deadly, because the
		 * शेष primary handler just wakes the thपढ़ो, then
		 * the irq lines is reenabled, but the device still
		 * has the level irq निश्चितed. Rinse and repeat....
		 *
		 * While this works क्रम edge type पूर्णांकerrupts, we play
		 * it safe and reject unconditionally because we can't
		 * say क्रम sure which type this पूर्णांकerrupt really
		 * has. The type flags are unreliable as the
		 * underlying chip implementation can override them.
		 */
		pr_err("Threaded irq requested with handler=NULL and !ONESHOT for %s (irq %d)\n",
		       new->name, irq);
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (!shared) अणु
		init_रुकोqueue_head(&desc->रुको_क्रम_thपढ़ोs);

		/* Setup the type (level, edge polarity) अगर configured: */
		अगर (new->flags & IRQF_TRIGGER_MASK) अणु
			ret = __irq_set_trigger(desc,
						new->flags & IRQF_TRIGGER_MASK);

			अगर (ret)
				जाओ out_unlock;
		पूर्ण

		/*
		 * Activate the पूर्णांकerrupt. That activation must happen
		 * independently of IRQ_NOAUTOEN. request_irq() can fail
		 * and the callers are supposed to handle
		 * that. enable_irq() of an पूर्णांकerrupt requested with
		 * IRQ_NOAUTOEN is not supposed to fail. The activation
		 * keeps it in shutकरोwn mode, it merily associates
		 * resources अगर necessary and अगर that's not possible it
		 * fails. Interrupts which are in managed shutकरोwn mode
		 * will simply ignore that activation request.
		 */
		ret = irq_activate(desc);
		अगर (ret)
			जाओ out_unlock;

		desc->istate &= ~(IRQS_AUTODETECT | IRQS_SPURIOUS_DISABLED | \
				  IRQS_ONESHOT | IRQS_WAITING);
		irqd_clear(&desc->irq_data, IRQD_IRQ_INPROGRESS);

		अगर (new->flags & IRQF_PERCPU) अणु
			irqd_set(&desc->irq_data, IRQD_PER_CPU);
			irq_settings_set_per_cpu(desc);
		पूर्ण

		अगर (new->flags & IRQF_ONESHOT)
			desc->istate |= IRQS_ONESHOT;

		/* Exclude IRQ from balancing अगर requested */
		अगर (new->flags & IRQF_NOBALANCING) अणु
			irq_settings_set_no_balancing(desc);
			irqd_set(&desc->irq_data, IRQD_NO_BALANCING);
		पूर्ण

		अगर (!(new->flags & IRQF_NO_AUTOEN) &&
		    irq_settings_can_स्वतःenable(desc)) अणु
			irq_startup(desc, IRQ_RESEND, IRQ_START_COND);
		पूर्ण अन्यथा अणु
			/*
			 * Shared पूर्णांकerrupts करो not go well with disabling
			 * स्वतः enable. The sharing पूर्णांकerrupt might request
			 * it जबतक it's still disabled and then रुको क्रम
			 * पूर्णांकerrupts क्रमever.
			 */
			WARN_ON_ONCE(new->flags & IRQF_SHARED);
			/* Unकरो nested disables: */
			desc->depth = 1;
		पूर्ण

	पूर्ण अन्यथा अगर (new->flags & IRQF_TRIGGER_MASK) अणु
		अचिन्हित पूर्णांक nmsk = new->flags & IRQF_TRIGGER_MASK;
		अचिन्हित पूर्णांक omsk = irqd_get_trigger_type(&desc->irq_data);

		अगर (nmsk != omsk)
			/* hope the handler works with current  trigger mode */
			pr_warn("irq %d uses trigger mode %u; requested %u\n",
				irq, omsk, nmsk);
	पूर्ण

	*old_ptr = new;

	irq_pm_install_action(desc, new);

	/* Reset broken irq detection when installing new handler */
	desc->irq_count = 0;
	desc->irqs_unhandled = 0;

	/*
	 * Check whether we disabled the irq via the spurious handler
	 * beक्रमe. Reenable it and give it another chance.
	 */
	अगर (shared && (desc->istate & IRQS_SPURIOUS_DISABLED)) अणु
		desc->istate &= ~IRQS_SPURIOUS_DISABLED;
		__enable_irq(desc);
	पूर्ण

	raw_spin_unlock_irqrestore(&desc->lock, flags);
	chip_bus_sync_unlock(desc);
	mutex_unlock(&desc->request_mutex);

	irq_setup_timings(desc, new);

	/*
	 * Strictly no need to wake it up, but hung_task complains
	 * when no hard पूर्णांकerrupt wakes the thपढ़ो up.
	 */
	अगर (new->thपढ़ो)
		wake_up_process(new->thपढ़ो);
	अगर (new->secondary)
		wake_up_process(new->secondary->thपढ़ो);

	रेजिस्टर_irq_proc(irq, desc);
	new->dir = शून्य;
	रेजिस्टर_handler_proc(irq, new);
	वापस 0;

mismatch:
	अगर (!(new->flags & IRQF_PROBE_SHARED)) अणु
		pr_err("Flags mismatch irq %d. %08x (%s) vs. %08x (%s)\n",
		       irq, new->flags, new->name, old->flags, old->name);
#अगर_घोषित CONFIG_DEBUG_SHIRQ
		dump_stack();
#पूर्ण_अगर
	पूर्ण
	ret = -EBUSY;

out_unlock:
	raw_spin_unlock_irqrestore(&desc->lock, flags);

	अगर (!desc->action)
		irq_release_resources(desc);
out_bus_unlock:
	chip_bus_sync_unlock(desc);
	mutex_unlock(&desc->request_mutex);

out_thपढ़ो:
	अगर (new->thपढ़ो) अणु
		काष्ठा task_काष्ठा *t = new->thपढ़ो;

		new->thपढ़ो = शून्य;
		kthपढ़ो_stop(t);
		put_task_काष्ठा(t);
	पूर्ण
	अगर (new->secondary && new->secondary->thपढ़ो) अणु
		काष्ठा task_काष्ठा *t = new->secondary->thपढ़ो;

		new->secondary->thपढ़ो = शून्य;
		kthपढ़ो_stop(t);
		put_task_काष्ठा(t);
	पूर्ण
out_mput:
	module_put(desc->owner);
	वापस ret;
पूर्ण

/*
 * Internal function to unरेजिस्टर an irqaction - used to मुक्त
 * regular and special पूर्णांकerrupts that are part of the architecture.
 */
अटल काष्ठा irqaction *__मुक्त_irq(काष्ठा irq_desc *desc, व्योम *dev_id)
अणु
	अचिन्हित irq = desc->irq_data.irq;
	काष्ठा irqaction *action, **action_ptr;
	अचिन्हित दीर्घ flags;

	WARN(in_पूर्णांकerrupt(), "Trying to free IRQ %d from IRQ context!\n", irq);

	mutex_lock(&desc->request_mutex);
	chip_bus_lock(desc);
	raw_spin_lock_irqsave(&desc->lock, flags);

	/*
	 * There can be multiple actions per IRQ descriptor, find the right
	 * one based on the dev_id:
	 */
	action_ptr = &desc->action;
	क्रम (;;) अणु
		action = *action_ptr;

		अगर (!action) अणु
			WARN(1, "Trying to free already-free IRQ %d\n", irq);
			raw_spin_unlock_irqrestore(&desc->lock, flags);
			chip_bus_sync_unlock(desc);
			mutex_unlock(&desc->request_mutex);
			वापस शून्य;
		पूर्ण

		अगर (action->dev_id == dev_id)
			अवरोध;
		action_ptr = &action->next;
	पूर्ण

	/* Found it - now हटाओ it from the list of entries: */
	*action_ptr = action->next;

	irq_pm_हटाओ_action(desc, action);

	/* If this was the last handler, shut करोwn the IRQ line: */
	अगर (!desc->action) अणु
		irq_settings_clr_disable_unlazy(desc);
		/* Only shutकरोwn. Deactivate after synchronize_hardirq() */
		irq_shutकरोwn(desc);
	पूर्ण

#अगर_घोषित CONFIG_SMP
	/* make sure affinity_hपूर्णांक is cleaned up */
	अगर (WARN_ON_ONCE(desc->affinity_hपूर्णांक))
		desc->affinity_hपूर्णांक = शून्य;
#पूर्ण_अगर

	raw_spin_unlock_irqrestore(&desc->lock, flags);
	/*
	 * Drop bus_lock here so the changes which were करोne in the chip
	 * callbacks above are synced out to the irq chips which hang
	 * behind a slow bus (I2C, SPI) beक्रमe calling synchronize_hardirq().
	 *
	 * Aside of that the bus_lock can also be taken from the thपढ़ोed
	 * handler in irq_finalize_oneshot() which results in a deadlock
	 * because kthपढ़ो_stop() would रुको क्रमever क्रम the thपढ़ो to
	 * complete, which is blocked on the bus lock.
	 *
	 * The still held desc->request_mutex() protects against a
	 * concurrent request_irq() of this irq so the release of resources
	 * and timing data is properly serialized.
	 */
	chip_bus_sync_unlock(desc);

	unरेजिस्टर_handler_proc(irq, action);

	/*
	 * Make sure it's not being used on another CPU and अगर the chip
	 * supports it also make sure that there is no (not yet serviced)
	 * पूर्णांकerrupt in flight at the hardware level.
	 */
	__synchronize_hardirq(desc, true);

#अगर_घोषित CONFIG_DEBUG_SHIRQ
	/*
	 * It's a shared IRQ -- the driver ought to be prepared क्रम an IRQ
	 * event to happen even now it's being freed, so let's make sure that
	 * is so by करोing an extra call to the handler ....
	 *
	 * ( We करो this after actually deरेजिस्टरing it, to make sure that a
	 *   'real' IRQ doesn't run in parallel with our fake. )
	 */
	अगर (action->flags & IRQF_SHARED) अणु
		local_irq_save(flags);
		action->handler(irq, dev_id);
		local_irq_restore(flags);
	पूर्ण
#पूर्ण_अगर

	/*
	 * The action has alपढ़ोy been हटाओd above, but the thपढ़ो ग_लिखोs
	 * its oneshot mask bit when it completes. Though request_mutex is
	 * held across this which prevents __setup_irq() from handing out
	 * the same bit to a newly requested action.
	 */
	अगर (action->thपढ़ो) अणु
		kthपढ़ो_stop(action->thपढ़ो);
		put_task_काष्ठा(action->thपढ़ो);
		अगर (action->secondary && action->secondary->thपढ़ो) अणु
			kthपढ़ो_stop(action->secondary->thपढ़ो);
			put_task_काष्ठा(action->secondary->thपढ़ो);
		पूर्ण
	पूर्ण

	/* Last action releases resources */
	अगर (!desc->action) अणु
		/*
		 * Reacquire bus lock as irq_release_resources() might
		 * require it to deallocate resources over the slow bus.
		 */
		chip_bus_lock(desc);
		/*
		 * There is no पूर्णांकerrupt on the fly anymore. Deactivate it
		 * completely.
		 */
		raw_spin_lock_irqsave(&desc->lock, flags);
		irq_करोमुख्य_deactivate_irq(&desc->irq_data);
		raw_spin_unlock_irqrestore(&desc->lock, flags);

		irq_release_resources(desc);
		chip_bus_sync_unlock(desc);
		irq_हटाओ_timings(desc);
	पूर्ण

	mutex_unlock(&desc->request_mutex);

	irq_chip_pm_put(&desc->irq_data);
	module_put(desc->owner);
	kमुक्त(action->secondary);
	वापस action;
पूर्ण

/**
 *	मुक्त_irq - मुक्त an पूर्णांकerrupt allocated with request_irq
 *	@irq: Interrupt line to मुक्त
 *	@dev_id: Device identity to मुक्त
 *
 *	Remove an पूर्णांकerrupt handler. The handler is हटाओd and अगर the
 *	पूर्णांकerrupt line is no दीर्घer in use by any driver it is disabled.
 *	On a shared IRQ the caller must ensure the पूर्णांकerrupt is disabled
 *	on the card it drives beक्रमe calling this function. The function
 *	करोes not वापस until any executing पूर्णांकerrupts क्रम this IRQ
 *	have completed.
 *
 *	This function must not be called from पूर्णांकerrupt context.
 *
 *	Returns the devname argument passed to request_irq.
 */
स्थिर व्योम *मुक्त_irq(अचिन्हित पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	काष्ठा irqaction *action;
	स्थिर अक्षर *devname;

	अगर (!desc || WARN_ON(irq_settings_is_per_cpu_devid(desc)))
		वापस शून्य;

#अगर_घोषित CONFIG_SMP
	अगर (WARN_ON(desc->affinity_notअगरy))
		desc->affinity_notअगरy = शून्य;
#पूर्ण_अगर

	action = __मुक्त_irq(desc, dev_id);

	अगर (!action)
		वापस शून्य;

	devname = action->name;
	kमुक्त(action);
	वापस devname;
पूर्ण
EXPORT_SYMBOL(मुक्त_irq);

/* This function must be called with desc->lock held */
अटल स्थिर व्योम *__cleanup_nmi(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *desc)
अणु
	स्थिर अक्षर *devname = शून्य;

	desc->istate &= ~IRQS_NMI;

	अगर (!WARN_ON(desc->action == शून्य)) अणु
		irq_pm_हटाओ_action(desc, desc->action);
		devname = desc->action->name;
		unरेजिस्टर_handler_proc(irq, desc->action);

		kमुक्त(desc->action);
		desc->action = शून्य;
	पूर्ण

	irq_settings_clr_disable_unlazy(desc);
	irq_shutकरोwn_and_deactivate(desc);

	irq_release_resources(desc);

	irq_chip_pm_put(&desc->irq_data);
	module_put(desc->owner);

	वापस devname;
पूर्ण

स्थिर व्योम *मुक्त_nmi(अचिन्हित पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	अचिन्हित दीर्घ flags;
	स्थिर व्योम *devname;

	अगर (!desc || WARN_ON(!(desc->istate & IRQS_NMI)))
		वापस शून्य;

	अगर (WARN_ON(irq_settings_is_per_cpu_devid(desc)))
		वापस शून्य;

	/* NMI still enabled */
	अगर (WARN_ON(desc->depth == 0))
		disable_nmi_nosync(irq);

	raw_spin_lock_irqsave(&desc->lock, flags);

	irq_nmi_tearकरोwn(desc);
	devname = __cleanup_nmi(irq, desc);

	raw_spin_unlock_irqrestore(&desc->lock, flags);

	वापस devname;
पूर्ण

/**
 *	request_thपढ़ोed_irq - allocate an पूर्णांकerrupt line
 *	@irq: Interrupt line to allocate
 *	@handler: Function to be called when the IRQ occurs.
 *		  Primary handler क्रम thपढ़ोed पूर्णांकerrupts
 *		  If शून्य and thपढ़ो_fn != शून्य the शेष
 *		  primary handler is installed
 *	@thपढ़ो_fn: Function called from the irq handler thपढ़ो
 *		    If शून्य, no irq thपढ़ो is created
 *	@irqflags: Interrupt type flags
 *	@devname: An ascii name क्रम the claiming device
 *	@dev_id: A cookie passed back to the handler function
 *
 *	This call allocates पूर्णांकerrupt resources and enables the
 *	पूर्णांकerrupt line and IRQ handling. From the poपूर्णांक this
 *	call is made your handler function may be invoked. Since
 *	your handler function must clear any पूर्णांकerrupt the board
 *	उठाओs, you must take care both to initialise your hardware
 *	and to set up the पूर्णांकerrupt handler in the right order.
 *
 *	If you want to set up a thपढ़ोed irq handler क्रम your device
 *	then you need to supply @handler and @thपढ़ो_fn. @handler is
 *	still called in hard पूर्णांकerrupt context and has to check
 *	whether the पूर्णांकerrupt originates from the device. If yes it
 *	needs to disable the पूर्णांकerrupt on the device and वापस
 *	IRQ_WAKE_THREAD which will wake up the handler thपढ़ो and run
 *	@thपढ़ो_fn. This split handler design is necessary to support
 *	shared पूर्णांकerrupts.
 *
 *	Dev_id must be globally unique. Normally the address of the
 *	device data काष्ठाure is used as the cookie. Since the handler
 *	receives this value it makes sense to use it.
 *
 *	If your पूर्णांकerrupt is shared you must pass a non शून्य dev_id
 *	as this is required when मुक्तing the पूर्णांकerrupt.
 *
 *	Flags:
 *
 *	IRQF_SHARED		Interrupt is shared
 *	IRQF_TRIGGER_*		Specअगरy active edge(s) or level
 *
 */
पूर्णांक request_thपढ़ोed_irq(अचिन्हित पूर्णांक irq, irq_handler_t handler,
			 irq_handler_t thपढ़ो_fn, अचिन्हित दीर्घ irqflags,
			 स्थिर अक्षर *devname, व्योम *dev_id)
अणु
	काष्ठा irqaction *action;
	काष्ठा irq_desc *desc;
	पूर्णांक retval;

	अगर (irq == IRQ_NOTCONNECTED)
		वापस -ENOTCONN;

	/*
	 * Sanity-check: shared पूर्णांकerrupts must pass in a real dev-ID,
	 * otherwise we'll have trouble later trying to figure out
	 * which पूर्णांकerrupt is which (messes up the पूर्णांकerrupt मुक्तing
	 * logic etc).
	 *
	 * Also shared पूर्णांकerrupts करो not go well with disabling स्वतः enable.
	 * The sharing पूर्णांकerrupt might request it जबतक it's still disabled
	 * and then रुको क्रम पूर्णांकerrupts क्रमever.
	 *
	 * Also IRQF_COND_SUSPEND only makes sense क्रम shared पूर्णांकerrupts and
	 * it cannot be set aदीर्घ with IRQF_NO_SUSPEND.
	 */
	अगर (((irqflags & IRQF_SHARED) && !dev_id) ||
	    ((irqflags & IRQF_SHARED) && (irqflags & IRQF_NO_AUTOEN)) ||
	    (!(irqflags & IRQF_SHARED) && (irqflags & IRQF_COND_SUSPEND)) ||
	    ((irqflags & IRQF_NO_SUSPEND) && (irqflags & IRQF_COND_SUSPEND)))
		वापस -EINVAL;

	desc = irq_to_desc(irq);
	अगर (!desc)
		वापस -EINVAL;

	अगर (!irq_settings_can_request(desc) ||
	    WARN_ON(irq_settings_is_per_cpu_devid(desc)))
		वापस -EINVAL;

	अगर (!handler) अणु
		अगर (!thपढ़ो_fn)
			वापस -EINVAL;
		handler = irq_शेष_primary_handler;
	पूर्ण

	action = kzalloc(माप(काष्ठा irqaction), GFP_KERNEL);
	अगर (!action)
		वापस -ENOMEM;

	action->handler = handler;
	action->thपढ़ो_fn = thपढ़ो_fn;
	action->flags = irqflags;
	action->name = devname;
	action->dev_id = dev_id;

	retval = irq_chip_pm_get(&desc->irq_data);
	अगर (retval < 0) अणु
		kमुक्त(action);
		वापस retval;
	पूर्ण

	retval = __setup_irq(irq, desc, action);

	अगर (retval) अणु
		irq_chip_pm_put(&desc->irq_data);
		kमुक्त(action->secondary);
		kमुक्त(action);
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_SHIRQ_FIXME
	अगर (!retval && (irqflags & IRQF_SHARED)) अणु
		/*
		 * It's a shared IRQ -- the driver ought to be prepared क्रम it
		 * to happen immediately, so let's make sure....
		 * We disable the irq to make sure that a 'real' IRQ doesn't
		 * run in parallel with our fake.
		 */
		अचिन्हित दीर्घ flags;

		disable_irq(irq);
		local_irq_save(flags);

		handler(irq, dev_id);

		local_irq_restore(flags);
		enable_irq(irq);
	पूर्ण
#पूर्ण_अगर
	वापस retval;
पूर्ण
EXPORT_SYMBOL(request_thपढ़ोed_irq);

/**
 *	request_any_context_irq - allocate an पूर्णांकerrupt line
 *	@irq: Interrupt line to allocate
 *	@handler: Function to be called when the IRQ occurs.
 *		  Thपढ़ोed handler क्रम thपढ़ोed पूर्णांकerrupts.
 *	@flags: Interrupt type flags
 *	@name: An ascii name क्रम the claiming device
 *	@dev_id: A cookie passed back to the handler function
 *
 *	This call allocates पूर्णांकerrupt resources and enables the
 *	पूर्णांकerrupt line and IRQ handling. It selects either a
 *	hardirq or thपढ़ोed handling method depending on the
 *	context.
 *
 *	On failure, it वापसs a negative value. On success,
 *	it वापसs either IRQC_IS_HARसूचीQ or IRQC_IS_NESTED.
 */
पूर्णांक request_any_context_irq(अचिन्हित पूर्णांक irq, irq_handler_t handler,
			    अचिन्हित दीर्घ flags, स्थिर अक्षर *name, व्योम *dev_id)
अणु
	काष्ठा irq_desc *desc;
	पूर्णांक ret;

	अगर (irq == IRQ_NOTCONNECTED)
		वापस -ENOTCONN;

	desc = irq_to_desc(irq);
	अगर (!desc)
		वापस -EINVAL;

	अगर (irq_settings_is_nested_thपढ़ो(desc)) अणु
		ret = request_thपढ़ोed_irq(irq, शून्य, handler,
					   flags, name, dev_id);
		वापस !ret ? IRQC_IS_NESTED : ret;
	पूर्ण

	ret = request_irq(irq, handler, flags, name, dev_id);
	वापस !ret ? IRQC_IS_HARसूचीQ : ret;
पूर्ण
EXPORT_SYMBOL_GPL(request_any_context_irq);

/**
 *	request_nmi - allocate an पूर्णांकerrupt line क्रम NMI delivery
 *	@irq: Interrupt line to allocate
 *	@handler: Function to be called when the IRQ occurs.
 *		  Thपढ़ोed handler क्रम thपढ़ोed पूर्णांकerrupts.
 *	@irqflags: Interrupt type flags
 *	@name: An ascii name क्रम the claiming device
 *	@dev_id: A cookie passed back to the handler function
 *
 *	This call allocates पूर्णांकerrupt resources and enables the
 *	पूर्णांकerrupt line and IRQ handling. It sets up the IRQ line
 *	to be handled as an NMI.
 *
 *	An पूर्णांकerrupt line delivering NMIs cannot be shared and IRQ handling
 *	cannot be thपढ़ोed.
 *
 *	Interrupt lines requested क्रम NMI delivering must produce per cpu
 *	पूर्णांकerrupts and have स्वतः enabling setting disabled.
 *
 *	Dev_id must be globally unique. Normally the address of the
 *	device data काष्ठाure is used as the cookie. Since the handler
 *	receives this value it makes sense to use it.
 *
 *	If the पूर्णांकerrupt line cannot be used to deliver NMIs, function
 *	will fail and वापस a negative value.
 */
पूर्णांक request_nmi(अचिन्हित पूर्णांक irq, irq_handler_t handler,
		अचिन्हित दीर्घ irqflags, स्थिर अक्षर *name, व्योम *dev_id)
अणु
	काष्ठा irqaction *action;
	काष्ठा irq_desc *desc;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	अगर (irq == IRQ_NOTCONNECTED)
		वापस -ENOTCONN;

	/* NMI cannot be shared, used क्रम Polling */
	अगर (irqflags & (IRQF_SHARED | IRQF_COND_SUSPEND | IRQF_IRQPOLL))
		वापस -EINVAL;

	अगर (!(irqflags & IRQF_PERCPU))
		वापस -EINVAL;

	अगर (!handler)
		वापस -EINVAL;

	desc = irq_to_desc(irq);

	अगर (!desc || (irq_settings_can_स्वतःenable(desc) &&
	    !(irqflags & IRQF_NO_AUTOEN)) ||
	    !irq_settings_can_request(desc) ||
	    WARN_ON(irq_settings_is_per_cpu_devid(desc)) ||
	    !irq_supports_nmi(desc))
		वापस -EINVAL;

	action = kzalloc(माप(काष्ठा irqaction), GFP_KERNEL);
	अगर (!action)
		वापस -ENOMEM;

	action->handler = handler;
	action->flags = irqflags | IRQF_NO_THREAD | IRQF_NOBALANCING;
	action->name = name;
	action->dev_id = dev_id;

	retval = irq_chip_pm_get(&desc->irq_data);
	अगर (retval < 0)
		जाओ err_out;

	retval = __setup_irq(irq, desc, action);
	अगर (retval)
		जाओ err_irq_setup;

	raw_spin_lock_irqsave(&desc->lock, flags);

	/* Setup NMI state */
	desc->istate |= IRQS_NMI;
	retval = irq_nmi_setup(desc);
	अगर (retval) अणु
		__cleanup_nmi(irq, desc);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
		वापस -EINVAL;
	पूर्ण

	raw_spin_unlock_irqrestore(&desc->lock, flags);

	वापस 0;

err_irq_setup:
	irq_chip_pm_put(&desc->irq_data);
err_out:
	kमुक्त(action);

	वापस retval;
पूर्ण

व्योम enable_percpu_irq(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_lock(irq, &flags, IRQ_GET_DESC_CHECK_PERCPU);

	अगर (!desc)
		वापस;

	/*
	 * If the trigger type is not specअगरied by the caller, then
	 * use the शेष क्रम this पूर्णांकerrupt.
	 */
	type &= IRQ_TYPE_SENSE_MASK;
	अगर (type == IRQ_TYPE_NONE)
		type = irqd_get_trigger_type(&desc->irq_data);

	अगर (type != IRQ_TYPE_NONE) अणु
		पूर्णांक ret;

		ret = __irq_set_trigger(desc, type);

		अगर (ret) अणु
			WARN(1, "failed to set type for IRQ%d\n", irq);
			जाओ out;
		पूर्ण
	पूर्ण

	irq_percpu_enable(desc, cpu);
out:
	irq_put_desc_unlock(desc, flags);
पूर्ण
EXPORT_SYMBOL_GPL(enable_percpu_irq);

व्योम enable_percpu_nmi(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक type)
अणु
	enable_percpu_irq(irq, type);
पूर्ण

/**
 * irq_percpu_is_enabled - Check whether the per cpu irq is enabled
 * @irq:	Linux irq number to check क्रम
 *
 * Must be called from a non migratable context. Returns the enable
 * state of a per cpu पूर्णांकerrupt on the current cpu.
 */
bool irq_percpu_is_enabled(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा irq_desc *desc;
	अचिन्हित दीर्घ flags;
	bool is_enabled;

	desc = irq_get_desc_lock(irq, &flags, IRQ_GET_DESC_CHECK_PERCPU);
	अगर (!desc)
		वापस false;

	is_enabled = cpumask_test_cpu(cpu, desc->percpu_enabled);
	irq_put_desc_unlock(desc, flags);

	वापस is_enabled;
पूर्ण
EXPORT_SYMBOL_GPL(irq_percpu_is_enabled);

व्योम disable_percpu_irq(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_lock(irq, &flags, IRQ_GET_DESC_CHECK_PERCPU);

	अगर (!desc)
		वापस;

	irq_percpu_disable(desc, cpu);
	irq_put_desc_unlock(desc, flags);
पूर्ण
EXPORT_SYMBOL_GPL(disable_percpu_irq);

व्योम disable_percpu_nmi(अचिन्हित पूर्णांक irq)
अणु
	disable_percpu_irq(irq);
पूर्ण

/*
 * Internal function to unरेजिस्टर a percpu irqaction.
 */
अटल काष्ठा irqaction *__मुक्त_percpu_irq(अचिन्हित पूर्णांक irq, व्योम __percpu *dev_id)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	काष्ठा irqaction *action;
	अचिन्हित दीर्घ flags;

	WARN(in_पूर्णांकerrupt(), "Trying to free IRQ %d from IRQ context!\n", irq);

	अगर (!desc)
		वापस शून्य;

	raw_spin_lock_irqsave(&desc->lock, flags);

	action = desc->action;
	अगर (!action || action->percpu_dev_id != dev_id) अणु
		WARN(1, "Trying to free already-free IRQ %d\n", irq);
		जाओ bad;
	पूर्ण

	अगर (!cpumask_empty(desc->percpu_enabled)) अणु
		WARN(1, "percpu IRQ %d still enabled on CPU%d!\n",
		     irq, cpumask_first(desc->percpu_enabled));
		जाओ bad;
	पूर्ण

	/* Found it - now हटाओ it from the list of entries: */
	desc->action = शून्य;

	desc->istate &= ~IRQS_NMI;

	raw_spin_unlock_irqrestore(&desc->lock, flags);

	unरेजिस्टर_handler_proc(irq, action);

	irq_chip_pm_put(&desc->irq_data);
	module_put(desc->owner);
	वापस action;

bad:
	raw_spin_unlock_irqrestore(&desc->lock, flags);
	वापस शून्य;
पूर्ण

/**
 *	हटाओ_percpu_irq - मुक्त a per-cpu पूर्णांकerrupt
 *	@irq: Interrupt line to मुक्त
 *	@act: irqaction क्रम the पूर्णांकerrupt
 *
 * Used to हटाओ पूर्णांकerrupts अटलally setup by the early boot process.
 */
व्योम हटाओ_percpu_irq(अचिन्हित पूर्णांक irq, काष्ठा irqaction *act)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);

	अगर (desc && irq_settings_is_per_cpu_devid(desc))
	    __मुक्त_percpu_irq(irq, act->percpu_dev_id);
पूर्ण

/**
 *	मुक्त_percpu_irq - मुक्त an पूर्णांकerrupt allocated with request_percpu_irq
 *	@irq: Interrupt line to मुक्त
 *	@dev_id: Device identity to मुक्त
 *
 *	Remove a percpu पूर्णांकerrupt handler. The handler is हटाओd, but
 *	the पूर्णांकerrupt line is not disabled. This must be करोne on each
 *	CPU beक्रमe calling this function. The function करोes not वापस
 *	until any executing पूर्णांकerrupts क्रम this IRQ have completed.
 *
 *	This function must not be called from पूर्णांकerrupt context.
 */
व्योम मुक्त_percpu_irq(अचिन्हित पूर्णांक irq, व्योम __percpu *dev_id)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);

	अगर (!desc || !irq_settings_is_per_cpu_devid(desc))
		वापस;

	chip_bus_lock(desc);
	kमुक्त(__मुक्त_percpu_irq(irq, dev_id));
	chip_bus_sync_unlock(desc);
पूर्ण
EXPORT_SYMBOL_GPL(मुक्त_percpu_irq);

व्योम मुक्त_percpu_nmi(अचिन्हित पूर्णांक irq, व्योम __percpu *dev_id)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);

	अगर (!desc || !irq_settings_is_per_cpu_devid(desc))
		वापस;

	अगर (WARN_ON(!(desc->istate & IRQS_NMI)))
		वापस;

	kमुक्त(__मुक्त_percpu_irq(irq, dev_id));
पूर्ण

/**
 *	setup_percpu_irq - setup a per-cpu पूर्णांकerrupt
 *	@irq: Interrupt line to setup
 *	@act: irqaction क्रम the पूर्णांकerrupt
 *
 * Used to अटलally setup per-cpu पूर्णांकerrupts in the early boot process.
 */
पूर्णांक setup_percpu_irq(अचिन्हित पूर्णांक irq, काष्ठा irqaction *act)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	पूर्णांक retval;

	अगर (!desc || !irq_settings_is_per_cpu_devid(desc))
		वापस -EINVAL;

	retval = irq_chip_pm_get(&desc->irq_data);
	अगर (retval < 0)
		वापस retval;

	retval = __setup_irq(irq, desc, act);

	अगर (retval)
		irq_chip_pm_put(&desc->irq_data);

	वापस retval;
पूर्ण

/**
 *	__request_percpu_irq - allocate a percpu पूर्णांकerrupt line
 *	@irq: Interrupt line to allocate
 *	@handler: Function to be called when the IRQ occurs.
 *	@flags: Interrupt type flags (IRQF_TIMER only)
 *	@devname: An ascii name क्रम the claiming device
 *	@dev_id: A percpu cookie passed back to the handler function
 *
 *	This call allocates पूर्णांकerrupt resources and enables the
 *	पूर्णांकerrupt on the local CPU. If the पूर्णांकerrupt is supposed to be
 *	enabled on other CPUs, it has to be करोne on each CPU using
 *	enable_percpu_irq().
 *
 *	Dev_id must be globally unique. It is a per-cpu variable, and
 *	the handler माला_लो called with the पूर्णांकerrupted CPU's instance of
 *	that variable.
 */
पूर्णांक __request_percpu_irq(अचिन्हित पूर्णांक irq, irq_handler_t handler,
			 अचिन्हित दीर्घ flags, स्थिर अक्षर *devname,
			 व्योम __percpu *dev_id)
अणु
	काष्ठा irqaction *action;
	काष्ठा irq_desc *desc;
	पूर्णांक retval;

	अगर (!dev_id)
		वापस -EINVAL;

	desc = irq_to_desc(irq);
	अगर (!desc || !irq_settings_can_request(desc) ||
	    !irq_settings_is_per_cpu_devid(desc))
		वापस -EINVAL;

	अगर (flags && flags != IRQF_TIMER)
		वापस -EINVAL;

	action = kzalloc(माप(काष्ठा irqaction), GFP_KERNEL);
	अगर (!action)
		वापस -ENOMEM;

	action->handler = handler;
	action->flags = flags | IRQF_PERCPU | IRQF_NO_SUSPEND;
	action->name = devname;
	action->percpu_dev_id = dev_id;

	retval = irq_chip_pm_get(&desc->irq_data);
	अगर (retval < 0) अणु
		kमुक्त(action);
		वापस retval;
	पूर्ण

	retval = __setup_irq(irq, desc, action);

	अगर (retval) अणु
		irq_chip_pm_put(&desc->irq_data);
		kमुक्त(action);
	पूर्ण

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(__request_percpu_irq);

/**
 *	request_percpu_nmi - allocate a percpu पूर्णांकerrupt line क्रम NMI delivery
 *	@irq: Interrupt line to allocate
 *	@handler: Function to be called when the IRQ occurs.
 *	@name: An ascii name क्रम the claiming device
 *	@dev_id: A percpu cookie passed back to the handler function
 *
 *	This call allocates पूर्णांकerrupt resources क्रम a per CPU NMI. Per CPU NMIs
 *	have to be setup on each CPU by calling prepare_percpu_nmi() beक्रमe
 *	being enabled on the same CPU by using enable_percpu_nmi().
 *
 *	Dev_id must be globally unique. It is a per-cpu variable, and
 *	the handler माला_लो called with the पूर्णांकerrupted CPU's instance of
 *	that variable.
 *
 *	Interrupt lines requested क्रम NMI delivering should have स्वतः enabling
 *	setting disabled.
 *
 *	If the पूर्णांकerrupt line cannot be used to deliver NMIs, function
 *	will fail वापसing a negative value.
 */
पूर्णांक request_percpu_nmi(अचिन्हित पूर्णांक irq, irq_handler_t handler,
		       स्थिर अक्षर *name, व्योम __percpu *dev_id)
अणु
	काष्ठा irqaction *action;
	काष्ठा irq_desc *desc;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	अगर (!handler)
		वापस -EINVAL;

	desc = irq_to_desc(irq);

	अगर (!desc || !irq_settings_can_request(desc) ||
	    !irq_settings_is_per_cpu_devid(desc) ||
	    irq_settings_can_स्वतःenable(desc) ||
	    !irq_supports_nmi(desc))
		वापस -EINVAL;

	/* The line cannot alपढ़ोy be NMI */
	अगर (desc->istate & IRQS_NMI)
		वापस -EINVAL;

	action = kzalloc(माप(काष्ठा irqaction), GFP_KERNEL);
	अगर (!action)
		वापस -ENOMEM;

	action->handler = handler;
	action->flags = IRQF_PERCPU | IRQF_NO_SUSPEND | IRQF_NO_THREAD
		| IRQF_NOBALANCING;
	action->name = name;
	action->percpu_dev_id = dev_id;

	retval = irq_chip_pm_get(&desc->irq_data);
	अगर (retval < 0)
		जाओ err_out;

	retval = __setup_irq(irq, desc, action);
	अगर (retval)
		जाओ err_irq_setup;

	raw_spin_lock_irqsave(&desc->lock, flags);
	desc->istate |= IRQS_NMI;
	raw_spin_unlock_irqrestore(&desc->lock, flags);

	वापस 0;

err_irq_setup:
	irq_chip_pm_put(&desc->irq_data);
err_out:
	kमुक्त(action);

	वापस retval;
पूर्ण

/**
 *	prepare_percpu_nmi - perक्रमms CPU local setup क्रम NMI delivery
 *	@irq: Interrupt line to prepare क्रम NMI delivery
 *
 *	This call prepares an पूर्णांकerrupt line to deliver NMI on the current CPU,
 *	beक्रमe that पूर्णांकerrupt line माला_लो enabled with enable_percpu_nmi().
 *
 *	As a CPU local operation, this should be called from non-preemptible
 *	context.
 *
 *	If the पूर्णांकerrupt line cannot be used to deliver NMIs, function
 *	will fail वापसing a negative value.
 */
पूर्णांक prepare_percpu_nmi(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc;
	पूर्णांक ret = 0;

	WARN_ON(preemptible());

	desc = irq_get_desc_lock(irq, &flags,
				 IRQ_GET_DESC_CHECK_PERCPU);
	अगर (!desc)
		वापस -EINVAL;

	अगर (WARN(!(desc->istate & IRQS_NMI),
		 KERN_ERR "prepare_percpu_nmi called for a non-NMI interrupt: irq %u\n",
		 irq)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = irq_nmi_setup(desc);
	अगर (ret) अणु
		pr_err("Failed to setup NMI delivery: irq %u\n", irq);
		जाओ out;
	पूर्ण

out:
	irq_put_desc_unlock(desc, flags);
	वापस ret;
पूर्ण

/**
 *	tearकरोwn_percpu_nmi - unकरोes NMI setup of IRQ line
 *	@irq: Interrupt line from which CPU local NMI configuration should be
 *	      हटाओd
 *
 *	This call unकरोes the setup करोne by prepare_percpu_nmi().
 *
 *	IRQ line should not be enabled क्रम the current CPU.
 *
 *	As a CPU local operation, this should be called from non-preemptible
 *	context.
 */
व्योम tearकरोwn_percpu_nmi(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc;

	WARN_ON(preemptible());

	desc = irq_get_desc_lock(irq, &flags,
				 IRQ_GET_DESC_CHECK_PERCPU);
	अगर (!desc)
		वापस;

	अगर (WARN_ON(!(desc->istate & IRQS_NMI)))
		जाओ out;

	irq_nmi_tearकरोwn(desc);
out:
	irq_put_desc_unlock(desc, flags);
पूर्ण

पूर्णांक __irq_get_irqchip_state(काष्ठा irq_data *data, क्रमागत irqchip_irq_state which,
			    bool *state)
अणु
	काष्ठा irq_chip *chip;
	पूर्णांक err = -EINVAL;

	करो अणु
		chip = irq_data_get_irq_chip(data);
		अगर (WARN_ON_ONCE(!chip))
			वापस -ENODEV;
		अगर (chip->irq_get_irqchip_state)
			अवरोध;
#अगर_घोषित CONFIG_IRQ_DOMAIN_HIERARCHY
		data = data->parent_data;
#अन्यथा
		data = शून्य;
#पूर्ण_अगर
	पूर्ण जबतक (data);

	अगर (data)
		err = chip->irq_get_irqchip_state(data, which, state);
	वापस err;
पूर्ण

/**
 *	irq_get_irqchip_state - वापसs the irqchip state of a पूर्णांकerrupt.
 *	@irq: Interrupt line that is क्रमwarded to a VM
 *	@which: One of IRQCHIP_STATE_* the caller wants to know about
 *	@state: a poपूर्णांकer to a boolean where the state is to be stored
 *
 *	This call snapshots the पूर्णांकernal irqchip state of an
 *	पूर्णांकerrupt, वापसing पूर्णांकo @state the bit corresponding to
 *	stage @which
 *
 *	This function should be called with preemption disabled अगर the
 *	पूर्णांकerrupt controller has per-cpu रेजिस्टरs.
 */
पूर्णांक irq_get_irqchip_state(अचिन्हित पूर्णांक irq, क्रमागत irqchip_irq_state which,
			  bool *state)
अणु
	काष्ठा irq_desc *desc;
	काष्ठा irq_data *data;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -EINVAL;

	desc = irq_get_desc_buslock(irq, &flags, 0);
	अगर (!desc)
		वापस err;

	data = irq_desc_get_irq_data(desc);

	err = __irq_get_irqchip_state(data, which, state);

	irq_put_desc_busunlock(desc, flags);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(irq_get_irqchip_state);

/**
 *	irq_set_irqchip_state - set the state of a क्रमwarded पूर्णांकerrupt.
 *	@irq: Interrupt line that is क्रमwarded to a VM
 *	@which: State to be restored (one of IRQCHIP_STATE_*)
 *	@val: Value corresponding to @which
 *
 *	This call sets the पूर्णांकernal irqchip state of an पूर्णांकerrupt,
 *	depending on the value of @which.
 *
 *	This function should be called with preemption disabled अगर the
 *	पूर्णांकerrupt controller has per-cpu रेजिस्टरs.
 */
पूर्णांक irq_set_irqchip_state(अचिन्हित पूर्णांक irq, क्रमागत irqchip_irq_state which,
			  bool val)
अणु
	काष्ठा irq_desc *desc;
	काष्ठा irq_data *data;
	काष्ठा irq_chip *chip;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -EINVAL;

	desc = irq_get_desc_buslock(irq, &flags, 0);
	अगर (!desc)
		वापस err;

	data = irq_desc_get_irq_data(desc);

	करो अणु
		chip = irq_data_get_irq_chip(data);
		अगर (WARN_ON_ONCE(!chip)) अणु
			err = -ENODEV;
			जाओ out_unlock;
		पूर्ण
		अगर (chip->irq_set_irqchip_state)
			अवरोध;
#अगर_घोषित CONFIG_IRQ_DOMAIN_HIERARCHY
		data = data->parent_data;
#अन्यथा
		data = शून्य;
#पूर्ण_अगर
	पूर्ण जबतक (data);

	अगर (data)
		err = chip->irq_set_irqchip_state(data, which, val);

out_unlock:
	irq_put_desc_busunlock(desc, flags);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(irq_set_irqchip_state);

/**
 * irq_has_action - Check whether an पूर्णांकerrupt is requested
 * @irq:	The linux irq number
 *
 * Returns: A snapshot of the current state
 */
bool irq_has_action(अचिन्हित पूर्णांक irq)
अणु
	bool res;

	rcu_पढ़ो_lock();
	res = irq_desc_has_action(irq_to_desc(irq));
	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(irq_has_action);

/**
 * irq_check_status_bit - Check whether bits in the irq descriptor status are set
 * @irq:	The linux irq number
 * @biपंचांगask:	The biपंचांगask to evaluate
 *
 * Returns: True अगर one of the bits in @biपंचांगask is set
 */
bool irq_check_status_bit(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक biपंचांगask)
अणु
	काष्ठा irq_desc *desc;
	bool res = false;

	rcu_पढ़ो_lock();
	desc = irq_to_desc(irq);
	अगर (desc)
		res = !!(desc->status_use_accessors & biपंचांगask);
	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(irq_check_status_bit);
