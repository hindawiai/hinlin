<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Fileप्रणाली index definition
 *
 * Copyright (C) 2004-2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा FSCACHE_DEBUG_LEVEL CACHE
#समावेश <linux/module.h>
#समावेश "internal.h"

अटल
क्रमागत fscache_checkaux fscache_fsdef_netfs_check_aux(व्योम *cookie_netfs_data,
						    स्थिर व्योम *data,
						    uपूर्णांक16_t datalen,
						    loff_t object_size);

/*
 * The root index is owned by FS-Cache itself.
 *
 * When a netfs requests caching facilities, FS-Cache will, अगर one करोesn't
 * alपढ़ोy exist, create an entry in the root index with the key being the name
 * of the netfs ("AFS" क्रम example), and the auxiliary data holding the index
 * काष्ठाure version supplied by the netfs:
 *
 *				     FSDEF
 *				       |
 *				 +-----------+
 *				 |           |
 *				NFS         AFS
 *			       [v=1]       [v=1]
 *
 * If an entry with the appropriate name करोes alपढ़ोy exist, the version is
 * compared.  If the version is dअगरferent, the entire subtree from that entry
 * will be discarded and a new entry created.
 *
 * The new entry will be an index, and a cookie referring to it will be passed
 * to the netfs.  This is then the root handle by which the netfs accesses the
 * cache.  It can create whatever objects it likes in that index, including
 * further indices.
 */
अटल काष्ठा fscache_cookie_def fscache_fsdef_index_def = अणु
	.name		= ".FS-Cache",
	.type		= FSCACHE_COOKIE_TYPE_INDEX,
पूर्ण;

काष्ठा fscache_cookie fscache_fsdef_index = अणु
	.usage		= ATOMIC_INIT(1),
	.n_active	= ATOMIC_INIT(1),
	.lock		= __SPIN_LOCK_UNLOCKED(fscache_fsdef_index.lock),
	.backing_objects = HLIST_HEAD_INIT,
	.def		= &fscache_fsdef_index_def,
	.flags		= 1 << FSCACHE_COOKIE_ENABLED,
	.type		= FSCACHE_COOKIE_TYPE_INDEX,
पूर्ण;
EXPORT_SYMBOL(fscache_fsdef_index);

/*
 * Definition of an entry in the root index.  Each entry is an index, keyed to
 * a specअगरic netfs and only applicable to a particular version of the index
 * काष्ठाure used by that netfs.
 */
काष्ठा fscache_cookie_def fscache_fsdef_netfs_def = अणु
	.name		= "FSDEF.netfs",
	.type		= FSCACHE_COOKIE_TYPE_INDEX,
	.check_aux	= fscache_fsdef_netfs_check_aux,
पूर्ण;

/*
 * check that the index काष्ठाure version number stored in the auxiliary data
 * matches the one the netfs gave us
 */
अटल क्रमागत fscache_checkaux fscache_fsdef_netfs_check_aux(
	व्योम *cookie_netfs_data,
	स्थिर व्योम *data,
	uपूर्णांक16_t datalen,
	loff_t object_size)
अणु
	काष्ठा fscache_netfs *netfs = cookie_netfs_data;
	uपूर्णांक32_t version;

	_enter("{%s},,%hu", netfs->name, datalen);

	अगर (datalen != माप(version)) अणु
		_leave(" = OBSOLETE [dl=%d v=%zu]", datalen, माप(version));
		वापस FSCACHE_CHECKAUX_OBSOLETE;
	पूर्ण

	स_नकल(&version, data, माप(version));
	अगर (version != netfs->version) अणु
		_leave(" = OBSOLETE [ver=%x net=%x]", version, netfs->version);
		वापस FSCACHE_CHECKAUX_OBSOLETE;
	पूर्ण

	_leave(" = OKAY");
	वापस FSCACHE_CHECKAUX_OKAY;
पूर्ण
