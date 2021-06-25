<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xen event channels (2-level ABI)
 *
 * Jeremy Fitzhardinge <jeremy@xensource.com>, XenSource Inc, 2007
 */

#घोषणा pr_fmt(fmt) "xen:" KBUILD_MODNAME ": " fmt

#समावेश <linux/linkage.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/sync_bitops.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/hypervisor.h>

#समावेश <xen/xen.h>
#समावेश <xen/xen-ops.h>
#समावेश <xen/events.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/event_channel.h>

#समावेश "events_internal.h"

/*
 * Note माप(xen_uदीर्घ_t) can be more than माप(अचिन्हित दीर्घ). Be
 * careful to only use bitops which allow क्रम this (e.g
 * test_bit/find_first_bit and मित्रs but not __ffs) and to pass
 * BITS_PER_EVTCHN_WORD as the biपंचांगask length.
 */
#घोषणा BITS_PER_EVTCHN_WORD (माप(xen_uदीर्घ_t)*8)
/*
 * Make a biपंचांगask (i.e. अचिन्हित दीर्घ *) of a xen_uदीर्घ_t
 * array. Primarily to aव्योम दीर्घ lines (hence the terse name).
 */
#घोषणा BM(x) (अचिन्हित दीर्घ *)(x)
/* Find the first set bit in a evtchn mask */
#घोषणा EVTCHN_FIRST_BIT(w) find_first_bit(BM(&(w)), BITS_PER_EVTCHN_WORD)

#घोषणा EVTCHN_MASK_SIZE (EVTCHN_2L_NR_CHANNELS/BITS_PER_EVTCHN_WORD)

अटल DEFINE_PER_CPU(xen_uदीर्घ_t [EVTCHN_MASK_SIZE], cpu_evtchn_mask);

अटल अचिन्हित evtchn_2l_max_channels(व्योम)
अणु
	वापस EVTCHN_2L_NR_CHANNELS;
पूर्ण

अटल व्योम evtchn_2l_हटाओ(evtchn_port_t evtchn, अचिन्हित पूर्णांक cpu)
अणु
	clear_bit(evtchn, BM(per_cpu(cpu_evtchn_mask, cpu)));
पूर्ण

अटल व्योम evtchn_2l_bind_to_cpu(evtchn_port_t evtchn, अचिन्हित पूर्णांक cpu,
				  अचिन्हित पूर्णांक old_cpu)
अणु
	clear_bit(evtchn, BM(per_cpu(cpu_evtchn_mask, old_cpu)));
	set_bit(evtchn, BM(per_cpu(cpu_evtchn_mask, cpu)));
पूर्ण

अटल व्योम evtchn_2l_clear_pending(evtchn_port_t port)
अणु
	काष्ठा shared_info *s = HYPERVISOR_shared_info;
	sync_clear_bit(port, BM(&s->evtchn_pending[0]));
पूर्ण

अटल व्योम evtchn_2l_set_pending(evtchn_port_t port)
अणु
	काष्ठा shared_info *s = HYPERVISOR_shared_info;
	sync_set_bit(port, BM(&s->evtchn_pending[0]));
पूर्ण

अटल bool evtchn_2l_is_pending(evtchn_port_t port)
अणु
	काष्ठा shared_info *s = HYPERVISOR_shared_info;
	वापस sync_test_bit(port, BM(&s->evtchn_pending[0]));
पूर्ण

अटल व्योम evtchn_2l_mask(evtchn_port_t port)
अणु
	काष्ठा shared_info *s = HYPERVISOR_shared_info;
	sync_set_bit(port, BM(&s->evtchn_mask[0]));
पूर्ण

अटल व्योम evtchn_2l_unmask(evtchn_port_t port)
अणु
	काष्ठा shared_info *s = HYPERVISOR_shared_info;
	अचिन्हित पूर्णांक cpu = get_cpu();
	पूर्णांक करो_hypercall = 0, evtchn_pending = 0;

	BUG_ON(!irqs_disabled());

	smp_wmb();	/* All ग_लिखोs beक्रमe unmask must be visible. */

	अगर (unlikely((cpu != cpu_from_evtchn(port))))
		करो_hypercall = 1;
	अन्यथा अणु
		/*
		 * Need to clear the mask beक्रमe checking pending to
		 * aव्योम a race with an event becoming pending.
		 *
		 * EVTCHNOP_unmask will only trigger an upcall अगर the
		 * mask bit was set, so अगर a hypercall is needed
		 * remask the event.
		 */
		sync_clear_bit(port, BM(&s->evtchn_mask[0]));
		evtchn_pending = sync_test_bit(port, BM(&s->evtchn_pending[0]));

		अगर (unlikely(evtchn_pending && xen_hvm_करोमुख्य())) अणु
			sync_set_bit(port, BM(&s->evtchn_mask[0]));
			करो_hypercall = 1;
		पूर्ण
	पूर्ण

	/* Slow path (hypercall) अगर this is a non-local port or अगर this is
	 * an hvm करोमुख्य and an event is pending (hvm करोमुख्यs करोn't have
	 * their own implementation of irq_enable). */
	अगर (करो_hypercall) अणु
		काष्ठा evtchn_unmask unmask = अणु .port = port पूर्ण;
		(व्योम)HYPERVISOR_event_channel_op(EVTCHNOP_unmask, &unmask);
	पूर्ण अन्यथा अणु
		काष्ठा vcpu_info *vcpu_info = __this_cpu_पढ़ो(xen_vcpu);

		/*
		 * The following is basically the equivalent of
		 * 'hw_resend_irq'. Just like a real IO-APIC we 'lose
		 * the पूर्णांकerrupt edge' अगर the channel is masked.
		 */
		अगर (evtchn_pending &&
		    !sync_test_and_set_bit(port / BITS_PER_EVTCHN_WORD,
					   BM(&vcpu_info->evtchn_pending_sel)))
			vcpu_info->evtchn_upcall_pending = 1;
	पूर्ण

	put_cpu();
पूर्ण

अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, current_word_idx);
अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, current_bit_idx);

/*
 * Mask out the i least signअगरicant bits of w
 */
#घोषणा MASK_LSBS(w, i) (w & ((~((xen_uदीर्घ_t)0UL)) << i))

अटल अंतरभूत xen_uदीर्घ_t active_evtchns(अचिन्हित पूर्णांक cpu,
					 काष्ठा shared_info *sh,
					 अचिन्हित पूर्णांक idx)
अणु
	वापस sh->evtchn_pending[idx] &
		per_cpu(cpu_evtchn_mask, cpu)[idx] &
		~sh->evtchn_mask[idx];
पूर्ण

/*
 * Search the CPU's pending events biपंचांगasks.  For each one found, map
 * the event number to an irq, and feed it पूर्णांकo करो_IRQ() क्रम handling.
 *
 * Xen uses a two-level biपंचांगap to speed searching.  The first level is
 * a bitset of words which contain pending event bits.  The second
 * level is a bitset of pending events themselves.
 */
अटल व्योम evtchn_2l_handle_events(अचिन्हित cpu, काष्ठा evtchn_loop_ctrl *ctrl)
अणु
	पूर्णांक irq;
	xen_uदीर्घ_t pending_words;
	xen_uदीर्घ_t pending_bits;
	पूर्णांक start_word_idx, start_bit_idx;
	पूर्णांक word_idx, bit_idx;
	पूर्णांक i;
	काष्ठा shared_info *s = HYPERVISOR_shared_info;
	काष्ठा vcpu_info *vcpu_info = __this_cpu_पढ़ो(xen_vcpu);

	/* Timer पूर्णांकerrupt has highest priority. */
	irq = irq_from_virq(cpu, VIRQ_TIMER);
	अगर (irq != -1) अणु
		evtchn_port_t evtchn = evtchn_from_irq(irq);
		word_idx = evtchn / BITS_PER_LONG;
		bit_idx = evtchn % BITS_PER_LONG;
		अगर (active_evtchns(cpu, s, word_idx) & (1ULL << bit_idx))
			generic_handle_irq(irq);
	पूर्ण

	/*
	 * Master flag must be cleared /beक्रमe/ clearing
	 * selector flag. xchg_xen_uदीर्घ must contain an
	 * appropriate barrier.
	 */
	pending_words = xchg_xen_uदीर्घ(&vcpu_info->evtchn_pending_sel, 0);

	start_word_idx = __this_cpu_पढ़ो(current_word_idx);
	start_bit_idx = __this_cpu_पढ़ो(current_bit_idx);

	word_idx = start_word_idx;

	क्रम (i = 0; pending_words != 0; i++) अणु
		xen_uदीर्घ_t words;

		words = MASK_LSBS(pending_words, word_idx);

		/*
		 * If we masked out all events, wrap to beginning.
		 */
		अगर (words == 0) अणु
			word_idx = 0;
			bit_idx = 0;
			जारी;
		पूर्ण
		word_idx = EVTCHN_FIRST_BIT(words);

		pending_bits = active_evtchns(cpu, s, word_idx);
		bit_idx = 0; /* usually scan entire word from start */
		/*
		 * We scan the starting word in two parts.
		 *
		 * 1st समय: start in the middle, scanning the
		 * upper bits.
		 *
		 * 2nd समय: scan the whole word (not just the
		 * parts skipped in the first pass) -- अगर an
		 * event in the previously scanned bits is
		 * pending again it would just be scanned on
		 * the next loop anyway.
		 */
		अगर (word_idx == start_word_idx) अणु
			अगर (i == 0)
				bit_idx = start_bit_idx;
		पूर्ण

		करो अणु
			xen_uदीर्घ_t bits;
			evtchn_port_t port;

			bits = MASK_LSBS(pending_bits, bit_idx);

			/* If we masked out all events, move on. */
			अगर (bits == 0)
				अवरोध;

			bit_idx = EVTCHN_FIRST_BIT(bits);

			/* Process port. */
			port = (word_idx * BITS_PER_EVTCHN_WORD) + bit_idx;
			handle_irq_क्रम_port(port, ctrl);

			bit_idx = (bit_idx + 1) % BITS_PER_EVTCHN_WORD;

			/* Next caller starts at last processed + 1 */
			__this_cpu_ग_लिखो(current_word_idx,
					 bit_idx ? word_idx :
					 (word_idx+1) % BITS_PER_EVTCHN_WORD);
			__this_cpu_ग_लिखो(current_bit_idx, bit_idx);
		पूर्ण जबतक (bit_idx != 0);

		/* Scan start_l1i twice; all others once. */
		अगर ((word_idx != start_word_idx) || (i != 0))
			pending_words &= ~(1UL << word_idx);

		word_idx = (word_idx + 1) % BITS_PER_EVTCHN_WORD;
	पूर्ण
पूर्ण

irqवापस_t xen_debug_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा shared_info *sh = HYPERVISOR_shared_info;
	पूर्णांक cpu = smp_processor_id();
	xen_uदीर्घ_t *cpu_evtchn = per_cpu(cpu_evtchn_mask, cpu);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	अटल DEFINE_SPINLOCK(debug_lock);
	काष्ठा vcpu_info *v;

	spin_lock_irqsave(&debug_lock, flags);

	prपूर्णांकk("\nvcpu %d\n  ", cpu);

	क्रम_each_online_cpu(i) अणु
		पूर्णांक pending;
		v = per_cpu(xen_vcpu, i);
		pending = (get_irq_regs() && i == cpu)
			? xen_irqs_disabled(get_irq_regs())
			: v->evtchn_upcall_mask;
		prपूर्णांकk("%d: masked=%d pending=%d event_sel %0*"PRI_xen_uदीर्घ"\n  ", i,
		       pending, v->evtchn_upcall_pending,
		       (पूर्णांक)(माप(v->evtchn_pending_sel)*2),
		       v->evtchn_pending_sel);
	पूर्ण
	v = per_cpu(xen_vcpu, cpu);

	prपूर्णांकk("\npending:\n   ");
	क्रम (i = ARRAY_SIZE(sh->evtchn_pending)-1; i >= 0; i--)
		prपूर्णांकk("%0*"PRI_xen_uदीर्घ"%s",
		       (पूर्णांक)माप(sh->evtchn_pending[0])*2,
		       sh->evtchn_pending[i],
		       i % 8 == 0 ? "\n   " : " ");
	prपूर्णांकk("\nglobal mask:\n   ");
	क्रम (i = ARRAY_SIZE(sh->evtchn_mask)-1; i >= 0; i--)
		prपूर्णांकk("%0*"PRI_xen_uदीर्घ"%s",
		       (पूर्णांक)(माप(sh->evtchn_mask[0])*2),
		       sh->evtchn_mask[i],
		       i % 8 == 0 ? "\n   " : " ");

	prपूर्णांकk("\nglobally unmasked:\n   ");
	क्रम (i = ARRAY_SIZE(sh->evtchn_mask)-1; i >= 0; i--)
		prपूर्णांकk("%0*"PRI_xen_uदीर्घ"%s",
		       (पूर्णांक)(माप(sh->evtchn_mask[0])*2),
		       sh->evtchn_pending[i] & ~sh->evtchn_mask[i],
		       i % 8 == 0 ? "\n   " : " ");

	prपूर्णांकk("\nlocal cpu%d mask:\n   ", cpu);
	क्रम (i = (EVTCHN_2L_NR_CHANNELS/BITS_PER_EVTCHN_WORD)-1; i >= 0; i--)
		prपूर्णांकk("%0*"PRI_xen_uदीर्घ"%s", (पूर्णांक)(माप(cpu_evtchn[0])*2),
		       cpu_evtchn[i],
		       i % 8 == 0 ? "\n   " : " ");

	prपूर्णांकk("\nlocally unmasked:\n   ");
	क्रम (i = ARRAY_SIZE(sh->evtchn_mask)-1; i >= 0; i--) अणु
		xen_uदीर्घ_t pending = sh->evtchn_pending[i]
			& ~sh->evtchn_mask[i]
			& cpu_evtchn[i];
		prपूर्णांकk("%0*"PRI_xen_uदीर्घ"%s",
		       (पूर्णांक)(माप(sh->evtchn_mask[0])*2),
		       pending, i % 8 == 0 ? "\n   " : " ");
	पूर्ण

	prपूर्णांकk("\npending list:\n");
	क्रम (i = 0; i < EVTCHN_2L_NR_CHANNELS; i++) अणु
		अगर (sync_test_bit(i, BM(sh->evtchn_pending))) अणु
			पूर्णांक word_idx = i / BITS_PER_EVTCHN_WORD;
			prपूर्णांकk("  %d: event %d -> irq %d%s%s%s\n",
			       cpu_from_evtchn(i), i,
			       get_evtchn_to_irq(i),
			       sync_test_bit(word_idx, BM(&v->evtchn_pending_sel))
			       ? "" : " l2-clear",
			       !sync_test_bit(i, BM(sh->evtchn_mask))
			       ? "" : " globally-masked",
			       sync_test_bit(i, BM(cpu_evtchn))
			       ? "" : " locally-masked");
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&debug_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम evtchn_2l_resume(व्योम)
अणु
	पूर्णांक i;

	क्रम_each_online_cpu(i)
		स_रखो(per_cpu(cpu_evtchn_mask, i), 0, माप(xen_uदीर्घ_t) *
				EVTCHN_2L_NR_CHANNELS/BITS_PER_EVTCHN_WORD);
पूर्ण

अटल पूर्णांक evtchn_2l_percpu_deinit(अचिन्हित पूर्णांक cpu)
अणु
	स_रखो(per_cpu(cpu_evtchn_mask, cpu), 0, माप(xen_uदीर्घ_t) *
			EVTCHN_2L_NR_CHANNELS/BITS_PER_EVTCHN_WORD);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा evtchn_ops evtchn_ops_2l = अणु
	.max_channels      = evtchn_2l_max_channels,
	.nr_channels       = evtchn_2l_max_channels,
	.हटाओ            = evtchn_2l_हटाओ,
	.bind_to_cpu       = evtchn_2l_bind_to_cpu,
	.clear_pending     = evtchn_2l_clear_pending,
	.set_pending       = evtchn_2l_set_pending,
	.is_pending        = evtchn_2l_is_pending,
	.mask              = evtchn_2l_mask,
	.unmask            = evtchn_2l_unmask,
	.handle_events     = evtchn_2l_handle_events,
	.resume	           = evtchn_2l_resume,
	.percpu_deinit     = evtchn_2l_percpu_deinit,
पूर्ण;

व्योम __init xen_evtchn_2l_init(व्योम)
अणु
	pr_info("Using 2-level ABI\n");
	evtchn_ops = &evtchn_ops_2l;
पूर्ण
