<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_TIMEX_H
#घोषणा __ASM_GENERIC_TIMEX_H

/*
 * If you have a cycle counter, वापस the value here.
 */
प्रकार अचिन्हित दीर्घ cycles_t;
#अगर_अघोषित get_cycles
अटल अंतरभूत cycles_t get_cycles(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Architectures are encouraged to implement पढ़ो_current_समयr
 * and define this in order to aव्योम the expensive delay loop
 * calibration during boot.
 */
#अघोषित ARCH_HAS_READ_CURRENT_TIMER

#पूर्ण_अगर /* __ASM_GENERIC_TIMEX_H */
