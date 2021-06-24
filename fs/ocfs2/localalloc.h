<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * localभाग.स
 *
 * Function prototypes
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_LOCALALLOC_H
#घोषणा OCFS2_LOCALALLOC_H

पूर्णांक ocfs2_load_local_alloc(काष्ठा ocfs2_super *osb);

व्योम ocfs2_shutकरोwn_local_alloc(काष्ठा ocfs2_super *osb);

व्योम ocfs2_la_set_sizes(काष्ठा ocfs2_super *osb, पूर्णांक requested_mb);
अचिन्हित पूर्णांक ocfs2_la_शेष_mb(काष्ठा ocfs2_super *osb);

पूर्णांक ocfs2_begin_local_alloc_recovery(काष्ठा ocfs2_super *osb,
				     पूर्णांक node_num,
				     काष्ठा ocfs2_dinode **alloc_copy);

पूर्णांक ocfs2_complete_local_alloc_recovery(काष्ठा ocfs2_super *osb,
					काष्ठा ocfs2_dinode *alloc);

पूर्णांक ocfs2_alloc_should_use_local(काष्ठा ocfs2_super *osb,
				 u64 bits);

काष्ठा ocfs2_alloc_context;
पूर्णांक ocfs2_reserve_local_alloc_bits(काष्ठा ocfs2_super *osb,
				   u32 bits_wanted,
				   काष्ठा ocfs2_alloc_context *ac);

पूर्णांक ocfs2_claim_local_alloc_bits(काष्ठा ocfs2_super *osb,
				 handle_t *handle,
				 काष्ठा ocfs2_alloc_context *ac,
				 u32 bits_wanted,
				 u32 *bit_off,
				 u32 *num_bits);

पूर्णांक ocfs2_मुक्त_local_alloc_bits(काष्ठा ocfs2_super *osb,
				handle_t *handle,
				काष्ठा ocfs2_alloc_context *ac,
				u32 bit_off,
				u32 num_bits);

व्योम ocfs2_local_alloc_seen_मुक्त_bits(काष्ठा ocfs2_super *osb,
				      अचिन्हित पूर्णांक num_clusters);
व्योम ocfs2_la_enable_worker(काष्ठा work_काष्ठा *work);

#पूर्ण_अगर /* OCFS2_LOCALALLOC_H */
