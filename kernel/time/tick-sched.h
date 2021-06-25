<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TICK_SCHED_H
#घोषणा _TICK_SCHED_H

#समावेश <linux/hrसमयr.h>

क्रमागत tick_device_mode अणु
	TICKDEV_MODE_PERIODIC,
	TICKDEV_MODE_ONESHOT,
पूर्ण;

काष्ठा tick_device अणु
	काष्ठा घड़ी_event_device *evtdev;
	क्रमागत tick_device_mode mode;
पूर्ण;

क्रमागत tick_nohz_mode अणु
	NOHZ_MODE_INACTIVE,
	NOHZ_MODE_LOWRES,
	NOHZ_MODE_HIGHRES,
पूर्ण;

/**
 * काष्ठा tick_sched - sched tick emulation and no idle tick control/stats
 * @sched_समयr:	hrसमयr to schedule the periodic tick in high
 *			resolution mode
 * @check_घड़ीs:	Notअगरication mechanism about घड़ीsource changes
 * @nohz_mode:		Mode - one state of tick_nohz_mode
 * @inidle:		Indicator that the CPU is in the tick idle mode
 * @tick_stopped:	Indicator that the idle tick has been stopped
 * @idle_active:	Indicator that the CPU is actively in the tick idle mode;
 *			it is reset during irq handling phases.
 * @करो_समयr_lst:	CPU was the last one करोing करो_समयr beक्रमe going idle
 * @got_idle_tick:	Tick समयr function has run with @inidle set
 * @last_tick:		Store the last tick expiry समय when the tick
 *			समयr is modअगरied क्रम nohz sleeps. This is necessary
 *			to resume the tick समयr operation in the समयline
 *			when the CPU वापसs from nohz sleep.
 * @next_tick:		Next tick to be fired when in dynticks mode.
 * @idle_jअगरfies:	jअगरfies at the entry to idle क्रम idle समय accounting
 * @idle_calls:		Total number of idle calls
 * @idle_sleeps:	Number of idle calls, where the sched tick was stopped
 * @idle_entryसमय:	Time when the idle call was entered
 * @idle_wakeसमय:	Time when the idle was पूर्णांकerrupted
 * @idle_निकाससमय:	Time when the idle state was left
 * @idle_sleepसमय:	Sum of the समय slept in idle with sched tick stopped
 * @ioरुको_sleepसमय:	Sum of the समय slept in idle with sched tick stopped, with IO outstanding
 * @समयr_expires:	Anticipated समयr expiration समय (in हाल sched tick is stopped)
 * @समयr_expires_base:	Base समय घड़ी monotonic क्रम @समयr_expires
 * @next_समयr:		Expiry समय of next expiring समयr क्रम debugging purpose only
 * @tick_dep_mask:	Tick dependency mask - is set, अगर someone needs the tick
 */
काष्ठा tick_sched अणु
	काष्ठा hrसमयr			sched_समयr;
	अचिन्हित दीर्घ			check_घड़ीs;
	क्रमागत tick_nohz_mode		nohz_mode;

	अचिन्हित पूर्णांक			inidle		: 1;
	अचिन्हित पूर्णांक			tick_stopped	: 1;
	अचिन्हित पूर्णांक			idle_active	: 1;
	अचिन्हित पूर्णांक			करो_समयr_last	: 1;
	अचिन्हित पूर्णांक			got_idle_tick	: 1;

	kसमय_प्रकार				last_tick;
	kसमय_प्रकार				next_tick;
	अचिन्हित दीर्घ			idle_jअगरfies;
	अचिन्हित दीर्घ			idle_calls;
	अचिन्हित दीर्घ			idle_sleeps;
	kसमय_प्रकार				idle_entryसमय;
	kसमय_प्रकार				idle_wakeसमय;
	kसमय_प्रकार				idle_निकाससमय;
	kसमय_प्रकार				idle_sleepसमय;
	kसमय_प्रकार				ioरुको_sleepसमय;
	अचिन्हित दीर्घ			last_jअगरfies;
	u64				समयr_expires;
	u64				समयr_expires_base;
	u64				next_समयr;
	kसमय_प्रकार				idle_expires;
	atomic_t			tick_dep_mask;
पूर्ण;

बाह्य काष्ठा tick_sched *tick_get_tick_sched(पूर्णांक cpu);

बाह्य व्योम tick_setup_sched_समयr(व्योम);
#अगर defined CONFIG_NO_HZ_COMMON || defined CONFIG_HIGH_RES_TIMERS
बाह्य व्योम tick_cancel_sched_समयr(पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत व्योम tick_cancel_sched_समयr(पूर्णांक cpu) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
बाह्य पूर्णांक __tick_broadcast_oneshot_control(क्रमागत tick_broadcast_state state);
#अन्यथा
अटल अंतरभूत पूर्णांक
__tick_broadcast_oneshot_control(क्रमागत tick_broadcast_state state)
अणु
	वापस -EBUSY;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
