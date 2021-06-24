<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/spinlock.h
 *
 * Copyright (C) 2002, 2003 Paul Mundt
 * Copyright (C) 2006, 2007 Akio Idehara
 */
#अगर_अघोषित __ASM_SH_SPINLOCK_H
#घोषणा __ASM_SH_SPINLOCK_H

#अगर defined(CONFIG_CPU_SH4A)
#समावेश <यंत्र/spinlock-llsc.h>
#या_अगर defined(CONFIG_CPU_J2)
#समावेश <यंत्र/spinlock-cas.h>
#अन्यथा
#त्रुटि "The configured cpu type does not support spinlocks"
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SH_SPINLOCK_H */
