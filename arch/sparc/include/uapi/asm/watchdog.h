<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *
 * watchकरोg - Driver पूर्णांकerface क्रम the hardware watchकरोg समयrs
 * present on Sun Microप्रणालीs boardsets
 *
 * Copyright (c) 2000 Eric Brower <ebrower@usa.net>
 *
 */

#अगर_अघोषित _SPARC64_WATCHDOG_H
#घोषणा _SPARC64_WATCHDOG_H

#समावेश <linux/watchकरोg.h>

/* Solaris compatibility ioctls--
 * Ref. <linux/watchकरोg.h> क्रम standard linux watchकरोg ioctls
 */
#घोषणा WIOCSTART _IO (WATCHDOG_IOCTL_BASE, 10)		/* Start Timer		*/
#घोषणा WIOCSTOP  _IO (WATCHDOG_IOCTL_BASE, 11)		/* Stop Timer		*/
#घोषणा WIOCGSTAT _IOR(WATCHDOG_IOCTL_BASE, 12, पूर्णांक)/* Get Timer Status	*/

/* Status flags from WIOCGSTAT ioctl
 */
#घोषणा WD_FREERUN	0x01	/* समयr is running, पूर्णांकerrupts disabled	*/
#घोषणा WD_EXPIRED	0x02	/* समयr has expired						*/
#घोषणा WD_RUNNING	0x04	/* समयr is running, पूर्णांकerrupts enabled		*/
#घोषणा WD_STOPPED	0x08	/* समयr has not been started				*/
#घोषणा WD_SERVICED 0x10	/* समयr पूर्णांकerrupt was serviced				*/

#पूर्ण_अगर /* अगरndef _SPARC64_WATCHDOG_H */

