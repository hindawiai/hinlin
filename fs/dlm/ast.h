<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) 2005-2010 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#अगर_अघोषित __ASTD_DOT_H__
#घोषणा __ASTD_DOT_H__

व्योम dlm_del_ast(काष्ठा dlm_lkb *lkb);
पूर्णांक dlm_add_lkb_callback(काष्ठा dlm_lkb *lkb, uपूर्णांक32_t flags, पूर्णांक mode,
                         पूर्णांक status, uपूर्णांक32_t sbflags, uपूर्णांक64_t seq);
पूर्णांक dlm_rem_lkb_callback(काष्ठा dlm_ls *ls, काष्ठा dlm_lkb *lkb,
                         काष्ठा dlm_callback *cb, पूर्णांक *resid);
व्योम dlm_add_cb(काष्ठा dlm_lkb *lkb, uपूर्णांक32_t flags, पूर्णांक mode, पूर्णांक status,
                uपूर्णांक32_t sbflags);

व्योम dlm_callback_work(काष्ठा work_काष्ठा *work);
पूर्णांक dlm_callback_start(काष्ठा dlm_ls *ls);
व्योम dlm_callback_stop(काष्ठा dlm_ls *ls);
व्योम dlm_callback_suspend(काष्ठा dlm_ls *ls);
व्योम dlm_callback_resume(काष्ठा dlm_ls *ls);

#पूर्ण_अगर


