<शैली गुरु>
/*
 * FSE : Finite State Entropy decoder
 * Copyright (C) 2013-2015, Yann Collet.
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
*  Includes
****************************************************************/
#समावेश "bitstream.h"
#समावेश "fse.h"
#समावेश "zstd_internal.h"
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स> /* स_नकल, स_रखो */

/* **************************************************************
*  Error Management
****************************************************************/
#घोषणा FSE_isError ERR_isError
#घोषणा FSE_STATIC_ASSERT(c)                                   \
	अणु                                                      \
		क्रमागत अणु FSE_अटल_निश्चित = 1 / (पूर्णांक)(!!(c)) पूर्ण; \
	पूर्ण /* use only *after* variable declarations */

/* **************************************************************
*  Templates
****************************************************************/
/*
  deचिन्हित to be included
  क्रम type-specअगरic functions (ढाँचा emulation in C)
  Objective is to ग_लिखो these functions only once, क्रम improved मुख्यtenance
*/

/* safety checks */
#अगर_अघोषित FSE_FUNCTION_EXTENSION
#त्रुटि "FSE_FUNCTION_EXTENSION must be defined"
#पूर्ण_अगर
#अगर_अघोषित FSE_FUNCTION_TYPE
#त्रुटि "FSE_FUNCTION_TYPE must be defined"
#पूर्ण_अगर

/* Function names */
#घोषणा FSE_CAT(X, Y) X##Y
#घोषणा FSE_FUNCTION_NAME(X, Y) FSE_CAT(X, Y)
#घोषणा FSE_TYPE_NAME(X, Y) FSE_CAT(X, Y)

/* Function ढाँचाs */

माप_प्रकार FSE_buildDTable_wksp(FSE_DTable *dt, स्थिर लघु *normalizedCounter, अचिन्हित maxSymbolValue, अचिन्हित tableLog, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	व्योम *स्थिर tdPtr = dt + 1; /* because *dt is अचिन्हित, 32-bits aligned on 32-bits */
	FSE_DECODE_TYPE *स्थिर tableDecode = (FSE_DECODE_TYPE *)(tdPtr);
	U16 *symbolNext = (U16 *)workspace;

	U32 स्थिर maxSV1 = maxSymbolValue + 1;
	U32 स्थिर tableSize = 1 << tableLog;
	U32 highThreshold = tableSize - 1;

	/* Sanity Checks */
	अगर (workspaceSize < माप(U16) * (FSE_MAX_SYMBOL_VALUE + 1))
		वापस ERROR(tableLog_tooLarge);
	अगर (maxSymbolValue > FSE_MAX_SYMBOL_VALUE)
		वापस ERROR(maxSymbolValue_tooLarge);
	अगर (tableLog > FSE_MAX_TABLELOG)
		वापस ERROR(tableLog_tooLarge);

	/* Init, lay करोwn lowprob symbols */
	अणु
		FSE_DTableHeader DTableH;
		DTableH.tableLog = (U16)tableLog;
		DTableH.fastMode = 1;
		अणु
			S16 स्थिर largeLimit = (S16)(1 << (tableLog - 1));
			U32 s;
			क्रम (s = 0; s < maxSV1; s++) अणु
				अगर (normalizedCounter[s] == -1) अणु
					tableDecode[highThreshold--].symbol = (FSE_FUNCTION_TYPE)s;
					symbolNext[s] = 1;
				पूर्ण अन्यथा अणु
					अगर (normalizedCounter[s] >= largeLimit)
						DTableH.fastMode = 0;
					symbolNext[s] = normalizedCounter[s];
				पूर्ण
			पूर्ण
		पूर्ण
		स_नकल(dt, &DTableH, माप(DTableH));
	पूर्ण

	/* Spपढ़ो symbols */
	अणु
		U32 स्थिर tableMask = tableSize - 1;
		U32 स्थिर step = FSE_TABLESTEP(tableSize);
		U32 s, position = 0;
		क्रम (s = 0; s < maxSV1; s++) अणु
			पूर्णांक i;
			क्रम (i = 0; i < normalizedCounter[s]; i++) अणु
				tableDecode[position].symbol = (FSE_FUNCTION_TYPE)s;
				position = (position + step) & tableMask;
				जबतक (position > highThreshold)
					position = (position + step) & tableMask; /* lowprob area */
			पूर्ण
		पूर्ण
		अगर (position != 0)
			वापस ERROR(GENERIC); /* position must reach all cells once, otherwise normalizedCounter is incorrect */
	पूर्ण

	/* Build Decoding table */
	अणु
		U32 u;
		क्रम (u = 0; u < tableSize; u++) अणु
			FSE_FUNCTION_TYPE स्थिर symbol = (FSE_FUNCTION_TYPE)(tableDecode[u].symbol);
			U16 nextState = symbolNext[symbol]++;
			tableDecode[u].nbBits = (BYTE)(tableLog - BIT_highbit32((U32)nextState));
			tableDecode[u].newState = (U16)((nextState << tableDecode[u].nbBits) - tableSize);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*-*******************************************************
*  Decompression (Byte symbols)
*********************************************************/
माप_प्रकार FSE_buildDTable_rle(FSE_DTable *dt, BYTE symbolValue)
अणु
	व्योम *ptr = dt;
	FSE_DTableHeader *स्थिर DTableH = (FSE_DTableHeader *)ptr;
	व्योम *dPtr = dt + 1;
	FSE_decode_t *स्थिर cell = (FSE_decode_t *)dPtr;

	DTableH->tableLog = 0;
	DTableH->fastMode = 0;

	cell->newState = 0;
	cell->symbol = symbolValue;
	cell->nbBits = 0;

	वापस 0;
पूर्ण

माप_प्रकार FSE_buildDTable_raw(FSE_DTable *dt, अचिन्हित nbBits)
अणु
	व्योम *ptr = dt;
	FSE_DTableHeader *स्थिर DTableH = (FSE_DTableHeader *)ptr;
	व्योम *dPtr = dt + 1;
	FSE_decode_t *स्थिर dinfo = (FSE_decode_t *)dPtr;
	स्थिर अचिन्हित tableSize = 1 << nbBits;
	स्थिर अचिन्हित tableMask = tableSize - 1;
	स्थिर अचिन्हित maxSV1 = tableMask + 1;
	अचिन्हित s;

	/* Sanity checks */
	अगर (nbBits < 1)
		वापस ERROR(GENERIC); /* min size */

	/* Build Decoding Table */
	DTableH->tableLog = (U16)nbBits;
	DTableH->fastMode = 1;
	क्रम (s = 0; s < maxSV1; s++) अणु
		dinfo[s].newState = 0;
		dinfo[s].symbol = (BYTE)s;
		dinfo[s].nbBits = (BYTE)nbBits;
	पूर्ण

	वापस 0;
पूर्ण

FORCE_INLINE माप_प्रकार FSE_decompress_usingDTable_generic(व्योम *dst, माप_प्रकार maxDstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर FSE_DTable *dt,
						       स्थिर अचिन्हित fast)
अणु
	BYTE *स्थिर ostart = (BYTE *)dst;
	BYTE *op = ostart;
	BYTE *स्थिर omax = op + maxDstSize;
	BYTE *स्थिर olimit = omax - 3;

	BIT_DStream_t bitD;
	FSE_DState_t state1;
	FSE_DState_t state2;

	/* Init */
	CHECK_F(BIT_initDStream(&bitD, cSrc, cSrcSize));

	FSE_initDState(&state1, &bitD, dt);
	FSE_initDState(&state2, &bitD, dt);

#घोषणा FSE_GETSYMBOL(statePtr) fast ? FSE_decodeSymbolFast(statePtr, &bitD) : FSE_decodeSymbol(statePtr, &bitD)

	/* 4 symbols per loop */
	क्रम (; (BIT_reloadDStream(&bitD) == BIT_DStream_unfinished) & (op < olimit); op += 4) अणु
		op[0] = FSE_GETSYMBOL(&state1);

		अगर (FSE_MAX_TABLELOG * 2 + 7 > माप(bitD.bitContainer) * 8) /* This test must be अटल */
			BIT_reloadDStream(&bitD);

		op[1] = FSE_GETSYMBOL(&state2);

		अगर (FSE_MAX_TABLELOG * 4 + 7 > माप(bitD.bitContainer) * 8) /* This test must be अटल */
		अणु
			अगर (BIT_reloadDStream(&bitD) > BIT_DStream_unfinished) अणु
				op += 2;
				अवरोध;
			पूर्ण
		पूर्ण

		op[2] = FSE_GETSYMBOL(&state1);

		अगर (FSE_MAX_TABLELOG * 2 + 7 > माप(bitD.bitContainer) * 8) /* This test must be अटल */
			BIT_reloadDStream(&bitD);

		op[3] = FSE_GETSYMBOL(&state2);
	पूर्ण

	/* tail */
	/* note : BIT_reloadDStream(&bitD) >= FSE_DStream_partiallyFilled; Ends at exactly BIT_DStream_completed */
	जबतक (1) अणु
		अगर (op > (omax - 2))
			वापस ERROR(dstSize_tooSmall);
		*op++ = FSE_GETSYMBOL(&state1);
		अगर (BIT_reloadDStream(&bitD) == BIT_DStream_overflow) अणु
			*op++ = FSE_GETSYMBOL(&state2);
			अवरोध;
		पूर्ण

		अगर (op > (omax - 2))
			वापस ERROR(dstSize_tooSmall);
		*op++ = FSE_GETSYMBOL(&state2);
		अगर (BIT_reloadDStream(&bitD) == BIT_DStream_overflow) अणु
			*op++ = FSE_GETSYMBOL(&state1);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस op - ostart;
पूर्ण

माप_प्रकार FSE_decompress_usingDTable(व्योम *dst, माप_प्रकार originalSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर FSE_DTable *dt)
अणु
	स्थिर व्योम *ptr = dt;
	स्थिर FSE_DTableHeader *DTableH = (स्थिर FSE_DTableHeader *)ptr;
	स्थिर U32 fastMode = DTableH->fastMode;

	/* select fast mode (अटल) */
	अगर (fastMode)
		वापस FSE_decompress_usingDTable_generic(dst, originalSize, cSrc, cSrcSize, dt, 1);
	वापस FSE_decompress_usingDTable_generic(dst, originalSize, cSrc, cSrcSize, dt, 0);
पूर्ण

माप_प्रकार FSE_decompress_wksp(व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, अचिन्हित maxLog, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)cSrc;
	स्थिर BYTE *ip = istart;
	अचिन्हित tableLog;
	अचिन्हित maxSymbolValue = FSE_MAX_SYMBOL_VALUE;
	माप_प्रकार NCountLength;

	FSE_DTable *dt;
	लघु *counting;
	माप_प्रकार spaceUsed32 = 0;

	FSE_STATIC_ASSERT(माप(FSE_DTable) == माप(U32));

	dt = (FSE_DTable *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += FSE_DTABLE_SIZE_U32(maxLog);
	counting = (लघु *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += ALIGN(माप(लघु) * (FSE_MAX_SYMBOL_VALUE + 1), माप(U32)) >> 2;

	अगर ((spaceUsed32 << 2) > workspaceSize)
		वापस ERROR(tableLog_tooLarge);
	workspace = (U32 *)workspace + spaceUsed32;
	workspaceSize -= (spaceUsed32 << 2);

	/* normal FSE decoding mode */
	NCountLength = FSE_पढ़ोNCount(counting, &maxSymbolValue, &tableLog, istart, cSrcSize);
	अगर (FSE_isError(NCountLength))
		वापस NCountLength;
	// अगर (NCountLength >= cSrcSize) वापस ERROR(srcSize_wrong);   /* too small input size; supposed to be alपढ़ोy checked in NCountLength, only reमुख्यing
	// हाल : NCountLength==cSrcSize */
	अगर (tableLog > maxLog)
		वापस ERROR(tableLog_tooLarge);
	ip += NCountLength;
	cSrcSize -= NCountLength;

	CHECK_F(FSE_buildDTable_wksp(dt, counting, maxSymbolValue, tableLog, workspace, workspaceSize));

	वापस FSE_decompress_usingDTable(dst, dstCapacity, ip, cSrcSize, dt); /* always वापस, even अगर it is an error code */
पूर्ण
