<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __DIO_DOT_H__
#घोषणा __DIO_DOT_H__

#समावेश <linux/buffer_head.h>
#समावेश <linux/माला.स>
#समावेश "incore.h"

अटल अंतरभूत व्योम gfs2_buffer_clear(काष्ठा buffer_head *bh)
अणु
	स_रखो(bh->b_data, 0, bh->b_size);
पूर्ण

अटल अंतरभूत व्योम gfs2_buffer_clear_tail(काष्ठा buffer_head *bh, पूर्णांक head)
अणु
	BUG_ON(head > bh->b_size);
	स_रखो(bh->b_data + head, 0, bh->b_size - head);
पूर्ण

अटल अंतरभूत व्योम gfs2_buffer_copy_tail(काष्ठा buffer_head *to_bh,
					 पूर्णांक to_head,
					 काष्ठा buffer_head *from_bh,
					 पूर्णांक from_head)
अणु
	BUG_ON(from_head < to_head);
	स_नकल(to_bh->b_data + to_head, from_bh->b_data + from_head,
	       from_bh->b_size - from_head);
	स_रखो(to_bh->b_data + to_bh->b_size + to_head - from_head,
	       0, from_head - to_head);
पूर्ण

बाह्य स्थिर काष्ठा address_space_operations gfs2_meta_aops;
बाह्य स्थिर काष्ठा address_space_operations gfs2_rgrp_aops;

अटल अंतरभूत काष्ठा gfs2_sbd *gfs2_mapping2sbd(काष्ठा address_space *mapping)
अणु
	काष्ठा inode *inode = mapping->host;
	अगर (mapping->a_ops == &gfs2_meta_aops)
		वापस (((काष्ठा gfs2_glock *)mapping) - 1)->gl_name.ln_sbd;
	अन्यथा अगर (mapping->a_ops == &gfs2_rgrp_aops)
		वापस container_of(mapping, काष्ठा gfs2_sbd, sd_aspace);
	अन्यथा
		वापस inode->i_sb->s_fs_info;
पूर्ण

बाह्य काष्ठा buffer_head *gfs2_meta_new(काष्ठा gfs2_glock *gl, u64 blkno);
बाह्य पूर्णांक gfs2_meta_पढ़ो(काष्ठा gfs2_glock *gl, u64 blkno, पूर्णांक flags,
			  पूर्णांक rahead, काष्ठा buffer_head **bhp);
बाह्य पूर्णांक gfs2_meta_रुको(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *bh);
बाह्य काष्ठा buffer_head *gfs2_getbuf(काष्ठा gfs2_glock *gl, u64 blkno,
				       पूर्णांक create);
क्रमागत अणु
	REMOVE_JDATA = 0,
	REMOVE_META = 1,
पूर्ण;

बाह्य व्योम gfs2_हटाओ_from_journal(काष्ठा buffer_head *bh, पूर्णांक meta);
बाह्य व्योम gfs2_journal_wipe(काष्ठा gfs2_inode *ip, u64 bstart, u32 blen);
बाह्य पूर्णांक gfs2_meta_buffer(काष्ठा gfs2_inode *ip, u32 mtype, u64 num,
			    काष्ठा buffer_head **bhp);

अटल अंतरभूत पूर्णांक gfs2_meta_inode_buffer(काष्ठा gfs2_inode *ip,
					 काष्ठा buffer_head **bhp)
अणु
	वापस gfs2_meta_buffer(ip, GFS2_METATYPE_DI, ip->i_no_addr, bhp);
पूर्ण

काष्ठा buffer_head *gfs2_meta_ra(काष्ठा gfs2_glock *gl, u64 dblock, u32 extlen);

#घोषणा buffer_busy(bh) \
((bh)->b_state & ((1ul << BH_Dirty) | (1ul << BH_Lock) | (1ul << BH_Pinned)))

#पूर्ण_अगर /* __DIO_DOT_H__ */

