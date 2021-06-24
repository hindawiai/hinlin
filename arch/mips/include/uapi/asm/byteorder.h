<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 99, 2003 by Ralf Baechle
 */
#अगर_अघोषित _ASM_BYTEORDER_H
#घोषणा _ASM_BYTEORDER_H

#अगर defined(__MIPSEB__)
#समावेश <linux/byteorder/big_endian.h>
#या_अगर defined(__MIPSEL__)
#समावेश <linux/byteorder/little_endian.h>
#अन्यथा
# error "MIPS, but neither __MIPSEB__, nor __MIPSEL__???"
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_BYTEORDER_H */
