<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2005 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#अगर_अघोषित __RECOVER_DOT_H__
#घोषणा __RECOVER_DOT_H__

पूर्णांक dlm_रुको_function(काष्ठा dlm_ls *ls, पूर्णांक (*testfn) (काष्ठा dlm_ls *ls));
uपूर्णांक32_t dlm_recover_status(काष्ठा dlm_ls *ls);
व्योम dlm_set_recover_status(काष्ठा dlm_ls *ls, uपूर्णांक32_t status);
पूर्णांक dlm_recover_members_रुको(काष्ठा dlm_ls *ls);
पूर्णांक dlm_recover_directory_रुको(काष्ठा dlm_ls *ls);
पूर्णांक dlm_recover_locks_रुको(काष्ठा dlm_ls *ls);
पूर्णांक dlm_recover_करोne_रुको(काष्ठा dlm_ls *ls);
पूर्णांक dlm_recover_masters(काष्ठा dlm_ls *ls);
पूर्णांक dlm_recover_master_reply(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc);
पूर्णांक dlm_recover_locks(काष्ठा dlm_ls *ls);
व्योम dlm_recovered_lock(काष्ठा dlm_rsb *r);
पूर्णांक dlm_create_root_list(काष्ठा dlm_ls *ls);
व्योम dlm_release_root_list(काष्ठा dlm_ls *ls);
व्योम dlm_clear_toss(काष्ठा dlm_ls *ls);
व्योम dlm_recover_rsbs(काष्ठा dlm_ls *ls);

#पूर्ण_अगर				/* __RECOVER_DOT_H__ */

