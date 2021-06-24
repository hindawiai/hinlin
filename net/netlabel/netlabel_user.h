<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NetLabel NETLINK Interface
 *
 * This file defines the NETLINK पूर्णांकerface क्रम the NetLabel प्रणाली.  The
 * NetLabel प्रणाली manages अटल and dynamic label mappings क्रम network
 * protocols such as CIPSO and RIPSO.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006
 */

#अगर_अघोषित _NETLABEL_USER_H
#घोषणा _NETLABEL_USER_H

#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/capability.h>
#समावेश <linux/audit.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>
#समावेश <net/netlabel.h>

/* NetLabel NETLINK helper functions */

/**
 * netlbl_netlink_auditinfo - Fetch the audit inक्रमmation from a NETLINK msg
 * @skb: the packet
 * @audit_info: NetLabel audit inक्रमmation
 */
अटल अंतरभूत व्योम netlbl_netlink_auditinfo(काष्ठा sk_buff *skb,
					    काष्ठा netlbl_audit *audit_info)
अणु
	security_task_माला_लोecid_subj(current, &audit_info->secid);
	audit_info->loginuid = audit_get_loginuid(current);
	audit_info->sessionid = audit_get_sessionid(current);
पूर्ण

/* NetLabel NETLINK I/O functions */

पूर्णांक netlbl_netlink_init(व्योम);

/* NetLabel Audit Functions */

काष्ठा audit_buffer *netlbl_audit_start_common(पूर्णांक type,
					      काष्ठा netlbl_audit *audit_info);

#पूर्ण_अगर
