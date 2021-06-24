<शैली गुरु>
/*
 * FSE : Finite State Entropy codec
 * Public Prototypes declaration
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
#अगर_अघोषित FSE_H
#घोषणा FSE_H

/*-*****************************************
*  Dependencies
******************************************/
#समावेश <linux/types.h> /* माप_प्रकार, सूचक_भेद_प्रकार */

/*-*****************************************
*  FSE_PUBLIC_API : control library symbols visibility
******************************************/
#घोषणा FSE_PUBLIC_API

/*------   Version   ------*/
#घोषणा FSE_VERSION_MAJOR 0
#घोषणा FSE_VERSION_MINOR 9
#घोषणा FSE_VERSION_RELEASE 0

#घोषणा FSE_LIB_VERSION FSE_VERSION_MAJOR.FSE_VERSION_MINOR.FSE_VERSION_RELEASE
#घोषणा FSE_QUOTE(str) #str
#घोषणा FSE_EXPAND_AND_QUOTE(str) FSE_QUOTE(str)
#घोषणा FSE_VERSION_STRING FSE_EXPAND_AND_QUOTE(FSE_LIB_VERSION)

#घोषणा FSE_VERSION_NUMBER (FSE_VERSION_MAJOR * 100 * 100 + FSE_VERSION_MINOR * 100 + FSE_VERSION_RELEASE)
FSE_PUBLIC_API अचिन्हित FSE_versionNumber(व्योम); /**< library version number; to be used when checking dll version */

/*-*****************************************
*  Tool functions
******************************************/
FSE_PUBLIC_API माप_प्रकार FSE_compressBound(माप_प्रकार size); /* maximum compressed size */

/* Error Management */
FSE_PUBLIC_API अचिन्हित FSE_isError(माप_प्रकार code); /* tells अगर a वापस value is an error code */

/*-*****************************************
*  FSE detailed API
******************************************/
/*!
FSE_compress() करोes the following:
1. count symbol occurrence from source[] पूर्णांकo table count[]
2. normalize counters so that sum(count[]) == Power_of_2 (2^tableLog)
3. save normalized counters to memory buffer using ग_लिखोNCount()
4. build encoding table 'CTable' from normalized counters
5. encode the data stream using encoding table 'CTable'

FSE_decompress() करोes the following:
1. पढ़ो normalized counters with पढ़ोNCount()
2. build decoding table 'DTable' from normalized counters
3. decode the data stream using decoding table 'DTable'

The following API allows targeting specअगरic sub-functions क्रम advanced tasks.
For example, it's possible to compress several blocks using the same 'CTable',
or to save and provide normalized distribution using बाह्यal method.
*/

/* *** COMPRESSION *** */
/*! FSE_optimalTableLog():
	dynamically करोwnsize 'tableLog' when conditions are met.
	It saves CPU समय, by using smaller tables, जबतक preserving or even improving compression ratio.
	@वापस : recommended tableLog (necessarily <= 'maxTableLog') */
FSE_PUBLIC_API अचिन्हित FSE_optimalTableLog(अचिन्हित maxTableLog, माप_प्रकार srcSize, अचिन्हित maxSymbolValue);

/*! FSE_normalizeCount():
	normalize counts so that sum(count[]) == Power_of_2 (2^tableLog)
	'normalizedCounter' is a table of लघु, of minimum size (maxSymbolValue+1).
	@वापस : tableLog,
			  or an errorCode, which can be tested using FSE_isError() */
FSE_PUBLIC_API माप_प्रकार FSE_normalizeCount(लघु *normalizedCounter, अचिन्हित tableLog, स्थिर अचिन्हित *count, माप_प्रकार srcSize, अचिन्हित maxSymbolValue);

/*! FSE_NCountWriteBound():
	Provides the maximum possible size of an FSE normalized table, given 'maxSymbolValue' and 'tableLog'.
	Typically useful क्रम allocation purpose. */
FSE_PUBLIC_API माप_प्रकार FSE_NCountWriteBound(अचिन्हित maxSymbolValue, अचिन्हित tableLog);

/*! FSE_ग_लिखोNCount():
	Compactly save 'normalizedCounter' into 'buffer'.
	@वापस : size of the compressed table,
			  or an errorCode, which can be tested using FSE_isError(). */
FSE_PUBLIC_API माप_प्रकार FSE_ग_लिखोNCount(व्योम *buffer, माप_प्रकार bufferSize, स्थिर लघु *normalizedCounter, अचिन्हित maxSymbolValue, अचिन्हित tableLog);

/*! Conकाष्ठाor and Deकाष्ठाor of FSE_CTable.
	Note that FSE_CTable size depends on 'tableLog' and 'maxSymbolValue' */
प्रकार अचिन्हित FSE_CTable; /* करोn't allocate that. It's only meant to be more restrictive than व्योम* */

/*! FSE_compress_usingCTable():
	Compress `src` using `ct` पूर्णांकo `dst` which must be alपढ़ोy allocated.
	@वापस : size of compressed data (<= `dstCapacity`),
			  or 0 अगर compressed data could not fit पूर्णांकo `dst`,
			  or an errorCode, which can be tested using FSE_isError() */
FSE_PUBLIC_API माप_प्रकार FSE_compress_usingCTable(व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर FSE_CTable *ct);

/*!
Tutorial :
----------
The first step is to count all symbols. FSE_count() करोes this job very fast.
Result will be saved पूर्णांकo 'count', a table of unsigned int, which must be already allocated, and have 'maxSymbolValuePtr[0]+1' cells.
'src' is a table of bytes of size 'srcSize'. All values within 'src' MUST be <= maxSymbolValuePtr[0]
maxSymbolValuePtr[0] will be updated, with its real value (necessarily <= original value)
FSE_count() will वापस the number of occurrence of the most frequent symbol.
This can be used to know अगर there is a single symbol within 'src', and to quickly evaluate its compressibility.
If there is an error, the function will वापस an ErrorCode (which can be tested using FSE_isError()).

The next step is to normalize the frequencies.
FSE_normalizeCount() will ensure that sum of frequencies is == 2 ^'tableLog'.
It also guarantees a minimum of 1 to any Symbol with frequency >= 1.
You can use 'tableLog'==0 to mean "use default tableLog value".
If you are unsure of which tableLog value to use, you can ask FSE_optimalTableLog(),
which will provide the optimal valid tableLog given sourceSize, maxSymbolValue, and a user-defined maximum (0 means "default").

The result of FSE_normalizeCount() will be saved पूर्णांकo a table,
called 'normalizedCounter', which is a table of चिन्हित लघु.
'normalizedCounter' must be already allocated, and have at least 'maxSymbolValue+1' cells.
The वापस value is tableLog अगर everything proceeded as expected.
It is 0 अगर there is a single symbol within distribution.
If there is an error (ex: invalid tableLog value), the function will वापस an ErrorCode (which can be tested using FSE_isError()).

'normalizedCounter' can be saved in a compact manner to a memory area using FSE_ग_लिखोNCount().
'buffer' must be alपढ़ोy allocated.
For guaranteed success, buffer size must be at least FSE_headerBound().
The result of the function is the number of bytes written पूर्णांकo 'buffer'.
If there is an error, the function will वापस an ErrorCode (which can be tested using FSE_isError(); ex : buffer size too small).

'normalizedCounter' can then be used to create the compression table 'CTable'.
The space required by 'CTable' must be alपढ़ोy allocated, using FSE_createCTable().
You can then use FSE_buildCTable() to fill 'CTable'.
If there is an error, both functions will वापस an ErrorCode (which can be tested using FSE_isError()).

'CTable' can then be used to compress 'src', with FSE_compress_usingCTable().
Similar to FSE_count(), the convention is that 'src' is assumed to be a table of char of size 'srcSize'
The function वापसs the size of compressed data (without header), necessarily <= `dstCapacity`.
If it वापसs '0', compressed data could not fit into 'dst'.
If there is an error, the function will वापस an ErrorCode (which can be tested using FSE_isError()).
*/

/* *** DECOMPRESSION *** */

/*! FSE_पढ़ोNCount():
	Read compactly saved 'normalizedCounter' from 'rBuffer'.
	@वापस : size पढ़ो from 'rBuffer',
			  or an errorCode, which can be tested using FSE_isError().
			  maxSymbolValuePtr[0] and tableLogPtr[0] will also be updated with their respective values */
FSE_PUBLIC_API माप_प्रकार FSE_पढ़ोNCount(लघु *normalizedCounter, अचिन्हित *maxSymbolValuePtr, अचिन्हित *tableLogPtr, स्थिर व्योम *rBuffer, माप_प्रकार rBuffSize);

/*! Conकाष्ठाor and Deकाष्ठाor of FSE_DTable.
	Note that its size depends on 'tableLog' */
प्रकार अचिन्हित FSE_DTable; /* करोn't allocate that. It's just a way to be more restrictive than व्योम* */

/*! FSE_buildDTable():
	Builds 'dt', which must be alपढ़ोy allocated, using FSE_createDTable().
	वापस : 0, or an errorCode, which can be tested using FSE_isError() */
FSE_PUBLIC_API माप_प्रकार FSE_buildDTable_wksp(FSE_DTable *dt, स्थिर लघु *normalizedCounter, अचिन्हित maxSymbolValue, अचिन्हित tableLog, व्योम *workspace, माप_प्रकार workspaceSize);

/*! FSE_decompress_usingDTable():
	Decompress compressed source `cSrc` of size `cSrcSize` using `dt`
	पूर्णांकo `dst` which must be alपढ़ोy allocated.
	@वापस : size of regenerated data (necessarily <= `dstCapacity`),
			  or an errorCode, which can be tested using FSE_isError() */
FSE_PUBLIC_API माप_प्रकार FSE_decompress_usingDTable(व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर FSE_DTable *dt);

/*!
Tutorial :
----------
(Note : these functions only decompress FSE-compressed blocks.
 If block is uncompressed, use स_नकल() instead
 If block is a single repeated byte, use स_रखो() instead )

The first step is to obtain the normalized frequencies of symbols.
This can be perक्रमmed by FSE_पढ़ोNCount() अगर it was saved using FSE_ग_लिखोNCount().
'normalizedCounter' must be already allocated, and have at least 'maxSymbolValuePtr[0]+1' cells of चिन्हित लघु.
In practice, that means it's necessary to know 'maxSymbolValue' beक्रमehand,
or size the table to handle worst हाल situations (typically 256).
FSE_पढ़ोNCount() will provide 'tableLog' and 'maxSymbolValue'.
The result of FSE_पढ़ोNCount() is the number of bytes पढ़ो from 'rBuffer'.
Note that 'rBufferSize' must be at least 4 bytes, even अगर useful inक्रमmation is less than that.
If there is an error, the function will वापस an error code, which can be tested using FSE_isError().

The next step is to build the decompression tables 'FSE_DTable' from 'normalizedCounter'.
This is perक्रमmed by the function FSE_buildDTable().
The space required by 'FSE_DTable' must be alपढ़ोy allocated using FSE_createDTable().
If there is an error, the function will वापस an error code, which can be tested using FSE_isError().

`FSE_DTable` can then be used to decompress `cSrc`, with FSE_decompress_usingDTable().
`cSrcSize` must be strictly correct, otherwise decompression will fail.
FSE_decompress_usingDTable() result will tell how many bytes were regenerated (<=`dstCapacity`).
If there is an error, the function will वापस an error code, which can be tested using FSE_isError(). (ex: dst buffer too small)
*/

/* *** Dependency *** */
#समावेश "bitstream.h"

/* *****************************************
*  Static allocation
*******************************************/
/* FSE buffer bounds */
#घोषणा FSE_NCOUNTBOUND 512
#घोषणा FSE_BLOCKBOUND(size) (size + (size >> 7))
#घोषणा FSE_COMPRESSBOUND(size) (FSE_NCOUNTBOUND + FSE_BLOCKBOUND(size)) /* Macro version, useful क्रम अटल allocation */

/* It is possible to अटलally allocate FSE CTable/DTable as a table of FSE_CTable/FSE_DTable using below macros */
#घोषणा FSE_CTABLE_SIZE_U32(maxTableLog, maxSymbolValue) (1 + (1 << (maxTableLog - 1)) + ((maxSymbolValue + 1) * 2))
#घोषणा FSE_DTABLE_SIZE_U32(maxTableLog) (1 + (1 << maxTableLog))

/* *****************************************
*  FSE advanced API
*******************************************/
/* FSE_count_wksp() :
 * Same as FSE_count(), but using an बाह्यally provided scratch buffer.
 * `workSpace` size must be table of >= `1024` अचिन्हित
 */
माप_प्रकार FSE_count_wksp(अचिन्हित *count, अचिन्हित *maxSymbolValuePtr, स्थिर व्योम *source, माप_प्रकार sourceSize, अचिन्हित *workSpace);

/* FSE_countFast_wksp() :
 * Same as FSE_countFast(), but using an बाह्यally provided scratch buffer.
 * `workSpace` must be a table of minimum `1024` अचिन्हित
 */
माप_प्रकार FSE_countFast_wksp(अचिन्हित *count, अचिन्हित *maxSymbolValuePtr, स्थिर व्योम *src, माप_प्रकार srcSize, अचिन्हित *workSpace);

/*! FSE_count_simple
 * Same as FSE_countFast(), but करोes not use any additional memory (not even on stack).
 * This function is unsafe, and will segfault अगर any value within `src` is `> *maxSymbolValuePtr` (presuming it's also the size of `count`).
*/
माप_प्रकार FSE_count_simple(अचिन्हित *count, अचिन्हित *maxSymbolValuePtr, स्थिर व्योम *src, माप_प्रकार srcSize);

अचिन्हित FSE_optimalTableLog_पूर्णांकernal(अचिन्हित maxTableLog, माप_प्रकार srcSize, अचिन्हित maxSymbolValue, अचिन्हित minus);
/**< same as FSE_optimalTableLog(), which used `minus==2` */

माप_प्रकार FSE_buildCTable_raw(FSE_CTable *ct, अचिन्हित nbBits);
/**< build a fake FSE_CTable, deचिन्हित क्रम a flat distribution, where each symbol uses nbBits */

माप_प्रकार FSE_buildCTable_rle(FSE_CTable *ct, अचिन्हित अक्षर symbolValue);
/**< build a fake FSE_CTable, deचिन्हित to compress always the same symbolValue */

/* FSE_buildCTable_wksp() :
 * Same as FSE_buildCTable(), but using an बाह्यally allocated scratch buffer (`workSpace`).
 * `wkspSize` must be >= `(1<<tableLog)`.
 */
माप_प्रकार FSE_buildCTable_wksp(FSE_CTable *ct, स्थिर लघु *normalizedCounter, अचिन्हित maxSymbolValue, अचिन्हित tableLog, व्योम *workSpace, माप_प्रकार wkspSize);

माप_प्रकार FSE_buildDTable_raw(FSE_DTable *dt, अचिन्हित nbBits);
/**< build a fake FSE_DTable, deचिन्हित to पढ़ो a flat distribution where each symbol uses nbBits */

माप_प्रकार FSE_buildDTable_rle(FSE_DTable *dt, अचिन्हित अक्षर symbolValue);
/**< build a fake FSE_DTable, deचिन्हित to always generate the same symbolValue */

माप_प्रकार FSE_decompress_wksp(व्योम *dst, माप_प्रकार dstCapacity, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, अचिन्हित maxLog, व्योम *workspace, माप_प्रकार workspaceSize);
/**< same as FSE_decompress(), using an बाह्यally allocated `workSpace` produced with `FSE_DTABLE_SIZE_U32(maxLog)` */

/* *****************************************
*  FSE symbol compression API
*******************************************/
/*!
   This API consists of small unitary functions, which highly benefit from being अंतरभूतd.
   Hence their body are included in next section.
*/
प्रकार काष्ठा अणु
	सूचक_भेद_प्रकार value;
	स्थिर व्योम *stateTable;
	स्थिर व्योम *symbolTT;
	अचिन्हित stateLog;
पूर्ण FSE_CState_t;

अटल व्योम FSE_initCState(FSE_CState_t *CStatePtr, स्थिर FSE_CTable *ct);

अटल व्योम FSE_encodeSymbol(BIT_CStream_t *bitC, FSE_CState_t *CStatePtr, अचिन्हित symbol);

अटल व्योम FSE_flushCState(BIT_CStream_t *bitC, स्थिर FSE_CState_t *CStatePtr);

/**<
These functions are inner components of FSE_compress_usingCTable().
They allow the creation of custom streams, mixing multiple tables and bit sources.

A key property to keep in mind is that encoding and decoding are करोne **in reverse direction**.
So the first symbol you will encode is the last you will decode, like a LIFO stack.

You will need a few variables to track your CStream. They are :

FSE_CTable    ct;         // Provided by FSE_buildCTable()
BIT_CStream_t bitStream;  // bitStream tracking काष्ठाure
FSE_CState_t  state;      // State tracking काष्ठाure (can have several)


The first thing to करो is to init bitStream and state.
	माप_प्रकार errorCode = BIT_initCStream(&bitStream, dstBuffer, maxDstSize);
	FSE_initCState(&state, ct);

Note that BIT_initCStream() can produce an error code, so its result should be tested, using FSE_isError();
You can then encode your input data, byte after byte.
FSE_encodeSymbol() outमाला_दो a maximum of 'tableLog' bits at a समय.
Remember decoding will be करोne in reverse direction.
	FSE_encodeByte(&bitStream, &state, symbol);

At any समय, you can also add any bit sequence.
Note : maximum allowed nbBits is 25, क्रम compatibility with 32-bits decoders
	BIT_addBits(&bitStream, bitField, nbBits);

The above methods करोn't commit data to memory, they just store it पूर्णांकo local रेजिस्टर, क्रम speed.
Local रेजिस्टर size is 64-bits on 64-bits प्रणालीs, 32-bits on 32-bits प्रणालीs (माप_प्रकार).
Writing data to memory is a manual operation, perक्रमmed by the flushBits function.
	BIT_flushBits(&bitStream);

Your last FSE encoding operation shall be to flush your last state value(s).
	FSE_flushState(&bitStream, &state);

Finally, you must बंद the bitStream.
The function वापसs the size of CStream in bytes.
If data couldn't fit पूर्णांकo dstBuffer, it will वापस a 0 ( == not compressible)
If there is an error, it वापसs an errorCode (which can be tested using FSE_isError()).
	माप_प्रकार size = BIT_बंदCStream(&bitStream);
*/

/* *****************************************
*  FSE symbol decompression API
*******************************************/
प्रकार काष्ठा अणु
	माप_प्रकार state;
	स्थिर व्योम *table; /* precise table may vary, depending on U16 */
पूर्ण FSE_DState_t;

अटल व्योम FSE_initDState(FSE_DState_t *DStatePtr, BIT_DStream_t *bitD, स्थिर FSE_DTable *dt);

अटल अचिन्हित अक्षर FSE_decodeSymbol(FSE_DState_t *DStatePtr, BIT_DStream_t *bitD);

अटल अचिन्हित FSE_endOfDState(स्थिर FSE_DState_t *DStatePtr);

/**<
Let's now decompose FSE_decompress_usingDTable() पूर्णांकo its unitary components.
You will decode FSE-encoded symbols from the bitStream,
and also any other bitFields you put in, **in reverse order**.

You will need a few variables to track your bitStream. They are :

BIT_DStream_t DStream;    // Stream context
FSE_DState_t  DState;     // State context. Multiple ones are possible
FSE_DTable*   DTablePtr;  // Decoding table, provided by FSE_buildDTable()

The first thing to करो is to init the bitStream.
	errorCode = BIT_initDStream(&DStream, srcBuffer, srcSize);

You should then retrieve your initial state(s)
(in reverse flushing order अगर you have several ones) :
	errorCode = FSE_initDState(&DState, &DStream, DTablePtr);

You can then decode your data, symbol after symbol.
For inक्रमmation the maximum number of bits पढ़ो by FSE_decodeSymbol() is 'tableLog'.
Keep in mind that symbols are decoded in reverse order, like a LIFO stack (last in, first out).
	अचिन्हित अक्षर symbol = FSE_decodeSymbol(&DState, &DStream);

You can retrieve any bitfield you eventually stored पूर्णांकo the bitStream (in reverse order)
Note : maximum allowed nbBits is 25, क्रम 32-bits compatibility
	माप_प्रकार bitField = BIT_पढ़ोBits(&DStream, nbBits);

All above operations only पढ़ो from local रेजिस्टर (which size depends on माप_प्रकार).
Refueling the रेजिस्टर from memory is manually perक्रमmed by the reload method.
	endSignal = FSE_reloadDStream(&DStream);

BIT_reloadDStream() result tells अगर there is still some more data to पढ़ो from DStream.
BIT_DStream_unfinished : there is still some data left पूर्णांकo the DStream.
BIT_DStream_endOfBuffer : Dstream reached end of buffer. Its container may no दीर्घer be completely filled.
BIT_DStream_completed : Dstream reached its exact end, corresponding in general to decompression completed.
BIT_DStream_tooFar : Dstream went too far. Decompression result is corrupted.

When reaching end of buffer (BIT_DStream_endOfBuffer), progress slowly, notably अगर you decode multiple symbols per loop,
to properly detect the exact end of stream.
After each decoded symbol, check अगर DStream is fully consumed using this simple test :
	BIT_reloadDStream(&DStream) >= BIT_DStream_completed

When it's करोne, verअगरy decompression is fully completed, by checking both DStream and the relevant states.
Checking अगर DStream has reached its end is perक्रमmed by :
	BIT_endOfDStream(&DStream);
Check also the states. There might be some symbols left there, अगर some high probability ones (>50%) are possible.
	FSE_endOfDState(&DState);
*/

/* *****************************************
*  FSE unsafe API
*******************************************/
अटल अचिन्हित अक्षर FSE_decodeSymbolFast(FSE_DState_t *DStatePtr, BIT_DStream_t *bitD);
/* faster, but works only अगर nbBits is always >= 1 (otherwise, result will be corrupted) */

/* *****************************************
*  Implementation of अंतरभूतd functions
*******************************************/
प्रकार काष्ठा अणु
	पूर्णांक deltaFindState;
	U32 deltaNbBits;
पूर्ण FSE_symbolCompressionTransक्रमm; /* total 8 bytes */

ZSTD_STATIC व्योम FSE_initCState(FSE_CState_t *statePtr, स्थिर FSE_CTable *ct)
अणु
	स्थिर व्योम *ptr = ct;
	स्थिर U16 *u16ptr = (स्थिर U16 *)ptr;
	स्थिर U32 tableLog = ZSTD_पढ़ो16(ptr);
	statePtr->value = (सूचक_भेद_प्रकार)1 << tableLog;
	statePtr->stateTable = u16ptr + 2;
	statePtr->symbolTT = ((स्थिर U32 *)ct + 1 + (tableLog ? (1 << (tableLog - 1)) : 1));
	statePtr->stateLog = tableLog;
पूर्ण

/*! FSE_initCState2() :
*   Same as FSE_initCState(), but the first symbol to include (which will be the last to be पढ़ो)
*   uses the smallest state value possible, saving the cost of this symbol */
ZSTD_STATIC व्योम FSE_initCState2(FSE_CState_t *statePtr, स्थिर FSE_CTable *ct, U32 symbol)
अणु
	FSE_initCState(statePtr, ct);
	अणु
		स्थिर FSE_symbolCompressionTransक्रमm symbolTT = ((स्थिर FSE_symbolCompressionTransक्रमm *)(statePtr->symbolTT))[symbol];
		स्थिर U16 *stateTable = (स्थिर U16 *)(statePtr->stateTable);
		U32 nbBitsOut = (U32)((symbolTT.deltaNbBits + (1 << 15)) >> 16);
		statePtr->value = (nbBitsOut << 16) - symbolTT.deltaNbBits;
		statePtr->value = stateTable[(statePtr->value >> nbBitsOut) + symbolTT.deltaFindState];
	पूर्ण
पूर्ण

ZSTD_STATIC व्योम FSE_encodeSymbol(BIT_CStream_t *bitC, FSE_CState_t *statePtr, U32 symbol)
अणु
	स्थिर FSE_symbolCompressionTransक्रमm symbolTT = ((स्थिर FSE_symbolCompressionTransक्रमm *)(statePtr->symbolTT))[symbol];
	स्थिर U16 *स्थिर stateTable = (स्थिर U16 *)(statePtr->stateTable);
	U32 nbBitsOut = (U32)((statePtr->value + symbolTT.deltaNbBits) >> 16);
	BIT_addBits(bitC, statePtr->value, nbBitsOut);
	statePtr->value = stateTable[(statePtr->value >> nbBitsOut) + symbolTT.deltaFindState];
पूर्ण

ZSTD_STATIC व्योम FSE_flushCState(BIT_CStream_t *bitC, स्थिर FSE_CState_t *statePtr)
अणु
	BIT_addBits(bitC, statePtr->value, statePtr->stateLog);
	BIT_flushBits(bitC);
पूर्ण

/* ======    Decompression    ====== */

प्रकार काष्ठा अणु
	U16 tableLog;
	U16 fastMode;
पूर्ण FSE_DTableHeader; /* माप U32 */

प्रकार काष्ठा अणु
	अचिन्हित लघु newState;
	अचिन्हित अक्षर symbol;
	अचिन्हित अक्षर nbBits;
पूर्ण FSE_decode_t; /* size == U32 */

ZSTD_STATIC व्योम FSE_initDState(FSE_DState_t *DStatePtr, BIT_DStream_t *bitD, स्थिर FSE_DTable *dt)
अणु
	स्थिर व्योम *ptr = dt;
	स्थिर FSE_DTableHeader *स्थिर DTableH = (स्थिर FSE_DTableHeader *)ptr;
	DStatePtr->state = BIT_पढ़ोBits(bitD, DTableH->tableLog);
	BIT_reloadDStream(bitD);
	DStatePtr->table = dt + 1;
पूर्ण

ZSTD_STATIC BYTE FSE_peekSymbol(स्थिर FSE_DState_t *DStatePtr)
अणु
	FSE_decode_t स्थिर DInfo = ((स्थिर FSE_decode_t *)(DStatePtr->table))[DStatePtr->state];
	वापस DInfo.symbol;
पूर्ण

ZSTD_STATIC व्योम FSE_updateState(FSE_DState_t *DStatePtr, BIT_DStream_t *bitD)
अणु
	FSE_decode_t स्थिर DInfo = ((स्थिर FSE_decode_t *)(DStatePtr->table))[DStatePtr->state];
	U32 स्थिर nbBits = DInfo.nbBits;
	माप_प्रकार स्थिर lowBits = BIT_पढ़ोBits(bitD, nbBits);
	DStatePtr->state = DInfo.newState + lowBits;
पूर्ण

ZSTD_STATIC BYTE FSE_decodeSymbol(FSE_DState_t *DStatePtr, BIT_DStream_t *bitD)
अणु
	FSE_decode_t स्थिर DInfo = ((स्थिर FSE_decode_t *)(DStatePtr->table))[DStatePtr->state];
	U32 स्थिर nbBits = DInfo.nbBits;
	BYTE स्थिर symbol = DInfo.symbol;
	माप_प्रकार स्थिर lowBits = BIT_पढ़ोBits(bitD, nbBits);

	DStatePtr->state = DInfo.newState + lowBits;
	वापस symbol;
पूर्ण

/*! FSE_decodeSymbolFast() :
	unsafe, only works अगर no symbol has a probability > 50% */
ZSTD_STATIC BYTE FSE_decodeSymbolFast(FSE_DState_t *DStatePtr, BIT_DStream_t *bitD)
अणु
	FSE_decode_t स्थिर DInfo = ((स्थिर FSE_decode_t *)(DStatePtr->table))[DStatePtr->state];
	U32 स्थिर nbBits = DInfo.nbBits;
	BYTE स्थिर symbol = DInfo.symbol;
	माप_प्रकार स्थिर lowBits = BIT_पढ़ोBitsFast(bitD, nbBits);

	DStatePtr->state = DInfo.newState + lowBits;
	वापस symbol;
पूर्ण

ZSTD_STATIC अचिन्हित FSE_endOfDState(स्थिर FSE_DState_t *DStatePtr) अणु वापस DStatePtr->state == 0; पूर्ण

/* **************************************************************
*  Tuning parameters
****************************************************************/
/*!MEMORY_USAGE :
*  Memory usage क्रमmula : N->2^N Bytes (examples : 10 -> 1KB; 12 -> 4KB ; 16 -> 64KB; 20 -> 1MB; etc.)
*  Increasing memory usage improves compression ratio
*  Reduced memory usage can improve speed, due to cache effect
*  Recommended max value is 14, क्रम 16KB, which nicely fits पूर्णांकo Intel x86 L1 cache */
#अगर_अघोषित FSE_MAX_MEMORY_USAGE
#घोषणा FSE_MAX_MEMORY_USAGE 14
#पूर्ण_अगर
#अगर_अघोषित FSE_DEFAULT_MEMORY_USAGE
#घोषणा FSE_DEFAULT_MEMORY_USAGE 13
#पूर्ण_अगर

/*!FSE_MAX_SYMBOL_VALUE :
*  Maximum symbol value authorized.
*  Required क्रम proper stack allocation */
#अगर_अघोषित FSE_MAX_SYMBOL_VALUE
#घोषणा FSE_MAX_SYMBOL_VALUE 255
#पूर्ण_अगर

/* **************************************************************
*  ढाँचा functions type & suffix
****************************************************************/
#घोषणा FSE_FUNCTION_TYPE BYTE
#घोषणा FSE_FUNCTION_EXTENSION
#घोषणा FSE_DECODE_TYPE FSE_decode_t

/* ***************************************************************
*  Constants
*****************************************************************/
#घोषणा FSE_MAX_TABLELOG (FSE_MAX_MEMORY_USAGE - 2)
#घोषणा FSE_MAX_TABLESIZE (1U << FSE_MAX_TABLELOG)
#घोषणा FSE_MAXTABLESIZE_MASK (FSE_MAX_TABLESIZE - 1)
#घोषणा FSE_DEFAULT_TABLELOG (FSE_DEFAULT_MEMORY_USAGE - 2)
#घोषणा FSE_MIN_TABLELOG 5

#घोषणा FSE_TABLELOG_ABSOLUTE_MAX 15
#अगर FSE_MAX_TABLELOG > FSE_TABLELOG_ABSOLUTE_MAX
#त्रुटि "FSE_MAX_TABLELOG > FSE_TABLELOG_ABSOLUTE_MAX is not supported"
#पूर्ण_अगर

#घोषणा FSE_TABLESTEP(tableSize) ((tableSize >> 1) + (tableSize >> 3) + 3)

#पूर्ण_अगर /* FSE_H */
