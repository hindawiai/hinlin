<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *	crc16.h - CRC-16 routine
 *
 * Implements the standard CRC-16:
 *   Width 16
 *   Poly  0x8005 (x^16 + x^15 + x^2 + 1)
 *   Init  0
 *
 * Copyright (c) 2005 Ben Gardner <bgardner@wabtec.com>
 */

#अगर_अघोषित __CRC16_H
#घोषणा __CRC16_H

#समावेश <linux/types.h>

बाह्य u16 स्थिर crc16_table[256];

बाह्य u16 crc16(u16 crc, स्थिर u8 *buffer, माप_प्रकार len);

अटल अंतरभूत u16 crc16_byte(u16 crc, स्थिर u8 data)
अणु
	वापस (crc >> 8) ^ crc16_table[(crc ^ data) & 0xff];
पूर्ण

#पूर्ण_अगर /* __CRC16_H */

