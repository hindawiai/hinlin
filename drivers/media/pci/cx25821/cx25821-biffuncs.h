<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम the Conexant CX25821 PCIe bridge
 *
 *  Copyright (C) 2009 Conexant Systems Inc.
 *  Authors  <shu.lin@conexant.com>, <hiep.huynh@conexant.com>
 */

#अगर_अघोषित _BITFUNCS_H
#घोषणा _BITFUNCS_H

#घोषणा SetBit(Bit)  (1 << Bit)

अटल अंतरभूत u8 getBit(u32 sample, u8 index)
अणु
	वापस (u8) ((sample >> index) & 1);
पूर्ण

अटल अंतरभूत u32 clearBitAtPos(u32 value, u8 bit)
अणु
	वापस value & ~(1 << bit);
पूर्ण

अटल अंतरभूत u32 setBitAtPos(u32 sample, u8 bit)
अणु
	sample |= (1 << bit);
	वापस sample;

पूर्ण

#पूर्ण_अगर
