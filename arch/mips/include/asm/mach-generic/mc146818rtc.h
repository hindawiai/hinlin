<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1998, 2001, 03 by Ralf Baechle
 *
 * RTC routines क्रम PC style attached Dallas chip.
 */
#अगर_अघोषित __ASM_MACH_GENERIC_MC146818RTC_H
#घोषणा __ASM_MACH_GENERIC_MC146818RTC_H

#समावेश <यंत्र/पन.स>

#घोषणा RTC_PORT(x)	(0x70 + (x))
#घोषणा RTC_IRQ		8

अटल अंतरभूत अचिन्हित अक्षर CMOS_READ(अचिन्हित दीर्घ addr)
अणु
	outb_p(addr, RTC_PORT(0));
	वापस inb_p(RTC_PORT(1));
पूर्ण

अटल अंतरभूत व्योम CMOS_WRITE(अचिन्हित अक्षर data, अचिन्हित दीर्घ addr)
अणु
	outb_p(addr, RTC_PORT(0));
	outb_p(data, RTC_PORT(1));
पूर्ण

#घोषणा RTC_ALWAYS_BCD	0

#अगर_अघोषित mc146818_decode_year
#घोषणा mc146818_decode_year(year) ((year) < 70 ? (year) + 2000 : (year) + 1900)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_MACH_GENERIC_MC146818RTC_H */
