<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Machine dependent access functions क्रम RTC रेजिस्टरs.
 */
#अगर_अघोषित _ASM_MC146818RTC_H
#घोषणा _ASM_MC146818RTC_H


#अगर_घोषित CONFIG_ATARI
/* RTC in Atari machines */

#समावेश <यंत्र/atarihw.h>

#घोषणा ATARI_RTC_PORT(x)	(TT_RTC_BAS + 2*(x))
#घोषणा RTC_ALWAYS_BCD	0

#घोषणा CMOS_READ(addr) (अणु \
atari_outb_p((addr), ATARI_RTC_PORT(0)); \
atari_inb_p(ATARI_RTC_PORT(1)); \
पूर्ण)
#घोषणा CMOS_WRITE(val, addr) (अणु \
atari_outb_p((addr), ATARI_RTC_PORT(0)); \
atari_outb_p((val), ATARI_RTC_PORT(1)); \
पूर्ण)
#पूर्ण_अगर /* CONFIG_ATARI */

#पूर्ण_अगर /* _ASM_MC146818RTC_H */
