<शैली गुरु>
/*
 * Huffman decoder, part of New Generation Entropy library
 * Copyright (C) 2013-2016, Yann Collet.
 *
 * BSD 2-Clause License (http://www.खोलोsource.org/licenses/bsd-license.php)
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the करोcumentation and/or other materials provided with the
 * distribution.
 *
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
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it under
 * the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation. This program is dual-licensed; you may select
 * either version 2 of the GNU General Public License ("GPL") or BSD license
 * ("BSD").
 *
 * You can contact the author at :
 * - Source repository : https://github.com/Cyan4973/FiniteStateEntropy
 */

/* **************************************************************
*  Compiler specअगरics
****************************************************************/
#घोषणा FORCE_INLINE अटल __always_अंतरभूत

/* **************************************************************
*  Dependencies
****************************************************************/
#समावेश "bitstream.h" /* BIT_* */
#समावेश "fse.h"       /* header compression */
#समावेश "huf.h"
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स> /* स_नकल, स_रखो */

/* **************************************************************
*  Error Management
****************************************************************/
#घोषणा HUF_STATIC_ASSERT(c)                                   \
	अणु                                                      \
		क्रमागत अणु HUF_अटल_निश्चित = 1 / (पूर्णांक)(!!(c)) पूर्ण; \
	पूर्ण /* use only *after* variable declarations */

/*-***************************/
/*  generic DTableDesc       */
/*-***************************/

प्रकार काष्ठा अणु
	BYTE maxTableLog;
	BYTE tableType;
	BYTE tableLog;
	BYTE reserved;
पूर्ण DTableDesc;

अटल DTableDesc HUF_getDTableDesc(स्थिर HUF_DTable *table)
अणु
	DTableDesc dtd;
	स_नकल(&dtd, table, माप(dtd));
	वापस dtd;
पूर्ण

/*-***************************/
/*  single-symbol decoding   */
/*-***************************/

प्रकार काष्ठा अणु
	BYTE byte;
	BYTE nbBits;
पूर्ण HUF_DEltX2; /* single-symbol decoding */

माप_प्रकार HUF_पढ़ोDTableX2_wksp(HUF_DTable *DTable, स्थिर व्योम *src, माप_प्रकार srcSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	U32 tableLog = 0;
	U32 nbSymbols = 0;
	माप_प्रकार iSize;
	व्योम *स्थिर dtPtr = DTable + 1;
	HUF_DEltX2 *स्थिर dt = (HUF_DEltX2 *)dtPtr;

	U32 *rankVal;
	BYTE *huffWeight;
	माप_प्रकार spaceUsed32 = 0;

	rankVal = (U32 *)workspace + spaceUsed32;
	spaceUsed32 += HUF_TABLELOG_ABSOLUTEMAX + 1;
	huffWeight = (BYTE *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += ALIGN(HUF_SYMBOLVALUE_MAX + 1, माप(U32)) >> 2;

	अगर ((spaceUsed32 << 2) > workspaceSize)
		वापस ERROR(tableLog_tooLarge);
	workspace = (U32 *)workspace + spaceUsed32;
	workspaceSize -= (spaceUsed32 << 2);

	HUF_STATIC_ASSERT(माप(DTableDesc) == माप(HUF_DTable));
	/* स_रखो(huffWeight, 0, माप(huffWeight)); */ /* is not necessary, even though some analyzer complain ... */

	iSize = HUF_पढ़ोStats_wksp(huffWeight, HUF_SYMBOLVALUE_MAX + 1, rankVal, &nbSymbols, &tableLog, src, srcSize, workspace, workspaceSize);
	अगर (HUF_isError(iSize))
		वापस iSize;

	/* Table header */
	अणु
		DTableDesc dtd = HUF_getDTableDesc(DTable);
		अगर (tableLog > (U32)(dtd.maxTableLog + 1))
			वापस ERROR(tableLog_tooLarge); /* DTable too small, Huffman tree cannot fit in */
		dtd.tableType = 0;
		dtd.tableLog = (BYTE)tableLog;
		स_नकल(DTable, &dtd, माप(dtd));
	पूर्ण

	/* Calculate starting value क्रम each rank */
	अणु
		U32 n, nextRankStart = 0;
		क्रम (n = 1; n < tableLog + 1; n++) अणु
			U32 स्थिर curr = nextRankStart;
			nextRankStart += (rankVal[n] << (n - 1));
			rankVal[n] = curr;
		पूर्ण
	पूर्ण

	/* fill DTable */
	अणु
		U32 n;
		क्रम (n = 0; n < nbSymbols; n++) अणु
			U32 स्थिर w = huffWeight[n];
			U32 स्थिर length = (1 << w) >> 1;
			U32 u;
			HUF_DEltX2 D;
			D.byte = (BYTE)n;
			D.nbBits = (BYTE)(tableLog + 1 - w);
			क्रम (u = rankVal[w]; u < rankVal[w] + length; u++)
				dt[u] = D;
			rankVal[w] += length;
		पूर्ण
	पूर्ण

	वापस iSize;
पूर्ण

अटल BYTE HUF_decodeSymbolX2(BIT_DStream_t *Dstream, स्थिर HUF_DEltX2 *dt, स्थिर U32 dtLog)
अणु
	माप_प्रकार स्थिर val = BIT_lookBitsFast(Dstream, dtLog); /* note : dtLog >= 1 */
	BYTE स्थिर c = dt[val].byte;
	BIT_skipBits(Dstream, dt[val].nbBits);
	वापस c;
पूर्ण

#घोषणा HUF_DECODE_SYMBOLX2_0(ptr, DStreamPtr) *ptr++ = HUF_decodeSymbolX2(DStreamPtr, dt, dtLog)

#घोषणा HUF_DECODE_SYMBOLX2_1(ptr, DStreamPtr)         \
	अगर (ZSTD_64bits() || (HUF_TABLELOG_MAX <= 12)) \
	HUF_DECODE_SYMBOLX2_0(ptr, DStreamPtr)

#घोषणा HUF_DECODE_SYMBOLX2_2(ptr, DStreamPtr) \
	अगर (ZSTD_64bits())                     \
	HUF_DECODE_SYMBOLX2_0(ptr, DStreamPtr)

FORCE_INLINE माप_प्रकार HUF_decodeStreamX2(BYTE *p, BIT_DStream_t *स्थिर bitDPtr, BYTE *स्थिर pEnd, स्थिर HUF_DEltX2 *स्थिर dt, स्थिर U32 dtLog)
अणु
	BYTE *स्थिर pStart = p;

	/* up to 4 symbols at a समय */
	जबतक ((BIT_reloadDStream(bitDPtr) == BIT_DStream_unfinished) && (p <= pEnd - 4)) अणु
		HUF_DECODE_SYMBOLX2_2(p, bitDPtr);
		HUF_DECODE_SYMBOLX2_1(p, bitDPtr);
		HUF_DECODE_SYMBOLX2_2(p, bitDPtr);
		HUF_DECODE_SYMBOLX2_0(p, bitDPtr);
	पूर्ण

	/* बंदr to the end */
	जबतक ((BIT_reloadDStream(bitDPtr) == BIT_DStream_unfinished) && (p < pEnd))
		HUF_DECODE_SYMBOLX2_0(p, bitDPtr);

	/* no more data to retrieve from bitstream, hence no need to reload */
	जबतक (p < pEnd)
		HUF_DECODE_SYMBOLX2_0(p, bitDPtr);

	वापस pEnd - pStart;
पूर्ण

अटल माप_प्रकार HUF_decompress1X2_usingDTable_पूर्णांकernal(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable)
अणु
	BYTE *op = (BYTE *)dst;
	BYTE *स्थिर oend = op + dstSize;
	स्थिर व्योम *dtPtr = DTable + 1;
	स्थिर HUF_DEltX2 *स्थिर dt = (स्थिर HUF_DEltX2 *)dtPtr;
	BIT_DStream_t bitD;
	DTableDesc स्थिर dtd = HUF_getDTableDesc(DTable);
	U32 स्थिर dtLog = dtd.tableLog;

	अणु
		माप_प्रकार स्थिर errorCode = BIT_initDStream(&bitD, cSrc, cSrcSize);
		अगर (HUF_isError(errorCode))
			वापस errorCode;
	पूर्ण

	HUF_decodeStreamX2(op, &bitD, oend, dt, dtLog);

	/* check */
	अगर (!BIT_endOfDStream(&bitD))
		वापस ERROR(corruption_detected);

	वापस dstSize;
पूर्ण

माप_प्रकार HUF_decompress1X2_usingDTable(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable)
अणु
	DTableDesc dtd = HUF_getDTableDesc(DTable);
	अगर (dtd.tableType != 0)
		वापस ERROR(GENERIC);
	वापस HUF_decompress1X2_usingDTable_पूर्णांकernal(dst, dstSize, cSrc, cSrcSize, DTable);
पूर्ण

माप_प्रकार HUF_decompress1X2_DCtx_wksp(HUF_DTable *DCtx, व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *)cSrc;

	माप_प्रकार स्थिर hSize = HUF_पढ़ोDTableX2_wksp(DCtx, cSrc, cSrcSize, workspace, workspaceSize);
	अगर (HUF_isError(hSize))
		वापस hSize;
	अगर (hSize >= cSrcSize)
		वापस ERROR(srcSize_wrong);
	ip += hSize;
	cSrcSize -= hSize;

	वापस HUF_decompress1X2_usingDTable_पूर्णांकernal(dst, dstSize, ip, cSrcSize, DCtx);
पूर्ण

अटल माप_प्रकार HUF_decompress4X2_usingDTable_पूर्णांकernal(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable)
अणु
	/* Check */
	अगर (cSrcSize < 10)
		वापस ERROR(corruption_detected); /* strict minimum : jump table + 1 byte per stream */

	अणु
		स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)cSrc;
		BYTE *स्थिर ostart = (BYTE *)dst;
		BYTE *स्थिर oend = ostart + dstSize;
		स्थिर व्योम *स्थिर dtPtr = DTable + 1;
		स्थिर HUF_DEltX2 *स्थिर dt = (स्थिर HUF_DEltX2 *)dtPtr;

		/* Init */
		BIT_DStream_t bitD1;
		BIT_DStream_t bitD2;
		BIT_DStream_t bitD3;
		BIT_DStream_t bitD4;
		माप_प्रकार स्थिर length1 = ZSTD_पढ़ोLE16(istart);
		माप_प्रकार स्थिर length2 = ZSTD_पढ़ोLE16(istart + 2);
		माप_प्रकार स्थिर length3 = ZSTD_पढ़ोLE16(istart + 4);
		माप_प्रकार स्थिर length4 = cSrcSize - (length1 + length2 + length3 + 6);
		स्थिर BYTE *स्थिर istart1 = istart + 6; /* jumpTable */
		स्थिर BYTE *स्थिर istart2 = istart1 + length1;
		स्थिर BYTE *स्थिर istart3 = istart2 + length2;
		स्थिर BYTE *स्थिर istart4 = istart3 + length3;
		स्थिर माप_प्रकार segmentSize = (dstSize + 3) / 4;
		BYTE *स्थिर opStart2 = ostart + segmentSize;
		BYTE *स्थिर opStart3 = opStart2 + segmentSize;
		BYTE *स्थिर opStart4 = opStart3 + segmentSize;
		BYTE *op1 = ostart;
		BYTE *op2 = opStart2;
		BYTE *op3 = opStart3;
		BYTE *op4 = opStart4;
		U32 endSignal;
		DTableDesc स्थिर dtd = HUF_getDTableDesc(DTable);
		U32 स्थिर dtLog = dtd.tableLog;

		अगर (length4 > cSrcSize)
			वापस ERROR(corruption_detected); /* overflow */
		अणु
			माप_प्रकार स्थिर errorCode = BIT_initDStream(&bitD1, istart1, length1);
			अगर (HUF_isError(errorCode))
				वापस errorCode;
		पूर्ण
		अणु
			माप_प्रकार स्थिर errorCode = BIT_initDStream(&bitD2, istart2, length2);
			अगर (HUF_isError(errorCode))
				वापस errorCode;
		पूर्ण
		अणु
			माप_प्रकार स्थिर errorCode = BIT_initDStream(&bitD3, istart3, length3);
			अगर (HUF_isError(errorCode))
				वापस errorCode;
		पूर्ण
		अणु
			माप_प्रकार स्थिर errorCode = BIT_initDStream(&bitD4, istart4, length4);
			अगर (HUF_isError(errorCode))
				वापस errorCode;
		पूर्ण

		/* 16-32 symbols per loop (4-8 symbols per stream) */
		endSignal = BIT_reloadDStream(&bitD1) | BIT_reloadDStream(&bitD2) | BIT_reloadDStream(&bitD3) | BIT_reloadDStream(&bitD4);
		क्रम (; (endSignal == BIT_DStream_unfinished) && (op4 < (oend - 7));) अणु
			HUF_DECODE_SYMBOLX2_2(op1, &bitD1);
			HUF_DECODE_SYMBOLX2_2(op2, &bitD2);
			HUF_DECODE_SYMBOLX2_2(op3, &bitD3);
			HUF_DECODE_SYMBOLX2_2(op4, &bitD4);
			HUF_DECODE_SYMBOLX2_1(op1, &bitD1);
			HUF_DECODE_SYMBOLX2_1(op2, &bitD2);
			HUF_DECODE_SYMBOLX2_1(op3, &bitD3);
			HUF_DECODE_SYMBOLX2_1(op4, &bitD4);
			HUF_DECODE_SYMBOLX2_2(op1, &bitD1);
			HUF_DECODE_SYMBOLX2_2(op2, &bitD2);
			HUF_DECODE_SYMBOLX2_2(op3, &bitD3);
			HUF_DECODE_SYMBOLX2_2(op4, &bitD4);
			HUF_DECODE_SYMBOLX2_0(op1, &bitD1);
			HUF_DECODE_SYMBOLX2_0(op2, &bitD2);
			HUF_DECODE_SYMBOLX2_0(op3, &bitD3);
			HUF_DECODE_SYMBOLX2_0(op4, &bitD4);
			endSignal = BIT_reloadDStream(&bitD1) | BIT_reloadDStream(&bitD2) | BIT_reloadDStream(&bitD3) | BIT_reloadDStream(&bitD4);
		पूर्ण

		/* check corruption */
		अगर (op1 > opStart2)
			वापस ERROR(corruption_detected);
		अगर (op2 > opStart3)
			वापस ERROR(corruption_detected);
		अगर (op3 > opStart4)
			वापस ERROR(corruption_detected);
		/* note : op4 supposed alपढ़ोy verअगरied within मुख्य loop */

		/* finish bitStreams one by one */
		HUF_decodeStreamX2(op1, &bitD1, opStart2, dt, dtLog);
		HUF_decodeStreamX2(op2, &bitD2, opStart3, dt, dtLog);
		HUF_decodeStreamX2(op3, &bitD3, opStart4, dt, dtLog);
		HUF_decodeStreamX2(op4, &bitD4, oend, dt, dtLog);

		/* check */
		endSignal = BIT_endOfDStream(&bitD1) & BIT_endOfDStream(&bitD2) & BIT_endOfDStream(&bitD3) & BIT_endOfDStream(&bitD4);
		अगर (!endSignal)
			वापस ERROR(corruption_detected);

		/* decoded size */
		वापस dstSize;
	पूर्ण
पूर्ण

माप_प्रकार HUF_decompress4X2_usingDTable(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable)
अणु
	DTableDesc dtd = HUF_getDTableDesc(DTable);
	अगर (dtd.tableType != 0)
		वापस ERROR(GENERIC);
	वापस HUF_decompress4X2_usingDTable_पूर्णांकernal(dst, dstSize, cSrc, cSrcSize, DTable);
पूर्ण

माप_प्रकार HUF_decompress4X2_DCtx_wksp(HUF_DTable *dctx, व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *)cSrc;

	माप_प्रकार स्थिर hSize = HUF_पढ़ोDTableX2_wksp(dctx, cSrc, cSrcSize, workspace, workspaceSize);
	अगर (HUF_isError(hSize))
		वापस hSize;
	अगर (hSize >= cSrcSize)
		वापस ERROR(srcSize_wrong);
	ip += hSize;
	cSrcSize -= hSize;

	वापस HUF_decompress4X2_usingDTable_पूर्णांकernal(dst, dstSize, ip, cSrcSize, dctx);
पूर्ण

/* *************************/
/* द्विगुन-symbols decoding */
/* *************************/
प्रकार काष्ठा अणु
	U16 sequence;
	BYTE nbBits;
	BYTE length;
पूर्ण HUF_DEltX4; /* द्विगुन-symbols decoding */

प्रकार काष्ठा अणु
	BYTE symbol;
	BYTE weight;
पूर्ण sortedSymbol_t;

/* HUF_fillDTableX4Level2() :
 * `rankValOrigin` must be a table of at least (HUF_TABLELOG_MAX + 1) U32 */
अटल व्योम HUF_fillDTableX4Level2(HUF_DEltX4 *DTable, U32 sizeLog, स्थिर U32 consumed, स्थिर U32 *rankValOrigin, स्थिर पूर्णांक minWeight,
				   स्थिर sortedSymbol_t *sortedSymbols, स्थिर U32 sortedListSize, U32 nbBitsBaseline, U16 baseSeq)
अणु
	HUF_DEltX4 DElt;
	U32 rankVal[HUF_TABLELOG_MAX + 1];

	/* get pre-calculated rankVal */
	स_नकल(rankVal, rankValOrigin, माप(rankVal));

	/* fill skipped values */
	अगर (minWeight > 1) अणु
		U32 i, skipSize = rankVal[minWeight];
		ZSTD_ग_लिखोLE16(&(DElt.sequence), baseSeq);
		DElt.nbBits = (BYTE)(consumed);
		DElt.length = 1;
		क्रम (i = 0; i < skipSize; i++)
			DTable[i] = DElt;
	पूर्ण

	/* fill DTable */
	अणु
		U32 s;
		क्रम (s = 0; s < sortedListSize; s++) अणु /* note : sortedSymbols alपढ़ोy skipped */
			स्थिर U32 symbol = sortedSymbols[s].symbol;
			स्थिर U32 weight = sortedSymbols[s].weight;
			स्थिर U32 nbBits = nbBitsBaseline - weight;
			स्थिर U32 length = 1 << (sizeLog - nbBits);
			स्थिर U32 start = rankVal[weight];
			U32 i = start;
			स्थिर U32 end = start + length;

			ZSTD_ग_लिखोLE16(&(DElt.sequence), (U16)(baseSeq + (symbol << 8)));
			DElt.nbBits = (BYTE)(nbBits + consumed);
			DElt.length = 2;
			करो अणु
				DTable[i++] = DElt;
			पूर्ण जबतक (i < end); /* since length >= 1 */

			rankVal[weight] += length;
		पूर्ण
	पूर्ण
पूर्ण

प्रकार U32 rankVal_t[HUF_TABLELOG_MAX][HUF_TABLELOG_MAX + 1];
प्रकार U32 rankValCol_t[HUF_TABLELOG_MAX + 1];

अटल व्योम HUF_fillDTableX4(HUF_DEltX4 *DTable, स्थिर U32 targetLog, स्थिर sortedSymbol_t *sortedList, स्थिर U32 sortedListSize, स्थिर U32 *rankStart,
			     rankVal_t rankValOrigin, स्थिर U32 maxWeight, स्थिर U32 nbBitsBaseline)
अणु
	U32 rankVal[HUF_TABLELOG_MAX + 1];
	स्थिर पूर्णांक scaleLog = nbBitsBaseline - targetLog; /* note : targetLog >= srcLog, hence scaleLog <= 1 */
	स्थिर U32 minBits = nbBitsBaseline - maxWeight;
	U32 s;

	स_नकल(rankVal, rankValOrigin, माप(rankVal));

	/* fill DTable */
	क्रम (s = 0; s < sortedListSize; s++) अणु
		स्थिर U16 symbol = sortedList[s].symbol;
		स्थिर U32 weight = sortedList[s].weight;
		स्थिर U32 nbBits = nbBitsBaseline - weight;
		स्थिर U32 start = rankVal[weight];
		स्थिर U32 length = 1 << (targetLog - nbBits);

		अगर (targetLog - nbBits >= minBits) अणु /* enough room क्रम a second symbol */
			U32 sortedRank;
			पूर्णांक minWeight = nbBits + scaleLog;
			अगर (minWeight < 1)
				minWeight = 1;
			sortedRank = rankStart[minWeight];
			HUF_fillDTableX4Level2(DTable + start, targetLog - nbBits, nbBits, rankValOrigin[nbBits], minWeight, sortedList + sortedRank,
					       sortedListSize - sortedRank, nbBitsBaseline, symbol);
		पूर्ण अन्यथा अणु
			HUF_DEltX4 DElt;
			ZSTD_ग_लिखोLE16(&(DElt.sequence), symbol);
			DElt.nbBits = (BYTE)(nbBits);
			DElt.length = 1;
			अणु
				U32 स्थिर end = start + length;
				U32 u;
				क्रम (u = start; u < end; u++)
					DTable[u] = DElt;
			पूर्ण
		पूर्ण
		rankVal[weight] += length;
	पूर्ण
पूर्ण

माप_प्रकार HUF_पढ़ोDTableX4_wksp(HUF_DTable *DTable, स्थिर व्योम *src, माप_प्रकार srcSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	U32 tableLog, maxW, sizeOfSort, nbSymbols;
	DTableDesc dtd = HUF_getDTableDesc(DTable);
	U32 स्थिर maxTableLog = dtd.maxTableLog;
	माप_प्रकार iSize;
	व्योम *dtPtr = DTable + 1; /* क्रमce compiler to aव्योम strict-aliasing */
	HUF_DEltX4 *स्थिर dt = (HUF_DEltX4 *)dtPtr;
	U32 *rankStart;

	rankValCol_t *rankVal;
	U32 *rankStats;
	U32 *rankStart0;
	sortedSymbol_t *sortedSymbol;
	BYTE *weightList;
	माप_प्रकार spaceUsed32 = 0;

	HUF_STATIC_ASSERT((माप(rankValCol_t) & 3) == 0);

	rankVal = (rankValCol_t *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += (माप(rankValCol_t) * HUF_TABLELOG_MAX) >> 2;
	rankStats = (U32 *)workspace + spaceUsed32;
	spaceUsed32 += HUF_TABLELOG_MAX + 1;
	rankStart0 = (U32 *)workspace + spaceUsed32;
	spaceUsed32 += HUF_TABLELOG_MAX + 2;
	sortedSymbol = (sortedSymbol_t *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += ALIGN(माप(sortedSymbol_t) * (HUF_SYMBOLVALUE_MAX + 1), माप(U32)) >> 2;
	weightList = (BYTE *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += ALIGN(HUF_SYMBOLVALUE_MAX + 1, माप(U32)) >> 2;

	अगर ((spaceUsed32 << 2) > workspaceSize)
		वापस ERROR(tableLog_tooLarge);
	workspace = (U32 *)workspace + spaceUsed32;
	workspaceSize -= (spaceUsed32 << 2);

	rankStart = rankStart0 + 1;
	स_रखो(rankStats, 0, माप(U32) * (2 * HUF_TABLELOG_MAX + 2 + 1));

	HUF_STATIC_ASSERT(माप(HUF_DEltX4) == माप(HUF_DTable)); /* अगर compiler fails here, निश्चितion is wrong */
	अगर (maxTableLog > HUF_TABLELOG_MAX)
		वापस ERROR(tableLog_tooLarge);
	/* स_रखो(weightList, 0, माप(weightList)); */ /* is not necessary, even though some analyzer complain ... */

	iSize = HUF_पढ़ोStats_wksp(weightList, HUF_SYMBOLVALUE_MAX + 1, rankStats, &nbSymbols, &tableLog, src, srcSize, workspace, workspaceSize);
	अगर (HUF_isError(iSize))
		वापस iSize;

	/* check result */
	अगर (tableLog > maxTableLog)
		वापस ERROR(tableLog_tooLarge); /* DTable can't fit code depth */

	/* find maxWeight */
	क्रम (maxW = tableLog; rankStats[maxW] == 0; maxW--) अणु
	पूर्ण /* necessarily finds a solution beक्रमe 0 */

	/* Get start index of each weight */
	अणु
		U32 w, nextRankStart = 0;
		क्रम (w = 1; w < maxW + 1; w++) अणु
			U32 curr = nextRankStart;
			nextRankStart += rankStats[w];
			rankStart[w] = curr;
		पूर्ण
		rankStart[0] = nextRankStart; /* put all 0w symbols at the end of sorted list*/
		sizeOfSort = nextRankStart;
	पूर्ण

	/* sort symbols by weight */
	अणु
		U32 s;
		क्रम (s = 0; s < nbSymbols; s++) अणु
			U32 स्थिर w = weightList[s];
			U32 स्थिर r = rankStart[w]++;
			sortedSymbol[r].symbol = (BYTE)s;
			sortedSymbol[r].weight = (BYTE)w;
		पूर्ण
		rankStart[0] = 0; /* क्रमget 0w symbols; this is beginning of weight(1) */
	पूर्ण

	/* Build rankVal */
	अणु
		U32 *स्थिर rankVal0 = rankVal[0];
		अणु
			पूर्णांक स्थिर rescale = (maxTableLog - tableLog) - 1; /* tableLog <= maxTableLog */
			U32 nextRankVal = 0;
			U32 w;
			क्रम (w = 1; w < maxW + 1; w++) अणु
				U32 curr = nextRankVal;
				nextRankVal += rankStats[w] << (w + rescale);
				rankVal0[w] = curr;
			पूर्ण
		पूर्ण
		अणु
			U32 स्थिर minBits = tableLog + 1 - maxW;
			U32 consumed;
			क्रम (consumed = minBits; consumed < maxTableLog - minBits + 1; consumed++) अणु
				U32 *स्थिर rankValPtr = rankVal[consumed];
				U32 w;
				क्रम (w = 1; w < maxW + 1; w++) अणु
					rankValPtr[w] = rankVal0[w] >> consumed;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	HUF_fillDTableX4(dt, maxTableLog, sortedSymbol, sizeOfSort, rankStart0, rankVal, maxW, tableLog + 1);

	dtd.tableLog = (BYTE)maxTableLog;
	dtd.tableType = 1;
	स_नकल(DTable, &dtd, माप(dtd));
	वापस iSize;
पूर्ण

अटल U32 HUF_decodeSymbolX4(व्योम *op, BIT_DStream_t *DStream, स्थिर HUF_DEltX4 *dt, स्थिर U32 dtLog)
अणु
	माप_प्रकार स्थिर val = BIT_lookBitsFast(DStream, dtLog); /* note : dtLog >= 1 */
	स_नकल(op, dt + val, 2);
	BIT_skipBits(DStream, dt[val].nbBits);
	वापस dt[val].length;
पूर्ण

अटल U32 HUF_decodeLastSymbolX4(व्योम *op, BIT_DStream_t *DStream, स्थिर HUF_DEltX4 *dt, स्थिर U32 dtLog)
अणु
	माप_प्रकार स्थिर val = BIT_lookBitsFast(DStream, dtLog); /* note : dtLog >= 1 */
	स_नकल(op, dt + val, 1);
	अगर (dt[val].length == 1)
		BIT_skipBits(DStream, dt[val].nbBits);
	अन्यथा अणु
		अगर (DStream->bitsConsumed < (माप(DStream->bitContainer) * 8)) अणु
			BIT_skipBits(DStream, dt[val].nbBits);
			अगर (DStream->bitsConsumed > (माप(DStream->bitContainer) * 8))
				/* ugly hack; works only because it's the last symbol. Note : can't easily extract nbBits from just this symbol */
				DStream->bitsConsumed = (माप(DStream->bitContainer) * 8);
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

#घोषणा HUF_DECODE_SYMBOLX4_0(ptr, DStreamPtr) ptr += HUF_decodeSymbolX4(ptr, DStreamPtr, dt, dtLog)

#घोषणा HUF_DECODE_SYMBOLX4_1(ptr, DStreamPtr)         \
	अगर (ZSTD_64bits() || (HUF_TABLELOG_MAX <= 12)) \
	ptr += HUF_decodeSymbolX4(ptr, DStreamPtr, dt, dtLog)

#घोषणा HUF_DECODE_SYMBOLX4_2(ptr, DStreamPtr) \
	अगर (ZSTD_64bits())                     \
	ptr += HUF_decodeSymbolX4(ptr, DStreamPtr, dt, dtLog)

FORCE_INLINE माप_प्रकार HUF_decodeStreamX4(BYTE *p, BIT_DStream_t *bitDPtr, BYTE *स्थिर pEnd, स्थिर HUF_DEltX4 *स्थिर dt, स्थिर U32 dtLog)
अणु
	BYTE *स्थिर pStart = p;

	/* up to 8 symbols at a समय */
	जबतक ((BIT_reloadDStream(bitDPtr) == BIT_DStream_unfinished) & (p < pEnd - (माप(bitDPtr->bitContainer) - 1))) अणु
		HUF_DECODE_SYMBOLX4_2(p, bitDPtr);
		HUF_DECODE_SYMBOLX4_1(p, bitDPtr);
		HUF_DECODE_SYMBOLX4_2(p, bitDPtr);
		HUF_DECODE_SYMBOLX4_0(p, bitDPtr);
	पूर्ण

	/* बंदr to end : up to 2 symbols at a समय */
	जबतक ((BIT_reloadDStream(bitDPtr) == BIT_DStream_unfinished) & (p <= pEnd - 2))
		HUF_DECODE_SYMBOLX4_0(p, bitDPtr);

	जबतक (p <= pEnd - 2)
		HUF_DECODE_SYMBOLX4_0(p, bitDPtr); /* no need to reload : reached the end of DStream */

	अगर (p < pEnd)
		p += HUF_decodeLastSymbolX4(p, bitDPtr, dt, dtLog);

	वापस p - pStart;
पूर्ण

अटल माप_प्रकार HUF_decompress1X4_usingDTable_पूर्णांकernal(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable)
अणु
	BIT_DStream_t bitD;

	/* Init */
	अणु
		माप_प्रकार स्थिर errorCode = BIT_initDStream(&bitD, cSrc, cSrcSize);
		अगर (HUF_isError(errorCode))
			वापस errorCode;
	पूर्ण

	/* decode */
	अणु
		BYTE *स्थिर ostart = (BYTE *)dst;
		BYTE *स्थिर oend = ostart + dstSize;
		स्थिर व्योम *स्थिर dtPtr = DTable + 1; /* क्रमce compiler to not use strict-aliasing */
		स्थिर HUF_DEltX4 *स्थिर dt = (स्थिर HUF_DEltX4 *)dtPtr;
		DTableDesc स्थिर dtd = HUF_getDTableDesc(DTable);
		HUF_decodeStreamX4(ostart, &bitD, oend, dt, dtd.tableLog);
	पूर्ण

	/* check */
	अगर (!BIT_endOfDStream(&bitD))
		वापस ERROR(corruption_detected);

	/* decoded size */
	वापस dstSize;
पूर्ण

माप_प्रकार HUF_decompress1X4_usingDTable(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable)
अणु
	DTableDesc dtd = HUF_getDTableDesc(DTable);
	अगर (dtd.tableType != 1)
		वापस ERROR(GENERIC);
	वापस HUF_decompress1X4_usingDTable_पूर्णांकernal(dst, dstSize, cSrc, cSrcSize, DTable);
पूर्ण

माप_प्रकार HUF_decompress1X4_DCtx_wksp(HUF_DTable *DCtx, व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *)cSrc;

	माप_प्रकार स्थिर hSize = HUF_पढ़ोDTableX4_wksp(DCtx, cSrc, cSrcSize, workspace, workspaceSize);
	अगर (HUF_isError(hSize))
		वापस hSize;
	अगर (hSize >= cSrcSize)
		वापस ERROR(srcSize_wrong);
	ip += hSize;
	cSrcSize -= hSize;

	वापस HUF_decompress1X4_usingDTable_पूर्णांकernal(dst, dstSize, ip, cSrcSize, DCtx);
पूर्ण

अटल माप_प्रकार HUF_decompress4X4_usingDTable_पूर्णांकernal(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable)
अणु
	अगर (cSrcSize < 10)
		वापस ERROR(corruption_detected); /* strict minimum : jump table + 1 byte per stream */

	अणु
		स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)cSrc;
		BYTE *स्थिर ostart = (BYTE *)dst;
		BYTE *स्थिर oend = ostart + dstSize;
		स्थिर व्योम *स्थिर dtPtr = DTable + 1;
		स्थिर HUF_DEltX4 *स्थिर dt = (स्थिर HUF_DEltX4 *)dtPtr;

		/* Init */
		BIT_DStream_t bitD1;
		BIT_DStream_t bitD2;
		BIT_DStream_t bitD3;
		BIT_DStream_t bitD4;
		माप_प्रकार स्थिर length1 = ZSTD_पढ़ोLE16(istart);
		माप_प्रकार स्थिर length2 = ZSTD_पढ़ोLE16(istart + 2);
		माप_प्रकार स्थिर length3 = ZSTD_पढ़ोLE16(istart + 4);
		माप_प्रकार स्थिर length4 = cSrcSize - (length1 + length2 + length3 + 6);
		स्थिर BYTE *स्थिर istart1 = istart + 6; /* jumpTable */
		स्थिर BYTE *स्थिर istart2 = istart1 + length1;
		स्थिर BYTE *स्थिर istart3 = istart2 + length2;
		स्थिर BYTE *स्थिर istart4 = istart3 + length3;
		माप_प्रकार स्थिर segmentSize = (dstSize + 3) / 4;
		BYTE *स्थिर opStart2 = ostart + segmentSize;
		BYTE *स्थिर opStart3 = opStart2 + segmentSize;
		BYTE *स्थिर opStart4 = opStart3 + segmentSize;
		BYTE *op1 = ostart;
		BYTE *op2 = opStart2;
		BYTE *op3 = opStart3;
		BYTE *op4 = opStart4;
		U32 endSignal;
		DTableDesc स्थिर dtd = HUF_getDTableDesc(DTable);
		U32 स्थिर dtLog = dtd.tableLog;

		अगर (length4 > cSrcSize)
			वापस ERROR(corruption_detected); /* overflow */
		अणु
			माप_प्रकार स्थिर errorCode = BIT_initDStream(&bitD1, istart1, length1);
			अगर (HUF_isError(errorCode))
				वापस errorCode;
		पूर्ण
		अणु
			माप_प्रकार स्थिर errorCode = BIT_initDStream(&bitD2, istart2, length2);
			अगर (HUF_isError(errorCode))
				वापस errorCode;
		पूर्ण
		अणु
			माप_प्रकार स्थिर errorCode = BIT_initDStream(&bitD3, istart3, length3);
			अगर (HUF_isError(errorCode))
				वापस errorCode;
		पूर्ण
		अणु
			माप_प्रकार स्थिर errorCode = BIT_initDStream(&bitD4, istart4, length4);
			अगर (HUF_isError(errorCode))
				वापस errorCode;
		पूर्ण

		/* 16-32 symbols per loop (4-8 symbols per stream) */
		endSignal = BIT_reloadDStream(&bitD1) | BIT_reloadDStream(&bitD2) | BIT_reloadDStream(&bitD3) | BIT_reloadDStream(&bitD4);
		क्रम (; (endSignal == BIT_DStream_unfinished) & (op4 < (oend - (माप(bitD4.bitContainer) - 1)));) अणु
			HUF_DECODE_SYMBOLX4_2(op1, &bitD1);
			HUF_DECODE_SYMBOLX4_2(op2, &bitD2);
			HUF_DECODE_SYMBOLX4_2(op3, &bitD3);
			HUF_DECODE_SYMBOLX4_2(op4, &bitD4);
			HUF_DECODE_SYMBOLX4_1(op1, &bitD1);
			HUF_DECODE_SYMBOLX4_1(op2, &bitD2);
			HUF_DECODE_SYMBOLX4_1(op3, &bitD3);
			HUF_DECODE_SYMBOLX4_1(op4, &bitD4);
			HUF_DECODE_SYMBOLX4_2(op1, &bitD1);
			HUF_DECODE_SYMBOLX4_2(op2, &bitD2);
			HUF_DECODE_SYMBOLX4_2(op3, &bitD3);
			HUF_DECODE_SYMBOLX4_2(op4, &bitD4);
			HUF_DECODE_SYMBOLX4_0(op1, &bitD1);
			HUF_DECODE_SYMBOLX4_0(op2, &bitD2);
			HUF_DECODE_SYMBOLX4_0(op3, &bitD3);
			HUF_DECODE_SYMBOLX4_0(op4, &bitD4);

			endSignal = BIT_reloadDStream(&bitD1) | BIT_reloadDStream(&bitD2) | BIT_reloadDStream(&bitD3) | BIT_reloadDStream(&bitD4);
		पूर्ण

		/* check corruption */
		अगर (op1 > opStart2)
			वापस ERROR(corruption_detected);
		अगर (op2 > opStart3)
			वापस ERROR(corruption_detected);
		अगर (op3 > opStart4)
			वापस ERROR(corruption_detected);
		/* note : op4 alपढ़ोy verअगरied within मुख्य loop */

		/* finish bitStreams one by one */
		HUF_decodeStreamX4(op1, &bitD1, opStart2, dt, dtLog);
		HUF_decodeStreamX4(op2, &bitD2, opStart3, dt, dtLog);
		HUF_decodeStreamX4(op3, &bitD3, opStart4, dt, dtLog);
		HUF_decodeStreamX4(op4, &bitD4, oend, dt, dtLog);

		/* check */
		अणु
			U32 स्थिर endCheck = BIT_endOfDStream(&bitD1) & BIT_endOfDStream(&bitD2) & BIT_endOfDStream(&bitD3) & BIT_endOfDStream(&bitD4);
			अगर (!endCheck)
				वापस ERROR(corruption_detected);
		पूर्ण

		/* decoded size */
		वापस dstSize;
	पूर्ण
पूर्ण

माप_प्रकार HUF_decompress4X4_usingDTable(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable)
अणु
	DTableDesc dtd = HUF_getDTableDesc(DTable);
	अगर (dtd.tableType != 1)
		वापस ERROR(GENERIC);
	वापस HUF_decompress4X4_usingDTable_पूर्णांकernal(dst, dstSize, cSrc, cSrcSize, DTable);
पूर्ण

माप_प्रकार HUF_decompress4X4_DCtx_wksp(HUF_DTable *dctx, व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *)cSrc;

	माप_प्रकार hSize = HUF_पढ़ोDTableX4_wksp(dctx, cSrc, cSrcSize, workspace, workspaceSize);
	अगर (HUF_isError(hSize))
		वापस hSize;
	अगर (hSize >= cSrcSize)
		वापस ERROR(srcSize_wrong);
	ip += hSize;
	cSrcSize -= hSize;

	वापस HUF_decompress4X4_usingDTable_पूर्णांकernal(dst, dstSize, ip, cSrcSize, dctx);
पूर्ण

/* ********************************/
/* Generic decompression selector */
/* ********************************/

माप_प्रकार HUF_decompress1X_usingDTable(व्योम *dst, माप_प्रकार maxDstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable)
अणु
	DTableDesc स्थिर dtd = HUF_getDTableDesc(DTable);
	वापस dtd.tableType ? HUF_decompress1X4_usingDTable_पूर्णांकernal(dst, maxDstSize, cSrc, cSrcSize, DTable)
			     : HUF_decompress1X2_usingDTable_पूर्णांकernal(dst, maxDstSize, cSrc, cSrcSize, DTable);
पूर्ण

माप_प्रकार HUF_decompress4X_usingDTable(व्योम *dst, माप_प्रकार maxDstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable)
अणु
	DTableDesc स्थिर dtd = HUF_getDTableDesc(DTable);
	वापस dtd.tableType ? HUF_decompress4X4_usingDTable_पूर्णांकernal(dst, maxDstSize, cSrc, cSrcSize, DTable)
			     : HUF_decompress4X2_usingDTable_पूर्णांकernal(dst, maxDstSize, cSrc, cSrcSize, DTable);
पूर्ण

प्रकार काष्ठा अणु
	U32 tableTime;
	U32 decode256Time;
पूर्ण algo_समय_प्रकार;
अटल स्थिर algo_समय_प्रकार algoTime[16 /* Quantization */][3 /* single, द्विगुन, quad */] = अणु
    /* single, द्विगुन, quad */
    अणुअणु0, 0पूर्ण, अणु1, 1पूर्ण, अणु2, 2पूर्णपूर्ण,		     /* Q==0 : impossible */
    अणुअणु0, 0पूर्ण, अणु1, 1पूर्ण, अणु2, 2पूर्णपूर्ण,		     /* Q==1 : impossible */
    अणुअणु38, 130पूर्ण, अणु1313, 74पूर्ण, अणु2151, 38पूर्णपूर्ण,     /* Q == 2 : 12-18% */
    अणुअणु448, 128पूर्ण, अणु1353, 74पूर्ण, अणु2238, 41पूर्णपूर्ण,    /* Q == 3 : 18-25% */
    अणुअणु556, 128पूर्ण, अणु1353, 74पूर्ण, अणु2238, 47पूर्णपूर्ण,    /* Q == 4 : 25-32% */
    अणुअणु714, 128पूर्ण, अणु1418, 74पूर्ण, अणु2436, 53पूर्णपूर्ण,    /* Q == 5 : 32-38% */
    अणुअणु883, 128पूर्ण, अणु1437, 74पूर्ण, अणु2464, 61पूर्णपूर्ण,    /* Q == 6 : 38-44% */
    अणुअणु897, 128पूर्ण, अणु1515, 75पूर्ण, अणु2622, 68पूर्णपूर्ण,    /* Q == 7 : 44-50% */
    अणुअणु926, 128पूर्ण, अणु1613, 75पूर्ण, अणु2730, 75पूर्णपूर्ण,    /* Q == 8 : 50-56% */
    अणुअणु947, 128पूर्ण, अणु1729, 77पूर्ण, अणु3359, 77पूर्णपूर्ण,    /* Q == 9 : 56-62% */
    अणुअणु1107, 128पूर्ण, अणु2083, 81पूर्ण, अणु4006, 84पूर्णपूर्ण,   /* Q ==10 : 62-69% */
    अणुअणु1177, 128पूर्ण, अणु2379, 87पूर्ण, अणु4785, 88पूर्णपूर्ण,   /* Q ==11 : 69-75% */
    अणुअणु1242, 128पूर्ण, अणु2415, 93पूर्ण, अणु5155, 84पूर्णपूर्ण,   /* Q ==12 : 75-81% */
    अणुअणु1349, 128पूर्ण, अणु2644, 106पूर्ण, अणु5260, 106पूर्णपूर्ण, /* Q ==13 : 81-87% */
    अणुअणु1455, 128पूर्ण, अणु2422, 124पूर्ण, अणु4174, 124पूर्णपूर्ण, /* Q ==14 : 87-93% */
    अणुअणु722, 128पूर्ण, अणु1891, 145पूर्ण, अणु1936, 146पूर्णपूर्ण,  /* Q ==15 : 93-99% */
पूर्ण;

/** HUF_selectDecoder() :
*   Tells which decoder is likely to decode faster,
*   based on a set of pre-determined metrics.
*   @वापस : 0==HUF_decompress4X2, 1==HUF_decompress4X4 .
*   Assumption : 0 < cSrcSize < dstSize <= 128 KB */
U32 HUF_selectDecoder(माप_प्रकार dstSize, माप_प्रकार cSrcSize)
अणु
	/* decoder timing evaluation */
	U32 स्थिर Q = (U32)(cSrcSize * 16 / dstSize); /* Q < 16 since dstSize > cSrcSize */
	U32 स्थिर D256 = (U32)(dstSize >> 8);
	U32 स्थिर DTime0 = algoTime[Q][0].tableTime + (algoTime[Q][0].decode256Time * D256);
	U32 DTime1 = algoTime[Q][1].tableTime + (algoTime[Q][1].decode256Time * D256);
	DTime1 += DTime1 >> 3; /* advantage to algorithm using less memory, क्रम cache eviction */

	वापस DTime1 < DTime0;
पूर्ण

प्रकार माप_प्रकार (*decompressionAlgo)(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize);

माप_प्रकार HUF_decompress4X_DCtx_wksp(HUF_DTable *dctx, व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	/* validation checks */
	अगर (dstSize == 0)
		वापस ERROR(dstSize_tooSmall);
	अगर (cSrcSize > dstSize)
		वापस ERROR(corruption_detected); /* invalid */
	अगर (cSrcSize == dstSize) अणु
		स_नकल(dst, cSrc, dstSize);
		वापस dstSize;
	पूर्ण /* not compressed */
	अगर (cSrcSize == 1) अणु
		स_रखो(dst, *(स्थिर BYTE *)cSrc, dstSize);
		वापस dstSize;
	पूर्ण /* RLE */

	अणु
		U32 स्थिर algoNb = HUF_selectDecoder(dstSize, cSrcSize);
		वापस algoNb ? HUF_decompress4X4_DCtx_wksp(dctx, dst, dstSize, cSrc, cSrcSize, workspace, workspaceSize)
			      : HUF_decompress4X2_DCtx_wksp(dctx, dst, dstSize, cSrc, cSrcSize, workspace, workspaceSize);
	पूर्ण
पूर्ण

माप_प्रकार HUF_decompress4X_hufOnly_wksp(HUF_DTable *dctx, व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	/* validation checks */
	अगर (dstSize == 0)
		वापस ERROR(dstSize_tooSmall);
	अगर ((cSrcSize >= dstSize) || (cSrcSize <= 1))
		वापस ERROR(corruption_detected); /* invalid */

	अणु
		U32 स्थिर algoNb = HUF_selectDecoder(dstSize, cSrcSize);
		वापस algoNb ? HUF_decompress4X4_DCtx_wksp(dctx, dst, dstSize, cSrc, cSrcSize, workspace, workspaceSize)
			      : HUF_decompress4X2_DCtx_wksp(dctx, dst, dstSize, cSrc, cSrcSize, workspace, workspaceSize);
	पूर्ण
पूर्ण

माप_प्रकार HUF_decompress1X_DCtx_wksp(HUF_DTable *dctx, व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	/* validation checks */
	अगर (dstSize == 0)
		वापस ERROR(dstSize_tooSmall);
	अगर (cSrcSize > dstSize)
		वापस ERROR(corruption_detected); /* invalid */
	अगर (cSrcSize == dstSize) अणु
		स_नकल(dst, cSrc, dstSize);
		वापस dstSize;
	पूर्ण /* not compressed */
	अगर (cSrcSize == 1) अणु
		स_रखो(dst, *(स्थिर BYTE *)cSrc, dstSize);
		वापस dstSize;
	पूर्ण /* RLE */

	अणु
		U32 स्थिर algoNb = HUF_selectDecoder(dstSize, cSrcSize);
		वापस algoNb ? HUF_decompress1X4_DCtx_wksp(dctx, dst, dstSize, cSrc, cSrcSize, workspace, workspaceSize)
			      : HUF_decompress1X2_DCtx_wksp(dctx, dst, dstSize, cSrc, cSrcSize, workspace, workspaceSize);
	पूर्ण
पूर्ण
