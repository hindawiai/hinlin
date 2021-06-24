<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <lzma.h>

पूर्णांक मुख्य(व्योम)
अणु
	lzma_stream strm = LZMA_STREAM_INIT;
	पूर्णांक ret;

	ret = lzma_stream_decoder(&strm, UINT64_MAX, LZMA_CONCATENATED);
	वापस ret ? -1 : 0;
पूर्ण
