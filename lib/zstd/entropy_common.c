<शैली गुरु>
/*
 * Common functions of New Generation Entropy library
 * Copyright (C) 2016, Yann Collet.
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

/* *************************************
*  Dependencies
***************************************/
#समावेश "error_private.h" /* ERR_*, ERROR */
#समावेश "fse.h"
#समावेश "huf.h"
#समावेश "mem.h"

/*===   Version   ===*/
अचिन्हित FSE_versionNumber(व्योम) अणु वापस FSE_VERSION_NUMBER; पूर्ण

/*===   Error Management   ===*/
अचिन्हित FSE_isError(माप_प्रकार code) अणु वापस ERR_isError(code); पूर्ण

अचिन्हित HUF_isError(माप_प्रकार code) अणु वापस ERR_isError(code); पूर्ण

/*-**************************************************************
*  FSE NCount encoding-decoding
****************************************************************/
माप_प्रकार FSE_पढ़ोNCount(लघु *normalizedCounter, अचिन्हित *maxSVPtr, अचिन्हित *tableLogPtr, स्थिर व्योम *headerBuffer, माप_प्रकार hbSize)
अणु
	स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)headerBuffer;
	स्थिर BYTE *स्थिर iend = istart + hbSize;
	स्थिर BYTE *ip = istart;
	पूर्णांक nbBits;
	पूर्णांक reमुख्यing;
	पूर्णांक threshold;
	U32 bitStream;
	पूर्णांक bitCount;
	अचिन्हित अक्षरnum = 0;
	पूर्णांक previous0 = 0;

	अगर (hbSize < 4)
		वापस ERROR(srcSize_wrong);
	bitStream = ZSTD_पढ़ोLE32(ip);
	nbBits = (bitStream & 0xF) + FSE_MIN_TABLELOG; /* extract tableLog */
	अगर (nbBits > FSE_TABLELOG_ABSOLUTE_MAX)
		वापस ERROR(tableLog_tooLarge);
	bitStream >>= 4;
	bitCount = 4;
	*tableLogPtr = nbBits;
	reमुख्यing = (1 << nbBits) + 1;
	threshold = 1 << nbBits;
	nbBits++;

	जबतक ((reमुख्यing > 1) & (अक्षरnum <= *maxSVPtr)) अणु
		अगर (previous0) अणु
			अचिन्हित n0 = अक्षरnum;
			जबतक ((bitStream & 0xFFFF) == 0xFFFF) अणु
				n0 += 24;
				अगर (ip < iend - 5) अणु
					ip += 2;
					bitStream = ZSTD_पढ़ोLE32(ip) >> bitCount;
				पूर्ण अन्यथा अणु
					bitStream >>= 16;
					bitCount += 16;
				पूर्ण
			पूर्ण
			जबतक ((bitStream & 3) == 3) अणु
				n0 += 3;
				bitStream >>= 2;
				bitCount += 2;
			पूर्ण
			n0 += bitStream & 3;
			bitCount += 2;
			अगर (n0 > *maxSVPtr)
				वापस ERROR(maxSymbolValue_tooSmall);
			जबतक (अक्षरnum < n0)
				normalizedCounter[अक्षरnum++] = 0;
			अगर ((ip <= iend - 7) || (ip + (bitCount >> 3) <= iend - 4)) अणु
				ip += bitCount >> 3;
				bitCount &= 7;
				bitStream = ZSTD_पढ़ोLE32(ip) >> bitCount;
			पूर्ण अन्यथा अणु
				bitStream >>= 2;
			पूर्ण
		पूर्ण
		अणु
			पूर्णांक स्थिर max = (2 * threshold - 1) - reमुख्यing;
			पूर्णांक count;

			अगर ((bitStream & (threshold - 1)) < (U32)max) अणु
				count = bitStream & (threshold - 1);
				bitCount += nbBits - 1;
			पूर्ण अन्यथा अणु
				count = bitStream & (2 * threshold - 1);
				अगर (count >= threshold)
					count -= max;
				bitCount += nbBits;
			पूर्ण

			count--;				 /* extra accuracy */
			reमुख्यing -= count < 0 ? -count : count; /* -1 means +1 */
			normalizedCounter[अक्षरnum++] = (लघु)count;
			previous0 = !count;
			जबतक (reमुख्यing < threshold) अणु
				nbBits--;
				threshold >>= 1;
			पूर्ण

			अगर ((ip <= iend - 7) || (ip + (bitCount >> 3) <= iend - 4)) अणु
				ip += bitCount >> 3;
				bitCount &= 7;
			पूर्ण अन्यथा अणु
				bitCount -= (पूर्णांक)(8 * (iend - 4 - ip));
				ip = iend - 4;
			पूर्ण
			bitStream = ZSTD_पढ़ोLE32(ip) >> (bitCount & 31);
		पूर्ण
	पूर्ण /* जबतक ((reमुख्यing>1) & (अक्षरnum<=*maxSVPtr)) */
	अगर (reमुख्यing != 1)
		वापस ERROR(corruption_detected);
	अगर (bitCount > 32)
		वापस ERROR(corruption_detected);
	*maxSVPtr = अक्षरnum - 1;

	ip += (bitCount + 7) >> 3;
	वापस ip - istart;
पूर्ण

/*! HUF_पढ़ोStats() :
	Read compact Huffman tree, saved by HUF_ग_लिखोCTable().
	`huffWeight` is destination buffer.
	`rankStats` is assumed to be a table of at least HUF_TABLELOG_MAX U32.
	@वापस : size पढ़ो from `src` , or an error Code .
	Note : Needed by HUF_पढ़ोCTable() and HUF_पढ़ोDTableX?() .
*/
माप_प्रकार HUF_पढ़ोStats_wksp(BYTE *huffWeight, माप_प्रकार hwSize, U32 *rankStats, U32 *nbSymbolsPtr, U32 *tableLogPtr, स्थिर व्योम *src, माप_प्रकार srcSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	U32 weightTotal;
	स्थिर BYTE *ip = (स्थिर BYTE *)src;
	माप_प्रकार iSize;
	माप_प्रकार oSize;

	अगर (!srcSize)
		वापस ERROR(srcSize_wrong);
	iSize = ip[0];
	/* स_रखो(huffWeight, 0, hwSize);   */ /* is not necessary, even though some analyzer complain ... */

	अगर (iSize >= 128) अणु /* special header */
		oSize = iSize - 127;
		iSize = ((oSize + 1) / 2);
		अगर (iSize + 1 > srcSize)
			वापस ERROR(srcSize_wrong);
		अगर (oSize >= hwSize)
			वापस ERROR(corruption_detected);
		ip += 1;
		अणु
			U32 n;
			क्रम (n = 0; n < oSize; n += 2) अणु
				huffWeight[n] = ip[n / 2] >> 4;
				huffWeight[n + 1] = ip[n / 2] & 15;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु						 /* header compressed with FSE (normal हाल) */
		अगर (iSize + 1 > srcSize)
			वापस ERROR(srcSize_wrong);
		oSize = FSE_decompress_wksp(huffWeight, hwSize - 1, ip + 1, iSize, 6, workspace, workspaceSize); /* max (hwSize-1) values decoded, as last one is implied */
		अगर (FSE_isError(oSize))
			वापस oSize;
	पूर्ण

	/* collect weight stats */
	स_रखो(rankStats, 0, (HUF_TABLELOG_MAX + 1) * माप(U32));
	weightTotal = 0;
	अणु
		U32 n;
		क्रम (n = 0; n < oSize; n++) अणु
			अगर (huffWeight[n] >= HUF_TABLELOG_MAX)
				वापस ERROR(corruption_detected);
			rankStats[huffWeight[n]]++;
			weightTotal += (1 << huffWeight[n]) >> 1;
		पूर्ण
	पूर्ण
	अगर (weightTotal == 0)
		वापस ERROR(corruption_detected);

	/* get last non-null symbol weight (implied, total must be 2^n) */
	अणु
		U32 स्थिर tableLog = BIT_highbit32(weightTotal) + 1;
		अगर (tableLog > HUF_TABLELOG_MAX)
			वापस ERROR(corruption_detected);
		*tableLogPtr = tableLog;
		/* determine last weight */
		अणु
			U32 स्थिर total = 1 << tableLog;
			U32 स्थिर rest = total - weightTotal;
			U32 स्थिर verअगर = 1 << BIT_highbit32(rest);
			U32 स्थिर lastWeight = BIT_highbit32(rest) + 1;
			अगर (verअगर != rest)
				वापस ERROR(corruption_detected); /* last value must be a clean घातer of 2 */
			huffWeight[oSize] = (BYTE)lastWeight;
			rankStats[lastWeight]++;
		पूर्ण
	पूर्ण

	/* check tree स्थिरruction validity */
	अगर ((rankStats[1] < 2) || (rankStats[1] & 1))
		वापस ERROR(corruption_detected); /* by स्थिरruction : at least 2 elts of rank 1, must be even */

	/* results */
	*nbSymbolsPtr = (U32)(oSize + 1);
	वापस iSize + 1;
पूर्ण
