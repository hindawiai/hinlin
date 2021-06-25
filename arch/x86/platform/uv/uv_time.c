<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SGI RTC घड़ी/समयr routines.
 *
 *  (C) Copyright 2020 Hewlett Packard Enterprise Development LP
 *  Copyright (c) 2009-2013 Silicon Graphics, Inc.  All Rights Reserved.
 *  Copyright (c) Dimitri Sivanich
 */
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/uv/uv_mmrs.h>
#समावेश <यंत्र/uv/uv_hub.h>
#समावेश <यंत्र/uv/मूलप्रण.स>
#समावेश <यंत्र/uv/uv.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/cpu.h>

#घोषणा RTC_NAME		"sgi_rtc"

अटल u64 uv_पढ़ो_rtc(काष्ठा घड़ीsource *cs);
अटल पूर्णांक uv_rtc_next_event(अचिन्हित दीर्घ, काष्ठा घड़ी_event_device *);
अटल पूर्णांक uv_rtc_shutकरोwn(काष्ठा घड़ी_event_device *evt);

अटल काष्ठा घड़ीsource घड़ीsource_uv = अणु
	.name		= RTC_NAME,
	.rating		= 299,
	.पढ़ो		= uv_पढ़ो_rtc,
	.mask		= (u64)UVH_RTC_REAL_TIME_CLOCK_MASK,
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल काष्ठा घड़ी_event_device घड़ी_event_device_uv = अणु
	.name			= RTC_NAME,
	.features		= CLOCK_EVT_FEAT_ONESHOT,
	.shअगरt			= 20,
	.rating			= 400,
	.irq			= -1,
	.set_next_event		= uv_rtc_next_event,
	.set_state_shutकरोwn	= uv_rtc_shutकरोwn,
	.event_handler		= शून्य,
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, cpu_ced);

/* There is one of these allocated per node */
काष्ठा uv_rtc_समयr_head अणु
	spinlock_t	lock;
	/* next cpu रुकोing क्रम समयr, local node relative: */
	पूर्णांक		next_cpu;
	/* number of cpus on this node: */
	पूर्णांक		ncpus;
	काष्ठा अणु
		पूर्णांक	lcpu;		/* प्रणालीwide logical cpu number */
		u64	expires;	/* next समयr expiration क्रम this cpu */
	पूर्ण cpu[];
पूर्ण;

/*
 * Access to uv_rtc_समयr_head via blade id.
 */
अटल काष्ठा uv_rtc_समयr_head		**blade_info __पढ़ो_mostly;

अटल पूर्णांक				uv_rtc_evt_enable;

/*
 * Hardware पूर्णांकerface routines
 */

/* Send IPIs to another node */
अटल व्योम uv_rtc_send_IPI(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ apicid, val;
	पूर्णांक pnode;

	apicid = cpu_physical_id(cpu);
	pnode = uv_apicid_to_pnode(apicid);
	val = (1UL << UVH_IPI_INT_SEND_SHFT) |
	      (apicid << UVH_IPI_INT_APIC_ID_SHFT) |
	      (X86_PLATFORM_IPI_VECTOR << UVH_IPI_INT_VECTOR_SHFT);

	uv_ग_लिखो_global_mmr64(pnode, UVH_IPI_INT, val);
पूर्ण

/* Check क्रम an RTC पूर्णांकerrupt pending */
अटल पूर्णांक uv_पूर्णांकr_pending(पूर्णांक pnode)
अणु
	वापस uv_पढ़ो_global_mmr64(pnode, UVH_EVENT_OCCURRED2) &
		UVH_EVENT_OCCURRED2_RTC_1_MASK;
पूर्ण

/* Setup पूर्णांकerrupt and वापस non-zero अगर early expiration occurred. */
अटल पूर्णांक uv_setup_पूर्णांकr(पूर्णांक cpu, u64 expires)
अणु
	u64 val;
	अचिन्हित दीर्घ apicid = cpu_physical_id(cpu);
	पूर्णांक pnode = uv_cpu_to_pnode(cpu);

	uv_ग_लिखो_global_mmr64(pnode, UVH_RTC1_INT_CONFIG,
		UVH_RTC1_INT_CONFIG_M_MASK);
	uv_ग_लिखो_global_mmr64(pnode, UVH_INT_CMPB, -1L);

	uv_ग_लिखो_global_mmr64(pnode, UVH_EVENT_OCCURRED2_ALIAS,
			      UVH_EVENT_OCCURRED2_RTC_1_MASK);

	val = (X86_PLATFORM_IPI_VECTOR << UVH_RTC1_INT_CONFIG_VECTOR_SHFT) |
		((u64)apicid << UVH_RTC1_INT_CONFIG_APIC_ID_SHFT);

	/* Set configuration */
	uv_ग_लिखो_global_mmr64(pnode, UVH_RTC1_INT_CONFIG, val);
	/* Initialize comparator value */
	uv_ग_लिखो_global_mmr64(pnode, UVH_INT_CMPB, expires);

	अगर (uv_पढ़ो_rtc(शून्य) <= expires)
		वापस 0;

	वापस !uv_पूर्णांकr_pending(pnode);
पूर्ण

/*
 * Per-cpu समयr tracking routines
 */

अटल __init व्योम uv_rtc_deallocate_समयrs(व्योम)
अणु
	पूर्णांक bid;

	क्रम_each_possible_blade(bid) अणु
		kमुक्त(blade_info[bid]);
	पूर्ण
	kमुक्त(blade_info);
पूर्ण

/* Allocate per-node list of cpu समयr expiration बार. */
अटल __init पूर्णांक uv_rtc_allocate_समयrs(व्योम)
अणु
	पूर्णांक cpu;

	blade_info = kसुस्मृति(uv_possible_blades, माप(व्योम *), GFP_KERNEL);
	अगर (!blade_info)
		वापस -ENOMEM;

	क्रम_each_present_cpu(cpu) अणु
		पूर्णांक nid = cpu_to_node(cpu);
		पूर्णांक bid = uv_cpu_to_blade_id(cpu);
		पूर्णांक bcpu = uv_cpu_blade_processor_id(cpu);
		काष्ठा uv_rtc_समयr_head *head = blade_info[bid];

		अगर (!head) अणु
			head = kदो_स्मृति_node(काष्ठा_size(head, cpu,
				uv_blade_nr_possible_cpus(bid)),
				GFP_KERNEL, nid);
			अगर (!head) अणु
				uv_rtc_deallocate_समयrs();
				वापस -ENOMEM;
			पूर्ण
			spin_lock_init(&head->lock);
			head->ncpus = uv_blade_nr_possible_cpus(bid);
			head->next_cpu = -1;
			blade_info[bid] = head;
		पूर्ण

		head->cpu[bcpu].lcpu = cpu;
		head->cpu[bcpu].expires = ULदीर्घ_उच्च;
	पूर्ण

	वापस 0;
पूर्ण

/* Find and set the next expiring समयr.  */
अटल व्योम uv_rtc_find_next_समयr(काष्ठा uv_rtc_समयr_head *head, पूर्णांक pnode)
अणु
	u64 lowest = ULदीर्घ_उच्च;
	पूर्णांक c, bcpu = -1;

	head->next_cpu = -1;
	क्रम (c = 0; c < head->ncpus; c++) अणु
		u64 exp = head->cpu[c].expires;
		अगर (exp < lowest) अणु
			bcpu = c;
			lowest = exp;
		पूर्ण
	पूर्ण
	अगर (bcpu >= 0) अणु
		head->next_cpu = bcpu;
		c = head->cpu[bcpu].lcpu;
		अगर (uv_setup_पूर्णांकr(c, lowest))
			/* If we didn't set it up in समय, trigger */
			uv_rtc_send_IPI(c);
	पूर्ण अन्यथा अणु
		uv_ग_लिखो_global_mmr64(pnode, UVH_RTC1_INT_CONFIG,
			UVH_RTC1_INT_CONFIG_M_MASK);
	पूर्ण
पूर्ण

/*
 * Set expiration समय क्रम current cpu.
 *
 * Returns 1 अगर we missed the expiration समय.
 */
अटल पूर्णांक uv_rtc_set_समयr(पूर्णांक cpu, u64 expires)
अणु
	पूर्णांक pnode = uv_cpu_to_pnode(cpu);
	पूर्णांक bid = uv_cpu_to_blade_id(cpu);
	काष्ठा uv_rtc_समयr_head *head = blade_info[bid];
	पूर्णांक bcpu = uv_cpu_blade_processor_id(cpu);
	u64 *t = &head->cpu[bcpu].expires;
	अचिन्हित दीर्घ flags;
	पूर्णांक next_cpu;

	spin_lock_irqsave(&head->lock, flags);

	next_cpu = head->next_cpu;
	*t = expires;

	/* Will this one be next to go off? */
	अगर (next_cpu < 0 || bcpu == next_cpu ||
			expires < head->cpu[next_cpu].expires) अणु
		head->next_cpu = bcpu;
		अगर (uv_setup_पूर्णांकr(cpu, expires)) अणु
			*t = ULदीर्घ_उच्च;
			uv_rtc_find_next_समयr(head, pnode);
			spin_unlock_irqrestore(&head->lock, flags);
			वापस -ETIME;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&head->lock, flags);
	वापस 0;
पूर्ण

/*
 * Unset expiration समय क्रम current cpu.
 *
 * Returns 1 अगर this समयr was pending.
 */
अटल पूर्णांक uv_rtc_unset_समयr(पूर्णांक cpu, पूर्णांक क्रमce)
अणु
	पूर्णांक pnode = uv_cpu_to_pnode(cpu);
	पूर्णांक bid = uv_cpu_to_blade_id(cpu);
	काष्ठा uv_rtc_समयr_head *head = blade_info[bid];
	पूर्णांक bcpu = uv_cpu_blade_processor_id(cpu);
	u64 *t = &head->cpu[bcpu].expires;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&head->lock, flags);

	अगर ((head->next_cpu == bcpu && uv_पढ़ो_rtc(शून्य) >= *t) || क्रमce)
		rc = 1;

	अगर (rc) अणु
		*t = ULदीर्घ_उच्च;
		/* Was the hardware setup क्रम this समयr? */
		अगर (head->next_cpu == bcpu)
			uv_rtc_find_next_समयr(head, pnode);
	पूर्ण

	spin_unlock_irqrestore(&head->lock, flags);

	वापस rc;
पूर्ण


/*
 * Kernel पूर्णांकerface routines.
 */

/*
 * Read the RTC.
 *
 * Starting with HUB rev 2.0, the UV RTC रेजिस्टर is replicated across all
 * cachelines of it's own page.  This allows faster simultaneous पढ़ोs
 * from a given socket.
 */
अटल u64 uv_पढ़ो_rtc(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ offset;

	अगर (uv_get_min_hub_revision_id() == 1)
		offset = 0;
	अन्यथा
		offset = (uv_blade_processor_id() * L1_CACHE_BYTES) % PAGE_SIZE;

	वापस (u64)uv_पढ़ो_local_mmr(UVH_RTC | offset);
पूर्ण

/*
 * Program the next event, relative to now
 */
अटल पूर्णांक uv_rtc_next_event(अचिन्हित दीर्घ delta,
			     काष्ठा घड़ी_event_device *ced)
अणु
	पूर्णांक ced_cpu = cpumask_first(ced->cpumask);

	वापस uv_rtc_set_समयr(ced_cpu, delta + uv_पढ़ो_rtc(शून्य));
पूर्ण

/*
 * Shutकरोwn the RTC समयr
 */
अटल पूर्णांक uv_rtc_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	पूर्णांक ced_cpu = cpumask_first(evt->cpumask);

	uv_rtc_unset_समयr(ced_cpu, 1);
	वापस 0;
पूर्ण

अटल व्योम uv_rtc_पूर्णांकerrupt(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *ced = &per_cpu(cpu_ced, cpu);

	अगर (!ced || !ced->event_handler)
		वापस;

	अगर (uv_rtc_unset_समयr(cpu, 0) != 1)
		वापस;

	ced->event_handler(ced);
पूर्ण

अटल पूर्णांक __init uv_enable_evt_rtc(अक्षर *str)
अणु
	uv_rtc_evt_enable = 1;

	वापस 1;
पूर्ण
__setup("uvrtcevt", uv_enable_evt_rtc);

अटल __init व्योम uv_rtc_रेजिस्टर_घड़ीevents(काष्ठा work_काष्ठा *dummy)
अणु
	काष्ठा घड़ी_event_device *ced = this_cpu_ptr(&cpu_ced);

	*ced = घड़ी_event_device_uv;
	ced->cpumask = cpumask_of(smp_processor_id());
	घड़ीevents_रेजिस्टर_device(ced);
पूर्ण

अटल __init पूर्णांक uv_rtc_setup_घड़ी(व्योम)
अणु
	पूर्णांक rc;

	अगर (!is_uv_प्रणाली())
		वापस -ENODEV;

	rc = घड़ीsource_रेजिस्टर_hz(&घड़ीsource_uv, sn_rtc_cycles_per_second);
	अगर (rc)
		prपूर्णांकk(KERN_INFO "UV RTC clocksource failed rc %d\n", rc);
	अन्यथा
		prपूर्णांकk(KERN_INFO "UV RTC clocksource registered freq %lu MHz\n",
			sn_rtc_cycles_per_second/(अचिन्हित दीर्घ)1E6);

	अगर (rc || !uv_rtc_evt_enable || x86_platक्रमm_ipi_callback)
		वापस rc;

	/* Setup and रेजिस्टर घड़ीevents */
	rc = uv_rtc_allocate_समयrs();
	अगर (rc)
		जाओ error;

	x86_platक्रमm_ipi_callback = uv_rtc_पूर्णांकerrupt;

	घड़ी_event_device_uv.mult = भाग_sc(sn_rtc_cycles_per_second,
				NSEC_PER_SEC, घड़ी_event_device_uv.shअगरt);

	घड़ी_event_device_uv.min_delta_ns = NSEC_PER_SEC /
						sn_rtc_cycles_per_second;
	घड़ी_event_device_uv.min_delta_ticks = 1;

	घड़ी_event_device_uv.max_delta_ns = घड़ीsource_uv.mask *
				(NSEC_PER_SEC / sn_rtc_cycles_per_second);
	घड़ी_event_device_uv.max_delta_ticks = घड़ीsource_uv.mask;

	rc = schedule_on_each_cpu(uv_rtc_रेजिस्टर_घड़ीevents);
	अगर (rc) अणु
		x86_platक्रमm_ipi_callback = शून्य;
		uv_rtc_deallocate_समयrs();
		जाओ error;
	पूर्ण

	prपूर्णांकk(KERN_INFO "UV RTC clockevents registered\n");

	वापस 0;

error:
	घड़ीsource_unरेजिस्टर(&घड़ीsource_uv);
	prपूर्णांकk(KERN_INFO "UV RTC clockevents failed rc %d\n", rc);

	वापस rc;
पूर्ण
arch_initcall(uv_rtc_setup_घड़ी);
