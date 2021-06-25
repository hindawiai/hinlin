<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lib/ts_fsm.c	   A naive finite state machine text search approach
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 *
 * ==========================================================================
 *
 *   A finite state machine consists of n states (काष्ठा ts_fsm_token)
 *   representing the pattern as a finite स्वतःmaton. The data is पढ़ो
 *   sequentially on an octet basis. Every state token specअगरies the number
 *   of recurrences and the type of value accepted which can be either a
 *   specअगरic अक्षरacter or ctype based set of अक्षरacters. The available
 *   type of recurrences include 1, (0|1), [0 n], and [1 n].
 *
 *   The algorithm dअगरfers between strict/non-strict mode specअगरying
 *   whether the pattern has to start at the first octet. Strict mode
 *   is enabled by शेष and can be disabled by inserting
 *   TS_FSM_HEAD_IGNORE as the first token in the chain.
 *
 *   The runसमय perक्रमmance of the algorithm should be around O(n),
 *   however जबतक in strict mode the average runसमय can be better.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/textsearch.h>
#समावेश <linux/textsearch_fsm.h>

काष्ठा ts_fsm
अणु
	अचिन्हित पूर्णांक		ntokens;
	काष्ठा ts_fsm_token	tokens[];
पूर्ण;

/* other values derived from प्रकार.स */
#घोषणा _A		0x100 /* ascii */
#घोषणा _W		0x200 /* wildcard */

/* Map to _ctype flags and some magic numbers */
अटल स्थिर u16 token_map[TS_FSM_TYPE_MAX+1] = अणु
	[TS_FSM_SPECIFIC] = 0,
	[TS_FSM_WILDCARD] = _W,
	[TS_FSM_CNTRL]	  = _C,
	[TS_FSM_LOWER]	  = _L,
	[TS_FSM_UPPER]	  = _U,
	[TS_FSM_PUNCT]	  = _P,
	[TS_FSM_SPACE]	  = _S,
	[TS_FSM_DIGIT]	  = _D,
	[TS_FSM_XDIGIT]	  = _D | _X,
	[TS_FSM_ALPHA]	  = _U | _L,
	[TS_FSM_ALNUM]	  = _U | _L | _D,
	[TS_FSM_PRINT]	  = _P | _U | _L | _D | _SP,
	[TS_FSM_GRAPH]	  = _P | _U | _L | _D,
	[TS_FSM_ASCII]	  = _A,
पूर्ण;

अटल स्थिर u16 token_lookup_tbl[256] = अणु
_W|_A|_C,      _W|_A|_C,     _W|_A|_C,     _W|_A|_C,		/*   0-  3 */
_W|_A|_C,      _W|_A|_C,     _W|_A|_C,     _W|_A|_C,		/*   4-  7 */
_W|_A|_C,      _W|_A|_C|_S,  _W|_A|_C|_S,  _W|_A|_C|_S,		/*   8- 11 */
_W|_A|_C|_S,   _W|_A|_C|_S,  _W|_A|_C,     _W|_A|_C,		/*  12- 15 */
_W|_A|_C,      _W|_A|_C,     _W|_A|_C,     _W|_A|_C,		/*  16- 19 */
_W|_A|_C,      _W|_A|_C,     _W|_A|_C,     _W|_A|_C,		/*  20- 23 */
_W|_A|_C,      _W|_A|_C,     _W|_A|_C,     _W|_A|_C,		/*  24- 27 */
_W|_A|_C,      _W|_A|_C,     _W|_A|_C,     _W|_A|_C,		/*  28- 31 */
_W|_A|_S|_SP,  _W|_A|_P,     _W|_A|_P,     _W|_A|_P,		/*  32- 35 */
_W|_A|_P,      _W|_A|_P,     _W|_A|_P,     _W|_A|_P,		/*  36- 39 */
_W|_A|_P,      _W|_A|_P,     _W|_A|_P,     _W|_A|_P,		/*  40- 43 */
_W|_A|_P,      _W|_A|_P,     _W|_A|_P,     _W|_A|_P,		/*  44- 47 */
_W|_A|_D,      _W|_A|_D,     _W|_A|_D,     _W|_A|_D,		/*  48- 51 */
_W|_A|_D,      _W|_A|_D,     _W|_A|_D,     _W|_A|_D,		/*  52- 55 */
_W|_A|_D,      _W|_A|_D,     _W|_A|_P,     _W|_A|_P,		/*  56- 59 */
_W|_A|_P,      _W|_A|_P,     _W|_A|_P,     _W|_A|_P,		/*  60- 63 */
_W|_A|_P,      _W|_A|_U|_X,  _W|_A|_U|_X,  _W|_A|_U|_X,		/*  64- 67 */
_W|_A|_U|_X,   _W|_A|_U|_X,  _W|_A|_U|_X,  _W|_A|_U,		/*  68- 71 */
_W|_A|_U,      _W|_A|_U,     _W|_A|_U,     _W|_A|_U,		/*  72- 75 */
_W|_A|_U,      _W|_A|_U,     _W|_A|_U,     _W|_A|_U,		/*  76- 79 */
_W|_A|_U,      _W|_A|_U,     _W|_A|_U,     _W|_A|_U,		/*  80- 83 */
_W|_A|_U,      _W|_A|_U,     _W|_A|_U,     _W|_A|_U,		/*  84- 87 */
_W|_A|_U,      _W|_A|_U,     _W|_A|_U,     _W|_A|_P,		/*  88- 91 */
_W|_A|_P,      _W|_A|_P,     _W|_A|_P,     _W|_A|_P,		/*  92- 95 */
_W|_A|_P,      _W|_A|_L|_X,  _W|_A|_L|_X,  _W|_A|_L|_X,		/*  96- 99 */
_W|_A|_L|_X,   _W|_A|_L|_X,  _W|_A|_L|_X,  _W|_A|_L,		/* 100-103 */
_W|_A|_L,      _W|_A|_L,     _W|_A|_L,     _W|_A|_L,		/* 104-107 */
_W|_A|_L,      _W|_A|_L,     _W|_A|_L,     _W|_A|_L,		/* 108-111 */
_W|_A|_L,      _W|_A|_L,     _W|_A|_L,     _W|_A|_L,		/* 112-115 */
_W|_A|_L,      _W|_A|_L,     _W|_A|_L,     _W|_A|_L,		/* 116-119 */
_W|_A|_L,      _W|_A|_L,     _W|_A|_L,     _W|_A|_P,		/* 120-123 */
_W|_A|_P,      _W|_A|_P,     _W|_A|_P,     _W|_A|_C,		/* 124-127 */
_W,            _W,           _W,           _W,			/* 128-131 */
_W,            _W,           _W,           _W,			/* 132-135 */
_W,            _W,           _W,           _W,			/* 136-139 */
_W,            _W,           _W,           _W,			/* 140-143 */
_W,            _W,           _W,           _W,			/* 144-147 */
_W,            _W,           _W,           _W,			/* 148-151 */
_W,            _W,           _W,           _W,			/* 152-155 */
_W,            _W,           _W,           _W,			/* 156-159 */
_W|_S|_SP,     _W|_P,        _W|_P,        _W|_P,		/* 160-163 */
_W|_P,         _W|_P,        _W|_P,        _W|_P,		/* 164-167 */
_W|_P,         _W|_P,        _W|_P,        _W|_P,		/* 168-171 */
_W|_P,         _W|_P,        _W|_P,        _W|_P,		/* 172-175 */
_W|_P,         _W|_P,        _W|_P,        _W|_P,		/* 176-179 */
_W|_P,         _W|_P,        _W|_P,        _W|_P,		/* 180-183 */
_W|_P,         _W|_P,        _W|_P,        _W|_P,		/* 184-187 */
_W|_P,         _W|_P,        _W|_P,        _W|_P,		/* 188-191 */
_W|_U,         _W|_U,        _W|_U,        _W|_U,		/* 192-195 */
_W|_U,         _W|_U,        _W|_U,        _W|_U,		/* 196-199 */
_W|_U,         _W|_U,        _W|_U,        _W|_U,		/* 200-203 */
_W|_U,         _W|_U,        _W|_U,        _W|_U,		/* 204-207 */
_W|_U,         _W|_U,        _W|_U,        _W|_U,		/* 208-211 */
_W|_U,         _W|_U,        _W|_U,        _W|_P,		/* 212-215 */
_W|_U,         _W|_U,        _W|_U,        _W|_U,		/* 216-219 */
_W|_U,         _W|_U,        _W|_U,        _W|_L,		/* 220-223 */
_W|_L,         _W|_L,        _W|_L,        _W|_L,		/* 224-227 */
_W|_L,         _W|_L,        _W|_L,        _W|_L,		/* 228-231 */
_W|_L,         _W|_L,        _W|_L,        _W|_L,		/* 232-235 */
_W|_L,         _W|_L,        _W|_L,        _W|_L,		/* 236-239 */
_W|_L,         _W|_L,        _W|_L,        _W|_L,		/* 240-243 */
_W|_L,         _W|_L,        _W|_L,        _W|_P,		/* 244-247 */
_W|_L,         _W|_L,        _W|_L,        _W|_L,		/* 248-251 */
_W|_L,         _W|_L,        _W|_L,        _W|_Lपूर्ण;		/* 252-255 */

अटल अंतरभूत पूर्णांक match_token(काष्ठा ts_fsm_token *t, u8 d)
अणु
	अगर (t->type)
		वापस (token_lookup_tbl[d] & t->type) != 0;
	अन्यथा
		वापस t->value == d;
पूर्ण

अटल अचिन्हित पूर्णांक fsm_find(काष्ठा ts_config *conf, काष्ठा ts_state *state)
अणु
	काष्ठा ts_fsm *fsm = ts_config_priv(conf);
	काष्ठा ts_fsm_token *cur = शून्य, *next;
	अचिन्हित पूर्णांक match_start, block_idx = 0, tok_idx;
	अचिन्हित block_len = 0, strict, consumed = state->offset;
	स्थिर u8 *data;

#घोषणा GET_NEXT_BLOCK()		\
(अणु	consumed += block_idx;		\
	block_idx = 0;			\
	block_len = conf->get_next_block(consumed, &data, conf, state); पूर्ण)

#घोषणा TOKEN_MISMATCH()		\
	करो अणु				\
		अगर (strict)		\
			जाओ no_match;	\
		block_idx++;		\
		जाओ startover;		\
	पूर्ण जबतक(0)

#घोषणा end_of_data() unlikely(block_idx >= block_len && !GET_NEXT_BLOCK())

	अगर (end_of_data())
		जाओ no_match;

	strict = fsm->tokens[0].recur != TS_FSM_HEAD_IGNORE;

startover:
	match_start = consumed + block_idx;

	क्रम (tok_idx = 0; tok_idx < fsm->ntokens; tok_idx++) अणु
		cur = &fsm->tokens[tok_idx];

		अगर (likely(tok_idx < (fsm->ntokens - 1)))
			next = &fsm->tokens[tok_idx + 1];
		अन्यथा
			next = शून्य;

		चयन (cur->recur) अणु
		हाल TS_FSM_SINGLE:
			अगर (end_of_data())
				जाओ no_match;

			अगर (!match_token(cur, data[block_idx]))
				TOKEN_MISMATCH();
			अवरोध;

		हाल TS_FSM_PERHAPS:
			अगर (end_of_data() ||
			    !match_token(cur, data[block_idx]))
				जारी;
			अवरोध;

		हाल TS_FSM_MULTI:
			अगर (end_of_data())
				जाओ no_match;

			अगर (!match_token(cur, data[block_idx]))
				TOKEN_MISMATCH();

			block_idx++;
			fallthrough;

		हाल TS_FSM_ANY:
			अगर (next == शून्य)
				जाओ found_match;

			अगर (end_of_data())
				जारी;

			जबतक (!match_token(next, data[block_idx])) अणु
				अगर (!match_token(cur, data[block_idx]))
					TOKEN_MISMATCH();
				block_idx++;
				अगर (end_of_data())
					जाओ no_match;
			पूर्ण
			जारी;

		/*
		 * Optimization: Prefer small local loop over jumping
		 * back and क्रमth until garbage at head is munched.
		 */
		हाल TS_FSM_HEAD_IGNORE:
			अगर (end_of_data())
				जारी;

			जबतक (!match_token(next, data[block_idx])) अणु
				/*
				 * Special हाल, करोn't start over upon
				 * a mismatch, give the user the
				 * chance to specअगरy the type of data
				 * allowed to be ignored.
				 */
				अगर (!match_token(cur, data[block_idx]))
					जाओ no_match;

				block_idx++;
				अगर (end_of_data())
					जाओ no_match;
			पूर्ण

			match_start = consumed + block_idx;
			जारी;
		पूर्ण

		block_idx++;
	पूर्ण

	अगर (end_of_data())
		जाओ found_match;

no_match:
	वापस अच_पूर्णांक_उच्च;

found_match:
	state->offset = consumed + block_idx;
	वापस match_start;
पूर्ण

अटल काष्ठा ts_config *fsm_init(स्थिर व्योम *pattern, अचिन्हित पूर्णांक len,
				    gfp_t gfp_mask, पूर्णांक flags)
अणु
	पूर्णांक i, err = -EINVAL;
	काष्ठा ts_config *conf;
	काष्ठा ts_fsm *fsm;
	काष्ठा ts_fsm_token *tokens = (काष्ठा ts_fsm_token *) pattern;
	अचिन्हित पूर्णांक ntokens = len / माप(*tokens);
	माप_प्रकार priv_size = माप(*fsm) + len;

	अगर (len  % माप(काष्ठा ts_fsm_token) || ntokens < 1)
		जाओ errout;

	अगर (flags & TS_IGNORECASE)
		जाओ errout;

	क्रम (i = 0; i < ntokens; i++) अणु
		काष्ठा ts_fsm_token *t = &tokens[i];

		अगर (t->type > TS_FSM_TYPE_MAX || t->recur > TS_FSM_RECUR_MAX)
			जाओ errout;

		अगर (t->recur == TS_FSM_HEAD_IGNORE &&
		    (i != 0 || i == (ntokens - 1)))
			जाओ errout;
	पूर्ण

	conf = alloc_ts_config(priv_size, gfp_mask);
	अगर (IS_ERR(conf))
		वापस conf;

	conf->flags = flags;
	fsm = ts_config_priv(conf);
	fsm->ntokens = ntokens;
	स_नकल(fsm->tokens, pattern, len);

	क्रम (i = 0; i < fsm->ntokens; i++) अणु
		काष्ठा ts_fsm_token *t = &fsm->tokens[i];
		t->type = token_map[t->type];
	पूर्ण

	वापस conf;

errout:
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम *fsm_get_pattern(काष्ठा ts_config *conf)
अणु
	काष्ठा ts_fsm *fsm = ts_config_priv(conf);
	वापस fsm->tokens;
पूर्ण

अटल अचिन्हित पूर्णांक fsm_get_pattern_len(काष्ठा ts_config *conf)
अणु
	काष्ठा ts_fsm *fsm = ts_config_priv(conf);
	वापस fsm->ntokens * माप(काष्ठा ts_fsm_token);
पूर्ण

अटल काष्ठा ts_ops fsm_ops = अणु
	.name		  = "fsm",
	.find		  = fsm_find,
	.init		  = fsm_init,
	.get_pattern	  = fsm_get_pattern,
	.get_pattern_len  = fsm_get_pattern_len,
	.owner		  = THIS_MODULE,
	.list		  = LIST_HEAD_INIT(fsm_ops.list)
पूर्ण;

अटल पूर्णांक __init init_fsm(व्योम)
अणु
	वापस textsearch_रेजिस्टर(&fsm_ops);
पूर्ण

अटल व्योम __निकास निकास_fsm(व्योम)
अणु
	textsearch_unरेजिस्टर(&fsm_ops);
पूर्ण

MODULE_LICENSE("GPL");

module_init(init_fsm);
module_निकास(निकास_fsm);
