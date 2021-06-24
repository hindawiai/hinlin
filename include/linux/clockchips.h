<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  linux/include/linux/घड़ीchips.h
 *
 *  This file contains the काष्ठाure definitions क्रम घड़ीchips.
 *
 *  If you are not a घड़ीchip, or the समय of day code, you should
 *  not be including this file!
 */
#अगर_अघोषित _LINUX_CLOCKCHIPS_H
#घोषणा _LINUX_CLOCKCHIPS_H

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS

# include <linux/घड़ीsource.h>
# include <linux/cpumask.h>
# include <linux/kसमय.स>
# include <linux/notअगरier.h>

काष्ठा घड़ी_event_device;
काष्ठा module;

/*
 * Possible states of a घड़ी event device.
 *
 * DETACHED:	Device is not used by घड़ीevents core. Initial state or can be
 *		reached from SHUTDOWN.
 * SHUTDOWN:	Device is घातered-off. Can be reached from PERIODIC or ONESHOT.
 * PERIODIC:	Device is programmed to generate events periodically. Can be
 *		reached from DETACHED or SHUTDOWN.
 * ONESHOT:	Device is programmed to generate event only once. Can be reached
 *		from DETACHED or SHUTDOWN.
 * ONESHOT_STOPPED: Device was programmed in ONESHOT mode and is temporarily
 *		    stopped.
 */
क्रमागत घड़ी_event_state अणु
	CLOCK_EVT_STATE_DETACHED,
	CLOCK_EVT_STATE_SHUTDOWN,
	CLOCK_EVT_STATE_PERIODIC,
	CLOCK_EVT_STATE_ONESHOT,
	CLOCK_EVT_STATE_ONESHOT_STOPPED,
पूर्ण;

/*
 * Clock event features
 */
# define CLOCK_EVT_FEAT_PERIODIC	0x000001
# define CLOCK_EVT_FEAT_ONESHOT		0x000002
# define CLOCK_EVT_FEAT_KTIME		0x000004

/*
 * x86(64) specअगरic (mis)features:
 *
 * - Clockevent source stops in C3 State and needs broadcast support.
 * - Local APIC समयr is used as a dummy device.
 */
# define CLOCK_EVT_FEAT_C3STOP		0x000008
# define CLOCK_EVT_FEAT_DUMMY		0x000010

/*
 * Core shall set the पूर्णांकerrupt affinity dynamically in broadcast mode
 */
# define CLOCK_EVT_FEAT_DYNIRQ		0x000020
# define CLOCK_EVT_FEAT_PERCPU		0x000040

/*
 * Clockevent device is based on a hrसमयr क्रम broadcast
 */
# define CLOCK_EVT_FEAT_HRTIMER		0x000080

/**
 * काष्ठा घड़ी_event_device - घड़ी event device descriptor
 * @event_handler:	Asचिन्हित by the framework to be called by the low
 *			level handler of the event source
 * @set_next_event:	set next event function using a घड़ीsource delta
 * @set_next_kसमय:	set next event function using a direct kसमय value
 * @next_event:		local storage क्रम the next event in oneshot mode
 * @max_delta_ns:	maximum delta value in ns
 * @min_delta_ns:	minimum delta value in ns
 * @mult:		nanosecond to cycles multiplier
 * @shअगरt:		nanoseconds to cycles भागisor (घातer of two)
 * @state_use_accessors:current state of the device, asचिन्हित by the core code
 * @features:		features
 * @retries:		number of क्रमced programming retries
 * @set_state_periodic:	चयन state to periodic
 * @set_state_oneshot:	चयन state to oneshot
 * @set_state_oneshot_stopped: चयन state to oneshot_stopped
 * @set_state_shutकरोwn:	चयन state to shutकरोwn
 * @tick_resume:	resume clkevt device
 * @broadcast:		function to broadcast events
 * @min_delta_ticks:	minimum delta value in ticks stored क्रम reconfiguration
 * @max_delta_ticks:	maximum delta value in ticks stored क्रम reconfiguration
 * @name:		ptr to घड़ी event name
 * @rating:		variable to rate घड़ी event devices
 * @irq:		IRQ number (only क्रम non CPU local devices)
 * @bound_on:		Bound on CPU
 * @cpumask:		cpumask to indicate क्रम which CPUs this device works
 * @list:		list head क्रम the management code
 * @owner:		module reference
 */
काष्ठा घड़ी_event_device अणु
	व्योम			(*event_handler)(काष्ठा घड़ी_event_device *);
	पूर्णांक			(*set_next_event)(अचिन्हित दीर्घ evt, काष्ठा घड़ी_event_device *);
	पूर्णांक			(*set_next_kसमय)(kसमय_प्रकार expires, काष्ठा घड़ी_event_device *);
	kसमय_प्रकार			next_event;
	u64			max_delta_ns;
	u64			min_delta_ns;
	u32			mult;
	u32			shअगरt;
	क्रमागत घड़ी_event_state	state_use_accessors;
	अचिन्हित पूर्णांक		features;
	अचिन्हित दीर्घ		retries;

	पूर्णांक			(*set_state_periodic)(काष्ठा घड़ी_event_device *);
	पूर्णांक			(*set_state_oneshot)(काष्ठा घड़ी_event_device *);
	पूर्णांक			(*set_state_oneshot_stopped)(काष्ठा घड़ी_event_device *);
	पूर्णांक			(*set_state_shutकरोwn)(काष्ठा घड़ी_event_device *);
	पूर्णांक			(*tick_resume)(काष्ठा घड़ी_event_device *);

	व्योम			(*broadcast)(स्थिर काष्ठा cpumask *mask);
	व्योम			(*suspend)(काष्ठा घड़ी_event_device *);
	व्योम			(*resume)(काष्ठा घड़ी_event_device *);
	अचिन्हित दीर्घ		min_delta_ticks;
	अचिन्हित दीर्घ		max_delta_ticks;

	स्थिर अक्षर		*name;
	पूर्णांक			rating;
	पूर्णांक			irq;
	पूर्णांक			bound_on;
	स्थिर काष्ठा cpumask	*cpumask;
	काष्ठा list_head	list;
	काष्ठा module		*owner;
पूर्ण ____cacheline_aligned;

/* Helpers to verअगरy state of a घड़ीevent device */
अटल अंतरभूत bool घड़ीevent_state_detached(काष्ठा घड़ी_event_device *dev)
अणु
	वापस dev->state_use_accessors == CLOCK_EVT_STATE_DETACHED;
पूर्ण

अटल अंतरभूत bool घड़ीevent_state_shutकरोwn(काष्ठा घड़ी_event_device *dev)
अणु
	वापस dev->state_use_accessors == CLOCK_EVT_STATE_SHUTDOWN;
पूर्ण

अटल अंतरभूत bool घड़ीevent_state_periodic(काष्ठा घड़ी_event_device *dev)
अणु
	वापस dev->state_use_accessors == CLOCK_EVT_STATE_PERIODIC;
पूर्ण

अटल अंतरभूत bool घड़ीevent_state_oneshot(काष्ठा घड़ी_event_device *dev)
अणु
	वापस dev->state_use_accessors == CLOCK_EVT_STATE_ONESHOT;
पूर्ण

अटल अंतरभूत bool घड़ीevent_state_oneshot_stopped(काष्ठा घड़ी_event_device *dev)
अणु
	वापस dev->state_use_accessors == CLOCK_EVT_STATE_ONESHOT_STOPPED;
पूर्ण

/*
 * Calculate a multiplication factor क्रम scaled math, which is used to convert
 * nanoseconds based values to घड़ी ticks:
 *
 * घड़ी_प्रकारicks = (nanoseconds * factor) >> shअगरt.
 *
 * भाग_sc is the rearranged equation to calculate a factor from a given घड़ी
 * ticks / nanoseconds ratio:
 *
 * factor = (घड़ी_प्रकारicks << shअगरt) / nanoseconds
 */
अटल अंतरभूत अचिन्हित दीर्घ
भाग_sc(अचिन्हित दीर्घ ticks, अचिन्हित दीर्घ nsec, पूर्णांक shअगरt)
अणु
	u64 पंचांगp = ((u64)ticks) << shअगरt;

	करो_भाग(पंचांगp, nsec);

	वापस (अचिन्हित दीर्घ) पंचांगp;
पूर्ण

/* Clock event layer functions */
बाह्य u64 घड़ीevent_delta2ns(अचिन्हित दीर्घ latch, काष्ठा घड़ी_event_device *evt);
बाह्य व्योम घड़ीevents_रेजिस्टर_device(काष्ठा घड़ी_event_device *dev);
बाह्य पूर्णांक घड़ीevents_unbind_device(काष्ठा घड़ी_event_device *ced, पूर्णांक cpu);

बाह्य व्योम घड़ीevents_config_and_रेजिस्टर(काष्ठा घड़ी_event_device *dev,
					    u32 freq, अचिन्हित दीर्घ min_delta,
					    अचिन्हित दीर्घ max_delta);

बाह्य पूर्णांक घड़ीevents_update_freq(काष्ठा घड़ी_event_device *ce, u32 freq);

अटल अंतरभूत व्योम
घड़ीevents_calc_mult_shअगरt(काष्ठा घड़ी_event_device *ce, u32 freq, u32 maxsec)
अणु
	वापस घड़ीs_calc_mult_shअगरt(&ce->mult, &ce->shअगरt, NSEC_PER_SEC, freq, maxsec);
पूर्ण

बाह्य व्योम घड़ीevents_suspend(व्योम);
बाह्य व्योम घड़ीevents_resume(व्योम);

# अगरdef CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
#  अगरdef CONFIG_ARCH_HAS_TICK_BROADCAST
बाह्य व्योम tick_broadcast(स्थिर काष्ठा cpumask *mask);
#  अन्यथा
#   define tick_broadcast	शून्य
#  endअगर
बाह्य पूर्णांक tick_receive_broadcast(व्योम);
# endअगर

# अगर defined(CONFIG_GENERIC_CLOCKEVENTS_BROADCAST) && defined(CONFIG_TICK_ONESHOT)
बाह्य व्योम tick_setup_hrसमयr_broadcast(व्योम);
बाह्य पूर्णांक tick_check_broadcast_expired(व्योम);
# अन्यथा
अटल अंतरभूत पूर्णांक tick_check_broadcast_expired(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम tick_setup_hrसमयr_broadcast(व्योम) अणु पूर्ण
# endअगर

#अन्यथा /* !CONFIG_GENERIC_CLOCKEVENTS: */

अटल अंतरभूत व्योम घड़ीevents_suspend(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम घड़ीevents_resume(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक tick_check_broadcast_expired(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम tick_setup_hrसमयr_broadcast(व्योम) अणु पूर्ण

#पूर्ण_अगर /* !CONFIG_GENERIC_CLOCKEVENTS */

#पूर्ण_अगर /* _LINUX_CLOCKCHIPS_H */
