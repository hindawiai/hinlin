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
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_dir2.h"

#समावेश <linux/iversion.h>

/*
 * If we are करोing पढ़ोahead on an inode buffer, we might be in log recovery
 * पढ़ोing an inode allocation buffer that hasn't yet been replayed, and hence
 * has not had the inode cores stamped पूर्णांकo it. Hence क्रम पढ़ोahead, the buffer
 * may be potentially invalid.
 *
 * If the पढ़ोahead buffer is invalid, we need to mark it with an error and
 * clear the DONE status of the buffer so that a followup पढ़ो will re-पढ़ो it
 * from disk. We करोn't report the error otherwise to aव्योम warnings during log
 * recovery and we करोn't get unnecessary panics on debug kernels. We use EIO here
 * because all we want to करो is say पढ़ोahead failed; there is no-one to report
 * the error to, so this will distinguish it from a non-ra verअगरier failure.
 * Changes to this पढ़ोahead error behaviour also need to be reflected in
 * xfs_dquot_buf_पढ़ोahead_verअगरy().
 */
अटल व्योम
xfs_inode_buf_verअगरy(
	काष्ठा xfs_buf	*bp,
	bool		पढ़ोahead)
अणु
	काष्ठा xfs_mount *mp = bp->b_mount;
	xfs_agnumber_t	agno;
	पूर्णांक		i;
	पूर्णांक		ni;

	/*
	 * Validate the magic number and version of every inode in the buffer
	 */
	agno = xfs_daddr_to_agno(mp, XFS_BUF_ADDR(bp));
	ni = XFS_BB_TO_FSB(mp, bp->b_length) * mp->m_sb.sb_inopblock;
	क्रम (i = 0; i < ni; i++) अणु
		पूर्णांक		di_ok;
		xfs_dinode_t	*dip;
		xfs_agino_t	unlinked_ino;

		dip = xfs_buf_offset(bp, (i << mp->m_sb.sb_inodelog));
		unlinked_ino = be32_to_cpu(dip->di_next_unlinked);
		di_ok = xfs_verअगरy_magic16(bp, dip->di_magic) &&
			xfs_dinode_good_version(&mp->m_sb, dip->di_version) &&
			xfs_verअगरy_agino_or_null(mp, agno, unlinked_ino);
		अगर (unlikely(XFS_TEST_ERROR(!di_ok, mp,
						XFS_ERRTAG_ITOBP_INOTOBP))) अणु
			अगर (पढ़ोahead) अणु
				bp->b_flags &= ~XBF_DONE;
				xfs_buf_ioerror(bp, -EIO);
				वापस;
			पूर्ण

#अगर_घोषित DEBUG
			xfs_alert(mp,
				"bad inode magic/vsn daddr %lld #%d (magic=%x)",
				(अचिन्हित दीर्घ दीर्घ)bp->b_bn, i,
				be16_to_cpu(dip->di_magic));
#पूर्ण_अगर
			xfs_buf_verअगरier_error(bp, -EFSCORRUPTED,
					__func__, dip, माप(*dip),
					शून्य);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम
xfs_inode_buf_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_inode_buf_verअगरy(bp, false);
पूर्ण

अटल व्योम
xfs_inode_buf_पढ़ोahead_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_inode_buf_verअगरy(bp, true);
पूर्ण

अटल व्योम
xfs_inode_buf_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_inode_buf_verअगरy(bp, false);
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_inode_buf_ops = अणु
	.name = "xfs_inode",
	.magic16 = अणु cpu_to_be16(XFS_DINODE_MAGIC),
		     cpu_to_be16(XFS_DINODE_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_inode_buf_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_inode_buf_ग_लिखो_verअगरy,
पूर्ण;

स्थिर काष्ठा xfs_buf_ops xfs_inode_buf_ra_ops = अणु
	.name = "xfs_inode_ra",
	.magic16 = अणु cpu_to_be16(XFS_DINODE_MAGIC),
		     cpu_to_be16(XFS_DINODE_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_inode_buf_पढ़ोahead_verअगरy,
	.verअगरy_ग_लिखो = xfs_inode_buf_ग_लिखो_verअगरy,
पूर्ण;


/*
 * This routine is called to map an inode to the buffer containing the on-disk
 * version of the inode.  It वापसs a poपूर्णांकer to the buffer containing the
 * on-disk inode in the bpp parameter.
 */
पूर्णांक
xfs_imap_to_bp(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_imap		*imap,
	काष्ठा xfs_buf		**bpp)
अणु
	वापस xfs_trans_पढ़ो_buf(mp, tp, mp->m_ddev_targp, imap->im_blkno,
				   imap->im_len, XBF_UNMAPPED, bpp,
				   &xfs_inode_buf_ops);
पूर्ण

अटल अंतरभूत काष्ठा बारpec64 xfs_inode_decode_bigसमय(uपूर्णांक64_t ts)
अणु
	काष्ठा बारpec64	tv;
	uपूर्णांक32_t		n;

	tv.tv_sec = xfs_bigसमय_प्रकारo_unix(भाग_u64_rem(ts, NSEC_PER_SEC, &n));
	tv.tv_nsec = n;

	वापस tv;
पूर्ण

/* Convert an ondisk बारtamp to an incore बारtamp. */
काष्ठा बारpec64
xfs_inode_from_disk_ts(
	काष्ठा xfs_dinode		*dip,
	स्थिर xfs_बारtamp_t		ts)
अणु
	काष्ठा बारpec64		tv;
	काष्ठा xfs_legacy_बारtamp	*lts;

	अगर (xfs_dinode_has_bigसमय(dip))
		वापस xfs_inode_decode_bigसमय(be64_to_cpu(ts));

	lts = (काष्ठा xfs_legacy_बारtamp *)&ts;
	tv.tv_sec = (पूर्णांक)be32_to_cpu(lts->t_sec);
	tv.tv_nsec = (पूर्णांक)be32_to_cpu(lts->t_nsec);

	वापस tv;
पूर्ण

पूर्णांक
xfs_inode_from_disk(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_dinode	*from)
अणु
	काष्ठा inode		*inode = VFS_I(ip);
	पूर्णांक			error;
	xfs_failaddr_t		fa;

	ASSERT(ip->i_cowfp == शून्य);
	ASSERT(ip->i_afp == शून्य);

	fa = xfs_dinode_verअगरy(ip->i_mount, ip->i_ino, from);
	अगर (fa) अणु
		xfs_inode_verअगरier_error(ip, -EFSCORRUPTED, "dinode", from,
				माप(*from), fa);
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * First get the permanent inक्रमmation that is needed to allocate an
	 * inode. If the inode is unused, mode is zero and we shouldn't mess
	 * with the uninitialized part of it.
	 */
	अगर (!xfs_sb_version_has_v3inode(&ip->i_mount->m_sb))
		ip->i_flushiter = be16_to_cpu(from->di_flushiter);
	inode->i_generation = be32_to_cpu(from->di_gen);
	inode->i_mode = be16_to_cpu(from->di_mode);
	अगर (!inode->i_mode)
		वापस 0;

	/*
	 * Convert v1 inodes immediately to v2 inode क्रमmat as this is the
	 * minimum inode version क्रमmat we support in the rest of the code.
	 * They will also be unconditionally written back to disk as v2 inodes.
	 */
	अगर (unlikely(from->di_version == 1)) अणु
		set_nlink(inode, be16_to_cpu(from->di_onlink));
		ip->i_projid = 0;
	पूर्ण अन्यथा अणु
		set_nlink(inode, be32_to_cpu(from->di_nlink));
		ip->i_projid = (prid_t)be16_to_cpu(from->di_projid_hi) << 16 |
					be16_to_cpu(from->di_projid_lo);
	पूर्ण

	i_uid_ग_लिखो(inode, be32_to_cpu(from->di_uid));
	i_gid_ग_लिखो(inode, be32_to_cpu(from->di_gid));

	/*
	 * Time is चिन्हित, so need to convert to चिन्हित 32 bit beक्रमe
	 * storing in inode बारtamp which may be 64 bit. Otherwise
	 * a समय beक्रमe epoch is converted to a समय दीर्घ after epoch
	 * on 64 bit प्रणालीs.
	 */
	inode->i_aसमय = xfs_inode_from_disk_ts(from, from->di_aसमय);
	inode->i_mसमय = xfs_inode_from_disk_ts(from, from->di_mसमय);
	inode->i_स_समय = xfs_inode_from_disk_ts(from, from->di_स_समय);

	ip->i_disk_size = be64_to_cpu(from->di_size);
	ip->i_nblocks = be64_to_cpu(from->di_nblocks);
	ip->i_extsize = be32_to_cpu(from->di_extsize);
	ip->i_विभाजनoff = from->di_विभाजनoff;
	ip->i_dअगरlags	= be16_to_cpu(from->di_flags);

	अगर (from->di_dmevmask || from->di_dmstate)
		xfs_अगरlags_set(ip, XFS_IPRESERVE_DM_FIELDS);

	अगर (xfs_sb_version_has_v3inode(&ip->i_mount->m_sb)) अणु
		inode_set_iversion_queried(inode,
					   be64_to_cpu(from->di_changecount));
		ip->i_crसमय = xfs_inode_from_disk_ts(from, from->di_crसमय);
		ip->i_dअगरlags2 = be64_to_cpu(from->di_flags2);
		ip->i_cowextsize = be32_to_cpu(from->di_cowextsize);
	पूर्ण

	error = xfs_अगरormat_data_विभाजन(ip, from);
	अगर (error)
		वापस error;
	अगर (from->di_विभाजनoff) अणु
		error = xfs_अगरormat_attr_विभाजन(ip, from);
		अगर (error)
			जाओ out_destroy_data_विभाजन;
	पूर्ण
	अगर (xfs_is_reflink_inode(ip))
		xfs_अगरork_init_cow(ip);
	वापस 0;

out_destroy_data_विभाजन:
	xfs_idestroy_विभाजन(&ip->i_df);
	वापस error;
पूर्ण

/* Convert an incore बारtamp to an ondisk बारtamp. */
अटल अंतरभूत xfs_बारtamp_t
xfs_inode_to_disk_ts(
	काष्ठा xfs_inode		*ip,
	स्थिर काष्ठा बारpec64		tv)
अणु
	काष्ठा xfs_legacy_बारtamp	*lts;
	xfs_बारtamp_t			ts;

	अगर (xfs_inode_has_bigसमय(ip))
		वापस cpu_to_be64(xfs_inode_encode_bigसमय(tv));

	lts = (काष्ठा xfs_legacy_बारtamp *)&ts;
	lts->t_sec = cpu_to_be32(tv.tv_sec);
	lts->t_nsec = cpu_to_be32(tv.tv_nsec);

	वापस ts;
पूर्ण

व्योम
xfs_inode_to_disk(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_dinode	*to,
	xfs_lsn_t		lsn)
अणु
	काष्ठा inode		*inode = VFS_I(ip);

	to->di_magic = cpu_to_be16(XFS_DINODE_MAGIC);
	to->di_onlink = 0;

	to->di_क्रमmat = xfs_अगरork_क्रमmat(&ip->i_df);
	to->di_uid = cpu_to_be32(i_uid_पढ़ो(inode));
	to->di_gid = cpu_to_be32(i_gid_पढ़ो(inode));
	to->di_projid_lo = cpu_to_be16(ip->i_projid & 0xffff);
	to->di_projid_hi = cpu_to_be16(ip->i_projid >> 16);

	स_रखो(to->di_pad, 0, माप(to->di_pad));
	to->di_aसमय = xfs_inode_to_disk_ts(ip, inode->i_aसमय);
	to->di_mसमय = xfs_inode_to_disk_ts(ip, inode->i_mसमय);
	to->di_स_समय = xfs_inode_to_disk_ts(ip, inode->i_स_समय);
	to->di_nlink = cpu_to_be32(inode->i_nlink);
	to->di_gen = cpu_to_be32(inode->i_generation);
	to->di_mode = cpu_to_be16(inode->i_mode);

	to->di_size = cpu_to_be64(ip->i_disk_size);
	to->di_nblocks = cpu_to_be64(ip->i_nblocks);
	to->di_extsize = cpu_to_be32(ip->i_extsize);
	to->di_nextents = cpu_to_be32(xfs_अगरork_nextents(&ip->i_df));
	to->di_anextents = cpu_to_be16(xfs_अगरork_nextents(ip->i_afp));
	to->di_विभाजनoff = ip->i_विभाजनoff;
	to->di_aक्रमmat = xfs_अगरork_क्रमmat(ip->i_afp);
	to->di_flags = cpu_to_be16(ip->i_dअगरlags);

	अगर (xfs_sb_version_has_v3inode(&ip->i_mount->m_sb)) अणु
		to->di_version = 3;
		to->di_changecount = cpu_to_be64(inode_peek_iversion(inode));
		to->di_crसमय = xfs_inode_to_disk_ts(ip, ip->i_crसमय);
		to->di_flags2 = cpu_to_be64(ip->i_dअगरlags2);
		to->di_cowextsize = cpu_to_be32(ip->i_cowextsize);
		to->di_ino = cpu_to_be64(ip->i_ino);
		to->di_lsn = cpu_to_be64(lsn);
		स_रखो(to->di_pad2, 0, माप(to->di_pad2));
		uuid_copy(&to->di_uuid, &ip->i_mount->m_sb.sb_meta_uuid);
		to->di_flushiter = 0;
	पूर्ण अन्यथा अणु
		to->di_version = 2;
		to->di_flushiter = cpu_to_be16(ip->i_flushiter);
	पूर्ण
पूर्ण

अटल xfs_failaddr_t
xfs_dinode_verअगरy_विभाजन(
	काष्ठा xfs_dinode	*dip,
	काष्ठा xfs_mount	*mp,
	पूर्णांक			whichविभाजन)
अणु
	uपूर्णांक32_t		di_nextents = XFS_DFORK_NEXTENTS(dip, whichविभाजन);

	चयन (XFS_DFORK_FORMAT(dip, whichविभाजन)) अणु
	हाल XFS_DINODE_FMT_LOCAL:
		/*
		 * no local regular files yet
		 */
		अगर (whichविभाजन == XFS_DATA_FORK) अणु
			अगर (S_ISREG(be16_to_cpu(dip->di_mode)))
				वापस __this_address;
			अगर (be64_to_cpu(dip->di_size) >
					XFS_DFORK_SIZE(dip, mp, whichविभाजन))
				वापस __this_address;
		पूर्ण
		अगर (di_nextents)
			वापस __this_address;
		अवरोध;
	हाल XFS_DINODE_FMT_EXTENTS:
		अगर (di_nextents > XFS_DFORK_MAXEXT(dip, mp, whichविभाजन))
			वापस __this_address;
		अवरोध;
	हाल XFS_DINODE_FMT_BTREE:
		अगर (whichविभाजन == XFS_ATTR_FORK) अणु
			अगर (di_nextents > MAXAEXTNUM)
				वापस __this_address;
		पूर्ण अन्यथा अगर (di_nextents > MAXEXTNUM) अणु
			वापस __this_address;
		पूर्ण
		अवरोध;
	शेष:
		वापस __this_address;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल xfs_failaddr_t
xfs_dinode_verअगरy_विभाजनoff(
	काष्ठा xfs_dinode	*dip,
	काष्ठा xfs_mount	*mp)
अणु
	अगर (!dip->di_विभाजनoff)
		वापस शून्य;

	चयन (dip->di_क्रमmat)  अणु
	हाल XFS_DINODE_FMT_DEV:
		अगर (dip->di_विभाजनoff != (roundup(माप(xfs_dev_t), 8) >> 3))
			वापस __this_address;
		अवरोध;
	हाल XFS_DINODE_FMT_LOCAL:	/* fall through ... */
	हाल XFS_DINODE_FMT_EXTENTS:    /* fall through ... */
	हाल XFS_DINODE_FMT_BTREE:
		अगर (dip->di_विभाजनoff >= (XFS_LITINO(mp) >> 3))
			वापस __this_address;
		अवरोध;
	शेष:
		वापस __this_address;
	पूर्ण
	वापस शून्य;
पूर्ण

xfs_failaddr_t
xfs_dinode_verअगरy(
	काष्ठा xfs_mount	*mp,
	xfs_ino_t		ino,
	काष्ठा xfs_dinode	*dip)
अणु
	xfs_failaddr_t		fa;
	uपूर्णांक16_t		mode;
	uपूर्णांक16_t		flags;
	uपूर्णांक64_t		flags2;
	uपूर्णांक64_t		di_size;

	अगर (dip->di_magic != cpu_to_be16(XFS_DINODE_MAGIC))
		वापस __this_address;

	/* Verअगरy v3 पूर्णांकegrity inक्रमmation first */
	अगर (dip->di_version >= 3) अणु
		अगर (!xfs_sb_version_has_v3inode(&mp->m_sb))
			वापस __this_address;
		अगर (!xfs_verअगरy_cksum((अक्षर *)dip, mp->m_sb.sb_inodesize,
				      XFS_DINODE_CRC_OFF))
			वापस __this_address;
		अगर (be64_to_cpu(dip->di_ino) != ino)
			वापस __this_address;
		अगर (!uuid_equal(&dip->di_uuid, &mp->m_sb.sb_meta_uuid))
			वापस __this_address;
	पूर्ण

	/* करोn't allow invalid i_size */
	di_size = be64_to_cpu(dip->di_size);
	अगर (di_size & (1ULL << 63))
		वापस __this_address;

	mode = be16_to_cpu(dip->di_mode);
	अगर (mode && xfs_mode_to_ftype(mode) == XFS_सूची3_FT_UNKNOWN)
		वापस __this_address;

	/* No zero-length symlinks/dirs. */
	अगर ((S_ISLNK(mode) || S_ISसूची(mode)) && di_size == 0)
		वापस __this_address;

	/* Fork checks carried over from xfs_अगरormat_विभाजन */
	अगर (mode &&
	    be32_to_cpu(dip->di_nextents) + be16_to_cpu(dip->di_anextents) >
			be64_to_cpu(dip->di_nblocks))
		वापस __this_address;

	अगर (mode && XFS_DFORK_BOFF(dip) > mp->m_sb.sb_inodesize)
		वापस __this_address;

	flags = be16_to_cpu(dip->di_flags);

	अगर (mode && (flags & XFS_DIFLAG_REALTIME) && !mp->m_rtdev_targp)
		वापस __this_address;

	/* check क्रम illegal values of विभाजनoff */
	fa = xfs_dinode_verअगरy_विभाजनoff(dip, mp);
	अगर (fa)
		वापस fa;

	/* Do we have appropriate data विभाजन क्रमmats क्रम the mode? */
	चयन (mode & S_IFMT) अणु
	हाल S_IFIFO:
	हाल S_IFCHR:
	हाल S_IFBLK:
	हाल S_IFSOCK:
		अगर (dip->di_क्रमmat != XFS_DINODE_FMT_DEV)
			वापस __this_address;
		अवरोध;
	हाल S_IFREG:
	हाल S_IFLNK:
	हाल S_IFसूची:
		fa = xfs_dinode_verअगरy_विभाजन(dip, mp, XFS_DATA_FORK);
		अगर (fa)
			वापस fa;
		अवरोध;
	हाल 0:
		/* Uninitialized inode ok. */
		अवरोध;
	शेष:
		वापस __this_address;
	पूर्ण

	अगर (dip->di_विभाजनoff) अणु
		fa = xfs_dinode_verअगरy_विभाजन(dip, mp, XFS_ATTR_FORK);
		अगर (fa)
			वापस fa;
	पूर्ण अन्यथा अणु
		/*
		 * If there is no विभाजन offset, this may be a freshly-made inode
		 * in a new disk cluster, in which हाल di_aक्रमmat is zeroed.
		 * Otherwise, such an inode must be in EXTENTS क्रमmat; this goes
		 * क्रम मुक्तd inodes as well.
		 */
		चयन (dip->di_aक्रमmat) अणु
		हाल 0:
		हाल XFS_DINODE_FMT_EXTENTS:
			अवरोध;
		शेष:
			वापस __this_address;
		पूर्ण
		अगर (dip->di_anextents)
			वापस __this_address;
	पूर्ण

	/* extent size hपूर्णांक validation */
	fa = xfs_inode_validate_extsize(mp, be32_to_cpu(dip->di_extsize),
			mode, flags);
	अगर (fa)
		वापस fa;

	/* only version 3 or greater inodes are extensively verअगरied here */
	अगर (dip->di_version < 3)
		वापस शून्य;

	flags2 = be64_to_cpu(dip->di_flags2);

	/* करोn't allow reflink/cowextsize if we don't have reflink */
	अगर ((flags2 & (XFS_DIFLAG2_REFLINK | XFS_DIFLAG2_COWEXTSIZE)) &&
	     !xfs_sb_version_hasreflink(&mp->m_sb))
		वापस __this_address;

	/* only regular files get reflink */
	अगर ((flags2 & XFS_DIFLAG2_REFLINK) && (mode & S_IFMT) != S_IFREG)
		वापस __this_address;

	/* करोn't let reflink and realसमय mix */
	अगर ((flags2 & XFS_DIFLAG2_REFLINK) && (flags & XFS_DIFLAG_REALTIME))
		वापस __this_address;

	/* COW extent size hपूर्णांक validation */
	fa = xfs_inode_validate_cowextsize(mp, be32_to_cpu(dip->di_cowextsize),
			mode, flags, flags2);
	अगर (fa)
		वापस fa;

	/* bigसमय अगरlag can only happen on bigसमय fileप्रणालीs */
	अगर (xfs_dinode_has_bigसमय(dip) &&
	    !xfs_sb_version_hasbigसमय(&mp->m_sb))
		वापस __this_address;

	वापस शून्य;
पूर्ण

व्योम
xfs_dinode_calc_crc(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dinode	*dip)
अणु
	uपूर्णांक32_t		crc;

	अगर (dip->di_version < 3)
		वापस;

	ASSERT(xfs_sb_version_hascrc(&mp->m_sb));
	crc = xfs_start_cksum_update((अक्षर *)dip, mp->m_sb.sb_inodesize,
			      XFS_DINODE_CRC_OFF);
	dip->di_crc = xfs_end_cksum(crc);
पूर्ण

/*
 * Validate di_extsize hपूर्णांक.
 *
 * 1. Extent size hपूर्णांक is only valid क्रम directories and regular files.
 * 2. FS_XFLAG_EXTSIZE is only valid क्रम regular files.
 * 3. FS_XFLAG_EXTSZINHERIT is only valid क्रम directories.
 * 4. Hपूर्णांक cannot be larger than MAXTEXTLEN.
 * 5. Can be changed on directories at any समय.
 * 6. Hपूर्णांक value of 0 turns off hपूर्णांकs, clears inode flags.
 * 7. Extent size must be a multiple of the appropriate block size.
 *    For realसमय files, this is the rt extent size.
 * 8. For non-realसमय files, the extent size hपूर्णांक must be limited
 *    to half the AG size to aव्योम alignment extending the extent beyond the
 *    limits of the AG.
 */
xfs_failaddr_t
xfs_inode_validate_extsize(
	काष्ठा xfs_mount		*mp,
	uपूर्णांक32_t			extsize,
	uपूर्णांक16_t			mode,
	uपूर्णांक16_t			flags)
अणु
	bool				rt_flag;
	bool				hपूर्णांक_flag;
	bool				inherit_flag;
	uपूर्णांक32_t			extsize_bytes;
	uपूर्णांक32_t			blocksize_bytes;

	rt_flag = (flags & XFS_DIFLAG_REALTIME);
	hपूर्णांक_flag = (flags & XFS_DIFLAG_EXTSIZE);
	inherit_flag = (flags & XFS_DIFLAG_EXTSZINHERIT);
	extsize_bytes = XFS_FSB_TO_B(mp, extsize);

	/*
	 * This comment describes a historic gap in this verअगरier function.
	 *
	 * On older kernels, the extent size hपूर्णांक verअगरier करोesn't check that
	 * the extent size hपूर्णांक is an पूर्णांकeger multiple of the realसमय extent
	 * size on a directory with both RTINHERIT and EXTSZINHERIT flags set.
	 * The verअगरier has always enक्रमced the alignment rule क्रम regular
	 * files with the REALTIME flag set.
	 *
	 * If a directory with a misaligned extent size hपूर्णांक is allowed to
	 * propagate that hपूर्णांक पूर्णांकo a new regular realसमय file, the result
	 * is that the inode cluster buffer verअगरier will trigger a corruption
	 * shutकरोwn the next समय it is run.
	 *
	 * Unक्रमtunately, there could be fileप्रणालीs with these misconfigured
	 * directories in the wild, so we cannot add a check to this verअगरier
	 * at this समय because that will result a new source of directory
	 * corruption errors when पढ़ोing an existing fileप्रणाली.  Instead, we
	 * permit the misconfiguration to pass through the verअगरiers so that
	 * callers of this function can correct and mitigate बाह्यally.
	 */

	अगर (rt_flag)
		blocksize_bytes = mp->m_sb.sb_rextsize << mp->m_sb.sb_blocklog;
	अन्यथा
		blocksize_bytes = mp->m_sb.sb_blocksize;

	अगर ((hपूर्णांक_flag || inherit_flag) && !(S_ISसूची(mode) || S_ISREG(mode)))
		वापस __this_address;

	अगर (hपूर्णांक_flag && !S_ISREG(mode))
		वापस __this_address;

	अगर (inherit_flag && !S_ISसूची(mode))
		वापस __this_address;

	अगर ((hपूर्णांक_flag || inherit_flag) && extsize == 0)
		वापस __this_address;

	/* मुक्त inodes get flags set to zero but extsize reमुख्यs */
	अगर (mode && !(hपूर्णांक_flag || inherit_flag) && extsize != 0)
		वापस __this_address;

	अगर (extsize_bytes % blocksize_bytes)
		वापस __this_address;

	अगर (extsize > MAXEXTLEN)
		वापस __this_address;

	अगर (!rt_flag && extsize > mp->m_sb.sb_agblocks / 2)
		वापस __this_address;

	वापस शून्य;
पूर्ण

/*
 * Validate di_cowextsize hपूर्णांक.
 *
 * 1. CoW extent size hपूर्णांक can only be set अगर reflink is enabled on the fs.
 *    The inode करोes not have to have any shared blocks, but it must be a v3.
 * 2. FS_XFLAG_COWEXTSIZE is only valid क्रम directories and regular files;
 *    क्रम a directory, the hपूर्णांक is propagated to new files.
 * 3. Can be changed on files & directories at any समय.
 * 4. Hपूर्णांक value of 0 turns off hपूर्णांकs, clears inode flags.
 * 5. Extent size must be a multiple of the appropriate block size.
 * 6. The extent size hपूर्णांक must be limited to half the AG size to aव्योम
 *    alignment extending the extent beyond the limits of the AG.
 */
xfs_failaddr_t
xfs_inode_validate_cowextsize(
	काष्ठा xfs_mount		*mp,
	uपूर्णांक32_t			cowextsize,
	uपूर्णांक16_t			mode,
	uपूर्णांक16_t			flags,
	uपूर्णांक64_t			flags2)
अणु
	bool				rt_flag;
	bool				hपूर्णांक_flag;
	uपूर्णांक32_t			cowextsize_bytes;

	rt_flag = (flags & XFS_DIFLAG_REALTIME);
	hपूर्णांक_flag = (flags2 & XFS_DIFLAG2_COWEXTSIZE);
	cowextsize_bytes = XFS_FSB_TO_B(mp, cowextsize);

	अगर (hपूर्णांक_flag && !xfs_sb_version_hasreflink(&mp->m_sb))
		वापस __this_address;

	अगर (hपूर्णांक_flag && !(S_ISसूची(mode) || S_ISREG(mode)))
		वापस __this_address;

	अगर (hपूर्णांक_flag && cowextsize == 0)
		वापस __this_address;

	/* मुक्त inodes get flags set to zero but cowextsize reमुख्यs */
	अगर (mode && !hपूर्णांक_flag && cowextsize != 0)
		वापस __this_address;

	अगर (hपूर्णांक_flag && rt_flag)
		वापस __this_address;

	अगर (cowextsize_bytes % mp->m_sb.sb_blocksize)
		वापस __this_address;

	अगर (cowextsize > MAXEXTLEN)
		वापस __this_address;

	अगर (cowextsize > mp->m_sb.sb_agblocks / 2)
		वापस __this_address;

	वापस शून्य;
पूर्ण
