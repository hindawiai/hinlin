<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <माला.स>

#समावेश "util/compress.h"
#समावेश "util/debug.h"

पूर्णांक zstd_init(काष्ठा zstd_data *data, पूर्णांक level)
अणु
	माप_प्रकार ret;

	data->dstream = ZSTD_createDStream();
	अगर (data->dstream == शून्य) अणु
		pr_err("Couldn't create decompression stream.\n");
		वापस -1;
	पूर्ण

	ret = ZSTD_initDStream(data->dstream);
	अगर (ZSTD_isError(ret)) अणु
		pr_err("Failed to initialize decompression stream: %s\n", ZSTD_getErrorName(ret));
		वापस -1;
	पूर्ण

	अगर (!level)
		वापस 0;

	data->cstream = ZSTD_createCStream();
	अगर (data->cstream == शून्य) अणु
		pr_err("Couldn't create compression stream.\n");
		वापस -1;
	पूर्ण

	ret = ZSTD_initCStream(data->cstream, level);
	अगर (ZSTD_isError(ret)) अणु
		pr_err("Failed to initialize compression stream: %s\n", ZSTD_getErrorName(ret));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक zstd_fini(काष्ठा zstd_data *data)
अणु
	अगर (data->dstream) अणु
		ZSTD_मुक्तDStream(data->dstream);
		data->dstream = शून्य;
	पूर्ण

	अगर (data->cstream) अणु
		ZSTD_मुक्तCStream(data->cstream);
		data->cstream = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

माप_प्रकार zstd_compress_stream_to_records(काष्ठा zstd_data *data, व्योम *dst, माप_प्रकार dst_size,
				       व्योम *src, माप_प्रकार src_size, माप_प्रकार max_record_size,
				       माप_प्रकार process_header(व्योम *record, माप_प्रकार increment))
अणु
	माप_प्रकार ret, size, compressed = 0;
	ZSTD_inBuffer input = अणु src, src_size, 0 पूर्ण;
	ZSTD_outBuffer output;
	व्योम *record;

	जबतक (input.pos < input.size) अणु
		record = dst;
		size = process_header(record, 0);
		compressed += size;
		dst += size;
		dst_size -= size;
		output = (ZSTD_outBuffer)अणु dst, (dst_size > max_record_size) ?
						max_record_size : dst_size, 0 पूर्ण;
		ret = ZSTD_compressStream(data->cstream, &output, &input);
		ZSTD_flushStream(data->cstream, &output);
		अगर (ZSTD_isError(ret)) अणु
			pr_err("failed to compress %ld bytes: %s\n",
				(दीर्घ)src_size, ZSTD_getErrorName(ret));
			स_नकल(dst, src, src_size);
			वापस src_size;
		पूर्ण
		size = output.pos;
		size = process_header(record, size);
		compressed += size;
		dst += size;
		dst_size -= size;
	पूर्ण

	वापस compressed;
पूर्ण

माप_प्रकार zstd_decompress_stream(काष्ठा zstd_data *data, व्योम *src, माप_प्रकार src_size,
			      व्योम *dst, माप_प्रकार dst_size)
अणु
	माप_प्रकार ret;
	ZSTD_inBuffer input = अणु src, src_size, 0 पूर्ण;
	ZSTD_outBuffer output = अणु dst, dst_size, 0 पूर्ण;

	जबतक (input.pos < input.size) अणु
		ret = ZSTD_decompressStream(data->dstream, &output, &input);
		अगर (ZSTD_isError(ret)) अणु
			pr_err("failed to decompress (B): %zd -> %zd, dst_size %zd : %s\n",
			       src_size, output.size, dst_size, ZSTD_getErrorName(ret));
			अवरोध;
		पूर्ण
		output.dst  = dst + output.pos;
		output.size = dst_size - output.pos;
	पूर्ण

	वापस output.pos;
पूर्ण
