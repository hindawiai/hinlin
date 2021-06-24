<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IRQ_H
#घोषणा _LINUX_IRQ_H

/*
 * Please करो not include this file in generic code.  There is currently
 * no requirement क्रम any architecture to implement anything held
 * within this file.
 *
 * Thanks. --rmk
 */

#समावेश <linux/cache.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/irqhandler.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/irqnr.h>
#समावेश <linux/topology.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/irq_regs.h>

काष्ठा seq_file;
काष्ठा module;
काष्ठा msi_msg;
काष्ठा irq_affinity_desc;
क्रमागत irqchip_irq_state;

/*
 * IRQ line status.
 *
 * Bits 0-7 are the same as the IRQF_* bits in linux/पूर्णांकerrupt.h
 *
 * IRQ_TYPE_NONE		- शेष, unspecअगरied type
 * IRQ_TYPE_EDGE_RISING		- rising edge triggered
 * IRQ_TYPE_EDGE_FALLING	- falling edge triggered
 * IRQ_TYPE_EDGE_BOTH		- rising and falling edge triggered
 * IRQ_TYPE_LEVEL_HIGH		- high level triggered
 * IRQ_TYPE_LEVEL_LOW		- low level triggered
 * IRQ_TYPE_LEVEL_MASK		- Mask to filter out the level bits
 * IRQ_TYPE_SENSE_MASK		- Mask क्रम all the above bits
 * IRQ_TYPE_DEFAULT		- For use by some PICs to ask irq_set_type
 *				  to setup the HW to a sane शेष (used
 *                                by irqकरोमुख्य map() callbacks to synchronize
 *                                the HW state and SW flags क्रम a newly
 *                                allocated descriptor).
 *
 * IRQ_TYPE_PROBE		- Special flag क्रम probing in progress
 *
 * Bits which can be modअगरied via irq_set/clear/modअगरy_status_flags()
 * IRQ_LEVEL			- Interrupt is level type. Will be also
 *				  updated in the code when the above trigger
 *				  bits are modअगरied via irq_set_irq_type()
 * IRQ_PER_CPU			- Mark an पूर्णांकerrupt PER_CPU. Will protect
 *				  it from affinity setting
 * IRQ_NOPROBE			- Interrupt cannot be probed by स्वतःprobing
 * IRQ_NOREQUEST		- Interrupt cannot be requested via
 *				  request_irq()
 * IRQ_NOTHREAD			- Interrupt cannot be thपढ़ोed
 * IRQ_NOAUTOEN			- Interrupt is not स्वतःmatically enabled in
 *				  request/setup_irq()
 * IRQ_NO_BALANCING		- Interrupt cannot be balanced (affinity set)
 * IRQ_MOVE_PCNTXT		- Interrupt can be migrated from process context
 * IRQ_NESTED_THREAD		- Interrupt nests पूर्णांकo another thपढ़ो
 * IRQ_PER_CPU_DEVID		- Dev_id is a per-cpu variable
 * IRQ_IS_POLLED		- Always polled by another पूर्णांकerrupt. Exclude
 *				  it from the spurious पूर्णांकerrupt detection
 *				  mechanism and from core side polling.
 * IRQ_DISABLE_UNLAZY		- Disable lazy irq disable
 * IRQ_HIDDEN			- Don't show up in /proc/पूर्णांकerrupts
 */
क्रमागत अणु
	IRQ_TYPE_NONE		= 0x00000000,
	IRQ_TYPE_EDGE_RISING	= 0x00000001,
	IRQ_TYPE_EDGE_FALLING	= 0x00000002,
	IRQ_TYPE_EDGE_BOTH	= (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING),
	IRQ_TYPE_LEVEL_HIGH	= 0x00000004,
	IRQ_TYPE_LEVEL_LOW	= 0x00000008,
	IRQ_TYPE_LEVEL_MASK	= (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH),
	IRQ_TYPE_SENSE_MASK	= 0x0000000f,
	IRQ_TYPE_DEFAULT	= IRQ_TYPE_SENSE_MASK,

	IRQ_TYPE_PROBE		= 0x00000010,

	IRQ_LEVEL		= (1 <<  8),
	IRQ_PER_CPU		= (1 <<  9),
	IRQ_NOPROBE		= (1 << 10),
	IRQ_NOREQUEST		= (1 << 11),
	IRQ_NOAUTOEN		= (1 << 12),
	IRQ_NO_BALANCING	= (1 << 13),
	IRQ_MOVE_PCNTXT		= (1 << 14),
	IRQ_NESTED_THREAD	= (1 << 15),
	IRQ_NOTHREAD		= (1 << 16),
	IRQ_PER_CPU_DEVID	= (1 << 17),
	IRQ_IS_POLLED		= (1 << 18),
	IRQ_DISABLE_UNLAZY	= (1 << 19),
	IRQ_HIDDEN		= (1 << 20),
पूर्ण;

#घोषणा IRQF_MODIFY_MASK	\
	(IRQ_TYPE_SENSE_MASK | IRQ_NOPROBE | IRQ_NOREQUEST | \
	 IRQ_NOAUTOEN | IRQ_MOVE_PCNTXT | IRQ_LEVEL | IRQ_NO_BALANCING | \
	 IRQ_PER_CPU | IRQ_NESTED_THREAD | IRQ_NOTHREAD | IRQ_PER_CPU_DEVID | \
	 IRQ_IS_POLLED | IRQ_DISABLE_UNLAZY | IRQ_HIDDEN)

#घोषणा IRQ_NO_BALANCING_MASK	(IRQ_PER_CPU | IRQ_NO_BALANCING)

/*
 * Return value क्रम chip->irq_set_affinity()
 *
 * IRQ_SET_MASK_OK	- OK, core updates irq_common_data.affinity
 * IRQ_SET_MASK_NOCPY	- OK, chip did update irq_common_data.affinity
 * IRQ_SET_MASK_OK_DONE	- Same as IRQ_SET_MASK_OK क्रम core. Special code to
 *			  support stacked irqchips, which indicates skipping
 *			  all descendant irqchips.
 */
क्रमागत अणु
	IRQ_SET_MASK_OK = 0,
	IRQ_SET_MASK_OK_NOCOPY,
	IRQ_SET_MASK_OK_DONE,
पूर्ण;

काष्ठा msi_desc;
काष्ठा irq_करोमुख्य;

/**
 * काष्ठा irq_common_data - per irq data shared by all irqchips
 * @state_use_accessors: status inक्रमmation क्रम irq chip functions.
 *			Use accessor functions to deal with it
 * @node:		node index useful क्रम balancing
 * @handler_data:	per-IRQ data क्रम the irq_chip methods
 * @affinity:		IRQ affinity on SMP. If this is an IPI
 *			related irq, then this is the mask of the
 *			CPUs to which an IPI can be sent.
 * @effective_affinity:	The effective IRQ affinity on SMP as some irq
 *			chips करो not allow multi CPU destinations.
 *			A subset of @affinity.
 * @msi_desc:		MSI descriptor
 * @ipi_offset:		Offset of first IPI target cpu in @affinity. Optional.
 */
काष्ठा irq_common_data अणु
	अचिन्हित पूर्णांक		__निजी state_use_accessors;
#अगर_घोषित CONFIG_NUMA
	अचिन्हित पूर्णांक		node;
#पूर्ण_अगर
	व्योम			*handler_data;
	काष्ठा msi_desc		*msi_desc;
	cpumask_var_t		affinity;
#अगर_घोषित CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK
	cpumask_var_t		effective_affinity;
#पूर्ण_अगर
#अगर_घोषित CONFIG_GENERIC_IRQ_IPI
	अचिन्हित पूर्णांक		ipi_offset;
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा irq_data - per irq chip data passed करोwn to chip functions
 * @mask:		precomputed biपंचांगask क्रम accessing the chip रेजिस्टरs
 * @irq:		पूर्णांकerrupt number
 * @hwirq:		hardware पूर्णांकerrupt number, local to the पूर्णांकerrupt करोमुख्य
 * @common:		poपूर्णांक to data shared by all irqchips
 * @chip:		low level पूर्णांकerrupt hardware access
 * @करोमुख्य:		Interrupt translation करोमुख्य; responsible क्रम mapping
 *			between hwirq number and linux irq number.
 * @parent_data:	poपूर्णांकer to parent काष्ठा irq_data to support hierarchy
 *			irq_करोमुख्य
 * @chip_data:		platक्रमm-specअगरic per-chip निजी data क्रम the chip
 *			methods, to allow shared chip implementations
 */
काष्ठा irq_data अणु
	u32			mask;
	अचिन्हित पूर्णांक		irq;
	अचिन्हित दीर्घ		hwirq;
	काष्ठा irq_common_data	*common;
	काष्ठा irq_chip		*chip;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
#अगर_घोषित	CONFIG_IRQ_DOMAIN_HIERARCHY
	काष्ठा irq_data		*parent_data;
#पूर्ण_अगर
	व्योम			*chip_data;
पूर्ण;

/*
 * Bit masks क्रम irq_common_data.state_use_accessors
 *
 * IRQD_TRIGGER_MASK		- Mask क्रम the trigger type bits
 * IRQD_SETAFFINITY_PENDING	- Affinity setting is pending
 * IRQD_ACTIVATED		- Interrupt has alपढ़ोy been activated
 * IRQD_NO_BALANCING		- Balancing disabled क्रम this IRQ
 * IRQD_PER_CPU			- Interrupt is per cpu
 * IRQD_AFFINITY_SET		- Interrupt affinity was set
 * IRQD_LEVEL			- Interrupt is level triggered
 * IRQD_WAKEUP_STATE		- Interrupt is configured क्रम wakeup
 *				  from suspend
 * IRQD_MOVE_PCNTXT		- Interrupt can be moved in process
 *				  context
 * IRQD_IRQ_DISABLED		- Disabled state of the पूर्णांकerrupt
 * IRQD_IRQ_MASKED		- Masked state of the पूर्णांकerrupt
 * IRQD_IRQ_INPROGRESS		- In progress state of the पूर्णांकerrupt
 * IRQD_WAKEUP_ARMED		- Wakeup mode armed
 * IRQD_FORWARDED_TO_VCPU	- The पूर्णांकerrupt is क्रमwarded to a VCPU
 * IRQD_AFFINITY_MANAGED	- Affinity is स्वतः-managed by the kernel
 * IRQD_IRQ_STARTED		- Startup state of the पूर्णांकerrupt
 * IRQD_MANAGED_SHUTDOWN	- Interrupt was shutकरोwn due to empty affinity
 *				  mask. Applies only to affinity managed irqs.
 * IRQD_SINGLE_TARGET		- IRQ allows only a single affinity target
 * IRQD_DEFAULT_TRIGGER_SET	- Expected trigger alपढ़ोy been set
 * IRQD_CAN_RESERVE		- Can use reservation mode
 * IRQD_MSI_NOMASK_QUIRK	- Non-maskable MSI quirk क्रम affinity change
 *				  required
 * IRQD_HANDLE_ENFORCE_IRQCTX	- Enक्रमce that handle_irq_*() is only invoked
 *				  from actual पूर्णांकerrupt context.
 * IRQD_AFFINITY_ON_ACTIVATE	- Affinity is set on activation. Don't call
 *				  irq_chip::irq_set_affinity() when deactivated.
 * IRQD_IRQ_ENABLED_ON_SUSPEND	- Interrupt is enabled on suspend by irq pm अगर
 *				  irqchip have flag IRQCHIP_ENABLE_WAKEUP_ON_SUSPEND set.
 */
क्रमागत अणु
	IRQD_TRIGGER_MASK		= 0xf,
	IRQD_SETAFFINITY_PENDING	= (1 <<  8),
	IRQD_ACTIVATED			= (1 <<  9),
	IRQD_NO_BALANCING		= (1 << 10),
	IRQD_PER_CPU			= (1 << 11),
	IRQD_AFFINITY_SET		= (1 << 12),
	IRQD_LEVEL			= (1 << 13),
	IRQD_WAKEUP_STATE		= (1 << 14),
	IRQD_MOVE_PCNTXT		= (1 << 15),
	IRQD_IRQ_DISABLED		= (1 << 16),
	IRQD_IRQ_MASKED			= (1 << 17),
	IRQD_IRQ_INPROGRESS		= (1 << 18),
	IRQD_WAKEUP_ARMED		= (1 << 19),
	IRQD_FORWARDED_TO_VCPU		= (1 << 20),
	IRQD_AFFINITY_MANAGED		= (1 << 21),
	IRQD_IRQ_STARTED		= (1 << 22),
	IRQD_MANAGED_SHUTDOWN		= (1 << 23),
	IRQD_SINGLE_TARGET		= (1 << 24),
	IRQD_DEFAULT_TRIGGER_SET	= (1 << 25),
	IRQD_CAN_RESERVE		= (1 << 26),
	IRQD_MSI_NOMASK_QUIRK		= (1 << 27),
	IRQD_HANDLE_ENFORCE_IRQCTX	= (1 << 28),
	IRQD_AFFINITY_ON_ACTIVATE	= (1 << 29),
	IRQD_IRQ_ENABLED_ON_SUSPEND	= (1 << 30),
पूर्ण;

#घोषणा __irqd_to_state(d) ACCESS_PRIVATE((d)->common, state_use_accessors)

अटल अंतरभूत bool irqd_is_setaffinity_pending(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_SETAFFINITY_PENDING;
पूर्ण

अटल अंतरभूत bool irqd_is_per_cpu(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_PER_CPU;
पूर्ण

अटल अंतरभूत bool irqd_can_balance(काष्ठा irq_data *d)
अणु
	वापस !(__irqd_to_state(d) & (IRQD_PER_CPU | IRQD_NO_BALANCING));
पूर्ण

अटल अंतरभूत bool irqd_affinity_was_set(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_AFFINITY_SET;
पूर्ण

अटल अंतरभूत व्योम irqd_mark_affinity_was_set(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) |= IRQD_AFFINITY_SET;
पूर्ण

अटल अंतरभूत bool irqd_trigger_type_was_set(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_DEFAULT_TRIGGER_SET;
पूर्ण

अटल अंतरभूत u32 irqd_get_trigger_type(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_TRIGGER_MASK;
पूर्ण

/*
 * Must only be called inside irq_chip.irq_set_type() functions or
 * from the DT/ACPI setup code.
 */
अटल अंतरभूत व्योम irqd_set_trigger_type(काष्ठा irq_data *d, u32 type)
अणु
	__irqd_to_state(d) &= ~IRQD_TRIGGER_MASK;
	__irqd_to_state(d) |= type & IRQD_TRIGGER_MASK;
	__irqd_to_state(d) |= IRQD_DEFAULT_TRIGGER_SET;
पूर्ण

अटल अंतरभूत bool irqd_is_level_type(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_LEVEL;
पूर्ण

/*
 * Must only be called of irqchip.irq_set_affinity() or low level
 * hierarchy करोमुख्य allocation functions.
 */
अटल अंतरभूत व्योम irqd_set_single_target(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) |= IRQD_SINGLE_TARGET;
पूर्ण

अटल अंतरभूत bool irqd_is_single_target(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_SINGLE_TARGET;
पूर्ण

अटल अंतरभूत व्योम irqd_set_handle_enक्रमce_irqctx(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) |= IRQD_HANDLE_ENFORCE_IRQCTX;
पूर्ण

अटल अंतरभूत bool irqd_is_handle_enक्रमce_irqctx(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_HANDLE_ENFORCE_IRQCTX;
पूर्ण

अटल अंतरभूत bool irqd_is_enabled_on_suspend(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_IRQ_ENABLED_ON_SUSPEND;
पूर्ण

अटल अंतरभूत bool irqd_is_wakeup_set(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_WAKEUP_STATE;
पूर्ण

अटल अंतरभूत bool irqd_can_move_in_process_context(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_MOVE_PCNTXT;
पूर्ण

अटल अंतरभूत bool irqd_irq_disabled(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_IRQ_DISABLED;
पूर्ण

अटल अंतरभूत bool irqd_irq_masked(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_IRQ_MASKED;
पूर्ण

अटल अंतरभूत bool irqd_irq_inprogress(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_IRQ_INPROGRESS;
पूर्ण

अटल अंतरभूत bool irqd_is_wakeup_armed(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_WAKEUP_ARMED;
पूर्ण

अटल अंतरभूत bool irqd_is_क्रमwarded_to_vcpu(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_FORWARDED_TO_VCPU;
पूर्ण

अटल अंतरभूत व्योम irqd_set_क्रमwarded_to_vcpu(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) |= IRQD_FORWARDED_TO_VCPU;
पूर्ण

अटल अंतरभूत व्योम irqd_clr_क्रमwarded_to_vcpu(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) &= ~IRQD_FORWARDED_TO_VCPU;
पूर्ण

अटल अंतरभूत bool irqd_affinity_is_managed(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_AFFINITY_MANAGED;
पूर्ण

अटल अंतरभूत bool irqd_is_activated(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_ACTIVATED;
पूर्ण

अटल अंतरभूत व्योम irqd_set_activated(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) |= IRQD_ACTIVATED;
पूर्ण

अटल अंतरभूत व्योम irqd_clr_activated(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) &= ~IRQD_ACTIVATED;
पूर्ण

अटल अंतरभूत bool irqd_is_started(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_IRQ_STARTED;
पूर्ण

अटल अंतरभूत bool irqd_is_managed_and_shutकरोwn(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_MANAGED_SHUTDOWN;
पूर्ण

अटल अंतरभूत व्योम irqd_set_can_reserve(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) |= IRQD_CAN_RESERVE;
पूर्ण

अटल अंतरभूत व्योम irqd_clr_can_reserve(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) &= ~IRQD_CAN_RESERVE;
पूर्ण

अटल अंतरभूत bool irqd_can_reserve(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_CAN_RESERVE;
पूर्ण

अटल अंतरभूत व्योम irqd_set_msi_nomask_quirk(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) |= IRQD_MSI_NOMASK_QUIRK;
पूर्ण

अटल अंतरभूत व्योम irqd_clr_msi_nomask_quirk(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) &= ~IRQD_MSI_NOMASK_QUIRK;
पूर्ण

अटल अंतरभूत bool irqd_msi_nomask_quirk(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_MSI_NOMASK_QUIRK;
पूर्ण

अटल अंतरभूत व्योम irqd_set_affinity_on_activate(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) |= IRQD_AFFINITY_ON_ACTIVATE;
पूर्ण

अटल अंतरभूत bool irqd_affinity_on_activate(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d) & IRQD_AFFINITY_ON_ACTIVATE;
पूर्ण

#अघोषित __irqd_to_state

अटल अंतरभूत irq_hw_number_t irqd_to_hwirq(काष्ठा irq_data *d)
अणु
	वापस d->hwirq;
पूर्ण

/**
 * काष्ठा irq_chip - hardware पूर्णांकerrupt chip descriptor
 *
 * @parent_device:	poपूर्णांकer to parent device क्रम irqchip
 * @name:		name क्रम /proc/पूर्णांकerrupts
 * @irq_startup:	start up the पूर्णांकerrupt (शेषs to ->enable अगर शून्य)
 * @irq_shutकरोwn:	shut करोwn the पूर्णांकerrupt (शेषs to ->disable अगर शून्य)
 * @irq_enable:		enable the पूर्णांकerrupt (शेषs to chip->unmask अगर शून्य)
 * @irq_disable:	disable the पूर्णांकerrupt
 * @irq_ack:		start of a new पूर्णांकerrupt
 * @irq_mask:		mask an पूर्णांकerrupt source
 * @irq_mask_ack:	ack and mask an पूर्णांकerrupt source
 * @irq_unmask:		unmask an पूर्णांकerrupt source
 * @irq_eoi:		end of पूर्णांकerrupt
 * @irq_set_affinity:	Set the CPU affinity on SMP machines. If the क्रमce
 *			argument is true, it tells the driver to
 *			unconditionally apply the affinity setting. Sanity
 *			checks against the supplied affinity mask are not
 *			required. This is used क्रम CPU hotplug where the
 *			target CPU is not yet set in the cpu_online_mask.
 * @irq_retrigger:	resend an IRQ to the CPU
 * @irq_set_type:	set the flow type (IRQ_TYPE_LEVEL/etc.) of an IRQ
 * @irq_set_wake:	enable/disable घातer-management wake-on of an IRQ
 * @irq_bus_lock:	function to lock access to slow bus (i2c) chips
 * @irq_bus_sync_unlock:function to sync and unlock slow bus (i2c) chips
 * @irq_cpu_online:	configure an पूर्णांकerrupt source क्रम a secondary CPU
 * @irq_cpu_offline:	un-configure an पूर्णांकerrupt source क्रम a secondary CPU
 * @irq_suspend:	function called from core code on suspend once per
 *			chip, when one or more पूर्णांकerrupts are installed
 * @irq_resume:		function called from core code on resume once per chip,
 *			when one ore more पूर्णांकerrupts are installed
 * @irq_pm_shutकरोwn:	function called from core code on shutकरोwn once per chip
 * @irq_calc_mask:	Optional function to set irq_data.mask क्रम special हालs
 * @irq_prपूर्णांक_chip:	optional to prपूर्णांक special chip info in show_पूर्णांकerrupts
 * @irq_request_resources:	optional to request resources beक्रमe calling
 *				any other callback related to this irq
 * @irq_release_resources:	optional to release resources acquired with
 *				irq_request_resources
 * @irq_compose_msi_msg:	optional to compose message content क्रम MSI
 * @irq_ग_लिखो_msi_msg:	optional to ग_लिखो message content क्रम MSI
 * @irq_get_irqchip_state:	वापस the पूर्णांकernal state of an पूर्णांकerrupt
 * @irq_set_irqchip_state:	set the पूर्णांकernal state of a पूर्णांकerrupt
 * @irq_set_vcpu_affinity:	optional to target a vCPU in a भव machine
 * @ipi_send_single:	send a single IPI to destination cpus
 * @ipi_send_mask:	send an IPI to destination cpus in cpumask
 * @irq_nmi_setup:	function called from core code beक्रमe enabling an NMI
 * @irq_nmi_tearकरोwn:	function called from core code after disabling an NMI
 * @flags:		chip specअगरic flags
 */
काष्ठा irq_chip अणु
	काष्ठा device	*parent_device;
	स्थिर अक्षर	*name;
	अचिन्हित पूर्णांक	(*irq_startup)(काष्ठा irq_data *data);
	व्योम		(*irq_shutकरोwn)(काष्ठा irq_data *data);
	व्योम		(*irq_enable)(काष्ठा irq_data *data);
	व्योम		(*irq_disable)(काष्ठा irq_data *data);

	व्योम		(*irq_ack)(काष्ठा irq_data *data);
	व्योम		(*irq_mask)(काष्ठा irq_data *data);
	व्योम		(*irq_mask_ack)(काष्ठा irq_data *data);
	व्योम		(*irq_unmask)(काष्ठा irq_data *data);
	व्योम		(*irq_eoi)(काष्ठा irq_data *data);

	पूर्णांक		(*irq_set_affinity)(काष्ठा irq_data *data, स्थिर काष्ठा cpumask *dest, bool क्रमce);
	पूर्णांक		(*irq_retrigger)(काष्ठा irq_data *data);
	पूर्णांक		(*irq_set_type)(काष्ठा irq_data *data, अचिन्हित पूर्णांक flow_type);
	पूर्णांक		(*irq_set_wake)(काष्ठा irq_data *data, अचिन्हित पूर्णांक on);

	व्योम		(*irq_bus_lock)(काष्ठा irq_data *data);
	व्योम		(*irq_bus_sync_unlock)(काष्ठा irq_data *data);

	व्योम		(*irq_cpu_online)(काष्ठा irq_data *data);
	व्योम		(*irq_cpu_offline)(काष्ठा irq_data *data);

	व्योम		(*irq_suspend)(काष्ठा irq_data *data);
	व्योम		(*irq_resume)(काष्ठा irq_data *data);
	व्योम		(*irq_pm_shutकरोwn)(काष्ठा irq_data *data);

	व्योम		(*irq_calc_mask)(काष्ठा irq_data *data);

	व्योम		(*irq_prपूर्णांक_chip)(काष्ठा irq_data *data, काष्ठा seq_file *p);
	पूर्णांक		(*irq_request_resources)(काष्ठा irq_data *data);
	व्योम		(*irq_release_resources)(काष्ठा irq_data *data);

	व्योम		(*irq_compose_msi_msg)(काष्ठा irq_data *data, काष्ठा msi_msg *msg);
	व्योम		(*irq_ग_लिखो_msi_msg)(काष्ठा irq_data *data, काष्ठा msi_msg *msg);

	पूर्णांक		(*irq_get_irqchip_state)(काष्ठा irq_data *data, क्रमागत irqchip_irq_state which, bool *state);
	पूर्णांक		(*irq_set_irqchip_state)(काष्ठा irq_data *data, क्रमागत irqchip_irq_state which, bool state);

	पूर्णांक		(*irq_set_vcpu_affinity)(काष्ठा irq_data *data, व्योम *vcpu_info);

	व्योम		(*ipi_send_single)(काष्ठा irq_data *data, अचिन्हित पूर्णांक cpu);
	व्योम		(*ipi_send_mask)(काष्ठा irq_data *data, स्थिर काष्ठा cpumask *dest);

	पूर्णांक		(*irq_nmi_setup)(काष्ठा irq_data *data);
	व्योम		(*irq_nmi_tearकरोwn)(काष्ठा irq_data *data);

	अचिन्हित दीर्घ	flags;
पूर्ण;

/*
 * irq_chip specअगरic flags
 *
 * IRQCHIP_SET_TYPE_MASKED:           Mask beक्रमe calling chip.irq_set_type()
 * IRQCHIP_EOI_IF_HANDLED:            Only issue irq_eoi() when irq was handled
 * IRQCHIP_MASK_ON_SUSPEND:           Mask non wake irqs in the suspend path
 * IRQCHIP_ONOFFLINE_ENABLED:         Only call irq_on/off_line callbacks
 *                                    when irq enabled
 * IRQCHIP_SKIP_SET_WAKE:             Skip chip.irq_set_wake(), क्रम this irq chip
 * IRQCHIP_ONESHOT_SAFE:              One shot करोes not require mask/unmask
 * IRQCHIP_EOI_THREADED:              Chip requires eoi() on unmask in thपढ़ोed mode
 * IRQCHIP_SUPPORTS_LEVEL_MSI:        Chip can provide two करोorbells क्रम Level MSIs
 * IRQCHIP_SUPPORTS_NMI:              Chip can deliver NMIs, only क्रम root irqchips
 * IRQCHIP_ENABLE_WAKEUP_ON_SUSPEND:  Invokes __enable_irq()/__disable_irq() क्रम wake irqs
 *                                    in the suspend path अगर they are in disabled state
 */
क्रमागत अणु
	IRQCHIP_SET_TYPE_MASKED			= (1 <<  0),
	IRQCHIP_EOI_IF_HANDLED			= (1 <<  1),
	IRQCHIP_MASK_ON_SUSPEND			= (1 <<  2),
	IRQCHIP_ONOFFLINE_ENABLED		= (1 <<  3),
	IRQCHIP_SKIP_SET_WAKE			= (1 <<  4),
	IRQCHIP_ONESHOT_SAFE			= (1 <<  5),
	IRQCHIP_EOI_THREADED			= (1 <<  6),
	IRQCHIP_SUPPORTS_LEVEL_MSI		= (1 <<  7),
	IRQCHIP_SUPPORTS_NMI			= (1 <<  8),
	IRQCHIP_ENABLE_WAKEUP_ON_SUSPEND	= (1 <<  9),
पूर्ण;

#समावेश <linux/irqdesc.h>

/*
 * Pick up the arch-dependent methods:
 */
#समावेश <यंत्र/hw_irq.h>

#अगर_अघोषित NR_IRQS_LEGACY
# define NR_IRQS_LEGACY 0
#पूर्ण_अगर

#अगर_अघोषित ARCH_IRQ_INIT_FLAGS
# define ARCH_IRQ_INIT_FLAGS	0
#पूर्ण_अगर

#घोषणा IRQ_DEFAULT_INIT_FLAGS	ARCH_IRQ_INIT_FLAGS

काष्ठा irqaction;
बाह्य पूर्णांक setup_percpu_irq(अचिन्हित पूर्णांक irq, काष्ठा irqaction *new);
बाह्य व्योम हटाओ_percpu_irq(अचिन्हित पूर्णांक irq, काष्ठा irqaction *act);

बाह्य व्योम irq_cpu_online(व्योम);
बाह्य व्योम irq_cpu_offline(व्योम);
बाह्य पूर्णांक irq_set_affinity_locked(काष्ठा irq_data *data,
				   स्थिर काष्ठा cpumask *cpumask, bool क्रमce);
बाह्य पूर्णांक irq_set_vcpu_affinity(अचिन्हित पूर्णांक irq, व्योम *vcpu_info);

#अगर defined(CONFIG_SMP) && defined(CONFIG_GENERIC_IRQ_MIGRATION)
बाह्य व्योम irq_migrate_all_off_this_cpu(व्योम);
बाह्य पूर्णांक irq_affinity_online_cpu(अचिन्हित पूर्णांक cpu);
#अन्यथा
# define irq_affinity_online_cpu	शून्य
#पूर्ण_अगर

#अगर defined(CONFIG_SMP) && defined(CONFIG_GENERIC_PENDING_IRQ)
व्योम __irq_move_irq(काष्ठा irq_data *data);
अटल अंतरभूत व्योम irq_move_irq(काष्ठा irq_data *data)
अणु
	अगर (unlikely(irqd_is_setaffinity_pending(data)))
		__irq_move_irq(data);
पूर्ण
व्योम irq_move_masked_irq(काष्ठा irq_data *data);
व्योम irq_क्रमce_complete_move(काष्ठा irq_desc *desc);
#अन्यथा
अटल अंतरभूत व्योम irq_move_irq(काष्ठा irq_data *data) अणु पूर्ण
अटल अंतरभूत व्योम irq_move_masked_irq(काष्ठा irq_data *data) अणु पूर्ण
अटल अंतरभूत व्योम irq_क्रमce_complete_move(काष्ठा irq_desc *desc) अणु पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक no_irq_affinity;

#अगर_घोषित CONFIG_HARसूचीQS_SW_RESEND
पूर्णांक irq_set_parent(पूर्णांक irq, पूर्णांक parent_irq);
#अन्यथा
अटल अंतरभूत पूर्णांक irq_set_parent(पूर्णांक irq, पूर्णांक parent_irq)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Built-in IRQ handlers क्रम various IRQ types,
 * callable via desc->handle_irq()
 */
बाह्य व्योम handle_level_irq(काष्ठा irq_desc *desc);
बाह्य व्योम handle_fasteoi_irq(काष्ठा irq_desc *desc);
बाह्य व्योम handle_edge_irq(काष्ठा irq_desc *desc);
बाह्य व्योम handle_edge_eoi_irq(काष्ठा irq_desc *desc);
बाह्य व्योम handle_simple_irq(काष्ठा irq_desc *desc);
बाह्य व्योम handle_untracked_irq(काष्ठा irq_desc *desc);
बाह्य व्योम handle_percpu_irq(काष्ठा irq_desc *desc);
बाह्य व्योम handle_percpu_devid_irq(काष्ठा irq_desc *desc);
बाह्य व्योम handle_bad_irq(काष्ठा irq_desc *desc);
बाह्य व्योम handle_nested_irq(अचिन्हित पूर्णांक irq);

बाह्य व्योम handle_fasteoi_nmi(काष्ठा irq_desc *desc);
बाह्य व्योम handle_percpu_devid_fasteoi_nmi(काष्ठा irq_desc *desc);

बाह्य पूर्णांक irq_chip_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg);
बाह्य पूर्णांक irq_chip_pm_get(काष्ठा irq_data *data);
बाह्य पूर्णांक irq_chip_pm_put(काष्ठा irq_data *data);
#अगर_घोषित	CONFIG_IRQ_DOMAIN_HIERARCHY
बाह्य व्योम handle_fasteoi_ack_irq(काष्ठा irq_desc *desc);
बाह्य व्योम handle_fasteoi_mask_irq(काष्ठा irq_desc *desc);
बाह्य पूर्णांक irq_chip_set_parent_state(काष्ठा irq_data *data,
				     क्रमागत irqchip_irq_state which,
				     bool val);
बाह्य पूर्णांक irq_chip_get_parent_state(काष्ठा irq_data *data,
				     क्रमागत irqchip_irq_state which,
				     bool *state);
बाह्य व्योम irq_chip_enable_parent(काष्ठा irq_data *data);
बाह्य व्योम irq_chip_disable_parent(काष्ठा irq_data *data);
बाह्य व्योम irq_chip_ack_parent(काष्ठा irq_data *data);
बाह्य पूर्णांक irq_chip_retrigger_hierarchy(काष्ठा irq_data *data);
बाह्य व्योम irq_chip_mask_parent(काष्ठा irq_data *data);
बाह्य व्योम irq_chip_mask_ack_parent(काष्ठा irq_data *data);
बाह्य व्योम irq_chip_unmask_parent(काष्ठा irq_data *data);
बाह्य व्योम irq_chip_eoi_parent(काष्ठा irq_data *data);
बाह्य पूर्णांक irq_chip_set_affinity_parent(काष्ठा irq_data *data,
					स्थिर काष्ठा cpumask *dest,
					bool क्रमce);
बाह्य पूर्णांक irq_chip_set_wake_parent(काष्ठा irq_data *data, अचिन्हित पूर्णांक on);
बाह्य पूर्णांक irq_chip_set_vcpu_affinity_parent(काष्ठा irq_data *data,
					     व्योम *vcpu_info);
बाह्य पूर्णांक irq_chip_set_type_parent(काष्ठा irq_data *data, अचिन्हित पूर्णांक type);
बाह्य पूर्णांक irq_chip_request_resources_parent(काष्ठा irq_data *data);
बाह्य व्योम irq_chip_release_resources_parent(काष्ठा irq_data *data);
#पूर्ण_अगर

/* Handling of unhandled and spurious पूर्णांकerrupts: */
बाह्य व्योम note_पूर्णांकerrupt(काष्ठा irq_desc *desc, irqवापस_t action_ret);


/* Enable/disable irq debugging output: */
बाह्य पूर्णांक noirqdebug_setup(अक्षर *str);

/* Checks whether the पूर्णांकerrupt can be requested by request_irq(): */
बाह्य पूर्णांक can_request_irq(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ irqflags);

/* Dummy irq-chip implementations: */
बाह्य काष्ठा irq_chip no_irq_chip;
बाह्य काष्ठा irq_chip dummy_irq_chip;

बाह्य व्योम
irq_set_chip_and_handler_name(अचिन्हित पूर्णांक irq, काष्ठा irq_chip *chip,
			      irq_flow_handler_t handle, स्थिर अक्षर *name);

अटल अंतरभूत व्योम irq_set_chip_and_handler(अचिन्हित पूर्णांक irq, काष्ठा irq_chip *chip,
					    irq_flow_handler_t handle)
अणु
	irq_set_chip_and_handler_name(irq, chip, handle, शून्य);
पूर्ण

बाह्य पूर्णांक irq_set_percpu_devid(अचिन्हित पूर्णांक irq);
बाह्य पूर्णांक irq_set_percpu_devid_partition(अचिन्हित पूर्णांक irq,
					  स्थिर काष्ठा cpumask *affinity);
बाह्य पूर्णांक irq_get_percpu_devid_partition(अचिन्हित पूर्णांक irq,
					  काष्ठा cpumask *affinity);

बाह्य व्योम
__irq_set_handler(अचिन्हित पूर्णांक irq, irq_flow_handler_t handle, पूर्णांक is_chained,
		  स्थिर अक्षर *name);

अटल अंतरभूत व्योम
irq_set_handler(अचिन्हित पूर्णांक irq, irq_flow_handler_t handle)
अणु
	__irq_set_handler(irq, handle, 0, शून्य);
पूर्ण

/*
 * Set a highlevel chained flow handler क्रम a given IRQ.
 * (a chained handler is स्वतःmatically enabled and set to
 *  IRQ_NOREQUEST, IRQ_NOPROBE, and IRQ_NOTHREAD)
 */
अटल अंतरभूत व्योम
irq_set_chained_handler(अचिन्हित पूर्णांक irq, irq_flow_handler_t handle)
अणु
	__irq_set_handler(irq, handle, 1, शून्य);
पूर्ण

/*
 * Set a highlevel chained flow handler and its data क्रम a given IRQ.
 * (a chained handler is स्वतःmatically enabled and set to
 *  IRQ_NOREQUEST, IRQ_NOPROBE, and IRQ_NOTHREAD)
 */
व्योम
irq_set_chained_handler_and_data(अचिन्हित पूर्णांक irq, irq_flow_handler_t handle,
				 व्योम *data);

व्योम irq_modअगरy_status(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ clr, अचिन्हित दीर्घ set);

अटल अंतरभूत व्योम irq_set_status_flags(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ set)
अणु
	irq_modअगरy_status(irq, 0, set);
पूर्ण

अटल अंतरभूत व्योम irq_clear_status_flags(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ clr)
अणु
	irq_modअगरy_status(irq, clr, 0);
पूर्ण

अटल अंतरभूत व्योम irq_set_noprobe(अचिन्हित पूर्णांक irq)
अणु
	irq_modअगरy_status(irq, 0, IRQ_NOPROBE);
पूर्ण

अटल अंतरभूत व्योम irq_set_probe(अचिन्हित पूर्णांक irq)
अणु
	irq_modअगरy_status(irq, IRQ_NOPROBE, 0);
पूर्ण

अटल अंतरभूत व्योम irq_set_nothपढ़ो(अचिन्हित पूर्णांक irq)
अणु
	irq_modअगरy_status(irq, 0, IRQ_NOTHREAD);
पूर्ण

अटल अंतरभूत व्योम irq_set_thपढ़ो(अचिन्हित पूर्णांक irq)
अणु
	irq_modअगरy_status(irq, IRQ_NOTHREAD, 0);
पूर्ण

अटल अंतरभूत व्योम irq_set_nested_thपढ़ो(अचिन्हित पूर्णांक irq, bool nest)
अणु
	अगर (nest)
		irq_set_status_flags(irq, IRQ_NESTED_THREAD);
	अन्यथा
		irq_clear_status_flags(irq, IRQ_NESTED_THREAD);
पूर्ण

अटल अंतरभूत व्योम irq_set_percpu_devid_flags(अचिन्हित पूर्णांक irq)
अणु
	irq_set_status_flags(irq,
			     IRQ_NOAUTOEN | IRQ_PER_CPU | IRQ_NOTHREAD |
			     IRQ_NOPROBE | IRQ_PER_CPU_DEVID);
पूर्ण

/* Set/get chip/data क्रम an IRQ: */
बाह्य पूर्णांक irq_set_chip(अचिन्हित पूर्णांक irq, काष्ठा irq_chip *chip);
बाह्य पूर्णांक irq_set_handler_data(अचिन्हित पूर्णांक irq, व्योम *data);
बाह्य पूर्णांक irq_set_chip_data(अचिन्हित पूर्णांक irq, व्योम *data);
बाह्य पूर्णांक irq_set_irq_type(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक type);
बाह्य पूर्णांक irq_set_msi_desc(अचिन्हित पूर्णांक irq, काष्ठा msi_desc *entry);
बाह्य पूर्णांक irq_set_msi_desc_off(अचिन्हित पूर्णांक irq_base, अचिन्हित पूर्णांक irq_offset,
				काष्ठा msi_desc *entry);
बाह्य काष्ठा irq_data *irq_get_irq_data(अचिन्हित पूर्णांक irq);

अटल अंतरभूत काष्ठा irq_chip *irq_get_chip(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_data *d = irq_get_irq_data(irq);
	वापस d ? d->chip : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा irq_chip *irq_data_get_irq_chip(काष्ठा irq_data *d)
अणु
	वापस d->chip;
पूर्ण

अटल अंतरभूत व्योम *irq_get_chip_data(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_data *d = irq_get_irq_data(irq);
	वापस d ? d->chip_data : शून्य;
पूर्ण

अटल अंतरभूत व्योम *irq_data_get_irq_chip_data(काष्ठा irq_data *d)
अणु
	वापस d->chip_data;
पूर्ण

अटल अंतरभूत व्योम *irq_get_handler_data(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_data *d = irq_get_irq_data(irq);
	वापस d ? d->common->handler_data : शून्य;
पूर्ण

अटल अंतरभूत व्योम *irq_data_get_irq_handler_data(काष्ठा irq_data *d)
अणु
	वापस d->common->handler_data;
पूर्ण

अटल अंतरभूत काष्ठा msi_desc *irq_get_msi_desc(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_data *d = irq_get_irq_data(irq);
	वापस d ? d->common->msi_desc : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा msi_desc *irq_data_get_msi_desc(काष्ठा irq_data *d)
अणु
	वापस d->common->msi_desc;
पूर्ण

अटल अंतरभूत u32 irq_get_trigger_type(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_data *d = irq_get_irq_data(irq);
	वापस d ? irqd_get_trigger_type(d) : 0;
पूर्ण

अटल अंतरभूत पूर्णांक irq_common_data_get_node(काष्ठा irq_common_data *d)
अणु
#अगर_घोषित CONFIG_NUMA
	वापस d->node;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक irq_data_get_node(काष्ठा irq_data *d)
अणु
	वापस irq_common_data_get_node(d->common);
पूर्ण

अटल अंतरभूत काष्ठा cpumask *irq_get_affinity_mask(पूर्णांक irq)
अणु
	काष्ठा irq_data *d = irq_get_irq_data(irq);

	वापस d ? d->common->affinity : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा cpumask *irq_data_get_affinity_mask(काष्ठा irq_data *d)
अणु
	वापस d->common->affinity;
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK
अटल अंतरभूत
काष्ठा cpumask *irq_data_get_effective_affinity_mask(काष्ठा irq_data *d)
अणु
	वापस d->common->effective_affinity;
पूर्ण
अटल अंतरभूत व्योम irq_data_update_effective_affinity(काष्ठा irq_data *d,
						      स्थिर काष्ठा cpumask *m)
अणु
	cpumask_copy(d->common->effective_affinity, m);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम irq_data_update_effective_affinity(काष्ठा irq_data *d,
						      स्थिर काष्ठा cpumask *m)
अणु
पूर्ण
अटल अंतरभूत
काष्ठा cpumask *irq_data_get_effective_affinity_mask(काष्ठा irq_data *d)
अणु
	वापस d->common->affinity;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा cpumask *irq_get_effective_affinity_mask(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_data *d = irq_get_irq_data(irq);

	वापस d ? irq_data_get_effective_affinity_mask(d) : शून्य;
पूर्ण

अचिन्हित पूर्णांक arch_dynirq_lower_bound(अचिन्हित पूर्णांक from);

पूर्णांक __irq_alloc_descs(पूर्णांक irq, अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक cnt, पूर्णांक node,
		      काष्ठा module *owner,
		      स्थिर काष्ठा irq_affinity_desc *affinity);

पूर्णांक __devm_irq_alloc_descs(काष्ठा device *dev, पूर्णांक irq, अचिन्हित पूर्णांक from,
			   अचिन्हित पूर्णांक cnt, पूर्णांक node, काष्ठा module *owner,
			   स्थिर काष्ठा irq_affinity_desc *affinity);

/* use macros to aव्योम needing export.h क्रम THIS_MODULE */
#घोषणा irq_alloc_descs(irq, from, cnt, node)	\
	__irq_alloc_descs(irq, from, cnt, node, THIS_MODULE, शून्य)

#घोषणा irq_alloc_desc(node)			\
	irq_alloc_descs(-1, 1, 1, node)

#घोषणा irq_alloc_desc_at(at, node)		\
	irq_alloc_descs(at, at, 1, node)

#घोषणा irq_alloc_desc_from(from, node)		\
	irq_alloc_descs(-1, from, 1, node)

#घोषणा irq_alloc_descs_from(from, cnt, node)	\
	irq_alloc_descs(-1, from, cnt, node)

#घोषणा devm_irq_alloc_descs(dev, irq, from, cnt, node)		\
	__devm_irq_alloc_descs(dev, irq, from, cnt, node, THIS_MODULE, शून्य)

#घोषणा devm_irq_alloc_desc(dev, node)				\
	devm_irq_alloc_descs(dev, -1, 1, 1, node)

#घोषणा devm_irq_alloc_desc_at(dev, at, node)			\
	devm_irq_alloc_descs(dev, at, at, 1, node)

#घोषणा devm_irq_alloc_desc_from(dev, from, node)		\
	devm_irq_alloc_descs(dev, -1, from, 1, node)

#घोषणा devm_irq_alloc_descs_from(dev, from, cnt, node)		\
	devm_irq_alloc_descs(dev, -1, from, cnt, node)

व्योम irq_मुक्त_descs(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक cnt);
अटल अंतरभूत व्योम irq_मुक्त_desc(अचिन्हित पूर्णांक irq)
अणु
	irq_मुक्त_descs(irq, 1);
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IRQ_LEGACY
व्योम irq_init_desc(अचिन्हित पूर्णांक irq);
#पूर्ण_अगर

/**
 * काष्ठा irq_chip_regs - रेजिस्टर offsets क्रम काष्ठा irq_gci
 * @enable:	Enable रेजिस्टर offset to reg_base
 * @disable:	Disable रेजिस्टर offset to reg_base
 * @mask:	Mask रेजिस्टर offset to reg_base
 * @ack:	Ack रेजिस्टर offset to reg_base
 * @eoi:	Eoi रेजिस्टर offset to reg_base
 * @type:	Type configuration रेजिस्टर offset to reg_base
 * @polarity:	Polarity configuration रेजिस्टर offset to reg_base
 */
काष्ठा irq_chip_regs अणु
	अचिन्हित दीर्घ		enable;
	अचिन्हित दीर्घ		disable;
	अचिन्हित दीर्घ		mask;
	अचिन्हित दीर्घ		ack;
	अचिन्हित दीर्घ		eoi;
	अचिन्हित दीर्घ		type;
	अचिन्हित दीर्घ		polarity;
पूर्ण;

/**
 * काष्ठा irq_chip_type - Generic पूर्णांकerrupt chip instance क्रम a flow type
 * @chip:		The real पूर्णांकerrupt chip which provides the callbacks
 * @regs:		Register offsets क्रम this chip
 * @handler:		Flow handler associated with this chip
 * @type:		Chip can handle these flow types
 * @mask_cache_priv:	Cached mask रेजिस्टर निजी to the chip type
 * @mask_cache:		Poपूर्णांकer to cached mask रेजिस्टर
 *
 * A irq_generic_chip can have several instances of irq_chip_type when
 * it requires dअगरferent functions and रेजिस्टर offsets क्रम dअगरferent
 * flow types.
 */
काष्ठा irq_chip_type अणु
	काष्ठा irq_chip		chip;
	काष्ठा irq_chip_regs	regs;
	irq_flow_handler_t	handler;
	u32			type;
	u32			mask_cache_priv;
	u32			*mask_cache;
पूर्ण;

/**
 * काष्ठा irq_chip_generic - Generic irq chip data काष्ठाure
 * @lock:		Lock to protect रेजिस्टर and cache data access
 * @reg_base:		Register base address (भव)
 * @reg_पढ़ोl:		Alternate I/O accessor (शेषs to पढ़ोl अगर शून्य)
 * @reg_ग_लिखोl:		Alternate I/O accessor (शेषs to ग_लिखोl अगर शून्य)
 * @suspend:		Function called from core code on suspend once per
 *			chip; can be useful instead of irq_chip::suspend to
 *			handle chip details even when no पूर्णांकerrupts are in use
 * @resume:		Function called from core code on resume once per chip;
 *			can be useful instead of irq_chip::suspend to handle
 *			chip details even when no पूर्णांकerrupts are in use
 * @irq_base:		Interrupt base nr क्रम this chip
 * @irq_cnt:		Number of पूर्णांकerrupts handled by this chip
 * @mask_cache:		Cached mask रेजिस्टर shared between all chip types
 * @type_cache:		Cached type रेजिस्टर
 * @polarity_cache:	Cached polarity रेजिस्टर
 * @wake_enabled:	Interrupt can wakeup from suspend
 * @wake_active:	Interrupt is marked as an wakeup from suspend source
 * @num_ct:		Number of available irq_chip_type instances (usually 1)
 * @निजी:		Private data क्रम non generic chip callbacks
 * @installed:		bitfield to denote installed पूर्णांकerrupts
 * @unused:		bitfield to denote unused पूर्णांकerrupts
 * @करोमुख्य:		irq करोमुख्य poपूर्णांकer
 * @list:		List head क्रम keeping track of instances
 * @chip_types:		Array of पूर्णांकerrupt irq_chip_types
 *
 * Note, that irq_chip_generic can have multiple irq_chip_type
 * implementations which can be associated to a particular irq line of
 * an irq_chip_generic instance. That allows to share and protect
 * state in an irq_chip_generic instance when we need to implement
 * dअगरferent flow mechanisms (level/edge) क्रम it.
 */
काष्ठा irq_chip_generic अणु
	raw_spinlock_t		lock;
	व्योम __iomem		*reg_base;
	u32			(*reg_पढ़ोl)(व्योम __iomem *addr);
	व्योम			(*reg_ग_लिखोl)(u32 val, व्योम __iomem *addr);
	व्योम			(*suspend)(काष्ठा irq_chip_generic *gc);
	व्योम			(*resume)(काष्ठा irq_chip_generic *gc);
	अचिन्हित पूर्णांक		irq_base;
	अचिन्हित पूर्णांक		irq_cnt;
	u32			mask_cache;
	u32			type_cache;
	u32			polarity_cache;
	u32			wake_enabled;
	u32			wake_active;
	अचिन्हित पूर्णांक		num_ct;
	व्योम			*निजी;
	अचिन्हित दीर्घ		installed;
	अचिन्हित दीर्घ		unused;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	काष्ठा list_head	list;
	काष्ठा irq_chip_type	chip_types[];
पूर्ण;

/**
 * क्रमागत irq_gc_flags - Initialization flags क्रम generic irq chips
 * @IRQ_GC_INIT_MASK_CACHE:	Initialize the mask_cache by पढ़ोing mask reg
 * @IRQ_GC_INIT_NESTED_LOCK:	Set the lock class of the irqs to nested क्रम
 *				irq chips which need to call irq_set_wake() on
 *				the parent irq. Usually GPIO implementations
 * @IRQ_GC_MASK_CACHE_PER_TYPE:	Mask cache is chip type निजी
 * @IRQ_GC_NO_MASK:		Do not calculate irq_data->mask
 * @IRQ_GC_BE_IO:		Use big-endian रेजिस्टर accesses (शेष: LE)
 */
क्रमागत irq_gc_flags अणु
	IRQ_GC_INIT_MASK_CACHE		= 1 << 0,
	IRQ_GC_INIT_NESTED_LOCK		= 1 << 1,
	IRQ_GC_MASK_CACHE_PER_TYPE	= 1 << 2,
	IRQ_GC_NO_MASK			= 1 << 3,
	IRQ_GC_BE_IO			= 1 << 4,
पूर्ण;

/*
 * काष्ठा irq_करोमुख्य_chip_generic - Generic irq chip data काष्ठाure क्रम irq करोमुख्यs
 * @irqs_per_chip:	Number of पूर्णांकerrupts per chip
 * @num_chips:		Number of chips
 * @irq_flags_to_set:	IRQ* flags to set on irq setup
 * @irq_flags_to_clear:	IRQ* flags to clear on irq setup
 * @gc_flags:		Generic chip specअगरic setup flags
 * @gc:			Array of poपूर्णांकers to generic पूर्णांकerrupt chips
 */
काष्ठा irq_करोमुख्य_chip_generic अणु
	अचिन्हित पूर्णांक		irqs_per_chip;
	अचिन्हित पूर्णांक		num_chips;
	अचिन्हित पूर्णांक		irq_flags_to_clear;
	अचिन्हित पूर्णांक		irq_flags_to_set;
	क्रमागत irq_gc_flags	gc_flags;
	काष्ठा irq_chip_generic	*gc[];
पूर्ण;

/* Generic chip callback functions */
व्योम irq_gc_noop(काष्ठा irq_data *d);
व्योम irq_gc_mask_disable_reg(काष्ठा irq_data *d);
व्योम irq_gc_mask_set_bit(काष्ठा irq_data *d);
व्योम irq_gc_mask_clr_bit(काष्ठा irq_data *d);
व्योम irq_gc_unmask_enable_reg(काष्ठा irq_data *d);
व्योम irq_gc_ack_set_bit(काष्ठा irq_data *d);
व्योम irq_gc_ack_clr_bit(काष्ठा irq_data *d);
व्योम irq_gc_mask_disable_and_ack_set(काष्ठा irq_data *d);
व्योम irq_gc_eoi(काष्ठा irq_data *d);
पूर्णांक irq_gc_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on);

/* Setup functions क्रम irq_chip_generic */
पूर्णांक irq_map_generic_chip(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hw_irq);
काष्ठा irq_chip_generic *
irq_alloc_generic_chip(स्थिर अक्षर *name, पूर्णांक nr_ct, अचिन्हित पूर्णांक irq_base,
		       व्योम __iomem *reg_base, irq_flow_handler_t handler);
व्योम irq_setup_generic_chip(काष्ठा irq_chip_generic *gc, u32 msk,
			    क्रमागत irq_gc_flags flags, अचिन्हित पूर्णांक clr,
			    अचिन्हित पूर्णांक set);
पूर्णांक irq_setup_alt_chip(काष्ठा irq_data *d, अचिन्हित पूर्णांक type);
व्योम irq_हटाओ_generic_chip(काष्ठा irq_chip_generic *gc, u32 msk,
			     अचिन्हित पूर्णांक clr, अचिन्हित पूर्णांक set);

काष्ठा irq_chip_generic *
devm_irq_alloc_generic_chip(काष्ठा device *dev, स्थिर अक्षर *name, पूर्णांक num_ct,
			    अचिन्हित पूर्णांक irq_base, व्योम __iomem *reg_base,
			    irq_flow_handler_t handler);
पूर्णांक devm_irq_setup_generic_chip(काष्ठा device *dev, काष्ठा irq_chip_generic *gc,
				u32 msk, क्रमागत irq_gc_flags flags,
				अचिन्हित पूर्णांक clr, अचिन्हित पूर्णांक set);

काष्ठा irq_chip_generic *irq_get_करोमुख्य_generic_chip(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक hw_irq);

पूर्णांक __irq_alloc_करोमुख्य_generic_chips(काष्ठा irq_करोमुख्य *d, पूर्णांक irqs_per_chip,
				     पूर्णांक num_ct, स्थिर अक्षर *name,
				     irq_flow_handler_t handler,
				     अचिन्हित पूर्णांक clr, अचिन्हित पूर्णांक set,
				     क्रमागत irq_gc_flags flags);

#घोषणा irq_alloc_करोमुख्य_generic_chips(d, irqs_per_chip, num_ct, name,	\
				       handler,	clr, set, flags)	\
(अणु									\
	MAYBE_BUILD_BUG_ON(irqs_per_chip > 32);				\
	__irq_alloc_करोमुख्य_generic_chips(d, irqs_per_chip, num_ct, name,\
					 handler, clr, set, flags);	\
पूर्ण)

अटल अंतरभूत व्योम irq_मुक्त_generic_chip(काष्ठा irq_chip_generic *gc)
अणु
	kमुक्त(gc);
पूर्ण

अटल अंतरभूत व्योम irq_destroy_generic_chip(काष्ठा irq_chip_generic *gc,
					    u32 msk, अचिन्हित पूर्णांक clr,
					    अचिन्हित पूर्णांक set)
अणु
	irq_हटाओ_generic_chip(gc, msk, clr, set);
	irq_मुक्त_generic_chip(gc);
पूर्ण

अटल अंतरभूत काष्ठा irq_chip_type *irq_data_get_chip_type(काष्ठा irq_data *d)
अणु
	वापस container_of(d->chip, काष्ठा irq_chip_type, chip);
पूर्ण

#घोषणा IRQ_MSK(n) (u32)((n) < 32 ? ((1 << (n)) - 1) : अच_पूर्णांक_उच्च)

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत व्योम irq_gc_lock(काष्ठा irq_chip_generic *gc)
अणु
	raw_spin_lock(&gc->lock);
पूर्ण

अटल अंतरभूत व्योम irq_gc_unlock(काष्ठा irq_chip_generic *gc)
अणु
	raw_spin_unlock(&gc->lock);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम irq_gc_lock(काष्ठा irq_chip_generic *gc) अणु पूर्ण
अटल अंतरभूत व्योम irq_gc_unlock(काष्ठा irq_chip_generic *gc) अणु पूर्ण
#पूर्ण_अगर

/*
 * The irqsave variants are क्रम usage in non पूर्णांकerrupt code. Do not use
 * them in irq_chip callbacks. Use irq_gc_lock() instead.
 */
#घोषणा irq_gc_lock_irqsave(gc, flags)	\
	raw_spin_lock_irqsave(&(gc)->lock, flags)

#घोषणा irq_gc_unlock_irqrestore(gc, flags)	\
	raw_spin_unlock_irqrestore(&(gc)->lock, flags)

अटल अंतरभूत व्योम irq_reg_ग_लिखोl(काष्ठा irq_chip_generic *gc,
				  u32 val, पूर्णांक reg_offset)
अणु
	अगर (gc->reg_ग_लिखोl)
		gc->reg_ग_लिखोl(val, gc->reg_base + reg_offset);
	अन्यथा
		ग_लिखोl(val, gc->reg_base + reg_offset);
पूर्ण

अटल अंतरभूत u32 irq_reg_पढ़ोl(काष्ठा irq_chip_generic *gc,
				पूर्णांक reg_offset)
अणु
	अगर (gc->reg_पढ़ोl)
		वापस gc->reg_पढ़ोl(gc->reg_base + reg_offset);
	अन्यथा
		वापस पढ़ोl(gc->reg_base + reg_offset);
पूर्ण

काष्ठा irq_matrix;
काष्ठा irq_matrix *irq_alloc_matrix(अचिन्हित पूर्णांक matrix_bits,
				    अचिन्हित पूर्णांक alloc_start,
				    अचिन्हित पूर्णांक alloc_end);
व्योम irq_matrix_online(काष्ठा irq_matrix *m);
व्योम irq_matrix_offline(काष्ठा irq_matrix *m);
व्योम irq_matrix_assign_प्रणाली(काष्ठा irq_matrix *m, अचिन्हित पूर्णांक bit, bool replace);
पूर्णांक irq_matrix_reserve_managed(काष्ठा irq_matrix *m, स्थिर काष्ठा cpumask *msk);
व्योम irq_matrix_हटाओ_managed(काष्ठा irq_matrix *m, स्थिर काष्ठा cpumask *msk);
पूर्णांक irq_matrix_alloc_managed(काष्ठा irq_matrix *m, स्थिर काष्ठा cpumask *msk,
				अचिन्हित पूर्णांक *mapped_cpu);
व्योम irq_matrix_reserve(काष्ठा irq_matrix *m);
व्योम irq_matrix_हटाओ_reserved(काष्ठा irq_matrix *m);
पूर्णांक irq_matrix_alloc(काष्ठा irq_matrix *m, स्थिर काष्ठा cpumask *msk,
		     bool reserved, अचिन्हित पूर्णांक *mapped_cpu);
व्योम irq_matrix_मुक्त(काष्ठा irq_matrix *m, अचिन्हित पूर्णांक cpu,
		     अचिन्हित पूर्णांक bit, bool managed);
व्योम irq_matrix_assign(काष्ठा irq_matrix *m, अचिन्हित पूर्णांक bit);
अचिन्हित पूर्णांक irq_matrix_available(काष्ठा irq_matrix *m, bool cpuकरोwn);
अचिन्हित पूर्णांक irq_matrix_allocated(काष्ठा irq_matrix *m);
अचिन्हित पूर्णांक irq_matrix_reserved(काष्ठा irq_matrix *m);
व्योम irq_matrix_debug_show(काष्ठा seq_file *sf, काष्ठा irq_matrix *m, पूर्णांक ind);

/* Contrary to Linux irqs, क्रम hardware irqs the irq number 0 is valid */
#घोषणा INVALID_HWIRQ	(~0UL)
irq_hw_number_t ipi_get_hwirq(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक cpu);
पूर्णांक __ipi_send_single(काष्ठा irq_desc *desc, अचिन्हित पूर्णांक cpu);
पूर्णांक __ipi_send_mask(काष्ठा irq_desc *desc, स्थिर काष्ठा cpumask *dest);
पूर्णांक ipi_send_single(अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक cpu);
पूर्णांक ipi_send_mask(अचिन्हित पूर्णांक virq, स्थिर काष्ठा cpumask *dest);

#अगर_घोषित CONFIG_GENERIC_IRQ_MULTI_HANDLER
/*
 * Registers a generic IRQ handling function as the top-level IRQ handler in
 * the प्रणाली, which is generally the first C code called from an assembly
 * architecture-specअगरic पूर्णांकerrupt handler.
 *
 * Returns 0 on success, or -EBUSY अगर an IRQ handler has alपढ़ोy been
 * रेजिस्टरed.
 */
पूर्णांक __init set_handle_irq(व्योम (*handle_irq)(काष्ठा pt_regs *));

/*
 * Allows पूर्णांकerrupt handlers to find the irqchip that's been रेजिस्टरed as the
 * top-level IRQ handler.
 */
बाह्य व्योम (*handle_arch_irq)(काष्ठा pt_regs *) __ro_after_init;
#अन्यथा
#अगर_अघोषित set_handle_irq
#घोषणा set_handle_irq(handle_irq)		\
	करो अणु					\
		(व्योम)handle_irq;		\
		WARN_ON(1);			\
	पूर्ण जबतक (0)
#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_IRQ_H */
