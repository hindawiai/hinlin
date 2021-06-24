<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PERF_COMPRESS_H
#घोषणा PERF_COMPRESS_H

#समावेश <stdbool.h>
#अगर_घोषित HAVE_ZSTD_SUPPORT
#समावेश <zstd.h>
#पूर्ण_अगर

#अगर_घोषित HAVE_ZLIB_SUPPORT
पूर्णांक gzip_decompress_to_file(स्थिर अक्षर *input, पूर्णांक output_fd);
bool gzip_is_compressed(स्थिर अक्षर *input);
#पूर्ण_अगर

#अगर_घोषित HAVE_LZMA_SUPPORT
पूर्णांक lzma_decompress_to_file(स्थिर अक्षर *input, पूर्णांक output_fd);
bool lzma_is_compressed(स्थिर अक्षर *input);
#पूर्ण_अगर

काष्ठा zstd_data अणु
#अगर_घोषित HAVE_ZSTD_SUPPORT
	ZSTD_CStream	*cstream;
	ZSTD_DStream	*dstream;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित HAVE_ZSTD_SUPPORT

पूर्णांक zstd_init(काष्ठा zstd_data *data, पूर्णांक level);
पूर्णांक zstd_fini(काष्ठा zstd_data *data);

माप_प्रकार zstd_compress_stream_to_records(काष्ठा zstd_data *data, व्योम *dst, माप_प्रकार dst_size,
				       व्योम *src, माप_प्रकार src_size, माप_प्रकार max_record_size,
				       माप_प्रकार process_header(व्योम *record, माप_प्रकार increment));

माप_प्रकार zstd_decompress_stream(काष्ठा zstd_data *data, व्योम *src, माप_प्रकार src_size,
			      व्योम *dst, माप_प्रकार dst_size);
#अन्यथा /* !HAVE_ZSTD_SUPPORT */

अटल अंतरभूत पूर्णांक zstd_init(काष्ठा zstd_data *data __maybe_unused, पूर्णांक level __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक zstd_fini(काष्ठा zstd_data *data __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
माप_प्रकार zstd_compress_stream_to_records(काष्ठा zstd_data *data __maybe_unused,
				       व्योम *dst __maybe_unused, माप_प्रकार dst_size __maybe_unused,
				       व्योम *src __maybe_unused, माप_प्रकार src_size __maybe_unused,
				       माप_प्रकार max_record_size __maybe_unused,
				       माप_प्रकार process_header(व्योम *record, माप_प्रकार increment) __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत माप_प्रकार zstd_decompress_stream(काष्ठा zstd_data *data __maybe_unused, व्योम *src __maybe_unused,
					    माप_प्रकार src_size __maybe_unused, व्योम *dst __maybe_unused,
					    माप_प्रकार dst_size __maybe_unused)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* PERF_COMPRESS_H */
