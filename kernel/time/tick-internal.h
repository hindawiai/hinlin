<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * tick पूर्णांकernal variable and functions used by low/high res code
 */
#समावेश <linux/hrसमयr.h>
#समावेश <linux/tick.h>

#समावेश "timekeeping.h"
#समावेश "tick-sched.h"

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS

# define TICK_DO_TIMER_NONE	-1
# define TICK_DO_TIMER_BOOT	-2

DECLARE_PER_CPU(काष्ठा tick_device, tick_cpu_device);
बाह्य kसमय_प्रकार tick_next_period;
बाह्य पूर्णांक tick_करो_समयr_cpu __पढ़ो_mostly;

बाह्य व्योम tick_setup_periodic(काष्ठा घड़ी_event_device *dev, पूर्णांक broadcast);
बाह्य व्योम tick_handle_periodic(काष्ठा घड़ी_event_device *dev);
बाह्य व्योम tick_check_new_device(काष्ठा घड़ी_event_device *dev);
बाह्य व्योम tick_shutकरोwn(अचिन्हित पूर्णांक cpu);
बाह्य व्योम tick_suspend(व्योम);
बाह्य व्योम tick_resume(व्योम);
बाह्य bool tick_check_replacement(काष्ठा घड़ी_event_device *curdev,
				   काष्ठा घड़ी_event_device *newdev);
बाह्य व्योम tick_install_replacement(काष्ठा घड़ी_event_device *dev);
बाह्य पूर्णांक tick_is_oneshot_available(व्योम);
बाह्य काष्ठा tick_device *tick_get_device(पूर्णांक cpu);

बाह्य पूर्णांक घड़ीevents_tick_resume(काष्ठा घड़ी_event_device *dev);
/* Check, अगर the device is functional or a dummy क्रम broadcast */
अटल अंतरभूत पूर्णांक tick_device_is_functional(काष्ठा घड़ी_event_device *dev)
अणु
	वापस !(dev->features & CLOCK_EVT_FEAT_DUMMY);
पूर्ण

अटल अंतरभूत क्रमागत घड़ी_event_state घड़ीevent_get_state(काष्ठा घड़ी_event_device *dev)
अणु
	वापस dev->state_use_accessors;
पूर्ण

अटल अंतरभूत व्योम घड़ीevent_set_state(काष्ठा घड़ी_event_device *dev,
					क्रमागत घड़ी_event_state state)
अणु
	dev->state_use_accessors = state;
पूर्ण

बाह्य व्योम घड़ीevents_shutकरोwn(काष्ठा घड़ी_event_device *dev);
बाह्य व्योम घड़ीevents_exchange_device(काष्ठा घड़ी_event_device *old,
					काष्ठा घड़ी_event_device *new);
बाह्य व्योम घड़ीevents_चयन_state(काष्ठा घड़ी_event_device *dev,
				     क्रमागत घड़ी_event_state state);
बाह्य पूर्णांक घड़ीevents_program_event(काष्ठा घड़ी_event_device *dev,
				     kसमय_प्रकार expires, bool क्रमce);
बाह्य व्योम घड़ीevents_handle_noop(काष्ठा घड़ी_event_device *dev);
बाह्य पूर्णांक __घड़ीevents_update_freq(काष्ठा घड़ी_event_device *dev, u32 freq);
बाह्य sमाप_प्रकार sysfs_get_uname(स्थिर अक्षर *buf, अक्षर *dst, माप_प्रकार cnt);

/* Broadcasting support */
# अगरdef CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
बाह्य पूर्णांक tick_device_uses_broadcast(काष्ठा घड़ी_event_device *dev, पूर्णांक cpu);
बाह्य व्योम tick_install_broadcast_device(काष्ठा घड़ी_event_device *dev);
बाह्य पूर्णांक tick_is_broadcast_device(काष्ठा घड़ी_event_device *dev);
बाह्य व्योम tick_suspend_broadcast(व्योम);
बाह्य व्योम tick_resume_broadcast(व्योम);
बाह्य bool tick_resume_check_broadcast(व्योम);
बाह्य व्योम tick_broadcast_init(व्योम);
बाह्य व्योम tick_set_periodic_handler(काष्ठा घड़ी_event_device *dev, पूर्णांक broadcast);
बाह्य पूर्णांक tick_broadcast_update_freq(काष्ठा घड़ी_event_device *dev, u32 freq);
बाह्य काष्ठा tick_device *tick_get_broadcast_device(व्योम);
बाह्य काष्ठा cpumask *tick_get_broadcast_mask(व्योम);
# अन्यथा /* !CONFIG_GENERIC_CLOCKEVENTS_BROADCAST: */
अटल अंतरभूत व्योम tick_install_broadcast_device(काष्ठा घड़ी_event_device *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक tick_is_broadcast_device(काष्ठा घड़ी_event_device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक tick_device_uses_broadcast(काष्ठा घड़ी_event_device *dev, पूर्णांक cpu) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम tick_करो_periodic_broadcast(काष्ठा घड़ी_event_device *d) अणु पूर्ण
अटल अंतरभूत व्योम tick_suspend_broadcast(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tick_resume_broadcast(व्योम) अणु पूर्ण
अटल अंतरभूत bool tick_resume_check_broadcast(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम tick_broadcast_init(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक tick_broadcast_update_freq(काष्ठा घड़ी_event_device *dev, u32 freq) अणु वापस -ENODEV; पूर्ण

/* Set the periodic handler in non broadcast mode */
अटल अंतरभूत व्योम tick_set_periodic_handler(काष्ठा घड़ी_event_device *dev, पूर्णांक broadcast)
अणु
	dev->event_handler = tick_handle_periodic;
पूर्ण
# endअगर /* !CONFIG_GENERIC_CLOCKEVENTS_BROADCAST */

#अन्यथा /* !GENERIC_CLOCKEVENTS: */
अटल अंतरभूत व्योम tick_suspend(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tick_resume(व्योम) अणु पूर्ण
#पूर्ण_अगर /* !GENERIC_CLOCKEVENTS */

/* Oneshot related functions */
#अगर_घोषित CONFIG_TICK_ONESHOT
बाह्य व्योम tick_setup_oneshot(काष्ठा घड़ी_event_device *newdev,
			       व्योम (*handler)(काष्ठा घड़ी_event_device *),
			       kसमय_प्रकार nextevt);
बाह्य पूर्णांक tick_program_event(kसमय_प्रकार expires, पूर्णांक क्रमce);
बाह्य व्योम tick_oneshot_notअगरy(व्योम);
बाह्य पूर्णांक tick_चयन_to_oneshot(व्योम (*handler)(काष्ठा घड़ी_event_device *));
बाह्य व्योम tick_resume_oneshot(व्योम);
अटल अंतरभूत bool tick_oneshot_possible(व्योम) अणु वापस true; पूर्ण
बाह्य पूर्णांक tick_oneshot_mode_active(व्योम);
बाह्य व्योम tick_घड़ी_notअगरy(व्योम);
बाह्य पूर्णांक tick_check_oneshot_change(पूर्णांक allow_nohz);
बाह्य पूर्णांक tick_init_highres(व्योम);
#अन्यथा /* !CONFIG_TICK_ONESHOT: */
अटल अंतरभूत
व्योम tick_setup_oneshot(काष्ठा घड़ी_event_device *newdev,
			व्योम (*handler)(काष्ठा घड़ी_event_device *),
			kसमय_प्रकार nextevt) अणु BUG(); पूर्ण
अटल अंतरभूत व्योम tick_resume_oneshot(व्योम) अणु BUG(); पूर्ण
अटल अंतरभूत पूर्णांक tick_program_event(kसमय_प्रकार expires, पूर्णांक क्रमce) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम tick_oneshot_notअगरy(व्योम) अणु पूर्ण
अटल अंतरभूत bool tick_oneshot_possible(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक tick_oneshot_mode_active(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम tick_घड़ी_notअगरy(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक tick_check_oneshot_change(पूर्णांक allow_nohz) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* !CONFIG_TICK_ONESHOT */

/* Functions related to oneshot broadcasting */
#अगर defined(CONFIG_GENERIC_CLOCKEVENTS_BROADCAST) && defined(CONFIG_TICK_ONESHOT)
बाह्य व्योम tick_broadcast_चयन_to_oneshot(व्योम);
बाह्य पूर्णांक tick_broadcast_oneshot_active(व्योम);
बाह्य व्योम tick_check_oneshot_broadcast_this_cpu(व्योम);
bool tick_broadcast_oneshot_available(व्योम);
बाह्य काष्ठा cpumask *tick_get_broadcast_oneshot_mask(व्योम);
#अन्यथा /* !(BROADCAST && ONESHOT): */
अटल अंतरभूत व्योम tick_broadcast_चयन_to_oneshot(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक tick_broadcast_oneshot_active(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम tick_check_oneshot_broadcast_this_cpu(व्योम) अणु पूर्ण
अटल अंतरभूत bool tick_broadcast_oneshot_available(व्योम) अणु वापस tick_oneshot_possible(); पूर्ण
#पूर्ण_अगर /* !(BROADCAST && ONESHOT) */

#अगर defined(CONFIG_GENERIC_CLOCKEVENTS_BROADCAST) && defined(CONFIG_HOTPLUG_CPU)
बाह्य व्योम tick_broadcast_offline(अचिन्हित पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत व्योम tick_broadcast_offline(अचिन्हित पूर्णांक cpu) अणु पूर्ण
#पूर्ण_अगर

/* NO_HZ_FULL पूर्णांकernal */
#अगर_घोषित CONFIG_NO_HZ_FULL
बाह्य व्योम tick_nohz_init(व्योम);
# अन्यथा
अटल अंतरभूत व्योम tick_nohz_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NO_HZ_COMMON
बाह्य अचिन्हित दीर्घ tick_nohz_active;
बाह्य व्योम समयrs_update_nohz(व्योम);
# अगरdef CONFIG_SMP
बाह्य काष्ठा अटल_key_false समयrs_migration_enabled;
# endअगर
#अन्यथा /* CONFIG_NO_HZ_COMMON */
अटल अंतरभूत व्योम समयrs_update_nohz(व्योम) अणु पूर्ण
#घोषणा tick_nohz_active (0)
#पूर्ण_अगर

DECLARE_PER_CPU(काष्ठा hrसमयr_cpu_base, hrसमयr_bases);

बाह्य u64 get_next_समयr_पूर्णांकerrupt(अचिन्हित दीर्घ basej, u64 basem);
व्योम समयr_clear_idle(व्योम);
