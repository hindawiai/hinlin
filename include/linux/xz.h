<शैली गुरु>
/*
 * XZ decompressor
 *
 * Authors: Lasse Collin <lasse.collin@tukaani.org>
 *          Igor Pavlov <https://7-zip.org/>
 *
 * This file has been put पूर्णांकo the खुला करोमुख्य.
 * You can करो whatever you want with this file.
 */

#अगर_अघोषित XZ_H
#घोषणा XZ_H

#अगर_घोषित __KERNEL__
#	include <linux/मानकघोष.स>
#	include <linux/types.h>
#अन्यथा
#	include <मानकघोष.स>
#	include <मानक_निवेशt.h>
#पूर्ण_अगर

/* In Linux, this is used to make बाह्य functions अटल when needed. */
#अगर_अघोषित XZ_EXTERN
#	define XZ_EXTERN बाह्य
#पूर्ण_अगर

/**
 * क्रमागत xz_mode - Operation mode
 *
 * @XZ_SINGLE:              Single-call mode. This uses less RAM than
 *                          multi-call modes, because the LZMA2
 *                          dictionary करोesn't need to be allocated as
 *                          part of the decoder state. All required data
 *                          काष्ठाures are allocated at initialization,
 *                          so xz_dec_run() cannot वापस XZ_MEM_ERROR.
 * @XZ_PREALLOC:            Multi-call mode with pपुनः_स्मृतिated LZMA2
 *                          dictionary buffer. All data काष्ठाures are
 *                          allocated at initialization, so xz_dec_run()
 *                          cannot वापस XZ_MEM_ERROR.
 * @XZ_DYNALLOC:            Multi-call mode. The LZMA2 dictionary is
 *                          allocated once the required size has been
 *                          parsed from the stream headers. If the
 *                          allocation fails, xz_dec_run() will वापस
 *                          XZ_MEM_ERROR.
 *
 * It is possible to enable support only क्रम a subset of the above
 * modes at compile समय by defining XZ_DEC_SINGLE, XZ_DEC_PREALLOC,
 * or XZ_DEC_DYNALLOC. The xz_dec kernel module is always compiled
 * with support क्रम all operation modes, but the preboot code may
 * be built with fewer features to minimize code size.
 */
क्रमागत xz_mode अणु
	XZ_SINGLE,
	XZ_PREALLOC,
	XZ_DYNALLOC
पूर्ण;

/**
 * क्रमागत xz_ret - Return codes
 * @XZ_OK:                  Everything is OK so far. More input or more
 *                          output space is required to जारी. This
 *                          वापस code is possible only in multi-call mode
 *                          (XZ_PREALLOC or XZ_DYNALLOC).
 * @XZ_STREAM_END:          Operation finished successfully.
 * @XZ_UNSUPPORTED_CHECK:   Integrity check type is not supported. Decoding
 *                          is still possible in multi-call mode by simply
 *                          calling xz_dec_run() again.
 *                          Note that this वापस value is used only अगर
 *                          XZ_DEC_ANY_CHECK was defined at build समय,
 *                          which is not used in the kernel. Unsupported
 *                          check types वापस XZ_OPTIONS_ERROR अगर
 *                          XZ_DEC_ANY_CHECK was not defined at build समय.
 * @XZ_MEM_ERROR:           Allocating memory failed. This वापस code is
 *                          possible only अगर the decoder was initialized
 *                          with XZ_DYNALLOC. The amount of memory that was
 *                          tried to be allocated was no more than the
 *                          dict_max argument given to xz_dec_init().
 * @XZ_MEMLIMIT_ERROR:      A bigger LZMA2 dictionary would be needed than
 *                          allowed by the dict_max argument given to
 *                          xz_dec_init(). This वापस value is possible
 *                          only in multi-call mode (XZ_PREALLOC or
 *                          XZ_DYNALLOC); the single-call mode (XZ_SINGLE)
 *                          ignores the dict_max argument.
 * @XZ_FORMAT_ERROR:        File क्रमmat was not recognized (wrong magic
 *                          bytes).
 * @XZ_OPTIONS_ERROR:       This implementation करोesn't support the requested
 *                          compression options. In the decoder this means
 *                          that the header CRC32 matches, but the header
 *                          itself specअगरies something that we करोn't support.
 * @XZ_DATA_ERROR:          Compressed data is corrupt.
 * @XZ_BUF_ERROR:           Cannot make any progress. Details are slightly
 *                          dअगरferent between multi-call and single-call
 *                          mode; more inक्रमmation below.
 *
 * In multi-call mode, XZ_BUF_ERROR is वापसed when two consecutive calls
 * to XZ code cannot consume any input and cannot produce any new output.
 * This happens when there is no new input available, or the output buffer
 * is full जबतक at least one output byte is still pending. Assuming your
 * code is not buggy, you can get this error only when decoding a compressed
 * stream that is truncated or otherwise corrupt.
 *
 * In single-call mode, XZ_BUF_ERROR is वापसed only when the output buffer
 * is too small or the compressed input is corrupt in a way that makes the
 * decoder produce more output than the caller expected. When it is
 * (relatively) clear that the compressed input is truncated, XZ_DATA_ERROR
 * is used instead of XZ_BUF_ERROR.
 */
क्रमागत xz_ret अणु
	XZ_OK,
	XZ_STREAM_END,
	XZ_UNSUPPORTED_CHECK,
	XZ_MEM_ERROR,
	XZ_MEMLIMIT_ERROR,
	XZ_FORMAT_ERROR,
	XZ_OPTIONS_ERROR,
	XZ_DATA_ERROR,
	XZ_BUF_ERROR
पूर्ण;

/**
 * काष्ठा xz_buf - Passing input and output buffers to XZ code
 * @in:         Beginning of the input buffer. This may be शून्य अगर and only
 *              अगर in_pos is equal to in_size.
 * @in_pos:     Current position in the input buffer. This must not exceed
 *              in_size.
 * @in_size:    Size of the input buffer
 * @out:        Beginning of the output buffer. This may be शून्य अगर and only
 *              अगर out_pos is equal to out_size.
 * @out_pos:    Current position in the output buffer. This must not exceed
 *              out_size.
 * @out_size:   Size of the output buffer
 *
 * Only the contents of the output buffer from out[out_pos] onward, and
 * the variables in_pos and out_pos are modअगरied by the XZ code.
 */
काष्ठा xz_buf अणु
	स्थिर uपूर्णांक8_t *in;
	माप_प्रकार in_pos;
	माप_प्रकार in_size;

	uपूर्णांक8_t *out;
	माप_प्रकार out_pos;
	माप_प्रकार out_size;
पूर्ण;

/**
 * काष्ठा xz_dec - Opaque type to hold the XZ decoder state
 */
काष्ठा xz_dec;

/**
 * xz_dec_init() - Allocate and initialize a XZ decoder state
 * @mode:       Operation mode
 * @dict_max:   Maximum size of the LZMA2 dictionary (history buffer) क्रम
 *              multi-call decoding. This is ignored in single-call mode
 *              (mode == XZ_SINGLE). LZMA2 dictionary is always 2^n bytes
 *              or 2^n + 2^(n-1) bytes (the latter sizes are less common
 *              in practice), so other values क्रम dict_max करोn't make sense.
 *              In the kernel, dictionary sizes of 64 KiB, 128 KiB, 256 KiB,
 *              512 KiB, and 1 MiB are probably the only reasonable values,
 *              except क्रम kernel and initramfs images where a bigger
 *              dictionary can be fine and useful.
 *
 * Single-call mode (XZ_SINGLE): xz_dec_run() decodes the whole stream at
 * once. The caller must provide enough output space or the decoding will
 * fail. The output space is used as the dictionary buffer, which is why
 * there is no need to allocate the dictionary as part of the decoder's
 * पूर्णांकernal state.
 *
 * Because the output buffer is used as the workspace, streams encoded using
 * a big dictionary are not a problem in single-call mode. It is enough that
 * the output buffer is big enough to hold the actual uncompressed data; it
 * can be smaller than the dictionary size stored in the stream headers.
 *
 * Multi-call mode with pपुनः_स्मृतिated dictionary (XZ_PREALLOC): dict_max bytes
 * of memory is pपुनः_स्मृतिated क्रम the LZMA2 dictionary. This way there is no
 * risk that xz_dec_run() could run out of memory, since xz_dec_run() will
 * never allocate any memory. Instead, अगर the pपुनः_स्मृतिated dictionary is too
 * small क्रम decoding the given input stream, xz_dec_run() will वापस
 * XZ_MEMLIMIT_ERROR. Thus, it is important to know what kind of data will be
 * decoded to aव्योम allocating excessive amount of memory क्रम the dictionary.
 *
 * Multi-call mode with dynamically allocated dictionary (XZ_DYNALLOC):
 * dict_max specअगरies the maximum allowed dictionary size that xz_dec_run()
 * may allocate once it has parsed the dictionary size from the stream
 * headers. This way excessive allocations can be aव्योमed जबतक still
 * limiting the maximum memory usage to a sane value to prevent running the
 * प्रणाली out of memory when decompressing streams from untrusted sources.
 *
 * On success, xz_dec_init() वापसs a poपूर्णांकer to काष्ठा xz_dec, which is
 * पढ़ोy to be used with xz_dec_run(). If memory allocation fails,
 * xz_dec_init() वापसs शून्य.
 */
XZ_EXTERN काष्ठा xz_dec *xz_dec_init(क्रमागत xz_mode mode, uपूर्णांक32_t dict_max);

/**
 * xz_dec_run() - Run the XZ decoder
 * @s:          Decoder state allocated using xz_dec_init()
 * @b:          Input and output buffers
 *
 * The possible वापस values depend on build options and operation mode.
 * See क्रमागत xz_ret क्रम details.
 *
 * Note that अगर an error occurs in single-call mode (वापस value is not
 * XZ_STREAM_END), b->in_pos and b->out_pos are not modअगरied and the
 * contents of the output buffer from b->out[b->out_pos] onward are
 * undefined. This is true even after XZ_BUF_ERROR, because with some filter
 * chains, there may be a second pass over the output buffer, and this pass
 * cannot be properly करोne अगर the output buffer is truncated. Thus, you
 * cannot give the single-call decoder a too small buffer and then expect to
 * get that amount valid data from the beginning of the stream. You must use
 * the multi-call decoder अगर you करोn't want to uncompress the whole stream.
 */
XZ_EXTERN क्रमागत xz_ret xz_dec_run(काष्ठा xz_dec *s, काष्ठा xz_buf *b);

/**
 * xz_dec_reset() - Reset an alपढ़ोy allocated decoder state
 * @s:          Decoder state allocated using xz_dec_init()
 *
 * This function can be used to reset the multi-call decoder state without
 * मुक्तing and पुनः_स्मृतिating memory with xz_dec_end() and xz_dec_init().
 *
 * In single-call mode, xz_dec_reset() is always called in the beginning of
 * xz_dec_run(). Thus, explicit call to xz_dec_reset() is useful only in
 * multi-call mode.
 */
XZ_EXTERN व्योम xz_dec_reset(काष्ठा xz_dec *s);

/**
 * xz_dec_end() - Free the memory allocated क्रम the decoder state
 * @s:          Decoder state allocated using xz_dec_init(). If s is शून्य,
 *              this function करोes nothing.
 */
XZ_EXTERN व्योम xz_dec_end(काष्ठा xz_dec *s);

/*
 * Standalone build (userspace build or in-kernel build क्रम boot समय use)
 * needs a CRC32 implementation. For normal in-kernel use, kernel's own
 * CRC32 module is used instead, and users of this module करोn't need to
 * care about the functions below.
 */
#अगर_अघोषित XZ_INTERNAL_CRC32
#	अगरdef __KERNEL__
#		define XZ_INTERNAL_CRC32 0
#	अन्यथा
#		define XZ_INTERNAL_CRC32 1
#	endअगर
#पूर्ण_अगर

#अगर XZ_INTERNAL_CRC32
/*
 * This must be called beक्रमe any other xz_* function to initialize
 * the CRC32 lookup table.
 */
XZ_EXTERN व्योम xz_crc32_init(व्योम);

/*
 * Update CRC32 value using the polynomial from IEEE-802.3. To start a new
 * calculation, the third argument must be zero. To जारी the calculation,
 * the previously वापसed value is passed as the third argument.
 */
XZ_EXTERN uपूर्णांक32_t xz_crc32(स्थिर uपूर्णांक8_t *buf, माप_प्रकार size, uपूर्णांक32_t crc);
#पूर्ण_अगर
#पूर्ण_अगर
