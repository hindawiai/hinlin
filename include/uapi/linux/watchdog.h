<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *	Generic watchकरोg defines. Derived from..
 *
 * Berkshire PC Watchकरोg Defines
 * by Ken Hollis <khollis@bitgate.com>
 *
 */

#अगर_अघोषित _UAPI_LINUX_WATCHDOG_H
#घोषणा _UAPI_LINUX_WATCHDOG_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

#घोषणा	WATCHDOG_IOCTL_BASE	'W'

काष्ठा watchकरोg_info अणु
	__u32 options;		/* Options the card/driver supports */
	__u32 firmware_version;	/* Firmware version of the card */
	__u8  identity[32];	/* Identity of the board */
पूर्ण;

#घोषणा	WDIOC_GETSUPPORT	_IOR(WATCHDOG_IOCTL_BASE, 0, काष्ठा watchकरोg_info)
#घोषणा	WDIOC_GETSTATUS		_IOR(WATCHDOG_IOCTL_BASE, 1, पूर्णांक)
#घोषणा	WDIOC_GETBOOTSTATUS	_IOR(WATCHDOG_IOCTL_BASE, 2, पूर्णांक)
#घोषणा	WDIOC_GETTEMP		_IOR(WATCHDOG_IOCTL_BASE, 3, पूर्णांक)
#घोषणा	WDIOC_SETOPTIONS	_IOR(WATCHDOG_IOCTL_BASE, 4, पूर्णांक)
#घोषणा	WDIOC_KEEPALIVE		_IOR(WATCHDOG_IOCTL_BASE, 5, पूर्णांक)
#घोषणा	WDIOC_SETTIMEOUT        _IOWR(WATCHDOG_IOCTL_BASE, 6, पूर्णांक)
#घोषणा	WDIOC_GETTIMEOUT        _IOR(WATCHDOG_IOCTL_BASE, 7, पूर्णांक)
#घोषणा	WDIOC_SETPRETIMEOUT	_IOWR(WATCHDOG_IOCTL_BASE, 8, पूर्णांक)
#घोषणा	WDIOC_GETPRETIMEOUT	_IOR(WATCHDOG_IOCTL_BASE, 9, पूर्णांक)
#घोषणा	WDIOC_GETTIMELEFT	_IOR(WATCHDOG_IOCTL_BASE, 10, पूर्णांक)

#घोषणा	WDIOF_UNKNOWN		-1	/* Unknown flag error */
#घोषणा	WDIOS_UNKNOWN		-1	/* Unknown status error */

#घोषणा	WDIOF_OVERHEAT		0x0001	/* Reset due to CPU overheat */
#घोषणा	WDIOF_FANFAULT		0x0002	/* Fan failed */
#घोषणा	WDIOF_EXTERN1		0x0004	/* External relay 1 */
#घोषणा	WDIOF_EXTERN2		0x0008	/* External relay 2 */
#घोषणा	WDIOF_POWERUNDER	0x0010	/* Power bad/घातer fault */
#घोषणा	WDIOF_CARDRESET		0x0020	/* Card previously reset the CPU */
#घोषणा	WDIOF_POWEROVER		0x0040	/* Power over voltage */
#घोषणा	WDIOF_SETTIMEOUT	0x0080  /* Set समयout (in seconds) */
#घोषणा	WDIOF_MAGICCLOSE	0x0100	/* Supports magic बंद अक्षर */
#घोषणा	WDIOF_PRETIMEOUT	0x0200  /* Preसमयout (in seconds), get/set */
#घोषणा	WDIOF_ALARMONLY		0x0400	/* Watchकरोg triggers a management or
					   other बाह्यal alarm not a reboot */
#घोषणा	WDIOF_KEEPALIVEPING	0x8000	/* Keep alive ping reply */

#घोषणा	WDIOS_DISABLECARD	0x0001	/* Turn off the watchकरोg समयr */
#घोषणा	WDIOS_ENABLECARD	0x0002	/* Turn on the watchकरोg समयr */
#घोषणा	WDIOS_TEMPPANIC		0x0004	/* Kernel panic on temperature trip */


#पूर्ण_अगर /* _UAPI_LINUX_WATCHDOG_H */
