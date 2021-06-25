<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 *
 * include file क्रम HSR and PRP.
 */

#अगर_अघोषित __HSR_NETLINK_H
#घोषणा __HSR_NETLINK_H

#समावेश <linux/अगर_ether.h>
#समावेश <linux/module.h>
#समावेश <uapi/linux/hsr_netlink.h>

काष्ठा hsr_priv;
काष्ठा hsr_port;

पूर्णांक __init hsr_netlink_init(व्योम);
व्योम __निकास hsr_netlink_निकास(व्योम);

व्योम hsr_nl_ringerror(काष्ठा hsr_priv *hsr, अचिन्हित अक्षर addr[ETH_ALEN],
		      काष्ठा hsr_port *port);
व्योम hsr_nl_nodeकरोwn(काष्ठा hsr_priv *hsr, अचिन्हित अक्षर addr[ETH_ALEN]);
व्योम hsr_nl_framedrop(पूर्णांक dropcount, पूर्णांक dev_idx);
व्योम hsr_nl_linkकरोwn(पूर्णांक dev_idx);

#पूर्ण_अगर /* __HSR_NETLINK_H */
