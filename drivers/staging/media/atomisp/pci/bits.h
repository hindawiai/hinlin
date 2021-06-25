<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित _HRT_BITS_H
#घोषणा _HRT_BITS_H

#समावेश "defs.h"

#घोषणा _hrt_ones(n) HRTCAT(_hrt_ones_, n)
#घोषणा _hrt_ones_0x0  0x00000000U
#घोषणा _hrt_ones_0x1  0x00000001U
#घोषणा _hrt_ones_0x2  0x00000003U
#घोषणा _hrt_ones_0x3  0x00000007U
#घोषणा _hrt_ones_0x4  0x0000000FU
#घोषणा _hrt_ones_0x5  0x0000001FU
#घोषणा _hrt_ones_0x6  0x0000003FU
#घोषणा _hrt_ones_0x7  0x0000007FU
#घोषणा _hrt_ones_0x8  0x000000FFU
#घोषणा _hrt_ones_0x9  0x000001FFU
#घोषणा _hrt_ones_0xA  0x000003FFU
#घोषणा _hrt_ones_0xB  0x000007FFU
#घोषणा _hrt_ones_0xC  0x00000FFFU
#घोषणा _hrt_ones_0xD  0x00001FFFU
#घोषणा _hrt_ones_0xE  0x00003FFFU
#घोषणा _hrt_ones_0xF  0x00007FFFU
#घोषणा _hrt_ones_0x10 0x0000FFFFU
#घोषणा _hrt_ones_0x11 0x0001FFFFU
#घोषणा _hrt_ones_0x12 0x0003FFFFU
#घोषणा _hrt_ones_0x13 0x0007FFFFU
#घोषणा _hrt_ones_0x14 0x000FFFFFU
#घोषणा _hrt_ones_0x15 0x001FFFFFU
#घोषणा _hrt_ones_0x16 0x003FFFFFU
#घोषणा _hrt_ones_0x17 0x007FFFFFU
#घोषणा _hrt_ones_0x18 0x00FFFFFFU
#घोषणा _hrt_ones_0x19 0x01FFFFFFU
#घोषणा _hrt_ones_0x1A 0x03FFFFFFU
#घोषणा _hrt_ones_0x1B 0x07FFFFFFU
#घोषणा _hrt_ones_0x1C 0x0FFFFFFFU
#घोषणा _hrt_ones_0x1D 0x1FFFFFFFU
#घोषणा _hrt_ones_0x1E 0x3FFFFFFFU
#घोषणा _hrt_ones_0x1F 0x7FFFFFFFU
#घोषणा _hrt_ones_0x20 0xFFFFFFFFU

#घोषणा _hrt_ones_0  _hrt_ones_0x0
#घोषणा _hrt_ones_1  _hrt_ones_0x1
#घोषणा _hrt_ones_2  _hrt_ones_0x2
#घोषणा _hrt_ones_3  _hrt_ones_0x3
#घोषणा _hrt_ones_4  _hrt_ones_0x4
#घोषणा _hrt_ones_5  _hrt_ones_0x5
#घोषणा _hrt_ones_6  _hrt_ones_0x6
#घोषणा _hrt_ones_7  _hrt_ones_0x7
#घोषणा _hrt_ones_8  _hrt_ones_0x8
#घोषणा _hrt_ones_9  _hrt_ones_0x9
#घोषणा _hrt_ones_10 _hrt_ones_0xA
#घोषणा _hrt_ones_11 _hrt_ones_0xB
#घोषणा _hrt_ones_12 _hrt_ones_0xC
#घोषणा _hrt_ones_13 _hrt_ones_0xD
#घोषणा _hrt_ones_14 _hrt_ones_0xE
#घोषणा _hrt_ones_15 _hrt_ones_0xF
#घोषणा _hrt_ones_16 _hrt_ones_0x10
#घोषणा _hrt_ones_17 _hrt_ones_0x11
#घोषणा _hrt_ones_18 _hrt_ones_0x12
#घोषणा _hrt_ones_19 _hrt_ones_0x13
#घोषणा _hrt_ones_20 _hrt_ones_0x14
#घोषणा _hrt_ones_21 _hrt_ones_0x15
#घोषणा _hrt_ones_22 _hrt_ones_0x16
#घोषणा _hrt_ones_23 _hrt_ones_0x17
#घोषणा _hrt_ones_24 _hrt_ones_0x18
#घोषणा _hrt_ones_25 _hrt_ones_0x19
#घोषणा _hrt_ones_26 _hrt_ones_0x1A
#घोषणा _hrt_ones_27 _hrt_ones_0x1B
#घोषणा _hrt_ones_28 _hrt_ones_0x1C
#घोषणा _hrt_ones_29 _hrt_ones_0x1D
#घोषणा _hrt_ones_30 _hrt_ones_0x1E
#घोषणा _hrt_ones_31 _hrt_ones_0x1F
#घोषणा _hrt_ones_32 _hrt_ones_0x20

#घोषणा _hrt_mask(b, n) \
  (_hrt_ones(n) << (b))
#घोषणा _hrt_get_bits(w, b, n) \
  (((w) >> (b)) & _hrt_ones(n))
#घोषणा _hrt_set_bits(w, b, n, v) \
  (((w) & ~_hrt_mask(b, n)) | (((v) & _hrt_ones(n)) << (b)))
#घोषणा _hrt_get_bit(w, b) \
  (((w) >> (b)) & 1)
#घोषणा _hrt_set_bit(w, b, v) \
  (((w) & (~(1 << (b)))) | (((v) & 1) << (b)))
#घोषणा _hrt_set_lower_half(w, v) \
  _hrt_set_bits(w, 0, 16, v)
#घोषणा _hrt_set_upper_half(w, v) \
  _hrt_set_bits(w, 16, 16, v)

#पूर्ण_अगर /* _HRT_BITS_H */
