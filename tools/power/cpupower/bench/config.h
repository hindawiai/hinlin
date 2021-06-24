<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  cpufreq-bench CPUFreq microbenchmark
 *
 *  Copyright (C) 2008 Christian Kornacker <ckornacker@suse.de>
 */

/* initial loop count क्रम the load calibration */
#घोषणा GAUGECOUNT	1500

/* शेष scheduling policy SCHED_OTHER */
#घोषणा SCHEDULER	SCHED_OTHER

#घोषणा PRIORITY_DEFAULT 0
#घोषणा PRIORITY_HIGH	 sched_get_priority_max(SCHEDULER)
#घोषणा PRIORITY_LOW	 sched_get_priority_min(SCHEDULER)

/* enable further debug messages */
#अगर_घोषित DEBUG
#घोषणा dम_लिखो म_लिखो
#अन्यथा
#घोषणा dम_लिखो(...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

