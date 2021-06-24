<शैली गुरु>
/**
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

/* ***************************************************************
*  Tuning parameters
*****************************************************************/
/*!
*  MAXWINDOWSIZE_DEFAULT :
*  maximum winकरोw size accepted by DStream, by शेष.
*  Frames requiring more memory will be rejected.
*/
#अगर_अघोषित ZSTD_MAXWINDOWSIZE_DEFAULT
#घोषणा ZSTD_MAXWINDOWSIZE_DEFAULT ((1 << ZSTD_WINDOWLOG_MAX) + 1) /* defined within zstd.h */
#पूर्ण_अगर

/*-*******************************************************
*  Dependencies
*********************************************************/
#समावेश "fse.h"
#समावेश "huf.h"
#समावेश "mem.h" /* low level memory routines */
#समावेश "zstd_internal.h"
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स> /* स_नकल, स_हटाओ, स_रखो */

#घोषणा ZSTD_PREFETCH(ptr) __builtin_prefetch(ptr, 0, 0)

/*-*************************************
*  Macros
***************************************/
#घोषणा ZSTD_isError ERR_isError /* क्रम inlining */
#घोषणा FSE_isError ERR_isError
#घोषणा HUF_isError ERR_isError

/*_*******************************************************
*  Memory operations
**********************************************************/
अटल व्योम ZSTD_copy4(व्योम *dst, स्थिर व्योम *src) अणु स_नकल(dst, src, 4); पूर्ण

/*-*************************************************************
*   Context management
***************************************************************/
प्रकार क्रमागत अणु
	ZSTDds_getFrameHeaderSize,
	ZSTDds_decodeFrameHeader,
	ZSTDds_decodeBlockHeader,
	ZSTDds_decompressBlock,
	ZSTDds_decompressLastBlock,
	ZSTDds_checkChecksum,
	ZSTDds_decodeSkippableHeader,
	ZSTDds_skipFrame
पूर्ण ZSTD_dStage;

प्रकार काष्ठा अणु
	FSE_DTable LLTable[FSE_DTABLE_SIZE_U32(LLFSELog)];
	FSE_DTable OFTable[FSE_DTABLE_SIZE_U32(OffFSELog)];
	FSE_DTable MLTable[FSE_DTABLE_SIZE_U32(MLFSELog)];
	HUF_DTable hufTable[HUF_DTABLE_SIZE(HufLog)]; /* can accommodate HUF_decompress4X */
	U64 workspace[HUF_DECOMPRESS_WORKSPACE_SIZE_U32 / 2];
	U32 rep[ZSTD_REP_NUM];
पूर्ण ZSTD_entropyTables_t;

काष्ठा ZSTD_DCtx_s अणु
	स्थिर FSE_DTable *LLTptr;
	स्थिर FSE_DTable *MLTptr;
	स्थिर FSE_DTable *OFTptr;
	स्थिर HUF_DTable *HUFptr;
	ZSTD_entropyTables_t entropy;
	स्थिर व्योम *previousDstEnd; /* detect continuity */
	स्थिर व्योम *base;	   /* start of curr segment */
	स्थिर व्योम *vBase;	  /* भव start of previous segment अगर it was just beक्रमe curr one */
	स्थिर व्योम *dictEnd;	/* end of previous segment */
	माप_प्रकार expected;
	ZSTD_frameParams fParams;
	blockType_e bType; /* used in ZSTD_decompressContinue(), to transfer blockType between header decoding and block decoding stages */
	ZSTD_dStage stage;
	U32 litEntropy;
	U32 fseEntropy;
	काष्ठा xxh64_state xxhState;
	माप_प्रकार headerSize;
	U32 dictID;
	स्थिर BYTE *litPtr;
	ZSTD_customMem customMem;
	माप_प्रकार litSize;
	माप_प्रकार rleSize;
	BYTE litBuffer[ZSTD_BLOCKSIZE_ABSOLUTEMAX + WILDCOPY_OVERLENGTH];
	BYTE headerBuffer[ZSTD_FRAMEHEADERSIZE_MAX];
पूर्ण; /* प्रकार'd to ZSTD_DCtx within "zstd.h" */

माप_प्रकार ZSTD_DCtxWorkspaceBound(व्योम) अणु वापस ZSTD_ALIGN(माप(ZSTD_stack)) + ZSTD_ALIGN(माप(ZSTD_DCtx)); पूर्ण

माप_प्रकार ZSTD_decompressBegin(ZSTD_DCtx *dctx)
अणु
	dctx->expected = ZSTD_frameHeaderSize_prefix;
	dctx->stage = ZSTDds_getFrameHeaderSize;
	dctx->previousDstEnd = शून्य;
	dctx->base = शून्य;
	dctx->vBase = शून्य;
	dctx->dictEnd = शून्य;
	dctx->entropy.hufTable[0] = (HUF_DTable)((HufLog)*0x1000001); /* cover both little and big endian */
	dctx->litEntropy = dctx->fseEntropy = 0;
	dctx->dictID = 0;
	ZSTD_STATIC_ASSERT(माप(dctx->entropy.rep) == माप(repStartValue));
	स_नकल(dctx->entropy.rep, repStartValue, माप(repStartValue)); /* initial repcodes */
	dctx->LLTptr = dctx->entropy.LLTable;
	dctx->MLTptr = dctx->entropy.MLTable;
	dctx->OFTptr = dctx->entropy.OFTable;
	dctx->HUFptr = dctx->entropy.hufTable;
	वापस 0;
पूर्ण

ZSTD_DCtx *ZSTD_createDCtx_advanced(ZSTD_customMem customMem)
अणु
	ZSTD_DCtx *dctx;

	अगर (!customMem.customAlloc || !customMem.customFree)
		वापस शून्य;

	dctx = (ZSTD_DCtx *)ZSTD_दो_स्मृति(माप(ZSTD_DCtx), customMem);
	अगर (!dctx)
		वापस शून्य;
	स_नकल(&dctx->customMem, &customMem, माप(customMem));
	ZSTD_decompressBegin(dctx);
	वापस dctx;
पूर्ण

ZSTD_DCtx *ZSTD_initDCtx(व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	ZSTD_customMem स्थिर stackMem = ZSTD_initStack(workspace, workspaceSize);
	वापस ZSTD_createDCtx_advanced(stackMem);
पूर्ण

माप_प्रकार ZSTD_मुक्तDCtx(ZSTD_DCtx *dctx)
अणु
	अगर (dctx == शून्य)
		वापस 0; /* support मुक्त on शून्य */
	ZSTD_मुक्त(dctx, dctx->customMem);
	वापस 0; /* reserved as a potential error code in the future */
पूर्ण

व्योम ZSTD_copyDCtx(ZSTD_DCtx *dstDCtx, स्थिर ZSTD_DCtx *srcDCtx)
अणु
	माप_प्रकार स्थिर workSpaceSize = (ZSTD_BLOCKSIZE_ABSOLUTEMAX + WILDCOPY_OVERLENGTH) + ZSTD_frameHeaderSize_max;
	स_नकल(dstDCtx, srcDCtx, माप(ZSTD_DCtx) - workSpaceSize); /* no need to copy workspace */
पूर्ण

अटल व्योम ZSTD_refDDict(ZSTD_DCtx *dstDCtx, स्थिर ZSTD_DDict *ddict);

/*-*************************************************************
*   Decompression section
***************************************************************/

/*! ZSTD_isFrame() :
 *  Tells अगर the content of `buffer` starts with a valid Frame Identअगरier.
 *  Note : Frame Identअगरier is 4 bytes. If `size < 4`, @वापस will always be 0.
 *  Note 2 : Legacy Frame Identअगरiers are considered valid only अगर Legacy Support is enabled.
 *  Note 3 : Skippable Frame Identअगरiers are considered valid. */
अचिन्हित ZSTD_isFrame(स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	अगर (size < 4)
		वापस 0;
	अणु
		U32 स्थिर magic = ZSTD_पढ़ोLE32(buffer);
		अगर (magic == ZSTD_MAGICNUMBER)
			वापस 1;
		अगर ((magic & 0xFFFFFFF0U) == ZSTD_MAGIC_SKIPPABLE_START)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/** ZSTD_frameHeaderSize() :
*   srcSize must be >= ZSTD_frameHeaderSize_prefix.
*   @वापस : size of the Frame Header */
अटल माप_प्रकार ZSTD_frameHeaderSize(स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	अगर (srcSize < ZSTD_frameHeaderSize_prefix)
		वापस ERROR(srcSize_wrong);
	अणु
		BYTE स्थिर fhd = ((स्थिर BYTE *)src)[4];
		U32 स्थिर dictID = fhd & 3;
		U32 स्थिर singleSegment = (fhd >> 5) & 1;
		U32 स्थिर fcsId = fhd >> 6;
		वापस ZSTD_frameHeaderSize_prefix + !singleSegment + ZSTD_did_fieldSize[dictID] + ZSTD_fcs_fieldSize[fcsId] + (singleSegment && !fcsId);
	पूर्ण
पूर्ण

/** ZSTD_getFrameParams() :
*   decode Frame Header, or require larger `srcSize`.
*   @वापस : 0, `fparamsPtr` is correctly filled,
*            >0, `srcSize` is too small, result is expected `srcSize`,
*             or an error code, which can be tested using ZSTD_isError() */
माप_प्रकार ZSTD_getFrameParams(ZSTD_frameParams *fparamsPtr, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *)src;

	अगर (srcSize < ZSTD_frameHeaderSize_prefix)
		वापस ZSTD_frameHeaderSize_prefix;
	अगर (ZSTD_पढ़ोLE32(src) != ZSTD_MAGICNUMBER) अणु
		अगर ((ZSTD_पढ़ोLE32(src) & 0xFFFFFFF0U) == ZSTD_MAGIC_SKIPPABLE_START) अणु
			अगर (srcSize < ZSTD_skippableHeaderSize)
				वापस ZSTD_skippableHeaderSize; /* magic number + skippable frame length */
			स_रखो(fparamsPtr, 0, माप(*fparamsPtr));
			fparamsPtr->frameContentSize = ZSTD_पढ़ोLE32((स्थिर अक्षर *)src + 4);
			fparamsPtr->winकरोwSize = 0; /* winकरोwSize==0 means a frame is skippable */
			वापस 0;
		पूर्ण
		वापस ERROR(prefix_unknown);
	पूर्ण

	/* ensure there is enough `srcSize` to fully पढ़ो/decode frame header */
	अणु
		माप_प्रकार स्थिर fhsize = ZSTD_frameHeaderSize(src, srcSize);
		अगर (srcSize < fhsize)
			वापस fhsize;
	पूर्ण

	अणु
		BYTE स्थिर fhdByte = ip[4];
		माप_प्रकार pos = 5;
		U32 स्थिर dictIDSizeCode = fhdByte & 3;
		U32 स्थिर checksumFlag = (fhdByte >> 2) & 1;
		U32 स्थिर singleSegment = (fhdByte >> 5) & 1;
		U32 स्थिर fcsID = fhdByte >> 6;
		U32 स्थिर winकरोwSizeMax = 1U << ZSTD_WINDOWLOG_MAX;
		U32 winकरोwSize = 0;
		U32 dictID = 0;
		U64 frameContentSize = 0;
		अगर ((fhdByte & 0x08) != 0)
			वापस ERROR(frameParameter_unsupported); /* reserved bits, which must be zero */
		अगर (!singleSegment) अणु
			BYTE स्थिर wlByte = ip[pos++];
			U32 स्थिर winकरोwLog = (wlByte >> 3) + ZSTD_WINDOWLOG_ABSOLUTEMIN;
			अगर (winकरोwLog > ZSTD_WINDOWLOG_MAX)
				वापस ERROR(frameParameter_winकरोwTooLarge); /* aव्योमs issue with 1 << winकरोwLog */
			winकरोwSize = (1U << winकरोwLog);
			winकरोwSize += (winकरोwSize >> 3) * (wlByte & 7);
		पूर्ण

		चयन (dictIDSizeCode) अणु
		शेष: /* impossible */
		हाल 0: अवरोध;
		हाल 1:
			dictID = ip[pos];
			pos++;
			अवरोध;
		हाल 2:
			dictID = ZSTD_पढ़ोLE16(ip + pos);
			pos += 2;
			अवरोध;
		हाल 3:
			dictID = ZSTD_पढ़ोLE32(ip + pos);
			pos += 4;
			अवरोध;
		पूर्ण
		चयन (fcsID) अणु
		शेष: /* impossible */
		हाल 0:
			अगर (singleSegment)
				frameContentSize = ip[pos];
			अवरोध;
		हाल 1: frameContentSize = ZSTD_पढ़ोLE16(ip + pos) + 256; अवरोध;
		हाल 2: frameContentSize = ZSTD_पढ़ोLE32(ip + pos); अवरोध;
		हाल 3: frameContentSize = ZSTD_पढ़ोLE64(ip + pos); अवरोध;
		पूर्ण
		अगर (!winकरोwSize)
			winकरोwSize = (U32)frameContentSize;
		अगर (winकरोwSize > winकरोwSizeMax)
			वापस ERROR(frameParameter_winकरोwTooLarge);
		fparamsPtr->frameContentSize = frameContentSize;
		fparamsPtr->winकरोwSize = winकरोwSize;
		fparamsPtr->dictID = dictID;
		fparamsPtr->checksumFlag = checksumFlag;
	पूर्ण
	वापस 0;
पूर्ण

/** ZSTD_getFrameContentSize() :
*   compatible with legacy mode
*   @वापस : decompressed size of the single frame poपूर्णांकed to be `src` अगर known, otherwise
*             - ZSTD_CONTENTSIZE_UNKNOWN अगर the size cannot be determined
*             - ZSTD_CONTENTSIZE_ERROR अगर an error occurred (e.g. invalid magic number, srcSize too small) */
अचिन्हित दीर्घ दीर्घ ZSTD_getFrameContentSize(स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	अणु
		ZSTD_frameParams fParams;
		अगर (ZSTD_getFrameParams(&fParams, src, srcSize) != 0)
			वापस ZSTD_CONTENTSIZE_ERROR;
		अगर (fParams.winकरोwSize == 0) अणु
			/* Either skippable or empty frame, size == 0 either way */
			वापस 0;
		पूर्ण अन्यथा अगर (fParams.frameContentSize != 0) अणु
			वापस fParams.frameContentSize;
		पूर्ण अन्यथा अणु
			वापस ZSTD_CONTENTSIZE_UNKNOWN;
		पूर्ण
	पूर्ण
पूर्ण

/** ZSTD_findDecompressedSize() :
 *  compatible with legacy mode
 *  `srcSize` must be the exact length of some number of ZSTD compressed and/or
 *      skippable frames
 *  @वापस : decompressed size of the frames contained */
अचिन्हित दीर्घ दीर्घ ZSTD_findDecompressedSize(स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	अणु
		अचिन्हित दीर्घ दीर्घ totalDstSize = 0;
		जबतक (srcSize >= ZSTD_frameHeaderSize_prefix) अणु
			स्थिर U32 magicNumber = ZSTD_पढ़ोLE32(src);

			अगर ((magicNumber & 0xFFFFFFF0U) == ZSTD_MAGIC_SKIPPABLE_START) अणु
				माप_प्रकार skippableSize;
				अगर (srcSize < ZSTD_skippableHeaderSize)
					वापस ERROR(srcSize_wrong);
				skippableSize = ZSTD_पढ़ोLE32((स्थिर BYTE *)src + 4) + ZSTD_skippableHeaderSize;
				अगर (srcSize < skippableSize) अणु
					वापस ZSTD_CONTENTSIZE_ERROR;
				पूर्ण

				src = (स्थिर BYTE *)src + skippableSize;
				srcSize -= skippableSize;
				जारी;
			पूर्ण

			अणु
				अचिन्हित दीर्घ दीर्घ स्थिर ret = ZSTD_getFrameContentSize(src, srcSize);
				अगर (ret >= ZSTD_CONTENTSIZE_ERROR)
					वापस ret;

				/* check क्रम overflow */
				अगर (totalDstSize + ret < totalDstSize)
					वापस ZSTD_CONTENTSIZE_ERROR;
				totalDstSize += ret;
			पूर्ण
			अणु
				माप_प्रकार स्थिर frameSrcSize = ZSTD_findFrameCompressedSize(src, srcSize);
				अगर (ZSTD_isError(frameSrcSize)) अणु
					वापस ZSTD_CONTENTSIZE_ERROR;
				पूर्ण

				src = (स्थिर BYTE *)src + frameSrcSize;
				srcSize -= frameSrcSize;
			पूर्ण
		पूर्ण

		अगर (srcSize) अणु
			वापस ZSTD_CONTENTSIZE_ERROR;
		पूर्ण

		वापस totalDstSize;
	पूर्ण
पूर्ण

/** ZSTD_decodeFrameHeader() :
*   `headerSize` must be the size provided by ZSTD_frameHeaderSize().
*   @वापस : 0 अगर success, or an error code, which can be tested using ZSTD_isError() */
अटल माप_प्रकार ZSTD_decodeFrameHeader(ZSTD_DCtx *dctx, स्थिर व्योम *src, माप_प्रकार headerSize)
अणु
	माप_प्रकार स्थिर result = ZSTD_getFrameParams(&(dctx->fParams), src, headerSize);
	अगर (ZSTD_isError(result))
		वापस result; /* invalid header */
	अगर (result > 0)
		वापस ERROR(srcSize_wrong); /* headerSize too small */
	अगर (dctx->fParams.dictID && (dctx->dictID != dctx->fParams.dictID))
		वापस ERROR(dictionary_wrong);
	अगर (dctx->fParams.checksumFlag)
		xxh64_reset(&dctx->xxhState, 0);
	वापस 0;
पूर्ण

प्रकार काष्ठा अणु
	blockType_e blockType;
	U32 lastBlock;
	U32 origSize;
पूर्ण blockProperties_t;

/*! ZSTD_अ_लोBlockSize() :
*   Provides the size of compressed block from block header `src` */
माप_प्रकार ZSTD_अ_लोBlockSize(स्थिर व्योम *src, माप_प्रकार srcSize, blockProperties_t *bpPtr)
अणु
	अगर (srcSize < ZSTD_blockHeaderSize)
		वापस ERROR(srcSize_wrong);
	अणु
		U32 स्थिर cBlockHeader = ZSTD_पढ़ोLE24(src);
		U32 स्थिर cSize = cBlockHeader >> 3;
		bpPtr->lastBlock = cBlockHeader & 1;
		bpPtr->blockType = (blockType_e)((cBlockHeader >> 1) & 3);
		bpPtr->origSize = cSize; /* only useful क्रम RLE */
		अगर (bpPtr->blockType == bt_rle)
			वापस 1;
		अगर (bpPtr->blockType == bt_reserved)
			वापस ERROR(corruption_detected);
		वापस cSize;
	पूर्ण
पूर्ण

अटल माप_प्रकार ZSTD_copyRawBlock(व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	अगर (srcSize > dstCapacity)
		वापस ERROR(dstSize_tooSmall);
	स_नकल(dst, src, srcSize);
	वापस srcSize;
पूर्ण

अटल माप_प्रकार ZSTD_setRleBlock(व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize, माप_प्रकार regenSize)
अणु
	अगर (srcSize != 1)
		वापस ERROR(srcSize_wrong);
	अगर (regenSize > dstCapacity)
		वापस ERROR(dstSize_tooSmall);
	स_रखो(dst, *(स्थिर BYTE *)src, regenSize);
	वापस regenSize;
पूर्ण

/*! ZSTD_decodeLiteralsBlock() :
	@वापस : nb of bytes पढ़ो from src (< srcSize ) */
माप_प्रकार ZSTD_decodeLiteralsBlock(ZSTD_DCtx *dctx, स्थिर व्योम *src, माप_प्रकार srcSize) /* note : srcSize < BLOCKSIZE */
अणु
	अगर (srcSize < MIN_CBLOCK_SIZE)
		वापस ERROR(corruption_detected);

	अणु
		स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)src;
		symbolEncodingType_e स्थिर litEncType = (symbolEncodingType_e)(istart[0] & 3);

		चयन (litEncType) अणु
		हाल set_repeat:
			अगर (dctx->litEntropy == 0)
				वापस ERROR(dictionary_corrupted);
			fallthrough;
		हाल set_compressed:
			अगर (srcSize < 5)
				वापस ERROR(corruption_detected); /* srcSize >= MIN_CBLOCK_SIZE == 3; here we need up to 5 क्रम हाल 3 */
			अणु
				माप_प्रकार lhSize, litSize, litCSize;
				U32 singleStream = 0;
				U32 स्थिर lhlCode = (istart[0] >> 2) & 3;
				U32 स्थिर lhc = ZSTD_पढ़ोLE32(istart);
				चयन (lhlCode) अणु
				हाल 0:
				हाल 1:
				शेष: /* note : शेष is impossible, since lhlCode पूर्णांकo [0..3] */
					/* 2 - 2 - 10 - 10 */
					singleStream = !lhlCode;
					lhSize = 3;
					litSize = (lhc >> 4) & 0x3FF;
					litCSize = (lhc >> 14) & 0x3FF;
					अवरोध;
				हाल 2:
					/* 2 - 2 - 14 - 14 */
					lhSize = 4;
					litSize = (lhc >> 4) & 0x3FFF;
					litCSize = lhc >> 18;
					अवरोध;
				हाल 3:
					/* 2 - 2 - 18 - 18 */
					lhSize = 5;
					litSize = (lhc >> 4) & 0x3FFFF;
					litCSize = (lhc >> 22) + (istart[4] << 10);
					अवरोध;
				पूर्ण
				अगर (litSize > ZSTD_BLOCKSIZE_ABSOLUTEMAX)
					वापस ERROR(corruption_detected);
				अगर (litCSize + lhSize > srcSize)
					वापस ERROR(corruption_detected);

				अगर (HUF_isError(
					(litEncType == set_repeat)
					    ? (singleStream ? HUF_decompress1X_usingDTable(dctx->litBuffer, litSize, istart + lhSize, litCSize, dctx->HUFptr)
							    : HUF_decompress4X_usingDTable(dctx->litBuffer, litSize, istart + lhSize, litCSize, dctx->HUFptr))
					    : (singleStream
						   ? HUF_decompress1X2_DCtx_wksp(dctx->entropy.hufTable, dctx->litBuffer, litSize, istart + lhSize, litCSize,
										 dctx->entropy.workspace, माप(dctx->entropy.workspace))
						   : HUF_decompress4X_hufOnly_wksp(dctx->entropy.hufTable, dctx->litBuffer, litSize, istart + lhSize, litCSize,
										   dctx->entropy.workspace, माप(dctx->entropy.workspace)))))
					वापस ERROR(corruption_detected);

				dctx->litPtr = dctx->litBuffer;
				dctx->litSize = litSize;
				dctx->litEntropy = 1;
				अगर (litEncType == set_compressed)
					dctx->HUFptr = dctx->entropy.hufTable;
				स_रखो(dctx->litBuffer + dctx->litSize, 0, WILDCOPY_OVERLENGTH);
				वापस litCSize + lhSize;
			पूर्ण

		हाल set_basic: अणु
			माप_प्रकार litSize, lhSize;
			U32 स्थिर lhlCode = ((istart[0]) >> 2) & 3;
			चयन (lhlCode) अणु
			हाल 0:
			हाल 2:
			शेष: /* note : शेष is impossible, since lhlCode पूर्णांकo [0..3] */
				lhSize = 1;
				litSize = istart[0] >> 3;
				अवरोध;
			हाल 1:
				lhSize = 2;
				litSize = ZSTD_पढ़ोLE16(istart) >> 4;
				अवरोध;
			हाल 3:
				lhSize = 3;
				litSize = ZSTD_पढ़ोLE24(istart) >> 4;
				अवरोध;
			पूर्ण

			अगर (lhSize + litSize + WILDCOPY_OVERLENGTH > srcSize) अणु /* risk पढ़ोing beyond src buffer with wildcopy */
				अगर (litSize + lhSize > srcSize)
					वापस ERROR(corruption_detected);
				स_नकल(dctx->litBuffer, istart + lhSize, litSize);
				dctx->litPtr = dctx->litBuffer;
				dctx->litSize = litSize;
				स_रखो(dctx->litBuffer + dctx->litSize, 0, WILDCOPY_OVERLENGTH);
				वापस lhSize + litSize;
			पूर्ण
			/* direct reference पूर्णांकo compressed stream */
			dctx->litPtr = istart + lhSize;
			dctx->litSize = litSize;
			वापस lhSize + litSize;
		पूर्ण

		हाल set_rle: अणु
			U32 स्थिर lhlCode = ((istart[0]) >> 2) & 3;
			माप_प्रकार litSize, lhSize;
			चयन (lhlCode) अणु
			हाल 0:
			हाल 2:
			शेष: /* note : शेष is impossible, since lhlCode पूर्णांकo [0..3] */
				lhSize = 1;
				litSize = istart[0] >> 3;
				अवरोध;
			हाल 1:
				lhSize = 2;
				litSize = ZSTD_पढ़ोLE16(istart) >> 4;
				अवरोध;
			हाल 3:
				lhSize = 3;
				litSize = ZSTD_पढ़ोLE24(istart) >> 4;
				अगर (srcSize < 4)
					वापस ERROR(corruption_detected); /* srcSize >= MIN_CBLOCK_SIZE == 3; here we need lhSize+1 = 4 */
				अवरोध;
			पूर्ण
			अगर (litSize > ZSTD_BLOCKSIZE_ABSOLUTEMAX)
				वापस ERROR(corruption_detected);
			स_रखो(dctx->litBuffer, istart[lhSize], litSize + WILDCOPY_OVERLENGTH);
			dctx->litPtr = dctx->litBuffer;
			dctx->litSize = litSize;
			वापस lhSize + 1;
		पूर्ण
		शेष:
			वापस ERROR(corruption_detected); /* impossible */
		पूर्ण
	पूर्ण
पूर्ण

प्रकार जोड़ अणु
	FSE_decode_t realData;
	U32 alignedBy4;
पूर्ण FSE_decode_t4;

अटल स्थिर FSE_decode_t4 LL_शेषDTable[(1 << LL_DEFAULTNORMLOG) + 1] = अणु
    अणुअणुLL_DEFAULTNORMLOG, 1, 1पूर्णपूर्ण, /* header : tableLog, fastMode, fastMode */
    अणुअणु0, 0, 4पूर्णपूर्ण,		 /* 0 : base, symbol, bits */
    अणुअणु16, 0, 4पूर्णपूर्ण,
    अणुअणु32, 1, 5पूर्णपूर्ण,
    अणुअणु0, 3, 5पूर्णपूर्ण,
    अणुअणु0, 4, 5पूर्णपूर्ण,
    अणुअणु0, 6, 5पूर्णपूर्ण,
    अणुअणु0, 7, 5पूर्णपूर्ण,
    अणुअणु0, 9, 5पूर्णपूर्ण,
    अणुअणु0, 10, 5पूर्णपूर्ण,
    अणुअणु0, 12, 5पूर्णपूर्ण,
    अणुअणु0, 14, 6पूर्णपूर्ण,
    अणुअणु0, 16, 5पूर्णपूर्ण,
    अणुअणु0, 18, 5पूर्णपूर्ण,
    अणुअणु0, 19, 5पूर्णपूर्ण,
    अणुअणु0, 21, 5पूर्णपूर्ण,
    अणुअणु0, 22, 5पूर्णपूर्ण,
    अणुअणु0, 24, 5पूर्णपूर्ण,
    अणुअणु32, 25, 5पूर्णपूर्ण,
    अणुअणु0, 26, 5पूर्णपूर्ण,
    अणुअणु0, 27, 6पूर्णपूर्ण,
    अणुअणु0, 29, 6पूर्णपूर्ण,
    अणुअणु0, 31, 6पूर्णपूर्ण,
    अणुअणु32, 0, 4पूर्णपूर्ण,
    अणुअणु0, 1, 4पूर्णपूर्ण,
    अणुअणु0, 2, 5पूर्णपूर्ण,
    अणुअणु32, 4, 5पूर्णपूर्ण,
    अणुअणु0, 5, 5पूर्णपूर्ण,
    अणुअणु32, 7, 5पूर्णपूर्ण,
    अणुअणु0, 8, 5पूर्णपूर्ण,
    अणुअणु32, 10, 5पूर्णपूर्ण,
    अणुअणु0, 11, 5पूर्णपूर्ण,
    अणुअणु0, 13, 6पूर्णपूर्ण,
    अणुअणु32, 16, 5पूर्णपूर्ण,
    अणुअणु0, 17, 5पूर्णपूर्ण,
    अणुअणु32, 19, 5पूर्णपूर्ण,
    अणुअणु0, 20, 5पूर्णपूर्ण,
    अणुअणु32, 22, 5पूर्णपूर्ण,
    अणुअणु0, 23, 5पूर्णपूर्ण,
    अणुअणु0, 25, 4पूर्णपूर्ण,
    अणुअणु16, 25, 4पूर्णपूर्ण,
    अणुअणु32, 26, 5पूर्णपूर्ण,
    अणुअणु0, 28, 6पूर्णपूर्ण,
    अणुअणु0, 30, 6पूर्णपूर्ण,
    अणुअणु48, 0, 4पूर्णपूर्ण,
    अणुअणु16, 1, 4पूर्णपूर्ण,
    अणुअणु32, 2, 5पूर्णपूर्ण,
    अणुअणु32, 3, 5पूर्णपूर्ण,
    अणुअणु32, 5, 5पूर्णपूर्ण,
    अणुअणु32, 6, 5पूर्णपूर्ण,
    अणुअणु32, 8, 5पूर्णपूर्ण,
    अणुअणु32, 9, 5पूर्णपूर्ण,
    अणुअणु32, 11, 5पूर्णपूर्ण,
    अणुअणु32, 12, 5पूर्णपूर्ण,
    अणुअणु0, 15, 6पूर्णपूर्ण,
    अणुअणु32, 17, 5पूर्णपूर्ण,
    अणुअणु32, 18, 5पूर्णपूर्ण,
    अणुअणु32, 20, 5पूर्णपूर्ण,
    अणुअणु32, 21, 5पूर्णपूर्ण,
    अणुअणु32, 23, 5पूर्णपूर्ण,
    अणुअणु32, 24, 5पूर्णपूर्ण,
    अणुअणु0, 35, 6पूर्णपूर्ण,
    अणुअणु0, 34, 6पूर्णपूर्ण,
    अणुअणु0, 33, 6पूर्णपूर्ण,
    अणुअणु0, 32, 6पूर्णपूर्ण,
पूर्ण; /* LL_शेषDTable */

अटल स्थिर FSE_decode_t4 ML_शेषDTable[(1 << ML_DEFAULTNORMLOG) + 1] = अणु
    अणुअणुML_DEFAULTNORMLOG, 1, 1पूर्णपूर्ण, /* header : tableLog, fastMode, fastMode */
    अणुअणु0, 0, 6पूर्णपूर्ण,		 /* 0 : base, symbol, bits */
    अणुअणु0, 1, 4पूर्णपूर्ण,
    अणुअणु32, 2, 5पूर्णपूर्ण,
    अणुअणु0, 3, 5पूर्णपूर्ण,
    अणुअणु0, 5, 5पूर्णपूर्ण,
    अणुअणु0, 6, 5पूर्णपूर्ण,
    अणुअणु0, 8, 5पूर्णपूर्ण,
    अणुअणु0, 10, 6पूर्णपूर्ण,
    अणुअणु0, 13, 6पूर्णपूर्ण,
    अणुअणु0, 16, 6पूर्णपूर्ण,
    अणुअणु0, 19, 6पूर्णपूर्ण,
    अणुअणु0, 22, 6पूर्णपूर्ण,
    अणुअणु0, 25, 6पूर्णपूर्ण,
    अणुअणु0, 28, 6पूर्णपूर्ण,
    अणुअणु0, 31, 6पूर्णपूर्ण,
    अणुअणु0, 33, 6पूर्णपूर्ण,
    अणुअणु0, 35, 6पूर्णपूर्ण,
    अणुअणु0, 37, 6पूर्णपूर्ण,
    अणुअणु0, 39, 6पूर्णपूर्ण,
    अणुअणु0, 41, 6पूर्णपूर्ण,
    अणुअणु0, 43, 6पूर्णपूर्ण,
    अणुअणु0, 45, 6पूर्णपूर्ण,
    अणुअणु16, 1, 4पूर्णपूर्ण,
    अणुअणु0, 2, 4पूर्णपूर्ण,
    अणुअणु32, 3, 5पूर्णपूर्ण,
    अणुअणु0, 4, 5पूर्णपूर्ण,
    अणुअणु32, 6, 5पूर्णपूर्ण,
    अणुअणु0, 7, 5पूर्णपूर्ण,
    अणुअणु0, 9, 6पूर्णपूर्ण,
    अणुअणु0, 12, 6पूर्णपूर्ण,
    अणुअणु0, 15, 6पूर्णपूर्ण,
    अणुअणु0, 18, 6पूर्णपूर्ण,
    अणुअणु0, 21, 6पूर्णपूर्ण,
    अणुअणु0, 24, 6पूर्णपूर्ण,
    अणुअणु0, 27, 6पूर्णपूर्ण,
    अणुअणु0, 30, 6पूर्णपूर्ण,
    अणुअणु0, 32, 6पूर्णपूर्ण,
    अणुअणु0, 34, 6पूर्णपूर्ण,
    अणुअणु0, 36, 6पूर्णपूर्ण,
    अणुअणु0, 38, 6पूर्णपूर्ण,
    अणुअणु0, 40, 6पूर्णपूर्ण,
    अणुअणु0, 42, 6पूर्णपूर्ण,
    अणुअणु0, 44, 6पूर्णपूर्ण,
    अणुअणु32, 1, 4पूर्णपूर्ण,
    अणुअणु48, 1, 4पूर्णपूर्ण,
    अणुअणु16, 2, 4पूर्णपूर्ण,
    अणुअणु32, 4, 5पूर्णपूर्ण,
    अणुअणु32, 5, 5पूर्णपूर्ण,
    अणुअणु32, 7, 5पूर्णपूर्ण,
    अणुअणु32, 8, 5पूर्णपूर्ण,
    अणुअणु0, 11, 6पूर्णपूर्ण,
    अणुअणु0, 14, 6पूर्णपूर्ण,
    अणुअणु0, 17, 6पूर्णपूर्ण,
    अणुअणु0, 20, 6पूर्णपूर्ण,
    अणुअणु0, 23, 6पूर्णपूर्ण,
    अणुअणु0, 26, 6पूर्णपूर्ण,
    अणुअणु0, 29, 6पूर्णपूर्ण,
    अणुअणु0, 52, 6पूर्णपूर्ण,
    अणुअणु0, 51, 6पूर्णपूर्ण,
    अणुअणु0, 50, 6पूर्णपूर्ण,
    अणुअणु0, 49, 6पूर्णपूर्ण,
    अणुअणु0, 48, 6पूर्णपूर्ण,
    अणुअणु0, 47, 6पूर्णपूर्ण,
    अणुअणु0, 46, 6पूर्णपूर्ण,
पूर्ण; /* ML_शेषDTable */

अटल स्थिर FSE_decode_t4 OF_शेषDTable[(1 << OF_DEFAULTNORMLOG) + 1] = अणु
    अणुअणुOF_DEFAULTNORMLOG, 1, 1पूर्णपूर्ण, /* header : tableLog, fastMode, fastMode */
    अणुअणु0, 0, 5पूर्णपूर्ण,		 /* 0 : base, symbol, bits */
    अणुअणु0, 6, 4पूर्णपूर्ण,
    अणुअणु0, 9, 5पूर्णपूर्ण,
    अणुअणु0, 15, 5पूर्णपूर्ण,
    अणुअणु0, 21, 5पूर्णपूर्ण,
    अणुअणु0, 3, 5पूर्णपूर्ण,
    अणुअणु0, 7, 4पूर्णपूर्ण,
    अणुअणु0, 12, 5पूर्णपूर्ण,
    अणुअणु0, 18, 5पूर्णपूर्ण,
    अणुअणु0, 23, 5पूर्णपूर्ण,
    अणुअणु0, 5, 5पूर्णपूर्ण,
    अणुअणु0, 8, 4पूर्णपूर्ण,
    अणुअणु0, 14, 5पूर्णपूर्ण,
    अणुअणु0, 20, 5पूर्णपूर्ण,
    अणुअणु0, 2, 5पूर्णपूर्ण,
    अणुअणु16, 7, 4पूर्णपूर्ण,
    अणुअणु0, 11, 5पूर्णपूर्ण,
    अणुअणु0, 17, 5पूर्णपूर्ण,
    अणुअणु0, 22, 5पूर्णपूर्ण,
    अणुअणु0, 4, 5पूर्णपूर्ण,
    अणुअणु16, 8, 4पूर्णपूर्ण,
    अणुअणु0, 13, 5पूर्णपूर्ण,
    अणुअणु0, 19, 5पूर्णपूर्ण,
    अणुअणु0, 1, 5पूर्णपूर्ण,
    अणुअणु16, 6, 4पूर्णपूर्ण,
    अणुअणु0, 10, 5पूर्णपूर्ण,
    अणुअणु0, 16, 5पूर्णपूर्ण,
    अणुअणु0, 28, 5पूर्णपूर्ण,
    अणुअणु0, 27, 5पूर्णपूर्ण,
    अणुअणु0, 26, 5पूर्णपूर्ण,
    अणुअणु0, 25, 5पूर्णपूर्ण,
    अणुअणु0, 24, 5पूर्णपूर्ण,
पूर्ण; /* OF_शेषDTable */

/*! ZSTD_buildSeqTable() :
	@वापस : nb bytes पढ़ो from src,
			  or an error code अगर it fails, testable with ZSTD_isError()
*/
अटल माप_प्रकार ZSTD_buildSeqTable(FSE_DTable *DTableSpace, स्थिर FSE_DTable **DTablePtr, symbolEncodingType_e type, U32 max, U32 maxLog, स्थिर व्योम *src,
				 माप_प्रकार srcSize, स्थिर FSE_decode_t4 *शेषTable, U32 flagRepeatTable, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	स्थिर व्योम *स्थिर पंचांगpPtr = शेषTable; /* bypass strict aliasing */
	चयन (type) अणु
	हाल set_rle:
		अगर (!srcSize)
			वापस ERROR(srcSize_wrong);
		अगर ((*(स्थिर BYTE *)src) > max)
			वापस ERROR(corruption_detected);
		FSE_buildDTable_rle(DTableSpace, *(स्थिर BYTE *)src);
		*DTablePtr = DTableSpace;
		वापस 1;
	हाल set_basic: *DTablePtr = (स्थिर FSE_DTable *)पंचांगpPtr; वापस 0;
	हाल set_repeat:
		अगर (!flagRepeatTable)
			वापस ERROR(corruption_detected);
		वापस 0;
	शेष: /* impossible */
	हाल set_compressed: अणु
		U32 tableLog;
		S16 *norm = (S16 *)workspace;
		माप_प्रकार स्थिर spaceUsed32 = ALIGN(माप(S16) * (MaxSeq + 1), माप(U32)) >> 2;

		अगर ((spaceUsed32 << 2) > workspaceSize)
			वापस ERROR(GENERIC);
		workspace = (U32 *)workspace + spaceUsed32;
		workspaceSize -= (spaceUsed32 << 2);
		अणु
			माप_प्रकार स्थिर headerSize = FSE_पढ़ोNCount(norm, &max, &tableLog, src, srcSize);
			अगर (FSE_isError(headerSize))
				वापस ERROR(corruption_detected);
			अगर (tableLog > maxLog)
				वापस ERROR(corruption_detected);
			FSE_buildDTable_wksp(DTableSpace, norm, max, tableLog, workspace, workspaceSize);
			*DTablePtr = DTableSpace;
			वापस headerSize;
		पूर्ण
	पूर्ण
	पूर्ण
पूर्ण

माप_प्रकार ZSTD_decodeSeqHeaders(ZSTD_DCtx *dctx, पूर्णांक *nbSeqPtr, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	स्थिर BYTE *स्थिर istart = (स्थिर BYTE *स्थिर)src;
	स्थिर BYTE *स्थिर iend = istart + srcSize;
	स्थिर BYTE *ip = istart;

	/* check */
	अगर (srcSize < MIN_SEQUENCES_SIZE)
		वापस ERROR(srcSize_wrong);

	/* SeqHead */
	अणु
		पूर्णांक nbSeq = *ip++;
		अगर (!nbSeq) अणु
			*nbSeqPtr = 0;
			वापस 1;
		पूर्ण
		अगर (nbSeq > 0x7F) अणु
			अगर (nbSeq == 0xFF) अणु
				अगर (ip + 2 > iend)
					वापस ERROR(srcSize_wrong);
				nbSeq = ZSTD_पढ़ोLE16(ip) + LONGNBSEQ, ip += 2;
			पूर्ण अन्यथा अणु
				अगर (ip >= iend)
					वापस ERROR(srcSize_wrong);
				nbSeq = ((nbSeq - 0x80) << 8) + *ip++;
			पूर्ण
		पूर्ण
		*nbSeqPtr = nbSeq;
	पूर्ण

	/* FSE table descriptors */
	अगर (ip + 4 > iend)
		वापस ERROR(srcSize_wrong); /* minimum possible size */
	अणु
		symbolEncodingType_e स्थिर LLtype = (symbolEncodingType_e)(*ip >> 6);
		symbolEncodingType_e स्थिर OFtype = (symbolEncodingType_e)((*ip >> 4) & 3);
		symbolEncodingType_e स्थिर MLtype = (symbolEncodingType_e)((*ip >> 2) & 3);
		ip++;

		/* Build DTables */
		अणु
			माप_प्रकार स्थिर llhSize = ZSTD_buildSeqTable(dctx->entropy.LLTable, &dctx->LLTptr, LLtype, MaxLL, LLFSELog, ip, iend - ip,
								  LL_शेषDTable, dctx->fseEntropy, dctx->entropy.workspace, माप(dctx->entropy.workspace));
			अगर (ZSTD_isError(llhSize))
				वापस ERROR(corruption_detected);
			ip += llhSize;
		पूर्ण
		अणु
			माप_प्रकार स्थिर ofhSize = ZSTD_buildSeqTable(dctx->entropy.OFTable, &dctx->OFTptr, OFtype, MaxOff, OffFSELog, ip, iend - ip,
								  OF_शेषDTable, dctx->fseEntropy, dctx->entropy.workspace, माप(dctx->entropy.workspace));
			अगर (ZSTD_isError(ofhSize))
				वापस ERROR(corruption_detected);
			ip += ofhSize;
		पूर्ण
		अणु
			माप_प्रकार स्थिर mlhSize = ZSTD_buildSeqTable(dctx->entropy.MLTable, &dctx->MLTptr, MLtype, MaxML, MLFSELog, ip, iend - ip,
								  ML_शेषDTable, dctx->fseEntropy, dctx->entropy.workspace, माप(dctx->entropy.workspace));
			अगर (ZSTD_isError(mlhSize))
				वापस ERROR(corruption_detected);
			ip += mlhSize;
		पूर्ण
	पूर्ण

	वापस ip - istart;
पूर्ण

प्रकार काष्ठा अणु
	माप_प्रकार litLength;
	माप_प्रकार matchLength;
	माप_प्रकार offset;
	स्थिर BYTE *match;
पूर्ण seq_t;

प्रकार काष्ठा अणु
	BIT_DStream_t DStream;
	FSE_DState_t stateLL;
	FSE_DState_t stateOffb;
	FSE_DState_t stateML;
	माप_प्रकार prevOffset[ZSTD_REP_NUM];
	स्थिर BYTE *base;
	माप_प्रकार pos;
	uPtrDअगरf जाओDict;
पूर्ण seqState_t;

FORCE_NOINLINE
माप_प्रकार ZSTD_execSequenceLast7(BYTE *op, BYTE *स्थिर oend, seq_t sequence, स्थिर BYTE **litPtr, स्थिर BYTE *स्थिर litLimit, स्थिर BYTE *स्थिर base,
			      स्थिर BYTE *स्थिर vBase, स्थिर BYTE *स्थिर dictEnd)
अणु
	BYTE *स्थिर oLitEnd = op + sequence.litLength;
	माप_प्रकार स्थिर sequenceLength = sequence.litLength + sequence.matchLength;
	BYTE *स्थिर oMatchEnd = op + sequenceLength; /* risk : address space overflow (32-bits) */
	BYTE *स्थिर oend_w = oend - WILDCOPY_OVERLENGTH;
	स्थिर BYTE *स्थिर iLitEnd = *litPtr + sequence.litLength;
	स्थिर BYTE *match = oLitEnd - sequence.offset;

	/* check */
	अगर (oMatchEnd > oend)
		वापस ERROR(dstSize_tooSmall); /* last match must start at a minimum distance of WILDCOPY_OVERLENGTH from oend */
	अगर (iLitEnd > litLimit)
		वापस ERROR(corruption_detected); /* over-पढ़ो beyond lit buffer */
	अगर (oLitEnd <= oend_w)
		वापस ERROR(GENERIC); /* Precondition */

	/* copy literals */
	अगर (op < oend_w) अणु
		ZSTD_wildcopy(op, *litPtr, oend_w - op);
		*litPtr += oend_w - op;
		op = oend_w;
	पूर्ण
	जबतक (op < oLitEnd)
		*op++ = *(*litPtr)++;

	/* copy Match */
	अगर (sequence.offset > (माप_प्रकार)(oLitEnd - base)) अणु
		/* offset beyond prefix */
		अगर (sequence.offset > (माप_प्रकार)(oLitEnd - vBase))
			वापस ERROR(corruption_detected);
		match = dictEnd - (base - match);
		अगर (match + sequence.matchLength <= dictEnd) अणु
			स_हटाओ(oLitEnd, match, sequence.matchLength);
			वापस sequenceLength;
		पूर्ण
		/* span extDict & currPrefixSegment */
		अणु
			माप_प्रकार स्थिर length1 = dictEnd - match;
			स_हटाओ(oLitEnd, match, length1);
			op = oLitEnd + length1;
			sequence.matchLength -= length1;
			match = base;
		पूर्ण
	पूर्ण
	जबतक (op < oMatchEnd)
		*op++ = *match++;
	वापस sequenceLength;
पूर्ण

अटल seq_t ZSTD_decodeSequence(seqState_t *seqState)
अणु
	seq_t seq;

	U32 स्थिर llCode = FSE_peekSymbol(&seqState->stateLL);
	U32 स्थिर mlCode = FSE_peekSymbol(&seqState->stateML);
	U32 स्थिर ofCode = FSE_peekSymbol(&seqState->stateOffb); /* <= maxOff, by table स्थिरruction */

	U32 स्थिर llBits = LL_bits[llCode];
	U32 स्थिर mlBits = ML_bits[mlCode];
	U32 स्थिर ofBits = ofCode;
	U32 स्थिर totalBits = llBits + mlBits + ofBits;

	अटल स्थिर U32 LL_base[MaxLL + 1] = अणु0,  1,  2,  3,  4,  5,  6,  7,  8,    9,     10,    11,    12,    13,     14,     15,     16,     18,
					       20, 22, 24, 28, 32, 40, 48, 64, 0x80, 0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000, 0x10000पूर्ण;

	अटल स्थिर U32 ML_base[MaxML + 1] = अणु3,  4,  5,  6,  7,  8,  9,  10,   11,    12,    13,    14,    15,     16,     17,     18,     19,     20,
					       21, 22, 23, 24, 25, 26, 27, 28,   29,    30,    31,    32,    33,     34,     35,     37,     39,     41,
					       43, 47, 51, 59, 67, 83, 99, 0x83, 0x103, 0x203, 0x403, 0x803, 0x1003, 0x2003, 0x4003, 0x8003, 0x10003पूर्ण;

	अटल स्थिर U32 OF_base[MaxOff + 1] = अणु0,       1,	1,	5,	0xD,      0x1D,      0x3D,      0x7D,      0xFD,     0x1FD,
						0x3FD,   0x7FD,    0xFFD,    0x1FFD,   0x3FFD,   0x7FFD,    0xFFFD,    0x1FFFD,   0x3FFFD,  0x7FFFD,
						0xFFFFD, 0x1FFFFD, 0x3FFFFD, 0x7FFFFD, 0xFFFFFD, 0x1FFFFFD, 0x3FFFFFD, 0x7FFFFFD, 0xFFFFFFDपूर्ण;

	/* sequence */
	अणु
		माप_प्रकार offset;
		अगर (!ofCode)
			offset = 0;
		अन्यथा अणु
			offset = OF_base[ofCode] + BIT_पढ़ोBitsFast(&seqState->DStream, ofBits); /* <=  (ZSTD_WINDOWLOG_MAX-1) bits */
			अगर (ZSTD_32bits())
				BIT_reloadDStream(&seqState->DStream);
		पूर्ण

		अगर (ofCode <= 1) अणु
			offset += (llCode == 0);
			अगर (offset) अणु
				माप_प्रकार temp = (offset == 3) ? seqState->prevOffset[0] - 1 : seqState->prevOffset[offset];
				temp += !temp; /* 0 is not valid; input is corrupted; क्रमce offset to 1 */
				अगर (offset != 1)
					seqState->prevOffset[2] = seqState->prevOffset[1];
				seqState->prevOffset[1] = seqState->prevOffset[0];
				seqState->prevOffset[0] = offset = temp;
			पूर्ण अन्यथा अणु
				offset = seqState->prevOffset[0];
			पूर्ण
		पूर्ण अन्यथा अणु
			seqState->prevOffset[2] = seqState->prevOffset[1];
			seqState->prevOffset[1] = seqState->prevOffset[0];
			seqState->prevOffset[0] = offset;
		पूर्ण
		seq.offset = offset;
	पूर्ण

	seq.matchLength = ML_base[mlCode] + ((mlCode > 31) ? BIT_पढ़ोBitsFast(&seqState->DStream, mlBits) : 0); /* <=  16 bits */
	अगर (ZSTD_32bits() && (mlBits + llBits > 24))
		BIT_reloadDStream(&seqState->DStream);

	seq.litLength = LL_base[llCode] + ((llCode > 15) ? BIT_पढ़ोBitsFast(&seqState->DStream, llBits) : 0); /* <=  16 bits */
	अगर (ZSTD_32bits() || (totalBits > 64 - 7 - (LLFSELog + MLFSELog + OffFSELog)))
		BIT_reloadDStream(&seqState->DStream);

	/* ANS state update */
	FSE_updateState(&seqState->stateLL, &seqState->DStream); /* <=  9 bits */
	FSE_updateState(&seqState->stateML, &seqState->DStream); /* <=  9 bits */
	अगर (ZSTD_32bits())
		BIT_reloadDStream(&seqState->DStream);		   /* <= 18 bits */
	FSE_updateState(&seqState->stateOffb, &seqState->DStream); /* <=  8 bits */

	seq.match = शून्य;

	वापस seq;
पूर्ण

FORCE_INLINE
माप_प्रकार ZSTD_execSequence(BYTE *op, BYTE *स्थिर oend, seq_t sequence, स्थिर BYTE **litPtr, स्थिर BYTE *स्थिर litLimit, स्थिर BYTE *स्थिर base,
			 स्थिर BYTE *स्थिर vBase, स्थिर BYTE *स्थिर dictEnd)
अणु
	BYTE *स्थिर oLitEnd = op + sequence.litLength;
	माप_प्रकार स्थिर sequenceLength = sequence.litLength + sequence.matchLength;
	BYTE *स्थिर oMatchEnd = op + sequenceLength; /* risk : address space overflow (32-bits) */
	BYTE *स्थिर oend_w = oend - WILDCOPY_OVERLENGTH;
	स्थिर BYTE *स्थिर iLitEnd = *litPtr + sequence.litLength;
	स्थिर BYTE *match = oLitEnd - sequence.offset;

	/* check */
	अगर (oMatchEnd > oend)
		वापस ERROR(dstSize_tooSmall); /* last match must start at a minimum distance of WILDCOPY_OVERLENGTH from oend */
	अगर (iLitEnd > litLimit)
		वापस ERROR(corruption_detected); /* over-पढ़ो beyond lit buffer */
	अगर (oLitEnd > oend_w)
		वापस ZSTD_execSequenceLast7(op, oend, sequence, litPtr, litLimit, base, vBase, dictEnd);

	/* copy Literals */
	ZSTD_copy8(op, *litPtr);
	अगर (sequence.litLength > 8)
		ZSTD_wildcopy(op + 8, (*litPtr) + 8,
			      sequence.litLength - 8); /* note : since oLitEnd <= oend-WILDCOPY_OVERLENGTH, no risk of overग_लिखो beyond oend */
	op = oLitEnd;
	*litPtr = iLitEnd; /* update क्रम next sequence */

	/* copy Match */
	अगर (sequence.offset > (माप_प्रकार)(oLitEnd - base)) अणु
		/* offset beyond prefix */
		अगर (sequence.offset > (माप_प्रकार)(oLitEnd - vBase))
			वापस ERROR(corruption_detected);
		match = dictEnd + (match - base);
		अगर (match + sequence.matchLength <= dictEnd) अणु
			स_हटाओ(oLitEnd, match, sequence.matchLength);
			वापस sequenceLength;
		पूर्ण
		/* span extDict & currPrefixSegment */
		अणु
			माप_प्रकार स्थिर length1 = dictEnd - match;
			स_हटाओ(oLitEnd, match, length1);
			op = oLitEnd + length1;
			sequence.matchLength -= length1;
			match = base;
			अगर (op > oend_w || sequence.matchLength < MINMATCH) अणु
				U32 i;
				क्रम (i = 0; i < sequence.matchLength; ++i)
					op[i] = match[i];
				वापस sequenceLength;
			पूर्ण
		पूर्ण
	पूर्ण
	/* Requirement: op <= oend_w && sequence.matchLength >= MINMATCH */

	/* match within prefix */
	अगर (sequence.offset < 8) अणु
		/* बंद range match, overlap */
		अटल स्थिर U32 dec32table[] = अणु0, 1, 2, 1, 4, 4, 4, 4पूर्ण;   /* added */
		अटल स्थिर पूर्णांक dec64table[] = अणु8, 8, 8, 7, 8, 9, 10, 11पूर्ण; /* subtracted */
		पूर्णांक स्थिर sub2 = dec64table[sequence.offset];
		op[0] = match[0];
		op[1] = match[1];
		op[2] = match[2];
		op[3] = match[3];
		match += dec32table[sequence.offset];
		ZSTD_copy4(op + 4, match);
		match -= sub2;
	पूर्ण अन्यथा अणु
		ZSTD_copy8(op, match);
	पूर्ण
	op += 8;
	match += 8;

	अगर (oMatchEnd > oend - (16 - MINMATCH)) अणु
		अगर (op < oend_w) अणु
			ZSTD_wildcopy(op, match, oend_w - op);
			match += oend_w - op;
			op = oend_w;
		पूर्ण
		जबतक (op < oMatchEnd)
			*op++ = *match++;
	पूर्ण अन्यथा अणु
		ZSTD_wildcopy(op, match, (सूचक_भेद_प्रकार)sequence.matchLength - 8); /* works even अगर matchLength < 8 */
	पूर्ण
	वापस sequenceLength;
पूर्ण

अटल माप_प्रकार ZSTD_decompressSequences(ZSTD_DCtx *dctx, व्योम *dst, माप_प्रकार maxDstSize, स्थिर व्योम *seqStart, माप_प्रकार seqSize)
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *)seqStart;
	स्थिर BYTE *स्थिर iend = ip + seqSize;
	BYTE *स्थिर ostart = (BYTE * स्थिर)dst;
	BYTE *स्थिर oend = ostart + maxDstSize;
	BYTE *op = ostart;
	स्थिर BYTE *litPtr = dctx->litPtr;
	स्थिर BYTE *स्थिर litEnd = litPtr + dctx->litSize;
	स्थिर BYTE *स्थिर base = (स्थिर BYTE *)(dctx->base);
	स्थिर BYTE *स्थिर vBase = (स्थिर BYTE *)(dctx->vBase);
	स्थिर BYTE *स्थिर dictEnd = (स्थिर BYTE *)(dctx->dictEnd);
	पूर्णांक nbSeq;

	/* Build Decoding Tables */
	अणु
		माप_प्रकार स्थिर seqHSize = ZSTD_decodeSeqHeaders(dctx, &nbSeq, ip, seqSize);
		अगर (ZSTD_isError(seqHSize))
			वापस seqHSize;
		ip += seqHSize;
	पूर्ण

	/* Regen sequences */
	अगर (nbSeq) अणु
		seqState_t seqState;
		dctx->fseEntropy = 1;
		अणु
			U32 i;
			क्रम (i = 0; i < ZSTD_REP_NUM; i++)
				seqState.prevOffset[i] = dctx->entropy.rep[i];
		पूर्ण
		CHECK_E(BIT_initDStream(&seqState.DStream, ip, iend - ip), corruption_detected);
		FSE_initDState(&seqState.stateLL, &seqState.DStream, dctx->LLTptr);
		FSE_initDState(&seqState.stateOffb, &seqState.DStream, dctx->OFTptr);
		FSE_initDState(&seqState.stateML, &seqState.DStream, dctx->MLTptr);

		क्रम (; (BIT_reloadDStream(&(seqState.DStream)) <= BIT_DStream_completed) && nbSeq;) अणु
			nbSeq--;
			अणु
				seq_t स्थिर sequence = ZSTD_decodeSequence(&seqState);
				माप_प्रकार स्थिर oneSeqSize = ZSTD_execSequence(op, oend, sequence, &litPtr, litEnd, base, vBase, dictEnd);
				अगर (ZSTD_isError(oneSeqSize))
					वापस oneSeqSize;
				op += oneSeqSize;
			पूर्ण
		पूर्ण

		/* check अगर reached exact end */
		अगर (nbSeq)
			वापस ERROR(corruption_detected);
		/* save reps क्रम next block */
		अणु
			U32 i;
			क्रम (i = 0; i < ZSTD_REP_NUM; i++)
				dctx->entropy.rep[i] = (U32)(seqState.prevOffset[i]);
		पूर्ण
	पूर्ण

	/* last literal segment */
	अणु
		माप_प्रकार स्थिर lastLLSize = litEnd - litPtr;
		अगर (lastLLSize > (माप_प्रकार)(oend - op))
			वापस ERROR(dstSize_tooSmall);
		स_नकल(op, litPtr, lastLLSize);
		op += lastLLSize;
	पूर्ण

	वापस op - ostart;
पूर्ण

FORCE_INLINE seq_t ZSTD_decodeSequenceLong_generic(seqState_t *seqState, पूर्णांक स्थिर दीर्घOffsets)
अणु
	seq_t seq;

	U32 स्थिर llCode = FSE_peekSymbol(&seqState->stateLL);
	U32 स्थिर mlCode = FSE_peekSymbol(&seqState->stateML);
	U32 स्थिर ofCode = FSE_peekSymbol(&seqState->stateOffb); /* <= maxOff, by table स्थिरruction */

	U32 स्थिर llBits = LL_bits[llCode];
	U32 स्थिर mlBits = ML_bits[mlCode];
	U32 स्थिर ofBits = ofCode;
	U32 स्थिर totalBits = llBits + mlBits + ofBits;

	अटल स्थिर U32 LL_base[MaxLL + 1] = अणु0,  1,  2,  3,  4,  5,  6,  7,  8,    9,     10,    11,    12,    13,     14,     15,     16,     18,
					       20, 22, 24, 28, 32, 40, 48, 64, 0x80, 0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000, 0x10000पूर्ण;

	अटल स्थिर U32 ML_base[MaxML + 1] = अणु3,  4,  5,  6,  7,  8,  9,  10,   11,    12,    13,    14,    15,     16,     17,     18,     19,     20,
					       21, 22, 23, 24, 25, 26, 27, 28,   29,    30,    31,    32,    33,     34,     35,     37,     39,     41,
					       43, 47, 51, 59, 67, 83, 99, 0x83, 0x103, 0x203, 0x403, 0x803, 0x1003, 0x2003, 0x4003, 0x8003, 0x10003पूर्ण;

	अटल स्थिर U32 OF_base[MaxOff + 1] = अणु0,       1,	1,	5,	0xD,      0x1D,      0x3D,      0x7D,      0xFD,     0x1FD,
						0x3FD,   0x7FD,    0xFFD,    0x1FFD,   0x3FFD,   0x7FFD,    0xFFFD,    0x1FFFD,   0x3FFFD,  0x7FFFD,
						0xFFFFD, 0x1FFFFD, 0x3FFFFD, 0x7FFFFD, 0xFFFFFD, 0x1FFFFFD, 0x3FFFFFD, 0x7FFFFFD, 0xFFFFFFDपूर्ण;

	/* sequence */
	अणु
		माप_प्रकार offset;
		अगर (!ofCode)
			offset = 0;
		अन्यथा अणु
			अगर (दीर्घOffsets) अणु
				पूर्णांक स्थिर extraBits = ofBits - MIN(ofBits, STREAM_ACCUMULATOR_MIN);
				offset = OF_base[ofCode] + (BIT_पढ़ोBitsFast(&seqState->DStream, ofBits - extraBits) << extraBits);
				अगर (ZSTD_32bits() || extraBits)
					BIT_reloadDStream(&seqState->DStream);
				अगर (extraBits)
					offset += BIT_पढ़ोBitsFast(&seqState->DStream, extraBits);
			पूर्ण अन्यथा अणु
				offset = OF_base[ofCode] + BIT_पढ़ोBitsFast(&seqState->DStream, ofBits); /* <=  (ZSTD_WINDOWLOG_MAX-1) bits */
				अगर (ZSTD_32bits())
					BIT_reloadDStream(&seqState->DStream);
			पूर्ण
		पूर्ण

		अगर (ofCode <= 1) अणु
			offset += (llCode == 0);
			अगर (offset) अणु
				माप_प्रकार temp = (offset == 3) ? seqState->prevOffset[0] - 1 : seqState->prevOffset[offset];
				temp += !temp; /* 0 is not valid; input is corrupted; क्रमce offset to 1 */
				अगर (offset != 1)
					seqState->prevOffset[2] = seqState->prevOffset[1];
				seqState->prevOffset[1] = seqState->prevOffset[0];
				seqState->prevOffset[0] = offset = temp;
			पूर्ण अन्यथा अणु
				offset = seqState->prevOffset[0];
			पूर्ण
		पूर्ण अन्यथा अणु
			seqState->prevOffset[2] = seqState->prevOffset[1];
			seqState->prevOffset[1] = seqState->prevOffset[0];
			seqState->prevOffset[0] = offset;
		पूर्ण
		seq.offset = offset;
	पूर्ण

	seq.matchLength = ML_base[mlCode] + ((mlCode > 31) ? BIT_पढ़ोBitsFast(&seqState->DStream, mlBits) : 0); /* <=  16 bits */
	अगर (ZSTD_32bits() && (mlBits + llBits > 24))
		BIT_reloadDStream(&seqState->DStream);

	seq.litLength = LL_base[llCode] + ((llCode > 15) ? BIT_पढ़ोBitsFast(&seqState->DStream, llBits) : 0); /* <=  16 bits */
	अगर (ZSTD_32bits() || (totalBits > 64 - 7 - (LLFSELog + MLFSELog + OffFSELog)))
		BIT_reloadDStream(&seqState->DStream);

	अणु
		माप_प्रकार स्थिर pos = seqState->pos + seq.litLength;
		seq.match = seqState->base + pos - seq.offset; /* single memory segment */
		अगर (seq.offset > pos)
			seq.match += seqState->जाओDict; /* separate memory segment */
		seqState->pos = pos + seq.matchLength;
	पूर्ण

	/* ANS state update */
	FSE_updateState(&seqState->stateLL, &seqState->DStream); /* <=  9 bits */
	FSE_updateState(&seqState->stateML, &seqState->DStream); /* <=  9 bits */
	अगर (ZSTD_32bits())
		BIT_reloadDStream(&seqState->DStream);		   /* <= 18 bits */
	FSE_updateState(&seqState->stateOffb, &seqState->DStream); /* <=  8 bits */

	वापस seq;
पूर्ण

अटल seq_t ZSTD_decodeSequenceLong(seqState_t *seqState, अचिन्हित स्थिर winकरोwSize)
अणु
	अगर (ZSTD_highbit32(winकरोwSize) > STREAM_ACCUMULATOR_MIN) अणु
		वापस ZSTD_decodeSequenceLong_generic(seqState, 1);
	पूर्ण अन्यथा अणु
		वापस ZSTD_decodeSequenceLong_generic(seqState, 0);
	पूर्ण
पूर्ण

FORCE_INLINE
माप_प्रकार ZSTD_execSequenceLong(BYTE *op, BYTE *स्थिर oend, seq_t sequence, स्थिर BYTE **litPtr, स्थिर BYTE *स्थिर litLimit, स्थिर BYTE *स्थिर base,
			     स्थिर BYTE *स्थिर vBase, स्थिर BYTE *स्थिर dictEnd)
अणु
	BYTE *स्थिर oLitEnd = op + sequence.litLength;
	माप_प्रकार स्थिर sequenceLength = sequence.litLength + sequence.matchLength;
	BYTE *स्थिर oMatchEnd = op + sequenceLength; /* risk : address space overflow (32-bits) */
	BYTE *स्थिर oend_w = oend - WILDCOPY_OVERLENGTH;
	स्थिर BYTE *स्थिर iLitEnd = *litPtr + sequence.litLength;
	स्थिर BYTE *match = sequence.match;

	/* check */
	अगर (oMatchEnd > oend)
		वापस ERROR(dstSize_tooSmall); /* last match must start at a minimum distance of WILDCOPY_OVERLENGTH from oend */
	अगर (iLitEnd > litLimit)
		वापस ERROR(corruption_detected); /* over-पढ़ो beyond lit buffer */
	अगर (oLitEnd > oend_w)
		वापस ZSTD_execSequenceLast7(op, oend, sequence, litPtr, litLimit, base, vBase, dictEnd);

	/* copy Literals */
	ZSTD_copy8(op, *litPtr);
	अगर (sequence.litLength > 8)
		ZSTD_wildcopy(op + 8, (*litPtr) + 8,
			      sequence.litLength - 8); /* note : since oLitEnd <= oend-WILDCOPY_OVERLENGTH, no risk of overग_लिखो beyond oend */
	op = oLitEnd;
	*litPtr = iLitEnd; /* update क्रम next sequence */

	/* copy Match */
	अगर (sequence.offset > (माप_प्रकार)(oLitEnd - base)) अणु
		/* offset beyond prefix */
		अगर (sequence.offset > (माप_प्रकार)(oLitEnd - vBase))
			वापस ERROR(corruption_detected);
		अगर (match + sequence.matchLength <= dictEnd) अणु
			स_हटाओ(oLitEnd, match, sequence.matchLength);
			वापस sequenceLength;
		पूर्ण
		/* span extDict & currPrefixSegment */
		अणु
			माप_प्रकार स्थिर length1 = dictEnd - match;
			स_हटाओ(oLitEnd, match, length1);
			op = oLitEnd + length1;
			sequence.matchLength -= length1;
			match = base;
			अगर (op > oend_w || sequence.matchLength < MINMATCH) अणु
				U32 i;
				क्रम (i = 0; i < sequence.matchLength; ++i)
					op[i] = match[i];
				वापस sequenceLength;
			पूर्ण
		पूर्ण
	पूर्ण
	/* Requirement: op <= oend_w && sequence.matchLength >= MINMATCH */

	/* match within prefix */
	अगर (sequence.offset < 8) अणु
		/* बंद range match, overlap */
		अटल स्थिर U32 dec32table[] = अणु0, 1, 2, 1, 4, 4, 4, 4पूर्ण;   /* added */
		अटल स्थिर पूर्णांक dec64table[] = अणु8, 8, 8, 7, 8, 9, 10, 11पूर्ण; /* subtracted */
		पूर्णांक स्थिर sub2 = dec64table[sequence.offset];
		op[0] = match[0];
		op[1] = match[1];
		op[2] = match[2];
		op[3] = match[3];
		match += dec32table[sequence.offset];
		ZSTD_copy4(op + 4, match);
		match -= sub2;
	पूर्ण अन्यथा अणु
		ZSTD_copy8(op, match);
	पूर्ण
	op += 8;
	match += 8;

	अगर (oMatchEnd > oend - (16 - MINMATCH)) अणु
		अगर (op < oend_w) अणु
			ZSTD_wildcopy(op, match, oend_w - op);
			match += oend_w - op;
			op = oend_w;
		पूर्ण
		जबतक (op < oMatchEnd)
			*op++ = *match++;
	पूर्ण अन्यथा अणु
		ZSTD_wildcopy(op, match, (सूचक_भेद_प्रकार)sequence.matchLength - 8); /* works even अगर matchLength < 8 */
	पूर्ण
	वापस sequenceLength;
पूर्ण

अटल माप_प्रकार ZSTD_decompressSequencesLong(ZSTD_DCtx *dctx, व्योम *dst, माप_प्रकार maxDstSize, स्थिर व्योम *seqStart, माप_प्रकार seqSize)
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *)seqStart;
	स्थिर BYTE *स्थिर iend = ip + seqSize;
	BYTE *स्थिर ostart = (BYTE * स्थिर)dst;
	BYTE *स्थिर oend = ostart + maxDstSize;
	BYTE *op = ostart;
	स्थिर BYTE *litPtr = dctx->litPtr;
	स्थिर BYTE *स्थिर litEnd = litPtr + dctx->litSize;
	स्थिर BYTE *स्थिर base = (स्थिर BYTE *)(dctx->base);
	स्थिर BYTE *स्थिर vBase = (स्थिर BYTE *)(dctx->vBase);
	स्थिर BYTE *स्थिर dictEnd = (स्थिर BYTE *)(dctx->dictEnd);
	अचिन्हित स्थिर winकरोwSize = dctx->fParams.winकरोwSize;
	पूर्णांक nbSeq;

	/* Build Decoding Tables */
	अणु
		माप_प्रकार स्थिर seqHSize = ZSTD_decodeSeqHeaders(dctx, &nbSeq, ip, seqSize);
		अगर (ZSTD_isError(seqHSize))
			वापस seqHSize;
		ip += seqHSize;
	पूर्ण

	/* Regen sequences */
	अगर (nbSeq) अणु
#घोषणा STORED_SEQS 4
#घोषणा STOSEQ_MASK (STORED_SEQS - 1)
#घोषणा ADVANCED_SEQS 4
		seq_t *sequences = (seq_t *)dctx->entropy.workspace;
		पूर्णांक स्थिर seqAdvance = MIN(nbSeq, ADVANCED_SEQS);
		seqState_t seqState;
		पूर्णांक seqNb;
		ZSTD_STATIC_ASSERT(माप(dctx->entropy.workspace) >= माप(seq_t) * STORED_SEQS);
		dctx->fseEntropy = 1;
		अणु
			U32 i;
			क्रम (i = 0; i < ZSTD_REP_NUM; i++)
				seqState.prevOffset[i] = dctx->entropy.rep[i];
		पूर्ण
		seqState.base = base;
		seqState.pos = (माप_प्रकार)(op - base);
		seqState.जाओDict = (uPtrDअगरf)dictEnd - (uPtrDअगरf)base; /* cast to aव्योम undefined behaviour */
		CHECK_E(BIT_initDStream(&seqState.DStream, ip, iend - ip), corruption_detected);
		FSE_initDState(&seqState.stateLL, &seqState.DStream, dctx->LLTptr);
		FSE_initDState(&seqState.stateOffb, &seqState.DStream, dctx->OFTptr);
		FSE_initDState(&seqState.stateML, &seqState.DStream, dctx->MLTptr);

		/* prepare in advance */
		क्रम (seqNb = 0; (BIT_reloadDStream(&seqState.DStream) <= BIT_DStream_completed) && seqNb < seqAdvance; seqNb++) अणु
			sequences[seqNb] = ZSTD_decodeSequenceLong(&seqState, winकरोwSize);
		पूर्ण
		अगर (seqNb < seqAdvance)
			वापस ERROR(corruption_detected);

		/* decode and decompress */
		क्रम (; (BIT_reloadDStream(&(seqState.DStream)) <= BIT_DStream_completed) && seqNb < nbSeq; seqNb++) अणु
			seq_t स्थिर sequence = ZSTD_decodeSequenceLong(&seqState, winकरोwSize);
			माप_प्रकार स्थिर oneSeqSize =
			    ZSTD_execSequenceLong(op, oend, sequences[(seqNb - ADVANCED_SEQS) & STOSEQ_MASK], &litPtr, litEnd, base, vBase, dictEnd);
			अगर (ZSTD_isError(oneSeqSize))
				वापस oneSeqSize;
			ZSTD_PREFETCH(sequence.match);
			sequences[seqNb & STOSEQ_MASK] = sequence;
			op += oneSeqSize;
		पूर्ण
		अगर (seqNb < nbSeq)
			वापस ERROR(corruption_detected);

		/* finish queue */
		seqNb -= seqAdvance;
		क्रम (; seqNb < nbSeq; seqNb++) अणु
			माप_प्रकार स्थिर oneSeqSize = ZSTD_execSequenceLong(op, oend, sequences[seqNb & STOSEQ_MASK], &litPtr, litEnd, base, vBase, dictEnd);
			अगर (ZSTD_isError(oneSeqSize))
				वापस oneSeqSize;
			op += oneSeqSize;
		पूर्ण

		/* save reps क्रम next block */
		अणु
			U32 i;
			क्रम (i = 0; i < ZSTD_REP_NUM; i++)
				dctx->entropy.rep[i] = (U32)(seqState.prevOffset[i]);
		पूर्ण
	पूर्ण

	/* last literal segment */
	अणु
		माप_प्रकार स्थिर lastLLSize = litEnd - litPtr;
		अगर (lastLLSize > (माप_प्रकार)(oend - op))
			वापस ERROR(dstSize_tooSmall);
		स_नकल(op, litPtr, lastLLSize);
		op += lastLLSize;
	पूर्ण

	वापस op - ostart;
पूर्ण

अटल माप_प्रकार ZSTD_decompressBlock_पूर्णांकernal(ZSTD_DCtx *dctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु /* blockType == blockCompressed */
	स्थिर BYTE *ip = (स्थिर BYTE *)src;

	अगर (srcSize >= ZSTD_BLOCKSIZE_ABSOLUTEMAX)
		वापस ERROR(srcSize_wrong);

	/* Decode literals section */
	अणु
		माप_प्रकार स्थिर litCSize = ZSTD_decodeLiteralsBlock(dctx, src, srcSize);
		अगर (ZSTD_isError(litCSize))
			वापस litCSize;
		ip += litCSize;
		srcSize -= litCSize;
	पूर्ण
	अगर (माप(माप_प्रकार) > 4) /* करो not enable prefetching on 32-bits x86, as it's perक्रमmance detrimental */
				/* likely because of रेजिस्टर pressure */
				/* अगर that's the correct cause, then 32-bits ARM should be affected dअगरferently */
				/* it would be good to test this on ARM real hardware, to see अगर prefetch version improves speed */
		अगर (dctx->fParams.winकरोwSize > (1 << 23))
			वापस ZSTD_decompressSequencesLong(dctx, dst, dstCapacity, ip, srcSize);
	वापस ZSTD_decompressSequences(dctx, dst, dstCapacity, ip, srcSize);
पूर्ण

अटल व्योम ZSTD_checkContinuity(ZSTD_DCtx *dctx, स्थिर व्योम *dst)
अणु
	अगर (dst != dctx->previousDstEnd) अणु /* not contiguous */
		dctx->dictEnd = dctx->previousDstEnd;
		dctx->vBase = (स्थिर अक्षर *)dst - ((स्थिर अक्षर *)(dctx->previousDstEnd) - (स्थिर अक्षर *)(dctx->base));
		dctx->base = dst;
		dctx->previousDstEnd = dst;
	पूर्ण
पूर्ण

माप_प्रकार ZSTD_decompressBlock(ZSTD_DCtx *dctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	माप_प्रकार dSize;
	ZSTD_checkContinuity(dctx, dst);
	dSize = ZSTD_decompressBlock_पूर्णांकernal(dctx, dst, dstCapacity, src, srcSize);
	dctx->previousDstEnd = (अक्षर *)dst + dSize;
	वापस dSize;
पूर्ण

/** ZSTD_insertBlock() :
	insert `src` block पूर्णांकo `dctx` history. Useful to track uncompressed blocks. */
माप_प्रकार ZSTD_insertBlock(ZSTD_DCtx *dctx, स्थिर व्योम *blockStart, माप_प्रकार blockSize)
अणु
	ZSTD_checkContinuity(dctx, blockStart);
	dctx->previousDstEnd = (स्थिर अक्षर *)blockStart + blockSize;
	वापस blockSize;
पूर्ण

माप_प्रकार ZSTD_generateNxBytes(व्योम *dst, माप_प्रकार dstCapacity, BYTE byte, माप_प्रकार length)
अणु
	अगर (length > dstCapacity)
		वापस ERROR(dstSize_tooSmall);
	स_रखो(dst, byte, length);
	वापस length;
पूर्ण

/** ZSTD_findFrameCompressedSize() :
 *  compatible with legacy mode
 *  `src` must poपूर्णांक to the start of a ZSTD frame, ZSTD legacy frame, or skippable frame
 *  `srcSize` must be at least as large as the frame contained
 *  @वापस : the compressed size of the frame starting at `src` */
माप_प्रकार ZSTD_findFrameCompressedSize(स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	अगर (srcSize >= ZSTD_skippableHeaderSize && (ZSTD_पढ़ोLE32(src) & 0xFFFFFFF0U) == ZSTD_MAGIC_SKIPPABLE_START) अणु
		वापस ZSTD_skippableHeaderSize + ZSTD_पढ़ोLE32((स्थिर BYTE *)src + 4);
	पूर्ण अन्यथा अणु
		स्थिर BYTE *ip = (स्थिर BYTE *)src;
		स्थिर BYTE *स्थिर ipstart = ip;
		माप_प्रकार reमुख्यingSize = srcSize;
		ZSTD_frameParams fParams;

		माप_प्रकार स्थिर headerSize = ZSTD_frameHeaderSize(ip, reमुख्यingSize);
		अगर (ZSTD_isError(headerSize))
			वापस headerSize;

		/* Frame Header */
		अणु
			माप_प्रकार स्थिर ret = ZSTD_getFrameParams(&fParams, ip, reमुख्यingSize);
			अगर (ZSTD_isError(ret))
				वापस ret;
			अगर (ret > 0)
				वापस ERROR(srcSize_wrong);
		पूर्ण

		ip += headerSize;
		reमुख्यingSize -= headerSize;

		/* Loop on each block */
		जबतक (1) अणु
			blockProperties_t blockProperties;
			माप_प्रकार स्थिर cBlockSize = ZSTD_अ_लोBlockSize(ip, reमुख्यingSize, &blockProperties);
			अगर (ZSTD_isError(cBlockSize))
				वापस cBlockSize;

			अगर (ZSTD_blockHeaderSize + cBlockSize > reमुख्यingSize)
				वापस ERROR(srcSize_wrong);

			ip += ZSTD_blockHeaderSize + cBlockSize;
			reमुख्यingSize -= ZSTD_blockHeaderSize + cBlockSize;

			अगर (blockProperties.lastBlock)
				अवरोध;
		पूर्ण

		अगर (fParams.checksumFlag) अणु /* Frame content checksum */
			अगर (reमुख्यingSize < 4)
				वापस ERROR(srcSize_wrong);
			ip += 4;
			reमुख्यingSize -= 4;
		पूर्ण

		वापस ip - ipstart;
	पूर्ण
पूर्ण

/*! ZSTD_decompressFrame() :
*   @dctx must be properly initialized */
अटल माप_प्रकार ZSTD_decompressFrame(ZSTD_DCtx *dctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम **srcPtr, माप_प्रकार *srcSizePtr)
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *)(*srcPtr);
	BYTE *स्थिर ostart = (BYTE * स्थिर)dst;
	BYTE *स्थिर oend = ostart + dstCapacity;
	BYTE *op = ostart;
	माप_प्रकार reमुख्यingSize = *srcSizePtr;

	/* check */
	अगर (reमुख्यingSize < ZSTD_frameHeaderSize_min + ZSTD_blockHeaderSize)
		वापस ERROR(srcSize_wrong);

	/* Frame Header */
	अणु
		माप_प्रकार स्थिर frameHeaderSize = ZSTD_frameHeaderSize(ip, ZSTD_frameHeaderSize_prefix);
		अगर (ZSTD_isError(frameHeaderSize))
			वापस frameHeaderSize;
		अगर (reमुख्यingSize < frameHeaderSize + ZSTD_blockHeaderSize)
			वापस ERROR(srcSize_wrong);
		CHECK_F(ZSTD_decodeFrameHeader(dctx, ip, frameHeaderSize));
		ip += frameHeaderSize;
		reमुख्यingSize -= frameHeaderSize;
	पूर्ण

	/* Loop on each block */
	जबतक (1) अणु
		माप_प्रकार decodedSize;
		blockProperties_t blockProperties;
		माप_प्रकार स्थिर cBlockSize = ZSTD_अ_लोBlockSize(ip, reमुख्यingSize, &blockProperties);
		अगर (ZSTD_isError(cBlockSize))
			वापस cBlockSize;

		ip += ZSTD_blockHeaderSize;
		reमुख्यingSize -= ZSTD_blockHeaderSize;
		अगर (cBlockSize > reमुख्यingSize)
			वापस ERROR(srcSize_wrong);

		चयन (blockProperties.blockType) अणु
		हाल bt_compressed: decodedSize = ZSTD_decompressBlock_पूर्णांकernal(dctx, op, oend - op, ip, cBlockSize); अवरोध;
		हाल bt_raw: decodedSize = ZSTD_copyRawBlock(op, oend - op, ip, cBlockSize); अवरोध;
		हाल bt_rle: decodedSize = ZSTD_generateNxBytes(op, oend - op, *ip, blockProperties.origSize); अवरोध;
		हाल bt_reserved:
		शेष: वापस ERROR(corruption_detected);
		पूर्ण

		अगर (ZSTD_isError(decodedSize))
			वापस decodedSize;
		अगर (dctx->fParams.checksumFlag)
			xxh64_update(&dctx->xxhState, op, decodedSize);
		op += decodedSize;
		ip += cBlockSize;
		reमुख्यingSize -= cBlockSize;
		अगर (blockProperties.lastBlock)
			अवरोध;
	पूर्ण

	अगर (dctx->fParams.checksumFlag) अणु /* Frame content checksum verअगरication */
		U32 स्थिर checkCalc = (U32)xxh64_digest(&dctx->xxhState);
		U32 checkRead;
		अगर (reमुख्यingSize < 4)
			वापस ERROR(checksum_wrong);
		checkRead = ZSTD_पढ़ोLE32(ip);
		अगर (checkRead != checkCalc)
			वापस ERROR(checksum_wrong);
		ip += 4;
		reमुख्यingSize -= 4;
	पूर्ण

	/* Allow caller to get size पढ़ो */
	*srcPtr = ip;
	*srcSizePtr = reमुख्यingSize;
	वापस op - ostart;
पूर्ण

अटल स्थिर व्योम *ZSTD_DDictDictContent(स्थिर ZSTD_DDict *ddict);
अटल माप_प्रकार ZSTD_DDictDictSize(स्थिर ZSTD_DDict *ddict);

अटल माप_प्रकार ZSTD_decompressMultiFrame(ZSTD_DCtx *dctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर व्योम *dict, माप_प्रकार dictSize,
					स्थिर ZSTD_DDict *ddict)
अणु
	व्योम *स्थिर dststart = dst;

	अगर (ddict) अणु
		अगर (dict) अणु
			/* programmer error, these two हालs should be mutually exclusive */
			वापस ERROR(GENERIC);
		पूर्ण

		dict = ZSTD_DDictDictContent(ddict);
		dictSize = ZSTD_DDictDictSize(ddict);
	पूर्ण

	जबतक (srcSize >= ZSTD_frameHeaderSize_prefix) अणु
		U32 magicNumber;

		magicNumber = ZSTD_पढ़ोLE32(src);
		अगर (magicNumber != ZSTD_MAGICNUMBER) अणु
			अगर ((magicNumber & 0xFFFFFFF0U) == ZSTD_MAGIC_SKIPPABLE_START) अणु
				माप_प्रकार skippableSize;
				अगर (srcSize < ZSTD_skippableHeaderSize)
					वापस ERROR(srcSize_wrong);
				skippableSize = ZSTD_पढ़ोLE32((स्थिर BYTE *)src + 4) + ZSTD_skippableHeaderSize;
				अगर (srcSize < skippableSize) अणु
					वापस ERROR(srcSize_wrong);
				पूर्ण

				src = (स्थिर BYTE *)src + skippableSize;
				srcSize -= skippableSize;
				जारी;
			पूर्ण अन्यथा अणु
				वापस ERROR(prefix_unknown);
			पूर्ण
		पूर्ण

		अगर (ddict) अणु
			/* we were called from ZSTD_decompress_usingDDict */
			ZSTD_refDDict(dctx, ddict);
		पूर्ण अन्यथा अणु
			/* this will initialize correctly with no dict अगर dict == शून्य, so
			 * use this in all हालs but ddict */
			CHECK_F(ZSTD_decompressBegin_usingDict(dctx, dict, dictSize));
		पूर्ण
		ZSTD_checkContinuity(dctx, dst);

		अणु
			स्थिर माप_प्रकार res = ZSTD_decompressFrame(dctx, dst, dstCapacity, &src, &srcSize);
			अगर (ZSTD_isError(res))
				वापस res;
			/* करोn't need to bounds check this, ZSTD_decompressFrame will have
			 * alपढ़ोy */
			dst = (BYTE *)dst + res;
			dstCapacity -= res;
		पूर्ण
	पूर्ण

	अगर (srcSize)
		वापस ERROR(srcSize_wrong); /* input not entirely consumed */

	वापस (BYTE *)dst - (BYTE *)dststart;
पूर्ण

माप_प्रकार ZSTD_decompress_usingDict(ZSTD_DCtx *dctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर व्योम *dict, माप_प्रकार dictSize)
अणु
	वापस ZSTD_decompressMultiFrame(dctx, dst, dstCapacity, src, srcSize, dict, dictSize, शून्य);
पूर्ण

माप_प्रकार ZSTD_decompressDCtx(ZSTD_DCtx *dctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	वापस ZSTD_decompress_usingDict(dctx, dst, dstCapacity, src, srcSize, शून्य, 0);
पूर्ण

/*-**************************************
*   Advanced Streaming Decompression API
*   Bufferless and synchronous
****************************************/
माप_प्रकार ZSTD_nextSrcSizeToDecompress(ZSTD_DCtx *dctx) अणु वापस dctx->expected; पूर्ण

ZSTD_nextInputType_e ZSTD_nextInputType(ZSTD_DCtx *dctx)
अणु
	चयन (dctx->stage) अणु
	शेष: /* should not happen */
	हाल ZSTDds_getFrameHeaderSize:
	हाल ZSTDds_decodeFrameHeader: वापस ZSTDnit_frameHeader;
	हाल ZSTDds_decodeBlockHeader: वापस ZSTDnit_blockHeader;
	हाल ZSTDds_decompressBlock: वापस ZSTDnit_block;
	हाल ZSTDds_decompressLastBlock: वापस ZSTDnit_lastBlock;
	हाल ZSTDds_checkChecksum: वापस ZSTDnit_checksum;
	हाल ZSTDds_decodeSkippableHeader:
	हाल ZSTDds_skipFrame: वापस ZSTDnit_skippableFrame;
	पूर्ण
पूर्ण

पूर्णांक ZSTD_isSkipFrame(ZSTD_DCtx *dctx) अणु वापस dctx->stage == ZSTDds_skipFrame; पूर्ण /* क्रम zbuff */

/** ZSTD_decompressContinue() :
*   @वापस : nb of bytes generated पूर्णांकo `dst` (necessarily <= `dstCapacity)
*             or an error code, which can be tested using ZSTD_isError() */
माप_प्रकार ZSTD_decompressContinue(ZSTD_DCtx *dctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	/* Sanity check */
	अगर (srcSize != dctx->expected)
		वापस ERROR(srcSize_wrong);
	अगर (dstCapacity)
		ZSTD_checkContinuity(dctx, dst);

	चयन (dctx->stage) अणु
	हाल ZSTDds_getFrameHeaderSize:
		अगर (srcSize != ZSTD_frameHeaderSize_prefix)
			वापस ERROR(srcSize_wrong);					/* impossible */
		अगर ((ZSTD_पढ़ोLE32(src) & 0xFFFFFFF0U) == ZSTD_MAGIC_SKIPPABLE_START) अणु /* skippable frame */
			स_नकल(dctx->headerBuffer, src, ZSTD_frameHeaderSize_prefix);
			dctx->expected = ZSTD_skippableHeaderSize - ZSTD_frameHeaderSize_prefix; /* magic number + skippable frame length */
			dctx->stage = ZSTDds_decodeSkippableHeader;
			वापस 0;
		पूर्ण
		dctx->headerSize = ZSTD_frameHeaderSize(src, ZSTD_frameHeaderSize_prefix);
		अगर (ZSTD_isError(dctx->headerSize))
			वापस dctx->headerSize;
		स_नकल(dctx->headerBuffer, src, ZSTD_frameHeaderSize_prefix);
		अगर (dctx->headerSize > ZSTD_frameHeaderSize_prefix) अणु
			dctx->expected = dctx->headerSize - ZSTD_frameHeaderSize_prefix;
			dctx->stage = ZSTDds_decodeFrameHeader;
			वापस 0;
		पूर्ण
		dctx->expected = 0; /* not necessary to copy more */
		fallthrough;

	हाल ZSTDds_decodeFrameHeader:
		स_नकल(dctx->headerBuffer + ZSTD_frameHeaderSize_prefix, src, dctx->expected);
		CHECK_F(ZSTD_decodeFrameHeader(dctx, dctx->headerBuffer, dctx->headerSize));
		dctx->expected = ZSTD_blockHeaderSize;
		dctx->stage = ZSTDds_decodeBlockHeader;
		वापस 0;

	हाल ZSTDds_decodeBlockHeader: अणु
		blockProperties_t bp;
		माप_प्रकार स्थिर cBlockSize = ZSTD_अ_लोBlockSize(src, ZSTD_blockHeaderSize, &bp);
		अगर (ZSTD_isError(cBlockSize))
			वापस cBlockSize;
		dctx->expected = cBlockSize;
		dctx->bType = bp.blockType;
		dctx->rleSize = bp.origSize;
		अगर (cBlockSize) अणु
			dctx->stage = bp.lastBlock ? ZSTDds_decompressLastBlock : ZSTDds_decompressBlock;
			वापस 0;
		पूर्ण
		/* empty block */
		अगर (bp.lastBlock) अणु
			अगर (dctx->fParams.checksumFlag) अणु
				dctx->expected = 4;
				dctx->stage = ZSTDds_checkChecksum;
			पूर्ण अन्यथा अणु
				dctx->expected = 0; /* end of frame */
				dctx->stage = ZSTDds_getFrameHeaderSize;
			पूर्ण
		पूर्ण अन्यथा अणु
			dctx->expected = 3; /* go directly to next header */
			dctx->stage = ZSTDds_decodeBlockHeader;
		पूर्ण
		वापस 0;
	पूर्ण
	हाल ZSTDds_decompressLastBlock:
	हाल ZSTDds_decompressBlock: अणु
		माप_प्रकार rSize;
		चयन (dctx->bType) अणु
		हाल bt_compressed: rSize = ZSTD_decompressBlock_पूर्णांकernal(dctx, dst, dstCapacity, src, srcSize); अवरोध;
		हाल bt_raw: rSize = ZSTD_copyRawBlock(dst, dstCapacity, src, srcSize); अवरोध;
		हाल bt_rle: rSize = ZSTD_setRleBlock(dst, dstCapacity, src, srcSize, dctx->rleSize); अवरोध;
		हाल bt_reserved: /* should never happen */
		शेष: वापस ERROR(corruption_detected);
		पूर्ण
		अगर (ZSTD_isError(rSize))
			वापस rSize;
		अगर (dctx->fParams.checksumFlag)
			xxh64_update(&dctx->xxhState, dst, rSize);

		अगर (dctx->stage == ZSTDds_decompressLastBlock) अणु /* end of frame */
			अगर (dctx->fParams.checksumFlag) अणु	/* another round क्रम frame checksum */
				dctx->expected = 4;
				dctx->stage = ZSTDds_checkChecksum;
			पूर्ण अन्यथा अणु
				dctx->expected = 0; /* ends here */
				dctx->stage = ZSTDds_getFrameHeaderSize;
			पूर्ण
		पूर्ण अन्यथा अणु
			dctx->stage = ZSTDds_decodeBlockHeader;
			dctx->expected = ZSTD_blockHeaderSize;
			dctx->previousDstEnd = (अक्षर *)dst + rSize;
		पूर्ण
		वापस rSize;
	पूर्ण
	हाल ZSTDds_checkChecksum: अणु
		U32 स्थिर h32 = (U32)xxh64_digest(&dctx->xxhState);
		U32 स्थिर check32 = ZSTD_पढ़ोLE32(src); /* srcSize == 4, guaranteed by dctx->expected */
		अगर (check32 != h32)
			वापस ERROR(checksum_wrong);
		dctx->expected = 0;
		dctx->stage = ZSTDds_getFrameHeaderSize;
		वापस 0;
	पूर्ण
	हाल ZSTDds_decodeSkippableHeader: अणु
		स_नकल(dctx->headerBuffer + ZSTD_frameHeaderSize_prefix, src, dctx->expected);
		dctx->expected = ZSTD_पढ़ोLE32(dctx->headerBuffer + 4);
		dctx->stage = ZSTDds_skipFrame;
		वापस 0;
	पूर्ण
	हाल ZSTDds_skipFrame: अणु
		dctx->expected = 0;
		dctx->stage = ZSTDds_getFrameHeaderSize;
		वापस 0;
	पूर्ण
	शेष:
		वापस ERROR(GENERIC); /* impossible */
	पूर्ण
पूर्ण

अटल माप_प्रकार ZSTD_refDictContent(ZSTD_DCtx *dctx, स्थिर व्योम *dict, माप_प्रकार dictSize)
अणु
	dctx->dictEnd = dctx->previousDstEnd;
	dctx->vBase = (स्थिर अक्षर *)dict - ((स्थिर अक्षर *)(dctx->previousDstEnd) - (स्थिर अक्षर *)(dctx->base));
	dctx->base = dict;
	dctx->previousDstEnd = (स्थिर अक्षर *)dict + dictSize;
	वापस 0;
पूर्ण

/* ZSTD_loadEntropy() :
 * dict : must poपूर्णांक at beginning of a valid zstd dictionary
 * @वापस : size of entropy tables पढ़ो */
अटल माप_प्रकार ZSTD_loadEntropy(ZSTD_entropyTables_t *entropy, स्थिर व्योम *स्थिर dict, माप_प्रकार स्थिर dictSize)
अणु
	स्थिर BYTE *dictPtr = (स्थिर BYTE *)dict;
	स्थिर BYTE *स्थिर dictEnd = dictPtr + dictSize;

	अगर (dictSize <= 8)
		वापस ERROR(dictionary_corrupted);
	dictPtr += 8; /* skip header = magic + dictID */

	अणु
		माप_प्रकार स्थिर hSize = HUF_पढ़ोDTableX4_wksp(entropy->hufTable, dictPtr, dictEnd - dictPtr, entropy->workspace, माप(entropy->workspace));
		अगर (HUF_isError(hSize))
			वापस ERROR(dictionary_corrupted);
		dictPtr += hSize;
	पूर्ण

	अणु
		लघु offcodeNCount[MaxOff + 1];
		U32 offcodeMaxValue = MaxOff, offcodeLog;
		माप_प्रकार स्थिर offcodeHeaderSize = FSE_पढ़ोNCount(offcodeNCount, &offcodeMaxValue, &offcodeLog, dictPtr, dictEnd - dictPtr);
		अगर (FSE_isError(offcodeHeaderSize))
			वापस ERROR(dictionary_corrupted);
		अगर (offcodeLog > OffFSELog)
			वापस ERROR(dictionary_corrupted);
		CHECK_E(FSE_buildDTable_wksp(entropy->OFTable, offcodeNCount, offcodeMaxValue, offcodeLog, entropy->workspace, माप(entropy->workspace)), dictionary_corrupted);
		dictPtr += offcodeHeaderSize;
	पूर्ण

	अणु
		लघु matchlengthNCount[MaxML + 1];
		अचिन्हित matchlengthMaxValue = MaxML, matchlengthLog;
		माप_प्रकार स्थिर matchlengthHeaderSize = FSE_पढ़ोNCount(matchlengthNCount, &matchlengthMaxValue, &matchlengthLog, dictPtr, dictEnd - dictPtr);
		अगर (FSE_isError(matchlengthHeaderSize))
			वापस ERROR(dictionary_corrupted);
		अगर (matchlengthLog > MLFSELog)
			वापस ERROR(dictionary_corrupted);
		CHECK_E(FSE_buildDTable_wksp(entropy->MLTable, matchlengthNCount, matchlengthMaxValue, matchlengthLog, entropy->workspace, माप(entropy->workspace)), dictionary_corrupted);
		dictPtr += matchlengthHeaderSize;
	पूर्ण

	अणु
		लघु litlengthNCount[MaxLL + 1];
		अचिन्हित litlengthMaxValue = MaxLL, litlengthLog;
		माप_प्रकार स्थिर litlengthHeaderSize = FSE_पढ़ोNCount(litlengthNCount, &litlengthMaxValue, &litlengthLog, dictPtr, dictEnd - dictPtr);
		अगर (FSE_isError(litlengthHeaderSize))
			वापस ERROR(dictionary_corrupted);
		अगर (litlengthLog > LLFSELog)
			वापस ERROR(dictionary_corrupted);
		CHECK_E(FSE_buildDTable_wksp(entropy->LLTable, litlengthNCount, litlengthMaxValue, litlengthLog, entropy->workspace, माप(entropy->workspace)), dictionary_corrupted);
		dictPtr += litlengthHeaderSize;
	पूर्ण

	अगर (dictPtr + 12 > dictEnd)
		वापस ERROR(dictionary_corrupted);
	अणु
		पूर्णांक i;
		माप_प्रकार स्थिर dictContentSize = (माप_प्रकार)(dictEnd - (dictPtr + 12));
		क्रम (i = 0; i < 3; i++) अणु
			U32 स्थिर rep = ZSTD_पढ़ोLE32(dictPtr);
			dictPtr += 4;
			अगर (rep == 0 || rep >= dictContentSize)
				वापस ERROR(dictionary_corrupted);
			entropy->rep[i] = rep;
		पूर्ण
	पूर्ण

	वापस dictPtr - (स्थिर BYTE *)dict;
पूर्ण

अटल माप_प्रकार ZSTD_decompress_insertDictionary(ZSTD_DCtx *dctx, स्थिर व्योम *dict, माप_प्रकार dictSize)
अणु
	अगर (dictSize < 8)
		वापस ZSTD_refDictContent(dctx, dict, dictSize);
	अणु
		U32 स्थिर magic = ZSTD_पढ़ोLE32(dict);
		अगर (magic != ZSTD_DICT_MAGIC) अणु
			वापस ZSTD_refDictContent(dctx, dict, dictSize); /* pure content mode */
		पूर्ण
	पूर्ण
	dctx->dictID = ZSTD_पढ़ोLE32((स्थिर अक्षर *)dict + 4);

	/* load entropy tables */
	अणु
		माप_प्रकार स्थिर eSize = ZSTD_loadEntropy(&dctx->entropy, dict, dictSize);
		अगर (ZSTD_isError(eSize))
			वापस ERROR(dictionary_corrupted);
		dict = (स्थिर अक्षर *)dict + eSize;
		dictSize -= eSize;
	पूर्ण
	dctx->litEntropy = dctx->fseEntropy = 1;

	/* reference dictionary content */
	वापस ZSTD_refDictContent(dctx, dict, dictSize);
पूर्ण

माप_प्रकार ZSTD_decompressBegin_usingDict(ZSTD_DCtx *dctx, स्थिर व्योम *dict, माप_प्रकार dictSize)
अणु
	CHECK_F(ZSTD_decompressBegin(dctx));
	अगर (dict && dictSize)
		CHECK_E(ZSTD_decompress_insertDictionary(dctx, dict, dictSize), dictionary_corrupted);
	वापस 0;
पूर्ण

/* ======   ZSTD_DDict   ====== */

काष्ठा ZSTD_DDict_s अणु
	व्योम *dictBuffer;
	स्थिर व्योम *dictContent;
	माप_प्रकार dictSize;
	ZSTD_entropyTables_t entropy;
	U32 dictID;
	U32 entropyPresent;
	ZSTD_customMem cMem;
पूर्ण; /* प्रकार'd to ZSTD_DDict within "zstd.h" */

माप_प्रकार ZSTD_DDictWorkspaceBound(व्योम) अणु वापस ZSTD_ALIGN(माप(ZSTD_stack)) + ZSTD_ALIGN(माप(ZSTD_DDict)); पूर्ण

अटल स्थिर व्योम *ZSTD_DDictDictContent(स्थिर ZSTD_DDict *ddict) अणु वापस ddict->dictContent; पूर्ण

अटल माप_प्रकार ZSTD_DDictDictSize(स्थिर ZSTD_DDict *ddict) अणु वापस ddict->dictSize; पूर्ण

अटल व्योम ZSTD_refDDict(ZSTD_DCtx *dstDCtx, स्थिर ZSTD_DDict *ddict)
अणु
	ZSTD_decompressBegin(dstDCtx); /* init */
	अगर (ddict) अणु		       /* support refDDict on शून्य */
		dstDCtx->dictID = ddict->dictID;
		dstDCtx->base = ddict->dictContent;
		dstDCtx->vBase = ddict->dictContent;
		dstDCtx->dictEnd = (स्थिर BYTE *)ddict->dictContent + ddict->dictSize;
		dstDCtx->previousDstEnd = dstDCtx->dictEnd;
		अगर (ddict->entropyPresent) अणु
			dstDCtx->litEntropy = 1;
			dstDCtx->fseEntropy = 1;
			dstDCtx->LLTptr = ddict->entropy.LLTable;
			dstDCtx->MLTptr = ddict->entropy.MLTable;
			dstDCtx->OFTptr = ddict->entropy.OFTable;
			dstDCtx->HUFptr = ddict->entropy.hufTable;
			dstDCtx->entropy.rep[0] = ddict->entropy.rep[0];
			dstDCtx->entropy.rep[1] = ddict->entropy.rep[1];
			dstDCtx->entropy.rep[2] = ddict->entropy.rep[2];
		पूर्ण अन्यथा अणु
			dstDCtx->litEntropy = 0;
			dstDCtx->fseEntropy = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल माप_प्रकार ZSTD_loadEntropy_inDDict(ZSTD_DDict *ddict)
अणु
	ddict->dictID = 0;
	ddict->entropyPresent = 0;
	अगर (ddict->dictSize < 8)
		वापस 0;
	अणु
		U32 स्थिर magic = ZSTD_पढ़ोLE32(ddict->dictContent);
		अगर (magic != ZSTD_DICT_MAGIC)
			वापस 0; /* pure content mode */
	पूर्ण
	ddict->dictID = ZSTD_पढ़ोLE32((स्थिर अक्षर *)ddict->dictContent + 4);

	/* load entropy tables */
	CHECK_E(ZSTD_loadEntropy(&ddict->entropy, ddict->dictContent, ddict->dictSize), dictionary_corrupted);
	ddict->entropyPresent = 1;
	वापस 0;
पूर्ण

अटल ZSTD_DDict *ZSTD_createDDict_advanced(स्थिर व्योम *dict, माप_प्रकार dictSize, अचिन्हित byReference, ZSTD_customMem customMem)
अणु
	अगर (!customMem.customAlloc || !customMem.customFree)
		वापस शून्य;

	अणु
		ZSTD_DDict *स्थिर ddict = (ZSTD_DDict *)ZSTD_दो_स्मृति(माप(ZSTD_DDict), customMem);
		अगर (!ddict)
			वापस शून्य;
		ddict->cMem = customMem;

		अगर ((byReference) || (!dict) || (!dictSize)) अणु
			ddict->dictBuffer = शून्य;
			ddict->dictContent = dict;
		पूर्ण अन्यथा अणु
			व्योम *स्थिर पूर्णांकernalBuffer = ZSTD_दो_स्मृति(dictSize, customMem);
			अगर (!पूर्णांकernalBuffer) अणु
				ZSTD_मुक्तDDict(ddict);
				वापस शून्य;
			पूर्ण
			स_नकल(पूर्णांकernalBuffer, dict, dictSize);
			ddict->dictBuffer = पूर्णांकernalBuffer;
			ddict->dictContent = पूर्णांकernalBuffer;
		पूर्ण
		ddict->dictSize = dictSize;
		ddict->entropy.hufTable[0] = (HUF_DTable)((HufLog)*0x1000001); /* cover both little and big endian */
		/* parse dictionary content */
		अणु
			माप_प्रकार स्थिर errorCode = ZSTD_loadEntropy_inDDict(ddict);
			अगर (ZSTD_isError(errorCode)) अणु
				ZSTD_मुक्तDDict(ddict);
				वापस शून्य;
			पूर्ण
		पूर्ण

		वापस ddict;
	पूर्ण
पूर्ण

/*! ZSTD_initDDict() :
*   Create a digested dictionary, to start decompression without startup delay.
*   `dict` content is copied inside DDict.
*   Consequently, `dict` can be released after `ZSTD_DDict` creation */
ZSTD_DDict *ZSTD_initDDict(स्थिर व्योम *dict, माप_प्रकार dictSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	ZSTD_customMem स्थिर stackMem = ZSTD_initStack(workspace, workspaceSize);
	वापस ZSTD_createDDict_advanced(dict, dictSize, 1, stackMem);
पूर्ण

माप_प्रकार ZSTD_मुक्तDDict(ZSTD_DDict *ddict)
अणु
	अगर (ddict == शून्य)
		वापस 0; /* support मुक्त on शून्य */
	अणु
		ZSTD_customMem स्थिर cMem = ddict->cMem;
		ZSTD_मुक्त(ddict->dictBuffer, cMem);
		ZSTD_मुक्त(ddict, cMem);
		वापस 0;
	पूर्ण
पूर्ण

/*! ZSTD_getDictID_fromDict() :
 *  Provides the dictID stored within dictionary.
 *  अगर @वापस == 0, the dictionary is not conक्रमmant with Zstandard specअगरication.
 *  It can still be loaded, but as a content-only dictionary. */
अचिन्हित ZSTD_getDictID_fromDict(स्थिर व्योम *dict, माप_प्रकार dictSize)
अणु
	अगर (dictSize < 8)
		वापस 0;
	अगर (ZSTD_पढ़ोLE32(dict) != ZSTD_DICT_MAGIC)
		वापस 0;
	वापस ZSTD_पढ़ोLE32((स्थिर अक्षर *)dict + 4);
पूर्ण

/*! ZSTD_getDictID_fromDDict() :
 *  Provides the dictID of the dictionary loaded पूर्णांकo `ddict`.
 *  If @वापस == 0, the dictionary is not conक्रमmant to Zstandard specअगरication, or empty.
 *  Non-conक्रमmant dictionaries can still be loaded, but as content-only dictionaries. */
अचिन्हित ZSTD_getDictID_fromDDict(स्थिर ZSTD_DDict *ddict)
अणु
	अगर (ddict == शून्य)
		वापस 0;
	वापस ZSTD_getDictID_fromDict(ddict->dictContent, ddict->dictSize);
पूर्ण

/*! ZSTD_getDictID_fromFrame() :
 *  Provides the dictID required to decompressed the frame stored within `src`.
 *  If @वापस == 0, the dictID could not be decoded.
 *  This could क्रम one of the following reasons :
 *  - The frame करोes not require a dictionary to be decoded (most common हाल).
 *  - The frame was built with dictID पूर्णांकentionally हटाओd. Whatever dictionary is necessary is a hidden inक्रमmation.
 *    Note : this use हाल also happens when using a non-conक्रमmant dictionary.
 *  - `srcSize` is too small, and as a result, the frame header could not be decoded (only possible अगर `srcSize < ZSTD_FRAMEHEADERSIZE_MAX`).
 *  - This is not a Zstandard frame.
 *  When identअगरying the exact failure cause, it's possible to used ZSTD_getFrameParams(), which will provide a more precise error code. */
अचिन्हित ZSTD_getDictID_fromFrame(स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	ZSTD_frameParams zfp = अणु0, 0, 0, 0पूर्ण;
	माप_प्रकार स्थिर hError = ZSTD_getFrameParams(&zfp, src, srcSize);
	अगर (ZSTD_isError(hError))
		वापस 0;
	वापस zfp.dictID;
पूर्ण

/*! ZSTD_decompress_usingDDict() :
*   Decompression using a pre-digested Dictionary
*   Use dictionary without signअगरicant overhead. */
माप_प्रकार ZSTD_decompress_usingDDict(ZSTD_DCtx *dctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर ZSTD_DDict *ddict)
अणु
	/* pass content and size in हाल legacy frames are encountered */
	वापस ZSTD_decompressMultiFrame(dctx, dst, dstCapacity, src, srcSize, शून्य, 0, ddict);
पूर्ण

/*=====================================
*   Streaming decompression
*====================================*/

प्रकार क्रमागत अणु zdss_init, zdss_loadHeader, zdss_पढ़ो, zdss_load, zdss_flush पूर्ण ZSTD_dStreamStage;

/* *** Resource management *** */
काष्ठा ZSTD_DStream_s अणु
	ZSTD_DCtx *dctx;
	ZSTD_DDict *ddictLocal;
	स्थिर ZSTD_DDict *ddict;
	ZSTD_frameParams fParams;
	ZSTD_dStreamStage stage;
	अक्षर *inBuff;
	माप_प्रकार inBuffSize;
	माप_प्रकार inPos;
	माप_प्रकार maxWinकरोwSize;
	अक्षर *outBuff;
	माप_प्रकार outBuffSize;
	माप_प्रकार outStart;
	माप_प्रकार outEnd;
	माप_प्रकार blockSize;
	BYTE headerBuffer[ZSTD_FRAMEHEADERSIZE_MAX]; /* पंचांगp buffer to store frame header */
	माप_प्रकार lhSize;
	ZSTD_customMem customMem;
	व्योम *legacyContext;
	U32 previousLegacyVersion;
	U32 legacyVersion;
	U32 hostageByte;
पूर्ण; /* प्रकार'd to ZSTD_DStream within "zstd.h" */

माप_प्रकार ZSTD_DStreamWorkspaceBound(माप_प्रकार maxWinकरोwSize)
अणु
	माप_प्रकार स्थिर blockSize = MIN(maxWinकरोwSize, ZSTD_BLOCKSIZE_ABSOLUTEMAX);
	माप_प्रकार स्थिर inBuffSize = blockSize;
	माप_प्रकार स्थिर outBuffSize = maxWinकरोwSize + blockSize + WILDCOPY_OVERLENGTH * 2;
	वापस ZSTD_DCtxWorkspaceBound() + ZSTD_ALIGN(माप(ZSTD_DStream)) + ZSTD_ALIGN(inBuffSize) + ZSTD_ALIGN(outBuffSize);
पूर्ण

अटल ZSTD_DStream *ZSTD_createDStream_advanced(ZSTD_customMem customMem)
अणु
	ZSTD_DStream *zds;

	अगर (!customMem.customAlloc || !customMem.customFree)
		वापस शून्य;

	zds = (ZSTD_DStream *)ZSTD_दो_स्मृति(माप(ZSTD_DStream), customMem);
	अगर (zds == शून्य)
		वापस शून्य;
	स_रखो(zds, 0, माप(ZSTD_DStream));
	स_नकल(&zds->customMem, &customMem, माप(ZSTD_customMem));
	zds->dctx = ZSTD_createDCtx_advanced(customMem);
	अगर (zds->dctx == शून्य) अणु
		ZSTD_मुक्तDStream(zds);
		वापस शून्य;
	पूर्ण
	zds->stage = zdss_init;
	zds->maxWinकरोwSize = ZSTD_MAXWINDOWSIZE_DEFAULT;
	वापस zds;
पूर्ण

ZSTD_DStream *ZSTD_initDStream(माप_प्रकार maxWinकरोwSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	ZSTD_customMem स्थिर stackMem = ZSTD_initStack(workspace, workspaceSize);
	ZSTD_DStream *zds = ZSTD_createDStream_advanced(stackMem);
	अगर (!zds) अणु
		वापस शून्य;
	पूर्ण

	zds->maxWinकरोwSize = maxWinकरोwSize;
	zds->stage = zdss_loadHeader;
	zds->lhSize = zds->inPos = zds->outStart = zds->outEnd = 0;
	ZSTD_मुक्तDDict(zds->ddictLocal);
	zds->ddictLocal = शून्य;
	zds->ddict = zds->ddictLocal;
	zds->legacyVersion = 0;
	zds->hostageByte = 0;

	अणु
		माप_प्रकार स्थिर blockSize = MIN(zds->maxWinकरोwSize, ZSTD_BLOCKSIZE_ABSOLUTEMAX);
		माप_प्रकार स्थिर neededOutSize = zds->maxWinकरोwSize + blockSize + WILDCOPY_OVERLENGTH * 2;

		zds->inBuff = (अक्षर *)ZSTD_दो_स्मृति(blockSize, zds->customMem);
		zds->inBuffSize = blockSize;
		zds->outBuff = (अक्षर *)ZSTD_दो_स्मृति(neededOutSize, zds->customMem);
		zds->outBuffSize = neededOutSize;
		अगर (zds->inBuff == शून्य || zds->outBuff == शून्य) अणु
			ZSTD_मुक्तDStream(zds);
			वापस शून्य;
		पूर्ण
	पूर्ण
	वापस zds;
पूर्ण

ZSTD_DStream *ZSTD_initDStream_usingDDict(माप_प्रकार maxWinकरोwSize, स्थिर ZSTD_DDict *ddict, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	ZSTD_DStream *zds = ZSTD_initDStream(maxWinकरोwSize, workspace, workspaceSize);
	अगर (zds) अणु
		zds->ddict = ddict;
	पूर्ण
	वापस zds;
पूर्ण

माप_प्रकार ZSTD_मुक्तDStream(ZSTD_DStream *zds)
अणु
	अगर (zds == शून्य)
		वापस 0; /* support मुक्त on null */
	अणु
		ZSTD_customMem स्थिर cMem = zds->customMem;
		ZSTD_मुक्तDCtx(zds->dctx);
		zds->dctx = शून्य;
		ZSTD_मुक्तDDict(zds->ddictLocal);
		zds->ddictLocal = शून्य;
		ZSTD_मुक्त(zds->inBuff, cMem);
		zds->inBuff = शून्य;
		ZSTD_मुक्त(zds->outBuff, cMem);
		zds->outBuff = शून्य;
		ZSTD_मुक्त(zds, cMem);
		वापस 0;
	पूर्ण
पूर्ण

/* *** Initialization *** */

माप_प्रकार ZSTD_DStreamInSize(व्योम) अणु वापस ZSTD_BLOCKSIZE_ABSOLUTEMAX + ZSTD_blockHeaderSize; पूर्ण
माप_प्रकार ZSTD_DStreamOutSize(व्योम) अणु वापस ZSTD_BLOCKSIZE_ABSOLUTEMAX; पूर्ण

माप_प्रकार ZSTD_resetDStream(ZSTD_DStream *zds)
अणु
	zds->stage = zdss_loadHeader;
	zds->lhSize = zds->inPos = zds->outStart = zds->outEnd = 0;
	zds->legacyVersion = 0;
	zds->hostageByte = 0;
	वापस ZSTD_frameHeaderSize_prefix;
पूर्ण

/* *****   Decompression   ***** */

ZSTD_STATIC माप_प्रकार ZSTD_limitCopy(व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	माप_प्रकार स्थिर length = MIN(dstCapacity, srcSize);
	स_नकल(dst, src, length);
	वापस length;
पूर्ण

माप_प्रकार ZSTD_decompressStream(ZSTD_DStream *zds, ZSTD_outBuffer *output, ZSTD_inBuffer *input)
अणु
	स्थिर अक्षर *स्थिर istart = (स्थिर अक्षर *)(input->src) + input->pos;
	स्थिर अक्षर *स्थिर iend = (स्थिर अक्षर *)(input->src) + input->size;
	स्थिर अक्षर *ip = istart;
	अक्षर *स्थिर ostart = (अक्षर *)(output->dst) + output->pos;
	अक्षर *स्थिर oend = (अक्षर *)(output->dst) + output->size;
	अक्षर *op = ostart;
	U32 someMoreWork = 1;

	जबतक (someMoreWork) अणु
		चयन (zds->stage) अणु
		हाल zdss_init:
			ZSTD_resetDStream(zds); /* transparent reset on starting decoding a new frame */
			fallthrough;

		हाल zdss_loadHeader: अणु
			माप_प्रकार स्थिर hSize = ZSTD_getFrameParams(&zds->fParams, zds->headerBuffer, zds->lhSize);
			अगर (ZSTD_isError(hSize))
				वापस hSize;
			अगर (hSize != 0) अणु				   /* need more input */
				माप_प्रकार स्थिर toLoad = hSize - zds->lhSize; /* अगर hSize!=0, hSize > zds->lhSize */
				अगर (toLoad > (माप_प्रकार)(iend - ip)) अणु	/* not enough input to load full header */
					स_नकल(zds->headerBuffer + zds->lhSize, ip, iend - ip);
					zds->lhSize += iend - ip;
					input->pos = input->size;
					वापस (MAX(ZSTD_frameHeaderSize_min, hSize) - zds->lhSize) +
					       ZSTD_blockHeaderSize; /* reमुख्यing header bytes + next block header */
				पूर्ण
				स_नकल(zds->headerBuffer + zds->lhSize, ip, toLoad);
				zds->lhSize = hSize;
				ip += toLoad;
				अवरोध;
			पूर्ण

			/* check क्रम single-pass mode opportunity */
			अगर (zds->fParams.frameContentSize && zds->fParams.winकरोwSize /* skippable frame अगर == 0 */
			    && (U64)(माप_प्रकार)(oend - op) >= zds->fParams.frameContentSize) अणु
				माप_प्रकार स्थिर cSize = ZSTD_findFrameCompressedSize(istart, iend - istart);
				अगर (cSize <= (माप_प्रकार)(iend - istart)) अणु
					माप_प्रकार स्थिर decompressedSize = ZSTD_decompress_usingDDict(zds->dctx, op, oend - op, istart, cSize, zds->ddict);
					अगर (ZSTD_isError(decompressedSize))
						वापस decompressedSize;
					ip = istart + cSize;
					op += decompressedSize;
					zds->dctx->expected = 0;
					zds->stage = zdss_init;
					someMoreWork = 0;
					अवरोध;
				पूर्ण
			पूर्ण

			/* Consume header */
			ZSTD_refDDict(zds->dctx, zds->ddict);
			अणु
				माप_प्रकार स्थिर h1Size = ZSTD_nextSrcSizeToDecompress(zds->dctx); /* == ZSTD_frameHeaderSize_prefix */
				CHECK_F(ZSTD_decompressContinue(zds->dctx, शून्य, 0, zds->headerBuffer, h1Size));
				अणु
					माप_प्रकार स्थिर h2Size = ZSTD_nextSrcSizeToDecompress(zds->dctx);
					CHECK_F(ZSTD_decompressContinue(zds->dctx, शून्य, 0, zds->headerBuffer + h1Size, h2Size));
				पूर्ण
			पूर्ण

			zds->fParams.winकरोwSize = MAX(zds->fParams.winकरोwSize, 1U << ZSTD_WINDOWLOG_ABSOLUTEMIN);
			अगर (zds->fParams.winकरोwSize > zds->maxWinकरोwSize)
				वापस ERROR(frameParameter_winकरोwTooLarge);

			/* Buffers are pपुनः_स्मृतिated, but द्विगुन check */
			अणु
				माप_प्रकार स्थिर blockSize = MIN(zds->maxWinकरोwSize, ZSTD_BLOCKSIZE_ABSOLUTEMAX);
				माप_प्रकार स्थिर neededOutSize = zds->maxWinकरोwSize + blockSize + WILDCOPY_OVERLENGTH * 2;
				अगर (zds->inBuffSize < blockSize) अणु
					वापस ERROR(GENERIC);
				पूर्ण
				अगर (zds->outBuffSize < neededOutSize) अणु
					वापस ERROR(GENERIC);
				पूर्ण
				zds->blockSize = blockSize;
			पूर्ण
			zds->stage = zdss_पढ़ो;
		पूर्ण
			fallthrough;

		हाल zdss_पढ़ो: अणु
			माप_प्रकार स्थिर neededInSize = ZSTD_nextSrcSizeToDecompress(zds->dctx);
			अगर (neededInSize == 0) अणु /* end of frame */
				zds->stage = zdss_init;
				someMoreWork = 0;
				अवरोध;
			पूर्ण
			अगर ((माप_प्रकार)(iend - ip) >= neededInSize) अणु /* decode directly from src */
				स्थिर पूर्णांक isSkipFrame = ZSTD_isSkipFrame(zds->dctx);
				माप_प्रकार स्थिर decodedSize = ZSTD_decompressContinue(zds->dctx, zds->outBuff + zds->outStart,
										   (isSkipFrame ? 0 : zds->outBuffSize - zds->outStart), ip, neededInSize);
				अगर (ZSTD_isError(decodedSize))
					वापस decodedSize;
				ip += neededInSize;
				अगर (!decodedSize && !isSkipFrame)
					अवरोध; /* this was just a header */
				zds->outEnd = zds->outStart + decodedSize;
				zds->stage = zdss_flush;
				अवरोध;
			पूर्ण
			अगर (ip == iend) अणु
				someMoreWork = 0;
				अवरोध;
			पूर्ण /* no more input */
			zds->stage = zdss_load;
			/* pass-through */
		पूर्ण
			fallthrough;

		हाल zdss_load: अणु
			माप_प्रकार स्थिर neededInSize = ZSTD_nextSrcSizeToDecompress(zds->dctx);
			माप_प्रकार स्थिर toLoad = neededInSize - zds->inPos; /* should always be <= reमुख्यing space within inBuff */
			माप_प्रकार loadedSize;
			अगर (toLoad > zds->inBuffSize - zds->inPos)
				वापस ERROR(corruption_detected); /* should never happen */
			loadedSize = ZSTD_limitCopy(zds->inBuff + zds->inPos, toLoad, ip, iend - ip);
			ip += loadedSize;
			zds->inPos += loadedSize;
			अगर (loadedSize < toLoad) अणु
				someMoreWork = 0;
				अवरोध;
			पूर्ण /* not enough input, रुको क्रम more */

			/* decode loaded input */
			अणु
				स्थिर पूर्णांक isSkipFrame = ZSTD_isSkipFrame(zds->dctx);
				माप_प्रकार स्थिर decodedSize = ZSTD_decompressContinue(zds->dctx, zds->outBuff + zds->outStart, zds->outBuffSize - zds->outStart,
										   zds->inBuff, neededInSize);
				अगर (ZSTD_isError(decodedSize))
					वापस decodedSize;
				zds->inPos = 0; /* input is consumed */
				अगर (!decodedSize && !isSkipFrame) अणु
					zds->stage = zdss_पढ़ो;
					अवरोध;
				पूर्ण /* this was just a header */
				zds->outEnd = zds->outStart + decodedSize;
				zds->stage = zdss_flush;
				/* pass-through */
			पूर्ण
		पूर्ण
			fallthrough;

		हाल zdss_flush: अणु
			माप_प्रकार स्थिर toFlushSize = zds->outEnd - zds->outStart;
			माप_प्रकार स्थिर flushedSize = ZSTD_limitCopy(op, oend - op, zds->outBuff + zds->outStart, toFlushSize);
			op += flushedSize;
			zds->outStart += flushedSize;
			अगर (flushedSize == toFlushSize) अणु /* flush completed */
				zds->stage = zdss_पढ़ो;
				अगर (zds->outStart + zds->blockSize > zds->outBuffSize)
					zds->outStart = zds->outEnd = 0;
				अवरोध;
			पूर्ण
			/* cannot complete flush */
			someMoreWork = 0;
			अवरोध;
		पूर्ण
		शेष:
			वापस ERROR(GENERIC); /* impossible */
		पूर्ण
	पूर्ण

	/* result */
	input->pos += (माप_प्रकार)(ip - istart);
	output->pos += (माप_प्रकार)(op - ostart);
	अणु
		माप_प्रकार nextSrcSizeHपूर्णांक = ZSTD_nextSrcSizeToDecompress(zds->dctx);
		अगर (!nextSrcSizeHपूर्णांक) अणु			    /* frame fully decoded */
			अगर (zds->outEnd == zds->outStart) अणु /* output fully flushed */
				अगर (zds->hostageByte) अणु
					अगर (input->pos >= input->size) अणु
						zds->stage = zdss_पढ़ो;
						वापस 1;
					पूर्ण	     /* can't release hostage (not present) */
					input->pos++; /* release hostage */
				पूर्ण
				वापस 0;
			पूर्ण
			अगर (!zds->hostageByte) अणु /* output not fully flushed; keep last byte as hostage; will be released when all output is flushed */
				input->pos--;    /* note : pos > 0, otherwise, impossible to finish पढ़ोing last block */
				zds->hostageByte = 1;
			पूर्ण
			वापस 1;
		पूर्ण
		nextSrcSizeHपूर्णांक += ZSTD_blockHeaderSize * (ZSTD_nextInputType(zds->dctx) == ZSTDnit_block); /* preload header of next block */
		अगर (zds->inPos > nextSrcSizeHपूर्णांक)
			वापस ERROR(GENERIC); /* should never happen */
		nextSrcSizeHपूर्णांक -= zds->inPos; /* alपढ़ोy loaded*/
		वापस nextSrcSizeHपूर्णांक;
	पूर्ण
पूर्ण

EXPORT_SYMBOL(ZSTD_DCtxWorkspaceBound);
EXPORT_SYMBOL(ZSTD_initDCtx);
EXPORT_SYMBOL(ZSTD_decompressDCtx);
EXPORT_SYMBOL(ZSTD_decompress_usingDict);

EXPORT_SYMBOL(ZSTD_DDictWorkspaceBound);
EXPORT_SYMBOL(ZSTD_initDDict);
EXPORT_SYMBOL(ZSTD_decompress_usingDDict);

EXPORT_SYMBOL(ZSTD_DStreamWorkspaceBound);
EXPORT_SYMBOL(ZSTD_initDStream);
EXPORT_SYMBOL(ZSTD_initDStream_usingDDict);
EXPORT_SYMBOL(ZSTD_resetDStream);
EXPORT_SYMBOL(ZSTD_decompressStream);
EXPORT_SYMBOL(ZSTD_DStreamInSize);
EXPORT_SYMBOL(ZSTD_DStreamOutSize);

EXPORT_SYMBOL(ZSTD_findFrameCompressedSize);
EXPORT_SYMBOL(ZSTD_getFrameContentSize);
EXPORT_SYMBOL(ZSTD_findDecompressedSize);

EXPORT_SYMBOL(ZSTD_isFrame);
EXPORT_SYMBOL(ZSTD_getDictID_fromDict);
EXPORT_SYMBOL(ZSTD_getDictID_fromDDict);
EXPORT_SYMBOL(ZSTD_getDictID_fromFrame);

EXPORT_SYMBOL(ZSTD_getFrameParams);
EXPORT_SYMBOL(ZSTD_decompressBegin);
EXPORT_SYMBOL(ZSTD_decompressBegin_usingDict);
EXPORT_SYMBOL(ZSTD_copyDCtx);
EXPORT_SYMBOL(ZSTD_nextSrcSizeToDecompress);
EXPORT_SYMBOL(ZSTD_decompressContinue);
EXPORT_SYMBOL(ZSTD_nextInputType);

EXPORT_SYMBOL(ZSTD_decompressBlock);
EXPORT_SYMBOL(ZSTD_insertBlock);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Zstd Decompressor");
