<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_TIME_H
#घोषणा _XT_TIME_H 1

#समावेश <linux/types.h>

काष्ठा xt_समय_info अणु
	__u32 date_start;
	__u32 date_stop;
	__u32 dayसमय_start;
	__u32 dayसमय_stop;
	__u32 monthdays_match;
	__u8 weekdays_match;
	__u8 flags;
पूर्ण;

क्रमागत अणु
	/* Match against local समय (instead of UTC) */
	XT_TIME_LOCAL_TZ = 1 << 0,

	/* treat बारtart > बारtop (e.g. 23:00-01:00) as single period */
	XT_TIME_CONTIGUOUS = 1 << 1,

	/* Shortcuts */
	XT_TIME_ALL_MONTHDAYS = 0xFFFFFFFE,
	XT_TIME_ALL_WEEKDAYS  = 0xFE,
	XT_TIME_MIN_DAYTIME   = 0,
	XT_TIME_MAX_DAYTIME   = 24 * 60 * 60 - 1,
पूर्ण;

#घोषणा XT_TIME_ALL_FLAGS (XT_TIME_LOCAL_TZ|XT_TIME_CONTIGUOUS)

#पूर्ण_अगर /* _XT_TIME_H */
