<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_SCRUB_BITMAP_H__
#घोषणा __XFS_SCRUB_BITMAP_H__

काष्ठा xbiपंचांगap_range अणु
	काष्ठा list_head	list;
	uपूर्णांक64_t		start;
	uपूर्णांक64_t		len;
पूर्ण;

काष्ठा xbiपंचांगap अणु
	काष्ठा list_head	list;
पूर्ण;

व्योम xbiपंचांगap_init(काष्ठा xbiपंचांगap *biपंचांगap);
व्योम xbiपंचांगap_destroy(काष्ठा xbiपंचांगap *biपंचांगap);

#घोषणा क्रम_each_xbiपंचांगap_extent(bex, n, biपंचांगap) \
	list_क्रम_each_entry_safe((bex), (n), &(biपंचांगap)->list, list)

#घोषणा क्रम_each_xbiपंचांगap_block(b, bex, n, biपंचांगap) \
	list_क्रम_each_entry_safe((bex), (n), &(biपंचांगap)->list, list) \
		क्रम ((b) = (bex)->start; (b) < (bex)->start + (bex)->len; (b)++)

पूर्णांक xbiपंचांगap_set(काष्ठा xbiपंचांगap *biपंचांगap, uपूर्णांक64_t start, uपूर्णांक64_t len);
पूर्णांक xbiपंचांगap_disजोड़(काष्ठा xbiपंचांगap *biपंचांगap, काष्ठा xbiपंचांगap *sub);
पूर्णांक xbiपंचांगap_set_btcur_path(काष्ठा xbiपंचांगap *biपंचांगap,
		काष्ठा xfs_btree_cur *cur);
पूर्णांक xbiपंचांगap_set_btblocks(काष्ठा xbiपंचांगap *biपंचांगap,
		काष्ठा xfs_btree_cur *cur);
uपूर्णांक64_t xbiपंचांगap_hweight(काष्ठा xbiपंचांगap *biपंचांगap);

#पूर्ण_अगर	/* __XFS_SCRUB_BITMAP_H__ */
