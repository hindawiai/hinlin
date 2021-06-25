<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_CRC_CCITT_H
#घोषणा _LINUX_CRC_CCITT_H

#समावेश <linux/types.h>

बाह्य u16 स्थिर crc_ccitt_table[256];
बाह्य u16 स्थिर crc_ccitt_false_table[256];

बाह्य u16 crc_ccitt(u16 crc, स्थिर u8 *buffer, माप_प्रकार len);
बाह्य u16 crc_ccitt_false(u16 crc, स्थिर u8 *buffer, माप_प्रकार len);

अटल अंतरभूत u16 crc_ccitt_byte(u16 crc, स्थिर u8 c)
अणु
	वापस (crc >> 8) ^ crc_ccitt_table[(crc ^ c) & 0xff];
पूर्ण

अटल अंतरभूत u16 crc_ccitt_false_byte(u16 crc, स्थिर u8 c)
अणु
    वापस (crc << 8) ^ crc_ccitt_false_table[(crc >> 8) ^ c];
पूर्ण

#पूर्ण_अगर /* _LINUX_CRC_CCITT_H */
