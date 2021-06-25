<शैली गुरु>
/* LZ4 Kernel Interface
 *
 * Copyright (C) 2013, LG Electronics, Kyungsik Lee <kyungsik.lee@lge.com>
 * Copyright (C) 2016, Sven Schmidt <4sschmid@inक्रमmatik.uni-hamburg.de>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This file is based on the original header file
 * क्रम LZ4 - Fast LZ compression algorithm.
 *
 * LZ4 - Fast LZ compression algorithm
 * Copyright (C) 2011-2016, Yann Collet.
 * BSD 2-Clause License (http://www.खोलोsource.org/licenses/bsd-license.php)
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are
 * met:
 *	* Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *	* Redistributions in binary क्रमm must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the करोcumentation and/or other materials provided with the
 * distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * You can contact the author at :
 *	- LZ4 homepage : http://www.lz4.org
 *	- LZ4 source repository : https://github.com/lz4/lz4
 */

#अगर_अघोषित __LZ4_H__
#घोषणा __LZ4_H__

#समावेश <linux/types.h>
#समावेश <linux/माला.स>	 /* स_रखो, स_नकल */

/*-************************************************************************
 *	CONSTANTS
 **************************************************************************/
/*
 * LZ4_MEMORY_USAGE :
 * Memory usage क्रमmula : N->2^N Bytes
 * (examples : 10 -> 1KB; 12 -> 4KB ; 16 -> 64KB; 20 -> 1MB; etc.)
 * Increasing memory usage improves compression ratio
 * Reduced memory usage can improve speed, due to cache effect
 * Default value is 14, क्रम 16KB, which nicely fits पूर्णांकo Intel x86 L1 cache
 */
#घोषणा LZ4_MEMORY_USAGE 14

#घोषणा LZ4_MAX_INPUT_SIZE	0x7E000000 /* 2 113 929 216 bytes */
#घोषणा LZ4_COMPRESSBOUND(isize)	(\
	(अचिन्हित पूर्णांक)(isize) > (अचिन्हित पूर्णांक)LZ4_MAX_INPUT_SIZE \
	? 0 \
	: (isize) + ((isize)/255) + 16)

#घोषणा LZ4_ACCELERATION_DEFAULT 1
#घोषणा LZ4_HASHLOG	 (LZ4_MEMORY_USAGE-2)
#घोषणा LZ4_HASHTABLESIZE (1 << LZ4_MEMORY_USAGE)
#घोषणा LZ4_HASH_SIZE_U32 (1 << LZ4_HASHLOG)

#घोषणा LZ4HC_MIN_CLEVEL			3
#घोषणा LZ4HC_DEFAULT_CLEVEL			9
#घोषणा LZ4HC_MAX_CLEVEL			16

#घोषणा LZ4HC_DICTIONARY_LOGSIZE 16
#घोषणा LZ4HC_MAXD (1<<LZ4HC_DICTIONARY_LOGSIZE)
#घोषणा LZ4HC_MAXD_MASK (LZ4HC_MAXD - 1)
#घोषणा LZ4HC_HASH_LOG (LZ4HC_DICTIONARY_LOGSIZE - 1)
#घोषणा LZ4HC_HASHTABLESIZE (1 << LZ4HC_HASH_LOG)
#घोषणा LZ4HC_HASH_MASK (LZ4HC_HASHTABLESIZE - 1)

/*-************************************************************************
 *	STREAMING CONSTANTS AND STRUCTURES
 **************************************************************************/
#घोषणा LZ4_STREAMSIZE_U64 ((1 << (LZ4_MEMORY_USAGE - 3)) + 4)
#घोषणा LZ4_STREAMSIZE	(LZ4_STREAMSIZE_U64 * माप(अचिन्हित दीर्घ दीर्घ))

#घोषणा LZ4_STREAMHCSIZE        262192
#घोषणा LZ4_STREAMHCSIZE_SIZET (262192 / माप(माप_प्रकार))

#घोषणा LZ4_STREAMDECODESIZE_U64	4
#घोषणा LZ4_STREAMDECODESIZE		 (LZ4_STREAMDECODESIZE_U64 * \
	माप(अचिन्हित दीर्घ दीर्घ))

/*
 * LZ4_stream_t - inक्रमmation काष्ठाure to track an LZ4 stream.
 */
प्रकार काष्ठा अणु
	uपूर्णांक32_t hashTable[LZ4_HASH_SIZE_U32];
	uपूर्णांक32_t currentOffset;
	uपूर्णांक32_t initCheck;
	स्थिर uपूर्णांक8_t *dictionary;
	uपूर्णांक8_t *bufferStart;
	uपूर्णांक32_t dictSize;
पूर्ण LZ4_stream_t_पूर्णांकernal;
प्रकार जोड़ अणु
	अचिन्हित दीर्घ दीर्घ table[LZ4_STREAMSIZE_U64];
	LZ4_stream_t_पूर्णांकernal पूर्णांकernal_करोnotuse;
पूर्ण LZ4_stream_t;

/*
 * LZ4_streamHC_t - inक्रमmation काष्ठाure to track an LZ4HC stream.
 */
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक	 hashTable[LZ4HC_HASHTABLESIZE];
	अचिन्हित लघु	 chainTable[LZ4HC_MAXD];
	/* next block to जारी on current prefix */
	स्थिर अचिन्हित अक्षर *end;
	/* All index relative to this position */
	स्थिर अचिन्हित अक्षर *base;
	/* alternate base क्रम extDict */
	स्थिर अचिन्हित अक्षर *dictBase;
	/* below that poपूर्णांक, need extDict */
	अचिन्हित पूर्णांक	 dictLimit;
	/* below that poपूर्णांक, no more dict */
	अचिन्हित पूर्णांक	 lowLimit;
	/* index from which to जारी dict update */
	अचिन्हित पूर्णांक	 nextToUpdate;
	अचिन्हित पूर्णांक	 compressionLevel;
पूर्ण LZ4HC_CCtx_पूर्णांकernal;
प्रकार जोड़ अणु
	माप_प्रकार table[LZ4_STREAMHCSIZE_SIZET];
	LZ4HC_CCtx_पूर्णांकernal पूर्णांकernal_करोnotuse;
पूर्ण LZ4_streamHC_t;

/*
 * LZ4_streamDecode_t - inक्रमmation काष्ठाure to track an
 *	LZ4 stream during decompression.
 *
 * init this काष्ठाure using LZ4_setStreamDecode (or स_रखो()) beक्रमe first use
 */
प्रकार काष्ठा अणु
	स्थिर uपूर्णांक8_t *बाह्यalDict;
	माप_प्रकार extDictSize;
	स्थिर uपूर्णांक8_t *prefixEnd;
	माप_प्रकार prefixSize;
पूर्ण LZ4_streamDecode_t_पूर्णांकernal;
प्रकार जोड़ अणु
	अचिन्हित दीर्घ दीर्घ table[LZ4_STREAMDECODESIZE_U64];
	LZ4_streamDecode_t_पूर्णांकernal पूर्णांकernal_करोnotuse;
पूर्ण LZ4_streamDecode_t;

/*-************************************************************************
 *	SIZE OF STATE
 **************************************************************************/
#घोषणा LZ4_MEM_COMPRESS	LZ4_STREAMSIZE
#घोषणा LZ4HC_MEM_COMPRESS	LZ4_STREAMHCSIZE

/*-************************************************************************
 *	Compression Functions
 **************************************************************************/

/**
 * LZ4_compressBound() - Max. output size in worst हाल szenarios
 * @isize: Size of the input data
 *
 * Return: Max. size LZ4 may output in a "worst case" szenario
 * (data not compressible)
 */
अटल अंतरभूत पूर्णांक LZ4_compressBound(माप_प्रकार isize)
अणु
	वापस LZ4_COMPRESSBOUND(isize);
पूर्ण

/**
 * LZ4_compress_शेष() - Compress data from source to dest
 * @source: source address of the original data
 * @dest: output buffer address of the compressed data
 * @inputSize: size of the input data. Max supported value is LZ4_MAX_INPUT_SIZE
 * @maxOutputSize: full or partial size of buffer 'dest'
 *	which must be alपढ़ोy allocated
 * @wrkmem: address of the working memory.
 *	This requires 'workmem' of LZ4_MEM_COMPRESS.
 *
 * Compresses 'sourceSize' bytes from buffer 'source'
 * पूर्णांकo alपढ़ोy allocated 'dest' buffer of size 'maxOutputSize'.
 * Compression is guaranteed to succeed अगर
 * 'maxOutputSize' >= LZ4_compressBound(inputSize).
 * It also runs faster, so it's a recommended setting.
 * If the function cannot compress 'source' into a more limited 'dest' budget,
 * compression stops *immediately*, and the function result is zero.
 * As a consequence, 'dest' content is not valid.
 *
 * Return: Number of bytes written पूर्णांकo buffer 'dest'
 *	(necessarily <= maxOutputSize) or 0 अगर compression fails
 */
पूर्णांक LZ4_compress_शेष(स्थिर अक्षर *source, अक्षर *dest, पूर्णांक inputSize,
	पूर्णांक maxOutputSize, व्योम *wrkmem);

/**
 * LZ4_compress_fast() - As LZ4_compress_शेष providing an acceleration param
 * @source: source address of the original data
 * @dest: output buffer address of the compressed data
 * @inputSize: size of the input data. Max supported value is LZ4_MAX_INPUT_SIZE
 * @maxOutputSize: full or partial size of buffer 'dest'
 *	which must be alपढ़ोy allocated
 * @acceleration: acceleration factor
 * @wrkmem: address of the working memory.
 *	This requires 'workmem' of LZ4_MEM_COMPRESS.
 *
 * Same as LZ4_compress_शेष(), but allows to select an "acceleration"
 * factor. The larger the acceleration value, the faster the algorithm,
 * but also the lesser the compression. It's a trade-off. It can be fine tuned,
 * with each successive value providing roughly +~3% to speed.
 * An acceleration value of "1" is the same as regular LZ4_compress_शेष()
 * Values <= 0 will be replaced by LZ4_ACCELERATION_DEFAULT, which is 1.
 *
 * Return: Number of bytes written पूर्णांकo buffer 'dest'
 *	(necessarily <= maxOutputSize) or 0 अगर compression fails
 */
पूर्णांक LZ4_compress_fast(स्थिर अक्षर *source, अक्षर *dest, पूर्णांक inputSize,
	पूर्णांक maxOutputSize, पूर्णांक acceleration, व्योम *wrkmem);

/**
 * LZ4_compress_destSize() - Compress as much data as possible
 *	from source to dest
 * @source: source address of the original data
 * @dest: output buffer address of the compressed data
 * @sourceSizePtr: will be modअगरied to indicate how many bytes where पढ़ो
 *	from 'source' to fill 'dest'. New value is necessarily <= old value.
 * @targetDestSize: Size of buffer 'dest' which must be alपढ़ोy allocated
 * @wrkmem: address of the working memory.
 *	This requires 'workmem' of LZ4_MEM_COMPRESS.
 *
 * Reverse the logic, by compressing as much data as possible
 * from 'source' buffer into already allocated buffer 'dest'
 * of size 'targetDestSize'.
 * This function either compresses the entire 'source' content into 'dest'
 * अगर it's large enough, or fill 'dest' buffer completely with as much data as
 * possible from 'source'.
 *
 * Return: Number of bytes written पूर्णांकo 'dest' (necessarily <= targetDestSize)
 *	or 0 अगर compression fails
 */
पूर्णांक LZ4_compress_destSize(स्थिर अक्षर *source, अक्षर *dest, पूर्णांक *sourceSizePtr,
	पूर्णांक targetDestSize, व्योम *wrkmem);

/*-************************************************************************
 *	Decompression Functions
 **************************************************************************/

/**
 * LZ4_decompress_fast() - Decompresses data from 'source' into 'dest'
 * @source: source address of the compressed data
 * @dest: output buffer address of the uncompressed data
 *	which must be alपढ़ोy allocated with 'originalSize' bytes
 * @originalSize: is the original and thereक्रमe uncompressed size
 *
 * Decompresses data from 'source' into 'dest'.
 * This function fully respect memory boundaries क्रम properly क्रमmed
 * compressed data.
 * It is a bit faster than LZ4_decompress_safe().
 * However, it करोes not provide any protection against पूर्णांकentionally
 * modअगरied data stream (malicious input).
 * Use this function in trusted environment only
 * (data to decode comes from a trusted source).
 *
 * Return: number of bytes पढ़ो from the source buffer
 *	or a negative result अगर decompression fails.
 */
पूर्णांक LZ4_decompress_fast(स्थिर अक्षर *source, अक्षर *dest, पूर्णांक originalSize);

/**
 * LZ4_decompress_safe() - Decompression रक्षित against buffer overflow
 * @source: source address of the compressed data
 * @dest: output buffer address of the uncompressed data
 *	which must be alपढ़ोy allocated
 * @compressedSize: is the precise full size of the compressed block
 * @maxDecompressedSize: is the size of 'dest' buffer
 *
 * Decompresses data from 'source' into 'dest'.
 * If the source stream is detected malक्रमmed, the function will
 * stop decoding and वापस a negative result.
 * This function is रक्षित against buffer overflow exploits,
 * including malicious data packets. It never ग_लिखोs outside output buffer,
 * nor पढ़ोs outside input buffer.
 *
 * Return: number of bytes decompressed पूर्णांकo destination buffer
 *	(necessarily <= maxDecompressedSize)
 *	or a negative result in हाल of error
 */
पूर्णांक LZ4_decompress_safe(स्थिर अक्षर *source, अक्षर *dest, पूर्णांक compressedSize,
	पूर्णांक maxDecompressedSize);

/**
 * LZ4_decompress_safe_partial() - Decompress a block of size 'compressedSize'
 *	at position 'source' into buffer 'dest'
 * @source: source address of the compressed data
 * @dest: output buffer address of the decompressed data which must be
 *	alपढ़ोy allocated
 * @compressedSize: is the precise full size of the compressed block.
 * @targetOutputSize: the decompression operation will try
 *	to stop as soon as 'targetOutputSize' has been reached
 * @maxDecompressedSize: is the size of destination buffer
 *
 * This function decompresses a compressed block of size 'compressedSize'
 * at position 'source' into destination buffer 'dest'
 * of size 'maxDecompressedSize'.
 * The function tries to stop decompressing operation as soon as
 * 'targetOutputSize' has been reached, reducing decompression समय.
 * This function never ग_लिखोs outside of output buffer,
 * and never पढ़ोs outside of input buffer.
 * It is thereक्रमe रक्षित against malicious data packets.
 *
 * Return: the number of bytes decoded in the destination buffer
 *	(necessarily <= maxDecompressedSize)
 *	or a negative result in हाल of error
 *
 */
पूर्णांक LZ4_decompress_safe_partial(स्थिर अक्षर *source, अक्षर *dest,
	पूर्णांक compressedSize, पूर्णांक targetOutputSize, पूर्णांक maxDecompressedSize);

/*-************************************************************************
 *	LZ4 HC Compression
 **************************************************************************/

/**
 * LZ4_compress_HC() - Compress data from `src` पूर्णांकo `dst`, using HC algorithm
 * @src: source address of the original data
 * @dst: output buffer address of the compressed data
 * @srcSize: size of the input data. Max supported value is LZ4_MAX_INPUT_SIZE
 * @dstCapacity: full or partial size of buffer 'dst',
 *	which must be alपढ़ोy allocated
 * @compressionLevel: Recommended values are between 4 and 9, although any
 *	value between 1 and LZ4HC_MAX_CLEVEL will work.
 *	Values >LZ4HC_MAX_CLEVEL behave the same as 16.
 * @wrkmem: address of the working memory.
 *	This requires 'wrkmem' of size LZ4HC_MEM_COMPRESS.
 *
 * Compress data from 'src' into 'dst', using the more घातerful
 * but slower "HC" algorithm. Compression is guaranteed to succeed अगर
 * `dstCapacity >= LZ4_compressBound(srcSize)
 *
 * Return : the number of bytes written पूर्णांकo 'dst' or 0 अगर compression fails.
 */
पूर्णांक LZ4_compress_HC(स्थिर अक्षर *src, अक्षर *dst, पूर्णांक srcSize, पूर्णांक dstCapacity,
	पूर्णांक compressionLevel, व्योम *wrkmem);

/**
 * LZ4_resetStreamHC() - Init an allocated 'LZ4_streamHC_t' काष्ठाure
 * @streamHCPtr: poपूर्णांकer to the 'LZ4_streamHC_t' काष्ठाure
 * @compressionLevel: Recommended values are between 4 and 9, although any
 *	value between 1 and LZ4HC_MAX_CLEVEL will work.
 *	Values >LZ4HC_MAX_CLEVEL behave the same as 16.
 *
 * An LZ4_streamHC_t काष्ठाure can be allocated once
 * and re-used multiple बार.
 * Use this function to init an allocated `LZ4_streamHC_t` काष्ठाure
 * and start a new compression.
 */
व्योम LZ4_resetStreamHC(LZ4_streamHC_t *streamHCPtr, पूर्णांक compressionLevel);

/**
 * LZ4_loadDictHC() - Load a अटल dictionary पूर्णांकo LZ4_streamHC
 * @streamHCPtr: poपूर्णांकer to the LZ4HC_stream_t
 * @dictionary: dictionary to load
 * @dictSize: size of dictionary
 *
 * Use this function to load a अटल dictionary पूर्णांकo LZ4HC_stream.
 * Any previous data will be क्रमgotten, only 'dictionary'
 * will reमुख्य in memory.
 * Loading a size of 0 is allowed.
 *
 * Return : dictionary size, in bytes (necessarily <= 64 KB)
 */
पूर्णांक	LZ4_loadDictHC(LZ4_streamHC_t *streamHCPtr, स्थिर अक्षर *dictionary,
	पूर्णांक dictSize);

/**
 * LZ4_compress_HC_जारी() - Compress 'src' using data from previously
 *	compressed blocks as a dictionary using the HC algorithm
 * @streamHCPtr: Poपूर्णांकer to the previous 'LZ4_streamHC_t' काष्ठाure
 * @src: source address of the original data
 * @dst: output buffer address of the compressed data,
 *	which must be alपढ़ोy allocated
 * @srcSize: size of the input data. Max supported value is LZ4_MAX_INPUT_SIZE
 * @maxDstSize: full or partial size of buffer 'dest'
 *	which must be alपढ़ोy allocated
 *
 * These functions compress data in successive blocks of any size, using
 * previous blocks as dictionary. One key assumption is that previous
 * blocks (up to 64 KB) reमुख्य पढ़ो-accessible जबतक
 * compressing next blocks. There is an exception क्रम ring buffers,
 * which can be smaller than 64 KB.
 * Ring buffers scenario is स्वतःmatically detected and handled by
 * LZ4_compress_HC_जारी().
 * Beक्रमe starting compression, state must be properly initialized,
 * using LZ4_resetStreamHC().
 * A first "fictional block" can then be designated as
 * initial dictionary, using LZ4_loadDictHC() (Optional).
 * Then, use LZ4_compress_HC_जारी()
 * to compress each successive block. Previous memory blocks
 * (including initial dictionary when present) must reमुख्य accessible
 * and unmodअगरied during compression.
 * 'dst' buffer should be sized to handle worst हाल scenarios, using
 *  LZ4_compressBound(), to ensure operation success.
 *  If, क्रम any reason, previous data blocks can't be preserved unmodअगरied
 *  in memory during next compression block,
 *  you must save it to a safer memory space, using LZ4_saveDictHC().
 * Return value of LZ4_saveDictHC() is the size of dictionary
 * effectively saved पूर्णांकo 'safeBuffer'.
 *
 * Return: Number of bytes written पूर्णांकo buffer 'dst'  or 0 अगर compression fails
 */
पूर्णांक LZ4_compress_HC_जारी(LZ4_streamHC_t *streamHCPtr, स्थिर अक्षर *src,
	अक्षर *dst, पूर्णांक srcSize, पूर्णांक maxDstSize);

/**
 * LZ4_saveDictHC() - Save अटल dictionary from LZ4HC_stream
 * @streamHCPtr: poपूर्णांकer to the 'LZ4HC_stream_t' काष्ठाure
 * @safeBuffer: buffer to save dictionary to, must be alपढ़ोy allocated
 * @maxDictSize: size of 'safeBuffer'
 *
 * If previously compressed data block is not guaranteed
 * to reमुख्य available at its memory location,
 * save it पूर्णांकo a safer place (अक्षर *safeBuffer).
 * Note : you करोn't need to call LZ4_loadDictHC() afterwards,
 * dictionary is immediately usable, you can thereक्रमe call
 * LZ4_compress_HC_जारी().
 *
 * Return : saved dictionary size in bytes (necessarily <= maxDictSize),
 *	or 0 अगर error.
 */
पूर्णांक LZ4_saveDictHC(LZ4_streamHC_t *streamHCPtr, अक्षर *safeBuffer,
	पूर्णांक maxDictSize);

/*-*********************************************
 *	Streaming Compression Functions
 ***********************************************/

/**
 * LZ4_resetStream() - Init an allocated 'LZ4_stream_t' काष्ठाure
 * @LZ4_stream: poपूर्णांकer to the 'LZ4_stream_t' काष्ठाure
 *
 * An LZ4_stream_t काष्ठाure can be allocated once
 * and re-used multiple बार.
 * Use this function to init an allocated `LZ4_stream_t` काष्ठाure
 * and start a new compression.
 */
व्योम LZ4_resetStream(LZ4_stream_t *LZ4_stream);

/**
 * LZ4_loadDict() - Load a अटल dictionary पूर्णांकo LZ4_stream
 * @streamPtr: poपूर्णांकer to the LZ4_stream_t
 * @dictionary: dictionary to load
 * @dictSize: size of dictionary
 *
 * Use this function to load a अटल dictionary पूर्णांकo LZ4_stream.
 * Any previous data will be क्रमgotten, only 'dictionary'
 * will reमुख्य in memory.
 * Loading a size of 0 is allowed.
 *
 * Return : dictionary size, in bytes (necessarily <= 64 KB)
 */
पूर्णांक LZ4_loadDict(LZ4_stream_t *streamPtr, स्थिर अक्षर *dictionary,
	पूर्णांक dictSize);

/**
 * LZ4_saveDict() - Save अटल dictionary from LZ4_stream
 * @streamPtr: poपूर्णांकer to the 'LZ4_stream_t' काष्ठाure
 * @safeBuffer: buffer to save dictionary to, must be alपढ़ोy allocated
 * @dictSize: size of 'safeBuffer'
 *
 * If previously compressed data block is not guaranteed
 * to reमुख्य available at its memory location,
 * save it पूर्णांकo a safer place (अक्षर *safeBuffer).
 * Note : you करोn't need to call LZ4_loadDict() afterwards,
 * dictionary is immediately usable, you can thereक्रमe call
 * LZ4_compress_fast_जारी().
 *
 * Return : saved dictionary size in bytes (necessarily <= dictSize),
 *	or 0 अगर error.
 */
पूर्णांक LZ4_saveDict(LZ4_stream_t *streamPtr, अक्षर *safeBuffer, पूर्णांक dictSize);

/**
 * LZ4_compress_fast_जारी() - Compress 'src' using data from previously
 *	compressed blocks as a dictionary
 * @streamPtr: Poपूर्णांकer to the previous 'LZ4_stream_t' काष्ठाure
 * @src: source address of the original data
 * @dst: output buffer address of the compressed data,
 *	which must be alपढ़ोy allocated
 * @srcSize: size of the input data. Max supported value is LZ4_MAX_INPUT_SIZE
 * @maxDstSize: full or partial size of buffer 'dest'
 *	which must be alपढ़ोy allocated
 * @acceleration: acceleration factor
 *
 * Compress buffer content 'src', using data from previously compressed blocks
 * as dictionary to improve compression ratio.
 * Important : Previous data blocks are assumed to still
 * be present and unmodअगरied !
 * If maxDstSize >= LZ4_compressBound(srcSize),
 * compression is guaranteed to succeed, and runs faster.
 *
 * Return: Number of bytes written पूर्णांकo buffer 'dst'  or 0 अगर compression fails
 */
पूर्णांक LZ4_compress_fast_जारी(LZ4_stream_t *streamPtr, स्थिर अक्षर *src,
	अक्षर *dst, पूर्णांक srcSize, पूर्णांक maxDstSize, पूर्णांक acceleration);

/**
 * LZ4_setStreamDecode() - Inकाष्ठा where to find dictionary
 * @LZ4_streamDecode: the 'LZ4_streamDecode_t' काष्ठाure
 * @dictionary: dictionary to use
 * @dictSize: size of dictionary
 *
 * Use this function to inकाष्ठा where to find the dictionary.
 *	Setting a size of 0 is allowed (same effect as reset).
 *
 * Return: 1 अगर OK, 0 अगर error
 */
पूर्णांक LZ4_setStreamDecode(LZ4_streamDecode_t *LZ4_streamDecode,
	स्थिर अक्षर *dictionary, पूर्णांक dictSize);

/**
 * LZ4_decompress_safe_जारी() - Decompress blocks in streaming mode
 * @LZ4_streamDecode: the 'LZ4_streamDecode_t' काष्ठाure
 * @source: source address of the compressed data
 * @dest: output buffer address of the uncompressed data
 *	which must be alपढ़ोy allocated
 * @compressedSize: is the precise full size of the compressed block
 * @maxDecompressedSize: is the size of 'dest' buffer
 *
 * This decoding function allows decompression of multiple blocks
 * in "streaming" mode.
 * Previously decoded blocks *must* reमुख्य available at the memory position
 * where they were decoded (up to 64 KB)
 * In the हाल of a ring buffers, decoding buffer must be either :
 *    - Exactly same size as encoding buffer, with same update rule
 *      (block boundaries at same positions) In which हाल,
 *      the decoding & encoding ring buffer can have any size,
 *      including very small ones ( < 64 KB).
 *    - Larger than encoding buffer, by a minimum of maxBlockSize more bytes.
 *      maxBlockSize is implementation dependent.
 *      It's the maximum size you पूर्णांकend to compress पूर्णांकo a single block.
 *      In which हाल, encoding and decoding buffers करो not need
 *      to be synchronized, and encoding ring buffer can have any size,
 *      including small ones ( < 64 KB).
 *    - _At least_ 64 KB + 8 bytes + maxBlockSize.
 *      In which हाल, encoding and decoding buffers करो not need to be
 *      synchronized, and encoding ring buffer can have any size,
 *      including larger than decoding buffer. W
 * Whenever these conditions are not possible, save the last 64KB of decoded
 * data पूर्णांकo a safe buffer, and indicate where it is saved
 * using LZ4_setStreamDecode()
 *
 * Return: number of bytes decompressed पूर्णांकo destination buffer
 *	(necessarily <= maxDecompressedSize)
 *	or a negative result in हाल of error
 */
पूर्णांक LZ4_decompress_safe_जारी(LZ4_streamDecode_t *LZ4_streamDecode,
	स्थिर अक्षर *source, अक्षर *dest, पूर्णांक compressedSize,
	पूर्णांक maxDecompressedSize);

/**
 * LZ4_decompress_fast_जारी() - Decompress blocks in streaming mode
 * @LZ4_streamDecode: the 'LZ4_streamDecode_t' काष्ठाure
 * @source: source address of the compressed data
 * @dest: output buffer address of the uncompressed data
 *	which must be alपढ़ोy allocated with 'originalSize' bytes
 * @originalSize: is the original and thereक्रमe uncompressed size
 *
 * This decoding function allows decompression of multiple blocks
 * in "streaming" mode.
 * Previously decoded blocks *must* reमुख्य available at the memory position
 * where they were decoded (up to 64 KB)
 * In the हाल of a ring buffers, decoding buffer must be either :
 *    - Exactly same size as encoding buffer, with same update rule
 *      (block boundaries at same positions) In which हाल,
 *      the decoding & encoding ring buffer can have any size,
 *      including very small ones ( < 64 KB).
 *    - Larger than encoding buffer, by a minimum of maxBlockSize more bytes.
 *      maxBlockSize is implementation dependent.
 *      It's the maximum size you पूर्णांकend to compress पूर्णांकo a single block.
 *      In which हाल, encoding and decoding buffers करो not need
 *      to be synchronized, and encoding ring buffer can have any size,
 *      including small ones ( < 64 KB).
 *    - _At least_ 64 KB + 8 bytes + maxBlockSize.
 *      In which हाल, encoding and decoding buffers करो not need to be
 *      synchronized, and encoding ring buffer can have any size,
 *      including larger than decoding buffer. W
 * Whenever these conditions are not possible, save the last 64KB of decoded
 * data पूर्णांकo a safe buffer, and indicate where it is saved
 * using LZ4_setStreamDecode()
 *
 * Return: number of bytes decompressed पूर्णांकo destination buffer
 *	(necessarily <= maxDecompressedSize)
 *	or a negative result in हाल of error
 */
पूर्णांक LZ4_decompress_fast_जारी(LZ4_streamDecode_t *LZ4_streamDecode,
	स्थिर अक्षर *source, अक्षर *dest, पूर्णांक originalSize);

/**
 * LZ4_decompress_safe_usingDict() - Same as LZ4_setStreamDecode()
 *	followed by LZ4_decompress_safe_जारी()
 * @source: source address of the compressed data
 * @dest: output buffer address of the uncompressed data
 *	which must be alपढ़ोy allocated
 * @compressedSize: is the precise full size of the compressed block
 * @maxDecompressedSize: is the size of 'dest' buffer
 * @dictStart: poपूर्णांकer to the start of the dictionary in memory
 * @dictSize: size of dictionary
 *
 * This decoding function works the same as
 * a combination of LZ4_setStreamDecode() followed by
 * LZ4_decompress_safe_जारी()
 * It is stand-alone, and करोesn't need an LZ4_streamDecode_t काष्ठाure.
 *
 * Return: number of bytes decompressed पूर्णांकo destination buffer
 *	(necessarily <= maxDecompressedSize)
 *	or a negative result in हाल of error
 */
पूर्णांक LZ4_decompress_safe_usingDict(स्थिर अक्षर *source, अक्षर *dest,
	पूर्णांक compressedSize, पूर्णांक maxDecompressedSize, स्थिर अक्षर *dictStart,
	पूर्णांक dictSize);

/**
 * LZ4_decompress_fast_usingDict() - Same as LZ4_setStreamDecode()
 *	followed by LZ4_decompress_fast_जारी()
 * @source: source address of the compressed data
 * @dest: output buffer address of the uncompressed data
 *	which must be alपढ़ोy allocated with 'originalSize' bytes
 * @originalSize: is the original and thereक्रमe uncompressed size
 * @dictStart: poपूर्णांकer to the start of the dictionary in memory
 * @dictSize: size of dictionary
 *
 * This decoding function works the same as
 * a combination of LZ4_setStreamDecode() followed by
 * LZ4_decompress_fast_जारी()
 * It is stand-alone, and करोesn't need an LZ4_streamDecode_t काष्ठाure.
 *
 * Return: number of bytes decompressed पूर्णांकo destination buffer
 *	(necessarily <= maxDecompressedSize)
 *	or a negative result in हाल of error
 */
पूर्णांक LZ4_decompress_fast_usingDict(स्थिर अक्षर *source, अक्षर *dest,
	पूर्णांक originalSize, स्थिर अक्षर *dictStart, पूर्णांक dictSize);

#पूर्ण_अगर
