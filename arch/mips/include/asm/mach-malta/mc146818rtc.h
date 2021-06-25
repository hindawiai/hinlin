<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.
 * Copyright (C) 2003 by Ralf Baechle
 *
 * RTC routines क्रम Malta style attached PIIX4 device, which contains a
 * Motorola MC146818A-compatible Real Time Clock.
 */
#अगर_अघोषित __ASM_MACH_MALTA_MC146818RTC_H
#घोषणा __ASM_MACH_MALTA_MC146818RTC_H

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mips-boards/generic.h>
#समावेश <यंत्र/mips-boards/malta.h>

#घोषणा RTC_PORT(x)	(0x70 + (x))
#घोषणा RTC_IRQ		8

अटल अंतरभूत अचिन्हित अक्षर CMOS_READ(अचिन्हित दीर्घ addr)
अणु
	outb(addr, MALTA_RTC_ADR_REG);
	वापस inb(MALTA_RTC_DAT_REG);
पूर्ण

अटल अंतरभूत व्योम CMOS_WRITE(अचिन्हित अक्षर data, अचिन्हित दीर्घ addr)
अणु
	outb(addr, MALTA_RTC_ADR_REG);
	outb(data, MALTA_RTC_DAT_REG);
पूर्ण

#घोषणा RTC_ALWAYS_BCD	0

#घोषणा mc146818_decode_year(year) ((year) < 70 ? (year) + 2000 : (year) + 1900)

#पूर्ण_अगर /* __ASM_MACH_MALTA_MC146818RTC_H */
