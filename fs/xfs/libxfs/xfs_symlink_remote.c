<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * Copyright (c) 2012-2013 Red Hat, Inc.
 * All rights reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_log.h"


/*
 * Each contiguous block has a header, so it is not just a simple pathlen
 * to FSB conversion.
 */
पूर्णांक
xfs_symlink_blocks(
	काष्ठा xfs_mount *mp,
	पूर्णांक		pathlen)
अणु
	पूर्णांक buflen = XFS_SYMLINK_BUF_SPACE(mp, mp->m_sb.sb_blocksize);

	वापस (pathlen + buflen - 1) / buflen;
पूर्ण

पूर्णांक
xfs_symlink_hdr_set(
	काष्ठा xfs_mount	*mp,
	xfs_ino_t		ino,
	uपूर्णांक32_t		offset,
	uपूर्णांक32_t		size,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_dsymlink_hdr	*dsl = bp->b_addr;

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस 0;

	स_रखो(dsl, 0, माप(काष्ठा xfs_dsymlink_hdr));
	dsl->sl_magic = cpu_to_be32(XFS_SYMLINK_MAGIC);
	dsl->sl_offset = cpu_to_be32(offset);
	dsl->sl_bytes = cpu_to_be32(size);
	uuid_copy(&dsl->sl_uuid, &mp->m_sb.sb_meta_uuid);
	dsl->sl_owner = cpu_to_be64(ino);
	dsl->sl_blkno = cpu_to_be64(bp->b_bn);
	bp->b_ops = &xfs_symlink_buf_ops;

	वापस माप(काष्ठा xfs_dsymlink_hdr);
पूर्ण

/*
 * Checking of the symlink header is split पूर्णांकo two parts. the verअगरier करोes
 * CRC, location and bounds checking, the unpacking function checks the path
 * parameters and owner.
 */
bool
xfs_symlink_hdr_ok(
	xfs_ino_t		ino,
	uपूर्णांक32_t		offset,
	uपूर्णांक32_t		size,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_dsymlink_hdr *dsl = bp->b_addr;

	अगर (offset != be32_to_cpu(dsl->sl_offset))
		वापस false;
	अगर (size != be32_to_cpu(dsl->sl_bytes))
		वापस false;
	अगर (ino != be64_to_cpu(dsl->sl_owner))
		वापस false;

	/* ok */
	वापस true;
पूर्ण

अटल xfs_failaddr_t
xfs_symlink_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_dsymlink_hdr	*dsl = bp->b_addr;

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस __this_address;
	अगर (!xfs_verअगरy_magic(bp, dsl->sl_magic))
		वापस __this_address;
	अगर (!uuid_equal(&dsl->sl_uuid, &mp->m_sb.sb_meta_uuid))
		वापस __this_address;
	अगर (bp->b_bn != be64_to_cpu(dsl->sl_blkno))
		वापस __this_address;
	अगर (be32_to_cpu(dsl->sl_offset) +
				be32_to_cpu(dsl->sl_bytes) >= XFS_SYMLINK_MAXLEN)
		वापस __this_address;
	अगर (dsl->sl_owner == 0)
		वापस __this_address;
	अगर (!xfs_log_check_lsn(mp, be64_to_cpu(dsl->sl_lsn)))
		वापस __this_address;

	वापस शून्य;
पूर्ण

अटल व्योम
xfs_symlink_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount *mp = bp->b_mount;
	xfs_failaddr_t	fa;

	/* no verअगरication of non-crc buffers */
	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	अगर (!xfs_buf_verअगरy_cksum(bp, XFS_SYMLINK_CRC_OFF))
		xfs_verअगरier_error(bp, -EFSBADCRC, __this_address);
	अन्यथा अणु
		fa = xfs_symlink_verअगरy(bp);
		अगर (fa)
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
	पूर्ण
पूर्ण

अटल व्योम
xfs_symlink_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount *mp = bp->b_mount;
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;
	xfs_failaddr_t		fa;

	/* no verअगरication of non-crc buffers */
	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	fa = xfs_symlink_verअगरy(bp);
	अगर (fa) अणु
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण

	अगर (bip) अणु
		काष्ठा xfs_dsymlink_hdr *dsl = bp->b_addr;
		dsl->sl_lsn = cpu_to_be64(bip->bli_item.li_lsn);
	पूर्ण
	xfs_buf_update_cksum(bp, XFS_SYMLINK_CRC_OFF);
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_symlink_buf_ops = अणु
	.name = "xfs_symlink",
	.magic = अणु 0, cpu_to_be32(XFS_SYMLINK_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_symlink_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_symlink_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_symlink_verअगरy,
पूर्ण;

व्योम
xfs_symlink_local_to_remote(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*bp,
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_अगरork	*अगरp)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	अक्षर			*buf;

	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_SYMLINK_BUF);

	अगर (!xfs_sb_version_hascrc(&mp->m_sb)) अणु
		bp->b_ops = शून्य;
		स_नकल(bp->b_addr, अगरp->अगर_u1.अगर_data, अगरp->अगर_bytes);
		xfs_trans_log_buf(tp, bp, 0, अगरp->अगर_bytes - 1);
		वापस;
	पूर्ण

	/*
	 * As this symlink fits in an inode literal area, it must also fit in
	 * the smallest buffer the fileप्रणाली supports.
	 */
	ASSERT(BBTOB(bp->b_length) >=
			अगरp->अगर_bytes + माप(काष्ठा xfs_dsymlink_hdr));

	bp->b_ops = &xfs_symlink_buf_ops;

	buf = bp->b_addr;
	buf += xfs_symlink_hdr_set(mp, ip->i_ino, 0, अगरp->अगर_bytes, bp);
	स_नकल(buf, अगरp->अगर_u1.अगर_data, अगरp->अगर_bytes);
	xfs_trans_log_buf(tp, bp, 0, माप(काष्ठा xfs_dsymlink_hdr) +
					अगरp->अगर_bytes - 1);
पूर्ण

/*
 * Verअगरy the in-memory consistency of an अंतरभूत symlink data विभाजन. This
 * करोes not करो on-disk क्रमmat checks.
 */
xfs_failaddr_t
xfs_symlink_लघुक्रमm_verअगरy(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, XFS_DATA_FORK);
	अक्षर			*sfp = (अक्षर *)अगरp->अगर_u1.अगर_data;
	पूर्णांक			size = अगरp->अगर_bytes;
	अक्षर			*endp = sfp + size;

	ASSERT(अगरp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);

	/*
	 * Zero length symlinks should never occur in memory as they are
	 * never alllowed to exist on disk.
	 */
	अगर (!size)
		वापस __this_address;

	/* No negative sizes or overly दीर्घ symlink tarमाला_लो. */
	अगर (size < 0 || size > XFS_SYMLINK_MAXLEN)
		वापस __this_address;

	/* No शून्यs in the target either. */
	अगर (स_प्रथम(sfp, 0, size - 1))
		वापस __this_address;

	/* We /did/ null-terminate the buffer, right? */
	अगर (*endp != 0)
		वापस __this_address;
	वापस शून्य;
पूर्ण
