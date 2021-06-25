<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Generic RTC पूर्णांकerface.
 * This version contains the part of the user पूर्णांकerface to the Real Time Clock
 * service. It is used with both the legacy mc146818 and also  EFI
 * Struct rtc_समय and first 12 ioctl by Paul Gorपंचांगaker, 1996 - separated out
 * from <linux/mc146818rtc.h> to this file क्रम 2.4 kernels.
 *
 * Copyright (C) 1999 Hewlett-Packard Co.
 * Copyright (C) 1999 Stephane Eranian <eranian@hpl.hp.com>
 */
#अगर_अघोषित _UAPI_LINUX_RTC_H_
#घोषणा _UAPI_LINUX_RTC_H_

#समावेश <linux/स्थिर.h>
#समावेश <linux/ioctl.h>

/*
 * The काष्ठा used to pass data via the following ioctl. Similar to the
 * काष्ठा पंचांग in <समय.स>, but it needs to be here so that the kernel
 * source is self contained, allowing cross-compiles, etc. etc.
 */

काष्ठा rtc_समय अणु
	पूर्णांक पंचांग_sec;
	पूर्णांक पंचांग_min;
	पूर्णांक पंचांग_hour;
	पूर्णांक पंचांग_mday;
	पूर्णांक पंचांग_mon;
	पूर्णांक पंचांग_year;
	पूर्णांक पंचांग_wday;
	पूर्णांक पंचांग_yday;
	पूर्णांक पंचांग_isdst;
पूर्ण;

/*
 * This data काष्ठाure is inspired by the EFI (v0.92) wakeup
 * alarm API.
 */
काष्ठा rtc_wkalrm अणु
	अचिन्हित अक्षर enabled;	/* 0 = alarm disabled, 1 = alarm enabled */
	अचिन्हित अक्षर pending;  /* 0 = alarm not pending, 1 = alarm pending */
	काष्ठा rtc_समय समय;	/* समय the alarm is set to */
पूर्ण;

/*
 * Data काष्ठाure to control PLL correction some better RTC feature
 * pll_value is used to get or set current value of correction,
 * the rest of the काष्ठा is used to query HW capabilities.
 * This is modeled after the RTC used in Q40/Q60 computers but
 * should be sufficiently flexible क्रम other devices
 *
 * +ve pll_value means घड़ी will run faster by
 *   pll_value*pll_posmult/pll_घड़ी
 * -ve pll_value means घड़ी will run slower by
 *   pll_value*pll_negmult/pll_घड़ी
 */

काष्ठा rtc_pll_info अणु
	पूर्णांक pll_ctrl;       /* placeholder क्रम fancier control */
	पूर्णांक pll_value;      /* get/set correction value */
	पूर्णांक pll_max;        /* max +ve (faster) adjusपंचांगent value */
	पूर्णांक pll_min;        /* max -ve (slower) adjusपंचांगent value */
	पूर्णांक pll_posmult;    /* factor क्रम +ve correction */
	पूर्णांक pll_negmult;    /* factor क्रम -ve correction */
	दीर्घ pll_घड़ी;     /* base PLL frequency */
पूर्ण;

/*
 * ioctl calls that are permitted to the /dev/rtc पूर्णांकerface, अगर
 * any of the RTC drivers are enabled.
 */

#घोषणा RTC_AIE_ON	_IO('p', 0x01)	/* Alarm पूर्णांक. enable on		*/
#घोषणा RTC_AIE_OFF	_IO('p', 0x02)	/* ... off			*/
#घोषणा RTC_UIE_ON	_IO('p', 0x03)	/* Update पूर्णांक. enable on	*/
#घोषणा RTC_UIE_OFF	_IO('p', 0x04)	/* ... off			*/
#घोषणा RTC_PIE_ON	_IO('p', 0x05)	/* Periodic पूर्णांक. enable on	*/
#घोषणा RTC_PIE_OFF	_IO('p', 0x06)	/* ... off			*/
#घोषणा RTC_WIE_ON	_IO('p', 0x0f)  /* Watchकरोg पूर्णांक. enable on	*/
#घोषणा RTC_WIE_OFF	_IO('p', 0x10)  /* ... off			*/

#घोषणा RTC_ALM_SET	_IOW('p', 0x07, काष्ठा rtc_समय) /* Set alarm समय  */
#घोषणा RTC_ALM_READ	_IOR('p', 0x08, काष्ठा rtc_समय) /* Read alarm समय */
#घोषणा RTC_RD_TIME	_IOR('p', 0x09, काष्ठा rtc_समय) /* Read RTC समय   */
#घोषणा RTC_SET_TIME	_IOW('p', 0x0a, काष्ठा rtc_समय) /* Set RTC समय    */
#घोषणा RTC_IRQP_READ	_IOR('p', 0x0b, अचिन्हित दीर्घ)	 /* Read IRQ rate   */
#घोषणा RTC_IRQP_SET	_IOW('p', 0x0c, अचिन्हित दीर्घ)	 /* Set IRQ rate    */
#घोषणा RTC_EPOCH_READ	_IOR('p', 0x0d, अचिन्हित दीर्घ)	 /* Read epoch      */
#घोषणा RTC_EPOCH_SET	_IOW('p', 0x0e, अचिन्हित दीर्घ)	 /* Set epoch       */

#घोषणा RTC_WKALM_SET	_IOW('p', 0x0f, काष्ठा rtc_wkalrm)/* Set wakeup alarm*/
#घोषणा RTC_WKALM_RD	_IOR('p', 0x10, काष्ठा rtc_wkalrm)/* Get wakeup alarm*/

#घोषणा RTC_PLL_GET	_IOR('p', 0x11, काष्ठा rtc_pll_info)  /* Get PLL correction */
#घोषणा RTC_PLL_SET	_IOW('p', 0x12, काष्ठा rtc_pll_info)  /* Set PLL correction */

#घोषणा RTC_VL_DATA_INVALID	_BITUL(0) /* Voltage too low, RTC data is invalid */
#घोषणा RTC_VL_BACKUP_LOW	_BITUL(1) /* Backup voltage is low */
#घोषणा RTC_VL_BACKUP_EMPTY	_BITUL(2) /* Backup empty or not present */
#घोषणा RTC_VL_ACCURACY_LOW	_BITUL(3) /* Voltage is low, RTC accuracy is reduced */
#घोषणा RTC_VL_BACKUP_SWITCH	_BITUL(4) /* Backup चयनover happened */

#घोषणा RTC_VL_READ	_IOR('p', 0x13, अचिन्हित पूर्णांक)	/* Voltage low detection */
#घोषणा RTC_VL_CLR	_IO('p', 0x14)		/* Clear voltage low inक्रमmation */

/* पूर्णांकerrupt flags */
#घोषणा RTC_IRQF 0x80	/* Any of the following is active */
#घोषणा RTC_PF 0x40	/* Periodic पूर्णांकerrupt */
#घोषणा RTC_AF 0x20	/* Alarm पूर्णांकerrupt */
#घोषणा RTC_UF 0x10	/* Update पूर्णांकerrupt क्रम 1Hz RTC */

/* feature list */
#घोषणा RTC_FEATURE_ALARM		0
#घोषणा RTC_FEATURE_ALARM_RES_MINUTE	1
#घोषणा RTC_FEATURE_NEED_WEEK_DAY	2
#घोषणा RTC_FEATURE_CNT			3

#घोषणा RTC_MAX_FREQ	8192


#पूर्ण_अगर /* _UAPI_LINUX_RTC_H_ */
