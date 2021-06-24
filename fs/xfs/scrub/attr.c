<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_da_format.h"
#समावेश "xfs_da_btree.h"
#समावेश "xfs_attr.h"
#समावेश "xfs_attr_leaf.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/dabtree.h"
#समावेश "scrub/attr.h"

/*
 * Allocate enough memory to hold an attr value and attr block biपंचांगaps,
 * पुनः_स्मृतिating the buffer अगर necessary.  Buffer contents are not preserved
 * across a पुनः_स्मृतिation.
 */
पूर्णांक
xchk_setup_xattr_buf(
	काष्ठा xfs_scrub	*sc,
	माप_प्रकार			value_size,
	xfs_km_flags_t		flags)
अणु
	माप_प्रकार			sz;
	काष्ठा xchk_xattr_buf	*ab = sc->buf;

	/*
	 * We need enough space to पढ़ो an xattr value from the file or enough
	 * space to hold three copies of the xattr मुक्त space biपंचांगap.  We करोn't
	 * need the buffer space क्रम both purposes at the same समय.
	 */
	sz = 3 * माप(दीर्घ) * BITS_TO_LONGS(sc->mp->m_attr_geo->blksize);
	sz = max_t(माप_प्रकार, sz, value_size);

	/*
	 * If there's alपढ़ोy a buffer, figure out अगर we need to पुनः_स्मृतिate it
	 * to accommodate a larger size.
	 */
	अगर (ab) अणु
		अगर (sz <= ab->sz)
			वापस 0;
		kmem_मुक्त(ab);
		sc->buf = शून्य;
	पूर्ण

	/*
	 * Don't zero the buffer upon allocation to aव्योम runसमय overhead.
	 * All users must be careful never to पढ़ो uninitialized contents.
	 */
	ab = kmem_alloc_large(माप(*ab) + sz, flags);
	अगर (!ab)
		वापस -ENOMEM;

	ab->sz = sz;
	sc->buf = ab;
	वापस 0;
पूर्ण

/* Set us up to scrub an inode's extended attributes. */
पूर्णांक
xchk_setup_xattr(
	काष्ठा xfs_scrub	*sc)
अणु
	पूर्णांक			error;

	/*
	 * We failed to get memory जबतक checking attrs, so this समय try to
	 * get all the memory we're ever going to need.  Allocate the buffer
	 * without the inode lock held, which means we can sleep.
	 */
	अगर (sc->flags & XCHK_TRY_HARDER) अणु
		error = xchk_setup_xattr_buf(sc, XATTR_SIZE_MAX, 0);
		अगर (error)
			वापस error;
	पूर्ण

	वापस xchk_setup_inode_contents(sc, 0);
पूर्ण

/* Extended Attributes */

काष्ठा xchk_xattr अणु
	काष्ठा xfs_attr_list_context	context;
	काष्ठा xfs_scrub		*sc;
पूर्ण;

/*
 * Check that an extended attribute key can be looked up by hash.
 *
 * We use the XFS attribute list iterator (i.e. xfs_attr_list_ilocked)
 * to call this function क्रम every attribute key in an inode.  Once
 * we're here, we load the attribute value to see अगर any errors happen,
 * or अगर we get more or less data than we expected.
 */
अटल व्योम
xchk_xattr_listent(
	काष्ठा xfs_attr_list_context	*context,
	पूर्णांक				flags,
	अचिन्हित अक्षर			*name,
	पूर्णांक				namelen,
	पूर्णांक				valuelen)
अणु
	काष्ठा xchk_xattr		*sx;
	काष्ठा xfs_da_args		args = अणु शून्य पूर्ण;
	पूर्णांक				error = 0;

	sx = container_of(context, काष्ठा xchk_xattr, context);

	अगर (xchk_should_terminate(sx->sc, &error)) अणु
		context->seen_enough = error;
		वापस;
	पूर्ण

	अगर (flags & XFS_ATTR_INCOMPLETE) अणु
		/* Incomplete attr key, just mark the inode क्रम preening. */
		xchk_ino_set_preen(sx->sc, context->dp->i_ino);
		वापस;
	पूर्ण

	/* Does this name make sense? */
	अगर (!xfs_attr_namecheck(name, namelen)) अणु
		xchk_fblock_set_corrupt(sx->sc, XFS_ATTR_FORK, args.blkno);
		वापस;
	पूर्ण

	/*
	 * Try to allocate enough memory to extrat the attr value.  If that
	 * करोesn't work, we overload the seen_enough variable to convey
	 * the error message back to the मुख्य scrub function.
	 */
	error = xchk_setup_xattr_buf(sx->sc, valuelen, KM_MAYFAIL);
	अगर (error == -ENOMEM)
		error = -EDEADLOCK;
	अगर (error) अणु
		context->seen_enough = error;
		वापस;
	पूर्ण

	args.op_flags = XFS_DA_OP_NOTIME;
	args.attr_filter = flags & XFS_ATTR_NSP_ONDISK_MASK;
	args.geo = context->dp->i_mount->m_attr_geo;
	args.whichविभाजन = XFS_ATTR_FORK;
	args.dp = context->dp;
	args.name = name;
	args.namelen = namelen;
	args.hashval = xfs_da_hashname(args.name, args.namelen);
	args.trans = context->tp;
	args.value = xchk_xattr_valuebuf(sx->sc);
	args.valuelen = valuelen;

	error = xfs_attr_get_ilocked(&args);
	/* ENODATA means the hash lookup failed and the attr is bad */
	अगर (error == -ENODATA)
		error = -EFSCORRUPTED;
	अगर (!xchk_fblock_process_error(sx->sc, XFS_ATTR_FORK, args.blkno,
			&error))
		जाओ fail_xref;
	अगर (args.valuelen != valuelen)
		xchk_fblock_set_corrupt(sx->sc, XFS_ATTR_FORK,
					     args.blkno);
fail_xref:
	अगर (sx->sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		context->seen_enough = 1;
	वापस;
पूर्ण

/*
 * Mark a range [start, start+len) in this map.  Returns true अगर the
 * region was मुक्त, and false अगर there's a conflict or a problem.
 *
 * Within a अक्षर, the lowest bit of the अक्षर represents the byte with
 * the smallest address
 */
STATIC bool
xchk_xattr_set_map(
	काष्ठा xfs_scrub	*sc,
	अचिन्हित दीर्घ		*map,
	अचिन्हित पूर्णांक		start,
	अचिन्हित पूर्णांक		len)
अणु
	अचिन्हित पूर्णांक		mapsize = sc->mp->m_attr_geo->blksize;
	bool			ret = true;

	अगर (start >= mapsize)
		वापस false;
	अगर (start + len > mapsize) अणु
		len = mapsize - start;
		ret = false;
	पूर्ण

	अगर (find_next_bit(map, mapsize, start) < start + len)
		ret = false;
	biपंचांगap_set(map, start, len);

	वापस ret;
पूर्ण

/*
 * Check the leaf मुक्तmap from the usage biपंचांगap.  Returns false अगर the
 * attr मुक्तmap has problems or poपूर्णांकs to used space.
 */
STATIC bool
xchk_xattr_check_मुक्तmap(
	काष्ठा xfs_scrub		*sc,
	अचिन्हित दीर्घ			*map,
	काष्ठा xfs_attr3_icleaf_hdr	*leafhdr)
अणु
	अचिन्हित दीर्घ			*मुक्तmap = xchk_xattr_मुक्तmap(sc);
	अचिन्हित दीर्घ			*dsपंचांगap = xchk_xattr_dsपंचांगap(sc);
	अचिन्हित पूर्णांक			mapsize = sc->mp->m_attr_geo->blksize;
	पूर्णांक				i;

	/* Conकाष्ठा biपंचांगap of मुक्तmap contents. */
	biपंचांगap_zero(मुक्तmap, mapsize);
	क्रम (i = 0; i < XFS_ATTR_LEAF_MAPSIZE; i++) अणु
		अगर (!xchk_xattr_set_map(sc, मुक्तmap,
				leafhdr->मुक्तmap[i].base,
				leafhdr->मुक्तmap[i].size))
			वापस false;
	पूर्ण

	/* Look क्रम bits that are set in मुक्तmap and are marked in use. */
	वापस biपंचांगap_and(dsपंचांगap, मुक्तmap, map, mapsize) == 0;
पूर्ण

/*
 * Check this leaf entry's relations to everything अन्यथा.
 * Returns the number of bytes used क्रम the name/value data.
 */
STATIC व्योम
xchk_xattr_entry(
	काष्ठा xchk_da_btree		*ds,
	पूर्णांक				level,
	अक्षर				*buf_end,
	काष्ठा xfs_attr_leafblock	*leaf,
	काष्ठा xfs_attr3_icleaf_hdr	*leafhdr,
	काष्ठा xfs_attr_leaf_entry	*ent,
	पूर्णांक				idx,
	अचिन्हित पूर्णांक			*usedbytes,
	__u32				*last_hashval)
अणु
	काष्ठा xfs_mount		*mp = ds->state->mp;
	अचिन्हित दीर्घ			*usedmap = xchk_xattr_usedmap(ds->sc);
	अक्षर				*name_end;
	काष्ठा xfs_attr_leaf_name_local	*lentry;
	काष्ठा xfs_attr_leaf_name_remote *rentry;
	अचिन्हित पूर्णांक			nameidx;
	अचिन्हित पूर्णांक			namesize;

	अगर (ent->pad2 != 0)
		xchk_da_set_corrupt(ds, level);

	/* Hash values in order? */
	अगर (be32_to_cpu(ent->hashval) < *last_hashval)
		xchk_da_set_corrupt(ds, level);
	*last_hashval = be32_to_cpu(ent->hashval);

	nameidx = be16_to_cpu(ent->nameidx);
	अगर (nameidx < leafhdr->firstused ||
	    nameidx >= mp->m_attr_geo->blksize) अणु
		xchk_da_set_corrupt(ds, level);
		वापस;
	पूर्ण

	/* Check the name inक्रमmation. */
	अगर (ent->flags & XFS_ATTR_LOCAL) अणु
		lentry = xfs_attr3_leaf_name_local(leaf, idx);
		namesize = xfs_attr_leaf_entsize_local(lentry->namelen,
				be16_to_cpu(lentry->valuelen));
		name_end = (अक्षर *)lentry + namesize;
		अगर (lentry->namelen == 0)
			xchk_da_set_corrupt(ds, level);
	पूर्ण अन्यथा अणु
		rentry = xfs_attr3_leaf_name_remote(leaf, idx);
		namesize = xfs_attr_leaf_entsize_remote(rentry->namelen);
		name_end = (अक्षर *)rentry + namesize;
		अगर (rentry->namelen == 0 || rentry->valueblk == 0)
			xchk_da_set_corrupt(ds, level);
	पूर्ण
	अगर (name_end > buf_end)
		xchk_da_set_corrupt(ds, level);

	अगर (!xchk_xattr_set_map(ds->sc, usedmap, nameidx, namesize))
		xchk_da_set_corrupt(ds, level);
	अगर (!(ds->sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT))
		*usedbytes += namesize;
पूर्ण

/* Scrub an attribute leaf. */
STATIC पूर्णांक
xchk_xattr_block(
	काष्ठा xchk_da_btree		*ds,
	पूर्णांक				level)
अणु
	काष्ठा xfs_attr3_icleaf_hdr	leafhdr;
	काष्ठा xfs_mount		*mp = ds->state->mp;
	काष्ठा xfs_da_state_blk		*blk = &ds->state->path.blk[level];
	काष्ठा xfs_buf			*bp = blk->bp;
	xfs_dablk_t			*last_checked = ds->निजी;
	काष्ठा xfs_attr_leafblock	*leaf = bp->b_addr;
	काष्ठा xfs_attr_leaf_entry	*ent;
	काष्ठा xfs_attr_leaf_entry	*entries;
	अचिन्हित दीर्घ			*usedmap;
	अक्षर				*buf_end;
	माप_प्रकार				off;
	__u32				last_hashval = 0;
	अचिन्हित पूर्णांक			usedbytes = 0;
	अचिन्हित पूर्णांक			hdrsize;
	पूर्णांक				i;
	पूर्णांक				error;

	अगर (*last_checked == blk->blkno)
		वापस 0;

	/* Allocate memory क्रम block usage checking. */
	error = xchk_setup_xattr_buf(ds->sc, 0, KM_MAYFAIL);
	अगर (error == -ENOMEM)
		वापस -EDEADLOCK;
	अगर (error)
		वापस error;
	usedmap = xchk_xattr_usedmap(ds->sc);

	*last_checked = blk->blkno;
	biपंचांगap_zero(usedmap, mp->m_attr_geo->blksize);

	/* Check all the padding. */
	अगर (xfs_sb_version_hascrc(&ds->sc->mp->m_sb)) अणु
		काष्ठा xfs_attr3_leafblock	*leaf = bp->b_addr;

		अगर (leaf->hdr.pad1 != 0 || leaf->hdr.pad2 != 0 ||
		    leaf->hdr.info.hdr.pad != 0)
			xchk_da_set_corrupt(ds, level);
	पूर्ण अन्यथा अणु
		अगर (leaf->hdr.pad1 != 0 || leaf->hdr.info.pad != 0)
			xchk_da_set_corrupt(ds, level);
	पूर्ण

	/* Check the leaf header */
	xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &leafhdr, leaf);
	hdrsize = xfs_attr3_leaf_hdr_size(leaf);

	अगर (leafhdr.usedbytes > mp->m_attr_geo->blksize)
		xchk_da_set_corrupt(ds, level);
	अगर (leafhdr.firstused > mp->m_attr_geo->blksize)
		xchk_da_set_corrupt(ds, level);
	अगर (leafhdr.firstused < hdrsize)
		xchk_da_set_corrupt(ds, level);
	अगर (!xchk_xattr_set_map(ds->sc, usedmap, 0, hdrsize))
		xchk_da_set_corrupt(ds, level);

	अगर (ds->sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		जाओ out;

	entries = xfs_attr3_leaf_entryp(leaf);
	अगर ((अक्षर *)&entries[leafhdr.count] > (अक्षर *)leaf + leafhdr.firstused)
		xchk_da_set_corrupt(ds, level);

	buf_end = (अक्षर *)bp->b_addr + mp->m_attr_geo->blksize;
	क्रम (i = 0, ent = entries; i < leafhdr.count; ent++, i++) अणु
		/* Mark the leaf entry itself. */
		off = (अक्षर *)ent - (अक्षर *)leaf;
		अगर (!xchk_xattr_set_map(ds->sc, usedmap, off,
				माप(xfs_attr_leaf_entry_t))) अणु
			xchk_da_set_corrupt(ds, level);
			जाओ out;
		पूर्ण

		/* Check the entry and nameval. */
		xchk_xattr_entry(ds, level, buf_end, leaf, &leafhdr,
				ent, i, &usedbytes, &last_hashval);

		अगर (ds->sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
			जाओ out;
	पूर्ण

	अगर (!xchk_xattr_check_मुक्तmap(ds->sc, usedmap, &leafhdr))
		xchk_da_set_corrupt(ds, level);

	अगर (leafhdr.usedbytes != usedbytes)
		xchk_da_set_corrupt(ds, level);

out:
	वापस 0;
पूर्ण

/* Scrub a attribute btree record. */
STATIC पूर्णांक
xchk_xattr_rec(
	काष्ठा xchk_da_btree		*ds,
	पूर्णांक				level)
अणु
	काष्ठा xfs_mount		*mp = ds->state->mp;
	काष्ठा xfs_da_state_blk		*blk = &ds->state->path.blk[level];
	काष्ठा xfs_attr_leaf_name_local	*lentry;
	काष्ठा xfs_attr_leaf_name_remote	*rentry;
	काष्ठा xfs_buf			*bp;
	काष्ठा xfs_attr_leaf_entry	*ent;
	xfs_dahash_t			calc_hash;
	xfs_dahash_t			hash;
	पूर्णांक				nameidx;
	पूर्णांक				hdrsize;
	अचिन्हित पूर्णांक			badflags;
	पूर्णांक				error;

	ASSERT(blk->magic == XFS_ATTR_LEAF_MAGIC);

	ent = xfs_attr3_leaf_entryp(blk->bp->b_addr) + blk->index;

	/* Check the whole block, अगर necessary. */
	error = xchk_xattr_block(ds, level);
	अगर (error)
		जाओ out;
	अगर (ds->sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		जाओ out;

	/* Check the hash of the entry. */
	error = xchk_da_btree_hash(ds, level, &ent->hashval);
	अगर (error)
		जाओ out;

	/* Find the attr entry's location. */
	bp = blk->bp;
	hdrsize = xfs_attr3_leaf_hdr_size(bp->b_addr);
	nameidx = be16_to_cpu(ent->nameidx);
	अगर (nameidx < hdrsize || nameidx >= mp->m_attr_geo->blksize) अणु
		xchk_da_set_corrupt(ds, level);
		जाओ out;
	पूर्ण

	/* Retrieve the entry and check it. */
	hash = be32_to_cpu(ent->hashval);
	badflags = ~(XFS_ATTR_LOCAL | XFS_ATTR_ROOT | XFS_ATTR_SECURE |
			XFS_ATTR_INCOMPLETE);
	अगर ((ent->flags & badflags) != 0)
		xchk_da_set_corrupt(ds, level);
	अगर (ent->flags & XFS_ATTR_LOCAL) अणु
		lentry = (काष्ठा xfs_attr_leaf_name_local *)
				(((अक्षर *)bp->b_addr) + nameidx);
		अगर (lentry->namelen <= 0) अणु
			xchk_da_set_corrupt(ds, level);
			जाओ out;
		पूर्ण
		calc_hash = xfs_da_hashname(lentry->nameval, lentry->namelen);
	पूर्ण अन्यथा अणु
		rentry = (काष्ठा xfs_attr_leaf_name_remote *)
				(((अक्षर *)bp->b_addr) + nameidx);
		अगर (rentry->namelen <= 0) अणु
			xchk_da_set_corrupt(ds, level);
			जाओ out;
		पूर्ण
		calc_hash = xfs_da_hashname(rentry->name, rentry->namelen);
	पूर्ण
	अगर (calc_hash != hash)
		xchk_da_set_corrupt(ds, level);

out:
	वापस error;
पूर्ण

/* Scrub the extended attribute metadata. */
पूर्णांक
xchk_xattr(
	काष्ठा xfs_scrub		*sc)
अणु
	काष्ठा xchk_xattr		sx;
	xfs_dablk_t			last_checked = -1U;
	पूर्णांक				error = 0;

	अगर (!xfs_inode_hasattr(sc->ip))
		वापस -ENOENT;

	स_रखो(&sx, 0, माप(sx));
	/* Check attribute tree काष्ठाure */
	error = xchk_da_btree(sc, XFS_ATTR_FORK, xchk_xattr_rec,
			&last_checked);
	अगर (error)
		जाओ out;

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		जाओ out;

	/* Check that every attr key can also be looked up by hash. */
	sx.context.dp = sc->ip;
	sx.context.resynch = 1;
	sx.context.put_listent = xchk_xattr_listent;
	sx.context.tp = sc->tp;
	sx.context.allow_incomplete = true;
	sx.sc = sc;

	/*
	 * Look up every xattr in this file by name.
	 *
	 * Use the backend implementation of xfs_attr_list to call
	 * xchk_xattr_listent on every attribute key in this inode.
	 * In other words, we use the same iterator/callback mechanism
	 * that listattr uses to scrub extended attributes, though in our
	 * _listent function, we check the value of the attribute.
	 *
	 * The VFS only locks i_rwsem when modअगरying attrs, so keep all
	 * three locks held because that's the only way to ensure we're
	 * the only thपढ़ो poking पूर्णांकo the da btree.  We traverse the da
	 * btree जबतक holding a leaf buffer locked क्रम the xattr name
	 * iteration, which करोesn't really follow the usual buffer
	 * locking order.
	 */
	error = xfs_attr_list_ilocked(&sx.context);
	अगर (!xchk_fblock_process_error(sc, XFS_ATTR_FORK, 0, &error))
		जाओ out;

	/* Did our listent function try to वापस any errors? */
	अगर (sx.context.seen_enough < 0)
		error = sx.context.seen_enough;
out:
	वापस error;
पूर्ण
