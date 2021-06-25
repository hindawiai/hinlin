<शैली गुरु>
/*
 * LZMA2 decoder
 *
 * Authors: Lasse Collin <lasse.collin@tukaani.org>
 *          Igor Pavlov <https://7-zip.org/>
 *
 * This file has been put पूर्णांकo the खुला करोमुख्य.
 * You can करो whatever you want with this file.
 */

#समावेश "xz_private.h"
#समावेश "xz_lzma2.h"

/*
 * Range decoder initialization eats the first five bytes of each LZMA chunk.
 */
#घोषणा RC_INIT_BYTES 5

/*
 * Minimum number of usable input buffer to safely decode one LZMA symbol.
 * The worst हाल is that we decode 22 bits using probabilities and 26
 * direct bits. This may decode at maximum of 20 bytes of input. However,
 * lzma_मुख्य() करोes an extra normalization beक्रमe वापसing, thus we
 * need to put 21 here.
 */
#घोषणा LZMA_IN_REQUIRED 21

/*
 * Dictionary (history buffer)
 *
 * These are always true:
 *    start <= pos <= full <= end
 *    pos <= limit <= end
 *
 * In multi-call mode, also these are true:
 *    end == size
 *    size <= size_max
 *    allocated <= size
 *
 * Most of these variables are माप_प्रकार to support single-call mode,
 * in which the dictionary variables address the actual output
 * buffer directly.
 */
काष्ठा dictionary अणु
	/* Beginning of the history buffer */
	uपूर्णांक8_t *buf;

	/* Old position in buf (beक्रमe decoding more data) */
	माप_प्रकार start;

	/* Position in buf */
	माप_प्रकार pos;

	/*
	 * How full dictionary is. This is used to detect corrupt input that
	 * would पढ़ो beyond the beginning of the uncompressed stream.
	 */
	माप_प्रकार full;

	/* Write limit; we करोn't ग_लिखो to buf[limit] or later bytes. */
	माप_प्रकार limit;

	/*
	 * End of the dictionary buffer. In multi-call mode, this is
	 * the same as the dictionary size. In single-call mode, this
	 * indicates the size of the output buffer.
	 */
	माप_प्रकार end;

	/*
	 * Size of the dictionary as specअगरied in Block Header. This is used
	 * together with "full" to detect corrupt input that would make us
	 * पढ़ो beyond the beginning of the uncompressed stream.
	 */
	uपूर्णांक32_t size;

	/*
	 * Maximum allowed dictionary size in multi-call mode.
	 * This is ignored in single-call mode.
	 */
	uपूर्णांक32_t size_max;

	/*
	 * Amount of memory currently allocated क्रम the dictionary.
	 * This is used only with XZ_DYNALLOC. (With XZ_PREALLOC,
	 * size_max is always the same as the allocated size.)
	 */
	uपूर्णांक32_t allocated;

	/* Operation mode */
	क्रमागत xz_mode mode;
पूर्ण;

/* Range decoder */
काष्ठा rc_dec अणु
	uपूर्णांक32_t range;
	uपूर्णांक32_t code;

	/*
	 * Number of initializing bytes reमुख्यing to be पढ़ो
	 * by rc_पढ़ो_init().
	 */
	uपूर्णांक32_t init_bytes_left;

	/*
	 * Buffer from which we पढ़ो our input. It can be either
	 * temp.buf or the caller-provided input buffer.
	 */
	स्थिर uपूर्णांक8_t *in;
	माप_प्रकार in_pos;
	माप_प्रकार in_limit;
पूर्ण;

/* Probabilities क्रम a length decoder. */
काष्ठा lzma_len_dec अणु
	/* Probability of match length being at least 10 */
	uपूर्णांक16_t choice;

	/* Probability of match length being at least 18 */
	uपूर्णांक16_t choice2;

	/* Probabilities क्रम match lengths 2-9 */
	uपूर्णांक16_t low[POS_STATES_MAX][LEN_LOW_SYMBOLS];

	/* Probabilities क्रम match lengths 10-17 */
	uपूर्णांक16_t mid[POS_STATES_MAX][LEN_MID_SYMBOLS];

	/* Probabilities क्रम match lengths 18-273 */
	uपूर्णांक16_t high[LEN_HIGH_SYMBOLS];
पूर्ण;

काष्ठा lzma_dec अणु
	/* Distances of latest four matches */
	uपूर्णांक32_t rep0;
	uपूर्णांक32_t rep1;
	uपूर्णांक32_t rep2;
	uपूर्णांक32_t rep3;

	/* Types of the most recently seen LZMA symbols */
	क्रमागत lzma_state state;

	/*
	 * Length of a match. This is updated so that dict_repeat can
	 * be called again to finish repeating the whole match.
	 */
	uपूर्णांक32_t len;

	/*
	 * LZMA properties or related bit masks (number of literal
	 * context bits, a mask dervied from the number of literal
	 * position bits, and a mask dervied from the number
	 * position bits)
	 */
	uपूर्णांक32_t lc;
	uपूर्णांक32_t literal_pos_mask; /* (1 << lp) - 1 */
	uपूर्णांक32_t pos_mask;         /* (1 << pb) - 1 */

	/* If 1, it's a match. Otherwise it's a single 8-bit literal. */
	uपूर्णांक16_t is_match[STATES][POS_STATES_MAX];

	/* If 1, it's a repeated match. The distance is one of rep0 .. rep3. */
	uपूर्णांक16_t is_rep[STATES];

	/*
	 * If 0, distance of a repeated match is rep0.
	 * Otherwise check is_rep1.
	 */
	uपूर्णांक16_t is_rep0[STATES];

	/*
	 * If 0, distance of a repeated match is rep1.
	 * Otherwise check is_rep2.
	 */
	uपूर्णांक16_t is_rep1[STATES];

	/* If 0, distance of a repeated match is rep2. Otherwise it is rep3. */
	uपूर्णांक16_t is_rep2[STATES];

	/*
	 * If 1, the repeated match has length of one byte. Otherwise
	 * the length is decoded from rep_len_decoder.
	 */
	uपूर्णांक16_t is_rep0_दीर्घ[STATES][POS_STATES_MAX];

	/*
	 * Probability tree क्रम the highest two bits of the match
	 * distance. There is a separate probability tree क्रम match
	 * lengths of 2 (i.e. MATCH_LEN_MIN), 3, 4, and [5, 273].
	 */
	uपूर्णांक16_t dist_slot[DIST_STATES][DIST_SLOTS];

	/*
	 * Probility trees क्रम additional bits क्रम match distance
	 * when the distance is in the range [4, 127].
	 */
	uपूर्णांक16_t dist_special[FULL_DISTANCES - DIST_MODEL_END];

	/*
	 * Probability tree क्रम the lowest four bits of a match
	 * distance that is equal to or greater than 128.
	 */
	uपूर्णांक16_t dist_align[ALIGN_SIZE];

	/* Length of a normal match */
	काष्ठा lzma_len_dec match_len_dec;

	/* Length of a repeated match */
	काष्ठा lzma_len_dec rep_len_dec;

	/* Probabilities of literals */
	uपूर्णांक16_t literal[LITERAL_CODERS_MAX][LITERAL_CODER_SIZE];
पूर्ण;

काष्ठा lzma2_dec अणु
	/* Position in xz_dec_lzma2_run(). */
	क्रमागत lzma2_seq अणु
		SEQ_CONTROL,
		SEQ_UNCOMPRESSED_1,
		SEQ_UNCOMPRESSED_2,
		SEQ_COMPRESSED_0,
		SEQ_COMPRESSED_1,
		SEQ_PROPERTIES,
		SEQ_LZMA_PREPARE,
		SEQ_LZMA_RUN,
		SEQ_COPY
	पूर्ण sequence;

	/* Next position after decoding the compressed size of the chunk. */
	क्रमागत lzma2_seq next_sequence;

	/* Uncompressed size of LZMA chunk (2 MiB at maximum) */
	uपूर्णांक32_t uncompressed;

	/*
	 * Compressed size of LZMA chunk or compressed/uncompressed
	 * size of uncompressed chunk (64 KiB at maximum)
	 */
	uपूर्णांक32_t compressed;

	/*
	 * True अगर dictionary reset is needed. This is false beक्रमe
	 * the first chunk (LZMA or uncompressed).
	 */
	bool need_dict_reset;

	/*
	 * True अगर new LZMA properties are needed. This is false
	 * beक्रमe the first LZMA chunk.
	 */
	bool need_props;
पूर्ण;

काष्ठा xz_dec_lzma2 अणु
	/*
	 * The order below is important on x86 to reduce code size and
	 * it shouldn't hurt on other platक्रमms. Everything up to and
	 * including lzma.pos_mask are in the first 128 bytes on x86-32,
	 * which allows using smaller inकाष्ठाions to access those
	 * variables. On x86-64, fewer variables fit पूर्णांकo the first 128
	 * bytes, but this is still the best order without sacrअगरicing
	 * the पढ़ोability by splitting the काष्ठाures.
	 */
	काष्ठा rc_dec rc;
	काष्ठा dictionary dict;
	काष्ठा lzma2_dec lzma2;
	काष्ठा lzma_dec lzma;

	/*
	 * Temporary buffer which holds small number of input bytes between
	 * decoder calls. See lzma2_lzma() क्रम details.
	 */
	काष्ठा अणु
		uपूर्णांक32_t size;
		uपूर्णांक8_t buf[3 * LZMA_IN_REQUIRED];
	पूर्ण temp;
पूर्ण;

/**************
 * Dictionary *
 **************/

/*
 * Reset the dictionary state. When in single-call mode, set up the beginning
 * of the dictionary to poपूर्णांक to the actual output buffer.
 */
अटल व्योम dict_reset(काष्ठा dictionary *dict, काष्ठा xz_buf *b)
अणु
	अगर (DEC_IS_SINGLE(dict->mode)) अणु
		dict->buf = b->out + b->out_pos;
		dict->end = b->out_size - b->out_pos;
	पूर्ण

	dict->start = 0;
	dict->pos = 0;
	dict->limit = 0;
	dict->full = 0;
पूर्ण

/* Set dictionary ग_लिखो limit */
अटल व्योम dict_limit(काष्ठा dictionary *dict, माप_प्रकार out_max)
अणु
	अगर (dict->end - dict->pos <= out_max)
		dict->limit = dict->end;
	अन्यथा
		dict->limit = dict->pos + out_max;
पूर्ण

/* Return true अगर at least one byte can be written पूर्णांकo the dictionary. */
अटल अंतरभूत bool dict_has_space(स्थिर काष्ठा dictionary *dict)
अणु
	वापस dict->pos < dict->limit;
पूर्ण

/*
 * Get a byte from the dictionary at the given distance. The distance is
 * assumed to valid, or as a special हाल, zero when the dictionary is
 * still empty. This special हाल is needed क्रम single-call decoding to
 * aव्योम writing a '\0' to the end of the destination buffer.
 */
अटल अंतरभूत uपूर्णांक32_t dict_get(स्थिर काष्ठा dictionary *dict, uपूर्णांक32_t dist)
अणु
	माप_प्रकार offset = dict->pos - dist - 1;

	अगर (dist >= dict->pos)
		offset += dict->end;

	वापस dict->full > 0 ? dict->buf[offset] : 0;
पूर्ण

/*
 * Put one byte पूर्णांकo the dictionary. It is assumed that there is space क्रम it.
 */
अटल अंतरभूत व्योम dict_put(काष्ठा dictionary *dict, uपूर्णांक8_t byte)
अणु
	dict->buf[dict->pos++] = byte;

	अगर (dict->full < dict->pos)
		dict->full = dict->pos;
पूर्ण

/*
 * Repeat given number of bytes from the given distance. If the distance is
 * invalid, false is वापसed. On success, true is वापसed and *len is
 * updated to indicate how many bytes were left to be repeated.
 */
अटल bool dict_repeat(काष्ठा dictionary *dict, uपूर्णांक32_t *len, uपूर्णांक32_t dist)
अणु
	माप_प्रकार back;
	uपूर्णांक32_t left;

	अगर (dist >= dict->full || dist >= dict->size)
		वापस false;

	left = min_t(माप_प्रकार, dict->limit - dict->pos, *len);
	*len -= left;

	back = dict->pos - dist - 1;
	अगर (dist >= dict->pos)
		back += dict->end;

	करो अणु
		dict->buf[dict->pos++] = dict->buf[back++];
		अगर (back == dict->end)
			back = 0;
	पूर्ण जबतक (--left > 0);

	अगर (dict->full < dict->pos)
		dict->full = dict->pos;

	वापस true;
पूर्ण

/* Copy uncompressed data as is from input to dictionary and output buffers. */
अटल व्योम dict_uncompressed(काष्ठा dictionary *dict, काष्ठा xz_buf *b,
			      uपूर्णांक32_t *left)
अणु
	माप_प्रकार copy_size;

	जबतक (*left > 0 && b->in_pos < b->in_size
			&& b->out_pos < b->out_size) अणु
		copy_size = min(b->in_size - b->in_pos,
				b->out_size - b->out_pos);
		अगर (copy_size > dict->end - dict->pos)
			copy_size = dict->end - dict->pos;
		अगर (copy_size > *left)
			copy_size = *left;

		*left -= copy_size;

		स_नकल(dict->buf + dict->pos, b->in + b->in_pos, copy_size);
		dict->pos += copy_size;

		अगर (dict->full < dict->pos)
			dict->full = dict->pos;

		अगर (DEC_IS_MULTI(dict->mode)) अणु
			अगर (dict->pos == dict->end)
				dict->pos = 0;

			स_नकल(b->out + b->out_pos, b->in + b->in_pos,
					copy_size);
		पूर्ण

		dict->start = dict->pos;

		b->out_pos += copy_size;
		b->in_pos += copy_size;
	पूर्ण
पूर्ण

/*
 * Flush pending data from dictionary to b->out. It is assumed that there is
 * enough space in b->out. This is guaranteed because caller uses dict_limit()
 * beक्रमe decoding data पूर्णांकo the dictionary.
 */
अटल uपूर्णांक32_t dict_flush(काष्ठा dictionary *dict, काष्ठा xz_buf *b)
अणु
	माप_प्रकार copy_size = dict->pos - dict->start;

	अगर (DEC_IS_MULTI(dict->mode)) अणु
		अगर (dict->pos == dict->end)
			dict->pos = 0;

		स_नकल(b->out + b->out_pos, dict->buf + dict->start,
				copy_size);
	पूर्ण

	dict->start = dict->pos;
	b->out_pos += copy_size;
	वापस copy_size;
पूर्ण

/*****************
 * Range decoder *
 *****************/

/* Reset the range decoder. */
अटल व्योम rc_reset(काष्ठा rc_dec *rc)
अणु
	rc->range = (uपूर्णांक32_t)-1;
	rc->code = 0;
	rc->init_bytes_left = RC_INIT_BYTES;
पूर्ण

/*
 * Read the first five initial bytes पूर्णांकo rc->code अगर they haven't been
 * पढ़ो alपढ़ोy. (Yes, the first byte माला_लो completely ignored.)
 */
अटल bool rc_पढ़ो_init(काष्ठा rc_dec *rc, काष्ठा xz_buf *b)
अणु
	जबतक (rc->init_bytes_left > 0) अणु
		अगर (b->in_pos == b->in_size)
			वापस false;

		rc->code = (rc->code << 8) + b->in[b->in_pos++];
		--rc->init_bytes_left;
	पूर्ण

	वापस true;
पूर्ण

/* Return true अगर there may not be enough input क्रम the next decoding loop. */
अटल अंतरभूत bool rc_limit_exceeded(स्थिर काष्ठा rc_dec *rc)
अणु
	वापस rc->in_pos > rc->in_limit;
पूर्ण

/*
 * Return true अगर it is possible (from poपूर्णांक of view of range decoder) that
 * we have reached the end of the LZMA chunk.
 */
अटल अंतरभूत bool rc_is_finished(स्थिर काष्ठा rc_dec *rc)
अणु
	वापस rc->code == 0;
पूर्ण

/* Read the next input byte अगर needed. */
अटल __always_अंतरभूत व्योम rc_normalize(काष्ठा rc_dec *rc)
अणु
	अगर (rc->range < RC_TOP_VALUE) अणु
		rc->range <<= RC_SHIFT_BITS;
		rc->code = (rc->code << RC_SHIFT_BITS) + rc->in[rc->in_pos++];
	पूर्ण
पूर्ण

/*
 * Decode one bit. In some versions, this function has been splitted in three
 * functions so that the compiler is supposed to be able to more easily aव्योम
 * an extra branch. In this particular version of the LZMA decoder, this
 * करोesn't seem to be a good idea (tested with GCC 3.3.6, 3.4.6, and 4.3.3
 * on x86). Using a non-splitted version results in nicer looking code too.
 *
 * NOTE: This must वापस an पूर्णांक. Do not make it वापस a bool or the speed
 * of the code generated by GCC 3.x decreases 10-15 %. (GCC 4.3 करोesn't care,
 * and it generates 10-20 % faster code than GCC 3.x from this file anyway.)
 */
अटल __always_अंतरभूत पूर्णांक rc_bit(काष्ठा rc_dec *rc, uपूर्णांक16_t *prob)
अणु
	uपूर्णांक32_t bound;
	पूर्णांक bit;

	rc_normalize(rc);
	bound = (rc->range >> RC_BIT_MODEL_TOTAL_BITS) * *prob;
	अगर (rc->code < bound) अणु
		rc->range = bound;
		*prob += (RC_BIT_MODEL_TOTAL - *prob) >> RC_MOVE_BITS;
		bit = 0;
	पूर्ण अन्यथा अणु
		rc->range -= bound;
		rc->code -= bound;
		*prob -= *prob >> RC_MOVE_BITS;
		bit = 1;
	पूर्ण

	वापस bit;
पूर्ण

/* Decode a bittree starting from the most signअगरicant bit. */
अटल __always_अंतरभूत uपूर्णांक32_t rc_bittree(काष्ठा rc_dec *rc,
					   uपूर्णांक16_t *probs, uपूर्णांक32_t limit)
अणु
	uपूर्णांक32_t symbol = 1;

	करो अणु
		अगर (rc_bit(rc, &probs[symbol]))
			symbol = (symbol << 1) + 1;
		अन्यथा
			symbol <<= 1;
	पूर्ण जबतक (symbol < limit);

	वापस symbol;
पूर्ण

/* Decode a bittree starting from the least signअगरicant bit. */
अटल __always_अंतरभूत व्योम rc_bittree_reverse(काष्ठा rc_dec *rc,
					       uपूर्णांक16_t *probs,
					       uपूर्णांक32_t *dest, uपूर्णांक32_t limit)
अणु
	uपूर्णांक32_t symbol = 1;
	uपूर्णांक32_t i = 0;

	करो अणु
		अगर (rc_bit(rc, &probs[symbol])) अणु
			symbol = (symbol << 1) + 1;
			*dest += 1 << i;
		पूर्ण अन्यथा अणु
			symbol <<= 1;
		पूर्ण
	पूर्ण जबतक (++i < limit);
पूर्ण

/* Decode direct bits (fixed fअगरty-fअगरty probability) */
अटल अंतरभूत व्योम rc_direct(काष्ठा rc_dec *rc, uपूर्णांक32_t *dest, uपूर्णांक32_t limit)
अणु
	uपूर्णांक32_t mask;

	करो अणु
		rc_normalize(rc);
		rc->range >>= 1;
		rc->code -= rc->range;
		mask = (uपूर्णांक32_t)0 - (rc->code >> 31);
		rc->code += rc->range & mask;
		*dest = (*dest << 1) + (mask + 1);
	पूर्ण जबतक (--limit > 0);
पूर्ण

/********
 * LZMA *
 ********/

/* Get poपूर्णांकer to literal coder probability array. */
अटल uपूर्णांक16_t *lzma_literal_probs(काष्ठा xz_dec_lzma2 *s)
अणु
	uपूर्णांक32_t prev_byte = dict_get(&s->dict, 0);
	uपूर्णांक32_t low = prev_byte >> (8 - s->lzma.lc);
	uपूर्णांक32_t high = (s->dict.pos & s->lzma.literal_pos_mask) << s->lzma.lc;
	वापस s->lzma.literal[low + high];
पूर्ण

/* Decode a literal (one 8-bit byte) */
अटल व्योम lzma_literal(काष्ठा xz_dec_lzma2 *s)
अणु
	uपूर्णांक16_t *probs;
	uपूर्णांक32_t symbol;
	uपूर्णांक32_t match_byte;
	uपूर्णांक32_t match_bit;
	uपूर्णांक32_t offset;
	uपूर्णांक32_t i;

	probs = lzma_literal_probs(s);

	अगर (lzma_state_is_literal(s->lzma.state)) अणु
		symbol = rc_bittree(&s->rc, probs, 0x100);
	पूर्ण अन्यथा अणु
		symbol = 1;
		match_byte = dict_get(&s->dict, s->lzma.rep0) << 1;
		offset = 0x100;

		करो अणु
			match_bit = match_byte & offset;
			match_byte <<= 1;
			i = offset + match_bit + symbol;

			अगर (rc_bit(&s->rc, &probs[i])) अणु
				symbol = (symbol << 1) + 1;
				offset &= match_bit;
			पूर्ण अन्यथा अणु
				symbol <<= 1;
				offset &= ~match_bit;
			पूर्ण
		पूर्ण जबतक (symbol < 0x100);
	पूर्ण

	dict_put(&s->dict, (uपूर्णांक8_t)symbol);
	lzma_state_literal(&s->lzma.state);
पूर्ण

/* Decode the length of the match पूर्णांकo s->lzma.len. */
अटल व्योम lzma_len(काष्ठा xz_dec_lzma2 *s, काष्ठा lzma_len_dec *l,
		     uपूर्णांक32_t pos_state)
अणु
	uपूर्णांक16_t *probs;
	uपूर्णांक32_t limit;

	अगर (!rc_bit(&s->rc, &l->choice)) अणु
		probs = l->low[pos_state];
		limit = LEN_LOW_SYMBOLS;
		s->lzma.len = MATCH_LEN_MIN;
	पूर्ण अन्यथा अणु
		अगर (!rc_bit(&s->rc, &l->choice2)) अणु
			probs = l->mid[pos_state];
			limit = LEN_MID_SYMBOLS;
			s->lzma.len = MATCH_LEN_MIN + LEN_LOW_SYMBOLS;
		पूर्ण अन्यथा अणु
			probs = l->high;
			limit = LEN_HIGH_SYMBOLS;
			s->lzma.len = MATCH_LEN_MIN + LEN_LOW_SYMBOLS
					+ LEN_MID_SYMBOLS;
		पूर्ण
	पूर्ण

	s->lzma.len += rc_bittree(&s->rc, probs, limit) - limit;
पूर्ण

/* Decode a match. The distance will be stored in s->lzma.rep0. */
अटल व्योम lzma_match(काष्ठा xz_dec_lzma2 *s, uपूर्णांक32_t pos_state)
अणु
	uपूर्णांक16_t *probs;
	uपूर्णांक32_t dist_slot;
	uपूर्णांक32_t limit;

	lzma_state_match(&s->lzma.state);

	s->lzma.rep3 = s->lzma.rep2;
	s->lzma.rep2 = s->lzma.rep1;
	s->lzma.rep1 = s->lzma.rep0;

	lzma_len(s, &s->lzma.match_len_dec, pos_state);

	probs = s->lzma.dist_slot[lzma_get_dist_state(s->lzma.len)];
	dist_slot = rc_bittree(&s->rc, probs, DIST_SLOTS) - DIST_SLOTS;

	अगर (dist_slot < DIST_MODEL_START) अणु
		s->lzma.rep0 = dist_slot;
	पूर्ण अन्यथा अणु
		limit = (dist_slot >> 1) - 1;
		s->lzma.rep0 = 2 + (dist_slot & 1);

		अगर (dist_slot < DIST_MODEL_END) अणु
			s->lzma.rep0 <<= limit;
			probs = s->lzma.dist_special + s->lzma.rep0
					- dist_slot - 1;
			rc_bittree_reverse(&s->rc, probs,
					&s->lzma.rep0, limit);
		पूर्ण अन्यथा अणु
			rc_direct(&s->rc, &s->lzma.rep0, limit - ALIGN_BITS);
			s->lzma.rep0 <<= ALIGN_BITS;
			rc_bittree_reverse(&s->rc, s->lzma.dist_align,
					&s->lzma.rep0, ALIGN_BITS);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Decode a repeated match. The distance is one of the four most recently
 * seen matches. The distance will be stored in s->lzma.rep0.
 */
अटल व्योम lzma_rep_match(काष्ठा xz_dec_lzma2 *s, uपूर्णांक32_t pos_state)
अणु
	uपूर्णांक32_t पंचांगp;

	अगर (!rc_bit(&s->rc, &s->lzma.is_rep0[s->lzma.state])) अणु
		अगर (!rc_bit(&s->rc, &s->lzma.is_rep0_दीर्घ[
				s->lzma.state][pos_state])) अणु
			lzma_state_लघु_rep(&s->lzma.state);
			s->lzma.len = 1;
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!rc_bit(&s->rc, &s->lzma.is_rep1[s->lzma.state])) अणु
			पंचांगp = s->lzma.rep1;
		पूर्ण अन्यथा अणु
			अगर (!rc_bit(&s->rc, &s->lzma.is_rep2[s->lzma.state])) अणु
				पंचांगp = s->lzma.rep2;
			पूर्ण अन्यथा अणु
				पंचांगp = s->lzma.rep3;
				s->lzma.rep3 = s->lzma.rep2;
			पूर्ण

			s->lzma.rep2 = s->lzma.rep1;
		पूर्ण

		s->lzma.rep1 = s->lzma.rep0;
		s->lzma.rep0 = पंचांगp;
	पूर्ण

	lzma_state_दीर्घ_rep(&s->lzma.state);
	lzma_len(s, &s->lzma.rep_len_dec, pos_state);
पूर्ण

/* LZMA decoder core */
अटल bool lzma_मुख्य(काष्ठा xz_dec_lzma2 *s)
अणु
	uपूर्णांक32_t pos_state;

	/*
	 * If the dictionary was reached during the previous call, try to
	 * finish the possibly pending repeat in the dictionary.
	 */
	अगर (dict_has_space(&s->dict) && s->lzma.len > 0)
		dict_repeat(&s->dict, &s->lzma.len, s->lzma.rep0);

	/*
	 * Decode more LZMA symbols. One iteration may consume up to
	 * LZMA_IN_REQUIRED - 1 bytes.
	 */
	जबतक (dict_has_space(&s->dict) && !rc_limit_exceeded(&s->rc)) अणु
		pos_state = s->dict.pos & s->lzma.pos_mask;

		अगर (!rc_bit(&s->rc, &s->lzma.is_match[
				s->lzma.state][pos_state])) अणु
			lzma_literal(s);
		पूर्ण अन्यथा अणु
			अगर (rc_bit(&s->rc, &s->lzma.is_rep[s->lzma.state]))
				lzma_rep_match(s, pos_state);
			अन्यथा
				lzma_match(s, pos_state);

			अगर (!dict_repeat(&s->dict, &s->lzma.len, s->lzma.rep0))
				वापस false;
		पूर्ण
	पूर्ण

	/*
	 * Having the range decoder always normalized when we are outside
	 * this function makes it easier to correctly handle end of the chunk.
	 */
	rc_normalize(&s->rc);

	वापस true;
पूर्ण

/*
 * Reset the LZMA decoder and range decoder state. Dictionary is nore reset
 * here, because LZMA state may be reset without resetting the dictionary.
 */
अटल व्योम lzma_reset(काष्ठा xz_dec_lzma2 *s)
अणु
	uपूर्णांक16_t *probs;
	माप_प्रकार i;

	s->lzma.state = STATE_LIT_LIT;
	s->lzma.rep0 = 0;
	s->lzma.rep1 = 0;
	s->lzma.rep2 = 0;
	s->lzma.rep3 = 0;

	/*
	 * All probabilities are initialized to the same value. This hack
	 * makes the code smaller by aव्योमing a separate loop क्रम each
	 * probability array.
	 *
	 * This could be optimized so that only that part of literal
	 * probabilities that are actually required. In the common हाल
	 * we would ग_लिखो 12 KiB less.
	 */
	probs = s->lzma.is_match[0];
	क्रम (i = 0; i < PROBS_TOTAL; ++i)
		probs[i] = RC_BIT_MODEL_TOTAL / 2;

	rc_reset(&s->rc);
पूर्ण

/*
 * Decode and validate LZMA properties (lc/lp/pb) and calculate the bit masks
 * from the decoded lp and pb values. On success, the LZMA decoder state is
 * reset and true is वापसed.
 */
अटल bool lzma_props(काष्ठा xz_dec_lzma2 *s, uपूर्णांक8_t props)
अणु
	अगर (props > (4 * 5 + 4) * 9 + 8)
		वापस false;

	s->lzma.pos_mask = 0;
	जबतक (props >= 9 * 5) अणु
		props -= 9 * 5;
		++s->lzma.pos_mask;
	पूर्ण

	s->lzma.pos_mask = (1 << s->lzma.pos_mask) - 1;

	s->lzma.literal_pos_mask = 0;
	जबतक (props >= 9) अणु
		props -= 9;
		++s->lzma.literal_pos_mask;
	पूर्ण

	s->lzma.lc = props;

	अगर (s->lzma.lc + s->lzma.literal_pos_mask > 4)
		वापस false;

	s->lzma.literal_pos_mask = (1 << s->lzma.literal_pos_mask) - 1;

	lzma_reset(s);

	वापस true;
पूर्ण

/*********
 * LZMA2 *
 *********/

/*
 * The LZMA decoder assumes that अगर the input limit (s->rc.in_limit) hasn't
 * been exceeded, it is safe to पढ़ो up to LZMA_IN_REQUIRED bytes. This
 * wrapper function takes care of making the LZMA decoder's assumption safe.
 *
 * As दीर्घ as there is plenty of input left to be decoded in the current LZMA
 * chunk, we decode directly from the caller-supplied input buffer until
 * there's LZMA_IN_REQUIRED bytes left. Those reमुख्यing bytes are copied पूर्णांकo
 * s->temp.buf, which (hopefully) माला_लो filled on the next call to this
 * function. We decode a few bytes from the temporary buffer so that we can
 * जारी decoding from the caller-supplied input buffer again.
 */
अटल bool lzma2_lzma(काष्ठा xz_dec_lzma2 *s, काष्ठा xz_buf *b)
अणु
	माप_प्रकार in_avail;
	uपूर्णांक32_t पंचांगp;

	in_avail = b->in_size - b->in_pos;
	अगर (s->temp.size > 0 || s->lzma2.compressed == 0) अणु
		पंचांगp = 2 * LZMA_IN_REQUIRED - s->temp.size;
		अगर (पंचांगp > s->lzma2.compressed - s->temp.size)
			पंचांगp = s->lzma2.compressed - s->temp.size;
		अगर (पंचांगp > in_avail)
			पंचांगp = in_avail;

		स_नकल(s->temp.buf + s->temp.size, b->in + b->in_pos, पंचांगp);

		अगर (s->temp.size + पंचांगp == s->lzma2.compressed) अणु
			memzero(s->temp.buf + s->temp.size + पंचांगp,
					माप(s->temp.buf)
						- s->temp.size - पंचांगp);
			s->rc.in_limit = s->temp.size + पंचांगp;
		पूर्ण अन्यथा अगर (s->temp.size + पंचांगp < LZMA_IN_REQUIRED) अणु
			s->temp.size += पंचांगp;
			b->in_pos += पंचांगp;
			वापस true;
		पूर्ण अन्यथा अणु
			s->rc.in_limit = s->temp.size + पंचांगp - LZMA_IN_REQUIRED;
		पूर्ण

		s->rc.in = s->temp.buf;
		s->rc.in_pos = 0;

		अगर (!lzma_मुख्य(s) || s->rc.in_pos > s->temp.size + पंचांगp)
			वापस false;

		s->lzma2.compressed -= s->rc.in_pos;

		अगर (s->rc.in_pos < s->temp.size) अणु
			s->temp.size -= s->rc.in_pos;
			स_हटाओ(s->temp.buf, s->temp.buf + s->rc.in_pos,
					s->temp.size);
			वापस true;
		पूर्ण

		b->in_pos += s->rc.in_pos - s->temp.size;
		s->temp.size = 0;
	पूर्ण

	in_avail = b->in_size - b->in_pos;
	अगर (in_avail >= LZMA_IN_REQUIRED) अणु
		s->rc.in = b->in;
		s->rc.in_pos = b->in_pos;

		अगर (in_avail >= s->lzma2.compressed + LZMA_IN_REQUIRED)
			s->rc.in_limit = b->in_pos + s->lzma2.compressed;
		अन्यथा
			s->rc.in_limit = b->in_size - LZMA_IN_REQUIRED;

		अगर (!lzma_मुख्य(s))
			वापस false;

		in_avail = s->rc.in_pos - b->in_pos;
		अगर (in_avail > s->lzma2.compressed)
			वापस false;

		s->lzma2.compressed -= in_avail;
		b->in_pos = s->rc.in_pos;
	पूर्ण

	in_avail = b->in_size - b->in_pos;
	अगर (in_avail < LZMA_IN_REQUIRED) अणु
		अगर (in_avail > s->lzma2.compressed)
			in_avail = s->lzma2.compressed;

		स_नकल(s->temp.buf, b->in + b->in_pos, in_avail);
		s->temp.size = in_avail;
		b->in_pos += in_avail;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Take care of the LZMA2 control layer, and क्रमward the job of actual LZMA
 * decoding or copying of uncompressed chunks to other functions.
 */
XZ_EXTERN क्रमागत xz_ret xz_dec_lzma2_run(काष्ठा xz_dec_lzma2 *s,
				       काष्ठा xz_buf *b)
अणु
	uपूर्णांक32_t पंचांगp;

	जबतक (b->in_pos < b->in_size || s->lzma2.sequence == SEQ_LZMA_RUN) अणु
		चयन (s->lzma2.sequence) अणु
		हाल SEQ_CONTROL:
			/*
			 * LZMA2 control byte
			 *
			 * Exact values:
			 *   0x00   End marker
			 *   0x01   Dictionary reset followed by
			 *          an uncompressed chunk
			 *   0x02   Uncompressed chunk (no dictionary reset)
			 *
			 * Highest three bits (s->control & 0xE0):
			 *   0xE0   Dictionary reset, new properties and state
			 *          reset, followed by LZMA compressed chunk
			 *   0xC0   New properties and state reset, followed
			 *          by LZMA compressed chunk (no dictionary
			 *          reset)
			 *   0xA0   State reset using old properties,
			 *          followed by LZMA compressed chunk (no
			 *          dictionary reset)
			 *   0x80   LZMA chunk (no dictionary or state reset)
			 *
			 * For LZMA compressed chunks, the lowest five bits
			 * (s->control & 1F) are the highest bits of the
			 * uncompressed size (bits 16-20).
			 *
			 * A new LZMA2 stream must begin with a dictionary
			 * reset. The first LZMA chunk must set new
			 * properties and reset the LZMA state.
			 *
			 * Values that करोn't match anything described above
			 * are invalid and we वापस XZ_DATA_ERROR.
			 */
			पंचांगp = b->in[b->in_pos++];

			अगर (पंचांगp == 0x00)
				वापस XZ_STREAM_END;

			अगर (पंचांगp >= 0xE0 || पंचांगp == 0x01) अणु
				s->lzma2.need_props = true;
				s->lzma2.need_dict_reset = false;
				dict_reset(&s->dict, b);
			पूर्ण अन्यथा अगर (s->lzma2.need_dict_reset) अणु
				वापस XZ_DATA_ERROR;
			पूर्ण

			अगर (पंचांगp >= 0x80) अणु
				s->lzma2.uncompressed = (पंचांगp & 0x1F) << 16;
				s->lzma2.sequence = SEQ_UNCOMPRESSED_1;

				अगर (पंचांगp >= 0xC0) अणु
					/*
					 * When there are new properties,
					 * state reset is करोne at
					 * SEQ_PROPERTIES.
					 */
					s->lzma2.need_props = false;
					s->lzma2.next_sequence
							= SEQ_PROPERTIES;

				पूर्ण अन्यथा अगर (s->lzma2.need_props) अणु
					वापस XZ_DATA_ERROR;

				पूर्ण अन्यथा अणु
					s->lzma2.next_sequence
							= SEQ_LZMA_PREPARE;
					अगर (पंचांगp >= 0xA0)
						lzma_reset(s);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (पंचांगp > 0x02)
					वापस XZ_DATA_ERROR;

				s->lzma2.sequence = SEQ_COMPRESSED_0;
				s->lzma2.next_sequence = SEQ_COPY;
			पूर्ण

			अवरोध;

		हाल SEQ_UNCOMPRESSED_1:
			s->lzma2.uncompressed
					+= (uपूर्णांक32_t)b->in[b->in_pos++] << 8;
			s->lzma2.sequence = SEQ_UNCOMPRESSED_2;
			अवरोध;

		हाल SEQ_UNCOMPRESSED_2:
			s->lzma2.uncompressed
					+= (uपूर्णांक32_t)b->in[b->in_pos++] + 1;
			s->lzma2.sequence = SEQ_COMPRESSED_0;
			अवरोध;

		हाल SEQ_COMPRESSED_0:
			s->lzma2.compressed
					= (uपूर्णांक32_t)b->in[b->in_pos++] << 8;
			s->lzma2.sequence = SEQ_COMPRESSED_1;
			अवरोध;

		हाल SEQ_COMPRESSED_1:
			s->lzma2.compressed
					+= (uपूर्णांक32_t)b->in[b->in_pos++] + 1;
			s->lzma2.sequence = s->lzma2.next_sequence;
			अवरोध;

		हाल SEQ_PROPERTIES:
			अगर (!lzma_props(s, b->in[b->in_pos++]))
				वापस XZ_DATA_ERROR;

			s->lzma2.sequence = SEQ_LZMA_PREPARE;

			fallthrough;

		हाल SEQ_LZMA_PREPARE:
			अगर (s->lzma2.compressed < RC_INIT_BYTES)
				वापस XZ_DATA_ERROR;

			अगर (!rc_पढ़ो_init(&s->rc, b))
				वापस XZ_OK;

			s->lzma2.compressed -= RC_INIT_BYTES;
			s->lzma2.sequence = SEQ_LZMA_RUN;

			fallthrough;

		हाल SEQ_LZMA_RUN:
			/*
			 * Set dictionary limit to indicate how much we want
			 * to be encoded at maximum. Decode new data पूर्णांकo the
			 * dictionary. Flush the new data from dictionary to
			 * b->out. Check अगर we finished decoding this chunk.
			 * In हाल the dictionary got full but we didn't fill
			 * the output buffer yet, we may run this loop
			 * multiple बार without changing s->lzma2.sequence.
			 */
			dict_limit(&s->dict, min_t(माप_प्रकार,
					b->out_size - b->out_pos,
					s->lzma2.uncompressed));
			अगर (!lzma2_lzma(s, b))
				वापस XZ_DATA_ERROR;

			s->lzma2.uncompressed -= dict_flush(&s->dict, b);

			अगर (s->lzma2.uncompressed == 0) अणु
				अगर (s->lzma2.compressed > 0 || s->lzma.len > 0
						|| !rc_is_finished(&s->rc))
					वापस XZ_DATA_ERROR;

				rc_reset(&s->rc);
				s->lzma2.sequence = SEQ_CONTROL;

			पूर्ण अन्यथा अगर (b->out_pos == b->out_size
					|| (b->in_pos == b->in_size
						&& s->temp.size
						< s->lzma2.compressed)) अणु
				वापस XZ_OK;
			पूर्ण

			अवरोध;

		हाल SEQ_COPY:
			dict_uncompressed(&s->dict, b, &s->lzma2.compressed);
			अगर (s->lzma2.compressed > 0)
				वापस XZ_OK;

			s->lzma2.sequence = SEQ_CONTROL;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस XZ_OK;
पूर्ण

XZ_EXTERN काष्ठा xz_dec_lzma2 *xz_dec_lzma2_create(क्रमागत xz_mode mode,
						   uपूर्णांक32_t dict_max)
अणु
	काष्ठा xz_dec_lzma2 *s = kदो_स्मृति(माप(*s), GFP_KERNEL);
	अगर (s == शून्य)
		वापस शून्य;

	s->dict.mode = mode;
	s->dict.size_max = dict_max;

	अगर (DEC_IS_PREALLOC(mode)) अणु
		s->dict.buf = vदो_स्मृति(dict_max);
		अगर (s->dict.buf == शून्य) अणु
			kमुक्त(s);
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (DEC_IS_DYNALLOC(mode)) अणु
		s->dict.buf = शून्य;
		s->dict.allocated = 0;
	पूर्ण

	वापस s;
पूर्ण

XZ_EXTERN क्रमागत xz_ret xz_dec_lzma2_reset(काष्ठा xz_dec_lzma2 *s, uपूर्णांक8_t props)
अणु
	/* This limits dictionary size to 3 GiB to keep parsing simpler. */
	अगर (props > 39)
		वापस XZ_OPTIONS_ERROR;

	s->dict.size = 2 + (props & 1);
	s->dict.size <<= (props >> 1) + 11;

	अगर (DEC_IS_MULTI(s->dict.mode)) अणु
		अगर (s->dict.size > s->dict.size_max)
			वापस XZ_MEMLIMIT_ERROR;

		s->dict.end = s->dict.size;

		अगर (DEC_IS_DYNALLOC(s->dict.mode)) अणु
			अगर (s->dict.allocated < s->dict.size) अणु
				s->dict.allocated = s->dict.size;
				vमुक्त(s->dict.buf);
				s->dict.buf = vदो_स्मृति(s->dict.size);
				अगर (s->dict.buf == शून्य) अणु
					s->dict.allocated = 0;
					वापस XZ_MEM_ERROR;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	s->lzma.len = 0;

	s->lzma2.sequence = SEQ_CONTROL;
	s->lzma2.need_dict_reset = true;

	s->temp.size = 0;

	वापस XZ_OK;
पूर्ण

XZ_EXTERN व्योम xz_dec_lzma2_end(काष्ठा xz_dec_lzma2 *s)
अणु
	अगर (DEC_IS_MULTI(s->dict.mode))
		vमुक्त(s->dict.buf);

	kमुक्त(s);
पूर्ण
