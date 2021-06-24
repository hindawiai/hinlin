<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * All Rights Reserved.
 */

#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_inode_item.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_da_format.h"
#समावेश "xfs_da_btree.h"
#समावेश "xfs_dir2_priv.h"
#समावेश "xfs_attr_leaf.h"
#समावेश "xfs_types.h"
#समावेश "xfs_errortag.h"

kmem_zone_t *xfs_अगरork_zone;

व्योम
xfs_init_local_विभाजन(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	स्थिर व्योम		*data,
	पूर्णांक64_t			size)
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	पूर्णांक			mem_size = size, real_size = 0;
	bool			zero_terminate;

	/*
	 * If we are using the local विभाजन to store a symlink body we need to
	 * zero-terminate it so that we can pass it back to the VFS directly.
	 * Overallocate the in-memory विभाजन by one क्रम that and add a zero
	 * to terminate it below.
	 */
	zero_terminate = S_ISLNK(VFS_I(ip)->i_mode);
	अगर (zero_terminate)
		mem_size++;

	अगर (size) अणु
		real_size = roundup(mem_size, 4);
		अगरp->अगर_u1.अगर_data = kmem_alloc(real_size, KM_NOFS);
		स_नकल(अगरp->अगर_u1.अगर_data, data, size);
		अगर (zero_terminate)
			अगरp->अगर_u1.अगर_data[size] = '\0';
	पूर्ण अन्यथा अणु
		अगरp->अगर_u1.अगर_data = शून्य;
	पूर्ण

	अगरp->अगर_bytes = size;
पूर्ण

/*
 * The file is in-lined in the on-disk inode.
 */
STATIC पूर्णांक
xfs_अगरormat_local(
	xfs_inode_t	*ip,
	xfs_dinode_t	*dip,
	पूर्णांक		whichविभाजन,
	पूर्णांक		size)
अणु
	/*
	 * If the size is unreasonable, then something
	 * is wrong and we just bail out rather than crash in
	 * kmem_alloc() or स_नकल() below.
	 */
	अगर (unlikely(size > XFS_DFORK_SIZE(dip, ip->i_mount, whichविभाजन))) अणु
		xfs_warn(ip->i_mount,
	"corrupt inode %Lu (bad size %d for local fork, size = %zd).",
			(अचिन्हित दीर्घ दीर्घ) ip->i_ino, size,
			XFS_DFORK_SIZE(dip, ip->i_mount, whichविभाजन));
		xfs_inode_verअगरier_error(ip, -EFSCORRUPTED,
				"xfs_iformat_local", dip, माप(*dip),
				__this_address);
		वापस -EFSCORRUPTED;
	पूर्ण

	xfs_init_local_विभाजन(ip, whichविभाजन, XFS_DFORK_PTR(dip, whichविभाजन), size);
	वापस 0;
पूर्ण

/*
 * The file consists of a set of extents all of which fit पूर्णांकo the on-disk
 * inode.
 */
STATIC पूर्णांक
xfs_अगरormat_extents(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_dinode	*dip,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	पूर्णांक			state = xfs_bmap_विभाजन_to_state(whichविभाजन);
	पूर्णांक			nex = XFS_DFORK_NEXTENTS(dip, whichविभाजन);
	पूर्णांक			size = nex * माप(xfs_bmbt_rec_t);
	काष्ठा xfs_iext_cursor	icur;
	काष्ठा xfs_bmbt_rec	*dp;
	काष्ठा xfs_bmbt_irec	new;
	पूर्णांक			i;

	/*
	 * If the number of extents is unreasonable, then something is wrong and
	 * we just bail out rather than crash in kmem_alloc() or स_नकल() below.
	 */
	अगर (unlikely(size < 0 || size > XFS_DFORK_SIZE(dip, mp, whichविभाजन))) अणु
		xfs_warn(ip->i_mount, "corrupt inode %Lu ((a)extents = %d).",
			(अचिन्हित दीर्घ दीर्घ) ip->i_ino, nex);
		xfs_inode_verअगरier_error(ip, -EFSCORRUPTED,
				"xfs_iformat_extents(1)", dip, माप(*dip),
				__this_address);
		वापस -EFSCORRUPTED;
	पूर्ण

	अगरp->अगर_bytes = 0;
	अगरp->अगर_u1.अगर_root = शून्य;
	अगरp->अगर_height = 0;
	अगर (size) अणु
		dp = (xfs_bmbt_rec_t *) XFS_DFORK_PTR(dip, whichविभाजन);

		xfs_iext_first(अगरp, &icur);
		क्रम (i = 0; i < nex; i++, dp++) अणु
			xfs_failaddr_t	fa;

			xfs_bmbt_disk_get_all(dp, &new);
			fa = xfs_bmap_validate_extent(ip, whichविभाजन, &new);
			अगर (fa) अणु
				xfs_inode_verअगरier_error(ip, -EFSCORRUPTED,
						"xfs_iformat_extents(2)",
						dp, माप(*dp), fa);
				वापस -EFSCORRUPTED;
			पूर्ण

			xfs_iext_insert(ip, &icur, &new, state);
			trace_xfs_पढ़ो_extent(ip, &icur, state, _THIS_IP_);
			xfs_iext_next(अगरp, &icur);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * The file has too many extents to fit पूर्णांकo
 * the inode, so they are in B-tree क्रमmat.
 * Allocate a buffer क्रम the root of the B-tree
 * and copy the root पूर्णांकo it.  The i_extents
 * field will reमुख्य शून्य until all of the
 * extents are पढ़ो in (when they are needed).
 */
STATIC पूर्णांक
xfs_अगरormat_btree(
	xfs_inode_t		*ip,
	xfs_dinode_t		*dip,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_bmdr_block_t	*dfp;
	काष्ठा xfs_अगरork	*अगरp;
	/* REFERENCED */
	पूर्णांक			nrecs;
	पूर्णांक			size;
	पूर्णांक			level;

	अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	dfp = (xfs_bmdr_block_t *)XFS_DFORK_PTR(dip, whichविभाजन);
	size = XFS_BMAP_BROOT_SPACE(mp, dfp);
	nrecs = be16_to_cpu(dfp->bb_numrecs);
	level = be16_to_cpu(dfp->bb_level);

	/*
	 * blow out अगर -- विभाजन has less extents than can fit in
	 * विभाजन (विभाजन shouldn't be a btree क्रमmat), root btree
	 * block has more records than can fit पूर्णांकo the विभाजन,
	 * or the number of extents is greater than the number of
	 * blocks.
	 */
	अगर (unlikely(अगरp->अगर_nextents <= XFS_IFORK_MAXEXT(ip, whichविभाजन) ||
		     nrecs == 0 ||
		     XFS_BMDR_SPACE_CALC(nrecs) >
					XFS_DFORK_SIZE(dip, mp, whichविभाजन) ||
		     अगरp->अगर_nextents > ip->i_nblocks) ||
		     level == 0 || level > XFS_BM_MAXLEVELS(mp, whichविभाजन)) अणु
		xfs_warn(mp, "corrupt inode %Lu (btree).",
					(अचिन्हित दीर्घ दीर्घ) ip->i_ino);
		xfs_inode_verअगरier_error(ip, -EFSCORRUPTED,
				"xfs_iformat_btree", dfp, size,
				__this_address);
		वापस -EFSCORRUPTED;
	पूर्ण

	अगरp->अगर_broot_bytes = size;
	अगरp->अगर_broot = kmem_alloc(size, KM_NOFS);
	ASSERT(अगरp->अगर_broot != शून्य);
	/*
	 * Copy and convert from the on-disk काष्ठाure
	 * to the in-memory काष्ठाure.
	 */
	xfs_bmdr_to_bmbt(ip, dfp, XFS_DFORK_SIZE(dip, ip->i_mount, whichविभाजन),
			 अगरp->अगर_broot, size);

	अगरp->अगर_bytes = 0;
	अगरp->अगर_u1.अगर_root = शून्य;
	अगरp->अगर_height = 0;
	वापस 0;
पूर्ण

पूर्णांक
xfs_अगरormat_data_विभाजन(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_dinode	*dip)
अणु
	काष्ठा inode		*inode = VFS_I(ip);
	पूर्णांक			error;

	/*
	 * Initialize the extent count early, as the per-क्रमmat routines may
	 * depend on it.
	 */
	ip->i_df.अगर_क्रमmat = dip->di_क्रमmat;
	ip->i_df.अगर_nextents = be32_to_cpu(dip->di_nextents);

	चयन (inode->i_mode & S_IFMT) अणु
	हाल S_IFIFO:
	हाल S_IFCHR:
	हाल S_IFBLK:
	हाल S_IFSOCK:
		ip->i_disk_size = 0;
		inode->i_rdev = xfs_to_linux_dev_t(xfs_dinode_get_rdev(dip));
		वापस 0;
	हाल S_IFREG:
	हाल S_IFLNK:
	हाल S_IFसूची:
		चयन (ip->i_df.अगर_क्रमmat) अणु
		हाल XFS_DINODE_FMT_LOCAL:
			error = xfs_अगरormat_local(ip, dip, XFS_DATA_FORK,
					be64_to_cpu(dip->di_size));
			अगर (!error)
				error = xfs_अगरork_verअगरy_local_data(ip);
			वापस error;
		हाल XFS_DINODE_FMT_EXTENTS:
			वापस xfs_अगरormat_extents(ip, dip, XFS_DATA_FORK);
		हाल XFS_DINODE_FMT_BTREE:
			वापस xfs_अगरormat_btree(ip, dip, XFS_DATA_FORK);
		शेष:
			xfs_inode_verअगरier_error(ip, -EFSCORRUPTED, __func__,
					dip, माप(*dip), __this_address);
			वापस -EFSCORRUPTED;
		पूर्ण
		अवरोध;
	शेष:
		xfs_inode_verअगरier_error(ip, -EFSCORRUPTED, __func__, dip,
				माप(*dip), __this_address);
		वापस -EFSCORRUPTED;
	पूर्ण
पूर्ण

अटल uपूर्णांक16_t
xfs_dविभाजन_attr_लघुक्रमm_size(
	काष्ठा xfs_dinode		*dip)
अणु
	काष्ठा xfs_attr_लघुक्रमm	*atp =
		(काष्ठा xfs_attr_लघुक्रमm *)XFS_DFORK_APTR(dip);

	वापस be16_to_cpu(atp->hdr.totsize);
पूर्ण

काष्ठा xfs_अगरork *
xfs_अगरork_alloc(
	क्रमागत xfs_dinode_fmt	क्रमmat,
	xfs_extnum_t		nextents)
अणु
	काष्ठा xfs_अगरork	*अगरp;

	अगरp = kmem_cache_zalloc(xfs_अगरork_zone, GFP_NOFS | __GFP_NOFAIL);
	अगरp->अगर_क्रमmat = क्रमmat;
	अगरp->अगर_nextents = nextents;
	वापस अगरp;
पूर्ण

पूर्णांक
xfs_अगरormat_attr_विभाजन(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_dinode	*dip)
अणु
	पूर्णांक			error = 0;

	/*
	 * Initialize the extent count early, as the per-क्रमmat routines may
	 * depend on it.
	 */
	ip->i_afp = xfs_अगरork_alloc(dip->di_aक्रमmat,
				be16_to_cpu(dip->di_anextents));

	चयन (ip->i_afp->अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_LOCAL:
		error = xfs_अगरormat_local(ip, dip, XFS_ATTR_FORK,
				xfs_dविभाजन_attr_लघुक्रमm_size(dip));
		अगर (!error)
			error = xfs_अगरork_verअगरy_local_attr(ip);
		अवरोध;
	हाल XFS_DINODE_FMT_EXTENTS:
		error = xfs_अगरormat_extents(ip, dip, XFS_ATTR_FORK);
		अवरोध;
	हाल XFS_DINODE_FMT_BTREE:
		error = xfs_अगरormat_btree(ip, dip, XFS_ATTR_FORK);
		अवरोध;
	शेष:
		xfs_inode_verअगरier_error(ip, error, __func__, dip,
				माप(*dip), __this_address);
		error = -EFSCORRUPTED;
		अवरोध;
	पूर्ण

	अगर (error) अणु
		kmem_cache_मुक्त(xfs_अगरork_zone, ip->i_afp);
		ip->i_afp = शून्य;
	पूर्ण
	वापस error;
पूर्ण

/*
 * Reallocate the space क्रम अगर_broot based on the number of records
 * being added or deleted as indicated in rec_dअगरf.  Move the records
 * and poपूर्णांकers in अगर_broot to fit the new size.  When shrinking this
 * will eliminate holes between the records and poपूर्णांकers created by
 * the caller.  When growing this will create holes to be filled in
 * by the caller.
 *
 * The caller must not request to add more records than would fit in
 * the on-disk inode root.  If the अगर_broot is currently शून्य, then
 * अगर we are adding records, one will be allocated.  The caller must also
 * not request that the number of records go below zero, although
 * it can go to zero.
 *
 * ip -- the inode whose अगर_broot area is changing
 * ext_dअगरf -- the change in the number of records, positive or negative,
 *	 requested क्रम the अगर_broot array.
 */
व्योम
xfs_iroot_पुनः_स्मृति(
	xfs_inode_t		*ip,
	पूर्णांक			rec_dअगरf,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	पूर्णांक			cur_max;
	काष्ठा xfs_अगरork	*अगरp;
	काष्ठा xfs_btree_block	*new_broot;
	पूर्णांक			new_max;
	माप_प्रकार			new_size;
	अक्षर			*np;
	अक्षर			*op;

	/*
	 * Handle the degenerate हाल quietly.
	 */
	अगर (rec_dअगरf == 0) अणु
		वापस;
	पूर्ण

	अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	अगर (rec_dअगरf > 0) अणु
		/*
		 * If there wasn't any memory allocated beक्रमe, just
		 * allocate it now and get out.
		 */
		अगर (अगरp->अगर_broot_bytes == 0) अणु
			new_size = XFS_BMAP_BROOT_SPACE_CALC(mp, rec_dअगरf);
			अगरp->अगर_broot = kmem_alloc(new_size, KM_NOFS);
			अगरp->अगर_broot_bytes = (पूर्णांक)new_size;
			वापस;
		पूर्ण

		/*
		 * If there is alपढ़ोy an existing अगर_broot, then we need
		 * to पुनः_स्मृति() it and shअगरt the poपूर्णांकers to their new
		 * location.  The records करोn't change location because
		 * they are kept butted up against the btree block header.
		 */
		cur_max = xfs_bmbt_maxrecs(mp, अगरp->अगर_broot_bytes, 0);
		new_max = cur_max + rec_dअगरf;
		new_size = XFS_BMAP_BROOT_SPACE_CALC(mp, new_max);
		अगरp->अगर_broot = kपुनः_स्मृति(अगरp->अगर_broot, new_size,
					 GFP_NOFS | __GFP_NOFAIL);
		op = (अक्षर *)XFS_BMAP_BROOT_PTR_ADDR(mp, अगरp->अगर_broot, 1,
						     अगरp->अगर_broot_bytes);
		np = (अक्षर *)XFS_BMAP_BROOT_PTR_ADDR(mp, अगरp->अगर_broot, 1,
						     (पूर्णांक)new_size);
		अगरp->अगर_broot_bytes = (पूर्णांक)new_size;
		ASSERT(XFS_BMAP_BMDR_SPACE(अगरp->अगर_broot) <=
			XFS_IFORK_SIZE(ip, whichविभाजन));
		स_हटाओ(np, op, cur_max * (uपूर्णांक)माप(xfs_fsblock_t));
		वापस;
	पूर्ण

	/*
	 * rec_dअगरf is less than 0.  In this हाल, we are shrinking the
	 * अगर_broot buffer.  It must alपढ़ोy exist.  If we go to zero
	 * records, just get rid of the root and clear the status bit.
	 */
	ASSERT((अगरp->अगर_broot != शून्य) && (अगरp->अगर_broot_bytes > 0));
	cur_max = xfs_bmbt_maxrecs(mp, अगरp->अगर_broot_bytes, 0);
	new_max = cur_max + rec_dअगरf;
	ASSERT(new_max >= 0);
	अगर (new_max > 0)
		new_size = XFS_BMAP_BROOT_SPACE_CALC(mp, new_max);
	अन्यथा
		new_size = 0;
	अगर (new_size > 0) अणु
		new_broot = kmem_alloc(new_size, KM_NOFS);
		/*
		 * First copy over the btree block header.
		 */
		स_नकल(new_broot, अगरp->अगर_broot,
			XFS_BMBT_BLOCK_LEN(ip->i_mount));
	पूर्ण अन्यथा अणु
		new_broot = शून्य;
	पूर्ण

	/*
	 * Only copy the records and poपूर्णांकers अगर there are any.
	 */
	अगर (new_max > 0) अणु
		/*
		 * First copy the records.
		 */
		op = (अक्षर *)XFS_BMBT_REC_ADDR(mp, अगरp->अगर_broot, 1);
		np = (अक्षर *)XFS_BMBT_REC_ADDR(mp, new_broot, 1);
		स_नकल(np, op, new_max * (uपूर्णांक)माप(xfs_bmbt_rec_t));

		/*
		 * Then copy the poपूर्णांकers.
		 */
		op = (अक्षर *)XFS_BMAP_BROOT_PTR_ADDR(mp, अगरp->अगर_broot, 1,
						     अगरp->अगर_broot_bytes);
		np = (अक्षर *)XFS_BMAP_BROOT_PTR_ADDR(mp, new_broot, 1,
						     (पूर्णांक)new_size);
		स_नकल(np, op, new_max * (uपूर्णांक)माप(xfs_fsblock_t));
	पूर्ण
	kmem_मुक्त(अगरp->अगर_broot);
	अगरp->अगर_broot = new_broot;
	अगरp->अगर_broot_bytes = (पूर्णांक)new_size;
	अगर (अगरp->अगर_broot)
		ASSERT(XFS_BMAP_BMDR_SPACE(अगरp->अगर_broot) <=
			XFS_IFORK_SIZE(ip, whichविभाजन));
	वापस;
पूर्ण


/*
 * This is called when the amount of space needed क्रम अगर_data
 * is increased or decreased.  The change in size is indicated by
 * the number of bytes that need to be added or deleted in the
 * byte_dअगरf parameter.
 *
 * If the amount of space needed has decreased below the size of the
 * अंतरभूत buffer, then चयन to using the अंतरभूत buffer.  Otherwise,
 * use kmem_पुनः_स्मृति() or kmem_alloc() to adjust the size of the buffer
 * to what is needed.
 *
 * ip -- the inode whose अगर_data area is changing
 * byte_dअगरf -- the change in the number of bytes, positive or negative,
 *	 requested क्रम the अगर_data array.
 */
व्योम
xfs_idata_पुनः_स्मृति(
	काष्ठा xfs_inode	*ip,
	पूर्णांक64_t			byte_dअगरf,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	पूर्णांक64_t			new_size = अगरp->अगर_bytes + byte_dअगरf;

	ASSERT(new_size >= 0);
	ASSERT(new_size <= XFS_IFORK_SIZE(ip, whichविभाजन));

	अगर (byte_dअगरf == 0)
		वापस;

	अगर (new_size == 0) अणु
		kmem_मुक्त(अगरp->अगर_u1.अगर_data);
		अगरp->अगर_u1.अगर_data = शून्य;
		अगरp->अगर_bytes = 0;
		वापस;
	पूर्ण

	/*
	 * For अंतरभूत data, the underlying buffer must be a multiple of 4 bytes
	 * in size so that it can be logged and stay on word boundaries.
	 * We enक्रमce that here.
	 */
	अगरp->अगर_u1.अगर_data = kपुनः_स्मृति(अगरp->अगर_u1.अगर_data, roundup(new_size, 4),
				      GFP_NOFS | __GFP_NOFAIL);
	अगरp->अगर_bytes = new_size;
पूर्ण

व्योम
xfs_idestroy_विभाजन(
	काष्ठा xfs_अगरork	*अगरp)
अणु
	अगर (अगरp->अगर_broot != शून्य) अणु
		kmem_मुक्त(अगरp->अगर_broot);
		अगरp->अगर_broot = शून्य;
	पूर्ण

	चयन (अगरp->अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_LOCAL:
		kmem_मुक्त(अगरp->अगर_u1.अगर_data);
		अगरp->अगर_u1.अगर_data = शून्य;
		अवरोध;
	हाल XFS_DINODE_FMT_EXTENTS:
	हाल XFS_DINODE_FMT_BTREE:
		अगर (अगरp->अगर_height)
			xfs_iext_destroy(अगरp);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Convert in-core extents to on-disk क्रमm
 *
 * In the हाल of the data विभाजन, the in-core and on-disk विभाजन sizes can be
 * dअगरferent due to delayed allocation extents. We only copy on-disk extents
 * here, so callers must always use the physical विभाजन size to determine the
 * size of the buffer passed to this routine.  We will वापस the size actually
 * used.
 */
पूर्णांक
xfs_iextents_copy(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_bmbt_rec	*dp,
	पूर्णांक			whichविभाजन)
अणु
	पूर्णांक			state = xfs_bmap_विभाजन_to_state(whichविभाजन);
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_iext_cursor	icur;
	काष्ठा xfs_bmbt_irec	rec;
	पूर्णांक64_t			copied = 0;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL | XFS_ILOCK_SHARED));
	ASSERT(अगरp->अगर_bytes > 0);

	क्रम_each_xfs_iext(अगरp, &icur, &rec) अणु
		अगर (isnullstartblock(rec.br_startblock))
			जारी;
		ASSERT(xfs_bmap_validate_extent(ip, whichविभाजन, &rec) == शून्य);
		xfs_bmbt_disk_set_all(dp, &rec);
		trace_xfs_ग_लिखो_extent(ip, &icur, state, _RET_IP_);
		copied += माप(काष्ठा xfs_bmbt_rec);
		dp++;
	पूर्ण

	ASSERT(copied > 0);
	ASSERT(copied <= अगरp->अगर_bytes);
	वापस copied;
पूर्ण

/*
 * Each of the following हालs stores data पूर्णांकo the same region
 * of the on-disk inode, so only one of them can be valid at
 * any given समय. While it is possible to have conflicting क्रमmats
 * and log flags, e.g. having XFS_ILOG_?DATA set when the विभाजन is
 * in EXTENTS क्रमmat, this can only happen when the विभाजन has
 * changed क्रमmats after being modअगरied but beक्रमe being flushed.
 * In these हालs, the क्रमmat always takes precedence, because the
 * क्रमmat indicates the current state of the विभाजन.
 */
व्योम
xfs_अगरlush_विभाजन(
	xfs_inode_t		*ip,
	xfs_dinode_t		*dip,
	काष्ठा xfs_inode_log_item *iip,
	पूर्णांक			whichविभाजन)
अणु
	अक्षर			*cp;
	काष्ठा xfs_अगरork	*अगरp;
	xfs_mount_t		*mp;
	अटल स्थिर लघु	brootflag[2] =
		अणु XFS_ILOG_DBROOT, XFS_ILOG_ABROOT पूर्ण;
	अटल स्थिर लघु	dataflag[2] =
		अणु XFS_ILOG_DDATA, XFS_ILOG_ADATA पूर्ण;
	अटल स्थिर लघु	extflag[2] =
		अणु XFS_ILOG_DEXT, XFS_ILOG_AEXT पूर्ण;

	अगर (!iip)
		वापस;
	अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	/*
	 * This can happen अगर we gave up in अगरormat in an error path,
	 * क्रम the attribute विभाजन.
	 */
	अगर (!अगरp) अणु
		ASSERT(whichविभाजन == XFS_ATTR_FORK);
		वापस;
	पूर्ण
	cp = XFS_DFORK_PTR(dip, whichविभाजन);
	mp = ip->i_mount;
	चयन (अगरp->अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_LOCAL:
		अगर ((iip->ili_fields & dataflag[whichविभाजन]) &&
		    (अगरp->अगर_bytes > 0)) अणु
			ASSERT(अगरp->अगर_u1.अगर_data != शून्य);
			ASSERT(अगरp->अगर_bytes <= XFS_IFORK_SIZE(ip, whichविभाजन));
			स_नकल(cp, अगरp->अगर_u1.अगर_data, अगरp->अगर_bytes);
		पूर्ण
		अवरोध;

	हाल XFS_DINODE_FMT_EXTENTS:
		अगर ((iip->ili_fields & extflag[whichविभाजन]) &&
		    (अगरp->अगर_bytes > 0)) अणु
			ASSERT(अगरp->अगर_nextents > 0);
			(व्योम)xfs_iextents_copy(ip, (xfs_bmbt_rec_t *)cp,
				whichविभाजन);
		पूर्ण
		अवरोध;

	हाल XFS_DINODE_FMT_BTREE:
		अगर ((iip->ili_fields & brootflag[whichविभाजन]) &&
		    (अगरp->अगर_broot_bytes > 0)) अणु
			ASSERT(अगरp->अगर_broot != शून्य);
			ASSERT(XFS_BMAP_BMDR_SPACE(अगरp->अगर_broot) <=
			        XFS_IFORK_SIZE(ip, whichविभाजन));
			xfs_bmbt_to_bmdr(mp, अगरp->अगर_broot, अगरp->अगर_broot_bytes,
				(xfs_bmdr_block_t *)cp,
				XFS_DFORK_SIZE(dip, mp, whichविभाजन));
		पूर्ण
		अवरोध;

	हाल XFS_DINODE_FMT_DEV:
		अगर (iip->ili_fields & XFS_ILOG_DEV) अणु
			ASSERT(whichविभाजन == XFS_DATA_FORK);
			xfs_dinode_put_rdev(dip,
					linux_to_xfs_dev_t(VFS_I(ip)->i_rdev));
		पूर्ण
		अवरोध;

	शेष:
		ASSERT(0);
		अवरोध;
	पूर्ण
पूर्ण

/* Convert bmap state flags to an inode विभाजन. */
काष्ठा xfs_अगरork *
xfs_iext_state_to_विभाजन(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			state)
अणु
	अगर (state & BMAP_COWFORK)
		वापस ip->i_cowfp;
	अन्यथा अगर (state & BMAP_ATTRFORK)
		वापस ip->i_afp;
	वापस &ip->i_df;
पूर्ण

/*
 * Initialize an inode's copy-on-ग_लिखो विभाजन.
 */
व्योम
xfs_अगरork_init_cow(
	काष्ठा xfs_inode	*ip)
अणु
	अगर (ip->i_cowfp)
		वापस;

	ip->i_cowfp = kmem_cache_zalloc(xfs_अगरork_zone,
				       GFP_NOFS | __GFP_NOFAIL);
	ip->i_cowfp->अगर_क्रमmat = XFS_DINODE_FMT_EXTENTS;
पूर्ण

/* Verअगरy the अंतरभूत contents of the data विभाजन of an inode. */
पूर्णांक
xfs_अगरork_verअगरy_local_data(
	काष्ठा xfs_inode	*ip)
अणु
	xfs_failaddr_t		fa = शून्य;

	चयन (VFS_I(ip)->i_mode & S_IFMT) अणु
	हाल S_IFसूची:
		fa = xfs_dir2_sf_verअगरy(ip);
		अवरोध;
	हाल S_IFLNK:
		fa = xfs_symlink_लघुक्रमm_verअगरy(ip);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (fa) अणु
		xfs_inode_verअगरier_error(ip, -EFSCORRUPTED, "data fork",
				ip->i_df.अगर_u1.अगर_data, ip->i_df.अगर_bytes, fa);
		वापस -EFSCORRUPTED;
	पूर्ण

	वापस 0;
पूर्ण

/* Verअगरy the अंतरभूत contents of the attr विभाजन of an inode. */
पूर्णांक
xfs_अगरork_verअगरy_local_attr(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_अगरork	*अगरp = ip->i_afp;
	xfs_failaddr_t		fa;

	अगर (!अगरp)
		fa = __this_address;
	अन्यथा
		fa = xfs_attr_लघुक्रमm_verअगरy(ip);

	अगर (fa) अणु
		xfs_inode_verअगरier_error(ip, -EFSCORRUPTED, "attr fork",
				अगरp ? अगरp->अगर_u1.अगर_data : शून्य,
				अगरp ? अगरp->अगर_bytes : 0, fa);
		वापस -EFSCORRUPTED;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
xfs_iext_count_may_overflow(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	पूर्णांक			nr_to_add)
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	uपूर्णांक64_t		max_exts;
	uपूर्णांक64_t		nr_exts;

	अगर (whichविभाजन == XFS_COW_FORK)
		वापस 0;

	max_exts = (whichविभाजन == XFS_ATTR_FORK) ? MAXAEXTNUM : MAXEXTNUM;

	अगर (XFS_TEST_ERROR(false, ip->i_mount, XFS_ERRTAG_REDUCE_MAX_IEXTENTS))
		max_exts = 10;

	nr_exts = अगरp->अगर_nextents + nr_to_add;
	अगर (nr_exts < अगरp->अगर_nextents || nr_exts > max_exts)
		वापस -EFBIG;

	वापस 0;
पूर्ण
