<शैली गुरु>
#अगर_अघोषित DEFUTIL_H
#घोषणा DEFUTIL_H

#समावेश <linux/zutil.h>

#घोषणा Assert(err, str) 
#घोषणा Trace(dummy) 
#घोषणा Tracev(dummy) 
#घोषणा Tracecv(err, dummy) 
#घोषणा Tracevv(dummy) 



#घोषणा LENGTH_CODES 29
/* number of length codes, not counting the special END_BLOCK code */

#घोषणा LITERALS  256
/* number of literal bytes 0..255 */

#घोषणा L_CODES (LITERALS+1+LENGTH_CODES)
/* number of Literal or Length codes, including the END_BLOCK code */

#घोषणा D_CODES   30
/* number of distance codes */

#घोषणा BL_CODES  19
/* number of codes used to transfer the bit lengths */

#घोषणा HEAP_SIZE (2*L_CODES+1)
/* maximum heap size */

#घोषणा MAX_BITS 15
/* All codes must not exceed MAX_BITS bits */

#घोषणा INIT_STATE    42
#घोषणा BUSY_STATE   113
#घोषणा FINISH_STATE 666
/* Stream status */


/* Data काष्ठाure describing a single value and its code string. */
प्रकार काष्ठा ct_data_s अणु
    जोड़ अणु
        ush  freq;       /* frequency count */
        ush  code;       /* bit string */
    पूर्ण fc;
    जोड़ अणु
        ush  dad;        /* father node in Huffman tree */
        ush  len;        /* length of bit string */
    पूर्ण dl;
पूर्ण ct_data;

#घोषणा Freq fc.freq
#घोषणा Code fc.code
#घोषणा Dad  dl.dad
#घोषणा Len  dl.len

प्रकार काष्ठा अटल_tree_desc_s  अटल_tree_desc;

प्रकार काष्ठा tree_desc_s अणु
    ct_data *dyn_tree;           /* the dynamic tree */
    पूर्णांक     max_code;            /* largest code with non zero frequency */
    अटल_tree_desc *stat_desc; /* the corresponding अटल tree */
पूर्ण tree_desc;

प्रकार ush Pos;
प्रकार अचिन्हित IPos;

/* A Pos is an index in the अक्षरacter winकरोw. We use लघु instead of पूर्णांक to
 * save space in the various tables. IPos is used only क्रम parameter passing.
 */

प्रकार काष्ठा deflate_state अणु
    z_streamp strm;      /* poपूर्णांकer back to this zlib stream */
    पूर्णांक   status;        /* as the name implies */
    Byte *pending_buf;   /* output still pending */
    ulg   pending_buf_size; /* size of pending_buf */
    Byte *pending_out;   /* next pending byte to output to the stream */
    पूर्णांक   pending;       /* nb of bytes in the pending buffer */
    पूर्णांक   noheader;      /* suppress zlib header and adler32 */
    Byte  data_type;     /* UNKNOWN, BINARY or ASCII */
    Byte  method;        /* STORED (क्रम zip only) or DEFLATED */
    पूर्णांक   last_flush;    /* value of flush param क्रम previous deflate call */

                /* used by deflate.c: */

    uInt  w_size;        /* LZ77 winकरोw size (32K by शेष) */
    uInt  w_bits;        /* log2(w_size)  (8..16) */
    uInt  w_mask;        /* w_size - 1 */

    Byte *winकरोw;
    /* Sliding winकरोw. Input bytes are पढ़ो पूर्णांकo the second half of the winकरोw,
     * and move to the first half later to keep a dictionary of at least wSize
     * bytes. With this organization, matches are limited to a distance of
     * wSize-MAX_MATCH bytes, but this ensures that IO is always
     * perक्रमmed with a length multiple of the block size. Also, it limits
     * the winकरोw size to 64K, which is quite useful on MSDOS.
     * To करो: use the user input buffer as sliding winकरोw.
     */

    ulg winकरोw_size;
    /* Actual size of winकरोw: 2*wSize, except when the user input buffer
     * is directly used as sliding winकरोw.
     */

    Pos *prev;
    /* Link to older string with same hash index. To limit the size of this
     * array to 64K, this link is मुख्यtained only क्रम the last 32K strings.
     * An index in this array is thus a winकरोw index modulo 32K.
     */

    Pos *head; /* Heads of the hash chains or NIL. */

    uInt  ins_h;          /* hash index of string to be inserted */
    uInt  hash_size;      /* number of elements in hash table */
    uInt  hash_bits;      /* log2(hash_size) */
    uInt  hash_mask;      /* hash_size-1 */

    uInt  hash_shअगरt;
    /* Number of bits by which ins_h must be shअगरted at each input
     * step. It must be such that after MIN_MATCH steps, the oldest
     * byte no दीर्घer takes part in the hash key, that is:
     *   hash_shअगरt * MIN_MATCH >= hash_bits
     */

    दीर्घ block_start;
    /* Winकरोw position at the beginning of the current output block. Gets
     * negative when the winकरोw is moved backwards.
     */

    uInt match_length;           /* length of best match */
    IPos prev_match;             /* previous match */
    पूर्णांक match_available;         /* set अगर previous match exists */
    uInt strstart;               /* start of string to insert */
    uInt match_start;            /* start of matching string */
    uInt lookahead;              /* number of valid bytes ahead in winकरोw */

    uInt prev_length;
    /* Length of the best match at previous step. Matches not greater than this
     * are discarded. This is used in the lazy match evaluation.
     */

    uInt max_chain_length;
    /* To speed up deflation, hash chains are never searched beyond this
     * length.  A higher limit improves compression ratio but degrades the
     * speed.
     */

    uInt max_lazy_match;
    /* Attempt to find a better match only when the current match is strictly
     * smaller than this value. This mechanism is used only क्रम compression
     * levels >= 4.
     */
#   define max_insert_length  max_lazy_match
    /* Insert new strings in the hash table only अगर the match length is not
     * greater than this length. This saves समय but degrades compression.
     * max_insert_length is used only क्रम compression levels <= 3.
     */

    पूर्णांक level;    /* compression level (1..9) */
    पूर्णांक strategy; /* favor or क्रमce Huffman coding*/

    uInt good_match;
    /* Use a faster search when the previous match is दीर्घer than this */

    पूर्णांक nice_match; /* Stop searching when current match exceeds this */

                /* used by trees.c: */
    /* Didn't use ct_data प्रकार below to suppress compiler warning */
    काष्ठा ct_data_s dyn_ltree[HEAP_SIZE];   /* literal and length tree */
    काष्ठा ct_data_s dyn_dtree[2*D_CODES+1]; /* distance tree */
    काष्ठा ct_data_s bl_tree[2*BL_CODES+1];  /* Huffman tree क्रम bit lengths */

    काष्ठा tree_desc_s l_desc;               /* desc. क्रम literal tree */
    काष्ठा tree_desc_s d_desc;               /* desc. क्रम distance tree */
    काष्ठा tree_desc_s bl_desc;              /* desc. क्रम bit length tree */

    ush bl_count[MAX_BITS+1];
    /* number of codes at each bit length क्रम an optimal tree */

    पूर्णांक heap[2*L_CODES+1];      /* heap used to build the Huffman trees */
    पूर्णांक heap_len;               /* number of elements in the heap */
    पूर्णांक heap_max;               /* element of largest frequency */
    /* The sons of heap[n] are heap[2*n] and heap[2*n+1]. heap[0] is not used.
     * The same heap array is used to build all trees.
     */

    uch depth[2*L_CODES+1];
    /* Depth of each subtree used as tie अवरोधer क्रम trees of equal frequency
     */

    uch *l_buf;          /* buffer क्रम literals or lengths */

    uInt  lit_bufsize;
    /* Size of match buffer क्रम literals/lengths.  There are 4 reasons क्रम
     * limiting lit_bufsize to 64K:
     *   - frequencies can be kept in 16 bit counters
     *   - अगर compression is not successful क्रम the first block, all input
     *     data is still in the winकरोw so we can still emit a stored block even
     *     when input comes from standard input.  (This can also be करोne क्रम
     *     all blocks अगर lit_bufsize is not greater than 32K.)
     *   - अगर compression is not successful क्रम a file smaller than 64K, we can
     *     even emit a stored file instead of a stored block (saving 5 bytes).
     *     This is applicable only क्रम zip (not gzip or zlib).
     *   - creating new Huffman trees less frequently may not provide fast
     *     adaptation to changes in the input data statistics. (Take क्रम
     *     example a binary file with poorly compressible code followed by
     *     a highly compressible string table.) Smaller buffer sizes give
     *     fast adaptation but have of course the overhead of transmitting
     *     trees more frequently.
     *   - I can't count above 4
     */

    uInt last_lit;      /* running index in l_buf */

    ush *d_buf;
    /* Buffer क्रम distances. To simplअगरy the code, d_buf and l_buf have
     * the same number of elements. To use dअगरferent lengths, an extra flag
     * array would be necessary.
     */

    ulg opt_len;        /* bit length of current block with optimal trees */
    ulg अटल_len;     /* bit length of current block with अटल trees */
    ulg compressed_len; /* total bit length of compressed file */
    uInt matches;       /* number of string matches in current block */
    पूर्णांक last_eob_len;   /* bit length of EOB code क्रम last block */

#अगर_घोषित DEBUG_ZLIB
    ulg bits_sent;      /* bit length of the compressed data */
#पूर्ण_अगर

    ush bi_buf;
    /* Output buffer. bits are inserted starting at the bottom (least
     * signअगरicant bits).
     */
    पूर्णांक bi_valid;
    /* Number of valid bits in bi_buf.  All bits above the last valid bit
     * are always zero.
     */

पूर्ण deflate_state;

#अगर_घोषित CONFIG_ZLIB_DFLTCC
#घोषणा zlib_deflate_winकरोw_memsize(winकरोwBits) \
	(2 * (1 << (winकरोwBits)) * माप(Byte) + PAGE_SIZE)
#अन्यथा
#घोषणा zlib_deflate_winकरोw_memsize(winकरोwBits) \
	(2 * (1 << (winकरोwBits)) * माप(Byte))
#पूर्ण_अगर
#घोषणा zlib_deflate_prev_memsize(winकरोwBits) \
	((1 << (winकरोwBits)) * माप(Pos))
#घोषणा zlib_deflate_head_memsize(memLevel) \
	((1 << ((memLevel)+7)) * माप(Pos))
#घोषणा zlib_deflate_overlay_memsize(memLevel) \
	((1 << ((memLevel)+6)) * (माप(ush)+2))

/* Output a byte on the stream.
 * IN निश्चितion: there is enough room in pending_buf.
 */
#घोषणा put_byte(s, c) अणुs->pending_buf[s->pending++] = (c);पूर्ण


#घोषणा MIN_LOOKAHEAD (MAX_MATCH+MIN_MATCH+1)
/* Minimum amount of lookahead, except at the end of the input file.
 * See deflate.c क्रम comments about the MIN_MATCH+1.
 */

#घोषणा MAX_DIST(s)  ((s)->w_size-MIN_LOOKAHEAD)
/* In order to simplअगरy the code, particularly on 16 bit machines, match
 * distances are limited to MAX_DIST instead of WSIZE.
 */

        /* in trees.c */
व्योम zlib_tr_init         (deflate_state *s);
पूर्णांक  zlib_tr_tally        (deflate_state *s, अचिन्हित dist, अचिन्हित lc);
ulg  zlib_tr_flush_block  (deflate_state *s, अक्षर *buf, ulg stored_len,
			   पूर्णांक eof);
व्योम zlib_tr_align        (deflate_state *s);
व्योम zlib_tr_stored_block (deflate_state *s, अक्षर *buf, ulg stored_len,
			   पूर्णांक eof);
व्योम zlib_tr_stored_type_only (deflate_state *);


/* ===========================================================================
 * Output a लघु LSB first on the stream.
 * IN निश्चितion: there is enough room in pendingBuf.
 */
#घोषणा put_लघु(s, w) अणु \
    put_byte(s, (uch)((w) & 0xff)); \
    put_byte(s, (uch)((ush)(w) >> 8)); \
पूर्ण

/* ===========================================================================
 * Reverse the first len bits of a code, using straightक्रमward code (a faster
 * method would use a table)
 * IN निश्चितion: 1 <= len <= 15
 */
अटल अंतरभूत अचिन्हित  bi_reverse(
    अचिन्हित code, /* the value to invert */
    पूर्णांक len        /* its bit length */
)
अणु
    रेजिस्टर अचिन्हित res = 0;
    करो अणु
        res |= code & 1;
        code >>= 1, res <<= 1;
    पूर्ण जबतक (--len > 0);
    वापस res >> 1;
पूर्ण

/* ===========================================================================
 * Flush the bit buffer, keeping at most 7 bits in it.
 */
अटल अंतरभूत व्योम bi_flush(deflate_state *s)
अणु
    अगर (s->bi_valid == 16) अणु
        put_लघु(s, s->bi_buf);
        s->bi_buf = 0;
        s->bi_valid = 0;
    पूर्ण अन्यथा अगर (s->bi_valid >= 8) अणु
        put_byte(s, (Byte)s->bi_buf);
        s->bi_buf >>= 8;
        s->bi_valid -= 8;
    पूर्ण
पूर्ण

/* ===========================================================================
 * Flush the bit buffer and align the output on a byte boundary
 */
अटल अंतरभूत व्योम bi_windup(deflate_state *s)
अणु
    अगर (s->bi_valid > 8) अणु
        put_लघु(s, s->bi_buf);
    पूर्ण अन्यथा अगर (s->bi_valid > 0) अणु
        put_byte(s, (Byte)s->bi_buf);
    पूर्ण
    s->bi_buf = 0;
    s->bi_valid = 0;
#अगर_घोषित DEBUG_ZLIB
    s->bits_sent = (s->bits_sent+7) & ~7;
#पूर्ण_अगर
पूर्ण

प्रकार क्रमागत अणु
    need_more,      /* block not completed, need more input or more output */
    block_करोne,     /* block flush perक्रमmed */
    finish_started, /* finish started, need only more output at next deflate */
    finish_करोne     /* finish करोne, accept no more input or output */
पूर्ण block_state;

#घोषणा Buf_size (8 * 2*माप(अक्षर))
/* Number of bits used within bi_buf. (bi_buf might be implemented on
 * more than 16 bits on some प्रणालीs.)
 */

/* ===========================================================================
 * Send a value on a given number of bits.
 * IN निश्चितion: length <= 16 and value fits in length bits.
 */
#अगर_घोषित DEBUG_ZLIB
अटल व्योम send_bits      (deflate_state *s, पूर्णांक value, पूर्णांक length);

अटल व्योम send_bits(
    deflate_state *s,
    पूर्णांक value,  /* value to send */
    पूर्णांक length  /* number of bits */
)
अणु
    Tracevv((मानक_त्रुटि," l %2d v %4x ", length, value));
    Assert(length > 0 && length <= 15, "invalid length");
    s->bits_sent += (ulg)length;

    /* If not enough room in bi_buf, use (valid) bits from bi_buf and
     * (16 - bi_valid) bits from value, leaving (width - (16-bi_valid))
     * unused bits in value.
     */
    अगर (s->bi_valid > (पूर्णांक)Buf_size - length) अणु
        s->bi_buf |= (value << s->bi_valid);
        put_लघु(s, s->bi_buf);
        s->bi_buf = (ush)value >> (Buf_size - s->bi_valid);
        s->bi_valid += length - Buf_size;
    पूर्ण अन्यथा अणु
        s->bi_buf |= value << s->bi_valid;
        s->bi_valid += length;
    पूर्ण
पूर्ण
#अन्यथा /* !DEBUG_ZLIB */

#घोषणा send_bits(s, value, length) \
अणु पूर्णांक len = length;\
  अगर (s->bi_valid > (पूर्णांक)Buf_size - len) अणु\
    पूर्णांक val = value;\
    s->bi_buf |= (val << s->bi_valid);\
    put_लघु(s, s->bi_buf);\
    s->bi_buf = (ush)val >> (Buf_size - s->bi_valid);\
    s->bi_valid += len - Buf_size;\
  पूर्ण अन्यथा अणु\
    s->bi_buf |= (value) << s->bi_valid;\
    s->bi_valid += len;\
  पूर्ण\
पूर्ण
#पूर्ण_अगर /* DEBUG_ZLIB */

अटल अंतरभूत व्योम zlib_tr_send_bits(
    deflate_state *s,
    पूर्णांक value,
    पूर्णांक length
)
अणु
    send_bits(s, value, length);
पूर्ण

/* =========================================================================
 * Flush as much pending output as possible. All deflate() output goes
 * through this function so some applications may wish to modअगरy it
 * to aव्योम allocating a large strm->next_out buffer and copying पूर्णांकo it.
 * (See also पढ़ो_buf()).
 */
अटल अंतरभूत व्योम flush_pending(
	z_streamp strm
)
अणु
    deflate_state *s = (deflate_state *) strm->state;
    अचिन्हित len = s->pending;

    अगर (len > strm->avail_out) len = strm->avail_out;
    अगर (len == 0) वापस;

    अगर (strm->next_out != शून्य) अणु
	स_नकल(strm->next_out, s->pending_out, len);
	strm->next_out += len;
    पूर्ण
    s->pending_out += len;
    strm->total_out += len;
    strm->avail_out  -= len;
    s->pending -= len;
    अगर (s->pending == 0) अणु
        s->pending_out = s->pending_buf;
    पूर्ण
पूर्ण
#पूर्ण_अगर /* DEFUTIL_H */
