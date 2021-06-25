<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2005-2007 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#अगर_अघोषित __RCOM_DOT_H__
#घोषणा __RCOM_DOT_H__

पूर्णांक dlm_rcom_status(काष्ठा dlm_ls *ls, पूर्णांक nodeid, uपूर्णांक32_t status_flags);
पूर्णांक dlm_rcom_names(काष्ठा dlm_ls *ls, पूर्णांक nodeid, अक्षर *last_name,पूर्णांक last_len);
पूर्णांक dlm_send_rcom_lookup(काष्ठा dlm_rsb *r, पूर्णांक dir_nodeid);
पूर्णांक dlm_send_rcom_lock(काष्ठा dlm_rsb *r, काष्ठा dlm_lkb *lkb);
व्योम dlm_receive_rcom(काष्ठा dlm_ls *ls, काष्ठा dlm_rcom *rc, पूर्णांक nodeid);
पूर्णांक dlm_send_ls_not_पढ़ोy(पूर्णांक nodeid, काष्ठा dlm_rcom *rc_in);

#पूर्ण_अगर

