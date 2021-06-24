<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/यंत्र-sh/समयx.h
 *
 * sh architecture समयx specअगरications
 */
#अगर_अघोषित __ASM_SH_TIMEX_H
#घोषणा __ASM_SH_TIMEX_H

/*
 * Only parts using the legacy CPG code क्रम their घड़ी framework
 * implementation need to define their own Pclk value. If provided, this
 * can be used क्रम accurately setting CLOCK_TICK_RATE, otherwise we
 * simply fall back on the i8253 PIT value.
 */
#अगर_घोषित CONFIG_SH_PCLK_FREQ
#घोषणा CLOCK_TICK_RATE		(CONFIG_SH_PCLK_FREQ / 4) /* Underlying HZ */
#अन्यथा
#घोषणा CLOCK_TICK_RATE		1193180
#पूर्ण_अगर

#समावेश <यंत्र-generic/समयx.h>

#पूर्ण_अगर /* __ASM_SH_TIMEX_H */
