<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * Authors: Waiman Long <दीर्घman@redhat.com>
 */

#अगर_अघोषित __LOCKING_LOCK_EVENTS_H
#घोषणा __LOCKING_LOCK_EVENTS_H

क्रमागत lock_events अणु

#समावेश "lock_events_list.h"

	lockevent_num,	/* Total number of lock event counts */
	LOCKEVENT_reset_cnts = lockevent_num,
पूर्ण;

#अगर_घोषित CONFIG_LOCK_EVENT_COUNTS
/*
 * Per-cpu counters
 */
DECLARE_PER_CPU(अचिन्हित दीर्घ, lockevents[lockevent_num]);

/*
 * Increment the statistical counters. use raw_cpu_inc() because of lower
 * overhead and we करोn't care अगर we loose the occasional update.
 */
अटल अंतरभूत व्योम __lockevent_inc(क्रमागत lock_events event, bool cond)
अणु
	अगर (cond)
		raw_cpu_inc(lockevents[event]);
पूर्ण

#घोषणा lockevent_inc(ev)	  __lockevent_inc(LOCKEVENT_ ##ev, true)
#घोषणा lockevent_cond_inc(ev, c) __lockevent_inc(LOCKEVENT_ ##ev, c)

अटल अंतरभूत व्योम __lockevent_add(क्रमागत lock_events event, पूर्णांक inc)
अणु
	raw_cpu_add(lockevents[event], inc);
पूर्ण

#घोषणा lockevent_add(ev, c)	__lockevent_add(LOCKEVENT_ ##ev, c)

#अन्यथा  /* CONFIG_LOCK_EVENT_COUNTS */

#घोषणा lockevent_inc(ev)
#घोषणा lockevent_add(ev, c)
#घोषणा lockevent_cond_inc(ev, c)

#पूर्ण_अगर /* CONFIG_LOCK_EVENT_COUNTS */
#पूर्ण_अगर /* __LOCKING_LOCK_EVENTS_H */
