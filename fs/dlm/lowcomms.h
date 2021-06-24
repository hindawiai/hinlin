<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2009 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#अगर_अघोषित __LOWCOMMS_DOT_H__
#घोषणा __LOWCOMMS_DOT_H__

#घोषणा LOWCOMMS_MAX_TX_BUFFER_LEN	4096

/* चयन to check अगर dlm is running */
बाह्य पूर्णांक dlm_allow_conn;

पूर्णांक dlm_lowcomms_start(व्योम);
व्योम dlm_lowcomms_shutकरोwn(व्योम);
व्योम dlm_lowcomms_stop(व्योम);
व्योम dlm_lowcomms_निकास(व्योम);
पूर्णांक dlm_lowcomms_बंद(पूर्णांक nodeid);
व्योम *dlm_lowcomms_get_buffer(पूर्णांक nodeid, पूर्णांक len, gfp_t allocation, अक्षर **ppc);
व्योम dlm_lowcomms_commit_buffer(व्योम *mh);
पूर्णांक dlm_lowcomms_connect_node(पूर्णांक nodeid);
पूर्णांक dlm_lowcomms_nodes_set_mark(पूर्णांक nodeid, अचिन्हित पूर्णांक mark);
पूर्णांक dlm_lowcomms_addr(पूर्णांक nodeid, काष्ठा sockaddr_storage *addr, पूर्णांक len);

#पूर्ण_अगर				/* __LOWCOMMS_DOT_H__ */

