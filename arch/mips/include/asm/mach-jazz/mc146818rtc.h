<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1998, 2001, 03 by Ralf Baechle
 * Copyright (C) 2007 Thomas Bogenकरोerfer
 *
 * RTC routines क्रम Jazz style attached Dallas chip.
 */
#अगर_अघोषित __ASM_MACH_JAZZ_MC146818RTC_H
#घोषणा __ASM_MACH_JAZZ_MC146818RTC_H

#समावेश <linux/delay.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/jazz.h>

#घोषणा RTC_PORT(x)	(0x70 + (x))
#घोषणा RTC_IRQ		8

अटल अंतरभूत अचिन्हित अक्षर CMOS_READ(अचिन्हित दीर्घ addr)
अणु
	outb_p(addr, RTC_PORT(0));
	वापस *(अस्थिर अक्षर *)JAZZ_RTC_BASE;
पूर्ण

अटल अंतरभूत व्योम CMOS_WRITE(अचिन्हित अक्षर data, अचिन्हित दीर्घ addr)
अणु
	outb_p(addr, RTC_PORT(0));
	*(अस्थिर अक्षर *)JAZZ_RTC_BASE = data;
पूर्ण

#घोषणा RTC_ALWAYS_BCD	0

#घोषणा mc146818_decode_year(year) ((year) + 1980)

#पूर्ण_अगर /* __ASM_MACH_JAZZ_MC146818RTC_H */
