<शैली गुरु>
/*
 * Wrapper क्रम decompressing XZ-compressed kernel, initramfs, and initrd
 *
 * Author: Lasse Collin <lasse.collin@tukaani.org>
 *
 * This file has been put पूर्णांकo the खुला करोमुख्य.
 * You can करो whatever you want with this file.
 */

/*
 * Important notes about in-place decompression
 *
 * At least on x86, the kernel is decompressed in place: the compressed data
 * is placed to the end of the output buffer, and the decompressor overग_लिखोs
 * most of the compressed data. There must be enough safety margin to
 * guarantee that the ग_लिखो position is always behind the पढ़ो position.
 *
 * The safety margin क्रम XZ with LZMA2 or BCJ+LZMA2 is calculated below.
 * Note that the margin with XZ is bigger than with Deflate (gzip)!
 *
 * The worst हाल क्रम in-place decompression is that the beginning of
 * the file is compressed extremely well, and the rest of the file is
 * uncompressible. Thus, we must look क्रम worst-हाल expansion when the
 * compressor is encoding uncompressible data.
 *
 * The काष्ठाure of the .xz file in हाल of a compresed kernel is as follows.
 * Sizes (as bytes) of the fields are in parenthesis.
 *
 *    Stream Header (12)
 *    Block Header:
 *      Block Header (8-12)
 *      Compressed Data (N)
 *      Block Padding (0-3)
 *      CRC32 (4)
 *    Index (8-20)
 *    Stream Footer (12)
 *
 * Normally there is exactly one Block, but let's assume that there are
 * 2-4 Blocks just in हाल. Because Stream Header and also Block Header
 * of the first Block करोn't make the decompressor produce any uncompressed
 * data, we can ignore them from our calculations. Block Headers of possible
 * additional Blocks have to be taken पूर्णांकo account still. With these
 * assumptions, it is safe to assume that the total header overhead is
 * less than 128 bytes.
 *
 * Compressed Data contains LZMA2 or BCJ+LZMA2 encoded data. Since BCJ
 * करोesn't change the size of the data, it is enough to calculate the
 * safety margin क्रम LZMA2.
 *
 * LZMA2 stores the data in chunks. Each chunk has a header whose size is
 * a maximum of 6 bytes, but to get round 2^n numbers, let's assume that
 * the maximum chunk header size is 8 bytes. After the chunk header, there
 * may be up to 64 KiB of actual payload in the chunk. Often the payload is
 * quite a bit smaller though; to be safe, let's assume that an average
 * chunk has only 32 KiB of payload.
 *
 * The maximum uncompressed size of the payload is 2 MiB. The minimum
 * uncompressed size of the payload is in practice never less than the
 * payload size itself. The LZMA2 क्रमmat would allow uncompressed size
 * to be less than the payload size, but no sane compressor creates such
 * files. LZMA2 supports storing uncompressible data in uncompressed क्रमm,
 * so there's never a need to create payloads whose uncompressed size is
 * smaller than the compressed size.
 *
 * The assumption, that the uncompressed size of the payload is never
 * smaller than the payload itself, is valid only when talking about
 * the payload as a whole. It is possible that the payload has parts where
 * the decompressor consumes more input than it produces output. Calculating
 * the worst हाल क्रम this would be tricky. Instead of trying to करो that,
 * let's simply make sure that the decompressor never overग_लिखोs any bytes
 * of the payload which it is currently पढ़ोing.
 *
 * Now we have enough inक्रमmation to calculate the safety margin. We need
 *   - 128 bytes क्रम the .xz file क्रमmat headers;
 *   - 8 bytes per every 32 KiB of uncompressed size (one LZMA2 chunk header
 *     per chunk, each chunk having average payload size of 32 KiB); and
 *   - 64 KiB (biggest possible LZMA2 chunk payload size) to make sure that
 *     the decompressor never overग_लिखोs anything from the LZMA2 chunk
 *     payload it is currently पढ़ोing.
 *
 * We get the following क्रमmula:
 *
 *    safety_margin = 128 + uncompressed_size * 8 / 32768 + 65536
 *                  = 128 + (uncompressed_size >> 12) + 65536
 *
 * For comparison, according to arch/x86/boot/compressed/misc.c, the
 * equivalent क्रमmula क्रम Deflate is this:
 *
 *    safety_margin = 18 + (uncompressed_size >> 12) + 32768
 *
 * Thus, when updating Deflate-only in-place kernel decompressor to
 * support XZ, the fixed overhead has to be increased from 18+32768 bytes
 * to 128+65536 bytes.
 */

/*
 * STATIC is defined to "static" अगर we are being built क्रम kernel
 * decompression (pre-boot code). <linux/decompress/mm.h> will define
 * STATIC to empty अगर it wasn't alपढ़ोy defined. Since we will need to
 * know later अगर we are being used क्रम kernel decompression, we define
 * XZ_PREBOOT here.
 */
#अगर_घोषित STATIC
#	define XZ_PREBOOT
#पूर्ण_अगर
#अगर_घोषित __KERNEL__
#	include <linux/decompress/mm.h>
#पूर्ण_अगर
#घोषणा XZ_EXTERN STATIC

#अगर_अघोषित XZ_PREBOOT
#	include <linux/slab.h>
#	include <linux/xz.h>
#अन्यथा
/*
 * Use the पूर्णांकernal CRC32 code instead of kernel's CRC32 module, which
 * is not available in early phase of booting.
 */
#घोषणा XZ_INTERNAL_CRC32 1

/*
 * For boot समय use, we enable only the BCJ filter of the current
 * architecture or none अगर no BCJ filter is available क्रम the architecture.
 */
#अगर_घोषित CONFIG_X86
#	define XZ_DEC_X86
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC
#	define XZ_DEC_POWERPC
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM
#	define XZ_DEC_ARM
#पूर्ण_अगर
#अगर_घोषित CONFIG_IA64
#	define XZ_DEC_IA64
#पूर्ण_अगर
#अगर_घोषित CONFIG_SPARC
#	define XZ_DEC_SPARC
#पूर्ण_अगर

/*
 * This will get the basic headers so that memeq() and others
 * can be defined.
 */
#समावेश "xz/xz_private.h"

/*
 * Replace the normal allocation functions with the versions from
 * <linux/decompress/mm.h>. vमुक्त() needs to support vमुक्त(शून्य)
 * when XZ_DYNALLOC is used, but the pre-boot मुक्त() करोesn't support it.
 * Workaround it here because the other decompressors करोn't need it.
 */
#अघोषित kदो_स्मृति
#अघोषित kमुक्त
#अघोषित vदो_स्मृति
#अघोषित vमुक्त
#घोषणा kदो_स्मृति(size, flags) दो_स्मृति(size)
#घोषणा kमुक्त(ptr) मुक्त(ptr)
#घोषणा vदो_स्मृति(size) दो_स्मृति(size)
#घोषणा vमुक्त(ptr) करो अणु अगर (ptr != शून्य) मुक्त(ptr); पूर्ण जबतक (0)

/*
 * FIXME: Not all basic memory functions are provided in architecture-specअगरic
 * files (yet). We define our own versions here क्रम now, but this should be
 * only a temporary solution.
 *
 * memeq and memzero are not used much and any remotely sane implementation
 * is fast enough. स_नकल/स_हटाओ speed matters in multi-call mode, but
 * the kernel image is decompressed in single-call mode, in which only
 * स_नकल speed can matter and only अगर there is a lot of uncompressible data
 * (LZMA2 stores uncompressible chunks in uncompressed क्रमm). Thus, the
 * functions below should just be kept small; it's probably not worth
 * optimizing क्रम speed.
 */

#अगर_अघोषित memeq
अटल bool memeq(स्थिर व्योम *a, स्थिर व्योम *b, माप_प्रकार size)
अणु
	स्थिर uपूर्णांक8_t *x = a;
	स्थिर uपूर्णांक8_t *y = b;
	माप_प्रकार i;

	क्रम (i = 0; i < size; ++i)
		अगर (x[i] != y[i])
			वापस false;

	वापस true;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित memzero
अटल व्योम memzero(व्योम *buf, माप_प्रकार size)
अणु
	uपूर्णांक8_t *b = buf;
	uपूर्णांक8_t *e = b + size;

	जबतक (b != e)
		*b++ = '\0';
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित स_हटाओ
/* Not अटल to aव्योम a conflict with the prototype in the Linux headers. */
व्योम *स_हटाओ(व्योम *dest, स्थिर व्योम *src, माप_प्रकार size)
अणु
	uपूर्णांक8_t *d = dest;
	स्थिर uपूर्णांक8_t *s = src;
	माप_प्रकार i;

	अगर (d < s) अणु
		क्रम (i = 0; i < size; ++i)
			d[i] = s[i];
	पूर्ण अन्यथा अगर (d > s) अणु
		i = size;
		जबतक (i-- > 0)
			d[i] = s[i];
	पूर्ण

	वापस dest;
पूर्ण
#पूर्ण_अगर

/*
 * Since we need स_हटाओ anyway, would use it as स_नकल too.
 * Commented out क्रम now to aव्योम अवरोधing things.
 */
/*
#अगर_अघोषित स_नकल
#	define स_नकल स_हटाओ
#पूर्ण_अगर
*/

#समावेश "xz/xz_crc32.c"
#समावेश "xz/xz_dec_stream.c"
#समावेश "xz/xz_dec_lzma2.c"
#समावेश "xz/xz_dec_bcj.c"

#पूर्ण_अगर /* XZ_PREBOOT */

/* Size of the input and output buffers in multi-call mode */
#घोषणा XZ_IOBUF_SIZE 4096

/*
 * This function implements the API defined in <linux/decompress/generic.h>.
 *
 * This wrapper will स्वतःmatically choose single-call or multi-call mode
 * of the native XZ decoder API. The single-call mode can be used only when
 * both input and output buffers are available as a single chunk, i.e. when
 * fill() and flush() won't be used.
 */
STATIC पूर्णांक INIT unxz(अचिन्हित अक्षर *in, दीर्घ in_size,
		     दीर्घ (*fill)(व्योम *dest, अचिन्हित दीर्घ size),
		     दीर्घ (*flush)(व्योम *src, अचिन्हित दीर्घ size),
		     अचिन्हित अक्षर *out, दीर्घ *in_used,
		     व्योम (*error)(अक्षर *x))
अणु
	काष्ठा xz_buf b;
	काष्ठा xz_dec *s;
	क्रमागत xz_ret ret;
	bool must_मुक्त_in = false;

#अगर XZ_INTERNAL_CRC32
	xz_crc32_init();
#पूर्ण_अगर

	अगर (in_used != शून्य)
		*in_used = 0;

	अगर (fill == शून्य && flush == शून्य)
		s = xz_dec_init(XZ_SINGLE, 0);
	अन्यथा
		s = xz_dec_init(XZ_DYNALLOC, (uपूर्णांक32_t)-1);

	अगर (s == शून्य)
		जाओ error_alloc_state;

	अगर (flush == शून्य) अणु
		b.out = out;
		b.out_size = (माप_प्रकार)-1;
	पूर्ण अन्यथा अणु
		b.out_size = XZ_IOBUF_SIZE;
		b.out = दो_स्मृति(XZ_IOBUF_SIZE);
		अगर (b.out == शून्य)
			जाओ error_alloc_out;
	पूर्ण

	अगर (in == शून्य) अणु
		must_मुक्त_in = true;
		in = दो_स्मृति(XZ_IOBUF_SIZE);
		अगर (in == शून्य)
			जाओ error_alloc_in;
	पूर्ण

	b.in = in;
	b.in_pos = 0;
	b.in_size = in_size;
	b.out_pos = 0;

	अगर (fill == शून्य && flush == शून्य) अणु
		ret = xz_dec_run(s, &b);
	पूर्ण अन्यथा अणु
		करो अणु
			अगर (b.in_pos == b.in_size && fill != शून्य) अणु
				अगर (in_used != शून्य)
					*in_used += b.in_pos;

				b.in_pos = 0;

				in_size = fill(in, XZ_IOBUF_SIZE);
				अगर (in_size < 0) अणु
					/*
					 * This isn't an optimal error code
					 * but it probably isn't worth making
					 * a new one either.
					 */
					ret = XZ_BUF_ERROR;
					अवरोध;
				पूर्ण

				b.in_size = in_size;
			पूर्ण

			ret = xz_dec_run(s, &b);

			अगर (flush != शून्य && (b.out_pos == b.out_size
					|| (ret != XZ_OK && b.out_pos > 0))) अणु
				/*
				 * Setting ret here may hide an error
				 * वापसed by xz_dec_run(), but probably
				 * it's not too bad.
				 */
				अगर (flush(b.out, b.out_pos) != (दीर्घ)b.out_pos)
					ret = XZ_BUF_ERROR;

				b.out_pos = 0;
			पूर्ण
		पूर्ण जबतक (ret == XZ_OK);

		अगर (must_मुक्त_in)
			मुक्त(in);

		अगर (flush != शून्य)
			मुक्त(b.out);
	पूर्ण

	अगर (in_used != शून्य)
		*in_used += b.in_pos;

	xz_dec_end(s);

	चयन (ret) अणु
	हाल XZ_STREAM_END:
		वापस 0;

	हाल XZ_MEM_ERROR:
		/* This can occur only in multi-call mode. */
		error("XZ decompressor ran out of memory");
		अवरोध;

	हाल XZ_FORMAT_ERROR:
		error("Input is not in the XZ format (wrong magic bytes)");
		अवरोध;

	हाल XZ_OPTIONS_ERROR:
		error("Input was encoded with settings that are not "
				"supported by this XZ decoder");
		अवरोध;

	हाल XZ_DATA_ERROR:
	हाल XZ_BUF_ERROR:
		error("XZ-compressed data is corrupt");
		अवरोध;

	शेष:
		error("Bug in the XZ decompressor");
		अवरोध;
	पूर्ण

	वापस -1;

error_alloc_in:
	अगर (flush != शून्य)
		मुक्त(b.out);

error_alloc_out:
	xz_dec_end(s);

error_alloc_state:
	error("XZ decompressor ran out of memory");
	वापस -1;
पूर्ण

/*
 * This macro is used by architecture-specअगरic files to decompress
 * the kernel image.
 */
#अगर_घोषित XZ_PREBOOT
STATIC पूर्णांक INIT __decompress(अचिन्हित अक्षर *buf, दीर्घ len,
			   दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ),
			   दीर्घ (*flush)(व्योम*, अचिन्हित दीर्घ),
			   अचिन्हित अक्षर *out_buf, दीर्घ olen,
			   दीर्घ *pos,
			   व्योम (*error)(अक्षर *x))
अणु
	वापस unxz(buf, len, fill, flush, out_buf, pos, error);
पूर्ण
#पूर्ण_अगर
