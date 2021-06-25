<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Internal header to deal with irq_desc->status which will be नामd
 * to irq_desc->settings.
 */
क्रमागत अणु
	_IRQ_DEFAULT_INIT_FLAGS	= IRQ_DEFAULT_INIT_FLAGS,
	_IRQ_PER_CPU		= IRQ_PER_CPU,
	_IRQ_LEVEL		= IRQ_LEVEL,
	_IRQ_NOPROBE		= IRQ_NOPROBE,
	_IRQ_NOREQUEST		= IRQ_NOREQUEST,
	_IRQ_NOTHREAD		= IRQ_NOTHREAD,
	_IRQ_NOAUTOEN		= IRQ_NOAUTOEN,
	_IRQ_MOVE_PCNTXT	= IRQ_MOVE_PCNTXT,
	_IRQ_NO_BALANCING	= IRQ_NO_BALANCING,
	_IRQ_NESTED_THREAD	= IRQ_NESTED_THREAD,
	_IRQ_PER_CPU_DEVID	= IRQ_PER_CPU_DEVID,
	_IRQ_IS_POLLED		= IRQ_IS_POLLED,
	_IRQ_DISABLE_UNLAZY	= IRQ_DISABLE_UNLAZY,
	_IRQ_HIDDEN		= IRQ_HIDDEN,
	_IRQF_MODIFY_MASK	= IRQF_MODIFY_MASK,
पूर्ण;

#घोषणा IRQ_PER_CPU		GOT_YOU_MORON
#घोषणा IRQ_NO_BALANCING	GOT_YOU_MORON
#घोषणा IRQ_LEVEL		GOT_YOU_MORON
#घोषणा IRQ_NOPROBE		GOT_YOU_MORON
#घोषणा IRQ_NOREQUEST		GOT_YOU_MORON
#घोषणा IRQ_NOTHREAD		GOT_YOU_MORON
#घोषणा IRQ_NOAUTOEN		GOT_YOU_MORON
#घोषणा IRQ_NESTED_THREAD	GOT_YOU_MORON
#घोषणा IRQ_PER_CPU_DEVID	GOT_YOU_MORON
#घोषणा IRQ_IS_POLLED		GOT_YOU_MORON
#घोषणा IRQ_DISABLE_UNLAZY	GOT_YOU_MORON
#घोषणा IRQ_HIDDEN		GOT_YOU_MORON
#अघोषित IRQF_MODIFY_MASK
#घोषणा IRQF_MODIFY_MASK	GOT_YOU_MORON

अटल अंतरभूत व्योम
irq_settings_clr_and_set(काष्ठा irq_desc *desc, u32 clr, u32 set)
अणु
	desc->status_use_accessors &= ~(clr & _IRQF_MODIFY_MASK);
	desc->status_use_accessors |= (set & _IRQF_MODIFY_MASK);
पूर्ण

अटल अंतरभूत bool irq_settings_is_per_cpu(काष्ठा irq_desc *desc)
अणु
	वापस desc->status_use_accessors & _IRQ_PER_CPU;
पूर्ण

अटल अंतरभूत bool irq_settings_is_per_cpu_devid(काष्ठा irq_desc *desc)
अणु
	वापस desc->status_use_accessors & _IRQ_PER_CPU_DEVID;
पूर्ण

अटल अंतरभूत व्योम irq_settings_set_per_cpu(काष्ठा irq_desc *desc)
अणु
	desc->status_use_accessors |= _IRQ_PER_CPU;
पूर्ण

अटल अंतरभूत व्योम irq_settings_set_no_balancing(काष्ठा irq_desc *desc)
अणु
	desc->status_use_accessors |= _IRQ_NO_BALANCING;
पूर्ण

अटल अंतरभूत bool irq_settings_has_no_balance_set(काष्ठा irq_desc *desc)
अणु
	वापस desc->status_use_accessors & _IRQ_NO_BALANCING;
पूर्ण

अटल अंतरभूत u32 irq_settings_get_trigger_mask(काष्ठा irq_desc *desc)
अणु
	वापस desc->status_use_accessors & IRQ_TYPE_SENSE_MASK;
पूर्ण

अटल अंतरभूत व्योम
irq_settings_set_trigger_mask(काष्ठा irq_desc *desc, u32 mask)
अणु
	desc->status_use_accessors &= ~IRQ_TYPE_SENSE_MASK;
	desc->status_use_accessors |= mask & IRQ_TYPE_SENSE_MASK;
पूर्ण

अटल अंतरभूत bool irq_settings_is_level(काष्ठा irq_desc *desc)
अणु
	वापस desc->status_use_accessors & _IRQ_LEVEL;
पूर्ण

अटल अंतरभूत व्योम irq_settings_clr_level(काष्ठा irq_desc *desc)
अणु
	desc->status_use_accessors &= ~_IRQ_LEVEL;
पूर्ण

अटल अंतरभूत व्योम irq_settings_set_level(काष्ठा irq_desc *desc)
अणु
	desc->status_use_accessors |= _IRQ_LEVEL;
पूर्ण

अटल अंतरभूत bool irq_settings_can_request(काष्ठा irq_desc *desc)
अणु
	वापस !(desc->status_use_accessors & _IRQ_NOREQUEST);
पूर्ण

अटल अंतरभूत व्योम irq_settings_clr_norequest(काष्ठा irq_desc *desc)
अणु
	desc->status_use_accessors &= ~_IRQ_NOREQUEST;
पूर्ण

अटल अंतरभूत व्योम irq_settings_set_norequest(काष्ठा irq_desc *desc)
अणु
	desc->status_use_accessors |= _IRQ_NOREQUEST;
पूर्ण

अटल अंतरभूत bool irq_settings_can_thपढ़ो(काष्ठा irq_desc *desc)
अणु
	वापस !(desc->status_use_accessors & _IRQ_NOTHREAD);
पूर्ण

अटल अंतरभूत व्योम irq_settings_clr_nothपढ़ो(काष्ठा irq_desc *desc)
अणु
	desc->status_use_accessors &= ~_IRQ_NOTHREAD;
पूर्ण

अटल अंतरभूत व्योम irq_settings_set_nothपढ़ो(काष्ठा irq_desc *desc)
अणु
	desc->status_use_accessors |= _IRQ_NOTHREAD;
पूर्ण

अटल अंतरभूत bool irq_settings_can_probe(काष्ठा irq_desc *desc)
अणु
	वापस !(desc->status_use_accessors & _IRQ_NOPROBE);
पूर्ण

अटल अंतरभूत व्योम irq_settings_clr_noprobe(काष्ठा irq_desc *desc)
अणु
	desc->status_use_accessors &= ~_IRQ_NOPROBE;
पूर्ण

अटल अंतरभूत व्योम irq_settings_set_noprobe(काष्ठा irq_desc *desc)
अणु
	desc->status_use_accessors |= _IRQ_NOPROBE;
पूर्ण

अटल अंतरभूत bool irq_settings_can_move_pcntxt(काष्ठा irq_desc *desc)
अणु
	वापस desc->status_use_accessors & _IRQ_MOVE_PCNTXT;
पूर्ण

अटल अंतरभूत bool irq_settings_can_स्वतःenable(काष्ठा irq_desc *desc)
अणु
	वापस !(desc->status_use_accessors & _IRQ_NOAUTOEN);
पूर्ण

अटल अंतरभूत bool irq_settings_is_nested_thपढ़ो(काष्ठा irq_desc *desc)
अणु
	वापस desc->status_use_accessors & _IRQ_NESTED_THREAD;
पूर्ण

अटल अंतरभूत bool irq_settings_is_polled(काष्ठा irq_desc *desc)
अणु
	वापस desc->status_use_accessors & _IRQ_IS_POLLED;
पूर्ण

अटल अंतरभूत bool irq_settings_disable_unlazy(काष्ठा irq_desc *desc)
अणु
	वापस desc->status_use_accessors & _IRQ_DISABLE_UNLAZY;
पूर्ण

अटल अंतरभूत व्योम irq_settings_clr_disable_unlazy(काष्ठा irq_desc *desc)
अणु
	desc->status_use_accessors &= ~_IRQ_DISABLE_UNLAZY;
पूर्ण

अटल अंतरभूत bool irq_settings_is_hidden(काष्ठा irq_desc *desc)
अणु
	वापस desc->status_use_accessors & _IRQ_HIDDEN;
पूर्ण
