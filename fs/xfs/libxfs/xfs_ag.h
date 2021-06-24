<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018 Red Hat, Inc.
 * All rights reserved.
 */

#अगर_अघोषित __LIBXFS_AG_H
#घोषणा __LIBXFS_AG_H 1

काष्ठा xfs_mount;
काष्ठा xfs_trans;

काष्ठा aghdr_init_data अणु
	/* per ag data */
	xfs_agblock_t		agno;		/* ag to init */
	xfs_extlen_t		agsize;		/* new AG size */
	काष्ठा list_head	buffer_list;	/* buffer ग_लिखोback list */
	xfs_rfsblock_t		nमुक्त;		/* cumulative new मुक्त space */

	/* per header data */
	xfs_daddr_t		daddr;		/* header location */
	माप_प्रकार			numblks;	/* size of header */
	xfs_btnum_t		type;		/* type of btree root block */
पूर्ण;

पूर्णांक xfs_ag_init_headers(काष्ठा xfs_mount *mp, काष्ठा aghdr_init_data *id);
पूर्णांक xfs_ag_shrink_space(काष्ठा xfs_mount *mp, काष्ठा xfs_trans **tpp,
			xfs_agnumber_t agno, xfs_extlen_t delta);
पूर्णांक xfs_ag_extend_space(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
			काष्ठा aghdr_init_data *id, xfs_extlen_t len);
पूर्णांक xfs_ag_get_geometry(काष्ठा xfs_mount *mp, xfs_agnumber_t agno,
			काष्ठा xfs_ag_geometry *ageo);

#पूर्ण_अगर /* __LIBXFS_AG_H */
