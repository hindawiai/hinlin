<शैली गुरु>
/**
 * Copyright (c) 2016-present, Przemyslaw Skibinski, Yann Collet, Facebook, Inc.
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

/* Note : this file is पूर्णांकended to be included within zstd_compress.c */

#अगर_अघोषित ZSTD_OPT_H_91842398743
#घोषणा ZSTD_OPT_H_91842398743

#घोषणा ZSTD_LITFREQ_ADD 2
#घोषणा ZSTD_FREQ_DIV 4
#घोषणा ZSTD_MAX_PRICE (1 << 30)

/*-*************************************
*  Price functions क्रम optimal parser
***************************************/
FORCE_INLINE व्योम ZSTD_setLog2Prices(seqStore_t *ssPtr)
अणु
	ssPtr->log2matchLengthSum = ZSTD_highbit32(ssPtr->matchLengthSum + 1);
	ssPtr->log2litLengthSum = ZSTD_highbit32(ssPtr->litLengthSum + 1);
	ssPtr->log2litSum = ZSTD_highbit32(ssPtr->litSum + 1);
	ssPtr->log2offCodeSum = ZSTD_highbit32(ssPtr->offCodeSum + 1);
	ssPtr->factor = 1 + ((ssPtr->litSum >> 5) / ssPtr->litLengthSum) + ((ssPtr->litSum << 1) / (ssPtr->litSum + ssPtr->matchSum));
पूर्ण

ZSTD_STATIC व्योम ZSTD_rescaleFreqs(seqStore_t *ssPtr, स्थिर BYTE *src, माप_प्रकार srcSize)
अणु
	अचिन्हित u;

	ssPtr->cachedLiterals = शून्य;
	ssPtr->cachedPrice = ssPtr->cachedLitLength = 0;
	ssPtr->अटलPrices = 0;

	अगर (ssPtr->litLengthSum == 0) अणु
		अगर (srcSize <= 1024)
			ssPtr->अटलPrices = 1;

		क्रम (u = 0; u <= MaxLit; u++)
			ssPtr->litFreq[u] = 0;
		क्रम (u = 0; u < srcSize; u++)
			ssPtr->litFreq[src[u]]++;

		ssPtr->litSum = 0;
		ssPtr->litLengthSum = MaxLL + 1;
		ssPtr->matchLengthSum = MaxML + 1;
		ssPtr->offCodeSum = (MaxOff + 1);
		ssPtr->matchSum = (ZSTD_LITFREQ_ADD << Litbits);

		क्रम (u = 0; u <= MaxLit; u++) अणु
			ssPtr->litFreq[u] = 1 + (ssPtr->litFreq[u] >> ZSTD_FREQ_DIV);
			ssPtr->litSum += ssPtr->litFreq[u];
		पूर्ण
		क्रम (u = 0; u <= MaxLL; u++)
			ssPtr->litLengthFreq[u] = 1;
		क्रम (u = 0; u <= MaxML; u++)
			ssPtr->matchLengthFreq[u] = 1;
		क्रम (u = 0; u <= MaxOff; u++)
			ssPtr->offCodeFreq[u] = 1;
	पूर्ण अन्यथा अणु
		ssPtr->matchLengthSum = 0;
		ssPtr->litLengthSum = 0;
		ssPtr->offCodeSum = 0;
		ssPtr->matchSum = 0;
		ssPtr->litSum = 0;

		क्रम (u = 0; u <= MaxLit; u++) अणु
			ssPtr->litFreq[u] = 1 + (ssPtr->litFreq[u] >> (ZSTD_FREQ_DIV + 1));
			ssPtr->litSum += ssPtr->litFreq[u];
		पूर्ण
		क्रम (u = 0; u <= MaxLL; u++) अणु
			ssPtr->litLengthFreq[u] = 1 + (ssPtr->litLengthFreq[u] >> (ZSTD_FREQ_DIV + 1));
			ssPtr->litLengthSum += ssPtr->litLengthFreq[u];
		पूर्ण
		क्रम (u = 0; u <= MaxML; u++) अणु
			ssPtr->matchLengthFreq[u] = 1 + (ssPtr->matchLengthFreq[u] >> ZSTD_FREQ_DIV);
			ssPtr->matchLengthSum += ssPtr->matchLengthFreq[u];
			ssPtr->matchSum += ssPtr->matchLengthFreq[u] * (u + 3);
		पूर्ण
		ssPtr->matchSum *= ZSTD_LITFREQ_ADD;
		क्रम (u = 0; u <= MaxOff; u++) अणु
			ssPtr->offCodeFreq[u] = 1 + (ssPtr->offCodeFreq[u] >> ZSTD_FREQ_DIV);
			ssPtr->offCodeSum += ssPtr->offCodeFreq[u];
		पूर्ण
	पूर्ण

	ZSTD_setLog2Prices(ssPtr);
पूर्ण

FORCE_INLINE U32 ZSTD_getLiteralPrice(seqStore_t *ssPtr, U32 litLength, स्थिर BYTE *literals)
अणु
	U32 price, u;

	अगर (ssPtr->अटलPrices)
		वापस ZSTD_highbit32((U32)litLength + 1) + (litLength * 6);

	अगर (litLength == 0)
		वापस ssPtr->log2litLengthSum - ZSTD_highbit32(ssPtr->litLengthFreq[0] + 1);

	/* literals */
	अगर (ssPtr->cachedLiterals == literals) अणु
		U32 स्थिर additional = litLength - ssPtr->cachedLitLength;
		स्थिर BYTE *literals2 = ssPtr->cachedLiterals + ssPtr->cachedLitLength;
		price = ssPtr->cachedPrice + additional * ssPtr->log2litSum;
		क्रम (u = 0; u < additional; u++)
			price -= ZSTD_highbit32(ssPtr->litFreq[literals2[u]] + 1);
		ssPtr->cachedPrice = price;
		ssPtr->cachedLitLength = litLength;
	पूर्ण अन्यथा अणु
		price = litLength * ssPtr->log2litSum;
		क्रम (u = 0; u < litLength; u++)
			price -= ZSTD_highbit32(ssPtr->litFreq[literals[u]] + 1);

		अगर (litLength >= 12) अणु
			ssPtr->cachedLiterals = literals;
			ssPtr->cachedPrice = price;
			ssPtr->cachedLitLength = litLength;
		पूर्ण
	पूर्ण

	/* literal Length */
	अणु
		स्थिर BYTE LL_deltaCode = 19;
		स्थिर BYTE llCode = (litLength > 63) ? (BYTE)ZSTD_highbit32(litLength) + LL_deltaCode : LL_Code[litLength];
		price += LL_bits[llCode] + ssPtr->log2litLengthSum - ZSTD_highbit32(ssPtr->litLengthFreq[llCode] + 1);
	पूर्ण

	वापस price;
पूर्ण

FORCE_INLINE U32 ZSTD_getPrice(seqStore_t *seqStorePtr, U32 litLength, स्थिर BYTE *literals, U32 offset, U32 matchLength, स्थिर पूर्णांक ultra)
अणु
	/* offset */
	U32 price;
	BYTE स्थिर offCode = (BYTE)ZSTD_highbit32(offset + 1);

	अगर (seqStorePtr->अटलPrices)
		वापस ZSTD_getLiteralPrice(seqStorePtr, litLength, literals) + ZSTD_highbit32((U32)matchLength + 1) + 16 + offCode;

	price = offCode + seqStorePtr->log2offCodeSum - ZSTD_highbit32(seqStorePtr->offCodeFreq[offCode] + 1);
	अगर (!ultra && offCode >= 20)
		price += (offCode - 19) * 2;

	/* match Length */
	अणु
		स्थिर BYTE ML_deltaCode = 36;
		स्थिर BYTE mlCode = (matchLength > 127) ? (BYTE)ZSTD_highbit32(matchLength) + ML_deltaCode : ML_Code[matchLength];
		price += ML_bits[mlCode] + seqStorePtr->log2matchLengthSum - ZSTD_highbit32(seqStorePtr->matchLengthFreq[mlCode] + 1);
	पूर्ण

	वापस price + ZSTD_getLiteralPrice(seqStorePtr, litLength, literals) + seqStorePtr->factor;
पूर्ण

ZSTD_STATIC व्योम ZSTD_updatePrice(seqStore_t *seqStorePtr, U32 litLength, स्थिर BYTE *literals, U32 offset, U32 matchLength)
अणु
	U32 u;

	/* literals */
	seqStorePtr->litSum += litLength * ZSTD_LITFREQ_ADD;
	क्रम (u = 0; u < litLength; u++)
		seqStorePtr->litFreq[literals[u]] += ZSTD_LITFREQ_ADD;

	/* literal Length */
	अणु
		स्थिर BYTE LL_deltaCode = 19;
		स्थिर BYTE llCode = (litLength > 63) ? (BYTE)ZSTD_highbit32(litLength) + LL_deltaCode : LL_Code[litLength];
		seqStorePtr->litLengthFreq[llCode]++;
		seqStorePtr->litLengthSum++;
	पूर्ण

	/* match offset */
	अणु
		BYTE स्थिर offCode = (BYTE)ZSTD_highbit32(offset + 1);
		seqStorePtr->offCodeSum++;
		seqStorePtr->offCodeFreq[offCode]++;
	पूर्ण

	/* match Length */
	अणु
		स्थिर BYTE ML_deltaCode = 36;
		स्थिर BYTE mlCode = (matchLength > 127) ? (BYTE)ZSTD_highbit32(matchLength) + ML_deltaCode : ML_Code[matchLength];
		seqStorePtr->matchLengthFreq[mlCode]++;
		seqStorePtr->matchLengthSum++;
	पूर्ण

	ZSTD_setLog2Prices(seqStorePtr);
पूर्ण

#घोषणा SET_PRICE(pos, mlen_, offset_, litlen_, price_)           \
	अणु                                                         \
		जबतक (last_pos < pos) अणु                          \
			opt[last_pos + 1].price = ZSTD_MAX_PRICE; \
			last_pos++;                               \
		पूर्ण                                                 \
		opt[pos].mlen = mlen_;                            \
		opt[pos].off = offset_;                           \
		opt[pos].litlen = litlen_;                        \
		opt[pos].price = price_;                          \
	पूर्ण

/* Update hashTable3 up to ip (excluded)
   Assumption : always within prefix (i.e. not within extDict) */
FORCE_INLINE
U32 ZSTD_insertAndFindFirstIndexHash3(ZSTD_CCtx *zc, स्थिर BYTE *ip)
अणु
	U32 *स्थिर hashTable3 = zc->hashTable3;
	U32 स्थिर hashLog3 = zc->hashLog3;
	स्थिर BYTE *स्थिर base = zc->base;
	U32 idx = zc->nextToUpdate3;
	स्थिर U32 target = zc->nextToUpdate3 = (U32)(ip - base);
	स्थिर माप_प्रकार hash3 = ZSTD_hash3Ptr(ip, hashLog3);

	जबतक (idx < target) अणु
		hashTable3[ZSTD_hash3Ptr(base + idx, hashLog3)] = idx;
		idx++;
	पूर्ण

	वापस hashTable3[hash3];
पूर्ण

/*-*************************************
*  Binary Tree search
***************************************/
अटल U32 ZSTD_insertBtAndGetAllMatches(ZSTD_CCtx *zc, स्थिर BYTE *स्थिर ip, स्थिर BYTE *स्थिर iLimit, U32 nbCompares, स्थिर U32 mls, U32 extDict,
					 ZSTD_match_t *matches, स्थिर U32 minMatchLen)
अणु
	स्थिर BYTE *स्थिर base = zc->base;
	स्थिर U32 curr = (U32)(ip - base);
	स्थिर U32 hashLog = zc->params.cParams.hashLog;
	स्थिर माप_प्रकार h = ZSTD_hashPtr(ip, hashLog, mls);
	U32 *स्थिर hashTable = zc->hashTable;
	U32 matchIndex = hashTable[h];
	U32 *स्थिर bt = zc->chainTable;
	स्थिर U32 btLog = zc->params.cParams.chainLog - 1;
	स्थिर U32 btMask = (1U << btLog) - 1;
	माप_प्रकार commonLengthSmaller = 0, commonLengthLarger = 0;
	स्थिर BYTE *स्थिर dictBase = zc->dictBase;
	स्थिर U32 dictLimit = zc->dictLimit;
	स्थिर BYTE *स्थिर dictEnd = dictBase + dictLimit;
	स्थिर BYTE *स्थिर prefixStart = base + dictLimit;
	स्थिर U32 btLow = btMask >= curr ? 0 : curr - btMask;
	स्थिर U32 winकरोwLow = zc->lowLimit;
	U32 *smallerPtr = bt + 2 * (curr & btMask);
	U32 *largerPtr = bt + 2 * (curr & btMask) + 1;
	U32 matchEndIdx = curr + 8;
	U32 dummy32; /* to be nullअगरied at the end */
	U32 mnum = 0;

	स्थिर U32 minMatch = (mls == 3) ? 3 : 4;
	माप_प्रकार bestLength = minMatchLen - 1;

	अगर (minMatch == 3) अणु /* HC3 match finder */
		U32 स्थिर matchIndex3 = ZSTD_insertAndFindFirstIndexHash3(zc, ip);
		अगर (matchIndex3 > winकरोwLow && (curr - matchIndex3 < (1 << 18))) अणु
			स्थिर BYTE *match;
			माप_प्रकार currMl = 0;
			अगर ((!extDict) || matchIndex3 >= dictLimit) अणु
				match = base + matchIndex3;
				अगर (match[bestLength] == ip[bestLength])
					currMl = ZSTD_count(ip, match, iLimit);
			पूर्ण अन्यथा अणु
				match = dictBase + matchIndex3;
				अगर (ZSTD_पढ़ोMINMATCH(match, MINMATCH) ==
				    ZSTD_पढ़ोMINMATCH(ip, MINMATCH)) /* assumption : matchIndex3 <= dictLimit-4 (by table स्थिरruction) */
					currMl = ZSTD_count_2segments(ip + MINMATCH, match + MINMATCH, iLimit, dictEnd, prefixStart) + MINMATCH;
			पूर्ण

			/* save best solution */
			अगर (currMl > bestLength) अणु
				bestLength = currMl;
				matches[mnum].off = ZSTD_REP_MOVE_OPT + curr - matchIndex3;
				matches[mnum].len = (U32)currMl;
				mnum++;
				अगर (currMl > ZSTD_OPT_NUM)
					जाओ update;
				अगर (ip + currMl == iLimit)
					जाओ update; /* best possible, and aव्योम पढ़ो overflow*/
			पूर्ण
		पूर्ण
	पूर्ण

	hashTable[h] = curr; /* Update Hash Table */

	जबतक (nbCompares-- && (matchIndex > winकरोwLow)) अणु
		U32 *nextPtr = bt + 2 * (matchIndex & btMask);
		माप_प्रकार matchLength = MIN(commonLengthSmaller, commonLengthLarger); /* guaranteed minimum nb of common bytes */
		स्थिर BYTE *match;

		अगर ((!extDict) || (matchIndex + matchLength >= dictLimit)) अणु
			match = base + matchIndex;
			अगर (match[matchLength] == ip[matchLength]) अणु
				matchLength += ZSTD_count(ip + matchLength + 1, match + matchLength + 1, iLimit) + 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			match = dictBase + matchIndex;
			matchLength += ZSTD_count_2segments(ip + matchLength, match + matchLength, iLimit, dictEnd, prefixStart);
			अगर (matchIndex + matchLength >= dictLimit)
				match = base + matchIndex; /* to prepare क्रम next usage of match[matchLength] */
		पूर्ण

		अगर (matchLength > bestLength) अणु
			अगर (matchLength > matchEndIdx - matchIndex)
				matchEndIdx = matchIndex + (U32)matchLength;
			bestLength = matchLength;
			matches[mnum].off = ZSTD_REP_MOVE_OPT + curr - matchIndex;
			matches[mnum].len = (U32)matchLength;
			mnum++;
			अगर (matchLength > ZSTD_OPT_NUM)
				अवरोध;
			अगर (ip + matchLength == iLimit) /* equal : no way to know अगर inf or sup */
				अवरोध;			/* drop, to guarantee consistency (miss a little bit of compression) */
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

update:
	zc->nextToUpdate = (matchEndIdx > curr + 8) ? matchEndIdx - 8 : curr + 1;
	वापस mnum;
पूर्ण

/** Tree updater, providing best match */
अटल U32 ZSTD_BtGetAllMatches(ZSTD_CCtx *zc, स्थिर BYTE *स्थिर ip, स्थिर BYTE *स्थिर iLimit, स्थिर U32 maxNbAttempts, स्थिर U32 mls, ZSTD_match_t *matches,
				स्थिर U32 minMatchLen)
अणु
	अगर (ip < zc->base + zc->nextToUpdate)
		वापस 0; /* skipped area */
	ZSTD_updateTree(zc, ip, iLimit, maxNbAttempts, mls);
	वापस ZSTD_insertBtAndGetAllMatches(zc, ip, iLimit, maxNbAttempts, mls, 0, matches, minMatchLen);
पूर्ण

अटल U32 ZSTD_BtGetAllMatches_selectMLS(ZSTD_CCtx *zc, /* Index table will be updated */
					  स्थिर BYTE *ip, स्थिर BYTE *स्थिर iHighLimit, स्थिर U32 maxNbAttempts, स्थिर U32 matchLengthSearch,
					  ZSTD_match_t *matches, स्थिर U32 minMatchLen)
अणु
	चयन (matchLengthSearch) अणु
	हाल 3: वापस ZSTD_BtGetAllMatches(zc, ip, iHighLimit, maxNbAttempts, 3, matches, minMatchLen);
	शेष:
	हाल 4: वापस ZSTD_BtGetAllMatches(zc, ip, iHighLimit, maxNbAttempts, 4, matches, minMatchLen);
	हाल 5: वापस ZSTD_BtGetAllMatches(zc, ip, iHighLimit, maxNbAttempts, 5, matches, minMatchLen);
	हाल 7:
	हाल 6: वापस ZSTD_BtGetAllMatches(zc, ip, iHighLimit, maxNbAttempts, 6, matches, minMatchLen);
	पूर्ण
पूर्ण

/** Tree updater, providing best match */
अटल U32 ZSTD_BtGetAllMatches_extDict(ZSTD_CCtx *zc, स्थिर BYTE *स्थिर ip, स्थिर BYTE *स्थिर iLimit, स्थिर U32 maxNbAttempts, स्थिर U32 mls,
					ZSTD_match_t *matches, स्थिर U32 minMatchLen)
अणु
	अगर (ip < zc->base + zc->nextToUpdate)
		वापस 0; /* skipped area */
	ZSTD_updateTree_extDict(zc, ip, iLimit, maxNbAttempts, mls);
	वापस ZSTD_insertBtAndGetAllMatches(zc, ip, iLimit, maxNbAttempts, mls, 1, matches, minMatchLen);
पूर्ण

अटल U32 ZSTD_BtGetAllMatches_selectMLS_extDict(ZSTD_CCtx *zc, /* Index table will be updated */
						  स्थिर BYTE *ip, स्थिर BYTE *स्थिर iHighLimit, स्थिर U32 maxNbAttempts, स्थिर U32 matchLengthSearch,
						  ZSTD_match_t *matches, स्थिर U32 minMatchLen)
अणु
	चयन (matchLengthSearch) अणु
	हाल 3: वापस ZSTD_BtGetAllMatches_extDict(zc, ip, iHighLimit, maxNbAttempts, 3, matches, minMatchLen);
	शेष:
	हाल 4: वापस ZSTD_BtGetAllMatches_extDict(zc, ip, iHighLimit, maxNbAttempts, 4, matches, minMatchLen);
	हाल 5: वापस ZSTD_BtGetAllMatches_extDict(zc, ip, iHighLimit, maxNbAttempts, 5, matches, minMatchLen);
	हाल 7:
	हाल 6: वापस ZSTD_BtGetAllMatches_extDict(zc, ip, iHighLimit, maxNbAttempts, 6, matches, minMatchLen);
	पूर्ण
पूर्ण

/*-*******************************
*  Optimal parser
*********************************/
FORCE_INLINE
व्योम ZSTD_compressBlock_opt_generic(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर पूर्णांक ultra)
अणु
	seqStore_t *seqStorePtr = &(ctx->seqStore);
	स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)src;
	स्थिर BYTE *ip = istart;
	स्थिर BYTE *anchor = istart;
	स्थिर BYTE *स्थिर iend = istart + srcSize;
	स्थिर BYTE *स्थिर ilimit = iend - 8;
	स्थिर BYTE *स्थिर base = ctx->base;
	स्थिर BYTE *स्थिर prefixStart = base + ctx->dictLimit;

	स्थिर U32 maxSearches = 1U << ctx->params.cParams.searchLog;
	स्थिर U32 sufficient_len = ctx->params.cParams.targetLength;
	स्थिर U32 mls = ctx->params.cParams.searchLength;
	स्थिर U32 minMatch = (ctx->params.cParams.searchLength == 3) ? 3 : 4;

	ZSTD_optimal_t *opt = seqStorePtr->priceTable;
	ZSTD_match_t *matches = seqStorePtr->matchTable;
	स्थिर BYTE *inr;
	U32 offset, rep[ZSTD_REP_NUM];

	/* init */
	ctx->nextToUpdate3 = ctx->nextToUpdate;
	ZSTD_rescaleFreqs(seqStorePtr, (स्थिर BYTE *)src, srcSize);
	ip += (ip == prefixStart);
	अणु
		U32 i;
		क्रम (i = 0; i < ZSTD_REP_NUM; i++)
			rep[i] = ctx->rep[i];
	पूर्ण

	/* Match Loop */
	जबतक (ip < ilimit) अणु
		U32 cur, match_num, last_pos, litlen, price;
		U32 u, mlen, best_mlen, best_off, litLength;
		स_रखो(opt, 0, माप(ZSTD_optimal_t));
		last_pos = 0;
		litlen = (U32)(ip - anchor);

		/* check repCode */
		अणु
			U32 i, last_i = ZSTD_REP_CHECK + (ip == anchor);
			क्रम (i = (ip == anchor); i < last_i; i++) अणु
				स्थिर S32 repCur = (i == ZSTD_REP_MOVE_OPT) ? (rep[0] - 1) : rep[i];
				अगर ((repCur > 0) && (repCur < (S32)(ip - prefixStart)) &&
				    (ZSTD_पढ़ोMINMATCH(ip, minMatch) == ZSTD_पढ़ोMINMATCH(ip - repCur, minMatch))) अणु
					mlen = (U32)ZSTD_count(ip + minMatch, ip + minMatch - repCur, iend) + minMatch;
					अगर (mlen > sufficient_len || mlen >= ZSTD_OPT_NUM) अणु
						best_mlen = mlen;
						best_off = i;
						cur = 0;
						last_pos = 1;
						जाओ _storeSequence;
					पूर्ण
					best_off = i - (ip == anchor);
					करो अणु
						price = ZSTD_getPrice(seqStorePtr, litlen, anchor, best_off, mlen - MINMATCH, ultra);
						अगर (mlen > last_pos || price < opt[mlen].price)
							SET_PRICE(mlen, mlen, i, litlen, price); /* note : macro modअगरies last_pos */
						mlen--;
					पूर्ण जबतक (mlen >= minMatch);
				पूर्ण
			पूर्ण
		पूर्ण

		match_num = ZSTD_BtGetAllMatches_selectMLS(ctx, ip, iend, maxSearches, mls, matches, minMatch);

		अगर (!last_pos && !match_num) अणु
			ip++;
			जारी;
		पूर्ण

		अगर (match_num && (matches[match_num - 1].len > sufficient_len || matches[match_num - 1].len >= ZSTD_OPT_NUM)) अणु
			best_mlen = matches[match_num - 1].len;
			best_off = matches[match_num - 1].off;
			cur = 0;
			last_pos = 1;
			जाओ _storeSequence;
		पूर्ण

		/* set prices using matches at position = 0 */
		best_mlen = (last_pos) ? last_pos : minMatch;
		क्रम (u = 0; u < match_num; u++) अणु
			mlen = (u > 0) ? matches[u - 1].len + 1 : best_mlen;
			best_mlen = matches[u].len;
			जबतक (mlen <= best_mlen) अणु
				price = ZSTD_getPrice(seqStorePtr, litlen, anchor, matches[u].off - 1, mlen - MINMATCH, ultra);
				अगर (mlen > last_pos || price < opt[mlen].price)
					SET_PRICE(mlen, mlen, matches[u].off, litlen, price); /* note : macro modअगरies last_pos */
				mlen++;
			पूर्ण
		पूर्ण

		अगर (last_pos < minMatch) अणु
			ip++;
			जारी;
		पूर्ण

		/* initialize opt[0] */
		अणु
			U32 i;
			क्रम (i = 0; i < ZSTD_REP_NUM; i++)
				opt[0].rep[i] = rep[i];
		पूर्ण
		opt[0].mlen = 1;
		opt[0].litlen = litlen;

		/* check further positions */
		क्रम (cur = 1; cur <= last_pos; cur++) अणु
			inr = ip + cur;

			अगर (opt[cur - 1].mlen == 1) अणु
				litlen = opt[cur - 1].litlen + 1;
				अगर (cur > litlen) अणु
					price = opt[cur - litlen].price + ZSTD_getLiteralPrice(seqStorePtr, litlen, inr - litlen);
				पूर्ण अन्यथा
					price = ZSTD_getLiteralPrice(seqStorePtr, litlen, anchor);
			पूर्ण अन्यथा अणु
				litlen = 1;
				price = opt[cur - 1].price + ZSTD_getLiteralPrice(seqStorePtr, litlen, inr - 1);
			पूर्ण

			अगर (cur > last_pos || price <= opt[cur].price)
				SET_PRICE(cur, 1, 0, litlen, price);

			अगर (cur == last_pos)
				अवरोध;

			अगर (inr > ilimit) /* last match must start at a minimum distance of 8 from oend */
				जारी;

			mlen = opt[cur].mlen;
			अगर (opt[cur].off > ZSTD_REP_MOVE_OPT) अणु
				opt[cur].rep[2] = opt[cur - mlen].rep[1];
				opt[cur].rep[1] = opt[cur - mlen].rep[0];
				opt[cur].rep[0] = opt[cur].off - ZSTD_REP_MOVE_OPT;
			पूर्ण अन्यथा अणु
				opt[cur].rep[2] = (opt[cur].off > 1) ? opt[cur - mlen].rep[1] : opt[cur - mlen].rep[2];
				opt[cur].rep[1] = (opt[cur].off > 0) ? opt[cur - mlen].rep[0] : opt[cur - mlen].rep[1];
				opt[cur].rep[0] =
				    ((opt[cur].off == ZSTD_REP_MOVE_OPT) && (mlen != 1)) ? (opt[cur - mlen].rep[0] - 1) : (opt[cur - mlen].rep[opt[cur].off]);
			पूर्ण

			best_mlen = minMatch;
			अणु
				U32 i, last_i = ZSTD_REP_CHECK + (mlen != 1);
				क्रम (i = (opt[cur].mlen != 1); i < last_i; i++) अणु /* check rep */
					स्थिर S32 repCur = (i == ZSTD_REP_MOVE_OPT) ? (opt[cur].rep[0] - 1) : opt[cur].rep[i];
					अगर ((repCur > 0) && (repCur < (S32)(inr - prefixStart)) &&
					    (ZSTD_पढ़ोMINMATCH(inr, minMatch) == ZSTD_पढ़ोMINMATCH(inr - repCur, minMatch))) अणु
						mlen = (U32)ZSTD_count(inr + minMatch, inr + minMatch - repCur, iend) + minMatch;

						अगर (mlen > sufficient_len || cur + mlen >= ZSTD_OPT_NUM) अणु
							best_mlen = mlen;
							best_off = i;
							last_pos = cur + 1;
							जाओ _storeSequence;
						पूर्ण

						best_off = i - (opt[cur].mlen != 1);
						अगर (mlen > best_mlen)
							best_mlen = mlen;

						करो अणु
							अगर (opt[cur].mlen == 1) अणु
								litlen = opt[cur].litlen;
								अगर (cur > litlen) अणु
									price = opt[cur - litlen].price + ZSTD_getPrice(seqStorePtr, litlen, inr - litlen,
															best_off, mlen - MINMATCH, ultra);
								पूर्ण अन्यथा
									price = ZSTD_getPrice(seqStorePtr, litlen, anchor, best_off, mlen - MINMATCH, ultra);
							पूर्ण अन्यथा अणु
								litlen = 0;
								price = opt[cur].price + ZSTD_getPrice(seqStorePtr, 0, शून्य, best_off, mlen - MINMATCH, ultra);
							पूर्ण

							अगर (cur + mlen > last_pos || price <= opt[cur + mlen].price)
								SET_PRICE(cur + mlen, mlen, i, litlen, price);
							mlen--;
						पूर्ण जबतक (mlen >= minMatch);
					पूर्ण
				पूर्ण
			पूर्ण

			match_num = ZSTD_BtGetAllMatches_selectMLS(ctx, inr, iend, maxSearches, mls, matches, best_mlen);

			अगर (match_num > 0 && (matches[match_num - 1].len > sufficient_len || cur + matches[match_num - 1].len >= ZSTD_OPT_NUM)) अणु
				best_mlen = matches[match_num - 1].len;
				best_off = matches[match_num - 1].off;
				last_pos = cur + 1;
				जाओ _storeSequence;
			पूर्ण

			/* set prices using matches at position = cur */
			क्रम (u = 0; u < match_num; u++) अणु
				mlen = (u > 0) ? matches[u - 1].len + 1 : best_mlen;
				best_mlen = matches[u].len;

				जबतक (mlen <= best_mlen) अणु
					अगर (opt[cur].mlen == 1) अणु
						litlen = opt[cur].litlen;
						अगर (cur > litlen)
							price = opt[cur - litlen].price + ZSTD_getPrice(seqStorePtr, litlen, ip + cur - litlen,
													matches[u].off - 1, mlen - MINMATCH, ultra);
						अन्यथा
							price = ZSTD_getPrice(seqStorePtr, litlen, anchor, matches[u].off - 1, mlen - MINMATCH, ultra);
					पूर्ण अन्यथा अणु
						litlen = 0;
						price = opt[cur].price + ZSTD_getPrice(seqStorePtr, 0, शून्य, matches[u].off - 1, mlen - MINMATCH, ultra);
					पूर्ण

					अगर (cur + mlen > last_pos || (price < opt[cur + mlen].price))
						SET_PRICE(cur + mlen, mlen, matches[u].off, litlen, price);

					mlen++;
				पूर्ण
			पूर्ण
		पूर्ण

		best_mlen = opt[last_pos].mlen;
		best_off = opt[last_pos].off;
		cur = last_pos - best_mlen;

	/* store sequence */
_storeSequence: /* cur, last_pos, best_mlen, best_off have to be set */
		opt[0].mlen = 1;

		जबतक (1) अणु
			mlen = opt[cur].mlen;
			offset = opt[cur].off;
			opt[cur].mlen = best_mlen;
			opt[cur].off = best_off;
			best_mlen = mlen;
			best_off = offset;
			अगर (mlen > cur)
				अवरोध;
			cur -= mlen;
		पूर्ण

		क्रम (u = 0; u <= last_pos;) अणु
			u += opt[u].mlen;
		पूर्ण

		क्रम (cur = 0; cur < last_pos;) अणु
			mlen = opt[cur].mlen;
			अगर (mlen == 1) अणु
				ip++;
				cur++;
				जारी;
			पूर्ण
			offset = opt[cur].off;
			cur += mlen;
			litLength = (U32)(ip - anchor);

			अगर (offset > ZSTD_REP_MOVE_OPT) अणु
				rep[2] = rep[1];
				rep[1] = rep[0];
				rep[0] = offset - ZSTD_REP_MOVE_OPT;
				offset--;
			पूर्ण अन्यथा अणु
				अगर (offset != 0) अणु
					best_off = (offset == ZSTD_REP_MOVE_OPT) ? (rep[0] - 1) : (rep[offset]);
					अगर (offset != 1)
						rep[2] = rep[1];
					rep[1] = rep[0];
					rep[0] = best_off;
				पूर्ण
				अगर (litLength == 0)
					offset--;
			पूर्ण

			ZSTD_updatePrice(seqStorePtr, litLength, anchor, offset, mlen - MINMATCH);
			ZSTD_storeSeq(seqStorePtr, litLength, anchor, offset, mlen - MINMATCH);
			anchor = ip = ip + mlen;
		पूर्ण
	पूर्ण /* क्रम (cur=0; cur < last_pos; ) */

	/* Save reps क्रम next block */
	अणु
		पूर्णांक i;
		क्रम (i = 0; i < ZSTD_REP_NUM; i++)
			ctx->repToConfirm[i] = rep[i];
	पूर्ण

	/* Last Literals */
	अणु
		माप_प्रकार स्थिर lastLLSize = iend - anchor;
		स_नकल(seqStorePtr->lit, anchor, lastLLSize);
		seqStorePtr->lit += lastLLSize;
	पूर्ण
पूर्ण

FORCE_INLINE
व्योम ZSTD_compressBlock_opt_extDict_generic(ZSTD_CCtx *ctx, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर पूर्णांक ultra)
अणु
	seqStore_t *seqStorePtr = &(ctx->seqStore);
	स्थिर BYTE *स्थिर istart = (स्थिर BYTE *)src;
	स्थिर BYTE *ip = istart;
	स्थिर BYTE *anchor = istart;
	स्थिर BYTE *स्थिर iend = istart + srcSize;
	स्थिर BYTE *स्थिर ilimit = iend - 8;
	स्थिर BYTE *स्थिर base = ctx->base;
	स्थिर U32 lowestIndex = ctx->lowLimit;
	स्थिर U32 dictLimit = ctx->dictLimit;
	स्थिर BYTE *स्थिर prefixStart = base + dictLimit;
	स्थिर BYTE *स्थिर dictBase = ctx->dictBase;
	स्थिर BYTE *स्थिर dictEnd = dictBase + dictLimit;

	स्थिर U32 maxSearches = 1U << ctx->params.cParams.searchLog;
	स्थिर U32 sufficient_len = ctx->params.cParams.targetLength;
	स्थिर U32 mls = ctx->params.cParams.searchLength;
	स्थिर U32 minMatch = (ctx->params.cParams.searchLength == 3) ? 3 : 4;

	ZSTD_optimal_t *opt = seqStorePtr->priceTable;
	ZSTD_match_t *matches = seqStorePtr->matchTable;
	स्थिर BYTE *inr;

	/* init */
	U32 offset, rep[ZSTD_REP_NUM];
	अणु
		U32 i;
		क्रम (i = 0; i < ZSTD_REP_NUM; i++)
			rep[i] = ctx->rep[i];
	पूर्ण

	ctx->nextToUpdate3 = ctx->nextToUpdate;
	ZSTD_rescaleFreqs(seqStorePtr, (स्थिर BYTE *)src, srcSize);
	ip += (ip == prefixStart);

	/* Match Loop */
	जबतक (ip < ilimit) अणु
		U32 cur, match_num, last_pos, litlen, price;
		U32 u, mlen, best_mlen, best_off, litLength;
		U32 curr = (U32)(ip - base);
		स_रखो(opt, 0, माप(ZSTD_optimal_t));
		last_pos = 0;
		opt[0].litlen = (U32)(ip - anchor);

		/* check repCode */
		अणु
			U32 i, last_i = ZSTD_REP_CHECK + (ip == anchor);
			क्रम (i = (ip == anchor); i < last_i; i++) अणु
				स्थिर S32 repCur = (i == ZSTD_REP_MOVE_OPT) ? (rep[0] - 1) : rep[i];
				स्थिर U32 repIndex = (U32)(curr - repCur);
				स्थिर BYTE *स्थिर repBase = repIndex < dictLimit ? dictBase : base;
				स्थिर BYTE *स्थिर repMatch = repBase + repIndex;
				अगर ((repCur > 0 && repCur <= (S32)curr) &&
				    (((U32)((dictLimit - 1) - repIndex) >= 3) & (repIndex > lowestIndex)) /* पूर्णांकentional overflow */
				    && (ZSTD_पढ़ोMINMATCH(ip, minMatch) == ZSTD_पढ़ोMINMATCH(repMatch, minMatch))) अणु
					/* repcode detected we should take it */
					स्थिर BYTE *स्थिर repEnd = repIndex < dictLimit ? dictEnd : iend;
					mlen = (U32)ZSTD_count_2segments(ip + minMatch, repMatch + minMatch, iend, repEnd, prefixStart) + minMatch;

					अगर (mlen > sufficient_len || mlen >= ZSTD_OPT_NUM) अणु
						best_mlen = mlen;
						best_off = i;
						cur = 0;
						last_pos = 1;
						जाओ _storeSequence;
					पूर्ण

					best_off = i - (ip == anchor);
					litlen = opt[0].litlen;
					करो अणु
						price = ZSTD_getPrice(seqStorePtr, litlen, anchor, best_off, mlen - MINMATCH, ultra);
						अगर (mlen > last_pos || price < opt[mlen].price)
							SET_PRICE(mlen, mlen, i, litlen, price); /* note : macro modअगरies last_pos */
						mlen--;
					पूर्ण जबतक (mlen >= minMatch);
				पूर्ण
			पूर्ण
		पूर्ण

		match_num = ZSTD_BtGetAllMatches_selectMLS_extDict(ctx, ip, iend, maxSearches, mls, matches, minMatch); /* first search (depth 0) */

		अगर (!last_pos && !match_num) अणु
			ip++;
			जारी;
		पूर्ण

		अणु
			U32 i;
			क्रम (i = 0; i < ZSTD_REP_NUM; i++)
				opt[0].rep[i] = rep[i];
		पूर्ण
		opt[0].mlen = 1;

		अगर (match_num && (matches[match_num - 1].len > sufficient_len || matches[match_num - 1].len >= ZSTD_OPT_NUM)) अणु
			best_mlen = matches[match_num - 1].len;
			best_off = matches[match_num - 1].off;
			cur = 0;
			last_pos = 1;
			जाओ _storeSequence;
		पूर्ण

		best_mlen = (last_pos) ? last_pos : minMatch;

		/* set prices using matches at position = 0 */
		क्रम (u = 0; u < match_num; u++) अणु
			mlen = (u > 0) ? matches[u - 1].len + 1 : best_mlen;
			best_mlen = matches[u].len;
			litlen = opt[0].litlen;
			जबतक (mlen <= best_mlen) अणु
				price = ZSTD_getPrice(seqStorePtr, litlen, anchor, matches[u].off - 1, mlen - MINMATCH, ultra);
				अगर (mlen > last_pos || price < opt[mlen].price)
					SET_PRICE(mlen, mlen, matches[u].off, litlen, price);
				mlen++;
			पूर्ण
		पूर्ण

		अगर (last_pos < minMatch) अणु
			ip++;
			जारी;
		पूर्ण

		/* check further positions */
		क्रम (cur = 1; cur <= last_pos; cur++) अणु
			inr = ip + cur;

			अगर (opt[cur - 1].mlen == 1) अणु
				litlen = opt[cur - 1].litlen + 1;
				अगर (cur > litlen) अणु
					price = opt[cur - litlen].price + ZSTD_getLiteralPrice(seqStorePtr, litlen, inr - litlen);
				पूर्ण अन्यथा
					price = ZSTD_getLiteralPrice(seqStorePtr, litlen, anchor);
			पूर्ण अन्यथा अणु
				litlen = 1;
				price = opt[cur - 1].price + ZSTD_getLiteralPrice(seqStorePtr, litlen, inr - 1);
			पूर्ण

			अगर (cur > last_pos || price <= opt[cur].price)
				SET_PRICE(cur, 1, 0, litlen, price);

			अगर (cur == last_pos)
				अवरोध;

			अगर (inr > ilimit) /* last match must start at a minimum distance of 8 from oend */
				जारी;

			mlen = opt[cur].mlen;
			अगर (opt[cur].off > ZSTD_REP_MOVE_OPT) अणु
				opt[cur].rep[2] = opt[cur - mlen].rep[1];
				opt[cur].rep[1] = opt[cur - mlen].rep[0];
				opt[cur].rep[0] = opt[cur].off - ZSTD_REP_MOVE_OPT;
			पूर्ण अन्यथा अणु
				opt[cur].rep[2] = (opt[cur].off > 1) ? opt[cur - mlen].rep[1] : opt[cur - mlen].rep[2];
				opt[cur].rep[1] = (opt[cur].off > 0) ? opt[cur - mlen].rep[0] : opt[cur - mlen].rep[1];
				opt[cur].rep[0] =
				    ((opt[cur].off == ZSTD_REP_MOVE_OPT) && (mlen != 1)) ? (opt[cur - mlen].rep[0] - 1) : (opt[cur - mlen].rep[opt[cur].off]);
			पूर्ण

			best_mlen = minMatch;
			अणु
				U32 i, last_i = ZSTD_REP_CHECK + (mlen != 1);
				क्रम (i = (mlen != 1); i < last_i; i++) अणु
					स्थिर S32 repCur = (i == ZSTD_REP_MOVE_OPT) ? (opt[cur].rep[0] - 1) : opt[cur].rep[i];
					स्थिर U32 repIndex = (U32)(curr + cur - repCur);
					स्थिर BYTE *स्थिर repBase = repIndex < dictLimit ? dictBase : base;
					स्थिर BYTE *स्थिर repMatch = repBase + repIndex;
					अगर ((repCur > 0 && repCur <= (S32)(curr + cur)) &&
					    (((U32)((dictLimit - 1) - repIndex) >= 3) & (repIndex > lowestIndex)) /* पूर्णांकentional overflow */
					    && (ZSTD_पढ़ोMINMATCH(inr, minMatch) == ZSTD_पढ़ोMINMATCH(repMatch, minMatch))) अणु
						/* repcode detected */
						स्थिर BYTE *स्थिर repEnd = repIndex < dictLimit ? dictEnd : iend;
						mlen = (U32)ZSTD_count_2segments(inr + minMatch, repMatch + minMatch, iend, repEnd, prefixStart) + minMatch;

						अगर (mlen > sufficient_len || cur + mlen >= ZSTD_OPT_NUM) अणु
							best_mlen = mlen;
							best_off = i;
							last_pos = cur + 1;
							जाओ _storeSequence;
						पूर्ण

						best_off = i - (opt[cur].mlen != 1);
						अगर (mlen > best_mlen)
							best_mlen = mlen;

						करो अणु
							अगर (opt[cur].mlen == 1) अणु
								litlen = opt[cur].litlen;
								अगर (cur > litlen) अणु
									price = opt[cur - litlen].price + ZSTD_getPrice(seqStorePtr, litlen, inr - litlen,
															best_off, mlen - MINMATCH, ultra);
								पूर्ण अन्यथा
									price = ZSTD_getPrice(seqStorePtr, litlen, anchor, best_off, mlen - MINMATCH, ultra);
							पूर्ण अन्यथा अणु
								litlen = 0;
								price = opt[cur].price + ZSTD_getPrice(seqStorePtr, 0, शून्य, best_off, mlen - MINMATCH, ultra);
							पूर्ण

							अगर (cur + mlen > last_pos || price <= opt[cur + mlen].price)
								SET_PRICE(cur + mlen, mlen, i, litlen, price);
							mlen--;
						पूर्ण जबतक (mlen >= minMatch);
					पूर्ण
				पूर्ण
			पूर्ण

			match_num = ZSTD_BtGetAllMatches_selectMLS_extDict(ctx, inr, iend, maxSearches, mls, matches, minMatch);

			अगर (match_num > 0 && (matches[match_num - 1].len > sufficient_len || cur + matches[match_num - 1].len >= ZSTD_OPT_NUM)) अणु
				best_mlen = matches[match_num - 1].len;
				best_off = matches[match_num - 1].off;
				last_pos = cur + 1;
				जाओ _storeSequence;
			पूर्ण

			/* set prices using matches at position = cur */
			क्रम (u = 0; u < match_num; u++) अणु
				mlen = (u > 0) ? matches[u - 1].len + 1 : best_mlen;
				best_mlen = matches[u].len;

				जबतक (mlen <= best_mlen) अणु
					अगर (opt[cur].mlen == 1) अणु
						litlen = opt[cur].litlen;
						अगर (cur > litlen)
							price = opt[cur - litlen].price + ZSTD_getPrice(seqStorePtr, litlen, ip + cur - litlen,
													matches[u].off - 1, mlen - MINMATCH, ultra);
						अन्यथा
							price = ZSTD_getPrice(seqStorePtr, litlen, anchor, matches[u].off - 1, mlen - MINMATCH, ultra);
					पूर्ण अन्यथा अणु
						litlen = 0;
						price = opt[cur].price + ZSTD_getPrice(seqStorePtr, 0, शून्य, matches[u].off - 1, mlen - MINMATCH, ultra);
					पूर्ण

					अगर (cur + mlen > last_pos || (price < opt[cur + mlen].price))
						SET_PRICE(cur + mlen, mlen, matches[u].off, litlen, price);

					mlen++;
				पूर्ण
			पूर्ण
		पूर्ण /* क्रम (cur = 1; cur <= last_pos; cur++) */

		best_mlen = opt[last_pos].mlen;
		best_off = opt[last_pos].off;
		cur = last_pos - best_mlen;

	/* store sequence */
_storeSequence: /* cur, last_pos, best_mlen, best_off have to be set */
		opt[0].mlen = 1;

		जबतक (1) अणु
			mlen = opt[cur].mlen;
			offset = opt[cur].off;
			opt[cur].mlen = best_mlen;
			opt[cur].off = best_off;
			best_mlen = mlen;
			best_off = offset;
			अगर (mlen > cur)
				अवरोध;
			cur -= mlen;
		पूर्ण

		क्रम (u = 0; u <= last_pos;) अणु
			u += opt[u].mlen;
		पूर्ण

		क्रम (cur = 0; cur < last_pos;) अणु
			mlen = opt[cur].mlen;
			अगर (mlen == 1) अणु
				ip++;
				cur++;
				जारी;
			पूर्ण
			offset = opt[cur].off;
			cur += mlen;
			litLength = (U32)(ip - anchor);

			अगर (offset > ZSTD_REP_MOVE_OPT) अणु
				rep[2] = rep[1];
				rep[1] = rep[0];
				rep[0] = offset - ZSTD_REP_MOVE_OPT;
				offset--;
			पूर्ण अन्यथा अणु
				अगर (offset != 0) अणु
					best_off = (offset == ZSTD_REP_MOVE_OPT) ? (rep[0] - 1) : (rep[offset]);
					अगर (offset != 1)
						rep[2] = rep[1];
					rep[1] = rep[0];
					rep[0] = best_off;
				पूर्ण

				अगर (litLength == 0)
					offset--;
			पूर्ण

			ZSTD_updatePrice(seqStorePtr, litLength, anchor, offset, mlen - MINMATCH);
			ZSTD_storeSeq(seqStorePtr, litLength, anchor, offset, mlen - MINMATCH);
			anchor = ip = ip + mlen;
		पूर्ण
	पूर्ण /* क्रम (cur=0; cur < last_pos; ) */

	/* Save reps क्रम next block */
	अणु
		पूर्णांक i;
		क्रम (i = 0; i < ZSTD_REP_NUM; i++)
			ctx->repToConfirm[i] = rep[i];
	पूर्ण

	/* Last Literals */
	अणु
		माप_प्रकार lastLLSize = iend - anchor;
		स_नकल(seqStorePtr->lit, anchor, lastLLSize);
		seqStorePtr->lit += lastLLSize;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* ZSTD_OPT_H_91842398743 */
