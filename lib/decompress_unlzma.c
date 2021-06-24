<शैली गुरु>
/* Lzma decompressor क्रम Linux kernel. Shamelessly snarfed
 *from busybox 1.1.1
 *
 *Linux kernel adaptation
 *Copyright (C) 2006  Alain < alain@knaff.lu >
 *
 *Based on small lzma deflate implementation/Small range coder
 *implementation क्रम lzma.
 *Copyright (C) 2006  Aurelien Jacobs < aurel@gnuage.org >
 *
 *Based on LzmaDecode.c from the LZMA SDK 4.22 (https://www.7-zip.org/)
 *Copyright (C) 1999-2005  Igor Pavlov
 *
 *Copyrights of the parts, see headers below.
 *
 *
 *This program is मुक्त software; you can redistribute it and/or
 *modअगरy it under the terms of the GNU Lesser General Public
 *License as published by the Free Software Foundation; either
 *version 2.1 of the License, or (at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *Lesser General Public License क्रम more details.
 *
 *You should have received a copy of the GNU Lesser General Public
 *License aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA  02110-1301  USA
 */

#अगर_घोषित STATIC
#घोषणा PREBOOT
#अन्यथा
#समावेश <linux/decompress/unlzma.h>
#पूर्ण_अगर /* STATIC */

#समावेश <linux/decompress/mm.h>

#घोषणा	MIN(a, b) (((a) < (b)) ? (a) : (b))

अटल दीर्घ दीर्घ INIT पढ़ो_पूर्णांक(अचिन्हित अक्षर *ptr, पूर्णांक size)
अणु
	पूर्णांक i;
	दीर्घ दीर्घ ret = 0;

	क्रम (i = 0; i < size; i++)
		ret = (ret << 8) | ptr[size-i-1];
	वापस ret;
पूर्ण

#घोषणा ENDIAN_CONVERT(x) \
  x = (typeof(x))पढ़ो_पूर्णांक((अचिन्हित अक्षर *)&x, माप(x))


/* Small range coder implementation क्रम lzma.
 *Copyright (C) 2006  Aurelien Jacobs < aurel@gnuage.org >
 *
 *Based on LzmaDecode.c from the LZMA SDK 4.22 (https://www.7-zip.org/)
 *Copyright (c) 1999-2005  Igor Pavlov
 */

#समावेश <linux/compiler.h>

#घोषणा LZMA_IOBUF_SIZE	0x10000

काष्ठा rc अणु
	दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ);
	uपूर्णांक8_t *ptr;
	uपूर्णांक8_t *buffer;
	uपूर्णांक8_t *buffer_end;
	दीर्घ buffer_size;
	uपूर्णांक32_t code;
	uपूर्णांक32_t range;
	uपूर्णांक32_t bound;
	व्योम (*error)(अक्षर *);
पूर्ण;


#घोषणा RC_TOP_BITS 24
#घोषणा RC_MOVE_BITS 5
#घोषणा RC_MODEL_TOTAL_BITS 11


अटल दीर्घ INIT nofill(व्योम *buffer, अचिन्हित दीर्घ len)
अणु
	वापस -1;
पूर्ण

/* Called twice: once at startup and once in rc_normalize() */
अटल व्योम INIT rc_पढ़ो(काष्ठा rc *rc)
अणु
	rc->buffer_size = rc->fill((अक्षर *)rc->buffer, LZMA_IOBUF_SIZE);
	अगर (rc->buffer_size <= 0)
		rc->error("unexpected EOF");
	rc->ptr = rc->buffer;
	rc->buffer_end = rc->buffer + rc->buffer_size;
पूर्ण

/* Called once */
अटल अंतरभूत व्योम INIT rc_init(काष्ठा rc *rc,
				       दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ),
				       अक्षर *buffer, दीर्घ buffer_size)
अणु
	अगर (fill)
		rc->fill = fill;
	अन्यथा
		rc->fill = nofill;
	rc->buffer = (uपूर्णांक8_t *)buffer;
	rc->buffer_size = buffer_size;
	rc->buffer_end = rc->buffer + rc->buffer_size;
	rc->ptr = rc->buffer;

	rc->code = 0;
	rc->range = 0xFFFFFFFF;
पूर्ण

अटल अंतरभूत व्योम INIT rc_init_code(काष्ठा rc *rc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		अगर (rc->ptr >= rc->buffer_end)
			rc_पढ़ो(rc);
		rc->code = (rc->code << 8) | *rc->ptr++;
	पूर्ण
पूर्ण


/* Called twice, but one callsite is in अंतरभूत'd rc_is_bit_0_helper() */
अटल व्योम INIT rc_करो_normalize(काष्ठा rc *rc)
अणु
	अगर (rc->ptr >= rc->buffer_end)
		rc_पढ़ो(rc);
	rc->range <<= 8;
	rc->code = (rc->code << 8) | *rc->ptr++;
पूर्ण
अटल अंतरभूत व्योम INIT rc_normalize(काष्ठा rc *rc)
अणु
	अगर (rc->range < (1 << RC_TOP_BITS))
		rc_करो_normalize(rc);
पूर्ण

/* Called 9 बार */
/* Why rc_is_bit_0_helper exists?
 *Because we want to always expose (rc->code < rc->bound) to optimizer
 */
अटल अंतरभूत uपूर्णांक32_t INIT rc_is_bit_0_helper(काष्ठा rc *rc, uपूर्णांक16_t *p)
अणु
	rc_normalize(rc);
	rc->bound = *p * (rc->range >> RC_MODEL_TOTAL_BITS);
	वापस rc->bound;
पूर्ण
अटल अंतरभूत पूर्णांक INIT rc_is_bit_0(काष्ठा rc *rc, uपूर्णांक16_t *p)
अणु
	uपूर्णांक32_t t = rc_is_bit_0_helper(rc, p);
	वापस rc->code < t;
पूर्ण

/* Called ~10 बार, but very small, thus अंतरभूतd */
अटल अंतरभूत व्योम INIT rc_update_bit_0(काष्ठा rc *rc, uपूर्णांक16_t *p)
अणु
	rc->range = rc->bound;
	*p += ((1 << RC_MODEL_TOTAL_BITS) - *p) >> RC_MOVE_BITS;
पूर्ण
अटल अंतरभूत व्योम INIT rc_update_bit_1(काष्ठा rc *rc, uपूर्णांक16_t *p)
अणु
	rc->range -= rc->bound;
	rc->code -= rc->bound;
	*p -= *p >> RC_MOVE_BITS;
पूर्ण

/* Called 4 बार in unlzma loop */
अटल पूर्णांक INIT rc_get_bit(काष्ठा rc *rc, uपूर्णांक16_t *p, पूर्णांक *symbol)
अणु
	अगर (rc_is_bit_0(rc, p)) अणु
		rc_update_bit_0(rc, p);
		*symbol *= 2;
		वापस 0;
	पूर्ण अन्यथा अणु
		rc_update_bit_1(rc, p);
		*symbol = *symbol * 2 + 1;
		वापस 1;
	पूर्ण
पूर्ण

/* Called once */
अटल अंतरभूत पूर्णांक INIT rc_direct_bit(काष्ठा rc *rc)
अणु
	rc_normalize(rc);
	rc->range >>= 1;
	अगर (rc->code >= rc->range) अणु
		rc->code -= rc->range;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Called twice */
अटल अंतरभूत व्योम INIT
rc_bit_tree_decode(काष्ठा rc *rc, uपूर्णांक16_t *p, पूर्णांक num_levels, पूर्णांक *symbol)
अणु
	पूर्णांक i = num_levels;

	*symbol = 1;
	जबतक (i--)
		rc_get_bit(rc, p + *symbol, symbol);
	*symbol -= 1 << num_levels;
पूर्ण


/*
 * Small lzma deflate implementation.
 * Copyright (C) 2006  Aurelien Jacobs < aurel@gnuage.org >
 *
 * Based on LzmaDecode.c from the LZMA SDK 4.22 (https://www.7-zip.org/)
 * Copyright (C) 1999-2005  Igor Pavlov
 */


काष्ठा lzma_header अणु
	uपूर्णांक8_t pos;
	uपूर्णांक32_t dict_size;
	uपूर्णांक64_t dst_size;
पूर्ण __attribute__ ((packed)) ;


#घोषणा LZMA_BASE_SIZE 1846
#घोषणा LZMA_LIT_SIZE 768

#घोषणा LZMA_NUM_POS_BITS_MAX 4

#घोषणा LZMA_LEN_NUM_LOW_BITS 3
#घोषणा LZMA_LEN_NUM_MID_BITS 3
#घोषणा LZMA_LEN_NUM_HIGH_BITS 8

#घोषणा LZMA_LEN_CHOICE 0
#घोषणा LZMA_LEN_CHOICE_2 (LZMA_LEN_CHOICE + 1)
#घोषणा LZMA_LEN_LOW (LZMA_LEN_CHOICE_2 + 1)
#घोषणा LZMA_LEN_MID (LZMA_LEN_LOW \
		      + (1 << (LZMA_NUM_POS_BITS_MAX + LZMA_LEN_NUM_LOW_BITS)))
#घोषणा LZMA_LEN_HIGH (LZMA_LEN_MID \
		       +(1 << (LZMA_NUM_POS_BITS_MAX + LZMA_LEN_NUM_MID_BITS)))
#घोषणा LZMA_NUM_LEN_PROBS (LZMA_LEN_HIGH + (1 << LZMA_LEN_NUM_HIGH_BITS))

#घोषणा LZMA_NUM_STATES 12
#घोषणा LZMA_NUM_LIT_STATES 7

#घोषणा LZMA_START_POS_MODEL_INDEX 4
#घोषणा LZMA_END_POS_MODEL_INDEX 14
#घोषणा LZMA_NUM_FULL_DISTANCES (1 << (LZMA_END_POS_MODEL_INDEX >> 1))

#घोषणा LZMA_NUM_POS_SLOT_BITS 6
#घोषणा LZMA_NUM_LEN_TO_POS_STATES 4

#घोषणा LZMA_NUM_ALIGN_BITS 4

#घोषणा LZMA_MATCH_MIN_LEN 2

#घोषणा LZMA_IS_MATCH 0
#घोषणा LZMA_IS_REP (LZMA_IS_MATCH + (LZMA_NUM_STATES << LZMA_NUM_POS_BITS_MAX))
#घोषणा LZMA_IS_REP_G0 (LZMA_IS_REP + LZMA_NUM_STATES)
#घोषणा LZMA_IS_REP_G1 (LZMA_IS_REP_G0 + LZMA_NUM_STATES)
#घोषणा LZMA_IS_REP_G2 (LZMA_IS_REP_G1 + LZMA_NUM_STATES)
#घोषणा LZMA_IS_REP_0_LONG (LZMA_IS_REP_G2 + LZMA_NUM_STATES)
#घोषणा LZMA_POS_SLOT (LZMA_IS_REP_0_LONG \
		       + (LZMA_NUM_STATES << LZMA_NUM_POS_BITS_MAX))
#घोषणा LZMA_SPEC_POS (LZMA_POS_SLOT \
		       +(LZMA_NUM_LEN_TO_POS_STATES << LZMA_NUM_POS_SLOT_BITS))
#घोषणा LZMA_ALIGN (LZMA_SPEC_POS \
		    + LZMA_NUM_FULL_DISTANCES - LZMA_END_POS_MODEL_INDEX)
#घोषणा LZMA_LEN_CODER (LZMA_ALIGN + (1 << LZMA_NUM_ALIGN_BITS))
#घोषणा LZMA_REP_LEN_CODER (LZMA_LEN_CODER + LZMA_NUM_LEN_PROBS)
#घोषणा LZMA_LITERAL (LZMA_REP_LEN_CODER + LZMA_NUM_LEN_PROBS)


काष्ठा ग_लिखोr अणु
	uपूर्णांक8_t *buffer;
	uपूर्णांक8_t previous_byte;
	माप_प्रकार buffer_pos;
	पूर्णांक bufsize;
	माप_प्रकार global_pos;
	दीर्घ (*flush)(व्योम*, अचिन्हित दीर्घ);
	काष्ठा lzma_header *header;
पूर्ण;

काष्ठा cstate अणु
	पूर्णांक state;
	uपूर्णांक32_t rep0, rep1, rep2, rep3;
पूर्ण;

अटल अंतरभूत माप_प्रकार INIT get_pos(काष्ठा ग_लिखोr *wr)
अणु
	वापस
		wr->global_pos + wr->buffer_pos;
पूर्ण

अटल अंतरभूत uपूर्णांक8_t INIT peek_old_byte(काष्ठा ग_लिखोr *wr,
						uपूर्णांक32_t offs)
अणु
	अगर (!wr->flush) अणु
		पूर्णांक32_t pos;
		जबतक (offs > wr->header->dict_size)
			offs -= wr->header->dict_size;
		pos = wr->buffer_pos - offs;
		वापस wr->buffer[pos];
	पूर्ण अन्यथा अणु
		uपूर्णांक32_t pos = wr->buffer_pos - offs;
		जबतक (pos >= wr->header->dict_size)
			pos += wr->header->dict_size;
		वापस wr->buffer[pos];
	पूर्ण

पूर्ण

अटल अंतरभूत पूर्णांक INIT ग_लिखो_byte(काष्ठा ग_लिखोr *wr, uपूर्णांक8_t byte)
अणु
	wr->buffer[wr->buffer_pos++] = wr->previous_byte = byte;
	अगर (wr->flush && wr->buffer_pos == wr->header->dict_size) अणु
		wr->buffer_pos = 0;
		wr->global_pos += wr->header->dict_size;
		अगर (wr->flush((अक्षर *)wr->buffer, wr->header->dict_size)
				!= wr->header->dict_size)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण


अटल अंतरभूत पूर्णांक INIT copy_byte(काष्ठा ग_लिखोr *wr, uपूर्णांक32_t offs)
अणु
	वापस ग_लिखो_byte(wr, peek_old_byte(wr, offs));
पूर्ण

अटल अंतरभूत पूर्णांक INIT copy_bytes(काष्ठा ग_लिखोr *wr,
					 uपूर्णांक32_t rep0, पूर्णांक len)
अणु
	करो अणु
		अगर (copy_byte(wr, rep0))
			वापस -1;
		len--;
	पूर्ण जबतक (len != 0 && wr->buffer_pos < wr->header->dst_size);

	वापस len;
पूर्ण

अटल अंतरभूत पूर्णांक INIT process_bit0(काष्ठा ग_लिखोr *wr, काष्ठा rc *rc,
				     काष्ठा cstate *cst, uपूर्णांक16_t *p,
				     पूर्णांक pos_state, uपूर्णांक16_t *prob,
				     पूर्णांक lc, uपूर्णांक32_t literal_pos_mask) अणु
	पूर्णांक mi = 1;
	rc_update_bit_0(rc, prob);
	prob = (p + LZMA_LITERAL +
		(LZMA_LIT_SIZE
		 * (((get_pos(wr) & literal_pos_mask) << lc)
		    + (wr->previous_byte >> (8 - lc))))
		);

	अगर (cst->state >= LZMA_NUM_LIT_STATES) अणु
		पूर्णांक match_byte = peek_old_byte(wr, cst->rep0);
		करो अणु
			पूर्णांक bit;
			uपूर्णांक16_t *prob_lit;

			match_byte <<= 1;
			bit = match_byte & 0x100;
			prob_lit = prob + 0x100 + bit + mi;
			अगर (rc_get_bit(rc, prob_lit, &mi)) अणु
				अगर (!bit)
					अवरोध;
			पूर्ण अन्यथा अणु
				अगर (bit)
					अवरोध;
			पूर्ण
		पूर्ण जबतक (mi < 0x100);
	पूर्ण
	जबतक (mi < 0x100) अणु
		uपूर्णांक16_t *prob_lit = prob + mi;
		rc_get_bit(rc, prob_lit, &mi);
	पूर्ण
	अगर (cst->state < 4)
		cst->state = 0;
	अन्यथा अगर (cst->state < 10)
		cst->state -= 3;
	अन्यथा
		cst->state -= 6;

	वापस ग_लिखो_byte(wr, mi);
पूर्ण

अटल अंतरभूत पूर्णांक INIT process_bit1(काष्ठा ग_लिखोr *wr, काष्ठा rc *rc,
					    काष्ठा cstate *cst, uपूर्णांक16_t *p,
					    पूर्णांक pos_state, uपूर्णांक16_t *prob) अणु
	पूर्णांक offset;
	uपूर्णांक16_t *prob_len;
	पूर्णांक num_bits;
	पूर्णांक len;

	rc_update_bit_1(rc, prob);
	prob = p + LZMA_IS_REP + cst->state;
	अगर (rc_is_bit_0(rc, prob)) अणु
		rc_update_bit_0(rc, prob);
		cst->rep3 = cst->rep2;
		cst->rep2 = cst->rep1;
		cst->rep1 = cst->rep0;
		cst->state = cst->state < LZMA_NUM_LIT_STATES ? 0 : 3;
		prob = p + LZMA_LEN_CODER;
	पूर्ण अन्यथा अणु
		rc_update_bit_1(rc, prob);
		prob = p + LZMA_IS_REP_G0 + cst->state;
		अगर (rc_is_bit_0(rc, prob)) अणु
			rc_update_bit_0(rc, prob);
			prob = (p + LZMA_IS_REP_0_LONG
				+ (cst->state <<
				   LZMA_NUM_POS_BITS_MAX) +
				pos_state);
			अगर (rc_is_bit_0(rc, prob)) अणु
				rc_update_bit_0(rc, prob);

				cst->state = cst->state < LZMA_NUM_LIT_STATES ?
					9 : 11;
				वापस copy_byte(wr, cst->rep0);
			पूर्ण अन्यथा अणु
				rc_update_bit_1(rc, prob);
			पूर्ण
		पूर्ण अन्यथा अणु
			uपूर्णांक32_t distance;

			rc_update_bit_1(rc, prob);
			prob = p + LZMA_IS_REP_G1 + cst->state;
			अगर (rc_is_bit_0(rc, prob)) अणु
				rc_update_bit_0(rc, prob);
				distance = cst->rep1;
			पूर्ण अन्यथा अणु
				rc_update_bit_1(rc, prob);
				prob = p + LZMA_IS_REP_G2 + cst->state;
				अगर (rc_is_bit_0(rc, prob)) अणु
					rc_update_bit_0(rc, prob);
					distance = cst->rep2;
				पूर्ण अन्यथा अणु
					rc_update_bit_1(rc, prob);
					distance = cst->rep3;
					cst->rep3 = cst->rep2;
				पूर्ण
				cst->rep2 = cst->rep1;
			पूर्ण
			cst->rep1 = cst->rep0;
			cst->rep0 = distance;
		पूर्ण
		cst->state = cst->state < LZMA_NUM_LIT_STATES ? 8 : 11;
		prob = p + LZMA_REP_LEN_CODER;
	पूर्ण

	prob_len = prob + LZMA_LEN_CHOICE;
	अगर (rc_is_bit_0(rc, prob_len)) अणु
		rc_update_bit_0(rc, prob_len);
		prob_len = (prob + LZMA_LEN_LOW
			    + (pos_state <<
			       LZMA_LEN_NUM_LOW_BITS));
		offset = 0;
		num_bits = LZMA_LEN_NUM_LOW_BITS;
	पूर्ण अन्यथा अणु
		rc_update_bit_1(rc, prob_len);
		prob_len = prob + LZMA_LEN_CHOICE_2;
		अगर (rc_is_bit_0(rc, prob_len)) अणु
			rc_update_bit_0(rc, prob_len);
			prob_len = (prob + LZMA_LEN_MID
				    + (pos_state <<
				       LZMA_LEN_NUM_MID_BITS));
			offset = 1 << LZMA_LEN_NUM_LOW_BITS;
			num_bits = LZMA_LEN_NUM_MID_BITS;
		पूर्ण अन्यथा अणु
			rc_update_bit_1(rc, prob_len);
			prob_len = prob + LZMA_LEN_HIGH;
			offset = ((1 << LZMA_LEN_NUM_LOW_BITS)
				  + (1 << LZMA_LEN_NUM_MID_BITS));
			num_bits = LZMA_LEN_NUM_HIGH_BITS;
		पूर्ण
	पूर्ण

	rc_bit_tree_decode(rc, prob_len, num_bits, &len);
	len += offset;

	अगर (cst->state < 4) अणु
		पूर्णांक pos_slot;

		cst->state += LZMA_NUM_LIT_STATES;
		prob =
			p + LZMA_POS_SLOT +
			((len <
			  LZMA_NUM_LEN_TO_POS_STATES ? len :
			  LZMA_NUM_LEN_TO_POS_STATES - 1)
			 << LZMA_NUM_POS_SLOT_BITS);
		rc_bit_tree_decode(rc, prob,
				   LZMA_NUM_POS_SLOT_BITS,
				   &pos_slot);
		अगर (pos_slot >= LZMA_START_POS_MODEL_INDEX) अणु
			पूर्णांक i, mi;
			num_bits = (pos_slot >> 1) - 1;
			cst->rep0 = 2 | (pos_slot & 1);
			अगर (pos_slot < LZMA_END_POS_MODEL_INDEX) अणु
				cst->rep0 <<= num_bits;
				prob = p + LZMA_SPEC_POS +
					cst->rep0 - pos_slot - 1;
			पूर्ण अन्यथा अणु
				num_bits -= LZMA_NUM_ALIGN_BITS;
				जबतक (num_bits--)
					cst->rep0 = (cst->rep0 << 1) |
						rc_direct_bit(rc);
				prob = p + LZMA_ALIGN;
				cst->rep0 <<= LZMA_NUM_ALIGN_BITS;
				num_bits = LZMA_NUM_ALIGN_BITS;
			पूर्ण
			i = 1;
			mi = 1;
			जबतक (num_bits--) अणु
				अगर (rc_get_bit(rc, prob + mi, &mi))
					cst->rep0 |= i;
				i <<= 1;
			पूर्ण
		पूर्ण अन्यथा
			cst->rep0 = pos_slot;
		अगर (++(cst->rep0) == 0)
			वापस 0;
		अगर (cst->rep0 > wr->header->dict_size
				|| cst->rep0 > get_pos(wr))
			वापस -1;
	पूर्ण

	len += LZMA_MATCH_MIN_LEN;

	वापस copy_bytes(wr, cst->rep0, len);
पूर्ण



STATIC अंतरभूत पूर्णांक INIT unlzma(अचिन्हित अक्षर *buf, दीर्घ in_len,
			      दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ),
			      दीर्घ (*flush)(व्योम*, अचिन्हित दीर्घ),
			      अचिन्हित अक्षर *output,
			      दीर्घ *posp,
			      व्योम(*error)(अक्षर *x)
	)
अणु
	काष्ठा lzma_header header;
	पूर्णांक lc, pb, lp;
	uपूर्णांक32_t pos_state_mask;
	uपूर्णांक32_t literal_pos_mask;
	uपूर्णांक16_t *p;
	पूर्णांक num_probs;
	काष्ठा rc rc;
	पूर्णांक i, mi;
	काष्ठा ग_लिखोr wr;
	काष्ठा cstate cst;
	अचिन्हित अक्षर *inbuf;
	पूर्णांक ret = -1;

	rc.error = error;

	अगर (buf)
		inbuf = buf;
	अन्यथा
		inbuf = दो_स्मृति(LZMA_IOBUF_SIZE);
	अगर (!inbuf) अणु
		error("Could not allocate input buffer");
		जाओ निकास_0;
	पूर्ण

	cst.state = 0;
	cst.rep0 = cst.rep1 = cst.rep2 = cst.rep3 = 1;

	wr.header = &header;
	wr.flush = flush;
	wr.global_pos = 0;
	wr.previous_byte = 0;
	wr.buffer_pos = 0;

	rc_init(&rc, fill, inbuf, in_len);

	क्रम (i = 0; i < माप(header); i++) अणु
		अगर (rc.ptr >= rc.buffer_end)
			rc_पढ़ो(&rc);
		((अचिन्हित अक्षर *)&header)[i] = *rc.ptr++;
	पूर्ण

	अगर (header.pos >= (9 * 5 * 5)) अणु
		error("bad header");
		जाओ निकास_1;
	पूर्ण

	mi = 0;
	lc = header.pos;
	जबतक (lc >= 9) अणु
		mi++;
		lc -= 9;
	पूर्ण
	pb = 0;
	lp = mi;
	जबतक (lp >= 5) अणु
		pb++;
		lp -= 5;
	पूर्ण
	pos_state_mask = (1 << pb) - 1;
	literal_pos_mask = (1 << lp) - 1;

	ENDIAN_CONVERT(header.dict_size);
	ENDIAN_CONVERT(header.dst_size);

	अगर (header.dict_size == 0)
		header.dict_size = 1;

	अगर (output)
		wr.buffer = output;
	अन्यथा अणु
		wr.bufsize = MIN(header.dst_size, header.dict_size);
		wr.buffer = large_दो_स्मृति(wr.bufsize);
	पूर्ण
	अगर (wr.buffer == शून्य)
		जाओ निकास_1;

	num_probs = LZMA_BASE_SIZE + (LZMA_LIT_SIZE << (lc + lp));
	p = (uपूर्णांक16_t *) large_दो_स्मृति(num_probs * माप(*p));
	अगर (p == शून्य)
		जाओ निकास_2;
	num_probs = LZMA_LITERAL + (LZMA_LIT_SIZE << (lc + lp));
	क्रम (i = 0; i < num_probs; i++)
		p[i] = (1 << RC_MODEL_TOTAL_BITS) >> 1;

	rc_init_code(&rc);

	जबतक (get_pos(&wr) < header.dst_size) अणु
		पूर्णांक pos_state =	get_pos(&wr) & pos_state_mask;
		uपूर्णांक16_t *prob = p + LZMA_IS_MATCH +
			(cst.state << LZMA_NUM_POS_BITS_MAX) + pos_state;
		अगर (rc_is_bit_0(&rc, prob)) अणु
			अगर (process_bit0(&wr, &rc, &cst, p, pos_state, prob,
					lc, literal_pos_mask)) अणु
				error("LZMA data is corrupt");
				जाओ निकास_3;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (process_bit1(&wr, &rc, &cst, p, pos_state, prob)) अणु
				error("LZMA data is corrupt");
				जाओ निकास_3;
			पूर्ण
			अगर (cst.rep0 == 0)
				अवरोध;
		पूर्ण
		अगर (rc.buffer_size <= 0)
			जाओ निकास_3;
	पूर्ण

	अगर (posp)
		*posp = rc.ptr-rc.buffer;
	अगर (!wr.flush || wr.flush(wr.buffer, wr.buffer_pos) == wr.buffer_pos)
		ret = 0;
निकास_3:
	large_मुक्त(p);
निकास_2:
	अगर (!output)
		large_मुक्त(wr.buffer);
निकास_1:
	अगर (!buf)
		मुक्त(inbuf);
निकास_0:
	वापस ret;
पूर्ण

#अगर_घोषित PREBOOT
STATIC पूर्णांक INIT __decompress(अचिन्हित अक्षर *buf, दीर्घ in_len,
			      दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ),
			      दीर्घ (*flush)(व्योम*, अचिन्हित दीर्घ),
			      अचिन्हित अक्षर *output, दीर्घ out_len,
			      दीर्घ *posp,
			      व्योम (*error)(अक्षर *x))
अणु
	वापस unlzma(buf, in_len - 4, fill, flush, output, posp, error);
पूर्ण
#पूर्ण_अगर
