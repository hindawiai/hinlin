<शैली गुरु>
/*
 * Copyright (c) 2016-present, Yann Collet, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of https://github.com/facebook/zstd.
 * An additional grant of patent rights can be found in the PATENTS file in the
 * same directory.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it under
 * the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation. This program is dual-licensed; you may select
 * either version 2 of the GNU General Public License ("GPL") or BSD license
 * ("BSD").
 */

#अगर_अघोषित ZSTD_H
#घोषणा ZSTD_H

/* ======   Dependency   ======*/
#समावेश <linux/types.h>   /* माप_प्रकार */


/*-*****************************************************************************
 * Introduction
 *
 * zstd, लघु क्रम Zstandard, is a fast lossless compression algorithm,
 * targeting real-समय compression scenarios at zlib-level and better
 * compression ratios. The zstd compression library provides in-memory
 * compression and decompression functions. The library supports compression
 * levels from 1 up to ZSTD_maxCLevel() which is 22. Levels >= 20, labeled
 * ultra, should be used with caution, as they require more memory.
 * Compression can be करोne in:
 *  - a single step, reusing a context (described as Explicit memory management)
 *  - unbounded multiple steps (described as Streaming compression)
 * The compression ratio achievable on small data can be highly improved using
 * compression with a dictionary in:
 *  - a single step (described as Simple dictionary API)
 *  - a single step, reusing a dictionary (described as Fast dictionary API)
 ******************************************************************************/

/*======  Helper functions  ======*/

/**
 * क्रमागत ZSTD_ErrorCode - zstd error codes
 *
 * Functions that वापस माप_प्रकार can be checked क्रम errors using ZSTD_isError()
 * and the ZSTD_ErrorCode can be extracted using ZSTD_getErrorCode().
 */
प्रकार क्रमागत अणु
	ZSTD_error_no_error,
	ZSTD_error_GENERIC,
	ZSTD_error_prefix_unknown,
	ZSTD_error_version_unsupported,
	ZSTD_error_parameter_unknown,
	ZSTD_error_frameParameter_unsupported,
	ZSTD_error_frameParameter_unsupportedBy32bits,
	ZSTD_error_frameParameter_winकरोwTooLarge,
	ZSTD_error_compressionParameter_unsupported,
	ZSTD_error_init_missing,
	ZSTD_error_memory_allocation,
	ZSTD_error_stage_wrong,
	ZSTD_error_dstSize_tooSmall,
	ZSTD_error_srcSize_wrong,
	ZSTD_error_corruption_detected,
	ZSTD_error_checksum_wrong,
	ZSTD_error_tableLog_tooLarge,
	ZSTD_error_maxSymbolValue_tooLarge,
	ZSTD_error_maxSymbolValue_tooSmall,
	ZSTD_error_dictionary_corrupted,
	ZSTD_error_dictionary_wrong,
	ZSTD_error_dictionaryCreation_failed,
	ZSTD_error_maxCode
पूर्ण ZSTD_ErrorCode;

/**
 * ZSTD_maxCLevel() - maximum compression level available
 *
 * Return: Maximum compression level available.
 */
पूर्णांक ZSTD_maxCLevel(व्योम);
/**
 * ZSTD_compressBound() - maximum compressed size in worst हाल scenario
 * @srcSize: The size of the data to compress.
 *
 * Return:   The maximum compressed size in the worst हाल scenario.
 */
माप_प्रकार ZSTD_compressBound(माप_प्रकार srcSize);
/**
 * ZSTD_isError() - tells अगर a माप_प्रकार function result is an error code
 * @code:  The function result to check क्रम error.
 *
 * Return: Non-zero अगरf the code is an error.
 */
अटल __attribute__((unused)) अचिन्हित पूर्णांक ZSTD_isError(माप_प्रकार code)
अणु
	वापस code > (माप_प्रकार)-ZSTD_error_maxCode;
पूर्ण
/**
 * ZSTD_getErrorCode() - translates an error function result to a ZSTD_ErrorCode
 * @functionResult: The result of a function क्रम which ZSTD_isError() is true.
 *
 * Return:          The ZSTD_ErrorCode corresponding to the functionResult or 0
 *                  अगर the functionResult isn't an error.
 */
अटल __attribute__((unused)) ZSTD_ErrorCode ZSTD_getErrorCode(
	माप_प्रकार functionResult)
अणु
	अगर (!ZSTD_isError(functionResult))
		वापस (ZSTD_ErrorCode)0;
	वापस (ZSTD_ErrorCode)(0 - functionResult);
पूर्ण

/**
 * क्रमागत ZSTD_strategy - zstd compression search strategy
 *
 * From faster to stronger.
 */
प्रकार क्रमागत अणु
	ZSTD_fast,
	ZSTD_dfast,
	ZSTD_greedy,
	ZSTD_lazy,
	ZSTD_lazy2,
	ZSTD_btlazy2,
	ZSTD_btopt,
	ZSTD_btopt2
पूर्ण ZSTD_strategy;

/**
 * काष्ठा ZSTD_compressionParameters - zstd compression parameters
 * @winकरोwLog:    Log of the largest match distance. Larger means more
 *                compression, and more memory needed during decompression.
 * @chainLog:     Fully searched segment. Larger means more compression, slower,
 *                and more memory (useless क्रम fast).
 * @hashLog:      Dispatch table. Larger means more compression,
 *                slower, and more memory.
 * @searchLog:    Number of searches. Larger means more compression and slower.
 * @searchLength: Match length searched. Larger means faster decompression,
 *                someबार less compression.
 * @targetLength: Acceptable match size क्रम optimal parser (only). Larger means
 *                more compression, and slower.
 * @strategy:     The zstd compression strategy.
 */
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक winकरोwLog;
	अचिन्हित पूर्णांक chainLog;
	अचिन्हित पूर्णांक hashLog;
	अचिन्हित पूर्णांक searchLog;
	अचिन्हित पूर्णांक searchLength;
	अचिन्हित पूर्णांक targetLength;
	ZSTD_strategy strategy;
पूर्ण ZSTD_compressionParameters;

/**
 * काष्ठा ZSTD_frameParameters - zstd frame parameters
 * @contentSizeFlag: Controls whether content size will be present in the frame
 *                   header (when known).
 * @checksumFlag:    Controls whether a 32-bit checksum is generated at the end
 *                   of the frame क्रम error detection.
 * @noDictIDFlag:    Controls whether dictID will be saved पूर्णांकo the frame header
 *                   when using dictionary compression.
 *
 * The शेष value is all fields set to 0.
 */
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक contentSizeFlag;
	अचिन्हित पूर्णांक checksumFlag;
	अचिन्हित पूर्णांक noDictIDFlag;
पूर्ण ZSTD_frameParameters;

/**
 * काष्ठा ZSTD_parameters - zstd parameters
 * @cParams: The compression parameters.
 * @fParams: The frame parameters.
 */
प्रकार काष्ठा अणु
	ZSTD_compressionParameters cParams;
	ZSTD_frameParameters fParams;
पूर्ण ZSTD_parameters;

/**
 * ZSTD_getCParams() - वापसs ZSTD_compressionParameters क्रम selected level
 * @compressionLevel: The compression level from 1 to ZSTD_maxCLevel().
 * @estimatedSrcSize: The estimated source size to compress or 0 अगर unknown.
 * @dictSize:         The dictionary size or 0 अगर a dictionary isn't being used.
 *
 * Return:            The selected ZSTD_compressionParameters.
 */
ZSTD_compressionParameters ZSTD_getCParams(पूर्णांक compressionLevel,
	अचिन्हित दीर्घ दीर्घ estimatedSrcSize, माप_प्रकार dictSize);

/**
 * ZSTD_getParams() - वापसs ZSTD_parameters क्रम selected level
 * @compressionLevel: The compression level from 1 to ZSTD_maxCLevel().
 * @estimatedSrcSize: The estimated source size to compress or 0 अगर unknown.
 * @dictSize:         The dictionary size or 0 अगर a dictionary isn't being used.
 *
 * The same as ZSTD_getCParams() except also selects the शेष frame
 * parameters (all zero).
 *
 * Return:            The selected ZSTD_parameters.
 */
ZSTD_parameters ZSTD_getParams(पूर्णांक compressionLevel,
	अचिन्हित दीर्घ दीर्घ estimatedSrcSize, माप_प्रकार dictSize);

/*-*************************************
 * Explicit memory management
 **************************************/

/**
 * ZSTD_CCtxWorkspaceBound() - amount of memory needed to initialize a ZSTD_CCtx
 * @cParams: The compression parameters to be used क्रम compression.
 *
 * If multiple compression parameters might be used, the caller must call
 * ZSTD_CCtxWorkspaceBound() क्रम each set of parameters and use the maximum
 * size.
 *
 * Return:   A lower bound on the size of the workspace that is passed to
 *           ZSTD_initCCtx().
 */
माप_प्रकार ZSTD_CCtxWorkspaceBound(ZSTD_compressionParameters cParams);

/**
 * काष्ठा ZSTD_CCtx - the zstd compression context
 *
 * When compressing many बार it is recommended to allocate a context just once
 * and reuse it क्रम each successive compression operation.
 */
प्रकार काष्ठा ZSTD_CCtx_s ZSTD_CCtx;
/**
 * ZSTD_initCCtx() - initialize a zstd compression context
 * @workspace:     The workspace to emplace the context पूर्णांकo. It must outlive
 *                 the वापसed context.
 * @workspaceSize: The size of workspace. Use ZSTD_CCtxWorkspaceBound() to
 *                 determine how large the workspace must be.
 *
 * Return:         A compression context emplaced पूर्णांकo workspace.
 */
ZSTD_CCtx *ZSTD_initCCtx(व्योम *workspace, माप_प्रकार workspaceSize);

/**
 * ZSTD_compressCCtx() - compress src पूर्णांकo dst
 * @ctx:         The context. Must have been initialized with a workspace at
 *               least as large as ZSTD_CCtxWorkspaceBound(params.cParams).
 * @dst:         The buffer to compress src पूर्णांकo.
 * @dstCapacity: The size of the destination buffer. May be any size, but
 *               ZSTD_compressBound(srcSize) is guaranteed to be large enough.
 * @src:         The data to compress.
 * @srcSize:     The size of the data to compress.
 * @params:      The parameters to use क्रम compression. See ZSTD_getParams().
 *
 * Return:       The compressed size or an error, which can be checked using
 *               ZSTD_isError().
 */
माप_प्रकार ZSTD_compressCCtx(ZSTD_CCtx *ctx, व्योम *dst, माप_प्रकार dstCapacity,
	स्थिर व्योम *src, माप_प्रकार srcSize, ZSTD_parameters params);

/**
 * ZSTD_DCtxWorkspaceBound() - amount of memory needed to initialize a ZSTD_DCtx
 *
 * Return: A lower bound on the size of the workspace that is passed to
 *         ZSTD_initDCtx().
 */
माप_प्रकार ZSTD_DCtxWorkspaceBound(व्योम);

/**
 * काष्ठा ZSTD_DCtx - the zstd decompression context
 *
 * When decompressing many बार it is recommended to allocate a context just
 * once and reuse it क्रम each successive decompression operation.
 */
प्रकार काष्ठा ZSTD_DCtx_s ZSTD_DCtx;
/**
 * ZSTD_initDCtx() - initialize a zstd decompression context
 * @workspace:     The workspace to emplace the context पूर्णांकo. It must outlive
 *                 the वापसed context.
 * @workspaceSize: The size of workspace. Use ZSTD_DCtxWorkspaceBound() to
 *                 determine how large the workspace must be.
 *
 * Return:         A decompression context emplaced पूर्णांकo workspace.
 */
ZSTD_DCtx *ZSTD_initDCtx(व्योम *workspace, माप_प्रकार workspaceSize);

/**
 * ZSTD_decompressDCtx() - decompress zstd compressed src पूर्णांकo dst
 * @ctx:         The decompression context.
 * @dst:         The buffer to decompress src पूर्णांकo.
 * @dstCapacity: The size of the destination buffer. Must be at least as large
 *               as the decompressed size. If the caller cannot upper bound the
 *               decompressed size, then it's better to use the streaming API.
 * @src:         The zstd compressed data to decompress. Multiple concatenated
 *               frames and skippable frames are allowed.
 * @srcSize:     The exact size of the data to decompress.
 *
 * Return:       The decompressed size or an error, which can be checked using
 *               ZSTD_isError().
 */
माप_प्रकार ZSTD_decompressDCtx(ZSTD_DCtx *ctx, व्योम *dst, माप_प्रकार dstCapacity,
	स्थिर व्योम *src, माप_प्रकार srcSize);

/*-************************
 * Simple dictionary API
 **************************/

/**
 * ZSTD_compress_usingDict() - compress src पूर्णांकo dst using a dictionary
 * @ctx:         The context. Must have been initialized with a workspace at
 *               least as large as ZSTD_CCtxWorkspaceBound(params.cParams).
 * @dst:         The buffer to compress src पूर्णांकo.
 * @dstCapacity: The size of the destination buffer. May be any size, but
 *               ZSTD_compressBound(srcSize) is guaranteed to be large enough.
 * @src:         The data to compress.
 * @srcSize:     The size of the data to compress.
 * @dict:        The dictionary to use क्रम compression.
 * @dictSize:    The size of the dictionary.
 * @params:      The parameters to use क्रम compression. See ZSTD_getParams().
 *
 * Compression using a predefined dictionary. The same dictionary must be used
 * during decompression.
 *
 * Return:       The compressed size or an error, which can be checked using
 *               ZSTD_isError().
 */
माप_प्रकार ZSTD_compress_usingDict(ZSTD_CCtx *ctx, व्योम *dst, माप_प्रकार dstCapacity,
	स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर व्योम *dict, माप_प्रकार dictSize,
	ZSTD_parameters params);

/**
 * ZSTD_decompress_usingDict() - decompress src पूर्णांकo dst using a dictionary
 * @ctx:         The decompression context.
 * @dst:         The buffer to decompress src पूर्णांकo.
 * @dstCapacity: The size of the destination buffer. Must be at least as large
 *               as the decompressed size. If the caller cannot upper bound the
 *               decompressed size, then it's better to use the streaming API.
 * @src:         The zstd compressed data to decompress. Multiple concatenated
 *               frames and skippable frames are allowed.
 * @srcSize:     The exact size of the data to decompress.
 * @dict:        The dictionary to use क्रम decompression. The same dictionary
 *               must've been used to compress the data.
 * @dictSize:    The size of the dictionary.
 *
 * Return:       The decompressed size or an error, which can be checked using
 *               ZSTD_isError().
 */
माप_प्रकार ZSTD_decompress_usingDict(ZSTD_DCtx *ctx, व्योम *dst, माप_प्रकार dstCapacity,
	स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर व्योम *dict, माप_प्रकार dictSize);

/*-**************************
 * Fast dictionary API
 ***************************/

/**
 * ZSTD_CDictWorkspaceBound() - memory needed to initialize a ZSTD_CDict
 * @cParams: The compression parameters to be used क्रम compression.
 *
 * Return:   A lower bound on the size of the workspace that is passed to
 *           ZSTD_initCDict().
 */
माप_प्रकार ZSTD_CDictWorkspaceBound(ZSTD_compressionParameters cParams);

/**
 * काष्ठा ZSTD_CDict - a digested dictionary to be used क्रम compression
 */
प्रकार काष्ठा ZSTD_CDict_s ZSTD_CDict;

/**
 * ZSTD_initCDict() - initialize a digested dictionary क्रम compression
 * @dictBuffer:    The dictionary to digest. The buffer is referenced by the
 *                 ZSTD_CDict so it must outlive the वापसed ZSTD_CDict.
 * @dictSize:      The size of the dictionary.
 * @params:        The parameters to use क्रम compression. See ZSTD_getParams().
 * @workspace:     The workspace. It must outlive the वापसed ZSTD_CDict.
 * @workspaceSize: The workspace size. Must be at least
 *                 ZSTD_CDictWorkspaceBound(params.cParams).
 *
 * When compressing multiple messages / blocks with the same dictionary it is
 * recommended to load it just once. The ZSTD_CDict merely references the
 * dictBuffer, so it must outlive the वापसed ZSTD_CDict.
 *
 * Return:         The digested dictionary emplaced पूर्णांकo workspace.
 */
ZSTD_CDict *ZSTD_initCDict(स्थिर व्योम *dictBuffer, माप_प्रकार dictSize,
	ZSTD_parameters params, व्योम *workspace, माप_प्रकार workspaceSize);

/**
 * ZSTD_compress_usingCDict() - compress src पूर्णांकo dst using a ZSTD_CDict
 * @ctx:         The context. Must have been initialized with a workspace at
 *               least as large as ZSTD_CCtxWorkspaceBound(cParams) where
 *               cParams are the compression parameters used to initialize the
 *               cdict.
 * @dst:         The buffer to compress src पूर्णांकo.
 * @dstCapacity: The size of the destination buffer. May be any size, but
 *               ZSTD_compressBound(srcSize) is guaranteed to be large enough.
 * @src:         The data to compress.
 * @srcSize:     The size of the data to compress.
 * @cdict:       The digested dictionary to use क्रम compression.
 * @params:      The parameters to use क्रम compression. See ZSTD_getParams().
 *
 * Compression using a digested dictionary. The same dictionary must be used
 * during decompression.
 *
 * Return:       The compressed size or an error, which can be checked using
 *               ZSTD_isError().
 */
माप_प्रकार ZSTD_compress_usingCDict(ZSTD_CCtx *cctx, व्योम *dst, माप_प्रकार dstCapacity,
	स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर ZSTD_CDict *cdict);


/**
 * ZSTD_DDictWorkspaceBound() - memory needed to initialize a ZSTD_DDict
 *
 * Return:  A lower bound on the size of the workspace that is passed to
 *          ZSTD_initDDict().
 */
माप_प्रकार ZSTD_DDictWorkspaceBound(व्योम);

/**
 * काष्ठा ZSTD_DDict - a digested dictionary to be used क्रम decompression
 */
प्रकार काष्ठा ZSTD_DDict_s ZSTD_DDict;

/**
 * ZSTD_initDDict() - initialize a digested dictionary क्रम decompression
 * @dictBuffer:    The dictionary to digest. The buffer is referenced by the
 *                 ZSTD_DDict so it must outlive the वापसed ZSTD_DDict.
 * @dictSize:      The size of the dictionary.
 * @workspace:     The workspace. It must outlive the वापसed ZSTD_DDict.
 * @workspaceSize: The workspace size. Must be at least
 *                 ZSTD_DDictWorkspaceBound().
 *
 * When decompressing multiple messages / blocks with the same dictionary it is
 * recommended to load it just once. The ZSTD_DDict merely references the
 * dictBuffer, so it must outlive the वापसed ZSTD_DDict.
 *
 * Return:         The digested dictionary emplaced पूर्णांकo workspace.
 */
ZSTD_DDict *ZSTD_initDDict(स्थिर व्योम *dictBuffer, माप_प्रकार dictSize,
	व्योम *workspace, माप_प्रकार workspaceSize);

/**
 * ZSTD_decompress_usingDDict() - decompress src पूर्णांकo dst using a ZSTD_DDict
 * @ctx:         The decompression context.
 * @dst:         The buffer to decompress src पूर्णांकo.
 * @dstCapacity: The size of the destination buffer. Must be at least as large
 *               as the decompressed size. If the caller cannot upper bound the
 *               decompressed size, then it's better to use the streaming API.
 * @src:         The zstd compressed data to decompress. Multiple concatenated
 *               frames and skippable frames are allowed.
 * @srcSize:     The exact size of the data to decompress.
 * @ddict:       The digested dictionary to use क्रम decompression. The same
 *               dictionary must've been used to compress the data.
 *
 * Return:       The decompressed size or an error, which can be checked using
 *               ZSTD_isError().
 */
माप_प्रकार ZSTD_decompress_usingDDict(ZSTD_DCtx *dctx, व्योम *dst,
	माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize,
	स्थिर ZSTD_DDict *ddict);


/*-**************************
 * Streaming
 ***************************/

/**
 * काष्ठा ZSTD_inBuffer - input buffer क्रम streaming
 * @src:  Start of the input buffer.
 * @size: Size of the input buffer.
 * @pos:  Position where पढ़ोing stopped. Will be updated.
 *        Necessarily 0 <= pos <= size.
 */
प्रकार काष्ठा ZSTD_inBuffer_s अणु
	स्थिर व्योम *src;
	माप_प्रकार size;
	माप_प्रकार pos;
पूर्ण ZSTD_inBuffer;

/**
 * काष्ठा ZSTD_outBuffer - output buffer क्रम streaming
 * @dst:  Start of the output buffer.
 * @size: Size of the output buffer.
 * @pos:  Position where writing stopped. Will be updated.
 *        Necessarily 0 <= pos <= size.
 */
प्रकार काष्ठा ZSTD_outBuffer_s अणु
	व्योम *dst;
	माप_प्रकार size;
	माप_प्रकार pos;
पूर्ण ZSTD_outBuffer;



/*-*****************************************************************************
 * Streaming compression - HowTo
 *
 * A ZSTD_CStream object is required to track streaming operation.
 * Use ZSTD_initCStream() to initialize a ZSTD_CStream object.
 * ZSTD_CStream objects can be reused multiple बार on consecutive compression
 * operations. It is recommended to re-use ZSTD_CStream in situations where many
 * streaming operations will be achieved consecutively. Use one separate
 * ZSTD_CStream per thपढ़ो क्रम parallel execution.
 *
 * Use ZSTD_compressStream() repetitively to consume input stream.
 * The function will स्वतःmatically update both `pos` fields.
 * Note that it may not consume the entire input, in which हाल `pos < size`,
 * and it's up to the caller to present again reमुख्यing data.
 * It वापसs a hपूर्णांक क्रम the preferred number of bytes to use as an input क्रम
 * the next function call.
 *
 * At any moment, it's possible to flush whatever data reमुख्यs within पूर्णांकernal
 * buffer, using ZSTD_flushStream(). `output->pos` will be updated. There might
 * still be some content left within the पूर्णांकernal buffer अगर `output->size` is
 * too small. It वापसs the number of bytes left in the पूर्णांकernal buffer and
 * must be called until it वापसs 0.
 *
 * ZSTD_endStream() inकाष्ठाs to finish a frame. It will perक्रमm a flush and
 * ग_लिखो frame epilogue. The epilogue is required क्रम decoders to consider a
 * frame completed. Similar to ZSTD_flushStream(), it may not be able to flush
 * the full content अगर `output->size` is too small. In which हाल, call again
 * ZSTD_endStream() to complete the flush. It वापसs the number of bytes left
 * in the पूर्णांकernal buffer and must be called until it वापसs 0.
 ******************************************************************************/

/**
 * ZSTD_CStreamWorkspaceBound() - memory needed to initialize a ZSTD_CStream
 * @cParams: The compression parameters to be used क्रम compression.
 *
 * Return:   A lower bound on the size of the workspace that is passed to
 *           ZSTD_initCStream() and ZSTD_initCStream_usingCDict().
 */
माप_प्रकार ZSTD_CStreamWorkspaceBound(ZSTD_compressionParameters cParams);

/**
 * काष्ठा ZSTD_CStream - the zstd streaming compression context
 */
प्रकार काष्ठा ZSTD_CStream_s ZSTD_CStream;

/*===== ZSTD_CStream management functions =====*/
/**
 * ZSTD_initCStream() - initialize a zstd streaming compression context
 * @params:         The zstd compression parameters.
 * @pledgedSrcSize: If params.fParams.contentSizeFlag == 1 then the caller must
 *                  pass the source size (zero means empty source). Otherwise,
 *                  the caller may optionally pass the source size, or zero अगर
 *                  unknown.
 * @workspace:      The workspace to emplace the context पूर्णांकo. It must outlive
 *                  the वापसed context.
 * @workspaceSize:  The size of workspace.
 *                  Use ZSTD_CStreamWorkspaceBound(params.cParams) to determine
 *                  how large the workspace must be.
 *
 * Return:          The zstd streaming compression context.
 */
ZSTD_CStream *ZSTD_initCStream(ZSTD_parameters params,
	अचिन्हित दीर्घ दीर्घ pledgedSrcSize, व्योम *workspace,
	माप_प्रकार workspaceSize);

/**
 * ZSTD_initCStream_usingCDict() - initialize a streaming compression context
 * @cdict:          The digested dictionary to use क्रम compression.
 * @pledgedSrcSize: Optionally the source size, or zero अगर unknown.
 * @workspace:      The workspace to emplace the context पूर्णांकo. It must outlive
 *                  the वापसed context.
 * @workspaceSize:  The size of workspace. Call ZSTD_CStreamWorkspaceBound()
 *                  with the cParams used to initialize the cdict to determine
 *                  how large the workspace must be.
 *
 * Return:          The zstd streaming compression context.
 */
ZSTD_CStream *ZSTD_initCStream_usingCDict(स्थिर ZSTD_CDict *cdict,
	अचिन्हित दीर्घ दीर्घ pledgedSrcSize, व्योम *workspace,
	माप_प्रकार workspaceSize);

/*===== Streaming compression functions =====*/
/**
 * ZSTD_resetCStream() - reset the context using parameters from creation
 * @zcs:            The zstd streaming compression context to reset.
 * @pledgedSrcSize: Optionally the source size, or zero अगर unknown.
 *
 * Resets the context using the parameters from creation. Skips dictionary
 * loading, since it can be reused. If `pledgedSrcSize` is non-zero the frame
 * content size is always written पूर्णांकo the frame header.
 *
 * Return:          Zero or an error, which can be checked using ZSTD_isError().
 */
माप_प्रकार ZSTD_resetCStream(ZSTD_CStream *zcs, अचिन्हित दीर्घ दीर्घ pledgedSrcSize);
/**
 * ZSTD_compressStream() - streaming compress some of input पूर्णांकo output
 * @zcs:    The zstd streaming compression context.
 * @output: Destination buffer. `output->pos` is updated to indicate how much
 *          compressed data was written.
 * @input:  Source buffer. `input->pos` is updated to indicate how much data was
 *          पढ़ो. Note that it may not consume the entire input, in which हाल
 *          `input->pos < input->size`, and it's up to the caller to present
 *          reमुख्यing data again.
 *
 * The `input` and `output` buffers may be any size. Guaranteed to make some
 * क्रमward progress अगर `input` and `output` are not empty.
 *
 * Return:  A hपूर्णांक क्रम the number of bytes to use as the input क्रम the next
 *          function call or an error, which can be checked using
 *          ZSTD_isError().
 */
माप_प्रकार ZSTD_compressStream(ZSTD_CStream *zcs, ZSTD_outBuffer *output,
	ZSTD_inBuffer *input);
/**
 * ZSTD_flushStream() - flush पूर्णांकernal buffers पूर्णांकo output
 * @zcs:    The zstd streaming compression context.
 * @output: Destination buffer. `output->pos` is updated to indicate how much
 *          compressed data was written.
 *
 * ZSTD_flushStream() must be called until it वापसs 0, meaning all the data
 * has been flushed. Since ZSTD_flushStream() causes a block to be ended,
 * calling it too often will degrade the compression ratio.
 *
 * Return:  The number of bytes still present within पूर्णांकernal buffers or an
 *          error, which can be checked using ZSTD_isError().
 */
माप_प्रकार ZSTD_flushStream(ZSTD_CStream *zcs, ZSTD_outBuffer *output);
/**
 * ZSTD_endStream() - flush पूर्णांकernal buffers पूर्णांकo output and end the frame
 * @zcs:    The zstd streaming compression context.
 * @output: Destination buffer. `output->pos` is updated to indicate how much
 *          compressed data was written.
 *
 * ZSTD_endStream() must be called until it वापसs 0, meaning all the data has
 * been flushed and the frame epilogue has been written.
 *
 * Return:  The number of bytes still present within पूर्णांकernal buffers or an
 *          error, which can be checked using ZSTD_isError().
 */
माप_प्रकार ZSTD_endStream(ZSTD_CStream *zcs, ZSTD_outBuffer *output);

/**
 * ZSTD_CStreamInSize() - recommended size क्रम the input buffer
 *
 * Return: The recommended size क्रम the input buffer.
 */
माप_प्रकार ZSTD_CStreamInSize(व्योम);
/**
 * ZSTD_CStreamOutSize() - recommended size क्रम the output buffer
 *
 * When the output buffer is at least this large, it is guaranteed to be large
 * enough to flush at least one complete compressed block.
 *
 * Return: The recommended size क्रम the output buffer.
 */
माप_प्रकार ZSTD_CStreamOutSize(व्योम);



/*-*****************************************************************************
 * Streaming decompression - HowTo
 *
 * A ZSTD_DStream object is required to track streaming operations.
 * Use ZSTD_initDStream() to initialize a ZSTD_DStream object.
 * ZSTD_DStream objects can be re-used multiple बार.
 *
 * Use ZSTD_decompressStream() repetitively to consume your input.
 * The function will update both `pos` fields.
 * If `input->pos < input->size`, some input has not been consumed.
 * It's up to the caller to present again reमुख्यing data.
 * If `output->pos < output->size`, decoder has flushed everything it could.
 * Returns 0 अगरf a frame is completely decoded and fully flushed.
 * Otherwise it वापसs a suggested next input size that will never load more
 * than the current frame.
 ******************************************************************************/

/**
 * ZSTD_DStreamWorkspaceBound() - memory needed to initialize a ZSTD_DStream
 * @maxWinकरोwSize: The maximum winकरोw size allowed क्रम compressed frames.
 *
 * Return:         A lower bound on the size of the workspace that is passed to
 *                 ZSTD_initDStream() and ZSTD_initDStream_usingDDict().
 */
माप_प्रकार ZSTD_DStreamWorkspaceBound(माप_प्रकार maxWinकरोwSize);

/**
 * काष्ठा ZSTD_DStream - the zstd streaming decompression context
 */
प्रकार काष्ठा ZSTD_DStream_s ZSTD_DStream;
/*===== ZSTD_DStream management functions =====*/
/**
 * ZSTD_initDStream() - initialize a zstd streaming decompression context
 * @maxWinकरोwSize: The maximum winकरोw size allowed क्रम compressed frames.
 * @workspace:     The workspace to emplace the context पूर्णांकo. It must outlive
 *                 the वापसed context.
 * @workspaceSize: The size of workspace.
 *                 Use ZSTD_DStreamWorkspaceBound(maxWinकरोwSize) to determine
 *                 how large the workspace must be.
 *
 * Return:         The zstd streaming decompression context.
 */
ZSTD_DStream *ZSTD_initDStream(माप_प्रकार maxWinकरोwSize, व्योम *workspace,
	माप_प्रकार workspaceSize);
/**
 * ZSTD_initDStream_usingDDict() - initialize streaming decompression context
 * @maxWinकरोwSize: The maximum winकरोw size allowed क्रम compressed frames.
 * @ddict:         The digested dictionary to use क्रम decompression.
 * @workspace:     The workspace to emplace the context पूर्णांकo. It must outlive
 *                 the वापसed context.
 * @workspaceSize: The size of workspace.
 *                 Use ZSTD_DStreamWorkspaceBound(maxWinकरोwSize) to determine
 *                 how large the workspace must be.
 *
 * Return:         The zstd streaming decompression context.
 */
ZSTD_DStream *ZSTD_initDStream_usingDDict(माप_प्रकार maxWinकरोwSize,
	स्थिर ZSTD_DDict *ddict, व्योम *workspace, माप_प्रकार workspaceSize);

/*===== Streaming decompression functions =====*/
/**
 * ZSTD_resetDStream() - reset the context using parameters from creation
 * @zds:   The zstd streaming decompression context to reset.
 *
 * Resets the context using the parameters from creation. Skips dictionary
 * loading, since it can be reused.
 *
 * Return: Zero or an error, which can be checked using ZSTD_isError().
 */
माप_प्रकार ZSTD_resetDStream(ZSTD_DStream *zds);
/**
 * ZSTD_decompressStream() - streaming decompress some of input पूर्णांकo output
 * @zds:    The zstd streaming decompression context.
 * @output: Destination buffer. `output.pos` is updated to indicate how much
 *          decompressed data was written.
 * @input:  Source buffer. `input.pos` is updated to indicate how much data was
 *          पढ़ो. Note that it may not consume the entire input, in which हाल
 *          `input.pos < input.size`, and it's up to the caller to present
 *          reमुख्यing data again.
 *
 * The `input` and `output` buffers may be any size. Guaranteed to make some
 * क्रमward progress अगर `input` and `output` are not empty.
 * ZSTD_decompressStream() will not consume the last byte of the frame until
 * the entire frame is flushed.
 *
 * Return:  Returns 0 अगरf a frame is completely decoded and fully flushed.
 *          Otherwise वापसs a hपूर्णांक क्रम the number of bytes to use as the input
 *          क्रम the next function call or an error, which can be checked using
 *          ZSTD_isError(). The size hपूर्णांक will never load more than the frame.
 */
माप_प्रकार ZSTD_decompressStream(ZSTD_DStream *zds, ZSTD_outBuffer *output,
	ZSTD_inBuffer *input);

/**
 * ZSTD_DStreamInSize() - recommended size क्रम the input buffer
 *
 * Return: The recommended size क्रम the input buffer.
 */
माप_प्रकार ZSTD_DStreamInSize(व्योम);
/**
 * ZSTD_DStreamOutSize() - recommended size क्रम the output buffer
 *
 * When the output buffer is at least this large, it is guaranteed to be large
 * enough to flush at least one complete decompressed block.
 *
 * Return: The recommended size क्रम the output buffer.
 */
माप_प्रकार ZSTD_DStreamOutSize(व्योम);


/* --- Constants ---*/
#घोषणा ZSTD_MAGICNUMBER            0xFD2FB528   /* >= v0.8.0 */
#घोषणा ZSTD_MAGIC_SKIPPABLE_START  0x184D2A50U

#घोषणा ZSTD_CONTENTSIZE_UNKNOWN (0ULL - 1)
#घोषणा ZSTD_CONTENTSIZE_ERROR   (0ULL - 2)

#घोषणा ZSTD_WINDOWLOG_MAX_32  27
#घोषणा ZSTD_WINDOWLOG_MAX_64  27
#घोषणा ZSTD_WINDOWLOG_MAX \
	((अचिन्हित पूर्णांक)(माप(माप_प्रकार) == 4 \
		? ZSTD_WINDOWLOG_MAX_32 \
		: ZSTD_WINDOWLOG_MAX_64))
#घोषणा ZSTD_WINDOWLOG_MIN 10
#घोषणा ZSTD_HASHLOG_MAX ZSTD_WINDOWLOG_MAX
#घोषणा ZSTD_HASHLOG_MIN        6
#घोषणा ZSTD_CHAINLOG_MAX     (ZSTD_WINDOWLOG_MAX+1)
#घोषणा ZSTD_CHAINLOG_MIN      ZSTD_HASHLOG_MIN
#घोषणा ZSTD_HASHLOG3_MAX      17
#घोषणा ZSTD_SEARCHLOG_MAX    (ZSTD_WINDOWLOG_MAX-1)
#घोषणा ZSTD_SEARCHLOG_MIN      1
/* only क्रम ZSTD_fast, other strategies are limited to 6 */
#घोषणा ZSTD_SEARCHLENGTH_MAX   7
/* only क्रम ZSTD_btopt, other strategies are limited to 4 */
#घोषणा ZSTD_SEARCHLENGTH_MIN   3
#घोषणा ZSTD_TARGETLENGTH_MIN   4
#घोषणा ZSTD_TARGETLENGTH_MAX 999

/* क्रम अटल allocation */
#घोषणा ZSTD_FRAMEHEADERSIZE_MAX 18
#घोषणा ZSTD_FRAMEHEADERSIZE_MIN  6
#घोषणा ZSTD_frameHeaderSize_prefix 5
#घोषणा ZSTD_frameHeaderSize_min ZSTD_FRAMEHEADERSIZE_MIN
#घोषणा ZSTD_frameHeaderSize_max ZSTD_FRAMEHEADERSIZE_MAX
/* magic number + skippable frame length */
#घोषणा ZSTD_skippableHeaderSize 8


/*-*************************************
 * Compressed size functions
 **************************************/

/**
 * ZSTD_findFrameCompressedSize() - वापसs the size of a compressed frame
 * @src:     Source buffer. It should poपूर्णांक to the start of a zstd encoded frame
 *           or a skippable frame.
 * @srcSize: The size of the source buffer. It must be at least as large as the
 *           size of the frame.
 *
 * Return:   The compressed size of the frame poपूर्णांकed to by `src` or an error,
 *           which can be check with ZSTD_isError().
 *           Suitable to pass to ZSTD_decompress() or similar functions.
 */
माप_प्रकार ZSTD_findFrameCompressedSize(स्थिर व्योम *src, माप_प्रकार srcSize);

/*-*************************************
 * Decompressed size functions
 **************************************/
/**
 * ZSTD_getFrameContentSize() - वापसs the content size in a zstd frame header
 * @src:     It should poपूर्णांक to the start of a zstd encoded frame.
 * @srcSize: The size of the source buffer. It must be at least as large as the
 *           frame header. `ZSTD_frameHeaderSize_max` is always large enough.
 *
 * Return:   The frame content size stored in the frame header अगर known.
 *           `ZSTD_CONTENTSIZE_UNKNOWN` अगर the content size isn't stored in the
 *           frame header. `ZSTD_CONTENTSIZE_ERROR` on invalid input.
 */
अचिन्हित दीर्घ दीर्घ ZSTD_getFrameContentSize(स्थिर व्योम *src, माप_प्रकार srcSize);

/**
 * ZSTD_findDecompressedSize() - वापसs decompressed size of a series of frames
 * @src:     It should poपूर्णांक to the start of a series of zstd encoded and/or
 *           skippable frames.
 * @srcSize: The exact size of the series of frames.
 *
 * If any zstd encoded frame in the series करोesn't have the frame content size
 * set, `ZSTD_CONTENTSIZE_UNKNOWN` is वापसed. But frame content size is always
 * set when using ZSTD_compress(). The decompressed size can be very large.
 * If the source is untrusted, the decompressed size could be wrong or
 * पूर्णांकentionally modअगरied. Always ensure the result fits within the
 * application's authorized limits. ZSTD_findDecompressedSize() handles multiple
 * frames, and so it must traverse the input to पढ़ो each frame header. This is
 * efficient as most of the data is skipped, however it करोes mean that all frame
 * data must be present and valid.
 *
 * Return:   Decompressed size of all the data contained in the frames अगर known.
 *           `ZSTD_CONTENTSIZE_UNKNOWN` अगर the decompressed size is unknown.
 *           `ZSTD_CONTENTSIZE_ERROR` अगर an error occurred.
 */
अचिन्हित दीर्घ दीर्घ ZSTD_findDecompressedSize(स्थिर व्योम *src, माप_प्रकार srcSize);

/*-*************************************
 * Advanced compression functions
 **************************************/
/**
 * ZSTD_checkCParams() - ensure parameter values reमुख्य within authorized range
 * @cParams: The zstd compression parameters.
 *
 * Return:   Zero or an error, which can be checked using ZSTD_isError().
 */
माप_प्रकार ZSTD_checkCParams(ZSTD_compressionParameters cParams);

/**
 * ZSTD_adjustCParams() - optimize parameters क्रम a given srcSize and dictSize
 * @srcSize:  Optionally the estimated source size, or zero अगर unknown.
 * @dictSize: Optionally the estimated dictionary size, or zero अगर unknown.
 *
 * Return:    The optimized parameters.
 */
ZSTD_compressionParameters ZSTD_adjustCParams(
	ZSTD_compressionParameters cParams, अचिन्हित दीर्घ दीर्घ srcSize,
	माप_प्रकार dictSize);

/*--- Advanced decompression functions ---*/

/**
 * ZSTD_isFrame() - वापसs true अगरf the buffer starts with a valid frame
 * @buffer: The source buffer to check.
 * @size:   The size of the source buffer, must be at least 4 bytes.
 *
 * Return: True अगरf the buffer starts with a zstd or skippable frame identअगरier.
 */
अचिन्हित पूर्णांक ZSTD_isFrame(स्थिर व्योम *buffer, माप_प्रकार size);

/**
 * ZSTD_getDictID_fromDict() - वापसs the dictionary id stored in a dictionary
 * @dict:     The dictionary buffer.
 * @dictSize: The size of the dictionary buffer.
 *
 * Return:    The dictionary id stored within the dictionary or 0 अगर the
 *            dictionary is not a zstd dictionary. If it वापसs 0 the
 *            dictionary can still be loaded as a content-only dictionary.
 */
अचिन्हित पूर्णांक ZSTD_getDictID_fromDict(स्थिर व्योम *dict, माप_प्रकार dictSize);

/**
 * ZSTD_getDictID_fromDDict() - वापसs the dictionary id stored in a ZSTD_DDict
 * @ddict: The ddict to find the id of.
 *
 * Return: The dictionary id stored within `ddict` or 0 अगर the dictionary is not
 *         a zstd dictionary. If it वापसs 0 `ddict` will be loaded as a
 *         content-only dictionary.
 */
अचिन्हित पूर्णांक ZSTD_getDictID_fromDDict(स्थिर ZSTD_DDict *ddict);

/**
 * ZSTD_getDictID_fromFrame() - वापसs the dictionary id stored in a zstd frame
 * @src:     Source buffer. It must be a zstd encoded frame.
 * @srcSize: The size of the source buffer. It must be at least as large as the
 *           frame header. `ZSTD_frameHeaderSize_max` is always large enough.
 *
 * Return:   The dictionary id required to decompress the frame stored within
 *           `src` or 0 अगर the dictionary id could not be decoded. It can वापस
 *           0 अगर the frame करोes not require a dictionary, the dictionary id
 *           wasn't stored in the frame, `src` is not a zstd frame, or `srcSize`
 *           is too small.
 */
अचिन्हित पूर्णांक ZSTD_getDictID_fromFrame(स्थिर व्योम *src, माप_प्रकार srcSize);

/**
 * काष्ठा ZSTD_frameParams - zstd frame parameters stored in the frame header
 * @frameContentSize: The frame content size, or 0 अगर not present.
 * @winकरोwSize:       The winकरोw size, or 0 अगर the frame is a skippable frame.
 * @dictID:           The dictionary id, or 0 अगर not present.
 * @checksumFlag:     Whether a checksum was used.
 */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ दीर्घ frameContentSize;
	अचिन्हित पूर्णांक winकरोwSize;
	अचिन्हित पूर्णांक dictID;
	अचिन्हित पूर्णांक checksumFlag;
पूर्ण ZSTD_frameParams;

/**
 * ZSTD_getFrameParams() - extracts parameters from a zstd or skippable frame
 * @fparamsPtr: On success the frame parameters are written here.
 * @src:        The source buffer. It must poपूर्णांक to a zstd or skippable frame.
 * @srcSize:    The size of the source buffer. `ZSTD_frameHeaderSize_max` is
 *              always large enough to succeed.
 *
 * Return:      0 on success. If more data is required it वापसs how many bytes
 *              must be provided to make क्रमward progress. Otherwise it वापसs
 *              an error, which can be checked using ZSTD_isError().
 */
माप_प्रकार ZSTD_getFrameParams(ZSTD_frameParams *fparamsPtr, स्थिर व्योम *src,
	माप_प्रकार srcSize);

/*-*****************************************************************************
 * Buffer-less and synchronous inner streaming functions
 *
 * This is an advanced API, giving full control over buffer management, क्रम
 * users which need direct control over memory.
 * But it's also a complex one, with many restrictions (करोcumented below).
 * Prefer using normal streaming API क्रम an easier experience
 ******************************************************************************/

/*-*****************************************************************************
 * Buffer-less streaming compression (synchronous mode)
 *
 * A ZSTD_CCtx object is required to track streaming operations.
 * Use ZSTD_initCCtx() to initialize a context.
 * ZSTD_CCtx object can be re-used multiple बार within successive compression
 * operations.
 *
 * Start by initializing a context.
 * Use ZSTD_compressBegin(), or ZSTD_compressBegin_usingDict() क्रम dictionary
 * compression,
 * or ZSTD_compressBegin_advanced(), क्रम finer parameter control.
 * It's also possible to duplicate a reference context which has alपढ़ोy been
 * initialized, using ZSTD_copyCCtx()
 *
 * Then, consume your input using ZSTD_compressContinue().
 * There are some important considerations to keep in mind when using this
 * advanced function :
 * - ZSTD_compressContinue() has no पूर्णांकernal buffer. It uses बाह्यally provided
 *   buffer only.
 * - Interface is synchronous : input is consumed entirely and produce 1+
 *   (or more) compressed blocks.
 * - Caller must ensure there is enough space in `dst` to store compressed data
 *   under worst हाल scenario. Worst हाल evaluation is provided by
 *   ZSTD_compressBound().
 *   ZSTD_compressContinue() करोesn't guarantee recover after a failed
 *   compression.
 * - ZSTD_compressContinue() presumes prior input ***is still accessible and
 *   unmodअगरied*** (up to maximum distance size, see WinकरोwLog).
 *   It remembers all previous contiguous blocks, plus one separated memory
 *   segment (which can itself consists of multiple contiguous blocks)
 * - ZSTD_compressContinue() detects that prior input has been overwritten when
 *   `src` buffer overlaps. In which हाल, it will "discard" the relevant memory
 *   section from its history.
 *
 * Finish a frame with ZSTD_compressEnd(), which will ग_लिखो the last block(s)
 * and optional checksum. It's possible to use srcSize==0, in which हाल, it
 * will ग_लिखो a final empty block to end the frame. Without last block mark,
 * frames will be considered unfinished (corrupted) by decoders.
 *
 * `ZSTD_CCtx` object can be re-used (ZSTD_compressBegin()) to compress some new
 * frame.
 ******************************************************************************/

/*=====   Buffer-less streaming compression functions  =====*/
माप_प्रकार ZSTD_compressBegin(ZSTD_CCtx *cctx, पूर्णांक compressionLevel);
माप_प्रकार ZSTD_compressBegin_usingDict(ZSTD_CCtx *cctx, स्थिर व्योम *dict,
	माप_प्रकार dictSize, पूर्णांक compressionLevel);
माप_प्रकार ZSTD_compressBegin_advanced(ZSTD_CCtx *cctx, स्थिर व्योम *dict,
	माप_प्रकार dictSize, ZSTD_parameters params,
	अचिन्हित दीर्घ दीर्घ pledgedSrcSize);
माप_प्रकार ZSTD_copyCCtx(ZSTD_CCtx *cctx, स्थिर ZSTD_CCtx *preparedCCtx,
	अचिन्हित दीर्घ दीर्घ pledgedSrcSize);
माप_प्रकार ZSTD_compressBegin_usingCDict(ZSTD_CCtx *cctx, स्थिर ZSTD_CDict *cdict,
	अचिन्हित दीर्घ दीर्घ pledgedSrcSize);
माप_प्रकार ZSTD_compressContinue(ZSTD_CCtx *cctx, व्योम *dst, माप_प्रकार dstCapacity,
	स्थिर व्योम *src, माप_प्रकार srcSize);
माप_प्रकार ZSTD_compressEnd(ZSTD_CCtx *cctx, व्योम *dst, माप_प्रकार dstCapacity,
	स्थिर व्योम *src, माप_प्रकार srcSize);



/*-*****************************************************************************
 * Buffer-less streaming decompression (synchronous mode)
 *
 * A ZSTD_DCtx object is required to track streaming operations.
 * Use ZSTD_initDCtx() to initialize a context.
 * A ZSTD_DCtx object can be re-used multiple बार.
 *
 * First typical operation is to retrieve frame parameters, using
 * ZSTD_getFrameParams(). It fills a ZSTD_frameParams काष्ठाure which provide
 * important inक्रमmation to correctly decode the frame, such as the minimum
 * rolling buffer size to allocate to decompress data (`winकरोwSize`), and the
 * dictionary ID used.
 * Note: content size is optional, it may not be present. 0 means unknown.
 * Note that these values could be wrong, either because of data malक्रमmation,
 * or because an attacker is spoofing deliberate false inक्रमmation. As a
 * consequence, check that values reमुख्य within valid application range,
 * especially `winकरोwSize`, beक्रमe allocation. Each application can set its own
 * limit, depending on local restrictions. For extended पूर्णांकeroperability, it is
 * recommended to support at least 8 MB.
 * Frame parameters are extracted from the beginning of the compressed frame.
 * Data fragment must be large enough to ensure successful decoding, typically
 * `ZSTD_frameHeaderSize_max` bytes.
 * Result: 0: successful decoding, the `ZSTD_frameParams` काष्ठाure is filled.
 *        >0: `srcSize` is too small, provide at least this many bytes.
 *        errorCode, which can be tested using ZSTD_isError().
 *
 * Start decompression, with ZSTD_decompressBegin() or
 * ZSTD_decompressBegin_usingDict(). Alternatively, you can copy a prepared
 * context, using ZSTD_copyDCtx().
 *
 * Then use ZSTD_nextSrcSizeToDecompress() and ZSTD_decompressContinue()
 * alternatively.
 * ZSTD_nextSrcSizeToDecompress() tells how many bytes to provide as 'srcSize'
 * to ZSTD_decompressContinue().
 * ZSTD_decompressContinue() requires this _exact_ amount of bytes, or it will
 * fail.
 *
 * The result of ZSTD_decompressContinue() is the number of bytes regenerated
 * within 'dst' (necessarily <= dstCapacity). It can be zero, which is not an
 * error; it just means ZSTD_decompressContinue() has decoded some metadata
 * item. It can also be an error code, which can be tested with ZSTD_isError().
 *
 * ZSTD_decompressContinue() needs previous data blocks during decompression, up
 * to `winकरोwSize`. They should preferably be located contiguously, prior to
 * current block. Alternatively, a round buffer of sufficient size is also
 * possible. Sufficient size is determined by frame parameters.
 * ZSTD_decompressContinue() is very sensitive to contiguity, अगर 2 blocks करोn't
 * follow each other, make sure that either the compressor अवरोधs contiguity at
 * the same place, or that previous contiguous segment is large enough to
 * properly handle maximum back-reference.
 *
 * A frame is fully decoded when ZSTD_nextSrcSizeToDecompress() वापसs zero.
 * Context can then be reset to start a new decompression.
 *
 * Note: it's possible to know अगर next input to present is a header or a block,
 * using ZSTD_nextInputType(). This inक्रमmation is not required to properly
 * decode a frame.
 *
 * == Special हाल: skippable frames ==
 *
 * Skippable frames allow पूर्णांकegration of user-defined data पूर्णांकo a flow of
 * concatenated frames. Skippable frames will be ignored (skipped) by a
 * decompressor. The क्रमmat of skippable frames is as follows:
 * a) Skippable frame ID - 4 Bytes, Little endian क्रमmat, any value from
 *    0x184D2A50 to 0x184D2A5F
 * b) Frame Size - 4 Bytes, Little endian क्रमmat, अचिन्हित 32-bits
 * c) Frame Content - any content (User Data) of length equal to Frame Size
 * For skippable frames ZSTD_decompressContinue() always वापसs 0.
 * For skippable frames ZSTD_getFrameParams() वापसs fparamsPtr->winकरोwLog==0
 * what means that a frame is skippable.
 * Note: If fparamsPtr->frameContentSize==0, it is ambiguous: the frame might
 *       actually be a zstd encoded frame with no content. For purposes of
 *       decompression, it is valid in both हालs to skip the frame using
 *       ZSTD_findFrameCompressedSize() to find its size in bytes.
 * It also वापसs frame size as fparamsPtr->frameContentSize.
 ******************************************************************************/

/*=====   Buffer-less streaming decompression functions  =====*/
माप_प्रकार ZSTD_decompressBegin(ZSTD_DCtx *dctx);
माप_प्रकार ZSTD_decompressBegin_usingDict(ZSTD_DCtx *dctx, स्थिर व्योम *dict,
	माप_प्रकार dictSize);
व्योम   ZSTD_copyDCtx(ZSTD_DCtx *dctx, स्थिर ZSTD_DCtx *preparedDCtx);
माप_प्रकार ZSTD_nextSrcSizeToDecompress(ZSTD_DCtx *dctx);
माप_प्रकार ZSTD_decompressContinue(ZSTD_DCtx *dctx, व्योम *dst, माप_प्रकार dstCapacity,
	स्थिर व्योम *src, माप_प्रकार srcSize);
प्रकार क्रमागत अणु
	ZSTDnit_frameHeader,
	ZSTDnit_blockHeader,
	ZSTDnit_block,
	ZSTDnit_lastBlock,
	ZSTDnit_checksum,
	ZSTDnit_skippableFrame
पूर्ण ZSTD_nextInputType_e;
ZSTD_nextInputType_e ZSTD_nextInputType(ZSTD_DCtx *dctx);

/*-*****************************************************************************
 * Block functions
 *
 * Block functions produce and decode raw zstd blocks, without frame metadata.
 * Frame metadata cost is typically ~18 bytes, which can be non-negligible क्रम
 * very small blocks (< 100 bytes). User will have to take in अक्षरge required
 * inक्रमmation to regenerate data, such as compressed and content sizes.
 *
 * A few rules to respect:
 * - Compressing and decompressing require a context काष्ठाure
 *   + Use ZSTD_initCCtx() and ZSTD_initDCtx()
 * - It is necessary to init context beक्रमe starting
 *   + compression : ZSTD_compressBegin()
 *   + decompression : ZSTD_decompressBegin()
 *   + variants _usingDict() are also allowed
 *   + copyCCtx() and copyDCtx() work too
 * - Block size is limited, it must be <= ZSTD_getBlockSizeMax()
 *   + If you need to compress more, cut data पूर्णांकo multiple blocks
 *   + Consider using the regular ZSTD_compress() instead, as frame metadata
 *     costs become negligible when source size is large.
 * - When a block is considered not compressible enough, ZSTD_compressBlock()
 *   result will be zero. In which हाल, nothing is produced पूर्णांकo `dst`.
 *   + User must test क्रम such outcome and deal directly with uncompressed data
 *   + ZSTD_decompressBlock() करोesn't accept uncompressed data as input!!!
 *   + In हाल of multiple successive blocks, decoder must be inक्रमmed of
 *     uncompressed block existence to follow proper history. Use
 *     ZSTD_insertBlock() in such a हाल.
 ******************************************************************************/

/* Define क्रम अटल allocation */
#घोषणा ZSTD_BLOCKSIZE_ABSOLUTEMAX (128 * 1024)
/*=====   Raw zstd block functions  =====*/
माप_प्रकार ZSTD_getBlockSizeMax(ZSTD_CCtx *cctx);
माप_प्रकार ZSTD_compressBlock(ZSTD_CCtx *cctx, व्योम *dst, माप_प्रकार dstCapacity,
	स्थिर व्योम *src, माप_प्रकार srcSize);
माप_प्रकार ZSTD_decompressBlock(ZSTD_DCtx *dctx, व्योम *dst, माप_प्रकार dstCapacity,
	स्थिर व्योम *src, माप_प्रकार srcSize);
माप_प्रकार ZSTD_insertBlock(ZSTD_DCtx *dctx, स्थिर व्योम *blockStart,
	माप_प्रकार blockSize);

#पूर्ण_अगर  /* ZSTD_H */
