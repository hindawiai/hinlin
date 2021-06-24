<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2009 Daniel Hellstrom (daniel@gaisler.com) Aeroflex Gaisler AB
 * Copyright (C) 2009 Konrad Eisele (konrad@gaisler.com) Aeroflex Gaisler AB
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_device.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>

#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/leon.h>
#समावेश <यंत्र/leon_amba.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/setup.h>

#समावेश "kernel.h"
#समावेश "prom.h"
#समावेश "irq.h"

काष्ठा leon3_irqctrl_regs_map *leon3_irqctrl_regs; /* पूर्णांकerrupt controller base address */
काष्ठा leon3_gpसमयr_regs_map *leon3_gpसमयr_regs; /* समयr controller base address */

पूर्णांक leondebug_irq_disable;
पूर्णांक leon_debug_irqout;
अटल अस्थिर u32 dummy_master_l10_counter;
अचिन्हित दीर्घ amba_प्रणाली_id;
अटल DEFINE_SPINLOCK(leon_irq_lock);

अटल अचिन्हित दीर्घ leon3_gpसमयr_idx; /* Timer Index (0..6) within Timer Core */
अटल अचिन्हित दीर्घ leon3_gpसमयr_ackmask; /* For clearing pending bit */
अचिन्हित दीर्घ leon3_gpसमयr_irq; /* पूर्णांकerrupt controller irq number */
अचिन्हित पूर्णांक sparc_leon_eirq;
#घोषणा LEON_IMASK(cpu) (&leon3_irqctrl_regs->mask[cpu])
#घोषणा LEON_IACK (&leon3_irqctrl_regs->iclear)
#घोषणा LEON_DO_ACK_HW 1

/* Return the last ACKed IRQ by the Extended IRQ controller. It has alपढ़ोy
 * been (स्वतःmatically) ACKed when the CPU takes the trap.
 */
अटल अंतरभूत अचिन्हित पूर्णांक leon_eirq_get(पूर्णांक cpu)
अणु
	वापस LEON3_BYPASS_LOAD_PA(&leon3_irqctrl_regs->पूर्णांकid[cpu]) & 0x1f;
पूर्ण

/* Handle one or multiple IRQs from the extended पूर्णांकerrupt controller */
अटल व्योम leon_handle_ext_irq(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक eirq;
	काष्ठा irq_bucket *p;
	पूर्णांक cpu = sparc_leon3_cpuid();

	eirq = leon_eirq_get(cpu);
	p = irq_map[eirq];
	अगर ((eirq & 0x10) && p && p->irq) /* bit4 tells अगर IRQ happened */
		generic_handle_irq(p->irq);
पूर्ण

/* The extended IRQ controller has been found, this function रेजिस्टरs it */
अटल व्योम leon_eirq_setup(अचिन्हित पूर्णांक eirq)
अणु
	अचिन्हित दीर्घ mask, oldmask;
	अचिन्हित पूर्णांक veirq;

	अगर (eirq < 1 || eirq > 0xf) अणु
		prपूर्णांकk(KERN_ERR "LEON EXT IRQ NUMBER BAD: %d\n", eirq);
		वापस;
	पूर्ण

	veirq = leon_build_device_irq(eirq, leon_handle_ext_irq, "extirq", 0);

	/*
	 * Unmask the Extended IRQ, the IRQs routed through the Ext-IRQ
	 * controller have a mask-bit of their own, so this is safe.
	 */
	irq_link(veirq);
	mask = 1 << eirq;
	oldmask = LEON3_BYPASS_LOAD_PA(LEON_IMASK(boot_cpu_id));
	LEON3_BYPASS_STORE_PA(LEON_IMASK(boot_cpu_id), (oldmask | mask));
	sparc_leon_eirq = eirq;
पूर्ण

अचिन्हित दीर्घ leon_get_irqmask(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित दीर्घ mask;

	अगर (!irq || ((irq > 0xf) && !sparc_leon_eirq)
	    || ((irq > 0x1f) && sparc_leon_eirq)) अणु
		prपूर्णांकk(KERN_ERR
		       "leon_get_irqmask: false irq number: %d\n", irq);
		mask = 0;
	पूर्ण अन्यथा अणु
		mask = LEON_HARD_INT(irq);
	पूर्ण
	वापस mask;
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक irq_choose_cpu(स्थिर काष्ठा cpumask *affinity)
अणु
	cpumask_t mask;

	cpumask_and(&mask, cpu_online_mask, affinity);
	अगर (cpumask_equal(&mask, cpu_online_mask) || cpumask_empty(&mask))
		वापस boot_cpu_id;
	अन्यथा
		वापस cpumask_first(&mask);
पूर्ण
#अन्यथा
#घोषणा irq_choose_cpu(affinity) boot_cpu_id
#पूर्ण_अगर

अटल पूर्णांक leon_set_affinity(काष्ठा irq_data *data, स्थिर काष्ठा cpumask *dest,
			     bool क्रमce)
अणु
	अचिन्हित दीर्घ mask, oldmask, flags;
	पूर्णांक oldcpu, newcpu;

	mask = (अचिन्हित दीर्घ)data->chip_data;
	oldcpu = irq_choose_cpu(irq_data_get_affinity_mask(data));
	newcpu = irq_choose_cpu(dest);

	अगर (oldcpu == newcpu)
		जाओ out;

	/* unmask on old CPU first beक्रमe enabling on the selected CPU */
	spin_lock_irqsave(&leon_irq_lock, flags);
	oldmask = LEON3_BYPASS_LOAD_PA(LEON_IMASK(oldcpu));
	LEON3_BYPASS_STORE_PA(LEON_IMASK(oldcpu), (oldmask & ~mask));
	oldmask = LEON3_BYPASS_LOAD_PA(LEON_IMASK(newcpu));
	LEON3_BYPASS_STORE_PA(LEON_IMASK(newcpu), (oldmask | mask));
	spin_unlock_irqrestore(&leon_irq_lock, flags);
out:
	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल व्योम leon_unmask_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ mask, oldmask, flags;
	पूर्णांक cpu;

	mask = (अचिन्हित दीर्घ)data->chip_data;
	cpu = irq_choose_cpu(irq_data_get_affinity_mask(data));
	spin_lock_irqsave(&leon_irq_lock, flags);
	oldmask = LEON3_BYPASS_LOAD_PA(LEON_IMASK(cpu));
	LEON3_BYPASS_STORE_PA(LEON_IMASK(cpu), (oldmask | mask));
	spin_unlock_irqrestore(&leon_irq_lock, flags);
पूर्ण

अटल व्योम leon_mask_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ mask, oldmask, flags;
	पूर्णांक cpu;

	mask = (अचिन्हित दीर्घ)data->chip_data;
	cpu = irq_choose_cpu(irq_data_get_affinity_mask(data));
	spin_lock_irqsave(&leon_irq_lock, flags);
	oldmask = LEON3_BYPASS_LOAD_PA(LEON_IMASK(cpu));
	LEON3_BYPASS_STORE_PA(LEON_IMASK(cpu), (oldmask & ~mask));
	spin_unlock_irqrestore(&leon_irq_lock, flags);
पूर्ण

अटल अचिन्हित पूर्णांक leon_startup_irq(काष्ठा irq_data *data)
अणु
	irq_link(data->irq);
	leon_unmask_irq(data);
	वापस 0;
पूर्ण

अटल व्योम leon_shutकरोwn_irq(काष्ठा irq_data *data)
अणु
	leon_mask_irq(data);
	irq_unlink(data->irq);
पूर्ण

/* Used by बाह्यal level sensitive IRQ handlers on the LEON: ACK IRQ ctrl */
अटल व्योम leon_eoi_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ mask = (अचिन्हित दीर्घ)data->chip_data;

	अगर (mask & LEON_DO_ACK_HW)
		LEON3_BYPASS_STORE_PA(LEON_IACK, mask & ~LEON_DO_ACK_HW);
पूर्ण

अटल काष्ठा irq_chip leon_irq = अणु
	.name			= "leon",
	.irq_startup		= leon_startup_irq,
	.irq_shutकरोwn		= leon_shutकरोwn_irq,
	.irq_mask		= leon_mask_irq,
	.irq_unmask		= leon_unmask_irq,
	.irq_eoi		= leon_eoi_irq,
	.irq_set_affinity	= leon_set_affinity,
पूर्ण;

/*
 * Build a LEON IRQ क्रम the edge triggered LEON IRQ controller:
 *  Edge (normal) IRQ           - handle_simple_irq, ack=DON'T-CARE, never ack
 *  Level IRQ (PCI|Level-GPIO)  - handle_fasteoi_irq, ack=1, ack after ISR
 *  Per-CPU Edge                - handle_percpu_irq, ack=0
 */
अचिन्हित पूर्णांक leon_build_device_irq(अचिन्हित पूर्णांक real_irq,
				    irq_flow_handler_t flow_handler,
				    स्थिर अक्षर *name, पूर्णांक करो_ack)
अणु
	अचिन्हित पूर्णांक irq;
	अचिन्हित दीर्घ mask;
	काष्ठा irq_desc *desc;

	irq = 0;
	mask = leon_get_irqmask(real_irq);
	अगर (mask == 0)
		जाओ out;

	irq = irq_alloc(real_irq, real_irq);
	अगर (irq == 0)
		जाओ out;

	अगर (करो_ack)
		mask |= LEON_DO_ACK_HW;

	desc = irq_to_desc(irq);
	अगर (!desc || !desc->handle_irq || desc->handle_irq == handle_bad_irq) अणु
		irq_set_chip_and_handler_name(irq, &leon_irq,
					      flow_handler, name);
		irq_set_chip_data(irq, (व्योम *)mask);
	पूर्ण

out:
	वापस irq;
पूर्ण

अटल अचिन्हित पूर्णांक _leon_build_device_irq(काष्ठा platक्रमm_device *op,
					   अचिन्हित पूर्णांक real_irq)
अणु
	वापस leon_build_device_irq(real_irq, handle_simple_irq, "edge", 0);
पूर्ण

व्योम leon_update_virq_handling(अचिन्हित पूर्णांक virq,
			      irq_flow_handler_t flow_handler,
			      स्थिर अक्षर *name, पूर्णांक करो_ack)
अणु
	अचिन्हित दीर्घ mask = (अचिन्हित दीर्घ)irq_get_chip_data(virq);

	mask &= ~LEON_DO_ACK_HW;
	अगर (करो_ack)
		mask |= LEON_DO_ACK_HW;

	irq_set_chip_and_handler_name(virq, &leon_irq,
				      flow_handler, name);
	irq_set_chip_data(virq, (व्योम *)mask);
पूर्ण

अटल u32 leon_cycles_offset(व्योम)
अणु
	u32 rld, val, ctrl, off;

	rld = LEON3_BYPASS_LOAD_PA(&leon3_gpसमयr_regs->e[leon3_gpसमयr_idx].rld);
	val = LEON3_BYPASS_LOAD_PA(&leon3_gpसमयr_regs->e[leon3_gpसमयr_idx].val);
	ctrl = LEON3_BYPASS_LOAD_PA(&leon3_gpसमयr_regs->e[leon3_gpसमयr_idx].ctrl);
	अगर (LEON3_GPTIMER_CTRL_ISPENDING(ctrl)) अणु
		val = LEON3_BYPASS_LOAD_PA(&leon3_gpसमयr_regs->e[leon3_gpसमयr_idx].val);
		off = 2 * rld - val;
	पूर्ण अन्यथा अणु
		off = rld - val;
	पूर्ण

	वापस off;
पूर्ण

#अगर_घोषित CONFIG_SMP

/* smp घड़ीevent irq */
अटल irqवापस_t leon_percpu_समयr_ce_पूर्णांकerrupt(पूर्णांक irq, व्योम *unused)
अणु
	काष्ठा घड़ी_event_device *ce;
	पूर्णांक cpu = smp_processor_id();

	leon_clear_profile_irq(cpu);

	अगर (cpu == boot_cpu_id)
		समयr_पूर्णांकerrupt(irq, शून्य);

	ce = &per_cpu(sparc32_घड़ीevent, cpu);

	irq_enter();
	अगर (ce->event_handler)
		ce->event_handler(ce);
	irq_निकास();

	वापस IRQ_HANDLED;
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

व्योम __init leon_init_समयrs(व्योम)
अणु
	पूर्णांक irq, eirq;
	काष्ठा device_node *rootnp, *np, *nnp;
	काष्ठा property *pp;
	पूर्णांक len;
	पूर्णांक icsel;
	पूर्णांक ampopts;
	पूर्णांक err;
	u32 config;
	u32 ctrl;

	sparc_config.get_cycles_offset = leon_cycles_offset;
	sparc_config.cs_period = 1000000 / HZ;
	sparc_config.features |= FEAT_L10_CLOCKSOURCE;

#अगर_अघोषित CONFIG_SMP
	sparc_config.features |= FEAT_L10_CLOCKEVENT;
#पूर्ण_अगर

	leondebug_irq_disable = 0;
	leon_debug_irqout = 0;
	master_l10_counter = (u32 __iomem *)&dummy_master_l10_counter;
	dummy_master_l10_counter = 0;

	rootnp = of_find_node_by_path("/ambapp0");
	अगर (!rootnp)
		जाओ bad;

	/* Find System ID: GRLIB build ID and optional CHIP ID */
	pp = of_find_property(rootnp, "systemid", &len);
	अगर (pp)
		amba_प्रणाली_id = *(अचिन्हित दीर्घ *)pp->value;

	/* Find IRQMP IRQ Controller Registers base adr otherwise bail out */
	np = of_find_node_by_name(rootnp, "GAISLER_IRQMP");
	अगर (!np) अणु
		np = of_find_node_by_name(rootnp, "01_00d");
		अगर (!np)
			जाओ bad;
	पूर्ण
	pp = of_find_property(np, "reg", &len);
	अगर (!pp)
		जाओ bad;
	leon3_irqctrl_regs = *(काष्ठा leon3_irqctrl_regs_map **)pp->value;

	/* Find GPTIMER Timer Registers base address otherwise bail out. */
	nnp = rootnp;

retry:
	np = of_find_node_by_name(nnp, "GAISLER_GPTIMER");
	अगर (!np) अणु
		np = of_find_node_by_name(nnp, "01_011");
		अगर (!np)
			जाओ bad;
	पूर्ण

	ampopts = 0;
	pp = of_find_property(np, "ampopts", &len);
	अगर (pp) अणु
		ampopts = *(पूर्णांक *)pp->value;
		अगर (ampopts == 0) अणु
			/* Skip this instance, resource alपढ़ोy
			 * allocated by other OS */
			nnp = np;
			जाओ retry;
		पूर्ण
	पूर्ण

	/* Select Timer-Instance on Timer Core. Default is zero */
	leon3_gpसमयr_idx = ampopts & 0x7;

	pp = of_find_property(np, "reg", &len);
	अगर (pp)
		leon3_gpसमयr_regs = *(काष्ठा leon3_gpसमयr_regs_map **)
					pp->value;
	pp = of_find_property(np, "interrupts", &len);
	अगर (pp)
		leon3_gpसमयr_irq = *(अचिन्हित पूर्णांक *)pp->value;

	अगर (!(leon3_gpसमयr_regs && leon3_irqctrl_regs && leon3_gpसमयr_irq))
		जाओ bad;

	ctrl = LEON3_BYPASS_LOAD_PA(&leon3_gpसमयr_regs->e[leon3_gpसमयr_idx].ctrl);
	LEON3_BYPASS_STORE_PA(&leon3_gpसमयr_regs->e[leon3_gpसमयr_idx].ctrl,
			      ctrl | LEON3_GPTIMER_CTRL_PENDING);
	ctrl = LEON3_BYPASS_LOAD_PA(&leon3_gpसमयr_regs->e[leon3_gpसमयr_idx].ctrl);

	अगर ((ctrl & LEON3_GPTIMER_CTRL_PENDING) != 0)
		leon3_gpसमयr_ackmask = ~LEON3_GPTIMER_CTRL_PENDING;
	अन्यथा
		leon3_gpसमयr_ackmask = ~0;

	LEON3_BYPASS_STORE_PA(&leon3_gpसमयr_regs->e[leon3_gpसमयr_idx].val, 0);
	LEON3_BYPASS_STORE_PA(&leon3_gpसमयr_regs->e[leon3_gpसमयr_idx].rld,
				(((1000000 / HZ) - 1)));
	LEON3_BYPASS_STORE_PA(
			&leon3_gpसमयr_regs->e[leon3_gpसमयr_idx].ctrl, 0);

	/*
	 * The IRQ controller may (अगर implemented) consist of multiple
	 * IRQ controllers, each mapped on a 4Kb boundary.
	 * Each CPU may be routed to dअगरferent IRQCTRLs, however
	 * we assume that all CPUs (in SMP प्रणाली) is routed to the
	 * same IRQ Controller, and क्रम non-SMP only one IRQCTRL is
	 * accessed anyway.
	 * In AMP प्रणालीs, Linux must run on CPU0 क्रम the समय being.
	 */
	icsel = LEON3_BYPASS_LOAD_PA(&leon3_irqctrl_regs->icsel[boot_cpu_id/8]);
	icsel = (icsel >> ((7 - (boot_cpu_id&0x7)) * 4)) & 0xf;
	leon3_irqctrl_regs += icsel;

	/* Mask all IRQs on boot-cpu IRQ controller */
	LEON3_BYPASS_STORE_PA(&leon3_irqctrl_regs->mask[boot_cpu_id], 0);

	/* Probe extended IRQ controller */
	eirq = (LEON3_BYPASS_LOAD_PA(&leon3_irqctrl_regs->mpstatus)
		>> 16) & 0xf;
	अगर (eirq != 0)
		leon_eirq_setup(eirq);

#अगर_घोषित CONFIG_SMP
	अणु
		अचिन्हित दीर्घ flags;

		/*
		 * In SMP, sun4m adds a IPI handler to IRQ trap handler that
		 * LEON never must take, sun4d and LEON overग_लिखोs the branch
		 * with a NOP.
		 */
		local_irq_save(flags);
		patchme_maybe_smp_msg[0] = 0x01000000; /* NOP out the branch */
		local_ops->cache_all();
		local_irq_restore(flags);
	पूर्ण
#पूर्ण_अगर

	config = LEON3_BYPASS_LOAD_PA(&leon3_gpसमयr_regs->config);
	अगर (config & (1 << LEON3_GPTIMER_SEPIRQ))
		leon3_gpसमयr_irq += leon3_gpसमयr_idx;
	अन्यथा अगर ((config & LEON3_GPTIMER_TIMERS) > 1)
		pr_warn("GPTIMER uses shared irqs, using other timers of the same core will fail.\n");

#अगर_घोषित CONFIG_SMP
	/* Install per-cpu IRQ handler क्रम broadcasted ticker */
	irq = leon_build_device_irq(leon3_gpसमयr_irq, handle_percpu_irq,
				    "per-cpu", 0);
	err = request_irq(irq, leon_percpu_समयr_ce_पूर्णांकerrupt,
			  IRQF_PERCPU | IRQF_TIMER, "timer", शून्य);
#अन्यथा
	irq = _leon_build_device_irq(शून्य, leon3_gpसमयr_irq);
	err = request_irq(irq, समयr_पूर्णांकerrupt, IRQF_TIMER, "timer", शून्य);
#पूर्ण_अगर
	अगर (err) अणु
		pr_err("Unable to attach timer IRQ%d\n", irq);
		prom_halt();
	पूर्ण
	LEON3_BYPASS_STORE_PA(&leon3_gpसमयr_regs->e[leon3_gpसमयr_idx].ctrl,
			      LEON3_GPTIMER_EN |
			      LEON3_GPTIMER_RL |
			      LEON3_GPTIMER_LD |
			      LEON3_GPTIMER_IRQEN);
	वापस;
bad:
	prपूर्णांकk(KERN_ERR "No Timer/irqctrl found\n");
	BUG();
	वापस;
पूर्ण

अटल व्योम leon_clear_घड़ी_irq(व्योम)
अणु
	u32 ctrl;

	ctrl = LEON3_BYPASS_LOAD_PA(&leon3_gpसमयr_regs->e[leon3_gpसमयr_idx].ctrl);
	LEON3_BYPASS_STORE_PA(&leon3_gpसमयr_regs->e[leon3_gpसमयr_idx].ctrl,
			      ctrl & leon3_gpसमयr_ackmask);
पूर्ण

अटल व्योम leon_load_profile_irq(पूर्णांक cpu, अचिन्हित पूर्णांक limit)
अणु
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम leon_clear_profile_irq(पूर्णांक cpu)
अणु
पूर्ण

व्योम leon_enable_irq_cpu(अचिन्हित पूर्णांक irq_nr, अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ mask, flags, *addr;
	mask = leon_get_irqmask(irq_nr);
	spin_lock_irqsave(&leon_irq_lock, flags);
	addr = (अचिन्हित दीर्घ *)LEON_IMASK(cpu);
	LEON3_BYPASS_STORE_PA(addr, (LEON3_BYPASS_LOAD_PA(addr) | mask));
	spin_unlock_irqrestore(&leon_irq_lock, flags);
पूर्ण

#पूर्ण_अगर

व्योम __init leon_init_IRQ(व्योम)
अणु
	sparc_config.init_समयrs      = leon_init_समयrs;
	sparc_config.build_device_irq = _leon_build_device_irq;
	sparc_config.घड़ी_rate       = 1000000;
	sparc_config.clear_घड़ी_irq  = leon_clear_घड़ी_irq;
	sparc_config.load_profile_irq = leon_load_profile_irq;
पूर्ण
