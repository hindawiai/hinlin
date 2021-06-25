<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2015 Numascale AS. All rights reserved.
 */

#समावेश <linux/घड़ीchips.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/numachip/numachip.h>
#समावेश <यंत्र/numachip/numachip_csr.h>

अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, numachip2_ced);

अटल cycles_t numachip2_समयr_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस numachip2_पढ़ो64_lcsr(NUMACHIP2_TIMER_NOW);
पूर्ण

अटल काष्ठा घड़ीsource numachip2_घड़ीsource = अणु
	.name            = "numachip2",
	.rating          = 295,
	.पढ़ो            = numachip2_समयr_पढ़ो,
	.mask            = CLOCKSOURCE_MASK(64),
	.flags           = CLOCK_SOURCE_IS_CONTINUOUS,
	.mult            = 1,
	.shअगरt           = 0,
पूर्ण;

अटल पूर्णांक numachip2_set_next_event(अचिन्हित दीर्घ delta, काष्ठा घड़ी_event_device *ced)
अणु
	numachip2_ग_लिखो64_lcsr(NUMACHIP2_TIMER_DEADLINE + numachip2_समयr(),
		delta);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा घड़ी_event_device numachip2_घड़ीevent __initस्थिर = अणु
	.name            = "numachip2",
	.rating          = 400,
	.set_next_event  = numachip2_set_next_event,
	.features        = CLOCK_EVT_FEAT_ONESHOT,
	.mult            = 1,
	.shअगरt           = 0,
	.min_delta_ns    = 1250,
	.min_delta_ticks = 1250,
	.max_delta_ns    = दीर्घ_उच्च,
	.max_delta_ticks = दीर्घ_उच्च,
पूर्ण;

अटल व्योम numachip_समयr_पूर्णांकerrupt(व्योम)
अणु
	काष्ठा घड़ी_event_device *ced = this_cpu_ptr(&numachip2_ced);

	ced->event_handler(ced);
पूर्ण

अटल __init व्योम numachip_समयr_each(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित local_apicid = __this_cpu_पढ़ो(x86_cpu_to_apicid) & 0xff;
	काष्ठा घड़ी_event_device *ced = this_cpu_ptr(&numachip2_ced);

	/* Setup IPI vector to local core and relative timing mode */
	numachip2_ग_लिखो64_lcsr(NUMACHIP2_TIMER_INT + numachip2_समयr(),
		(3 << 22) | (X86_PLATFORM_IPI_VECTOR << 14) |
		(local_apicid << 6));

	*ced = numachip2_घड़ीevent;
	ced->cpumask = cpumask_of(smp_processor_id());
	घड़ीevents_रेजिस्टर_device(ced);
पूर्ण

अटल पूर्णांक __init numachip_समयr_init(व्योम)
अणु
	अगर (numachip_प्रणाली != 2)
		वापस -ENODEV;

	/* Reset समयr */
	numachip2_ग_लिखो64_lcsr(NUMACHIP2_TIMER_RESET, 0);
	घड़ीsource_रेजिस्टर_hz(&numachip2_घड़ीsource, NSEC_PER_SEC);

	/* Setup per-cpu घड़ीevents */
	x86_platक्रमm_ipi_callback = numachip_समयr_पूर्णांकerrupt;
	schedule_on_each_cpu(&numachip_समयr_each);

	वापस 0;
पूर्ण

arch_initcall(numachip_समयr_init);
