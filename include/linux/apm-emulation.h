<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* -*- linux-c -*-
 *
 * (C) 2003 zecke@handhelds.org
 *
 * based on arch/arm/kernel/apm.c
 * factor out the inक्रमmation needed by architectures to provide
 * apm status
 */
#अगर_अघोषित __LINUX_APM_EMULATION_H
#घोषणा __LINUX_APM_EMULATION_H

#समावेश <linux/apm_मूलप्रण.स>

/*
 * This काष्ठाure माला_लो filled in by the machine specअगरic 'get_power_status'
 * implementation.  Any fields which are not set शेष to a safe value.
 */
काष्ठा apm_घातer_info अणु
	अचिन्हित अक्षर	ac_line_status;
#घोषणा APM_AC_OFFLINE			0
#घोषणा APM_AC_ONLINE			1
#घोषणा APM_AC_BACKUP			2
#घोषणा APM_AC_UNKNOWN			0xff

	अचिन्हित अक्षर	battery_status;
#घोषणा APM_BATTERY_STATUS_HIGH		0
#घोषणा APM_BATTERY_STATUS_LOW		1
#घोषणा APM_BATTERY_STATUS_CRITICAL	2
#घोषणा APM_BATTERY_STATUS_CHARGING	3
#घोषणा APM_BATTERY_STATUS_NOT_PRESENT	4
#घोषणा APM_BATTERY_STATUS_UNKNOWN	0xff

	अचिन्हित अक्षर	battery_flag;
#घोषणा APM_BATTERY_FLAG_HIGH		(1 << 0)
#घोषणा APM_BATTERY_FLAG_LOW		(1 << 1)
#घोषणा APM_BATTERY_FLAG_CRITICAL	(1 << 2)
#घोषणा APM_BATTERY_FLAG_CHARGING	(1 << 3)
#घोषणा APM_BATTERY_FLAG_NOT_PRESENT	(1 << 7)
#घोषणा APM_BATTERY_FLAG_UNKNOWN	0xff

	पूर्णांक		battery_lअगरe;
	पूर्णांक		समय;
	पूर्णांक		units;
#घोषणा APM_UNITS_MINS			0
#घोषणा APM_UNITS_SECS			1
#घोषणा APM_UNITS_UNKNOWN		-1

पूर्ण;

/*
 * This allows machines to provide their own "apm get power status" function.
 */
बाह्य व्योम (*apm_get_घातer_status)(काष्ठा apm_घातer_info *);

/*
 * Queue an event (APM_SYS_SUSPEND or APM_CRITICAL_SUSPEND)
 */
व्योम apm_queue_event(apm_event_t event);

#पूर्ण_अगर /* __LINUX_APM_EMULATION_H */
