<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/यंत्र/समयx.h
 *
 * sparc64 architecture समयx specअगरications
 */
#अगर_अघोषित _ASMsparc64_TIMEX_H
#घोषणा _ASMsparc64_TIMEX_H

#समावेश <यंत्र/समयr.h>

#घोषणा CLOCK_TICK_RATE	1193180 /* Underlying HZ */

/* Getting on the cycle counter on sparc64. */
प्रकार अचिन्हित दीर्घ cycles_t;
#घोषणा get_cycles()	tick_ops->get_tick()

#घोषणा ARCH_HAS_READ_CURRENT_TIMER

#पूर्ण_अगर
