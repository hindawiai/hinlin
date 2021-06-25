<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * snapshot.c    Ceph snapshot context utility routines (part of libceph)
 *
 * Copyright (C) 2013 Inktank Storage, Inc.
 */

#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/ceph/libceph.h>

/*
 * Ceph snapshot contexts are reference counted objects, and the
 * वापसed काष्ठाure holds a single reference.  Acquire additional
 * references with ceph_get_snap_context(), and release them with
 * ceph_put_snap_context().  When the reference count reaches zero
 * the entire काष्ठाure is मुक्तd.
 */

/*
 * Create a new ceph snapshot context large enough to hold the
 * indicated number of snapshot ids (which can be 0).  Caller has
 * to fill in snapc->seq and snapc->snaps[0..snap_count-1].
 *
 * Returns a null poपूर्णांकer अगर an error occurs.
 */
काष्ठा ceph_snap_context *ceph_create_snap_context(u32 snap_count,
						gfp_t gfp_flags)
अणु
	काष्ठा ceph_snap_context *snapc;
	माप_प्रकार size;

	size = माप (काष्ठा ceph_snap_context);
	size += snap_count * माप (snapc->snaps[0]);
	snapc = kzalloc(size, gfp_flags);
	अगर (!snapc)
		वापस शून्य;

	refcount_set(&snapc->nref, 1);
	snapc->num_snaps = snap_count;

	वापस snapc;
पूर्ण
EXPORT_SYMBOL(ceph_create_snap_context);

काष्ठा ceph_snap_context *ceph_get_snap_context(काष्ठा ceph_snap_context *sc)
अणु
	अगर (sc)
		refcount_inc(&sc->nref);
	वापस sc;
पूर्ण
EXPORT_SYMBOL(ceph_get_snap_context);

व्योम ceph_put_snap_context(काष्ठा ceph_snap_context *sc)
अणु
	अगर (!sc)
		वापस;
	अगर (refcount_dec_and_test(&sc->nref)) अणु
		/*prपूर्णांकk(" deleting snap_context %p\n", sc);*/
		kमुक्त(sc);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ceph_put_snap_context);
