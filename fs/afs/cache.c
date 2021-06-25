<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS caching stuff
 *
 * Copyright (C) 2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/sched.h>
#समावेश "internal.h"

अटल क्रमागत fscache_checkaux afs_vnode_cache_check_aux(व्योम *cookie_netfs_data,
						       स्थिर व्योम *buffer,
						       uपूर्णांक16_t buflen,
						       loff_t object_size);

काष्ठा fscache_netfs afs_cache_netfs = अणु
	.name			= "afs",
	.version		= 2,
पूर्ण;

काष्ठा fscache_cookie_def afs_cell_cache_index_def = अणु
	.name		= "AFS.cell",
	.type		= FSCACHE_COOKIE_TYPE_INDEX,
पूर्ण;

काष्ठा fscache_cookie_def afs_volume_cache_index_def = अणु
	.name		= "AFS.volume",
	.type		= FSCACHE_COOKIE_TYPE_INDEX,
पूर्ण;

काष्ठा fscache_cookie_def afs_vnode_cache_index_def = अणु
	.name		= "AFS.vnode",
	.type		= FSCACHE_COOKIE_TYPE_DATAखाता,
	.check_aux	= afs_vnode_cache_check_aux,
पूर्ण;

/*
 * check that the auxiliary data indicates that the entry is still valid
 */
अटल क्रमागत fscache_checkaux afs_vnode_cache_check_aux(व्योम *cookie_netfs_data,
						       स्थिर व्योम *buffer,
						       uपूर्णांक16_t buflen,
						       loff_t object_size)
अणु
	काष्ठा afs_vnode *vnode = cookie_netfs_data;
	काष्ठा afs_vnode_cache_aux aux;

	_enter("{%llx,%x,%llx},%p,%u",
	       vnode->fid.vnode, vnode->fid.unique, vnode->status.data_version,
	       buffer, buflen);

	स_नकल(&aux, buffer, माप(aux));

	/* check the size of the data is what we're expecting */
	अगर (buflen != माप(aux)) अणु
		_leave(" = OBSOLETE [len %hx != %zx]", buflen, माप(aux));
		वापस FSCACHE_CHECKAUX_OBSOLETE;
	पूर्ण

	अगर (vnode->status.data_version != aux.data_version) अणु
		_leave(" = OBSOLETE [vers %llx != %llx]",
		       aux.data_version, vnode->status.data_version);
		वापस FSCACHE_CHECKAUX_OBSOLETE;
	पूर्ण

	_leave(" = SUCCESS");
	वापस FSCACHE_CHECKAUX_OKAY;
पूर्ण
