<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __TRANS_DOT_H__
#घोषणा __TRANS_DOT_H__

#समावेश <linux/buffer_head.h>
काष्ठा gfs2_sbd;
काष्ठा gfs2_rgrpd;
काष्ठा gfs2_glock;

#घोषणा RES_DINODE	1
#घोषणा RES_INसूचीECT	1
#घोषणा RES_JDATA	1
#घोषणा RES_DATA	1
#घोषणा RES_LEAF	1
#घोषणा RES_RG_HDR	1
#घोषणा RES_RG_BIT	2
#घोषणा RES_EATTR	1
#घोषणा RES_STATFS	1
#घोषणा RES_QUOTA	2

/* reserve either the number of blocks to be allocated plus the rg header
 * block, or all of the blocks in the rg, whichever is smaller */
अटल अंतरभूत अचिन्हित पूर्णांक gfs2_rg_blocks(स्थिर काष्ठा gfs2_inode *ip, अचिन्हित requested)
अणु
	काष्ठा gfs2_rgrpd *rgd = ip->i_res.rs_rgd;

	अगर (requested < rgd->rd_length)
		वापस requested + 1;
	वापस rgd->rd_length;
पूर्ण

बाह्य पूर्णांक __gfs2_trans_begin(काष्ठा gfs2_trans *tr, काष्ठा gfs2_sbd *sdp,
			      अचिन्हित पूर्णांक blocks, अचिन्हित पूर्णांक revokes,
			      अचिन्हित दीर्घ ip);
बाह्य पूर्णांक gfs2_trans_begin(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक blocks,
			    अचिन्हित पूर्णांक revokes);

बाह्य व्योम gfs2_trans_end(काष्ठा gfs2_sbd *sdp);
बाह्य व्योम gfs2_trans_add_data(काष्ठा gfs2_glock *gl, काष्ठा buffer_head *bh);
बाह्य व्योम gfs2_trans_add_meta(काष्ठा gfs2_glock *gl, काष्ठा buffer_head *bh);
बाह्य व्योम gfs2_trans_add_revoke(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_bufdata *bd);
बाह्य व्योम gfs2_trans_हटाओ_revoke(काष्ठा gfs2_sbd *sdp, u64 blkno, अचिन्हित पूर्णांक len);
बाह्य व्योम gfs2_trans_मुक्त(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr);

#पूर्ण_अगर /* __TRANS_DOT_H__ */
