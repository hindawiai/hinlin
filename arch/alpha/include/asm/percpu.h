<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_PERCPU_H
#घोषणा __ALPHA_PERCPU_H

/*
 * To calculate addresses of locally defined variables, GCC uses
 * 32-bit displacement from the GP. Which करोesn't work क्रम per cpu
 * variables in modules, as an offset to the kernel per cpu area is
 * way above 4G.
 *
 * Always use weak definitions क्रम percpu variables in modules.
 */
#अगर defined(MODULE) && defined(CONFIG_SMP)
#घोषणा ARCH_NEEDS_WEAK_PER_CPU
#पूर्ण_अगर

#समावेश <यंत्र-generic/percpu.h>

#पूर्ण_अगर /* __ALPHA_PERCPU_H */
