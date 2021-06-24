<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Wrapper around the kernel's pre-boot decompression library.
 *
 * Copyright (C) IBM Corporation 2016.
 */

#समावेश "elf.h"
#समावेश "page.h"
#समावेश "string.h"
#समावेश "stdio.h"
#समावेश "ops.h"
#समावेश "reg.h"
#समावेश "types.h"

/*
 * The decompressor_*.c files play #अगर_घोषित games so they can be used in both
 * pre-boot and regular kernel code. We need these definitions to make the
 * includes work.
 */

#घोषणा STATIC अटल
#घोषणा INIT

/*
 * The build process will copy the required zlib source files and headers
 * out of lib/ and "fix" the includes so they करो not pull in other kernel
 * headers.
 */

#अगर_घोषित CONFIG_KERNEL_GZIP
#	include "decompress_inflate.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_XZ
#	include "xz_config.h"
#	include "../../../lib/decompress_unxz.c"
#पूर्ण_अगर

/* globals क्रम tracking the state of the decompression */
अटल अचिन्हित दीर्घ decompressed_bytes;
अटल अचिन्हित दीर्घ limit;
अटल अचिन्हित दीर्घ skip;
अटल अक्षर *output_buffer;

/*
 * flush() is called by __decompress() when the decompressor's scratch buffer is
 * full.
 */
अटल दीर्घ flush(व्योम *v, अचिन्हित दीर्घ buffer_size)
अणु
	अचिन्हित दीर्घ end = decompressed_bytes + buffer_size;
	अचिन्हित दीर्घ size = buffer_size;
	अचिन्हित दीर्घ offset = 0;
	अक्षर *in = v;
	अक्षर *out;

	/*
	 * अगर we hit our decompression limit, we need to fake an error to पात
	 * the in-progress decompression.
	 */
	अगर (decompressed_bytes >= limit)
		वापस -1;

	/* skip this entire block */
	अगर (end <= skip) अणु
		decompressed_bytes += buffer_size;
		वापस buffer_size;
	पूर्ण

	/* skip some data at the start, but keep the rest of the block */
	अगर (decompressed_bytes < skip && end > skip) अणु
		offset = skip - decompressed_bytes;

		in += offset;
		size -= offset;
		decompressed_bytes += offset;
	पूर्ण

	out = &output_buffer[decompressed_bytes - skip];
	size = min(decompressed_bytes + size, limit) - decompressed_bytes;

	स_नकल(out, in, size);
	decompressed_bytes += size;

	वापस buffer_size;
पूर्ण

अटल व्योम prपूर्णांक_err(अक्षर *s)
अणु
	/* suppress the "error" when we terminate the decompressor */
	अगर (decompressed_bytes >= limit)
		वापस;

	म_लिखो("Decompression error: '%s'\n\r", s);
पूर्ण

/**
 * partial_decompress - decompresses part or all of a compressed buffer
 * @inbuf:       input buffer
 * @input_size:  length of the input buffer
 * @outbuf:      input buffer
 * @output_size: length of the input buffer
 * @skip         number of output bytes to ignore
 *
 * This function takes compressed data from inbuf, decompresses and ग_लिखो it to
 * outbuf. Once output_size bytes are written to the output buffer, or the
 * stream is exhausted the function will वापस the number of bytes that were
 * decompressed. Otherwise it will वापस whatever error code the decompressor
 * reported (NB: This is specअगरic to each decompressor type).
 *
 * The skip functionality is मुख्यly there so the program and discover
 * the size of the compressed image so that it can ask firmware (अगर present)
 * क्रम an appropriately sized buffer.
 */
दीर्घ partial_decompress(व्योम *inbuf, अचिन्हित दीर्घ input_size,
	व्योम *outbuf, अचिन्हित दीर्घ output_size, अचिन्हित दीर्घ _skip)
अणु
	पूर्णांक ret;

	/*
	 * The skipped bytes needs to be included in the size of data we want
	 * to decompress.
	 */
	output_size += _skip;

	decompressed_bytes = 0;
	output_buffer = outbuf;
	limit = output_size;
	skip = _skip;

	ret = __decompress(inbuf, input_size, शून्य, flush, outbuf,
		output_size, शून्य, prपूर्णांक_err);

	/*
	 * If decompression was पातed due to an actual error rather than
	 * a fake error that we used to पात, then we should report it.
	 */
	अगर (decompressed_bytes < limit)
		वापस ret;

	वापस decompressed_bytes - skip;
पूर्ण
