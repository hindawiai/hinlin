<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/i8253.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/smp.h>
#समावेश <linux/समय.स>
#समावेश <linux/घड़ीchips.h>

#समावेश <यंत्र/sni.h>
#समावेश <यंत्र/समय.स>

#घोषणा SNI_CLOCK_TICK_RATE	3686400
#घोषणा SNI_COUNTER2_DIV	64
#घोषणा SNI_COUNTER0_DIV	((SNI_CLOCK_TICK_RATE / SNI_COUNTER2_DIV) / HZ)

अटल पूर्णांक a20r_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	*(अस्थिर u8 *)(A20R_PT_CLOCK_BASE + 12) = 0x34;
	wmb();
	*(अस्थिर u8 *)(A20R_PT_CLOCK_BASE + 0) = SNI_COUNTER0_DIV;
	wmb();
	*(अस्थिर u8 *)(A20R_PT_CLOCK_BASE + 0) = SNI_COUNTER0_DIV >> 8;
	wmb();

	*(अस्थिर u8 *)(A20R_PT_CLOCK_BASE + 12) = 0xb4;
	wmb();
	*(अस्थिर u8 *)(A20R_PT_CLOCK_BASE + 8) = SNI_COUNTER2_DIV;
	wmb();
	*(अस्थिर u8 *)(A20R_PT_CLOCK_BASE + 8) = SNI_COUNTER2_DIV >> 8;
	wmb();
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device a20r_घड़ीevent_device = अणु
	.name			= "a20r-timer",
	.features		= CLOCK_EVT_FEAT_PERIODIC,

	/* .mult, .shअगरt, .max_delta_ns and .min_delta_ns left uninitialized */

	.rating			= 300,
	.irq			= SNI_A20R_IRQ_TIMER,
	.set_state_periodic	= a20r_set_periodic,
पूर्ण;

अटल irqवापस_t a20r_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *cd = dev_id;

	*(अस्थिर u8 *)A20R_PT_TIM0_ACK = 0;
	wmb();

	cd->event_handler(cd);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * a20r platक्रमm uses 2 counters to भागide the input frequency.
 * Counter 2 output is connected to Counter 0 & 1 input.
 */
अटल व्योम __init sni_a20r_समयr_setup(व्योम)
अणु
	काष्ठा घड़ी_event_device *cd = &a20r_घड़ीevent_device;
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	cd->cpumask		= cpumask_of(cpu);
	घड़ीevents_रेजिस्टर_device(cd);
	अगर (request_irq(SNI_A20R_IRQ_TIMER, a20r_पूर्णांकerrupt,
			IRQF_PERCPU | IRQF_TIMER, "a20r-timer", cd))
		pr_err("Failed to register a20r-timer interrupt\n");
पूर्ण

#घोषणा SNI_8254_TICK_RATE	  1193182UL

#घोषणा SNI_8254_TCSAMP_COUNTER	  ((SNI_8254_TICK_RATE / HZ) + 255)

अटल __init अचिन्हित दीर्घ करोsample(व्योम)
अणु
	u32 ct0, ct1;
	अस्थिर u8 msb;

	/* Start the counter. */
	outb_p(0x34, 0x43);
	outb_p(SNI_8254_TCSAMP_COUNTER & 0xff, 0x40);
	outb(SNI_8254_TCSAMP_COUNTER >> 8, 0x40);

	/* Get initial counter invariant */
	ct0 = पढ़ो_c0_count();

	/* Latch and spin until top byte of counter0 is zero */
	करो अणु
		outb(0x00, 0x43);
		(व्योम) inb(0x40);
		msb = inb(0x40);
		ct1 = पढ़ो_c0_count();
	पूर्ण जबतक (msb);

	/* Stop the counter. */
	outb(0x38, 0x43);
	/*
	 * Return the dअगरference, this is how far the r4k counter increments
	 * क्रम every 1/HZ seconds. We round off the nearest 1 MHz of master
	 * घड़ी (= 1000000 / HZ / 2).
	 */
	/*वापस (ct1 - ct0 + (500000/HZ/2)) / (500000/HZ) * (500000/HZ);*/
	वापस (ct1 - ct0) / (500000/HZ) * (500000/HZ);
पूर्ण

/*
 * Here we need to calibrate the cycle counter to at least be बंद.
 */
व्योम __init plat_समय_init(व्योम)
अणु
	अचिन्हित दीर्घ r4k_ticks[3];
	अचिन्हित दीर्घ r4k_tick;

	/*
	 * Figure out the r4k offset, the algorithm is very simple and works in
	 * _all_ हालs as दीर्घ as the 8254 counter रेजिस्टर itself works ok (as
	 * an पूर्णांकerrupt driving समयr it करोes not because of bug, this is why
	 * we are using the onchip r4k counter/compare रेजिस्टर to serve this
	 * purpose, but क्रम r4k_offset calculation it will work ok क्रम us).
	 * There are other very complicated ways of perक्रमming this calculation
	 * but this one works just fine so I am not going to futz around. ;-)
	 */
	prपूर्णांकk(KERN_INFO "Calibrating system timer... ");
	करोsample();	/* Prime cache. */
	करोsample();	/* Prime cache. */
	/* Zero is NOT an option. */
	करो अणु
		r4k_ticks[0] = करोsample();
	पूर्ण जबतक (!r4k_ticks[0]);
	करो अणु
		r4k_ticks[1] = करोsample();
	पूर्ण जबतक (!r4k_ticks[1]);

	अगर (r4k_ticks[0] != r4k_ticks[1]) अणु
		prपूर्णांकk("warning: timer counts differ, retrying... ");
		r4k_ticks[2] = करोsample();
		अगर (r4k_ticks[2] == r4k_ticks[0]
		    || r4k_ticks[2] == r4k_ticks[1])
			r4k_tick = r4k_ticks[2];
		अन्यथा अणु
			prपूर्णांकk("disagreement, using average... ");
			r4k_tick = (r4k_ticks[0] + r4k_ticks[1]
				   + r4k_ticks[2]) / 3;
		पूर्ण
	पूर्ण अन्यथा
		r4k_tick = r4k_ticks[0];

	prपूर्णांकk("%d [%d.%04d MHz CPU]\n", (पूर्णांक) r4k_tick,
		(पूर्णांक) (r4k_tick / (500000 / HZ)),
		(पूर्णांक) (r4k_tick % (500000 / HZ)));

	mips_hpt_frequency = r4k_tick * HZ;

	चयन (sni_brd_type) अणु
	हाल SNI_BRD_10:
	हाल SNI_BRD_10NEW:
	हाल SNI_BRD_TOWER_OASIC:
	हाल SNI_BRD_MINITOWER:
		sni_a20r_समयr_setup();
		अवरोध;
	पूर्ण
	setup_pit_समयr();
पूर्ण
