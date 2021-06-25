<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KERN_LEVELS_H__
#घोषणा __KERN_LEVELS_H__

#घोषणा KERN_SOH	"\001"		/* ASCII Start Of Header */
#घोषणा KERN_SOH_ASCII	'\001'

#घोषणा KERN_EMERG	KERN_SOH "0"	/* प्रणाली is unusable */
#घोषणा KERN_ALERT	KERN_SOH "1"	/* action must be taken immediately */
#घोषणा KERN_CRIT	KERN_SOH "2"	/* critical conditions */
#घोषणा KERN_ERR	KERN_SOH "3"	/* error conditions */
#घोषणा KERN_WARNING	KERN_SOH "4"	/* warning conditions */
#घोषणा KERN_NOTICE	KERN_SOH "5"	/* normal but signअगरicant condition */
#घोषणा KERN_INFO	KERN_SOH "6"	/* inक्रमmational */
#घोषणा KERN_DEBUG	KERN_SOH "7"	/* debug-level messages */

#घोषणा KERN_DEFAULT	""		/* the शेष kernel loglevel */

/*
 * Annotation क्रम a "continued" line of log prपूर्णांकout (only करोne after a
 * line that had no enclosing \न). Only to be used by core/arch code
 * during early bootup (a जारीd line is not SMP-safe otherwise).
 */
#घोषणा KERN_CONT	KERN_SOH "c"

/* पूर्णांकeger equivalents of KERN_<LEVEL> */
#घोषणा LOGLEVEL_SCHED		-2	/* Deferred messages from sched code
					 * are set to this special level */
#घोषणा LOGLEVEL_DEFAULT	-1	/* शेष (or last) loglevel */
#घोषणा LOGLEVEL_EMERG		0	/* प्रणाली is unusable */
#घोषणा LOGLEVEL_ALERT		1	/* action must be taken immediately */
#घोषणा LOGLEVEL_CRIT		2	/* critical conditions */
#घोषणा LOGLEVEL_ERR		3	/* error conditions */
#घोषणा LOGLEVEL_WARNING	4	/* warning conditions */
#घोषणा LOGLEVEL_NOTICE		5	/* normal but signअगरicant condition */
#घोषणा LOGLEVEL_INFO		6	/* inक्रमmational */
#घोषणा LOGLEVEL_DEBUG		7	/* debug-level messages */

#पूर्ण_अगर
