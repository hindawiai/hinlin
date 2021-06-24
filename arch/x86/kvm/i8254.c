<शैली गुरु>
/*
 * 8253/8254 पूर्णांकerval समयr emulation
 *
 * Copyright (c) 2003-2004 Fabrice Bellard
 * Copyright (c) 2006 Intel Corporation
 * Copyright (c) 2007 Keir Fraser, XenSource Inc
 * Copyright (c) 2008 Intel Corporation
 * Copyright 2009 Red Hat, Inc. and/or its affiliates.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Authors:
 *   Sheng Yang <sheng.yang@पूर्णांकel.com>
 *   Based on QEMU and Xen.
 */

#घोषणा pr_fmt(fmt) "pit: " fmt

#समावेश <linux/kvm_host.h>
#समावेश <linux/slab.h>

#समावेश "ioapic.h"
#समावेश "irq.h"
#समावेश "i8254.h"
#समावेश "x86.h"

#अगर_अघोषित CONFIG_X86_64
#घोषणा mod_64(x, y) ((x) - (y) * भाग64_u64(x, y))
#अन्यथा
#घोषणा mod_64(x, y) ((x) % (y))
#पूर्ण_अगर

#घोषणा RW_STATE_LSB 1
#घोषणा RW_STATE_MSB 2
#घोषणा RW_STATE_WORD0 3
#घोषणा RW_STATE_WORD1 4

अटल व्योम pit_set_gate(काष्ठा kvm_pit *pit, पूर्णांक channel, u32 val)
अणु
	काष्ठा kvm_kpit_channel_state *c = &pit->pit_state.channels[channel];

	चयन (c->mode) अणु
	शेष:
	हाल 0:
	हाल 4:
		/* XXX: just disable/enable counting */
		अवरोध;
	हाल 1:
	हाल 2:
	हाल 3:
	हाल 5:
		/* Restart counting on rising edge. */
		अगर (c->gate < val)
			c->count_load_समय = kसमय_get();
		अवरोध;
	पूर्ण

	c->gate = val;
पूर्ण

अटल पूर्णांक pit_get_gate(काष्ठा kvm_pit *pit, पूर्णांक channel)
अणु
	वापस pit->pit_state.channels[channel].gate;
पूर्ण

अटल s64 __kpit_elapsed(काष्ठा kvm_pit *pit)
अणु
	s64 elapsed;
	kसमय_प्रकार reमुख्यing;
	काष्ठा kvm_kpit_state *ps = &pit->pit_state;

	अगर (!ps->period)
		वापस 0;

	/*
	 * The Counter करोes not stop when it reaches zero. In
	 * Modes 0, 1, 4, and 5 the Counter ``wraps around'' to
	 * the highest count, either FFFF hex क्रम binary counting
	 * or 9999 क्रम BCD counting, and जारीs counting.
	 * Modes 2 and 3 are periodic; the Counter reloads
	 * itself with the initial count and जारीs counting
	 * from there.
	 */
	reमुख्यing = hrसमयr_get_reमुख्यing(&ps->समयr);
	elapsed = ps->period - kसमय_प्रकारo_ns(reमुख्यing);

	वापस elapsed;
पूर्ण

अटल s64 kpit_elapsed(काष्ठा kvm_pit *pit, काष्ठा kvm_kpit_channel_state *c,
			पूर्णांक channel)
अणु
	अगर (channel == 0)
		वापस __kpit_elapsed(pit);

	वापस kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), c->count_load_समय));
पूर्ण

अटल पूर्णांक pit_get_count(काष्ठा kvm_pit *pit, पूर्णांक channel)
अणु
	काष्ठा kvm_kpit_channel_state *c = &pit->pit_state.channels[channel];
	s64 d, t;
	पूर्णांक counter;

	t = kpit_elapsed(pit, c, channel);
	d = mul_u64_u32_भाग(t, KVM_PIT_FREQ, NSEC_PER_SEC);

	चयन (c->mode) अणु
	हाल 0:
	हाल 1:
	हाल 4:
	हाल 5:
		counter = (c->count - d) & 0xffff;
		अवरोध;
	हाल 3:
		/* XXX: may be incorrect क्रम odd counts */
		counter = c->count - (mod_64((2 * d), c->count));
		अवरोध;
	शेष:
		counter = c->count - mod_64(d, c->count);
		अवरोध;
	पूर्ण
	वापस counter;
पूर्ण

अटल पूर्णांक pit_get_out(काष्ठा kvm_pit *pit, पूर्णांक channel)
अणु
	काष्ठा kvm_kpit_channel_state *c = &pit->pit_state.channels[channel];
	s64 d, t;
	पूर्णांक out;

	t = kpit_elapsed(pit, c, channel);
	d = mul_u64_u32_भाग(t, KVM_PIT_FREQ, NSEC_PER_SEC);

	चयन (c->mode) अणु
	शेष:
	हाल 0:
		out = (d >= c->count);
		अवरोध;
	हाल 1:
		out = (d < c->count);
		अवरोध;
	हाल 2:
		out = ((mod_64(d, c->count) == 0) && (d != 0));
		अवरोध;
	हाल 3:
		out = (mod_64(d, c->count) < ((c->count + 1) >> 1));
		अवरोध;
	हाल 4:
	हाल 5:
		out = (d == c->count);
		अवरोध;
	पूर्ण

	वापस out;
पूर्ण

अटल व्योम pit_latch_count(काष्ठा kvm_pit *pit, पूर्णांक channel)
अणु
	काष्ठा kvm_kpit_channel_state *c = &pit->pit_state.channels[channel];

	अगर (!c->count_latched) अणु
		c->latched_count = pit_get_count(pit, channel);
		c->count_latched = c->rw_mode;
	पूर्ण
पूर्ण

अटल व्योम pit_latch_status(काष्ठा kvm_pit *pit, पूर्णांक channel)
अणु
	काष्ठा kvm_kpit_channel_state *c = &pit->pit_state.channels[channel];

	अगर (!c->status_latched) अणु
		/* TODO: Return शून्य COUNT (bit 6). */
		c->status = ((pit_get_out(pit, channel) << 7) |
				(c->rw_mode << 4) |
				(c->mode << 1) |
				c->bcd);
		c->status_latched = 1;
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा kvm_pit *pit_state_to_pit(काष्ठा kvm_kpit_state *ps)
अणु
	वापस container_of(ps, काष्ठा kvm_pit, pit_state);
पूर्ण

अटल व्योम kvm_pit_ack_irq(काष्ठा kvm_irq_ack_notअगरier *kian)
अणु
	काष्ठा kvm_kpit_state *ps = container_of(kian, काष्ठा kvm_kpit_state,
						 irq_ack_notअगरier);
	काष्ठा kvm_pit *pit = pit_state_to_pit(ps);

	atomic_set(&ps->irq_ack, 1);
	/* irq_ack should be set beक्रमe pending is पढ़ो.  Order accesses with
	 * inc(pending) in pit_समयr_fn and xchg(irq_ack, 0) in pit_करो_work.
	 */
	smp_mb();
	अगर (atomic_dec_अगर_positive(&ps->pending) > 0)
		kthपढ़ो_queue_work(pit->worker, &pit->expired);
पूर्ण

व्योम __kvm_migrate_pit_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_pit *pit = vcpu->kvm->arch.vpit;
	काष्ठा hrसमयr *समयr;

	अगर (!kvm_vcpu_is_bsp(vcpu) || !pit)
		वापस;

	समयr = &pit->pit_state.समयr;
	mutex_lock(&pit->pit_state.lock);
	अगर (hrसमयr_cancel(समयr))
		hrसमयr_start_expires(समयr, HRTIMER_MODE_ABS);
	mutex_unlock(&pit->pit_state.lock);
पूर्ण

अटल व्योम destroy_pit_समयr(काष्ठा kvm_pit *pit)
अणु
	hrसमयr_cancel(&pit->pit_state.समयr);
	kthपढ़ो_flush_work(&pit->expired);
पूर्ण

अटल व्योम pit_करो_work(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा kvm_pit *pit = container_of(work, काष्ठा kvm_pit, expired);
	काष्ठा kvm *kvm = pit->kvm;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;
	काष्ठा kvm_kpit_state *ps = &pit->pit_state;

	अगर (atomic_पढ़ो(&ps->reinject) && !atomic_xchg(&ps->irq_ack, 0))
		वापस;

	kvm_set_irq(kvm, pit->irq_source_id, 0, 1, false);
	kvm_set_irq(kvm, pit->irq_source_id, 0, 0, false);

	/*
	 * Provides NMI watchकरोg support via Virtual Wire mode.
	 * The route is: PIT -> LVT0 in NMI mode.
	 *
	 * Note: Our Virtual Wire implementation करोes not follow
	 * the MP specअगरication.  We propagate a PIT पूर्णांकerrupt to all
	 * VCPUs and only when LVT0 is in NMI mode.  The पूर्णांकerrupt can
	 * also be simultaneously delivered through PIC and IOAPIC.
	 */
	अगर (atomic_पढ़ो(&kvm->arch.vapics_in_nmi_mode) > 0)
		kvm_क्रम_each_vcpu(i, vcpu, kvm)
			kvm_apic_nmi_wd_deliver(vcpu);
पूर्ण

अटल क्रमागत hrसमयr_restart pit_समयr_fn(काष्ठा hrसमयr *data)
अणु
	काष्ठा kvm_kpit_state *ps = container_of(data, काष्ठा kvm_kpit_state, समयr);
	काष्ठा kvm_pit *pt = pit_state_to_pit(ps);

	अगर (atomic_पढ़ो(&ps->reinject))
		atomic_inc(&ps->pending);

	kthपढ़ो_queue_work(pt->worker, &pt->expired);

	अगर (ps->is_periodic) अणु
		hrसमयr_add_expires_ns(&ps->समयr, ps->period);
		वापस HRTIMER_RESTART;
	पूर्ण अन्यथा
		वापस HRTIMER_NORESTART;
पूर्ण

अटल अंतरभूत व्योम kvm_pit_reset_reinject(काष्ठा kvm_pit *pit)
अणु
	atomic_set(&pit->pit_state.pending, 0);
	atomic_set(&pit->pit_state.irq_ack, 1);
पूर्ण

व्योम kvm_pit_set_reinject(काष्ठा kvm_pit *pit, bool reinject)
अणु
	काष्ठा kvm_kpit_state *ps = &pit->pit_state;
	काष्ठा kvm *kvm = pit->kvm;

	अगर (atomic_पढ़ो(&ps->reinject) == reinject)
		वापस;

	/*
	 * AMD SVM AVIC accelerates EOI ग_लिखो and करोes not trap.
	 * This cause in-kernel PIT re-inject mode to fail
	 * since it checks ps->irq_ack beक्रमe kvm_set_irq()
	 * and relies on the ack notअगरier to समयly queue
	 * the pt->worker work iterm and reinject the missed tick.
	 * So, deactivate APICv when PIT is in reinject mode.
	 */
	अगर (reinject) अणु
		kvm_request_apicv_update(kvm, false,
					 APICV_INHIBIT_REASON_PIT_REINJ);
		/* The initial state is preserved जबतक ps->reinject == 0. */
		kvm_pit_reset_reinject(pit);
		kvm_रेजिस्टर_irq_ack_notअगरier(kvm, &ps->irq_ack_notअगरier);
		kvm_रेजिस्टर_irq_mask_notअगरier(kvm, 0, &pit->mask_notअगरier);
	पूर्ण अन्यथा अणु
		kvm_request_apicv_update(kvm, true,
					 APICV_INHIBIT_REASON_PIT_REINJ);
		kvm_unरेजिस्टर_irq_ack_notअगरier(kvm, &ps->irq_ack_notअगरier);
		kvm_unरेजिस्टर_irq_mask_notअगरier(kvm, 0, &pit->mask_notअगरier);
	पूर्ण

	atomic_set(&ps->reinject, reinject);
पूर्ण

अटल व्योम create_pit_समयr(काष्ठा kvm_pit *pit, u32 val, पूर्णांक is_period)
अणु
	काष्ठा kvm_kpit_state *ps = &pit->pit_state;
	काष्ठा kvm *kvm = pit->kvm;
	s64 पूर्णांकerval;

	अगर (!ioapic_in_kernel(kvm) ||
	    ps->flags & KVM_PIT_FLAGS_HPET_LEGACY)
		वापस;

	पूर्णांकerval = mul_u64_u32_भाग(val, NSEC_PER_SEC, KVM_PIT_FREQ);

	pr_debug("create pit timer, interval is %llu nsec\n", पूर्णांकerval);

	/* TODO The new value only affected after the retriggered */
	hrसमयr_cancel(&ps->समयr);
	kthपढ़ो_flush_work(&pit->expired);
	ps->period = पूर्णांकerval;
	ps->is_periodic = is_period;

	kvm_pit_reset_reinject(pit);

	/*
	 * Do not allow the guest to program periodic समयrs with small
	 * पूर्णांकerval, since the hrसमयrs are not throttled by the host
	 * scheduler.
	 */
	अगर (ps->is_periodic) अणु
		s64 min_period = min_समयr_period_us * 1000LL;

		अगर (ps->period < min_period) अणु
			pr_info_ratelimited(
			    "kvm: requested %lld ns "
			    "i8254 timer period limited to %lld ns\n",
			    ps->period, min_period);
			ps->period = min_period;
		पूर्ण
	पूर्ण

	hrसमयr_start(&ps->समयr, kसमय_add_ns(kसमय_get(), पूर्णांकerval),
		      HRTIMER_MODE_ABS);
पूर्ण

अटल व्योम pit_load_count(काष्ठा kvm_pit *pit, पूर्णांक channel, u32 val)
अणु
	काष्ठा kvm_kpit_state *ps = &pit->pit_state;

	pr_debug("load_count val is %u, channel is %d\n", val, channel);

	/*
	 * The largest possible initial count is 0; this is equivalent
	 * to 216 क्रम binary counting and 104 क्रम BCD counting.
	 */
	अगर (val == 0)
		val = 0x10000;

	ps->channels[channel].count = val;

	अगर (channel != 0) अणु
		ps->channels[channel].count_load_समय = kसमय_get();
		वापस;
	पूर्ण

	/* Two types of समयr
	 * mode 1 is one shot, mode 2 is period, otherwise del समयr */
	चयन (ps->channels[0].mode) अणु
	हाल 0:
	हाल 1:
        /* FIXME: enhance mode 4 precision */
	हाल 4:
		create_pit_समयr(pit, val, 0);
		अवरोध;
	हाल 2:
	हाल 3:
		create_pit_समयr(pit, val, 1);
		अवरोध;
	शेष:
		destroy_pit_समयr(pit);
	पूर्ण
पूर्ण

व्योम kvm_pit_load_count(काष्ठा kvm_pit *pit, पूर्णांक channel, u32 val,
		पूर्णांक hpet_legacy_start)
अणु
	u8 saved_mode;

	WARN_ON_ONCE(!mutex_is_locked(&pit->pit_state.lock));

	अगर (hpet_legacy_start) अणु
		/* save existing mode क्रम later reenablement */
		WARN_ON(channel != 0);
		saved_mode = pit->pit_state.channels[0].mode;
		pit->pit_state.channels[0].mode = 0xff; /* disable समयr */
		pit_load_count(pit, channel, val);
		pit->pit_state.channels[0].mode = saved_mode;
	पूर्ण अन्यथा अणु
		pit_load_count(pit, channel, val);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा kvm_pit *dev_to_pit(काष्ठा kvm_io_device *dev)
अणु
	वापस container_of(dev, काष्ठा kvm_pit, dev);
पूर्ण

अटल अंतरभूत काष्ठा kvm_pit *speaker_to_pit(काष्ठा kvm_io_device *dev)
अणु
	वापस container_of(dev, काष्ठा kvm_pit, speaker_dev);
पूर्ण

अटल अंतरभूत पूर्णांक pit_in_range(gpa_t addr)
अणु
	वापस ((addr >= KVM_PIT_BASE_ADDRESS) &&
		(addr < KVM_PIT_BASE_ADDRESS + KVM_PIT_MEM_LENGTH));
पूर्ण

अटल पूर्णांक pit_ioport_ग_लिखो(काष्ठा kvm_vcpu *vcpu,
				काष्ठा kvm_io_device *this,
			    gpa_t addr, पूर्णांक len, स्थिर व्योम *data)
अणु
	काष्ठा kvm_pit *pit = dev_to_pit(this);
	काष्ठा kvm_kpit_state *pit_state = &pit->pit_state;
	पूर्णांक channel, access;
	काष्ठा kvm_kpit_channel_state *s;
	u32 val = *(u32 *) data;
	अगर (!pit_in_range(addr))
		वापस -EOPNOTSUPP;

	val  &= 0xff;
	addr &= KVM_PIT_CHANNEL_MASK;

	mutex_lock(&pit_state->lock);

	अगर (val != 0)
		pr_debug("write addr is 0x%x, len is %d, val is 0x%x\n",
			 (अचिन्हित पूर्णांक)addr, len, val);

	अगर (addr == 3) अणु
		channel = val >> 6;
		अगर (channel == 3) अणु
			/* Read-Back Command. */
			क्रम (channel = 0; channel < 3; channel++) अणु
				अगर (val & (2 << channel)) अणु
					अगर (!(val & 0x20))
						pit_latch_count(pit, channel);
					अगर (!(val & 0x10))
						pit_latch_status(pit, channel);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Select Counter <channel>. */
			s = &pit_state->channels[channel];
			access = (val >> 4) & KVM_PIT_CHANNEL_MASK;
			अगर (access == 0) अणु
				pit_latch_count(pit, channel);
			पूर्ण अन्यथा अणु
				s->rw_mode = access;
				s->पढ़ो_state = access;
				s->ग_लिखो_state = access;
				s->mode = (val >> 1) & 7;
				अगर (s->mode > 5)
					s->mode -= 4;
				s->bcd = val & 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Write Count. */
		s = &pit_state->channels[addr];
		चयन (s->ग_लिखो_state) अणु
		शेष:
		हाल RW_STATE_LSB:
			pit_load_count(pit, addr, val);
			अवरोध;
		हाल RW_STATE_MSB:
			pit_load_count(pit, addr, val << 8);
			अवरोध;
		हाल RW_STATE_WORD0:
			s->ग_लिखो_latch = val;
			s->ग_लिखो_state = RW_STATE_WORD1;
			अवरोध;
		हाल RW_STATE_WORD1:
			pit_load_count(pit, addr, s->ग_लिखो_latch | (val << 8));
			s->ग_लिखो_state = RW_STATE_WORD0;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&pit_state->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक pit_ioport_पढ़ो(काष्ठा kvm_vcpu *vcpu,
			   काष्ठा kvm_io_device *this,
			   gpa_t addr, पूर्णांक len, व्योम *data)
अणु
	काष्ठा kvm_pit *pit = dev_to_pit(this);
	काष्ठा kvm_kpit_state *pit_state = &pit->pit_state;
	पूर्णांक ret, count;
	काष्ठा kvm_kpit_channel_state *s;
	अगर (!pit_in_range(addr))
		वापस -EOPNOTSUPP;

	addr &= KVM_PIT_CHANNEL_MASK;
	अगर (addr == 3)
		वापस 0;

	s = &pit_state->channels[addr];

	mutex_lock(&pit_state->lock);

	अगर (s->status_latched) अणु
		s->status_latched = 0;
		ret = s->status;
	पूर्ण अन्यथा अगर (s->count_latched) अणु
		चयन (s->count_latched) अणु
		शेष:
		हाल RW_STATE_LSB:
			ret = s->latched_count & 0xff;
			s->count_latched = 0;
			अवरोध;
		हाल RW_STATE_MSB:
			ret = s->latched_count >> 8;
			s->count_latched = 0;
			अवरोध;
		हाल RW_STATE_WORD0:
			ret = s->latched_count & 0xff;
			s->count_latched = RW_STATE_MSB;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (s->पढ़ो_state) अणु
		शेष:
		हाल RW_STATE_LSB:
			count = pit_get_count(pit, addr);
			ret = count & 0xff;
			अवरोध;
		हाल RW_STATE_MSB:
			count = pit_get_count(pit, addr);
			ret = (count >> 8) & 0xff;
			अवरोध;
		हाल RW_STATE_WORD0:
			count = pit_get_count(pit, addr);
			ret = count & 0xff;
			s->पढ़ो_state = RW_STATE_WORD1;
			अवरोध;
		हाल RW_STATE_WORD1:
			count = pit_get_count(pit, addr);
			ret = (count >> 8) & 0xff;
			s->पढ़ो_state = RW_STATE_WORD0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (len > माप(ret))
		len = माप(ret);
	स_नकल(data, (अक्षर *)&ret, len);

	mutex_unlock(&pit_state->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक speaker_ioport_ग_लिखो(काष्ठा kvm_vcpu *vcpu,
				काष्ठा kvm_io_device *this,
				gpa_t addr, पूर्णांक len, स्थिर व्योम *data)
अणु
	काष्ठा kvm_pit *pit = speaker_to_pit(this);
	काष्ठा kvm_kpit_state *pit_state = &pit->pit_state;
	u32 val = *(u32 *) data;
	अगर (addr != KVM_SPEAKER_BASE_ADDRESS)
		वापस -EOPNOTSUPP;

	mutex_lock(&pit_state->lock);
	pit_state->speaker_data_on = (val >> 1) & 1;
	pit_set_gate(pit, 2, val & 1);
	mutex_unlock(&pit_state->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक speaker_ioport_पढ़ो(काष्ठा kvm_vcpu *vcpu,
				   काष्ठा kvm_io_device *this,
				   gpa_t addr, पूर्णांक len, व्योम *data)
अणु
	काष्ठा kvm_pit *pit = speaker_to_pit(this);
	काष्ठा kvm_kpit_state *pit_state = &pit->pit_state;
	अचिन्हित पूर्णांक refresh_घड़ी;
	पूर्णांक ret;
	अगर (addr != KVM_SPEAKER_BASE_ADDRESS)
		वापस -EOPNOTSUPP;

	/* Refresh घड़ी toggles at about 15us. We approximate as 2^14ns. */
	refresh_घड़ी = ((अचिन्हित पूर्णांक)kसमय_प्रकारo_ns(kसमय_get()) >> 14) & 1;

	mutex_lock(&pit_state->lock);
	ret = ((pit_state->speaker_data_on << 1) | pit_get_gate(pit, 2) |
		(pit_get_out(pit, 2) << 5) | (refresh_घड़ी << 4));
	अगर (len > माप(ret))
		len = माप(ret);
	स_नकल(data, (अक्षर *)&ret, len);
	mutex_unlock(&pit_state->lock);
	वापस 0;
पूर्ण

अटल व्योम kvm_pit_reset(काष्ठा kvm_pit *pit)
अणु
	पूर्णांक i;
	काष्ठा kvm_kpit_channel_state *c;

	pit->pit_state.flags = 0;
	क्रम (i = 0; i < 3; i++) अणु
		c = &pit->pit_state.channels[i];
		c->mode = 0xff;
		c->gate = (i != 2);
		pit_load_count(pit, i, 0);
	पूर्ण

	kvm_pit_reset_reinject(pit);
पूर्ण

अटल व्योम pit_mask_notअगरer(काष्ठा kvm_irq_mask_notअगरier *kimn, bool mask)
अणु
	काष्ठा kvm_pit *pit = container_of(kimn, काष्ठा kvm_pit, mask_notअगरier);

	अगर (!mask)
		kvm_pit_reset_reinject(pit);
पूर्ण

अटल स्थिर काष्ठा kvm_io_device_ops pit_dev_ops = अणु
	.पढ़ो     = pit_ioport_पढ़ो,
	.ग_लिखो    = pit_ioport_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा kvm_io_device_ops speaker_dev_ops = अणु
	.पढ़ो     = speaker_ioport_पढ़ो,
	.ग_लिखो    = speaker_ioport_ग_लिखो,
पूर्ण;

काष्ठा kvm_pit *kvm_create_pit(काष्ठा kvm *kvm, u32 flags)
अणु
	काष्ठा kvm_pit *pit;
	काष्ठा kvm_kpit_state *pit_state;
	काष्ठा pid *pid;
	pid_t pid_nr;
	पूर्णांक ret;

	pit = kzalloc(माप(काष्ठा kvm_pit), GFP_KERNEL_ACCOUNT);
	अगर (!pit)
		वापस शून्य;

	pit->irq_source_id = kvm_request_irq_source_id(kvm);
	अगर (pit->irq_source_id < 0)
		जाओ fail_request;

	mutex_init(&pit->pit_state.lock);

	pid = get_pid(task_tgid(current));
	pid_nr = pid_vnr(pid);
	put_pid(pid);

	pit->worker = kthपढ़ो_create_worker(0, "kvm-pit/%d", pid_nr);
	अगर (IS_ERR(pit->worker))
		जाओ fail_kthपढ़ो;

	kthपढ़ो_init_work(&pit->expired, pit_करो_work);

	pit->kvm = kvm;

	pit_state = &pit->pit_state;
	hrसमयr_init(&pit_state->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	pit_state->समयr.function = pit_समयr_fn;

	pit_state->irq_ack_notअगरier.gsi = 0;
	pit_state->irq_ack_notअगरier.irq_acked = kvm_pit_ack_irq;
	pit->mask_notअगरier.func = pit_mask_notअगरer;

	kvm_pit_reset(pit);

	kvm_pit_set_reinject(pit, true);

	mutex_lock(&kvm->slots_lock);
	kvm_iodevice_init(&pit->dev, &pit_dev_ops);
	ret = kvm_io_bus_रेजिस्टर_dev(kvm, KVM_PIO_BUS, KVM_PIT_BASE_ADDRESS,
				      KVM_PIT_MEM_LENGTH, &pit->dev);
	अगर (ret < 0)
		जाओ fail_रेजिस्टर_pit;

	अगर (flags & KVM_PIT_SPEAKER_DUMMY) अणु
		kvm_iodevice_init(&pit->speaker_dev, &speaker_dev_ops);
		ret = kvm_io_bus_रेजिस्टर_dev(kvm, KVM_PIO_BUS,
					      KVM_SPEAKER_BASE_ADDRESS, 4,
					      &pit->speaker_dev);
		अगर (ret < 0)
			जाओ fail_रेजिस्टर_speaker;
	पूर्ण
	mutex_unlock(&kvm->slots_lock);

	वापस pit;

fail_रेजिस्टर_speaker:
	kvm_io_bus_unरेजिस्टर_dev(kvm, KVM_PIO_BUS, &pit->dev);
fail_रेजिस्टर_pit:
	mutex_unlock(&kvm->slots_lock);
	kvm_pit_set_reinject(pit, false);
	kthपढ़ो_destroy_worker(pit->worker);
fail_kthपढ़ो:
	kvm_मुक्त_irq_source_id(kvm, pit->irq_source_id);
fail_request:
	kमुक्त(pit);
	वापस शून्य;
पूर्ण

व्योम kvm_मुक्त_pit(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_pit *pit = kvm->arch.vpit;

	अगर (pit) अणु
		mutex_lock(&kvm->slots_lock);
		kvm_io_bus_unरेजिस्टर_dev(kvm, KVM_PIO_BUS, &pit->dev);
		kvm_io_bus_unरेजिस्टर_dev(kvm, KVM_PIO_BUS, &pit->speaker_dev);
		mutex_unlock(&kvm->slots_lock);
		kvm_pit_set_reinject(pit, false);
		hrसमयr_cancel(&pit->pit_state.समयr);
		kthपढ़ो_destroy_worker(pit->worker);
		kvm_मुक्त_irq_source_id(kvm, pit->irq_source_id);
		kमुक्त(pit);
	पूर्ण
पूर्ण
