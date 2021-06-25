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

#अगर_अघोषित ZSTD_CCOMMON_H_MODULE
#घोषणा ZSTD_CCOMMON_H_MODULE

/*-*******************************************************
*  Compiler specअगरics
*********************************************************/
#घोषणा FORCE_INLINE अटल __always_अंतरभूत
#घोषणा FORCE_NOINLINE अटल noअंतरभूत

/*-*************************************
*  Dependencies
***************************************/
#समावेश "error_private.h"
#समावेश "mem.h"
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/xxhash.h>
#समावेश <linux/zstd.h>

/*-*************************************
*  shared macros
***************************************/
#घोषणा MIN(a, b) ((a) < (b) ? (a) : (b))
#घोषणा MAX(a, b) ((a) > (b) ? (a) : (b))
#घोषणा CHECK_F(f)                       \
	अणु                                \
		माप_प्रकार स्थिर errcod = f; \
		अगर (ERR_isError(errcod)) \
			वापस errcod;   \
	पूर्ण /* check and Forward error code */
#घोषणा CHECK_E(f, e)                    \
	अणु                                \
		माप_प्रकार स्थिर errcod = f; \
		अगर (ERR_isError(errcod)) \
			वापस ERROR(e); \
	पूर्ण /* check and send Error code */
#घोषणा ZSTD_STATIC_ASSERT(c)                                   \
	अणु                                                       \
		क्रमागत अणु ZSTD_अटल_निश्चित = 1 / (पूर्णांक)(!!(c)) पूर्ण; \
	पूर्ण

/*-*************************************
*  Common स्थिरants
***************************************/
#घोषणा ZSTD_OPT_NUM (1 << 12)
#घोषणा ZSTD_DICT_MAGIC 0xEC30A437 /* v0.7+ */

#घोषणा ZSTD_REP_NUM 3		      /* number of repcodes */
#घोषणा ZSTD_REP_CHECK (ZSTD_REP_NUM) /* number of repcodes to check by the optimal parser */
#घोषणा ZSTD_REP_MOVE (ZSTD_REP_NUM - 1)
#घोषणा ZSTD_REP_MOVE_OPT (ZSTD_REP_NUM)
अटल स्थिर U32 repStartValue[ZSTD_REP_NUM] = अणु1, 4, 8पूर्ण;

#घोषणा KB *(1 << 10)
#घोषणा MB *(1 << 20)
#घोषणा GB *(1U << 30)

#घोषणा BIT7 128
#घोषणा BIT6 64
#घोषणा BIT5 32
#घोषणा BIT4 16
#घोषणा BIT1 2
#घोषणा BIT0 1

#घोषणा ZSTD_WINDOWLOG_ABSOLUTEMIN 10
अटल स्थिर माप_प्रकार ZSTD_fcs_fieldSize[4] = अणु0, 2, 4, 8पूर्ण;
अटल स्थिर माप_प्रकार ZSTD_did_fieldSize[4] = अणु0, 1, 2, 4पूर्ण;

#घोषणा ZSTD_BLOCKHEADERSIZE 3 /* C standard करोesn't allow `अटल स्थिर` variable to be init using another `अटल स्थिर` variable */
अटल स्थिर माप_प्रकार ZSTD_blockHeaderSize = ZSTD_BLOCKHEADERSIZE;
प्रकार क्रमागत अणु bt_raw, bt_rle, bt_compressed, bt_reserved पूर्ण blockType_e;

#घोषणा MIN_SEQUENCES_SIZE 1									  /* nbSeq==0 */
#घोषणा MIN_CBLOCK_SIZE (1 /*litCSize*/ + 1 /* RLE or RAW */ + MIN_SEQUENCES_SIZE /* nbSeq==0 */) /* क्रम a non-null block */

#घोषणा HufLog 12
प्रकार क्रमागत अणु set_basic, set_rle, set_compressed, set_repeat पूर्ण symbolEncodingType_e;

#घोषणा LONGNBSEQ 0x7F00

#घोषणा MINMATCH 3
#घोषणा EQUAL_READ32 4

#घोषणा Litbits 8
#घोषणा MaxLit ((1 << Litbits) - 1)
#घोषणा MaxML 52
#घोषणा MaxLL 35
#घोषणा MaxOff 28
#घोषणा MaxSeq MAX(MaxLL, MaxML) /* Assumption : MaxOff < MaxLL,MaxML */
#घोषणा MLFSELog 9
#घोषणा LLFSELog 9
#घोषणा OffFSELog 8

अटल स्थिर U32 LL_bits[MaxLL + 1] = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16पूर्ण;
अटल स्थिर S16 LL_शेषNorm[MaxLL + 1] = अणु4, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 1, 1, 1, 1, 1, -1, -1, -1, -1पूर्ण;
#घोषणा LL_DEFAULTNORMLOG 6 /* क्रम अटल allocation */
अटल स्थिर U32 LL_शेषNormLog = LL_DEFAULTNORMLOG;

अटल स्थिर U32 ML_bits[MaxML + 1] = अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0,
				       0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16पूर्ण;
अटल स्थिर S16 ML_शेषNorm[MaxML + 1] = अणु1, 4, 3, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1, 1,
					      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1पूर्ण;
#घोषणा ML_DEFAULTNORMLOG 6 /* क्रम अटल allocation */
अटल स्थिर U32 ML_शेषNormLog = ML_DEFAULTNORMLOG;

अटल स्थिर S16 OF_शेषNorm[MaxOff + 1] = अणु1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1पूर्ण;
#घोषणा OF_DEFAULTNORMLOG 5 /* क्रम अटल allocation */
अटल स्थिर U32 OF_शेषNormLog = OF_DEFAULTNORMLOG;

/*-*******************************************
*  Shared functions to include क्रम inlining
*********************************************/
ZSTD_STATIC व्योम ZSTD_copy8(व्योम *dst, स्थिर व्योम *src) अणु
	/*
	 * zstd relies heavily on gcc being able to analyze and अंतरभूत this
	 * स_नकल() call, since it is called in a tight loop. Preboot mode
	 * is compiled in मुक्तstanding mode, which stops gcc from analyzing
	 * स_नकल(). Use __builtin_स_नकल() to tell gcc to analyze this as a
	 * regular स_नकल().
	 */
	__builtin_स_नकल(dst, src, 8);
पूर्ण
/*! ZSTD_wildcopy() :
*   custom version of स_नकल(), can copy up to 7 bytes too many (8 bytes अगर length==0) */
#घोषणा WILDCOPY_OVERLENGTH 8
ZSTD_STATIC व्योम ZSTD_wildcopy(व्योम *dst, स्थिर व्योम *src, सूचक_भेद_प्रकार length)
अणु
	स्थिर BYTE* ip = (स्थिर BYTE*)src;
	BYTE* op = (BYTE*)dst;
	BYTE* स्थिर oend = op + length;
#अगर defined(GCC_VERSION) && GCC_VERSION >= 70000 && GCC_VERSION < 70200
	/*
	 * Work around https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81388.
	 * Aव्योम the bad हाल where the loop only runs once by handling the
	 * special हाल separately. This करोesn't trigger the bug because it
	 * करोesn't involve poपूर्णांकer/पूर्णांकeger overflow.
	 */
	अगर (length <= 8)
		वापस ZSTD_copy8(dst, src);
#पूर्ण_अगर
	करो अणु
		ZSTD_copy8(op, ip);
		op += 8;
		ip += 8;
	पूर्ण जबतक (op < oend);
पूर्ण

/*-*******************************************
*  Private पूर्णांकerfaces
*********************************************/
प्रकार काष्ठा ZSTD_stats_s ZSTD_stats_t;

प्रकार काष्ठा अणु
	U32 off;
	U32 len;
पूर्ण ZSTD_match_t;

प्रकार काष्ठा अणु
	U32 price;
	U32 off;
	U32 mlen;
	U32 litlen;
	U32 rep[ZSTD_REP_NUM];
पूर्ण ZSTD_optimal_t;

प्रकार काष्ठा seqDef_s अणु
	U32 offset;
	U16 litLength;
	U16 matchLength;
पूर्ण seqDef;

प्रकार काष्ठा अणु
	seqDef *sequencesStart;
	seqDef *sequences;
	BYTE *litStart;
	BYTE *lit;
	BYTE *llCode;
	BYTE *mlCode;
	BYTE *ofCode;
	U32 दीर्घLengthID; /* 0 == no दीर्घLength; 1 == Lit.दीर्घLength; 2 == Match.दीर्घLength; */
	U32 दीर्घLengthPos;
	/* opt */
	ZSTD_optimal_t *priceTable;
	ZSTD_match_t *matchTable;
	U32 *matchLengthFreq;
	U32 *litLengthFreq;
	U32 *litFreq;
	U32 *offCodeFreq;
	U32 matchLengthSum;
	U32 matchSum;
	U32 litLengthSum;
	U32 litSum;
	U32 offCodeSum;
	U32 log2matchLengthSum;
	U32 log2matchSum;
	U32 log2litLengthSum;
	U32 log2litSum;
	U32 log2offCodeSum;
	U32 factor;
	U32 अटलPrices;
	U32 cachedPrice;
	U32 cachedLitLength;
	स्थिर BYTE *cachedLiterals;
पूर्ण seqStore_t;

स्थिर seqStore_t *ZSTD_getSeqStore(स्थिर ZSTD_CCtx *ctx);
व्योम ZSTD_seqToCodes(स्थिर seqStore_t *seqStorePtr);
पूर्णांक ZSTD_isSkipFrame(ZSTD_DCtx *dctx);

/*= Custom memory allocation functions */
प्रकार व्योम *(*ZSTD_allocFunction)(व्योम *opaque, माप_प्रकार size);
प्रकार व्योम (*ZSTD_मुक्तFunction)(व्योम *opaque, व्योम *address);
प्रकार काष्ठा अणु
	ZSTD_allocFunction customAlloc;
	ZSTD_मुक्तFunction customFree;
	व्योम *opaque;
पूर्ण ZSTD_customMem;

व्योम *ZSTD_दो_स्मृति(माप_प्रकार size, ZSTD_customMem customMem);
व्योम ZSTD_मुक्त(व्योम *ptr, ZSTD_customMem customMem);

/*====== stack allocation  ======*/

प्रकार काष्ठा अणु
	व्योम *ptr;
	स्थिर व्योम *end;
पूर्ण ZSTD_stack;

#घोषणा ZSTD_ALIGN(x) ALIGN(x, माप(माप_प्रकार))
#घोषणा ZSTD_PTR_ALIGN(p) PTR_ALIGN(p, माप(माप_प्रकार))

ZSTD_customMem ZSTD_initStack(व्योम *workspace, माप_प्रकार workspaceSize);

व्योम *ZSTD_stackAllocAll(व्योम *opaque, माप_प्रकार *size);
व्योम *ZSTD_stackAlloc(व्योम *opaque, माप_प्रकार size);
व्योम ZSTD_stackFree(व्योम *opaque, व्योम *address);

/*======  common function  ======*/

ZSTD_STATIC U32 ZSTD_highbit32(U32 val) अणु वापस 31 - __builtin_clz(val); पूर्ण

/* hidden functions */

/* ZSTD_invalidateRepCodes() :
 * ensures next compression will not use repcodes from previous block.
 * Note : only works with regular variant;
 *        करो not use with extDict variant ! */
व्योम ZSTD_invalidateRepCodes(ZSTD_CCtx *cctx);

माप_प्रकार ZSTD_मुक्तCCtx(ZSTD_CCtx *cctx);
माप_प्रकार ZSTD_मुक्तDCtx(ZSTD_DCtx *dctx);
माप_प्रकार ZSTD_मुक्तCDict(ZSTD_CDict *cdict);
माप_प्रकार ZSTD_मुक्तDDict(ZSTD_DDict *cdict);
माप_प्रकार ZSTD_मुक्तCStream(ZSTD_CStream *zcs);
माप_प्रकार ZSTD_मुक्तDStream(ZSTD_DStream *zds);

#पूर्ण_अगर /* ZSTD_CCOMMON_H_MODULE */
