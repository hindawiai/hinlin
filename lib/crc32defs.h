<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Try to choose an implementation variant via Kconfig */
#अगर_घोषित CONFIG_CRC32_SLICEBY8
# define CRC_LE_BITS 64
# define CRC_BE_BITS 64
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRC32_SLICEBY4
# define CRC_LE_BITS 32
# define CRC_BE_BITS 32
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRC32_SARWATE
# define CRC_LE_BITS 8
# define CRC_BE_BITS 8
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRC32_BIT
# define CRC_LE_BITS 1
# define CRC_BE_BITS 1
#पूर्ण_अगर

/*
 * How many bits at a समय to use.  Valid values are 1, 2, 4, 8, 32 and 64.
 * For less perक्रमmance-sensitive, use 4 or 8 to save table size.
 * For larger प्रणालीs choose same as CPU architecture as शेष.
 * This works well on X86_64, SPARC64 प्रणालीs. This may require some
 * elaboration after experiments with other architectures.
 */
#अगर_अघोषित CRC_LE_BITS
#  अगरdef CONFIG_64BIT
#  define CRC_LE_BITS 64
#  अन्यथा
#  define CRC_LE_BITS 32
#  endअगर
#पूर्ण_अगर
#अगर_अघोषित CRC_BE_BITS
#  अगरdef CONFIG_64BIT
#  define CRC_BE_BITS 64
#  अन्यथा
#  define CRC_BE_BITS 32
#  endअगर
#पूर्ण_अगर

/*
 * Little-endian CRC computation.  Used with serial bit streams sent
 * lsbit-first.  Be sure to use cpu_to_le32() to append the computed CRC.
 */
#अगर CRC_LE_BITS > 64 || CRC_LE_BITS < 1 || CRC_LE_BITS == 16 || \
	CRC_LE_BITS & CRC_LE_BITS-1
# error "CRC_LE_BITS must be one of {1, 2, 4, 8, 32, 64}"
#पूर्ण_अगर

/*
 * Big-endian CRC computation.  Used with serial bit streams sent
 * msbit-first.  Be sure to use cpu_to_be32() to append the computed CRC.
 */
#अगर CRC_BE_BITS > 64 || CRC_BE_BITS < 1 || CRC_BE_BITS == 16 || \
	CRC_BE_BITS & CRC_BE_BITS-1
# error "CRC_BE_BITS must be one of {1, 2, 4, 8, 32, 64}"
#पूर्ण_अगर
