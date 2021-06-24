<शैली गुरु>
/*
 * Definitions क्रम handling the .xz file क्रमmat
 *
 * Author: Lasse Collin <lasse.collin@tukaani.org>
 *
 * This file has been put पूर्णांकo the खुला करोमुख्य.
 * You can करो whatever you want with this file.
 */

#अगर_अघोषित XZ_STREAM_H
#घोषणा XZ_STREAM_H

#अगर defined(__KERNEL__) && !XZ_INTERNAL_CRC32
#	include <linux/crc32.h>
#	undef crc32
#	define xz_crc32(buf, size, crc) \
		(~crc32_le(~(uपूर्णांक32_t)(crc), buf, size))
#पूर्ण_अगर

/*
 * See the .xz file क्रमmat specअगरication at
 * https://tukaani.org/xz/xz-file-क्रमmat.txt
 * to understand the container क्रमmat.
 */

#घोषणा STREAM_HEADER_SIZE 12

#घोषणा HEADER_MAGIC "\3757zXZ"
#घोषणा HEADER_MAGIC_SIZE 6

#घोषणा FOOTER_MAGIC "YZ"
#घोषणा FOOTER_MAGIC_SIZE 2

/*
 * Variable-length पूर्णांकeger can hold a 63-bit अचिन्हित पूर्णांकeger or a special
 * value indicating that the value is unknown.
 *
 * Experimental: vli_type can be defined to uपूर्णांक32_t to save a few bytes
 * in code size (no effect on speed). Doing so limits the uncompressed and
 * compressed size of the file to less than 256 MiB and may also weaken
 * error detection slightly.
 */
प्रकार uपूर्णांक64_t vli_type;

#घोषणा VLI_MAX ((vli_type)-1 / 2)
#घोषणा VLI_UNKNOWN ((vli_type)-1)

/* Maximum encoded size of a VLI */
#घोषणा VLI_BYTES_MAX (माप(vli_type) * 8 / 7)

/* Integrity Check types */
क्रमागत xz_check अणु
	XZ_CHECK_NONE = 0,
	XZ_CHECK_CRC32 = 1,
	XZ_CHECK_CRC64 = 4,
	XZ_CHECK_SHA256 = 10
पूर्ण;

/* Maximum possible Check ID */
#घोषणा XZ_CHECK_MAX 15

#पूर्ण_अगर
