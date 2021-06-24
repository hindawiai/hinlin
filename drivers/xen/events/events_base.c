<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Xen event channels
 *
 * Xen models पूर्णांकerrupts with असलtract event channels.  Because each
 * करोमुख्य माला_लो 1024 event channels, but NR_IRQ is not that large, we
 * must dynamically map irqs<->event channels.  The event channels
 * पूर्णांकerface with the rest of the kernel by defining a xen पूर्णांकerrupt
 * chip.  When an event is received, it is mapped to an irq and sent
 * through the normal पूर्णांकerrupt processing path.
 *
 * There are four kinds of events which can be mapped to an event
 * channel:
 *
 * 1. Inter-करोमुख्य notअगरications.  This includes all the भव
 *    device events, since they're driven by front-ends in another करोमुख्य
 *    (typically करोm0).
 * 2. VIRQs, typically used क्रम समयrs.  These are per-cpu events.
 * 3. IPIs.
 * 4. PIRQs - Hardware पूर्णांकerrupts.
 *
 * Jeremy Fitzhardinge <jeremy@xensource.com>, XenSource Inc, 2007
 */

#घोषणा pr_fmt(fmt) "xen:" KBUILD_MODNAME ": " fmt

#समावेश <linux/linkage.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/माला.स>
#समावेश <linux/memblock.h>
#समावेश <linux/slab.h>
#समावेश <linux/irqnr.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/atomic.h>
#समावेश <linux/kसमय.स>

#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/idtentry.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/xen/pci.h>
#पूर्ण_अगर
#समावेश <यंत्र/sync_bitops.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <xen/page.h>

#समावेश <xen/xen.h>
#समावेश <xen/hvm.h>
#समावेश <xen/xen-ops.h>
#समावेश <xen/events.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/event_channel.h>
#समावेश <xen/पूर्णांकerface/hvm/hvm_op.h>
#समावेश <xen/पूर्णांकerface/hvm/params.h>
#समावेश <xen/पूर्णांकerface/physdev.h>
#समावेश <xen/पूर्णांकerface/sched.h>
#समावेश <xen/पूर्णांकerface/vcpu.h>
#समावेश <xen/xenbus.h>
#समावेश <यंत्र/hw_irq.h>

#समावेश "events_internal.h"

#अघोषित MODULE_PARAM_PREFIX
#घोषणा MODULE_PARAM_PREFIX "xen."

/* Interrupt types. */
क्रमागत xen_irq_type अणु
	IRQT_UNBOUND = 0,
	IRQT_PIRQ,
	IRQT_VIRQ,
	IRQT_IPI,
	IRQT_EVTCHN
पूर्ण;

/*
 * Packed IRQ inक्रमmation:
 * type - क्रमागत xen_irq_type
 * event channel - irq->event channel mapping
 * cpu - cpu this event channel is bound to
 * index - type-specअगरic inक्रमmation:
 *    PIRQ - vector, with MSB being "needs EIO", or physical IRQ of the HVM
 *           guest, or GSI (real passthrough IRQ) of the device.
 *    VIRQ - virq number
 *    IPI - IPI vector
 *    EVTCHN -
 */
काष्ठा irq_info अणु
	काष्ठा list_head list;
	काष्ठा list_head eoi_list;
	लघु refcnt;
	u8 spurious_cnt;
	u8 is_accounted;
	लघु type;		/* type: IRQT_* */
	u8 mask_reason;		/* Why is event channel masked */
#घोषणा EVT_MASK_REASON_EXPLICIT	0x01
#घोषणा EVT_MASK_REASON_TEMPORARY	0x02
#घोषणा EVT_MASK_REASON_EOI_PENDING	0x04
	u8 is_active;		/* Is event just being handled? */
	अचिन्हित irq;
	evtchn_port_t evtchn;   /* event channel */
	अचिन्हित लघु cpu;     /* cpu bound */
	अचिन्हित लघु eoi_cpu; /* EOI must happen on this cpu-1 */
	अचिन्हित पूर्णांक irq_epoch; /* If eoi_cpu valid: irq_epoch of event */
	u64 eoi_समय;           /* Time in jअगरfies when to EOI. */
	raw_spinlock_t lock;

	जोड़ अणु
		अचिन्हित लघु virq;
		क्रमागत ipi_vector ipi;
		काष्ठा अणु
			अचिन्हित लघु pirq;
			अचिन्हित लघु gsi;
			अचिन्हित अक्षर vector;
			अचिन्हित अक्षर flags;
			uपूर्णांक16_t करोmid;
		पूर्ण pirq;
		काष्ठा xenbus_device *पूर्णांकerकरोमुख्य;
	पूर्ण u;
पूर्ण;

#घोषणा PIRQ_NEEDS_EOI	(1 << 0)
#घोषणा PIRQ_SHAREABLE	(1 << 1)
#घोषणा PIRQ_MSI_GROUP	(1 << 2)

अटल uपूर्णांक __पढ़ो_mostly event_loop_समयout = 2;
module_param(event_loop_समयout, uपूर्णांक, 0644);

अटल uपूर्णांक __पढ़ो_mostly event_eoi_delay = 10;
module_param(event_eoi_delay, uपूर्णांक, 0644);

स्थिर काष्ठा evtchn_ops *evtchn_ops;

/*
 * This lock protects updates to the following mapping and reference-count
 * arrays. The lock करोes not need to be acquired to पढ़ो the mapping tables.
 */
अटल DEFINE_MUTEX(irq_mapping_update_lock);

/*
 * Lock protecting event handling loop against removing event channels.
 * Adding of event channels is no issue as the associated IRQ becomes active
 * only after everything is setup (beक्रमe request_[thपढ़ोed_]irq() the handler
 * can't be entered क्रम an event, as the event channel will be unmasked only
 * then).
 */
अटल DEFINE_RWLOCK(evtchn_rwlock);

/*
 * Lock hierarchy:
 *
 * irq_mapping_update_lock
 *   evtchn_rwlock
 *     IRQ-desc lock
 *       percpu eoi_list_lock
 *         irq_info->lock
 */

अटल LIST_HEAD(xen_irq_list_head);

/* IRQ <-> VIRQ mapping. */
अटल DEFINE_PER_CPU(पूर्णांक [NR_VIRQS], virq_to_irq) = अणु[0 ... NR_VIRQS-1] = -1पूर्ण;

/* IRQ <-> IPI mapping */
अटल DEFINE_PER_CPU(पूर्णांक [XEN_NR_IPIS], ipi_to_irq) = अणु[0 ... XEN_NR_IPIS-1] = -1पूर्ण;

/* Event channel distribution data */
अटल atomic_t channels_on_cpu[NR_CPUS];

अटल पूर्णांक **evtchn_to_irq;
#अगर_घोषित CONFIG_X86
अटल अचिन्हित दीर्घ *pirq_eoi_map;
#पूर्ण_अगर
अटल bool (*pirq_needs_eoi)(अचिन्हित irq);

#घोषणा EVTCHN_ROW(e)  (e / (PAGE_SIZE/माप(**evtchn_to_irq)))
#घोषणा EVTCHN_COL(e)  (e % (PAGE_SIZE/माप(**evtchn_to_irq)))
#घोषणा EVTCHN_PER_ROW (PAGE_SIZE / माप(**evtchn_to_irq))

/* Xen will never allocate port zero क्रम any purpose. */
#घोषणा VALID_EVTCHN(chn)	((chn) != 0)

अटल काष्ठा irq_info *legacy_info_ptrs[NR_IRQS_LEGACY];

अटल काष्ठा irq_chip xen_dynamic_chip;
अटल काष्ठा irq_chip xen_lateeoi_chip;
अटल काष्ठा irq_chip xen_percpu_chip;
अटल काष्ठा irq_chip xen_pirq_chip;
अटल व्योम enable_dynirq(काष्ठा irq_data *data);
अटल व्योम disable_dynirq(काष्ठा irq_data *data);

अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, irq_epoch);

अटल व्योम clear_evtchn_to_irq_row(अचिन्हित row)
अणु
	अचिन्हित col;

	क्रम (col = 0; col < EVTCHN_PER_ROW; col++)
		WRITE_ONCE(evtchn_to_irq[row][col], -1);
पूर्ण

अटल व्योम clear_evtchn_to_irq_all(व्योम)
अणु
	अचिन्हित row;

	क्रम (row = 0; row < EVTCHN_ROW(xen_evtchn_max_channels()); row++) अणु
		अगर (evtchn_to_irq[row] == शून्य)
			जारी;
		clear_evtchn_to_irq_row(row);
	पूर्ण
पूर्ण

अटल पूर्णांक set_evtchn_to_irq(evtchn_port_t evtchn, अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित row;
	अचिन्हित col;

	अगर (evtchn >= xen_evtchn_max_channels())
		वापस -EINVAL;

	row = EVTCHN_ROW(evtchn);
	col = EVTCHN_COL(evtchn);

	अगर (evtchn_to_irq[row] == शून्य) अणु
		/* Unallocated irq entries वापस -1 anyway */
		अगर (irq == -1)
			वापस 0;

		evtchn_to_irq[row] = (पूर्णांक *)get_zeroed_page(GFP_KERNEL);
		अगर (evtchn_to_irq[row] == शून्य)
			वापस -ENOMEM;

		clear_evtchn_to_irq_row(row);
	पूर्ण

	WRITE_ONCE(evtchn_to_irq[row][col], irq);
	वापस 0;
पूर्ण

पूर्णांक get_evtchn_to_irq(evtchn_port_t evtchn)
अणु
	अगर (evtchn >= xen_evtchn_max_channels())
		वापस -1;
	अगर (evtchn_to_irq[EVTCHN_ROW(evtchn)] == शून्य)
		वापस -1;
	वापस READ_ONCE(evtchn_to_irq[EVTCHN_ROW(evtchn)][EVTCHN_COL(evtchn)]);
पूर्ण

/* Get info क्रम IRQ */
अटल काष्ठा irq_info *info_क्रम_irq(अचिन्हित irq)
अणु
	अगर (irq < nr_legacy_irqs())
		वापस legacy_info_ptrs[irq];
	अन्यथा
		वापस irq_get_chip_data(irq);
पूर्ण

अटल व्योम set_info_क्रम_irq(अचिन्हित पूर्णांक irq, काष्ठा irq_info *info)
अणु
	अगर (irq < nr_legacy_irqs())
		legacy_info_ptrs[irq] = info;
	अन्यथा
		irq_set_chip_data(irq, info);
पूर्ण

/* Per CPU channel accounting */
अटल व्योम channels_on_cpu_dec(काष्ठा irq_info *info)
अणु
	अगर (!info->is_accounted)
		वापस;

	info->is_accounted = 0;

	अगर (WARN_ON_ONCE(info->cpu >= nr_cpu_ids))
		वापस;

	WARN_ON_ONCE(!atomic_add_unless(&channels_on_cpu[info->cpu], -1 , 0));
पूर्ण

अटल व्योम channels_on_cpu_inc(काष्ठा irq_info *info)
अणु
	अगर (WARN_ON_ONCE(info->cpu >= nr_cpu_ids))
		वापस;

	अगर (WARN_ON_ONCE(!atomic_add_unless(&channels_on_cpu[info->cpu], 1,
					    पूर्णांक_उच्च)))
		वापस;

	info->is_accounted = 1;
पूर्ण

/* Conकाष्ठाors क्रम packed IRQ inक्रमmation. */
अटल पूर्णांक xen_irq_info_common_setup(काष्ठा irq_info *info,
				     अचिन्हित irq,
				     क्रमागत xen_irq_type type,
				     evtchn_port_t evtchn,
				     अचिन्हित लघु cpu)
अणु
	पूर्णांक ret;

	BUG_ON(info->type != IRQT_UNBOUND && info->type != type);

	info->type = type;
	info->irq = irq;
	info->evtchn = evtchn;
	info->cpu = cpu;
	info->mask_reason = EVT_MASK_REASON_EXPLICIT;
	raw_spin_lock_init(&info->lock);

	ret = set_evtchn_to_irq(evtchn, irq);
	अगर (ret < 0)
		वापस ret;

	irq_clear_status_flags(irq, IRQ_NOREQUEST|IRQ_NOAUTOEN);

	वापस xen_evtchn_port_setup(evtchn);
पूर्ण

अटल पूर्णांक xen_irq_info_evtchn_setup(अचिन्हित irq,
				     evtchn_port_t evtchn,
				     काष्ठा xenbus_device *dev)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(irq);
	पूर्णांक ret;

	ret = xen_irq_info_common_setup(info, irq, IRQT_EVTCHN, evtchn, 0);
	info->u.पूर्णांकerकरोमुख्य = dev;
	अगर (dev)
		atomic_inc(&dev->event_channels);

	वापस ret;
पूर्ण

अटल पूर्णांक xen_irq_info_ipi_setup(अचिन्हित cpu,
				  अचिन्हित irq,
				  evtchn_port_t evtchn,
				  क्रमागत ipi_vector ipi)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(irq);

	info->u.ipi = ipi;

	per_cpu(ipi_to_irq, cpu)[ipi] = irq;

	वापस xen_irq_info_common_setup(info, irq, IRQT_IPI, evtchn, 0);
पूर्ण

अटल पूर्णांक xen_irq_info_virq_setup(अचिन्हित cpu,
				   अचिन्हित irq,
				   evtchn_port_t evtchn,
				   अचिन्हित virq)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(irq);

	info->u.virq = virq;

	per_cpu(virq_to_irq, cpu)[virq] = irq;

	वापस xen_irq_info_common_setup(info, irq, IRQT_VIRQ, evtchn, 0);
पूर्ण

अटल पूर्णांक xen_irq_info_pirq_setup(अचिन्हित irq,
				   evtchn_port_t evtchn,
				   अचिन्हित pirq,
				   अचिन्हित gsi,
				   uपूर्णांक16_t करोmid,
				   अचिन्हित अक्षर flags)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(irq);

	info->u.pirq.pirq = pirq;
	info->u.pirq.gsi = gsi;
	info->u.pirq.करोmid = करोmid;
	info->u.pirq.flags = flags;

	वापस xen_irq_info_common_setup(info, irq, IRQT_PIRQ, evtchn, 0);
पूर्ण

अटल व्योम xen_irq_info_cleanup(काष्ठा irq_info *info)
अणु
	set_evtchn_to_irq(info->evtchn, -1);
	xen_evtchn_port_हटाओ(info->evtchn, info->cpu);
	info->evtchn = 0;
	channels_on_cpu_dec(info);
पूर्ण

/*
 * Accessors क्रम packed IRQ inक्रमmation.
 */
evtchn_port_t evtchn_from_irq(अचिन्हित irq)
अणु
	स्थिर काष्ठा irq_info *info = शून्य;

	अगर (likely(irq < nr_irqs))
		info = info_क्रम_irq(irq);
	अगर (!info)
		वापस 0;

	वापस info->evtchn;
पूर्ण

अचिन्हित पूर्णांक irq_from_evtchn(evtchn_port_t evtchn)
अणु
	वापस get_evtchn_to_irq(evtchn);
पूर्ण
EXPORT_SYMBOL_GPL(irq_from_evtchn);

पूर्णांक irq_from_virq(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक virq)
अणु
	वापस per_cpu(virq_to_irq, cpu)[virq];
पूर्ण

अटल क्रमागत ipi_vector ipi_from_irq(अचिन्हित irq)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(irq);

	BUG_ON(info == शून्य);
	BUG_ON(info->type != IRQT_IPI);

	वापस info->u.ipi;
पूर्ण

अटल अचिन्हित virq_from_irq(अचिन्हित irq)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(irq);

	BUG_ON(info == शून्य);
	BUG_ON(info->type != IRQT_VIRQ);

	वापस info->u.virq;
पूर्ण

अटल अचिन्हित pirq_from_irq(अचिन्हित irq)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(irq);

	BUG_ON(info == शून्य);
	BUG_ON(info->type != IRQT_PIRQ);

	वापस info->u.pirq.pirq;
पूर्ण

अटल क्रमागत xen_irq_type type_from_irq(अचिन्हित irq)
अणु
	वापस info_क्रम_irq(irq)->type;
पूर्ण

अटल अचिन्हित cpu_from_irq(अचिन्हित irq)
अणु
	वापस info_क्रम_irq(irq)->cpu;
पूर्ण

अचिन्हित पूर्णांक cpu_from_evtchn(evtchn_port_t evtchn)
अणु
	पूर्णांक irq = get_evtchn_to_irq(evtchn);
	अचिन्हित ret = 0;

	अगर (irq != -1)
		ret = cpu_from_irq(irq);

	वापस ret;
पूर्ण

अटल व्योम करो_mask(काष्ठा irq_info *info, u8 reason)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&info->lock, flags);

	अगर (!info->mask_reason)
		mask_evtchn(info->evtchn);

	info->mask_reason |= reason;

	raw_spin_unlock_irqrestore(&info->lock, flags);
पूर्ण

अटल व्योम करो_unmask(काष्ठा irq_info *info, u8 reason)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&info->lock, flags);

	info->mask_reason &= ~reason;

	अगर (!info->mask_reason)
		unmask_evtchn(info->evtchn);

	raw_spin_unlock_irqrestore(&info->lock, flags);
पूर्ण

#अगर_घोषित CONFIG_X86
अटल bool pirq_check_eoi_map(अचिन्हित irq)
अणु
	वापस test_bit(pirq_from_irq(irq), pirq_eoi_map);
पूर्ण
#पूर्ण_अगर

अटल bool pirq_needs_eoi_flag(अचिन्हित irq)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(irq);
	BUG_ON(info->type != IRQT_PIRQ);

	वापस info->u.pirq.flags & PIRQ_NEEDS_EOI;
पूर्ण

अटल व्योम bind_evtchn_to_cpu(evtchn_port_t evtchn, अचिन्हित पूर्णांक cpu,
			       bool क्रमce_affinity)
अणु
	पूर्णांक irq = get_evtchn_to_irq(evtchn);
	काष्ठा irq_info *info = info_क्रम_irq(irq);

	BUG_ON(irq == -1);

	अगर (IS_ENABLED(CONFIG_SMP) && क्रमce_affinity) अणु
		cpumask_copy(irq_get_affinity_mask(irq), cpumask_of(cpu));
		cpumask_copy(irq_get_effective_affinity_mask(irq),
			     cpumask_of(cpu));
	पूर्ण

	xen_evtchn_port_bind_to_cpu(evtchn, cpu, info->cpu);

	channels_on_cpu_dec(info);
	info->cpu = cpu;
	channels_on_cpu_inc(info);
पूर्ण

/**
 * notअगरy_remote_via_irq - send event to remote end of event channel via irq
 * @irq: irq of event channel to send event to
 *
 * Unlike notअगरy_remote_via_evtchn(), this is safe to use across
 * save/restore. Notअगरications on a broken connection are silently
 * dropped.
 */
व्योम notअगरy_remote_via_irq(पूर्णांक irq)
अणु
	evtchn_port_t evtchn = evtchn_from_irq(irq);

	अगर (VALID_EVTCHN(evtchn))
		notअगरy_remote_via_evtchn(evtchn);
पूर्ण
EXPORT_SYMBOL_GPL(notअगरy_remote_via_irq);

काष्ठा lateeoi_work अणु
	काष्ठा delayed_work delayed;
	spinlock_t eoi_list_lock;
	काष्ठा list_head eoi_list;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा lateeoi_work, lateeoi);

अटल व्योम lateeoi_list_del(काष्ठा irq_info *info)
अणु
	काष्ठा lateeoi_work *eoi = &per_cpu(lateeoi, info->eoi_cpu);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&eoi->eoi_list_lock, flags);
	list_del_init(&info->eoi_list);
	spin_unlock_irqrestore(&eoi->eoi_list_lock, flags);
पूर्ण

अटल व्योम lateeoi_list_add(काष्ठा irq_info *info)
अणु
	काष्ठा lateeoi_work *eoi = &per_cpu(lateeoi, info->eoi_cpu);
	काष्ठा irq_info *elem;
	u64 now = get_jअगरfies_64();
	अचिन्हित दीर्घ delay;
	अचिन्हित दीर्घ flags;

	अगर (now < info->eoi_समय)
		delay = info->eoi_समय - now;
	अन्यथा
		delay = 1;

	spin_lock_irqsave(&eoi->eoi_list_lock, flags);

	अगर (list_empty(&eoi->eoi_list)) अणु
		list_add(&info->eoi_list, &eoi->eoi_list);
		mod_delayed_work_on(info->eoi_cpu, प्रणाली_wq,
				    &eoi->delayed, delay);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_reverse(elem, &eoi->eoi_list, eoi_list) अणु
			अगर (elem->eoi_समय <= info->eoi_समय)
				अवरोध;
		पूर्ण
		list_add(&info->eoi_list, &elem->eoi_list);
	पूर्ण

	spin_unlock_irqrestore(&eoi->eoi_list_lock, flags);
पूर्ण

अटल व्योम xen_irq_lateeoi_locked(काष्ठा irq_info *info, bool spurious)
अणु
	evtchn_port_t evtchn;
	अचिन्हित पूर्णांक cpu;
	अचिन्हित पूर्णांक delay = 0;

	evtchn = info->evtchn;
	अगर (!VALID_EVTCHN(evtchn) || !list_empty(&info->eoi_list))
		वापस;

	अगर (spurious) अणु
		काष्ठा xenbus_device *dev = info->u.पूर्णांकerकरोमुख्य;
		अचिन्हित पूर्णांक threshold = 1;

		अगर (dev && dev->spurious_threshold)
			threshold = dev->spurious_threshold;

		अगर ((1 << info->spurious_cnt) < (HZ << 2)) अणु
			अगर (info->spurious_cnt != 0xFF)
				info->spurious_cnt++;
		पूर्ण
		अगर (info->spurious_cnt > threshold) अणु
			delay = 1 << (info->spurious_cnt - 1 - threshold);
			अगर (delay > HZ)
				delay = HZ;
			अगर (!info->eoi_समय)
				info->eoi_cpu = smp_processor_id();
			info->eoi_समय = get_jअगरfies_64() + delay;
			अगर (dev)
				atomic_add(delay, &dev->jअगरfies_eoi_delayed);
		पूर्ण
		अगर (dev)
			atomic_inc(&dev->spurious_events);
	पूर्ण अन्यथा अणु
		info->spurious_cnt = 0;
	पूर्ण

	cpu = info->eoi_cpu;
	अगर (info->eoi_समय &&
	    (info->irq_epoch == per_cpu(irq_epoch, cpu) || delay)) अणु
		lateeoi_list_add(info);
		वापस;
	पूर्ण

	info->eoi_समय = 0;
	करो_unmask(info, EVT_MASK_REASON_EOI_PENDING);
पूर्ण

अटल व्योम xen_irq_lateeoi_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lateeoi_work *eoi;
	काष्ठा irq_info *info;
	u64 now = get_jअगरfies_64();
	अचिन्हित दीर्घ flags;

	eoi = container_of(to_delayed_work(work), काष्ठा lateeoi_work, delayed);

	पढ़ो_lock_irqsave(&evtchn_rwlock, flags);

	जबतक (true) अणु
		spin_lock(&eoi->eoi_list_lock);

		info = list_first_entry_or_null(&eoi->eoi_list, काष्ठा irq_info,
						eoi_list);

		अगर (info == शून्य || now < info->eoi_समय) अणु
			spin_unlock(&eoi->eoi_list_lock);
			अवरोध;
		पूर्ण

		list_del_init(&info->eoi_list);

		spin_unlock(&eoi->eoi_list_lock);

		info->eoi_समय = 0;

		xen_irq_lateeoi_locked(info, false);
	पूर्ण

	अगर (info)
		mod_delayed_work_on(info->eoi_cpu, प्रणाली_wq,
				    &eoi->delayed, info->eoi_समय - now);

	पढ़ो_unlock_irqrestore(&evtchn_rwlock, flags);
पूर्ण

अटल व्योम xen_cpu_init_eoi(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा lateeoi_work *eoi = &per_cpu(lateeoi, cpu);

	INIT_DELAYED_WORK(&eoi->delayed, xen_irq_lateeoi_worker);
	spin_lock_init(&eoi->eoi_list_lock);
	INIT_LIST_HEAD(&eoi->eoi_list);
पूर्ण

व्योम xen_irq_lateeoi(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक eoi_flags)
अणु
	काष्ठा irq_info *info;
	अचिन्हित दीर्घ flags;

	पढ़ो_lock_irqsave(&evtchn_rwlock, flags);

	info = info_क्रम_irq(irq);

	अगर (info)
		xen_irq_lateeoi_locked(info, eoi_flags & XEN_EOI_FLAG_SPURIOUS);

	पढ़ो_unlock_irqrestore(&evtchn_rwlock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(xen_irq_lateeoi);

अटल व्योम xen_irq_init(अचिन्हित irq)
अणु
	काष्ठा irq_info *info;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (info == शून्य)
		panic("Unable to allocate metadata for IRQ%d\n", irq);

	info->type = IRQT_UNBOUND;
	info->refcnt = -1;

	set_info_क्रम_irq(irq, info);
	/*
	 * Interrupt affinity setting can be immediate. No poपूर्णांक
	 * in delaying it until an पूर्णांकerrupt is handled.
	 */
	irq_set_status_flags(irq, IRQ_MOVE_PCNTXT);

	INIT_LIST_HEAD(&info->eoi_list);
	list_add_tail(&info->list, &xen_irq_list_head);
पूर्ण

अटल पूर्णांक __must_check xen_allocate_irqs_dynamic(पूर्णांक nvec)
अणु
	पूर्णांक i, irq = irq_alloc_descs(-1, 0, nvec, -1);

	अगर (irq >= 0) अणु
		क्रम (i = 0; i < nvec; i++)
			xen_irq_init(irq + i);
	पूर्ण

	वापस irq;
पूर्ण

अटल अंतरभूत पूर्णांक __must_check xen_allocate_irq_dynamic(व्योम)
अणु

	वापस xen_allocate_irqs_dynamic(1);
पूर्ण

अटल पूर्णांक __must_check xen_allocate_irq_gsi(अचिन्हित gsi)
अणु
	पूर्णांक irq;

	/*
	 * A PV guest has no concept of a GSI (since it has no ACPI
	 * nor access to/knowledge of the physical APICs). Thereक्रमe
	 * all IRQs are dynamically allocated from the entire IRQ
	 * space.
	 */
	अगर (xen_pv_करोमुख्य() && !xen_initial_करोमुख्य())
		वापस xen_allocate_irq_dynamic();

	/* Legacy IRQ descriptors are alपढ़ोy allocated by the arch. */
	अगर (gsi < nr_legacy_irqs())
		irq = gsi;
	अन्यथा
		irq = irq_alloc_desc_at(gsi, -1);

	xen_irq_init(irq);

	वापस irq;
पूर्ण

अटल व्योम xen_मुक्त_irq(अचिन्हित irq)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(irq);
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(!info))
		वापस;

	ग_लिखो_lock_irqsave(&evtchn_rwlock, flags);

	अगर (!list_empty(&info->eoi_list))
		lateeoi_list_del(info);

	list_del(&info->list);

	set_info_क्रम_irq(irq, शून्य);

	WARN_ON(info->refcnt > 0);

	ग_लिखो_unlock_irqrestore(&evtchn_rwlock, flags);

	kमुक्त(info);

	/* Legacy IRQ descriptors are managed by the arch. */
	अगर (irq < nr_legacy_irqs())
		वापस;

	irq_मुक्त_desc(irq);
पूर्ण

अटल व्योम xen_evtchn_बंद(evtchn_port_t port)
अणु
	काष्ठा evtchn_बंद बंद;

	बंद.port = port;
	अगर (HYPERVISOR_event_channel_op(EVTCHNOP_बंद, &बंद) != 0)
		BUG();
पूर्ण

अटल व्योम event_handler_निकास(काष्ठा irq_info *info)
अणु
	smp_store_release(&info->is_active, 0);
	clear_evtchn(info->evtchn);
पूर्ण

अटल व्योम pirq_query_unmask(पूर्णांक irq)
अणु
	काष्ठा physdev_irq_status_query irq_status;
	काष्ठा irq_info *info = info_क्रम_irq(irq);

	BUG_ON(info->type != IRQT_PIRQ);

	irq_status.irq = pirq_from_irq(irq);
	अगर (HYPERVISOR_physdev_op(PHYSDEVOP_irq_status_query, &irq_status))
		irq_status.flags = 0;

	info->u.pirq.flags &= ~PIRQ_NEEDS_EOI;
	अगर (irq_status.flags & XENIRQSTAT_needs_eoi)
		info->u.pirq.flags |= PIRQ_NEEDS_EOI;
पूर्ण

अटल व्योम eoi_pirq(काष्ठा irq_data *data)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(data->irq);
	evtchn_port_t evtchn = info ? info->evtchn : 0;
	काष्ठा physdev_eoi eoi = अणु .irq = pirq_from_irq(data->irq) पूर्ण;
	पूर्णांक rc = 0;

	अगर (!VALID_EVTCHN(evtchn))
		वापस;

	event_handler_निकास(info);

	अगर (pirq_needs_eoi(data->irq)) अणु
		rc = HYPERVISOR_physdev_op(PHYSDEVOP_eoi, &eoi);
		WARN_ON(rc);
	पूर्ण
पूर्ण

अटल व्योम mask_ack_pirq(काष्ठा irq_data *data)
अणु
	disable_dynirq(data);
	eoi_pirq(data);
पूर्ण

अटल अचिन्हित पूर्णांक __startup_pirq(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा evtchn_bind_pirq bind_pirq;
	काष्ठा irq_info *info = info_क्रम_irq(irq);
	evtchn_port_t evtchn = evtchn_from_irq(irq);
	पूर्णांक rc;

	BUG_ON(info->type != IRQT_PIRQ);

	अगर (VALID_EVTCHN(evtchn))
		जाओ out;

	bind_pirq.pirq = pirq_from_irq(irq);
	/* NB. We are happy to share unless we are probing. */
	bind_pirq.flags = info->u.pirq.flags & PIRQ_SHAREABLE ?
					BIND_PIRQ__WILL_SHARE : 0;
	rc = HYPERVISOR_event_channel_op(EVTCHNOP_bind_pirq, &bind_pirq);
	अगर (rc != 0) अणु
		pr_warn("Failed to obtain physical IRQ %d\n", irq);
		वापस 0;
	पूर्ण
	evtchn = bind_pirq.port;

	pirq_query_unmask(irq);

	rc = set_evtchn_to_irq(evtchn, irq);
	अगर (rc)
		जाओ err;

	info->evtchn = evtchn;
	bind_evtchn_to_cpu(evtchn, 0, false);

	rc = xen_evtchn_port_setup(evtchn);
	अगर (rc)
		जाओ err;

out:
	करो_unmask(info, EVT_MASK_REASON_EXPLICIT);

	eoi_pirq(irq_get_irq_data(irq));

	वापस 0;

err:
	pr_err("irq%d: Failed to set port to irq mapping (%d)\n", irq, rc);
	xen_evtchn_बंद(evtchn);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक startup_pirq(काष्ठा irq_data *data)
अणु
	वापस __startup_pirq(data->irq);
पूर्ण

अटल व्योम shutकरोwn_pirq(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	काष्ठा irq_info *info = info_क्रम_irq(irq);
	evtchn_port_t evtchn = evtchn_from_irq(irq);

	BUG_ON(info->type != IRQT_PIRQ);

	अगर (!VALID_EVTCHN(evtchn))
		वापस;

	करो_mask(info, EVT_MASK_REASON_EXPLICIT);
	xen_evtchn_बंद(evtchn);
	xen_irq_info_cleanup(info);
पूर्ण

अटल व्योम enable_pirq(काष्ठा irq_data *data)
अणु
	enable_dynirq(data);
पूर्ण

अटल व्योम disable_pirq(काष्ठा irq_data *data)
अणु
	disable_dynirq(data);
पूर्ण

पूर्णांक xen_irq_from_gsi(अचिन्हित gsi)
अणु
	काष्ठा irq_info *info;

	list_क्रम_each_entry(info, &xen_irq_list_head, list) अणु
		अगर (info->type != IRQT_PIRQ)
			जारी;

		अगर (info->u.pirq.gsi == gsi)
			वापस info->irq;
	पूर्ण

	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(xen_irq_from_gsi);

अटल व्योम __unbind_from_irq(अचिन्हित पूर्णांक irq)
अणु
	evtchn_port_t evtchn = evtchn_from_irq(irq);
	काष्ठा irq_info *info = info_क्रम_irq(irq);

	अगर (info->refcnt > 0) अणु
		info->refcnt--;
		अगर (info->refcnt != 0)
			वापस;
	पूर्ण

	अगर (VALID_EVTCHN(evtchn)) अणु
		अचिन्हित पूर्णांक cpu = cpu_from_irq(irq);
		काष्ठा xenbus_device *dev;

		xen_evtchn_बंद(evtchn);

		चयन (type_from_irq(irq)) अणु
		हाल IRQT_VIRQ:
			per_cpu(virq_to_irq, cpu)[virq_from_irq(irq)] = -1;
			अवरोध;
		हाल IRQT_IPI:
			per_cpu(ipi_to_irq, cpu)[ipi_from_irq(irq)] = -1;
			अवरोध;
		हाल IRQT_EVTCHN:
			dev = info->u.पूर्णांकerकरोमुख्य;
			अगर (dev)
				atomic_dec(&dev->event_channels);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		xen_irq_info_cleanup(info);
	पूर्ण

	xen_मुक्त_irq(irq);
पूर्ण

/*
 * Do not make any assumptions regarding the relationship between the
 * IRQ number वापसed here and the Xen pirq argument.
 *
 * Note: We करोn't assign an event channel until the irq actually started
 * up.  Return an existing irq अगर we've alपढ़ोy got one क्रम the gsi.
 *
 * Shareable implies level triggered, not shareable implies edge
 * triggered here.
 */
पूर्णांक xen_bind_pirq_gsi_to_irq(अचिन्हित gsi,
			     अचिन्हित pirq, पूर्णांक shareable, अक्षर *name)
अणु
	पूर्णांक irq = -1;
	काष्ठा physdev_irq irq_op;
	पूर्णांक ret;

	mutex_lock(&irq_mapping_update_lock);

	irq = xen_irq_from_gsi(gsi);
	अगर (irq != -1) अणु
		pr_info("%s: returning irq %d for gsi %u\n",
			__func__, irq, gsi);
		जाओ out;
	पूर्ण

	irq = xen_allocate_irq_gsi(gsi);
	अगर (irq < 0)
		जाओ out;

	irq_op.irq = irq;
	irq_op.vector = 0;

	/* Only the privileged करोमुख्य can करो this. For non-priv, the pcअगरront
	 * driver provides a PCI bus that करोes the call to करो exactly
	 * this in the priv करोमुख्य. */
	अगर (xen_initial_करोमुख्य() &&
	    HYPERVISOR_physdev_op(PHYSDEVOP_alloc_irq_vector, &irq_op)) अणु
		xen_मुक्त_irq(irq);
		irq = -ENOSPC;
		जाओ out;
	पूर्ण

	ret = xen_irq_info_pirq_setup(irq, 0, pirq, gsi, DOMID_SELF,
			       shareable ? PIRQ_SHAREABLE : 0);
	अगर (ret < 0) अणु
		__unbind_from_irq(irq);
		irq = ret;
		जाओ out;
	पूर्ण

	pirq_query_unmask(irq);
	/* We try to use the handler with the appropriate semantic क्रम the
	 * type of पूर्णांकerrupt: अगर the पूर्णांकerrupt is an edge triggered
	 * पूर्णांकerrupt we use handle_edge_irq.
	 *
	 * On the other hand अगर the पूर्णांकerrupt is level triggered we use
	 * handle_fasteoi_irq like the native code करोes क्रम this kind of
	 * पूर्णांकerrupts.
	 *
	 * Depending on the Xen version, pirq_needs_eoi might वापस true
	 * not only क्रम level triggered पूर्णांकerrupts but क्रम edge triggered
	 * पूर्णांकerrupts too. In any हाल Xen always honors the eoi mechanism,
	 * not injecting any more pirqs of the same kind अगर the first one
	 * hasn't received an eoi yet. Thereक्रमe using the fasteoi handler
	 * is the right choice either way.
	 */
	अगर (shareable)
		irq_set_chip_and_handler_name(irq, &xen_pirq_chip,
				handle_fasteoi_irq, name);
	अन्यथा
		irq_set_chip_and_handler_name(irq, &xen_pirq_chip,
				handle_edge_irq, name);

out:
	mutex_unlock(&irq_mapping_update_lock);

	वापस irq;
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
पूर्णांक xen_allocate_pirq_msi(काष्ठा pci_dev *dev, काष्ठा msi_desc *msidesc)
अणु
	पूर्णांक rc;
	काष्ठा physdev_get_मुक्त_pirq op_get_मुक्त_pirq;

	op_get_मुक्त_pirq.type = MAP_PIRQ_TYPE_MSI;
	rc = HYPERVISOR_physdev_op(PHYSDEVOP_get_मुक्त_pirq, &op_get_मुक्त_pirq);

	WARN_ONCE(rc == -ENOSYS,
		  "hypervisor does not support the PHYSDEVOP_get_free_pirq interface\n");

	वापस rc ? -1 : op_get_मुक्त_pirq.pirq;
पूर्ण

पूर्णांक xen_bind_pirq_msi_to_irq(काष्ठा pci_dev *dev, काष्ठा msi_desc *msidesc,
			     पूर्णांक pirq, पूर्णांक nvec, स्थिर अक्षर *name, करोmid_t करोmid)
अणु
	पूर्णांक i, irq, ret;

	mutex_lock(&irq_mapping_update_lock);

	irq = xen_allocate_irqs_dynamic(nvec);
	अगर (irq < 0)
		जाओ out;

	क्रम (i = 0; i < nvec; i++) अणु
		irq_set_chip_and_handler_name(irq + i, &xen_pirq_chip, handle_edge_irq, name);

		ret = xen_irq_info_pirq_setup(irq + i, 0, pirq + i, 0, करोmid,
					      i == 0 ? 0 : PIRQ_MSI_GROUP);
		अगर (ret < 0)
			जाओ error_irq;
	पूर्ण

	ret = irq_set_msi_desc(irq, msidesc);
	अगर (ret < 0)
		जाओ error_irq;
out:
	mutex_unlock(&irq_mapping_update_lock);
	वापस irq;
error_irq:
	जबतक (nvec--)
		__unbind_from_irq(irq + nvec);
	mutex_unlock(&irq_mapping_update_lock);
	वापस ret;
पूर्ण
#पूर्ण_अगर

पूर्णांक xen_destroy_irq(पूर्णांक irq)
अणु
	काष्ठा physdev_unmap_pirq unmap_irq;
	काष्ठा irq_info *info = info_क्रम_irq(irq);
	पूर्णांक rc = -ENOENT;

	mutex_lock(&irq_mapping_update_lock);

	/*
	 * If trying to हटाओ a vector in a MSI group dअगरferent
	 * than the first one skip the PIRQ unmap unless this vector
	 * is the first one in the group.
	 */
	अगर (xen_initial_करोमुख्य() && !(info->u.pirq.flags & PIRQ_MSI_GROUP)) अणु
		unmap_irq.pirq = info->u.pirq.pirq;
		unmap_irq.करोmid = info->u.pirq.करोmid;
		rc = HYPERVISOR_physdev_op(PHYSDEVOP_unmap_pirq, &unmap_irq);
		/* If another करोमुख्य quits without making the pci_disable_msix
		 * call, the Xen hypervisor takes care of मुक्तing the PIRQs
		 * (मुक्त_करोमुख्य_pirqs).
		 */
		अगर ((rc == -ESRCH && info->u.pirq.करोmid != DOMID_SELF))
			pr_info("domain %d does not have %d anymore\n",
				info->u.pirq.करोmid, info->u.pirq.pirq);
		अन्यथा अगर (rc) अणु
			pr_warn("unmap irq failed %d\n", rc);
			जाओ out;
		पूर्ण
	पूर्ण

	xen_मुक्त_irq(irq);

out:
	mutex_unlock(&irq_mapping_update_lock);
	वापस rc;
पूर्ण

पूर्णांक xen_irq_from_pirq(अचिन्हित pirq)
अणु
	पूर्णांक irq;

	काष्ठा irq_info *info;

	mutex_lock(&irq_mapping_update_lock);

	list_क्रम_each_entry(info, &xen_irq_list_head, list) अणु
		अगर (info->type != IRQT_PIRQ)
			जारी;
		irq = info->irq;
		अगर (info->u.pirq.pirq == pirq)
			जाओ out;
	पूर्ण
	irq = -1;
out:
	mutex_unlock(&irq_mapping_update_lock);

	वापस irq;
पूर्ण


पूर्णांक xen_pirq_from_irq(अचिन्हित irq)
अणु
	वापस pirq_from_irq(irq);
पूर्ण
EXPORT_SYMBOL_GPL(xen_pirq_from_irq);

अटल पूर्णांक bind_evtchn_to_irq_chip(evtchn_port_t evtchn, काष्ठा irq_chip *chip,
				   काष्ठा xenbus_device *dev)
अणु
	पूर्णांक irq;
	पूर्णांक ret;

	अगर (evtchn >= xen_evtchn_max_channels())
		वापस -ENOMEM;

	mutex_lock(&irq_mapping_update_lock);

	irq = get_evtchn_to_irq(evtchn);

	अगर (irq == -1) अणु
		irq = xen_allocate_irq_dynamic();
		अगर (irq < 0)
			जाओ out;

		irq_set_chip_and_handler_name(irq, chip,
					      handle_edge_irq, "event");

		ret = xen_irq_info_evtchn_setup(irq, evtchn, dev);
		अगर (ret < 0) अणु
			__unbind_from_irq(irq);
			irq = ret;
			जाओ out;
		पूर्ण
		/*
		 * New पूर्णांकerकरोमुख्य events are initially bound to vCPU0 This
		 * is required to setup the event channel in the first
		 * place and also important क्रम UP guests because the
		 * affinity setting is not invoked on them so nothing would
		 * bind the channel.
		 */
		bind_evtchn_to_cpu(evtchn, 0, false);
	पूर्ण अन्यथा अणु
		काष्ठा irq_info *info = info_क्रम_irq(irq);
		WARN_ON(info == शून्य || info->type != IRQT_EVTCHN);
	पूर्ण

out:
	mutex_unlock(&irq_mapping_update_lock);

	वापस irq;
पूर्ण

पूर्णांक bind_evtchn_to_irq(evtchn_port_t evtchn)
अणु
	वापस bind_evtchn_to_irq_chip(evtchn, &xen_dynamic_chip, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(bind_evtchn_to_irq);

अटल पूर्णांक bind_ipi_to_irq(अचिन्हित पूर्णांक ipi, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा evtchn_bind_ipi bind_ipi;
	evtchn_port_t evtchn;
	पूर्णांक ret, irq;

	mutex_lock(&irq_mapping_update_lock);

	irq = per_cpu(ipi_to_irq, cpu)[ipi];

	अगर (irq == -1) अणु
		irq = xen_allocate_irq_dynamic();
		अगर (irq < 0)
			जाओ out;

		irq_set_chip_and_handler_name(irq, &xen_percpu_chip,
					      handle_percpu_irq, "ipi");

		bind_ipi.vcpu = xen_vcpu_nr(cpu);
		अगर (HYPERVISOR_event_channel_op(EVTCHNOP_bind_ipi,
						&bind_ipi) != 0)
			BUG();
		evtchn = bind_ipi.port;

		ret = xen_irq_info_ipi_setup(cpu, irq, evtchn, ipi);
		अगर (ret < 0) अणु
			__unbind_from_irq(irq);
			irq = ret;
			जाओ out;
		पूर्ण
		/*
		 * Force the affinity mask to the target CPU so proc shows
		 * the correct target.
		 */
		bind_evtchn_to_cpu(evtchn, cpu, true);
	पूर्ण अन्यथा अणु
		काष्ठा irq_info *info = info_क्रम_irq(irq);
		WARN_ON(info == शून्य || info->type != IRQT_IPI);
	पूर्ण

 out:
	mutex_unlock(&irq_mapping_update_lock);
	वापस irq;
पूर्ण

अटल पूर्णांक bind_पूर्णांकerकरोमुख्य_evtchn_to_irq_chip(काष्ठा xenbus_device *dev,
					       evtchn_port_t remote_port,
					       काष्ठा irq_chip *chip)
अणु
	काष्ठा evtchn_bind_पूर्णांकerकरोमुख्य bind_पूर्णांकerकरोमुख्य;
	पूर्णांक err;

	bind_पूर्णांकerकरोमुख्य.remote_करोm  = dev->otherend_id;
	bind_पूर्णांकerकरोमुख्य.remote_port = remote_port;

	err = HYPERVISOR_event_channel_op(EVTCHNOP_bind_पूर्णांकerकरोमुख्य,
					  &bind_पूर्णांकerकरोमुख्य);

	वापस err ? : bind_evtchn_to_irq_chip(bind_पूर्णांकerकरोमुख्य.local_port,
					       chip, dev);
पूर्ण

पूर्णांक bind_पूर्णांकerकरोमुख्य_evtchn_to_irq_lateeoi(काष्ठा xenbus_device *dev,
					   evtchn_port_t remote_port)
अणु
	वापस bind_पूर्णांकerकरोमुख्य_evtchn_to_irq_chip(dev, remote_port,
						   &xen_lateeoi_chip);
पूर्ण
EXPORT_SYMBOL_GPL(bind_पूर्णांकerकरोमुख्य_evtchn_to_irq_lateeoi);

अटल पूर्णांक find_virq(अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक cpu, evtchn_port_t *evtchn)
अणु
	काष्ठा evtchn_status status;
	evtchn_port_t port;
	पूर्णांक rc = -ENOENT;

	स_रखो(&status, 0, माप(status));
	क्रम (port = 0; port < xen_evtchn_max_channels(); port++) अणु
		status.करोm = DOMID_SELF;
		status.port = port;
		rc = HYPERVISOR_event_channel_op(EVTCHNOP_status, &status);
		अगर (rc < 0)
			जारी;
		अगर (status.status != EVTCHNSTAT_virq)
			जारी;
		अगर (status.u.virq == virq && status.vcpu == xen_vcpu_nr(cpu)) अणु
			*evtchn = port;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

/**
 * xen_evtchn_nr_channels - number of usable event channel ports
 *
 * This may be less than the maximum supported by the current
 * hypervisor ABI. Use xen_evtchn_max_channels() क्रम the maximum
 * supported.
 */
अचिन्हित xen_evtchn_nr_channels(व्योम)
अणु
        वापस evtchn_ops->nr_channels();
पूर्ण
EXPORT_SYMBOL_GPL(xen_evtchn_nr_channels);

पूर्णांक bind_virq_to_irq(अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक cpu, bool percpu)
अणु
	काष्ठा evtchn_bind_virq bind_virq;
	evtchn_port_t evtchn = 0;
	पूर्णांक irq, ret;

	mutex_lock(&irq_mapping_update_lock);

	irq = per_cpu(virq_to_irq, cpu)[virq];

	अगर (irq == -1) अणु
		irq = xen_allocate_irq_dynamic();
		अगर (irq < 0)
			जाओ out;

		अगर (percpu)
			irq_set_chip_and_handler_name(irq, &xen_percpu_chip,
						      handle_percpu_irq, "virq");
		अन्यथा
			irq_set_chip_and_handler_name(irq, &xen_dynamic_chip,
						      handle_edge_irq, "virq");

		bind_virq.virq = virq;
		bind_virq.vcpu = xen_vcpu_nr(cpu);
		ret = HYPERVISOR_event_channel_op(EVTCHNOP_bind_virq,
						&bind_virq);
		अगर (ret == 0)
			evtchn = bind_virq.port;
		अन्यथा अणु
			अगर (ret == -EEXIST)
				ret = find_virq(virq, cpu, &evtchn);
			BUG_ON(ret < 0);
		पूर्ण

		ret = xen_irq_info_virq_setup(cpu, irq, evtchn, virq);
		अगर (ret < 0) अणु
			__unbind_from_irq(irq);
			irq = ret;
			जाओ out;
		पूर्ण

		/*
		 * Force the affinity mask क्रम percpu पूर्णांकerrupts so proc
		 * shows the correct target.
		 */
		bind_evtchn_to_cpu(evtchn, cpu, percpu);
	पूर्ण अन्यथा अणु
		काष्ठा irq_info *info = info_क्रम_irq(irq);
		WARN_ON(info == शून्य || info->type != IRQT_VIRQ);
	पूर्ण

out:
	mutex_unlock(&irq_mapping_update_lock);

	वापस irq;
पूर्ण

अटल व्योम unbind_from_irq(अचिन्हित पूर्णांक irq)
अणु
	mutex_lock(&irq_mapping_update_lock);
	__unbind_from_irq(irq);
	mutex_unlock(&irq_mapping_update_lock);
पूर्ण

अटल पूर्णांक bind_evtchn_to_irqhandler_chip(evtchn_port_t evtchn,
					  irq_handler_t handler,
					  अचिन्हित दीर्घ irqflags,
					  स्थिर अक्षर *devname, व्योम *dev_id,
					  काष्ठा irq_chip *chip)
अणु
	पूर्णांक irq, retval;

	irq = bind_evtchn_to_irq_chip(evtchn, chip, शून्य);
	अगर (irq < 0)
		वापस irq;
	retval = request_irq(irq, handler, irqflags, devname, dev_id);
	अगर (retval != 0) अणु
		unbind_from_irq(irq);
		वापस retval;
	पूर्ण

	वापस irq;
पूर्ण

पूर्णांक bind_evtchn_to_irqhandler(evtchn_port_t evtchn,
			      irq_handler_t handler,
			      अचिन्हित दीर्घ irqflags,
			      स्थिर अक्षर *devname, व्योम *dev_id)
अणु
	वापस bind_evtchn_to_irqhandler_chip(evtchn, handler, irqflags,
					      devname, dev_id,
					      &xen_dynamic_chip);
पूर्ण
EXPORT_SYMBOL_GPL(bind_evtchn_to_irqhandler);

पूर्णांक bind_evtchn_to_irqhandler_lateeoi(evtchn_port_t evtchn,
				      irq_handler_t handler,
				      अचिन्हित दीर्घ irqflags,
				      स्थिर अक्षर *devname, व्योम *dev_id)
अणु
	वापस bind_evtchn_to_irqhandler_chip(evtchn, handler, irqflags,
					      devname, dev_id,
					      &xen_lateeoi_chip);
पूर्ण
EXPORT_SYMBOL_GPL(bind_evtchn_to_irqhandler_lateeoi);

अटल पूर्णांक bind_पूर्णांकerकरोमुख्य_evtchn_to_irqhandler_chip(
		काष्ठा xenbus_device *dev, evtchn_port_t remote_port,
		irq_handler_t handler, अचिन्हित दीर्घ irqflags,
		स्थिर अक्षर *devname, व्योम *dev_id, काष्ठा irq_chip *chip)
अणु
	पूर्णांक irq, retval;

	irq = bind_पूर्णांकerकरोमुख्य_evtchn_to_irq_chip(dev, remote_port, chip);
	अगर (irq < 0)
		वापस irq;

	retval = request_irq(irq, handler, irqflags, devname, dev_id);
	अगर (retval != 0) अणु
		unbind_from_irq(irq);
		वापस retval;
	पूर्ण

	वापस irq;
पूर्ण

पूर्णांक bind_पूर्णांकerकरोमुख्य_evtchn_to_irqhandler_lateeoi(काष्ठा xenbus_device *dev,
						  evtchn_port_t remote_port,
						  irq_handler_t handler,
						  अचिन्हित दीर्घ irqflags,
						  स्थिर अक्षर *devname,
						  व्योम *dev_id)
अणु
	वापस bind_पूर्णांकerकरोमुख्य_evtchn_to_irqhandler_chip(dev,
				remote_port, handler, irqflags, devname,
				dev_id, &xen_lateeoi_chip);
पूर्ण
EXPORT_SYMBOL_GPL(bind_पूर्णांकerकरोमुख्य_evtchn_to_irqhandler_lateeoi);

पूर्णांक bind_virq_to_irqhandler(अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक cpu,
			    irq_handler_t handler,
			    अचिन्हित दीर्घ irqflags, स्थिर अक्षर *devname, व्योम *dev_id)
अणु
	पूर्णांक irq, retval;

	irq = bind_virq_to_irq(virq, cpu, irqflags & IRQF_PERCPU);
	अगर (irq < 0)
		वापस irq;
	retval = request_irq(irq, handler, irqflags, devname, dev_id);
	अगर (retval != 0) अणु
		unbind_from_irq(irq);
		वापस retval;
	पूर्ण

	वापस irq;
पूर्ण
EXPORT_SYMBOL_GPL(bind_virq_to_irqhandler);

पूर्णांक bind_ipi_to_irqhandler(क्रमागत ipi_vector ipi,
			   अचिन्हित पूर्णांक cpu,
			   irq_handler_t handler,
			   अचिन्हित दीर्घ irqflags,
			   स्थिर अक्षर *devname,
			   व्योम *dev_id)
अणु
	पूर्णांक irq, retval;

	irq = bind_ipi_to_irq(ipi, cpu);
	अगर (irq < 0)
		वापस irq;

	irqflags |= IRQF_NO_SUSPEND | IRQF_FORCE_RESUME | IRQF_EARLY_RESUME;
	retval = request_irq(irq, handler, irqflags, devname, dev_id);
	अगर (retval != 0) अणु
		unbind_from_irq(irq);
		वापस retval;
	पूर्ण

	वापस irq;
पूर्ण

व्योम unbind_from_irqhandler(अचिन्हित पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(irq);

	अगर (WARN_ON(!info))
		वापस;
	मुक्त_irq(irq, dev_id);
	unbind_from_irq(irq);
पूर्ण
EXPORT_SYMBOL_GPL(unbind_from_irqhandler);

/**
 * xen_set_irq_priority() - set an event channel priority.
 * @irq:irq bound to an event channel.
 * @priority: priority between XEN_IRQ_PRIORITY_MAX and XEN_IRQ_PRIORITY_MIN.
 */
पूर्णांक xen_set_irq_priority(अचिन्हित irq, अचिन्हित priority)
अणु
	काष्ठा evtchn_set_priority set_priority;

	set_priority.port = evtchn_from_irq(irq);
	set_priority.priority = priority;

	वापस HYPERVISOR_event_channel_op(EVTCHNOP_set_priority,
					   &set_priority);
पूर्ण
EXPORT_SYMBOL_GPL(xen_set_irq_priority);

पूर्णांक evtchn_make_refcounted(evtchn_port_t evtchn)
अणु
	पूर्णांक irq = get_evtchn_to_irq(evtchn);
	काष्ठा irq_info *info;

	अगर (irq == -1)
		वापस -ENOENT;

	info = info_क्रम_irq(irq);

	अगर (!info)
		वापस -ENOENT;

	WARN_ON(info->refcnt != -1);

	info->refcnt = 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(evtchn_make_refcounted);

पूर्णांक evtchn_get(evtchn_port_t evtchn)
अणु
	पूर्णांक irq;
	काष्ठा irq_info *info;
	पूर्णांक err = -ENOENT;

	अगर (evtchn >= xen_evtchn_max_channels())
		वापस -EINVAL;

	mutex_lock(&irq_mapping_update_lock);

	irq = get_evtchn_to_irq(evtchn);
	अगर (irq == -1)
		जाओ करोne;

	info = info_क्रम_irq(irq);

	अगर (!info)
		जाओ करोne;

	err = -EINVAL;
	अगर (info->refcnt <= 0 || info->refcnt == लघु_उच्च)
		जाओ करोne;

	info->refcnt++;
	err = 0;
 करोne:
	mutex_unlock(&irq_mapping_update_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(evtchn_get);

व्योम evtchn_put(evtchn_port_t evtchn)
अणु
	पूर्णांक irq = get_evtchn_to_irq(evtchn);
	अगर (WARN_ON(irq == -1))
		वापस;
	unbind_from_irq(irq);
पूर्ण
EXPORT_SYMBOL_GPL(evtchn_put);

व्योम xen_send_IPI_one(अचिन्हित पूर्णांक cpu, क्रमागत ipi_vector vector)
अणु
	पूर्णांक irq;

#अगर_घोषित CONFIG_X86
	अगर (unlikely(vector == XEN_NMI_VECTOR)) अणु
		पूर्णांक rc =  HYPERVISOR_vcpu_op(VCPUOP_send_nmi, xen_vcpu_nr(cpu),
					     शून्य);
		अगर (rc < 0)
			prपूर्णांकk(KERN_WARNING "Sending nmi to CPU%d failed (rc:%d)\n", cpu, rc);
		वापस;
	पूर्ण
#पूर्ण_अगर
	irq = per_cpu(ipi_to_irq, cpu)[vector];
	BUG_ON(irq < 0);
	notअगरy_remote_via_irq(irq);
पूर्ण

काष्ठा evtchn_loop_ctrl अणु
	kसमय_प्रकार समयout;
	अचिन्हित count;
	bool defer_eoi;
पूर्ण;

व्योम handle_irq_क्रम_port(evtchn_port_t port, काष्ठा evtchn_loop_ctrl *ctrl)
अणु
	पूर्णांक irq;
	काष्ठा irq_info *info;
	काष्ठा xenbus_device *dev;

	irq = get_evtchn_to_irq(port);
	अगर (irq == -1)
		वापस;

	/*
	 * Check क्रम समयout every 256 events.
	 * We are setting the समयout value only after the first 256
	 * events in order to not hurt the common हाल of few loop
	 * iterations. The 256 is basically an arbitrary value.
	 *
	 * In हाल we are hitting the समयout we need to defer all further
	 * EOIs in order to ensure to leave the event handling loop rather
	 * sooner than later.
	 */
	अगर (!ctrl->defer_eoi && !(++ctrl->count & 0xff)) अणु
		kसमय_प्रकार kt = kसमय_get();

		अगर (!ctrl->समयout) अणु
			kt = kसमय_add_ms(kt,
					  jअगरfies_to_msecs(event_loop_समयout));
			ctrl->समयout = kt;
		पूर्ण अन्यथा अगर (kt > ctrl->समयout) अणु
			ctrl->defer_eoi = true;
		पूर्ण
	पूर्ण

	info = info_क्रम_irq(irq);
	अगर (xchg_acquire(&info->is_active, 1))
		वापस;

	dev = (info->type == IRQT_EVTCHN) ? info->u.पूर्णांकerकरोमुख्य : शून्य;
	अगर (dev)
		atomic_inc(&dev->events);

	अगर (ctrl->defer_eoi) अणु
		info->eoi_cpu = smp_processor_id();
		info->irq_epoch = __this_cpu_पढ़ो(irq_epoch);
		info->eoi_समय = get_jअगरfies_64() + event_eoi_delay;
	पूर्ण

	generic_handle_irq(irq);
पूर्ण

अटल व्योम __xen_evtchn_करो_upcall(व्योम)
अणु
	काष्ठा vcpu_info *vcpu_info = __this_cpu_पढ़ो(xen_vcpu);
	पूर्णांक cpu = smp_processor_id();
	काष्ठा evtchn_loop_ctrl ctrl = अणु 0 पूर्ण;

	पढ़ो_lock(&evtchn_rwlock);

	करो अणु
		vcpu_info->evtchn_upcall_pending = 0;

		xen_evtchn_handle_events(cpu, &ctrl);

		BUG_ON(!irqs_disabled());

		virt_rmb(); /* Hypervisor can set upcall pending. */

	पूर्ण जबतक (vcpu_info->evtchn_upcall_pending);

	पढ़ो_unlock(&evtchn_rwlock);

	/*
	 * Increment irq_epoch only now to defer EOIs only क्रम
	 * xen_irq_lateeoi() invocations occurring from inside the loop
	 * above.
	 */
	__this_cpu_inc(irq_epoch);
पूर्ण

व्योम xen_evtchn_करो_upcall(काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);

	irq_enter();

	__xen_evtchn_करो_upcall();

	irq_निकास();
	set_irq_regs(old_regs);
पूर्ण

व्योम xen_hvm_evtchn_करो_upcall(व्योम)
अणु
	__xen_evtchn_करो_upcall();
पूर्ण
EXPORT_SYMBOL_GPL(xen_hvm_evtchn_करो_upcall);

/* Rebind a new event channel to an existing irq. */
व्योम rebind_evtchn_irq(evtchn_port_t evtchn, पूर्णांक irq)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(irq);

	अगर (WARN_ON(!info))
		वापस;

	/* Make sure the irq is masked, since the new event channel
	   will also be masked. */
	disable_irq(irq);

	mutex_lock(&irq_mapping_update_lock);

	/* After resume the irq<->evtchn mappings are all cleared out */
	BUG_ON(get_evtchn_to_irq(evtchn) != -1);
	/* Expect irq to have been bound beक्रमe,
	   so there should be a proper type */
	BUG_ON(info->type == IRQT_UNBOUND);

	(व्योम)xen_irq_info_evtchn_setup(irq, evtchn, शून्य);

	mutex_unlock(&irq_mapping_update_lock);

	bind_evtchn_to_cpu(evtchn, info->cpu, false);

	/* Unmask the event channel. */
	enable_irq(irq);
पूर्ण

/* Rebind an evtchn so that it माला_लो delivered to a specअगरic cpu */
अटल पूर्णांक xen_rebind_evtchn_to_cpu(काष्ठा irq_info *info, अचिन्हित पूर्णांक tcpu)
अणु
	काष्ठा evtchn_bind_vcpu bind_vcpu;
	evtchn_port_t evtchn = info ? info->evtchn : 0;

	अगर (!VALID_EVTCHN(evtchn))
		वापस -1;

	अगर (!xen_support_evtchn_rebind())
		वापस -1;

	/* Send future instances of this पूर्णांकerrupt to other vcpu. */
	bind_vcpu.port = evtchn;
	bind_vcpu.vcpu = xen_vcpu_nr(tcpu);

	/*
	 * Mask the event जबतक changing the VCPU binding to prevent
	 * it being delivered on an unexpected VCPU.
	 */
	करो_mask(info, EVT_MASK_REASON_TEMPORARY);

	/*
	 * If this fails, it usually just indicates that we're dealing with a
	 * virq or IPI channel, which करोn't actually need to be rebound. Ignore
	 * it, but करोn't करो the xenlinux-level rebind in that हाल.
	 */
	अगर (HYPERVISOR_event_channel_op(EVTCHNOP_bind_vcpu, &bind_vcpu) >= 0)
		bind_evtchn_to_cpu(evtchn, tcpu, false);

	करो_unmask(info, EVT_MASK_REASON_TEMPORARY);

	वापस 0;
पूर्ण

/*
 * Find the CPU within @dest mask which has the least number of channels
 * asचिन्हित. This is not precise as the per cpu counts can be modअगरied
 * concurrently.
 */
अटल अचिन्हित पूर्णांक select_target_cpu(स्थिर काष्ठा cpumask *dest)
अणु
	अचिन्हित पूर्णांक cpu, best_cpu = अच_पूर्णांक_उच्च, minch = अच_पूर्णांक_उच्च;

	क्रम_each_cpu_and(cpu, dest, cpu_online_mask) अणु
		अचिन्हित पूर्णांक curch = atomic_पढ़ो(&channels_on_cpu[cpu]);

		अगर (curch < minch) अणु
			minch = curch;
			best_cpu = cpu;
		पूर्ण
	पूर्ण

	/*
	 * Catch the unlikely हाल that dest contains no online CPUs. Can't
	 * recurse.
	 */
	अगर (best_cpu == अच_पूर्णांक_उच्च)
		वापस select_target_cpu(cpu_online_mask);

	वापस best_cpu;
पूर्ण

अटल पूर्णांक set_affinity_irq(काष्ठा irq_data *data, स्थिर काष्ठा cpumask *dest,
			    bool क्रमce)
अणु
	अचिन्हित पूर्णांक tcpu = select_target_cpu(dest);
	पूर्णांक ret;

	ret = xen_rebind_evtchn_to_cpu(info_क्रम_irq(data->irq), tcpu);
	अगर (!ret)
		irq_data_update_effective_affinity(data, cpumask_of(tcpu));

	वापस ret;
पूर्ण

अटल व्योम enable_dynirq(काष्ठा irq_data *data)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(data->irq);
	evtchn_port_t evtchn = info ? info->evtchn : 0;

	अगर (VALID_EVTCHN(evtchn))
		करो_unmask(info, EVT_MASK_REASON_EXPLICIT);
पूर्ण

अटल व्योम disable_dynirq(काष्ठा irq_data *data)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(data->irq);
	evtchn_port_t evtchn = info ? info->evtchn : 0;

	अगर (VALID_EVTCHN(evtchn))
		करो_mask(info, EVT_MASK_REASON_EXPLICIT);
पूर्ण

अटल व्योम ack_dynirq(काष्ठा irq_data *data)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(data->irq);
	evtchn_port_t evtchn = info ? info->evtchn : 0;

	अगर (VALID_EVTCHN(evtchn))
		event_handler_निकास(info);
पूर्ण

अटल व्योम mask_ack_dynirq(काष्ठा irq_data *data)
अणु
	disable_dynirq(data);
	ack_dynirq(data);
पूर्ण

अटल व्योम lateeoi_ack_dynirq(काष्ठा irq_data *data)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(data->irq);
	evtchn_port_t evtchn = info ? info->evtchn : 0;

	अगर (VALID_EVTCHN(evtchn)) अणु
		करो_mask(info, EVT_MASK_REASON_EOI_PENDING);
		event_handler_निकास(info);
	पूर्ण
पूर्ण

अटल व्योम lateeoi_mask_ack_dynirq(काष्ठा irq_data *data)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(data->irq);
	evtchn_port_t evtchn = info ? info->evtchn : 0;

	अगर (VALID_EVTCHN(evtchn)) अणु
		करो_mask(info, EVT_MASK_REASON_EXPLICIT);
		event_handler_निकास(info);
	पूर्ण
पूर्ण

अटल पूर्णांक retrigger_dynirq(काष्ठा irq_data *data)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(data->irq);
	evtchn_port_t evtchn = info ? info->evtchn : 0;

	अगर (!VALID_EVTCHN(evtchn))
		वापस 0;

	करो_mask(info, EVT_MASK_REASON_TEMPORARY);
	set_evtchn(evtchn);
	करो_unmask(info, EVT_MASK_REASON_TEMPORARY);

	वापस 1;
पूर्ण

अटल व्योम restore_pirqs(व्योम)
अणु
	पूर्णांक pirq, rc, irq, gsi;
	काष्ठा physdev_map_pirq map_irq;
	काष्ठा irq_info *info;

	list_क्रम_each_entry(info, &xen_irq_list_head, list) अणु
		अगर (info->type != IRQT_PIRQ)
			जारी;

		pirq = info->u.pirq.pirq;
		gsi = info->u.pirq.gsi;
		irq = info->irq;

		/* save/restore of PT devices करोesn't work, so at this poपूर्णांक the
		 * only devices present are GSI based emulated devices */
		अगर (!gsi)
			जारी;

		map_irq.करोmid = DOMID_SELF;
		map_irq.type = MAP_PIRQ_TYPE_GSI;
		map_irq.index = gsi;
		map_irq.pirq = pirq;

		rc = HYPERVISOR_physdev_op(PHYSDEVOP_map_pirq, &map_irq);
		अगर (rc) अणु
			pr_warn("xen map irq failed gsi=%d irq=%d pirq=%d rc=%d\n",
				gsi, irq, pirq, rc);
			xen_मुक्त_irq(irq);
			जारी;
		पूर्ण

		prपूर्णांकk(KERN_DEBUG "xen: --> irq=%d, pirq=%d\n", irq, map_irq.pirq);

		__startup_pirq(irq);
	पूर्ण
पूर्ण

अटल व्योम restore_cpu_virqs(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा evtchn_bind_virq bind_virq;
	evtchn_port_t evtchn;
	पूर्णांक virq, irq;

	क्रम (virq = 0; virq < NR_VIRQS; virq++) अणु
		अगर ((irq = per_cpu(virq_to_irq, cpu)[virq]) == -1)
			जारी;

		BUG_ON(virq_from_irq(irq) != virq);

		/* Get a new binding from Xen. */
		bind_virq.virq = virq;
		bind_virq.vcpu = xen_vcpu_nr(cpu);
		अगर (HYPERVISOR_event_channel_op(EVTCHNOP_bind_virq,
						&bind_virq) != 0)
			BUG();
		evtchn = bind_virq.port;

		/* Record the new mapping. */
		(व्योम)xen_irq_info_virq_setup(cpu, irq, evtchn, virq);
		/* The affinity mask is still valid */
		bind_evtchn_to_cpu(evtchn, cpu, false);
	पूर्ण
पूर्ण

अटल व्योम restore_cpu_ipis(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा evtchn_bind_ipi bind_ipi;
	evtchn_port_t evtchn;
	पूर्णांक ipi, irq;

	क्रम (ipi = 0; ipi < XEN_NR_IPIS; ipi++) अणु
		अगर ((irq = per_cpu(ipi_to_irq, cpu)[ipi]) == -1)
			जारी;

		BUG_ON(ipi_from_irq(irq) != ipi);

		/* Get a new binding from Xen. */
		bind_ipi.vcpu = xen_vcpu_nr(cpu);
		अगर (HYPERVISOR_event_channel_op(EVTCHNOP_bind_ipi,
						&bind_ipi) != 0)
			BUG();
		evtchn = bind_ipi.port;

		/* Record the new mapping. */
		(व्योम)xen_irq_info_ipi_setup(cpu, irq, evtchn, ipi);
		/* The affinity mask is still valid */
		bind_evtchn_to_cpu(evtchn, cpu, false);
	पूर्ण
पूर्ण

/* Clear an irq's pending state, in preparation क्रम polling on it */
व्योम xen_clear_irq_pending(पूर्णांक irq)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(irq);
	evtchn_port_t evtchn = info ? info->evtchn : 0;

	अगर (VALID_EVTCHN(evtchn))
		event_handler_निकास(info);
पूर्ण
EXPORT_SYMBOL(xen_clear_irq_pending);
व्योम xen_set_irq_pending(पूर्णांक irq)
अणु
	evtchn_port_t evtchn = evtchn_from_irq(irq);

	अगर (VALID_EVTCHN(evtchn))
		set_evtchn(evtchn);
पूर्ण

bool xen_test_irq_pending(पूर्णांक irq)
अणु
	evtchn_port_t evtchn = evtchn_from_irq(irq);
	bool ret = false;

	अगर (VALID_EVTCHN(evtchn))
		ret = test_evtchn(evtchn);

	वापस ret;
पूर्ण

/* Poll रुकोing क्रम an irq to become pending with समयout.  In the usual हाल,
 * the irq will be disabled so it won't deliver an पूर्णांकerrupt. */
व्योम xen_poll_irq_समयout(पूर्णांक irq, u64 समयout)
अणु
	evtchn_port_t evtchn = evtchn_from_irq(irq);

	अगर (VALID_EVTCHN(evtchn)) अणु
		काष्ठा sched_poll poll;

		poll.nr_ports = 1;
		poll.समयout = समयout;
		set_xen_guest_handle(poll.ports, &evtchn);

		अगर (HYPERVISOR_sched_op(SCHEDOP_poll, &poll) != 0)
			BUG();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(xen_poll_irq_समयout);
/* Poll रुकोing क्रम an irq to become pending.  In the usual हाल, the
 * irq will be disabled so it won't deliver an पूर्णांकerrupt. */
व्योम xen_poll_irq(पूर्णांक irq)
अणु
	xen_poll_irq_समयout(irq, 0 /* no समयout */);
पूर्ण

/* Check whether the IRQ line is shared with other guests. */
पूर्णांक xen_test_irq_shared(पूर्णांक irq)
अणु
	काष्ठा irq_info *info = info_क्रम_irq(irq);
	काष्ठा physdev_irq_status_query irq_status;

	अगर (WARN_ON(!info))
		वापस -ENOENT;

	irq_status.irq = info->u.pirq.pirq;

	अगर (HYPERVISOR_physdev_op(PHYSDEVOP_irq_status_query, &irq_status))
		वापस 0;
	वापस !(irq_status.flags & XENIRQSTAT_shared);
पूर्ण
EXPORT_SYMBOL_GPL(xen_test_irq_shared);

व्योम xen_irq_resume(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;
	काष्ठा irq_info *info;

	/* New event-channel space is not 'live' yet. */
	xen_evtchn_resume();

	/* No IRQ <-> event-channel mappings. */
	list_क्रम_each_entry(info, &xen_irq_list_head, list) अणु
		/* Zap event-channel binding */
		info->evtchn = 0;
		/* Adjust accounting */
		channels_on_cpu_dec(info);
	पूर्ण

	clear_evtchn_to_irq_all();

	क्रम_each_possible_cpu(cpu) अणु
		restore_cpu_virqs(cpu);
		restore_cpu_ipis(cpu);
	पूर्ण

	restore_pirqs();
पूर्ण

अटल काष्ठा irq_chip xen_dynamic_chip __पढ़ो_mostly = अणु
	.name			= "xen-dyn",

	.irq_disable		= disable_dynirq,
	.irq_mask		= disable_dynirq,
	.irq_unmask		= enable_dynirq,

	.irq_ack		= ack_dynirq,
	.irq_mask_ack		= mask_ack_dynirq,

	.irq_set_affinity	= set_affinity_irq,
	.irq_retrigger		= retrigger_dynirq,
पूर्ण;

अटल काष्ठा irq_chip xen_lateeoi_chip __पढ़ो_mostly = अणु
	/* The chip name needs to contain "xen-dyn" क्रम irqbalance to work. */
	.name			= "xen-dyn-lateeoi",

	.irq_disable		= disable_dynirq,
	.irq_mask		= disable_dynirq,
	.irq_unmask		= enable_dynirq,

	.irq_ack		= lateeoi_ack_dynirq,
	.irq_mask_ack		= lateeoi_mask_ack_dynirq,

	.irq_set_affinity	= set_affinity_irq,
	.irq_retrigger		= retrigger_dynirq,
पूर्ण;

अटल काष्ठा irq_chip xen_pirq_chip __पढ़ो_mostly = अणु
	.name			= "xen-pirq",

	.irq_startup		= startup_pirq,
	.irq_shutकरोwn		= shutकरोwn_pirq,
	.irq_enable		= enable_pirq,
	.irq_disable		= disable_pirq,

	.irq_mask		= disable_dynirq,
	.irq_unmask		= enable_dynirq,

	.irq_ack		= eoi_pirq,
	.irq_eoi		= eoi_pirq,
	.irq_mask_ack		= mask_ack_pirq,

	.irq_set_affinity	= set_affinity_irq,

	.irq_retrigger		= retrigger_dynirq,
पूर्ण;

अटल काष्ठा irq_chip xen_percpu_chip __पढ़ो_mostly = अणु
	.name			= "xen-percpu",

	.irq_disable		= disable_dynirq,
	.irq_mask		= disable_dynirq,
	.irq_unmask		= enable_dynirq,

	.irq_ack		= ack_dynirq,
पूर्ण;

#अगर_घोषित CONFIG_XEN_PVHVM
/* Vector callbacks are better than PCI पूर्णांकerrupts to receive event
 * channel notअगरications because we can receive vector callbacks on any
 * vcpu and we करोn't need PCI support or APIC पूर्णांकeractions. */
व्योम xen_setup_callback_vector(व्योम)
अणु
	uपूर्णांक64_t callback_via;

	अगर (xen_have_vector_callback) अणु
		callback_via = HVM_CALLBACK_VECTOR(HYPERVISOR_CALLBACK_VECTOR);
		अगर (xen_set_callback_via(callback_via)) अणु
			pr_err("Request for Xen HVM callback vector failed\n");
			xen_have_vector_callback = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल __init व्योम xen_alloc_callback_vector(व्योम)
अणु
	अगर (!xen_have_vector_callback)
		वापस;

	pr_info("Xen HVM callback vector for event delivery is enabled\n");
	alloc_पूर्णांकr_gate(HYPERVISOR_CALLBACK_VECTOR, यंत्र_sysvec_xen_hvm_callback);
पूर्ण
#अन्यथा
व्योम xen_setup_callback_vector(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम xen_alloc_callback_vector(व्योम) अणुपूर्ण
#पूर्ण_अगर

bool xen_fअगरo_events = true;
module_param_named(fअगरo_events, xen_fअगरo_events, bool, 0);

अटल पूर्णांक xen_evtchn_cpu_prepare(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक ret = 0;

	xen_cpu_init_eoi(cpu);

	अगर (evtchn_ops->percpu_init)
		ret = evtchn_ops->percpu_init(cpu);

	वापस ret;
पूर्ण

अटल पूर्णांक xen_evtchn_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक ret = 0;

	अगर (evtchn_ops->percpu_deinit)
		ret = evtchn_ops->percpu_deinit(cpu);

	वापस ret;
पूर्ण

व्योम __init xen_init_IRQ(व्योम)
अणु
	पूर्णांक ret = -EINVAL;
	evtchn_port_t evtchn;

	अगर (xen_fअगरo_events)
		ret = xen_evtchn_fअगरo_init();
	अगर (ret < 0) अणु
		xen_evtchn_2l_init();
		xen_fअगरo_events = false;
	पूर्ण

	xen_cpu_init_eoi(smp_processor_id());

	cpuhp_setup_state_nocalls(CPUHP_XEN_EVTCHN_PREPARE,
				  "xen/evtchn:prepare",
				  xen_evtchn_cpu_prepare, xen_evtchn_cpu_dead);

	evtchn_to_irq = kसुस्मृति(EVTCHN_ROW(xen_evtchn_max_channels()),
				माप(*evtchn_to_irq), GFP_KERNEL);
	BUG_ON(!evtchn_to_irq);

	/* No event channels are 'live' right now. */
	क्रम (evtchn = 0; evtchn < xen_evtchn_nr_channels(); evtchn++)
		mask_evtchn(evtchn);

	pirq_needs_eoi = pirq_needs_eoi_flag;

#अगर_घोषित CONFIG_X86
	अगर (xen_pv_करोमुख्य()) अणु
		अगर (xen_initial_करोमुख्य())
			pci_xen_initial_करोमुख्य();
	पूर्ण
	अगर (xen_feature(XENFEAT_hvm_callback_vector)) अणु
		xen_setup_callback_vector();
		xen_alloc_callback_vector();
	पूर्ण

	अगर (xen_hvm_करोमुख्य()) अणु
		native_init_IRQ();
		/* pci_xen_hvm_init must be called after native_init_IRQ so that
		 * __acpi_रेजिस्टर_gsi can poपूर्णांक at the right function */
		pci_xen_hvm_init();
	पूर्ण अन्यथा अणु
		पूर्णांक rc;
		काष्ठा physdev_pirq_eoi_gmfn eoi_gmfn;

		pirq_eoi_map = (व्योम *)__get_मुक्त_page(GFP_KERNEL|__GFP_ZERO);
		eoi_gmfn.gmfn = virt_to_gfn(pirq_eoi_map);
		rc = HYPERVISOR_physdev_op(PHYSDEVOP_pirq_eoi_gmfn_v2, &eoi_gmfn);
		अगर (rc != 0) अणु
			मुक्त_page((अचिन्हित दीर्घ) pirq_eoi_map);
			pirq_eoi_map = शून्य;
		पूर्ण अन्यथा
			pirq_needs_eoi = pirq_check_eoi_map;
	पूर्ण
#पूर्ण_अगर
पूर्ण
