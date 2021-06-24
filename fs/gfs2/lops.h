<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2008 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __LOPS_DOT_H__
#घोषणा __LOPS_DOT_H__

#समावेश <linux/list.h>
#समावेश "incore.h"

बाह्य स्थिर काष्ठा gfs2_log_operations *gfs2_log_ops[];
बाह्य व्योम gfs2_log_incr_head(काष्ठा gfs2_sbd *sdp);
बाह्य u64 gfs2_log_bmap(काष्ठा gfs2_jdesc *jd, अचिन्हित पूर्णांक lbn);
बाह्य व्योम gfs2_log_ग_लिखो(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_jdesc *jd,
			   काष्ठा page *page, अचिन्हित size, अचिन्हित offset,
			   u64 blkno);
बाह्य व्योम gfs2_log_submit_bio(काष्ठा bio **biop, पूर्णांक opf);
बाह्य व्योम gfs2_pin(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *bh);
बाह्य पूर्णांक gfs2_find_jhead(काष्ठा gfs2_jdesc *jd,
			   काष्ठा gfs2_log_header_host *head, bool keep_cache);
बाह्य व्योम gfs2_drain_revokes(काष्ठा gfs2_sbd *sdp);
अटल अंतरभूत अचिन्हित पूर्णांक buf_limit(काष्ठा gfs2_sbd *sdp)
अणु
	वापस sdp->sd_ldptrs;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक databuf_limit(काष्ठा gfs2_sbd *sdp)
अणु
	वापस sdp->sd_ldptrs / 2;
पूर्ण

अटल अंतरभूत व्योम lops_beक्रमe_commit(काष्ठा gfs2_sbd *sdp,
				      काष्ठा gfs2_trans *tr)
अणु
	पूर्णांक x;
	क्रम (x = 0; gfs2_log_ops[x]; x++)
		अगर (gfs2_log_ops[x]->lo_beक्रमe_commit)
			gfs2_log_ops[x]->lo_beक्रमe_commit(sdp, tr);
पूर्ण

अटल अंतरभूत व्योम lops_after_commit(काष्ठा gfs2_sbd *sdp,
				     काष्ठा gfs2_trans *tr)
अणु
	पूर्णांक x;
	क्रम (x = 0; gfs2_log_ops[x]; x++)
		अगर (gfs2_log_ops[x]->lo_after_commit)
			gfs2_log_ops[x]->lo_after_commit(sdp, tr);
पूर्ण

अटल अंतरभूत व्योम lops_beक्रमe_scan(काष्ठा gfs2_jdesc *jd,
				    काष्ठा gfs2_log_header_host *head,
				    अचिन्हित पूर्णांक pass)
अणु
	पूर्णांक x;
	क्रम (x = 0; gfs2_log_ops[x]; x++)
		अगर (gfs2_log_ops[x]->lo_beक्रमe_scan)
			gfs2_log_ops[x]->lo_beक्रमe_scan(jd, head, pass);
पूर्ण

अटल अंतरभूत पूर्णांक lops_scan_elements(काष्ठा gfs2_jdesc *jd, u32 start,
				     काष्ठा gfs2_log_descriptor *ld,
				     __be64 *ptr,
				     अचिन्हित पूर्णांक pass)
अणु
	पूर्णांक x, error;
	क्रम (x = 0; gfs2_log_ops[x]; x++)
		अगर (gfs2_log_ops[x]->lo_scan_elements) अणु
			error = gfs2_log_ops[x]->lo_scan_elements(jd, start,
								  ld, ptr, pass);
			अगर (error)
				वापस error;
		पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम lops_after_scan(काष्ठा gfs2_jdesc *jd, पूर्णांक error,
				   अचिन्हित पूर्णांक pass)
अणु
	पूर्णांक x;
	क्रम (x = 0; gfs2_log_ops[x]; x++)
		अगर (gfs2_log_ops[x]->lo_beक्रमe_scan)
			gfs2_log_ops[x]->lo_after_scan(jd, error, pass);
पूर्ण

#पूर्ण_अगर /* __LOPS_DOT_H__ */

