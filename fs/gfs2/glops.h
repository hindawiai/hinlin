<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __GLOPS_DOT_H__
#घोषणा __GLOPS_DOT_H__

#समावेश "incore.h"

बाह्य काष्ठा workqueue_काष्ठा *gfs2_मुक्तze_wq;

बाह्य स्थिर काष्ठा gfs2_glock_operations gfs2_meta_glops;
बाह्य स्थिर काष्ठा gfs2_glock_operations gfs2_inode_glops;
बाह्य स्थिर काष्ठा gfs2_glock_operations gfs2_rgrp_glops;
बाह्य स्थिर काष्ठा gfs2_glock_operations gfs2_मुक्तze_glops;
बाह्य स्थिर काष्ठा gfs2_glock_operations gfs2_iखोलो_glops;
बाह्य स्थिर काष्ठा gfs2_glock_operations gfs2_flock_glops;
बाह्य स्थिर काष्ठा gfs2_glock_operations gfs2_nondisk_glops;
बाह्य स्थिर काष्ठा gfs2_glock_operations gfs2_quota_glops;
बाह्य स्थिर काष्ठा gfs2_glock_operations gfs2_journal_glops;
बाह्य स्थिर काष्ठा gfs2_glock_operations *gfs2_glops_list[];

बाह्य पूर्णांक gfs2_inode_metasync(काष्ठा gfs2_glock *gl);
बाह्य व्योम gfs2_ail_flush(काष्ठा gfs2_glock *gl, bool fsync);

#पूर्ण_अगर /* __GLOPS_DOT_H__ */
