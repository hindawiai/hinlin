<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Feature set bits and string conversion.
 * Inspired by ext4's features compat/incompat/ro_compat related code.
 *
 * Copyright 2020 Coly Li <colyli@suse.de>
 *
 */
#समावेश <linux/bcache.h>
#समावेश "bcache.h"
#समावेश "features.h"

काष्ठा feature अणु
	पूर्णांक		compat;
	अचिन्हित पूर्णांक	mask;
	स्थिर अक्षर	*string;
पूर्ण;

अटल काष्ठा feature feature_list[] = अणु
	अणुBCH_FEATURE_INCOMPAT, BCH_FEATURE_INCOMPAT_LOG_LARGE_BUCKET_SIZE,
		"large_bucket"पूर्ण,
	अणु0, 0, शून्य पूर्ण,
पूर्ण;

#घोषणा compose_feature_string(type)				\
(अणु									\
	काष्ठा feature *f;						\
	bool first = true;						\
									\
	क्रम (f = &feature_list[0]; f->compat != 0; f++) अणु		\
		अगर (f->compat != BCH_FEATURE_ ## type)			\
			जारी;					\
		अगर (BCH_HAS_ ## type ## _FEATURE(&c->cache->sb, f->mask)) अणु	\
			अगर (first) अणु					\
				out += snम_लिखो(out, buf + size - out,	\
						"[");	\
			पूर्ण अन्यथा अणु					\
				out += snम_लिखो(out, buf + size - out,	\
						" [");			\
			पूर्ण						\
		पूर्ण अन्यथा अगर (!first) अणु					\
			out += snम_लिखो(out, buf + size - out, " ");	\
		पूर्ण							\
									\
		out += snम_लिखो(out, buf + size - out, "%s", f->string);\
									\
		अगर (BCH_HAS_ ## type ## _FEATURE(&c->cache->sb, f->mask))	\
			out += snम_लिखो(out, buf + size - out, "]");	\
									\
		first = false;						\
	पूर्ण								\
	अगर (!first)							\
		out += snम_लिखो(out, buf + size - out, "\n");		\
पूर्ण)

पूर्णांक bch_prपूर्णांक_cache_set_feature_compat(काष्ठा cache_set *c, अक्षर *buf, पूर्णांक size)
अणु
	अक्षर *out = buf;
	compose_feature_string(COMPAT);
	वापस out - buf;
पूर्ण

पूर्णांक bch_prपूर्णांक_cache_set_feature_ro_compat(काष्ठा cache_set *c, अक्षर *buf, पूर्णांक size)
अणु
	अक्षर *out = buf;
	compose_feature_string(RO_COMPAT);
	वापस out - buf;
पूर्ण

पूर्णांक bch_prपूर्णांक_cache_set_feature_incompat(काष्ठा cache_set *c, अक्षर *buf, पूर्णांक size)
अणु
	अक्षर *out = buf;
	compose_feature_string(INCOMPAT);
	वापस out - buf;
पूर्ण
