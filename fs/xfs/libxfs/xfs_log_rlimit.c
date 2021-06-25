<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2013 Jie Liu.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_da_format.h"
#समावेश "xfs_trans_space.h"
#समावेश "xfs_da_btree.h"
#समावेश "xfs_bmap_btree.h"

/*
 * Calculate the maximum length in bytes that would be required क्रम a local
 * attribute value as large attributes out of line are not logged.
 */
STATIC पूर्णांक
xfs_log_calc_max_attrseपंचांग_res(
	काष्ठा xfs_mount	*mp)
अणु
	पूर्णांक			size;
	पूर्णांक			nblks;

	size = xfs_attr_leaf_entsize_local_max(mp->m_attr_geo->blksize) -
	       MAXNAMELEN - 1;
	nblks = XFS_DAENTER_SPACE_RES(mp, XFS_ATTR_FORK);
	nblks += XFS_B_TO_FSB(mp, size);
	nblks += XFS_NEXTENTADD_SPACE_RES(mp, size, XFS_ATTR_FORK);

	वापस  M_RES(mp)->tr_attrseपंचांग.tr_logres +
		M_RES(mp)->tr_attrsetrt.tr_logres * nblks;
पूर्ण

/*
 * Iterate over the log space reservation table to figure out and वापस
 * the maximum one in terms of the pre-calculated values which were करोne
 * at mount समय.
 */
व्योम
xfs_log_get_max_trans_res(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans_res	*max_resp)
अणु
	काष्ठा xfs_trans_res	*resp;
	काष्ठा xfs_trans_res	*end_resp;
	पूर्णांक			log_space = 0;
	पूर्णांक			attr_space;

	attr_space = xfs_log_calc_max_attrseपंचांग_res(mp);

	resp = (काष्ठा xfs_trans_res *)M_RES(mp);
	end_resp = (काष्ठा xfs_trans_res *)(M_RES(mp) + 1);
	क्रम (; resp < end_resp; resp++) अणु
		पूर्णांक		पंचांगp = resp->tr_logcount > 1 ?
				      resp->tr_logres * resp->tr_logcount :
				      resp->tr_logres;
		अगर (log_space < पंचांगp) अणु
			log_space = पंचांगp;
			*max_resp = *resp;		/* काष्ठा copy */
		पूर्ण
	पूर्ण

	अगर (attr_space > log_space) अणु
		*max_resp = M_RES(mp)->tr_attrseपंचांग;	/* काष्ठा copy */
		max_resp->tr_logres = attr_space;
	पूर्ण
पूर्ण

/*
 * Calculate the minimum valid log size क्रम the given superblock configuration.
 * Used to calculate the minimum log size at mkfs समय, and to determine अगर
 * the log is large enough or not at mount समय. Returns the minimum size in
 * fileप्रणाली block size units.
 */
पूर्णांक
xfs_log_calc_minimum_size(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_trans_res	tres = अणु0पूर्ण;
	पूर्णांक			max_logres;
	पूर्णांक			min_logblks = 0;
	पूर्णांक			lsunit = 0;

	xfs_log_get_max_trans_res(mp, &tres);

	max_logres = xfs_log_calc_unit_res(mp, tres.tr_logres);
	अगर (tres.tr_logcount > 1)
		max_logres *= tres.tr_logcount;

	अगर (xfs_sb_version_haslogv2(&mp->m_sb) && mp->m_sb.sb_logsunit > 1)
		lsunit = BTOBB(mp->m_sb.sb_logsunit);

	/*
	 * Two factors should be taken पूर्णांकo account क्रम calculating the minimum
	 * log space.
	 * 1) The fundamental limitation is that no single transaction can be
	 *    larger than half size of the log.
	 *
	 *    From mkfs.xfs, this is considered by the XFS_MIN_LOG_FACTOR
	 *    define, which is set to 3. That means we can definitely fit
	 *    maximally sized 2 transactions in the log. We'll use this same
	 *    value here.
	 *
	 * 2) If the lsunit option is specअगरied, a transaction requires 2 LSU
	 *    क्रम the reservation because there are two log ग_लिखोs that can
	 *    require padding - the transaction data and the commit record which
	 *    are written separately and both can require padding to the LSU.
	 *    Consider that we can have an active CIL reservation holding 2*LSU,
	 *    but the CIL is not over a push threshold, in this हाल, अगर we
	 *    करोn't have enough log space क्रम at one new transaction, which
	 *    includes another 2*LSU in the reservation, we will run पूर्णांकo dead
	 *    loop situation in log space grant procedure. i.e.
	 *    xlog_grant_head_रुको().
	 *
	 *    Hence the log size needs to be able to contain two maximally sized
	 *    and padded transactions, which is (2 * (2 * LSU + maxlres)).
	 *
	 * Also, the log size should be a multiple of the log stripe unit, round
	 * it up to lsunit boundary अगर lsunit is specअगरied.
	 */
	अगर (lsunit) अणु
		min_logblks = roundup_64(BTOBB(max_logres), lsunit) +
			      2 * lsunit;
	पूर्ण अन्यथा
		min_logblks = BTOBB(max_logres) + 2 * BBSIZE;
	min_logblks *= XFS_MIN_LOG_FACTOR;

	वापस XFS_BB_TO_FSB(mp, min_logblks);
पूर्ण
