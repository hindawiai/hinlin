<शैली गुरु>
/*
 * LZ4 - Fast LZ compression algorithm
 * Copyright (C) 2011 - 2016, Yann Collet.
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
#समावेश <यंत्र/unaligned.h>

अटल स्थिर पूर्णांक LZ4_minLength = (MFLIMIT + 1);
अटल स्थिर पूर्णांक LZ4_64Klimit = ((64 * KB) + (MFLIMIT - 1));

/*-******************************
 *	Compression functions
 ********************************/
अटल FORCE_INLINE U32 LZ4_hash4(
	U32 sequence,
	tableType_t स्थिर tableType)
अणु
	अगर (tableType == byU16)
		वापस ((sequence * 2654435761U)
			>> ((MINMATCH * 8) - (LZ4_HASHLOG + 1)));
	अन्यथा
		वापस ((sequence * 2654435761U)
			>> ((MINMATCH * 8) - LZ4_HASHLOG));
पूर्ण

अटल FORCE_INLINE U32 LZ4_hash5(
	U64 sequence,
	tableType_t स्थिर tableType)
अणु
	स्थिर U32 hashLog = (tableType == byU16)
		? LZ4_HASHLOG + 1
		: LZ4_HASHLOG;

#अगर LZ4_LITTLE_ENDIAN
	अटल स्थिर U64 prime5bytes = 889523592379ULL;

	वापस (U32)(((sequence << 24) * prime5bytes) >> (64 - hashLog));
#अन्यथा
	अटल स्थिर U64 prime8bytes = 11400714785074694791ULL;

	वापस (U32)(((sequence >> 24) * prime8bytes) >> (64 - hashLog));
#पूर्ण_अगर
पूर्ण

अटल FORCE_INLINE U32 LZ4_hashPosition(
	स्थिर व्योम *p,
	tableType_t स्थिर tableType)
अणु
#अगर LZ4_ARCH64
	अगर (tableType == byU32)
		वापस LZ4_hash5(LZ4_पढ़ो_ARCH(p), tableType);
#पूर्ण_अगर

	वापस LZ4_hash4(LZ4_पढ़ो32(p), tableType);
पूर्ण

अटल व्योम LZ4_putPositionOnHash(
	स्थिर BYTE *p,
	U32 h,
	व्योम *tableBase,
	tableType_t स्थिर tableType,
	स्थिर BYTE *srcBase)
अणु
	चयन (tableType) अणु
	हाल byPtr:
	अणु
		स्थिर BYTE **hashTable = (स्थिर BYTE **)tableBase;

		hashTable[h] = p;
		वापस;
	पूर्ण
	हाल byU32:
	अणु
		U32 *hashTable = (U32 *) tableBase;

		hashTable[h] = (U32)(p - srcBase);
		वापस;
	पूर्ण
	हाल byU16:
	अणु
		U16 *hashTable = (U16 *) tableBase;

		hashTable[h] = (U16)(p - srcBase);
		वापस;
	पूर्ण
	पूर्ण
पूर्ण

अटल FORCE_INLINE व्योम LZ4_putPosition(
	स्थिर BYTE *p,
	व्योम *tableBase,
	tableType_t tableType,
	स्थिर BYTE *srcBase)
अणु
	U32 स्थिर h = LZ4_hashPosition(p, tableType);

	LZ4_putPositionOnHash(p, h, tableBase, tableType, srcBase);
पूर्ण

अटल स्थिर BYTE *LZ4_getPositionOnHash(
	U32 h,
	व्योम *tableBase,
	tableType_t tableType,
	स्थिर BYTE *srcBase)
अणु
	अगर (tableType == byPtr) अणु
		स्थिर BYTE **hashTable = (स्थिर BYTE **) tableBase;

		वापस hashTable[h];
	पूर्ण

	अगर (tableType == byU32) अणु
		स्थिर U32 * स्थिर hashTable = (U32 *) tableBase;

		वापस hashTable[h] + srcBase;
	पूर्ण

	अणु
		/* शेष, to ensure a वापस */
		स्थिर U16 * स्थिर hashTable = (U16 *) tableBase;

		वापस hashTable[h] + srcBase;
	पूर्ण
पूर्ण

अटल FORCE_INLINE स्थिर BYTE *LZ4_getPosition(
	स्थिर BYTE *p,
	व्योम *tableBase,
	tableType_t tableType,
	स्थिर BYTE *srcBase)
अणु
	U32 स्थिर h = LZ4_hashPosition(p, tableType);

	वापस LZ4_getPositionOnHash(h, tableBase, tableType, srcBase);
पूर्ण


/*
 * LZ4_compress_generic() :
 * अंतरभूतd, to ensure branches are decided at compilation समय
 */
अटल FORCE_INLINE पूर्णांक LZ4_compress_generic(
	LZ4_stream_t_पूर्णांकernal * स्थिर dictPtr,
	स्थिर अक्षर * स्थिर source,
	अक्षर * स्थिर dest,
	स्थिर पूर्णांक inputSize,
	स्थिर पूर्णांक maxOutputSize,
	स्थिर limitedOutput_directive outputLimited,
	स्थिर tableType_t tableType,
	स्थिर dict_directive dict,
	स्थिर dictIssue_directive dictIssue,
	स्थिर U32 acceleration)
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *) source;
	स्थिर BYTE *base;
	स्थिर BYTE *lowLimit;
	स्थिर BYTE * स्थिर lowRefLimit = ip - dictPtr->dictSize;
	स्थिर BYTE * स्थिर dictionary = dictPtr->dictionary;
	स्थिर BYTE * स्थिर dictEnd = dictionary + dictPtr->dictSize;
	स्थिर माप_प्रकार dictDelta = dictEnd - (स्थिर BYTE *)source;
	स्थिर BYTE *anchor = (स्थिर BYTE *) source;
	स्थिर BYTE * स्थिर iend = ip + inputSize;
	स्थिर BYTE * स्थिर mflimit = iend - MFLIMIT;
	स्थिर BYTE * स्थिर matchlimit = iend - LASTLITERALS;

	BYTE *op = (BYTE *) dest;
	BYTE * स्थिर olimit = op + maxOutputSize;

	U32 क्रमwardH;
	माप_प्रकार refDelta = 0;

	/* Init conditions */
	अगर ((U32)inputSize > (U32)LZ4_MAX_INPUT_SIZE) अणु
		/* Unsupported inputSize, too large (or negative) */
		वापस 0;
	पूर्ण

	चयन (dict) अणु
	हाल noDict:
	शेष:
		base = (स्थिर BYTE *)source;
		lowLimit = (स्थिर BYTE *)source;
		अवरोध;
	हाल withPrefix64k:
		base = (स्थिर BYTE *)source - dictPtr->currentOffset;
		lowLimit = (स्थिर BYTE *)source - dictPtr->dictSize;
		अवरोध;
	हाल usingExtDict:
		base = (स्थिर BYTE *)source - dictPtr->currentOffset;
		lowLimit = (स्थिर BYTE *)source;
		अवरोध;
	पूर्ण

	अगर ((tableType == byU16)
		&& (inputSize >= LZ4_64Klimit)) अणु
		/* Size too large (not within 64K limit) */
		वापस 0;
	पूर्ण

	अगर (inputSize < LZ4_minLength) अणु
		/* Input too small, no compression (all literals) */
		जाओ _last_literals;
	पूर्ण

	/* First Byte */
	LZ4_putPosition(ip, dictPtr->hashTable, tableType, base);
	ip++;
	क्रमwardH = LZ4_hashPosition(ip, tableType);

	/* Main Loop */
	क्रम ( ; ; ) अणु
		स्थिर BYTE *match;
		BYTE *token;

		/* Find a match */
		अणु
			स्थिर BYTE *क्रमwardIp = ip;
			अचिन्हित पूर्णांक step = 1;
			अचिन्हित पूर्णांक searchMatchNb = acceleration << LZ4_SKIPTRIGGER;

			करो अणु
				U32 स्थिर h = क्रमwardH;

				ip = क्रमwardIp;
				क्रमwardIp += step;
				step = (searchMatchNb++ >> LZ4_SKIPTRIGGER);

				अगर (unlikely(क्रमwardIp > mflimit))
					जाओ _last_literals;

				match = LZ4_getPositionOnHash(h,
					dictPtr->hashTable,
					tableType, base);

				अगर (dict == usingExtDict) अणु
					अगर (match < (स्थिर BYTE *)source) अणु
						refDelta = dictDelta;
						lowLimit = dictionary;
					पूर्ण अन्यथा अणु
						refDelta = 0;
						lowLimit = (स्थिर BYTE *)source;
				पूर्ण	 पूर्ण

				क्रमwardH = LZ4_hashPosition(क्रमwardIp,
					tableType);

				LZ4_putPositionOnHash(ip, h, dictPtr->hashTable,
					tableType, base);
			पूर्ण जबतक (((dictIssue == dictSmall)
					? (match < lowRefLimit)
					: 0)
				|| ((tableType == byU16)
					? 0
					: (match + MAX_DISTANCE < ip))
				|| (LZ4_पढ़ो32(match + refDelta)
					!= LZ4_पढ़ो32(ip)));
		पूर्ण

		/* Catch up */
		जबतक (((ip > anchor) & (match + refDelta > lowLimit))
				&& (unlikely(ip[-1] == match[refDelta - 1]))) अणु
			ip--;
			match--;
		पूर्ण

		/* Encode Literals */
		अणु
			अचिन्हित स्थिर पूर्णांक litLength = (अचिन्हित पूर्णांक)(ip - anchor);

			token = op++;

			अगर ((outputLimited) &&
				/* Check output buffer overflow */
				(unlikely(op + litLength +
					(2 + 1 + LASTLITERALS) +
					(litLength / 255) > olimit)))
				वापस 0;

			अगर (litLength >= RUN_MASK) अणु
				पूर्णांक len = (पूर्णांक)litLength - RUN_MASK;

				*token = (RUN_MASK << ML_BITS);

				क्रम (; len >= 255; len -= 255)
					*op++ = 255;
				*op++ = (BYTE)len;
			पूर्ण अन्यथा
				*token = (BYTE)(litLength << ML_BITS);

			/* Copy Literals */
			LZ4_wildCopy(op, anchor, op + litLength);
			op += litLength;
		पूर्ण

_next_match:
		/* Encode Offset */
		LZ4_ग_लिखोLE16(op, (U16)(ip - match));
		op += 2;

		/* Encode MatchLength */
		अणु
			अचिन्हित पूर्णांक matchCode;

			अगर ((dict == usingExtDict)
				&& (lowLimit == dictionary)) अणु
				स्थिर BYTE *limit;

				match += refDelta;
				limit = ip + (dictEnd - match);

				अगर (limit > matchlimit)
					limit = matchlimit;

				matchCode = LZ4_count(ip + MINMATCH,
					match + MINMATCH, limit);

				ip += MINMATCH + matchCode;

				अगर (ip == limit) अणु
					अचिन्हित स्थिर पूर्णांक more = LZ4_count(ip,
						(स्थिर BYTE *)source,
						matchlimit);

					matchCode += more;
					ip += more;
				पूर्ण
			पूर्ण अन्यथा अणु
				matchCode = LZ4_count(ip + MINMATCH,
					match + MINMATCH, matchlimit);
				ip += MINMATCH + matchCode;
			पूर्ण

			अगर (outputLimited &&
				/* Check output buffer overflow */
				(unlikely(op +
					(1 + LASTLITERALS) +
					(matchCode >> 8) > olimit)))
				वापस 0;

			अगर (matchCode >= ML_MASK) अणु
				*token += ML_MASK;
				matchCode -= ML_MASK;
				LZ4_ग_लिखो32(op, 0xFFFFFFFF);

				जबतक (matchCode >= 4 * 255) अणु
					op += 4;
					LZ4_ग_लिखो32(op, 0xFFFFFFFF);
					matchCode -= 4 * 255;
				पूर्ण

				op += matchCode / 255;
				*op++ = (BYTE)(matchCode % 255);
			पूर्ण अन्यथा
				*token += (BYTE)(matchCode);
		पूर्ण

		anchor = ip;

		/* Test end of chunk */
		अगर (ip > mflimit)
			अवरोध;

		/* Fill table */
		LZ4_putPosition(ip - 2, dictPtr->hashTable, tableType, base);

		/* Test next position */
		match = LZ4_getPosition(ip, dictPtr->hashTable,
			tableType, base);

		अगर (dict == usingExtDict) अणु
			अगर (match < (स्थिर BYTE *)source) अणु
				refDelta = dictDelta;
				lowLimit = dictionary;
			पूर्ण अन्यथा अणु
				refDelta = 0;
				lowLimit = (स्थिर BYTE *)source;
			पूर्ण
		पूर्ण

		LZ4_putPosition(ip, dictPtr->hashTable, tableType, base);

		अगर (((dictIssue == dictSmall) ? (match >= lowRefLimit) : 1)
			&& (match + MAX_DISTANCE >= ip)
			&& (LZ4_पढ़ो32(match + refDelta) == LZ4_पढ़ो32(ip))) अणु
			token = op++;
			*token = 0;
			जाओ _next_match;
		पूर्ण

		/* Prepare next loop */
		क्रमwardH = LZ4_hashPosition(++ip, tableType);
	पूर्ण

_last_literals:
	/* Encode Last Literals */
	अणु
		माप_प्रकार स्थिर lastRun = (माप_प्रकार)(iend - anchor);

		अगर ((outputLimited) &&
			/* Check output buffer overflow */
			((op - (BYTE *)dest) + lastRun + 1 +
			((lastRun + 255 - RUN_MASK) / 255) > (U32)maxOutputSize))
			वापस 0;

		अगर (lastRun >= RUN_MASK) अणु
			माप_प्रकार accumulator = lastRun - RUN_MASK;
			*op++ = RUN_MASK << ML_BITS;
			क्रम (; accumulator >= 255; accumulator -= 255)
				*op++ = 255;
			*op++ = (BYTE) accumulator;
		पूर्ण अन्यथा अणु
			*op++ = (BYTE)(lastRun << ML_BITS);
		पूर्ण

		LZ4_स_नकल(op, anchor, lastRun);

		op += lastRun;
	पूर्ण

	/* End */
	वापस (पूर्णांक) (((अक्षर *)op) - dest);
पूर्ण

अटल पूर्णांक LZ4_compress_fast_extState(
	व्योम *state,
	स्थिर अक्षर *source,
	अक्षर *dest,
	पूर्णांक inputSize,
	पूर्णांक maxOutputSize,
	पूर्णांक acceleration)
अणु
	LZ4_stream_t_पूर्णांकernal *ctx = &((LZ4_stream_t *)state)->पूर्णांकernal_करोnotuse;
#अगर LZ4_ARCH64
	स्थिर tableType_t tableType = byU32;
#अन्यथा
	स्थिर tableType_t tableType = byPtr;
#पूर्ण_अगर

	LZ4_resetStream((LZ4_stream_t *)state);

	अगर (acceleration < 1)
		acceleration = LZ4_ACCELERATION_DEFAULT;

	अगर (maxOutputSize >= LZ4_COMPRESSBOUND(inputSize)) अणु
		अगर (inputSize < LZ4_64Klimit)
			वापस LZ4_compress_generic(ctx, source,
				dest, inputSize, 0,
				noLimit, byU16, noDict,
				noDictIssue, acceleration);
		अन्यथा
			वापस LZ4_compress_generic(ctx, source,
				dest, inputSize, 0,
				noLimit, tableType, noDict,
				noDictIssue, acceleration);
	पूर्ण अन्यथा अणु
		अगर (inputSize < LZ4_64Klimit)
			वापस LZ4_compress_generic(ctx, source,
				dest, inputSize,
				maxOutputSize, limitedOutput, byU16, noDict,
				noDictIssue, acceleration);
		अन्यथा
			वापस LZ4_compress_generic(ctx, source,
				dest, inputSize,
				maxOutputSize, limitedOutput, tableType, noDict,
				noDictIssue, acceleration);
	पूर्ण
पूर्ण

पूर्णांक LZ4_compress_fast(स्थिर अक्षर *source, अक्षर *dest, पूर्णांक inputSize,
	पूर्णांक maxOutputSize, पूर्णांक acceleration, व्योम *wrkmem)
अणु
	वापस LZ4_compress_fast_extState(wrkmem, source, dest, inputSize,
		maxOutputSize, acceleration);
पूर्ण
EXPORT_SYMBOL(LZ4_compress_fast);

पूर्णांक LZ4_compress_शेष(स्थिर अक्षर *source, अक्षर *dest, पूर्णांक inputSize,
	पूर्णांक maxOutputSize, व्योम *wrkmem)
अणु
	वापस LZ4_compress_fast(source, dest, inputSize,
		maxOutputSize, LZ4_ACCELERATION_DEFAULT, wrkmem);
पूर्ण
EXPORT_SYMBOL(LZ4_compress_शेष);

/*-******************************
 *	*_destSize() variant
 ********************************/
अटल पूर्णांक LZ4_compress_destSize_generic(
	LZ4_stream_t_पूर्णांकernal * स्थिर ctx,
	स्थिर अक्षर * स्थिर src,
	अक्षर * स्थिर dst,
	पूर्णांक * स्थिर srcSizePtr,
	स्थिर पूर्णांक targetDstSize,
	स्थिर tableType_t tableType)
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *) src;
	स्थिर BYTE *base = (स्थिर BYTE *) src;
	स्थिर BYTE *lowLimit = (स्थिर BYTE *) src;
	स्थिर BYTE *anchor = ip;
	स्थिर BYTE * स्थिर iend = ip + *srcSizePtr;
	स्थिर BYTE * स्थिर mflimit = iend - MFLIMIT;
	स्थिर BYTE * स्थिर matchlimit = iend - LASTLITERALS;

	BYTE *op = (BYTE *) dst;
	BYTE * स्थिर oend = op + targetDstSize;
	BYTE * स्थिर oMaxLit = op + targetDstSize - 2 /* offset */
		- 8 /* because 8 + MINMATCH == MFLIMIT */ - 1 /* token */;
	BYTE * स्थिर oMaxMatch = op + targetDstSize
		- (LASTLITERALS + 1 /* token */);
	BYTE * स्थिर oMaxSeq = oMaxLit - 1 /* token */;

	U32 क्रमwardH;

	/* Init conditions */
	/* Impossible to store anything */
	अगर (targetDstSize < 1)
		वापस 0;
	/* Unsupported input size, too large (or negative) */
	अगर ((U32)*srcSizePtr > (U32)LZ4_MAX_INPUT_SIZE)
		वापस 0;
	/* Size too large (not within 64K limit) */
	अगर ((tableType == byU16) && (*srcSizePtr >= LZ4_64Klimit))
		वापस 0;
	/* Input too small, no compression (all literals) */
	अगर (*srcSizePtr < LZ4_minLength)
		जाओ _last_literals;

	/* First Byte */
	*srcSizePtr = 0;
	LZ4_putPosition(ip, ctx->hashTable, tableType, base);
	ip++; क्रमwardH = LZ4_hashPosition(ip, tableType);

	/* Main Loop */
	क्रम ( ; ; ) अणु
		स्थिर BYTE *match;
		BYTE *token;

		/* Find a match */
		अणु
			स्थिर BYTE *क्रमwardIp = ip;
			अचिन्हित पूर्णांक step = 1;
			अचिन्हित पूर्णांक searchMatchNb = 1 << LZ4_SKIPTRIGGER;

			करो अणु
				U32 h = क्रमwardH;

				ip = क्रमwardIp;
				क्रमwardIp += step;
				step = (searchMatchNb++ >> LZ4_SKIPTRIGGER);

				अगर (unlikely(क्रमwardIp > mflimit))
					जाओ _last_literals;

				match = LZ4_getPositionOnHash(h, ctx->hashTable,
					tableType, base);
				क्रमwardH = LZ4_hashPosition(क्रमwardIp,
					tableType);
				LZ4_putPositionOnHash(ip, h,
					ctx->hashTable, tableType,
					base);

			पूर्ण जबतक (((tableType == byU16)
				? 0
				: (match + MAX_DISTANCE < ip))
				|| (LZ4_पढ़ो32(match) != LZ4_पढ़ो32(ip)));
		पूर्ण

		/* Catch up */
		जबतक ((ip > anchor)
			&& (match > lowLimit)
			&& (unlikely(ip[-1] == match[-1]))) अणु
			ip--;
			match--;
		पूर्ण

		/* Encode Literal length */
		अणु
			अचिन्हित पूर्णांक litLength = (अचिन्हित पूर्णांक)(ip - anchor);

			token = op++;
			अगर (op + ((litLength + 240) / 255)
				+ litLength > oMaxLit) अणु
				/* Not enough space क्रम a last match */
				op--;
				जाओ _last_literals;
			पूर्ण
			अगर (litLength >= RUN_MASK) अणु
				अचिन्हित पूर्णांक len = litLength - RUN_MASK;
				*token = (RUN_MASK<<ML_BITS);
				क्रम (; len >= 255; len -= 255)
					*op++ = 255;
				*op++ = (BYTE)len;
			पूर्ण अन्यथा
				*token = (BYTE)(litLength << ML_BITS);

			/* Copy Literals */
			LZ4_wildCopy(op, anchor, op + litLength);
			op += litLength;
		पूर्ण

_next_match:
		/* Encode Offset */
		LZ4_ग_लिखोLE16(op, (U16)(ip - match)); op += 2;

		/* Encode MatchLength */
		अणु
			माप_प्रकार matchLength = LZ4_count(ip + MINMATCH,
			match + MINMATCH, matchlimit);

			अगर (op + ((matchLength + 240)/255) > oMaxMatch) अणु
				/* Match description too दीर्घ : reduce it */
				matchLength = (15 - 1) + (oMaxMatch - op) * 255;
			पूर्ण
			ip += MINMATCH + matchLength;

			अगर (matchLength >= ML_MASK) अणु
				*token += ML_MASK;
				matchLength -= ML_MASK;
				जबतक (matchLength >= 255) अणु
					matchLength -= 255;
					*op++ = 255;
				पूर्ण
				*op++ = (BYTE)matchLength;
			पूर्ण अन्यथा
				*token += (BYTE)(matchLength);
		पूर्ण

		anchor = ip;

		/* Test end of block */
		अगर (ip > mflimit)
			अवरोध;
		अगर (op > oMaxSeq)
			अवरोध;

		/* Fill table */
		LZ4_putPosition(ip - 2, ctx->hashTable, tableType, base);

		/* Test next position */
		match = LZ4_getPosition(ip, ctx->hashTable, tableType, base);
		LZ4_putPosition(ip, ctx->hashTable, tableType, base);

		अगर ((match + MAX_DISTANCE >= ip)
			&& (LZ4_पढ़ो32(match) == LZ4_पढ़ो32(ip))) अणु
			token = op++; *token = 0;
			जाओ _next_match;
		पूर्ण

		/* Prepare next loop */
		क्रमwardH = LZ4_hashPosition(++ip, tableType);
	पूर्ण

_last_literals:
	/* Encode Last Literals */
	अणु
		माप_प्रकार lastRunSize = (माप_प्रकार)(iend - anchor);

		अगर (op + 1 /* token */
			+ ((lastRunSize + 240) / 255) /* litLength */
			+ lastRunSize /* literals */ > oend) अणु
			/* adapt lastRunSize to fill 'dst' */
			lastRunSize	= (oend - op) - 1;
			lastRunSize -= (lastRunSize + 240) / 255;
		पूर्ण
		ip = anchor + lastRunSize;

		अगर (lastRunSize >= RUN_MASK) अणु
			माप_प्रकार accumulator = lastRunSize - RUN_MASK;

			*op++ = RUN_MASK << ML_BITS;
			क्रम (; accumulator >= 255; accumulator -= 255)
				*op++ = 255;
			*op++ = (BYTE) accumulator;
		पूर्ण अन्यथा अणु
			*op++ = (BYTE)(lastRunSize<<ML_BITS);
		पूर्ण
		LZ4_स_नकल(op, anchor, lastRunSize);
		op += lastRunSize;
	पूर्ण

	/* End */
	*srcSizePtr = (पूर्णांक) (((स्थिर अक्षर *)ip) - src);
	वापस (पूर्णांक) (((अक्षर *)op) - dst);
पूर्ण

अटल पूर्णांक LZ4_compress_destSize_extState(
	LZ4_stream_t *state,
	स्थिर अक्षर *src,
	अक्षर *dst,
	पूर्णांक *srcSizePtr,
	पूर्णांक targetDstSize)
अणु
#अगर LZ4_ARCH64
	स्थिर tableType_t tableType = byU32;
#अन्यथा
	स्थिर tableType_t tableType = byPtr;
#पूर्ण_अगर

	LZ4_resetStream(state);

	अगर (targetDstSize >= LZ4_COMPRESSBOUND(*srcSizePtr)) अणु
		/* compression success is guaranteed */
		वापस LZ4_compress_fast_extState(
			state, src, dst, *srcSizePtr,
			targetDstSize, 1);
	पूर्ण अन्यथा अणु
		अगर (*srcSizePtr < LZ4_64Klimit)
			वापस LZ4_compress_destSize_generic(
				&state->पूर्णांकernal_करोnotuse,
				src, dst, srcSizePtr,
				targetDstSize, byU16);
		अन्यथा
			वापस LZ4_compress_destSize_generic(
				&state->पूर्णांकernal_करोnotuse,
				src, dst, srcSizePtr,
				targetDstSize, tableType);
	पूर्ण
पूर्ण


पूर्णांक LZ4_compress_destSize(
	स्थिर अक्षर *src,
	अक्षर *dst,
	पूर्णांक *srcSizePtr,
	पूर्णांक targetDstSize,
	व्योम *wrkmem)
अणु
	वापस LZ4_compress_destSize_extState(wrkmem, src, dst, srcSizePtr,
		targetDstSize);
पूर्ण
EXPORT_SYMBOL(LZ4_compress_destSize);

/*-******************************
 *	Streaming functions
 ********************************/
व्योम LZ4_resetStream(LZ4_stream_t *LZ4_stream)
अणु
	स_रखो(LZ4_stream, 0, माप(LZ4_stream_t));
पूर्ण

पूर्णांक LZ4_loadDict(LZ4_stream_t *LZ4_dict,
	स्थिर अक्षर *dictionary, पूर्णांक dictSize)
अणु
	LZ4_stream_t_पूर्णांकernal *dict = &LZ4_dict->पूर्णांकernal_करोnotuse;
	स्थिर BYTE *p = (स्थिर BYTE *)dictionary;
	स्थिर BYTE * स्थिर dictEnd = p + dictSize;
	स्थिर BYTE *base;

	अगर ((dict->initCheck)
		|| (dict->currentOffset > 1 * GB)) अणु
		/* Uninitialized काष्ठाure, or reuse overflow */
		LZ4_resetStream(LZ4_dict);
	पूर्ण

	अगर (dictSize < (पूर्णांक)HASH_UNIT) अणु
		dict->dictionary = शून्य;
		dict->dictSize = 0;
		वापस 0;
	पूर्ण

	अगर ((dictEnd - p) > 64 * KB)
		p = dictEnd - 64 * KB;
	dict->currentOffset += 64 * KB;
	base = p - dict->currentOffset;
	dict->dictionary = p;
	dict->dictSize = (U32)(dictEnd - p);
	dict->currentOffset += dict->dictSize;

	जबतक (p <= dictEnd - HASH_UNIT) अणु
		LZ4_putPosition(p, dict->hashTable, byU32, base);
		p += 3;
	पूर्ण

	वापस dict->dictSize;
पूर्ण
EXPORT_SYMBOL(LZ4_loadDict);

अटल व्योम LZ4_renormDictT(LZ4_stream_t_पूर्णांकernal *LZ4_dict,
	स्थिर BYTE *src)
अणु
	अगर ((LZ4_dict->currentOffset > 0x80000000) ||
		((uptrval)LZ4_dict->currentOffset > (uptrval)src)) अणु
		/* address space overflow */
		/* rescale hash table */
		U32 स्थिर delta = LZ4_dict->currentOffset - 64 * KB;
		स्थिर BYTE *dictEnd = LZ4_dict->dictionary + LZ4_dict->dictSize;
		पूर्णांक i;

		क्रम (i = 0; i < LZ4_HASH_SIZE_U32; i++) अणु
			अगर (LZ4_dict->hashTable[i] < delta)
				LZ4_dict->hashTable[i] = 0;
			अन्यथा
				LZ4_dict->hashTable[i] -= delta;
		पूर्ण
		LZ4_dict->currentOffset = 64 * KB;
		अगर (LZ4_dict->dictSize > 64 * KB)
			LZ4_dict->dictSize = 64 * KB;
		LZ4_dict->dictionary = dictEnd - LZ4_dict->dictSize;
	पूर्ण
पूर्ण

पूर्णांक LZ4_saveDict(LZ4_stream_t *LZ4_dict, अक्षर *safeBuffer, पूर्णांक dictSize)
अणु
	LZ4_stream_t_पूर्णांकernal * स्थिर dict = &LZ4_dict->पूर्णांकernal_करोnotuse;
	स्थिर BYTE * स्थिर previousDictEnd = dict->dictionary + dict->dictSize;

	अगर ((U32)dictSize > 64 * KB) अणु
		/* useless to define a dictionary > 64 * KB */
		dictSize = 64 * KB;
	पूर्ण
	अगर ((U32)dictSize > dict->dictSize)
		dictSize = dict->dictSize;

	स_हटाओ(safeBuffer, previousDictEnd - dictSize, dictSize);

	dict->dictionary = (स्थिर BYTE *)safeBuffer;
	dict->dictSize = (U32)dictSize;

	वापस dictSize;
पूर्ण
EXPORT_SYMBOL(LZ4_saveDict);

पूर्णांक LZ4_compress_fast_जारी(LZ4_stream_t *LZ4_stream, स्थिर अक्षर *source,
	अक्षर *dest, पूर्णांक inputSize, पूर्णांक maxOutputSize, पूर्णांक acceleration)
अणु
	LZ4_stream_t_पूर्णांकernal *streamPtr = &LZ4_stream->पूर्णांकernal_करोnotuse;
	स्थिर BYTE * स्थिर dictEnd = streamPtr->dictionary
		+ streamPtr->dictSize;

	स्थिर BYTE *smallest = (स्थिर BYTE *) source;

	अगर (streamPtr->initCheck) अणु
		/* Uninitialized काष्ठाure detected */
		वापस 0;
	पूर्ण

	अगर ((streamPtr->dictSize > 0) && (smallest > dictEnd))
		smallest = dictEnd;

	LZ4_renormDictT(streamPtr, smallest);

	अगर (acceleration < 1)
		acceleration = LZ4_ACCELERATION_DEFAULT;

	/* Check overlapping input/dictionary space */
	अणु
		स्थिर BYTE *sourceEnd = (स्थिर BYTE *) source + inputSize;

		अगर ((sourceEnd > streamPtr->dictionary)
			&& (sourceEnd < dictEnd)) अणु
			streamPtr->dictSize = (U32)(dictEnd - sourceEnd);
			अगर (streamPtr->dictSize > 64 * KB)
				streamPtr->dictSize = 64 * KB;
			अगर (streamPtr->dictSize < 4)
				streamPtr->dictSize = 0;
			streamPtr->dictionary = dictEnd - streamPtr->dictSize;
		पूर्ण
	पूर्ण

	/* prefix mode : source data follows dictionary */
	अगर (dictEnd == (स्थिर BYTE *)source) अणु
		पूर्णांक result;

		अगर ((streamPtr->dictSize < 64 * KB) &&
			(streamPtr->dictSize < streamPtr->currentOffset)) अणु
			result = LZ4_compress_generic(
				streamPtr, source, dest, inputSize,
				maxOutputSize, limitedOutput, byU32,
				withPrefix64k, dictSmall, acceleration);
		पूर्ण अन्यथा अणु
			result = LZ4_compress_generic(
				streamPtr, source, dest, inputSize,
				maxOutputSize, limitedOutput, byU32,
				withPrefix64k, noDictIssue, acceleration);
		पूर्ण
		streamPtr->dictSize += (U32)inputSize;
		streamPtr->currentOffset += (U32)inputSize;
		वापस result;
	पूर्ण

	/* बाह्यal dictionary mode */
	अणु
		पूर्णांक result;

		अगर ((streamPtr->dictSize < 64 * KB) &&
			(streamPtr->dictSize < streamPtr->currentOffset)) अणु
			result = LZ4_compress_generic(
				streamPtr, source, dest, inputSize,
				maxOutputSize, limitedOutput, byU32,
				usingExtDict, dictSmall, acceleration);
		पूर्ण अन्यथा अणु
			result = LZ4_compress_generic(
				streamPtr, source, dest, inputSize,
				maxOutputSize, limitedOutput, byU32,
				usingExtDict, noDictIssue, acceleration);
		पूर्ण
		streamPtr->dictionary = (स्थिर BYTE *)source;
		streamPtr->dictSize = (U32)inputSize;
		streamPtr->currentOffset += (U32)inputSize;
		वापस result;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(LZ4_compress_fast_जारी);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("LZ4 compressor");
