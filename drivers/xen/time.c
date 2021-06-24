<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xen stolen ticks accounting.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/math64.h>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/अटल_call.h>

#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/xen/hypercall.h>

#समावेश <xen/events.h>
#समावेश <xen/features.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/vcpu.h>
#समावेश <xen/xen-ops.h>

/* runstate info updated by Xen */
अटल DEFINE_PER_CPU(काष्ठा vcpu_runstate_info, xen_runstate);

अटल DEFINE_PER_CPU(u64[4], old_runstate_समय);

/* वापस an consistent snapshot of 64-bit समय/counter value */
अटल u64 get64(स्थिर u64 *p)
अणु
	u64 ret;

	अगर (BITS_PER_LONG < 64) अणु
		u32 *p32 = (u32 *)p;
		u32 h, l, h2;

		/*
		 * Read high then low, and then make sure high is
		 * still the same; this will only loop अगर low wraps
		 * and carries पूर्णांकo high.
		 * XXX some clean way to make this endian-proof?
		 */
		करो अणु
			h = READ_ONCE(p32[1]);
			l = READ_ONCE(p32[0]);
			h2 = READ_ONCE(p32[1]);
		पूर्ण जबतक(h2 != h);

		ret = (((u64)h) << 32) | l;
	पूर्ण अन्यथा
		ret = READ_ONCE(*p);

	वापस ret;
पूर्ण

अटल व्योम xen_get_runstate_snapshot_cpu_delta(
			      काष्ठा vcpu_runstate_info *res, अचिन्हित पूर्णांक cpu)
अणु
	u64 state_समय;
	काष्ठा vcpu_runstate_info *state;

	BUG_ON(preemptible());

	state = per_cpu_ptr(&xen_runstate, cpu);

	करो अणु
		state_समय = get64(&state->state_entry_समय);
		rmb();	/* Hypervisor might update data. */
		*res = __READ_ONCE(*state);
		rmb();	/* Hypervisor might update data. */
	पूर्ण जबतक (get64(&state->state_entry_समय) != state_समय ||
		 (state_समय & XEN_RUNSTATE_UPDATE));
पूर्ण

अटल व्योम xen_get_runstate_snapshot_cpu(काष्ठा vcpu_runstate_info *res,
					  अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i;

	xen_get_runstate_snapshot_cpu_delta(res, cpu);

	क्रम (i = 0; i < 4; i++)
		res->समय[i] += per_cpu(old_runstate_समय, cpu)[i];
पूर्ण

व्योम xen_manage_runstate_समय(पूर्णांक action)
अणु
	अटल काष्ठा vcpu_runstate_info *runstate_delta;
	काष्ठा vcpu_runstate_info state;
	पूर्णांक cpu, i;

	चयन (action) अणु
	हाल -1: /* backup runstate समय beक्रमe suspend */
		अगर (unlikely(runstate_delta))
			pr_warn_once("%s: memory leak as runstate_delta is not NULL\n",
					__func__);

		runstate_delta = kदो_स्मृति_array(num_possible_cpus(),
					माप(*runstate_delta),
					GFP_ATOMIC);
		अगर (unlikely(!runstate_delta)) अणु
			pr_warn("%s: failed to allocate runstate_delta\n",
					__func__);
			वापस;
		पूर्ण

		क्रम_each_possible_cpu(cpu) अणु
			xen_get_runstate_snapshot_cpu_delta(&state, cpu);
			स_नकल(runstate_delta[cpu].समय, state.समय,
					माप(runstate_delta[cpu].समय));
		पूर्ण

		अवरोध;

	हाल 0: /* backup runstate समय after resume */
		अगर (unlikely(!runstate_delta)) अणु
			pr_warn("%s: cannot accumulate runstate time as runstate_delta is NULL\n",
					__func__);
			वापस;
		पूर्ण

		क्रम_each_possible_cpu(cpu) अणु
			क्रम (i = 0; i < 4; i++)
				per_cpu(old_runstate_समय, cpu)[i] +=
					runstate_delta[cpu].समय[i];
		पूर्ण

		अवरोध;

	शेष: /* करो not accumulate runstate समय क्रम checkpoपूर्णांकing */
		अवरोध;
	पूर्ण

	अगर (action != -1 && runstate_delta) अणु
		kमुक्त(runstate_delta);
		runstate_delta = शून्य;
	पूर्ण
पूर्ण

/*
 * Runstate accounting
 */
व्योम xen_get_runstate_snapshot(काष्ठा vcpu_runstate_info *res)
अणु
	xen_get_runstate_snapshot_cpu(res, smp_processor_id());
पूर्ण

/* वापस true when a vcpu could run but has no real cpu to run on */
bool xen_vcpu_stolen(पूर्णांक vcpu)
अणु
	वापस per_cpu(xen_runstate, vcpu).state == RUNSTATE_runnable;
पूर्ण

u64 xen_steal_घड़ी(पूर्णांक cpu)
अणु
	काष्ठा vcpu_runstate_info state;

	xen_get_runstate_snapshot_cpu(&state, cpu);
	वापस state.समय[RUNSTATE_runnable] + state.समय[RUNSTATE_offline];
पूर्ण

व्योम xen_setup_runstate_info(पूर्णांक cpu)
अणु
	काष्ठा vcpu_रेजिस्टर_runstate_memory_area area;

	area.addr.v = &per_cpu(xen_runstate, cpu);

	अगर (HYPERVISOR_vcpu_op(VCPUOP_रेजिस्टर_runstate_memory_area,
			       xen_vcpu_nr(cpu), &area))
		BUG();
पूर्ण

व्योम __init xen_समय_setup_guest(व्योम)
अणु
	bool xen_runstate_remote;

	xen_runstate_remote = !HYPERVISOR_vm_assist(VMASST_CMD_enable,
					VMASST_TYPE_runstate_update_flag);

	अटल_call_update(pv_steal_घड़ी, xen_steal_घड़ी);

	अटल_key_slow_inc(&paravirt_steal_enabled);
	अगर (xen_runstate_remote)
		अटल_key_slow_inc(&paravirt_steal_rq_enabled);
पूर्ण
