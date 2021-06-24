<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_SCRUB_REPAIR_H__
#घोषणा __XFS_SCRUB_REPAIR_H__

#समावेश "xfs_quota_defs.h"

अटल अंतरभूत पूर्णांक xrep_notsupported(काष्ठा xfs_scrub *sc)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

#अगर_घोषित CONFIG_XFS_ONLINE_REPAIR

/* Repair helpers */

पूर्णांक xrep_attempt(काष्ठा xfs_scrub *sc);
व्योम xrep_failure(काष्ठा xfs_mount *mp);
पूर्णांक xrep_roll_ag_trans(काष्ठा xfs_scrub *sc);
bool xrep_ag_has_space(काष्ठा xfs_perag *pag, xfs_extlen_t nr_blocks,
		क्रमागत xfs_ag_resv_type type);
xfs_extlen_t xrep_calc_ag_resblks(काष्ठा xfs_scrub *sc);
पूर्णांक xrep_alloc_ag_block(काष्ठा xfs_scrub *sc,
		स्थिर काष्ठा xfs_owner_info *oinfo, xfs_fsblock_t *fsbno,
		क्रमागत xfs_ag_resv_type resv);
पूर्णांक xrep_init_btblock(काष्ठा xfs_scrub *sc, xfs_fsblock_t fsb,
		काष्ठा xfs_buf **bpp, xfs_btnum_t btnum,
		स्थिर काष्ठा xfs_buf_ops *ops);

काष्ठा xbiपंचांगap;

पूर्णांक xrep_fix_मुक्तlist(काष्ठा xfs_scrub *sc, bool can_shrink);
पूर्णांक xrep_invalidate_blocks(काष्ठा xfs_scrub *sc, काष्ठा xbiपंचांगap *btlist);
पूर्णांक xrep_reap_extents(काष्ठा xfs_scrub *sc, काष्ठा xbiपंचांगap *exlist,
		स्थिर काष्ठा xfs_owner_info *oinfo, क्रमागत xfs_ag_resv_type type);

काष्ठा xrep_find_ag_btree अणु
	/* in: rmap owner of the btree we're looking क्रम */
	uपूर्णांक64_t			rmap_owner;

	/* in: buffer ops */
	स्थिर काष्ठा xfs_buf_ops	*buf_ops;

	/* out: the highest btree block found and the tree height */
	xfs_agblock_t			root;
	अचिन्हित पूर्णांक			height;
पूर्ण;

पूर्णांक xrep_find_ag_btree_roots(काष्ठा xfs_scrub *sc, काष्ठा xfs_buf *agf_bp,
		काष्ठा xrep_find_ag_btree *btree_info, काष्ठा xfs_buf *agfl_bp);
व्योम xrep_क्रमce_quotacheck(काष्ठा xfs_scrub *sc, xfs_dqtype_t type);
पूर्णांक xrep_ino_dqattach(काष्ठा xfs_scrub *sc);

/* Metadata repairers */

पूर्णांक xrep_probe(काष्ठा xfs_scrub *sc);
पूर्णांक xrep_superblock(काष्ठा xfs_scrub *sc);
पूर्णांक xrep_agf(काष्ठा xfs_scrub *sc);
पूर्णांक xrep_agfl(काष्ठा xfs_scrub *sc);
पूर्णांक xrep_agi(काष्ठा xfs_scrub *sc);

#अन्यथा

अटल अंतरभूत पूर्णांक
xrep_attempt(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम xrep_failure(काष्ठा xfs_mount *mp) अणुपूर्ण

अटल अंतरभूत xfs_extlen_t
xrep_calc_ag_resblks(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस 0;
पूर्ण

#घोषणा xrep_probe			xrep_notsupported
#घोषणा xrep_superblock			xrep_notsupported
#घोषणा xrep_agf			xrep_notsupported
#घोषणा xrep_agfl			xrep_notsupported
#घोषणा xrep_agi			xrep_notsupported

#पूर्ण_अगर /* CONFIG_XFS_ONLINE_REPAIR */

#पूर्ण_अगर	/* __XFS_SCRUB_REPAIR_H__ */
