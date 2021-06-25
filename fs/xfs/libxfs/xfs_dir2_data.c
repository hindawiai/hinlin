<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
 * Copyright (c) 2013 Red Hat, Inc.
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
#समावेश "xfs_dir2.h"
#समावेश "xfs_dir2_priv.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_log.h"

अटल xfs_failaddr_t xfs_dir2_data_मुक्तfind_verअगरy(
		काष्ठा xfs_dir2_data_hdr *hdr, काष्ठा xfs_dir2_data_मुक्त *bf,
		काष्ठा xfs_dir2_data_unused *dup,
		काष्ठा xfs_dir2_data_मुक्त **bf_ent);

काष्ठा xfs_dir2_data_मुक्त *
xfs_dir2_data_bestमुक्त_p(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_dir2_data_hdr	*hdr)
अणु
	अगर (xfs_sb_version_hascrc(&mp->m_sb))
		वापस ((काष्ठा xfs_dir3_data_hdr *)hdr)->best_मुक्त;
	वापस hdr->bestमुक्त;
पूर्ण

/*
 * Poपूर्णांकer to an entry's tag word.
 */
__be16 *
xfs_dir2_data_entry_tag_p(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_dir2_data_entry	*dep)
अणु
	वापस (__be16 *)((अक्षर *)dep +
		xfs_dir2_data_entsize(mp, dep->namelen) - माप(__be16));
पूर्ण

uपूर्णांक8_t
xfs_dir2_data_get_ftype(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_dir2_data_entry	*dep)
अणु
	अगर (xfs_sb_version_hasftype(&mp->m_sb)) अणु
		uपूर्णांक8_t			ftype = dep->name[dep->namelen];

		अगर (likely(ftype < XFS_सूची3_FT_MAX))
			वापस ftype;
	पूर्ण

	वापस XFS_सूची3_FT_UNKNOWN;
पूर्ण

व्योम
xfs_dir2_data_put_ftype(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_dir2_data_entry	*dep,
	uपूर्णांक8_t				ftype)
अणु
	ASSERT(ftype < XFS_सूची3_FT_MAX);
	ASSERT(dep->namelen != 0);

	अगर (xfs_sb_version_hasftype(&mp->m_sb))
		dep->name[dep->namelen] = ftype;
पूर्ण

/*
 * The number of leaf entries is limited by the size of the block and the amount
 * of space used by the data entries.  We करोn't know how much space is used by
 * the data entries yet, so just ensure that the count falls somewhere inside
 * the block right now.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
xfs_dir2_data_max_leaf_entries(
	काष्ठा xfs_da_geometry		*geo)
अणु
	वापस (geo->blksize - माप(काष्ठा xfs_dir2_block_tail) -
		geo->data_entry_offset) /
			माप(काष्ठा xfs_dir2_leaf_entry);
पूर्ण

/*
 * Check the consistency of the data block.
 * The input can also be a block-क्रमmat directory.
 * Return शून्य अगर the buffer is good, otherwise the address of the error.
 */
xfs_failaddr_t
__xfs_dir3_data_check(
	काष्ठा xfs_inode	*dp,		/* incore inode poपूर्णांकer */
	काष्ठा xfs_buf		*bp)		/* data block's buffer */
अणु
	xfs_dir2_dataptr_t	addr;		/* addr क्रम leaf lookup */
	xfs_dir2_data_मुक्त_t	*bf;		/* bestमुक्त table */
	xfs_dir2_block_tail_t	*btp=शून्य;	/* block tail */
	पूर्णांक			count;		/* count of entries found */
	xfs_dir2_data_hdr_t	*hdr;		/* data block header */
	xfs_dir2_data_मुक्त_t	*dfp;		/* bestमुक्त entry */
	पूर्णांक			मुक्तseen;	/* mask of bestमुक्तs seen */
	xfs_dahash_t		hash;		/* hash of current name */
	पूर्णांक			i;		/* leaf index */
	पूर्णांक			lastमुक्त;	/* last entry was unused */
	xfs_dir2_leaf_entry_t	*lep=शून्य;	/* block leaf entries */
	काष्ठा xfs_mount	*mp = bp->b_mount;
	पूर्णांक			stale;		/* count of stale leaves */
	काष्ठा xfs_name		name;
	अचिन्हित पूर्णांक		offset;
	अचिन्हित पूर्णांक		end;
	काष्ठा xfs_da_geometry	*geo = mp->m_dir_geo;

	/*
	 * If this isn't a directory, something is seriously wrong.  Bail out.
	 */
	अगर (dp && !S_ISसूची(VFS_I(dp)->i_mode))
		वापस __this_address;

	hdr = bp->b_addr;
	offset = geo->data_entry_offset;

	चयन (hdr->magic) अणु
	हाल cpu_to_be32(XFS_सूची3_BLOCK_MAGIC):
	हाल cpu_to_be32(XFS_सूची2_BLOCK_MAGIC):
		btp = xfs_dir2_block_tail_p(geo, hdr);
		lep = xfs_dir2_block_leaf_p(btp);

		अगर (be32_to_cpu(btp->count) >=
		    xfs_dir2_data_max_leaf_entries(geo))
			वापस __this_address;
		अवरोध;
	हाल cpu_to_be32(XFS_सूची3_DATA_MAGIC):
	हाल cpu_to_be32(XFS_सूची2_DATA_MAGIC):
		अवरोध;
	शेष:
		वापस __this_address;
	पूर्ण
	end = xfs_dir3_data_end_offset(geo, hdr);
	अगर (!end)
		वापस __this_address;

	/*
	 * Account क्रम zero bestमुक्त entries.
	 */
	bf = xfs_dir2_data_bestमुक्त_p(mp, hdr);
	count = lastमुक्त = मुक्तseen = 0;
	अगर (!bf[0].length) अणु
		अगर (bf[0].offset)
			वापस __this_address;
		मुक्तseen |= 1 << 0;
	पूर्ण
	अगर (!bf[1].length) अणु
		अगर (bf[1].offset)
			वापस __this_address;
		मुक्तseen |= 1 << 1;
	पूर्ण
	अगर (!bf[2].length) अणु
		अगर (bf[2].offset)
			वापस __this_address;
		मुक्तseen |= 1 << 2;
	पूर्ण

	अगर (be16_to_cpu(bf[0].length) < be16_to_cpu(bf[1].length))
		वापस __this_address;
	अगर (be16_to_cpu(bf[1].length) < be16_to_cpu(bf[2].length))
		वापस __this_address;
	/*
	 * Loop over the data/unused entries.
	 */
	जबतक (offset < end) अणु
		काष्ठा xfs_dir2_data_unused	*dup = bp->b_addr + offset;
		काष्ठा xfs_dir2_data_entry	*dep = bp->b_addr + offset;

		/*
		 * If it's unused, look क्रम the space in the bestमुक्त table.
		 * If we find it, account क्रम that, अन्यथा make sure it
		 * करोesn't need to be there.
		 */
		अगर (be16_to_cpu(dup->मुक्तtag) == XFS_सूची2_DATA_FREE_TAG) अणु
			xfs_failaddr_t	fa;

			अगर (lastमुक्त != 0)
				वापस __this_address;
			अगर (offset + be16_to_cpu(dup->length) > end)
				वापस __this_address;
			अगर (be16_to_cpu(*xfs_dir2_data_unused_tag_p(dup)) !=
			    offset)
				वापस __this_address;
			fa = xfs_dir2_data_मुक्तfind_verअगरy(hdr, bf, dup, &dfp);
			अगर (fa)
				वापस fa;
			अगर (dfp) अणु
				i = (पूर्णांक)(dfp - bf);
				अगर ((मुक्तseen & (1 << i)) != 0)
					वापस __this_address;
				मुक्तseen |= 1 << i;
			पूर्ण अन्यथा अणु
				अगर (be16_to_cpu(dup->length) >
				    be16_to_cpu(bf[2].length))
					वापस __this_address;
			पूर्ण
			offset += be16_to_cpu(dup->length);
			lastमुक्त = 1;
			जारी;
		पूर्ण
		/*
		 * It's a real entry.  Validate the fields.
		 * If this is a block directory then make sure it's
		 * in the leaf section of the block.
		 * The linear search is crude but this is DEBUG code.
		 */
		अगर (dep->namelen == 0)
			वापस __this_address;
		अगर (!xfs_verअगरy_dir_ino(mp, be64_to_cpu(dep->inumber)))
			वापस __this_address;
		अगर (offset + xfs_dir2_data_entsize(mp, dep->namelen) > end)
			वापस __this_address;
		अगर (be16_to_cpu(*xfs_dir2_data_entry_tag_p(mp, dep)) != offset)
			वापस __this_address;
		अगर (xfs_dir2_data_get_ftype(mp, dep) >= XFS_सूची3_FT_MAX)
			वापस __this_address;
		count++;
		lastमुक्त = 0;
		अगर (hdr->magic == cpu_to_be32(XFS_सूची2_BLOCK_MAGIC) ||
		    hdr->magic == cpu_to_be32(XFS_सूची3_BLOCK_MAGIC)) अणु
			addr = xfs_dir2_db_off_to_dataptr(geo, geo->datablk,
						(xfs_dir2_data_aoff_t)
						((अक्षर *)dep - (अक्षर *)hdr));
			name.name = dep->name;
			name.len = dep->namelen;
			hash = xfs_dir2_hashname(mp, &name);
			क्रम (i = 0; i < be32_to_cpu(btp->count); i++) अणु
				अगर (be32_to_cpu(lep[i].address) == addr &&
				    be32_to_cpu(lep[i].hashval) == hash)
					अवरोध;
			पूर्ण
			अगर (i >= be32_to_cpu(btp->count))
				वापस __this_address;
		पूर्ण
		offset += xfs_dir2_data_entsize(mp, dep->namelen);
	पूर्ण
	/*
	 * Need to have seen all the entries and all the bestमुक्त slots.
	 */
	अगर (मुक्तseen != 7)
		वापस __this_address;
	अगर (hdr->magic == cpu_to_be32(XFS_सूची2_BLOCK_MAGIC) ||
	    hdr->magic == cpu_to_be32(XFS_सूची3_BLOCK_MAGIC)) अणु
		क्रम (i = stale = 0; i < be32_to_cpu(btp->count); i++) अणु
			अगर (lep[i].address ==
			    cpu_to_be32(XFS_सूची2_शून्य_DATAPTR))
				stale++;
			अगर (i > 0 && be32_to_cpu(lep[i].hashval) <
				     be32_to_cpu(lep[i - 1].hashval))
				वापस __this_address;
		पूर्ण
		अगर (count != be32_to_cpu(btp->count) - be32_to_cpu(btp->stale))
			वापस __this_address;
		अगर (stale != be32_to_cpu(btp->stale))
			वापस __this_address;
	पूर्ण
	वापस शून्य;
पूर्ण

#अगर_घोषित DEBUG
व्योम
xfs_dir3_data_check(
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_buf		*bp)
अणु
	xfs_failaddr_t		fa;

	fa = __xfs_dir3_data_check(dp, bp);
	अगर (!fa)
		वापस;
	xfs_corruption_error(__func__, XFS_ERRLEVEL_LOW, dp->i_mount,
			bp->b_addr, BBTOB(bp->b_length), __खाता__, __LINE__,
			fa);
	ASSERT(0);
पूर्ण
#पूर्ण_अगर

अटल xfs_failaddr_t
xfs_dir3_data_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_dir3_blk_hdr	*hdr3 = bp->b_addr;

	अगर (!xfs_verअगरy_magic(bp, hdr3->magic))
		वापस __this_address;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		अगर (!uuid_equal(&hdr3->uuid, &mp->m_sb.sb_meta_uuid))
			वापस __this_address;
		अगर (be64_to_cpu(hdr3->blkno) != bp->b_bn)
			वापस __this_address;
		अगर (!xfs_log_check_lsn(mp, be64_to_cpu(hdr3->lsn)))
			वापस __this_address;
	पूर्ण
	वापस __xfs_dir3_data_check(शून्य, bp);
पूर्ण

/*
 * Readahead of the first block of the directory when it is खोलोed is completely
 * oblivious to the क्रमmat of the directory. Hence we can either get a block
 * क्रमmat buffer or a data क्रमmat buffer on पढ़ोahead.
 */
अटल व्योम
xfs_dir3_data_पढ़ोa_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_dir2_data_hdr *hdr = bp->b_addr;

	चयन (hdr->magic) अणु
	हाल cpu_to_be32(XFS_सूची2_BLOCK_MAGIC):
	हाल cpu_to_be32(XFS_सूची3_BLOCK_MAGIC):
		bp->b_ops = &xfs_dir3_block_buf_ops;
		bp->b_ops->verअगरy_पढ़ो(bp);
		वापस;
	हाल cpu_to_be32(XFS_सूची2_DATA_MAGIC):
	हाल cpu_to_be32(XFS_सूची3_DATA_MAGIC):
		bp->b_ops = &xfs_dir3_data_buf_ops;
		bp->b_ops->verअगरy_पढ़ो(bp);
		वापस;
	शेष:
		xfs_verअगरier_error(bp, -EFSCORRUPTED, __this_address);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
xfs_dir3_data_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	xfs_failaddr_t		fa;

	अगर (xfs_sb_version_hascrc(&mp->m_sb) &&
	    !xfs_buf_verअगरy_cksum(bp, XFS_सूची3_DATA_CRC_OFF))
		xfs_verअगरier_error(bp, -EFSBADCRC, __this_address);
	अन्यथा अणु
		fa = xfs_dir3_data_verअगरy(bp);
		अगर (fa)
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
	पूर्ण
पूर्ण

अटल व्योम
xfs_dir3_data_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;
	काष्ठा xfs_dir3_blk_hdr	*hdr3 = bp->b_addr;
	xfs_failaddr_t		fa;

	fa = xfs_dir3_data_verअगरy(bp);
	अगर (fa) अणु
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	अगर (bip)
		hdr3->lsn = cpu_to_be64(bip->bli_item.li_lsn);

	xfs_buf_update_cksum(bp, XFS_सूची3_DATA_CRC_OFF);
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_dir3_data_buf_ops = अणु
	.name = "xfs_dir3_data",
	.magic = अणु cpu_to_be32(XFS_सूची2_DATA_MAGIC),
		   cpu_to_be32(XFS_सूची3_DATA_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_dir3_data_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_dir3_data_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_dir3_data_verअगरy,
पूर्ण;

अटल स्थिर काष्ठा xfs_buf_ops xfs_dir3_data_पढ़ोa_buf_ops = अणु
	.name = "xfs_dir3_data_reada",
	.magic = अणु cpu_to_be32(XFS_सूची2_DATA_MAGIC),
		   cpu_to_be32(XFS_सूची3_DATA_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_dir3_data_पढ़ोa_verअगरy,
	.verअगरy_ग_लिखो = xfs_dir3_data_ग_लिखो_verअगरy,
पूर्ण;

अटल xfs_failaddr_t
xfs_dir3_data_header_check(
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = dp->i_mount;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_dir3_data_hdr *hdr3 = bp->b_addr;

		अगर (be64_to_cpu(hdr3->hdr.owner) != dp->i_ino)
			वापस __this_address;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक
xfs_dir3_data_पढ़ो(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		bno,
	अचिन्हित पूर्णांक		flags,
	काष्ठा xfs_buf		**bpp)
अणु
	xfs_failaddr_t		fa;
	पूर्णांक			err;

	err = xfs_da_पढ़ो_buf(tp, dp, bno, flags, bpp, XFS_DATA_FORK,
			&xfs_dir3_data_buf_ops);
	अगर (err || !*bpp)
		वापस err;

	/* Check things that we can't करो in the verअगरier. */
	fa = xfs_dir3_data_header_check(dp, *bpp);
	अगर (fa) अणु
		__xfs_buf_mark_corrupt(*bpp, fa);
		xfs_trans_brअन्यथा(tp, *bpp);
		*bpp = शून्य;
		वापस -EFSCORRUPTED;
	पूर्ण

	xfs_trans_buf_set_type(tp, *bpp, XFS_BLFT_सूची_DATA_BUF);
	वापस err;
पूर्ण

पूर्णांक
xfs_dir3_data_पढ़ोahead(
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		bno,
	अचिन्हित पूर्णांक		flags)
अणु
	वापस xfs_da_पढ़ोa_buf(dp, bno, flags, XFS_DATA_FORK,
				&xfs_dir3_data_पढ़ोa_buf_ops);
पूर्ण

/*
 * Find the bestमुक्त entry that exactly coincides with unused directory space
 * or a verअगरier error because the bestमुक्त data are bad.
 */
अटल xfs_failaddr_t
xfs_dir2_data_मुक्तfind_verअगरy(
	काष्ठा xfs_dir2_data_hdr	*hdr,
	काष्ठा xfs_dir2_data_मुक्त	*bf,
	काष्ठा xfs_dir2_data_unused	*dup,
	काष्ठा xfs_dir2_data_मुक्त	**bf_ent)
अणु
	काष्ठा xfs_dir2_data_मुक्त	*dfp;
	xfs_dir2_data_aoff_t		off;
	bool				matched = false;
	bool				seenzero = false;

	*bf_ent = शून्य;
	off = (xfs_dir2_data_aoff_t)((अक्षर *)dup - (अक्षर *)hdr);

	/*
	 * Validate some consistency in the bestमुक्त table.
	 * Check order, non-overlapping entries, and अगर we find the
	 * one we're looking क्रम it has to be exact.
	 */
	क्रम (dfp = &bf[0]; dfp < &bf[XFS_सूची2_DATA_FD_COUNT]; dfp++) अणु
		अगर (!dfp->offset) अणु
			अगर (dfp->length)
				वापस __this_address;
			seenzero = true;
			जारी;
		पूर्ण
		अगर (seenzero)
			वापस __this_address;
		अगर (be16_to_cpu(dfp->offset) == off) अणु
			matched = true;
			अगर (dfp->length != dup->length)
				वापस __this_address;
		पूर्ण अन्यथा अगर (be16_to_cpu(dfp->offset) > off) अणु
			अगर (off + be16_to_cpu(dup->length) >
					be16_to_cpu(dfp->offset))
				वापस __this_address;
		पूर्ण अन्यथा अणु
			अगर (be16_to_cpu(dfp->offset) +
					be16_to_cpu(dfp->length) > off)
				वापस __this_address;
		पूर्ण
		अगर (!matched &&
		    be16_to_cpu(dfp->length) < be16_to_cpu(dup->length))
			वापस __this_address;
		अगर (dfp > &bf[0] &&
		    be16_to_cpu(dfp[-1].length) < be16_to_cpu(dfp[0].length))
			वापस __this_address;
	पूर्ण

	/* Looks ok so far; now try to match up with a bestमुक्त entry. */
	*bf_ent = xfs_dir2_data_मुक्तfind(hdr, bf, dup);
	वापस शून्य;
पूर्ण

/*
 * Given a data block and an unused entry from that block,
 * वापस the bestमुक्त entry अगर any that corresponds to it.
 */
xfs_dir2_data_मुक्त_t *
xfs_dir2_data_मुक्तfind(
	काष्ठा xfs_dir2_data_hdr *hdr,		/* data block header */
	काष्ठा xfs_dir2_data_मुक्त *bf,		/* bestमुक्त table poपूर्णांकer */
	काष्ठा xfs_dir2_data_unused *dup)	/* unused space */
अणु
	xfs_dir2_data_मुक्त_t	*dfp;		/* bestमुक्त entry */
	xfs_dir2_data_aoff_t	off;		/* offset value needed */

	off = (xfs_dir2_data_aoff_t)((अक्षर *)dup - (अक्षर *)hdr);

	/*
	 * If this is smaller than the smallest bestमुक्त entry,
	 * it can't be there since they're sorted.
	 */
	अगर (be16_to_cpu(dup->length) <
	    be16_to_cpu(bf[XFS_सूची2_DATA_FD_COUNT - 1].length))
		वापस शून्य;
	/*
	 * Look at the three bestमुक्त entries क्रम our guy.
	 */
	क्रम (dfp = &bf[0]; dfp < &bf[XFS_सूची2_DATA_FD_COUNT]; dfp++) अणु
		अगर (!dfp->offset)
			वापस शून्य;
		अगर (be16_to_cpu(dfp->offset) == off)
			वापस dfp;
	पूर्ण
	/*
	 * Didn't find it.  This only happens अगर there are duplicate lengths.
	 */
	वापस शून्य;
पूर्ण

/*
 * Insert an unused-space entry पूर्णांकo the bestमुक्त table.
 */
xfs_dir2_data_मुक्त_t *				/* entry inserted */
xfs_dir2_data_मुक्तinsert(
	काष्ठा xfs_dir2_data_hdr *hdr,		/* data block poपूर्णांकer */
	काष्ठा xfs_dir2_data_मुक्त *dfp,		/* bestमुक्त table poपूर्णांकer */
	काष्ठा xfs_dir2_data_unused *dup,	/* unused space */
	पूर्णांक			*loghead)	/* log the data header (out) */
अणु
	xfs_dir2_data_मुक्त_t	new;		/* new bestमुक्त entry */

	ASSERT(hdr->magic == cpu_to_be32(XFS_सूची2_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची2_BLOCK_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची3_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची3_BLOCK_MAGIC));

	new.length = dup->length;
	new.offset = cpu_to_be16((अक्षर *)dup - (अक्षर *)hdr);

	/*
	 * Insert at position 0, 1, or 2; or not at all.
	 */
	अगर (be16_to_cpu(new.length) > be16_to_cpu(dfp[0].length)) अणु
		dfp[2] = dfp[1];
		dfp[1] = dfp[0];
		dfp[0] = new;
		*loghead = 1;
		वापस &dfp[0];
	पूर्ण
	अगर (be16_to_cpu(new.length) > be16_to_cpu(dfp[1].length)) अणु
		dfp[2] = dfp[1];
		dfp[1] = new;
		*loghead = 1;
		वापस &dfp[1];
	पूर्ण
	अगर (be16_to_cpu(new.length) > be16_to_cpu(dfp[2].length)) अणु
		dfp[2] = new;
		*loghead = 1;
		वापस &dfp[2];
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Remove a bestमुक्त entry from the table.
 */
STATIC व्योम
xfs_dir2_data_मुक्तहटाओ(
	काष्ठा xfs_dir2_data_hdr *hdr,		/* data block header */
	काष्ठा xfs_dir2_data_मुक्त *bf,		/* bestमुक्त table poपूर्णांकer */
	काष्ठा xfs_dir2_data_मुक्त *dfp,		/* bestमुक्त entry poपूर्णांकer */
	पूर्णांक			*loghead)	/* out: log data header */
अणु

	ASSERT(hdr->magic == cpu_to_be32(XFS_सूची2_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची2_BLOCK_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची3_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची3_BLOCK_MAGIC));

	/*
	 * It's the first entry, slide the next 2 up.
	 */
	अगर (dfp == &bf[0]) अणु
		bf[0] = bf[1];
		bf[1] = bf[2];
	पूर्ण
	/*
	 * It's the second entry, slide the 3rd entry up.
	 */
	अन्यथा अगर (dfp == &bf[1])
		bf[1] = bf[2];
	/*
	 * Must be the last entry.
	 */
	अन्यथा
		ASSERT(dfp == &bf[2]);
	/*
	 * Clear the 3rd entry, must be zero now.
	 */
	bf[2].length = 0;
	bf[2].offset = 0;
	*loghead = 1;
पूर्ण

/*
 * Given a data block, reस्थिरruct its bestमुक्त map.
 */
व्योम
xfs_dir2_data_मुक्तscan(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_dir2_data_hdr	*hdr,
	पूर्णांक				*loghead)
अणु
	काष्ठा xfs_da_geometry		*geo = mp->m_dir_geo;
	काष्ठा xfs_dir2_data_मुक्त	*bf = xfs_dir2_data_bestमुक्त_p(mp, hdr);
	व्योम				*addr = hdr;
	अचिन्हित पूर्णांक			offset = geo->data_entry_offset;
	अचिन्हित पूर्णांक			end;

	ASSERT(hdr->magic == cpu_to_be32(XFS_सूची2_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची3_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची2_BLOCK_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची3_BLOCK_MAGIC));

	/*
	 * Start by clearing the table.
	 */
	स_रखो(bf, 0, माप(*bf) * XFS_सूची2_DATA_FD_COUNT);
	*loghead = 1;

	end = xfs_dir3_data_end_offset(geo, addr);
	जबतक (offset < end) अणु
		काष्ठा xfs_dir2_data_unused	*dup = addr + offset;
		काष्ठा xfs_dir2_data_entry	*dep = addr + offset;

		/*
		 * If it's a मुक्त entry, insert it.
		 */
		अगर (be16_to_cpu(dup->मुक्तtag) == XFS_सूची2_DATA_FREE_TAG) अणु
			ASSERT(offset ==
			       be16_to_cpu(*xfs_dir2_data_unused_tag_p(dup)));
			xfs_dir2_data_मुक्तinsert(hdr, bf, dup, loghead);
			offset += be16_to_cpu(dup->length);
			जारी;
		पूर्ण

		/*
		 * For active entries, check their tags and skip them.
		 */
		ASSERT(offset ==
		       be16_to_cpu(*xfs_dir2_data_entry_tag_p(mp, dep)));
		offset += xfs_dir2_data_entsize(mp, dep->namelen);
	पूर्ण
पूर्ण

/*
 * Initialize a data block at the given block number in the directory.
 * Give back the buffer क्रम the created block.
 */
पूर्णांक						/* error */
xfs_dir3_data_init(
	काष्ठा xfs_da_args		*args,	/* directory operation args */
	xfs_dir2_db_t			blkno,	/* logical dir block number */
	काष्ठा xfs_buf			**bpp)	/* output block buffer */
अणु
	काष्ठा xfs_trans		*tp = args->trans;
	काष्ठा xfs_inode		*dp = args->dp;
	काष्ठा xfs_mount		*mp = dp->i_mount;
	काष्ठा xfs_da_geometry		*geo = args->geo;
	काष्ठा xfs_buf			*bp;
	काष्ठा xfs_dir2_data_hdr	*hdr;
	काष्ठा xfs_dir2_data_unused	*dup;
	काष्ठा xfs_dir2_data_मुक्त 	*bf;
	पूर्णांक				error;
	पूर्णांक				i;

	/*
	 * Get the buffer set up क्रम the block.
	 */
	error = xfs_da_get_buf(tp, dp, xfs_dir2_db_to_da(args->geo, blkno),
			       &bp, XFS_DATA_FORK);
	अगर (error)
		वापस error;
	bp->b_ops = &xfs_dir3_data_buf_ops;
	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_सूची_DATA_BUF);

	/*
	 * Initialize the header.
	 */
	hdr = bp->b_addr;
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_dir3_blk_hdr *hdr3 = bp->b_addr;

		स_रखो(hdr3, 0, माप(*hdr3));
		hdr3->magic = cpu_to_be32(XFS_सूची3_DATA_MAGIC);
		hdr3->blkno = cpu_to_be64(bp->b_bn);
		hdr3->owner = cpu_to_be64(dp->i_ino);
		uuid_copy(&hdr3->uuid, &mp->m_sb.sb_meta_uuid);

	पूर्ण अन्यथा
		hdr->magic = cpu_to_be32(XFS_सूची2_DATA_MAGIC);

	bf = xfs_dir2_data_bestमुक्त_p(mp, hdr);
	bf[0].offset = cpu_to_be16(geo->data_entry_offset);
	bf[0].length = cpu_to_be16(geo->blksize - geo->data_entry_offset);
	क्रम (i = 1; i < XFS_सूची2_DATA_FD_COUNT; i++) अणु
		bf[i].length = 0;
		bf[i].offset = 0;
	पूर्ण

	/*
	 * Set up an unused entry क्रम the block's body.
	 */
	dup = bp->b_addr + geo->data_entry_offset;
	dup->मुक्तtag = cpu_to_be16(XFS_सूची2_DATA_FREE_TAG);
	dup->length = bf[0].length;
	*xfs_dir2_data_unused_tag_p(dup) = cpu_to_be16((अक्षर *)dup - (अक्षर *)hdr);

	/*
	 * Log it and वापस it.
	 */
	xfs_dir2_data_log_header(args, bp);
	xfs_dir2_data_log_unused(args, bp, dup);
	*bpp = bp;
	वापस 0;
पूर्ण

/*
 * Log an active data entry from the block.
 */
व्योम
xfs_dir2_data_log_entry(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_buf		*bp,
	xfs_dir2_data_entry_t	*dep)		/* data entry poपूर्णांकer */
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_dir2_data_hdr *hdr = bp->b_addr;

	ASSERT(hdr->magic == cpu_to_be32(XFS_सूची2_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची3_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची2_BLOCK_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची3_BLOCK_MAGIC));

	xfs_trans_log_buf(args->trans, bp, (uपूर्णांक)((अक्षर *)dep - (अक्षर *)hdr),
		(uपूर्णांक)((अक्षर *)(xfs_dir2_data_entry_tag_p(mp, dep) + 1) -
		       (अक्षर *)hdr - 1));
पूर्ण

/*
 * Log a data block header.
 */
व्योम
xfs_dir2_data_log_header(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_buf		*bp)
अणु
#अगर_घोषित DEBUG
	काष्ठा xfs_dir2_data_hdr *hdr = bp->b_addr;

	ASSERT(hdr->magic == cpu_to_be32(XFS_सूची2_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची3_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची2_BLOCK_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची3_BLOCK_MAGIC));
#पूर्ण_अगर

	xfs_trans_log_buf(args->trans, bp, 0, args->geo->data_entry_offset - 1);
पूर्ण

/*
 * Log a data unused entry.
 */
व्योम
xfs_dir2_data_log_unused(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_buf		*bp,
	xfs_dir2_data_unused_t	*dup)		/* data unused poपूर्णांकer */
अणु
	xfs_dir2_data_hdr_t	*hdr = bp->b_addr;

	ASSERT(hdr->magic == cpu_to_be32(XFS_सूची2_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची3_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची2_BLOCK_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची3_BLOCK_MAGIC));

	/*
	 * Log the first part of the unused entry.
	 */
	xfs_trans_log_buf(args->trans, bp, (uपूर्णांक)((अक्षर *)dup - (अक्षर *)hdr),
		(uपूर्णांक)((अक्षर *)&dup->length + माप(dup->length) -
		       1 - (अक्षर *)hdr));
	/*
	 * Log the end (tag) of the unused entry.
	 */
	xfs_trans_log_buf(args->trans, bp,
		(uपूर्णांक)((अक्षर *)xfs_dir2_data_unused_tag_p(dup) - (अक्षर *)hdr),
		(uपूर्णांक)((अक्षर *)xfs_dir2_data_unused_tag_p(dup) - (अक्षर *)hdr +
		       माप(xfs_dir2_data_off_t) - 1));
पूर्ण

/*
 * Make a byte range in the data block unused.
 * Its current contents are unimportant.
 */
व्योम
xfs_dir2_data_make_मुक्त(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_buf		*bp,
	xfs_dir2_data_aoff_t	offset,		/* starting byte offset */
	xfs_dir2_data_aoff_t	len,		/* length in bytes */
	पूर्णांक			*needlogp,	/* out: log header */
	पूर्णांक			*needscanp)	/* out: regen bestमुक्त */
अणु
	xfs_dir2_data_hdr_t	*hdr;		/* data block poपूर्णांकer */
	xfs_dir2_data_मुक्त_t	*dfp;		/* bestमुक्त poपूर्णांकer */
	पूर्णांक			needscan;	/* need to regen bestमुक्त */
	xfs_dir2_data_unused_t	*newdup;	/* new unused entry */
	xfs_dir2_data_unused_t	*postdup;	/* unused entry after us */
	xfs_dir2_data_unused_t	*prevdup;	/* unused entry beक्रमe us */
	अचिन्हित पूर्णांक		end;
	काष्ठा xfs_dir2_data_मुक्त *bf;

	hdr = bp->b_addr;

	/*
	 * Figure out where the end of the data area is.
	 */
	end = xfs_dir3_data_end_offset(args->geo, hdr);
	ASSERT(end != 0);

	/*
	 * If this isn't the start of the block, then back up to
	 * the previous entry and see अगर it's मुक्त.
	 */
	अगर (offset > args->geo->data_entry_offset) अणु
		__be16			*tagp;	/* tag just beक्रमe us */

		tagp = (__be16 *)((अक्षर *)hdr + offset) - 1;
		prevdup = (xfs_dir2_data_unused_t *)((अक्षर *)hdr + be16_to_cpu(*tagp));
		अगर (be16_to_cpu(prevdup->मुक्तtag) != XFS_सूची2_DATA_FREE_TAG)
			prevdup = शून्य;
	पूर्ण अन्यथा
		prevdup = शून्य;
	/*
	 * If this isn't the end of the block, see अगर the entry after
	 * us is मुक्त.
	 */
	अगर (offset + len < end) अणु
		postdup =
			(xfs_dir2_data_unused_t *)((अक्षर *)hdr + offset + len);
		अगर (be16_to_cpu(postdup->मुक्तtag) != XFS_सूची2_DATA_FREE_TAG)
			postdup = शून्य;
	पूर्ण अन्यथा
		postdup = शून्य;
	ASSERT(*needscanp == 0);
	needscan = 0;
	/*
	 * Previous and following entries are both मुक्त,
	 * merge everything पूर्णांकo a single मुक्त entry.
	 */
	bf = xfs_dir2_data_bestमुक्त_p(args->dp->i_mount, hdr);
	अगर (prevdup && postdup) अणु
		xfs_dir2_data_मुक्त_t	*dfp2;	/* another bestमुक्त poपूर्णांकer */

		/*
		 * See अगर prevdup and/or postdup are in bestमुक्त table.
		 */
		dfp = xfs_dir2_data_मुक्तfind(hdr, bf, prevdup);
		dfp2 = xfs_dir2_data_मुक्तfind(hdr, bf, postdup);
		/*
		 * We need a rescan unless there are exactly 2 मुक्त entries
		 * namely our two.  Then we know what's happening, otherwise
		 * since the third bestमुक्त is there, there might be more
		 * entries.
		 */
		needscan = (bf[2].length != 0);
		/*
		 * Fix up the new big मुक्तspace.
		 */
		be16_add_cpu(&prevdup->length, len + be16_to_cpu(postdup->length));
		*xfs_dir2_data_unused_tag_p(prevdup) =
			cpu_to_be16((अक्षर *)prevdup - (अक्षर *)hdr);
		xfs_dir2_data_log_unused(args, bp, prevdup);
		अगर (!needscan) अणु
			/*
			 * Has to be the हाल that entries 0 and 1 are
			 * dfp and dfp2 (करोn't know which is which), and
			 * entry 2 is empty.
			 * Remove entry 1 first then entry 0.
			 */
			ASSERT(dfp && dfp2);
			अगर (dfp == &bf[1]) अणु
				dfp = &bf[0];
				ASSERT(dfp2 == dfp);
				dfp2 = &bf[1];
			पूर्ण
			xfs_dir2_data_मुक्तहटाओ(hdr, bf, dfp2, needlogp);
			xfs_dir2_data_मुक्तहटाओ(hdr, bf, dfp, needlogp);
			/*
			 * Now insert the new entry.
			 */
			dfp = xfs_dir2_data_मुक्तinsert(hdr, bf, prevdup,
						       needlogp);
			ASSERT(dfp == &bf[0]);
			ASSERT(dfp->length == prevdup->length);
			ASSERT(!dfp[1].length);
			ASSERT(!dfp[2].length);
		पूर्ण
	पूर्ण
	/*
	 * The entry beक्रमe us is मुक्त, merge with it.
	 */
	अन्यथा अगर (prevdup) अणु
		dfp = xfs_dir2_data_मुक्तfind(hdr, bf, prevdup);
		be16_add_cpu(&prevdup->length, len);
		*xfs_dir2_data_unused_tag_p(prevdup) =
			cpu_to_be16((अक्षर *)prevdup - (अक्षर *)hdr);
		xfs_dir2_data_log_unused(args, bp, prevdup);
		/*
		 * If the previous entry was in the table, the new entry
		 * is दीर्घer, so it will be in the table too.  Remove
		 * the old one and add the new one.
		 */
		अगर (dfp) अणु
			xfs_dir2_data_मुक्तहटाओ(hdr, bf, dfp, needlogp);
			xfs_dir2_data_मुक्तinsert(hdr, bf, prevdup, needlogp);
		पूर्ण
		/*
		 * Otherwise we need a scan अगर the new entry is big enough.
		 */
		अन्यथा अणु
			needscan = be16_to_cpu(prevdup->length) >
				   be16_to_cpu(bf[2].length);
		पूर्ण
	पूर्ण
	/*
	 * The following entry is मुक्त, merge with it.
	 */
	अन्यथा अगर (postdup) अणु
		dfp = xfs_dir2_data_मुक्तfind(hdr, bf, postdup);
		newdup = (xfs_dir2_data_unused_t *)((अक्षर *)hdr + offset);
		newdup->मुक्तtag = cpu_to_be16(XFS_सूची2_DATA_FREE_TAG);
		newdup->length = cpu_to_be16(len + be16_to_cpu(postdup->length));
		*xfs_dir2_data_unused_tag_p(newdup) =
			cpu_to_be16((अक्षर *)newdup - (अक्षर *)hdr);
		xfs_dir2_data_log_unused(args, bp, newdup);
		/*
		 * If the following entry was in the table, the new entry
		 * is दीर्घer, so it will be in the table too.  Remove
		 * the old one and add the new one.
		 */
		अगर (dfp) अणु
			xfs_dir2_data_मुक्तहटाओ(hdr, bf, dfp, needlogp);
			xfs_dir2_data_मुक्तinsert(hdr, bf, newdup, needlogp);
		पूर्ण
		/*
		 * Otherwise we need a scan अगर the new entry is big enough.
		 */
		अन्यथा अणु
			needscan = be16_to_cpu(newdup->length) >
				   be16_to_cpu(bf[2].length);
		पूर्ण
	पूर्ण
	/*
	 * Neither neighbor is मुक्त.  Make a new entry.
	 */
	अन्यथा अणु
		newdup = (xfs_dir2_data_unused_t *)((अक्षर *)hdr + offset);
		newdup->मुक्तtag = cpu_to_be16(XFS_सूची2_DATA_FREE_TAG);
		newdup->length = cpu_to_be16(len);
		*xfs_dir2_data_unused_tag_p(newdup) =
			cpu_to_be16((अक्षर *)newdup - (अक्षर *)hdr);
		xfs_dir2_data_log_unused(args, bp, newdup);
		xfs_dir2_data_मुक्तinsert(hdr, bf, newdup, needlogp);
	पूर्ण
	*needscanp = needscan;
पूर्ण

/* Check our मुक्त data क्रम obvious signs of corruption. */
अटल अंतरभूत xfs_failaddr_t
xfs_dir2_data_check_मुक्त(
	काष्ठा xfs_dir2_data_hdr	*hdr,
	काष्ठा xfs_dir2_data_unused	*dup,
	xfs_dir2_data_aoff_t		offset,
	xfs_dir2_data_aoff_t		len)
अणु
	अगर (hdr->magic != cpu_to_be32(XFS_सूची2_DATA_MAGIC) &&
	    hdr->magic != cpu_to_be32(XFS_सूची3_DATA_MAGIC) &&
	    hdr->magic != cpu_to_be32(XFS_सूची2_BLOCK_MAGIC) &&
	    hdr->magic != cpu_to_be32(XFS_सूची3_BLOCK_MAGIC))
		वापस __this_address;
	अगर (be16_to_cpu(dup->मुक्तtag) != XFS_सूची2_DATA_FREE_TAG)
		वापस __this_address;
	अगर (offset < (अक्षर *)dup - (अक्षर *)hdr)
		वापस __this_address;
	अगर (offset + len > (अक्षर *)dup + be16_to_cpu(dup->length) - (अक्षर *)hdr)
		वापस __this_address;
	अगर ((अक्षर *)dup - (अक्षर *)hdr !=
			be16_to_cpu(*xfs_dir2_data_unused_tag_p(dup)))
		वापस __this_address;
	वापस शून्य;
पूर्ण

/* Sanity-check a new bestमुक्त entry. */
अटल अंतरभूत xfs_failaddr_t
xfs_dir2_data_check_new_मुक्त(
	काष्ठा xfs_dir2_data_hdr	*hdr,
	काष्ठा xfs_dir2_data_मुक्त	*dfp,
	काष्ठा xfs_dir2_data_unused	*newdup)
अणु
	अगर (dfp == शून्य)
		वापस __this_address;
	अगर (dfp->length != newdup->length)
		वापस __this_address;
	अगर (be16_to_cpu(dfp->offset) != (अक्षर *)newdup - (अक्षर *)hdr)
		वापस __this_address;
	वापस शून्य;
पूर्ण

/*
 * Take a byte range out of an existing unused space and make it un-मुक्त.
 */
पूर्णांक
xfs_dir2_data_use_मुक्त(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_buf		*bp,
	xfs_dir2_data_unused_t	*dup,		/* unused entry */
	xfs_dir2_data_aoff_t	offset,		/* starting offset to use */
	xfs_dir2_data_aoff_t	len,		/* length to use */
	पूर्णांक			*needlogp,	/* out: need to log header */
	पूर्णांक			*needscanp)	/* out: need regen bestमुक्त */
अणु
	xfs_dir2_data_hdr_t	*hdr;		/* data block header */
	xfs_dir2_data_मुक्त_t	*dfp;		/* bestमुक्त poपूर्णांकer */
	xfs_dir2_data_unused_t	*newdup;	/* new unused entry */
	xfs_dir2_data_unused_t	*newdup2;	/* another new unused entry */
	काष्ठा xfs_dir2_data_मुक्त *bf;
	xfs_failaddr_t		fa;
	पूर्णांक			matchback;	/* matches end of मुक्तspace */
	पूर्णांक			matchfront;	/* matches start of मुक्तspace */
	पूर्णांक			needscan;	/* need to regen bestमुक्त */
	पूर्णांक			oldlen;		/* old unused entry's length */

	hdr = bp->b_addr;
	fa = xfs_dir2_data_check_मुक्त(hdr, dup, offset, len);
	अगर (fa)
		जाओ corrupt;
	/*
	 * Look up the entry in the bestमुक्त table.
	 */
	oldlen = be16_to_cpu(dup->length);
	bf = xfs_dir2_data_bestमुक्त_p(args->dp->i_mount, hdr);
	dfp = xfs_dir2_data_मुक्तfind(hdr, bf, dup);
	ASSERT(dfp || oldlen <= be16_to_cpu(bf[2].length));
	/*
	 * Check क्रम alignment with front and back of the entry.
	 */
	matchfront = (अक्षर *)dup - (अक्षर *)hdr == offset;
	matchback = (अक्षर *)dup + oldlen - (अक्षर *)hdr == offset + len;
	ASSERT(*needscanp == 0);
	needscan = 0;
	/*
	 * If we matched it exactly we just need to get rid of it from
	 * the bestमुक्त table.
	 */
	अगर (matchfront && matchback) अणु
		अगर (dfp) अणु
			needscan = (bf[2].offset != 0);
			अगर (!needscan)
				xfs_dir2_data_मुक्तहटाओ(hdr, bf, dfp,
							 needlogp);
		पूर्ण
	पूर्ण
	/*
	 * We match the first part of the entry.
	 * Make a new entry with the reमुख्यing मुक्तspace.
	 */
	अन्यथा अगर (matchfront) अणु
		newdup = (xfs_dir2_data_unused_t *)((अक्षर *)hdr + offset + len);
		newdup->मुक्तtag = cpu_to_be16(XFS_सूची2_DATA_FREE_TAG);
		newdup->length = cpu_to_be16(oldlen - len);
		*xfs_dir2_data_unused_tag_p(newdup) =
			cpu_to_be16((अक्षर *)newdup - (अक्षर *)hdr);
		xfs_dir2_data_log_unused(args, bp, newdup);
		/*
		 * If it was in the table, हटाओ it and add the new one.
		 */
		अगर (dfp) अणु
			xfs_dir2_data_मुक्तहटाओ(hdr, bf, dfp, needlogp);
			dfp = xfs_dir2_data_मुक्तinsert(hdr, bf, newdup,
						       needlogp);
			fa = xfs_dir2_data_check_new_मुक्त(hdr, dfp, newdup);
			अगर (fa)
				जाओ corrupt;
			/*
			 * If we got inserted at the last slot,
			 * that means we करोn't know अगर there was a better
			 * choice क्रम the last slot, or not.  Rescan.
			 */
			needscan = dfp == &bf[2];
		पूर्ण
	पूर्ण
	/*
	 * We match the last part of the entry.
	 * Trim the allocated space off the tail of the entry.
	 */
	अन्यथा अगर (matchback) अणु
		newdup = dup;
		newdup->length = cpu_to_be16(((अक्षर *)hdr + offset) - (अक्षर *)newdup);
		*xfs_dir2_data_unused_tag_p(newdup) =
			cpu_to_be16((अक्षर *)newdup - (अक्षर *)hdr);
		xfs_dir2_data_log_unused(args, bp, newdup);
		/*
		 * If it was in the table, हटाओ it and add the new one.
		 */
		अगर (dfp) अणु
			xfs_dir2_data_मुक्तहटाओ(hdr, bf, dfp, needlogp);
			dfp = xfs_dir2_data_मुक्तinsert(hdr, bf, newdup,
						       needlogp);
			fa = xfs_dir2_data_check_new_मुक्त(hdr, dfp, newdup);
			अगर (fa)
				जाओ corrupt;
			/*
			 * If we got inserted at the last slot,
			 * that means we करोn't know अगर there was a better
			 * choice क्रम the last slot, or not.  Rescan.
			 */
			needscan = dfp == &bf[2];
		पूर्ण
	पूर्ण
	/*
	 * Poking out the middle of an entry.
	 * Make two new entries.
	 */
	अन्यथा अणु
		newdup = dup;
		newdup->length = cpu_to_be16(((अक्षर *)hdr + offset) - (अक्षर *)newdup);
		*xfs_dir2_data_unused_tag_p(newdup) =
			cpu_to_be16((अक्षर *)newdup - (अक्षर *)hdr);
		xfs_dir2_data_log_unused(args, bp, newdup);
		newdup2 = (xfs_dir2_data_unused_t *)((अक्षर *)hdr + offset + len);
		newdup2->मुक्तtag = cpu_to_be16(XFS_सूची2_DATA_FREE_TAG);
		newdup2->length = cpu_to_be16(oldlen - len - be16_to_cpu(newdup->length));
		*xfs_dir2_data_unused_tag_p(newdup2) =
			cpu_to_be16((अक्षर *)newdup2 - (अक्षर *)hdr);
		xfs_dir2_data_log_unused(args, bp, newdup2);
		/*
		 * If the old entry was in the table, we need to scan
		 * अगर the 3rd entry was valid, since these entries
		 * are smaller than the old one.
		 * If we करोn't need to scan that means there were 1 or 2
		 * entries in the table, and removing the old and adding
		 * the 2 new will work.
		 */
		अगर (dfp) अणु
			needscan = (bf[2].length != 0);
			अगर (!needscan) अणु
				xfs_dir2_data_मुक्तहटाओ(hdr, bf, dfp,
							 needlogp);
				xfs_dir2_data_मुक्तinsert(hdr, bf, newdup,
							 needlogp);
				xfs_dir2_data_मुक्तinsert(hdr, bf, newdup2,
							 needlogp);
			पूर्ण
		पूर्ण
	पूर्ण
	*needscanp = needscan;
	वापस 0;
corrupt:
	xfs_corruption_error(__func__, XFS_ERRLEVEL_LOW, args->dp->i_mount,
			hdr, माप(*hdr), __खाता__, __LINE__, fa);
	वापस -EFSCORRUPTED;
पूर्ण

/* Find the end of the entry data in a data/block क्रमmat dir block. */
अचिन्हित पूर्णांक
xfs_dir3_data_end_offset(
	काष्ठा xfs_da_geometry		*geo,
	काष्ठा xfs_dir2_data_hdr	*hdr)
अणु
	व्योम				*p;

	चयन (hdr->magic) अणु
	हाल cpu_to_be32(XFS_सूची3_BLOCK_MAGIC):
	हाल cpu_to_be32(XFS_सूची2_BLOCK_MAGIC):
		p = xfs_dir2_block_leaf_p(xfs_dir2_block_tail_p(geo, hdr));
		वापस p - (व्योम *)hdr;
	हाल cpu_to_be32(XFS_सूची3_DATA_MAGIC):
	हाल cpu_to_be32(XFS_सूची2_DATA_MAGIC):
		वापस geo->blksize;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
