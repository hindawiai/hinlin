<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Important notes about in-place decompression
 *
 * At least on x86, the kernel is decompressed in place: the compressed data
 * is placed to the end of the output buffer, and the decompressor overग_लिखोs
 * most of the compressed data. There must be enough safety margin to
 * guarantee that the ग_लिखो position is always behind the पढ़ो position.
 *
 * The safety margin क्रम ZSTD with a 128 KB block size is calculated below.
 * Note that the margin with ZSTD is bigger than with GZIP or XZ!
 *
 * The worst हाल क्रम in-place decompression is that the beginning of
 * the file is compressed extremely well, and the rest of the file is
 * uncompressible. Thus, we must look क्रम worst-हाल expansion when the
 * compressor is encoding uncompressible data.
 *
 * The काष्ठाure of the .zst file in हाल of a compresed kernel is as follows.
 * Maximum sizes (as bytes) of the fields are in parenthesis.
 *
 *    Frame Header: (18)
 *    Blocks: (N)
 *    Checksum: (4)
 *
 * The frame header and checksum overhead is at most 22 bytes.
 *
 * ZSTD stores the data in blocks. Each block has a header whose size is
 * a 3 bytes. After the block header, there is up to 128 KB of payload.
 * The maximum uncompressed size of the payload is 128 KB. The minimum
 * uncompressed size of the payload is never less than the payload size
 * (excluding the block header).
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
 *   - 22 bytes क्रम the .zst file क्रमmat headers;
 *   - 3 bytes per every 128 KiB of uncompressed size (one block header per
 *     block); and
 *   - 128 KiB (biggest possible zstd block size) to make sure that the
 *     decompressor never overग_लिखोs anything from the block it is currently
 *     पढ़ोing.
 *
 * We get the following क्रमmula:
 *
 *    safety_margin = 22 + uncompressed_size * 3 / 131072 + 131072
 *                 <= 22 + (uncompressed_size >> 15) + 131072
 */

/*
 * Preboot environments #समावेश "path/to/decompress_unzstd.c".
 * All of the source files we depend on must be #समावेशd.
 * zstd's only source dependeny is xxhash, which has no source
 * dependencies.
 *
 * When UNZSTD_PREBOOT is defined we declare __decompress(), which is
 * used क्रम kernel decompression, instead of unzstd().
 *
 * Define __DISABLE_EXPORTS in preboot environments to prevent symbols
 * from xxhash and zstd from being exported by the EXPORT_SYMBOL macro.
 */
#अगर_घोषित STATIC
# define UNZSTD_PREBOOT
# include "xxhash.c"
# include "zstd/entropy_common.c"
# include "zstd/fse_decompress.c"
# include "zstd/huf_decompress.c"
# include "zstd/zstd_common.c"
# include "zstd/decompress.c"
#पूर्ण_अगर

#समावेश <linux/decompress/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/zstd.h>

/* 128MB is the maximum winकरोw size supported by zstd. */
#घोषणा ZSTD_WINDOWSIZE_MAX	(1 << ZSTD_WINDOWLOG_MAX)
/*
 * Size of the input and output buffers in multi-call mode.
 * Pick a larger size because it isn't used during kernel decompression,
 * since that is single pass, and we have to allocate a large buffer क्रम
 * zstd's winकरोw anyway. The larger size speeds up initramfs decompression.
 */
#घोषणा ZSTD_IOBUF_SIZE		(1 << 17)

अटल पूर्णांक INIT handle_zstd_error(माप_प्रकार ret, व्योम (*error)(अक्षर *x))
अणु
	स्थिर पूर्णांक err = ZSTD_getErrorCode(ret);

	अगर (!ZSTD_isError(ret))
		वापस 0;

	चयन (err) अणु
	हाल ZSTD_error_memory_allocation:
		error("ZSTD decompressor ran out of memory");
		अवरोध;
	हाल ZSTD_error_prefix_unknown:
		error("Input is not in the ZSTD format (wrong magic bytes)");
		अवरोध;
	हाल ZSTD_error_dstSize_tooSmall:
	हाल ZSTD_error_corruption_detected:
	हाल ZSTD_error_checksum_wrong:
		error("ZSTD-compressed data is corrupt");
		अवरोध;
	शेष:
		error("ZSTD-compressed data is probably corrupt");
		अवरोध;
	पूर्ण
	वापस -1;
पूर्ण

/*
 * Handle the हाल where we have the entire input and output in one segment.
 * We can allocate less memory (no circular buffer क्रम the sliding winकरोw),
 * and aव्योम some स_नकल() calls.
 */
अटल पूर्णांक INIT decompress_single(स्थिर u8 *in_buf, दीर्घ in_len, u8 *out_buf,
				  दीर्घ out_len, दीर्घ *in_pos,
				  व्योम (*error)(अक्षर *x))
अणु
	स्थिर माप_प्रकार wksp_size = ZSTD_DCtxWorkspaceBound();
	व्योम *wksp = large_दो_स्मृति(wksp_size);
	ZSTD_DCtx *dctx = ZSTD_initDCtx(wksp, wksp_size);
	पूर्णांक err;
	माप_प्रकार ret;

	अगर (dctx == शून्य) अणु
		error("Out of memory while allocating ZSTD_DCtx");
		err = -1;
		जाओ out;
	पूर्ण
	/*
	 * Find out how large the frame actually is, there may be junk at
	 * the end of the frame that ZSTD_decompressDCtx() can't handle.
	 */
	ret = ZSTD_findFrameCompressedSize(in_buf, in_len);
	err = handle_zstd_error(ret, error);
	अगर (err)
		जाओ out;
	in_len = (दीर्घ)ret;

	ret = ZSTD_decompressDCtx(dctx, out_buf, out_len, in_buf, in_len);
	err = handle_zstd_error(ret, error);
	अगर (err)
		जाओ out;

	अगर (in_pos != शून्य)
		*in_pos = in_len;

	err = 0;
out:
	अगर (wksp != शून्य)
		large_मुक्त(wksp);
	वापस err;
पूर्ण

अटल पूर्णांक INIT __unzstd(अचिन्हित अक्षर *in_buf, दीर्घ in_len,
			 दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ),
			 दीर्घ (*flush)(व्योम*, अचिन्हित दीर्घ),
			 अचिन्हित अक्षर *out_buf, दीर्घ out_len,
			 दीर्घ *in_pos,
			 व्योम (*error)(अक्षर *x))
अणु
	ZSTD_inBuffer in;
	ZSTD_outBuffer out;
	ZSTD_frameParams params;
	व्योम *in_allocated = शून्य;
	व्योम *out_allocated = शून्य;
	व्योम *wksp = शून्य;
	माप_प्रकार wksp_size;
	ZSTD_DStream *dstream;
	पूर्णांक err;
	माप_प्रकार ret;

	/*
	 * ZSTD decompression code won't be happy अगर the buffer size is so big
	 * that its end address overflows. When the size is not provided, make
	 * it as big as possible without having the end address overflow.
	 */
	अगर (out_len == 0)
		out_len = UINTPTR_MAX - (uपूर्णांकptr_t)out_buf;

	अगर (fill == शून्य && flush == शून्य)
		/*
		 * We can decompress faster and with less memory when we have a
		 * single chunk.
		 */
		वापस decompress_single(in_buf, in_len, out_buf, out_len,
					 in_pos, error);

	/*
	 * If in_buf is not provided, we must be using fill(), so allocate
	 * a large enough buffer. If it is provided, it must be at least
	 * ZSTD_IOBUF_SIZE large.
	 */
	अगर (in_buf == शून्य) अणु
		in_allocated = large_दो_स्मृति(ZSTD_IOBUF_SIZE);
		अगर (in_allocated == शून्य) अणु
			error("Out of memory while allocating input buffer");
			err = -1;
			जाओ out;
		पूर्ण
		in_buf = in_allocated;
		in_len = 0;
	पूर्ण
	/* Read the first chunk, since we need to decode the frame header. */
	अगर (fill != शून्य)
		in_len = fill(in_buf, ZSTD_IOBUF_SIZE);
	अगर (in_len < 0) अणु
		error("ZSTD-compressed data is truncated");
		err = -1;
		जाओ out;
	पूर्ण
	/* Set the first non-empty input buffer. */
	in.src = in_buf;
	in.pos = 0;
	in.size = in_len;
	/* Allocate the output buffer अगर we are using flush(). */
	अगर (flush != शून्य) अणु
		out_allocated = large_दो_स्मृति(ZSTD_IOBUF_SIZE);
		अगर (out_allocated == शून्य) अणु
			error("Out of memory while allocating output buffer");
			err = -1;
			जाओ out;
		पूर्ण
		out_buf = out_allocated;
		out_len = ZSTD_IOBUF_SIZE;
	पूर्ण
	/* Set the output buffer. */
	out.dst = out_buf;
	out.pos = 0;
	out.size = out_len;

	/*
	 * We need to know the winकरोw size to allocate the ZSTD_DStream.
	 * Since we are streaming, we need to allocate a buffer क्रम the sliding
	 * winकरोw. The winकरोw size varies from 1 KB to ZSTD_WINDOWSIZE_MAX
	 * (8 MB), so it is important to use the actual value so as not to
	 * waste memory when it is smaller.
	 */
	ret = ZSTD_getFrameParams(&params, in.src, in.size);
	err = handle_zstd_error(ret, error);
	अगर (err)
		जाओ out;
	अगर (ret != 0) अणु
		error("ZSTD-compressed data has an incomplete frame header");
		err = -1;
		जाओ out;
	पूर्ण
	अगर (params.winकरोwSize > ZSTD_WINDOWSIZE_MAX) अणु
		error("ZSTD-compressed data has too large a window size");
		err = -1;
		जाओ out;
	पूर्ण

	/*
	 * Allocate the ZSTD_DStream now that we know how much memory is
	 * required.
	 */
	wksp_size = ZSTD_DStreamWorkspaceBound(params.winकरोwSize);
	wksp = large_दो_स्मृति(wksp_size);
	dstream = ZSTD_initDStream(params.winकरोwSize, wksp, wksp_size);
	अगर (dstream == शून्य) अणु
		error("Out of memory while allocating ZSTD_DStream");
		err = -1;
		जाओ out;
	पूर्ण

	/*
	 * Decompression loop:
	 * Read more data अगर necessary (error अगर no more data can be पढ़ो).
	 * Call the decompression function, which वापसs 0 when finished.
	 * Flush any data produced अगर using flush().
	 */
	अगर (in_pos != शून्य)
		*in_pos = 0;
	करो अणु
		/*
		 * If we need to reload data, either we have fill() and can
		 * try to get more data, or we करोn't and the input is truncated.
		 */
		अगर (in.pos == in.size) अणु
			अगर (in_pos != शून्य)
				*in_pos += in.pos;
			in_len = fill ? fill(in_buf, ZSTD_IOBUF_SIZE) : -1;
			अगर (in_len < 0) अणु
				error("ZSTD-compressed data is truncated");
				err = -1;
				जाओ out;
			पूर्ण
			in.pos = 0;
			in.size = in_len;
		पूर्ण
		/* Returns zero when the frame is complete. */
		ret = ZSTD_decompressStream(dstream, &out, &in);
		err = handle_zstd_error(ret, error);
		अगर (err)
			जाओ out;
		/* Flush all of the data produced अगर using flush(). */
		अगर (flush != शून्य && out.pos > 0) अणु
			अगर (out.pos != flush(out.dst, out.pos)) अणु
				error("Failed to flush()");
				err = -1;
				जाओ out;
			पूर्ण
			out.pos = 0;
		पूर्ण
	पूर्ण जबतक (ret != 0);

	अगर (in_pos != शून्य)
		*in_pos += in.pos;

	err = 0;
out:
	अगर (in_allocated != शून्य)
		large_मुक्त(in_allocated);
	अगर (out_allocated != शून्य)
		large_मुक्त(out_allocated);
	अगर (wksp != शून्य)
		large_मुक्त(wksp);
	वापस err;
पूर्ण

#अगर_अघोषित UNZSTD_PREBOOT
STATIC पूर्णांक INIT unzstd(अचिन्हित अक्षर *buf, दीर्घ len,
		       दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ),
		       दीर्घ (*flush)(व्योम*, अचिन्हित दीर्घ),
		       अचिन्हित अक्षर *out_buf,
		       दीर्घ *pos,
		       व्योम (*error)(अक्षर *x))
अणु
	वापस __unzstd(buf, len, fill, flush, out_buf, 0, pos, error);
पूर्ण
#अन्यथा
STATIC पूर्णांक INIT __decompress(अचिन्हित अक्षर *buf, दीर्घ len,
			     दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ),
			     दीर्घ (*flush)(व्योम*, अचिन्हित दीर्घ),
			     अचिन्हित अक्षर *out_buf, दीर्घ out_len,
			     दीर्घ *pos,
			     व्योम (*error)(अक्षर *x))
अणु
	वापस __unzstd(buf, len, fill, flush, out_buf, out_len, pos, error);
पूर्ण
#पूर्ण_अगर
