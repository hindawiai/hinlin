<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LZO decompressor क्रम the Linux kernel. Code borrowed from the lzo
 * implementation by Markus Franz Xaver Johannes Oberhumer.
 *
 * Linux kernel adaptation:
 * Copyright (C) 2009
 * Albin Tonnerre, Free Electrons <albin.tonnerre@मुक्त-electrons.com>
 *
 * Original code:
 * Copyright (C) 1996-2005 Markus Franz Xaver Johannes Oberhumer
 * All Rights Reserved.
 *
 * Markus F.X.J. Oberhumer
 * <markus@oberhumer.com>
 * http://www.oberhumer.com/खोलोsource/lzop/
 */

#अगर_घोषित STATIC
#घोषणा PREBOOT
#समावेश "lzo/lzo1x_decompress_safe.c"
#अन्यथा
#समावेश <linux/decompress/unlzo.h>
#पूर्ण_अगर

#समावेश <linux/types.h>
#समावेश <linux/lzo.h>
#समावेश <linux/decompress/mm.h>

#समावेश <linux/compiler.h>
#समावेश <यंत्र/unaligned.h>

अटल स्थिर अचिन्हित अक्षर lzop_magic[] = अणु
	0x89, 0x4c, 0x5a, 0x4f, 0x00, 0x0d, 0x0a, 0x1a, 0x0a पूर्ण;

#घोषणा LZO_BLOCK_SIZE        (256*1024l)
#घोषणा HEADER_HAS_FILTER      0x00000800L
#घोषणा HEADER_SIZE_MIN       (9 + 7     + 4 + 8     + 1       + 4)
#घोषणा HEADER_SIZE_MAX       (9 + 7 + 1 + 8 + 8 + 4 + 1 + 255 + 4)

STATIC अंतरभूत दीर्घ INIT parse_header(u8 *input, दीर्घ *skip, दीर्घ in_len)
अणु
	पूर्णांक l;
	u8 *parse = input;
	u8 *end = input + in_len;
	u8 level = 0;
	u16 version;

	/*
	 * Check that there's enough input to possibly have a valid header.
	 * Then it is possible to parse several fields until the minimum
	 * size may have been used.
	 */
	अगर (in_len < HEADER_SIZE_MIN)
		वापस 0;

	/* पढ़ो magic: 9 first bits */
	क्रम (l = 0; l < 9; l++) अणु
		अगर (*parse++ != lzop_magic[l])
			वापस 0;
	पूर्ण
	/* get version (2bytes), skip library version (2),
	 * 'need to be extracted' version (2) and
	 * method (1) */
	version = get_unaligned_be16(parse);
	parse += 7;
	अगर (version >= 0x0940)
		level = *parse++;
	अगर (get_unaligned_be32(parse) & HEADER_HAS_FILTER)
		parse += 8; /* flags + filter info */
	अन्यथा
		parse += 4; /* flags */

	/*
	 * At least mode, mसमय_low, filename length, and checksum must
	 * be left to be parsed. If also mसमय_high is present, it's OK
	 * because the next input buffer check is after पढ़ोing the
	 * filename length.
	 */
	अगर (end - parse < 8 + 1 + 4)
		वापस 0;

	/* skip mode and mसमय_low */
	parse += 8;
	अगर (version >= 0x0940)
		parse += 4;	/* skip mसमय_high */

	l = *parse++;
	/* करोn't care about the file name, and skip checksum */
	अगर (end - parse < l + 4)
		वापस 0;
	parse += l + 4;

	*skip = parse - input;
	वापस 1;
पूर्ण

STATIC पूर्णांक INIT unlzo(u8 *input, दीर्घ in_len,
				दीर्घ (*fill)(व्योम *, अचिन्हित दीर्घ),
				दीर्घ (*flush)(व्योम *, अचिन्हित दीर्घ),
				u8 *output, दीर्घ *posp,
				व्योम (*error) (अक्षर *x))
अणु
	u8 r = 0;
	दीर्घ skip = 0;
	u32 src_len, dst_len;
	माप_प्रकार पंचांगp;
	u8 *in_buf, *in_buf_save, *out_buf;
	पूर्णांक ret = -1;

	अगर (output) अणु
		out_buf = output;
	पूर्ण अन्यथा अगर (!flush) अणु
		error("NULL output pointer and no flush function provided");
		जाओ निकास;
	पूर्ण अन्यथा अणु
		out_buf = दो_स्मृति(LZO_BLOCK_SIZE);
		अगर (!out_buf) अणु
			error("Could not allocate output buffer");
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (input && fill) अणु
		error("Both input pointer and fill function provided, don't know what to do");
		जाओ निकास_1;
	पूर्ण अन्यथा अगर (input) अणु
		in_buf = input;
	पूर्ण अन्यथा अगर (!fill) अणु
		error("NULL input pointer and missing fill function");
		जाओ निकास_1;
	पूर्ण अन्यथा अणु
		in_buf = दो_स्मृति(lzo1x_worst_compress(LZO_BLOCK_SIZE));
		अगर (!in_buf) अणु
			error("Could not allocate input buffer");
			जाओ निकास_1;
		पूर्ण
	पूर्ण
	in_buf_save = in_buf;

	अगर (posp)
		*posp = 0;

	अगर (fill) अणु
		/*
		 * Start from in_buf + HEADER_SIZE_MAX to make it possible
		 * to use स_नकल() to copy the unused data to the beginning
		 * of the buffer. This way स_हटाओ() isn't needed which
		 * is missing from pre-boot environments of most archs.
		 */
		in_buf += HEADER_SIZE_MAX;
		in_len = fill(in_buf, HEADER_SIZE_MAX);
	पूर्ण

	अगर (!parse_header(in_buf, &skip, in_len)) अणु
		error("invalid header");
		जाओ निकास_2;
	पूर्ण
	in_buf += skip;
	in_len -= skip;

	अगर (fill) अणु
		/* Move the unused data to the beginning of the buffer. */
		स_नकल(in_buf_save, in_buf, in_len);
		in_buf = in_buf_save;
	पूर्ण

	अगर (posp)
		*posp = skip;

	क्रम (;;) अणु
		/* पढ़ो uncompressed block size */
		अगर (fill && in_len < 4) अणु
			skip = fill(in_buf + in_len, 4 - in_len);
			अगर (skip > 0)
				in_len += skip;
		पूर्ण
		अगर (in_len < 4) अणु
			error("file corrupted");
			जाओ निकास_2;
		पूर्ण
		dst_len = get_unaligned_be32(in_buf);
		in_buf += 4;
		in_len -= 4;

		/* निकास अगर last block */
		अगर (dst_len == 0) अणु
			अगर (posp)
				*posp += 4;
			अवरोध;
		पूर्ण

		अगर (dst_len > LZO_BLOCK_SIZE) अणु
			error("dest len longer than block size");
			जाओ निकास_2;
		पूर्ण

		/* पढ़ो compressed block size, and skip block checksum info */
		अगर (fill && in_len < 8) अणु
			skip = fill(in_buf + in_len, 8 - in_len);
			अगर (skip > 0)
				in_len += skip;
		पूर्ण
		अगर (in_len < 8) अणु
			error("file corrupted");
			जाओ निकास_2;
		पूर्ण
		src_len = get_unaligned_be32(in_buf);
		in_buf += 8;
		in_len -= 8;

		अगर (src_len <= 0 || src_len > dst_len) अणु
			error("file corrupted");
			जाओ निकास_2;
		पूर्ण

		/* decompress */
		अगर (fill && in_len < src_len) अणु
			skip = fill(in_buf + in_len, src_len - in_len);
			अगर (skip > 0)
				in_len += skip;
		पूर्ण
		अगर (in_len < src_len) अणु
			error("file corrupted");
			जाओ निकास_2;
		पूर्ण
		पंचांगp = dst_len;

		/* When the input data is not compressed at all,
		 * lzo1x_decompress_safe will fail, so call स_नकल()
		 * instead */
		अगर (unlikely(dst_len == src_len))
			स_नकल(out_buf, in_buf, src_len);
		अन्यथा अणु
			r = lzo1x_decompress_safe((u8 *) in_buf, src_len,
						out_buf, &पंचांगp);

			अगर (r != LZO_E_OK || dst_len != पंचांगp) अणु
				error("Compressed data violation");
				जाओ निकास_2;
			पूर्ण
		पूर्ण

		अगर (flush && flush(out_buf, dst_len) != dst_len)
			जाओ निकास_2;
		अगर (output)
			out_buf += dst_len;
		अगर (posp)
			*posp += src_len + 12;

		in_buf += src_len;
		in_len -= src_len;
		अगर (fill) अणु
			/*
			 * If there happens to still be unused data left in
			 * in_buf, move it to the beginning of the buffer.
			 * Use a loop to aव्योम स_हटाओ() dependency.
			 */
			अगर (in_len > 0)
				क्रम (skip = 0; skip < in_len; ++skip)
					in_buf_save[skip] = in_buf[skip];
			in_buf = in_buf_save;
		पूर्ण
	पूर्ण

	ret = 0;
निकास_2:
	अगर (!input)
		मुक्त(in_buf_save);
निकास_1:
	अगर (!output)
		मुक्त(out_buf);
निकास:
	वापस ret;
पूर्ण

#अगर_घोषित PREBOOT
STATIC पूर्णांक INIT __decompress(अचिन्हित अक्षर *buf, दीर्घ len,
			   दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ),
			   दीर्घ (*flush)(व्योम*, अचिन्हित दीर्घ),
			   अचिन्हित अक्षर *out_buf, दीर्घ olen,
			   दीर्घ *pos,
			   व्योम (*error)(अक्षर *x))
अणु
	वापस unlzo(buf, len, fill, flush, out_buf, pos, error);
पूर्ण
#पूर्ण_अगर
