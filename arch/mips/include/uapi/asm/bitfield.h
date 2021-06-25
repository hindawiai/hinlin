<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2014 by Ralf Baechle <ralf@linux-mips.org>
 */
#अगर_अघोषित __UAPI_ASM_BITFIELD_H
#घोषणा __UAPI_ASM_BITFIELD_H

/*
 *  * Damn ...  bitfields depend from byteorder :-(
 *   */
#अगर_घोषित __MIPSEB__
#घोषणा __BITFIELD_FIELD(field, more)					\
	field;								\
	more

#या_अगर defined(__MIPSEL__)

#घोषणा __BITFIELD_FIELD(field, more)					\
	more								\
	field;

#अन्यथा /* !defined (__MIPSEB__) && !defined (__MIPSEL__) */
#त्रुटि "MIPS but neither __MIPSEL__ nor __MIPSEB__?"
#पूर्ण_अगर

#पूर्ण_अगर /* __UAPI_ASM_BITFIELD_H */
