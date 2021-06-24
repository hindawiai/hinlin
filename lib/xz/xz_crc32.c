<शैली गुरु>
/*
 * CRC32 using the polynomial from IEEE-802.3
 *
 * Authors: Lasse Collin <lasse.collin@tukaani.org>
 *          Igor Pavlov <https://7-zip.org/>
 *
 * This file has been put पूर्णांकo the खुला करोमुख्य.
 * You can करो whatever you want with this file.
 */

/*
 * This is not the fastest implementation, but it is pretty compact.
 * The fastest versions of xz_crc32() on modern CPUs without hardware
 * accelerated CRC inकाष्ठाion are 3-5 बार as fast as this version,
 * but they are bigger and use more memory क्रम the lookup table.
 */

#समावेश "xz_private.h"

/*
 * STATIC_RW_DATA is used in the pre-boot environment on some architectures.
 * See <linux/decompress/mm.h> क्रम details.
 */
#अगर_अघोषित STATIC_RW_DATA
#	define STATIC_RW_DATA अटल
#पूर्ण_अगर

STATIC_RW_DATA uपूर्णांक32_t xz_crc32_table[256];

XZ_EXTERN व्योम xz_crc32_init(व्योम)
अणु
	स्थिर uपूर्णांक32_t poly = CRC32_POLY_LE;

	uपूर्णांक32_t i;
	uपूर्णांक32_t j;
	uपूर्णांक32_t r;

	क्रम (i = 0; i < 256; ++i) अणु
		r = i;
		क्रम (j = 0; j < 8; ++j)
			r = (r >> 1) ^ (poly & ~((r & 1) - 1));

		xz_crc32_table[i] = r;
	पूर्ण

	वापस;
पूर्ण

XZ_EXTERN uपूर्णांक32_t xz_crc32(स्थिर uपूर्णांक8_t *buf, माप_प्रकार size, uपूर्णांक32_t crc)
अणु
	crc = ~crc;

	जबतक (size != 0) अणु
		crc = xz_crc32_table[*buf++ ^ (crc & 0xFF)] ^ (crc >> 8);
		--size;
	पूर्ण

	वापस ~crc;
पूर्ण
