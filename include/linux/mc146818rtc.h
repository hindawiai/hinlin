<शैली गुरु>
/* mc146818rtc.h - रेजिस्टर definitions क्रम the Real-Time-Clock / CMOS RAM
 * Copyright Torsten Duwe <duwe@inक्रमmatik.uni-erlangen.de> 1993
 * derived from Data Sheet, Copyright Motorola 1984 (!).
 * It was written to be part of the Linux operating प्रणाली.
 */
/* permission is hereby granted to copy, modअगरy and redistribute this code
 * in terms of the GNU Library General Public License, Version 2 or later,
 * at your option.
 */

#अगर_अघोषित _MC146818RTC_H
#घोषणा _MC146818RTC_H

#समावेश <यंत्र/पन.स>
#समावेश <linux/rtc.h>			/* get the user-level API */
#समावेश <यंत्र/mc146818rtc.h>		/* रेजिस्टर access macros */
#समावेश <linux/bcd.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm-trace.h>

#अगर_घोषित __KERNEL__
#समावेश <linux/spinlock.h>		/* spinlock_t */
बाह्य spinlock_t rtc_lock;		/* serialize CMOS RAM access */

/* Some RTCs extend the mc146818 रेजिस्टर set to support alarms of more
 * than 24 hours in the future; or dates that include a century code.
 * This platक्रमm_data काष्ठाure can pass this inक्रमmation to the driver.
 *
 * Also, some platक्रमms need suspend()/resume() hooks to kick in special
 * handling of wake alarms, e.g. activating ACPI BIOS hooks or setting up
 * a separate wakeup alarm used by some almost-clone chips.
 */
काष्ठा cmos_rtc_board_info अणु
	व्योम	(*wake_on)(काष्ठा device *dev);
	व्योम	(*wake_off)(काष्ठा device *dev);

	u32	flags;
#घोषणा CMOS_RTC_FLAGS_NOFREQ	(1 << 0)
	पूर्णांक	address_space;

	u8	rtc_day_alarm;		/* zero, or रेजिस्टर index */
	u8	rtc_mon_alarm;		/* zero, or रेजिस्टर index */
	u8	rtc_century;		/* zero, or रेजिस्टर index */
पूर्ण;
#पूर्ण_अगर

/**********************************************************************
 * रेजिस्टर summary
 **********************************************************************/
#घोषणा RTC_SECONDS		0
#घोषणा RTC_SECONDS_ALARM	1
#घोषणा RTC_MINUTES		2
#घोषणा RTC_MINUTES_ALARM	3
#घोषणा RTC_HOURS		4
#घोषणा RTC_HOURS_ALARM		5
/* RTC_*_alarm is always true अगर 2 MSBs are set */
# define RTC_ALARM_DONT_CARE 	0xC0

#घोषणा RTC_DAY_OF_WEEK		6
#घोषणा RTC_DAY_OF_MONTH	7
#घोषणा RTC_MONTH		8
#घोषणा RTC_YEAR		9

/* control रेजिस्टरs - Moto names
 */
#घोषणा RTC_REG_A		10
#घोषणा RTC_REG_B		11
#घोषणा RTC_REG_C		12
#घोषणा RTC_REG_D		13

/**********************************************************************
 * रेजिस्टर details
 **********************************************************************/
#घोषणा RTC_FREQ_SELECT	RTC_REG_A

/* update-in-progress  - set to "1" 244 microsecs beक्रमe RTC goes off the bus,
 * reset after update (may take 1.984ms @ 32768Hz RefClock) is complete,
 * totalling to a max high पूर्णांकerval of 2.228 ms.
 */
# define RTC_UIP		0x80
# define RTC_DIV_CTL		0x70
   /* भागider control: refघड़ी values 4.194 / 1.049 MHz / 32.768 kHz */
#  define RTC_REF_CLCK_4MHZ	0x00
#  define RTC_REF_CLCK_1MHZ	0x10
#  define RTC_REF_CLCK_32KHZ	0x20
   /* 2 values क्रम भागider stage reset, others क्रम "testing purposes only" */
#  define RTC_DIV_RESET1	0x60
#  define RTC_DIV_RESET2	0x70
  /* Periodic पूर्णांकr. / Square wave rate select. 0=none, 1=32.8kHz,... 15=2Hz */
# define RTC_RATE_SELECT 	0x0F

/**********************************************************************/
#घोषणा RTC_CONTROL	RTC_REG_B
# define RTC_SET 0x80		/* disable updates क्रम घड़ी setting */
# define RTC_PIE 0x40		/* periodic पूर्णांकerrupt enable */
# define RTC_AIE 0x20		/* alarm पूर्णांकerrupt enable */
# define RTC_UIE 0x10		/* update-finished पूर्णांकerrupt enable */
# define RTC_SQWE 0x08		/* enable square-wave output */
# define RTC_DM_BINARY 0x04	/* all समय/date values are BCD अगर clear */
# define RTC_24H 0x02		/* 24 hour mode - अन्यथा hours bit 7 means pm */
# define RTC_DST_EN 0x01	/* स्वतः चयन DST - works f. USA only */

/**********************************************************************/
#घोषणा RTC_INTR_FLAGS	RTC_REG_C
/* caution - cleared by पढ़ो */
# define RTC_IRQF 0x80		/* any of the following 3 is active */
# define RTC_PF 0x40
# define RTC_AF 0x20
# define RTC_UF 0x10

/**********************************************************************/
#घोषणा RTC_VALID	RTC_REG_D
# define RTC_VRT 0x80		/* valid RAM and समय */
/**********************************************************************/

#अगर_अघोषित ARCH_RTC_LOCATION	/* Override by <यंत्र/mc146818rtc.h>? */

#घोषणा RTC_IO_EXTENT	0x8
#घोषणा RTC_IO_EXTENT_USED	0x2
#घोषणा RTC_IOMAPPED	1	/* Default to I/O mapping. */

#अन्यथा
#घोषणा RTC_IO_EXTENT_USED      RTC_IO_EXTENT
#पूर्ण_अगर /* ARCH_RTC_LOCATION */

अचिन्हित पूर्णांक mc146818_get_समय(काष्ठा rtc_समय *समय);
पूर्णांक mc146818_set_समय(काष्ठा rtc_समय *समय);

#पूर्ण_अगर /* _MC146818RTC_H */
