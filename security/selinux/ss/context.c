<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implementations of the security context functions.
 *
 * Author: Ondrej Mosnacek <omosnacek@gmail.com>
 * Copyright (C) 2020 Red Hat, Inc.
 */

#समावेश <linux/jhash.h>

#समावेश "context.h"
#समावेश "mls.h"

u32 context_compute_hash(स्थिर काष्ठा context *c)
अणु
	u32 hash = 0;

	/*
	 * If a context is invalid, it will always be represented by a
	 * context काष्ठा with only the len & str set (and vice versa)
	 * under a given policy. Since context काष्ठाs from dअगरferent
	 * policies should never meet, it is safe to hash valid and
	 * invalid contexts dअगरferently. The context_cmp() function
	 * alपढ़ोy operates under the same assumption.
	 */
	अगर (c->len)
		वापस full_name_hash(शून्य, c->str, c->len);

	hash = jhash_3words(c->user, c->role, c->type, hash);
	hash = mls_range_hash(&c->range, hash);
	वापस hash;
पूर्ण
