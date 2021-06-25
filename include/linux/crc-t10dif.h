<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_CRC_T10DIF_H
#घोषणा _LINUX_CRC_T10DIF_H

#समावेश <linux/types.h>

#घोषणा CRC_T10DIF_DIGEST_SIZE 2
#घोषणा CRC_T10DIF_BLOCK_SIZE 1
#घोषणा CRC_T10DIF_STRING "crct10dif"

बाह्य __u16 crc_t10dअगर_generic(__u16 crc, स्थिर अचिन्हित अक्षर *buffer,
				माप_प्रकार len);
बाह्य __u16 crc_t10dअगर(अचिन्हित अक्षर स्थिर *, माप_प्रकार);
बाह्य __u16 crc_t10dअगर_update(__u16 crc, अचिन्हित अक्षर स्थिर *, माप_प्रकार);

#पूर्ण_अगर
