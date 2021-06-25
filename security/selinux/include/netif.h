<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Network पूर्णांकerface table.
 *
 * Network पूर्णांकerfaces (devices) करो not have a security field, so we
 * मुख्यtain a table associating each पूर्णांकerface with a SID.
 *
 * Author: James Morris <jmorris@redhat.com>
 *
 * Copyright (C) 2003 Red Hat, Inc., James Morris <jmorris@redhat.com>
 * Copyright (C) 2007 Hewlett-Packard Development Company, L.P.
 *                    Paul Moore <paul@paul-moore.com>
 */
#अगर_अघोषित _SELINUX_NETIF_H_
#घोषणा _SELINUX_NETIF_H_

#समावेश <net/net_namespace.h>

व्योम sel_netअगर_flush(व्योम);

पूर्णांक sel_netअगर_sid(काष्ठा net *ns, पूर्णांक अगरindex, u32 *sid);

#पूर्ण_अगर	/* _SELINUX_NETIF_H_ */

