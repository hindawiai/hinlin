<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
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
#समावेश "xfs_trace.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_log.h"
#समावेश "xfs_error.h"

#समावेश <linux/iversion.h>

kmem_zone_t	*xfs_ili_zone;		/* inode log item zone */

अटल अंतरभूत काष्ठा xfs_inode_log_item *INODE_ITEM(काष्ठा xfs_log_item *lip)
अणु
	वापस container_of(lip, काष्ठा xfs_inode_log_item, ili_item);
पूर्ण

STATIC व्योम
xfs_inode_item_data_विभाजन_size(
	काष्ठा xfs_inode_log_item *iip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	काष्ठा xfs_inode	*ip = iip->ili_inode;

	चयन (ip->i_df.अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_EXTENTS:
		अगर ((iip->ili_fields & XFS_ILOG_DEXT) &&
		    ip->i_df.अगर_nextents > 0 &&
		    ip->i_df.अगर_bytes > 0) अणु
			/* worst हाल, करोesn't subtract delalloc extents */
			*nbytes += XFS_IFORK_DSIZE(ip);
			*nvecs += 1;
		पूर्ण
		अवरोध;
	हाल XFS_DINODE_FMT_BTREE:
		अगर ((iip->ili_fields & XFS_ILOG_DBROOT) &&
		    ip->i_df.अगर_broot_bytes > 0) अणु
			*nbytes += ip->i_df.अगर_broot_bytes;
			*nvecs += 1;
		पूर्ण
		अवरोध;
	हाल XFS_DINODE_FMT_LOCAL:
		अगर ((iip->ili_fields & XFS_ILOG_DDATA) &&
		    ip->i_df.अगर_bytes > 0) अणु
			*nbytes += roundup(ip->i_df.अगर_bytes, 4);
			*nvecs += 1;
		पूर्ण
		अवरोध;

	हाल XFS_DINODE_FMT_DEV:
		अवरोध;
	शेष:
		ASSERT(0);
		अवरोध;
	पूर्ण
पूर्ण

STATIC व्योम
xfs_inode_item_attr_विभाजन_size(
	काष्ठा xfs_inode_log_item *iip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	काष्ठा xfs_inode	*ip = iip->ili_inode;

	चयन (ip->i_afp->अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_EXTENTS:
		अगर ((iip->ili_fields & XFS_ILOG_AEXT) &&
		    ip->i_afp->अगर_nextents > 0 &&
		    ip->i_afp->अगर_bytes > 0) अणु
			/* worst हाल, करोesn't subtract unused space */
			*nbytes += XFS_IFORK_ASIZE(ip);
			*nvecs += 1;
		पूर्ण
		अवरोध;
	हाल XFS_DINODE_FMT_BTREE:
		अगर ((iip->ili_fields & XFS_ILOG_ABROOT) &&
		    ip->i_afp->अगर_broot_bytes > 0) अणु
			*nbytes += ip->i_afp->अगर_broot_bytes;
			*nvecs += 1;
		पूर्ण
		अवरोध;
	हाल XFS_DINODE_FMT_LOCAL:
		अगर ((iip->ili_fields & XFS_ILOG_ADATA) &&
		    ip->i_afp->अगर_bytes > 0) अणु
			*nbytes += roundup(ip->i_afp->अगर_bytes, 4);
			*nvecs += 1;
		पूर्ण
		अवरोध;
	शेष:
		ASSERT(0);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * This वापसs the number of iovecs needed to log the given inode item.
 *
 * We need one iovec क्रम the inode log क्रमmat काष्ठाure, one क्रम the
 * inode core, and possibly one क्रम the inode data/extents/b-tree root
 * and one क्रम the inode attribute data/extents/b-tree root.
 */
STATIC व्योम
xfs_inode_item_size(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	काष्ठा xfs_inode_log_item *iip = INODE_ITEM(lip);
	काष्ठा xfs_inode	*ip = iip->ili_inode;

	*nvecs += 2;
	*nbytes += माप(काष्ठा xfs_inode_log_क्रमmat) +
		   xfs_log_dinode_size(ip->i_mount);

	xfs_inode_item_data_विभाजन_size(iip, nvecs, nbytes);
	अगर (XFS_IFORK_Q(ip))
		xfs_inode_item_attr_विभाजन_size(iip, nvecs, nbytes);
पूर्ण

STATIC व्योम
xfs_inode_item_क्रमmat_data_विभाजन(
	काष्ठा xfs_inode_log_item *iip,
	काष्ठा xfs_inode_log_क्रमmat *ilf,
	काष्ठा xfs_log_vec	*lv,
	काष्ठा xfs_log_iovec	**vecp)
अणु
	काष्ठा xfs_inode	*ip = iip->ili_inode;
	माप_प्रकार			data_bytes;

	चयन (ip->i_df.अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_EXTENTS:
		iip->ili_fields &=
			~(XFS_ILOG_DDATA | XFS_ILOG_DBROOT | XFS_ILOG_DEV);

		अगर ((iip->ili_fields & XFS_ILOG_DEXT) &&
		    ip->i_df.अगर_nextents > 0 &&
		    ip->i_df.अगर_bytes > 0) अणु
			काष्ठा xfs_bmbt_rec *p;

			ASSERT(xfs_iext_count(&ip->i_df) > 0);

			p = xlog_prepare_iovec(lv, vecp, XLOG_REG_TYPE_IEXT);
			data_bytes = xfs_iextents_copy(ip, p, XFS_DATA_FORK);
			xlog_finish_iovec(lv, *vecp, data_bytes);

			ASSERT(data_bytes <= ip->i_df.अगर_bytes);

			ilf->ilf_dsize = data_bytes;
			ilf->ilf_size++;
		पूर्ण अन्यथा अणु
			iip->ili_fields &= ~XFS_ILOG_DEXT;
		पूर्ण
		अवरोध;
	हाल XFS_DINODE_FMT_BTREE:
		iip->ili_fields &=
			~(XFS_ILOG_DDATA | XFS_ILOG_DEXT | XFS_ILOG_DEV);

		अगर ((iip->ili_fields & XFS_ILOG_DBROOT) &&
		    ip->i_df.अगर_broot_bytes > 0) अणु
			ASSERT(ip->i_df.अगर_broot != शून्य);
			xlog_copy_iovec(lv, vecp, XLOG_REG_TYPE_IBROOT,
					ip->i_df.अगर_broot,
					ip->i_df.अगर_broot_bytes);
			ilf->ilf_dsize = ip->i_df.अगर_broot_bytes;
			ilf->ilf_size++;
		पूर्ण अन्यथा अणु
			ASSERT(!(iip->ili_fields &
				 XFS_ILOG_DBROOT));
			iip->ili_fields &= ~XFS_ILOG_DBROOT;
		पूर्ण
		अवरोध;
	हाल XFS_DINODE_FMT_LOCAL:
		iip->ili_fields &=
			~(XFS_ILOG_DEXT | XFS_ILOG_DBROOT | XFS_ILOG_DEV);
		अगर ((iip->ili_fields & XFS_ILOG_DDATA) &&
		    ip->i_df.अगर_bytes > 0) अणु
			/*
			 * Round i_bytes up to a word boundary.
			 * The underlying memory is guaranteed
			 * to be there by xfs_idata_पुनः_स्मृति().
			 */
			data_bytes = roundup(ip->i_df.अगर_bytes, 4);
			ASSERT(ip->i_df.अगर_u1.अगर_data != शून्य);
			ASSERT(ip->i_disk_size > 0);
			xlog_copy_iovec(lv, vecp, XLOG_REG_TYPE_ILOCAL,
					ip->i_df.अगर_u1.अगर_data, data_bytes);
			ilf->ilf_dsize = (अचिन्हित)data_bytes;
			ilf->ilf_size++;
		पूर्ण अन्यथा अणु
			iip->ili_fields &= ~XFS_ILOG_DDATA;
		पूर्ण
		अवरोध;
	हाल XFS_DINODE_FMT_DEV:
		iip->ili_fields &=
			~(XFS_ILOG_DDATA | XFS_ILOG_DBROOT | XFS_ILOG_DEXT);
		अगर (iip->ili_fields & XFS_ILOG_DEV)
			ilf->ilf_u.ilfu_rdev = sysv_encode_dev(VFS_I(ip)->i_rdev);
		अवरोध;
	शेष:
		ASSERT(0);
		अवरोध;
	पूर्ण
पूर्ण

STATIC व्योम
xfs_inode_item_क्रमmat_attr_विभाजन(
	काष्ठा xfs_inode_log_item *iip,
	काष्ठा xfs_inode_log_क्रमmat *ilf,
	काष्ठा xfs_log_vec	*lv,
	काष्ठा xfs_log_iovec	**vecp)
अणु
	काष्ठा xfs_inode	*ip = iip->ili_inode;
	माप_प्रकार			data_bytes;

	चयन (ip->i_afp->अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_EXTENTS:
		iip->ili_fields &=
			~(XFS_ILOG_ADATA | XFS_ILOG_ABROOT);

		अगर ((iip->ili_fields & XFS_ILOG_AEXT) &&
		    ip->i_afp->अगर_nextents > 0 &&
		    ip->i_afp->अगर_bytes > 0) अणु
			काष्ठा xfs_bmbt_rec *p;

			ASSERT(xfs_iext_count(ip->i_afp) ==
				ip->i_afp->अगर_nextents);

			p = xlog_prepare_iovec(lv, vecp, XLOG_REG_TYPE_IATTR_EXT);
			data_bytes = xfs_iextents_copy(ip, p, XFS_ATTR_FORK);
			xlog_finish_iovec(lv, *vecp, data_bytes);

			ilf->ilf_asize = data_bytes;
			ilf->ilf_size++;
		पूर्ण अन्यथा अणु
			iip->ili_fields &= ~XFS_ILOG_AEXT;
		पूर्ण
		अवरोध;
	हाल XFS_DINODE_FMT_BTREE:
		iip->ili_fields &=
			~(XFS_ILOG_ADATA | XFS_ILOG_AEXT);

		अगर ((iip->ili_fields & XFS_ILOG_ABROOT) &&
		    ip->i_afp->अगर_broot_bytes > 0) अणु
			ASSERT(ip->i_afp->अगर_broot != शून्य);

			xlog_copy_iovec(lv, vecp, XLOG_REG_TYPE_IATTR_BROOT,
					ip->i_afp->अगर_broot,
					ip->i_afp->अगर_broot_bytes);
			ilf->ilf_asize = ip->i_afp->अगर_broot_bytes;
			ilf->ilf_size++;
		पूर्ण अन्यथा अणु
			iip->ili_fields &= ~XFS_ILOG_ABROOT;
		पूर्ण
		अवरोध;
	हाल XFS_DINODE_FMT_LOCAL:
		iip->ili_fields &=
			~(XFS_ILOG_AEXT | XFS_ILOG_ABROOT);

		अगर ((iip->ili_fields & XFS_ILOG_ADATA) &&
		    ip->i_afp->अगर_bytes > 0) अणु
			/*
			 * Round i_bytes up to a word boundary.
			 * The underlying memory is guaranteed
			 * to be there by xfs_idata_पुनः_स्मृति().
			 */
			data_bytes = roundup(ip->i_afp->अगर_bytes, 4);
			ASSERT(ip->i_afp->अगर_u1.अगर_data != शून्य);
			xlog_copy_iovec(lv, vecp, XLOG_REG_TYPE_IATTR_LOCAL,
					ip->i_afp->अगर_u1.अगर_data,
					data_bytes);
			ilf->ilf_asize = (अचिन्हित)data_bytes;
			ilf->ilf_size++;
		पूर्ण अन्यथा अणु
			iip->ili_fields &= ~XFS_ILOG_ADATA;
		पूर्ण
		अवरोध;
	शेष:
		ASSERT(0);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Convert an incore बारtamp to a log बारtamp.  Note that the log क्रमmat
 * specअगरies host endian क्रमmat!
 */
अटल अंतरभूत xfs_log_बारtamp_t
xfs_inode_to_log_dinode_ts(
	काष्ठा xfs_inode		*ip,
	स्थिर काष्ठा बारpec64		tv)
अणु
	काष्ठा xfs_log_legacy_बारtamp	*lits;
	xfs_log_बारtamp_t		its;

	अगर (xfs_inode_has_bigसमय(ip))
		वापस xfs_inode_encode_bigसमय(tv);

	lits = (काष्ठा xfs_log_legacy_बारtamp *)&its;
	lits->t_sec = tv.tv_sec;
	lits->t_nsec = tv.tv_nsec;

	वापस its;
पूर्ण

/*
 * The legacy DMAPI fields are only present in the on-disk and in-log inodes,
 * but not in the in-memory one.  But we are guaranteed to have an inode buffer
 * in memory when logging an inode, so we can just copy it from the on-disk
 * inode to the in-log inode here so that recovery of file प्रणाली with these
 * fields set to non-zero values करोesn't lose them.  For all other हालs we zero
 * the fields.
 */
अटल व्योम
xfs_copy_dm_fields_to_log_dinode(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_log_dinode	*to)
अणु
	काष्ठा xfs_dinode	*dip;

	dip = xfs_buf_offset(ip->i_itemp->ili_item.li_buf,
			     ip->i_imap.im_boffset);

	अगर (xfs_अगरlags_test(ip, XFS_IPRESERVE_DM_FIELDS)) अणु
		to->di_dmevmask = be32_to_cpu(dip->di_dmevmask);
		to->di_dmstate = be16_to_cpu(dip->di_dmstate);
	पूर्ण अन्यथा अणु
		to->di_dmevmask = 0;
		to->di_dmstate = 0;
	पूर्ण
पूर्ण

अटल व्योम
xfs_inode_to_log_dinode(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_log_dinode	*to,
	xfs_lsn_t		lsn)
अणु
	काष्ठा inode		*inode = VFS_I(ip);

	to->di_magic = XFS_DINODE_MAGIC;
	to->di_क्रमmat = xfs_अगरork_क्रमmat(&ip->i_df);
	to->di_uid = i_uid_पढ़ो(inode);
	to->di_gid = i_gid_पढ़ो(inode);
	to->di_projid_lo = ip->i_projid & 0xffff;
	to->di_projid_hi = ip->i_projid >> 16;

	स_रखो(to->di_pad, 0, माप(to->di_pad));
	स_रखो(to->di_pad3, 0, माप(to->di_pad3));
	to->di_aसमय = xfs_inode_to_log_dinode_ts(ip, inode->i_aसमय);
	to->di_mसमय = xfs_inode_to_log_dinode_ts(ip, inode->i_mसमय);
	to->di_स_समय = xfs_inode_to_log_dinode_ts(ip, inode->i_स_समय);
	to->di_nlink = inode->i_nlink;
	to->di_gen = inode->i_generation;
	to->di_mode = inode->i_mode;

	to->di_size = ip->i_disk_size;
	to->di_nblocks = ip->i_nblocks;
	to->di_extsize = ip->i_extsize;
	to->di_nextents = xfs_अगरork_nextents(&ip->i_df);
	to->di_anextents = xfs_अगरork_nextents(ip->i_afp);
	to->di_विभाजनoff = ip->i_विभाजनoff;
	to->di_aक्रमmat = xfs_अगरork_क्रमmat(ip->i_afp);
	to->di_flags = ip->i_dअगरlags;

	xfs_copy_dm_fields_to_log_dinode(ip, to);

	/* log a dummy value to ensure log काष्ठाure is fully initialised */
	to->di_next_unlinked = शून्यAGINO;

	अगर (xfs_sb_version_has_v3inode(&ip->i_mount->m_sb)) अणु
		to->di_version = 3;
		to->di_changecount = inode_peek_iversion(inode);
		to->di_crसमय = xfs_inode_to_log_dinode_ts(ip, ip->i_crसमय);
		to->di_flags2 = ip->i_dअगरlags2;
		to->di_cowextsize = ip->i_cowextsize;
		to->di_ino = ip->i_ino;
		to->di_lsn = lsn;
		स_रखो(to->di_pad2, 0, माप(to->di_pad2));
		uuid_copy(&to->di_uuid, &ip->i_mount->m_sb.sb_meta_uuid);
		to->di_flushiter = 0;
	पूर्ण अन्यथा अणु
		to->di_version = 2;
		to->di_flushiter = ip->i_flushiter;
	पूर्ण
पूर्ण

/*
 * Format the inode core. Current बारtamp data is only in the VFS inode
 * fields, so we need to grab them from there. Hence rather than just copying
 * the XFS inode core काष्ठाure, क्रमmat the fields directly पूर्णांकo the iovec.
 */
अटल व्योम
xfs_inode_item_क्रमmat_core(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_log_vec	*lv,
	काष्ठा xfs_log_iovec	**vecp)
अणु
	काष्ठा xfs_log_dinode	*dic;

	dic = xlog_prepare_iovec(lv, vecp, XLOG_REG_TYPE_ICORE);
	xfs_inode_to_log_dinode(ip, dic, ip->i_itemp->ili_item.li_lsn);
	xlog_finish_iovec(lv, *vecp, xfs_log_dinode_size(ip->i_mount));
पूर्ण

/*
 * This is called to fill in the vector of log iovecs क्रम the given inode
 * log item.  It fills the first item with an inode log क्रमmat काष्ठाure,
 * the second with the on-disk inode काष्ठाure, and a possible third and/or
 * fourth with the inode data/extents/b-tree root and inode attributes
 * data/extents/b-tree root.
 *
 * Note: Always use the 64 bit inode log क्रमmat काष्ठाure so we करोn't
 * leave an uninitialised hole in the क्रमmat item on 64 bit प्रणालीs. Log
 * recovery on 32 bit प्रणालीs handles this just fine, so there's no reason
 * क्रम not using an initialising the properly padded काष्ठाure all the समय.
 */
STATIC व्योम
xfs_inode_item_क्रमmat(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_log_vec	*lv)
अणु
	काष्ठा xfs_inode_log_item *iip = INODE_ITEM(lip);
	काष्ठा xfs_inode	*ip = iip->ili_inode;
	काष्ठा xfs_log_iovec	*vecp = शून्य;
	काष्ठा xfs_inode_log_क्रमmat *ilf;

	ilf = xlog_prepare_iovec(lv, &vecp, XLOG_REG_TYPE_IFORMAT);
	ilf->ilf_type = XFS_LI_INODE;
	ilf->ilf_ino = ip->i_ino;
	ilf->ilf_blkno = ip->i_imap.im_blkno;
	ilf->ilf_len = ip->i_imap.im_len;
	ilf->ilf_boffset = ip->i_imap.im_boffset;
	ilf->ilf_fields = XFS_ILOG_CORE;
	ilf->ilf_size = 2; /* क्रमmat + core */

	/*
	 * make sure we करोn't leak uninitialised data पूर्णांकo the log in the हाल
	 * when we करोn't log every field in the inode.
	 */
	ilf->ilf_dsize = 0;
	ilf->ilf_asize = 0;
	ilf->ilf_pad = 0;
	स_रखो(&ilf->ilf_u, 0, माप(ilf->ilf_u));

	xlog_finish_iovec(lv, vecp, माप(*ilf));

	xfs_inode_item_क्रमmat_core(ip, lv, &vecp);
	xfs_inode_item_क्रमmat_data_विभाजन(iip, ilf, lv, &vecp);
	अगर (XFS_IFORK_Q(ip)) अणु
		xfs_inode_item_क्रमmat_attr_विभाजन(iip, ilf, lv, &vecp);
	पूर्ण अन्यथा अणु
		iip->ili_fields &=
			~(XFS_ILOG_ADATA | XFS_ILOG_ABROOT | XFS_ILOG_AEXT);
	पूर्ण

	/* update the क्रमmat with the exact fields we actually logged */
	ilf->ilf_fields |= (iip->ili_fields & ~XFS_ILOG_TIMESTAMP);
पूर्ण

/*
 * This is called to pin the inode associated with the inode log
 * item in memory so it cannot be written out.
 */
STATIC व्योम
xfs_inode_item_pin(
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_inode	*ip = INODE_ITEM(lip)->ili_inode;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	ASSERT(lip->li_buf);

	trace_xfs_inode_pin(ip, _RET_IP_);
	atomic_inc(&ip->i_pincount);
पूर्ण


/*
 * This is called to unpin the inode associated with the inode log
 * item which was previously pinned with a call to xfs_inode_item_pin().
 *
 * Also wake up anyone in xfs_iunpin_रुको() अगर the count goes to 0.
 *
 * Note that unpin can race with inode cluster buffer मुक्तing marking the buffer
 * stale. In that हाल, flush completions are run from the buffer unpin call,
 * which may happen beक्रमe the inode is unpinned. If we lose the race, there
 * will be no buffer attached to the log item, but the inode will be marked
 * XFS_ISTALE.
 */
STATIC व्योम
xfs_inode_item_unpin(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			हटाओ)
अणु
	काष्ठा xfs_inode	*ip = INODE_ITEM(lip)->ili_inode;

	trace_xfs_inode_unpin(ip, _RET_IP_);
	ASSERT(lip->li_buf || xfs_अगरlags_test(ip, XFS_ISTALE));
	ASSERT(atomic_पढ़ो(&ip->i_pincount) > 0);
	अगर (atomic_dec_and_test(&ip->i_pincount))
		wake_up_bit(&ip->i_flags, __XFS_IPINNED_BIT);
पूर्ण

STATIC uपूर्णांक
xfs_inode_item_push(
	काष्ठा xfs_log_item	*lip,
	काष्ठा list_head	*buffer_list)
		__releases(&lip->li_ailp->ail_lock)
		__acquires(&lip->li_ailp->ail_lock)
अणु
	काष्ठा xfs_inode_log_item *iip = INODE_ITEM(lip);
	काष्ठा xfs_inode	*ip = iip->ili_inode;
	काष्ठा xfs_buf		*bp = lip->li_buf;
	uपूर्णांक			rval = XFS_ITEM_SUCCESS;
	पूर्णांक			error;

	ASSERT(iip->ili_item.li_buf);

	अगर (xfs_ipincount(ip) > 0 || xfs_buf_ispinned(bp) ||
	    (ip->i_flags & XFS_ISTALE))
		वापस XFS_ITEM_PINNED;

	अगर (xfs_अगरlags_test(ip, XFS_IFLUSHING))
		वापस XFS_ITEM_FLUSHING;

	अगर (!xfs_buf_trylock(bp))
		वापस XFS_ITEM_LOCKED;

	spin_unlock(&lip->li_ailp->ail_lock);

	/*
	 * We need to hold a reference क्रम flushing the cluster buffer as it may
	 * fail the buffer without IO submission. In which हाल, we better get a
	 * reference क्रम that completion because otherwise we करोn't get a
	 * reference क्रम IO until we queue the buffer क्रम delwri submission.
	 */
	xfs_buf_hold(bp);
	error = xfs_अगरlush_cluster(bp);
	अगर (!error) अणु
		अगर (!xfs_buf_delwri_queue(bp, buffer_list))
			rval = XFS_ITEM_FLUSHING;
		xfs_buf_rअन्यथा(bp);
	पूर्ण अन्यथा अणु
		/*
		 * Release the buffer अगर we were unable to flush anything. On
		 * any other error, the buffer has alपढ़ोy been released.
		 */
		अगर (error == -EAGAIN)
			xfs_buf_rअन्यथा(bp);
		rval = XFS_ITEM_LOCKED;
	पूर्ण

	spin_lock(&lip->li_ailp->ail_lock);
	वापस rval;
पूर्ण

/*
 * Unlock the inode associated with the inode log item.
 */
STATIC व्योम
xfs_inode_item_release(
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_inode_log_item *iip = INODE_ITEM(lip);
	काष्ठा xfs_inode	*ip = iip->ili_inode;
	अचिन्हित लघु		lock_flags;

	ASSERT(ip->i_itemp != शून्य);
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	lock_flags = iip->ili_lock_flags;
	iip->ili_lock_flags = 0;
	अगर (lock_flags)
		xfs_iunlock(ip, lock_flags);
पूर्ण

/*
 * This is called to find out where the oldest active copy of the inode log
 * item in the on disk log resides now that the last log ग_लिखो of it completed
 * at the given lsn.  Since we always re-log all dirty data in an inode, the
 * latest copy in the on disk log is the only one that matters.  Thereक्रमe,
 * simply वापस the given lsn.
 *
 * If the inode has been marked stale because the cluster is being मुक्तd, we
 * करोn't want to (re-)insert this inode पूर्णांकo the AIL. There is a race condition
 * where the cluster buffer may be unpinned beक्रमe the inode is inserted पूर्णांकo
 * the AIL during transaction committed processing. If the buffer is unpinned
 * beक्रमe the inode item has been committed and inserted, then it is possible
 * क्रम the buffer to be written and IO completes beक्रमe the inode is inserted
 * पूर्णांकo the AIL. In that हाल, we'd be inserting a clean, stale inode पूर्णांकo the
 * AIL which will never get हटाओd. It will, however, get reclaimed which
 * triggers an निश्चित in xfs_inode_मुक्त() complaining about मुक्तin an inode
 * still in the AIL.
 *
 * To aव्योम this, just unpin the inode directly and वापस a LSN of -1 so the
 * transaction committed code knows that it करोes not need to करो any further
 * processing on the item.
 */
STATIC xfs_lsn_t
xfs_inode_item_committed(
	काष्ठा xfs_log_item	*lip,
	xfs_lsn_t		lsn)
अणु
	काष्ठा xfs_inode_log_item *iip = INODE_ITEM(lip);
	काष्ठा xfs_inode	*ip = iip->ili_inode;

	अगर (xfs_अगरlags_test(ip, XFS_ISTALE)) अणु
		xfs_inode_item_unpin(lip, 0);
		वापस -1;
	पूर्ण
	वापस lsn;
पूर्ण

STATIC व्योम
xfs_inode_item_committing(
	काष्ठा xfs_log_item	*lip,
	xfs_lsn_t		commit_lsn)
अणु
	INODE_ITEM(lip)->ili_last_lsn = commit_lsn;
	वापस xfs_inode_item_release(lip);
पूर्ण

अटल स्थिर काष्ठा xfs_item_ops xfs_inode_item_ops = अणु
	.iop_size	= xfs_inode_item_size,
	.iop_क्रमmat	= xfs_inode_item_क्रमmat,
	.iop_pin	= xfs_inode_item_pin,
	.iop_unpin	= xfs_inode_item_unpin,
	.iop_release	= xfs_inode_item_release,
	.iop_committed	= xfs_inode_item_committed,
	.iop_push	= xfs_inode_item_push,
	.iop_committing	= xfs_inode_item_committing,
पूर्ण;


/*
 * Initialize the inode log item क्रम a newly allocated (in-core) inode.
 */
व्योम
xfs_inode_item_init(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_inode_log_item *iip;

	ASSERT(ip->i_itemp == शून्य);
	iip = ip->i_itemp = kmem_cache_zalloc(xfs_ili_zone,
					      GFP_KERNEL | __GFP_NOFAIL);

	iip->ili_inode = ip;
	spin_lock_init(&iip->ili_lock);
	xfs_log_item_init(mp, &iip->ili_item, XFS_LI_INODE,
						&xfs_inode_item_ops);
पूर्ण

/*
 * Free the inode log item and any memory hanging off of it.
 */
व्योम
xfs_inode_item_destroy(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_inode_log_item *iip = ip->i_itemp;

	ASSERT(iip->ili_item.li_buf == शून्य);

	ip->i_itemp = शून्य;
	kmem_मुक्त(iip->ili_item.li_lv_shaकरोw);
	kmem_cache_मुक्त(xfs_ili_zone, iip);
पूर्ण


/*
 * We only want to pull the item from the AIL अगर it is actually there
 * and its location in the log has not changed since we started the
 * flush.  Thus, we only bother अगर the inode's lsn has not changed.
 */
अटल व्योम
xfs_अगरlush_ail_updates(
	काष्ठा xfs_ail		*ailp,
	काष्ठा list_head	*list)
अणु
	काष्ठा xfs_log_item	*lip;
	xfs_lsn_t		tail_lsn = 0;

	/* this is an खोलोcoded batch version of xfs_trans_ail_delete */
	spin_lock(&ailp->ail_lock);
	list_क्रम_each_entry(lip, list, li_bio_list) अणु
		xfs_lsn_t	lsn;

		clear_bit(XFS_LI_FAILED, &lip->li_flags);
		अगर (INODE_ITEM(lip)->ili_flush_lsn != lip->li_lsn)
			जारी;

		lsn = xfs_ail_delete_one(ailp, lip);
		अगर (!tail_lsn && lsn)
			tail_lsn = lsn;
	पूर्ण
	xfs_ail_update_finish(ailp, tail_lsn);
पूर्ण

/*
 * Walk the list of inodes that have completed their IOs. If they are clean
 * हटाओ them from the list and dissociate them from the buffer. Buffers that
 * are still dirty reमुख्य linked to the buffer and on the list. Caller must
 * handle them appropriately.
 */
अटल व्योम
xfs_अगरlush_finish(
	काष्ठा xfs_buf		*bp,
	काष्ठा list_head	*list)
अणु
	काष्ठा xfs_log_item	*lip, *n;

	list_क्रम_each_entry_safe(lip, n, list, li_bio_list) अणु
		काष्ठा xfs_inode_log_item *iip = INODE_ITEM(lip);
		bool	drop_buffer = false;

		spin_lock(&iip->ili_lock);

		/*
		 * Remove the reference to the cluster buffer अगर the inode is
		 * clean in memory and drop the buffer reference once we've
		 * dropped the locks we hold.
		 */
		ASSERT(iip->ili_item.li_buf == bp);
		अगर (!iip->ili_fields) अणु
			iip->ili_item.li_buf = शून्य;
			list_del_init(&lip->li_bio_list);
			drop_buffer = true;
		पूर्ण
		iip->ili_last_fields = 0;
		iip->ili_flush_lsn = 0;
		spin_unlock(&iip->ili_lock);
		xfs_अगरlags_clear(iip->ili_inode, XFS_IFLUSHING);
		अगर (drop_buffer)
			xfs_buf_rele(bp);
	पूर्ण
पूर्ण

/*
 * Inode buffer IO completion routine.  It is responsible क्रम removing inodes
 * attached to the buffer from the AIL अगर they have not been re-logged and
 * completing the inode flush.
 */
व्योम
xfs_buf_inode_ioकरोne(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_log_item	*lip, *n;
	LIST_HEAD(flushed_inodes);
	LIST_HEAD(ail_updates);

	/*
	 * Pull the attached inodes from the buffer one at a समय and take the
	 * appropriate action on them.
	 */
	list_क्रम_each_entry_safe(lip, n, &bp->b_li_list, li_bio_list) अणु
		काष्ठा xfs_inode_log_item *iip = INODE_ITEM(lip);

		अगर (xfs_अगरlags_test(iip->ili_inode, XFS_ISTALE)) अणु
			xfs_अगरlush_पात(iip->ili_inode);
			जारी;
		पूर्ण
		अगर (!iip->ili_last_fields)
			जारी;

		/* Do an unlocked check क्रम needing the AIL lock. */
		अगर (iip->ili_flush_lsn == lip->li_lsn ||
		    test_bit(XFS_LI_FAILED, &lip->li_flags))
			list_move_tail(&lip->li_bio_list, &ail_updates);
		अन्यथा
			list_move_tail(&lip->li_bio_list, &flushed_inodes);
	पूर्ण

	अगर (!list_empty(&ail_updates)) अणु
		xfs_अगरlush_ail_updates(bp->b_mount->m_ail, &ail_updates);
		list_splice_tail(&ail_updates, &flushed_inodes);
	पूर्ण

	xfs_अगरlush_finish(bp, &flushed_inodes);
	अगर (!list_empty(&flushed_inodes))
		list_splice_tail(&flushed_inodes, &bp->b_li_list);
पूर्ण

व्योम
xfs_buf_inode_io_fail(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_log_item	*lip;

	list_क्रम_each_entry(lip, &bp->b_li_list, li_bio_list)
		set_bit(XFS_LI_FAILED, &lip->li_flags);
पूर्ण

/*
 * This is the inode flushing पात routine.  It is called when
 * the fileप्रणाली is shutting करोwn to clean up the inode state.  It is
 * responsible क्रम removing the inode item from the AIL अगर it has not been
 * re-logged and clearing the inode's flush state.
 */
व्योम
xfs_अगरlush_पात(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_inode_log_item *iip = ip->i_itemp;
	काष्ठा xfs_buf		*bp = शून्य;

	अगर (iip) अणु
		/*
		 * Clear the failed bit beक्रमe removing the item from the AIL so
		 * xfs_trans_ail_delete() करोesn't try to clear and release the
		 * buffer attached to the log item beक्रमe we are करोne with it.
		 */
		clear_bit(XFS_LI_FAILED, &iip->ili_item.li_flags);
		xfs_trans_ail_delete(&iip->ili_item, 0);

		/*
		 * Clear the inode logging fields so no more flushes are
		 * attempted.
		 */
		spin_lock(&iip->ili_lock);
		iip->ili_last_fields = 0;
		iip->ili_fields = 0;
		iip->ili_fsync_fields = 0;
		iip->ili_flush_lsn = 0;
		bp = iip->ili_item.li_buf;
		iip->ili_item.li_buf = शून्य;
		list_del_init(&iip->ili_item.li_bio_list);
		spin_unlock(&iip->ili_lock);
	पूर्ण
	xfs_अगरlags_clear(ip, XFS_IFLUSHING);
	अगर (bp)
		xfs_buf_rele(bp);
पूर्ण

/*
 * convert an xfs_inode_log_क्रमmat काष्ठा from the old 32 bit version
 * (which can have dअगरferent field alignments) to the native 64 bit version
 */
पूर्णांक
xfs_inode_item_क्रमmat_convert(
	काष्ठा xfs_log_iovec		*buf,
	काष्ठा xfs_inode_log_क्रमmat	*in_f)
अणु
	काष्ठा xfs_inode_log_क्रमmat_32	*in_f32 = buf->i_addr;

	अगर (buf->i_len != माप(*in_f32)) अणु
		XFS_ERROR_REPORT(__func__, XFS_ERRLEVEL_LOW, शून्य);
		वापस -EFSCORRUPTED;
	पूर्ण

	in_f->ilf_type = in_f32->ilf_type;
	in_f->ilf_size = in_f32->ilf_size;
	in_f->ilf_fields = in_f32->ilf_fields;
	in_f->ilf_asize = in_f32->ilf_asize;
	in_f->ilf_dsize = in_f32->ilf_dsize;
	in_f->ilf_ino = in_f32->ilf_ino;
	स_नकल(&in_f->ilf_u, &in_f32->ilf_u, माप(in_f->ilf_u));
	in_f->ilf_blkno = in_f32->ilf_blkno;
	in_f->ilf_len = in_f32->ilf_len;
	in_f->ilf_boffset = in_f32->ilf_boffset;
	वापस 0;
पूर्ण
