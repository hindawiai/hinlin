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
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/unaligned.h>

/*-*****************************
 *	Decompression functions
 *******************************/

#घोषणा DEBUGLOG(l, ...) अणुपूर्ण	/* disabled */

#अगर_अघोषित निश्चित
#घोषणा निश्चित(condition) ((व्योम)0)
#पूर्ण_अगर

/*
 * LZ4_decompress_generic() :
 * This generic decompression function covers all use हालs.
 * It shall be instantiated several बार, using dअगरferent sets of directives.
 * Note that it is important क्रम perक्रमmance that this function really get अंतरभूतd,
 * in order to हटाओ useless branches during compilation optimization.
 */
अटल FORCE_INLINE पूर्णांक LZ4_decompress_generic(
	 स्थिर अक्षर * स्थिर src,
	 अक्षर * स्थिर dst,
	 पूर्णांक srcSize,
		/*
		 * If endOnInput == endOnInputSize,
		 * this value is `dstCapacity`
		 */
	 पूर्णांक outputSize,
	 /* endOnOutputSize, endOnInputSize */
	 endCondition_directive endOnInput,
	 /* full, partial */
	 earlyEnd_directive partialDecoding,
	 /* noDict, withPrefix64k, usingExtDict */
	 dict_directive dict,
	 /* always <= dst, == dst when no prefix */
	 स्थिर BYTE * स्थिर lowPrefix,
	 /* only अगर dict == usingExtDict */
	 स्थिर BYTE * स्थिर dictStart,
	 /* note : = 0 अगर noDict */
	 स्थिर माप_प्रकार dictSize
	 )
अणु
	स्थिर BYTE *ip = (स्थिर BYTE *) src;
	स्थिर BYTE * स्थिर iend = ip + srcSize;

	BYTE *op = (BYTE *) dst;
	BYTE * स्थिर oend = op + outputSize;
	BYTE *cpy;

	स्थिर BYTE * स्थिर dictEnd = (स्थिर BYTE *)dictStart + dictSize;
	अटल स्थिर अचिन्हित पूर्णांक inc32table[8] = अणु0, 1, 2, 1, 0, 4, 4, 4पूर्ण;
	अटल स्थिर पूर्णांक dec64table[8] = अणु0, 0, 0, -1, -4, 1, 2, 3पूर्ण;

	स्थिर पूर्णांक safeDecode = (endOnInput == endOnInputSize);
	स्थिर पूर्णांक checkOffset = ((safeDecode) && (dictSize < (पूर्णांक)(64 * KB)));

	/* Set up the "end" poपूर्णांकers क्रम the लघुcut. */
	स्थिर BYTE *स्थिर लघुiend = iend -
		(endOnInput ? 14 : 8) /*maxLL*/ - 2 /*offset*/;
	स्थिर BYTE *स्थिर लघुoend = oend -
		(endOnInput ? 14 : 8) /*maxLL*/ - 18 /*maxML*/;

	DEBUGLOG(5, "%s (srcSize:%i, dstSize:%i)", __func__,
		 srcSize, outputSize);

	/* Special हालs */
	निश्चित(lowPrefix <= op);
	निश्चित(src != शून्य);

	/* Empty output buffer */
	अगर ((endOnInput) && (unlikely(outputSize == 0)))
		वापस ((srcSize == 1) && (*ip == 0)) ? 0 : -1;

	अगर ((!endOnInput) && (unlikely(outputSize == 0)))
		वापस (*ip == 0 ? 1 : -1);

	अगर ((endOnInput) && unlikely(srcSize == 0))
		वापस -1;

	/* Main Loop : decode sequences */
	जबतक (1) अणु
		माप_प्रकार length;
		स्थिर BYTE *match;
		माप_प्रकार offset;

		/* get literal length */
		अचिन्हित पूर्णांक स्थिर token = *ip++;
		length = token>>ML_BITS;

		/* ip < iend beक्रमe the increment */
		निश्चित(!endOnInput || ip <= iend);

		/*
		 * A two-stage लघुcut क्रम the most common हाल:
		 * 1) If the literal length is 0..14, and there is enough
		 * space, enter the लघुcut and copy 16 bytes on behalf
		 * of the literals (in the fast mode, only 8 bytes can be
		 * safely copied this way).
		 * 2) Further अगर the match length is 4..18, copy 18 bytes
		 * in a similar manner; but we ensure that there's enough
		 * space in the output क्रम those 18 bytes earlier, upon
		 * entering the लघुcut (in other words, there is a
		 * combined check क्रम both stages).
		 *
		 * The & in the likely() below is पूर्णांकentionally not && so that
		 * some compilers can produce better parallelized runसमय code
		 */
		अगर ((endOnInput ? length != RUN_MASK : length <= 8)
		   /*
		    * strictly "less than" on input, to re-enter
		    * the loop with at least one byte
		    */
		   && likely((endOnInput ? ip < लघुiend : 1) &
			     (op <= लघुoend))) अणु
			/* Copy the literals */
			LZ4_स_नकल(op, ip, endOnInput ? 16 : 8);
			op += length; ip += length;

			/*
			 * The second stage:
			 * prepare क्रम match copying, decode full info.
			 * If it करोesn't work out, the info won't be wasted.
			 */
			length = token & ML_MASK; /* match length */
			offset = LZ4_पढ़ोLE16(ip);
			ip += 2;
			match = op - offset;
			निश्चित(match <= op); /* check overflow */

			/* Do not deal with overlapping matches. */
			अगर ((length != ML_MASK) &&
			    (offset >= 8) &&
			    (dict == withPrefix64k || match >= lowPrefix)) अणु
				/* Copy the match. */
				LZ4_स_नकल(op + 0, match + 0, 8);
				LZ4_स_नकल(op + 8, match + 8, 8);
				LZ4_स_नकल(op + 16, match + 16, 2);
				op += length + MINMATCH;
				/* Both stages worked, load the next token. */
				जारी;
			पूर्ण

			/*
			 * The second stage didn't work out, but the info
			 * is पढ़ोy. Propel it right to the poपूर्णांक of match
			 * copying.
			 */
			जाओ _copy_match;
		पूर्ण

		/* decode literal length */
		अगर (length == RUN_MASK) अणु
			अचिन्हित पूर्णांक s;

			अगर (unlikely(endOnInput ? ip >= iend - RUN_MASK : 0)) अणु
				/* overflow detection */
				जाओ _output_error;
			पूर्ण
			करो अणु
				s = *ip++;
				length += s;
			पूर्ण जबतक (likely(endOnInput
				? ip < iend - RUN_MASK
				: 1) & (s == 255));

			अगर ((safeDecode)
			    && unlikely((uptrval)(op) +
					length < (uptrval)(op))) अणु
				/* overflow detection */
				जाओ _output_error;
			पूर्ण
			अगर ((safeDecode)
			    && unlikely((uptrval)(ip) +
					length < (uptrval)(ip))) अणु
				/* overflow detection */
				जाओ _output_error;
			पूर्ण
		पूर्ण

		/* copy literals */
		cpy = op + length;
		LZ4_STATIC_ASSERT(MFLIMIT >= WILDCOPYLENGTH);

		अगर (((endOnInput) && ((cpy > oend - MFLIMIT)
			|| (ip + length > iend - (2 + 1 + LASTLITERALS))))
			|| ((!endOnInput) && (cpy > oend - WILDCOPYLENGTH))) अणु
			अगर (partialDecoding) अणु
				अगर (cpy > oend) अणु
					/*
					 * Partial decoding :
					 * stop in the middle of literal segment
					 */
					cpy = oend;
					length = oend - op;
				पूर्ण
				अगर ((endOnInput)
					&& (ip + length > iend)) अणु
					/*
					 * Error :
					 * पढ़ो attempt beyond
					 * end of input buffer
					 */
					जाओ _output_error;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर ((!endOnInput)
					&& (cpy != oend)) अणु
					/*
					 * Error :
					 * block decoding must
					 * stop exactly there
					 */
					जाओ _output_error;
				पूर्ण
				अगर ((endOnInput)
					&& ((ip + length != iend)
					|| (cpy > oend))) अणु
					/*
					 * Error :
					 * input must be consumed
					 */
					जाओ _output_error;
				पूर्ण
			पूर्ण

			/*
			 * supports overlapping memory regions; only matters
			 * क्रम in-place decompression scenarios
			 */
			LZ4_स_हटाओ(op, ip, length);
			ip += length;
			op += length;

			/* Necessarily खातापूर्ण, due to parsing restrictions */
			अगर (!partialDecoding || (cpy == oend))
				अवरोध;
		पूर्ण अन्यथा अणु
			/* may overग_लिखो up to WILDCOPYLENGTH beyond cpy */
			LZ4_wildCopy(op, ip, cpy);
			ip += length;
			op = cpy;
		पूर्ण

		/* get offset */
		offset = LZ4_पढ़ोLE16(ip);
		ip += 2;
		match = op - offset;

		/* get matchlength */
		length = token & ML_MASK;

_copy_match:
		अगर ((checkOffset) && (unlikely(match + dictSize < lowPrefix))) अणु
			/* Error : offset outside buffers */
			जाओ _output_error;
		पूर्ण

		/* costs ~1%; silence an msan warning when offset == 0 */
		/*
		 * note : when partialDecoding, there is no guarantee that
		 * at least 4 bytes reमुख्य available in output buffer
		 */
		अगर (!partialDecoding) अणु
			निश्चित(oend > op);
			निश्चित(oend - op >= 4);

			LZ4_ग_लिखो32(op, (U32)offset);
		पूर्ण

		अगर (length == ML_MASK) अणु
			अचिन्हित पूर्णांक s;

			करो अणु
				s = *ip++;

				अगर ((endOnInput) && (ip > iend - LASTLITERALS))
					जाओ _output_error;

				length += s;
			पूर्ण जबतक (s == 255);

			अगर ((safeDecode)
				&& unlikely(
					(uptrval)(op) + length < (uptrval)op)) अणु
				/* overflow detection */
				जाओ _output_error;
			पूर्ण
		पूर्ण

		length += MINMATCH;

		/* match starting within बाह्यal dictionary */
		अगर ((dict == usingExtDict) && (match < lowPrefix)) अणु
			अगर (unlikely(op + length > oend - LASTLITERALS)) अणु
				/* करोesn't respect parsing restriction */
				अगर (!partialDecoding)
					जाओ _output_error;
				length = min(length, (माप_प्रकार)(oend - op));
			पूर्ण

			अगर (length <= (माप_प्रकार)(lowPrefix - match)) अणु
				/*
				 * match fits entirely within बाह्यal
				 * dictionary : just copy
				 */
				स_हटाओ(op, dictEnd - (lowPrefix - match),
					length);
				op += length;
			पूर्ण अन्यथा अणु
				/*
				 * match stretches पूर्णांकo both बाह्यal
				 * dictionary and current block
				 */
				माप_प्रकार स्थिर copySize = (माप_प्रकार)(lowPrefix - match);
				माप_प्रकार स्थिर restSize = length - copySize;

				LZ4_स_नकल(op, dictEnd - copySize, copySize);
				op += copySize;
				अगर (restSize > (माप_प्रकार)(op - lowPrefix)) अणु
					/* overlap copy */
					BYTE * स्थिर endOfMatch = op + restSize;
					स्थिर BYTE *copyFrom = lowPrefix;

					जबतक (op < endOfMatch)
						*op++ = *copyFrom++;
				पूर्ण अन्यथा अणु
					LZ4_स_नकल(op, lowPrefix, restSize);
					op += restSize;
				पूर्ण
			पूर्ण
			जारी;
		पूर्ण

		/* copy match within block */
		cpy = op + length;

		/*
		 * partialDecoding :
		 * may not respect endBlock parsing restrictions
		 */
		निश्चित(op <= oend);
		अगर (partialDecoding &&
		    (cpy > oend - MATCH_SAFEGUARD_DISTANCE)) अणु
			माप_प्रकार स्थिर mlen = min(length, (माप_प्रकार)(oend - op));
			स्थिर BYTE * स्थिर matchEnd = match + mlen;
			BYTE * स्थिर copyEnd = op + mlen;

			अगर (matchEnd > op) अणु
				/* overlap copy */
				जबतक (op < copyEnd)
					*op++ = *match++;
			पूर्ण अन्यथा अणु
				LZ4_स_नकल(op, match, mlen);
			पूर्ण
			op = copyEnd;
			अगर (op == oend)
				अवरोध;
			जारी;
		पूर्ण

		अगर (unlikely(offset < 8)) अणु
			op[0] = match[0];
			op[1] = match[1];
			op[2] = match[2];
			op[3] = match[3];
			match += inc32table[offset];
			LZ4_स_नकल(op + 4, match, 4);
			match -= dec64table[offset];
		पूर्ण अन्यथा अणु
			LZ4_copy8(op, match);
			match += 8;
		पूर्ण

		op += 8;

		अगर (unlikely(cpy > oend - MATCH_SAFEGUARD_DISTANCE)) अणु
			BYTE * स्थिर oCopyLimit = oend - (WILDCOPYLENGTH - 1);

			अगर (cpy > oend - LASTLITERALS) अणु
				/*
				 * Error : last LASTLITERALS bytes
				 * must be literals (uncompressed)
				 */
				जाओ _output_error;
			पूर्ण

			अगर (op < oCopyLimit) अणु
				LZ4_wildCopy(op, match, oCopyLimit);
				match += oCopyLimit - op;
				op = oCopyLimit;
			पूर्ण
			जबतक (op < cpy)
				*op++ = *match++;
		पूर्ण अन्यथा अणु
			LZ4_copy8(op, match);
			अगर (length > 16)
				LZ4_wildCopy(op + 8, match + 8, cpy);
		पूर्ण
		op = cpy; /* wildcopy correction */
	पूर्ण

	/* end of decoding */
	अगर (endOnInput) अणु
		/* Nb of output bytes decoded */
		वापस (पूर्णांक) (((अक्षर *)op) - dst);
	पूर्ण अन्यथा अणु
		/* Nb of input bytes पढ़ो */
		वापस (पूर्णांक) (((स्थिर अक्षर *)ip) - src);
	पूर्ण

	/* Overflow error detected */
_output_error:
	वापस (पूर्णांक) (-(((स्थिर अक्षर *)ip) - src)) - 1;
पूर्ण

पूर्णांक LZ4_decompress_safe(स्थिर अक्षर *source, अक्षर *dest,
	पूर्णांक compressedSize, पूर्णांक maxDecompressedSize)
अणु
	वापस LZ4_decompress_generic(source, dest,
				      compressedSize, maxDecompressedSize,
				      endOnInputSize, decode_full_block,
				      noDict, (BYTE *)dest, शून्य, 0);
पूर्ण

पूर्णांक LZ4_decompress_safe_partial(स्थिर अक्षर *src, अक्षर *dst,
	पूर्णांक compressedSize, पूर्णांक targetOutputSize, पूर्णांक dstCapacity)
अणु
	dstCapacity = min(targetOutputSize, dstCapacity);
	वापस LZ4_decompress_generic(src, dst, compressedSize, dstCapacity,
				      endOnInputSize, partial_decode,
				      noDict, (BYTE *)dst, शून्य, 0);
पूर्ण

पूर्णांक LZ4_decompress_fast(स्थिर अक्षर *source, अक्षर *dest, पूर्णांक originalSize)
अणु
	वापस LZ4_decompress_generic(source, dest, 0, originalSize,
				      endOnOutputSize, decode_full_block,
				      withPrefix64k,
				      (BYTE *)dest - 64 * KB, शून्य, 0);
पूर्ण

/* ===== Instantiate a few more decoding हालs, used more than once. ===== */

पूर्णांक LZ4_decompress_safe_withPrefix64k(स्थिर अक्षर *source, अक्षर *dest,
				      पूर्णांक compressedSize, पूर्णांक maxOutputSize)
अणु
	वापस LZ4_decompress_generic(source, dest,
				      compressedSize, maxOutputSize,
				      endOnInputSize, decode_full_block,
				      withPrefix64k,
				      (BYTE *)dest - 64 * KB, शून्य, 0);
पूर्ण

अटल पूर्णांक LZ4_decompress_safe_withSmallPrefix(स्थिर अक्षर *source, अक्षर *dest,
					       पूर्णांक compressedSize,
					       पूर्णांक maxOutputSize,
					       माप_प्रकार prefixSize)
अणु
	वापस LZ4_decompress_generic(source, dest,
				      compressedSize, maxOutputSize,
				      endOnInputSize, decode_full_block,
				      noDict,
				      (BYTE *)dest - prefixSize, शून्य, 0);
पूर्ण

पूर्णांक LZ4_decompress_safe_क्रमceExtDict(स्थिर अक्षर *source, अक्षर *dest,
				     पूर्णांक compressedSize, पूर्णांक maxOutputSize,
				     स्थिर व्योम *dictStart, माप_प्रकार dictSize)
अणु
	वापस LZ4_decompress_generic(source, dest,
				      compressedSize, maxOutputSize,
				      endOnInputSize, decode_full_block,
				      usingExtDict, (BYTE *)dest,
				      (स्थिर BYTE *)dictStart, dictSize);
पूर्ण

अटल पूर्णांक LZ4_decompress_fast_extDict(स्थिर अक्षर *source, अक्षर *dest,
				       पूर्णांक originalSize,
				       स्थिर व्योम *dictStart, माप_प्रकार dictSize)
अणु
	वापस LZ4_decompress_generic(source, dest,
				      0, originalSize,
				      endOnOutputSize, decode_full_block,
				      usingExtDict, (BYTE *)dest,
				      (स्थिर BYTE *)dictStart, dictSize);
पूर्ण

/*
 * The "double dictionary" mode, क्रम use with e.g. ring buffers: the first part
 * of the dictionary is passed as prefix, and the second via dictStart + dictSize.
 * These routines are used only once, in LZ4_decompress_*_जारी().
 */
अटल FORCE_INLINE
पूर्णांक LZ4_decompress_safe_द्विगुनDict(स्थिर अक्षर *source, अक्षर *dest,
				   पूर्णांक compressedSize, पूर्णांक maxOutputSize,
				   माप_प्रकार prefixSize,
				   स्थिर व्योम *dictStart, माप_प्रकार dictSize)
अणु
	वापस LZ4_decompress_generic(source, dest,
				      compressedSize, maxOutputSize,
				      endOnInputSize, decode_full_block,
				      usingExtDict, (BYTE *)dest - prefixSize,
				      (स्थिर BYTE *)dictStart, dictSize);
पूर्ण

अटल FORCE_INLINE
पूर्णांक LZ4_decompress_fast_द्विगुनDict(स्थिर अक्षर *source, अक्षर *dest,
				   पूर्णांक originalSize, माप_प्रकार prefixSize,
				   स्थिर व्योम *dictStart, माप_प्रकार dictSize)
अणु
	वापस LZ4_decompress_generic(source, dest,
				      0, originalSize,
				      endOnOutputSize, decode_full_block,
				      usingExtDict, (BYTE *)dest - prefixSize,
				      (स्थिर BYTE *)dictStart, dictSize);
पूर्ण

/* ===== streaming decompression functions ===== */

पूर्णांक LZ4_setStreamDecode(LZ4_streamDecode_t *LZ4_streamDecode,
	स्थिर अक्षर *dictionary, पूर्णांक dictSize)
अणु
	LZ4_streamDecode_t_पूर्णांकernal *lz4sd =
		&LZ4_streamDecode->पूर्णांकernal_करोnotuse;

	lz4sd->prefixSize = (माप_प्रकार) dictSize;
	lz4sd->prefixEnd = (स्थिर BYTE *) dictionary + dictSize;
	lz4sd->बाह्यalDict = शून्य;
	lz4sd->extDictSize	= 0;
	वापस 1;
पूर्ण

/*
 * *_जारी() :
 * These decoding functions allow decompression of multiple blocks
 * in "streaming" mode.
 * Previously decoded blocks must still be available at the memory
 * position where they were decoded.
 * If it's not possible, save the relevant part of
 * decoded data पूर्णांकo a safe buffer,
 * and indicate where it stands using LZ4_setStreamDecode()
 */
पूर्णांक LZ4_decompress_safe_जारी(LZ4_streamDecode_t *LZ4_streamDecode,
	स्थिर अक्षर *source, अक्षर *dest, पूर्णांक compressedSize, पूर्णांक maxOutputSize)
अणु
	LZ4_streamDecode_t_पूर्णांकernal *lz4sd =
		&LZ4_streamDecode->पूर्णांकernal_करोnotuse;
	पूर्णांक result;

	अगर (lz4sd->prefixSize == 0) अणु
		/* The first call, no dictionary yet. */
		निश्चित(lz4sd->extDictSize == 0);
		result = LZ4_decompress_safe(source, dest,
			compressedSize, maxOutputSize);
		अगर (result <= 0)
			वापस result;
		lz4sd->prefixSize = result;
		lz4sd->prefixEnd = (BYTE *)dest + result;
	पूर्ण अन्यथा अगर (lz4sd->prefixEnd == (BYTE *)dest) अणु
		/* They're rolling the current segment. */
		अगर (lz4sd->prefixSize >= 64 * KB - 1)
			result = LZ4_decompress_safe_withPrefix64k(source, dest,
				compressedSize, maxOutputSize);
		अन्यथा अगर (lz4sd->extDictSize == 0)
			result = LZ4_decompress_safe_withSmallPrefix(source,
				dest, compressedSize, maxOutputSize,
				lz4sd->prefixSize);
		अन्यथा
			result = LZ4_decompress_safe_द्विगुनDict(source, dest,
				compressedSize, maxOutputSize,
				lz4sd->prefixSize,
				lz4sd->बाह्यalDict, lz4sd->extDictSize);
		अगर (result <= 0)
			वापस result;
		lz4sd->prefixSize += result;
		lz4sd->prefixEnd  += result;
	पूर्ण अन्यथा अणु
		/*
		 * The buffer wraps around, or they're
		 * चयनing to another buffer.
		 */
		lz4sd->extDictSize = lz4sd->prefixSize;
		lz4sd->बाह्यalDict = lz4sd->prefixEnd - lz4sd->extDictSize;
		result = LZ4_decompress_safe_क्रमceExtDict(source, dest,
			compressedSize, maxOutputSize,
			lz4sd->बाह्यalDict, lz4sd->extDictSize);
		अगर (result <= 0)
			वापस result;
		lz4sd->prefixSize = result;
		lz4sd->prefixEnd  = (BYTE *)dest + result;
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक LZ4_decompress_fast_जारी(LZ4_streamDecode_t *LZ4_streamDecode,
	स्थिर अक्षर *source, अक्षर *dest, पूर्णांक originalSize)
अणु
	LZ4_streamDecode_t_पूर्णांकernal *lz4sd = &LZ4_streamDecode->पूर्णांकernal_करोnotuse;
	पूर्णांक result;

	अगर (lz4sd->prefixSize == 0) अणु
		निश्चित(lz4sd->extDictSize == 0);
		result = LZ4_decompress_fast(source, dest, originalSize);
		अगर (result <= 0)
			वापस result;
		lz4sd->prefixSize = originalSize;
		lz4sd->prefixEnd = (BYTE *)dest + originalSize;
	पूर्ण अन्यथा अगर (lz4sd->prefixEnd == (BYTE *)dest) अणु
		अगर (lz4sd->prefixSize >= 64 * KB - 1 ||
		    lz4sd->extDictSize == 0)
			result = LZ4_decompress_fast(source, dest,
						     originalSize);
		अन्यथा
			result = LZ4_decompress_fast_द्विगुनDict(source, dest,
				originalSize, lz4sd->prefixSize,
				lz4sd->बाह्यalDict, lz4sd->extDictSize);
		अगर (result <= 0)
			वापस result;
		lz4sd->prefixSize += originalSize;
		lz4sd->prefixEnd  += originalSize;
	पूर्ण अन्यथा अणु
		lz4sd->extDictSize = lz4sd->prefixSize;
		lz4sd->बाह्यalDict = lz4sd->prefixEnd - lz4sd->extDictSize;
		result = LZ4_decompress_fast_extDict(source, dest,
			originalSize, lz4sd->बाह्यalDict, lz4sd->extDictSize);
		अगर (result <= 0)
			वापस result;
		lz4sd->prefixSize = originalSize;
		lz4sd->prefixEnd = (BYTE *)dest + originalSize;
	पूर्ण
	वापस result;
पूर्ण

पूर्णांक LZ4_decompress_safe_usingDict(स्थिर अक्षर *source, अक्षर *dest,
				  पूर्णांक compressedSize, पूर्णांक maxOutputSize,
				  स्थिर अक्षर *dictStart, पूर्णांक dictSize)
अणु
	अगर (dictSize == 0)
		वापस LZ4_decompress_safe(source, dest,
					   compressedSize, maxOutputSize);
	अगर (dictStart+dictSize == dest) अणु
		अगर (dictSize >= 64 * KB - 1)
			वापस LZ4_decompress_safe_withPrefix64k(source, dest,
				compressedSize, maxOutputSize);
		वापस LZ4_decompress_safe_withSmallPrefix(source, dest,
			compressedSize, maxOutputSize, dictSize);
	पूर्ण
	वापस LZ4_decompress_safe_क्रमceExtDict(source, dest,
		compressedSize, maxOutputSize, dictStart, dictSize);
पूर्ण

पूर्णांक LZ4_decompress_fast_usingDict(स्थिर अक्षर *source, अक्षर *dest,
				  पूर्णांक originalSize,
				  स्थिर अक्षर *dictStart, पूर्णांक dictSize)
अणु
	अगर (dictSize == 0 || dictStart + dictSize == dest)
		वापस LZ4_decompress_fast(source, dest, originalSize);

	वापस LZ4_decompress_fast_extDict(source, dest, originalSize,
		dictStart, dictSize);
पूर्ण

#अगर_अघोषित STATIC
EXPORT_SYMBOL(LZ4_decompress_safe);
EXPORT_SYMBOL(LZ4_decompress_safe_partial);
EXPORT_SYMBOL(LZ4_decompress_fast);
EXPORT_SYMBOL(LZ4_setStreamDecode);
EXPORT_SYMBOL(LZ4_decompress_safe_जारी);
EXPORT_SYMBOL(LZ4_decompress_fast_जारी);
EXPORT_SYMBOL(LZ4_decompress_safe_usingDict);
EXPORT_SYMBOL(LZ4_decompress_fast_usingDict);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("LZ4 decompressor");
#पूर्ण_अगर
