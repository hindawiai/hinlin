<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2004 by Ralf Baechle
 *
 * RTC routines क्रम PC style attached Dallas chip with ARC epoch.
 */
#अगर_अघोषित __ASM_MACH_RM_MC146818RTC_H
#घोषणा __ASM_MACH_RM_MC146818RTC_H

#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#घोषणा mc146818_decode_year(year) ((year) < 70 ? (year) + 2000 : (year) + 1900)
#अन्यथा
#घोषणा mc146818_decode_year(year) ((year) + 1980)
#पूर्ण_अगर

#समावेश <यंत्र/mach-generic/mc146818rtc.h>

#पूर्ण_अगर /* __ASM_MACH_RM_MC146818RTC_H */
