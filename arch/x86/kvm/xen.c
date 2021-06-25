<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright तऊ 2019 Oracle and/or its affiliates. All rights reserved.
 * Copyright तऊ 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * KVM Xen emulation
 */

#समावेश "x86.h"
#समावेश "xen.h"
#समावेश "hyperv.h"

#समावेश <linux/kvm_host.h>
#समावेश <linux/sched/स्थिति.स>

#समावेश <trace/events/kvm.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/vcpu.h>

#समावेश "trace.h"

DEFINE_STATIC_KEY_DEFERRED_FALSE(kvm_xen_enabled, HZ);

अटल पूर्णांक kvm_xen_shared_info_init(काष्ठा kvm *kvm, gfn_t gfn)
अणु
	gpa_t gpa = gfn_to_gpa(gfn);
	पूर्णांक wc_ofs, sec_hi_ofs;
	पूर्णांक ret;
	पूर्णांक idx = srcu_पढ़ो_lock(&kvm->srcu);

	ret = kvm_gfn_to_hva_cache_init(kvm, &kvm->arch.xen.shinfo_cache,
					gpa, PAGE_SIZE);
	अगर (ret)
		जाओ out;

	kvm->arch.xen.shinfo_set = true;

	/* Paranoia checks on the 32-bit काष्ठा layout */
	BUILD_BUG_ON(दुरत्व(काष्ठा compat_shared_info, wc) != 0x900);
	BUILD_BUG_ON(दुरत्व(काष्ठा compat_shared_info, arch.wc_sec_hi) != 0x924);
	BUILD_BUG_ON(दुरत्व(काष्ठा pvघड़ी_vcpu_समय_info, version) != 0);

	/* 32-bit location by शेष */
	wc_ofs = दुरत्व(काष्ठा compat_shared_info, wc);
	sec_hi_ofs = दुरत्व(काष्ठा compat_shared_info, arch.wc_sec_hi);

#अगर_घोषित CONFIG_X86_64
	/* Paranoia checks on the 64-bit काष्ठा layout */
	BUILD_BUG_ON(दुरत्व(काष्ठा shared_info, wc) != 0xc00);
	BUILD_BUG_ON(दुरत्व(काष्ठा shared_info, wc_sec_hi) != 0xc0c);

	अगर (kvm->arch.xen.दीर्घ_mode) अणु
		wc_ofs = दुरत्व(काष्ठा shared_info, wc);
		sec_hi_ofs = दुरत्व(काष्ठा shared_info, wc_sec_hi);
	पूर्ण
#पूर्ण_अगर

	kvm_ग_लिखो_wall_घड़ी(kvm, gpa + wc_ofs, sec_hi_ofs - wc_ofs);
	kvm_make_all_cpus_request(kvm, KVM_REQ_MASTERCLOCK_UPDATE);

out:
	srcu_पढ़ो_unlock(&kvm->srcu, idx);
	वापस ret;
पूर्ण

अटल व्योम kvm_xen_update_runstate(काष्ठा kvm_vcpu *v, पूर्णांक state)
अणु
	काष्ठा kvm_vcpu_xen *vx = &v->arch.xen;
	u64 now = get_kvmघड़ी_ns(v->kvm);
	u64 delta_ns = now - vx->runstate_entry_समय;
	u64 run_delay = current->sched_info.run_delay;

	अगर (unlikely(!vx->runstate_entry_समय))
		vx->current_runstate = RUNSTATE_offline;

	/*
	 * Time रुकोing क्रम the scheduler isn't "stolen" अगर the
	 * vCPU wasn't running anyway.
	 */
	अगर (vx->current_runstate == RUNSTATE_running) अणु
		u64 steal_ns = run_delay - vx->last_steal;

		delta_ns -= steal_ns;

		vx->runstate_बार[RUNSTATE_runnable] += steal_ns;
	पूर्ण
	vx->last_steal = run_delay;

	vx->runstate_बार[vx->current_runstate] += delta_ns;
	vx->current_runstate = state;
	vx->runstate_entry_समय = now;
पूर्ण

व्योम kvm_xen_update_runstate_guest(काष्ठा kvm_vcpu *v, पूर्णांक state)
अणु
	काष्ठा kvm_vcpu_xen *vx = &v->arch.xen;
	uपूर्णांक64_t state_entry_समय;
	अचिन्हित पूर्णांक offset;

	kvm_xen_update_runstate(v, state);

	अगर (!vx->runstate_set)
		वापस;

	BUILD_BUG_ON(माप(काष्ठा compat_vcpu_runstate_info) != 0x2c);

	offset = दुरत्व(काष्ठा compat_vcpu_runstate_info, state_entry_समय);
#अगर_घोषित CONFIG_X86_64
	/*
	 * The only dअगरference is alignment of uपूर्णांक64_t in 32-bit.
	 * So the first field 'state' is accessed directly using
	 * दुरत्व() (where its offset happens to be zero), जबतक the
	 * reमुख्यing fields which are all uपूर्णांक64_t, start at 'offset'
	 * which we tweak here by adding 4.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा vcpu_runstate_info, state_entry_समय) !=
		     दुरत्व(काष्ठा compat_vcpu_runstate_info, state_entry_समय) + 4);
	BUILD_BUG_ON(दुरत्व(काष्ठा vcpu_runstate_info, समय) !=
		     दुरत्व(काष्ठा compat_vcpu_runstate_info, समय) + 4);

	अगर (v->kvm->arch.xen.दीर्घ_mode)
		offset = दुरत्व(काष्ठा vcpu_runstate_info, state_entry_समय);
#पूर्ण_अगर
	/*
	 * First ग_लिखो the updated state_entry_समय at the appropriate
	 * location determined by 'offset'.
	 */
	state_entry_समय = vx->runstate_entry_समय;
	state_entry_समय |= XEN_RUNSTATE_UPDATE;

	BUILD_BUG_ON(माप(((काष्ठा vcpu_runstate_info *)0)->state_entry_समय) !=
		     माप(state_entry_समय));
	BUILD_BUG_ON(माप(((काष्ठा compat_vcpu_runstate_info *)0)->state_entry_समय) !=
		     माप(state_entry_समय));

	अगर (kvm_ग_लिखो_guest_offset_cached(v->kvm, &v->arch.xen.runstate_cache,
					  &state_entry_समय, offset,
					  माप(state_entry_समय)))
		वापस;
	smp_wmb();

	/*
	 * Next, ग_लिखो the new runstate. This is in the *same* place
	 * क्रम 32-bit and 64-bit guests, निश्चितed here क्रम paranoia.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा vcpu_runstate_info, state) !=
		     दुरत्व(काष्ठा compat_vcpu_runstate_info, state));
	BUILD_BUG_ON(माप(((काष्ठा vcpu_runstate_info *)0)->state) !=
		     माप(vx->current_runstate));
	BUILD_BUG_ON(माप(((काष्ठा compat_vcpu_runstate_info *)0)->state) !=
		     माप(vx->current_runstate));

	अगर (kvm_ग_लिखो_guest_offset_cached(v->kvm, &v->arch.xen.runstate_cache,
					  &vx->current_runstate,
					  दुरत्व(काष्ठा vcpu_runstate_info, state),
					  माप(vx->current_runstate)))
		वापस;

	/*
	 * Write the actual runstate बार immediately after the
	 * runstate_entry_समय.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा vcpu_runstate_info, state_entry_समय) !=
		     दुरत्व(काष्ठा vcpu_runstate_info, समय) - माप(u64));
	BUILD_BUG_ON(दुरत्व(काष्ठा compat_vcpu_runstate_info, state_entry_समय) !=
		     दुरत्व(काष्ठा compat_vcpu_runstate_info, समय) - माप(u64));
	BUILD_BUG_ON(माप(((काष्ठा vcpu_runstate_info *)0)->समय) !=
		     माप(((काष्ठा compat_vcpu_runstate_info *)0)->समय));
	BUILD_BUG_ON(माप(((काष्ठा vcpu_runstate_info *)0)->समय) !=
		     माप(vx->runstate_बार));

	अगर (kvm_ग_लिखो_guest_offset_cached(v->kvm, &v->arch.xen.runstate_cache,
					  &vx->runstate_बार[0],
					  offset + माप(u64),
					  माप(vx->runstate_बार)))
		वापस;

	smp_wmb();

	/*
	 * Finally, clear the XEN_RUNSTATE_UPDATE bit in the guest's
	 * runstate_entry_समय field.
	 */

	state_entry_समय &= ~XEN_RUNSTATE_UPDATE;
	अगर (kvm_ग_लिखो_guest_offset_cached(v->kvm, &v->arch.xen.runstate_cache,
					  &state_entry_समय, offset,
					  माप(state_entry_समय)))
		वापस;
पूर्ण

पूर्णांक __kvm_xen_has_पूर्णांकerrupt(काष्ठा kvm_vcpu *v)
अणु
	u8 rc = 0;

	/*
	 * If the global upcall vector (HVMIRQ_callback_vector) is set and
	 * the vCPU's evtchn_upcall_pending flag is set, the IRQ is pending.
	 */
	काष्ठा gfn_to_hva_cache *ghc = &v->arch.xen.vcpu_info_cache;
	काष्ठा kvm_memslots *slots = kvm_memslots(v->kvm);
	अचिन्हित पूर्णांक offset = दुरत्व(काष्ठा vcpu_info, evtchn_upcall_pending);

	/* No need क्रम compat handling here */
	BUILD_BUG_ON(दुरत्व(काष्ठा vcpu_info, evtchn_upcall_pending) !=
		     दुरत्व(काष्ठा compat_vcpu_info, evtchn_upcall_pending));
	BUILD_BUG_ON(माप(rc) !=
		     माप(((काष्ठा vcpu_info *)0)->evtchn_upcall_pending));
	BUILD_BUG_ON(माप(rc) !=
		     माप(((काष्ठा compat_vcpu_info *)0)->evtchn_upcall_pending));

	/*
	 * For efficiency, this mirrors the checks क्रम using the valid
	 * cache in kvm_पढ़ो_guest_offset_cached(), but just uses
	 * __get_user() instead. And falls back to the slow path.
	 */
	अगर (likely(slots->generation == ghc->generation &&
		   !kvm_is_error_hva(ghc->hva) && ghc->memslot)) अणु
		/* Fast path */
		__get_user(rc, (u8 __user *)ghc->hva + offset);
	पूर्ण अन्यथा अणु
		/* Slow path */
		kvm_पढ़ो_guest_offset_cached(v->kvm, ghc, &rc, offset,
					     माप(rc));
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक kvm_xen_hvm_set_attr(काष्ठा kvm *kvm, काष्ठा kvm_xen_hvm_attr *data)
अणु
	पूर्णांक r = -ENOENT;

	mutex_lock(&kvm->lock);

	चयन (data->type) अणु
	हाल KVM_XEN_ATTR_TYPE_LONG_MODE:
		अगर (!IS_ENABLED(CONFIG_64BIT) && data->u.दीर्घ_mode) अणु
			r = -EINVAL;
		पूर्ण अन्यथा अणु
			kvm->arch.xen.दीर्घ_mode = !!data->u.दीर्घ_mode;
			r = 0;
		पूर्ण
		अवरोध;

	हाल KVM_XEN_ATTR_TYPE_SHARED_INFO:
		अगर (data->u.shared_info.gfn == GPA_INVALID) अणु
			kvm->arch.xen.shinfo_set = false;
			r = 0;
			अवरोध;
		पूर्ण
		r = kvm_xen_shared_info_init(kvm, data->u.shared_info.gfn);
		अवरोध;


	हाल KVM_XEN_ATTR_TYPE_UPCALL_VECTOR:
		अगर (data->u.vector && data->u.vector < 0x10)
			r = -EINVAL;
		अन्यथा अणु
			kvm->arch.xen.upcall_vector = data->u.vector;
			r = 0;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&kvm->lock);
	वापस r;
पूर्ण

पूर्णांक kvm_xen_hvm_get_attr(काष्ठा kvm *kvm, काष्ठा kvm_xen_hvm_attr *data)
अणु
	पूर्णांक r = -ENOENT;

	mutex_lock(&kvm->lock);

	चयन (data->type) अणु
	हाल KVM_XEN_ATTR_TYPE_LONG_MODE:
		data->u.दीर्घ_mode = kvm->arch.xen.दीर्घ_mode;
		r = 0;
		अवरोध;

	हाल KVM_XEN_ATTR_TYPE_SHARED_INFO:
		अगर (kvm->arch.xen.shinfo_set)
			data->u.shared_info.gfn = gpa_to_gfn(kvm->arch.xen.shinfo_cache.gpa);
		अन्यथा
			data->u.shared_info.gfn = GPA_INVALID;
		r = 0;
		अवरोध;

	हाल KVM_XEN_ATTR_TYPE_UPCALL_VECTOR:
		data->u.vector = kvm->arch.xen.upcall_vector;
		r = 0;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&kvm->lock);
	वापस r;
पूर्ण

पूर्णांक kvm_xen_vcpu_set_attr(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_xen_vcpu_attr *data)
अणु
	पूर्णांक idx, r = -ENOENT;

	mutex_lock(&vcpu->kvm->lock);
	idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

	चयन (data->type) अणु
	हाल KVM_XEN_VCPU_ATTR_TYPE_VCPU_INFO:
		/* No compat necessary here. */
		BUILD_BUG_ON(माप(काष्ठा vcpu_info) !=
			     माप(काष्ठा compat_vcpu_info));
		BUILD_BUG_ON(दुरत्व(काष्ठा vcpu_info, समय) !=
			     दुरत्व(काष्ठा compat_vcpu_info, समय));

		अगर (data->u.gpa == GPA_INVALID) अणु
			vcpu->arch.xen.vcpu_info_set = false;
			r = 0;
			अवरोध;
		पूर्ण

		r = kvm_gfn_to_hva_cache_init(vcpu->kvm,
					      &vcpu->arch.xen.vcpu_info_cache,
					      data->u.gpa,
					      माप(काष्ठा vcpu_info));
		अगर (!r) अणु
			vcpu->arch.xen.vcpu_info_set = true;
			kvm_make_request(KVM_REQ_CLOCK_UPDATE, vcpu);
		पूर्ण
		अवरोध;

	हाल KVM_XEN_VCPU_ATTR_TYPE_VCPU_TIME_INFO:
		अगर (data->u.gpa == GPA_INVALID) अणु
			vcpu->arch.xen.vcpu_समय_info_set = false;
			r = 0;
			अवरोध;
		पूर्ण

		r = kvm_gfn_to_hva_cache_init(vcpu->kvm,
					      &vcpu->arch.xen.vcpu_समय_info_cache,
					      data->u.gpa,
					      माप(काष्ठा pvघड़ी_vcpu_समय_info));
		अगर (!r) अणु
			vcpu->arch.xen.vcpu_समय_info_set = true;
			kvm_make_request(KVM_REQ_CLOCK_UPDATE, vcpu);
		पूर्ण
		अवरोध;

	हाल KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_ADDR:
		अगर (!sched_info_on()) अणु
			r = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		अगर (data->u.gpa == GPA_INVALID) अणु
			vcpu->arch.xen.runstate_set = false;
			r = 0;
			अवरोध;
		पूर्ण

		r = kvm_gfn_to_hva_cache_init(vcpu->kvm,
					      &vcpu->arch.xen.runstate_cache,
					      data->u.gpa,
					      माप(काष्ठा vcpu_runstate_info));
		अगर (!r) अणु
			vcpu->arch.xen.runstate_set = true;
		पूर्ण
		अवरोध;

	हाल KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_CURRENT:
		अगर (!sched_info_on()) अणु
			r = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		अगर (data->u.runstate.state > RUNSTATE_offline) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		kvm_xen_update_runstate(vcpu, data->u.runstate.state);
		r = 0;
		अवरोध;

	हाल KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_DATA:
		अगर (!sched_info_on()) अणु
			r = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		अगर (data->u.runstate.state > RUNSTATE_offline) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (data->u.runstate.state_entry_समय !=
		    (data->u.runstate.समय_running +
		     data->u.runstate.समय_runnable +
		     data->u.runstate.समय_blocked +
		     data->u.runstate.समय_offline)) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (get_kvmघड़ी_ns(vcpu->kvm) <
		    data->u.runstate.state_entry_समय) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		vcpu->arch.xen.current_runstate = data->u.runstate.state;
		vcpu->arch.xen.runstate_entry_समय =
			data->u.runstate.state_entry_समय;
		vcpu->arch.xen.runstate_बार[RUNSTATE_running] =
			data->u.runstate.समय_running;
		vcpu->arch.xen.runstate_बार[RUNSTATE_runnable] =
			data->u.runstate.समय_runnable;
		vcpu->arch.xen.runstate_बार[RUNSTATE_blocked] =
			data->u.runstate.समय_blocked;
		vcpu->arch.xen.runstate_बार[RUNSTATE_offline] =
			data->u.runstate.समय_offline;
		vcpu->arch.xen.last_steal = current->sched_info.run_delay;
		r = 0;
		अवरोध;

	हाल KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_ADJUST:
		अगर (!sched_info_on()) अणु
			r = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		अगर (data->u.runstate.state > RUNSTATE_offline &&
		    data->u.runstate.state != (u64)-1) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण
		/* The adjusपंचांगent must add up */
		अगर (data->u.runstate.state_entry_समय !=
		    (data->u.runstate.समय_running +
		     data->u.runstate.समय_runnable +
		     data->u.runstate.समय_blocked +
		     data->u.runstate.समय_offline)) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (get_kvmघड़ी_ns(vcpu->kvm) <
		    (vcpu->arch.xen.runstate_entry_समय +
		     data->u.runstate.state_entry_समय)) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		vcpu->arch.xen.runstate_entry_समय +=
			data->u.runstate.state_entry_समय;
		vcpu->arch.xen.runstate_बार[RUNSTATE_running] +=
			data->u.runstate.समय_running;
		vcpu->arch.xen.runstate_बार[RUNSTATE_runnable] +=
			data->u.runstate.समय_runnable;
		vcpu->arch.xen.runstate_बार[RUNSTATE_blocked] +=
			data->u.runstate.समय_blocked;
		vcpu->arch.xen.runstate_बार[RUNSTATE_offline] +=
			data->u.runstate.समय_offline;

		अगर (data->u.runstate.state <= RUNSTATE_offline)
			kvm_xen_update_runstate(vcpu, data->u.runstate.state);
		r = 0;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
	mutex_unlock(&vcpu->kvm->lock);
	वापस r;
पूर्ण

पूर्णांक kvm_xen_vcpu_get_attr(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_xen_vcpu_attr *data)
अणु
	पूर्णांक r = -ENOENT;

	mutex_lock(&vcpu->kvm->lock);

	चयन (data->type) अणु
	हाल KVM_XEN_VCPU_ATTR_TYPE_VCPU_INFO:
		अगर (vcpu->arch.xen.vcpu_info_set)
			data->u.gpa = vcpu->arch.xen.vcpu_info_cache.gpa;
		अन्यथा
			data->u.gpa = GPA_INVALID;
		r = 0;
		अवरोध;

	हाल KVM_XEN_VCPU_ATTR_TYPE_VCPU_TIME_INFO:
		अगर (vcpu->arch.xen.vcpu_समय_info_set)
			data->u.gpa = vcpu->arch.xen.vcpu_समय_info_cache.gpa;
		अन्यथा
			data->u.gpa = GPA_INVALID;
		r = 0;
		अवरोध;

	हाल KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_ADDR:
		अगर (!sched_info_on()) अणु
			r = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		अगर (vcpu->arch.xen.runstate_set) अणु
			data->u.gpa = vcpu->arch.xen.runstate_cache.gpa;
			r = 0;
		पूर्ण
		अवरोध;

	हाल KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_CURRENT:
		अगर (!sched_info_on()) अणु
			r = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		data->u.runstate.state = vcpu->arch.xen.current_runstate;
		r = 0;
		अवरोध;

	हाल KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_DATA:
		अगर (!sched_info_on()) अणु
			r = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		data->u.runstate.state = vcpu->arch.xen.current_runstate;
		data->u.runstate.state_entry_समय =
			vcpu->arch.xen.runstate_entry_समय;
		data->u.runstate.समय_running =
			vcpu->arch.xen.runstate_बार[RUNSTATE_running];
		data->u.runstate.समय_runnable =
			vcpu->arch.xen.runstate_बार[RUNSTATE_runnable];
		data->u.runstate.समय_blocked =
			vcpu->arch.xen.runstate_बार[RUNSTATE_blocked];
		data->u.runstate.समय_offline =
			vcpu->arch.xen.runstate_बार[RUNSTATE_offline];
		r = 0;
		अवरोध;

	हाल KVM_XEN_VCPU_ATTR_TYPE_RUNSTATE_ADJUST:
		r = -EINVAL;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&vcpu->kvm->lock);
	वापस r;
पूर्ण

पूर्णांक kvm_xen_ग_लिखो_hypercall_page(काष्ठा kvm_vcpu *vcpu, u64 data)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	u32 page_num = data & ~PAGE_MASK;
	u64 page_addr = data & PAGE_MASK;
	bool lm = is_दीर्घ_mode(vcpu);

	/* Latch दीर्घ_mode क्रम shared_info pages etc. */
	vcpu->kvm->arch.xen.दीर्घ_mode = lm;

	/*
	 * If Xen hypercall पूर्णांकercept is enabled, fill the hypercall
	 * page with VMCALL/VMMCALL inकाष्ठाions since that's what
	 * we catch. Else the VMM has provided the hypercall pages
	 * with inकाष्ठाions of its own choosing, so use those.
	 */
	अगर (kvm_xen_hypercall_enabled(kvm)) अणु
		u8 inकाष्ठाions[32];
		पूर्णांक i;

		अगर (page_num)
			वापस 1;

		/* mov imm32, %eax */
		inकाष्ठाions[0] = 0xb8;

		/* vmcall / vmmcall */
		kvm_x86_ops.patch_hypercall(vcpu, inकाष्ठाions + 5);

		/* ret */
		inकाष्ठाions[8] = 0xc3;

		/* पूर्णांक3 to pad */
		स_रखो(inकाष्ठाions + 9, 0xcc, माप(inकाष्ठाions) - 9);

		क्रम (i = 0; i < PAGE_SIZE / माप(inकाष्ठाions); i++) अणु
			*(u32 *)&inकाष्ठाions[1] = i;
			अगर (kvm_vcpu_ग_लिखो_guest(vcpu,
						 page_addr + (i * माप(inकाष्ठाions)),
						 inकाष्ठाions, माप(inकाष्ठाions)))
				वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Note, truncation is a non-issue as 'lm' is guaranteed to be
		 * false क्रम a 32-bit kernel, i.e. when hva_t is only 4 bytes.
		 */
		hva_t blob_addr = lm ? kvm->arch.xen_hvm_config.blob_addr_64
				     : kvm->arch.xen_hvm_config.blob_addr_32;
		u8 blob_size = lm ? kvm->arch.xen_hvm_config.blob_size_64
				  : kvm->arch.xen_hvm_config.blob_size_32;
		u8 *page;

		अगर (page_num >= blob_size)
			वापस 1;

		blob_addr += page_num * PAGE_SIZE;

		page = memdup_user((u8 __user *)blob_addr, PAGE_SIZE);
		अगर (IS_ERR(page))
			वापस PTR_ERR(page);

		अगर (kvm_vcpu_ग_लिखो_guest(vcpu, page_addr, page, PAGE_SIZE)) अणु
			kमुक्त(page);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक kvm_xen_hvm_config(काष्ठा kvm *kvm, काष्ठा kvm_xen_hvm_config *xhc)
अणु
	अगर (xhc->flags & ~KVM_XEN_HVM_CONFIG_INTERCEPT_HCALL)
		वापस -EINVAL;

	/*
	 * With hypercall पूर्णांकerception the kernel generates its own
	 * hypercall page so it must not be provided.
	 */
	अगर ((xhc->flags & KVM_XEN_HVM_CONFIG_INTERCEPT_HCALL) &&
	    (xhc->blob_addr_32 || xhc->blob_addr_64 ||
	     xhc->blob_size_32 || xhc->blob_size_64))
		वापस -EINVAL;

	mutex_lock(&kvm->lock);

	अगर (xhc->msr && !kvm->arch.xen_hvm_config.msr)
		अटल_branch_inc(&kvm_xen_enabled.key);
	अन्यथा अगर (!xhc->msr && kvm->arch.xen_hvm_config.msr)
		अटल_branch_slow_dec_deferred(&kvm_xen_enabled);

	स_नकल(&kvm->arch.xen_hvm_config, xhc, माप(*xhc));

	mutex_unlock(&kvm->lock);
	वापस 0;
पूर्ण

व्योम kvm_xen_destroy_vm(काष्ठा kvm *kvm)
अणु
	अगर (kvm->arch.xen_hvm_config.msr)
		अटल_branch_slow_dec_deferred(&kvm_xen_enabled);
पूर्ण

अटल पूर्णांक kvm_xen_hypercall_set_result(काष्ठा kvm_vcpu *vcpu, u64 result)
अणु
	kvm_rax_ग_लिखो(vcpu, result);
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण

अटल पूर्णांक kvm_xen_hypercall_complete_userspace(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;

	अगर (unlikely(!kvm_is_linear_rip(vcpu, vcpu->arch.xen.hypercall_rip)))
		वापस 1;

	वापस kvm_xen_hypercall_set_result(vcpu, run->xen.u.hcall.result);
पूर्ण

पूर्णांक kvm_xen_hypercall(काष्ठा kvm_vcpu *vcpu)
अणु
	bool दीर्घmode;
	u64 input, params[6];

	input = (u64)kvm_रेजिस्टर_पढ़ो(vcpu, VCPU_REGS_RAX);

	/* Hyper-V hypercalls get bit 31 set in EAX */
	अगर ((input & 0x80000000) &&
	    kvm_hv_hypercall_enabled(vcpu))
		वापस kvm_hv_hypercall(vcpu);

	दीर्घmode = is_64_bit_mode(vcpu);
	अगर (!दीर्घmode) अणु
		params[0] = (u32)kvm_rbx_पढ़ो(vcpu);
		params[1] = (u32)kvm_rcx_पढ़ो(vcpu);
		params[2] = (u32)kvm_rdx_पढ़ो(vcpu);
		params[3] = (u32)kvm_rsi_पढ़ो(vcpu);
		params[4] = (u32)kvm_rdi_पढ़ो(vcpu);
		params[5] = (u32)kvm_rbp_पढ़ो(vcpu);
	पूर्ण
#अगर_घोषित CONFIG_X86_64
	अन्यथा अणु
		params[0] = (u64)kvm_rdi_पढ़ो(vcpu);
		params[1] = (u64)kvm_rsi_पढ़ो(vcpu);
		params[2] = (u64)kvm_rdx_पढ़ो(vcpu);
		params[3] = (u64)kvm_r10_पढ़ो(vcpu);
		params[4] = (u64)kvm_r8_पढ़ो(vcpu);
		params[5] = (u64)kvm_r9_पढ़ो(vcpu);
	पूर्ण
#पूर्ण_अगर
	trace_kvm_xen_hypercall(input, params[0], params[1], params[2],
				params[3], params[4], params[5]);

	vcpu->run->निकास_reason = KVM_EXIT_XEN;
	vcpu->run->xen.type = KVM_EXIT_XEN_HCALL;
	vcpu->run->xen.u.hcall.दीर्घmode = दीर्घmode;
	vcpu->run->xen.u.hcall.cpl = kvm_x86_ops.get_cpl(vcpu);
	vcpu->run->xen.u.hcall.input = input;
	vcpu->run->xen.u.hcall.params[0] = params[0];
	vcpu->run->xen.u.hcall.params[1] = params[1];
	vcpu->run->xen.u.hcall.params[2] = params[2];
	vcpu->run->xen.u.hcall.params[3] = params[3];
	vcpu->run->xen.u.hcall.params[4] = params[4];
	vcpu->run->xen.u.hcall.params[5] = params[5];
	vcpu->arch.xen.hypercall_rip = kvm_get_linear_rip(vcpu);
	vcpu->arch.complete_userspace_io =
		kvm_xen_hypercall_complete_userspace;

	वापस 0;
पूर्ण
