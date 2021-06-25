<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) 2005-2011 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#अगर_अघोषित __MEMBER_DOT_H__
#घोषणा __MEMBER_DOT_H__

पूर्णांक dlm_ls_stop(काष्ठा dlm_ls *ls);
पूर्णांक dlm_ls_start(काष्ठा dlm_ls *ls);
व्योम dlm_clear_members(काष्ठा dlm_ls *ls);
व्योम dlm_clear_members_gone(काष्ठा dlm_ls *ls);
पूर्णांक dlm_recover_members(काष्ठा dlm_ls *ls, काष्ठा dlm_recover *rv,पूर्णांक *neg_out);
पूर्णांक dlm_is_हटाओd(काष्ठा dlm_ls *ls, पूर्णांक nodeid);
पूर्णांक dlm_is_member(काष्ठा dlm_ls *ls, पूर्णांक nodeid);
पूर्णांक dlm_slots_version(काष्ठा dlm_header *h);
व्योम dlm_slot_save(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc,
		   काष्ठा dlm_member *memb);
व्योम dlm_slots_copy_out(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc);
पूर्णांक dlm_slots_copy_in(काष्ठा dlm_ls *ls);
पूर्णांक dlm_slots_assign(काष्ठा dlm_ls *ls, पूर्णांक *num_slots, पूर्णांक *slots_size,
		     काष्ठा dlm_slot **slots_out, uपूर्णांक32_t *gen_out);
व्योम dlm_lsop_recover_करोne(काष्ठा dlm_ls *ls);

#पूर्ण_अगर                          /* __MEMBER_DOT_H__ */

