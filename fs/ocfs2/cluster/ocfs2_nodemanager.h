<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ocfs2_nodemanager.h
 *
 * Header describing the पूर्णांकerface between userspace and the kernel
 * क्रम the ocfs2_nodemanager module.
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित _OCFS2_NODEMANAGER_H
#घोषणा _OCFS2_NODEMANAGER_H

#घोषणा O2NM_API_VERSION	5

#घोषणा O2NM_MAX_NODES		255
#घोषणा O2NM_INVALID_NODE_NUM	255

/* host name, group name, cluster name all 64 bytes */
#घोषणा O2NM_MAX_NAME_LEN        64    // __NEW_UTS_LEN

/*
 * Maximum number of global heartbeat regions allowed.
 * **CAUTION**  Changing this number will अवरोध dlm compatibility.
 */
#घोषणा O2NM_MAX_REGIONS	32

#पूर्ण_अगर /* _OCFS2_NODEMANAGER_H */
