<शैली गुरु>
/*
 * Copyright (C) 1998, 1999, 2003 Ralf Baechle
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित __LINUX_DS1286_H
#घोषणा __LINUX_DS1286_H

/**********************************************************************
 * रेजिस्टर summary
 **********************************************************************/
#घोषणा RTC_HUNDREDTH_SECOND	0
#घोषणा RTC_SECONDS		1
#घोषणा RTC_MINUTES		2
#घोषणा RTC_MINUTES_ALARM	3
#घोषणा RTC_HOURS		4
#घोषणा RTC_HOURS_ALARM		5
#घोषणा RTC_DAY			6
#घोषणा RTC_DAY_ALARM		7
#घोषणा RTC_DATE		8
#घोषणा RTC_MONTH		9
#घोषणा RTC_YEAR		10
#घोषणा RTC_CMD			11
#घोषणा RTC_WHSEC		12
#घोषणा RTC_WSEC		13
#घोषणा RTC_UNUSED		14

/* RTC_*_alarm is always true अगर 2 MSBs are set */
# define RTC_ALARM_DONT_CARE 	0xC0


/*
 * Bits in the month रेजिस्टर
 */
#घोषणा RTC_EOSC		0x80
#घोषणा RTC_ESQW		0x40

/*
 * Bits in the Command रेजिस्टर
 */
#घोषणा RTC_TDF			0x01
#घोषणा RTC_WAF			0x02
#घोषणा RTC_TDM			0x04
#घोषणा RTC_WAM			0x08
#घोषणा RTC_PU_LVL		0x10
#घोषणा RTC_IBH_LO		0x20
#घोषणा RTC_IPSW		0x40
#घोषणा RTC_TE			0x80

#पूर्ण_अगर /* __LINUX_DS1286_H */
