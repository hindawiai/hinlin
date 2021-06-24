<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * i8253 PIT घड़ीsource
 */
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयx.h>
#समावेश <linux/module.h>
#समावेश <linux/i8253.h>
#समावेश <linux/smp.h>

/*
 * Protects access to I/O ports
 *
 * 0040-0043 : समयr0, i8253 / i8254
 * 0061-0061 : NMI Control Register which contains two speaker control bits.
 */
DEFINE_RAW_SPINLOCK(i8253_lock);
EXPORT_SYMBOL(i8253_lock);

/*
 * Handle PIT quirk in pit_shutकरोwn() where zeroing the counter रेजिस्टर
 * restarts the PIT, negating the shutकरोwn. On platक्रमms with the quirk,
 * platक्रमm specअगरic code can set this to false.
 */
bool i8253_clear_counter_on_shutकरोwn __ro_after_init = true;

#अगर_घोषित CONFIG_CLKSRC_I8253
/*
 * Since the PIT overflows every tick, its not very useful
 * to just पढ़ो by itself. So use jअगरfies to emulate a मुक्त
 * running counter:
 */
अटल u64 i8253_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	अटल पूर्णांक old_count;
	अटल u32 old_jअगरs;
	अचिन्हित दीर्घ flags;
	पूर्णांक count;
	u32 jअगरs;

	raw_spin_lock_irqsave(&i8253_lock, flags);
	/*
	 * Although our caller may have the पढ़ो side of jअगरfies_lock,
	 * this is now a seqlock, and we are cheating in this routine
	 * by having side effects on state that we cannot unकरो अगर
	 * there is a collision on the seqlock and our caller has to
	 * retry.  (Namely, old_jअगरs and old_count.)  So we must treat
	 * jअगरfies as अस्थिर despite the lock.  We पढ़ो jअगरfies
	 * beक्रमe latching the समयr count to guarantee that although
	 * the jअगरfies value might be older than the count (that is,
	 * the counter may underflow between the last poपूर्णांक where
	 * jअगरfies was incremented and the poपूर्णांक where we latch the
	 * count), it cannot be newer.
	 */
	jअगरs = jअगरfies;
	outb_p(0x00, PIT_MODE);	/* latch the count ASAP */
	count = inb_p(PIT_CH0);	/* पढ़ो the latched count */
	count |= inb_p(PIT_CH0) << 8;

	/* VIA686a test code... reset the latch अगर count > max + 1 */
	अगर (count > PIT_LATCH) अणु
		outb_p(0x34, PIT_MODE);
		outb_p(PIT_LATCH & 0xff, PIT_CH0);
		outb_p(PIT_LATCH >> 8, PIT_CH0);
		count = PIT_LATCH - 1;
	पूर्ण

	/*
	 * It's possible क्रम count to appear to go the wrong way क्रम a
	 * couple of reasons:
	 *
	 *  1. The समयr counter underflows, but we haven't handled the
	 *     resulting पूर्णांकerrupt and incremented jअगरfies yet.
	 *  2. Hardware problem with the समयr, not giving us continuous समय,
	 *     the counter करोes small "jumps" upwards on some Pentium प्रणालीs,
	 *     (see c't 95/10 page 335 क्रम Neptun bug.)
	 *
	 * Previous attempts to handle these हालs पूर्णांकelligently were
	 * buggy, so we just करो the simple thing now.
	 */
	अगर (count > old_count && jअगरs == old_jअगरs)
		count = old_count;

	old_count = count;
	old_jअगरs = jअगरs;

	raw_spin_unlock_irqrestore(&i8253_lock, flags);

	count = (PIT_LATCH - 1) - count;

	वापस (u64)(jअगरs * PIT_LATCH) + count;
पूर्ण

अटल काष्ठा घड़ीsource i8253_cs = अणु
	.name		= "pit",
	.rating		= 110,
	.पढ़ो		= i8253_पढ़ो,
	.mask		= CLOCKSOURCE_MASK(32),
पूर्ण;

पूर्णांक __init घड़ीsource_i8253_init(व्योम)
अणु
	वापस घड़ीsource_रेजिस्टर_hz(&i8253_cs, PIT_TICK_RATE);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CLKEVT_I8253
अटल पूर्णांक pit_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	अगर (!घड़ीevent_state_oneshot(evt) && !घड़ीevent_state_periodic(evt))
		वापस 0;

	raw_spin_lock(&i8253_lock);

	outb_p(0x30, PIT_MODE);

	अगर (i8253_clear_counter_on_shutकरोwn) अणु
		outb_p(0, PIT_CH0);
		outb_p(0, PIT_CH0);
	पूर्ण

	raw_spin_unlock(&i8253_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक pit_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	raw_spin_lock(&i8253_lock);
	outb_p(0x38, PIT_MODE);
	raw_spin_unlock(&i8253_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक pit_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	raw_spin_lock(&i8253_lock);

	/* binary, mode 2, LSB/MSB, ch 0 */
	outb_p(0x34, PIT_MODE);
	outb_p(PIT_LATCH & 0xff, PIT_CH0);	/* LSB */
	outb_p(PIT_LATCH >> 8, PIT_CH0);	/* MSB */

	raw_spin_unlock(&i8253_lock);
	वापस 0;
पूर्ण

/*
 * Program the next event in oneshot mode
 *
 * Delta is given in PIT ticks
 */
अटल पूर्णांक pit_next_event(अचिन्हित दीर्घ delta, काष्ठा घड़ी_event_device *evt)
अणु
	raw_spin_lock(&i8253_lock);
	outb_p(delta & 0xff , PIT_CH0);	/* LSB */
	outb_p(delta >> 8 , PIT_CH0);		/* MSB */
	raw_spin_unlock(&i8253_lock);

	वापस 0;
पूर्ण

/*
 * On UP the PIT can serve all of the possible समयr functions. On SMP प्रणालीs
 * it can be solely used क्रम the global tick.
 */
काष्ठा घड़ी_event_device i8253_घड़ीevent = अणु
	.name			= "pit",
	.features		= CLOCK_EVT_FEAT_PERIODIC,
	.set_state_shutकरोwn	= pit_shutकरोwn,
	.set_state_periodic	= pit_set_periodic,
	.set_next_event		= pit_next_event,
पूर्ण;

/*
 * Initialize the conversion factor and the min/max deltas of the घड़ी event
 * काष्ठाure and रेजिस्टर the घड़ी event source with the framework.
 */
व्योम __init घड़ीevent_i8253_init(bool oneshot)
अणु
	अगर (oneshot) अणु
		i8253_घड़ीevent.features |= CLOCK_EVT_FEAT_ONESHOT;
		i8253_घड़ीevent.set_state_oneshot = pit_set_oneshot;
	पूर्ण
	/*
	 * Start pit with the boot cpu mask. x86 might make it global
	 * when it is used as broadcast device later.
	 */
	i8253_घड़ीevent.cpumask = cpumask_of(smp_processor_id());

	घड़ीevents_config_and_रेजिस्टर(&i8253_घड़ीevent, PIT_TICK_RATE,
					0xF, 0x7FFF);
पूर्ण
#पूर्ण_अगर
