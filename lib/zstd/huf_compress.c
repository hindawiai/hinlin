<शैली गुरु>
/*
 * Huffman encoder, part of New Generation Entropy library
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
*  Includes
****************************************************************/
#समावेश "bitstream.h"
#समावेश "fse.h" /* header compression */
#समावेश "huf.h"
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स> /* स_नकल, स_रखो */

/* **************************************************************
*  Error Management
****************************************************************/
#घोषणा HUF_STATIC_ASSERT(c)                                   \
	अणु                                                      \
		क्रमागत अणु HUF_अटल_निश्चित = 1 / (पूर्णांक)(!!(c)) पूर्ण; \
	पूर्ण /* use only *after* variable declarations */
#घोषणा CHECK_V_F(e, f)     \
	माप_प्रकार स्थिर e = f; \
	अगर (ERR_isError(e)) \
	वापस f
#घोषणा CHECK_F(f)                        \
	अणु                                 \
		CHECK_V_F(_var_err__, f); \
	पूर्ण

/* **************************************************************
*  Utils
****************************************************************/
अचिन्हित HUF_optimalTableLog(अचिन्हित maxTableLog, माप_प्रकार srcSize, अचिन्हित maxSymbolValue)
अणु
	वापस FSE_optimalTableLog_पूर्णांकernal(maxTableLog, srcSize, maxSymbolValue, 1);
पूर्ण

/* *******************************************************
*  HUF : Huffman block compression
*********************************************************/
/* HUF_compressWeights() :
 * Same as FSE_compress(), but dedicated to huff0's weights compression.
 * The use हाल needs much less stack memory.
 * Note : all elements within weightTable are supposed to be <= HUF_TABLELOG_MAX.
 */
#घोषणा MAX_FSE_TABLELOG_FOR_HUFF_HEADER 6
माप_प्रकार HUF_compressWeights_wksp(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *weightTable, माप_प्रकार wtSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	BYTE *स्थिर ostart = (BYTE *)dst;
	BYTE *op = ostart;
	BYTE *स्थिर oend = ostart + dstSize;

	U32 maxSymbolValue = HUF_TABLELOG_MAX;
	U32 tableLog = MAX_FSE_TABLELOG_FOR_HUFF_HEADER;

	FSE_CTable *CTable;
	U32 *count;
	S16 *norm;
	माप_प्रकार spaceUsed32 = 0;

	HUF_STATIC_ASSERT(माप(FSE_CTable) == माप(U32));

	CTable = (FSE_CTable *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += FSE_CTABLE_SIZE_U32(MAX_FSE_TABLELOG_FOR_HUFF_HEADER, HUF_TABLELOG_MAX);
	count = (U32 *)workspace + spaceUsed32;
	spaceUsed32 += HUF_TABLELOG_MAX + 1;
	norm = (S16 *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += ALIGN(माप(S16) * (HUF_TABLELOG_MAX + 1), माप(U32)) >> 2;

	अगर ((spaceUsed32 << 2) > workspaceSize)
		वापस ERROR(tableLog_tooLarge);
	workspace = (U32 *)workspace + spaceUsed32;
	workspaceSize -= (spaceUsed32 << 2);

	/* init conditions */
	अगर (wtSize <= 1)
		वापस 0; /* Not compressible */

	/* Scan input and build symbol stats */
	अणु
		CHECK_V_F(maxCount, FSE_count_simple(count, &maxSymbolValue, weightTable, wtSize));
		अगर (maxCount == wtSize)
			वापस 1; /* only a single symbol in src : rle */
		अगर (maxCount == 1)
			वापस 0; /* each symbol present maximum once => not compressible */
	पूर्ण

	tableLog = FSE_optimalTableLog(tableLog, wtSize, maxSymbolValue);
	CHECK_F(FSE_normalizeCount(norm, tableLog, count, wtSize, maxSymbolValue));

	/* Write table description header */
	अणु
		CHECK_V_F(hSize, FSE_ग_लिखोNCount(op, oend - op, norm, maxSymbolValue, tableLog));
		op += hSize;
	पूर्ण

	/* Compress */
	CHECK_F(FSE_buildCTable_wksp(CTable, norm, maxSymbolValue, tableLog, workspace, workspaceSize));
	अणु
		CHECK_V_F(cSize, FSE_compress_usingCTable(op, oend - op, weightTable, wtSize, CTable));
		अगर (cSize == 0)
			वापस 0; /* not enough space क्रम compressed data */
		op += cSize;
	पूर्ण

	वापस op - ostart;
पूर्ण

काष्ठा HUF_CElt_s अणु
	U16 val;
	BYTE nbBits;
पूर्ण; /* प्रकार'd to HUF_CElt within "huf.h" */

/*! HUF_ग_लिखोCTable_wksp() :
	`CTable` : Huffman tree to save, using huf representation.
	@वापस : size of saved CTable */
माप_प्रकार HUF_ग_लिखोCTable_wksp(व्योम *dst, माप_प्रकार maxDstSize, स्थिर HUF_CElt *CTable, U32 maxSymbolValue, U32 huffLog, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	BYTE *op = (BYTE *)dst;
	U32 n;

	BYTE *bitsToWeight;
	BYTE *huffWeight;
	माप_प्रकार spaceUsed32 = 0;

	bitsToWeight = (BYTE *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += ALIGN(HUF_TABLELOG_MAX + 1, माप(U32)) >> 2;
	huffWeight = (BYTE *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += ALIGN(HUF_SYMBOLVALUE_MAX, माप(U32)) >> 2;

	अगर ((spaceUsed32 << 2) > workspaceSize)
		वापस ERROR(tableLog_tooLarge);
	workspace = (U32 *)workspace + spaceUsed32;
	workspaceSize -= (spaceUsed32 << 2);

	/* check conditions */
	अगर (maxSymbolValue > HUF_SYMBOLVALUE_MAX)
		वापस ERROR(maxSymbolValue_tooLarge);

	/* convert to weight */
	bitsToWeight[0] = 0;
	क्रम (n = 1; n < huffLog + 1; n++)
		bitsToWeight[n] = (BYTE)(huffLog + 1 - n);
	क्रम (n = 0; n < maxSymbolValue; n++)
		huffWeight[n] = bitsToWeight[CTable[n].nbBits];

	/* attempt weights compression by FSE */
	अणु
		CHECK_V_F(hSize, HUF_compressWeights_wksp(op + 1, maxDstSize - 1, huffWeight, maxSymbolValue, workspace, workspaceSize));
		अगर ((hSize > 1) & (hSize < maxSymbolValue / 2)) अणु /* FSE compressed */
			op[0] = (BYTE)hSize;
			वापस hSize + 1;
		पूर्ण
	पूर्ण

	/* ग_लिखो raw values as 4-bits (max : 15) */
	अगर (maxSymbolValue > (256 - 128))
		वापस ERROR(GENERIC); /* should not happen : likely means source cannot be compressed */
	अगर (((maxSymbolValue + 1) / 2) + 1 > maxDstSize)
		वापस ERROR(dstSize_tooSmall); /* not enough space within dst buffer */
	op[0] = (BYTE)(128 /*special हाल*/ + (maxSymbolValue - 1));
	huffWeight[maxSymbolValue] = 0; /* to be sure it करोesn't cause msan issue in final combination */
	क्रम (n = 0; n < maxSymbolValue; n += 2)
		op[(n / 2) + 1] = (BYTE)((huffWeight[n] << 4) + huffWeight[n + 1]);
	वापस ((maxSymbolValue + 1) / 2) + 1;
पूर्ण

माप_प्रकार HUF_पढ़ोCTable_wksp(HUF_CElt *CTable, U32 maxSymbolValue, स्थिर व्योम *src, माप_प्रकार srcSize, व्योम *workspace, माप_प्रकार workspaceSize)
अणु
	U32 *rankVal;
	BYTE *huffWeight;
	U32 tableLog = 0;
	U32 nbSymbols = 0;
	माप_प्रकार पढ़ोSize;
	माप_प्रकार spaceUsed32 = 0;

	rankVal = (U32 *)workspace + spaceUsed32;
	spaceUsed32 += HUF_TABLELOG_ABSOLUTEMAX + 1;
	huffWeight = (BYTE *)((U32 *)workspace + spaceUsed32);
	spaceUsed32 += ALIGN(HUF_SYMBOLVALUE_MAX + 1, माप(U32)) >> 2;

	अगर ((spaceUsed32 << 2) > workspaceSize)
		वापस ERROR(tableLog_tooLarge);
	workspace = (U32 *)workspace + spaceUsed32;
	workspaceSize -= (spaceUsed32 << 2);

	/* get symbol weights */
	पढ़ोSize = HUF_पढ़ोStats_wksp(huffWeight, HUF_SYMBOLVALUE_MAX + 1, rankVal, &nbSymbols, &tableLog, src, srcSize, workspace, workspaceSize);
	अगर (ERR_isError(पढ़ोSize))
		वापस पढ़ोSize;

	/* check result */
	अगर (tableLog > HUF_TABLELOG_MAX)
		वापस ERROR(tableLog_tooLarge);
	अगर (nbSymbols > maxSymbolValue + 1)
		वापस ERROR(maxSymbolValue_tooSmall);

	/* Prepare base value per rank */
	अणु
		U32 n, nextRankStart = 0;
		क्रम (n = 1; n <= tableLog; n++) अणु
			U32 curr = nextRankStart;
			nextRankStart += (rankVal[n] << (n - 1));
			rankVal[n] = curr;
		पूर्ण
	पूर्ण

	/* fill nbBits */
	अणु
		U32 n;
		क्रम (n = 0; n < nbSymbols; n++) अणु
			स्थिर U32 w = huffWeight[n];
			CTable[n].nbBits = (BYTE)(tableLog + 1 - w);
		पूर्ण
	पूर्ण

	/* fill val */
	अणु
		U16 nbPerRank[HUF_TABLELOG_MAX + 2] = अणु0पूर्ण; /* support w=0=>n=tableLog+1 */
		U16 valPerRank[HUF_TABLELOG_MAX + 2] = अणु0पूर्ण;
		अणु
			U32 n;
			क्रम (n = 0; n < nbSymbols; n++)
				nbPerRank[CTable[n].nbBits]++;
		पूर्ण
		/* determine stating value per rank */
		valPerRank[tableLog + 1] = 0; /* क्रम w==0 */
		अणु
			U16 min = 0;
			U32 n;
			क्रम (n = tableLog; n > 0; n--) अणु /* start at n=tablelog <-> w=1 */
				valPerRank[n] = min;     /* get starting value within each rank */
				min += nbPerRank[n];
				min >>= 1;
			पूर्ण
		पूर्ण
		/* assign value within rank, symbol order */
		अणु
			U32 n;
			क्रम (n = 0; n <= maxSymbolValue; n++)
				CTable[n].val = valPerRank[CTable[n].nbBits]++;
		पूर्ण
	पूर्ण

	वापस पढ़ोSize;
पूर्ण

प्रकार काष्ठा nodeElt_s अणु
	U32 count;
	U16 parent;
	BYTE byte;
	BYTE nbBits;
पूर्ण nodeElt;

अटल U32 HUF_setMaxHeight(nodeElt *huffNode, U32 lastNonNull, U32 maxNbBits)
अणु
	स्थिर U32 largestBits = huffNode[lastNonNull].nbBits;
	अगर (largestBits <= maxNbBits)
		वापस largestBits; /* early निकास : no elt > maxNbBits */

	/* there are several too large elements (at least >= 2) */
	अणु
		पूर्णांक totalCost = 0;
		स्थिर U32 baseCost = 1 << (largestBits - maxNbBits);
		U32 n = lastNonNull;

		जबतक (huffNode[n].nbBits > maxNbBits) अणु
			totalCost += baseCost - (1 << (largestBits - huffNode[n].nbBits));
			huffNode[n].nbBits = (BYTE)maxNbBits;
			n--;
		पूर्ण /* n stops at huffNode[n].nbBits <= maxNbBits */
		जबतक (huffNode[n].nbBits == maxNbBits)
			n--; /* n end at index of smallest symbol using < maxNbBits */

		/* renorm totalCost */
		totalCost >>= (largestBits - maxNbBits); /* note : totalCost is necessarily a multiple of baseCost */

		/* repay normalized cost */
		अणु
			U32 स्थिर noSymbol = 0xF0F0F0F0;
			U32 rankLast[HUF_TABLELOG_MAX + 2];
			पूर्णांक pos;

			/* Get pos of last (smallest) symbol per rank */
			स_रखो(rankLast, 0xF0, माप(rankLast));
			अणु
				U32 currNbBits = maxNbBits;
				क्रम (pos = n; pos >= 0; pos--) अणु
					अगर (huffNode[pos].nbBits >= currNbBits)
						जारी;
					currNbBits = huffNode[pos].nbBits; /* < maxNbBits */
					rankLast[maxNbBits - currNbBits] = pos;
				पूर्ण
			पूर्ण

			जबतक (totalCost > 0) अणु
				U32 nBitsToDecrease = BIT_highbit32(totalCost) + 1;
				क्रम (; nBitsToDecrease > 1; nBitsToDecrease--) अणु
					U32 highPos = rankLast[nBitsToDecrease];
					U32 lowPos = rankLast[nBitsToDecrease - 1];
					अगर (highPos == noSymbol)
						जारी;
					अगर (lowPos == noSymbol)
						अवरोध;
					अणु
						U32 स्थिर highTotal = huffNode[highPos].count;
						U32 स्थिर lowTotal = 2 * huffNode[lowPos].count;
						अगर (highTotal <= lowTotal)
							अवरोध;
					पूर्ण
				पूर्ण
				/* only triggered when no more rank 1 symbol left => find बंदst one (note : there is necessarily at least one !) */
				/* HUF_MAX_TABLELOG test just to please gcc 5+; but it should not be necessary */
				जबतक ((nBitsToDecrease <= HUF_TABLELOG_MAX) && (rankLast[nBitsToDecrease] == noSymbol))
					nBitsToDecrease++;
				totalCost -= 1 << (nBitsToDecrease - 1);
				अगर (rankLast[nBitsToDecrease - 1] == noSymbol)
					rankLast[nBitsToDecrease - 1] = rankLast[nBitsToDecrease]; /* this rank is no दीर्घer empty */
				huffNode[rankLast[nBitsToDecrease]].nbBits++;
				अगर (rankLast[nBitsToDecrease] == 0) /* special हाल, reached largest symbol */
					rankLast[nBitsToDecrease] = noSymbol;
				अन्यथा अणु
					rankLast[nBitsToDecrease]--;
					अगर (huffNode[rankLast[nBitsToDecrease]].nbBits != maxNbBits - nBitsToDecrease)
						rankLast[nBitsToDecrease] = noSymbol; /* this rank is now empty */
				पूर्ण
			पूर्ण /* जबतक (totalCost > 0) */

			जबतक (totalCost < 0) अणु		       /* Someबार, cost correction overshoot */
				अगर (rankLast[1] == noSymbol) अणु /* special हाल : no rank 1 symbol (using maxNbBits-1); let's create one from largest rank 0
								  (using maxNbBits) */
					जबतक (huffNode[n].nbBits == maxNbBits)
						n--;
					huffNode[n + 1].nbBits--;
					rankLast[1] = n + 1;
					totalCost++;
					जारी;
				पूर्ण
				huffNode[rankLast[1] + 1].nbBits--;
				rankLast[1]++;
				totalCost++;
			पूर्ण
		पूर्ण
	पूर्ण /* there are several too large elements (at least >= 2) */

	वापस maxNbBits;
पूर्ण

प्रकार काष्ठा अणु
	U32 base;
	U32 curr;
पूर्ण rankPos;

अटल व्योम HUF_sort(nodeElt *huffNode, स्थिर U32 *count, U32 maxSymbolValue)
अणु
	rankPos rank[32];
	U32 n;

	स_रखो(rank, 0, माप(rank));
	क्रम (n = 0; n <= maxSymbolValue; n++) अणु
		U32 r = BIT_highbit32(count[n] + 1);
		rank[r].base++;
	पूर्ण
	क्रम (n = 30; n > 0; n--)
		rank[n - 1].base += rank[n].base;
	क्रम (n = 0; n < 32; n++)
		rank[n].curr = rank[n].base;
	क्रम (n = 0; n <= maxSymbolValue; n++) अणु
		U32 स्थिर c = count[n];
		U32 स्थिर r = BIT_highbit32(c + 1) + 1;
		U32 pos = rank[r].curr++;
		जबतक ((pos > rank[r].base) && (c > huffNode[pos - 1].count))
			huffNode[pos] = huffNode[pos - 1], pos--;
		huffNode[pos].count = c;
		huffNode[pos].byte = (BYTE)n;
	पूर्ण
पूर्ण

/** HUF_buildCTable_wksp() :
 *  Same as HUF_buildCTable(), but using बाह्यally allocated scratch buffer.
 *  `workSpace` must be aligned on 4-bytes boundaries, and be at least as large as a table of 1024 अचिन्हित.
 */
#घोषणा STARTNODE (HUF_SYMBOLVALUE_MAX + 1)
प्रकार nodeElt huffNodeTable[2 * HUF_SYMBOLVALUE_MAX + 1 + 1];
माप_प्रकार HUF_buildCTable_wksp(HUF_CElt *tree, स्थिर U32 *count, U32 maxSymbolValue, U32 maxNbBits, व्योम *workSpace, माप_प्रकार wkspSize)
अणु
	nodeElt *स्थिर huffNode0 = (nodeElt *)workSpace;
	nodeElt *स्थिर huffNode = huffNode0 + 1;
	U32 n, nonNullRank;
	पूर्णांक lowS, lowN;
	U16 nodeNb = STARTNODE;
	U32 nodeRoot;

	/* safety checks */
	अगर (wkspSize < माप(huffNodeTable))
		वापस ERROR(GENERIC); /* workSpace is not large enough */
	अगर (maxNbBits == 0)
		maxNbBits = HUF_TABLELOG_DEFAULT;
	अगर (maxSymbolValue > HUF_SYMBOLVALUE_MAX)
		वापस ERROR(GENERIC);
	स_रखो(huffNode0, 0, माप(huffNodeTable));

	/* sort, decreasing order */
	HUF_sort(huffNode, count, maxSymbolValue);

	/* init क्रम parents */
	nonNullRank = maxSymbolValue;
	जबतक (huffNode[nonNullRank].count == 0)
		nonNullRank--;
	lowS = nonNullRank;
	nodeRoot = nodeNb + lowS - 1;
	lowN = nodeNb;
	huffNode[nodeNb].count = huffNode[lowS].count + huffNode[lowS - 1].count;
	huffNode[lowS].parent = huffNode[lowS - 1].parent = nodeNb;
	nodeNb++;
	lowS -= 2;
	क्रम (n = nodeNb; n <= nodeRoot; n++)
		huffNode[n].count = (U32)(1U << 30);
	huffNode0[0].count = (U32)(1U << 31); /* fake entry, strong barrier */

	/* create parents */
	जबतक (nodeNb <= nodeRoot) अणु
		U32 n1 = (huffNode[lowS].count < huffNode[lowN].count) ? lowS-- : lowN++;
		U32 n2 = (huffNode[lowS].count < huffNode[lowN].count) ? lowS-- : lowN++;
		huffNode[nodeNb].count = huffNode[n1].count + huffNode[n2].count;
		huffNode[n1].parent = huffNode[n2].parent = nodeNb;
		nodeNb++;
	पूर्ण

	/* distribute weights (unlimited tree height) */
	huffNode[nodeRoot].nbBits = 0;
	क्रम (n = nodeRoot - 1; n >= STARTNODE; n--)
		huffNode[n].nbBits = huffNode[huffNode[n].parent].nbBits + 1;
	क्रम (n = 0; n <= nonNullRank; n++)
		huffNode[n].nbBits = huffNode[huffNode[n].parent].nbBits + 1;

	/* enक्रमce maxTableLog */
	maxNbBits = HUF_setMaxHeight(huffNode, nonNullRank, maxNbBits);

	/* fill result पूर्णांकo tree (val, nbBits) */
	अणु
		U16 nbPerRank[HUF_TABLELOG_MAX + 1] = अणु0पूर्ण;
		U16 valPerRank[HUF_TABLELOG_MAX + 1] = अणु0पूर्ण;
		अगर (maxNbBits > HUF_TABLELOG_MAX)
			वापस ERROR(GENERIC); /* check fit पूर्णांकo table */
		क्रम (n = 0; n <= nonNullRank; n++)
			nbPerRank[huffNode[n].nbBits]++;
		/* determine stating value per rank */
		अणु
			U16 min = 0;
			क्रम (n = maxNbBits; n > 0; n--) अणु
				valPerRank[n] = min; /* get starting value within each rank */
				min += nbPerRank[n];
				min >>= 1;
			पूर्ण
		पूर्ण
		क्रम (n = 0; n <= maxSymbolValue; n++)
			tree[huffNode[n].byte].nbBits = huffNode[n].nbBits; /* push nbBits per symbol, symbol order */
		क्रम (n = 0; n <= maxSymbolValue; n++)
			tree[n].val = valPerRank[tree[n].nbBits]++; /* assign value within rank, symbol order */
	पूर्ण

	वापस maxNbBits;
पूर्ण

अटल माप_प्रकार HUF_estimateCompressedSize(HUF_CElt *CTable, स्थिर अचिन्हित *count, अचिन्हित maxSymbolValue)
अणु
	माप_प्रकार nbBits = 0;
	पूर्णांक s;
	क्रम (s = 0; s <= (पूर्णांक)maxSymbolValue; ++s) अणु
		nbBits += CTable[s].nbBits * count[s];
	पूर्ण
	वापस nbBits >> 3;
पूर्ण

अटल पूर्णांक HUF_validateCTable(स्थिर HUF_CElt *CTable, स्थिर अचिन्हित *count, अचिन्हित maxSymbolValue)
अणु
	पूर्णांक bad = 0;
	पूर्णांक s;
	क्रम (s = 0; s <= (पूर्णांक)maxSymbolValue; ++s) अणु
		bad |= (count[s] != 0) & (CTable[s].nbBits == 0);
	पूर्ण
	वापस !bad;
पूर्ण

अटल व्योम HUF_encodeSymbol(BIT_CStream_t *bitCPtr, U32 symbol, स्थिर HUF_CElt *CTable)
अणु
	BIT_addBitsFast(bitCPtr, CTable[symbol].val, CTable[symbol].nbBits);
पूर्ण

माप_प्रकार HUF_compressBound(माप_प्रकार size) अणु वापस HUF_COMPRESSBOUND(size); पूर्ण

#घोषणा HUF_FLUSHBITS(s)  BIT_flushBits(s)

#घोषणा HUF_FLUSHBITS_1(stream)                                            \
	अगर (माप((stream)->bitContainer) * 8 < HUF_TABLELOG_MAX * 2 + 7) \
	HUF_FLUSHBITS(stream)

#घोषणा HUF_FLUSHBITS_2(stream)                                            \
	अगर (माप((stream)->bitContainer) * 8 < HUF_TABLELOG_MAX * 4 + 7) \
	HUF_FLUSHBITS(stream)

माप_प्रकार HUF_compress1X_usingCTable(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर HUF_CElt *CTable)
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *)src;
	BYTE *स्थिर ostart = (BYTE *)dst;
	BYTE *स्थिर oend = ostart + dstSize;
	BYTE *op = ostart;
	माप_प्रकार n;
	BIT_CStream_t bitC;

	/* init */
	अगर (dstSize < 8)
		वापस 0; /* not enough space to compress */
	अणु
		माप_प्रकार स्थिर initErr = BIT_initCStream(&bitC, op, oend - op);
		अगर (HUF_isError(initErr))
			वापस 0;
	पूर्ण

	n = srcSize & ~3; /* join to mod 4 */
	चयन (srcSize & 3) अणु
	हाल 3: HUF_encodeSymbol(&bitC, ip[n + 2], CTable); HUF_FLUSHBITS_2(&bitC);
		fallthrough;
	हाल 2: HUF_encodeSymbol(&bitC, ip[n + 1], CTable); HUF_FLUSHBITS_1(&bitC);
		fallthrough;
	हाल 1: HUF_encodeSymbol(&bitC, ip[n + 0], CTable); HUF_FLUSHBITS(&bitC);
		fallthrough;
	हाल 0:
	शेष:;
	पूर्ण

	क्रम (; n > 0; n -= 4) अणु /* note : n&3==0 at this stage */
		HUF_encodeSymbol(&bitC, ip[n - 1], CTable);
		HUF_FLUSHBITS_1(&bitC);
		HUF_encodeSymbol(&bitC, ip[n - 2], CTable);
		HUF_FLUSHBITS_2(&bitC);
		HUF_encodeSymbol(&bitC, ip[n - 3], CTable);
		HUF_FLUSHBITS_1(&bitC);
		HUF_encodeSymbol(&bitC, ip[n - 4], CTable);
		HUF_FLUSHBITS(&bitC);
	पूर्ण

	वापस BIT_बंदCStream(&bitC);
पूर्ण

माप_प्रकार HUF_compress4X_usingCTable(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर HUF_CElt *CTable)
अणु
	माप_प्रकार स्थिर segmentSize = (srcSize + 3) / 4; /* first 3 segments */
	स्थिर BYTE *ip = (स्थिर BYTE *)src;
	स्थिर BYTE *स्थिर iend = ip + srcSize;
	BYTE *स्थिर ostart = (BYTE *)dst;
	BYTE *स्थिर oend = ostart + dstSize;
	BYTE *op = ostart;

	अगर (dstSize < 6 + 1 + 1 + 1 + 8)
		वापस 0; /* minimum space to compress successfully */
	अगर (srcSize < 12)
		वापस 0; /* no saving possible : too small input */
	op += 6;	  /* jumpTable */

	अणु
		CHECK_V_F(cSize, HUF_compress1X_usingCTable(op, oend - op, ip, segmentSize, CTable));
		अगर (cSize == 0)
			वापस 0;
		ZSTD_ग_लिखोLE16(ostart, (U16)cSize);
		op += cSize;
	पूर्ण

	ip += segmentSize;
	अणु
		CHECK_V_F(cSize, HUF_compress1X_usingCTable(op, oend - op, ip, segmentSize, CTable));
		अगर (cSize == 0)
			वापस 0;
		ZSTD_ग_लिखोLE16(ostart + 2, (U16)cSize);
		op += cSize;
	पूर्ण

	ip += segmentSize;
	अणु
		CHECK_V_F(cSize, HUF_compress1X_usingCTable(op, oend - op, ip, segmentSize, CTable));
		अगर (cSize == 0)
			वापस 0;
		ZSTD_ग_लिखोLE16(ostart + 4, (U16)cSize);
		op += cSize;
	पूर्ण

	ip += segmentSize;
	अणु
		CHECK_V_F(cSize, HUF_compress1X_usingCTable(op, oend - op, ip, iend - ip, CTable));
		अगर (cSize == 0)
			वापस 0;
		op += cSize;
	पूर्ण

	वापस op - ostart;
पूर्ण

अटल माप_प्रकार HUF_compressCTable_पूर्णांकernal(BYTE *स्थिर ostart, BYTE *op, BYTE *स्थिर oend, स्थिर व्योम *src, माप_प्रकार srcSize, अचिन्हित singleStream,
					  स्थिर HUF_CElt *CTable)
अणु
	माप_प्रकार स्थिर cSize =
	    singleStream ? HUF_compress1X_usingCTable(op, oend - op, src, srcSize, CTable) : HUF_compress4X_usingCTable(op, oend - op, src, srcSize, CTable);
	अगर (HUF_isError(cSize)) अणु
		वापस cSize;
	पूर्ण
	अगर (cSize == 0) अणु
		वापस 0;
	पूर्ण /* uncompressible */
	op += cSize;
	/* check compressibility */
	अगर ((माप_प्रकार)(op - ostart) >= srcSize - 1) अणु
		वापस 0;
	पूर्ण
	वापस op - ostart;
पूर्ण

/* `workSpace` must a table of at least 1024 अचिन्हित */
अटल माप_प्रकार HUF_compress_पूर्णांकernal(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, अचिन्हित maxSymbolValue, अचिन्हित huffLog,
				    अचिन्हित singleStream, व्योम *workSpace, माप_प्रकार wkspSize, HUF_CElt *oldHufTable, HUF_repeat *repeat, पूर्णांक preferRepeat)
अणु
	BYTE *स्थिर ostart = (BYTE *)dst;
	BYTE *स्थिर oend = ostart + dstSize;
	BYTE *op = ostart;

	U32 *count;
	माप_प्रकार स्थिर countSize = माप(U32) * (HUF_SYMBOLVALUE_MAX + 1);
	HUF_CElt *CTable;
	माप_प्रकार स्थिर CTableSize = माप(HUF_CElt) * (HUF_SYMBOLVALUE_MAX + 1);

	/* checks & inits */
	अगर (wkspSize < माप(huffNodeTable) + countSize + CTableSize)
		वापस ERROR(GENERIC);
	अगर (!srcSize)
		वापस 0; /* Uncompressed (note : 1 means rle, so first byte must be correct) */
	अगर (!dstSize)
		वापस 0; /* cannot fit within dst budget */
	अगर (srcSize > HUF_BLOCKSIZE_MAX)
		वापस ERROR(srcSize_wrong); /* curr block size limit */
	अगर (huffLog > HUF_TABLELOG_MAX)
		वापस ERROR(tableLog_tooLarge);
	अगर (!maxSymbolValue)
		maxSymbolValue = HUF_SYMBOLVALUE_MAX;
	अगर (!huffLog)
		huffLog = HUF_TABLELOG_DEFAULT;

	count = (U32 *)workSpace;
	workSpace = (BYTE *)workSpace + countSize;
	wkspSize -= countSize;
	CTable = (HUF_CElt *)workSpace;
	workSpace = (BYTE *)workSpace + CTableSize;
	wkspSize -= CTableSize;

	/* Heuristic : If we करोn't need to check the validity of the old table use the old table क्रम small inमाला_दो */
	अगर (preferRepeat && repeat && *repeat == HUF_repeat_valid) अणु
		वापस HUF_compressCTable_पूर्णांकernal(ostart, op, oend, src, srcSize, singleStream, oldHufTable);
	पूर्ण

	/* Scan input and build symbol stats */
	अणु
		CHECK_V_F(largest, FSE_count_wksp(count, &maxSymbolValue, (स्थिर BYTE *)src, srcSize, (U32 *)workSpace));
		अगर (largest == srcSize) अणु
			*ostart = ((स्थिर BYTE *)src)[0];
			वापस 1;
		पूर्ण /* single symbol, rle */
		अगर (largest <= (srcSize >> 7) + 1)
			वापस 0; /* Fast heuristic : not compressible enough */
	पूर्ण

	/* Check validity of previous table */
	अगर (repeat && *repeat == HUF_repeat_check && !HUF_validateCTable(oldHufTable, count, maxSymbolValue)) अणु
		*repeat = HUF_repeat_none;
	पूर्ण
	/* Heuristic : use existing table क्रम small inमाला_दो */
	अगर (preferRepeat && repeat && *repeat != HUF_repeat_none) अणु
		वापस HUF_compressCTable_पूर्णांकernal(ostart, op, oend, src, srcSize, singleStream, oldHufTable);
	पूर्ण

	/* Build Huffman Tree */
	huffLog = HUF_optimalTableLog(huffLog, srcSize, maxSymbolValue);
	अणु
		CHECK_V_F(maxBits, HUF_buildCTable_wksp(CTable, count, maxSymbolValue, huffLog, workSpace, wkspSize));
		huffLog = (U32)maxBits;
		/* Zero the unused symbols so we can check it क्रम validity */
		स_रखो(CTable + maxSymbolValue + 1, 0, CTableSize - (maxSymbolValue + 1) * माप(HUF_CElt));
	पूर्ण

	/* Write table description header */
	अणु
		CHECK_V_F(hSize, HUF_ग_लिखोCTable_wksp(op, dstSize, CTable, maxSymbolValue, huffLog, workSpace, wkspSize));
		/* Check अगर using the previous table will be beneficial */
		अगर (repeat && *repeat != HUF_repeat_none) अणु
			माप_प्रकार स्थिर oldSize = HUF_estimateCompressedSize(oldHufTable, count, maxSymbolValue);
			माप_प्रकार स्थिर newSize = HUF_estimateCompressedSize(CTable, count, maxSymbolValue);
			अगर (oldSize <= hSize + newSize || hSize + 12 >= srcSize) अणु
				वापस HUF_compressCTable_पूर्णांकernal(ostart, op, oend, src, srcSize, singleStream, oldHufTable);
			पूर्ण
		पूर्ण
		/* Use the new table */
		अगर (hSize + 12ul >= srcSize) अणु
			वापस 0;
		पूर्ण
		op += hSize;
		अगर (repeat) अणु
			*repeat = HUF_repeat_none;
		पूर्ण
		अगर (oldHufTable) अणु
			स_नकल(oldHufTable, CTable, CTableSize);
		पूर्ण /* Save the new table */
	पूर्ण
	वापस HUF_compressCTable_पूर्णांकernal(ostart, op, oend, src, srcSize, singleStream, CTable);
पूर्ण

माप_प्रकार HUF_compress1X_wksp(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, अचिन्हित maxSymbolValue, अचिन्हित huffLog, व्योम *workSpace,
			   माप_प्रकार wkspSize)
अणु
	वापस HUF_compress_पूर्णांकernal(dst, dstSize, src, srcSize, maxSymbolValue, huffLog, 1 /* single stream */, workSpace, wkspSize, शून्य, शून्य, 0);
पूर्ण

माप_प्रकार HUF_compress1X_repeat(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, अचिन्हित maxSymbolValue, अचिन्हित huffLog, व्योम *workSpace,
			     माप_प्रकार wkspSize, HUF_CElt *hufTable, HUF_repeat *repeat, पूर्णांक preferRepeat)
अणु
	वापस HUF_compress_पूर्णांकernal(dst, dstSize, src, srcSize, maxSymbolValue, huffLog, 1 /* single stream */, workSpace, wkspSize, hufTable, repeat,
				     preferRepeat);
पूर्ण

माप_प्रकार HUF_compress4X_wksp(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, अचिन्हित maxSymbolValue, अचिन्हित huffLog, व्योम *workSpace,
			   माप_प्रकार wkspSize)
अणु
	वापस HUF_compress_पूर्णांकernal(dst, dstSize, src, srcSize, maxSymbolValue, huffLog, 0 /* 4 streams */, workSpace, wkspSize, शून्य, शून्य, 0);
पूर्ण

माप_प्रकार HUF_compress4X_repeat(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, अचिन्हित maxSymbolValue, अचिन्हित huffLog, व्योम *workSpace,
			     माप_प्रकार wkspSize, HUF_CElt *hufTable, HUF_repeat *repeat, पूर्णांक preferRepeat)
अणु
	वापस HUF_compress_पूर्णांकernal(dst, dstSize, src, srcSize, maxSymbolValue, huffLog, 0 /* 4 streams */, workSpace, wkspSize, hufTable, repeat,
				     preferRepeat);
पूर्ण
