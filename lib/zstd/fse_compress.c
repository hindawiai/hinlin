<शैली गुरु>
/*
 * FSE : Finite State Entropy encoder
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
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/माला.स> /* स_नकल, स_रखो */

/* **************************************************************
*  Error Management
****************************************************************/
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

/* FSE_buildCTable_wksp() :
 * Same as FSE_buildCTable(), but using an बाह्यally allocated scratch buffer (`workSpace`).
 * wkspSize should be sized to handle worst हाल situation, which is `1<<max_tableLog * माप(FSE_FUNCTION_TYPE)`
 * workSpace must also be properly aligned with FSE_FUNCTION_TYPE requirements
 */
माप_प्रकार FSE_buildCTable_wksp(FSE_CTable *ct, स्थिर लघु *normalizedCounter, अचिन्हित maxSymbolValue, अचिन्हित tableLog, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	U32 स्थिर tableSize = 1 << tableLog;
	U32 स्थिर tableMask = tableSize - 1;
	व्योम *स्थिर ptr = ct;
	U16 *स्थिर tableU16 = ((U16 *)ptr) + 2;
	व्योम *स्थिर FSCT = ((U32 *)ptr) + 1 /* header */ + (tableLog ? tableSize >> 1 : 1);
	FSE_symbolCompressionTransक्रमm *स्थिर symbolTT = (FSE_symbolCompressionTransक्रमm *)(FSCT);
	U32 स्थिर step = FSE_TABLESTEP(tableSize);
	U32 highThreshold = tableSize - 1;

	U32 *cumul;
	FSE_FUNCTION_TYPE *tableSymbol;
	माप_प्रकार spaceUsed32 = 0;

	cumul = (U32 *)workspace + spaceUsed32;
	spaceUsed32 += FSE_MAX_SYMBOL_VALUE + 2;
	tableSymbol = (FSE_FUNCTION_TYPE *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += ALIGN(माप(FSE_FUNCTION_TYPE) * ((माप_प्रकार)1 << tableLog), माप(U32)) >> 2;

	अगर ((spaceUsed32 << 2) > workspaceSize)
		वापस ERROR(tableLog_tooLarge);
	workspace = (U32 *)workspace + spaceUsed32;
	workspaceSize -= (spaceUsed32 << 2);

	/* CTable header */
	tableU16[-2] = (U16)tableLog;
	tableU16[-1] = (U16)maxSymbolValue;

	/* For explanations on how to distribute symbol values over the table :
	*  http://fastcompression.blogspot.fr/2014/02/fse-distributing-symbol-values.hपंचांगl */

	/* symbol start positions */
	अणु
		U32 u;
		cumul[0] = 0;
		क्रम (u = 1; u <= maxSymbolValue + 1; u++) अणु
			अगर (normalizedCounter[u - 1] == -1) अणु /* Low proba symbol */
				cumul[u] = cumul[u - 1] + 1;
				tableSymbol[highThreshold--] = (FSE_FUNCTION_TYPE)(u - 1);
			पूर्ण अन्यथा अणु
				cumul[u] = cumul[u - 1] + normalizedCounter[u - 1];
			पूर्ण
		पूर्ण
		cumul[maxSymbolValue + 1] = tableSize + 1;
	पूर्ण

	/* Spपढ़ो symbols */
	अणु
		U32 position = 0;
		U32 symbol;
		क्रम (symbol = 0; symbol <= maxSymbolValue; symbol++) अणु
			पूर्णांक nbOccurences;
			क्रम (nbOccurences = 0; nbOccurences < normalizedCounter[symbol]; nbOccurences++) अणु
				tableSymbol[position] = (FSE_FUNCTION_TYPE)symbol;
				position = (position + step) & tableMask;
				जबतक (position > highThreshold)
					position = (position + step) & tableMask; /* Low proba area */
			पूर्ण
		पूर्ण

		अगर (position != 0)
			वापस ERROR(GENERIC); /* Must have gone through all positions */
	पूर्ण

	/* Build table */
	अणु
		U32 u;
		क्रम (u = 0; u < tableSize; u++) अणु
			FSE_FUNCTION_TYPE s = tableSymbol[u];	/* note : अटल analyzer may not understand tableSymbol is properly initialized */
			tableU16[cumul[s]++] = (U16)(tableSize + u); /* TableU16 : sorted by symbol order; gives next state value */
		पूर्ण
	पूर्ण

	/* Build Symbol Transक्रमmation Table */
	अणु
		अचिन्हित total = 0;
		अचिन्हित s;
		क्रम (s = 0; s <= maxSymbolValue; s++) अणु
			चयन (normalizedCounter[s]) अणु
			हाल 0: अवरोध;

			हाल -1:
			हाल 1:
				symbolTT[s].deltaNbBits = (tableLog << 16) - (1 << tableLog);
				symbolTT[s].deltaFindState = total - 1;
				total++;
				अवरोध;
			शेष: अणु
				U32 स्थिर maxBitsOut = tableLog - BIT_highbit32(normalizedCounter[s] - 1);
				U32 स्थिर minStatePlus = normalizedCounter[s] << maxBitsOut;
				symbolTT[s].deltaNbBits = (maxBitsOut << 16) - minStatePlus;
				symbolTT[s].deltaFindState = total - normalizedCounter[s];
				total += normalizedCounter[s];
			पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*-**************************************************************
*  FSE NCount encoding-decoding
****************************************************************/
माप_प्रकार FSE_NCountWriteBound(अचिन्हित maxSymbolValue, अचिन्हित tableLog)
अणु
	माप_प्रकार स्थिर maxHeaderSize = (((maxSymbolValue + 1) * tableLog) >> 3) + 3;
	वापस maxSymbolValue ? maxHeaderSize : FSE_NCOUNTBOUND; /* maxSymbolValue==0 ? use शेष */
पूर्ण

अटल माप_प्रकार FSE_ग_लिखोNCount_generic(व्योम *header, माप_प्रकार headerBufferSize, स्थिर लघु *normalizedCounter, अचिन्हित maxSymbolValue, अचिन्हित tableLog,
				      अचिन्हित ग_लिखोIsSafe)
अणु
	BYTE *स्थिर ostart = (BYTE *)header;
	BYTE *out = ostart;
	BYTE *स्थिर oend = ostart + headerBufferSize;
	पूर्णांक nbBits;
	स्थिर पूर्णांक tableSize = 1 << tableLog;
	पूर्णांक reमुख्यing;
	पूर्णांक threshold;
	U32 bitStream;
	पूर्णांक bitCount;
	अचिन्हित अक्षरnum = 0;
	पूर्णांक previous0 = 0;

	bitStream = 0;
	bitCount = 0;
	/* Table Size */
	bitStream += (tableLog - FSE_MIN_TABLELOG) << bitCount;
	bitCount += 4;

	/* Init */
	reमुख्यing = tableSize + 1; /* +1 क्रम extra accuracy */
	threshold = tableSize;
	nbBits = tableLog + 1;

	जबतक (reमुख्यing > 1) अणु /* stops at 1 */
		अगर (previous0) अणु
			अचिन्हित start = अक्षरnum;
			जबतक (!normalizedCounter[अक्षरnum])
				अक्षरnum++;
			जबतक (अक्षरnum >= start + 24) अणु
				start += 24;
				bitStream += 0xFFFFU << bitCount;
				अगर ((!ग_लिखोIsSafe) && (out > oend - 2))
					वापस ERROR(dstSize_tooSmall); /* Buffer overflow */
				out[0] = (BYTE)bitStream;
				out[1] = (BYTE)(bitStream >> 8);
				out += 2;
				bitStream >>= 16;
			पूर्ण
			जबतक (अक्षरnum >= start + 3) अणु
				start += 3;
				bitStream += 3 << bitCount;
				bitCount += 2;
			पूर्ण
			bitStream += (अक्षरnum - start) << bitCount;
			bitCount += 2;
			अगर (bitCount > 16) अणु
				अगर ((!ग_लिखोIsSafe) && (out > oend - 2))
					वापस ERROR(dstSize_tooSmall); /* Buffer overflow */
				out[0] = (BYTE)bitStream;
				out[1] = (BYTE)(bitStream >> 8);
				out += 2;
				bitStream >>= 16;
				bitCount -= 16;
			पूर्ण
		पूर्ण
		अणु
			पूर्णांक count = normalizedCounter[अक्षरnum++];
			पूर्णांक स्थिर max = (2 * threshold - 1) - reमुख्यing;
			reमुख्यing -= count < 0 ? -count : count;
			count++; /* +1 क्रम extra accuracy */
			अगर (count >= threshold)
				count += max; /* [0..max[ [max..threshold[ (...) [threshold+max 2*threshold[ */
			bitStream += count << bitCount;
			bitCount += nbBits;
			bitCount -= (count < max);
			previous0 = (count == 1);
			अगर (reमुख्यing < 1)
				वापस ERROR(GENERIC);
			जबतक (reमुख्यing < threshold)
				nbBits--, threshold >>= 1;
		पूर्ण
		अगर (bitCount > 16) अणु
			अगर ((!ग_लिखोIsSafe) && (out > oend - 2))
				वापस ERROR(dstSize_tooSmall); /* Buffer overflow */
			out[0] = (BYTE)bitStream;
			out[1] = (BYTE)(bitStream >> 8);
			out += 2;
			bitStream >>= 16;
			bitCount -= 16;
		पूर्ण
	पूर्ण

	/* flush reमुख्यing bitStream */
	अगर ((!ग_लिखोIsSafe) && (out > oend - 2))
		वापस ERROR(dstSize_tooSmall); /* Buffer overflow */
	out[0] = (BYTE)bitStream;
	out[1] = (BYTE)(bitStream >> 8);
	out += (bitCount + 7) / 8;

	अगर (अक्षरnum > maxSymbolValue + 1)
		वापस ERROR(GENERIC);

	वापस (out - ostart);
पूर्ण

माप_प्रकार FSE_ग_लिखोNCount(व्योम *buffer, माप_प्रकार bufferSize, स्थिर लघु *normalizedCounter, अचिन्हित maxSymbolValue, अचिन्हित tableLog)
अणु
	अगर (tableLog > FSE_MAX_TABLELOG)
		वापस ERROR(tableLog_tooLarge); /* Unsupported */
	अगर (tableLog < FSE_MIN_TABLELOG)
		वापस ERROR(GENERIC); /* Unsupported */

	अगर (bufferSize < FSE_NCountWriteBound(maxSymbolValue, tableLog))
		वापस FSE_ग_लिखोNCount_generic(buffer, bufferSize, normalizedCounter, maxSymbolValue, tableLog, 0);

	वापस FSE_ग_लिखोNCount_generic(buffer, bufferSize, normalizedCounter, maxSymbolValue, tableLog, 1);
पूर्ण

/*-**************************************************************
*  Counting histogram
****************************************************************/
/*! FSE_count_simple
	This function counts byte values within `src`, and store the histogram पूर्णांकo table `count`.
	It करोesn't use any additional memory.
	But this function is unsafe : it करोesn't check that all values within `src` can fit पूर्णांकo `count`.
	For this reason, prefer using a table `count` with 256 elements.
	@वापस : count of most numerous element
*/
माप_प्रकार FSE_count_simple(अचिन्हित *count, अचिन्हित *maxSymbolValuePtr, स्थिर व्योम *src, माप_प्रकार srcSize)
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *)src;
	स्थिर BYTE *स्थिर end = ip + srcSize;
	अचिन्हित maxSymbolValue = *maxSymbolValuePtr;
	अचिन्हित max = 0;

	स_रखो(count, 0, (maxSymbolValue + 1) * माप(*count));
	अगर (srcSize == 0) अणु
		*maxSymbolValuePtr = 0;
		वापस 0;
	पूर्ण

	जबतक (ip < end)
		count[*ip++]++;

	जबतक (!count[maxSymbolValue])
		maxSymbolValue--;
	*maxSymbolValuePtr = maxSymbolValue;

	अणु
		U32 s;
		क्रम (s = 0; s <= maxSymbolValue; s++)
			अगर (count[s] > max)
				max = count[s];
	पूर्ण

	वापस (माप_प्रकार)max;
पूर्ण

/* FSE_count_parallel_wksp() :
 * Same as FSE_count_parallel(), but using an बाह्यally provided scratch buffer.
 * `workSpace` size must be a minimum of `1024 * माप(अचिन्हित)`` */
अटल माप_प्रकार FSE_count_parallel_wksp(अचिन्हित *count, अचिन्हित *maxSymbolValuePtr, स्थिर व्योम *source, माप_प्रकार sourceSize, अचिन्हित checkMax,
				      अचिन्हित *स्थिर workSpace)
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *)source;
	स्थिर BYTE *स्थिर iend = ip + sourceSize;
	अचिन्हित maxSymbolValue = *maxSymbolValuePtr;
	अचिन्हित max = 0;
	U32 *स्थिर Counting1 = workSpace;
	U32 *स्थिर Counting2 = Counting1 + 256;
	U32 *स्थिर Counting3 = Counting2 + 256;
	U32 *स्थिर Counting4 = Counting3 + 256;

	स_रखो(Counting1, 0, 4 * 256 * माप(अचिन्हित));

	/* safety checks */
	अगर (!sourceSize) अणु
		स_रखो(count, 0, maxSymbolValue + 1);
		*maxSymbolValuePtr = 0;
		वापस 0;
	पूर्ण
	अगर (!maxSymbolValue)
		maxSymbolValue = 255; /* 0 == शेष */

	/* by stripes of 16 bytes */
	अणु
		U32 cached = ZSTD_पढ़ो32(ip);
		ip += 4;
		जबतक (ip < iend - 15) अणु
			U32 c = cached;
			cached = ZSTD_पढ़ो32(ip);
			ip += 4;
			Counting1[(BYTE)c]++;
			Counting2[(BYTE)(c >> 8)]++;
			Counting3[(BYTE)(c >> 16)]++;
			Counting4[c >> 24]++;
			c = cached;
			cached = ZSTD_पढ़ो32(ip);
			ip += 4;
			Counting1[(BYTE)c]++;
			Counting2[(BYTE)(c >> 8)]++;
			Counting3[(BYTE)(c >> 16)]++;
			Counting4[c >> 24]++;
			c = cached;
			cached = ZSTD_पढ़ो32(ip);
			ip += 4;
			Counting1[(BYTE)c]++;
			Counting2[(BYTE)(c >> 8)]++;
			Counting3[(BYTE)(c >> 16)]++;
			Counting4[c >> 24]++;
			c = cached;
			cached = ZSTD_पढ़ो32(ip);
			ip += 4;
			Counting1[(BYTE)c]++;
			Counting2[(BYTE)(c >> 8)]++;
			Counting3[(BYTE)(c >> 16)]++;
			Counting4[c >> 24]++;
		पूर्ण
		ip -= 4;
	पूर्ण

	/* finish last symbols */
	जबतक (ip < iend)
		Counting1[*ip++]++;

	अगर (checkMax) अणु /* verअगरy stats will fit पूर्णांकo destination table */
		U32 s;
		क्रम (s = 255; s > maxSymbolValue; s--) अणु
			Counting1[s] += Counting2[s] + Counting3[s] + Counting4[s];
			अगर (Counting1[s])
				वापस ERROR(maxSymbolValue_tooSmall);
		पूर्ण
	पूर्ण

	अणु
		U32 s;
		क्रम (s = 0; s <= maxSymbolValue; s++) अणु
			count[s] = Counting1[s] + Counting2[s] + Counting3[s] + Counting4[s];
			अगर (count[s] > max)
				max = count[s];
		पूर्ण
	पूर्ण

	जबतक (!count[maxSymbolValue])
		maxSymbolValue--;
	*maxSymbolValuePtr = maxSymbolValue;
	वापस (माप_प्रकार)max;
पूर्ण

/* FSE_countFast_wksp() :
 * Same as FSE_countFast(), but using an बाह्यally provided scratch buffer.
 * `workSpace` size must be table of >= `1024` अचिन्हित */
माप_प्रकार FSE_countFast_wksp(अचिन्हित *count, अचिन्हित *maxSymbolValuePtr, स्थिर व्योम *source, माप_प्रकार sourceSize, अचिन्हित *workSpace)
अणु
	अगर (sourceSize < 1500)
		वापस FSE_count_simple(count, maxSymbolValuePtr, source, sourceSize);
	वापस FSE_count_parallel_wksp(count, maxSymbolValuePtr, source, sourceSize, 0, workSpace);
पूर्ण

/* FSE_count_wksp() :
 * Same as FSE_count(), but using an बाह्यally provided scratch buffer.
 * `workSpace` size must be table of >= `1024` अचिन्हित */
माप_प्रकार FSE_count_wksp(अचिन्हित *count, अचिन्हित *maxSymbolValuePtr, स्थिर व्योम *source, माप_प्रकार sourceSize, अचिन्हित *workSpace)
अणु
	अगर (*maxSymbolValuePtr < 255)
		वापस FSE_count_parallel_wksp(count, maxSymbolValuePtr, source, sourceSize, 1, workSpace);
	*maxSymbolValuePtr = 255;
	वापस FSE_countFast_wksp(count, maxSymbolValuePtr, source, sourceSize, workSpace);
पूर्ण

/*-**************************************************************
*  FSE Compression Code
****************************************************************/
/*! FSE_माप_CTable() :
	FSE_CTable is a variable size काष्ठाure which contains :
	`U16 tableLog;`
	`U16 maxSymbolValue;`
	`U16 nextStateNumber[1 << tableLog];`                         // This size is variable
	`FSE_symbolCompressionTransक्रमm symbolTT[maxSymbolValue+1];`  // This size is variable
Allocation is manual (C standard करोes not support variable-size काष्ठाures).
*/
माप_प्रकार FSE_माप_CTable(अचिन्हित maxSymbolValue, अचिन्हित tableLog)
अणु
	अगर (tableLog > FSE_MAX_TABLELOG)
		वापस ERROR(tableLog_tooLarge);
	वापस FSE_CTABLE_SIZE_U32(tableLog, maxSymbolValue) * माप(U32);
पूर्ण

/* provides the minimum logSize to safely represent a distribution */
अटल अचिन्हित FSE_minTableLog(माप_प्रकार srcSize, अचिन्हित maxSymbolValue)
अणु
	U32 minBitsSrc = BIT_highbit32((U32)(srcSize - 1)) + 1;
	U32 minBitsSymbols = BIT_highbit32(maxSymbolValue) + 2;
	U32 minBits = minBitsSrc < minBitsSymbols ? minBitsSrc : minBitsSymbols;
	वापस minBits;
पूर्ण

अचिन्हित FSE_optimalTableLog_पूर्णांकernal(अचिन्हित maxTableLog, माप_प्रकार srcSize, अचिन्हित maxSymbolValue, अचिन्हित minus)
अणु
	U32 maxBitsSrc = BIT_highbit32((U32)(srcSize - 1)) - minus;
	U32 tableLog = maxTableLog;
	U32 minBits = FSE_minTableLog(srcSize, maxSymbolValue);
	अगर (tableLog == 0)
		tableLog = FSE_DEFAULT_TABLELOG;
	अगर (maxBitsSrc < tableLog)
		tableLog = maxBitsSrc; /* Accuracy can be reduced */
	अगर (minBits > tableLog)
		tableLog = minBits; /* Need a minimum to safely represent all symbol values */
	अगर (tableLog < FSE_MIN_TABLELOG)
		tableLog = FSE_MIN_TABLELOG;
	अगर (tableLog > FSE_MAX_TABLELOG)
		tableLog = FSE_MAX_TABLELOG;
	वापस tableLog;
पूर्ण

अचिन्हित FSE_optimalTableLog(अचिन्हित maxTableLog, माप_प्रकार srcSize, अचिन्हित maxSymbolValue)
अणु
	वापस FSE_optimalTableLog_पूर्णांकernal(maxTableLog, srcSize, maxSymbolValue, 2);
पूर्ण

/* Secondary normalization method.
   To be used when primary method fails. */

अटल माप_प्रकार FSE_normalizeM2(लघु *norm, U32 tableLog, स्थिर अचिन्हित *count, माप_प्रकार total, U32 maxSymbolValue)
अणु
	लघु स्थिर NOT_YET_ASSIGNED = -2;
	U32 s;
	U32 distributed = 0;
	U32 ToDistribute;

	/* Init */
	U32 स्थिर lowThreshold = (U32)(total >> tableLog);
	U32 lowOne = (U32)((total * 3) >> (tableLog + 1));

	क्रम (s = 0; s <= maxSymbolValue; s++) अणु
		अगर (count[s] == 0) अणु
			norm[s] = 0;
			जारी;
		पूर्ण
		अगर (count[s] <= lowThreshold) अणु
			norm[s] = -1;
			distributed++;
			total -= count[s];
			जारी;
		पूर्ण
		अगर (count[s] <= lowOne) अणु
			norm[s] = 1;
			distributed++;
			total -= count[s];
			जारी;
		पूर्ण

		norm[s] = NOT_YET_ASSIGNED;
	पूर्ण
	ToDistribute = (1 << tableLog) - distributed;

	अगर ((total / ToDistribute) > lowOne) अणु
		/* risk of rounding to zero */
		lowOne = (U32)((total * 3) / (ToDistribute * 2));
		क्रम (s = 0; s <= maxSymbolValue; s++) अणु
			अगर ((norm[s] == NOT_YET_ASSIGNED) && (count[s] <= lowOne)) अणु
				norm[s] = 1;
				distributed++;
				total -= count[s];
				जारी;
			पूर्ण
		पूर्ण
		ToDistribute = (1 << tableLog) - distributed;
	पूर्ण

	अगर (distributed == maxSymbolValue + 1) अणु
		/* all values are pretty poor;
		   probably incompressible data (should have alपढ़ोy been detected);
		   find max, then give all reमुख्यing poपूर्णांकs to max */
		U32 maxV = 0, maxC = 0;
		क्रम (s = 0; s <= maxSymbolValue; s++)
			अगर (count[s] > maxC)
				maxV = s, maxC = count[s];
		norm[maxV] += (लघु)ToDistribute;
		वापस 0;
	पूर्ण

	अगर (total == 0) अणु
		/* all of the symbols were low enough क्रम the lowOne or lowThreshold */
		क्रम (s = 0; ToDistribute > 0; s = (s + 1) % (maxSymbolValue + 1))
			अगर (norm[s] > 0)
				ToDistribute--, norm[s]++;
		वापस 0;
	पूर्ण

	अणु
		U64 स्थिर vStepLog = 62 - tableLog;
		U64 स्थिर mid = (1ULL << (vStepLog - 1)) - 1;
		U64 स्थिर rStep = भाग_u64((((U64)1 << vStepLog) * ToDistribute) + mid, (U32)total); /* scale on reमुख्यing */
		U64 पंचांगpTotal = mid;
		क्रम (s = 0; s <= maxSymbolValue; s++) अणु
			अगर (norm[s] == NOT_YET_ASSIGNED) अणु
				U64 स्थिर end = पंचांगpTotal + (count[s] * rStep);
				U32 स्थिर sStart = (U32)(पंचांगpTotal >> vStepLog);
				U32 स्थिर sEnd = (U32)(end >> vStepLog);
				U32 स्थिर weight = sEnd - sStart;
				अगर (weight < 1)
					वापस ERROR(GENERIC);
				norm[s] = (लघु)weight;
				पंचांगpTotal = end;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

माप_प्रकार FSE_normalizeCount(लघु *normalizedCounter, अचिन्हित tableLog, स्थिर अचिन्हित *count, माप_प्रकार total, अचिन्हित maxSymbolValue)
अणु
	/* Sanity checks */
	अगर (tableLog == 0)
		tableLog = FSE_DEFAULT_TABLELOG;
	अगर (tableLog < FSE_MIN_TABLELOG)
		वापस ERROR(GENERIC); /* Unsupported size */
	अगर (tableLog > FSE_MAX_TABLELOG)
		वापस ERROR(tableLog_tooLarge); /* Unsupported size */
	अगर (tableLog < FSE_minTableLog(total, maxSymbolValue))
		वापस ERROR(GENERIC); /* Too small tableLog, compression potentially impossible */

	अणु
		U32 स्थिर rtbTable[] = अणु0, 473195, 504333, 520860, 550000, 700000, 750000, 830000पूर्ण;
		U64 स्थिर scale = 62 - tableLog;
		U64 स्थिर step = भाग_u64((U64)1 << 62, (U32)total); /* <== here, one भागision ! */
		U64 स्थिर vStep = 1ULL << (scale - 20);
		पूर्णांक stillToDistribute = 1 << tableLog;
		अचिन्हित s;
		अचिन्हित largest = 0;
		लघु largestP = 0;
		U32 lowThreshold = (U32)(total >> tableLog);

		क्रम (s = 0; s <= maxSymbolValue; s++) अणु
			अगर (count[s] == total)
				वापस 0; /* rle special हाल */
			अगर (count[s] == 0) अणु
				normalizedCounter[s] = 0;
				जारी;
			पूर्ण
			अगर (count[s] <= lowThreshold) अणु
				normalizedCounter[s] = -1;
				stillToDistribute--;
			पूर्ण अन्यथा अणु
				लघु proba = (लघु)((count[s] * step) >> scale);
				अगर (proba < 8) अणु
					U64 restToBeat = vStep * rtbTable[proba];
					proba += (count[s] * step) - ((U64)proba << scale) > restToBeat;
				पूर्ण
				अगर (proba > largestP)
					largestP = proba, largest = s;
				normalizedCounter[s] = proba;
				stillToDistribute -= proba;
			पूर्ण
		पूर्ण
		अगर (-stillToDistribute >= (normalizedCounter[largest] >> 1)) अणु
			/* corner हाल, need another normalization method */
			माप_प्रकार स्थिर errorCode = FSE_normalizeM2(normalizedCounter, tableLog, count, total, maxSymbolValue);
			अगर (FSE_isError(errorCode))
				वापस errorCode;
		पूर्ण अन्यथा
			normalizedCounter[largest] += (लघु)stillToDistribute;
	पूर्ण

	वापस tableLog;
पूर्ण

/* fake FSE_CTable, क्रम raw (uncompressed) input */
माप_प्रकार FSE_buildCTable_raw(FSE_CTable *ct, अचिन्हित nbBits)
अणु
	स्थिर अचिन्हित tableSize = 1 << nbBits;
	स्थिर अचिन्हित tableMask = tableSize - 1;
	स्थिर अचिन्हित maxSymbolValue = tableMask;
	व्योम *स्थिर ptr = ct;
	U16 *स्थिर tableU16 = ((U16 *)ptr) + 2;
	व्योम *स्थिर FSCT = ((U32 *)ptr) + 1 /* header */ + (tableSize >> 1); /* assumption : tableLog >= 1 */
	FSE_symbolCompressionTransक्रमm *स्थिर symbolTT = (FSE_symbolCompressionTransक्रमm *)(FSCT);
	अचिन्हित s;

	/* Sanity checks */
	अगर (nbBits < 1)
		वापस ERROR(GENERIC); /* min size */

	/* header */
	tableU16[-2] = (U16)nbBits;
	tableU16[-1] = (U16)maxSymbolValue;

	/* Build table */
	क्रम (s = 0; s < tableSize; s++)
		tableU16[s] = (U16)(tableSize + s);

	/* Build Symbol Transक्रमmation Table */
	अणु
		स्थिर U32 deltaNbBits = (nbBits << 16) - (1 << nbBits);
		क्रम (s = 0; s <= maxSymbolValue; s++) अणु
			symbolTT[s].deltaNbBits = deltaNbBits;
			symbolTT[s].deltaFindState = s - 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* fake FSE_CTable, क्रम rle input (always same symbol) */
माप_प्रकार FSE_buildCTable_rle(FSE_CTable *ct, BYTE symbolValue)
अणु
	व्योम *ptr = ct;
	U16 *tableU16 = ((U16 *)ptr) + 2;
	व्योम *FSCTptr = (U32 *)ptr + 2;
	FSE_symbolCompressionTransक्रमm *symbolTT = (FSE_symbolCompressionTransक्रमm *)FSCTptr;

	/* header */
	tableU16[-2] = (U16)0;
	tableU16[-1] = (U16)symbolValue;

	/* Build table */
	tableU16[0] = 0;
	tableU16[1] = 0; /* just in हाल */

	/* Build Symbol Transक्रमmation Table */
	symbolTT[symbolValue].deltaNbBits = 0;
	symbolTT[symbolValue].deltaFindState = 0;

	वापस 0;
पूर्ण

अटल माप_प्रकार FSE_compress_usingCTable_generic(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर FSE_CTable *ct, स्थिर अचिन्हित fast)
अणु
	स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)src;
	स्थिर BYTE *स्थिर iend = istart + srcSize;
	स्थिर BYTE *ip = iend;

	BIT_CStream_t bitC;
	FSE_CState_t CState1, CState2;

	/* init */
	अगर (srcSize <= 2)
		वापस 0;
	अणु
		माप_प्रकार स्थिर initError = BIT_initCStream(&bitC, dst, dstSize);
		अगर (FSE_isError(initError))
			वापस 0; /* not enough space available to ग_लिखो a bitstream */
	पूर्ण

#घोषणा FSE_FLUSHBITS(s) (fast ? BIT_flushBitsFast(s) : BIT_flushBits(s))

	अगर (srcSize & 1) अणु
		FSE_initCState2(&CState1, ct, *--ip);
		FSE_initCState2(&CState2, ct, *--ip);
		FSE_encodeSymbol(&bitC, &CState1, *--ip);
		FSE_FLUSHBITS(&bitC);
	पूर्ण अन्यथा अणु
		FSE_initCState2(&CState2, ct, *--ip);
		FSE_initCState2(&CState1, ct, *--ip);
	पूर्ण

	/* join to mod 4 */
	srcSize -= 2;
	अगर ((माप(bitC.bitContainer) * 8 > FSE_MAX_TABLELOG * 4 + 7) && (srcSize & 2)) अणु /* test bit 2 */
		FSE_encodeSymbol(&bitC, &CState2, *--ip);
		FSE_encodeSymbol(&bitC, &CState1, *--ip);
		FSE_FLUSHBITS(&bitC);
	पूर्ण

	/* 2 or 4 encoding per loop */
	जबतक (ip > istart) अणु

		FSE_encodeSymbol(&bitC, &CState2, *--ip);

		अगर (माप(bitC.bitContainer) * 8 < FSE_MAX_TABLELOG * 2 + 7) /* this test must be अटल */
			FSE_FLUSHBITS(&bitC);

		FSE_encodeSymbol(&bitC, &CState1, *--ip);

		अगर (माप(bitC.bitContainer) * 8 > FSE_MAX_TABLELOG * 4 + 7) अणु /* this test must be अटल */
			FSE_encodeSymbol(&bitC, &CState2, *--ip);
			FSE_encodeSymbol(&bitC, &CState1, *--ip);
		पूर्ण

		FSE_FLUSHBITS(&bitC);
	पूर्ण

	FSE_flushCState(&bitC, &CState2);
	FSE_flushCState(&bitC, &CState1);
	वापस BIT_बंदCStream(&bitC);
पूर्ण

माप_प्रकार FSE_compress_usingCTable(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर FSE_CTable *ct)
अणु
	अचिन्हित स्थिर fast = (dstSize >= FSE_BLOCKBOUND(srcSize));

	अगर (fast)
		वापस FSE_compress_usingCTable_generic(dst, dstSize, src, srcSize, ct, 1);
	अन्यथा
		वापस FSE_compress_usingCTable_generic(dst, dstSize, src, srcSize, ct, 0);
पूर्ण

माप_प्रकार FSE_compressBound(माप_प्रकार size) अणु वापस FSE_COMPRESSBOUND(size); पूर्ण
