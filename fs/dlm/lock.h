<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) 2005-2007 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#अगर_अघोषित __LOCK_DOT_H__
#घोषणा __LOCK_DOT_H__

व्योम dlm_dump_rsb(काष्ठा dlm_rsb *r);
व्योम dlm_dump_rsb_name(काष्ठा dlm_ls *ls, अक्षर *name, पूर्णांक len);
व्योम dlm_prपूर्णांक_lkb(काष्ठा dlm_lkb *lkb);
व्योम dlm_receive_message_saved(काष्ठा dlm_ls *ls, काष्ठा dlm_message *ms,
			       uपूर्णांक32_t saved_seq);
व्योम dlm_receive_buffer(जोड़ dlm_packet *p, पूर्णांक nodeid);
पूर्णांक dlm_modes_compat(पूर्णांक mode1, पूर्णांक mode2);
व्योम dlm_put_rsb(काष्ठा dlm_rsb *r);
व्योम dlm_hold_rsb(काष्ठा dlm_rsb *r);
पूर्णांक dlm_put_lkb(काष्ठा dlm_lkb *lkb);
व्योम dlm_scan_rsbs(काष्ठा dlm_ls *ls);
पूर्णांक dlm_lock_recovery_try(काष्ठा dlm_ls *ls);
व्योम dlm_unlock_recovery(काष्ठा dlm_ls *ls);
व्योम dlm_scan_रुकोers(काष्ठा dlm_ls *ls);
व्योम dlm_scan_समयout(काष्ठा dlm_ls *ls);
व्योम dlm_adjust_समयouts(काष्ठा dlm_ls *ls);
पूर्णांक dlm_master_lookup(काष्ठा dlm_ls *ls, पूर्णांक nodeid, अक्षर *name, पूर्णांक len,
		      अचिन्हित पूर्णांक flags, पूर्णांक *r_nodeid, पूर्णांक *result);

पूर्णांक dlm_search_rsb_tree(काष्ठा rb_root *tree, अक्षर *name, पूर्णांक len,
			काष्ठा dlm_rsb **r_ret);

व्योम dlm_recover_purge(काष्ठा dlm_ls *ls);
व्योम dlm_purge_mstcpy_locks(काष्ठा dlm_rsb *r);
व्योम dlm_recover_grant(काष्ठा dlm_ls *ls);
पूर्णांक dlm_recover_रुकोers_post(काष्ठा dlm_ls *ls);
व्योम dlm_recover_रुकोers_pre(काष्ठा dlm_ls *ls);
पूर्णांक dlm_recover_master_copy(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc);
पूर्णांक dlm_recover_process_copy(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc);

पूर्णांक dlm_user_request(काष्ठा dlm_ls *ls, काष्ठा dlm_user_args *ua, पूर्णांक mode,
	uपूर्णांक32_t flags, व्योम *name, अचिन्हित पूर्णांक namelen,
	अचिन्हित दीर्घ समयout_cs);
पूर्णांक dlm_user_convert(काष्ठा dlm_ls *ls, काष्ठा dlm_user_args *ua_पंचांगp,
	पूर्णांक mode, uपूर्णांक32_t flags, uपूर्णांक32_t lkid, अक्षर *lvb_in,
	अचिन्हित दीर्घ समयout_cs);
पूर्णांक dlm_user_aकरोpt_orphan(काष्ठा dlm_ls *ls, काष्ठा dlm_user_args *ua_पंचांगp,
	पूर्णांक mode, uपूर्णांक32_t flags, व्योम *name, अचिन्हित पूर्णांक namelen,
	अचिन्हित दीर्घ समयout_cs, uपूर्णांक32_t *lkid);
पूर्णांक dlm_user_unlock(काष्ठा dlm_ls *ls, काष्ठा dlm_user_args *ua_पंचांगp,
	uपूर्णांक32_t flags, uपूर्णांक32_t lkid, अक्षर *lvb_in);
पूर्णांक dlm_user_cancel(काष्ठा dlm_ls *ls,  काष्ठा dlm_user_args *ua_पंचांगp,
	uपूर्णांक32_t flags, uपूर्णांक32_t lkid);
पूर्णांक dlm_user_purge(काष्ठा dlm_ls *ls, काष्ठा dlm_user_proc *proc,
	पूर्णांक nodeid, पूर्णांक pid);
पूर्णांक dlm_user_deadlock(काष्ठा dlm_ls *ls, uपूर्णांक32_t flags, uपूर्णांक32_t lkid);
व्योम dlm_clear_proc_locks(काष्ठा dlm_ls *ls, काष्ठा dlm_user_proc *proc);

अटल अंतरभूत पूर्णांक is_master(काष्ठा dlm_rsb *r)
अणु
	वापस !r->res_nodeid;
पूर्ण

अटल अंतरभूत व्योम lock_rsb(काष्ठा dlm_rsb *r)
अणु
	mutex_lock(&r->res_mutex);
पूर्ण

अटल अंतरभूत व्योम unlock_rsb(काष्ठा dlm_rsb *r)
अणु
	mutex_unlock(&r->res_mutex);
पूर्ण

#पूर्ण_अगर

