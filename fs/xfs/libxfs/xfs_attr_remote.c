<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * Copyright (c) 2013 Red Hat, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_defer.h"
#समावेश "xfs_da_format.h"
#समावेश "xfs_da_btree.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_attr.h"
#समावेश "xfs_attr_remote.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_error.h"

#घोषणा ATTR_RMTVALUE_MAPSIZE	1	/* # of map entries at once */

/*
 * Remote Attribute Values
 * =======================
 *
 * Remote extended attribute values are conceptually simple -- they're written
 * to data blocks mapped by an inode's attribute विभाजन, and they have an upper
 * size limit of 64k.  Setting a value करोes not involve the XFS log.
 *
 * However, on a v5 fileप्रणाली, maximally sized remote attr values require one
 * block more than 64k worth of space to hold both the remote attribute value
 * header (64 bytes).  On a 4k block fileप्रणाली this results in a 68k buffer;
 * on a 64k block fileप्रणाली, this would be a 128k buffer.  Note that the log
 * क्रमmat can only handle a dirty buffer of XFS_MAX_BLOCKSIZE length (64k).
 * Thereक्रमe, we /must/ ensure that remote attribute value buffers never touch
 * the logging प्रणाली and thereक्रमe never have a log item.
 */

/*
 * Each contiguous block has a header, so it is not just a simple attribute
 * length to FSB conversion.
 */
पूर्णांक
xfs_attr3_rmt_blocks(
	काष्ठा xfs_mount *mp,
	पूर्णांक		attrlen)
अणु
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		पूर्णांक buflen = XFS_ATTR3_RMT_BUF_SPACE(mp, mp->m_sb.sb_blocksize);
		वापस (attrlen + buflen - 1) / buflen;
	पूर्ण
	वापस XFS_B_TO_FSB(mp, attrlen);
पूर्ण

/*
 * Checking of the remote attribute header is split पूर्णांकo two parts. The verअगरier
 * करोes CRC, location and bounds checking, the unpacking function checks the
 * attribute parameters and owner.
 */
अटल xfs_failaddr_t
xfs_attr3_rmt_hdr_ok(
	व्योम			*ptr,
	xfs_ino_t		ino,
	uपूर्णांक32_t		offset,
	uपूर्णांक32_t		size,
	xfs_daddr_t		bno)
अणु
	काष्ठा xfs_attr3_rmt_hdr *rmt = ptr;

	अगर (bno != be64_to_cpu(rmt->rm_blkno))
		वापस __this_address;
	अगर (offset != be32_to_cpu(rmt->rm_offset))
		वापस __this_address;
	अगर (size != be32_to_cpu(rmt->rm_bytes))
		वापस __this_address;
	अगर (ino != be64_to_cpu(rmt->rm_owner))
		वापस __this_address;

	/* ok */
	वापस शून्य;
पूर्ण

अटल xfs_failaddr_t
xfs_attr3_rmt_verअगरy(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	व्योम			*ptr,
	पूर्णांक			fsbsize,
	xfs_daddr_t		bno)
अणु
	काष्ठा xfs_attr3_rmt_hdr *rmt = ptr;

	अगर (!xfs_verअगरy_magic(bp, rmt->rm_magic))
		वापस __this_address;
	अगर (!uuid_equal(&rmt->rm_uuid, &mp->m_sb.sb_meta_uuid))
		वापस __this_address;
	अगर (be64_to_cpu(rmt->rm_blkno) != bno)
		वापस __this_address;
	अगर (be32_to_cpu(rmt->rm_bytes) > fsbsize - माप(*rmt))
		वापस __this_address;
	अगर (be32_to_cpu(rmt->rm_offset) +
				be32_to_cpu(rmt->rm_bytes) > XFS_XATTR_SIZE_MAX)
		वापस __this_address;
	अगर (rmt->rm_owner == 0)
		वापस __this_address;

	वापस शून्य;
पूर्ण

अटल पूर्णांक
__xfs_attr3_rmt_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp,
	bool		check_crc,
	xfs_failaddr_t	*failaddr)
अणु
	काष्ठा xfs_mount *mp = bp->b_mount;
	अक्षर		*ptr;
	पूर्णांक		len;
	xfs_daddr_t	bno;
	पूर्णांक		blksize = mp->m_attr_geo->blksize;

	/* no verअगरication of non-crc buffers */
	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस 0;

	ptr = bp->b_addr;
	bno = bp->b_bn;
	len = BBTOB(bp->b_length);
	ASSERT(len >= blksize);

	जबतक (len > 0) अणु
		अगर (check_crc &&
		    !xfs_verअगरy_cksum(ptr, blksize, XFS_ATTR3_RMT_CRC_OFF)) अणु
			*failaddr = __this_address;
			वापस -EFSBADCRC;
		पूर्ण
		*failaddr = xfs_attr3_rmt_verअगरy(mp, bp, ptr, blksize, bno);
		अगर (*failaddr)
			वापस -EFSCORRUPTED;
		len -= blksize;
		ptr += blksize;
		bno += BTOBB(blksize);
	पूर्ण

	अगर (len != 0) अणु
		*failaddr = __this_address;
		वापस -EFSCORRUPTED;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
xfs_attr3_rmt_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_failaddr_t	fa;
	पूर्णांक		error;

	error = __xfs_attr3_rmt_पढ़ो_verअगरy(bp, true, &fa);
	अगर (error)
		xfs_verअगरier_error(bp, error, fa);
पूर्ण

अटल xfs_failaddr_t
xfs_attr3_rmt_verअगरy_काष्ठा(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_failaddr_t	fa;
	पूर्णांक		error;

	error = __xfs_attr3_rmt_पढ़ो_verअगरy(bp, false, &fa);
	वापस error ? fa : शून्य;
पूर्ण

अटल व्योम
xfs_attr3_rmt_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount *mp = bp->b_mount;
	xfs_failaddr_t	fa;
	पूर्णांक		blksize = mp->m_attr_geo->blksize;
	अक्षर		*ptr;
	पूर्णांक		len;
	xfs_daddr_t	bno;

	/* no verअगरication of non-crc buffers */
	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	ptr = bp->b_addr;
	bno = bp->b_bn;
	len = BBTOB(bp->b_length);
	ASSERT(len >= blksize);

	जबतक (len > 0) अणु
		काष्ठा xfs_attr3_rmt_hdr *rmt = (काष्ठा xfs_attr3_rmt_hdr *)ptr;

		fa = xfs_attr3_rmt_verअगरy(mp, bp, ptr, blksize, bno);
		अगर (fa) अणु
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
			वापस;
		पूर्ण

		/*
		 * Ensure we aren't writing bogus LSNs to disk. See
		 * xfs_attr3_rmt_hdr_set() क्रम the explanation.
		 */
		अगर (rmt->rm_lsn != cpu_to_be64(शून्यCOMMITLSN)) अणु
			xfs_verअगरier_error(bp, -EFSCORRUPTED, __this_address);
			वापस;
		पूर्ण
		xfs_update_cksum(ptr, blksize, XFS_ATTR3_RMT_CRC_OFF);

		len -= blksize;
		ptr += blksize;
		bno += BTOBB(blksize);
	पूर्ण

	अगर (len != 0)
		xfs_verअगरier_error(bp, -EFSCORRUPTED, __this_address);
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_attr3_rmt_buf_ops = अणु
	.name = "xfs_attr3_rmt",
	.magic = अणु 0, cpu_to_be32(XFS_ATTR3_RMT_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_attr3_rmt_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_attr3_rmt_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_attr3_rmt_verअगरy_काष्ठा,
पूर्ण;

STATIC पूर्णांक
xfs_attr3_rmt_hdr_set(
	काष्ठा xfs_mount	*mp,
	व्योम			*ptr,
	xfs_ino_t		ino,
	uपूर्णांक32_t		offset,
	uपूर्णांक32_t		size,
	xfs_daddr_t		bno)
अणु
	काष्ठा xfs_attr3_rmt_hdr *rmt = ptr;

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस 0;

	rmt->rm_magic = cpu_to_be32(XFS_ATTR3_RMT_MAGIC);
	rmt->rm_offset = cpu_to_be32(offset);
	rmt->rm_bytes = cpu_to_be32(size);
	uuid_copy(&rmt->rm_uuid, &mp->m_sb.sb_meta_uuid);
	rmt->rm_owner = cpu_to_be64(ino);
	rmt->rm_blkno = cpu_to_be64(bno);

	/*
	 * Remote attribute blocks are written synchronously, so we करोn't
	 * have an LSN that we can stamp in them that makes any sense to log
	 * recovery. To ensure that log recovery handles overग_लिखोs of these
	 * blocks sanely (i.e. once they've been मुक्तd and पुनः_स्मृतिated as some
	 * other type of metadata) we need to ensure that the LSN has a value
	 * that tells log recovery to ignore the LSN and overग_लिखो the buffer
	 * with whatever is in it's log. To करो this, we use the magic
	 * शून्यCOMMITLSN to indicate that the LSN is invalid.
	 */
	rmt->rm_lsn = cpu_to_be64(शून्यCOMMITLSN);

	वापस माप(काष्ठा xfs_attr3_rmt_hdr);
पूर्ण

/*
 * Helper functions to copy attribute data in and out of the one disk extents
 */
STATIC पूर्णांक
xfs_attr_rmtval_copyout(
	काष्ठा xfs_mount *mp,
	काष्ठा xfs_buf	*bp,
	xfs_ino_t	ino,
	पूर्णांक		*offset,
	पूर्णांक		*valuelen,
	uपूर्णांक8_t		**dst)
अणु
	अक्षर		*src = bp->b_addr;
	xfs_daddr_t	bno = bp->b_bn;
	पूर्णांक		len = BBTOB(bp->b_length);
	पूर्णांक		blksize = mp->m_attr_geo->blksize;

	ASSERT(len >= blksize);

	जबतक (len > 0 && *valuelen > 0) अणु
		पूर्णांक hdr_size = 0;
		पूर्णांक byte_cnt = XFS_ATTR3_RMT_BUF_SPACE(mp, blksize);

		byte_cnt = min(*valuelen, byte_cnt);

		अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
			अगर (xfs_attr3_rmt_hdr_ok(src, ino, *offset,
						  byte_cnt, bno)) अणु
				xfs_alert(mp,
"remote attribute header mismatch bno/off/len/owner (0x%llx/0x%x/Ox%x/0x%llx)",
					bno, *offset, byte_cnt, ino);
				वापस -EFSCORRUPTED;
			पूर्ण
			hdr_size = माप(काष्ठा xfs_attr3_rmt_hdr);
		पूर्ण

		स_नकल(*dst, src + hdr_size, byte_cnt);

		/* roll buffer क्रमwards */
		len -= blksize;
		src += blksize;
		bno += BTOBB(blksize);

		/* roll attribute data क्रमwards */
		*valuelen -= byte_cnt;
		*dst += byte_cnt;
		*offset += byte_cnt;
	पूर्ण
	वापस 0;
पूर्ण

STATIC व्योम
xfs_attr_rmtval_copyin(
	काष्ठा xfs_mount *mp,
	काष्ठा xfs_buf	*bp,
	xfs_ino_t	ino,
	पूर्णांक		*offset,
	पूर्णांक		*valuelen,
	uपूर्णांक8_t		**src)
अणु
	अक्षर		*dst = bp->b_addr;
	xfs_daddr_t	bno = bp->b_bn;
	पूर्णांक		len = BBTOB(bp->b_length);
	पूर्णांक		blksize = mp->m_attr_geo->blksize;

	ASSERT(len >= blksize);

	जबतक (len > 0 && *valuelen > 0) अणु
		पूर्णांक hdr_size;
		पूर्णांक byte_cnt = XFS_ATTR3_RMT_BUF_SPACE(mp, blksize);

		byte_cnt = min(*valuelen, byte_cnt);
		hdr_size = xfs_attr3_rmt_hdr_set(mp, dst, ino, *offset,
						 byte_cnt, bno);

		स_नकल(dst + hdr_size, *src, byte_cnt);

		/*
		 * If this is the last block, zero the reमुख्यder of it.
		 * Check that we are actually the last block, too.
		 */
		अगर (byte_cnt + hdr_size < blksize) अणु
			ASSERT(*valuelen - byte_cnt == 0);
			ASSERT(len == blksize);
			स_रखो(dst + hdr_size + byte_cnt, 0,
					blksize - hdr_size - byte_cnt);
		पूर्ण

		/* roll buffer क्रमwards */
		len -= blksize;
		dst += blksize;
		bno += BTOBB(blksize);

		/* roll attribute data क्रमwards */
		*valuelen -= byte_cnt;
		*src += byte_cnt;
		*offset += byte_cnt;
	पूर्ण
पूर्ण

/*
 * Read the value associated with an attribute from the out-of-line buffer
 * that we stored it in.
 *
 * Returns 0 on successful retrieval, otherwise an error.
 */
पूर्णांक
xfs_attr_rmtval_get(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_bmbt_irec	map[ATTR_RMTVALUE_MAPSIZE];
	काष्ठा xfs_mount	*mp = args->dp->i_mount;
	काष्ठा xfs_buf		*bp;
	xfs_dablk_t		lblkno = args->rmtblkno;
	uपूर्णांक8_t			*dst = args->value;
	पूर्णांक			valuelen;
	पूर्णांक			nmap;
	पूर्णांक			error;
	पूर्णांक			blkcnt = args->rmtblkcnt;
	पूर्णांक			i;
	पूर्णांक			offset = 0;

	trace_xfs_attr_rmtval_get(args);

	ASSERT(args->valuelen != 0);
	ASSERT(args->rmtvaluelen == args->valuelen);

	valuelen = args->rmtvaluelen;
	जबतक (valuelen > 0) अणु
		nmap = ATTR_RMTVALUE_MAPSIZE;
		error = xfs_bmapi_पढ़ो(args->dp, (xfs_fileoff_t)lblkno,
				       blkcnt, map, &nmap,
				       XFS_BMAPI_ATTRFORK);
		अगर (error)
			वापस error;
		ASSERT(nmap >= 1);

		क्रम (i = 0; (i < nmap) && (valuelen > 0); i++) अणु
			xfs_daddr_t	dblkno;
			पूर्णांक		dblkcnt;

			ASSERT((map[i].br_startblock != DELAYSTARTBLOCK) &&
			       (map[i].br_startblock != HOLESTARTBLOCK));
			dblkno = XFS_FSB_TO_DADDR(mp, map[i].br_startblock);
			dblkcnt = XFS_FSB_TO_BB(mp, map[i].br_blockcount);
			error = xfs_buf_पढ़ो(mp->m_ddev_targp, dblkno, dblkcnt,
					0, &bp, &xfs_attr3_rmt_buf_ops);
			अगर (error)
				वापस error;

			error = xfs_attr_rmtval_copyout(mp, bp, args->dp->i_ino,
							&offset, &valuelen,
							&dst);
			xfs_buf_rअन्यथा(bp);
			अगर (error)
				वापस error;

			/* roll attribute extent map क्रमwards */
			lblkno += map[i].br_blockcount;
			blkcnt -= map[i].br_blockcount;
		पूर्ण
	पूर्ण
	ASSERT(valuelen == 0);
	वापस 0;
पूर्ण

/*
 * Find a "hole" in the attribute address space large enough क्रम us to drop the
 * new attribute's value पूर्णांकo
 */
STATIC पूर्णांक
xfs_attr_rmt_find_hole(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	पूर्णांक			error;
	पूर्णांक			blkcnt;
	xfs_fileoff_t		lfileoff = 0;

	/*
	 * Because CRC enable attributes have headers, we can't just करो a
	 * straight byte to FSB conversion and have to take the header space
	 * पूर्णांकo account.
	 */
	blkcnt = xfs_attr3_rmt_blocks(mp, args->rmtvaluelen);
	error = xfs_bmap_first_unused(args->trans, args->dp, blkcnt, &lfileoff,
						   XFS_ATTR_FORK);
	अगर (error)
		वापस error;

	args->rmtblkno = (xfs_dablk_t)lfileoff;
	args->rmtblkcnt = blkcnt;

	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_attr_rmtval_set_value(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_bmbt_irec	map;
	xfs_dablk_t		lblkno;
	uपूर्णांक8_t			*src = args->value;
	पूर्णांक			blkcnt;
	पूर्णांक			valuelen;
	पूर्णांक			nmap;
	पूर्णांक			error;
	पूर्णांक			offset = 0;

	/*
	 * Roll through the "value", copying the attribute value to the
	 * alपढ़ोy-allocated blocks.  Blocks are written synchronously
	 * so that we can know they are all on disk beक्रमe we turn off
	 * the INCOMPLETE flag.
	 */
	lblkno = args->rmtblkno;
	blkcnt = args->rmtblkcnt;
	valuelen = args->rmtvaluelen;
	जबतक (valuelen > 0) अणु
		काष्ठा xfs_buf	*bp;
		xfs_daddr_t	dblkno;
		पूर्णांक		dblkcnt;

		ASSERT(blkcnt > 0);

		nmap = 1;
		error = xfs_bmapi_पढ़ो(dp, (xfs_fileoff_t)lblkno,
				       blkcnt, &map, &nmap,
				       XFS_BMAPI_ATTRFORK);
		अगर (error)
			वापस error;
		ASSERT(nmap == 1);
		ASSERT((map.br_startblock != DELAYSTARTBLOCK) &&
		       (map.br_startblock != HOLESTARTBLOCK));

		dblkno = XFS_FSB_TO_DADDR(mp, map.br_startblock),
		dblkcnt = XFS_FSB_TO_BB(mp, map.br_blockcount);

		error = xfs_buf_get(mp->m_ddev_targp, dblkno, dblkcnt, &bp);
		अगर (error)
			वापस error;
		bp->b_ops = &xfs_attr3_rmt_buf_ops;

		xfs_attr_rmtval_copyin(mp, bp, args->dp->i_ino, &offset,
				       &valuelen, &src);

		error = xfs_bग_लिखो(bp);	/* GROT: NOTE: synchronous ग_लिखो */
		xfs_buf_rअन्यथा(bp);
		अगर (error)
			वापस error;


		/* roll attribute extent map क्रमwards */
		lblkno += map.br_blockcount;
		blkcnt -= map.br_blockcount;
	पूर्ण
	ASSERT(valuelen == 0);
	वापस 0;
पूर्ण

/* Mark stale any incore buffers क्रम the remote value. */
पूर्णांक
xfs_attr_rmtval_stale(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_bmbt_irec	*map,
	xfs_buf_flags_t		incore_flags)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_buf		*bp;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	अगर (XFS_IS_CORRUPT(mp, map->br_startblock == DELAYSTARTBLOCK) ||
	    XFS_IS_CORRUPT(mp, map->br_startblock == HOLESTARTBLOCK))
		वापस -EFSCORRUPTED;

	bp = xfs_buf_incore(mp->m_ddev_targp,
			XFS_FSB_TO_DADDR(mp, map->br_startblock),
			XFS_FSB_TO_BB(mp, map->br_blockcount), incore_flags);
	अगर (bp) अणु
		xfs_buf_stale(bp);
		xfs_buf_rअन्यथा(bp);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Write the value associated with an attribute पूर्णांकo the out-of-line buffer
 * that we have defined क्रम it.
 */
पूर्णांक
xfs_attr_rmtval_set(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_bmbt_irec	map;
	xfs_dablk_t		lblkno;
	पूर्णांक			blkcnt;
	पूर्णांक			nmap;
	पूर्णांक			error;

	trace_xfs_attr_rmtval_set(args);

	error = xfs_attr_rmt_find_hole(args);
	अगर (error)
		वापस error;

	blkcnt = args->rmtblkcnt;
	lblkno = (xfs_dablk_t)args->rmtblkno;
	/*
	 * Roll through the "value", allocating blocks on disk as required.
	 */
	जबतक (blkcnt > 0) अणु
		/*
		 * Allocate a single extent, up to the size of the value.
		 *
		 * Note that we have to consider this a data allocation as we
		 * ग_लिखो the remote attribute without logging the contents.
		 * Hence we must ensure that we aren't using blocks that are on
		 * the busy list so that we करोn't overग_लिखो blocks which have
		 * recently been मुक्तd but their transactions are not yet
		 * committed to disk. If we overग_लिखो the contents of a busy
		 * extent and then crash then the block may not contain the
		 * correct metadata after log recovery occurs.
		 */
		nmap = 1;
		error = xfs_bmapi_ग_लिखो(args->trans, dp, (xfs_fileoff_t)lblkno,
				  blkcnt, XFS_BMAPI_ATTRFORK, args->total, &map,
				  &nmap);
		अगर (error)
			वापस error;
		error = xfs_defer_finish(&args->trans);
		अगर (error)
			वापस error;

		ASSERT(nmap == 1);
		ASSERT((map.br_startblock != DELAYSTARTBLOCK) &&
		       (map.br_startblock != HOLESTARTBLOCK));
		lblkno += map.br_blockcount;
		blkcnt -= map.br_blockcount;

		/*
		 * Start the next trans in the chain.
		 */
		error = xfs_trans_roll_inode(&args->trans, dp);
		अगर (error)
			वापस error;
	पूर्ण

	वापस xfs_attr_rmtval_set_value(args);
पूर्ण

/*
 * Remove the value associated with an attribute by deleting the
 * out-of-line buffer that it is stored on.
 */
पूर्णांक
xfs_attr_rmtval_invalidate(
	काष्ठा xfs_da_args	*args)
अणु
	xfs_dablk_t		lblkno;
	पूर्णांक			blkcnt;
	पूर्णांक			error;

	/*
	 * Roll through the "value", invalidating the attribute value's blocks.
	 */
	lblkno = args->rmtblkno;
	blkcnt = args->rmtblkcnt;
	जबतक (blkcnt > 0) अणु
		काष्ठा xfs_bmbt_irec	map;
		पूर्णांक			nmap;

		/*
		 * Try to remember where we decided to put the value.
		 */
		nmap = 1;
		error = xfs_bmapi_पढ़ो(args->dp, (xfs_fileoff_t)lblkno,
				       blkcnt, &map, &nmap, XFS_BMAPI_ATTRFORK);
		अगर (error)
			वापस error;
		अगर (XFS_IS_CORRUPT(args->dp->i_mount, nmap != 1))
			वापस -EFSCORRUPTED;
		error = xfs_attr_rmtval_stale(args->dp, &map, XBF_TRYLOCK);
		अगर (error)
			वापस error;

		lblkno += map.br_blockcount;
		blkcnt -= map.br_blockcount;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Remove the value associated with an attribute by deleting the
 * out-of-line buffer that it is stored on.
 */
पूर्णांक
xfs_attr_rmtval_हटाओ(
	काष्ठा xfs_da_args      *args)
अणु
	पूर्णांक			error;
	पूर्णांक			retval;

	trace_xfs_attr_rmtval_हटाओ(args);

	/*
	 * Keep de-allocating extents until the remote-value region is gone.
	 */
	करो अणु
		retval = __xfs_attr_rmtval_हटाओ(args);
		अगर (retval && retval != -EAGAIN)
			वापस retval;

		/*
		 * Close out trans and start the next one in the chain.
		 */
		error = xfs_trans_roll_inode(&args->trans, args->dp);
		अगर (error)
			वापस error;
	पूर्ण जबतक (retval == -EAGAIN);

	वापस 0;
पूर्ण

/*
 * Remove the value associated with an attribute by deleting the out-of-line
 * buffer that it is stored on. Returns EAGAIN क्रम the caller to refresh the
 * transaction and re-call the function
 */
पूर्णांक
__xfs_attr_rmtval_हटाओ(
	काष्ठा xfs_da_args	*args)
अणु
	पूर्णांक			error, करोne;

	/*
	 * Unmap value blocks क्रम this attr.
	 */
	error = xfs_bunmapi(args->trans, args->dp, args->rmtblkno,
			    args->rmtblkcnt, XFS_BMAPI_ATTRFORK, 1, &करोne);
	अगर (error)
		वापस error;

	error = xfs_defer_finish(&args->trans);
	अगर (error)
		वापस error;

	अगर (!करोne)
		वापस -EAGAIN;

	वापस error;
पूर्ण
