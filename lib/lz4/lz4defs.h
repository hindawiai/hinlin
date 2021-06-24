<शैली गुरु>
#अगर_अघोषित __LZ4DEFS_H__
#घोषणा __LZ4DEFS_H__

/*
 * lz4defs.h -- common and architecture specअगरic defines क्रम the kernel usage

 * LZ4 - Fast LZ compression algorithm
 * Copyright (C) 2011-2016, Yann Collet.
 * BSD 2-Clause License (http://www.खोलोsource.org/licenses/bsd-license.php)
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

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/माला.स>	 /* स_रखो, स_नकल */

#घोषणा FORCE_INLINE __always_अंतरभूत

/*-************************************
 *	Basic Types
 **************************************/
#समावेश <linux/types.h>

प्रकार	uपूर्णांक8_t BYTE;
प्रकार uपूर्णांक16_t U16;
प्रकार uपूर्णांक32_t U32;
प्रकार	पूर्णांक32_t S32;
प्रकार uपूर्णांक64_t U64;
प्रकार uपूर्णांकptr_t uptrval;

/*-************************************
 *	Architecture specअगरics
 **************************************/
#अगर defined(CONFIG_64BIT)
#घोषणा LZ4_ARCH64 1
#अन्यथा
#घोषणा LZ4_ARCH64 0
#पूर्ण_अगर

#अगर defined(__LITTLE_ENDIAN)
#घोषणा LZ4_LITTLE_ENDIAN 1
#अन्यथा
#घोषणा LZ4_LITTLE_ENDIAN 0
#पूर्ण_अगर

/*-************************************
 *	Constants
 **************************************/
#घोषणा MINMATCH 4

#घोषणा WILDCOPYLENGTH 8
#घोषणा LASTLITERALS 5
#घोषणा MFLIMIT (WILDCOPYLENGTH + MINMATCH)
/*
 * ensure it's possible to ग_लिखो 2 x wildcopyLength
 * without overflowing output buffer
 */
#घोषणा MATCH_SAFEGUARD_DISTANCE  ((2 * WILDCOPYLENGTH) - MINMATCH)

/* Increase this value ==> compression run slower on incompressible data */
#घोषणा LZ4_SKIPTRIGGER 6

#घोषणा HASH_UNIT माप(माप_प्रकार)

#घोषणा KB (1 << 10)
#घोषणा MB (1 << 20)
#घोषणा GB (1U << 30)

#घोषणा MAXD_LOG 16
#घोषणा MAX_DISTANCE ((1 << MAXD_LOG) - 1)
#घोषणा STEPSIZE माप(माप_प्रकार)

#घोषणा ML_BITS	4
#घोषणा ML_MASK	((1U << ML_BITS) - 1)
#घोषणा RUN_BITS (8 - ML_BITS)
#घोषणा RUN_MASK ((1U << RUN_BITS) - 1)

/*-************************************
 *	Reading and writing पूर्णांकo memory
 **************************************/
अटल FORCE_INLINE U16 LZ4_पढ़ो16(स्थिर व्योम *ptr)
अणु
	वापस get_unaligned((स्थिर U16 *)ptr);
पूर्ण

अटल FORCE_INLINE U32 LZ4_पढ़ो32(स्थिर व्योम *ptr)
अणु
	वापस get_unaligned((स्थिर U32 *)ptr);
पूर्ण

अटल FORCE_INLINE माप_प्रकार LZ4_पढ़ो_ARCH(स्थिर व्योम *ptr)
अणु
	वापस get_unaligned((स्थिर माप_प्रकार *)ptr);
पूर्ण

अटल FORCE_INLINE व्योम LZ4_ग_लिखो16(व्योम *memPtr, U16 value)
अणु
	put_unaligned(value, (U16 *)memPtr);
पूर्ण

अटल FORCE_INLINE व्योम LZ4_ग_लिखो32(व्योम *memPtr, U32 value)
अणु
	put_unaligned(value, (U32 *)memPtr);
पूर्ण

अटल FORCE_INLINE U16 LZ4_पढ़ोLE16(स्थिर व्योम *memPtr)
अणु
	वापस get_unaligned_le16(memPtr);
पूर्ण

अटल FORCE_INLINE व्योम LZ4_ग_लिखोLE16(व्योम *memPtr, U16 value)
अणु
	वापस put_unaligned_le16(value, memPtr);
पूर्ण

/*
 * LZ4 relies on स_नकल with a स्थिरant size being अंतरभूतd. In मुक्तstanding
 * environments, the compiler can't assume the implementation of स_नकल() is
 * standard compliant, so apply its specialized स_नकल() inlining logic. When
 * possible, use __builtin_स_नकल() to tell the compiler to analyze स_नकल()
 * as-अगर it were standard compliant, so it can अंतरभूत it in मुक्तstanding
 * environments. This is needed when decompressing the Linux Kernel, क्रम example.
 */
#घोषणा LZ4_स_नकल(dst, src, size) __builtin_स_नकल(dst, src, size)
#घोषणा LZ4_स_हटाओ(dst, src, size) __builtin_स_हटाओ(dst, src, size)

अटल FORCE_INLINE व्योम LZ4_copy8(व्योम *dst, स्थिर व्योम *src)
अणु
#अगर LZ4_ARCH64
	U64 a = get_unaligned((स्थिर U64 *)src);

	put_unaligned(a, (U64 *)dst);
#अन्यथा
	U32 a = get_unaligned((स्थिर U32 *)src);
	U32 b = get_unaligned((स्थिर U32 *)src + 1);

	put_unaligned(a, (U32 *)dst);
	put_unaligned(b, (U32 *)dst + 1);
#पूर्ण_अगर
पूर्ण

/*
 * customized variant of स_नकल,
 * which can overग_लिखो up to 7 bytes beyond dstEnd
 */
अटल FORCE_INLINE व्योम LZ4_wildCopy(व्योम *dstPtr,
	स्थिर व्योम *srcPtr, व्योम *dstEnd)
अणु
	BYTE *d = (BYTE *)dstPtr;
	स्थिर BYTE *s = (स्थिर BYTE *)srcPtr;
	BYTE *स्थिर e = (BYTE *)dstEnd;

	करो अणु
		LZ4_copy8(d, s);
		d += 8;
		s += 8;
	पूर्ण जबतक (d < e);
पूर्ण

अटल FORCE_INLINE अचिन्हित पूर्णांक LZ4_NbCommonBytes(रेजिस्टर माप_प्रकार val)
अणु
#अगर LZ4_LITTLE_ENDIAN
	वापस __ffs(val) >> 3;
#अन्यथा
	वापस (BITS_PER_LONG - 1 - __fls(val)) >> 3;
#पूर्ण_अगर
पूर्ण

अटल FORCE_INLINE अचिन्हित पूर्णांक LZ4_count(
	स्थिर BYTE *pIn,
	स्थिर BYTE *pMatch,
	स्थिर BYTE *pInLimit)
अणु
	स्थिर BYTE *स्थिर pStart = pIn;

	जबतक (likely(pIn < pInLimit - (STEPSIZE - 1))) अणु
		माप_प्रकार स्थिर dअगरf = LZ4_पढ़ो_ARCH(pMatch) ^ LZ4_पढ़ो_ARCH(pIn);

		अगर (!dअगरf) अणु
			pIn += STEPSIZE;
			pMatch += STEPSIZE;
			जारी;
		पूर्ण

		pIn += LZ4_NbCommonBytes(dअगरf);

		वापस (अचिन्हित पूर्णांक)(pIn - pStart);
	पूर्ण

#अगर LZ4_ARCH64
	अगर ((pIn < (pInLimit - 3))
		&& (LZ4_पढ़ो32(pMatch) == LZ4_पढ़ो32(pIn))) अणु
		pIn += 4;
		pMatch += 4;
	पूर्ण
#पूर्ण_अगर

	अगर ((pIn < (pInLimit - 1))
		&& (LZ4_पढ़ो16(pMatch) == LZ4_पढ़ो16(pIn))) अणु
		pIn += 2;
		pMatch += 2;
	पूर्ण

	अगर ((pIn < pInLimit) && (*pMatch == *pIn))
		pIn++;

	वापस (अचिन्हित पूर्णांक)(pIn - pStart);
पूर्ण

प्रकार क्रमागत अणु noLimit = 0, limitedOutput = 1 पूर्ण limitedOutput_directive;
प्रकार क्रमागत अणु byPtr, byU32, byU16 पूर्ण tableType_t;

प्रकार क्रमागत अणु noDict = 0, withPrefix64k, usingExtDict पूर्ण dict_directive;
प्रकार क्रमागत अणु noDictIssue = 0, dictSmall पूर्ण dictIssue_directive;

प्रकार क्रमागत अणु endOnOutputSize = 0, endOnInputSize = 1 पूर्ण endCondition_directive;
प्रकार क्रमागत अणु decode_full_block = 0, partial_decode = 1 पूर्ण earlyEnd_directive;

#घोषणा LZ4_STATIC_ASSERT(c)	BUILD_BUG_ON(!(c))

#पूर्ण_अगर
