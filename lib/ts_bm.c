<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lib/ts_bm.c		Boyer-Moore text search implementation
 *
 * Authors:	Pablo Neira Ayuso <pablo@eurodev.net>
 *
 * ==========================================================================
 * 
 *   Implements Boyer-Moore string matching algorithm:
 *
 *   [1] A Fast String Searching Algorithm, R.S. Boyer and Moore.
 *       Communications of the Association क्रम Computing Machinery, 
 *       20(10), 1977, pp. 762-772.
 *       https://www.cs.utexas.edu/users/moore/खुलाations/fstrpos.pdf
 *
 *   [2] Handbook of Exact String Matching Algorithms, Thierry Lecroq, 2004
 *       http://www-igm.univ-mlv.fr/~lecroq/string/string.pdf
 *
 *   Note: Since Boyer-Moore (BM) perक्रमms searches क्रम matchings from right 
 *   to left, it's still possible that a matching could be spपढ़ो over 
 *   multiple blocks, in that हाल this algorithm won't find any coincidence.
 *   
 *   If you're willing to ensure that such thing won't ever happen, use the
 *   Knuth-Pratt-Morris (KMP) implementation instead. In conclusion, choose 
 *   the proper string search algorithm depending on your setting. 
 *
 *   Say you're using the textsearch infraकाष्ठाure क्रम filtering, NIDS or 
 *   any similar security focused purpose, then go KMP. Otherwise, अगर you 
 *   really care about perक्रमmance, say you're classअगरying packets to apply
 *   Quality of Service (QoS) policies, and you करोn't mind about possible
 *   matchings spपढ़ो over multiple fragments, then go BM.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/textsearch.h>

/* Alphabet size, use ASCII */
#घोषणा ASIZE 256

#अगर 0
#घोषणा DEBUGP prपूर्णांकk
#अन्यथा
#घोषणा DEBUGP(args, क्रमmat...)
#पूर्ण_अगर

काष्ठा ts_bm
अणु
	u8 *		pattern;
	अचिन्हित पूर्णांक	patlen;
	अचिन्हित पूर्णांक 	bad_shअगरt[ASIZE];
	अचिन्हित पूर्णांक	good_shअगरt[];
पूर्ण;

अटल अचिन्हित पूर्णांक bm_find(काष्ठा ts_config *conf, काष्ठा ts_state *state)
अणु
	काष्ठा ts_bm *bm = ts_config_priv(conf);
	अचिन्हित पूर्णांक i, text_len, consumed = state->offset;
	स्थिर u8 *text;
	पूर्णांक shअगरt = bm->patlen - 1, bs;
	स्थिर u8 iहाल = conf->flags & TS_IGNORECASE;

	क्रम (;;) अणु
		text_len = conf->get_next_block(consumed, &text, conf, state);

		अगर (unlikely(text_len == 0))
			अवरोध;

		जबतक (shअगरt < text_len) अणु
			DEBUGP("Searching in position %d (%c)\n", 
				shअगरt, text[shअगरt]);
			क्रम (i = 0; i < bm->patlen; i++) 
				अगर ((iहाल ? बड़े(text[shअगरt-i])
				    : text[shअगरt-i])
					!= bm->pattern[bm->patlen-1-i])
				     जाओ next;

			/* Lonकरोn calling... */
			DEBUGP("found!\n");
			वापस consumed += (shअगरt-(bm->patlen-1));

next:			bs = bm->bad_shअगरt[text[shअगरt-i]];

			/* Now jumping to... */
			shअगरt = max_t(पूर्णांक, shअगरt-i+bs, shअगरt+bm->good_shअगरt[i]);
		पूर्ण
		consumed += text_len;
	पूर्ण

	वापस अच_पूर्णांक_उच्च;
पूर्ण

अटल पूर्णांक subpattern(u8 *pattern, पूर्णांक i, पूर्णांक j, पूर्णांक g)
अणु
	पूर्णांक x = i+g-1, y = j+g-1, ret = 0;

	जबतक(pattern[x--] == pattern[y--]) अणु
		अगर (y < 0) अणु
			ret = 1;
			अवरोध;
		पूर्ण
		अगर (--g == 0) अणु
			ret = pattern[i-1] != pattern[j-1];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम compute_prefix_tbl(काष्ठा ts_bm *bm, पूर्णांक flags)
अणु
	पूर्णांक i, j, g;

	क्रम (i = 0; i < ASIZE; i++)
		bm->bad_shअगरt[i] = bm->patlen;
	क्रम (i = 0; i < bm->patlen - 1; i++) अणु
		bm->bad_shअगरt[bm->pattern[i]] = bm->patlen - 1 - i;
		अगर (flags & TS_IGNORECASE)
			bm->bad_shअगरt[छोटे(bm->pattern[i])]
			    = bm->patlen - 1 - i;
	पूर्ण

	/* Compute the good shअगरt array, used to match reocurrences 
	 * of a subpattern */
	bm->good_shअगरt[0] = 1;
	क्रम (i = 1; i < bm->patlen; i++)
		bm->good_shअगरt[i] = bm->patlen;
        क्रम (i = bm->patlen-1, g = 1; i > 0; g++, i--) अणु
		क्रम (j = i-1; j >= 1-g ; j--)
			अगर (subpattern(bm->pattern, i, j, g)) अणु
				bm->good_shअगरt[g] = bm->patlen-j-g;
				अवरोध;
			पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा ts_config *bm_init(स्थिर व्योम *pattern, अचिन्हित पूर्णांक len,
				 gfp_t gfp_mask, पूर्णांक flags)
अणु
	काष्ठा ts_config *conf;
	काष्ठा ts_bm *bm;
	पूर्णांक i;
	अचिन्हित पूर्णांक prefix_tbl_len = len * माप(अचिन्हित पूर्णांक);
	माप_प्रकार priv_size = माप(*bm) + len + prefix_tbl_len;

	conf = alloc_ts_config(priv_size, gfp_mask);
	अगर (IS_ERR(conf))
		वापस conf;

	conf->flags = flags;
	bm = ts_config_priv(conf);
	bm->patlen = len;
	bm->pattern = (u8 *) bm->good_shअगरt + prefix_tbl_len;
	अगर (flags & TS_IGNORECASE)
		क्रम (i = 0; i < len; i++)
			bm->pattern[i] = बड़े(((u8 *)pattern)[i]);
	अन्यथा
		स_नकल(bm->pattern, pattern, len);
	compute_prefix_tbl(bm, flags);

	वापस conf;
पूर्ण

अटल व्योम *bm_get_pattern(काष्ठा ts_config *conf)
अणु
	काष्ठा ts_bm *bm = ts_config_priv(conf);
	वापस bm->pattern;
पूर्ण

अटल अचिन्हित पूर्णांक bm_get_pattern_len(काष्ठा ts_config *conf)
अणु
	काष्ठा ts_bm *bm = ts_config_priv(conf);
	वापस bm->patlen;
पूर्ण

अटल काष्ठा ts_ops bm_ops = अणु
	.name		  = "bm",
	.find		  = bm_find,
	.init		  = bm_init,
	.get_pattern	  = bm_get_pattern,
	.get_pattern_len  = bm_get_pattern_len,
	.owner		  = THIS_MODULE,
	.list		  = LIST_HEAD_INIT(bm_ops.list)
पूर्ण;

अटल पूर्णांक __init init_bm(व्योम)
अणु
	वापस textsearch_रेजिस्टर(&bm_ops);
पूर्ण

अटल व्योम __निकास निकास_bm(व्योम)
अणु
	textsearch_unरेजिस्टर(&bm_ops);
पूर्ण

MODULE_LICENSE("GPL");

module_init(init_bm);
module_निकास(निकास_bm);
