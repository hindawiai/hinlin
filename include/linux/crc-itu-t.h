<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *	crc-itu-t.h - CRC ITU-T V.41 routine
 *
 * Implements the standard CRC ITU-T V.41:
 *   Width 16
 *   Poly  0x1021 (x^16 + x^12 + x^15 + 1)
 *   Init  0
 */

#अगर_अघोषित CRC_ITU_T_H
#घोषणा CRC_ITU_T_H

#समावेश <linux/types.h>

बाह्य u16 स्थिर crc_itu_t_table[256];

बाह्य u16 crc_itu_t(u16 crc, स्थिर u8 *buffer, माप_प्रकार len);

अटल अंतरभूत u16 crc_itu_t_byte(u16 crc, स्थिर u8 data)
अणु
	वापस (crc << 8) ^ crc_itu_t_table[((crc >> 8) ^ data) & 0xff];
पूर्ण

#पूर्ण_अगर /* CRC_ITU_T_H */

