<शैली गुरु>
/*
 * LZ4 HC - High Compression Mode of LZ4
 * Copyright (C) 2011-2015, Yann Collet.
 *
 * BSD 2 - Clause License (http://www.खोलोsource.org/licenses/bsd - license.php)
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
 *
 *	Changed क्रम kernel usage by:
 *	Sven Schmidt <4sschmid@inक्रमmatik.uni-hamburg.de>
 */

/*-************************************
 *	Dependencies
 **************************************/
#समावेश <linux/lz4.h>
#समावेश "lz4defs.h"
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स> /* स_रखो */

/* *************************************
 *	Local Constants and types
 ***************************************/

#घोषणा OPTIMAL_ML (पूर्णांक)((ML_MASK - 1) + MINMATCH)

#घोषणा HASH_FUNCTION(i)	(((i) * 2654435761U) \
	>> ((MINMATCH*8) - LZ4HC_HASH_LOG))
#घोषणा DELTANEXTU16(p)	chainTable[(U16)(p)] /* faster */

अटल U32 LZ4HC_hashPtr(स्थिर व्योम *ptr)
अणु
	वापस HASH_FUNCTION(LZ4_पढ़ो32(ptr));
पूर्ण

/**************************************
 *	HC Compression
 **************************************/
अटल व्योम LZ4HC_init(LZ4HC_CCtx_पूर्णांकernal *hc4, स्थिर BYTE *start)
अणु
	स_रखो((व्योम *)hc4->hashTable, 0, माप(hc4->hashTable));
	स_रखो(hc4->chainTable, 0xFF, माप(hc4->chainTable));
	hc4->nextToUpdate = 64 * KB;
	hc4->base = start - 64 * KB;
	hc4->end = start;
	hc4->dictBase = start - 64 * KB;
	hc4->dictLimit = 64 * KB;
	hc4->lowLimit = 64 * KB;
पूर्ण

/* Update chains up to ip (excluded) */
अटल FORCE_INLINE व्योम LZ4HC_Insert(LZ4HC_CCtx_पूर्णांकernal *hc4,
	स्थिर BYTE *ip)
अणु
	U16 * स्थिर chainTable = hc4->chainTable;
	U32 * स्थिर hashTable	= hc4->hashTable;
	स्थिर BYTE * स्थिर base = hc4->base;
	U32 स्थिर target = (U32)(ip - base);
	U32 idx = hc4->nextToUpdate;

	जबतक (idx < target) अणु
		U32 स्थिर h = LZ4HC_hashPtr(base + idx);
		माप_प्रकार delta = idx - hashTable[h];

		अगर (delta > MAX_DISTANCE)
			delta = MAX_DISTANCE;

		DELTANEXTU16(idx) = (U16)delta;

		hashTable[h] = idx;
		idx++;
	पूर्ण

	hc4->nextToUpdate = target;
पूर्ण

अटल FORCE_INLINE पूर्णांक LZ4HC_InsertAndFindBestMatch(
	LZ4HC_CCtx_पूर्णांकernal *hc4, /* Index table will be updated */
	स्थिर BYTE *ip,
	स्थिर BYTE * स्थिर iLimit,
	स्थिर BYTE **matchpos,
	स्थिर पूर्णांक maxNbAttempts)
अणु
	U16 * स्थिर chainTable = hc4->chainTable;
	U32 * स्थिर HashTable = hc4->hashTable;
	स्थिर BYTE * स्थिर base = hc4->base;
	स्थिर BYTE * स्थिर dictBase = hc4->dictBase;
	स्थिर U32 dictLimit = hc4->dictLimit;
	स्थिर U32 lowLimit = (hc4->lowLimit + 64 * KB > (U32)(ip - base))
		? hc4->lowLimit
		: (U32)(ip - base) - (64 * KB - 1);
	U32 matchIndex;
	पूर्णांक nbAttempts = maxNbAttempts;
	माप_प्रकार ml = 0;

	/* HC4 match finder */
	LZ4HC_Insert(hc4, ip);
	matchIndex = HashTable[LZ4HC_hashPtr(ip)];

	जबतक ((matchIndex >= lowLimit)
		&& (nbAttempts)) अणु
		nbAttempts--;
		अगर (matchIndex >= dictLimit) अणु
			स्थिर BYTE * स्थिर match = base + matchIndex;

			अगर (*(match + ml) == *(ip + ml)
				&& (LZ4_पढ़ो32(match) == LZ4_पढ़ो32(ip))) अणु
				माप_प्रकार स्थिर mlt = LZ4_count(ip + MINMATCH,
					match + MINMATCH, iLimit) + MINMATCH;

				अगर (mlt > ml) अणु
					ml = mlt;
					*matchpos = match;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			स्थिर BYTE * स्थिर match = dictBase + matchIndex;

			अगर (LZ4_पढ़ो32(match) == LZ4_पढ़ो32(ip)) अणु
				माप_प्रकार mlt;
				स्थिर BYTE *vLimit = ip
					+ (dictLimit - matchIndex);

				अगर (vLimit > iLimit)
					vLimit = iLimit;
				mlt = LZ4_count(ip + MINMATCH,
					match + MINMATCH, vLimit) + MINMATCH;
				अगर ((ip + mlt == vLimit)
					&& (vLimit < iLimit))
					mlt += LZ4_count(ip + mlt,
						base + dictLimit,
						iLimit);
				अगर (mlt > ml) अणु
					/* भव matchpos */
					ml = mlt;
					*matchpos = base + matchIndex;
				पूर्ण
			पूर्ण
		पूर्ण
		matchIndex -= DELTANEXTU16(matchIndex);
	पूर्ण

	वापस (पूर्णांक)ml;
पूर्ण

अटल FORCE_INLINE पूर्णांक LZ4HC_InsertAndGetWiderMatch(
	LZ4HC_CCtx_पूर्णांकernal *hc4,
	स्थिर BYTE * स्थिर ip,
	स्थिर BYTE * स्थिर iLowLimit,
	स्थिर BYTE * स्थिर iHighLimit,
	पूर्णांक दीर्घest,
	स्थिर BYTE **matchpos,
	स्थिर BYTE **startpos,
	स्थिर पूर्णांक maxNbAttempts)
अणु
	U16 * स्थिर chainTable = hc4->chainTable;
	U32 * स्थिर HashTable = hc4->hashTable;
	स्थिर BYTE * स्थिर base = hc4->base;
	स्थिर U32 dictLimit = hc4->dictLimit;
	स्थिर BYTE * स्थिर lowPrefixPtr = base + dictLimit;
	स्थिर U32 lowLimit = (hc4->lowLimit + 64 * KB > (U32)(ip - base))
		? hc4->lowLimit
		: (U32)(ip - base) - (64 * KB - 1);
	स्थिर BYTE * स्थिर dictBase = hc4->dictBase;
	U32 matchIndex;
	पूर्णांक nbAttempts = maxNbAttempts;
	पूर्णांक delta = (पूर्णांक)(ip - iLowLimit);

	/* First Match */
	LZ4HC_Insert(hc4, ip);
	matchIndex = HashTable[LZ4HC_hashPtr(ip)];

	जबतक ((matchIndex >= lowLimit)
		&& (nbAttempts)) अणु
		nbAttempts--;
		अगर (matchIndex >= dictLimit) अणु
			स्थिर BYTE *matchPtr = base + matchIndex;

			अगर (*(iLowLimit + दीर्घest)
				== *(matchPtr - delta + दीर्घest)) अणु
				अगर (LZ4_पढ़ो32(matchPtr) == LZ4_पढ़ो32(ip)) अणु
					पूर्णांक mlt = MINMATCH + LZ4_count(
						ip + MINMATCH,
						matchPtr + MINMATCH,
						iHighLimit);
					पूर्णांक back = 0;

					जबतक ((ip + back > iLowLimit)
						&& (matchPtr + back > lowPrefixPtr)
						&& (ip[back - 1] == matchPtr[back - 1]))
						back--;

					mlt -= back;

					अगर (mlt > दीर्घest) अणु
						दीर्घest = (पूर्णांक)mlt;
						*matchpos = matchPtr + back;
						*startpos = ip + back;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			स्थिर BYTE * स्थिर matchPtr = dictBase + matchIndex;

			अगर (LZ4_पढ़ो32(matchPtr) == LZ4_पढ़ो32(ip)) अणु
				माप_प्रकार mlt;
				पूर्णांक back = 0;
				स्थिर BYTE *vLimit = ip + (dictLimit - matchIndex);

				अगर (vLimit > iHighLimit)
					vLimit = iHighLimit;

				mlt = LZ4_count(ip + MINMATCH,
					matchPtr + MINMATCH, vLimit) + MINMATCH;

				अगर ((ip + mlt == vLimit) && (vLimit < iHighLimit))
					mlt += LZ4_count(ip + mlt, base + dictLimit,
						iHighLimit);
				जबतक ((ip + back > iLowLimit)
					&& (matchIndex + back > lowLimit)
					&& (ip[back - 1] == matchPtr[back - 1]))
					back--;

				mlt -= back;

				अगर ((पूर्णांक)mlt > दीर्घest) अणु
					दीर्घest = (पूर्णांक)mlt;
					*matchpos = base + matchIndex + back;
					*startpos = ip + back;
				पूर्ण
			पूर्ण
		पूर्ण

		matchIndex -= DELTANEXTU16(matchIndex);
	पूर्ण

	वापस दीर्घest;
पूर्ण

अटल FORCE_INLINE पूर्णांक LZ4HC_encodeSequence(
	स्थिर BYTE **ip,
	BYTE **op,
	स्थिर BYTE **anchor,
	पूर्णांक matchLength,
	स्थिर BYTE * स्थिर match,
	limitedOutput_directive limitedOutputBuffer,
	BYTE *oend)
अणु
	पूर्णांक length;
	BYTE *token;

	/* Encode Literal length */
	length = (पूर्णांक)(*ip - *anchor);
	token = (*op)++;

	अगर ((limitedOutputBuffer)
		&& ((*op + (length>>8)
			+ length + (2 + 1 + LASTLITERALS)) > oend)) अणु
		/* Check output limit */
		वापस 1;
	पूर्ण
	अगर (length >= (पूर्णांक)RUN_MASK) अणु
		पूर्णांक len;

		*token = (RUN_MASK<<ML_BITS);
		len = length - RUN_MASK;
		क्रम (; len > 254 ; len -= 255)
			*(*op)++ = 255;
		*(*op)++ = (BYTE)len;
	पूर्ण अन्यथा
		*token = (BYTE)(length<<ML_BITS);

	/* Copy Literals */
	LZ4_wildCopy(*op, *anchor, (*op) + length);
	*op += length;

	/* Encode Offset */
	LZ4_ग_लिखोLE16(*op, (U16)(*ip - match));
	*op += 2;

	/* Encode MatchLength */
	length = (पूर्णांक)(matchLength - MINMATCH);

	अगर ((limitedOutputBuffer)
		&& (*op + (length>>8)
			+ (1 + LASTLITERALS) > oend)) अणु
		/* Check output limit */
		वापस 1;
	पूर्ण

	अगर (length >= (पूर्णांक)ML_MASK) अणु
		*token += ML_MASK;
		length -= ML_MASK;

		क्रम (; length > 509 ; length -= 510) अणु
			*(*op)++ = 255;
			*(*op)++ = 255;
		पूर्ण

		अगर (length > 254) अणु
			length -= 255;
			*(*op)++ = 255;
		पूर्ण

		*(*op)++ = (BYTE)length;
	पूर्ण अन्यथा
		*token += (BYTE)(length);

	/* Prepare next loop */
	*ip += matchLength;
	*anchor = *ip;

	वापस 0;
पूर्ण

अटल पूर्णांक LZ4HC_compress_generic(
	LZ4HC_CCtx_पूर्णांकernal *स्थिर ctx,
	स्थिर अक्षर * स्थिर source,
	अक्षर * स्थिर dest,
	पूर्णांक स्थिर inputSize,
	पूर्णांक स्थिर maxOutputSize,
	पूर्णांक compressionLevel,
	limitedOutput_directive limit
	)
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *) source;
	स्थिर BYTE *anchor = ip;
	स्थिर BYTE * स्थिर iend = ip + inputSize;
	स्थिर BYTE * स्थिर mflimit = iend - MFLIMIT;
	स्थिर BYTE * स्थिर matchlimit = (iend - LASTLITERALS);

	BYTE *op = (BYTE *) dest;
	BYTE * स्थिर oend = op + maxOutputSize;

	अचिन्हित पूर्णांक maxNbAttempts;
	पूर्णांक ml, ml2, ml3, ml0;
	स्थिर BYTE *ref = शून्य;
	स्थिर BYTE *start2 = शून्य;
	स्थिर BYTE *ref2 = शून्य;
	स्थिर BYTE *start3 = शून्य;
	स्थिर BYTE *ref3 = शून्य;
	स्थिर BYTE *start0;
	स्थिर BYTE *ref0;

	/* init */
	अगर (compressionLevel > LZ4HC_MAX_CLEVEL)
		compressionLevel = LZ4HC_MAX_CLEVEL;
	अगर (compressionLevel < 1)
		compressionLevel = LZ4HC_DEFAULT_CLEVEL;
	maxNbAttempts = 1 << (compressionLevel - 1);
	ctx->end += inputSize;

	ip++;

	/* Main Loop */
	जबतक (ip < mflimit) अणु
		ml = LZ4HC_InsertAndFindBestMatch(ctx, ip,
			matchlimit, (&ref), maxNbAttempts);
		अगर (!ml) अणु
			ip++;
			जारी;
		पूर्ण

		/* saved, in हाल we would skip too much */
		start0 = ip;
		ref0 = ref;
		ml0 = ml;

_Search2:
		अगर (ip + ml < mflimit)
			ml2 = LZ4HC_InsertAndGetWiderMatch(ctx,
				ip + ml - 2, ip + 0,
				matchlimit, ml, &ref2,
				&start2, maxNbAttempts);
		अन्यथा
			ml2 = ml;

		अगर (ml2 == ml) अणु
			/* No better match */
			अगर (LZ4HC_encodeSequence(&ip, &op,
				&anchor, ml, ref, limit, oend))
				वापस 0;
			जारी;
		पूर्ण

		अगर (start0 < ip) अणु
			अगर (start2 < ip + ml0) अणु
				/* empirical */
				ip = start0;
				ref = ref0;
				ml = ml0;
			पूर्ण
		पूर्ण

		/* Here, start0 == ip */
		अगर ((start2 - ip) < 3) अणु
			/* First Match too small : हटाओd */
			ml = ml2;
			ip = start2;
			ref = ref2;
			जाओ _Search2;
		पूर्ण

_Search3:
		/*
		* Currently we have :
		* ml2 > ml1, and
		* ip1 + 3 <= ip2 (usually < ip1 + ml1)
		*/
		अगर ((start2 - ip) < OPTIMAL_ML) अणु
			पूर्णांक correction;
			पूर्णांक new_ml = ml;

			अगर (new_ml > OPTIMAL_ML)
				new_ml = OPTIMAL_ML;
			अगर (ip + new_ml > start2 + ml2 - MINMATCH)
				new_ml = (पूर्णांक)(start2 - ip) + ml2 - MINMATCH;

			correction = new_ml - (पूर्णांक)(start2 - ip);

			अगर (correction > 0) अणु
				start2 += correction;
				ref2 += correction;
				ml2 -= correction;
			पूर्ण
		पूर्ण
		/*
		 * Now, we have start2 = ip + new_ml,
		 * with new_ml = min(ml, OPTIMAL_ML = 18)
		 */

		अगर (start2 + ml2 < mflimit)
			ml3 = LZ4HC_InsertAndGetWiderMatch(ctx,
				start2 + ml2 - 3, start2,
				matchlimit, ml2, &ref3, &start3,
				maxNbAttempts);
		अन्यथा
			ml3 = ml2;

		अगर (ml3 == ml2) अणु
			/* No better match : 2 sequences to encode */
			/* ip & ref are known; Now क्रम ml */
			अगर (start2 < ip + ml)
				ml = (पूर्णांक)(start2 - ip);
			/* Now, encode 2 sequences */
			अगर (LZ4HC_encodeSequence(&ip, &op, &anchor,
				ml, ref, limit, oend))
				वापस 0;
			ip = start2;
			अगर (LZ4HC_encodeSequence(&ip, &op, &anchor,
				ml2, ref2, limit, oend))
				वापस 0;
			जारी;
		पूर्ण

		अगर (start3 < ip + ml + 3) अणु
			/* Not enough space क्रम match 2 : हटाओ it */
			अगर (start3 >= (ip + ml)) अणु
				/* can ग_लिखो Seq1 immediately
				 * ==> Seq2 is हटाओd,
				 * so Seq3 becomes Seq1
				 */
				अगर (start2 < ip + ml) अणु
					पूर्णांक correction = (पूर्णांक)(ip + ml - start2);

					start2 += correction;
					ref2 += correction;
					ml2 -= correction;
					अगर (ml2 < MINMATCH) अणु
						start2 = start3;
						ref2 = ref3;
						ml2 = ml3;
					पूर्ण
				पूर्ण

				अगर (LZ4HC_encodeSequence(&ip, &op, &anchor,
					ml, ref, limit, oend))
					वापस 0;
				ip = start3;
				ref = ref3;
				ml = ml3;

				start0 = start2;
				ref0 = ref2;
				ml0 = ml2;
				जाओ _Search2;
			पूर्ण

			start2 = start3;
			ref2 = ref3;
			ml2 = ml3;
			जाओ _Search3;
		पूर्ण

		/*
		* OK, now we have 3 ascending matches;
		* let's ग_लिखो at least the first one
		* ip & ref are known; Now क्रम ml
		*/
		अगर (start2 < ip + ml) अणु
			अगर ((start2 - ip) < (पूर्णांक)ML_MASK) अणु
				पूर्णांक correction;

				अगर (ml > OPTIMAL_ML)
					ml = OPTIMAL_ML;
				अगर (ip + ml > start2 + ml2 - MINMATCH)
					ml = (पूर्णांक)(start2 - ip) + ml2 - MINMATCH;
				correction = ml - (पूर्णांक)(start2 - ip);
				अगर (correction > 0) अणु
					start2 += correction;
					ref2 += correction;
					ml2 -= correction;
				पूर्ण
			पूर्ण अन्यथा
				ml = (पूर्णांक)(start2 - ip);
		पूर्ण
		अगर (LZ4HC_encodeSequence(&ip, &op, &anchor, ml,
			ref, limit, oend))
			वापस 0;

		ip = start2;
		ref = ref2;
		ml = ml2;

		start2 = start3;
		ref2 = ref3;
		ml2 = ml3;

		जाओ _Search3;
	पूर्ण

	/* Encode Last Literals */
	अणु
		पूर्णांक lastRun = (पूर्णांक)(iend - anchor);

		अगर ((limit)
			&& (((अक्षर *)op - dest) + lastRun + 1
				+ ((lastRun + 255 - RUN_MASK)/255)
					> (U32)maxOutputSize)) अणु
			/* Check output limit */
			वापस 0;
		पूर्ण
		अगर (lastRun >= (पूर्णांक)RUN_MASK) अणु
			*op++ = (RUN_MASK<<ML_BITS);
			lastRun -= RUN_MASK;
			क्रम (; lastRun > 254 ; lastRun -= 255)
				*op++ = 255;
			*op++ = (BYTE) lastRun;
		पूर्ण अन्यथा
			*op++ = (BYTE)(lastRun<<ML_BITS);
		LZ4_स_नकल(op, anchor, iend - anchor);
		op += iend - anchor;
	पूर्ण

	/* End */
	वापस (पूर्णांक) (((अक्षर *)op) - dest);
पूर्ण

अटल पूर्णांक LZ4_compress_HC_extStateHC(
	व्योम *state,
	स्थिर अक्षर *src,
	अक्षर *dst,
	पूर्णांक srcSize,
	पूर्णांक maxDstSize,
	पूर्णांक compressionLevel)
अणु
	LZ4HC_CCtx_पूर्णांकernal *ctx = &((LZ4_streamHC_t *)state)->पूर्णांकernal_करोnotuse;

	अगर (((माप_प्रकार)(state)&(माप(व्योम *) - 1)) != 0) अणु
		/* Error : state is not aligned
		 * क्रम poपूर्णांकers (32 or 64 bits)
		 */
		वापस 0;
	पूर्ण

	LZ4HC_init(ctx, (स्थिर BYTE *)src);

	अगर (maxDstSize < LZ4_compressBound(srcSize))
		वापस LZ4HC_compress_generic(ctx, src, dst,
			srcSize, maxDstSize, compressionLevel, limitedOutput);
	अन्यथा
		वापस LZ4HC_compress_generic(ctx, src, dst,
			srcSize, maxDstSize, compressionLevel, noLimit);
पूर्ण

पूर्णांक LZ4_compress_HC(स्थिर अक्षर *src, अक्षर *dst, पूर्णांक srcSize,
	पूर्णांक maxDstSize, पूर्णांक compressionLevel, व्योम *wrkmem)
अणु
	वापस LZ4_compress_HC_extStateHC(wrkmem, src, dst,
		srcSize, maxDstSize, compressionLevel);
पूर्ण
EXPORT_SYMBOL(LZ4_compress_HC);

/**************************************
 *	Streaming Functions
 **************************************/
व्योम LZ4_resetStreamHC(LZ4_streamHC_t *LZ4_streamHCPtr, पूर्णांक compressionLevel)
अणु
	LZ4_streamHCPtr->पूर्णांकernal_करोnotuse.base = शून्य;
	LZ4_streamHCPtr->पूर्णांकernal_करोnotuse.compressionLevel = (अचिन्हित पूर्णांक)compressionLevel;
पूर्ण

पूर्णांक LZ4_loadDictHC(LZ4_streamHC_t *LZ4_streamHCPtr,
	स्थिर अक्षर *dictionary,
	पूर्णांक dictSize)
अणु
	LZ4HC_CCtx_पूर्णांकernal *ctxPtr = &LZ4_streamHCPtr->पूर्णांकernal_करोnotuse;

	अगर (dictSize > 64 * KB) अणु
		dictionary += dictSize - 64 * KB;
		dictSize = 64 * KB;
	पूर्ण
	LZ4HC_init(ctxPtr, (स्थिर BYTE *)dictionary);
	अगर (dictSize >= 4)
		LZ4HC_Insert(ctxPtr, (स्थिर BYTE *)dictionary + (dictSize - 3));
	ctxPtr->end = (स्थिर BYTE *)dictionary + dictSize;
	वापस dictSize;
पूर्ण
EXPORT_SYMBOL(LZ4_loadDictHC);

/* compression */

अटल व्योम LZ4HC_setExternalDict(
	LZ4HC_CCtx_पूर्णांकernal *ctxPtr,
	स्थिर BYTE *newBlock)
अणु
	अगर (ctxPtr->end >= ctxPtr->base + 4) अणु
		/* Referencing reमुख्यing dictionary content */
		LZ4HC_Insert(ctxPtr, ctxPtr->end - 3);
	पूर्ण

	/*
	 * Only one memory segment क्रम extDict,
	 * so any previous extDict is lost at this stage
	 */
	ctxPtr->lowLimit	= ctxPtr->dictLimit;
	ctxPtr->dictLimit = (U32)(ctxPtr->end - ctxPtr->base);
	ctxPtr->dictBase	= ctxPtr->base;
	ctxPtr->base = newBlock - ctxPtr->dictLimit;
	ctxPtr->end	= newBlock;
	/* match referencing will resume from there */
	ctxPtr->nextToUpdate = ctxPtr->dictLimit;
पूर्ण

अटल पूर्णांक LZ4_compressHC_जारी_generic(
	LZ4_streamHC_t *LZ4_streamHCPtr,
	स्थिर अक्षर *source,
	अक्षर *dest,
	पूर्णांक inputSize,
	पूर्णांक maxOutputSize,
	limitedOutput_directive limit)
अणु
	LZ4HC_CCtx_पूर्णांकernal *ctxPtr = &LZ4_streamHCPtr->पूर्णांकernal_करोnotuse;

	/* स्वतः - init अगर क्रमgotten */
	अगर (ctxPtr->base == शून्य)
		LZ4HC_init(ctxPtr, (स्थिर BYTE *) source);

	/* Check overflow */
	अगर ((माप_प्रकार)(ctxPtr->end - ctxPtr->base) > 2 * GB) अणु
		माप_प्रकार dictSize = (माप_प्रकार)(ctxPtr->end - ctxPtr->base)
			- ctxPtr->dictLimit;
		अगर (dictSize > 64 * KB)
			dictSize = 64 * KB;
		LZ4_loadDictHC(LZ4_streamHCPtr,
			(स्थिर अक्षर *)(ctxPtr->end) - dictSize, (पूर्णांक)dictSize);
	पूर्ण

	/* Check अगर blocks follow each other */
	अगर ((स्थिर BYTE *)source != ctxPtr->end)
		LZ4HC_setExternalDict(ctxPtr, (स्थिर BYTE *)source);

	/* Check overlapping input/dictionary space */
	अणु
		स्थिर BYTE *sourceEnd = (स्थिर BYTE *) source + inputSize;
		स्थिर BYTE * स्थिर dictBegin = ctxPtr->dictBase + ctxPtr->lowLimit;
		स्थिर BYTE * स्थिर dictEnd = ctxPtr->dictBase + ctxPtr->dictLimit;

		अगर ((sourceEnd > dictBegin)
			&& ((स्थिर BYTE *)source < dictEnd)) अणु
			अगर (sourceEnd > dictEnd)
				sourceEnd = dictEnd;
			ctxPtr->lowLimit = (U32)(sourceEnd - ctxPtr->dictBase);

			अगर (ctxPtr->dictLimit - ctxPtr->lowLimit < 4)
				ctxPtr->lowLimit = ctxPtr->dictLimit;
		पूर्ण
	पूर्ण

	वापस LZ4HC_compress_generic(ctxPtr, source, dest,
		inputSize, maxOutputSize, ctxPtr->compressionLevel, limit);
पूर्ण

पूर्णांक LZ4_compress_HC_जारी(
	LZ4_streamHC_t *LZ4_streamHCPtr,
	स्थिर अक्षर *source,
	अक्षर *dest,
	पूर्णांक inputSize,
	पूर्णांक maxOutputSize)
अणु
	अगर (maxOutputSize < LZ4_compressBound(inputSize))
		वापस LZ4_compressHC_जारी_generic(LZ4_streamHCPtr,
			source, dest, inputSize, maxOutputSize, limitedOutput);
	अन्यथा
		वापस LZ4_compressHC_जारी_generic(LZ4_streamHCPtr,
			source, dest, inputSize, maxOutputSize, noLimit);
पूर्ण
EXPORT_SYMBOL(LZ4_compress_HC_जारी);

/* dictionary saving */

पूर्णांक LZ4_saveDictHC(
	LZ4_streamHC_t *LZ4_streamHCPtr,
	अक्षर *safeBuffer,
	पूर्णांक dictSize)
अणु
	LZ4HC_CCtx_पूर्णांकernal *स्थिर streamPtr = &LZ4_streamHCPtr->पूर्णांकernal_करोnotuse;
	पूर्णांक स्थिर prefixSize = (पूर्णांक)(streamPtr->end
		- (streamPtr->base + streamPtr->dictLimit));

	अगर (dictSize > 64 * KB)
		dictSize = 64 * KB;
	अगर (dictSize < 4)
		dictSize = 0;
	अगर (dictSize > prefixSize)
		dictSize = prefixSize;

	स_हटाओ(safeBuffer, streamPtr->end - dictSize, dictSize);

	अणु
		U32 स्थिर endIndex = (U32)(streamPtr->end - streamPtr->base);

		streamPtr->end = (स्थिर BYTE *)safeBuffer + dictSize;
		streamPtr->base = streamPtr->end - endIndex;
		streamPtr->dictLimit = endIndex - dictSize;
		streamPtr->lowLimit = endIndex - dictSize;

		अगर (streamPtr->nextToUpdate < streamPtr->dictLimit)
			streamPtr->nextToUpdate = streamPtr->dictLimit;
	पूर्ण
	वापस dictSize;
पूर्ण
EXPORT_SYMBOL(LZ4_saveDictHC);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("LZ4 HC compressor");
