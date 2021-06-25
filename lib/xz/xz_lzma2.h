<शैली गुरु>
/*
 * LZMA2 definitions
 *
 * Authors: Lasse Collin <lasse.collin@tukaani.org>
 *          Igor Pavlov <https://7-zip.org/>
 *
 * This file has been put पूर्णांकo the खुला करोमुख्य.
 * You can करो whatever you want with this file.
 */

#अगर_अघोषित XZ_LZMA2_H
#घोषणा XZ_LZMA2_H

/* Range coder स्थिरants */
#घोषणा RC_SHIFT_BITS 8
#घोषणा RC_TOP_BITS 24
#घोषणा RC_TOP_VALUE (1 << RC_TOP_BITS)
#घोषणा RC_BIT_MODEL_TOTAL_BITS 11
#घोषणा RC_BIT_MODEL_TOTAL (1 << RC_BIT_MODEL_TOTAL_BITS)
#घोषणा RC_MOVE_BITS 5

/*
 * Maximum number of position states. A position state is the lowest pb
 * number of bits of the current uncompressed offset. In some places there
 * are dअगरferent sets of probabilities क्रम dअगरferent position states.
 */
#घोषणा POS_STATES_MAX (1 << 4)

/*
 * This क्रमागत is used to track which LZMA symbols have occurred most recently
 * and in which order. This inक्रमmation is used to predict the next symbol.
 *
 * Symbols:
 *  - Literal: One 8-bit byte
 *  - Match: Repeat a chunk of data at some distance
 *  - Long repeat: Multi-byte match at a recently seen distance
 *  - Short repeat: One-byte repeat at a recently seen distance
 *
 * The symbol names are in from STATE_oldest_older_previous. REP means
 * either लघु or दीर्घ repeated match, and NONLIT means any non-literal.
 */
क्रमागत lzma_state अणु
	STATE_LIT_LIT,
	STATE_MATCH_LIT_LIT,
	STATE_REP_LIT_LIT,
	STATE_SHORTREP_LIT_LIT,
	STATE_MATCH_LIT,
	STATE_REP_LIT,
	STATE_SHORTREP_LIT,
	STATE_LIT_MATCH,
	STATE_LIT_LONGREP,
	STATE_LIT_SHORTREP,
	STATE_NONLIT_MATCH,
	STATE_NONLIT_REP
पूर्ण;

/* Total number of states */
#घोषणा STATES 12

/* The lowest 7 states indicate that the previous state was a literal. */
#घोषणा LIT_STATES 7

/* Indicate that the latest symbol was a literal. */
अटल अंतरभूत व्योम lzma_state_literal(क्रमागत lzma_state *state)
अणु
	अगर (*state <= STATE_SHORTREP_LIT_LIT)
		*state = STATE_LIT_LIT;
	अन्यथा अगर (*state <= STATE_LIT_SHORTREP)
		*state -= 3;
	अन्यथा
		*state -= 6;
पूर्ण

/* Indicate that the latest symbol was a match. */
अटल अंतरभूत व्योम lzma_state_match(क्रमागत lzma_state *state)
अणु
	*state = *state < LIT_STATES ? STATE_LIT_MATCH : STATE_NONLIT_MATCH;
पूर्ण

/* Indicate that the latest state was a दीर्घ repeated match. */
अटल अंतरभूत व्योम lzma_state_दीर्घ_rep(क्रमागत lzma_state *state)
अणु
	*state = *state < LIT_STATES ? STATE_LIT_LONGREP : STATE_NONLIT_REP;
पूर्ण

/* Indicate that the latest symbol was a लघु match. */
अटल अंतरभूत व्योम lzma_state_लघु_rep(क्रमागत lzma_state *state)
अणु
	*state = *state < LIT_STATES ? STATE_LIT_SHORTREP : STATE_NONLIT_REP;
पूर्ण

/* Test अगर the previous symbol was a literal. */
अटल अंतरभूत bool lzma_state_is_literal(क्रमागत lzma_state state)
अणु
	वापस state < LIT_STATES;
पूर्ण

/* Each literal coder is भागided in three sections:
 *   - 0x001-0x0FF: Without match byte
 *   - 0x101-0x1FF: With match byte; match bit is 0
 *   - 0x201-0x2FF: With match byte; match bit is 1
 *
 * Match byte is used when the previous LZMA symbol was something अन्यथा than
 * a literal (that is, it was some kind of match).
 */
#घोषणा LITERAL_CODER_SIZE 0x300

/* Maximum number of literal coders */
#घोषणा LITERAL_CODERS_MAX (1 << 4)

/* Minimum length of a match is two bytes. */
#घोषणा MATCH_LEN_MIN 2

/* Match length is encoded with 4, 5, or 10 bits.
 *
 * Length   Bits
 *  2-9      4 = Choice=0 + 3 bits
 * 10-17     5 = Choice=1 + Choice2=0 + 3 bits
 * 18-273   10 = Choice=1 + Choice2=1 + 8 bits
 */
#घोषणा LEN_LOW_BITS 3
#घोषणा LEN_LOW_SYMBOLS (1 << LEN_LOW_BITS)
#घोषणा LEN_MID_BITS 3
#घोषणा LEN_MID_SYMBOLS (1 << LEN_MID_BITS)
#घोषणा LEN_HIGH_BITS 8
#घोषणा LEN_HIGH_SYMBOLS (1 << LEN_HIGH_BITS)
#घोषणा LEN_SYMBOLS (LEN_LOW_SYMBOLS + LEN_MID_SYMBOLS + LEN_HIGH_SYMBOLS)

/*
 * Maximum length of a match is 273 which is a result of the encoding
 * described above.
 */
#घोषणा MATCH_LEN_MAX (MATCH_LEN_MIN + LEN_SYMBOLS - 1)

/*
 * Dअगरferent sets of probabilities are used क्रम match distances that have
 * very लघु match length: Lengths of 2, 3, and 4 bytes have a separate
 * set of probabilities क्रम each length. The matches with दीर्घer length
 * use a shared set of probabilities.
 */
#घोषणा DIST_STATES 4

/*
 * Get the index of the appropriate probability array क्रम decoding
 * the distance slot.
 */
अटल अंतरभूत uपूर्णांक32_t lzma_get_dist_state(uपूर्णांक32_t len)
अणु
	वापस len < DIST_STATES + MATCH_LEN_MIN
			? len - MATCH_LEN_MIN : DIST_STATES - 1;
पूर्ण

/*
 * The highest two bits of a 32-bit match distance are encoded using six bits.
 * This six-bit value is called a distance slot. This way encoding a 32-bit
 * value takes 6-36 bits, larger values taking more bits.
 */
#घोषणा DIST_SLOT_BITS 6
#घोषणा DIST_SLOTS (1 << DIST_SLOT_BITS)

/* Match distances up to 127 are fully encoded using probabilities. Since
 * the highest two bits (distance slot) are always encoded using six bits,
 * the distances 0-3 करोn't need any additional bits to encode, since the
 * distance slot itself is the same as the actual distance. DIST_MODEL_START
 * indicates the first distance slot where at least one additional bit is
 * needed.
 */
#घोषणा DIST_MODEL_START 4

/*
 * Match distances greater than 127 are encoded in three pieces:
 *   - distance slot: the highest two bits
 *   - direct bits: 2-26 bits below the highest two bits
 *   - alignment bits: four lowest bits
 *
 * Direct bits करोn't use any probabilities.
 *
 * The distance slot value of 14 is क्रम distances 128-191.
 */
#घोषणा DIST_MODEL_END 14

/* Distance slots that indicate a distance <= 127. */
#घोषणा FULL_DISTANCES_BITS (DIST_MODEL_END / 2)
#घोषणा FULL_DISTANCES (1 << FULL_DISTANCES_BITS)

/*
 * For match distances greater than 127, only the highest two bits and the
 * lowest four bits (alignment) is encoded using probabilities.
 */
#घोषणा ALIGN_BITS 4
#घोषणा ALIGN_SIZE (1 << ALIGN_BITS)
#घोषणा ALIGN_MASK (ALIGN_SIZE - 1)

/* Total number of all probability variables */
#घोषणा PROBS_TOTAL (1846 + LITERAL_CODERS_MAX * LITERAL_CODER_SIZE)

/*
 * LZMA remembers the four most recent match distances. Reusing these
 * distances tends to take less space than re-encoding the actual
 * distance value.
 */
#घोषणा REPS 4

#पूर्ण_अगर
