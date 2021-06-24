<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/entry-kvm.h>
#समावेश <linux/kvm_host.h>

अटल पूर्णांक xfer_to_guest_mode_work(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ ti_work)
अणु
	करो अणु
		पूर्णांक ret;

		अगर (ti_work & _TIF_NOTIFY_SIGNAL)
			tracehook_notअगरy_संकेत();

		अगर (ti_work & _TIF_SIGPENDING) अणु
			kvm_handle_संकेत_निकास(vcpu);
			वापस -EINTR;
		पूर्ण

		अगर (ti_work & _TIF_NEED_RESCHED)
			schedule();

		अगर (ti_work & _TIF_NOTIFY_RESUME)
			tracehook_notअगरy_resume(शून्य);

		ret = arch_xfer_to_guest_mode_handle_work(vcpu, ti_work);
		अगर (ret)
			वापस ret;

		ti_work = READ_ONCE(current_thपढ़ो_info()->flags);
	पूर्ण जबतक (ti_work & XFER_TO_GUEST_MODE_WORK || need_resched());
	वापस 0;
पूर्ण

पूर्णांक xfer_to_guest_mode_handle_work(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ ti_work;

	/*
	 * This is invoked from the outer guest loop with पूर्णांकerrupts and
	 * preemption enabled.
	 *
	 * KVM invokes xfer_to_guest_mode_work_pending() with पूर्णांकerrupts
	 * disabled in the inner loop beक्रमe going पूर्णांकo guest mode. No need
	 * to disable पूर्णांकerrupts here.
	 */
	ti_work = READ_ONCE(current_thपढ़ो_info()->flags);
	अगर (!(ti_work & XFER_TO_GUEST_MODE_WORK))
		वापस 0;

	वापस xfer_to_guest_mode_work(vcpu, ti_work);
पूर्ण
EXPORT_SYMBOL_GPL(xfer_to_guest_mode_handle_work);
