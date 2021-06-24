<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Machine dependent access functions क्रम RTC रेजिस्टरs.
 */
#अगर_अघोषित __ASM_SPARC64_MC146818RTC_H
#घोषणा __ASM_SPARC64_MC146818RTC_H

#समावेश <यंत्र/पन.स>

#अगर_अघोषित RTC_PORT
बाह्य अचिन्हित दीर्घ cmos_regs;
#घोषणा RTC_PORT(x)	(cmos_regs + (x))
#घोषणा RTC_ALWAYS_BCD	0
#पूर्ण_अगर

/*
 * The yet supported machines all access the RTC index रेजिस्टर via
 * an ISA port access but the way to access the date रेजिस्टर dअगरfers ...
 */
#घोषणा CMOS_READ(addr) (अणु \
outb_p((addr),RTC_PORT(0)); \
inb_p(RTC_PORT(1)); \
पूर्ण)
#घोषणा CMOS_WRITE(val, addr) (अणु \
outb_p((addr),RTC_PORT(0)); \
outb_p((val),RTC_PORT(1)); \
पूर्ण)

#पूर्ण_अगर /* __ASM_SPARC64_MC146818RTC_H */
