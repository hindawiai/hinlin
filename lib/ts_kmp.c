<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lib/ts_kmp.c		Knuth-Morris-Pratt text search implementation
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 *
 * ==========================================================================
 * 
 *   Implements a linear-समय string-matching algorithm due to Knuth,
 *   Morris, and Pratt [1]. Their algorithm aव्योमs the explicit
 *   computation of the transition function DELTA altogether. Its
 *   matching समय is O(n), क्रम n being length(text), using just an
 *   auxiliary function PI[1..m], क्रम m being length(pattern),
 *   precomputed from the pattern in समय O(m). The array PI allows
 *   the transition function DELTA to be computed efficiently
 *   "on the fly" as needed. Roughly speaking, क्रम any state
 *   "q" = 0,1,...,m and any अक्षरacter "a" in SIGMA, the value
 *   PI["q"] contains the inक्रमmation that is independent of "a" and
 *   is needed to compute DELTA("q", "a") [2]. Since the array PI
 *   has only m entries, whereas DELTA has O(m|SIGMA|) entries, we
 *   save a factor of |SIGMA| in the preprocessing समय by computing
 *   PI rather than DELTA.
 *
 *   [1] Cormen, Leiserson, Rivest, Stein
 *       Introdcution to Algorithms, 2nd Edition, MIT Press
 *   [2] See finite स्वतःmaton theory
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/textsearch.h>

काष्ठा ts_kmp
अणु
	u8 *		pattern;
	अचिन्हित पूर्णांक	pattern_len;
	अचिन्हित पूर्णांक	prefix_tbl[];
पूर्ण;

अटल अचिन्हित पूर्णांक kmp_find(काष्ठा ts_config *conf, काष्ठा ts_state *state)
अणु
	काष्ठा ts_kmp *kmp = ts_config_priv(conf);
	अचिन्हित पूर्णांक i, q = 0, text_len, consumed = state->offset;
	स्थिर u8 *text;
	स्थिर पूर्णांक iहाल = conf->flags & TS_IGNORECASE;

	क्रम (;;) अणु
		text_len = conf->get_next_block(consumed, &text, conf, state);

		अगर (unlikely(text_len == 0))
			अवरोध;

		क्रम (i = 0; i < text_len; i++) अणु
			जबतक (q > 0 && kmp->pattern[q]
			    != (iहाल ? बड़े(text[i]) : text[i]))
				q = kmp->prefix_tbl[q - 1];
			अगर (kmp->pattern[q]
			    == (iहाल ? बड़े(text[i]) : text[i]))
				q++;
			अगर (unlikely(q == kmp->pattern_len)) अणु
				state->offset = consumed + i + 1;
				वापस state->offset - kmp->pattern_len;
			पूर्ण
		पूर्ण

		consumed += text_len;
	पूर्ण

	वापस अच_पूर्णांक_उच्च;
पूर्ण

अटल अंतरभूत व्योम compute_prefix_tbl(स्थिर u8 *pattern, अचिन्हित पूर्णांक len,
				      अचिन्हित पूर्णांक *prefix_tbl, पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक k, q;
	स्थिर u8 iहाल = flags & TS_IGNORECASE;

	क्रम (k = 0, q = 1; q < len; q++) अणु
		जबतक (k > 0 && (iहाल ? बड़े(pattern[k]) : pattern[k])
		    != (iहाल ? बड़े(pattern[q]) : pattern[q]))
			k = prefix_tbl[k-1];
		अगर ((iहाल ? बड़े(pattern[k]) : pattern[k])
		    == (iहाल ? बड़े(pattern[q]) : pattern[q]))
			k++;
		prefix_tbl[q] = k;
	पूर्ण
पूर्ण

अटल काष्ठा ts_config *kmp_init(स्थिर व्योम *pattern, अचिन्हित पूर्णांक len,
				  gfp_t gfp_mask, पूर्णांक flags)
अणु
	काष्ठा ts_config *conf;
	काष्ठा ts_kmp *kmp;
	पूर्णांक i;
	अचिन्हित पूर्णांक prefix_tbl_len = len * माप(अचिन्हित पूर्णांक);
	माप_प्रकार priv_size = माप(*kmp) + len + prefix_tbl_len;

	conf = alloc_ts_config(priv_size, gfp_mask);
	अगर (IS_ERR(conf))
		वापस conf;

	conf->flags = flags;
	kmp = ts_config_priv(conf);
	kmp->pattern_len = len;
	compute_prefix_tbl(pattern, len, kmp->prefix_tbl, flags);
	kmp->pattern = (u8 *) kmp->prefix_tbl + prefix_tbl_len;
	अगर (flags & TS_IGNORECASE)
		क्रम (i = 0; i < len; i++)
			kmp->pattern[i] = बड़े(((u8 *)pattern)[i]);
	अन्यथा
		स_नकल(kmp->pattern, pattern, len);

	वापस conf;
पूर्ण

अटल व्योम *kmp_get_pattern(काष्ठा ts_config *conf)
अणु
	काष्ठा ts_kmp *kmp = ts_config_priv(conf);
	वापस kmp->pattern;
पूर्ण

अटल अचिन्हित पूर्णांक kmp_get_pattern_len(काष्ठा ts_config *conf)
अणु
	काष्ठा ts_kmp *kmp = ts_config_priv(conf);
	वापस kmp->pattern_len;
पूर्ण

अटल काष्ठा ts_ops kmp_ops = अणु
	.name		  = "kmp",
	.find		  = kmp_find,
	.init		  = kmp_init,
	.get_pattern	  = kmp_get_pattern,
	.get_pattern_len  = kmp_get_pattern_len,
	.owner		  = THIS_MODULE,
	.list		  = LIST_HEAD_INIT(kmp_ops.list)
पूर्ण;

अटल पूर्णांक __init init_kmp(व्योम)
अणु
	वापस textsearch_रेजिस्टर(&kmp_ops);
पूर्ण

अटल व्योम __निकास निकास_kmp(व्योम)
अणु
	textsearch_unरेजिस्टर(&kmp_ops);
पूर्ण

MODULE_LICENSE("GPL");

module_init(init_kmp);
module_निकास(निकास_kmp);
