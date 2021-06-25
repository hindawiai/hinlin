<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * dlmdebug.h
 *
 * Copyright (C) 2008 Oracle.  All rights reserved.
 */

#अगर_अघोषित DLMDEBUG_H
#घोषणा DLMDEBUG_H

व्योम dlm_prपूर्णांक_one_mle(काष्ठा dlm_master_list_entry *mle);

#अगर_घोषित CONFIG_DEBUG_FS

काष्ठा debug_lockres अणु
	पूर्णांक dl_len;
	अक्षर *dl_buf;
	काष्ठा dlm_ctxt *dl_ctxt;
	काष्ठा dlm_lock_resource *dl_res;
पूर्ण;

व्योम dlm_debug_init(काष्ठा dlm_ctxt *dlm);

व्योम dlm_create_debugfs_subroot(काष्ठा dlm_ctxt *dlm);
व्योम dlm_destroy_debugfs_subroot(काष्ठा dlm_ctxt *dlm);

व्योम dlm_create_debugfs_root(व्योम);
व्योम dlm_destroy_debugfs_root(व्योम);

#अन्यथा

अटल अंतरभूत व्योम dlm_debug_init(काष्ठा dlm_ctxt *dlm)
अणु
पूर्ण
अटल अंतरभूत व्योम dlm_create_debugfs_subroot(काष्ठा dlm_ctxt *dlm)
अणु
पूर्ण
अटल अंतरभूत व्योम dlm_destroy_debugfs_subroot(काष्ठा dlm_ctxt *dlm)
अणु
पूर्ण
अटल अंतरभूत व्योम dlm_create_debugfs_root(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम dlm_destroy_debugfs_root(व्योम)
अणु
पूर्ण

#पूर्ण_अगर	/* CONFIG_DEBUG_FS */
#पूर्ण_अगर	/* DLMDEBUG_H */
