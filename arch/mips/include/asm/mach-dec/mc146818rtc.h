<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RTC definitions क्रम DECstation style attached Dallas DS1287 chip.
 *
 * Copyright (C) 1998, 2001 by Ralf Baechle
 * Copyright (C) 1998 by Harald Koerfgen
 * Copyright (C) 2002, 2005  Maciej W. Rozycki
 */
#अगर_अघोषित __ASM_MIPS_DEC_RTC_DEC_H
#घोषणा __ASM_MIPS_DEC_RTC_DEC_H

#समावेश <linux/types.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/dec/प्रणाली.h>

बाह्य अस्थिर u8 *dec_rtc_base;

#घोषणा ARCH_RTC_LOCATION

#घोषणा RTC_PORT(x)	CPHYSADDR((दीर्घ)dec_rtc_base)
#घोषणा RTC_IO_EXTENT	dec_kn_slot_size
#घोषणा RTC_IOMAPPED	0
#अघोषित RTC_IRQ

#घोषणा RTC_DEC_YEAR	0x3f	/* Where we store the real year on DECs.  */

अटल अंतरभूत अचिन्हित अक्षर CMOS_READ(अचिन्हित दीर्घ addr)
अणु
	वापस dec_rtc_base[addr * 4];
पूर्ण

अटल अंतरभूत व्योम CMOS_WRITE(अचिन्हित अक्षर data, अचिन्हित दीर्घ addr)
अणु
	dec_rtc_base[addr * 4] = data;
पूर्ण

#घोषणा RTC_ALWAYS_BCD	0

#पूर्ण_अगर /* __ASM_MIPS_DEC_RTC_DEC_H */
