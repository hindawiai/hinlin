<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* FS-Cache netfs (client) registration
 *
 * Copyright (C) 2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा FSCACHE_DEBUG_LEVEL COOKIE
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश "internal.h"

/*
 * रेजिस्टर a network fileप्रणाली क्रम caching
 */
पूर्णांक __fscache_रेजिस्टर_netfs(काष्ठा fscache_netfs *netfs)
अणु
	काष्ठा fscache_cookie *candidate, *cookie;

	_enter("{%s}", netfs->name);

	/* allocate a cookie क्रम the primary index */
	candidate = fscache_alloc_cookie(&fscache_fsdef_index,
					 &fscache_fsdef_netfs_def,
					 netfs->name, म_माप(netfs->name),
					 &netfs->version, माप(netfs->version),
					 netfs, 0);
	अगर (!candidate) अणु
		_leave(" = -ENOMEM");
		वापस -ENOMEM;
	पूर्ण

	candidate->flags = 1 << FSCACHE_COOKIE_ENABLED;

	/* check the netfs type is not alपढ़ोy present */
	cookie = fscache_hash_cookie(candidate);
	अगर (!cookie)
		जाओ alपढ़ोy_रेजिस्टरed;
	अगर (cookie != candidate) अणु
		trace_fscache_cookie(candidate, fscache_cookie_discard, 1);
		fscache_मुक्त_cookie(candidate);
	पूर्ण

	fscache_cookie_get(cookie->parent, fscache_cookie_get_रेजिस्टर_netfs);
	atomic_inc(&cookie->parent->n_children);

	netfs->primary_index = cookie;

	pr_notice("Netfs '%s' registered for caching\n", netfs->name);
	trace_fscache_netfs(netfs);
	_leave(" = 0");
	वापस 0;

alपढ़ोy_रेजिस्टरed:
	fscache_cookie_put(candidate, fscache_cookie_put_dup_netfs);
	_leave(" = -EEXIST");
	वापस -EEXIST;
पूर्ण
EXPORT_SYMBOL(__fscache_रेजिस्टर_netfs);

/*
 * unरेजिस्टर a network fileप्रणाली from the cache
 * - all cookies must have been released first
 */
व्योम __fscache_unरेजिस्टर_netfs(काष्ठा fscache_netfs *netfs)
अणु
	_enter("{%s.%u}", netfs->name, netfs->version);

	fscache_relinquish_cookie(netfs->primary_index, शून्य, false);
	pr_notice("Netfs '%s' unregistered from caching\n", netfs->name);

	_leave("");
पूर्ण
EXPORT_SYMBOL(__fscache_unरेजिस्टर_netfs);
