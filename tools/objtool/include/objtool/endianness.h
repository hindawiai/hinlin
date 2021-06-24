<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _OBJTOOL_ENDIANNESS_H
#घोषणा _OBJTOOL_ENDIANNESS_H

#समावेश <arch/endianness.h>
#समावेश <linux/kernel.h>
#समावेश <endian.h>

#अगर_अघोषित __TARGET_BYTE_ORDER
#त्रुटि undefined arch __TARGET_BYTE_ORDER
#पूर्ण_अगर

#अगर __BYTE_ORDER != __TARGET_BYTE_ORDER
#घोषणा __NEED_BSWAP 1
#अन्यथा
#घोषणा __NEED_BSWAP 0
#पूर्ण_अगर

/*
 * Does a byte swap अगर target endianness करोesn't match the host, i.e. cross
 * compilation क्रम little endian on big endian and vice versa.
 * To be used क्रम multi-byte values conversion, which are पढ़ो from / about
 * to be written to a target native endianness ELF file.
 */
#घोषणा bswap_अगर_needed(val)						\
(अणु									\
	__typeof__(val) __ret;						\
	चयन (माप(val)) अणु						\
	हाल 8: __ret = __NEED_BSWAP ? bswap_64(val) : (val); अवरोध;	\
	हाल 4: __ret = __NEED_BSWAP ? bswap_32(val) : (val); अवरोध;	\
	हाल 2: __ret = __NEED_BSWAP ? bswap_16(val) : (val); अवरोध;	\
	शेष:							\
		BUILD_BUG(); अवरोध;					\
	पूर्ण								\
	__ret;								\
पूर्ण)

#पूर्ण_अगर /* _OBJTOOL_ENDIANNESS_H */
