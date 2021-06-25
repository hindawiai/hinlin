<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_HRTIMER_DEFS_H
#घोषणा _LINUX_HRTIMER_DEFS_H

#समावेश <linux/kसमय.स>

#अगर_घोषित CONFIG_HIGH_RES_TIMERS

/*
 * The resolution of the घड़ीs. The resolution value is वापसed in
 * the घड़ी_getres() प्रणाली call to give application programmers an
 * idea of the (in)accuracy of समयrs. Timer values are rounded up to
 * this resolution values.
 */
# define HIGH_RES_NSEC		1
# define KTIME_HIGH_RES		(HIGH_RES_NSEC)
# define MONOTONIC_RES_NSEC	HIGH_RES_NSEC
# define KTIME_MONOTONIC_RES	KTIME_HIGH_RES

#अन्यथा

# define MONOTONIC_RES_NSEC	LOW_RES_NSEC
# define KTIME_MONOTONIC_RES	KTIME_LOW_RES

#पूर्ण_अगर

#पूर्ण_अगर
