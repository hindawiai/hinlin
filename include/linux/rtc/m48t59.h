<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/linux/rtc/m48t59.h
 *
 * Definitions क्रम the platक्रमm data of m48t59 RTC chip driver.
 *
 * Copyright (c) 2007 Wind River Systems, Inc.
 *
 * Mark Zhan <rongkai.zhan@windriver.com>
 */

#अगर_अघोषित _LINUX_RTC_M48T59_H_
#घोषणा _LINUX_RTC_M48T59_H_

/*
 * M48T59 Register Offset
 */
#घोषणा M48T59_YEAR		0xf
#घोषणा M48T59_MONTH		0xe
#घोषणा M48T59_MDAY		0xd	/* Day of Month */
#घोषणा M48T59_WDAY		0xc	/* Day of Week */
#घोषणा M48T59_WDAY_CB			0x20	/* Century Bit */
#घोषणा M48T59_WDAY_CEB			0x10	/* Century Enable Bit */
#घोषणा M48T59_HOUR		0xb
#घोषणा M48T59_MIN		0xa
#घोषणा M48T59_SEC		0x9
#घोषणा M48T59_CNTL		0x8
#घोषणा M48T59_CNTL_READ		0x40
#घोषणा M48T59_CNTL_WRITE		0x80
#घोषणा M48T59_WATCHDOG		0x7
#घोषणा M48T59_INTR		0x6
#घोषणा M48T59_INTR_AFE			0x80	/* Alarm Interrupt Enable */
#घोषणा M48T59_INTR_ABE			0x20
#घोषणा M48T59_ALARM_DATE	0x5
#घोषणा M48T59_ALARM_HOUR	0x4
#घोषणा M48T59_ALARM_MIN	0x3
#घोषणा M48T59_ALARM_SEC	0x2
#घोषणा M48T59_UNUSED		0x1
#घोषणा M48T59_FLAGS		0x0
#घोषणा M48T59_FLAGS_WDT		0x80	/* watchकरोg समयr expired */
#घोषणा M48T59_FLAGS_AF			0x40	/* alarm */
#घोषणा M48T59_FLAGS_BF			0x10	/* low battery */

#घोषणा M48T59RTC_TYPE_M48T59	0 /* to keep compatibility */
#घोषणा M48T59RTC_TYPE_M48T02	1
#घोषणा M48T59RTC_TYPE_M48T08	2

काष्ठा m48t59_plat_data अणु
	/* The method to access M48T59 रेजिस्टरs */
	व्योम (*ग_लिखो_byte)(काष्ठा device *dev, u32 ofs, u8 val);
	अचिन्हित अक्षर (*पढ़ो_byte)(काष्ठा device *dev, u32 ofs);

	पूर्णांक type; /* RTC model */

	/* ioaddr mapped बाह्यally */
	व्योम __iomem *ioaddr;
	/* offset to RTC रेजिस्टरs, स्वतःmatically set according to the type */
	अचिन्हित पूर्णांक offset;
पूर्ण;

#पूर्ण_अगर /* _LINUX_RTC_M48T59_H_ */
