<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright तऊ 2001-2010 David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <यंत्र/byteorder.h>

#घोषणा CFI_HOST_ENDIAN 1
#घोषणा CFI_LITTLE_ENDIAN 2
#घोषणा CFI_BIG_ENDIAN 3

#अगर !defined(CONFIG_MTD_CFI_ADV_OPTIONS) || defined(CONFIG_MTD_CFI_NOSWAP)
#घोषणा CFI_DEFAULT_ENDIAN CFI_HOST_ENDIAN
#या_अगर defined(CONFIG_MTD_CFI_LE_BYTE_SWAP)
#घोषणा CFI_DEFAULT_ENDIAN CFI_LITTLE_ENDIAN
#या_अगर defined(CONFIG_MTD_CFI_BE_BYTE_SWAP)
#घोषणा CFI_DEFAULT_ENDIAN CFI_BIG_ENDIAN
#अन्यथा
#त्रुटि No CFI endianness defined
#पूर्ण_अगर

#घोषणा cfi_शेष(s) ((s)?:CFI_DEFAULT_ENDIAN)
#घोषणा cfi_be(s) (cfi_शेष(s) == CFI_BIG_ENDIAN)
#घोषणा cfi_le(s) (cfi_शेष(s) == CFI_LITTLE_ENDIAN)
#घोषणा cfi_host(s) (cfi_शेष(s) == CFI_HOST_ENDIAN)

#घोषणा cpu_to_cfi8(map, x) (x)
#घोषणा cfi8_to_cpu(map, x) (x)
#घोषणा cpu_to_cfi16(map, x) _cpu_to_cfi(16, (map)->swap, (x))
#घोषणा cpu_to_cfi32(map, x) _cpu_to_cfi(32, (map)->swap, (x))
#घोषणा cpu_to_cfi64(map, x) _cpu_to_cfi(64, (map)->swap, (x))
#घोषणा cfi16_to_cpu(map, x) _cfi_to_cpu(16, (map)->swap, (x))
#घोषणा cfi32_to_cpu(map, x) _cfi_to_cpu(32, (map)->swap, (x))
#घोषणा cfi64_to_cpu(map, x) _cfi_to_cpu(64, (map)->swap, (x))

#घोषणा _cpu_to_cfi(w, s, x) (cfi_host(s)?(x):_swap_to_cfi(w, s, x))
#घोषणा _cfi_to_cpu(w, s, x) (cfi_host(s)?(x):_swap_to_cpu(w, s, x))
#घोषणा _swap_to_cfi(w, s, x) (cfi_be(s)?cpu_to_be##w(x):cpu_to_le##w(x))
#घोषणा _swap_to_cpu(w, s, x) (cfi_be(s)?be##w##_to_cpu(x):le##w##_to_cpu(x))
