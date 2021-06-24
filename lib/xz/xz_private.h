<शैली गुरु>
/*
 * Private includes and definitions
 *
 * Author: Lasse Collin <lasse.collin@tukaani.org>
 *
 * This file has been put पूर्णांकo the खुला करोमुख्य.
 * You can करो whatever you want with this file.
 */

#अगर_अघोषित XZ_PRIVATE_H
#घोषणा XZ_PRIVATE_H

#अगर_घोषित __KERNEL__
#	include <linux/xz.h>
#	include <linux/kernel.h>
#	include <यंत्र/unaligned.h>
	/* XZ_PREBOOT may be defined only via decompress_unxz.c. */
#	अगरndef XZ_PREBOOT
#		include <linux/slab.h>
#		include <linux/vदो_स्मृति.h>
#		include <linux/माला.स>
#		अगरdef CONFIG_XZ_DEC_X86
#			define XZ_DEC_X86
#		endअगर
#		अगरdef CONFIG_XZ_DEC_POWERPC
#			define XZ_DEC_POWERPC
#		endअगर
#		अगरdef CONFIG_XZ_DEC_IA64
#			define XZ_DEC_IA64
#		endअगर
#		अगरdef CONFIG_XZ_DEC_ARM
#			define XZ_DEC_ARM
#		endअगर
#		अगरdef CONFIG_XZ_DEC_ARMTHUMB
#			define XZ_DEC_ARMTHUMB
#		endअगर
#		अगरdef CONFIG_XZ_DEC_SPARC
#			define XZ_DEC_SPARC
#		endअगर
#		define memeq(a, b, size) (स_भेद(a, b, size) == 0)
#		define memzero(buf, size) स_रखो(buf, 0, size)
#	endअगर
#	define get_le32(p) le32_to_cpup((स्थिर uपूर्णांक32_t *)(p))
#अन्यथा
	/*
	 * For userspace builds, use a separate header to define the required
	 * macros and functions. This makes it easier to adapt the code पूर्णांकo
	 * dअगरferent environments and aव्योमs clutter in the Linux kernel tree.
	 */
#	include "xz_config.h"
#पूर्ण_अगर

/* If no specअगरic decoding mode is requested, enable support क्रम all modes. */
#अगर !defined(XZ_DEC_SINGLE) && !defined(XZ_DEC_PREALLOC) \
		&& !defined(XZ_DEC_DYNALLOC)
#	define XZ_DEC_SINGLE
#	define XZ_DEC_PREALLOC
#	define XZ_DEC_DYNALLOC
#पूर्ण_अगर

/*
 * The DEC_IS_foo(mode) macros are used in "if" statements. If only some
 * of the supported modes are enabled, these macros will evaluate to true or
 * false at compile समय and thus allow the compiler to omit unneeded code.
 */
#अगर_घोषित XZ_DEC_SINGLE
#	define DEC_IS_SINGLE(mode) ((mode) == XZ_SINGLE)
#अन्यथा
#	define DEC_IS_SINGLE(mode) (false)
#पूर्ण_अगर

#अगर_घोषित XZ_DEC_PREALLOC
#	define DEC_IS_PREALLOC(mode) ((mode) == XZ_PREALLOC)
#अन्यथा
#	define DEC_IS_PREALLOC(mode) (false)
#पूर्ण_अगर

#अगर_घोषित XZ_DEC_DYNALLOC
#	define DEC_IS_DYNALLOC(mode) ((mode) == XZ_DYNALLOC)
#अन्यथा
#	define DEC_IS_DYNALLOC(mode) (false)
#पूर्ण_अगर

#अगर !defined(XZ_DEC_SINGLE)
#	define DEC_IS_MULTI(mode) (true)
#या_अगर defined(XZ_DEC_PREALLOC) || defined(XZ_DEC_DYNALLOC)
#	define DEC_IS_MULTI(mode) ((mode) != XZ_SINGLE)
#अन्यथा
#	define DEC_IS_MULTI(mode) (false)
#पूर्ण_अगर

/*
 * If any of the BCJ filter decoders are wanted, define XZ_DEC_BCJ.
 * XZ_DEC_BCJ is used to enable generic support क्रम BCJ decoders.
 */
#अगर_अघोषित XZ_DEC_BCJ
#	अगर defined(XZ_DEC_X86) || defined(XZ_DEC_POWERPC) \
			|| defined(XZ_DEC_IA64) || defined(XZ_DEC_ARM) \
			|| defined(XZ_DEC_ARM) || defined(XZ_DEC_ARMTHUMB) \
			|| defined(XZ_DEC_SPARC)
#		define XZ_DEC_BCJ
#	endअगर
#पूर्ण_अगर

#अगर_अघोषित CRC32_POLY_LE
#घोषणा CRC32_POLY_LE 0xedb88320
#पूर्ण_अगर

/*
 * Allocate memory क्रम LZMA2 decoder. xz_dec_lzma2_reset() must be used
 * beक्रमe calling xz_dec_lzma2_run().
 */
XZ_EXTERN काष्ठा xz_dec_lzma2 *xz_dec_lzma2_create(क्रमागत xz_mode mode,
						   uपूर्णांक32_t dict_max);

/*
 * Decode the LZMA2 properties (one byte) and reset the decoder. Return
 * XZ_OK on success, XZ_MEMLIMIT_ERROR अगर the pपुनः_स्मृतिated dictionary is not
 * big enough, and XZ_OPTIONS_ERROR अगर props indicates something that this
 * decoder करोesn't support.
 */
XZ_EXTERN क्रमागत xz_ret xz_dec_lzma2_reset(काष्ठा xz_dec_lzma2 *s,
					 uपूर्णांक8_t props);

/* Decode raw LZMA2 stream from b->in to b->out. */
XZ_EXTERN क्रमागत xz_ret xz_dec_lzma2_run(काष्ठा xz_dec_lzma2 *s,
				       काष्ठा xz_buf *b);

/* Free the memory allocated क्रम the LZMA2 decoder. */
XZ_EXTERN व्योम xz_dec_lzma2_end(काष्ठा xz_dec_lzma2 *s);

#अगर_घोषित XZ_DEC_BCJ
/*
 * Allocate memory क्रम BCJ decoders. xz_dec_bcj_reset() must be used beक्रमe
 * calling xz_dec_bcj_run().
 */
XZ_EXTERN काष्ठा xz_dec_bcj *xz_dec_bcj_create(bool single_call);

/*
 * Decode the Filter ID of a BCJ filter. This implementation करोesn't
 * support custom start offsets, so no decoding of Filter Properties
 * is needed. Returns XZ_OK अगर the given Filter ID is supported.
 * Otherwise XZ_OPTIONS_ERROR is वापसed.
 */
XZ_EXTERN क्रमागत xz_ret xz_dec_bcj_reset(काष्ठा xz_dec_bcj *s, uपूर्णांक8_t id);

/*
 * Decode raw BCJ + LZMA2 stream. This must be used only अगर there actually is
 * a BCJ filter in the chain. If the chain has only LZMA2, xz_dec_lzma2_run()
 * must be called directly.
 */
XZ_EXTERN क्रमागत xz_ret xz_dec_bcj_run(काष्ठा xz_dec_bcj *s,
				     काष्ठा xz_dec_lzma2 *lzma2,
				     काष्ठा xz_buf *b);

/* Free the memory allocated क्रम the BCJ filters. */
#घोषणा xz_dec_bcj_end(s) kमुक्त(s)
#पूर्ण_अगर

#पूर्ण_अगर
