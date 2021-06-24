<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __NDS32_DELAY_H__
#घोषणा __NDS32_DELAY_H__

#समावेश <यंत्र/param.h>

/* There is no घड़ीsource cycle counter in the CPU. */
अटल अंतरभूत व्योम __delay(अचिन्हित दीर्घ loops)
अणु
	__यंत्र__ __अस्थिर__(".align 2\n"
			     "1:\n"
			     "\taddi\t%0, %0, -1\n"
			     "\tbgtz\t%0, 1b\n"
			     :"=r"(loops)
			     :"0"(loops));
पूर्ण

अटल अंतरभूत व्योम __udelay(अचिन्हित दीर्घ usecs, अचिन्हित दीर्घ lpj)
अणु
	usecs *= (अचिन्हित दीर्घ)(((0x8000000000000000ULL / (500000 / HZ)) +
				  0x80000000ULL) >> 32);
	usecs = (अचिन्हित दीर्घ)(((अचिन्हित दीर्घ दीर्घ)usecs * lpj) >> 32);
	__delay(usecs);
पूर्ण

#घोषणा udelay(usecs) __udelay((usecs), loops_per_jअगरfy)

/* make sure "usecs *= ..." in udelay करो not overflow. */
#अगर HZ >= 1000
#घोषणा MAX_UDELAY_MS	1
#या_अगर HZ <= 200
#घोषणा MAX_UDELAY_MS	5
#अन्यथा
#घोषणा MAX_UDELAY_MS	(1000 / HZ)
#पूर्ण_अगर

#पूर्ण_अगर
