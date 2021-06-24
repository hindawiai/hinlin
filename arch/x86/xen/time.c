<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xen समय implementation.
 *
 * This is implemented in terms of a घड़ीsource driver which uses
 * the hypervisor घड़ी as a nanosecond समयbase, and a घड़ीevent
 * driver which uses the hypervisor's समयr mechanism.
 *
 * Jeremy Fitzhardinge <jeremy@xensource.com>, XenSource Inc, 2007
 */
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/pvघड़ी_gtod.h>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>

#समावेश <यंत्र/pvघड़ी.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/xen/hypercall.h>

#समावेश <xen/events.h>
#समावेश <xen/features.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/vcpu.h>

#समावेश "xen-ops.h"

/* Minimum amount of समय until next घड़ी event fires */
#घोषणा TIMER_SLOP	100000

अटल u64 xen_sched_घड़ी_offset __पढ़ो_mostly;

/* Get the TSC speed from Xen */
अटल अचिन्हित दीर्घ xen_tsc_khz(व्योम)
अणु
	काष्ठा pvघड़ी_vcpu_समय_info *info =
		&HYPERVISOR_shared_info->vcpu_info[0].समय;

	setup_क्रमce_cpu_cap(X86_FEATURE_TSC_KNOWN_FREQ);
	वापस pvघड़ी_प्रकारsc_khz(info);
पूर्ण

अटल u64 xen_घड़ीsource_पढ़ो(व्योम)
अणु
        काष्ठा pvघड़ी_vcpu_समय_info *src;
	u64 ret;

	preempt_disable_notrace();
	src = &__this_cpu_पढ़ो(xen_vcpu)->समय;
	ret = pvघड़ी_घड़ीsource_पढ़ो(src);
	preempt_enable_notrace();
	वापस ret;
पूर्ण

अटल u64 xen_घड़ीsource_get_cycles(काष्ठा घड़ीsource *cs)
अणु
	वापस xen_घड़ीsource_पढ़ो();
पूर्ण

अटल u64 xen_sched_घड़ी(व्योम)
अणु
	वापस xen_घड़ीsource_पढ़ो() - xen_sched_घड़ी_offset;
पूर्ण

अटल व्योम xen_पढ़ो_wallघड़ी(काष्ठा बारpec64 *ts)
अणु
	काष्ठा shared_info *s = HYPERVISOR_shared_info;
	काष्ठा pvघड़ी_wall_घड़ी *wall_घड़ी = &(s->wc);
        काष्ठा pvघड़ी_vcpu_समय_info *vcpu_समय;

	vcpu_समय = &get_cpu_var(xen_vcpu)->समय;
	pvघड़ी_पढ़ो_wallघड़ी(wall_घड़ी, vcpu_समय, ts);
	put_cpu_var(xen_vcpu);
पूर्ण

अटल व्योम xen_get_wallघड़ी(काष्ठा बारpec64 *now)
अणु
	xen_पढ़ो_wallघड़ी(now);
पूर्ण

अटल पूर्णांक xen_set_wallघड़ी(स्थिर काष्ठा बारpec64 *now)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक xen_pvघड़ी_gtod_notअगरy(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ was_set, व्योम *priv)
अणु
	/* Protected by the calling core code serialization */
	अटल काष्ठा बारpec64 next_sync;

	काष्ठा xen_platक्रमm_op op;
	काष्ठा बारpec64 now;
	काष्ठा समयkeeper *tk = priv;
	अटल bool समय_रखो64_supported = true;
	पूर्णांक ret;

	now.tv_sec = tk->xसमय_sec;
	now.tv_nsec = (दीर्घ)(tk->tkr_mono.xसमय_nsec >> tk->tkr_mono.shअगरt);

	/*
	 * We only take the expensive HV call when the घड़ी was set
	 * or when the 11 minutes RTC synchronization समय elapsed.
	 */
	अगर (!was_set && बारpec64_compare(&now, &next_sync) < 0)
		वापस NOTIFY_OK;

again:
	अगर (समय_रखो64_supported) अणु
		op.cmd = XENPF_समय_रखो64;
		op.u.समय_रखो64.mbz = 0;
		op.u.समय_रखो64.secs = now.tv_sec;
		op.u.समय_रखो64.nsecs = now.tv_nsec;
		op.u.समय_रखो64.प्रणाली_समय = xen_घड़ीsource_पढ़ो();
	पूर्ण अन्यथा अणु
		op.cmd = XENPF_समय_रखो32;
		op.u.समय_रखो32.secs = now.tv_sec;
		op.u.समय_रखो32.nsecs = now.tv_nsec;
		op.u.समय_रखो32.प्रणाली_समय = xen_घड़ीsource_पढ़ो();
	पूर्ण

	ret = HYPERVISOR_platक्रमm_op(&op);

	अगर (ret == -ENOSYS && समय_रखो64_supported) अणु
		समय_रखो64_supported = false;
		जाओ again;
	पूर्ण
	अगर (ret < 0)
		वापस NOTIFY_BAD;

	/*
	 * Move the next drअगरt compensation समय 11 minutes
	 * ahead. That's emulating the sync_cmos_घड़ी() update क्रम
	 * the hardware RTC.
	 */
	next_sync = now;
	next_sync.tv_sec += 11 * 60;

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block xen_pvघड़ी_gtod_notअगरier = अणु
	.notअगरier_call = xen_pvघड़ी_gtod_notअगरy,
पूर्ण;

अटल पूर्णांक xen_cs_enable(काष्ठा घड़ीsource *cs)
अणु
	vघड़ीs_set_used(VDSO_CLOCKMODE_PVCLOCK);
	वापस 0;
पूर्ण

अटल काष्ठा घड़ीsource xen_घड़ीsource __पढ़ो_mostly = अणु
	.name	= "xen",
	.rating	= 400,
	.पढ़ो	= xen_घड़ीsource_get_cycles,
	.mask	= CLOCKSOURCE_MASK(64),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
	.enable = xen_cs_enable,
पूर्ण;

/*
   Xen घड़ीevent implementation

   Xen has two घड़ीevent implementations:

   The old समयr_op one works with all released versions of Xen prior
   to version 3.0.4.  This version of the hypervisor provides a
   single-shot समयr with nanosecond resolution.  However, sharing the
   same event channel is a 100Hz tick which is delivered जबतक the
   vcpu is running.  We करोn't care about or use this tick, but it will
   cause the core समय code to think the समयr fired too soon, and
   will end up resetting it each समय.  It could be filtered, but
   करोing so has complications when the kसमय घड़ीsource is not yet
   the xen घड़ीsource (ie, at boot समय).

   The new vcpu_op-based समयr पूर्णांकerface allows the tick समयr period
   to be changed or turned off.  The tick समयr is not useful as a
   periodic समयr because events are only delivered to running vcpus.
   The one-shot समयr can report when a समयout is in the past, so
   set_next_event is capable of वापसing -ETIME when appropriate.
   This पूर्णांकerface is used when available.
*/


/*
  Get a hypervisor असलolute समय.  In theory we could मुख्यtain an
  offset between the kernel's time and the hypervisor's समय, and
  apply that to a kernel's असलolute समयout.  Unक्रमtunately the
  hypervisor and kernel बार can drअगरt even अगर the kernel is using
  the Xen घड़ीsource, because ntp can warp the kernel's घड़ीsource.
*/
अटल s64 get_असल_समयout(अचिन्हित दीर्घ delta)
अणु
	वापस xen_घड़ीsource_पढ़ो() + delta;
पूर्ण

अटल पूर्णांक xen_समयrop_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	/* cancel समयout */
	HYPERVISOR_set_समयr_op(0);

	वापस 0;
पूर्ण

अटल पूर्णांक xen_समयrop_set_next_event(अचिन्हित दीर्घ delta,
				      काष्ठा घड़ी_event_device *evt)
अणु
	WARN_ON(!घड़ीevent_state_oneshot(evt));

	अगर (HYPERVISOR_set_समयr_op(get_असल_समयout(delta)) < 0)
		BUG();

	/* We may have missed the deadline, but there's no real way of
	   knowing क्रम sure.  If the event was in the past, then we'll
	   get an immediate पूर्णांकerrupt. */

	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device xen_समयrop_घड़ीevent __ro_after_init = अणु
	.name			= "xen",
	.features		= CLOCK_EVT_FEAT_ONESHOT,

	.max_delta_ns		= 0xffffffff,
	.max_delta_ticks	= 0xffffffff,
	.min_delta_ns		= TIMER_SLOP,
	.min_delta_ticks	= TIMER_SLOP,

	.mult			= 1,
	.shअगरt			= 0,
	.rating			= 500,

	.set_state_shutकरोwn	= xen_समयrop_shutकरोwn,
	.set_next_event		= xen_समयrop_set_next_event,
पूर्ण;

अटल पूर्णांक xen_vcpuop_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	पूर्णांक cpu = smp_processor_id();

	अगर (HYPERVISOR_vcpu_op(VCPUOP_stop_singleshot_समयr, xen_vcpu_nr(cpu),
			       शून्य) ||
	    HYPERVISOR_vcpu_op(VCPUOP_stop_periodic_समयr, xen_vcpu_nr(cpu),
			       शून्य))
		BUG();

	वापस 0;
पूर्ण

अटल पूर्णांक xen_vcpuop_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	पूर्णांक cpu = smp_processor_id();

	अगर (HYPERVISOR_vcpu_op(VCPUOP_stop_periodic_समयr, xen_vcpu_nr(cpu),
			       शून्य))
		BUG();

	वापस 0;
पूर्ण

अटल पूर्णांक xen_vcpuop_set_next_event(अचिन्हित दीर्घ delta,
				     काष्ठा घड़ी_event_device *evt)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा vcpu_set_singleshot_समयr single;
	पूर्णांक ret;

	WARN_ON(!घड़ीevent_state_oneshot(evt));

	single.समयout_असल_ns = get_असल_समयout(delta);
	/* Get an event anyway, even अगर the समयout is alपढ़ोy expired */
	single.flags = 0;

	ret = HYPERVISOR_vcpu_op(VCPUOP_set_singleshot_समयr, xen_vcpu_nr(cpu),
				 &single);
	BUG_ON(ret != 0);

	वापस ret;
पूर्ण

अटल काष्ठा घड़ी_event_device xen_vcpuop_घड़ीevent __ro_after_init = अणु
	.name = "xen",
	.features = CLOCK_EVT_FEAT_ONESHOT,

	.max_delta_ns = 0xffffffff,
	.max_delta_ticks = 0xffffffff,
	.min_delta_ns = TIMER_SLOP,
	.min_delta_ticks = TIMER_SLOP,

	.mult = 1,
	.shअगरt = 0,
	.rating = 500,

	.set_state_shutकरोwn = xen_vcpuop_shutकरोwn,
	.set_state_oneshot = xen_vcpuop_set_oneshot,
	.set_next_event = xen_vcpuop_set_next_event,
पूर्ण;

अटल स्थिर काष्ठा घड़ी_event_device *xen_घड़ीevent =
	&xen_समयrop_घड़ीevent;

काष्ठा xen_घड़ी_event_device अणु
	काष्ठा घड़ी_event_device evt;
	अक्षर name[16];
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा xen_घड़ी_event_device, xen_घड़ी_events) = अणु .evt.irq = -1 पूर्ण;

अटल irqवापस_t xen_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = this_cpu_ptr(&xen_घड़ी_events.evt);
	irqवापस_t ret;

	ret = IRQ_NONE;
	अगर (evt->event_handler) अणु
		evt->event_handler(evt);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

व्योम xen_tearकरोwn_समयr(पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *evt;
	evt = &per_cpu(xen_घड़ी_events, cpu).evt;

	अगर (evt->irq >= 0) अणु
		unbind_from_irqhandler(evt->irq, शून्य);
		evt->irq = -1;
	पूर्ण
पूर्ण

व्योम xen_setup_समयr(पूर्णांक cpu)
अणु
	काष्ठा xen_घड़ी_event_device *xevt = &per_cpu(xen_घड़ी_events, cpu);
	काष्ठा घड़ी_event_device *evt = &xevt->evt;
	पूर्णांक irq;

	WARN(evt->irq >= 0, "IRQ%d for CPU%d is already allocated\n", evt->irq, cpu);
	अगर (evt->irq >= 0)
		xen_tearकरोwn_समयr(cpu);

	prपूर्णांकk(KERN_INFO "installing Xen timer for CPU %d\n", cpu);

	snम_लिखो(xevt->name, माप(xevt->name), "timer%d", cpu);

	irq = bind_virq_to_irqhandler(VIRQ_TIMER, cpu, xen_समयr_पूर्णांकerrupt,
				      IRQF_PERCPU|IRQF_NOBALANCING|IRQF_TIMER|
				      IRQF_FORCE_RESUME|IRQF_EARLY_RESUME,
				      xevt->name, शून्य);
	(व्योम)xen_set_irq_priority(irq, XEN_IRQ_PRIORITY_MAX);

	स_नकल(evt, xen_घड़ीevent, माप(*evt));

	evt->cpumask = cpumask_of(cpu);
	evt->irq = irq;
पूर्ण


व्योम xen_setup_cpu_घड़ीevents(व्योम)
अणु
	घड़ीevents_रेजिस्टर_device(this_cpu_ptr(&xen_घड़ी_events.evt));
पूर्ण

व्योम xen_समयr_resume(व्योम)
अणु
	पूर्णांक cpu;

	अगर (xen_घड़ीevent != &xen_vcpuop_घड़ीevent)
		वापस;

	क्रम_each_online_cpu(cpu) अणु
		अगर (HYPERVISOR_vcpu_op(VCPUOP_stop_periodic_समयr,
				       xen_vcpu_nr(cpu), शून्य))
			BUG();
	पूर्ण
पूर्ण

अटल काष्ठा pvघड़ी_vsyscall_समय_info *xen_घड़ी __पढ़ो_mostly;
अटल u64 xen_घड़ी_value_saved;

व्योम xen_save_समय_memory_area(व्योम)
अणु
	काष्ठा vcpu_रेजिस्टर_समय_memory_area t;
	पूर्णांक ret;

	xen_घड़ी_value_saved = xen_घड़ीsource_पढ़ो() - xen_sched_घड़ी_offset;

	अगर (!xen_घड़ी)
		वापस;

	t.addr.v = शून्य;

	ret = HYPERVISOR_vcpu_op(VCPUOP_रेजिस्टर_vcpu_समय_memory_area, 0, &t);
	अगर (ret != 0)
		pr_notice("Cannot save secondary vcpu_time_info (err %d)",
			  ret);
	अन्यथा
		clear_page(xen_घड़ी);
पूर्ण

व्योम xen_restore_समय_memory_area(व्योम)
अणु
	काष्ठा vcpu_रेजिस्टर_समय_memory_area t;
	पूर्णांक ret;

	अगर (!xen_घड़ी)
		जाओ out;

	t.addr.v = &xen_घड़ी->pvti;

	ret = HYPERVISOR_vcpu_op(VCPUOP_रेजिस्टर_vcpu_समय_memory_area, 0, &t);

	/*
	 * We करोn't disable VDSO_CLOCKMODE_PVCLOCK entirely अगर it fails to
	 * रेजिस्टर the secondary समय info with Xen or अगर we migrated to a
	 * host without the necessary flags. On both of these हालs what
	 * happens is either process seeing a zeroed out pvti or seeing no
	 * PVCLOCK_TSC_STABLE_BIT bit set. Userspace checks the latter and
	 * अगर 0, it discards the data in pvti and fallbacks to a प्रणाली
	 * call क्रम a reliable बारtamp.
	 */
	अगर (ret != 0)
		pr_notice("Cannot restore secondary vcpu_time_info (err %d)",
			  ret);

out:
	/* Need pvघड़ी_resume() beक्रमe using xen_घड़ीsource_पढ़ो(). */
	pvघड़ी_resume();
	xen_sched_घड़ी_offset = xen_घड़ीsource_पढ़ो() - xen_घड़ी_value_saved;
पूर्ण

अटल व्योम xen_setup_vsyscall_समय_info(व्योम)
अणु
	काष्ठा vcpu_रेजिस्टर_समय_memory_area t;
	काष्ठा pvघड़ी_vsyscall_समय_info *ti;
	पूर्णांक ret;

	ti = (काष्ठा pvघड़ी_vsyscall_समय_info *)get_zeroed_page(GFP_KERNEL);
	अगर (!ti)
		वापस;

	t.addr.v = &ti->pvti;

	ret = HYPERVISOR_vcpu_op(VCPUOP_रेजिस्टर_vcpu_समय_memory_area, 0, &t);
	अगर (ret) अणु
		pr_notice("xen: VDSO_CLOCKMODE_PVCLOCK not supported (err %d)\n", ret);
		मुक्त_page((अचिन्हित दीर्घ)ti);
		वापस;
	पूर्ण

	/*
	 * If primary समय info had this bit set, secondary should too since
	 * it's the same data on both just dअगरferent memory regions. But we
	 * still check it in हाल hypervisor is buggy.
	 */
	अगर (!(ti->pvti.flags & PVCLOCK_TSC_STABLE_BIT)) अणु
		t.addr.v = शून्य;
		ret = HYPERVISOR_vcpu_op(VCPUOP_रेजिस्टर_vcpu_समय_memory_area,
					 0, &t);
		अगर (!ret)
			मुक्त_page((अचिन्हित दीर्घ)ti);

		pr_notice("xen: VDSO_CLOCKMODE_PVCLOCK not supported (tsc unstable)\n");
		वापस;
	पूर्ण

	xen_घड़ी = ti;
	pvघड़ी_set_pvti_cpu0_va(xen_घड़ी);

	xen_घड़ीsource.vdso_घड़ी_mode = VDSO_CLOCKMODE_PVCLOCK;
पूर्ण

अटल व्योम __init xen_समय_init(व्योम)
अणु
	काष्ठा pvघड़ी_vcpu_समय_info *pvti;
	पूर्णांक cpu = smp_processor_id();
	काष्ठा बारpec64 tp;

	/* As Dom0 is never moved, no penalty on using TSC there */
	अगर (xen_initial_करोमुख्य())
		xen_घड़ीsource.rating = 275;

	घड़ीsource_रेजिस्टर_hz(&xen_घड़ीsource, NSEC_PER_SEC);

	अगर (HYPERVISOR_vcpu_op(VCPUOP_stop_periodic_समयr, xen_vcpu_nr(cpu),
			       शून्य) == 0) अणु
		/* Successfully turned off 100Hz tick, so we have the
		   vcpuop-based समयr पूर्णांकerface */
		prपूर्णांकk(KERN_DEBUG "Xen: using vcpuop timer interface\n");
		xen_घड़ीevent = &xen_vcpuop_घड़ीevent;
	पूर्ण

	/* Set initial प्रणाली समय with full resolution */
	xen_पढ़ो_wallघड़ी(&tp);
	करो_समय_रखोofday64(&tp);

	setup_क्रमce_cpu_cap(X86_FEATURE_TSC);

	/*
	 * We check ahead on the primary समय info अगर this
	 * bit is supported hence speeding up Xen घड़ीsource.
	 */
	pvti = &__this_cpu_पढ़ो(xen_vcpu)->समय;
	अगर (pvti->flags & PVCLOCK_TSC_STABLE_BIT) अणु
		pvघड़ी_set_flags(PVCLOCK_TSC_STABLE_BIT);
		xen_setup_vsyscall_समय_info();
	पूर्ण

	xen_setup_runstate_info(cpu);
	xen_setup_समयr(cpu);
	xen_setup_cpu_घड़ीevents();

	xen_समय_setup_guest();

	अगर (xen_initial_करोमुख्य())
		pvघड़ी_gtod_रेजिस्टर_notअगरier(&xen_pvघड़ी_gtod_notअगरier);
पूर्ण

अटल व्योम __init xen_init_समय_common(व्योम)
अणु
	xen_sched_घड़ी_offset = xen_घड़ीsource_पढ़ो();
	अटल_call_update(pv_steal_घड़ी, xen_steal_घड़ी);
	paravirt_set_sched_घड़ी(xen_sched_घड़ी);

	x86_platक्रमm.calibrate_tsc = xen_tsc_khz;
	x86_platक्रमm.get_wallघड़ी = xen_get_wallघड़ी;
पूर्ण

व्योम __init xen_init_समय_ops(व्योम)
अणु
	xen_init_समय_common();

	x86_init.समयrs.समयr_init = xen_समय_init;
	x86_init.समयrs.setup_percpu_घड़ीev = x86_init_noop;
	x86_cpuinit.setup_percpu_घड़ीev = x86_init_noop;

	/* Dom0 uses the native method to set the hardware RTC. */
	अगर (!xen_initial_करोमुख्य())
		x86_platक्रमm.set_wallघड़ी = xen_set_wallघड़ी;
पूर्ण

#अगर_घोषित CONFIG_XEN_PVHVM
अटल व्योम xen_hvm_setup_cpu_घड़ीevents(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	xen_setup_runstate_info(cpu);
	/*
	 * xen_setup_समयr(cpu) - snम_लिखो is bad in atomic context. Hence
	 * करोing it xen_hvm_cpu_notअगरy (which माला_लो called by smp_init during
	 * early bootup and also during CPU hotplug events).
	 */
	xen_setup_cpu_घड़ीevents();
पूर्ण

व्योम __init xen_hvm_init_समय_ops(व्योम)
अणु
	/*
	 * vector callback is needed otherwise we cannot receive पूर्णांकerrupts
	 * on cpu > 0 and at this poपूर्णांक we करोn't know how many cpus are
	 * available.
	 */
	अगर (!xen_have_vector_callback)
		वापस;

	अगर (!xen_feature(XENFEAT_hvm_safe_pvघड़ी)) अणु
		pr_info("Xen doesn't support pvclock on HVM, disable pv timer");
		वापस;
	पूर्ण

	xen_init_समय_common();

	x86_init.समयrs.setup_percpu_घड़ीev = xen_समय_init;
	x86_cpuinit.setup_percpu_घड़ीev = xen_hvm_setup_cpu_घड़ीevents;

	x86_platक्रमm.set_wallघड़ी = xen_set_wallघड़ी;
पूर्ण
#पूर्ण_अगर

/* Kernel parameter to specअगरy Xen समयr slop */
अटल पूर्णांक __init parse_xen_समयr_slop(अक्षर *ptr)
अणु
	अचिन्हित दीर्घ slop = memparse(ptr, शून्य);

	xen_समयrop_घड़ीevent.min_delta_ns = slop;
	xen_समयrop_घड़ीevent.min_delta_ticks = slop;
	xen_vcpuop_घड़ीevent.min_delta_ns = slop;
	xen_vcpuop_घड़ीevent.min_delta_ticks = slop;

	वापस 0;
पूर्ण
early_param("xen_timer_slop", parse_xen_समयr_slop);
