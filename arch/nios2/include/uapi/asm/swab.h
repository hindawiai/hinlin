<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2012 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2011 Pyramid Technical Consultants, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 */

#अगर_अघोषित _ASM_NIOS2_SWAB_H
#घोषणा _ASM_NIOS2_SWAB_H

#समावेश <linux/types.h>
#समावेश <यंत्र-generic/swab.h>

#अगर_घोषित CONFIG_NIOS2_CI_SWAB_SUPPORT
#अगर_घोषित __GNUC__

#घोषणा __nios2_swab(x)		\
	__builtin_custom_ini(CONFIG_NIOS2_CI_SWAB_NO, (x))

अटल अंतरभूत __attribute__((स्थिर)) __u16 __arch_swab16(__u16 x)
अणु
	वापस (__u16) __nios2_swab(((__u32) x) << 16);
पूर्ण
#घोषणा __arch_swab16 __arch_swab16

अटल अंतरभूत __attribute__((स्थिर)) __u32 __arch_swab32(__u32 x)
अणु
	वापस (__u32) __nios2_swab(x);
पूर्ण
#घोषणा __arch_swab32 __arch_swab32

#पूर्ण_अगर /* __GNUC__ */
#पूर्ण_अगर /* CONFIG_NIOS2_CI_SWAB_SUPPORT */

#पूर्ण_अगर /* _ASM_NIOS2_SWAB_H */
