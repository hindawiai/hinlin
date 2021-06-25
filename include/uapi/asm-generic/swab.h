<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_GENERIC_SWAB_H
#घोषणा _ASM_GENERIC_SWAB_H

#समावेश <यंत्र/bitsperदीर्घ.h>

/*
 * 32 bit architectures typically (but not always) want to
 * set __SWAB_64_THRU_32__. In user space, this is only
 * valid अगर the compiler supports 64 bit data types.
 */

#अगर __BITS_PER_LONG == 32
#अगर defined(__GNUC__) && !defined(__STRICT_ANSI__) || defined(__KERNEL__)
#घोषणा __SWAB_64_THRU_32__
#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_GENERIC_SWAB_H */
