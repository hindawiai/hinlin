<शैली गुरु>
/* zlib.h -- पूर्णांकerface of the 'zlib' general purpose compression library

  Copyright (C) 1995-2005 Jean-loup Gailly and Mark Adler

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable क्रम any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software क्रम any purpose,
  including commercial applications, and to alter it and redistribute it
  मुक्तly, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product करोcumentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be हटाओd or altered from any source distribution.

  Jean-loup Gailly        Mark Adler
  jloup@gzip.org          madler@alumni.caltech.edu


  The data क्रमmat used by the zlib library is described by RFCs (Request क्रम
  Comments) 1950 to 1952 in the files https://www.ietf.org/rfc/rfc1950.txt
  (zlib क्रमmat), rfc1951.txt (deflate क्रमmat) and rfc1952.txt (gzip क्रमmat).
*/

#अगर_अघोषित _ZLIB_H
#घोषणा _ZLIB_H

#समावेश <linux/zconf.h>

/* zlib deflate based on ZLIB_VERSION "1.1.3" */
/* zlib inflate based on ZLIB_VERSION "1.2.3" */

/*
  This is a modअगरied version of zlib क्रम use inside the Linux kernel.
  The मुख्य changes are to perक्रमm all memory allocation in advance.

  Inflation Changes:
    * Z_PACKET_FLUSH is added and used by ppp_deflate. Beक्रमe वापसing
      this checks there is no more input data available and the next data
      is a STORED block. It also resets the mode to be पढ़ो क्रम the next
      data, all as per PPP requirements.
    * Addition of zlib_inflateIncomp which copies incompressible data पूर्णांकo
      the history winकरोw and adjusts the accoutning without calling
      zlib_inflate itself to inflate the data.
*/

/* 
     The 'zlib' compression library provides in-memory compression and
  decompression functions, including पूर्णांकegrity checks of the uncompressed
  data.  This version of the library supports only one compression method
  (deflation) but other algorithms will be added later and will have the same
  stream पूर्णांकerface.

     Compression can be करोne in a single step अगर the buffers are large
  enough (क्रम example अगर an input file is mmap'ed), or can be करोne by
  repeated calls of the compression function.  In the latter हाल, the
  application must provide more input and/or consume the output
  (providing more output space) beक्रमe each call.

     The compressed data क्रमmat used by शेष by the in-memory functions is
  the zlib क्रमmat, which is a zlib wrapper करोcumented in RFC 1950, wrapped
  around a deflate stream, which is itself करोcumented in RFC 1951.

     The library also supports पढ़ोing and writing files in gzip (.gz) क्रमmat
  with an पूर्णांकerface similar to that of stdio.

     The zlib क्रमmat was deचिन्हित to be compact and fast क्रम use in memory
  and on communications channels.  The gzip क्रमmat was deचिन्हित क्रम single-
  file compression on file प्रणालीs, has a larger header than zlib to मुख्यtain
  directory inक्रमmation, and uses a dअगरferent, slower check method than zlib.

     The library करोes not install any संकेत handler. The decoder checks
  the consistency of the compressed data, so the library should never
  crash even in हाल of corrupted input.
*/

काष्ठा पूर्णांकernal_state;

प्रकार काष्ठा z_stream_s अणु
    स्थिर Byte *next_in;   /* next input byte */
	uLong avail_in;  /* number of bytes available at next_in */
    uLong    total_in;  /* total nb of input bytes पढ़ो so far */

    Byte    *next_out;  /* next output byte should be put there */
	uLong avail_out; /* reमुख्यing मुक्त space at next_out */
    uLong    total_out; /* total nb of bytes output so far */

    अक्षर     *msg;      /* last error message, शून्य अगर no error */
    काष्ठा पूर्णांकernal_state *state; /* not visible by applications */

    व्योम     *workspace; /* memory allocated क्रम this stream */

    पूर्णांक     data_type;  /* best guess about the data type: ascii or binary */
    uLong   adler;      /* adler32 value of the uncompressed data */
    uLong   reserved;   /* reserved क्रम future use */
पूर्ण z_stream;

प्रकार z_stream *z_streamp;

/*
   The application must update next_in and avail_in when avail_in has
   dropped to zero. It must update next_out and avail_out when avail_out
   has dropped to zero. The application must initialize zalloc, zमुक्त and
   opaque beक्रमe calling the init function. All other fields are set by the
   compression library and must not be updated by the application.

   The opaque value provided by the application will be passed as the first
   parameter क्रम calls of zalloc and zमुक्त. This can be useful क्रम custom
   memory management. The compression library attaches no meaning to the
   opaque value.

   zalloc must वापस शून्य अगर there is not enough memory क्रम the object.
   If zlib is used in a multi-thपढ़ोed application, zalloc and zमुक्त must be
   thपढ़ो safe.

   On 16-bit प्रणालीs, the functions zalloc and zमुक्त must be able to allocate
   exactly 65536 bytes, but will not be required to allocate more than this
   अगर the symbol MAXSEG_64K is defined (see zconf.h). WARNING: On MSDOS,
   poपूर्णांकers वापसed by zalloc क्रम objects of exactly 65536 bytes *must*
   have their offset normalized to zero. The शेष allocation function
   provided by this library ensures this (see zutil.c). To reduce memory
   requirements and aव्योम any allocation of 64K objects, at the expense of
   compression ratio, compile the library with -DMAX_WBITS=14 (see zconf.h).

   The fields total_in and total_out can be used क्रम statistics or
   progress reports. After compression, total_in holds the total size of
   the uncompressed data and may be saved क्रम use in the decompressor
   (particularly अगर the decompressor wants to decompress everything in
   a single step).
*/

                        /* स्थिरants */

#घोषणा Z_NO_FLUSH      0
#घोषणा Z_PARTIAL_FLUSH 1 /* will be हटाओd, use Z_SYNC_FLUSH instead */
#घोषणा Z_PACKET_FLUSH  2
#घोषणा Z_SYNC_FLUSH    3
#घोषणा Z_FULL_FLUSH    4
#घोषणा Z_FINISH        5
#घोषणा Z_BLOCK         6 /* Only क्रम inflate at present */
/* Allowed flush values; see deflate() and inflate() below क्रम details */

#घोषणा Z_OK            0
#घोषणा Z_STREAM_END    1
#घोषणा Z_NEED_DICT     2
#घोषणा Z_ERRNO        (-1)
#घोषणा Z_STREAM_ERROR (-2)
#घोषणा Z_DATA_ERROR   (-3)
#घोषणा Z_MEM_ERROR    (-4)
#घोषणा Z_BUF_ERROR    (-5)
#घोषणा Z_VERSION_ERROR (-6)
/* Return codes क्रम the compression/decompression functions. Negative
 * values are errors, positive values are used क्रम special but normal events.
 */

#घोषणा Z_NO_COMPRESSION         0
#घोषणा Z_BEST_SPEED             1
#घोषणा Z_BEST_COMPRESSION       9
#घोषणा Z_DEFAULT_COMPRESSION  (-1)
/* compression levels */

#घोषणा Z_FILTERED            1
#घोषणा Z_HUFFMAN_ONLY        2
#घोषणा Z_DEFAULT_STRATEGY    0
/* compression strategy; see deflateInit2() below क्रम details */

#घोषणा Z_BINARY   0
#घोषणा Z_ASCII    1
#घोषणा Z_UNKNOWN  2
/* Possible values of the data_type field */

#घोषणा Z_DEFLATED   8
/* The deflate compression method (the only one supported in this version) */

                        /* basic functions */

बाह्य पूर्णांक zlib_deflate_workspacesize (पूर्णांक winकरोwBits, पूर्णांक memLevel);
/*
   Returns the number of bytes that needs to be allocated क्रम a per-
   stream workspace with the specअगरied parameters.  A poपूर्णांकer to this
   number of bytes should be वापसed in stream->workspace beक्रमe
   you call zlib_deflateInit() or zlib_deflateInit2().  If you call
   zlib_deflateInit(), specअगरy winकरोwBits = MAX_WBITS and memLevel =
   MAX_MEM_LEVEL here.  If you call zlib_deflateInit2(), the winकरोwBits
   and memLevel parameters passed to zlib_deflateInit2() must not
   exceed those passed here.
*/

बाह्य पूर्णांक zlib_deflate_dfltcc_enabled (व्योम);
/*
   Returns 1 अगर Deflate-Conversion facility is installed and enabled,
   otherwise 0.
*/

/* 
बाह्य पूर्णांक deflateInit (z_streamp strm, पूर्णांक level);

     Initializes the पूर्णांकernal stream state क्रम compression. The fields
   zalloc, zमुक्त and opaque must be initialized beक्रमe by the caller.
   If zalloc and zमुक्त are set to शून्य, deflateInit updates them to
   use शेष allocation functions.

     The compression level must be Z_DEFAULT_COMPRESSION, or between 0 and 9:
   1 gives best speed, 9 gives best compression, 0 gives no compression at
   all (the input data is simply copied a block at a समय).
   Z_DEFAULT_COMPRESSION requests a शेष compromise between speed and
   compression (currently equivalent to level 6).

     deflateInit वापसs Z_OK अगर success, Z_MEM_ERROR अगर there was not
   enough memory, Z_STREAM_ERROR अगर level is not a valid compression level,
   Z_VERSION_ERROR अगर the zlib library version (zlib_version) is incompatible
   with the version assumed by the caller (ZLIB_VERSION).
   msg is set to null अगर there is no error message.  deflateInit करोes not
   perक्रमm any compression: this will be करोne by deflate().
*/


बाह्य पूर्णांक zlib_deflate (z_streamp strm, पूर्णांक flush);
/*
    deflate compresses as much data as possible, and stops when the input
  buffer becomes empty or the output buffer becomes full. It may पूर्णांकroduce some
  output latency (पढ़ोing input without producing any output) except when
  क्रमced to flush.

    The detailed semantics are as follows. deflate perक्रमms one or both of the
  following actions:

  - Compress more input starting at next_in and update next_in and avail_in
    accordingly. If not all input can be processed (because there is not
    enough room in the output buffer), next_in and avail_in are updated and
    processing will resume at this poपूर्णांक क्रम the next call of deflate().

  - Provide more output starting at next_out and update next_out and avail_out
    accordingly. This action is क्रमced अगर the parameter flush is non zero.
    Forcing flush frequently degrades the compression ratio, so this parameter
    should be set only when necessary (in पूर्णांकeractive applications).
    Some output may be provided even अगर flush is not set.

  Beक्रमe the call of deflate(), the application should ensure that at least
  one of the actions is possible, by providing more input and/or consuming
  more output, and updating avail_in or avail_out accordingly; avail_out
  should never be zero beक्रमe the call. The application can consume the
  compressed output when it wants, क्रम example when the output buffer is full
  (avail_out == 0), or after each call of deflate(). If deflate वापसs Z_OK
  and with zero avail_out, it must be called again after making room in the
  output buffer because there might be more output pending.

    If the parameter flush is set to Z_SYNC_FLUSH, all pending output is
  flushed to the output buffer and the output is aligned on a byte boundary, so
  that the decompressor can get all input data available so far. (In particular
  avail_in is zero after the call अगर enough output space has been provided
  beक्रमe the call.)  Flushing may degrade compression क्रम some compression
  algorithms and so it should be used only when necessary.

    If flush is set to Z_FULL_FLUSH, all output is flushed as with
  Z_SYNC_FLUSH, and the compression state is reset so that decompression can
  restart from this poपूर्णांक अगर previous compressed data has been damaged or अगर
  अक्रमom access is desired. Using Z_FULL_FLUSH too often can seriously degrade
  the compression.

    If deflate वापसs with avail_out == 0, this function must be called again
  with the same value of the flush parameter and more output space (updated
  avail_out), until the flush is complete (deflate वापसs with non-zero
  avail_out).

    If the parameter flush is set to Z_FINISH, pending input is processed,
  pending output is flushed and deflate वापसs with Z_STREAM_END अगर there
  was enough output space; अगर deflate वापसs with Z_OK, this function must be
  called again with Z_FINISH and more output space (updated avail_out) but no
  more input data, until it वापसs with Z_STREAM_END or an error. After
  deflate has वापसed Z_STREAM_END, the only possible operations on the
  stream are deflateReset or deflateEnd.
  
    Z_FINISH can be used immediately after deflateInit अगर all the compression
  is to be करोne in a single step. In this हाल, avail_out must be at least
  0.1% larger than avail_in plus 12 bytes.  If deflate करोes not वापस
  Z_STREAM_END, then it must be called again as described above.

    deflate() sets strm->adler to the adler32 checksum of all input पढ़ो
  so far (that is, total_in bytes).

    deflate() may update data_type अगर it can make a good guess about
  the input data type (Z_ASCII or Z_BINARY). In करोubt, the data is considered
  binary. This field is only क्रम inक्रमmation purposes and करोes not affect
  the compression algorithm in any manner.

    deflate() वापसs Z_OK अगर some progress has been made (more input
  processed or more output produced), Z_STREAM_END अगर all input has been
  consumed and all output has been produced (only when flush is set to
  Z_FINISH), Z_STREAM_ERROR अगर the stream state was inconsistent (क्रम example
  अगर next_in or next_out was शून्य), Z_BUF_ERROR अगर no progress is possible
  (क्रम example avail_in or avail_out was zero).
*/


बाह्य पूर्णांक zlib_deflateEnd (z_streamp strm);
/*
     All dynamically allocated data काष्ठाures क्रम this stream are मुक्तd.
   This function discards any unprocessed input and करोes not flush any
   pending output.

     deflateEnd वापसs Z_OK अगर success, Z_STREAM_ERROR अगर the
   stream state was inconsistent, Z_DATA_ERROR अगर the stream was मुक्तd
   prematurely (some input or output was discarded). In the error हाल,
   msg may be set but then poपूर्णांकs to a अटल string (which must not be
   deallocated).
*/


बाह्य पूर्णांक zlib_inflate_workspacesize (व्योम);
/*
   Returns the number of bytes that needs to be allocated क्रम a per-
   stream workspace.  A poपूर्णांकer to this number of bytes should be
   वापसed in stream->workspace beक्रमe calling zlib_inflateInit().
*/

/* 
बाह्य पूर्णांक zlib_inflateInit (z_streamp strm);

     Initializes the पूर्णांकernal stream state क्रम decompression. The fields
   next_in, avail_in, and workspace must be initialized beक्रमe by
   the caller. If next_in is not शून्य and avail_in is large enough (the exact
   value depends on the compression method), inflateInit determines the
   compression method from the zlib header and allocates all data काष्ठाures
   accordingly; otherwise the allocation will be deferred to the first call of
   inflate.  If zalloc and zमुक्त are set to शून्य, inflateInit updates them to
   use शेष allocation functions.

     inflateInit वापसs Z_OK अगर success, Z_MEM_ERROR अगर there was not enough
   memory, Z_VERSION_ERROR अगर the zlib library version is incompatible with the
   version assumed by the caller.  msg is set to null अगर there is no error
   message. inflateInit करोes not perक्रमm any decompression apart from पढ़ोing
   the zlib header अगर present: this will be करोne by inflate().  (So next_in and
   avail_in may be modअगरied, but next_out and avail_out are unchanged.)
*/


बाह्य पूर्णांक zlib_inflate (z_streamp strm, पूर्णांक flush);
/*
    inflate decompresses as much data as possible, and stops when the input
  buffer becomes empty or the output buffer becomes full. It may पूर्णांकroduce
  some output latency (पढ़ोing input without producing any output) except when
  क्रमced to flush.

  The detailed semantics are as follows. inflate perक्रमms one or both of the
  following actions:

  - Decompress more input starting at next_in and update next_in and avail_in
    accordingly. If not all input can be processed (because there is not
    enough room in the output buffer), next_in is updated and processing
    will resume at this poपूर्णांक क्रम the next call of inflate().

  - Provide more output starting at next_out and update next_out and avail_out
    accordingly.  inflate() provides as much output as possible, until there
    is no more input data or no more space in the output buffer (see below
    about the flush parameter).

  Beक्रमe the call of inflate(), the application should ensure that at least
  one of the actions is possible, by providing more input and/or consuming
  more output, and updating the next_* and avail_* values accordingly.
  The application can consume the uncompressed output when it wants, क्रम
  example when the output buffer is full (avail_out == 0), or after each
  call of inflate(). If inflate वापसs Z_OK and with zero avail_out, it
  must be called again after making room in the output buffer because there
  might be more output pending.

    The flush parameter of inflate() can be Z_NO_FLUSH, Z_SYNC_FLUSH,
  Z_FINISH, or Z_BLOCK. Z_SYNC_FLUSH requests that inflate() flush as much
  output as possible to the output buffer. Z_BLOCK requests that inflate() stop
  अगर and when it माला_लो to the next deflate block boundary. When decoding the
  zlib or gzip क्रमmat, this will cause inflate() to वापस immediately after
  the header and beक्रमe the first block. When करोing a raw inflate, inflate()
  will go ahead and process the first block, and will वापस when it माला_लो to
  the end of that block, or when it runs out of data.

    The Z_BLOCK option assists in appending to or combining deflate streams.
  Also to assist in this, on वापस inflate() will set strm->data_type to the
  number of unused bits in the last byte taken from strm->next_in, plus 64
  अगर inflate() is currently decoding the last block in the deflate stream,
  plus 128 अगर inflate() वापसed immediately after decoding an end-of-block
  code or decoding the complete header up to just beक्रमe the first byte of the
  deflate stream. The end-of-block will not be indicated until all of the
  uncompressed data from that block has been written to strm->next_out.  The
  number of unused bits may in general be greater than seven, except when
  bit 7 of data_type is set, in which हाल the number of unused bits will be
  less than eight.

    inflate() should normally be called until it वापसs Z_STREAM_END or an
  error. However अगर all decompression is to be perक्रमmed in a single step
  (a single call of inflate), the parameter flush should be set to
  Z_FINISH. In this हाल all pending input is processed and all pending
  output is flushed; avail_out must be large enough to hold all the
  uncompressed data. (The size of the uncompressed data may have been saved
  by the compressor क्रम this purpose.) The next operation on this stream must
  be inflateEnd to deallocate the decompression state. The use of Z_FINISH
  is never required, but can be used to inक्रमm inflate that a faster approach
  may be used क्रम the single inflate() call.

     In this implementation, inflate() always flushes as much output as
  possible to the output buffer, and always uses the faster approach on the
  first call. So the only effect of the flush parameter in this implementation
  is on the वापस value of inflate(), as noted below, or when it वापसs early
  because Z_BLOCK is used.

     If a preset dictionary is needed after this call (see inflateSetDictionary
  below), inflate sets strm->adler to the adler32 checksum of the dictionary
  chosen by the compressor and वापसs Z_NEED_DICT; otherwise it sets
  strm->adler to the adler32 checksum of all output produced so far (that is,
  total_out bytes) and वापसs Z_OK, Z_STREAM_END or an error code as described
  below. At the end of the stream, inflate() checks that its computed adler32
  checksum is equal to that saved by the compressor and वापसs Z_STREAM_END
  only अगर the checksum is correct.

    inflate() will decompress and check either zlib-wrapped or gzip-wrapped
  deflate data.  The header type is detected स्वतःmatically.  Any inक्रमmation
  contained in the gzip header is not retained, so applications that need that
  inक्रमmation should instead use raw inflate, see inflateInit2() below, or
  inflateBack() and perक्रमm their own processing of the gzip header and
  trailer.

    inflate() वापसs Z_OK अगर some progress has been made (more input processed
  or more output produced), Z_STREAM_END अगर the end of the compressed data has
  been reached and all uncompressed output has been produced, Z_NEED_DICT अगर a
  preset dictionary is needed at this poपूर्णांक, Z_DATA_ERROR अगर the input data was
  corrupted (input stream not conक्रमming to the zlib क्रमmat or incorrect check
  value), Z_STREAM_ERROR अगर the stream काष्ठाure was inconsistent (क्रम example
  अगर next_in or next_out was शून्य), Z_MEM_ERROR अगर there was not enough memory,
  Z_BUF_ERROR अगर no progress is possible or अगर there was not enough room in the
  output buffer when Z_FINISH is used. Note that Z_BUF_ERROR is not fatal, and
  inflate() can be called again with more input and more output space to
  जारी decompressing. If Z_DATA_ERROR is वापसed, the application may then
  call inflateSync() to look क्रम a good compression block अगर a partial recovery
  of the data is desired.
*/


बाह्य पूर्णांक zlib_inflateEnd (z_streamp strm);
/*
     All dynamically allocated data काष्ठाures क्रम this stream are मुक्तd.
   This function discards any unprocessed input and करोes not flush any
   pending output.

     inflateEnd वापसs Z_OK अगर success, Z_STREAM_ERROR अगर the stream state
   was inconsistent. In the error हाल, msg may be set but then poपूर्णांकs to a
   अटल string (which must not be deallocated).
*/

                        /* Advanced functions */

/*
    The following functions are needed only in some special applications.
*/

/*   
बाह्य पूर्णांक deflateInit2 (z_streamp strm,
                                     पूर्णांक  level,
                                     पूर्णांक  method,
                                     पूर्णांक  winकरोwBits,
                                     पूर्णांक  memLevel,
                                     पूर्णांक  strategy);

     This is another version of deflateInit with more compression options. The
   fields next_in, zalloc, zमुक्त and opaque must be initialized beक्रमe by
   the caller.

     The method parameter is the compression method. It must be Z_DEFLATED in
   this version of the library.

     The winकरोwBits parameter is the base two logarithm of the winकरोw size
   (the size of the history buffer).  It should be in the range 8..15 क्रम this
   version of the library. Larger values of this parameter result in better
   compression at the expense of memory usage. The शेष value is 15 अगर
   deflateInit is used instead.

     The memLevel parameter specअगरies how much memory should be allocated
   क्रम the पूर्णांकernal compression state. memLevel=1 uses minimum memory but
   is slow and reduces compression ratio; memLevel=9 uses maximum memory
   क्रम optimal speed. The शेष value is 8. See zconf.h क्रम total memory
   usage as a function of winकरोwBits and memLevel.

     The strategy parameter is used to tune the compression algorithm. Use the
   value Z_DEFAULT_STRATEGY क्रम normal data, Z_FILTERED क्रम data produced by a
   filter (or predictor), or Z_HUFFMAN_ONLY to क्रमce Huffman encoding only (no
   string match).  Filtered data consists mostly of small values with a
   somewhat अक्रमom distribution. In this हाल, the compression algorithm is
   tuned to compress them better. The effect of Z_FILTERED is to क्रमce more
   Huffman coding and less string matching; it is somewhat पूर्णांकermediate
   between Z_DEFAULT and Z_HUFFMAN_ONLY. The strategy parameter only affects
   the compression ratio but not the correctness of the compressed output even
   अगर it is not set appropriately.

      deflateInit2 वापसs Z_OK अगर success, Z_MEM_ERROR अगर there was not enough
   memory, Z_STREAM_ERROR अगर a parameter is invalid (such as an invalid
   method). msg is set to null अगर there is no error message.  deflateInit2 करोes
   not perक्रमm any compression: this will be करोne by deflate().
*/

बाह्य पूर्णांक zlib_deflateReset (z_streamp strm);
/*
     This function is equivalent to deflateEnd followed by deflateInit,
   but करोes not मुक्त and पुनः_स्मृतिate all the पूर्णांकernal compression state.
   The stream will keep the same compression level and any other attributes
   that may have been set by deflateInit2.

      deflateReset वापसs Z_OK अगर success, or Z_STREAM_ERROR अगर the source
   stream state was inconsistent (such as zalloc or state being शून्य).
*/

अटल अंतरभूत अचिन्हित दीर्घ deflateBound(अचिन्हित दीर्घ s)
अणु
	वापस s + ((s + 7) >> 3) + ((s + 63) >> 6) + 11;
पूर्ण

/*   
बाह्य पूर्णांक inflateInit2 (z_streamp strm, पूर्णांक  winकरोwBits);

     This is another version of inflateInit with an extra parameter. The
   fields next_in, avail_in, zalloc, zमुक्त and opaque must be initialized
   beक्रमe by the caller.

     The winकरोwBits parameter is the base two logarithm of the maximum winकरोw
   size (the size of the history buffer).  It should be in the range 8..15 क्रम
   this version of the library. The शेष value is 15 अगर inflateInit is used
   instead. winकरोwBits must be greater than or equal to the winकरोwBits value
   provided to deflateInit2() जबतक compressing, or it must be equal to 15 अगर
   deflateInit2() was not used. If a compressed stream with a larger winकरोw
   size is given as input, inflate() will वापस with the error code
   Z_DATA_ERROR instead of trying to allocate a larger winकरोw.

     winकरोwBits can also be -8..-15 क्रम raw inflate. In this हाल, -winकरोwBits
   determines the winकरोw size. inflate() will then process raw deflate data,
   not looking क्रम a zlib or gzip header, not generating a check value, and not
   looking क्रम any check values क्रम comparison at the end of the stream. This
   is क्रम use with other क्रमmats that use the deflate compressed data क्रमmat
   such as zip.  Those क्रमmats provide their own check values. If a custom
   क्रमmat is developed using the raw deflate क्रमmat क्रम compressed data, it is
   recommended that a check value such as an adler32 or a crc32 be applied to
   the uncompressed data as is करोne in the zlib, gzip, and zip क्रमmats.  For
   most applications, the zlib क्रमmat should be used as is. Note that comments
   above on the use in deflateInit2() applies to the magnitude of winकरोwBits.

     winकरोwBits can also be greater than 15 क्रम optional gzip decoding. Add
   32 to winकरोwBits to enable zlib and gzip decoding with स्वतःmatic header
   detection, or add 16 to decode only the gzip क्रमmat (the zlib क्रमmat will
   वापस a Z_DATA_ERROR).  If a gzip stream is being decoded, strm->adler is
   a crc32 instead of an adler32.

     inflateInit2 वापसs Z_OK अगर success, Z_MEM_ERROR अगर there was not enough
   memory, Z_STREAM_ERROR अगर a parameter is invalid (such as a null strm). msg
   is set to null अगर there is no error message.  inflateInit2 करोes not perक्रमm
   any decompression apart from पढ़ोing the zlib header अगर present: this will
   be करोne by inflate(). (So next_in and avail_in may be modअगरied, but next_out
   and avail_out are unchanged.)
*/

बाह्य पूर्णांक zlib_inflateReset (z_streamp strm);
/*
     This function is equivalent to inflateEnd followed by inflateInit,
   but करोes not मुक्त and पुनः_स्मृतिate all the पूर्णांकernal decompression state.
   The stream will keep attributes that may have been set by inflateInit2.

      inflateReset वापसs Z_OK अगर success, or Z_STREAM_ERROR अगर the source
   stream state was inconsistent (such as zalloc or state being शून्य).
*/

बाह्य पूर्णांक zlib_inflateIncomp (z_stream *strm);
/*
     This function adds the data at next_in (avail_in bytes) to the output
   history without perक्रमming any output.  There must be no pending output,
   and the decompressor must be expecting to see the start of a block.
   Calling this function is equivalent to decompressing a stored block
   containing the data at next_in (except that the data is not output).
*/

#घोषणा zlib_deflateInit(strm, level) \
	zlib_deflateInit2((strm), (level), Z_DEFLATED, MAX_WBITS, \
			      DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY)
#घोषणा zlib_inflateInit(strm) \
	zlib_inflateInit2((strm), DEF_WBITS)

बाह्य पूर्णांक zlib_deflateInit2(z_streamp strm, पूर्णांक  level, पूर्णांक  method,
                                      पूर्णांक winकरोwBits, पूर्णांक memLevel,
                                      पूर्णांक strategy);
बाह्य पूर्णांक zlib_inflateInit2(z_streamp strm, पूर्णांक  winकरोwBits);

#अगर !defined(_Z_UTIL_H) && !defined(NO_DUMMY_DECL)
    काष्ठा पूर्णांकernal_state अणुपूर्णांक dummy;पूर्ण; /* hack क्रम buggy compilers */
#पूर्ण_अगर

/* Utility function: initialize zlib, unpack binary blob, clean up zlib,
 * वापस len or negative error code. */
बाह्य पूर्णांक zlib_inflate_blob(व्योम *dst, अचिन्हित dst_sz, स्थिर व्योम *src, अचिन्हित src_sz);

#पूर्ण_अगर /* _ZLIB_H */
