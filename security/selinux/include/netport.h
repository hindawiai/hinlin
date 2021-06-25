<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Network port table
 *
 * SELinux must keep a mapping of network ports to labels/SIDs.  This
 * mapping is मुख्यtained as part of the normal policy but a fast cache is
 * needed to reduce the lookup overhead.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2008
 */

#अगर_अघोषित _SELINUX_NETPORT_H
#घोषणा _SELINUX_NETPORT_H

व्योम sel_netport_flush(व्योम);

पूर्णांक sel_netport_sid(u8 protocol, u16 pnum, u32 *sid);

#पूर्ण_अगर
