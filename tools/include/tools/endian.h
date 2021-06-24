<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_ENDIAN_H
#घोषणा _TOOLS_ENDIAN_H

#समावेश <byteswap.h>

#अगर __BYTE_ORDER == __LITTLE_ENDIAN

#अगर_अघोषित htole16
#घोषणा htole16(x) (x)
#पूर्ण_अगर
#अगर_अघोषित htole32
#घोषणा htole32(x) (x)
#पूर्ण_अगर
#अगर_अघोषित htole64
#घोषणा htole64(x) (x)
#पूर्ण_अगर

#अगर_अघोषित le16toh
#घोषणा le16toh(x) (x)
#पूर्ण_अगर

#अगर_अघोषित le32toh
#घोषणा le32toh(x) (x)
#पूर्ण_अगर

#अगर_अघोषित le64toh
#घोषणा le64toh(x) (x)
#पूर्ण_अगर

#अन्यथा /* __BYTE_ORDER */

#अगर_अघोषित htole16
#घोषणा htole16(x) __bswap_16(x)
#पूर्ण_अगर
#अगर_अघोषित htole32
#घोषणा htole32(x) __bswap_32(x)
#पूर्ण_अगर
#अगर_अघोषित htole64
#घोषणा htole64(x) __bswap_64(x)
#पूर्ण_अगर

#अगर_अघोषित le16toh
#घोषणा le16toh(x) __bswap_16(x)
#पूर्ण_अगर

#अगर_अघोषित le32toh
#घोषणा le32toh(x) __bswap_32(x)
#पूर्ण_अगर

#अगर_अघोषित le64toh
#घोषणा le64toh(x) __bswap_64(x)
#पूर्ण_अगर

#पूर्ण_अगर

#पूर्ण_अगर /* _TOOLS_ENDIAN_H */
