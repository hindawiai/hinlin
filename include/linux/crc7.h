<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_CRC7_H
#घोषणा _LINUX_CRC7_H
#समावेश <linux/types.h>

बाह्य स्थिर u8 crc7_be_syndrome_table[256];

अटल अंतरभूत u8 crc7_be_byte(u8 crc, u8 data)
अणु
	वापस crc7_be_syndrome_table[crc ^ data];
पूर्ण

बाह्य u8 crc7_be(u8 crc, स्थिर u8 *buffer, माप_प्रकार len);

#पूर्ण_अगर
