<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2008 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __RGRP_DOT_H__
#घोषणा __RGRP_DOT_H__

#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

/* Since each block in the file प्रणाली is represented by two bits in the
 * biपंचांगap, one 64-bit word in the biपंचांगap will represent 32 blocks.
 * By reserving 32 blocks at a समय, we can optimize / लघुcut how we search
 * through the biपंचांगaps by looking a word at a समय.
 */
#घोषणा RGRP_RSRV_MINBLKS 32
#घोषणा RGRP_RSRV_ADDBLKS 64

काष्ठा gfs2_rgrpd;
काष्ठा gfs2_sbd;
काष्ठा gfs2_holder;

बाह्य व्योम gfs2_rgrp_verअगरy(काष्ठा gfs2_rgrpd *rgd);

बाह्य काष्ठा gfs2_rgrpd *gfs2_blk2rgrpd(काष्ठा gfs2_sbd *sdp, u64 blk, bool exact);
बाह्य काष्ठा gfs2_rgrpd *gfs2_rgrpd_get_first(काष्ठा gfs2_sbd *sdp);
बाह्य काष्ठा gfs2_rgrpd *gfs2_rgrpd_get_next(काष्ठा gfs2_rgrpd *rgd);

बाह्य व्योम gfs2_clear_rgrpd(काष्ठा gfs2_sbd *sdp);
बाह्य पूर्णांक gfs2_rindex_update(काष्ठा gfs2_sbd *sdp);
बाह्य व्योम gfs2_मुक्त_clones(काष्ठा gfs2_rgrpd *rgd);
बाह्य पूर्णांक gfs2_rgrp_go_lock(काष्ठा gfs2_holder *gh);
बाह्य व्योम gfs2_rgrp_brअन्यथा(काष्ठा gfs2_rgrpd *rgd);

बाह्य काष्ठा gfs2_alloc *gfs2_alloc_get(काष्ठा gfs2_inode *ip);

#घोषणा GFS2_AF_ORLOV 1
बाह्य पूर्णांक gfs2_inplace_reserve(काष्ठा gfs2_inode *ip,
				काष्ठा gfs2_alloc_parms *ap);
बाह्य व्योम gfs2_inplace_release(काष्ठा gfs2_inode *ip);

बाह्य पूर्णांक gfs2_alloc_blocks(काष्ठा gfs2_inode *ip, u64 *bn, अचिन्हित पूर्णांक *n,
			     bool dinode, u64 *generation);

बाह्य व्योम gfs2_rs_deltree(काष्ठा gfs2_blkreserv *rs);
बाह्य व्योम gfs2_rs_delete(काष्ठा gfs2_inode *ip, atomic_t *wcount);
बाह्य व्योम __gfs2_मुक्त_blocks(काष्ठा gfs2_inode *ip, काष्ठा gfs2_rgrpd *rgd,
			       u64 bstart, u32 blen, पूर्णांक meta);
बाह्य व्योम gfs2_मुक्त_meta(काष्ठा gfs2_inode *ip, काष्ठा gfs2_rgrpd *rgd,
			   u64 bstart, u32 blen);
बाह्य व्योम gfs2_मुक्त_di(काष्ठा gfs2_rgrpd *rgd, काष्ठा gfs2_inode *ip);
बाह्य व्योम gfs2_unlink_di(काष्ठा inode *inode);
बाह्य पूर्णांक gfs2_check_blk_type(काष्ठा gfs2_sbd *sdp, u64 no_addr,
			       अचिन्हित पूर्णांक type);

काष्ठा gfs2_rgrp_list अणु
	अचिन्हित पूर्णांक rl_rgrps;
	अचिन्हित पूर्णांक rl_space;
	काष्ठा gfs2_rgrpd **rl_rgd;
	काष्ठा gfs2_holder *rl_ghs;
पूर्ण;

बाह्य व्योम gfs2_rlist_add(काष्ठा gfs2_inode *ip, काष्ठा gfs2_rgrp_list *rlist,
			   u64 block);
बाह्य व्योम gfs2_rlist_alloc(काष्ठा gfs2_rgrp_list *rlist);
बाह्य व्योम gfs2_rlist_मुक्त(काष्ठा gfs2_rgrp_list *rlist);
बाह्य u64 gfs2_ri_total(काष्ठा gfs2_sbd *sdp);
बाह्य व्योम gfs2_rgrp_dump(काष्ठा seq_file *seq, काष्ठा gfs2_rgrpd *rgd,
			   स्थिर अक्षर *fs_id_buf);
बाह्य पूर्णांक gfs2_rgrp_send_discards(काष्ठा gfs2_sbd *sdp, u64 offset,
				   काष्ठा buffer_head *bh,
				   स्थिर काष्ठा gfs2_biपंचांगap *bi, अचिन्हित minlen, u64 *ptrimmed);
बाह्य पूर्णांक gfs2_fitrim(काष्ठा file *filp, व्योम __user *argp);

/* This is how to tell अगर a reservation is in the rgrp tree: */
अटल अंतरभूत bool gfs2_rs_active(स्थिर काष्ठा gfs2_blkreserv *rs)
अणु
	वापस !RB_EMPTY_NODE(&rs->rs_node);
पूर्ण

अटल अंतरभूत पूर्णांक rgrp_contains_block(काष्ठा gfs2_rgrpd *rgd, u64 block)
अणु
	u64 first = rgd->rd_data0;
	u64 last = first + rgd->rd_data;
	वापस first <= block && block < last;
पूर्ण

बाह्य व्योम check_and_update_goal(काष्ठा gfs2_inode *ip);

बाह्य व्योम rgrp_lock_local(काष्ठा gfs2_rgrpd *rgd);
बाह्य व्योम rgrp_unlock_local(काष्ठा gfs2_rgrpd *rgd);

#पूर्ण_अगर /* __RGRP_DOT_H__ */
