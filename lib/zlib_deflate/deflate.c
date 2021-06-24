<शैली गुरु>
/* +++ deflate.c */
/* deflate.c -- compress data using the deflation algorithm
 * Copyright (C) 1995-1996 Jean-loup Gailly.
 * For conditions of distribution and use, see copyright notice in zlib.h 
 */

/*
 *  ALGORITHM
 *
 *      The "deflation" process depends on being able to identअगरy portions
 *      of the input text which are identical to earlier input (within a
 *      sliding winकरोw trailing behind the input currently being processed).
 *
 *      The most straightक्रमward technique turns out to be the fastest क्रम
 *      most input files: try all possible matches and select the दीर्घest.
 *      The key feature of this algorithm is that insertions पूर्णांकo the string
 *      dictionary are very simple and thus fast, and deletions are aव्योमed
 *      completely. Insertions are perक्रमmed at each input अक्षरacter, whereas
 *      string matches are perक्रमmed only when the previous match ends. So it
 *      is preferable to spend more समय in matches to allow very fast string
 *      insertions and aव्योम deletions. The matching algorithm क्रम small
 *      strings is inspired from that of Rabin & Karp. A brute क्रमce approach
 *      is used to find दीर्घer strings when a small match has been found.
 *      A similar algorithm is used in comic (by Jan-Mark Wams) and मुक्तze
 *      (by Leonid Broukhis).
 *         A previous version of this file used a more sophisticated algorithm
 *      (by Fiala and Greene) which is guaranteed to run in linear amortized
 *      समय, but has a larger average cost, uses more memory and is patented.
 *      However the F&G algorithm may be faster क्रम some highly redundant
 *      files अगर the parameter max_chain_length (described below) is too large.
 *
 *  ACKNOWLEDGEMENTS
 *
 *      The idea of lazy evaluation of matches is due to Jan-Mark Wams, and
 *      I found it in 'freeze' written by Leonid Broukhis.
 *      Thanks to many people क्रम bug reports and testing.
 *
 *  REFERENCES
 *
 *      Deutsch, L.P.,"DEFLATE Compressed Data Format Specification".
 *      Available in ftp://ds.पूर्णांकernic.net/rfc/rfc1951.txt
 *
 *      A description of the Rabin and Karp algorithm is given in the book
 *         "Algorithms" by R. Sedgewick, Addison-Wesley, p252.
 *
 *      Fiala,E.R., and Greene,D.H.
 *         Data Compression with Finite Winकरोws, Comm.ACM, 32,4 (1989) 490-595
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/zutil.h>
#समावेश "defutil.h"

/* architecture-specअगरic bits */
#अगर_घोषित CONFIG_ZLIB_DFLTCC
#  include "../zlib_dfltcc/dfltcc.h"
#अन्यथा
#घोषणा DEFLATE_RESET_HOOK(strm) करो अणुपूर्ण जबतक (0)
#घोषणा DEFLATE_HOOK(strm, flush, bstate) 0
#घोषणा DEFLATE_NEED_CHECKSUM(strm) 1
#घोषणा DEFLATE_DFLTCC_ENABLED() 0
#पूर्ण_अगर

/* ===========================================================================
 *  Function prototypes.
 */

प्रकार block_state (*compress_func) (deflate_state *s, पूर्णांक flush);
/* Compression function. Returns the block state after the call. */

अटल व्योम fill_winकरोw    (deflate_state *s);
अटल block_state deflate_stored (deflate_state *s, पूर्णांक flush);
अटल block_state deflate_fast   (deflate_state *s, पूर्णांक flush);
अटल block_state deflate_slow   (deflate_state *s, पूर्णांक flush);
अटल व्योम lm_init        (deflate_state *s);
अटल व्योम putShortMSB    (deflate_state *s, uInt b);
अटल पूर्णांक पढ़ो_buf        (z_streamp strm, Byte *buf, अचिन्हित size);
अटल uInt दीर्घest_match  (deflate_state *s, IPos cur_match);

#अगर_घोषित DEBUG_ZLIB
अटल  व्योम check_match (deflate_state *s, IPos start, IPos match,
                         पूर्णांक length);
#पूर्ण_अगर

/* ===========================================================================
 * Local data
 */

#घोषणा NIL 0
/* Tail of hash chains */

#अगर_अघोषित TOO_FAR
#  define TOO_FAR 4096
#पूर्ण_अगर
/* Matches of length 3 are discarded अगर their distance exceeds TOO_FAR */

#घोषणा MIN_LOOKAHEAD (MAX_MATCH+MIN_MATCH+1)
/* Minimum amount of lookahead, except at the end of the input file.
 * See deflate.c क्रम comments about the MIN_MATCH+1.
 */

/* Workspace to be allocated क्रम deflate processing */
प्रकार काष्ठा deflate_workspace अणु
    /* State memory क्रम the deflator */
    deflate_state deflate_memory;
#अगर_घोषित CONFIG_ZLIB_DFLTCC
    /* State memory क्रम s390 hardware deflate */
    काष्ठा dfltcc_state dfltcc_memory;
#पूर्ण_अगर
    Byte *winकरोw_memory;
    Pos *prev_memory;
    Pos *head_memory;
    अक्षर *overlay_memory;
पूर्ण deflate_workspace;

#अगर_घोषित CONFIG_ZLIB_DFLTCC
/* dfltcc_state must be द्विगुनword aligned क्रम DFLTCC call */
अटल_निश्चित(दुरत्व(काष्ठा deflate_workspace, dfltcc_memory) % 8 == 0);
#पूर्ण_अगर

/* Values क्रम max_lazy_match, good_match and max_chain_length, depending on
 * the desired pack level (0..9). The values given below have been tuned to
 * exclude worst हाल perक्रमmance क्रम pathological files. Better values may be
 * found क्रम specअगरic files.
 */
प्रकार काष्ठा config_s अणु
   ush good_length; /* reduce lazy search above this match length */
   ush max_lazy;    /* करो not perक्रमm lazy search above this match length */
   ush nice_length; /* quit search above this match length */
   ush max_chain;
   compress_func func;
पूर्ण config;

अटल स्थिर config configuration_table[10] = अणु
/*      good lazy nice chain */
/* 0 */ अणु0,    0,  0,    0, deflate_storedपूर्ण,  /* store only */
/* 1 */ अणु4,    4,  8,    4, deflate_fastपूर्ण, /* maximum speed, no lazy matches */
/* 2 */ अणु4,    5, 16,    8, deflate_fastपूर्ण,
/* 3 */ अणु4,    6, 32,   32, deflate_fastपूर्ण,

/* 4 */ अणु4,    4, 16,   16, deflate_slowपूर्ण,  /* lazy matches */
/* 5 */ अणु8,   16, 32,   32, deflate_slowपूर्ण,
/* 6 */ अणु8,   16, 128, 128, deflate_slowपूर्ण,
/* 7 */ अणु8,   32, 128, 256, deflate_slowपूर्ण,
/* 8 */ अणु32, 128, 258, 1024, deflate_slowपूर्ण,
/* 9 */ अणु32, 258, 258, 4096, deflate_slowपूर्णपूर्ण; /* maximum compression */

/* Note: the deflate() code requires max_lazy >= MIN_MATCH and max_chain >= 4
 * For deflate_fast() (levels <= 3) good is ignored and lazy has a dअगरferent
 * meaning.
 */

#घोषणा EQUAL 0
/* result of स_भेद क्रम equal strings */

/* ===========================================================================
 * Update a hash value with the given input byte
 * IN  निश्चितion: all calls to UPDATE_HASH are made with consecutive
 *    input अक्षरacters, so that a running hash key can be computed from the
 *    previous key instead of complete recalculation each समय.
 */
#घोषणा UPDATE_HASH(s,h,c) (h = (((h)<<s->hash_shअगरt) ^ (c)) & s->hash_mask)


/* ===========================================================================
 * Insert string str in the dictionary and set match_head to the previous head
 * of the hash chain (the most recent string with same hash key). Return
 * the previous length of the hash chain.
 * IN  निश्चितion: all calls to INSERT_STRING are made with consecutive
 *    input अक्षरacters and the first MIN_MATCH bytes of str are valid
 *    (except क्रम the last MIN_MATCH-1 bytes of the input file).
 */
#घोषणा INSERT_STRING(s, str, match_head) \
   (UPDATE_HASH(s, s->ins_h, s->winकरोw[(str) + (MIN_MATCH-1)]), \
    s->prev[(str) & s->w_mask] = match_head = s->head[s->ins_h], \
    s->head[s->ins_h] = (Pos)(str))

/* ===========================================================================
 * Initialize the hash table (aव्योमing 64K overflow क्रम 16 bit प्रणालीs).
 * prev[] will be initialized on the fly.
 */
#घोषणा CLEAR_HASH(s) \
    s->head[s->hash_size-1] = NIL; \
    स_रखो((अक्षर *)s->head, 0, (अचिन्हित)(s->hash_size-1)*माप(*s->head));

/* ========================================================================= */
पूर्णांक zlib_deflateInit2(
	z_streamp strm,
	पूर्णांक  level,
	पूर्णांक  method,
	पूर्णांक  winकरोwBits,
	पूर्णांक  memLevel,
	पूर्णांक  strategy
)
अणु
    deflate_state *s;
    पूर्णांक noheader = 0;
    deflate_workspace *mem;
    अक्षर *next;

    ush *overlay;
    /* We overlay pending_buf and d_buf+l_buf. This works since the average
     * output size क्रम (length,distance) codes is <= 24 bits.
     */

    अगर (strm == शून्य) वापस Z_STREAM_ERROR;

    strm->msg = शून्य;

    अगर (level == Z_DEFAULT_COMPRESSION) level = 6;

    mem = (deflate_workspace *) strm->workspace;

    अगर (winकरोwBits < 0) अणु /* unकरोcumented feature: suppress zlib header */
        noheader = 1;
        winकरोwBits = -winकरोwBits;
    पूर्ण
    अगर (memLevel < 1 || memLevel > MAX_MEM_LEVEL || method != Z_DEFLATED ||
        winकरोwBits < 9 || winकरोwBits > 15 || level < 0 || level > 9 ||
	strategy < 0 || strategy > Z_HUFFMAN_ONLY) अणु
        वापस Z_STREAM_ERROR;
    पूर्ण

    /*
     * Direct the workspace's poपूर्णांकers to the chunks that were allocated
     * aदीर्घ with the deflate_workspace काष्ठा.
     */
    next = (अक्षर *) mem;
    next += माप(*mem);
#अगर_घोषित CONFIG_ZLIB_DFLTCC
    /*
     *  DFLTCC requires the winकरोw to be page aligned.
     *  Thus, we overallocate and take the aligned portion of the buffer.
     */
    mem->winकरोw_memory = (Byte *) PTR_ALIGN(next, PAGE_SIZE);
#अन्यथा
    mem->winकरोw_memory = (Byte *) next;
#पूर्ण_अगर
    next += zlib_deflate_winकरोw_memsize(winकरोwBits);
    mem->prev_memory = (Pos *) next;
    next += zlib_deflate_prev_memsize(winकरोwBits);
    mem->head_memory = (Pos *) next;
    next += zlib_deflate_head_memsize(memLevel);
    mem->overlay_memory = next;

    s = (deflate_state *) &(mem->deflate_memory);
    strm->state = (काष्ठा पूर्णांकernal_state *)s;
    s->strm = strm;

    s->noheader = noheader;
    s->w_bits = winकरोwBits;
    s->w_size = 1 << s->w_bits;
    s->w_mask = s->w_size - 1;

    s->hash_bits = memLevel + 7;
    s->hash_size = 1 << s->hash_bits;
    s->hash_mask = s->hash_size - 1;
    s->hash_shअगरt =  ((s->hash_bits+MIN_MATCH-1)/MIN_MATCH);

    s->winकरोw = (Byte *) mem->winकरोw_memory;
    s->prev   = (Pos *)  mem->prev_memory;
    s->head   = (Pos *)  mem->head_memory;

    s->lit_bufsize = 1 << (memLevel + 6); /* 16K elements by शेष */

    overlay = (ush *) mem->overlay_memory;
    s->pending_buf = (uch *) overlay;
    s->pending_buf_size = (ulg)s->lit_bufsize * (माप(ush)+2L);

    s->d_buf = overlay + s->lit_bufsize/माप(ush);
    s->l_buf = s->pending_buf + (1+माप(ush))*s->lit_bufsize;

    s->level = level;
    s->strategy = strategy;
    s->method = (Byte)method;

    वापस zlib_deflateReset(strm);
पूर्ण

/* ========================================================================= */
पूर्णांक zlib_deflateReset(
	z_streamp strm
)
अणु
    deflate_state *s;
    
    अगर (strm == शून्य || strm->state == शून्य)
        वापस Z_STREAM_ERROR;

    strm->total_in = strm->total_out = 0;
    strm->msg = शून्य;
    strm->data_type = Z_UNKNOWN;

    s = (deflate_state *)strm->state;
    s->pending = 0;
    s->pending_out = s->pending_buf;

    अगर (s->noheader < 0) अणु
        s->noheader = 0; /* was set to -1 by deflate(..., Z_FINISH); */
    पूर्ण
    s->status = s->noheader ? BUSY_STATE : INIT_STATE;
    strm->adler = 1;
    s->last_flush = Z_NO_FLUSH;

    zlib_tr_init(s);
    lm_init(s);

    DEFLATE_RESET_HOOK(strm);

    वापस Z_OK;
पूर्ण

/* =========================================================================
 * Put a लघु in the pending buffer. The 16-bit value is put in MSB order.
 * IN निश्चितion: the stream state is correct and there is enough room in
 * pending_buf.
 */
अटल व्योम putShortMSB(
	deflate_state *s,
	uInt b
)
अणु
    put_byte(s, (Byte)(b >> 8));
    put_byte(s, (Byte)(b & 0xff));
पूर्ण   

/* ========================================================================= */
पूर्णांक zlib_deflate(
	z_streamp strm,
	पूर्णांक flush
)
अणु
    पूर्णांक old_flush; /* value of flush param क्रम previous deflate call */
    deflate_state *s;

    अगर (strm == शून्य || strm->state == शून्य ||
	flush > Z_FINISH || flush < 0) अणु
        वापस Z_STREAM_ERROR;
    पूर्ण
    s = (deflate_state *) strm->state;

    अगर ((strm->next_in == शून्य && strm->avail_in != 0) ||
	(s->status == FINISH_STATE && flush != Z_FINISH)) अणु
        वापस Z_STREAM_ERROR;
    पूर्ण
    अगर (strm->avail_out == 0) वापस Z_BUF_ERROR;

    s->strm = strm; /* just in हाल */
    old_flush = s->last_flush;
    s->last_flush = flush;

    /* Write the zlib header */
    अगर (s->status == INIT_STATE) अणु

        uInt header = (Z_DEFLATED + ((s->w_bits-8)<<4)) << 8;
        uInt level_flags = (s->level-1) >> 1;

        अगर (level_flags > 3) level_flags = 3;
        header |= (level_flags << 6);
	अगर (s->strstart != 0) header |= PRESET_DICT;
        header += 31 - (header % 31);

        s->status = BUSY_STATE;
        putShortMSB(s, header);

	/* Save the adler32 of the preset dictionary: */
	अगर (s->strstart != 0) अणु
	    putShortMSB(s, (uInt)(strm->adler >> 16));
	    putShortMSB(s, (uInt)(strm->adler & 0xffff));
	पूर्ण
	strm->adler = 1L;
    पूर्ण

    /* Flush as much pending output as possible */
    अगर (s->pending != 0) अणु
        flush_pending(strm);
        अगर (strm->avail_out == 0) अणु
	    /* Since avail_out is 0, deflate will be called again with
	     * more output space, but possibly with both pending and
	     * avail_in equal to zero. There won't be anything to करो,
	     * but this is not an error situation so make sure we
	     * वापस OK instead of BUF_ERROR at next call of deflate:
             */
	    s->last_flush = -1;
	    वापस Z_OK;
	पूर्ण

    /* Make sure there is something to करो and aव्योम duplicate consecutive
     * flushes. For repeated and useless calls with Z_FINISH, we keep
     * वापसing Z_STREAM_END instead of Z_BUFF_ERROR.
     */
    पूर्ण अन्यथा अगर (strm->avail_in == 0 && flush <= old_flush &&
	       flush != Z_FINISH) अणु
        वापस Z_BUF_ERROR;
    पूर्ण

    /* User must not provide more input after the first FINISH: */
    अगर (s->status == FINISH_STATE && strm->avail_in != 0) अणु
        वापस Z_BUF_ERROR;
    पूर्ण

    /* Start a new block or जारी the current one.
     */
    अगर (strm->avail_in != 0 || s->lookahead != 0 ||
        (flush != Z_NO_FLUSH && s->status != FINISH_STATE)) अणु
        block_state bstate;

	bstate = DEFLATE_HOOK(strm, flush, &bstate) ? bstate :
		 (*(configuration_table[s->level].func))(s, flush);

        अगर (bstate == finish_started || bstate == finish_करोne) अणु
            s->status = FINISH_STATE;
        पूर्ण
        अगर (bstate == need_more || bstate == finish_started) अणु
	    अगर (strm->avail_out == 0) अणु
	        s->last_flush = -1; /* aव्योम BUF_ERROR next call, see above */
	    पूर्ण
	    वापस Z_OK;
	    /* If flush != Z_NO_FLUSH && avail_out == 0, the next call
	     * of deflate should use the same flush parameter to make sure
	     * that the flush is complete. So we करोn't have to output an
	     * empty block here, this will be करोne at next call. This also
	     * ensures that क्रम a very small output buffer, we emit at most
	     * one empty block.
	     */
	पूर्ण
        अगर (bstate == block_करोne) अणु
            अगर (flush == Z_PARTIAL_FLUSH) अणु
                zlib_tr_align(s);
	    पूर्ण अन्यथा अगर (flush == Z_PACKET_FLUSH) अणु
		/* Output just the 3-bit `stored' block type value,
		   but not a zero length. */
		zlib_tr_stored_type_only(s);
            पूर्ण अन्यथा अणु /* FULL_FLUSH or SYNC_FLUSH */
                zlib_tr_stored_block(s, (अक्षर*)0, 0L, 0);
                /* For a full flush, this empty block will be recognized
                 * as a special marker by inflate_sync().
                 */
                अगर (flush == Z_FULL_FLUSH) अणु
                    CLEAR_HASH(s);             /* क्रमget history */
                पूर्ण
            पूर्ण
            flush_pending(strm);
	    अगर (strm->avail_out == 0) अणु
	      s->last_flush = -1; /* aव्योम BUF_ERROR at next call, see above */
	      वापस Z_OK;
	    पूर्ण
        पूर्ण
    पूर्ण
    Assert(strm->avail_out > 0, "bug2");

    अगर (flush != Z_FINISH) वापस Z_OK;
    अगर (s->noheader) वापस Z_STREAM_END;

    /* Write the zlib trailer (adler32) */
    putShortMSB(s, (uInt)(strm->adler >> 16));
    putShortMSB(s, (uInt)(strm->adler & 0xffff));
    flush_pending(strm);
    /* If avail_out is zero, the application will call deflate again
     * to flush the rest.
     */
    s->noheader = -1; /* ग_लिखो the trailer only once! */
    वापस s->pending != 0 ? Z_OK : Z_STREAM_END;
पूर्ण

/* ========================================================================= */
पूर्णांक zlib_deflateEnd(
	z_streamp strm
)
अणु
    पूर्णांक status;
    deflate_state *s;

    अगर (strm == शून्य || strm->state == शून्य) वापस Z_STREAM_ERROR;
    s = (deflate_state *) strm->state;

    status = s->status;
    अगर (status != INIT_STATE && status != BUSY_STATE &&
	status != FINISH_STATE) अणु
      वापस Z_STREAM_ERROR;
    पूर्ण

    strm->state = शून्य;

    वापस status == BUSY_STATE ? Z_DATA_ERROR : Z_OK;
पूर्ण

/* ===========================================================================
 * Read a new buffer from the current input stream, update the adler32
 * and total number of bytes पढ़ो.  All deflate() input goes through
 * this function so some applications may wish to modअगरy it to aव्योम
 * allocating a large strm->next_in buffer and copying from it.
 * (See also flush_pending()).
 */
अटल पूर्णांक पढ़ो_buf(
	z_streamp strm,
	Byte *buf,
	अचिन्हित size
)
अणु
    अचिन्हित len = strm->avail_in;

    अगर (len > size) len = size;
    अगर (len == 0) वापस 0;

    strm->avail_in  -= len;

    अगर (!DEFLATE_NEED_CHECKSUM(strm)) अणुपूर्ण
    अन्यथा अगर (!((deflate_state *)(strm->state))->noheader) अणु
        strm->adler = zlib_adler32(strm->adler, strm->next_in, len);
    पूर्ण
    स_नकल(buf, strm->next_in, len);
    strm->next_in  += len;
    strm->total_in += len;

    वापस (पूर्णांक)len;
पूर्ण

/* ===========================================================================
 * Initialize the "longest match" routines क्रम a new zlib stream
 */
अटल व्योम lm_init(
	deflate_state *s
)
अणु
    s->winकरोw_size = (ulg)2L*s->w_size;

    CLEAR_HASH(s);

    /* Set the शेष configuration parameters:
     */
    s->max_lazy_match   = configuration_table[s->level].max_lazy;
    s->good_match       = configuration_table[s->level].good_length;
    s->nice_match       = configuration_table[s->level].nice_length;
    s->max_chain_length = configuration_table[s->level].max_chain;

    s->strstart = 0;
    s->block_start = 0L;
    s->lookahead = 0;
    s->match_length = s->prev_length = MIN_MATCH-1;
    s->match_available = 0;
    s->ins_h = 0;
पूर्ण

/* ===========================================================================
 * Set match_start to the दीर्घest match starting at the given string and
 * वापस its length. Matches लघुer or equal to prev_length are discarded,
 * in which हाल the result is equal to prev_length and match_start is
 * garbage.
 * IN निश्चितions: cur_match is the head of the hash chain क्रम the current
 *   string (strstart) and its distance is <= MAX_DIST, and prev_length >= 1
 * OUT निश्चितion: the match length is not greater than s->lookahead.
 */
/* For 80x86 and 680x0, an optimized version will be provided in match.यंत्र or
 * match.S. The code will be functionally equivalent.
 */
अटल uInt दीर्घest_match(
	deflate_state *s,
	IPos cur_match			/* current match */
)
अणु
    अचिन्हित chain_length = s->max_chain_length;/* max hash chain length */
    रेजिस्टर Byte *scan = s->winकरोw + s->strstart; /* current string */
    रेजिस्टर Byte *match;                       /* matched string */
    रेजिस्टर पूर्णांक len;                           /* length of current match */
    पूर्णांक best_len = s->prev_length;              /* best match length so far */
    पूर्णांक nice_match = s->nice_match;             /* stop अगर match दीर्घ enough */
    IPos limit = s->strstart > (IPos)MAX_DIST(s) ?
        s->strstart - (IPos)MAX_DIST(s) : NIL;
    /* Stop when cur_match becomes <= limit. To simplअगरy the code,
     * we prevent matches with the string of winकरोw index 0.
     */
    Pos *prev = s->prev;
    uInt wmask = s->w_mask;

#अगर_घोषित UNALIGNED_OK
    /* Compare two bytes at a समय. Note: this is not always beneficial.
     * Try with and without -DUNALIGNED_OK to check.
     */
    रेजिस्टर Byte *strend = s->winकरोw + s->strstart + MAX_MATCH - 1;
    रेजिस्टर ush scan_start = *(ush*)scan;
    रेजिस्टर ush scan_end   = *(ush*)(scan+best_len-1);
#अन्यथा
    रेजिस्टर Byte *strend = s->winकरोw + s->strstart + MAX_MATCH;
    रेजिस्टर Byte scan_end1  = scan[best_len-1];
    रेजिस्टर Byte scan_end   = scan[best_len];
#पूर्ण_अगर

    /* The code is optimized क्रम HASH_BITS >= 8 and MAX_MATCH-2 multiple of 16.
     * It is easy to get rid of this optimization अगर necessary.
     */
    Assert(s->hash_bits >= 8 && MAX_MATCH == 258, "Code too clever");

    /* Do not waste too much समय अगर we alपढ़ोy have a good match: */
    अगर (s->prev_length >= s->good_match) अणु
        chain_length >>= 2;
    पूर्ण
    /* Do not look क्रम matches beyond the end of the input. This is necessary
     * to make deflate deterministic.
     */
    अगर ((uInt)nice_match > s->lookahead) nice_match = s->lookahead;

    Assert((ulg)s->strstart <= s->winकरोw_size-MIN_LOOKAHEAD, "need lookahead");

    करो अणु
        Assert(cur_match < s->strstart, "no future");
        match = s->winकरोw + cur_match;

        /* Skip to next match अगर the match length cannot increase
         * or अगर the match length is less than 2:
         */
#अगर (defined(UNALIGNED_OK) && MAX_MATCH == 258)
        /* This code assumes माप(अचिन्हित लघु) == 2. Do not use
         * UNALIGNED_OK अगर your compiler uses a dअगरferent size.
         */
        अगर (*(ush*)(match+best_len-1) != scan_end ||
            *(ush*)match != scan_start) जारी;

        /* It is not necessary to compare scan[2] and match[2] since they are
         * always equal when the other bytes match, given that the hash keys
         * are equal and that HASH_BITS >= 8. Compare 2 bytes at a समय at
         * strstart+3, +5, ... up to strstart+257. We check क्रम insufficient
         * lookahead only every 4th comparison; the 128th check will be made
         * at strstart+257. If MAX_MATCH-2 is not a multiple of 8, it is
         * necessary to put more guard bytes at the end of the winकरोw, or
         * to check more often क्रम insufficient lookahead.
         */
        Assert(scan[2] == match[2], "scan[2]?");
        scan++, match++;
        करो अणु
        पूर्ण जबतक (*(ush*)(scan+=2) == *(ush*)(match+=2) &&
                 *(ush*)(scan+=2) == *(ush*)(match+=2) &&
                 *(ush*)(scan+=2) == *(ush*)(match+=2) &&
                 *(ush*)(scan+=2) == *(ush*)(match+=2) &&
                 scan < strend);
        /* The funny "do {}" generates better code on most compilers */

        /* Here, scan <= winकरोw+strstart+257 */
        Assert(scan <= s->winकरोw+(अचिन्हित)(s->winकरोw_size-1), "wild scan");
        अगर (*scan == *match) scan++;

        len = (MAX_MATCH - 1) - (पूर्णांक)(strend-scan);
        scan = strend - (MAX_MATCH-1);

#अन्यथा /* UNALIGNED_OK */

        अगर (match[best_len]   != scan_end  ||
            match[best_len-1] != scan_end1 ||
            *match            != *scan     ||
            *++match          != scan[1])      जारी;

        /* The check at best_len-1 can be हटाओd because it will be made
         * again later. (This heuristic is not always a win.)
         * It is not necessary to compare scan[2] and match[2] since they
         * are always equal when the other bytes match, given that
         * the hash keys are equal and that HASH_BITS >= 8.
         */
        scan += 2, match++;
        Assert(*scan == *match, "match[2]?");

        /* We check क्रम insufficient lookahead only every 8th comparison;
         * the 256th check will be made at strstart+258.
         */
        करो अणु
        पूर्ण जबतक (*++scan == *++match && *++scan == *++match &&
                 *++scan == *++match && *++scan == *++match &&
                 *++scan == *++match && *++scan == *++match &&
                 *++scan == *++match && *++scan == *++match &&
                 scan < strend);

        Assert(scan <= s->winकरोw+(अचिन्हित)(s->winकरोw_size-1), "wild scan");

        len = MAX_MATCH - (पूर्णांक)(strend - scan);
        scan = strend - MAX_MATCH;

#पूर्ण_अगर /* UNALIGNED_OK */

        अगर (len > best_len) अणु
            s->match_start = cur_match;
            best_len = len;
            अगर (len >= nice_match) अवरोध;
#अगर_घोषित UNALIGNED_OK
            scan_end = *(ush*)(scan+best_len-1);
#अन्यथा
            scan_end1  = scan[best_len-1];
            scan_end   = scan[best_len];
#पूर्ण_अगर
        पूर्ण
    पूर्ण जबतक ((cur_match = prev[cur_match & wmask]) > limit
             && --chain_length != 0);

    अगर ((uInt)best_len <= s->lookahead) वापस best_len;
    वापस s->lookahead;
पूर्ण

#अगर_घोषित DEBUG_ZLIB
/* ===========================================================================
 * Check that the match at match_start is indeed a match.
 */
अटल व्योम check_match(
	deflate_state *s,
	IPos start,
	IPos match,
	पूर्णांक length
)
अणु
    /* check that the match is indeed a match */
    अगर (स_भेद((अक्षर *)s->winकरोw + match,
                (अक्षर *)s->winकरोw + start, length) != EQUAL) अणु
        ख_लिखो(मानक_त्रुटि, " start %u, match %u, length %d\n",
		start, match, length);
        करो अणु
	    ख_लिखो(मानक_त्रुटि, "%c%c", s->winकरोw[match++], s->winकरोw[start++]);
	पूर्ण जबतक (--length != 0);
        z_error("invalid match");
    पूर्ण
    अगर (z_verbose > 1) अणु
        ख_लिखो(मानक_त्रुटि,"\\[%d,%d]", start-match, length);
        करो अणु अ_दो(s->winकरोw[start++], मानक_त्रुटि); पूर्ण जबतक (--length != 0);
    पूर्ण
पूर्ण
#अन्यथा
#  define check_match(s, start, match, length)
#पूर्ण_अगर

/* ===========================================================================
 * Fill the winकरोw when the lookahead becomes insufficient.
 * Updates strstart and lookahead.
 *
 * IN निश्चितion: lookahead < MIN_LOOKAHEAD
 * OUT निश्चितions: strstart <= winकरोw_size-MIN_LOOKAHEAD
 *    At least one byte has been पढ़ो, or avail_in == 0; पढ़ोs are
 *    perक्रमmed क्रम at least two bytes (required क्रम the zip translate_eol
 *    option -- not supported here).
 */
अटल व्योम fill_winकरोw(
	deflate_state *s
)
अणु
    रेजिस्टर अचिन्हित n, m;
    रेजिस्टर Pos *p;
    अचिन्हित more;    /* Amount of मुक्त space at the end of the winकरोw. */
    uInt wsize = s->w_size;

    करो अणु
        more = (अचिन्हित)(s->winकरोw_size -(ulg)s->lookahead -(ulg)s->strstart);

        /* Deal with !@#$% 64K limit: */
        अगर (more == 0 && s->strstart == 0 && s->lookahead == 0) अणु
            more = wsize;

        पूर्ण अन्यथा अगर (more == (अचिन्हित)(-1)) अणु
            /* Very unlikely, but possible on 16 bit machine अगर strstart == 0
             * and lookahead == 1 (input करोne one byte at समय)
             */
            more--;

        /* If the winकरोw is almost full and there is insufficient lookahead,
         * move the upper half to the lower one to make room in the upper half.
         */
        पूर्ण अन्यथा अगर (s->strstart >= wsize+MAX_DIST(s)) अणु

            स_नकल((अक्षर *)s->winकरोw, (अक्षर *)s->winकरोw+wsize,
                   (अचिन्हित)wsize);
            s->match_start -= wsize;
            s->strstart    -= wsize; /* we now have strstart >= MAX_DIST */
            s->block_start -= (दीर्घ) wsize;

            /* Slide the hash table (could be aव्योमed with 32 bit values
               at the expense of memory usage). We slide even when level == 0
               to keep the hash table consistent अगर we चयन back to level > 0
               later. (Using level 0 permanently is not an optimal usage of
               zlib, so we करोn't care about this pathological हाल.)
             */
            n = s->hash_size;
            p = &s->head[n];
            करो अणु
                m = *--p;
                *p = (Pos)(m >= wsize ? m-wsize : NIL);
            पूर्ण जबतक (--n);

            n = wsize;
            p = &s->prev[n];
            करो अणु
                m = *--p;
                *p = (Pos)(m >= wsize ? m-wsize : NIL);
                /* If n is not on any hash chain, prev[n] is garbage but
                 * its value will never be used.
                 */
            पूर्ण जबतक (--n);
            more += wsize;
        पूर्ण
        अगर (s->strm->avail_in == 0) वापस;

        /* If there was no sliding:
         *    strstart <= WSIZE+MAX_DIST-1 && lookahead <= MIN_LOOKAHEAD - 1 &&
         *    more == winकरोw_size - lookahead - strstart
         * => more >= winकरोw_size - (MIN_LOOKAHEAD-1 + WSIZE + MAX_DIST-1)
         * => more >= winकरोw_size - 2*WSIZE + 2
         * In the BIG_MEM or MMAP हाल (not yet supported),
         *   winकरोw_size == input_size + MIN_LOOKAHEAD  &&
         *   strstart + s->lookahead <= input_size => more >= MIN_LOOKAHEAD.
         * Otherwise, winकरोw_size == 2*WSIZE so more >= 2.
         * If there was sliding, more >= WSIZE. So in all हालs, more >= 2.
         */
        Assert(more >= 2, "more < 2");

        n = पढ़ो_buf(s->strm, s->winकरोw + s->strstart + s->lookahead, more);
        s->lookahead += n;

        /* Initialize the hash value now that we have some input: */
        अगर (s->lookahead >= MIN_MATCH) अणु
            s->ins_h = s->winकरोw[s->strstart];
            UPDATE_HASH(s, s->ins_h, s->winकरोw[s->strstart+1]);
#अगर MIN_MATCH != 3
            Call UPDATE_HASH() MIN_MATCH-3 more बार
#पूर्ण_अगर
        पूर्ण
        /* If the whole input has less than MIN_MATCH bytes, ins_h is garbage,
         * but this is not important since only literal bytes will be emitted.
         */

    पूर्ण जबतक (s->lookahead < MIN_LOOKAHEAD && s->strm->avail_in != 0);
पूर्ण

/* ===========================================================================
 * Flush the current block, with given end-of-file flag.
 * IN निश्चितion: strstart is set to the end of the current match.
 */
#घोषणा FLUSH_BLOCK_ONLY(s, eof) अणु \
   zlib_tr_flush_block(s, (s->block_start >= 0L ? \
                   (अक्षर *)&s->winकरोw[(अचिन्हित)s->block_start] : \
                   शून्य), \
		(ulg)((दीर्घ)s->strstart - s->block_start), \
		(eof)); \
   s->block_start = s->strstart; \
   flush_pending(s->strm); \
   Tracev((मानक_त्रुटि,"[FLUSH]")); \
पूर्ण

/* Same but क्रमce premature निकास अगर necessary. */
#घोषणा FLUSH_BLOCK(s, eof) अणु \
   FLUSH_BLOCK_ONLY(s, eof); \
   अगर (s->strm->avail_out == 0) वापस (eof) ? finish_started : need_more; \
पूर्ण

/* ===========================================================================
 * Copy without compression as much as possible from the input stream, वापस
 * the current block state.
 * This function करोes not insert new strings in the dictionary since
 * uncompressible data is probably not useful. This function is used
 * only क्रम the level=0 compression option.
 * NOTE: this function should be optimized to aव्योम extra copying from
 * winकरोw to pending_buf.
 */
अटल block_state deflate_stored(
	deflate_state *s,
	पूर्णांक flush
)
अणु
    /* Stored blocks are limited to 0xffff bytes, pending_buf is limited
     * to pending_buf_size, and each stored block has a 5 byte header:
     */
    ulg max_block_size = 0xffff;
    ulg max_start;

    अगर (max_block_size > s->pending_buf_size - 5) अणु
        max_block_size = s->pending_buf_size - 5;
    पूर्ण

    /* Copy as much as possible from input to output: */
    क्रम (;;) अणु
        /* Fill the winकरोw as much as possible: */
        अगर (s->lookahead <= 1) अणु

            Assert(s->strstart < s->w_size+MAX_DIST(s) ||
		   s->block_start >= (दीर्घ)s->w_size, "slide too late");

            fill_winकरोw(s);
            अगर (s->lookahead == 0 && flush == Z_NO_FLUSH) वापस need_more;

            अगर (s->lookahead == 0) अवरोध; /* flush the current block */
        पूर्ण
	Assert(s->block_start >= 0L, "block gone");

	s->strstart += s->lookahead;
	s->lookahead = 0;

	/* Emit a stored block अगर pending_buf will be full: */
 	max_start = s->block_start + max_block_size;
        अगर (s->strstart == 0 || (ulg)s->strstart >= max_start) अणु
	    /* strstart == 0 is possible when wraparound on 16-bit machine */
	    s->lookahead = (uInt)(s->strstart - max_start);
	    s->strstart = (uInt)max_start;
            FLUSH_BLOCK(s, 0);
	पूर्ण
	/* Flush अगर we may have to slide, otherwise block_start may become
         * negative and the data will be gone:
         */
        अगर (s->strstart - (uInt)s->block_start >= MAX_DIST(s)) अणु
            FLUSH_BLOCK(s, 0);
	पूर्ण
    पूर्ण
    FLUSH_BLOCK(s, flush == Z_FINISH);
    वापस flush == Z_FINISH ? finish_करोne : block_करोne;
पूर्ण

/* ===========================================================================
 * Compress as much as possible from the input stream, वापस the current
 * block state.
 * This function करोes not perक्रमm lazy evaluation of matches and inserts
 * new strings in the dictionary only क्रम unmatched strings or क्रम लघु
 * matches. It is used only क्रम the fast compression options.
 */
अटल block_state deflate_fast(
	deflate_state *s,
	पूर्णांक flush
)
अणु
    IPos hash_head = NIL; /* head of the hash chain */
    पूर्णांक bflush;           /* set अगर current block must be flushed */

    क्रम (;;) अणु
        /* Make sure that we always have enough lookahead, except
         * at the end of the input file. We need MAX_MATCH bytes
         * क्रम the next match, plus MIN_MATCH bytes to insert the
         * string following the next match.
         */
        अगर (s->lookahead < MIN_LOOKAHEAD) अणु
            fill_winकरोw(s);
            अगर (s->lookahead < MIN_LOOKAHEAD && flush == Z_NO_FLUSH) अणु
	        वापस need_more;
	    पूर्ण
            अगर (s->lookahead == 0) अवरोध; /* flush the current block */
        पूर्ण

        /* Insert the string winकरोw[strstart .. strstart+2] in the
         * dictionary, and set hash_head to the head of the hash chain:
         */
        अगर (s->lookahead >= MIN_MATCH) अणु
            INSERT_STRING(s, s->strstart, hash_head);
        पूर्ण

        /* Find the दीर्घest match, discarding those <= prev_length.
         * At this poपूर्णांक we have always match_length < MIN_MATCH
         */
        अगर (hash_head != NIL && s->strstart - hash_head <= MAX_DIST(s)) अणु
            /* To simplअगरy the code, we prevent matches with the string
             * of winकरोw index 0 (in particular we have to aव्योम a match
             * of the string with itself at the start of the input file).
             */
            अगर (s->strategy != Z_HUFFMAN_ONLY) अणु
                s->match_length = दीर्घest_match (s, hash_head);
            पूर्ण
            /* दीर्घest_match() sets match_start */
        पूर्ण
        अगर (s->match_length >= MIN_MATCH) अणु
            check_match(s, s->strstart, s->match_start, s->match_length);

            bflush = zlib_tr_tally(s, s->strstart - s->match_start,
                               s->match_length - MIN_MATCH);

            s->lookahead -= s->match_length;

            /* Insert new strings in the hash table only अगर the match length
             * is not too large. This saves समय but degrades compression.
             */
            अगर (s->match_length <= s->max_insert_length &&
                s->lookahead >= MIN_MATCH) अणु
                s->match_length--; /* string at strstart alपढ़ोy in hash table */
                करो अणु
                    s->strstart++;
                    INSERT_STRING(s, s->strstart, hash_head);
                    /* strstart never exceeds WSIZE-MAX_MATCH, so there are
                     * always MIN_MATCH bytes ahead.
                     */
                पूर्ण जबतक (--s->match_length != 0);
                s->strstart++; 
            पूर्ण अन्यथा अणु
                s->strstart += s->match_length;
                s->match_length = 0;
                s->ins_h = s->winकरोw[s->strstart];
                UPDATE_HASH(s, s->ins_h, s->winकरोw[s->strstart+1]);
#अगर MIN_MATCH != 3
                Call UPDATE_HASH() MIN_MATCH-3 more बार
#पूर्ण_अगर
                /* If lookahead < MIN_MATCH, ins_h is garbage, but it करोes not
                 * matter since it will be recomputed at next deflate call.
                 */
            पूर्ण
        पूर्ण अन्यथा अणु
            /* No match, output a literal byte */
            Tracevv((मानक_त्रुटि,"%c", s->winकरोw[s->strstart]));
            bflush = zlib_tr_tally (s, 0, s->winकरोw[s->strstart]);
            s->lookahead--;
            s->strstart++; 
        पूर्ण
        अगर (bflush) FLUSH_BLOCK(s, 0);
    पूर्ण
    FLUSH_BLOCK(s, flush == Z_FINISH);
    वापस flush == Z_FINISH ? finish_करोne : block_करोne;
पूर्ण

/* ===========================================================================
 * Same as above, but achieves better compression. We use a lazy
 * evaluation क्रम matches: a match is finally aकरोpted only अगर there is
 * no better match at the next winकरोw position.
 */
अटल block_state deflate_slow(
	deflate_state *s,
	पूर्णांक flush
)
अणु
    IPos hash_head = NIL;    /* head of hash chain */
    पूर्णांक bflush;              /* set अगर current block must be flushed */

    /* Process the input block. */
    क्रम (;;) अणु
        /* Make sure that we always have enough lookahead, except
         * at the end of the input file. We need MAX_MATCH bytes
         * क्रम the next match, plus MIN_MATCH bytes to insert the
         * string following the next match.
         */
        अगर (s->lookahead < MIN_LOOKAHEAD) अणु
            fill_winकरोw(s);
            अगर (s->lookahead < MIN_LOOKAHEAD && flush == Z_NO_FLUSH) अणु
	        वापस need_more;
	    पूर्ण
            अगर (s->lookahead == 0) अवरोध; /* flush the current block */
        पूर्ण

        /* Insert the string winकरोw[strstart .. strstart+2] in the
         * dictionary, and set hash_head to the head of the hash chain:
         */
        अगर (s->lookahead >= MIN_MATCH) अणु
            INSERT_STRING(s, s->strstart, hash_head);
        पूर्ण

        /* Find the दीर्घest match, discarding those <= prev_length.
         */
        s->prev_length = s->match_length, s->prev_match = s->match_start;
        s->match_length = MIN_MATCH-1;

        अगर (hash_head != NIL && s->prev_length < s->max_lazy_match &&
            s->strstart - hash_head <= MAX_DIST(s)) अणु
            /* To simplअगरy the code, we prevent matches with the string
             * of winकरोw index 0 (in particular we have to aव्योम a match
             * of the string with itself at the start of the input file).
             */
            अगर (s->strategy != Z_HUFFMAN_ONLY) अणु
                s->match_length = दीर्घest_match (s, hash_head);
            पूर्ण
            /* दीर्घest_match() sets match_start */

            अगर (s->match_length <= 5 && (s->strategy == Z_FILTERED ||
                 (s->match_length == MIN_MATCH &&
                  s->strstart - s->match_start > TOO_FAR))) अणु

                /* If prev_match is also MIN_MATCH, match_start is garbage
                 * but we will ignore the current match anyway.
                 */
                s->match_length = MIN_MATCH-1;
            पूर्ण
        पूर्ण
        /* If there was a match at the previous step and the current
         * match is not better, output the previous match:
         */
        अगर (s->prev_length >= MIN_MATCH && s->match_length <= s->prev_length) अणु
            uInt max_insert = s->strstart + s->lookahead - MIN_MATCH;
            /* Do not insert strings in hash table beyond this. */

            check_match(s, s->strstart-1, s->prev_match, s->prev_length);

            bflush = zlib_tr_tally(s, s->strstart -1 - s->prev_match,
				   s->prev_length - MIN_MATCH);

            /* Insert in hash table all strings up to the end of the match.
             * strstart-1 and strstart are alपढ़ोy inserted. If there is not
             * enough lookahead, the last two strings are not inserted in
             * the hash table.
             */
            s->lookahead -= s->prev_length-1;
            s->prev_length -= 2;
            करो अणु
                अगर (++s->strstart <= max_insert) अणु
                    INSERT_STRING(s, s->strstart, hash_head);
                पूर्ण
            पूर्ण जबतक (--s->prev_length != 0);
            s->match_available = 0;
            s->match_length = MIN_MATCH-1;
            s->strstart++;

            अगर (bflush) FLUSH_BLOCK(s, 0);

        पूर्ण अन्यथा अगर (s->match_available) अणु
            /* If there was no match at the previous position, output a
             * single literal. If there was a match but the current match
             * is दीर्घer, truncate the previous match to a single literal.
             */
            Tracevv((मानक_त्रुटि,"%c", s->winकरोw[s->strstart-1]));
            अगर (zlib_tr_tally (s, 0, s->winकरोw[s->strstart-1])) अणु
                FLUSH_BLOCK_ONLY(s, 0);
            पूर्ण
            s->strstart++;
            s->lookahead--;
            अगर (s->strm->avail_out == 0) वापस need_more;
        पूर्ण अन्यथा अणु
            /* There is no previous match to compare with, रुको क्रम
             * the next step to decide.
             */
            s->match_available = 1;
            s->strstart++;
            s->lookahead--;
        पूर्ण
    पूर्ण
    Assert (flush != Z_NO_FLUSH, "no flush?");
    अगर (s->match_available) अणु
        Tracevv((मानक_त्रुटि,"%c", s->winकरोw[s->strstart-1]));
        zlib_tr_tally (s, 0, s->winकरोw[s->strstart-1]);
        s->match_available = 0;
    पूर्ण
    FLUSH_BLOCK(s, flush == Z_FINISH);
    वापस flush == Z_FINISH ? finish_करोne : block_करोne;
पूर्ण

पूर्णांक zlib_deflate_workspacesize(पूर्णांक winकरोwBits, पूर्णांक memLevel)
अणु
    अगर (winकरोwBits < 0) /* unकरोcumented feature: suppress zlib header */
        winकरोwBits = -winकरोwBits;

    /* Since the वापस value is typically passed to vदो_स्मृति() unchecked... */
    BUG_ON(memLevel < 1 || memLevel > MAX_MEM_LEVEL || winकरोwBits < 9 ||
							winकरोwBits > 15);

    वापस माप(deflate_workspace)
        + zlib_deflate_winकरोw_memsize(winकरोwBits)
        + zlib_deflate_prev_memsize(winकरोwBits)
        + zlib_deflate_head_memsize(memLevel)
        + zlib_deflate_overlay_memsize(memLevel);
पूर्ण

पूर्णांक zlib_deflate_dfltcc_enabled(व्योम)
अणु
	वापस DEFLATE_DFLTCC_ENABLED();
पूर्ण
