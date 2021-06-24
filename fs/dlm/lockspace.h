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

#अगर_अघोषित __LOCKSPACE_DOT_H__
#घोषणा __LOCKSPACE_DOT_H__

पूर्णांक dlm_lockspace_init(व्योम);
व्योम dlm_lockspace_निकास(व्योम);
काष्ठा dlm_ls *dlm_find_lockspace_global(uपूर्णांक32_t id);
काष्ठा dlm_ls *dlm_find_lockspace_local(व्योम *id);
काष्ठा dlm_ls *dlm_find_lockspace_device(पूर्णांक minor);
व्योम dlm_put_lockspace(काष्ठा dlm_ls *ls);
व्योम dlm_stop_lockspaces(व्योम);

#पूर्ण_अगर				/* __LOCKSPACE_DOT_H__ */

