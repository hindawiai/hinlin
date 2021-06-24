<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KERN_LEVELS_H__
#घोषणा __KERN_LEVELS_H__

#घोषणा KERN_SOH	""		/* ASCII Start Of Header */
#घोषणा KERN_SOH_ASCII	''

#घोषणा KERN_EMERG	KERN_SOH ""	/* प्रणाली is unusable */
#घोषणा KERN_ALERT	KERN_SOH ""	/* action must be taken immediately */
#घोषणा KERN_CRIT	KERN_SOH ""	/* critical conditions */
#घोषणा KERN_ERR	KERN_SOH ""	/* error conditions */
#घोषणा KERN_WARNING	KERN_SOH ""	/* warning conditions */
#घोषणा KERN_NOTICE	KERN_SOH ""	/* normal but signअगरicant condition */
#घोषणा KERN_INFO	KERN_SOH ""	/* inक्रमmational */
#घोषणा KERN_DEBUG	KERN_SOH ""	/* debug-level messages */

#घोषणा KERN_DEFAULT	KERN_SOH ""	/* the शेष kernel loglevel */

/*
 * Annotation क्रम a "continued" line of log prपूर्णांकout (only करोne after a
 * line that had no enclosing \न). Only to be used by core/arch code
 * during early bootup (a जारीd line is not SMP-safe otherwise).
 */
#घोषणा KERN_CONT	""

#पूर्ण_अगर
