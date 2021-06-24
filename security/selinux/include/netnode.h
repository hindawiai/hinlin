<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Network node table
 *
 * SELinux must keep a mapping of network nodes to labels/SIDs.  This
 * mapping is मुख्यtained as part of the normal policy but a fast cache is
 * needed to reduce the lookup overhead since most of these queries happen on
 * a per-packet basis.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2007
 */

#अगर_अघोषित _SELINUX_NETNODE_H
#घोषणा _SELINUX_NETNODE_H

व्योम sel_netnode_flush(व्योम);

पूर्णांक sel_netnode_sid(व्योम *addr, u16 family, u32 *sid);

#पूर्ण_अगर
