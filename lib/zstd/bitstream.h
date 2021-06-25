<शैली गुरु>
/*
 * bitstream
 * Part of FSE library
 * header file (to include)
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
#अगर_अघोषित BITSTREAM_H_MODULE
#घोषणा BITSTREAM_H_MODULE

/*
*  This API consists of small unitary functions, which must be अंतरभूतd क्रम best perक्रमmance.
*  Since link-समय-optimization is not available क्रम all compilers,
*  these functions are defined पूर्णांकo a .h to be included.
*/

/*-****************************************
*  Dependencies
******************************************/
#समावेश "error_private.h" /* error codes and messages */
#समावेश "mem.h"	   /* unaligned access routines */

/*=========================================
*  Target specअगरic
=========================================*/
#घोषणा STREAM_ACCUMULATOR_MIN_32 25
#घोषणा STREAM_ACCUMULATOR_MIN_64 57
#घोषणा STREAM_ACCUMULATOR_MIN ((U32)(ZSTD_32bits() ? STREAM_ACCUMULATOR_MIN_32 : STREAM_ACCUMULATOR_MIN_64))

/*-******************************************
*  bitStream encoding API (ग_लिखो क्रमward)
********************************************/
/* bitStream can mix input from multiple sources.
*  A critical property of these streams is that they encode and decode in **reverse** direction.
*  So the first bit sequence you add will be the last to be पढ़ो, like a LIFO stack.
*/
प्रकार काष्ठा अणु
	माप_प्रकार bitContainer;
	पूर्णांक bitPos;
	अक्षर *startPtr;
	अक्षर *ptr;
	अक्षर *endPtr;
पूर्ण BIT_CStream_t;

ZSTD_STATIC माप_प्रकार BIT_initCStream(BIT_CStream_t *bitC, व्योम *dstBuffer, माप_प्रकार dstCapacity);
ZSTD_STATIC व्योम BIT_addBits(BIT_CStream_t *bitC, माप_प्रकार value, अचिन्हित nbBits);
ZSTD_STATIC व्योम BIT_flushBits(BIT_CStream_t *bitC);
ZSTD_STATIC माप_प्रकार BIT_बंदCStream(BIT_CStream_t *bitC);

/* Start with initCStream, providing the size of buffer to ग_लिखो पूर्णांकo.
*  bitStream will never ग_लिखो outside of this buffer.
*  `dstCapacity` must be >= माप(bitD->bitContainer), otherwise @वापस will be an error code.
*
*  bits are first added to a local रेजिस्टर.
*  Local रेजिस्टर is माप_प्रकार, hence 64-bits on 64-bits प्रणालीs, or 32-bits on 32-bits प्रणालीs.
*  Writing data पूर्णांकo memory is an explicit operation, perक्रमmed by the flushBits function.
*  Hence keep track how many bits are potentially stored पूर्णांकo local रेजिस्टर to aव्योम रेजिस्टर overflow.
*  After a flushBits, a maximum of 7 bits might still be stored पूर्णांकo local रेजिस्टर.
*
*  Aव्योम storing elements of more than 24 bits अगर you want compatibility with 32-bits bitstream पढ़ोers.
*
*  Last operation is to बंद the bitStream.
*  The function वापसs the final size of CStream in bytes.
*  If data couldn't fit पूर्णांकo `dstBuffer`, it will वापस a 0 ( == not storable)
*/

/*-********************************************
*  bitStream decoding API (पढ़ो backward)
**********************************************/
प्रकार काष्ठा अणु
	माप_प्रकार bitContainer;
	अचिन्हित bitsConsumed;
	स्थिर अक्षर *ptr;
	स्थिर अक्षर *start;
पूर्ण BIT_DStream_t;

प्रकार क्रमागत अणु
	BIT_DStream_unfinished = 0,
	BIT_DStream_endOfBuffer = 1,
	BIT_DStream_completed = 2,
	BIT_DStream_overflow = 3
पूर्ण BIT_DStream_status; /* result of BIT_reloadDStream() */
/* 1,2,4,8 would be better क्रम biपंचांगap combinations, but slows करोwn perक्रमmance a bit ... :( */

ZSTD_STATIC माप_प्रकार BIT_initDStream(BIT_DStream_t *bitD, स्थिर व्योम *srcBuffer, माप_प्रकार srcSize);
ZSTD_STATIC माप_प्रकार BIT_पढ़ोBits(BIT_DStream_t *bitD, अचिन्हित nbBits);
ZSTD_STATIC BIT_DStream_status BIT_reloadDStream(BIT_DStream_t *bitD);
ZSTD_STATIC अचिन्हित BIT_endOfDStream(स्थिर BIT_DStream_t *bitD);

/* Start by invoking BIT_initDStream().
*  A chunk of the bitStream is then stored पूर्णांकo a local रेजिस्टर.
*  Local रेजिस्टर size is 64-bits on 64-bits प्रणालीs, 32-bits on 32-bits प्रणालीs (माप_प्रकार).
*  You can then retrieve bitFields stored पूर्णांकo the local रेजिस्टर, **in reverse order**.
*  Local रेजिस्टर is explicitly reloaded from memory by the BIT_reloadDStream() method.
*  A reload guarantee a minimum of ((8*माप(bitD->bitContainer))-7) bits when its result is BIT_DStream_unfinished.
*  Otherwise, it can be less than that, so proceed accordingly.
*  Checking अगर DStream has reached its end can be perक्रमmed with BIT_endOfDStream().
*/

/*-****************************************
*  unsafe API
******************************************/
ZSTD_STATIC व्योम BIT_addBitsFast(BIT_CStream_t *bitC, माप_प्रकार value, अचिन्हित nbBits);
/* faster, but works only अगर value is "clean", meaning all high bits above nbBits are 0 */

ZSTD_STATIC व्योम BIT_flushBitsFast(BIT_CStream_t *bitC);
/* unsafe version; करोes not check buffer overflow */

ZSTD_STATIC माप_प्रकार BIT_पढ़ोBitsFast(BIT_DStream_t *bitD, अचिन्हित nbBits);
/* faster, but works only अगर nbBits >= 1 */

/*-**************************************************************
*  Internal functions
****************************************************************/
ZSTD_STATIC अचिन्हित BIT_highbit32(रेजिस्टर U32 val) अणु वापस 31 - __builtin_clz(val); पूर्ण

/*=====    Local Constants   =====*/
अटल स्थिर अचिन्हित BIT_mask[] = अणु0,       1,       3,       7,	0xF,      0x1F,     0x3F,     0x7F,      0xFF,
				    0x1FF,   0x3FF,   0x7FF,   0xFFF,    0x1FFF,   0x3FFF,   0x7FFF,   0xFFFF,    0x1FFFF,
				    0x3FFFF, 0x7FFFF, 0xFFFFF, 0x1FFFFF, 0x3FFFFF, 0x7FFFFF, 0xFFFFFF, 0x1FFFFFF, 0x3FFFFFFपूर्ण; /* up to 26 bits */

/*-**************************************************************
*  bitStream encoding
****************************************************************/
/*! BIT_initCStream() :
 *  `dstCapacity` must be > माप(व्योम*)
 *  @वापस : 0 अगर success,
			  otherwise an error code (can be tested using ERR_isError() ) */
ZSTD_STATIC माप_प्रकार BIT_initCStream(BIT_CStream_t *bitC, व्योम *startPtr, माप_प्रकार dstCapacity)
अणु
	bitC->bitContainer = 0;
	bitC->bitPos = 0;
	bitC->startPtr = (अक्षर *)startPtr;
	bitC->ptr = bitC->startPtr;
	bitC->endPtr = bitC->startPtr + dstCapacity - माप(bitC->ptr);
	अगर (dstCapacity <= माप(bitC->ptr))
		वापस ERROR(dstSize_tooSmall);
	वापस 0;
पूर्ण

/*! BIT_addBits() :
	can add up to 26 bits पूर्णांकo `bitC`.
	Does not check क्रम रेजिस्टर overflow ! */
ZSTD_STATIC व्योम BIT_addBits(BIT_CStream_t *bitC, माप_प्रकार value, अचिन्हित nbBits)
अणु
	bitC->bitContainer |= (value & BIT_mask[nbBits]) << bitC->bitPos;
	bitC->bitPos += nbBits;
पूर्ण

/*! BIT_addBitsFast() :
 *  works only अगर `value` is _clean_, meaning all high bits above nbBits are 0 */
ZSTD_STATIC व्योम BIT_addBitsFast(BIT_CStream_t *bitC, माप_प्रकार value, अचिन्हित nbBits)
अणु
	bitC->bitContainer |= value << bitC->bitPos;
	bitC->bitPos += nbBits;
पूर्ण

/*! BIT_flushBitsFast() :
 *  unsafe version; करोes not check buffer overflow */
ZSTD_STATIC व्योम BIT_flushBitsFast(BIT_CStream_t *bitC)
अणु
	माप_प्रकार स्थिर nbBytes = bitC->bitPos >> 3;
	ZSTD_ग_लिखोLEST(bitC->ptr, bitC->bitContainer);
	bitC->ptr += nbBytes;
	bitC->bitPos &= 7;
	bitC->bitContainer >>= nbBytes * 8; /* अगर bitPos >= माप(bitContainer)*8 --> undefined behavior */
पूर्ण

/*! BIT_flushBits() :
 *  safe version; check क्रम buffer overflow, and prevents it.
 *  note : करोes not संकेत buffer overflow. This will be revealed later on using BIT_बंदCStream() */
ZSTD_STATIC व्योम BIT_flushBits(BIT_CStream_t *bitC)
अणु
	माप_प्रकार स्थिर nbBytes = bitC->bitPos >> 3;
	ZSTD_ग_लिखोLEST(bitC->ptr, bitC->bitContainer);
	bitC->ptr += nbBytes;
	अगर (bitC->ptr > bitC->endPtr)
		bitC->ptr = bitC->endPtr;
	bitC->bitPos &= 7;
	bitC->bitContainer >>= nbBytes * 8; /* अगर bitPos >= माप(bitContainer)*8 --> undefined behavior */
पूर्ण

/*! BIT_बंदCStream() :
 *  @वापस : size of CStream, in bytes,
			  or 0 अगर it could not fit पूर्णांकo dstBuffer */
ZSTD_STATIC माप_प्रकार BIT_बंदCStream(BIT_CStream_t *bitC)
अणु
	BIT_addBitsFast(bitC, 1, 1); /* endMark */
	BIT_flushBits(bitC);

	अगर (bitC->ptr >= bitC->endPtr)
		वापस 0; /* करोesn't fit within authorized budget : cancel */

	वापस (bitC->ptr - bitC->startPtr) + (bitC->bitPos > 0);
पूर्ण

/*-********************************************************
* bitStream decoding
**********************************************************/
/*! BIT_initDStream() :
*   Initialize a BIT_DStream_t.
*   `bitD` : a poपूर्णांकer to an alपढ़ोy allocated BIT_DStream_t काष्ठाure.
*   `srcSize` must be the *exact* size of the bitStream, in bytes.
*   @वापस : size of stream (== srcSize) or an errorCode अगर a problem is detected
*/
ZSTD_STATIC माप_प्रकार BIT_initDStream(BIT_DStream_t *bitD, स्थिर व्योम *srcBuffer, माप_प्रकार srcSize)
अणु
	अगर (srcSize < 1) अणु
		स_रखो(bitD, 0, माप(*bitD));
		वापस ERROR(srcSize_wrong);
	पूर्ण

	अगर (srcSize >= माप(bitD->bitContainer)) अणु /* normal हाल */
		bitD->start = (स्थिर अक्षर *)srcBuffer;
		bitD->ptr = (स्थिर अक्षर *)srcBuffer + srcSize - माप(bitD->bitContainer);
		bitD->bitContainer = ZSTD_पढ़ोLEST(bitD->ptr);
		अणु
			BYTE स्थिर lastByte = ((स्थिर BYTE *)srcBuffer)[srcSize - 1];
			bitD->bitsConsumed = lastByte ? 8 - BIT_highbit32(lastByte) : 0; /* ensures bitsConsumed is always set */
			अगर (lastByte == 0)
				वापस ERROR(GENERIC); /* endMark not present */
		पूर्ण
	पूर्ण अन्यथा अणु
		bitD->start = (स्थिर अक्षर *)srcBuffer;
		bitD->ptr = bitD->start;
		bitD->bitContainer = *(स्थिर BYTE *)(bitD->start);
		चयन (srcSize) अणु
		हाल 7: bitD->bitContainer += (माप_प्रकार)(((स्थिर BYTE *)(srcBuffer))[6]) << (माप(bitD->bitContainer) * 8 - 16);
			fallthrough;
		हाल 6: bitD->bitContainer += (माप_प्रकार)(((स्थिर BYTE *)(srcBuffer))[5]) << (माप(bitD->bitContainer) * 8 - 24);
			fallthrough;
		हाल 5: bitD->bitContainer += (माप_प्रकार)(((स्थिर BYTE *)(srcBuffer))[4]) << (माप(bitD->bitContainer) * 8 - 32);
			fallthrough;
		हाल 4: bitD->bitContainer += (माप_प्रकार)(((स्थिर BYTE *)(srcBuffer))[3]) << 24;
			fallthrough;
		हाल 3: bitD->bitContainer += (माप_प्रकार)(((स्थिर BYTE *)(srcBuffer))[2]) << 16;
			fallthrough;
		हाल 2: bitD->bitContainer += (माप_प्रकार)(((स्थिर BYTE *)(srcBuffer))[1]) << 8;
			fallthrough;
		शेष:;
		पूर्ण
		अणु
			BYTE स्थिर lastByte = ((स्थिर BYTE *)srcBuffer)[srcSize - 1];
			bitD->bitsConsumed = lastByte ? 8 - BIT_highbit32(lastByte) : 0;
			अगर (lastByte == 0)
				वापस ERROR(GENERIC); /* endMark not present */
		पूर्ण
		bitD->bitsConsumed += (U32)(माप(bitD->bitContainer) - srcSize) * 8;
	पूर्ण

	वापस srcSize;
पूर्ण

ZSTD_STATIC माप_प्रकार BIT_getUpperBits(माप_प्रकार bitContainer, U32 स्थिर start) अणु वापस bitContainer >> start; पूर्ण

ZSTD_STATIC माप_प्रकार BIT_getMiddleBits(माप_प्रकार bitContainer, U32 स्थिर start, U32 स्थिर nbBits) अणु वापस (bitContainer >> start) & BIT_mask[nbBits]; पूर्ण

ZSTD_STATIC माप_प्रकार BIT_getLowerBits(माप_प्रकार bitContainer, U32 स्थिर nbBits) अणु वापस bitContainer & BIT_mask[nbBits]; पूर्ण

/*! BIT_lookBits() :
 *  Provides next n bits from local रेजिस्टर.
 *  local रेजिस्टर is not modअगरied.
 *  On 32-bits, maxNbBits==24.
 *  On 64-bits, maxNbBits==56.
 *  @वापस : value extracted
 */
ZSTD_STATIC माप_प्रकार BIT_lookBits(स्थिर BIT_DStream_t *bitD, U32 nbBits)
अणु
	U32 स्थिर bitMask = माप(bitD->bitContainer) * 8 - 1;
	वापस ((bitD->bitContainer << (bitD->bitsConsumed & bitMask)) >> 1) >> ((bitMask - nbBits) & bitMask);
पूर्ण

/*! BIT_lookBitsFast() :
*   unsafe version; only works only अगर nbBits >= 1 */
ZSTD_STATIC माप_प्रकार BIT_lookBitsFast(स्थिर BIT_DStream_t *bitD, U32 nbBits)
अणु
	U32 स्थिर bitMask = माप(bitD->bitContainer) * 8 - 1;
	वापस (bitD->bitContainer << (bitD->bitsConsumed & bitMask)) >> (((bitMask + 1) - nbBits) & bitMask);
पूर्ण

ZSTD_STATIC व्योम BIT_skipBits(BIT_DStream_t *bitD, U32 nbBits) अणु bitD->bitsConsumed += nbBits; पूर्ण

/*! BIT_पढ़ोBits() :
 *  Read (consume) next n bits from local रेजिस्टर and update.
 *  Pay attention to not पढ़ो more than nbBits contained पूर्णांकo local रेजिस्टर.
 *  @वापस : extracted value.
 */
ZSTD_STATIC माप_प्रकार BIT_पढ़ोBits(BIT_DStream_t *bitD, U32 nbBits)
अणु
	माप_प्रकार स्थिर value = BIT_lookBits(bitD, nbBits);
	BIT_skipBits(bitD, nbBits);
	वापस value;
पूर्ण

/*! BIT_पढ़ोBitsFast() :
*   unsafe version; only works only अगर nbBits >= 1 */
ZSTD_STATIC माप_प्रकार BIT_पढ़ोBitsFast(BIT_DStream_t *bitD, U32 nbBits)
अणु
	माप_प्रकार स्थिर value = BIT_lookBitsFast(bitD, nbBits);
	BIT_skipBits(bitD, nbBits);
	वापस value;
पूर्ण

/*! BIT_reloadDStream() :
*   Refill `bitD` from buffer previously set in BIT_initDStream() .
*   This function is safe, it guarantees it will not पढ़ो beyond src buffer.
*   @वापस : status of `BIT_DStream_t` पूर्णांकernal रेजिस्टर.
			  अगर status == BIT_DStream_unfinished, पूर्णांकernal रेजिस्टर is filled with >= (माप(bitD->bitContainer)*8 - 7) bits */
ZSTD_STATIC BIT_DStream_status BIT_reloadDStream(BIT_DStream_t *bitD)
अणु
	अगर (bitD->bitsConsumed > (माप(bitD->bitContainer) * 8)) /* should not happen => corruption detected */
		वापस BIT_DStream_overflow;

	अगर (bitD->ptr >= bitD->start + माप(bitD->bitContainer)) अणु
		bitD->ptr -= bitD->bitsConsumed >> 3;
		bitD->bitsConsumed &= 7;
		bitD->bitContainer = ZSTD_पढ़ोLEST(bitD->ptr);
		वापस BIT_DStream_unfinished;
	पूर्ण
	अगर (bitD->ptr == bitD->start) अणु
		अगर (bitD->bitsConsumed < माप(bitD->bitContainer) * 8)
			वापस BIT_DStream_endOfBuffer;
		वापस BIT_DStream_completed;
	पूर्ण
	अणु
		U32 nbBytes = bitD->bitsConsumed >> 3;
		BIT_DStream_status result = BIT_DStream_unfinished;
		अगर (bitD->ptr - nbBytes < bitD->start) अणु
			nbBytes = (U32)(bitD->ptr - bitD->start); /* ptr > start */
			result = BIT_DStream_endOfBuffer;
		पूर्ण
		bitD->ptr -= nbBytes;
		bitD->bitsConsumed -= nbBytes * 8;
		bitD->bitContainer = ZSTD_पढ़ोLEST(bitD->ptr); /* reminder : srcSize > माप(bitD) */
		वापस result;
	पूर्ण
पूर्ण

/*! BIT_endOfDStream() :
*   @वापस Tells अगर DStream has exactly reached its end (all bits consumed).
*/
ZSTD_STATIC अचिन्हित BIT_endOfDStream(स्थिर BIT_DStream_t *DStream)
अणु
	वापस ((DStream->ptr == DStream->start) && (DStream->bitsConsumed == माप(DStream->bitContainer) * 8));
पूर्ण

#पूर्ण_अगर /* BITSTREAM_H_MODULE */
