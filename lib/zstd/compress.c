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

/*-*************************************
*  Dependencies
***************************************/
#समावेश "fse.h"
#समावेश "huf.h"
#समावेश "mem.h"
#समावेश "zstd_internal.h" /* includes zstd.h */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स> /* स_रखो */

/*-*************************************
*  Constants
***************************************/
अटल स्थिर U32 g_searchStrength = 8; /* control skip over incompressible data */
#घोषणा HASH_READ_SIZE 8
प्रकार क्रमागत अणु ZSTDcs_created = 0, ZSTDcs_init, ZSTDcs_ongoing, ZSTDcs_ending पूर्ण ZSTD_compressionStage_e;

/*-*************************************
*  Helper functions
***************************************/
माप_प्रकार ZSTD_compressBound(माप_प्रकार srcSize) अणु वापस FSE_compressBound(srcSize) + 12; पूर्ण

/*-*************************************
*  Sequence storage
***************************************/
अटल व्योम ZSTD_resetSeqStore(seqStore_t *ssPtr)
अणु
	ssPtr->lit = ssPtr->litStart;
	ssPtr->sequences = ssPtr->sequencesStart;
	ssPtr->दीर्घLengthID = 0;
पूर्ण

/*-*************************************
*  Context memory management
***************************************/
काष्ठा ZSTD_CCtx_s अणु
	स्थिर BYTE *nextSrc;  /* next block here to जारी on curr prefix */
	स्थिर BYTE *base;     /* All regular indexes relative to this position */
	स्थिर BYTE *dictBase; /* extDict indexes relative to this position */
	U32 dictLimit;	/* below that poपूर्णांक, need extDict */
	U32 lowLimit;	 /* below that poपूर्णांक, no more data */
	U32 nextToUpdate;     /* index from which to जारी dictionary update */
	U32 nextToUpdate3;    /* index from which to जारी dictionary update */
	U32 hashLog3;	 /* dispatch table : larger == faster, more memory */
	U32 loadedDictEnd;    /* index of end of dictionary */
	U32 क्रमceWinकरोw;      /* क्रमce back-references to respect limit of 1<<wLog, even क्रम dictionary */
	U32 क्रमceRawDict;     /* Force loading dictionary in "content-only" mode (no header analysis) */
	ZSTD_compressionStage_e stage;
	U32 rep[ZSTD_REP_NUM];
	U32 repToConfirm[ZSTD_REP_NUM];
	U32 dictID;
	ZSTD_parameters params;
	व्योम *workSpace;
	माप_प्रकार workSpaceSize;
	माप_प्रकार blockSize;
	U64 frameContentSize;
	काष्ठा xxh64_state xxhState;
	ZSTD_customMem customMem;

	seqStore_t seqStore; /* sequences storage ptrs */
	U32 *hashTable;
	U32 *hashTable3;
	U32 *chainTable;
	HUF_CElt *hufTable;
	U32 flagStaticTables;
	HUF_repeat flagStaticHufTable;
	FSE_CTable offcodeCTable[FSE_CTABLE_SIZE_U32(OffFSELog, MaxOff)];
	FSE_CTable matchlengthCTable[FSE_CTABLE_SIZE_U32(MLFSELog, MaxML)];
	FSE_CTable litlengthCTable[FSE_CTABLE_SIZE_U32(LLFSELog, MaxLL)];
	अचिन्हित पंचांगpCounters[HUF_COMPRESS_WORKSPACE_SIZE_U32];
पूर्ण;

माप_प्रकार ZSTD_CCtxWorkspaceBound(ZSTD_compressionParameters cParams)
अणु
	माप_प्रकार स्थिर blockSize = MIN(ZSTD_BLOCKSIZE_ABSOLUTEMAX, (माप_प्रकार)1 << cParams.winकरोwLog);
	U32 स्थिर भागider = (cParams.searchLength == 3) ? 3 : 4;
	माप_प्रकार स्थिर maxNbSeq = blockSize / भागider;
	माप_प्रकार स्थिर tokenSpace = blockSize + 11 * maxNbSeq;
	माप_प्रकार स्थिर chainSize = (cParams.strategy == ZSTD_fast) ? 0 : (1 << cParams.chainLog);
	माप_प्रकार स्थिर hSize = ((माप_प्रकार)1) << cParams.hashLog;
	U32 स्थिर hashLog3 = (cParams.searchLength > 3) ? 0 : MIN(ZSTD_HASHLOG3_MAX, cParams.winकरोwLog);
	माप_प्रकार स्थिर h3Size = ((माप_प्रकार)1) << hashLog3;
	माप_प्रकार स्थिर tableSpace = (chainSize + hSize + h3Size) * माप(U32);
	माप_प्रकार स्थिर optSpace =
	    ((MaxML + 1) + (MaxLL + 1) + (MaxOff + 1) + (1 << Litbits)) * माप(U32) + (ZSTD_OPT_NUM + 1) * (माप(ZSTD_match_t) + माप(ZSTD_optimal_t));
	माप_प्रकार स्थिर workspaceSize = tableSpace + (256 * माप(U32)) /* huffTable */ + tokenSpace +
				     (((cParams.strategy == ZSTD_btopt) || (cParams.strategy == ZSTD_btopt2)) ? optSpace : 0);

	वापस ZSTD_ALIGN(माप(ZSTD_stack)) + ZSTD_ALIGN(माप(ZSTD_CCtx)) + ZSTD_ALIGN(workspaceSize);
पूर्ण

अटल ZSTD_CCtx *ZSTD_createCCtx_advanced(ZSTD_customMem customMem)
अणु
	ZSTD_CCtx *cctx;
	अगर (!customMem.customAlloc || !customMem.customFree)
		वापस शून्य;
	cctx = (ZSTD_CCtx *)ZSTD_दो_स्मृति(माप(ZSTD_CCtx), customMem);
	अगर (!cctx)
		वापस शून्य;
	स_रखो(cctx, 0, माप(ZSTD_CCtx));
	cctx->customMem = customMem;
	वापस cctx;
पूर्ण

ZSTD_CCtx *ZSTD_initCCtx(व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	ZSTD_customMem स्थिर stackMem = ZSTD_initStack(workspace, workspaceSize);
	ZSTD_CCtx *cctx = ZSTD_createCCtx_advanced(stackMem);
	अगर (cctx) अणु
		cctx->workSpace = ZSTD_stackAllocAll(cctx->customMem.opaque, &cctx->workSpaceSize);
	पूर्ण
	वापस cctx;
पूर्ण

माप_प्रकार ZSTD_मुक्तCCtx(ZSTD_CCtx *cctx)
अणु
	अगर (cctx == शून्य)
		वापस 0; /* support मुक्त on शून्य */
	ZSTD_मुक्त(cctx->workSpace, cctx->customMem);
	ZSTD_मुक्त(cctx, cctx->customMem);
	वापस 0; /* reserved as a potential error code in the future */
पूर्ण

स्थिर seqStore_t *ZSTD_getSeqStore(स्थिर ZSTD_CCtx *ctx) /* hidden पूर्णांकerface */ अणु वापस &(ctx->seqStore); पूर्ण

अटल ZSTD_parameters ZSTD_getParamsFromCCtx(स्थिर ZSTD_CCtx *cctx) अणु वापस cctx->params; पूर्ण

/** ZSTD_checkParams() :
	ensure param values reमुख्य within authorized range.
	@वापस : 0, or an error code अगर one value is beyond authorized range */
माप_प्रकार ZSTD_checkCParams(ZSTD_compressionParameters cParams)
अणु
#घोषणा CLAMPCHECK(val, min, max)                                       \
	अणु                                                               \
		अगर ((val < min) | (val > max))                          \
			वापस ERROR(compressionParameter_unsupported); \
	पूर्ण
	CLAMPCHECK(cParams.winकरोwLog, ZSTD_WINDOWLOG_MIN, ZSTD_WINDOWLOG_MAX);
	CLAMPCHECK(cParams.chainLog, ZSTD_CHAINLOG_MIN, ZSTD_CHAINLOG_MAX);
	CLAMPCHECK(cParams.hashLog, ZSTD_HASHLOG_MIN, ZSTD_HASHLOG_MAX);
	CLAMPCHECK(cParams.searchLog, ZSTD_SEARCHLOG_MIN, ZSTD_SEARCHLOG_MAX);
	CLAMPCHECK(cParams.searchLength, ZSTD_SEARCHLENGTH_MIN, ZSTD_SEARCHLENGTH_MAX);
	CLAMPCHECK(cParams.targetLength, ZSTD_TARGETLENGTH_MIN, ZSTD_TARGETLENGTH_MAX);
	अगर ((U32)(cParams.strategy) > (U32)ZSTD_btopt2)
		वापस ERROR(compressionParameter_unsupported);
	वापस 0;
पूर्ण

/** ZSTD_cycleLog() :
 *  condition क्रम correct operation : hashLog > 1 */
अटल U32 ZSTD_cycleLog(U32 hashLog, ZSTD_strategy strat)
अणु
	U32 स्थिर btScale = ((U32)strat >= (U32)ZSTD_btlazy2);
	वापस hashLog - btScale;
पूर्ण

/** ZSTD_adjustCParams() :
	optimize `cPar` क्रम a given input (`srcSize` and `dictSize`).
	mostly करोwnsizing to reduce memory consumption and initialization.
	Both `srcSize` and `dictSize` are optional (use 0 अगर unknown),
	but अगर both are 0, no optimization can be करोne.
	Note : cPar is considered validated at this stage. Use ZSTD_checkParams() to ensure that. */
ZSTD_compressionParameters ZSTD_adjustCParams(ZSTD_compressionParameters cPar, अचिन्हित दीर्घ दीर्घ srcSize, माप_प्रकार dictSize)
अणु
	अगर (srcSize + dictSize == 0)
		वापस cPar; /* no size inक्रमmation available : no adjusपंचांगent */

	/* resize params, to use less memory when necessary */
	अणु
		U32 स्थिर minSrcSize = (srcSize == 0) ? 500 : 0;
		U64 स्थिर rSize = srcSize + dictSize + minSrcSize;
		अगर (rSize < ((U64)1 << ZSTD_WINDOWLOG_MAX)) अणु
			U32 स्थिर srcLog = MAX(ZSTD_HASHLOG_MIN, ZSTD_highbit32((U32)(rSize)-1) + 1);
			अगर (cPar.winकरोwLog > srcLog)
				cPar.winकरोwLog = srcLog;
		पूर्ण
	पूर्ण
	अगर (cPar.hashLog > cPar.winकरोwLog)
		cPar.hashLog = cPar.winकरोwLog;
	अणु
		U32 स्थिर cycleLog = ZSTD_cycleLog(cPar.chainLog, cPar.strategy);
		अगर (cycleLog > cPar.winकरोwLog)
			cPar.chainLog -= (cycleLog - cPar.winकरोwLog);
	पूर्ण

	अगर (cPar.winकरोwLog < ZSTD_WINDOWLOG_ABSOLUTEMIN)
		cPar.winकरोwLog = ZSTD_WINDOWLOG_ABSOLUTEMIN; /* required क्रम frame header */

	वापस cPar;
पूर्ण

अटल U32 ZSTD_equivalentParams(ZSTD_parameters param1, ZSTD_parameters param2)
अणु
	वापस (param1.cParams.hashLog == param2.cParams.hashLog) & (param1.cParams.chainLog == param2.cParams.chainLog) &
	       (param1.cParams.strategy == param2.cParams.strategy) & ((param1.cParams.searchLength == 3) == (param2.cParams.searchLength == 3));
पूर्ण

/*! ZSTD_जारीCCtx() :
	reuse CCtx without reset (note : requires no dictionary) */
अटल माप_प्रकार ZSTD_जारीCCtx(ZSTD_CCtx *cctx, ZSTD_parameters params, U64 frameContentSize)
अणु
	U32 स्थिर end = (U32)(cctx->nextSrc - cctx->base);
	cctx->params = params;
	cctx->frameContentSize = frameContentSize;
	cctx->lowLimit = end;
	cctx->dictLimit = end;
	cctx->nextToUpdate = end + 1;
	cctx->stage = ZSTDcs_init;
	cctx->dictID = 0;
	cctx->loadedDictEnd = 0;
	अणु
		पूर्णांक i;
		क्रम (i = 0; i < ZSTD_REP_NUM; i++)
			cctx->rep[i] = repStartValue[i];
	पूर्ण
	cctx->seqStore.litLengthSum = 0; /* क्रमce reset of btopt stats */
	xxh64_reset(&cctx->xxhState, 0);
	वापस 0;
पूर्ण

प्रकार क्रमागत अणु ZSTDcrp_जारी, ZSTDcrp_noMemset, ZSTDcrp_fullReset पूर्ण ZSTD_compResetPolicy_e;

/*! ZSTD_resetCCtx_advanced() :
	note : `params` must be validated */
अटल माप_प्रकार ZSTD_resetCCtx_advanced(ZSTD_CCtx *zc, ZSTD_parameters params, U64 frameContentSize, ZSTD_compResetPolicy_e स्थिर crp)
अणु
	अगर (crp == ZSTDcrp_जारी)
		अगर (ZSTD_equivalentParams(params, zc->params)) अणु
			zc->flagStaticTables = 0;
			zc->flagStaticHufTable = HUF_repeat_none;
			वापस ZSTD_जारीCCtx(zc, params, frameContentSize);
		पूर्ण

	अणु
		माप_प्रकार स्थिर blockSize = MIN(ZSTD_BLOCKSIZE_ABSOLUTEMAX, (माप_प्रकार)1 << params.cParams.winकरोwLog);
		U32 स्थिर भागider = (params.cParams.searchLength == 3) ? 3 : 4;
		माप_प्रकार स्थिर maxNbSeq = blockSize / भागider;
		माप_प्रकार स्थिर tokenSpace = blockSize + 11 * maxNbSeq;
		माप_प्रकार स्थिर chainSize = (params.cParams.strategy == ZSTD_fast) ? 0 : (1 << params.cParams.chainLog);
		माप_प्रकार स्थिर hSize = ((माप_प्रकार)1) << params.cParams.hashLog;
		U32 स्थिर hashLog3 = (params.cParams.searchLength > 3) ? 0 : MIN(ZSTD_HASHLOG3_MAX, params.cParams.winकरोwLog);
		माप_प्रकार स्थिर h3Size = ((माप_प्रकार)1) << hashLog3;
		माप_प्रकार स्थिर tableSpace = (chainSize + hSize + h3Size) * माप(U32);
		व्योम *ptr;

		/* Check अगर workSpace is large enough, alloc a new one अगर needed */
		अणु
			माप_प्रकार स्थिर optSpace = ((MaxML + 1) + (MaxLL + 1) + (MaxOff + 1) + (1 << Litbits)) * माप(U32) +
						(ZSTD_OPT_NUM + 1) * (माप(ZSTD_match_t) + माप(ZSTD_optimal_t));
			माप_प्रकार स्थिर neededSpace = tableSpace + (256 * माप(U32)) /* huffTable */ + tokenSpace +
						   (((params.cParams.strategy == ZSTD_btopt) || (params.cParams.strategy == ZSTD_btopt2)) ? optSpace : 0);
			अगर (zc->workSpaceSize < neededSpace) अणु
				ZSTD_मुक्त(zc->workSpace, zc->customMem);
				zc->workSpace = ZSTD_दो_स्मृति(neededSpace, zc->customMem);
				अगर (zc->workSpace == शून्य)
					वापस ERROR(memory_allocation);
				zc->workSpaceSize = neededSpace;
			पूर्ण
		पूर्ण

		अगर (crp != ZSTDcrp_noMemset)
			स_रखो(zc->workSpace, 0, tableSpace); /* reset tables only */
		xxh64_reset(&zc->xxhState, 0);
		zc->hashLog3 = hashLog3;
		zc->hashTable = (U32 *)(zc->workSpace);
		zc->chainTable = zc->hashTable + hSize;
		zc->hashTable3 = zc->chainTable + chainSize;
		ptr = zc->hashTable3 + h3Size;
		zc->hufTable = (HUF_CElt *)ptr;
		zc->flagStaticTables = 0;
		zc->flagStaticHufTable = HUF_repeat_none;
		ptr = ((U32 *)ptr) + 256; /* note : HUF_CElt* is incomplete type, size is simulated using U32 */

		zc->nextToUpdate = 1;
		zc->nextSrc = शून्य;
		zc->base = शून्य;
		zc->dictBase = शून्य;
		zc->dictLimit = 0;
		zc->lowLimit = 0;
		zc->params = params;
		zc->blockSize = blockSize;
		zc->frameContentSize = frameContentSize;
		अणु
			पूर्णांक i;
			क्रम (i = 0; i < ZSTD_REP_NUM; i++)
				zc->rep[i] = repStartValue[i];
		पूर्ण

		अगर ((params.cParams.strategy == ZSTD_btopt) || (params.cParams.strategy == ZSTD_btopt2)) अणु
			zc->seqStore.litFreq = (U32 *)ptr;
			zc->seqStore.litLengthFreq = zc->seqStore.litFreq + (1 << Litbits);
			zc->seqStore.matchLengthFreq = zc->seqStore.litLengthFreq + (MaxLL + 1);
			zc->seqStore.offCodeFreq = zc->seqStore.matchLengthFreq + (MaxML + 1);
			ptr = zc->seqStore.offCodeFreq + (MaxOff + 1);
			zc->seqStore.matchTable = (ZSTD_match_t *)ptr;
			ptr = zc->seqStore.matchTable + ZSTD_OPT_NUM + 1;
			zc->seqStore.priceTable = (ZSTD_optimal_t *)ptr;
			ptr = zc->seqStore.priceTable + ZSTD_OPT_NUM + 1;
			zc->seqStore.litLengthSum = 0;
		पूर्ण
		zc->seqStore.sequencesStart = (seqDef *)ptr;
		ptr = zc->seqStore.sequencesStart + maxNbSeq;
		zc->seqStore.llCode = (BYTE *)ptr;
		zc->seqStore.mlCode = zc->seqStore.llCode + maxNbSeq;
		zc->seqStore.ofCode = zc->seqStore.mlCode + maxNbSeq;
		zc->seqStore.litStart = zc->seqStore.ofCode + maxNbSeq;

		zc->stage = ZSTDcs_init;
		zc->dictID = 0;
		zc->loadedDictEnd = 0;

		वापस 0;
	पूर्ण
पूर्ण

/* ZSTD_invalidateRepCodes() :
 * ensures next compression will not use repcodes from previous block.
 * Note : only works with regular variant;
 *        करो not use with extDict variant ! */
व्योम ZSTD_invalidateRepCodes(ZSTD_CCtx *cctx)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ZSTD_REP_NUM; i++)
		cctx->rep[i] = 0;
पूर्ण

/*! ZSTD_copyCCtx() :
*   Duplicate an existing context `srcCCtx` पूर्णांकo another one `dstCCtx`.
*   Only works during stage ZSTDcs_init (i.e. after creation, but beक्रमe first call to ZSTD_compressContinue()).
*   @वापस : 0, or an error code */
माप_प्रकार ZSTD_copyCCtx(ZSTD_CCtx *dstCCtx, स्थिर ZSTD_CCtx *srcCCtx, अचिन्हित दीर्घ दीर्घ pledgedSrcSize)
अणु
	अगर (srcCCtx->stage != ZSTDcs_init)
		वापस ERROR(stage_wrong);

	स_नकल(&dstCCtx->customMem, &srcCCtx->customMem, माप(ZSTD_customMem));
	अणु
		ZSTD_parameters params = srcCCtx->params;
		params.fParams.contentSizeFlag = (pledgedSrcSize > 0);
		ZSTD_resetCCtx_advanced(dstCCtx, params, pledgedSrcSize, ZSTDcrp_noMemset);
	पूर्ण

	/* copy tables */
	अणु
		माप_प्रकार स्थिर chainSize = (srcCCtx->params.cParams.strategy == ZSTD_fast) ? 0 : (1 << srcCCtx->params.cParams.chainLog);
		माप_प्रकार स्थिर hSize = ((माप_प्रकार)1) << srcCCtx->params.cParams.hashLog;
		माप_प्रकार स्थिर h3Size = (माप_प्रकार)1 << srcCCtx->hashLog3;
		माप_प्रकार स्थिर tableSpace = (chainSize + hSize + h3Size) * माप(U32);
		स_नकल(dstCCtx->workSpace, srcCCtx->workSpace, tableSpace);
	पूर्ण

	/* copy dictionary offsets */
	dstCCtx->nextToUpdate = srcCCtx->nextToUpdate;
	dstCCtx->nextToUpdate3 = srcCCtx->nextToUpdate3;
	dstCCtx->nextSrc = srcCCtx->nextSrc;
	dstCCtx->base = srcCCtx->base;
	dstCCtx->dictBase = srcCCtx->dictBase;
	dstCCtx->dictLimit = srcCCtx->dictLimit;
	dstCCtx->lowLimit = srcCCtx->lowLimit;
	dstCCtx->loadedDictEnd = srcCCtx->loadedDictEnd;
	dstCCtx->dictID = srcCCtx->dictID;

	/* copy entropy tables */
	dstCCtx->flagStaticTables = srcCCtx->flagStaticTables;
	dstCCtx->flagStaticHufTable = srcCCtx->flagStaticHufTable;
	अगर (srcCCtx->flagStaticTables) अणु
		स_नकल(dstCCtx->litlengthCTable, srcCCtx->litlengthCTable, माप(dstCCtx->litlengthCTable));
		स_नकल(dstCCtx->matchlengthCTable, srcCCtx->matchlengthCTable, माप(dstCCtx->matchlengthCTable));
		स_नकल(dstCCtx->offcodeCTable, srcCCtx->offcodeCTable, माप(dstCCtx->offcodeCTable));
	पूर्ण
	अगर (srcCCtx->flagStaticHufTable) अणु
		स_नकल(dstCCtx->hufTable, srcCCtx->hufTable, 256 * 4);
	पूर्ण

	वापस 0;
पूर्ण

/*! ZSTD_reduceTable() :
*   reduce table indexes by `reducerValue` */
अटल व्योम ZSTD_reduceTable(U32 *स्थिर table, U32 स्थिर size, U32 स्थिर reducerValue)
अणु
	U32 u;
	क्रम (u = 0; u < size; u++) अणु
		अगर (table[u] < reducerValue)
			table[u] = 0;
		अन्यथा
			table[u] -= reducerValue;
	पूर्ण
पूर्ण

/*! ZSTD_reduceIndex() :
*   rescale all indexes to aव्योम future overflow (indexes are U32) */
अटल व्योम ZSTD_reduceIndex(ZSTD_CCtx *zc, स्थिर U32 reducerValue)
अणु
	अणु
		U32 स्थिर hSize = 1 << zc->params.cParams.hashLog;
		ZSTD_reduceTable(zc->hashTable, hSize, reducerValue);
	पूर्ण

	अणु
		U32 स्थिर chainSize = (zc->params.cParams.strategy == ZSTD_fast) ? 0 : (1 << zc->params.cParams.chainLog);
		ZSTD_reduceTable(zc->chainTable, chainSize, reducerValue);
	पूर्ण

	अणु
		U32 स्थिर h3Size = (zc->hashLog3) ? 1 << zc->hashLog3 : 0;
		ZSTD_reduceTable(zc->hashTable3, h3Size, reducerValue);
	पूर्ण
पूर्ण

/*-*******************************************************
*  Block entropic compression
*********************************************************/

/* See करोc/zstd_compression_क्रमmat.md क्रम detailed क्रमmat description */

माप_प्रकार ZSTD_noCompressBlock(व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	अगर (srcSize + ZSTD_blockHeaderSize > dstCapacity)
		वापस ERROR(dstSize_tooSmall);
	स_नकल((BYTE *)dst + ZSTD_blockHeaderSize, src, srcSize);
	ZSTD_ग_लिखोLE24(dst, (U32)(srcSize << 2) + (U32)bt_raw);
	वापस ZSTD_blockHeaderSize + srcSize;
पूर्ण

अटल माप_प्रकार ZSTD_noCompressLiterals(व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	BYTE *स्थिर ostart = (BYTE * स्थिर)dst;
	U32 स्थिर flSize = 1 + (srcSize > 31) + (srcSize > 4095);

	अगर (srcSize + flSize > dstCapacity)
		वापस ERROR(dstSize_tooSmall);

	चयन (flSize) अणु
	हाल 1: /* 2 - 1 - 5 */ ostart[0] = (BYTE)((U32)set_basic + (srcSize << 3)); अवरोध;
	हाल 2: /* 2 - 2 - 12 */ ZSTD_ग_लिखोLE16(ostart, (U16)((U32)set_basic + (1 << 2) + (srcSize << 4))); अवरोध;
	शेष: /*note : should not be necessary : flSize is within अणु1,2,3पूर्ण */
	हाल 3: /* 2 - 2 - 20 */ ZSTD_ग_लिखोLE32(ostart, (U32)((U32)set_basic + (3 << 2) + (srcSize << 4))); अवरोध;
	पूर्ण

	स_नकल(ostart + flSize, src, srcSize);
	वापस srcSize + flSize;
पूर्ण

अटल माप_प्रकार ZSTD_compressRleLiteralsBlock(व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	BYTE *स्थिर ostart = (BYTE * स्थिर)dst;
	U32 स्थिर flSize = 1 + (srcSize > 31) + (srcSize > 4095);

	(व्योम)dstCapacity; /* dstCapacity alपढ़ोy guaranteed to be >=4, hence large enough */

	चयन (flSize) अणु
	हाल 1: /* 2 - 1 - 5 */ ostart[0] = (BYTE)((U32)set_rle + (srcSize << 3)); अवरोध;
	हाल 2: /* 2 - 2 - 12 */ ZSTD_ग_लिखोLE16(ostart, (U16)((U32)set_rle + (1 << 2) + (srcSize << 4))); अवरोध;
	शेष: /*note : should not be necessary : flSize is necessarily within अणु1,2,3पूर्ण */
	हाल 3: /* 2 - 2 - 20 */ ZSTD_ग_लिखोLE32(ostart, (U32)((U32)set_rle + (3 << 2) + (srcSize << 4))); अवरोध;
	पूर्ण

	ostart[flSize] = *(स्थिर BYTE *)src;
	वापस flSize + 1;
पूर्ण

अटल माप_प्रकार ZSTD_minGain(माप_प्रकार srcSize) अणु वापस (srcSize >> 6) + 2; पूर्ण

अटल माप_प्रकार ZSTD_compressLiterals(ZSTD_CCtx *zc, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	माप_प्रकार स्थिर minGain = ZSTD_minGain(srcSize);
	माप_प्रकार स्थिर lhSize = 3 + (srcSize >= 1 KB) + (srcSize >= 16 KB);
	BYTE *स्थिर ostart = (BYTE *)dst;
	U32 singleStream = srcSize < 256;
	symbolEncodingType_e hType = set_compressed;
	माप_प्रकार cLitSize;

/* small ? करोn't even attempt compression (speed opt) */
#घोषणा LITERAL_NOENTROPY 63
	अणु
		माप_प्रकार स्थिर minLitSize = zc->flagStaticHufTable == HUF_repeat_valid ? 6 : LITERAL_NOENTROPY;
		अगर (srcSize <= minLitSize)
			वापस ZSTD_noCompressLiterals(dst, dstCapacity, src, srcSize);
	पूर्ण

	अगर (dstCapacity < lhSize + 1)
		वापस ERROR(dstSize_tooSmall); /* not enough space क्रम compression */
	अणु
		HUF_repeat repeat = zc->flagStaticHufTable;
		पूर्णांक स्थिर preferRepeat = zc->params.cParams.strategy < ZSTD_lazy ? srcSize <= 1024 : 0;
		अगर (repeat == HUF_repeat_valid && lhSize == 3)
			singleStream = 1;
		cLitSize = singleStream ? HUF_compress1X_repeat(ostart + lhSize, dstCapacity - lhSize, src, srcSize, 255, 11, zc->पंचांगpCounters,
								माप(zc->पंचांगpCounters), zc->hufTable, &repeat, preferRepeat)
					: HUF_compress4X_repeat(ostart + lhSize, dstCapacity - lhSize, src, srcSize, 255, 11, zc->पंचांगpCounters,
								माप(zc->पंचांगpCounters), zc->hufTable, &repeat, preferRepeat);
		अगर (repeat != HUF_repeat_none) अणु
			hType = set_repeat;
		पूर्ण /* reused the existing table */
		अन्यथा अणु
			zc->flagStaticHufTable = HUF_repeat_check;
		पूर्ण /* now have a table to reuse */
	पूर्ण

	अगर ((cLitSize == 0) | (cLitSize >= srcSize - minGain)) अणु
		zc->flagStaticHufTable = HUF_repeat_none;
		वापस ZSTD_noCompressLiterals(dst, dstCapacity, src, srcSize);
	पूर्ण
	अगर (cLitSize == 1) अणु
		zc->flagStaticHufTable = HUF_repeat_none;
		वापस ZSTD_compressRleLiteralsBlock(dst, dstCapacity, src, srcSize);
	पूर्ण

	/* Build header */
	चयन (lhSize) अणु
	हाल 3: /* 2 - 2 - 10 - 10 */
	अणु
		U32 स्थिर lhc = hType + ((!singleStream) << 2) + ((U32)srcSize << 4) + ((U32)cLitSize << 14);
		ZSTD_ग_लिखोLE24(ostart, lhc);
		अवरोध;
	पूर्ण
	हाल 4: /* 2 - 2 - 14 - 14 */
	अणु
		U32 स्थिर lhc = hType + (2 << 2) + ((U32)srcSize << 4) + ((U32)cLitSize << 18);
		ZSTD_ग_लिखोLE32(ostart, lhc);
		अवरोध;
	पूर्ण
	शेष: /* should not be necessary, lhSize is only अणु3,4,5पूर्ण */
	हाल 5:  /* 2 - 2 - 18 - 18 */
	अणु
		U32 स्थिर lhc = hType + (3 << 2) + ((U32)srcSize << 4) + ((U32)cLitSize << 22);
		ZSTD_ग_लिखोLE32(ostart, lhc);
		ostart[4] = (BYTE)(cLitSize >> 10);
		अवरोध;
	पूर्ण
	पूर्ण
	वापस lhSize + cLitSize;
पूर्ण

अटल स्थिर BYTE LL_Code[64] = अणु0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 16, 17, 17, 18, 18,
				 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23,
				 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24पूर्ण;

अटल स्थिर BYTE ML_Code[128] = अणु0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
				  26, 27, 28, 29, 30, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 36, 36, 37, 37, 37, 37, 38, 38, 38, 38,
				  38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
				  40, 40, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 42, 42,
				  42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42पूर्ण;

व्योम ZSTD_seqToCodes(स्थिर seqStore_t *seqStorePtr)
अणु
	BYTE स्थिर LL_deltaCode = 19;
	BYTE स्थिर ML_deltaCode = 36;
	स्थिर seqDef *स्थिर sequences = seqStorePtr->sequencesStart;
	BYTE *स्थिर llCodeTable = seqStorePtr->llCode;
	BYTE *स्थिर ofCodeTable = seqStorePtr->ofCode;
	BYTE *स्थिर mlCodeTable = seqStorePtr->mlCode;
	U32 स्थिर nbSeq = (U32)(seqStorePtr->sequences - seqStorePtr->sequencesStart);
	U32 u;
	क्रम (u = 0; u < nbSeq; u++) अणु
		U32 स्थिर llv = sequences[u].litLength;
		U32 स्थिर mlv = sequences[u].matchLength;
		llCodeTable[u] = (llv > 63) ? (BYTE)ZSTD_highbit32(llv) + LL_deltaCode : LL_Code[llv];
		ofCodeTable[u] = (BYTE)ZSTD_highbit32(sequences[u].offset);
		mlCodeTable[u] = (mlv > 127) ? (BYTE)ZSTD_highbit32(mlv) + ML_deltaCode : ML_Code[mlv];
	पूर्ण
	अगर (seqStorePtr->दीर्घLengthID == 1)
		llCodeTable[seqStorePtr->दीर्घLengthPos] = MaxLL;
	अगर (seqStorePtr->दीर्घLengthID == 2)
		mlCodeTable[seqStorePtr->दीर्घLengthPos] = MaxML;
पूर्ण

ZSTD_STATIC माप_प्रकार ZSTD_compressSequences_पूर्णांकernal(ZSTD_CCtx *zc, व्योम *dst, माप_प्रकार dstCapacity)
अणु
	स्थिर पूर्णांक दीर्घOffsets = zc->params.cParams.winकरोwLog > STREAM_ACCUMULATOR_MIN;
	स्थिर seqStore_t *seqStorePtr = &(zc->seqStore);
	FSE_CTable *CTable_LitLength = zc->litlengthCTable;
	FSE_CTable *CTable_OffsetBits = zc->offcodeCTable;
	FSE_CTable *CTable_MatchLength = zc->matchlengthCTable;
	U32 LLtype, Offtype, MLtype; /* compressed, raw or rle */
	स्थिर seqDef *स्थिर sequences = seqStorePtr->sequencesStart;
	स्थिर BYTE *स्थिर ofCodeTable = seqStorePtr->ofCode;
	स्थिर BYTE *स्थिर llCodeTable = seqStorePtr->llCode;
	स्थिर BYTE *स्थिर mlCodeTable = seqStorePtr->mlCode;
	BYTE *स्थिर ostart = (BYTE *)dst;
	BYTE *स्थिर oend = ostart + dstCapacity;
	BYTE *op = ostart;
	माप_प्रकार स्थिर nbSeq = seqStorePtr->sequences - seqStorePtr->sequencesStart;
	BYTE *seqHead;

	U32 *count;
	S16 *norm;
	U32 *workspace;
	माप_प्रकार workspaceSize = माप(zc->पंचांगpCounters);
	अणु
		माप_प्रकार spaceUsed32 = 0;
		count = (U32 *)zc->पंचांगpCounters + spaceUsed32;
		spaceUsed32 += MaxSeq + 1;
		norm = (S16 *)((U32 *)zc->पंचांगpCounters + spaceUsed32);
		spaceUsed32 += ALIGN(माप(S16) * (MaxSeq + 1), माप(U32)) >> 2;

		workspace = (U32 *)zc->पंचांगpCounters + spaceUsed32;
		workspaceSize -= (spaceUsed32 << 2);
	पूर्ण

	/* Compress literals */
	अणु
		स्थिर BYTE *स्थिर literals = seqStorePtr->litStart;
		माप_प्रकार स्थिर litSize = seqStorePtr->lit - literals;
		माप_प्रकार स्थिर cSize = ZSTD_compressLiterals(zc, op, dstCapacity, literals, litSize);
		अगर (ZSTD_isError(cSize))
			वापस cSize;
		op += cSize;
	पूर्ण

	/* Sequences Header */
	अगर ((oend - op) < 3 /*max nbSeq Size*/ + 1 /*seqHead */)
		वापस ERROR(dstSize_tooSmall);
	अगर (nbSeq < 0x7F)
		*op++ = (BYTE)nbSeq;
	अन्यथा अगर (nbSeq < LONGNBSEQ)
		op[0] = (BYTE)((nbSeq >> 8) + 0x80), op[1] = (BYTE)nbSeq, op += 2;
	अन्यथा
		op[0] = 0xFF, ZSTD_ग_लिखोLE16(op + 1, (U16)(nbSeq - LONGNBSEQ)), op += 3;
	अगर (nbSeq == 0)
		वापस op - ostart;

	/* seqHead : flags क्रम FSE encoding type */
	seqHead = op++;

#घोषणा MIN_SEQ_FOR_DYNAMIC_FSE 64
#घोषणा MAX_SEQ_FOR_STATIC_FSE 1000

	/* convert length/distances पूर्णांकo codes */
	ZSTD_seqToCodes(seqStorePtr);

	/* CTable क्रम Literal Lengths */
	अणु
		U32 max = MaxLL;
		माप_प्रकार स्थिर mostFrequent = FSE_countFast_wksp(count, &max, llCodeTable, nbSeq, workspace);
		अगर ((mostFrequent == nbSeq) && (nbSeq > 2)) अणु
			*op++ = llCodeTable[0];
			FSE_buildCTable_rle(CTable_LitLength, (BYTE)max);
			LLtype = set_rle;
		पूर्ण अन्यथा अगर ((zc->flagStaticTables) && (nbSeq < MAX_SEQ_FOR_STATIC_FSE)) अणु
			LLtype = set_repeat;
		पूर्ण अन्यथा अगर ((nbSeq < MIN_SEQ_FOR_DYNAMIC_FSE) || (mostFrequent < (nbSeq >> (LL_शेषNormLog - 1)))) अणु
			FSE_buildCTable_wksp(CTable_LitLength, LL_शेषNorm, MaxLL, LL_शेषNormLog, workspace, workspaceSize);
			LLtype = set_basic;
		पूर्ण अन्यथा अणु
			माप_प्रकार nbSeq_1 = nbSeq;
			स्थिर U32 tableLog = FSE_optimalTableLog(LLFSELog, nbSeq, max);
			अगर (count[llCodeTable[nbSeq - 1]] > 1) अणु
				count[llCodeTable[nbSeq - 1]]--;
				nbSeq_1--;
			पूर्ण
			FSE_normalizeCount(norm, tableLog, count, nbSeq_1, max);
			अणु
				माप_प्रकार स्थिर NCountSize = FSE_ग_लिखोNCount(op, oend - op, norm, max, tableLog); /* overflow रक्षित */
				अगर (FSE_isError(NCountSize))
					वापस NCountSize;
				op += NCountSize;
			पूर्ण
			FSE_buildCTable_wksp(CTable_LitLength, norm, max, tableLog, workspace, workspaceSize);
			LLtype = set_compressed;
		पूर्ण
	पूर्ण

	/* CTable क्रम Offsets */
	अणु
		U32 max = MaxOff;
		माप_प्रकार स्थिर mostFrequent = FSE_countFast_wksp(count, &max, ofCodeTable, nbSeq, workspace);
		अगर ((mostFrequent == nbSeq) && (nbSeq > 2)) अणु
			*op++ = ofCodeTable[0];
			FSE_buildCTable_rle(CTable_OffsetBits, (BYTE)max);
			Offtype = set_rle;
		पूर्ण अन्यथा अगर ((zc->flagStaticTables) && (nbSeq < MAX_SEQ_FOR_STATIC_FSE)) अणु
			Offtype = set_repeat;
		पूर्ण अन्यथा अगर ((nbSeq < MIN_SEQ_FOR_DYNAMIC_FSE) || (mostFrequent < (nbSeq >> (OF_शेषNormLog - 1)))) अणु
			FSE_buildCTable_wksp(CTable_OffsetBits, OF_शेषNorm, MaxOff, OF_शेषNormLog, workspace, workspaceSize);
			Offtype = set_basic;
		पूर्ण अन्यथा अणु
			माप_प्रकार nbSeq_1 = nbSeq;
			स्थिर U32 tableLog = FSE_optimalTableLog(OffFSELog, nbSeq, max);
			अगर (count[ofCodeTable[nbSeq - 1]] > 1) अणु
				count[ofCodeTable[nbSeq - 1]]--;
				nbSeq_1--;
			पूर्ण
			FSE_normalizeCount(norm, tableLog, count, nbSeq_1, max);
			अणु
				माप_प्रकार स्थिर NCountSize = FSE_ग_लिखोNCount(op, oend - op, norm, max, tableLog); /* overflow रक्षित */
				अगर (FSE_isError(NCountSize))
					वापस NCountSize;
				op += NCountSize;
			पूर्ण
			FSE_buildCTable_wksp(CTable_OffsetBits, norm, max, tableLog, workspace, workspaceSize);
			Offtype = set_compressed;
		पूर्ण
	पूर्ण

	/* CTable क्रम MatchLengths */
	अणु
		U32 max = MaxML;
		माप_प्रकार स्थिर mostFrequent = FSE_countFast_wksp(count, &max, mlCodeTable, nbSeq, workspace);
		अगर ((mostFrequent == nbSeq) && (nbSeq > 2)) अणु
			*op++ = *mlCodeTable;
			FSE_buildCTable_rle(CTable_MatchLength, (BYTE)max);
			MLtype = set_rle;
		पूर्ण अन्यथा अगर ((zc->flagStaticTables) && (nbSeq < MAX_SEQ_FOR_STATIC_FSE)) अणु
			MLtype = set_repeat;
		पूर्ण अन्यथा अगर ((nbSeq < MIN_SEQ_FOR_DYNAMIC_FSE) || (mostFrequent < (nbSeq >> (ML_शेषNormLog - 1)))) अणु
			FSE_buildCTable_wksp(CTable_MatchLength, ML_शेषNorm, MaxML, ML_शेषNormLog, workspace, workspaceSize);
			MLtype = set_basic;
		पूर्ण अन्यथा अणु
			माप_प्रकार nbSeq_1 = nbSeq;
			स्थिर U32 tableLog = FSE_optimalTableLog(MLFSELog, nbSeq, max);
			अगर (count[mlCodeTable[nbSeq - 1]] > 1) अणु
				count[mlCodeTable[nbSeq - 1]]--;
				nbSeq_1--;
			पूर्ण
			FSE_normalizeCount(norm, tableLog, count, nbSeq_1, max);
			अणु
				माप_प्रकार स्थिर NCountSize = FSE_ग_लिखोNCount(op, oend - op, norm, max, tableLog); /* overflow रक्षित */
				अगर (FSE_isError(NCountSize))
					वापस NCountSize;
				op += NCountSize;
			पूर्ण
			FSE_buildCTable_wksp(CTable_MatchLength, norm, max, tableLog, workspace, workspaceSize);
			MLtype = set_compressed;
		पूर्ण
	पूर्ण

	*seqHead = (BYTE)((LLtype << 6) + (Offtype << 4) + (MLtype << 2));
	zc->flagStaticTables = 0;

	/* Encoding Sequences */
	अणु
		BIT_CStream_t blockStream;
		FSE_CState_t stateMatchLength;
		FSE_CState_t stateOffsetBits;
		FSE_CState_t stateLitLength;

		CHECK_E(BIT_initCStream(&blockStream, op, oend - op), dstSize_tooSmall); /* not enough space reमुख्यing */

		/* first symbols */
		FSE_initCState2(&stateMatchLength, CTable_MatchLength, mlCodeTable[nbSeq - 1]);
		FSE_initCState2(&stateOffsetBits, CTable_OffsetBits, ofCodeTable[nbSeq - 1]);
		FSE_initCState2(&stateLitLength, CTable_LitLength, llCodeTable[nbSeq - 1]);
		BIT_addBits(&blockStream, sequences[nbSeq - 1].litLength, LL_bits[llCodeTable[nbSeq - 1]]);
		अगर (ZSTD_32bits())
			BIT_flushBits(&blockStream);
		BIT_addBits(&blockStream, sequences[nbSeq - 1].matchLength, ML_bits[mlCodeTable[nbSeq - 1]]);
		अगर (ZSTD_32bits())
			BIT_flushBits(&blockStream);
		अगर (दीर्घOffsets) अणु
			U32 स्थिर ofBits = ofCodeTable[nbSeq - 1];
			पूर्णांक स्थिर extraBits = ofBits - MIN(ofBits, STREAM_ACCUMULATOR_MIN - 1);
			अगर (extraBits) अणु
				BIT_addBits(&blockStream, sequences[nbSeq - 1].offset, extraBits);
				BIT_flushBits(&blockStream);
			पूर्ण
			BIT_addBits(&blockStream, sequences[nbSeq - 1].offset >> extraBits, ofBits - extraBits);
		पूर्ण अन्यथा अणु
			BIT_addBits(&blockStream, sequences[nbSeq - 1].offset, ofCodeTable[nbSeq - 1]);
		पूर्ण
		BIT_flushBits(&blockStream);

		अणु
			माप_प्रकार n;
			क्रम (n = nbSeq - 2; n < nbSeq; n--) अणु /* पूर्णांकentional underflow */
				BYTE स्थिर llCode = llCodeTable[n];
				BYTE स्थिर ofCode = ofCodeTable[n];
				BYTE स्थिर mlCode = mlCodeTable[n];
				U32 स्थिर llBits = LL_bits[llCode];
				U32 स्थिर ofBits = ofCode; /* 32b*/ /* 64b*/
				U32 स्थिर mlBits = ML_bits[mlCode];
				/* (7)*/							    /* (7)*/
				FSE_encodeSymbol(&blockStream, &stateOffsetBits, ofCode); /* 15 */  /* 15 */
				FSE_encodeSymbol(&blockStream, &stateMatchLength, mlCode); /* 24 */ /* 24 */
				अगर (ZSTD_32bits())
					BIT_flushBits(&blockStream);				  /* (7)*/
				FSE_encodeSymbol(&blockStream, &stateLitLength, llCode); /* 16 */ /* 33 */
				अगर (ZSTD_32bits() || (ofBits + mlBits + llBits >= 64 - 7 - (LLFSELog + MLFSELog + OffFSELog)))
					BIT_flushBits(&blockStream); /* (7)*/
				BIT_addBits(&blockStream, sequences[n].litLength, llBits);
				अगर (ZSTD_32bits() && ((llBits + mlBits) > 24))
					BIT_flushBits(&blockStream);
				BIT_addBits(&blockStream, sequences[n].matchLength, mlBits);
				अगर (ZSTD_32bits())
					BIT_flushBits(&blockStream); /* (7)*/
				अगर (दीर्घOffsets) अणु
					पूर्णांक स्थिर extraBits = ofBits - MIN(ofBits, STREAM_ACCUMULATOR_MIN - 1);
					अगर (extraBits) अणु
						BIT_addBits(&blockStream, sequences[n].offset, extraBits);
						BIT_flushBits(&blockStream); /* (7)*/
					पूर्ण
					BIT_addBits(&blockStream, sequences[n].offset >> extraBits, ofBits - extraBits); /* 31 */
				पूर्ण अन्यथा अणु
					BIT_addBits(&blockStream, sequences[n].offset, ofBits); /* 31 */
				पूर्ण
				BIT_flushBits(&blockStream); /* (7)*/
			पूर्ण
		पूर्ण

		FSE_flushCState(&blockStream, &stateMatchLength);
		FSE_flushCState(&blockStream, &stateOffsetBits);
		FSE_flushCState(&blockStream, &stateLitLength);

		अणु
			माप_प्रकार स्थिर streamSize = BIT_बंदCStream(&blockStream);
			अगर (streamSize == 0)
				वापस ERROR(dstSize_tooSmall); /* not enough space */
			op += streamSize;
		पूर्ण
	पूर्ण
	वापस op - ostart;
पूर्ण

ZSTD_STATIC माप_प्रकार ZSTD_compressSequences(ZSTD_CCtx *zc, व्योम *dst, माप_प्रकार dstCapacity, माप_प्रकार srcSize)
अणु
	माप_प्रकार स्थिर cSize = ZSTD_compressSequences_पूर्णांकernal(zc, dst, dstCapacity);
	माप_प्रकार स्थिर minGain = ZSTD_minGain(srcSize);
	माप_प्रकार स्थिर maxCSize = srcSize - minGain;
	/* If the srcSize <= dstCapacity, then there is enough space to ग_लिखो a
	 * raw uncompressed block. Since we ran out of space, the block must not
	 * be compressible, so fall back to a raw uncompressed block.
	 */
	पूर्णांक स्थिर uncompressibleError = cSize == ERROR(dstSize_tooSmall) && srcSize <= dstCapacity;
	पूर्णांक i;

	अगर (ZSTD_isError(cSize) && !uncompressibleError)
		वापस cSize;
	अगर (cSize >= maxCSize || uncompressibleError) अणु
		zc->flagStaticHufTable = HUF_repeat_none;
		वापस 0;
	पूर्ण
	/* confirm repcodes */
	क्रम (i = 0; i < ZSTD_REP_NUM; i++)
		zc->rep[i] = zc->repToConfirm[i];
	वापस cSize;
पूर्ण

/*! ZSTD_storeSeq() :
	Store a sequence (literal length, literals, offset code and match length code) पूर्णांकo seqStore_t.
	`offsetCode` : distance to match, or 0 == repCode.
	`matchCode` : matchLength - MINMATCH
*/
ZSTD_STATIC व्योम ZSTD_storeSeq(seqStore_t *seqStorePtr, माप_प्रकार litLength, स्थिर व्योम *literals, U32 offsetCode, माप_प्रकार matchCode)
अणु
	/* copy Literals */
	ZSTD_wildcopy(seqStorePtr->lit, literals, litLength);
	seqStorePtr->lit += litLength;

	/* literal Length */
	अगर (litLength > 0xFFFF) अणु
		seqStorePtr->दीर्घLengthID = 1;
		seqStorePtr->दीर्घLengthPos = (U32)(seqStorePtr->sequences - seqStorePtr->sequencesStart);
	पूर्ण
	seqStorePtr->sequences[0].litLength = (U16)litLength;

	/* match offset */
	seqStorePtr->sequences[0].offset = offsetCode + 1;

	/* match Length */
	अगर (matchCode > 0xFFFF) अणु
		seqStorePtr->दीर्घLengthID = 2;
		seqStorePtr->दीर्घLengthPos = (U32)(seqStorePtr->sequences - seqStorePtr->sequencesStart);
	पूर्ण
	seqStorePtr->sequences[0].matchLength = (U16)matchCode;

	seqStorePtr->sequences++;
पूर्ण

/*-*************************************
*  Match length counter
***************************************/
अटल अचिन्हित ZSTD_NbCommonBytes(रेजिस्टर माप_प्रकार val)
अणु
	अगर (ZSTD_isLittleEndian()) अणु
		अगर (ZSTD_64bits()) अणु
			वापस (__builtin_ctzll((U64)val) >> 3);
		पूर्ण अन्यथा अणु /* 32 bits */
			वापस (__builtin_ctz((U32)val) >> 3);
		पूर्ण
	पूर्ण अन्यथा अणु /* Big Endian CPU */
		अगर (ZSTD_64bits()) अणु
			वापस (__builtin_clzll(val) >> 3);
		पूर्ण अन्यथा अणु /* 32 bits */
			वापस (__builtin_clz((U32)val) >> 3);
		पूर्ण
	पूर्ण
पूर्ण

अटल माप_प्रकार ZSTD_count(स्थिर BYTE *pIn, स्थिर BYTE *pMatch, स्थिर BYTE *स्थिर pInLimit)
अणु
	स्थिर BYTE *स्थिर pStart = pIn;
	स्थिर BYTE *स्थिर pInLoopLimit = pInLimit - (माप(माप_प्रकार) - 1);

	जबतक (pIn < pInLoopLimit) अणु
		माप_प्रकार स्थिर dअगरf = ZSTD_पढ़ोST(pMatch) ^ ZSTD_पढ़ोST(pIn);
		अगर (!dअगरf) अणु
			pIn += माप(माप_प्रकार);
			pMatch += माप(माप_प्रकार);
			जारी;
		पूर्ण
		pIn += ZSTD_NbCommonBytes(dअगरf);
		वापस (माप_प्रकार)(pIn - pStart);
	पूर्ण
	अगर (ZSTD_64bits())
		अगर ((pIn < (pInLimit - 3)) && (ZSTD_पढ़ो32(pMatch) == ZSTD_पढ़ो32(pIn))) अणु
			pIn += 4;
			pMatch += 4;
		पूर्ण
	अगर ((pIn < (pInLimit - 1)) && (ZSTD_पढ़ो16(pMatch) == ZSTD_पढ़ो16(pIn))) अणु
		pIn += 2;
		pMatch += 2;
	पूर्ण
	अगर ((pIn < pInLimit) && (*pMatch == *pIn))
		pIn++;
	वापस (माप_प्रकार)(pIn - pStart);
पूर्ण

/** ZSTD_count_2segments() :
*   can count match length with `ip` & `match` in 2 dअगरferent segments.
*   convention : on reaching mEnd, match count जारी starting from iStart
*/
अटल माप_प्रकार ZSTD_count_2segments(स्थिर BYTE *ip, स्थिर BYTE *match, स्थिर BYTE *iEnd, स्थिर BYTE *mEnd, स्थिर BYTE *iStart)
अणु
	स्थिर BYTE *स्थिर vEnd = MIN(ip + (mEnd - match), iEnd);
	माप_प्रकार स्थिर matchLength = ZSTD_count(ip, match, vEnd);
	अगर (match + matchLength != mEnd)
		वापस matchLength;
	वापस matchLength + ZSTD_count(ip + matchLength, iStart, iEnd);
पूर्ण

/*-*************************************
*  Hashes
***************************************/
अटल स्थिर U32 prime3bytes = 506832829U;
अटल U32 ZSTD_hash3(U32 u, U32 h) अणु वापस ((u << (32 - 24)) * prime3bytes) >> (32 - h); पूर्ण
ZSTD_STATIC माप_प्रकार ZSTD_hash3Ptr(स्थिर व्योम *ptr, U32 h) अणु वापस ZSTD_hash3(ZSTD_पढ़ोLE32(ptr), h); पूर्ण /* only in zstd_opt.h */

अटल स्थिर U32 prime4bytes = 2654435761U;
अटल U32 ZSTD_hash4(U32 u, U32 h) अणु वापस (u * prime4bytes) >> (32 - h); पूर्ण
अटल माप_प्रकार ZSTD_hash4Ptr(स्थिर व्योम *ptr, U32 h) अणु वापस ZSTD_hash4(ZSTD_पढ़ो32(ptr), h); पूर्ण

अटल स्थिर U64 prime5bytes = 889523592379ULL;
अटल माप_प्रकार ZSTD_hash5(U64 u, U32 h) अणु वापस (माप_प्रकार)(((u << (64 - 40)) * prime5bytes) >> (64 - h)); पूर्ण
अटल माप_प्रकार ZSTD_hash5Ptr(स्थिर व्योम *p, U32 h) अणु वापस ZSTD_hash5(ZSTD_पढ़ोLE64(p), h); पूर्ण

अटल स्थिर U64 prime6bytes = 227718039650203ULL;
अटल माप_प्रकार ZSTD_hash6(U64 u, U32 h) अणु वापस (माप_प्रकार)(((u << (64 - 48)) * prime6bytes) >> (64 - h)); पूर्ण
अटल माप_प्रकार ZSTD_hash6Ptr(स्थिर व्योम *p, U32 h) अणु वापस ZSTD_hash6(ZSTD_पढ़ोLE64(p), h); पूर्ण

अटल स्थिर U64 prime7bytes = 58295818150454627ULL;
अटल माप_प्रकार ZSTD_hash7(U64 u, U32 h) अणु वापस (माप_प्रकार)(((u << (64 - 56)) * prime7bytes) >> (64 - h)); पूर्ण
अटल माप_प्रकार ZSTD_hash7Ptr(स्थिर व्योम *p, U32 h) अणु वापस ZSTD_hash7(ZSTD_पढ़ोLE64(p), h); पूर्ण

अटल स्थिर U64 prime8bytes = 0xCF1BBCDCB7A56463ULL;
अटल माप_प्रकार ZSTD_hash8(U64 u, U32 h) अणु वापस (माप_प्रकार)(((u)*prime8bytes) >> (64 - h)); पूर्ण
अटल माप_प्रकार ZSTD_hash8Ptr(स्थिर व्योम *p, U32 h) अणु वापस ZSTD_hash8(ZSTD_पढ़ोLE64(p), h); पूर्ण

अटल माप_प्रकार ZSTD_hashPtr(स्थिर व्योम *p, U32 hBits, U32 mls)
अणु
	चयन (mls) अणु
	// हाल 3: वापस ZSTD_hash3Ptr(p, hBits);
	शेष:
	हाल 4: वापस ZSTD_hash4Ptr(p, hBits);
	हाल 5: वापस ZSTD_hash5Ptr(p, hBits);
	हाल 6: वापस ZSTD_hash6Ptr(p, hBits);
	हाल 7: वापस ZSTD_hash7Ptr(p, hBits);
	हाल 8: वापस ZSTD_hash8Ptr(p, hBits);
	पूर्ण
पूर्ण

/*-*************************************
*  Fast Scan
***************************************/
अटल व्योम ZSTD_fillHashTable(ZSTD_CCtx *zc, स्थिर व्योम *end, स्थिर U32 mls)
अणु
	U32 *स्थिर hashTable = zc->hashTable;
	U32 स्थिर hBits = zc->params.cParams.hashLog;
	स्थिर BYTE *स्थिर base = zc->base;
	स्थिर BYTE *ip = base + zc->nextToUpdate;
	स्थिर BYTE *स्थिर iend = ((स्थिर BYTE *)end) - HASH_READ_SIZE;
	स्थिर माप_प्रकार fastHashFillStep = 3;

	जबतक (ip <= iend) अणु
		hashTable[ZSTD_hashPtr(ip, hBits, mls)] = (U32)(ip - base);
		ip += fastHashFillStep;
	पूर्ण
पूर्ण

FORCE_INLINE
व्योम ZSTD_compressBlock_fast_generic(ZSTD_CCtx *cctx, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर U32 mls)
अणु
	U32 *स्थिर hashTable = cctx->hashTable;
	U32 स्थिर hBits = cctx->params.cParams.hashLog;
	seqStore_t *seqStorePtr = &(cctx->seqStore);
	स्थिर BYTE *स्थिर base = cctx->base;
	स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)src;
	स्थिर BYTE *ip = istart;
	स्थिर BYTE *anchor = istart;
	स्थिर U32 lowestIndex = cctx->dictLimit;
	स्थिर BYTE *स्थिर lowest = base + lowestIndex;
	स्थिर BYTE *स्थिर iend = istart + srcSize;
	स्थिर BYTE *स्थिर ilimit = iend - HASH_READ_SIZE;
	U32 offset_1 = cctx->rep[0], offset_2 = cctx->rep[1];
	U32 offsetSaved = 0;

	/* init */
	ip += (ip == lowest);
	अणु
		U32 स्थिर maxRep = (U32)(ip - lowest);
		अगर (offset_2 > maxRep)
			offsetSaved = offset_2, offset_2 = 0;
		अगर (offset_1 > maxRep)
			offsetSaved = offset_1, offset_1 = 0;
	पूर्ण

	/* Main Search Loop */
	जबतक (ip < ilimit) अणु /* < instead of <=, because repcode check at (ip+1) */
		माप_प्रकार mLength;
		माप_प्रकार स्थिर h = ZSTD_hashPtr(ip, hBits, mls);
		U32 स्थिर curr = (U32)(ip - base);
		U32 स्थिर matchIndex = hashTable[h];
		स्थिर BYTE *match = base + matchIndex;
		hashTable[h] = curr; /* update hash table */

		अगर ((offset_1 > 0) & (ZSTD_पढ़ो32(ip + 1 - offset_1) == ZSTD_पढ़ो32(ip + 1))) अणु
			mLength = ZSTD_count(ip + 1 + 4, ip + 1 + 4 - offset_1, iend) + 4;
			ip++;
			ZSTD_storeSeq(seqStorePtr, ip - anchor, anchor, 0, mLength - MINMATCH);
		पूर्ण अन्यथा अणु
			U32 offset;
			अगर ((matchIndex <= lowestIndex) || (ZSTD_पढ़ो32(match) != ZSTD_पढ़ो32(ip))) अणु
				ip += ((ip - anchor) >> g_searchStrength) + 1;
				जारी;
			पूर्ण
			mLength = ZSTD_count(ip + 4, match + 4, iend) + 4;
			offset = (U32)(ip - match);
			जबतक (((ip > anchor) & (match > lowest)) && (ip[-1] == match[-1])) अणु
				ip--;
				match--;
				mLength++;
			पूर्ण /* catch up */
			offset_2 = offset_1;
			offset_1 = offset;

			ZSTD_storeSeq(seqStorePtr, ip - anchor, anchor, offset + ZSTD_REP_MOVE, mLength - MINMATCH);
		पूर्ण

		/* match found */
		ip += mLength;
		anchor = ip;

		अगर (ip <= ilimit) अणु
			/* Fill Table */
			hashTable[ZSTD_hashPtr(base + curr + 2, hBits, mls)] = curr + 2; /* here because curr+2 could be > iend-8 */
			hashTable[ZSTD_hashPtr(ip - 2, hBits, mls)] = (U32)(ip - 2 - base);
			/* check immediate repcode */
			जबतक ((ip <= ilimit) && ((offset_2 > 0) & (ZSTD_पढ़ो32(ip) == ZSTD_पढ़ो32(ip - offset_2)))) अणु
				/* store sequence */
				माप_प्रकार स्थिर rLength = ZSTD_count(ip + 4, ip + 4 - offset_2, iend) + 4;
				अणु
					U32 स्थिर पंचांगpOff = offset_2;
					offset_2 = offset_1;
					offset_1 = पंचांगpOff;
				पूर्ण /* swap offset_2 <=> offset_1 */
				hashTable[ZSTD_hashPtr(ip, hBits, mls)] = (U32)(ip - base);
				ZSTD_storeSeq(seqStorePtr, 0, anchor, 0, rLength - MINMATCH);
				ip += rLength;
				anchor = ip;
				जारी; /* faster when present ... (?) */
			पूर्ण
		पूर्ण
	पूर्ण

	/* save reps क्रम next block */
	cctx->repToConfirm[0] = offset_1 ? offset_1 : offsetSaved;
	cctx->repToConfirm[1] = offset_2 ? offset_2 : offsetSaved;

	/* Last Literals */
	अणु
		माप_प्रकार स्थिर lastLLSize = iend - anchor;
		स_नकल(seqStorePtr->lit, anchor, lastLLSize);
		seqStorePtr->lit += lastLLSize;
	पूर्ण
पूर्ण

अटल व्योम ZSTD_compressBlock_fast(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	स्थिर U32 mls = ctx->params.cParams.searchLength;
	चयन (mls) अणु
	शेष: /* includes हाल 3 */
	हाल 4: ZSTD_compressBlock_fast_generic(ctx, src, srcSize, 4); वापस;
	हाल 5: ZSTD_compressBlock_fast_generic(ctx, src, srcSize, 5); वापस;
	हाल 6: ZSTD_compressBlock_fast_generic(ctx, src, srcSize, 6); वापस;
	हाल 7: ZSTD_compressBlock_fast_generic(ctx, src, srcSize, 7); वापस;
	पूर्ण
पूर्ण

अटल व्योम ZSTD_compressBlock_fast_extDict_generic(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर U32 mls)
अणु
	U32 *hashTable = ctx->hashTable;
	स्थिर U32 hBits = ctx->params.cParams.hashLog;
	seqStore_t *seqStorePtr = &(ctx->seqStore);
	स्थिर BYTE *स्थिर base = ctx->base;
	स्थिर BYTE *स्थिर dictBase = ctx->dictBase;
	स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)src;
	स्थिर BYTE *ip = istart;
	स्थिर BYTE *anchor = istart;
	स्थिर U32 lowestIndex = ctx->lowLimit;
	स्थिर BYTE *स्थिर dictStart = dictBase + lowestIndex;
	स्थिर U32 dictLimit = ctx->dictLimit;
	स्थिर BYTE *स्थिर lowPrefixPtr = base + dictLimit;
	स्थिर BYTE *स्थिर dictEnd = dictBase + dictLimit;
	स्थिर BYTE *स्थिर iend = istart + srcSize;
	स्थिर BYTE *स्थिर ilimit = iend - 8;
	U32 offset_1 = ctx->rep[0], offset_2 = ctx->rep[1];

	/* Search Loop */
	जबतक (ip < ilimit) अणु /* < instead of <=, because (ip+1) */
		स्थिर माप_प्रकार h = ZSTD_hashPtr(ip, hBits, mls);
		स्थिर U32 matchIndex = hashTable[h];
		स्थिर BYTE *matchBase = matchIndex < dictLimit ? dictBase : base;
		स्थिर BYTE *match = matchBase + matchIndex;
		स्थिर U32 curr = (U32)(ip - base);
		स्थिर U32 repIndex = curr + 1 - offset_1; /* offset_1 expected <= curr +1 */
		स्थिर BYTE *repBase = repIndex < dictLimit ? dictBase : base;
		स्थिर BYTE *repMatch = repBase + repIndex;
		माप_प्रकार mLength;
		hashTable[h] = curr; /* update hash table */

		अगर ((((U32)((dictLimit - 1) - repIndex) >= 3) /* पूर्णांकentional underflow */ & (repIndex > lowestIndex)) &&
		    (ZSTD_पढ़ो32(repMatch) == ZSTD_पढ़ो32(ip + 1))) अणु
			स्थिर BYTE *repMatchEnd = repIndex < dictLimit ? dictEnd : iend;
			mLength = ZSTD_count_2segments(ip + 1 + EQUAL_READ32, repMatch + EQUAL_READ32, iend, repMatchEnd, lowPrefixPtr) + EQUAL_READ32;
			ip++;
			ZSTD_storeSeq(seqStorePtr, ip - anchor, anchor, 0, mLength - MINMATCH);
		पूर्ण अन्यथा अणु
			अगर ((matchIndex < lowestIndex) || (ZSTD_पढ़ो32(match) != ZSTD_पढ़ो32(ip))) अणु
				ip += ((ip - anchor) >> g_searchStrength) + 1;
				जारी;
			पूर्ण
			अणु
				स्थिर BYTE *matchEnd = matchIndex < dictLimit ? dictEnd : iend;
				स्थिर BYTE *lowMatchPtr = matchIndex < dictLimit ? dictStart : lowPrefixPtr;
				U32 offset;
				mLength = ZSTD_count_2segments(ip + EQUAL_READ32, match + EQUAL_READ32, iend, matchEnd, lowPrefixPtr) + EQUAL_READ32;
				जबतक (((ip > anchor) & (match > lowMatchPtr)) && (ip[-1] == match[-1])) अणु
					ip--;
					match--;
					mLength++;
				पूर्ण /* catch up */
				offset = curr - matchIndex;
				offset_2 = offset_1;
				offset_1 = offset;
				ZSTD_storeSeq(seqStorePtr, ip - anchor, anchor, offset + ZSTD_REP_MOVE, mLength - MINMATCH);
			पूर्ण
		पूर्ण

		/* found a match : store it */
		ip += mLength;
		anchor = ip;

		अगर (ip <= ilimit) अणु
			/* Fill Table */
			hashTable[ZSTD_hashPtr(base + curr + 2, hBits, mls)] = curr + 2;
			hashTable[ZSTD_hashPtr(ip - 2, hBits, mls)] = (U32)(ip - 2 - base);
			/* check immediate repcode */
			जबतक (ip <= ilimit) अणु
				U32 स्थिर curr2 = (U32)(ip - base);
				U32 स्थिर repIndex2 = curr2 - offset_2;
				स्थिर BYTE *repMatch2 = repIndex2 < dictLimit ? dictBase + repIndex2 : base + repIndex2;
				अगर ((((U32)((dictLimit - 1) - repIndex2) >= 3) & (repIndex2 > lowestIndex)) /* पूर्णांकentional overflow */
				    && (ZSTD_पढ़ो32(repMatch2) == ZSTD_पढ़ो32(ip))) अणु
					स्थिर BYTE *स्थिर repEnd2 = repIndex2 < dictLimit ? dictEnd : iend;
					माप_प्रकार repLength2 =
					    ZSTD_count_2segments(ip + EQUAL_READ32, repMatch2 + EQUAL_READ32, iend, repEnd2, lowPrefixPtr) + EQUAL_READ32;
					U32 पंचांगpOffset = offset_2;
					offset_2 = offset_1;
					offset_1 = पंचांगpOffset; /* swap offset_2 <=> offset_1 */
					ZSTD_storeSeq(seqStorePtr, 0, anchor, 0, repLength2 - MINMATCH);
					hashTable[ZSTD_hashPtr(ip, hBits, mls)] = curr2;
					ip += repLength2;
					anchor = ip;
					जारी;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* save reps क्रम next block */
	ctx->repToConfirm[0] = offset_1;
	ctx->repToConfirm[1] = offset_2;

	/* Last Literals */
	अणु
		माप_प्रकार स्थिर lastLLSize = iend - anchor;
		स_नकल(seqStorePtr->lit, anchor, lastLLSize);
		seqStorePtr->lit += lastLLSize;
	पूर्ण
पूर्ण

अटल व्योम ZSTD_compressBlock_fast_extDict(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	U32 स्थिर mls = ctx->params.cParams.searchLength;
	चयन (mls) अणु
	शेष: /* includes हाल 3 */
	हाल 4: ZSTD_compressBlock_fast_extDict_generic(ctx, src, srcSize, 4); वापस;
	हाल 5: ZSTD_compressBlock_fast_extDict_generic(ctx, src, srcSize, 5); वापस;
	हाल 6: ZSTD_compressBlock_fast_extDict_generic(ctx, src, srcSize, 6); वापस;
	हाल 7: ZSTD_compressBlock_fast_extDict_generic(ctx, src, srcSize, 7); वापस;
	पूर्ण
पूर्ण

/*-*************************************
*  Double Fast
***************************************/
अटल व्योम ZSTD_fillDoubleHashTable(ZSTD_CCtx *cctx, स्थिर व्योम *end, स्थिर U32 mls)
अणु
	U32 *स्थिर hashLarge = cctx->hashTable;
	U32 स्थिर hBitsL = cctx->params.cParams.hashLog;
	U32 *स्थिर hashSmall = cctx->chainTable;
	U32 स्थिर hBitsS = cctx->params.cParams.chainLog;
	स्थिर BYTE *स्थिर base = cctx->base;
	स्थिर BYTE *ip = base + cctx->nextToUpdate;
	स्थिर BYTE *स्थिर iend = ((स्थिर BYTE *)end) - HASH_READ_SIZE;
	स्थिर माप_प्रकार fastHashFillStep = 3;

	जबतक (ip <= iend) अणु
		hashSmall[ZSTD_hashPtr(ip, hBitsS, mls)] = (U32)(ip - base);
		hashLarge[ZSTD_hashPtr(ip, hBitsL, 8)] = (U32)(ip - base);
		ip += fastHashFillStep;
	पूर्ण
पूर्ण

FORCE_INLINE
व्योम ZSTD_compressBlock_द्विगुनFast_generic(ZSTD_CCtx *cctx, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर U32 mls)
अणु
	U32 *स्थिर hashLong = cctx->hashTable;
	स्थिर U32 hBitsL = cctx->params.cParams.hashLog;
	U32 *स्थिर hashSmall = cctx->chainTable;
	स्थिर U32 hBitsS = cctx->params.cParams.chainLog;
	seqStore_t *seqStorePtr = &(cctx->seqStore);
	स्थिर BYTE *स्थिर base = cctx->base;
	स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)src;
	स्थिर BYTE *ip = istart;
	स्थिर BYTE *anchor = istart;
	स्थिर U32 lowestIndex = cctx->dictLimit;
	स्थिर BYTE *स्थिर lowest = base + lowestIndex;
	स्थिर BYTE *स्थिर iend = istart + srcSize;
	स्थिर BYTE *स्थिर ilimit = iend - HASH_READ_SIZE;
	U32 offset_1 = cctx->rep[0], offset_2 = cctx->rep[1];
	U32 offsetSaved = 0;

	/* init */
	ip += (ip == lowest);
	अणु
		U32 स्थिर maxRep = (U32)(ip - lowest);
		अगर (offset_2 > maxRep)
			offsetSaved = offset_2, offset_2 = 0;
		अगर (offset_1 > maxRep)
			offsetSaved = offset_1, offset_1 = 0;
	पूर्ण

	/* Main Search Loop */
	जबतक (ip < ilimit) अणु /* < instead of <=, because repcode check at (ip+1) */
		माप_प्रकार mLength;
		माप_प्रकार स्थिर h2 = ZSTD_hashPtr(ip, hBitsL, 8);
		माप_प्रकार स्थिर h = ZSTD_hashPtr(ip, hBitsS, mls);
		U32 स्थिर curr = (U32)(ip - base);
		U32 स्थिर matchIndexL = hashLong[h2];
		U32 स्थिर matchIndexS = hashSmall[h];
		स्थिर BYTE *matchLong = base + matchIndexL;
		स्थिर BYTE *match = base + matchIndexS;
		hashLong[h2] = hashSmall[h] = curr; /* update hash tables */

		अगर ((offset_1 > 0) & (ZSTD_पढ़ो32(ip + 1 - offset_1) == ZSTD_पढ़ो32(ip + 1))) अणु /* note : by स्थिरruction, offset_1 <= curr */
			mLength = ZSTD_count(ip + 1 + 4, ip + 1 + 4 - offset_1, iend) + 4;
			ip++;
			ZSTD_storeSeq(seqStorePtr, ip - anchor, anchor, 0, mLength - MINMATCH);
		पूर्ण अन्यथा अणु
			U32 offset;
			अगर ((matchIndexL > lowestIndex) && (ZSTD_पढ़ो64(matchLong) == ZSTD_पढ़ो64(ip))) अणु
				mLength = ZSTD_count(ip + 8, matchLong + 8, iend) + 8;
				offset = (U32)(ip - matchLong);
				जबतक (((ip > anchor) & (matchLong > lowest)) && (ip[-1] == matchLong[-1])) अणु
					ip--;
					matchLong--;
					mLength++;
				पूर्ण /* catch up */
			पूर्ण अन्यथा अगर ((matchIndexS > lowestIndex) && (ZSTD_पढ़ो32(match) == ZSTD_पढ़ो32(ip))) अणु
				माप_प्रकार स्थिर h3 = ZSTD_hashPtr(ip + 1, hBitsL, 8);
				U32 स्थिर matchIndex3 = hashLong[h3];
				स्थिर BYTE *match3 = base + matchIndex3;
				hashLong[h3] = curr + 1;
				अगर ((matchIndex3 > lowestIndex) && (ZSTD_पढ़ो64(match3) == ZSTD_पढ़ो64(ip + 1))) अणु
					mLength = ZSTD_count(ip + 9, match3 + 8, iend) + 8;
					ip++;
					offset = (U32)(ip - match3);
					जबतक (((ip > anchor) & (match3 > lowest)) && (ip[-1] == match3[-1])) अणु
						ip--;
						match3--;
						mLength++;
					पूर्ण /* catch up */
				पूर्ण अन्यथा अणु
					mLength = ZSTD_count(ip + 4, match + 4, iend) + 4;
					offset = (U32)(ip - match);
					जबतक (((ip > anchor) & (match > lowest)) && (ip[-1] == match[-1])) अणु
						ip--;
						match--;
						mLength++;
					पूर्ण /* catch up */
				पूर्ण
			पूर्ण अन्यथा अणु
				ip += ((ip - anchor) >> g_searchStrength) + 1;
				जारी;
			पूर्ण

			offset_2 = offset_1;
			offset_1 = offset;

			ZSTD_storeSeq(seqStorePtr, ip - anchor, anchor, offset + ZSTD_REP_MOVE, mLength - MINMATCH);
		पूर्ण

		/* match found */
		ip += mLength;
		anchor = ip;

		अगर (ip <= ilimit) अणु
			/* Fill Table */
			hashLong[ZSTD_hashPtr(base + curr + 2, hBitsL, 8)] = hashSmall[ZSTD_hashPtr(base + curr + 2, hBitsS, mls)] =
			    curr + 2; /* here because curr+2 could be > iend-8 */
			hashLong[ZSTD_hashPtr(ip - 2, hBitsL, 8)] = hashSmall[ZSTD_hashPtr(ip - 2, hBitsS, mls)] = (U32)(ip - 2 - base);

			/* check immediate repcode */
			जबतक ((ip <= ilimit) && ((offset_2 > 0) & (ZSTD_पढ़ो32(ip) == ZSTD_पढ़ो32(ip - offset_2)))) अणु
				/* store sequence */
				माप_प्रकार स्थिर rLength = ZSTD_count(ip + 4, ip + 4 - offset_2, iend) + 4;
				अणु
					U32 स्थिर पंचांगpOff = offset_2;
					offset_2 = offset_1;
					offset_1 = पंचांगpOff;
				पूर्ण /* swap offset_2 <=> offset_1 */
				hashSmall[ZSTD_hashPtr(ip, hBitsS, mls)] = (U32)(ip - base);
				hashLong[ZSTD_hashPtr(ip, hBitsL, 8)] = (U32)(ip - base);
				ZSTD_storeSeq(seqStorePtr, 0, anchor, 0, rLength - MINMATCH);
				ip += rLength;
				anchor = ip;
				जारी; /* faster when present ... (?) */
			पूर्ण
		पूर्ण
	पूर्ण

	/* save reps क्रम next block */
	cctx->repToConfirm[0] = offset_1 ? offset_1 : offsetSaved;
	cctx->repToConfirm[1] = offset_2 ? offset_2 : offsetSaved;

	/* Last Literals */
	अणु
		माप_प्रकार स्थिर lastLLSize = iend - anchor;
		स_नकल(seqStorePtr->lit, anchor, lastLLSize);
		seqStorePtr->lit += lastLLSize;
	पूर्ण
पूर्ण

अटल व्योम ZSTD_compressBlock_द्विगुनFast(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	स्थिर U32 mls = ctx->params.cParams.searchLength;
	चयन (mls) अणु
	शेष: /* includes हाल 3 */
	हाल 4: ZSTD_compressBlock_द्विगुनFast_generic(ctx, src, srcSize, 4); वापस;
	हाल 5: ZSTD_compressBlock_द्विगुनFast_generic(ctx, src, srcSize, 5); वापस;
	हाल 6: ZSTD_compressBlock_द्विगुनFast_generic(ctx, src, srcSize, 6); वापस;
	हाल 7: ZSTD_compressBlock_द्विगुनFast_generic(ctx, src, srcSize, 7); वापस;
	पूर्ण
पूर्ण

अटल व्योम ZSTD_compressBlock_द्विगुनFast_extDict_generic(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर U32 mls)
अणु
	U32 *स्थिर hashLong = ctx->hashTable;
	U32 स्थिर hBitsL = ctx->params.cParams.hashLog;
	U32 *स्थिर hashSmall = ctx->chainTable;
	U32 स्थिर hBitsS = ctx->params.cParams.chainLog;
	seqStore_t *seqStorePtr = &(ctx->seqStore);
	स्थिर BYTE *स्थिर base = ctx->base;
	स्थिर BYTE *स्थिर dictBase = ctx->dictBase;
	स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)src;
	स्थिर BYTE *ip = istart;
	स्थिर BYTE *anchor = istart;
	स्थिर U32 lowestIndex = ctx->lowLimit;
	स्थिर BYTE *स्थिर dictStart = dictBase + lowestIndex;
	स्थिर U32 dictLimit = ctx->dictLimit;
	स्थिर BYTE *स्थिर lowPrefixPtr = base + dictLimit;
	स्थिर BYTE *स्थिर dictEnd = dictBase + dictLimit;
	स्थिर BYTE *स्थिर iend = istart + srcSize;
	स्थिर BYTE *स्थिर ilimit = iend - 8;
	U32 offset_1 = ctx->rep[0], offset_2 = ctx->rep[1];

	/* Search Loop */
	जबतक (ip < ilimit) अणु /* < instead of <=, because (ip+1) */
		स्थिर माप_प्रकार hSmall = ZSTD_hashPtr(ip, hBitsS, mls);
		स्थिर U32 matchIndex = hashSmall[hSmall];
		स्थिर BYTE *matchBase = matchIndex < dictLimit ? dictBase : base;
		स्थिर BYTE *match = matchBase + matchIndex;

		स्थिर माप_प्रकार hLong = ZSTD_hashPtr(ip, hBitsL, 8);
		स्थिर U32 matchLongIndex = hashLong[hLong];
		स्थिर BYTE *matchLongBase = matchLongIndex < dictLimit ? dictBase : base;
		स्थिर BYTE *matchLong = matchLongBase + matchLongIndex;

		स्थिर U32 curr = (U32)(ip - base);
		स्थिर U32 repIndex = curr + 1 - offset_1; /* offset_1 expected <= curr +1 */
		स्थिर BYTE *repBase = repIndex < dictLimit ? dictBase : base;
		स्थिर BYTE *repMatch = repBase + repIndex;
		माप_प्रकार mLength;
		hashSmall[hSmall] = hashLong[hLong] = curr; /* update hash table */

		अगर ((((U32)((dictLimit - 1) - repIndex) >= 3) /* पूर्णांकentional underflow */ & (repIndex > lowestIndex)) &&
		    (ZSTD_पढ़ो32(repMatch) == ZSTD_पढ़ो32(ip + 1))) अणु
			स्थिर BYTE *repMatchEnd = repIndex < dictLimit ? dictEnd : iend;
			mLength = ZSTD_count_2segments(ip + 1 + 4, repMatch + 4, iend, repMatchEnd, lowPrefixPtr) + 4;
			ip++;
			ZSTD_storeSeq(seqStorePtr, ip - anchor, anchor, 0, mLength - MINMATCH);
		पूर्ण अन्यथा अणु
			अगर ((matchLongIndex > lowestIndex) && (ZSTD_पढ़ो64(matchLong) == ZSTD_पढ़ो64(ip))) अणु
				स्थिर BYTE *matchEnd = matchLongIndex < dictLimit ? dictEnd : iend;
				स्थिर BYTE *lowMatchPtr = matchLongIndex < dictLimit ? dictStart : lowPrefixPtr;
				U32 offset;
				mLength = ZSTD_count_2segments(ip + 8, matchLong + 8, iend, matchEnd, lowPrefixPtr) + 8;
				offset = curr - matchLongIndex;
				जबतक (((ip > anchor) & (matchLong > lowMatchPtr)) && (ip[-1] == matchLong[-1])) अणु
					ip--;
					matchLong--;
					mLength++;
				पूर्ण /* catch up */
				offset_2 = offset_1;
				offset_1 = offset;
				ZSTD_storeSeq(seqStorePtr, ip - anchor, anchor, offset + ZSTD_REP_MOVE, mLength - MINMATCH);

			पूर्ण अन्यथा अगर ((matchIndex > lowestIndex) && (ZSTD_पढ़ो32(match) == ZSTD_पढ़ो32(ip))) अणु
				माप_प्रकार स्थिर h3 = ZSTD_hashPtr(ip + 1, hBitsL, 8);
				U32 स्थिर matchIndex3 = hashLong[h3];
				स्थिर BYTE *स्थिर match3Base = matchIndex3 < dictLimit ? dictBase : base;
				स्थिर BYTE *match3 = match3Base + matchIndex3;
				U32 offset;
				hashLong[h3] = curr + 1;
				अगर ((matchIndex3 > lowestIndex) && (ZSTD_पढ़ो64(match3) == ZSTD_पढ़ो64(ip + 1))) अणु
					स्थिर BYTE *matchEnd = matchIndex3 < dictLimit ? dictEnd : iend;
					स्थिर BYTE *lowMatchPtr = matchIndex3 < dictLimit ? dictStart : lowPrefixPtr;
					mLength = ZSTD_count_2segments(ip + 9, match3 + 8, iend, matchEnd, lowPrefixPtr) + 8;
					ip++;
					offset = curr + 1 - matchIndex3;
					जबतक (((ip > anchor) & (match3 > lowMatchPtr)) && (ip[-1] == match3[-1])) अणु
						ip--;
						match3--;
						mLength++;
					पूर्ण /* catch up */
				पूर्ण अन्यथा अणु
					स्थिर BYTE *matchEnd = matchIndex < dictLimit ? dictEnd : iend;
					स्थिर BYTE *lowMatchPtr = matchIndex < dictLimit ? dictStart : lowPrefixPtr;
					mLength = ZSTD_count_2segments(ip + 4, match + 4, iend, matchEnd, lowPrefixPtr) + 4;
					offset = curr - matchIndex;
					जबतक (((ip > anchor) & (match > lowMatchPtr)) && (ip[-1] == match[-1])) अणु
						ip--;
						match--;
						mLength++;
					पूर्ण /* catch up */
				पूर्ण
				offset_2 = offset_1;
				offset_1 = offset;
				ZSTD_storeSeq(seqStorePtr, ip - anchor, anchor, offset + ZSTD_REP_MOVE, mLength - MINMATCH);

			पूर्ण अन्यथा अणु
				ip += ((ip - anchor) >> g_searchStrength) + 1;
				जारी;
			पूर्ण
		पूर्ण

		/* found a match : store it */
		ip += mLength;
		anchor = ip;

		अगर (ip <= ilimit) अणु
			/* Fill Table */
			hashSmall[ZSTD_hashPtr(base + curr + 2, hBitsS, mls)] = curr + 2;
			hashLong[ZSTD_hashPtr(base + curr + 2, hBitsL, 8)] = curr + 2;
			hashSmall[ZSTD_hashPtr(ip - 2, hBitsS, mls)] = (U32)(ip - 2 - base);
			hashLong[ZSTD_hashPtr(ip - 2, hBitsL, 8)] = (U32)(ip - 2 - base);
			/* check immediate repcode */
			जबतक (ip <= ilimit) अणु
				U32 स्थिर curr2 = (U32)(ip - base);
				U32 स्थिर repIndex2 = curr2 - offset_2;
				स्थिर BYTE *repMatch2 = repIndex2 < dictLimit ? dictBase + repIndex2 : base + repIndex2;
				अगर ((((U32)((dictLimit - 1) - repIndex2) >= 3) & (repIndex2 > lowestIndex)) /* पूर्णांकentional overflow */
				    && (ZSTD_पढ़ो32(repMatch2) == ZSTD_पढ़ो32(ip))) अणु
					स्थिर BYTE *स्थिर repEnd2 = repIndex2 < dictLimit ? dictEnd : iend;
					माप_प्रकार स्थिर repLength2 =
					    ZSTD_count_2segments(ip + EQUAL_READ32, repMatch2 + EQUAL_READ32, iend, repEnd2, lowPrefixPtr) + EQUAL_READ32;
					U32 पंचांगpOffset = offset_2;
					offset_2 = offset_1;
					offset_1 = पंचांगpOffset; /* swap offset_2 <=> offset_1 */
					ZSTD_storeSeq(seqStorePtr, 0, anchor, 0, repLength2 - MINMATCH);
					hashSmall[ZSTD_hashPtr(ip, hBitsS, mls)] = curr2;
					hashLong[ZSTD_hashPtr(ip, hBitsL, 8)] = curr2;
					ip += repLength2;
					anchor = ip;
					जारी;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* save reps क्रम next block */
	ctx->repToConfirm[0] = offset_1;
	ctx->repToConfirm[1] = offset_2;

	/* Last Literals */
	अणु
		माप_प्रकार स्थिर lastLLSize = iend - anchor;
		स_नकल(seqStorePtr->lit, anchor, lastLLSize);
		seqStorePtr->lit += lastLLSize;
	पूर्ण
पूर्ण

अटल व्योम ZSTD_compressBlock_द्विगुनFast_extDict(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	U32 स्थिर mls = ctx->params.cParams.searchLength;
	चयन (mls) अणु
	शेष: /* includes हाल 3 */
	हाल 4: ZSTD_compressBlock_द्विगुनFast_extDict_generic(ctx, src, srcSize, 4); वापस;
	हाल 5: ZSTD_compressBlock_द्विगुनFast_extDict_generic(ctx, src, srcSize, 5); वापस;
	हाल 6: ZSTD_compressBlock_द्विगुनFast_extDict_generic(ctx, src, srcSize, 6); वापस;
	हाल 7: ZSTD_compressBlock_द्विगुनFast_extDict_generic(ctx, src, srcSize, 7); वापस;
	पूर्ण
पूर्ण

/*-*************************************
*  Binary Tree search
***************************************/
/** ZSTD_insertBt1() : add one or multiple positions to tree.
*   ip : assumed <= iend-8 .
*   @वापस : nb of positions added */
अटल U32 ZSTD_insertBt1(ZSTD_CCtx *zc, स्थिर BYTE *स्थिर ip, स्थिर U32 mls, स्थिर BYTE *स्थिर iend, U32 nbCompares, U32 extDict)
अणु
	U32 *स्थिर hashTable = zc->hashTable;
	U32 स्थिर hashLog = zc->params.cParams.hashLog;
	माप_प्रकार स्थिर h = ZSTD_hashPtr(ip, hashLog, mls);
	U32 *स्थिर bt = zc->chainTable;
	U32 स्थिर btLog = zc->params.cParams.chainLog - 1;
	U32 स्थिर btMask = (1 << btLog) - 1;
	U32 matchIndex = hashTable[h];
	माप_प्रकार commonLengthSmaller = 0, commonLengthLarger = 0;
	स्थिर BYTE *स्थिर base = zc->base;
	स्थिर BYTE *स्थिर dictBase = zc->dictBase;
	स्थिर U32 dictLimit = zc->dictLimit;
	स्थिर BYTE *स्थिर dictEnd = dictBase + dictLimit;
	स्थिर BYTE *स्थिर prefixStart = base + dictLimit;
	स्थिर BYTE *match;
	स्थिर U32 curr = (U32)(ip - base);
	स्थिर U32 btLow = btMask >= curr ? 0 : curr - btMask;
	U32 *smallerPtr = bt + 2 * (curr & btMask);
	U32 *largerPtr = smallerPtr + 1;
	U32 dummy32; /* to be nullअगरied at the end */
	U32 स्थिर winकरोwLow = zc->lowLimit;
	U32 matchEndIdx = curr + 8;
	माप_प्रकार bestLength = 8;

	hashTable[h] = curr; /* Update Hash Table */

	जबतक (nbCompares-- && (matchIndex > winकरोwLow)) अणु
		U32 *स्थिर nextPtr = bt + 2 * (matchIndex & btMask);
		माप_प्रकार matchLength = MIN(commonLengthSmaller, commonLengthLarger); /* guaranteed minimum nb of common bytes */

		अगर ((!extDict) || (matchIndex + matchLength >= dictLimit)) अणु
			match = base + matchIndex;
			अगर (match[matchLength] == ip[matchLength])
				matchLength += ZSTD_count(ip + matchLength + 1, match + matchLength + 1, iend) + 1;
		पूर्ण अन्यथा अणु
			match = dictBase + matchIndex;
			matchLength += ZSTD_count_2segments(ip + matchLength, match + matchLength, iend, dictEnd, prefixStart);
			अगर (matchIndex + matchLength >= dictLimit)
				match = base + matchIndex; /* to prepare क्रम next usage of match[matchLength] */
		पूर्ण

		अगर (matchLength > bestLength) अणु
			bestLength = matchLength;
			अगर (matchLength > matchEndIdx - matchIndex)
				matchEndIdx = matchIndex + (U32)matchLength;
		पूर्ण

		अगर (ip + matchLength == iend) /* equal : no way to know अगर inf or sup */
			अवरोध;		      /* drop , to guarantee consistency ; miss a bit of compression, but other solutions can corrupt the tree */

		अगर (match[matchLength] < ip[matchLength]) अणु /* necessarily within correct buffer */
			/* match is smaller than curr */
			*smallerPtr = matchIndex;	  /* update smaller idx */
			commonLengthSmaller = matchLength; /* all smaller will now have at least this guaranteed common length */
			अगर (matchIndex <= btLow) अणु
				smallerPtr = &dummy32;
				अवरोध;
			पूर्ण			  /* beyond tree size, stop the search */
			smallerPtr = nextPtr + 1; /* new "smaller" => larger of match */
			matchIndex = nextPtr[1];  /* new matchIndex larger than previous (बंदr to curr) */
		पूर्ण अन्यथा अणु
			/* match is larger than curr */
			*largerPtr = matchIndex;
			commonLengthLarger = matchLength;
			अगर (matchIndex <= btLow) अणु
				largerPtr = &dummy32;
				अवरोध;
			पूर्ण /* beyond tree size, stop the search */
			largerPtr = nextPtr;
			matchIndex = nextPtr[0];
		पूर्ण
	पूर्ण

	*smallerPtr = *largerPtr = 0;
	अगर (bestLength > 384)
		वापस MIN(192, (U32)(bestLength - 384)); /* speed optimization */
	अगर (matchEndIdx > curr + 8)
		वापस matchEndIdx - curr - 8;
	वापस 1;
पूर्ण

अटल माप_प्रकार ZSTD_insertBtAndFindBestMatch(ZSTD_CCtx *zc, स्थिर BYTE *स्थिर ip, स्थिर BYTE *स्थिर iend, माप_प्रकार *offsetPtr, U32 nbCompares, स्थिर U32 mls,
					    U32 extDict)
अणु
	U32 *स्थिर hashTable = zc->hashTable;
	U32 स्थिर hashLog = zc->params.cParams.hashLog;
	माप_प्रकार स्थिर h = ZSTD_hashPtr(ip, hashLog, mls);
	U32 *स्थिर bt = zc->chainTable;
	U32 स्थिर btLog = zc->params.cParams.chainLog - 1;
	U32 स्थिर btMask = (1 << btLog) - 1;
	U32 matchIndex = hashTable[h];
	माप_प्रकार commonLengthSmaller = 0, commonLengthLarger = 0;
	स्थिर BYTE *स्थिर base = zc->base;
	स्थिर BYTE *स्थिर dictBase = zc->dictBase;
	स्थिर U32 dictLimit = zc->dictLimit;
	स्थिर BYTE *स्थिर dictEnd = dictBase + dictLimit;
	स्थिर BYTE *स्थिर prefixStart = base + dictLimit;
	स्थिर U32 curr = (U32)(ip - base);
	स्थिर U32 btLow = btMask >= curr ? 0 : curr - btMask;
	स्थिर U32 winकरोwLow = zc->lowLimit;
	U32 *smallerPtr = bt + 2 * (curr & btMask);
	U32 *largerPtr = bt + 2 * (curr & btMask) + 1;
	U32 matchEndIdx = curr + 8;
	U32 dummy32; /* to be nullअगरied at the end */
	माप_प्रकार bestLength = 0;

	hashTable[h] = curr; /* Update Hash Table */

	जबतक (nbCompares-- && (matchIndex > winकरोwLow)) अणु
		U32 *स्थिर nextPtr = bt + 2 * (matchIndex & btMask);
		माप_प्रकार matchLength = MIN(commonLengthSmaller, commonLengthLarger); /* guaranteed minimum nb of common bytes */
		स्थिर BYTE *match;

		अगर ((!extDict) || (matchIndex + matchLength >= dictLimit)) अणु
			match = base + matchIndex;
			अगर (match[matchLength] == ip[matchLength])
				matchLength += ZSTD_count(ip + matchLength + 1, match + matchLength + 1, iend) + 1;
		पूर्ण अन्यथा अणु
			match = dictBase + matchIndex;
			matchLength += ZSTD_count_2segments(ip + matchLength, match + matchLength, iend, dictEnd, prefixStart);
			अगर (matchIndex + matchLength >= dictLimit)
				match = base + matchIndex; /* to prepare क्रम next usage of match[matchLength] */
		पूर्ण

		अगर (matchLength > bestLength) अणु
			अगर (matchLength > matchEndIdx - matchIndex)
				matchEndIdx = matchIndex + (U32)matchLength;
			अगर ((4 * (पूर्णांक)(matchLength - bestLength)) > (पूर्णांक)(ZSTD_highbit32(curr - matchIndex + 1) - ZSTD_highbit32((U32)offsetPtr[0] + 1)))
				bestLength = matchLength, *offsetPtr = ZSTD_REP_MOVE + curr - matchIndex;
			अगर (ip + matchLength == iend) /* equal : no way to know अगर inf or sup */
				अवरोध;		      /* drop, to guarantee consistency (miss a little bit of compression) */
		पूर्ण

		अगर (match[matchLength] < ip[matchLength]) अणु
			/* match is smaller than curr */
			*smallerPtr = matchIndex;	  /* update smaller idx */
			commonLengthSmaller = matchLength; /* all smaller will now have at least this guaranteed common length */
			अगर (matchIndex <= btLow) अणु
				smallerPtr = &dummy32;
				अवरोध;
			पूर्ण			  /* beyond tree size, stop the search */
			smallerPtr = nextPtr + 1; /* new "smaller" => larger of match */
			matchIndex = nextPtr[1];  /* new matchIndex larger than previous (बंदr to curr) */
		पूर्ण अन्यथा अणु
			/* match is larger than curr */
			*largerPtr = matchIndex;
			commonLengthLarger = matchLength;
			अगर (matchIndex <= btLow) अणु
				largerPtr = &dummy32;
				अवरोध;
			पूर्ण /* beyond tree size, stop the search */
			largerPtr = nextPtr;
			matchIndex = nextPtr[0];
		पूर्ण
	पूर्ण

	*smallerPtr = *largerPtr = 0;

	zc->nextToUpdate = (matchEndIdx > curr + 8) ? matchEndIdx - 8 : curr + 1;
	वापस bestLength;
पूर्ण

अटल व्योम ZSTD_updateTree(ZSTD_CCtx *zc, स्थिर BYTE *स्थिर ip, स्थिर BYTE *स्थिर iend, स्थिर U32 nbCompares, स्थिर U32 mls)
अणु
	स्थिर BYTE *स्थिर base = zc->base;
	स्थिर U32 target = (U32)(ip - base);
	U32 idx = zc->nextToUpdate;

	जबतक (idx < target)
		idx += ZSTD_insertBt1(zc, base + idx, mls, iend, nbCompares, 0);
पूर्ण

/** ZSTD_BtFindBestMatch() : Tree updater, providing best match */
अटल माप_प्रकार ZSTD_BtFindBestMatch(ZSTD_CCtx *zc, स्थिर BYTE *स्थिर ip, स्थिर BYTE *स्थिर iLimit, माप_प्रकार *offsetPtr, स्थिर U32 maxNbAttempts, स्थिर U32 mls)
अणु
	अगर (ip < zc->base + zc->nextToUpdate)
		वापस 0; /* skipped area */
	ZSTD_updateTree(zc, ip, iLimit, maxNbAttempts, mls);
	वापस ZSTD_insertBtAndFindBestMatch(zc, ip, iLimit, offsetPtr, maxNbAttempts, mls, 0);
पूर्ण

अटल माप_प्रकार ZSTD_BtFindBestMatch_selectMLS(ZSTD_CCtx *zc, /* Index table will be updated */
					     स्थिर BYTE *ip, स्थिर BYTE *स्थिर iLimit, माप_प्रकार *offsetPtr, स्थिर U32 maxNbAttempts, स्थिर U32 matchLengthSearch)
अणु
	चयन (matchLengthSearch) अणु
	शेष: /* includes हाल 3 */
	हाल 4: वापस ZSTD_BtFindBestMatch(zc, ip, iLimit, offsetPtr, maxNbAttempts, 4);
	हाल 5: वापस ZSTD_BtFindBestMatch(zc, ip, iLimit, offsetPtr, maxNbAttempts, 5);
	हाल 7:
	हाल 6: वापस ZSTD_BtFindBestMatch(zc, ip, iLimit, offsetPtr, maxNbAttempts, 6);
	पूर्ण
पूर्ण

अटल व्योम ZSTD_updateTree_extDict(ZSTD_CCtx *zc, स्थिर BYTE *स्थिर ip, स्थिर BYTE *स्थिर iend, स्थिर U32 nbCompares, स्थिर U32 mls)
अणु
	स्थिर BYTE *स्थिर base = zc->base;
	स्थिर U32 target = (U32)(ip - base);
	U32 idx = zc->nextToUpdate;

	जबतक (idx < target)
		idx += ZSTD_insertBt1(zc, base + idx, mls, iend, nbCompares, 1);
पूर्ण

/** Tree updater, providing best match */
अटल माप_प्रकार ZSTD_BtFindBestMatch_extDict(ZSTD_CCtx *zc, स्थिर BYTE *स्थिर ip, स्थिर BYTE *स्थिर iLimit, माप_प्रकार *offsetPtr, स्थिर U32 maxNbAttempts,
					   स्थिर U32 mls)
अणु
	अगर (ip < zc->base + zc->nextToUpdate)
		वापस 0; /* skipped area */
	ZSTD_updateTree_extDict(zc, ip, iLimit, maxNbAttempts, mls);
	वापस ZSTD_insertBtAndFindBestMatch(zc, ip, iLimit, offsetPtr, maxNbAttempts, mls, 1);
पूर्ण

अटल माप_प्रकार ZSTD_BtFindBestMatch_selectMLS_extDict(ZSTD_CCtx *zc, /* Index table will be updated */
						     स्थिर BYTE *ip, स्थिर BYTE *स्थिर iLimit, माप_प्रकार *offsetPtr, स्थिर U32 maxNbAttempts,
						     स्थिर U32 matchLengthSearch)
अणु
	चयन (matchLengthSearch) अणु
	शेष: /* includes हाल 3 */
	हाल 4: वापस ZSTD_BtFindBestMatch_extDict(zc, ip, iLimit, offsetPtr, maxNbAttempts, 4);
	हाल 5: वापस ZSTD_BtFindBestMatch_extDict(zc, ip, iLimit, offsetPtr, maxNbAttempts, 5);
	हाल 7:
	हाल 6: वापस ZSTD_BtFindBestMatch_extDict(zc, ip, iLimit, offsetPtr, maxNbAttempts, 6);
	पूर्ण
पूर्ण

/* *********************************
*  Hash Chain
***********************************/
#घोषणा NEXT_IN_CHAIN(d, mask) chainTable[(d)&mask]

/* Update chains up to ip (excluded)
   Assumption : always within prefix (i.e. not within extDict) */
FORCE_INLINE
U32 ZSTD_insertAndFindFirstIndex(ZSTD_CCtx *zc, स्थिर BYTE *ip, U32 mls)
अणु
	U32 *स्थिर hashTable = zc->hashTable;
	स्थिर U32 hashLog = zc->params.cParams.hashLog;
	U32 *स्थिर chainTable = zc->chainTable;
	स्थिर U32 chainMask = (1 << zc->params.cParams.chainLog) - 1;
	स्थिर BYTE *स्थिर base = zc->base;
	स्थिर U32 target = (U32)(ip - base);
	U32 idx = zc->nextToUpdate;

	जबतक (idx < target) अणु /* catch up */
		माप_प्रकार स्थिर h = ZSTD_hashPtr(base + idx, hashLog, mls);
		NEXT_IN_CHAIN(idx, chainMask) = hashTable[h];
		hashTable[h] = idx;
		idx++;
	पूर्ण

	zc->nextToUpdate = target;
	वापस hashTable[ZSTD_hashPtr(ip, hashLog, mls)];
पूर्ण

/* inlining is important to hardwire a hot branch (ढाँचा emulation) */
FORCE_INLINE
माप_प्रकार ZSTD_HcFindBestMatch_generic(ZSTD_CCtx *zc, /* Index table will be updated */
				    स्थिर BYTE *स्थिर ip, स्थिर BYTE *स्थिर iLimit, माप_प्रकार *offsetPtr, स्थिर U32 maxNbAttempts, स्थिर U32 mls,
				    स्थिर U32 extDict)
अणु
	U32 *स्थिर chainTable = zc->chainTable;
	स्थिर U32 chainSize = (1 << zc->params.cParams.chainLog);
	स्थिर U32 chainMask = chainSize - 1;
	स्थिर BYTE *स्थिर base = zc->base;
	स्थिर BYTE *स्थिर dictBase = zc->dictBase;
	स्थिर U32 dictLimit = zc->dictLimit;
	स्थिर BYTE *स्थिर prefixStart = base + dictLimit;
	स्थिर BYTE *स्थिर dictEnd = dictBase + dictLimit;
	स्थिर U32 lowLimit = zc->lowLimit;
	स्थिर U32 curr = (U32)(ip - base);
	स्थिर U32 minChain = curr > chainSize ? curr - chainSize : 0;
	पूर्णांक nbAttempts = maxNbAttempts;
	माप_प्रकार ml = EQUAL_READ32 - 1;

	/* HC4 match finder */
	U32 matchIndex = ZSTD_insertAndFindFirstIndex(zc, ip, mls);

	क्रम (; (matchIndex > lowLimit) & (nbAttempts > 0); nbAttempts--) अणु
		स्थिर BYTE *match;
		माप_प्रकार currMl = 0;
		अगर ((!extDict) || matchIndex >= dictLimit) अणु
			match = base + matchIndex;
			अगर (match[ml] == ip[ml]) /* potentially better */
				currMl = ZSTD_count(ip, match, iLimit);
		पूर्ण अन्यथा अणु
			match = dictBase + matchIndex;
			अगर (ZSTD_पढ़ो32(match) == ZSTD_पढ़ो32(ip)) /* assumption : matchIndex <= dictLimit-4 (by table स्थिरruction) */
				currMl = ZSTD_count_2segments(ip + EQUAL_READ32, match + EQUAL_READ32, iLimit, dictEnd, prefixStart) + EQUAL_READ32;
		पूर्ण

		/* save best solution */
		अगर (currMl > ml) अणु
			ml = currMl;
			*offsetPtr = curr - matchIndex + ZSTD_REP_MOVE;
			अगर (ip + currMl == iLimit)
				अवरोध; /* best possible, and aव्योम पढ़ो overflow*/
		पूर्ण

		अगर (matchIndex <= minChain)
			अवरोध;
		matchIndex = NEXT_IN_CHAIN(matchIndex, chainMask);
	पूर्ण

	वापस ml;
पूर्ण

FORCE_INLINE माप_प्रकार ZSTD_HcFindBestMatch_selectMLS(ZSTD_CCtx *zc, स्थिर BYTE *ip, स्थिर BYTE *स्थिर iLimit, माप_प्रकार *offsetPtr, स्थिर U32 maxNbAttempts,
						   स्थिर U32 matchLengthSearch)
अणु
	चयन (matchLengthSearch) अणु
	शेष: /* includes हाल 3 */
	हाल 4: वापस ZSTD_HcFindBestMatch_generic(zc, ip, iLimit, offsetPtr, maxNbAttempts, 4, 0);
	हाल 5: वापस ZSTD_HcFindBestMatch_generic(zc, ip, iLimit, offsetPtr, maxNbAttempts, 5, 0);
	हाल 7:
	हाल 6: वापस ZSTD_HcFindBestMatch_generic(zc, ip, iLimit, offsetPtr, maxNbAttempts, 6, 0);
	पूर्ण
पूर्ण

FORCE_INLINE माप_प्रकार ZSTD_HcFindBestMatch_extDict_selectMLS(ZSTD_CCtx *zc, स्थिर BYTE *ip, स्थिर BYTE *स्थिर iLimit, माप_प्रकार *offsetPtr, स्थिर U32 maxNbAttempts,
							   स्थिर U32 matchLengthSearch)
अणु
	चयन (matchLengthSearch) अणु
	शेष: /* includes हाल 3 */
	हाल 4: वापस ZSTD_HcFindBestMatch_generic(zc, ip, iLimit, offsetPtr, maxNbAttempts, 4, 1);
	हाल 5: वापस ZSTD_HcFindBestMatch_generic(zc, ip, iLimit, offsetPtr, maxNbAttempts, 5, 1);
	हाल 7:
	हाल 6: वापस ZSTD_HcFindBestMatch_generic(zc, ip, iLimit, offsetPtr, maxNbAttempts, 6, 1);
	पूर्ण
पूर्ण

/* *******************************
*  Common parser - lazy strategy
*********************************/
FORCE_INLINE
व्योम ZSTD_compressBlock_lazy_generic(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर U32 searchMethod, स्थिर U32 depth)
अणु
	seqStore_t *seqStorePtr = &(ctx->seqStore);
	स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)src;
	स्थिर BYTE *ip = istart;
	स्थिर BYTE *anchor = istart;
	स्थिर BYTE *स्थिर iend = istart + srcSize;
	स्थिर BYTE *स्थिर ilimit = iend - 8;
	स्थिर BYTE *स्थिर base = ctx->base + ctx->dictLimit;

	U32 स्थिर maxSearches = 1 << ctx->params.cParams.searchLog;
	U32 स्थिर mls = ctx->params.cParams.searchLength;

	प्रकार माप_प्रकार (*searchMax_f)(ZSTD_CCtx * zc, स्थिर BYTE *ip, स्थिर BYTE *iLimit, माप_प्रकार *offsetPtr, U32 maxNbAttempts, U32 matchLengthSearch);
	searchMax_f स्थिर searchMax = searchMethod ? ZSTD_BtFindBestMatch_selectMLS : ZSTD_HcFindBestMatch_selectMLS;
	U32 offset_1 = ctx->rep[0], offset_2 = ctx->rep[1], savedOffset = 0;

	/* init */
	ip += (ip == base);
	ctx->nextToUpdate3 = ctx->nextToUpdate;
	अणु
		U32 स्थिर maxRep = (U32)(ip - base);
		अगर (offset_2 > maxRep)
			savedOffset = offset_2, offset_2 = 0;
		अगर (offset_1 > maxRep)
			savedOffset = offset_1, offset_1 = 0;
	पूर्ण

	/* Match Loop */
	जबतक (ip < ilimit) अणु
		माप_प्रकार matchLength = 0;
		माप_प्रकार offset = 0;
		स्थिर BYTE *start = ip + 1;

		/* check repCode */
		अगर ((offset_1 > 0) & (ZSTD_पढ़ो32(ip + 1) == ZSTD_पढ़ो32(ip + 1 - offset_1))) अणु
			/* repcode : we take it */
			matchLength = ZSTD_count(ip + 1 + EQUAL_READ32, ip + 1 + EQUAL_READ32 - offset_1, iend) + EQUAL_READ32;
			अगर (depth == 0)
				जाओ _storeSequence;
		पूर्ण

		/* first search (depth 0) */
		अणु
			माप_प्रकार offsetFound = 99999999;
			माप_प्रकार स्थिर ml2 = searchMax(ctx, ip, iend, &offsetFound, maxSearches, mls);
			अगर (ml2 > matchLength)
				matchLength = ml2, start = ip, offset = offsetFound;
		पूर्ण

		अगर (matchLength < EQUAL_READ32) अणु
			ip += ((ip - anchor) >> g_searchStrength) + 1; /* jump faster over incompressible sections */
			जारी;
		पूर्ण

		/* let's try to find a better solution */
		अगर (depth >= 1)
			जबतक (ip < ilimit) अणु
				ip++;
				अगर ((offset) && ((offset_1 > 0) & (ZSTD_पढ़ो32(ip) == ZSTD_पढ़ो32(ip - offset_1)))) अणु
					माप_प्रकार स्थिर mlRep = ZSTD_count(ip + EQUAL_READ32, ip + EQUAL_READ32 - offset_1, iend) + EQUAL_READ32;
					पूर्णांक स्थिर gain2 = (पूर्णांक)(mlRep * 3);
					पूर्णांक स्थिर gain1 = (पूर्णांक)(matchLength * 3 - ZSTD_highbit32((U32)offset + 1) + 1);
					अगर ((mlRep >= EQUAL_READ32) && (gain2 > gain1))
						matchLength = mlRep, offset = 0, start = ip;
				पूर्ण
				अणु
					माप_प्रकार offset2 = 99999999;
					माप_प्रकार स्थिर ml2 = searchMax(ctx, ip, iend, &offset2, maxSearches, mls);
					पूर्णांक स्थिर gain2 = (पूर्णांक)(ml2 * 4 - ZSTD_highbit32((U32)offset2 + 1)); /* raw approx */
					पूर्णांक स्थिर gain1 = (पूर्णांक)(matchLength * 4 - ZSTD_highbit32((U32)offset + 1) + 4);
					अगर ((ml2 >= EQUAL_READ32) && (gain2 > gain1)) अणु
						matchLength = ml2, offset = offset2, start = ip;
						जारी; /* search a better one */
					पूर्ण
				पूर्ण

				/* let's find an even better one */
				अगर ((depth == 2) && (ip < ilimit)) अणु
					ip++;
					अगर ((offset) && ((offset_1 > 0) & (ZSTD_पढ़ो32(ip) == ZSTD_पढ़ो32(ip - offset_1)))) अणु
						माप_प्रकार स्थिर ml2 = ZSTD_count(ip + EQUAL_READ32, ip + EQUAL_READ32 - offset_1, iend) + EQUAL_READ32;
						पूर्णांक स्थिर gain2 = (पूर्णांक)(ml2 * 4);
						पूर्णांक स्थिर gain1 = (पूर्णांक)(matchLength * 4 - ZSTD_highbit32((U32)offset + 1) + 1);
						अगर ((ml2 >= EQUAL_READ32) && (gain2 > gain1))
							matchLength = ml2, offset = 0, start = ip;
					पूर्ण
					अणु
						माप_प्रकार offset2 = 99999999;
						माप_प्रकार स्थिर ml2 = searchMax(ctx, ip, iend, &offset2, maxSearches, mls);
						पूर्णांक स्थिर gain2 = (पूर्णांक)(ml2 * 4 - ZSTD_highbit32((U32)offset2 + 1)); /* raw approx */
						पूर्णांक स्थिर gain1 = (पूर्णांक)(matchLength * 4 - ZSTD_highbit32((U32)offset + 1) + 7);
						अगर ((ml2 >= EQUAL_READ32) && (gain2 > gain1)) अणु
							matchLength = ml2, offset = offset2, start = ip;
							जारी;
						पूर्ण
					पूर्ण
				पूर्ण
				अवरोध; /* nothing found : store previous solution */
			पूर्ण

		/* NOTE:
		 * start[-offset+ZSTD_REP_MOVE-1] is undefined behavior.
		 * (-offset+ZSTD_REP_MOVE-1) is अचिन्हित, and is added to start, which
		 * overflows the poपूर्णांकer, which is undefined behavior.
		 */
		/* catch up */
		अगर (offset) अणु
			जबतक ((start > anchor) && (start > base + offset - ZSTD_REP_MOVE) &&
			       (start[-1] == (start-offset+ZSTD_REP_MOVE)[-1])) /* only search क्रम offset within prefix */
			अणु
				start--;
				matchLength++;
			पूर्ण
			offset_2 = offset_1;
			offset_1 = (U32)(offset - ZSTD_REP_MOVE);
		पूर्ण

	/* store sequence */
_storeSequence:
		अणु
			माप_प्रकार स्थिर litLength = start - anchor;
			ZSTD_storeSeq(seqStorePtr, litLength, anchor, (U32)offset, matchLength - MINMATCH);
			anchor = ip = start + matchLength;
		पूर्ण

		/* check immediate repcode */
		जबतक ((ip <= ilimit) && ((offset_2 > 0) & (ZSTD_पढ़ो32(ip) == ZSTD_पढ़ो32(ip - offset_2)))) अणु
			/* store sequence */
			matchLength = ZSTD_count(ip + EQUAL_READ32, ip + EQUAL_READ32 - offset_2, iend) + EQUAL_READ32;
			offset = offset_2;
			offset_2 = offset_1;
			offset_1 = (U32)offset; /* swap repcodes */
			ZSTD_storeSeq(seqStorePtr, 0, anchor, 0, matchLength - MINMATCH);
			ip += matchLength;
			anchor = ip;
			जारी; /* faster when present ... (?) */
		पूर्ण
	पूर्ण

	/* Save reps क्रम next block */
	ctx->repToConfirm[0] = offset_1 ? offset_1 : savedOffset;
	ctx->repToConfirm[1] = offset_2 ? offset_2 : savedOffset;

	/* Last Literals */
	अणु
		माप_प्रकार स्थिर lastLLSize = iend - anchor;
		स_नकल(seqStorePtr->lit, anchor, lastLLSize);
		seqStorePtr->lit += lastLLSize;
	पूर्ण
पूर्ण

अटल व्योम ZSTD_compressBlock_btlazy2(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize) अणु ZSTD_compressBlock_lazy_generic(ctx, src, srcSize, 1, 2); पूर्ण

अटल व्योम ZSTD_compressBlock_lazy2(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize) अणु ZSTD_compressBlock_lazy_generic(ctx, src, srcSize, 0, 2); पूर्ण

अटल व्योम ZSTD_compressBlock_lazy(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize) अणु ZSTD_compressBlock_lazy_generic(ctx, src, srcSize, 0, 1); पूर्ण

अटल व्योम ZSTD_compressBlock_greedy(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize) अणु ZSTD_compressBlock_lazy_generic(ctx, src, srcSize, 0, 0); पूर्ण

FORCE_INLINE
व्योम ZSTD_compressBlock_lazy_extDict_generic(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर U32 searchMethod, स्थिर U32 depth)
अणु
	seqStore_t *seqStorePtr = &(ctx->seqStore);
	स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)src;
	स्थिर BYTE *ip = istart;
	स्थिर BYTE *anchor = istart;
	स्थिर BYTE *स्थिर iend = istart + srcSize;
	स्थिर BYTE *स्थिर ilimit = iend - 8;
	स्थिर BYTE *स्थिर base = ctx->base;
	स्थिर U32 dictLimit = ctx->dictLimit;
	स्थिर U32 lowestIndex = ctx->lowLimit;
	स्थिर BYTE *स्थिर prefixStart = base + dictLimit;
	स्थिर BYTE *स्थिर dictBase = ctx->dictBase;
	स्थिर BYTE *स्थिर dictEnd = dictBase + dictLimit;
	स्थिर BYTE *स्थिर dictStart = dictBase + ctx->lowLimit;

	स्थिर U32 maxSearches = 1 << ctx->params.cParams.searchLog;
	स्थिर U32 mls = ctx->params.cParams.searchLength;

	प्रकार माप_प्रकार (*searchMax_f)(ZSTD_CCtx * zc, स्थिर BYTE *ip, स्थिर BYTE *iLimit, माप_प्रकार *offsetPtr, U32 maxNbAttempts, U32 matchLengthSearch);
	searchMax_f searchMax = searchMethod ? ZSTD_BtFindBestMatch_selectMLS_extDict : ZSTD_HcFindBestMatch_extDict_selectMLS;

	U32 offset_1 = ctx->rep[0], offset_2 = ctx->rep[1];

	/* init */
	ctx->nextToUpdate3 = ctx->nextToUpdate;
	ip += (ip == prefixStart);

	/* Match Loop */
	जबतक (ip < ilimit) अणु
		माप_प्रकार matchLength = 0;
		माप_प्रकार offset = 0;
		स्थिर BYTE *start = ip + 1;
		U32 curr = (U32)(ip - base);

		/* check repCode */
		अणु
			स्थिर U32 repIndex = (U32)(curr + 1 - offset_1);
			स्थिर BYTE *स्थिर repBase = repIndex < dictLimit ? dictBase : base;
			स्थिर BYTE *स्थिर repMatch = repBase + repIndex;
			अगर (((U32)((dictLimit - 1) - repIndex) >= 3) & (repIndex > lowestIndex)) /* पूर्णांकentional overflow */
				अगर (ZSTD_पढ़ो32(ip + 1) == ZSTD_पढ़ो32(repMatch)) अणु
					/* repcode detected we should take it */
					स्थिर BYTE *स्थिर repEnd = repIndex < dictLimit ? dictEnd : iend;
					matchLength =
					    ZSTD_count_2segments(ip + 1 + EQUAL_READ32, repMatch + EQUAL_READ32, iend, repEnd, prefixStart) + EQUAL_READ32;
					अगर (depth == 0)
						जाओ _storeSequence;
				पूर्ण
		पूर्ण

		/* first search (depth 0) */
		अणु
			माप_प्रकार offsetFound = 99999999;
			माप_प्रकार स्थिर ml2 = searchMax(ctx, ip, iend, &offsetFound, maxSearches, mls);
			अगर (ml2 > matchLength)
				matchLength = ml2, start = ip, offset = offsetFound;
		पूर्ण

		अगर (matchLength < EQUAL_READ32) अणु
			ip += ((ip - anchor) >> g_searchStrength) + 1; /* jump faster over incompressible sections */
			जारी;
		पूर्ण

		/* let's try to find a better solution */
		अगर (depth >= 1)
			जबतक (ip < ilimit) अणु
				ip++;
				curr++;
				/* check repCode */
				अगर (offset) अणु
					स्थिर U32 repIndex = (U32)(curr - offset_1);
					स्थिर BYTE *स्थिर repBase = repIndex < dictLimit ? dictBase : base;
					स्थिर BYTE *स्थिर repMatch = repBase + repIndex;
					अगर (((U32)((dictLimit - 1) - repIndex) >= 3) & (repIndex > lowestIndex)) /* पूर्णांकentional overflow */
						अगर (ZSTD_पढ़ो32(ip) == ZSTD_पढ़ो32(repMatch)) अणु
							/* repcode detected */
							स्थिर BYTE *स्थिर repEnd = repIndex < dictLimit ? dictEnd : iend;
							माप_प्रकार स्थिर repLength =
							    ZSTD_count_2segments(ip + EQUAL_READ32, repMatch + EQUAL_READ32, iend, repEnd, prefixStart) +
							    EQUAL_READ32;
							पूर्णांक स्थिर gain2 = (पूर्णांक)(repLength * 3);
							पूर्णांक स्थिर gain1 = (पूर्णांक)(matchLength * 3 - ZSTD_highbit32((U32)offset + 1) + 1);
							अगर ((repLength >= EQUAL_READ32) && (gain2 > gain1))
								matchLength = repLength, offset = 0, start = ip;
						पूर्ण
				पूर्ण

				/* search match, depth 1 */
				अणु
					माप_प्रकार offset2 = 99999999;
					माप_प्रकार स्थिर ml2 = searchMax(ctx, ip, iend, &offset2, maxSearches, mls);
					पूर्णांक स्थिर gain2 = (पूर्णांक)(ml2 * 4 - ZSTD_highbit32((U32)offset2 + 1)); /* raw approx */
					पूर्णांक स्थिर gain1 = (पूर्णांक)(matchLength * 4 - ZSTD_highbit32((U32)offset + 1) + 4);
					अगर ((ml2 >= EQUAL_READ32) && (gain2 > gain1)) अणु
						matchLength = ml2, offset = offset2, start = ip;
						जारी; /* search a better one */
					पूर्ण
				पूर्ण

				/* let's find an even better one */
				अगर ((depth == 2) && (ip < ilimit)) अणु
					ip++;
					curr++;
					/* check repCode */
					अगर (offset) अणु
						स्थिर U32 repIndex = (U32)(curr - offset_1);
						स्थिर BYTE *स्थिर repBase = repIndex < dictLimit ? dictBase : base;
						स्थिर BYTE *स्थिर repMatch = repBase + repIndex;
						अगर (((U32)((dictLimit - 1) - repIndex) >= 3) & (repIndex > lowestIndex)) /* पूर्णांकentional overflow */
							अगर (ZSTD_पढ़ो32(ip) == ZSTD_पढ़ो32(repMatch)) अणु
								/* repcode detected */
								स्थिर BYTE *स्थिर repEnd = repIndex < dictLimit ? dictEnd : iend;
								माप_प्रकार repLength = ZSTD_count_2segments(ip + EQUAL_READ32, repMatch + EQUAL_READ32, iend,
													repEnd, prefixStart) +
										   EQUAL_READ32;
								पूर्णांक gain2 = (पूर्णांक)(repLength * 4);
								पूर्णांक gain1 = (पूर्णांक)(matchLength * 4 - ZSTD_highbit32((U32)offset + 1) + 1);
								अगर ((repLength >= EQUAL_READ32) && (gain2 > gain1))
									matchLength = repLength, offset = 0, start = ip;
							पूर्ण
					पूर्ण

					/* search match, depth 2 */
					अणु
						माप_प्रकार offset2 = 99999999;
						माप_प्रकार स्थिर ml2 = searchMax(ctx, ip, iend, &offset2, maxSearches, mls);
						पूर्णांक स्थिर gain2 = (पूर्णांक)(ml2 * 4 - ZSTD_highbit32((U32)offset2 + 1)); /* raw approx */
						पूर्णांक स्थिर gain1 = (पूर्णांक)(matchLength * 4 - ZSTD_highbit32((U32)offset + 1) + 7);
						अगर ((ml2 >= EQUAL_READ32) && (gain2 > gain1)) अणु
							matchLength = ml2, offset = offset2, start = ip;
							जारी;
						पूर्ण
					पूर्ण
				पूर्ण
				अवरोध; /* nothing found : store previous solution */
			पूर्ण

		/* catch up */
		अगर (offset) अणु
			U32 स्थिर matchIndex = (U32)((start - base) - (offset - ZSTD_REP_MOVE));
			स्थिर BYTE *match = (matchIndex < dictLimit) ? dictBase + matchIndex : base + matchIndex;
			स्थिर BYTE *स्थिर mStart = (matchIndex < dictLimit) ? dictStart : prefixStart;
			जबतक ((start > anchor) && (match > mStart) && (start[-1] == match[-1])) अणु
				start--;
				match--;
				matchLength++;
			पूर्ण /* catch up */
			offset_2 = offset_1;
			offset_1 = (U32)(offset - ZSTD_REP_MOVE);
		पूर्ण

	/* store sequence */
	_storeSequence : अणु
		माप_प्रकार स्थिर litLength = start - anchor;
		ZSTD_storeSeq(seqStorePtr, litLength, anchor, (U32)offset, matchLength - MINMATCH);
		anchor = ip = start + matchLength;
	पूर्ण

		/* check immediate repcode */
		जबतक (ip <= ilimit) अणु
			स्थिर U32 repIndex = (U32)((ip - base) - offset_2);
			स्थिर BYTE *स्थिर repBase = repIndex < dictLimit ? dictBase : base;
			स्थिर BYTE *स्थिर repMatch = repBase + repIndex;
			अगर (((U32)((dictLimit - 1) - repIndex) >= 3) & (repIndex > lowestIndex)) /* पूर्णांकentional overflow */
				अगर (ZSTD_पढ़ो32(ip) == ZSTD_पढ़ो32(repMatch)) अणु
					/* repcode detected we should take it */
					स्थिर BYTE *स्थिर repEnd = repIndex < dictLimit ? dictEnd : iend;
					matchLength =
					    ZSTD_count_2segments(ip + EQUAL_READ32, repMatch + EQUAL_READ32, iend, repEnd, prefixStart) + EQUAL_READ32;
					offset = offset_2;
					offset_2 = offset_1;
					offset_1 = (U32)offset; /* swap offset history */
					ZSTD_storeSeq(seqStorePtr, 0, anchor, 0, matchLength - MINMATCH);
					ip += matchLength;
					anchor = ip;
					जारी; /* faster when present ... (?) */
				पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	/* Save reps क्रम next block */
	ctx->repToConfirm[0] = offset_1;
	ctx->repToConfirm[1] = offset_2;

	/* Last Literals */
	अणु
		माप_प्रकार स्थिर lastLLSize = iend - anchor;
		स_नकल(seqStorePtr->lit, anchor, lastLLSize);
		seqStorePtr->lit += lastLLSize;
	पूर्ण
पूर्ण

व्योम ZSTD_compressBlock_greedy_extDict(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize) अणु ZSTD_compressBlock_lazy_extDict_generic(ctx, src, srcSize, 0, 0); पूर्ण

अटल व्योम ZSTD_compressBlock_lazy_extDict(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	ZSTD_compressBlock_lazy_extDict_generic(ctx, src, srcSize, 0, 1);
पूर्ण

अटल व्योम ZSTD_compressBlock_lazy2_extDict(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	ZSTD_compressBlock_lazy_extDict_generic(ctx, src, srcSize, 0, 2);
पूर्ण

अटल व्योम ZSTD_compressBlock_btlazy2_extDict(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	ZSTD_compressBlock_lazy_extDict_generic(ctx, src, srcSize, 1, 2);
पूर्ण

/* The optimal parser */
#समावेश "zstd_opt.h"

अटल व्योम ZSTD_compressBlock_btopt(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
#अगर_घोषित ZSTD_OPT_H_91842398743
	ZSTD_compressBlock_opt_generic(ctx, src, srcSize, 0);
#अन्यथा
	(व्योम)ctx;
	(व्योम)src;
	(व्योम)srcSize;
	वापस;
#पूर्ण_अगर
पूर्ण

अटल व्योम ZSTD_compressBlock_btopt2(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
#अगर_घोषित ZSTD_OPT_H_91842398743
	ZSTD_compressBlock_opt_generic(ctx, src, srcSize, 1);
#अन्यथा
	(व्योम)ctx;
	(व्योम)src;
	(व्योम)srcSize;
	वापस;
#पूर्ण_अगर
पूर्ण

अटल व्योम ZSTD_compressBlock_btopt_extDict(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
#अगर_घोषित ZSTD_OPT_H_91842398743
	ZSTD_compressBlock_opt_extDict_generic(ctx, src, srcSize, 0);
#अन्यथा
	(व्योम)ctx;
	(व्योम)src;
	(व्योम)srcSize;
	वापस;
#पूर्ण_अगर
पूर्ण

अटल व्योम ZSTD_compressBlock_btopt2_extDict(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
#अगर_घोषित ZSTD_OPT_H_91842398743
	ZSTD_compressBlock_opt_extDict_generic(ctx, src, srcSize, 1);
#अन्यथा
	(व्योम)ctx;
	(व्योम)src;
	(व्योम)srcSize;
	वापस;
#पूर्ण_अगर
पूर्ण

प्रकार व्योम (*ZSTD_blockCompressor)(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize);

अटल ZSTD_blockCompressor ZSTD_selectBlockCompressor(ZSTD_strategy strat, पूर्णांक extDict)
अणु
	अटल स्थिर ZSTD_blockCompressor blockCompressor[2][8] = अणु
	    अणुZSTD_compressBlock_fast, ZSTD_compressBlock_द्विगुनFast, ZSTD_compressBlock_greedy, ZSTD_compressBlock_lazy, ZSTD_compressBlock_lazy2,
	     ZSTD_compressBlock_btlazy2, ZSTD_compressBlock_btopt, ZSTD_compressBlock_btopt2पूर्ण,
	    अणुZSTD_compressBlock_fast_extDict, ZSTD_compressBlock_द्विगुनFast_extDict, ZSTD_compressBlock_greedy_extDict, ZSTD_compressBlock_lazy_extDict,
	     ZSTD_compressBlock_lazy2_extDict, ZSTD_compressBlock_btlazy2_extDict, ZSTD_compressBlock_btopt_extDict, ZSTD_compressBlock_btopt2_extDictपूर्णपूर्ण;

	वापस blockCompressor[extDict][(U32)strat];
पूर्ण

अटल माप_प्रकार ZSTD_compressBlock_पूर्णांकernal(ZSTD_CCtx *zc, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	ZSTD_blockCompressor स्थिर blockCompressor = ZSTD_selectBlockCompressor(zc->params.cParams.strategy, zc->lowLimit < zc->dictLimit);
	स्थिर BYTE *स्थिर base = zc->base;
	स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)src;
	स्थिर U32 curr = (U32)(istart - base);
	अगर (srcSize < MIN_CBLOCK_SIZE + ZSTD_blockHeaderSize + 1)
		वापस 0; /* करोn't even attempt compression below a certain srcSize */
	ZSTD_resetSeqStore(&(zc->seqStore));
	अगर (curr > zc->nextToUpdate + 384)
		zc->nextToUpdate = curr - MIN(192, (U32)(curr - zc->nextToUpdate - 384)); /* update tree not updated after finding very दीर्घ rep matches */
	blockCompressor(zc, src, srcSize);
	वापस ZSTD_compressSequences(zc, dst, dstCapacity, srcSize);
पूर्ण

/*! ZSTD_compress_generic() :
*   Compress a chunk of data पूर्णांकo one or multiple blocks.
*   All blocks will be terminated, all input will be consumed.
*   Function will issue an error अगर there is not enough `dstCapacity` to hold the compressed content.
*   Frame is supposed alपढ़ोy started (header alपढ़ोy produced)
*   @वापस : compressed size, or an error code
*/
अटल माप_प्रकार ZSTD_compress_generic(ZSTD_CCtx *cctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize, U32 lastFrameChunk)
अणु
	माप_प्रकार blockSize = cctx->blockSize;
	माप_प्रकार reमुख्यing = srcSize;
	स्थिर BYTE *ip = (स्थिर BYTE *)src;
	BYTE *स्थिर ostart = (BYTE *)dst;
	BYTE *op = ostart;
	U32 स्थिर maxDist = 1 << cctx->params.cParams.winकरोwLog;

	अगर (cctx->params.fParams.checksumFlag && srcSize)
		xxh64_update(&cctx->xxhState, src, srcSize);

	जबतक (reमुख्यing) अणु
		U32 स्थिर lastBlock = lastFrameChunk & (blockSize >= reमुख्यing);
		माप_प्रकार cSize;

		अगर (dstCapacity < ZSTD_blockHeaderSize + MIN_CBLOCK_SIZE)
			वापस ERROR(dstSize_tooSmall); /* not enough space to store compressed block */
		अगर (reमुख्यing < blockSize)
			blockSize = reमुख्यing;

		/* preemptive overflow correction */
		अगर (cctx->lowLimit > (3U << 29)) अणु
			U32 स्थिर cycleMask = (1 << ZSTD_cycleLog(cctx->params.cParams.hashLog, cctx->params.cParams.strategy)) - 1;
			U32 स्थिर curr = (U32)(ip - cctx->base);
			U32 स्थिर newCurr = (curr & cycleMask) + (1 << cctx->params.cParams.winकरोwLog);
			U32 स्थिर correction = curr - newCurr;
			ZSTD_STATIC_ASSERT(ZSTD_WINDOWLOG_MAX_64 <= 30);
			ZSTD_reduceIndex(cctx, correction);
			cctx->base += correction;
			cctx->dictBase += correction;
			cctx->lowLimit -= correction;
			cctx->dictLimit -= correction;
			अगर (cctx->nextToUpdate < correction)
				cctx->nextToUpdate = 0;
			अन्यथा
				cctx->nextToUpdate -= correction;
		पूर्ण

		अगर ((U32)(ip + blockSize - cctx->base) > cctx->loadedDictEnd + maxDist) अणु
			/* enक्रमce maxDist */
			U32 स्थिर newLowLimit = (U32)(ip + blockSize - cctx->base) - maxDist;
			अगर (cctx->lowLimit < newLowLimit)
				cctx->lowLimit = newLowLimit;
			अगर (cctx->dictLimit < cctx->lowLimit)
				cctx->dictLimit = cctx->lowLimit;
		पूर्ण

		cSize = ZSTD_compressBlock_पूर्णांकernal(cctx, op + ZSTD_blockHeaderSize, dstCapacity - ZSTD_blockHeaderSize, ip, blockSize);
		अगर (ZSTD_isError(cSize))
			वापस cSize;

		अगर (cSize == 0) अणु /* block is not compressible */
			U32 स्थिर cBlockHeader24 = lastBlock + (((U32)bt_raw) << 1) + (U32)(blockSize << 3);
			अगर (blockSize + ZSTD_blockHeaderSize > dstCapacity)
				वापस ERROR(dstSize_tooSmall);
			ZSTD_ग_लिखोLE32(op, cBlockHeader24); /* no pb, 4th byte will be overwritten */
			स_नकल(op + ZSTD_blockHeaderSize, ip, blockSize);
			cSize = ZSTD_blockHeaderSize + blockSize;
		पूर्ण अन्यथा अणु
			U32 स्थिर cBlockHeader24 = lastBlock + (((U32)bt_compressed) << 1) + (U32)(cSize << 3);
			ZSTD_ग_लिखोLE24(op, cBlockHeader24);
			cSize += ZSTD_blockHeaderSize;
		पूर्ण

		reमुख्यing -= blockSize;
		dstCapacity -= cSize;
		ip += blockSize;
		op += cSize;
	पूर्ण

	अगर (lastFrameChunk && (op > ostart))
		cctx->stage = ZSTDcs_ending;
	वापस op - ostart;
पूर्ण

अटल माप_प्रकार ZSTD_ग_लिखोFrameHeader(व्योम *dst, माप_प्रकार dstCapacity, ZSTD_parameters params, U64 pledgedSrcSize, U32 dictID)
अणु
	BYTE *स्थिर op = (BYTE *)dst;
	U32 स्थिर dictIDSizeCode = (dictID > 0) + (dictID >= 256) + (dictID >= 65536); /* 0-3 */
	U32 स्थिर checksumFlag = params.fParams.checksumFlag > 0;
	U32 स्थिर winकरोwSize = 1U << params.cParams.winकरोwLog;
	U32 स्थिर singleSegment = params.fParams.contentSizeFlag && (winकरोwSize >= pledgedSrcSize);
	BYTE स्थिर winकरोwLogByte = (BYTE)((params.cParams.winकरोwLog - ZSTD_WINDOWLOG_ABSOLUTEMIN) << 3);
	U32 स्थिर fcsCode =
	    params.fParams.contentSizeFlag ? (pledgedSrcSize >= 256) + (pledgedSrcSize >= 65536 + 256) + (pledgedSrcSize >= 0xFFFFFFFFU) : 0; /* 0-3 */
	BYTE स्थिर frameHeaderDecriptionByte = (BYTE)(dictIDSizeCode + (checksumFlag << 2) + (singleSegment << 5) + (fcsCode << 6));
	माप_प्रकार pos;

	अगर (dstCapacity < ZSTD_frameHeaderSize_max)
		वापस ERROR(dstSize_tooSmall);

	ZSTD_ग_लिखोLE32(dst, ZSTD_MAGICNUMBER);
	op[4] = frameHeaderDecriptionByte;
	pos = 5;
	अगर (!singleSegment)
		op[pos++] = winकरोwLogByte;
	चयन (dictIDSizeCode) अणु
	शेष: /* impossible */
	हाल 0: अवरोध;
	हाल 1:
		op[pos] = (BYTE)(dictID);
		pos++;
		अवरोध;
	हाल 2:
		ZSTD_ग_लिखोLE16(op + pos, (U16)dictID);
		pos += 2;
		अवरोध;
	हाल 3:
		ZSTD_ग_लिखोLE32(op + pos, dictID);
		pos += 4;
		अवरोध;
	पूर्ण
	चयन (fcsCode) अणु
	शेष: /* impossible */
	हाल 0:
		अगर (singleSegment)
			op[pos++] = (BYTE)(pledgedSrcSize);
		अवरोध;
	हाल 1:
		ZSTD_ग_लिखोLE16(op + pos, (U16)(pledgedSrcSize - 256));
		pos += 2;
		अवरोध;
	हाल 2:
		ZSTD_ग_लिखोLE32(op + pos, (U32)(pledgedSrcSize));
		pos += 4;
		अवरोध;
	हाल 3:
		ZSTD_ग_लिखोLE64(op + pos, (U64)(pledgedSrcSize));
		pos += 8;
		अवरोध;
	पूर्ण
	वापस pos;
पूर्ण

अटल माप_प्रकार ZSTD_compressContinue_पूर्णांकernal(ZSTD_CCtx *cctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize, U32 frame, U32 lastFrameChunk)
अणु
	स्थिर BYTE *स्थिर ip = (स्थिर BYTE *)src;
	माप_प्रकार fhSize = 0;

	अगर (cctx->stage == ZSTDcs_created)
		वापस ERROR(stage_wrong); /* missing init (ZSTD_compressBegin) */

	अगर (frame && (cctx->stage == ZSTDcs_init)) अणु
		fhSize = ZSTD_ग_लिखोFrameHeader(dst, dstCapacity, cctx->params, cctx->frameContentSize, cctx->dictID);
		अगर (ZSTD_isError(fhSize))
			वापस fhSize;
		dstCapacity -= fhSize;
		dst = (अक्षर *)dst + fhSize;
		cctx->stage = ZSTDcs_ongoing;
	पूर्ण

	/* Check अगर blocks follow each other */
	अगर (src != cctx->nextSrc) अणु
		/* not contiguous */
		सूचक_भेद_प्रकार स्थिर delta = cctx->nextSrc - ip;
		cctx->lowLimit = cctx->dictLimit;
		cctx->dictLimit = (U32)(cctx->nextSrc - cctx->base);
		cctx->dictBase = cctx->base;
		cctx->base -= delta;
		cctx->nextToUpdate = cctx->dictLimit;
		अगर (cctx->dictLimit - cctx->lowLimit < HASH_READ_SIZE)
			cctx->lowLimit = cctx->dictLimit; /* too small extDict */
	पूर्ण

	/* अगर input and dictionary overlap : reduce dictionary (area presumed modअगरied by input) */
	अगर ((ip + srcSize > cctx->dictBase + cctx->lowLimit) & (ip < cctx->dictBase + cctx->dictLimit)) अणु
		सूचक_भेद_प्रकार स्थिर highInputIdx = (ip + srcSize) - cctx->dictBase;
		U32 स्थिर lowLimitMax = (highInputIdx > (सूचक_भेद_प्रकार)cctx->dictLimit) ? cctx->dictLimit : (U32)highInputIdx;
		cctx->lowLimit = lowLimitMax;
	पूर्ण

	cctx->nextSrc = ip + srcSize;

	अगर (srcSize) अणु
		माप_प्रकार स्थिर cSize = frame ? ZSTD_compress_generic(cctx, dst, dstCapacity, src, srcSize, lastFrameChunk)
					   : ZSTD_compressBlock_पूर्णांकernal(cctx, dst, dstCapacity, src, srcSize);
		अगर (ZSTD_isError(cSize))
			वापस cSize;
		वापस cSize + fhSize;
	पूर्ण अन्यथा
		वापस fhSize;
पूर्ण

माप_प्रकार ZSTD_compressContinue(ZSTD_CCtx *cctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	वापस ZSTD_compressContinue_पूर्णांकernal(cctx, dst, dstCapacity, src, srcSize, 1, 0);
पूर्ण

माप_प्रकार ZSTD_getBlockSizeMax(ZSTD_CCtx *cctx) अणु वापस MIN(ZSTD_BLOCKSIZE_ABSOLUTEMAX, 1 << cctx->params.cParams.winकरोwLog); पूर्ण

माप_प्रकार ZSTD_compressBlock(ZSTD_CCtx *cctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	माप_प्रकार स्थिर blockSizeMax = ZSTD_getBlockSizeMax(cctx);
	अगर (srcSize > blockSizeMax)
		वापस ERROR(srcSize_wrong);
	वापस ZSTD_compressContinue_पूर्णांकernal(cctx, dst, dstCapacity, src, srcSize, 0, 0);
पूर्ण

/*! ZSTD_loadDictionaryContent() :
 *  @वापस : 0, or an error code
 */
अटल माप_प्रकार ZSTD_loadDictionaryContent(ZSTD_CCtx *zc, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	स्थिर BYTE *स्थिर ip = (स्थिर BYTE *)src;
	स्थिर BYTE *स्थिर iend = ip + srcSize;

	/* input becomes curr prefix */
	zc->lowLimit = zc->dictLimit;
	zc->dictLimit = (U32)(zc->nextSrc - zc->base);
	zc->dictBase = zc->base;
	zc->base += ip - zc->nextSrc;
	zc->nextToUpdate = zc->dictLimit;
	zc->loadedDictEnd = zc->क्रमceWinकरोw ? 0 : (U32)(iend - zc->base);

	zc->nextSrc = iend;
	अगर (srcSize <= HASH_READ_SIZE)
		वापस 0;

	चयन (zc->params.cParams.strategy) अणु
	हाल ZSTD_fast: ZSTD_fillHashTable(zc, iend, zc->params.cParams.searchLength); अवरोध;

	हाल ZSTD_dfast: ZSTD_fillDoubleHashTable(zc, iend, zc->params.cParams.searchLength); अवरोध;

	हाल ZSTD_greedy:
	हाल ZSTD_lazy:
	हाल ZSTD_lazy2:
		अगर (srcSize >= HASH_READ_SIZE)
			ZSTD_insertAndFindFirstIndex(zc, iend - HASH_READ_SIZE, zc->params.cParams.searchLength);
		अवरोध;

	हाल ZSTD_btlazy2:
	हाल ZSTD_btopt:
	हाल ZSTD_btopt2:
		अगर (srcSize >= HASH_READ_SIZE)
			ZSTD_updateTree(zc, iend - HASH_READ_SIZE, iend, 1 << zc->params.cParams.searchLog, zc->params.cParams.searchLength);
		अवरोध;

	शेष:
		वापस ERROR(GENERIC); /* strategy करोesn't exist; impossible */
	पूर्ण

	zc->nextToUpdate = (U32)(iend - zc->base);
	वापस 0;
पूर्ण

/* Dictionaries that assign zero probability to symbols that show up causes problems
   when FSE encoding.  Refuse dictionaries that assign zero probability to symbols
   that we may encounter during compression.
   NOTE: This behavior is not standard and could be improved in the future. */
अटल माप_प्रकार ZSTD_checkDictNCount(लघु *normalizedCounter, अचिन्हित dictMaxSymbolValue, अचिन्हित maxSymbolValue)
अणु
	U32 s;
	अगर (dictMaxSymbolValue < maxSymbolValue)
		वापस ERROR(dictionary_corrupted);
	क्रम (s = 0; s <= maxSymbolValue; ++s) अणु
		अगर (normalizedCounter[s] == 0)
			वापस ERROR(dictionary_corrupted);
	पूर्ण
	वापस 0;
पूर्ण

/* Dictionary क्रमmat :
 * See :
 * https://github.com/facebook/zstd/blob/master/करोc/zstd_compression_क्रमmat.md#dictionary-क्रमmat
 */
/*! ZSTD_loadZstdDictionary() :
 * @वापस : 0, or an error code
 *  assumptions : magic number supposed alपढ़ोy checked
 *                dictSize supposed > 8
 */
अटल माप_प्रकार ZSTD_loadZstdDictionary(ZSTD_CCtx *cctx, स्थिर व्योम *dict, माप_प्रकार dictSize)
अणु
	स्थिर BYTE *dictPtr = (स्थिर BYTE *)dict;
	स्थिर BYTE *स्थिर dictEnd = dictPtr + dictSize;
	लघु offcodeNCount[MaxOff + 1];
	अचिन्हित offcodeMaxValue = MaxOff;

	dictPtr += 4; /* skip magic number */
	cctx->dictID = cctx->params.fParams.noDictIDFlag ? 0 : ZSTD_पढ़ोLE32(dictPtr);
	dictPtr += 4;

	अणु
		माप_प्रकार स्थिर hufHeaderSize = HUF_पढ़ोCTable_wksp(cctx->hufTable, 255, dictPtr, dictEnd - dictPtr, cctx->पंचांगpCounters, माप(cctx->पंचांगpCounters));
		अगर (HUF_isError(hufHeaderSize))
			वापस ERROR(dictionary_corrupted);
		dictPtr += hufHeaderSize;
	पूर्ण

	अणु
		अचिन्हित offcodeLog;
		माप_प्रकार स्थिर offcodeHeaderSize = FSE_पढ़ोNCount(offcodeNCount, &offcodeMaxValue, &offcodeLog, dictPtr, dictEnd - dictPtr);
		अगर (FSE_isError(offcodeHeaderSize))
			वापस ERROR(dictionary_corrupted);
		अगर (offcodeLog > OffFSELog)
			वापस ERROR(dictionary_corrupted);
		/* Defer checking offcodeMaxValue because we need to know the size of the dictionary content */
		CHECK_E(FSE_buildCTable_wksp(cctx->offcodeCTable, offcodeNCount, offcodeMaxValue, offcodeLog, cctx->पंचांगpCounters, माप(cctx->पंचांगpCounters)),
			dictionary_corrupted);
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
		/* Every match length code must have non-zero probability */
		CHECK_F(ZSTD_checkDictNCount(matchlengthNCount, matchlengthMaxValue, MaxML));
		CHECK_E(
		    FSE_buildCTable_wksp(cctx->matchlengthCTable, matchlengthNCount, matchlengthMaxValue, matchlengthLog, cctx->पंचांगpCounters, माप(cctx->पंचांगpCounters)),
		    dictionary_corrupted);
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
		/* Every literal length code must have non-zero probability */
		CHECK_F(ZSTD_checkDictNCount(litlengthNCount, litlengthMaxValue, MaxLL));
		CHECK_E(FSE_buildCTable_wksp(cctx->litlengthCTable, litlengthNCount, litlengthMaxValue, litlengthLog, cctx->पंचांगpCounters, माप(cctx->पंचांगpCounters)),
			dictionary_corrupted);
		dictPtr += litlengthHeaderSize;
	पूर्ण

	अगर (dictPtr + 12 > dictEnd)
		वापस ERROR(dictionary_corrupted);
	cctx->rep[0] = ZSTD_पढ़ोLE32(dictPtr + 0);
	cctx->rep[1] = ZSTD_पढ़ोLE32(dictPtr + 4);
	cctx->rep[2] = ZSTD_पढ़ोLE32(dictPtr + 8);
	dictPtr += 12;

	अणु
		माप_प्रकार स्थिर dictContentSize = (माप_प्रकार)(dictEnd - dictPtr);
		U32 offcodeMax = MaxOff;
		अगर (dictContentSize <= ((U32)-1) - 128 KB) अणु
			U32 स्थिर maxOffset = (U32)dictContentSize + 128 KB; /* The maximum offset that must be supported */
			offcodeMax = ZSTD_highbit32(maxOffset);		     /* Calculate minimum offset code required to represent maxOffset */
		पूर्ण
		/* All offset values <= dictContentSize + 128 KB must be representable */
		CHECK_F(ZSTD_checkDictNCount(offcodeNCount, offcodeMaxValue, MIN(offcodeMax, MaxOff)));
		/* All repCodes must be <= dictContentSize and != 0*/
		अणु
			U32 u;
			क्रम (u = 0; u < 3; u++) अणु
				अगर (cctx->rep[u] == 0)
					वापस ERROR(dictionary_corrupted);
				अगर (cctx->rep[u] > dictContentSize)
					वापस ERROR(dictionary_corrupted);
			पूर्ण
		पूर्ण

		cctx->flagStaticTables = 1;
		cctx->flagStaticHufTable = HUF_repeat_valid;
		वापस ZSTD_loadDictionaryContent(cctx, dictPtr, dictContentSize);
	पूर्ण
पूर्ण

/** ZSTD_compress_insertDictionary() :
*   @वापस : 0, or an error code */
अटल माप_प्रकार ZSTD_compress_insertDictionary(ZSTD_CCtx *cctx, स्थिर व्योम *dict, माप_प्रकार dictSize)
अणु
	अगर ((dict == शून्य) || (dictSize <= 8))
		वापस 0;

	/* dict as pure content */
	अगर ((ZSTD_पढ़ोLE32(dict) != ZSTD_DICT_MAGIC) || (cctx->क्रमceRawDict))
		वापस ZSTD_loadDictionaryContent(cctx, dict, dictSize);

	/* dict as zstd dictionary */
	वापस ZSTD_loadZstdDictionary(cctx, dict, dictSize);
पूर्ण

/*! ZSTD_compressBegin_पूर्णांकernal() :
*   @वापस : 0, or an error code */
अटल माप_प्रकार ZSTD_compressBegin_पूर्णांकernal(ZSTD_CCtx *cctx, स्थिर व्योम *dict, माप_प्रकार dictSize, ZSTD_parameters params, U64 pledgedSrcSize)
अणु
	ZSTD_compResetPolicy_e स्थिर crp = dictSize ? ZSTDcrp_fullReset : ZSTDcrp_जारी;
	CHECK_F(ZSTD_resetCCtx_advanced(cctx, params, pledgedSrcSize, crp));
	वापस ZSTD_compress_insertDictionary(cctx, dict, dictSize);
पूर्ण

/*! ZSTD_compressBegin_advanced() :
*   @वापस : 0, or an error code */
माप_प्रकार ZSTD_compressBegin_advanced(ZSTD_CCtx *cctx, स्थिर व्योम *dict, माप_प्रकार dictSize, ZSTD_parameters params, अचिन्हित दीर्घ दीर्घ pledgedSrcSize)
अणु
	/* compression parameters verअगरication and optimization */
	CHECK_F(ZSTD_checkCParams(params.cParams));
	वापस ZSTD_compressBegin_पूर्णांकernal(cctx, dict, dictSize, params, pledgedSrcSize);
पूर्ण

माप_प्रकार ZSTD_compressBegin_usingDict(ZSTD_CCtx *cctx, स्थिर व्योम *dict, माप_प्रकार dictSize, पूर्णांक compressionLevel)
अणु
	ZSTD_parameters स्थिर params = ZSTD_getParams(compressionLevel, 0, dictSize);
	वापस ZSTD_compressBegin_पूर्णांकernal(cctx, dict, dictSize, params, 0);
पूर्ण

माप_प्रकार ZSTD_compressBegin(ZSTD_CCtx *cctx, पूर्णांक compressionLevel) अणु वापस ZSTD_compressBegin_usingDict(cctx, शून्य, 0, compressionLevel); पूर्ण

/*! ZSTD_ग_लिखोEpilogue() :
*   Ends a frame.
*   @वापस : nb of bytes written पूर्णांकo dst (or an error code) */
अटल माप_प्रकार ZSTD_ग_लिखोEpilogue(ZSTD_CCtx *cctx, व्योम *dst, माप_प्रकार dstCapacity)
अणु
	BYTE *स्थिर ostart = (BYTE *)dst;
	BYTE *op = ostart;
	माप_प्रकार fhSize = 0;

	अगर (cctx->stage == ZSTDcs_created)
		वापस ERROR(stage_wrong); /* init missing */

	/* special हाल : empty frame */
	अगर (cctx->stage == ZSTDcs_init) अणु
		fhSize = ZSTD_ग_लिखोFrameHeader(dst, dstCapacity, cctx->params, 0, 0);
		अगर (ZSTD_isError(fhSize))
			वापस fhSize;
		dstCapacity -= fhSize;
		op += fhSize;
		cctx->stage = ZSTDcs_ongoing;
	पूर्ण

	अगर (cctx->stage != ZSTDcs_ending) अणु
		/* ग_लिखो one last empty block, make it the "last" block */
		U32 स्थिर cBlockHeader24 = 1 /* last block */ + (((U32)bt_raw) << 1) + 0;
		अगर (dstCapacity < 4)
			वापस ERROR(dstSize_tooSmall);
		ZSTD_ग_लिखोLE32(op, cBlockHeader24);
		op += ZSTD_blockHeaderSize;
		dstCapacity -= ZSTD_blockHeaderSize;
	पूर्ण

	अगर (cctx->params.fParams.checksumFlag) अणु
		U32 स्थिर checksum = (U32)xxh64_digest(&cctx->xxhState);
		अगर (dstCapacity < 4)
			वापस ERROR(dstSize_tooSmall);
		ZSTD_ग_लिखोLE32(op, checksum);
		op += 4;
	पूर्ण

	cctx->stage = ZSTDcs_created; /* वापस to "created but no init" status */
	वापस op - ostart;
पूर्ण

माप_प्रकार ZSTD_compressEnd(ZSTD_CCtx *cctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	माप_प्रकार endResult;
	माप_प्रकार स्थिर cSize = ZSTD_compressContinue_पूर्णांकernal(cctx, dst, dstCapacity, src, srcSize, 1, 1);
	अगर (ZSTD_isError(cSize))
		वापस cSize;
	endResult = ZSTD_ग_लिखोEpilogue(cctx, (अक्षर *)dst + cSize, dstCapacity - cSize);
	अगर (ZSTD_isError(endResult))
		वापस endResult;
	वापस cSize + endResult;
पूर्ण

अटल माप_प्रकार ZSTD_compress_पूर्णांकernal(ZSTD_CCtx *cctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर व्योम *dict, माप_प्रकार dictSize,
				     ZSTD_parameters params)
अणु
	CHECK_F(ZSTD_compressBegin_पूर्णांकernal(cctx, dict, dictSize, params, srcSize));
	वापस ZSTD_compressEnd(cctx, dst, dstCapacity, src, srcSize);
पूर्ण

माप_प्रकार ZSTD_compress_usingDict(ZSTD_CCtx *ctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर व्योम *dict, माप_प्रकार dictSize,
			       ZSTD_parameters params)
अणु
	वापस ZSTD_compress_पूर्णांकernal(ctx, dst, dstCapacity, src, srcSize, dict, dictSize, params);
पूर्ण

माप_प्रकार ZSTD_compressCCtx(ZSTD_CCtx *ctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize, ZSTD_parameters params)
अणु
	वापस ZSTD_compress_पूर्णांकernal(ctx, dst, dstCapacity, src, srcSize, शून्य, 0, params);
पूर्ण

/* =====  Dictionary API  ===== */

काष्ठा ZSTD_CDict_s अणु
	व्योम *dictBuffer;
	स्थिर व्योम *dictContent;
	माप_प्रकार dictContentSize;
	ZSTD_CCtx *refContext;
पूर्ण; /* प्रकार'd tp ZSTD_CDict within "zstd.h" */

माप_प्रकार ZSTD_CDictWorkspaceBound(ZSTD_compressionParameters cParams) अणु वापस ZSTD_CCtxWorkspaceBound(cParams) + ZSTD_ALIGN(माप(ZSTD_CDict)); पूर्ण

अटल ZSTD_CDict *ZSTD_createCDict_advanced(स्थिर व्योम *dictBuffer, माप_प्रकार dictSize, अचिन्हित byReference, ZSTD_parameters params, ZSTD_customMem customMem)
अणु
	अगर (!customMem.customAlloc || !customMem.customFree)
		वापस शून्य;

	अणु
		ZSTD_CDict *स्थिर cdict = (ZSTD_CDict *)ZSTD_दो_स्मृति(माप(ZSTD_CDict), customMem);
		ZSTD_CCtx *स्थिर cctx = ZSTD_createCCtx_advanced(customMem);

		अगर (!cdict || !cctx) अणु
			ZSTD_मुक्त(cdict, customMem);
			ZSTD_मुक्तCCtx(cctx);
			वापस शून्य;
		पूर्ण

		अगर ((byReference) || (!dictBuffer) || (!dictSize)) अणु
			cdict->dictBuffer = शून्य;
			cdict->dictContent = dictBuffer;
		पूर्ण अन्यथा अणु
			व्योम *स्थिर पूर्णांकernalBuffer = ZSTD_दो_स्मृति(dictSize, customMem);
			अगर (!पूर्णांकernalBuffer) अणु
				ZSTD_मुक्त(cctx, customMem);
				ZSTD_मुक्त(cdict, customMem);
				वापस शून्य;
			पूर्ण
			स_नकल(पूर्णांकernalBuffer, dictBuffer, dictSize);
			cdict->dictBuffer = पूर्णांकernalBuffer;
			cdict->dictContent = पूर्णांकernalBuffer;
		पूर्ण

		अणु
			माप_प्रकार स्थिर errorCode = ZSTD_compressBegin_advanced(cctx, cdict->dictContent, dictSize, params, 0);
			अगर (ZSTD_isError(errorCode)) अणु
				ZSTD_मुक्त(cdict->dictBuffer, customMem);
				ZSTD_मुक्त(cdict, customMem);
				ZSTD_मुक्तCCtx(cctx);
				वापस शून्य;
			पूर्ण
		पूर्ण

		cdict->refContext = cctx;
		cdict->dictContentSize = dictSize;
		वापस cdict;
	पूर्ण
पूर्ण

ZSTD_CDict *ZSTD_initCDict(स्थिर व्योम *dict, माप_प्रकार dictSize, ZSTD_parameters params, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	ZSTD_customMem स्थिर stackMem = ZSTD_initStack(workspace, workspaceSize);
	वापस ZSTD_createCDict_advanced(dict, dictSize, 1, params, stackMem);
पूर्ण

माप_प्रकार ZSTD_मुक्तCDict(ZSTD_CDict *cdict)
अणु
	अगर (cdict == शून्य)
		वापस 0; /* support मुक्त on शून्य */
	अणु
		ZSTD_customMem स्थिर cMem = cdict->refContext->customMem;
		ZSTD_मुक्तCCtx(cdict->refContext);
		ZSTD_मुक्त(cdict->dictBuffer, cMem);
		ZSTD_मुक्त(cdict, cMem);
		वापस 0;
	पूर्ण
पूर्ण

अटल ZSTD_parameters ZSTD_getParamsFromCDict(स्थिर ZSTD_CDict *cdict) अणु वापस ZSTD_getParamsFromCCtx(cdict->refContext); पूर्ण

माप_प्रकार ZSTD_compressBegin_usingCDict(ZSTD_CCtx *cctx, स्थिर ZSTD_CDict *cdict, अचिन्हित दीर्घ दीर्घ pledgedSrcSize)
अणु
	अगर (cdict->dictContentSize)
		CHECK_F(ZSTD_copyCCtx(cctx, cdict->refContext, pledgedSrcSize))
	अन्यथा अणु
		ZSTD_parameters params = cdict->refContext->params;
		params.fParams.contentSizeFlag = (pledgedSrcSize > 0);
		CHECK_F(ZSTD_compressBegin_advanced(cctx, शून्य, 0, params, pledgedSrcSize));
	पूर्ण
	वापस 0;
पूर्ण

/*! ZSTD_compress_usingCDict() :
*   Compression using a digested Dictionary.
*   Faster startup than ZSTD_compress_usingDict(), recommended when same dictionary is used multiple बार.
*   Note that compression level is decided during dictionary creation */
माप_प्रकार ZSTD_compress_usingCDict(ZSTD_CCtx *cctx, व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर ZSTD_CDict *cdict)
अणु
	CHECK_F(ZSTD_compressBegin_usingCDict(cctx, cdict, srcSize));

	अगर (cdict->refContext->params.fParams.contentSizeFlag == 1) अणु
		cctx->params.fParams.contentSizeFlag = 1;
		cctx->frameContentSize = srcSize;
	पूर्ण अन्यथा अणु
		cctx->params.fParams.contentSizeFlag = 0;
	पूर्ण

	वापस ZSTD_compressEnd(cctx, dst, dstCapacity, src, srcSize);
पूर्ण

/* ******************************************************************
*  Streaming
********************************************************************/

प्रकार क्रमागत अणु zcss_init, zcss_load, zcss_flush, zcss_final पूर्ण ZSTD_cStreamStage;

काष्ठा ZSTD_CStream_s अणु
	ZSTD_CCtx *cctx;
	ZSTD_CDict *cdictLocal;
	स्थिर ZSTD_CDict *cdict;
	अक्षर *inBuff;
	माप_प्रकार inBuffSize;
	माप_प्रकार inToCompress;
	माप_प्रकार inBuffPos;
	माप_प्रकार inBuffTarget;
	माप_प्रकार blockSize;
	अक्षर *outBuff;
	माप_प्रकार outBuffSize;
	माप_प्रकार outBuffContentSize;
	माप_प्रकार outBuffFlushedSize;
	ZSTD_cStreamStage stage;
	U32 checksum;
	U32 frameEnded;
	U64 pledgedSrcSize;
	U64 inputProcessed;
	ZSTD_parameters params;
	ZSTD_customMem customMem;
पूर्ण; /* प्रकार'd to ZSTD_CStream within "zstd.h" */

माप_प्रकार ZSTD_CStreamWorkspaceBound(ZSTD_compressionParameters cParams)
अणु
	माप_प्रकार स्थिर inBuffSize = (माप_प्रकार)1 << cParams.winकरोwLog;
	माप_प्रकार स्थिर blockSize = MIN(ZSTD_BLOCKSIZE_ABSOLUTEMAX, inBuffSize);
	माप_प्रकार स्थिर outBuffSize = ZSTD_compressBound(blockSize) + 1;

	वापस ZSTD_CCtxWorkspaceBound(cParams) + ZSTD_ALIGN(माप(ZSTD_CStream)) + ZSTD_ALIGN(inBuffSize) + ZSTD_ALIGN(outBuffSize);
पूर्ण

ZSTD_CStream *ZSTD_createCStream_advanced(ZSTD_customMem customMem)
अणु
	ZSTD_CStream *zcs;

	अगर (!customMem.customAlloc || !customMem.customFree)
		वापस शून्य;

	zcs = (ZSTD_CStream *)ZSTD_दो_स्मृति(माप(ZSTD_CStream), customMem);
	अगर (zcs == शून्य)
		वापस शून्य;
	स_रखो(zcs, 0, माप(ZSTD_CStream));
	स_नकल(&zcs->customMem, &customMem, माप(ZSTD_customMem));
	zcs->cctx = ZSTD_createCCtx_advanced(customMem);
	अगर (zcs->cctx == शून्य) अणु
		ZSTD_मुक्तCStream(zcs);
		वापस शून्य;
	पूर्ण
	वापस zcs;
पूर्ण

माप_प्रकार ZSTD_मुक्तCStream(ZSTD_CStream *zcs)
अणु
	अगर (zcs == शून्य)
		वापस 0; /* support मुक्त on शून्य */
	अणु
		ZSTD_customMem स्थिर cMem = zcs->customMem;
		ZSTD_मुक्तCCtx(zcs->cctx);
		zcs->cctx = शून्य;
		ZSTD_मुक्तCDict(zcs->cdictLocal);
		zcs->cdictLocal = शून्य;
		ZSTD_मुक्त(zcs->inBuff, cMem);
		zcs->inBuff = शून्य;
		ZSTD_मुक्त(zcs->outBuff, cMem);
		zcs->outBuff = शून्य;
		ZSTD_मुक्त(zcs, cMem);
		वापस 0;
	पूर्ण
पूर्ण

/*======   Initialization   ======*/

माप_प्रकार ZSTD_CStreamInSize(व्योम) अणु वापस ZSTD_BLOCKSIZE_ABSOLUTEMAX; पूर्ण
माप_प्रकार ZSTD_CStreamOutSize(व्योम) अणु वापस ZSTD_compressBound(ZSTD_BLOCKSIZE_ABSOLUTEMAX) + ZSTD_blockHeaderSize + 4 /* 32-bits hash */; पूर्ण

अटल माप_प्रकार ZSTD_resetCStream_पूर्णांकernal(ZSTD_CStream *zcs, अचिन्हित दीर्घ दीर्घ pledgedSrcSize)
अणु
	अगर (zcs->inBuffSize == 0)
		वापस ERROR(stage_wrong); /* zcs has not been init at least once => can't reset */

	अगर (zcs->cdict)
		CHECK_F(ZSTD_compressBegin_usingCDict(zcs->cctx, zcs->cdict, pledgedSrcSize))
	अन्यथा
		CHECK_F(ZSTD_compressBegin_advanced(zcs->cctx, शून्य, 0, zcs->params, pledgedSrcSize));

	zcs->inToCompress = 0;
	zcs->inBuffPos = 0;
	zcs->inBuffTarget = zcs->blockSize;
	zcs->outBuffContentSize = zcs->outBuffFlushedSize = 0;
	zcs->stage = zcss_load;
	zcs->frameEnded = 0;
	zcs->pledgedSrcSize = pledgedSrcSize;
	zcs->inputProcessed = 0;
	वापस 0; /* पढ़ोy to go */
पूर्ण

माप_प्रकार ZSTD_resetCStream(ZSTD_CStream *zcs, अचिन्हित दीर्घ दीर्घ pledgedSrcSize)
अणु

	zcs->params.fParams.contentSizeFlag = (pledgedSrcSize > 0);

	वापस ZSTD_resetCStream_पूर्णांकernal(zcs, pledgedSrcSize);
पूर्ण

अटल माप_प्रकार ZSTD_initCStream_advanced(ZSTD_CStream *zcs, स्थिर व्योम *dict, माप_प्रकार dictSize, ZSTD_parameters params, अचिन्हित दीर्घ दीर्घ pledgedSrcSize)
अणु
	/* allocate buffers */
	अणु
		माप_प्रकार स्थिर neededInBuffSize = (माप_प्रकार)1 << params.cParams.winकरोwLog;
		अगर (zcs->inBuffSize < neededInBuffSize) अणु
			zcs->inBuffSize = neededInBuffSize;
			ZSTD_मुक्त(zcs->inBuff, zcs->customMem);
			zcs->inBuff = (अक्षर *)ZSTD_दो_स्मृति(neededInBuffSize, zcs->customMem);
			अगर (zcs->inBuff == शून्य)
				वापस ERROR(memory_allocation);
		पूर्ण
		zcs->blockSize = MIN(ZSTD_BLOCKSIZE_ABSOLUTEMAX, neededInBuffSize);
	पूर्ण
	अगर (zcs->outBuffSize < ZSTD_compressBound(zcs->blockSize) + 1) अणु
		zcs->outBuffSize = ZSTD_compressBound(zcs->blockSize) + 1;
		ZSTD_मुक्त(zcs->outBuff, zcs->customMem);
		zcs->outBuff = (अक्षर *)ZSTD_दो_स्मृति(zcs->outBuffSize, zcs->customMem);
		अगर (zcs->outBuff == शून्य)
			वापस ERROR(memory_allocation);
	पूर्ण

	अगर (dict && dictSize >= 8) अणु
		ZSTD_मुक्तCDict(zcs->cdictLocal);
		zcs->cdictLocal = ZSTD_createCDict_advanced(dict, dictSize, 0, params, zcs->customMem);
		अगर (zcs->cdictLocal == शून्य)
			वापस ERROR(memory_allocation);
		zcs->cdict = zcs->cdictLocal;
	पूर्ण अन्यथा
		zcs->cdict = शून्य;

	zcs->checksum = params.fParams.checksumFlag > 0;
	zcs->params = params;

	वापस ZSTD_resetCStream_पूर्णांकernal(zcs, pledgedSrcSize);
पूर्ण

ZSTD_CStream *ZSTD_initCStream(ZSTD_parameters params, अचिन्हित दीर्घ दीर्घ pledgedSrcSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	ZSTD_customMem स्थिर stackMem = ZSTD_initStack(workspace, workspaceSize);
	ZSTD_CStream *स्थिर zcs = ZSTD_createCStream_advanced(stackMem);
	अगर (zcs) अणु
		माप_प्रकार स्थिर code = ZSTD_initCStream_advanced(zcs, शून्य, 0, params, pledgedSrcSize);
		अगर (ZSTD_isError(code)) अणु
			वापस शून्य;
		पूर्ण
	पूर्ण
	वापस zcs;
पूर्ण

ZSTD_CStream *ZSTD_initCStream_usingCDict(स्थिर ZSTD_CDict *cdict, अचिन्हित दीर्घ दीर्घ pledgedSrcSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	ZSTD_parameters स्थिर params = ZSTD_getParamsFromCDict(cdict);
	ZSTD_CStream *स्थिर zcs = ZSTD_initCStream(params, pledgedSrcSize, workspace, workspaceSize);
	अगर (zcs) अणु
		zcs->cdict = cdict;
		अगर (ZSTD_isError(ZSTD_resetCStream_पूर्णांकernal(zcs, pledgedSrcSize))) अणु
			वापस शून्य;
		पूर्ण
	पूर्ण
	वापस zcs;
पूर्ण

/*======   Compression   ======*/

प्रकार क्रमागत अणु zsf_gather, zsf_flush, zsf_end पूर्ण ZSTD_flush_e;

ZSTD_STATIC माप_प्रकार ZSTD_limitCopy(व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	माप_प्रकार स्थिर length = MIN(dstCapacity, srcSize);
	स_नकल(dst, src, length);
	वापस length;
पूर्ण

अटल माप_प्रकार ZSTD_compressStream_generic(ZSTD_CStream *zcs, व्योम *dst, माप_प्रकार *dstCapacityPtr, स्थिर व्योम *src, माप_प्रकार *srcSizePtr, ZSTD_flush_e स्थिर flush)
अणु
	U32 someMoreWork = 1;
	स्थिर अक्षर *स्थिर istart = (स्थिर अक्षर *)src;
	स्थिर अक्षर *स्थिर iend = istart + *srcSizePtr;
	स्थिर अक्षर *ip = istart;
	अक्षर *स्थिर ostart = (अक्षर *)dst;
	अक्षर *स्थिर oend = ostart + *dstCapacityPtr;
	अक्षर *op = ostart;

	जबतक (someMoreWork) अणु
		चयन (zcs->stage) अणु
		हाल zcss_init:
			वापस ERROR(init_missing); /* call ZBUFF_compressInit() first ! */

		हाल zcss_load:
			/* complete inBuffer */
			अणु
				माप_प्रकार स्थिर toLoad = zcs->inBuffTarget - zcs->inBuffPos;
				माप_प्रकार स्थिर loaded = ZSTD_limitCopy(zcs->inBuff + zcs->inBuffPos, toLoad, ip, iend - ip);
				zcs->inBuffPos += loaded;
				ip += loaded;
				अगर ((zcs->inBuffPos == zcs->inToCompress) || (!flush && (toLoad != loaded))) अणु
					someMoreWork = 0;
					अवरोध; /* not enough input to get a full block : stop there, रुको क्रम more */
				पूर्ण
			पूर्ण
			/* compress curr block (note : this stage cannot be stopped in the middle) */
			अणु
				व्योम *cDst;
				माप_प्रकार cSize;
				माप_प्रकार स्थिर iSize = zcs->inBuffPos - zcs->inToCompress;
				माप_प्रकार oSize = oend - op;
				अगर (oSize >= ZSTD_compressBound(iSize))
					cDst = op; /* compress directly पूर्णांकo output buffer (aव्योम flush stage) */
				अन्यथा
					cDst = zcs->outBuff, oSize = zcs->outBuffSize;
				cSize = (flush == zsf_end) ? ZSTD_compressEnd(zcs->cctx, cDst, oSize, zcs->inBuff + zcs->inToCompress, iSize)
							   : ZSTD_compressContinue(zcs->cctx, cDst, oSize, zcs->inBuff + zcs->inToCompress, iSize);
				अगर (ZSTD_isError(cSize))
					वापस cSize;
				अगर (flush == zsf_end)
					zcs->frameEnded = 1;
				/* prepare next block */
				zcs->inBuffTarget = zcs->inBuffPos + zcs->blockSize;
				अगर (zcs->inBuffTarget > zcs->inBuffSize)
					zcs->inBuffPos = 0, zcs->inBuffTarget = zcs->blockSize; /* note : inBuffSize >= blockSize */
				zcs->inToCompress = zcs->inBuffPos;
				अगर (cDst == op) अणु
					op += cSize;
					अवरोध;
				पूर्ण /* no need to flush */
				zcs->outBuffContentSize = cSize;
				zcs->outBuffFlushedSize = 0;
				zcs->stage = zcss_flush; /* pass-through to flush stage */
			पूर्ण
			fallthrough;

		हाल zcss_flush: अणु
			माप_प्रकार स्थिर toFlush = zcs->outBuffContentSize - zcs->outBuffFlushedSize;
			माप_प्रकार स्थिर flushed = ZSTD_limitCopy(op, oend - op, zcs->outBuff + zcs->outBuffFlushedSize, toFlush);
			op += flushed;
			zcs->outBuffFlushedSize += flushed;
			अगर (toFlush != flushed) अणु
				someMoreWork = 0;
				अवरोध;
			पूर्ण /* dst too small to store flushed data : stop there */
			zcs->outBuffContentSize = zcs->outBuffFlushedSize = 0;
			zcs->stage = zcss_load;
			अवरोध;
		पूर्ण

		हाल zcss_final:
			someMoreWork = 0; /* करो nothing */
			अवरोध;

		शेष:
			वापस ERROR(GENERIC); /* impossible */
		पूर्ण
	पूर्ण

	*srcSizePtr = ip - istart;
	*dstCapacityPtr = op - ostart;
	zcs->inputProcessed += *srcSizePtr;
	अगर (zcs->frameEnded)
		वापस 0;
	अणु
		माप_प्रकार hपूर्णांकInSize = zcs->inBuffTarget - zcs->inBuffPos;
		अगर (hपूर्णांकInSize == 0)
			hपूर्णांकInSize = zcs->blockSize;
		वापस hपूर्णांकInSize;
	पूर्ण
पूर्ण

माप_प्रकार ZSTD_compressStream(ZSTD_CStream *zcs, ZSTD_outBuffer *output, ZSTD_inBuffer *input)
अणु
	माप_प्रकार sizeRead = input->size - input->pos;
	माप_प्रकार sizeWritten = output->size - output->pos;
	माप_प्रकार स्थिर result =
	    ZSTD_compressStream_generic(zcs, (अक्षर *)(output->dst) + output->pos, &sizeWritten, (स्थिर अक्षर *)(input->src) + input->pos, &sizeRead, zsf_gather);
	input->pos += sizeRead;
	output->pos += sizeWritten;
	वापस result;
पूर्ण

/*======   Finalize   ======*/

/*! ZSTD_flushStream() :
*   @वापस : amount of data reमुख्यing to flush */
माप_प्रकार ZSTD_flushStream(ZSTD_CStream *zcs, ZSTD_outBuffer *output)
अणु
	माप_प्रकार srcSize = 0;
	माप_प्रकार sizeWritten = output->size - output->pos;
	माप_प्रकार स्थिर result = ZSTD_compressStream_generic(zcs, (अक्षर *)(output->dst) + output->pos, &sizeWritten, &srcSize,
							  &srcSize, /* use a valid src address instead of शून्य */
							  zsf_flush);
	output->pos += sizeWritten;
	अगर (ZSTD_isError(result))
		वापस result;
	वापस zcs->outBuffContentSize - zcs->outBuffFlushedSize; /* reमुख्यing to flush */
पूर्ण

माप_प्रकार ZSTD_endStream(ZSTD_CStream *zcs, ZSTD_outBuffer *output)
अणु
	BYTE *स्थिर ostart = (BYTE *)(output->dst) + output->pos;
	BYTE *स्थिर oend = (BYTE *)(output->dst) + output->size;
	BYTE *op = ostart;

	अगर ((zcs->pledgedSrcSize) && (zcs->inputProcessed != zcs->pledgedSrcSize))
		वापस ERROR(srcSize_wrong); /* pledgedSrcSize not respected */

	अगर (zcs->stage != zcss_final) अणु
		/* flush whatever reमुख्यs */
		माप_प्रकार srcSize = 0;
		माप_प्रकार sizeWritten = output->size - output->pos;
		माप_प्रकार स्थिर notEnded =
		    ZSTD_compressStream_generic(zcs, ostart, &sizeWritten, &srcSize, &srcSize, zsf_end); /* use a valid src address instead of शून्य */
		माप_प्रकार स्थिर reमुख्यingToFlush = zcs->outBuffContentSize - zcs->outBuffFlushedSize;
		op += sizeWritten;
		अगर (reमुख्यingToFlush) अणु
			output->pos += sizeWritten;
			वापस reमुख्यingToFlush + ZSTD_BLOCKHEADERSIZE /* final empty block */ + (zcs->checksum * 4);
		पूर्ण
		/* create epilogue */
		zcs->stage = zcss_final;
		zcs->outBuffContentSize = !notEnded ? 0 : ZSTD_compressEnd(zcs->cctx, zcs->outBuff, zcs->outBuffSize, शून्य,
									   0); /* ग_लिखो epilogue, including final empty block, पूर्णांकo outBuff */
	पूर्ण

	/* flush epilogue */
	अणु
		माप_प्रकार स्थिर toFlush = zcs->outBuffContentSize - zcs->outBuffFlushedSize;
		माप_प्रकार स्थिर flushed = ZSTD_limitCopy(op, oend - op, zcs->outBuff + zcs->outBuffFlushedSize, toFlush);
		op += flushed;
		zcs->outBuffFlushedSize += flushed;
		output->pos += op - ostart;
		अगर (toFlush == flushed)
			zcs->stage = zcss_init; /* end reached */
		वापस toFlush - flushed;
	पूर्ण
पूर्ण

/*-=====  Pre-defined compression levels  =====-*/

#घोषणा ZSTD_DEFAULT_CLEVEL 1
#घोषणा ZSTD_MAX_CLEVEL 22
पूर्णांक ZSTD_maxCLevel(व्योम) अणु वापस ZSTD_MAX_CLEVEL; पूर्ण

अटल स्थिर ZSTD_compressionParameters ZSTD_शेषCParameters[4][ZSTD_MAX_CLEVEL + 1] = अणु
    अणु
	/* "default" */
	/* W,  C,  H,  S,  L, TL, strat */
	अणु18, 12, 12, 1, 7, 16, ZSTD_fastपूर्ण,    /* level  0 - never used */
	अणु19, 13, 14, 1, 7, 16, ZSTD_fastपूर्ण,    /* level  1 */
	अणु19, 15, 16, 1, 6, 16, ZSTD_fastपूर्ण,    /* level  2 */
	अणु20, 16, 17, 1, 5, 16, ZSTD_dfastपूर्ण,   /* level  3.*/
	अणु20, 18, 18, 1, 5, 16, ZSTD_dfastपूर्ण,   /* level  4.*/
	अणु20, 15, 18, 3, 5, 16, ZSTD_greedyपूर्ण,  /* level  5 */
	अणु21, 16, 19, 2, 5, 16, ZSTD_lazyपूर्ण,    /* level  6 */
	अणु21, 17, 20, 3, 5, 16, ZSTD_lazyपूर्ण,    /* level  7 */
	अणु21, 18, 20, 3, 5, 16, ZSTD_lazy2पूर्ण,   /* level  8 */
	अणु21, 20, 20, 3, 5, 16, ZSTD_lazy2पूर्ण,   /* level  9 */
	अणु21, 19, 21, 4, 5, 16, ZSTD_lazy2पूर्ण,   /* level 10 */
	अणु22, 20, 22, 4, 5, 16, ZSTD_lazy2पूर्ण,   /* level 11 */
	अणु22, 20, 22, 5, 5, 16, ZSTD_lazy2पूर्ण,   /* level 12 */
	अणु22, 21, 22, 5, 5, 16, ZSTD_lazy2पूर्ण,   /* level 13 */
	अणु22, 21, 22, 6, 5, 16, ZSTD_lazy2पूर्ण,   /* level 14 */
	अणु22, 21, 21, 5, 5, 16, ZSTD_btlazy2पूर्ण, /* level 15 */
	अणु23, 22, 22, 5, 5, 16, ZSTD_btlazy2पूर्ण, /* level 16 */
	अणु23, 21, 22, 4, 5, 24, ZSTD_btoptपूर्ण,   /* level 17 */
	अणु23, 23, 22, 6, 5, 32, ZSTD_btoptपूर्ण,   /* level 18 */
	अणु23, 23, 22, 6, 3, 48, ZSTD_btoptपूर्ण,   /* level 19 */
	अणु25, 25, 23, 7, 3, 64, ZSTD_btopt2पूर्ण,  /* level 20 */
	अणु26, 26, 23, 7, 3, 256, ZSTD_btopt2पूर्ण, /* level 21 */
	अणु27, 27, 25, 9, 3, 512, ZSTD_btopt2पूर्ण, /* level 22 */
    पूर्ण,
    अणु
	/* क्रम srcSize <= 256 KB */
	/* W,  C,  H,  S,  L,  T, strat */
	अणु0, 0, 0, 0, 0, 0, ZSTD_fastपूर्ण,	 /* level  0 - not used */
	अणु18, 13, 14, 1, 6, 8, ZSTD_fastपूर्ण,      /* level  1 */
	अणु18, 14, 13, 1, 5, 8, ZSTD_dfastपूर्ण,     /* level  2 */
	अणु18, 16, 15, 1, 5, 8, ZSTD_dfastपूर्ण,     /* level  3 */
	अणु18, 15, 17, 1, 5, 8, ZSTD_greedyपूर्ण,    /* level  4.*/
	अणु18, 16, 17, 4, 5, 8, ZSTD_greedyपूर्ण,    /* level  5.*/
	अणु18, 16, 17, 3, 5, 8, ZSTD_lazyपूर्ण,      /* level  6.*/
	अणु18, 17, 17, 4, 4, 8, ZSTD_lazyपूर्ण,      /* level  7 */
	अणु18, 17, 17, 4, 4, 8, ZSTD_lazy2पूर्ण,     /* level  8 */
	अणु18, 17, 17, 5, 4, 8, ZSTD_lazy2पूर्ण,     /* level  9 */
	अणु18, 17, 17, 6, 4, 8, ZSTD_lazy2पूर्ण,     /* level 10 */
	अणु18, 18, 17, 6, 4, 8, ZSTD_lazy2पूर्ण,     /* level 11.*/
	अणु18, 18, 17, 7, 4, 8, ZSTD_lazy2पूर्ण,     /* level 12.*/
	अणु18, 19, 17, 6, 4, 8, ZSTD_btlazy2पूर्ण,   /* level 13 */
	अणु18, 18, 18, 4, 4, 16, ZSTD_btoptपूर्ण,    /* level 14.*/
	अणु18, 18, 18, 4, 3, 16, ZSTD_btoptपूर्ण,    /* level 15.*/
	अणु18, 19, 18, 6, 3, 32, ZSTD_btoptपूर्ण,    /* level 16.*/
	अणु18, 19, 18, 8, 3, 64, ZSTD_btoptपूर्ण,    /* level 17.*/
	अणु18, 19, 18, 9, 3, 128, ZSTD_btoptपूर्ण,   /* level 18.*/
	अणु18, 19, 18, 10, 3, 256, ZSTD_btoptपूर्ण,  /* level 19.*/
	अणु18, 19, 18, 11, 3, 512, ZSTD_btopt2पूर्ण, /* level 20.*/
	अणु18, 19, 18, 12, 3, 512, ZSTD_btopt2पूर्ण, /* level 21.*/
	अणु18, 19, 18, 13, 3, 512, ZSTD_btopt2पूर्ण, /* level 22.*/
    पूर्ण,
    अणु
	/* क्रम srcSize <= 128 KB */
	/* W,  C,  H,  S,  L,  T, strat */
	अणु17, 12, 12, 1, 7, 8, ZSTD_fastपूर्ण,      /* level  0 - not used */
	अणु17, 12, 13, 1, 6, 8, ZSTD_fastपूर्ण,      /* level  1 */
	अणु17, 13, 16, 1, 5, 8, ZSTD_fastपूर्ण,      /* level  2 */
	अणु17, 16, 16, 2, 5, 8, ZSTD_dfastपूर्ण,     /* level  3 */
	अणु17, 13, 15, 3, 4, 8, ZSTD_greedyपूर्ण,    /* level  4 */
	अणु17, 15, 17, 4, 4, 8, ZSTD_greedyपूर्ण,    /* level  5 */
	अणु17, 16, 17, 3, 4, 8, ZSTD_lazyपूर्ण,      /* level  6 */
	अणु17, 15, 17, 4, 4, 8, ZSTD_lazy2पूर्ण,     /* level  7 */
	अणु17, 17, 17, 4, 4, 8, ZSTD_lazy2पूर्ण,     /* level  8 */
	अणु17, 17, 17, 5, 4, 8, ZSTD_lazy2पूर्ण,     /* level  9 */
	अणु17, 17, 17, 6, 4, 8, ZSTD_lazy2पूर्ण,     /* level 10 */
	अणु17, 17, 17, 7, 4, 8, ZSTD_lazy2पूर्ण,     /* level 11 */
	अणु17, 17, 17, 8, 4, 8, ZSTD_lazy2पूर्ण,     /* level 12 */
	अणु17, 18, 17, 6, 4, 8, ZSTD_btlazy2पूर्ण,   /* level 13.*/
	अणु17, 17, 17, 7, 3, 8, ZSTD_btoptपूर्ण,     /* level 14.*/
	अणु17, 17, 17, 7, 3, 16, ZSTD_btoptपूर्ण,    /* level 15.*/
	अणु17, 18, 17, 7, 3, 32, ZSTD_btoptपूर्ण,    /* level 16.*/
	अणु17, 18, 17, 7, 3, 64, ZSTD_btoptपूर्ण,    /* level 17.*/
	अणु17, 18, 17, 7, 3, 256, ZSTD_btoptपूर्ण,   /* level 18.*/
	अणु17, 18, 17, 8, 3, 256, ZSTD_btoptपूर्ण,   /* level 19.*/
	अणु17, 18, 17, 9, 3, 256, ZSTD_btopt2पूर्ण,  /* level 20.*/
	अणु17, 18, 17, 10, 3, 256, ZSTD_btopt2पूर्ण, /* level 21.*/
	अणु17, 18, 17, 11, 3, 512, ZSTD_btopt2पूर्ण, /* level 22.*/
    पूर्ण,
    अणु
	/* क्रम srcSize <= 16 KB */
	/* W,  C,  H,  S,  L,  T, strat */
	अणु14, 12, 12, 1, 7, 6, ZSTD_fastपूर्ण,      /* level  0 - not used */
	अणु14, 14, 14, 1, 6, 6, ZSTD_fastपूर्ण,      /* level  1 */
	अणु14, 14, 14, 1, 4, 6, ZSTD_fastपूर्ण,      /* level  2 */
	अणु14, 14, 14, 1, 4, 6, ZSTD_dfastपूर्ण,     /* level  3.*/
	अणु14, 14, 14, 4, 4, 6, ZSTD_greedyपूर्ण,    /* level  4.*/
	अणु14, 14, 14, 3, 4, 6, ZSTD_lazyपूर्ण,      /* level  5.*/
	अणु14, 14, 14, 4, 4, 6, ZSTD_lazy2पूर्ण,     /* level  6 */
	अणु14, 14, 14, 5, 4, 6, ZSTD_lazy2पूर्ण,     /* level  7 */
	अणु14, 14, 14, 6, 4, 6, ZSTD_lazy2पूर्ण,     /* level  8.*/
	अणु14, 15, 14, 6, 4, 6, ZSTD_btlazy2पूर्ण,   /* level  9.*/
	अणु14, 15, 14, 3, 3, 6, ZSTD_btoptपूर्ण,     /* level 10.*/
	अणु14, 15, 14, 6, 3, 8, ZSTD_btoptपूर्ण,     /* level 11.*/
	अणु14, 15, 14, 6, 3, 16, ZSTD_btoptपूर्ण,    /* level 12.*/
	अणु14, 15, 14, 6, 3, 24, ZSTD_btoptपूर्ण,    /* level 13.*/
	अणु14, 15, 15, 6, 3, 48, ZSTD_btoptपूर्ण,    /* level 14.*/
	अणु14, 15, 15, 6, 3, 64, ZSTD_btoptपूर्ण,    /* level 15.*/
	अणु14, 15, 15, 6, 3, 96, ZSTD_btoptपूर्ण,    /* level 16.*/
	अणु14, 15, 15, 6, 3, 128, ZSTD_btoptपूर्ण,   /* level 17.*/
	अणु14, 15, 15, 6, 3, 256, ZSTD_btoptपूर्ण,   /* level 18.*/
	अणु14, 15, 15, 7, 3, 256, ZSTD_btoptपूर्ण,   /* level 19.*/
	अणु14, 15, 15, 8, 3, 256, ZSTD_btopt2पूर्ण,  /* level 20.*/
	अणु14, 15, 15, 9, 3, 256, ZSTD_btopt2पूर्ण,  /* level 21.*/
	अणु14, 15, 15, 10, 3, 256, ZSTD_btopt2पूर्ण, /* level 22.*/
    पूर्ण,
पूर्ण;

/*! ZSTD_getCParams() :
*   @वापस ZSTD_compressionParameters काष्ठाure क्रम a selected compression level, `srcSize` and `dictSize`.
*   Size values are optional, provide 0 अगर not known or unused */
ZSTD_compressionParameters ZSTD_getCParams(पूर्णांक compressionLevel, अचिन्हित दीर्घ दीर्घ srcSize, माप_प्रकार dictSize)
अणु
	ZSTD_compressionParameters cp;
	माप_प्रकार स्थिर addedSize = srcSize ? 0 : 500;
	U64 स्थिर rSize = srcSize + dictSize ? srcSize + dictSize + addedSize : (U64)-1;
	U32 स्थिर tableID = (rSize <= 256 KB) + (rSize <= 128 KB) + (rSize <= 16 KB); /* पूर्णांकentional underflow क्रम srcSizeHपूर्णांक == 0 */
	अगर (compressionLevel <= 0)
		compressionLevel = ZSTD_DEFAULT_CLEVEL; /* 0 == शेष; no negative compressionLevel yet */
	अगर (compressionLevel > ZSTD_MAX_CLEVEL)
		compressionLevel = ZSTD_MAX_CLEVEL;
	cp = ZSTD_शेषCParameters[tableID][compressionLevel];
	अगर (ZSTD_32bits()) अणु /* स्वतः-correction, क्रम 32-bits mode */
		अगर (cp.winकरोwLog > ZSTD_WINDOWLOG_MAX)
			cp.winकरोwLog = ZSTD_WINDOWLOG_MAX;
		अगर (cp.chainLog > ZSTD_CHAINLOG_MAX)
			cp.chainLog = ZSTD_CHAINLOG_MAX;
		अगर (cp.hashLog > ZSTD_HASHLOG_MAX)
			cp.hashLog = ZSTD_HASHLOG_MAX;
	पूर्ण
	cp = ZSTD_adjustCParams(cp, srcSize, dictSize);
	वापस cp;
पूर्ण

/*! ZSTD_getParams() :
*   same as ZSTD_getCParams(), but @वापस a `ZSTD_parameters` object (instead of `ZSTD_compressionParameters`).
*   All fields of `ZSTD_frameParameters` are set to शेष (0) */
ZSTD_parameters ZSTD_getParams(पूर्णांक compressionLevel, अचिन्हित दीर्घ दीर्घ srcSize, माप_प्रकार dictSize)
अणु
	ZSTD_parameters params;
	ZSTD_compressionParameters स्थिर cParams = ZSTD_getCParams(compressionLevel, srcSize, dictSize);
	स_रखो(&params, 0, माप(params));
	params.cParams = cParams;
	वापस params;
पूर्ण

EXPORT_SYMBOL(ZSTD_maxCLevel);
EXPORT_SYMBOL(ZSTD_compressBound);

EXPORT_SYMBOL(ZSTD_CCtxWorkspaceBound);
EXPORT_SYMBOL(ZSTD_initCCtx);
EXPORT_SYMBOL(ZSTD_compressCCtx);
EXPORT_SYMBOL(ZSTD_compress_usingDict);

EXPORT_SYMBOL(ZSTD_CDictWorkspaceBound);
EXPORT_SYMBOL(ZSTD_initCDict);
EXPORT_SYMBOL(ZSTD_compress_usingCDict);

EXPORT_SYMBOL(ZSTD_CStreamWorkspaceBound);
EXPORT_SYMBOL(ZSTD_initCStream);
EXPORT_SYMBOL(ZSTD_initCStream_usingCDict);
EXPORT_SYMBOL(ZSTD_resetCStream);
EXPORT_SYMBOL(ZSTD_compressStream);
EXPORT_SYMBOL(ZSTD_flushStream);
EXPORT_SYMBOL(ZSTD_endStream);
EXPORT_SYMBOL(ZSTD_CStreamInSize);
EXPORT_SYMBOL(ZSTD_CStreamOutSize);

EXPORT_SYMBOL(ZSTD_getCParams);
EXPORT_SYMBOL(ZSTD_getParams);
EXPORT_SYMBOL(ZSTD_checkCParams);
EXPORT_SYMBOL(ZSTD_adjustCParams);

EXPORT_SYMBOL(ZSTD_compressBegin);
EXPORT_SYMBOL(ZSTD_compressBegin_usingDict);
EXPORT_SYMBOL(ZSTD_compressBegin_advanced);
EXPORT_SYMBOL(ZSTD_copyCCtx);
EXPORT_SYMBOL(ZSTD_compressBegin_usingCDict);
EXPORT_SYMBOL(ZSTD_compressContinue);
EXPORT_SYMBOL(ZSTD_compressEnd);

EXPORT_SYMBOL(ZSTD_getBlockSizeMax);
EXPORT_SYMBOL(ZSTD_compressBlock);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Zstd Compressor");
