<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ALARMTIMER_H
#घोषणा _LINUX_ALARMTIMER_H

#समावेश <linux/समय.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/समयrqueue.h>

काष्ठा rtc_device;

क्रमागत alarmसमयr_type अणु
	ALARM_REALTIME,
	ALARM_BOOTTIME,

	/* Supported types end here */
	ALARM_NUMTYPE,

	/* Used क्रम tracing inक्रमmation. No usable types. */
	ALARM_REALTIME_FREEZER,
	ALARM_BOOTTIME_FREEZER,
पूर्ण;

क्रमागत alarmसमयr_restart अणु
	ALARMTIMER_NORESTART,
	ALARMTIMER_RESTART,
पूर्ण;


#घोषणा ALARMTIMER_STATE_INACTIVE	0x00
#घोषणा ALARMTIMER_STATE_ENQUEUED	0x01

/**
 * काष्ठा alarm - Alarm समयr काष्ठाure
 * @node:	समयrqueue node क्रम adding to the event list this value
 *		also includes the expiration समय.
 * @समयr:	hrसमयr used to schedule events जबतक running
 * @function:	Function poपूर्णांकer to be executed when the समयr fires.
 * @type:	Alarm type (BOOTTIME/REALTIME).
 * @state:	Flag that represents अगर the alarm is set to fire or not.
 * @data:	Internal data value.
 */
काष्ठा alarm अणु
	काष्ठा समयrqueue_node	node;
	काष्ठा hrसमयr		समयr;
	क्रमागत alarmसमयr_restart	(*function)(काष्ठा alarm *, kसमय_प्रकार now);
	क्रमागत alarmसमयr_type	type;
	पूर्णांक			state;
	व्योम			*data;
पूर्ण;

व्योम alarm_init(काष्ठा alarm *alarm, क्रमागत alarmसमयr_type type,
		क्रमागत alarmसमयr_restart (*function)(काष्ठा alarm *, kसमय_प्रकार));
व्योम alarm_start(काष्ठा alarm *alarm, kसमय_प्रकार start);
व्योम alarm_start_relative(काष्ठा alarm *alarm, kसमय_प्रकार start);
व्योम alarm_restart(काष्ठा alarm *alarm);
पूर्णांक alarm_try_to_cancel(काष्ठा alarm *alarm);
पूर्णांक alarm_cancel(काष्ठा alarm *alarm);

u64 alarm_क्रमward(काष्ठा alarm *alarm, kसमय_प्रकार now, kसमय_प्रकार पूर्णांकerval);
u64 alarm_क्रमward_now(काष्ठा alarm *alarm, kसमय_प्रकार पूर्णांकerval);
kसमय_प्रकार alarm_expires_reमुख्यing(स्थिर काष्ठा alarm *alarm);

#अगर_घोषित CONFIG_RTC_CLASS
/* Provide way to access the rtc device being used by alarmसमयrs */
काष्ठा rtc_device *alarmसमयr_get_rtcdev(व्योम);
#अन्यथा
अटल अंतरभूत काष्ठा rtc_device *alarmसमयr_get_rtcdev(व्योम) अणु वापस शून्य; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
