<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __SUPER_DOT_H__
#घोषणा __SUPER_DOT_H__

#समावेश <linux/fs.h>
#समावेश <linux/dcache.h>
#समावेश "incore.h"

/* Supported fs क्रमmat version range */
#घोषणा GFS2_FS_FORMAT_MIN (1801)
#घोषणा GFS2_FS_FORMAT_MAX (1802)

बाह्य व्योम gfs2_lm_unmount(काष्ठा gfs2_sbd *sdp);

अटल अंतरभूत अचिन्हित पूर्णांक gfs2_jindex_size(काष्ठा gfs2_sbd *sdp)
अणु
	अचिन्हित पूर्णांक x;
	spin_lock(&sdp->sd_jindex_spin);
	x = sdp->sd_journals;
	spin_unlock(&sdp->sd_jindex_spin);
	वापस x;
पूर्ण

बाह्य व्योम gfs2_jindex_मुक्त(काष्ठा gfs2_sbd *sdp);

बाह्य काष्ठा gfs2_jdesc *gfs2_jdesc_find(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक jid);
बाह्य पूर्णांक gfs2_jdesc_check(काष्ठा gfs2_jdesc *jd);
बाह्य पूर्णांक gfs2_lookup_in_master_dir(काष्ठा gfs2_sbd *sdp, अक्षर *filename,
				     काष्ठा gfs2_inode **ipp);

बाह्य पूर्णांक gfs2_make_fs_rw(काष्ठा gfs2_sbd *sdp);
बाह्य व्योम gfs2_make_fs_ro(काष्ठा gfs2_sbd *sdp);
बाह्य व्योम gfs2_online_uevent(काष्ठा gfs2_sbd *sdp);
बाह्य पूर्णांक gfs2_statfs_init(काष्ठा gfs2_sbd *sdp);
बाह्य व्योम gfs2_statfs_change(काष्ठा gfs2_sbd *sdp, s64 total, s64 मुक्त,
			       s64 dinodes);
बाह्य व्योम gfs2_statfs_change_in(काष्ठा gfs2_statfs_change_host *sc,
				  स्थिर व्योम *buf);
बाह्य व्योम gfs2_statfs_change_out(स्थिर काष्ठा gfs2_statfs_change_host *sc,
				   व्योम *buf);
बाह्य व्योम update_statfs(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *m_bh,
			  काष्ठा buffer_head *l_bh);
बाह्य पूर्णांक gfs2_statfs_sync(काष्ठा super_block *sb, पूर्णांक type);
बाह्य व्योम gfs2_मुक्तze_func(काष्ठा work_काष्ठा *work);

बाह्य व्योम मुक्त_local_statfs_inodes(काष्ठा gfs2_sbd *sdp);
बाह्य काष्ठा inode *find_local_statfs_inode(काष्ठा gfs2_sbd *sdp,
					     अचिन्हित पूर्णांक index);
बाह्य व्योम मुक्त_sbd(काष्ठा gfs2_sbd *sdp);

बाह्य काष्ठा file_प्रणाली_type gfs2_fs_type;
बाह्य काष्ठा file_प्रणाली_type gfs2meta_fs_type;
बाह्य स्थिर काष्ठा export_operations gfs2_export_ops;
बाह्य स्थिर काष्ठा super_operations gfs2_super_ops;
बाह्य स्थिर काष्ठा dentry_operations gfs2_करोps;

बाह्य स्थिर काष्ठा xattr_handler *gfs2_xattr_handlers_max[];
बाह्य स्थिर काष्ठा xattr_handler **gfs2_xattr_handlers_min;

#पूर्ण_अगर /* __SUPER_DOT_H__ */

