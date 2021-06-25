<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Definitions क्रम talking to the PMU.  The PMU is a microcontroller
 * which controls battery अक्षरging and प्रणाली घातer on PowerBook 3400
 * and 2400 models as well as the RTC and various other things.
 *
 * Copyright (C) 1998 Paul Mackerras.
 */

#अगर_अघोषित _UAPI_LINUX_PMU_H
#घोषणा _UAPI_LINUX_PMU_H

#घोषणा PMU_DRIVER_VERSION	2

/*
 * PMU commands
 */
#घोषणा PMU_POWER_CTRL0		0x10	/* control घातer of some devices */
#घोषणा PMU_POWER_CTRL		0x11	/* control घातer of some devices */
#घोषणा PMU_ADB_CMD		0x20	/* send ADB packet */
#घोषणा PMU_ADB_POLL_OFF	0x21	/* disable ADB स्वतः-poll */
#घोषणा PMU_WRITE_XPRAM		0x32	/* ग_लिखो eXtended Parameter RAM */
#घोषणा PMU_WRITE_NVRAM		0x33	/* ग_लिखो non-अस्थिर RAM */
#घोषणा PMU_READ_XPRAM		0x3a	/* पढ़ो eXtended Parameter RAM */
#घोषणा PMU_READ_NVRAM		0x3b	/* पढ़ो non-अस्थिर RAM */
#घोषणा PMU_SET_RTC		0x30	/* set real-समय घड़ी */
#घोषणा PMU_READ_RTC		0x38	/* पढ़ो real-समय घड़ी */
#घोषणा PMU_SET_VOLBUTTON	0x40	/* set volume up/करोwn position */
#घोषणा PMU_BACKLIGHT_BRIGHT	0x41	/* set backlight brightness */
#घोषणा PMU_GET_VOLBUTTON	0x48	/* get volume up/करोwn position */
#घोषणा PMU_PCEJECT		0x4c	/* eject PC-card from slot */
#घोषणा PMU_BATTERY_STATE	0x6b	/* report battery state etc. */
#घोषणा PMU_SMART_BATTERY_STATE	0x6f	/* report battery state (new way) */
#घोषणा PMU_SET_INTR_MASK	0x70	/* set PMU पूर्णांकerrupt mask */
#घोषणा PMU_INT_ACK		0x78	/* पढ़ो पूर्णांकerrupt bits */
#घोषणा PMU_SHUTDOWN		0x7e	/* turn घातer off */
#घोषणा PMU_CPU_SPEED		0x7d	/* control CPU speed on some models */
#घोषणा PMU_SLEEP		0x7f	/* put CPU to sleep */
#घोषणा PMU_POWER_EVENTS	0x8f	/* Send घातer-event commands to PMU */
#घोषणा PMU_I2C_CMD		0x9a	/* I2C operations */
#घोषणा PMU_RESET		0xd0	/* reset CPU */
#घोषणा PMU_GET_BRIGHTBUTTON	0xd9	/* report brightness up/करोwn pos */
#घोषणा PMU_GET_COVER		0xdc	/* report cover खोलो/बंदd */
#घोषणा PMU_SYSTEM_READY	0xdf	/* tell PMU we are awake */
#घोषणा PMU_GET_VERSION		0xea	/* पढ़ो the PMU version */

/* Bits to use with the PMU_POWER_CTRL0 command */
#घोषणा PMU_POW0_ON		0x80	/* OR this to घातer ON the device */
#घोषणा PMU_POW0_OFF		0x00	/* leave bit 7 to 0 to घातer it OFF */
#घोषणा PMU_POW0_HARD_DRIVE	0x04	/* Hard drive घातer (on wallstreet/lombard ?) */

/* Bits to use with the PMU_POWER_CTRL command */
#घोषणा PMU_POW_ON		0x80	/* OR this to घातer ON the device */
#घोषणा PMU_POW_OFF		0x00	/* leave bit 7 to 0 to घातer it OFF */
#घोषणा PMU_POW_BACKLIGHT	0x01	/* backlight घातer */
#घोषणा PMU_POW_CHARGER		0x02	/* battery अक्षरger घातer */
#घोषणा PMU_POW_IRLED		0x04	/* IR led घातer (on wallstreet) */
#घोषणा PMU_POW_MEDIABAY	0x08	/* media bay घातer (wallstreet/lombard ?) */

/* Bits in PMU पूर्णांकerrupt and पूर्णांकerrupt mask bytes */
#घोषणा PMU_INT_PCEJECT		0x04	/* PC-card eject buttons */
#घोषणा PMU_INT_SNDBRT		0x08	/* sound/brightness up/करोwn buttons */
#घोषणा PMU_INT_ADB		0x10	/* ADB स्वतःpoll or reply data */
#घोषणा PMU_INT_BATTERY		0x20	/* Battery state change */
#घोषणा PMU_INT_ENVIRONMENT	0x40	/* Environment पूर्णांकerrupts */
#घोषणा PMU_INT_TICK		0x80	/* 1-second tick पूर्णांकerrupt */

/* Other bits in PMU पूर्णांकerrupt valid when PMU_INT_ADB is set */
#घोषणा PMU_INT_ADB_AUTO	0x04	/* ADB स्वतःpoll, when PMU_INT_ADB */
#घोषणा PMU_INT_WAITING_CHARGER	0x01	/* ??? */
#घोषणा PMU_INT_AUTO_SRQ_POLL	0x02	/* ??? */

/* Bits in the environement message (either obtained via PMU_GET_COVER,
 * or via PMU_INT_ENVIRONMENT on core99 */
#घोषणा PMU_ENV_LID_CLOSED	0x01	/* The lid is बंदd */

/* I2C related definitions */
#घोषणा PMU_I2C_MODE_SIMPLE	0
#घोषणा PMU_I2C_MODE_STDSUB	1
#घोषणा PMU_I2C_MODE_COMBINED	2

#घोषणा PMU_I2C_BUS_STATUS	0
#घोषणा PMU_I2C_BUS_SYSCLK	1
#घोषणा PMU_I2C_BUS_POWER	2

#घोषणा PMU_I2C_STATUS_OK	0
#घोषणा PMU_I2C_STATUS_DATAREAD	1
#घोषणा PMU_I2C_STATUS_BUSY	0xfe


/* Kind of PMU (model) */
क्रमागत अणु
	PMU_UNKNOWN,
	PMU_OHARE_BASED,	/* 2400, 3400, 3500 (old G3 घातerbook) */
	PMU_HEATHROW_BASED,	/* PowerBook G3 series */
	PMU_PADDINGTON_BASED,	/* 1999 PowerBook G3 */
	PMU_KEYLARGO_BASED,	/* Core99 motherboard (PMU99) */
	PMU_68K_V1,		/* Unused/deprecated */
	PMU_68K_V2,		/* Unused/deprecated */
पूर्ण;

/* PMU PMU_POWER_EVENTS commands */
क्रमागत अणु
	PMU_PWR_GET_POWERUP_EVENTS	= 0x00,
	PMU_PWR_SET_POWERUP_EVENTS	= 0x01,
	PMU_PWR_CLR_POWERUP_EVENTS	= 0x02,
	PMU_PWR_GET_WAKEUP_EVENTS	= 0x03,
	PMU_PWR_SET_WAKEUP_EVENTS	= 0x04,
	PMU_PWR_CLR_WAKEUP_EVENTS	= 0x05,
पूर्ण;

/* Power events wakeup bits */
क्रमागत अणु
	PMU_PWR_WAKEUP_KEY		= 0x01,	/* Wake on key press */
	PMU_PWR_WAKEUP_AC_INSERT	= 0x02, /* Wake on AC adapter plug */
	PMU_PWR_WAKEUP_AC_CHANGE	= 0x04,
	PMU_PWR_WAKEUP_LID_OPEN		= 0x08,
	PMU_PWR_WAKEUP_RING		= 0x10,
पूर्ण;
	
/*
 * Ioctl commands क्रम the /dev/pmu device
 */
#समावेश <linux/ioctl.h>

/* no param */
#घोषणा PMU_IOC_SLEEP		_IO('B', 0)
/* out param: u32*	backlight value: 0 to 15 */
#घोषणा PMU_IOC_GET_BACKLIGHT	_IOR('B', 1, माप_प्रकार)
/* in param: u32	backlight value: 0 to 15 */
#घोषणा PMU_IOC_SET_BACKLIGHT	_IOW('B', 2, माप_प्रकार)
/* out param: u32*	PMU model */
#घोषणा PMU_IOC_GET_MODEL	_IOR('B', 3, माप_प्रकार)
/* out param: u32*	has_adb: 0 or 1 */
#घोषणा PMU_IOC_HAS_ADB		_IOR('B', 4, माप_प्रकार) 
/* out param: u32*	can_sleep: 0 or 1 */
#घोषणा PMU_IOC_CAN_SLEEP	_IOR('B', 5, माप_प्रकार) 
/* no param, but historically was _IOR('B', 6, 0), meaning 4 bytes */
#घोषणा PMU_IOC_GRAB_BACKLIGHT	_IOR('B', 6, माप_प्रकार) 


#पूर्ण_अगर /* _UAPI_LINUX_PMU_H */
